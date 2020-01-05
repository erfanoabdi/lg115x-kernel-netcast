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


/** @file	audio_kdrv_capturer.c
 *
 *  main driver implementation for  audio capturer device.
 *  audio capturer device will teach you how to make device driver with new platform.
 *
 *  author	wonchang.shin (wonchang.shin@lge.com)
 *  version	0.1
 *  date		2012.04.25
 *  note		Additional information.
 *
 *  @addtogroup lg1150_audio
 *	@{
 */


/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>    /**< For isr */
#include <linux/irq.h>			/**< For isr */
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <linux/rmap.h>
#include <linux/kthread.h>
#include <asm/io.h>			/**< For ioremap_nocache */
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/version.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"

#include "debug_util.h"
#include "audio_cfg.h"
#include "audio_drv.h"
#include "audio_drv_capturer.h"

#include "audio_drv_master.h"
#include "audio_drv_manager.h"
#include "audio_drv_renderer.h"
#include "audio_imc_func.h"
#include "audio_buffer.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define AUD_PCM_1SEC				(48000*2*2*1)		///< 1 second PCM audio data(48Khz * 16 bits * 2 channel * 1 second)
#define AUD_PCM_200MSEC				(AUD_PCM_1SEC/5)	///< 200 mseconds PCM audio data

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern UINT8 *  allocMod_Str [ADEC_MODULE_MOD_MAX+1] ;
extern UINT8 * modTypeStr[LX_AUD_MOD_TYPE_MAX+1];
extern UINT8 *  allocDev_Str [AUD_DEV_MAX+1] ;
extern UINT8 * devTypeStr[LX_AUD_DEV_TYPE_MAX+1];
extern LX_AUD_BUF_MEM_CFG_S_T stCAP[] ;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
AUD_CAPTURER_INFO_T _gCapturerInfo[DEV_CAP_NUM];

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static SINT32 AUDIO_StartCapturer (UINT32 allocDev);
static SINT32 AUDIO_StopCapturer (UINT32 allocDev);
static SINT32 AUDIO_FlushCapturer (UINT32 allocDev);
static SINT32 AUDIO_CloseCapture(AUD_DEVICE_T* audDev);
static SINT32 AUDIO_SetCaptureParam(UINT32 allocDev, LX_AUD_CAPTURE_PARAM_T *pCapParam);
static SINT32 AUDIO_GetCapturedInfo(UINT32 allocDev, LX_AUD_CAPTURE_CAPTURED_INFO_T *pCapInfo);
static SINT32 AUDIO_GetCapturedData(UINT32 allocDev, LX_AUD_CAPTURE_CAPTURED_DATA_T *pCapData);
static SINT32 AUDIO_ConnectCapturer (UINT32 allocDev, UINT32 connectDev);
static SINT32 AUDIO_DisconnectCapturer (UINT32 allocDev, UINT32 disconnectDev);
static SINT32 AUDIO_SetCaptureVolume (UINT32 allocDev, UINT32 volume);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * open handler for audio Capture device
 *
 */
SINT32	KDRV_AUDIO_OpenCapture(struct inode *inode, struct file *filp)
{
	ULONG	flags;
	SINT32 retVal = RET_OK;
	UINT32 nMajor;
	UINT32 nMinor;
	UINT32 devType;
	SINT32 capIndex = 0;

	AUD_DEVICE_T*	my_dev;
	LX_AUD_ALLOC_FREE_INFO_T OpenInfo;
	UINT32 allocMod_CAPB = ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_DEV_T allocDev;
	LX_AUD_MOD_TYPE_T				modTypeToAlloc;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	filp->private_data = kmalloc(sizeof(AUD_DEVICE_T), GFP_KERNEL);
	my_dev = (AUD_DEVICE_T*)filp->private_data;

	/* Set device */
	devType = DEV_TYPE_BASE + nMinor;
	my_dev->devType = devType;

	//my_dev->devType = LX_AUD_CAPTURER;

	OpenInfo.devType = devType;

	allocDev = AUDIO_AllocDev(&OpenInfo);
	if(allocDev == AUD_NO_DEV)
	{
		AUD_KDRV_RMD(" %s is not available \n",devTypeStr[devType]);
		goto KDRV_OPEN_ERROR;
	}

	AUD_KDRV_RM("%s is opened[major:%d minor:%d][Alloc:%s] \n",devTypeStr[devType],nMajor,nMinor,(char *)allocDev_Str[allocDev]);

	my_dev->allocDev =  allocDev;

	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR("[%s] capIndex[%d] is not available. \n", __F__, capIndex);
		return RET_ERROR;
	}

	memset(&(_gCapturerInfo[capIndex]), 0x0, sizeof(AUD_CAPTURER_INFO_T));
	_gCapturerInfo[capIndex].ui32Volume = 0xFFFFFFFF;

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

	// get CAP buffer
	modTypeToAlloc = LX_AUD_CAPB;
	allocMod_CAPB = AUDIO_AllocModule(my_dev->allocDev, modTypeToAlloc, 0);
	if(allocMod_CAPB == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
		return RET_ERROR;
	}

	AUD_KDRV_RM("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_CAPB]);

	return retVal;

KDRV_OPEN_ERROR:
	kfree(filp->private_data);
	return RET_ERROR;
}

/**
 * close handler for audio Capture device
 *
 */
SINT32	KDRV_AUDIO_CloseCapture(struct inode *inode, struct file *filp)
{
	SINT32 retVal = 0;
	UINT32 nMajor;
	UINT32 nMinor;

	AUD_DEVICE_T*	my_dev;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	my_dev = (AUD_DEVICE_T*)filp->private_data;

	kfree(filp->private_data);

	AUD_KDRV_RM("Close Capture device file  (%d:%d)\n", nMajor, nMinor);

	return retVal;
}

