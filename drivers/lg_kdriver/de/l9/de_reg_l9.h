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
#ifndef  DE_REG_L9_INC
#define  DE_REG_L9_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_vbi_def.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_PWM_RUN_IN_KDRIVER
#ifndef USE_VIDEO_PWM_DEFINED
#define USE_VIDEO_PWM_DEFINED
typedef enum {
	PWM_NUM_ID0  ,
	PWM_NUM_ID1  ,
	PWM_NUM_ID2  ,
	PWM_NUM_ID3  ,
	PWM_NUM_MAX
} VIDEO_PWM_NUM_T;

typedef enum {
	PWM_ORD_1ST  ,
	PWM_ORD_2ND  ,
	PWM_ORD_3RD  ,
	PWM_ORD_4TH  ,
	PWM_ORD_5TH  ,
	PWM_ORD_6TH  ,
	PWM_ORD_7TH  ,
	PWM_ORD_8TH  ,
	PWM_ORD_MAX
} VIDEO_PWM_ORD_T;

typedef enum {
	PWM_FREQ_60HZ  ,
	PWM_FREQ_120HZ ,
	PWM_FREQ_240HZ ,
	PWM_FREQ_480HZ ,
	PWM_FREQ_MAX
} VIDEO_PWM_FREQ_T;

typedef enum {
	PWM_FREE_OFF ,
	PWM_FREE_ON  ,
	PWM_FREE_MAX
} VIDEO_PWM_FREE_T;

typedef enum {
	PWM_RES_256   ,
	PWM_RES_512   ,
	PWM_RES_1024  ,
	PWM_RES_MAX
} VIDEO_PWM_RES_T;

typedef enum {
	PWM_MODE_DUTY	,
	PWM_MODE_WIDTH	,
	PWM_MODE_MAX
} VIDEO_PWM_MODE_T;

typedef enum {
	PWM_CTRL_ENB ,
	PWM_CTRL_FRQ ,
	PWM_CTRL_FRE ,
	PWM_CTRL_RES ,
	PWM_CTRL_INV ,
	PWM_CTRL_MOD ,
	PWM_CTRL_POS ,
	PWM_CTRL_LOW ,
	PWM_CTRL_HIG ,
	PWM_CTRL_WDH ,
	PWM_CTRL_MSK ,
	PWM_CTRL_MAX
} VIDEO_PWM_CTRL_TYPE_T;

typedef struct {
	UINT32 pwm_x_f_v;// : 14;	// 13: 0
	UINT32 pwm_x_r_v;// : 14;	// 27:14
	UINT32 pwm_v_id ;// : 3;	// 30:28
	UINT32 pwm_v_we ;// : 1;	//	  31
} VIDEO_PWM_TIMING_T;

typedef struct {
	UINT32 pwm_en		;//: 1;	//	   0
	UINT32 pwm_freq_mode;//: 2;	//	2: 1
	UINT32 pwm_method	;//: 1;	//	   3
	UINT32 pwm_resolution;//: 2;	//	5: 4
	UINT32 pwm_inv		;//: 1;	//	   6
	UINT32 pwm_sel		;//: 1;	//	   7
	UINT32 pwm_width_falling_pos;//22;	// 29: 8
	UINT32 pwm_fc_h_disp;//: 1;	//	  30
	UINT32 pwm_fc_l_disp;//: 1;	//	  31
} VIDEO_PWM_CTRL_T;

typedef struct {
	UINT32 pwm_intr_mask        ;   //  0: 7
	UINT32 pwm_free_width       ;  //  8:29
} VIDEO_PWM_CTRL1_T;

typedef struct {
	UINT32             unit;
	UINT32             ordr;
	UINT32             pxls;
	UINT32             free;
	UINT32			   mask;
	UINT32			   wdth;
	VIDEO_PWM_CTRL_T   ctrl;
	VIDEO_PWM_CTRL1_T  ctl1;
	VIDEO_PWM_TIMING_T t1st;
	VIDEO_PWM_TIMING_T t2nd;
	UINT32             duty;
	UINT32             offs;
	UINT32             freq;
} DE_PWM_INFO_T;

