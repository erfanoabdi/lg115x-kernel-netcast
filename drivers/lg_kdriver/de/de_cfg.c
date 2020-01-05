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
 *  main configuration file for de device
 *  de device will teach you how to make device driver with new platform.
 *
 *  author      dongho7.park (dongho7.park@lge.com)
 *  version     1.0
 *  date        2009.12.30
 *  note        Additional information.
 *
 *  @addtogroup lg1150_de
 *  @{
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "de_ver_def.h"
#include "de_cfg.h"
#ifdef USE_KDRV_CODES_FOR_L9
#include "l9/de_cfg_l9.h"
#endif
#ifdef USE_KDRV_CODES_FOR_H13
#include "h13/de_cfg_h13.h"
#endif

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
LX_DE_MEM_CFG_T gMemCfgDe[] =
{
	// for LG1152 A0/B0 real chip.
    {
#ifdef USE_KDRV_CODES_FOR_L9
        {
            {   "fw_de",  VIDEO_L9_FIRMWARE_MEM_BASE_OF_DE,  VIDEO_L9_FIRMWARE_MEM_SIZE_OF_DE  } ,
            {   "fw_led", VIDEO_L9_FIRMWARE_MEM_BASE_OF_LED, VIDEO_L9_FIRMWARE_MEM_SIZE_OF_LED } ,
            {   "fw_ipc", VIDEO_L9_FIRMWARE_MEM_BASE_OF_IPC, VIDEO_L9_FIRMWARE_MEM_SIZE_OF_IPC } ,
        },
        .frame_name = "ddr2",
        .frame_base = VIDEO_L9_MBASE_OF_FRAME_MEMORY,
        .frame_size = VIDEO_L9_MEM_SIZE_OF_FRAME_MEMORY,
#else
	.frame_name = "",
	.frame_base = 0,
	.frame_size = 0
#endif
    },
    
	// for h13 A0/B0 real chip.
    {
#ifdef USE_KDRV_CODES_FOR_H13
        {
#ifdef USE_DE_FIRMWARE_RUN_IN_PAK_H13
            {   "fw_led", VIDEO_H13_FIRMWARE_MEM_BASE_OF_LED, VIDEO_H13_FIRMWARE_MEM_SIZE_OF_LED } ,
            {   "fw_ipc", VIDEO_H13_FIRMWARE_MEM_BASE_OF_IPC, VIDEO_H13_FIRMWARE_MEM_SIZE_OF_IPC } ,
            {   "fw_de",  VIDEO_H13_FIRMWARE_MEM_BASE_OF_DE,  VIDEO_H13_FIRMWARE_MEM_SIZE_OF_DE  } ,
#else
            {   "fw_de",  VIDEO_H13_FIRMWARE_MEM_BASE_OF_DE,  VIDEO_H13_FIRMWARE_MEM_SIZE_OF_DE  } ,
            {   "fw_led", VIDEO_H13_FIRMWARE_MEM_BASE_OF_LED, VIDEO_H13_FIRMWARE_MEM_SIZE_OF_LED } ,
            {   "fw_ipc", VIDEO_H13_FIRMWARE_MEM_BASE_OF_IPC, VIDEO_H13_FIRMWARE_MEM_SIZE_OF_IPC } ,
#endif
        },
        .frame_name = "DE_FRM",
        .frame_base = VIDEO_H13_MBASE_OF_FRAME_MEMORY,
        .frame_size = VIDEO_H13_MEM_SIZE_OF_FRAME_MEMORY,
#else
	.frame_name = "",
	.frame_base = 0,
	.frame_size = 0
#endif
    }
};

LX_DE_CH_MEM_T gMemCfgDePreW[] =
{
    // for h13 A0/B0 real chip.
	{
		.fw_name = "DE_PreW",
		.fw_base = 0x0,
		.fw_size = VIDEO_H13_MEM_SIZE_OF_FRAME_PREW,
	}
};

LX_DE_CH_MEM_T gMemCfgDeGrap[] =
{
    // for h13 A0/B0 real chip.
	{
		.fw_name = "DE_GRAP",
		.fw_base = 0x0,
		.fw_size = VIDEO_H13_MEM_SIZE_OF_FRAME_GRAP + 0x8000, // add 0x8000 for ROW align
	}
};

LX_DE_CH_MEM_T gMemCfgDeFW[] =
{
    // temporal base for h13 B0 real chip.
	{
		.fw_name = "DE_FW_LBUS",
		.fw_base = 0x0,
		.fw_size = (VIDEO_H13_FIRMWARE_MEM_SIZE_OF_DE * 2),
	}
};

//LX_DE_MEM_CFG_T *gpDeMem = &gMemCfgDe[1];   // for FPGA.
LX_DE_MEM_CFG_T *gpDeMem = &gMemCfgDe[0];   // for COSMO.
//LX_DE_MEM_CFG_T *gpDeMem = &gMemCfgDe[2];   // for GP3 L9.

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

