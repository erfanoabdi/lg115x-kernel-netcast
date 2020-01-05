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


/** @file	audio_kdrv_decoder.c
 *
 *  main driver implementation for  audio decoder device.
 *  audio decoder device will teach you how to make device driver with new platform.
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

#include "audio_imc_func.h"
#include "audio_buffer.h"
#include "common/adec_media_type.h"

#include "audio_drv_decoder.h"
#include "audio_drv_master.h"
#include "audio_drv_manager.h"
#include "audio_drv_renderer.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* define WMA and WMAPro codec parameters */
/****************************************************************
*	Format Tag
*****************************************************************
*	0x0160: WMA version1
*	0x0161:	WMA v7, v8, v9 (WMA version2)
*	0x0162:	WMA Professional (WMA version3)
*	0x0163:	WMA Lossless
****************************************************************/

/****************************************************************
*	DSI (Decoder Specific Info) of WMA
*****************************************************************
*	WMA1
*	size: 4 bytes
*	Samples Per Block(2bytes) + Encode Options(2bytes)
*****************************************************************
*	WMA2
*	size: 10 bytes
*	Samples Per Block(4bytes) + Encode Options(2bytes) + Super Block Align(4bytes)
*****************************************************************
*	WMA3 - WMA Pro(v10, Lossless)
*	size: 18 bytes
*	Samples Per Block(2bytes) + Channel Mask(4bytes) + Advanced Encode Options2(8bytes) + Encode Option(2bytes) + Advanced Encode Option(2bytes)
*	// Valid Bits Per Sample(2bytes) + Channel Mask(4bytes) + reserved1(4bytes) + reserved2(4bytes) + Encode Options(2bytes) + reserved3(2bytes)
****************************************************************/
#define LENGTH_OF_DSI_FOR_WMA1			4
#define LENGTH_OF_DSI_FOR_WMA2			10
#define LENGTH_OF_DSI_FOR_WMA3			18

#define WMA1_FORMAT_TAG					0x160
#define WMA2_FORMAT_TAG					0x161
#define WMAPRO_FORMAT_TAG				0x162
#define WMALOSSLESS_FORMAT_TAG			0x163

#define ADEC_READ16_LE(buf)				(buf)[0] | ((UINT16)(buf)[1]<<8)
#define ADEC_READ24_LE(buf)				(buf)[0] | ((UINT32)(buf)[1]<<8) | ((UINT32)(buf)[2]<<16)
#define ADEC_READ32_LE(buf)				(buf)[0] | ((UINT32)(buf)[1]<<8) | ((UINT32)(buf)[2]<<16) | ((UINT32)(buf)[3]<<24)
#define ADEC_READ64_LE(buf)				ADEC_READ32_LE((buf)) | ((UINT64)ADEC_READ32_LE(&(buf)[4]))<<32

#define ADEC_READ16_BE(buf)				((UINT16)(buf)[0]<<8) | (buf)[1]
#define ADEC_READ24_BE(buf)				((UINT32)(buf)[0]<<16) | ((UINT32)(buf)[1]<<8) | (buf)[2]
#define ADEC_READ32_BE(buf)				((UINT32)(buf)[0]<<24) | ((UINT32)(buf)[1]<<16) | ((UINT32)(buf)[2]<<8) | (buf)[3]
#define ADEC_READ64_BE(buf)				(((UINT64)ADEC_READ32_BE((buf)))<<32) | ADEC_READ32_BE(&(buf)[4])

/* define RA8 codec parameters */
#define MIN_LENGTH_OF_DSI_FOR_RA8		8
#define MIN_LENGTH_OF_DSI_FOR_RA8_V13	16
#define RA8_MAJOR_V1					1
#define RA8_MINOR_V3					3

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

AUD_DECODER_INFO_T		_gDecoderInfo[DEV_DEC_NUM];

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern UINT8	*allocMod_Str[ADEC_MODULE_MOD_MAX+1];
extern UINT8	*modTypeStr[LX_AUD_MOD_TYPE_MAX+1];
extern UINT8	*allocDev_Str[AUD_DEV_MAX+1];
extern UINT8	*devTypeStr[LX_AUD_DEV_TYPE_MAX+1];

extern LX_AUD_BUF_MEM_CFG_S_T stCPB[];

extern LX_AUD_CLOCK_SRC_T	g_setClockSrc;	// DTO Rate
extern UINT32 g_DuringReset;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static SINT32 AUDIO_InitDecoder(UINT32 allocDev);
static SINT32 AUDIO_StartDecoder(UINT32 allocDev);
static SINT32 AUDIO_StopDecoder(UINT32 allocDev);
static SINT32 AUDIO_FlushDecoder(UINT32 allocDev);
static SINT32 AUDIO_SetDecoderOutMode(UINT32 allocDev, LX_AUD_DECODER_OUT_MODE_T outMode);
static SINT32 AUDIO_SetDecoderParam(UINT32 allocDev, LX_AUD_DECODER_PARAM_T *pDecParam);
static SINT32 AUDIO_FeedDec(UINT32 allocDev, LX_AUD_DECODER_FEED_T *pDecFeed);
static SINT32 AUDIO_GetDecodedInfo(UINT32 allocDev, LX_AUD_DECODED_INFO_T *pDecodedInfo);
static SINT32 AUDIO_IsDecodable(UINT32 allocDev, UINT32 *pIsDecodable);
static SINT32 AUDIO_CloseDecoder(AUD_DEVICE_T* audDev);
static SINT32 AUDIO_SetDecoderMode(UINT32 allocDev, LX_AUD_DECODER_MODE_T *pDecMode);
static SINT32 AUDIO_GetDecodedStatus(UINT32 allocDev, LX_AUD_DECODED_STATUS_T *pDecodedStatus);
static SINT32 AUDIO_SetDecoderCertiParam(UINT32 allocDev, UINT32 decCertiParam);
static void _AUDIO_RegisterDecoderEvent(UINT32 allocDev);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * open handler for audio decoder device
 *
 */
