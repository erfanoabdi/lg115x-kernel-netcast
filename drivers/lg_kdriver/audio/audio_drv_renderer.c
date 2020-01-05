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


/** @file	audio_kdrv_renderer.c
 *
 *  main driver implementation for  audio render device.
 *  audio render device will teach you how to make device driver with new platform.
 *
 *  author	wonchang.shin (wonchang.shin@lge.com)
 *  version	0.1
 *  date		2012.04.25
 *  note		Additional information.
 *
 *  @addtogroup lg1150_audio
 *	@{
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>    /**< For isr */
#include <linux/irq.h>			/**< For isr */
#include <linux/ioport.h>		/**< For request_region, check_region etc */
#include <linux/rmap.h>
#include <linux/kthread.h>
#include <asm/io.h>				/**< For ioremap_nocache */
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/version.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "base_drv.h"
#include "debug_util.h"
#include "audio_cfg.h"
#include "audio_drv.h"

#include "audio_drv_master.h"
#include "audio_imc_func.h"
#include "audio_buffer.h"
#include "audio_drv_renderer.h"
#include "audio_drv_manager.h"

#include "imc/adec_imc.h"
#include "imc/evt/module_evt_dec.h"

#define GET_REN_INDEX(ALLOCDEC_DEV_ID)	((ALLOCDEC_DEV_ID) - AUD_DEV_REN0)

// A/V Lipsync
#define TIMESTAMP_MASK						0x0FFFFFFF
#define AUD_REN_DEFAULT_VOLUME				1024
#define AUD_REN_DEFULT_PORT					0xFF

// Mixer
#define AUD_REN_PORT_ENABLE					0x1
#define AUD_REN_PORT_DISABLE				0x0

#define AUD_REN_NUM_OF_CHANNEL_OF_SRC_MIX	 2		// channel of SRC output & MIX input
#define AUD_REN_BITS_PER_SAMPLE_OF_SRC_MIX	32		// bits per sample of SRC output & MIX input
#define AUD_REN_INIT_MUTE_LENGTH_MIX	  5120		// initial mute delay 112ms(1024, 23ms) & MIX input

#define COUNT_MIN_CHECK_START	1
#define COUNT_MAX_CHECK_START	3

// RTS threshold
#if 1
#define RTS_THRESHOLD_UPPER			(384*40)	// (384*30)	// 30ms: 48KHz Stereo 32Bits 기준
#define RTS_RECOVER_UPPER			(384*20)	// (384*10)	// 10ms
#define RTS_THRESHOLD_LOWER			(384*1)		//  1ms
#define RTS_RECOVER_LOWER			(384*30)	// (384*20)	// 20ms
#else
// for test
#define RTS_THRESHOLD_UPPER			(384*300)	// 300ms: 48KHz Stereo 32Bits 기준
#define RTS_RECOVER_UPPER			(384*100)	// 100ms
#define RTS_THRESHOLD_LOWER			(384*10)	//  10ms
#define RTS_RECOVER_LOWER			(384*200)	// 200ms
#endif

// RTS output frequency
#define RTS_FAST_FREQ				47875		// 47750
#define RTS_NORMAL_FREQ				48000
#define RTS_SLOW_FREQ				48125		// 48250

// Fade In/Out control - for RTS
#define FADE_IN_OUT_ENABLE_DEFAULT	1			// Enable
#define FADE_LENGTH_DEFAULT			8			// 9(512sample)->8(256smaple) for Reducing PCM Delay
#define FADE_LENGTH_RTS				7

// MIX wait length
#define MIX_WAIT_LENGTH_DEFAULT		512			// 2048(17408byte)->512(5120byte) for reducing PCM Delay
#define MIX_WAIT_LENGTH_RTS			256
#define MIX_WAIT_LENGTH_EMP			2048

#define	MOD_CTRL_SRC_NUM			2

extern UINT8	*allocMod_Str[ADEC_MODULE_MOD_MAX+1];
extern UINT8	*modTypeStr[LX_AUD_MOD_TYPE_MAX+1];
extern UINT8	*allocDev_Str[AUD_DEV_MAX+1];
extern UINT8	*devTypeStr[LX_AUD_DEV_TYPE_MAX+1];

extern AUD_MOD_NUM_T stFwRmModType[LX_AUD_MOD_TYPE_MAX+1];
extern LX_AUD_BUF_MEM_CFG_S_T stMIX[];
extern VDEC_LIPSYNC_REG_T	*g_pVDEC_LipsyncReg;	//VDEC H/W Reg. for Lip Sync Control with ADEC H/W Reg.

AUD_RENDER_INFO_T	_gRenderInfo[DEV_REN_NUM];

