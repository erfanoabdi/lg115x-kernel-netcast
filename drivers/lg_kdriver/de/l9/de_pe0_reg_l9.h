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
#ifndef  DE_PE0_REG_L9_INC
#define  DE_PE0_REG_L9_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "l9/de_reg_mac.h"
#include "l9/de_pe0_reg_l9a0.h"
#include "l9/de_pe0_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
// A0, A1
#define DE_P0L_L9_RdFL(_r)                  FN_CHIP_RdFL(DE_P0L, L9, _r)
#define DE_P0L_L9_WrFL(_r)                  FN_CHIP_WrFL(DE_P0L, L9, _r)
#define DE_P0L_L9_Rd(_r)                    FN_CHIP_Rd32(DE_P0L, L9, _r)
#define DE_P0L_L9_Wr(_r, _v)                FN_CHIP_Wr32(DE_P0L, L9, _r, _v)
#define DE_P0L_L9_Rd01(_r, _f01, _v01)      FN_CHIP_Rd01(DE_P0L, L9, _r, _f01, _v01)
#define DE_P0L_L9_Wr01(_r, _f01, _v01)      FN_CHIP_Wr01(DE_P0L, L9, _r, _f01, _v01)
#define DE_P0L_L9_WfCM(_r, _f, _c, _m)      FN_CHIP_WfCM(DE_P0L, L9, _r, _f, _c, _m)

#define DE_P0R_L9_RdFL(_r)                  FN_CHIP_RdFL(DE_P0R, L9, _r)
#define DE_P0R_L9_WrFL(_r)                  FN_CHIP_WrFL(DE_P0R, L9, _r)
#define DE_P0R_L9_Rd(_r)                    FN_CHIP_Rd32(DE_P0R, L9, _r)
#define DE_P0R_L9_Wr(_r, _v)                FN_CHIP_Wr32(DE_P0R, L9, _r, _v)
#define DE_P0R_L9_Rd01(_r, _f01, _v01)      FN_CHIP_Rd01(DE_P0R, L9, _r, _f01, _v01)
#define DE_P0R_L9_Wr01(_r, _f01, _v01)      FN_CHIP_Wr01(DE_P0R, L9, _r, _f01, _v01)
#define DE_P0R_L9_WfCM(_r, _f, _c, _m)      FN_CHIP_WfCM(DE_P0R, L9, _r, _f, _c, _m)

// B0
#define DE_P0L_L9B0_RdFL(_r)                  REG_PHYS_VER_RdFL(g##DE_P0L##_##L9B, b0, _r)
#define DE_P0L_L9B0_WrFL(_r)                  REG_PHYS_VER_WrFL(g##DE_P0L##_##L9B, b0, _r)
#define DE_P0L_L9B0_Rd(_r)                    REG_SHDW_VER_Rd32(g##DE_P0L##_##L9B, b0, _r)
#define DE_P0L_L9B0_Wr(_r, _v)                REG_SHDW_VER_Wr32(g##DE_P0L##_##L9B, b0, _r, _v)
#define DE_P0L_L9B0_Rd01(_r, _f01, _v01)      REG_SHDW_VER_Rd01(g##DE_P0L##_##L9B, b0, _r, _f01, _v01)
#define DE_P0L_L9B0_Wr01(_r, _f01, _v01)      REG_SHDW_VER_Wr01(g##DE_P0L##_##L9B, b0, _r, _f01, _v01)
#define DE_P0L_L9B0_WfCM(_r, _f, _c, _m)      REG_SHDW_VER_WfCM(g##DE_P0L##_##L9B, b0, _r, _f, _c, _m)

#define DE_P0R_L9B0_RdFL(_r)                  REG_PHYS_VER_RdFL(g##DE_P0R##_##L9B, b0, _r)
#define DE_P0R_L9B0_WrFL(_r)                  REG_PHYS_VER_WrFL(g##DE_P0R##_##L9B, b0, _r)
#define DE_P0R_L9B0_Rd(_r)                    REG_SHDW_VER_Rd32(g##DE_P0R##_##L9B, b0, _r)
#define DE_P0R_L9B0_Wr(_r, _v)                REG_SHDW_VER_Wr32(g##DE_P0R##_##L9B, b0, _r, _v)
#define DE_P0R_L9B0_Rd01(_r, _f01, _v01)      REG_SHDW_VER_Rd01(g##DE_P0R##_##L9B, b0, _r, _f01, _v01)
#define DE_P0R_L9B0_Wr01(_r, _f01, _v01)      REG_SHDW_VER_Wr01(g##DE_P0R##_##L9B, b0, _r, _f01, _v01)
#define DE_P0R_L9B0_WfCM(_r, _f, _c, _m)      REG_SHDW_VER_WfCM(g##DE_P0R##_##L9B, b0, _r, _f, _c, _m)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DE_P0L_REG_L9A0_T *a0;
		DE_P0L_REG_L9A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_P0L_REG_L9A0_T *a0;
		volatile DE_P0L_REG_L9A0_T *b0;
    } phys;
} DE_P0L_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_P0R_REG_L9A0_T *a0;
		DE_P0R_REG_L9A0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_P0R_REG_L9A0_T *a0;
		volatile DE_P0R_REG_L9A0_T *b0;
    } phys;
} DE_P0R_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
		DE_P0L_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile DE_P0L_REG_L9B0_T *b0;
    } phys;
} DE_P0L_REG_L9B_T;

typedef struct {
    union {
        UINT32          *addr;
		DE_P0R_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
		volatile DE_P0R_REG_L9B0_T *b0;
    } phys;
} DE_P0R_REG_L9B_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_PE0_REG_L9_INC  ----- */
/**  @} */
