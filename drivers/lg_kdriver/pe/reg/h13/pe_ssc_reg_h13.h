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


/** @file pe_ssc_reg_h13.h
 *
 *  driver for picture enhance register read, write functions. ( used only within kdriver )
 *
 *	@author		inkyung.park(inkyung.park@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.10.12
 *	@see
 */
#ifndef  _PE_SSC_REG_H13_INC_
#define  _PE_SSC_REG_H13_INC_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "pe_reg_mac.h"
#include "pe_ssc_reg_h13a0.h"
#include "pe_ssc_reg_h13b0.h"


/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_SSC_H13_RdFL(_r)							PE_FN_CHIP_RdFL(PE_SSC, H13, _r)
#define PE_SSC_H13_WrFL(_r)							PE_FN_CHIP_WrFL(PE_SSC, H13, _r)
#define PE_SSC_H13_Rd(_r)							PE_FN_CHIP_Rd32(PE_SSC, H13, _r)
#define PE_SSC_H13_Wr(_r, _v)						PE_FN_CHIP_Wr32(PE_SSC, H13, _r, _v)
#define PE_SSC_H13_Rd01(_r, _f01, _v01)				PE_FN_CHIP_Rd01(PE_SSC, H13, _r, _f01, _v01)
#define PE_SSC_H13_Wr01(_r, _f01, _v01)				PE_FN_CHIP_Wr01(PE_SSC, H13, _r, _f01, _v01)
#define PE_SSC_H13_FLRd(_r, _v)						PE_FN_CHIP_FLRd(PE_SSC, H13, _r, _v)
#define PE_SSC_H13_FLWr(_r, _v)						PE_FN_CHIP_FLWr(PE_SSC, H13, _r, _v)
#define PE_SSC_H13_FLRf(_r, _f01, _v01)				PE_FN_CHIP_FLRf(PE_SSC, H13, _r, _f01, _v01)
#define PE_SSC_H13_FLWf(_r, _f01, _v01)				PE_FN_CHIP_FLWf(PE_SSC, H13, _r, _f01, _v01)


/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	union {
		UINT32			*addr;
		PE_SSC_REG_H13A0_T *a0;
		PE_SSC_REG_H13B0_T *b0;
	} shdw;

	union {
		volatile UINT32			 *addr;
		volatile PE_SSC_REG_H13A0_T *a0;
		volatile PE_SSC_REG_H13B0_T *b0;
	} phys;
} PE_SSC_REG_H13_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* ----- #ifndef PE_SSC_REG_H13_INC  ----- */
/**  @} */