UINT32	_gRenderCheckStartCount[DEV_REN_NUM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

BOOLEAN	_gbUsedCtrlSrc[MOD_CTRL_SRC_NUM] = {FALSE, FALSE};

static SINT32 AUDIO_StartRenderer (UINT32 allocDev);
static SINT32 AUDIO_StopRenderer (UINT32 allocDev);
static SINT32 AUDIO_FlushRenderer (UINT32 allocDev);
static SINT32 AUDIO_FeedRen(UINT32 allocDev, LX_AUD_RENDER_FEED_T * pRenFeed);
static SINT32 AUDIO_SetRendererVolume (UINT32 allocDev, UINT32 volume);
static SINT32 AUDIO_SetLipsync (UINT32 allocDev,  LX_AUD_RENDER_PARAM_LIPSYNC_T *pParamLipsync);
static SINT32 AUDIO_EnableLipsync (UINT32 allocDev, UINT32 bOnOff);
static SINT32 AUDIO_SetClockId (UINT32 allocDev, UINT32 clockId);
static SINT32 AUDIO_SetRate (UINT32 allocDev, LX_AUD_RENDER_PARAM_RATE_T *pParamRate);
static SINT32 AUDIO_SetBasetime (UINT32 allocDev, LX_AUD_RENDER_PARAM_BASETIME_T *pParamBasetime);
static SINT32 AUDIO_SetClockType (UINT32 allocDev, LX_AUD_RENDER_CLK_TYPE_T clockType);
static SINT32 AUDIO_SetRendererParam (UINT32 allocDev, LX_AUD_RENDER_PARAM_T *pParamCodec);
static SINT32 AUDIO_ConnectRenderer (UINT32 allocDev, UINT32 otherAllocDev);
static SINT32 AUDIO_DisconnectRenderer (UINT32 allocDev, UINT32 otherAllocDev);
static SINT32 AUDIO_CloseRenderer (AUD_DEVICE_T* audDev);
static SINT32 AUDIO_GetRenderedStatus(UINT32 allocDev, LX_AUD_RENDERED_STATUS_T *pRenderedStatus);
static SINT32 AUDIO_EnableRTS (UINT32 allocDev, UINT32 bOnOff);
static SINT32 AUDIO_SetTrickPlayMode(UINT32 allocDev, UINT32 trickMode);

/**
 * Register Notification.
 * @param 	pRenInfo		[in] renderer information.
 * @param 	pFuncImcNoti	[in] pointer to callback function.
 * @param 	allocMod		[in] allocated module.
 * @param 	event			[in] event.
 * @return 	void.
 * @see		().
 */
static void _AUDIO_RegisterRendererNoti(
	AUD_RENDER_INFO_T* pRenInfo,
	PFN_ImcNoti	pFuncImcNoti,
	UINT32 allocMod,
	UINT32 event,
	IMC_ACTION_REPEAT_TYPE repeatType,
	SINT32 notiLevel)
{
	UINT32							actionID;
	AUD_EVENT_T						*pRenEvent 		= NULL;
	ImcActionParameter 				actionParam;

	if(pRenInfo->ui32EventNum >= AUD_EVENT_NUM)
	{
		AUD_KDRV_ERROR("RenEventNum(%d) is over AUD_EVENT_NUM. \n", pRenInfo->ui32EventNum);
		return;
	}

	actionParam.actionType = IMC_ACTION_GET_CALLBACK;
	actionParam.repeatType = repeatType;
	actionParam.target = ADEC_MODULE_MAN_ARM;
	actionParam.actionParam.notiParam.noti = (PFN_ImcNoti)pFuncImcNoti;
	actionParam.actionParam.notiParam.param = pRenInfo;
	actionParam.actionParam.notiParam.level = notiLevel;
	IMC_RegisterEvent(IMC_GetLocalImc(0), event, allocMod, &actionID, &actionParam);

	//if(repeatType != IMC_ACTION_ONCE)
	{
		pRenEvent = &pRenInfo->renderEvent[pRenInfo->ui32EventNum];
		pRenEvent->event = event;
		pRenEvent->actionID = actionID;
		pRenEvent->moduleID = allocMod;
		pRenInfo->ui32EventNum++;
	}

	AUD_KDRV_PRINT("%s [0x%x 0x%x, 0x%x] \n", __F__, event, actionID, allocMod);
	return;
}

static SINT32 _AUDIO_InitRendererParam(UINT32 allocDev)
{
	ULONG	flags;
	SINT32	renIndex = 0;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	memset(&(_gRenderInfo[renIndex].renderStatus), 0, sizeof(LX_AUD_RENDERED_STATUS_T));

	memset(&(_gRenderInfo[renIndex].renderEvent[0]), 0, sizeof(AUD_EVENT_T)*AUD_EVENT_NUM);
	_gRenderInfo[renIndex].ui32EventNum = 0;

	memset(&(_gRenderInfo[renIndex].renderConnect[0]), 0, sizeof(AUD_RENDER_CONNECT_T)*AUD_RENDER_CONNECT_NUM);
	_gRenderInfo[renIndex].ui32ConnectNum = 0;

	_gRenderInfo[renIndex].ui32AllocDev = allocDev;
	_gRenderInfo[renIndex].bStarted = FALSE;
	_gRenderInfo[renIndex].bClosed = FALSE;
	_gRenderInfo[renIndex].bResetting = FALSE;
	_gRenderInfo[renIndex].ui32Volume = AUD_REN_DEFAULT_VOLUME;
	_gRenderInfo[renIndex].ui32MixerPort = AUD_REN_DEFULT_PORT;
	_gRenderInfo[renIndex].renderParam.samplingFreq = LX_AUD_SAMPLING_FREQ_NONE;
	_gRenderInfo[renIndex].bLipsyncOnOff = FALSE;
	_gRenderInfo[renIndex].bRTSOnOff = FALSE;
	_gRenderInfo[renIndex].ctrlSrcInfo.bCtrlSrcOnOff = FALSE;
	_gRenderInfo[renIndex].ctrlSrcInfo.allocCtrlSrc = ADEC_MODULE_NOT_DEF;

	_gRenderCheckStartCount[renIndex] = 0;

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Reset a audio SET event type for next event.
	gAudSetEvent[allocDev].allocDev = AUD_NO_DEV;
	gAudSetEvent[allocDev].eventMsg = LX_AUD_EVENT_MASK_NONE;

	//Reset a audio GET event type for next event.
	gAudGetEvent[allocDev].allocDev = AUD_NO_DEV;
	gAudGetEvent[allocDev].eventMsg = LX_AUD_EVENT_MASK_NONE;

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	AUD_KDRV_PRINT("%s : renIndex %x.\n", __F__, renIndex);

	return RET_OK;
}

/**
 * open handler for audio render device
 *
 */
SINT32	KDRV_AUDIO_OpenRenderer(struct inode *inode, struct file *filp)
{
	SINT32	retVal = 0;
	UINT32 nMajor;
	UINT32 nMinor;
	AUD_DEVICE_T*	my_dev;
	UINT32 devType;
	LX_AUD_ALLOC_FREE_INFO_T OpenInfo;
	LX_AUD_ALLOC_DEV_T		allocDev =AUD_NO_DEV;
	SINT32	renIndex = 0;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	filp->private_data = kmalloc(sizeof(AUD_DEVICE_T), GFP_KERNEL);
	my_dev = (AUD_DEVICE_T*)filp->private_data;

	devType = DEV_TYPE_BASE + nMinor;
	my_dev->devType = devType;

	//my_dev->devType = LX_AUD_RENDERER;
	OpenInfo.devType = devType;
	allocDev = AUDIO_AllocDev(&OpenInfo);
	if(allocDev != AUD_NO_DEV )
	{
		AUD_KDRV_RM("%s is opened[major:%d minor:%d][Alloc:%s:%d] \n",(char *)devTypeStr[devType],nMajor,nMinor,(char *)allocDev_Str[allocDev],allocDev);
		retVal =RET_OK;
	}
	else
	{
		AUD_KDRV_RM(" %s is not available ret[%d] \n",devTypeStr[devType],allocDev);
		goto KDRV_OPEN_ERROR;
	}

	my_dev->allocDev =  allocDev ;
	filp->private_data = my_dev;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	if(_AUDIO_InitRendererParam(allocDev) == RET_ERROR)
		goto KDRV_OPEN_ERROR;

	AUD_KDRV_RM("Open Render device file  (%d:%d)\n", nMajor, nMinor);

	return retVal;

KDRV_OPEN_ERROR:
	kfree(filp->private_data);
	return RET_ERROR;
}

/**
 * close handler for audio render device
 *
 */
SINT32	KDRV_AUDIO_CloseRenderer(struct inode *inode, struct file *filp)
{
	SINT32	retVal = 0;
	UINT32	nMajor;
	UINT32	nMinor;
	AUD_DEVICE_T* audDev;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	audDev = (AUD_DEVICE_T*)filp->private_data;

	if(audDev == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: private_data is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	kfree(audDev);

	AUD_KDRV_RM("Close Render device file   (%d:%d)\n", nMajor, nMinor);

	return retVal;
}


/**
 * ioctl handler for audio render device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int KDRV_AUDIO_IoctlRenderer(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#else
long KDRV_AUDIO_IoctlRenderer(struct file *filp, unsigned int cmd, unsigned long arg)
#endif
{
	SINT32			retVal = RET_OK;
	SINT32			err = 0;
	UINT32			allocDev;
	AUD_DEVICE_T*	my_dev;

	my_dev = (AUD_DEVICE_T*)filp->private_data;
	if(my_dev == NULL)
		return RET_ERROR;
	/*
	* check if IOCTL command is valid or not.
	* - if magic value doesn't match, return error (-ENOTTY)
	* - if command is out of range, return error (-ENOTTY)
	*
	* note) -ENOTTY means "Inappropriate ioctl for device.
	*/
	if(_IOC_TYPE(cmd) != AUD_REN_IOC_MAGIC)
	{
		DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if(_IOC_NR(cmd) > AUD_REN_IOC_MAXNR)
	{
		DBG_PRINT_WARNING("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
		return -ENOTTY;
	}

	/*
	* check if user memory is valid or not.
	* if memory can't be accessed from kernel, return error (-EFAULT)
	*/
	if(_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if(_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if(err)
	{
		DBG_PRINT_WARNING("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
							_IOC_NR(cmd),
							(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
							(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
							(void*)arg );
		return -EFAULT;
	}

	allocDev = my_dev->allocDev;

	AUD_KDRV_TRACE("cmd = %08X (cmd_idx=%d) allocDev = %d\n", cmd, _IOC_NR(cmd), allocDev);

	switch(cmd)
	{
		case AUD_REN_IOW_SET_PARAM:
		{
			LX_AUD_RENDER_PARAM_T		renParam;

			if(copy_from_user(&renParam, (void __user *)arg, sizeof(LX_AUD_RENDER_PARAM_T)))
				return RET_ERROR;

			AUD_KDRV_TRACE("%s.%d: [AUD_REN_IOW_SET_PARAM] Called\n", __F__, __L__);
			retVal = AUDIO_SetRendererParam(allocDev, &renParam);
		}
		break;

		case AUD_REN_IO_START:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_REN_IOW_START] Called\n", __F__, __L__);
			retVal = AUDIO_StartRenderer(allocDev);
		}
		break;

		case AUD_REN_IO_STOP:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_REN_IOW_STOP] Called\n", __F__, __L__);
			retVal = AUDIO_StopRenderer(allocDev);
		}
		break;

		case AUD_REN_IO_FLUSH:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_REN_IOW_FLUSH] Called\n", __F__, __L__);
			retVal = AUDIO_FlushRenderer(allocDev);
		}
		break;

		case AUD_REN_IOW_FEED:
		{
			LX_AUD_RENDER_FEED_T		renFeed;

			if(copy_from_user(&renFeed, (void __user *)arg, sizeof(LX_AUD_RENDER_FEED_T)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_FeedRen[alloc:%d] \n",allocDev);
			retVal = AUDIO_FeedRen(allocDev, &renFeed);
		}
		break;

		case AUD_REN_IOW_SET_VOLUME:
		{
			UINT32		renVolume;

			if(copy_from_user(&renVolume, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUD_REN_IOW_SET_VOLUME[alloc:%d] \n",allocDev);
			retVal = AUDIO_SetRendererVolume(allocDev, renVolume);
		}
		break;

		case AUD_REN_IOW_SET_LIPSYNCPARAM:
		{
			LX_AUD_RENDER_PARAM_LIPSYNC_T		paramLipsync;

			if(copy_from_user(&paramLipsync, (void __user *)arg, sizeof(LX_AUD_RENDER_PARAM_LIPSYNC_T)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_SetLipsync[alloc:%d] \n",allocDev);
			retVal = AUDIO_SetLipsync(allocDev, &paramLipsync);
		}
		break;

		case AUD_REN_IOW_ENABLE_LIPSYNC:
		{
			UINT32		bOnOff;

			if(copy_from_user(&bOnOff, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_EnableLipsync[alloc:%d] \n",allocDev);
			retVal = AUDIO_EnableLipsync(allocDev, bOnOff);
		}
		break;

		case AUD_REN_IOW_SET_CLOCKID:
		{
			UINT32		clockId;

			if(copy_from_user(&clockId, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_SetClockId[alloc:%d] \n",allocDev);
			retVal = AUDIO_SetClockId(allocDev, clockId);
		}
		break;

		case AUD_REN_IOW_SET_RATE:
		{
			LX_AUD_RENDER_PARAM_RATE_T		paramRate;

			if(copy_from_user(&paramRate, (void __user *)arg, sizeof(LX_AUD_RENDER_PARAM_RATE_T)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_SetRate[alloc:%d] \n",allocDev);
			retVal = AUDIO_SetRate(allocDev, &paramRate);
		}
		break;

		case AUD_REN_IOW_SET_BASETIME:
		{
			LX_AUD_RENDER_PARAM_BASETIME_T		paramBasetime;

			if(copy_from_user(&paramBasetime, (void __user *)arg, sizeof(LX_AUD_RENDER_PARAM_BASETIME_T)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_SetBasetime[alloc:%d] \n",allocDev);
			retVal = AUDIO_SetBasetime(allocDev, &paramBasetime);
		}
		break;

		case AUD_REN_IOW_SET_CLOCKTYPE:
		{
			LX_AUD_RENDER_PARAM_CLOCKTYPE_T		paramClockType;

			if(copy_from_user(&paramClockType, (void __user *)arg, sizeof(LX_AUD_RENDER_PARAM_CLOCKTYPE_T)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_SetClockType[alloc:%d] \n",allocDev);
			retVal = AUDIO_SetClockType(allocDev, paramClockType.clocktype);
		}
		break;

		case AUD_REN_IOW_CONNECT:
		{
			UINT32	connectDev;

			if(copy_from_user(&connectDev, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUD_REN_IOW_CONNECT A[%d] \n",connectDev);
			retVal = AUDIO_ConnectRenderer(allocDev, connectDev);

		}
		break;

		case AUD_REN_IOW_DISCONNECT:
		{
			UINT32	disconnectDev;

			if(copy_from_user(&disconnectDev, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUD_REN_IOW_DISCONNECT A[%d] \n",disconnectDev);
			retVal = AUDIO_DisconnectRenderer(allocDev, disconnectDev);
		}
		break;

		case AUD_REN_IOR_GET_KDRV_HANDLE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_REN_IOW_GET_KDRV_HANDLE] Called\n", __F__, __L__);

			if(copy_to_user((void *)arg, (void *)&(my_dev->allocDev), sizeof(UINT32)))
				return RET_ERROR;
		}
		break;

		case AUD_REN_IO_CLOSE_DEVICE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_REN_IO_CLOSE_DEVICE] Called\n", __F__, __L__);
			retVal = AUDIO_CloseRenderer(my_dev);
		}
		break;

		case AUD_REN_IOR_GET_STATUS:
		{
			LX_AUD_RENDERED_STATUS_T renderedStatus;

			AUD_KDRV_TRACE("%s.%d: [AUD_REN_IOW_GET_STATUS] Called\n", __F__, __L__);

			AUDIO_GetRenderedStatus(allocDev, &renderedStatus);

			if(copy_to_user((void *)arg, (void *)&(renderedStatus), sizeof(LX_AUD_RENDERED_STATUS_T)))
				return RET_ERROR;
		}
		break;

		case AUD_REN_IOW_ENABLE_RTS:
		{
			UINT32		bOnOff;

			if(copy_from_user(&bOnOff, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_EnableLipsync[alloc:%d] \n", allocDev);
			retVal = AUDIO_EnableRTS(allocDev, bOnOff);
		}
		break;

		case AUD_REN_IOW_TRICK_PLAY:
		{
			UINT32		trickMode;

			if(copy_from_user(&trickMode, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			AUD_KDRV_TRACE(" AUDIO_SetTrickPlayMode[alloc:%d] \n", allocDev);
			retVal = AUDIO_SetTrickPlayMode(allocDev, trickMode);
		}
		break;

		default:
		{
			/* redundant check but it seems more readable */
			AUD_KDRV_ERROR("Invalid IOCTL Call!!!\n");
			retVal = RET_INVALID_IOCTL;
		}
		break;
	}


	return retVal;
}

static ADEC_BUF_T* _AUDIO_GetRendererWriteStructure(UINT32 allocDev)
{
	LX_AUD_ALLOC_MOD_T		mpbModule = ADEC_MODULE_MPB_0;
	UINT32 					bufIndex = 0;
	ADEC_BUF_T				*pWriterStruct = NULL;

	// Get a MPB buffer
	mpbModule = AUDIO_HasThisModuleType(allocDev, LX_AUD_MPB);
	if((mpbModule < ADEC_MODULE_MPB_0) || (mpbModule > ADEC_MODULE_MPB_7))
	{
		AUD_KDRV_RMD(" Module[%s] is not available \n", modTypeStr[LX_AUD_MPB]);
		return pWriterStruct;
	}
	else
	{
		AUD_KDRV_RMD("Module[%s] [Alloc:%s:%d] \n",modTypeStr[LX_AUD_MPB],(char *)allocMod_Str[mpbModule],mpbModule);
	}

	bufIndex = mpbModule - ADEC_MODULE_MPB_0;
	pWriterStruct = ( ADEC_BUF_T  * )stMIX[bufIndex].pWriterReaderStruct;

	AUD_KDRV_PRINT("%s : allocDev %x.\n", __F__, allocDev);

	return pWriterStruct;
}

static ADEC_BUF_T* _AUDIO_GetRendererDPBWriteStructure(UINT32 allocDev)
{
	LX_AUD_ALLOC_MOD_T		dpbModule = ADEC_MODULE_DPB_0;
	UINT32 					bufIndex = 0;
	ADEC_BUF_T				*pWriterStruct = NULL;

	// Get a DPB buffer
	dpbModule = AUDIO_HasThisModuleType(allocDev, LX_AUD_DPB);

	if((dpbModule < ADEC_MODULE_DPB_0) || (dpbModule > ADEC_MODULE_DPB_3))
	{
		AUD_KDRV_RMD(" Module[%s] is not available \n", modTypeStr[LX_AUD_DPB]);
		return pWriterStruct;
	}
	else
	{
		AUD_KDRV_RMD("Module[%s] [Alloc:%s:%d] \n",modTypeStr[LX_AUD_DPB],(char *)allocMod_Str[dpbModule],dpbModule);
	}

	bufIndex = dpbModule - ADEC_MODULE_DPB_0;
	pWriterStruct = ( ADEC_BUF_T  * )stDPB[bufIndex].pWriterReaderStruct;

	AUD_KDRV_PRINT("%s : allocDev %x.\n", __F__, allocDev);

	return pWriterStruct;
}

static void _AUDIO_EnableMixerPort(UINT32 port, BOOLEAN onOff)
{
	ADEC_MODULE_ID	mixModule = ADEC_MODULE_MIX_0;
	MixCmdEnablePort	mixEnable;

	mixEnable.port = port;

	if(onOff == ON)
		mixEnable.enable = AUD_REN_PORT_ENABLE;
	else
		mixEnable.enable = AUD_REN_PORT_DISABLE;

	if(AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT, mixModule, sizeof(MixCmdEnablePort), &mixEnable))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT) Err\n", __FUNCTION__, __LINE__);
	}
}

static void _AUDIO_SetSRCFormat(UINT32 allocMod, UINT32 sampleFreq, UINT32 numOfChannel, UINT32 bitPerSample, UINT32 endianType, UINT32 signedType)
{
	SrcCmdSetAllfmt 	 srcSetFmt;
	SrcCmdSetOverProtect srcSetOverProtect;

	srcSetFmt.InFs		= sampleFreq;
	srcSetFmt.InCh		= numOfChannel;
	srcSetFmt.InFormat	= bitPerSample;
	srcSetFmt.InEndian	= endianType;	// 0 is little , 1 is big
	srcSetFmt.InSigned	= signedType;	// 0 is signed , 1 is unsigned
	srcSetFmt.OutFs		= LX_AUD_SAMPLING_FREQ_48_KHZ;
	srcSetFmt.OutCh		= AUD_REN_NUM_OF_CHANNEL_OF_SRC_MIX;
	srcSetFmt.OutFormat	= AUD_REN_BITS_PER_SAMPLE_OF_SRC_MIX;

	AUDIO_IMC_SendCmdParam(SRC_CMD_SET_ALLFMT, allocMod, sizeof(SrcCmdSetAllfmt), &srcSetFmt);

	srcSetOverProtect.over_protect = NOT_USE_OVERFLOW_PROTECTION;
	AUDIO_IMC_SendCmdParam(SRC_CMD_SET_OVERPROTECT, allocMod, sizeof(SrcCmdSetOverProtect), &srcSetOverProtect);

	return;
}

static void _AUDIO_SetMixerConfig(UINT32 port, UINT32 fade_length, UINT32 wait_length, UINT32 volume)
{
	ADEC_MODULE_ID	mixModule = ADEC_MODULE_MIX_0;

	MixCmdSetConfig		mixParam;
	MixCmdSetFadeCfg	mixFadeInOut;
	MixCmdSetWaitLength	mixWaitLength;
	//MixCmdSetMuteLength	mixMuteLength;

	_AUDIO_EnableMixerPort(port, AUD_REN_PORT_DISABLE);

	mixParam.port			= port;
	mixParam.num_of_channel	= AUD_REN_NUM_OF_CHANNEL_OF_SRC_MIX;
	mixParam.bit_per_sample	= AUD_REN_BITS_PER_SAMPLE_OF_SRC_MIX;
	mixParam.gain			= volume;

	if(AUDIO_IMC_SendCmdParam(MIX_CMD_SET_CONFIG, mixModule, sizeof(MixCmdSetConfig), &mixParam))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_SET_CONFIG) Err\n", __FUNCTION__, __LINE__);
	}

	// set fade in/out
	mixFadeInOut.port					= port;
	mixFadeInOut.enable_auto_fade_in	= FADE_IN_OUT_ENABLE_DEFAULT;
	mixFadeInOut.enable_auto_fade_out	= FADE_IN_OUT_ENABLE_DEFAULT;
	mixFadeInOut.fade_length_in_bit		= fade_length;
	if(AUDIO_IMC_SendCmdParam(MIX_CMD_SET_FADE_CFG, mixModule, sizeof(MixCmdSetFadeCfg), &mixFadeInOut))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_SET_FADE_CFG) Error\n", __FUNCTION__, __LINE__);
	}

	// set wait length of MIX
	mixWaitLength.port			= port;
	mixWaitLength.wait_length	= wait_length;
	if(AUDIO_IMC_SendCmdParam(MIX_CMD_SET_WAIT_LENGTH, mixModule, sizeof(MixCmdSetWaitLength), &mixWaitLength))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_SET_WAIT_LENGTH) Error\n", __FUNCTION__, __LINE__);
	}

#if 0
	mixMuteLength.port		  = port;
	mixMuteLength.mute_length = AUD_REN_INIT_MUTE_LENGTH_MIX;	//115ms

	if(AUDIO_IMC_SendCmdParam(MIX_CMD_SET_MUTE_LENGTH, mixModule, sizeof(MixCmdSetMuteLength), &mixMuteLength))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_SET_MUTE_LENGTH) Err\n", __FUNCTION__, __LINE__);
	}
#endif

	_AUDIO_EnableMixerPort(port, AUD_REN_PORT_ENABLE);

	return;
}

static SINT32 _AUDIO_RenDecInfoCb(void *_param, SINT32 _paramLen, void *_cbParam)
{
	ULONG	flags;

	UINT32 allocDev = AUD_DEV_REN0;

	UINT32 allocMod_SRC = ADEC_MODULE_NO_MOD;
	UINT32 allocMod_LIP = ADEC_MODULE_NO_MOD;

	LipsyncCmdSetFs			setEsLipsyncFs;

	DecEvtESDecInfoParam	*pEsInfoParam = (DecEvtESDecInfoParam*)_param;

	AUD_RENDER_INFO_T		*pRenderInfo = (AUD_RENDER_INFO_T*) _cbParam;
	LX_AUD_RENDER_PARAM_T	*pRenderParam = &(pRenderInfo->renderParam);

	allocDev = pRenderInfo->ui32AllocDev;

	// Print For Debug
	if(_paramLen != sizeof(DecEvtESDecInfoParam))
	{
		AUD_KDRV_ERROR("Ren Info : Param Length Error[Expected:%d][Input:%d]\n", sizeof(DecEvtESDecInfoParam), _paramLen);
		return RET_ERROR;
	}

	if(pEsInfoParam->sample_rate == LX_AUD_SAMPLING_FREQ_NONE)
	{
		AUD_KDRV_ERROR("Ren Info : Sampling Frequency Error[%d]\n", pEsInfoParam->sample_rate);
		return RET_ERROR;
	}

	if(pRenderInfo->renderParam.lipsyncType == LX_AUD_RENDER_LIPSYNC_PCM)
	{
		allocMod_SRC = AUDIO_GetModule(allocDev, LX_AUD_SRC1);

		if(allocMod_SRC == ADEC_MODULE_NO_MOD )
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[LX_AUD_SRC1]);
			return RET_ERROR;
		}

		//Set a SRC config if any value is changed.
		if( (pRenderParam->samplingFreq		!= pEsInfoParam->sample_rate)		\
		  ||(pRenderParam->ui32NumOfChannel != pEsInfoParam->num_of_channel)	\
		  ||(pRenderParam->ui32BitPerSample != pEsInfoParam->bit_per_sample)	\
		  ||(pRenderParam->endianType		!= pEsInfoParam->input_endian)		\
		  ||(pRenderParam->signedType		!= pEsInfoParam->input_signed) )
		{
			_AUDIO_SetSRCFormat(allocMod_SRC, 			  pEsInfoParam->sample_rate,	\
								pEsInfoParam->num_of_channel, pEsInfoParam->bit_per_sample,	\
								pEsInfoParam->input_endian,	  pEsInfoParam->input_signed);
		}

		/* Set a SPDIF sampling frequency and DSP SPDIF module to set Fs. */
		if(pRenderParam->samplingFreq != pEsInfoParam->sample_rate)
		{
			KDRV_AUDIO_UpdateSamplingFreq(pEsInfoParam->sample_rate);
		}
	}
	else
	{
		//Set a sampling frequency for SPDIF ES config if any value is changed.
		if(pRenderParam->samplingFreq != pEsInfoParam->sample_rate)
		{
			allocMod_LIP = AUDIO_GetModule(allocDev, LX_AUD_LIP_ES);

			if(allocMod_LIP == ADEC_MODULE_NO_MOD)
			{
				AUD_KDRV_ERROR("Module[%s] is not available \n", modTypeStr[LX_AUD_LIP_ES]);
				return RET_ERROR;
			}

			/* Set a current value */
			setEsLipsyncFs.Fs = pEsInfoParam->sample_rate;

			/* If lipsync type is ES, set a sampling frequency seeting to compute delay */
			if(AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_FS, allocMod_LIP, sizeof(LipsyncCmdSetFs), &setEsLipsyncFs) < 0)
			{
				AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_FS, LIP_%d) Error\n", __FUNCTION__, __LINE__, allocMod_LIP);
			}

			/* Set a SPDIF sampling frequency and DSP SPDIF module to set Fs. */
			KDRV_AUDIO_UpdateSamplingFreq(pEsInfoParam->sample_rate);

			/* Check a AAC audio codec and sampling frequency */
			if( (pEsInfoParam->media_type  == LX_AUD_CODEC_AAC || pEsInfoParam->media_type  == LX_AUD_CODEC_DTS)		\
			  &&(pEsInfoParam->sample_rate != LX_AUD_SAMPLING_FREQ_48_KHZ) )
			{
				//spin lock for protection
				spin_lock_irqsave(&gAudEventSpinLock, flags);

				//Set a audio GET event type for next event.
				gAudGetEvent[allocDev].allocDev  = allocDev;
				gAudGetEvent[allocDev].eventMsg |= LX_AUD_EVENT_DEC_AAC_PCM;

				//spin unlock for protection
				spin_unlock_irqrestore(&gAudEventSpinLock, flags);

				//Wake up poll event if allocated device and event message is set.
				if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
				  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_DEC_AAC_PCM) )
				{
					wake_up_interruptible_all(&gAudPollWaitQueue);
				}

				AUD_KDRV_DEBUG("Ren Info(%d) : SPDIF PCM Fs(%d)\n", allocDev, pEsInfoParam->sample_rate);
			}
		}
	}

	// Restart when sampling frequency changes.
	if(pRenderInfo->bStarted == TRUE)
	{
		if(pRenderParam->samplingFreq != pEsInfoParam->sample_rate)
		{
			AUDIO_StopRenderer(allocDev);
			AUDIO_FlushRenderer(allocDev);
			AUDIO_StartRenderer(allocDev);
		}
	}

	//Update a render information by decoder information.
	pRenderParam->ui32NumOfChannel = pEsInfoParam->num_of_channel;
	pRenderParam->ui32BitPerSample = pEsInfoParam->bit_per_sample;
	pRenderParam->samplingFreq 	   = pEsInfoParam->sample_rate;
	pRenderParam->endianType 	   = pEsInfoParam->input_endian;
	pRenderParam->signedType 	   = pEsInfoParam->input_signed;

	//Starts a render by decoder information.
	if(pRenderInfo->bStarted == FALSE)
		AUDIO_StartRenderer(allocDev);

	if((pEsInfoParam->media_type == (ADEC_MEDIA_TYPE)LX_AUD_CODEC_PCM)	\
	  &&(pRenderInfo->renderParam.lipsyncType == LX_AUD_RENDER_LIPSYNC_PCM))
	{
		AUD_KDRV_DEBUG("Ren Info(%d) : Fs(%d), Ch(%d), Bs(%d), En(%d), Si(%d)\n", \
						allocDev, pRenderParam->samplingFreq, pRenderParam->ui32NumOfChannel,	\
						pRenderParam->ui32BitPerSample, pRenderParam->endianType, pRenderParam->signedType);
	}
	else
	{
		AUD_KDRV_DEBUG("Ren Info(%d) : Fs(%d), Ch(%d), Bs(%d)\n", \
						allocDev, pRenderParam->samplingFreq, pRenderParam->ui32NumOfChannel, pRenderParam->ui32BitPerSample);
	}
	return RET_OK;
}

static SINT32 _AUDIO_RenBasetimeCb(void *_param, SINT32 _paramLen, void *_cbParam)
{
	LipsyncEvtNopcrBaseline	*pBasetime = (LipsyncEvtNopcrBaseline*)_param;
	AUD_RENDER_INFO_T		*pRenderInfo = (AUD_RENDER_INFO_T*) _cbParam;
	LX_AUD_RENDER_PARAM_BASETIME_T	basetimeParam;
	UINT32					allocDev = AUD_DEV_REN0;
	UINT32					ConnectedDev = AUD_DEV_DEC0;
	UINT32					i;
	SINT32					decIndex = 0;

	allocDev = pRenderInfo->ui32AllocDev;

	// Print For Debug
	if(_paramLen != sizeof(LipsyncEvtNopcrBaseline))
	{
		AUD_KDRV_ERROR("Ren Basetime : Param Length Error : [Expected:%d][Input:%d]\n", sizeof(LipsyncEvtNopcrBaseline), _paramLen);
		return RET_ERROR;
	}

	for(i = 0; i < AUD_RENDER_CONNECT_NUM; i++)
	{
		if(pRenderInfo->renderConnect[i].devType == LX_AUD_DEV_DEC)
		{
			ConnectedDev = pRenderInfo->renderConnect[i].connectDev;
		}
	}

	decIndex = ConnectedDev - AUD_DEV_DEC0;
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR(" decIndex[%d] is not available. \n", decIndex);
		return RET_ERROR;
	}

	BASE_AVLIPSYNC_LOCK();

	if(decIndex == 0)
	{
		if( (g_pVDEC_LipsyncReg->vdec_dec0_cbt == 0xFFFFFFFF)
		 || (g_pVDEC_LipsyncReg->vdec_dec0_sbt == 0xFFFFFFFF) )
		{
			basetimeParam.ui64ClockBaseTime  = (UINT64)(pBasetime->baseCT);
			basetimeParam.ui64StreamBaseTime = (UINT64)(pBasetime->baseST);
		}
		else
		{
			basetimeParam.ui64ClockBaseTime  = (UINT64)(g_pVDEC_LipsyncReg->vdec_dec0_cbt);
			basetimeParam.ui64StreamBaseTime = (UINT64)(g_pVDEC_LipsyncReg->vdec_dec0_sbt);
		}

		AUD_Wr(aud_dec0_cbt, (UINT32)(basetimeParam.ui64ClockBaseTime));
		AUD_WrFL(aud_dec0_cbt);

		AUD_Wr(aud_dec0_sbt, (UINT32)(basetimeParam.ui64StreamBaseTime));
		AUD_WrFL(aud_dec0_sbt);
	}
	else
	{
		if((g_pVDEC_LipsyncReg->vdec_dec1_cbt == 0xFFFFFFFF)
		 || (g_pVDEC_LipsyncReg->vdec_dec1_sbt == 0xFFFFFFFF))
		{
			basetimeParam.ui64ClockBaseTime  = (UINT64)(pBasetime->baseCT);
			basetimeParam.ui64StreamBaseTime = (UINT64)(pBasetime->baseST);
		}
		else
		{
			basetimeParam.ui64ClockBaseTime  = (UINT64)(g_pVDEC_LipsyncReg->vdec_dec1_cbt);
			basetimeParam.ui64StreamBaseTime = (UINT64)(g_pVDEC_LipsyncReg->vdec_dec1_sbt);
		}

		AUD_Wr(aud_dec1_cbt, (UINT32)(basetimeParam.ui64ClockBaseTime));
		AUD_WrFL(aud_dec1_cbt);

		AUD_Wr(aud_dec1_sbt, (UINT32)(basetimeParam.ui64StreamBaseTime));
		AUD_WrFL(aud_dec1_sbt);
	}

	AUDIO_SetBasetime(allocDev, &basetimeParam);

	BASE_AVLIPSYNC_UNLOCK();

	AUD_KDRV_DEBUG("Ren Basetime(%d) : Bst(0x%X), Bct(0x%X)\n", allocDev, pBasetime->baseST, pBasetime->baseCT);
	return RET_OK;
}

/**
 * Present End Callback function.
 * @param 	_param			[out] parameters.
 * @param 	_paramLen		[out] length of parameters.
 * @param 	_cbParam		[in] callback parameters.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		AUDIO_SetRendererParam
 */
static SINT32 _AUDIO_RenPresentEndCb(void *_param, SINT32 _paramLen, void *_cbParam)
{
	UINT32	allocDev = AUD_DEV_REN0;
	SINT32	renIndex = 0;
	ULONG	flags;

	LipsyncEvtPresentEnd	*pPresentEnd = (LipsyncEvtPresentEnd *)_param;
	AUD_RENDER_INFO_T		*pRenderInfo = (AUD_RENDER_INFO_T *)_cbParam;

	allocDev = pRenderInfo->ui32AllocDev;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR("renIndex[%d] is not available.\n", renIndex);
		return RET_ERROR;
	}

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Set a audio GET event type for next event.
	gAudGetEvent[allocDev].allocDev  = allocDev;
	gAudGetEvent[allocDev].eventMsg |= LX_AUD_EVENT_PRESENT_END;

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	//Wake up poll event if allocated device and event message is set.
	if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
	  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_PRESENT_END) )
	{
		wake_up_interruptible_all(&gAudPollWaitQueue);
	}

	AUD_KDRV_DEBUG("Ren(%d) PresentEnd : remain %d ms\n", allocDev, pPresentEnd->remain_ms);
	return RET_OK;
}