typedef struct {
	UINT32             pwm_0_low;
	UINT32             pwm_0_high;
	UINT32             pwm_1_low;
	UINT32             pwm_1_high;
	UINT32             pwm_2_low;
	UINT32             pwm_2_high;
	UINT32             pwm_3_low;
	UINT32             pwm_3_high;
} DE_PWM_RX_INFO_T;
#endif
#endif

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_L9_InitPHY2VIRT(void);
int DE_REG_L9_FreePHY2VIRT(void);
int DE_REG_L9_InitAddrSwitch(void);
int DE_IPC_L9_WakeUpReg(VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn);
int DE_IPC_L9_GetStatusReg(VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int DE_WDG_L9_WakeUpReg(BOOLEAN turnOn);
int DE_DMA_L9_WakeUpReg(BOOLEAN turnOn);
UINT32 DE_REG_L9_RD(UINT32 addr);
int DE_REG_L9_WD(UINT32 addr, UINT32 value);
int DE_REG_L9_SetBgColor(LX_DE_COLOR_T *pBackColor);
int DE_REG_L9_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank);

BOOLEAN DE_REG_L9_CheckIrq4Vsync(void);
int DE_REG_L9_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
int DE_REG_L9_Init(LX_DE_PANEL_TYPE_T *pstParams);
int DE_REG_L9_GetCviCsc(LX_DE_CVI_CSC_T *pstParams);
int DE_REG_L9_SetCviCsc(LX_DE_CVI_CSC_T *pstParams);
int DE_REG_L9_GetPostCsc(LX_DE_POST_CSC_T *pstParams);
int DE_REG_L9_SetPostCsc(LX_DE_POST_CSC_T *pstParams);
int DE_REG_L9_GetMviColorimetry(LX_DE_MVI_COLORIMETRY_T *pstParams);
int DE_REG_L9_SetSpread(LX_DE_SET_SPREAD_T *pstParams);
int DE_REG_L9_SetFrRate(DE_DPLL_CLK_T dclk);
int DE_REG_L9_GetFrRate(LX_DE_FR_RATE_T *pstParams);
int DE_REG_L9_SetDeinterlace(BOOLEAN bEnable);
int DE_REG_L9_SetInputSrc(LX_DE_SET_INPUT_T *pstParams);
int DE_REG_L9_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams);

int DE_REG_L9_OIF_Init(LX_DE_OIF_INFO_T *pstParams);
int DE_REG_L9_OIF_GetInfo(LX_DE_OIF_INFO_T *pstParams);
int DE_REG_L9_OIF_SelectOutCh(LX_DE_OIF_OUTPUT_CH_T *pstParams);
int DE_REG_L9_OIF_SetLvdsOutput(BOOLEAN *pstParams);
int DE_REG_L9_OIF_SetLvdsPower(BOOLEAN *pstParams);
int DE_REG_L9_OIF_SetDarkScreen(BOOLEAN *pstParams);
int DE_REG_L9_OIF_SetVesaJeida(LX_DE_OIF_STD_T *pstParams);
int DE_REG_L9_OIF_SetPanelIf(LX_DE_OIF_PANEL_IF_T *pstParams);
int DE_REG_L9_OIF_SetPixel(LX_DE_OIF_PIXEL_T *pstParams);
int DE_REG_L9_OIF_SetBitDepth(LX_DE_OIF_BIT_DEPTH_T *pstParams);
int DE_REG_L9_OIF_SelectOutPath(LX_DE_OIF_OUTPUT_PATH_T *pstParams);
int DE_REG_L9_OIF_SelectLvdsPath(LX_DE_OIF_LVDS_PATH_T *pstParams);
int DE_REG_L9_OIF_SelectLedPath(LX_DE_OIF_LED_IN_PATH_T *pstParams);
int DE_REG_L9_OIF_SelectPwmPath(LX_DE_OIF_PWM_PATH_T *pstParams);
int DE_REG_L9_OIF_SelectLrPath(LX_DE_OIF_LR_PATH_T *pstParams);
int DE_REG_L9_OIF_SetLvdsOutCtrl(LX_DE_OIF_LVDS_OUT_CTRL_T *pstParams);
int DE_REG_L9_OIF_SetLvdsPortSwap(BOOLEAN *pstParams);