SINT32	KDRV_AUDIO_OpenDecoder(struct inode *inode, struct file *filp)
{
	ULONG	flags;

	int							retVal = RET_OK;
	unsigned int				nMajor;
	unsigned int				nMinor;
	unsigned int				devType;
	AUD_DEVICE_T*				my_dev;
	LX_AUD_ALLOC_FREE_INFO_T	OpenInfo;
	LX_AUD_ALLOC_DEV_T			allocDev =AUD_NO_DEV;
	SINT32						decIndex = 0;
	BOOLEAN						bBufferRepeat;		//The status of buffer repeat is set previously.

	/* for debug */
	nMajor = imajor(inode);
	nMinor = iminor(inode);

	filp->private_data = kmalloc(sizeof(AUD_DEVICE_T), GFP_KERNEL);
	my_dev = (AUD_DEVICE_T*)filp->private_data;

	/* Set device */
	devType = DEV_TYPE_BASE + nMinor;
	my_dev->devType = devType;

	OpenInfo.devType = devType;

	allocDev = AUDIO_AllocDev(&OpenInfo);
	if(allocDev == AUD_NO_DEV )
	{
		AUD_KDRV_RM("%s is not available \n",devTypeStr[devType]);
		goto KDRV_OPEN_ERROR;
	}

	AUD_KDRV_RM("%s is opened[major:%d minor:%d][Alloc:%s] \n",devTypeStr[devType],nMajor,nMinor,(char *)allocDev_Str[allocDev]);

	my_dev->allocDev = allocDev;
	filp->private_data = my_dev;

	decIndex = GET_DEC_INDEX(allocDev);
	if ((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		goto KDRV_OPEN_ERROR;
	}

	//Copy a previous buffer repeat variable
	bBufferRepeat = _gDecoderInfo[decIndex].bBufferRepeat;

	//Clears a all decoder information.
	memset(&_gDecoderInfo[decIndex], 0, sizeof(AUD_DECODER_INFO_T));

	_gDecoderInfo[decIndex].ui32AllocDev 	= allocDev;
	_gDecoderInfo[decIndex].bClosed 		= FALSE;
	_gDecoderInfo[decIndex].bResetting 		= FALSE;
	_gDecoderInfo[decIndex].ui32EventNum 	= 0;

	_gDecoderInfo[decIndex].bBufferRepeat 	  = bBufferRepeat;
	_gDecoderInfo[decIndex].decMode.drc 	  = LX_AUD_DECODER_DRC_LINE;
	_gDecoderInfo[decIndex].decMode.downmix   = LX_AUD_DECODER_DOWNMIX_LORO;
	_gDecoderInfo[decIndex].decMode.aacBypass = LX_AUD_DECODER_AAC_BYPASS_OFF;
	_gDecoderInfo[decIndex].decMode.tpTimerInterval 	 = 0x2000;
	_gDecoderInfo[decIndex].decodedInfo.samplingFreq  	 = LX_AUD_SAMPLING_FREQ_NONE;
	_gDecoderInfo[decIndex].decodedInfo.ui32BitPerSample = 0;
	_gDecoderInfo[decIndex].decodedInfo.esInfo.adecFormat= LX_AUD_CODEC_UNKNOWN;
	_gDecoderInfo[decIndex].decodedInfo.esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
	_gDecoderInfo[decIndex].bIsDualDec	= FALSE;

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

	AUD_KDRV_RM("Open Decoder device file (%d:%d)\n", nMajor, nMinor);
	return retVal;

KDRV_OPEN_ERROR:
	kfree(filp->private_data);
	return RET_ERROR;
}

/**
 * close handler for audio decoder device
 *
 */
SINT32	KDRV_AUDIO_CloseDecoder(struct inode *inode, struct file *filp)
{
	SINT32				retVal = 0;
	UINT32				nMajor;
	UINT32				nMinor;
	AUD_DEVICE_T*		audDev = NULL;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	audDev = (AUD_DEVICE_T*)filp->private_data;

	if (audDev == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: private_data is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	kfree(audDev);

	AUD_KDRV_RMD("Close Decoder device file  (%d:%d)\n", nMajor, nMinor);
	return retVal;
}


/**
 * ioctl handler for audio decoder device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static SINT32 KDRV_AUDIO_IoctlDecoder (struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#else
long KDRV_AUDIO_IoctlDecoder(struct file *filp, unsigned int cmd, unsigned long arg)
#endif
{
	SINT32				retVal = 0;
	SINT32				err = 0;
	AUD_DEVICE_T		*my_dev;
	UINT32				allocDev;

	my_dev = (AUD_DEVICE_T*)filp->private_data;
	if(my_dev == NULL)
		return RET_ERROR;

	allocDev = my_dev->allocDev;

	/*
	* check if IOCTL command is valid or not.
	* - if magic value doesn't match, return error (-ENOTTY)
	* - if command is out of range, return error (-ENOTTY)
	*
	* note) -ENOTTY means "Inappropriate ioctl for device.
	*/
	if (_IOC_TYPE(cmd) != AUD_DEC_IOC_MAGIC)
	{
		DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > AUD_DEC_IOC_MAXNR)
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
		case AUD_DEC_IO_START:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_START] Called\n", __F__, __L__);
			retVal = AUDIO_StartDecoder(allocDev);
		}
		break;

		case AUD_DEC_IO_STOP:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_STOP] Called\n", __F__, __L__);
			retVal = AUDIO_StopDecoder(allocDev);
		}
		break;

		case AUD_DEC_IO_FLUSH:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_FLUSH] Called\n", __F__, __L__);
			retVal = AUDIO_FlushDecoder(allocDev);
		}
		break;

		case AUD_DEC_IOW_SET_OUT_MODE:
		{
			LX_AUD_DECODER_OUT_MODE_T	decOutMode;

			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_SET_OUT_MODE] Called\n", __F__, __L__);

			if ( copy_from_user(&decOutMode, (void __user *)arg, sizeof(LX_AUD_DECODER_OUT_MODE_T)) )
			{
				AUD_KDRV_ERROR("%s.%d: [AUD_DEC_IOW_SET_OUT_MODE] copy_from_user() Err\n", __F__, __L__);
				return RET_ERROR;
			}

			retVal = AUDIO_SetDecoderOutMode(allocDev, decOutMode);
		}
		break;

		case AUD_DEC_IOW_FEED:
		{
			LX_AUD_DECODER_FEED_T		decFeedData;

			if ( copy_from_user(&decFeedData, (void __user *)arg, sizeof(LX_AUD_DECODER_FEED_T)) )
			{
				AUD_KDRV_ERROR("%s.%d: [AUD_DEC_IOW_FEED] copy_from_user() Err\n", __F__, __L__);
				return RET_ERROR;
			}

			retVal = AUDIO_FeedDec(allocDev, &decFeedData);
			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_FEED] bufSize=%u, bufStatus=%d, TS=%llu\n", __F__, __L__, decFeedData.ui32BufferSize, decFeedData.statusBuffer, decFeedData.ui64TimeStamp);
		}
		break;

		case AUD_DEC_IOW_SET_PARAM:
		{
			LX_AUD_DECODER_PARAM_T		decParam;

			if ( copy_from_user(&decParam, (void __user *)arg, sizeof(LX_AUD_DECODER_PARAM_T)) )
			{
				AUD_KDRV_ERROR("%s.%d: [AUD_DEC_IOW_SET_DECODING] copy_from_user() Err\n", __F__, __L__);
				return RET_ERROR;
			}

			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_SET_DECODING] codec =%d\n", __F__, __L__, decParam.codecType);
			retVal = AUDIO_SetDecoderParam(allocDev, &decParam);
		}
		break;

		case AUD_DEC_IOW_GET_KDRV_HANDLE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_GET_KDRV_HANDLE] Called\n", __F__, __L__);

			if (copy_to_user((void *)arg, (void *)&(my_dev->allocDev), sizeof(UINT32)))
				return RET_ERROR;
		}
		break;

		case AUD_DEC_IOR_GET_INFO:
		{
			LX_AUD_DECODED_INFO_T esInfo;

			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_GET_ES_INFO] Called\n", __F__, __L__);

			AUDIO_GetDecodedInfo(allocDev, &esInfo);

			if (copy_to_user((void *)arg, (void *)&esInfo, sizeof(LX_AUD_DECODED_INFO_T)))
				return RET_ERROR;
		}
		break;

		case AUD_DEC_IOW_IS_DECODABLE:
		{
			UINT32 isDecodable;

			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_IS_DECODABLE] Called\n", __F__, __L__);

			AUDIO_IsDecodable(allocDev, &isDecodable);

			if (copy_to_user((void *)arg, (void *)&isDecodable, sizeof(UINT32)))
				return RET_ERROR;
		}
		break;

		case AUD_DEC_IO_CLOSE_DEVICE:
		{
			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IO_CLOSE_DEVICE] Called\n", __F__, __L__);
			retVal = AUDIO_CloseDecoder(my_dev);
		}
		break;

		case AUD_DEC_IOW_SET_MODE:
		{
			LX_AUD_DECODER_MODE_T		decMode;

			if ( copy_from_user(&decMode, (void __user *)arg, sizeof(LX_AUD_DECODER_MODE_T)) )
			{
				AUD_KDRV_ERROR("%s.%d: [AUD_DEC_IOW_SET_MODE] copy_from_user() Err\n", __F__, __L__);
				return RET_ERROR;
			}

			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_SET_MODE] drc=%d, downmix=%d, aac=%d, tp=%d, ad=%d, sub=%d\n", __F__, __L__, decMode.drc, decMode.downmix, decMode.aacBypass, decMode.tpTimerInterval, decMode.bSetAD, decMode.bSetSubDec);
			retVal = AUDIO_SetDecoderMode(allocDev, &decMode);
		}
		break;

		case AUD_DEC_IOR_GET_STATUS:
		{
			LX_AUD_DECODED_STATUS_T decodedStatus;

			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_GET_STATUS] Called\n", __F__, __L__);

			AUDIO_GetDecodedStatus(allocDev, &decodedStatus);

			if (copy_to_user((void *)arg, (void *)&decodedStatus, sizeof(LX_AUD_DECODED_STATUS_T)))
				return RET_ERROR;
		}
		break;

		case AUD_DEC_IOW_SET_CERTI_PARAM:
		{
			UINT32		decCertiParam;

			if ( copy_from_user(&decCertiParam, (void __user *)arg, sizeof(UINT32)) )
			{
				AUD_KDRV_ERROR("%s.%d: [AUD_DEC_IOW_SET_DECODING] copy_from_user() Err\n", __F__, __L__);
				return RET_ERROR;
			}

			AUD_KDRV_TRACE("%s.%d: [AUD_DEC_IOW_SET_CERTI_PARAM] certi_param =%d\n", __F__, __L__, decCertiParam);
			retVal = AUDIO_SetDecoderCertiParam(allocDev, decCertiParam);
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

#if 0
/**
 * Is Dual Decoding or Not.
 *
 * @param 	decIndex		[in] decoder index.
 * @return 	if dual decoding - TRUE, else - FALSE.
 * @see		AUDIO_FeedDec(), AUDIO_GetDecodedStatus().
 */
static BOOLEAN _AUDIO_isDualDecoding(SINT32 decIndex)
{
	SINT32		i = 0;

	for(i = 0; i < DEV_DEC_NUM; i++)
	{
		if(i != decIndex)
		{
			if(_gDecoderInfo[i].ui32AllocDev != 0)
			{
				if(_gDecoderInfo[decIndex].decParam.codecType == _gDecoderInfo[i].decParam.codecType)
				{
					if(_gDecoderInfo[i].bIsDualDec == FALSE)
					{
						_gDecoderInfo[decIndex].bIsDualDec = TRUE;
						return TRUE;
					}
				}
			}
		}
	}

	_gDecoderInfo[decIndex].bIsDualDec = FALSE;
	return FALSE;
}
#endif

/**
 * Notify AAC 5.1 Dual Decoding Case to disable PIP HP audio output.
 *
 * @param 	decIndex		[in] decoder index.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		AUDIO_FeedDec(), AUDIO_GetDecodedStatus().
 */
static SINT32 _AUDIO_NotifyAAC51DualDecoding(UINT32 allocDev)
{
	ULONG	flags;
	SINT32	decIndex = 0;

	BOOLEAN	notiFlag = FALSE;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	/* Check a audio dsp performance issue. */
	if((_gDecoderInfo[AUD_DECODER_0].decodedInfo.codecType == LX_AUD_CODEC_AAC)	\
	 &&(_gDecoderInfo[AUD_DECODER_1].decodedInfo.codecType == LX_AUD_CODEC_AAC) )	//AAC Dual Decoding.
	{
		/* Check a AD On status to disable above AD 2 channel audio. */
		if(_gDecoderInfo[decIndex].decMode.bSetAD == FALSE)
		{
			/* Check a AAC 5.1 Dual Decoding to disable Sub 5.1 channel audio. */
			if((_gDecoderInfo[AUD_DECODER_0].ui32ChannelNum == 6)	\
			 &&(_gDecoderInfo[AUD_DECODER_1].ui32ChannelNum == 6) )	//AAC Dual 5.1CH
			{
				notiFlag = TRUE;
			}
		}
		else
		{
			/* Check a AD On status to disable above AD 2 channel audio. */
			if(_gDecoderInfo[AUD_DECODER_1].ui32ChannelNum > 2)		//AAC AD above 2 CH
			{
				notiFlag = TRUE;
			}
		}
	}

	/* Check a AAC 5.1 dual or AD above 2 channel flag to stop sub audio decoding in app. level. */
	if(notiFlag == TRUE)
	{
		//spin lock for protection
		spin_lock_irqsave(&gAudEventSpinLock, flags);

		//Set a audio GET event type for next event.
		gAudGetEvent[AUD_DEV_DEC0].allocDev  = AUD_DEV_DEC0;
		gAudGetEvent[AUD_DEV_DEC0].eventMsg |= LX_AUD_EVENT_DEC_AAC51_DUAL;

		//Set a audio GET event type for next event.
		gAudGetEvent[AUD_DEV_DEC1].allocDev  = AUD_DEV_DEC1;
		gAudGetEvent[AUD_DEV_DEC1].eventMsg |= LX_AUD_EVENT_DEC_AAC51_DUAL;

		//spin unlock for protection
		spin_unlock_irqrestore(&gAudEventSpinLock, flags);

		//Wake up poll event if allocated device and event message is set for DEC0.
		if( (gAudSetEvent[AUD_DEV_DEC0].allocDev != AUD_NO_DEV)		\
		  &&(gAudSetEvent[AUD_DEV_DEC0].eventMsg & LX_AUD_EVENT_DEC_AAC51_DUAL) )
		{
			wake_up_interruptible_all(&gAudPollWaitQueue);
			AUD_KDRV_DEBUG("Dec Info0(%d) : DEC_AAC51_DUAL(%d, %d)\n", allocDev, _gDecoderInfo[AUD_DECODER_0].ui32ChannelNum, _gDecoderInfo[AUD_DECODER_1].ui32ChannelNum);
		}

		//Wake up poll event if allocated device and event message is set for DEC1.
		if( (gAudSetEvent[AUD_DEV_DEC1].allocDev != AUD_NO_DEV)		\
		  &&(gAudSetEvent[AUD_DEV_DEC1].eventMsg & LX_AUD_EVENT_DEC_AAC51_DUAL) )
		{
			wake_up_interruptible_all(&gAudPollWaitQueue);
			AUD_KDRV_DEBUG("Dec Info1(%d) : DEC_AAC51_DUAL(%d, %d)\n", allocDev, _gDecoderInfo[AUD_DECODER_0].ui32ChannelNum, _gDecoderInfo[AUD_DECODER_1].ui32ChannelNum);
		}
	}

	AUD_KDRV_ISR_DEBUG("Dec Info(%d) : NotifyAAC51Dual(%d, %d), notiFlag = %d\n", allocDev, _gDecoderInfo[AUD_DECODER_0].ui32ChannelNum, _gDecoderInfo[AUD_DECODER_1].ui32ChannelNum, notiFlag);
	return RET_OK;
}

/**
 * Get Decoder Writer Structure.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @return 	if succeeded - writer structure, else - NULL.
 * @see		AUDIO_FeedDec(), AUDIO_GetDecodedStatus().
 */
static ADEC_BUF_T* _AUDIO_GetDecoderWriteStructure(UINT32 allocDev)
{
	LX_AUD_ALLOC_MOD_T		cpbModule = ADEC_MODULE_CPB_0;

	UINT32 					bufIndex = 0;
	ADEC_BUF_T				*pWriterStruct = NULL;

	// Get a CPB buffer
	cpbModule = AUDIO_HasThisModuleType(allocDev, LX_AUD_CPB);
	switch(cpbModule)
	{
		case ADEC_MODULE_CPB_0:
		case ADEC_MODULE_CPB_1:

			bufIndex = cpbModule - ADEC_MODULE_CPB_0;
			pWriterStruct =(ADEC_BUF_T *)stCPB[bufIndex].pWriterReaderStruct;
			break;

		case ADEC_MODULE_CPB_2:
		case ADEC_MODULE_CPB_3:
		default:
			AUD_KDRV_ERROR("%s.%d: Unknown CPB buffer(%d)!!!\n", __FUNCTION__, __LINE__, cpbModule);
			return pWriterStruct;
			break;
	}

	AUD_KDRV_PRINT("%s : allocDev %x %x.\n", __F__, allocDev, bufIndex);
	return pWriterStruct;
}

/**
 * Set parameters for WMAPRO.
 *
 * @param 	moduleId		[in] a allocated module.
 * @param 	pDecParam		[in] parameters to set.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		AUDIO_SetDecoderParam().
 */
static SINT32 _AUDIO_SetDecoderParam_WMAPRO(ADEC_MODULE_ID moduleId, LX_AUD_DECODER_PARAM_T *pDecParam)
{
	UINT32			wmaFormatTag	= pDecParam->wmaproInfo.ui32WmaFormatTag;
	UINT32			blockAlign	 	= pDecParam->wmaproInfo.ui32BlockAlign;
	UINT32			avgBitRate		= pDecParam->wmaproInfo.ui32AvgBytesPerSec;
	UINT32			lengthOfDSI		= pDecParam->ui32LengthOfDSI;
	UINT32			channelMask		= 0;
	UINT32			advEncodeOpt2	= 0;
	UINT16			encodeOpt		= 0;
	UINT16			advEncodeOpt	= 0;
	UINT8			*pDSIBuffer		= (UINT8 *)pDecParam->pDSIBuffer;
	WmaCmdSetParam	wmaParam;

	if (pDSIBuffer == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: pDSIBuffer is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	wmaParam.val_samp_freq		= pDecParam->samplingFreq;
	wmaParam.val_num_chan		= pDecParam->wmaproInfo.ui32NumberOfChannel;
	wmaParam.val_pcm_wd_sz		= pDecParam->wmaproInfo.ui32PcmBitsPerSample;
	wmaParam.val_w_fmt_tag		= wmaFormatTag;
	wmaParam.val_blk_align		= blockAlign;
	wmaParam.val_avg_bitrate	= avgBitRate;

	if((wmaFormatTag == WMAPRO_FORMAT_TAG) || (wmaFormatTag == WMALOSSLESS_FORMAT_TAG))
	{
		//Check Sanity
		if(lengthOfDSI != LENGTH_OF_DSI_FOR_WMA3)
		{
			AUD_KDRV_ERROR("%s.%d: DSI length(%d) is less than WMA3 info\n", __FUNCTION__, __LINE__, lengthOfDSI);
			return RET_ERROR;
		}

		//Get a parameters from DSI buffer.
		channelMask		= ADEC_READ32_LE(pDSIBuffer + 2);
		advEncodeOpt2	= ADEC_READ32_LE(pDSIBuffer + 6);
		encodeOpt		= ADEC_READ16_LE(pDSIBuffer + 14);
		advEncodeOpt	= ADEC_READ16_LE(pDSIBuffer + 16);
	}
	else if(wmaFormatTag == WMA2_FORMAT_TAG)
	{
		if(lengthOfDSI != LENGTH_OF_DSI_FOR_WMA2)
		{
			AUD_KDRV_ERROR("%s.%d: DSI length(%d) is less than WMA2 info\n", __FUNCTION__, __LINE__, lengthOfDSI);
			return RET_ERROR;
		}

		//Get a parameters from DSI buffer.
		encodeOpt		= ADEC_READ16_LE(pDSIBuffer + 4);
	}
	else				// WMA1
	{
		if(lengthOfDSI != LENGTH_OF_DSI_FOR_WMA1)
		{
			AUD_KDRV_ERROR("%s.%d: DSI length(%d) is less than WMA1 info\n", __FUNCTION__, __LINE__, lengthOfDSI);
			return RET_ERROR;
		}

		//Get a parameters from DSI buffer.
		encodeOpt		= ADEC_READ16_LE(pDSIBuffer + 2);
	}

	wmaParam.val_encode_opt		= encodeOpt;
	wmaParam.val_ch_mask		= channelMask;
	wmaParam.val_adv_encode_opt	= advEncodeOpt;
	wmaParam.adv_encode_opt2	= advEncodeOpt2;

	AUDIO_IMC_SendCmdParam(WMA_CMD_SET_PARAM, moduleId, sizeof(WmaCmdSetParam), &wmaParam);

	AUD_KDRV_PRINT("%s.%d: WMA Info: freq=%u, ch#=%u, width=%u, tag=0x%X, align=%u, encodeOpt=0x%08X, avgBitrate=%u, chMask=0x%08X, advEncodeOpt=0x%08X, advEncodeOpt2=0x%08X\n",
					__FUNCTION__, __LINE__,
					wmaParam.val_samp_freq,
					wmaParam.val_num_chan,
					wmaParam.val_pcm_wd_sz,
					wmaParam.val_w_fmt_tag,
					wmaParam.val_blk_align,
					wmaParam.val_encode_opt,
					wmaParam.val_avg_bitrate,
					wmaParam.val_ch_mask,
					wmaParam.val_adv_encode_opt,
					wmaParam.adv_encode_opt2);

	return RET_OK;
}

/**
 * Set parameters for RA8.
 *
 * @param 	moduleId		[in] a allocated module.
 * @param 	pDecParam		[in] parameters to set.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		AUDIO_SetDecoderParam().
 */
static SINT32 _AUDIO_SetDecoderParam_RA8(ADEC_MODULE_ID moduleId, LX_AUD_DECODER_PARAM_T *pDecParam)
{
	Ra8CmdSetParam	raParam;
	UINT32			leafSize		= pDecParam->raInfo.ui32LeafSize;			// leaf size
	UINT32			lengthOfDSI		= pDecParam->ui32LengthOfDSI;
	UINT8			*pDSIBuffer		= (UINT8 *)pDecParam->pDSIBuffer;
	UINT8			majorVer;
	UINT8			minorVer;
	UINT16			samplesPerFrame;		// number of samples per frame
	UINT16			freqResponse;			// determines frequency response
	UINT16			cplStartRegion	= 0;	// related to joint stereo encoding
	UINT16			cplQuantBits	= 0;	// related to joint stereo encoding

	if(pDSIBuffer == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: pDSIBuffer is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	// 8bytes, 12bytes or 16bytes
	if(lengthOfDSI < MIN_LENGTH_OF_DSI_FOR_RA8)
	{
		AUD_KDRV_ERROR("%s.%d: DSI length(%d) is less than RA info\n", __FUNCTION__, __LINE__, lengthOfDSI);
		return RET_ERROR;
	}

	majorVer		= pDSIBuffer[0];
	minorVer		= pDSIBuffer[3];
	samplesPerFrame = ADEC_READ16_BE(pDSIBuffer + 4);
	freqResponse	= ADEC_READ16_BE(pDSIBuffer + 6);

	if((majorVer >= RA8_MAJOR_V1) && (minorVer >= RA8_MINOR_V3) && (lengthOfDSI >= MIN_LENGTH_OF_DSI_FOR_RA8_V13))
	{
		cplStartRegion = ADEC_READ16_BE(pDSIBuffer + 12);
		cplQuantBits   = ADEC_READ16_BE(pDSIBuffer + 14);
	}

	raParam.nsamples	= (UINT32)samplesPerFrame;
	raParam.regions		= (UINT32)freqResponse;
	raParam.bits		= leafSize;
	raParam.cplstart	= (UINT32)cplStartRegion;
	raParam.cplqbits	= (UINT32)cplQuantBits;
	raParam.nchannels	= pDecParam->raInfo.ui32NumberOfChannel;

	AUDIO_IMC_SendCmdParam(RA8_CMD_SET_PARAM, moduleId, sizeof(Ra8CmdSetParam), &raParam);

	AUD_KDRV_PRINT("%s.%d: RA Info: samplesPerFrame=%u, freqResponse=%u, leafSize=%u, cplStartRegion=%u, cplQuantBits=%u, nchannels=%u\n",
					__FUNCTION__, __LINE__,
					raParam.nsamples,
					raParam.regions,
					raParam.bits,
					raParam.cplstart,
					raParam.cplqbits,
					raParam.nchannels);

	return RET_OK;
}

/**
 * Set codec parameters for audio decoder.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pDecParam		[in] parameters to set.
 * @return 	decoder module.
 * @see		AUDIO_SetDecoderParam().
 */
static ADEC_MODULE_ID _AUDIO_SetDecoderParam_Codec(UINT32 allocDev, LX_AUD_DECODER_PARAM_T *pDecParam)
{
	SINT32		decIndex = 0;

	ADEC_MODULE_ID		decoderModule = ADEC_MODULE_NOT_DEF;
	ADEC_MODULE_ID		managerModule = ADEC_MODULE_NOT_DEF;

	LX_AUD_DECODER_OUT_MODE_T 	outMode = LX_AUD_DECODER_OUT_LR;

	CmCmdCreateModule		createModule;

	PcmDecCmdSetParam 	pcmDecParam;
	DdcCmdSetParam 		ddcParam;
	DdtCmdSetParam 		ddtParam;
	BypassESCmdSetMode bypassEsParam;

	//Get a decoder index from allocated device.
	decIndex = GET_DEC_INDEX(allocDev);

	if(pDecParam->codecType == LX_AUD_CODEC_AAC_BYPASS)
	{
		//Get a decoder module from allocated module.
		decoderModule = (ADEC_MODULE_ID)AUDIO_AllocModule(allocDev, LX_AUD_BYPASS_ES_DSP0, 0);
		AUD_KDRV_PRINT("%s.%d: WATCH bypassModule = %d\n", __FUNCTION__, __LINE__, decoderModule);

		if((LX_AUD_ALLOC_MOD_T)decoderModule != ADEC_MODULE_NO_MOD )
		{
			AUD_KDRV_RM("Module[%s] [Alloc:%s] \n", modTypeStr[LX_AUD_DEC], (char *)allocMod_Str[decoderModule]);
		}
		else
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n", modTypeStr[LX_AUD_DEC]);
			return ADEC_MODULE_NOT_DEF;
		}

		// 0 - AAC
		// 1 - HE-AAC v1
		// 2 - HE-AAC v2

		bypassEsParam.mode				= AU_BASED_MODE ;
		bypassEsParam.over_protect		= ENABLE_OVERFLOW_PROTECTION;
		bypassEsParam.version			= 0;

		(void)AUDIO_IMC_SendCmdParam(BYPASSES_CMD_SET_MODE, decoderModule, sizeof(BypassESCmdSetMode), &bypassEsParam);


		return decoderModule;
	}

	//Get a decoder module from allocated module.
	decoderModule = (ADEC_MODULE_ID)AUDIO_AllocModule(allocDev, LX_AUD_DEC, 0);

	if((LX_AUD_ALLOC_MOD_T)decoderModule != ADEC_MODULE_NO_MOD )
	{
		AUD_KDRV_RM("Module[%s] [Alloc:%s] \n", modTypeStr[LX_AUD_DEC], (char *)allocMod_Str[decoderModule]);
	}
	else
	{
		AUD_KDRV_ERROR(" Module[%s] is not available \n", modTypeStr[LX_AUD_DEC]);
		return ADEC_MODULE_NOT_DEF;
	}

	//Create Decoder module before connect
	managerModule = _AUDIO_GetManagerModule(decoderModule);
	if(managerModule != ADEC_MODULE_NOT_DEF)
	{
		createModule.module_id = decoderModule;
		createModule.module_param.codec_param.media_type = (ADEC_MEDIA_TYPE)pDecParam->codecType;

		AUDIO_IMC_SendCmdParam(CM_CMD_CREATE_MODULE, managerModule, sizeof(CmCmdCreateModule), &createModule);
	}

	//Set a param of PCM decoder
	if(pDecParam->codecType == LX_AUD_CODEC_PCM)
	{
		pcmDecParam.i_samp_freq	= pDecParam->samplingFreq;

		//If PCM data is from memory, set a pcm decoding information from app.
		if(pDecParam->input == LX_AUD_INPUT_SYSTEM)
		{
			pcmDecParam.i_pcm_wd_sz = pDecParam->pcmInfo.ui32PcmBitsPerSample;
			pcmDecParam.i_num_chan	= pDecParam->pcmInfo.ui32NumberOfChannel;
			pcmDecParam.i_endian	= pDecParam->pcmInfo.ui32Endian;
			pcmDecParam.i_signed	= pDecParam->pcmInfo.ui32Signed;

			/* Set a default decoder output mode for memory */
			outMode = LX_AUD_DECODER_OUT_LR;
			(void)AUDIO_IMC_SendCmdParam(ADEC_CMD_SET_OUTMODE, decoderModule, sizeof(LX_AUD_DECODER_OUT_MODE_T), &outMode);

			_gDecoderInfo[decIndex].decOutMode = outMode;
		}
		else
		{
			//This is a pre-defined value in audio DSP module.
			pcmDecParam.i_pcm_wd_sz = 32;
			pcmDecParam.i_num_chan	= 2;
			pcmDecParam.i_endian	= LX_AUD_RENDER_LITTLE_ENDIAN;
			pcmDecParam.i_signed	= LX_AUD_RENDER_SIGNED;
		}

		AUDIO_IMC_SendCmdParam(PCMDEC_CMD_SET_PARAM, decoderModule, sizeof(PcmDecCmdSetParam), &pcmDecParam);
	}
	//Set a param of DDC decoder
	else if(pDecParam->codecType == LX_AUD_CODEC_AC3)
	{
		ddcParam.drc_mode	  = _gDecoderInfo[decIndex].decMode.drc;		// LX_ADEC_DOLBY_LINE_MODE;	// ATSC = LX_ADEC_DOLBY_LINE_MODE, DVB = LX_ADEC_DOLBY_RF_MODE
		ddcParam.downmix_mode = _gDecoderInfo[decIndex].decMode.downmix;	// LX_ADEC_LTRT_MODE;		// DDC = LX_ADEC_LTRT_MODE, DDT = LX_ADEC_LORO_MODE

		//To check codecs same, dual decoding
		//ddcParam.isDualDec = (UINT32)_AUDIO_isDualDecoding(decIndex);

		//To check sub decoding mode.
		ddcParam.isSubDec  = (UINT32)_gDecoderInfo[decIndex].decMode.bSetSubDec;	//Sub Decoding mode for SPDIF ES Not Support(Main Dec(SPDIF ES Support).

		//Set a AD Mode for Implement a meta data processing and mix volume for overload.
		ddcParam.isADMode  = (UINT32)_gDecoderInfo[decIndex].decMode.bSetAD;	// AD mode : 0 = Off(default), 1 = On(DEC0, DEC1 must set)

		AUDIO_IMC_SendCmdParam(DDC_CMD_SET_PARAM, decoderModule, sizeof(DdcCmdSetParam), &ddcParam);
		AUD_KDRV_DEBUG("%s.%d: MS10_DDC : isSubDec(%d), isADMode(%d)\n", __FUNCTION__, __LINE__, ddcParam.isSubDec, ddcParam.isADMode);
	}
	// set param of DDT decoder
	else if(pDecParam->codecType == LX_AUD_CODEC_AAC)
	{
		ddtParam.drc_mode	  = _gDecoderInfo[decIndex].decMode.drc;		// LX_ADEC_DOLBY_LINE_MODE;	// ATSC = LX_ADEC_DOLBY_LINE_MODE, DVB = LX_ADEC_DOLBY_RF_MODE
		ddtParam.downmix_mode = _gDecoderInfo[decIndex].decMode.downmix;	// LX_ADEC_LORO_MODE;		// DDC = LX_ADEC_LTRT_MODE, DDT = LX_ADEC_LORO_MODE

		//To check codecs same, dual decoding
		//ddtParam.isDualDec = (UINT32)_AUDIO_isDualDecoding(decIndex);

		//To check sub decoding mode.
		ddtParam.isSubDec  = (UINT32)_gDecoderInfo[decIndex].decMode.bSetSubDec;	//Sub Decoding mode for SPDIF ES Not Support(Main Dec(SPDIF ES Support).

		//Set a AD Mode for Implement a meta data processing and mix volume for overload.
		ddtParam.isADMode  = (UINT32)_gDecoderInfo[decIndex].decMode.bSetAD;	// AD mode : 0 = Off(default), 1 = On(DEC0, DEC1 must set)

		//Set a SPDIF AAC ES Bypass mode
		ddtParam.iec_fmt = (UINT32)_gDecoderInfo[decIndex].decMode.aacBypass;

		//Set input type
		ddtParam.inputtype = (MS10_DDT_INPUT_T)pDecParam->input;

		AUDIO_IMC_SendCmdParam(DDT_CMD_SET_PARAM, decoderModule, sizeof(DdtCmdSetParam), &ddtParam);
		AUD_KDRV_DEBUG("%s.%d: MS10_DDT(isSubDec %d, iec_fmt %d, isADMode %d input %d)\n", __FUNCTION__, __LINE__, ddtParam.isSubDec, ddtParam.iec_fmt, ddtParam.isADMode, ddtParam.inputtype);
	}
	// set param of WMA
	else if(pDecParam->codecType == LX_AUD_CODEC_WMA_PRO)
	{
		_AUDIO_SetDecoderParam_WMAPRO(decoderModule, pDecParam);
	}
	// set param of RA8
	else if(pDecParam->codecType == LX_AUD_CODEC_RA8)
	{
		_AUDIO_SetDecoderParam_RA8(decoderModule, pDecParam);
	}

	//Send a IMC command - INIT : This command is only called when decoder codec is created once.
	(void)AUDIO_IMC_SendCmd(ADEC_CMD_INIT, decoderModule);

	//Register a decoder event
	_AUDIO_RegisterDecoderEvent(allocDev);

	AUD_KDRV_PRINT("%s.%d: decoderModule = %d\n", __FUNCTION__, __LINE__, decoderModule);
	return decoderModule;
}

/**
 * Set input parameters for audio decoder.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pDecParam		[in] parameters to set.
 * @return 	input module.
 * @see		AUDIO_SetDecoderParam().
 */
static ADEC_MODULE_ID _AUDIO_SetDecoderParam_Input(UINT32 allocDev, LX_AUD_DECODER_PARAM_T *pDecParam)
{
	ADEC_MODULE_ID		inputModule		= ADEC_MODULE_NOT_DEF;
	LX_AUD_MOD_TYPE_T	modTypeToAlloc 	= LX_AUD_MOD_TYPE_NONE;
	SINT32				decIndex = 0;

	TpCmdSetParam		tpSetParam;
	SifCmdSetFmt		sifSetFmt;
	AdcCmdSetFmt		adcSetFmt;
	HdmiCmdSetFmt		hdmiSetFmt;
	HdmiCmdSetMode		hdmiSetMode;

	//Get a input module from audio source
	if(pDecParam->input == LX_AUD_INPUT_TP0)
	{
		modTypeToAlloc = LX_AUD_TP_IN0;
	}
	else if(pDecParam->input == LX_AUD_INPUT_TP1)
	{
		modTypeToAlloc = LX_AUD_TP_IN1;
	}
	else if(pDecParam->input == LX_AUD_INPUT_SIF)
	{
		modTypeToAlloc = LX_AUD_SIF_IN;
	}
	else if(pDecParam->input == LX_AUD_INPUT_ADC)
	{
		modTypeToAlloc = LX_AUD_ADC_IN;
	}
	else if(pDecParam->input == LX_AUD_INPUT_HDMI)
	{
		modTypeToAlloc = LX_AUD_HDMI_IN;
	}
	else if(pDecParam->input == LX_AUD_INPUT_SYSTEM)
	{
		modTypeToAlloc = LX_AUD_CPB;
	}
	else
	{
		AUD_KDRV_ERROR("Input[%d] is not available \n", pDecParam->input);
		return ADEC_MODULE_NOT_DEF;
	}

	//Allocate a audio input module.
	if(modTypeToAlloc != LX_AUD_MOD_TYPE_NONE)
	{
		inputModule = (ADEC_MODULE_ID)AUDIO_AllocModule(allocDev, modTypeToAlloc, 0);

		if((LX_AUD_ALLOC_MOD_T)inputModule == ADEC_MODULE_NO_MOD)
		{
			AUD_KDRV_ERROR(" Module[%s] is not available \n", modTypeStr[modTypeToAlloc]);
			return RET_ERROR;
		}

		AUD_KDRV_RM("Module[%s] is allocated.[Alloc:%s] \n", modTypeStr[modTypeToAlloc], (char *)allocMod_Str[inputModule]);
	}

	//Set a input parameter for each audio input port.
	if(pDecParam->input == LX_AUD_INPUT_TP0 || pDecParam->input == LX_AUD_INPUT_TP1)
	{
		//Get a decoder index
		decIndex = GET_DEC_INDEX(allocDev);
		if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
		{
			AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
			return RET_ERROR;
		}

		tpSetParam.codec_type = (ADEC_MEDIA_TYPE)pDecParam->codecType;
		tpSetParam.interval = _gDecoderInfo[decIndex].decMode.tpTimerInterval;

		AUDIO_IMC_SendCmdParam(TP_CMD_SET_PARAM, inputModule, sizeof(TpCmdSetParam), &tpSetParam);
	}
	else if(pDecParam->input == LX_AUD_INPUT_SIF)
	{
		sifSetFmt.format 			  	= 0;
		sifSetFmt.resolution 		  	= 3;
		sifSetFmt.sck_polarity_control 	= 0;
		sifSetFmt.lrck_polarity_control	= 0;
		AUDIO_IMC_SendCmdParam(SIF_CMD_SET_FMT, inputModule, sizeof(SifCmdSetFmt), &sifSetFmt);
	}
	else if(pDecParam->input == LX_AUD_INPUT_ADC)
	{
		adcSetFmt.format 	 = 0;
		adcSetFmt.resolution = 3;

		//Set I2S and 24 bit mode for I2S input : H13 ACE bug is fixed.
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
			//24 bit(0x03)
			adcSetFmt.sck_polarity_control = 0;
		}
		//Set I2S and 24 bit mode for I2S input(L/R change)
		else if(lx_chip_rev() >= LX_CHIP_REV(L9, B0))
		{
			//24 bit(0x03), SCLK polarity invert.(0x04)
			adcSetFmt.sck_polarity_control = 1;
		}
		else
		{
			//24 bit(0x03)
			adcSetFmt.sck_polarity_control = 0;
		}
		adcSetFmt.lrck_polarity_control = 0;
		AUDIO_IMC_SendCmdParam(ADC_CMD_SET_FMT, inputModule, sizeof(AdcCmdSetFmt), &adcSetFmt);
	}
	else if(pDecParam->input == LX_AUD_INPUT_HDMI)
	{
		if(pDecParam->codecType == LX_AUD_CODEC_PCM)
		{
			hdmiSetFmt.format 				= 0;
			hdmiSetFmt.resolution 			= 3;
			hdmiSetFmt.sck_polarity_control = 0;
			hdmiSetFmt.lrck_polarity_control= 0;
			AUDIO_IMC_SendCmdParam(HDMI_CMD_SET_FMT, inputModule, sizeof(HdmiCmdSetFmt), &hdmiSetFmt);

			hdmiSetMode.mode = 0;
		}
		else
		{
			hdmiSetMode.mode = 1;
		}
		AUDIO_IMC_SendCmdParam(HDMI_CMD_SET_MODE, inputModule, sizeof(hdmiSetMode), &hdmiSetMode);
	}

	AUD_KDRV_PRINT("%s.%d: inputModule = %d\n", __FUNCTION__, __LINE__, inputModule);
	return inputModule;
}

/**
 * Set a audio channel mode from decoded information.
 *
 * @param 	pEsInfoParam	[in] decoder ES info from decoder.
 * @param 	pDecodedInfo	[in] decoded ES info for notity.
 * @return 	Channel Number.
 * @see		_AUDIO_DecodedInfoCb().
 */
static UINT8 _AUDIO_SetChannelMode(DecEvtESDecInfoParam *pEsInfoParam, LX_AUD_DECODED_INFO_T *pDecodedInfo)
{
	UINT8	channelNum;

	LX_AUD_CODEC_T	adecFormat;

	adecFormat = pEsInfoParam->media_type;

	//Set a default audio channel number and mode.
	channelNum = 2;
	pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;

	if(adecFormat == LX_AUD_CODEC_PCM)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case PCMDEC_CHANNELMODE_1CH:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case PCMDEC_CHANNELMODE_2CH:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			case PCMDEC_CHANNELMODE_3CH:
				channelNum = 3;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case PCMDEC_CHANNELMODE_4CH:
				channelNum = 4;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case PCMDEC_CHANNELMODE_5CH:
				channelNum = 5;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case PCMDEC_CHANNELMODE_6CH:
				channelNum = 6;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_AC3)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case MS10DDC_CHANNELMODE_DUAL_MONO:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_DUAL_MONO;
				break;

			case MS10DDC_CHANNELMODE_MONO_CENTER:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case MS10DDC_CHANNELMODE_STEREO:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			case MS10DDC_CHANNELMODE_3_0_CHANNEL:
			case MS10DDC_CHANNELMODE_2_1_CHANNEL:
				channelNum = 3;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case MS10DDC_CHANNELMODE_3_1_CHANNEL:
			case MS10DDC_CHANNELMODE_2_2_CHANNEL:
				channelNum = 4;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case MS10DDC_CHANNELMODE_3_2_CHANNEL:
				channelNum = 6;		//5.1ch
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_AAC)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case MS10DDT_CHANNELMODE_MONO:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case MS10DDT_CHANNELMODE_PARAMETRIC_STEREO:
			case MS10DDT_CHANNELMODE_STEREO:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			case MS10DDT_CHANNELMODE_DUAL_CHANNEL:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_DUAL_MONO;
				break;

			case MS10DDT_CHANNELMODE_3_CHANNEL_FRONT:
			case MS10DDT_CHANNELMODE_3_CHANNEL_SURR:
			case MS10DDT_CHANNELMODE_2_1_STEREO:
				channelNum = 3;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case MS10DDT_CHANNELMODE_4_CHANNEL_2SURR:
			case MS10DDT_CHANNELMODE_4_CHANNEL_1SURR:
			case MS10DDT_CHANNELMODE_3_1_CHANNEL_FRONT:
			case MS10DDT_CHANNELMODE_3_1_CHANNEL_SURR:
				channelNum = 4;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case MS10DDT_CHANNELMODE_5_CHANNEL:
			case MS10DDT_CHANNELMODE_4_1_CHANNEL_2SURR:
			case MS10DDT_CHANNELMODE_4_1_CHANNEL_1SURR:
				channelNum = 5;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case MS10DDT_CHANNELMODE_5_1_CHANNEL:
				channelNum = 6;	//AAC 5.1 Ch. -> Not support for dual decoding.
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_MP3)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case MP3DEC_CHANNELMODE_STEREO:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			case MP3DEC_CHANNELMODE_JOINT_STEREO:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_JOINT_STEREO;
				break;

			case MP3DEC_CHANNELMODE_DUAL_MONO:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_DUAL_MONO;
				break;

			case MP3DEC_CHANNELMODE_MONO:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_WMA_PRO)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case WMADEC_CHANNELMODE_STEREO:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			case WMADEC_CHANNELMODE_MONO:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case WMADEC_CHANNELMODE_THREE:
				channelNum = 3;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case WMADEC_CHANNELMODE_BACK:
			case WMADEC_CHANNELMODE_QUAD:
				channelNum = 4;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case WMADEC_CHANNELMODE_5:
				channelNum = 5;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case WMADEC_CHANNELMODE_5DOT1:
				channelNum = 6;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case WMADEC_CHANNELMODE_6DOT1:
				channelNum = 7;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case WMADEC_CHANNELMODE_7DOT1:
				channelNum = 8;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_DTS)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case DTSDEC_CHANNELMODE_1CH:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case DTSDEC_CHANNELMODE_2CH:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			case DTSDEC_CHANNELMODE_3CH:
				channelNum = 3;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case DTSDEC_CHANNELMODE_4CH:
				channelNum = 4;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case DTSDEC_CHANNELMODE_5CH:
				channelNum = 5;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case DTSDEC_CHANNELMODE_6CH:
				channelNum = 6;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_VORBIS)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case OGGDEC_CHANNELMODE_1CH:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case OGGDEC_CHANNELMODE_2CH:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_AMR_WB)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case AMRWBDEC_CHANNELMODE_MONO:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_AMR_NB)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case AMRNBDEC_CHANNELMODE_MONO:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_RA8)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case RA8DEC_CHANNELMODE_1CH:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case RA8DEC_CHANNELMODE_2CH:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}
	else if(adecFormat == LX_AUD_CODEC_FLAC)
	{
		switch(pEsInfoParam->channel_mode)
		{
			case FLACDEC_CHANNELMODE_1CH:
				channelNum = 1;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MONO;
				break;

			case FLACDEC_CHANNELMODE_2CH:
				channelNum = 2;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_STEREO;
				break;

			case FLACDEC_CHANNELMODE_3CH:
				channelNum = 3;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case FLACDEC_CHANNELMODE_4CH:
				channelNum = 4;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case FLACDEC_CHANNELMODE_5CH:
				channelNum = 5;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case FLACDEC_CHANNELMODE_6CH:
				channelNum = 6;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case FLACDEC_CHANNELMODE_7CH:
				channelNum = 7;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			case FLACDEC_CHANNELMODE_8CH:
				channelNum = 8;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_MULTI;
				break;

			default:
				channelNum = 0;
				pDecodedInfo->esInfo.audioMode = LX_AUD_DECODER_MODE_UNKNOWN;
				break;
		}
	}

	return channelNum;
}

