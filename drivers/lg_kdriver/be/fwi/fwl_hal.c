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
 *  fw loader hal driver file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.06
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_def.h"

#include "fwl_hal.h"
#include "h13/fwl_reg_h13.h"

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

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief download BE firmware in hal layer
 *
 * @param pstParams [IN] pointer, size information for new firmware
 *
 * @return FW base address if success, NULL for otherwise
 */
UINT32 FWL_HAL_FW_Download(BE_FIRMWARE_T* pstParams)
{
	return FWL_REG_H13_FW_Download(pstParams->index, pstParams->pBuffer, pstParams->size, pstParams->isMcuFw);
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief check mcu is alive in hal layer
 *
 * @param void
 *
 * @return TRUE if mcu run, FALSE for otherwise
 */
BOOLEAN FWL_HAL_MCUisAlive(void)
{
	BOOLEAN isFwRun = FALSE;

	isFwRun = FWL_REG_H13_MCUisAlive();

	return isFwRun;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief return firmware memory base size in hal layer
 *
 * @param ucIndex [IN] index information for the firmware
 *
 * @return firmware memory base size if success, 0 for otherwise
 */
UINT32 FWL_HAL_GetFwMemBaseSize(UINT8 ucIndex)
{
	return FWL_REG_H13_GetFwMemBaseSize(ucIndex);
}



