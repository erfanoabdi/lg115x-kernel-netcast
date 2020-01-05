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
 * date       2011.02.16
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef  DE_MIF_REG_L9_INC
#define  DE_MIF_REG_L9_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "l9/de_reg_mac.h"
#include "l9/de_mif_reg_l9a0.h"
#include "l9/de_mif_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_MIA_L9_RdFL(_r)                  		FN_CHIP_RdFL(DE_MIA, L9, _r)
#define DE_MIA_L9_WrFL(_r)                  		FN_CHIP_WrFL(DE_MIA, L9, _r)
#define DE_MIA_L9_Rd(_r)                    		FN_CHIP_Rd32(DE_MIA, L9, _r)
#define DE_MIA_L9_Wr(_r, _v)                		FN_CHIP_Wr32(DE_MIA, L9, _r, _v)
#define DE_MIA_L9_Rd01(_r, _f01, _v01)      		FN_CHIP_Rd01(DE_MIA, L9, _r, _f01, _v01)
#define DE_MIA_L9_Wr01(_r, _f01, _v01)      		FN_CHIP_Wr01(DE_MIA, L9, _r, _f01, _v01)
#define DE_MIA_L9_WfCM(_r, _f, _c, _m)      		FN_CHIP_WfCM(DE_MIA, L9, _r, _f, _c, _m)
#define DE_MIA_L9_WfCV(_r, _f, _c, _v1, _v2)        FN_CHIP_WfCV(DE_MIA, L9, _r, _f, _c, _v1, _v2)
#define DE_MIA_L9_FLRd(_r, _v)              		FN_CHIP_FLRd(DE_MIA, L9, _r, _v)
#define DE_MIA_L9_FLWr(_r, _v)              		FN_CHIP_FLWr(DE_MIA, L9, _r, _v)
#define DE_MIA_L9_FLRf(_r, _f01, _v01)      		FN_CHIP_FLRf(DE_MIA, L9, _r, _f01, _v01)
#define DE_MIA_L9_FLWf(_r, _f01, _v01)      		FN_CHIP_FLWf(DE_MIA, L9, _r, _f01, _v01)
#define DE_MIA_L9_FLCM(_r, _f, _c, _m)      		FN_CHIP_FLCM(DE_MIA, L9, _r, _f, _c, _m)
#define DE_MIA_L9_FLCV(_r, _f, _c, _v1, _v2)    	FN_CHIP_FLCV(DE_MIA, L9, _r, _f, _c, _v1, _v2)

#define DE_MIB_L9_RdFL(_r)                  		FN_CHIP_RdFL(DE_MIB, L9, _r)
#define DE_MIB_L9_WrFL(_r)                  		FN_CHIP_WrFL(DE_MIB, L9, _r)
#define DE_MIB_L9_Rd(_r)                    		FN_CHIP_Rd32(DE_MIB, L9, _r)
#define DE_MIB_L9_Wr(_r, _v)                		FN_CHIP_Wr32(DE_MIB, L9, _r, _v)
#define DE_MIB_L9_Rd01(_r, _f01, _v01)      		FN_CHIP_Rd01(DE_MIB, L9, _r, _f01, _v01)
#define DE_MIB_L9_Wr01(_r, _f01, _v01)      		FN_CHIP_Wr01(DE_MIB, L9, _r, _f01, _v01)
#define DE_MIB_L9_WfCM(_r, _f, _c, _m)      		FN_CHIP_WfCM(DE_MIB, L9, _r, _f, _c, _m)
#define DE_MIB_L9_WfCV(_r, _f, _c, _v1, _v2)        FN_CHIP_WfCV(DE_MIB, L9, _r, _f, _c, _v1, _v2)
#define DE_MIB_L9_FLRd(_r, _v)              		FN_CHIP_FLRd(DE_MIB, L9, _r, _v)
#define DE_MIB_L9_FLWr(_r, _v)              		FN_CHIP_FLWr(DE_MIB, L9, _r, _v)
#define DE_MIB_L9_FLRf(_r, _f01, _v01)      		FN_CHIP_FLRf(DE_MIB, L9, _r, _f01, _v01)
#define DE_MIB_L9_FLWf(_r, _f01, _v01)      		FN_CHIP_FLWf(DE_MIB, L9, _r, _f01, _v01)
#define DE_MIB_L9_FLCM(_r, _f, _c, _m)      		FN_CHIP_FLCM(DE_MIB, L9, _r, _f, _c, _m)
#define DE_MIB_L9_FLCV(_r, _f, _c, _v1, _v2)    	FN_CHIP_FLCV(DE_MIB, L9, _r, _f, _c, _v1, _v2)