static SINT32	AUDIO_CloseCapture(AUD_DEVICE_T* audDev)
{
	SINT32							retVal = 0;
	SINT32							capIndex = 0;
	UINT32							devType;
	LX_AUD_ALLOC_FREE_INFO_T		CloseInfo;
	LX_AUD_ALLOC_DEV_T				allocDev = AUD_NO_DEV;
	LX_AUD_ALLOC_MOD_T				allocMod_SRC = ADEC_MODULE_NO_MOD;
	SrcCmdSetGain					srcSetGain;

	/* Set device */
	devType = audDev->devType;
	allocDev = audDev->allocDev;

	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR(" capIndex[%d] is not available. \n", capIndex);
		return RET_ERROR;
	}

	AUDIO_DisconnectAllInDev(allocDev);

	allocMod_SRC = AUDIO_HasThisModuleType(allocDev, LX_AUD_SRC1);
	if(allocMod_SRC != ADEC_MODULE_NO_MOD)
	{
		srcSetGain.GainEnable	= 0;
		srcSetGain.Gain			= 0xFFFFFFFF;

		AUDIO_IMC_SendCmdParam(SRC_CMD_SET_GAIN, allocMod_SRC, sizeof(SrcCmdSetGain), &srcSetGain);

		_gCapturerInfo[capIndex].ui32Volume = 0xFFFFFFFF;
	}

	CloseInfo.devType = devType;
	CloseInfo.allocDev = allocDev;

	retVal = AUDIO_FreeDev(&CloseInfo);

	if(retVal == AUD_NO_DEV)
	{
		AUD_KDRV_RMD(" All %s is already freed \n",devTypeStr[devType]);
	}
	else
	{
		AUD_KDRV_RMD("%s is closed[Freed:%s]\n", devTypeStr[devType], (char *)allocDev_Str[retVal]);
	}



	AUD_KDRV_PRINT("%s : alloc Device %d.\n", __F__, allocDev);

	return RET_OK;
}


/**
 * ioctl handler for audio Capture device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int KDRV_AUDIO_IoctlCapture(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#else
long KDRV_AUDIO_IoctlCapture(struct file *filp, unsigned int cmd, unsigned long arg)
#endif
{
	SINT32				retVal = 0;
	SINT32				err = 0;
	AUD_DEVICE_T*		my_dev;
	UINT32				allocDev;

	my_dev = (AUD_DEVICE_T*)filp->private_data;

	allocDev = my_dev->allocDev;

	/*
	* check if IOCTL command is valid or not.
	* - if magic value doesn't match, return error (-ENOTTY)
	* - if command is out of range, return error (-ENOTTY)
	*
	* note) -ENOTTY means "Inappropriate ioctl for device.
	*/
	if (_IOC_TYPE(cmd) != AUD_CAP_IOC_MAGIC)
	{
		DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > AUD_CAP_IOC_MAXNR)
	{
		DBG_PRINT_WARNING("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
		return -ENOTTY;
	}

	/*
	* check if user memory is valid or not.
	* if memory can't be accessed from kernel, return error (-EFAULT)
	*/
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err)
	{
		DBG_PRINT_WARNING("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
							_IOC_NR(cmd),
							(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
							(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
							(void*)arg );
		return -EFAULT;
	}

	AUD_KDRV_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd));

	switch(cmd)
	{
		case AUD_CAP_IO_START:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_CAP_IOW_START] Called\n", __F__, __L__);
			AUDIO_StartCapturer(allocDev);
			retVal = RET_OK;
		}
		break;

		case AUD_CAP_IO_STOP:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_CAP_IOW_STOP] Called\n", __F__, __L__);
			AUDIO_StopCapturer(allocDev);
			retVal = RET_OK;
		}
		break;

		case AUD_CAP_IO_FLUSH:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_CAP_IOW_FLUSH] Called\n", __F__, __L__);
			AUDIO_FlushCapturer(allocDev);
			retVal = RET_OK;
		}
		break;

		case AUD_CAP_IOW_SET_VOLUME:
		{
			UINT32		capVolume;

			AUD_KDRV_TRACE("AUD_CAP_IOW_SET_VOLUME\n");

			if(copy_from_user(&capVolume, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			retVal = AUDIO_SetCaptureVolume(allocDev, capVolume);
		}
		break;

		case AUD_CAP_IOW_SET_PARAM:
		{
			LX_AUD_CAPTURE_PARAM_T		capParam;

			AUD_KDRV_TRACE("AUD_CAP_IOW_SET_PARAM_CODING\n");

			if(copy_from_user(&capParam, (void __user *)arg, sizeof(LX_AUD_CAPTURE_PARAM_T)))
				return RET_ERROR;

			retVal = AUDIO_SetCaptureParam(allocDev, &capParam);
		}
		break;

		case AUD_CAP_IOR_GET_CAPTURED_INFO:
		{
			LX_AUD_CAPTURE_CAPTURED_INFO_T	capInfo;

			AUD_KDRV_TRACE("AUD_CAP_IOW_GET_CAPTURED_INFO\n");

			retVal = AUDIO_GetCapturedInfo(allocDev, &capInfo);
			if(retVal != RET_OK)
				return RET_ERROR;

			if(copy_to_user((void *)arg, (void *)&capInfo, sizeof(LX_AUD_CAPTURE_CAPTURED_INFO_T)))
				return RET_ERROR;
		}
		break;

		case AUD_CAP_IOWR_GET_CAPTURED_DATA:
		{
			LX_AUD_CAPTURE_CAPTURED_DATA_T	capData;

			AUD_KDRV_TRACE("AUD_CAP_IOW_GET_CAPTURED_DATA\n");

			if(copy_from_user(&capData, (void __user *)arg, sizeof(LX_AUD_CAPTURE_CAPTURED_DATA_T)))
				return RET_ERROR;

			retVal = AUDIO_GetCapturedData(allocDev, &capData);
			if(retVal != RET_OK)
				return RET_ERROR;

			if(copy_to_user((void *)arg, (void *)&capData, sizeof(LX_AUD_CAPTURE_CAPTURED_DATA_T)))
				return RET_ERROR;
		}
		break;

		case AUD_CAP_IOR_GET_KDRV_HANDLE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_CAP_IOW_GET_KDRV_HANDLE] Called\n", __F__, __L__);

			if(copy_to_user((void *)arg, (void *)&(my_dev->allocDev), sizeof(UINT32)))
				return RET_ERROR;
		}
		break;

		case AUD_CAP_IOW_CONNECT:
		{
			UINT32									connectDev;

			AUD_KDRV_TRACE("%s.%d: [AUD_CAP_IOW_CONNECT] Called\n", __F__, __L__);

			if(copy_from_user(&connectDev, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			retVal = AUDIO_ConnectCapturer(allocDev, connectDev);
		}
		break;

		case AUD_CAP_IOW_DISCONNECT:
		{
			UINT32									disconnectDev;

			AUD_KDRV_TRACE("%s.%d: [AUD_CAP_IOW_DISCONNECT] Called\n", __F__, __L__);

			if(copy_from_user(&disconnectDev, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			retVal = AUDIO_DisconnectCapturer(allocDev, disconnectDev);
		}
		break;

		case AUD_CAP_IO_CLOSE_DEVICE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_CAP_IO_CLOSE_DEVICE] Called\n", __F__, __L__);
			retVal = AUDIO_CloseCapture(my_dev);
		}
		break;


		default:
		{
			/* redundant check but it seems more readable */
			DBG_PRINT_ERROR("Invalid IOCTL Call!!!\n");
			retVal = RET_INVALID_IOCTL;
		}
		break;
	}

	return retVal;
}

