/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *  
 *  This program is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU General Public License 
 *  version 2 as published by the Free Software Foundation.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 *   GNU General Public License for more details.
 *   */ 

/** @file
 *
 * Video decoding driver implementation for VDEC device.
 * VDEC device will teach you how to make device driver with lg115x platform.
 *
 * @author     Junghyun Son(junghyun.son@lge.com)
 * @version    1.0
 * @date       2012.05.10
 * @note       Additional information.
 *
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define USE_ZEROPADDING_DETECT
/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "../mcu/vdec_type_defs.h"

#include <linux/kernel.h>
#include <asm/string.h>	// memset
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/workqueue.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>

#include "../mcu/os_adap.h"
#include "../mcu/ipc_callback.h"

#include "vdc_drv.h"
#include "vdec_stc_timer.h"
#include "vdu_drv.h"

#include "../ves/ves_auib.h"
#include "../ves/ves_cpb.h"

#include "../vds/vdec_rate.h"
#include "../vds/disp_q.h"
#include "../vds/disp_clear_q.h"

#include "hal/top_hal_api.h"
#include "hal/pdec_hal_api.h"
#include "hal/ipc_reg_api.h"
#include "hal/lq_hal_api.h"

#include "../vdec_drv.h"

#include "hma_alloc.h"

#define LOG_NAME	vdec_vdc
#include "log.h"

static int mvc_test;
static int vdc_unlimit_retry;
module_param (mvc_test, int, 0644);
module_param(vdc_unlimit_retry, int, 0644);

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VDC_RESET_THRESHOLD			18000	// 200ms to 90k tick
#define VDC_SEQUENCE_INIT_THRESHOLD 135000	// 1.5s to 90k tick
#define VDC_FEEDING_WAIT_THRESHOLD	900000	// 10s to 90k tick
//#define VDC_DEFAULT_FRAME_DURATION  4500 // default : 20 frame rate (50ms -> 4500 tick for 90K)
#define VDC_MAX_RETRY_COUNT_FOR_DECODING   20
#define VDC_MAX_RETRY_COUNT_FOR_NOT_FOUND  20
#define VDC_MAX_RETRY_COUNT_FOR_FAILED   	3
#define VDC_MAX_DPB_SIZE			32
#define VDC_READPOINTER_MISMATCH_THRESHOLD 0xA
#define VDC_INITIAL_DPB_SIZE			   3 // for multi-channel, this value can privents other channel's starving
#define	VDC_UNKNOWN_PTS				0xFFFFFFFE
#define VDC_INVALID_TIMESTAMP				-1
#define VDC_TS_USESKIPNOTI_MODE
#define VDC_FEEDING_NUMBER_THERSHOLD 450
//#define VDC_TS_USEDECNOTI_MODE
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define GET_SIZE(_start, _end, _total)	( (_start > _end)?	\
												_total-(_start-_end) : _end - _start)
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	VDC_NULL = 0,
	VDC_CLOSING,
	VDC_PLAY,
	VDC_READY,	
	VDC_STOP,	
	VDC_INVALID = 0x20111007
} VDC_STATE_T;

#define FSTR(s0,s1,s2,s3)	((s0<<0)|(s1<<8)|(s2<<16)|(s3<<24))
typedef enum
{
	FEED_DATA = 0,
	FEED_CMD_FLUSH		= FSTR('F','L','S','H'),
	FEED_CMD_SCAN_ALL	= FSTR('S','C','N','A'),
	FEED_CMD_SCAN_I		= FSTR('S','C','N','I'),
	FEED_CMD_OPEN		= FSTR('O','P','E','N'),
	FEED_CMD_CLOSE		= FSTR('C','L','O','S'),
} FEEDDUMP_CMD_T;

typedef struct
{
	UINT32	ui32Pts;
	UINT32	ui32FeededPtr;
	UINT64	ui64Ts;
} VDC_MATCH_INFO_T;

static struct
{
	VDC_CODEC_STATE_T	VCoreState;
	UINT8			ui8UseNum;
	UINT32			ui32RunningTime;
	wait_queue_head_t wait_state_change;
} VCoreInfo[VDEC_NUM_OF_CORE];

static struct
{
	VDC_STATE_T state;
	UINT8		ui8Core;
	// Parameter
	UINT8		ui8VesCh;
	UINT8		ui8DPBSize;
	UINT8		ui8NumofDPBOccupied;
	UINT8		ui8SeqRetryCounter;
	UINT8		ui8DecRetryCounter;
	UINT8		ui8StcDiscontCounter;
	UINT8		ui8ScanMode;
	UINT8 		ui8CodecType;
	UINT8		ui8LROrder;
	UINT8		ui8SamePtsCounter;
	UINT8		ui8FrameFlags[VDC_MAX_DPB_SIZE];

	UINT32		ui32FeededCounter;
	UINT32		ui32prevPTS;
	UINT32		ui32FeedStartTime;

	UINT32		ui32DiscontTotal;

	SINT64		si64prevTS;
	SINT64		si64WaitingTS;

	void		*priv;
	clear_q_t 	*clear_q;
	decoded_q_t	*decoded_q;

	VDU_HANDLE_T hBodaInst;

	BOOLEAN		bWaitingClear;
	BOOLEAN		bFlushed;
	BOOLEAN		bPopped;
	BOOLEAN		bCPBEmpty;
	BOOLEAN		bLive;
	BOOLEAN		bFirstDecoded;
	BOOLEAN		bRemainedData;
	BOOLEAN		bIsDecoding;
	BOOLEAN		bSequenceInitFailed;
	BOOLEAN		bFieldCh;
	BOOLEAN		bFieldButOneValidTsCh;

	volatile BOOLEAN bFlushing;

	VDC_MATCH_INFO_T	stCBInfo;
	SINT64				si64TSInfo[VDC_MAX_DPB_SIZE];
} gsVdcDb[VDEC_NUM_OF_CHANNEL];

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static	DEFINE_SPINLOCK(_VDC_Spinlock);
static  DEFINE_SPINLOCK(_VDC_CheckBodaLock);
static DEFINE_MUTEX (_VDC_IoMutex);
static void _Scheduler(UINT8 ui8VCore);
static void _CheckBodaReset(UINT8 ui8VCore);
static void _DecCallback(VDU_HANDLE_T hInstance, VDU_DEC_RESULT_T* pstDecResult);
static void _FeedMain(UINT8 ui8VCore);
static void _VDC_InitializeDB(UINT8 ui8VdcCh);
static void _VDC_InitInnerDatas(UINT8 ui8VdcCh);
static UINT8 _VDC_FeedSellectChannel(UINT8 ui8VCore);
static BOOLEAN _VDC_CheckUsableDPB(UINT8 ui8VdcCh,BOOLEAN bPrint);
static BOOLEAN _VDC_PrepareFeed(UINT8 ui8VdcCh,VDU_AU_T *stBodaAU);
static BOOLEAN _VDC_PrepareDec(UINT8 ui8VdcCh);
static void _VDC_DecPostProc(UINT8 ui8VdcCh,BOOLEAN bSuspended);
static void _VDC_Close(UINT8 ui8VdcCh);
static UINT64 _VDC_DecideTS(UINT8 ui8VdcCh);
static void _VDC_DecideCoreReady(UINT8 ui8VdcCh);
#ifdef USE_ZEROPADDING_DETECT
static BOOLEAN _VDC_IsZeroPadded(UINT8 ui8VdcCh, UINT32 ui32Start, UINT32 ui32End);
#endif
/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
// for performence test later
//static UINT32 startTime = 0;
//static UINT32 endTime = 0;
//static UINT32 accTime = 0;
/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/

logm_define (vdec_feeddump, log_level_warning);

static struct proc_dir_entry *feeddump_proc_entry;
static unsigned char *feeddump_buf;
static int feeddump_buf_size = 1024*1024;
static int feeddump_buf_head, feeddump_buf_tail;
static spinlock_t feeddump_lock;
static DECLARE_WAIT_QUEUE_HEAD (feeddump_wq);

static int _feeddump_dump (unsigned char *data, int size, int head)
{
	int count1, count2;

	logm_trace (vdec_feeddump, "head %d, size %d\n",
			head, size);
	if (head + size > feeddump_buf_size)
	{
		/* wraped */
		count1 = feeddump_buf_size - head;
		count2 = head+size - feeddump_buf_size;
	}
	else
	{
		count1 = size;
		count2 = 0;
	}

	logm_trace (vdec_feeddump, "count1 %d, count2 %d\n",
			count1, count2);

	if (count1)
		memcpy (feeddump_buf + head, data, count1);
	if (count2)
		memcpy (feeddump_buf, data+count1, count2);

	return 0;
}

static int feeddump_dump (int ves, int vdc, unsigned int cmd,
		int addr,unsigned char *data, int size)
{
	unsigned long flags;
	unsigned long cpb_base;
	unsigned char *cpb_base_virt;
	int cpb_size;
	unsigned char *data1, *data2;
	int head, tail;
	int free;
	int size1, size2;
	int ret = 0;
	int offset;

	spin_lock_irqsave (&feeddump_lock, flags);
	if (!feeddump_buf)
		goto done;

	/* get CPB information */
	cpb_base = VES_CPB_GetBufferBaseAddr (ves);
	cpb_size = VES_CPB_GetBufferSize (ves);
	cpb_base_virt = VES_CPB_TranslatePhyWrPtr (ves, cpb_base);
	if (!cpb_base || !cpb_base_virt)
	{
		logm_warning (vdec_feeddump, "Oops\n");
		ret = -1;
		goto done;
	}

	if (addr)
	{
		offset = addr - cpb_base;
		if (size+offset > cpb_size)
		{
			size1 = cpb_size-offset;
			size2 = size-size1;
		}
		else
		{
			size1 = size;
			size2 = 0;
		}
		data1 = cpb_base_virt + offset;
		data2 = cpb_base_virt;
		logm_trace (vdec_feeddump,
				"size1 0x%x, size2 0x%x from "
				"offset 0x%x(0x%lx)\n",
				size1, size2, offset, cpb_base);
	}
	else if (data)
	{
		data1 = data;
		size1 = size;

		data2 = NULL;
		size2 = 0;

		logm_trace (vdec_feeddump,
				"data %p, size %d from data\n",
				data, size);
	}
	else
	{
		data1 = data2 = NULL;
		size1 = size2 = 0;
	}

	/* get local temporal buffer information */
	head = feeddump_buf_head;
	tail = feeddump_buf_tail;

	logm_trace (vdec_feeddump, "before copy tail %d, head %d, size %d\n",
			tail, head, size);

	/* check we have enough free space */
	free = tail-head;
	if (free <= 0)
		free += feeddump_buf_size;
	logm_trace (vdec_feeddump, "free %d\n", free);

	if (free <= size+12)
	{
		logm_warning (vdec_feeddump, "queue full\n");
		ret = -1;
		goto done;
	}

	/* put stream length */
	_feeddump_dump ((unsigned char *)&size, 4, head);
	head += 4;
	head %= feeddump_buf_size;

	/* put vdc ch */
	_feeddump_dump((unsigned char *)&vdc, 4, head);
	head += 4;
	head %= feeddump_buf_size;

	/* put command */
	_feeddump_dump ((unsigned char *)&cmd, 4, head);
	head += 4;
	head %= feeddump_buf_size;

	/* puth stream or argument */
	if (size1)
	{
		_feeddump_dump (data1, size1, head);
		head += size1;
		head %= feeddump_buf_size;
	}

	if (size2)
	{
		_feeddump_dump (data2, size2, head);
		head += size2;
		head %= feeddump_buf_size;
	}

	/* update head pointer */
	feeddump_buf_head = head;

	wake_up (&feeddump_wq);
	logm_debug (vdec_feeddump, "after  copy tail %d, head %d, written %d\n",
			tail, head, size);

done:
	spin_unlock_irqrestore (&feeddump_lock, flags);

	return ret;
}

