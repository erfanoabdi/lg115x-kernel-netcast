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


/** @file	audio_kdrv_encoder.c
 *
 *  main driver implementation for  audio encoder device.
 *  audio encoder device will teach you how to make device driver with new platform.
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
    File Inclusions
----------------------------------------------------------------------------------------*/
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

#include "debug_util.h"
#include "audio_cfg.h"
#include "audio_drv.h"
#include "audio_drv_decoder.h"
#include "audio_drv_encoder.h"
#include "audio_drv_decoder.h"
#include "audio_drv_master.h"
#include "audio_drv_manager.h"
#include "audio_imc_func.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define AUD_ENC_NUM_OF_CHANNEL_OF_SRC_ENC	2		// channel of SRC output & ENC input
#define AUD_ENC_BITS_PER_SAMPLE_OF_SRC_ENC	32		// bits per sample of SRC output & ENC input

#define AUD_ENC_DEFAULT_BITRATE				72000	// Default Bitrate

#define COUNT_MIN_CHECK_START				1
#define COUNT_MAX_CHECK_START				25

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern UINT8 *  allocMod_Str [ADEC_MODULE_MOD_MAX+1] ;
extern UINT8 * modTypeStr[LX_AUD_MOD_TYPE_MAX  +1];

extern UINT8 *  allocDev_Str [AUD_DEV_MAX+1] ;
extern UINT8 * devTypeStr[LX_AUD_DEV_TYPE_MAX+1];