/**
 * Set SRC format.
 *
 * @param 	allocMod		[in] a allocated SRC module.
 * @param 	sampleFreq		[in] sampling frequency.
 * @param 	numOfChannel	[in] the number of channels.
 * @param 	bitPerSample	[in] the bit per a sample.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		AUDIO_ConnectCapturer()
 */
static void _AUDIO_SetSRCFormatForCatupre(UINT32 allocMod, UINT32 sampleFreq, UINT32 numOfChannel, UINT32 bitPerSample)
{
	SrcCmdSetAllfmt	srcSetFmt;
	SrcCmdSetOverProtect srcOverProtect;

	srcSetFmt.InFs		= LX_AUD_SAMPLING_FREQ_48_KHZ;
	srcSetFmt.InCh		= 2;
	srcSetFmt.InFormat	= 32;
	srcSetFmt.InEndian	= LX_AUD_RENDER_LITTLE_ENDIAN;
	srcSetFmt.InSigned	= LX_AUD_RENDER_SIGNED;
	srcSetFmt.OutFs		= sampleFreq;
	srcSetFmt.OutCh		= numOfChannel;
	srcSetFmt.OutFormat	= bitPerSample;

	if(AUDIO_IMC_SendCmdParam(SRC_CMD_SET_ALLFMT, allocMod, sizeof(SrcCmdSetAllfmt), &srcSetFmt))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(SRC_CMD_SET_ALLFMT) Err\n", __FUNCTION__, __LINE__);
	}

	srcOverProtect.over_protect = USE_OVERFLOW_PROTECTION;

	if(AUDIO_IMC_SendCmdParam(SRC_CMD_SET_OVERPROTECT, allocMod, sizeof(SrcCmdSetFmt), &srcOverProtect))
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(SRC_CMD_SET_OVERPROTECT) Err\n", __FUNCTION__, __LINE__);
	}

	return;
}

/**
 * Start Capturer.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_RestartCapturer()
 */
static SINT32 AUDIO_StartCapturer (UINT32 allocDev)
{
	UINT32			allocModNum;
	LX_AUD_MOD_T	*pOwnMods;
	UINT32			i;
	int				retVal = RET_OK;
	SINT32			capIndex = 0;
	LX_AUD_CAPTURE_PARAM_T	*pCaptureParam = NULL;

	if(allocDev < AUD_DEV_CAP0 || allocDev > AUD_DEV_CAP2)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}

	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR(" renIndex[%d] is not available. \n", capIndex);
		return RET_ERROR;
	}
	pCaptureParam = &(_gCapturerInfo[capIndex].capParam);

	//get alloc module info in given device node
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if(pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX)
		{
			//Send a IMC command - INIT & START
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_INIT, pOwnMods[i].mod);		// need to init SRC before start SRC by gunho.song
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_START, pOwnMods[i].mod);
			AUD_KDRV_PRINT("Send START CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
		}
	}

	_gCapturerInfo[capIndex].bStarted = TRUE;

	return retVal;
}

/**
 * Stop Capturer.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_ResetCapturer()
 */
static SINT32 AUDIO_StopCapturer (UINT32 allocDev)
{
	UINT32			allocModNum;
	LX_AUD_MOD_T	*pOwnMods;
	UINT32			i;
	SINT32			retVal = RET_OK;

	if(allocDev < AUD_DEV_CAP0 || allocDev > AUD_DEV_CAP2)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}
	//get alloc module info in given device node
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if(pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX)
		{
			//Send a IMC command - STOP
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_STOP, pOwnMods[i].mod);		// need to init SRC before start SRC by gunho.song
			AUD_KDRV_PRINT("Send STOP CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
		}
	}

	return retVal;
}

/**
 * Flush Capturer.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_ResetCapturer()
 */
static SINT32 AUDIO_FlushCapturer (UINT32 allocDev)
{
	UINT32			allocModNum;
	LX_AUD_MOD_T	*pOwnMods;
	UINT32			i;
	SINT32			retVal = RET_OK;

	if(allocDev < AUD_DEV_CAP0 || allocDev > AUD_DEV_CAP2)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}
	//get alloc module info in given device node
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if(pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX)
		{
			//Send a IMC command - STOP
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_FLUSH, pOwnMods[i].mod);		// need to init SRC before start SRC by gunho.song
			AUD_KDRV_PRINT("Send FLUSH CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
		}
	}

	return retVal;
}

