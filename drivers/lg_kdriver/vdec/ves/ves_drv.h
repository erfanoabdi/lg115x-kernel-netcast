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
 * version    0.1
 * date       2011.05.04
 * note       Additional information.
 *
 */

#ifndef _VES_DRV_H_
#define _VES_DRV_H_


#include "../mcu/vdec_type_defs.h"
#include "ves_cpb.h"
#include "../hal/pdec_hal_api.h"



#ifdef __cplusplus
extern "C" {
#endif



#define	VES_NUM_OF_CHANNEL			3



typedef enum
{
	VES_SRC_SDEC0		= 0x00,
	VES_SRC_SDEC1		= 0x01,
	VES_SRC_SDEC2		= 0x02,
	VES_SRC_TVP			= 0x12,
	VES_SRC_BUFF0		= 0x20,
	VES_SRC_BUFF1		= 0x21,
	VES_SRC_32bits		= 0x20120316,
} E_VES_SRC_T;


typedef	E_PDEC_AU_T		E_VES_AU_T;
typedef void (*VES_BUFFER_UPDATED_T) (UINT8 ch, void *arg, int stc_invalid, unsigned int uid);



void VES_Init(void);
UINT8 VES_Open(E_VES_SRC_T ui8VesSrcCh,
		UINT8 ui8Vcodec,
		UINT32 ui32CpbBufAddr, UINT32 ui32CpbBufSize,
		BOOLEAN bUseGstc, UINT32 ui32DecodeOffset,
		VES_BUFFER_UPDATED_T updated, void *updated_arg);
BOOLEAN VES_SetOpenParam(UINT8 ui8PdecCh, UINT8 ui8LipSyncCh, void *priv, BOOLEAN bRingBufferMode, BOOLEAN b512bytesAligned);
void *VES_GetVdecPriv(UINT8 ui8PdecCh);
void VES_Close(UINT8 ui8PdecCh);
void VES_Reset(UINT8 ui8PesDecCh);
void VES_Start(UINT8 ui8PdecCh);
void VES_Stop(UINT8 ui8PdecCh);
void VES_Flush(UINT8 ui8PdecCh);

BOOLEAN VES_ES_UpdateBuffer(UINT8 ui8PdecCh,
									UINT32 ui32au_type,
									UINT32 ui32UserBuf,
									UINT32 ui32UserBufSize,
									fpCpbCopyfunc fpCopyfunc,
									UINT32 ui32UId,
									UINT64 ui64TimeStamp,	// ns
									UINT32 ui32TimeStamp_90kHzTick,
									UINT32 ui32FrameRateRes,
									UINT32 ui32FrameRateDiv);

void VDEC_ISR_PIC_Detected(UINT8 ui8PdecCh);


#ifdef __cplusplus
}
#endif

#endif /* _VES_DRV_H_ */

