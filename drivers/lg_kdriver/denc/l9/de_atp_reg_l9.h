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
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2011.02.17
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DE_ATP_REG_L9_INC
#define  DE_ATP_REG_L9_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "../de/l9/de_reg_mac.h"
#include "l9/de_atp_reg_l9a0.h"
#include "../de/l9/de_atp_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_ATP_L9_RdFL(_r)                  		FN_CHIP_RdFL(DE_ATP, L9, _r)
#define DE_ATP_L9_WrFL(_r)                  		FN_CHIP_WrFL(DE_ATP, L9, _r)
#define DE_ATP_L9_Rd(_r)                    		FN_CHIP_Rd32(DE_ATP, L9, _r)
#define DE_ATP_L9_Wr(_r, _v)                		FN_CHIP_Wr32(DE_ATP, L9, _r, _v)
#define DE_ATP_L9_Rd01(_r, _f01, _v01)      		FN_CHIP_Rd01(DE_ATP, L9, _r, _f01, _v01)
#define DE_ATP_L9_Wr01(_r, _f01, _v01)      		FN_CHIP_Wr01(DE_ATP, L9, _r, _f01, _v01)
#define DE_ATP_L9_WfCM(_r, _f, _c, _m)      		FN_CHIP_WfCM(DE_ATP, L9, _r, _f, _c, _m)
#define DE_ATP_L9_WfCV(_r, _f, _c, _v1, _v2)        FN_CHIP_WfCV(DE_ATP, L9, _r, _f, _c, _v1, _v2)
#define DE_ATP_L9_FLRd(_r, _v)              		FN_CHIP_FLRd(DE_ATP, L9, _r, _v)
#define DE_ATP_L9_FLWr(_r, _v)              		FN_CHIP_FLWr(DE_ATP, L9, _r, _v)
#define DE_ATP_L9_FLRf(_r, _f01, _v01)      		FN_CHIP_FLRf(DE_ATP, L9, _r, _f01, _v01)
#define DE_ATP_L9_FLWf(_r, _f01, _v01)      		FN_CHIP_FLWf(DE_ATP, L9, _r, _f01, _v01)
#define DE_ATP_L9_FLCM(_r, _f, _c, _m)      		FN_CHIP_FLCM(DE_ATP, L9, _r, _f, _c, _m)
#define DE_ATP_L9_FLCV(_r, _f, _c, _v1, _v2)    	FN_CHIP_FLCV(DE_ATP, L9, _r, _f, _c, _v1, _v2)

#define DE_ATP_L9A_RdFL(_r)                         REG_PHYS_VER_RdFL(g##DE_ATP##_##L9, a0, _r)
#define DE_ATP_L9A_WrFL(_r)                         REG_PHYS_VER_WrFL(g##DE_ATP##_##L9, a0, _r)
#define DE_ATP_L9A_Rd(_r)                           REG_SHDW_VER_Rd32(g##DE_ATP##_##L9, a0, _r)
#define DE_ATP_L9A_Wr(_r, _v)                       REG_SHDW_VER_Wr32(g##DE_ATP##_##L9, a0, _r, _v)
#define DE_ATP_L9A_Rd01(_r, _f01, _v01)             REG_SHDW_VER_Rd01(g##DE_ATP##_##L9, a0, _r, _f01, _v01)
#define DE_ATP_L9A_Wr01(_r, _f01, _v01)             REG_SHDW_VER_Wr01(g##DE_ATP##_##L9, a0, _r, _f01, _v01)
#define DE_ATP_L9A_FLRf(_r, _f01, _v01)             REG_PHYS_VER_FLRf(g##DE_ATP##_##L9, a0, _r, _f01, _v01)
#define DE_ATP_L9A_FLWf(_r, _f01, _v01)             REG_PHYS_VER_FLWf(g##DE_ATP##_##L9, a0, _r, _f01, _v01)
#define DE_ATP_L9A_WfCM(_r, _f, _c, _m)             REG_SHDW_VER_WfCM(g##DE_ATP##_##L9, a0, _r, _f, _c, _m)
#define DE_ATP_L9A_FLCM(_r, _f, _c, _m)             REG_PHYS_VER_FLCM(g##DE_ATP##_##L9, a0, _r, _f, _c, _m)
#define DE_ATP_L9A_WfCV(_r, _f, _c, _v1, _v2)       REG_SHDW_VER_WfCV(g##DE_ATP##_##L9, a0, _r, _f, _c, _v1, _v2)
#define DE_ATP_L9A_FLRd(_r, _v)              		REG_PHYS_VER_FLRd(g##DE_ATP##_##L9, a0, _r, _v)
#define DE_ATP_L9A_FLWr(_r, _v)              		REG_PHYS_VER_FLWr(g##DE_ATP##_##L9, a0, _r, _v)
#define DE_ATP_L9A_FLCV(_r, _f, _c, _v1, _v2)    	REG_PHYS_VER_FLCV(g##DE_ATP##_##L9, a0, _r, _f, _c, _v1, _v2)