/**
 * Sets volume for capturer.
 * Controls the volume function.
 * @see
*/
static SINT32 AUDIO_SetCaptureVolume (UINT32 allocDev, UINT32 volume)
{
	SINT32						capIndex = 0;
	LX_AUD_ALLOC_MOD_T			allocMod_SRC = ADEC_MODULE_NO_MOD;
	LX_AUD_CAPTURE_PARAM_T		*pCapInfoParam;

	SrcCmdSetGain				srcSetGain;

	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR(" capIndex[%d] is not available. \n", capIndex);
		return RET_ERROR;
	}

	pCapInfoParam = &_gCapturerInfo[capIndex].capParam;

	if(pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_DECODER_PCM)
	{
		allocMod_SRC = AUDIO_HasThisModuleType(allocDev, LX_AUD_SRC_DEC);
		if(allocMod_SRC == ADEC_MODULE_NO_MOD )
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n", modTypeStr[LX_AUD_SRC1]);
			return RET_ERROR;
		}
	}
	else
	{
		allocMod_SRC = AUDIO_HasThisModuleType(allocDev, LX_AUD_SRC1);
		if(allocMod_SRC == ADEC_MODULE_NO_MOD )
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n", modTypeStr[LX_AUD_SRC1]);
			return RET_ERROR;
		}
	}

	srcSetGain.GainEnable	= 1;
	srcSetGain.Gain			= volume;
	AUDIO_IMC_SendCmdParam(SRC_CMD_SET_GAIN, allocMod_SRC, sizeof(SrcCmdSetGain), &srcSetGain);

	_gCapturerInfo[capIndex].ui32Volume = volume;

	AUD_KDRV_PRINT("%s : vol %x \n", __F__, volume);
	return RET_OK;
}


/**
 * Connect other device to Capturer.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @param 	connectDev		[in] Device to connect.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlCapture(), KDRV_AUDIO_ResetCapturerParam().
 */