extern AUD_DECODER_INFO_T _gDecoderInfo[DEV_DEC_NUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
AUD_ENCODER_INFO_T	_gEncoderInfo[DEV_ENC_NUM];

UINT32	_gEncoderCheckStartCount[DEV_ENC_NUM] = {0, 0};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static SINT32 AUDIO_StartEncoder(UINT32 allocDev);
static SINT32 AUDIO_StopEncoder(UINT32 allocDev);
static SINT32 AUDIO_FlushEncoder(UINT32 allocDev);
static SINT32 AUDIO_ConnectEncoder (UINT32 allocDev, UINT32 connectDev);
static SINT32 AUDIO_DisconnectEncoder (UINT32 allocDev, UINT32 disconnectDev);
static SINT32 AUDIO_SetEncoderParam(UINT32 allocDev, LX_AUD_ENCODER_PARAM_T *pParam);
static SINT32 AUDIO_CloseEncoder(AUD_DEVICE_T *pAudDev);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * initialize for audio encoder device
 *
 */
static SINT32 _AUDIO_InitEncoderParam(UINT32 allocDev)
{
	ULONG	flags;
	SINT32	encIndex = 0;

	encIndex = GET_ENC_INDEX(allocDev);
	if((encIndex < 0) || (encIndex >= DEV_ENC_NUM))
	{
		AUD_KDRV_ERROR(" encIndex[%d] is not available. \n", encIndex);
		return RET_ERROR;
	}

	memset(&(_gEncoderInfo[encIndex].encoderEvent[0]), 0, sizeof(AUD_EVENT_T)*AUD_EVENT_NUM);
	_gEncoderInfo[encIndex].ui32EventNum = 0;

	memset(&(_gEncoderInfo[encIndex].encoderConnect), 0, sizeof(AUD_CONNECT_T));

	_gEncoderInfo[encIndex].samplingFreq	 = LX_AUD_SAMPLING_FREQ_NONE;
	_gEncoderInfo[encIndex].ui32NumOfChannel = AUD_ENC_NUM_OF_CHANNEL_OF_SRC_ENC;
	_gEncoderInfo[encIndex].ui32BitPerSample = AUD_ENC_BITS_PER_SAMPLE_OF_SRC_ENC;
	_gEncoderInfo[encIndex].ui32Volume 		 = 0xFFFFFFFF;

	_gEncoderInfo[encIndex].ui32AllocDev 	= allocDev;
	_gEncoderInfo[encIndex].bStarted 	 	= FALSE;
	_gEncoderInfo[encIndex].bDecInfoStarted = FALSE;
	_gEncoderInfo[encIndex].bResetting 	 	= FALSE;

	//Initalize a global variable.
	_gEncoderCheckStartCount[encIndex] = 0;

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

	AUD_KDRV_PRINT("%s : encIndex %x.\n", __F__, encIndex);
	return RET_OK;
}

/**
 * Set a SRC format for audio encoder device
 *
 */
static void _AUDIO_SetSRCEncoder(UINT32 allocMod, UINT32 sampleFreq, UINT32 numOfChannel, UINT32 bitPerSample)
{
	SrcCmdSetAllfmt 		srcSetFmt;
	SrcCmdSetOverProtect 	srcSetOverProtect;

	//Set a SRC format for encoder input buffer
	srcSetFmt.InFs		= sampleFreq;
	srcSetFmt.InCh		= numOfChannel;
	srcSetFmt.InFormat	= bitPerSample;
	srcSetFmt.InEndian	= 0;	// 0 is little , 1 is big
	srcSetFmt.InSigned	= 0;	// 0 is signed , 1 is unsigned
	srcSetFmt.OutFs		= LX_AUD_SAMPLING_FREQ_48_KHZ;
	srcSetFmt.OutCh		= AUD_ENC_NUM_OF_CHANNEL_OF_SRC_ENC;
	srcSetFmt.OutFormat	= AUD_ENC_BITS_PER_SAMPLE_OF_SRC_ENC;

	(void)AUDIO_IMC_SendCmdParam(SRC_CMD_SET_ALLFMT, allocMod, sizeof(SrcCmdSetAllfmt), &srcSetFmt);

	//Set a overflow protection mode in SRC module to avoid dsp not running if encoder buffer is overflow case.
	srcSetOverProtect.over_protect = USE_OVERFLOW_PROTECTION;

	(void)AUDIO_IMC_SendCmdParam(SRC_CMD_SET_OVERPROTECT, allocMod, sizeof(SrcCmdSetOverProtect), &srcSetOverProtect);
	return;
}

/**
 * open handler for audio encoder device
 *
 */
SINT32	KDRV_AUDIO_OpenEncoder(struct inode *inode, struct file *filp)
{
	SINT32 	retVal = 0;
	SINT32	encIndex = 0;

	UINT32 	nMajor;
	UINT32 	nMinor;
	UINT32 	devType;

	AUD_DEVICE_T*	my_dev;
	LX_AUD_ALLOC_FREE_INFO_T OpenInfo;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	filp->private_data = kmalloc(sizeof(AUD_DEVICE_T), GFP_KERNEL);
	my_dev = (AUD_DEVICE_T*)filp->private_data;

	/* Set device */
	devType = DEV_TYPE_BASE + nMinor;
	my_dev->devType = devType;

	OpenInfo.devType = devType;

	retVal = AUDIO_AllocDev(&OpenInfo);

	if(retVal != AUD_NO_DEV)
	{
		AUD_KDRV_RM("%s is opened[major:%d minor:%d][Alloc:%s] \n",devTypeStr[devType],nMajor,nMinor,(char *)allocDev_Str[retVal]);

		my_dev->allocDev =  retVal ;

		retVal = RET_OK;
	}
	else
	{
		AUD_KDRV_RM("%s is not available \n",devTypeStr[devType]);
		goto KDRV_OPEN_ERROR;
	}

	encIndex = GET_ENC_INDEX(my_dev->allocDev );
	if((encIndex < 0) || (encIndex >= DEV_ENC_NUM))
	{
		AUD_KDRV_ERROR(" encIndex[%d] is not available. \n", encIndex);
		return RET_ERROR;
	}

	//Initialze a audio encoder module.
	if(_AUDIO_InitEncoderParam(my_dev->allocDev) == RET_ERROR)
		goto KDRV_OPEN_ERROR;

	AUD_KDRV_RM("Open Encoder device file (%d:%d)\n", nMajor, nMinor);

	return retVal;

KDRV_OPEN_ERROR:
	kfree(filp->private_data);
	return RET_ERROR;
}

/**
 * close handler for audio encoder device
 *
 */
SINT32	KDRV_AUDIO_CloseEncoder(struct inode *inode, struct file *filp)
{
	SINT32 retVal = 0;
	UINT32 nMajor;
	UINT32 nMinor;

	AUD_DEVICE_T	*my_dev;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	my_dev = (AUD_DEVICE_T *)filp->private_data;

	if(my_dev == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: private_data is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	kfree(my_dev);

	AUD_KDRV_RMD("Close Encoder device file  (%d:%d)\n", nMajor, nMinor);
	return retVal;
}

/**
 * ioctl handler for audio encoder device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int KDRV_AUDIO_IoctlEncoder(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#else
long KDRV_AUDIO_IoctlEncoder(struct file *filp, unsigned int cmd, unsigned long arg)
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
	if(_IOC_TYPE(cmd) != AUD_ENC_IOC_MAGIC)
	{
		DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if(_IOC_NR(cmd) > AUD_ENC_IOC_MAXNR)
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

	AUD_KDRV_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case AUD_ENC_IO_START:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_ENC_IOW_START] Called\n", __F__, __L__);
			retVal = AUDIO_StartEncoder(allocDev);
		}
		break;

		case AUD_ENC_IO_STOP:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_ENC_IOW_STOP] Called\n", __F__, __L__);
			retVal = AUDIO_StopEncoder(allocDev);
		}
		break;

		case AUD_ENC_IO_FLUSH:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_ENC_IOW_FLUSH] Called\n", __F__, __L__);
			retVal = AUDIO_FlushEncoder(allocDev);
		}
		break;

		case AUD_ENC_IOW_SET_PARAM:
		{
			LX_AUD_ENCODER_PARAM_T	encParam;

			AUD_KDRV_TRACE("AUD_ENC_IOW_SET_PARAM_CODING\n");

			if(copy_from_user(&encParam, (void __user *)arg, sizeof(LX_AUD_ENCODER_PARAM_T)))
				return RET_ERROR;

			retVal = AUDIO_SetEncoderParam(allocDev, &encParam);
		}
		break;

		case AUD_ENC_IOR_GET_KDRV_HANDLE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_ENC_IOW_GET_KDRV_HANDLE] Called\n", __F__, __L__);

			if(copy_to_user((void *)arg, (void *)&(my_dev->allocDev), sizeof(UINT32)))
				return RET_ERROR;
		}
		break;

		case AUD_ENC_IOW_CONNECT:
		{
			UINT32									connectDev;

			AUD_KDRV_TRACE("%s.%d: [AUD_ENC_IOW_CONNECT] Called\n", __F__, __L__);

			if(copy_from_user(&connectDev, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			retVal = AUDIO_ConnectEncoder(allocDev, connectDev);
		}
		break;

		case AUD_ENC_IOW_DISCONNECT:
		{
			UINT32									disconnectDev;

			AUD_KDRV_TRACE("%s.%d: [AUD_ENC_IOW_DISCONNECT] Called\n", __F__, __L__);

			if(copy_from_user(&disconnectDev, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			if(disconnectDev < AUD_DEV_DEC0 || disconnectDev >= AUD_DEV_MAX)
			{
				AUD_KDRV_RM("[%s][%d] Check Arg\n",__FUNCTION__,__LINE__);
				return RET_ERROR;
			}
			else
			{
				retVal = AUDIO_DisconnectEncoder(allocDev, disconnectDev);
			}
		}
		break;

		case AUD_ENC_IO_CLOSE_DEVICE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_ENC_IO_CLOSE_DEVICE] Called\n", __F__, __L__);
			retVal = AUDIO_CloseEncoder(my_dev);
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

/**
 * Register Notification.
 * @param 	pEncInfo		[in] encoder information.
 * @param 	pFuncImcNoti	[in] pointer to callback function.
 * @param 	allocMod		[in] allocated module.
 * @param 	event			[in] event.
 * @return 	void.
 * @see		.
 */
static void _AUDIO_RegisterEncoderNoti(
	AUD_ENCODER_INFO_T* pEncInfo,
	PFN_ImcNoti	pFuncImcNoti,
	UINT32 allocMod,
	UINT32 event,
	IMC_ACTION_REPEAT_TYPE repeatType,
	SINT32 notiLevel)
{
	UINT32							actionID;
	AUD_EVENT_T						*pEncEvent 		= NULL;
	ImcActionParameter 				actionParam;

	if(pEncInfo->ui32EventNum >= AUD_EVENT_NUM)
	{
		AUD_KDRV_ERROR("EncEventNum(%d) is over AUD_EVENT_NUM. \n", pEncInfo->ui32EventNum);
		return;
	}

	actionParam.actionType = IMC_ACTION_GET_CALLBACK;
	actionParam.repeatType = repeatType;
	actionParam.target = ADEC_MODULE_MAN_ARM;
	actionParam.actionParam.notiParam.noti = (PFN_ImcNoti)pFuncImcNoti;
	actionParam.actionParam.notiParam.param = pEncInfo;
	actionParam.actionParam.notiParam.level = notiLevel;
	IMC_RegisterEvent(IMC_GetLocalImc(0), event, allocMod, &actionID, &actionParam);

	//if(repeatType != IMC_ACTION_ONCE)
	{
		pEncEvent = &pEncInfo->encoderEvent[pEncInfo->ui32EventNum];
		pEncEvent->event = event;
		pEncEvent->actionID = actionID;
		pEncEvent->moduleID = allocMod;
		pEncInfo->ui32EventNum++;
	}

	AUD_KDRV_PRINT("%s [0x%x 0x%x, 0x%x] \n", __F__, event, actionID, allocMod);
	return;
}

static SINT32 _AUDIO_EncDecodedInfoCb(void *_param, int _paramLen, void *_cbParam)
{
	UINT32 allocDev 	  = AUD_DEV_ENC0;
	UINT32 allocMod_SRC = ADEC_MODULE_NO_MOD;

	DecEvtESDecInfoParam	*pDecInfoParam = (DecEvtESDecInfoParam *)_param;
	AUD_ENCODER_INFO_T		*pEncoderInfo  = (AUD_ENCODER_INFO_T *)_cbParam;

	allocDev = pEncoderInfo->ui32AllocDev;

	// Print For Debug
	if(_paramLen != sizeof(DecEvtESDecInfoParam))
	{
		AUD_KDRV_ERROR("Enc Info : Param Length Error[Expected:%d][Input:%d]\n", sizeof(DecEvtESDecInfoParam), _paramLen);
		return RET_ERROR;
	}

	//Update a encoder information by decoder information.
	pEncoderInfo->bDecInfoStarted = TRUE;

	// Set SRC config
	allocMod_SRC = AUDIO_GetModule(allocDev, LX_AUD_SRC_DEC);
	if(allocMod_SRC == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n",modTypeStr[LX_AUD_SRC1]);
		return RET_ERROR;
	}

	//Check a previous information if changed now.
	if( (pEncoderInfo->samplingFreq	    != pDecInfoParam->sample_rate)		\
	  ||(pEncoderInfo->ui32NumOfChannel != pDecInfoParam->num_of_channel)	\
	  ||(pEncoderInfo->ui32BitPerSample != pDecInfoParam->bit_per_sample) )
	{
		_AUDIO_SetSRCEncoder(allocMod_SRC,			    pDecInfoParam->sample_rate,
							 pDecInfoParam->num_of_channel, pDecInfoParam->bit_per_sample);
	}

	//Update a encoder information by decoder information.
	pEncoderInfo->samplingFreq 	   = pDecInfoParam->sample_rate;
	pEncoderInfo->ui32NumOfChannel = pDecInfoParam->num_of_channel;
	pEncoderInfo->ui32BitPerSample = pDecInfoParam->bit_per_sample;

	//Starts a encoder by decoder information.
	if(pEncoderInfo->bStarted == FALSE)
		AUDIO_StartEncoder(allocDev);

	AUD_KDRV_DEBUG("Enc Info(%d) : Fs(%d), Ch(%d), Bs(%d)\n", \
					allocDev, pEncoderInfo->samplingFreq, pEncoderInfo->ui32NumOfChannel, pEncoderInfo->ui32BitPerSample);

	return RET_OK;
}

/**
 * Start Encoder.
 *
 * @param 	allocDev		[in] a allocated encoder device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlEncoder(), KDRV_AUDIO_RestartEncoder()
 */
static SINT32 AUDIO_StartEncoder(UINT32 allocDev)
{
	SINT32	retVal = RET_OK;
	SINT32	encIndex = 0;
	UINT32	connectDev;
	UINT32	allocModNum;
	UINT32	i = 0;

	LX_AUD_MOD_T *pOwnMods;
	LX_AUD_DEV_TYPE_T 	devType;
	LX_AUD_ALLOC_MOD_T	moduleId = ADEC_MODULE_NOT_DEF;

	/* Get a Encoder Index */
	encIndex = GET_ENC_INDEX(allocDev);
	if((encIndex < 0) || (encIndex >= DEV_ENC_NUM))
	{
		AUD_KDRV_ERROR(" encIndex[%d] is not available. \n", encIndex);
		return RET_ERROR;
	}

	/* Check a decoder information for encoder module. */
	if(_gEncoderInfo[encIndex].bDecInfoStarted == FALSE)
	{
		/* Get a connected audio decoder information. */
		devType = _gEncoderInfo[encIndex].encoderConnect.devType;
		if(devType != LX_AUD_DEV_DEC)
		{
			AUD_KDRV_ERROR("%s.%d: Audio devType is not decoder.\n", __FUNCTION__, __LINE__);
			return RET_ERROR;
		}

		connectDev = _gEncoderInfo[encIndex].encoderConnect.connectDev;
		moduleId = AUDIO_HasThisModuleType(connectDev, LX_AUD_DEC);
		if(moduleId == ADEC_MODULE_NO_MOD)
		{
			AUD_KDRV_ERROR("%s.%d: audio module is Unknown\n", __FUNCTION__, __LINE__);
			return RET_ERROR;
		}

		/* Set a decoder notification to get a decoder information. */
		retVal = AUDIO_IMC_SendCmd(ADEC_CMD_GET_DECINFO, moduleId);

		AUD_KDRV_PRINT("Send GET_DECINFO CMD [%d] \n", moduleId);
		return retVal;
	}

	/* Get a allocated module in encoder module. */
	AUDIO_GetAllocInfo(allocDev, &allocModNum, &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if(pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX)
		{
			//Send a IMC command - INIT & START
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_INIT, pOwnMods[i].mod);		// need to init SRC before start SRC by gunho.song
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_START, pOwnMods[i].mod);
			AUD_KDRV_RM("Send START CMD [%s] \n", allocMod_Str[pOwnMods[i].mod]);
		}
	}

	_gEncoderInfo[encIndex].bStarted = TRUE;

	return retVal;
}

