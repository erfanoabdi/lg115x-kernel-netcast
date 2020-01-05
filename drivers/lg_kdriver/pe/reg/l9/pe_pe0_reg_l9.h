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


/** @file pe_pe0_reg_l9.h
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
#ifndef _PE_PE0_REG_L9_H_
#define _PE_PE0_REG_L9_H_
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_pe0_reg_l9a0.h"
#include "pe_pe0_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
// A0, A1
#define PE_P0L_L9_RdFL(_r)                  PE_FN_CHIP_RdFL(PE_P0L, L9, _r)
#define PE_P0L_L9_WrFL(_r)                  PE_FN_CHIP_WrFL(PE_P0L, L9, _r)
#define PE_P0L_L9_Rd(_r)                    PE_FN_CHIP_Rd32(PE_P0L, L9, _r)
#define PE_P0L_L9_Wr(_r, _v)                PE_FN_CHIP_Wr32(PE_P0L, L9, _r, _v)
#define PE_P0L_L9_Rd01(_r, _f01, _v01)      PE_FN_CHIP_Rd01(PE_P0L, L9, _r, _f01, _v01)
#define PE_P0L_L9_Wr01(_r, _f01, _v01)      PE_FN_CHIP_Wr01(PE_P0L, L9, _r, _f01, _v01)
#define PE_P0L_L9_WfCM(_r, _f, _c, _m)      PE_FN_CHIP_WfCM(PE_P0L, L9, _r, _f, _c, _m)

#define PE_P0R_L9_RdFL(_r)                  PE_FN_CHIP_RdFL(PE_P0R, L9, _r)
#define PE_P0R_L9_WrFL(_r)                  PE_FN_CHIP_WrFL(PE_P0R, L9, _r)
#define PE_P0R_L9_Rd(_r)                    PE_FN_CHIP_Rd32(PE_P0R, L9, _r)
#define PE_P0R_L9_Wr(_r, _v)                PE_FN_CHIP_Wr32(PE_P0R, L9, _r, _v)
#define PE_P0R_L9_Rd01(_r, _f01, _v01)      PE_FN_CHIP_Rd01(PE_P0R, L9, _r, _f01, _v01)
#define PE_P0R_L9_Wr01(_r, _f01, _v01)      PE_FN_CHIP_Wr01(PE_P0R, L9, _r, _f01, _v01)
#define PE_P0R_L9_WfCM(_r, _f, _c, _m)      PE_FN_CHIP_WfCM(PE_P0R, L9, _r, _f, _c, _m)

// B0
#define PE_P0L_L9B0_RdFL(_r)                  PE_REG_PHYS_VER_RdFL(g##PE_P0L##_##L9B, b0, _r)
#define PE_P0L_L9B0_WrFL(_r)                  PE_REG_PHYS_VER_WrFL(g##PE_P0L##_##L9B, b0, _r)
#define PE_P0L_L9B0_Rd(_r)                    PE_REG_SHDW_VER_Rd32(g##PE_P0L##_##L9B, b0, _r)
#define PE_P0L_L9B0_Wr(_r, _v)                PE_REG_SHDW_VER_Wr32(g##PE_P0L##_##L9B, b0, _r, _v)
#define PE_P0L_L9B0_Rd01(_r, _f01, _v01)      PE_REG_SHDW_VER_Rd01(g##PE_P0L##_##L9B, b0, _r, _f01, _v01)
#define PE_P0L_L9B0_Wr01(_r, _f01, _v01)      PE_REG_SHDW_VER_Wr01(g##PE_P0L##_##L9B, b0, _r, _f01, _v01)
#define PE_P0L_L9B0_WfCM(_r, _f, _c, _m)      PE_REG_SHDW_VER_WfCM(g##PE_P0L##_##L9B, b0, _r, _f, _c, _m)

#define PE_P0R_L9B0_RdFL(_r)                  PE_REG_PHYS_VER_RdFL(g##PE_P0R##_##L9B, b0, _r)
#define PE_P0R_L9B0_WrFL(_r)                  PE_REG_PHYS_VER_WrFL(g##PE_P0R##_##L9B, b0, _r)
#define PE_P0R_L9B0_Rd(_r)                    PE_REG_SHDW_VER_Rd32(g##PE_P0R##_##L9B, b0, _r)
#define PE_P0R_L9B0_Wr(_r, _v)                PE_REG_SHDW_VER_Wr32(g##PE_P0R##_##L9B, b0, _r, _v)
#define PE_P0R_L9B0_Rd01(_r, _f01, _v01)      PE_REG_SHDW_VER_Rd01(g##PE_P0R##_##L9B, b0, _r, _f01, _v01)
#define PE_P0R_L9B0_Wr01(_r, _f01, _v01)      PE_REG_SHDW_VER_Wr01(g##PE_P0R##_##L9B, b0, _r, _f01, _v01)
#define PE_P0R_L9B0_WfCM(_r, _f, _c, _m)      PE_REG_SHDW_VER_WfCM(g##PE_P0R##_##L9B, b0, _r, _f, _c, _m)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        PE_P0L_REG_L9A0_T *a0;
		PE_P0L_REG_L9A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_P0L_REG_L9A0_T *a0;
		volatile PE_P0L_REG_L9A0_T *b0;
    } phys;
} PE_P0L_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_P0R_REG_L9A0_T *a0;
		PE_P0R_REG_L9A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_P0R_REG_L9A0_T *a0;
		volatile PE_P0R_REG_L9A0_T *b0;
    } phys;
} PE_P0R_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
		PE_P0L_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile PE_P0L_REG_L9B0_T *b0;
    } phys;
} PE_P0L_REG_L9B_T;

typedef struct {
    union {
        UINT32          *addr;
		PE_P0R_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile PE_P0R_REG_L9B0_T *b0;
    } phys;
} PE_P0R_REG_L9B_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* _PE_PE0_REG_L9_H_ */

