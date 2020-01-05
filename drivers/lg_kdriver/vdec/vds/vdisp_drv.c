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

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "vdisp_drv.h"
#include "de_if_drv.h"
#include "vsync_drv.h"
#include "pts_drv.h"
#include "vdec_rate.h"
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
#include <linux/spinlock.h>
//#include <linux/kthread.h>
#endif

#include "../mcu/os_adap.h"

#include "disp_q.h"
#include "disp_clear_q.h"
#include "../hal/top_hal_api.h"
#include "../hal/ipc_reg_api.h"
#include "../hal/lq_hal_api.h"

//#define VDISP_DBG_LIPSYNC
#define LOG_NAME	vdec_dqpop
#include "log.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define		VDISP_NUM_OF_CMD_Q				0x20
#define		VDISP_DUAL_CH_NUM			4
#define		VDISP_SMOOTH_DISCARD_THOLD		(4)
#define		VDISP_SMOOTH_WAIT_THOLD		(4)

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
//typedef UINT32 (*fpGetStc)(void[], UINT8);

typedef enum
{
	VDISP_CMD_NONE = 0,
	VDISP_CMD_PLAY,
	VDISP_CMD_STEP,
	VDISP_CMD_PAUSE,
	VDISP_CMD_RESET,
	VDISP_CMD_FLUSH,
	VDISP_CMD_REPEAT,
	VDISP_CMD_UINT32 = 0x20110915
} VDISP_CMD_TYPE_E;

typedef struct
{
	VDISP_CMD_TYPE_E	eCmdType;
	UINT32				u32Param;
} VDISP_CMD_T;

typedef enum
{
	VDISP_NULL = 0,
	VDISP_READY = 10,
	VDISP_PLAY = 20,
	VDISP_PAUSE,
	VDISP_STATE_UINT32 = 0x20110716
} E_VDISP_STATE_T;

struct _VDISP_CH_T;
typedef struct _VDISP_CH_T VDISP_CH_T;

typedef struct
{
	VDISP_CH_T	*pstVdispCh[2];
	UINT8			u8EmptyCnt[2];
	UINT8			u8nPluged;
	UINT8			u8VsyncCh;
	UINT8			u8State;
} DualCh_T;

typedef struct
{
	enum {
		SYNC_FRM_INVALID,
		SYNC_FRM_INACTIVE,
		SYNC_FRM_WAITPAIR,
		SYNC_FRM_READY,
		SYNC_FRM_ACTIVE
	} eState;

	UINT32			ui32PTS;
	UINT32			ui32FrameRateRes;
	UINT32			ui32FrameRateDiv;
	S_DISPQ_BUF_T 	stDqFrame;
	S_DISPQ_BUF_T 	stPairFrame;
	BOOLEAN			bValidPairFrame;
} SYNC_FRAME_T;

struct _VDISP_CH_T
{
	E_VDISP_STATE_T	State;
	UINT8			u8VdispCh;
	VDISP_CLK_SRC	eClkSrc;
	UINT32			u32PrePts;
	UINT32			u32PreOrgPts;
	UINT32			u32PreDispPeriod;
	S_DISPQ_BUF_T	stNextFrame;
	S_DISPQ_BUF_T	stCurFrame;
	S_DISPQ_BUF_T	stFrame2Disp;
	BOOLEAN			bValidCurFrame;
	BOOLEAN			bValidNextFrame;
	SYNC_FRAME_T	stSyncFrame;

	BOOLEAN			bForcedPush;

	BOOLEAN			bIsDualCh;
	VDISP_CH_T		*pstPairCh;
	DualCh_T		*pstDualCh;

	BOOLEAN			bLock4Pair;

	SYNC_T			*pstSync;

	struct
	{
		E_DE_IF_DST_T	eDeIfDstCh;
		UINT8 			ui8VSyncCh;
	} Config;
	struct
	{
		VDISP_CMD_T			astCmd[VDISP_NUM_OF_CMD_Q];
		volatile UINT32		ui32WrIndex;
		volatile UINT32		ui32RdIndex;
	} CmdQ;
	struct
	{
		BOOLEAN			bStepping;
		volatile BOOLEAN		bPlaying;
		volatile BOOLEAN		bClosing;
		BOOLEAN			bFreeze;
		VDISP_STATUS_CB	fpStatus;
	} Status;

	struct
	{
		UINT32		ui32LogTick_UpdateBuf;
		UINT32		u32nInt;
		UINT32		u32nPopFrame;
		UINT32		u32nDispFrame;
	} Debug;

	spinlock_t stLock;
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
#ifdef VDISP_DBG_LIPSYNC
static volatile UINT32 *pDeInfo, *pDePixel;
static struct task_struct *gpstVdispTask = NULL;
#endif
static BOOLEAN bVdispInit = FALSE;
/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static void VDISP_VsyncCallback(UINT8 u8VsyncCh, UINT8 u8nVdisp, UINT8 au8VdispCh[], UINT8 u8FieldInfo);

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static CHAR gazClkSrcStr[VDISP_CLK_MAX][10] =
{
	[VDISP_CLK_NONE]	= "CLK_NONE",
	[VDISP_CLK_PDEC0]	= "CLK_PDEC0",
	[VDISP_CLK_PDEC1]	= "CLK_PDEC1",
	[VDISP_CLK_PDEC2]	= "CLK_PDEC2",
	[VDISP_CLK_PDEC3]	= "CLK_PDEC3",
	[VDISP_CLK_GSTC]	= "CLK_GSTC"
};

VDISP_CH_T gsVdisp[VDISP_NUM_OF_CHANNEL];
DualCh_T gstDualCh[VDISP_DUAL_CH_NUM];



/*----------------------------------------------------------------------------------------
 *   Function Define
 *---------------------------------------------------------------------------------------*/
static BOOLEAN _VDISP_CheckBelongTo90kTick(UINT32 ui32STC_Start, UINT32 ui32STC_End, UINT32 ui32PTS)
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

#ifdef VDISP_DBG_LIPSYNC
static UINT32 u32VdecSendTime;
static int VDISP_MonTask(void *data)
{
	UINT32 preData=0;
	UINT32 preDataW=0;
	UINT32 addr, addrW, pixelData=0, pixelDataW=0;
	UINT32 u32Stc;
	UINT32 uFrameAddr[12] = {
			0x98000000,
			0x98438000,
			0x98870000,
			0x98ca8000,
			0x990e0000,
			0x99518000,
			0x99950000,
			0x99d88000,
			0x9a1c0000,
			0x9a5f8000,
			0x9aa30000,
			0x9ae68000 };
	UINT32 nFrame, nFrame2, nFramePre=0, i;

	OS_MsecSleep(3000);

	while(1)
	{

		if( gsVdisp[0].State != VDISP_PLAY )
		{
			OS_MsecSleep(100);
			continue;
		}

		addr = *pDeInfo;
		addr = (addr >> 19)<<15;
		addrW = *(pDeInfo+2);
		addrW = (addrW >> 19)<<15;

		if( addr < 0x800000 && addrW < 0x800000 )
		{
			pixelData = *(volatile UINT32*)((UINT32)pDePixel+addr);
			pixelDataW = *(volatile UINT32*)((UINT32)pDePixel+addrW);
		}

		u32Stc = VDISP_GetSTC(0);

		nFrame = 0;
		nFrame2 = 0;

		for(i=0;i<12;i++)
		{
			pixelData = *(volatile UINT32*)(pDePixel+(uFrameAddr[i]-uFrameAddr[0]+((2048*500)+900)*2 )/4);
			log_debug("  + %d: pixel %X nfrm %d addr %X\n",i, pixelData, nFrame,
					pDePixel+(uFrameAddr[i]-uFrameAddr[0]+((2048*500)+900)*2 )/4
					);
			//if( pixelData > 0xA0000000 )
			if( pixelData < 0x20000000 )
				nFrame2++;
			else if( pixelData > 0x40000000 )
				nFrame++;
		}

		if( nFramePre == 0 && nFrame != 0 && nFrame2 > 5 )
			log_noti("= Write %d dif %d %X =\n", u32Stc, u32Stc-u32VdecSendTime, *pDePixel);

		nFramePre = nFrame;

			/*
		if( preData < 0x70000000 && pixelData > 0x70000000 )
			log_noti("= Read %d dif %d %X =\n", u32Stc, u32Stc-u32VdecSendTime, pixelData);
		if( preDataW < 0x70000000 && pixelDataW > 0x70000000 )
			log_noti("= Write %d dif %d %X =\n", u32Stc, u32Stc-u32VdecSendTime, pixelData);
*/
		preData = pixelData;
		preDataW = pixelDataW;

		// check stop condition when device is closed
		if(kthread_should_stop())
		{
			break;
		}

		OS_MsecSleep(5);
	}
	return 0;
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
static BOOLEAN _VDISP_GetCmdQ(UINT8 u8VdispCh, VDISP_CMD_T *pstCmd)
{
	UINT32		ui32WrIndex;
	UINT32		ui32RdIndex, ui32RdIndex_Next;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] %s\n", u8VdispCh, __FUNCTION__ );
		return FALSE;
	}

