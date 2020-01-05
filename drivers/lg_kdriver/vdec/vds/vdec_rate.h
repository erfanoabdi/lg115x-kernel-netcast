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
 * date       2011.03.11
 * note       Additional information.
 *
 */

#ifndef _VDEC_RATE_H_
#define _VDEC_RATE_H_

#include "../mcu/vdec_type_defs.h"

#ifndef __XTENSA__
#include <linux/kernel.h>
#endif



#define	VDEC_SPEED_MAX						16

#define	VDEC_FRAMERATE_MAX					60
#define	VDEC_FRAMERATE_MIN					7

// 29.97Hz
#define	VDEC_DEFAULT_FRAME_RATE_RES			30000
#define	VDEC_DEFAULT_FRAME_RATE_DIV			1001



#ifdef __cplusplus
extern "C" {
#endif



void VDEC_RATE_Init(void);
void VDEC_RATE_Reset(UINT8 ui8LipSyncCh);
void VDEC_RATE_Flush(UINT8 ui8SyncCh);

BOOLEAN VDEC_RATE_Set_Speed(UINT8 ui8SyncCh, SINT32 i32Speed);
SINT32 VDEC_RATE_Get_Speed(UINT8 ui8SyncCh );

void VDEC_RATE_UpdateFrameRate_Config(UINT8 ui8LipSyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv);
void VDEC_RATE_UpdateFrameRate_Decoder(UINT8 ui8LipSyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv, BOOLEAN bFieldPicture, BOOLEAN bInterlaced);
UINT32 VDEC_RATE_UpdateFrameRate_byDTS(UINT8 ui8LipSyncCh, UINT32 ui32DTS, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);
UINT32 VDEC_RATE_UpdateFrameRate_byFeed(UINT8 ui8LipSyncCh, UINT32 ui32GSTC, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);
UINT32 VDEC_RATE_UpdateFrameRate_byDecDone(UINT8 ui8LipSyncCh, UINT32 ui32GSTC, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);
UINT32 VDEC_RATE_UpdateFrameRate_byDqPop(UINT8 ui8LipSyncCh, UINT32 ui32GSTC, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);
UINT32 VDEC_RATE_UpdateFrameRate_byPTS(UINT8 ui8LipSyncCh, UINT32 ui32PTS, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);

UINT32 VDEC_RATE_GetDTSRate(UINT8 ui8LipSyncCh, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);
UINT32 VDEC_RATE_GetPTSRate(UINT8 ui8LipSyncCh, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);

UINT32 VDEC_RATE_GetFrameRateDuration(UINT8 ui8LipSyncCh);
UINT32 VDEC_RATE_GetFrameRateResDiv(UINT8 ui8LipSyncCh, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv);
BOOLEAN VDEC_RATE_IsModifiedFrameRate(UINT8 ui8SyncCh);




#ifdef __cplusplus
}
#endif

#endif /* _VDEC_RATE_H_ */

