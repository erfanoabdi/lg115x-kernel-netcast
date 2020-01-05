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
 * date       2011.04.09
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
#include "de_if_drv.h"
#include "vsync_drv.h"

#ifdef __XTENSA__
#include <stdio.h>
#include <string.h>
#else
#include <linux/kernel.h>
#include <asm/string.h>	// memset
#endif

#include "../mcu/os_adap.h"

#include "../hal/ipc_reg_api.h"

#include "../hal/de_ipc_hal_api.h"
#include "../hal/top_hal_api.h"
#include "../hal/lq_hal_api.h"
#include "../hal/vdec_base.h"
#include "../hal/de_vdo_hal_api.h"

#define LOG_NAME	vdec_de_if
#include "log.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define	DE_IF_NUM_OF_CMD_Q					0x10
#define DE_Q_FRAME_NUM						2
/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	S_DE_IPC_T		sDeIpc;

	enum
	{
		DE_IF_CLOSE,
		DE_IF_OPEN
	} eState;

	BOOLEAN			bFreezing;

	UINT32			ui32DisplayInfo;
	UINT32			ui32DisplayPeriod;
	UINT32			ui32FieldCount;

	BOOLEAN			bForcedPush;
	UINT8			u8NoneForcedPushCnt;
	UINT8			u8nFrameRepeat;

	// for Debug
	UINT32			ui32LogTick;
	UINT32			ui32UpdateFrameCount;
} S_DE_IF_DB_T;


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
static S_DE_IF_DB_T		gsDeIf[DE_IF_NUM_OF_CHANNEL];
static BOOLEAN gbMirrorMode = FALSE, gbMirrorOn = FALSE;
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
static void _DE_IF_Reset(UINT8 ui8DeIfCh)
{
	S_DE_IPC_T		*psDeIpc = NULL;

	psDeIpc = (S_DE_IPC_T *)&gsDeIf[ui8DeIfCh].sDeIpc;
	memset((void *)psDeIpc, 0x0, sizeof(S_DE_IPC_T));
	psDeIpc->ui32FrameIdx = 0xFF;
	psDeIpc->ui32DisplayMode = 0x3;
	psDeIpc->ui32LR_Order = 2;	// None
	psDeIpc->ui32DpbMapType = 0xFF;


	gsDeIf[ui8DeIfCh].bFreezing = FALSE;
	gsDeIf[ui8DeIfCh].bForcedPush = TRUE;
	gsDeIf[ui8DeIfCh].u8nFrameRepeat = DE_Q_FRAME_NUM+1;
	gsDeIf[ui8DeIfCh].u8NoneForcedPushCnt = 0;

	gsDeIf[ui8DeIfCh].ui32DisplayInfo = DISPQ_SCAN_NULL;
	gsDeIf[ui8DeIfCh].ui32DisplayPeriod = 0x0;
	gsDeIf[ui8DeIfCh].ui32FieldCount = 0xFFFFFFFF;

	gsDeIf[ui8DeIfCh].ui32LogTick = 0xFFFFFFF0;
	gsDeIf[ui8DeIfCh].ui32UpdateFrameCount = 0;

	if( ui8DeIfCh < DE_IPC_NUM_OF_CHANNEL )
	{
		DE_IPC_HAL_Update( ui8DeIfCh, psDeIpc );
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
void DE_IF_Init(void)
{
	UINT8	ui8DeIfCh;

	bDualVsyncForProgFrame = lx_chip_rev() < LX_CHIP_REV(H13, B0);


	log_noti("[DE_IF][DBG] DE I/F Init: 0x%X, %s\n", (UINT32)gsDeIf, __FUNCTION__ );

	for( ui8DeIfCh = 0; ui8DeIfCh < DE_IF_NUM_OF_CHANNEL; ui8DeIfCh++ )
	{
		gsDeIf[ui8DeIfCh].eState = DE_IF_CLOSE;
		_DE_IF_Reset(ui8DeIfCh);
	}
}


static void _de_if_dual_output_on(void)
{
	log_noti("[DE_IF][DBG] dual out ON\n");

	DE_VDO_HAL_Register(1, 1, TRUE);
	_DE_IF_Reset(1);
	DE_VDO_HAL_SetVSyncSel(1,0);
	gbMirrorOn = TRUE;
}

static void _de_if_dual_output_off(void)
{
	log_noti("[DE_IF][DBG] dual out OFF\n");

	gbMirrorOn = FALSE;
	DE_VDO_HAL_Register(1, 0xFF, TRUE);
	_DE_IF_Reset(1);
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
BOOLEAN DE_IF_Open(E_DE_IF_DST_T eDeIfDstCh)
{
	UINT8		ui8DeIfCh;

	ui8DeIfCh = (UINT8)eDeIfDstCh;

	log_noti("[DE_IF%d][DBG] %s \n", ui8DeIfCh, __FUNCTION__ );

	if( ui8DeIfCh >= DE_IF_DST_MAX )
	{
		log_error("[DE_IF%d][Err] wrong channel! %s\n", ui8DeIfCh, __FUNCTION__ );
		return FALSE;
	}

	if( gsDeIf[ui8DeIfCh].eState == DE_IF_OPEN )
		log_warning("[DE_IF%d] Already opened channel, %s\n", ui8DeIfCh, __FUNCTION__ );

	gsDeIf[ui8DeIfCh].eState = DE_IF_OPEN;

	DE_VDO_HAL_Register(ui8DeIfCh, ui8DeIfCh, TRUE);
	_DE_IF_Reset(ui8DeIfCh);

	if( ui8DeIfCh == 0 && gbMirrorMode == TRUE &&
			gbMirrorOn == FALSE && gsDeIf[1].eState != DE_IF_OPEN )
		_de_if_dual_output_on();

	if( ui8DeIfCh == 1 && gbMirrorMode == TRUE )
	{
		log_error("deif: mirror mode is on but try to open deif 1\n");
		if( gbMirrorOn == TRUE )
			_de_if_dual_output_off();
	}

	return TRUE;
}


void DE_IF_SelVsync(E_DE_IF_DST_T eDeIfDstCh, UINT32 ui32VSyncSrc)
{
	DE_VDO_HAL_SetVSyncSel((UINT8)eDeIfDstCh, ui32VSyncSrc);
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
void DE_IF_Close(E_DE_IF_DST_T eDeIfDstCh)
{
	UINT8		ui8DeIfCh;

	ui8DeIfCh = (UINT8)eDeIfDstCh;

	log_noti("[DE_IF%d][DBG] %s \n", ui8DeIfCh, __FUNCTION__ );

	if( ui8DeIfCh >= DE_IF_DST_MAX )
	{
		log_error("[DE_IF%d][Err] wrong channel! %s\n", ui8DeIfCh, __FUNCTION__ );
		return;
	}

	if( ui8DeIfCh == 1 && gbMirrorMode == TRUE &&
			gbMirrorOn == FALSE && gsDeIf[0].eState != DE_IF_OPEN)
		_de_if_dual_output_on();

	if( ui8DeIfCh == 0 && gbMirrorOn == TRUE )
		_de_if_dual_output_off();

	gsDeIf[ui8DeIfCh].eState = DE_IF_CLOSE;

	DE_VDO_HAL_Register(ui8DeIfCh, 0xFF, FALSE);
	_DE_IF_Reset(ui8DeIfCh);

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
void DE_IF_Freeze(E_DE_IF_DST_T eDeIfDstCh, BOOLEAN bOnOff)
{
	UINT8		ui8DeIfCh;

	switch( eDeIfDstCh )
	{
	case DE_IF_DST_DE_IF0 :
	case DE_IF_DST_DE_IF1 :
		ui8DeIfCh = (UINT8)eDeIfDstCh;
		gsDeIf[ui8DeIfCh].bFreezing = bOnOff;

		log_noti("[DE_IF%d][DBG] Freeze:%d %s \n", ui8DeIfCh, bOnOff, __FUNCTION__ );
		break;
	default :
		log_error("[DE_IF%d][Err] %s\n", eDeIfDstCh, __FUNCTION__ );
	}
}


BOOLEAN DE_IF_SetDualOutput(BOOLEAN bOn)
{
	BOOLEAN bPreConf;

	bPreConf = gbMirrorMode;
	gbMirrorMode = !!bOn;

	if( gbMirrorMode == TRUE )
	{
		if( gbMirrorOn == FALSE &&
			gsDeIf[0].eState == DE_IF_OPEN && gsDeIf[1].eState != DE_IF_OPEN )
		_de_if_dual_output_on();
	}
	else
	{
		if( gbMirrorOn == TRUE )
			_de_if_dual_output_off();
	}

	return bPreConf;
}

void DE_IF_RepeatFrame(E_DE_IF_DST_T eDeIfDstCh, UINT8 u8nTimes)
{
	S_DE_IF_DB_T	*pstDeIf = NULL;

	if( eDeIfDstCh >= DE_IF_DST_MAX )
	{
		log_error("wrong DE IF channel %d\n", (UINT32)eDeIfDstCh);
		return;
	}
	pstDeIf = &gsDeIf[eDeIfDstCh];

	if( u8nTimes == 0 )
	{
		pstDeIf->bForcedPush = FALSE;
		log_noti("ch %d forced push off\n", eDeIfDstCh);
	}
	else
	{
		pstDeIf->bForcedPush = TRUE;
		pstDeIf->u8nFrameRepeat = u8nTimes;
		pstDeIf->ui32FieldCount = 0;
	}

	pstDeIf->u8NoneForcedPushCnt = 0;
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
UINT32 DE_IF_GetRunningFrameIndex(E_DE_IF_DST_T eDeIfDstCh)
{
	UINT32	ui32FrameIdx = 0xFF;
	UINT8	ui8DeIfCh;

	switch( eDeIfDstCh )
	{
	case DE_IF_DST_DE_IF0 :
	case DE_IF_DST_DE_IF1 :
		ui8DeIfCh = (UINT8)eDeIfDstCh;

		ui32FrameIdx = gsDeIf[ui8DeIfCh].sDeIpc.ui32FrameIdx;

//		log_noti("[DE_IF%d][DBG] Running Frame Index:0x%X\n", ui8DeIfCh, ui32FrameIdx );
		break;
	default :
		log_error("[DE_IF%d][Err] %s", eDeIfDstCh, __FUNCTION__ );
	}

	return ui32FrameIdx;
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

static UINT32 _get_nth_field(UINT32 u32PicScanType, UINT32 u32nThField)
{
	UINT32 u32FieldType;

	switch( u32PicScanType )
	{
		case DISPQ_SCAN_PROG :
			u32FieldType = DE_IPC_FRAME;
			break;

		case DISPQ_SCAN_TFF :
			if( u32nThField == 0 )
				u32FieldType = DE_IPC_TOP_FIELD;
			else
				u32FieldType = DE_IPC_BOTTOM_FIELD;
			break;

		case DISPQ_SCAN_BFF :
			if( u32nThField == 0 )
				u32FieldType = DE_IPC_BOTTOM_FIELD;
			else
				u32FieldType = DE_IPC_TOP_FIELD;
			break;

		default :
			u32FieldType = DE_IPC_FRAME;
			log_error("[DE_IF][Err] Picture Scan Type:%d, Frame Idx:%d\n",
					u32PicScanType, u32nThField);
			break;
	}

	return u32FieldType;
}

inline BOOLEAN DE_IF_IsNeedNewFrame(E_DE_IF_DST_T eDeIfDstCh)
{
	S_DE_IF_DB_T	*pstDeIf = NULL;
	UINT32 			u32DispPeriod=0;
	BOOLEAN			bRet = TRUE;

	pstDeIf = &gsDeIf[(UINT8)eDeIfDstCh];

	if( (pstDeIf->sDeIpc.ui32FrameIdx & 0xFF) != 0xFF )
	{
		u32DispPeriod = pstDeIf->ui32DisplayPeriod;

		if( pstDeIf->ui32FieldCount < u32DispPeriod )
			bRet = FALSE;

		// A0 Work Around
		if( bDualVsyncForProgFrame &&
				pstDeIf->ui32DisplayInfo == DISPQ_SCAN_PROG &&
				pstDeIf->ui32FieldCount%2 == 1 )
			bRet = FALSE;
	}

	log_trace("DE_IF:%d: NeedNew? %d, %d <= %d ?\n", (UINT32)eDeIfDstCh, bRet,
			pstDeIf->ui32FieldCount, u32DispPeriod);

	return bRet;
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

inline static void _check_new_frame(UINT8 ui8DeIfCh, S_DE_IPC_T *psDeIpc, S_DISPQ_BUF_T *psDisBuf)
{
	if( (psDeIpc->ui32FrameIdx & 0xFF) == 0xFF )
	{
		log_noti("[DE_IF%d] Start Transfer\n", ui8DeIfCh);
		log_noti("[DE_IF%d] Stride: 0x%X, Base_Y: 0x%X, Base_C: 0x%X, Offset_Y: 0x%X, Offset_C: 0x%X\n",
				ui8DeIfCh, psDisBuf->ui32Stride,
				psDisBuf->ui32Y_FrameBaseAddr, psDisBuf->ui32C_FrameBaseAddr,
				psDisBuf->ui32Y_FrameOffset, psDisBuf->ui32C_FrameOffset );

		log_noti("[DE_IF%d] FrameIdx: 0x%X, FrameRateRes: %d, FrameRateDiv: %d, AspectRatio: %d\n",
				ui8DeIfCh, psDisBuf->ui32FrameIdx, psDisBuf->ui32FrameRateRes,
				psDisBuf->ui32FrameRateDiv, psDisBuf->ui32AspectRatio);

		log_noti("[DE_IF%d] H_Offset: %d, V_Offset: %d, PicWidth: %d, PicHeight: %d\n",
				ui8DeIfCh, psDisBuf->ui32H_Offset, psDisBuf->ui32V_Offset,
				psDisBuf->ui32PicWidth, psDisBuf->ui32PicHeight);

		log_noti("[DE_IF%d] FramePackArrange: %d, LR_Order: %d\n", ui8DeIfCh,
				psDisBuf->i32FramePackArrange, psDisBuf->ui32LR_Order);
	}
	else if( gsDeIf[ui8DeIfCh].ui32FieldCount != gsDeIf[ui8DeIfCh].ui32DisplayPeriod )
	{
		log_noti("[DE_IF%d] Field Count: %d / Display Period: %d, %s\n",
				ui8DeIfCh, gsDeIf[ui8DeIfCh].ui32FieldCount,
				gsDeIf[ui8DeIfCh].ui32DisplayPeriod, __FUNCTION__ );
	}

	if( (psDeIpc->ui16FrameRateRes != psDisBuf->ui32FrameRateRes) ||
			(psDeIpc->ui16FrameRateDiv != psDisBuf->ui32FrameRateDiv) ||
			(psDeIpc->ui32AspectRatio != psDisBuf->ui32AspectRatio) )
		log_noti("[DE_IF%d] FrameRate: %d/%d -> %d/%d, AspectRatio: %d -> %d\n",
				ui8DeIfCh, psDeIpc->ui16FrameRateRes, psDeIpc->ui16FrameRateDiv,
				psDisBuf->ui32FrameRateRes, psDisBuf->ui32FrameRateDiv,
				psDeIpc->ui32AspectRatio, psDisBuf->ui32AspectRatio);

	if( (psDeIpc->ui16PicWidth != psDisBuf->ui32PicWidth) ||
			(psDeIpc->ui16PicHeight != psDisBuf->ui32PicHeight) )
		log_noti("[DE_IF%d] Width * Height: %d * %d -> %d * %d\n",
				ui8DeIfCh, psDeIpc->ui16PicWidth, psDeIpc->ui16PicHeight,
				psDisBuf->ui32PicWidth, psDisBuf->ui32PicHeight);

	return;
}

inline static void _de_if_debug_log(UINT8 ui8DeIfCh, S_DE_IF_DB_T *pstDeIf,
		S_DE_IPC_T *psDeIpc)
{
	if( pstDeIf->ui32FieldCount >= pstDeIf->ui32DisplayPeriod )
	{
		if( (pstDeIf->ui32FieldCount % 0x100) == 0xFF && !pstDeIf->bFreezing )
		{
			log_noti(
					"[DE_IF%d] Too Big FieldCnt %d >= Period %d DispInfo:%d/%d\n",
					ui8DeIfCh, pstDeIf->ui32FieldCount,
					pstDeIf->ui32DisplayPeriod,
					pstDeIf->ui32DisplayInfo,
					psDeIpc->ui32DisplayMode);
		}
	}

	if( (pstDeIf->ui32UpdateFrameCount == 1) &&
			(pstDeIf->ui32FieldCount == 1) )
	{
		log_noti("[DE_IF%d][DBG] Start Updating\n", ui8DeIfCh );
	}

	// log for debug
	pstDeIf->ui32LogTick++;
	if( pstDeIf->ui32LogTick >= 0x100 )
	{
		log_noti("[DE_IF%d][DBG] Updated Frame Count: %d, DispInfo: %d\n",
				ui8DeIfCh,
				pstDeIf->ui32UpdateFrameCount,
				pstDeIf->ui32DisplayInfo);

		pstDeIf->ui32LogTick = 0;
	}
}

inline static BOOLEAN deif_check_ipc_update_need(UINT8 ui8DeIfCh, S_DE_IF_DB_T *pstDeIf,
		UINT8 u8PicDispType, UINT32 ui32SyncField)
{
	static UINT32 logCnt=0;
	BOOLEAN bReqIpcUpdate = FALSE;

	if( u8PicDispType == DE_IPC_FRAME )
	{
		if( !bDualVsyncForProgFrame || ui32SyncField == (pstDeIf->ui32FieldCount % 2) )
			bReqIpcUpdate = TRUE;
	}
	else
	{
		if( (ui32SyncField == 0 && u8PicDispType == DE_IPC_TOP_FIELD) ||
				(ui32SyncField == 1 && u8PicDispType == DE_IPC_BOTTOM_FIELD) )
		{
			bReqIpcUpdate = TRUE;
			if(logCnt) logCnt--;
		}
		else
		{
			bReqIpcUpdate = FALSE;
			logCnt++;

			// The first frame right after vsync set
			// 		could have wrong field sync, but it's not a big deal.

			//if(pstDeIf->ui32UpdateFrameCount > 1)
			if(pstDeIf->ui32LogTick < 0xFFFFFFF0 &&
					(logCnt<5 || !(logCnt%10)) )
			{
				log_noti( "[DE_IF%d][Err%d] SyncField:%d, FieldCnt:%d\n",
						ui8DeIfCh, logCnt, ui32SyncField, pstDeIf->ui32FieldCount);
			}
		}
	}

	return bReqIpcUpdate;
}

inline BOOLEAN DE_IF_UpdateDisplay(E_DE_IF_DST_T eDeIfDstCh, UINT32 ui32SyncField)
{
	S_DE_IF_DB_T	*pstDeIf = NULL;
	S_DE_IPC_T		*psDeIpc = NULL;
	UINT8			ui8DeIfCh, u8PauseThold;
	UINT8			u8PicDispType;
	BOOLEAN			bReqIpcUpdate = FALSE;
	static UINT32 u32DbgCnt[DE_IF_DST_MAX]={0, };

	ui8DeIfCh = (UINT8)eDeIfDstCh;
	if( ui8DeIfCh >= DE_IF_DST_MAX )
	{
		log_error("[DE_IF%d][Err] %s\n", eDeIfDstCh, __FUNCTION__ );
		return FALSE;
	}

	psDeIpc = (S_DE_IPC_T *)&gsDeIf[ui8DeIfCh].sDeIpc;
	pstDeIf = &gsDeIf[ui8DeIfCh];

	if( (psDeIpc->ui32FrameIdx & 0xFF) == 0xFF )
	{
		if( u32DbgCnt[ui8DeIfCh] != 0xFF )
			log_noti("DE_IF: mute idx\n");

		goto exit_de_if_up;
	}

	u8PauseThold = pstDeIf->ui32DisplayPeriod;

	if( pstDeIf->bForcedPush )
		u8PauseThold *= pstDeIf->u8nFrameRepeat;

	if( pstDeIf->ui32FieldCount >= u8PauseThold )
	{
		// Pause or Repeat
		psDeIpc->ui32UpdateInfo = 0x0;
		psDeIpc->ui32VdecPause = 0x1;
		pstDeIf->u8nFrameRepeat = DE_Q_FRAME_NUM+1;
	}
	else
	{
		if( pstDeIf->ui32FieldCount == 0 )
			psDeIpc->ui32UpdateInfo = 0x1;
		else
			psDeIpc->ui32UpdateInfo = 0x0;

		psDeIpc->ui32VdecPause = 0x0;
	}

	if( unlikely(psDeIpc->ui32VdecPause) )
	{
		bReqIpcUpdate = TRUE;
		u8PicDispType = _get_nth_field( pstDeIf->ui32DisplayInfo,
				(pstDeIf->ui32DisplayPeriod-1) % 2);
	}
	else
	{
		u8PicDispType = _get_nth_field( pstDeIf->ui32DisplayInfo,
				pstDeIf->ui32FieldCount % 2);

		bReqIpcUpdate = deif_check_ipc_update_need(ui8DeIfCh, pstDeIf,
				u8PicDispType, ui32SyncField);
	}

	if( bReqIpcUpdate == TRUE )
	{
		psDeIpc->ui32DisplayMode = u8PicDispType;

		// detect whether still picture or not
		if( pstDeIf->bForcedPush )
		{
			if( pstDeIf->ui32FieldCount == 0 )
				pstDeIf->u8NoneForcedPushCnt++;
			else if( pstDeIf->ui32FieldCount >= pstDeIf->ui32DisplayPeriod*2 )
				pstDeIf->u8NoneForcedPushCnt=0;

			if( pstDeIf->u8NoneForcedPushCnt >= 3 )
			{
				log_noti("DEIF %d: forced push off\n", ui8DeIfCh);
				pstDeIf->bForcedPush = FALSE;
				pstDeIf->u8NoneForcedPushCnt=0;
			}
		}

		if( pstDeIf->ui32FieldCount == 0 )
		{
			DE_IPC_HAL_SetNewFrame(ui8DeIfCh, psDeIpc);
			if( gbMirrorOn )
				DE_IPC_HAL_SetNewFrame(DE_IF_DST_DE_IF1, psDeIpc);
		}

		DE_IPC_HAL_UpdateIpc(ui8DeIfCh, psDeIpc);
		if( gbMirrorOn )
			DE_IPC_HAL_UpdateIpc(DE_IF_DST_DE_IF1, psDeIpc);

		if (psDeIpc->ui32Tiled_FrameBaseAddr)
		{
			DE_VDO_HAL_Update (ui8DeIfCh, psDeIpc, ui32SyncField);
			if( gbMirrorOn )
				DE_VDO_HAL_Update (DE_IF_DST_DE_IF1, psDeIpc, ui32SyncField);
		}

		pstDeIf->ui32FieldCount++;
	}

	_de_if_debug_log(ui8DeIfCh, pstDeIf, psDeIpc);
	log_user1("DE%d Idx %2d Field %d FldCnt %d/%d ReqIpcUp %d Pause %d PicTy %d Qlen %d\n",
			ui8DeIfCh, pstDeIf->sDeIpc.ui32FrameIdx, ui32SyncField, pstDeIf->ui32FieldCount,
			pstDeIf->ui32DisplayPeriod,	bReqIpcUpdate, pstDeIf->sDeIpc.ui32VdecPause,
			u8PicDispType, DISP_Q_NumActive(0)
			);

exit_de_if_up:

	u32DbgCnt[ui8DeIfCh] = psDeIpc->ui32FrameIdx;
	return TRUE;
}


inline BOOLEAN DE_IF_SetNewFrame(E_DE_IF_DST_T eDeIfDstCh, S_DISPQ_BUF_T *psDisBuf, UINT32 ui32SyncField)
{
	S_DE_IPC_T		*psDeIpc = NULL;
	UINT32			ui32DeIfCh;

	ui32DeIfCh = (UINT32)eDeIfDstCh;
	if( ui32DeIfCh >= DE_IF_DST_MAX )
	{
		log_error("[DE_IF%d][Err] %s\n", eDeIfDstCh, __FUNCTION__ );
		return FALSE;
	}

	if( gsDeIf[ui32DeIfCh].bFreezing == TRUE )
		return FALSE;

	log_trace("DE_IF:%d: Set New Frame #%d\n", ui32DeIfCh, psDisBuf->ui32FrameIdx);

	psDeIpc = (S_DE_IPC_T *)&gsDeIf[ui32DeIfCh].sDeIpc;
	_check_new_frame(ui32DeIfCh, psDeIpc, psDisBuf);

	if( gsDeIf[ui32DeIfCh].bForcedPush == FALSE && (
			(psDeIpc->ui32DisplayMode == 1 && psDisBuf->ui32DisplayInfo == DISPQ_SCAN_TFF) ||
			(psDeIpc->ui32DisplayMode == 2 && psDisBuf->ui32DisplayInfo == DISPQ_SCAN_BFF) )  )
	{
		if( psDisBuf->ui32DisplayPeriod >2 )
		{
			log_noti("drop one field\n");
			psDisBuf->ui32DisplayPeriod--;
		}
		else
		{
			log_noti("stuff one field\n");
			psDisBuf->ui32DisplayPeriod++;
		}

		if( psDisBuf->ui32DisplayInfo == DISPQ_SCAN_TFF )
			psDisBuf->ui32DisplayInfo = DISPQ_SCAN_BFF;
		else
			psDisBuf->ui32DisplayInfo = DISPQ_SCAN_TFF;
	}

	if( (psDisBuf->ui32DisplayInfo == DISPQ_SCAN_TFF && ui32SyncField == 1) ||
			(psDisBuf->ui32DisplayInfo == DISPQ_SCAN_BFF && ui32SyncField == 0) )
	{
		log_noti("[DEIF%d] syncfield not matched\n", eDeIfDstCh);
		//return FALSE;

		return FALSE;
	}

	psDeIpc->ui32Tiled_FrameBaseAddr = psDisBuf->ui32Tiled_FrameBaseAddr;
	psDeIpc->ui32DpbMapType = psDisBuf->ui32DpbMapMode;
	psDeIpc->ui32Y_FrameBaseAddr = psDisBuf->ui32Y_FrameBaseAddr;
	psDeIpc->ui32C_FrameBaseAddr = psDisBuf->ui32C_FrameBaseAddr;
	psDeIpc->ui32Y_FrameOffset = psDisBuf->ui32Y_FrameOffset;
	psDeIpc->ui32C_FrameOffset = psDisBuf->ui32C_FrameOffset;
	psDeIpc->ui32Stride = psDisBuf->ui32Stride;
	psDeIpc->ui32ColorFormat = psDisBuf->FrameFormat;

	psDeIpc->ui32FrameIdx = psDisBuf->ui32FrameIdx;
	psDeIpc->ui16FrameRateRes = psDisBuf->ui32FrameRateRes;
	psDeIpc->ui16FrameRateDiv = psDisBuf->ui32FrameRateDiv;
	psDeIpc->ui32AspectRatio = psDisBuf->ui32AspectRatio;
	psDeIpc->ui32H_Offset = psDisBuf->ui32H_Offset;
	psDeIpc->ui32V_Offset = psDisBuf->ui32V_Offset;
	psDeIpc->ui16PicWidth = psDisBuf->ui32PicWidth;
	psDeIpc->ui16PicHeight = psDisBuf->ui32PicHeight;
	psDeIpc->ui32FramePackArrange = psDisBuf->i32FramePackArrange;
	psDeIpc->ui32LR_Order = psDisBuf->ui32LR_Order;
	psDeIpc->ui16ParW = psDisBuf->ui16ParW;
	psDeIpc->ui16ParH = psDisBuf->ui16ParH;
	psDeIpc->ui32PTS = psDisBuf->ui32PTS;

	gsDeIf[ui32DeIfCh].ui32DisplayInfo = psDisBuf->ui32DisplayInfo;
	gsDeIf[ui32DeIfCh].ui32DisplayPeriod = psDisBuf->ui32DisplayPeriod;
	gsDeIf[ui32DeIfCh].ui32FieldCount = 0;

	gsDeIf[ui32DeIfCh].ui32UpdateFrameCount++;

	return TRUE;
}

void DE_IF_RunVdo(UINT8 u8FieldInfo)
{
	DE_VDO_HAL_RunCmd (NULL, NULL, u8FieldInfo);
}
#endif

