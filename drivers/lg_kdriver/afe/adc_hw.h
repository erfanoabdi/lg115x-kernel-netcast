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
 *	ADC hw control
 *
 *  author      sinchul.jung (sinchul.jung@lge.com)
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg1150_afe
 *  @{
 */

#ifndef	_ADC_HW_H_
#define	_ADC_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define __ARM__

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C"
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define ADC_DETECTION_INTERRUPT_MASK	0x0000068A
#define ADC_PERIODIC_SIGNAL_INFO_READ

//#define L8_PHASE_NOISE_WORKAROUND
//#define L8_COMP_HSYNC_PHASE_SEARCH
//#define ADC_SOG_LVL_WORKAROUND

#define ADC_L9_R_PRE_OFFSET_VALUE	0x800
#define ADC_L9_G_PRE_OFFSET_VALUE	0x800
#define ADC_L9_B_PRE_OFFSET_VALUE	0x800

#define	SUPPORT_SCART_RGB_ULTRA_BLACK

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
#define	SCART_RGB_OFFSET_ADD	0x4C	//16 level added
#endif

/*----------------------------------------------------------------------------------------
    Type Definitions (enum)
----------------------------------------------------------------------------------------*/

typedef struct{
	unsigned int height_offset;
	unsigned int width_offset;
	unsigned int control;
	unsigned int level;
}S_EXTAU_VALUE;

typedef struct{
	unsigned int port;
	bool hsselover;
	bool hsseluser;
	bool vsselover;
	bool vsseluser;
	bool compover;
	bool compuser;
}S_SEL_PORT;

typedef struct{
	unsigned int out_b;
	unsigned int out_g;
	unsigned int out_r;

}S_RGB_OUT;

typedef struct{
	unsigned int	sum_R;
	unsigned int	sum_G;
	unsigned int	sum_B;
}S_RGB_SUM;


typedef struct{
	unsigned int width_b;
	unsigned int width_g;
	unsigned int width_r;

	unsigned int height_b;
	unsigned int height_g;
	unsigned int height_r;
}S_RGB_SIZE;

typedef struct{
	unsigned int width_b;
	unsigned int width_g;
	unsigned int width_r;

	unsigned int height_b;
	unsigned int height_g;
	unsigned int height_r;
}S_RGB_POSITION;

typedef enum
{
	IRE0	= 0,
	IRE73	= 1,
	IRE950	= 2,
	IRE1023	= 3,
	IRE0_RGB	=4,
	IRE0_COMP	=5
} E_AGC_IRE;

typedef enum
{
	IRE73_L9	= 0,
	IRE146_L9	= 1,
	IRE877_L9	= 2,
	IRE950_L9	= 3,
	IRE0_RGB_L9		=4,
	IRE0_COMP_L9	=5
} E_AGC_IRE_L9;

typedef struct{
	unsigned int	gain_R;
	unsigned int	gain_G;
	unsigned int	gain_B;
}ST_GAIN_INFORM;


typedef struct{
	//120103 wonsik.do : removed floating point in kernel driver
//	float gain_R;
//	float gain_G;
//	float gain_B;
	UINT64 gain_R;
	UINT64 gain_G;
	UINT64 gain_B;
} S_GAIN_TARGET;

typedef struct{
	int offset_R;
	int offset_G;
	int offset_B;

} S_OFFSET_INFORM;

typedef struct {
	int r_blank_target_value;
	int g_blank_target_value;
	int b_blank_target_value;
	int width;
	int r_shift_value;
	int g_shift_value;
	int b_shift_value;
} S_BLANK_INFORM;


typedef enum
{
	ADC_SEPERATED_SYNC_MODE,
	ADC_COMPOSITE_SYNC_MODE,
	ADC_SYNC_MODE_UNKNOWN
} ADC_SYNC_MODE;

typedef enum
{
	ADC_MUTE_CTRL_NORMAL 	= 0x0,
	ADC_MUTE_CTRL_MUTE		= 0x1,
	ADC_MUTE_CTRL_AUTO		= 0x2,
}	ADC_MUTE_CTRL;
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

// Function pointer
extern int (*ADC_PowerOn)(void);
extern int (*ADC_PowerOff)(void);
extern int (*ADC_InitDaughterBoard)(void);
extern int (*ADC_GetBoundaryInform)(ST_EXTAU *inform);
extern int (*ADC_SetTAUInform)(S_EXTAU_VALUE *value);
extern int (*ADC_SetRGBPosition)(S_RGB_POSITION *pos);
extern int (*ADC_GetRGBResult)(S_RGB_OUT *result);
extern int (*ADC_GetRGBPosition)(S_RGB_POSITION *pos);
extern int (*ADC_SetRGBSize)(S_RGB_SIZE *size);
extern int (*ADC_GetSizeValue)(S_VIDEO_SIZE_INFORM *size);
extern int (*ADC_SetPort)(S_SEL_PORT *sel_port);
extern unsigned int (*ADC_GetPhaseValue)(void);
extern int (*ADC_SetPhaseValue)(unsigned int phase);
extern unsigned int (*ADC_GetScanType)(void);
extern int (*ADC_SetGainValue)(LX_AFE_ADC_GAIN_VALUE_T *stGain);
extern int (*ADC_GetGainValue)(LX_AFE_ADC_GAIN_VALUE_T *stGain);
extern int (*ADC_SetOffsetValue)(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
extern int (*ADC_GetOffsetValue)(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
extern int (*ADC_SetInputVideo)(int iIndex);
extern int (*ADC_Enable_Scart_Mode)(BOOLEAN scart_enable);
extern void (*ADC_Vport_ALL_Power_Down)(void);
extern int (*ADC_Channel_Power_Control)(int vref_pdb, int bpdb, int gpdb, int rpdb);
extern int (*ADC_SetType)(LX_AFE_ADC_INPUT_SOURCE_TYPE_T sel_type);
extern int (*ADC_Set_LLPLL)(UINT32 arg);
extern int (*ADC_SetClock)(int iIndex, SINT16 value);
extern int (*ADC_AGOCInit)(void);
extern int (*ADC_GetSelectedPort)(void);
extern int (*ADC_SetGainRGB)( ST_GAIN_INFORM *gain);
extern int (*ADC_GetGainRGB)( ST_GAIN_INFORM *gain);
extern int (*ADC_SetIRELevel)(E_AGC_IRE ire , S_GAIN_TARGET *gain);
extern int (*ADC_GetOffsetRGB)( S_OFFSET_INFORM *offset);
extern int (*ADC_SetOffsetRGB)( S_OFFSET_INFORM *offset);
extern int (*ADC_GetSumRGB)(S_RGB_SUM *sum);
extern int (*ADC_SetAgocWakeup)(void);
extern int (*ADC_Reset_Digital)(void);
extern int (*ADC_Reset_Digital_24MHZ)(void);
extern int (*ADC_Reset_LLPLL)(void);
extern int (*ADC_Check_Sync_Exist)(void);
extern int (*ADC_Sync_Polarity_Override)(int set);
extern int (*ADC_Enable_Detection_Interrupt)(int enable);
extern int (*ADC_Enable_AOGC_Interrupt)(int enable);
extern int (*ADC_Mute_Enable)(int enable);
extern int (*ADC_Power_OnOff)(void);
extern int (*ADC_Ext_Clamp)(int sel_ext);
extern int (*ADC_Set_Clamp)(UINT8 clamp_base, UINT8 clamp_place, UINT8 clamp_width);
extern int (*ADC_GetPCModeInfo)(LX_AFE_PCMODE_INFO_T *stPCModeInfo);
extern int (*ADC_Get_LLPLL_Filter_Status)(void);
extern int (*ADC_SetIRETestMode)(int sel , E_AGC_IRE mode);
extern int (*ADC_Set_Coast)(UINT8 precoast, UINT8 postcoast);
extern int (*ADC_Set_Hsync_Sel)(UINT8 select);
extern int (*ADC_CVI_Sync_Exist)(void);
extern int (*ADC_Set_SOG_Level)(UINT32 level);
extern int (*ADC_Get_SOG_Level)(UINT32 *level);
extern int (*ADC_Check_Htotal_Diff)(UINT8 count, int Kadp_Index);
extern int (*ADC_Read_Pixel_Value)(LX_AFE_ADC_PIXEL_VALUE_T *pixel_value_t);
extern int (*ADC_Green_Mid_Level_Select)(UINT8 value);
extern int (*ADC_Read_VSync_Width)(UINT32 *pvs_width);
extern int (*ADC_Read_HSync_Width)(UINT32 *pvs_width);
extern void (*ADC_Set_Blank)(int blank_sp); // added by won.hur(won.hur@lge.com) @2011.08.17
extern void (*ADC_LVDS_Control)(int enable); // added by won.hur(won.hur@lge.com) @2011.08.17
extern int (*ADC_Component_APA)(int iIndex);
extern int (*ADC_Component_APA_Test)(UINT32 ADC_APA_Delay, UINT32 ADC_APA_Enable, UINT32 ADC_APA_Same_Count, UINT32 ADC_APA_Execute, UINT32 ADC_APA_Enable_Print);
extern int (*ADC_Get_Vtotal_Value)(void);
extern int (*ADC_Set_Sync_Mode)(ADC_SYNC_MODE sync_mode);
extern int (*ADC_LVDS_Channel_Enable_Control)(int enable);
extern int (*ADC_Mute_Control)(ADC_MUTE_CTRL adc_mute_control);
extern int (*ADC_Post_Gain_Control)(int percent);
extern int (*ADC_Set_Comp_Params)(int width, int progressive, int v_freq);
extern int (*ADC_Read_Sync_Low_Level)(void);
extern int (*ADC_Enable_Sync_Low_Level_Read)(int enable);
extern int (*ADC_Check_LLPLL_status)(void);
extern int (*ADC_LVDS_Src_Control)(LX_AFE_LVDS_SRC_CONTROL_T *pLVDS_Control_t);
extern int (*ADC_Read_ACE_Reg)(UINT32 addr , UINT32 *value);
extern int (*ADC_Write_ACE_Reg)(UINT32 addr , UINT32 value);
#ifdef	KDRV_CONFIG_PM
extern int (*ADC_RunSuspend)(void);
extern int (*ADC_RunResume)(void);
#endif


// Ax function prototype
int ADC_PowerOn_Ax(void);
int ADC_PowerOff_Ax(void);
int ADC_InitDaughterBoard_Ax(void);
int ADC_GetBoundaryInform_Ax(ST_EXTAU *inform);
int ADC_SetTAUInform_Ax(S_EXTAU_VALUE *value);
int ADC_SetRGBPosition_Ax(S_RGB_POSITION *pos);
int ADC_GetRGBResult_Ax(S_RGB_OUT *result);
int ADC_GetRGBPosition_Ax(S_RGB_POSITION *pos);
int ADC_SetRGBSize_Ax(S_RGB_SIZE *size);
int ADC_GetSizeValue_Ax(S_VIDEO_SIZE_INFORM *size);
int ADC_SetPort_Ax(S_SEL_PORT *sel_port);
unsigned int ADC_GetPhaseValue_Ax(void);
int ADC_SetPhaseValue_Ax(unsigned int phase);
unsigned int ADC_GetScanType_Ax(void);
int ADC_SetGainValue_Ax(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_GetGainValue_Ax(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_SetOffsetValue_Ax(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
int ADC_GetOffsetValue_Ax(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
int ADC_SetInputVideo_Ax(int iIndex);
int ADC_Enable_Scart_Mode_Ax(BOOLEAN scart_enable);
void ADC_Vport_ALL_Power_Down_Ax(void);
int ADC_Channel_Power_Control_Ax(int vref_pdb, int bpdb, int gpdb, int rpdb);
int ADC_SetType_Ax(LX_AFE_ADC_INPUT_SOURCE_TYPE_T sel_type);
int ADC_Set_LLPLL_Ax(UINT32 arg);
int ADC_SetClock_Ax(int iIndex, SINT16 value);
int ADC_AGOCInit_Ax(void);
int ADC_GetSelectedPort_Ax(void);
int ADC_SetGainRGB_Ax( ST_GAIN_INFORM *gain);
int ADC_GetGainRGB_Ax( ST_GAIN_INFORM *gain);
int ADC_SetIRELevel_Ax(E_AGC_IRE ire , S_GAIN_TARGET *gain);
int ADC_GetOffsetRGB_Ax( S_OFFSET_INFORM *offset);
int ADC_SetOffsetRGB_Ax( S_OFFSET_INFORM *offset);
int ADC_GetSumRGB_Ax(S_RGB_SUM *sum);
int ADC_SetAgocWakeup_Ax(void);
int ADC_Reset_Digital_Ax(void);
int ADC_Reset_Digital_24MHZ_Ax(void);
int ADC_Reset_LLPLL_Ax(void);
int ADC_Check_Sync_Exist_Ax(void);
int ADC_Sync_Polarity_Override_Ax(int set);
int ADC_Enable_Detection_Interrupt_Ax(int enable);
int ADC_Enable_AOGC_Interrupt_Ax(int enable);
int ADC_Mute_Enable_Ax(int enable);
int ADC_Power_OnOff_Ax(void);
int ADC_Ext_Clamp_Ax(int sel_ext);
int ADC_Set_Clamp_Ax(UINT8 clamp_base, UINT8 clamp_place, UINT8 clamp_width);
int ADC_GetPCModeInfo_Ax(LX_AFE_PCMODE_INFO_T *stPCModeInfo);
int ADC_Get_LLPLL_Filter_Status_Ax(void);
int ADC_Set_Coast_Ax(UINT8 precoast, UINT8 postcoast);
int ADC_SetIRETestMode_Ax(int sel , E_AGC_IRE mode);
int ADC_Set_Hsync_Sel_Ax(UINT8 select);
int ADC_CVI_Sync_Exist_Ax(void);
int ADC_Set_SOG_Level_Ax(UINT32 level);
int ADC_Get_SOG_Level_Ax(UINT32 *level);
int ADC_Check_Htotal_Diff_Ax(UINT8 count, int Kadp_Index);
int ADC_Read_Pixel_Value_Ax(LX_AFE_ADC_PIXEL_VALUE_T *pixel_value_t);
int ADC_Green_Mid_Level_Select_Ax(UINT8 value);
int ADC_Read_VSync_Width_Ax(UINT32 *pvs_width);
int ADC_Read_HSync_Width_Ax(UINT32 *pvs_width);
#ifdef	KDRV_CONFIG_PM
int ADC_RunSuspend_Ax(void);
int ADC_RunResume_Ax(void);
#endif

// Bx function prototype
int ADC_PowerOn_Bx(void);
int ADC_PowerOff_Bx(void);
int ADC_InitDaughterBoard_Bx(void);
int ADC_GetBoundaryInform_Bx(ST_EXTAU *inform);
int ADC_SetTAUInform_Bx(S_EXTAU_VALUE *value);
int ADC_SetRGBPosition_Bx(S_RGB_POSITION *pos);
int ADC_GetRGBResult_Bx(S_RGB_OUT *result);
int ADC_GetRGBPosition_Bx(S_RGB_POSITION *pos);
int ADC_SetRGBSize_Bx(S_RGB_SIZE *size);
int ADC_GetSizeValue_Bx(S_VIDEO_SIZE_INFORM *size);
int ADC_SetPort_Bx(S_SEL_PORT *sel_port);
unsigned int ADC_GetPhaseValue_Bx(void);
int ADC_SetPhaseValue_Bx(unsigned int phase);
unsigned int ADC_GetScanType_Bx(void);
int ADC_SetGainValue_Bx(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_GetGainValue_Bx(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_SetOffsetValue_Bx(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
int ADC_GetOffsetValue_Bx(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
int ADC_SetInputVideo_Bx(int iIndex);
int ADC_Enable_Scart_Mode_Bx(BOOLEAN scart_enable);
void ADC_Vport_ALL_Power_Down_Bx(void);
int ADC_Channel_Power_Control_Bx(int vref_pdb, int bpdb, int gpdb, int rpdb);
int ADC_SetType_Bx(LX_AFE_ADC_INPUT_SOURCE_TYPE_T sel_type);
int ADC_Set_LLPLL_Bx(UINT32 arg);
int ADC_SetClock_Bx(int iIndex, SINT16 value);
int ADC_AGOCInit_Bx(void);
int ADC_GetSelectedPort_Bx(void);
int ADC_SetGainRGB_Bx( ST_GAIN_INFORM *gain);
int ADC_GetGainRGB_Bx( ST_GAIN_INFORM *gain);
int ADC_SetIRELevel_Bx(E_AGC_IRE ire , S_GAIN_TARGET *gain);
int ADC_GetOffsetRGB_Bx( S_OFFSET_INFORM *offset);
int ADC_SetOffsetRGB_Bx( S_OFFSET_INFORM *offset);
int ADC_GetSumRGB_Bx(S_RGB_SUM *sum);
int ADC_SetAgocWakeup_Bx(void);
int ADC_Reset_Digital_Bx(void);
int ADC_Reset_Digital_24MHZ_Bx(void);
int ADC_Reset_LLPLL_Bx(void);
int ADC_Check_Sync_Exist_Bx(void);
int ADC_Sync_Polarity_Override_Bx(int set);
int ADC_Enable_Detection_Interrupt_Bx(int enable);
int ADC_Enable_AOGC_Interrupt_Bx(int enable);
int ADC_Mute_Enable_Bx(int enable);
int ADC_Power_OnOff_Bx(void);
int ADC_Ext_Clamp_Bx(int sel_ext);
int ADC_Set_Clamp_Bx(UINT8 clamp_base, UINT8 clamp_place, UINT8 clamp_width);
int ADC_GetPCModeInfo_Bx(LX_AFE_PCMODE_INFO_T *stPCModeInfo);
int ADC_Get_LLPLL_Filter_Status_Bx(void);
int ADC_SetIRETestMode_Bx(int sel , E_AGC_IRE mode);
int ADC_Set_Coast_Bx(UINT8 precoast, UINT8 postcoast);
int ADC_Set_Hsync_Sel_Bx(UINT8 select);
int ADC_CVI_Sync_Exist_Bx(void);
int ADC_Set_SOG_Level_Bx(UINT32 level);
int ADC_Get_SOG_Level_Bx(UINT32 *level);
int ADC_Check_Htotal_Diff_Bx(UINT8 count, int Kadp_Index);
int ADC_Read_Pixel_Value_Bx(LX_AFE_ADC_PIXEL_VALUE_T *pixel_value_t);
int ADC_Green_Mid_Level_Select_Bx(UINT8 value);
int ADC_Read_VSync_Width_Bx(UINT32 *pvs_width);
int ADC_Read_HSync_Width_Bx(UINT32 *pvs_width);
int ADC_Set_DCO_MinMax_Value_Bx(UINT8 dco_min, UINT8 dco_max);
int ADC_Get_DCO_MinMax_Value_Bx(UINT8 *pdco_min, UINT8 *pdco_max);
#ifdef	KDRV_CONFIG_PM
int ADC_RunSuspend_Bx(void);
int ADC_RunResume_Bx(void);
#endif

// L9Bx function prototype, added by won.hur(won.hur@lge.com) @2011.08.17
int ADC_L9Bx_PowerOn(void);
int ADC_L9Bx_PowerOff(void);
int ADC_L9Bx_InitDaughterBoard(void);
int ADC_L9Bx_GetBoundaryInform(ST_EXTAU *inform);
int ADC_L9Bx_SetTAUInform(S_EXTAU_VALUE *value);
int ADC_L9Bx_SetRGBPosition(S_RGB_POSITION *pos);
int ADC_L9Bx_GetRGBResult(S_RGB_OUT *result);
int ADC_L9Bx_GetRGBPosition(S_RGB_POSITION *pos);
int ADC_L9Bx_SetRGBSize(S_RGB_SIZE *size);
int ADC_L9Bx_GetSizeValue(S_VIDEO_SIZE_INFORM *size);
int ADC_L9Bx_SetPort(S_SEL_PORT *sel_port);
unsigned int ADC_L9Bx_GetPhaseValue(void);
int ADC_L9Bx_SetPhaseValue(unsigned int phase);
unsigned int ADC_L9Bx_GetScanType(void);
int ADC_L9Bx_SetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_L9Bx_GetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_L9Bx_SetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
int ADC_L9Bx_GetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
int ADC_L9Bx_SetInputVideo(int iIndex);
int ADC_L9Bx_Enable_Scart_Mode(BOOLEAN scart_enable);
void ADC_L9Bx_Vport_ALL_Power_Down(void);
int ADC_L9Bx_Channel_Power_Control(int vref_pdb, int bpdb, int gpdb, int rpdb);
int ADC_L9Bx_SetType(LX_AFE_ADC_INPUT_SOURCE_TYPE_T sel_type);
int ADC_L9Bx_Set_LLPLL(UINT32 arg);
int ADC_L9Bx_SetClock(int iIndex, SINT16 value);
int ADC_L9Bx_AGOCInit(void);
int ADC_L9Bx_GetSelectedPort(void);
int ADC_L9Bx_SetGainRGB( ST_GAIN_INFORM *gain);
int ADC_L9Bx_GetGainRGB( ST_GAIN_INFORM *gain);
int ADC_L9Bx_SetIRELevel(E_AGC_IRE ire , S_GAIN_TARGET *gain);
int ADC_L9Bx_GetOffsetRGB( S_OFFSET_INFORM *offset);
int ADC_L9Bx_SetOffsetRGB( S_OFFSET_INFORM *offset);
int ADC_L9Bx_GetSumRGB(S_RGB_SUM *sum);
int ADC_L9Bx_SetAgocWakeup(void);
int ADC_L9Bx_Reset_Digital(void);
int ADC_L9Bx_Reset_Digital_24MHZ(void);
int ADC_L9Bx_Reset_LLPLL(void);
int ADC_L9Bx_Check_Sync_Exist(void);
int ADC_L9Bx_Sync_Polarity_Override(int set);
int ADC_L9Bx_Enable_Detection_Interrupt(int enable);
int ADC_L9Bx_Enable_AOGC_Interrupt(int enable);
int ADC_L9Bx_Mute_Enable(int enable);
int ADC_L9Bx_Power_OnOff(void);
int ADC_L9Bx_Ext_Clamp(int sel_ext);
int ADC_L9Bx_Set_Clamp(UINT8 clamp_base, UINT8 clamp_place, UINT8 clamp_width);
int ADC_L9Bx_GetPCModeInfo(LX_AFE_PCMODE_INFO_T *stPCModeInfo);
int ADC_L9Bx_Get_LLPLL_Filter_Status(void);
int ADC_L9Bx_SetIRETestMode(int sel , E_AGC_IRE mode);
int ADC_L9Bx_Set_Coast(UINT8 precoast, UINT8 postcoast);
int ADC_L9Bx_Set_Hsync_Sel(UINT8 select);
int ADC_L9Bx_CVI_Sync_Exist(void);
int ADC_L9Bx_Set_SOG_Level(UINT32 level);
int ADC_L9Bx_Get_SOG_Level(UINT32 *level);
int ADC_L9Bx_Check_Htotal_Diff(UINT8 count, int Kadp_Index);
int ADC_L9Bx_Read_Pixel_Value(LX_AFE_ADC_PIXEL_VALUE_T *pixel_value_t);
int ADC_L9Bx_Green_Mid_Level_Select(UINT8 value);
int ADC_L9Bx_Read_VSync_Width(UINT32 *pvs_width);
int ADC_L9Bx_Read_HSync_Width(UINT32 *pvs_width);
int ADC_L9Bx_Set_DCO_MinMax_Value(UINT8 dco_min, UINT8 dco_max);
int ADC_L9Bx_Get_DCO_MinMax_Value(UINT8 *pdco_min, UINT8 *pdco_max);
void ADC_L9Bx_LVDS_Control(int enable);
void ADC_L9Bx_Set_Blank(int blank_sp);
int ADC_L9Bx_Set_Blank_Value(S_BLANK_INFORM *blank_t);
int ADC_L9Bx_Reset_LLPLL_Control(int enable_reset);
int ADC_L9Bx_Reset_Digital_Control(int enable_reset);
int ADC_L9Bx_LVDS_Reset_Control(int reset_enable);
int ADC_L9Bx_LVDS_Src_Control(LX_AFE_LVDS_SRC_CONTROL_T *pLVDS_Control_t);
int ADC_L9Bx_Component_APA(int iIndex);
int ADC_L9Bx_Component_APA_Test(UINT32 ADC_APA_Delay, UINT32 ADC_APA_Enable, UINT32 ADC_APA_Same_Count, UINT32 ADC_APA_Execute, UINT32 ADC_APA_Enable_Print);
int ADC_L9Bx_Get_Vtotal_Value(void);
int ADC_L9Bx_Set_Sync_Mode(ADC_SYNC_MODE sync_mode);
int ADC_L9Bx_Mute_Control(ADC_MUTE_CTRL adc_mute_control);
int ADC_L9Bx_Set_Comp_Params(int width, int progressive, int v_freq);
int ADC_L9Bx_Read_AGOC_State(void);
int ADC_L9Bx_Enable_Sync_Low_Level_Read(int enable);
int ADC_L9Bx_GetIRELevel( S_GAIN_TARGET *gain);
int ADC_L9Bx_Read_Sync_Low_Level(void);
int ADC_L9Bx_Post_Gain_Control(int percent);
int ADC_L9Bx_Check_LLPLL_status(void);
int ADC_L9Bx_LVDS_Channel_Enable_Control(int enable);
int ADC_L9Bx_Set_Ctl_Add(UINT32 sel_fs, UINT32 sinking_current, UINT32 source_current, UINT32 sog_input_filter_bw);
int ADC_L9Bx_Read_ACE_Reg(UINT32 addr , UINT32 *value);
int ADC_L9Bx_Write_ACE_Reg(UINT32 addr , UINT32 value);
#ifdef	KDRV_CONFIG_PM
int ADC_L9Bx_RunSuspend(void);
int ADC_L9Bx_RunResume(void);
#endif




// I2C only
#if 0
int ADC_SetDE(int  , unsigned int , unsigned int );
int ADC_SetHorPos(unsigned short pos);
int ADC_SetVerPos(unsigned short pos);
int ADC_SetHorTotal(unsigned short value);
int ADC_SetI2CData(unsigned int sub , unsigned int addr , unsigned int size , unsigned int value);
int ADC_GetI2CData(unsigned int sub , unsigned int addr , unsigned int size );
#endif
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _ADC_HW_H_ */

/** @} */