/**
 * Underflow Callback function.
 * @param 	_param			[out] parameters.
 * @param 	_paramLen		[out] length of parameters.
 * @param 	_cbParam		[in] callback parameters.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		AUDIO_SetRendererParam
 */
static SINT32 _AUDIO_RenUnderflowCb(void *_param, SINT32 _paramLen, void *_cbParam)
{
	UINT32	allocDev = AUD_DEV_REN0;
	SINT32	renIndex = 0;
	ULONG	flags;

	LipsyncEvtUnderflow		*pUnderflow = (LipsyncEvtUnderflow *)_param;
	AUD_RENDER_INFO_T		*pRenderInfo = (AUD_RENDER_INFO_T *)_cbParam;

	allocDev = pRenderInfo->ui32AllocDev;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR("renIndex[%d] is not available.\n", renIndex);
		return RET_ERROR;
	}

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Set a audio GET event type for next event.
	gAudGetEvent[allocDev].allocDev  = allocDev;
	gAudGetEvent[allocDev].eventMsg |= LX_AUD_EVENT_UNDERFLOW;

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	//Wake up poll event if allocated device and event message is set.
	if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
	  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_UNDERFLOW) )
	{
		wake_up_interruptible_all(&gAudPollWaitQueue);
	}

	AUD_KDRV_DEBUG("Ren(%d) Underflow : temp %x.\n", allocDev, pUnderflow->tmp);
	return RET_OK;
}

/**
 * Alloc CTRL_SRC Module.
 * @param 	modID			[in] Module T.
 * @return 	if is used - TRUE, else - FALSE.
 * @see		AUDIO_ConnectRenderer
 */
static LX_AUD_ALLOC_MOD_T _AUDIO_AllocCtrlSrcModule(void)
{
	UINT32	i;
	LX_AUD_ALLOC_MOD_T	modID = ADEC_MODULE_NO_MOD;

	for(i = 0; i < stFwRmModType[LX_AUD_CTRLSRC].ModNum; i++)
	{
		if(_gbUsedCtrlSrc[i] == FALSE)
		{
			_gbUsedCtrlSrc[i] = TRUE;
			modID = ADEC_MODULE_CTRLSRC_0 + i;
			break;
		}
	}

	AUD_KDRV_DEBUG("%s modID(%d) is alloced.\n", __F__, modID);

	return modID;
}

/**
 * Free CTRL_SRC Module.
 * @param 	modID			[in] Module T.
 * @return 	if is used - TRUE, else - FALSE.
 * @see		AUDIO_ConnectRenderer
 */
static void _AUDIO_FreeCtrlSrcModule(ADEC_MODULE_ID modID)
{
	if((modID < ADEC_MODULE_CTRLSRC_0) || (modID > (ADEC_MODULE_CTRLSRC_0 + stFwRmModType[LX_AUD_CTRLSRC].ModNum - 1)))
	{
		AUD_KDRV_DEBUG("%s.%d: Invalid CTRL_SRC module(%d)!!!\n", __FUNCTION__, __LINE__, modID);
		return;
	}

	_gbUsedCtrlSrc[modID - ADEC_MODULE_CTRLSRC_0] = FALSE;

	AUD_KDRV_DEBUG("%s.%d: modID(%d) is freed\n", __F__, __L__, modID);

	return;
}

/**
 * Alloc Renderer Module.
 * @param 	modID			[in] Module ID.
 * @return 	if is used - TRUE, else - FALSE.
 * @see		AUDIO_ConnectRenderer
 */
