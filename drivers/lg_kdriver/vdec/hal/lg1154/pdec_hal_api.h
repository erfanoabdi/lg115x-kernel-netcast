
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
 */

#ifndef _PDEC_HAL_H_
#define _PDEC_HAL_H_


#include "../../mcu/vdec_type_defs.h"

#ifdef __cplusplus
extern "C" {
#endif


#define 		PDEC_AUI_SIZE						0x10


#define		PDEC_AUIB_CEILING_16BYTES( _addr )			(((_addr) + 0xF) & (~0xF))
#define		PDEC_AUIB_BOTTOM_16BYTES( _addr )			(((_addr) + 0x0) & (~0xF))

#define		PDEC_AUIB_NEXT_START_OFFSET( _offset, _auibsize )	\
				((((_offset) + PDEC_AUI_SIZE) >= (_auibsize)) ? 0 : (_offset) + PDEC_AUI_SIZE)
#define		PDEC_AUIB_NEXT_START_ADDR( _addr, _base, _auibsize )	\
				((((_addr) + PDEC_AUI_SIZE) >= ((_base) + (_auibsize))) ? (_base) : (_addr) + PDEC_AUI_SIZE)
#define		PDEC_AUIB_PREV_START_OFFSET( _offset, _auibsize )	\
				(((_offset) == 0) ? (_auibsize) -PDEC_AUI_SIZE  : (_offset) - PDEC_AUI_SIZE)
#define		PDEC_AUIB_PREV_START_ADDR( _addr, _base, _auibsize )	\
				(((_addr) == (_base)) ? (_base) + (_auibsize) -PDEC_AUI_SIZE  : (_addr) - PDEC_AUI_SIZE)


// AU Type
typedef enum
{
	AU_SEQUENCE_HEADER		= 0x1,
	AU_SEQUENCE_END			= 0x2,
	AU_PICTURE_I			= 0x3,
	AU_PICTURE_P			= 0x4,
	AU_PICTURE_B_NOSKIP		= 0x5,
	AU_PICTURE_B_SKIP		= 0x6,
	AU_ANYTYPE				= 0x7,
	AU_SKIP					= 0x8,
	AU_CMD_FLUSH			= 0x9,
	AU_CMD_SCANI			= 0x10,
	AU_CMD_SCANALL			= 0x11,
	AU_32bits				= 0x20120317,
} E_PDEC_AU_T;



typedef struct{
	// PDEC AU Indexing Information
	/*	AU_INFO_1
		cmd bit field
		Access Unit Type		: 4,	//	 0: 3
								: 1,	//	 4
		gop header				: 1,	//	 5
		not valid vbv dealy		: 1,	//	 6
		stcc discont flag		: 1,	//	 7
		CHB Valid				: 1,	//	 8
		Start Address of Access Unit	:23;	//	 9:31
	*/
	E_PDEC_AU_T		eAuType;
	BOOLEAN			bGopHeader;
	BOOLEAN			bStccDiscontinuity;
	BOOLEAN			bIPicDetect;
	UINT32			ui32AuStartAddr;		// 512bytes aligned size

	/*	AU_INFO_2
		DTS						:28,	//	 0:27
		DTS Error				: 1,	//	28
		isNotFirstPictureinPESPacket	: 1,	//	29
		Access DTSType			: 2,	//	30:31
	*/
	UINT32			ui32DTS;			// real size

	/*	AU_INFO_3
		PTS 						:28,	//	 0:27
		PTS Error					: 1,	//	28
		Sequence Error Code			: 1,	//	29
		Scrambled ES				: 1,	//	30
		Packet Error				: 1,	//	31
	*/
	UINT32			ui32PTS;

	/*	AU_INFO_4
	*/

	UINT32			STC_PTS_flag;
}S_PDEC_AUI_T;

typedef enum {
	PDEC_SKIP_NON_FRAME = 0,
	PDEC_SKIP_B_FRAME,
	PDEC_SKIP_BP_FRAME,
	PDEC_SKIP_FRAME_MAX = 0x12345678
} S_PDEC_SKIP_FRAME_T;



void PDEC_HAL_Init(void);
void PDEC_HAL_Reset(UINT8 ui8PdecCh);
void PDEC_HAL_Enable(UINT8 ui8PdecCh);
void PDEC_HAL_Disable(UINT8 ui8PdecCh);
void PDEC_HAL_SetVideoStandard(UINT8 ui8PdecCh, UINT8 ui8Vcodec);
void PDEC_HAL_Pause(UINT8 ui8PdecCh);
void PDEC_HAL_Resume(UINT8 ui8PdecCh);
void PDEC_HAL_SetBypass(UINT8 ui8PdecCh);
void PDEC_HAL_UnsetBypass(UINT8 ui8PdecCh);
void PDEC_HAL_SkipPicFrame(UINT8 ui8PdecCh, S_PDEC_SKIP_FRAME_T eSkipFrame);
void PDEC_HAL_Ignore_Stall(UINT8 ui8PdecCh);
void PDEC_HAL_SetReadyCtrlMode(UINT8 ui8PdecCh, BOOLEAN bBufferFull);

void PDEC_HAL_CPB_Init(UINT8 ui8PdecCh, UINT32 ui32CpbBase, UINT32 ui32CpbSize);
void PDEC_HAL_CPB_SetCpbVirBase(UINT8 ui8PdecCh, UINT8 *pui8CpbVirBase);
UINT32 PDEC_HAL_GetCPBBase(UINT8 ui8PdecCh);
UINT32 PDEC_HAL_GetCPBSize(UINT8 ui8PdecCh);
UINT32 PDEC_HAL_CPB_GetWrPtr(UINT8 ui8PdecCh);
void PDEC_HAL_CPB_SetWrPtr(UINT8 ui8PdecCh, UINT32 ui32CpbRdPtr);
UINT32 PDEC_HAL_CPB_GetRdPtr(UINT8 ui8PdecCh);
void PDEC_HAL_CPB_SetRdPtr(UINT8 ui8PdecCh, UINT32 ui32CpbRdPtr);
void PDEC_HAL_CPB_SetBufALevel(UINT8 ui8PdecCh, UINT32 ui32AFullPercent, UINT32 ui32AEmptyPercent);
void PDEC_HAL_CPB_GetBufALevel(UINT8 ui8PdecCh, UINT32 *pui32AFullPercent, UINT32 *pui32AEmptyPercent);

UINT32 PDEC_HAL_CPB_GetBufferLevel(UINT8 ui8PdecCh);
UINT32 PDEC_HAL_GetBufferStatus(UINT8 ui8PdecCh);
UINT32 PDEC_HAL_AUIB_GetStatus(UINT8 ui8PdecCh);

void PDEC_HAL_AUIB_SetBufALevel(UINT8 ui8PdecCh, UINT32 ui32AFullPercent, UINT32 ui32AEmptyPercent);
void PDEC_HAL_AUIB_GetBufALevel(UINT8 ui8PdecCh, UINT32 *pui32AFullPercent, UINT32 *pui32AEmptyPercent);
void PDEC_HAL_AUIB_Init(UINT8 ui8PdecCh, UINT32 ui32AuibBase, UINT32 ui32AuibSize);
void PDEC_HAL_AUIB_SetAuibVirBase(UINT8 ui8PdecCh, UINT32 *pui32AuibVirBase);
UINT32 PDEC_HAL_AUIB_GetWrPtr(UINT8 ui8PdecCh, BOOLEAN bIsHwReg);
void PDEC_HAL_AUIB_SetWrPtr(UINT8 ui8PdecCh, UINT32 ui32CpbRdPtr);
UINT32 PDEC_HAL_AUIB_GetRdPtr(UINT8 ui8PdecCh);
void PDEC_HAL_AUIB_SetRdPtr(UINT8 ui8PdecCh, UINT32 ui32CpbRdPtr);
void PDEC_HAL_AUIB_Pop(UINT8 ui8PdecCh, S_PDEC_AUI_T *pPdecAui);
void PDEC_HAL_Flush(UINT8 ui8PdecCh);
UINT32 *PDEC_HAL_GetLatestDecodedAUI(UINT8 ui8PdecCh, S_PDEC_AUI_T *pPdecAui);
void PDEC_UTIL_SetDiscontinuity(UINT32 *pui32PdecAuiVirPtr, BOOLEAN bStccDiscontinuity);
void PDEC_UTIL_SetWrapAround(UINT32 *pui32PdecAuiVirPtr, BOOLEAN bWrapAround);

UINT32 PDEC_GET_Stc(UINT8 ui8PdecCh);

#ifdef __cplusplus
}
#endif

#endif /* _PDEC_HAL_H_ */

