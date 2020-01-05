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

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/platform.h>

#include "base_types.h"
#include "os_util.h"

#include "../de/de_model.h"
#include "../de/de_ver_def.h"

#include "../de/de_def.h"
#include "dimm_kapi.h"
#ifdef USE_KDRV_CODES_FOR_L8
#include "l8/dimm_regp_l8.h"
#endif
#ifdef USE_KDRV_CODES_FOR_L9
#include "l9/dimm_regp_l9.h"
#endif

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
/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize DIMM module.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_Init(LX_DIMM_INFO_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_Init(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_Init(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control local-dimming-on.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_LocaldimmingControl(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_LocaldimmingControl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_LocaldimmingControl(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Dimming Store Demo Mode.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_StoreDemo(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_StoreDemo(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_StoreDemo(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Dimming Line Demo Mode.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_LineDemo(LX_DIMM_LINE_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_LineDemo(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_LineDemo(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Pixel Compensation.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_ControlCompensation(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_ControlCompensation(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_ControlCompensation(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Look up Table.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_LutControl(LX_DIMM_LUT_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_LutControl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_LutControl(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Local Dimming Control for Store Mode.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_StoreControl(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_StoreControl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_StoreControl(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Local Dimming Control White Balance Color.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_WbColorControl(LX_DIMM_WBCOLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_WbColorControl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_WbColorControl(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Read Reigster
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
UINT32 DIMM_HAL_RegRd(UINT32 addr)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_RegRd(addr);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_RegRd(addr);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Reigster
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_RegWr(LX_DIMM_REG_WRITE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_RegWr(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_RegWr(pstParams);
	} else
#endif
	{
	}
	return ret;
}

#ifdef USE_DIMM_TEMPORAL_DEFINITION
/**
 * @callgraph
 * @callergraph
 *
 * @brief Get DIMM INFO.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_GetVersion(LX_DIMM_VERSION_T *pstParams)
{
    int ret = RET_OK;

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief For DIMM debugging.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_DbgControl(LX_DIMM_DBG_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_DbgControl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_DbgControl(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief BLU(Back Light Uint) Control of DIMM.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_HAL_BluControl(LX_DIMM_BLU_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DIMM_REG_L9_BluControl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L8
	if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
		ret = DIMM_REG_BluControl(pstParams);
	} else
#endif
	{
	}
	return ret;
}
#endif

/**  @} */