#define DE_MIC_L9_RdFL(_r)                  		FN_CHIP_RdFL(DE_MIC, L9, _r)
#define DE_MIC_L9_WrFL(_r)                  		FN_CHIP_WrFL(DE_MIC, L9, _r)
#define DE_MIC_L9_Rd(_r)                    		FN_CHIP_Rd32(DE_MIC, L9, _r)
#define DE_MIC_L9_Wr(_r, _v)                		FN_CHIP_Wr32(DE_MIC, L9, _r, _v)
#define DE_MIC_L9_Rd01(_r, _f01, _v01)      		FN_CHIP_Rd01(DE_MIC, L9, _r, _f01, _v01)
#define DE_MIC_L9_Wr01(_r, _f01, _v01)      		FN_CHIP_Wr01(DE_MIC, L9, _r, _f01, _v01)
#define DE_MIC_L9_WfCM(_r, _f, _c, _m)      		FN_CHIP_WfCM(DE_MIC, L9, _r, _f, _c, _m)
#define DE_MIC_L9_WfCV(_r, _f, _c, _v1, _v2)        FN_CHIP_WfCV(DE_MIC, L9, _r, _f, _c, _v1, _v2)
#define DE_MIC_L9_FLRd(_r, _v)              		FN_CHIP_FLRd(DE_MIC, L9, _r, _v)
#define DE_MIC_L9_FLWr(_r, _v)              		FN_CHIP_FLWr(DE_MIC, L9, _r, _v)
#define DE_MIC_L9_FLRf(_r, _f01, _v01)      		FN_CHIP_FLRf(DE_MIC, L9, _r, _f01, _v01)
#define DE_MIC_L9_FLWf(_r, _f01, _v01)      		FN_CHIP_FLWf(DE_MIC, L9, _r, _f01, _v01)
#define DE_MIC_L9_FLCM(_r, _f, _c, _m)      		FN_CHIP_FLCM(DE_MIC, L9, _r, _f, _c, _m)
#define DE_MIC_L9_FLCV(_r, _f, _c, _v1, _v2)    	FN_CHIP_FLCV(DE_MIC, L9, _r, _f, _c, _v1, _v2)

#define DE_MID_L9_RdFL(_r)                  		FN_CHIP_RdFL(DE_MID, L9, _r)
#define DE_MID_L9_WrFL(_r)                  		FN_CHIP_WrFL(DE_MID, L9, _r)
#define DE_MID_L9_Rd(_r)                    		FN_CHIP_Rd32(DE_MID, L9, _r)
#define DE_MID_L9_Wr(_r, _v)                		FN_CHIP_Wr32(DE_MID, L9, _r, _v)
#define DE_MID_L9_Rd01(_r, _f01, _v01)      		FN_CHIP_Rd01(DE_MID, L9, _r, _f01, _v01)
#define DE_MID_L9_Wr01(_r, _f01, _v01)      		FN_CHIP_Wr01(DE_MID, L9, _r, _f01, _v01)
#define DE_MID_L9_WfCM(_r, _f, _c, _m)      		FN_CHIP_WfCM(DE_MID, L9, _r, _f, _c, _m)
#define DE_MID_L9_WfCV(_r, _f, _c, _v1, _v2)        FN_CHIP_WfCV(DE_MID, L9, _r, _f, _c, _v1, _v2)
#define DE_MID_L9_FLRd(_r, _v)              		FN_CHIP_FLRd(DE_MID, L9, _r, _v)
#define DE_MID_L9_FLWr(_r, _v)              		FN_CHIP_FLWr(DE_MID, L9, _r, _v)
#define DE_MID_L9_FLRf(_r, _f01, _v01)      		FN_CHIP_FLRf(DE_MID, L9, _r, _f01, _v01)
#define DE_MID_L9_FLWf(_r, _f01, _v01)      		FN_CHIP_FLWf(DE_MID, L9, _r, _f01, _v01)
#define DE_MID_L9_FLCM(_r, _f, _c, _m)      		FN_CHIP_FLCM(DE_MID, L9, _r, _f, _c, _m)
#define DE_MID_L9_FLCV(_r, _f, _c, _v1, _v2)    	FN_CHIP_FLCV(DE_MID, L9, _r, _f, _c, _v1, _v2)