	ui32WrIndex = gsVdisp[u8VdispCh].CmdQ.ui32WrIndex;
	ui32RdIndex = gsVdisp[u8VdispCh].CmdQ.ui32RdIndex;

	if( ui32WrIndex == ui32RdIndex )
		return FALSE;

	*pstCmd = gsVdisp[u8VdispCh].CmdQ.astCmd[ui32RdIndex];

	log_noti("[Vdisp%d-%d][DBG] Cmd: %d, %s\n", u8VdispCh,
			gsVdisp[u8VdispCh].State, pstCmd->eCmdType, __FUNCTION__ );

	ui32RdIndex_Next = ui32RdIndex + 1;
	if( ui32RdIndex_Next == VDISP_NUM_OF_CMD_Q )
		ui32RdIndex_Next = 0;

	gsVdisp[u8VdispCh].CmdQ.ui32RdIndex = ui32RdIndex_Next;

	return TRUE;
}



UINT32 VDISP_GetSTC(UINT8 u8VdispCh)
{
	VDISP_CH_T	*pstVdispCh;
	UINT32				ui32STC = 0xFFFFFFFF;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] %s", u8VdispCh, __FUNCTION__ );
		return 0xFFFFFFFF;
	}

	pstVdispCh = &gsVdisp[u8VdispCh];

	if( pstVdispCh->eClkSrc == VDISP_CLK_GSTC )
		ui32STC = TOP_HAL_GetGSTCC() & 0x0fffffff;
	else
		ui32STC = LQ_HAL_GetSTC(pstVdispCh->eClkSrc - VDISP_CLK_PDEC0) & 0x0fffffff;

	return ui32STC;
}

static void VDISP_InitDualCh(void)
{
	UINT8 i;

	for(i=0; i<VDISP_DUAL_CH_NUM; i++)
	{
		gstDualCh[i].u8nPluged = 0;
		gstDualCh[i].pstVdispCh[0] = NULL;
		gstDualCh[i].pstVdispCh[1] = NULL;
		gstDualCh[i].u8EmptyCnt[0] = 0;
		gstDualCh[i].u8EmptyCnt[1] = 0;
	}

	return;
}

static DualCh_T* VDISP_GetFreeDualCh(void)
{
	UINT8 i;
	DualCh_T*	pstDualCh = NULL;

	for(i=0; i<VDISP_DUAL_CH_NUM; i++)
		if( gstDualCh[i].u8nPluged < 2)
			break;

	if( i< VDISP_DUAL_CH_NUM )
		pstDualCh = &gstDualCh[i];

	return pstDualCh;
}

static DualCh_T* VDISP_SetDualCh(VDISP_CH_T *pstVdispCh)
{
	DualCh_T*	pstDualCh = NULL;
	UINT32		u8VdispIdx;

	pstDualCh = VDISP_GetFreeDualCh();

	if( pstDualCh == NULL )
	{
		log_error("[Vdisp][Err] insufficient dual channel\n");
		return NULL;
	}

	for(u8VdispIdx=0; u8VdispIdx<2; u8VdispIdx++)
		if( pstDualCh->pstVdispCh[u8VdispIdx] == NULL )
			break;

	if( u8VdispIdx == 2 )
	{
		log_error("Wrong Dual Channel Vdisp Idx %d\n", u8VdispIdx);
		return NULL;
	}

	pstDualCh->pstVdispCh[u8VdispIdx] = pstVdispCh;
	pstDualCh->u8nPluged++;
	pstVdispCh->bIsDualCh = TRUE;
	pstVdispCh->pstDualCh = pstDualCh;

	if(pstDualCh->u8nPluged == 1)
	{
		// init
		pstDualCh->u8EmptyCnt[0] = 0;
		pstDualCh->u8EmptyCnt[1] = 0;
	}
	else if(pstDualCh->u8nPluged == 2)
	{
		pstDualCh->pstVdispCh[0]->pstPairCh = pstDualCh->pstVdispCh[1];
		pstDualCh->pstVdispCh[1]->pstPairCh = pstDualCh->pstVdispCh[0];
	}

	log_noti("DualCh %p Plug Vdisp%d  n:%d\n",
			pstDualCh, pstVdispCh->u8VdispCh, pstDualCh->u8nPluged);

	return pstDualCh;
}

static void VDISP_FreeDualCh(VDISP_CH_T *pstVdispCh)
{
	DualCh_T*	pstDualCh = pstVdispCh->pstDualCh;
	UINT32		u8VdispIdx;

	if( pstDualCh == NULL )
	{
		log_error("not belong to dual ch\n");
		return;
	}

	for(u8VdispIdx=0; u8VdispIdx<2; u8VdispIdx++)
		if( pstDualCh->pstVdispCh[u8VdispIdx] == pstVdispCh )
			break;

	if( u8VdispIdx == 2 )
	{
		log_error("Wrong Dual Channel Vdisp Idx %d\n", u8VdispIdx);
		return;
	}

	if(pstDualCh->u8nPluged == 2)
	{
		pstDualCh->pstVdispCh[0]->pstPairCh = NULL;
		pstDualCh->pstVdispCh[1]->pstPairCh = NULL;
	}

	pstDualCh->u8nPluged--;
	pstDualCh->pstVdispCh[u8VdispIdx] = NULL;
	pstVdispCh->bIsDualCh = FALSE;
	pstVdispCh->pstDualCh = NULL;


	log_noti("DualCh %p: Free Vdisp%d  n:%d\n",
			pstDualCh, pstVdispCh->u8VdispCh, pstDualCh->u8nPluged);

	return;
}