/**
 * Stop Encoder.
 *
 * @param 	allocDev		[in] a allocated encoder device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlEncoder(), KDRV_AUDIO_ResetEncoder()
 */
static SINT32 AUDIO_StopEncoder(UINT32 allocDev)
{
	UINT32			allocModNum;
	LX_AUD_MOD_T	*pOwnMods;
	UINT32			i;
	SINT32			retVal = RET_OK;

	if( allocDev < AUD_DEV_ENC0 || allocDev > AUD_DEV_ENC1)
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
			retVal = AUDIO_IMC_SendCmd(ADEC_CMD_STOP, pOwnMods[i].mod);		// need to init SRC before start SRC by gunho.song
			AUD_KDRV_RM("Send STOP CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
		}
	}

	return retVal;
}

/**
 * Flush Encoder.
 *
 * @param 	allocDev		[in] a allocated encoder device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlEncoder(), KDRV_AUDIO_ResetEncoder()
 */
static SINT32 AUDIO_FlushEncoder(UINT32 allocDev)
{
	UINT32				allocModNum;
	LX_AUD_MOD_T		*pOwnMods;
	UINT32				i;
	ImcCmdFlushParam	flushParam;
	SINT32				retVal = RET_OK;

	if(allocDev < AUD_DEV_ENC0 || allocDev > AUD_DEV_ENC1)
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
			retVal = AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, pOwnMods[i].mod, sizeof(ImcCmdFlushParam), &flushParam);
			AUD_KDRV_RM("Send FLUSH CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
		}
	}

	return retVal;
}

