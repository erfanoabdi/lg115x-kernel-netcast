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


/** @file pe_mif_reg_l9.h
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2011.02.16
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef _PE_MIF_REG_L9_H_
#define _PE_MIF_REG_L9_H_
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_mif_reg_l9a0.h"
#include "pe_mif_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_MIA_L9_RdFL(_r)                  		PE_FN_CHIP_RdFL(PE_MIA, L9, _r)
#define PE_MIA_L9_WrFL(_r)                  		PE_FN_CHIP_WrFL(PE_MIA, L9, _r)
#define PE_MIA_L9_Rd(_r)                    		PE_FN_CHIP_Rd32(PE_MIA, L9, _r)
#define PE_MIA_L9_Wr(_r, _v)                		PE_FN_CHIP_Wr32(PE_MIA, L9, _r, _v)
#define PE_MIA_L9_Rd01(_r, _f01, _v01)      		PE_FN_CHIP_Rd01(PE_MIA, L9, _r, _f01, _v01)
#define PE_MIA_L9_Wr01(_r, _f01, _v01)      		PE_FN_CHIP_Wr01(PE_MIA, L9, _r, _f01, _v01)
#define PE_MIA_L9_WfCM(_r, _f, _c, _m)      		PE_FN_CHIP_WfCM(PE_MIA, L9, _r, _f, _c, _m)
#define PE_MIA_L9_WfCV(_r, _f, _c, _v1, _v2)        PE_FN_CHIP_WfCV(PE_MIA, L9, _r, _f, _c, _v1, _v2)
#define PE_MIA_L9_FLRd(_r, _v)              		PE_FN_CHIP_FLRd(PE_MIA, L9, _r, _v)
#define PE_MIA_L9_FLWr(_r, _v)              		PE_FN_CHIP_FLWr(PE_MIA, L9, _r, _v)
#define PE_MIA_L9_FLRf(_r, _f01, _v01)      		PE_FN_CHIP_FLRf(PE_MIA, L9, _r, _f01, _v01)
#define PE_MIA_L9_FLWf(_r, _f01, _v01)      		PE_FN_CHIP_FLWf(PE_MIA, L9, _r, _f01, _v01)
#define PE_MIA_L9_FLCM(_r, _f, _c, _m)      		PE_FN_CHIP_FLCM(PE_MIA, L9, _r, _f, _c, _m)
#define PE_MIA_L9_FLCV(_r, _f, _c, _v1, _v2)    	PE_FN_CHIP_FLCV(PE_MIA, L9, _r, _f, _c, _v1, _v2)

#define PE_MIB_L9_RdFL(_r)                  		PE_FN_CHIP_RdFL(PE_MIB, L9, _r)
#define PE_MIB_L9_WrFL(_r)                  		PE_FN_CHIP_WrFL(PE_MIB, L9, _r)
#define PE_MIB_L9_Rd(_r)                    		PE_FN_CHIP_Rd32(PE_MIB, L9, _r)
#define PE_MIB_L9_Wr(_r, _v)                		PE_FN_CHIP_Wr32(PE_MIB, L9, _r, _v)
#define PE_MIB_L9_Rd01(_r, _f01, _v01)      		PE_FN_CHIP_Rd01(PE_MIB, L9, _r, _f01, _v01)
#define PE_MIB_L9_Wr01(_r, _f01, _v01)      		PE_FN_CHIP_Wr01(PE_MIB, L9, _r, _f01, _v01)
#define PE_MIB_L9_WfCM(_r, _f, _c, _m)      		PE_FN_CHIP_WfCM(PE_MIB, L9, _r, _f, _c, _m)
#define PE_MIB_L9_WfCV(_r, _f, _c, _v1, _v2)        PE_FN_CHIP_WfCV(PE_MIB, L9, _r, _f, _c, _v1, _v2)
#define PE_MIB_L9_FLRd(_r, _v)              		PE_FN_CHIP_FLRd(PE_MIB, L9, _r, _v)
#define PE_MIB_L9_FLWr(_r, _v)              		PE_FN_CHIP_FLWr(PE_MIB, L9, _r, _v)
#define PE_MIB_L9_FLRf(_r, _f01, _v01)      		PE_FN_CHIP_FLRf(PE_MIB, L9, _r, _f01, _v01)
#define PE_MIB_L9_FLWf(_r, _f01, _v01)      		PE_FN_CHIP_FLWf(PE_MIB, L9, _r, _f01, _v01)
#define PE_MIB_L9_FLCM(_r, _f, _c, _m)      		PE_FN_CHIP_FLCM(PE_MIB, L9, _r, _f, _c, _m)
#define PE_MIB_L9_FLCV(_r, _f, _c, _v1, _v2)    	PE_FN_CHIP_FLCV(PE_MIB, L9, _r, _f, _c, _v1, _v2)

#define PE_MIC_L9_RdFL(_r)                  		PE_FN_CHIP_RdFL(PE_MIC, L9, _r)
#define PE_MIC_L9_WrFL(_r)                  		PE_FN_CHIP_WrFL(PE_MIC, L9, _r)
#define PE_MIC_L9_Rd(_r)                    		PE_FN_CHIP_Rd32(PE_MIC, L9, _r)
#define PE_MIC_L9_Wr(_r, _v)                		PE_FN_CHIP_Wr32(PE_MIC, L9, _r, _v)
#define PE_MIC_L9_Rd01(_r, _f01, _v01)      		PE_FN_CHIP_Rd01(PE_MIC, L9, _r, _f01, _v01)
#define PE_MIC_L9_Wr01(_r, _f01, _v01)      		PE_FN_CHIP_Wr01(PE_MIC, L9, _r, _f01, _v01)
#define PE_MIC_L9_WfCM(_r, _f, _c, _m)      		PE_FN_CHIP_WfCM(PE_MIC, L9, _r, _f, _c, _m)
#define PE_MIC_L9_WfCV(_r, _f, _c, _v1, _v2)        PE_FN_CHIP_WfCV(PE_MIC, L9, _r, _f, _c, _v1, _v2)
#define PE_MIC_L9_FLRd(_r, _v)              		PE_FN_CHIP_FLRd(PE_MIC, L9, _r, _v)
#define PE_MIC_L9_FLWr(_r, _v)              		PE_FN_CHIP_FLWr(PE_MIC, L9, _r, _v)
#define PE_MIC_L9_FLRf(_r, _f01, _v01)      		PE_FN_CHIP_FLRf(PE_MIC, L9, _r, _f01, _v01)
#define PE_MIC_L9_FLWf(_r, _f01, _v01)      		PE_FN_CHIP_FLWf(PE_MIC, L9, _r, _f01, _v01)
#define PE_MIC_L9_FLCM(_r, _f, _c, _m)      		PE_FN_CHIP_FLCM(PE_MIC, L9, _r, _f, _c, _m)
#define PE_MIC_L9_FLCV(_r, _f, _c, _v1, _v2)    	PE_FN_CHIP_FLCV(PE_MIC, L9, _r, _f, _c, _v1, _v2)

#define PE_MID_L9_RdFL(_r)                  		PE_FN_CHIP_RdFL(PE_MID, L9, _r)
#define PE_MID_L9_WrFL(_r)                  		PE_FN_CHIP_WrFL(PE_MID, L9, _r)
#define PE_MID_L9_Rd(_r)                    		PE_FN_CHIP_Rd32(PE_MID, L9, _r)
#define PE_MID_L9_Wr(_r, _v)                		PE_FN_CHIP_Wr32(PE_MID, L9, _r, _v)
#define PE_MID_L9_Rd01(_r, _f01, _v01)      		PE_FN_CHIP_Rd01(PE_MID, L9, _r, _f01, _v01)
#define PE_MID_L9_Wr01(_r, _f01, _v01)      		PE_FN_CHIP_Wr01(PE_MID, L9, _r, _f01, _v01)
#define PE_MID_L9_WfCM(_r, _f, _c, _m)      		PE_FN_CHIP_WfCM(PE_MID, L9, _r, _f, _c, _m)
#define PE_MID_L9_WfCV(_r, _f, _c, _v1, _v2)        PE_FN_CHIP_WfCV(PE_MID, L9, _r, _f, _c, _v1, _v2)
#define PE_MID_L9_FLRd(_r, _v)              		PE_FN_CHIP_FLRd(PE_MID, L9, _r, _v)
#define PE_MID_L9_FLWr(_r, _v)              		PE_FN_CHIP_FLWr(PE_MID, L9, _r, _v)
#define PE_MID_L9_FLRf(_r, _f01, _v01)      		PE_FN_CHIP_FLRf(PE_MID, L9, _r, _f01, _v01)
#define PE_MID_L9_FLWf(_r, _f01, _v01)      		PE_FN_CHIP_FLWf(PE_MID, L9, _r, _f01, _v01)
#define PE_MID_L9_FLCM(_r, _f, _c, _m)      		PE_FN_CHIP_FLCM(PE_MID, L9, _r, _f, _c, _m)
#define PE_MID_L9_FLCV(_r, _f, _c, _v1, _v2)    	PE_FN_CHIP_FLCV(PE_MID, L9, _r, _f, _c, _v1, _v2)

#define PE_MIF_L9_RdFL(_r)                  		PE_FN_CHIP_RdFL(PE_MIF, L9, _r)
#define PE_MIF_L9_WrFL(_r)                  		PE_FN_CHIP_WrFL(PE_MIF, L9, _r)
#define PE_MIF_L9_Rd(_r)                    		PE_FN_CHIP_Rd32(PE_MIF, L9, _r)
#define PE_MIF_L9_Wr(_r, _v)                		PE_FN_CHIP_Wr32(PE_MIF, L9, _r, _v)
#define PE_MIF_L9_Rd01(_r, _f01, _v01)      		PE_FN_CHIP_Rd01(PE_MIF, L9, _r, _f01, _v01)
#define PE_MIF_L9_Wr01(_r, _f01, _v01)      		PE_FN_CHIP_Wr01(PE_MIF, L9, _r, _f01, _v01)
#define PE_MIF_L9_WfCM(_r, _f, _c, _m)      		PE_FN_CHIP_WfCM(PE_MIF, L9, _r, _f, _c, _m)
#define PE_MIF_L9_WfCV(_r, _f, _c, _v1, _v2)        PE_FN_CHIP_WfCV(PE_MIF, L9, _r, _f, _c, _v1, _v2)
#define PE_MIF_L9_FLRd(_r, _v)              		PE_FN_CHIP_FLRd(PE_MIF, L9, _r, _v)
#define PE_MIF_L9_FLWr(_r, _v)              		PE_FN_CHIP_FLWr(PE_MIF, L9, _r, _v)
#define PE_MIF_L9_FLRf(_r, _f01, _v01)      		PE_FN_CHIP_FLRf(PE_MIF, L9, _r, _f01, _v01)
#define PE_MIF_L9_FLWf(_r, _f01, _v01)      		PE_FN_CHIP_FLWf(PE_MIF, L9, _r, _f01, _v01)
#define PE_MIF_L9_FLCM(_r, _f, _c, _m)      		PE_FN_CHIP_FLCM(PE_MIF, L9, _r, _f, _c, _m)
#define PE_MIF_L9_FLCV(_r, _f, _c, _v1, _v2)    	PE_FN_CHIP_FLCV(PE_MIF, L9, _r, _f, _c, _v1, _v2)

#define PE_MIA_L9B0_RdFL(_r)                        PE_REG_PHYS_VER_RdFL(g##PE_MIA##_##L9, b0, _r)
#define PE_MIA_L9B0_WrFL(_r)                        PE_REG_PHYS_VER_WrFL(g##PE_MIA##_##L9, b0, _r)
#define PE_MIA_L9B0_Rd(_r)                          PE_REG_SHDW_VER_Rd32(g##PE_MIA##_##L9, b0, _r)
#define PE_MIA_L9B0_Wr(_r, _v)                      PE_REG_SHDW_VER_Wr32(g##PE_MIA##_##L9, b0, _r, _v)
#define PE_MIA_L9B0_Rd01(_r, _f01, _v01)            PE_REG_SHDW_VER_Rd01(g##PE_MIA##_##L9, b0, _r, _f01, _v01)
#define PE_MIA_L9B0_Wr01(_r, _f01, _v01)            PE_REG_SHDW_VER_Wr01(g##PE_MIA##_##L9, b0, _r, _f01, _v01)
#define PE_MIA_L9B0_WfCM(_r, _f, _c, _m)            PE_REG_SHDW_VER_WfCM(g##PE_MIA##_##L9, b0, _r, _f, _c, _m)
#define PE_MIA_L9B0_WfCV(_r, _f, _c, _v1, _v2)      PE_REG_SHDW_VER_WfCV(g##PE_MIA##_##L9, b0, _r, _f, _c, _v1, _v2)

#define PE_MIB_L9B0_RdFL(_r)                        PE_REG_PHYS_VER_RdFL(g##PE_MIB##_##L9, b0, _r)
#define PE_MIB_L9B0_WrFL(_r)                        PE_REG_PHYS_VER_WrFL(g##PE_MIB##_##L9, b0, _r)
#define PE_MIB_L9B0_Rd(_r)                          PE_REG_SHDW_VER_Rd32(g##PE_MIB##_##L9, b0, _r)
#define PE_MIB_L9B0_Wr(_r, _v)                      PE_REG_SHDW_VER_Wr32(g##PE_MIB##_##L9, b0, _r, _v)
#define PE_MIB_L9B0_Rd01(_r, _f01, _v01)            PE_REG_SHDW_VER_Rd01(g##PE_MIB##_##L9, b0, _r, _f01, _v01)
#define PE_MIB_L9B0_Wr01(_r, _f01, _v01)            PE_REG_SHDW_VER_Wr01(g##PE_MIB##_##L9, b0, _r, _f01, _v01)
#define PE_MIB_L9B0_WfCM(_r, _f, _c, _m)            PE_REG_SHDW_VER_WfCM(g##PE_MIB##_##L9, b0, _r, _f, _c, _m)
#define PE_MIB_L9B0_WfCV(_r, _f, _c, _v1, _v2)      PE_REG_SHDW_VER_WfCV(g##PE_MIB##_##L9, b0, _r, _f, _c, _v1, _v2)

#define PE_MIC_L9B0_RdFL(_r)                        PE_REG_PHYS_VER_RdFL(g##PE_MIC##_##L9, b0, _r)
#define PE_MIC_L9B0_WrFL(_r)                        PE_REG_PHYS_VER_WrFL(g##PE_MIC##_##L9, b0, _r)
#define PE_MIC_L9B0_Rd(_r)                          PE_REG_SHDW_VER_Rd32(g##PE_MIC##_##L9, b0, _r)
#define PE_MIC_L9B0_Wr(_r, _v)                      PE_REG_SHDW_VER_Wr32(g##PE_MIC##_##L9, b0, _r, _v)
#define PE_MIC_L9B0_Rd01(_r, _f01, _v01)            PE_REG_SHDW_VER_Rd01(g##PE_MIC##_##L9, b0, _r, _f01, _v01)
#define PE_MIC_L9B0_Wr01(_r, _f01, _v01)            PE_REG_SHDW_VER_Wr01(g##PE_MIC##_##L9, b0, _r, _f01, _v01)
#define PE_MIC_L9B0_WfCM(_r, _f, _c, _m)            PE_REG_SHDW_VER_WfCM(g##PE_MIC##_##L9, b0, _r, _f, _c, _m)
#define PE_MIC_L9B0_WfCV(_r, _f, _c, _v1, _v2)      PE_REG_SHDW_VER_WfCV(g##PE_MIC##_##L9, b0, _r, _f, _c, _v1, _v2)

#define PE_MID_L9B0_RdFL(_r)                        PE_REG_PHYS_VER_RdFL(g##PE_MID##_##L9, b0, _r)
#define PE_MID_L9B0_WrFL(_r)                        PE_REG_PHYS_VER_WrFL(g##PE_MID##_##L9, b0, _r)
#define PE_MID_L9B0_Rd(_r)                          PE_REG_SHDW_VER_Rd32(g##PE_MID##_##L9, b0, _r)
#define PE_MID_L9B0_Wr(_r, _v)                      PE_REG_SHDW_VER_Wr32(g##PE_MID##_##L9, b0, _r, _v)
#define PE_MID_L9B0_Rd01(_r, _f01, _v01)            PE_REG_SHDW_VER_Rd01(g##PE_MID##_##L9, b0, _r, _f01, _v01)
#define PE_MID_L9B0_Wr01(_r, _f01, _v01)            PE_REG_SHDW_VER_Wr01(g##PE_MID##_##L9, b0, _r, _f01, _v01)
#define PE_MID_L9B0_WfCM(_r, _f, _c, _m)            PE_REG_SHDW_VER_WfCM(g##PE_MID##_##L9, b0, _r, _f, _c, _m)
#define PE_MID_L9B0_WfCV(_r, _f, _c, _v1, _v2)      PE_REG_SHDW_VER_WfCV(g##PE_MID##_##L9, b0, _r, _f, _c, _v1, _v2)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        PE_MIA_REG_L9A0_T *a0;
		PE_MIA_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_MIA_REG_L9A0_T *a0;
		volatile PE_MIA_REG_L9B0_T *b0;
    } phys;
} PE_MIA_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_MIB_REG_L9A0_T *a0;
		PE_MIB_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_MIB_REG_L9A0_T *a0;
		volatile PE_MIB_REG_L9B0_T *b0;
    } phys;
} PE_MIB_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_MIC_REG_L9A0_T *a0;
		PE_MIC_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_MIC_REG_L9A0_T *a0;
		volatile PE_MIC_REG_L9B0_T *b0;
    } phys;
} PE_MIC_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_MID_REG_L9A0_T *a0;
		PE_MID_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_MID_REG_L9A0_T *a0;
		volatile PE_MID_REG_L9B0_T *b0;
    } phys;
} PE_MID_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_MIF_REG_L9B0_T *a0;
		PE_MIF_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_MIF_REG_L9B0_T *a0;
		volatile PE_MIF_REG_L9B0_T *b0;
    } phys;
} PE_MIF_REG_L9_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* _PE_MIF_REG_L9_H_ */

