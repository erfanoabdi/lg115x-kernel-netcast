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
 * date       2011.02.17
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef  DE_REG_H13_INC
#define  DE_REG_H13_INC

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
int DE_REG_H13_InitPHY2VIRT(void);
int DE_REG_H13_FreePHY2VIRT(void);
int DE_REG_H13_InitAddrSwitch(void);
int DE_IPC_H13_WakeUpReg(VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_H13_GetStatusReg(VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_H13_WakeUpReg(BOOLEAN turnOn);
int DE_DMA_H13_WakeUpReg(BOOLEAN turnOn);
UINT32 DE_REG_H13_RD(UINT32 addr);
int DE_REG_H13_WD(UINT32 addr, UINT32 value);
int DE_REG_H13_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_H13_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_H13_CheckIrq4Vsync(void);
int DE_REG_H13_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_H13_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_H13_GetCviCsc(LX_DE_CVI_CSC_T *pstParams);
int DE_REG_H13_SetCviCsc(LX_DE_CVI_CSC_T *pstParams);
int DE_REG_H13_GetPostCsc(LX_DE_POST_CSC_T *pstParams);
int DE_REG_H13_SetPostCsc(LX_DE_POST_CSC_T *pstParams);
int DE_REG_H13_GetMviColorimetry(LX_DE_MVI_COLORIMETRY_T *pstParams);
int DE_REG_H13_SetSpread(LX_DE_SET_SPREAD_T *pstParams);
int DE_REG_H13_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_H13_GetFrRate(LX_DE_FR_RATE_T *pstParams);
int DE_REG_H13_SetDeinterlace(BOOLEAN bEnable);
int DE_REG_H13_SetInputSrc(LX_DE_SET_INPUT_T *pstParams);
int DE_REG_H13_SetInSrc(LX_DE_INPUT_CFG_T *pstParams);
int DE_REG_H13_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);

int DE_REG_H13_OIF_Init(LX_DE_OIF_INFO_T *pstParams);
int DE_REG_H13_OIF_GetInfo(LX_DE_OIF_INFO_T *pstParams);
int DE_REG_H13_OIF_SelectOutCh(LX_DE_OIF_OUTPUT_CH_T *pstParams);
int DE_REG_H13_OIF_SetLvdsOutput(BOOLEAN *pstParams);
int DE_REG_H13_OIF_SetLvdsPower(BOOLEAN *pstParams);
int DE_REG_H13_OIF_SetDarkScreen(BOOLEAN *pstParams);
int DE_REG_H13_OIF_SetVesaJeida(LX_DE_OIF_STD_T *pstParams);
int DE_REG_H13_OIF_SetPanelIf(LX_DE_OIF_PANEL_IF_T *pstParams);
int DE_REG_H13_OIF_SetPixel(LX_DE_OIF_PIXEL_T *pstParams);
int DE_REG_H13_OIF_SetBitDepth(LX_DE_OIF_BIT_DEPTH_T *pstParams);
int DE_REG_H13_OIF_SelectOutPath(LX_DE_OIF_OUTPUT_PATH_T *pstParams);
int DE_REG_H13_OIF_SelectLvdsPath(LX_DE_OIF_LVDS_PATH_T *pstParams);
int DE_REG_H13_OIF_SelectLedPath(LX_DE_OIF_LED_IN_PATH_T *pstParams);
int DE_REG_H13_OIF_SelectPwmPath(LX_DE_OIF_PWM_PATH_T *pstParams);
int DE_REG_H13_OIF_SelectLrPath(LX_DE_OIF_LR_PATH_T *pstParams);
int DE_REG_H13_OIF_SetLvdsOutCtrl(LX_DE_OIF_LVDS_OUT_CTRL_T *pstParams);
int DE_REG_H13_OIF_SetLvdsPortSwap(BOOLEAN *pstParams);

int DE_REG_H13_SetTable(LX_DE_SET_TABLE_T *pstParams);

int DE_REG_H13_GPIO_Init(void);
int DE_REG_H13_HDMI_Init(void);
int DE_REG_H13_LVDS_Init(void);
int DE_REG_H13_MISC_Init(void);
int DE_REG_H13_OSD_Init(void);
int DE_REG_H13_Uart0_Switch(int whichUart);
int DE_REG_H13_OIF_InitLvdsIfCtrl(void);
int DE_REG_H13_VSPMute(BOOLEAN turnOn);


#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_H13_FW_Download(LX_DE_FW_DWLD_T *pstParams);
#endif

int DE_REG_H13_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_H13_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_H13_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_H13_SetCviSyncReshape(LX_DE_CVI_SYNC_RESHAPE_T *pstParams);
int DE_REG_H13_SetPeTestPatternGen(LX_DE_PE_TPG_T *pstParams);
int DE_REG_H13_SetPeBbdCtrl(LX_DE_PE_BBD_CTRL_T *pstParams);
int DE_REG_H13_GetPeBbdStatus(LX_DE_PE_COORDINATE_T *pstParams);
int DE_REG_H13_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_H13_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_H13_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_H13_IPCisAlive(void);
int DE_REG_H13_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_H13_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_H13_GrabPixel(LX_DE_GRAB_PIXEL_T *pstParams);
int DE_REG_H13_GetCviInfo(LX_DE_CVI_INFO_T *pstParams);
int DE_REG_H13_Set3DFullMode(LX_DE_3D_FULL_MODE_T *pstParams);
int DE_REG_H13_SetUdMode(BOOLEAN *pstParams);
int DE_REG_H13_SetLAMode(BOOLEAN *pstParams);
int DE_REG_H13_SetFrameToOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams);
int DE_REG_H13_GetFrameForOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams);

int DE_REG_H13_SetMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_H13_GetDebug(LX_DE_SET_DBG_T *pstParams);
int DE_REG_H13_SetDebug(LX_DE_SET_DBG_T *pstParams);

int DE_REG_H13_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams);
int DE_REG_H13_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams);
int DE_REG_H13_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams);
int DE_REG_H13_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams);
int DE_REG_H13_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_H13_INC  ----- */
/**  @} */
