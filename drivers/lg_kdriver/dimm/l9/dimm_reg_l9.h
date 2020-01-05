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
 * date       2011.02.25
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DIMM_REG_L9_INC
#define  DIMM_REG_L9_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "l9/de_reg_mac.h"
#include "l8/dimm_reg_l8b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DIMM_L9_RdFL(_r)						  FN_CHIP_RdFL(DIMM, L9, _r)
#define DIMM_L9_WrFL(_r)						  FN_CHIP_WrFL(DIMM, L9, _r)
#define DIMM_L9_Rd(_r)							  FN_CHIP_Rd32(DIMM, L9, _r)
#define DIMM_L9_Wr(_r, _v)						  FN_CHIP_Wr32(DIMM, L9, _r, _v)
#define DIMM_L9_Rd01(_r, _f01, _v01)			  FN_CHIP_Rd01(DIMM, L9, _r, _f01, _v01)
#define DIMM_L9_Wr01(_r, _f01, _v01)			  FN_CHIP_Wr01(DIMM, L9, _r, _f01, _v01)
#define DIMM_L9_WfCM(_r, _f, _c, _m)			  FN_CHIP_WfCM(DIMM, L9, _r, _f, _c, _m)
#define DIMM_L9_WfCV(_r, _f, _c, _v1, _v2)		  FN_CHIP_WfCV(DIMM, L9, _r, _f, _c, _v1, _v2)
#define DIMM_L9_FLRd(_r, _v)					  FN_CHIP_FLRd(DIMM, L9, _r, _v)
#define DIMM_L9_FLWr(_r, _v)					  FN_CHIP_FLWr(DIMM, L9, _r, _v)
#define DIMM_L9_FLRf(_r, _f01, _v01)			  FN_CHIP_FLRf(DIMM, L9, _r, _f01, _v01)
#define DIMM_L9_FLWf(_r, _f01, _v01)			  FN_CHIP_FLWf(DIMM, L9, _r, _f01, _v01)
#define DIMM_L9_FLCM(_r, _f, _c, _m)			  FN_CHIP_FLCM(DIMM, L9, _r, _f, _c, _m)
#define DIMM_L9_FLCV(_r, _f, _c, _v1, _v2)		  FN_CHIP_FLCV(DIMM, L9, _r, _f, _c, _v1, _v2)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        LED_L8B0_REG_T *a0;
		LED_L8B0_REG_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile LED_L8B0_REG_T *a0;
		volatile LED_L8B0_REG_T *b0;
    } phys;
} DIMM_REG_L9_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DIMM_REG_L9_INC  ----- */
/**  @} */