/**
 * Connect other device to Encoder.
 *
 * @param 	allocDev		[in] a allocated encoder device.
 * @param 	connectDev		[in] Device to connect.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlEncoder(), KDRV_AUDIO_ResetEncoderParam()
*/
static SINT32 AUDIO_ConnectEncoder(UINT32 allocDev, UINT32 connectDev)
{
	SINT32	encIndex = 0;

	AUD_ENCODER_INFO_T			*pEncoderInfo = NULL;
	LX_AUD_ALLOC_FREE_INFO_T	*encDevInfo, *connectDevInfo;

	UINT32 	left, right;

	LX_AUD_ALLOC_MOD_T 	allocModule_DEC = ADEC_MODULE_NO_MOD;

	/* Get a Encoder Index */
	encIndex = GET_ENC_INDEX(allocDev);
	if((encIndex < 0) || (encIndex >= DEV_ENC_NUM))
	{
		AUD_KDRV_ERROR("encIndex[%d] is not available. \n", encIndex);
		return RET_ERROR;
	}

	pEncoderInfo = &_gEncoderInfo[encIndex];

	/* Get a allocated information */
	encDevInfo 	   = AUDIO_GetAllocDevInfo(allocDev);
	connectDevInfo = AUDIO_GetAllocDevInfo(connectDev);

	if(connectDevInfo == NULL || encDevInfo == NULL)
	{
		AUD_KDRV_DEBUG("Check connectDevInfo[%p] encDevInfo[%p] \n",connectDevInfo,encDevInfo);
		return RET_ERROR;
	}

	if(connectDevInfo->devType == LX_AUD_DEV_DEC)
	{
		if (connectDevInfo->headOfDev == NULL ||  encDevInfo->headOfDev == NULL	\
		 || connectDevInfo->tailOfDev == NULL ||  encDevInfo->tailOfDev == NULL)
		{
			AUD_KDRV_ERROR("========== CAUTION ============ \n");
			AUD_KDRV_ERROR("ENC head[%p] tail[%p]  CON [%p] [%p] \n", encDevInfo->headOfDev, encDevInfo->tailOfDev,connectDevInfo->headOfDev, connectDevInfo->tailOfDev );
			return RET_ERROR;
		}

		allocModule_DEC = AUDIO_HasThisModuleType(connectDev, LX_AUD_DEC);
		if(allocModule_DEC == ADEC_MODULE_NO_MOD)
		{
			AUD_KDRV_RMD("AUDIO_ConnectEncoder : No Valid Connection Trial\n");
			return RET_ERROR;
		}

		/* Set a left and right module to connect */
		left  =	allocModule_DEC;
		right =	((LX_AUD_ALLOC_FREE_INFO_T *)(encDevInfo->headOfDev))->allocMod;

		AUDIO_ConnectTo(left, right, NO_FORCE, NO_FORCE);
		AUD_KDRV_RMD("AUDIO_ConnectEncoder : A%d, C%d\n", allocDev, connectDev);

		_AUDIO_RegisterEncoderNoti(pEncoderInfo, (PFN_ImcNoti)_AUDIO_EncDecodedInfoCb, allocModule_DEC, DEC_EVT_ES_DEC_INFO, IMC_ACTION_REPEAT, 1);
	}
	else
	{
		AUD_KDRV_RMD("devType is not LX_AUD_DEV_DEC\n");
	}

	if(pEncoderInfo->bResetting == FALSE)
	{
		pEncoderInfo->encoderConnect.devType	= connectDevInfo->devType;
		pEncoderInfo->encoderConnect.connectDev = connectDev;
	}

	AUD_KDRV_PRINT("ConnectEncoder : Fs(%d), Ch(%d), Bs(%d)\n", \
					pEncoderInfo->samplingFreq, pEncoderInfo->ui32NumOfChannel, pEncoderInfo->ui32BitPerSample);
	return RET_OK;
}

