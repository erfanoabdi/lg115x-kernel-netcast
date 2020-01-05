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


/** @file pe_reg_def_l9.h
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

#ifndef _PE_REG_DEF_L9_H_
#define _PE_REG_DEF_L9_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_DTVSOC_DE_L9_BASE              0xC0020000
#define PE_DTVSOC_CTOP_CTRL_L9_BASE       0xFD300010
#define PE_DTVSOC_DIMM_L9_BASE            0xC001c000  //TODO modify properly

#define PE_DEA_REG_L9_OFFSET           0x0000
#define PE_DEB_REG_L9_OFFSET           0x1000
#define PE_DEC_REG_L9_OFFSET           0x2000
#define PE_DED_REG_L9_OFFSET           0x3000
#define PE_DEE_REG_L9_OFFSET           0x4000

#define PE_CVA_REG_L9_OFFSET           0x0100
#define PE_CVB_REG_L9_OFFSET           0x0200

#define PE_P0L_REG_L9_OFFSET           0x0400
#define PE_P0R_REG_L9_OFFSET           0x2400

#define PE_MIA_REG_L9_OFFSET           0x0800
#define PE_MIB_REG_L9_OFFSET           0x1b00
#define PE_MIC_REG_L9_OFFSET           0x2800
#define PE_MID_REG_L9_OFFSET           0x3e00

#define PE_MSL_REG_L9_OFFSET           0x1100
#define PE_MSR_REG_L9_OFFSET           0x3100

#define PE_OVL_REG_L9_OFFSET           0x1200
#define PE_OVR_REG_L9_OFFSET           0x3200

#define PE_P1L_REG_L9_OFFSET           0x1300
#define PE_P1R_REG_L9_OFFSET           0x3300

#define PE_SSC_REG_L9_OFFSET           0x2100

#define PE_DEA_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_DEA_REG_L9_OFFSET)
#define PE_DEB_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_DEB_REG_L9_OFFSET)
#define PE_DEC_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_DEC_REG_L9_OFFSET)
#define PE_DED_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_DED_REG_L9_OFFSET)
#define PE_DEE_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_DEE_REG_L9_OFFSET)

#define PE_CVA_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_CVA_REG_L9_OFFSET)
#define PE_CVB_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_CVB_REG_L9_OFFSET)

#define PE_P0L_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_P0L_REG_L9_OFFSET)
#define PE_P0R_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_P0R_REG_L9_OFFSET)

#define PE_MIA_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_MIA_REG_L9_OFFSET)
#define PE_MIB_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_MIB_REG_L9_OFFSET)
#define PE_MIC_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_MIC_REG_L9_OFFSET)
#define PE_MID_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_MID_REG_L9_OFFSET)

#define PE_MSL_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_MSL_REG_L9_OFFSET)
#define PE_MSR_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_MSR_REG_L9_OFFSET)

#define PE_OVL_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_OVL_REG_L9_OFFSET)
#define PE_OVR_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_OVR_REG_L9_OFFSET)

#define PE_P1L_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_P1L_REG_L9_OFFSET)
#define PE_P1R_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_P1R_REG_L9_OFFSET)

#define PE_SSC_REG_L9_BASE             (PE_DTVSOC_DE_L9_BASE + PE_SSC_REG_L9_OFFSET)

#define PE_MID_REG_L9B0_OFFSET		   0x3900
#define PE_MIF_REG_L9B0_OFFSET		   0x5F00
#define PE_MID_REG_L9B0_BASE		   (PE_DTVSOC_DE_L9_BASE + PE_MID_REG_L9B0_OFFSET)
#define PE_MIF_REG_L9B0_BASE		   (PE_DTVSOC_DE_L9_BASE + PE_MIF_REG_L9B0_OFFSET)

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif	/* _PE_REG_DEF_L9_H_ */

