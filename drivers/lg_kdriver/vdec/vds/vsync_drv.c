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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     youngki.lyu@lge.com
 * version    1.0
 * date       2011.11.08
 * note       Additional information.
 *
 * @addtogroup lg115x_vdec
 * @{
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "vsync_drv.h"
#include "vdisp_drv.h"
#include "pts_drv.h"
#include "de_if_drv.h"
#include "../mcu/ipc_callback.h"
#include "../mcu/ipc_req.h"

#ifdef __XTENSA__
#include <stdio.h>
#else
#include <linux/kernel.h>
#include <asm/string.h>	// memset
#include <linux/delay.h>
//#include <linux/time.h>
#endif

#include "../mcu/os_adap.h"
#include "disp_q.h"
#include "../hal/ipc_reg_api.h"
#include "../hal/vsync_hal_api.h"
#include "../hal/top_hal_api.h"
#include "../hal/lq_hal_api.h"

#define LOG_NAME	vdec_vsync
#include "log.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define		VSYNC_NUM_OF_WORK_Q				0x80
//#define  VSYNC_ISR_PERFORMANCE_EVAL

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	BOOLEAN			bUse;
	UINT8 			ui8SyncCh;
	E_DE_IF_DST_T 	eDeIfDstCh;
} VDISP_CH_TAG_T;

