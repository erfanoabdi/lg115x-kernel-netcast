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
 * date       2011.10.04
 * note       Additional information.
 *
 */

#ifndef __VDEC_MCU_TIMER_H__
#define __VDEC_MCU_TIMER_H__

#include "..\vdec_type_defs.h"


typedef void (*VDEC_MCU_TIMER_CALLBACK_T)(void);


void VDEC_MCU_SetTimer(UINT32 ui32Expires_ms, VDEC_MCU_TIMER_CALLBACK_T fpTimerFunc);
void VDEC_MCU_KillTimer(void);


#endif //__VDEC_MCU_TIMER_H__
