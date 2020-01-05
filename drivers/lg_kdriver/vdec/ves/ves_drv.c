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
*/ 
/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     youngki.lyu@lge.com
 * version    1.0
 * date       2011.02.21
 * note       Additional information.
 *
 * @addtogroup lg115x_ves
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ves_drv.h"

#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>
#include <asm/uaccess.h> // copy_from_user
#include <asm/div64.h> // do_div
#include <linux/delay.h>
#include "vdec_kapi.h"
#include "../mcu/os_adap.h"

#include "ves_cpb.h"
#include "ves_auib.h"
#include "../hal/pdec_hal_api.h"
#include "../hal/top_hal_api.h"
#include "../hal/lq_hal_api.h"
#include "../hal/ipc_reg_api.h"
#include "../vds/vdec_rate.h"

#include "log.h"
logm_define (vdec_ves, log_level_warning);

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
static DEFINE_MUTEX (ves_lock);
/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef enum
{
	DTS_JITTER,
	DTS_SAME,
	DTS_NORMAL,
	DTS_WRAPAROUND,
	DTS_UINT32 = 0x20110725
} E_DTS_DISCONTINUITY_T;

typedef struct
{
	enum
	{
		VES_NULL = 0,
		VES_READY = 10,
		VES_PLAY = 20,
		VES_PAUSE,
	} State;
	struct
	{
		E_VES_SRC_T	eVesSrcCh;
		UINT8		ui8SyncCh;
		void		*priv;
		UINT8		ui8CodecType_Config;
		BOOLEAN		bRingBufferMode;
		BOOLEAN		b512bytesAligned;
		BOOLEAN		bUseGstc;
		VES_BUFFER_UPDATED_T fpBufferUpdated;
		void 		*pBufferUpdatedArg;

		BOOLEAN		bFromTVP;
	} Config;
	struct
	{
		BOOLEAN		bSTCCDiscontinuity;
		UINT32		ui32DTS_Prev;
		UINT32		ui32PushedAui;

		volatile BOOLEAN		bFlushing;
	} Status;
	struct
	{
		UINT32		ui32LogTick;
		UINT32		ui32GSTC_Prev;
		UINT32		ui32UID;
		UINT32           STC_PTS_flag;
		/*
		STC_PTS_flag: 10-PTS, 11-PTS&DTS, 00-neither
		*/
	} Debug;
} S_VDEC_VES_DB_T;

typedef struct
{
	UINT8	ui8VesCh;
	UINT32	ui32au_type;
	UINT32	ui32UserBuf;
	UINT32	ui32UserBufSize;
	BOOLEAN	bIsDTS;
	UINT32	ui32UId;
	UINT64	ui64TimeStamp;
	UINT32	ui32TimeStamp_90kHzTick;
	UINT32	ui32FrameRateRes;
	UINT32	ui32FrameRateDiv;
} S_IPC_MCUWRITE_T;


/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
UINT32	ui32WorkfuncParam = 0x0;
static void _VDEC_ISR_PIC_Detected_workfunc(struct work_struct *data);

DECLARE_WORK( _VDEC_VES_work, _VDEC_ISR_PIC_Detected_workfunc );

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
volatile S_VDEC_VES_DB_T gsVesDrv[VES_NUM_OF_CHANNEL];