#define DE_ATP_L9B_RdFL(_r)                         REG_PHYS_VER_RdFL(g##DE_ATP##_##L9, b0, _r)
#define DE_ATP_L9B_WrFL(_r)                         REG_PHYS_VER_WrFL(g##DE_ATP##_##L9, b0, _r)
#define DE_ATP_L9B_Rd(_r)                           REG_SHDW_VER_Rd32(g##DE_ATP##_##L9, b0, _r)
#define DE_ATP_L9B_Wr(_r, _v)                       REG_SHDW_VER_Wr32(g##DE_ATP##_##L9, b0, _r, _v)
#define DE_ATP_L9B_Rd01(_r, _f01, _v01)             REG_SHDW_VER_Rd01(g##DE_ATP##_##L9, b0, _r, _f01, _v01)
#define DE_ATP_L9B_Wr01(_r, _f01, _v01)             REG_SHDW_VER_Wr01(g##DE_ATP##_##L9, b0, _r, _f01, _v01)
#define DE_ATP_L9B_FLRf(_r, _f01, _v01)             REG_PHYS_VER_FLRf(g##DE_ATP##_##L9, b0, _r, _f01, _v01)
#define DE_ATP_L9B_FLWf(_r, _f01, _v01)             REG_PHYS_VER_FLWf(g##DE_ATP##_##L9, b0, _r, _f01, _v01)
#define DE_ATP_L9B_WfCM(_r, _f, _c, _m)             REG_SHDW_VER_WfCM(g##DE_ATP##_##L9, b0, _r, _f, _c, _m)
#define DE_ATP_L9B_FLCM(_r, _f, _c, _m)             REG_PHYS_VER_FLCM(g##DE_ATP##_##L9, b0, _r, _f, _c, _m)
#define DE_ATP_L9B_WfCV(_r, _f, _c, _v1, _v2)       REG_SHDW_VER_WfCV(g##DE_ATP##_##L9, b0, _r, _f, _c, _v1, _v2)
#define DE_ATP_L9B_FLRd(_r, _v)              		REG_PHYS_VER_FLRd(g##DE_ATP##_##L9, b0, _r, _v)
#define DE_ATP_L9B_FLWr(_r, _v)              		REG_PHYS_VER_FLWr(g##DE_ATP##_##L9, b0, _r, _v)
#define DE_ATP_L9B_FLCV(_r, _f, _c, _v1, _v2)    	REG_PHYS_VER_FLCV(g##DE_ATP##_##L9, b0, _r, _f, _c, _v1, _v2)
/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DE_ATP_REG_L9A0_T *a0;
		DE_ATP_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_ATP_REG_L9A0_T *a0;
		volatile DE_ATP_REG_L9B0_T *b0;
    } phys;
} DE_ATP_REG_L9_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_ATP_REG_L9_INC  ----- */
/**  @} */
