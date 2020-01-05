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
 *  interrupt reg header file for be device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.08
 *  note		Additional information.
 *
 *  @addtogroup be
 *	@{
 */

#ifndef _INT_REG_H13_H_
#define _INT_REG_H13_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

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
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int INT_REG_H13_Init(void);
int INT_REG_H13_GetStatus(BE_INT_TYPE_T intrType, UINT32 *pIntrStatus);
int INT_REG_H13_ClearStatus(BE_INT_TYPE_T intrType, UINT32 *pIntrStatus);
int INT_REG_H13_WakeUpReg(BE_INT_DIR_TYPE_T intrDir, BOOLEAN turnOn);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _INT_REG_H13_H_ */

/** @} */


