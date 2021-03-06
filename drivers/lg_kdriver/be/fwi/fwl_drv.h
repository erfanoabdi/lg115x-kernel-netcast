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
 *  firmware loader header file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.05
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _BE_FWL_H_
#define _BE_FWL_H_

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
typedef struct
{
	int  inx;
	char fwName[128];
	BOOLEAN	isMcuFw;	///< BOOLEAN for MCU firmware or not
}
BE_FW_FILE_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int BE_FW_Update(unsigned long arg);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _BE_FWL_H_ */

/** @} */