/**
 * Disconnect other device to Encoder.
 * @see
*/
static SINT32 AUDIO_DisconnectEncoder (UINT32 allocDev, UINT32 disconnectDev)
{
	UINT32 left, right;

	LX_AUD_ALLOC_MOD_T 	allocModule_DEC = ADEC_MODULE_NO_MOD;

	LX_AUD_ALLOC_FREE_INFO_T *encDevInfo, *disconnectDevInfo;

	encDevInfo = AUDIO_GetAllocDevInfo(allocDev);
	disconnectDevInfo = AUDIO_GetAllocDevInfo(disconnectDev);

	if(disconnectDevInfo == NULL || encDevInfo == NULL)
	{
		AUD_KDRV_DEBUG(" Check disconnectDevInfo[%p] encDevInfo[%p] \n",disconnectDevInfo,encDevInfo);
		return RET_ERROR;
	}

	if(disconnectDevInfo->devType ==LX_AUD_DEV_DEC)
	{
		if(disconnectDevInfo->headOfDev == NULL || encDevInfo->headOfDev == NULL	\
		 ||disconnectDevInfo->tailOfDev == NULL || encDevInfo->tailOfDev == NULL)
		{
			AUD_KDRV_ERROR("========== CAUTION ============ \n");
			AUD_KDRV_ERROR("ENC head[%p] tail[%p]  DISCON [%p] [%p] \n",encDevInfo->headOfDev, encDevInfo->tailOfDev,disconnectDevInfo->headOfDev, disconnectDevInfo->tailOfDev );
			return RET_ERROR;
		}

		/* Find a BYPASS module in connected decoder module. */
		allocModule_DEC = AUDIO_HasThisModuleType(disconnectDev, LX_AUD_DEC);
		if(allocModule_DEC != ADEC_MODULE_NO_MOD)
		{
			left =	allocModule_DEC;
			right =	((LX_AUD_ALLOC_FREE_INFO_T *)(encDevInfo->headOfDev))->allocMod;

			AUDIO_DisconnectTo (left, right, NO_FORCE, NO_FORCE);
			AUD_KDRV_RMD("AUDIO_DisconnectEncoder : A%d, D%d\n", allocDev, disconnectDev);
		}
	}
	else
	{
		AUD_KDRV_RMD("No Valid Disconnection Trial\n");
		return RET_ERROR;
	}

	return RET_OK;
}