/**
 * callback function to update Decoded ES inforamtion.
 * @see		_AUDIO_RegisterDecoderEvent().
 */
static SINT32 _AUDIO_DecodedInfoCb(void *_param, int _paramLen, void *_cbParam)
{
	UINT8	channelNum = 2;

	ULONG	flags;
	UINT32	allocDev = AUD_DEV_DEC0;

	DecEvtESDecInfoParam	*pEsInfoParam = NULL;
	AUD_DECODER_INFO_T		*pDecInfo 	  = NULL;
	LX_AUD_DECODED_INFO_T 	*pDecodedInfo = NULL;

	pEsInfoParam = (DecEvtESDecInfoParam *)_param;
	pDecInfo 	 = (AUD_DECODER_INFO_T *)_cbParam;
	allocDev	 = pDecInfo->ui32AllocDev;
	pDecodedInfo = &(pDecInfo->decodedInfo);

	// Print For Debug
	if(_paramLen != sizeof(DecEvtESDecInfoParam))
	{
		AUD_KDRV_ERROR("Dec Es Info : Param Length Error[Expected:%d][Input:%d]\n", sizeof(DecEvtESDecInfoParam), _paramLen);
		return RET_ERROR;
	}

	//Set a audio codec type.
	pDecodedInfo->esInfo.adecFormat = (LX_AUD_CODEC_T)pEsInfoParam->media_type;

	//Set a audio channel mode.
	channelNum = _AUDIO_SetChannelMode(pEsInfoParam, pDecodedInfo);
	pDecInfo->ui32ChannelNum = channelNum;

	//Copy a additional decoded info.
	pDecodedInfo->codecType		   = (LX_AUD_CODEC_T)pEsInfoParam->media_type;
	pDecodedInfo->samplingFreq	   = pEsInfoParam->sample_rate;
	pDecodedInfo->ui32AvgBitRate   = pEsInfoParam->avg_bit_rate;
	pDecodedInfo->ui32NumOfChannel = pEsInfoParam->num_of_channel;
	pDecodedInfo->ui32BitPerSample = pEsInfoParam->bit_per_sample;

	//Copy a additional decoded es info for app.
	if(pDecodedInfo->esInfo.adecFormat == LX_AUD_CODEC_AC3)
	{
		DecAC3EsInfo	ac3EsInfo;

		pDecodedInfo->esInfo.ac3ESInfo.bitRate 	  = pEsInfoParam->avg_bit_rate/(1000*32);
		pDecodedInfo->esInfo.ac3ESInfo.sampleRate = pEsInfoParam->sample_rate/1000;
		pDecodedInfo->esInfo.ac3ESInfo.channelNum = channelNum;

		memcpy(&ac3EsInfo, pEsInfoParam->es_info, sizeof(DecAC3EsInfo));
		pDecodedInfo->esInfo.ac3ESInfo.EAC3 = ac3EsInfo.EAC3;
	}
	else if(pDecodedInfo->esInfo.adecFormat == LX_AUD_CODEC_MP3)
	{
		DecMPEGEsInfo	mpegEsInfo;

		pDecodedInfo->esInfo.mpegESInfo.bitRate = pEsInfoParam->avg_bit_rate/(1000*32);
		pDecodedInfo->esInfo.mpegESInfo.sampleRate = pEsInfoParam->sample_rate/1000;
		pDecodedInfo->esInfo.mpegESInfo.channelNum = channelNum;

		memcpy(&mpegEsInfo, pEsInfoParam->es_info, sizeof(DecMPEGEsInfo));
		pDecodedInfo->esInfo.mpegESInfo.layer = mpegEsInfo.layer;
	}
	else if(pDecodedInfo->esInfo.adecFormat == LX_AUD_CODEC_AAC)
	{
		DecHEAACEsInfo	heaacEsInfo;

		memcpy(&heaacEsInfo, pEsInfoParam->es_info, sizeof(DecHEAACEsInfo));
		pDecodedInfo->esInfo.heAAcEsInfo.version = heaacEsInfo.version;
		pDecodedInfo->esInfo.heAAcEsInfo.transmissionformat = heaacEsInfo.transmissionformat;
		pDecodedInfo->esInfo.heAAcEsInfo.channelNum = channelNum;

		//Check a AAC 5.1 dual decoding case.
		(void)_AUDIO_NotifyAAC51DualDecoding(allocDev);

		//Check a AAC Codec decoding case.
		if(allocDev == AUD_DEV_DEC0 && pDecInfo->decParam.input == LX_AUD_INPUT_TP0)
		{
			//spin lock for protection
			spin_lock_irqsave(&gAudEventSpinLock, flags);

			//Set a audio GET event type for next event.
			gAudGetEvent[allocDev].allocDev  = allocDev;
			gAudGetEvent[allocDev].eventMsg |= LX_AUD_EVENT_DEC_AAC_CODEC;

			//spin unlock for protection
			spin_unlock_irqrestore(&gAudEventSpinLock, flags);

			//Wake up poll event if allocated device and event message is set for DEC0.
			if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
			  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_DEC_AAC_CODEC) )
			{
				wake_up_interruptible_all(&gAudPollWaitQueue);
				AUD_KDRV_DEBUG("Dec Info(%d) : DEC_(HE)AAC_Codec(ver = %d)\n", allocDev, heaacEsInfo.version);
			}
		}
	}

	//For debug print.
	if(pDecodedInfo->esInfo.audioMode == LX_AUD_DECODER_MODE_DUAL_MONO)
	{
		AUD_KDRV_DEBUG("Dec Info(DUAL_MONO) : channelNum(%d)\n", channelNum);
	}
	else if(pDecodedInfo->esInfo.audioMode == LX_AUD_DECODER_MODE_MULTI)
	{
		AUD_KDRV_DEBUG("Dec Info(MULTI) : channelNum(%d)\n", channelNum);
	}
	else if(pDecodedInfo->esInfo.audioMode == LX_AUD_DECODER_MODE_MONO)
	{
		AUD_KDRV_DEBUG("Dec Info(MONO) : channelNum(%d)\n", channelNum);
	}
	else if(pDecodedInfo->esInfo.audioMode == LX_AUD_DECODER_MODE_JOINT_STEREO)
	{
		AUD_KDRV_DEBUG("Dec Info(JOINT_STEREO) : CN(%d)\n", channelNum);
	}

	AUD_KDRV_DEBUG("Dec Info(%d) : Type(%d), Fs(%d), Ch(%d), Bs(%d), Br(%d), Cm(%d)\n", \
					allocDev, pEsInfoParam->media_type, pEsInfoParam->sample_rate, pEsInfoParam->num_of_channel, pEsInfoParam->bit_per_sample, pEsInfoParam->avg_bit_rate, pEsInfoParam->channel_mode);
	return RET_OK;
}

