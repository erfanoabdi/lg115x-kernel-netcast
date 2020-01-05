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



/** @file be_kapi.h
 *
 *	@author	    won.hur (won.hur@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.25
 *	@see
 */

#ifndef	_BE_KAPI_H_
#define	_BE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	BE_IOC_MAGIC		'D'

/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/* common */
#define BE_IOW_UPDATE_FIRMWARE     	_IOW(BE_IOC_MAGIC, 0, BE_FW_DWLD_T)
#define BE_IOW_RESET_SW            		_IO(BE_IOC_MAGIC, 1)

#define BE_IOW_TOP_SET_BYPASS			_IOW(BE_IOC_MAGIC, 2, BE_BLOCK_BYPASS_T)
#define BE_IOR_TOP_GET_BYPASS			_IOR(BE_IOC_MAGIC, 3, BE_BLOCK_BYPASS_T)
#define BE_IOR_TOP_GET_STATUS			_IOR(BE_IOC_MAGIC, 4, BE_STATUS_T)
#define BE_IOW_TOP_TOGGLE_3D_LR			_IOW(BE_IOC_MAGIC, 5, BE_3D_LR_T)
#define BE_IOW_TOP_SET_3D_IN_FORMAT 	_IOW(BE_IOC_MAGIC, 6, BE_TOP_3D_IN_FORMAT_T)
#define BE_IOW_TOP_GET_3D_IN_FORMAT 	_IOW(BE_IOC_MAGIC, 7, BE_TOP_3D_IN_FORMAT_T)
#define BE_IOW_TOP_SET_3D_OUT_FORMAT	_IOW(BE_IOC_MAGIC, 8, BE_3D_OUT_FORMAT_T)
#define BE_IOW_TOP_SET_3D_SYNC_DELAY	_IOW(BE_IOC_MAGIC, 9, BE_SYNC_DELAY_T)
#define BE_IOW_TOP_SET_3D_CONVERGENCE	_IOW(BE_IOC_MAGIC, 10,	BE_3D_CONVERGENCE_T)
#define BE_IOW_TOP_SET_BLACK_BAR		_IOW(BE_IOC_MAGIC, 11, BE_BLACK_BAR_T)
#define BE_IOW_TOP_SET_VIDEO_MUTE		_IOW(BE_IOC_MAGIC, 12, BE_VIDEO_MUTE_T)
#define BE_IOW_TOP_SET_MUTE_COLOR		_IOW(BE_IOC_MAGIC, 13, BE_VIDEO_MUTE_COLOR_T)
#define BE_IOW_TOP_SET_DISPLAY_TYPE		_IOW(BE_IOC_MAGIC, 14, BE_DISPLAY_TYPE_T)
//#define BE_IOW_TOP_SET_SPREAD_SPECT		// BE TOP에서 ARM에서 구현 필요
#define BE_IOW_TOP_SET_DEBUG_DISPLAY	_IOW(BE_IOC_MAGIC, 15, BE_DEBUG_DISPLAY_T)
#define BE_IOW_SET_VID_OPERATION		_IOW(BE_IOC_MAGIC, 16, BE_VID_OPERATION_T)
#define BE_IOW_SET_INPUT_SRC_TYPE		_IOW(BE_IOC_MAGIC, 17, BE_SRC_TYPE_T)
#define BE_IOW_SET_ACTIVE_WINDOW_START	_IOW(BE_IOC_MAGIC, 18, BE_ACTIVE_WINDOW_START_T)
#define BE_IOW_SET_ACTIVE_WINDOW_SIZE	_IOW(BE_IOC_MAGIC, 19, BE_ACTIVE_WINDOW_SIZE_T)
#define BE_IOW_TOP_FIRMWARE_DEBUG		_IOW(BE_IOC_MAGIC, 20, BE_FIRMWARE_DEBUG_T)
#define BE_IOW_SET_UART_FOR_MCU			_IOW(BE_IOC_MAGIC, 21, BOOLEAN )
#define BE_IORW_REG_ACCESS				_IOWR(BE_IOC_MAGIC, 22, BE_REG_RW_T)
#define BE_IOW_ENABLE_DEBUG_PRINT		_IOW(BE_IOC_MAGIC, 23, BE_DEBUG_PRINT_T )

#define BE_IOC_TOP_MAX					(_IOC_NR(BE_IOW_ENABLE_DEBUG_PRINT) +1 )

/* H3D */
#define BE_IOR_H3D_GET_VERSION			_IOR(BE_IOC_MAGIC, BE_IOC_TOP_MAX, BE_H3D_VERSION_T)
#define BE_IOR_H3D_GET_STATUS				_IOR(BE_IOC_MAGIC, BE_IOC_TOP_MAX+1, BE_H3D_STATUS_T)
#define BE_IOW_H3D_RESET_BLOCK			_IOR(BE_IOC_MAGIC, BE_IOC_TOP_MAX+2, BE_H3D_RESET_BLOCK_T)
#define BE_IOW_H3D_BYPASS_ALL				_IOR(BE_IOC_MAGIC, BE_IOC_TOP_MAX+3, BE_H3D_BYPASS_ALL_T)
#define BE_IOW_H3D_SET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+4, BE_H3D_MODE_T)
#define BE_IOW_H3D_GET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+5, BE_H3D_MODE_T)
#define BE_IOW_H3D_IN_FORMAT				_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+6, BE_H3D_IN_FORMAT_T)
#define BE_IOW_H3D_T3C_DEPTH_LEVEL		_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+7, BE_H3D_T3C_DEPTH_LEVEL_T)
#define BE_IOW_H3D_A3C_DEPTH_LEVEL		_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+8, BE_H3D_A3C_DEPTH_LEVEL_T)
#define BE_IOW_H3D_A3C_AUTOCONVERGENCE	_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+9, BE_H3D_A3C_AUTOCONVERGENCE_T)
#define BE_IOW_H3D_GET_A3C_DMINMAX		_IOW(BE_IOC_MAGIC, BE_IOC_TOP_MAX+10, BE_H3D_A3C_DMINMAX_T)

