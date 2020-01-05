
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
#ifndef _HAL_TOP_H
#define _HAL_TOP_H

#if 0
/*
 * interrupt flags
 *
 * platform에 따라 TOP_HAL_Init() 함수에서 초기화 된다. 사용되지 않는 interrupt
 * flag에 대해서는 0으로 설정해 해당 변수를 사용했을 때 아무런 동작을 하지 않게
 * 하도록 한다.
 */
extern unsigned int TOP_HAL_VDEC_INTR_MACH0;
extern unsigned int TOP_HAL_VDEC_INTR_MACH1;
extern unsigned int TOP_HAL_VDEC_INTR_NOT_ALLOWED_MEMACCESS;
extern unsigned int TOP_HAL_VDEC_INTR_SIMPLE_DE0;
extern unsigned int TOP_HAL_VDEC_INTR_VSYNC0;
extern unsigned int TOP_HAL_VDEC_INTR_VSYNC1;
extern unsigned int TOP_HAL_VDEC_INTR_VSYNC2;
extern unsigned int TOP_HAL_VDEC_INTR_VSYNC3;
extern unsigned int TOP_HAL_VDEC_INTR_LQ0_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_LQ1_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_LQ2_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_LQ3_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_PDEC0_AU_DETECT;
extern unsigned int TOP_HAL_VDEC_INTR_PDEC1_AU_DETECT;
extern unsigned int TOP_HAL_VDEC_INTR_PDEC2_AU_DETECT;
extern unsigned int TOP_HAL_VDEC_INTR_BUFFER_STATUS;
extern unsigned int TOP_HAL_VDEC_INTR_SIMPLE_DE1;
extern unsigned int TOP_HAL_VDEC_INTR_MACH0_SRST_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_MACH1_SRST_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_PDEC_SRST_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_G1DEC_SRST_DONE;
extern unsigned int TOP_HAL_VDEC_INTR_VSYNC4;
extern unsigned int TOP_HAL_VDEC_INTR_G1DEC;

extern unsigned int TOP_HAL_BUFFER_INTR_PDEC0_CPB_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC0_CPB_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC0_AUB_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC0_AUB_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC0_BDRC_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC0_BDRC_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC0_IES_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC1_CPB_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC1_CPB_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC1_AUB_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC1_AUB_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC1_BDRC_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC1_BDRC_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC1_IES_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC2_CPB_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC2_CPB_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC2_AUB_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC2_AUB_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC2_BDRC_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC2_BDRC_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_PDEC2_IES_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC0_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC1_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC2_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC3_ALMOST_EMPTY;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC0_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC1_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC2_ALMOST_FULL;
extern unsigned int TOP_HAL_BUFFER_INTR_LQC3_ALMOST_FULL;


/*
 * HAL이 포함하는 함수 포인터 구조체
 *
 * HAL이 제공하는 함수 포인터 구조체로써 platform에 따른 함수 포인터가
 * 연결된다. 각각의 함수 포인터는 NULL이 될수 없으며, 동작을 하지 않는
 * HAL기능에 대해서는 빈 함수 포인터가 연결되어야 한다.
 */
struct TOP_HAL
{
	int (*Init) (void);
	unsigned int (*GetVersion) (void);
	int (*ResetMach) (int vcore_num);
	int (*ResetPDECAll) (void);
	int (*SetPdecInputSelection) (int ui8PdecCh, int ui8TECh);
	int (*GetPdecInputSelection) (int ui8PdecCh);
	int (*EnablePdecInput) (int ui8PdecCh);
	int (*DisablePdecInput) (int ui8PdecCh);
	int (*IsEnablePdecInput) (int ui8PdecCh);
	int (*SetLQSyncMode) (int ui8LQCh, int ui8Vsync);
	int (*GetLQSyncMode) (int ui8LQCh);
	int (*SetLQInputSelection) (int ui8LQCh, int ui8PdecCh);
	int (*GetLQInputSelection) (int ui8LQCh);
	int (*EnableLQInput) (int ui8LQCh);
	int (*DisableLQInput) (int ui8LQCh);
	int (*IsEnableLQInput) (int ui8LQCh);
	int (*SetMachIntrMode) (int vcore_num, int IntrMode);
	int (*GetMachIntrMode) (int vcore_num);
	int (*GetMachIdleStatus) (int vcore_num);
	int (*GetMachUnderRunStatus) (int vcore_num);
	int (*EnableExtIntr) (VDEC_INTR_T ui32IntrSrc);
	int (*DisableExtIntr) (VDEC_INTR_T ui32IntrSrc);
	int (*ClearExtIntr) (VDEC_INTR_T ui32IntrSrc);
	int (*ClearExtIntrMsk) (unsigned int ui32IntrMsk);
	int (*DisableExtIntrAll) (void);
	int (*IsExtIntrEnable) (VDEC_INTR_T eVdecIntrSrc);
	unsigned int (*GetExtIntrStatus) (void);
	int (*EnableInterIntr) (VDEC_INTR_T ui32IntrSrc);
	int (*DisableInterIntr) (VDEC_INTR_T ui32IntrSrc);
	int (*ClearInterIntr) (VDEC_INTR_T ui32IntrSrc);
	int (*ClearInterIntrMsk) (unsigned int ui32IntrMsk);
	int (*DisableInterIntrAll) (void);
	int (*IsInterIntrEnable) (VDEC_INTR_T ui32IntrSrc);
	unsigned int (*GetInterIntrStatus) (void);
	int (*EnableBufIntr) (BUFFER_INTR_T ui32IntrSrc);
	int (*DisableBufIntr) (BUFFER_INTR_T ui32IntrSrc);
	int (*ClearBufIntr) (BUFFER_INTR_T ui32IntrSrc);
	int (*ClearBufIntrMsk) (unsigned int ui32IntrMsk);
	int (*DisableBufIntrAll) (void);
	int (*IsBufIntrEnable) (BUFFER_INTR_T ui32IntrSrc);
	unsigned int (*GetBufIntrStatus) (void);
	unsigned int (*GetGSTCC) (void);
};


/*
 * struct TOP_HAL 구조체의 함수 포인터를 호출하기 쉽게 해주는 매크로
 *
 * 실제 함수 포인터는 TOP_HAL 구조체 변수에 저장되며, TOP_HAL 구조체 변수는
 * TOP_HAL_Init() 함수에서 초기화 된다.
 */
#define TOP_HAL(cmd, args...)		{ if (TOP_HAL->cmd) TOP_HAL->cmd (##args); else 0; }
extern struct TOP_HAL *TOP_HAL;


extern int TOP_HAL_Init (void);


#else

#include <generated/autoconf.h>

#if defined (CONFIG_MACH_LG1152)
#include "lg1152/top_hal_api.h"
#elif defined (CONFIG_MACH_LG1154)
#include "lg1154/top_hal_api.h"
#else
#error "unknown platform chip"
#endif

#endif

#endif
