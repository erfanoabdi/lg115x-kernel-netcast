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
 *  fw loader hal header file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.07
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _FWL_HAL_H_
#define _FWL_HAL_H_

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
typedef struct {
	char index;
	int  size;
	char *pBuffer;
	BOOLEAN	isMcuFw;	///< BOOLEAN for MCU firmware or not
} BE_FIRMWARE_T; 

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
UINT32 FWL_HAL_FW_Download(BE_FIRMWARE_T* pstParams);
BOOLEAN FWL_HAL_MCUisAlive(void);
UINT32 FWL_HAL_GetFwMemBaseSize(UINT8 ucIndex);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _FWL_HAL_H_ */

/** @} */