static int feeddump_open (struct inode *inode, struct file *file)
{
	unsigned long flags;
	unsigned char *buf;
	int ret = 0;

	logm_debug (vdec_feeddump, "open..\n");

	/* vmalloc() can be scheduled */
	buf = vmalloc (feeddump_buf_size);
	if (!buf)
	{
		logm_warning (vdec_feeddump, "no memory\n");
		return -ENOMEM;
	}

	spin_lock_irqsave (&feeddump_lock, flags);
	if (feeddump_buf)
		ret = -EBUSY;
	else
	{
		feeddump_buf = buf;		
		feeddump_buf_head = feeddump_buf_tail = 0;
	}
	spin_unlock_irqrestore (&feeddump_lock, flags);

	if (ret < 0)
	{
		logm_warning (vdec_feeddump, "feeddump busy\n");
		vfree (buf);
		return ret;
	}

	return 0;
}

static ssize_t feeddump_read (struct file *file, char __user *data, size_t size, loff_t *off)
{
	int count1, count2;
	int ret;
	int head, tail;

	logm_trace (vdec_feeddump, "reading %d bytes\n", size);

	ret = wait_event_interruptible  (feeddump_wq,
			feeddump_buf_head != feeddump_buf_tail);
	if (ret < 0)
		return ret;

	head = feeddump_buf_head;
	tail = feeddump_buf_tail;

	logm_trace (vdec_feeddump, "before copy tail %d, head %d\n", tail, head);

	count1 = head-tail;
	if (count1 < 0)
		count1 += feeddump_buf_size;
	if (count1 > size)
		count1 = size;

	if (tail+count1 > feeddump_buf_size)
	{
		count2 = tail+count1-feeddump_buf_size;
		count1 = feeddump_buf_size - tail;
	}
	else
		count2 = 0;

	if (count1)
	{
		ret = copy_to_user (data, feeddump_buf + tail, count1);
		if (ret)
			return -EFAULT;
	}
	if (count2)
	{
		ret = copy_to_user (data+count1, feeddump_buf, count2);
		if (ret)
			return -EFAULT;
	}

	tail += count1+count2;
	tail %= feeddump_buf_size;
	feeddump_buf_tail = tail;

	logm_debug (vdec_feeddump, "after  copy tail %d, head %d, readed %d\n",
			tail, head, count1+count2);

	return count1+count2;
}

static int feeddump_release (struct inode *inode, struct file *file)
{
	unsigned long flags;

	logm_debug (vdec_feeddump, "close feeddump\n");
	spin_lock_irqsave (&feeddump_lock, flags);
	vfree (feeddump_buf);
	feeddump_buf = NULL;
	spin_unlock_irqrestore (&feeddump_lock, flags);

	return 0;
}

static struct file_operations feeddump_fops =
{
	.open = feeddump_open,
	.read = feeddump_read,
	.release = feeddump_release,
};

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*	None
* @return
*	None
********************************************************************************
*/
void VDC_Init(void)
{
	UINT8 ui8VdcCh, ui8VCore;

	// Initialize VDC DB
	for(ui8VdcCh=0; ui8VdcCh<VDEC_NUM_OF_CHANNEL ; ui8VdcCh++)
	{
		if(ui8VdcCh<MSVC_NUM_OF_CHANNEL)
			gsVdcDb[ui8VdcCh].ui8Core = VDC_CORE_BODA950;
		else	// if(ui8VdcCh<VDEC_NUM_OF_CHANNEL)
			gsVdcDb[ui8VdcCh].ui8Core = VDC_CORE_NOT_SUPPORTED;

		_VDC_InitializeDB(ui8VdcCh);

	}

	// Initialize Core waitqueue
	for(ui8VCore=0; ui8VCore<MSVC_NUM_OF_CORE; ui8VCore++)
	{
		init_waitqueue_head(&VCoreInfo[ui8VCore].wait_state_change);
	}

	VDU_Init(_DecCallback);
	STC_TIMER_Init(_CheckBodaReset);

	log_noti("Init done \n");


	/* make proc debug interface */
	feeddump_proc_entry = proc_create ("feeddump", 0440,
			vdec_proc_root_entry, &feeddump_fops);
	if (!feeddump_proc_entry)
		log_warning ("proc_create failed\n");
}