struct workqueue_struct *_VDEC_VES_workqueue;
static spinlock_t	stVdecVesSpinlock;

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
static void _VES_PrintStatus(UINT8 ui8VesCh)
{
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return;
	}

	logm_debug(vdec_ves, "[VES%d-%d][DBG] Buf:%d(%d), AUIB Use:%d, CPB Use:%d \n",
								ui8VesCh,
								gsVesDrv[ui8VesCh].State,
								gsVesDrv[ui8VesCh].Config.bRingBufferMode, gsVesDrv[ui8VesCh].Config.b512bytesAligned,
								VES_AUIB_NumActive(ui8VesCh),
								VES_CPB_GetUsedBuffer(ui8VesCh));
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
static BOOLEAN _VES_CheckBelongTo90kTick(UINT32 ui32STC_Start, UINT32 ui32STC_End, UINT32 ui32DTS)
{
	if( ui32STC_Start <= ui32STC_End )
	{
		if( (ui32DTS > ui32STC_Start) &&
			(ui32DTS <= ui32STC_End) )
			return TRUE;
	}
	else
	{
		if( (ui32DTS > ui32STC_Start) ||
			(ui32DTS <= ui32STC_End) )
			return TRUE;
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
static E_DTS_DISCONTINUITY_T _VES_CheckDtsDiscontinuity(UINT8 ui8VesCh, UINT32 ui32DTS)
{
	UINT32		ui32JitterDuration;
	UINT32		ui32JitterBoundary;
	UINT32		ui32NormalDuration;
	UINT32		ui32NormalBoundary;

	UINT32		ui32FrameDuration;
	E_DTS_DISCONTINUITY_T	eDtsDiscontinuity = DTS_UINT32;
	UINT32		ui32DTS_Prev = gsVesDrv[ui8VesCh].Status.ui32DTS_Prev;


	if( ui32DTS_Prev == 0xFFFFFFFF )
		goto _VES_CheckDtsDiscontinuity_Exit;

	ui32FrameDuration = VDEC_RATE_GetFrameRateDuration(gsVesDrv[ui8VesCh].Config.ui8SyncCh);
	if( ui32FrameDuration == 0 )
		goto _VES_CheckDtsDiscontinuity_Exit;

	ui32DTS_Prev &= 0x0fffffff;
	ui32DTS &= 0x0fffffff;

	ui32JitterDuration = ui32FrameDuration * VDEC_SPEED_MAX;
	if( ui32DTS_Prev>= ui32JitterDuration )
		ui32JitterBoundary = ui32DTS_Prev - ui32JitterDuration;
	else
		ui32JitterBoundary = ui32DTS_Prev + 0x0FFFFFFF - ui32JitterDuration;

	ui32NormalDuration = ui32FrameDuration * VDEC_SPEED_MAX;
	ui32NormalBoundary = ui32DTS_Prev + ui32NormalDuration;
	ui32NormalBoundary &= 0x0FFFFFFF;

	if( _VES_CheckBelongTo90kTick(ui32JitterBoundary, ui32DTS_Prev, ui32DTS) == TRUE )
	{
		if( ui32DTS_Prev == ui32DTS )
		{
			eDtsDiscontinuity = DTS_SAME;
			logm_debug(vdec_ves, "[VES%d-%d][Warning] S/W DTS Discontinuity - Same DTS(0x%X), Use: %d, FrameDuration:0x%X\n", ui8VesCh, gsVesDrv[ui8VesCh].State, ui32DTS, VES_AUIB_NumActive(ui8VesCh), ui32FrameDuration );
		}
		else
		{
			eDtsDiscontinuity = DTS_JITTER;
			logm_debug(vdec_ves, "[VES%d-%d][Warning] S/W DTS Discontinuity - Jitter DTS(Prev:0x%X, Curr:0x%X), Use: %d, FrameDuration:0x%X\n", ui8VesCh, gsVesDrv[ui8VesCh].State, ui32DTS_Prev, ui32DTS, VES_AUIB_NumActive(ui8VesCh), ui32FrameDuration );
		}
	}
	else if( _VES_CheckBelongTo90kTick(ui32DTS_Prev, ui32NormalBoundary, ui32DTS) == TRUE )
	{
		eDtsDiscontinuity = DTS_NORMAL;
	}
	else
	{
		eDtsDiscontinuity = DTS_WRAPAROUND;
		logm_noti(vdec_ves, "[VES%d-%d][Warning] S/W DTS Discontinuity - Wrap Around DTS(Prev:0x%X, Curr:0x%X), Use: %d, FrameDuration:0x%X\n", ui8VesCh, gsVesDrv[ui8VesCh].State, ui32DTS_Prev, ui32DTS, VES_AUIB_NumActive(ui8VesCh), ui32FrameDuration );
	}

_VES_CheckDtsDiscontinuity_Exit:

	gsVesDrv[ui8VesCh].Status.ui32DTS_Prev = ui32DTS;

	return eDtsDiscontinuity;
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
static UINT8 _VES_GetTranslateCodecType(LX_VDEC_CODEC_T codec)
{
	switch (codec)
	{
	default:
		logm_error (vdec_ves, "unknown codec type %d\n", codec);
	case LX_VDEC_CODEC_H264_HP:
	case LX_VDEC_CODEC_H264_MVC:
		return 0;

	case LX_VDEC_CODEC_VC1_RCV_V1:
	case LX_VDEC_CODEC_VC1_RCV_V2:
	case LX_VDEC_CODEC_VC1_ES:
		return 1;

	case LX_VDEC_CODEC_MPEG2_HP:
		return 2;

	case LX_VDEC_CODEC_MPEG4_ASP:
	case LX_VDEC_CODEC_XVID:
	case LX_VDEC_CODEC_DIVX3:
	case LX_VDEC_CODEC_DIVX4:
	case LX_VDEC_CODEC_DIVX5:
		return 3;

	case LX_VDEC_CODEC_RVX:
		return 4;

	case LX_VDEC_CODEC_AVS:
		return 5;

	//case LX_VDEC_CODEC_JPEG:
	//	return 8;
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
static void _PDEC_HW_Reset(UINT8 ui8VesCh, UINT8 ui8CodecType_Config, E_VES_SRC_T eVesSrcCh)
{
	BOOLEAN		bIsIntrEnable;

	if( eVesSrcCh >= VES_SRC_BUFF0 )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number \n", ui8VesCh);
		return;
	}

	logm_info(vdec_ves, "[VES%d][DBG] \n", ui8VesCh);

#if defined(USE_MCU_FOR_VDEC_VES)
	bIsIntrEnable = TOP_HAL_IsInterIntrEnable(PDEC0_AU_DETECT+ui8VesCh);
#else
	bIsIntrEnable = TOP_HAL_IsExtIntrEnable(PDEC0_AU_DETECT+ui8VesCh);
#endif
	if( bIsIntrEnable == TRUE )
	{
#if defined(USE_MCU_FOR_VDEC_VES)
		TOP_HAL_DisableInterIntr(PDEC0_AU_DETECT+ui8VesCh);
		TOP_HAL_ClearInterIntr(PDEC0_AU_DETECT+ui8VesCh);
#else
		TOP_HAL_DisableExtIntr(PDEC0_AU_DETECT+ui8VesCh);
		TOP_HAL_ClearExtIntr(PDEC0_AU_DETECT+ui8VesCh);
#endif
	}

	TOP_HAL_DisablePdecInput(ui8VesCh);
	PDEC_HAL_Disable(ui8VesCh);

	PDEC_HAL_Reset(ui8VesCh);

	VES_AUIB_Reset(ui8VesCh);
	VES_CPB_Reset(ui8VesCh);

	switch( gsVesDrv[ui8VesCh].State )
	{
	case VES_PLAY :
	case VES_PAUSE :
		if( bIsIntrEnable == FALSE )
		{
			logm_error(vdec_ves, "[VES%d-%d][Err] Disabled PIC_Detected Interrupt \n", ui8VesCh, gsVesDrv[ui8VesCh].State);
		}
	case VES_READY :
		PDEC_HAL_SetVideoStandard(ui8VesCh, _VES_GetTranslateCodecType(ui8CodecType_Config));

		TOP_HAL_EnablePdecInput(ui8VesCh);
		TOP_HAL_SetPdecInputSelection(ui8VesCh, eVesSrcCh);

#if defined(USE_MCU_FOR_VDEC_VES)
		TOP_HAL_ClearInterIntr(PDEC0_AU_DETECT+ui8VesCh);
		TOP_HAL_EnableInterIntr(PDEC0_AU_DETECT+ui8VesCh);
#else
		TOP_HAL_ClearExtIntr(PDEC0_AU_DETECT+ui8VesCh);
		TOP_HAL_EnableExtIntr(PDEC0_AU_DETECT+ui8VesCh);
#endif
		break;
	case VES_NULL :
		break;
	default :
		logm_error(vdec_ves, "[VES%d-%d][Err] Current State \n", ui8VesCh, gsVesDrv[ui8VesCh].State);
	}

	switch( gsVesDrv[ui8VesCh].State )
	{
	case VES_READY :
		break;
	case VES_PLAY :
		PDEC_HAL_Enable(ui8VesCh);
		break;
	case VES_PAUSE :
		PDEC_HAL_Disable(ui8VesCh);
		break;
	case VES_NULL :
		break;
	default :
		logm_error(vdec_ves, "[VES%d-%d][Err] Current State \n", ui8VesCh, gsVesDrv[ui8VesCh].State);
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
void VES_Init()
{
	UINT8	ui8VesCh;
	
	_VDEC_VES_workqueue = create_workqueue("VDEC_VES");
	spin_lock_init(&stVdecVesSpinlock);

	for( ui8VesCh = 0; ui8VesCh < VES_NUM_OF_CHANNEL; ui8VesCh++ )
	{
		gsVesDrv[ui8VesCh].State = VES_NULL;

		if( ui8VesCh < PDEC_NUM_OF_CHANNEL )
		{
			TOP_HAL_DisablePdecInput(ui8VesCh);
			PDEC_HAL_Disable(ui8VesCh);
		}
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
UINT8 VES_Open( E_VES_SRC_T eVesSrcCh,
		UINT8 ui8CodecType_Config,
		UINT32 ui32CpbBufAddr, UINT32 ui32CpbBufSize,
		BOOLEAN bUseGstc,
		UINT32 ui32DecodeOffset_bytes,
		VES_BUFFER_UPDATED_T updated, void *updated_arg)
{
	UINT8		ui8VesCh = 0xFF;
	BOOLEAN		bIsHwPath;
	BOOLEAN		bFromTVP = FALSE;

	mutex_lock (&ves_lock);

	if( eVesSrcCh == VES_SRC_TVP )
	{
		ui8VesCh = 2;
		bFromTVP = TRUE;
		bIsHwPath = TRUE;

		if( gsVesDrv[ui8VesCh].State != VES_NULL )
		{
			logm_error(vdec_ves, "[VES][Err] Not Enough Channel - VES Src:%d\n", eVesSrcCh);
			for( ui8VesCh = 0; ui8VesCh < VES_NUM_OF_CHANNEL; ui8VesCh++ )
				logm_error(vdec_ves, "[VES%d][Err] State: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State );

			mutex_unlock (&ves_lock);

			return 0xFF;
		}

		logm_info(vdec_ves, "[VES%d-%d][DBG] Trust Video Path \n", ui8VesCh, gsVesDrv[ui8VesCh].State);
	}
	else
	{
		for( ui8VesCh = 0; ui8VesCh < VES_NUM_OF_CHANNEL; ui8VesCh++ )
		{
			if( gsVesDrv[ui8VesCh].State == VES_NULL )
				break;
		}
		if( ui8VesCh == VES_NUM_OF_CHANNEL )
		{
			logm_error(vdec_ves, "[VES][Err] Not Enough Channel - VES Src:%d, \n", eVesSrcCh);
			for( ui8VesCh = 0; ui8VesCh < VES_NUM_OF_CHANNEL; ui8VesCh++ )
				logm_error(vdec_ves, "[VES%d][Err] State: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State );

			mutex_unlock (&ves_lock);
			
			return 0xFF;
		}

		bIsHwPath = ( eVesSrcCh <= VES_SRC_SDEC2 ) ? TRUE : FALSE;
	}

	logm_info(vdec_ves, "[VES%d-%d][DBG] Buffer Size: 0x%X, Decoding Offset: 0x%X, UseGstc: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State, ui32CpbBufSize, ui32DecodeOffset_bytes, bUseGstc);

	if( VES_AUIB_Open( ui8VesCh, ui32DecodeOffset_bytes, bIsHwPath, bFromTVP) == FALSE )
	{
		mutex_unlock (&ves_lock);
	
		return 0xFF;
	}
	if( VES_CPB_Open( ui8VesCh, ui32CpbBufAddr, ui32CpbBufSize, bIsHwPath, bFromTVP) == FALSE )
	{
		VES_AUIB_Close(ui8VesCh);

		mutex_unlock (&ves_lock);
		
		return 0xFF;
	}

	gsVesDrv[ui8VesCh].State = VES_READY;
	gsVesDrv[ui8VesCh].Config.eVesSrcCh = eVesSrcCh;
	gsVesDrv[ui8VesCh].Config.ui8CodecType_Config = ui8CodecType_Config;
	gsVesDrv[ui8VesCh].Config.bUseGstc = bUseGstc;
	gsVesDrv[ui8VesCh].Config.bFromTVP = bFromTVP;
	gsVesDrv[ui8VesCh].Config.fpBufferUpdated = updated;
	gsVesDrv[ui8VesCh].Config.pBufferUpdatedArg = updated_arg;
	gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = FALSE;
	gsVesDrv[ui8VesCh].Status.ui32DTS_Prev = 0xFFFFFFFF;
	gsVesDrv[ui8VesCh].Status.ui32PushedAui = 0;
	gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = FALSE;

	gsVesDrv[ui8VesCh].Debug.ui32UID = 0x0;
	gsVesDrv[ui8VesCh].Debug.STC_PTS_flag = 0x0;

	gsVesDrv[ui8VesCh].Debug.ui32LogTick = 0;

	gsVesDrv[ui8VesCh].Status.bFlushing = FALSE;

	if( (bIsHwPath == TRUE) && (bFromTVP == FALSE) )
	{
		_PDEC_HW_Reset(ui8VesCh, ui8CodecType_Config, eVesSrcCh);
	}

	mutex_unlock (&ves_lock);

	return ui8VesCh;
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
BOOLEAN VES_SetOpenParam(UINT8 ui8VesCh, UINT8 ui8SyncCh, void *priv, BOOLEAN bRingBufferMode, BOOLEAN b512bytesAligned) // for File Play
{

	mutex_lock (&ves_lock);

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);

		mutex_unlock (&ves_lock);

		return FALSE;
	}

	if( gsVesDrv[ui8VesCh].State != VES_READY )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel State: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State);

		mutex_unlock (&ves_lock);

		return FALSE;
	}

	gsVesDrv[ui8VesCh].Config.ui8SyncCh = ui8SyncCh;
	gsVesDrv[ui8VesCh].Config.priv = priv;

	if( gsVesDrv[ui8VesCh].Config.eVesSrcCh <= VES_SRC_SDEC2 )
	{
		if( (bRingBufferMode != TRUE) ||(b512bytesAligned != TRUE) )
			logm_error(vdec_ves, "[VES%d-%d][Err] Buffer Mode: %d, 512bytes Aligned: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State, bRingBufferMode, b512bytesAligned);

		gsVesDrv[ui8VesCh].Config.bRingBufferMode = TRUE;
		gsVesDrv[ui8VesCh].Config.b512bytesAligned = TRUE;
	}
	else
	{ // for File Play
		gsVesDrv[ui8VesCh].Config.bRingBufferMode = bRingBufferMode;
		// workaround for boda rollback mode bug in h263,mpeg4
		if(gsVesDrv[ui8VesCh].Config.ui8CodecType_Config == LX_VDEC_CODEC_MPEG4_ASP
			|| gsVesDrv[ui8VesCh].Config.ui8CodecType_Config == LX_VDEC_CODEC_XVID
			|| gsVesDrv[ui8VesCh].Config.ui8CodecType_Config == LX_VDEC_CODEC_DIVX4
			|| gsVesDrv[ui8VesCh].Config.ui8CodecType_Config == LX_VDEC_CODEC_DIVX5)
			gsVesDrv[ui8VesCh].Config.b512bytesAligned = TRUE;
		else gsVesDrv[ui8VesCh].Config.b512bytesAligned = FALSE;
	}
	
	logm_info(vdec_ves, "[VES%d-%d][DBG] Buffer Mode: %d Aligned: %d, LS: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State, bRingBufferMode, b512bytesAligned, ui8SyncCh);

	mutex_unlock (&ves_lock);

	return TRUE;
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
void * VES_GetVdecPriv(UINT8 ui8VesCh)
{
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);
		return NULL;
	}

	return gsVesDrv[ui8VesCh].Config.priv;
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
void VES_Close(UINT8 ui8VesCh)
{
	mutex_lock (&ves_lock);
	
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);

		mutex_unlock (&ves_lock);	

		return;
	}

	logm_info(vdec_ves, "[VES%d-%d][DBG] \n", ui8VesCh, gsVesDrv[ui8VesCh].State);

	if( gsVesDrv[ui8VesCh].Config.eVesSrcCh <= VES_SRC_SDEC2 )
	{
#if defined(USE_MCU_FOR_VDEC_VES)
		TOP_HAL_DisableInterIntr(PDEC0_AU_DETECT+ui8VesCh);
		TOP_HAL_ClearInterIntr(PDEC0_AU_DETECT+ui8VesCh);
#else
		TOP_HAL_DisableExtIntr(PDEC0_AU_DETECT+ui8VesCh);
		TOP_HAL_ClearExtIntr(PDEC0_AU_DETECT+ui8VesCh);
#endif
		TOP_HAL_DisablePdecInput(ui8VesCh);
		PDEC_HAL_Disable(ui8VesCh);
	}
	
	gsVesDrv[ui8VesCh].State = VES_NULL;

	VES_AUIB_Close(ui8VesCh);
	VES_CPB_Close(ui8VesCh);

	gsVesDrv[ui8VesCh].Config.eVesSrcCh = 0xFF;
	gsVesDrv[ui8VesCh].Config.ui8SyncCh = 0xFF;
	gsVesDrv[ui8VesCh].Config.priv = NULL;

	gsVesDrv[ui8VesCh].Debug.ui32UID = 0x0;
	gsVesDrv[ui8VesCh].Debug.STC_PTS_flag = 0x0;

	mutex_unlock (&ves_lock);	

	

//	if( gsVesDrv[ui8VesCh].Config.ui8TeCh <= VDEC_SRC_SDEC2 )
//	{
//		_PDEC_HW_Reset(ui8VesCh, gsVesDrv[ui8VesCh].Config.ui8CodecType_Config, gsVesDrv[ui8VesCh].Config.ui8TeCh);
//	}

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
void VES_Reset(UINT8 ui8VesCh)
{
	mutex_lock (&ves_lock);
	
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);

		mutex_unlock (&ves_lock);

		return;
	}

	logm_info(vdec_ves, "[VES%d-%d][DBG] \n", ui8VesCh, gsVesDrv[ui8VesCh].State);

	gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = FALSE;
	gsVesDrv[ui8VesCh].Status.ui32DTS_Prev = 0xFFFFFFFF;
	gsVesDrv[ui8VesCh].Status.ui32PushedAui = 0;
	gsVesDrv[ui8VesCh].Status.bFlushing = FALSE;

	gsVesDrv[ui8VesCh].Debug.ui32UID = 0x0;
	gsVesDrv[ui8VesCh].Debug.STC_PTS_flag = 0x0;

	if( gsVesDrv[ui8VesCh].Config.eVesSrcCh <= VES_SRC_SDEC2 )
	{
		_PDEC_HW_Reset(ui8VesCh, gsVesDrv[ui8VesCh].Config.ui8CodecType_Config, gsVesDrv[ui8VesCh].Config.eVesSrcCh);
	}
	else
	{
		VES_AUIB_Reset(ui8VesCh);
		VES_CPB_Reset(ui8VesCh);
	}
	
	mutex_unlock (&ves_lock);
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
void VES_Start(UINT8 ui8VesCh)
{
	mutex_lock (&ves_lock);
	
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);

		mutex_unlock (&ves_lock);

		return;
	}

	logm_info(vdec_ves, "[VES%d-%d][DBG] \n", ui8VesCh, gsVesDrv[ui8VesCh].State);

	switch( gsVesDrv[ui8VesCh].State )
	{
	case VES_READY :
	case VES_PAUSE :
		gsVesDrv[ui8VesCh].State = VES_PLAY;

		if( gsVesDrv[ui8VesCh].Config.eVesSrcCh <= VES_SRC_SDEC2 )
			PDEC_HAL_Enable(ui8VesCh);
		break;
	case VES_PLAY :
		logm_info(vdec_ves, "[VES%d-%d][DBG] Already Played\n", ui8VesCh, gsVesDrv[ui8VesCh].State);
		break;
	case VES_NULL :
	default :
		logm_error(vdec_ves, "[VES%d-%d][Err] Current State\n", ui8VesCh, gsVesDrv[ui8VesCh].State);
	}
	
	mutex_unlock (&ves_lock);
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
void VES_Stop(UINT8 ui8VesCh)
{
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);

		return;
	}

	logm_info(vdec_ves, "[VES%d-%d][DBG] \n", ui8VesCh, gsVesDrv[ui8VesCh].State);

	switch( gsVesDrv[ui8VesCh].State )
	{
	case VES_PLAY :
		gsVesDrv[ui8VesCh].State = VES_PAUSE;

		if( gsVesDrv[ui8VesCh].Config.eVesSrcCh <= VES_SRC_SDEC2 )
		{
			PDEC_HAL_Disable(ui8VesCh);
			
			flush_workqueue (_VDEC_VES_workqueue);
		}

		break;
	case VES_NULL :
	case VES_READY :
	case VES_PAUSE :
	default :
		logm_error(vdec_ves, "[VES%d-%d][Err] Current State\n", ui8VesCh, gsVesDrv[ui8VesCh].State);
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
void VES_Flush(UINT8 ui8VesCh)
{
	mutex_lock (&ves_lock);	
	
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);

		mutex_unlock (&ves_lock);
		
		return;
	}

	logm_info(vdec_ves, "[VES%d-%d][DBG] \n", ui8VesCh, gsVesDrv[ui8VesCh].State);

	if(gsVesDrv[ui8VesCh].State == VES_NULL)
	{
		mutex_unlock (&ves_lock);
	
		return;
	}
	
	gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = FALSE;
	gsVesDrv[ui8VesCh].Status.ui32DTS_Prev = 0xFFFFFFFF;
	gsVesDrv[ui8VesCh].Status.ui32PushedAui = 0;
	gsVesDrv[ui8VesCh].Status.bFlushing = TRUE;

//	if( gsVesDrv[ui8VesCh].Config.eVesSrcCh <= VES_SRC_SDEC2 )
//		PDEC_HAL_Pause(ui8VesCh);

	VES_AUIB_Flush(ui8VesCh);
	VES_CPB_Flush(ui8VesCh);
	
	mutex_unlock (&ves_lock);
//	if( gsVesDrv[ui8VesCh].Config.eVesSrcCh <= VES_SRC_SDEC2 )
//		PDEC_HAL_Resume(ui8VesCh);

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
BOOLEAN VES_ES_UpdateBuffer(UINT8 ui8VesCh,
									E_VES_AU_T eAuType,
									UINT32 ui32UserBuf,
									UINT32 ui32UserBufSize,
									fpCpbCopyfunc fpCopyfunc,
									UINT32 ui32UId,
									UINT64 ui64TimeStamp,	// ns
									UINT32 ui32TimeStamp_90kHzTick,
									UINT32 ui32FrameRateRes,
									UINT32 ui32FrameRateDiv)
{
	UINT32		ui32CpbWrPhyAddr = 0x0;
	UINT32		ui32CpbWrPhyAddr_End= 0x0;
	UINT32		ui32AuSize_modified= 0x0;
	S_VES_AU_T	sVesAu = {0};
	UINT32		ui32GSTC= 0x0;
	UINT32 		ui32FrameRateRes_byDTS = 0x0;
	UINT32  		ui32FrameRateDiv_byDTS = 0x0;
	UINT32 		ui32FrameRateRes_byGSTC = 0x0;
	UINT32  		ui32FrameRateDiv_byGSTC = 0x0;
	UINT32		ui32FrameRate_byDTS = 0x0;
	UINT32		ui32FrameRate_byGSTC = 0x0;
	UINT32		ui32FrameRate_byCFG = 0x0;
	E_DTS_DISCONTINUITY_T	eDtsDiscontinuity = DTS_NORMAL;
	BOOLEAN		bSTCCDiscontinuity_SW = FALSE;
	BOOLEAN		bWrapAround = FALSE;
	BOOLEAN		b512bytesAligned= 0x0;
	BOOLEAN		bRingBufferMode= 0x0;
	UINT8		ui8SyncCh= 0x0;

	ui32GSTC = TOP_HAL_GetGSTCC();

	b512bytesAligned = gsVesDrv[ui8VesCh].Config.b512bytesAligned;
	bRingBufferMode = gsVesDrv[ui8VesCh].Config.bRingBufferMode;
	ui8SyncCh = gsVesDrv[ui8VesCh].Config.ui8SyncCh;

	switch( gsVesDrv[ui8VesCh].State  )
	{
	case VES_READY :
	case VES_PAUSE :
		logm_error(vdec_ves, "[VES%d-%d][Warning] Current State\n",
									ui8VesCh, gsVesDrv[ui8VesCh].State);
	case VES_PLAY :
		if( gsVesDrv[ui8VesCh].Status.ui32PushedAui == 0 )
		{
			logm_noti(vdec_ves, "[VES%d-%d][DBG] Start UpdateBuffer - Time Stamp: %llu, GSTC: 0x%08X\n",
										ui8VesCh, gsVesDrv[ui8VesCh].State, ui64TimeStamp, ui32GSTC );
		}

		if( eAuType ==  AU_SEQUENCE_HEADER )	// Sequence Header
		{
#if 0
			UINT32		ui32CpbDumpBuf[16];

			if( copy_from_user(ui32CpbDumpBuf, (char *)(ui32UserBuf), 4*16) )
				logm_error(vdec_ves, "[VES][Err][CPB%d] copy_from_user(0x%X) - \n", ui8VesCh, (UINT32)ui32UserBuf);

			logm_noti(vdec_ves, "[VES%d-%d][DBG] 0x%X 0x%X 0x%X 0x%X\n", ui8VesCh, gsVesDrv[ui8VesCh].State,
									ui32CpbDumpBuf[0], ui32CpbDumpBuf[1], ui32CpbDumpBuf[2], ui32CpbDumpBuf[3] );
			logm_noti(vdec_ves, "[VES%d-%d][DBG] 0x%X 0x%X 0x%X 0x%X\n", ui8VesCh, gsVesDrv[ui8VesCh].State,
									ui32CpbDumpBuf[4], ui32CpbDumpBuf[5], ui32CpbDumpBuf[6], ui32CpbDumpBuf[7] );
			logm_noti(vdec_ves, "[VES%d-%d][DBG] 0x%X 0x%X 0x%X 0x%X\n", ui8VesCh, gsVesDrv[ui8VesCh].State,
									ui32CpbDumpBuf[8], ui32CpbDumpBuf[9], ui32CpbDumpBuf[10], ui32CpbDumpBuf[11] );
			logm_noti(vdec_ves, "[VES%d-%d][DBG] 0x%X 0x%X 0x%X 0x%X\n", ui8VesCh, gsVesDrv[ui8VesCh].State,
									ui32CpbDumpBuf[12], ui32CpbDumpBuf[13], ui32CpbDumpBuf[14], ui32CpbDumpBuf[15] );
#endif
			logm_debug(vdec_ves, "[VES%d-%d][DBG] Receive Sequence Header(Size:%d)\n", ui8VesCh, gsVesDrv[ui8VesCh].State, ui32UserBufSize );
		}

		// Check AUIB Overflow
		if( VES_AUIB_NumFree(ui8VesCh) < 1 )
		{
			logm_error(vdec_ves, "[VES%d][Err] AUIB Overflow \n", ui8VesCh);
			_VES_PrintStatus(ui8VesCh);
			
			return FALSE;
		}

		if( gsVesDrv[ui8VesCh].Config.bFromTVP == TRUE )
		{
			ui32CpbWrPhyAddr = ui32UserBuf;
			ui32CpbWrPhyAddr_End = ui32UserBuf + ui32UserBufSize;
			if( ui32CpbWrPhyAddr_End >= (VES_CPB_GetBufferBaseAddr(ui8VesCh) + VES_CPB_GetBufferSize(ui8VesCh)) )
				ui32CpbWrPhyAddr_End -= VES_CPB_GetBufferSize(ui8VesCh);
		}
		else
		{
			ui32CpbWrPhyAddr = VES_CPB_Write(ui8VesCh, eAuType, ui32UserBuf, ui32UserBufSize, fpCopyfunc, bRingBufferMode, b512bytesAligned,&ui32AuSize_modified, &ui32CpbWrPhyAddr_End);
			if( ui32CpbWrPhyAddr == 0x0 )
			{
				logm_error(vdec_ves, "[VES%d][Err] VES_CPB_Write Failed\n", ui8VesCh);
				_VES_PrintStatus(ui8VesCh);
				
				return FALSE;
			}
		}
		// Update Write Pointer of CPB
		VES_CPB_UpdateWrPtr( ui8VesCh, ui32CpbWrPhyAddr_End );

		VDEC_RATE_UpdateFrameRate_byDTS(ui8SyncCh, ui32TimeStamp_90kHzTick, &ui32FrameRateRes_byDTS, &ui32FrameRateDiv_byDTS);
		if( (ui32FrameRateRes_byDTS) && (ui32FrameRateDiv_byDTS) )
			ui32FrameRate_byDTS = ui32FrameRateRes_byDTS / ui32FrameRateDiv_byDTS;
		if( (ui32FrameRateRes_byGSTC) && (ui32FrameRateDiv_byGSTC) )
			ui32FrameRate_byGSTC = ui32FrameRateRes_byGSTC / ui32FrameRateDiv_byGSTC;
		if( (ui32FrameRateRes) && (ui32FrameRateDiv) )
			ui32FrameRate_byCFG = ui32FrameRateRes /ui32FrameRateDiv;

		// for debug log
		_VES_PrintStatus(ui8VesCh);	
		logm_trace(vdec_ves, "[VES%d-%d][DBG] Frame Rate byDTS: %u, byGSTC: %u, byCFG: %u\n",
										ui8VesCh, gsVesDrv[ui8VesCh].State,
										ui32FrameRate_byDTS, ui32FrameRate_byGSTC, ui32FrameRate_byCFG);
		logm_trace(vdec_ves, "[VES%d-%d][DBG] Time Stamp: %llu, DTS: 0x%08X, GSTC: 0x%08X\n",
										ui8VesCh, gsVesDrv[ui8VesCh].State,
										ui64TimeStamp, ui32TimeStamp_90kHzTick, ui32GSTC);

	
		// for debug log
//		if( gsVesDrv[ui8VesCh].Debug.ui32LogTick == 0xC0 )
//		{
//			logm_debug(vdec_ves, "[VES%d-%d][DBG] Diff DTS: %d, GSTC: 0x%08X \n",
//										ui8VesCh, gsVesDrv[ui8VesCh].State,
//										ui32TimeStamp_90kHzTick - gsVesDrv[ui8VesCh].Status.ui32DTS_Prev,
//										ui32GSTC - gsVesDrv[ui8VesCh].Debug.ui32GSTC_Prev);
//		}

//		logm_debug(vdec_ves, "[VES%d][DBG] Time Stamp: %llu, DTS: 0x%X(Rate:%u), GSTC: 0x%X\n", ui8VesCh, ui64TimeStamp, (UINT32)ui64TimeStamp_90kHzTick, ui32FrameRate_byDTS, ui32GSTC );

		if( ui32FrameRate_byDTS )
		{
			eDtsDiscontinuity = _VES_CheckDtsDiscontinuity(ui8VesCh, ui32TimeStamp_90kHzTick);
			switch( eDtsDiscontinuity )
			{
			case DTS_WRAPAROUND :
				bWrapAround = TRUE;
			case DTS_JITTER :
			case DTS_SAME :
				bSTCCDiscontinuity_SW = TRUE;
				break;
			case DTS_NORMAL :
				break;
			default :
				break;
			}
		}

		if( bSTCCDiscontinuity_SW == TRUE )
		{
			if( gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity == FALSE )
			{
				logm_debug(vdec_ves, "[VES%d-%d][Warning] S/W Detect DTS Discontinuity, DTS:0x%X(Rate:%u), GSTC:0x%X\n",
												ui8VesCh, gsVesDrv[ui8VesCh].State,
												ui32TimeStamp_90kHzTick, ui32FrameRate_byDTS, ui32GSTC );
			}

			gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = TRUE;
		}
		else if( (bSTCCDiscontinuity_SW == FALSE) && (gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity == TRUE) )
		{
			gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = FALSE;

			logm_debug(vdec_ves, "[VES%d-%d][DBG] Clear DTS Discontinuity, DTS:0x%X(Rate:%u), GSTC:0x%X\n",
										ui8VesCh, gsVesDrv[ui8VesCh].State,
										ui32TimeStamp_90kHzTick, ui32FrameRate_byDTS, ui32GSTC );
		}

//		logm_error(vdec_ves, "[VES%d] ui32TimeStamp_90kHzTick: 0x%X\n", ui8VesCh, ui32TimeStamp_90kHzTick );

		// Push CPB Parameters into CQ/AUIBs
		sVesAu.eAuType = eAuType;
		sVesAu.ui32AuStartAddr = ui32CpbWrPhyAddr;
		sVesAu.bStccDiscontinuity = gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity;
		sVesAu.bWrapAround = bWrapAround;
		sVesAu.ui32DTS = ui32TimeStamp_90kHzTick;
		sVesAu.ui32AuEndAddr = ui32CpbWrPhyAddr_End;
		if(b512bytesAligned) sVesAu.ui32AuSize = ui32AuSize_modified;
		else sVesAu.ui32AuSize = ui32UserBufSize;
		sVesAu.ui32PTS = ui32TimeStamp_90kHzTick;
		sVesAu.ui32FrameRateRes = ui32FrameRateRes;
		sVesAu.ui32FrameRateDiv = ui32FrameRateDiv;
		sVesAu.bRingBufferMode = gsVesDrv[ui8VesCh].Config.bRingBufferMode;
		sVesAu.b512bytesAligned = gsVesDrv[ui8VesCh].Config.b512bytesAligned;
		sVesAu.ui64TimeStamp = ui64TimeStamp;
		sVesAu.ui32UId = ui32UId;
		VES_AUIB_Push(ui8VesCh, &sVesAu);

		gsVesDrv[ui8VesCh].Status.ui32DTS_Prev = ui32TimeStamp_90kHzTick;
		gsVesDrv[ui8VesCh].Status.ui32PushedAui++;
		break;
	case VES_NULL :
	default :
		logm_error(vdec_ves, "[VES%d][Err] Current State: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State);
		break;
	}
	
	gsVesDrv[ui8VesCh].Debug.ui32GSTC_Prev = ui32GSTC;

	return TRUE;
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

static UINT32 _VES_Decoded2Auib(UINT8 ui8VesCh)
{
	S_PDEC_AUI_T	sPdecAui = {0};
	UINT32			ui32GSTC = 0x0;
	UINT32			*pui32AuibVirAddr;
	E_DTS_DISCONTINUITY_T	eDtsDiscontinuity = DTS_NORMAL;
	BOOLEAN			bSTCCDiscontinuity_SW = FALSE;
	BOOLEAN			bWrapAround = FALSE;
	UINT32			ui32DecodedAuiCount = 0x0;
	int stc_invalid = 0x0;
	UINT32 uid;
	UINT32 *pui32PrevAuibVirAddr;
	volatile UINT32	ui32AU_Info3;

	ui32GSTC = TOP_HAL_GetGSTCC();
	
	switch( gsVesDrv[ui8VesCh].State  )
	{
	case VES_READY :
	case VES_PAUSE :
		logm_error(vdec_ves, "[VES%d-%d][Warning] Current State\n",
									ui8VesCh, gsVesDrv[ui8VesCh].State);
		break;
	case VES_PLAY :
		if( gsVesDrv[ui8VesCh].Status.ui32PushedAui == 0 )
		{
			logm_info(vdec_ves, "[VES%d-%d][DBG] Start Decoding, GSTC:0x%X\n",
										ui8VesCh, gsVesDrv[ui8VesCh].State,
										ui32GSTC );
		}

		while( (pui32AuibVirAddr = PDEC_HAL_GetLatestDecodedAUI(ui8VesCh, &sPdecAui)) != 0x0 )
		{
			ui32DecodedAuiCount++;

			if( sPdecAui.bStccDiscontinuity == TRUE )
			{
				if( gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity == FALSE )
				{
					logm_noti(vdec_ves, "[VES%d-%d][Warning] H/W Detect DTS Discontinuity, DTS:0x%X, GSTC:0x%X\n",
													ui8VesCh, gsVesDrv[ui8VesCh].State,
													sPdecAui.ui32DTS, ui32GSTC );
				}
				else
				{
					logm_noti(vdec_ves, "[VES%d-%d][Warning] H/W DTS Discontinuity, DTS:0x%X, GSTC:0x%X\n",
													ui8VesCh, gsVesDrv[ui8VesCh].State,
													sPdecAui.ui32DTS, ui32GSTC );
				}
			}

			eDtsDiscontinuity = _VES_CheckDtsDiscontinuity(ui8VesCh, sPdecAui.ui32DTS);
			switch( eDtsDiscontinuity )
			{
			case DTS_WRAPAROUND :
				bWrapAround = TRUE;
			case DTS_JITTER :
				bSTCCDiscontinuity_SW = TRUE;
				break;
			case DTS_SAME :
			case DTS_NORMAL :
				break;
			default :
				break;
			}

			// for debug log
			if( bSTCCDiscontinuity_SW == TRUE )
			{
				if( gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity == FALSE )
				{
					logm_noti(vdec_ves, "[VES%d-%d][Warning] S/W Detect DTS Discontinuity, DTS:0x%X, GSTC:0x%X\n",
													ui8VesCh, gsVesDrv[ui8VesCh].State,
													sPdecAui.ui32DTS, ui32GSTC );
				}
				else
				{
					logm_debug(vdec_ves, "[VES%d-%d][Warning] S/W DTS Discontinuity, DTS:0x%X, GSTC:0x%X\n",
													ui8VesCh, gsVesDrv[ui8VesCh].State,
													sPdecAui.ui32DTS, ui32GSTC );
				}
			}

			PDEC_UTIL_SetWrapAround(pui32AuibVirAddr, bWrapAround);

			if( (sPdecAui.bStccDiscontinuity == TRUE) || (bSTCCDiscontinuity_SW == TRUE) )
			{
				if( gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity == FALSE )
				{
					logm_noti(vdec_ves, "[VES%d-%d][Warning] Set DTS Discontinuity, DTS:0x%X, GSTC:0x%X\n",
												ui8VesCh, gsVesDrv[ui8VesCh].State,
												sPdecAui.ui32DTS, ui32GSTC );
				}
				gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = TRUE;

				PDEC_UTIL_SetDiscontinuity(pui32AuibVirAddr, TRUE);
			}
			else if( (bSTCCDiscontinuity_SW == FALSE) && (gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity == TRUE) )
			{
				gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity = FALSE;

				PDEC_UTIL_SetDiscontinuity(pui32AuibVirAddr, FALSE);

				logm_noti(vdec_ves, "[VES%d-%d][DBG] Clear DTS Discontinuity, DTS:0x%X, GSTC:0x%X\n",
											ui8VesCh, gsVesDrv[ui8VesCh].State,
											sPdecAui.ui32DTS, ui32GSTC );
			}			

			gsVesDrv[ui8VesCh].Status.ui32DTS_Prev = sPdecAui.ui32DTS;

			pui32PrevAuibVirAddr = pui32AuibVirAddr;
			
		}
		gsVesDrv[ui8VesCh].Status.ui32PushedAui += ui32DecodedAuiCount;

		if( ui32DecodedAuiCount )
		{
			if( VES_AUIB_NumFree(ui8VesCh) < 1 )
			{
				logm_error(vdec_ves, "[VES%d][Err] AUIB Overflow - UseNum: %d\n", ui8VesCh, VES_AUIB_NumActive(ui8VesCh));
				
				return 0;
			}

			gsVesDrv[ui8VesCh].Debug.STC_PTS_flag = sPdecAui.STC_PTS_flag;

			ui32AU_Info3 = pui32PrevAuibVirAddr[3];
			ui32AU_Info3 &= ~0x00000001;

			if(sPdecAui.bStccDiscontinuity)
			{
				ui32AU_Info3 |= 0x00000001;
				pui32PrevAuibVirAddr[3] = ui32AU_Info3;
			}
			else
			{
				pui32PrevAuibVirAddr[3] = ui32AU_Info3;
			}

			stc_invalid = sPdecAui.bStccDiscontinuity;			
			//gsVesDrv[ui8VesCh].Status.bSTCCDiscontinuity;
			uid = gsVesDrv[ui8VesCh].Debug.ui32UID;
			gsVesDrv[ui8VesCh].Debug.ui32UID++;

			VES_AUIB_UpdateWrPtr(ui8VesCh, PDEC_HAL_AUIB_GetWrPtr(ui8VesCh, FALSE));
			VES_CPB_UpdateWrPtr(ui8VesCh, PDEC_HAL_CPB_GetWrPtr(ui8VesCh));

			if (gsVesDrv[ui8VesCh].Config.fpBufferUpdated)
			gsVesDrv[ui8VesCh].Config.fpBufferUpdated (ui8VesCh,
					gsVesDrv[ui8VesCh].Config.pBufferUpdatedArg, stc_invalid, uid);
		}	

		break;
	case VES_NULL :
	default :
		logm_error(vdec_ves, "[VES%d][Warning] Current State: %d\n", ui8VesCh, gsVesDrv[ui8VesCh].State);
		break;
	}

	gsVesDrv[ui8VesCh].Debug.ui32GSTC_Prev = ui32GSTC;

	return ui32DecodedAuiCount;
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
static void _VDEC_ISR_PIC_Detected(UINT8 ui8VesCh)
{
	switch( ui8VesCh )
	{
	case 0 :
	case 1 :
	case 2 :
		if( gsVesDrv[ui8VesCh].Status.bFlushing == TRUE )
		{
			PDEC_HAL_Flush(ui8VesCh);
			VES_AUIB_UpdateWrPtr(ui8VesCh, PDEC_HAL_AUIB_GetWrPtr(ui8VesCh, FALSE));
			VES_CPB_UpdateWrPtr(ui8VesCh, PDEC_HAL_CPB_GetWrPtr(ui8VesCh));

			gsVesDrv[ui8VesCh].Status.bFlushing = FALSE;
		}

		_VES_Decoded2Auib(ui8VesCh);
		break;
	default :
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);
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
static void _VDEC_ISR_PIC_Detected_workfunc(struct work_struct *data)
{
	UINT8	ui8VesCh = 0;
	UINT32	ui32VesChBitMask = ui32WorkfuncParam;
	ui32WorkfuncParam = 0x0;

	mutex_lock (&ves_lock);	

	while( ui32VesChBitMask )
	{
		if( ui32VesChBitMask & 0x1 )
			_VDEC_ISR_PIC_Detected(ui8VesCh);

		ui32VesChBitMask >>= 1;
		ui8VesCh++;
	}
	
	mutex_unlock (&ves_lock);
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
void VDEC_ISR_PIC_Detected(UINT8 ui8VesCh)
{

	ui32WorkfuncParam |= (1 << ui8VesCh);
	queue_work(_VDEC_VES_workqueue,  &_VDEC_VES_work);

}

