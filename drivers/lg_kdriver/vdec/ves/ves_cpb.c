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
 * date       2011.03.09
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
#include "ves_cpb.h"

#include <linux/kernel.h>
#include <asm/uaccess.h> // copy_from_user
#include <asm/cacheflush.h>
#include <linux/version.h>
#include <linux/dma-mapping.h>

#include "../mcu/ipc_callback.h"

#include "../hal/vdec_base.h"
#include "../hal/pdec_hal_api.h"
#include "../hal/top_hal_api.h"
#include "../hal/ipc_reg_api.h"
#include "../mcu/os_adap.h"
#include "../vdc/vdc_drv.h"
#include "ves_drv.h"

#include "log.h"
/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define		VES_NUM_OF_CPB_POOL			VES_NUM_OF_CHANNEL

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define		VES_CPB_ALIGNED_OFFSET( _offset, _cpbsize )	\
					((VES_CPB_CEILING_512BYTES(_offset) >= (_cpbsize)) ? 0 : VES_CPB_CEILING_512BYTES(_offset))
#define		VES_CPB_ALIGNED_ADDR( _addr, _cpbbase, _cpbsize )	\
					((VES_CPB_CEILING_512BYTES(_addr) >= ((_cpbbase) + (_cpbsize))) ? (_cpbbase) : VES_CPB_CEILING_512BYTES(_addr))

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
static void _VES_CPB_SetDb(UINT8 ui8VesCh, UINT32 ui32CpbBufAddr, UINT32 ui32CpbBufSize, BOOLEAN bIsHwPath, BOOLEAN bFromTVP);

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static struct
{
	UINT32 		ui32PhyBaseAddr;	// constant
	UINT8 		*pui8VirBasePtr;		// constant
	UINT32 		ui32BufSize;			// constant
	BOOLEAN		bIsHwPath;
	BOOLEAN		bFromTVP;

	//for Divx3, VP8
	UINT16 		ui16PicWidth;
	UINT16          ui16PicHeight;
	UINT8		ui8CodecType;

	// for Debug
	UINT32 		ui32WrOffset;		// variable
	UINT32 		ui32RdOffset;		// variable

	UINT32		ui32SwPrevRdPtr;
	UINT32		ui32HwPrevRdPtr;

} gsVesCpb[VES_NUM_OF_CHANNEL];



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
void VES_CPB_Init(void)
{
	UINT32	i;

	for( i = 0; i < VES_NUM_OF_CHANNEL; i++ )
	{
		gsVesCpb[i].ui32PhyBaseAddr = 0x0;
		gsVesCpb[i].pui8VirBasePtr = NULL;
		gsVesCpb[i].ui32BufSize = 0x0;
		gsVesCpb[i].bIsHwPath = TRUE;
		gsVesCpb[i].bFromTVP = FALSE;

		gsVesCpb[i].ui32WrOffset = 0x0;
		gsVesCpb[i].ui32RdOffset = 0x0;
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
static BOOLEAN _VES_CPB_CheckBelongToAddress(UINT32 ui32StartAddr, UINT32 ui32EndAddr, UINT32 ui32TargetAddr)
{
	if( ui32StartAddr <= ui32EndAddr )
	{
		if( (ui32TargetAddr > ui32StartAddr) &&
			(ui32TargetAddr <= ui32EndAddr) )
			return TRUE;
	}
	else
	{
		if( (ui32TargetAddr > ui32StartAddr) ||
			(ui32TargetAddr <= ui32EndAddr) )
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
void VES_CPB_UpdateWrPtr(UINT8 ui8VesCh, UINT32 ui32WrPhyAddr)
{
	UINT32		ui32RdOffset;
	UINT32		ui32WrOffset, ui32WrOffset_Next;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return;
	}

	ui32WrOffset_Next = ui32WrPhyAddr - gsVesCpb[ui8VesCh].ui32PhyBaseAddr;

	if( ui32WrOffset_Next > gsVesCpb[ui8VesCh].ui32BufSize )
	{
		logm_error(vdec_ves, "[VES%d][Err][CPB] Invalid Write Addr:0x%X\n", ui8VesCh, ui32WrPhyAddr );
		return;
	}
	if( ui32WrOffset_Next == gsVesCpb[ui8VesCh].ui32BufSize )
	{
		ui32WrOffset_Next = 0;
	}

	ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);
	ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);

	if( _VES_CPB_CheckBelongToAddress(ui32WrOffset, ui32WrOffset_Next, ui32RdOffset) == TRUE )
	{
		logm_error(vdec_ves, "[VES%d][Err][CPB] Overwrite - Write:0x%X, Write_Next:0x%X, Read:0x%X\n", ui8VesCh, ui32WrOffset, ui32WrOffset_Next, ui32RdOffset );
		ui32WrOffset_Next = ui32RdOffset;
		ui32WrPhyAddr = gsVesCpb[ui8VesCh].ui32PhyBaseAddr + ui32WrOffset_Next;
	}

	logm_debug(vdec_ves, "[VES%d][CPB] WritePtr Updated:%x -> %x \n",ui8VesCh,ui32WrOffset,ui32WrOffset_Next);

	IPC_REG_CPB_SetWrOffset(ui8VesCh, ui32WrOffset_Next);

	// for Debug
	gsVesCpb[ui8VesCh].ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);
	gsVesCpb[ui8VesCh].ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);
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
void VES_CPB_UpdateRdPtr(UINT8 ui8VesCh, UINT32 ui32RdPhyAddr)
{
	UINT32		ui32RdOffset, ui32RdOffset_Next;
	UINT32		ui32WrOffset;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return;
	}

	ui32RdOffset_Next = ui32RdPhyAddr - gsVesCpb[ui8VesCh].ui32PhyBaseAddr;

	if( ui32RdOffset_Next > gsVesCpb[ui8VesCh].ui32BufSize )
	{
		logm_error(vdec_ves, "[VES%d][Err][CPB] Invalid Read Addr:0x%X, Base Addr:0x%X\n", ui8VesCh, ui32RdPhyAddr, gsVesCpb[ui8VesCh].ui32PhyBaseAddr );
		return;
	}
	if( ui32RdOffset_Next == gsVesCpb[ui8VesCh].ui32BufSize )
	{
		ui32RdOffset_Next = 0;
	}

	ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);
	ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);

	if( _VES_CPB_CheckBelongToAddress(ui32RdOffset, ui32RdOffset_Next, ui32WrOffset) == TRUE )
	{
		if( ui32RdOffset_Next != ui32WrOffset )
		{
			logm_error(vdec_ves, "[VES%d][Err][CPB] Overread - Read:0x%X, Read_Next:0x%X, Write:0x%X\n", ui8VesCh, ui32RdOffset, ui32RdOffset_Next, ui32WrOffset );
			ui32RdOffset_Next = ui32WrOffset;
			ui32RdPhyAddr = gsVesCpb[ui8VesCh].ui32PhyBaseAddr + ui32RdOffset_Next;
		}
	}

	gsVesCpb[ui8VesCh].ui32SwPrevRdPtr = ui32RdOffset;

	logm_debug(vdec_ves, "[VES%d][CPB] ReadPtr Updated:%x -> %x \n",ui8VesCh,ui32RdOffset,ui32RdOffset_Next);
	
	IPC_REG_CPB_SetRdOffset(ui8VesCh, ui32RdOffset_Next);

	// for Debug
	gsVesCpb[ui8VesCh].ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);
	gsVesCpb[ui8VesCh].ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);

	if( gsVesCpb[ui8VesCh].bIsHwPath == TRUE )
	{
		gsVesCpb[ui8VesCh].ui32HwPrevRdPtr = PDEC_HAL_CPB_GetRdPtr(ui8VesCh);
		PDEC_HAL_CPB_SetRdPtr(ui8VesCh, ui32RdPhyAddr);
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
void VES_CPB_Reset(UINT8 ui8VesCh)
{
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return;
	}

	logm_info(vdec_ves, "[VES%d][DBG] \n", ui8VesCh);

	IPC_REG_CPB_SetWrOffset(ui8VesCh, 0);
	IPC_REG_CPB_SetRdOffset(ui8VesCh, 0);

	// for Debug
	gsVesCpb[ui8VesCh].ui32WrOffset = 0;
	gsVesCpb[ui8VesCh].ui32RdOffset = 0;

	if( gsVesCpb[ui8VesCh].bIsHwPath == TRUE )
	{
		PDEC_HAL_CPB_Init(ui8VesCh, gsVesCpb[ui8VesCh].ui32PhyBaseAddr, gsVesCpb[ui8VesCh].ui32BufSize);
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
void VES_CPB_Flush(UINT8 ui8VesCh)
{
	UINT32		ui32WrOffset;
	UINT32		ui32RdOffset;
	UINT8		*pui8CpbRdVirPtr;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return;
	}

	ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);
	ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);

	logm_info(vdec_ves, "[VES%d][DBG] WrOffset:%d, RdOffset:%d, BufSize:%d\n", ui8VesCh, ui32WrOffset, ui32RdOffset, gsVesCpb[ui8VesCh].ui32BufSize);

	VES_CPB_UpdateRdPtr(ui8VesCh, gsVesCpb[ui8VesCh].ui32PhyBaseAddr + ui32WrOffset);