void VDC_Cleanup (void)
{
	remove_proc_entry ("feeddump", vdec_proc_root_entry);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*typedef struct
{
	UINT8			ui8VesCh;
	void			*priv;
	VDC_SRC_T		ui8Src;
	UINT8			ui8Vcodec;
	UINT32			ui32CpbBufAddr;
	UINT32			ui32CpbBufSize;
	BOOLEAN			bNoAdpStr;
	clear_q_t		*clear_q;
} VDC_OPEN_PARAM_T;
* @return
*	UINT8
********************************************************************************
*/
UINT8 VDC_Open(VDC_OPEN_PARAM_T* pstOpenParam)
{
	UINT8	ui8VCore;
	VDU_CODEC_T	eCodecType;
	VDU_OPEN_PARAM_T stOpenParam;
	UINT8	ui8VdcCh=0xFF;

	mutex_lock (&_VDC_IoMutex);

	switch(pstOpenParam->ui8Vcodec)
	{
	case VDC_CODEC_H264_HP:		eCodecType = VDU_CODEC_H264_AVC; break;
	case VDC_CODEC_MPEG2_HP:	eCodecType = VDU_CODEC_MPEG2; break;
	case VDC_CODEC_MPEG4_ASP:	eCodecType = VDU_CODEC_H263; break;
	case VDC_CODEC_DIVX3:		eCodecType = VDU_CODEC_DIVX3; break;
	case VDC_CODEC_DIVX4:		eCodecType = VDU_CODEC_DIVX4; break;
	case VDC_CODEC_DIVX5:		eCodecType = VDU_CODEC_DIVX5; break;
	case VDC_CODEC_XVID:		eCodecType = VDU_CODEC_XVID; break;
	case VDC_CODEC_VC1_RCV_V1:	eCodecType = VDU_CODEC_VC1_RCV_V1; break;
	case VDC_CODEC_VC1_RCV_V2:	eCodecType = VDU_CODEC_VC1_RCV_V2; break;
	case VDC_CODEC_VC1_ES:		eCodecType = VDU_CODEC_VC1_ES; break;
	case VDC_CODEC_AVS:			eCodecType = VDU_CODEC_AVS; break;
	case VDC_CODEC_RVX:			eCodecType = VDU_CODEC_RVX; break;
	case VDC_CODEC_VP8:			eCodecType = VDU_CODEC_VP8; break;
	case VDC_CODEC_H264_MVC:	eCodecType = VDU_CODEC_H264_MVC; break;
	case VDC_CODEC_THEORA:		eCodecType = VDU_CODEC_THEORA; break;
	default: eCodecType = VDU_CODEC_INVALID; break;
	}

	switch(pstOpenParam->ui8Vcodec)
	{
	case VDC_CODEC_H264_HP:
	case VDC_CODEC_VC1_RCV_V1:
	case VDC_CODEC_VC1_RCV_V2:
	case VDC_CODEC_VC1_ES:
	case VDC_CODEC_MPEG2_HP:
	case VDC_CODEC_AVS:
	case VDC_CODEC_MPEG4_ASP:
	case VDC_CODEC_XVID:
	case VDC_CODEC_DIVX3:
	case VDC_CODEC_DIVX4:
	case VDC_CODEC_DIVX5:
	case VDC_CODEC_RVX:
	case VDC_CODEC_VP8:
	case VDC_CODEC_H264_MVC:
	case VDC_CODEC_THEORA:
		ui8VCore = VDC_CORE_BODA950;
		if(VCoreInfo[ui8VCore].ui8UseNum>=MSVC_NUM_OF_CHANNEL)
			break;

		if(mvc_test == 1) stOpenParam.eCodecType = VDU_CODEC_H264_MVC;
		else stOpenParam.eCodecType = eCodecType;

		stOpenParam.eFrameMapType = (pstOpenParam->output_memory_format == VDC_MEMORY_FORMAT_RASTER)? VDU_FRM_MAP_LINEAR : VDU_FRM_MAP_TILED_MIXED_V;
		stOpenParam.ui32CPBAddr = pstOpenParam->ui32CpbBufAddr;
		stOpenParam.ui32CPBSize = pstOpenParam->ui32CpbBufSize;
		stOpenParam.ui32DataSize = sizeof(VDC_MATCH_INFO_T);
		ui8VdcCh = (UINT8)VDU_Open(&stOpenParam);
		gsVdcDb[ui8VdcCh].hBodaInst = (VDU_HANDLE_T)ui8VdcCh;
		// vdec core state
		if(VCoreInfo[ui8VCore].VCoreState == VDC_CODEC_STATE_NULL)
		{
			VCoreInfo[ui8VCore].VCoreState = VDC_CODEC_STATE_READY;
		}
		VCoreInfo[ui8VCore].ui8UseNum++;
		break;
	default:
		ui8VCore = VDC_CORE_NOT_SUPPORTED;
		log_error("ch:%d Not Support Codec Type : %d \n", ui8VdcCh, pstOpenParam->ui8Vcodec);
		break;
	}

	if( ui8VdcCh >= VDEC_NUM_OF_CHANNEL )
	{
		log_error("ch:%d Not Enough VDC Channel - %s, Used Ch:%d \n"
							, ui8VdcCh
							, (ui8VCore==VDC_CORE_BODA950)? "BODA950" : "Not Support Codec"
							, VCoreInfo[ui8VCore].ui8UseNum);
		mutex_unlock (&_VDC_IoMutex);
		return 0xFF;
	}

	if(gsVdcDb[ui8VdcCh].state != VDC_NULL)
	{
		log_error("ch:%d already used Current VDC Channel \n", ui8VdcCh);
		mutex_unlock (&_VDC_IoMutex);
		return 0xFF;
	}

	if( pstOpenParam->ui8Src  <= VDC_SRC_SDEC2 ) {
		gsVdcDb[ui8VdcCh].bLive = TRUE;
	} else gsVdcDb[ui8VdcCh].bLive = FALSE;

	// feeder state
	gsVdcDb[ui8VdcCh].state = VDC_READY;
	if(mvc_test == 1) gsVdcDb[ui8VdcCh].ui8CodecType = VDC_CODEC_H264_MVC;
	else gsVdcDb[ui8VdcCh].ui8CodecType = pstOpenParam->ui8Vcodec;

	if(ui8VCore != gsVdcDb[ui8VdcCh].ui8Core)
	{
		log_error("Ch:%d Invalid Core(%d-%d) \n", ui8VdcCh,ui8VCore,gsVdcDb[ui8VdcCh].ui8Core);
		gsVdcDb[ui8VdcCh].ui8Core = ui8VCore;
	}
	gsVdcDb[ui8VdcCh].priv = pstOpenParam->priv;
	gsVdcDb[ui8VdcCh].ui8VesCh = pstOpenParam->ui8VesCh;
	gsVdcDb[ui8VdcCh].clear_q = pstOpenParam->clear_q;
	gsVdcDb[ui8VdcCh].decoded_q = pstOpenParam->decoded_q;

	feeddump_dump(gsVdcDb[ui8VdcCh].ui8VesCh,ui8VdcCh,
			FEED_CMD_OPEN,
			0, (unsigned char*)&pstOpenParam->ui8Vcodec,
			sizeof(UINT8));

	log_noti("VDCch:%d BODAch:%d VESch:%d clear_q:%p decoded_q:%p codec:%d usenum:%d \n"
		,ui8VdcCh, gsVdcDb[ui8VdcCh].hBodaInst, gsVdcDb[ui8VdcCh].ui8VesCh
		,gsVdcDb[ui8VdcCh].clear_q,gsVdcDb[ui8VdcCh].decoded_q, gsVdcDb[ui8VdcCh].ui8CodecType, VCoreInfo[ui8VCore].ui8UseNum);

	mutex_unlock (&_VDC_IoMutex);
	return ui8VdcCh;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
********************************************************************************
*/
void VDC_Close(UINT8 ui8VdcCh)
{
	int irq_enabled;	
	ULONG flags=0;

	if( ui8VdcCh >= VDEC_NUM_OF_CHANNEL )
	{
		log_error("ch:%d wrong \n", ui8VdcCh);
		return;
	}

	spin_lock_irqsave(&_VDC_Spinlock, flags); 

	/* disable irq */
	irq_enabled = TOP_HAL_DisableExtIntr (BUFFER_STATUS);

	log_noti("ch:%d close start \n", ui8VdcCh);
	
	gsVdcDb[ui8VdcCh].state = VDC_CLOSING;

	spin_unlock_irqrestore(&_VDC_Spinlock, flags);

	/* close vdc */
	_VDC_Close(ui8VdcCh);

	feeddump_dump(gsVdcDb[ui8VdcCh].ui8VesCh, ui8VdcCh,
			FEED_CMD_CLOSE,
			0, NULL, 0);

	/* enable the irq */

	if (irq_enabled)
		TOP_HAL_EnableExtIntr (BUFFER_STATUS);
	else
		log_warning ("do not enable interrupt\n");
	
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDC_Reset(UINT8 ui8VdcCh)
{
	UINT8 ui8VCore;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return;
	}

	mutex_lock (&_VDC_IoMutex);

	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;

	switch(ui8VCore)
	{
	case VDC_CORE_BODA950:
		// BODA Instance Reset
		if(gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE 
			&& VDU_Reset(gsVdcDb[ui8VdcCh].hBodaInst) == VDU_RET_OK)
		{
			// rd off set to wr off set
			log_noti("ch:%d boda reseted, BODA IDLE \n",ui8VdcCh);
			VCoreInfo[ui8VCore].VCoreState = VDC_CODEC_STATE_READY;
			STC_TIMER_Stop();
			if(!gsVdcDb[ui8VdcCh].bLive) wake_up_all (&VCoreInfo[ui8VCore].wait_state_change);
			_VDC_InitInnerDatas(ui8VdcCh);
		}
		else
		{
			log_error("ch:%d boda reset failed \n",ui8VdcCh);
		}
		break;
	default:
		log_error("ch:%d Not Support Core(%d)\n", ui8VdcCh, ui8VCore );
		break;
	}

	mutex_unlock (&_VDC_IoMutex);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDC_Start(UINT8 ui8VdcCh)
{
	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return;
	}
	log_noti("ch:%d Starts \n", ui8VdcCh);
	gsVdcDb[ui8VdcCh].state = VDC_PLAY;
}
/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDC_Update(UINT8 ui8VdcCh)
{
	UINT8 ui8VCore;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return;
	}

	log_trace("ch:%d, Feed by VDC Update \n",ui8VdcCh);
	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;
	_Scheduler(ui8VCore);
}
/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDC_Flush(UINT8 ui8VdcCh)
{
	UINT8 ui8Index;
	UINT8 ui8VCore;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL ||gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return;
	}

	mutex_lock (&_VDC_IoMutex);

	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;

	log_info("Ch:%d State:%d \n", ui8VdcCh, gsVdcDb[ui8VdcCh].state);

	switch(ui8VCore)
	{
	case VDC_CORE_BODA950:
		if( gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE 
			&& VDU_Flush(gsVdcDb[ui8VdcCh].hBodaInst) == VDU_RET_OK )
		{
			// initialize timestamp & feeded addr
			for(ui8Index=0;ui8Index<VDC_MAX_DPB_SIZE;ui8Index++){
				gsVdcDb[ui8VdcCh].si64TSInfo[ui8Index]=VDC_INVALID_TIMESTAMP;
			}
			gsVdcDb[ui8VdcCh].si64WaitingTS=VDC_INVALID_TIMESTAMP;
			gsVdcDb[ui8VdcCh].si64prevTS=VDC_INVALID_TIMESTAMP;
			gsVdcDb[ui8VdcCh].bCPBEmpty = FALSE;
			gsVdcDb[ui8VdcCh].bFlushed = TRUE;
			gsVdcDb[ui8VdcCh].ui32FeededCounter = 0;
			gsVdcDb[ui8VdcCh].ui32FeedStartTime = TOP_HAL_GetGSTCC();			
			log_noti("ch:%d BODA Flush Done, BODA IDLE \n",ui8VdcCh);
		}
		else
		{
			log_error("ch:%d Flush failed \n",ui8VdcCh);
		}
		feeddump_dump(gsVdcDb[ui8VdcCh].ui8VesCh,ui8VdcCh,
					FEED_CMD_FLUSH,
					0,NULL,0);
		_VDC_DecideCoreReady(ui8VdcCh);
		break;
	default:
		log_error("ch:%d Not Support Core:%d \n",ui8VdcCh,ui8VCore);
		break;
	}

	mutex_unlock (&_VDC_IoMutex);
}

void VDC_Stop(UINT8 ui8VdcCh)
{
	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return;
	}
	gsVdcDb[ui8VdcCh].state = VDC_STOP;
	log_trace("ch:%d, Stopped \n",ui8VdcCh);
}

