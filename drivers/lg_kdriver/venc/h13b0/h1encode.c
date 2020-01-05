/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 2010 by LG Electronics Inc.
 
This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License 
version 2 as published by the Free Software Foundation.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details.
*/


/** @file
 *
 *  register api implementation for venc device of H13.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		jaeseop.so (jaeseop.so@lge.com)
 *  version		1.0
 *  date		2012.06.12
 *  note		Additional information.
 *
 *  @addtogroup lg1154_venc
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kthread.h>
#include <asm/io.h>			// for ioremap()/iounmap()
#include <linux/slab.h>
#include <linux/delay.h>	// for msleep()

#ifdef H1ENCODE_USE_TIMER_VSYNC
#include <linux/timer.h>	
#endif

#include "base_types.h"
#include "os_util.h"
#include "venc_kapi.h"
#include "../venc_cfg.h"
#include "../venc_drv.h"

#include "venc_h13b0_regprep.h"
#include "h1encode.h"

#ifdef VENC_HXENC_BUILTIN
#include "hxenc_api.h"
#else
#include "h1encode_wrapper.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef H1ENCODE_USE_LOCK
#define H1ENCODE_LOCK()				spin_lock(&h1enc_lock)
#define H1ENCODE_UNLOCK()			spin_unlock(&h1enc_lock)
#else
#define H1ENCODE_LOCK()
#define H1ENCODE_UNLOCK()
#endif

#ifdef H1ENCODE_DEBUG_AUI_SEQ
#define SEQ_LOCK()					spin_lock(&h1enc_lock_seq)
#define SEQ_UNLOCK()				spin_unlock(&h1enc_lock_seq)
#else
#define SEQ_LOCK()					/* NOP */
#define SEQ_UNLOCK()				/* NOP */
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#if 0
int hx280enc_init(unsigned int, unsigned int);
int hx280enc_cleanup(void);
#endif

// H.246
H1ENCODE_API_T *H264Alloc( void );
void H264Release(H1ENCODE_API_T * pstEncoder);

// VP8
H1ENCODE_API_T *VP8Alloc( void );
void VP8Release(H1ENCODE_API_T * pstEncoder);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
H1ENCODE_T 			gH1Encode;
extern LX_VENC_MEM_CFG_S_T *gpstVencMemConfig;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int H1EncodeMemoryInit( void );
static int H1EncodeMemoryCleanup( void );
static int H1EncodeRegisterInit( u32 regPREPBase, u32 regPREPSize );
static int H1EncodeRegisterCleanup( void );
static int H1EncodeTask( void* pParam );
static void H1EncodeReset( void );
static void H1EncodeCheckTime( H1ENCODE_T *pstEncode, u32 time );
static void H1EncodeCheckBitrate( H1ENCODE_T *pstEncode, u32 streamSize );
static int H1EncodeWaitDoneTimeout( int timeout );

#if 0
static u32 _ConvertFrameRate( LX_VENC_ENC_FRAME_RATE_T eFrameRate );
#endif

static void _InterruptEnable( void );
static void _InterruptDisable( void );
static void _InterruptEnableVsync( BOOLEAN enable );
static void _VsyncWait( void );
static int _EventWait( H1ENCODE_EVENT_T event, int timeout );
static void _EventPost( H1ENCODE_EVENT_T event );

#ifdef H1ENCODE_ENABLE_DELAYED_ENCODING
static void _EncodeStartPost( void );
#endif

static void H1EncodeVsyncHandler( unsigned long temp );

#ifdef H1ENCODE_UNUSE_ENCODE_THREAD
static void H1EncodeEncodeHandler( unsigned long temp );
DECLARE_TASKLET( VENC_TASKLET_VSYNC, H1EncodeEncodeHandler, 0 );
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static volatile VENC_H13_REG_PREP_T *gpRegVENCPREP;
static volatile VENC_H13_REG_PREP_T *gpRealRegVENCPREP;
static wait_queue_head_t 	wqEncodeVsync;
static wait_queue_head_t 	wqEncodeDone;
#ifdef H1ENCODE_ENABLE_DELAYED_ENCODING
static wait_queue_head_t 	wqEncodeStart;
#endif

static int	eventEncodeDoneWakeup;

static struct task_struct *g_pstH1EncodeTask = NULL;
static H1ENCODE_OUTPUT_STATUS_T	gstOutputStatus;

#ifdef H1ENCODE_USE_LOCK
DEFINE_SPINLOCK(h1enc_lock);
#endif

#ifdef H1ENCODE_DEBUG_AUI_SEQ
DEFINE_SPINLOCK(h1enc_lock_seq);
static int gNextAUISeq = 0;
#endif

#ifdef H1ENCODE_USE_TIMER_VSYNC
struct timer_list encode_timer;
#endif

static int	encode_count = 0;

static OS_EVENT_T	gstEventH1;

#ifdef H1ENCODE_CHECK_INTERLACED_INPUT
static H1ENCODE_FRAME_TYPE_T _prevFrameType;
#endif

#ifdef H1ENCODE_ENABLE_SCD
H1ENCODE_ENC_PARAMS_T *pstEncParamsPrev = NULL;
#endif

#ifdef H1ENCODE_ENABLE_DELAYED_ENCODING
UINT32 maxDelayedTime;
#endif

#ifdef H1ENCODE_USE_LOGFILE
struct timeval _irqTime;
#endif

static UINT32 encodedCountBeforeDiscard;

#ifdef DH1ENCODE_DEBUG_MEM_LEAK
static atomic_t encparams_count = ATOMIC_INIT( 0 );
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/

////////////////////////////////////////////////////////////////////////////////
//
//	Stream Dump
//
////////////////////////////////////////////////////////////////////////////////

#if defined(H1ENCODE_DEBUG_DUMP)

static OS_FILE_T dump_file;
static BOOLEAN	isDumpOpened = FALSE;

static void H1EncodeSaveStream(u32* buf, u32 size)
{
	if ( !isDumpOpened )
	{
		char filepath[100];

		if (gH1Encode.outputType == LX_VENC_ENCODE_TYPE_VP8)
		{
			sprintf(filepath, "h1enc_dump.vp8");
		}
		else
		{
			sprintf(filepath, "h1enc_dump.264");
		}

		if ( RET_OK != OS_OpenFile( &dump_file, filepath, O_CREAT|O_TRUNC|O_RDWR|O_LARGEFILE, 0666 ) )
		{
			return;
		}

		isDumpOpened = TRUE;
	}

#if 0
	if(endian == 1)
	 {
		 u32 i = 0, words = (size + 3) / 4;

		 while(words)
		 {
			 u32 val = strmbuf[i];
			 u32 tmp = 0;

			 tmp |= (val & 0xFF) << 24;
			 tmp |= (val & 0xFF00) << 8;
			 tmp |= (val & 0xFF0000) >> 8;
			 tmp |= (val & 0xFF000000) >> 24;
			 strmbuf[i] = tmp;
			 words--;
			 i++;
		 }

	 }
#endif

	OS_WriteFile( &dump_file, (char *)buf, size );

	VENC_DEBUG("[SAVESTRM] Addr: 0x%08x, Size: 0x%08x\n", (u32)buf, size);

}

static void H1EncodeDumpStop( void )
{
	if ( isDumpOpened )
	{
		OS_CloseFile( &dump_file );
		isDumpOpened = FALSE;
	}
}

#endif

#ifdef H1ENCODE_USE_LOGFILE
static OS_FILE_T _logFile;

int _LOG_Write( const char * format, ... )
{
	int len;
	char buf[128];
	va_list args;

	va_start(args, format);
	len = snprintf(buf, sizeof(buf), format, args);
	va_end(args);

	if ( RET_OK != OS_OpenFile( &_logFile, LOGFILE_NAME, O_CREAT|O_APPEND|O_LARGEFILE, 0666 ) )
	{
		return RET_ERROR;
	}

	len = OS_WriteFile( &_logFile, (char *)buf, len );

	OS_CloseFile( &_logFile );

	return len;
}

int _LOG_WriteTime( struct timeval *pstTime )
{
	int len = 0;
	struct timeval curTime;

	if ( pstTime != NULL )
	{
		curTime = *pstTime;
	}
	else
	{
		do_gettimeofday(&curTime);
	}

#if 0
	len = _LOG_Write( "%lu.%06lu,", curTime.tv_sec, curTime.tv_usec );
#else
	char buf[128];

	len = snprintf(buf, sizeof(buf), "%lu.%06lu,", curTime.tv_sec, curTime.tv_usec );

	if ( RET_OK != OS_OpenFile( &_logFile, LOGFILE_NAME, O_CREAT|O_APPEND|O_LARGEFILE, 0666 ) )
	{
		return RET_ERROR;
	}

	len = OS_WriteFile( &_logFile, (char *)buf, len );

	OS_CloseFile( &_logFile );
#endif

	return len;
}

#else
#define H1ENCODE_LOG( format, args... )
#endif

////////////////////////////////////////////////////////////////////////////////
//
//	Memory Allocator
//
////////////////////////////////////////////////////////////////////////////////

#define H1ENCODE_USE_ENCPARAMS_KMALLOC

#ifndef H1ENCODE_USE_ENCPARAMS_KMALLOC
#define H1ENCODE_ENCPARAM_LIST_SIZE	16
static H1ENCODE_ENC_PARAMS_T *_EncParamList[H1ENCODE_ENCPARAM_LIST_SIZE];
static BOOLEAN _EncParamStatus[H1ENCODE_ENCPARAM_LIST_SIZE];
#endif

static void _EncParamInit( void )
{
#ifndef H1ENCODE_USE_ENCPARAMS_KMALLOC	
	int i;

	for ( i = 0; i < H1ENCODE_ENCPARAM_LIST_SIZE; i++ )
	{
		_EncParamList[i] = (H1ENCODE_ENC_PARAMS_T *)kmalloc( sizeof(H1ENCODE_ENC_PARAMS_T), GFP_KERNEL );
		_EncParamStatus[i] = FALSE;
	}
#else
	// NOP
#endif
}

static void _EncParamFinal( void )
{
#ifndef H1ENCODE_USE_ENCPARAMS_KMALLOC
	int i;

	for ( i = 0; i < H1ENCODE_ENCPARAM_LIST_SIZE; i++ )
	{
		if ( _EncParamList[i] != NULL )
		{
			kfree( _EncParamList[i] );
			_EncParamList[i] = NULL;
			_EncParamStatus[i] = TRUE;
		}
	}
#else
	// NOP
#endif
}

static H1ENCODE_ENC_PARAMS_T * _EncParamAlloc( void )
{
#ifndef H1ENCODE_USE_ENCPARAMS_KMALLOC
	int i;

	for ( i = 0; i < H1ENCODE_ENCPARAM_LIST_SIZE; i++ )
	{
		if ( _EncParamStatus[i] == FALSE )
		{
			_EncParamStatus[i] = TRUE;
			memset( _EncParamList[i], 0x0, sizeof(H1ENCODE_ENC_PARAMS_T) );
			return _EncParamList[i];
		}
	}

	return NULL;
#else
	H1ENCODE_ENC_PARAMS_T * pstEncParams = NULL;
	int retry = 5;

	while ( pstEncParams == NULL && retry > 0 )
	{
		pstEncParams = kmalloc( sizeof(H1ENCODE_ENC_PARAMS_T), GFP_ATOMIC );
		retry--;
	}

#ifdef DH1ENCODE_DEBUG_MEM_LEAK
	atomic_inc( &encparams_count );
#endif

	return pstEncParams;
#endif
}

static void _EncParamFree( H1ENCODE_ENC_PARAMS_T * pstEncParams )
{
#ifndef H1ENCODE_USE_ENCPARAMS_KMALLOC
	int i;

	for ( i = 0; i < H1ENCODE_ENCPARAM_LIST_SIZE; i++ )
	{
		if ( _EncParamList[i] == pstEncParams )
		{
			_EncParamStatus[i] = FALSE;
			break;
		}
	}
#else
	if ( pstEncParams != NULL )
	{
		kfree( pstEncParams );

#ifdef DH1ENCODE_DEBUG_MEM_LEAK
		atomic_dec( &encparams_count );
#endif

	}
#endif
}

