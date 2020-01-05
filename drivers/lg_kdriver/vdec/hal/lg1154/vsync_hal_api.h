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
 * version    0.1
 * date       2011.05.28
 * note       Additional information.
 *
 */

#ifndef _SYNC_HAL_API_h
#define _SYNC_HAL_API_h

#include "../../mcu/vdec_type_defs.h"
#include "lg1154_vdec_base.h"
#include "de_ipc_hal_api.h"


#ifdef __cplusplus
extern "C" {
#endif

#define	VSYNC_NUM_OF_CHANNEL			DE_IPC_NUM_OF_CHANNEL


void VSync_HAL_Init(void);

UINT32 VSync_HAL_GetVersion(void);
void VSync_HAL_Reset(void);
UINT32 VSync_HAL_UTIL_GCD(UINT32 a, UINT32 b);
BOOLEAN VSync_HAL_SetVsyncField(UINT8 ui8VSyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv, BOOLEAN bInterlaced);
void VSync_HAL_RestartAllVsync(void);
UINT32  VSync_HAL_IntField(UINT8 ui8VSyncCh);
UINT32  VSync_HAL_ExtField(UINT8 ui8VSyncCh);

void VSync_HAL_SetVsyncShift(UINT8 ui8SyncCh, UINT32 u32Delta);
void VSync_HAL_SetUpdateMode(UINT8 ui8TimerCh, UINT8 ui8Mode);
void VSync_HAL_ResetTimer(UINT8 ui8TimerCh);
void VSync_HAL_EnableTimer(UINT8 ui8TimerCh);
void VSync_HAL_DisableTimer(UINT8 ui8TimerCh);
void VSync_HAL_SetTimer(UINT8 ui8TimerCh, UINT32 ui32Value);

#ifdef __cplusplus
}
#endif


#endif // endif of _VDEC_HAL_API_h

