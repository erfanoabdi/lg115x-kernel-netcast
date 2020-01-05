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
 *  ipc def header file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.08
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _IPC_DEF_H_
#define _IPC_DEF_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define MCU_IPC_DEBUG

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define IPC_TOTAL_SIZE		 	0x20
#define IPC_BUFF_NUM			 100
#define MSG_STR_MAX			 2048

#define IPC_FROM_DE_SIZE	 0x8
#define IPC_FROM_CPU_SIZE	 ((IPC_TOTAL_SIZE-IPC_FROM_DE_SIZE)/2)
#define IPC_FROM_MCU_SIZE	 ((IPC_TOTAL_SIZE-IPC_FROM_DE_SIZE)/2)
#define IPC_FROM_CPU_DATA_SIZE
#define IPC_FROM_MCU_DATA_SIZE 

#define IPC_STR_MAX			 IPC_FROM_CPU_SIZE

#define INT_WDG_BIT  MCU_INT_WDG
#define INT_DMA_BIT  MCU_INT_DMA
#define INT_LED_BIT  MCU_INT_LED
#define INT_DPPA_BIT MCU_INT_DPPA
#define INT_SRE_BIT  MCU_INT_SRE
#define INT_LRX_BIT  MCU_INT_LRX
#define INT_DVO_BIT  MCU_INT_DVO
#define INT_DVI_BIT  MCU_INT_DVI
#define INT_H3D_BIT  MCU_INT_H3D
#define INT_SWI_BIT  MCU_INT_SWI

#define INT_WDG_MASK  (1 << MCU_INT_WDG)
#define INT_DMA_MASK  (1 << MCU_INT_DMA)
#define INT_LED_MASK  (1 << MCU_INT_LED)
#define INT_DPPA_MASK (1 << MCU_INT_DPPA)
#define INT_SRE_MASK  (1 << MCU_INT_SRE)
#define INT_LRX_MASK  (1 << MCU_INT_LRX)
#define INT_DVO_MASK  (1 << MCU_INT_DVO)
#define INT_DVI_MASK  (1 << MCU_INT_DVI)
#define INT_H3D_MASK  (3 << MCU_INT_H3D)
#define INT_SWI_MASK  (0x3FFF << MCU_INT_SWI)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define IPC_SET_DEFAULT_PARAM(structure, name)  \
	do{\
		memset(&name, 0xFF, sizeof(structure));\
	}while(0)

#define IPC_SET_GET_PARAM(structure, name)	IPC_SET_DEFAULT_PARAM(structure, name)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	FWI_IPC_SIZE ,
	FWI_IPC_CONT ,
	FWI_IPC_FROM ,
	FWI_IPC_TYPE ,
	FWI_IPC_DATA ,
} FWI_IPC_CMD_T;

typedef enum {
	FWI_IPC_FROM_UART = 1 ,
	FWI_IPC_FROM_HOST = 2 ,
	FWI_IPC_FROM_MAX = 0xFFFF
} FWI_IPC_FROM_T;

typedef enum { 
	FWI_IPC_CMD_CLI = 1 ,
	FWI_IPC_CMD_VAL = 2 ,
	FWI_IPC_CMD_RET = 3 ,	// MCU -> CPU return value
	FWI_IPC_CMD_DBG = 4, 	// MCU -> CPU request for DEBUG : switch UART0 (MCU to CPU), MCU reset etc.
	FWI_IPC_CMD_SYNC = 5,	// MCU -> CPU interrupt : VSYNC rate changed -> PWM frequency change
	FWI_IPC_CMD_MAX = 0xFFFF
} FWI_IPC_DATA_TYPE_T;

typedef enum {
	FWI_IPC_OK,
	FWI_IPC_BUSY,
	FWI_IPC_EMPTY,
	FWI_IPC_LAST,
} FWI_IPC_STATUS_T;

typedef struct {
	UINT16 u16From;
	UINT16 u16Type;
	UINT32 u32Cmd;
	UINT32 u32Data;
} FWI_IPC_MSG_T;

