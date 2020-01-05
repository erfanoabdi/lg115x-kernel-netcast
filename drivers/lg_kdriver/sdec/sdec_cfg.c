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
 *  main configuration file for sdec device
 *  sdec device will teach you how to make device driver with new platform.
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

#include "sdec_cfg.h"
#include "os_util.h"

/*------------
----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
LX_SDEC_MEM_CFG_T gMemCfgSDECGPB[] =
{
	[0] = // for LG1150
	{
		.memory_name				= "sdec_gpb",
		.gpb_memory_base			= 0x00000000,
		.gpb_memory_size			= 0x00300000
	},
	[1] = // for LG1152
	{
		.memory_name				= "sdec_gpb",
		.gpb_memory_base			= 0x00000000, //0x7B4E4000,
#if (KDRV_PLATFORM == KDRV_COSMO_PLATFORM)	// GCD
		.gpb_memory_size			= 0x00800000
#else		// NetCast
		.gpb_memory_size			= 0x00900000
#endif
	}
};

/* L8 B0 ~ L9 A1 */
LX_SDEC_CHA_INFO_T gSdecChannelCfg_0[] =
{
	// A
	{
		.capa_lev	= 1,	//* Full feature channel */
		.num_pidf	= 64, 	//* # of pid filter */
		.num_secf	= 64, 	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// B
	{
		.capa_lev	= 1,	//* Full feature channel */
		.num_pidf	= 64,	//* # of pid filter */
		.num_secf	= 64,	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// C
	{
		.capa_lev	= 0,	//* simple channel, just for channel browser */
		.num_pidf	= 1,	//* # of pid filter */
		.num_secf	= 0,	//* # of section filter */
		.flt_dept	= 0,	//* depth of section filter mask */
	},
};

/* L9 B0 ~ */
LX_SDEC_CHA_INFO_T gSdecChannelCfg_1[] =
{
	// A
	{
		.capa_lev	= 1,	//* Full feature channel */
		.num_pidf	= 64, 	//* # of pid filter */
		.num_secf	= 64, 	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// B
	{
		.capa_lev	= 1,	//* Full feature channel */
		.num_pidf	= 64,	//* # of pid filter */
		.num_secf	= 64,	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// C
	{
		.capa_lev	= 0,	//* simple channel, just for channel browser */
		.num_pidf	= 1,	//* # of pid filter */
		.num_secf	= 1,	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// D
	{
		.capa_lev	= 0,	//* simple channel, just for all pass recording */
		.num_pidf	= 0,	//* # of pid filter */
		.num_secf	= 0,	//* # of section filter */
		.flt_dept	= 0,	//* depth of section filter mask */
	},
};

/* H13 A0 ~ */
LX_SDEC_CHA_INFO_T gSdecChannelCfg_H13_A0[] =
{
	// A
	{
		.capa_lev	= 1,	//* Full feature channel */
		.num_pidf	= 64, 	//* # of pid filter */
		.num_secf	= 64, 	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// B
	{
		.capa_lev	= 1,	//* Full feature channel */
		.num_pidf	= 64,	//* # of pid filter */
		.num_secf	= 64,	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// C
	{
		.capa_lev	= 0,	//* simple channel, just for SDT Parsing*/
		.num_pidf	= 4,	//* # of pid filter */
		.num_secf	= 4,	//* # of section filter */
		.flt_dept	= 8,	//* depth of section filter mask */
	},
	// D
	{
		.capa_lev	= 0,	//* simple channel, just for all pass recording */
		.num_pidf	= 0,	//* # of pid filter */
		.num_secf	= 0,	//* # of section filter */
		.flt_dept	= 0,	//* depth of section filter mask */
	},
};


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

LX_SDEC_CFG_T	_gSdecCfgs[] =
{
//	{ .chip_rev = LX_CHIP_REV(L9A,A0),	.name = "SDEC L9S A0", 	.nChannel = 3, .nVdecOutPort = 3, 	.memCfg = 1 }, // L9S	A0
#if (KDRV_PLATFORM == KDRV_COSMO_PLATFORM)	// GCD
	{ .chip_rev = LX_CHIP_REV(H13,A0),	.name = "SDEC H13 A0", 	.nChannel = 4, .nVdecOutPort = 3, 	.memCfg = 1,	.noPesBug = 1,	.staticGPB = 1,	.chInfo = gSdecChannelCfg_H13_A0 }, // H13 A0
	{ .chip_rev = LX_CHIP_REV(L9,B2),	.name = "SDEC L9 B2", 	.nChannel = 4, .nVdecOutPort = 3, 	.memCfg = 1,	.noPesBug = 1,	.staticGPB = 0,	.chInfo = gSdecChannelCfg_1 }, // L9	B0
	{ .chip_rev = LX_CHIP_REV(L9,B1),	.name = "SDEC L9 B1", 	.nChannel = 4, .nVdecOutPort = 3, 	.memCfg = 1,	.noPesBug = 1,	.staticGPB = 0,	.chInfo = gSdecChannelCfg_1 }, // L9	B0
	{ .chip_rev = LX_CHIP_REV(L9,B0),	.name = "SDEC L9 B0", 	.nChannel = 4, .nVdecOutPort = 3, 	.memCfg = 1,	.noPesBug = 0,	.staticGPB = 0,	.chInfo = gSdecChannelCfg_1 }, // L9	B0
	{ .chip_rev = LX_CHIP_REV(L9,A1),	.name = "SDEC L9 A1",	.nChannel = 3, .nVdecOutPort = 3,	.memCfg = 1,	.noPesBug = 0,	.staticGPB = 0, .chInfo = gSdecChannelCfg_0 }, // L9	A1
	{ .chip_rev = LX_CHIP_REV(L9,A0),	.name = "SDEC L9 A0",	.nChannel = 3, .nVdecOutPort = 3,	.memCfg = 1,	.noPesBug = 0,	.staticGPB = 0, .chInfo = gSdecChannelCfg_0 }, // L9	A0
#else	// NetCast
	{ .chip_rev = LX_CHIP_REV(H13,A0),	.name = "SDEC H13 A0", 	.nChannel = 4, .nVdecOutPort = 3, 	.memCfg = 1,	.noPesBug = 1,	.staticGPB = 1,	.chInfo = gSdecChannelCfg_H13_A0 }, // H13 A0
	{ .chip_rev = LX_CHIP_REV(L9,B2),	.name = "SDEC L9 B2",	.nChannel = 4, .nVdecOutPort = 3,	.memCfg = 1,	.noPesBug = 1,	.staticGPB = 1, .chInfo = gSdecChannelCfg_1 }, // L9	B0
	{ .chip_rev = LX_CHIP_REV(L9,B1),	.name = "SDEC L9 B1",	.nChannel = 4, .nVdecOutPort = 3,	.memCfg = 1,	.noPesBug = 1,	.staticGPB = 1, .chInfo = gSdecChannelCfg_1 }, // L9	B0
	{ .chip_rev = LX_CHIP_REV(L9,B0),	.name = "SDEC L9 B0",	.nChannel = 4, .nVdecOutPort = 3,	.memCfg = 1,	.noPesBug = 0,	.staticGPB = 1, .chInfo = gSdecChannelCfg_1 }, // L9	B0
	{ .chip_rev = LX_CHIP_REV(L9,A1),	.name = "SDEC L9 A1",	.nChannel = 3, .nVdecOutPort = 3,	.memCfg = 1,	.noPesBug = 0,	.staticGPB = 1, .chInfo = gSdecChannelCfg_0 }, // L9	A1
	{ .chip_rev = LX_CHIP_REV(L9,A0),	.name = "SDEC L9 A0",	.nChannel = 3, .nVdecOutPort = 3,	.memCfg = 1,	.noPesBug = 0,	.staticGPB = 1, .chInfo = gSdecChannelCfg_0 }, // L9	A0
#endif
	{ .chip_rev = LX_CHIP_REV(L8,B0),	.name = "SDEC L8 B0", 	.nChannel = 3, .nVdecOutPort = 2, 	.memCfg = 0,	.noPesBug = 0,	.staticGPB = 1,	.chInfo = gSdecChannelCfg_0}, // L8	B0
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

/**
********************************************************************************
* @brief
*	Get conf which is fit to chip revision
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*  LX_SDEC_CFG_T* : pointer of config structure
********************************************************************************
*/
LX_SDEC_CFG_T* SDEC_CFG_GetConfig(void)
{
	int i, num;

	/* number of configs */
	num = sizeof(_gSdecCfgs) / sizeof(LX_SDEC_CFG_T);

	for ( i = 0 ; i < num ; i++ )
	{
		if(_gSdecCfgs[i].chip_rev == lx_chip_rev())
			return &_gSdecCfgs[i];
	}

	return &_gSdecCfgs[0];
}


/** @} */

