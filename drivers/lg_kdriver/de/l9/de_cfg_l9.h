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
 * date       2011.04.06
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DE_CFG_L9_INC
#define  DE_CFG_L9_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_model.h"
#include "de_cfg_def.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define VIDEO_L9_FRAME_DDR_LW_SCR           1644
#define VIDEO_L9_FRAME_DDR_LW_CAP           688
#define VIDEO_L9_FRAME_DDR_LW_TNR_IPC       1720
#define VIDEO_L9_FRAME_DDR_RW_SCR           1233
#define VIDEO_L9_FRAME_DDR_RW_CAP           548
#define VIDEO_L9_FRAME_DDR_RW_TNR_IPC       1096
#define VIDEO_L9_FRAME_DDR_SW_VCR           444
#define VIDEO_L9_FRAME_DDR_SW_MDI           178

#define VIDEO_L9_CODEC_DDR_BASE             (0x70000000)
#define VIDEO_L9_FRAME_DDR_BASE             (0x80000000)
#define VIDEO_L9_FRAME_FIRMWARE_OFFSET      (0x00000000)

#define VIDEO_L9_ROW2PHY(_r)                (CONV_ROW2BYTE(_r) | VIDEO_L9_FRAME_DDR_BASE)

#define VIDEO_L9_FIRMWARE_ROW_SIZE_OF_DE    (VIDEO_FIRMWARE_ROW_SIZE)
#define VIDEO_L9_FIRMWARE_ROW_SIZE_OF_LED   (VIDEO_FIRMWARE_ROW_SIZE)
#define VIDEO_L9_FIRMWARE_ROW_SIZE_OF_IPC   (VIDEO_FIRMWARE_ROW_SIZE)
#define VIDEO_L9_FIRMWARE_ROW_SIZE_IPC_MC	(1)
#define VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP	(1)
#define VIDEO_L9_FIRMWARE_ROW_SIZE_OF_TTX	(1)
#define VIDEO_L9_FIRMWARE_ROW_SIZE_WEB_OS	(1)
#define VIDEO_L9_FIRMWARE_ROW_SIZE_REG_TR	(1)

#define VIDEO_L9_ROW_SIZE_OF_FRAME_MEMORY   (VIDEO_L9_FRAME_DDR_LW_SCR + VIDEO_L9_FRAME_DDR_LW_CAP + VIDEO_L9_FRAME_DDR_LW_TNR_IPC + VIDEO_L9_FRAME_DDR_RW_SCR + VIDEO_L9_FRAME_DDR_RW_CAP + VIDEO_L9_FRAME_DDR_RW_TNR_IPC + VIDEO_L9_FRAME_DDR_SW_VCR + VIDEO_L9_FRAME_DDR_SW_MDI)

#ifdef USE_DE_FIRMWARE_RUN_IN_PAK
#define VIDEO_L9_FIRMWARE_ROW_BASE_OF_LED	(VIDEO_L9_FRAME_FIRMWARE_OFFSET/VIDEO_ROW_STRIDE)
#define VIDEO_L9_FIRMWARE_ROW_BASE_OF_IPC	(VIDEO_L9_FIRMWARE_ROW_BASE_OF_LED + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_L9_FIRMWARE_ROW_BASE_OF_DE	(VIDEO_L9_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_IPC)
#define VIDEO_L9_START_OF_FRAME_MEMORY		(VIDEO_L9_FIRMWARE_ROW_BASE_OF_DE  + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_DE)
#else
#define VIDEO_L9_FIRMWARE_ROW_BASE_OF_DE	(VIDEO_L9_FRAME_FIRMWARE_OFFSET/VIDEO_ROW_STRIDE)
#define VIDEO_L9_FIRMWARE_ROW_BASE_OF_LED	(VIDEO_L9_FIRMWARE_ROW_BASE_OF_DE  + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_L9_FIRMWARE_ROW_BASE_OF_IPC	(VIDEO_L9_FIRMWARE_ROW_BASE_OF_LED + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_L9_START_OF_FRAME_MEMORY		(VIDEO_L9_FIRMWARE_ROW_BASE_OF_IPC + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_IPC)
#endif