static void _EncParamClear( void )
{
#ifndef H1ENCODE_USE_ENCPARAMS_KMALLOC
	int i;

	for ( i = 0; i < H1ENCODE_ENCPARAM_LIST_SIZE; i++ )
	{
		if ( _EncParamList[i] != NULL )
		{
			_EncParamStatus[i] = FALSE;
		}
	}
#else
	// NOP
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
//	WorkQueue
//
////////////////////////////////////////////////////////////////////////////////

static int _WorkQInit( void )
{
	int ret = RET_OK;
	gH1Encode.venc_workqueue = create_singlethread_workqueue("VENC_WORK");

	if ( gH1Encode.venc_workqueue == NULL )
	{
		VENC_ERROR("workqueue allocation failed\n");
		ret = RET_ERROR;
	}

	return ret;
}

static int _WorkQCleanup( void )
{
	if ( gH1Encode.venc_workqueue == NULL )
	{
		VENC_ERROR("workqueue is NULL\n");
		return RET_ERROR;
	}

	destroy_workqueue( gH1Encode.venc_workqueue );

	return RET_OK;
}

static void _WorkQEncodeBH( struct work_struct *work )
{
	H1ENCODE_ENC_PARAMS_T *pstEncParams = (H1ENCODE_ENC_PARAMS_T *) work;
	u32 u32ESBCurrentStart = 0;
	u32 u32ESBStreamSize = 0;
	u32 streamBase;
	u32 streamSize;

	H1ENCODE_MEM_T	*pMemESB = NULL;
	H1ENCODE_MEM_T	*pMemAUI = NULL;

	struct list_head *pStreamList;

#ifdef H1ENCODE_ENABLE_COMBINE_FIELD_AUI
	static H1ENCODE_AUI_T	stTopFieldAUI;
#endif

	//TRACE_ENTER();

	if ( pstEncParams == NULL )
	{
		return;
	}

	pMemESB 	= pstEncParams->pMemESB;
	pMemAUI 	= pstEncParams->pMemAUI;
	pStreamList = pstEncParams->pStreamList;

	u32ESBCurrentStart = pMemESB->u32WriteOffset;

	streamBase = pMemESB->u32Phys + pMemESB->u32WriteOffset;
	streamSize = _StreamListCopy2Mem( pStreamList, pMemESB );

	if ( pMemESB->u32WriteOffset < u32ESBCurrentStart )
	{
		// wrap-around
		u32ESBStreamSize = pMemESB->u32WriteOffset + ( pMemESB->u32Size - u32ESBCurrentStart);
	}
	else
	{
		u32ESBStreamSize = pMemESB->u32WriteOffset - u32ESBCurrentStart;
	}

	// Create aui data & Notify encode done
	//if ( au_type == H1ENCODE_AU_TYPE_I || au_type == H1ENCODE_AU_TYPE_P )
	{
		H1ENCODE_AUI_T stAUI;
		stAUI.au_type = pstEncParams->au_type;
		stAUI.unit_size = streamSize;
		stAUI.unit_start = streamBase;
#ifdef H1ENCODE_DEBUG_SAVE_DURATION
		stAUI.index		= (pstEncParams->u32FrameIndex & 0xFF);	// 16bit
		stAUI.duration 	= pstEncParams->u32EncodingTime;
#else
		stAUI.index 	= pstEncParams->u32FrameIndex;
#endif
		stAUI.timestamp = pstEncParams->u32Timestamp;

		VENC_INFO("AUI={type:%d, size:%08x, base:%08x, index:%4d, stc:%08x, dur:%4d}\n", 
			pstEncParams->au_type, streamSize, streamBase, pstEncParams->u32FrameIndex, 
			pstEncParams->u32Timestamp, pstEncParams->u32EncodingTime);

#ifdef H1ENCODE_DEBUG_AUI_SEQ
		SEQ_LOCK();

		if ( pstEncParams->u32FrameIndex != gNextAUISeq )
		{
			VENC_WARN("H1ENCODE_DEBUG_AUI_SEQ: AUI Sequence is changed.\n");
		}

		gNextAUISeq = pstEncParams->u32FrameIndex + 1;

		SEQ_UNLOCK();
#endif

#ifdef H1ENCODE_ENABLE_COMBINE_FIELD_AUI
		if ( pstEncParams->interlaced == 1 && pstEncParams->tb == 0 )
		{
#ifdef H1ENCODE_USE_STRUCT_ASSIGNMENT
			stTopFieldAUI = stAUI;
#else
			memcpy( &stTopFieldAUI, &stAUI, sizeof(H1ENCODE_AUI_T) );
#endif
		}
		else
		{
			if ( pstEncParams->interlaced == 1 )
			{
				u32 unit_size = stAUI.unit_size;

#ifdef H1ENCODE_USE_STRUCT_ASSIGNMENT
				stAUI = stTopFieldAUI;
#else
				memcpy( &stAUI, &stTopFieldAUI, sizeof(H1ENCODE_AUI_T) );
#endif
				stAUI.unit_size += unit_size;
			}

			H1EncodeAUIWrite( pMemAUI, stAUI );

			//Should be calling H1EncodeUpdateStatus before calling EncodeNotifyDone.
			H1EncodeUpdateStatus( 1, streamSize, pstEncParams->u32EncodingTime );
			H1EncodeNotifyDone( pMemESB, pMemAUI );
		}
#else
		H1EncodeAUIWrite( pMemAUI, stAUI );

		// Should be calling H1EncodeUpdateStatus before calling EncodeNotifyDone.
		H1EncodeUpdateStatus( 1, streamSize, pstEncParams->u32EncodingTime );
		H1EncodeNotifyDone( pMemESB, pMemAUI );
#endif
		//bNeedAlign = FALSE;
	}

#if 0
	if ( FALSE )
	{
		u32 align = MROUND( pMemESB->u32WriteOffset, 16 );

		if (align - pMemESB->u32WriteOffset)
		{
			u32 paddingSize = align - pMemESB->u32WriteOffset;
			u32 start = pMemESB->u32Virt + pMemESB->u32WriteOffset;

			// clear padding data.
			memset ( (void *)start, 0x0, paddingSize );

			VENC_DEBUG("[ESBuffer][ALIGN] start: 0x%08x, end: 0x%08x, size: 0x%08x\n", start, align, paddingSize);
		}

		// 다음 데이터가 기록될 위치 조정
		pMemESB->u32WriteOffset = align;
	}
#endif

	// Free all related resource
	_StreamListFree( pStreamList );

	// work is pointer of H1ENCODE_ENC_PARAMS_T type.
	// it has been allocated by H1EncodeEncode function.
	// it should be freed by current function.
	_EncParamFree( pstEncParams );

	//TRACE_EXIT();

}

int _WorkQEnqueue( H1ENCODE_API_T *pstEncoder, H1ENCODE_ENC_PARAMS_T *pstEncParams )
{
	int ret = RET_OK;

	//TRACE_ENTER();

	if ( gH1Encode.venc_workqueue == NULL )
	{
		VENC_ERROR("workqueue is not created.\n");

		_EncParamFree( pstEncParams );

		ret = RET_ERROR;
	}
	else
	{
		if ( pstEncParams != NULL )
		{
			INIT_WORK( (struct work_struct *)pstEncParams, (void *)&_WorkQEncodeBH);
			ret = queue_work( gH1Encode.venc_workqueue, (struct work_struct *)pstEncParams );
		}
	}

	//TRACE_EXIT();

	return ret;

}

////////////////////////////////////////////////////////////////////////////////
//
//	Common
//
////////////////////////////////////////////////////////////////////////////////
void H1EncodeInitialize( void )
{
	u32 regBase, regSize;
	u32 regPREPBase, regPREPSize;

	TRACE_ENTER();

#ifdef H1ENCODE_ENABLE_SCD
	SET_VENC_CFG_CTRL_INDEX( VENC_CFG_CTRL_SCD );
#endif
	
#ifdef H1ENCODE_ENABLE_SAR
	SET_VENC_CFG_CTRL_INDEX( VENC_CFG_CTRL_SAR );
#endif

	if ( lx_chip_rev() >= LX_CHIP_REV(H13, B0) ) 
	{
		regBase = H13_VENC_BASE;
		regSize = 0x600;
	}
	else
	{
		VENC_ERROR("Not support chip_rev: 0x%08x", lx_chip_rev());
		return;
	}

	regPREPBase = regBase + 0x800;
	regPREPSize = 0x100;
	
	// memory mapping h1encoder h/w register.
#if 0
	hx280enc_init( regBase, regSize );
	MemallocInit( gpstVencMemConfig->uiH1EncBufBase, gpstVencMemConfig->uiH1EncBufBase + gpstVencMemConfig->uiH1EncBufSize);
#else

	H1EncodeHxencInit();
#endif

	H1EncodeReset();
	H1EncodeMemoryInit();
	H1EncodeRegisterInit( regPREPBase, regPREPSize );

	_EncParamInit();

	//H1EncodeSetEncodeType(LX_VENC_ENCODE_TYPE_VP8);
	//H1EncodeSetEncodeType(LX_VENC_ENCODE_TYPE_H264);

#if 0
	VENC_DEBUG("========== H1Encode Initialize ==========\n");
	VENC_DEBUG("u32OutBuffer Phys: 0x%08x, Virt: 0x%08x, Size: 0x%08x\n",
		gH1Encode.memOSB.u32Phys, gH1Encode.memOSB.u32Virt, gH1Encode.memOSB.u32Size);
	VENC_DEBUG("u32ESBuffer  Phys: 0x%08x, Virt: 0x%08x, Size: 0x%08x\n",
		gH1Encode.memESB.u32Phys, gH1Encode.memESB.u32Virt, gH1Encode.memESB.u32Size);
	VENC_DEBUG("u32AUIBuffer Phys: 0x%08x, Virt: 0x%08x, Size: 0x%08x\n",
		gH1Encode.memAUI.u32Phys, gH1Encode.memAUI.u32Virt, gH1Encode.memAUI.u32Size);
	VENC_DEBUG("=========================================\n");
#endif

	_InterruptEnable();
	_InterruptEnableVsync( FALSE );

	// Initialize for sync
	init_waitqueue_head( &wqEncodeVsync );

	// Initialize waitq for encoding done
	init_waitqueue_head( &wqEncodeDone );

#ifdef H1ENCODE_ENABLE_DELAYED_ENCODING
	init_waitqueue_head( &wqEncodeStart );
#endif

	OS_InitEvent( &gstEventH1 );

#ifdef H1ENCODE_USE_TIMER_VSYNC
	init_timer(&encode_timer);
#endif

#ifndef H1ENCODE_UNUSE_ENCODE_THREAD
	// Create kthread for encode task
	g_pstH1EncodeTask = kthread_run( &H1EncodeTask, NULL, "H1EncodeTask" );

#ifdef H1ENCODE_ENABLE_TASK_PRIORITY_HIGH
	{
		// set priority of kthread
		struct sched_param param = { 0 };
		param.sched_priority = H1ENCODE_SCHED_PRIORITY;
		if(sched_setscheduler(g_pstH1EncodeTask, SCHED_RR, &param) != 0)
		{
			VENC_ERROR("[%s:%u] Fail set priority of kthread\n", __F__, __L__);
		}
	}
#endif
#endif

	_WorkQInit();

#ifdef H1ENCODE_USE_PREP_STC
	VENC_PREP_RdFL(stc_ctrl);
	VENC_PREP_Wr01(stc_ctrl, select_stc_src, 0x0 ); // select source gstc0
	VENC_PREP_Wr01(stc_ctrl, select_stc, 0x2);		//stc value every de interrupt
	VENC_PREP_WrFL(stc_ctrl);
#endif

	TRACE_EXIT();
}

void H1EncodeFinalize( void )
{
	TRACE_ENTER();

#ifdef H1ENCODE_USE_TIMER_VSYNC
	del_timer_sync(&encode_timer);
#endif

	_InterruptDisable();

#if 0
	hx280enc_cleanup();
#else
	HXENC_Cleanup();
#endif

#ifndef H1ENCODE_UNUSE_ENCODE_THREAD
	if ( g_pstH1EncodeTask != NULL )
	{
		kthread_stop( g_pstH1EncodeTask );
	}
#endif

	H1EncodeMemoryCleanup();
	H1EncodeRegisterCleanup();

	_EncParamFinal();
	_WorkQCleanup();

	TRACE_EXIT();
}

void H1EncodeHxencInit( void )
{
	u32 regBase, regSize;

	if ( lx_chip_rev() >= LX_CHIP_REV(H13, B0) ) 
	{
		regBase = H13_VENC_BASE;
		regSize = 0x600;
	}
	else
	{
		VENC_ERROR("Not support chip_rev: 0x%08x", lx_chip_rev());
		return;
	}

	HXENC_Init( regBase, regSize);
	HXENC_MemallocInit( gpstVencMemConfig->uiH1EncBufBase, gpstVencMemConfig->uiH1EncBufBase + gpstVencMemConfig->uiH1EncBufSize);
}
EXPORT_SYMBOL( H1EncodeHxencInit );

static int H1EncodeRegisterInit( u32 regPREPBase, u32 regPREPSize )
{
	// Do ioremap for real & shadow registers
	gpRealRegVENCPREP = (VENC_H13_REG_PREP_T*)ioremap( regPREPBase, regPREPSize);
	gpRegVENCPREP = (VENC_H13_REG_PREP_T*)kzalloc( regPREPSize, GFP_KERNEL);

	if ( gpRealRegVENCPREP == MAP_FAILED || gpRegVENCPREP == NULL )
	{
		VENC_ERROR("Can't ioremap for registers.\n");
		return RET_ERROR;
	}

	return RET_OK;
}


static int H1EncodeRegisterCleanup( void )
{

	if ( gpRealRegVENCPREP )
	{
		iounmap( (void *)gpRealRegVENCPREP );
		gpRealRegVENCPREP = NULL;
	}

	if ( gpRegVENCPREP )
	{
		kfree( (void *)gpRegVENCPREP );
		gpRegVENCPREP = NULL;
	}

	return RET_OK;
}


static int H1EncodeMemoryInit( void )
{
	// Set DPB address & ioremap
	// !!! FIXME(IPC_SetVideoESBaseAddr, IPC_SetVideoESEndAddr)
	gH1Encode.memOSB.u32Phys = gpstVencMemConfig->uiDPBBase;
	gH1Encode.memOSB.u32Size = gpstVencMemConfig->uiDPBSize;
	gH1Encode.memOSB.u32Virt = (u32)ioremap( gH1Encode.memOSB.u32Phys, gH1Encode.memOSB.u32Size );

	if ( (void*)gH1Encode.memOSB.u32Virt == MAP_FAILED )
	{
		VENC_ERROR("Error ioremap: Output frame buffer.\n");
		goto RETURN_ERROR;
	}

	// Set ES Buffer address & ioremap
	gH1Encode.memESB.u32Phys = gpstVencMemConfig->uiESBufBase;
	gH1Encode.memESB.u32Size = gpstVencMemConfig->uiESBufSize;
	gH1Encode.memESB.u32Virt =(u32)ioremap( gH1Encode.memESB.u32Phys, gH1Encode.memESB.u32Size );

	// Clear ES Buffer
	memset( (void *)gH1Encode.memESB.u32Virt, 0x0, gH1Encode.memESB.u32Size );

	if ( (void*)gH1Encode.memESB.u32Virt == MAP_FAILED )
	{
		VENC_ERROR("Error ioremap: ES buffer.\n");
		goto RETURN_ERROR;
	}

	// Set AUI Buffer address & ioremap
	gH1Encode.memAUI.u32Phys = gpstVencMemConfig->uiAUIBufBase;
	gH1Encode.memAUI.u32Size = gpstVencMemConfig->uiAUIBufSize;
	gH1Encode.memAUI.u32Virt =(u32)ioremap( gH1Encode.memAUI.u32Phys, gH1Encode.memAUI.u32Size );

	// Clear AUI Buffer
	memset( (void *)gH1Encode.memAUI.u32Virt, 0x0, gH1Encode.memAUI.u32Size );

	if ( (void*)gH1Encode.memAUI.u32Virt == MAP_FAILED )
	{
		VENC_ERROR("Error ioremap: AUI buffer.\n");
		goto RETURN_ERROR;
	}

	// Set Input frame image buffer for thumbnail
	gH1Encode.memTFB.u32Phys = gpstVencMemConfig->uiScalerBase;
	gH1Encode.memTFB.u32Size = gpstVencMemConfig->uiScalerSize;
	gH1Encode.memTFB.u32Virt = (u32)ioremap( gH1Encode.memTFB.u32Phys, gH1Encode.memTFB.u32Size );

	if ( (void*)gH1Encode.memTFB.u32Virt == MAP_FAILED )
	{
		VENC_ERROR("Error ioremap: Input frame buffer.\n");
		goto RETURN_ERROR;
	}

	return RET_OK;

RETURN_ERROR:

	if ( (void*)gH1Encode.memOSB.u32Virt != MAP_FAILED )
	{
		iounmap( (void*)gH1Encode.memOSB.u32Virt );
	}

	if ( (void*)gH1Encode.memESB.u32Virt != MAP_FAILED )
	{
		iounmap( (void*)gH1Encode.memESB.u32Virt );
	}

	if ( (void*)gH1Encode.memAUI.u32Virt != MAP_FAILED )
	{
		iounmap( (void*)gH1Encode.memAUI.u32Virt );
	}

	if ( (void*)gH1Encode.memTFB.u32Virt != MAP_FAILED )
	{
		iounmap( (void*)gH1Encode.memTFB.u32Virt );
	}

	return RET_ERROR;

}

static int H1EncodeMemoryCleanup( void )
{

	if ( gH1Encode.memESB.u32Virt )
	{
		iounmap( (void *)gH1Encode.memESB.u32Virt );
		gH1Encode.memESB.u32Virt = 0;
	}

	if ( gH1Encode.memAUI.u32Virt )
	{
		iounmap( (void *)gH1Encode.memAUI.u32Virt );
		gH1Encode.memAUI.u32Virt = 0;
	}

	if ( gH1Encode.memOSB.u32Virt )
	{
		iounmap( (void *)gH1Encode.memOSB.u32Virt );
		gH1Encode.memOSB.u32Virt = 0;
	}

	if ( gH1Encode.memTFB.u32Virt )
	{
		iounmap( (void *)gH1Encode.memTFB.u32Virt );
		gH1Encode.memTFB.u32Virt = 0;
	}

	return RET_OK;
}

// Reset internal variables
static void H1EncodeReset( void )
{
//	gH1Encode.u32OutBufferRd = 0;
//	gH1Encode.u32OutBufferWr = 0;

	gH1Encode.memESB.u32ReadOffset = 0;
	gH1Encode.memESB.u32WriteOffset = 0;

	gH1Encode.memAUI.u32ReadOffset = 0;
	gH1Encode.memAUI.u32WriteOffset = 0;
	gH1Encode.u32AUIIndex = 0;

	gH1Encode.u32AUIStreamSize = 0;

	gH1Encode.u32EncodedFrames = 0;

	memset( gH1Encode.arEncodeTimes, 0x0, sizeof(gH1Encode.arEncodeTimes) );
	gH1Encode.u32EncodedTime = 0;
	gH1Encode.timeIndex = 0;

	memset( gH1Encode.arStreamSizes, 0x0, sizeof(gH1Encode.arStreamSizes) );
	gH1Encode.u32EncodedBitrate = 0;
	gH1Encode.sizeIndex = 0;

	gH1Encode.ui32CountFrameSkip = 0;

#ifdef H1ENCODE_CHECK_INTERLACED_INPUT
	#ifdef H1ENCODE_ENABLE_INTERLACED_BF
	_prevFrameType = LX_VENC_FRAME_TYPE_TOP;
	#else
	_prevFrameType = LX_VENC_FRAME_TYPE_BOTTOM;
	#endif

	if ( gH1Encode.pstEncoder != NULL )
	{
		gH1Encode.pstEncoder->bIsFirstFrame = TRUE;
	}
#endif
}


void H1EncodeSetEncodeType( LX_VENC_ENCODE_TYPE_T eEncodeType )
{
	if ( eEncodeType == LX_VENC_ENCODE_TYPE_H264 || eEncodeType == LX_VENC_ENCODE_TYPE_VP8 )
	{
		gH1Encode.outputType = eEncodeType;

		VENC_TRACE("Encode Type: %s\n", eEncodeType == LX_VENC_ENCODE_TYPE_H264 ? "H264" : "VP8");
	}
	else
	{
		VENC_ERROR("Wrong encode type.\n");
	}
}

int H1EncodeGetOutputBuffer( LX_VENC_ENC_OUTPUT_T *pstEncOutput )
{
	// Wait 100ms
	if ( H1EncodeWaitDoneTimeout( 100 ) != RET_OK )
	{
		return RET_ERROR;
	}

//	LOCK();

	pstEncOutput->ui32OffsetStart = gstOutputStatus.ui32ESRptr - gH1Encode.memESB.u32Phys;
	pstEncOutput->ui32OffsetEnd	 = gstOutputStatus.ui32ESWptr - gH1Encode.memESB.u32Phys;
	gstOutputStatus.ui32ESRptr = gstOutputStatus.ui32ESWptr;

	pstEncOutput->ui32AUIOffsetStart = gstOutputStatus.ui32AUIRptr - gH1Encode.memAUI.u32Phys;
	pstEncOutput->ui32AUIOffsetEnd	 = gstOutputStatus.ui32AUIWptr - gH1Encode.memAUI.u32Phys;
	gstOutputStatus.ui32AUIRptr = gstOutputStatus.ui32AUIWptr;

//	UNLOCK();

	return RET_OK;
}

u32 H1EncodeGetEncodedFrameCount( void )
{
	return gH1Encode.u32EncodedFrames;
}

u32 H1EncodeGetEncodeMsec( void )
{
	if ( gH1Encode.u32EncodedTime > 0 )
	{
		return gH1Encode.u32EncodedTime / 1000;
	}
	else
	{
		return 0;
	}
}

s32 H1EncodeGetResolution( u16 *pWidth, u16 *pHeight )
{
	if ( pWidth == NULL || pHeight == NULL )
	{
		return RET_ERROR;
	}

	if( gH1Encode.pstEncoder == NULL )
	{
		return RET_ERROR;
	}
	
	*pWidth = gH1Encode.pstEncoder->width;
	*pHeight = gH1Encode.pstEncoder->height;
	
	return RET_OK;
}

s32 H1EncodeSetFramerate( u32 framerate )
{
	u32		frameRateCode;
	u32 	frameRateDenom;
	u32		frameRateNum;

	switch( framerate )
	{
		case 25:
			frameRateCode = LX_VENC_FRAME_RATE_25HZ;
			frameRateDenom = 1000;
			frameRateNum = 25000;
			break;
			
		case 30:
			frameRateCode = LX_VENC_FRAME_RATE_30HZ;
			frameRateDenom = 1000;
			frameRateNum = 30000;
			break;

		case 50:
			frameRateCode = LX_VENC_FRAME_RATE_50HZ;
			frameRateDenom = 1000;
			frameRateNum = 50000;
			break;
			
		case 60:
			frameRateCode = LX_VENC_FRAME_RATE_60HZ;
			frameRateDenom = 1000;
			frameRateNum = 60000;
			break;
			
		default:
			frameRateCode = 0;
			frameRateDenom = 0;
			frameRateNum = 0;
			break;
	}
	
	gH1Encode.frameRateCode 	= frameRateCode;
	gH1Encode.frameRateDenom 	= frameRateDenom;
	gH1Encode.frameRateNum		= frameRateNum;

	return RET_OK;
}

u32 H1EncodeGetFramerate( void )
{
	u32 framerate;
	
	if ( gH1Encode.pstEncoder == NULL)
	{
		return 0;
	}

	if ( gH1Encode.pstEncoder->GetFrameRate != NULL )
	{
		gH1Encode.pstEncoder->GetFrameRate( gH1Encode.pstEncoder, &framerate );
	}
	else
	{
		return 0;
	}

	return framerate;
}

s32 H1EncodeSetBitrate( u32 targetBitrate )
{
	if ( gH1Encode.pstEncoder == NULL || gH1Encode.pstEncoder->SetBitrate == NULL )
	{
		gH1Encode.targetBitrate = targetBitrate;
	}
	else if ( gH1Encode.pstEncoder->SetBitrate != NULL )
	{
		gH1Encode.pstEncoder->SetBitrate( gH1Encode.pstEncoder, targetBitrate );
	}
	else
	{
		return RET_NOT_SUPPORTED;
	}

	return RET_OK;
}

u32 H1EncodeGetBitrate( void )
{
	if ( gH1Encode.u32EncodedBitrate > 0 )
	{
		return gH1Encode.u32EncodedBitrate;
	}
	else
	{
		return 0;
	}
}

s32 H1EncodeSetGOP( u32 gopLength )
{
	
	if ( gH1Encode.pstEncoder == NULL )
	{
		return RET_ERROR;
	}
	
	if ( gH1Encode.pstEncoder->SetGOPLength != NULL )
	{
		gH1Encode.pstEncoder->SetGOPLength( gH1Encode.pstEncoder, gopLength );
	}
	else
	{
		return RET_NOT_SUPPORTED;
	}

	return RET_OK;
}

u32 H1EncodeGetGOP( void )
{
	u32 gopLength = H1ENCODE_GOPLENGTH_DEFAULT;
	
	if ( gH1Encode.pstEncoder != NULL &&
		gH1Encode.pstEncoder->GetGOPLength != NULL )
	{
		gH1Encode.pstEncoder->GetGOPLength( gH1Encode.pstEncoder, &gopLength );
	}

	return gopLength;
}

s32 H1EncodeSetQPValue( u32 qp )
{
	if ( gH1Encode.pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	if ( gH1Encode.pstEncoder->SetQPValue != NULL )
	{
		gH1Encode.pstEncoder->SetQPValue( gH1Encode.pstEncoder, qp );
	}
	else
	{
		return RET_NOT_SUPPORTED;
	}

	return RET_OK;
}

u32 H1EncodeGetQPValue( void )
{
	u32 qp = 0;

	if ( gH1Encode.pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	if ( gH1Encode.pstEncoder->GetQPValue != NULL )
	{
		gH1Encode.pstEncoder->GetQPValue( gH1Encode.pstEncoder, &qp );
	}
	else
	{
		return RET_NOT_SUPPORTED;
	}

	return qp;	
}

s32 H1EncodeSetInputSource( LX_VENC_INPUT_SRC_T eInputSource )
{
	gH1Encode.eInputSource = eInputSource;

	return RET_OK;
}

void H1EncodeSetTime( u32 clock )
{
	// !!! FIXME (2012/05/31)
	// 시간 측정을 위해서 임시로 만든 레지스터이며, 기존 레지스터 명칭을 바꾸지 않음,
	VENC_PREP_RdFL(prep_wbase1);
	VENC_PREP_Wr(prep_wbase1, clock);
	VENC_PREP_WrFL(prep_wbase1);
}

u32 H1EncodeGetTime( void )
{
	u32 time;
	// !!! FIXME (2012/05/31)
	// 시간 측정을 위해서 임시로 만든 레지스터이며, 기존 레지스터 명칭을 바꾸지 않음,
	VENC_PREP_RdFL(prep_wbase1);

	time = VENC_PREP_Rd(prep_wbase1);
	time = time / ( H1ENCODE_HW_CLOCK / 1000000 );	// microsec (㎲)

	//VENC_DEBUG("encoding time: %d\n", time);

	return time;	// return microsec
}

static void H1EncodeCheckTime( H1ENCODE_T *pstEncode, u32 time )
{
	int i;
	int checkFrameCount = 10;
	u32 validValue = 0;
	u32 totalTime = 0;
	u32 avgTime = 0;
	u32 minTime = ~0;
	u32 maxTime = 0;

#if 0
	if ( checkFrameCount > H1ENCODE_CHECK_FRAME_MAX )
	{
		checkFrameCount = H1ENCODE_CHECK_FRAME_MAX;
	}
#endif

	pstEncode->arEncodeTimes[pstEncode->timeIndex] = time;
	pstEncode->timeIndex++;

	if ( pstEncode->timeIndex >= checkFrameCount )
	{
		u32 milliSec, microSec;

		for ( i = 0; i < checkFrameCount; i++ )
		{
			if (pstEncode->arEncodeTimes[i] > 0)
			{
				validValue++;
				totalTime += pstEncode->arEncodeTimes[i];

				minTime = MIN(minTime, pstEncode->arEncodeTimes[i]);
				maxTime = MAX(maxTime, pstEncode->arEncodeTimes[i]);
			}
		}

		if ( validValue > 0 )
		{
			avgTime = totalTime / validValue;

			milliSec = avgTime / 1000;
			microSec = avgTime % 1000;

#if 0
			VENC_DEBUG("Encoding Time: Last %d Frames AVG[%u.%03u ms] MIN[%u ms] MAX[%u ms]\n",
					checkFrameCount, milliSec, microSec, (minTime / 1000), (maxTime / 1000));
#endif

		}
		else
		{
			VENC_DEBUG("Encoding Time: No valid values\n");
		}

		pstEncode->timeIndex = 0;
	}
}

static void H1EncodeCheckBitrate( H1ENCODE_T *pstEncode, u32 streamSize )
{
	int i;
	int checkFrameCount = H1ENCODE_CHECK_FRAME_MAX;
	u32 validValue = 0;
	u32 totalStreamSize = 0;
	u32 bitrate;

	if ( pstEncode->pstEncoder == NULL )
	{
		return;
	}

	pstEncode->arStreamSizes[pstEncode->sizeIndex] = streamSize;

	// Calculate the sum of stream sizes
	for ( i = 0; i < checkFrameCount; i++ )
	{
		if (pstEncode->arStreamSizes[i] > 0)
		{
			validValue++;
			totalStreamSize += pstEncode->arStreamSizes[i];
		}
	}

	// Calculate the bitrate at latest n frames
	if ( validValue > 0 && pstEncode->pstEncoder->frameRateDenom > 0)
	{
		u32 tmp = totalStreamSize / validValue;
		tmp *= (u32) pstEncode->pstEncoder->frameRateNum;
		bitrate = (u32) (8 * (tmp / (u32) pstEncode->pstEncoder->frameRateDenom));

		pstEncode->u32EncodedBitrate = bitrate;

		//VENC_DEBUG("Bitrate: %d\n", bitrate);
	}

	// Set the next index
	pstEncode->sizeIndex++;

	if ( pstEncode->sizeIndex >= checkFrameCount )
	{
		pstEncode->sizeIndex = 0;
	}

}

void H1EncodeUpdateStatus( u32 frameCount, u32 streamSize, u32 encodingTime )
{
	gH1Encode.u32EncodedFrames += frameCount;
	gH1Encode.u32EncodedTime = encodingTime;

	//H1EncodeCheckTime( &gH1Encode, encodingTime );
	//H1EncodeCheckBitrate( &gH1Encode, streamSize );
}

int H1EncodeReadStatus( char *buffer )
{
	int len = 0;
	const static char *COMMAND_STATUS[4] = {
		"STOP",
		"STOP_PREPARE",
		"START",
		"START_PREPARE"
	};

	if ( buffer == NULL )
	{
		return 0;
	}

	len += sprintf( buffer + len, "#### VENC Status ####\n");
	if ( gH1Encode.eStatus < 4 )
	{
		len += sprintf( buffer + len, "Command [%s]\n", COMMAND_STATUS[gH1Encode.eStatus] );
	}

	if ( gH1Encode.eStatus == H1ENCODE_STATUS_TYPE_START &&  gH1Encode.pstEncoder != NULL )
	{
	 	H1ENCODE_API_T *pstEncoder = gH1Encode.pstEncoder;

		len += sprintf( buffer + len, "Input Source Type: %s\n", (gH1Encode.eInputSource == LX_VENC_INPUT_SRC_DTV) ? "DTV":"OTHERS" );
		len += sprintf( buffer + len, "Output Format Type: %s\n", (gH1Encode.outputType == LX_VENC_ENCODE_TYPE_H264) ? "H.264":"VP8" );
		len += sprintf( buffer + len, "Target Bitrate: %d Mbits/sec\n", gH1Encode.targetBitrate );
		len += sprintf( buffer + len, "Resolution: %d x %d, Framerate: %d/%d\n", pstEncoder->width, pstEncoder->height, pstEncoder->frameRateDenom, pstEncoder->frameRateNum);
		len += sprintf( buffer + len, "GOP Length: %d\n", pstEncoder->gopLength);
		
	#ifdef H1ENCODE_ENABLE_SAR
		len += sprintf( buffer + len, "SAR: %d:%d\n", pstEncoder->decWidth, pstEncoder->decHeight);
	#endif
	}
	len += sprintf( buffer + len, "\n");

	len += sprintf( buffer + len, "Buffer Status:\n");
	if ( gH1Encode.pstEncoder != NULL )
	{
		H1ENCODE_API_T *pstEncoder = gH1Encode.pstEncoder;

		len += sprintf( buffer + len, "\t ES Buffer: 0x%08X-0x%08X [0x%08X]\n", gH1Encode.memESB.u32Phys, gH1Encode.memESB.u32Phys+gH1Encode.memESB.u32Size, pstEncoder->memESB.u32WriteOffset );
		len += sprintf( buffer + len, "\tAUI Buffer: 0x%08X-0x%08X [0x%08X]\n", gH1Encode.memAUI.u32Phys, gH1Encode.memAUI.u32Phys+gH1Encode.memAUI.u32Size, pstEncoder->memAUI.u32WriteOffset );
	}
	else
	{
		len += sprintf( buffer + len, "\t ES Buffer: 0x%08X-0x%08X\n", gH1Encode.memESB.u32Phys, gH1Encode.memESB.u32Phys+gH1Encode.memESB.u32Size );
		len += sprintf( buffer + len, "\tAUI Buffer: 0x%08X-0x%08X\n", gH1Encode.memAUI.u32Phys, gH1Encode.memAUI.u32Phys+gH1Encode.memAUI.u32Size );
	}

	len += sprintf( buffer + len, "Vsync Status: Total[%d], Skip[%d]\n",  gH1Encode.ui32TotalVsync,  gH1Encode.ui32CountFrameSkip );
	len += sprintf( buffer + len, "\n");

#ifdef DH1ENCODE_DEBUG_MEM_LEAK
	extern atomic_t aui_count;
	extern atomic_t api_count;

	len += sprintf( buffer + len, "DEBUG Check MEM Leak:\n");
	len += sprintf( buffer + len, "\tENC PARAM COUNT: %d\n", encparams_count.counter);
	len += sprintf( buffer + len, "\t      API COUNT: %d\n", api_count.counter);
	len += sprintf( buffer + len, "\t      AUI COUNT: %d\n", aui_count.counter);
	len += sprintf( buffer + len, "\n");
#endif

	return len;
}

static u32 H1EncodeReadSTC( LX_VENC_TIMESTAMP_TYPE_T eTimestamp )
{
	u32 stc;
	
	switch( eTimestamp )
	{
		case LX_VENC_TIMESTAMP_PTS:
		{
			VENC_PREP_RdFL( info );
			stc = VENC_PREP_Rd( info );
		}
		break;
#ifdef H1ENCODE_USE_PREP_STC		
		case LX_VENC_TIMESTAMP_STC:
		{
			VENC_PREP_RdFL( stc );
			stc = VENC_PREP_Rd( stc );
		}
		break;
#endif
		case LX_VENC_TIMESTAMP_GSTC:
		default:
		{
			VENC_PREP_RdFL(vdec_gstcc0);
			VENC_PREP_Rd01(vdec_gstcc0, gstcc0, stc);
		}
		break;
	}

	return stc;

}

static void H1EncodeUpdateTimestamp( void )
{
#ifdef H1ENCODE_USE_VDEC_PTS
	if ( gH1Encode.eInputSource == LX_VENC_INPUT_SRC_DTV )
	{
		gH1Encode.u32CurrentPTS = H1EncodeReadSTC( LX_VENC_TIMESTAMP_PTS ) & 0x0FFFFFFF;	// use 28bits
	}
	else
#endif
	{
		gH1Encode.u32CurrentPTS = H1EncodeReadSTC( LX_VENC_TIMESTAMP_GSTC );
	}
}

u32 H1EncodeGetTimestamp( void )
{
	return gH1Encode.u32CurrentPTS;
}

#ifdef H1ENCODE_ENABLE_AUTO_RESTART
/**
 * Diff two H1ENCODE_PREP_STATUS_T value.
 *
 * @param pstPrepA first H1ENCODE_PREP_STATUS_T
 * @param pstPrepB second H1ENCODE_PREP_STATUS_T
 * @retrun 0: not chaged, non-zero: something chaged.
 */
static BOOLEAN H1EncodeDiffPREP( H1ENCODE_PREP_STATUS_T *pstPrepA, H1ENCODE_PREP_STATUS_T *pstPrepB )
{
	if ( pstPrepA == NULL || pstPrepB == NULL )
	{
		return TRUE;
	}

	if ( pstPrepA->inWidth != pstPrepB->inWidth )
	{
		return TRUE;
	}

	if ( pstPrepA->inHeight != pstPrepB->inHeight )
	{
		return TRUE;
	}

	if ( pstPrepA->yStride != pstPrepB->yStride )
	{
		return TRUE;
	}
	
	if ( pstPrepA->cStride != pstPrepB->cStride )
	{
		return TRUE;
	}
	
	if ( pstPrepA->frameType == LX_VENC_FRAME_TYPE_PROGRESSIVE && 
		pstPrepB->frameType != LX_VENC_FRAME_TYPE_PROGRESSIVE )
	{
		return TRUE;
	}
 	else if ( pstPrepA->frameType != LX_VENC_FRAME_TYPE_PROGRESSIVE &&
		pstPrepB->frameType == LX_VENC_FRAME_TYPE_PROGRESSIVE )
 	{
		return TRUE;
	}

	return FALSE; // size is not chagned.
}

#endif

#ifdef H1ENCODE_ENABLE_SAR
static BOOLEAN H1EncodeDiffPREP_SAR( H1ENCODE_PREP_STATUS_T *pstPrepA, H1ENCODE_PREP_STATUS_T *pstPrepB )
{
	if ( pstPrepA == NULL || pstPrepB == NULL )
	{
		return TRUE;
	}

	if ( pstPrepA->decWidth != pstPrepB->decWidth )
	{
		return TRUE;
	}
	
	if ( pstPrepA->decHeight != pstPrepB->decHeight )
	{
		return TRUE;
	}	

	return FALSE; // size is not chagned.
}
#endif

static void H1EncodeReadPREP(H1ENCODE_PREP_STATUS_T *pstPrepStatus)
{
	BOOLEAN _enableFlipTB = FALSE;
	
	// 사이즈, 포맷 정보를 PREP 레지스터에서 읽어옴.	 (DE/VDEC에서 기록하는 내용)
	u32 yBase, cBase;
	int inHeight, inWidth;
	int yStride, cStride;
	int frm_rate;
	H1ENCODE_FRAME_TYPE_T frameType;

#ifdef H1ENCODE_ENABLE_SAR	
	int decHeight, decWidth;
#endif

	if ( pstPrepStatus == NULL )
	{
		return;
	}

	// Frame base Address (Y)
	VENC_PREP_RdFL(y_addr);
	VENC_PREP_Rd01(y_addr, addr, yBase);

	// Frame base Address (CbCr)	
	VENC_PREP_RdFL(c_addr);
	VENC_PREP_Rd01(c_addr, addr, cBase);

	// Size
	VENC_PREP_RdFL(de_dsize);
	VENC_PREP_Rd02(de_dsize, vsize, inHeight, hsize, inWidth);

#ifdef H1ENCODE_ENABLE_SAR
	// SAR Infomation
	VENC_PREP_RdFL(decsize);
	VENC_PREP_Rd02(decsize, dec_vsize, decHeight, dec_hsize, decWidth);
#endif

	// Frame Type (Field/Frame)
	VENC_PREP_RdFL(pic_info);
	VENC_PREP_Rd01(pic_info, frm_struct, frameType);

	// Stride (Y/C)
	VENC_PREP_RdFL(y_stride);
	VENC_PREP_Rd01(y_stride, stride, yStride);
	VENC_PREP_RdFL(c_stride);
	VENC_PREP_Rd01(c_stride, stride, cStride);

	// Sequence Info
	VENC_PREP_RdFL(seqinfo);
	VENC_PREP_Rd01(seqinfo, frm_rate, frm_rate);

#ifdef H1ENCODE_DEBUG_SWAP_TB
	_enableFlipTB = TRUE;
#else
	_enableFlipTB = GET_VENC_CFG_CTRL_INDEX( VENC_CFG_CTRL_FLIP_TB );
#endif

	if ( _enableFlipTB )
	{
		if ( frameType == LX_VENC_FRAME_TYPE_TOP )
		{
			frameType = LX_VENC_FRAME_TYPE_BOTTOM;
		}
		else if ( frameType == LX_VENC_FRAME_TYPE_BOTTOM )
		{
			frameType = LX_VENC_FRAME_TYPE_TOP;
		}
	}

	pstPrepStatus->yBase = yBase;
	pstPrepStatus->cBase = cBase;

	pstPrepStatus->inWidth = inWidth;
	pstPrepStatus->inHeight = inHeight;
	pstPrepStatus->yStride = yStride;
	pstPrepStatus->cStride = cStride;
	pstPrepStatus->frameType = frameType;
	pstPrepStatus->frameRateCode = frm_rate;

#ifdef H1ENCODE_ENABLE_SAR
	pstPrepStatus->decWidth = decWidth;
	pstPrepStatus->decHeight = decHeight;
#endif

#if 0
	VENC_INFO("[PREP] width: %d, height: %d\n", inWidth, inHeight);
	VENC_INFO("[PREP] yStride: %d, cStride: %d\n", yStride, cStride);
	VENC_INFO("[PREP] frameType: %d\n", frameType);
#endif

	if ( inWidth == 0 || inHeight == 0 )
	{
		VENC_ERROR("Resolution error.\n");
		//return RET_ERROR;
	}

	if ( yStride == 0 || cStride == 0)
	{
		VENC_ERROR("Stride error.\n");
		//return RET_ERROR;
	}

	//return RET_OK;
}

static void H1EncodeUpdatePREP( void )
{
	H1ENCODE_PREP_STATUS_T stPrepStatus = {0};

	//memset( &stPrepStatus, 0x0, sizeof(H1ENCODE_PREP_STATUS_T) );

	// Read input frame infomation from PREP register (DE or VDEC writed)
	H1EncodeReadPREP( &stPrepStatus );

#ifdef H1ENCODE_ENABLE_AUTO_RESTART
	if ( H1EncodeDiffPREP( &gH1Encode.stPrepStatus, &stPrepStatus ) )
	{
		// if chagend input format (size, frame type, ... )
		// Restart encoding ( stop -> start )
	}
#endif

#ifdef H1ENCODE_ENABLE_SAR
	if ( H1EncodeDiffPREP_SAR( &gH1Encode.stPrepStatus, &stPrepStatus ) )
	{
		// NEED Modify
	}
#endif

#ifdef H1ENCODE_USE_STRUCT_ASSIGNMENT
	gH1Encode.stPrepStatus = stPrepStatus;
#else
	memcpy( &gH1Encode.stPrepStatus, &stPrepStatus, sizeof(H1ENCODE_PREP_STATUS_T) );
#endif

	_EventPost( H1ENCODE_EVENT_THUMBNAIL );
	
}

int H1EncodeGetFrameImage( LX_VENC_ENC_FRAME_IMAGE_T *pstFrameImage )
{
	int ret = RET_ERROR;

	if ( pstFrameImage == NULL )
	{
		return ret;
	}
	
	ret = _EventWait( H1ENCODE_EVENT_THUMBNAIL, 100 );
	
	if ( ret != RET_OK )
	{ 
		VENC_WARN("Event timeout!!!\n");
		ret = RET_ERROR;
	}
	else
	{
		u32 yBase = gH1Encode.stPrepStatus.yBase;
		u32 cBase = gH1Encode.stPrepStatus.cBase;
		u16 width = gH1Encode.stPrepStatus.inWidth;
		u16 height = gH1Encode.stPrepStatus.inHeight;
		u16 stride = gH1Encode.stPrepStatus.yStride;
		u32 size = width * stride;
		
		LX_VENC_ENC_FRAME_TYPE_T frameType = gH1Encode.stPrepStatus.frameType;

		void *dest, *pY, *pC;

		VENC_DEBUG("stPrepStatus={.yBase=%08x .cBase=%08x .inWidth=%d .inHeight=%d}\n",
			gH1Encode.stPrepStatus.yBase, gH1Encode.stPrepStatus.cBase,
			gH1Encode.stPrepStatus.inWidth, gH1Encode.stPrepStatus.inHeight);

		if ( yBase == 0 || cBase == 0 || width == 0 || height == 0 )
		{
			return RET_ERROR;
		}

		dest = (void *)gH1Encode.memTFB.u32Virt;
		if ( dest == (void *)-1 )
		{
			return RET_ERROR;
		}
		
		pY = ioremap( yBase, size );
		if ( pY == (void *)-1 )
		{			
			return RET_ERROR;
		}
		
		pC = ioremap( cBase, size );
		if ( pC == (void *)-1 )
		{
			iounmap( pY );

			return RET_ERROR;
		}

		if ( frameType == LX_VENC_ENC_FRAME_TYPE_PROGRESSIVE )
		{			
			UINT32 targetBase = (UINT32)dest;
			UINT32 sourceBase;
			char *cb, *cr;
			int i, j;

			int cbOffset = width * height;
			int crOffset = (width * height) + ((width * height) >> 2);
			
			sourceBase = (UINT32)pY;
			for ( i = 0; i < height; i++ )
			{
				memcpy( (void *)targetBase, (void *)sourceBase, width );

				targetBase += width;
				sourceBase += stride;
			}

			sourceBase = (UINT32)pC;
			cb = (char *)(dest + cbOffset);
			cr = (char *)(dest + crOffset);
			
			for ( i = 0; i < height / 2; i++ )
			{
				UINT32 srcOffset = i * stride;
				UINT32 tarOffset = i * (width / 2);
				
				for ( j = 0; j < width / 2; j ++ )
				{
					cb[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
					cr[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
				}
			}

			pstFrameImage->type = LX_VENC_ENC_FRAME_IMAGE_TYPE_420_PLANAR;
			pstFrameImage->ui32Size = width * height * 2;
			pstFrameImage->ui32Height = height;
			pstFrameImage->ui32Width = width;
			pstFrameImage->ui32Stride = width;
			pstFrameImage->ui32YPhyAdd = gH1Encode.memTFB.u32Phys;
			pstFrameImage->ui32UPhyAdd = gH1Encode.memTFB.u32Phys + cbOffset;
			pstFrameImage->ui32VPhyAdd = gH1Encode.memTFB.u32Phys + crOffset;

		}
		else if ( frameType == LX_VENC_ENC_FRAME_TYPE_TOP || frameType == LX_VENC_ENC_FRAME_TYPE_BOTTOM )
		{
			UINT32 targetBase = (UINT32)dest;
			UINT32 sourceBase;
			char *cb, *cr;
			int i, j;

			int cbOffset = width * height;
			int crOffset = (width * height) + ((width * height) >> 2);
			
			sourceBase = (UINT32)pY;
			for ( i = 0; i < height / 2; i++ )
			{
				memcpy( (void *)targetBase, (void *)sourceBase, width );
				memcpy( (void *)targetBase + width, (void *)sourceBase, width );

				targetBase += (width * 2);
				sourceBase += stride;
			}

			sourceBase = (UINT32)pC;
			cb = (char *)(dest + cbOffset);
			cr = (char *)(dest + crOffset);
			
			for ( i = 0; i < height / 4; i++ )
			{
				UINT32 srcOffset = i * stride;
				UINT32 tarOffset = i * 2 * (width / 2);
				
				for ( j = 0; j < width / 2; j ++ )
				{
					cb[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
					cr[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
				}

				tarOffset = i * 2 * (width / 2) + (width / 2);
				
				for ( j = 0; j < width / 2; j ++ )
				{
					cb[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
					cr[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
				}				
			}

			pstFrameImage->type = LX_VENC_ENC_FRAME_IMAGE_TYPE_420_PLANAR;
			pstFrameImage->ui32Size = width * height * 2;
			pstFrameImage->ui32Height = height;
			pstFrameImage->ui32Width = width;
			pstFrameImage->ui32Stride = width;
			pstFrameImage->ui32YPhyAdd = gH1Encode.memTFB.u32Phys;
			pstFrameImage->ui32UPhyAdd = gH1Encode.memTFB.u32Phys + cbOffset;
			pstFrameImage->ui32VPhyAdd = gH1Encode.memTFB.u32Phys + crOffset;
		}

		iounmap( pY );
		iounmap( pC );
	}

	return ret;
}

static int H1EncodeOpen( H1ENCODE_PREP_STATUS_T stPrepStatus )
{
	int ret = RET_ERROR;
	H1ENCODE_API_T * pstEncoder;

	TRACE_ENTER();

	if ( gH1Encode.pstEncoder != NULL )
	{
		// Already allocate encoder instance
		return RET_ERROR;
	}

	H1ENCODE_LOCK();

	if (gH1Encode.outputType == LX_VENC_ENCODE_TYPE_VP8)
	{
		gH1Encode.pstEncoder = VP8Alloc();
	}
	else
	{
		gH1Encode.pstEncoder = H264Alloc();
	}

	gH1Encode.ui32TotalVsync = 0;
#ifdef H1ENCODE_ENABLE_DROP_FIRST_FRAME		
	gH1Encode.remain_drop = H1ENCODE_DROP_FIRST_FRAME_COUNT;
#endif

	H1ENCODE_UNLOCK();
	
	pstEncoder = gH1Encode.pstEncoder;

	if ( pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	// Check function pointers
	if ( pstEncoder->SetMemOSB == NULL || pstEncoder->SetMemESB == NULL || pstEncoder->SetMemAUI == NULL )
	{
		VENC_ERROR("Memory setter function is NULL.\n");
		return RET_ERROR;
	}

	if ( pstEncoder->SetFrameType == NULL || pstEncoder->SetFrameSize == NULL || 
		pstEncoder->SetGOPLength == NULL || pstEncoder->SetFrameRate == NULL ||
		pstEncoder->SetBitrate == NULL )
	{
		VENC_ERROR("Config setter function is NULL.\n");
		return RET_ERROR;
	}

	if ( pstEncoder->Open == NULL || pstEncoder->Close == NULL )
	{
		VENC_ERROR("Open or Close function is NULL.\n");
		return RET_ERROR;
	}

	// Set buffer infomation
	pstEncoder->SetMemOSB( pstEncoder, gH1Encode.memOSB );
	pstEncoder->SetMemESB( pstEncoder, gH1Encode.memESB );
	pstEncoder->SetMemAUI( pstEncoder, gH1Encode.memAUI );

	// Init configuration
	pstEncoder->eFrameType = stPrepStatus.frameType;
	pstEncoder->width = stPrepStatus.inWidth;
	pstEncoder->height = stPrepStatus.inHeight;
	pstEncoder->stride = stPrepStatus.yStride;
	pstEncoder->gopLength = H1ENCODE_GOPLENGTH_DEFAULT;

	// 20130207: Fix for frame rate problem.
	if ( gH1Encode.frameRateDenom == 0 || gH1Encode.frameRateNum == 0 )
	{
		VENC_WARN("The framerate set to a value from PREP register.\n");

		pstEncoder->SetFrameRate( pstEncoder, stPrepStatus.frameRateCode );
	}
	else
	{
		VENC_WARN("The framerate set to a value from KADP. [%d,%d,%d]\n", 
			gH1Encode.frameRateCode, gH1Encode.frameRateDenom, gH1Encode.frameRateNum);

		pstEncoder->frameRateCode = gH1Encode.frameRateCode;
		pstEncoder->frameRateDenom = gH1Encode.frameRateDenom;
		pstEncoder->frameRateNum = gH1Encode.frameRateNum;
	}

#ifdef	H1ENCODE_ENABLE_DELAYED_ENCODING
	if ( pstEncoder->frameRateDenom > 0 && pstEncoder->frameRateNum > 0 )
	{
		maxDelayedTime = ( pstEncoder->frameRateDenom * 1000 / pstEncoder->frameRateNum );
		//maxDelayedTime = (maxDelayedTime * 2) + (maxDelayedTime>>1);	// x2.5
		maxDelayedTime = (maxDelayedTime * 2) - (maxDelayedTime>>3);	// x1.875
	}
	else
	{
		maxDelayedTime = 32;
	}

	VENC_WARN("Max delayed time: %d ms\n", maxDelayedTime );
#endif

	if ( gH1Encode.targetBitrate > 0 )
	{
		pstEncoder->bitrate = gH1Encode.targetBitrate;
	}
	else if ( pstEncoder->bitrate == 0 )
	{
		if ( pstEncoder->width == 1920 && pstEncoder->height == 1080 )
		{
			pstEncoder->bitrate = H1ENCODE_BITRATE_FHD;
		}
		else
		{
			pstEncoder->bitrate = H1ENCODE_BITRATE_HD;
		}
	}

#ifdef H1ENCODE_ENABLE_SAR
	// Set SAR Infomation
	pstEncoder->decWidth = stPrepStatus.decWidth;
	pstEncoder->decHeight = stPrepStatus.decHeight;
#endif

	H1ENCODE_LOCK();

	// Open encoder instance ( h.264 or VP8 )
	ret = pstEncoder->Open( pstEncoder );

	H1ENCODE_UNLOCK();

	return ret;
}

static int H1EncodeClose( void )
{
	int ret = RET_ERROR;
	int wait_count = 50;
	
	H1ENCODE_API_T *pstEncoder;

	TRACE_ENTER();

	if ( gH1Encode.pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	while( encode_count > 0 ) 
	{
		if ( wait_count == 0 )
		{
			VENC_ERROR("[%s:%u] wait_count is zero.\n", __F__, __L__ );
			break;
		}
		
		// Wait until idle state
		msleep_interruptible(10);
		wait_count--;
	}
	
	pstEncoder = gH1Encode.pstEncoder;

	if ( pstEncoder->Close == NULL )
	{
		VENC_ERROR("Close function is NULL.\n");
		return RET_ERROR;
	}

	H1ENCODE_LOCK();

#ifdef H1ENCODE_ENABLE_SCD
	// free resource to avoid memory leak. 
	if ( pstEncParamsPrev != NULL )
	{
		_EncParamFree( pstEncParamsPrev );
		pstEncParamsPrev = NULL;
	}
#endif

	ret = pstEncoder->Close( pstEncoder );

	H1ENCODE_UNLOCK();

	// Flush workqueue to avoid NULL pointer access after H1EncodeClose().
	flush_workqueue( gH1Encode.venc_workqueue );

	H1ENCODE_LOCK();

	if (gH1Encode.outputType == LX_VENC_ENCODE_TYPE_VP8)
	{
		VP8Release( pstEncoder );
	}
	else
	{
		H264Release( pstEncoder );
	}
	
	gH1Encode.frameRateCode = 0;
	gH1Encode.frameRateDenom = 0;
	gH1Encode.frameRateNum = 0;
	gH1Encode.pstEncoder = NULL;

#ifdef	H1ENCODE_ENABLE_DELAYED_ENCODING
	maxDelayedTime = 0;
#endif

	H1ENCODE_UNLOCK();

	return ret;
}

#ifdef H1ENCODE_DEBUG_INTERLACED_DUMP
static void _DebugSaveField( void )
{
	u32 yBase;
	H1ENCODE_FRAME_TYPE_T frameType;
	u32 topBase = gH1Encode.memTFB.u32Virt;
	u32 bottomBase = gH1Encode.memTFB.u32Virt + 0x220000;

	yBase = gH1Encode.stPrepStatus.yBase;
	frameType = gH1Encode.stPrepStatus.frameType;

	u32 yVirt = (u32)ioremap( yBase, 2048 * 100 );

	static int top;
	static int bottom;

	if ( top == 0 && frameType == LX_VENC_FRAME_TYPE_TOP )
	{
		VENC_DEBUG("[T] 0x%08x\n", gH1Encode.memTFB.u32Phys);
		memcpy( (void *)topBase, (void *)yVirt, 2048*100 );

		top = 1;
	}
	else if ( bottom == 0 && frameType == LX_VENC_FRAME_TYPE_BOTTOM )
	{
		VENC_DEBUG("[B] 0x%08x\n", gH1Encode.memTFB.u32Phys + 0x220000);
		memcpy( (void *)bottomBase, (void *)yVirt, 2048*100 );

		bottom = 1;
	}

	iounmap( (void *)yVirt );
}
#endif

static int H1EncodeEncode( H1ENCODE_PREP_STATUS_T *pstPrep, u32 gstc )
{
	int ret;
	H1ENCODE_FRAME_TYPE_T frameType;
	H1ENCODE_API_T *pstEncoder;
	H1ENCODE_ENC_PARAMS_T *pstEncParams;

	if ( gH1Encode.pstEncoder == NULL && pstPrep == NULL )
	{
		return RET_ERROR;
	}

	pstEncoder = gH1Encode.pstEncoder;

	pstEncParams = _EncParamAlloc();

	if ( pstEncParams == NULL )
	{
		VENC_ERROR("H1EncodeEncode: Can't allocate pstEncParams.\n");
		return RET_ERROR;
	}
	
	pstEncParams->u32YBase = pstPrep->yBase;
	pstEncParams->u32CBase = pstPrep->cBase;
	pstEncParams->u32Timestamp 	= gstc;
	pstEncParams->frameType = pstPrep->frameType;	// for determining field or frame
	
#ifdef H1ENCODE_ENABLE_SCD
	if ( GET_VENC_CFG_CTRL_INDEX( VENC_CFG_CTRL_SCD ) )
	{
		if ( pstEncParamsPrev == NULL )
		{
			pstEncParamsPrev = pstEncParams;
			return RET_OK;
		}
		else
		{
			H1ENCODE_ENC_PARAMS_T *pstEncParamsTmp;
			
			// Swap current pstEncParams to pstEncParamsPrev
			pstEncParamsTmp = pstEncParams;
			pstEncParams = pstEncParamsPrev;
			pstEncParamsPrev = pstEncParamsTmp;

			if ( pstEncParams != NULL )
			{
				pstEncParams->u32YBaseNext = pstEncParamsPrev->u32YBase;
			}
		}
	}
#endif

	if ( pstEncParams == NULL )
	{
		return RET_ERROR;
	}

#ifdef H1ENCODE_CHECK_INTERLACED_INPUT
	frameType = pstEncParams->frameType;

	if ( frameType == LX_VENC_FRAME_TYPE_TOP || frameType == LX_VENC_FRAME_TYPE_BOTTOM )
	{
	#ifdef H1ENCODE_ENABLE_INTERLACED_BF	
		if ( pstEncoder->bIsFirstFrame && frameType == LX_VENC_FRAME_TYPE_TOP )
	#else
		// if input frame is interaced, check frame type is top field first.
		if ( pstEncoder->bIsFirstFrame && frameType == LX_VENC_FRAME_TYPE_BOTTOM )
	#endif
		{
			ret = RET_ERROR;
			goto ENCODE_END;
		}

		if ( _prevFrameType == frameType )
		{
			VENC_WARN("Unexpected field type. [%d]\n", frameType);
			// Skip the duplicated type of field.
			ret = RET_ERROR;
			goto ENCODE_END;
		}

		//_prevFrameType = frameType;
	}
#endif

	H1ENCODE_TIME( NULL );

	ret = pstEncoder->Encode( pstEncoder, pstEncParams );

	H1ENCODE_TIME( NULL );

ENCODE_END:

	if ( ret != RET_OK )
	{
		VENC_WARN("Encode error!!!\n");

		_EncParamFree( pstEncParams );
	}
#ifdef H1ENCODE_CHECK_INTERLACED_INPUT
	else
	{
		_prevFrameType = frameType;
	}
#endif

	return ret;
}

int H1EncodeCommand( LX_VENC_ENC_COMMAND_T cmd )
{
	int ret;
	
	if ( gH1Encode.eStatus == H1ENCODE_STATUS_TYPE_STOP_PREPARE ||
		gH1Encode.eStatus == H1ENCODE_STATUS_TYPE_START_PREPARE )
	{
		VENC_WARN( "Status is STOP/START PREPARE.\n");
		return RET_ERROR;
	}

	if (cmd == LX_VENC_COMMAND_REFRESH)
	{
		gstOutputStatus.ui32ESRptr = gstOutputStatus.ui32ESWptr = gH1Encode.memESB.u32Phys;
		gstOutputStatus.ui32AUIRptr = gstOutputStatus.ui32AUIWptr = gH1Encode.memAUI.u32Phys;
	}
	else
	{
		gstOutputStatus.ui32ESRptr = gstOutputStatus.ui32ESWptr;
		gstOutputStatus.ui32AUIRptr = gstOutputStatus.ui32AUIWptr;
	}

	if ( cmd == LX_VENC_COMMAND_REFRESH && gH1Encode.eStatus != H1ENCODE_STATUS_TYPE_START )
	{
		H1ENCODE_PREP_STATUS_T stPrepStatus;

		H1ENCODE_LOCK();
		gH1Encode.eStatus = H1ENCODE_STATUS_TYPE_START_PREPARE;
		H1ENCODE_UNLOCK();

		msleep( 100 );
	
		// Init 전에 picture size 및 format 정보를 읽어 옴.
		H1EncodeReadPREP( &stPrepStatus );

		// Index 및 offset 초기화
		H1EncodeReset();

		// H1 Init 및 Config 정보 설정
		ret = H1EncodeOpen( stPrepStatus );

		if ( ret == RET_OK )
		{
			_EncParamClear();
			_InterruptEnableVsync( TRUE );
			
			H1ENCODE_LOCK();
			encode_count = 0;
			gH1Encode.eStatus = H1ENCODE_STATUS_TYPE_START;
			H1ENCODE_UNLOCK();

#ifdef H1ENCODE_ENABLE_DELAYED_ENCODING
			_EncodeStartPost();
#endif
		}
		else
		{
			H1ENCODE_LOCK();
			gH1Encode.eStatus = H1ENCODE_STATUS_TYPE_STOP;
			H1ENCODE_UNLOCK();
		}
	}
	else if ( cmd == LX_VENC_COMMAND_PAUSE && gH1Encode.eStatus != H1ENCODE_STATUS_TYPE_STOP )
	{	
		H1ENCODE_LOCK();
		gH1Encode.eStatus = H1ENCODE_STATUS_TYPE_STOP_PREPARE;
		H1ENCODE_UNLOCK();
		
		_InterruptEnableVsync( FALSE );

		ret = H1EncodeClose();

		H1ENCODE_LOCK();
		gH1Encode.eStatus = H1ENCODE_STATUS_TYPE_STOP;
		H1ENCODE_UNLOCK();
	}
	else
	{
		VENC_DEBUG("Not valid command.\n");

		ret = RET_ERROR;
	}

	if ( ret == RET_OK )
	{
		gH1Encode.cmd = cmd;
	}
	else
	{
		VENC_WARN( "%s: RET_ERROR\n", __F__ );
	}

	return ret;
}

void H1EncodeAUIWrite( H1ENCODE_MEM_T *pMemAUI, const H1ENCODE_AUI_T stAUI )
{
	// au_type
	//	0: IDR picture
	//	1: non-IDR I picture
	// 	2: P picture
	//	3: B picture
	// unit_size: encoded size
	// unit_start: offset from output buffer base
	// timestamp: time at incoming time

	// +----------------------------------------------------------------+
	// |8bit|24bit      |32bit          |32bit          |32bit          | <= 16byte
	// +----+-----------+---------------+---------------+---------------+
	// |AU  |UINT_SIZE  |UINT_START     |INDEX          |TIMESTAMP      |
	// +----------------------------------------------------------------+
	H1ENCODE_AUI_T *pstAUI;

	pstAUI = (H1ENCODE_AUI_T *)(pMemAUI->u32Virt + pMemAUI->u32WriteOffset );

	//VENC_DEBUG("[%s] pstAUI: 0x%08x\n", __FUNCTION__, (u32)pstAUI);

#ifdef H1ENCODE_USE_STRUCT_ASSIGNMENT
	*pstAUI = stAUI;
#else
	memcpy( pstAUI, &stAUI, sizeof(H1ENCODE_AUI_T) );
#endif

	pMemAUI->u32WriteOffset += sizeof(H1ENCODE_AUI_T);	// 128bits = 16bytes

	if ( pMemAUI->u32WriteOffset >= pMemAUI->u32Size )
	{
		pMemAUI->u32WriteOffset = 0;
	}

	return;
}

static void H1EncodePostDone( void )
{
	//TRACE_ENTER();

	eventEncodeDoneWakeup++;
	wake_up_interruptible( &wqEncodeDone );

}

static int H1EncodeWaitDoneTimeout( int timeout )
{
	int ret = RET_OK;

	//TRACE_ENTER();

	eventEncodeDoneWakeup = 0;

	if ( timeout > 0 )
	{
		ret = wait_event_interruptible_timeout( wqEncodeDone, eventEncodeDoneWakeup > 0, timeout * HZ / 1000 );

		if ( ret == 0 )
		{
			ret = RET_TIMEOUT;
		}
		else
		{
			ret = RET_OK;
		}
	}
	else
	{
		wait_event_interruptible( wqEncodeDone, eventEncodeDoneWakeup > 0 );
	}

	return ret;
}

void H1EncodeNotifyDone( H1ENCODE_MEM_T *pstESB, H1ENCODE_MEM_T *pstAUI )
{
	UINT32 ui32ESWptr, ui32ESRptr;
	UINT32 ui32AUIWptr, ui32AUIRptr;

	if ( pstESB == NULL || pstAUI == NULL )
	{
		VENC_ERROR("%s: pstESB or pstAUI is NULL.\n", __F__);
		return;
	}

	ui32ESWptr = pstESB->u32Phys + pstESB->u32WriteOffset;
	ui32ESRptr = pstESB->u32Phys + pstESB->u32ReadOffset;
	ui32AUIWptr = pstAUI->u32Phys + pstAUI->u32WriteOffset;
	ui32AUIRptr = pstAUI->u32Phys + pstAUI->u32ReadOffset;

#if 0
	if ( gui32NumberOfFrames < VENC_BIT_RATE_BUFFER ) { ++gui32NumberOfFrames; }

	gaFrameBytes[gui32BufferIndex] = (ui32ESRptr<ui32ESWptr)?
									(ui32ESWptr-ui32ESRptr) : (pstESB->u32Size-(ui32ESRptr-ui32ESWptr));
	gui32BufferIndex = (gui32BufferIndex+1)%VENC_BIT_RATE_BUFFER;
#endif

	// Flash ES buffer when buffer overflow
	if ( ( gstOutputStatus.ui32ESRptr <= ui32ESWptr) && (ui32ESWptr <= gstOutputStatus.ui32ESWptr) )
	{
		gstOutputStatus.ui32ESRptr = ui32ESRptr;
	}
	gstOutputStatus.ui32ESWptr = ui32ESWptr;

	// Flash AUI buffer when buffer overflow
	if ( ( gstOutputStatus.ui32AUIRptr <= ui32AUIWptr ) && (ui32AUIWptr <= gstOutputStatus.ui32AUIWptr) )
	{
		gstOutputStatus.ui32AUIRptr = ui32AUIRptr;
	}
	gstOutputStatus.ui32AUIWptr = ui32AUIWptr;

#if 0
	VENC_DEBUG("[%s] gui32ESRptr : 0x%8x, gui32ESWptr : 0x%08x\n",
		__FUNCTION__, gstOutputStatus.ui32ESRptr, gstOutputStatus.ui32ESWptr);
	VENC_DEBUG("[%s] gui32AUIRptr: 0x%8x, gui32AUIWptr: 0x%08x\n",
		__FUNCTION__, gstOutputStatus.ui32AUIRptr, gstOutputStatus.ui32AUIRptr);
#endif

	// 기존 venc와 호환을 위해서 GetOutput ioctl용 이벤트 kick
	//OS_SendEvent( &gstEvent, VENC_EVENT_ES_WPTR );
	H1EncodePostDone();
}

#ifdef H1ENCODE_ENABLE_DELAYED_ENCODING

typedef struct {
	H1ENCODE_PREP_STATUS_T stPrepStatus;
	UINT32 timestamp;
	UINT32 inputTime;

	struct list_head encodeList;

} H1ENCODE_ENCODE_LIST_T;

struct list_head gEncodeList;

static void _EncodeQueueInit( void )
{
	INIT_LIST_HEAD( &gEncodeList );
}

static void _EncodeQueueClear( void )
{
	struct list_head *pos;
	struct list_head *q;

	list_for_each_safe( pos, q, &gEncodeList )
	{
		H1ENCODE_ENCODE_LIST_T *item;

		item = list_entry( pos, H1ENCODE_ENCODE_LIST_T, encodeList );
		list_del( pos );

		if ( item != NULL )
		{
			kfree( item );
		}
	}
}

static void _EncodeQueueDestory( void )
{
	//VENC_DEBUG("%s: 0x%08x\n",  __F__, (u32)pStreamList);

	if ( !list_empty( &gEncodeList ) )
	{
		// if list is not empty, clear the list entry
		_EncodeQueueClear( );
	}
	
}

static void _EncodeCheckQueue( void )
{
	while ( list_empty( &gEncodeList ) )
	{
		// wait until list not empty
		msleep_interruptible(2);
	}

	return;
}


static void _EncodeEnqueue( H1ENCODE_PREP_STATUS_T *pstPrepStatus, UINT32 timestamp, UINT32 inputTime )
{
	H1ENCODE_ENCODE_LIST_T *item = NULL;

	if ( pstPrepStatus == NULL )
	{
		return;
	}
	
	while ( item == NULL )
	{
		item = (H1ENCODE_ENCODE_LIST_T *) kmalloc( sizeof(H1ENCODE_ENCODE_LIST_T), GFP_ATOMIC );
	}

#ifdef H1ENCODE_USE_STRUCT_ASSIGNMENT
	item->stPrepStatus = *pstPrepStatus;
#else
	memcpy( &item->stPrepStatus, pstPrepStatus, sizeof(H1ENCODE_PREP_STATUS_T) );
#endif

	item->timestamp = timestamp;
	item->inputTime = inputTime;

	list_add_tail( &item->encodeList, &gEncodeList );
}

static int _EncodeDequeue( H1ENCODE_PREP_STATUS_T *pstPrepStatus, UINT32 *pTimestamp )
{
	struct list_head *pos;
	struct list_head *q;

	if ( pstPrepStatus == NULL || pTimestamp == NULL )
	{
		return RET_ERROR;
	}
	
	list_for_each_safe( pos, q, &gEncodeList )
	{
		H1ENCODE_ENCODE_LIST_T *item;

		item = list_entry( pos, H1ENCODE_ENCODE_LIST_T, encodeList );
		
		if ( item != NULL )
		{
#ifdef H1ENCODE_USE_STRUCT_ASSIGNMENT
			*pstPrepStatus = item->stPrepStatus;
#else
			memcpy( pstPrepStatus, &item->stPrepStatus, sizeof(H1ENCODE_PREP_STATUS_T) );
#endif
			*pTimestamp = item->timestamp;
		}

		list_del( pos );

		if ( item != NULL )
		{
			kfree( item );
			return RET_OK;
		}
		else
		{
			return RET_ERROR;
		}
		
	}

	return RET_ERROR;
}

// Choose discard input by input time
static int _EncodeDiscardQueue( UINT32 currentTime )
{
	struct list_head *pos;
	struct list_head *q;

	int discardCount = 0;
		
	list_for_each_safe( pos, q, &gEncodeList )
	{
		H1ENCODE_ENCODE_LIST_T *item;
		int waitTime;

		item = list_entry( pos, H1ENCODE_ENCODE_LIST_T, encodeList );

		if ( currentTime > item->timestamp )
		{
			waitTime = currentTime - item->timestamp;
		}
		else
		{
			waitTime = currentTime + ((UINT32)0xFFFFFFFF - item->timestamp);
		}

		if ( waitTime > maxDelayedTime )
		{
			list_del( pos );
			discardCount++;
		}
	}

	if ( discardCount )
	{
		VENC_WARN("discardCount [%d], encodedCount [%d]\n", discardCount, encodedCountBeforeDiscard );
		
		H1ENCODE_LOCK();
		encodedCountBeforeDiscard = 0;
		H1ENCODE_UNLOCK();
	}
	
	return discardCount;
}

static void _EncodeStartWait( void )
{
	if ( gH1Encode.eStatus != H1ENCODE_STATUS_TYPE_START )
	{
		interruptible_sleep_on( &wqEncodeStart );
	} 
}

static void _EncodeStartPost( void )
{
	wake_up_interruptible( &wqEncodeStart );
}

static int H1EncodeTask( void* pParam )
{
	int ret;
	
	_EncodeQueueInit();
	
	while(1)
	{
		if ( kthread_should_stop() )
		{
			VENC_TRACE("H1EncodeTask - exit!\n");

			break;
		}

		_EncodeStartWait();

		H1ENCODE_TIME( NULL );

		if ( gH1Encode.pstEncoder != NULL )
		{
			H1ENCODE_PREP_STATUS_T stPrepStatus = {0};
			UINT32 gstc = 0;
			
			if ( gH1Encode.eStatus != H1ENCODE_STATUS_TYPE_START )
			{
				msleep(5);
				continue;
			}

			_EncodeCheckQueue();
			if ( _EncodeDequeue( &stPrepStatus, &gstc ) != RET_OK )
			{
				continue;
			}

			H1ENCODE_LOCK();
			encode_count++;
			H1ENCODE_UNLOCK();

			H1ENCODE_TIME( NULL );

			ret = H1EncodeEncode( &stPrepStatus, gstc );

			H1ENCODE_TIME( NULL );

			H1ENCODE_LOCK();
			if ( ret == RET_OK )
			{ 
				encodedCountBeforeDiscard++;
			}
			encode_count--;
			H1ENCODE_UNLOCK();

			_EncodeDiscardQueue( jiffies );
		}

		H1ENCODE_TIME_END();
	}

	_EncodeQueueDestory();

	return 0;
}
#else
static int H1EncodeTask( void* pParam )
{
	int ret;

	while(1)
	{
		if ( kthread_should_stop() )
		{
			VENC_TRACE("H1EncodeTask - exit!\n");

			break;
		}

		_VsyncWait();

		H1ENCODE_TIME( NULL );

		if ( gH1Encode.pstEncoder != NULL )
		{
			u32 gstc = H1EncodeGetTimestamp();
			H1ENCODE_PREP_STATUS_T stPrepStatus = {0};
		
			if ( gH1Encode.eStatus != H1ENCODE_STATUS_TYPE_START )
			{
				continue;
			}

			H1ENCODE_LOCK();
			encode_count++;
			H1ENCODE_UNLOCK();

			H1EncodeReadPREP( &stPrepStatus );

			H1ENCODE_TIME( NULL );

			ret = H1EncodeEncode( &stPrepStatus, gstc );

			H1ENCODE_TIME( NULL );

			H1ENCODE_LOCK();
			if ( ret == RET_OK )
			{
				encodedCountBeforeDiscard++;
			}
			encode_count--;
			H1ENCODE_UNLOCK();

			#ifdef H1ENCODE_DEBUG_INTERLACED_DUMP
			if ( gH1Encode.stPrepStatus.frameType == LX_VENC_FRAME_TYPE_TOP ||
				gH1Encode.stPrepStatus.frameType == LX_VENC_FRAME_TYPE_BOTTOM ) 
			{
				_DebugSaveField();
			}
			#endif
		}

		H1ENCODE_TIME_END();
	}

	return 0;
}
#endif

#if 0
static u32 _ConvertFrameRate( const LX_VENC_ENC_FRAME_RATE_T eFrameRate )
{
	u32 u32FrameRate = 0;

	switch( eFrameRate )
	{
		case LX_VENC_FRAME_RATE_NONE:
			u32FrameRate = 0;
			break;
		case LX_VENC_FRAME_RATE_23HZ:
			u32FrameRate = 23;
			break;
		case LX_VENC_FRAME_RATE_24HZ:
			u32FrameRate = 24;
			break;
		case LX_VENC_FRAME_RATE_25HZ:
			u32FrameRate = 25;
			break;
		case LX_VENC_FRAME_RATE_29HZ:
			u32FrameRate = 29;
			break;
		case LX_VENC_FRAME_RATE_30HZ:
			u32FrameRate = 30;
			break;
		case LX_VENC_FRAME_RATE_50HZ:
			u32FrameRate = 50;
			break;
		case LX_VENC_FRAME_RATE_59HZ:
			u32FrameRate = 59;
			break;
		case LX_VENC_FRAME_RATE_60HZ:
			u32FrameRate = 60;
			break;
		case LX_VENC_FRAME_RATE_15HZ:
			u32FrameRate = 15;
			break;
	}

	return u32FrameRate;
}
#endif

static void _InterruptEnable( void )
{
	VENC_PREP_RdFL(vdecintr_e_en);

#if !defined(H1ENCODE_USE_POLLING)
//#warning "H1Encode: Use interrupt."
	VENC_PREP_Wr01(vdecintr_e_en, h1_intr_e_en, 1);
#else
//#warning "H1Encode: Use polling."
	VENC_PREP_Wr01(vdecintr_e_en, h1_intr_e_en, 0);
#endif

	//VENC_PREP_Wr01(vdecintr_e_en, vdec_intr_e_en, 1);
	//VENC_PREP_Wr01(vdecintr_e_en, de_intr_e_en, 1);

	VENC_PREP_WrFL(vdecintr_e_en);
}

static void _InterruptDisable( void )
{
	VENC_PREP_RdFL(vdecintr_e_en);

	VENC_PREP_Wr01(vdecintr_e_en, h1_intr_e_en, 0);
	//VENC_PREP_Wr01(vdecintr_e_en, vdec_intr_e_en, 0);
	//VENC_PREP_Wr01(vdecintr_e_en, de_intr_e_en, 0);

	VENC_PREP_WrFL(vdecintr_e_en);
}

static u32 _InterruptRead( void )
{
	u32 status;

	VENC_PREP_RdFL(vdecintr_e_st);
	status = VENC_PREP_Rd(vdecintr_e_st);

	VENC_INTER("status: 0x%08x\n", status);

	return status;
}

static void _InterruptClear( void )
{
	u32 enableIntr;

	VENC_PREP_RdFL(vdecintr_e_en);
	enableIntr = VENC_PREP_Rd(vdecintr_e_en);

	VENC_PREP_RdFL(vdecintr_e_cl);

	if ( enableIntr & 0x1 )
	{
		// clear vdec
		VENC_PREP_Wr01(vdecintr_e_cl, vdec_intr_e_cl, 1);
	}

	if ( enableIntr & 0x2 )
	{
		// clear de vsync
		VENC_PREP_Wr01(vdecintr_e_cl, de_intr_e_cl, 1);
	}

	if ( enableIntr & 0x4 )
	{
		// H1Encoder Interrupt

	}

	VENC_PREP_WrFL(vdecintr_e_cl);

}

static void _InterruptEnableVsync( BOOLEAN enable )
{
	//VENC_DEBUG("H1EncodeVsync ( enable=%s ) \n", enable ? "TRUE": "FALSE");

	VENC_PREP_RdFL(vdecintr_e_en);

	if ( enable )
	{
		VENC_PREP_Wr01(vdecintr_e_en, vdec_intr_e_en, 1);
		VENC_PREP_Wr01(vdecintr_e_en, de_intr_e_en, 1);
	}
	else
	{
		VENC_PREP_Wr01(vdecintr_e_en, vdec_intr_e_en, 0);
		VENC_PREP_Wr01(vdecintr_e_en, de_intr_e_en, 0);
	}

	VENC_PREP_WrFL(vdecintr_e_en);

#if defined(H1ENCODE_DEBUG_DUMP)
	if ( enable == FALSE )
	{
		H1EncodeDumpStop();
	}
#endif

}

#ifdef H1ENCODE_USE_TIMER_VSYNC
static void _TimerCheckEncode( unsigned long arg );
static void _TimerAdd( unsigned long arg )
{
	if ( arg > 4 )
	{
		return;
	}
	
	// Add timer
	encode_timer.data = arg + 1;

	if ( encode_timer.function == NULL )
	{
		encode_timer.function = _TimerCheckEncode;
	}
	
#ifdef	DEFINE_TARGET_FPGA
	encode_timer.expires = jiffies + 10000;	// +2ms
#else
	encode_timer.expires = jiffies + msecs_to_jiffies(1);
#endif

	VENC_KDRV_MSG( VENC_MSG_TIMER, "Add timer: expires[%lu]\n", encode_timer.expires);
	add_timer( &encode_timer );
}

static void _TimerCheckEncode( unsigned long arg )
{
	if ( encode_count > 0 )
	{
		// Add (arg)th timer
		_TimerAdd( arg );
	}
	else
	{
		VENC_KDRV_MSG( VENC_MSG_TIMER, "Call wake_up_interruptible() @ timer function\n");		
		wake_up_interruptible( &wqEncodeVsync );
	}
}
#endif

static void _VsyncWait( void )
{
	int ret;
	int discardCount = 0;

#ifdef H1ENCODE_USE_VSYNC_BUSYWAIT
	while( 1 )
	{
		if ( gH1Encode.ui32CountVsync != 0 )
		{
			break;
		}
		else 
		{
			mdelay(2);
		}
	}
#else
	wait_event_interruptible( wqEncodeVsync, gH1Encode.ui32CountVsync != 0 );
#endif

#if 0
{
	static UINT32 log_pts_list[30];
	static UINT32 log_jiffies_list[30];
	static UINT32 log_index;
	static UINT32 log_count;

	log_pts_list[log_index] = H1EncodeReadSTC( LX_VENC_TIMESTAMP_PTS );
	log_jiffies_list[log_index] = jiffies;
	log_index++;

	if ( log_index == 30 )
	{	
		int len;
		char buf[128];
		OS_FILE_T log_file;

		if ( log_count > 2000 )
		{
			OS_OpenFile( &log_file, "/tmp/pts_venc.log", O_CREAT|O_TRUNC|O_LARGEFILE, 0666 );
			OS_CloseFile( &log_file );	
			log_count = 0;
		}
		else
		{
			log_count++;
		}

		if ( RET_OK == OS_OpenFile( &log_file, "/tmp/pts_venc.log", O_CREAT|O_APPEND|O_LARGEFILE, 0666 ) )
		{
			int i;

			for ( i = 0; i < 30; i++ )
			{
				len = snprintf(buf, sizeof(buf), "VENC: PTS:%lu, jiffies:%lu\n", log_pts_list[i], log_jiffies_list[i] );
				len = OS_WriteFile( &log_file, (char *)buf, len );
			}

			OS_CloseFile( &log_file );	
		}

		log_index = 0;
	}
}
#endif

	if ( gH1Encode.ui32CountVsync > 1 )
	{
		u32 before = gH1Encode.ui32CountFrameSkip;
		gH1Encode.ui32CountFrameSkip += (gH1Encode.ui32CountVsync - 1);

		VENC_VSYNC("%d vsync skip. (Total vsync skip: %d)\n", gH1Encode.ui32CountFrameSkip - before, gH1Encode.ui32CountFrameSkip);

		if ( before < gH1Encode.ui32CountFrameSkip )
		{
			discardCount = gH1Encode.ui32CountFrameSkip - before;
		}
		else if ( before > gH1Encode.ui32CountFrameSkip )
		{
			discardCount = gH1Encode.ui32CountFrameSkip + ((UINT32)0xFFFFFFFF - before);
		}
	}
	
	if ( discardCount > 0 )
	{
		VENC_WARN("discardCount [%d], encodedCount [%d]\n", discardCount, encodedCountBeforeDiscard );
		
		H1ENCODE_LOCK();
		encodedCountBeforeDiscard = 0;
		H1ENCODE_UNLOCK();
	}

	gH1Encode.ui32CountVsync = 0;
}

static void _VsyncPost( void )
{
	gH1Encode.ui32CountVsync++;

#ifdef H1ENCODE_USE_TIMER_VSYNC
	if ( encode_count > 0 )
	{
		// Add 1st timer ( count=0 )
		_TimerAdd( 0 );
	}
	else
#endif
	{
		wake_up_interruptible( &wqEncodeVsync );
	}
}

static int _EventWait( H1ENCODE_EVENT_T event, int timeout )
{
	int ret = RET_ERROR;
	u32 recvEvent;

	if ( event == 0 )
	{
		return ret;
	}

	if ( timeout == 0 )
	{
		timeout = 100;
	}
		
	ret = OS_RecvEvent( &gstEventH1, event, &recvEvent, OS_EVENT_RECEIVE_ANY, timeout);

	return ret;
}

static void _EventPost( H1ENCODE_EVENT_T event )
{
	
	if ( event == 0 )
	{
		return;
	}
	
	OS_SendEvent( &gstEventH1, event );
}

#if !defined(H1ENCODE_USE_POLLING)

static void H1EncodeHX280ISR( unsigned long temp )
{

	// reference from hx286enc_isr() at hx280enc.c:413
	u32 irq_status;

	// 1. save irq status & clear irq status
	irq_status = HXENC_ReadIRQ();

	if ( irq_status & 0x01 )
	{
		// 2. Clear IRQ and sllice ready interrupt bit
		HXENC_WriteIRQ( irq_status & (~0x101) );

		// Handle slice ready interrupts. The reference implementation
		// doesn't signal slice ready interrupts to EWL.
		// The EWL will poll the slices ready register value.
		if ( (irq_status & 0x1FE) == 0x100)
		{
			// Slice ready IRQ handled
			return;
		}

		// 2. kick event
		HXENC_WakeupIRQ();

#ifdef H1ENCODE_USE_LOGFILE
		do_gettimeofday(&_irqTime);
#endif
	}

}

#endif

#ifdef H1ENCODE_UNUSE_ENCODE_THREAD
static void H1EncodeEncodeHandler( unsigned long temp )
{
	int ret;
	H1ENCODE_PREP_STATUS_T stPrepStatus;
	u32 gstc;

	H1EncodeUpdateTimestamp();
	gstc = H1EncodeGetTimestamp();
	H1EncodeReadPREP( &stPrepStatus );

	ret = H1EncodeEncode( &stPrepStatus, gstc );

	if ( ret != RET_OK )
	{
		VENC_ERROR("[%s:%d] H1EncodeEncode() = %d\n", __F__, __L__, ret );
	}
}
#endif

#ifdef H1ENCODE_DEBUG_CHECK_VSYNC
static UINT32 jiffies_vsync;
#endif

static void H1EncodeVsyncHandler( unsigned long temp )
{
#ifdef H1ENCODE_DEBUG_CHECK_VSYNC	
	UINT32 jiffies_cur = jiffies;
#endif

#ifdef H1ENCODE_ENABLE_DROP_FIRST_FRAME
	if ( gH1Encode.remain_drop > 0 )
	{
		gH1Encode.remain_drop--;
		return;
	}
#endif

	// Raise vsync interrupt
#ifdef H1ENCODE_ENABLE_DELAYED_ENCODING
	H1ENCODE_PREP_STATUS_T stPrepStatus;
	u32 gstc;

	H1EncodeUpdateTimestamp();
	gstc = H1EncodeGetTimestamp();
	H1EncodeReadPREP( &stPrepStatus );

	_EncodeEnqueue( &stPrepStatus, gstc, jiffies );
#else
	H1EncodeUpdateTimestamp();
	H1EncodeUpdatePREP();
	
	// Encode wakeup (EncodeTask)
	// 이전 frame encoding시간 지연으로 Vsync 처리를 바로 할 수 없을 때, 
	// Timer interrupt를 동작시켜 5ms정도 지연효과를 기대함.
	// (Worst Cast에서 테스트 필요)
	_VsyncPost();
#endif

	gH1Encode.ui32TotalVsync++;

#ifdef H1ENCODE_DEBUG_CHECK_VSYNC
	if ( gH1Encode.frameRateNum > 0 && gH1Encode.frameRateDenom > 0 )
	{
		UINT32 interval = (jiffies_cur - jiffies_vsync);
		UINT32 expectedInterval = (gH1Encode.frameRateDenom * 1000 / gH1Encode.frameRateNum);

		if ( interval < expectedInterval - 1 )
		{
			VENC_WARN("Too short vsync interval: %d\n", interval );
		}
		else if ( interval > expectedInterval + 1 )
		{
			VENC_WARN("Too long vsync interval: %d\n", interval );
		}
	}

	jiffies_vsync = jiffies_cur;
#endif

}

void H1EncodeISRHandler( void )
{
//	BOOLEAN bVsync = FALSE;
	u32 status;

//	TRACE_ENTER();

	status = _InterruptRead();

	if ( status )
	{
		_InterruptClear();

		if ( status & 0x1 || status & 0x2 )	// vdec_intr_st, de_intr_st
		{
#ifdef H1ENCODE_UNUSE_ENCODE_THREAD
			tasklet_schedule( &VENC_TASKLET_VSYNC ); 
#else
			H1EncodeVsyncHandler( 0UL );
#endif
		}

#if !defined(H1ENCODE_USE_POLLING)
		if ( status & 0x4 )	// intr_h1enc
		{
			H1EncodeHX280ISR( 0UL );
		}
#endif
	}
}

