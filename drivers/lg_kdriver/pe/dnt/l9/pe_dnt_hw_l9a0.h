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


/** @file pe_dnt_coeff_l9a0.h
 *
 *  driver header for picture enhance deinterlacer parameters. ( used only within kdriver )
 *	- initial settings
 *	- default settings for each format
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_DNT_COEFF_L9A0_H_
#define	_PE_DNT_COEFF_L9A0_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_reg.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
const PE_REG_PARAM_T dnt_l_init_param_l9a0[] =
{
	/*---	Deinterlace Default Setting	---*/
	{0x051C,0x1601FF81},	{0x0504,0x80002404},	{0x0544,0xA03080E0},	{0x0520,0x24080000},	
	{0x0508,0x18287008},	{0x050C,0xF5505038},	{0x05F0,0x400080F5},	{0x05F4,0x18398000},	
	{0x05F8,0x13300173},	{0x05FC,0x1009A0BF},	{0x060C,0x30301011},	{0x0608,0x08081010},	
	{0x0604,0x10400000},	{0x0600,0x10000801},	{0x0610,0x04186003},	{0x0524,0x14142A06},	
	{0x0518,0x351E0F2D},	{0x0514,0x01013005},	{0x0510,0x54400000},	{0x0548,0x84400000},	
	{0x0580,0x3EFF3000},	{0x0500,0xF1046FAA},

	/*---	Film Mode Default Setting	---*/
	{0x0528,0x05000034},	{0x052C,0x04400320},	{0x0530,0xB4018037},	{0x0534,0x0E107003},
	{0x0538,0x04353E07},	{0x053C,0x15004005},	{0x0540,0x13101036},	{0x0550,0x030902A7},
	{0x0554,0x002509E1},	{0x0558,0x00002000},	{0x055C,0x01000000},	{0x0614,0x0E085F00},
};

const PE_REG_PARAM_T dnt_r_init_param_l9a0[] =
{
	/*---	Deinterlace Default Setting	---*/
	{0x251C,0x1601FF81},	{0x2504,0x80002404},	{0x2544,0xA03080E0},	{0x2520,0x24080000},	
	{0x2508,0x18287008},	{0x250C,0xF5505038},	{0x25F0,0x400080F5},	{0x25F4,0x18398000},
	{0x25F8,0x13300173},	{0x25FC,0x1009A0BF},	{0x260C,0x30301011},	{0x2608,0x08081010},
	{0x2604,0x10400000},	{0x2600,0x10000801},	{0x2610,0x04186003},	{0x2524,0x14142A06},
	{0x2518,0x351E0F2D},	{0x2514,0x01013005},	{0x2510,0x54400000},	{0x2548,0x84400000},
	{0x2580,0x3EFF3000},	{0x2500,0xF1046FAA},

	/*---	Film Mode Default Setting	---*/
	{0x2528,0x05000034},	{0x252C,0x04400320},	{0x2530,0xB4018037},	{0x2534,0x0E107003},
	{0x2538,0x04353E07},	{0x253C,0x15004005},	{0x2540,0x13101036},	{0x2550,0x030902A7},
	{0x2554,0x002509E1},	{0x2558,0x00002000},	{0x255C,0x01000000},	{0x2614,0x0E085F00},
};

#ifdef	__cplusplus
}
#endif /* __cplusplus */
 
#endif /* _PE_DNT_COEFF_L9A0_H_ */

