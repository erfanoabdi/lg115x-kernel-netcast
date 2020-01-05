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


/** @file pe_ctr_reg_l9.h
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
#ifndef _PE_CTRL_REG_L9_H_
#define _PE_CTRL_REG_L9_H_
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_ctr_reg_l9a0.h"
#include "pe_ctr_reg_l9b0.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_DEA_L9_RdFL(_r)                          PE_FN_CHIP_RdFL(PE_DEA, L9, _r)
#define PE_DEA_L9_WrFL(_r)                          PE_FN_CHIP_WrFL(PE_DEA, L9, _r)
#define PE_DEA_L9_Rd(_r)                            PE_FN_CHIP_Rd32(PE_DEA, L9, _r)
#define PE_DEA_L9_Wr(_r, _v)                        PE_FN_CHIP_Wr32(PE_DEA, L9, _r, _v)
#define PE_DEA_L9_Rd01(_r, _f01, _v01)              PE_FN_CHIP_Rd01(PE_DEA, L9, _r, _f01, _v01)
#define PE_DEA_L9_Wr01(_r, _f01, _v01)              PE_FN_CHIP_Wr01(PE_DEA, L9, _r, _f01, _v01)
#define PE_DEA_L9_FLRd(_r, _v)                      PE_FN_CHIP_FLRd(PE_DEA, L9, _r, _v)
#define PE_DEA_L9_FLWr(_r, _v)                      PE_FN_CHIP_FLWr(PE_DEA, L9, _r, _v)
#define PE_DEA_L9_FLRf(_r, _f01, _v01)              PE_FN_CHIP_FLRf(PE_DEA, L9, _r, _f01, _v01)
#define PE_DEA_L9_FLWf(_r, _f01, _v01)              PE_FN_CHIP_FLWf(PE_DEA, L9, _r, _f01, _v01)

#define PE_DEB_L9_RdFL(_r)                          PE_FN_CHIP_RdFL(PE_DEB, L9, _r)
#define PE_DEB_L9_WrFL(_r)                          PE_FN_CHIP_WrFL(PE_DEB, L9, _r)
#define PE_DEB_L9_Rd(_r)                            PE_FN_CHIP_Rd32(PE_DEB, L9, _r)
#define PE_DEB_L9_Wr(_r, _v)                        PE_FN_CHIP_Wr32(PE_DEB, L9, _r, _v)
#define PE_DEB_L9_Rd01(_r, _f01, _v01)              PE_FN_CHIP_Rd01(PE_DEB, L9, _r, _f01, _v01)
#define PE_DEB_L9_Wr01(_r, _f01, _v01)              PE_FN_CHIP_Wr01(PE_DEB, L9, _r, _f01, _v01)
#define PE_DEB_L9_FLRd(_r, _v)                      PE_FN_CHIP_FLRd(PE_DEB, L9, _r, _v)
#define PE_DEB_L9_FLWr(_r, _v)                      PE_FN_CHIP_FLWr(PE_DEB, L9, _r, _v)
#define PE_DEB_L9_FLRf(_r, _f01, _v01)              PE_FN_CHIP_FLRf(PE_DEB, L9, _r, _f01, _v01)
#define PE_DEB_L9_FLWf(_r, _f01, _v01)              PE_FN_CHIP_FLWf(PE_DEB, L9, _r, _f01, _v01)

#define PE_DEC_L9_RdFL(_r)                          PE_FN_CHIP_RdFL(PE_DEC, L9, _r)
#define PE_DEC_L9_WrFL(_r)                          PE_FN_CHIP_WrFL(PE_DEC, L9, _r)
#define PE_DEC_L9_Rd(_r)                            PE_FN_CHIP_Rd32(PE_DEC, L9, _r)
#define PE_DEC_L9_Wr(_r, _v)                        PE_FN_CHIP_Wr32(PE_DEC, L9, _r, _v)
#define PE_DEC_L9_Rd01(_r, _f01, _v01)              PE_FN_CHIP_Rd01(PE_DEC, L9, _r, _f01, _v01)
#define PE_DEC_L9_Wr01(_r, _f01, _v01)              PE_FN_CHIP_Wr01(PE_DEC, L9, _r, _f01, _v01)
#define PE_DEC_L9_FLRd(_r, _v)                      PE_FN_CHIP_FLRd(PE_DEC, L9, _r, _v)
#define PE_DEC_L9_FLWr(_r, _v)                      PE_FN_CHIP_FLWr(PE_DEC, L9, _r, _v)
#define PE_DEC_L9_FLRf(_r, _f01, _v01)              PE_FN_CHIP_FLRf(PE_DEC, L9, _r, _f01, _v01)
#define PE_DEC_L9_FLWf(_r, _f01, _v01)              PE_FN_CHIP_FLWf(PE_DEC, L9, _r, _f01, _v01)

#define PE_DED_L9_RdFL(_r)                          PE_FN_CHIP_RdFL(PE_DED, L9, _r)
#define PE_DED_L9_WrFL(_r)                          PE_FN_CHIP_WrFL(PE_DED, L9, _r)
#define PE_DED_L9_Rd(_r)                            PE_FN_CHIP_Rd32(PE_DED, L9, _r)
#define PE_DED_L9_Wr(_r, _v)                        PE_FN_CHIP_Wr32(PE_DED, L9, _r, _v)
#define PE_DED_L9_Rd01(_r, _f01, _v01)              PE_FN_CHIP_Rd01(PE_DED, L9, _r, _f01, _v01)
#define PE_DED_L9_Wr01(_r, _f01, _v01)              PE_FN_CHIP_Wr01(PE_DED, L9, _r, _f01, _v01)
#define PE_DED_L9_FLRd(_r, _v)                      PE_FN_CHIP_FLRd(PE_DED, L9, _r, _v)
#define PE_DED_L9_FLWr(_r, _v)                      PE_FN_CHIP_FLWr(PE_DED, L9, _r, _v)
#define PE_DED_L9_FLRf(_r, _f01, _v01)              PE_FN_CHIP_FLRf(PE_DED, L9, _r, _f01, _v01)
#define PE_DED_L9_FLWf(_r, _f01, _v01)              PE_FN_CHIP_FLWf(PE_DED, L9, _r, _f01, _v01)

#define PE_DEE_L9_RdFL(_r)                          PE_FN_CHIP_RdFL(PE_DEE, L9, _r)
#define PE_DEE_L9_WrFL(_r)                          PE_FN_CHIP_WrFL(PE_DEE, L9, _r)
#define PE_DEE_L9_Rd(_r)                            PE_FN_CHIP_Rd32(PE_DEE, L9, _r)
#define PE_DEE_L9_Wr(_r, _v)                        PE_FN_CHIP_Wr32(PE_DEE, L9, _r, _v)
#define PE_DEE_L9_Rd01(_r, _f01, _v01)              PE_FN_CHIP_Rd01(PE_DEE, L9, _r, _f01, _v01)
#define PE_DEE_L9_Wr01(_r, _f01, _v01)              PE_FN_CHIP_Wr01(PE_DEE, L9, _r, _f01, _v01)
#define PE_DEE_L9_FLRd(_r, _v)                      PE_FN_CHIP_FLRd(PE_DEE, L9, _r, _v)
#define PE_DEE_L9_FLWr(_r, _v)                      PE_FN_CHIP_FLWr(PE_DEE, L9, _r, _v)
#define PE_DEE_L9_FLRf(_r, _f01, _v01)              PE_FN_CHIP_FLRf(PE_DEE, L9, _r, _f01, _v01)
#define PE_DEE_L9_FLWf(_r, _f01, _v01)              PE_FN_CHIP_FLWf(PE_DEE, L9, _r, _f01, _v01)

#define PE_DEB_L9A_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DEB##_##L9, a0, _r)
#define PE_DEB_L9A_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DEB##_##L9, a0, _r)
#define PE_DEB_L9A_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DEB##_##L9, a0, _r)
#define PE_DEB_L9A_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DEB##_##L9, a0, _r, _v)
#define PE_DEB_L9A_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DEB##_##L9, a0, _r, _f01, _v01)
#define PE_DEB_L9A_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DEB##_##L9, a0, _r, _f01, _v01)
#define PE_DEB_L9A_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DEB##_##L9, a0, _r, _f01, _v01)
#define PE_DEB_L9A_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DEB##_##L9, a0, _r, _f01, _v01)
#define PE_DEB_L9A_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DEB##_##L9, a0, _r, _f, _c, _m)
#define PE_DEB_L9A_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DEB##_##L9, a0, _r, _f, _c, _m)
#define PE_DEB_L9A_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DEB##_##L9, a0, _r, _f, _c, _v1, _v2)
#define PE_DEB_L9A_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DEB##_##L9, a0, _r, _v)
#define PE_DEB_L9A_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DEB##_##L9, a0, _r, _v)
#define PE_DEB_L9A_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DEB##_##L9, a0, _r, _f, _c, _v1, _v2)

#define PE_DED_L9A_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DED##_##L9, a0, _r)
#define PE_DED_L9A_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DED##_##L9, a0, _r)
#define PE_DED_L9A_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DED##_##L9, a0, _r)
#define PE_DED_L9A_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DED##_##L9, a0, _r, _v)
#define PE_DED_L9A_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DED##_##L9, a0, _r, _f01, _v01)
#define PE_DED_L9A_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DED##_##L9, a0, _r, _f01, _v01)
#define PE_DED_L9A_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DED##_##L9, a0, _r, _f01, _v01)
#define PE_DED_L9A_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DED##_##L9, a0, _r, _f01, _v01)
#define PE_DED_L9A_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DED##_##L9, a0, _r, _f, _c, _m)
#define PE_DED_L9A_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DED##_##L9, a0, _r, _f, _c, _m)
#define PE_DED_L9A_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DED##_##L9, a0, _r, _f, _c, _v1, _v2)
#define PE_DED_L9A_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DED##_##L9, a0, _r, _v)
#define PE_DED_L9A_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DED##_##L9, a0, _r, _v)
#define PE_DED_L9A_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DED##_##L9, a0, _r, _f, _c, _v1, _v2)

#define PE_DEE_L9A_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DEE##_##L9, a0, _r)
#define PE_DEE_L9A_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DEE##_##L9, a0, _r)
#define PE_DEE_L9A_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DEE##_##L9, a0, _r)
#define PE_DEE_L9A_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DEE##_##L9, a0, _r, _v)
#define PE_DEE_L9A_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DEE##_##L9, a0, _r, _f01, _v01)
#define PE_DEE_L9A_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DEE##_##L9, a0, _r, _f01, _v01)
#define PE_DEE_L9A_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DEE##_##L9, a0, _r, _f01, _v01)
#define PE_DEE_L9A_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DEE##_##L9, a0, _r, _f01, _v01)
#define PE_DEE_L9A_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DEE##_##L9, a0, _r, _f, _c, _m)
#define PE_DEE_L9A_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DEE##_##L9, a0, _r, _f, _c, _m)
#define PE_DEE_L9A_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DEE##_##L9, a0, _r, _f, _c, _v1, _v2)
#define PE_DEE_L9A_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DEE##_##L9, a0, _r, _v)
#define PE_DEE_L9A_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DEE##_##L9, a0, _r, _v)
#define PE_DEE_L9A_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DEE##_##L9, a0, _r, _f, _c, _v1, _v2)

#define PE_DEA_L9B_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DEA##_##L9, b0, _r)
#define PE_DEA_L9B_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DEA##_##L9, b0, _r)
#define PE_DEA_L9B_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DEA##_##L9, b0, _r)
#define PE_DEA_L9B_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DEA##_##L9, b0, _r, _v)
#define PE_DEA_L9B_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DEA##_##L9, b0, _r, _f01, _v01)
#define PE_DEA_L9B_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DEA##_##L9, b0, _r, _f01, _v01)
#define PE_DEA_L9B_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DEA##_##L9, b0, _r, _f01, _v01)
#define PE_DEA_L9B_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DEA##_##L9, b0, _r, _f01, _v01)
#define PE_DEA_L9B_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DEA##_##L9, b0, _r, _f, _c, _m)
#define PE_DEA_L9B_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DEA##_##L9, b0, _r, _f, _c, _m)
#define PE_DEA_L9B_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DEA##_##L9, b0, _r, _f, _c, _v1, _v2)
#define PE_DEA_L9B_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DEA##_##L9, b0, _r, _v)
#define PE_DEA_L9B_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DEA##_##L9, b0, _r, _v)
#define PE_DEA_L9B_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DEA##_##L9, b0, _r, _f, _c, _v1, _v2)

#define PE_DEB_L9B_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DEB##_##L9, b0, _r)
#define PE_DEB_L9B_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DEB##_##L9, b0, _r)
#define PE_DEB_L9B_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DEB##_##L9, b0, _r)
#define PE_DEB_L9B_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DEB##_##L9, b0, _r, _v)
#define PE_DEB_L9B_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DEB##_##L9, b0, _r, _f01, _v01)
#define PE_DEB_L9B_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DEB##_##L9, b0, _r, _f01, _v01)
#define PE_DEB_L9B_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DEB##_##L9, b0, _r, _f01, _v01)
#define PE_DEB_L9B_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DEB##_##L9, b0, _r, _f01, _v01)
#define PE_DEB_L9B_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DEB##_##L9, b0, _r, _f, _c, _m)
#define PE_DEB_L9B_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DEB##_##L9, b0, _r, _f, _c, _m)
#define PE_DEB_L9B_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DEB##_##L9, b0, _r, _f, _c, _v1, _v2)
#define PE_DEB_L9B_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DEB##_##L9, b0, _r, _v)
#define PE_DEB_L9B_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DEB##_##L9, b0, _r, _v)
#define PE_DEB_L9B_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DEB##_##L9, b0, _r, _f, _c, _v1, _v2)

#define PE_DEC_L9B_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DEC##_##L9, b0, _r)
#define PE_DEC_L9B_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DEC##_##L9, b0, _r)
#define PE_DEC_L9B_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DEC##_##L9, b0, _r)
#define PE_DEC_L9B_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DEC##_##L9, b0, _r, _v)
#define PE_DEC_L9B_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DEC##_##L9, b0, _r, _f01, _v01)
#define PE_DEC_L9B_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DEC##_##L9, b0, _r, _f01, _v01)
#define PE_DEC_L9B_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DEC##_##L9, b0, _r, _f01, _v01)
#define PE_DEC_L9B_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DEC##_##L9, b0, _r, _f01, _v01)
#define PE_DEC_L9B_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DEC##_##L9, b0, _r, _f, _c, _m)
#define PE_DEC_L9B_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DEC##_##L9, b0, _r, _f, _c, _m)
#define PE_DEC_L9B_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DEC##_##L9, b0, _r, _f, _c, _v1, _v2)
#define PE_DEC_L9B_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DEC##_##L9, b0, _r, _v)
#define PE_DEC_L9B_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DEC##_##L9, b0, _r, _v)
#define PE_DEC_L9B_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DEC##_##L9, b0, _r, _f, _c, _v1, _v2)

#define PE_DED_L9B_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DED##_##L9, b0, _r)
#define PE_DED_L9B_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DED##_##L9, b0, _r)
#define PE_DED_L9B_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DED##_##L9, b0, _r)
#define PE_DED_L9B_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DED##_##L9, b0, _r, _v)
#define PE_DED_L9B_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DED##_##L9, b0, _r, _f01, _v01)
#define PE_DED_L9B_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DED##_##L9, b0, _r, _f01, _v01)
#define PE_DED_L9B_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DED##_##L9, b0, _r, _f01, _v01)
#define PE_DED_L9B_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DED##_##L9, b0, _r, _f01, _v01)
#define PE_DED_L9B_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DED##_##L9, b0, _r, _f, _c, _m)
#define PE_DED_L9B_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DED##_##L9, b0, _r, _f, _c, _m)
#define PE_DED_L9B_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DED##_##L9, b0, _r, _f, _c, _v1, _v2)
#define PE_DED_L9B_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DED##_##L9, b0, _r, _v)
#define PE_DED_L9B_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DED##_##L9, b0, _r, _v)
#define PE_DED_L9B_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DED##_##L9, b0, _r, _f, _c, _v1, _v2)

#define PE_DEE_L9B_RdFL(_r)                         PE_REG_PHYS_VER_RdFL(g##PE_DEE##_##L9, b0, _r)
#define PE_DEE_L9B_WrFL(_r)                         PE_REG_PHYS_VER_WrFL(g##PE_DEE##_##L9, b0, _r)
#define PE_DEE_L9B_Rd(_r)                           PE_REG_SHDW_VER_Rd32(g##PE_DEE##_##L9, b0, _r)
#define PE_DEE_L9B_Wr(_r, _v)                       PE_REG_SHDW_VER_Wr32(g##PE_DEE##_##L9, b0, _r, _v)
#define PE_DEE_L9B_Rd01(_r, _f01, _v01)             PE_REG_SHDW_VER_Rd01(g##PE_DEE##_##L9, b0, _r, _f01, _v01)
#define PE_DEE_L9B_Wr01(_r, _f01, _v01)             PE_REG_SHDW_VER_Wr01(g##PE_DEE##_##L9, b0, _r, _f01, _v01)
#define PE_DEE_L9B_FLRf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLRf(g##PE_DEE##_##L9, b0, _r, _f01, _v01)
#define PE_DEE_L9B_FLWf(_r, _f01, _v01)             PE_REG_PHYS_VER_FLWf(g##PE_DEE##_##L9, b0, _r, _f01, _v01)
#define PE_DEE_L9B_WfCM(_r, _f, _c, _m)             PE_REG_SHDW_VER_WfCM(g##PE_DEE##_##L9, b0, _r, _f, _c, _m)
#define PE_DEE_L9B_FLCM(_r, _f, _c, _m)             PE_REG_PHYS_VER_FLCM(g##PE_DEE##_##L9, b0, _r, _f, _c, _m)
#define PE_DEE_L9B_WfCV(_r, _f, _c, _v1, _v2)       PE_REG_SHDW_VER_WfCV(g##PE_DEE##_##L9, b0, _r, _f, _c, _v1, _v2)
#define PE_DEE_L9B_FLRd(_r, _v)              		PE_REG_PHYS_VER_FLRd(g##PE_DEE##_##L9, b0, _r, _v)
#define PE_DEE_L9B_FLWr(_r, _v)              		PE_REG_PHYS_VER_FLWr(g##PE_DEE##_##L9, b0, _r, _v)
#define PE_DEE_L9B_FLCV(_r, _f, _c, _v1, _v2)    	PE_REG_PHYS_VER_FLCV(g##PE_DEE##_##L9, b0, _r, _f, _c, _v1, _v2)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
    union {
        UINT32          *addr;
        PE_DEA_REG_L9A0_T *a0;
		PE_DEA_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_DEA_REG_L9A0_T *a0;
		volatile PE_DEA_REG_L9B0_T *b0;
    } phys;
} PE_DEA_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_DEB_REG_L9A0_T *a0;
		PE_DEB_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_DEB_REG_L9A0_T *a0;
		volatile PE_DEB_REG_L9B0_T *b0;
    } phys;
} PE_DEB_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_DEC_REG_L9A0_T *a0;
		PE_DEC_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_DEC_REG_L9A0_T *a0;
		volatile PE_DEC_REG_L9B0_T *b0;
    } phys;
} PE_DEC_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_DED_REG_L9A0_T *a0;
		PE_DED_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_DED_REG_L9A0_T *a0;
		volatile PE_DED_REG_L9B0_T *b0;
    } phys;
} PE_DED_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_DEE_REG_L9A0_T *a0;
		PE_DEE_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_DEE_REG_L9A0_T *a0;
		volatile PE_DEE_REG_L9B0_T *b0;
    } phys;
} PE_DEE_REG_L9_T;

typedef struct {
    union {
        UINT32          *addr;
        PE_DEE_REG_L9B0_T *a0;
		PE_DEE_REG_L9B0_T *b0;
    } shdw;

    union {
        volatile UINT32          *addr;
        volatile PE_DEE_REG_L9B0_T *a0;
		volatile PE_DEE_REG_L9B0_T *b0;
    } phys;
} PE_DEF_REG_L9_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* _PE_CTRL_REG_L9_H_ */

