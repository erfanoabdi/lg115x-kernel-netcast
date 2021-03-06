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
 *  fw loader reg header file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.06
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _FWL_REG_H13_H_
#define _FWL_REG_H13_H_

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
UINT32 FWL_REG_H13_FW_Download(UINT8 ucIndex, UINT8 *pucBuff, UINT32 ulSize, BOOLEAN bIsMcuFw);
BOOLEAN FWL_REG_H13_MCUisAlive(void);
UINT32 FWL_REG_H13_GetFwMemBaseSize(UINT8 ucIndex);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _FWL_REG_H13_H_ */

/** @} */







