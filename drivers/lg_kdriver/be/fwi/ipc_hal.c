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
 *  ipc hal file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.14
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

#include "os_util.h"
#include "be_dbg.h"

#include "be_def.h"
#include "h13/ipc_reg_h13.h"

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
 * @brief initialize ipc register
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int IPC_HAL_Init(UINT32 *pIPCBuffToMCU, UINT32 *pIPCBuffFrMCU)
{
	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0)) {
		IPC_REG_H13_Init(pIPCBuffToMCU, pIPCBuffFrMCU);
	} else {
		IPC_REG_H13_Init(pIPCBuffToMCU, pIPCBuffFrMCU);
	}
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief free ipc register
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int IPC_HAL_Free(UINT32 *pIPCBuffToMCU, UINT32 *pIPCBuffFrMCU)
{
	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0)) {
		IPC_REG_H13_Free(pIPCBuffToMCU, pIPCBuffFrMCU);
	} else {
		IPC_REG_H13_Free(pIPCBuffToMCU, pIPCBuffFrMCU);
	}
	return RET_OK;
}


