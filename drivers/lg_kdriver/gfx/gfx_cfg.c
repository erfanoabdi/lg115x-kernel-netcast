
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
 *  main configuration file for gfx device
 *	gfx device will teach you how to make device driver with new platform.
 *
 *  author		raxis.lim (raxis.lim@lge.com).lim (raxis.lim@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_gfx
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "gfx_impl.h"
#include "base_device.h"
#include "misc_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	GFX_SIZE_FOR_768MB

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
/** GFX memory description table
 *
 *	if base value is zero, base address is dynamicalled assigned by devmem manager ( dynamic address )
 *	if base value is non zero, devmem manager doesn't modify its address ( static address )
 *
 *	@see GFX_InitCfg
 */
LX_MEMCFG_T gfx_mem_desc_table[] =
{
	[0] = { .name = "gfx_surf", .base = 0x0,				.size = 137<<20  			},	/* L9 GP */
	[1] = { .name = "gfx_surf", .base = 0x33A00000,			.size = 0x00100000 			},	/* L9 COSMO */
	[2] = { .name = "gfx_surf", .base = GFX_DEV_MEM_BASE, 	.size = GFX_DEV_MEM_SIZE	},	/* H13 = tunable */
};

/** GFX H/W configuratin table
 *
 */
LX_GFX_REG_CFG_T	gfx_reg_cfg_desc_table[] =
{
	/* L9 */
    [0] = {
		.chip				= LX_CHIP_L9,
        .chip_name          = "GFX-L9",
        .reg_base_addr      = 0xc001d000, 	// L9_GFX_BASE,
        .reg_size           = 0x200, 		// real size is '0x1EC'
        .irq_num            = L9_IRQ_GFX,
    },

	/* H13 */
    [1] = {
		.chip				= LX_CHIP_H13,
        .chip_name          = "GFX-H13",
        .reg_base_addr      = 0xc000b000,   // H13_GFX_BASE,
        .reg_size           = 0x200,        // real size is '0x1EC'
        .irq_num            = (32/*H13_IRQ_GIC_START*/ + 54),//H13_IRQ_GPU_GFX
    },
};

LX_GFX_REG_CFG_T*	gpGfxRegCfg = NULL;
LX_GFX_MEM_CFG_T	gMemCfgGfx;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void    GFX_InitCfg ( void )
{
	/* get chip configuration */
	memcpy( &g_gfx_cfg, g_gfx_hal.GetCfg(), sizeof(LX_GFX_CFG_T));

	/*-----------------------------------------------------------------------------------
	 * [H13] configuration
	 *----------------------------------------------------------------------------------*/
    if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_H13) )
	{
		gpGfxRegCfg = &gfx_reg_cfg_desc_table[1];
		memcpy( &gMemCfgGfx.surface, &gfx_mem_desc_table[2], sizeof(LX_MEMCFG_T));
	}
	/*-----------------------------------------------------------------------------------
	 * [L9] configuration
	 *----------------------------------------------------------------------------------*/
    else if( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L9) )
    {
		gpGfxRegCfg = &gfx_reg_cfg_desc_table[0];

        switch ( lx_chip_plt() )
        {
            case LX_CHIP_PLATFORM_COSMO:
            {
				memcpy( &gMemCfgGfx.surface, &gfx_mem_desc_table[1], sizeof(LX_MEMCFG_T));
            }
            break;

            case LX_CHIP_PLATFORM_GP:
            default:
			{
				memcpy( &gMemCfgGfx.surface, &gfx_mem_desc_table[0], sizeof(LX_MEMCFG_T));
			}
			break;
        }
    }
	/*-----------------------------------------------------------------------------------
	 * unknown chip
	 *----------------------------------------------------------------------------------*/
    else
    {
		DBG_PRINT_ERROR("unknown chip 0x%x\n", lx_chip_rev() );	
    }
}

/** @} */

