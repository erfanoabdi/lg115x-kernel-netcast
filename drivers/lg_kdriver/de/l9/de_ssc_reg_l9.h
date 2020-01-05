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
#ifndef  DE_SSC_REG_L9_INC
#define  DE_SSC_REG_L9_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "l9/de_reg_mac.h"
#include "l9/de_ssc_reg_l9a0.h"
#include "l9/de_ssc_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_SSC_L9_RdFL(_r)                  FN_CHIP_RdFL(DE_SSC, L9, _r)
#define DE_SSC_L9_WrFL(_r)                  FN_CHIP_WrFL(DE_SSC, L9, _r)
#define DE_SSC_L9_Rd(_r)                    FN_CHIP_Rd32(DE_SSC, L9, _r)
#define DE_SSC_L9_Wr(_r, _v)                FN_CHIP_Wr32(DE_SSC, L9, _r, _v)
#define DE_SSC_L9_Rd01(_r, _f01, _v01)      FN_CHIP_Rd01(DE_SSC, L9, _r, _f01, _v01)
#define DE_SSC_L9_Wr01(_r, _f01, _v01)      FN_CHIP_Wr01(DE_SSC, L9, _r, _f01, _v01)
#define DE_SSC_L9_FLRd(_r, _v)              FN_CHIP_FLRd(DE_SSC, L9, _r, _v)
#define DE_SSC_L9_FLWr(_r, _v)              FN_CHIP_FLWr(DE_SSC, L9, _r, _v)
#define DE_SSC_L9_FLRf(_r, _f01, _v01)      FN_CHIP_FLRf(DE_SSC, L9, _r, _f01, _v01)
#define DE_SSC_L9_FLWf(_r, _f01, _v01)      FN_CHIP_FLWf(DE_SSC, L9, _r, _f01, _v01)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DE_SSC_REG_L9A0_T *a0;
		DE_SSC_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_SSC_REG_L9A0_T *a0;
		volatile DE_SSC_REG_L9B0_T *b0;
    } phys;
} DE_SSC_REG_L9_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_SSC_REG_L9_INC  ----- */
/**  @} */