typedef struct
{
	UINT32 u32PhaseShift;

	UINT32 u32NextPhaseShift;
	UINT32 u32NextResidual;
	UINT32 u32NextDivider;
	BOOLEAN bNextInterlaced;

	struct
	{
		UINT32		ui32FrameResidual;
		UINT32		ui32FrameDivider;
		UINT32		ui32FrameDuration90K;
		BOOLEAN		bInterlaced;
	} Rate;

	struct
	{
		UINT8		u8VsyncCh;
		BOOLEAN		bFixedVSync;
		VDISP_CH_TAG_T astSyncChTag[VDISP_MAX_NUM_OF_MULTI_CHANNEL];
	} Config;

	struct
	{
		volatile UINT32		ui32WrIndex;
		volatile UINT32		ui32RdIndex;
	} WorkQ;

	struct
	{
		volatile UINT32		ui32DualUseChMask;
		volatile UINT32		ui32ActiveDeIfChMask;
		volatile UINT32		ui32ClosingDeIfChMask;
	} Status;

	struct
	{
		UINT32		ui32LogTick_ISR;
		UINT32		ui32LogTick_Dual;
		UINT32		ui32GSTC_Prev;
		UINT32		ui32DurationTick;
		UINT32		ui32DualTickDiff;
//		UINT32		ui32VsyncShare;
//		UINT32		ui32VsyncSum;
	} Debug;

} VSYNC_CH_T;



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

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static VSYNC_CH_T gsVSync[VSYNC_NUM_OF_CHANNEL];
//static VSYNC_CB fnVsyncCallback = NULL;
static VSYNC_CB fnFeedCallback = NULL;
#ifdef  VSYNC_ISR_PERFORMANCE_EVAL
static struct timeval tv_start;
#endif
static BOOLEAN bDualVsyncForProgFrame = FALSE;

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
void VSync_Init(VSYNC_CB fnCallback)
{
	UINT8	ui8VSyncCh, ui8UseCh;

	log_noti("[VSync][DBG] Vsync Init: 0x%X, %s\n", (UINT32)gsVSync, __FUNCTION__ );

	bDualVsyncForProgFrame = lx_chip_rev() < LX_CHIP_REV(H13, B0);

	fnFeedCallback = fnCallback;

	for( ui8VSyncCh = 0; ui8VSyncCh < VSYNC_NUM_OF_CHANNEL; ui8VSyncCh++ )
	{
		gsVSync[ui8VSyncCh].Rate.ui32FrameResidual = 0x0;
		gsVSync[ui8VSyncCh].Rate.ui32FrameDivider = 0x1;
		gsVSync[ui8VSyncCh].Rate.ui32FrameDuration90K = 0x0;
		gsVSync[ui8VSyncCh].Rate.bInterlaced = TRUE;

		gsVSync[ui8VSyncCh].Config.u8VsyncCh = ui8VSyncCh;
		gsVSync[ui8VSyncCh].Config.bFixedVSync = FALSE;
		for( ui8UseCh = 0; ui8UseCh < VDISP_MAX_NUM_OF_MULTI_CHANNEL; ui8UseCh++ )
		{
			gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].bUse = FALSE;
			gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].ui8SyncCh = VDISP_INVALID_CHANNEL;
			gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].eDeIfDstCh = VDISP_INVALID_CHANNEL;
		}

		gsVSync[ui8VSyncCh].WorkQ.ui32WrIndex = 0;
		gsVSync[ui8VSyncCh].WorkQ.ui32RdIndex = 0;

		gsVSync[ui8VSyncCh].Status.ui32DualUseChMask = FALSE;
		gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask = 0x0;
		gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask = 0x0;
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
UINT8 VSync_Open(E_DE_IF_DST_T eDeIfDstCh, UINT8 ui8SyncCh, BOOLEAN bIsDualDecoding, BOOLEAN bFixedVSync, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv, BOOLEAN bInterlaced)
{
	UINT8		ui8VSyncCh = VDISP_INVALID_CHANNEL;
	UINT8		ui8UseCh;
	UINT8		ui8EmptyCh;
	BOOLEAN		bIsIntrEnable;
	UINT32		ui32WaintCount = 0;

	switch( eDeIfDstCh )
	{
	case DE_IF_DST_DE_IF0 :		// 0
	case DE_IF_DST_DE_IF1 :		// 1
		if( bIsDualDecoding == TRUE || bDualVsyncForProgFrame )
		{
			ui8VSyncCh = 0;
			log_noti("[VSync%d][DBG] Dual - Sync:%d, DE_IF:%d, %s\n",
					ui8VSyncCh, ui8SyncCh, eDeIfDstCh, __FUNCTION__ );
		}
		else
		{
			ui8VSyncCh = (UINT8)eDeIfDstCh;
		}
		break;
	default :
		log_error("[DE_IF%d][Err] %s\n", eDeIfDstCh, __FUNCTION__ );
		return VDISP_INVALID_CHANNEL;
	}

	// wait closing complete
	while( (gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask) &&
		(gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask ==
		 gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask) )
	{
		if( ui32WaintCount > 0x100 )
		{
			log_error("[VSync%d][Err] %s(%d)\n", ui8VSyncCh, __FUNCTION__, __LINE__ );
			break;
		}

		log_error("[VSync%d][Warning] Closing, %s(%d)\n",
				ui8VSyncCh, __FUNCTION__, __LINE__ );

		mdelay(10);
		ui32WaintCount++;
	}

	if( gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask & (1 << eDeIfDstCh) )
	{
		log_error("[VSync%d][Err] Already Set - ActiveChMask: 0x%X(%d), %s(%d)\n",
				ui8VSyncCh, gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask,
				eDeIfDstCh, __FUNCTION__, __LINE__ );

		for( ui8UseCh = 0; ui8UseCh < VDISP_MAX_NUM_OF_MULTI_CHANNEL; ui8UseCh++ )
			log_error("[VSync%d:%d][Err] Use:%d, Sync:%d, DE_IF:%d, %s(%d)\n",
					ui8VSyncCh, ui8UseCh,
					gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].bUse,
					gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].ui8SyncCh,
					gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].eDeIfDstCh,
					__FUNCTION__, __LINE__ );

		return VDISP_INVALID_CHANNEL;
	}

	log_noti("[VSync%d][DBG] DualDecoding:%d, ActiveChMask: 0x%X, DE_IF:%d, Sync:%d, %s \n",
			ui8VSyncCh, bIsDualDecoding, gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask,
			eDeIfDstCh, ui8SyncCh, __FUNCTION__ );

	ui8EmptyCh = VDISP_INVALID_CHANNEL;
	for( ui8UseCh = 0; ui8UseCh < VDISP_MAX_NUM_OF_MULTI_CHANNEL; ui8UseCh++ )
	{
		if( gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].bUse == TRUE )
		{
			if( (gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].ui8SyncCh == ui8SyncCh) &&
				(gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].eDeIfDstCh == eDeIfDstCh) )
			{
				log_error("[VSync%d:%d][Err] Already Set - Sync:%d, DE_IF:%d, %s(%d)\n",
						ui8VSyncCh, ui8UseCh, ui8SyncCh, eDeIfDstCh, __FUNCTION__, __LINE__ );
				return VDISP_INVALID_CHANNEL;
			}
		}
		else
		{
			ui8EmptyCh = ui8UseCh;
			break;
		}
	}

	if( ui8EmptyCh == VDISP_INVALID_CHANNEL )
	{
		log_error("[VSync%d][Err] Not Enough Mux Channel, %s(%d)\n",
				ui8VSyncCh, __FUNCTION__, __LINE__ );
		return VDISP_INVALID_CHANNEL;
	}

	log_noti("[VSync%d][DBG] DE_IF:%d, Sync:%d, %s \n",
			ui8VSyncCh, eDeIfDstCh, ui8SyncCh, __FUNCTION__ );

	if( bIsDualDecoding == TRUE )
	{
		if( gsVSync[ui8VSyncCh].Status.ui32DualUseChMask & (1 << (UINT32)ui8EmptyCh) )
			log_error("[VSync%d][Err] IsDualDecoding - Sync:%d, DE_IF:%d, %s(%d)\n",
					ui8VSyncCh, ui8SyncCh, eDeIfDstCh, __FUNCTION__, __LINE__ );
		else
			gsVSync[ui8VSyncCh].Status.ui32DualUseChMask |= (1 << (UINT32)ui8EmptyCh);
	}
	gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8EmptyCh].bUse = TRUE;
	gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8EmptyCh].ui8SyncCh = ui8SyncCh;
	gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8EmptyCh].eDeIfDstCh = eDeIfDstCh;
	gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask |= (1 << (UINT32)eDeIfDstCh);

	// if the first vsync usage,
	if( gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask == (1 << (UINT32)eDeIfDstCh) )
	{
		gsVSync[ui8VSyncCh].u32PhaseShift = 0;
		gsVSync[ui8VSyncCh].u32NextPhaseShift = 0;
		gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask = 0x0;

		gsVSync[ui8VSyncCh].Debug.ui32LogTick_ISR = 0;
		gsVSync[ui8VSyncCh].Debug.ui32LogTick_Dual = 0;
		gsVSync[ui8VSyncCh].Debug.ui32GSTC_Prev = 0xFFFFFFFF;
		gsVSync[ui8VSyncCh].Debug.ui32DurationTick = 0;
		gsVSync[ui8VSyncCh].Debug.ui32DualTickDiff = 0;

		gsVSync[ui8VSyncCh].Rate.ui32FrameResidual = ui32FrameRateRes;
		gsVSync[ui8VSyncCh].Rate.ui32FrameDivider = ui32FrameRateDiv;
		gsVSync[ui8VSyncCh].Rate.ui32FrameDuration90K =
			VSync_CalFrameDuration(ui32FrameRateRes, ui32FrameRateDiv);
		gsVSync[ui8VSyncCh].Rate.bInterlaced = bInterlaced;

		gsVSync[ui8VSyncCh].u32NextResidual = ui32FrameRateRes;
		gsVSync[ui8VSyncCh].u32NextDivider = ui32FrameRateDiv;
		gsVSync[ui8VSyncCh].bNextInterlaced = bInterlaced;

		VSync_HAL_SetVsyncField(ui8VSyncCh, ui32FrameRateRes, ui32FrameRateDiv, bInterlaced);

		TOP_HAL_SetLQSyncMode(ui8SyncCh, ui8VSyncCh);

		TOP_HAL_ClearExtIntr(VSYNC0+ui8VSyncCh);
		TOP_HAL_EnableExtIntr(VSYNC0+ui8VSyncCh);

		log_noti("[VSync%d][DBG] Enable Interrupt, %s \n",
				ui8VSyncCh, __FUNCTION__ );
	}

	bIsIntrEnable = TOP_HAL_IsExtIntrEnable(VSYNC0+ui8VSyncCh);
	if( bIsIntrEnable == FALSE )
	{
		log_error("[VSync%d][Err] VSync Channel Interrupt Disabled, %s \n",
				ui8VSyncCh, __FUNCTION__ );
	}

	return ui8VSyncCh;
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
void VSync_SetClosing(UINT8 ui8VSyncCh, E_DE_IF_DST_T eDeIfDstCh)
{
	if( gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask & (1 << eDeIfDstCh) )
	{
		log_error("[VSync%d][Err] Closing Channel Mask: 0x%X, %s \n", ui8VSyncCh, gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask, __FUNCTION__ );
	}

	gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask |= (1 << eDeIfDstCh);
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
void VSync_Close(UINT8 ui8VSyncCh, E_DE_IF_DST_T eDeIfDstCh, UINT8 ui8SyncCh)
{
	UINT8	ui8UseCh;
	UINT8	ui8DeleteCh;

	if( ui8VSyncCh >= VSYNC_NUM_OF_CHANNEL )
	{
		log_error("[VSync%d][Err] %s\n", ui8VSyncCh, __FUNCTION__ );
		return;
	}

	log_noti("[VSync%d][DBG] %s\n", ui8VSyncCh, __FUNCTION__ );

	ui8DeleteCh = VDISP_INVALID_CHANNEL;
	for( ui8UseCh = 0; ui8UseCh < VDISP_MAX_NUM_OF_MULTI_CHANNEL; ui8UseCh++ )
	{
		if( gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].bUse == TRUE )
		{
			if( (gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].ui8SyncCh == ui8SyncCh) &&
				(gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8UseCh].eDeIfDstCh == eDeIfDstCh) )
			{
				if( ui8DeleteCh != VDISP_INVALID_CHANNEL )
					log_error("[VSync%d][Err] Not Matched Ch - DE_IF:%d, Sync:%d, %s(%d)\n",
							ui8VSyncCh, eDeIfDstCh, ui8SyncCh, __FUNCTION__, __LINE__ );

				ui8DeleteCh = ui8UseCh;
			}
		}
	}
	if( ui8DeleteCh == VDISP_INVALID_CHANNEL )
	{
		log_error("[VSync%d][Err] Not Matched Ch - DE_IF:%d, Sync:%d, %s(%d)\n",
				ui8VSyncCh, eDeIfDstCh, ui8SyncCh, __FUNCTION__, __LINE__ );
		return;
	}

	gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8DeleteCh].ui8SyncCh = VDISP_INVALID_CHANNEL;
	gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8DeleteCh].eDeIfDstCh = VDISP_INVALID_CHANNEL;
	gsVSync[ui8VSyncCh].Config.astSyncChTag[ui8DeleteCh].bUse = FALSE;
	gsVSync[ui8VSyncCh].Status.ui32DualUseChMask &= ~(1 << (UINT32)ui8DeleteCh);

	log_noti("[VSync%d][DBG] DE_IF:%d, Sync:%d, %s \n",
			ui8VSyncCh, eDeIfDstCh, ui8SyncCh, __FUNCTION__ );

	gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask &= ~(1 << (UINT32)eDeIfDstCh);
	if( gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask == 0x0 )
	{
		BOOLEAN			bIsIntrEnable;

		gsVSync[ui8VSyncCh].Debug.ui32LogTick_ISR = 0;
		gsVSync[ui8VSyncCh].Debug.ui32LogTick_Dual = 0;
		gsVSync[ui8VSyncCh].Debug.ui32GSTC_Prev = 0xFFFFFFFF;
		gsVSync[ui8VSyncCh].Debug.ui32DurationTick = 0;
		gsVSync[ui8VSyncCh].Debug.ui32DualTickDiff = 0;
//		gsVSync[ui8VSyncCh].Debug.ui32VsyncShare = 0;
//		gsVSync[ui8VSyncCh].Debug.ui32VsyncSum = 0;

		gsVSync[ui8VSyncCh].Rate.ui32FrameResidual = 0x0;
		gsVSync[ui8VSyncCh].Rate.ui32FrameDivider = 0x1;
		gsVSync[ui8VSyncCh].Rate.ui32FrameDuration90K = 0x0;
		gsVSync[ui8VSyncCh].Rate.bInterlaced = TRUE;

		bIsIntrEnable = TOP_HAL_IsExtIntrEnable(VSYNC0+ui8VSyncCh);
		if( bIsIntrEnable == FALSE )
			log_error("[VSync%d][Err] VSync Intr Already Disabled, %s \n",
					ui8VSyncCh, __FUNCTION__ );

		TOP_HAL_DisableExtIntr(VSYNC0+ui8VSyncCh);
		TOP_HAL_ClearExtIntr(VSYNC0+ui8VSyncCh);

		log_noti("[VSync%d][DBG] Disable Interrupt, %s \n", ui8VSyncCh,
				__FUNCTION__ );
	}

	gsVSync[ui8VSyncCh].Status.ui32ClosingDeIfChMask &= ~(1 << (UINT32)eDeIfDstCh);
}

