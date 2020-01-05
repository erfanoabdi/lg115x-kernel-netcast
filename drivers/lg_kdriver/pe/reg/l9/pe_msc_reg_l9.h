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


/** @file pe_msc_reg_l9.h
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
#ifndef _PE_MSC_REG_L9_H_
#define _PE_MSC_REG_L9_H_
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_msc_reg_l9a0.h"
#include "pe_msc_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_MSL_L9_RdFL(_r)                          PE_FN_CHIP_RdFL(PE_MSL, L9, _r)
#define PE_MSL_L9_WrFL(_r)                          PE_FN_CHIP_WrFL(PE_MSL, L9, _r)
#define PE_MSL_L9_Rd(_r)                            PE_FN_CHIP_Rd32(PE_MSL, L9, _r)
#define PE_MSL_L9_Wr(_r, _v)                        PE_FN_CHIP_Wr32(PE_MSL, L9, _r, _v)
#define PE_MSL_L9_Rd01(_r, _f01, _v01)              PE_FN_CHIP_Rd01(PE_MSL, L9, _r, _f01, _v01)
#define PE_MSL_L9_Wr01(_r, _f01, _v01)              PE_FN_CHIP_Wr01(PE_MSL, L9, _r, _f01, _v01)
#define PE_MSL_L9_WfCM(_r, _f, _c, _m)              PE_FN_CHIP_WfCM(PE_MSL, L9, _r, _f, _c, _m)
#define PE_MSL_L9_FLRd(_r, _v)                      PE_FN_CHIP_FLRd(PE_MSL, L9, _r, _v)
#define PE_MSL_L9_FLWr(_r, _v)                      PE_FN_CHIP_FLWr(PE_MSL, L9, _r, _v)
#define PE_MSL_L9_FLRf(_r, _f01, _v01)              PE_FN_CHIP_FLRf(PE_MSL, L9, _r, _f01, _v01)
#define PE_MSL_L9_FLWf(_r, _f01, _v01)              PE_FN_CHIP_FLWf(PE_MSL, L9, _r, _f01, _v01)

#define PE_MSR_L9_RdFL(_r)                          PE_FN_CHIP_RdFL(PE_MSR, L9, _r)
#define PE_MSR_L9_WrFL(_r)                          PE_FN_CHIP_WrFL(PE_MSR, L9, _r)
#define PE_MSR_L9_Rd(_r)                            PE_FN_CHIP_Rd32(PE_MSR, L9, _r)
#define PE_MSR_L9_Wr(_r, _v)                        PE_FN_CHIP_Wr32(PE_MSR, L9, _r, _v)
#define PE_MSR_L9_Rd01(_r, _f01, _v01)              PE_FN_CHIP_Rd01(PE_MSR, L9, _r, _f01, _v01)
#define PE_MSR_L9_Wr01(_r, _f01, _v01)              PE_FN_CHIP_Wr01(PE_MSR, L9, _r, _f01, _v01)
#define PE_MSR_L9_WfCM(_r, _f, _c, _m)              PE_FN_CHIP_WfCM(PE_MSR, L9, _r, _f, _c, _m)
#define PE_MSR_L9_FLRd(_r, _v)                      PE_FN_CHIP_FLRd(PE_MSR, L9, _r, _v)
#define PE_MSR_L9_FLWr(_r, _v)                      PE_FN_CHIP_FLWr(PE_MSR, L9, _r, _v)
#define PE_MSR_L9_FLRf(_r, _f01, _v01)              PE_FN_CHIP_FLRf(PE_MSR, L9, _r, _f01, _v01)
#define PE_MSR_L9_FLWf(_r, _f01, _v01)              PE_FN_CHIP_FLWf(PE_MSR, L9, _r, _f01, _v01)

#define PE_MSR_L9A_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_MSR##_##L9, a0, _r)
#define PE_MSR_L9A_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_MSR##_##L9, a0, _r)
#define PE_MSR_L9A_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_MSR##_##L9, a0, _r)
#define PE_MSR_L9A_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_MSR##_##L9, a0, _r, _v)
#define PE_MSR_L9A_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_MSR##_##L9, a0, _r, _f01, _v01)
#define PE_MSR_L9A_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_MSR##_##L9, a0, _r, _f01, _v01)
#define PE_MSR_L9A_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_MSR##_##L9, a0, _r, _f01, _v01)
#define PE_MSR_L9A_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_MSR##_##L9, a0, _r, _f01, _v01)
#define PE_MSR_L9A_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_MSR##_##L9, a0, _r, _f, _c, _m)
#define PE_MSR_L9A_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_MSR##_##L9, a0, _r, _f, _c, _m)
#define PE_MSR_L9A_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_MSR##_##L9, a0, _r, _f, _c, _v1, _v2)
#define PE_MSR_L9A_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_MSR##_##L9, a0, _r, _v)
#define PE_MSR_L9A_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_MSR##_##L9, a0, _r, _v)
#define PE_MSR_L9A_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_MSR##_##L9, a0, _r, _f, _c, _v1, _v2)

#define PE_MSR_L9B_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_MSR##_##L9, b0, _r)
#define PE_MSR_L9B_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_MSR##_##L9, b0, _r)
#define PE_MSR_L9B_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_MSR##_##L9, b0, _r)
#define PE_MSR_L9B_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_MSR##_##L9, b0, _r, _v)
#define PE_MSR_L9B_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_MSR##_##L9, b0, _r, _f01, _v01)
#define PE_MSR_L9B_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_MSR##_##L9, b0, _r, _f01, _v01)
#define PE_MSR_L9B_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_MSR##_##L9, b0, _r, _f01, _v01)
#define PE_MSR_L9B_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_MSR##_##L9, b0, _r, _f01, _v01)
#define PE_MSR_L9B_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_MSR##_##L9, b0, _r, _f, _c, _m)
#define PE_MSR_L9B_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_MSR##_##L9, b0, _r, _f, _c, _m)
#define PE_MSR_L9B_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_MSR##_##L9, b0, _r, _f, _c, _v1, _v2)
#define PE_MSR_L9B_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_MSR##_##L9, b0, _r, _v)
#define PE_MSR_L9B_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_MSR##_##L9, b0, _r, _v)
#define PE_MSR_L9B_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_MSR##_##L9, b0, _r, _f, _c, _v1, _v2)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        PE_MSL_REG_L9A0_T *a0;
		PE_MSL_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_MSL_REG_L9A0_T *a0;
		volatile PE_MSL_REG_L9B0_T *b0;
    } phys;
} PE_MSL_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_MSR_REG_L9A0_T *a0;
		PE_MSR_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_MSR_REG_L9A0_T *a0;
		volatile PE_MSR_REG_L9B0_T *b0;
    } phys;
} PE_MSR_REG_L9_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* _PE_MSC_REG_L9_H_ */

