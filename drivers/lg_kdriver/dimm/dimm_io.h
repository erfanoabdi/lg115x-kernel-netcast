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
 * date       2010.03.17
 * note       Additional information.
 *
 * @addtogroup lg1150_dimm
 * @{
 */

#ifndef  DIMM_IO_INC
#define  DIMM_IO_INC

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
int DIMM_IO_Init(unsigned long arg);
int DIMM_IO_LocaldimmingControl(unsigned long arg);
int DIMM_IO_StoreDemo(unsigned long arg);
int DIMM_IO_LineDemo(unsigned long arg);
int DIMM_IO_ControlCompensation(unsigned long arg);
int DIMM_IO_LutControl(unsigned long arg);
int DIMM_IO_StoreControl(unsigned long arg);
int DIMM_IO_RegRd(unsigned long arg);
int DIMM_IO_RegWr(unsigned long arg);
//#ifdef USE_DIMM_TEMPORAL_DEFINITION
int DIMM_IO_GetVersion(unsigned long arg);
int DIMM_IO_DbgControl(unsigned long arg);
int DIMM_IO_BluControl(unsigned long arg);
//#endif
int DIMM_IO_WbColorControl(unsigned long arg);
#ifdef USE_DIMM_SUSPEND
int DIMM_IO_probe(void);
int DIMM_IO_remove(void);
int DIMM_IO_resume(void);
#endif

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DIMM_IO_INC  ----- */
/**  @} */
