
/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/


/** @file 
 *
 *  main configuration file for aad device
 *	aad device will teach you how to make device driver with new platform.
 *
 *  author		jongsang.oh (jongsang.oh@lge.com)
 *  version		1.0 
 *  date		2010.01.26
 *  note		Additional information. 
 *
 *  @addtogroup lg1150_aad 
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "../base/h13/linux_platform.h"
#include "../base/h13/linux_irqs.h"

#include "aad_cfg.h"


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
/**
AAD Register configuration.
*/
LX_AAD_REG_CFG_T gstAadRegCfg[] =
{
	// for LG1152(L9)
	{
		.chip_name			= "LG1152(L9)",
		.reg_base_addr 		= 0xC0009600,
		.reg_size			= 0x000002AC,
		.irq_num			= 0x67,
	},
	// for LG1154(H13)
	{
		.chip_name			= "LG1154(H13)",
		.reg_base_addr		= H13_AAD_BASE,
		.reg_size			= 0x000002AC,
		.irq_num			= H13_IRQ_AAD,
	},
};

/**
AAD Register definition.
*/
LX_AAD_REG_CFG_T *pstAadRegCfg = &gstAadRegCfg[0];	// for Real. Chip



/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/



/** @} */

