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

/*
 * =====================================================================================
 *
 *       Filename:  io_dimm.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  3/17/2010 3:39:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jaemo.kim (),
 *        Company:  SIC, LG Electronics
 *
 * =====================================================================================
 */

#ifndef  IO_DIMM_INC
#define  IO_DIMM_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_LINUX_KERNEL
#define OK     RET_OK
#define NOT_OK RET_ERROR
#define DTV_STATUS_T int
#endif

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

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

DTV_STATUS_T MCU_DIMM_IO_Init(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_LocaldimmingControl(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_StoreDemo(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_LineDemo(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_ControlCompensation(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_LutControl(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_StoreControl(char *strBuff);
#ifdef USE_DIMM_TEMPORAL_DEFINITION
DTV_STATUS_T MCU_DIMM_IO_GetVersion(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_DbgControl(char *strBuff);
DTV_STATUS_T MCU_DIMM_IO_BluControl(char *strBuff);
#endif

#endif   /* ----- #ifndef IO_DIMM_INC  ----- */