static SINT32 AUDIO_SetEncoderParam(UINT32 allocDev, LX_AUD_ENCODER_PARAM_T *pParam)
{
	SINT32	encIndex = 0;

	ADEC_MODULE_ID		managerModule	= ADEC_MODULE_NOT_DEF;
	LX_AUD_ALLOC_MOD_T 	allocModule_ENC = ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T 	allocModule_SRC = ADEC_MODULE_NO_MOD;

	CmCmdCreateModule	createModule;

	if(pParam == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: pParam is NULL.\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	/* Get a Encoder Index */
	encIndex = GET_ENC_INDEX(allocDev);
	if((encIndex < 0) || (encIndex >= DEV_ENC_NUM))
	{
		AUD_KDRV_ERROR(" encIndex[%d] is not available.\n", encIndex);
		return RET_ERROR;
	}

	/* Allocate a Encoder Module */
	allocModule_ENC = AUDIO_AllocModule(allocDev, LX_AUD_ENC, 0);

	/* Get a Manager Module for Encoder */
	managerModule = _AUDIO_GetManagerModule(allocModule_ENC);
	if(managerModule != ADEC_MODULE_NOT_DEF)
	{
		createModule.module_id = allocModule_ENC;
		createModule.module_param.codec_param.media_type = pParam->codecType;

		AUDIO_IMC_SendCmdParam(CM_CMD_CREATE_MODULE, managerModule, sizeof(CmCmdCreateModule), &createModule);

		AUD_KDRV_PRINT("%s.%d: CM_CMD_CREATE_MODULE, ENC : 0x%x : %d\n", __FUNCTION__, __LINE__, createModule.module_id, createModule.module_param.codec_param.media_type);
	}

	//Copy a encoder parameters : bitrate only
	memcpy(&(_gEncoderInfo[encIndex].encoderParam), pParam, sizeof(LX_AUD_ENCODER_PARAM_T));

	allocModule_ENC = AUDIO_HasThisModuleType(allocDev, LX_AUD_ENC);

	//Set Encoder and SRC Params
	if(pParam->codecType == LX_AUD_CODEC_AAC_ENC)
	{
		AacEncCmdSetParam 	aacEncSetParam;
		SrcCmdSetGain		srcSetGain;

		//From SRC parameters for encoder
		aacEncSetParam.i_samp_freq = LX_AUD_SAMPLING_FREQ_48_KHZ;
		aacEncSetParam.i_pcm_wd_sz = AUD_ENC_BITS_PER_SAMPLE_OF_SRC_ENC;
		aacEncSetParam.i_num_chan  = AUD_ENC_NUM_OF_CHANNEL_OF_SRC_ENC;

		// Input Output Bitrate
		//aacEncSetParam.i_bitrate   = _gEncoderInfo[encIndex].encoderParam.bitRate;
		aacEncSetParam.i_bitrate   = AUD_ENC_DEFAULT_BITRATE;

		AUDIO_IMC_SendCmdParam(AACENC_CMD_SET_PARAM, allocModule_ENC, sizeof(AacEncCmdSetParam), &aacEncSetParam);

		AUD_KDRV_PRINT("[%s] mod(%x), Fs(%d) Bs(%d) Ch(%d) Br(%d)\n", __F__, allocModule_ENC, aacEncSetParam.i_samp_freq,	\
						aacEncSetParam.i_pcm_wd_sz, aacEncSetParam.i_num_chan, aacEncSetParam.i_bitrate);

		/* Allocate a SRC Module for Encoder */
		allocModule_SRC = AUDIO_AllocModule(allocDev, LX_AUD_SRC_DEC, 0);
		if(allocModule_SRC == ADEC_MODULE_NO_MOD )
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n", modTypeStr[LX_AUD_SRC_DEC]);
			return RET_ERROR;
		}

		/* Set a default SRC format for encoder */
		_AUDIO_SetSRCEncoder(allocModule_SRC, LX_AUD_SAMPLING_FREQ_48_KHZ,	\
							 AUD_ENC_NUM_OF_CHANNEL_OF_SRC_ENC, AUD_ENC_BITS_PER_SAMPLE_OF_SRC_ENC);

		/* Set a SRC_DEC gain. */
		srcSetGain.GainEnable	= 1;
		srcSetGain.Gain			= pParam->ui32Volume;
		AUDIO_IMC_SendCmdParam(SRC_CMD_SET_GAIN, allocModule_SRC, sizeof(SrcCmdSetGain), &srcSetGain);

		_gEncoderInfo[encIndex].ui32Volume = pParam->ui32Volume;

		/* Allocate a Encoder SRC to Encoder Module */
		if(AUDIO_IsNotConnectedYet(allocModule_SRC, allocModule_ENC))
		{
			(void)AUDIO_ConnectTo(allocModule_SRC, allocModule_ENC, NO_FORCE, NO_FORCE);
		}

		//Send a IMC command - INIT & START
		AUDIO_IMC_SendCmd(ADEC_CMD_INIT, allocModule_SRC);
		AUDIO_IMC_SendCmd(ADEC_CMD_START, allocModule_SRC);
		AUD_KDRV_PRINT("Send START CMD [%s] \n",allocMod_Str[allocModule_SRC]);

	}
	else
	{
		AUD_KDRV_ERROR("[%s] This codec(%d) is not supported.\n", __F__, pParam->codecType);
		return RET_ERROR;
	}

	AUD_KDRV_DEBUG("AUDIO_SetEncoderParam : bitRate[%d], volume[0x%X]", pParam->bitRate, pParam->ui32Volume);
	return RET_OK;
}