#define BE_IOC_H3D_MAX					(_IOC_NR(BE_IOW_H3D_GET_A3C_DMINMAX) +1 )

/* FRC */
#define BE_IOW_FRC_CONTROL_MEMC        	_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX, BE_FRC_MEMC_MODE_T)
//#define BE_IOW_FRC_SET_TRUEMOTION_DEMO _IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+1, BOOLEAN)	//구현되는 것인가? 확인 필요. 기존 L9에서 가져온것임.
#define BE_IOW_FRC_SET_DEMO_MODE		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+2, BE_FRC_DEMO_MODE_T)
#define BE_IOW_FRC_SET_DEBUG_BOX		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+3, BE_FRC_ENABLE_DEBUG_BOX_T)
#define BE_IOW_FRC_SET_BYPASS_MEMC_REG	_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+4, BE_FRC_MEMC_BYPASS_REGION_T)
#define BE_IOW_FRC_SET_YUV_444_MODE	_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+5, BE_FRC_COLOR_YUV444_T)
#define BE_IOW_FRC_SET_LOW_DELAY		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+6, BE_FRC_LOW_DELAY_T)
#define BE_IOR_FRC_GET_FIRMWARE_VER		_IOR(BE_IOC_MAGIC, BE_IOC_H3D_MAX+7, BE_FRC_VERSION_T)
#define BE_IOR_FRC_GET_STATUS			_IOR(BE_IOC_MAGIC, BE_IOC_H3D_MAX+8, BE_FRC_STATUS_T)
#define BE_IOW_FRC_FORCE_FRAME_RATE	_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+9, BE_FRC_FRAME_RATE_T)
#define BE_IOW_FRC_SET_FAST_MV_TH		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+10, BE_FRC_FAST_MV_TH_T)
#define BE_IOW_FRC_SET_STILL_DET_TH		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+11, BE_FRC_STILL_DET_TH_T)
#define BE_IOW_FRC_SET_SAME_DET_TH		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+12, BE_FRC_VMODE_SAME_TH_T)
#define BE_IOW_FRC_SET_DIFF_DET_TH		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+13, BE_FRC_VMODE_DIFF_TH_T)
#define BE_IOW_FRC_SET_VMODE_ERR_CNT	_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+14, BE_FRC_VMODE_ERR_CNT_TH_T)
#define BE_IOW_FRC_SET_JUDDER_SLOPE		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+15, BE_FRC_JUDDER_CONTROL_SLOPE_T)
#define BE_IOW_FRC_SET_MIN_ERR_TH		_IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+16, BE_FRC_MIN_ERROR_T)
#define BE_IOW_FRC_SET_ABNORM_SYNC_CNT _IOW(BE_IOC_MAGIC, BE_IOC_H3D_MAX+17, BE_FRC_ABNORMAL_SYNC_CNT_T)

#define BE_IOC_FRC_MAX					(_IOC_NR(BE_IOW_FRC_SET_ABNORM_SYNC_CNT) +1 )

/* SRE */
#define BE_IOW_SRE_SET_BYPASS			_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX, BE_SRE_BYPASS_ALL_T)
#define BE_IOW_SRE_SET_INPUT_FORMAT	_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+1, BE_SRE_INPUT_MODE_T)
#define BE_IOR_SRE_GET_VERSION			_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+2, BE_SRE_VERSION_T)
#define BE_IOR_SRE_GET_STATUS			_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+3, BE_SRE_STATUS_T)
#define BE_IOW_SRE_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+4, BE_SRE_CONTROL_T)
#define BE_IOW_SRE_SET_DB_GRADE			_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+5, BE_SRE_DB_GRADE_T)
#define BE_IOW_SRE_SR_STRENGTH_LEVEL	_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+6, BE_SRE_SR_STRENGTH_LEVEL_T)
#define BE_IOW_SRE_UPDATE_ALL			_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+7, BE_SRE_UPDATE_ALL_T)
#define BE_IOW_SRE_WRITE_DATA			_IOW(BE_IOC_MAGIC, BE_IOC_FRC_MAX+8, BE_SRE_WRITE_DATA_T)
#define BE_IOR_SRE_GET_DATA				_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+9, BE_SRE_GET_DATA_T)
#define BE_IOR_SRE_SET_GLOBAL_SCALE		_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+10, BE_SRE_GLOBAL_SCALE_T)
#define BE_IOR_SRE_SET_LOCAL_SCALE		_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+11, BE_SRE_LOCAL_SCALE_T)
#define BE_IOR_SRE_SET_PREPROCESSING		_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+12, BE_SRE_PREPROCESSING_T)
#define BE_IOR_SRE_SET_NOISE_CONTROL		_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+13, BE_SRE_NOISE_CONTROL_T)
#define BE_IOR_SRE_SET_LOCAL_BYPASS		_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+14, BE_SRE_LOCAL_BYPASS_T)
#define BE_IOR_SRE_SET_CLIP_CONTROL		_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+15, BE_SRE_CLIP_CONTROL_T)
#define BE_IOR_SRE_SET_WEIGHT_CONTROL	_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+16, BE_SRE_WEIGHT_CONTROL_T)
#define BE_IOR_SRE_SET_ETC_CONTROL		_IOR(BE_IOC_MAGIC, BE_IOC_FRC_MAX+17, BE_SRE_ETC_CONTROL_T)

