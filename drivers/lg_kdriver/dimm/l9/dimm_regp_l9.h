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

#ifndef  DIMM_REGP_L9_INC
#define  DIMM_REGP_L9_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DIMM_REG_L9_Create(void);
int DIMM_REG_L9_Destroy(void);
int DIMM_REG_L9_Init(LX_DIMM_INFO_T *pstParams);
int DIMM_REG_L9_LocaldimmingControl(BOOLEAN *pstParams);
int DIMM_REG_L9_StoreDemo(BOOLEAN *pstParams);
int DIMM_REG_L9_LineDemo(LX_DIMM_LINE_CTRL_T *pstParams);
int DIMM_REG_L9_ControlCompensation(BOOLEAN *pstParams);
int DIMM_REG_L9_LutControl(LX_DIMM_LUT_CTRL_T *pstParams);
int DIMM_REG_L9_StoreControl(BOOLEAN *pstParams);
UINT32 DIMM_REG_L9_RegRd(UINT32 addr);
int DIMM_REG_L9_RegWr(LX_DIMM_REG_WRITE_T *pstParams);
int DIMM_REG_L9_WbColorControl(LX_DIMM_WBCOLOR_CTRL_T *pstParams);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DIMM_REGP_L9_INC  ----- */
/**  @} */