/**
 * callback function to update decodable inforamtion.
 * @see		_AUDIO_RegisterDecoderEvent().
 */
static SINT32 _AUDIO_DecIsDecodableCb(void *_param, int	_paramLen, void *_cbParam)
{
	UINT32					*pIsDecodable = NULL;
	AUD_DECODER_INFO_T		*pDecInfo 	 = NULL;
	DecEvtESExistInfoParam	*pEsExistInfo = NULL;

	pEsExistInfo = (DecEvtESExistInfoParam *)_param;
	pDecInfo = (AUD_DECODER_INFO_T *)_cbParam;
	pIsDecodable = &(pDecInfo->decIsDecodable);

	// Print For Debug
	if (_paramLen != sizeof(DecEvtESExistInfoParam))
	{
		AUD_KDRV_ERROR("Decodable : Param Length Error[Expected:%d][Input:%d]\n", sizeof(DecEvtESExistInfoParam), _paramLen);
		return RET_ERROR;
	}

	*pIsDecodable = pEsExistInfo->es_exist;

	AUD_KDRV_DEBUG("Dec Decodable : %d\n", pEsExistInfo->es_exist);
	return RET_OK;
}

/**
 * callback function to notificate Decoder error inforamtion.
 * @see		_AUDIO_RegisterDecoderEvent().
 */