#define BE_IOC_SRE_MAX					(_IOC_NR(BE_IOR_SRE_SET_ETC_CONTROL) +1 )

/* PE */
#define BE_IOR_PE_GET_STATUS 		_IOR(BE_IOC_MAGIC, BE_IOC_SRE_MAX, BE_PE_STATUS_T)

#define BE_IOC_PE_MAX					(_IOC_NR(BE_IOR_PE_GET_STATUS) +1 )

/* LED */
#define BE_IOR_LED_GET_VERSION			_IOR(BE_IOC_MAGIC, BE_IOC_PE_MAX, BE_LED_VERSION_T)
#define BE_IOR_LED_GET_STATUS			_IOR(BE_IOC_MAGIC, BE_IOC_PE_MAX+1, BE_LED_STATUS_T)
#define BE_IOW_LED_SET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+2, BE_LED_MODE_T)
#define BE_IOW_LED_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+3, BE_LED_CONTROL_T)

#define BE_IOR_HDR_GET_VERSION			_IOR(BE_IOC_MAGIC, BE_IOC_PE_MAX+4, BE_HDR_VERSION_T)
#define BE_IOR_HDR_GET_STATUS			_IOR(BE_IOC_MAGIC, BE_IOC_PE_MAX+5, BE_HDR_STATUS_T)
#define BE_IOW_HDR_SET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+6, BE_HDR_MODE_T)
#define BE_IOW_HDR_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+7, BE_HDR_CONTROL_T)

#define BE_IOR_WCG_GET_VERSION			_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+8, BE_WCG_VERSION_T)
#define BE_IOR_WCG_GET_STATUS			_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+9, BE_WCG_STATUS_T)
#define BE_IOW_WCG_SET_MODE				_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+10, BE_WCG_MODE_T)
#define BE_IOW_WCG_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_PE_MAX+11, BE_WCG_CONTROL_T)

#define BE_IOC_LED_MAX					(_IOC_NR(BE_IOW_WCG_CONTROL) +1 )

/* PWM */
#define BE_IOW_PWM_SET_CONTROL				_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX, BE_PWM_CTRL_T)
#define BE_IOW_PWM_SET_ADAPT_FREQ_CONTROL	_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+1, BE_PWM_ADAPT_FREQ_DB_T)
#define BE_IOW_PWM_SET_FREQUENCY			_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+2, BE_PWM_FREQ_T)
#define BE_IOW_PWM_SET_DUTY_CYCLE			_IOW(BE_IOC_MAGIC, BE_IOC_LED_MAX+3, BE_PWM_DUTY_T)
#define BE_IOR_PWM_GET_EXTERNAL_PWM			_IOR(BE_IOC_MAGIC, BE_IOC_LED_MAX+4, BE_EXTERNAL_PWM_T)

#define BE_IOC_PWM_MAX						(_IOC_NR(BE_IOR_PWM_GET_EXTERNAL_PWM) +1 )
#define BE_IOC_MAXNR							BE_IOC_PWM_MAX