static SINT32 _AUDIO_SetCtrlSrc(AUD_RENDER_INFO_T *pRenderInfo)
{
	UINT32							allocMod_SRC = ADEC_MODULE_NO_MOD;
	UINT32							allocMod_CTRL_SRC = ADEC_MODULE_NO_MOD;
	CtrlsrcCmdSetSrcModule			setSrcModule;
	CtrlsrcCmdSetIntInfo			setIntInfo;
	CtrlsrcCmdSetSrcrunningmode		setRuningMode;

	if(pRenderInfo==NULL)
	{
		AUD_KDRV_ERROR("%s.%d: pRenderInfo is NULL!!!\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	allocMod_SRC = AUDIO_HasThisModuleType(pRenderInfo->ui32AllocDev, LX_AUD_SRC1);
	if ((allocMod_SRC < ADEC_MODULE_SRC_0) || (allocMod_SRC > (ADEC_MODULE_SRC_0 + stFwRmModType[LX_AUD_SRC1].ModNum -1)))
	{
		AUD_KDRV_DEBUG("%s.%d: Invalid SRC module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_SRC);
		return RET_ERROR;
	}

	allocMod_CTRL_SRC = _AUDIO_AllocCtrlSrcModule();
	if(allocMod_CTRL_SRC == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_DEBUG("%s.%d: All CTRL_SRC modules are already used!!!\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	setSrcModule.src_module_id = allocMod_SRC;
	if(AUDIO_IMC_SendCmdParam(CTRLSRC_CMD_SET_SRC_MODULE, allocMod_CTRL_SRC, sizeof(CtrlsrcCmdSetSrcModule), &setSrcModule) < 0)
	{
		AUD_KDRV_DEBUG("%s.%d: AUDIO_IMC_SendCmdParam(CTRLSRC_CMD_SET_SRC_MODULE) Error\n", __FUNCTION__, __LINE__);
	}

	if(pRenderInfo->renderParam.input == LX_AUD_INPUT_SIF)
	{
		setIntInfo.RefInt	= AUD_INT_AADIN;
		setIntInfo.TarInt	= AUD_INT_PCM;
	}
	else if(pRenderInfo->renderParam.input == LX_AUD_INPUT_HDMI)
	{
		setIntInfo.RefInt	= AUD_INT_HDMIIN;
		setIntInfo.TarInt	= AUD_INT_PCM;
	}

	if(AUDIO_IMC_SendCmdParam(CTRLSRC_CMD_SET_INTINFO, allocMod_CTRL_SRC, sizeof(CtrlsrcCmdSetIntInfo), &setIntInfo) < 0)
	{
		AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CTRLSRC_CMD_SET_INTINFO) Error\n", __FUNCTION__, __LINE__);
	}

	if(pRenderInfo->renderParam.bSetMainRen)
	{
		setRuningMode.src_running_mode = 0;
	}
	else
	{
		setRuningMode.src_running_mode = 1;
	}

	if(AUDIO_IMC_SendCmdParam(CTRLSRC_CMD_SET_SRCRUNNINGMODE, allocMod_CTRL_SRC, sizeof(CtrlsrcCmdSetSrcrunningmode), &setRuningMode) < 0)
	{
		AUD_KDRV_DEBUG("%s.%d: AUDIO_IMC_SendCmdParam(CTRLSRC_CMD_SET_SRCRUNNINGMODE) Error\n", __FUNCTION__, __LINE__);
	}

	pRenderInfo->ctrlSrcInfo.bCtrlSrcOnOff = TRUE;
	pRenderInfo->ctrlSrcInfo.allocCtrlSrc = allocMod_CTRL_SRC;

	return RET_OK;
}

static SINT32 AUDIO_FeedRen(UINT32 allocDev, LX_AUD_RENDER_FEED_T *pRenFeed)
{
	SINT32					retVal = 0;
	ADEC_BUF_T				*pWriterStruct = NULL;
	UINT32					ui32FreeAuCount;
	UINT64					ui64TS90kHzTick;
	ADEC_AU_INFO_T			info = {0, };

	LX_AUD_RENDER_FEED_T	renFeedData;
	SINT32					renIndex = 0;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	pWriterStruct = _AUDIO_GetRendererWriteStructure(allocDev);
	if(pWriterStruct == NULL)
	{
		AUD_KDRV_ERROR("Feed : pWriterStruct is NULL !!!\n" );
		return RET_ERROR;
	}

	//Check a repeat number and buffer status to initialize audio buffer
	if(_gRenderInfo[renIndex].bBufferRepeat == TRUE)
	{
		//buffer init : buffer is not flushed if repeat is set previously.
		pWriterStruct->init(pWriterStruct);

		//Clear a buffer repeat variable.
		_gRenderInfo[renIndex].bBufferRepeat = FALSE;
	}

	memcpy(&renFeedData,pRenFeed,sizeof(LX_AUD_RENDER_FEED_T));

	if(renFeedData.ui32BufferSize > 0 || renFeedData.statusBuffer == LX_AUD_BUFFER_END)
	{
		AUD_KDRV_PRINT("Feed => Free:%d, Used:%d\n", pWriterStruct->get_free_size(pWriterStruct), pWriterStruct->get_used_size(pWriterStruct));

		/* Compute free au count */
		ui32FreeAuCount = pWriterStruct->get_max_au(pWriterStruct) - pWriterStruct->get_au_cnt(pWriterStruct);

		/* Check buffer overflow and AUI overflow */
		if( (pWriterStruct->get_free_size(pWriterStruct) >=  renFeedData.ui32BufferSize) &&(ui32FreeAuCount > 1) )
		{
			if (renFeedData.ui32BufferSize > 0)
			{
				ui64TS90kHzTick = renFeedData.ui64TimeStamp;
				if(ui64TS90kHzTick != 0xFFFFFFFFFFFFFFFFULL)
				{
					ui64TS90kHzTick *= 9;

					do_div(ui64TS90kHzTick, 100000);	// = Xns * 90 000 / 1 000 000 000
				}
				//Set NEW AUI info.
				info.size			= (UINT64)renFeedData.ui32BufferSize;
				info.timestamp		= (UINT32)(ui64TS90kHzTick) & TIMESTAMP_MASK;	//28 bit
				info.gstc			= 0;
				info.index			= _gRenderInfo[renIndex].renderStatus.ui32FeededIndex;
				info.error			= 0;
				info.discontinuity	= 0;
				info.lastAu			= 0;

				AUD_KDRV_PRINT("pts[%10d], dts[%10d], idx[%5d], size[%5llu]\n", info.timestamp, info.gstc, info.index, info.size);

				//Write AUI info.
				retVal = pWriterStruct->create_new_au(&info, pWriterStruct);
				if(retVal != RET_OK)
				{
					AUD_KDRV_ERROR("Feed => create_new_au(ret = %d, cnt = %d, free = %d)!!!\n",	\
								retVal, pWriterStruct->get_au_cnt(pWriterStruct), pWriterStruct->get_free_size(pWriterStruct));
					return RET_ERROR;
				}

			    //Write Mix data
			    retVal = pWriterStruct->write_data(renFeedData.pBuffer, renFeedData.ui32BufferSize, pWriterStruct);
				if(retVal != RET_OK)
				{
					AUD_KDRV_ERROR("Feed => write_data(ret = %d, cnt = %d, free = %d)!!!\n",	\
								retVal, pWriterStruct->get_au_cnt(pWriterStruct), pWriterStruct->get_free_size(pWriterStruct));
					return RET_ERROR;
				}
			}

			//Check buffer status
			if(renFeedData.statusBuffer == LX_AUD_BUFFER_END)
			{
				//Set last buffer
				retVal = BufHelper_SetLast(pWriterStruct);
				if(retVal != RET_OK)
				{
					AUD_KDRV_ERROR("Feed => BufHelper_SetLast(ret = %d, free = %d, cnt = %d)!!!\n",	\
								retVal, pWriterStruct->get_free_size(pWriterStruct), pWriterStruct->get_au_cnt(pWriterStruct));
					return RET_ERROR;
				}

				//Set a repeat function and variable for buffer init.
				if(renFeedData.ui32RepeatNumber > 1)
				{
					_gRenderInfo[renIndex].bBufferRepeat = TRUE;

					(void)pWriterStruct->set_repeat(renFeedData.ui32RepeatNumber - 1, pWriterStruct);
				}
			}

			_gRenderInfo[renIndex].renderStatus.ui32FeededIndex++;
			if(_gRenderInfo[renIndex].renderStatus.ui32FeededIndex == MPB_AUI_INDEX_COUNT)
				_gRenderInfo[renIndex].renderStatus.ui32FeededIndex = 0;

			_gRenderInfo[renIndex].renderStatus.ui32FeededCount++;
		}
		else
		{
			AUD_KDRV_DEBUG("Feed => free = %d, count = %d!!!\n", 	\
						pWriterStruct->get_free_size(pWriterStruct), pWriterStruct->get_au_cnt(pWriterStruct));

			retVal = RET_ERROR;
		}
	}
	else
	{
		AUD_KDRV_ERROR("Feed => renFeedData.ui32BufferSize = %u!!!\n", renFeedData.ui32BufferSize);
		retVal = RET_ERROR;
	}
	AUD_KDRV_PRINT("%s.%d:bufSize=%u, bufStatus=%d, TS=%llu\n", __F__, __L__, renFeedData.ui32BufferSize, renFeedData.statusBuffer, renFeedData.ui64TimeStamp);

	return retVal;
}

/**
 * Start for renderer.
 * @see
*/
static SINT32 AUDIO_StartRenderer (UINT32 allocDev)
{
	UINT32			allocModNum;
	LX_AUD_MOD_T	*pOwnMods;
	UINT32			i;
	SINT32			retVal = RET_OK;
	SINT32			renIndex = 0;

	LX_AUD_RENDER_PARAM_T	*pRenderParam = NULL;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available.\n", renIndex);
		return RET_ERROR;
	}

	pRenderParam = &(_gRenderInfo[renIndex].renderParam);

	if(pRenderParam->samplingFreq == LX_AUD_SAMPLING_FREQ_NONE)
	{
		AUD_KDRV_PRINT("Sampling Frequency is not available.[%d]\n",allocDev );
		return RET_OK;
	}
	else
		AUD_KDRV_PRINT("Sampling Frequency is available.[%d]\n",allocDev );

	//get alloc module info in given device node
	AUDIO_GetAllocInfo(allocDev, &allocModNum, &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if(pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX )
		{
			if( (pOwnMods[i].mod >= (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_BYPASS_00)	\
			  &&(pOwnMods[i].mod <= (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_BYPASS_11) )
			{
				//Send a IMC command - START
				retVal = AUDIO_IMC_SendCmd(ADEC_CMD_START, pOwnMods[i].mod);
			}
			else if (pOwnMods[i].mod != (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_RTS)
			{
				//Send a IMC command - INIT & START(need to init SRC before start SRC by gunho.song)
				retVal = AUDIO_IMC_SendCmd(ADEC_CMD_INIT, pOwnMods[i].mod);
				retVal = AUDIO_IMC_SendCmd(ADEC_CMD_START, pOwnMods[i].mod);
			}

			AUD_KDRV_PRINT("Send START CMD [%s] [%d] \n", allocMod_Str[pOwnMods[i].mod],allocDev);
		}
	}

	// set RTS mode
	if (_gRenderInfo[renIndex].bRTSOnOff == TRUE)
	{
		RtsCmdSetThreashold		rtsThreshold;
		RtsCmdSetOutFreq		rtsOutFreq;
		RtsCmdSetPortMultiplier	rtsPortMultiplier;

		// set RTS threshold
		rtsThreshold.upper_th		= RTS_THRESHOLD_UPPER;
		rtsThreshold.lower_th		= RTS_THRESHOLD_LOWER;
		rtsThreshold.recover_upper	= RTS_RECOVER_UPPER;
		rtsThreshold.recover_lower	= RTS_RECOVER_LOWER;
		if (AUDIO_IMC_SendCmdParam(RTS_CMD_SET_THRESHOLD, ADEC_MODULE_RTS, sizeof(RtsCmdSetThreashold), &rtsThreshold) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(RTS_CMD_SET_THRESHOLD, RTS) Error\n", __FUNCTION__, __LINE__);
		}

		// set RTS output frequency
		rtsOutFreq.fast_freq	= RTS_FAST_FREQ;
		rtsOutFreq.normal_freq	= RTS_NORMAL_FREQ;
		rtsOutFreq.slow_freq	= RTS_SLOW_FREQ;
		if (AUDIO_IMC_SendCmdParam(RTS_CMD_SET_OUT_FREQ, ADEC_MODULE_RTS, sizeof(RtsCmdSetOutFreq), &rtsOutFreq) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(RTS_CMD_SET_OUT_FREQ, RTS) Error\n", __FUNCTION__, __LINE__);
		}

		// set port multplier - only input port 0 (the input port of SRC module)
		rtsPortMultiplier.ref_port		= MOD_REF_PORT(0);
		rtsPortMultiplier.numerator		= 384000;			// 48000Hz * 2ch * 32bits
		rtsPortMultiplier.denominator	= (UINT32)(pRenderParam->samplingFreq * pRenderParam->ui32NumOfChannel * (pRenderParam->ui32BitPerSample >> 3));
		if (AUDIO_IMC_SendCmdParam(RTS_CMD_SET_PORT_MULTPLIER, ADEC_MODULE_RTS, sizeof(RtsCmdSetPortMultiplier), &rtsPortMultiplier) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(RTS_CMD_SET_PORT_MULTPLIER, RTS) Error\n", __FUNCTION__, __LINE__);
		}

		// INIT & START
		//AUDIO_IMC_SendCmd(ADEC_CMD_INIT, ADEC_MODULE_RTS);
		if (AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_RTS) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmd(ADEC_CMD_START, RTS) Error\n", __FUNCTION__, __LINE__);
		}
	}

	if(_gRenderInfo[renIndex].ctrlSrcInfo.bCtrlSrcOnOff == TRUE)
	{
		if (AUDIO_IMC_SendCmd(ADEC_CMD_START, _gRenderInfo[renIndex].ctrlSrcInfo.allocCtrlSrc) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmd(ADEC_CMD_START, CTRLSRC%d) Error\n", __FUNCTION__, __LINE__, _gRenderInfo[renIndex].ctrlSrcInfo.allocCtrlSrc);
		}
	}

	_gRenderInfo[renIndex].bStarted = TRUE;

	return retVal;
}


static SINT32 AUDIO_StopRenderer (UINT32 allocDev)
{
	UINT32			allocModNum;
	LX_AUD_MOD_T	*pOwnMods;
	UINT32			i;
	SINT32			retVal = RET_OK;

	UINT32			ConnectedDev = AUD_DEV_DEC0;
	SINT32			renIndex = 0;
	SINT32			decIndex = 0;

	AUD_RENDER_INFO_T	*pRenderInfo = NULL;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available.\n", renIndex);
		return RET_ERROR;
	}

	//get alloc module info in given device node
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if( pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX )
		{
			//Send a IMC command - STOP
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_STOP, pOwnMods[i].mod);		// need to init SRC before start SRC by gunho.song
			AUD_KDRV_PRINT("Send STOP CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
		}
	}

	pRenderInfo = &_gRenderInfo[renIndex];

	if(pRenderInfo->bRTSOnOff == TRUE)
	{
		// STOP
		if(AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_RTS) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmd(ADEC_CMD_STOP, RTS) Error\n", __FUNCTION__, __LINE__);
		}
	}

	if(pRenderInfo->ctrlSrcInfo.bCtrlSrcOnOff == TRUE)
	{
		if (AUDIO_IMC_SendCmd(ADEC_CMD_STOP, pRenderInfo->ctrlSrcInfo.allocCtrlSrc) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmd(ADEC_CMD_STOP, CTRLSRC%d) Error\n", __FUNCTION__, __LINE__, pRenderInfo->ctrlSrcInfo.allocCtrlSrc);
		}
	}

	for(i = 0; i < AUD_RENDER_CONNECT_NUM; i++)
	{
		if(pRenderInfo->renderConnect[i].devType == LX_AUD_DEV_DEC)
		{
			ConnectedDev = pRenderInfo->renderConnect[i].connectDev;
		}
	}

	decIndex = GET_DEC_INDEX(ConnectedDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR(" decIndex[%d] is not available. \n", decIndex);
		return RET_ERROR;
	}

	BASE_AVLIPSYNC_LOCK();

	//Clear & save a av lip sync register value.
	if(decIndex == 0)
	{
		// Set DEC0 Clock Basetime
		AUD_Wr(aud_dec0_cbt, 0xFFFFFFFF);
		AUD_WrFL(aud_dec0_cbt);

		// Set DEC0 Stream Basetime
		AUD_Wr(aud_dec0_sbt, 0xFFFFFFFF);
		AUD_WrFL(aud_dec0_sbt);
	}
	else
	{
		// Set DEC1 Clock Basetime
		AUD_Wr(aud_dec1_cbt, 0xFFFFFFFF);
		AUD_WrFL(aud_dec1_cbt);

		// Set DEC1 Stream Basetime
		AUD_Wr(aud_dec1_sbt, 0xFFFFFFFF);
		AUD_WrFL(aud_dec1_sbt);
	}

	BASE_AVLIPSYNC_UNLOCK();

	return retVal;
}

static SINT32 AUDIO_FlushRenderer (UINT32 allocDev)
{
	UINT32			allocModNum;
	LX_AUD_MOD_T	*pOwnMods;
	UINT32			i;
	ImcCmdFlushParam	flushParam;
	SINT32			retVal = RET_OK;

	if(allocDev < AUD_DEV_REN0 || allocDev > AUD_DEV_REN11)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}

	//get alloc module info in given device node
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		//Send a IMC command - FLUSH
		if( pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T) ADEC_MODULE_MAX)
		{
			memset(&flushParam, 0, sizeof(ImcCmdFlushParam));
			flushParam.num_of_port	= 1;
			flushParam.port_list[0]	= MOD_IN_PORT(0);

			retVal = AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, pOwnMods[i].mod, sizeof(ImcCmdFlushParam), &flushParam);
			AUD_KDRV_PRINT("Send FLUSH CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
		}
	}

	return retVal;
}