#define VIDEO_L9_FIRMWARE_ROW_BASE_IPC_MC	(VIDEO_L9_FIRMWARE_ROW_BASE_OF_IPC                                    )
#define VIDEO_L9_FIRMWARE_ROW_BASE_DDR_UP	(VIDEO_L9_FIRMWARE_ROW_BASE_IPC_MC + VIDEO_L9_FIRMWARE_ROW_SIZE_IPC_MC)
#define VIDEO_L9_FIRMWARE_ROW_BASE_OF_TTX	(VIDEO_L9_FIRMWARE_ROW_BASE_DDR_UP + VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_L9_FIRMWARE_ROW_BASE_WEB_OS	(VIDEO_L9_FIRMWARE_ROW_BASE_OF_TTX + VIDEO_L9_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_L9_FIRMWARE_ROW_BASE_REG_TR	(VIDEO_L9_FIRMWARE_ROW_BASE_WEB_OS + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_TTX)

#define VIDEO_L9_FIRMWARE_MEM_BASE_OF_DE    VIDEO_L9_ROW2PHY(VIDEO_L9_FIRMWARE_ROW_BASE_OF_DE)
#define VIDEO_L9_FIRMWARE_MEM_BASE_OF_LED   VIDEO_L9_ROW2PHY(VIDEO_L9_FIRMWARE_ROW_BASE_OF_LED)
#define VIDEO_L9_FIRMWARE_MEM_BASE_OF_IPC   VIDEO_L9_ROW2PHY(VIDEO_L9_FIRMWARE_ROW_BASE_OF_IPC)
#define VIDEO_L9_FIRMWARE_MEM_BASE_DDR_UP	VIDEO_L9_ROW2PHY(VIDEO_L9_FIRMWARE_ROW_BASE_DDR_UP)
#define VIDEO_L9_FIRMWARE_MEM_BASE_OF_TTX	VIDEO_L9_ROW2PHY(VIDEO_L9_FIRMWARE_ROW_BASE_OF_TTX)
#define VIDEO_L9_FIRMWARE_MEM_BASE_WEB_OS	VIDEO_L9_ROW2PHY(VIDEO_L9_FIRMWARE_ROW_BASE_WEB_OS)
#define VIDEO_L9_FIRMWARE_MEM_BASE_REG_TR	VIDEO_L9_ROW2PHY(VIDEO_L9_FIRMWARE_ROW_BASE_REG_TR)
#define VIDEO_L9_MBASE_OF_FRAME_MEMORY      VIDEO_L9_ROW2PHY(VIDEO_L9_START_OF_FRAME_MEMORY)

#define VIDEO_L9_FIRMWARE_MEM_SIZE_OF_DE	CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_OF_DE)
#define VIDEO_L9_FIRMWARE_MEM_SIZE_OF_LED	CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_OF_LED)
#define VIDEO_L9_FIRMWARE_MEM_SIZE_OF_IPC	CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_OF_IPC)
#define VIDEO_L9_FIRMWARE_MEM_SIZE_DDR_UP	CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_L9_FIRMWARE_MEM_SIZE_OF_TTX	CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_OF_TTX)
#define VIDEO_L9_FIRMWARE_MEM_SIZE_WEB_OS	CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_L9_FIRMWARE_MEM_SIZE_REG_TR	CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_REG_TR)
#define VIDEO_L9_MEM_SIZE_OF_FRAME_MEMORY   CONV_ROW2BYTE(VIDEO_L9_ROW_SIZE_OF_FRAME_MEMORY)

#define VIDEO_L9_FIRMWARE_ROW_OFST_IPC_MC	(0)
#define VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP	(VIDEO_L9_FIRMWARE_ROW_OFST_IPC_MC + VIDEO_L9_FIRMWARE_ROW_SIZE_IPC_MC)
#define VIDEO_L9_FIRMWARE_ROW_OFST_OF_TTX	(VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP + VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP)
#define VIDEO_L9_FIRMWARE_ROW_OFST_WEB_OS	(VIDEO_L9_FIRMWARE_ROW_OFST_OF_TTX + VIDEO_L9_FIRMWARE_ROW_SIZE_WEB_OS)
#define VIDEO_L9_FIRMWARE_ROW_OFST_REG_TR	(VIDEO_L9_FIRMWARE_ROW_OFST_OF_TTX + VIDEO_L9_FIRMWARE_ROW_SIZE_OF_TTX)

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

#endif   /* ----- #ifndef DE_CFG_L9_INC  ----- */
/**  @} */