static SINT32 AUDIO_CloseEncoder(AUD_DEVICE_T *pAudDev)
{
	UINT32 devType;
	UINT32 i = 0;

	SINT32 retVal = 0;
	SINT32 encIndex = 0;

	LX_AUD_ALLOC_FREE_INFO_T CloseInfo;
	LX_AUD_ALLOC_DEV_T allocDev;
	LX_AUD_ALLOC_MOD_T allocModule_SRC = ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_MOD_T allocModule_ENC = ADEC_MODULE_NO_MOD;

	AUD_EVENT_T			*pEncEvent = NULL;

	SrcCmdSetGain		srcSetGain;
	CmCmdDisconnect		DecDisconnectParam;
	LX_AUD_ALLOC_FREE_INFO_T * MOD;
	UINT64 SRC_DEC_InputPort = 0;

	/* Set device */
	devType = pAudDev->devType;
	allocDev = pAudDev->allocDev;

	/* Get a Encoder Index */
	encIndex = GET_ENC_INDEX(allocDev);
	if((encIndex < 0) || (encIndex >= DEV_ENC_NUM))
	{
		AUD_KDRV_ERROR("encIndex[%d] is not available. \n", encIndex);
		return RET_ERROR;
	}

	retVal = AUDIO_DisconnectAllInDev(allocDev);
	if(retVal == RET_ERROR)
	{
		AUD_KDRV_ERROR("Fail to disconnect in dev[%s] \n", allocDev_Str[allocDev]);
	}

	allocModule_SRC = AUDIO_HasThisModuleType(allocDev, LX_AUD_SRC_DEC);
	if(allocModule_SRC != ADEC_MODULE_NO_MOD)
	{
		srcSetGain.GainEnable = 0;
		srcSetGain.Gain		  = 0xFFFFFFFF;

		AUDIO_IMC_SendCmdParam(SRC_CMD_SET_GAIN, allocModule_SRC, sizeof(SrcCmdSetGain), &srcSetGain);

		_gEncoderInfo[encIndex].ui32Volume = 0xFFFFFFFF;

		/* preparation for missing of disconnection between decoder and encoder */
		/* do disconnection of input port of SRC_DEC module in forcing mananer */

		DecDisconnectParam.module	= allocModule_SRC;
		DecDisconnectParam.port		= MOD_IN_PORT(SRC_DEC_InputPort);

		if (AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, ADEC_MODULE_MAN_DSP0, sizeof(CmCmdDisconnect), &DecDisconnectParam) < 0)
		{
			AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, SEC_DEC INPUT port ) Error\n", __FUNCTION__, __LINE__);
		}

		MOD	= AUDIO_GetAllocModInfo(allocModule_SRC) ;
		MOD->inPool = MOD->inPool &( ~(SRC_DEC_InputPort+1));
	}

	allocModule_ENC = AUDIO_HasThisModuleType(allocDev, LX_AUD_ENC);
	if(allocModule_ENC != ADEC_MODULE_NO_MOD)
	{
		AUDIO_Destory(allocModule_ENC);
	}
	else
	{
		AUD_KDRV_RMD("No encoder module  to destory\n");
	}

	CloseInfo.devType = devType;
	CloseInfo.allocDev = allocDev;
	retVal = AUDIO_FreeDev(&CloseInfo);

	if(retVal == AUD_NO_DEV )
	{
		AUD_KDRV_RMD(" All %s is already freed \n", devTypeStr[devType]);
	}

	for(i = 0; i < _gEncoderInfo[encIndex].ui32EventNum; i++)
	{
		pEncEvent = &_gEncoderInfo[encIndex].encoderEvent[i];

		IMC_CancelEvent(IMC_GetLocalImc(0), pEncEvent->event, pEncEvent->moduleID, pEncEvent->actionID);
		AUD_KDRV_PRINT("%s: IMC_CancelEvent(%d) is (%d, %d, %d)!!!\n", __FUNCTION__, encIndex, pEncEvent->event,	\
						pEncEvent->moduleID, pEncEvent->actionID);
	}

	//Clear a capturer resource.
	_gEncoderInfo[encIndex].ui32EventNum = 0;
	_gEncoderInfo[encIndex].ui32AllocDev = 0;

	AUD_KDRV_PRINT("%s : Close Device %d.\n", __F__, allocDev);
	return RET_OK;
}