typedef struct {
	UINT32 wInx;
	UINT32 rInx;
	UINT32 queMax;
	UINT32 queOverflow;
	UINT8  str[IPC_BUFF_NUM][IPC_STR_MAX];
} FWI_EXCHANGE_T;

typedef enum {
	FWI_IPC_PACK,
	FWI_IPC_UNPACK
} FWI_IPC_PACKING_T;

typedef enum {
	INT_HWI,
	INT_SWI
} BE_INT_TYPE_T;

typedef enum {
	INT_CPU_MCU_ACK,
	INT_CPU_MCU_IPC,
	INT_MCU_CPU_ACK,
	INT_MCU_CPU_IPC,
	INT_DE_MCU_ACK,
	INT_DE_MCU_IPC,
	INT_TYPE_MAX
} BE_INT_DIR_TYPE_T;

typedef enum {
	MCU_INT_WDG = 0,
	MCU_INT_GPIO,
	MCU_INT_DMA,
	MCU_INT_SWI,
	MCU_INT_MAX = 32
} BE_MCU_INT_TYPE_T;  

typedef enum {
	CPU_INT_WDG = 0,
	CPU_INT_DMA,
	CPU_INT_LED,
	CPU_INT_DPPA,
	CPU_INT_SRE,
	CPU_INT_LRX,
	CPU_INT_DVO,
	CPU_INT_DVI,
	CPU_INT_H3D0,
	CPU_INT_H3D1,
	CPU_INT_SWI = 15, // 15 ~ 31
	CPU_INT_MAX = 32
} BE_CPU_INT_TYPE_T;

typedef enum {
	DE_INT_WDG = 0,
	DE_INT_DMA,
	DE_INT_LED,
	DE_INT_DPPA,
	DE_INT_SRE,
	DE_INT_LRX,
	DE_INT_DVO,
	DE_INT_DVI,
	DE_INT_H3D = 8,  // 8 ~ 9

	DE_INT_SWI = 10, // 10 ~ 31

	DE_INT_MAX = 32
} BE_DE_INT_TYPE_T;

typedef enum {
	SWI_TYPE_IPC = 0x00000001,	
	SWI_TYPE_ACK = 0x00000002,

	SWI_MAX
} BE_SWI_TYPE_T;