/**
 * Sets volume for renderer.
 * Controls the volume function.
 * @see
*/
static SINT32 AUDIO_SetRendererVolume (UINT32 allocDev, UINT32 volume)
{
	SINT32						renIndex = 0;
	MixCmdSetGain				SetMixGain;
	ADEC_MODULE_ID				mixModule = ADEC_MODULE_MIX_0;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	if(_gRenderInfo[renIndex].ui32MixerPort != AUD_REN_DEFULT_PORT)
	{
		SetMixGain.port		= _gRenderInfo[renIndex].ui32MixerPort;
		SetMixGain.gain		= volume;

		if(AUDIO_IMC_SendCmdParam(MIX_CMD_SET_GAIN, mixModule, sizeof(MixCmdSetGain), &SetMixGain))
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_SET_CONFIG) Err\n", __FUNCTION__, __LINE__);
		}
	}

	_gRenderInfo[renIndex].ui32Volume = volume;

	AUD_KDRV_PRINT("%s : vol %x \n", __F__, volume);
	return RET_OK;
}

/**
 * Sets the AV Lipsync mechanism.
 * Controls the lipsync function manually.
 * @see
*/
static SINT32 AUDIO_SetLipsync (UINT32 allocDev,  LX_AUD_RENDER_PARAM_LIPSYNC_T *pParamLipsync)
{
	LipsyncCmdSetBound	setLipsyncBound;
	LipsyncCmdSetFs		setEsLipsyncFs;

	SINT32				renIndex = 0;
	LX_AUD_MOD_TYPE_T	modType;

	UINT32 allocMod_LIP= ADEC_MODULE_NO_MOD;

	if(pParamLipsync == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: pParamLipsync is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	if(_gRenderInfo[renIndex].renderParam.lipsyncType == LX_AUD_RENDER_LIPSYNC_PCM)
		modType = LX_AUD_LIP;
	else
		modType = LX_AUD_LIP_ES;

	allocMod_LIP = AUDIO_GetModule(allocDev, modType);
	if(allocMod_LIP == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modType]);
		return RET_ERROR;
	}

	setLipsyncBound.ubound = pParamLipsync->ui32Ubound;
	setLipsyncBound.lbound = pParamLipsync->ui32Lbound;
	setLipsyncBound.offset = pParamLipsync->ui32Offset;
	setLipsyncBound.freerunubound = pParamLipsync->ui32Freerunubound;
	setLipsyncBound.freerunlbound = pParamLipsync->ui32Freerunlbound;

	if(AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_BOUND, allocMod_LIP, sizeof(LipsyncCmdSetBound), &setLipsyncBound) < 0)
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_BOUND, LIP_0) Error\n", __FUNCTION__, __LINE__);
	}

	/* If lipsync type is ES, set a sampling frequency seeting to compute delay */
	if(modType == LX_AUD_LIP_ES)
	{
		/* Set a default value */
		setEsLipsyncFs.Fs = 48000;

		if(AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_FS, allocMod_LIP, sizeof(LipsyncCmdSetFs), &setEsLipsyncFs) < 0)
		{
			AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_FS, LIP_%d) Error\n", __FUNCTION__, __LINE__, allocMod_LIP);
		}
	}

	_gRenderInfo[renIndex].renderLipsync.ui32Ubound = pParamLipsync->ui32Ubound;
	_gRenderInfo[renIndex].renderLipsync.ui32Lbound = pParamLipsync->ui32Lbound;
	_gRenderInfo[renIndex].renderLipsync.ui32Offset = pParamLipsync->ui32Offset;
	_gRenderInfo[renIndex].renderLipsync.ui32Freerunubound = pParamLipsync->ui32Freerunubound;
	_gRenderInfo[renIndex].renderLipsync.ui32Freerunlbound = pParamLipsync->ui32Freerunlbound;

	return RET_OK;
}

/**
 * Sets the AV Lipsync mechanism.
 * Controls the lipsync function manually.
 * @see
*/
static SINT32 AUDIO_EnableLipsync (UINT32 allocDev, UINT32 bOnOff)
{
	UINT32		allocMod_LIP = ADEC_MODULE_NO_MOD;
	LipsyncCmdSetOnoff	setLipsyncOnOff;

	LX_AUD_MOD_TYPE_T	modType;
	SINT32	renIndex;

	AUD_KDRV_PRINT("%s.%d: set lipsync to %s\n", __FUNCTION__, __LINE__, (bOnOff == TRUE ? "On" : "Off"));

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	if(_gRenderInfo[renIndex].renderParam.lipsyncType == LX_AUD_RENDER_LIPSYNC_PCM)
		modType = LX_AUD_LIP;
	else
		modType = LX_AUD_LIP_ES;

	allocMod_LIP = AUDIO_GetModule(allocDev, modType);
	if(allocMod_LIP == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modType]);
		return RET_ERROR;
	}

	setLipsyncOnOff.onoff = bOnOff;

	if(AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_ONOFF, allocMod_LIP, sizeof(LipsyncCmdSetOnoff), &setLipsyncOnOff) < 0)
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_ONOFF, LIP) Error\n", __FUNCTION__, __LINE__);
	}

	_gRenderInfo[renIndex].bLipsyncOnOff = bOnOff;

	return RET_OK;
}

/**
 * Sets clock ID for AV Lipsync.
 * Controls the AV Lipsync function.
 * @see
*/
static SINT32 AUDIO_SetClockId (UINT32 allocDev, UINT32 clockId)
{
	// TODO: 정리 필요

	return RET_OK;
}

/**
 * Sets Rate Parameters for Clock.
 * Controls the AV Lipsync function.
 * @see
*/
static SINT32 AUDIO_SetRate (UINT32 allocDev, LX_AUD_RENDER_PARAM_RATE_T *pParamRate)
{
	// TODO: 정리 필요

	return RET_OK;
}

/**
 * Sets Basetime Parameters for Clock.
 * Controls the AV Lipsync function.
 * @see
*/
static SINT32 AUDIO_SetBasetime (UINT32 allocDev, LX_AUD_RENDER_PARAM_BASETIME_T *pParamBasetime)
{
	UINT32				allocMod_LIP = ADEC_MODULE_NO_MOD;
	LipsyncCmdSetBase	basetime;
	LX_AUD_MOD_TYPE_T	modType;
	SINT32				renIndex;

	if(pParamBasetime == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: pParamBasetime is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	if(_gRenderInfo[renIndex].renderParam.lipsyncType == LX_AUD_RENDER_LIPSYNC_PCM)
		modType = LX_AUD_LIP;
	else
		modType = LX_AUD_LIP_ES;

	allocMod_LIP = AUDIO_GetModule(allocDev, modType);
	if(allocMod_LIP == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modType]);
		return RET_ERROR;
	}

	basetime.clockbase	= (UINT32)(pParamBasetime->ui64ClockBaseTime & TIMESTAMP_MASK);
	basetime.streambase	= (UINT32)(pParamBasetime->ui64StreamBaseTime & TIMESTAMP_MASK);
	AUD_KDRV_ERROR("%s.%d: basetime - stream(0x%08X), clock(0x%08X)\n", __FUNCTION__, __LINE__, basetime.streambase, basetime.clockbase);

	AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_BASE, allocMod_LIP, sizeof(LipsyncCmdSetBase), &basetime);

	return RET_OK;
}

/**
 * Sets Clock Type Parameters for lipcync.
 * Controls the AV Lipsync function.
 * @see
*/
static SINT32 AUDIO_SetClockType (UINT32 allocDev, LX_AUD_RENDER_CLK_TYPE_T clockType)
{
	UINT32					allocMod_LIP;
	SINT32					renIndex;
	LipsyncCmdSetclocktype	setLipsyncClockType;
	LX_AUD_MOD_TYPE_T		modType;
	AUD_RENDER_INFO_T		*pRenderInfo = NULL;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	pRenderInfo = &_gRenderInfo[renIndex];

	if(pRenderInfo->renderParam.lipsyncType == LX_AUD_RENDER_LIPSYNC_PCM)
		modType = LX_AUD_LIP;
	else
		modType = LX_AUD_LIP_ES;

	allocMod_LIP = AUDIO_GetModule(allocDev, modType);
	if(allocMod_LIP == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modType]);
		return RET_ERROR;
	}

	setLipsyncClockType.clocktype = clockType;
 	AUDIO_IMC_SendCmdParam(LIPSYNC_CMD_SET_CLOCKTYPE, allocMod_LIP, sizeof(LipsyncCmdSetclocktype), &setLipsyncClockType);

	// Register Basetime
	if(clockType == LX_AUD_RENDER_CLK_TYPE_NO_PCR)
	{
		_AUDIO_RegisterRendererNoti(pRenderInfo, (PFN_ImcNoti)_AUDIO_RenBasetimeCb, allocMod_LIP, LIPSYNC_EVT_NOPCR_BASELINE, IMC_ACTION_ONCE, 1);
	}

	// Register Underflow
	if((clockType == LX_AUD_RENDER_CLK_TYPE_GSTC) && (modType == LX_AUD_LIP))
	{
		_AUDIO_RegisterRendererNoti(pRenderInfo, (PFN_ImcNoti)_AUDIO_RenUnderflowCb, allocMod_LIP, LIPSYNC_EVT_UNDERFLOW, IMC_ACTION_REPEAT, 1);
	}

	pRenderInfo->renderClockType = clockType;

	AUD_KDRV_PRINT("%s : Dev %x, clocktype %d\n", __F__, allocDev, clockType);

	return RET_OK;
}

/**
 * Sets Codec Parameters for Renderer.
 * Controls the Renderer Codec Param function.
 * @see
*/
static SINT32 AUDIO_SetRendererParam (UINT32 allocDev, LX_AUD_RENDER_PARAM_T *pParamCodec)
{
	LX_AUD_MOD_TYPE_T			modTypeToAlloc;

	UINT32						allocMod_IEC = ADEC_MODULE_NO_MOD, allocMod_SRC = ADEC_MODULE_NO_MOD, allocMod_LIP = ADEC_MODULE_NO_MOD;
	UINT32						allocMod_LIP_ES = ADEC_MODULE_NO_MOD;
	#ifdef ENABLE_SOLA
	UINT32						allocMod_SOLA = ADEC_MODULE_NO_MOD;
	#endif

	LX_AUD_ALLOC_FREE_INFO_T	*allocDEV;
	SINT32						renIndex = 0;
	AUD_RENDER_INFO_T			*pRenderInfo = NULL;

	AUD_KDRV_RMD("AUDIO_SetRendererParamCodec  allocDev[%s:%d] \n",allocDev_Str[allocDev],allocDev);

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	pRenderInfo = &_gRenderInfo[renIndex];

	/* Copy a renderer param to global variable. */
	pRenderInfo->renderParam.input				= pParamCodec->input;
	pRenderInfo->renderParam.lipsyncType		= pParamCodec->lipsyncType;
	pRenderInfo->renderParam.ui32NumOfChannel	= pParamCodec->ui32NumOfChannel;
	pRenderInfo->renderParam.ui32BitPerSample	= pParamCodec->ui32BitPerSample;
	pRenderInfo->renderParam.samplingFreq		= pParamCodec->samplingFreq;
	pRenderInfo->renderParam.endianType			= pParamCodec->endianType;	///< the endian of PCM
	pRenderInfo->renderParam.signedType			= pParamCodec->signedType;	///< the signed of PCM
	pRenderInfo->renderParam.bSetMainRen		= pParamCodec->bSetMainRen;	///< Sub Ren Mode

	if(pParamCodec->lipsyncType ==  LX_AUD_RENDER_LIPSYNC_ES)
	{
		modTypeToAlloc = LX_AUD_IEC;

		allocMod_IEC = AUDIO_AllocModule(allocDev,modTypeToAlloc , 0);
		if(allocMod_IEC == ADEC_MODULE_NO_MOD )
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
			return RET_ERROR;
		}

		AUD_KDRV_RMD("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_IEC]);

		allocDEV = AUDIO_GetAllocDevInfo(allocDev);

		if(allocDEV == NULL)
		{
			AUD_KDRV_DEBUG(" allocDEV info is NULL\n");
			return RET_ERROR	;
		}

		allocDEV->hasIECBuff = 1;

		modTypeToAlloc	= LX_AUD_LIP_ES;

		allocMod_LIP_ES = AUDIO_AllocModule(allocDev, modTypeToAlloc , 0);

		if(allocMod_IEC != ADEC_MODULE_NO_MOD )
		{
			AUD_KDRV_RMD("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_IEC]);
		}
		else
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
			return RET_ERROR	;
		}

		AUDIO_ConnectTo(allocMod_IEC, allocMod_LIP_ES, NO_FORCE, NO_FORCE);

		AUD_KDRV_PRINT("%s : Dev %x, InFs %d, InFm %d\n", __F__, allocDev, pParamCodec->samplingFreq, pParamCodec->ui32BitPerSample);

		return RET_OK;
	}



	// Set SRC config
	modTypeToAlloc	= LX_AUD_SRC1;
	allocMod_SRC = AUDIO_AllocModule(allocDev,modTypeToAlloc , 0);
	if(allocMod_SRC == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
		return RET_ERROR;
	}

	_AUDIO_SetSRCFormat(allocMod_SRC, pParamCodec->samplingFreq,
						pParamCodec->ui32NumOfChannel, pParamCodec->ui32BitPerSample,
						pParamCodec->endianType, pParamCodec->signedType);

	// Set LIP config
	modTypeToAlloc	= LX_AUD_LIP;
	allocMod_LIP = AUDIO_AllocModule(allocDev,modTypeToAlloc , 0);
	if(allocMod_LIP == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
		return RET_ERROR;
	}

#ifdef ENABLE_SOLA
	// Set SOLA config
	modTypeToAlloc	= LX_AUD_SOLA;
	allocMod_SOLA = AUDIO_AllocModule(allocDev,modTypeToAlloc , 0);
	if(allocMod_SOLA == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
		return RET_ERROR;
	}
	AUD_KDRV_RM("SOLA CONFIG\n",allocMod_Str[allocMod_SOLA]);

	// REN device has LIP already , connet  		// LIP   -- MIX1
	if( AUDIO_IsNotConnectedYet(allocMod_SRC , allocMod_SOLA))
	{
		AUDIO_ConnectTo( allocMod_SRC , allocMod_SOLA , NO_FORCE, NO_FORCE );
	}
		// REN device has LIP already , connet  		// LIP   -- MIX1
	if( AUDIO_IsNotConnectedYet(allocMod_SOLA , allocMod_LIP))
	{
		AUDIO_ConnectTo( allocMod_SOLA , allocMod_LIP , NO_FORCE, NO_FORCE );
	}
#else
	// REN device has LIP already , connet  		// LIP   -- MIX1
	if( AUDIO_IsNotConnectedYet(allocMod_SRC , allocMod_LIP))
	{
		AUDIO_ConnectTo( allocMod_SRC , allocMod_LIP , NO_FORCE, NO_FORCE );
	}

#endif

	// Register Present End
	_AUDIO_RegisterRendererNoti(pRenderInfo, (PFN_ImcNoti)_AUDIO_RenPresentEndCb, allocMod_LIP, LIPSYNC_EVT_PRESENT_END, IMC_ACTION_REPEAT, 1);

	AUD_KDRV_DEBUG("%s : Dev %x, InFs %d, InBs %d\n", __F__, allocDev, pParamCodec->samplingFreq, pParamCodec->ui32BitPerSample);

	return RET_OK;
}


