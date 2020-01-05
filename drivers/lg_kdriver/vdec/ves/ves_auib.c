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
 * date       2011.04.19
 * note       Additional information.
 *
 * @addtogroup lg1150_ves
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ves_auib.h"
#include "ves_cpb.h"

#include <linux/kernel.h>
#include <linux/wait.h>

#include "hma_alloc.h"

#include "../mcu/ipc_callback.h"
#include "../mcu/os_adap.h"

#include "../hal/pdec_hal_api.h"
#include "../hal/ipc_reg_api.h"
#include "../hal/top_hal_api.h"
#include "../hal/vdec_base.h"
#include "ves_drv.h"

#include "log.h"
/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define	VES_AUIB_NUM_OF_MEM			(VES_NUM_OF_CHANNEL * 2)		// H/W Queue & S/W Queue

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32 		ui32FrameRateRes;
	UINT32 		ui32FrameRateDiv;
	UINT64		ui64TimeStamp;
	UINT32		ui32UId;
	BOOLEAN		bRingBufferMode;
	BOOLEAN		b512bytesAligned;
	UINT32		ui32AuStartAddr;	// for not 512 bytes aligned buf
	UINT32 		ui32AuSize;
} S_SW_AUIB_T;

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
static struct
{
	UINT32 		ui32PhyBaseAddr_HwQ;	// constant
	UINT32 		*pui32VirBasePtr_HwQ;	// constant
	UINT32 		ui32BufSize_HwQ;		// constant

	UINT32 		ui32PhyBaseAddr_SwQ;	// constant
	UINT32 		*pui32VirBasePtr_SwQ;	// constant
	UINT32 		ui32BufSize_SwQ;		// constant

	UINT32 		ui32DecodeOffset_bytes;	// bytes size
	BOOLEAN		bIsHwPath;
	BOOLEAN		bFromTVP;

	// for Debug
	UINT32 		ui32WrOffset;		// variable
	UINT32 		ui32RdOffset;		// variable

	wait_queue_head_t wq;
} gsVesAuib[VES_NUM_OF_CHANNEL];

static struct
{
	BOOLEAN		bUsed;
	BOOLEAN		bAlloced;
	UINT32		ui32BufAddr;
	UINT32		ui32BufSize;
} gsAuibMem[VES_AUIB_NUM_OF_MEM];


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
void VES_AUIB_Init(void)
{
	UINT32	i;

	logm_info(vdec_ves, "[VES][DBG] \n" );


	for( i = 0; i < VES_NUM_OF_CHANNEL; i++ )
	{
		gsVesAuib[i].ui32PhyBaseAddr_HwQ = 0x0;
		gsVesAuib[i].pui32VirBasePtr_HwQ = NULL;
		gsVesAuib[i].ui32BufSize_HwQ = 0x0;

		gsVesAuib[i].ui32PhyBaseAddr_SwQ = 0x0;
		gsVesAuib[i].pui32VirBasePtr_SwQ = NULL;
		gsVesAuib[i].ui32BufSize_SwQ = 0x0;

		gsVesAuib[i].ui32DecodeOffset_bytes = 0x0;
		gsVesAuib[i].bIsHwPath = TRUE;
		gsVesAuib[i].bFromTVP = FALSE;

		gsVesAuib[i].ui32WrOffset = 0x0;
		gsVesAuib[i].ui32RdOffset = 0x0;

		init_waitqueue_head(&gsVesAuib[i].wq);
	}
}

