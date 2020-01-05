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
 * VBI module
 *
 *  author      won.hur (won.hur@lge.com)
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg115x_vbi
 *  @{
 */

#ifndef _VBI_HW_H_
#define _VBI_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct{
	unsigned short wss_data;
	unsigned int wss_int_time;
} sWSSBufInform;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
// function pointer
extern int (*VBI_CheckVline625)(void);
extern int (*VBI_CheckAnalogCP)(void);

extern int (*VBI_TTX_HWInitialize)(void);
extern int (*VBI_TTX_SetInputFormat)(eVBIDataType type);
extern int (*VBI_TTX_SetInterrupt)(int on_off);
extern int (*VBI_TTX_ParsingVBIData)(sHeaderData *data);
extern int (*VBI_TTX_PutVBIData)(sHeaderData *data);
extern int (*VBI_TTX_SetInterruptClear)(void);
extern int (*VBI_TTX_Enable_VPS_Slicer)(BOOLEAN Enable);
extern int (*VBI_TTX_Set_TT_Slicer_Mode)(unsigned int mode);
extern int (*VBI_TTX_SetVBILPF)(int onoff);
extern int (*VBI_TTX_CheckOnLine318)(int mode);
extern int (*VBI_TTX_SetTypeLine318)(int onoff);
extern int (*VBI_TTX_DebugPrintMode)(int mode);
#ifdef	KDRV_CONFIG_PM
extern int (*VBI_TTX_RunSuspend)(void);
extern int (*VBI_TTX_RunResume)(void);
#endif

// H13 Bx function prototype
int TTX_HWInitialize_H13Bx(void);
int TTX_SetInputFormat_H13Bx(eVBIDataType type);
int TTX_SetInterrupt_H13Bx(int on_off);
int TTX_ParsingVBIData_H13Bx(sHeaderData *data);
int TTX_PutVBIData_H13Bx(sHeaderData *data);
int TTX_SetInterruptClear_H13Bx(void);
int TTX_Enable_VPS_Slicer_H13Bx(BOOLEAN Enable);
int TTX_SetVBILPF_H13Bx(int onoff);
int TTX_CheckOnLine318_H13Bx(int mode);
int TTX_SetTypeLine318_H13Bx(int onoff);
int TTX_Set_TT_Slicer_Mode_H13Bx(unsigned int slicer_mode);
int TTX_DebugPrintMode_H13Bx(int mode);
int TTX_CheckVline625_H13Bx(void);
int TTX_CheckAnalogCP_H13Bx(void);

#ifdef	KDRV_CONFIG_PM
int TTX_RunSuspend_H13Bx(void);
int TTX_RunResume_H13Bx(void);
#endif

// H13 Ax function prototype
int TTX_HWInitialize_H13Ax(void);
int TTX_SetInputFormat_H13Ax(eVBIDataType type);
int TTX_SetInterrupt_H13Ax(int on_off);
int TTX_ParsingVBIData_H13Ax(sHeaderData *data);
int TTX_PutVBIData_H13Ax(sHeaderData *data);
int TTX_SetInterruptClear_H13Ax(void);
int TTX_Enable_VPS_Slicer_H13Ax(BOOLEAN Enable);
int TTX_SetVBILPF_H13Ax(int onoff);
int TTX_CheckOnLine318_H13Ax(int mode);
int TTX_SetTypeLine318_H13Ax(int onoff);
int TTX_Set_TT_Slicer_Mode_H13Ax(unsigned int slicer_mode);
int TTX_DebugPrintMode_H13Ax(int mode);
int TTX_CheckVline625_H13Ax(void);
int TTX_CheckAnalogCP_H13Ax(void);

#ifdef	KDRV_CONFIG_PM
int TTX_RunSuspend_H13Ax(void);
int TTX_RunResume_H13Ax(void);
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
// L9 Bx function prototype
int TTX_HWInitialize_L9Bx(void);
int TTX_SetInputFormat_L9Bx(eVBIDataType type);
int TTX_SetInterrupt_L9Bx(int on_off);
int TTX_ParsingVBIData_L9Bx(sHeaderData *data);
int TTX_PutVBIData_L9Bx(sHeaderData *data);
int TTX_SetInterruptClear_L9Bx(void);
int TTX_Enable_VPS_Slicer_L9Bx(BOOLEAN Enable);
int TTX_SetVBILPF_L9Bx(int onoff);
int TTX_CheckOnLine318_L9Bx(int mode);
int TTX_SetTypeLine318_L9Bx(int onoff);
int TTX_Set_TT_Slicer_Mode_L9Bx(unsigned int slicer_mode);
#ifdef	KDRV_CONFIG_PM
int TTX_RunSuspend_L9Bx(void);
int TTX_RunResume_L9Bx(void);
#endif
#endif



// For CC
extern int (*VBI_CC_HWInitialize)(void);
extern int (*VBI_CC_SetInputFormat)(eVBIDataType type);
extern int (*VBI_CC_SetInterrupt)(int on_off);
extern int (*VBI_CC_ParsingVBIData)(unsigned int *packet);
extern int (*VBI_CC_SetInterruptClear)(void);
extern int (*VBI_CC_DebugPrintMode)(int mode);

#ifdef	KDRV_CONFIG_PM
extern int (*VBI_CC_RunSuspend)(void);
extern int (*VBI_CC_RunResume)(void);
#endif

// H13Bx function prototype
int CC_H13Bx_HWInitialize(void);
int CC_H13Bx_SetInputFormat(eVBIDataType type);
int CC_H13Bx_SetInterrupt(int on_off);
int CC_H13Bx_ParsingVBIData(unsigned int *packet);
int CC_H13Bx_SetInterruptClear(void);
int CC_H13Bx_DebugPrintMode(int mode);
int CC_H13Bx_CheckVline625(void);
int CC_H13Bx_CheckAnalogCP(void);

#ifdef	KDRV_CONFIG_PM
int CC_H13Bx_RunSuspend(void);
int CC_H13Bx_RunResume(void);
#endif



// H13Ax function prototype
int CC_H13Ax_HWInitialize(void);
int CC_H13Ax_SetInputFormat(eVBIDataType type);
int CC_H13Ax_SetInterrupt(int on_off);
int CC_H13Ax_ParsingVBIData(unsigned int *packet);
int CC_H13Ax_SetInterruptClear(void);
int CC_H13Ax_DebugPrintMode(int mode);
int CC_H13Ax_CheckVline625(void);
int CC_H13Ax_CheckAnalogCP(void);

#ifdef	KDRV_CONFIG_PM
int CC_H13Ax_RunSuspend(void);
int CC_H13Ax_RunResume(void);
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
// L9 Bx function prototype
int CC_L9B0_HWInitialize(void);
int CC_L9B0_SetInputFormat(eVBIDataType type);
int CC_L9B0_SetInterrupt(int on_off);
int CC_L9B0_ParsingVBIData(unsigned int *packet);
int CC_L9B0_SetInterruptClear(void);
#ifdef	KDRV_CONFIG_PM
int CC_L9B0_RunSuspend(void);
int CC_L9B0_RunResume(void);
#endif
#endif


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VBI_HW_H_ */

/** @} */

