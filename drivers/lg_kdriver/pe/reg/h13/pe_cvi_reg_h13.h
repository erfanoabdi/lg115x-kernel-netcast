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


/** @file pe_cvi_reg_h13.h
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.17
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef _PE_CVI_REG_H13_H_
#define _PE_CVI_REG_H13_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_cvi_reg_h13a0.h"
#include "pe_cvi_reg_h13b0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_CVA_H13_RdFL(_r)						PE_FN_CHIP_RdFL(PE_CVA, H13, _r)
#define PE_CVA_H13_WrFL(_r)						PE_FN_CHIP_WrFL(PE_CVA, H13, _r)
#define PE_CVA_H13_Rd(_r)						PE_FN_CHIP_Rd32(PE_CVA, H13, _r)
#define PE_CVA_H13_Wr(_r, _v)					PE_FN_CHIP_Wr32(PE_CVA, H13, _r, _v)
#define PE_CVA_H13_Rd01(_r, _f01, _v01)			PE_FN_CHIP_Rd01(PE_CVA, H13, _r, _f01, _v01)
#define PE_CVA_H13_Wr01(_r, _f01, _v01)			PE_FN_CHIP_Wr01(PE_CVA, H13, _r, _f01, _v01)
#define PE_CVA_H13_FLRf(_r, _f01, _v01)			PE_FN_CHIP_FLRf(PE_CVA, H13, _r, _f01, _v01)
#define PE_CVA_H13_FLWf(_r, _f01, _v01)			PE_FN_CHIP_FLWf(PE_CVA, H13, _r, _f01, _v01)
#define PE_CVA_H13_WfCM(_r, _f, _c, _m)			PE_FN_CHIP_WfCM(PE_CVA, H13, _r, _f, _c, _m)
#define PE_CVA_H13_FLCM(_r, _f, _c, _m)			PE_FN_CHIP_FLCM(PE_CVA, H13, _r, _f, _c, _m)

#define PE_CVB_H13_RdFL(_r)						PE_FN_CHIP_RdFL(PE_CVB, H13, _r)
#define PE_CVB_H13_WrFL(_r)						PE_FN_CHIP_WrFL(PE_CVB, H13, _r)
#define PE_CVB_H13_Rd(_r)						PE_FN_CHIP_Rd32(PE_CVB, H13, _r)
#define PE_CVB_H13_Wr(_r, _v)					PE_FN_CHIP_Wr32(PE_CVB, H13, _r, _v)
#define PE_CVB_H13_Rd01(_r, _f01, _v01)			PE_FN_CHIP_Rd01(PE_CVB, H13, _r, _f01, _v01)
#define PE_CVB_H13_Wr01(_r, _f01, _v01)			PE_FN_CHIP_Wr01(PE_CVB, H13, _r, _f01, _v01)
#define PE_CVB_H13_FLRf(_r, _f01, _v01)			PE_FN_CHIP_FLRf(PE_CVB, H13, _r, _f01, _v01)
#define PE_CVB_H13_FLWf(_r, _f01, _v01)			PE_FN_CHIP_FLWf(PE_CVB, H13, _r, _f01, _v01)
#define PE_CVB_H13_WfCM(_r, _f, _c, _m)			PE_FN_CHIP_WfCM(PE_CVB, H13, _r, _f, _c, _m)
#define PE_CVB_H13_FLCM(_r, _f, _c, _m)			PE_FN_CHIP_FLCM(PE_CVB, H13, _r, _f, _c, _m)

#define PE_CVA_H13B0_RdFL(_r)					PE_REG_PHYS_VER_RdFL(g##PE_CVA##_##H13, b0, _r)
#define PE_CVA_H13B0_WrFL(_r)					PE_REG_PHYS_VER_WrFL(g##PE_CVA##_##H13, b0, _r)
#define PE_CVA_H13B0_Rd(_r)						PE_REG_SHDW_VER_Rd32(g##PE_CVA##_##H13, b0, _r)
#define PE_CVA_H13B0_Wr(_r, _v)					PE_REG_SHDW_VER_Wr32(g##PE_CVA##_##H13, b0, _r, _v)
#define PE_CVA_H13B0_Rd01(_r, _f01, _v01)		PE_REG_SHDW_VER_Rd01(g##PE_CVA##_##H13, b0, _r, _f01, _v01)
#define PE_CVA_H13B0_Wr01(_r, _f01, _v01)		PE_REG_SHDW_VER_Wr01(g##PE_CVA##_##H13, b0, _r, _f01, _v01)
#define PE_CVA_H13B0_FLRf(_r, _f01, _v01)		PE_REG_PHYS_VER_FLRf(g##PE_CVA##_##H13, b0, _r, _f01, _v01)
#define PE_CVA_H13B0_FLWf(_r, _f01, _v01)		PE_REG_PHYS_VER_FLWf(g##PE_CVA##_##H13, b0, _r, _f01, _v01)
#define PE_CVA_H13B0_WfCM(_r, _f, _c, _m)		PE_REG_SHDW_VER_WfCM(g##PE_CVA##_##H13, b0, _r, _f, _c, _m)
#define PE_CVA_H13B0_FLCM(_r, _f, _c, _m)		PE_REG_PHYS_VER_FLCM(g##PE_CVA##_##H13, b0, _r, _f, _c, _m)

#define PE_CVB_H13B0_RdFL(_r)					PE_REG_PHYS_VER_RdFL(g##PE_CVB##_##H13, b0, _r)
#define PE_CVB_H13B0_WrFL(_r)					PE_REG_PHYS_VER_WrFL(g##PE_CVB##_##H13, b0, _r)
#define PE_CVB_H13B0_Rd(_r)						PE_REG_SHDW_VER_Rd32(g##PE_CVB##_##H13, b0, _r)
#define PE_CVB_H13B0_Wr(_r, _v)					PE_REG_SHDW_VER_Wr32(g##PE_CVB##_##H13, b0, _r, _v)
#define PE_CVB_H13B0_Rd01(_r, _f01, _v01)		PE_REG_SHDW_VER_Rd01(g##PE_CVB##_##H13, b0, _r, _f01, _v01)
#define PE_CVB_H13B0_Wr01(_r, _f01, _v01)		PE_REG_SHDW_VER_Wr01(g##PE_CVB##_##H13, b0, _r, _f01, _v01)
#define PE_CVB_H13B0_FLRf(_r, _f01, _v01)		PE_REG_PHYS_VER_FLRf(g##PE_CVB##_##H13, b0, _r, _f01, _v01)
#define PE_CVB_H13B0_FLWf(_r, _f01, _v01)		PE_REG_PHYS_VER_FLWf(g##PE_CVB##_##H13, b0, _r, _f01, _v01)
#define PE_CVB_H13B0_WfCM(_r, _f, _c, _m)		PE_REG_SHDW_VER_WfCM(g##PE_CVB##_##H13, b0, _r, _f, _c, _m)
#define PE_CVB_H13B0_FLCM(_r, _f, _c, _m)		PE_REG_PHYS_VER_FLCM(g##PE_CVB##_##H13, b0, _r, _f, _c, _m)

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_CVA_REG_H13A0_T *a0;
		PE_CVA_REG_H13A0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CVA_REG_H13A0_T *a0;
		volatile PE_CVA_REG_H13A0_T *b0;
	} phys;
} PE_CVA_REG_H13_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CVB_REG_H13A0_T *a0;
		PE_CVB_REG_H13A0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CVB_REG_H13A0_T *a0;
		volatile PE_CVB_REG_H13A0_T *b0;
	} phys;
} PE_CVB_REG_H13_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CVA_REG_H13B0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CVA_REG_H13B0_T *b0;
	} phys;
} PE_CVA_REG_H13B_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_CVB_REG_H13B0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_CVB_REG_H13B0_T *b0;
	} phys;
} PE_CVB_REG_H13B_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_CVI_REG_H13_H_ */