static SINT32 AUDIO_ConnectCapturer(UINT32 allocDev, UINT32 connectDev)
{
	UINT32 	left, right;
	UINT32 	leftManagerModule, rightManagerModule;
	UINT32	tempLeft, tempRight;
	SINT32 	capIndex = 0;

	LX_AUD_ALLOC_FREE_INFO_T *connectDevInfo ,*capDevInfo,*capModInfo;
	LX_AUD_CAPTURE_PARAM_T *pCapInfoParam;
	LX_AUD_MOD_TYPE_T			modTypeToAlloc;

	LX_AUD_ALLOC_MOD_T  allocMod_SE	= ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T	allocMod_DEC	= ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T  allocMod_SRC	= ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T 	allocMod_Bypass_DSP0 = ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T 	allocModule_ENC = ADEC_MODULE_NO_MOD;

	/* Get a Capturer Index */
	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR("[%s] capIndex[%d] is not available. \n", __F__, capIndex);
		return RET_ERROR;
	}

	pCapInfoParam = &_gCapturerInfo[capIndex].capParam;

	capDevInfo = AUDIO_GetAllocDevInfo(allocDev);
	connectDevInfo = AUDIO_GetAllocDevInfo(connectDev);

	if(connectDevInfo == NULL || capDevInfo == NULL)
	{
		AUD_KDRV_DEBUG(" Check connectDevInfo[%p] capDevInfo[%p] \n",connectDevInfo,capDevInfo);
		return RET_ERROR;
	}

	if (connectDevInfo->headOfDev == NULL ||  connectDevInfo->tailOfDev == NULL ||
	    capDevInfo->headOfDev == NULL ||  capDevInfo->tailOfDev == NULL)
	{
		AUD_KDRV_ERROR("========== CAUTION ============ \n");
		AUD_KDRV_ERROR("CAP head[%p] tail[%p]  CON [%p] [%p] \n",capDevInfo->headOfDev, capDevInfo->tailOfDev,connectDevInfo->headOfDev, connectDevInfo->tailOfDev );
		return RET_ERROR;
	}

	tempLeft 	= ((LX_AUD_ALLOC_FREE_INFO_T *) (connectDevInfo->tailOfDev))->allocMod;
	tempRight 	= ((LX_AUD_ALLOC_FREE_INFO_T *) (capDevInfo->headOfDev))->allocMod;

	leftManagerModule = _AUDIO_GetManagerModule(tempLeft);
	rightManagerModule = _AUDIO_GetManagerModule(tempRight);

	if(connectDevInfo->devType == LX_AUD_DEV_ENC)
	{
		if(leftManagerModule != rightManagerModule)
		{
			allocModule_ENC = AUDIO_HasThisModuleType(connectDev, LX_AUD_ENC);

			if(allocModule_ENC != ADEC_MODULE_NO_MOD)
			{
				left  =	allocModule_ENC;
				right =	((LX_AUD_ALLOC_FREE_INFO_T *)(capDevInfo->headOfDev))->allocMod;
				AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
			}
			else
			{
				AUD_KDRV_RMD("No ENC module  in connectDev\n");
				return RET_ERROR;
			}
		}
	}
	else if(connectDevInfo->devType ==LX_AUD_DEV_MAS)
	{
		if(pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_SE)
		{
			//se end capture
			allocMod_SE = AUDIO_HasThisModuleType(connectDev, LX_AUD_SE);
			if(allocMod_SE != ADEC_MODULE_NO_MOD)
			{
				tempLeft =	allocMod_SE;
			}
		}
		else if(pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_MIXER)
		{
			//mix end capture
			tempLeft = ((LX_AUD_ALLOC_FREE_INFO_T *) (connectDevInfo->headOfDev))->allocMod;
		}
		else
		{
			allocMod_SE = AUDIO_HasThisModuleType(connectDev, LX_AUD_SE);
			if ( allocMod_SE != ADEC_MODULE_NO_MOD )
			{
				tempLeft =	allocMod_SE;
			}
		}

		//cap
		tempRight 	= ((LX_AUD_ALLOC_FREE_INFO_T *) (capDevInfo->headOfDev))->allocMod;

		leftManagerModule = _AUDIO_GetManagerModule(tempLeft);
		rightManagerModule = _AUDIO_GetManagerModule(tempRight);

		//if (leftManagerModule != rightManagerModule )
		{
			// get Bypass DSP1 in DEC device
			modTypeToAlloc	= LX_AUD_SRC1;
			allocMod_SRC = AUDIO_AllocModule(allocDev,modTypeToAlloc, 0);
			if(allocMod_SRC != ADEC_MODULE_NO_MOD)
			{
				AUD_KDRV_RMD("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_SRC]);
			}
			else
			{
				AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
				return RET_ERROR;
			}

			left = allocMod_SRC;
			right = tempRight; //capb
										//bypass_dsp1               //capb
			if(AUDIO_IsNotConnectedYet(left, right))
			{
				AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
			}

			//Send a IMC command - Set PCM format
			_AUDIO_SetSRCFormatForCatupre(allocMod_SRC,
											pCapInfoParam->samplingFreq,
											pCapInfoParam->ui32NumOfChannel,
											pCapInfoParam->ui32BitPerSample);

			//Send a IMC command - INIT & START
			AUDIO_IMC_SendCmd(ADEC_CMD_INIT, allocMod_SRC);
			AUDIO_IMC_SendCmd(ADEC_CMD_START, allocMod_SRC);
			AUD_KDRV_PRINT("Send START CMD [%s] \n",allocMod_Str[allocMod_SRC]);

			//mix0
			left	 = tempLeft;
			right	 = allocMod_SRC;

			if(AUDIO_IsNotConnectedYet(left, right))
			{
				AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
			}

		}
	}
	else if(connectDevInfo->devType == LX_AUD_DEV_DEC)
	{
		tempRight = ((LX_AUD_ALLOC_FREE_INFO_T *) (capDevInfo->headOfDev))->allocMod;

		if (pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_DECODER_ES && pCapInfoParam->codecType == LX_AUD_CODEC_AAC_BYPASS )
		{
			//cap module
			right = tempRight;

			//BYPASS_ES_DSP0 module
			left = AUDIO_HasThisModuleType(connectDev, LX_AUD_BYPASS_ES_DSP0);

			if(left != ADEC_MODULE_NO_MOD)
			{
				if(AUDIO_IsNotConnectedYet(left, right))
				{
					AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
					return RET_OK;
				}
			}
		}
		else
		{

			if(pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_DECODER_ES)
			{
				// get Bypass DSP1 in DEC device
				modTypeToAlloc	= LX_AUD_BYPASS_DSP0;

				allocMod_Bypass_DSP0 = AUDIO_AllocModule(allocDev, modTypeToAlloc , 0);
				if(allocMod_Bypass_DSP0 != ADEC_MODULE_NO_MOD )
				{
					AUD_KDRV_RMD("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_Bypass_DSP0]);
				}
				else
				{
					AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
					return RET_ERROR;
				}

				// Set a default lip sync on and buffer overflow disable mode
				AUDIO_SetBypassMode(allocMod_Bypass_DSP0, AU_BASED_MODE, NO_OVERFLOW_PROTECTION);
				left =	allocMod_Bypass_DSP0;
			}
			else
			{
				// get SRC_DEC in DEC device
				modTypeToAlloc	= LX_AUD_SRC_DEC;
				allocMod_SRC = AUDIO_AllocModule(allocDev,modTypeToAlloc, 0);
				if(allocMod_SRC != ADEC_MODULE_NO_MOD)
				{
					AUD_KDRV_RMD("Module[%s] [Alloc:%s] \n",modTypeStr[modTypeToAlloc],(char *)allocMod_Str[allocMod_SRC]);
				}
				else
				{
					AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[modTypeToAlloc]);
					return RET_ERROR;
				}

				//Send a IMC command - Set PCM format
				_AUDIO_SetSRCFormatForCatupre(allocMod_SRC,
												pCapInfoParam->samplingFreq,
												pCapInfoParam->ui32NumOfChannel,
												pCapInfoParam->ui32BitPerSample);
				left = allocMod_SRC;
			}
			right =	tempRight;

			AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);

			allocMod_DEC = AUDIO_HasThisModuleType(connectDev, LX_AUD_DEC);
			if(allocMod_DEC != ADEC_MODULE_NO_MOD)
			{
				if(AUDIO_IsNotConnectedYet(allocMod_DEC, left))
				{
					if(pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_DECODER_ES)
					{
						capModInfo = AUDIO_GetAllocModInfo(left);
						capModInfo->needToConnectToIntra = 1;
					}
				}

				AUDIO_ConnectTo(allocMod_DEC, left, NO_FORCE, NO_FORCE);
			}

		}

	}

	_gCapturerInfo[capIndex].captureConnect.connectDev = connectDev;

	AUD_KDRV_RMD("AUDIO_ConnectCapturer : A%d, C%d\n", allocDev, connectDev);
	return RET_OK;
}

/**
 * Disconnect Capture device From Other Device.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @param 	connectDev		[in] Device to connect.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlCapture(), KDRV_AUDIO_ResetCapturer().
 */
