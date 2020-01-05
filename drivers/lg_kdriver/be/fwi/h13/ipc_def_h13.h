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
 * chip specific definition for be device.
 *
 * author     justine.jeong@lge.com
 * version    1.0
 * date       2012.03.15
 * note       Additional information.
 *
 * @addtogroup be
 * @{
 */

#ifndef  _IPC_DEF_H13_H_
#define  _IPC_DEF_H13_H_

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#define BE_IPC_FROM_CPU_H13A0_BASE       (DPPB_TOP_REG_H13_BASE + DPPB_TOP_IPC_H13A0_OFFSET)
#define BE_IPC_FROM_MCU_H13A0_BASE       (BE_IPC_FROM_CPU_H13A0_BASE + IPC_FROM_CPU_SIZE)

#define BE_IPC_FROM_CPU_H13B0_BASE       (DPPB_TOP_REG_H13_BASE + DPPB_TOP_IPC_H13B0_OFFSET)
#define BE_IPC_FROM_MCU_H13B0_BASE       (BE_IPC_FROM_CPU_H13B0_BASE + IPC_FROM_CPU_SIZE)

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"

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

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef _IPC_DEF_H13_H_  ----- */
/**  @} */