//	VES_CPB_Reset(ui8VesCh);

	if( gsVesCpb[ui8VesCh].pui8VirBasePtr != NULL )
	{ // for Ring Buffer
		pui8CpbRdVirPtr = gsVesCpb[ui8VesCh].pui8VirBasePtr + ui32RdOffset;
		if( ui32WrOffset >= ui32RdOffset )
		{
			memset(pui8CpbRdVirPtr, 0x0, (ui32WrOffset - ui32RdOffset));
		}
		else
		{
			memset(pui8CpbRdVirPtr, 0x0, (gsVesCpb[ui8VesCh].ui32BufSize - ui32RdOffset));
			if( ui32WrOffset )
			{
				pui8CpbRdVirPtr = gsVesCpb[ui8VesCh].pui8VirBasePtr;
				memset(pui8CpbRdVirPtr, 0x0, ui32WrOffset);
			}
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
static void _VES_CPB_SetDb(UINT8 ui8VesCh, UINT32 ui32CpbBufAddr, UINT32 ui32CpbBufSize, BOOLEAN bIsHwPath, BOOLEAN bFromTVP)
{
	logm_info(vdec_ves, "[VES%d][DBG] CPB Base: 0x%X, Size: 0x%X \n", ui8VesCh, ui32CpbBufAddr, ui32CpbBufSize);

	if( ui32CpbBufAddr && ui32CpbBufSize )
	{
		if( bFromTVP == FALSE )
			gsVesCpb[ui8VesCh].pui8VirBasePtr = (UINT8 *)VDEC_TranselateVirualAddr(ui32CpbBufAddr, ui32CpbBufSize);
		else
			gsVesCpb[ui8VesCh].pui8VirBasePtr = NULL;
	}
	else
	{
		if( bFromTVP == FALSE )
			VDEC_ClearVirualAddr((void *)gsVesCpb[ui8VesCh].pui8VirBasePtr );

		gsVesCpb[ui8VesCh].pui8VirBasePtr = NULL;
	}

	gsVesCpb[ui8VesCh].ui32PhyBaseAddr = ui32CpbBufAddr;
	gsVesCpb[ui8VesCh].ui32BufSize = ui32CpbBufSize;

	gsVesCpb[ui8VesCh].bIsHwPath = bIsHwPath;
	gsVesCpb[ui8VesCh].bFromTVP = bFromTVP;

	gsVesCpb[ui8VesCh].ui32WrOffset = 0;
	gsVesCpb[ui8VesCh].ui32RdOffset = 0;
	IPC_REG_CPB_SetWrOffset(ui8VesCh, 0);
	IPC_REG_CPB_SetRdOffset(ui8VesCh, 0);

	if( (bIsHwPath == TRUE) && (bFromTVP == FALSE) )
		PDEC_HAL_CPB_SetCpbVirBase(ui8VesCh, gsVesCpb[ui8VesCh].pui8VirBasePtr);

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
BOOLEAN VES_CPB_Open(UINT8 ui8VesCh, UINT32 ui32CpbBufAddr, UINT32 ui32CpbBufSize, BOOLEAN bIsHwPath, BOOLEAN bFromTVP)
{

	logm_info(vdec_ves, "[VES%d][DBG] \n", ui8VesCh);

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return FALSE;
	}

	if( ui32CpbBufAddr == 0x0 )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return FALSE;
	}

	logm_noti(vdec_ves, "[VES%d][DBG][CPB] Addr: 0x%X, Size: 0x%X\n", ui8VesCh, ui32CpbBufAddr, ui32CpbBufSize );

	ui32CpbBufAddr = VES_CPB_CEILING_512BYTES( ui32CpbBufAddr );
	ui32CpbBufSize = VES_CPB_BOTTOM_512BYTES( ui32CpbBufSize );

	_VES_CPB_SetDb(ui8VesCh, ui32CpbBufAddr, ui32CpbBufSize, bIsHwPath, bFromTVP);

	if( bIsHwPath == TRUE )
	{
		if( bFromTVP == TRUE )
		{
			PDEC_HAL_Disable(ui8VesCh);
			PDEC_HAL_CPB_Init(ui8VesCh, ui32CpbBufAddr, ui32CpbBufSize);
		}
		else
		{
			PDEC_HAL_CPB_Init(ui8VesCh, ui32CpbBufAddr, ui32CpbBufSize);

			PDEC_HAL_CPB_SetBufALevel(ui8VesCh, 80, 5);

			switch( ui8VesCh )
			{
			case 0 :
				TOP_HAL_EnableBufIntr(PDEC0_CPB_ALMOST_FULL);
				TOP_HAL_EnableBufIntr(PDEC0_CPB_ALMOST_EMPTY);
				break;
			case 1 :
				TOP_HAL_EnableBufIntr(PDEC1_CPB_ALMOST_FULL);
				TOP_HAL_EnableBufIntr(PDEC1_CPB_ALMOST_EMPTY);
				break;
			case 2 :
				TOP_HAL_EnableBufIntr(PDEC2_CPB_ALMOST_FULL);
				TOP_HAL_EnableBufIntr(PDEC2_CPB_ALMOST_EMPTY);
				break;
			default :
				logm_error(vdec_ves, "[VES%d][Err]\n", ui8VesCh);
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
void VES_CPB_Close(UINT8 ui8VesCh)
{
	logm_noti(vdec_ves, "[VES%d]Close \n",ui8VesCh);
	
	if( gsVesCpb[ui8VesCh].bIsHwPath == TRUE )
	{
		PDEC_HAL_CPB_Init(ui8VesCh, 0x0, 0x0);

		switch( ui8VesCh )
		{
		case 0 :
			TOP_HAL_ClearBufIntr(PDEC0_CPB_ALMOST_FULL);
			TOP_HAL_DisableBufIntr(PDEC0_CPB_ALMOST_FULL);
			TOP_HAL_ClearBufIntr(PDEC0_CPB_ALMOST_EMPTY);
			TOP_HAL_DisableBufIntr(PDEC0_CPB_ALMOST_EMPTY);
			break;
		case 1 :
			TOP_HAL_ClearBufIntr(PDEC1_CPB_ALMOST_FULL);
			TOP_HAL_DisableBufIntr(PDEC1_CPB_ALMOST_FULL);
			TOP_HAL_ClearBufIntr(PDEC1_CPB_ALMOST_EMPTY);
			TOP_HAL_DisableBufIntr(PDEC1_CPB_ALMOST_EMPTY);
			break;
		case 2 :
			TOP_HAL_ClearBufIntr(PDEC2_CPB_ALMOST_FULL);
			TOP_HAL_DisableBufIntr(PDEC2_CPB_ALMOST_FULL);
			TOP_HAL_ClearBufIntr(PDEC2_CPB_ALMOST_EMPTY);
			TOP_HAL_DisableBufIntr(PDEC2_CPB_ALMOST_EMPTY);
			break;
		default :
			logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		}
	}

	_VES_CPB_SetDb(ui8VesCh, 0x0, 0x0, FALSE, FALSE);
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
UINT32 VES_CPB_GetPhyWrPtr(UINT8 ui8VesCh)
{
	UINT32		ui32WrPhyAddr;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return 0x0;
	}

	if( !gsVesCpb[ui8VesCh].ui32PhyBaseAddr )
	{
		logm_error(vdec_ves, "[VES%d][Err] Not Initialised\n", ui8VesCh);
		return 0x0;
	}

	ui32WrPhyAddr = gsVesCpb[ui8VesCh].ui32PhyBaseAddr + IPC_REG_CPB_GetWrOffset(ui8VesCh);

	return ui32WrPhyAddr;
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
UINT32 VES_CPB_GetPhyRdPtr(UINT8 ui8VesCh)
{
	UINT32		ui32RdPhyAddr;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return 0x0;
	}

	if( !gsVesCpb[ui8VesCh].ui32PhyBaseAddr )
	{
		logm_error(vdec_ves, "[VES%d][Err] Not Initialised\n", ui8VesCh);
		return 0x0;
	}

	if( gsVesCpb[ui8VesCh].bIsHwPath == TRUE )
		ui32RdPhyAddr = PDEC_HAL_CPB_GetRdPtr(ui8VesCh);
	else
		ui32RdPhyAddr = gsVesCpb[ui8VesCh].ui32PhyBaseAddr + IPC_REG_CPB_GetRdOffset(ui8VesCh);

	return ui32RdPhyAddr;
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
UINT8 *VES_CPB_TranslatePhyWrPtr(UINT8 ui8VesCh, UINT32 ui32WrPhyAddr)
{
	UINT32		ui32WrOffset;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return 0x0;
	}

	if( gsVesCpb[ui8VesCh].pui8VirBasePtr == NULL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Not Initialised\n", ui8VesCh);
		return 0x0;
	}

	ui32WrOffset = ui32WrPhyAddr - gsVesCpb[ui8VesCh].ui32PhyBaseAddr;

	return gsVesCpb[ui8VesCh].pui8VirBasePtr + ui32WrOffset;
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
static BOOLEAN _VES_CPB_CheckOverflow(UINT8 ui8VesCh, UINT32 ui32AuSize_Modified, BOOLEAN bRingBufferMode, UINT32 *pui32WrOffset_AuStart, UINT32 *pui32WrOffset_AlignedEnd, UINT32 ui32RdOffset)
{
	UINT32 ui32WrOffset_Org = *pui32WrOffset_AuStart ;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return TRUE;
	}

	if( (*pui32WrOffset_AuStart + ui32AuSize_Modified) >= gsVesCpb[ui8VesCh].ui32BufSize )
	{
		if( bRingBufferMode == TRUE )
		{
			*pui32WrOffset_AlignedEnd = (*pui32WrOffset_AuStart + ui32AuSize_Modified) - gsVesCpb[ui8VesCh].ui32BufSize;
		}
		else
		{
			if( (*pui32WrOffset_AuStart + ui32AuSize_Modified) >= gsVesCpb[ui8VesCh].ui32BufSize )
			{
				*pui32WrOffset_AuStart = 0;
			}
			*pui32WrOffset_AlignedEnd = *pui32WrOffset_AuStart + ui32AuSize_Modified;
		}
	}
	else
	{
		*pui32WrOffset_AlignedEnd = *pui32WrOffset_AuStart + ui32AuSize_Modified;
	}

	if( _VES_CPB_CheckBelongToAddress(ui32WrOffset_Org, *pui32WrOffset_AlignedEnd, ui32RdOffset) == TRUE )
	{
		logm_error(vdec_ves, "[VES%d][Err][CPB] Overflow - Write:0x%X, Size:0x%X, Read:0x%X\n", ui8VesCh, ui32WrOffset_Org, ui32AuSize_Modified, ui32RdOffset );
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
UINT32 VES_CPB_Write(	UINT8 ui8VesCh,
							UINT32 eAuType,
							UINT32 ui32AuStartAddr,
							UINT32 ui32AuSize,
							fpCpbCopyfunc fpCopyfunc,
							BOOLEAN bRingBufferMode,
							BOOLEAN b512bytesAligned,
							UINT32 *pui32AuSizeModified,
							UINT32 *pui32CpbWrPhyAddr_End)
{
/*
	ui32WrOffset,
				ui32WrOffset_AuStart + ui32AuSize = ui32WrOffset_AuEnd,
																ui32WrOffset_AlignedEnd
*/

	UINT32		ui32WrOffset, ui32WrOffset_AuStart, ui32WrOffset_AuEnd, ui32WrOffset_AlignedEnd;
	UINT32		ui32RdOffset;
	UINT32		ui32CpbWrPhyAddr = 0x0;
	UINT8		*pui8CpbWrVirPtr;
	char			*pui8AuStartAddr = (char*)ui32AuStartAddr;
	UINT32		ui32AuSize_Modified;

	if( b512bytesAligned == TRUE )
		ui32AuSize_Modified = (VES_CPB_CEILING_512BYTES(ui32AuSize) + 1024);
	else
		ui32AuSize_Modified = ui32AuSize;

	ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);
	ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);
	ui32WrOffset_AuStart = ui32WrOffset;

	// 1. Check CPB Overflow
	if( _VES_CPB_CheckOverflow(ui8VesCh, ui32AuSize_Modified, bRingBufferMode, &ui32WrOffset_AuStart, &ui32WrOffset_AlignedEnd, ui32RdOffset) == TRUE )
		return 0x0;

	// pad buffer end
	if( ui32WrOffset > ui32WrOffset_AuStart )
	{
		UINT32		ui32PadSize;

		logm_debug(vdec_ves, "[VES%d][DBG] Pad CPB End, WrOffset:0x%08X/0x%08X/0x%08X, RdOffset:0x%08X\n", ui8VesCh, ui32WrOffset, ui32WrOffset_AuStart, ui32WrOffset_AlignedEnd, ui32RdOffset);

		if( ui32WrOffset_AuStart != 0 )
		{
			logm_error(vdec_ves, "[VES%d][Err] WrOffset:0x%08X/0x%08X/0x%08X, RdOffset:0x%08X\n", ui8VesCh, ui32WrOffset, ui32WrOffset_AuStart, ui32WrOffset_AlignedEnd, ui32RdOffset);
			return 0x0;
		}

		pui8CpbWrVirPtr = gsVesCpb[ui8VesCh].pui8VirBasePtr + ui32WrOffset;
		ui32PadSize = gsVesCpb[ui8VesCh].ui32BufSize - ui32WrOffset;

		memset(pui8CpbWrVirPtr, 0x0, ui32PadSize);
	}

	ui32CpbWrPhyAddr = gsVesCpb[ui8VesCh].ui32PhyBaseAddr + ui32WrOffset_AuStart;
	pui8CpbWrVirPtr = gsVesCpb[ui8VesCh].pui8VirBasePtr + ui32WrOffset_AuStart;

	// 2. Write User Data to CPB
	if( (ui32WrOffset_AuStart + ui32AuSize) > gsVesCpb[ui8VesCh].ui32BufSize )
	{ // Wrap Around
		UINT32		ui32AuSize_Front;
		UINT32		ui32AuSize_Back;

		logm_debug(vdec_ves, "[VES%d][DBG] Cpb Wrap Around, WrOffset:0x%08X/0x%08X/0x%08X, RdOffset:0x%08X\n", ui8VesCh, ui32WrOffset, ui32WrOffset_AuStart, ui32WrOffset_AlignedEnd, ui32RdOffset);

		ui32AuSize_Front = gsVesCpb[ui8VesCh].ui32BufSize - ui32WrOffset_AuStart;

		fpCopyfunc(pui8CpbWrVirPtr, pui8AuStartAddr, ui32AuSize_Front);

//		logm_error(vdec_ves, "[VES%d] Addr:0x%X, Size:0x%X, Data:0x%08X\n", ui8VesCh, ui32CpbWrPhyAddr, ui32AuSize, *(UINT32 *)pui8CpbWrVirPtr );

		pui8CpbWrVirPtr = gsVesCpb[ui8VesCh].pui8VirBasePtr;
		pui8AuStartAddr += ui32AuSize_Front;

		ui32AuSize_Back = (ui32WrOffset_AuStart + ui32AuSize) - gsVesCpb[ui8VesCh].ui32BufSize;

		fpCopyfunc(pui8CpbWrVirPtr, pui8AuStartAddr, ui32AuSize_Back);

		pui8CpbWrVirPtr = gsVesCpb[ui8VesCh].pui8VirBasePtr + ui32AuSize_Back;
		ui32WrOffset_AuEnd = ui32AuSize_Back;
	}
	else
	{

		fpCopyfunc(pui8CpbWrVirPtr, pui8AuStartAddr, ui32AuSize);

//		logm_error(vdec_ves, "[VES%d] Addr:0x%X, Size:0x%X, Data:0x%08X\n", ui8VesCh, ui32CpbWrPhyAddr, ui32AuSize, *(UINT32 *)pui8CpbWrVirPtr );

		pui8CpbWrVirPtr += ui32AuSize;
		ui32WrOffset_AuEnd = ui32WrOffset_AuStart + ui32AuSize;
	}

	// pad au end
	if( ui32WrOffset_AuEnd > ui32WrOffset_AlignedEnd )
	{
		memset(pui8CpbWrVirPtr, 0x0, gsVesCpb[ui8VesCh].ui32BufSize - ui32WrOffset_AuEnd);

		if( ui32WrOffset_AlignedEnd > 0 )
		{
			pui8CpbWrVirPtr = gsVesCpb[ui8VesCh].pui8VirBasePtr;
			memset(pui8CpbWrVirPtr, 0x0, ui32WrOffset_AlignedEnd);
		}
	}
	else if( ui32WrOffset_AuEnd < ui32WrOffset_AlignedEnd )
	{
		memset(pui8CpbWrVirPtr, 0x0, ui32WrOffset_AlignedEnd - ui32WrOffset_AuEnd);
	}

	*pui32CpbWrPhyAddr_End = gsVesCpb[ui8VesCh].ui32PhyBaseAddr + ui32WrOffset_AlignedEnd;
	*pui32AuSizeModified = ui32AuSize_Modified;

	return ui32CpbWrPhyAddr;
}

BOOLEAN VES_CPB_Read(UINT8 ui8VesCh, UINT32 ui32Start, UINT32 ui32Size, UINT8 *pui8Buf)
{
	UINT32	ui32RdOffset;
	UINT8*	pui8RdVirAddr;
	UINT32	ui32Size_Front, ui32Size_Back;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err]  \n\n", ui8VesCh);
		return FALSE;
	}

	if( gsVesCpb[ui8VesCh].bFromTVP == TRUE )
	{
		// CANNOT ACCESS TO VIRTUAL MEMORY WHEN TVP PATH
		return FALSE;
	}
	else 
	{

		// calculate offset	
		ui32RdOffset = ui32Start - gsVesCpb[ui8VesCh].ui32PhyBaseAddr;

		if( ui32RdOffset == gsVesCpb[ui8VesCh].ui32BufSize )
		{
			ui32RdOffset = 0;
		}
		logm_info(vdec_ves,"[VES%d] rd offset:%x \n\n",ui8VesCh,ui32RdOffset);

		// calculate vir addr	
		pui8RdVirAddr = gsVesCpb[ui8VesCh].pui8VirBasePtr + ui32RdOffset;
		logm_info(vdec_ves,"[VES%d] vir rd:0x%08x \n\n",ui8VesCh,pui8RdVirAddr);

		// addr + size가 buffer를 초과하면
		if( ui32RdOffset + ui32Size > gsVesCpb[ui8VesCh].ui32BufSize) {
			ui32Size_Front = gsVesCpb[ui8VesCh].ui32BufSize - ui32RdOffset;
			ui32Size_Back = ui32Size - ui32Size_Front;

			logm_info(vdec_ves,"[VES%d] wrap arounded: Front:%d, Back:%d \n\n",ui8VesCh,ui32Size_Front,ui32Size_Back);
			
			memcpy(pui8Buf, pui8RdVirAddr, ui32Size_Front);
			memcpy(pui8Buf+ui32Size_Front, gsVesCpb[ui8VesCh].pui8VirBasePtr, ui32Size_Back);
		}
		else memcpy(pui8Buf, pui8RdVirAddr, ui32Size);

		return TRUE;
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
UINT32 VES_CPB_GetUsedBuffer(UINT8 ui8VesCh)
{
	UINT32		ui32UseBytes;
	UINT32		ui32WrOffset;
	UINT32		ui32RdOffset;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return 0;
	}

	ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);
	ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);

	if( ui32WrOffset >= ui32RdOffset )
		ui32UseBytes = ui32WrOffset - ui32RdOffset;
	else
		ui32UseBytes = ui32WrOffset + gsVesCpb[ui8VesCh].ui32BufSize - ui32RdOffset;
/*
	if( gsVesCpb[ui8VesCh].bIsHwPath == TRUE )
		logm_debug(vdec_ves, "[VES%d][DBG][CPB] Used Size SW:0x%X, HW:0x%X\n", ui8VesCh, ui32UseBytes, PDEC_HAL_CPB_GetBufferLevel(ui8VesCh) );
	else
		logm_debug(vdec_ves, "[VES%d][DBG][CPB] Used Size SW:0x%X\n", ui8VesCh, ui32UseBytes );*/

	return ui32UseBytes;
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
UINT32 VES_CPB_GetBufferBaseAddr(UINT8 ui8VesCh)
{
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return 0;
	}

//	logm_debug(vdec_ves, "[VES%d][DBG] buf base addr : 0x%X \n", ui8VesCh, gsVesCpb[ui8VesCh].ui32PhyBaseAddr);

	return gsVesCpb[ui8VesCh].ui32PhyBaseAddr;
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
UINT32 VES_CPB_GetBufferSize(UINT8 ui8VesCh)
{
	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return 0;
	}

//	logm_debug(vdec_ves, "[VES%d][DBG] buf size : 0x%X \n", ui8VesCh, gsVesCpb[ui8VesCh].ui32BufSize);

	return gsVesCpb[ui8VesCh].ui32BufSize;
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
void VES_CPB_PrintUsedBuffer(UINT8 ui8VesCh)
{
	UINT32		ui32UseBytes;
	UINT32		ui32WrOffset;
	UINT32		ui32RdOffset;

	if( ui8VesCh >= VES_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
		return;
	}

	ui32WrOffset = IPC_REG_CPB_GetWrOffset(ui8VesCh);
	ui32RdOffset = IPC_REG_CPB_GetRdOffset(ui8VesCh);

	if( ui32WrOffset >= ui32RdOffset )
		ui32UseBytes = ui32WrOffset - ui32RdOffset;
	else
		ui32UseBytes = ui32WrOffset + gsVesCpb[ui8VesCh].ui32BufSize - ui32RdOffset;

	logm_debug(vdec_ves, "[VES%d][DBG][CPB] Use: 0x%08X, Free: 0x%08X \n", ui8VesCh, ui32UseBytes, gsVesCpb[ui8VesCh].ui32BufSize - ui32UseBytes );
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
void VDEC_ISR_CPB_AlmostFull(UINT8 ui8VesCh)
{
	S_IPC_CALLBACK_BODY_CPBSTATUS_T sReportCpbStatus;

	if( ui8VesCh >= PDEC_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);
		return;
	}

	switch( ui8VesCh)
	{
	case 0 :
		TOP_HAL_ClearBufIntr(PDEC0_CPB_ALMOST_FULL);
		break;
	case 1 :
		TOP_HAL_ClearBufIntr(PDEC1_CPB_ALMOST_FULL);
		break;
	case 2 :
		TOP_HAL_ClearBufIntr(PDEC2_CPB_ALMOST_FULL);
		break;
	default :
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh );
	}

	sReportCpbStatus.priv = VES_GetVdecPriv(ui8VesCh);
	sReportCpbStatus.eBufStatus = CPB_STATUS_ALMOST_FULL;
	IPC_CALLBACK_Report_CpbStatus( &sReportCpbStatus );

	logm_error(vdec_ves, "[VES%d][Err][CPB] Almost Full - Buffer Level: %d \n", ui8VesCh, PDEC_HAL_CPB_GetBufferLevel(ui8VesCh) );
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
void VDEC_ISR_CPB_AlmostEmpty(UINT8 ui8VesCh)
{
	if( ui8VesCh >= PDEC_NUM_OF_CHANNEL )
	{
		logm_error(vdec_ves, "[VES%d][Err] Channel Number\n", ui8VesCh);
		return;
	}

	switch( ui8VesCh )
	{
	case 0 :
		TOP_HAL_ClearBufIntr(PDEC0_CPB_ALMOST_EMPTY);
		break;
	case 1 :
		TOP_HAL_ClearBufIntr(PDEC1_CPB_ALMOST_EMPTY);
		break;
	case 2 :
		TOP_HAL_ClearBufIntr(PDEC2_CPB_ALMOST_EMPTY);
		break;
	default :
		logm_error(vdec_ves, "[VES%d][Err] \n", ui8VesCh);
	}

	logm_debug(vdec_ves, "[VES%d][DBG][CPB] Almost Empty - Buffer Level: %d \n", ui8VesCh, PDEC_HAL_CPB_GetBufferLevel(ui8VesCh) );
	logm_debug(vdec_ves, "[VES%d][DBG] Buffer Status: 0x%X \n", ui8VesCh, PDEC_HAL_GetBufferStatus(ui8VesCh) );
}