typedef enum {
	BE_TOP_INIT					= 0x00000000,
	BE_TOP_STATUS,
	BE_TOP_TOGGLE_3D_LR,
	BE_TOP_SET_3D_IN_FORMAT,
	BE_TOP_SET_3D_OUT_FORMAT,	
	BE_TOP_SET_3D_SYNC_DELAY,		
	BE_TOP_SET_3D_CONVERGENCE,		
	BE_TOP_SET_BLACK_BAR,	
	BE_TOP_SET_VIDEO_MUTE,			
	BE_TOP_SET_MUTE_COLOR,			
	BE_TOP_SET_BLOCK_BYPASS,		
	BE_TOP_SET_DISPLAY_TYPE,		
	BE_TOP_SET_DEBUG_DISPLAY,		
	BE_TOP_SET_VID_OPERATION,
	BE_TOP_SET_SRC_TYPE,
	BE_TOP_SET_ACTIVE_WINDOW_START,
	BE_TOP_SET_ACTIVE_WINDOW_SIZE,

	BE_H3D_GET_VERSION		= 0x10000000,
	BE_H3D_GET_STATUS,
	BE_H3D_INIT_BLOCK,
	BE_H3D_RESET_BLOCK,
	BE_H3D_BYPASS_ALL,
	BE_H3D_SET_MODE,
	BE_H3D_IN_FORMAT,
	BE_H3D_T3C_DEPTH_LEVEL,
	BE_H3D_A3C_DEPTH_LEVEL,	
	BE_H3D_A3C_AUTOCONVERGENCE,
	BE_H3D_GET_A3C_DMINMAX,
	
	BE_FRC_GET_FIRMWARE_VERSION	= 0x20000000,
	BE_FRC_GET_STATUS,
	BE_FRC_INIT_BLOCK,
	BE_FRC_SET_MEMC_MODE,
	BE_FRC_SET_LOW_DELAY,
	BE_FRC_SET_DEMO_MODE,
	BE_FRC_BYPASS_REGION,
	BE_FRC_BYPASS_REGION0_XY,
	BE_FRC_BYPASS_REGION0_WH,
	BE_FRC_BYPASS_REGION1_XY,
	BE_FRC_BYPASS_REGION1_WH,
	BE_FRC_BYPASS_REGION2_XY,
	BE_FRC_BYPASS_REGION2_WH,
	BE_FRC_BYPASS_REGION3_XY,
	BE_FRC_BYPASS_REGION3_WH,	
	BE_FRC_FORCE_FRAME_RATE,
	BE_FRC_SET_YUV444,
	BE_FRC_SET_FAST_MV_TH,
	BE_FRC_SET_STILL_DET_TH,
	BE_FRC_SET_SAME_DET_TH,
	BE_FRC_SET_DIFF_DET_TH,
	BE_FRC_SET_VMODE_ERR_CNT,
	BE_FRC_SET_JUDDER_SLOPE,
	BE_FRC_SET_MIN_ERR_TH,
	BE_FRC_SET_ABNORMAL_SYNC_CNT,
	BE_FRC_INIT_DB_ADDR,
	BE_FRC_ENABLE_DEBUG_BOX,

	BE_SRE_GET_VERSION		= 0x30000000, // SRE
	BE_SRE_GET_STATUS,
	BE_SRE_INIT_BLOCK,
	BE_SRE_BYPASS_ALL,
	BE_SRE_SET_LUT_ADDR,
	BE_SRE_LOAD_LUT,
	BE_SRE_SET_MODE,
	BE_SRE_CONTROL,
	BE_SRE_SET_INPUT_MODE,
	BE_SRE_SET_DB_GRADE,
	BE_SRE_SR_STRENGTH_LEVEL,
	BE_SRE_UPDATE_ALL,
	BE_SRE_WRITE_ADDRESS,
	BE_SRE_WRITE_DATA,
	BE_SRE_READ_ADDRESS,
	BE_SRE_GET_DATA,

	//SRE IPC Command for H13B0
	BE_SRE_GLOBAL_SCALE	= 0x30000016,
	BE_SRE_LOCAL_SCALE,
	BE_SRE_PREPROCESSING,
	BE_SRE_NOISE_CONTROL,
	BE_SRE_LOCAL_BYPASS,
	BE_SRE_CLIP_CONTROL,
	BE_SRE_WEIGHT_CONTROL,
	BE_SRE_ETC_CONTROL,
	
	BE_PE_GET_STATUS		= 0x40000000,	// DPPA
	BE_PE_INIT_BLOCK,
	BE_PE_SET_CEN_GAIN0,
	BE_PE_SET_CEN_GAIN1,
	
	BE_LED_GET_VERSION		= 0x50000000,	// DPPB
	BE_LED_GET_STATUS,
	BE_LED_INIT_BLOCK,
	BE_LED_SET_LUT_ADDR,
	BE_LED_LOAD_LUT,
	BE_LED_SET_MODE,
	BE_LED_CONTROL,		// store, dimming, pix_comp
	BE_HDR_GET_VERSION,
	BE_HDR_GET_STATUS,
	BE_HDR_INIT_BLOCK,
	BE_HDR_SET_LUT_ADDR,
	BE_HDR_LOAD_LUT,
	BE_HDR_SET_MODE,
	BE_HDR_CONTROL,
	BE_WCG_GET_VERSION,
	BE_WCG_GET_STATUS,
	BE_WCG_INIT_BLOCK,
	BE_WCG_SET_LUT_ADDR,
	BE_WCG_LOAD_LUT,
	BE_WCG_SET_MODE,
	BE_WCG_CONTROL,

	BE_PWM_SET_TX_CH0		= 0x60000000,	// control, duty, freq
	BE_PWM_SET_TX_CH1,
	BE_PWM_SET_TX_CH2,
	BE_PWM_GET_RX_CH0,
	BE_PWM_GET_RX_CH1,

	BE_DBG_UART_SWITCH		= 0xF0000000,	// DEBUG only (MCU -> CPU)
	BE_DBG_RESET
} BE_IPC_DEF_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _IPC_DEF_H_ */

/** @} */