int DE_REG_L9_SetTable(LX_DE_SET_TABLE_T *pstParams);

int DE_REG_L9_GPIO_Init(void);
int DE_REG_L9_HDMI_Init(void);
int DE_REG_L9_LVDS_Init(void);
int DE_REG_L9_MISC_Init(void);
int DE_REG_L9_OSD_Init(void);
int DE_REG_L9_Uart0_Switch(int whichUart);
int DE_REG_L9_OIF_InitLvdsIfCtrl(void);
int DE_REG_L9_VSPMute(BOOLEAN turnOn);


#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_L9_FW_Download(LX_DE_FW_DWLD_T *pstParams);
#endif

int DE_REG_L9_SetCviFir(LX_DE_CVI_FIR_T *pstParams);
int DE_REG_L9_SetCviTpg(LX_DE_CVI_TPG_T *pstParams);
int DE_REG_L9_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams);
int DE_REG_L9_SetCviSyncReshape(LX_DE_CVI_SYNC_RESHAPE_T *pstParams);
int DE_REG_L9_SetPeTestPatternGen(LX_DE_PE_TPG_T *pstParams);
int DE_REG_L9_SetPeBbdCtrl(LX_DE_PE_BBD_CTRL_T *pstParams);
int DE_REG_L9_GetPeBbdStatus(LX_DE_PE_COORDINATE_T *pstParams);
int DE_REG_L9_SetEdgeCrop(BOOLEAN *pstParams);
int DE_REG_L9_SetVcs(LX_DE_VCS_IPC_T *pstParams);
int DE_REG_L9_ResetDE(BOOLEAN bReset);
BOOLEAN DE_REG_L9_IPCisAlive(void);
int DE_REG_L9_SetPwmControl(LX_DE_PWM_CTRL_T *pstParams);
int DE_REG_L9_SetPwmDutyCycle(LX_DE_PWM_PARAM_T *pstParams);
int DE_REG_L9_GetPwmDutyCycle(LX_DE_EXTERNAL_PWM_T *pstParams);
int DE_REG_L9_SetPwmFrequency(LX_DE_PWM_FREQ_T *pstParams);
int DE_REG_L9_SetPwmPulseWidth(LX_DE_PWM_PULSE_T *pstParams);
int DE_REG_L9_SetPwmFreerun(void);
int DE_REG_L9_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams);
int DE_REG_L9_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_L9_Set_SCART_RGB_Bypass_Mode(int Bypass_Enable);
int DE_REG_L9_GrabPixel(LX_DE_GRAB_PIXEL_T *pstParams);
int DE_REG_L9_GetCviInfo(LX_DE_CVI_INFO_T *pstParams);
int DE_REG_L9_Set3DFullMode(LX_DE_3D_FULL_MODE_T *pstParams);
int DE_REG_L9_SetUdMode(BOOLEAN *pstParams);
int DE_REG_L9_SetLAMode(BOOLEAN *pstParams);
int DE_REG_L9_SetFrameToOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams);

int DE_REG_L9_SetCviSrc(void);
int DE_REG_L9_SetMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams);
int DE_REG_L9_GetDebug(LX_DE_SET_DBG_T *pstParams);
int DE_REG_L9_SetDebug(LX_DE_SET_DBG_T *pstParams);
int DE_REG_L9_SetTtx(VIDEO_TTX_PACK_T *pTtxPack);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_L9_INC  ----- */
/**  @} */