#define DE_MIF_L9_RdFL(_r)                  		FN_CHIP_RdFL(DE_MIF, L9, _r)
#define DE_MIF_L9_WrFL(_r)                  		FN_CHIP_WrFL(DE_MIF, L9, _r)
#define DE_MIF_L9_Rd(_r)                    		FN_CHIP_Rd32(DE_MIF, L9, _r)
#define DE_MIF_L9_Wr(_r, _v)                		FN_CHIP_Wr32(DE_MIF, L9, _r, _v)
#define DE_MIF_L9_Rd01(_r, _f01, _v01)      		FN_CHIP_Rd01(DE_MIF, L9, _r, _f01, _v01)
#define DE_MIF_L9_Wr01(_r, _f01, _v01)      		FN_CHIP_Wr01(DE_MIF, L9, _r, _f01, _v01)
#define DE_MIF_L9_WfCM(_r, _f, _c, _m)      		FN_CHIP_WfCM(DE_MIF, L9, _r, _f, _c, _m)
#define DE_MIF_L9_WfCV(_r, _f, _c, _v1, _v2)        FN_CHIP_WfCV(DE_MIF, L9, _r, _f, _c, _v1, _v2)
#define DE_MIF_L9_FLRd(_r, _v)              		FN_CHIP_FLRd(DE_MIF, L9, _r, _v)
#define DE_MIF_L9_FLWr(_r, _v)              		FN_CHIP_FLWr(DE_MIF, L9, _r, _v)
#define DE_MIF_L9_FLRf(_r, _f01, _v01)      		FN_CHIP_FLRf(DE_MIF, L9, _r, _f01, _v01)
#define DE_MIF_L9_FLWf(_r, _f01, _v01)      		FN_CHIP_FLWf(DE_MIF, L9, _r, _f01, _v01)
#define DE_MIF_L9_FLCM(_r, _f, _c, _m)      		FN_CHIP_FLCM(DE_MIF, L9, _r, _f, _c, _m)
#define DE_MIF_L9_FLCV(_r, _f, _c, _v1, _v2)    	FN_CHIP_FLCV(DE_MIF, L9, _r, _f, _c, _v1, _v2)

#define DE_MIA_L9B0_RdFL(_r)                        REG_PHYS_VER_RdFL(g##DE_MIA##_##L9, b0, _r)
#define DE_MIA_L9B0_WrFL(_r)                        REG_PHYS_VER_WrFL(g##DE_MIA##_##L9, b0, _r)
#define DE_MIA_L9B0_Rd(_r)                          REG_SHDW_VER_Rd32(g##DE_MIA##_##L9, b0, _r)
#define DE_MIA_L9B0_Wr(_r, _v)                      REG_SHDW_VER_Wr32(g##DE_MIA##_##L9, b0, _r, _v)
#define DE_MIA_L9B0_Rd01(_r, _f01, _v01)            REG_SHDW_VER_Rd01(g##DE_MIA##_##L9, b0, _r, _f01, _v01)
#define DE_MIA_L9B0_Wr01(_r, _f01, _v01)            REG_SHDW_VER_Wr01(g##DE_MIA##_##L9, b0, _r, _f01, _v01)
#define DE_MIA_L9B0_WfCM(_r, _f, _c, _m)            REG_SHDW_VER_WfCM(g##DE_MIA##_##L9, b0, _r, _f, _c, _m)
#define DE_MIA_L9B0_WfCV(_r, _f, _c, _v1, _v2)      REG_SHDW_VER_WfCV(g##DE_MIA##_##L9, b0, _r, _f, _c, _v1, _v2)

#define DE_MIB_L9B0_RdFL(_r)                        REG_PHYS_VER_RdFL(g##DE_MIB##_##L9, b0, _r)
#define DE_MIB_L9B0_WrFL(_r)                        REG_PHYS_VER_WrFL(g##DE_MIB##_##L9, b0, _r)
#define DE_MIB_L9B0_Rd(_r)                          REG_SHDW_VER_Rd32(g##DE_MIB##_##L9, b0, _r)
#define DE_MIB_L9B0_Wr(_r, _v)                      REG_SHDW_VER_Wr32(g##DE_MIB##_##L9, b0, _r, _v)
#define DE_MIB_L9B0_Rd01(_r, _f01, _v01)            REG_SHDW_VER_Rd01(g##DE_MIB##_##L9, b0, _r, _f01, _v01)
#define DE_MIB_L9B0_Wr01(_r, _f01, _v01)            REG_SHDW_VER_Wr01(g##DE_MIB##_##L9, b0, _r, _f01, _v01)
#define DE_MIB_L9B0_WfCM(_r, _f, _c, _m)            REG_SHDW_VER_WfCM(g##DE_MIB##_##L9, b0, _r, _f, _c, _m)
#define DE_MIB_L9B0_WfCV(_r, _f, _c, _v1, _v2)      REG_SHDW_VER_WfCV(g##DE_MIB##_##L9, b0, _r, _f, _c, _v1, _v2)

