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
 * DE IPC HAL.
 * (Register Access Hardware Abstraction Layer)
 *
 * author     youngki.lyu (youngki.lyu@lge.com)
 * version    0.1
 * date       2011.05.03
 * note       Additional information.
 *
 */

#ifndef _VDEC_DE_IF_HAL_API_H_
#define _VDEC_DE_IF_HAL_API_H_

#include "../../mcu/vdec_type_defs.h"



#ifdef __cplusplus
extern "C" {
#endif



#define	DE_IPC_NUM_OF_CHANNEL		2



typedef struct
{
	UINT32 ui32Tiled_FrameBaseAddr;
	UINT32 ui32Y_FrameBaseAddr;
	UINT32 ui32C_FrameBaseAddr;
	UINT32 ui32Y_FrameOffset;
	UINT32 ui32C_FrameOffset;
	UINT32 ui32Stride;
	UINT32 ui32ColorFormat;

	UINT32 ui32FrameIdx;
	UINT32 ui32ScalerFreeze;
	enum
	{
		DE_IPC_TOP_FIELD	= 1,
		DE_IPC_BOTTOM_FIELD	= 2,
		DE_IPC_FRAME		= 3,
	} ui32DisplayMode;
	UINT32 ui32FieldRepeat;
	UINT32 ui32VdecPause;
	UINT32 ui32AspectRatio;
	UINT32 ui16PicWidth;
	UINT32 ui16PicHeight;
	UINT32 ui32H_Offset;
	UINT32 ui32V_Offset;
	UINT32 ui32UpdateInfo;
	UINT32 ui32FramePackArrange;
	UINT32 ui32LR_Order;

	UINT32 ui16FrameRateRes;
	UINT32 ui16FrameRateDiv;
	UINT32 ui16ParW;
	UINT32 ui16ParH;

	UINT32 ui32PTS;
	UINT32 ui32DpbMapType;
}S_DE_IPC_T;



void DE_IPC_HAL_Init(void);
BOOLEAN DE_IPC_HAL_Update(UINT8 ui8DeIpcCh, S_DE_IPC_T *psDeIpc);
BOOLEAN DE_IPC_HAL_SetNewFrame(UINT8 ui8DeIpcCh, S_DE_IPC_T *psDeIpc);
BOOLEAN DE_IPC_HAL_UpdateIpc(UINT8 ui8DeIpcCh, S_DE_IPC_T *psDeIpc);

#ifdef __cplusplus
}
#endif

#endif /* _VDEC_DE_IF_HAL_API_H_ */

