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
 * date       2011.06.14
 * note       Additional information.
 *
 * @addtogroup lg115x_vdec
 * @{
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#define		PTS_STC_WAITING_DECISION_DURATION		(256)
#define		PTS_STC_SMOOTH_WAITING_DURATION			(4)
#define		PTS_STC_DISCARD_DECISION_DURATION		(4096)		// 2min = 2*60*1000/33
#define		PTS_STC_DISCARD_DECISION_DURATION_LIVE	(300)		// =~ 10sec
#define		PTS_STC_SMOOTH_DISCARD_DURATION			(64)
#define		PTS_CONTINUITY_DURATION					(64)
#define		PTS_CONTINUITY_COUNT					(16)
#define		PTS_WAITING_SYNC_COUNT					(4)
#define		PTS_DISCARD_SYNC_COUNT					(2)

#define		VDEC_FAST_CHCH_FRAME		3

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pts_drv.h"
#include "../mcu/ipc_callback.h"
#include "../mcu/ipc_req.h"

#ifdef __XTENSA__
#include <stdio.h>
#include "stdarg.h"
#include "../hal/mcu_hal_api.h"
#else
#include <linux/kernel.h>
#include <asm/string.h>	// memset
#include <linux/delay.h>
#include "base_drv.h"
#endif

#include "../mcu/os_adap.h"

#include "disp_q.h"
#include "disp_clear_q.h"
#include "../hal/top_hal_api.h"
#include "../hal/ipc_reg_api.h"
#include "../hal/vdec_base.h"

#include "vdec_rate.h"

#define LOG_NAME	vdec_pts
#define LOG_LEVEL	log_level_error
#include "log.h"


static int vdec_display_offset;
module_param (vdec_display_offset, int, 0644);

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define	PTS_GET_PTS_OFFSET( _prev, _curr )	\
				(((_curr) < (_prev)) ? ((_curr) + 0x0FFFFFFF - (_prev)) : (_curr) - (_prev))
#define	PTS_CHECK_PTS_WRAPAROUND( _pts)	((_pts) & 0x0FFFFFFF)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef enum
{
	PTS_CONTINUITY_NONE = 0,
	PTS_CONTINUITY_NORMAL,
	PTS_CONTINUITY_SAME,
	PTS_CONTINUITY_JITTER,
	PTS_CONTINUITY_WRAPAROUND,
	PTS_CONTINUITY_INVALID_STC,
	PTS_CONTINUITY_MAX,
	PTS_CONTINUITY_MAX_STR_LEN = 15,
	PTS_CONTINUITY_UINT32 = 0x20110809
} PTS_CONTINUITY_E;

typedef enum
{
	PTS_DQ_NONE = 0,
	PTS_DQ_UNDERRUN,
	PTS_DQ_NORMAL,
	PTS_DQ_OVERFLOW,
	PTS_DQ_UINT32 = 0x20110716
} E_PTS_FLOW_T;



struct _SYNC_T
{
	UINT32 ui8SyncCh;

	UINT32		u32nFrame;
	BOOLEAN		bSmoothOn;
	UINT32		u32SmWaitCnt;
	UINT32		u32SmDiscardCnt;

	UINT32		ui32PTS_Prev;
	UINT32		ui32STC_Prev;
	PTS_CONTINUITY_E		ePtsCont;
	UINT32		ui32FrameSkipCount;	// When underrun, Count vsync
	UINT32		ui32PtsContinuityCount;
	UINT32		ui32ContinuousFrameCount;
	SINT32		i32SyncDiff;

	UINT32		u32EmptyCnt10;
	UINT32		u32AdpMaxQLen;
	UINT32		u32AdpOverCnt;
	UINT32		u32QLen;

	BOOLEAN		bHighResolution;

	UINT8		u8DiscontCnt;

	struct
	{
		BOOLEAN		bUseGstc;
		PTS_MATCH_MODE_E		eMatchMode;
		UINT32 		ui32DisplayOffset_ms;
		UINT8		bIsDualDecoding;
	} Config;
	struct
	{
		UINT32		ui32DqPopRateRes;
		UINT32		ui32DqPopRateDiv;

		UINT32		ui32PtsRateRes;
		UINT32		ui32PtsRateDiv;

		UINT32		ui32BaseTime;
		UINT32		ui32BasePTS;
		UINT32		ui32PauseTime;

		BOOLEAN		bInterlaced;
	} Rate;
	struct
	{
		UINT32		ui32LogTick_GetNew;
		UINT32		ui32LogTick_GetNewNo;
		UINT32		ui32LogTick_Noti;
		UINT32		ui32LogTick_Match;
		UINT32		ui32LogTick_Pause;

		UINT32		ui32MatchedFrameCount;
		UINT32		ui32MatchingFrameDuration;
		UINT32		ui32TotalFrameCount;
	} Debug;
};

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
static SYNC_T gsPts[VDISP_NUM_OF_CHANNEL];
static BOOLEAN bDualVsyncForProgFrame = FALSE;
static UINT32 u32PreStc[VDISP_NUM_OF_CHANNEL];
static UINT32 u32PrePts[VDISP_NUM_OF_CHANNEL];
static BOOLEAN bWraparoundCheck[VDISP_NUM_OF_CHANNEL];
static BOOLEAN bStcDiscon[VDISP_NUM_OF_CHANNEL];
static BOOLEAN bNoPCR[VDISP_NUM_OF_CHANNEL];
static UINT32 u32StcDisconCnt[VDISP_NUM_OF_CHANNEL];

static char conti_string[PTS_CONTINUITY_MAX][PTS_CONTINUITY_MAX_STR_LEN] =
{
	[PTS_CONTINUITY_NONE]		= "NONE",
	[PTS_CONTINUITY_NORMAL]		= "NORMAL",
	[PTS_CONTINUITY_SAME]		= "SAME",
	[PTS_CONTINUITY_JITTER]		= "JITTER",
	[PTS_CONTINUITY_WRAPAROUND]	= "WRAPAROUND",
	[PTS_CONTINUITY_INVALID_STC] = "INVAL STC"
};

char azMatchModeName[STC_PTS_MAX][STC_PTS_MAX_STR_LEN] =
{
	[STC_PTS_NONE]  			= "NONE",
	[STC_PTS_DISCARD]           = "DISCARD",
	[STC_PTS_SMOOTH_DISCARD]    = "SMOOTH DISCARD",
	[STC_PTS_MATCHED]           = "MATCHED",
	[STC_PTS_SMOOTH_WAITING]    = "SMOOTH WAITING",
	[STC_PTS_WAITING]           = "WAITING",
	[STC_PTS_FREERUN]           = "FREERUN"
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
*
* @return
*
********************************************************************************
*/
#if 0
static void _PTS_Set_AVLipSyncBase(UINT8 ui8SyncCh, UINT32 ui32BaseTime, UINT32 ui32BasePTS)
{
	UINT8	bUseGstc = gsPts[ui8SyncCh].Config.bUseGstc;

	if(bUseGstc == FALSE)
	{
		log_error("[PTS%d][Err] Not File Play Channel, %s\n", ui8SyncCh, __FUNCTION__ );
		return;
	}

	if( ((ui32BaseTime != 0xFFFFFFFF) && (ui32BasePTS == 0xFFFFFFFF)) &&
		((ui32BaseTime == 0xFFFFFFFF) && (ui32BasePTS != 0xFFFFFFFF)) )
	{
		log_error("[PTS%d][ERR] Set Base Time:0x%08X, PTS:0x%08X, %s\n",
				ui8SyncCh, ui32BaseTime, ui32BasePTS, __FUNCTION__);
		return;
	}

	log_noti ("pts%d, set basetime %08x, basePTS %08x\n", ui8SyncCh,
			ui32BaseTime, ui32BasePTS);

	gsPts[ui8SyncCh].Rate.ui32BaseTime = ui32BaseTime;
	gsPts[ui8SyncCh].Rate.ui32BasePTS = ui32BasePTS;
}
#endif

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
void PTS_Reset(SYNC_T *pstSync)
{
	if( pstSync == NULL )
	{
		log_error("[PTS][Err] null pointer %x %s\n", (UINT32)pstSync, __FUNCTION__ );
		return;
	}

	log_noti("[PTS%d][DBG] %s\n", pstSync->ui8SyncCh, __FUNCTION__ );

	pstSync->u32nFrame = 0;

	// Pic
	pstSync->ui32PTS_Prev = 0xFFFFFFFF;
	pstSync->ui32STC_Prev = 0xFFFFFFFF;
	pstSync->ePtsCont = PTS_CONTINUITY_NORMAL;
	pstSync->u8DiscontCnt = 0;

	pstSync->bSmoothOn = FALSE;
	pstSync->u32SmWaitCnt = 0;
	pstSync->u32SmDiscardCnt = 0;

	pstSync->ui32FrameSkipCount = 0;
	pstSync->ui32PtsContinuityCount = 0;
	pstSync->ui32ContinuousFrameCount = 0;
	pstSync->i32SyncDiff = 0;

	pstSync->u32EmptyCnt10 = 0;
	pstSync->u32AdpMaxQLen = 1;
	pstSync->u32AdpOverCnt = 0;
	pstSync->u32QLen = 0;

	pstSync->bHighResolution = FALSE;

	pstSync->Rate.ui32DqPopRateRes = 0;
	pstSync->Rate.ui32DqPopRateDiv = 1;
	pstSync->Rate.ui32PtsRateRes = 0;
	pstSync->Rate.ui32PtsRateDiv = 1;
	pstSync->Rate.ui32BaseTime = 0xFFFFFFFF;
	pstSync->Rate.ui32BasePTS = 0xFFFFFFFF;
	pstSync->Rate.ui32PauseTime = 0xFFFFFFFF;
	pstSync->Rate.bInterlaced = TRUE;

	pstSync->Debug.ui32LogTick_GetNew = 0;
	pstSync->Debug.ui32LogTick_GetNewNo = 0;
	pstSync->Debug.ui32LogTick_Noti = 0x40;
	pstSync->Debug.ui32LogTick_Match = 0x80;
	pstSync->Debug.ui32LogTick_Pause = 0;

	pstSync->Debug.ui32MatchedFrameCount = 0;
	pstSync->Debug.ui32MatchingFrameDuration = 0;
	pstSync->Debug.ui32TotalFrameCount = 0;
}

SYNC_T* PTS_GetHandler(UINT8 ui8SyncCh)
{
	if( ui8SyncCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[PTS] wrong ch num %d\n", ui8SyncCh);
		return NULL;
	}

	gsPts[ui8SyncCh].ui8SyncCh = ui8SyncCh;

	return &gsPts[ui8SyncCh];
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
void PTS_Init(void)
{
	SYNC_T *pstSync;
	UINT8	ui8SyncCh;

	bDualVsyncForProgFrame = lx_chip_rev() < LX_CHIP_REV(H13, B0);

	VDEC_RATE_Init();

	log_noti("[PTS][DBG] PTS init: 0x%X, %s\n", (UINT32)gsPts, __FUNCTION__ );

	for( ui8SyncCh = 0; ui8SyncCh < VDISP_NUM_OF_CHANNEL; ui8SyncCh++ )
	{
		pstSync = PTS_GetHandler(ui8SyncCh);
		if(pstSync == NULL)
		{
			log_error("[PTS%d] fail to get handler\n", ui8SyncCh);
			break;
		}

		pstSync->ui8SyncCh = ui8SyncCh;
		pstSync->Config.bUseGstc = FALSE;
		pstSync->Config.eMatchMode = PTS_MATCH_ENABLE;
		pstSync->Config.ui32DisplayOffset_ms = 0x0;
		pstSync->Config.bIsDualDecoding = FALSE;

		PTS_Reset(pstSync);
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
SYNC_T* PTS_Open(UINT8 ui8SyncCh, BOOLEAN bUseGstc, UINT32 ui32DisplayOffset_ms, BOOLEAN bIsDualDecoding, PTS_MATCH_MODE_E eMatchMode)
{
	SYNC_T *pstSync;

	log_noti("[PTS%d][DBG] Display Offset: %d Dual? %d MatchMode? %d\n", ui8SyncCh,
			ui32DisplayOffset_ms, bIsDualDecoding, eMatchMode );

	pstSync = PTS_GetHandler(ui8SyncCh);
	if( pstSync == NULL )
	{
		log_error("[PTS%d] fail to get handler!!\n", ui8SyncCh);
		return NULL;
	}

	pstSync->Config.bUseGstc = bUseGstc;
	pstSync->Config.ui32DisplayOffset_ms = ui32DisplayOffset_ms;
	pstSync->Config.bIsDualDecoding = bIsDualDecoding;

	u32PreStc[ui8SyncCh] = 0xffffffff;
	u32PrePts[ui8SyncCh] = 0xffffffff;
	bWraparoundCheck[ui8SyncCh] = FALSE;
	bStcDiscon[ui8SyncCh] = FALSE;
	bNoPCR[ui8SyncCh] = FALSE;

	switch( eMatchMode )
	{
	case PTS_MATCH_ENABLE :
	case PTS_MATCH_FREERUN_BASED_SYNC :
	case PTS_MATCH_FREERUN_IGNORE_SYNC :
	case PTS_MATCH_ADAPTIVE_FREERUN :
		pstSync->Config.eMatchMode = eMatchMode;
		break;
	default :
		log_error("[PTS%d][Err] Match Mode:%d, %s\n", ui8SyncCh, eMatchMode, __FUNCTION__ );
	}

	PTS_Reset(pstSync);

	VDEC_RATE_Reset(ui8SyncCh);

	return pstSync;
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
void PTS_Close(SYNC_T *pstSync)
{
	if( pstSync == NULL )
	{
		log_error("[PTS][Err] NULL handler %s\n", __FUNCTION__ );
		return;
	}

	if(pstSync->ui8SyncCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[PTS%d][Err] %s\n", pstSync->ui8SyncCh, __FUNCTION__ );
		return;
	}

	log_noti("[PTS%d][DBG] %s\n", pstSync->ui8SyncCh, __FUNCTION__ );

	PTS_Reset(pstSync);

	pstSync->Config.eMatchMode = PTS_MATCH_ENABLE;
	pstSync->Config.ui32DisplayOffset_ms = 0x0;
	pstSync->Config.bIsDualDecoding = FALSE;
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
void PTS_Debug_Set_DisplayOffset(SYNC_T *pstSync, UINT32 ui32DisplayOffset_ms)
{
	if( pstSync == NULL )
	{
		log_error("[PTS] null pointer, %s\n", __FUNCTION__ );
		return;
	}

	log_noti("[PTS%d][DBG] DisplayOffset: %dms, %s\n", pstSync->ui8SyncCh,
			ui32DisplayOffset_ms, __FUNCTION__);

	pstSync->Config.ui32DisplayOffset_ms = ui32DisplayOffset_ms;
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
void PTS_SetStcDiscont(SYNC_T *pstSync)
{
/*
	if( pstSync->u8DiscontCnt > 32 )
		log_error("Too big discontinuity count %d\n", pstSync->u8DiscontCnt);

	pstSync->u8DiscontCnt++;
	log_debug("discontinuity count %d\n", pstSync->u8DiscontCnt);
*/
}

BOOLEAN PTS_IsDiscont(SYNC_T *pstSync)
{
	if( pstSync == NULL )
	{
		log_error("[PTS] wrong handler %X, %s\n", (UINT32)pstSync, __FUNCTION__ );
		return FALSE;
	}

	return bStcDiscon[pstSync->ui8SyncCh];
}

void PTS_Set_MatchMode(SYNC_T *pstSync, PTS_MATCH_MODE_E eMatchMode)
{
	if( pstSync == NULL )
	{
		log_error("[PTS] wrong handler %X, %s\n", (UINT32)pstSync, __FUNCTION__ );
		return;
	}

	log_noti("[PTS%d][DBG] %s\n", pstSync->ui8SyncCh, __FUNCTION__);

	switch( eMatchMode )
	{
	case PTS_MATCH_ENABLE :
	case PTS_MATCH_FREERUN_BASED_SYNC :
	case PTS_MATCH_FREERUN_IGNORE_SYNC :
	case PTS_MATCH_ADAPTIVE_FREERUN :
		pstSync->Config.eMatchMode = eMatchMode;
		break;
	default :
		log_error("[PTS%d][Err] Match Mode:%d, %s\n", pstSync->ui8SyncCh,
				eMatchMode, __FUNCTION__ );
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
void PTS_Set_BaseTime(SYNC_T *pstSync, UINT32 ui32BaseTime, UINT32 ui32BasePTS)
{
	if( pstSync == NULL )
	{
		log_error("[PTS] wrong handler %X, %s\n", (UINT32)pstSync, __FUNCTION__ );
		return;
	}

	if( ui32BasePTS == VDEC_UNKNOWN_PTS )
	{
		log_noti("[PTS%d][DBG] Unknwon PTS, %s\n", pstSync->ui8SyncCh, __FUNCTION__ );
		return;
	}

	ui32BaseTime &= 0x0FFFFFFF;
	ui32BasePTS &= 0x0FFFFFFF;

	if( pstSync->Config.bUseGstc )
	{
		log_noti("[PTS%d] Pre BaseTime:0x%08X, PTS:0x%08X\n", pstSync->ui8SyncCh,
				pstSync->Rate.ui32BaseTime,
				pstSync->Rate.ui32BasePTS);
		log_noti("[PTS%d]    Set new -> BaseTime:0x%08X, PTS:0x%08X\n", pstSync->ui8SyncCh,
				ui32BaseTime, ui32BasePTS);

		//_PTS_Set_AVLipSyncBase( pstSync->ui8SyncCh, ui32BaseTime, ui32BasePTS);
		pstSync->Rate.ui32BaseTime = ui32BaseTime;
		pstSync->Rate.ui32BasePTS = ui32BasePTS;
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
void PTS_Get_BaseTime(SYNC_T *pstSync, UINT32 *pui32BaseTime, UINT32 *pui32BasePTS )
{
	*pui32BaseTime = pstSync->Rate.ui32BaseTime;
	*pui32BasePTS = pstSync->Rate.ui32BasePTS;
}

SINT32 PTS_GetDiff(SYNC_T *pstSync)
{
	return pstSync->i32SyncDiff;
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
void PTS_ClearFrame(UINT8 ui8SyncCh, S_DISPQ_BUF_T *buffer)
{
	S_DISPCLEARQ_BUF_T sDisClearBuf;

	sDisClearBuf.ui32FrameIdx = buffer->ui32FrameIdx;

	log_user2("Sync:%d Push ClrQ %d\n", ui8SyncCh, sDisClearBuf.ui32FrameIdx);

	//DISP_CLEAR_Q_Push(ui8SyncCh, &sDisClearBuf);
	if (buffer->displayed_callback)
		buffer->displayed_callback (buffer->displayed_callback_arg, buffer);
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
void PTS_Flush(SYNC_T *pstSync)
{
	S_DISPQ_BUF_T sPopDisBuf;
	UINT8 ui8SyncCh = pstSync->ui8SyncCh;

	log_noti("[PTS%d] Flush: Occupancy: %d\n", ui8SyncCh, DISP_Q_NumActive(ui8SyncCh) );

	VDEC_RATE_Flush(ui8SyncCh);

	// Pic
	pstSync->ui32PTS_Prev = 0xFFFFFFFF;
	pstSync->ui32STC_Prev = 0xFFFFFFFF;
	pstSync->ePtsCont = PTS_CONTINUITY_NORMAL;
	pstSync->u8DiscontCnt = 0;

	pstSync->ui32FrameSkipCount = 0;
	pstSync->ui32PtsContinuityCount = 0;
	pstSync->ui32ContinuousFrameCount = 0;
	pstSync->i32SyncDiff = 0;

	while( DISP_Q_Pop( ui8SyncCh, &sPopDisBuf ) == TRUE )
	{
		sPopDisBuf.bDispResult = FALSE;
		PTS_ClearFrame( ui8SyncCh, &sPopDisBuf );

		pstSync->Debug.ui32TotalFrameCount++;
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
static BOOLEAN _PTS_WithinRange(UINT32 ui32STC_Start, UINT32 ui32STC_End, UINT32 ui32PTS)
{
	if( ui32STC_Start <= ui32STC_End )
	{
		if( (ui32PTS > ui32STC_Start) &&
			(ui32PTS <= ui32STC_End) )
			return TRUE;
	}
	else
	{
		if( (ui32PTS > ui32STC_Start) ||
			(ui32PTS <= ui32STC_End) )
			return TRUE;
	}

	return FALSE;
}

void PTS_WraparoundCheck(UINT8 ui8SyncCh, UINT32 ui32STC)
{
	UINT32 u32Start, u32End;
	static UINT32 u32SameStcCnt[VDISP_NUM_OF_CHANNEL];

	// No PCR check, No STC change check
	if( u32PreStc[ui8SyncCh] == ui32STC )
	{
		if(u32SameStcCnt[ui8SyncCh] > 10)
		{
			static UINT32 u32DbgCnt;

			if( !(u32DbgCnt++ % 900) )
					log_noti("PTS%d: wrong stc(pre:%d cur:%d)\n", ui8SyncCh,
							u32PreStc[ui8SyncCh], ui32STC);

			bNoPCR[ui8SyncCh] = TRUE;
			return;
		}
		else
			u32SameStcCnt[ui8SyncCh]++;
	}
	else
	{
		bNoPCR[ui8SyncCh] = FALSE;
		u32SameStcCnt[ui8SyncCh] = 0;
	}

	if( !bWraparoundCheck[ui8SyncCh] )
		return;

	if( u32PreStc[ui8SyncCh] == 0xffffffff )
		goto inval_wa_check_exit;

	if( bStcDiscon[ui8SyncCh] == FALSE )
	{
		u32Start = (u32PreStc[ui8SyncCh]-18000) & 0x0fffffff;
		u32End = (u32PreStc[ui8SyncCh]+45000) & 0x0fffffff;

		if( _PTS_WithinRange(u32Start, u32End, ui32STC) != TRUE )
		{
			log_noti("[pts%d] start wrap around %d->%d %d %d\n",
					ui8SyncCh, u32PreStc[ui8SyncCh], ui32STC, u32Start, u32End);
			bStcDiscon[ui8SyncCh] = TRUE;
			u32StcDisconCnt[ui8SyncCh] = 0;
		}
	}

inval_wa_check_exit:

	u32PreStc[ui8SyncCh] = ui32STC;
}

static BOOLEAN pts_invalid_stc_check(UINT8 ui8SyncCh, UINT32 ui32PTS, UINT32 ui32STC)
{
	UINT32 u32Start, u32End;

	if( bNoPCR[ui8SyncCh] )
		return TRUE;

	// Handling Wrap Around
	if( u32PrePts[ui8SyncCh] == 0xffffffff )
		goto inval_stc_check_exit;

	if( bStcDiscon[ui8SyncCh] )
	{
		u32Start = (u32PrePts[ui8SyncCh]-9000) & 0x0fffffff;
		u32End = (u32PrePts[ui8SyncCh]+27000) & 0x0fffffff;

		if( _PTS_WithinRange(u32Start, u32End, ui32PTS) != TRUE ||
				_PTS_WithinRange((ui32STC-180000)&0x0fffffff,
					(ui32STC+180000)&0x0fffffff, ui32PTS) 	)
		{
			log_noti("[pts%d] end wrap around\n", ui8SyncCh);
			bStcDiscon[ui8SyncCh] = FALSE;
		}

		u32StcDisconCnt[ui8SyncCh]++;
		if( u32StcDisconCnt[ui8SyncCh] > 60 )
		{
			log_noti("[pts%d] end wrap around forcedly %d\n", ui8SyncCh,
					u32StcDisconCnt[ui8SyncCh]);
			bStcDiscon[ui8SyncCh] = FALSE;
		}
	}

inval_stc_check_exit:

	u32PrePts[ui8SyncCh] = ui32PTS;

	return bStcDiscon[ui8SyncCh];

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
static PTS_CONTINUITY_E _PTS_CheckPtsDiscont(SYNC_T *pstSync, UINT32 ui32PTS_Prev, UINT32 ui32PTS_Curr, UINT32 ui32STC)
{
	UINT32		ui32JitterDuration;
	UINT32		ui32JitterBoundary;
	UINT32		ui32NormalDuration;
	UINT32		ui32NormalBoundary;
	UINT32		ui32FrameDuration;
	SINT32 		i32Speed;
	static UINT32 u32LogCnt = 0;
	UINT8 		ui8SyncCh = pstSync->ui8SyncCh;
	PTS_CONTINUITY_E	ePtsCont = PTS_CONTINUITY_NONE;
	static PTS_CONTINUITY_E	ePreCont[VDISP_NUM_OF_CHANNEL];

	if( pts_invalid_stc_check(ui8SyncCh, ui32PTS_Curr, ui32STC) )
		return PTS_CONTINUITY_INVALID_STC;
/*
	if( pstSync->u8DiscontCnt )
	{
		static UINT32 logCnt;
		if( !(logCnt++ % 100) )
			log_noti("Discontinous STC\n");
		return PTS_CONTINUITY_INVALID_STC;
	}
*/
	if( ui32PTS_Prev == 0xFFFFFFFF )
		return PTS_CONTINUITY_NORMAL;

	ui32FrameDuration = VDEC_RATE_GetFrameRateDuration(ui8SyncCh);
	if( ui32FrameDuration == 0 )
		return PTS_CONTINUITY_NORMAL;

	ui32PTS_Prev &= 0x0fffffff;
	ui32PTS_Curr &= 0x0fffffff;

	i32Speed = VDEC_RATE_Get_Speed(ui8SyncCh);

	if( i32Speed == 1000 )
		ui32JitterDuration = ui32FrameDuration * PTS_CONTINUITY_DURATION;
	else
	{
		if( i32Speed < 0 )
			return PTS_CONTINUITY_NORMAL;

		ui32JitterDuration = ui32FrameDuration * PTS_CONTINUITY_DURATION * i32Speed / 1000;
	}

	if( ui32PTS_Prev>= ui32JitterDuration )
		ui32JitterBoundary = ui32PTS_Prev - ui32JitterDuration;
	else
		ui32JitterBoundary = ui32PTS_Prev + 0x0FFFFFFF - ui32JitterDuration;

	if( i32Speed == 1000 )
		ui32NormalDuration = ui32FrameDuration * PTS_CONTINUITY_DURATION;
	else
		ui32NormalDuration = ui32FrameDuration * PTS_CONTINUITY_DURATION * i32Speed / 1000;
	ui32NormalBoundary = ui32PTS_Prev + ui32NormalDuration;
	ui32NormalBoundary &= 0x0FFFFFFF;

	if( _PTS_WithinRange(ui32JitterBoundary, ui32PTS_Prev, ui32PTS_Curr) == TRUE )
	{
		if( ui32PTS_Prev == ui32PTS_Curr )
		{
			ePtsCont = PTS_CONTINUITY_SAME;
			if( !((u32LogCnt++) % 30) )
				log_noti("[PTS%d][Warn:0x%X] PTS Discontin - Same PTS(0x%X), Occupancy: %d, FrameDuration:0x%X\n",
						ui8SyncCh, ui32STC, ui32PTS_Curr, DISP_Q_NumActive(ui8SyncCh), ui32FrameDuration );
		}
		else
		{
			ePtsCont = PTS_CONTINUITY_JITTER;

			if( !((u32LogCnt++) % 30) )
				log_warning("[PTS%d][Warn:0x%X] PTS Discontinuity - Jitter PTS(Prev:0x%X, Curr:0x%X), Occupancy: %d, FrameDuration:0x%X\n",
						ui8SyncCh, ui32STC, ui32PTS_Prev, ui32PTS_Curr,
						DISP_Q_NumActive(ui8SyncCh), ui32FrameDuration );
		}
	}
	else if( _PTS_WithinRange(ui32PTS_Prev, ui32NormalBoundary, ui32PTS_Curr) == TRUE )
	{
		ePtsCont = PTS_CONTINUITY_NORMAL;
		u32LogCnt = 0;
	}
	else
	{
		ePtsCont = PTS_CONTINUITY_WRAPAROUND;
		log_noti("[PTS%d][Warn:0x%X] PTS Discontinuity - Wrap Around PTS(Prev:0x%X, Curr:0x%X), Occupancy: %d, FrameDuration:0x%X\n",
				ui8SyncCh, ui32STC, ui32PTS_Prev, ui32PTS_Curr,
				DISP_Q_NumActive(ui8SyncCh), ui32FrameDuration );
	}

	if(ePtsCont != ePreCont[ui8SyncCh])
		log_noti("pts conti %s => %s\n",conti_string[ePreCont[ui8SyncCh]],
				conti_string[ePtsCont]);

	ePreCont[ui8SyncCh] = ePtsCont;

	return ePtsCont;
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
static PTS_MATCH_E _PTS_CheckStcPtsMatch(SYNC_T *pstSync, UINT32 ui32STC, UINT32 ui32PTS, UINT32 ui32DisplayOffset_ms, BOOLEAN bSmoothing)
{
	UINT32		ui32DiscardDuration;
	UINT32		ui32MatchedDuration;
	UINT32		ui32WaitingDuration;
	UINT32		ui32SmthWaitingDuration;
	UINT32		ui32SmthDiscardDuration;

	UINT32		u32DiscardBndary;
	UINT32		u32MatchBndary;
	UINT32		u32MatchBndaryEnd;
	UINT32		u32WaitBndary;
	UINT32		u32SmthWaitBndary;
	UINT32		u32SmthDiscardBndary;

	UINT32		ui32StreamTime;
	UINT32		u32CompenPts;
	PTS_MATCH_E	eStcPtsMatched = STC_PTS_NONE;
	UINT32		ui32DisplayOffset_90kTick;
	SINT32 		i32Speed, i32SyncDiff;
	UINT32		ui32FrameDuration;
	UINT8 ui8SyncCh = pstSync->ui8SyncCh;
	SINT32		i32PTS_Offset;

	bWraparoundCheck[ui8SyncCh] = TRUE;

	i32Speed = VDEC_RATE_Get_Speed(ui8SyncCh);
	if( i32Speed == 0 )
	{
		if( (pstSync->Debug.ui32LogTick_Pause % 10) == 0 )
			log_noti("[PTS%d][DBG:0x%X] STC Matched - Speed: %d, PTS:0x%X, STC:0x%X, Occupancy: %d\n", ui8SyncCh, ui32STC, i32Speed, ui32PTS, ui32STC, DISP_Q_NumActive(ui8SyncCh));
		pstSync->Debug.ui32LogTick_Pause++;

		return STC_PTS_WAITING;
	}
	else
	{
		pstSync->Debug.ui32LogTick_Pause = 0;
	}

	ui32FrameDuration = VDEC_RATE_GetFrameRateDuration(ui8SyncCh);
	if( ui32FrameDuration == 0 )
	{
		log_error("[PTS%d][Err:0x%X] No Frame Rate, %s\n", ui8SyncCh, ui32STC, __FUNCTION__);
		return STC_PTS_FREERUN;
	}

	ui32StreamTime = ui32PTS & 0x0fffffff;
	if (vdec_display_offset)
		ui32DisplayOffset_90kTick = vdec_display_offset * 90;
	else
		ui32DisplayOffset_90kTick = ui32DisplayOffset_ms * 90;		// = Xms * 90,000 / 1,000

	if( pstSync->Config.bUseGstc )
	{
		UINT32		ui32BaseTime;
		UINT32		ui32BasePTS;

		if( (pstSync->Rate.ui32BaseTime == 0xFFFFFFFF) ||
				(pstSync->Rate.ui32BasePTS == 0xFFFFFFFF) )
		{
			log_noti("pts%d, cut basetime %08x, basePTS %08x\n", ui8SyncCh, ui32STC, ui32PTS);
			PTS_Set_BaseTime(pstSync, ui32STC, ui32PTS);
		}

		ui32BaseTime = pstSync->Rate.ui32BaseTime;
		ui32BasePTS = pstSync->Rate.ui32BasePTS;

		// TODO: add more condition that consider constant time for duration
		//   just additionally more than considering nums of frames
		if( i32Speed == 1000 )
		{
			i32PTS_Offset = PTS_GET_PTS_OFFSET( ui32BasePTS, ui32StreamTime );
			u32CompenPts = PTS_CHECK_PTS_WRAPAROUND(ui32BaseTime + i32PTS_Offset +
					ui32DisplayOffset_90kTick );
			ui32DiscardDuration = ui32FrameDuration * PTS_STC_DISCARD_DECISION_DURATION;
			ui32SmthDiscardDuration = ui32FrameDuration * PTS_STC_SMOOTH_DISCARD_DURATION;
			ui32MatchedDuration = ui32FrameDuration;
			ui32SmthWaitingDuration = ui32FrameDuration * PTS_STC_SMOOTH_WAITING_DURATION;
			ui32WaitingDuration = ui32FrameDuration * PTS_STC_WAITING_DECISION_DURATION;
		}
		else
		{
			UINT32 u32Speed;
			if( i32Speed > 0 )
			{
				i32PTS_Offset = (SINT32)PTS_GET_PTS_OFFSET(ui32BasePTS, ui32StreamTime);
				u32Speed = i32Speed;
			}
			else
			{
				i32PTS_Offset = -((SINT32)PTS_GET_PTS_OFFSET(ui32StreamTime, ui32BasePTS));
				u32Speed = -i32Speed;
			}
			i32PTS_Offset = i32PTS_Offset / i32Speed * 1000;
			u32CompenPts = PTS_CHECK_PTS_WRAPAROUND(ui32BaseTime + i32PTS_Offset
				+ ui32DisplayOffset_90kTick );
			ui32DiscardDuration = ui32FrameDuration * PTS_STC_DISCARD_DECISION_DURATION
				* u32Speed / 1000;
			ui32SmthDiscardDuration = ui32FrameDuration * PTS_STC_SMOOTH_DISCARD_DURATION
				* u32Speed / 1000;
			ui32MatchedDuration = ui32FrameDuration * u32Speed / 1000;
			ui32SmthWaitingDuration = ui32FrameDuration * PTS_STC_SMOOTH_WAITING_DURATION
				* u32Speed / 1000;
			ui32WaitingDuration = ui32FrameDuration * PTS_STC_WAITING_DECISION_DURATION *
				u32Speed / 1000;

			log_debug("[PTS%d][DBG:0x%X] STC Match - Speed: %d, BaseTime: 0x%X, PTS:0x%X(0x%X), STC:0x%X, Occupancy: %d, FrameDuration:0x%X pbase %d poff %d str %d\n",
					ui8SyncCh, ui32STC, i32Speed, ui32BaseTime,
					u32CompenPts, ui32PTS, ui32STC,
					DISP_Q_NumActive(ui8SyncCh), ui32FrameDuration,
					i32PTS_Offset, ui32BasePTS, ui32StreamTime);
		}
	}
	else
	{
		u32CompenPts = PTS_CHECK_PTS_WRAPAROUND(ui32StreamTime + ui32DisplayOffset_90kTick);
		ui32DiscardDuration = ui32FrameDuration * PTS_STC_DISCARD_DECISION_DURATION_LIVE;
		ui32SmthDiscardDuration = ui32FrameDuration * PTS_STC_SMOOTH_DISCARD_DURATION;
		ui32MatchedDuration = ui32FrameDuration;
		ui32SmthWaitingDuration = ui32FrameDuration * PTS_STC_SMOOTH_WAITING_DURATION;
		ui32WaitingDuration = ui32FrameDuration * PTS_STC_WAITING_DECISION_DURATION;
	}

	// for first frame
	if( pstSync->u32nFrame == 1 )
		ui32WaitingDuration *= 4;

	if( pstSync->Config.bIsDualDecoding == FALSE )
	{
		if( pstSync->bHighResolution == TRUE )
			ui32WaitingDuration /= 2;
	}

	u32DiscardBndary = (ui32STC - ui32DiscardDuration) & 0x0FFFFFFF;
	u32SmthDiscardBndary = (ui32STC - ui32SmthDiscardDuration) & 0x0FFFFFFF;
	u32MatchBndary = (ui32STC - 270) & 0x0FFFFFFF;
	u32MatchBndaryEnd = (ui32STC + ui32MatchedDuration - 270) & 0x0FFFFFFF;
	u32SmthWaitBndary = (ui32STC + ui32SmthWaitingDuration) & 0x0FFFFFFF;
	u32WaitBndary = (ui32STC + ui32WaitingDuration) & 0x0FFFFFFF;

	if( _PTS_WithinRange(u32MatchBndary, u32MatchBndaryEnd, u32CompenPts) == TRUE )
		eStcPtsMatched = STC_PTS_MATCHED;
	else if(_PTS_WithinRange(u32DiscardBndary, u32SmthDiscardBndary, u32CompenPts) == TRUE)
		eStcPtsMatched = STC_PTS_DISCARD;
	else if( _PTS_WithinRange(u32SmthDiscardBndary, u32MatchBndary,	u32CompenPts) == TRUE )
		eStcPtsMatched = STC_PTS_SMOOTH_DISCARD;
	else if( _PTS_WithinRange(u32MatchBndaryEnd, u32SmthWaitBndary, u32CompenPts) == TRUE )
		eStcPtsMatched = STC_PTS_SMOOTH_WAITING;
	else if( _PTS_WithinRange(u32SmthWaitBndary, u32WaitBndary,	u32CompenPts) == TRUE )
		eStcPtsMatched = STC_PTS_WAITING;
	else
		eStcPtsMatched = STC_PTS_FREERUN;

	if( bSmoothing == FALSE )
	{
		if( eStcPtsMatched == STC_PTS_SMOOTH_WAITING )
			eStcPtsMatched = STC_PTS_WAITING;
		else if( eStcPtsMatched == STC_PTS_SMOOTH_DISCARD )
			eStcPtsMatched = STC_PTS_DISCARD;
	}

	if( eStcPtsMatched != STC_PTS_FREERUN )
	{
		i32SyncDiff = ui32STC - u32CompenPts;
		if(i32SyncDiff>0x7FFFFFF)
			i32SyncDiff-=0x10000000;
		else if(i32SyncDiff< -0x7FFFFFF)
			i32SyncDiff+=0x10000000;
		pstSync->i32SyncDiff = i32SyncDiff;
	}
	else
		pstSync->i32SyncDiff = 0;

	log_user1("[PTS%d] %s SMTH%d PTS:%d(+%d), STC:%d dif:%d Qlen %d, Duration:0x%X\n",
			ui8SyncCh, azMatchModeName[eStcPtsMatched], bSmoothing, ui32PTS,
			u32CompenPts, ui32STC, pstSync->i32SyncDiff, DISP_Q_NumActive(ui8SyncCh),
			ui32FrameDuration );

	pstSync->Debug.ui32LogTick_Match++;
	if( pstSync->Debug.ui32LogTick_Match == 0x100 )
	{
		log_noti(
				"[PTS%d][DBG:0x%X] speed %d Base(%d %d) (%d/%d) Offset90K:%d PTS:0x%X(0x%X) STC:0x%X Diff:%dms\n",
				ui8SyncCh, ui32STC,
				i32Speed,
				pstSync->Rate.ui32BaseTime,
				pstSync->Rate.ui32BasePTS,
				pstSync->Debug.ui32MatchedFrameCount,
				pstSync->Debug.ui32MatchingFrameDuration,
				ui32DisplayOffset_90kTick,
				ui32PTS, u32CompenPts, ui32STC, ((SINT32)ui32STC - (SINT32)u32CompenPts) / 90);

		pstSync->Debug.ui32LogTick_Match = 0;
		pstSync->Debug.ui32MatchedFrameCount = 0;
		pstSync->Debug.ui32MatchingFrameDuration = 0;
	}

	return eStcPtsMatched;
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
static PTS_MATCH_E _PTS_DecideFrameMatch(SYNC_T *pstSync, PTS_CONTINUITY_E ePtsCont, UINT32 ui32STC, UINT32 ui32PTS_Prev, UINT32 ui32PTS, UINT32 ui32DisplayOffset_ms, BOOLEAN bSmoothing)
{
	PTS_MATCH_E	eStcPtsMatched = STC_PTS_NONE;
	static PTS_MATCH_E ePreStcMatch[VDISP_NUM_OF_CHANNEL];
	UINT8 ui8SyncCh = pstSync->ui8SyncCh;

	switch( ePtsCont )
	{
	case PTS_CONTINUITY_SAME :
	case PTS_CONTINUITY_NORMAL :
		eStcPtsMatched = _PTS_CheckStcPtsMatch(pstSync, ui32STC, ui32PTS,
				ui32DisplayOffset_ms, bSmoothing);
		break;
	case PTS_CONTINUITY_JITTER :
		pstSync->ui32PtsContinuityCount = 0;
	case PTS_CONTINUITY_INVALID_STC :
	case PTS_CONTINUITY_WRAPAROUND :
		log_debug("[PTS%d][Warning:0x%X] PTS Continuity(%s) (Running:%d) - Prev:0x%X, Curr:0x%X, STC:0x%X, Occupancy: %d\n",
				ui8SyncCh, ui32STC, conti_string[(UINT32)ePtsCont], pstSync->ePtsCont,
				ui32PTS_Prev, ui32PTS, ui32STC, DISP_Q_NumActive(ui8SyncCh) );
		eStcPtsMatched = STC_PTS_FREERUN;
		break;

	default :
		log_error("[PTS%d][Err:0x%X] PTS eMatch %d, %s\n",
				ui8SyncCh, ui32STC, eStcPtsMatched, __FUNCTION__ );
	}

	if( ePtsCont == PTS_CONTINUITY_NORMAL )
		pstSync->ui32PtsContinuityCount++;
	else
		pstSync->ui32PtsContinuityCount = 0;

	if( pstSync->ePtsCont == PTS_CONTINUITY_JITTER )
	{
		if( pstSync->ui32PtsContinuityCount >= PTS_CONTINUITY_COUNT )
		{
			log_noti(
					"[PTS%d] Restore Normal State from Jitter PTS, STC:0x%X, DispQ len: %d\n",
					ui8SyncCh, ui32STC, DISP_Q_NumActive(ui8SyncCh) );
			pstSync->ePtsCont = PTS_CONTINUITY_NORMAL;
		}
		else
		{
			log_debug("[PTS%d] Jitter freerun, cnt%d\n", ui8SyncCh,
					pstSync->ui32PtsContinuityCount);
			pstSync->ePtsCont = PTS_CONTINUITY_JITTER;
			eStcPtsMatched = STC_PTS_FREERUN;
		}
	}
	else
	{
		pstSync->ePtsCont = ePtsCont;
	}

	if( eStcPtsMatched != ePreStcMatch[ui8SyncCh] )
		log_noti("[PTS%d][DBG] ContiState %s, Stc Match %s -> %s\n", ui8SyncCh,
				conti_string[(UINT32)ePtsCont],
				azMatchModeName[ePreStcMatch[ui8SyncCh]],
				azMatchModeName[eStcPtsMatched] );

	ePreStcMatch[ui8SyncCh] = eStcPtsMatched;

	return eStcPtsMatched;
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
UINT32 PTS_CheckFrame(SYNC_T *pstSync, S_DISPQ_BUF_T *pstDqFrame)
{
	UINT32		u32Ret = 0;
	UINT32		ui32PTS_Curr;
	UINT32		u32FrameRate;
	UINT8 ui8SyncCh = pstSync->ui8SyncCh;

	if( bDualVsyncForProgFrame && DISPQ_SCAN_PROG == pstDqFrame->ui32DisplayInfo )
		pstDqFrame->ui32DisplayPeriod = 2;

	// PTS check
	ui32PTS_Curr = pstDqFrame->ui32PTS;
	if( ui32PTS_Curr == VDEC_UNKNOWN_PTS )
		ui32PTS_Curr = pstSync->ui32PTS_Prev;
	else
		pstSync->ui32PTS_Prev = ui32PTS_Curr;

	if( ui32PTS_Curr != 0xFFFFFFFF )
		VDEC_RATE_UpdateFrameRate_byPTS(ui8SyncCh, pstDqFrame->ui32PTS,
				(UINT32 *)&pstSync->Rate.ui32PtsRateRes,
				(UINT32 *)&pstSync->Rate.ui32PtsRateDiv);

	pstSync->Rate.bInterlaced = pstDqFrame->ui32DisplayInfo == DISPQ_SCAN_PROG?FALSE:TRUE;
/*
	if( pstDqFrame->bDiscont )
		if( pstSync->u8DiscontCnt == 0 )
			log_error("Discontinuity cont is zero\n");
		else
			pstSync->u8DiscontCnt--;
*/
	if( pstSync->u32nFrame < 0xFFFFFFFF )
		pstSync->u32nFrame++;
	// Rate Check

	// Rate Constraint Check
	if( pstDqFrame->ui32FrameRateDiv != 0 )
	{
		u32FrameRate = pstDqFrame->ui32FrameRateRes/pstDqFrame->ui32FrameRateDiv;
		if( pstDqFrame->ui32DisplayInfo == DISPQ_SCAN_PROG )
		{
			UINT32 picsize = pstDqFrame->ui32PicWidth * pstDqFrame->ui32PicHeight;

			if( u32FrameRate > 30 && picsize >= 1920*1080 &&
					pstDqFrame->ui32LR_Order == DISPQ_3D_FRAME_NONE )
				pstDqFrame->ui32FrameRateRes = pstDqFrame->ui32FrameRateDiv * 30;
		}
		else
		{
			if( u32FrameRate > 30 )
			{
				if( u32FrameRate >= 50 && u32FrameRate <= 60 )
					pstDqFrame->ui32FrameRateRes /= 2;
				else
					pstDqFrame->ui32FrameRateRes = pstDqFrame->ui32FrameRateDiv * 30;
			}
		}
	}

	return u32Ret;
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
UINT32	PTS_GetDisplayOffsetMs(SYNC_T *pstSync)
{
	UINT32 ui32FrameDuration;
	UINT32 ui32OffsetMs, u32DeDly;
	//UINT32 ui32FrameDuration;
	//UINT8  u8ScanModeFactor;

	ui32OffsetMs = pstSync->Config.ui32DisplayOffset_ms;

	//u8ScanModeFactor = pstSync->Rate.bInterlaced ? 3:1;
	//ui32FrameDuration = VDEC_RATE_GetFrameRateDuration(pstSync->ui8SyncCh);
	//ui32OffsetMs = ui32OffsetMs + 99 - ((ui32FrameDuration/90) * u8ScanModeFactor);

	ui32FrameDuration = VDEC_RATE_GetFrameRateDuration(pstSync->ui8SyncCh);

	if( pstSync->Rate.bInterlaced )
	{
		u32DeDly = ui32FrameDuration / (90 / 3 * 2) + 17;
		ui32OffsetMs = ui32OffsetMs - u32DeDly + 67;
	}
	else
	{
		if( ui32FrameDuration > 11000 )
			ui32OffsetMs -= 200;
		else
		{
			u32DeDly = ui32FrameDuration / 90 + 14;
			ui32OffsetMs = ui32OffsetMs - u32DeDly + 64;
		}
	}

	// Live for Channel Change  // Not 3D Channel
	if( pstSync->Config.bUseGstc == FALSE && pstSync->Config.bIsDualDecoding == FALSE )
	{
		// First & Second Frame
		if(	pstSync->u32nFrame <= VDEC_FAST_CHCH_FRAME &&
				pstSync->Config.ui32DisplayOffset_ms >= 100 )
		{
			ui32OffsetMs -= 100;

			log_noti("[PTS%d] DispOffset: %d --> %d for Fast Channel Change\n",
					pstSync->ui8SyncCh, pstSync->Config.ui32DisplayOffset_ms,
					ui32OffsetMs );
		}
	}

	return ui32OffsetMs;
}

void PTS_NotiCurQlen(SYNC_T *pstSync, SINT32 i32QLen)
{
	if( i32QLen == 0 )
	{
		pstSync->u32EmptyCnt10 += 30;

		if( pstSync->u32EmptyCnt10 > 40 )
		{
			if( pstSync->u32AdpMaxQLen < 4)
			{
				pstSync->u32EmptyCnt10 = 0;
				pstSync->u32AdpMaxQLen++;
				log_debug("Adp Q Len ++, %d\n", pstSync->u32AdpMaxQLen);
			}
		}
		pstSync->u32AdpOverCnt = 0;
		log_debug("Adp Empty10:%d AdpQ:%d\n", pstSync->u32EmptyCnt10, pstSync->u32AdpMaxQLen);
	}
	else
	{
		if( i32QLen > 1 )
		{
			pstSync->u32AdpOverCnt++;

			if( pstSync->u32AdpOverCnt > 10 )
			{
				if(	pstSync->u32AdpMaxQLen > 1 )
					pstSync->u32AdpMaxQLen--;

				pstSync->u32AdpOverCnt = 0;
				log_debug("Adp Q Len --, Adp:%d Q:%d\n", pstSync->u32AdpMaxQLen, i32QLen);
			}
		}
		else
			pstSync->u32AdpOverCnt = 0;

		if( pstSync->u32EmptyCnt10 )
			pstSync->u32EmptyCnt10--;
	}

	pstSync->u32QLen = (UINT32)i32QLen;
}

PTS_MATCH_E PTS_MatchCheck(SYNC_T *pstSync, UINT32 ui32PTS,	UINT32 ui32STC,
		UINT32 ui32PTS_Prev)
{
	PTS_MATCH_E			eMatch = STC_PTS_NONE;
	PTS_CONTINUITY_E	ePtsCont = PTS_CONTINUITY_NONE;
	UINT32 				ui32PTS_Curr = 0xFFFFFFFF;
	UINT32				ui32DisplayOffset_ms = 0;

	SINT32 				i32Speed;
	BOOLEAN				bSmoothing = TRUE;
	UINT8 				ui8SyncCh;

	if( pstSync == NULL )
	{
		log_error("[PTS] null pointer\n");
		return FALSE;
	}

	ui8SyncCh = pstSync->ui8SyncCh;

	i32Speed = VDEC_RATE_Get_Speed(ui8SyncCh);

	if( VDEC_RATE_IsModifiedFrameRate(ui8SyncCh) == TRUE ||
			pstSync->bSmoothOn == FALSE )
		bSmoothing = FALSE;

	ui32PTS_Curr = ui32PTS;

	switch( pstSync->Config.eMatchMode )
	{
		case PTS_MATCH_ENABLE :
		if( ui32PTS_Curr == VDEC_UNKNOWN_PTS )
		{
			eMatch = STC_PTS_FREERUN;
		}
		else
		{
			// Check PTS discontinuity
			ePtsCont = _PTS_CheckPtsDiscont(pstSync, ui32PTS_Prev, ui32PTS_Curr, ui32STC);

			ui32DisplayOffset_ms = PTS_GetDisplayOffsetMs(pstSync);

			if( (pstSync->Config.bIsDualDecoding == TRUE) || (i32Speed != 1000))
				bSmoothing = FALSE;

			eMatch = _PTS_DecideFrameMatch(pstSync,	ePtsCont, ui32STC,
					ui32PTS_Prev, ui32PTS_Curr, ui32DisplayOffset_ms, bSmoothing);
		}
		break;
		case PTS_MATCH_FREERUN_IGNORE_SYNC :
			eMatch = STC_PTS_DISCARD;
			log_user1 ("pts%d, freerun ignore sync\n", ui8SyncCh);
			break;
		case PTS_MATCH_ADAPTIVE_FREERUN :
			if( pstSync->u32QLen <= pstSync->u32AdpMaxQLen )
				eMatch = STC_PTS_FREERUN;
			else
				eMatch = STC_PTS_DISCARD;

			log_user1("pts%d: adp sync -> %s, qlen%d adp_lv%d\n", ui8SyncCh,
					azMatchModeName[eMatch], pstSync->u32QLen, pstSync->u32AdpMaxQLen );
			break;
		default :
			log_error("[PTS%d][Err] Match Mode:%d, %s\n", ui8SyncCh,
					pstSync->Config.eMatchMode, __FUNCTION__ );
		case PTS_MATCH_FREERUN_BASED_SYNC :
			eMatch = STC_PTS_FREERUN;
			break;
	}

	if( eMatch == STC_PTS_MATCHED )
	{
		if( pstSync->u32nFrame > VDEC_FAST_CHCH_FRAME)
		{
			pstSync->bSmoothOn = TRUE;
			pstSync->u32SmWaitCnt = 0;
			pstSync->u32SmDiscardCnt = 0;
		}
	}
	else if( eMatch == STC_PTS_SMOOTH_DISCARD )
	{
		pstSync->u32SmDiscardCnt++;
		eMatch = STC_PTS_DISCARD;

		if( pstSync->u32SmDiscardCnt < 4 )
			eMatch = STC_PTS_MATCHED;
		else if( pstSync->u32SmDiscardCnt < 20 )
		{
			if( pstSync->u32SmDiscardCnt&3 )
				eMatch = STC_PTS_MATCHED;
		}
		else if( pstSync->u32SmDiscardCnt < 40 )
		{
			if( pstSync->u32SmDiscardCnt&1 )
				eMatch = STC_PTS_MATCHED;
		}
		else if( pstSync->u32SmDiscardCnt < 80 )
		{
			if( !(pstSync->u32SmDiscardCnt&3) )
				eMatch = STC_PTS_MATCHED;
		}
	}
	else if( eMatch == STC_PTS_SMOOTH_WAITING )
	{
		pstSync->u32SmWaitCnt++;
		eMatch = STC_PTS_WAITING;

		if( pstSync->u32SmWaitCnt < 4 )
			eMatch = STC_PTS_MATCHED;
		else if( pstSync->u32SmWaitCnt < 20 )
		{
			if( pstSync->u32SmWaitCnt&3 )
				eMatch = STC_PTS_MATCHED;
		}
		else if( pstSync->u32SmWaitCnt < 40 )
		{
			if( pstSync->u32SmWaitCnt&1 )
				eMatch = STC_PTS_MATCHED;
		}
		else if( pstSync->u32SmWaitCnt < 80 )
		{
			if( !(pstSync->u32SmWaitCnt&3) )
				eMatch = STC_PTS_MATCHED;
		}
	}

	pstSync->ui32ContinuousFrameCount++;
	pstSync->Debug.ui32LogTick_GetNewNo = 0;
/*
	// log for debug
	pstSync->Debug.ui32LogTick_GetNew++;
	if( pstSync->Debug.ui32LogTick_GetNew == 0x100 )
	{
		log_noti("[PTS%d][DBG:0x%X] DQlen:%d, Match Mode:%d, Offset(Conf %d Cur %d)\n",
			ui8SyncCh, ui32STC,
			DISP_Q_NumActive(ui8SyncCh),
			pstSync->Config.eMatchMode,
			pstSync->Config.ui32DisplayOffset_ms,
			PTS_GetDisplayOffsetMs(pstSync)
			);

		pstSync->Debug.ui32LogTick_GetNew = 0;
	}
*/
	pstSync->ui32STC_Prev = ui32STC;

	return eMatch;
}

#endif