#define DE_MIC_L9B0_RdFL(_r)                        REG_PHYS_VER_RdFL(g##DE_MIC##_##L9, b0, _r)
#define DE_MIC_L9B0_WrFL(_r)                        REG_PHYS_VER_WrFL(g##DE_MIC##_##L9, b0, _r)
#define DE_MIC_L9B0_Rd(_r)                          REG_SHDW_VER_Rd32(g##DE_MIC##_##L9, b0, _r)
#define DE_MIC_L9B0_Wr(_r, _v)                      REG_SHDW_VER_Wr32(g##DE_MIC##_##L9, b0, _r, _v)
#define DE_MIC_L9B0_Rd01(_r, _f01, _v01)            REG_SHDW_VER_Rd01(g##DE_MIC##_##L9, b0, _r, _f01, _v01)
#define DE_MIC_L9B0_Wr01(_r, _f01, _v01)            REG_SHDW_VER_Wr01(g##DE_MIC##_##L9, b0, _r, _f01, _v01)
#define DE_MIC_L9B0_WfCM(_r, _f, _c, _m)            REG_SHDW_VER_WfCM(g##DE_MIC##_##L9, b0, _r, _f, _c, _m)
#define DE_MIC_L9B0_WfCV(_r, _f, _c, _v1, _v2)      REG_SHDW_VER_WfCV(g##DE_MIC##_##L9, b0, _r, _f, _c, _v1, _v2)

#define DE_MID_L9B0_RdFL(_r)                        REG_PHYS_VER_RdFL(g##DE_MID##_##L9, b0, _r)
#define DE_MID_L9B0_WrFL(_r)                        REG_PHYS_VER_WrFL(g##DE_MID##_##L9, b0, _r)
#define DE_MID_L9B0_Rd(_r)                          REG_SHDW_VER_Rd32(g##DE_MID##_##L9, b0, _r)
#define DE_MID_L9B0_Wr(_r, _v)                      REG_SHDW_VER_Wr32(g##DE_MID##_##L9, b0, _r, _v)
#define DE_MID_L9B0_Rd01(_r, _f01, _v01)            REG_SHDW_VER_Rd01(g##DE_MID##_##L9, b0, _r, _f01, _v01)
#define DE_MID_L9B0_Wr01(_r, _f01, _v01)            REG_SHDW_VER_Wr01(g##DE_MID##_##L9, b0, _r, _f01, _v01)
#define DE_MID_L9B0_WfCM(_r, _f, _c, _m)            REG_SHDW_VER_WfCM(g##DE_MID##_##L9, b0, _r, _f, _c, _m)
#define DE_MID_L9B0_WfCV(_r, _f, _c, _v1, _v2)      REG_SHDW_VER_WfCV(g##DE_MID##_##L9, b0, _r, _f, _c, _v1, _v2)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        DE_MIA_REG_L9A0_T *a0;
		DE_MIA_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_MIA_REG_L9A0_T *a0;
		volatile DE_MIA_REG_L9B0_T *b0;
    } phys;
} DE_MIA_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_MIB_REG_L9A0_T *a0;
		DE_MIB_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_MIB_REG_L9A0_T *a0;
		volatile DE_MIB_REG_L9B0_T *b0;
    } phys;
} DE_MIB_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_MIC_REG_L9A0_T *a0;
		DE_MIC_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_MIC_REG_L9A0_T *a0;
		volatile DE_MIC_REG_L9B0_T *b0;
    } phys;
} DE_MIC_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_MID_REG_L9A0_T *a0;
		DE_MID_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_MID_REG_L9A0_T *a0;
		volatile DE_MID_REG_L9B0_T *b0;
    } phys;
} DE_MID_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        DE_MIF_REG_L9B0_T *a0;
		DE_MIF_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile DE_MIF_REG_L9B0_T *a0;
		volatile DE_MIF_REG_L9B0_T *b0;
    } phys;
} DE_MIF_REG_L9_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_MIF_REG_L9_INC  ----- */
/**  @} */