/**
 * Connect other device to renderer.
 * @see
*/
static SINT32 AUDIO_ConnectRenderer(UINT32 allocDev, UINT32 otherAllocDev)
{
	LX_AUD_ALLOC_FREE_INFO_T	*renDevInfo;
	LX_AUD_ALLOC_FREE_INFO_T	*othertDevInfo;
	LX_AUD_MOD_TYPE_T			modTypeToAlloc;
	UINT32						left, right;
	UINT32						allocMod_LIP;
	ADEC_MODULE_ID				managerModule;
	UINT32	allocMod_DPB = ADEC_MODULE_NO_MOD;
	UINT32	allocMod_MPB = ADEC_MODULE_NO_MOD;
	UINT32	allocMod_SRC = ADEC_MODULE_NO_MOD;
	UINT32	allocMod_DEC = ADEC_MODULE_NO_MOD;
	UINT32	allocMod_RTS = ADEC_MODULE_NO_MOD;
	UINT32	allocMod_LIP_ES = ADEC_MODULE_NO_MOD;

	UINT32 	leftManagerModule, rightManagerModule;
	UINT32	allocMod_BypassDSP0 = ADEC_MODULE_NO_MOD;
	UINT32	tempLeft, tempRight;
	SINT32	renIndex = 0;
	SINT32	leftOut_15_8_RightIn_7_0 =0;
	AUD_RENDER_INFO_T	*pRenderInfo = NULL;

	AUD_KDRV_RM("AUDIO_ConnectRenderer  %s  %s \n", allocDev_Str[allocDev], allocDev_Str[otherAllocDev]);

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR("renIndex[%d] is not available.\n", renIndex);
		return RET_ERROR;
	}

	pRenderInfo = &_gRenderInfo[renIndex];

	// if connect with DEC, connect DPB with SRC
	// else if connect with REN, connect MPB with SRC
	renDevInfo = AUDIO_GetAllocDevInfo(allocDev);
	othertDevInfo = AUDIO_GetAllocDevInfo(otherAllocDev);

	// Sanity check for allocated module
	if(othertDevInfo == NULL || renDevInfo == NULL)
	{
		AUD_KDRV_DEBUG("AUDIO_ConnectRenderer : Check ARG othertDevInfo[%p] renDevInfo [%p]\n", othertDevInfo, renDevInfo);
		return RET_ERROR;
	}

	// Sanity check for allocated head and tail device
	if(othertDevInfo->headOfDev == NULL || renDevInfo->headOfDev == NULL	\
	 ||othertDevInfo->tailOfDev == NULL || renDevInfo->tailOfDev == NULL)
	{
		AUD_KDRV_ERROR("========= CAUTION ============ \n");
		AUD_KDRV_ERROR("AUDIO_ConnectRenderer: REN head[%p] tail[%p], Other [%p][%p]\n",	\
						renDevInfo->headOfDev, renDevInfo->tailOfDev, othertDevInfo->headOfDev, othertDevInfo->tailOfDev);
		return RET_ERROR;
	}

	if(othertDevInfo->devType == LX_AUD_DEV_DEC)
	{
		tempLeft 	= ((LX_AUD_ALLOC_FREE_INFO_T *) (othertDevInfo->tailOfDev))->allocMod;
		tempRight 	= ((LX_AUD_ALLOC_FREE_INFO_T *) (renDevInfo->headOfDev))->allocMod;

		leftManagerModule = _AUDIO_GetManagerModule(tempLeft);
		rightManagerModule = _AUDIO_GetManagerModule(tempRight);

		if(leftManagerModule != rightManagerModule)
		{
			allocMod_LIP_ES = AUDIO_HasThisModuleType(allocDev, LX_AUD_LIP_ES);

			// if this dev is not a lip ES render
			if(allocMod_LIP_ES == ADEC_MODULE_NO_MOD)
			{
				// get Bypass DSP1 in DEC device
				modTypeToAlloc	= LX_AUD_BYPASS_DSP0;
				allocMod_BypassDSP0 = AUDIO_AllocModule(otherAllocDev,modTypeToAlloc , 0);

				if(allocMod_BypassDSP0 != ADEC_MODULE_NO_MOD)
				{
					AUD_KDRV_RM("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_BypassDSP0]);
				}
				else
				{
					AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
					return RET_ERROR;
				}

				// Set a default lip sync on and buffer overflow disable mode
				AUDIO_SetBypassMode( allocMod_BypassDSP0, AU_BASED_MODE, NO_OVERFLOW_PROTECTION);

				if(tempLeft != allocMod_BypassDSP0 && AUDIO_IsNotConnectedYet(tempLeft, allocMod_BypassDSP0))
				{
					AUDIO_ConnectTo( tempLeft , allocMod_BypassDSP0, NO_FORCE, NO_FORCE );
				}

				// get DPB buffer
				modTypeToAlloc	= LX_AUD_DPB;
				allocMod_DPB = AUDIO_AllocModule(allocDev,modTypeToAlloc, 0);
				if(allocMod_DPB != ADEC_MODULE_NO_MOD)
				{
					AUD_KDRV_RMD("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_DPB]);
				}
				else
				{
					AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
					return RET_ERROR;
				}

				// get SRC module
				allocMod_SRC = AUDIO_HasThisModuleType(allocDev, LX_AUD_SRC1);
				if ((allocMod_SRC < ADEC_MODULE_SRC_0) || (allocMod_SRC > (ADEC_MODULE_SRC_0 + stFwRmModType[LX_AUD_SRC1].ModNum -1)))
				{
					AUD_KDRV_ERROR("%s.%d: Invalid SRC module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_SRC);
					return RET_ERROR;
				}

				// connect DPB buffer with SRC module
				if(AUDIO_IsNotConnectedYet(allocMod_DPB, allocMod_SRC))
				{
					AUDIO_ConnectTo(allocMod_DPB, allocMod_SRC, NO_FORCE, NO_FORCE);
				}

				// set DPB to lipsync module's reference port
				allocMod_LIP = AUDIO_HasThisModuleType(allocDev, LX_AUD_LIP);
				if((allocMod_LIP < ADEC_MODULE_LIP_0) || (allocMod_LIP > (ADEC_MODULE_LIP_0 + stFwRmModType[LX_AUD_LIP].ModNum -1)))
				{
					AUD_KDRV_ERROR("%s.%d: Invalid LIP module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_LIP);
				}
				else
				{
					managerModule = _AUDIO_GetManagerModule(allocMod_LIP);
					if(managerModule != ADEC_MODULE_NOT_DEF)
					{
						CmCmdSetRefPorts	setRefBufPort;

						setRefBufPort.ref_module	= allocMod_LIP;
						setRefBufPort.num_of_ref	= 1;
						setRefBufPort.ref_port[0]	= MOD_REF_PORT(8);
						setRefBufPort.src_module[0]	= allocMod_SRC;
						setRefBufPort.src_port[0]	= MOD_IN_PORT(0);
						if (AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, managerModule, sizeof(CmCmdSetRefPorts), &setRefBufPort) < 0)
						{
							AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS) Error\n", __FUNCTION__, __LINE__);
						}
					}
				}

				// RTS setting
				if(pRenderInfo->bRTSOnOff == TRUE)
				{
					RtsCmdSetSrcModule	rtsSrcModule;
					CmCmdSetRefPorts	rtsRefBuffer;

					// get RTS
					modTypeToAlloc	= LX_AUD_RTS;
					allocMod_RTS = AUDIO_AllocModule(allocDev,modTypeToAlloc , 0);

					if(allocMod_RTS != ADEC_MODULE_NO_MOD )
					{
						AUD_KDRV_RMD("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_RTS]);
					}
					else
					{
						AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
						return RET_ERROR;
					}

					if((allocMod_SRC >= ADEC_MODULE_SRC_0) && (allocMod_SRC <= (ADEC_MODULE_SRC_0 + stFwRmModType[LX_AUD_SRC1].ModNum -1)))
					{
						// set SRC module
						rtsSrcModule.src_module_id	= allocMod_SRC;
						if(AUDIO_IMC_SendCmdParam(RTS_CMD_SET_SRC_MODULE, allocMod_RTS, sizeof(RtsCmdSetSrcModule), &rtsSrcModule) < 0)
						{
							AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(RTS_CMD_SET_SRC_MODULE, RTS) Error\n", __FUNCTION__, __LINE__);
						}

						// set reference buffer - SRC's input & SRC's output buffer
						rtsRefBuffer.ref_module		= allocMod_RTS;
						rtsRefBuffer.num_of_ref		= 1;
						rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(0);
						rtsRefBuffer.src_module[0]	= allocMod_SRC;
						rtsRefBuffer.src_port[0]	= MOD_IN_PORT(0);
						if(AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdSetRefPorts), &rtsRefBuffer) < 0)
						{
							AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, RTS_0, SRC_IN) Error\n", __FUNCTION__, __LINE__);
						}

						rtsRefBuffer.ref_module		= allocMod_RTS;
						rtsRefBuffer.num_of_ref		= 1;
						rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(1);
						rtsRefBuffer.src_module[0]	= allocMod_SRC;
						rtsRefBuffer.src_port[0]	= MOD_OUT_PORT(0);
						if(AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdSetRefPorts), &rtsRefBuffer) < 0)
						{
							AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, RTS_1, SRC_OUT) Error\n", __FUNCTION__, __LINE__);
						}
					}

					if((allocMod_LIP >= ADEC_MODULE_LIP_0) && (allocMod_LIP <= (ADEC_MODULE_LIP_0 + stFwRmModType[LX_AUD_LIP].ModNum -1)))
					{
						// set reference buffer - LIP's output & SRC's output buffer
						rtsRefBuffer.ref_module		= allocMod_RTS;
						rtsRefBuffer.num_of_ref		= 1;
						rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(2);
						rtsRefBuffer.src_module[0]	= allocMod_LIP;
						rtsRefBuffer.src_port[0]	= MOD_OUT_PORT(0);
						if(AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdSetRefPorts), &rtsRefBuffer) < 0)
						{
							AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, RTS_3, LIP_OUT) Error\n", __FUNCTION__, __LINE__);
						}
					}
				}

				left =	((LX_AUD_ALLOC_FREE_INFO_T *) (othertDevInfo->tailOfDev))->allocMod;
				right =	((LX_AUD_ALLOC_FREE_INFO_T *) (renDevInfo->headOfDev))->allocMod;

				if(AUDIO_IsNotConnectedYet(left, right))
				{
					AUDIO_ConnectTo (left, right, NO_FORCE, NO_FORCE);
				}
			}
			else //
			{
				allocMod_DEC = AUDIO_HasThisModuleType(otherAllocDev, LX_AUD_DEC);

				if(allocMod_DEC != ADEC_MODULE_NO_MOD)
				{
					left =	allocMod_DEC;
					right =	((LX_AUD_ALLOC_FREE_INFO_T *) (renDevInfo->headOfDev))->allocMod;
					AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
				}
				else
				{
					AUD_KDRV_RMD("No DEC module in otherDEV\n");
				}
			}
		}
	}
	else if(othertDevInfo->devType == LX_AUD_DEV_REN)
	{
		// get MBP buffer
		modTypeToAlloc = LX_AUD_MPB;
		allocMod_MPB = AUDIO_AllocModule(allocDev,modTypeToAlloc, 0);
		if(allocMod_MPB != ADEC_MODULE_NO_MOD)
		{
			AUD_KDRV_RMD("Module[%s] [Alloc:%s:%d] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_MPB],allocMod_MPB);
		}
		else
		{
			AUD_KDRV_RMD(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
			return RET_ERROR;
		}

		// get SRC module
		allocMod_SRC = AUDIO_HasThisModuleType(allocDev, LX_AUD_SRC1);
		if((allocMod_SRC < ADEC_MODULE_SRC_0) || (allocMod_SRC > (ADEC_MODULE_SRC_0 + stFwRmModType[LX_AUD_SRC1].ModNum -1)))
		{
			AUD_KDRV_ERROR("%s.%d: Invalid SRC module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_SRC);
			return RET_ERROR;
		}

		// connect DPB buffer with SRC module
		if(AUDIO_IsNotConnectedYet(allocMod_MPB, allocMod_SRC))
		{
			// MPB -- SRC
			AUDIO_ConnectTo(allocMod_MPB,allocMod_SRC , NO_FORCE, NO_FORCE );
		}

		// set MPB to lipsync module's reference port
		allocMod_LIP = AUDIO_HasThisModuleType(allocDev, LX_AUD_LIP);
		if((allocMod_LIP < ADEC_MODULE_LIP_0) || (allocMod_LIP > (ADEC_MODULE_LIP_0 + stFwRmModType[LX_AUD_LIP].ModNum -1)))
		{
			AUD_KDRV_ERROR("%s.%d: Invalid LIP module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_LIP);
		}
		else
		{
			managerModule = _AUDIO_GetManagerModule(allocMod_LIP);
			if(managerModule != ADEC_MODULE_NOT_DEF)
			{
				CmCmdSetRefPorts	setRefBufPort;

				setRefBufPort.ref_module	= allocMod_LIP;
				setRefBufPort.num_of_ref	= 1;
				setRefBufPort.ref_port[0]	= MOD_REF_PORT(8);
				setRefBufPort.src_module[0]	= allocMod_SRC;
				setRefBufPort.src_port[0]	= MOD_IN_PORT(0);
				if(AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, managerModule, sizeof(CmCmdSetRefPorts), &setRefBufPort) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS) Error\n", __FUNCTION__, __LINE__);
				}
			}
		}

		// RTS setting
		if(pRenderInfo->bRTSOnOff == TRUE)
		{
			RtsCmdSetSrcModule	rtsSrcModule;
			CmCmdSetRefPorts	rtsRefBuffer;

			// get RTS
			modTypeToAlloc	= LX_AUD_RTS;
			allocMod_RTS = AUDIO_AllocModule(allocDev,modTypeToAlloc , 0);

			if((allocMod_SRC >= ADEC_MODULE_SRC_0) && (allocMod_SRC <= (ADEC_MODULE_SRC_0 + stFwRmModType[LX_AUD_SRC1].ModNum -1)))
			{
				// set SRC module
				rtsSrcModule.src_module_id	= allocMod_SRC;
				if(AUDIO_IMC_SendCmdParam(RTS_CMD_SET_SRC_MODULE, allocMod_RTS, sizeof(RtsCmdSetSrcModule), &rtsSrcModule) < 0)
				{
					AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(RTS_CMD_SET_SRC_MODULE, RTS) Error\n", __FUNCTION__, __LINE__);
				}

				// set reference buffer - SRC's input & SRC's output buffer
				rtsRefBuffer.ref_module		= allocMod_RTS;
				rtsRefBuffer.num_of_ref		= 1;
				rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(0);
				rtsRefBuffer.src_module[0]	= allocMod_SRC;
				rtsRefBuffer.src_port[0]	= MOD_IN_PORT(0);
				if(AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdSetRefPorts), &rtsRefBuffer) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, RTS_0, SRC_IN) Error\n", __FUNCTION__, __LINE__);
				}

				rtsRefBuffer.ref_module		= allocMod_RTS;
				rtsRefBuffer.num_of_ref		= 1;
				rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(1);
				rtsRefBuffer.src_module[0]	= allocMod_SRC;
				rtsRefBuffer.src_port[0]	= MOD_OUT_PORT(0);
				if(AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdSetRefPorts), &rtsRefBuffer) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, RTS_1, SRC_OUT) Error\n", __FUNCTION__, __LINE__);
				}
			}

			if((allocMod_LIP >= ADEC_MODULE_LIP_0) && (allocMod_LIP <= (ADEC_MODULE_LIP_0 + stFwRmModType[LX_AUD_LIP].ModNum -1)))
			{
				// set reference buffer - LIP's output & SRC's output buffer
				rtsRefBuffer.ref_module		= allocMod_RTS;
				rtsRefBuffer.num_of_ref		= 1;
				rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(2);
				rtsRefBuffer.src_module[0]	= allocMod_LIP;
				rtsRefBuffer.src_port[0]	= MOD_OUT_PORT(0);
				if (AUDIO_IMC_SendCmdParam(CM_CMD_SET_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdSetRefPorts), &rtsRefBuffer) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, RTS_3, LIP_OUT) Error\n", __FUNCTION__, __LINE__);
				}
			}
		}
	}
	else if(othertDevInfo->devType ==LX_AUD_DEV_MAS)
	{
		left =	((LX_AUD_ALLOC_FREE_INFO_T *) (renDevInfo->tailOfDev))->allocMod;
		right =	((LX_AUD_ALLOC_FREE_INFO_T *) (othertDevInfo->headOfDev))->allocMod;

		if(AUDIO_IsNotConnectedYet(left,right))
		{
			leftOut_15_8_RightIn_7_0= AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
			if(leftOut_15_8_RightIn_7_0 !=RET_ERROR)
			{
				pRenderInfo->ui32MixerPort = leftOut_15_8_RightIn_7_0 & 0xff;
				AUD_KDRV_RM(" mix in port of ren idx[%d] is :[%x:%d] \n",renIndex,pRenderInfo->ui32MixerPort,
										pRenderInfo->ui32MixerPort);
			}
		}
		else
		{
			AUD_KDRV_RM(" connection is Already exist \n");
		}

		if(pRenderInfo->renderParam.input == LX_AUD_INPUT_SYSTEM)
		{
			// RTS setting
			if(pRenderInfo->bRTSOnOff == TRUE)
			{
				_AUDIO_SetMixerConfig(pRenderInfo->ui32MixerPort,
									FADE_LENGTH_RTS,
									MIX_WAIT_LENGTH_RTS,
									pRenderInfo->ui32Volume);
			}
			else	// Other EMP
			{
				_AUDIO_SetMixerConfig(pRenderInfo->ui32MixerPort,
										FADE_LENGTH_DEFAULT,
										MIX_WAIT_LENGTH_EMP,
										pRenderInfo->ui32Volume);
			}
		}	// Others
		else
		{
			_AUDIO_SetMixerConfig(pRenderInfo->ui32MixerPort,
									FADE_LENGTH_DEFAULT,
									MIX_WAIT_LENGTH_DEFAULT,
									pRenderInfo->ui32Volume);
		}
	}
	else if(othertDevInfo->devType == LX_AUD_DEV_ENC)
	{
		left 	= ((LX_AUD_ALLOC_FREE_INFO_T *) (othertDevInfo->tailOfDev))->allocMod;
		right 	= ((LX_AUD_ALLOC_FREE_INFO_T *) (renDevInfo->headOfDev))->allocMod;

		AUDIO_ConnectTo(left, right ,NO_FORCE, NO_FORCE);
	}
	else
	{
		AUD_KDRV_ERROR("NOT valid connection\n");
		//AUDIO_UpdateConnectionInfo();
		return RET_ERROR;
	}

	if(pRenderInfo->bResetting == FALSE)
	{
		_gRenderInfo[renIndex].renderConnect[_gRenderInfo[renIndex].ui32ConnectNum].devType    = othertDevInfo->devType;
		_gRenderInfo[renIndex].renderConnect[_gRenderInfo[renIndex].ui32ConnectNum].connectDev = othertDevInfo->allocDev;
		_gRenderInfo[renIndex].ui32ConnectNum++;
	}

	// Register Notification
	if(othertDevInfo->devType == LX_AUD_DEV_DEC)
	{
		allocMod_DEC = AUDIO_HasThisModuleType(otherAllocDev, LX_AUD_DEC);
		if(allocMod_DEC != ADEC_MODULE_NO_MOD)
		{
			_AUDIO_RegisterRendererNoti(pRenderInfo, (PFN_ImcNoti)_AUDIO_RenDecInfoCb, allocMod_DEC, DEC_EVT_ES_DEC_INFO, IMC_ACTION_REPEAT, 1);
		}
	}

	// Set SRC Control
	if(othertDevInfo->devType == LX_AUD_DEV_DEC)
	{
		if((pRenderInfo->renderParam.input == LX_AUD_INPUT_SIF) || (pRenderInfo->renderParam.input == LX_AUD_INPUT_HDMI))
		{
			if(_AUDIO_SetCtrlSrc(pRenderInfo) == RET_ERROR)
			{
				AUD_KDRV_RM("%s.%d : CtrlSrc is not setted.\n", __FILE__, __LINE__);
			}
		}
	}

	return RET_OK;
}