void	KDRV_AUDIO_ResetEncoder(void)
{
	LX_AUD_MOD_T				*pOwnMods;
	UINT32						allocDev;
	UINT32						i = 0, j  = 0;
	UINT32						allocModNum;
   	LX_AUD_ALLOC_FREE_INFO_T * freeDEV;
	for(i = 0; i < DEV_ENC_NUM; i++)
	{
		allocDev = _gEncoderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		if( allocDev < AUD_DEV_ENC0 || allocDev > AUD_DEV_ENC1)
		{
			AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		}
		_gEncoderInfo[i].bResetting = TRUE;

		AUDIO_StopEncoder(allocDev);
		AUDIO_FlushEncoder(allocDev);

		AUDIO_DisconnectEncoder(allocDev, _gEncoderInfo[i].encoderConnect.connectDev);

		AUDIO_DisconnectAllInDev(allocDev);

		//get alloc module info in given device node
		AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

		for(j = 0; j < allocModNum; j++)
		{
 			AUDIO_FreeModule (pOwnMods[j].mod, allocDev);
 		}
    	freeDEV = &DevInfo.list[allocDev];
    	freeDEV->headOfDev		= NULL;
    	freeDEV->tailOfDev		= NULL;
	}
}

void	KDRV_AUDIO_ResetEncoderParam(void)
{
	LX_AUD_ENCODER_PARAM_T		*pEncInfoParam = NULL;
	UINT32						allocDev;
	UINT32						i = 0;

	for(i = 0; i < DEV_ENC_NUM; i++)
	{
		allocDev = _gEncoderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		pEncInfoParam = &(_gEncoderInfo[i].encoderParam);
		AUDIO_SetEncoderParam(allocDev, pEncInfoParam);
		AUDIO_ConnectEncoder(allocDev, _gEncoderInfo[i].encoderConnect.connectDev);
	}
}

void	KDRV_AUDIO_RestartEncoder(void)
{
	UINT32						allocDev;
	UINT32						i = 0;

	for(i = 0; i < DEV_ENC_NUM; i++)
	{
		allocDev = _gEncoderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		AUDIO_StartEncoder(allocDev);

		_gEncoderInfo[i].bResetting = FALSE;
	}
}

/**
 * Redemand Decoded Notification.
 * @see
*/
void	KDRV_AUDIO_RedemandDecodedNofiEncoder(void)
{
	UINT32						tempCheckStartCount = 0;
	UINT32						allocDev;
	UINT32						i = 0;
	UINT32						connectDev;
	LX_AUD_ALLOC_MOD_T			moduleId = ADEC_MODULE_NOT_DEF;
	LX_AUD_ALLOC_MOD_T			tempModuleId = ADEC_MODULE_NOT_DEF;

	for(i = 0; i < DEV_ENC_NUM; i++)
	{
		allocDev = _gEncoderInfo[i].ui32AllocDev;
		if(allocDev == 0)
			continue;

		/* Set a decoder notification to get a decoder information. */
		if(_gEncoderInfo[i].bStarted == FALSE)
		{
			if(_gEncoderInfo[i].encoderConnect.devType == LX_AUD_DEV_DEC)
			{
				connectDev = _gEncoderInfo[i].encoderConnect.connectDev;
				moduleId   = AUDIO_HasThisModuleType(connectDev, LX_AUD_DEC);

				if(moduleId == ADEC_MODULE_NO_MOD)
				{
					AUD_KDRV_DEBUG("%s.%d: audio module is Unknown\n", __FUNCTION__, __LINE__);
					continue;
				}

				tempCheckStartCount = _gEncoderCheckStartCount[i]++;

				if((tempCheckStartCount > COUNT_MIN_CHECK_START) && (tempCheckStartCount <= COUNT_MAX_CHECK_START))
				{
					if(moduleId != tempModuleId)
					{
						(void)AUDIO_IMC_SendCmd(ADEC_CMD_GET_DECINFO, moduleId);
						tempModuleId = moduleId;

						AUD_KDRV_DEBUG("%s.%d: ADEC_CMD_GET_DECINFO.\n", __FUNCTION__, __LINE__);
					}
				}
			}
		}
	}

	return;
}