static SINT32 AUDIO_DisconnectCapturer (UINT32 allocDev, UINT32 disconnectDev)
{
	UINT32	left, right;
	UINT32	allocMod_DEC	= ADEC_MODULE_NO_MOD;
	SINT32	capIndex = 0;

	LX_AUD_ALLOC_MOD_T 	allocModule_ENC = ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T	allocMod_SE= ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T	tempLeft = ADEC_MODULE_NO_MOD;

	LX_AUD_CAPTURE_PARAM_T 	 *pCapInfoParam;
	LX_AUD_ALLOC_FREE_INFO_T *disConnectDevInfo,*capDevInfo;

	/* Get a Capturer Index */
	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR("[%s] capIndex[%d] is not available. \n", __F__, capIndex);
		return RET_ERROR;
	}

	pCapInfoParam = &_gCapturerInfo[capIndex].capParam;
	disConnectDevInfo = AUDIO_GetAllocDevInfo(disconnectDev);
	capDevInfo = AUDIO_GetAllocDevInfo(allocDev);

	if(disConnectDevInfo == NULL || capDevInfo == NULL)
	{
		AUD_KDRV_DEBUG(" Check disConnectDevInfo[%p] capDevInfo[%p] \n",disConnectDevInfo,capDevInfo);
		return RET_ERROR	;
	}

	if (disConnectDevInfo->headOfDev == NULL ||  disConnectDevInfo->tailOfDev == NULL ||
	capDevInfo->headOfDev == NULL ||  capDevInfo->tailOfDev == NULL)
	{
		AUD_KDRV_ERROR("========== CAUTION ============ \n");
		AUD_KDRV_ERROR("CAP head[%p] tail[%p]  DISCON [%p] [%p] \n",capDevInfo->headOfDev, capDevInfo->tailOfDev,disConnectDevInfo->headOfDev, disConnectDevInfo->tailOfDev );
		return RET_ERROR;
	}

	if(disConnectDevInfo->devType == LX_AUD_DEV_ENC)
	{
		allocModule_ENC = AUDIO_HasThisModuleType(disconnectDev, LX_AUD_ENC);

		if(allocModule_ENC != ADEC_MODULE_NO_MOD)
		{
			left  =	allocModule_ENC;
			right =	((LX_AUD_ALLOC_FREE_INFO_T *)(capDevInfo->headOfDev))->allocMod;
		}
		else
		{
			AUD_KDRV_RMD("No ENC module in disconnectDev\n");
			return RET_ERROR;
		}
	}
	else if(disConnectDevInfo->devType ==LX_AUD_DEV_MAS)
	{
		if(pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_SE)
		{
			//se end capture
			allocMod_SE = AUDIO_HasThisModuleType(disconnectDev, LX_AUD_SE);
			if ( allocMod_SE != ADEC_MODULE_NO_MOD )
			{
				tempLeft = allocMod_SE;
			}
		}
		else if(pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_MIXER)
		{
			//mix end capture
			tempLeft = ((LX_AUD_ALLOC_FREE_INFO_T *) (disConnectDevInfo->headOfDev))->allocMod;
		}
		else
		{
			allocMod_SE = AUDIO_HasThisModuleType(disconnectDev, LX_AUD_SE);
			if(allocMod_SE != ADEC_MODULE_NO_MOD )
			{
				tempLeft = allocMod_SE;
			}
		}

		//mix0
		left	 = tempLeft;
		//bypass_dsp1
		right	 = ((LX_AUD_ALLOC_FREE_INFO_T *) (capDevInfo->headOfDev))->allocMod;
	}

	else if(disConnectDevInfo->devType ==LX_AUD_DEV_DEC && pCapInfoParam->capInput == LX_AUD_CAPTURE_INPUT_DECODER_ES && pCapInfoParam->codecType == LX_AUD_CODEC_AAC_BYPASS )
	{
		//BYPASS_ES_DSP0 module
		left = AUDIO_HasThisModuleType(disconnectDev, LX_AUD_BYPASS_ES_DSP0);

		//cap module
		right = ((LX_AUD_ALLOC_FREE_INFO_T *) (capDevInfo->headOfDev))->allocMod;

		if(left != ADEC_MODULE_NO_MOD)
		{
			if(AUDIO_IsNotConnectedYet(left, right))
			{
				AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
				return RET_OK;
			}
		}


	}
	else
	{
		allocMod_DEC = AUDIO_HasThisModuleType(disconnectDev, LX_AUD_DEC);

		if(allocMod_DEC != ADEC_MODULE_NO_MOD)
		{
			left =	allocMod_DEC;
			right =	((LX_AUD_ALLOC_FREE_INFO_T *) (capDevInfo->headOfDev))->allocMod;
		}
		else
		{
			AUD_KDRV_RMD("No DEC module  in otherDEV\n");
			return RET_ERROR;
		}
	}

	AUDIO_DisconnectTo(left, right, NO_FORCE, NO_FORCE);

	return RET_OK;
}


/**
 * Set Capturer Parameter.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @param 	pcapParam		[in] param to set.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlCapture(), KDRV_AUDIO_ResetCapturerParam().
 */
static SINT32 AUDIO_SetCaptureParam(UINT32 allocDev, LX_AUD_CAPTURE_PARAM_T *pCapParam)
{
	SINT32 capIndex = 0;
	LX_AUD_CAPTURE_PARAM_T *pCapInfoParam;

	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR("[%s] capIndex[%d] is not available. \n", __F__, capIndex);
		return RET_ERROR;
	}

	pCapInfoParam = &_gCapturerInfo[capIndex].capParam;

	memcpy(pCapInfoParam, pCapParam, sizeof(LX_AUD_CAPTURE_PARAM_T));

	return RET_OK;
}

/**
 * Get Captured information.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @param 	pCapInfo		[in] captured information.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlCapture(), KDRV_AUDIO_ResetCapturerParam().
 */