/**
 * Disconnect other device to renderer.
 * @see
*/
static SINT32 AUDIO_DisconnectRenderer (UINT32 allocDev, UINT32 otherAllocDev)
{
	LX_AUD_ALLOC_FREE_INFO_T * renDevInfo, * othertDevInfo;
	UINT32						allocMod_LIP;
	ADEC_MODULE_ID				managerModule;
	UINT32 	left, right;
	UINT32	isConnectedFaceToFace = 0; //,isConnectedFaceToFaceDPB_SRC = 0,isConnectedFaceToFaceMIX_SRC = 0,isConnectedFaceToFaceDPB_MIX = 0;
	UINT32	allocMod_LIP_ES = ADEC_MODULE_NO_MOD;
	UINT32	allocMod_DEC = ADEC_MODULE_NO_MOD;
	UINT32	allocMod_RTS = ADEC_MODULE_NO_MOD;
	SINT32	renIndex = 0;
	AUD_RENDER_INFO_T	*pRenderInfo = NULL;

	AUD_KDRV_RM("AUDIO_DisconnectRenderer  %s  %s \n",allocDev_Str[ allocDev],allocDev_Str[otherAllocDev]);

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR("renIndex[%d] is not available.\n", renIndex);
		return RET_ERROR;
	}

	pRenderInfo = &_gRenderInfo[renIndex];

	renDevInfo = AUDIO_GetAllocDevInfo(allocDev);
	othertDevInfo = AUDIO_GetAllocDevInfo(otherAllocDev);

	if(othertDevInfo == NULL || renDevInfo == NULL)
	{
		AUD_KDRV_DEBUG("Check ARG othertDevInfo[%p] renDevInfo [%p]\n",othertDevInfo,renDevInfo);
		return RET_ERROR;
	}

	if(othertDevInfo->headOfDev == NULL || othertDevInfo->tailOfDev == NULL ||
	    renDevInfo->headOfDev == NULL || renDevInfo->tailOfDev == NULL)
	{
		AUD_KDRV_ERROR("========x1 CAUTION ============ \n");
		AUD_KDRV_ERROR("REN head[%p] tail[%p]  Other [%p] [%p] \n",renDevInfo->headOfDev, renDevInfo->tailOfDev,othertDevInfo->headOfDev, othertDevInfo->tailOfDev );
		return RET_OK;
	}

	if(othertDevInfo->devType == LX_AUD_DEV_DEC)
	{
		allocMod_LIP_ES = AUDIO_HasThisModuleType(allocDev, LX_AUD_LIP_ES);

		// if this dev is not a lip ES render
		if(allocMod_LIP_ES == ADEC_MODULE_NO_MOD)
		{

			left 	=((LX_AUD_ALLOC_FREE_INFO_T *)othertDevInfo->tailOfDev)->allocMod ;
			right = ((LX_AUD_ALLOC_FREE_INFO_T *)renDevInfo->headOfDev)->allocMod;

			if(AUDIO_IsAlreadyConnected( left,right))
			{
				AUDIO_DisconnectTo(left,right , NO_FORCE, NO_FORCE );
				AUD_KDRV_RM("[%s] -----X----- [%s] disconnection OKl\n", allocMod_Str[left],allocMod_Str[right]);
			}
			else
			{
				AUD_KDRV_RM("[%s] -----X----- [%s] disconnection NOT OKl\n", allocMod_Str[left],allocMod_Str[right]);

			}

			// clear DPB from lipsync module's reference port
			allocMod_LIP = AUDIO_HasThisModuleType(allocDev, LX_AUD_LIP);
			if((allocMod_LIP < ADEC_MODULE_LIP_0) || (allocMod_LIP > (ADEC_MODULE_LIP_0 + stFwRmModType[LX_AUD_LIP].ModNum -1)))
			{
				AUD_KDRV_ERROR("%s.%d: Invalid LIP module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_LIP);
			}
			else
			{
				managerModule = _AUDIO_GetManagerModule(allocMod_LIP);
				if(managerModule != ADEC_MODULE_NOT_DEF)
				{
					CmCmdClrRefPorts	clearRefBufPort;

					clearRefBufPort.module		= allocMod_LIP;
					clearRefBufPort.num_of_ref	= 1;
					clearRefBufPort.ref_port[0]	= MOD_REF_PORT(8);
					if(AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, managerModule, sizeof(CmCmdClrRefPorts), &clearRefBufPort) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS) Error\n", __FUNCTION__, __LINE__);
					}
				}
			}

			// RTS setting
			if (pRenderInfo->bRTSOnOff == TRUE)
			{
				CmCmdClrRefPorts	rtsRefBuffer;

				allocMod_RTS = AUDIO_HasThisModuleType(allocDev, LX_AUD_RTS);
				if (allocMod_RTS != ADEC_MODULE_RTS )
				{
					AUD_KDRV_ERROR("%s.%d: Invalid RTS module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_RTS);
				}
				else
				{
					rtsRefBuffer.module			= allocMod_RTS;
					rtsRefBuffer.num_of_ref		= 1;
					rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(0);
					if (AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdClrRefPorts), &rtsRefBuffer) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, RTS_0) Error\n", __FUNCTION__, __LINE__);
					}

					rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(1);
					if (AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdClrRefPorts), &rtsRefBuffer) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, RTS_1) Error\n", __FUNCTION__, __LINE__);
					}

					rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(2);
					if (AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdClrRefPorts), &rtsRefBuffer) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, RTS_2) Error\n", __FUNCTION__, __LINE__);
					}
				}

			}
		}
		else
		{
			allocMod_DEC = AUDIO_HasThisModuleType(otherAllocDev, LX_AUD_DEC);

			if( allocMod_DEC != ADEC_MODULE_NO_MOD )
			{
				left =	allocMod_DEC;
				right =	((LX_AUD_ALLOC_FREE_INFO_T *) (renDevInfo->headOfDev))->allocMod;

				if(AUDIO_IsAlreadyConnected( left,right))
				{
					AUDIO_DisconnectTo(left,right , NO_FORCE, NO_FORCE );
					AUD_KDRV_RM("[%s] -----X----- [%s] disconnection OKl\n", allocMod_Str[left],allocMod_Str[right]);
				}
			}
			else
			{
				AUD_KDRV_RMD("No DEC module  in otherDEV\n");
			}
		}
	}
	else if(othertDevInfo->devType == LX_AUD_DEV_REN)
	{
		left =((LX_AUD_ALLOC_FREE_INFO_T *)renDevInfo->headOfDev)->allocMod ;
		right = ((LX_AUD_ALLOC_FREE_INFO_T *)renDevInfo->tailOfDev)->allocMod;

		if(AUDIO_IsAlreadyConnected(left, right))
		{
			isConnectedFaceToFace = 1;
			AUD_KDRV_RM("[%s] -----X----- [%s] disconnection OKl\n", allocMod_Str[left],allocMod_Str[right]);
		}
		else
			AUD_KDRV_RM("[%s] -----X----- [%s] disconnection NOT OKl\n", allocMod_Str[left],allocMod_Str[right]);

		if(isConnectedFaceToFace == 1)
		{
			AUDIO_DisconnectTo(left, right, NO_FORCE, NO_FORCE);
		}

		// clear MPB from lipsync module's reference port
		allocMod_LIP = AUDIO_HasThisModuleType(allocDev, LX_AUD_LIP);
		if((allocMod_LIP < ADEC_MODULE_LIP_0) || (allocMod_LIP > (ADEC_MODULE_LIP_0 + stFwRmModType[LX_AUD_LIP].ModNum -1)))
		{
			AUD_KDRV_ERROR("%s.%d: Invalid LIP module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_LIP);
		}
		else
		{
			managerModule = _AUDIO_GetManagerModule(allocMod_LIP);
			if(managerModule != ADEC_MODULE_NOT_DEF)
			{
				CmCmdClrRefPorts	clearRefBufPort;

				clearRefBufPort.module		= allocMod_LIP;
				clearRefBufPort.num_of_ref	= 1;
				clearRefBufPort.ref_port[0]	= MOD_REF_PORT(8);
				if(AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, managerModule, sizeof(CmCmdClrRefPorts), &clearRefBufPort) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS) Error\n", __FUNCTION__, __LINE__);
				}
			}
		}

		// RTS setting
		if(pRenderInfo->bRTSOnOff == TRUE)
		{
			CmCmdClrRefPorts	rtsRefBuffer;

			allocMod_RTS = AUDIO_HasThisModuleType(allocDev, LX_AUD_RTS);
			if(allocMod_RTS != ADEC_MODULE_RTS)
			{
				AUD_KDRV_ERROR("%s.%d: Invalid RTS module(%d)!!!\n", __FUNCTION__, __LINE__, allocMod_RTS);
			}
			else
			{
				rtsRefBuffer.module			= allocMod_RTS;
				rtsRefBuffer.num_of_ref		= 1;
				rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(0);
				if(AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdClrRefPorts), &rtsRefBuffer) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, RTS_0) Error\n", __FUNCTION__, __LINE__);
				}

				rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(1);
				if(AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdClrRefPorts), &rtsRefBuffer) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, RTS_1) Error\n", __FUNCTION__, __LINE__);
				}

				rtsRefBuffer.ref_port[0]	= MOD_REF_PORT(2);
				if(AUDIO_IMC_SendCmdParam(CM_CMD_CLR_REF_PORTS, ADEC_MODULE_MAN_DSP1, sizeof(CmCmdClrRefPorts), &rtsRefBuffer) < 0)
				{
					AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, RTS_2) Error\n", __FUNCTION__, __LINE__);
				}

			}
		}
	}
	else if(othertDevInfo->devType ==LX_AUD_DEV_MAS)
	{
		// initialize mixer port
		_AUDIO_SetMixerConfig(pRenderInfo->ui32MixerPort,
								FADE_LENGTH_DEFAULT,
								MIX_WAIT_LENGTH_DEFAULT,
								pRenderInfo->ui32Volume);

		left = ((LX_AUD_ALLOC_FREE_INFO_T *) (renDevInfo->tailOfDev))->allocMod;
		right =	((LX_AUD_ALLOC_FREE_INFO_T *) (othertDevInfo->headOfDev))->allocMod;

		if(AUDIO_IsAlreadyConnected(left, right))
		{
			AUDIO_DisconnectTo(left, right, NO_FORCE, NO_FORCE);
		}
		else
		{
			AUD_KDRV_RM("[%s] -----X----- [%s] is already disconnection \n", allocMod_Str[left], allocMod_Str[right]);
		}
	}
	else
	{
		AUD_KDRV_RM("NOT valid disconnection\n");
		//AUDIO_UpdateConnectionInfo();
	}

	return RET_OK;
}