VDC_CODEC_STATE_T VDC_GetCoreState(UINT8 ui8VdcCh, wait_queue_head_t **wait)
{
	UINT8 ui8VCore;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return 0;
	}

	//log_trace("ch:%d State:%d \n", ui8VdcCh, gsVdcDb[ui8VdcCh].state);

	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;

	if (wait)
		*wait = &VCoreInfo[ui8VCore].wait_state_change;

	return VCoreInfo[ui8VCore].VCoreState;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDC_SetSkipMode(UINT8 ui8VdcCh, VDC_SKIP_T eSkipMode)
{
	UINT8 ui8VCore;
	VDU_OPTION_T stOption = VDU_OPTION_INIT_VALUE;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Current State is NULL \n", ui8VdcCh);
		return;
	}

	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;

	switch(ui8VCore)
	{
	case VDC_CORE_BODA950:
		stOption.ePicScanMode = (VDU_PIC_SCAN_T)eSkipMode;
		if(gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE &&
			VDU_SetOption(gsVdcDb[ui8VdcCh].hBodaInst, &stOption) == VDU_RET_OK){
			switch(eSkipMode){
				case VDC_SKIP_NONE:
					gsVdcDb[ui8VdcCh].ui8ScanMode = VDC_SKIP_NONE;
					feeddump_dump(gsVdcDb[ui8VdcCh].ui8VesCh,ui8VdcCh,
							FEED_CMD_SCAN_ALL,
							0,NULL,0);
					break;
				case VDC_SKIP_PB:
					gsVdcDb[ui8VdcCh].ui8ScanMode = VDC_SKIP_PB;
					feeddump_dump(gsVdcDb[ui8VdcCh].ui8VesCh,ui8VdcCh,
							FEED_CMD_SCAN_I,
							0,NULL,0);
					break;
				default:
					break;
			}
			log_noti("ch:(%d) skip mode done:%d \n",ui8VdcCh,(int)eSkipMode);
		}
		else{
			log_error("ch:%d set option error \n",ui8VdcCh);
		}
		break;
	default:
		log_error("ch:%d Not Support Core(%d) \n", ui8VdcCh, ui8VCore);
		break;
	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDC_SetUserDataOutput(UINT8 ui8VdcCh, BOOLEAN bEnable)
{
	UINT8 ui8VCore;
	VDU_OPTION_T stOption = VDU_OPTION_INIT_VALUE;
	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Current State is NULL \n", ui8VdcCh);
		return;
	}

	switch(ui8VCore)
	{
	case VDC_CORE_BODA950:
		stOption.eUserData = VDU_USERDATA_ENABLE;
		if(gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE && 
			VDU_SetOption(gsVdcDb[ui8VdcCh].hBodaInst, &stOption) == VDU_RET_OK){
			log_noti("ch:%d userdata enabled \n",ui8VdcCh);
		} else {
			log_noti("ch:%d userdata disabled \n",ui8VdcCh);
		}
		break;
	default:
		log_error("ch:%d Not Support Core(%d) \n", ui8VdcCh, ui8VCore);
		break;
	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
	0 = success
	-1 = fail
*
********************************************************************************
*/

void VDC_GetFrame(UINT8 ui8VdcCh, UINT8 ui8FrameNum, void* vpFrameBuf)
{
	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return;
	}

	if( gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE &&
		VDU_GetLinearFrame(gsVdcDb[ui8VdcCh].hBodaInst, ui8FrameNum, vpFrameBuf) ){
		log_debug("ch:%d get frame success idx:%d \n",ui8VdcCh,ui8FrameNum);
	}
	else {
		log_warning("ch:%d get frame failed idx:%d \n", ui8VdcCh,ui8FrameNum);
	}
}

/*----------------------------------------------------------------------------------------
    Static Function Definitions
----------------------------------------------------------------------------------------*/
/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/

static void _Scheduler(UINT8 ui8VCore)
{
	ULONG flags = 0;
	spin_lock_irqsave(&_VDC_Spinlock, flags);
	// check Core state
	if(VCoreInfo[ui8VCore].VCoreState > VDC_CODEC_STATE_READY)
	{
		log_trace("BODA BUSY \n");
		spin_unlock_irqrestore(&_VDC_Spinlock, flags);
		return;
	}
	else VCoreInfo[ui8VCore].VCoreState = VDC_CODEC_STATE_FEEDING;
	spin_unlock_irqrestore(&_VDC_Spinlock, flags);
	_FeedMain(ui8VCore);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static void _CheckBodaReset(UINT8 ui8VCore)
{
	UINT8 ui8VdcCh;
	BOOLEAN bFound=FALSE;
	UINT32 ui32prevTime = VCoreInfo[ui8VCore].ui32RunningTime;
	UINT32 ui32CurTime = TOP_HAL_GetGSTCC();
	UINT32 ui32Diff = GET_SIZE(ui32prevTime, ui32CurTime, 0xFFFFFFFF);
	decoded_buffer_t stDecBuf = {0,};
	log_user2("BODA Watchdog, prev:%d, cur:%d, diff:%d \n",ui32prevTime,ui32CurTime,ui32Diff);

	if(VCoreInfo[ui8VCore].VCoreState != VDC_CODEC_STATE_RUNNING) {		
		return;
	}
	if(ui32Diff >= VDC_RESET_THRESHOLD)
	{
		log_noti("BODA Watchdog HW Reset Occurs:PrevRunningTime:%d,CurTime:%d,Diff:%d \n"
			,ui32prevTime,ui32CurTime,ui32Diff);
		VCoreInfo[ui8VCore].ui32RunningTime = TOP_HAL_GetGSTCC();
		stDecBuf.buffer_index = -1;
		stDecBuf.report = DECODED_REPORT_HW_RESET;
		for(ui8VdcCh=0;ui8VdcCh<VDEC_NUM_OF_CHANNEL;ui8VdcCh++) {
			/* report to top for reset current non-responsible decoding channel */
			if(gsVdcDb[ui8VdcCh].state == VDC_PLAY && gsVdcDb[ui8VdcCh].bIsDecoding) {
				bFound = TRUE;
				break;
			}
		}
		if( bFound && gsVdcDb[ui8VdcCh].decoded_q != NULL ) {
			decoded_q_push(gsVdcDb[ui8VdcCh].decoded_q, &stDecBuf);
			log_noti("ch:%d request reset pushed \n",ui8VdcCh);
		}
		else {
			log_warning("CANNOT FIND VALID BODA CHANNEL, No Require RESET \n");			
		}
	}

}

//static UINT32 ui32checkTime=0;
static void _DecCallback(VDU_HANDLE_T hInstance, VDU_DEC_RESULT_T* pstDecResult)
{
	UINT8 ui8VdcCh = (UINT8)hInstance;
	SINT8 si8FrameIndex = pstDecResult->si8FrmIndex;
	decoded_buffer_t stDecBuf = {0,};
	const char *pic_type = 0;
	const char *interace = 0;
	UINT32 ui32feededaddr = 0;
	ULONG flags = 0;
	UINT8 ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;
	UINT32 ui32CurTime = 0;
	UINT32 ui32Diff = 0;
	UINT64 ui64Debug90kTS = 0;
	int idx=0;
#ifdef VDC_TS_USEDECNOTI_MODE
	int index=0;
#endif

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state == VDC_NULL)
	{
		log_warning("ch:%d Already Closed channel received Callback\n", ui8VdcCh);
		_VDC_DecideCoreReady(ui8VdcCh);
		goto ERROR;
	}
	else if(gsVdcDb[ui8VdcCh].state == VDC_CLOSING)
	{
		log_noti("ch:%d Closing Channel received Callback\n", ui8VdcCh);
		_VDC_DecideCoreReady(ui8VdcCh);
		goto ERROR;
	}

	//log_info("ch:%d noti type:%d time:%d \n",ui8VdcCh,pstDecResult->eNotiType,GET_SIZE(ui32checkTime,TOP_HAL_GetGSTCC(),0xFFFFFFFF));
	//ui32checkTime = TOP_HAL_GetGSTCC();

	spin_lock_irqsave(&_VDC_CheckBodaLock,flags);

	if(pstDecResult->bFieldSuccess){
		log_user3("ch:%d field channel detected \n",ui8VdcCh);
		gsVdcDb[ui8VdcCh].bFieldCh = TRUE;
	}

	ui32CurTime = TOP_HAL_GetGSTCC();
	ui32Diff = GET_SIZE(gsVdcDb[ui8VdcCh].ui32FeedStartTime, ui32CurTime, 0xFFFFFFFF);
	if(ui32Diff > VDC_FEEDING_WAIT_THRESHOLD/10 &&  pstDecResult->eNotiType != VDU_NOTI_CPB_EMPTY)
	{
		for(idx=1; idx< VDC_MAX_DPB_SIZE; idx++){
			gsVdcDb[ui8VdcCh].si64TSInfo[idx] = VDC_INVALID_TIMESTAMP;
		}
	}

	if(pstDecResult->bDecSuccess){	
		gsVdcDb[ui8VdcCh].ui32FeededCounter = 0;
		gsVdcDb[ui8VdcCh].ui32FeedStartTime = TOP_HAL_GetGSTCC();
#ifdef VDC_TS_USEDECNOTI_MODE
		// if 1 frame decoding success, ts pool update
		if(!gsVdcDb[ui8VdcCh].bLive && gsVdcDb[ui8VdcCh].ui8ScanMode==VDC_SKIP_NONE){
			for(index=0; index<VDC_MAX_DPB_SIZE; index++){
				if(gsVdcDb[ui8VdcCh].si64TSInfo[index] == VDC_INVALID_TIMESTAMP){
					log_user1("ch:%d decSuccess,so save ts:%lld at %d \n",ui8VdcCh,gsVdcDb[ui8VdcCh].si64WaitingTS,index);
					gsVdcDb[ui8VdcCh].si64TSInfo[index] = gsVdcDb[ui8VdcCh].si64WaitingTS;
					break;
				}
			}
		}
#endif
	}
#ifdef VDC_TS_USESKIPNOTI_MODE
	if(pstDecResult->eNotiType == VDU_NOTI_FRAME_SKIP || pstDecResult->eNotiType == VDU_NOTI_DECODING_ERROR
		|| pstDecResult->eNotiType == VDU_NOTI_SKIP_EMPTY || pstDecResult->si8FrmIndex == VDU_FRAME_INDEX_SKIPPED) {
		log_user1("ch:%d detect skipped ts noti \n",ui8VdcCh);
		_VDC_DecideTS(ui8VdcCh);
		// if field fileplay, skip one timestamp
		if(gsVdcDb[ui8VdcCh].bFieldCh && !gsVdcDb[ui8VdcCh].bFieldButOneValidTsCh) _VDC_DecideTS(ui8VdcCh);
	}	
#endif

	stDecBuf.buffer_index = -1;

	if(vdc_unlimit_retry==0){
		switch (pstDecResult->eNotiType)
		{
			case VDU_NOTI_HEADER_NOT_FOUND:
				if(!gsVdcDb[ui8VdcCh].bLive && gsVdcDb[ui8VdcCh].ui8SeqRetryCounter>=VDC_MAX_RETRY_COUNT_FOR_NOT_FOUND){
					stDecBuf.report = DECODED_REPORT_SEQUENCE_INIT_FAILED;
				}
				break;
			case VDU_NOTI_SEQ_INIT_FAIL:
				if(!gsVdcDb[ui8VdcCh].bLive && gsVdcDb[ui8VdcCh].ui8SeqRetryCounter>=VDC_MAX_RETRY_COUNT_FOR_FAILED){
					stDecBuf.report = DECODED_REPORT_SEQUENCE_INIT_FAILED;
				}
				break;
			//case VDU_NOTI_DECODING_ERROR:
				//stDecBuf.report = DECODED_REPORT_DECODE_FAILED; break;
			default: break;
		}
	}

	// forced clear decoded frame when flushing
	if( si8FrameIndex >= 0 && gsVdcDb[ui8VdcCh].state == VDC_STOP ){
		if ( gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE &&
			VDU_ClearFrame(gsVdcDb[ui8VdcCh].hBodaInst, si8FrameIndex & 0xFFFF) == VDU_RET_OK){
			log_debug("ch(%d) forced clear %d frame \n",ui8VdcCh, si8FrameIndex);
		} else {
			log_warning("ch(%d) forced clear %d failed \n",ui8VdcCh, si8FrameIndex);
		}
			
	}
	else if( si8FrameIndex >= 0 )
	{
		VDU_FRM_INFO_T stFrameInfo;

		if( gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE && 
			VDU_GetFrameInfo(hInstance, si8FrameIndex, &stFrameInfo) == VDU_RET_OK )
		{
			gsVdcDb[ui8VdcCh].ui8DPBSize = stFrameInfo.ui8NumOfFrames;

			// push decoding info
			stDecBuf.buffer_index = si8FrameIndex;
			stDecBuf.stride = stFrameInfo.stRect.ui32Stride;
			stDecBuf.width = stFrameInfo.stRect.ui32PicWidth;
			stDecBuf.height = stFrameInfo.stRect.ui32PicHeight;
			stDecBuf.crop_left = stFrameInfo.stRect.ui16CropLeft;
			stDecBuf.crop_right = stFrameInfo.stRect.ui16CropRight;
			stDecBuf.crop_top = stFrameInfo.stRect.ui16CropTop;
			stDecBuf.crop_bottom = stFrameInfo.stRect.ui16CropBottom;

			switch (stFrameInfo.stDispInfo.eFrameScanType)
			{
			default:
			case VDU_FRM_SCAN_PROGRESSIVE:
				stDecBuf.interlace = decoded_buffer_interlace_none; break;
			case VDU_FRM_SCAN_TOP_FIRST:
				stDecBuf.interlace = decoded_buffer_interlace_top_first; break;
			case VDU_FRM_SCAN_BOTTOM_FIRST:
				stDecBuf.interlace = decoded_buffer_interlace_bottom_first;	break;
			}
			stDecBuf.error_blocks = stFrameInfo.stDispInfo.ui8ErrorRate;
			switch (stFrameInfo.stDispInfo.eOrderOf3D)
			{
			default:
			case VDU_FRM_3D_NONE:
				stDecBuf.multi_picture = decoded_buffer_multi_picture_none;	break;
			case VDU_FRM_3D_LEFT:
				stDecBuf.multi_picture = decoded_buffer_multi_picture_left;	break;
			case VDU_FRM_3D_RIGHT:
				stDecBuf.multi_picture = decoded_buffer_multi_picture_right;break;
			}
			switch (stFrameInfo.stDispInfo.eFrameMapType)
			{
			default:
			case VDU_FRM_MAP_TILED_MIXED_V:
				stDecBuf.vdo_map_type = vdo_map_type_mixed; break;
			case VDU_FRM_MAP_TILED_FRAME_V:
				stDecBuf.vdo_map_type = vdo_map_type_frame; break;
			case VDU_FRM_MAP_LINEAR:
				stDecBuf.vdo_map_type = vdo_map_type_linear; break;
			}
			stDecBuf.frame_packing_arrangement = stFrameInfo.stDispInfo.si8FramePackArrange;
			stDecBuf.addr_tile_base = stFrameInfo.stAddress.ui32TiledBase;
			stDecBuf.addr_y = stFrameInfo.stAddress.ui32Y;
			stDecBuf.addr_cb = stFrameInfo.stAddress.ui32Cb;
			stDecBuf.addr_cr = stFrameInfo.stAddress.ui32Cr;
			if(stFrameInfo.stFrameRate.ui32Divider == 0){
				stDecBuf.framerate_num = 0;
				stDecBuf.framerate_den = 1;
			}
			else if(stFrameInfo.stFrameRate.ui32Residual / stFrameInfo.stFrameRate.ui32Divider < 1)
			{
				stDecBuf.framerate_num = 0;
				stDecBuf.framerate_den = 1;
			}
			else{
				stDecBuf.framerate_num = stFrameInfo.stFrameRate.ui32Residual;
				if(gsVdcDb[ui8VdcCh].ui8CodecType == VDC_CODEC_H264_MVC)
					stDecBuf.framerate_num *= 2;
				stDecBuf.framerate_den = stFrameInfo.stFrameRate.ui32Divider;
			}
			//stDecBuf.sar = stFrameInfo.stAspectRatio.ui8Mpeg2Dar;
			stDecBuf.par_w = stFrameInfo.stAspectRatio.ui16ParW;
			stDecBuf.par_h = stFrameInfo.stAspectRatio.ui16ParH;
			// variable frame rate not used

			if(stFrameInfo.stDispInfo.bLowDelay == 1) stDecBuf.report += DECODED_REPORT_LOW_DELAY;

			// push display info
			stDecBuf.picture_type = stFrameInfo.stDispInfo.ui8PictureType;
			stDecBuf.display_period = stFrameInfo.stDispInfo.ui8DisplayPeriod;
			stDecBuf.active_format = stFrameInfo.stUserData.ui8ActiveFmtDesc;

			// user data
			stDecBuf.user_data_addr = (void*)stFrameInfo.stUserData.ui32Address;
			stDecBuf.user_data_size = stFrameInfo.stUserData.ui32Size;
			stDecBuf.top_field_first = stFrameInfo.stDispInfo.bTopFieldFirst;
			stDecBuf.repeat_first_field = stFrameInfo.stDispInfo.bRepeatFirstField;

			// default value(pushing dq): ui32Y_FrameOffset = 0, ui32C_FrameOffset = 0, bFieldPicture=FALSE, ui32UId = 0

			//log_trace("ch:%d cb timestamp:%lld \n",ui8VdcCh,ui64ts);
			ui32feededaddr = ((VDC_MATCH_INFO_T*)(stFrameInfo.pAddtionalData))->ui32FeededPtr;

			if((gsVdcDb[ui8VdcCh].ui8CodecType == VDC_CODEC_H264_HP  ||
				gsVdcDb[ui8VdcCh].ui8CodecType == VDC_CODEC_MPEG2_HP ||
				gsVdcDb[ui8VdcCh].ui8CodecType == VDC_CODEC_H264_MVC) &&
				(ui32feededaddr - stFrameInfo.ui32CurRdPtr > VDC_READPOINTER_MISMATCH_THRESHOLD)){
				gsVdcDb[ui8VdcCh].bRemainedData = TRUE;
			} else gsVdcDb[ui8VdcCh].bRemainedData = FALSE;

			if(gsVdcDb[ui8VdcCh].bFirstDecoded==FALSE){
				gsVdcDb[ui8VdcCh].ui8LROrder=(UINT8)stDecBuf.multi_picture;
				gsVdcDb[ui8VdcCh].bFirstDecoded=TRUE;
			}

			stDecBuf.pts = ((VDC_MATCH_INFO_T*)(stFrameInfo.pAddtionalData))->ui32Pts;

			// if live, do not use timestamp reordering
			if(gsVdcDb[ui8VdcCh].bLive){				
				stDecBuf.timestamp = VDC_INVALID_TIMESTAMP;
			}
			else {
				if(gsVdcDb[ui8VdcCh].ui8ScanMode != VDC_SKIP_NONE)
					stDecBuf.timestamp = ((VDC_MATCH_INFO_T*)(stFrameInfo.pAddtionalData))->ui64Ts;
				else {
					stDecBuf.timestamp = _VDC_DecideTS(ui8VdcCh);
					// if field fileplay, skip one timestamp
					if(gsVdcDb[ui8VdcCh].bFieldCh && !gsVdcDb[ui8VdcCh].bFieldButOneValidTsCh) _VDC_DecideTS(ui8VdcCh);
				}
			}
			if(log_enabled (log_level_info))
			{
				switch (stDecBuf.picture_type)
				{
					case decoded_buffer_picture_type_i:	pic_type = "I";	break;
					case decoded_buffer_picture_type_p:	pic_type = "P";	break;
					case decoded_buffer_picture_type_b:	pic_type = "B";	break;
					case decoded_buffer_picture_type_bi: pic_type = "BI"; break;
					case decoded_buffer_picture_type_d: pic_type = "D";	break;
					case decoded_buffer_picture_type_s:	pic_type = "S";	break;
					case decoded_buffer_picture_type_pskip:	pic_type = "PSKIP";	break;
				}

				switch (stDecBuf.interlace)
				{
					case decoded_buffer_interlace_top_first:
					case decoded_buffer_interlace_bottom_first: interace = "i"; break;
					case decoded_buffer_interlace_none: interace = "p"; break;
					default: interace = "n"; break;
				}

				ui64Debug90kTS = stDecBuf.timestamp*9;
				do_div (ui64Debug90kTS, 100000);

				if(gsVdcDb[ui8VdcCh].bLive == TRUE){
					log_info("PUSH!!(%d) [%s][%dx%d@%d%s]disp:%d rd:%05x auib:%d cpb:%08d dpb:%02d/%d yaddr:%08lu ld:%d LR:%d err:%d fpa:%d mt:%d dt:%04d discont:%d ts:%lld \t pts:%d(0x%08X) \n"
					,ui8VdcCh,pic_type,stDecBuf.width,stDecBuf.height,stDecBuf.framerate_num/stDecBuf.framerate_den,interace,si8FrameIndex,ui32feededaddr - stFrameInfo.ui32CurRdPtr
					,VES_AUIB_NumActive(gsVdcDb[ui8VdcCh].ui8VesCh),VES_CPB_GetUsedBuffer(gsVdcDb[ui8VdcCh].ui8VesCh),gsVdcDb[ui8VdcCh].ui8NumofDPBOccupied
					,gsVdcDb[ui8VdcCh].ui8DPBSize,stDecBuf.addr_y,stDecBuf.report,stDecBuf.multi_picture,stDecBuf.error_blocks,stDecBuf.frame_packing_arrangement
					,stDecBuf.vdo_map_type,GET_SIZE(VCoreInfo[ui8VCore].ui32RunningTime,TOP_HAL_GetGSTCC(),0xFFFFFFFF)/90,gsVdcDb[ui8VdcCh].ui8StcDiscontCounter,stDecBuf.timestamp,stDecBuf.pts,stDecBuf.pts);
				} else {
					log_info("PUSH!!(%d) [%s][%dx%d@%d%s]disp:%d rd:%05x auib:%d cpb:%08d dpb:%02d/%d yaddr:%08lu ld:%d LR:%d err:%d fpa:%d mt:%d dt:%04d discont:%d pts:%d \t ts:%lld(0x%08llX) \n"
					,ui8VdcCh,pic_type,stDecBuf.width,stDecBuf.height,stDecBuf.framerate_num/stDecBuf.framerate_den,interace,si8FrameIndex,ui32feededaddr - stFrameInfo.ui32CurRdPtr
					,VES_AUIB_NumActive(gsVdcDb[ui8VdcCh].ui8VesCh),VES_CPB_GetUsedBuffer(gsVdcDb[ui8VdcCh].ui8VesCh),gsVdcDb[ui8VdcCh].ui8NumofDPBOccupied
					,gsVdcDb[ui8VdcCh].ui8DPBSize,stDecBuf.addr_y,stDecBuf.report,stDecBuf.multi_picture,stDecBuf.error_blocks,stDecBuf.frame_packing_arrangement
					,stDecBuf.vdo_map_type,GET_SIZE(VCoreInfo[ui8VCore].ui32RunningTime,TOP_HAL_GetGSTCC(),0xFFFFFFFF)/90,gsVdcDb[ui8VdcCh].ui8StcDiscontCounter,stDecBuf.pts,(SINT64)ui64Debug90kTS,ui64Debug90kTS);
				}

				//log_info("ch:%d \t PTS:%d \t STC:%d \n",ui8VdcCh,stDecBuf.pts,LQ_HAL_GetSTC(ui8VdcCh) & 0x0fffffff);
			}
			if(gsVdcDb[ui8VdcCh].ui8StcDiscontCounter>0){
				log_user2("ch:%d stc_discont occured! total:%d \n",ui8VdcCh,gsVdcDb[ui8VdcCh].ui32DiscontTotal++);
				stDecBuf.stc_discontinuity = 1;
				gsVdcDb[ui8VdcCh].ui8StcDiscontCounter--;
			}
			gsVdcDb[ui8VdcCh].ui8FrameFlags[si8FrameIndex]++;
		}
	}

	// FEEDED ENOUGH CHUNKS BUT BODA CANNOT DECODING OVER THRESHOLD
	ui32CurTime = TOP_HAL_GetGSTCC();
	ui32Diff = GET_SIZE(gsVdcDb[ui8VdcCh].ui32FeedStartTime, ui32CurTime, 0xFFFFFFFF);
	if(gsVdcDb[ui8VdcCh].ui8DPBSize!=VDC_INITIAL_DPB_SIZE && ui32Diff > VDC_FEEDING_WAIT_THRESHOLD
		&& gsVdcDb[ui8VdcCh].ui32FeededCounter > VDC_FEEDING_NUMBER_THERSHOLD){
		log_noti("ch:%d FeededTime(%d) exceeded over threshold (count:%d)",ui8VdcCh,ui32Diff,gsVdcDb[ui8VdcCh].ui32FeededCounter);
		stDecBuf.report += DECODED_REPORT_DECODE_FAILED;
		gsVdcDb[ui8VdcCh].ui32FeededCounter = 0;
		gsVdcDb[ui8VdcCh].ui32FeedStartTime = TOP_HAL_GetGSTCC();
	}

	spin_unlock_irqrestore(&_VDC_CheckBodaLock,flags);

	if(gsVdcDb[ui8VdcCh].decoded_q != NULL) {
		decoded_q_push(gsVdcDb[ui8VdcCh].decoded_q, &stDecBuf);
	}

	switch( pstDecResult->eNotiType )
	{
	case VDU_NOTI_SUCCESS:
	case VDU_NOTI_FRAME_SKIP:
		if( si8FrameIndex < 0 )
		{
			log_trace("ch:%d No Disp Index \n",ui8VdcCh);
		}
		gsVdcDb[ui8VdcCh].ui32FeededCounter = 0;
		gsVdcDb[ui8VdcCh].ui32FeedStartTime = TOP_HAL_GetGSTCC();
		break;
	case VDU_NOTI_DISPLAY:
		log_trace("ch:%d NOTI Display ISR, idx:%d \n",ui8VdcCh,si8FrameIndex);
		break;
	case VDU_NOTI_CPB_EMPTY:
	case VDU_NOTI_SKIP_EMPTY:
		log_trace("ch:%d CPB Empty ISR \n",ui8VdcCh);
		gsVdcDb[ui8VdcCh].bCPBEmpty = TRUE;
		_VDC_DecPostProc(ui8VdcCh,FALSE);
		break;
	case VDU_NOTI_DPB_FULL:
		log_trace("ch:%d dpb full,, disp:%d \n",ui8VdcCh,si8FrameIndex);
		gsVdcDb[ui8VdcCh].bWaitingClear = TRUE;
		gsVdcDb[ui8VdcCh].bPopped = FALSE;
		_VDC_DecPostProc(ui8VdcCh,FALSE);
		break;
	case VDU_NOTI_DECODING_ERROR:
		log_noti("ch:%d BODA Decoding Failed(disp:%d) \n",ui8VdcCh, si8FrameIndex);
		_VDC_DecPostProc(ui8VdcCh,FALSE);
		break;
	case VDU_NOTI_HEADER_NOT_FOUND:
		if(vdc_unlimit_retry==0 && !gsVdcDb[ui8VdcCh].bLive && gsVdcDb[ui8VdcCh].ui8SeqRetryCounter>=VDC_MAX_RETRY_COUNT_FOR_NOT_FOUND){
			log_warning("Ch:%d BODA Sequence Init Failed, Tried:%d \n",ui8VdcCh,gsVdcDb[ui8VdcCh].ui8SeqRetryCounter);
			gsVdcDb[ui8VdcCh].bSequenceInitFailed=TRUE;
			gsVdcDb[ui8VdcCh].ui8SeqRetryCounter=0;			
		}else {
			gsVdcDb[ui8VdcCh].ui8SeqRetryCounter++;
			log_noti("ch:%d BODA Header not found, SO Retry(%d) \n",ui8VdcCh,gsVdcDb[ui8VdcCh].ui8SeqRetryCounter);			
		}
		_VDC_DecPostProc(ui8VdcCh,FALSE);
		break;
	case VDU_NOTI_SEQ_INIT_FAIL:
		if(vdc_unlimit_retry==0 && !gsVdcDb[ui8VdcCh].bLive && gsVdcDb[ui8VdcCh].ui8SeqRetryCounter>=VDC_MAX_RETRY_COUNT_FOR_FAILED){
			log_warning("Ch:%d BODA Sequence Init Failed, Tried:%d \n",ui8VdcCh,gsVdcDb[ui8VdcCh].ui8SeqRetryCounter);
			gsVdcDb[ui8VdcCh].bSequenceInitFailed=TRUE;
			gsVdcDb[ui8VdcCh].ui8SeqRetryCounter=0;
		}else {
			gsVdcDb[ui8VdcCh].ui8SeqRetryCounter++;
			log_noti("ch:%d BODA Sequence Init Failed, SO Retry(%d) \n",ui8VdcCh,gsVdcDb[ui8VdcCh].ui8SeqRetryCounter);			
		}
		_VDC_DecPostProc(ui8VdcCh,FALSE);
		break;
	case VDU_NOTI_SUSPEND:
		log_trace("ch:%d noti suspended(disp:%d) \n",ui8VdcCh,si8FrameIndex);
		_VDC_DecPostProc(ui8VdcCh,TRUE);
		break;
	default:
		log_warning("ch:%d BODA Wrong Callback, Type is %d \n",ui8VdcCh,pstDecResult->eNotiType);
		_VDC_DecPostProc(ui8VdcCh,FALSE);
		break;
	}

	// any callback can updates running time
	VCoreInfo[ui8VCore].ui32RunningTime = TOP_HAL_GetGSTCC();

ERROR:
	return;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static void _FeedMain(UINT8 ui8VCore)
{
	UINT8 ui8VdcCh;	
	ULONG flags=0;
	VDU_RET_T eRetVal;
	VDU_AU_T stBodaAU = {0, };

	spin_lock_irqsave(&_VDC_Spinlock, flags);	

	// 1. select valid channel	
	ui8VdcCh = _VDC_FeedSellectChannel(ui8VCore);	
	if(ui8VdcCh == 0xFF){
		goto READY;
	}

	// 2. check waiting Clear queue condition
	if(gsVdcDb[ui8VdcCh].bWaitingClear == TRUE && gsVdcDb[ui8VdcCh].bFlushed == FALSE)
	{
		gsVdcDb[ui8VdcCh].bPopped = FALSE;		
		goto DECODING;
	}

	// 3. feeding AU	
	if(_VDC_PrepareFeed(ui8VdcCh,&stBodaAU) || gsVdcDb[ui8VdcCh].bRemainedData){
		goto FEEDING;
	} else {
		goto READY;
	}
FEEDING:
	spin_unlock_irqrestore(&_VDC_Spinlock, flags);
	eRetVal = VDU_FeedAu(gsVdcDb[ui8VdcCh].hBodaInst, &stBodaAU, &gsVdcDb[ui8VdcCh].stCBInfo);
	spin_lock_irqsave(&_VDC_Spinlock, flags);
	if(eRetVal != VDU_RET_OK){
		log_warning("ch:%d Feed AU Failed START:%x - SIZE:%x \n",ui8VdcCh,stBodaAU.ui32StartAddr-VES_CPB_GetBufferBaseAddr(gsVdcDb[ui8VdcCh].ui8VesCh),stBodaAU.ui32Size);
		goto READY;
	}		
DECODING:
	if(_VDC_PrepareDec(ui8VdcCh) == FALSE) 
		goto READY;
	spin_unlock_irqrestore(&_VDC_Spinlock, flags);	
	eRetVal = VDU_StartDecoding(gsVdcDb[ui8VdcCh].hBodaInst);
	if(eRetVal==VDU_RET_DPB_FULL)
	{
		log_warning("CH:%d DPB FULL: core state to BODA IDLE \n",ui8VdcCh);
		_VDC_DecideCoreReady(ui8VdcCh);
		gsVdcDb[ui8VdcCh].bWaitingClear = TRUE;
		gsVdcDb[ui8VdcCh].bPopped = FALSE;
	}
	else if(eRetVal != VDU_RET_OK)
	{
		log_warning("CH:%d DECODING FAILED: core state to BODA IDLE \n",ui8VdcCh);
		_VDC_DecideCoreReady(ui8VdcCh);
	}
	return;	

READY:
	VCoreInfo[ui8VCore].VCoreState = VDC_CODEC_STATE_READY;
	spin_unlock_irqrestore(&_VDC_Spinlock, flags);	
	return;
}

static void _VDC_InitializeDB(UINT8 ui8VdcCh)
{
	gsVdcDb[ui8VdcCh].state = VDC_NULL;
	gsVdcDb[ui8VdcCh].priv = NULL;
	gsVdcDb[ui8VdcCh].ui8VesCh = 0xFF;
	gsVdcDb[ui8VdcCh].ui8CodecType = 0xFF;
	gsVdcDb[ui8VdcCh].hBodaInst = VDU_INVALID_HANDLE;
	gsVdcDb[ui8VdcCh].decoded_q = NULL;
	gsVdcDb[ui8VdcCh].clear_q = NULL;

	_VDC_InitInnerDatas(ui8VdcCh);

	log_noti("ch:%d initialized db ok \n",ui8VdcCh);
}

static void _VDC_InitInnerDatas(UINT8 ui8VdcCh)
{
	int ch;

	gsVdcDb[ui8VdcCh].ui8DPBSize = VDC_INITIAL_DPB_SIZE;
	gsVdcDb[ui8VdcCh].ui8NumofDPBOccupied = 0;
	gsVdcDb[ui8VdcCh].ui8SeqRetryCounter = 0;
	gsVdcDb[ui8VdcCh].ui8DecRetryCounter = 0;
	gsVdcDb[ui8VdcCh].ui8StcDiscontCounter = 0;
	gsVdcDb[ui8VdcCh].ui8LROrder = 0;
	gsVdcDb[ui8VdcCh].ui8SamePtsCounter = 0;
	gsVdcDb[ui8VdcCh].ui8ScanMode = VDC_SKIP_NONE;

	gsVdcDb[ui8VdcCh].ui32DiscontTotal = 0;
	gsVdcDb[ui8VdcCh].ui32FeededCounter = 0;
	gsVdcDb[ui8VdcCh].ui32FeedStartTime = 0;
	gsVdcDb[ui8VdcCh].ui32prevPTS = 0;
	gsVdcDb[ui8VdcCh].si64WaitingTS = VDC_INVALID_TIMESTAMP;
	gsVdcDb[ui8VdcCh].si64prevTS = VDC_INVALID_TIMESTAMP;

	gsVdcDb[ui8VdcCh].bWaitingClear = FALSE;
	gsVdcDb[ui8VdcCh].bFlushed = FALSE;
	gsVdcDb[ui8VdcCh].bPopped = FALSE;
	gsVdcDb[ui8VdcCh].bLive = FALSE;
	gsVdcDb[ui8VdcCh].bFirstDecoded = FALSE;
	gsVdcDb[ui8VdcCh].bRemainedData = FALSE;
	gsVdcDb[ui8VdcCh].bIsDecoding = FALSE;
	gsVdcDb[ui8VdcCh].bSequenceInitFailed = FALSE;
	gsVdcDb[ui8VdcCh].bFieldCh = FALSE;
	gsVdcDb[ui8VdcCh].bFieldButOneValidTsCh = FALSE;

	gsVdcDb[ui8VdcCh].stCBInfo.ui32Pts = 0;
	gsVdcDb[ui8VdcCh].stCBInfo.ui32FeededPtr = 0;

	for(ch=0;ch<VDC_MAX_DPB_SIZE;ch++)
	{
		gsVdcDb[ui8VdcCh].ui8FrameFlags[ch] = 0;
		gsVdcDb[ui8VdcCh].si64TSInfo[ch] = VDC_INVALID_TIMESTAMP;
	}

	log_noti("ch:%d initialized inner datas ok \n",ui8VdcCh);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static UINT8 _VDC_FeedSellectChannel(UINT8 ui8VCore)
{
	UINT8 ui8Ch;
	UINT8 ui8VdcCh = 0xFF;
	UINT8 ui8selCount = 0;
	UINT8 ui8mostStarved = 0;
	UINT8 ui8starved = 0;
	BOOLEAN bFeedPossible[VDEC_NUM_OF_CHANNEL] = {0,};

	for(ui8Ch=0; ui8Ch<VDEC_NUM_OF_CHANNEL; ui8Ch++)
	{
		if(gsVdcDb[ui8Ch].state != VDC_PLAY || gsVdcDb[ui8Ch].bSequenceInitFailed)
			continue;

		// 2. Check usable Source(VES) Data
		if(gsVdcDb[ui8Ch].ui8VesCh != 0xFF && 
			VES_AUIB_NumActive(gsVdcDb[ui8Ch].ui8VesCh)==0)
		{
			if(gsVdcDb[ui8Ch].bRemainedData == FALSE){
				log_trace ("ch:%d NO AUIB.. auib %d, Used CPB %d\n",
						ui8Ch,
						VES_AUIB_NumActive(gsVdcDb[ui8Ch].ui8VesCh),
						VES_CPB_GetUsedBuffer(gsVdcDb[ui8Ch].ui8VesCh));
				// feed timer reset at starving condition
				gsVdcDb[ui8Ch].ui32FeedStartTime = TOP_HAL_GetGSTCC();
				continue;
			}else {
				// only retrying at DPB Full
				if(gsVdcDb[ui8Ch].bWaitingClear == TRUE){
					log_trace("ch:%d NO AUIB but remained data at BODA \n",ui8Ch);
				} else continue;
			}
		}

		// 3. Check usable Destination Queue or Buffer
		if(gsVdcDb[ui8Ch].ui8DPBSize != VDC_INITIAL_DPB_SIZE
			&& gsVdcDb[ui8Ch].decoded_q != NULL) // it means dpb alloced
		{
			UINT32 ui32NumDecodedQueue, ui32maxDecodedQSize;
			// 3-1. Check usable decoded queue
			ui32NumDecodedQueue = decoded_q_size(gsVdcDb[ui8Ch].decoded_q);
			ui32maxDecodedQSize = decoded_q_max_size(gsVdcDb[ui8Ch].decoded_q);
			if(ui32maxDecodedQSize <= ui32NumDecodedQueue)
			{
				log_trace("ch:%d, decoded q full, %d(%d) \n",
					ui8Ch, ui32NumDecodedQueue, ui32maxDecodedQSize);
				continue;
			}
			// 3-2. Check usable DPB
			if(_VDC_CheckUsableDPB(ui8Ch,TRUE)==TRUE)
			{
				ui8VdcCh=ui8Ch;
				bFeedPossible[ui8Ch] = TRUE;
				ui8selCount++;
			}else continue;
		}
		else {
			ui8VdcCh=ui8Ch;
			bFeedPossible[ui8Ch] = TRUE;
			ui8selCount++;
		}
	}
	// for multi channel sellect channel
	if(ui8selCount>1) {
		for(ui8Ch = 0; ui8Ch<VDEC_NUM_OF_CHANNEL; ui8Ch++){
			if(bFeedPossible[ui8Ch] == TRUE){
				ui8starved = gsVdcDb[ui8Ch].ui8DPBSize - gsVdcDb[ui8Ch].ui8NumofDPBOccupied;
				if(ui8starved > ui8mostStarved){
					log_trace("sel ch:%d prev ch starved:%d, cur ch starved:%d \n",
						ui8Ch, ui8mostStarved, ui8starved);
					ui8mostStarved = ui8starved;
					ui8VdcCh = ui8Ch;
				}
			}
		}
	}
	log_trace ("ch:%d selected\n", ui8VdcCh);
	return ui8VdcCh;
}

static BOOLEAN _VDC_CheckUsableDPB(UINT8 ui8VdcCh, BOOLEAN bPrint)
{
	S_DISPCLEARQ_BUF_T stClearQ;
	UINT32 idx;
	char temp[VDC_MAX_DPB_SIZE] = {0,};
	BOOLEAN bSpace = FALSE;
	gsVdcDb[ui8VdcCh].ui8NumofDPBOccupied = 0;

	if(gsVdcDb[ui8VdcCh].clear_q == NULL)
		goto ERROR;

	// display clear queue pop
	while( DISP_CLEAR_Q_Pop( gsVdcDb[ui8VdcCh].clear_q, &stClearQ) )
	{
		if(gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE && 
			VDU_ClearFrame(gsVdcDb[ui8VdcCh].hBodaInst, stClearQ.ui32FrameIdx & 0xFFFF) == VDU_RET_OK){
			gsVdcDb[ui8VdcCh].bPopped = TRUE;
			gsVdcDb[ui8VdcCh].ui8FrameFlags[stClearQ.ui32FrameIdx]--;
			log_debug("ch(%d) clear %d frame \n",ui8VdcCh, stClearQ.ui32FrameIdx);
		} else {
			log_warning("ch(%d) clear %d failed \n",ui8VdcCh, stClearQ.ui32FrameIdx);
		}
	}

	// 3-2. Check usable DPB
	for(idx = 0;idx<gsVdcDb[ui8VdcCh].ui8DPBSize;idx++)
	{
		if(gsVdcDb[ui8VdcCh].ui8FrameFlags[idx] == 1)
		{
			temp[idx] = '#';
			gsVdcDb[ui8VdcCh].ui8NumofDPBOccupied++;
		}
		else if(gsVdcDb[ui8VdcCh].ui8FrameFlags[idx] == 0)
		{
			temp[idx] = '-';
			bSpace = TRUE;
		}
		else
		{
			temp[idx] = (char)(((int)'0')+gsVdcDb[ui8VdcCh].ui8FrameFlags[idx]);
			gsVdcDb[ui8VdcCh].ui8NumofDPBOccupied++;
		}
	}

	if(bPrint){
		if(bSpace == FALSE)
		{
			log_trace("ch:%d dpb is full \n",ui8VdcCh);
		}
		else
		{
			log_debug("ch:%d dpb: %s waitclear?%d \n",ui8VdcCh,temp,gsVdcDb[ui8VdcCh].bWaitingClear);
		}
	}

	// first feeding started
	if(gsVdcDb[ui8VdcCh].ui8DPBSize == VDC_INITIAL_DPB_SIZE) bSpace = TRUE;

	// dpb full case, one ore more display clear queue popping needed
	if(gsVdcDb[ui8VdcCh].bWaitingClear == TRUE && gsVdcDb[ui8VdcCh].bPopped == FALSE) bSpace = FALSE;

	log_trace("ch:%d waitclear:%d popped:%d space:%d \n",ui8VdcCh,gsVdcDb[ui8VdcCh].bWaitingClear,gsVdcDb[ui8VdcCh].bPopped,bSpace);
ERROR:
	return bSpace;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static BOOLEAN _VDC_PrepareFeed(UINT8 ui8VdcCh, VDU_AU_T *stBodaAU)
{
#ifdef VDC_TS_USESKIPNOTI_MODE
	int index;
	int numofsaving;
	int numofsaved=0;	
#endif	
	UINT8 bSteppedPtsMargin;
	UINT64 ui64Debug90kTS=0;
	S_VES_AU_T stAUInfo = {0, };

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return FALSE;
	}

	if(gsVdcDb[ui8VdcCh].ui8VesCh != 0xFF && 
		VES_AUIB_NumActive(gsVdcDb[ui8VdcCh].ui8VesCh) > 0)
	{
		// 2. pop pdec auib
		if(VES_AUIB_Pop(gsVdcDb[ui8VdcCh].ui8VesCh, &stAUInfo))
		{
			switch(stAUInfo.eAuType){
				default: break;
				case AU_CMD_FLUSH:
					VDC_Flush(ui8VdcCh);
					return FALSE;
				case AU_CMD_SCANALL:
					VDC_SetSkipMode(ui8VdcCh,VDC_SKIP_NONE);
					return FALSE;
				case AU_CMD_SCANI:
					VDC_SetSkipMode(ui8VdcCh,VDC_SKIP_PB);
					return FALSE;
			}			
			// Making Callback Datas
			if(gsVdcDb[ui8VdcCh].bLive) {
					gsVdcDb[ui8VdcCh].stCBInfo.ui32Pts = stAUInfo.ui32PTS;
					gsVdcDb[ui8VdcCh].stCBInfo.ui32FeededPtr = stAUInfo.ui32AuEndAddr;
					// check stepped pts
					if(gsVdcDb[ui8VdcCh].ui32prevPTS == stAUInfo.ui32PTS){
						gsVdcDb[ui8VdcCh].ui8SamePtsCounter++;
					} else {
						gsVdcDb[ui8VdcCh].ui8SamePtsCounter=0;
					}
					bSteppedPtsMargin = gsVdcDb[ui8VdcCh].bFieldCh?2:1;
					if(gsVdcDb[ui8VdcCh].ui8SamePtsCounter >= bSteppedPtsMargin)
						gsVdcDb[ui8VdcCh].stCBInfo.ui32Pts = VDC_UNKNOWN_PTS;
			}
			else{
				gsVdcDb[ui8VdcCh].stCBInfo.ui32Pts = stAUInfo.ui32PTS;
				gsVdcDb[ui8VdcCh].stCBInfo.ui32FeededPtr = stAUInfo.ui32AuEndAddr;
				gsVdcDb[ui8VdcCh].stCBInfo.ui64Ts = stAUInfo.ui64TimeStamp;				
#ifdef VDC_TS_USESKIPNOTI_MODE
				// if 1 AU Feeding, ts pool update
				// Field File play, save all timestamps.
				// Update Feed Ts Pool When Feeding
				// save current AU information to unused pool
				// MVC case save same timestamp twice
				numofsaving = (gsVdcDb[ui8VdcCh].ui8CodecType==VDC_CODEC_H264_MVC)?2:1;
				if((SINT64)stAUInfo.ui64TimeStamp <= 0 && gsVdcDb[ui8VdcCh].bFieldCh) {
					log_noti("ch:%d this channel is field but has one valid ts \n",ui8VdcCh);
					gsVdcDb[ui8VdcCh].bFieldButOneValidTsCh = TRUE;						
				}
				else if((SINT64)stAUInfo.ui64TimeStamp >= 0 || gsVdcDb[ui8VdcCh].bFieldCh)
				{					
					ui64Debug90kTS = stAUInfo.ui64TimeStamp*9;
					do_div (ui64Debug90kTS, 100000);
					
					for(index=0; index<VDC_MAX_DPB_SIZE; index++)
					{
						if(gsVdcDb[ui8VdcCh].si64TSInfo[index] == VDC_INVALID_TIMESTAMP)
						{
							log_user1("ch:%d detect valid TS, so save %lld (%lld) at %d \n",ui8VdcCh,stAUInfo.ui64TimeStamp,ui64Debug90kTS,index);
							gsVdcDb[ui8VdcCh].si64TSInfo[index] = stAUInfo.ui64TimeStamp;
							numofsaved++;
							if(numofsaving == numofsaved) break;
						}
						if(index == VDC_MAX_DPB_SIZE-1){
							gsVdcDb[ui8VdcCh].si64TSInfo[0] = stAUInfo.ui64TimeStamp;
						}	
					}	
				}				
			}
#endif
#ifdef VDC_TS_USEDECNOTI_MODE
				if((SINT64)stAUInfo.ui64TimeStamp >= 0) {
					gsVdcDb[ui8VdcCh].si64WaitingTS = stAUInfo.ui64TimeStamp;
				}
			}
#endif
			if(stAUInfo.ui32AUPaircheck) gsVdcDb[ui8VdcCh].ui8StcDiscontCounter++;

			stBodaAU->ui32StartAddr = stAUInfo.ui32AuStartAddr;
			stBodaAU->ui32Size = GET_SIZE(stAUInfo.ui32AuStartAddr, stAUInfo.ui32AuEndAddr, VES_CPB_GetBufferSize(gsVdcDb[ui8VdcCh].ui8VesCh));
			
			log_debug("ch:%d Feed AU Success START:%x - END:%x SIZE:%d TYPE:%d PTS:%d PTS_Diff:%d TS:%lld 90KTS:%lld \n",ui8VdcCh,stBodaAU->ui32StartAddr-VES_CPB_GetBufferBaseAddr(gsVdcDb[ui8VdcCh].ui8VesCh),stAUInfo.ui32AuEndAddr-VES_CPB_GetBufferBaseAddr(gsVdcDb[ui8VdcCh].ui8VesCh),stBodaAU->ui32Size,stAUInfo.eAuType,gsVdcDb[ui8VdcCh].stCBInfo.ui32Pts,stAUInfo.ui32PTS-gsVdcDb[ui8VdcCh].ui32prevPTS,stAUInfo.ui64TimeStamp,ui64Debug90kTS);
			//log_info("AUIB:%x-%x(size:%d)(ts:%llu) \n",stAUInfo.ui32AuStartAddr,stAUInfo.ui32AuEndAddr,stAUInfo.ui32AuSize,stAUInfo.ui64TimeStamp);
			feeddump_dump(gsVdcDb[ui8VdcCh].ui8VesCh,
					ui8VdcCh,FEED_DATA,
					stBodaAU->ui32StartAddr,NULL,
					stBodaAU->ui32Size);
			
			if(stAUInfo.eAuType != AU_SEQUENCE_HEADER)
				gsVdcDb[ui8VdcCh].ui32prevPTS = stAUInfo.ui32PTS;
					 
			if(gsVdcDb[ui8VdcCh].ui32FeededCounter==0){
				gsVdcDb[ui8VdcCh].ui32FeedStartTime = TOP_HAL_GetGSTCC();
			}
			gsVdcDb[ui8VdcCh].ui32FeededCounter++;
			gsVdcDb[ui8VdcCh].ui8DecRetryCounter = 0;
			VES_AUIB_ConsumeOneAU(gsVdcDb[ui8VdcCh].ui8VesCh);
			VES_CPB_UpdateRdPtr(gsVdcDb[ui8VdcCh].ui8VesCh, stAUInfo.ui32AuEndAddr);

			return TRUE;
			
		}
	}
	else
	{
		if(gsVdcDb[ui8VdcCh].bRemainedData == FALSE) {
			log_trace("ch:%d NO AU TO FEED: vdc state to waiting au \n",ui8VdcCh);
		}else {
			gsVdcDb[ui8VdcCh].ui8DecRetryCounter++;
			if(gsVdcDb[ui8VdcCh].ui8DecRetryCounter == VDC_MAX_RETRY_COUNT_FOR_DECODING){
				gsVdcDb[ui8VdcCh].ui8DecRetryCounter = 0;
				gsVdcDb[ui8VdcCh].bRemainedData = FALSE;
				log_trace("ch:%d RETRY COUNTER REACHED MAX COUNT: stop retrying decode \n",ui8VdcCh);
			}
		}
	}
	return FALSE;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static BOOLEAN _VDC_PrepareDec(UINT8 ui8VdcCh)
{
	UINT8 ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;	

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);		
		return FALSE;
	}

	log_trace("CH:%d DECODING STARTED \n",ui8VdcCh);
	gsVdcDb[ui8VdcCh].bIsDecoding = TRUE;
	gsVdcDb[ui8VdcCh].bFlushed = FALSE;
	gsVdcDb[ui8VdcCh].bWaitingClear = FALSE;
	VCoreInfo[ui8VCore].VCoreState = VDC_CODEC_STATE_RUNNING;
	STC_TIMER_Start(ui8VCore);
	if(!gsVdcDb[ui8VdcCh].bLive) wake_up_all (&VCoreInfo[ui8VCore].wait_state_change);
	VCoreInfo[ui8VCore].ui32RunningTime = TOP_HAL_GetGSTCC();
	return TRUE;
}

static void _VDC_DecPostProc(UINT8 ui8VdcCh,BOOLEAN bSuspended)
{
	UINT8 ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Already Closed \n", ui8VdcCh);
		return;
	}

	_VDC_DecideCoreReady(ui8VdcCh);

	log_trace("ch:%d, BODA IDLE, suspend:%d, Feed by Decdone Interrupt \n",ui8VdcCh,bSuspended);
	if(bSuspended) return;
	_Scheduler(ui8VCore);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static void _VDC_Close(UINT8 ui8VdcCh)
{
	VDU_RET_T retVal;
	UINT8 ui8VCore;
	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;

	switch(ui8VCore)
	{
	case VDC_CORE_BODA950:
		if(gsVdcDb[ui8VdcCh].hBodaInst != VDU_INVALID_HANDLE) {
			retVal = VDU_Close(gsVdcDb[ui8VdcCh].hBodaInst);
			if( retVal == VDU_RET_OK){
				_VDC_DecideCoreReady(ui8VdcCh);
			}
			else {
				log_warning("ch:%d Boda Closing Failed:%d \n",ui8VdcCh, retVal);
			}
		}
		break;
	default:
		log_error("ch:%d Not Support Core:%d \n",ui8VdcCh, ui8VCore);
		break;
	}	

	// vdec core state
	if(VCoreInfo[ui8VCore].ui8UseNum>0)
	{
		VCoreInfo[ui8VCore].ui8UseNum --;
	}
	else
	{
		log_warning("ch:%d Num of used Core is Zero (%d - %d) \n"
			, ui8VdcCh, ui8VCore
			, VCoreInfo[ui8VCore].ui8UseNum);
		VCoreInfo[ui8VCore].ui8UseNum = 0;
	}

	_VDC_InitializeDB(ui8VdcCh);

	log_noti("ch:%d closed, remained:%d \n",ui8VdcCh,VCoreInfo[ui8VCore].ui8UseNum);

	if(VCoreInfo[ui8VCore].ui8UseNum==0)
	{
		VCoreInfo[ui8VCore].VCoreState = VDC_CODEC_STATE_NULL;
		STC_TIMER_Stop();
		log_noti("ch:%d all Channel is NULL State - Intr Clear \n", ui8VdcCh);
	}
}

static UINT64 _VDC_DecideTS(UINT8 ui8VdcCh)
{
	int index;
	long long ts = LLONG_MAX;
	int mintsidx = 0;

	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL || gsVdcDb[ui8VdcCh].state < VDC_PLAY)
	{
		log_warning("ch:%d Wrong Channel \n", ui8VdcCh);
		goto ERROR;
	}

	// timestamp matching
	for(index=0; index<VDC_MAX_DPB_SIZE; index++)
	{
		if(gsVdcDb[ui8VdcCh].si64TSInfo[index] == VDC_INVALID_TIMESTAMP) continue;

		log_user1("ch:%d index:%d timestamp:%lld \n",ui8VdcCh,index,(SINT64)gsVdcDb[ui8VdcCh].si64TSInfo[index]);

		if(gsVdcDb[ui8VdcCh].si64TSInfo[index] >= 0 &&
			gsVdcDb[ui8VdcCh].si64TSInfo[index] < ts){
				mintsidx = index;
				ts = gsVdcDb[ui8VdcCh].si64TSInfo[index];
			}
	}
	if(ts == LLONG_MAX) ts = VDC_INVALID_TIMESTAMP;
	else{
		if(gsVdcDb[ui8VdcCh].si64prevTS > ts) {
			log_user1("reversed timestamp : %lld -> %lld",gsVdcDb[ui8VdcCh].si64prevTS, ts);
			gsVdcDb[ui8VdcCh].si64prevTS = ts;
		}
		else {
			gsVdcDb[ui8VdcCh].si64prevTS = ts;
			gsVdcDb[ui8VdcCh].si64TSInfo[mintsidx] = VDC_INVALID_TIMESTAMP;
			log_user1("cleared ts info (%d) \n",mintsidx);		
		}		
	}
ERROR:
	return ts;
}

