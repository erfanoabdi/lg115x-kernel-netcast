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
 * date       2011.05.03
 * note       Additional information.
 *
 */

#ifndef _VDEC_DE_IF_H_
#define _VDEC_DE_IF_H_


#include "../mcu/vdec_type_defs.h"
#include "disp_q.h"
#include "pts_drv.h"



#ifdef __cplusplus
extern "C" {
#endif




typedef enum
{
	DE_IF_DST_DE_IF0		= 0x0,
	DE_IF_DST_DE_IF1		= 0x1,
	DE_IF_DST_MAX				,
	DE_IF_DST_32bits		= 0x20120321,
} E_DE_IF_DST_T;



void DE_IF_Init(void);
BOOLEAN DE_IF_Open(E_DE_IF_DST_T eDeIfDstCh);
void DE_IF_SelVsync(E_DE_IF_DST_T eDeIfDstCh, UINT32 ui32VSyncSrc);
void DE_IF_Close(E_DE_IF_DST_T eDeIfDstCh);
void DE_IF_Freeze(E_DE_IF_DST_T eDeIfDstCh, BOOLEAN bOnOff);
UINT32 DE_IF_GetRunningFrameIndex(E_DE_IF_DST_T eDeIfDstCh);
#if (defined(USE_MCU_FOR_VDEC_VDS) && defined(__XTENSA__)) || \
	(!defined(USE_MCU_FOR_VDEC_VDS) && !defined(__XTENSA__))
void DE_IF_RunVdo(UINT8 u8FieldInfo);
BOOLEAN DE_IF_IsNeedNewFrame(E_DE_IF_DST_T eDeIfDstCh);
BOOLEAN DE_IF_SetNewFrame(E_DE_IF_DST_T eDeIfDstCh, S_DISPQ_BUF_T *psDisBuf, UINT32 ui32SyncField);
BOOLEAN DE_IF_UpdateDisplay(E_DE_IF_DST_T eDeIfDstCh, UINT32 ui32SyncField);
BOOLEAN DE_IF_SetDualOutput(BOOLEAN bOn);
void DE_IF_RepeatFrame(E_DE_IF_DST_T eDeIfDstCh, UINT8 u8nTimes);
#endif



#ifdef __cplusplus
}
#endif

#endif /* _VDEC_DE_IF_H_ */