/**
 * Function for Close Renderer.
 * Close Renderer temporary.
 * @see
*/
static SINT32 AUDIO_CloseRenderer (AUD_DEVICE_T* audDev)
{
	UINT32 					devType;
	LX_AUD_ALLOC_FREE_INFO_T CloseInfo;
	UINT32					allocDev;
	SINT32					retVal = 0;
	SINT32					renIndex = 0;
	AUD_EVENT_T	 			*pRenEvent = NULL;
	UINT32					i = 0;

	/* Set device */
	devType = audDev->devType;
	allocDev = audDev->allocDev;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	if(_gRenderInfo[renIndex].bClosed == TRUE)
	{
		AUD_KDRV_ERROR(" renIndex[%d] is already closed. \n", renIndex);
		return RET_OK;
	}

	retVal = AUDIO_DisconnectAllInDev(allocDev);
	if(retVal == RET_ERROR)
	{
		AUD_KDRV_ERROR("Fail to disconnect in dev[%s] \n",allocDev_Str[allocDev]);
	}

	CloseInfo.devType = devType;
	CloseInfo.allocDev = allocDev;
	retVal = AUDIO_FreeDev(&CloseInfo);
	if(retVal == AUD_NO_DEV)
	{
		AUD_KDRV_ERROR(" All %s is already freed \n",devTypeStr[devType]);
	}
	else
	{
		AUD_KDRV_RM("%s is closed[Freed:%s]\n",devTypeStr[devType],(char *)allocDev_Str[retVal] );
	}

	for(i = 0; i < _gRenderInfo[renIndex].ui32EventNum; i++)
	{
		pRenEvent = &_gRenderInfo[renIndex].renderEvent[i];
		IMC_CancelEvent(IMC_GetLocalImc(0), pRenEvent->event , pRenEvent->moduleID, pRenEvent->actionID);
		AUD_KDRV_PRINT("%s: IMC_CancelEvent(%d) is (%x, %x, %x)!!!\n", __FUNCTION__, renIndex, pRenEvent->event,	\
			pRenEvent->moduleID, pRenEvent->actionID);
	}

	//Clear a render resource.
	_gRenderInfo[renIndex].ui32EventNum = 0;
	_gRenderInfo[renIndex].bClosed 		= TRUE;
	_gRenderInfo[renIndex].ui32AllocDev = 0;

	_AUDIO_FreeCtrlSrcModule(_gRenderInfo[renIndex].ctrlSrcInfo.allocCtrlSrc);
	_gRenderInfo[renIndex].ctrlSrcInfo.bCtrlSrcOnOff = FALSE;
	_gRenderInfo[renIndex].ctrlSrcInfo.allocCtrlSrc	= ADEC_MODULE_NO_MOD;

	AUD_KDRV_PRINT("%s : alloc Device %d.\n", __F__, allocDev);

	return RET_OK;
}

static SINT32 AUDIO_GetRenderedStatus(UINT32 allocDev, LX_AUD_RENDERED_STATUS_T *pRenderedStatus)
{
	SINT32					renIndex = 0;
	ADEC_BUF_T				*pWriterStruct = NULL;

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	// get MPB buffer
	pWriterStruct = _AUDIO_GetRendererWriteStructure(allocDev);
	if(pWriterStruct == NULL)
	{
		// get DPB buffer
		pWriterStruct = _AUDIO_GetRendererDPBWriteStructure(allocDev);
		if(pWriterStruct == NULL)
		{
			AUD_KDRV_ERROR("%s.%d: MPB & DPB pWriterStruct is NULL !!!\n", __FUNCTION__, __LINE__);
			return RET_ERROR;
		}
	}

	//Get a buffer info. from buffer interface
	_gRenderInfo[renIndex].renderStatus.ui32MaxMemSize = pWriterStruct->get_max_size(pWriterStruct);
	_gRenderInfo[renIndex].renderStatus.ui32FreeMemSize = pWriterStruct->get_free_size(pWriterStruct);
	_gRenderInfo[renIndex].renderStatus.ui32MaxAuiSize = pWriterStruct->get_max_au(pWriterStruct);
	_gRenderInfo[renIndex].renderStatus.ui32FreeAuiSize = pWriterStruct->get_max_au(pWriterStruct) - pWriterStruct->get_au_cnt(pWriterStruct) - 1;

	memcpy(pRenderedStatus, &(_gRenderInfo[renIndex].renderStatus), sizeof(LX_AUD_RENDERED_STATUS_T));

	AUD_KDRV_PRINT("AUDIO_GetDecodedStatus(%d)\n", renIndex);
	return RET_OK;
}

/**
 * Sets the RTS mechanism.
 * Controls the RTS function manually.
 * @see
*/
static SINT32 AUDIO_EnableRTS (UINT32 allocDev, UINT32 bOnOff)
{
	SINT32	renIndex;

	AUD_KDRV_PRINT("%s.%d: set RTS to %s\n", __FUNCTION__, __LINE__, (bOnOff == TRUE ? "On" : "Off"));

	renIndex = GET_REN_INDEX(allocDev);
	if((renIndex < 0) || (renIndex >= DEV_REN_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", renIndex);
		return RET_ERROR;
	}

	_gRenderInfo[renIndex].bRTSOnOff = bOnOff;
	return RET_OK;
}

/**
 * Sets the Audio Trick Play mechanism.
 * Controls the Renderer Play Speed.
 * @see
*/
static SINT32 AUDIO_SetTrickPlayMode(UINT32 allocDev, UINT32 trickMode)
{
#ifdef ENABLE_SOLA
	ADEC_MODULE_ID	solaModule;

	SolaCmdSetRate	solaParam;

	// Get a MPB buffer
	solaModule = (ADEC_MODULE_ID)AUDIO_HasThisModuleType(allocDev, LX_AUD_SOLA);
	if((solaModule < ADEC_MODULE_SOLA_0) || (solaModule > ADEC_MODULE_SOLA_1))
	{
		AUD_KDRV_ERROR(" sora Module[%s] is not available \n", modTypeStr[LX_AUD_SOLA]);
		return RET_ERROR;
	}
	else
	{
		AUD_KDRV_RM("Module[%s] [Alloc:%s:%d] Trick Mode[%d] \n",modTypeStr[LX_AUD_SOLA],(char *)allocMod_Str[solaModule],solaModule,trickMode );
	}
	//AUD_KDRV_ERROR("Module[%s] [Alloc:%s:%d] Trick Mode[%d] \n",modTypeStr[LX_AUD_SOLA],(char *)allocMod_Str[solaModule],solaModule,trickMode );

	switch (trickMode)
	{
		case LX_AUD_TRICK_NORMAL_PLAY:
			solaParam.InSample	= 1000;
			solaParam.OutSample	= 1000;

			break;
		case LX_AUD_TRICK_FAST_FOWARD_1P2X:
			solaParam.InSample	= 1000;
			solaParam.OutSample	= 800;
			break;

		case LX_AUD_TRICK_SLOW_MOTION_0P8X:
			solaParam.InSample	= 1000;
			solaParam.OutSample	= 1200;
			break;

		default:
			solaParam.InSample	= 1000;
			solaParam.OutSample	= 1000;
			break;
	}

	//AUD_KDRV_ERROR("  InSample[%d] OutSample[%d]\n",solaParam.InSample,solaParam.OutSample);

	if(AUDIO_IMC_SendCmdParam(SOLA_CMD_SET_RATE, solaModule, sizeof(SolaCmdSetRate), &solaParam))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(SOLA_CMD_SET_RATE) Err\n", __FUNCTION__, __LINE__);
	}
#endif

	AUD_KDRV_PRINT("AUDIO_SetTrickPlayMode(%d)\n", trickMode);
	return RET_OK;
}

void	KDRV_AUDIO_ResetRenderer(void)
{
	LX_AUD_MOD_T				*pOwnMods;
	AUD_EVENT_T	 				*pRenEvent = NULL;
	UINT32						allocDev;
	UINT32						i = 0, j  = 0;
	UINT32						allocModNum;
   	LX_AUD_ALLOC_FREE_INFO_T * freeDEV;

	for(i = 0; i < DEV_REN_NUM; i++)
	{
		allocDev = _gRenderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		_gRenderInfo[i].bResetting = TRUE;

		AUDIO_StopRenderer(allocDev);
		AUDIO_FlushRenderer(allocDev);

		for(j = 0; j < _gRenderInfo[i].ui32ConnectNum; j++)
		{
			AUDIO_DisconnectRenderer(allocDev, _gRenderInfo[i].renderConnect[j].connectDev);
		}

		AUDIO_DisconnectAllInDev(allocDev);

		//get alloc module info in given device node
		AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

		for(j = 0; j < allocModNum; j++)
		{
			AUDIO_FreeModule (pOwnMods[j].mod,allocDev);
		}

    	freeDEV = &DevInfo.list[allocDev];
    	freeDEV->headOfDev		= NULL;
    	freeDEV->tailOfDev		= NULL;

		for(j = 0; j < _gRenderInfo[i].ui32EventNum; j++)
		{
			pRenEvent = &_gRenderInfo[i].renderEvent[j];
			IMC_CancelEvent(IMC_GetLocalImc(0), pRenEvent->event , pRenEvent->moduleID, pRenEvent->actionID);
		}

		_gRenderInfo[i].ui32EventNum = 0;
	}
}

void	KDRV_AUDIO_ResetRendererParam(void)
{
	LX_AUD_RENDER_PARAM_T		*pRenInfoParam = NULL;
	UINT32						allocDev;
	UINT32						i = 0, j  = 0;

	for(i = 0; i < DEV_REN_NUM; i++)
	{
		allocDev = _gRenderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		pRenInfoParam = &(_gRenderInfo[i].renderParam);
		AUDIO_SetRendererParam(allocDev, pRenInfoParam);
		for(j = 0; j < _gRenderInfo[i].ui32ConnectNum; j++)
		{
			AUDIO_ConnectRenderer(allocDev, _gRenderInfo[i].renderConnect[j].connectDev);
		}

		AUDIO_SetLipsync(allocDev, &(_gRenderInfo[i].renderLipsync));
		AUDIO_SetClockType(allocDev, _gRenderInfo[i].renderClockType);
		AUDIO_EnableLipsync(allocDev, _gRenderInfo[i].bLipsyncOnOff);
	}
}

void	KDRV_AUDIO_RestartRenderer(void)
{
	UINT32						allocDev;
	UINT32						i = 0;

	for(i = 0; i < DEV_REN_NUM; i++)
	{
		allocDev = _gRenderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		//_gRenderInfo[i].renderParam.samplingFreq = LX_AUD_SAMPLING_FREQ_NONE;
		//_gRenderInfo[i].bStarted = FALSE;
		AUDIO_StartRenderer(allocDev);

		_gRenderInfo[i].bResetting = FALSE;
	}
}

/**
 * Function for Get Renderer Information for Debug.
 * @see
*/
void	KDRV_AUDIO_GetRendererInfoForDebug(UINT32 ui32RenderNum, LX_AUD_RENDER_PARAM_T *pRenderInfo)
{
	//Sanity check
	if(pRenderInfo != NULL)
	{
		if(ui32RenderNum < DEV_REN_NUM)
			memcpy(pRenderInfo, &(_gRenderInfo[ui32RenderNum].renderParam), sizeof(LX_AUD_RENDER_PARAM_T));
		else
			memset(pRenderInfo, 0, sizeof(LX_AUD_RENDER_PARAM_T));
	}

	return;
}

/**
 * Redemand Decoded Notification.
 * @see
*/
void	KDRV_AUDIO_RedemandDecodedNofiRenderer(void)
{
	UINT32						tempCheckStartCount = 0;
	UINT32						allocDev;
	UINT32						i = 0, j = 0;
	UINT32						connectDev;
	LX_AUD_ALLOC_MOD_T			moduleId = ADEC_MODULE_NOT_DEF;
	LX_AUD_ALLOC_MOD_T			tempModuleId = ADEC_MODULE_NOT_DEF;

	for(i = 0; i < DEV_REN_NUM; i++)
	{
		allocDev = _gRenderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		/* Set a decoder notification to get a decoder information. */
		if(_gRenderInfo[i].bStarted == FALSE)
		{
			for(j = 0; j < AUD_RENDER_CONNECT_NUM; j++)
			{
				if(_gRenderInfo[i].renderConnect[j].devType == LX_AUD_DEV_DEC)
				{
					connectDev = _gRenderInfo[i].renderConnect[j].connectDev;
					moduleId   = AUDIO_HasThisModuleType(connectDev, LX_AUD_DEC);

					if(moduleId == ADEC_MODULE_NO_MOD)
					{
						AUD_KDRV_DEBUG("%s.%d: audio module is Unknown\n", __FUNCTION__, __LINE__);
						continue;
					}

					tempCheckStartCount = _gRenderCheckStartCount[i]++;

					if((tempCheckStartCount > COUNT_MIN_CHECK_START) && (tempCheckStartCount <= COUNT_MAX_CHECK_START))
					{
						if(moduleId != tempModuleId)
						{
							(void)AUDIO_IMC_SendCmd(ADEC_CMD_GET_DECINFO, moduleId);
							tempModuleId = moduleId;

							AUD_KDRV_DEBUG("[%d]Renderer : ADEC_CMD_GET_DECINFO.\n", __LINE__);
						}
					}
				}
			}
		}
	}

	return;
}