VDISP_CH_T* VDISP_GetHandler(UINT8 u8VdispCh)
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return NULL;
	}

	return &gsVdisp[u8VdispCh];
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
static BOOLEAN _VDISP_PutCmdQ(UINT8 u8VdispCh, VDISP_CMD_T *pstCmd)
{
	UINT32		ui32WrIndex, ui32WrIndex_Next;
	UINT32		ui32RdIndex;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] %s\n", u8VdispCh, __FUNCTION__ );
		return FALSE;
	}

	ui32WrIndex = gsVdisp[u8VdispCh].CmdQ.ui32WrIndex;
	ui32RdIndex = gsVdisp[u8VdispCh].CmdQ.ui32RdIndex;

	ui32WrIndex_Next = ui32WrIndex + 1;
	if( ui32WrIndex_Next == VDISP_NUM_OF_CMD_Q )
		ui32WrIndex_Next = 0;

	if( ui32WrIndex_Next == ui32RdIndex )
	{
		log_error("[Vdisp%d][Err] Cmd Q Overflow\n", u8VdispCh );
		return FALSE;
	}

	log_noti("[Vdisp%d-%d][DBG] Cmd: %d, %s\n", u8VdispCh,
			gsVdisp[u8VdispCh].State, pstCmd->eCmdType, __FUNCTION__ );

	gsVdisp[u8VdispCh].CmdQ.astCmd[ui32WrIndex] = *pstCmd;
	gsVdisp[u8VdispCh].CmdQ.ui32WrIndex = ui32WrIndex_Next;

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
void VDISP_Init(void)
{
	UINT8	u8VdispCh;

	if( bVdispInit == TRUE )
	{
		log_warning("VDISP is already initialized\n");
		return;
	}

	bVdispInit = TRUE;

	VDISP_InitDualCh();

	for( u8VdispCh = 0; u8VdispCh < VDISP_NUM_OF_CHANNEL; u8VdispCh++ )
	{
		gsVdisp[u8VdispCh].stLock = __SPIN_LOCK_UNLOCKED(gsVdisp[u8VdispCh].stLock);
		gsVdisp[u8VdispCh].State = VDISP_NULL;
		gsVdisp[u8VdispCh].u8VdispCh = u8VdispCh;
		gsVdisp[u8VdispCh].u32PrePts = 0xFFFFFFFF;
		gsVdisp[u8VdispCh].stFrame2Disp.ui32FrameIdx = PTS_INVALID_FRAMEINDEX;
		gsVdisp[u8VdispCh].bIsDualCh = TRUE;
		gsVdisp[u8VdispCh].pstDualCh = NULL;
		gsVdisp[u8VdispCh].pstPairCh = NULL;

		gsVdisp[u8VdispCh].Config.eDeIfDstCh = 0xFF;
		gsVdisp[u8VdispCh].Config.ui8VSyncCh = 0xFF;

		gsVdisp[u8VdispCh].CmdQ.ui32WrIndex = 0;
		gsVdisp[u8VdispCh].CmdQ.ui32RdIndex = 0;

		gsVdisp[u8VdispCh].Status.bStepping = FALSE;
		gsVdisp[u8VdispCh].Status.bPlaying = FALSE;
		gsVdisp[u8VdispCh].Status.bClosing = FALSE;
		gsVdisp[u8VdispCh].Status.bFreeze = FALSE;

		gsVdisp[u8VdispCh].Debug.ui32LogTick_UpdateBuf = 0;

		gsVdisp[u8VdispCh].pstSync = PTS_GetHandler(u8VdispCh);
	}

	PTS_Init();
	VSync_Init(VDISP_VsyncCallback);
	DE_IF_Init();

#ifdef VDISP_DBG_LIPSYNC
	pDeInfo		= (volatile UINT32 *)VDEC_TranselateVirualAddr(0xC0014B40, 0x20);
	//pDePixel	= (volatile UINT32 *)VDEC_TranselateVirualAddr(0x90000000, 0x800000);
	pDePixel	= (volatile UINT32 *)VDEC_TranselateVirualAddr(0x98000000, 0x32A0000);
	gpstVdispTask = kthread_run(VDISP_MonTask, (void *)NULL, "vdisp_mon_thread");
#endif
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
UINT8 VDISP_Open(E_VDISP_DST_T eVdispDstCh, VDISP_CLK_SRC eClkSrc, UINT32 ui32DisplayOffset_ms, UINT32 ui32NumOfDq, BOOLEAN bIsDualDecoding, BOOLEAN bFixedVSync, PTS_MATCH_MODE_E eMatchMode, VDISP_STATUS_CB fpStatusCb)
{
	VDISP_CH_T *pstVdispCh;
	UINT8	u8VdispCh = (UINT8)eVdispDstCh;
	UINT8	ui8VSyncCh = 0xFF;

	pstVdispCh = VDISP_GetHandler(u8VdispCh);

	if( pstVdispCh == NULL )
	{
		log_error("[Vdisp%d][Err] Fail to get Vdisp handler\n", u8VdispCh);
		return 0xFF;
	}

	if( pstVdispCh->State != VDISP_NULL )
	{
		log_error("[Vdisp%d][Err] State: %d, %s(%d)\n",
				u8VdispCh, pstVdispCh->State, __FUNCTION__, __LINE__ );
		//VDISP_Close(u8VdispCh);
		return 0xFF;
	}

	if( eClkSrc >= VDISP_CLK_MAX || eClkSrc == VDISP_CLK_NONE )
	{
		log_error("[Vdisp%d][Err] Wrong Clock Src %d\n", u8VdispCh, eClkSrc);
		return 0xFF;
	}

	if( DISP_Q_Open(u8VdispCh, ui32NumOfDq) == FALSE )
	{
		log_error("[Vdisp%d-%d][Err] Failed to Alloc Display Queue Memory, %s\n",
				u8VdispCh, pstVdispCh->State, __FUNCTION__ );
		return 0xFF;
	}

	log_noti("[Vdisp%d-%d][DBG] Display Offset: %d, ClkSrc: %s\n",
			u8VdispCh, pstVdispCh->State, ui32DisplayOffset_ms,
			gazClkSrcStr[eClkSrc] );

	LQC_HAL_Init(u8VdispCh);
	LQ_HAL_Enable(u8VdispCh);

	if( DE_IF_Open((E_DE_IF_DST_T)eVdispDstCh) == FALSE )
	{
		DISP_Q_Close(u8VdispCh);
		return 0xFF;
	}

	pstVdispCh->Status.fpStatus = fpStatusCb;

	pstVdispCh->pstSync = PTS_Open(u8VdispCh, eClkSrc==VDISP_CLK_GSTC,
			ui32DisplayOffset_ms, bIsDualDecoding, eMatchMode);
	pstVdispCh->eClkSrc = eClkSrc;

	if( bIsDualDecoding )
		VDISP_SetDualCh(pstVdispCh);

	ui8VSyncCh = VSync_Open((E_DE_IF_DST_T)eVdispDstCh, u8VdispCh, bIsDualDecoding,
			bFixedVSync, 30, 1, FALSE);

	DE_IF_SelVsync((E_DE_IF_DST_T)eVdispDstCh, ui8VSyncCh);
	//DE_IF_SelVsync((E_DE_IF_DST_T)eVdispDstCh, ui8VSyncCh+2);	// for raster mode

	pstVdispCh->State = VDISP_READY;
	pstVdispCh->stSyncFrame.eState = SYNC_FRM_INVALID;
	pstVdispCh->stSyncFrame.bValidPairFrame = FALSE;
	pstVdispCh->u32PrePts = 0xFFFFFFFF;
	pstVdispCh->u32PreOrgPts = 0xFFFFFFFF;
	pstVdispCh->u32PreDispPeriod = 0;

	pstVdispCh->stFrame2Disp.ui32FrameIdx = PTS_INVALID_FRAMEINDEX;
	pstVdispCh->bValidCurFrame = FALSE;
	pstVdispCh->bValidNextFrame = FALSE;
	pstVdispCh->bForcedPush = TRUE;
	pstVdispCh->bLock4Pair = TRUE;

	pstVdispCh->Config.eDeIfDstCh = (E_DE_IF_DST_T)eVdispDstCh;
	pstVdispCh->Config.ui8VSyncCh = ui8VSyncCh;

	pstVdispCh->Status.bStepping = FALSE;
	pstVdispCh->Status.bPlaying = FALSE;
	pstVdispCh->Status.bClosing = FALSE;
	pstVdispCh->Status.bFreeze = FALSE;

	return u8VdispCh;
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
void VDISP_Close(UINT8 u8VdispCh)
{
	VDISP_CH_T *pstVdispCh;
	VDISP_CMD_T	stCmd;
	unsigned long flags;

	pstVdispCh = VDISP_GetHandler(u8VdispCh);
	if( pstVdispCh == NULL )
	{
		log_error("[Vdisp%d][Err] Fail to get Vdisp handler\n", u8VdispCh);
		return;
	}

	spin_lock_irqsave (&pstVdispCh->stLock, flags);

	log_noti("[Vdisp%d-%d]\n", u8VdispCh, pstVdispCh->State);

	if( pstVdispCh->State == VDISP_NULL )
	{
		log_error("[Vdisp%d-%d] State Error\n", u8VdispCh, pstVdispCh->State);
		return;
	}

	VSync_SetClosing(pstVdispCh->Config.ui8VSyncCh, pstVdispCh->Config.eDeIfDstCh);

	// from _VDISP_Close
	VSync_Close(pstVdispCh->Config.ui8VSyncCh, pstVdispCh->Config.eDeIfDstCh, u8VdispCh);
	DE_IF_Close(pstVdispCh->Config.eDeIfDstCh);

	if( pstVdispCh->pstDualCh != NULL )
		VDISP_FreeDualCh(&gsVdisp[u8VdispCh]);

	PTS_Close(pstVdispCh->pstSync);

	pstVdispCh->State = VDISP_NULL;
	pstVdispCh->Config.eDeIfDstCh = 0xFF;
	pstVdispCh->Config.ui8VSyncCh = 0xFF;

	pstVdispCh->Status.bClosing = FALSE;
	////////////////////////////////

	while( _VDISP_GetCmdQ( u8VdispCh, &stCmd ) == TRUE );

	DISP_Q_Close(u8VdispCh);

	spin_unlock_irqrestore (&pstVdispCh->stLock, flags);
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
void VDISP_Debug_Set_DisplayOffset(UINT8 u8VdispCh, UINT32 ui32DisplayOffset_ms)
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_error("[Vdisp%d][DBG] DisplayOffset: %dms, %s\n", u8VdispCh, ui32DisplayOffset_ms, __FUNCTION__);

	PTS_Debug_Set_DisplayOffset(gsVdisp[u8VdispCh].pstSync, ui32DisplayOffset_ms);
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
void VDISP_Reset(UINT8 u8VdispCh)
{
	VDISP_CMD_T stCmd;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_noti("[Vdisp%d-%d][DBG] %s \n", u8VdispCh, gsVdisp[u8VdispCh].State, __FUNCTION__ );

	stCmd.eCmdType = VDISP_CMD_RESET;
	stCmd.u32Param = 0;
	_VDISP_PutCmdQ( u8VdispCh, &stCmd );
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
void VDISP_Start(UINT8 u8VdispCh, BOOLEAN bStep)
{
	VDISP_CMD_T stCmd;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_noti("[Vdisp%d-%d][DBG] Step:%d, %s \n", u8VdispCh, gsVdisp[u8VdispCh].State, bStep, __FUNCTION__ );

	gsVdisp[u8VdispCh].Status.bPlaying = TRUE;

	if( bStep )
		stCmd.eCmdType = VDISP_CMD_STEP;
	else
		stCmd.eCmdType = VDISP_CMD_PLAY;

	stCmd.u32Param = 0;
	_VDISP_PutCmdQ( u8VdispCh, &stCmd );
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
void VDISP_Stop(UINT8 u8VdispCh)
{
	VDISP_CMD_T stCmd;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_noti("[Vdisp%d-%d][DBG] %s \n", u8VdispCh, gsVdisp[u8VdispCh].State, __FUNCTION__ );

	stCmd.eCmdType = VDISP_CMD_PAUSE;
	stCmd.u32Param = 0;
	_VDISP_PutCmdQ( u8VdispCh, &stCmd );
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
void VDISP_Flush(UINT8 u8VdispCh)
{
	VDISP_CMD_T stCmd;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_noti("[Vdisp%d-%d][DBG] %s \n", u8VdispCh, gsVdisp[u8VdispCh].State, __FUNCTION__ );

	stCmd.eCmdType = VDISP_CMD_FLUSH;
	stCmd.u32Param = 0;
	_VDISP_PutCmdQ( u8VdispCh, &stCmd );
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
void VDISP_Freeze( UINT8 u8VdispCh, BOOLEAN bOnOff )
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_noti("[Vdisp%d-%d][DBG] Freeze:%d, %s\n", u8VdispCh, gsVdisp[u8VdispCh].State, bOnOff, __FUNCTION__);


	DE_IF_Freeze( gsVdisp[u8VdispCh].Config.eDeIfDstCh, bOnOff );
	gsVdisp[u8VdispCh].Status.bFreeze = bOnOff;
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

void VDISP_RepeatFrame(UINT8 u8DeCh, UINT8 u8nRepeat)
{
	VDISP_CMD_T stCmd;
	UINT8 u8VdispCh, i;
	VDISP_CH_T *pstVdispCh;

	for(i=0; i<VDISP_NUM_OF_CHANNEL ; i++)
	{
		pstVdispCh = VDISP_GetHandler(i);
		if(pstVdispCh!= NULL && pstVdispCh->State != VDISP_NULL &&
				pstVdispCh->Config.eDeIfDstCh == u8DeCh)
			break;
	}

	if( i<VDISP_NUM_OF_CHANNEL )
	{
		u8VdispCh = i;
		log_noti("[Vdisp%d-%d] repeat %d\n", u8VdispCh, gsVdisp[u8VdispCh].State, u8nRepeat);
		stCmd.eCmdType = VDISP_CMD_REPEAT;
		stCmd.u32Param = (UINT32)u8nRepeat;
		_VDISP_PutCmdQ( u8VdispCh, &stCmd );
	}
	else
	{
		log_noti("cant find open de channel %d\n", u8DeCh);
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
void VDISP_SetStcDiscont(UINT8 u8VdispCh, UINT32 u32AuiId)
{
	log_noti("[Vdisp%d] Dicontinuity AU ID %u\n", u8VdispCh, u32AuiId);
	//
	//PTS_SetStcDiscont(gsVdisp[u8VdispCh].pstSync);
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
void VDISP_SetMatchMode(UINT8 u8VdispCh, PTS_MATCH_MODE_E eMatchMode)
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_noti("[Vdisp%d][DBG] %s\n", u8VdispCh, __FUNCTION__);

	PTS_Set_MatchMode(gsVdisp[u8VdispCh].pstSync, eMatchMode);
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
void VDISP_SetSpeed( UINT8 u8VdispCh, SINT32 i32Speed )
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	log_noti("[Vdisp%d-%d][DBG] Speed: %d\n", u8VdispCh, gsVdisp[u8VdispCh].State, i32Speed);

	VDEC_RATE_Set_Speed(u8VdispCh, i32Speed);
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
SINT32 VDISP_GetSpeed( UINT8 u8VdispCh )
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return 0;
	}

	return VDEC_RATE_Get_Speed(u8VdispCh);
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
void VDISP_SetBaseTime( UINT8 u8VdispCh, UINT32 ui32BaseTime, UINT32 ui32BasePTS )
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	/*
	// ClkSrc
	if( gsVdisp[u8VdispCh].Config.ui8ClkID != ui8ClkID )
	{
		if( ui8ClkID != 0xFF )
			log_error("[Vdisp%d][Err] Clock ID: %d/%d, %s\n", u8VdispCh, ui8ClkID, gsVdisp[u8VdispCh].Config.ui8ClkID, __FUNCTION__ );
		return;
	}
	*/
	log_noti("[VDISP%d]    Set new -> BaseTime:0x%08X, PTS:0x%08X\n", u8VdispCh,
			ui32BaseTime, ui32BasePTS);

	PTS_Set_BaseTime(gsVdisp[u8VdispCh].pstSync, ui32BaseTime, ui32BasePTS);
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
void VDISP_GetBaseTime( UINT8 u8VdispCh, UINT32 *pui32BaseTime, UINT32 *pui32BasePTS )
{
	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] Channel Number, %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	PTS_Get_BaseTime(gsVdisp[u8VdispCh].pstSync, pui32BaseTime, pui32BasePTS);
}

void VDISP_GetCurrentInfo( UINT8 u8DeCh, S_VDISP_DISP_INFO_T *info)
{
	VDISP_CH_T	*pstVdispCh;
	UINT8 i;

	info->width = 0;
	info->height = 0;

	for(i=0; i<VDISP_NUM_OF_CHANNEL ; i++)
	{
		pstVdispCh = VDISP_GetHandler(i);
		if(pstVdispCh!= NULL && pstVdispCh->State != VDISP_NULL &&
				pstVdispCh->Config.eDeIfDstCh == u8DeCh)
			break;
	}

	if( i<VDISP_NUM_OF_CHANNEL )
	{
		if(pstVdispCh->bValidCurFrame)
		{
			info->width = pstVdispCh->stCurFrame.ui32PicWidth;
			info->width -= pstVdispCh->stCurFrame.ui32H_Offset & 0xFFFF;
			info->height = pstVdispCh->stCurFrame.ui32PicHeight;
			info->height -= pstVdispCh->stCurFrame.ui32V_Offset & 0xFFFF;
		}
	}
}

#if (defined(USE_MCU_FOR_VDEC_VDS) && defined(__XTENSA__)) || \
	(!defined(USE_MCU_FOR_VDEC_VDS) && !defined(__XTENSA__))

BOOLEAN VDISP_SetDualOutput(BOOLEAN bOn)
{
	return DE_IF_SetDualOutput(bOn);
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

inline static void vdisp_start_cmd(VDISP_CH_T *pstVdispCh)
{
	UINT8 u8VdispCh = pstVdispCh->u8VdispCh;

	pstVdispCh->Status.bPlaying = FALSE;

	switch( pstVdispCh->State )
	{
		case VDISP_READY :
			log_noti("[Vdisp%d-%d][DBG] READY --> PLAY\n", u8VdispCh, pstVdispCh->State );
			pstVdispCh->State = VDISP_PLAY;
			break;
		case VDISP_PAUSE :
			log_noti("[Vdisp%d-%d][DBG] PAUSE --> PLAY\n", u8VdispCh, pstVdispCh->State );
			pstVdispCh->State = VDISP_PLAY;
			break;
		case VDISP_PLAY :
			log_noti("[Vdisp%d-%d][Warning] Already Started\n", u8VdispCh, pstVdispCh->State );
			break;
		case VDISP_NULL :
		default :
			log_error("[Vdisp%d-%d][Err] State, Cmd:START, Step? %d\n",
					u8VdispCh, pstVdispCh->State, pstVdispCh->Status.bStepping);
			break;
	}

	return;
}

inline static void vdisp_pause_cmd(VDISP_CH_T *pstVdispCh)
{
	UINT8 u8VdispCh = pstVdispCh->u8VdispCh;

	switch( pstVdispCh->State )
	{
		case VDISP_PLAY :
			log_noti("[Vdisp%d-%d][DBG] PLAY --> PAUSE\n", u8VdispCh, pstVdispCh->State );
			pstVdispCh->State = VDISP_PAUSE;
			break;
		case VDISP_PAUSE :
			log_noti("[Vdisp%d-%d][Warning] Already Paused\n", u8VdispCh, pstVdispCh->State );
			break;
		case VDISP_READY :
			log_noti("[Vdisp%d-%d][DBG] READY --> PAUSE\n", u8VdispCh, pstVdispCh->State );
			break;
		case VDISP_NULL :
		default :
			log_error("[Vdisp%d-%d][Err] State, Cmd:PAUSE\n", u8VdispCh, pstVdispCh->State);
			break;
	}

	return;
}

inline static void vdisp_reset_cmd(VDISP_CH_T *pstVdispCh)
{
	UINT8 u8VdispCh = pstVdispCh->u8VdispCh;

	pstVdispCh->u32PrePts = 0xFFFFFFFF;
	switch( pstVdispCh->State )
	{
		case VDISP_READY :
			log_noti("[Vdisp%d-%d][DBG] Reset in READY State\n", u8VdispCh, pstVdispCh->State );
			break;
		case VDISP_PLAY :
			log_noti("[Vdisp%d-%d][DBG] Reset in PLAY State\n", u8VdispCh, pstVdispCh->State );
			PTS_Flush(pstVdispCh->pstSync);
			break;
		case VDISP_PAUSE :
			log_noti("[Vdisp%d-%d][DBG] Reset in PAUSE State\n", u8VdispCh, pstVdispCh->State );
			PTS_Flush(pstVdispCh->pstSync);
			break;
		case VDISP_NULL :
		default :
			log_error("[Vdisp%d-%d][Err] State, Cmd:RESET\n", u8VdispCh, pstVdispCh->State );
			break;
	}

	return;
}

inline static void vdisp_flush_cmd(VDISP_CH_T *pstVdispCh)
{
	UINT8 u8VdispCh = pstVdispCh->u8VdispCh;

	pstVdispCh->u32PrePts = 0xFFFFFFFF;
	switch( pstVdispCh->State )
	{
		case VDISP_READY :
			log_noti("[Vdisp%d-%d][DBG] Flush in Not Play State\n", u8VdispCh, pstVdispCh->State );
			break;
		case VDISP_PLAY :
			log_noti("[Vdisp%d-%d][DBG] Flush in PLAY State\n", u8VdispCh, pstVdispCh->State );

			if( pstVdispCh->bValidNextFrame && pstVdispCh->bLock4Pair == FALSE )
			{
				log_noti("[Vdisp%d] Clear next frame for flush\n", u8VdispCh);
				pstVdispCh->bValidNextFrame = FALSE;
				PTS_ClearFrame(pstVdispCh->u8VdispCh, &pstVdispCh->stNextFrame);
			}

			if( pstVdispCh->stSyncFrame.eState != SYNC_FRM_INVALID )
			{
				log_noti("[Vdisp%d] Clear sync cal frame for flush\n", u8VdispCh);
				PTS_ClearFrame(pstVdispCh->u8VdispCh, &pstVdispCh->stSyncFrame.stDqFrame);

				if( pstVdispCh->stSyncFrame.bValidPairFrame )
				{
					PTS_ClearFrame(pstVdispCh->u8VdispCh,
							&pstVdispCh->stSyncFrame.stPairFrame);
					log_debug("[Vdisp%d] Clear pair frame for flush\n", u8VdispCh);
				}
				pstVdispCh->stSyncFrame.eState = SYNC_FRM_INVALID;
			}

			PTS_Flush(pstVdispCh->pstSync);
			//VDISP_ClearFrame(u8VdispCh);
			break;
		case VDISP_PAUSE :
			log_noti("[Vdisp%d-%d] Flush in PAUSE State\n", u8VdispCh, pstVdispCh->State);
			/*
			if( == SYNC_FRM_READY )
				ClearFrame();
			if( pstVdispCh->bValidNextFrame )
			{
				log_noti("[Vdisp%d] Clear next frame for flush\n", u8VdispCh);
				stFrame2Clear = pstVdispCh->stNextFrame;
				pstVdispCh->bValidNextFrame = FALSE;
				PTS_ClearFrame(pstVdispCh->u8VdispCh, &stFrame2Clear);
			}
			*/
			PTS_Flush(pstVdispCh->pstSync);
			break;
		case VDISP_NULL :
		default :
			log_error("[Vdisp%d-%d][Err] State, Cmd:FLUSH\n", u8VdispCh, pstVdispCh->State );
			break;
	}

	return;
}

inline static void vdisp_repeat_cmd(VDISP_CH_T *pstVdispCh, UINT8 u8nTimes)
{
	UINT8 u8VdispCh = pstVdispCh->u8VdispCh;

	log_noti("[Vdisp%d] repeat frame\n", u8VdispCh);

	switch( pstVdispCh->State )
	{
		case VDISP_READY :
		case VDISP_PLAY :
		case VDISP_PAUSE :
			DE_IF_RepeatFrame(pstVdispCh->Config.eDeIfDstCh, u8nTimes);
			break;
		case VDISP_NULL :
		default :
			log_error("[Vdisp%d-%d][Err] State, Cmd:REPEAT\n", u8VdispCh, pstVdispCh->State );
			break;
	}

	return;
}

void VDISP_RunCmd(UINT8 u8VdispCh)
{
	VDISP_CMD_T	stCmd;
	VDISP_CH_T	*pstVdispCh;

	if( u8VdispCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error("[Vdisp%d][Err] %s\n", u8VdispCh, __FUNCTION__ );
		return;
	}

	pstVdispCh = &gsVdisp[u8VdispCh];
	while( _VDISP_GetCmdQ( u8VdispCh, &stCmd ) == TRUE )
	{
		switch( stCmd.eCmdType )
		{
		case VDISP_CMD_STEP :
		case VDISP_CMD_PLAY :
			if( stCmd.eCmdType == VDISP_CMD_STEP )
				pstVdispCh->Status.bStepping = TRUE;
			else
				pstVdispCh->Status.bStepping = FALSE;

			vdisp_start_cmd(pstVdispCh);
			break;

		case VDISP_CMD_PAUSE :
			vdisp_pause_cmd(pstVdispCh);
			break;

		case VDISP_CMD_RESET :
			vdisp_reset_cmd(pstVdispCh);
			break;
		case VDISP_CMD_FLUSH :
			vdisp_flush_cmd(pstVdispCh);
			break;
		case VDISP_CMD_REPEAT:
			vdisp_repeat_cmd(pstVdispCh, stCmd.u32Param);
			break;
		case VDISP_CMD_NONE :
		default :
			log_error("[Vdisp%d-%d][Err] Cmd: %d, %s(%d)\n", u8VdispCh, pstVdispCh->State, stCmd.eCmdType, __FUNCTION__, __LINE__ );
			break;
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

BOOLEAN _VDISP_IsInterlacedFrame(S_DISPQ_BUF_T *pstDqFrame)
{
	BOOLEAN bRet;

	switch( pstDqFrame->ui32DisplayInfo )
	{
		case DISPQ_SCAN_PROG :
			bRet = FALSE;
			break;
		case DISPQ_SCAN_TFF :
		case DISPQ_SCAN_BFF :
			//if( pstDqFrame->ui32DisplayPeriod == 1 || pstDqFrame->ui32DisplayPeriod >= 4 )
			//	log_error("[Vdisp][Err] Disp Period: %d of Field Pic\n",
			//			pstDqFrame->ui32DisplayPeriod );

			bRet = TRUE;
			break;
		default :
			log_error("[Vdisp][Err] Display Info: %d\n",
					pstDqFrame->ui32DisplayInfo );

			bRet = TRUE;
			break;
	}

	return bRet;
}

BOOLEAN VDISP_CheckFrame(VDISP_CH_T *pstVdispCh, S_DISPQ_BUF_T *pstDqFrame)
{
	UINT32	u32Temp;
	SYNC_FRAME_T *pstSyncFrame = &pstVdispCh->stSyncFrame;
	UINT8	u8VdispCh = pstVdispCh->u8VdispCh;
	BOOLEAN bInterlaced;

	// for extract debugging info
	u32Temp = pstDqFrame->ui32DisplayPeriod;
	pstDqFrame->ui32DisplayPeriod = u32Temp & ((1<<3) -1);
	pstDqFrame->ui32FrameIdx = u32Temp >> 3;

	pstSyncFrame->stDqFrame.bDispResult = FALSE;

	log_user1("[Vdisp%d] Pop Idx %2d  Rate %d/%d PTS %5u%s STC %5u  Qlen %d Dispi %d/%d %c\n",
			u8VdispCh, //pstDqFrame->ui32Y_FrameBaseAddr,
			pstDqFrame->ui32FrameIdx,
			pstDqFrame->ui32FrameRateRes, pstDqFrame->ui32FrameRateDiv,
			pstDqFrame->ui32PTS,
			pstDqFrame->bDiscont?" Discont.":"",
			VDISP_GetSTC(u8VdispCh),
			DISP_Q_NumActive(u8VdispCh),
			pstDqFrame->ui32DisplayInfo,
			pstDqFrame->ui32DisplayPeriod,
			pstDqFrame->ui32LR_Order == DISPQ_3D_FRAME_LEFT ? 'L':
			(pstDqFrame->ui32LR_Order == DISPQ_3D_FRAME_RIGHT ? 'R' : ' ')
			);

	// Check Frame Sanity
	if( pstDqFrame->ui32FrameIdx >= 32 )	// invalid idx
	{
		log_warning("ch:%d wrong idx %d", u8VdispCh, pstDqFrame->ui32FrameIdx );
		return FALSE;
	}

	//if( pstDqFrame->ui32DisplayPeriod )

	PTS_CheckFrame(pstVdispCh->pstSync, pstDqFrame);

	bInterlaced = _VDISP_IsInterlacedFrame( pstDqFrame );

	if( pstDqFrame->ui32PTS != VDEC_UNKNOWN_PTS &&
			pstVdispCh->u32PreOrgPts != pstDqFrame->ui32PTS )
		pstSyncFrame->ui32PTS = pstDqFrame->ui32PTS;
	else
	{
		UINT32 u32Dura;
		u32Dura = VDEC_RATE_GetFrameRateDuration(u8VdispCh);
		if(bInterlaced)
			u32Dura /= 2;
		u32Dura *= pstVdispCh->u32PreDispPeriod;
		pstSyncFrame->ui32PTS = pstVdispCh->u32PrePts + u32Dura;
		log_debug("ch%d same pts %d -> %d\n", u8VdispCh, pstDqFrame->ui32PTS,
				pstSyncFrame->ui32PTS );

	}

	VDEC_RATE_UpdateFrameRate_Decoder(u8VdispCh, pstDqFrame->ui32FrameRateRes,
			pstDqFrame->ui32FrameRateDiv, bInterlaced, bInterlaced);

	return TRUE;
}

static BOOLEAN _VDISP_SyncDualCh(VDISP_CH_T* pstVdispCh)
{
	DualCh_T	*pstDualCh;
	UINT32		u32BchMkPts, u32Bound, u32AcceptThr0, u32AcceptThr1;
	S_DISPQ_BUF_T	*pstDqFrame0, *pstDqFrame1, *pstAdjFrame;
	VDISP_CH_T	*pstAdjVdispCh;
	UINT32		ui32Duration90K;
	SYNC_FRAME_T *pstSyncFrame;
	static UINT32 u32DbgCnt;

	pstDualCh = pstVdispCh->pstDualCh;

	// if it's not the main channel
	if( pstDualCh->pstVdispCh[0] != pstVdispCh )
		return pstDualCh->u8State;

	if( DE_IF_IsNeedNewFrame(pstDualCh->pstVdispCh[1]->Config.eDeIfDstCh) == FALSE )
	{
		log_debug("dual strm: wait another ch's new frame request\n");
		pstDualCh->u8State = FALSE;
		return FALSE;
	}

	pstSyncFrame = &pstDualCh->pstVdispCh[0]->stSyncFrame;
	if( pstSyncFrame->eState == SYNC_FRM_INVALID )
	{
		if( DISP_Q_Pop(pstDualCh->pstVdispCh[0]->u8VdispCh, &pstSyncFrame->stDqFrame) )
		{
			VDISP_CheckFrame(pstDualCh->pstVdispCh[0], &pstSyncFrame->stDqFrame);

			pstSyncFrame->stDqFrame.bDispResult = FALSE;
			pstSyncFrame->eState = SYNC_FRM_READY;

			pstDualCh->pstVdispCh[0]->Debug.u32nPopFrame++;
		}
	}

	if( pstSyncFrame->eState == SYNC_FRM_READY )
	{
		pstDqFrame0 = &pstSyncFrame->stDqFrame;
		pstDualCh->u8EmptyCnt[0] = 0;
	}
	else
	{
		log_debug("no main ch frame, cnt %d\n", pstDualCh->u8EmptyCnt[0]);

		pstDualCh->u8EmptyCnt[0]++;
		if(pstDualCh->u8EmptyCnt[0]>20)
		{
			pstDualCh->u8State = TRUE;
			return TRUE;
		}
		else
		{
			pstDualCh->u8State = FALSE;
			return FALSE;
		}
	}

	pstSyncFrame = &pstDualCh->pstVdispCh[1]->stSyncFrame;
	if( pstSyncFrame->eState == SYNC_FRM_INVALID )
	{
		if( DISP_Q_Pop(pstDualCh->pstVdispCh[1]->u8VdispCh, &pstSyncFrame->stDqFrame) )
		{
			VDISP_CheckFrame(pstDualCh->pstVdispCh[1], &pstSyncFrame->stDqFrame);

			pstSyncFrame->stDqFrame.bDispResult = FALSE;
			pstSyncFrame->eState = SYNC_FRM_READY;

			pstDualCh->pstVdispCh[1]->Debug.u32nPopFrame++;
		}
	}

	if( pstSyncFrame->eState == SYNC_FRM_READY )
	{
		pstDqFrame1 = &pstSyncFrame->stDqFrame;
		pstDualCh->u8EmptyCnt[1] = 0;
	}
	else
	{
		log_debug("no sub ch frame, cnt %d\n", pstDualCh->u8EmptyCnt[1]);

		pstDualCh->u8EmptyCnt[1]++;
		if(pstDualCh->u8EmptyCnt[1]>20)
		{
			pstDualCh->u8State = TRUE;
			return TRUE;
		}
		else
		{
			pstDualCh->u8State = FALSE;
			return FALSE;
		}
	}

	u32Bound = (pstDqFrame0->ui32PTS + 0x07FFFFFF) & 0x0FFFFFFF;
	if( _VDISP_CheckBelongTo90kTick(pstDqFrame0->ui32PTS, u32Bound,
				pstDqFrame1->ui32PTS) == TRUE )
	{
		u32BchMkPts = pstDualCh->pstVdispCh[1]->stSyncFrame.ui32PTS;
		pstAdjVdispCh = pstDualCh->pstVdispCh[0];
		pstAdjFrame = pstDqFrame0;
		pstSyncFrame = &pstDualCh->pstVdispCh[0]->stSyncFrame;
	}
	else
	{
		u32BchMkPts = pstDualCh->pstVdispCh[0]->stSyncFrame.ui32PTS;
		pstAdjVdispCh = pstDualCh->pstVdispCh[1];
		pstAdjFrame = pstDqFrame1;
		pstSyncFrame = &pstDualCh->pstVdispCh[1]->stSyncFrame;
	}

	ui32Duration90K = VDEC_RATE_GetFrameRateDuration(pstDualCh->pstVdispCh[0]->u8VdispCh);
	ui32Duration90K /= 2;

	u32AcceptThr0 = (u32BchMkPts-ui32Duration90K) & 0xFFFFFFF;
	u32AcceptThr1 = (u32BchMkPts+ui32Duration90K) & 0xFFFFFFF;
	do
	{
		log_trace("AdjustCh %d, %d %d Dual Diff %d\n", pstAdjVdispCh->u8VdispCh, u32BchMkPts,
				pstSyncFrame->ui32PTS, pstSyncFrame->ui32PTS - u32BchMkPts);

		if( PTS_IsDiscont(pstDualCh->pstVdispCh[0]->pstSync) == TRUE ||
				PTS_IsDiscont(pstDualCh->pstVdispCh[1]->pstSync) == TRUE )
			break;

		// if meet pts with benchmark pts, stop
		if( _VDISP_CheckBelongTo90kTick(u32AcceptThr0, u32AcceptThr1, pstSyncFrame->ui32PTS) )
			break;

		log_noti("[Vdisp%d] frame drop for 3d sync\n", pstAdjVdispCh->u8VdispCh);

		PTS_ClearFrame(pstAdjVdispCh->u8VdispCh, pstAdjFrame);
		pstSyncFrame->eState = SYNC_FRM_INVALID;

		if( DISP_Q_Pop(pstAdjVdispCh->u8VdispCh, &pstSyncFrame->stDqFrame) )
		{
			VDISP_CheckFrame(pstAdjVdispCh, &pstSyncFrame->stDqFrame);

			pstSyncFrame->stDqFrame.bDispResult = FALSE;
			pstSyncFrame->eState = SYNC_FRM_READY;

			pstAdjVdispCh->Debug.u32nPopFrame++;
		}
		else
		{
			log_debug("no adjust ch(%d) frame\n", pstAdjVdispCh->u8VdispCh);
		}

		if( pstSyncFrame->eState == SYNC_FRM_READY )
			pstAdjFrame = &pstSyncFrame->stDqFrame;
		else
		{
			pstDualCh->u8State = FALSE;
			return FALSE;
		}

	} while(1);

	if( !((u32DbgCnt++) % 0x100) && pstAdjFrame != NULL )
		log_noti("Dual Diff %d\n", pstSyncFrame->ui32PTS - u32BchMkPts);

	pstDualCh->u8State = TRUE;
	return TRUE;
}


BOOLEAN VDISP_CheckDualStream(VDISP_CH_T *pstVdispCh)
{
	// 3D dual stream pre-adjust
	if( pstVdispCh->pstDualCh != NULL  )
	{
		if( pstVdispCh->pstPairCh == NULL )
		{
			log_debug("dual strm but no pair ch\n");
			return FALSE;
		}

		if( //VDEC_RATE_Get_Speed(pstVdispCh->u8VdispCh) == 1000 &&
				_VDISP_SyncDualCh(pstVdispCh) == FALSE )
		{
			log_debug("dual strm: wait another ch's PTS timing\n");
			return FALSE;
		}
	}

	return TRUE;
}

BOOLEAN VDISP_GetNewFrame(VDISP_CH_T *pstVdispCh, S_DISPQ_BUF_T *pstNextFrame, UINT32 ui32STC)
{
	BOOLEAN bRet;
	static UINT32 u32EmptyCnt=0;
	PTS_MATCH_E			eMatch = STC_PTS_NONE;
	BOOLEAN 			bInterlaced, bValFrame2Clear = FALSE, bGotNewFrame = FALSE;
	S_DISPQ_BUF_T 		stDqFrame2Clear;
	UINT8				u8VdispCh;
	SYNC_FRAME_T *pstSyncFrame;
	SINT32				i32Diff;

	if( pstVdispCh == NULL )
		return FALSE;

	u8VdispCh = pstVdispCh->u8VdispCh;

	if( pstVdispCh->State != VDISP_PLAY )
	{
		static UINT32 u32DbgCnt=0;
		if( !((u32DbgCnt++)%100) )
			log_info("[Vdisp%d-%d][Err] Current State\n", u8VdispCh, pstVdispCh->State );
		return FALSE;
	}

	if( !VDISP_CheckDualStream(pstVdispCh) )
		return bGotNewFrame;

	pstSyncFrame = &pstVdispCh->stSyncFrame;

re_pop:
	if( pstSyncFrame->eState == SYNC_FRM_INVALID )
	{
		bRet = DISP_Q_Pop(u8VdispCh, &pstSyncFrame->stDqFrame);
		if( bRet )
		{
			UINT32 u32QLen = DISP_Q_NumActive(u8VdispCh);

			pstVdispCh->Debug.u32nPopFrame++;
			u32EmptyCnt = 0;

			PTS_NotiCurQlen(pstVdispCh->pstSync, u32QLen+1);

			if( VDISP_CheckFrame(pstVdispCh, &pstSyncFrame->stDqFrame) == FALSE )
				goto re_pop;

			pstSyncFrame->stDqFrame.bDispResult = FALSE;
			pstSyncFrame->eState = SYNC_FRM_READY;

			if( pstVdispCh->bForcedPush && u32QLen > 1 )
			{
				// In this case, it might be not steal picture stream!
				pstVdispCh->bForcedPush = FALSE;
				DE_IF_RepeatFrame(pstVdispCh->Config.eDeIfDstCh, 0);
			}

			// Frame Sequential Pairing
			if( pstSyncFrame->stDqFrame.ui32LR_Order == DISPQ_3D_FRAME_LEFT )
			{
				pstSyncFrame->bValidPairFrame = FALSE;
				pstSyncFrame->eState = SYNC_FRM_WAITPAIR;
				log_debug("Vdisp%d: Wait pair frame for frame sequential\n", u8VdispCh);
			}
		}
		else
		{
			PTS_NotiCurQlen(pstVdispCh->pstSync, 0);
			if( !((u32EmptyCnt++)%60) )
				log_noti("[Vdisp%d] DispQ empty\n", u8VdispCh);

			if( pstVdispCh->Status.fpStatus )
				pstVdispCh->Status.fpStatus(u8VdispCh, VDISP_ST_EMPTY, 0);
		}
	}

	if( pstSyncFrame->eState == SYNC_FRM_WAITPAIR )
	{
		bRet = DISP_Q_Pop(u8VdispCh, &pstSyncFrame->stPairFrame);
		if( bRet )
		{
			pstSyncFrame->stPairFrame.bDispResult = FALSE;

			//if( RIGHT);
			pstSyncFrame->bValidPairFrame = TRUE;
			pstSyncFrame->eState = SYNC_FRM_READY;
			log_debug("Vdisp%d: Get new pair\n", u8VdispCh);
		}
	}

	if( pstSyncFrame->eState == SYNC_FRM_READY )
	{
		eMatch = PTS_MatchCheck(pstVdispCh->pstSync, pstSyncFrame->ui32PTS, ui32STC,
				pstVdispCh->u32PrePts);

		if( eMatch == STC_PTS_MATCHED || eMatch == STC_PTS_FREERUN )
		{
			// Display matched frame
			pstSyncFrame->eState = SYNC_FRM_INVALID;
			pstVdispCh->u32PrePts = pstSyncFrame->ui32PTS;
			pstVdispCh->u32PreOrgPts = pstSyncFrame->stDqFrame.ui32PTS;
			pstVdispCh->u32PreDispPeriod = pstSyncFrame->stDqFrame.ui32DisplayPeriod;

			*pstNextFrame = pstSyncFrame->stDqFrame;
			pstNextFrame->ui32PTS = pstSyncFrame->ui32PTS;
			bGotNewFrame = TRUE;
		}
		else if( eMatch == STC_PTS_DISCARD )
		{
			if( bValFrame2Clear )
			{
				// discard DqFrame2clear previously set
				log_noti("[Vdisp%d] Discard -> clear frame\n", u8VdispCh);
				PTS_ClearFrame(u8VdispCh, &stDqFrame2Clear);
			}

			// Don't discard right now...
			pstSyncFrame->eState = SYNC_FRM_INVALID;
			pstVdispCh->u32PrePts = pstSyncFrame->ui32PTS;
			pstVdispCh->u32PreOrgPts = pstSyncFrame->stDqFrame.ui32PTS;
			pstVdispCh->u32PreDispPeriod = pstSyncFrame->stDqFrame.ui32DisplayPeriod;

			stDqFrame2Clear = pstSyncFrame->stDqFrame;
			stDqFrame2Clear.ui32PTS = pstSyncFrame->ui32PTS;
			bValFrame2Clear = TRUE;
			goto re_pop;
		}
	}

	// Clear frame if need
	if( bValFrame2Clear )
	{
		if( bGotNewFrame )
		{
			// discard
			log_noti("[Vdisp%d] Discard -> clear frame\n", u8VdispCh);
			PTS_ClearFrame(u8VdispCh, &stDqFrame2Clear);
		}
		else
		{
			if( VDEC_RATE_Get_Speed(u8VdispCh) < 0 )
				PTS_ClearFrame(u8VdispCh, &stDqFrame2Clear);
			else
			{
				// revival pre-discarded frame
				bGotNewFrame = TRUE;
				*pstNextFrame = stDqFrame2Clear;
			}

			bValFrame2Clear = FALSE;
		}
	}

	// when new frame turned to be activated
	if( bGotNewFrame )
	{
		log_user2("[Vdisp%d] Pop Idx %2d  bValClr %d  Match %d\n",
				u8VdispCh, pstNextFrame->ui32FrameIdx, bValFrame2Clear, eMatch
				);

		if( pstVdispCh->Status.bStepping == TRUE )
		{
			pstVdispCh->Status.bStepping = FALSE;
			pstVdispCh->State = VDISP_PAUSE;
		}

		bInterlaced = _VDISP_IsInterlacedFrame( pstNextFrame );

		VDEC_RATE_GetFrameRateResDiv(u8VdispCh, &(pstNextFrame->ui32FrameRateRes),
				&(pstNextFrame->ui32FrameRateDiv));

		i32Diff = PTS_GetDiff(pstVdispCh->pstSync);
		if( i32Diff )
		{
			UINT32 ui32FrameDuration = VDEC_RATE_GetFrameRateDuration(u8VdispCh);
			if( i32Diff >= -((SINT32)ui32FrameDuration-270) && i32Diff < -270 )
			{
				VSync_SetPhaseShift(pstVdispCh->Config.ui8VSyncCh, -i32Diff);
			}
		}

		VSync_SetNextVsyncField(pstVdispCh->Config.ui8VSyncCh,
				pstNextFrame->ui32FrameRateRes, pstNextFrame->ui32FrameRateDiv,
				bInterlaced);
	}

	return bGotNewFrame;
}

BOOLEAN VDISP_SetNewFrame(VDISP_CH_T *pstVdispCh, S_DISPQ_BUF_T *pstDqFrame,
		UINT32 ui32SyncField)
{
	UINT8	u8VdispCh;
	BOOLEAN bSet;

	if( pstVdispCh->State == VDISP_PLAY || pstVdispCh->State == VDISP_PAUSE )
	{
	}
	else
		return FALSE;

	u8VdispCh = pstVdispCh->u8VdispCh;

	if(pstVdispCh->Status.bFreeze)
	{
		PTS_ClearFrame(u8VdispCh, pstDqFrame);
		return TRUE;
	}

	log_user3("Frame2Disp STC %d Vdisp%d Idx %2d  Rate %d/%d DTS %5u PTS %5u Dispi %d\n",
			VDISP_GetSTC(u8VdispCh),
			u8VdispCh, pstDqFrame->ui32FrameIdx,
			pstDqFrame->ui32FrameRateRes, pstDqFrame->ui32FrameRateDiv,
			pstDqFrame->ui32DTS, pstDqFrame->ui32PTS,
			pstDqFrame->ui32DisplayInfo);

	// use sequential 3D L/R option only for normal play speed
	if( VDEC_RATE_Get_Speed(u8VdispCh) != 1000 &&
			pstDqFrame->ui32LR_Order != DISPQ_3D_FRAME_NONE )
		pstDqFrame->ui32LR_Order |= (0x1 << 1);

	bSet = DE_IF_SetNewFrame(pstVdispCh->Config.eDeIfDstCh, pstDqFrame, ui32SyncField);
	if( bSet )
	{
		pstDqFrame->bDispResult = TRUE;
		pstVdispCh->Debug.u32nDispFrame++;

		if( pstVdispCh->bValidCurFrame )
			PTS_ClearFrame(pstVdispCh->u8VdispCh, &pstVdispCh->stCurFrame);

		pstVdispCh->stCurFrame = *pstDqFrame;
		pstVdispCh->bValidCurFrame = TRUE;
	}
	else
		VSync_SetPhaseShift(pstVdispCh->Config.ui8VSyncCh, 0);

	return bSet;
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
void VDISP_DE_IF_UpdateDisplay(UINT8 u8VdispCh, E_DE_IF_DST_T eDeIfDstCh,
		UINT32 ui32SyncField)
{
	VDISP_CH_T		*pstVdispCh;
	pstVdispCh = VDISP_GetHandler(u8VdispCh);

	if( pstVdispCh == NULL )
	{
		log_error("[Vdisp%d][Err] Fail get handler %s\n",
				u8VdispCh,__FUNCTION__ );
		return;
	}

	switch( pstVdispCh->State )
	{
	case VDISP_PAUSE :
	case VDISP_PLAY :
	  	DE_IF_UpdateDisplay(eDeIfDstCh, ui32SyncField);
		break;
	case VDISP_NULL :
	case VDISP_READY :
	default :
		if( ((pstVdispCh->Debug.ui32LogTick_UpdateBuf++) % 23) == 0 )
			log_noti("[Vdisp%d-%d][Warning] Current State, %s(%d)\n",
					pstVdispCh->u8VdispCh, pstVdispCh->State, __FUNCTION__, __LINE__ );
		break;
	}

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

void vdisp_debug_print_status(VDISP_CH_T *pstVdispCh, UINT32 u32Stc)
{
	static UINT32 u32PreStc[VDISP_NUM_OF_CHANNEL] = {0,};

	if( u32Stc-u32PreStc[pstVdispCh->u8VdispCh] >= 90000*2 )
	{
		UINT32 u32ElapseTime;
		static UINT8 i;

		u32ElapseTime = u32Stc - u32PreStc[pstVdispCh->u8VdispCh];

		if( i == 0 && u32ElapseTime )
		{
			log_noti("[Vdisp%d] Rate100:  Disp %d  Pop %d\n",
					pstVdispCh->u8VdispCh,
					pstVdispCh->Debug.u32nDispFrame*100*90000/u32ElapseTime,
					pstVdispCh->Debug.u32nPopFrame*100*90000/u32ElapseTime);
		}

		if( i == 1 )
		{
			//log_noti("[Vdisp%d] Match,", pstVdispCh->u8VdispCh);
		}


		if( (++i)==2 )
			i=0;

		u32PreStc[pstVdispCh->u8VdispCh] = u32Stc;
		pstVdispCh->Debug.u32nDispFrame = 0;
		pstVdispCh->Debug.u32nPopFrame = 0;
	}
}

static void vdisp_debug_search_frame(VDISP_CH_T *pstVdispCh)
{
#ifdef VDISP_DBG_LIPSYNC

	#define VDISP_DBG_N_FRAME 3
	UINT32 i;
	UINT32 u32Pts[VDISP_DBG_N_FRAME] =
	{
//0x709C2	//0x123234	// DivX A31 8 Hz
//0x6FAFE	//0x123234	// DivX A32 12 Hz
//0x98562	// DivX A08 15 Hz
//0x70C92	//0x1237D4	// DivX A34 15 Hz
//0x6FAFE	//0x123234	// DivX A12 24 Hz
//0x972C0	// DivX A22 25 Hz
//0x6F9F0	// DivX A50 25 Hz
//0x6F6C6	// DivX A27 29.97 Hz
//0x98562 //0x14BC98	// DivX A11 30 Hz
//0x14BC98	// DivX A20 50 Hz
//0x14B5EA	// DivX A21 59.94 Hz
//0x14B69E	// DivX A10 60 Hz
		//0x33E92C4,
		//0x3457E11,
		//0x34C695E

		//1080
		0xBD17ADD-3003,
		0xBD8662A,
		0xBDF5177


	};

	for(i=0; i<VDISP_DBG_N_FRAME; i++)
	{
		if(	pstVdispCh->stNextFrame.ui32PTS > u32Pts[i] - 100 &&
				pstVdispCh->stNextFrame.ui32PTS < u32Pts[i] + 100 )
		{
			UINT32 u32Stc = VDISP_GetSTC(pstVdispCh->u8VdispCh);
			u32VdecSendTime = u32Stc;
			log_noti("%d %d\n", u32Stc, pstVdispCh->stNextFrame.ui32PTS);
			printk("%d %d Idx %d\n", u32Stc, pstVdispCh->stNextFrame.ui32PTS,
					pstVdispCh->stNextFrame.ui32FrameIdx);

			while(1);
			break;
		}
	}
#endif

	return;
}

void VDISP_VsyncCallback(UINT8 u8VsyncCh, UINT8 u8nVdisp, UINT8 au8VdispCh[], UINT8 u8FieldInfo)
{
	UINT32			i, u32Stc;
	VDISP_CH_T		*pstVdispCh;
	BOOLEAN			bSet, bReqNewFrame;
	unsigned long flags;

	for( i = 0; i < u8nVdisp; i++ )
	{
		pstVdispCh = VDISP_GetHandler(au8VdispCh[i]);
		if( pstVdispCh == NULL )
		{
			log_error("[Vdisp%d][Err] Fail get handler\n", au8VdispCh[i]);
			continue;
		}

		spin_lock_irqsave (&pstVdispCh->stLock, flags);

		VDISP_RunCmd(pstVdispCh->u8VdispCh);

		bReqNewFrame = DE_IF_IsNeedNewFrame(pstVdispCh->Config.eDeIfDstCh);
		u32Stc = VDISP_GetSTC(pstVdispCh->u8VdispCh);

		PTS_WraparoundCheck(pstVdispCh->u8VdispCh, u32Stc);

		if( bReqNewFrame == TRUE )
		{
			if( !pstVdispCh->bValidNextFrame )
				pstVdispCh->bValidNextFrame = VDISP_GetNewFrame(pstVdispCh,
						&pstVdispCh->stNextFrame, u32Stc);

			if( pstVdispCh->bValidNextFrame )
			{
				bSet = VDISP_SetNewFrame(pstVdispCh, &pstVdispCh->stNextFrame, u8FieldInfo);

				if( bSet )
				{
					pstVdispCh->bValidNextFrame = FALSE;

					if( pstVdispCh->stSyncFrame.bValidPairFrame )
					{
						SYNC_FRAME_T *pstSyncFrame = &pstVdispCh->stSyncFrame;

						pstVdispCh->bLock4Pair = TRUE;

						pstVdispCh->stNextFrame = pstSyncFrame->stPairFrame;
						pstSyncFrame->bValidPairFrame = FALSE;
						pstVdispCh->bValidNextFrame = TRUE;

						VDISP_CheckFrame(pstVdispCh, &pstVdispCh->stNextFrame);
						pstSyncFrame->stDqFrame.bDispResult = FALSE;

						log_debug("Vdisp%d : Pair Lock\n", pstVdispCh->u8VdispCh);
					}
					else if( pstVdispCh->bLock4Pair == TRUE )
					{
						pstVdispCh->bLock4Pair = FALSE;
						log_debug("Vdisp%d : Pair Unlock\n", pstVdispCh->u8VdispCh);
					}

					vdisp_debug_search_frame(pstVdispCh);
				}
			}
		}

		VDISP_DE_IF_UpdateDisplay(pstVdispCh->u8VdispCh, pstVdispCh->Config.eDeIfDstCh,
				(UINT32)u8FieldInfo);

		vdisp_debug_print_status(pstVdispCh, u32Stc);

		spin_unlock_irqrestore (&pstVdispCh->stLock, flags);
	}

	DE_IF_RunVdo(u8FieldInfo);
/*
	for( i = 0; i < u8nVdisp; i++ )
	{
		pstVdispCh = VDISP_GetHandler(au8VdispCh[i]);

		// frame pre-fetch
		if( pstVdispCh->bValidNextFrame == FALSE )
		{
			pstVdispCh->bValidNextFrame = VDISP_GetNewFrame(pstVdispCh->u8VdispCh,
					VDISP_GetSTC(pstVdispCh->u8VdispCh),
					&pstVdispCh->stNextFrame);
		}
	}
	*/
}
#endif


