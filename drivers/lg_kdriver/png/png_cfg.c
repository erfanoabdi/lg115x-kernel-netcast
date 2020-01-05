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
 *  main configuration file for png device
 *	png device will teach you how to make device driver with new platform.
 *
 *  author		Juhee Park
 *  version		1.0 
 *  date		2011.12.02
 *  note		Additional information. 
 *
 *  @addtogroup lg_png 
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/mm.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/slab.h>

#include <asm/io.h>

#include "os_util.h"
#include "base_device.h"
#include "png_impl.h"

#include "./l9/png_l9_drv.h"
#include "./h13/png_h13_drv.h"

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
// Default configuration is for L8
LX_PNG_MEM_CFG_T gMemCfgPng[] =
{
	[0] = /* L8 */
	{
		.memory_name = "png_buffer",
		.memory_base = 0x0,
		.memory_size = 0x80000,	/* 512KB. 512KB will support almost PNG image in GP UI */
	},

	[1] = /* L9 */
	{
		.memory_name = "png_buffer",
		.memory_base = 0x0,
		.memory_size = 0x00800000,
	},

	[2] = /* H13 */
	{
		.memory_name = "png_HW_buffer",
		.memory_base = 0x0, //0x7C000000,
		.memory_size = 0x00400000,
	},
};

LX_PNG_MEM_CFG_T*		gpMemCfgPng;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int PNG_Config(struct PNG_T **ppPNG)
{
	int ret = RET_OK;
	struct PNG_T* pPNG = NULL;

	pPNG = kzalloc(sizeof(struct PNG_T), GFP_KERNEL);
	if (pPNG == NULL)
	{
		ret = RET_ERROR;
		goto fail;
	}

	pPNG->chip = lx_chip_rev();
	pPNG->platform = lx_chip_plt();
	pPNG->devno = MKDEV(PNG_MAJOR, PNG_MINOR);

	if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L9) )
	{
		PNG_L9_Init(pPNG);
	}
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_H13) )
	{	
		PNG_H13_Init(pPNG);
	}
	else
	{
		DBG_PRINT_ERROR("unknown chip 0x%x\n", lx_chip_rev() );
		ret = RET_ERROR; goto fail;
	}

	*ppPNG = pPNG;

	return RET_OK;
fail:
	kfree(pPNG);
	return ret;
}

void PNG_Unconfig(struct PNG_T *pPNG)
{
	if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L9) )
	{
		PNG_L9_Exit(pPNG);
	}
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_H13) )
	{
		PNG_H13_Exit(pPNG);
	}
	else
	{
        DBG_PRINT_ERROR("unknown chip 0x%x\n", lx_chip_rev() );
		return;
	}

	kfree(pPNG);
}

/** @} */