wait_queue_head_t *VES_AUIB_GetWaitQueueHead(UINT8 ui8VesCh)
{
	return &gsVesAuib[ui8VesCh].wq;
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
static UINT32 _VES_AUIB_Alloc(UINT32 ui32BufSize)
{
	UINT32		i;
	UINT32		ui32BufAddr;

	for( i = 0; i < VES_AUIB_NUM_OF_MEM; i++ )
	{
		if( (gsAuibMem[i].bUsed == FALSE) &&
			(gsAuibMem[i].bAlloced == TRUE) &&
			(gsAuibMem[i].ui32BufSize == ui32BufSize) )
		{
			gsAuibMem[i].bUsed = TRUE;

			logm_info(vdec_ves, "[VES][DBG][AUIB] Addr: 0x%X, Size: 0x%X\n", gsAuibMem[i].ui32BufAddr, ui32BufSize);

			return gsAuibMem[i].ui32BufAddr;
		}
	}

	for( i = 0; i < VES_AUIB_NUM_OF_MEM; i++ )
	{
		if( gsAuibMem[i].bAlloced == FALSE )
			break;
	}
	if( i == VES_AUIB_NUM_OF_MEM )
	{
		logm_error(vdec_ves, "[VES][Err] Num of AUIB Pool, Request Buf Size: 0x%08X\n", ui32BufSize );
		for( i = 0; i < VES_AUIB_NUM_OF_MEM; i++ )
			logm_error(vdec_ves, "[VES][Err] Used:%d, Alloced:%d, BufAddr:0x%08X, BufSize:0x%08X\n", gsAuibMem[i].bUsed, gsAuibMem[i].bAlloced, gsAuibMem[i].ui32BufAddr, gsAuibMem[i].ui32BufSize );
		return 0x0;
	}

	ui32BufAddr = hma_alloc_user ("vdec", ui32BufSize + PDEC_AUI_SIZE, 1<<12, "ves_auib");
	if( ui32BufAddr == 0x0 )
	{
		logm_error(vdec_ves, "[VES][Err] Failed to hma_alloc, Request Buf Size: 0x%08X\n", ui32BufSize );
		for( i = 0; i < VES_AUIB_NUM_OF_MEM; i++ )
			logm_error(vdec_ves, "[VES][Err] Used:%d, Alloced:%d, BufAddr:0x%08X, BufSize:0x%08X\n", gsAuibMem[i].bUsed, gsAuibMem[i].bAlloced, gsAuibMem[i].ui32BufAddr, gsAuibMem[i].ui32BufSize );
		return 0x0;
	}
	ui32BufAddr = PDEC_AUIB_CEILING_16BYTES( ui32BufAddr );

	gsAuibMem[i].bUsed = TRUE;
	gsAuibMem[i].bAlloced = TRUE;
	gsAuibMem[i].ui32BufAddr = ui32BufAddr;
	gsAuibMem[i].ui32BufSize = ui32BufSize;

	logm_noti(vdec_ves, "[VES][DBG][AUIB] Addr: 0x%X, Size: 0x%X\n", ui32BufAddr, ui32BufSize);

	return ui32BufAddr;

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
static BOOLEAN _VES_AUIB_Free(UINT32 ui32BufAddr, UINT32 ui32BufSize)
{
	UINT32		i;

	for( i = 0; i < VES_AUIB_NUM_OF_MEM; i++ )
	{
		if( (gsAuibMem[i].bUsed == TRUE) &&
			(gsAuibMem[i].bAlloced == TRUE) &&
			(gsAuibMem[i].ui32BufAddr == ui32BufAddr) &&
			(gsAuibMem[i].ui32BufSize == ui32BufSize) )
		{
			gsAuibMem[i].bUsed = FALSE;

			logm_noti(vdec_ves, "[VES][DBG][AUIB] Addr: 0x%X, Size: 0x%X\n", ui32BufAddr, ui32BufSize);

			return TRUE;
		}
	}

	logm_error(vdec_ves, "[VES][Err] Not Matched AUIB Pool - 0x%X/0x%X \n\n", ui32BufAddr, ui32BufSize );

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
void VES_AUIB_UpdateWrPtr(UINT8 ui8VesCh, UINT32 ui32WrPhyAddr)
{
	gsVesAuib[ui8VesCh].ui32WrOffset = ui32WrPhyAddr - gsVesAuib[ui8VesCh].ui32PhyBaseAddr_HwQ;
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
void VES_AUIB_Reset(UINT8 ui8VesCh)
{
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		return;
	}

	logm_info(vdec_ves, "[VES%d][DBG] \n\n", ui8VesCh );

	// for Debug
	gsVesAuib[ui8VesCh].ui32WrOffset = 0;
	gsVesAuib[ui8VesCh].ui32RdOffset = 0;

	if( gsVesAuib[ui8VesCh].bIsHwPath == TRUE )
	{
		PDEC_HAL_AUIB_Init(ui8VesCh, gsVesAuib[ui8VesCh].ui32PhyBaseAddr_HwQ, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);
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
void VES_AUIB_Flush(UINT8 ui8VesCh)
{
	UINT32	ui32WrOffset;
	UINT32	ui32RdOffset;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh );
		return;
	}

	ui32WrOffset = gsVesAuib[ui8VesCh].ui32WrOffset;
	ui32RdOffset = gsVesAuib[ui8VesCh].ui32RdOffset;

	logm_info(vdec_ves, "[VES%d][DBG] WrOffset:%d, RdOffset:%d, BufSize:%d, \n\n", ui8VesCh, ui32WrOffset, ui32RdOffset, gsVesAuib[ui8VesCh].ui32BufSize_HwQ );

	gsVesAuib[ui8VesCh].ui32RdOffset = ui32WrOffset;
//	VES_AUIB_Reset(ui8VesCh);

	wake_up (&gsVesAuib[ui8VesCh].wq);
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
static void _VES_AUIB_SetDb(UINT8 ui8VesCh, UINT32 ui32DecodeOffset_bytes, UINT32 ui32AuibBufAddr_HwQ, UINT32 ui32AuibBufSize_HwQ, UINT32 ui32AuibBufAddr_SwQ, UINT32 ui32AuibBufSize_SwQ, BOOLEAN bIsHwPath, BOOLEAN bFromTVP)
{
	logm_noti(vdec_ves, "[VES%d][DBG] AUIB Hw Base: 0x%X, Size: 0x%X, Sw Base: 0x%X, Size: 0x%X \n", ui8VesCh, ui32AuibBufAddr_HwQ, ui32AuibBufSize_HwQ, ui32AuibBufAddr_SwQ, ui32AuibBufSize_SwQ);

	if( ui32AuibBufAddr_HwQ && ui32AuibBufSize_HwQ && ui32AuibBufAddr_SwQ && ui32AuibBufSize_SwQ )
	{
		gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ = VDEC_TranselateVirualAddr(ui32AuibBufAddr_HwQ, ui32AuibBufSize_HwQ);
		gsVesAuib[ui8VesCh].pui32VirBasePtr_SwQ = VDEC_TranselateVirualAddr(ui32AuibBufAddr_SwQ, ui32AuibBufSize_SwQ);
	}
	else
	{
		VDEC_ClearVirualAddr((void *)gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ);
		VDEC_ClearVirualAddr((void *)gsVesAuib[ui8VesCh].pui32VirBasePtr_SwQ);
		gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ = 0x0;
		gsVesAuib[ui8VesCh].pui32VirBasePtr_SwQ = 0x0;
	}

	gsVesAuib[ui8VesCh].ui32PhyBaseAddr_HwQ = ui32AuibBufAddr_HwQ;
	gsVesAuib[ui8VesCh].ui32BufSize_HwQ = ui32AuibBufSize_HwQ;
	gsVesAuib[ui8VesCh].ui32PhyBaseAddr_SwQ = ui32AuibBufAddr_SwQ;
	gsVesAuib[ui8VesCh].ui32BufSize_SwQ = ui32AuibBufSize_SwQ;

	gsVesAuib[ui8VesCh].ui32DecodeOffset_bytes = ui32DecodeOffset_bytes;
	gsVesAuib[ui8VesCh].bIsHwPath = bIsHwPath;
	gsVesAuib[ui8VesCh].bFromTVP = bFromTVP;

	gsVesAuib[ui8VesCh].ui32WrOffset = 0;
	gsVesAuib[ui8VesCh].ui32RdOffset = 0;

	if( bIsHwPath == TRUE )
		PDEC_HAL_AUIB_SetAuibVirBase(ui8VesCh, gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ);

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
BOOLEAN VES_AUIB_Open(UINT8 ui8VesCh, UINT32 ui32DecodeOffset_bytes, BOOLEAN bIsHwPath, BOOLEAN bFromTVP)
{
	UINT32 		ui32AuibBufAddr_HwQ;
	UINT32 		ui32AuibBufAddr_SwQ;
	UINT32 		ui32AuibBufSize_HwQ = VES_AUIB_NUM_OF_NODE * PDEC_AUI_SIZE;
	UINT32 		ui32AuibBufSize_SwQ = VES_AUIB_NUM_OF_NODE * sizeof(S_SW_AUIB_T);

	logm_noti(vdec_ves, "[VES%d][DBG] \n\n", ui8VesCh );

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		return FALSE;
	}

	ui32AuibBufAddr_HwQ = _VES_AUIB_Alloc( ui32AuibBufSize_HwQ );
	if( ui32AuibBufAddr_HwQ == 0x0 )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		return FALSE;
	}
	ui32AuibBufAddr_SwQ = _VES_AUIB_Alloc( ui32AuibBufSize_SwQ );
	if( ui32AuibBufAddr_SwQ == 0x0 )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		_VES_AUIB_Free(ui32AuibBufAddr_HwQ, ui32AuibBufSize_HwQ);
		return FALSE;
	}
	logm_info(vdec_ves, "[VES%d][DBG][AUIB] # of Node: %d, Decode Offset: %d \n", ui8VesCh, ui32AuibBufSize_HwQ/PDEC_AUI_SIZE, ui32DecodeOffset_bytes );

	_VES_AUIB_SetDb(ui8VesCh, ui32DecodeOffset_bytes, ui32AuibBufAddr_HwQ, ui32AuibBufSize_HwQ, ui32AuibBufAddr_SwQ, ui32AuibBufSize_SwQ, bIsHwPath, bFromTVP);

	if( bIsHwPath == TRUE )
	{
		if( bFromTVP == TRUE )
		{
			PDEC_HAL_Disable(ui8VesCh);
			PDEC_HAL_AUIB_Init(ui8VesCh, ui32AuibBufAddr_HwQ, ui32AuibBufSize_HwQ);
		}
		else
		{
			PDEC_HAL_AUIB_Init(ui8VesCh, ui32AuibBufAddr_HwQ, ui32AuibBufSize_HwQ);
			PDEC_HAL_AUIB_SetBufALevel(ui8VesCh, 80, 2);

			switch( ui8VesCh )
			{
			case 0 :
				TOP_HAL_EnableBufIntr(PDEC0_AUB_ALMOST_FULL);
				TOP_HAL_EnableBufIntr(PDEC0_AUB_ALMOST_EMPTY);
				break;
			case 1 :
				TOP_HAL_EnableBufIntr(PDEC1_AUB_ALMOST_FULL);
				TOP_HAL_EnableBufIntr(PDEC1_AUB_ALMOST_EMPTY);
				break;
			case 2 :
				TOP_HAL_EnableBufIntr(PDEC2_AUB_ALMOST_FULL);
				TOP_HAL_EnableBufIntr(PDEC2_AUB_ALMOST_EMPTY);
				break;
			default :
				logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
			}
		}
	}

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
void VES_AUIB_Close(UINT8 ui8VesCh)
{
	logm_info(vdec_ves, "[VES%d][DBG] \n\n", ui8VesCh );

	if( gsVesAuib[ui8VesCh].bIsHwPath == TRUE )
	{
		PDEC_HAL_AUIB_Init(ui8VesCh, 0x0, 0x0);

		switch( ui8VesCh )
		{
		case 0 :
			TOP_HAL_ClearBufIntr(PDEC0_AUB_ALMOST_FULL);
			TOP_HAL_DisableBufIntr(PDEC0_AUB_ALMOST_FULL);
			TOP_HAL_ClearBufIntr(PDEC0_AUB_ALMOST_EMPTY);
			TOP_HAL_DisableBufIntr(PDEC0_AUB_ALMOST_EMPTY);
			break;
		case 1 :
			TOP_HAL_ClearBufIntr(PDEC1_AUB_ALMOST_FULL);
			TOP_HAL_DisableBufIntr(PDEC1_AUB_ALMOST_FULL);
			TOP_HAL_ClearBufIntr(PDEC1_AUB_ALMOST_EMPTY);
			TOP_HAL_DisableBufIntr(PDEC1_AUB_ALMOST_EMPTY);
			break;
		case 2 :
			TOP_HAL_ClearBufIntr(PDEC2_AUB_ALMOST_FULL);
			TOP_HAL_DisableBufIntr(PDEC2_AUB_ALMOST_FULL);
			TOP_HAL_ClearBufIntr(PDEC2_AUB_ALMOST_EMPTY);
			TOP_HAL_DisableBufIntr(PDEC2_AUB_ALMOST_EMPTY);
			break;
		default :
			logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		}
	}

	_VES_AUIB_Free(gsVesAuib[ui8VesCh].ui32PhyBaseAddr_HwQ, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);
	_VES_AUIB_Free(gsVesAuib[ui8VesCh].ui32PhyBaseAddr_SwQ, gsVesAuib[ui8VesCh].ui32BufSize_SwQ);

	_VES_AUIB_SetDb(ui8VesCh, 0, 0x0, 0x0, 0x0, 0x0, FALSE, FALSE);
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
BOOLEAN VES_AUIB_Push(UINT8 ui8VesCh, S_VES_AU_T *pVesAu)
{
	UINT32		ui32WrOffset, ui32WrOffset_Next;
	UINT32		ui32RdOffset;
	UINT32 		ui32AU_Info0;
	UINT32 		*pui32WrVirPtr_HwQ;
	S_SW_AUIB_T 	*psWrVirPtr_SwQ;
	UINT32		ui32WrIndex;
	UINT32		ui32AuType;


	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		return FALSE;
	}

	ui32WrOffset = gsVesAuib[ui8VesCh].ui32WrOffset;
	ui32RdOffset = gsVesAuib[ui8VesCh].ui32RdOffset;

	ui32WrOffset_Next = PDEC_AUIB_NEXT_START_OFFSET(ui32WrOffset, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);
	if( ui32WrOffset_Next == ui32RdOffset )
	{
		logm_error(vdec_ves, "[VES%d][Err][AUIB] Overflow\n", ui8VesCh );
		return FALSE;
	}

	pui32WrVirPtr_HwQ = gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ + (ui32WrOffset>>2);
	psWrVirPtr_SwQ = (S_SW_AUIB_T *)gsVesAuib[ui8VesCh].pui32VirBasePtr_SwQ;

	if( pVesAu->bStccDiscontinuity & ~0x1 )
		logm_error(vdec_ves,  "[VES][Err] STC Discontinuity: 0x%X\n", pVesAu->bStccDiscontinuity );
	pVesAu->bStccDiscontinuity &= 0x1;

	if( pVesAu->bWrapAround & ~0x1 )
		logm_error(vdec_ves,  "[VES][Err] STC Wrap Around: 0x%X\n", pVesAu->bWrapAround );
	pVesAu->bWrapAround &= 0x1;

	ui32AuType = pVesAu->eAuType;
	if( ui32AuType & ~0xF )
		logm_error(vdec_ves,  "[VES][Err] Au Type: 0x%X\n", ui32AuType );
	ui32AuType &= 0xF;

	ui32WrIndex = ui32WrOffset / PDEC_AUI_SIZE;
	psWrVirPtr_SwQ[ui32WrIndex].ui32FrameRateRes = pVesAu->ui32FrameRateRes;
	psWrVirPtr_SwQ[ui32WrIndex].ui32FrameRateDiv = pVesAu->ui32FrameRateDiv;
	psWrVirPtr_SwQ[ui32WrIndex].ui64TimeStamp = pVesAu->ui64TimeStamp;
	psWrVirPtr_SwQ[ui32WrIndex].ui32UId = pVesAu->ui32UId;
	psWrVirPtr_SwQ[ui32WrIndex].bRingBufferMode = pVesAu->bRingBufferMode;
	psWrVirPtr_SwQ[ui32WrIndex].b512bytesAligned = pVesAu->b512bytesAligned;
	psWrVirPtr_SwQ[ui32WrIndex].ui32AuSize = pVesAu->ui32AuSize;

	if( pVesAu->b512bytesAligned == TRUE )
	{
		if( pVesAu->ui32AuStartAddr & 0x1FF ) // check 512 bytes align
			logm_error(vdec_ves,  "[VES][Err] AU Start Address: 0x%X is not aligned\n", pVesAu->ui32AuStartAddr );
		pVesAu->ui32AuStartAddr &= 0xFFFFFE00;

		ui32AU_Info0 = pVesAu->ui32AuStartAddr | (pVesAu->bStccDiscontinuity << 7) | (pVesAu->bWrapAround << 4)  | (ui32AuType << 0);
	}
	else
	{
		psWrVirPtr_SwQ[ui32WrIndex].ui32AuStartAddr = pVesAu->ui32AuStartAddr;

		ui32AU_Info0 = (pVesAu->bStccDiscontinuity << 7) | (pVesAu->bWrapAround << 4)  | (ui32AuType << 0);
	}
	pui32WrVirPtr_HwQ[0] = ui32AU_Info0;
	pui32WrVirPtr_HwQ[1] = pVesAu->ui32DTS;
	pui32WrVirPtr_HwQ[2] = pVesAu->ui32PTS;
	pui32WrVirPtr_HwQ[3] = pVesAu->ui32AuEndAddr;

	logm_info(vdec_ves, "[VES%d] AUIB Pushed - Typd:%d, PTS:%d, TS:%llu, Start:%x, End:%x \n",ui8VesCh,pVesAu->eAuType,pVesAu->ui32PTS,pVesAu->ui64TimeStamp,pVesAu->ui32AuStartAddr-VES_CPB_GetBufferBaseAddr(ui8VesCh),pVesAu->ui32AuEndAddr-VES_CPB_GetBufferBaseAddr(ui8VesCh));
	gsVesAuib[ui8VesCh].ui32WrOffset = ui32WrOffset_Next;

	return TRUE;
}

/**
********************************************************************************
* @brief
*  common interface for both file play and broadcast
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
BOOLEAN VES_AUIB_Pop(UINT8 ui8VesCh, S_VES_AU_T *pVesAu)
{
	UINT32 		ui32WrOffset;
	UINT32 		ui32RdOffset, ui32RdOffset_Next = 0xFFFFFFFF;
	UINT32 		*pui32RdVirPtr_HwQ;
	S_SW_AUIB_T 	*psRdVirPtr_SwQ;
	UINT32 		ui32AU_Info0;
	UINT32		ui32RdIndex;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		return FALSE;
	}

	ui32WrOffset = gsVesAuib[ui8VesCh].ui32WrOffset;
	ui32RdOffset = gsVesAuib[ui8VesCh].ui32RdOffset;

	if( ui32WrOffset == ui32RdOffset )
	{
		logm_error(vdec_ves, "[VES%d][Warning][AUIB] Underrun \n", ui8VesCh);
		return FALSE;
	}

	if( VES_CPB_GetUsedBuffer(ui8VesCh) < gsVesAuib[ui8VesCh].ui32DecodeOffset_bytes )
		return FALSE;
	else
		gsVesAuib[ui8VesCh].ui32DecodeOffset_bytes = 0;

	pui32RdVirPtr_HwQ = gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ + (ui32RdOffset>>2);
	psRdVirPtr_SwQ = (S_SW_AUIB_T *)gsVesAuib[ui8VesCh].pui32VirBasePtr_SwQ;
	ui32AU_Info0 = pui32RdVirPtr_HwQ[0];
	pVesAu->eAuType = (E_VES_AU_T)ui32AU_Info0 & 0x0000000F;
	pVesAu->bStccDiscontinuity = (ui32AU_Info0 & 0x0000080) >> 7;
	pVesAu->bWrapAround = (ui32AU_Info0 & 0x0000010) >> 4;

	if( (gsVesAuib[ui8VesCh].bIsHwPath == TRUE) && (gsVesAuib[ui8VesCh].bFromTVP == FALSE) )
	{
		// 2: for End Address
		ui32RdOffset_Next = PDEC_AUIB_NEXT_START_OFFSET(ui32RdOffset, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);
		if( ui32WrOffset == ui32RdOffset_Next )
		{
			logm_error(vdec_ves, "[VES%d][Warning][AUIB] Underrun 2 \n", ui8VesCh);
			return FALSE;
		}

		pVesAu->ui32AuStartAddr = ui32AU_Info0 & 0xFFFFFE00;
		if( pVesAu->ui32AuStartAddr < VES_CPB_GetBufferBaseAddr(ui8VesCh) )
			logm_error(vdec_ves, "[VES%d][Err][AUIB] AU Start Addr: 0x%X, Base Addr: %d\n", ui8VesCh, pVesAu->ui32AuStartAddr, VES_CPB_GetBufferBaseAddr(ui8VesCh) );

		pVesAu->bCHB_Valid = (ui32AU_Info0 & 0x0000100) >> 8;
		pVesAu->bGopHeader = (ui32AU_Info0 & 0x0000020) >> 5;
		pVesAu->ui32DTS = (pui32RdVirPtr_HwQ[1] & 0x0FFFFFFF);
		pVesAu->ui32PTS = (pui32RdVirPtr_HwQ[2] & 0x0FFFFFFF);
		pVesAu->DTS_PTS_flag = ((pui32RdVirPtr_HwQ[3] & 0xC0000000) >> 30);
		pVesAu->ui32AUPaircheck = (pui32RdVirPtr_HwQ[3] & 0x00000001);

		pVesAu->ui32FrameRateRes = 0x0;
		pVesAu->ui32FrameRateDiv = 0xFFFFFFFF;
		pVesAu->ui64TimeStamp = 0;
		pVesAu->ui32UId = 0;

		pVesAu->bRingBufferMode = TRUE;
		pVesAu->b512bytesAligned = TRUE;

		pui32RdVirPtr_HwQ = gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ + (ui32RdOffset_Next>>2);
		ui32AU_Info0 = pui32RdVirPtr_HwQ[0];
		pVesAu->ui32AuEndAddr = ui32AU_Info0 & 0xFFFFFE00;

		if( pVesAu->ui32AuEndAddr >= pVesAu->ui32AuStartAddr )
			pVesAu->ui32AuSize = pVesAu->ui32AuEndAddr - pVesAu->ui32AuStartAddr;
		else
			pVesAu->ui32AuSize = pVesAu->ui32AuEndAddr + VES_CPB_GetBufferSize(ui8VesCh) - pVesAu->ui32AuStartAddr;

		logm_info(vdec_ves, "[VES%d][AUIB] AUIB Popped(L) - Type:%d,PTS:%d,Start:%x, End:%x, CPBWr:%x\n", ui8VesCh,pVesAu->eAuType,pVesAu->ui32PTS,pVesAu->ui32AuStartAddr-VES_CPB_GetBufferBaseAddr(ui8VesCh), pVesAu->ui32AuEndAddr-VES_CPB_GetBufferBaseAddr(ui8VesCh),VES_CPB_GetPhyWrPtr(ui8VesCh)-VES_CPB_GetBufferBaseAddr(ui8VesCh));
}
	else
	{
#if 0
		UINT32	ui32CpbWrPtr, ui32CpbRdPtr;
		UINT32	ui32CpbWrPtr_Bottom, ui32CpbWrPtr_Ceiling;
		UINT32  diff;


		ui32CpbWrPtr_Bottom = VES_CPB_BOTTOM_512BYTES(ui32CpbWrPtr);
		if( ui32CpbWrPtr_Bottom == (VES_CPB_GetBufferBaseAddr(ui8VesCh) + VES_CPB_GetBufferSize(ui8VesCh)) )
			ui32CpbWrPtr_Bottom = VES_CPB_GetBufferBaseAddr(ui8VesCh);
		ui32CpbWrPtr_Ceiling = ui32CpbWrPtr_Bottom + 512;
		if( (ui32CpbWrPtr_Bottom < pVesAu->ui32AuEndAddr) && (pVesAu->ui32AuEndAddr <= ui32CpbWrPtr_Ceiling) )

		//junghyun.son modified Underrun Control Scheme
		// WrPtr->AuEndAddr(Update by IO_Update_buffer)
		// RdPtr->AuEndAddr(Update by AUIB_POP)

		ui32CpbWrPtr = VES_CPB_GetPhyWrPtr(ui8VesCh);
		ui32CpbRdPtr = VES_CPB_GetPhyRdPtr(ui8VesCh);
		if(ui32CpbRdPtr > ui32CpbWrPtr) diff = ui32CpbWrPtr + VES_CPB_GetBufferSize(ui8VesCh)- ui32CpbRdPtr;
		else diff = ui32CpbWrPtr - ui32CpbRdPtr;
		if( diff < 1024 )
		{
			//logm_error(vdec_ves, "[VES%d][Warning][AUIB] Underrun 3 - Not Enough %d / 512 Bytes, ui32CpbWrPtr: 0x%X, ui32CpbRdPtr: 0x%X\n", ui8VesCh, ui32CpbWrPtr - ui32CpbRdPtr, ui32CpbWrPtr, ui32CpbRdPtr );
			return FALSE;
		}
#endif
		pVesAu->ui32AuEndAddr = pui32RdVirPtr_HwQ[3];
		pVesAu->ui32DTS = pui32RdVirPtr_HwQ[1];
		pVesAu->ui32PTS = pui32RdVirPtr_HwQ[2];
		pVesAu->bWrapAround = FALSE;

//		VDEC_KDRV_Message(MONITOR, "[VES%d][DBG] D(P)TS: %d/%u, GSTC: %u\n", ui8VesCh, pui32RdVirPtr_HwQ[2], pVesAu->ui32PTS, TOP_HAL_GetGSTCC());

		ui32RdIndex = ui32RdOffset / PDEC_AUI_SIZE;
		pVesAu->ui32FrameRateRes = psRdVirPtr_SwQ[ui32RdIndex].ui32FrameRateRes;
		pVesAu->ui32FrameRateDiv = psRdVirPtr_SwQ[ui32RdIndex].ui32FrameRateDiv;
		pVesAu->ui64TimeStamp = psRdVirPtr_SwQ[ui32RdIndex].ui64TimeStamp;
		pVesAu->ui32UId = psRdVirPtr_SwQ[ui32RdIndex].ui32UId;
		pVesAu->bRingBufferMode = psRdVirPtr_SwQ[ui32RdIndex].bRingBufferMode;
		pVesAu->b512bytesAligned = psRdVirPtr_SwQ[ui32RdIndex].b512bytesAligned;
		pVesAu->ui32AuSize = psRdVirPtr_SwQ[ui32RdIndex].ui32AuSize;
		if( pVesAu->b512bytesAligned == TRUE )
			pVesAu->ui32AuStartAddr =  ui32AU_Info0 & 0xFFFFFE00;
		else
		{
			pVesAu->ui32AuStartAddr =  psRdVirPtr_SwQ[ui32RdIndex].ui32AuStartAddr;
		}

		pui32RdVirPtr_HwQ = gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ + (ui32RdOffset>>2);

		logm_info(vdec_ves, "[VES%d][AUIB] AUIB Popped(F) - Type:%d,TS:%llu,Start:%x, End:%x, CPBWr:%x \n", ui8VesCh,pVesAu->eAuType,pVesAu->ui64TimeStamp,pVesAu->ui32AuStartAddr-VES_CPB_GetBufferBaseAddr(ui8VesCh), pVesAu->ui32AuEndAddr-VES_CPB_GetBufferBaseAddr(ui8VesCh),VES_CPB_GetPhyWrPtr(ui8VesCh)-VES_CPB_GetBufferBaseAddr(ui8VesCh));
		//wake_up (&gsVesAuib[ui8VesCh].wq);
	}

	//logm_debug(vdec_ves, "[VES%d][DBG][AUIB] Start:0x%X, End:0x%X, Offset:0x%X\n", ui8VesCh, pVesAu->ui32AuStartAddr, pVesAu->ui32AuEndAddr, ui32RdOffset );

	//if( ui32RdOffset_Next == 0xFFFFFFFF )
	//	ui32RdOffset_Next = PDEC_AUIB_NEXT_START_OFFSET(ui32RdOffset, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);

	//gsVesAuib[ui8VesCh].ui32RdOffset = ui32RdOffset_Next;
	//if(gsVesAuib[ui8VesCh].bIsHwPath == TRUE) PDEC_HAL_AUIB_SetRdPtr(ui8VesCh, ui32RdOffset_Next);
	//VES_CPB_UpdateRdPtr(ui8VesCh, pVesAu->ui32AuEndAddr);

	return TRUE;
}

void VES_AUIB_ConsumeOneAU(UINT8 ui8VesCh)
{
	UINT32 ui32RdOffset_Next = PDEC_AUIB_NEXT_START_OFFSET(gsVesAuib[ui8VesCh].ui32RdOffset, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);
	gsVesAuib[ui8VesCh].ui32RdOffset = ui32RdOffset_Next;

	if(gsVesAuib[ui8VesCh].bIsHwPath)
	{
		ui32RdOffset_Next = gsVesAuib[ui8VesCh].ui32PhyBaseAddr_HwQ + ui32RdOffset_Next;
		PDEC_HAL_AUIB_SetRdPtr(ui8VesCh, ui32RdOffset_Next);
	}
	else
	{
		wake_up (&gsVesAuib[ui8VesCh].wq);
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
void VDEC_ISR_AUIB_AlmostFull(UINT8 ui8VesCh)
{
	S_IPC_CALLBACK_BODY_CPBSTATUS_T sReportCpbStatus;

	if( ui8VesCh >= PDEC_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number, \n\n", ui8VesCh );
		return;
	}

	switch( ui8VesCh )
	{
	case 0 :
		TOP_HAL_ClearBufIntr(PDEC0_AUB_ALMOST_FULL);
		break;
	case 1 :
		TOP_HAL_ClearBufIntr(PDEC1_AUB_ALMOST_FULL);
		break;
	case 2 :
		TOP_HAL_ClearBufIntr(PDEC2_AUB_ALMOST_FULL);
		break;
	default :
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
	}

	sReportCpbStatus.priv = VES_GetVdecPriv(ui8VesCh);
	sReportCpbStatus.eBufStatus = CPB_STATUS_ALMOST_FULL;
	IPC_CALLBACK_Report_CpbStatus( &sReportCpbStatus );

	logm_error(vdec_ves, "[VES%d][Err][AUIB] Almost Full - Buf Status: %d \n", ui8VesCh, PDEC_HAL_AUIB_GetStatus(ui8VesCh) );
	logm_debug(vdec_ves, "[VES%d][DBG] Buffer Status: 0x%X \n", ui8VesCh, PDEC_HAL_GetBufferStatus(ui8VesCh) );

//	PDEC_HAL_Ignore_Stall(ui8VesCh);
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
void VDEC_ISR_AUIB_AlmostEmpty(UINT8 ui8VesCh)
{
	if( ui8VesCh >= PDEC_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number, \n\n", ui8VesCh );
		return;
	}

	switch( ui8VesCh )
	{
	case 0 :
		TOP_HAL_ClearBufIntr(PDEC0_AUB_ALMOST_EMPTY);
		break;
	case 1 :
		TOP_HAL_ClearBufIntr(PDEC1_AUB_ALMOST_EMPTY);
		break;
	case 2 :
		TOP_HAL_ClearBufIntr(PDEC2_AUB_ALMOST_EMPTY);
		break;
	default :
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
	}

	logm_debug(vdec_ves, "[VES%d][DBG][AUIB] Almost Empty - Buf Status: %d \n", ui8VesCh, PDEC_HAL_AUIB_GetStatus(ui8VesCh) );
	logm_debug(vdec_ves, "[VES%d][DBG] Buffer Status: 0x%X \n", ui8VesCh, PDEC_HAL_GetBufferStatus(ui8VesCh) );
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
UINT32 VES_AUIB_NumActive(UINT8 ui8VesCh)
{
	UINT32 	*pui32RdVirPtr_HwQ;
	UINT32	ui32UsedBuf;
	UINT32	ui32WrOffset;
	UINT32	ui32RdOffset,ui32RdOffset_Next;
	UINT32	i;
	UINT32  ui32NumActive;
	UINT32  ui32CPBWrOffset,ui32CPBRdOffset;
	UINT32  ui32AUStartAddress,ui32AUEndAddress;
	SINT32  diff=0;
//	static UINT32 ui32NumActiveCnt = 0;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		return 0;
	}

	ui32WrOffset = gsVesAuib[ui8VesCh].ui32WrOffset;
	ui32RdOffset = gsVesAuib[ui8VesCh].ui32RdOffset;

	if( (gsVesAuib[ui8VesCh].bIsHwPath == TRUE) && (gsVesAuib[ui8VesCh].bFromTVP == FALSE) )
	{
		for( i = 0; i < 1; i++ ) // for End Address
		{
			if( ui32WrOffset == ui32RdOffset )
				break;

			ui32WrOffset = PDEC_AUIB_PREV_START_OFFSET(ui32WrOffset, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);
		}
	}

	if( ui32WrOffset >= ui32RdOffset )
		ui32UsedBuf = ui32WrOffset - ui32RdOffset;
	else
		ui32UsedBuf = ui32WrOffset + gsVesAuib[ui8VesCh].ui32BufSize_HwQ - ui32RdOffset;

	ui32NumActive = ui32UsedBuf / PDEC_AUI_SIZE;

	if( gsVesAuib[ui8VesCh].bIsHwPath == TRUE && ui32NumActive > 0) {

		ui32CPBWrOffset = VES_CPB_GetPhyWrPtr(ui8VesCh) - VES_CPB_GetBufferBaseAddr(ui8VesCh);
		ui32CPBRdOffset = VES_CPB_GetPhyRdPtr(ui8VesCh) - VES_CPB_GetBufferBaseAddr(ui8VesCh);

		if(ui32CPBWrOffset == ui32CPBRdOffset) {
			logm_noti(vdec_ves, "[VES%d]Nothing new data, active num:%d \n",ui8VesCh,ui32NumActive);
			return 0;
		}

		ui32RdOffset_Next = PDEC_AUIB_NEXT_START_OFFSET(ui32RdOffset, gsVesAuib[ui8VesCh].ui32BufSize_HwQ);
		pui32RdVirPtr_HwQ = gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ + (ui32RdOffset>>2);
		ui32AUStartAddress = (pui32RdVirPtr_HwQ[0] & 0xFFFFFE00) - VES_CPB_GetBufferBaseAddr(ui8VesCh);
		pui32RdVirPtr_HwQ = gsVesAuib[ui8VesCh].pui32VirBasePtr_HwQ + (ui32RdOffset_Next>>2);
		ui32AUEndAddress = (pui32RdVirPtr_HwQ[0] & 0xFFFFFE00) - VES_CPB_GetBufferBaseAddr(ui8VesCh);

		// |wrptr 							[austart    <-- 이 상태
		if(ui32CPBWrOffset <= ui32AUStartAddress)
			ui32CPBWrOffset += VES_CPB_GetBufferSize(ui8VesCh);
		// auend]							[austart   <-- 이 상태
		if(ui32AUEndAddress < ui32AUStartAddress) ui32AUEndAddress += VES_CPB_GetBufferSize(ui8VesCh);

		logm_trace(vdec_ves, "[VES%d]AuStart:%x, AuEnd:%x, Write:%x, Size:%x \n",ui8VesCh,ui32AUStartAddress,ui32AUEndAddress,ui32CPBWrOffset,VES_CPB_GetBufferSize(ui8VesCh));

		diff =  ui32CPBWrOffset - ui32AUEndAddress;

		if( diff < 0 ){
			logm_noti(vdec_ves,"[VES%d]AUEndAddr over Wrptr (diff:%d), Active AUIB:%d exists \n",ui8VesCh,diff,ui32NumActive);
			return 0;
		}
		logm_info(vdec_ves, "[VES%d][AUIB] AUIB NumActive:%d, usable CPB:%d \n", ui8VesCh,ui32NumActive,diff);
	}
	return ui32NumActive;
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
UINT32 VES_AUIB_NumFree(UINT8 ui8VesCh)
{
	UINT32	ui32FreeBuf;
	UINT32	ui32WrOffset;
	UINT32	ui32RdOffset;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n\n", ui8VesCh );
		return 0;
	}

	ui32WrOffset = gsVesAuib[ui8VesCh].ui32WrOffset;
	ui32RdOffset = gsVesAuib[ui8VesCh].ui32RdOffset;

	if( ui32WrOffset < ui32RdOffset )
		ui32FreeBuf = ui32RdOffset - ui32WrOffset;
	else
		ui32FreeBuf = ui32RdOffset + gsVesAuib[ui8VesCh].ui32BufSize_HwQ - ui32WrOffset;

	return ((ui32FreeBuf / PDEC_AUI_SIZE) - 1);
}