static SINT32 _AUDIO_DecErrorCb(void *_param, int _paramLen, void *_cbParam)
{
	ULONG	flags;
	UINT32	allocDev = AUD_DEV_DEC0;

	DecEvtDecErrorParam		*pErrorParam = NULL;
	AUD_DECODER_INFO_T		*pDecInfo 	 = NULL;

	pErrorParam = (DecEvtDecErrorParam *)_param;
	pDecInfo	= (AUD_DECODER_INFO_T *)_cbParam;
	allocDev	= pDecInfo->ui32AllocDev;

	// Print For Debug
	if(_paramLen != sizeof(DecEvtDecErrorParam))
	{
		AUD_KDRV_ERROR("Dec Error : Param Length Error[Expected:%d][Input:%d]\n", sizeof(DecEvtDecErrorParam), _paramLen);
		return RET_ERROR;
	}

	if ( pDecInfo->ui32AllocDev < AUD_DEV_DEC0 || pDecInfo->ui32AllocDev > AUD_DEV_DEC1)
	{
		AUD_KDRV_ERROR("Check CB ui32AllocDev [%d][%x]\n",pDecInfo->ui32AllocDev,pDecInfo->ui32AllocDev  );
		return RET_ERROR;
	}

	if(pErrorParam->error_type == 1 || pErrorParam->error_type == 2) // fatal decoding error(1), Sampling rate 변경시 Error 2
	{
		AUDIO_StopDecoder(pDecInfo->ui32AllocDev);

		if(pDecInfo->decParam.input != LX_AUD_INPUT_SYSTEM)
		{
			AUDIO_FlushDecoder(pDecInfo->ui32AllocDev);
		}

		AUDIO_InitDecoder(pDecInfo->ui32AllocDev);
		AUDIO_StartDecoder(pDecInfo->ui32AllocDev);
	}

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Set a audio GET event type for next event.
	gAudGetEvent[allocDev].allocDev  = allocDev;
	gAudGetEvent[allocDev].eventMsg |= LX_AUD_EVENT_DEC_ERROR;

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	//Wake up poll event if allocated device and event message is set.
	if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
	  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_DEC_ERROR) )
	{
		wake_up_interruptible_all(&gAudPollWaitQueue);
		AUD_KDRV_DEBUG("Dec Error(%d) : LX_AUD_EVENT_DEC_ERROR\n", allocDev);
	}

	AUD_KDRV_DEBUG("Dec Error(%d) : Type(%d), Err(%d)\n", allocDev, pErrorParam->media_type, pErrorParam->error_type);
	return RET_OK;
}

/**
 * callback function to notificate TP input error inforamtion.
 * @see		_AUDIO_RegisterDecoderEvent().
 */
static SINT32 _AUDIO_TpErrorCb(void *_param, int _paramLen, void *_cbParam)
{
	ULONG	flags;
	UINT32	allocDev = AUD_DEV_DEC0;

	TpEvtPdecErrorParam		*pErrorParam = NULL;
	AUD_DECODER_INFO_T		*pDecInfo 	 = NULL;

	pErrorParam = (TpEvtPdecErrorParam *)_param;
	pDecInfo	= (AUD_DECODER_INFO_T *)_cbParam;
	allocDev	= pDecInfo->ui32AllocDev;

	// Print For Debug
	if(_paramLen != sizeof(TpEvtPdecErrorParam))
	{
		AUD_KDRV_ERROR("TP Error : Param Length Error[Expected:%d][Input:%d]\n", sizeof(TpEvtPdecErrorParam), _paramLen);
		return RET_ERROR;
	}

	if ( pDecInfo->ui32AllocDev < AUD_DEV_DEC0 || pDecInfo->ui32AllocDev > AUD_DEV_DEC1)
	{
		AUD_KDRV_ERROR("Check CB ui32AllocDev [%d][%x]\n",pDecInfo->ui32AllocDev,pDecInfo->ui32AllocDev  );
		return RET_ERROR;
	}

	if(pErrorParam->error_type == 1) // fatal error
	{
		AUDIO_StopDecoder(pDecInfo->ui32AllocDev);
		AUDIO_FlushDecoder(pDecInfo->ui32AllocDev);
		AUDIO_InitDecoder(pDecInfo->ui32AllocDev);
		AUDIO_StartDecoder(pDecInfo->ui32AllocDev);
	}

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Set a audio GET event type for next event.
	gAudGetEvent[allocDev].allocDev  = allocDev;
	gAudGetEvent[allocDev].eventMsg |= LX_AUD_EVENT_DEC_ERROR;

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	//Wake up poll event if allocated device and event message is set.
	if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
	  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_DEC_ERROR) )
	{
		wake_up_interruptible_all(&gAudPollWaitQueue);
		AUD_KDRV_DEBUG("TP Error(%d) : LX_AUD_EVENT_DEC_ERROR\n", allocDev);
	}

	AUD_KDRV_DEBUG("TP Error(%d) : Type(%d), Err(%d)\n", allocDev, pErrorParam->media_type, pErrorParam->error_type);
	return RET_OK;
}