static void _VDC_DecideCoreReady(UINT8 ui8VdcCh)
{
	ULONG flags=0;
	UINT8 ui8VCore;
	if(ui8VdcCh >= VDEC_NUM_OF_CHANNEL)
	{
		log_warning("ch:%d Wrong channel \n", ui8VdcCh);
		return;
	}
	ui8VCore = gsVdcDb[ui8VdcCh].ui8Core;
	spin_lock_irqsave(&_VDC_Spinlock, flags);
	if(VCoreInfo[ui8VCore].VCoreState == VDC_CODEC_STATE_RUNNING && gsVdcDb[ui8VdcCh].bIsDecoding == TRUE)
	{
		gsVdcDb[ui8VdcCh].bIsDecoding = FALSE;
		VCoreInfo[ui8VCore].VCoreState = VDC_CODEC_STATE_READY;
		STC_TIMER_Stop();
		if(!gsVdcDb[ui8VdcCh].bLive) wake_up_all (&VCoreInfo[ui8VCore].wait_state_change);
	}
	spin_unlock_irqrestore(&_VDC_Spinlock, flags);
}

#ifdef USE_ZEROPADDING_DETECT
#define PADDING_SIZE_MAX 0x100
static BOOLEAN _VDC_IsZeroPadded(UINT8 ui8VdcCh, UINT32 ui32Start, UINT32 ui32End)
{
	UINT8 idx;
	static UINT8 tempBuf[PADDING_SIZE_MAX]={0,};
	UINT8 size = GET_SIZE(ui32Start,ui32End,VES_CPB_GetBufferSize(gsVdcDb[ui8VdcCh].ui8VesCh));
	BOOLEAN bNonzeroDetected=TRUE;

	if(size>PADDING_SIZE_MAX) {
		ui32Start = ui32End - PADDING_SIZE_MAX;
		size=(UINT8)PADDING_SIZE_MAX;
	}

	if(VES_CPB_Read(gsVdcDb[ui8VdcCh].ui8VesCh, ui32Start, size, tempBuf)){
		for(idx=0;idx<size; idx++)
		{
			log_user1("idx:%d , val:%2x \n",idx, tempBuf[idx]);
			if(tempBuf[idx] != 0)
			{
				bNonzeroDetected = FALSE;
				break;
			}
		}
		log_user1("ch:%d start:%08x end:%08x zero_padded:%d \n",ui8VdcCh,ui32Start,ui32End,bNonzeroDetected);
	}
	else bNonzeroDetected = FALSE;

	return bNonzeroDetected;
}
#endif