static SINT32 AUDIO_GetCapturedInfo(UINT32 allocDev, LX_AUD_CAPTURE_CAPTURED_INFO_T *pCapInfo)
{
	SINT32			retVal = RET_OK;
	SINT32			usedSize = 0;
	SINT32			freeSize = 0;
	SINT32			auCount  = 0;
	SINT32 			auOffset = 0;
	SINT32			capIndex = 0;
	ADEC_BUF_T  	*pCapReader = NULL;
	LX_AUD_AU_INFO_T  auInfo;

	//Sanity check
	if(pCapInfo == NULL)
	{
		AUD_KDRV_ERROR("AUDIO_GetCapturedInfo : error!!!(pCapInfo = %p)\n", pCapInfo);
		return RET_ERROR;
	}

	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR("[%s] capIndex[%d] is not available. \n", __F__, capIndex);
		return RET_ERROR;
	}

	//Set a default value
	pCapInfo->ui32WriteIndex = 0;
	pCapInfo->ui32SizeOfAu = 0;
	pCapInfo->ui32RemainIndex = 0;
	pCapInfo->ui32UsedSize = 0;
	pCapInfo->ui32FreeSize = 0;

	//Assign a PCM buffer
	pCapReader = (ADEC_BUF_T *)stCAP[capIndex].pWriterReaderStruct; 	//ADEC_COMMON_BUF_T *

	//Read a used PCM buffer size
	usedSize = pCapReader->get_used_size(pCapReader);
	freeSize = pCapReader->get_free_size(pCapReader);

	//Check a current buffer size
	if( usedSize <= 0 && freeSize < 0 )
	{
		AUD_KDRV_PRINT("AUDIO_GetCapturedInfo : used size = %d, free size = %d\n", usedSize, freeSize);
		return RET_OK;
	}

	//Read a ES AUI Count info.
	auCount = pCapReader->get_au_cnt(pCapReader);
	if(auCount < 2)
	{
		AUD_KDRV_PRINT("AUDIO_GetCapturedInfo : No AU Data(auCount = %d)\n", auCount);
		return RET_OK;
	}

	//Read a current ES AUI info.
	retVal = pCapReader->get_au_info(0, &auOffset, (ADEC_AU_INFO_T *)&auInfo, pCapReader);
	if(retVal != RET_OK)
	{
		AUD_KDRV_ERROR("AUDIO_GetCapturedInfo : get_au_info(ret = %d)\n", retVal);
		return RET_ERROR;
	}

	//Check a current offset for AAC encoder
	if(_gCapturerInfo[capIndex].capParam.codecType == LX_AUD_CODEC_AAC_ENC)
	{
		if(auInfo.ui64Size + auOffset <= 0)
		{
			AUD_KDRV_ERROR("AUDIO_GetCapturedInfo : AAC_ENC auInfo.size = %llu, auOffset = %d\n",	\
							auInfo.ui64Size, auOffset);
			return RET_ERROR;
		}
	}

	//Set a current AU index and size of AU
	pCapInfo->ui32WriteIndex  = (UINT32)auInfo.ui32Index;
	pCapInfo->ui32SizeOfAu    = (UINT32)auInfo.ui64Size;
	pCapInfo->ui32RemainIndex = (UINT32)(auCount - 1);
	pCapInfo->ui32UsedSize    = usedSize;
	pCapInfo->ui32FreeSize    = freeSize;

	AUD_KDRV_PRINT("AUDIO_GetCapturedInfo : wr idx = %d, size = %d\n",	pCapInfo->ui32WriteIndex, pCapInfo->ui32SizeOfAu);
	return RET_OK;
}

/**
 * Get Captured data.
 *
 * @param 	allocDev		[in] a allocated capture device.
 * @param 	pCapData		[in] captured data.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlCapture().
 */
static SINT32 AUDIO_GetCapturedData(UINT32 allocDev, LX_AUD_CAPTURE_CAPTURED_DATA_T *pCapData)
{
 	SINT32			retVal = RET_OK;
	SINT32			usedSize = 0;
	SINT32			freeSize = 0;
	SINT32 			auOffset = 0;
	SINT32 			auReadSize = 0;
	SINT32			auCount  = 0;
	SINT32			capIndex = 0;
	UINT8			*pDataBuf = NULL;
	ADEC_BUF_T		*pCapReader  = NULL;

	//Sanity check
	if((pCapData->pBuffer == NULL) && (pCapData->ui32BufSize != 0))
	{
		AUD_KDRV_ERROR("[%s] error!!!(pBuffer = %p, bufSize = %d)\n", __F__, pCapData->pBuffer, pCapData->ui32BufSize);
		return RET_ERROR;
	}

	capIndex = GET_CAP_INDEX(allocDev);
	if((capIndex < 0) || (capIndex >= DEV_CAP_NUM))
	{
		AUD_KDRV_ERROR("[%s] capIndex[%d] is not available. \n", __F__, capIndex);
		return RET_ERROR;
	}

	pCapReader = (ADEC_BUF_T *)stCAP[capIndex].pWriterReaderStruct; 	//ADEC_COMMON_BUF_T *

	//flush buffer
	if((pCapData->pBuffer == NULL) || (pCapData->ui32BufSize == 0))
	{
		//Read a used CAP(ES/PCM) buffer size
		usedSize = pCapReader->get_used_size(pCapReader);

		//Check a remain data size.
		if(usedSize > AUD_PCM_200MSEC)
		{
			//Flush a current AUI and AU data
			retVal	= pCapReader->flush_data(usedSize - AUD_PCM_200MSEC, pCapReader);
			if(retVal != RET_OK)
			{
				AUD_KDRV_ERROR("AUDIO_GetCapturedData : flush_data(ret = %d)\n", retVal);
				return RET_ERROR;
			}
			else
			{
				AUD_KDRV_PRINT("AUDIO_GetCapturedData : flush_data(ret = %d)\n", retVal);
				return RET_OK;
			}
		}
		else
		{
			AUD_KDRV_DEBUG("AUDIO_GetCapturedData : flush_data(used = %d)(ret = %d)\n", usedSize, retVal);
			return RET_OK;
		}
	}

	//Set a default value
	memset((void *)&pCapData->auInfo, 0x0, sizeof(LX_AUD_AU_INFO_T));
	pCapData->ui32RemainIndex = 0;
	pCapData->ui32UsedSize = 0;
	pCapData->ui32FreeSize = 0;

	//Read a AUI Count info.
	auCount = pCapReader->get_au_cnt(pCapReader);
	if(auCount >= 2)
	{
		pCapData->ui32RemainIndex = (UINT16)(auCount - 1);
	}
	else
	{
		AUD_KDRV_PRINT("ADEC_L9_GetEncodingInfo : No AU Data\n" );
		return RET_OK;
	}

	//Read a current AUI info.
	retVal = pCapReader->get_au_info(0, &auOffset, (ADEC_AU_INFO_T *)&pCapData->auInfo, pCapReader);
	if(retVal != RET_OK)
	{
		AUD_KDRV_ERROR("AUDIO_GetCapturedData : get_au_info(ret = %d)\n", retVal);
		return RET_ERROR;
	}
	//	AENCReader->get_au_info(1, &au_offset, &auInfo, AENCReader); // 2ÀÏ °æ¿ì

	//Read a used CAP buffer size
	usedSize = pCapReader->get_used_size(pCapReader);

	//Read a free CAP buffer size
	freeSize = pCapReader->get_free_size(pCapReader);

	//Check a AU read size and used size for AAC encoder
	if(_gCapturerInfo[capIndex].capParam.codecType == LX_AUD_CODEC_AAC_ENC)
	{
		if(pCapData->ui32BufSize != (UINT32)pCapData->auInfo.ui64Size)
		{
			AUD_KDRV_ERROR("AUDIO_GetCapturedData : AAC_ENC bufSize error(buf = %d, auSize = %d, used = %d)\n", \
							pCapData->ui32BufSize, (UINT32)pCapData->auInfo.ui64Size, usedSize);

			return RET_ERROR;
		}
	}
	else	//LX_AUD_CODEC_PCM
	{
		if(pCapData->ui32BufSize > (UINT32)usedSize)
		{
			AUD_KDRV_ERROR("AUDIO_GetCapturedData : PCM bufSize error(buf = %d, auSize = %d, used = %d)\n", \
							pCapData->ui32BufSize, (UINT32)pCapData->auInfo.ui64Size, usedSize);

			return RET_ERROR;
		}
	}

	//Compute a AU read offset and size
	auReadSize = (SINT32)pCapData->ui32BufSize + auOffset;

	//Read a AU PCM data from buffer
	retVal = pCapReader->read_data(&pDataBuf, &auReadSize, NULL, pCapReader);
	if(retVal != RET_OK)
	{
		AUD_KDRV_ERROR("AUDIO_GetCapturedData : read_data(ret = %d)\n", retVal);
		return RET_ERROR;
	}

	//Check a AU read size for AAC encoder : This code must be check if PCM data has error.
	//////////////////////////////////////////////////////////////////////////////////////
	if(_gCapturerInfo[capIndex].capParam.codecType == LX_AUD_CODEC_AAC_ENC)
	{
		if(auReadSize != (SINT32)pCapData->ui32BufSize)
		{
			pCapData->auInfo.ui64Size = (UINT64)auReadSize;

			AUD_KDRV_ERROR("AUDIO_GetCapturedData : read size error(%d)\n", auReadSize);
			return RET_ERROR;
		}
	}

	//Check a copy size for allocated memory from user space memory.
	if(auReadSize <= (SINT32)pCapData->ui32BufSize)
	{
		//Copy a from AU ES data from buffer to user memory
		memcpy(pCapData->pBuffer, pDataBuf, auReadSize);
	}
	else
	{
		AUD_KDRV_ERROR("AUDIO_GetCapturedData : read size error(%d > %d)\n", auReadSize, pCapData->ui32BufSize);
		return RET_ERROR;
	}

	if(pCapData->ui32BufSize != auReadSize)
		AUD_KDRV_DEBUG("GetCapturedData : uiSize = %d, RdSize = %d\n", pCapData->ui32BufSize, auReadSize);

	//Copy a memory copied size
	pCapData->auInfo.ui64Size = (UINT64)auReadSize;

	//Flush a current AUI and AU data
	retVal	= pCapReader->flush_data(auReadSize, pCapReader);
	if(retVal != RET_OK)
	{
		AUD_KDRV_ERROR("AUDIO_GetCapturedData : flush_data(ret = %d)\n", retVal);
		return RET_ERROR;
	}

	//Set a current AU index and size of AU
	pCapData->ui32RemainIndex = (UINT32)(auCount - 1);
	pCapData->ui32UsedSize = usedSize;
	pCapData->ui32FreeSize = freeSize;

	AUD_KDRV_PRINT("AUDIO_GetCapturedData : auReadSize = %d\n", auReadSize);
	return RET_OK;
}

