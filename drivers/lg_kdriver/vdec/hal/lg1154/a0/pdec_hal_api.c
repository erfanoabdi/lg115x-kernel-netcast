
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
 * date       2011.04.29
 * note       Additional information.
 *
 * @addtogroup h13_vdec
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "../lg1154_vdec_base.h"
#include "../top_hal_api.h"
#include "../pdec_hal_api.h"
#include "pdec_reg.h"

#ifndef __XTENSA__
#include <linux/kernel.h>
#include <asm/cacheflush.h>
#include <linux/version.h>
#include <linux/dma-mapping.h>
#endif

#include "../../../mcu/os_adap.h"

#define LOG_NAME vdec_hal_pdec
#include "log.h"


/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
//#define		L9_A0_WORKAROUND

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define 		H13_PDEC_BASE(ch)							(H13_VDEC_BASE + 0x0800 + (ch*0x100))

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

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
	UINT8 		*pui8CpbVirBase;		// constant
	UINT32 		*pui32AuibVirBase;		// constant
	UINT32 		ui32AuibWrOffset_Prev;	// variable

	volatile PDEC_REG_T		*stpReg;

#ifdef L9_A0_WORKAROUND
	UINT32		ui32SeqEndCpbOffset;
	BOOLEAN		bEOS_Found;
	UINT32		ui32AuStartAddr_HW;
	UINT32		ui32AddrMismatchingCnt;
