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



/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#ifndef _FRC_IPC_TYPE_h
#define _FRC_IPC_TYPE_h

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
/**
 * @brief IPC command list
 */
typedef enum {
	FRC_IPC_INIT = 0xf0000000, ///< Initialize frc module
	FRC_IPC_RESET_SW,
	FRC_IPC_IS_STABLE,
	FRC_IPC_SET_MEMC,
	FRC_IPC_SET_MEMC_TYPE,
	FRC_IPC_SET_TRUEMOTION_DEMO,
	FRC_IPC_SET_TRUEMOTION_DEMO_BAR,
	FRC_IPC_SET_SCAN_DIRECTION,
	FRC_IPC_SET_FREEZE,
	FRC_IPC_SET_OSD_CONTROL,
	FRC_IPC_SET_SPREAD_SPECTRUM,
	FRC_IPC_SET_PWM_DUTY_CYCLE,
	FRC_IPC_SET_PWM_CONTROL,
	FRC_IPC_SET_LOW_DELAY_MODE,
	FRC_IPC_SET_DISPLAY_OUTPUT,
	FRC_IPC_SET_FHD_MODE,
	FRC_IPC_SET_RGBYUV_MODE,
	FRC_IPC_SET_DISPLAY_MUTE,
	FRC_IPC_GET_FIRMWARE_VERSION,
	FRC_IPC_SET_JUDDER_LEVEL,
	FRC_IPC_SET_BLUR_LEVEL,
	FRC_IPC_REG_RD,
	FRC_IPC_REG_WR,
//	FRC_IPC_SET_3D_MODE,
	FRC_IPC_CMD_MAX, ///< Maximum number for IPC communication between MCU and CPU
} FRC_IPC_CMD_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif
/**  @} */
