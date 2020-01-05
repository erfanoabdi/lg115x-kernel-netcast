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


/** @file pe_msc_reg_h13.h
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
#ifndef _PE_MSC_REG_H13_H_
#define _PE_MSC_REG_H13_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_msc_reg_h13a0.h"
#include "pe_msc_reg_h13b0.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_MSL_H13_RdFL(_r)								PE_FN_CHIP_RdFL(PE_MSL, H13, _r)
#define PE_MSL_H13_WrFL(_r)								PE_FN_CHIP_WrFL(PE_MSL, H13, _r)
#define PE_MSL_H13_Rd(_r)								PE_FN_CHIP_Rd32(PE_MSL, H13, _r)
#define PE_MSL_H13_Wr(_r, _v)							PE_FN_CHIP_Wr32(PE_MSL, H13, _r, _v)
#define PE_MSL_H13_Rd01(_r, _f01, _v01)					PE_FN_CHIP_Rd01(PE_MSL, H13, _r, _f01, _v01)
#define PE_MSL_H13_Wr01(_r, _f01, _v01)					PE_FN_CHIP_Wr01(PE_MSL, H13, _r, _f01, _v01)
#define PE_MSL_H13_WfCM(_r, _f, _c, _m)					PE_FN_CHIP_WfCM(PE_MSL, H13, _r, _f, _c, _m)
#define PE_MSL_H13_FLRd(_r, _v)							PE_FN_CHIP_FLRd(PE_MSL, H13, _r, _v)
#define PE_MSL_H13_FLWr(_r, _v)							PE_FN_CHIP_FLWr(PE_MSL, H13, _r, _v)
#define PE_MSL_H13_FLRf(_r, _f01, _v01)					PE_FN_CHIP_FLRf(PE_MSL, H13, _r, _f01, _v01)
#define PE_MSL_H13_FLWf(_r, _f01, _v01)					PE_FN_CHIP_FLWf(PE_MSL, H13, _r, _f01, _v01)

#define PE_MSR_H13_RdFL(_r)								PE_FN_CHIP_RdFL(PE_MSR, H13, _r)
#define PE_MSR_H13_WrFL(_r)								PE_FN_CHIP_WrFL(PE_MSR, H13, _r)
#define PE_MSR_H13_Rd(_r)								PE_FN_CHIP_Rd32(PE_MSR, H13, _r)
#define PE_MSR_H13_Wr(_r, _v)							PE_FN_CHIP_Wr32(PE_MSR, H13, _r, _v)
#define PE_MSR_H13_Rd01(_r, _f01, _v01)					PE_FN_CHIP_Rd01(PE_MSR, H13, _r, _f01, _v01)
#define PE_MSR_H13_Wr01(_r, _f01, _v01)					PE_FN_CHIP_Wr01(PE_MSR, H13, _r, _f01, _v01)
#define PE_MSR_H13_WfCM(_r, _f, _c, _m)					PE_FN_CHIP_WfCM(PE_MSR, H13, _r, _f, _c, _m)
#define PE_MSR_H13_FLRd(_r, _v)							PE_FN_CHIP_FLRd(PE_MSR, H13, _r, _v)
#define PE_MSR_H13_FLWr(_r, _v)							PE_FN_CHIP_FLWr(PE_MSR, H13, _r, _v)
#define PE_MSR_H13_FLRf(_r, _f01, _v01)					PE_FN_CHIP_FLRf(PE_MSR, H13, _r, _f01, _v01)
#define PE_MSR_H13_FLWf(_r, _f01, _v01)					PE_FN_CHIP_FLWf(PE_MSR, H13, _r, _f01, _v01)

#define PE_MSL_H13B0_RdFL(_r)							PE_REG_PHYS_VER_RdFL(g##PE_MSL##_##H13, b0, _r)
#define PE_MSL_H13B0_WrFL(_r)							PE_REG_PHYS_VER_WrFL(g##PE_MSL##_##H13, b0, _r)
#define PE_MSL_H13B0_Rd(_r)								PE_REG_SHDW_VER_Rd32(g##PE_MSL##_##H13, b0, _r)
#define PE_MSL_H13B0_Wr(_r, _v)							PE_REG_SHDW_VER_Wr32(g##PE_MSL##_##H13, b0, _r, _v)
#define PE_MSL_H13B0_Rd01(_r, _f01, _v01)				PE_REG_SHDW_VER_Rd01(g##PE_MSL##_##H13, b0, _r, _f01, _v01)
#define PE_MSL_H13B0_Wr01(_r, _f01, _v01)				PE_REG_SHDW_VER_Wr01(g##PE_MSL##_##H13, b0, _r, _f01, _v01)
#define PE_MSL_H13B0_FLRf(_r, _f01, _v01)				PE_REG_PHYS_VER_FLRf(g##PE_MSL##_##H13, b0, _r, _f01, _v01)
#define PE_MSL_H13B0_FLWf(_r, _f01, _v01)				PE_REG_PHYS_VER_FLWf(g##PE_MSL##_##H13, b0, _r, _f01, _v01)
#define PE_MSL_H13B0_WfCM(_r, _f, _c, _m)				PE_REG_SHDW_VER_WfCM(g##PE_MSL##_##H13, b0, _r, _f, _c, _m)
#define PE_MSL_H13B0_FLCM(_r, _f, _c, _m)				PE_REG_PHYS_VER_FLCM(g##PE_MSL##_##H13, b0, _r, _f, _c, _m)
#define PE_MSL_H13B0_WfCV(_r, _f, _c, _v1, _v2)			PE_REG_SHDW_VER_WfCV(g##PE_MSL##_##H13, b0, _r, _f, _c, _v1, _v2)
#define PE_MSL_H13B0_FLRd(_r, _v)						PE_REG_PHYS_VER_FLRd(g##PE_MSL##_##H13, b0, _r, _v)
#define PE_MSL_H13B0_FLWr(_r, _v)						PE_REG_PHYS_VER_FLWr(g##PE_MSL##_##H13, b0, _r, _v)
#define PE_MSL_H13B0_FLCV(_r, _f, _c, _v1, _v2)			PE_REG_PHYS_VER_FLCV(g##PE_MSL##_##H13, b0, _r, _f, _c, _v1, _v2)

#define PE_MSR_H13B0_RdFL(_r)							PE_REG_PHYS_VER_RdFL(g##PE_MSR##_##H13, b0, _r)
#define PE_MSR_H13B0_WrFL(_r)							PE_REG_PHYS_VER_WrFL(g##PE_MSR##_##H13, b0, _r)
#define PE_MSR_H13B0_Rd(_r)								PE_REG_SHDW_VER_Rd32(g##PE_MSR##_##H13, b0, _r)
#define PE_MSR_H13B0_Wr(_r, _v)							PE_REG_SHDW_VER_Wr32(g##PE_MSR##_##H13, b0, _r, _v)
#define PE_MSR_H13B0_Rd01(_r, _f01, _v01)				PE_REG_SHDW_VER_Rd01(g##PE_MSR##_##H13, b0, _r, _f01, _v01)
#define PE_MSR_H13B0_Wr01(_r, _f01, _v01)				PE_REG_SHDW_VER_Wr01(g##PE_MSR##_##H13, b0, _r, _f01, _v01)
#define PE_MSR_H13B0_FLRf(_r, _f01, _v01)				PE_REG_PHYS_VER_FLRf(g##PE_MSR##_##H13, b0, _r, _f01, _v01)
#define PE_MSR_H13B0_FLWf(_r, _f01, _v01)				PE_REG_PHYS_VER_FLWf(g##PE_MSR##_##H13, b0, _r, _f01, _v01)
#define PE_MSR_H13B0_WfCM(_r, _f, _c, _m)				PE_REG_SHDW_VER_WfCM(g##PE_MSR##_##H13, b0, _r, _f, _c, _m)
#define PE_MSR_H13B0_FLCM(_r, _f, _c, _m)				PE_REG_PHYS_VER_FLCM(g##PE_MSR##_##H13, b0, _r, _f, _c, _m)
#define PE_MSR_H13B0_WfCV(_r, _f, _c, _v1, _v2)			PE_REG_SHDW_VER_WfCV(g##PE_MSR##_##H13, b0, _r, _f, _c, _v1, _v2)
#define PE_MSR_H13B0_FLRd(_r, _v)						PE_REG_PHYS_VER_FLRd(g##PE_MSR##_##H13, b0, _r, _v)
#define PE_MSR_H13B0_FLWr(_r, _v)						PE_REG_PHYS_VER_FLWr(g##PE_MSR##_##H13, b0, _r, _v)
#define PE_MSR_H13B0_FLCV(_r, _f, _c, _v1, _v2)			PE_REG_PHYS_VER_FLCV(g##PE_MSR##_##H13, b0, _r, _f, _c, _v1, _v2)

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_MSL_REG_H13A0_T *a0;
		PE_MSL_REG_H13A0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_MSL_REG_H13A0_T *a0;
		volatile PE_MSL_REG_H13A0_T *b0;
	} phys;
} PE_MSL_REG_H13_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_MSR_REG_H13A0_T *a0;
		PE_MSR_REG_H13A0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_MSR_REG_H13A0_T *a0;
		volatile PE_MSR_REG_H13A0_T *b0;
	} phys;
} PE_MSR_REG_H13_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_MSL_REG_H13B0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_MSL_REG_H13B0_T *b0;
	} phys;
} PE_MSL_REG_H13B_T;

typedef struct {
	union {
		UINT32			*addr;
		PE_MSR_REG_H13B0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_MSR_REG_H13B0_T *b0;
	} phys;
} PE_MSR_REG_H13B_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_MSC_REG_H13_H_ */

