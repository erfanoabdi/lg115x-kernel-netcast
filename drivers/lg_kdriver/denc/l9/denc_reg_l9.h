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
 * date       2011.02.25
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DENC_REG_L9_INC
#define  DENC_REG_L9_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DENC_REG_L9_Create(void);
int DENC_REG_L9_Destory(void);
int DENC_REG_L9_Init(void);
int DENC_REG_L9_OnOff ( BOOLEAN *pOnOff );
int DENC_REG_L9_SetOutPutVideoStd(LX_DENC_VIDEO_SYSTEM_T *pstParams);
int DENC_REG_L9_SetSource(LX_DENC_VIDEO_SOURCE_T *pstParams);
int DENC_REG_L9_TtxEnable(BOOLEAN *pstParams);
int DENC_REG_L9_WssEnable(BOOLEAN *pstParams);
int DENC_REG_L9_VpsEnable(BOOLEAN *pstParams);
int DENC_REG_L9_SetTtxData(LX_DENC_TTX_DATA_T *pstParams);
int DENC_REG_L9_SetWssData(LX_DENC_WSS_DATA_T *pstParams);
int DENC_REG_L9_SetVpsData(LX_DENC_VPS_DATA_T *pstParams);
int DENC_REG_L9_ColorBarEnable(BOOLEAN *pstParams);
int DENC_REG_L9_VdacPowerControl(BOOLEAN *pstParams);

int DENC_REG_L9_NTSC_Init(void);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DENC_REG_L9_INC  ----- */
/**  @} */