/* OIF */
/*
#define BE_IOW_OIF_SET_VESA_JEIDA	_IOW(BE_IOC_MAGIC, 190, BOOLEAN)
#define BE_IOW_OIF_SET_BIT_DEPTH
#define BE_IOW_OIF_SET_SELECT_OUTCH
#define BE_IOW_OIF_SET_LVDS_OUTPUT
#define BE_IOW_OIF_SET_LVDS_POWER
#define BE_IOW_OIF_SET_DARK_SCREEN
#define BE_IOW_OIF_SET_LVDS_OUT_CTRL
#define BE_IOW_OIF_SET_LVDS_PORT_SWAP
*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions (Common)
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32	dbgMask;	// bit 0 : PRINT, bit 1 : ERROR, bit 2 : DEBUG, bit 3: TRACE
} BE_DEBUG_PRINT_T;

typedef enum {
	BE_FRC_MC_TYPE_OFF,
	BE_FRC_MC_TYPE_LOW,
	BE_FRC_MC_TYPE_MID,
	BE_FRC_MC_TYPE_HIGH,
	BE_FRC_MC_TYPE_USER,
	BE_FRC_MC_TYPE_55_PULLDOWN
} BE_FRC_MC_TYPE_T;

typedef enum {
	BE_REG_RW_TYPE_NONE = 0,
	BE_REG_RW_TYPE_DPPB_TOP,
	BE_REG_RW_TYPE_DPPB_TXM,
	BE_REG_RW_TYPE_DPPB_LED,
	BE_REG_RW_TYPE_FRC_LRX,
	BE_REG_RW_TYPE_FRC_P3D,
	BE_REG_RW_TYPE_FRC_DVI,

	BE_REG_RW_TYPE_MAXNUM
} BE_REG_RW_TYPE_T;

typedef struct
{
	BOOLEAN	isRead;
	BE_REG_RW_TYPE_T type;
	UINT32	addr;
	UINT32	data;
} BE_REG_RW_T;

typedef enum {
	BE_FW_DWLD_TYPE_FRC = 0,
	BE_FW_DWLD_TYPE_SRE,
	BE_FW_DWLD_TYPE_WCG,
	BE_FW_DWLD_TYPE_LED,
	BE_FW_DWLD_TYPE_HDR,
	BE_FW_DWLD_TYPE_MAXNUM,

	BE_FW_DWLD_TYPE_ALL = BE_FW_DWLD_TYPE_MAXNUM
} BE_FW_DWLD_TYPE_T;

typedef struct {
	UINT32	size;	// 0 : header or file download
	CHAR	*pData;	// NULL : header or file download
	BE_FW_DWLD_TYPE_T	type;
} BE_FW_DWLD_T;

typedef enum {
	BE_PWM0 = 0, ///< pwm port0
	BE_PWM1,		///< pwm port1
	BE_PWM2,		///< pwm port2
	BE_PWM3,		///< pwm port3
	BE_PWM_MAX
} BE_PWM_ID_T;

typedef enum {
	BE_PWM_LOW	= 0,		///< PWM Output Signal Cotrol - Low
	BE_PWM_NORMAL,			///< PWM Output Signal Cotrol - Normal
	BE_PWM_HIGH,				///< PWM Output Signal Cotrol - High
	BE_PWM_INVERSION,		///< PWM Output Signal Cotrol - Inversion
} BE_PWM_OUT_CTRL_T;

typedef struct
{
	BE_PWM_ID_T			port;		///< PWM number: PWM0~2.
	BOOLEAN					enable;
	BOOLEAN					pwmMode;	///< freerun(0) / locking(1) mode
	BE_PWM_OUT_CTRL_T		pwmOutput;	///< PWM Output signal control
} BE_PWM_CTRL_T;

typedef struct
{
	UINT32			freq_48nHz;	///< PWM Output Frequency on 48xN Hz Vsync
	UINT32			freq_50nHz; ///< PWM Output Frequency on 50xN Hz Vsync
	UINT32			freq_60nHz; ///< PWM Output Frequency on 60xN Hz Vsync
} BE_PWM_ADAPT_FREQ_DB_T;

typedef struct
{
	BE_PWM_ID_T				port;	///< PWM number: PWM0~2.
	BOOLEAN						enable;
	BE_PWM_ADAPT_FREQ_DB_T	freqDb;	///< PWM Output Frequency DB
} BE_PWM_ADAPT_FREQ_CTRL_T;

typedef struct
{
	BE_PWM_ID_T			port;		///< PWM number: PWM0~2.
	UINT32					frequency;	///< PWM Output Frequency
} BE_PWM_FREQ_T;

typedef struct
{
	BE_PWM_ID_T	port;		///< PWM number: PWM0~2.
	UINT16			duty;		///< Set duty of PWM (0 ~ 255).
	UINT16			offset;		///< PWM Start Position (1~1125).
} BE_PWM_DUTY_T;

/**
 * BE PWM parameter.
 * get PWM Duty value for external port(FRC) .
 *
*/
typedef struct
{
	UINT16			frequency;		///< current frequency (locking mode frequncy)
    	UINT16			duty;		    	///< current duty of PWM (0 ~ 255).
} BE_EXTERNAL_PWM_T;

// prefix definition
// 4bit  : boolean			= b		-> boolean 용도지만 ignore value를 위해 4bit 할당, ignore value : 0xF
// 4bit  : nibble			= u4 	-> ignore value : 0xF
// 8bit  : byte    			= u8 	-> ignore value : 0xFF
// 16bit : unsigned int 	= u16		-> ignore value : 0xFFFF
// 32bit : unsigned int 	= u32		-> ignore value : 0xFFFFFFFF

typedef struct
{
	UINT32	bInit      				:	4,	// 0: BE All Block Normal, 1: BE All Block Init
			reserved				:	28;
} BE_INIT_T;

typedef struct
{
	UINT32 	u4BEStatus 				:	4,	// BE All block status
			u4H3DStatus				:	4,
			u4FRCStatus				:	4,
			u4SREStatus				:	4,
			u4DPPAStatus			:	4,
			u4LEDStatus				:	4,
			u4MCUStatus				:	4,
			reserved				:	4;
} BE_STATUS_T;

typedef struct
{
	UINT32  	u16ConvergenceVal 		:	16,
			u16ConvergenceEnable	:	16;	// 0 : Convergence auto disable,
											// 1 : Convergence auto enable with 3D depth info
} BE_3D_CONVERGENCE_T;

typedef struct
{
	UINT32	bOutLR					:	4,	// 0: Left/Top First, 1: Right/Bottom First
			reserved				:	28;
} BE_3D_LR_T;

typedef struct
{
	UINT32 	u4BE3DInFormat			:	4,	// 0 : 2D, 1 : S/S, 2 : T/B, 3: Dual
			u4BE3DInType 			:	4,	// 0 : 3D Normal, 0 : Dual Stream
			u4BE3DInSize 			:	4,	// 0 : 1920x1080, 1 : 960x1080, 2 : 1920x540, 3 : UD
			reserved				:	20;
} BE_TOP_3D_IN_FORMAT_T;

typedef struct
{
	UINT32 	u4OutFormat 			:	4,	//	0 : PG,	1 : SG,	2 : FS,
			u4PGMode 				:	4,	//	0 : Normal PG, 1 : FPR
			u4GSyncEnable			:	4,	// 	0 : Glass Sync disable, 1 : Glass Sync Enable for SG
			u4Single				:	4,	// 	0 : Dual View, 1 : Single View
			reserved				:	16;
} BE_3D_OUT_FORMAT_T;

typedef struct
{
	UINT32	u32GlassSyncDelay;		// Glass Sync Delay for SG mode
} BE_SYNC_DELAY_T;

typedef struct
{
	UINT32 	u8BarOn					:	8,
			u8BarVal				:	8,
			u8BarStep				:	8,
			reserved				:	8;
} BE_BLACK_BAR_T;

