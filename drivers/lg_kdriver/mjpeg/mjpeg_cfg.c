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
 *  main configuration file for mjpeg device
 *	mjpeg device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.04.09
 *  note		Additional information.
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "os_util.h"
#include "mjpeg_cfg.h"
#include "mjpeg_kapi.h"

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
	UINT32			chip;
	LX_MJPEG_CFG_T	cfg;
}
MJPEG_CFG_TBL_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
MJPEG_MEM_CFG_T gMemCfgMjpeg =
{
	.pcMemory_name = "mjpeg_buffer",
	.ui32Memory_base = 0x00000000,
	.ui32Memory_size = 0x00200000	/* 2Mb */
};

/** JPG H/W decoder configuration
 *
 */
MJPEG_CFG_TBL_T	g_mjpeg_cfg_table[] =
{
	[0] = { .chip = LX_CHIP_L9,
			.cfg  = { 	.max_decode_width 	= 8<<10, 
						.max_decode_height	= 8<<10, 
						.decode_caps 		= LX_MJPEG_DECODE_CAPS_NONE },
	},

	[1] = { .chip = LX_CHIP_H13,
			.cfg  = { 	.max_decode_width 	= 8<<10, 
						.max_decode_height	= 8<<10, 
						.decode_caps 		= LX_MJPEG_DECODE_CAPS_NONE },
	},
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
LX_MJPEG_CFG_T*	MJPEG_GetCfg( void )
{
	int	i;
	int num_cfg = NELEMENTS( g_mjpeg_cfg_table );

	for ( i=0; i<num_cfg; i++ )
	{
		if ( !LX_COMP_CHIP( lx_chip_rev(), g_mjpeg_cfg_table[i].chip ) )
		{
			return &(g_mjpeg_cfg_table[i].cfg);
		}
	}
	return NULL;
}

/** @} */