/**
 * callback function to update decoded status.
 * @see		_AUDIO_RegisterDecoderEvent().
 */
static SINT32 _AUDIO_DecStatusCb(void *_param, int _paramLen, void *_cbParam)
{
	DecEvtDecIndexParam	*pDecIndexParam;
	AUD_DECODER_INFO_T 	*pDecInfo = NULL;

	pDecIndexParam = (DecEvtDecIndexParam *)_param;
	pDecInfo   = (AUD_DECODER_INFO_T *)_cbParam;

	if(_paramLen != sizeof(DecEvtDecIndexParam))
	{
		AUD_KDRV_ERROR("Dec Index Param : Param Length Error[Expected:%d][Input:%d]\n", sizeof(DecEvtDecIndexParam), _paramLen);
		return RET_ERROR;
	}

	//Copy a additional decoded info.
	pDecInfo->decodedStatus.ui32DecodedIndex = pDecIndexParam->index;
	pDecInfo->decodedStatus.ui64Timestamp 	 = pDecInfo->ui64Timestamp[pDecIndexParam->index];

	// Print For Debug
		AUD_KDRV_DEBUG("Dec Index : Idx(%5d), Ts(%10d)\n", pDecIndexParam->index, pDecIndexParam->timestamp);
	return RET_OK;
}

/**
 * callback function to update decoded end.
 * @see		_AUDIO_RegisterDecoderEvent().
 */
static SINT32 _AUDIO_DecodedEndCb(void *_param, int	_paramLen, void *_cbParam)
{
	AUD_DECODER_INFO_T 	*pDecInfo = NULL;

	pDecInfo = (AUD_DECODER_INFO_T *)_cbParam;

	AUD_KDRV_DEBUG("Dec(%d) Decoded End\n", pDecInfo->ui32AllocDev);
	return RET_OK;
}

/**
 * Register Notification.
 * @param 	pDecInfo		[in] decoder information.
 * @param 	pFuncImcNoti	[in] pointer to callback function.
 * @param 	allocMod		[in] allocated module.
 * @param 	event			[in] event.
 * @return 	void.
 * @see		_AUDIO_RegisterDecoderNoti().
 */
static void _AUDIO_RegisterDecoderNoti(AUD_DECODER_INFO_T* pDecInfo, PFN_ImcNoti pFuncImcNoti, UINT32 allocMod,	\
									   UINT32 event, IMC_ACTION_REPEAT_TYPE repeatType, SINT32 notiLevel)
{
	UINT32							actionID;
	AUD_EVENT_T						*pDecEvent 		= NULL;
	ImcActionParameter 				actionParam;

	if(pDecInfo->ui32EventNum >= AUD_EVENT_NUM)
	{
		AUD_KDRV_ERROR("DecEventNum(%d) is over AUD_EVENT_NUM. \n", pDecInfo->ui32EventNum);
		return;
	}

	actionParam.actionType = IMC_ACTION_GET_CALLBACK;
	actionParam.repeatType = repeatType;
	actionParam.target = ADEC_MODULE_MAN_ARM;
	actionParam.actionParam.notiParam.noti = (PFN_ImcNoti)pFuncImcNoti;
	actionParam.actionParam.notiParam.param = pDecInfo;
	actionParam.actionParam.notiParam.level = notiLevel;
	IMC_RegisterEvent(IMC_GetLocalImc(0), event, allocMod, &actionID, &actionParam);

	//if(repeatType != IMC_ACTION_ONCE)
	{
		pDecEvent = &pDecInfo->decEvent[pDecInfo->ui32EventNum];
		pDecEvent->event = event;
		pDecEvent->actionID = actionID;
		pDecEvent->moduleID = allocMod;
		pDecInfo->ui32EventNum++;
	}

	AUD_KDRV_PRINT("%s [0x%x 0x%x, 0x%x] \n", __F__, event, actionID, allocMod);
	return;
}

/**
 * Register Event.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @return 	void.
 * @see		AUDIO_SetDecoderParam().
 */
static void _AUDIO_RegisterDecoderEvent(UINT32 allocDev)
{
	SINT32	decIndex	 = 0;
	UINT32	allocMod_Dec = ADEC_MODULE_NO_MOD;

	AUD_DECODER_INFO_T		*pDecInfo = NULL;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return;
	}

	pDecInfo = &_gDecoderInfo[decIndex];

	// Decoder Modules are needed to initialize
	allocMod_Dec = AUDIO_GetModule(allocDev, LX_AUD_DEC);
	if(allocMod_Dec != ADEC_MODULE_NO_MOD)
	{
		_AUDIO_RegisterDecoderNoti(pDecInfo, (PFN_ImcNoti)_AUDIO_DecodedInfoCb, allocMod_Dec, DEC_EVT_ES_DEC_INFO, IMC_ACTION_REPEAT, 1);
		_AUDIO_RegisterDecoderNoti(pDecInfo, (PFN_ImcNoti)_AUDIO_DecErrorCb, allocMod_Dec, DEC_EVT_DEC_ERROR, IMC_ACTION_REPEAT, 1);

		if((pDecInfo->decParam.input == LX_AUD_INPUT_TP0) || (pDecInfo->decParam.input == LX_AUD_INPUT_TP1))
		{
			_AUDIO_RegisterDecoderNoti(pDecInfo, (PFN_ImcNoti)_AUDIO_DecIsDecodableCb, allocMod_Dec, DEC_EVT_ES_EXIST_INFO, IMC_ACTION_REPEAT, 1);
		}
		else if(pDecInfo->decParam.input == LX_AUD_INPUT_SYSTEM)
		{
			_AUDIO_RegisterDecoderNoti(pDecInfo, (PFN_ImcNoti)_AUDIO_DecStatusCb, allocMod_Dec, DEC_EVT_DECODED_INDEX, IMC_ACTION_REPEAT, 100);
			_AUDIO_RegisterDecoderNoti(pDecInfo, (PFN_ImcNoti)_AUDIO_DecodedEndCb, allocMod_Dec, DEC_EVT_DECODED_END, IMC_ACTION_ONCE, 1);
		}
	}

	if(pDecInfo->decParam.input == LX_AUD_INPUT_TP0)
	{
		_AUDIO_RegisterDecoderNoti(pDecInfo, (PFN_ImcNoti)_AUDIO_TpErrorCb, LX_AUD_TP_IN0, TP_EVT_PDEC_ERROR, IMC_ACTION_REPEAT, 1);
	}
	else if(pDecInfo->decParam.input == LX_AUD_INPUT_TP1)
	{
		_AUDIO_RegisterDecoderNoti(pDecInfo, (PFN_ImcNoti)_AUDIO_TpErrorCb, LX_AUD_TP_IN1, TP_EVT_PDEC_ERROR, IMC_ACTION_REPEAT, 1);
	}

	return;
}

/**
 * Init Decoder.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		_AUDIO_DecErrorCb().
 */
static SINT32 AUDIO_InitDecoder(UINT32 allocDev)
{
	SINT32							retVal = RET_OK;
	UINT32							allocMod_Dec;

	//Get Decoder Module
	allocMod_Dec = AUDIO_HasThisModuleType(allocDev, LX_AUD_DEC);

	//Send a IMC command - INIT
	retVal = AUDIO_IMC_SendCmd(ADEC_CMD_INIT, allocMod_Dec);

	return retVal;
}

/**
 * Start Decoder.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder(), KDRV_AUDIO_RestartDecoder().
 */
static SINT32 AUDIO_StartDecoder(UINT32 allocDev)
{
	SINT32							retVal = RET_OK;
	UINT32							allocModNum;
	LX_AUD_MOD_T					*pOwnMods;
	UINT32							i;
	LX_AUD_ALLOC_FREE_INFO_T *		inputMOD = NULL;

	if(allocDev < AUD_DEV_DEC0 || allocDev > AUD_DEV_DEC1)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}
	//Send a IMC command - START
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if( pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX )
		{
			if((UINT32)(pOwnMods[i].mod)  >= (UINT32)ADEC_MODULE_TP_IN_0 && (UINT32)(pOwnMods[i].mod)  <= (UINT32)ADEC_MODULE_ADC_IN)
			{
				inputMOD = AUDIO_GetAllocModInfo(pOwnMods[i].mod);

				if(inputMOD->used && inputMOD->subUsed && g_DuringReset !=1)
				{
					AUD_KDRV_RM("Send START CMD is skipped [%s] \n",allocMod_Str[pOwnMods[i].mod]);
				}
				else
				{
					retVal = AUDIO_IMC_SendCmd(ADEC_CMD_START, pOwnMods[i].mod);
					AUD_KDRV_RM("Send START CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
				}
			}
			else
			{
				//Send a IMC command - START
				retVal = AUDIO_IMC_SendCmd(ADEC_CMD_START, pOwnMods[i].mod);
				AUD_KDRV_RM("Send START CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
			}
		}
	}

	return retVal;
}

/**
 * Stop Decoder.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder(), KDRV_AUDIO_ResetDecoder().
 */
static SINT32 AUDIO_StopDecoder(UINT32 allocDev)
{
	SINT32							retVal = RET_OK;
	UINT32							allocModNum;
	UINT32							i = 0;
	LX_AUD_MOD_T					*pOwnMods;
	LX_AUD_ALLOC_FREE_INFO_T *		inputMOD = NULL;

	if(allocDev < AUD_DEV_DEC0 || allocDev > AUD_DEV_DEC1)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}
	//Send a IMC command - STOP
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if(pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX)
		{
			if((UINT32)(pOwnMods[i].mod) >= (UINT32)ADEC_MODULE_TP_IN_0 && (UINT32)(pOwnMods[i].mod) <= (UINT32)ADEC_MODULE_ADC_IN)
			{
				inputMOD = AUDIO_GetAllocModInfo(pOwnMods[i].mod);

				if(inputMOD->used && inputMOD->subUsed && g_DuringReset !=1)
				{
					AUD_KDRV_RM("Send STOP CMD is skipped [%s] \n",allocMod_Str[pOwnMods[i].mod]);
				}
				else
				{
					retVal = AUDIO_IMC_SendCmd(ADEC_CMD_STOP, pOwnMods[i].mod);
					AUD_KDRV_RM("Send STOP CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
				}
			}
			else
			{
				retVal = AUDIO_IMC_SendCmd(ADEC_CMD_STOP, pOwnMods[i].mod);
				AUD_KDRV_RM("Send STOP CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
			}
		}
	}

	return RET_OK;
}

/**
 * Flush Decoder.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder(), KDRV_AUDIO_ResetDecoder().
 */
static SINT32 AUDIO_FlushDecoder(UINT32 allocDev)
{
	SINT32							retVal = RET_OK;
	UINT32							allocModNum;
	UINT32							i = 0;
	ImcCmdFlushParam				flushParam;
	LX_AUD_MOD_T					*pOwnMods;
	LX_AUD_ALLOC_FREE_INFO_T *		inputMOD = NULL;

	memset(&flushParam, 0, sizeof(ImcCmdFlushParam));
	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);

	if(allocDev < AUD_DEV_DEC0 || allocDev > AUD_DEV_DEC1)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}
	//Send a IMC command - FLUSH
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for(i = 0; i < allocModNum; i++)
	{
		if(pOwnMods[i].mod < (LX_AUD_ALLOC_MOD_T)ADEC_MODULE_MAX)
		{
			if((UINT32)(pOwnMods[i].mod) >= (UINT32)ADEC_MODULE_TP_IN_0 && (UINT32)(pOwnMods[i].mod) <= (UINT32)ADEC_MODULE_ADC_IN)
			{
				inputMOD = AUDIO_GetAllocModInfo(pOwnMods[i].mod);

				if(inputMOD->used && inputMOD->subUsed && g_DuringReset !=1)
				{
					AUD_KDRV_RM("Send FLUSH CMD is skipped [%s] \n",allocMod_Str[pOwnMods[i].mod]);
				}
				else
				{
					retVal |= AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, pOwnMods[i].mod, sizeof(ImcCmdFlushParam), &flushParam);
					AUD_KDRV_RM("Send FLUSH CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
				}
			}
			else
			{
				retVal |= AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, pOwnMods[i].mod, sizeof(ImcCmdFlushParam), &flushParam);
				AUD_KDRV_RM("Send FLUSH CMD [%s] \n",allocMod_Str[pOwnMods[i].mod]);
			}
		}
	}

	return retVal;
}