typedef struct
{
	UINT32	bVideoMuteOn			:	4,	// 0 : Video Mute off,	1 : Video Mute On
			u4DEInRate				:	4,	// DE Video input frame rate (0:15, 1:20, 2:24, 3:25, 4:30, 5:48, 6:50, 7:60, 0xF:N/A)
			u4DEOutRate			:	4,	// DE Video output frame rate (0:15, 1:20, 2:24, 3:25, 4:30, 5:48, 6:50, 7:60, 0xF:N/A)
			reserved				:	20;
} BE_VIDEO_MUTE_T;

typedef struct
{
	UINT32 	u8VideoMuteColorR		:	8,
			u8VideoMuteColorG		:	8,
			u8VideoMuteColorB		:	8,
			reserved				:	8;
} BE_VIDEO_MUTE_COLOR_T;

typedef struct
{
	UINT32	bH3DBypass				:	4,	//	0: H3D Normal, 1: H3D(2D-3D,Depth Block) Bypass
			bFRCBypass				:	4,	//	0: FRC Normal, 1: FRC Bypass
			bSREBypass				:	4,	//	0: SRE Normal, 1: SRE Bypass
			bPEBypass				:	4,	//	0: PE Normal, 1: PE Bypass
			bLEDBypass				:	4,	//	0: LED Normal, 1: LED Bypass
			bHDRBypass				:	4,	//	0: HDR Normal, 1: HDR Bypass
			bWCGBypass				:	4,	//	0: WCG Normal, 1: WCG Bypass
			reserved				:	4;
} BE_BLOCK_BYPASS_T;

typedef struct
{
	UINT32	u4BEPanelType			:	4,	// 0 : FHD,	 1 : UD,
			u4BEPanelRate			:	4,	// 0 : 60Hz, 1 : 120Hz
			u4BEPanelReverse		:	4,	// 0 : Normal,	1 : Reverse
			reserved				:	20;
} BE_DISPLAY_TYPE_T;

typedef struct
{
	UINT32	u8H3DDebugDisplay		:	8,
			u8FRCDebugDisplay		:	8,
			u8PEDebugDisplay		:	8,
			u8LEDDebugDisplay		:	8;
} BE_DEBUG_DISPLAY_T;

typedef struct
{
	UINT32	u4Mode					:	4,	// 0 : 2D,	1 : PIP, 2 : V_ENC On
			reserved				:	28;
} BE_VID_OPERATION_T;

typedef struct
{
	UINT32	u16SrcInputType		:	16,	// 0 : HDMI,	1 : Component, 2 : Composite, 3 : ETC
			u16SrcInputSize		:	16;	// 1080, 720, 480
} BE_SRC_TYPE_T;

typedef struct
{
	UINT32  u16ActiveWindowStartX   :          16,
			u16ActiveWindowStartY   :          16;
} BE_ACTIVE_WINDOW_START_T;

typedef struct
{
	UINT32  u16ActiveWindowWidth   :          16,
			u16ActiveWindowHeight  :          16;
} BE_ACTIVE_WINDOW_SIZE_T;

typedef struct
{
	UINT8	u8Read;
	UINT32	u32Cmd;
	UINT32	u32Param;
} BE_FIRMWARE_DEBUG_T;

typedef struct
{
	UINT32	u8A3CVersion			: 	8,
			u8T3CVersion			:	8,
			reserved				:	16;
} BE_H3D_VERSION_T;

typedef struct
{
	UINT32	u4H3DStatus				:	4,
			u4A3CStatus				:	4,
			u4T3CStatus				:	4,
			reserved				:	20;
} BE_H3D_STATUS_T;

typedef struct
{
	UINT32	bInitA3C				:	4,
			bInitT3C				:	4,
			reserved				:	24;
} BE_H3D_INIT_BLOCK_T;

typedef struct
{
	UINT32	bReset					:	4,
			reserved				:	28;
} BE_H3D_RESET_BLOCK_T;

typedef struct
{
	UINT32	bBypass					:	 4,
			reserved				:	28;
} BE_H3D_BYPASS_ALL_T;

typedef struct
{
	UINT32	bA3CMode				:	4, // 0 : off, 1: on
			bT3CMode				:	4, // 0 : off, 1: on
			reserved				:	24;
} BE_H3D_MODE_T;

typedef struct
{
	UINT32	u4H3DInFormat			:	4,	// 0: 1920x1080(FHD), 1:960x1080(SS), 2:1920x540(TB)
			reserved				:	28;
} BE_H3D_IN_FORMAT_T;

typedef struct
{
	UINT32	u8T3CDepthLevel		:	8,	// Depth level : 0 ~ 20
			reserved				:	24;
} BE_H3D_T3C_DEPTH_LEVEL_T;

typedef struct
{
	UINT32	u8A3CDepthLevel		:	8,	// Depth level : 0 ~ 20
			reserved				:	24;
} BE_H3D_A3C_DEPTH_LEVEL_T;

typedef struct
{
	UINT32	bA3CAutoConvergence	:	4,	// 0 : Auto Convergence off, 1 : Auto Convergence on
			reserved				:	28;
} BE_H3D_A3C_AUTOCONVERGENCE_T;

typedef struct
{
	UINT32	u8A3CDispMin			:	8,	// Disparity min
			u8A3CDispMax			:	8,	// Disparity max
			u8A3CDispMean			:	8,	// Disparity mean
			reserved				:	8;
} BE_H3D_A3C_DMINMAX_T;

typedef struct
{
    UINT32	u16Version      		:	16,
            		u16Subversion   		:	16;
} BE_FRC_VERSION_T;

