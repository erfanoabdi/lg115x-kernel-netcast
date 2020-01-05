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
 *  DE IPC HAL.
 *  (Register Access Hardware Abstraction Layer )
 *
 *  author	youngki.lyu@lge.com
 *  version	1.0
 *  date		2011-05-03
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
#include "../../../mcu/os_adap.h"

#include "../de_ipc_hal_api.h"
#include "deipc_reg.h"
#include "../de_vdo_hal_api.h"

#ifndef __XTENSA__
#include <linux/kernel.h>
#endif

#define LOG_NAME	vdec_hal_deipc
#include "log.h"


/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define 		H13_VDEC_DE_IF_BASE(ch)				(H13_VDEC_BASE + 0x0E00 + (ch * 0x40))

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/


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
static volatile DEIPC_REG_T		*stpDE_IPC_Reg[DE_IF_NUM_OF_CHANNEL];
#ifdef SIMPLE_DE
static UINT32 _gu32YBase[DE_IF_NUM_OF_CHANNEL];
static UINT32 _gu32CBase[DE_IF_NUM_OF_CHANNEL];
static UINT32 _gu32Stride[DE_IF_NUM_OF_CHANNEL];
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
void DE_IPC_HAL_Init(void)
{
	UINT8	ui8DeIpcCh;

	for( ui8DeIpcCh = 0; ui8DeIpcCh < DE_IF_NUM_OF_CHANNEL; ui8DeIpcCh++ )
	{
		stpDE_IPC_Reg[ui8DeIpcCh] = (volatile DEIPC_REG_T *)VDEC_TranselateVirualAddr(H13_VDEC_DE_IF_BASE(ui8DeIpcCh), 0x40);
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
inline BOOLEAN DE_IPC_HAL_SetNewFrame(UINT8 ui8DeIpcCh, S_DE_IPC_T *psDeIpc)
{
	const UINT32	ui32DownScaler = 0x10;
	UINT32 			ui16FrameRateRes;
	UINT32 			ui16FrameRateDiv;
	UINT16			ui16Width, ui16Height;
	UINT32			ui32H_Offset, ui32V_Offset;

	log_trace ("%d:%x %07x %07x %x %x %d %x %x %x %x %x %x(%dx%d)%x %x %x %d %x(%d/%d)%x %x %x\n",
			ui8DeIpcCh,
			psDeIpc->ui32Tiled_FrameBaseAddr,
			psDeIpc->ui32Y_FrameBaseAddr,
			psDeIpc->ui32C_FrameBaseAddr,
			psDeIpc->ui32Y_FrameOffset,
			psDeIpc->ui32C_FrameOffset,
			psDeIpc->ui32Stride,
			psDeIpc->ui32FrameIdx&0xFF,
			psDeIpc->ui32ScalerFreeze,
			psDeIpc->ui32DisplayMode,
			psDeIpc->ui32FieldRepeat,
			psDeIpc->ui32VdecPause,
			psDeIpc->ui32AspectRatio,
			psDeIpc->ui16PicWidth,
			psDeIpc->ui16PicHeight,
			psDeIpc->ui32H_Offset,
			psDeIpc->ui32V_Offset,
			psDeIpc->ui32UpdateInfo,
			psDeIpc->ui32FramePackArrange,
			psDeIpc->ui32LR_Order,
			psDeIpc->ui16FrameRateRes,
			psDeIpc->ui16FrameRateDiv,
			psDeIpc->ui16ParW,
			psDeIpc->ui16ParH,
			psDeIpc->ui32PTS);

	if( ui8DeIpcCh >= DE_IF_NUM_OF_CHANNEL )
	{
		log_error ("[DE_IPC][Err] Channel Number(%d)\n", ui8DeIpcCh);
		return FALSE;
	}

	if (psDeIpc->ui32Tiled_FrameBaseAddr != 0)
	{
		// tiled map
		stpDE_IPC_Reg[ui8DeIpcCh]->frame_idx = (psDeIpc->ui32FrameIdx & 0xFF) | 0xc00;
	}
	else
	{
		// raster map
		stpDE_IPC_Reg[ui8DeIpcCh]->frame_idx = (psDeIpc->ui32FrameIdx & 0xFF) | 0x800;
		DE_VDO_HAL_SetInterlaced(ui8DeIpcCh, (psDeIpc->ui32DisplayMode != 3));
	}

	ui16FrameRateRes = psDeIpc->ui16FrameRateRes;
	ui16FrameRateDiv = psDeIpc->ui16FrameRateDiv;
	while( (ui16FrameRateRes > 0xFFFF) || (ui16FrameRateDiv > 0xFFFF) )
	{
		ui16FrameRateRes /= ui32DownScaler;
		ui16FrameRateDiv /= ui32DownScaler;
	}

	ui16Width	= psDeIpc->ui16PicWidth;
	ui16Height	= psDeIpc->ui16PicHeight;
	ui32H_Offset= psDeIpc->ui32H_Offset;
	ui32V_Offset= psDeIpc->ui32V_Offset;

	// Crop (Requested by DE)
	if( ui32H_Offset & 0xFFFF )		// right crop
	{
		ui16Width = psDeIpc->ui16PicWidth - (ui32H_Offset & 0xFFFF);
		ui32H_Offset &= ~0xFFFF;
	}

	if( ui32V_Offset & 0xFFFF )		// bottom crop
	{
		ui16Height = psDeIpc->ui16PicHeight - (ui32V_Offset & 0xFFFF);
		ui32V_Offset &= ~0xFFFF;
	}

	if( psDeIpc->ui16PicHeight > 1080 )		// Max height
		ui16Height = 1080;

	stpDE_IPC_Reg[ui8DeIpcCh]->y_frame_base_address = psDeIpc->ui32Y_FrameBaseAddr;
	stpDE_IPC_Reg[ui8DeIpcCh]->c_frame_base_address = psDeIpc->ui32C_FrameBaseAddr;
	stpDE_IPC_Reg[ui8DeIpcCh]->y_frame_offset = psDeIpc->ui32Y_FrameOffset;
	stpDE_IPC_Reg[ui8DeIpcCh]->c_frame_offset = psDeIpc->ui32C_FrameOffset;
	stpDE_IPC_Reg[ui8DeIpcCh]->stride = psDeIpc->ui32Stride;
	stpDE_IPC_Reg[ui8DeIpcCh]->frame_rate =
		((UINT32)ui16FrameRateDiv << 16) | ((UINT32)ui16FrameRateRes & 0xFFFF);
	stpDE_IPC_Reg[ui8DeIpcCh]->aspect_ratio = psDeIpc->ui32AspectRatio;
	stpDE_IPC_Reg[ui8DeIpcCh]->picture_size = (ui16Width << 16) | ui16Height;
	stpDE_IPC_Reg[ui8DeIpcCh]->h_offset = ui32H_Offset;
	stpDE_IPC_Reg[ui8DeIpcCh]->v_offset = ui32V_Offset;
	stpDE_IPC_Reg[ui8DeIpcCh]->frame_pack_arrange =
		(psDeIpc->ui32FramePackArrange & 0xFF) | ((psDeIpc->ui32LR_Order & 0x3) << 8);
	stpDE_IPC_Reg[ui8DeIpcCh]->pixel_aspect_ratio =
		((UINT32)(psDeIpc->ui16ParW) << 16) | ((UINT32)(psDeIpc->ui16ParH) & 0xFFFF);
	stpDE_IPC_Reg[ui8DeIpcCh]->pts_info = psDeIpc->ui32PTS;

	return TRUE;
}

inline BOOLEAN DE_IPC_HAL_UpdateIpc(UINT8 ui8DeIpcCh, S_DE_IPC_T *psDeIpc)
{
	UINT32			ui32DisplayMode;

	log_trace ("%d:%x %07x %07x %x %x %d %x %x %x %x %x %x(%dx%d)%x %x %x %d %x(%d/%d)%x %x %x\n",
			ui8DeIpcCh,
			psDeIpc->ui32Tiled_FrameBaseAddr,
			psDeIpc->ui32Y_FrameBaseAddr,
			psDeIpc->ui32C_FrameBaseAddr,
			psDeIpc->ui32Y_FrameOffset,
			psDeIpc->ui32C_FrameOffset,
			psDeIpc->ui32Stride,
			psDeIpc->ui32FrameIdx&0xFF,
			psDeIpc->ui32ScalerFreeze,
			psDeIpc->ui32DisplayMode,
			psDeIpc->ui32FieldRepeat,
			psDeIpc->ui32VdecPause,
			psDeIpc->ui32AspectRatio,
			psDeIpc->ui16PicWidth,
			psDeIpc->ui16PicHeight,
			psDeIpc->ui32H_Offset,
			psDeIpc->ui32V_Offset,
			psDeIpc->ui32UpdateInfo,
			psDeIpc->ui32FramePackArrange,
			psDeIpc->ui32LR_Order,
			psDeIpc->ui16FrameRateRes,
			psDeIpc->ui16FrameRateDiv,
			psDeIpc->ui16ParW,
			psDeIpc->ui16ParH,
			psDeIpc->ui32PTS);

	if( ui8DeIpcCh >= DE_IF_NUM_OF_CHANNEL )
	{
		log_error ("[DE_IPC][Err] Channel Number(%d)\n", ui8DeIpcCh);
		return FALSE;
	}

	ui32DisplayMode = stpDE_IPC_Reg[ui8DeIpcCh]->display_info & 0x3;
	if( ui32DisplayMode != DE_IPC_FRAME && ui32DisplayMode == psDeIpc->ui32DisplayMode &&
			psDeIpc->ui32VdecPause == 0 )
	{
		log_noti("deipc:%d, field repeat. frame index %d->%d, display info %d->%d\n",
				ui8DeIpcCh,
				stpDE_IPC_Reg[ui8DeIpcCh]->frame_idx, psDeIpc->ui32FrameIdx,
				stpDE_IPC_Reg[ui8DeIpcCh]->display_info, psDeIpc->ui32DisplayMode);
	}

	switch (psDeIpc->ui32DisplayMode)
	{
	case DE_IPC_TOP_FIELD:
		ui32DisplayMode = 1;
		break;

	case DE_IPC_BOTTOM_FIELD:
		ui32DisplayMode = 2;
		break;

	default:
		log_warning ("deipc:%d, unknown display mode %d\n",
				ui8DeIpcCh, psDeIpc->ui32DisplayMode);
	case DE_IPC_FRAME:
		ui32DisplayMode = 3;
		break;
	}

	stpDE_IPC_Reg[ui8DeIpcCh]->display_info =
		((psDeIpc->ui32VdecPause & 0x1) << 3) |
		((psDeIpc->ui32ColorFormat & 0x3) << 4) |
		ui32DisplayMode;

	stpDE_IPC_Reg[ui8DeIpcCh]->update = psDeIpc->ui32UpdateInfo;

	return TRUE;
}

BOOLEAN DE_IPC_HAL_Update(UINT8 ui8DeIpcCh, S_DE_IPC_T *psDeIpc)
{
	const UINT32	ui32DownScaler = 0x10;
	UINT32			ui32DisplayMode;
	UINT32 			ui16FrameRateRes;
	UINT32 			ui16FrameRateDiv;
	UINT16			ui16Width, ui16Height;
	UINT32			ui32H_Offset, ui32V_Offset;

	log_trace ("%d:%x %07x %07x %x %x %d %x %x %x %x %x %x(%dx%d)%x %x %x %d %x(%d/%d)%x %x %x\n",
			ui8DeIpcCh,
			psDeIpc->ui32Tiled_FrameBaseAddr,
			psDeIpc->ui32Y_FrameBaseAddr,
			psDeIpc->ui32C_FrameBaseAddr,
			psDeIpc->ui32Y_FrameOffset,
			psDeIpc->ui32C_FrameOffset,
			psDeIpc->ui32Stride,
			psDeIpc->ui32FrameIdx&0xFF,
			psDeIpc->ui32ScalerFreeze,
			psDeIpc->ui32DisplayMode,
			psDeIpc->ui32FieldRepeat,
			psDeIpc->ui32VdecPause,
			psDeIpc->ui32AspectRatio,
			psDeIpc->ui16PicWidth,
			psDeIpc->ui16PicHeight,
			psDeIpc->ui32H_Offset,
			psDeIpc->ui32V_Offset,
			psDeIpc->ui32UpdateInfo,
			psDeIpc->ui32FramePackArrange,
			psDeIpc->ui32LR_Order,
			psDeIpc->ui16FrameRateRes,
			psDeIpc->ui16FrameRateDiv,
			psDeIpc->ui16ParW,
			psDeIpc->ui16ParH,
			psDeIpc->ui32PTS);

	if( ui8DeIpcCh >= DE_IF_NUM_OF_CHANNEL )
	{
		log_error ("[DE_IPC][Err] Channel Number(%d)\n", ui8DeIpcCh);
		return FALSE;
	}

	ui32DisplayMode = stpDE_IPC_Reg[ui8DeIpcCh]->display_info & 0x3;
	if(
			(
			 (ui32DisplayMode == 1 && psDeIpc->ui32DisplayMode == DE_IPC_TOP_FIELD) ||
			 (ui32DisplayMode == 2 && psDeIpc->ui32DisplayMode == DE_IPC_BOTTOM_FIELD)
			)
			&& psDeIpc->ui32VdecPause == 0
	  )
	{
		UINT32		ui32DisplayInfo;

		log_warning("deipc:%d, field repeat. frame index %d->%d, display info %d->%d\n",
				ui8DeIpcCh,
				stpDE_IPC_Reg[ui8DeIpcCh]->frame_idx, psDeIpc->ui32FrameIdx,
				stpDE_IPC_Reg[ui8DeIpcCh]->display_info, psDeIpc->ui32DisplayMode);

		ui32DisplayInfo = stpDE_IPC_Reg[ui8DeIpcCh]->display_info;
		ui32DisplayInfo &= ~(0x3);
		if( ui32DisplayMode == 0x1 )
			ui32DisplayInfo |= 0x2;
		else
			ui32DisplayInfo |= 0x1;

		stpDE_IPC_Reg[ui8DeIpcCh]->display_info = ui32DisplayInfo;
		return FALSE;
	}

	switch (psDeIpc->ui32DisplayMode)
	{
	case DE_IPC_TOP_FIELD:
		ui32DisplayMode = 1;
		break;

	case DE_IPC_BOTTOM_FIELD:
		ui32DisplayMode = 2;
		break;

	default:
		log_warning ("deipc:%d, unknown display mode %d\n",
				ui8DeIpcCh, psDeIpc->ui32DisplayMode);
	case DE_IPC_FRAME:
		ui32DisplayMode = 3;
		break;
	}

	stpDE_IPC_Reg[ui8DeIpcCh]->display_info =
		((psDeIpc->ui32VdecPause & 0x1) << 3) |
		((psDeIpc->ui32ColorFormat & 0x3) << 4) |
		ui32DisplayMode;

	if (psDeIpc->ui32Tiled_FrameBaseAddr != 0)
		stpDE_IPC_Reg[ui8DeIpcCh]->frame_idx = (psDeIpc->ui32FrameIdx & 0xFF) | 0xc00;	// tiled map
	else
	{
		stpDE_IPC_Reg[ui8DeIpcCh]->frame_idx = (psDeIpc->ui32FrameIdx & 0xFF) | 0x800;	// raster map
		DE_VDO_HAL_SetInterlaced(ui8DeIpcCh, (ui32DisplayMode != 3));
	}

	ui16FrameRateRes = psDeIpc->ui16FrameRateRes;
	ui16FrameRateDiv = psDeIpc->ui16FrameRateDiv;
	while( (ui16FrameRateRes > 0xFFFF) || (ui16FrameRateDiv > 0xFFFF) )
	{
		ui16FrameRateRes /= ui32DownScaler;
		ui16FrameRateDiv /= ui32DownScaler;
	}

	ui16Width	= psDeIpc->ui16PicWidth;
	ui16Height	= psDeIpc->ui16PicHeight;
	ui32H_Offset= psDeIpc->ui32H_Offset;
	ui32V_Offset= psDeIpc->ui32V_Offset;

	// Crop (Requested by DE)
	if( ui32H_Offset & 0xFFFF )		// right crop
	{
		ui16Width = psDeIpc->ui16PicWidth - (ui32H_Offset & 0xFFFF);
		ui32H_Offset &= ~0xFFFF;
	}

	if( ui32V_Offset & 0xFFFF )		// bottom crop
	{
		ui16Height = psDeIpc->ui16PicHeight - (ui32V_Offset & 0xFFFF);
		ui32V_Offset &= ~0xFFFF;
	}

	if( psDeIpc->ui16PicHeight > 1080 )		// Max height
		ui16Height = 1080;

	stpDE_IPC_Reg[ui8DeIpcCh]->y_frame_base_address = psDeIpc->ui32Y_FrameBaseAddr;
	stpDE_IPC_Reg[ui8DeIpcCh]->c_frame_base_address = psDeIpc->ui32C_FrameBaseAddr;
	stpDE_IPC_Reg[ui8DeIpcCh]->y_frame_offset = psDeIpc->ui32Y_FrameOffset;
	stpDE_IPC_Reg[ui8DeIpcCh]->c_frame_offset = psDeIpc->ui32C_FrameOffset;
	stpDE_IPC_Reg[ui8DeIpcCh]->stride = psDeIpc->ui32Stride;
	stpDE_IPC_Reg[ui8DeIpcCh]->frame_rate =
		((UINT32)ui16FrameRateDiv << 16) | ((UINT32)ui16FrameRateRes & 0xFFFF);
	stpDE_IPC_Reg[ui8DeIpcCh]->aspect_ratio = psDeIpc->ui32AspectRatio;
	stpDE_IPC_Reg[ui8DeIpcCh]->picture_size = (ui16Width << 16) | ui16Height;
	stpDE_IPC_Reg[ui8DeIpcCh]->h_offset = ui32H_Offset;
	stpDE_IPC_Reg[ui8DeIpcCh]->v_offset = ui32V_Offset;
	stpDE_IPC_Reg[ui8DeIpcCh]->update = psDeIpc->ui32UpdateInfo;
	stpDE_IPC_Reg[ui8DeIpcCh]->frame_pack_arrange = (psDeIpc->ui32FramePackArrange & 0xFF) | ((psDeIpc->ui32LR_Order & 0x3) << 8);
	stpDE_IPC_Reg[ui8DeIpcCh]->pixel_aspect_ratio = ((UINT32)(psDeIpc->ui16ParW) << 16) | ((UINT32)(psDeIpc->ui16ParH) & 0xFFFF);
	stpDE_IPC_Reg[ui8DeIpcCh]->pts_info = psDeIpc->ui32PTS;

	return TRUE;
}

/** @} */