/**
 * Set a Decoder Output Mode.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	outMode			[in] output mode.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32 AUDIO_SetDecoderOutMode(UINT32 allocDev, LX_AUD_DECODER_OUT_MODE_T outMode)
{
	SINT32		retVal = RET_OK;
	SINT32		decIndex = 0;

	LX_AUD_ALLOC_MOD_T	moduleId = ADEC_MODULE_NOT_DEF;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	moduleId = AUDIO_HasThisModuleType(allocDev, LX_AUD_DEC);
	if(moduleId != ADEC_MODULE_NO_MOD)
	{
		retVal = AUDIO_IMC_SendCmdParam(ADEC_CMD_SET_OUTMODE, moduleId, sizeof(LX_AUD_DECODER_OUT_MODE_T), &outMode);
	}

	_gDecoderInfo[decIndex].decOutMode = outMode;

	AUD_KDRV_PRINT("%s, %d: Output Mode[%d, %d] \n", __F__, __L__, allocDev, outMode);

	return retVal;
}

/**
 * Set decoder parameters.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pDecParam		[in] parameters to set.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder(), KDRV_AUDIO_ResetDecoderParam().
 */
static SINT32 AUDIO_SetDecoderParam(UINT32 allocDev, LX_AUD_DECODER_PARAM_T *pDecParam)
{
	SINT32	decIndex = 0;

	ADEC_MODULE_ID					decoderModule	= ADEC_MODULE_NOT_DEF;
	ADEC_MODULE_ID					inputModule		= ADEC_MODULE_NOT_DEF;

	LX_AUD_DECODER_PARAM_T			*pDecInfoParam	= NULL;

	//Sanity check
	if(pDecParam == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: pDecParam is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	//Get a decoder index
	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{

		AUD_KDRV_ERROR("%s.%d: decoder index(%d:%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex,allocDev );

		return RET_ERROR;
	}

	//Copy a decoder parameter to global value
	pDecInfoParam = &(_gDecoderInfo[decIndex].decParam);
	memcpy(pDecInfoParam, pDecParam, sizeof(LX_AUD_DECODER_PARAM_T));

	// Set a codec parameters for audio decoder module.
	decoderModule = _AUDIO_SetDecoderParam_Codec(allocDev, pDecParam);

	// Set a codec parameters for audio input module.
	inputModule= _AUDIO_SetDecoderParam_Input(allocDev, pDecParam);

	if(decoderModule == ADEC_MODULE_NOT_DEF || inputModule == ADEC_MODULE_NOT_DEF)
	{
		AUD_KDRV_ERROR("%s.%d: decoder(%d) or input(%d) module is invalid!!!\n", __FUNCTION__, __LINE__, decoderModule, inputModule);
		return RET_ERROR;
	}

	//Connect a decoder and input module.
	(void)AUDIO_ConnectTo(inputModule, decoderModule, NO_FORCE, NO_FORCE );

	// Set a clock setting for decoder 0
	if(decIndex == 0)		// TODO: DEC0 인 경우만 설정 - TEMP !!!!!
	{
		LX_AUD_SPDIF_DTO_RATE_T spdifDTORate;

		if(pDecParam->input == LX_AUD_INPUT_SIF)
		{
			(void)MIXED_IP_AUDIO_SetClockSource( LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_CLOCK_ATV, LX_AUD_MASTER_SPDIF_PCM);
		}
		else if(pDecParam->input == LX_AUD_INPUT_HDMI)
		{
			if(pDecParam->codecType != LX_AUD_CODEC_PCM)
				(void)MIXED_IP_AUDIO_SetClockSource( LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_CLOCK_HDMI, LX_AUD_MASTER_SPDIF_ES );
			else
				(void)MIXED_IP_AUDIO_SetClockSource( LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_CLOCK_HDMI, LX_AUD_MASTER_SPDIF_PCM );
		}
		else if(pDecParam->input == LX_AUD_INPUT_ADC)
		{
			(void)MIXED_IP_AUDIO_SetClockSource( LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_CLOCK_ADC, LX_AUD_MASTER_SPDIF_PCM );
		}
		else
		{
			(void)MIXED_IP_AUDIO_SetClockSource( LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_CLOCK_DTV, LX_AUD_MASTER_SPDIF_ES );
		}

		//Set default PCM frequency to 48Khz and notify input sampling frequency to DSP
		(void)MIXED_IP_AUDIO_SetPcmClockRate(LX_AUD_SAMPLING_FREQ_48_KHZ, APLL_DSP_VALUE_12_288MHZ);

		//Set a default SPDIF sampling frequency to 48Khz
		#ifdef USE_DTO_AAD
		spdifDTORate = MIXED_IP_AUDIO_GetDTORate(g_setClockSrc, LX_AUD_SAMPLING_FREQ_48_KHZ, AUD_DTO_AAD);
		(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(LX_AUD_SAMPLING_FREQ_48_KHZ, spdifDTORate, AUD_DTO_AAD);
		#else
		spdifDTORate = MIXED_IP_AUDIO_GetDTORate(g_setClockSrc, LX_AUD_SAMPLING_FREQ_48_KHZ, AUD_DTO_A);
		(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(LX_AUD_SAMPLING_FREQ_48_KHZ, spdifDTORate, AUD_DTO_A);
		#endif
	}

	AUD_KDRV_DEBUG("%s  : Dec %x, Input %d, Codec %d, Freq %d\n", __F__, decIndex, pDecParam->input, pDecParam->codecType, pDecParam->samplingFreq);
	return RET_OK;
}

/**
 * Set decoder mode.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pDecMode		[in] decoder mode.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32 AUDIO_SetDecoderMode(UINT32 allocDev, LX_AUD_DECODER_MODE_T *pDecMode)
{
	SINT32	decIndex = 0;

	decIndex = GET_DEC_INDEX(allocDev);
	if ((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	_gDecoderInfo[decIndex].decMode.drc = pDecMode->drc;
	_gDecoderInfo[decIndex].decMode.downmix	= pDecMode->downmix;
	_gDecoderInfo[decIndex].decMode.aacBypass = pDecMode->aacBypass;
	_gDecoderInfo[decIndex].decMode.tpTimerInterval = pDecMode->tpTimerInterval;
	_gDecoderInfo[decIndex].decMode.bSetAD = pDecMode->bSetAD;
	_gDecoderInfo[decIndex].decMode.bSetSubDec = pDecMode->bSetSubDec;

	AUD_KDRV_PRINT("AUDIO_SetDecoderMode(%d %d %d %d %d %d)\n", _gDecoderInfo[decIndex].decMode.drc, _gDecoderInfo[decIndex].decMode.downmix,	\
														  	    _gDecoderInfo[decIndex].decMode.aacBypass, _gDecoderInfo[decIndex].decMode.tpTimerInterval,	\
														  	    _gDecoderInfo[decIndex].decMode.bSetAD, _gDecoderInfo[decIndex].decMode.bSetSubDec);
	return RET_OK;
}

/**
 * Feed data.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pDecFeed		[in] Feeding Data.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32 AUDIO_FeedDec(UINT32 allocDev, LX_AUD_DECODER_FEED_T *pDecFeed)
{
	int						retVal = 0;
	ADEC_BUF_T				*pWriterStruct = NULL;
	UINT32					ui32FreeAuCount;
	UINT64					ui64TS90kHzTick;
	ADEC_AU_INFO_T			info = {0, };
	LX_AUD_DECODER_FEED_T	decFeedData;
	SINT32					decIndex = 0;

	if (pDecFeed == NULL)
	{
		AUD_KDRV_ERROR("Feed : pDecFeed is NULL !!!\n" );
		return RET_ERROR;
	}

	decIndex = GET_DEC_INDEX(allocDev);
	if ((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	pWriterStruct = _AUDIO_GetDecoderWriteStructure(allocDev);
	if (pWriterStruct == NULL)
	{
		AUD_KDRV_ERROR("Feed : pWriterStruct is NULL !!!\n" );
		return RET_ERROR;
	}

	//Check a repeat number and buffer status to initialize audio buffer
	if(_gDecoderInfo[decIndex].bBufferRepeat == TRUE)
	{
		//buffer init : buffer is not flushed if repeat is set previously.
		pWriterStruct->init(pWriterStruct);

		//Clear a buffer repeat variable.
		_gDecoderInfo[decIndex].bBufferRepeat = FALSE;
	}

	memcpy(&decFeedData, pDecFeed, sizeof(LX_AUD_DECODER_FEED_T));

	if(decFeedData.ui32BufferSize > 0 || decFeedData.statusBuffer == LX_AUD_BUFFER_END)
	{
		AUD_KDRV_PRINT("Feed => Free:%d, Used:%d\n", pWriterStruct->get_free_size(pWriterStruct), pWriterStruct->get_used_size(pWriterStruct));

		/* Compute free au count */
		ui32FreeAuCount = pWriterStruct->get_max_au(pWriterStruct) - pWriterStruct->get_au_cnt(pWriterStruct);

		/* Check buffer overflow and AUI overflow */
		if( (pWriterStruct->get_free_size(pWriterStruct) >=  decFeedData.ui32BufferSize) &&(ui32FreeAuCount > 1) )
		{
			if (decFeedData.ui32BufferSize > 0)
			{
				ui64TS90kHzTick = decFeedData.ui64TimeStamp;
				if(ui64TS90kHzTick != 0xFFFFFFFFFFFFFFFFULL)
				{
					ui64TS90kHzTick *= 9;

					do_div(ui64TS90kHzTick, 100000);	// = Xns * 90 000 / 1 000 000 000
				}

				//Set NEW AUI info.
				info.size			= (UINT64)decFeedData.ui32BufferSize;
				info.timestamp		= (UINT32)(ui64TS90kHzTick) & 0x0FFFFFFF;	//28 bit
				info.gstc			= 0;
				info.index			= _gDecoderInfo[decIndex].decodedStatus.ui32FeededIndex;
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
			    retVal = pWriterStruct->write_data(decFeedData.pBuffer, decFeedData.ui32BufferSize, pWriterStruct);
				if(retVal != RET_OK)
				{
					AUD_KDRV_ERROR("Feed => write_data(ret = %d, cnt = %d, free = %d)!!!\n",	\
								retVal, pWriterStruct->get_au_cnt(pWriterStruct), pWriterStruct->get_free_size(pWriterStruct));
					return RET_ERROR;
				}
			}

			//Check buffer status
			if(decFeedData.statusBuffer == LX_AUD_BUFFER_END)
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
				if(decFeedData.ui32RepeatNumber > 1)
				{
					_gDecoderInfo[decIndex].bBufferRepeat = TRUE;

					(void)pWriterStruct->set_repeat(decFeedData.ui32RepeatNumber - 1, pWriterStruct);
				}
			}

			_gDecoderInfo[decIndex].ui64Timestamp[_gDecoderInfo[decIndex].decodedStatus.ui32FeededIndex] = decFeedData.ui64TimeStamp;
			_gDecoderInfo[decIndex].decodedStatus.ui32FeededIndex++;
			if(_gDecoderInfo[decIndex].decodedStatus.ui32FeededIndex == CPB_AUI_INDEX_COUNT)
				_gDecoderInfo[decIndex].decodedStatus.ui32FeededIndex = 0;

			_gDecoderInfo[decIndex].decodedStatus.ui32FeededCount++;
		}
		else
		{
#ifndef IC_CERTIFICATION
			AUD_KDRV_DEBUG("Feed => free = %d, count = %d!!!\n", 	\
							pWriterStruct->get_free_size(pWriterStruct), pWriterStruct->get_au_cnt(pWriterStruct));
#else
			AUD_KDRV_DEBUG_TMP("Feed => free = %d, count = %d!!!\n", 	\
								pWriterStruct->get_free_size(pWriterStruct), pWriterStruct->get_au_cnt(pWriterStruct));
#endif
			retVal = RET_ERROR;
		}
	}
	else
	{
		AUD_KDRV_ERROR("Feed => decFeedData.ui32BufferSize = %u!!!\n", decFeedData.ui32BufferSize);
		retVal = RET_ERROR;
	}

	AUD_KDRV_PRINT("%s.%d: [AUD_DEC_IOW_FEED] bufSize=%u, bufStatus=%d, TS=%llu\n", __F__, __L__, decFeedData.ui32BufferSize, decFeedData.statusBuffer, decFeedData.ui64TimeStamp);

	return retVal;
}

/**
 * Get decodable information.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pIsDecodable	[in] is input stream decodable or not.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32 AUDIO_IsDecodable(UINT32 allocDev, UINT32 *pIsDecodable)
{
	SINT32							decIndex = 0;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	*pIsDecodable = _gDecoderInfo[decIndex].decIsDecodable;

	AUD_KDRV_PRINT("AUDIO_IsEsExist(%d %d)\n", decIndex, *pIsDecodable);

	return RET_OK;
}

/**
 * Get decoded element stream information.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pDecodedInfo	[in] decoded es information.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32 AUDIO_GetDecodedInfo(UINT32 allocDev, LX_AUD_DECODED_INFO_T *pDecodedInfo)
{
	SINT32		decIndex = 0;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	memcpy(pDecodedInfo, &(_gDecoderInfo[decIndex].decodedInfo), sizeof(LX_AUD_DECODED_INFO_T));

	AUD_KDRV_PRINT("AUDIO_GetDecodedInfo(%d)\n", decIndex);
	return RET_OK;
}

/**
 * Get decoded status.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	pDecodedStatus	[in] decoded status.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32 AUDIO_GetDecodedStatus(UINT32 allocDev, LX_AUD_DECODED_STATUS_T *pDecodedStatus)
{
	SINT32					decIndex = 0;
	ADEC_BUF_T				*pWriterStruct = NULL;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	if(_gDecoderInfo[decIndex].decParam.input == LX_AUD_INPUT_SYSTEM)
	{
		pWriterStruct = _AUDIO_GetDecoderWriteStructure(allocDev);
		if (pWriterStruct == NULL)
		{
			AUD_KDRV_ERROR("Feed : pWriterStruct is NULL !!!\n" );
			return RET_ERROR;
		}

		//Get a buffer info. from buffer interface
		_gDecoderInfo[decIndex].decodedStatus.ui32MaxMemSize = pWriterStruct->get_max_size(pWriterStruct);
		_gDecoderInfo[decIndex].decodedStatus.ui32FreeMemSize = pWriterStruct->get_free_size(pWriterStruct);
		_gDecoderInfo[decIndex].decodedStatus.ui32MaxAuiSize = pWriterStruct->get_max_au(pWriterStruct);
		_gDecoderInfo[decIndex].decodedStatus.ui32FreeAuiSize = pWriterStruct->get_max_au(pWriterStruct) - pWriterStruct->get_au_cnt(pWriterStruct) - 1;
	}
	else		//if(_gDecoderInfo[decIndex].decParam.input == LX_AUD_INPUT_TP0 || _gDecoderInfo[decIndex].decParam.input == LX_AUD_INPUT_TP1)
	{
		// TO_DO
	}

	memcpy(pDecodedStatus, &(_gDecoderInfo[decIndex].decodedStatus), sizeof(LX_AUD_DECODED_STATUS_T));

	AUD_KDRV_PRINT("AUDIO_GetDecodedStatus(%d)\n", decIndex);

	return RET_OK;
}


/**
 * Close decoder.
 *
 * @param 	audDev		[in] a allocated decoder device information.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32	AUDIO_CloseDecoder(AUD_DEVICE_T* audDev)
{
	UINT32		devType;
	UINT32		i = 0;
	SINT32		retVal = 0;
	SINT32		decIndex = 0;

	LX_AUD_ALLOC_FREE_INFO_T		CloseInfo;
	LX_AUD_ALLOC_MOD_T				decoderModule = ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_DEV_T				allocDev;

	AUD_EVENT_T						*pDecEvent = NULL;

	/* Set device */
	devType = audDev->devType;
	allocDev = audDev->allocDev;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	if(_gDecoderInfo[decIndex].bClosed == TRUE)
	{
		AUD_KDRV_ERROR(" decIndex[%d] is already closed. \n", decIndex);
		return RET_OK;
	}

	AUDIO_DisconnectAllInDev(allocDev);

	decoderModule = AUDIO_HasThisModuleType(allocDev, LX_AUD_DEC);

	if(decoderModule != ADEC_MODULE_NO_MOD)
	{
		AUDIO_Destory(decoderModule);
	}
	else
	{
		AUD_KDRV_RMD("No docoder module  to destory\n");
	}

	CloseInfo.devType = devType;
	CloseInfo.allocDev = allocDev;
	retVal = AUDIO_FreeDev(&CloseInfo);
	if(retVal == AUD_NO_DEV )
	{
		AUD_KDRV_RMD(" All %s is already freed \n",devTypeStr[devType]);
	}
	else
	{
		AUD_KDRV_RM("%s is closed[Freed:%s]\n",devTypeStr[devType],(char *)allocDev_Str[retVal] );
	}

	for(i = 0; i < _gDecoderInfo[decIndex].ui32EventNum; i++)
	{
		pDecEvent = &(_gDecoderInfo[decIndex].decEvent[i]);
		IMC_CancelEvent(IMC_GetLocalImc(0), pDecEvent->event , pDecEvent->moduleID, pDecEvent->actionID);
		AUD_KDRV_PRINT("%s: IMC_CancelEvent(%d) [0x%x 0x%x, 0x%x] \n", __FUNCTION__, decIndex, pDecEvent->event, pDecEvent->actionID, pDecEvent->moduleID);
	}

	//Clear a decoder resource.
	_gDecoderInfo[decIndex].ui32EventNum = 0;
	_gDecoderInfo[decIndex].bClosed 	 = TRUE;
	_gDecoderInfo[decIndex].ui32AllocDev = 0;
	_gDecoderInfo[decIndex].bIsDualDec   = FALSE;

	AUD_KDRV_PRINT("%s : Close Device %d.\n", __F__, allocDev);
	return RET_OK;
}

