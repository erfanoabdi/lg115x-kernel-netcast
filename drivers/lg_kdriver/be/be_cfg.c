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
 *  main configuration file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.02.07
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
#include "be_cfg.h"
#include "os_util.h"

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
BE_MEM_CFG_T gMemCfgBe[] = 
{
	{
		{
			{	"fw_frc",	0x97000000,	0x00080000	},
			{	"fw_sre",	0x00000000,	0x00100000	},
			{	"fw_wcg", 0x00000000,	0x00020000	},
			{	"fw_led",	0x00000000,	0x00040000	},
			{	"fw_hdr",	0x00000000,	0x00020000	},
			{	"fw_ipc",	0x00000000,	0x00100000	}
		},
		.frame_name = "BE_FRM",
		.frame_base = 0x00000000,
		.frame_size = 0x08D00000
	}
};

BE_MEM_CFG_T *gpBeMem;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void BE_InitCfg ( void )
{
	if( lx_chip_rev() >= LX_CHIP_REV(H13,B0) )
	{
		gpBeMem = &gMemCfgBe[0];
	}
	else
	{
		gpBeMem = &gMemCfgBe[0];
	}
}

/** @} */

