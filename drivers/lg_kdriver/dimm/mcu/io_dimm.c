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
 *       Filename:  io_dimm.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  3/17/2010 3:37:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jaemo.kim (),
 *        Company:  SIC, LG Electronics
 *
 * =====================================================================================
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_XTENSA
#include <string.h>
#include <stdlib.h>
#include <BSP/UART/stdio.h>

#include <XDE/CFG_VIDEO.h>
#include <Common/DDI_DTV.h>
#include <Common/MEM_DTV.h>

#include <XDE/IPC_VIDEO.h>
#include <XDE/REG_DLR.h>
#include <XDE/MEM_VIDEO.h>
#include <XDE/MCU_VIDEO.h>
#include <XDE/de_kapi.h>
#include <XDE/IO_VIDEO.h>
#include <XDE/dimm_kapi.h>
#else
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "os_util.h"

#include "base_types.h"

#include "../de/de_model.h"
#include "../de/de_def.h"
#include "../de/de_ipc_def.h"
#include "../de/de_ipc.h"

#include "dimm_kapi.h"
#include "mcu/io_dimm.h"

#endif

#ifdef USE_VIDEO_TEST_MCU_IN_CPU
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

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
DTV_STATUS_T MCU_DIMM_IO_Init(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_LocaldimmingControl(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	BOOLEAN stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_StoreDemo(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	BOOLEAN stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_LineDemo(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	BOOLEAN stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_ControlCompensation(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	BOOLEAN stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_LutControl(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_DIMM_LUT_CTRL_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_StoreControl(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	BOOLEAN stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_GetVersion(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_DIMM_VERSION_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_DbgControl(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_DIMM_DBG_CTRL_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_DIMM_IO_BluControl(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_DIMM_BLU_CTRL_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
	} while (0);
#endif

	return ret;
}

#endif