#endif
}gsPdecHal[PDEC_NUM_OF_CHANNEL];


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
void PDEC_HAL_Init(void)
{
	UINT8				ui8PdecCh;
	REG_PDEC_CONF		reg_pdec_conf;

	log_debug ("[PDEC][DBG] %s", __FUNCTION__ );

	for( ui8PdecCh = 0; ui8PdecCh < PDEC_NUM_OF_CHANNEL; ui8PdecCh++ )
	{
		gsPdecHal[ui8PdecCh].stpReg = (volatile PDEC_REG_T *)VDEC_TranselateVirualAddr(H13_PDEC_BASE(ui8PdecCh), 0x100);
		gsPdecHal[ui8PdecCh].stpReg->reg_aux_mode  = 0x40000010;

		reg_pdec_conf = gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf;
		reg_pdec_conf.reg_scd_en = 0;
		reg_pdec_conf.reg_pdec_en = 0;
		reg_pdec_conf.reg_aub_intr_chk_en = 0;
		reg_pdec_conf.reg_video_standard = 0;
		reg_pdec_conf.reg_pdec_endian = 0;
		reg_pdec_conf.reg_srst = 0;
		gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf = reg_pdec_conf;

		PDEC_HAL_CPB_Init(ui8PdecCh, 0x0, 0x0);
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
void PDEC_HAL_Reset(UINT8 ui8PdecCh)
{
	volatile REG_PDEC_CONF         reg_pdec_conf;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	// PDEC sw reset
	reg_pdec_conf = gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf;
	reg_pdec_conf.reg_srst = 0x7;
	gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf = reg_pdec_conf;

	// PDEC au_detection interrupt clear
	TOP_HAL_ClearExtIntr(PDEC0_AU_DETECT+ui8PdecCh);

	reg_pdec_conf = gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf;
	while( reg_pdec_conf.reg_srst )
	{ // wait sw reset ack
		reg_pdec_conf = gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf;
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
void PDEC_HAL_Enable(UINT8 ui8PdecCh)
{
	volatile REG_PDEC_CONF         reg_pdec_conf;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_pdec_conf = gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf;

	reg_pdec_conf.reg_scd_en = 1;
	reg_pdec_conf.reg_pdec_en = 1;

	gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf = reg_pdec_conf;
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
void PDEC_HAL_Disable(UINT8 ui8PdecCh)
{
	volatile REG_PDEC_CONF         reg_pdec_conf;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_pdec_conf = gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf;

	reg_pdec_conf.reg_scd_en = 0;
	reg_pdec_conf.reg_pdec_en = 0;

	gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf = reg_pdec_conf;
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
void PDEC_HAL_SetVideoStandard(UINT8 ui8PdecCh, UINT8 ui8Vcodec)
{
	volatile REG_PDEC_CONF         reg_pdec_conf;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_pdec_conf = gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf;

	reg_pdec_conf.reg_video_standard = ui8Vcodec;

	gsPdecHal[ui8PdecCh].stpReg->reg_pdec_conf = reg_pdec_conf;
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
void PDEC_HAL_Pause(UINT8 ui8PdecCh)
{
	volatile UINT32 reg_trick_mode;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_trick_mode = gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode;

	reg_trick_mode |= (1 << 4);

	gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode = reg_trick_mode;
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
void PDEC_HAL_Resume(UINT8 ui8PdecCh)
{
	volatile UINT32 reg_trick_mode;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_trick_mode = gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode;

	reg_trick_mode &= ~(1 << 4);

	gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode = reg_trick_mode;
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
void PDEC_HAL_SetBypass(UINT8 ui8PdecCh)
{
	volatile UINT32 reg_trick_mode;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_trick_mode = gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode;

	reg_trick_mode |= (1 << 2);

	gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode = reg_trick_mode;
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
void PDEC_HAL_UnsetBypass(UINT8 ui8PdecCh)
{
	volatile UINT32 reg_trick_mode;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_trick_mode = gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode;

	reg_trick_mode &= ~(1 << 2);

	gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode = reg_trick_mode;
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
void PDEC_HAL_SkipPicFrame(UINT8 ui8PdecCh, S_PDEC_SKIP_FRAME_T eSkipFrame)
{
	volatile UINT32 reg_trick_mode;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_trick_mode = gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode;
	reg_trick_mode &= ~(0x3 << 0);

	switch( eSkipFrame )
	{
	case PDEC_SKIP_NON_FRAME :
		break;
	case PDEC_SKIP_B_FRAME :
		reg_trick_mode |= (0x1 << 1);
		break;
	case PDEC_SKIP_BP_FRAME :
		reg_trick_mode |= (0x3 << 0);
		break;
	default :
		log_error ("[PDEC%d][Err] Skip Frame: %d, %s", ui8PdecCh, eSkipFrame, __FUNCTION__ );
	}

	gsPdecHal[ui8PdecCh].stpReg->reg_trick_mode = reg_trick_mode;
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
void PDEC_HAL_Ignore_Stall(UINT8 ui8PdecCh)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	log_debug ("[PDEC%d][DBG] %s", ui8PdecCh, __FUNCTION__ );

	gsPdecHal[ui8PdecCh].stpReg->reg_aux_mode |= 0x00030000;
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
void PDEC_HAL_CPB_Init(UINT8 ui8PdecCh, UINT32 ui32CpbBase, UINT32 ui32CpbSize)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	log_debug ("[PDEC%d][DBG][CPB] %s", ui8PdecCh, __FUNCTION__ );

	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_base = ui32CpbBase;
	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size = ui32CpbSize;
	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_wptr = ui32CpbBase;
	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_rptr = ui32CpbBase;
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
void PDEC_HAL_CPB_SetCpbVirBase(UINT8 ui8PdecCh, UINT8 *pui8CpbVirBase)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	log_debug ("[PDEC%d][DBG][CPB] %s", ui8PdecCh, __FUNCTION__ );

	gsPdecHal[ui8PdecCh].pui8CpbVirBase = pui8CpbVirBase;
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
UINT32 PDEC_HAL_GetCPBBase(UINT8 ui8PdecCh)
{
	return gsPdecHal[ui8PdecCh].stpReg->reg_cpb_base;
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
UINT32 PDEC_HAL_GetCPBSize(UINT8 ui8PdecCh)
{
	return gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size;
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
UINT32 PDEC_HAL_CPB_GetWrPtr(UINT8 ui8PdecCh)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	return gsPdecHal[ui8PdecCh].stpReg->reg_cpb_wptr;
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
void PDEC_HAL_CPB_SetWrPtr(UINT8 ui8PdecCh, UINT32 ui32CpbRdPtr)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_wptr = ui32CpbRdPtr;
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
UINT32 PDEC_HAL_CPB_GetRdPtr(UINT8 ui8PdecCh)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	return gsPdecHal[ui8PdecCh].stpReg->reg_cpb_rptr;
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
void PDEC_HAL_CPB_SetRdPtr(UINT8 ui8PdecCh, UINT32 ui32CpbRdPtr)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_rptr = ui32CpbRdPtr;
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
void PDEC_HAL_CPB_GetBufALevel(UINT8 ui8PdecCh, UINT32 *pui32AFullPercent, UINT32 *pui32AEmptyPercent)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	*pui32AFullPercent = gsPdecHal[ui8PdecCh].stpReg->reg_cpb_afull_level * 100 / gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size;
	*pui32AEmptyPercent = gsPdecHal[ui8PdecCh].stpReg->reg_cpb_aempty_level * 100 / gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size;
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
void PDEC_HAL_CPB_SetBufALevel(UINT8 ui8PdecCh, UINT32 ui32AFullPercent, UINT32 ui32AEmptyPercent)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_afull_level = gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size * ui32AFullPercent / 100;
	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_aempty_level = gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size * ui32AEmptyPercent / 100;
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
UINT32 PDEC_HAL_CPB_GetBufferLevel(UINT8 ui8PdecCh)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	return gsPdecHal[ui8PdecCh].stpReg->status_cpb_buf_level;
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
UINT32 PDEC_HAL_GetBufferStatus(UINT8 ui8PdecCh)
{
//	STATUS_BUF			status_buf;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	return *(volatile UINT32 *)&gsPdecHal[ui8PdecCh].stpReg->status_buf;
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
UINT32 PDEC_HAL_AUIB_GetStatus(UINT8 ui8PdecCh)
{
	STATUS_AUB			status_aub;
	UINT32				reg_aub_cnt = 0x0;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	status_aub = gsPdecHal[ui8PdecCh].stpReg->status_aub;
	if( status_aub.reg_aub_status == 0x00 )
		reg_aub_cnt = 0x0;
	else if( status_aub.reg_aub_status == 0x0F )
		reg_aub_cnt = 0xFFFFFFFF;
	else if( status_aub.reg_aub_status == 0x01 )
		reg_aub_cnt = status_aub.reg_aub_cnt;
	else
		log_error ("[PDEC%d][Err] reg_aub_status(0x%X) Field of STATUS_AUB", ui8PdecCh, status_aub.reg_aub_status );

	return reg_aub_cnt;
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
static void _PDEC_UTIL_AUI_Parse(UINT32 *pui32PdecAuiVirPtr, S_PDEC_AUI_T *pPdecAui)
{
	volatile UINT32	ui32PdecAuiAddr;
	volatile UINT32	ui32AU_Info0;

	ui32PdecAuiAddr = (UINT32)pui32PdecAuiVirPtr;
	if( ui32PdecAuiAddr != PDEC_AUIB_BOTTOM_16BYTES(ui32PdecAuiAddr) )
	{
		log_error ( "[PDEC][Err] PDEC AUI Address: 0x%X, %s", ui32PdecAuiAddr, __FUNCTION__ );
		return;
	}

	ui32AU_Info0 = pui32PdecAuiVirPtr[0];
	pPdecAui->ui32AuStartAddr =  ui32AU_Info0 & 0xFFFFFE00;
	pPdecAui->bIPicDetect = (BOOLEAN)((ui32AU_Info0 & 0x00000100) >> 8);
	pPdecAui->bStccDiscontinuity = (BOOLEAN)((ui32AU_Info0 & 0x00000080) >> 7);
	pPdecAui->bGopHeader = (BOOLEAN)((ui32AU_Info0 & 0x00000020) >> 5);
	pPdecAui->eAuType =  ui32AU_Info0 & 0x0000000F;
	pPdecAui->ui32DTS = pui32PdecAuiVirPtr[1] & 0x0FFFFFFF;
	pPdecAui->ui32PTS = pui32PdecAuiVirPtr[2] & 0x0FFFFFFF;

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
void PDEC_UTIL_SetDiscontinuity(UINT32 *pui32PdecAuiVirPtr, BOOLEAN bStccDiscontinuity)
{
	volatile UINT32	ui32AU_Info0;

	ui32AU_Info0 = pui32PdecAuiVirPtr[0];
	ui32AU_Info0 &= ~0x00000080;
	ui32AU_Info0 |= ((UINT32)(bStccDiscontinuity & 0x1) << 7);
	pui32PdecAuiVirPtr[0] = ui32AU_Info0;
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
void PDEC_UTIL_SetWrapAround(UINT32 *pui32PdecAuiVirPtr, BOOLEAN bWrapAround)
{
	volatile UINT32	ui32AU_Info0;

	ui32AU_Info0 = pui32PdecAuiVirPtr[0];
	ui32AU_Info0 &= ~0x00000010;
	ui32AU_Info0 |= ((UINT32)(bWrapAround & 0x1) << 4);
	pui32PdecAuiVirPtr[0] = ui32AU_Info0;
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
void PDEC_HAL_AUIB_GetBufALevel(UINT8 ui8PdecCh, UINT32 *pui32AFullPercent, UINT32 *pui32AEmptyPercent)
{
	REG_AUB_LEVEL		reg_aub_level;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_aub_level = gsPdecHal[ui8PdecCh].stpReg->reg_aub_level;

	*pui32AFullPercent = reg_aub_level.reg_aub_afull_level * 100 / gsPdecHal[ui8PdecCh].stpReg->reg_aub_size;
	*pui32AEmptyPercent = reg_aub_level.reg_aub_aempty_level * 100 / gsPdecHal[ui8PdecCh].stpReg->reg_aub_size;
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
void PDEC_HAL_AUIB_SetBufALevel(UINT8 ui8PdecCh, UINT32 ui32AFullPercent, UINT32 ui32AEmptyPercent)
{
	REG_AUB_LEVEL		reg_aub_level;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	reg_aub_level = gsPdecHal[ui8PdecCh].stpReg->reg_aub_level;

	reg_aub_level.reg_aub_afull_level = gsPdecHal[ui8PdecCh].stpReg->reg_aub_size * ui32AFullPercent / 100;
	reg_aub_level.reg_aub_aempty_level = gsPdecHal[ui8PdecCh].stpReg->reg_aub_size * ui32AEmptyPercent / 100;

	gsPdecHal[ui8PdecCh].stpReg->reg_aub_level = reg_aub_level;
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
void PDEC_HAL_AUIB_Init(UINT8 ui8PdecCh, UINT32 ui32AuibBase, UINT32 ui32AuibSize)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	log_debug ("[PDEC%d][DBG][AUIB] %s", ui8PdecCh, __FUNCTION__ );

	gsPdecHal[ui8PdecCh].stpReg->reg_aub_base = ui32AuibBase;
	gsPdecHal[ui8PdecCh].stpReg->reg_aub_size = ui32AuibSize >> 4;		// divide 16
	gsPdecHal[ui8PdecCh].stpReg->reg_aub_wptr = ui32AuibBase;
	gsPdecHal[ui8PdecCh].stpReg->reg_aub_rptr = ui32AuibBase;

	gsPdecHal[ui8PdecCh].ui32AuibWrOffset_Prev = 0;

#ifdef L9_A0_WORKAROUND
	gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset = 0x0;
	gsPdecHal[ui8PdecCh].bEOS_Found = FALSE;
	gsPdecHal[ui8PdecCh].ui32AuStartAddr_HW = 0x0;
	gsPdecHal[ui8PdecCh].ui32AddrMismatchingCnt = 0;
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
void PDEC_HAL_AUIB_SetAuibVirBase(UINT8 ui8PdecCh, UINT32 *pui32AuibVirBase)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	log_debug ("[PDEC%d][DBG][AUIB] %s", ui8PdecCh, __FUNCTION__ );

	gsPdecHal[ui8PdecCh].pui32AuibVirBase = pui32AuibVirBase;
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
UINT32 PDEC_HAL_AUIB_GetWrPtr(UINT8 ui8PdecCh, BOOLEAN bIsHwReg)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	return gsPdecHal[ui8PdecCh].stpReg->reg_aub_wptr;
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
void PDEC_HAL_AUIB_SetWrPtr(UINT8 ui8PdecCh, UINT32 ui32AubRdPtr)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	gsPdecHal[ui8PdecCh].stpReg->reg_aub_wptr = ui32AubRdPtr;
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
UINT32 PDEC_HAL_AUIB_GetRdPtr(UINT8 ui8PdecCh)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	return gsPdecHal[ui8PdecCh].stpReg->reg_aub_rptr;
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
void PDEC_HAL_AUIB_SetRdPtr(UINT8 ui8PdecCh, UINT32 ui32AubRdPtr)
{
	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	gsPdecHal[ui8PdecCh].stpReg->reg_aub_rptr = ui32AubRdPtr;
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
void PDEC_HAL_AUIB_Pop(UINT8 ui8PdecCh, S_PDEC_AUI_T *pPdecAui)
{
	UINT32	ui32AuibWrOffset;
	UINT32	ui32AuibRdOffset, ui32AuibRdOffset_Next;
	UINT32	*pui32AuibVirAddr;
	UINT32	ui32AuibSize;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}
	if( gsPdecHal[ui8PdecCh].pui32AuibVirBase == 0x0 )
	{
		log_error ("[PDEC%d][Err] Not Initialised, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	ui32AuibWrOffset = gsPdecHal[ui8PdecCh].stpReg->reg_aub_wptr - gsPdecHal[ui8PdecCh].stpReg->reg_aub_base;
	ui32AuibRdOffset = gsPdecHal[ui8PdecCh].stpReg->reg_aub_rptr - gsPdecHal[ui8PdecCh].stpReg->reg_aub_base;

	ui32AuibSize = gsPdecHal[ui8PdecCh].stpReg->reg_aub_size << 4; // multiple 16 = PDEC_AUI_SIZE

	if( ui32AuibWrOffset == ui32AuibRdOffset )
	{
		log_error ("[PDEC%d][Err] AUIB Underrun, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	ui32AuibRdOffset_Next = PDEC_AUIB_NEXT_START_OFFSET(ui32AuibRdOffset, ui32AuibSize);

	pui32AuibVirAddr = gsPdecHal[ui8PdecCh].pui32AuibVirBase + (ui32AuibWrOffset >> 2); // divide 4
	_PDEC_UTIL_AUI_Parse(pui32AuibVirAddr, pPdecAui);

	gsPdecHal[ui8PdecCh].stpReg->reg_aub_rptr = gsPdecHal[ui8PdecCh].stpReg->reg_aub_base + ui32AuibRdOffset_Next;
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
void PDEC_HAL_Flush(UINT8 ui8PdecCh)
{
	UINT32		ui32AubWrPtr;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return;
	}

	log_debug ("[PDEC%d][DBG][CPB] %s", ui8PdecCh, __FUNCTION__ );

	ui32AubWrPtr = gsPdecHal[ui8PdecCh].stpReg->reg_aub_wptr;

	gsPdecHal[ui8PdecCh].ui32AuibWrOffset_Prev = ui32AubWrPtr - gsPdecHal[ui8PdecCh].stpReg->reg_aub_base;
	gsPdecHal[ui8PdecCh].stpReg->reg_aub_rptr = ui32AubWrPtr;
	gsPdecHal[ui8PdecCh].stpReg->reg_cpb_rptr = gsPdecHal[ui8PdecCh].stpReg->reg_cpb_wptr;
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
static UINT8 *_PDEC_HAL_CPB_TranslatePhyWrPtr(UINT8 ui8PdecCh, UINT32 ui32WrPhyAddr)
{
	UINT32		ui32WrOffset;
	UINT32		ui32CpbPhyBase;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	if( !gsPdecHal[ui8PdecCh].pui8CpbVirBase )
	{
		log_error ("[PDEC%d][Err] Not Initialised, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	ui32CpbPhyBase =  gsPdecHal[ui8PdecCh].stpReg->reg_cpb_base;
	ui32WrOffset = ui32WrPhyAddr - ui32CpbPhyBase;

	return gsPdecHal[ui8PdecCh].pui8CpbVirBase + ui32WrOffset;
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
UINT32 *PDEC_HAL_GetLatestDecodedAUI(UINT8 ui8PdecCh, S_PDEC_AUI_T *pPdecAui)
{
	UINT32	ui32AuibWrOffset, ui32AuibWrOffset_Prev, ui32AuibWrOffset_Curr;
	UINT32	ui32AuibRdOffset;
	UINT32	*pui32AuibVirAddr;
	UINT32	ui32AuibSize;
	UINT32	ui32UsedBuf;

	if( ui8PdecCh >= PDEC_NUM_OF_CHANNEL )
	{
		log_error ("[PDEC%d][Err] Channel Number, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	if( gsPdecHal[ui8PdecCh].pui32AuibVirBase == 0x0 )
	{
		log_error ("[PDEC%d][Err] Not Initialised, %s", ui8PdecCh, __FUNCTION__ );
		return 0x0;
	}

	ui32AuibSize = gsPdecHal[ui8PdecCh].stpReg->reg_aub_size << 4; // multiple 16 = PDEC_AUI_SIZE

	ui32AuibWrOffset = gsPdecHal[ui8PdecCh].stpReg->reg_aub_wptr - gsPdecHal[ui8PdecCh].stpReg->reg_aub_base;
	ui32AuibRdOffset = gsPdecHal[ui8PdecCh].stpReg->reg_aub_rptr - gsPdecHal[ui8PdecCh].stpReg->reg_aub_base;
	if( ui32AuibWrOffset == ui32AuibRdOffset )
	{
		log_debug ("[PDEC%d][Err] AUIB Overflow or Underrun - Offset: 0x%X, %s(%d)", ui8PdecCh, ui32AuibWrOffset, __FUNCTION__, __LINE__ );
		return 0x0;
	}

	ui32AuibWrOffset = PDEC_AUIB_PREV_START_OFFSET(ui32AuibWrOffset, ui32AuibSize); // writing
	if( ui32AuibWrOffset == ui32AuibRdOffset )
	{
		log_debug ("[PDEC%d][Warning] Writing AUIB - Offset: 0x%X, %s(%d)", ui8PdecCh, ui32AuibWrOffset, __FUNCTION__, __LINE__ );
		return 0x0;
	}

	ui32AuibWrOffset_Prev = gsPdecHal[ui8PdecCh].ui32AuibWrOffset_Prev;

	if( ui32AuibWrOffset >= ui32AuibWrOffset_Prev )
		ui32UsedBuf = ui32AuibWrOffset - ui32AuibWrOffset_Prev;
	else
		ui32UsedBuf = ui32AuibWrOffset + ui32AuibSize - ui32AuibWrOffset_Prev;

	if( ui32UsedBuf == 0 )
	{
		return 0x0;
	}

	pui32AuibVirAddr = gsPdecHal[ui8PdecCh].pui32AuibVirBase + (ui32AuibWrOffset_Prev >> 2); // divide 4
	_PDEC_UTIL_AUI_Parse(pui32AuibVirAddr, pPdecAui);

#ifdef L9_A0_WORKAROUND
{
	UINT32	ui32AuStartAddr, ui32AuStartAddr_HW;
	UINT32	ui32AuEndAddr;
	UINT32	ui32CpbStartData;
	UINT32	ui32CpbSize = gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size;

	ui32AuStartAddr = pui32AuibVirAddr[0] & 0xFFFFFE00;
	ui32AuStartAddr_HW = ui32AuStartAddr;
//	log_debug ("[PDEC%d][Warning] ui32AuStartAddr_HW: 0x%08X", ui8PdecCh, ui32AuStartAddr_HW);

	if( gsPdecHal[ui8PdecCh].bEOS_Found == TRUE )
	{
		if( gsPdecHal[ui8PdecCh].ui32AuStartAddr_HW == ui32AuStartAddr_HW )
		{
			gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset += 0x200;
			while( gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset >= ui32CpbSize )
				gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset -= ui32CpbSize;
		}
		log_debug ("[PDEC%d][Warning] L9-A0 SEQUENCE_END, SeqEndCpbOffset: 0x%08X", ui8PdecCh, gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset);

		gsPdecHal[ui8PdecCh].bEOS_Found = FALSE;
	}

	ui32AuStartAddr += gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset;
	ui32AuEndAddr = gsPdecHal[ui8PdecCh].stpReg->reg_cpb_base + gsPdecHal[ui8PdecCh].stpReg->reg_cpb_size;
	while( ui32AuStartAddr >= ui32AuEndAddr )
		ui32AuStartAddr -= ui32CpbSize;
	pui32AuibVirAddr[0] = ui32AuStartAddr | (pui32AuibVirAddr[0] & 0x1FF);

	pPdecAui->ui32AuStartAddr = ui32AuStartAddr;

	ui32CpbStartData = *(UINT32 *)_PDEC_HAL_CPB_TranslatePhyWrPtr(ui8PdecCh, pPdecAui->ui32AuStartAddr);
	if( (ui32CpbStartData & 0x0000FFFF) == 0x00000100 )
	{
		gsPdecHal[ui8PdecCh].bEOS_Found = TRUE;
		gsPdecHal[ui8PdecCh].ui32AuStartAddr_HW = ui32AuStartAddr_HW;
	}

	if( (ui32CpbStartData & 0x00FFFFFF) != 0x00010000 )
	{
		log_debug ("[PDEC%d][Warning] ui32CpbStartData: 0x%08X, SeqEndCpbOffset: 0x%08X", ui8PdecCh, ui32CpbStartData, gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset);
		if( (ui32CpbStartData & 0x0000FFFF) != 0x00000100 )
		{
			if( (gsPdecHal[ui8PdecCh].ui32AddrMismatchingCnt % 0x40) == 0 )
				log_error ("[PDEC%d][Err] AU Start Address Mismatching, CPB Start Addr:0x%08X Data:0x%08X, SeqEndCpbOffset: %X", ui8PdecCh, pPdecAui->ui32AuStartAddr, ui32CpbStartData, gsPdecHal[ui8PdecCh].ui32SeqEndCpbOffset);

			gsPdecHal[ui8PdecCh].ui32AddrMismatchingCnt++;
//			PDEC_HAL_Disable(ui8PdecCh);
		}
	}
}
#endif // #ifdef L9_A0_WORKAROUND

	ui32AuibWrOffset_Curr = PDEC_AUIB_NEXT_START_OFFSET(ui32AuibWrOffset_Prev, ui32AuibSize);
	gsPdecHal[ui8PdecCh].ui32AuibWrOffset_Prev = ui32AuibWrOffset_Curr;

	return pui32AuibVirAddr;
}

UINT32 PDEC_GET_Stc(UINT8 ui8PdecCh)
{
	return 0;
}

/** @} */