/**
 * Set decoder parameters for certification.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	decCertiParam	[in] parameters to set.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_IoctlDecoder().
 */
static SINT32 AUDIO_SetDecoderCertiParam(UINT32 allocDev, UINT32 decCertiParam)
{
#ifdef IC_CERTIFICATION
	SINT32							decIndex		= 0;
	LX_AUD_DECODER_PARAM_T			*pDecInfoParam	= NULL;
	LX_AUD_ALLOC_MOD_T				decoderModule	= ADEC_MODULE_NOT_DEF;

	decIndex = GET_DEC_INDEX(allocDev);
	if((decIndex < 0) || (decIndex >= DEV_DEC_NUM))
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return RET_ERROR;
	}

	decoderModule = AUDIO_HasThisModuleType(allocDev, LX_AUD_DEC);
	if(decoderModule == ADEC_MODULE_NO_MOD)
	{
		AUD_KDRV_ERROR("%s.%d: audio module is Unknown\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	pDecInfoParam = &(_gDecoderInfo[decIndex].decParam);

	if(pDecInfoParam->codecType == LX_AUD_CODEC_AC3)
	{
		DdcCmdSetParam ddcParam;

		ddcParam.drc_mode = 0;
		ddcParam.downmix_mode = 1;
		ddcParam.isDualDec = 0;
		ddcParam.certi_param = decCertiParam;

		AUDIO_IMC_SendCmdParam(DDC_CMD_SET_PARAM, decoderModule, sizeof(DdcCmdSetParam), &ddcParam);
	}
	else if(pDecInfoParam->codecType == LX_AUD_CODEC_AAC)
	{
		DdtCmdSetParam ddtParam;

		ddtParam.drc_mode = 0;
		ddtParam.downmix_mode = 1;
		ddtParam.isDualDec = 0;
		ddtParam.iec_fmt = 0;
		ddtParam.certi_param = decCertiParam;

		AUDIO_IMC_SendCmdParam(DDT_CMD_SET_PARAM, decoderModule, sizeof(DdcCmdSetParam), &ddtParam);
	}
	else if(pDecInfoParam->codecType == LX_AUD_CODEC_DTS)
	{
		DtsCmdSetParam dtsParam;

		dtsParam.certi_param = decCertiParam;

		AUDIO_IMC_SendCmdParam(DTS_CMD_SET_PARAM, decoderModule, sizeof(DtsCmdSetParam), &dtsParam);
	}

	AUD_KDRV_ERROR("%s.%d: certi_param : %x.\n", __FUNCTION__, __LINE__, decCertiParam);
#endif

	return RET_OK;
}


/**
 * Reset decoder device.
 *
 * @see		AUDIO_Restart().
 */
void	KDRV_AUDIO_ResetDecoder(void)
{
	LX_AUD_MOD_T				*pOwnMods;
	LX_AUD_ALLOC_MOD_T			decoderModule = ADEC_MODULE_NO_MOD;
	AUD_EVENT_T					*pDecEvent = NULL;
	UINT32						allocDev;
	UINT32						i = 0, j = 0;
	UINT32						allocModNum;
   	LX_AUD_ALLOC_FREE_INFO_T * freeDEV;

	for(i = 0; i < DEV_DEC_NUM; i++)
	{
		if(_gDecoderInfo[i].decParam.input != LX_AUD_INPUT_SYSTEM)
		{
			allocDev = _gDecoderInfo[i].ui32AllocDev;
			if(allocDev == 0)
				continue;

			_gDecoderInfo[i].bResetting = TRUE;

			if(allocDev < AUD_DEV_DEC0 || allocDev > AUD_DEV_DEC1)
			{
				AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
			}

			AUDIO_StopDecoder(allocDev);
			AUDIO_FlushDecoder(allocDev);

			AUDIO_DisconnectAllInDev(allocDev);

			decoderModule = AUDIO_HasThisModuleType(allocDev, LX_AUD_DEC);
			if(decoderModule != ADEC_MODULE_NO_MOD )
			{
				AUDIO_Destory ( decoderModule );
			}

			//get alloc module info in given device node
			AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

			for(j = 0; j < allocModNum; j++)
			{
				AUDIO_FreeModule (pOwnMods[j].mod,allocDev );
 			}

        	freeDEV = &DevInfo.list[allocDev];
        	freeDEV->headOfDev			= NULL;
        	freeDEV->tailOfDev		= NULL;

			for(j = 0; j < _gDecoderInfo[i].ui32EventNum; j++)
			{
				pDecEvent = &(_gDecoderInfo[i].decEvent[j]);
				IMC_CancelEvent(IMC_GetLocalImc(0), pDecEvent->event , pDecEvent->moduleID, pDecEvent->actionID);
			}

			_gDecoderInfo[i].ui32EventNum = 0;
		}
	}
}

/**
 * Reset decoder parameters.
 *
 * @see		AUDIO_Restart().
 */
void	KDRV_AUDIO_ResetDecoderParam(void)
{
	LX_AUD_DECODER_PARAM_T	*pDecInfoParam = NULL;
	UINT32						allocDev;
	UINT32						i = 0;

	for(i = 0; i < DEV_DEC_NUM; i++)
	{
		if(_gDecoderInfo[i].decParam.input != LX_AUD_INPUT_SYSTEM)
		{
			allocDev = _gDecoderInfo[i].ui32AllocDev;
			if(allocDev == 0)
				continue;

			pDecInfoParam = &(_gDecoderInfo[i].decParam);
			AUDIO_SetDecoderParam(allocDev, pDecInfoParam);
		}
	}
}

/**
 * Restart decoder.
 *
 * @see		AUDIO_Restart().
 */
void	KDRV_AUDIO_RestartDecoder(void)
{
	UINT32						allocDev;
	UINT32						i = 0;

	for(i = 0; i < DEV_DEC_NUM; i++)
	{
		if(_gDecoderInfo[i].decParam.input != LX_AUD_INPUT_SYSTEM)
		{
			allocDev = _gDecoderInfo[i].ui32AllocDev;
			if(allocDev == 0)
				continue;

			AUDIO_StartDecoder(allocDev);

			_gDecoderInfo[i].bResetting = FALSE;
		}
	}
}

/**
 * Get a decoded Information for debug.
 *
 * @see	AUDIO_GetDecodedInfo().
 */
void KDRV_AUDIO_GetDecodedInfoForDebug(LX_AUD_DEBUG_DECODED_INFO_T *pDecInfo)
{
	UINT32	decIndex = pDecInfo->ui32DecoderNum;

	if(decIndex >= DEV_DEC_NUM)
	{
		AUD_KDRV_ERROR("%s.%d: decoder index(%d) is invalid!!!\n", __FUNCTION__, __LINE__, decIndex);
		return;
	}

	//Copy a decoded info. from global saved value from decoder callback info.
	pDecInfo->codecType 		=  _gDecoderInfo[decIndex].decodedInfo.codecType;
	pDecInfo->samplingFreq 		=  _gDecoderInfo[decIndex].decodedInfo.samplingFreq;
	pDecInfo->ui32AvgBitRate 	=  _gDecoderInfo[decIndex].decodedInfo.ui32AvgBitRate;
	pDecInfo->ui32NumOfChannel	=  _gDecoderInfo[decIndex].decodedInfo.ui32NumOfChannel;
	pDecInfo->ui32BitPerSample 	=  _gDecoderInfo[decIndex].decodedInfo.ui32BitPerSample;

	//Copy a decoder info. from global saved value.
	pDecInfo->ui32AllocDev		=  _gDecoderInfo[decIndex].ui32AllocDev;
	pDecInfo->input 			=  _gDecoderInfo[decIndex].decParam.input;
	pDecInfo->ui32IsDecodable 	=  _gDecoderInfo[decIndex].decIsDecodable;
	pDecInfo->ui32ChannelNum 	=  _gDecoderInfo[decIndex].ui32ChannelNum;

	AUD_KDRV_PRINT("KDRV_AUDIO_GetDebugDecodedInfo(%d)\n", decIndex);
	return;
}

/** @} */