/**
 * Reset Capture device.
 *
 * @see		AUDIO_Restart().
 */
void	KDRV_AUDIO_ResetCapturer(void)
{
	LX_AUD_MOD_T				*pOwnMods;
	UINT32						allocDev;
	UINT32						i = 0, j  = 0;
	UINT32						allocModNum;
   	LX_AUD_ALLOC_FREE_INFO_T * freeDEV;

	for(i = 0; i < DEV_CAP_NUM; i++)
	{
		allocDev = _gCapturerInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		if(allocDev < AUD_DEV_CAP0 || allocDev > AUD_DEV_CAP2)
		{
			AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		}
		_gCapturerInfo[i].bResetting = TRUE;

		AUDIO_StopCapturer(allocDev);
		AUDIO_FlushCapturer(allocDev);

		AUDIO_DisconnectCapturer(allocDev, _gCapturerInfo[i].captureConnect.connectDev);

		AUDIO_DisconnectAllInDev(allocDev);

		//get alloc module info in given device node
		AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

		for(j = 0; j < allocModNum; j++)
		{
			AUDIO_FreeModule (pOwnMods[j].mod,allocDev );
		}

    	freeDEV = &DevInfo.list[allocDev];
    	freeDEV->headOfDev		= NULL;
    	freeDEV->tailOfDev		= NULL;
	}
}

/**
 * Reset Capture parameters.
 *
 * @see		AUDIO_Restart().
 */
void	KDRV_AUDIO_ResetCapturerParam(void)
{
	LX_AUD_CAPTURE_PARAM_T	*pCapInfoParam = NULL;
	UINT32						allocDev;
	UINT32						i = 0;

	for(i = 0; i < DEV_CAP_NUM; i++)
	{
		allocDev = _gCapturerInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		pCapInfoParam = &(_gCapturerInfo[i].capParam);
		AUDIO_SetCaptureParam(allocDev, pCapInfoParam);
		AUDIO_ConnectCapturer(allocDev, _gCapturerInfo[i].captureConnect.connectDev);
	}
}

/**
 * Restart Capture.
 *
 * @see		AUDIO_Restart().
 */
void	KDRV_AUDIO_RestartCapturer(void)
{
	UINT32						allocDev;
	UINT32						i = 0;

	for(i = 0; i < DEV_CAP_NUM; i++)
	{
		allocDev = _gCapturerInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		AUDIO_StartCapturer(allocDev);

		_gCapturerInfo[i].bResetting = FALSE;
	}
}

/** @} */
