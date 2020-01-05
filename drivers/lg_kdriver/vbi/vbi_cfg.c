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
 *  author		won.hur (won.hur@lge.com)
 *  version		1.0
 *  date		2012.04.18
 *  note		Additional information.
 *
 *  @addtogroup lg115x_vbi
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "vbi_cfg.h"
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

LX_VBI_REG_CFG_T gstVbiRegCfgVBIRev[] =
{
	{
		.vbi_register_name = "L9Bx_TTX_REG",
		.vbi_register_base = 0xc0026000,
		.vbi_register_size = 0x800,
	},
    {
		.vbi_register_name = "H13_VBI_REG",
		.vbi_register_base = 0xc0019000,
		.vbi_register_size = 0x800,
	},
};


LX_VBI_MEM_CFG_T gstBufMemCfgVBIRev[] =
{
	{
		.buf_memory_name = "L9_ttx_memory",
		.buf_memory_base = 0,//0x7BA00000,
		.buf_memory_size = 0x00100000,
	},
    {
		.buf_memory_name = "H13_vbi_memory",
		.buf_memory_base = 0,//0x7BA00000,
		.buf_memory_size = 0x00100000,
	},
};

LX_VBI_MEM_CFG_T* 	gstMemCfgVBI	= NULL;
LX_VBI_REG_CFG_T* 	gstRegCfgVBI	= NULL;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
void    VBI_InitCfg ( void )
{

	/*-----------------------------------------------------------------------------------
	 * [L9] configuration
	 *----------------------------------------------------------------------------------*/
    if( lx_chip_rev( ) >= LX_CHIP_REV(H13, A0) )
    {
		gstMemCfgVBI = &gstBufMemCfgVBIRev[1];
		gstRegCfgVBI = &gstVbiRegCfgVBIRev[1];
    }
	#ifdef INCLUDE_L9_CHIP_KDRV
    else if( lx_chip_rev( ) >= LX_CHIP_REV(L9,B0) )
    {
		gstMemCfgVBI = &gstBufMemCfgVBIRev[0];
		gstRegCfgVBI = &gstVbiRegCfgVBIRev[0];
    }
	#endif
	/*-----------------------------------------------------------------------------------
	 * [L8] configuration
	 *----------------------------------------------------------------------------------*/
    else
    {
    }
}



/** @} */