typedef struct
{
    UINT32	u8Status      			:	4,		// 0: NOT_READY, 1:INIT, 2:NORMAL
			u8Syncstatus		:	4,		// 0: STABLE, 1:ABNORMAL_SYNC
            		reserved      			:	24;
} BE_FRC_STATUS_T;

typedef struct
{
    UINT32	bInit          			:	4,		// 0: NOT_READY, 1:INIT, 2:NORMAL
            		reserved      			:	28;
} BE_FRC_INIT_T;

typedef struct
{
    UINT32	u8Blur       				:	8,		// 0~9 : Blur level
            		u8Judder      			:	8,		// 0~9 : Judder level
			u8MemcType     			:	8,		// 0 : OFF, 1: LOW, 2:MID, 3:HIGH, 4:USER, 5: PULLDOWN55 : @ref FRC_MC_TYPE_T
			reserved				:	8;
} BE_FRC_MEMC_MODE_T;

typedef struct
{
    UINT32	bLowdelay      			:	4,		// 0: NORMAL_DELAY, 1:LOW_DELAY
            		reserved      				:	28;
} BE_FRC_LOW_DELAY_T;

typedef struct
{
    UINT32 	bDemoMode     			:	4,		// 0: DEMO_OFF, 1:DEMO_ON
			bDemoSide				:	4,		// 0: DEMO_SIDE_LEFT, 1:DEMO_SIDE_RIGHT
            		reserved   				:	24;
} BE_FRC_DEMO_MODE_T;

typedef struct
{
    UINT32	bBypassRegion0			:	4,	// Region 0 Bypass 0 : Off, 1 : On
			bBypassRegion1			:	4,	// Region 1 Bypass 0 : Off, 1 : On
			bBypassRegion2			:	4,	// Region 2 Bypass 0 : Off, 1 : On
			bBypassRegion3			:	4,	// Region 3 Bypass 0 : Off, 1 : On
			reserved   				:	16;
} BE_FRC_MEMC_BYPASS_ENABLE_T;

typedef struct
{
    UINT32	u16MemcBypassX 			:	16,	// Memc Bypass region Start X position
			u16MemcBypassY			:	16;	// Memc Bypass region Start Y position
} BE_FRC_MEMC_BYPASS_XY_T;

typedef struct
{
    UINT32	u16MemcBypassW 			:	16,	// Memc Bypass region Width
			u16MemcBypassH			:	16;	// Memc Bypass region Height
} BE_FRC_MEMC_BYPASS_WH_T;

typedef struct
{
	BE_FRC_MEMC_BYPASS_ENABLE_T	u32BypassEn;	// Memc Bypass On/Off
	BE_FRC_MEMC_BYPASS_XY_T	u32BypassXY;		// Memc Bypass region Start position X,Y
	BE_FRC_MEMC_BYPASS_WH_T	u32BypassWH;		// Memc Bypass region Start position W,H
} BE_FRC_MEMC_BYPASS_REGION_T;

typedef struct
{
    UINT32	u8FrameRate 			:	8,		// 0 : FREE_RUN, 1: RATE_120HZ, 2: RATE_100HZ, 3: RATE_60HZ, 4: RATE_50HZ
			reserved				:	24;
} BE_FRC_FRAME_RATE_T;

typedef struct
{
	UINT32 	u4ColorYuv 				: 	4,		// 0: YUV422, 1: YUV444
			u4ColorDepth 			:	4,		// 0: 10bit, 1:8bit
			u4CompMode 			:	4,		// 0: Compression mode Off, 1:Compression mode On
			reserved 				:	20;
} BE_FRC_COLOR_YUV444_T;

typedef struct
{
	UINT32	u8MotionSizeX			: 	8,		// Fast Motion Threshold X range
			u8MotionSizeY 			:	8,		// Fast Motion Threshold Y range
			reserved 				:	16;
} BE_FRC_FAST_MV_TH_T;

typedef struct
{
	UINT32	u16StillDetMinTh 		: 	16,		// Absolute Stil Detection threshold
			u16StillDetMaxTh		:	16;		// Relative Stil Detection threshold
} BE_FRC_STILL_DET_TH_T;

typedef struct
{
	UINT32	u16VmodeSameMinTh 		: 	16,		// Absolute Same Frame threhold for Video mode detection
			u16VmodeSameMaxTh		:	16;		// Relative Same Frame threshold for video mode detection
} BE_FRC_VMODE_SAME_TH_T;

typedef struct
{
	UINT32	u16VmodeDiffMinTh 		: 	16,		// Absolute Diffrent Frame threhold for Video mode detection
			u16VmodeDiffMaxTh		:	16;		// Relative Differnt Frame threshold for video mode detection
} BE_FRC_VMODE_DIFF_TH_T;

typedef struct
{
	UINT32	u8Vmode23ErrCntTh 		: 	8,		// Allowed abnormal frame cnt for 2:2 mode for video mode
			u8Vmode22ErrCntTh		:	8,		// Allowed abnormal frame cnt for 2:3 mode for video mode
			reserved				:	16;
} BE_FRC_VMODE_ERR_CNT_TH_T;

typedef struct
{
	UINT32	u8JudderChanelSlope 		: 	8,		// Judder Change weight for Judder control
			reserved				:	24;
} BE_FRC_JUDDER_CONTROL_SLOPE_T;

typedef struct
{
	UINT32	u8MinimumErrorTh 		: 	8,		// Frame repeat control thresold for Minimum FRC Error
			reserved				:	24;
} BE_FRC_MIN_ERROR_T;