int VSync_IsActive (UINT8 ui8VSyncCh)
{
	if (ui8VSyncCh >= VSYNC_NUM_OF_CHANNEL)
		return 0;

	return gsVSync[ui8VSyncCh].Status.ui32ActiveDeIfChMask != 0;
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
UINT32 VSync_CalFrameDuration(UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv)
{
	UINT32		ui32FrameDuration90K = 0;

	UINT32		ui32FrameRateRes_Scaled;
	UINT32		ui32_90kHz_Scaled = 90000;
	UINT32		ui32Gcd;
	UINT32		ui320xFFFFFFFF_Boundary;
	UINT32		ui32FrameRateDiv_Temp;

	const UINT32	ui32ScaleUnit = 10;	// must > 1

	if( ui32FrameRateRes == 0 )
		return 0;

	ui32Gcd = VSync_HAL_UTIL_GCD( ui32_90kHz_Scaled, ui32FrameRateRes );
	ui32_90kHz_Scaled /= ui32Gcd;
	ui32FrameRateRes_Scaled = ui32FrameRateRes / ui32Gcd;

	ui320xFFFFFFFF_Boundary = 0xFFFFFFFF / ui32_90kHz_Scaled;

	ui32FrameRateDiv_Temp = ui32FrameRateDiv;
	while( ui32_90kHz_Scaled )
	{
		if( ui32FrameRateDiv_Temp <= ui320xFFFFFFFF_Boundary )
			break;

		ui32FrameRateDiv_Temp /= ui32ScaleUnit;
		ui32_90kHz_Scaled /= ui32ScaleUnit;
		ui32FrameRateRes_Scaled /= ui32ScaleUnit;
	}

	// FrameDuration90K = 90KHz / (FrameRateRes / FrameRateDiv)
	ui32FrameDuration90K = ui32_90kHz_Scaled * ui32FrameRateDiv / ui32FrameRateRes_Scaled; // = 90kHz / FrameRate

	return ui32FrameDuration90K;
}

#if (defined(USE_MCU_FOR_VDEC_VDS) && defined(__XTENSA__)) || \
	(!defined(USE_MCU_FOR_VDEC_VDS) && !defined(__XTENSA__))
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
void VSync_SetPhaseShift(UINT8 ui8VSyncCh, UINT32 u32ShiftDelta90K)
{
	UINT32 u32ShiftDelta27M;

	log_noti("[Vsync%d] shift %d\n", ui8VSyncCh, u32ShiftDelta90K);

	if( gsVSync[ui8VSyncCh].u32PhaseShift )
	{
		log_noti("[Vsync%d] set phase shift fail: already set, cur shift %d\n",
				ui8VSyncCh, gsVSync[ui8VSyncCh].u32PhaseShift);
		return;
	}

	u32ShiftDelta27M = 27000000/90000 * u32ShiftDelta90K;

	gsVSync[ui8VSyncCh].u32NextPhaseShift = u32ShiftDelta27M;
}


BOOLEAN VSync_SetNextVsyncField(UINT8 ui8VSyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv, BOOLEAN bInterlaced)
{
	if( ui8VSyncCh >= VSYNC_NUM_OF_CHANNEL )
	{
		log_error("[VSync%d][Err] Channel Number, %s\n", ui8VSyncCh, __FUNCTION__ );
		return FALSE;
	}
	gsVSync[ui8VSyncCh].u32NextResidual = ui32FrameRateRes;
	gsVSync[ui8VSyncCh].u32NextDivider = ui32FrameRateDiv;
	gsVSync[ui8VSyncCh].bNextInterlaced = bInterlaced;

	return TRUE;
}

BOOLEAN VSync_SetVsyncField(UINT8 ui8VSyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv, BOOLEAN bInterlaced)
{
	UINT32		ui32FrameDuration90K;
	BOOLEAN		bUpdated = FALSE;

	if( ui8VSyncCh >= VSYNC_NUM_OF_CHANNEL )
	{
		log_error("[VSync%d][Err] Channel Number, %s\n", ui8VSyncCh, __FUNCTION__ );
		return FALSE;
	}

	if( gsVSync[ui8VSyncCh].Config.bFixedVSync == TRUE )
	{
		return FALSE;
	}

	if( (ui32FrameRateRes == 0) || (ui32FrameRateDiv == 0) )
	{
//			log_error("[VSync%d][Err] FrameRateRes:%d, FrameRateDiv:%d, %s\n", ui8VSyncCh, ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__);
		return FALSE;
	}

	if( (gsVSync[ui8VSyncCh].Rate.ui32FrameResidual != ui32FrameRateRes) ||
			(gsVSync[ui8VSyncCh].Rate.ui32FrameDivider != ui32FrameRateDiv) ||
			(gsVSync[ui8VSyncCh].Rate.bInterlaced != bInterlaced) ||
			gsVSync[ui8VSyncCh].u32PhaseShift != gsVSync[ui8VSyncCh].u32NextPhaseShift )
	{
		UINT32		ui32FieldRate_Prev, ui32FieldRate_Curr;

		if( bDualVsyncForProgFrame == TRUE )
		{
			ui32FieldRate_Prev = 2;
			ui32FieldRate_Curr = 2;
		}
		else
		{
			ui32FieldRate_Prev = (gsVSync[ui8VSyncCh].Rate.bInterlaced == TRUE) ? 2 : 1;
			ui32FieldRate_Curr = (bInterlaced == TRUE) ? 2 : 1;
		}

		ui32FrameDuration90K = VSync_CalFrameDuration( ui32FrameRateRes, ui32FrameRateDiv );

		log_noti("[VSync%d][DBG] FieldDuration90k: %d --> %d %d %d shift %d\n", ui8VSyncCh,
				gsVSync[ui8VSyncCh].Rate.ui32FrameDuration90K / ui32FieldRate_Prev,
				ui32FrameDuration90K / ui32FieldRate_Curr,
				ui32FrameDuration90K , ui32FieldRate_Curr,
				gsVSync[ui8VSyncCh].u32NextPhaseShift/300 );

		gsVSync[ui8VSyncCh].Rate.ui32FrameResidual = ui32FrameRateRes;
		gsVSync[ui8VSyncCh].Rate.ui32FrameDivider = ui32FrameRateDiv;
		gsVSync[ui8VSyncCh].Rate.bInterlaced = bInterlaced;

		gsVSync[ui8VSyncCh].Rate.ui32FrameDuration90K = ui32FrameDuration90K;

		if( !VSync_HAL_IntField(ui8VSyncCh) )
		{
			gsVSync[ui8VSyncCh].u32PhaseShift = gsVSync[ui8VSyncCh].u32NextPhaseShift;
			gsVSync[ui8VSyncCh].u32NextPhaseShift = 0;
			VSync_HAL_SetVsyncShift(ui8VSyncCh, gsVSync[ui8VSyncCh].u32PhaseShift);
		}

		VSync_HAL_SetVsyncField(ui8VSyncCh, ui32FrameRateRes, ui32FrameRateDiv, bInterlaced);

		bUpdated = TRUE;
	}

	return bUpdated;
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

static inline UINT32 _VSYNC_SearchDualCh(VSYNC_CH_T *pstVsync, BOOLEAN bIsNeededNewFrame[],
		UINT8 *pu8LowCh, UINT8 *pu8HighCh)
{
	UINT8			ui8VSyncCh;
	UINT8			ui8UseCh;
	VDISP_CH_TAG_T	*pstSync;
	VDISP_CH_TAG_T	*pstSyncs[2];
	UINT8			u8nCh=0;
	BOOLEAN			bNeedWait = FALSE;
	UINT8			ui8UseCh_Low = VDISP_INVALID_CHANNEL, ui8UseCh_High=VDISP_INVALID_CHANNEL;

	ui8VSyncCh = pstVsync->Config.u8VsyncCh;
	// find channal numbers usded for dual stream
	for( ui8UseCh = 0; ui8UseCh < VDISP_MAX_NUM_OF_MULTI_CHANNEL; ui8UseCh++ )
	{
		pstSync = &pstVsync->Config.astSyncChTag[ui8UseCh];
		if( pstVsync->Status.ui32DualUseChMask & (1 << ui8UseCh) )
		{
			if( pstSync->bUse == FALSE )
				log_error("[VSync%d] DualChMsk: 0x%X ActiveChMsk: 0x%X\n",
						ui8VSyncCh, pstVsync->Status.ui32DualUseChMask,
						pstVsync->Status.ui32ActiveDeIfChMask);

			if( u8nCh < 2 )
			{
				if( u8nCh == 0 )
					ui8UseCh_Low = ui8UseCh;
				else
					ui8UseCh_High = ui8UseCh;
				pstSyncs[u8nCh++] = pstSync;
			}
			else
			{
				log_error("[VSync%d][Err] DualStream - 1:%d, 2:%d, 3:%d, ActiveChMask: 0x%X\n",
						ui8VSyncCh, ui8UseCh_Low, ui8UseCh_High, ui8UseCh,
						pstVsync->Status.ui32ActiveDeIfChMask);
			}
		}
	}

	if( u8nCh == 2 )
	{
		if( (bIsNeededNewFrame[ui8UseCh_Low] == FALSE) ||
				(bIsNeededNewFrame[ui8UseCh_High] == FALSE) )
		{
			// when only one side needs new frame
			if( (bIsNeededNewFrame[ui8UseCh_Low] == TRUE) ||
					(bIsNeededNewFrame[ui8UseCh_High] == TRUE) )
			{
				if( (pstVsync->Debug.ui32LogTick_Dual % 10) == 0 )
					log_noti("[VSync%d Warn] DualStrm, Single Update, Ch%d-Up:%d, Ch%d-Up:%d\n",
							ui8VSyncCh, ui8UseCh_Low, ui8UseCh_High,
							bIsNeededNewFrame[ui8UseCh_Low],
							bIsNeededNewFrame[ui8UseCh_High]);

				pstVsync->Debug.ui32LogTick_Dual++;
			}

			//wait another side
			bNeedWait = TRUE;
		}
	}
	else
	{
		if( (pstVsync->Debug.ui32LogTick_Dual % 10) == 0 )
			log_noti("[VSync%d:%d %d][Warn] Wait Other Ch of Dual Straem\n",
					ui8VSyncCh, ui8UseCh_Low, ui8UseCh_High );
		pstVsync->Debug.ui32LogTick_Dual++;

		// wait until another side will be open
		if( u8nCh == 1 )
			bNeedWait = TRUE;
	}

	if( !bNeedWait )
	{
		*pu8LowCh = ui8UseCh_Low;
		*pu8HighCh = ui8UseCh_High;
	}
	else
	{
		if( ui8UseCh_Low != VDISP_INVALID_CHANNEL )
			bIsNeededNewFrame[ui8UseCh_Low] = FALSE;
		if( ui8UseCh_High != VDISP_INVALID_CHANNEL )
			bIsNeededNewFrame[ui8UseCh_High] = FALSE;

		*pu8LowCh = VDISP_INVALID_CHANNEL;
		*pu8HighCh = VDISP_INVALID_CHANNEL;
	}

	return u8nCh;
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

static inline void _VSYNC_Debug_Log(VSYNC_CH_T *pstVsync, UINT32 u32Gstc)
{
	UINT32			ui32DurationTick = 0;
	UINT8			ui8VSyncCh = pstVsync->Config.u8VsyncCh;
	VDISP_CH_TAG_T	*pstSync;

	pstVsync->Debug.ui32LogTick_ISR++;
	if( pstVsync->Debug.ui32LogTick_ISR >= 0x100 )
	{
		static UINT8		ui8UseCh = 0;

		if( pstVsync->Config.astSyncChTag[ui8UseCh].bUse )
		{
			pstSync = &pstVsync->Config.astSyncChTag[ui8UseCh];
			log_noti("[VSy%d:%d,Sy%d,DEIF%d] STC:0x%X DBG:0x%X Rate:%d,DualTickDiff:%d\n",
					ui8VSyncCh, ui8UseCh, pstSync->ui8SyncCh, pstSync->eDeIfDstCh,
					u32Gstc,
					u32Gstc,
					90000 / (u32Gstc - pstVsync->Debug.ui32GSTC_Prev),
					pstVsync->Debug.ui32DualTickDiff);

			pstVsync->Debug.ui32LogTick_ISR = 0;
		}

		ui8UseCh++;
		if( ui8UseCh >= VDISP_MAX_NUM_OF_MULTI_CHANNEL )
			ui8UseCh=0;
	}

	//if( pstVsync->Debug.ui32GSTC_Prev != 0xFFFFFFFF )
	//{
	//	UINT32		ui32GSTC_End;
	//
	//	ui32GSTC_End = TOP_HAL_GetGSTCC() & 0x7FFFFFFF;
	//
	//	pstVsync->Debug.ui32VsyncShare += (ui32GSTC_End >= u32Gstc) ?
	//		(ui32GSTC_End - u32Gstc) : (ui32GSTC_End + 0x7FFFFFFF - u32Gstc);
	//	pstVsync->Debug.ui32VsyncSum += (u32Gstc >= pstVsync->Debug.ui32GSTC_Prev) ?
	//		(u32Gstc - pstVsync->Debug.ui32GSTC_Prev) :
	//		(u32Gstc + 0x7FFFFFFF - pstVsync->Debug.ui32GSTC_Prev);
	//}

	if( pstVsync->Debug.ui32GSTC_Prev != 0xFFFFFFFF )
	{
		ui32DurationTick = ( u32Gstc >= pstVsync->Debug.ui32GSTC_Prev ) ?
			u32Gstc - pstVsync->Debug.ui32GSTC_Prev :
			0x7FFFFFFF - pstVsync->Debug.ui32GSTC_Prev + u32Gstc;
	}

	if( pstVsync->Debug.ui32DurationTick )
	{
		UINT32		ui32DurationTick_Diff;

		ui32DurationTick_Diff = ( ui32DurationTick >= pstVsync->Debug.ui32DurationTick ) ?
			ui32DurationTick - pstVsync->Debug.ui32DurationTick :
			pstVsync->Debug.ui32DurationTick - ui32DurationTick;

		if( ui32DurationTick_Diff > 270 )	// > 3ms
			log_noti("[VSync%d] Unstable vsync: intv %X->%X\n",
					ui8VSyncCh, pstVsync->Debug.ui32DurationTick, ui32DurationTick);
	}

	pstVsync->Debug.ui32DurationTick = ui32DurationTick;
	pstVsync->Debug.ui32GSTC_Prev = u32Gstc;

#ifdef  VSYNC_ISR_PERFORMANCE_EVAL
	// performance check
	{
		struct timeval tv_end;
		static UINT32 u32TotalTime=0, u32Cnt=0, u32Max=0;
		UINT32 t;

		do_gettimeofday(&tv_end);

		u32Cnt++;
		t = (tv_end.tv_sec - tv_start.tv_sec) * 1000000 +
				tv_end.tv_usec - tv_start.tv_usec;
		if( t>u32Max ) u32Max = t;

		u32TotalTime += t;

		if( u32Cnt >= 200 )
		{
			log_error("Ev.t %u Max %u\n", u32TotalTime/u32Cnt, u32Max);
			u32Cnt = 0;
			u32TotalTime = 0;
			u32Max = 0;
		}
	}
#endif

}

void VDEC_ISR_VSync(UINT8 ui8VSyncCh)
{
	VSYNC_CH_T *pstVsync;
	UINT8			i;
	UINT32			u32Gstc;
	UINT32			u32IntnField;
	UINT32			u32nSync = 0;
	UINT8			au8SyncCh[VDISP_MAX_NUM_OF_MULTI_CHANNEL];

	if( ui8VSyncCh >= VSYNC_NUM_OF_CHANNEL )
	{
		log_error("[VSync%d][Err] Channel NO. %s\n", ui8VSyncCh, __FUNCTION__ );
		goto _vsync_exit;
	}

#ifdef  VSYNC_ISR_PERFORMANCE_EVAL
	{
		//static struct timeval tv_pre_start;
		do_gettimeofday(&tv_start);
		//log_error("intv %u\n",
		//		(tv_start.tv_sec - tv_pre_start.tv_sec) * 1000000 +
		//		tv_start.tv_usec - tv_pre_start.tv_usec);
		//tv_pre_start = tv_start;
	}
#endif

	pstVsync = &gsVSync[ui8VSyncCh];
	// sync scan
	for( i = 0; i < VDISP_MAX_NUM_OF_MULTI_CHANNEL; i++ )
	{
		if( pstVsync->Config.astSyncChTag[i].bUse == TRUE )
			au8SyncCh[u32nSync++] = pstVsync->Config.astSyncChTag[i].ui8SyncCh;
	}

	u32IntnField = (VSync_HAL_IntField(ui8VSyncCh));
	u32Gstc = TOP_HAL_GetGSTCC() & 0x7FFFFFFF;

	log_user3("[Vsync%d] GSTC %d  Field %d\n", ui8VSyncCh, u32Gstc, u32IntnField);

	if( fnFeedCallback != NULL )
		fnFeedCallback(ui8VSyncCh, u32nSync, au8SyncCh, u32IntnField);

	VSync_SetVsyncField(ui8VSyncCh, pstVsync->u32NextResidual,
			pstVsync->u32NextDivider, pstVsync->bNextInterlaced );

	_VSYNC_Debug_Log(pstVsync, u32Gstc);

_vsync_exit:

	return;
}

#endif