typedef struct
{
	UINT32	u8AbnormalSyncTh 		: 	8,		// Abnormal Sync error interrupt threhold
			reserved				:	24;
} BE_FRC_ABNORMAL_SYNC_CNT_T;

typedef struct
{
	UINT32	u32FrcInitDDRAddr;				// FRC Initialization DB DDR Address
} BE_FRC_INIT_DB_ADDR_T;

typedef struct
{
	UINT32	u4FRCDebugBoxOn 		: 	4,		// 0 : Debug Box Off, 1 : Debug Box On
			u4FRCDebugBoxMode		: 	4,		// FRC Debug Box mode
			reserved				:	24;
} BE_FRC_ENABLE_DEBUG_BOX_T;

typedef struct
{
	UINT32	u16Version				:	16,
			u16SubVersion			:	16;
} BE_SRE_VERSION_T;

typedef struct
{
	UINT32	u8LutLoadStatus			:	8,	// 0 : DB not ready, 1 : invalid DB upload, 2 :valid db upload
			u8RunStatus				:	8,	// 0 : sre_bypass, 1 : sre_on, 2 : sre detour
			u16SREVersion			:	16;
} BE_SRE_STATUS_T;

typedef struct
{
	UINT32	bInit					:	4,
			reserved				:	28;
} BE_SRE_INIT_BLOCK_T;

typedef struct
{
	UINT32	bBypass					:	4,	// 0 : Normal,	1 : Bypass
			reserved				:	28;
} BE_SRE_BYPASS_ALL_T;

typedef struct
{
	UINT32	u32SreLutDDRAddr;
} BE_SRE_LUT_ADDR_T;

typedef struct
{
	UINT32	bLoad					:	4,
			reserved				:	28;
} BE_SRE_LOAD_LUT_T;

typedef struct
{
	UINT32	u4PictureMode			:	4,		// 0: Cinema, 1:Standard, 2:Vivid, 3:Game, 4:Expert
			reserved				:	28;
} BE_SRE_MODE_T;

typedef struct
{
	UINT32	u4Control				:	4,	//0:SRE bypass, 1:SRE LOW, 2:SRE MED, 3:SRE HIGH
			reserved				:	28;
} BE_SRE_CONTROL_T;

typedef struct
{
	UINT32	u4InputResolution		:	4,		// 0 : FHD,		1 : SD,		2 : UD(detour)
			u4Input3DMode			:	4,		// 0 : 2D,3D SG,	1 : 3D PG
			reserved				:	24;
	// 3D, HD, SD
} BE_SRE_INPUT_MODE_T;

typedef struct
{
	UINT32	u8DBGrade				:	8,
			reserved				:	24;
} BE_SRE_DB_GRADE_T;

typedef struct
{
	UINT32	u8StrengthLevel			:	8,
			reserved				:	24;
} BE_SRE_SR_STRENGTH_LEVEL_T;

typedef struct
{
	UINT32	bUpdate					:	4,
			reserved				:	28;
} BE_SRE_UPDATE_ALL_T;

typedef struct
{
	UINT32	u32DirectAddr;
} BE_SRE_WRITE_ADDRESS_T;

typedef struct
{
	UINT32	u32DirectData;
} BE_SRE_WRITE_DATA_T;

typedef struct
{
	UINT32	u32DirectAddr;
} BE_SRE_READ_ADDRESS_T;

typedef struct
{
	UINT32	u32DirectData;
} BE_SRE_GET_DATA_T;

typedef struct
{
	UINT32	u8SRAGlobalScale		:	8,
			u8SRBGlobalScale		:	8,
			reserved				:	16;
} BE_SRE_GLOBAL_SCALE_T;

typedef struct
{
	UINT32	u4ModeLocalScale		:	4,		// 0:standard deviation 1:gradient 2:std+grd
			u4SRALocalScale			:	4,
			u4SRBLocalScale			:	4,
			reserved				:	20;
} BE_SRE_LOCAL_SCALE_T;

typedef struct
{
	UINT32	u8XFilter				:	8,		// 0~15 : Horizontal PP filter idx
			u8YFilter				:	8,		// 0~15 : Vertical PP filter idx
			u8GlobalScale			:	8,		// 0~127 : Global scale for Pre-processing
			u8LocalScale			:	8;		// 0~15 : Local scale idx for Pre-processing
} BE_SRE_PREPROCESSING_T;

typedef struct
{
	UINT32	bUseNoiseStd			:	8,		// 0 : disable 1:enable
			bAutoNoiseStd			:	8,		// 1: auto noise estimation
			bAutoNoiseLevel			:	8,		// 1: auto noise level control
			u8UserNoiseStd			:	8;		// 0~64 : user noise std input
} BE_SRE_NOISE_CONTROL_T;

typedef struct
{
	UINT32	bUseLocalBypass		:	4,		// 0 : disable 1:enable
			u4BypassLevel			:	4,		// 0~15 : Local bypass strenghth level idx
			reserved				:	24;
} BE_SRE_LOCAL_BYPASS_T;

typedef struct
{
	UINT32	bUseClip				:	8,		// 0 : disable 1:enable
			u8ClipMode				:	8,		// 0: auto clip lv+str mode 1: auto clip lv mode 2: auto clip str mode 3: manual clip lv+str mode
			u8ClipLevel				:	8,
			u8ClipStrength			:	8;
} BE_SRE_CLIP_CONTROL_T;

typedef struct
{
	UINT32	u4ModeWeight			:	4,		// 0~15 0:only srb 15:only sra
			reserved				:	28;
} BE_SRE_WEIGHT_CONTROL_T;

typedef struct
{
	UINT32	bUseLineThinning		:	4,		// 0 : disable 1:enable
			bUseSVHE				:	4,		// 0 : disable 1:enable
			reserved				:	24;
} BE_SRE_ETC_CONTROL_T;

typedef struct
{
	UINT32	u4InitStatus				: 	4,		// 0 : Not Init
			reserved				:	28;
} BE_PE_STATUS_T;

typedef struct
{
	UINT32	bInit					:	4,
			reserved				:	28;
} BE_PE_INIT_BLOCK_T;

typedef struct
{
	UINT32	u8regnNum				:	8,	//	region number 0~15
			u8deltHue				:	8,	//	delta hue, -127 ~ 127
			u8deltSat				:	8,	//	delta saturation, -127 ~ 127
			u8deltVal				:	8;	//	delta value, -127 ~ 127
} BE_PE_CEN_CTRL0_T;

typedef struct
{
	UINT32	u8deltGrn				:	8,	//	delta green, -127 ~ 127
			u8deltBlu				:	8,	//	delta blue, -127 ~ 127
			u8deltRed				:	8,	//	delta red, -127 ~ 127
			u8gainMst				:	8;	//	master gain, 0 ~ 255
} BE_PE_CEN_CTRL1_T;

typedef struct
{
	UINT32	u8LEDLutVersion			:	8,
			u8LEDSubVersion			:	8,
			u4PanelSize				:	8,
			u4PanelType				:	8;
} BE_LED_VERSION_T;

typedef struct
{
	UINT32	u4LEDLutStatus			:	4,		// 0 : NO LUT,	1 : LUT Update, 2 : LUT Error, 3 : LUT Normal
			u4LEDControlStatus		:	4,		// 0 : Not ready, 1 : Normal
			u16LEDVersion			:	16,
			reserved				:	8;
} BE_LED_STATUS_T;

typedef struct
{
	UINT32	bInit					:	4,
			reserved				:	28;
} BE_LED_INIT_BLOCK_T;

typedef struct
{
	UINT32	u32LedLutDDRAddr;
} BE_LED_LUT_ADDR_T;

typedef struct
{
	UINT32	bLoad					:	4,
			reserved				:	28;
} BE_LED_LOAD_LUT_T;

typedef struct
{
	UINT32	u4PictureMode			:	4,		// 0: Lowest, 1:Low, 2:Medium, 3:High
			reserved				:	28;
} BE_LED_MODE_T;

typedef struct
{
	UINT32	u4DimminOn				:	4,		// 0 : OFF(smooth),	1 : ON(smooth), 2 : OFF(instant), 3 : ON(instant)
			bStoreMode				:	4,		// 0 : OFF,	1 : ON
			reserved				:	24;
} BE_LED_CONTROL_T;

typedef struct
{
	UINT32	u32HDRLutVersion;
} BE_HDR_VERSION_T;

typedef struct
{
	UINT32	u8LutLoadStatus			:	8,
			u8RunStatus				:	8,
			u16HDRVersion			:	16;
} BE_HDR_STATUS_T;

typedef struct
{
	UINT32	bInit					:	4,
			reserved				:	28;
} BE_HDR_INIT_BLOCK_T;

typedef struct
{
	UINT32	u32HdrLutDDRAddr;
} BE_HDR_LUT_ADDR_T;

typedef struct
{
	UINT32	bLoad					:	4,
			reserved				:	28;
} BE_HDR_LOAD_LUT_T;

typedef struct
{
	UINT32	u4DECMode			:	4,
			u4DCMode			:	4,
			bDCBypass			:	4,
			bDCsc				:	4,
			bOSD				:	4,
			bStore				: 	4,
			reserved			:	8;
} BE_HDR_MODE_T;

typedef struct
{
	UINT32	bDECEnable			:	4,
			bDRCEnable			:	4,
			reserved			:	24;
} BE_HDR_CONTROL_T;

typedef struct
{
	UINT32	u32WCGLutVersion;
} BE_WCG_VERSION_T;

typedef struct
{
	UINT32	u8LutLoadStatus		:	8,
			u8RunStatus			:	8,
			u16WCGVersion		:	16;
} BE_WCG_STATUS_T;

typedef struct
{
	UINT32	bInit				:	4,
			reserved			:	28;
} BE_WCG_INIT_BLOCK_T;

typedef struct
{
	UINT32	u32WcgLutDDRAddr;

} BE_WCG_LUT_ADDR_T;

typedef struct
{
	UINT32	bLoad				:	4,
			reserved			:	28;
} BE_WCG_LOAD_LUT_T;

typedef struct
{
	UINT32	u4PictureMode		:	4,		//  0 :Bypass, 1:BT709, 2:SMPTE, 3:EBU, 4:Color Extension
			reserved			:	28;
} BE_WCG_MODE_T;

typedef struct
{
	UINT32	bEnable				:	4,
			reserved			:	28;
} BE_WCG_CONTROL_T;

typedef struct
{
	UINT32	u16PwmDuty			:	16,
			u8PwmFreq			:	8,			// (FREQ>>2) eg) 120 ==> 30, 240 ==> 60, 480 ==> 120
			u4PwmControl		:	4,		//	0 : ENABLE,  1 : VSYNC LOCK mode,  2 : Free Run mode
			reserved			:	4;
} BE_PWM_TX_T;		//		= 0x60000000,	// control, duty, freq

typedef struct
{
	UINT32	u16PwmDuty			:	16,			// PWM duty
			u16PwmdFreq			:	16;		// Reference PWM Freq
} BE_PWM_RX_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _BE_DRV_H_ */

/** @} */

