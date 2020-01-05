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


/** @file de_kapi.h
 *
 *	application interface header for de device
 *
 *	@author		dongho7.park (dongho7.park@lge.com)
 *	@version		0.6a
 *	@date		2009.12.30
 *
 *	@addtogroup lg1150_de
 *	@{
 */

#ifndef _DE_KAPI_H_
#define _DE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#ifndef USE_XTENSA
#include "base_types.h"
#include "de_kapi_eval.h"	// for fpga evaluation
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define DE_IOC_MAGIC		'a'
/**
@name DE IOCTL List
ioctl list for de device.

@{
@def DE_IOW_DE_INIT
Initialize de module.
device open and reset
set default register for clock, csc etc.
enable irq and set intr mask
load ucode

@def DE_IOR_GET_FIRMWARE_INFO
Reads de firmware information( version and update info).

@def DE_IOW_SET_BG_COLOR
set background color (non-active region color).
L8 support back_color y(8bit) cb(4bit) cr(4bit) at window compose block(OV)

@def DE_IOR_GET_OUT_FR_RATE
get display output frame rate (50 or 60).

@def DE_IOW_SET_WIN_BLANK
set window blank, to support mote control.
L8 support dark_color y(8bit) cb(4bit) cr(4bit) at window compose block(OV)

@def DE_IOR_GET_INPUT_WIN
get scaler input window size and position.
depend on source size and crop.

@def DE_IOR_GET_OUT_WIN
get scaler output window size and position.
depend on display size and picture mode.

@def DE_IOW_SET_INPUT_WIN
set scaler input window size and position.
depend on source size and crop.

@def DE_IOW_SET_OUT_WIN
set scaler output window size and position.
depend on display size and picture mode.

@def DE_IOW_SET_FREEZE
Freeze moving picture.

@def DE_IOW_SET_INPUT_SRC
set path of input source.

@def DE_IOW_SET_DIS_OUT
on/off de display output

@def DE_IOW_SET_DIS_FMT
set de display size and frame rate, etc.
depend on panel attribute.
display parameter setting (DE1A DISP_PARAM0~3)

@def DE_IOW_SET_FR_RATE
set display frame rate and mode(forced freerun or not).

@def DE_IOW_SET_IRE_PATTERN
set color and IRE levels of full pattern.
used for factory adjustment.

@def DE_IOW_SET_MULTI_WIN
set multi window mode including split window mode.
used for auto demo mode of 60Hz display(PDP).

@def DE_IOW_MULTI_WIN_ENABLE
enable/disable multi window mode including split window mode.
used for auto demo mode on/off of 60Hz display(PDP).
also set picture quality parameters for enhanced side of window.

@def DE_IOWR_GRAB_PIXEL
grab video pixels of certain block size and position.
used for factory adjustment.

@def DE_IOR_GET_MVI_TIMING_INFO
get mpeg decoder timing parameters.
used for periodic video task.

@def DE_IOW_SET_SPREAD
set LVDS spread spectrum for 60Hz mode (PDP).
for above 120Hz mode, FRC controls LVDS spread spectrum
also see the CTOP CTR54[31:0] control register of SSPLL

@def DE_IOW_SET_CVI_SRC_TYPE
set captured(external) video source attribute.
channel A or B, size, offset, color, scan type, aspect ratio).

@def DE_IOW_SET_CVI_CSC
send color space conversion matrix and offset for each external source information.
RGB to YCbYr.

@def DE_IOW_SET_POST_CSC
send color space conversion matrix for post processing block
YCbCr to RGB.

@def DE_IOR_GET_MVI_COLORIMETRY
get MVI source colorimetry information.

@def DE_IOW_SET_ZLIST
control video/osd layers.
Controled by OSD_LAYER_MUX

@def DE_IOW_SET_DEINTERLACE
for deinterlace on/off control

@def DE_IOW_SET_PRE3D_IN_MODE
select pre-3D input mode  (0: normal mode, 1:frame by frame mode)

@def DE_IOW_SET_PRE3D_OPR_MODE
select pre-3D operation mode (0: off  1: on 2: bypass )

@def DE_IOW_SET_PWM
set de PWM parameter. only used for 60Hz LCD panel.
OIF selects DE PWM(60Hz) or FRC PWM(120Hz).

@def DE_IOW_SET_PWM_CONTROL
set de PWM Control parameter. only used for 60Hz LCD panel.
OIF selects DE PWM(60Hz) or FRC PWM(120Hz).

@def DE_IOW_SET_CVE
set de CVE parameter.
select CVE feedback path and timing parameters.

@def DE_IOW_SET_VCS
set de VCS parameter.
transfer information of VCS to MCU part via IPC

@def DE_IOR_GET_CAPTURE_WIN
get de captured video size and offset

@def DE_IOW_SET_CAPTURE_WIN
set de captured video size and offset

@def DE_IOW_SET_ECANVAS
set de ecanvas on/off and ecanvas source path

@def DE_IOW_OIF_INIT
Initialize OIF module.

@def DE_IOW_OIF_SET_LVDS_OUTPUT
Set LVDS OUTPUT Enable/Disable.
Each 24 channels can be controled separately

@def DE_IOW_OIF_SET_LVDS_POWER
LVDS power down.

@def DE_IOW_OIF_SET_DARK_SCREEN
set LVDS to dark screen.

@def DE_IOW_OIF_SET_VESA_JEIDA
Select LVDS type(VESA/JEIDA).

@def DE_IOW_OIF_SET_PANEL_IF
select LVDS inteface type(LVDS/mini-LVDS).

@def DE_IOW_OIF_SET_PIXEL
set LVDS pixel type( single/dual/quad).

@def DE_IOW_OIF_SET_BIT_DEPTH
set LVDS bit resolution(10bit/8bit).

@def DE_IOW_OIF_SELECT_OUT_PATH
select LVDS output path.
set LVDS signal path from DE/FRC/LED/(ODC removed)

@def DE_IOW_OIF_SELECT_LVDS_PATH
select LVDS output path.
select LVDS signal path from one of DE/FRC/LED or from ODC

@def DE_IOW_OIF_SELECT_OUT_CH
select output chanel number.
1ch/2ch/4ch

@def DE_IOW_OIF_SELECT_LED_PATH
select LED input path from DE/FRC.

@def DE_IOW_OIF_SELECT_PWM_PATH
select PWM signal path from DE or FRC.

@def DE_IOW_OIF_SELECT_LR_PATH
select LR signal path from DE or FRC.

@def DE_IOR_OIF_GET_INFO
get OIF setting information.

@def DE_IOW_OIF_SET_LVDS_OUT_CTRL
LVDS ouput channel control.
Single or Dual LVDS, LVDS Data select.

@def DE_IOW_OIF_SET_LVDS_PORT_SWAP
LVDS port Swap Control.

@def DE_IOW_FW_DOWNLOAD
downdload Firmware of DE

@def DE_IOW_SET_CVI_FIR
set FIR coefficient of captured video source.

@def DE_IOW_SET_CVI_TPG
set test pattern generator of captured video source.

@def DE_IOW_SET_CVI_CSAMPLE_MODE
set captured source color sub-sampling method.

@def DE_IOW_SET_CVI_SYNC_RESHAPE
reshape captured input sync timing for PC source.

@def DE_IOR_GET_CVI_INFO
get CVI frame rate for external inputs.

@def DE_IOW_SET_PE_BBD_CTRL
set black boundary detection control value

@def DE_IOW_GET_PE_BBD_STATUS
get black boundary status value(window start/end point)

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define DE_IOW_DE_INIT					_IOW(DE_IOC_MAGIC, 0, LX_DE_PANEL_TYPE_T )
#define DE_IOR_GET_FIRMWARE_INFO		_IOR(DE_IOC_MAGIC, 1, LX_DE_FIRMWARE_INFO_T )
#define DE_IOW_SET_BG_COLOR				_IOW(DE_IOC_MAGIC, 2, LX_DE_COLOR_T )
#define DE_IOR_GET_OUT_FR_RATE			_IOR(DE_IOC_MAGIC, 3, LX_DE_FR_RATE_T )
#define DE_IOW_SET_WIN_BLANK			_IOW(DE_IOC_MAGIC, 4, LX_DE_SET_WIN_BLANK_T )

// scaler window
#define DE_IOR_GET_INPUT_WIN			_IOR(DE_IOC_MAGIC, 5, LX_DE_WIN_DIMENSION_T )
#define DE_IOR_GET_OUT_WIN				_IOR(DE_IOC_MAGIC, 6, LX_DE_WIN_DIMENSION_T )
#define DE_IOW_SET_INPUT_WIN			_IOW(DE_IOC_MAGIC, 7, LX_DE_WIN_DIMENSION_T )
#define DE_IOW_SET_OUT_WIN				_IOW(DE_IOC_MAGIC, 8, LX_DE_WIN_DIMENSION_T )

#define DE_IOW_SET_FREEZE				_IOW(DE_IOC_MAGIC, 9, LX_DE_SET_FREEZE_T )
#define DE_IOW_SET_INPUT_SRC			_IOW(DE_IOC_MAGIC, 10, LX_DE_SET_INPUT_T )
#define DE_IOW_SET_DIS_OUT				_IOW(DE_IOC_MAGIC, 11, BOOLEAN )
#define DE_IOW_SET_DIS_FMT				_IOW(DE_IOC_MAGIC, 12, LX_DE_DIS_FMT_T )
#define DE_IOW_SET_FR_RATE				_IOW(DE_IOC_MAGIC, 13, LX_DE_FR_RATE_T )
#define DE_IOW_SET_IRE_PATTERN			_IOW(DE_IOC_MAGIC, 14, LX_DE_SET_IRE_PATTERN_T )

// PDP demo
#define DE_IOW_SET_MULTI_WIN			_IOW(DE_IOC_MAGIC, 15, LX_DE_MULTI_WIN_TYPE_T )
#define DE_IOW_MULTI_WIN_ENABLE			_IOW(DE_IOC_MAGIC, 16, BOOLEAN )

// GP3에서 VCS 관련 PIP 필요할 수 있음

#define DE_IOWR_GRAB_PIXEL				_IOWR(DE_IOC_MAGIC, 17, LX_DE_GRAB_PIXEL_T )
#define DE_IOR_GET_MVI_TIMING_INFO		_IOR(DE_IOC_MAGIC, 18, LX_DE_MVI_TIMING_INFO_T )

#define DE_IOW_SET_SPREAD				_IOW(DE_IOC_MAGIC, 19, LX_DE_SET_SPREAD_T )

// cvi
#define DE_IOW_SET_CVI_SRC_TYPE			_IOW(DE_IOC_MAGIC, 20, LX_DE_CVI_SRC_TYPE_T )

// CSC
#define DE_IOW_SET_CVI_CSC				_IOW(DE_IOC_MAGIC, 21, LX_DE_CVI_CSC_T )
#define DE_IOR_GET_CVI_CSC				_IOR(DE_IOC_MAGIC, 22, LX_DE_CVI_CSC_T )
#define DE_IOW_SET_POST_CSC				_IOW(DE_IOC_MAGIC, 23, LX_DE_POST_CSC_T )  // PE1
#define DE_IOR_GET_POST_CSC				_IOR(DE_IOC_MAGIC, 24, LX_DE_POST_CSC_T )  // PE1
#define DE_IOR_GET_MVI_COLORIMETRY		_IOR(DE_IOC_MAGIC, 25, LX_DE_MVI_COLORIMETRY_T )

// video layer order  add 2010. 1. 21
#define DE_IOW_SET_ZLIST				_IOW(DE_IOC_MAGIC, 26, LX_DE_ZLIST_T )
#define DE_IOW_SET_DEINTERLACE			_IOW(DE_IOC_MAGIC, 27, BOOLEAN )

#define DE_IOW_SET_UART_FOR_MCU			_IOW(DE_IOC_MAGIC, 28, BOOLEAN )

// pre-3D
#define DE_IOW_SET_PRE3D_IN_MODE		_IOW(DE_IOC_MAGIC, 29, LX_DE_PRE3D_IN_MODE_T )
#define DE_IOW_SET_3D_OPR_MODE			_IOW(DE_IOC_MAGIC, 30, LX_DE_3D_OPR_MODE_T )
#define DE_IOW_SET_3D_FULL_MODE			_IOW(DE_IOC_MAGIC, 31, LX_DE_3D_FULL_MODE_T )

// UD
#define DE_IOW_SET_UD_MODE				_IOW(DE_IOC_MAGIC, 32, BOOLEAN )

// CVE
#define DE_IOW_SET_CVE					_IOW(DE_IOC_MAGIC, 33, LX_DE_CVE_PARAM_T )

// VCS
#define DE_IOW_SET_VCS					_IOW(DE_IOC_MAGIC, 34, LX_DE_VCS_IPC_T )

// for DE debug
#define DE_IOR_REG_RD					_IOR(DE_IOC_MAGIC, 35, UINT32)
#define DE_IOW_REG_WR					_IOW(DE_IOC_MAGIC, 36, LX_DE_REG_WR_T)

// add for dynamic picture size update
#define DE_IOR_GET_CAPTURE_WIN			_IOR(DE_IOC_MAGIC, 37, LX_DE_CVI_CAPTURE_WIN_T )
#define DE_IOW_SET_CAPTURE_WIN			_IOW(DE_IOC_MAGIC, 38, LX_DE_CVI_CAPTURE_WIN_T )

// E canvas DE0B 0x000c e-canvas enable BOOLEAN isEnable
#define DE_IOW_SET_ECANVAS				_IOW(DE_IOC_MAGIC, 39, LX_DE_ECANVAS_T )

// OIF
#define DE_IOW_OIF_INIT					_IOW(DE_IOC_MAGIC, 40, LX_DE_OIF_INFO_T)
#define DE_IOW_OIF_SET_LVDS_OUTPUT		_IOW(DE_IOC_MAGIC, 41, BOOLEAN)
#define DE_IOW_OIF_SET_LVDS_POWER		_IOW(DE_IOC_MAGIC, 42, BOOLEAN)
#define DE_IOW_OIF_SET_DARK_SCREEN		_IOW(DE_IOC_MAGIC, 43, BOOLEAN)
#define DE_IOW_OIF_SET_VESA_JEIDA		_IOW(DE_IOC_MAGIC, 44, LX_DE_OIF_STD_T)
#define DE_IOW_OIF_SET_PANEL_IF			_IOW(DE_IOC_MAGIC, 45, LX_DE_OIF_PANEL_IF_T)
#define DE_IOW_OIF_SET_PIXEL			_IOW(DE_IOC_MAGIC, 46, LX_DE_OIF_PIXEL_T)
#define DE_IOW_OIF_SET_BIT_DEPTH		_IOW(DE_IOC_MAGIC, 47, LX_DE_OIF_BIT_DEPTH_T)
#define DE_IOW_OIF_SELECT_OUT_PATH		_IOW(DE_IOC_MAGIC, 48, LX_DE_OIF_OUTPUT_PATH_T)
#define DE_IOW_OIF_SELECT_LVDS_PATH		_IOW(DE_IOC_MAGIC, 49, LX_DE_OIF_LVDS_PATH_T)
#define DE_IOW_OIF_SELECT_OUT_CH		_IOW(DE_IOC_MAGIC, 50, LX_DE_OIF_OUTPUT_CH_T)	// add 2010. 5. 17
#define DE_IOW_OIF_SELECT_LED_PATH		_IOW(DE_IOC_MAGIC, 51, LX_DE_OIF_LED_IN_PATH_T)
#define DE_IOW_OIF_SELECT_PWM_PATH		_IOW(DE_IOC_MAGIC, 52, LX_DE_OIF_PWM_PATH_T)
#define DE_IOW_OIF_SELECT_LR_PATH		_IOW(DE_IOC_MAGIC, 53, LX_DE_OIF_LR_PATH_T) // add 2010. 7. 13
#define DE_IOR_OIF_GET_INFO				_IOR(DE_IOC_MAGIC, 54, LX_DE_OIF_INFO_T)
#define DE_IOW_OIF_SET_LVDS_OUT_CTRL	_IOW(DE_IOC_MAGIC, 55, LX_DE_OIF_LVDS_OUT_CTRL_T)
#define DE_IOW_OIF_SET_LVDS_PORT_SWAP	_IOW(DE_IOC_MAGIC, 56, BOOLEAN)			// add 2011. 11. 4 for UD fornat

#define DE_IOW_IPC_CLI					_IOW(DE_IOC_MAGIC, 59, LX_DE_IPC_CLI_T)
#define DE_IOW_FW_DOWNLOAD				_IOW(DE_IOC_MAGIC, 60, LX_DE_FW_DWLD_T)

#define DE_IOW_SET_CVI_FIR				_IOW(DE_IOC_MAGIC, 61, LX_DE_CVI_FIR_T )
#define DE_IOW_SET_CVI_TPG				_IOW(DE_IOC_MAGIC, 62, LX_DE_CVI_TPG_T )
#define DE_IOW_SET_CVI_CSAMPLE_MODE		_IOW(DE_IOC_MAGIC, 63, LX_DE_CSAMPLE_MODE_T )
#define DE_IOW_SET_CVI_SYNC_RESHAPE		_IOW(DE_IOC_MAGIC, 64, LX_DE_CVI_SYNC_RESHAPE_T )
#define DE_IOR_GET_CVI_INFO				_IOR(DE_IOC_MAGIC, 65, LX_DE_CVI_INFO_T )

// use PE block
#define DE_IOW_SET_PE_TEST_PATTERN_GEN	_IOW(DE_IOC_MAGIC, 67, LX_DE_PE_TPG_T )
#define DE_IOW_SET_PE_BBD_CTRL			_IOW(DE_IOC_MAGIC, 68, LX_DE_PE_BBD_CTRL_T )
#define DE_IOW_GET_PE_BBD_STATUS		_IOR(DE_IOC_MAGIC, 69, LX_DE_PE_COORDINATE_T )

#define DE_IOW_SET_EDGECROP				_IOW(DE_IOC_MAGIC, 70, BOOLEAN )

// DE PWM
#define DE_IOW_SET_PWM_CONTROL			_IOW(DE_IOC_MAGIC, 71, LX_DE_PWM_CTRL_T )
#define DE_IOW_SET_PWM_FREQUENCY		_IOW(DE_IOC_MAGIC, 72, LX_DE_PWM_FREQ_T )
#define DE_IOW_SET_PWM_PULSE_WIDTH		_IOW(DE_IOC_MAGIC, 73, LX_DE_PWM_PULSE_T )
#define DE_IOW_SET_PWM_DUTY_CYCLE		_IOW(DE_IOC_MAGIC, 74, LX_DE_PWM_PARAM_T )

#define DE_IOW_SET_TABLE				_IOW(DE_IOC_MAGIC, 75, LX_DE_SET_TABLE_T )
#define DE_IOW_SET_DVR_FMT_CTRL			_IOW(DE_IOC_MAGIC, 76, LX_DE_DVR_DISFMT_T )

// de display frame(osd+video) capture in msc-r or subscaler path
#define DE_IOW_FC_SET_WIN_INFO			_IOW(DE_IOC_MAGIC, 77, LX_DE_RECT_T )
#define DE_IOR_FC_GET_FRAME_INFO		_IOR(DE_IOC_MAGIC, 78, LX_DE_FC_PARAM_T )

// de freeze sub scaler frame in msc-r or subscaler path
#define DE_IOW_SET_SUB_SC_FREEZE		_IOW(DE_IOC_MAGIC, 79, BOOLEAN )

// de cvi video frame buffer freeze to read/write video frame before cvi csc parameter for self-diagnosis.
#define DE_IOW_SET_CVI_FREEZE			_IOW(DE_IOC_MAGIC, 80, LX_DE_CVI_CAPTURE_FREEZE_T )

// de read/write video frame before CVI csc parameter for self-diagnosis.
#define DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER			_IOWR(DE_IOC_MAGIC, 81, LX_DE_CVI_RW_VIDEO_FRAME_T )

// de use the vdec memory in the CVI path
#define DE_IOW_VDEC_MEM_SHARE			_IOW(DE_IOC_MAGIC, 82, BOOLEAN )

// de multi window source for cvi input.
#define DE_IOWR_SELECT_MULTI_WIN_SRC		_IOWR(DE_IOC_MAGIC, 84, LX_DE_MULTI_WIN_SRC_T )

// de get current de cpu/mvi port(A/B/C/D)
#define DE_IOR_GET_CPU_MVI_PORT			_IOR(DE_IOC_MAGIC, 85, LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T )
// de set current de cpu/mvi port(A/B/C/D)
#define DE_IOW_SET_CPU_MVI_PORT			_IOW(DE_IOC_MAGIC, 86, LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T )

// de set low delay mode for frame delay
#define DE_IOR_GET_LOW_DELAY			_IOR(DE_IOC_MAGIC, 87, LX_DE_LOW_DELAY_T )
#define DE_IOW_SET_LOW_DELAY			_IOW(DE_IOC_MAGIC, 88, UINT32 )

// PWM Duty Read for external port
#define DE_IOR_GET_EXTERNAL_PWM			_IOR(DE_IOC_MAGIC, 89, LX_DE_EXTERNAL_PWM_T )

// de set current 3D info through middleware(G-streamer)
#define DE_IOW_SET_3D_INFO_THROUGH_MIDDLEWARE  _IOW(DE_IOC_MAGIC, 90, LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T )

// de get current 3D info through middleware(G-streamer)
#define DE_IOW_GET_3D_INFO_THROUGH_MIDDLEWARE  _IOW(DE_IOC_MAGIC, 91, LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T )

// de get par info
#define DE_IOR_GET_PAR_INFO				_IOW(DE_IOC_MAGIC, 92, LX_DE_PAR_WIN_RECT_T)
// de debug.
#define DE_IOR_GET_DBG					_IOR(DE_IOC_MAGIC, 93, LX_DE_SET_DBG_T)
#define DE_IOW_SET_DBG					_IOW(DE_IOC_MAGIC, 94, LX_DE_SET_DBG_T)

#define DE_IOW_SET_SCART_RGB_BYPASS_MODE	_IOW(DE_IOC_MAGIC, 95, int)

#define DE_IOW_SET_MULTI_VISION				_IOW(DE_IOC_MAGIC, 96, LX_DE_RECT_T )
// from FMT3D (FMT3D_IOW_SET_INOUT_CTRL)
#define DE_IOW_SET_3D_INOUT_CTRL   			_IOW(DE_IOC_MAGIC, 97, LX_DE_3D_INOUT_CTRL_T )

// ioctl for h13 verification
#define DE_IOW_SET_EVAL_DBG				_IOWR(DE_IOC_MAGIC, 99, LX_DE_SET_EVAL_DBG_T)

//#ifndef DE_H13_IOCTL
#define DE_IOW_SET_IF_CONFIG			_IOW(DE_IOC_MAGIC, 101, LX_DE_IF_CONFIG_T)
#define DE_IOR_GET_SYS_STATUS			_IOR(DE_IOC_MAGIC, 102, LX_DE_SYS_STATUS_T)
#define DE_IOR_GET_SRC_STATUS			_IOR(DE_IOC_MAGIC, 103, LX_DE_SRC_STATUS_T)

#define DE_IOW_SET_IN_SRC				_IOW(DE_IOC_MAGIC,111, LX_DE_INPUT_CFG_T )			// IOCTL 10, 84 sum
#define DE_IOW_SET_TIMING_INFO		_IOW(DE_IOC_MAGIC,112, LX_DE_INPUT_CFG_T )			// IOCTL 10, 84 sum

#define DE_IOW_SET_OPERATION			_IOW(DE_IOC_MAGIC,113, LX_DE_OPERATION_CTRL_T )			// IOCTL 96, 32, 16 sum
#define DE_IOW_SET_SUB_OPERATION		_IOW(DE_IOC_MAGIC,114, LX_DE_SUB_OPERATION_CTRL_T )			// IOCTL 10, 84 sum

#define DE_IOW_SET_CAPTURE			_IOW(DE_IOC_MAGIC, 120, LX_DE_CAPTURE_CTRL_T )			// IOCTL 9, sum
#define DE_IOW_SET_FRAME_TO_OSD		_IOW(DE_IOC_MAGIC, 121, LX_DE_OSD_FRAME_CTRL_T)
#define DE_IOR_GET_FRAME_FOR_OSD		_IOR(DE_IOC_MAGIC, 122, LX_DE_OSD_FRAME_CTRL_T)
#define DE_IOR_GET_SCALER_INFO		_IOR(DE_IOC_MAGIC, 123, LX_DE_SCALER_INFO_T)
//#define DE_IOW_SET_FREEZE_H13			_IOW(DE_IOC_MAGIC, 120, LX_DE_SET_FREEZE_T )			// IOCTL 9, sum
//#endif

#define DE_IOC_MAXNR				255
/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/**
 * de display (panel) type, full HD or HD.
 */
typedef enum {
	LX_PANEL_TYPE_1920 = 0, ///< full HD
	LX_PANEL_TYPE_1366,		///< WXGA(HD)
	LX_PANEL_TYPE_1024,		///< 1024x768
	LX_PANEL_TYPE_1365,		///< 1365x768
	LX_PANEL_TYPE_3840,		///< 3840x2160
	LX_PANEL_TYPE_1280,		///< 1280x720
	LX_PANEL_TYPE_720,		///< 720x480
	LX_PANEL_TYPE_640,		///< 640x480
	LX_PANEL_TYPE_576,		///< 720x576
	LX_PANEL_TYPE_MAX		///< max number
}
LX_DE_PANEL_TYPE_T;


/**
 * de display (panel) device type
 */
typedef enum {
	LX_PANEL_DEV_LCD, 		///< LCD/LED device
	LX_PANEL_DEV_PDP,		///< PDP device
	LX_PANEL_DEV_OLED,		///< OLED device
	LX_PANEL_DEV_BOX,		///< CP box device
	LX_PANEL_DEV_GTV_STB,		///< Set-top box device for GTV
	LX_PANEL_DEV_MAX		///< max number
}
LX_DE_PANEL_DEV_T;

/**
 * de date type for firmware version info.
 */
typedef struct {
	UINT16 year;			///< year
	UINT16 month;			///< month
	UINT16 day;				///< day
}
LX_DE_DATE_T;

/**
 * de firmware u-code information.
 */
typedef struct {
	UINT32	version;		///< firmware version
	LX_DE_DATE_T date;		///< updated date
}
LX_DE_FIRMWARE_INFO_T;

/**
 * de source window index.
 */
typedef enum {
	LX_DE_WIN_MAIN = 0, ///< main window
	LX_DE_WIN_SUB,		///< sub window
	LX_DE_WIN_MAX		///< max number
}
LX_DE_WIN_ID_T;

/**
 * de horizontal(vertical) start, size in pixel.
 */
typedef struct
{
	UINT16		w;	///< horizontal Size(Width)    in pixel
	UINT16		h;	///< vertical	Size(Height)   in pixel
	UINT16		x;	///< horizontal Start Position in pixel
	UINT16		y;	///< vertical	Start Position in pixel
}
LX_DE_RECT_T;

/**
 * de input window horizontal(vertical) start, size information.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;	///< window index
	LX_DE_RECT_T rect;		///< window demension(w,h,x,y)
}
LX_DE_WIN_DIMENSION_T;

/**
 * de display nonactive region color parameter.
 * de window color for no signal or mute time.
 */
typedef struct {
	UINT8  r;	///< red
	UINT8  g;	///< green
	UINT8  b;	///< blue
}
LX_DE_COLOR_T;

/**
 * de enable input window blank and define window color(black or blue).
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;			///< window index
	BOOLEAN bEnable;				///< mute enable
	LX_DE_COLOR_T win_color;		///< mute color
	BOOLEAN	isRGB;					///< mute color domain
}
LX_DE_SET_WIN_BLANK_T;

/**
 * de enable image freezing in each windows.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;			///< window index
	BOOLEAN bEnable;				///< freeze enable
}
LX_DE_SET_FREEZE_T;

/**
 * de input source parameter.
 */
typedef enum {
	LX_DE_SRC_CVI  ,				///< captured external video input
	LX_DE_SRC_MVI  ,				///< video from MPEG decoder A
	LX_DE_SRC_CPU  ,				///< video from system memory A
	LX_DE_SRC_NONE ,				///< No Video
	LX_DE_SRC_MAX					///< Max
}
LX_DE_INPUT_SRC_T;

/**
 * de input source type.
 */
typedef struct {
	LX_DE_WIN_ID_T	  win_id;		///< window index
	LX_DE_INPUT_SRC_T inputSrc;		///< de video input source for each window
	UINT8			  port_id;		///< input Source port index (A -> 0, B -> 1)
}
LX_DE_SET_INPUT_T;

/**
 * de output format type.
 */
typedef struct {
	LX_DE_PANEL_TYPE_T panel_type;		///< display size
	UINT16 fr_rate;						///< display frame rate
	UINT16 h_total;						///< pixels per line
	UINT16 v_total;						///< lines per frame
	UINT16 h_active;					///< active pixel per line
	UINT16 v_active;					///< active lines per frame
	LX_DE_PANEL_DEV_T dev_type;			///< display device type
}
LX_DE_DIS_FMT_T;

/**
 * de output frame rate mode.
 */
typedef struct {
//	LX_DE_WIN_ID_T win_id;			///< window index --> window ID is not needed
	BOOLEAN isForceFreeRun;			///< enable forced free run mode
	UINT16 fr_rate;				///< frame rate
}
LX_DE_FR_RATE_T;

/**
 * de IRE test patterns colors.
 */
typedef enum
{
	LX_IRE_PATTERN_DISABLE,			///< no pattern
	LX_IRE_PATTERN_WHITE,			///< full white
	LX_IRE_PATTERN_RED,				///< full red
	LX_IRE_PATTERN_GREEN,			///< full green
	LX_IRE_PATTERN_BLUE,			///< full blue
	LX_IRE_PATTERN_MAX				///< max number
}
LX_DE_IRE_PATTERN_T;

/**
 * de IRE test patterns type(color and IRE value).
 */
typedef struct {
	LX_DE_IRE_PATTERN_T ire_pattern;		///< IRE pattern color
	UINT16 level;							///< IRE level
}
LX_DE_SET_IRE_PATTERN_T;

/**
 * de multi window types for auto demo.
 */
typedef enum {
	LX_MULTI_WIN_OFF,			///< off
	LX_MULTI_WIN_H_SPLIT,		///< horizontal split
	LX_MULTI_WIN_MOVE,			///< moving
	LX_MULTI_WIN_ZOOM,			///< zoom
	LX_MULTI_WIN_NUMS			///< max number
}
LX_DE_MULTI_WIN_TYPE_T;

/**
 * de region type of graped pixels.
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;
	UINT32 pixelGrabX;		///< x position
	UINT32 pixelGrabY;		///< y position
	UINT32 pixelGrabW;		///< capture width
	UINT32 pixelGrabH;		///< capture h

	UINT32 realPixelGrabW;	///< real W in memory
	UINT32 realPixelGrabH;	///< real H in memory
	UINT8 colorSpace;		///< 0: YUV 1:RGB
	UINT8 colorDepth;		///< 0: 8bit 1: 10bit
}
LX_DE_GRAB_REGION_T;

/**
 * de color type of graped pixels.
 */
typedef struct
{
	UINT16 pixelGrabCb;		///< Cb or B
	UINT16 pixelGrabY;		///< Y or G
	UINT16 pixelGrabCr;		///< CR or R
}
LX_DE_GRAB_COLOR_T;

/**
 * de graped pixel parameter.
 */
typedef struct
{
	LX_DE_GRAB_REGION_T region; ///< graped region
	LX_DE_GRAB_COLOR_T	color;	///< graped pixels color value
}
LX_DE_GRAB_PIXEL_T;

/**
 * de scan type parameter.
 */
typedef enum {
	LX_DE_INTERLACED,		///< interlaced scan
	LX_DE_PROGRESSIVE		///< progressive scan
}
LX_DE_SCAN_T;


/**
 * de mvi 3D Video Information. for[L9]
 *
 */

typedef enum
{
    //interim format - half
	LX_DE_MVI_3D_CHECKERBOARD = 0,		///< 3D check board format
	LX_DE_MVI_3D_COLUMN_INTERLEAVING,	///< 3D column interleaving format
	LX_DE_MVI_3D_ROW_INTERLEAVING,		///< 3D row interleaving format(line alternative)
	LX_DE_MVI_3D_SIDEBYSIDE,			///< 3D Side by Side format
	LX_DE_MVI_3D_TOPNBOTTOM,			///< 3D top and bottom format
	LX_DE_MVI_3D_FRAMESEQ,				///< 3D frame sequence format

    //Full format
	LX_DE_MVI_3D_FRAMEPACK,		    ///< 3D frame packing format
	LX_DE_MVI_3D_FIELD_ALTERNATIVE,	    ///< 3D field alternative format
	LX_DE_MVI_3D_LINE_ALTERNATIVE,		///< 3D line alternative format
	LX_DE_MVI_3D_SIDEBYSIDE_FULL,		///< 3D Side by Side full format
	LX_DE_MVI_3D_DUALSTREAM,			///< 3D dual stream format
    //  From UI, 3D ON이면서 아래 Format이 넘어오면 2D to 3D 가 됨
	LX_DE_MVI_3D_2DTO3D,				///< 3D format for2D TO 3D..... INPUT_TYPE_2DTO3D
	LX_DE_MVI_2D,						///< 2D format

    LX_DE_MVI_3D_FORMAT_MAX,

} LX_DE_MVI_3D_INFO_T;

/**
 * de mvi 3D L/R order
 *
 */
 typedef enum
{
	LX_DE_MVI_3D_R_FIRST = 0,			///< right first
	LX_DE_MVI_3D_L_FIRST,			    ///< left first
	LX_DE_MVI_3D_LR_ORDER_MAX			///< max number
}
LX_DE_MVI_3D_LR_ORDER_T;
/**
 * de Debug set type.
 */
 typedef enum {
	LX_DE_DBG_PIXEL_SHIFT = 0,			///< HDMI 13.5 MHz CSC 422 Issue - Pixel Shift
	LX_DE_DBG_SYNC_POSITION = 1,		///< source sync position value for HDMI & RGB
	LX_DE_DBG_CVI_RESET = 2,			///< CVI reset information of CTOP
	LX_DE_DBG_MAX						///< max number
}
LX_DE_DBG_SET_TYPE_T;


/**
 * de Debug set debug type.
 */
typedef struct {
	LX_DE_WIN_ID_T			win_id;			///< window index
	LX_DE_DBG_SET_TYPE_T	type;			///< debug set type
	BOOLEAN					bParam;			///< BOOLEAN parameter
	UINT32					u32Param;		///< UINT32 parameter 1
	UINT32					u32ParamOne;	///< UINT32 parameter 2
}
LX_DE_SET_DBG_T;

/**
 * de video timing parameter of vdec interface.
 * used for adaptaion & DDI
 */
typedef struct {
	UINT16 h_size;								///< mvi picture horizontal size
	UINT16 v_size;								///< mvi picture vertical size
	UINT16 h_start;								///< mvi picture horizontal position
	UINT16 v_start;								///< mvi picture vertical position
	LX_DE_SCAN_T isProg;						///< mvi picture scan type(0 : interlace, 1 : progressive)
	UINT16 v_freq;								///< mvi picture vertical frequency
	LX_DE_MVI_3D_INFO_T  mvi_3dfmt_info;		///< MVI 3D Format Information
	LX_DE_MVI_3D_LR_ORDER_T  mvi_3dlr_order;	///< MVI 3D LR Order Information
}
LX_DE_MPEG_TIMING_INFO_T;

/**
 * de video timing parameter of vdec interface.
 * used for kdriver
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;	///< window index
	LX_DE_MPEG_TIMING_INFO_T mpeg_time;
}
LX_DE_MVI_TIMING_INFO_T;

/**
 * de spread spectrum parameter.
 */
typedef enum {
	LX_DE_SPREAD_SPECTRUM_MAIN, ///< main just for debugging purpose
	LX_DE_SPREAD_SPECTRUM_FRC,	///< frc just for debugging purpose
	LX_DE_SPREAD_SPECTRUM_CPU,	///< cpu just for debugging purpose
	LX_DE_SPREAD_SPECTRUM_LVDS	///< lvds(Display)
}
LX_DE_SET_SPREAD_TYPE_T;

/**
 * de spread spectrum parameter.
 * if FRC support this fuction, then this is not used
 */
typedef struct {
	UINT16 period;		///< period
	UINT16 percent;		///< percent
	BOOLEAN bEnable;	///< on/off
	LX_DE_SET_SPREAD_TYPE_T type;  ///< main/frc
}
LX_DE_SET_SPREAD_T;

/**
 * de cvi source size offset parameter.
 */
typedef struct {
	UINT16	hsize;		///< horizontal pixels
	UINT16	vsize;		///< vertical lines
	UINT16	hoffset;		///< horizontal pixel offset
	UINT16	voffset;	///< vertical line offset
}
LX_DE_CVI_DIMENSION_T;

/**
 * de cvi source color format type.
 */
typedef enum
{
	LX_DE_COLOR_601,		///< SD
	LX_DE_COLOR_709,		///< HD
	LX_DE_COLOR_RGB,		///< PC/DVI 16~235
	LX_DE_COLOR_RGBEX,		///< PC/DVI 0~255
	LX_DE_COLOR_XVYCC601,	///< HDMI deep color for SD
	LX_DE_COLOR_XVYCC709,	///< HDMI deep color for HD
	LX_DE_COLOR_601_CVD,	///< CVBS through CVD
	LX_DE_COLOR_NOT_DEFINED
}
LX_DE_COLOR_STD_T;

/**
 * de cvi source aspect ratio type.
 */
typedef enum
{
	LX_DE_AR_4_3,		///< 4:3
	LX_DE_AR_16_9		///< 16:9
}
LX_DE_AR_T;


/**
 * de cvi channels type.
 */
typedef enum
{
	LX_DE_CVI_CH_A,		///< channel A
	LX_DE_CVI_CH_B		///< channel B
}
LX_DE_CVI_CHANNEL_T;

/**
 * de cvi bit resolution.
 */
typedef enum
{
	LX_DE_CVI_10BIT,	///< 10 bit
	LX_DE_CVI_8BIT		///< 8 bit
}
LX_DE_CVI_BITRES_T;

/**
 * de cvi chroma sampling.
 */
typedef enum
{
	LX_DE_CVI_422,	///< 16bit 422 chroma sampling
	LX_DE_CVI_444	///< 24bit 444 chroma sampling
}
LX_DE_CVI_CSAMPLE_T;

/**
 * de scaler operating chroma sampling.
 */
typedef enum
{
	LX_DE_SCALER_420,	///< YUV 420 chroma sampling
	LX_DE_SCALER_422,	///< YUV 422 chroma sampling
	LX_DE_SCALER_444	///< YUV 444 chroma sampling
}
LX_DE_SCALER_CSAMPLE_T;

/**
 * de cvi data enable mode.
 * hv offsets must be set to zero
 */
typedef enum
{
	LX_DE_CVI_NORMAL_SYNC_MODE,		///< sync mode for CVD, ADC
	LX_DE_CVI_HDMI_SYNC_MODE		///< sync mode for HDMI
}
LX_DE_CVI_SYNC_MODE_T;

/**
 * de cvi data sampling mode.
 */
typedef enum
{
	LX_DE_CVI_NORMAL_SAMPLING,	///< sync mode for CVD, ADC
	LX_DE_CVI_DOUBLE_SAMPLING,	///< sync mode for HDMI
	LX_DE_CVI_QUAD_SAMPLING		///< sync mode for HDMI
}
LX_DE_CVI_SAMPLING_MODE_T;

/**
 * de cvi data sync stability.
 */
typedef enum
{
	LX_DE_CVI_SYNC_STD,			///< sync is stable
	LX_DE_CVI_SYNC_NONSTD		///< sync is unstable
}
LX_DE_CVI_SYNC_STABILITY_T;

/**
 * de cvi field polarity.
 */
typedef enum
{
	LX_DE_CVI_FIELD_ORIGINAL,		///< original field polarity
	LX_DE_CVI_FIELD_REVERSED		///< reversed field polarity
}
LX_DE_CVI_FIELD_POLARITY_T;

/**
 * de cvi yc delay.
 */
typedef enum
{
	LX_DE_CVI_YC_DELAY_BYPASS,		///< yc_delay_mode_r = 0, yc_delay_mode_b = 0, yc_delay_mode_g = 0
	LX_DE_CVI_YC_DELAY_ATV,			///< yc_delay_mode_r = 0, yc_delay_mode_b = 3, yc_delay_mode_g = 2
	LX_DE_CVI_YC_DELAY_OTHERS		///< yc_delay_mode_r = 0, yc_delay_mode_b = 2, yc_delay_mode_g = 1
}
LX_DE_CVI_YC_DELAY_T;

/**
 * de cvi port select. for [L9]
 */
typedef enum
{
	LX_DE_CVI_EXT_A,  ///<
	LX_DE_CVI_EXT_B,  ///<
	LX_DE_CVI_CVD,	  ///<
	LX_DE_CVI_ADC	  ///<
}
LX_DE_CVI_PORT_T;

/**
 * de cvi 3D Video Full Information. for[L9]
 *
 */
typedef enum
{
	LX_DE_CVI_NORMAL_FORMAT = 0,		///< 2D format
	LX_DE_CVI_3D_FRAMEPACK,				///< 3D frame packing format
	LX_DE_CVI_3D_SBSFULL,				///< 3D Side by Side Full format
	LX_DE_CVI_3D_FIELD_ALTERNATIVE,		///< 3D field alternative format
	LX_DE_CVI_3D_ROW_INTERLEAVING,		///< 3D row interleaving format(line alternative)
	LX_DE_CVI_3D_COLUMN_INTERLEAVING,	///< 3D column interleaving format
	LX_DE_CVI_4K_2K,						///< 4K x 2K format
} LX_DE_CVI_3D_FULL_INFO_T;

/**
 * de cvi source type Information. for[L9]
 *
 */
typedef enum
{
	// Component Analog ports
	LX_DE_CVI_SRC_VGA,
	LX_DE_CVI_SRC_YPBPR,

	// Composite Analog ports
	LX_DE_CVI_SRC_ATV,
	LX_DE_CVI_SRC_CVBS,

	// Seperate Analog Ports
	LX_DE_CVI_SRC_SVIDEO,

	// SCART port
	LX_DE_CVI_SRC_SCART,

	// HDMI ports
	LX_DE_CVI_SRC_HDMI,

	LX_DE_CVI_SRC_NUM,

} LX_DE_CVI_INPUT_SRC_T;

/**
 * This enum is used to set CVD PQ Value to selected Color System
 * @see AFE_IOW_SET_3DCOMB_VALUE
 */

typedef enum {
	LX_DE_COLOR_DEFAULT		= 0,		///< Default CVD Params
	LX_DE_COLOR_NTSC_M		= 1,		///< CVD Params for NTSC_M AV inputs
	LX_DE_COLOR_NTSC_M_RF	= 2,		///< CVD Params for NTSC_M RF input
	LX_DE_COLOR_PAL			= 3,		///< CVD Params for NTSC_M AV inputs
	LX_DE_COLOR_PAL_RF		= 4,		///< CVD Params for NTSC_M RF input
	LX_DE_COLOR_SECAM		= 5,		///< CVD Params for NTSC_M AV inputs
	LX_DE_COLOR_SECAM_RF	= 6,		///< CVD Params for NTSC_M RF input
	LX_DE_COLOR_NTSC_443	= 7,		///< CVD Params for NTSC_443 AV inputs
	LX_DE_COLOR_NTSC_443_RF = 8,		///< CVD Params for NTSC_443 RF input
	LX_DE_COLOR_PAL_60		= 9,		///< CVD Params for PAL_60 AV inputs
	LX_DE_COLOR_PAL_60_RF	= 10,		///< CVD Params for PAL_60 RF input
	LX_DE_COLOR_PAL_M		= 11,		///< CVD Params for PAL_M AV inputs
	LX_DE_COLOR_PAL_M_RF	= 12,		///< CVD Params for PAL_M RF input
	LX_DE_COLOR_PAL_NC		= 13,		///< CVD Params for PAL_NC AV inputs
	LX_DE_COLOR_PAL_NC_RF	= 14,		///< CVD Params for PAL_NC RF input
	LX_DE_COLOR_UNKNOWN   	= 15,		///< CVD Params for Color System Unkown
	LX_DE_COLOR_NUM			= 16,
} LX_DE_CVD_COLOR_STD_T;

/**
 * de cvi source attribute type.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T		   cvi_channel;		  ///< CVI channel A or B
	LX_DE_CVI_DIMENSION_T	   size_offset;		  ///< h/v size offset
	LX_DE_COLOR_STD_T		   color;			  ///< color space 601,709,PC
	LX_DE_AR_T				   aspect;			  ///< aspect ratio 4:3 or 16:9
	LX_DE_SCAN_T			   scan;			  ///< interlaced or progressive
	LX_DE_CVI_BITRES_T		   bit_res;			  ///< bit resolution 10bit(0) or 8bit(1)
	LX_DE_CVI_CSAMPLE_T		   c_sample;		  ///< chroma sampling mode 422(0) or 444(1)
	LX_DE_CVI_SYNC_MODE_T	   de_mode;			  ///< internal data enable mode generated from sync(0) or de(1)
	LX_DE_CVI_SAMPLING_MODE_T  sampling;		  ///< external input sampling: noraml(0), double(1), quadrature(2)
	LX_DE_SCALER_CSAMPLE_T	   sc_c_sample;		  ///< scaler chroma sampling mode YUV420(0) YUV422(1) YUV444(2)
	LX_DE_CVI_SYNC_STABILITY_T stability;		  ///< stable sync(0), unstable sync(1)
	LX_DE_CVI_FIELD_POLARITY_T field_polarity;	  ///< original field polarity(0), reversed field polarity(1)
	LX_DE_CVI_YC_DELAY_T	   yc_delay;
	LX_DE_CVI_PORT_T		   cvi_port;		  ///< cvi port select. for [L9]
	LX_DE_CVI_3D_FULL_INFO_T   trid_full_format;  ///< 3D Video Full Information. for [L9]
	LX_DE_CVI_INPUT_SRC_T	   cvi_input_src;	  ///< cvi source type Information. for[L9]
	LX_DE_CVD_COLOR_STD_T	   cvd_color_std;	  ///< CVD color mode for[L9]
}
LX_DE_CVI_SRC_TYPE_T;

/**
 * de cvi capture window type.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	LX_DE_CVI_DIMENSION_T  size_offset;		///< h/v size offset
}
LX_DE_CVI_CAPTURE_WIN_T;

/**
 * de cvi source color scpace conversion parameter.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN isEnable;					///< enable csc loading or bypass
	UINT16 CSC_matrix[9];	///< CSC matrix coefficient
	UINT16 CSC_offset[6];	///< CSC matrix coefficient
}
LX_DE_CVI_CSC_T;

/**
 * de captured source FIR control parameter.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN isEnable;					///< fir enable
	UINT16 fir_coef[8];					///< fir coefficient
	UINT16 fir_coef_CbCr[6];			///< CbCr fir coefficient, add from L9 B0, by sh.myoung 201108
}
LX_DE_CVI_FIR_T;

/**
 * de cvi test pattern gen. pattern type.
 */
typedef enum
{
	LX_DE_CVI_TPG_WHITE,		///< white
	LX_DE_CVI_TPG_YELLOW,		///< yellow
	LX_DE_CVI_TPG_CYAN,			///< cyan
	LX_DE_CVI_TPG_GREEN,		///< green
	LX_DE_CVI_TPG_MAGENTA,		///< magenta
	LX_DE_CVI_TPG_RED,			///< red
	LX_DE_CVI_TPG_BLUE,			///< blue
	LX_DE_CVI_TPG_BLACK,		///< black
	LX_DE_CVI_TPG_GRADATION_H,	///< horizontal gradation
	LX_DE_CVI_TPG_GRADATION_V,	///< vertical gradation
	LX_DE_CVI_TPG_GRADATION_C,	///< color gradation
	LX_DE_CVI_TPG_GRADATION_YC, ///< Y/C gradation
	LX_DE_CVI_TPG_BW			///< black and white
}
LX_DE_CVI_TPG_COLOR_T;

/**
 * de captured test pattern generator.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN isPtnOn;					///< pattern enable
	BOOLEAN isFrzOn;					///< freeze enable
	BOOLEAN isGBR;						///< pattern color space
	LX_DE_CVI_TPG_COLOR_T ptnColor;		///< pattern color
}
LX_DE_CVI_TPG_T;

/**
 * de cvi info for external inputs.
 */
typedef struct {
	LX_DE_WIN_ID_T	  win_id;	///< window index --> window ID is not needed
	UINT16 fr_rate;				///< frame rate
	UINT16 line_num;			///< line number of one frame(field)
	UINT16 line_width;			///< width of one line
}
LX_DE_CVI_INFO_T;

/**
 * de captured source color sub-sampling parameter.(for YUV422)
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN is3tap;					///< sub_sample(0), 3-tap-filter[1:2:1] (1)
}
LX_DE_CSAMPLE_MODE_T;

/**
 * de captured source sync reshape parameter.(for PC mode)
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN isEnable;					///< sync reshape enable
	UINT16 hsync_delay;					///< horizontal sync delay from input horizontal sync
	UINT16 hfp_delay;					///< horizontal front porch delay from input horizontal front porch
	UINT16 vsync_delay;					///< vertical sync delay from input vertical sync
	UINT16 vfp_delay;					///< vertical front porch delay from input vertical front porch
}
LX_DE_CVI_SYNC_RESHAPE_T;

/**
 * de captured source sync status parameter.(for debug)
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN h;					///< hsync status
	BOOLEAN v;					///< vsync status
	BOOLEAN de;					///< de status
	BOOLEAN valid;				///< source valid
	UINT16 lnum;				///< current line number
}
LX_DE_CVI_SYNC_STATUS_T;

/**
 * de post processing  color scpace conversion parameter.
 */
typedef struct {
	//LX_DE_WIN_ID_T win_id;	///< window index
	UINT16 CSC_matrix[9];	///< CSC matrix coefficient
	UINT16 CSC_offset[6];	///< CSC matrix coefficient
}
LX_DE_POST_CSC_T;

/**
 * de colorimetry information of mpeg decoder (vdec).
 * used for kdriver
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;	///< window index
	LX_DE_COLOR_STD_T colorimetry;	///< colorimetry of MPEG (601 or 709)
}
LX_DE_MVI_COLORIMETRY_T;

/**
 * de video layer type definition.
 * layer order of video,osd1,2,3 can be changed
 */

typedef enum {
	LX_SURFACE_VIDEO = 0,	///< video layer
	LX_SURFACE_OSD1 = 1,	///< osd layer 1
	LX_SURFACE_OSD2 = 2,	///< osd layer 2
	LX_SURFACE_OSD3 = 3,	///< osd layer 3
	LX_SURFACE_CURSOR = 4,	///< osd cursor layer
	LX_SURFACE_MAX			///< max number
}
LX_DE_SURFACE_T;

/**
 * de video layer(z-order) control type.
 */

typedef struct {
	BOOLEAN enable;				///< z-list on/off (off : hw default order, win0-bottom/win1-top)
	UINT32 z_list[2];			///< index : order(0->top, 1->bottom) , value : win_id
	UINT32 alpha[2];			///< index : order(0->top, 1->bottom) , value : blending alpha
}
LX_DE_ZLIST_T;

/**
 * de ECANVAS parameter.
 */
typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B
	BOOLEAN isEnable;					///< Enable ecanvas
}
LX_DE_ECANVAS_T;

/* ############### DE 3D ################ */

/**
 * de 3D operating mode type.
 *
 */
typedef enum {
	LX_3D_OFF = 0,	///< de pre-3D block off, de T3 block off, frc 3d formatter off
	LX_3D_ON,		///< de pre-3D block on,  de T3 block off, frc 3d formatter on
	LX_3D_BYPASS,	///< for internal used by mcu
	LX_3D_2DTO3D,	///< de pre-3D block off, de T3 block on, frc 3d formatter on
	LX_3D_TB		///< de pre-3D block off, de T3 block used only for convergence, frc 3d formatter on
}
LX_DE_3D_OPR_MODE_T;

/**
 * de pre-3D input mode.
 *
 */
typedef enum {
	LX_PRE3D_IN_NORMAL = 0, ///< normal mode
	LX_PRE3D_IN_FRFR		///< frame by frame(?)
}
LX_DE_PRE3D_IN_MODE_T;

/**
 * de UD and specific 3D(SS Full & Frame Packing) operating mode type.
 *
 */
typedef enum
{
	LX_DE_3D_FULL_OFF,				///< OFF - 2D (No Data Bridge)
	LX_DE_3D_FULL_SS_FULL,			///< 3D Side by Side Full
	LX_DE_3D_FULL_FP_60HZ,			///< 3D Frame Packing 1080p@60Hz
	LX_DE_3D_FULL_MAX				///< max number
}
LX_DE_3D_FULL_MODE_T;

/* ############### DE PWM  ################ */

/**
 * de PWM port number index
 *
 */
typedef enum {
	LX_DE_PWM0 = 0, ///< pwm port0
	LX_DE_PWM1,		///< pwm port1
	LX_DE_PWM2,		///< pwm port2
	LX_DE_PWM3,		///< pwm port3
	LX_DE_PWM4		///< pwm port4
}
LX_DE_PWM_ID_T;

/**
 * de PWM control index
 *
 */
typedef enum {
	LX_DE_PWM_LOW	= 0,		///< PWM Output Signal Cotrol - Low
	LX_DE_PWM_NORMAL,			///< PWM Output Signal Cotrol - Normal
	LX_DE_PWM_HIGH,				///< PWM Output Signal Cotrol - High
	LX_DE_PWM_INVERSION,		///< PWM Output Signal Cotrol - Inversion
}
LX_DE_PWM_OUT_CTRL_T;

/**
 * de PWM output control parameter.
 * only used for 60Hz LCD panel.
 * OIF selects DE PWM(60Hz) or FRC PWM(120Hz).
 *
*/
typedef struct
{
	LX_DE_PWM_ID_T				port;		///< PWM number: PWM0~4.
	BOOLEAN						enable;
	BOOLEAN						pwmMode;		///< freerun(1) / locking(0) mode
	LX_DE_PWM_OUT_CTRL_T		PWMOutput;	///< PWM Output signal control
}
LX_DE_PWM_CTRL_T;

/**
 * de PWM parameter.
 * Parameter for PWM Frequency Set.
 * @see DE_IOW_SET_PWM_Frequency
*/
typedef struct
{
	LX_DE_PWM_ID_T	port;		///< PWM number: PWM0~4.
	UINT32			frequency;	///< PWM Output Frequency Set
}
LX_DE_PWM_FREQ_T;

/**
 * de PWM parameter.
 * only used for 60Hz LCD panel.
 * OIF selects DE PWM(60Hz) or FRC PWM(120Hz).
 *
*/
typedef struct
{
	LX_DE_PWM_ID_T	port;		///< PWM number: PWM0~4.
	UINT32			pulse;		///< Set pulse width of PWM.
}
LX_DE_PWM_PULSE_T;


/**
 * de PWM parameter.
 * only used for 60Hz LCD panel.
 * OIF selects DE PWM(60Hz) or FRC PWM(120Hz).
 *
*/
typedef struct
{
	LX_DE_PWM_ID_T	port;		///< PWM number: PWM0~4.
	UINT16			duty;		///< Set duty of PWM (0 ~ 100%).
	UINT16			offset;		///< PWM Start Position of DE(1~1125).
}
LX_DE_PWM_PARAM_T;

/**
 * de PWM parameter.
 * get PWM Duty value for external port(FRC) .
 *
*/
typedef struct
{
	UINT16			frequency;		///< current frequency (locking mode frequncy)
    UINT16			duty;		    ///< Set duty of PWM (0 ~ 255).
}
LX_DE_EXTERNAL_PWM_T;

/* ############### DE CVE  ################ */

/**
 * de DENC path selection
 * with OSD: set RGB to YUV mdm csc and mdm csc enable(use default csc coef.)
 * w/o OSD(PE1): set RGB to YUV mdm csc and mdm csc enable(use default csc coef.)
 * refer DE0B_CTRL/MDM_CTRL/MDM_CSC_COEF
 * w/o OSD(OV) : mdm csc disable
 */
typedef enum {
	LX_DE_CVE_WITH_OSD = 0,		///< Denc path feedback with OSD(DE end)
	LX_DE_CVE_WITHOUT_OSD,		///< Denc path feedback w/o OSD(select OV or PE1)
	LX_DE_CVE_FROM_SRC			///< Denc path from source ( original aspect ratio)
}
LX_DE_CVE_PATH_T;

/**
 * de DENC timing standard
 * PAL and SECAM have same sync parameters
 */
typedef enum {
	LX_DE_CVE_NTSC = 0,		///< Denc type is NTSC 60Hz
	LX_DE_CVE_PAL,			///< Denc type is PAL 50Hz
	LX_DE_CVE_SECAM			///< Denc type is SECAM 50Hz
}
LX_DE_CVE_TIMING_T;

/**
 * de CVE parameter.
 *
*/
typedef struct
{
	LX_DE_CVE_PATH_T	fb;		///< CVE feedback path (0: with OSD 1: w/o OSD)
	LX_DE_CVE_TIMING_T std;		///< CVE timing selection(0: NTSC 1: PAL 2:SECAM)
}
LX_DE_CVE_PARAM_T;

/**
 * de register value read type.
 */

typedef struct {
	UINT32 wr_addr; ///< register address
	UINT32 wr_data; ///< write data
}
LX_DE_REG_WR_T;

/**
 * DE Set Table Param
 */
typedef struct
{
	LX_DE_WIN_ID_T win_id;	///< window index

	const LX_DE_REG_WR_T *pTable;
	UINT32 size;
}
LX_DE_SET_TABLE_T;

/* ############### DE OIF  ################ */

/*-------------------------------------------------
	Res			Fr	out_ch	Led Tcon	FRC FRC3D
	HD(WXGA)	60		1	x	x		o	x
	HD(WXGA)	120		2	x	x		o	x
	FullHD		60		2	o	x		o	o
	FullHD		120		4	o	o		o	o
---------------------------------------------------*/

/**
 * OIF output video path type.
 *
 */
typedef enum {
	LX_OIF_OUTPUT_DE = 0,		///< DE OUTPUT
	LX_OIF_OUTPUT_FRC,			///< FRC OUTPUT
	LX_OIF_OUTPUT_LED			///< LED OUTPUT
}
LX_DE_OIF_OUTPUT_PATH_T;

/**
 * OIF lvds output path type.
 * Internal TCON support only 120Hz mode
 *
 */
typedef enum {
	LX_OIF_LVDS_NOT_ODC = 0,		///< one of DE/FRC/LED
	LX_OIF_LVDS_ODC					///< ODC OUTPUT
}
LX_DE_OIF_LVDS_PATH_T;

/**
 * OIF LED input path type.
 *
 */
typedef enum {
	LX_OIF_LED_IN_DE = 0,		///< LED input from DE
	LX_OIF_LED_IN_FRC			///< LED input from FRC
}
LX_DE_OIF_LED_IN_PATH_T;

/**
 * OIF PWM path type.
 *
 */
typedef enum {
	LX_OIF_PWM_DE = 0,		///< PWM from DE
	LX_OIF_PWM_FRC			///< PWM from FRC
}
LX_DE_OIF_PWM_PATH_T;

/**
 * OIF LR mux type.
 *
 */
typedef enum {
	LX_OIF_LR_DE = 0,		///< LR from DE
	LX_OIF_LR_FRC			///< LR from FRC
}
LX_DE_OIF_LR_PATH_T;

/**
 * OIF ouput channel number.
 *
 */
typedef enum {
	LX_OIF_1CH = 0,			///< OIF 1 Channel, WXGA 60Hz
	LX_OIF_2CH,				///< OIF 2 Channel, WXGA 120Hz, FullHD 60Hz
	LX_OIF_4CH,				///< OIF 4 Channel, FullHD 60Hz
	LX_OIF_CH_RESERVED		///< OIF Channel reserved
}
LX_DE_OIF_OUTPUT_CH_T;

/**
 * OIF output pixel type.
 *
 */
typedef enum {
	LX_OIF_PIXEL_SDQ = 0,		///< OIF sdq
	LX_OIF_PIXEL_SINGLE,		///< OIF Single
	LX_OIF_PIXEL_DUAL,			///< OIF Dual
	LX_OIF_PIXEL_QUAD			///< OIF Quad
}
LX_DE_OIF_PIXEL_T;

/**
 * OIF LVDS panel interface standard type.
 *
 */
typedef enum
{
	LX_DE_OIF_VESA,					///< VESA LVDS
	LX_DE_OIF_JEIDA					///< JEIDA LVDS
}
LX_DE_OIF_STD_T;

/**
 * OIF LVDS Panel interface type.
 * select LVDS or MINI-LVDS
 */
typedef enum
{
	LX_DE_OIF_PANEL_LVDS,					///< LVDS panel interface
	LX_DE_OIF_PANEL_MINI_LVDS				///< MINI-LVDS panel interface
}
LX_DE_OIF_PANEL_IF_T;

/**
 * OIF bit depth type.
 *
 */
typedef enum
{
	LX_DE_OIF_8BIT,					///< 8bit depth
	LX_DE_OIF_10BIT					///< 10bit depth
}
LX_DE_OIF_BIT_DEPTH_T;

/**
 * IPC for VCS
 * index of IPC for VCS
 * 0  : frame_inx
 * 1  : pic_info
 * 2  : frame_rate
 * 3  : aspect_ratio
 * 4  : picture_size
 * 5  : h_offset
 * 6  : v_offset
 * 7  : frameupdated
 * 8  : y_frame_base_address
 * 9  : c_frame_base_address
 * 10 : y_frame_offset
 * 11 : c_frame_offset
 * 12 : stride
 * 13 : pixel_aspect_ratio
 * 14 : vdi_framepackarrange
 * 15 : vdi_ptsinfo
 */
typedef struct
{
	UINT32			inx;		///< index of vcs for IPC
	UINT32			data;		///< data of vcs for IPC
}
LX_DE_VCS_IPC_T;

/**
 * OIF info parameter.
 *
 */
typedef struct {
	LX_DE_OIF_STD_T eVesaJeida;			///< 0 : VESA, 1 : JEDIA
	LX_DE_OIF_PANEL_IF_T eLvdsMini;		///< LVDS TX & Mini-LVDS TX selection 0:LVDS 1:Mini-LVDS
	LX_DE_OIF_PIXEL_T ePixel;			///< Port Select 0:sdq 1:single 2:dual 3:quad
	LX_DE_OIF_BIT_DEPTH_T eBitMode;		///< 0: 8 bit, 1: 10 bit
	LX_DE_OIF_OUTPUT_PATH_T eOutVideo;	///< Output select 0:DE 1:FRC 2:LED
	LX_DE_OIF_LVDS_PATH_T eOutLVDS;		///< Output select 0:one of DE/FRC/LED	1:ODC
	LX_DE_OIF_OUTPUT_CH_T	eOutCH;		///< CH select 0: one chanel 1: two channel 2: four channel
	LX_DE_OIF_LED_IN_PATH_T eLedIn;		///< LED input source from 0:DE 1:FRC
	LX_DE_OIF_PWM_PATH_T ePWM;			///< PWM signal from 0:DE 1:FRC
	LX_DE_OIF_LR_PATH_T eLR;			///< LR signal from 0:DE 1:FRC
}
LX_DE_OIF_INFO_T;


/**
 * OIF LVDS Output Channel control parameter.
 *
 */
typedef struct {
	BOOLEAN outMode;					///< lvds Out Mode 0: Single LVDS(High_LVDS), 1 : Dual LVDS for even, odd pixel
	UINT8	ch1LVDS;					///< lvds data selection for ch1  0 : DE1, 1: DE2, 2: OSD
	UINT8	ch2LVDS;					///< lvds data selection for ch2  0 : DE2, 1: DE1, 2: OSD
}
LX_DE_OIF_LVDS_OUT_CTRL_T;


/**
 * OIF LVDS interface control parameter.
 *
 */
typedef struct {
	UINT8	emptyData;		///< Empty Data
	BOOLEAN bitMode;		///< 1: 8 bit, 0 : 10 bit
	BOOLEAN lsbfirst;		///< LVDS lsbfirst
	UINT8	syncOrder;		///< LVDS_sync_order
	UINT8	ch3LVDS;		///< LVDS_ch3
	UINT8	ch2LVDS;		///< LVDS_ch2
	UINT8	ch1LVDS;		///< LVDS_ch1
	UINT8	ch0LVDS;		///< LVDS_ch0
	BOOLEAN outSel;			///< 0 : one of DE/FRC/LED (determined by out_sel), 1 : ODC
}
LX_DE_OIF_LVDS_IF_CTRL_T;

/**
 * OIF LVDS TX control parameter.
 * LVDS TX control register was trnsfered to CTOP LVDS_TX configuration registers.
 * CTOP CTR32 0xFD300090
 * CTOP CTR33 0xFD300094
 * CTOP CTR34 0xFD300098
 */

typedef struct {
	BOOLEAN pdb;				///< Power down control & PLL Reset--> CTOP pdb(Low:power down,outputs to Hi-Z) (High:normal)
	BOOLEAN rf;					///< Input data strobe edge selection --> CTOP rf(Low:falling of CLKIN, High:rasing of CLKIN)
	UINT32 rs;					///< LVDS output swing level control --> CTOP rs(CTR33 31:8, default 0xFFFFFF)(Low:reduced(~200mV@single), High:noraml(~350mV@single)
	UINT32 empCtrl;				///< Output emphasis control --> CTOP enpemp_h(CTR33 7:0)&l(CTR34 31:16) (Low:disable emphasis, High:enable emphasis)
	BOOLEAN miniLVDS;			///< LVDS TX & Mini-LVDS TX selection --> CTOP mini_en(Low:LVDS TX mode, High:Mini_LVDS TX mode)
	BOOLEAN miniFlip;			///< LVDS TX & Mini-LVDS polarity --> CTOP mini_flip_en(High : changed, L:not changed (** Default is 'L'))
	BOOLEAN swingLVDS;			///< Use exrenal resigtor for swing control --> CTOP rmlvds_en(H;External, L:Internal)
	UINT32	ovDrv;				///< Output Data and Clock over drive --> CTOP ovdrv(15:0)(H: Overdrive(+Diff. 100mV), L:Normal)
	UINT32	lvdsEn;				///< Output disable control for unused channel --> CTOP en(23:0)(Low:output to Hi-Z)(High:output enable)
}
LX_DE_OIF_LVDS_TX_CTRL_T;

/**
 * @brief de video ipc type to communicate between CPU and MCU
 */
typedef struct {
	int  cnt;					///< bytes to tranfer via IPC
	char *pStr;					///< buffer pointer to contain data via IPC
}
LX_DE_IPC_CLI_T;

/**
 * de FW Download.
 */
typedef struct {
	int  inx;					///< index --> 0:download all in de_fw.h, 1:led_fw, 2:de_iram, 3:de_ddr and run program
	int  size;					///< size  --> size of Firmware
	char *pData;				///< data  --> pointer carring data of Firmware
}
LX_DE_FW_DWLD_T;

/* ############### DE PE1 WINDOW ################ */

/**
 * de horizontal(vertical) start, end point in pixel.
 */
typedef struct
{
	UINT16		x0; ///< horizontal Start position in pixel
	UINT16		y0; ///< vertical Start position in pixel
	UINT16		x1; ///< horizontal end position in pixel
	UINT16		y1; ///< vertical end position in pixel
}
LX_DE_PE_COORDINATE_T;

/**
 * de set PE0 boundary scan ctrl.
 */
typedef struct {
	BOOLEAN isOn;							///< 0: disable, 1: enable
	UINT8 hysterisis;						///< hysterisis control(0: not use, 1~31 previous frames)
	UINT8 cnt_th;							///< counter threshold
	UINT8 diff_th;							///< difference threshold
}
LX_DE_PE_BBD_CTRL_T;

/**
 * de replace pixel data with arbitrary color data.
 */
typedef enum {
	LX_DE_WINBLANK_FULL,
	LX_DE_WINBLANK_FULL_BLUE,
	LX_DE_WINBLANK_WIN1_VCS,
	LX_DE_NONACTIVE_4_3,
	LX_DE_NONACTIVE_4_3_WR,
	LX_DE_NONACTIVE_VCS,
	LX_DE_NONACTIVE_3D,
	LX_DE_TPG_CLEAR_ALL,
	LX_DE_TPG_D3D_PTN,
	LX_DE_TPG_D3D_2D,
	LX_DE_TPG_D3D_3D,
	LX_DE_TPG_D3D_CB,
	LX_DE_TPG_D3D_CC,
	LX_DE_TPG_D3D_LL,
	LX_DE_TPG_D3D_SS,
	LX_DE_TPG_D3D_TB,
	LX_DE_TPG_MAX
}
LX_DE_PE_TPG_CONTROL_T;

/**
 * de PE TPG Control.
 */
typedef struct {
	BOOLEAN bOnOff;
	LX_DE_PE_TPG_CONTROL_T eControl;
}
LX_DE_PE_TPG_T;

/**
 * de DVR display format control. (de -> venc)
 */
typedef struct {
	BOOLEAN bOnOff;
	LX_DE_SCAN_T scan;
	UINT16 h_size;
	UINT16 v_size;
	UINT32 fr_rate;
	UINT32 baseAddr;
}
LX_DE_DVR_DISFMT_T;

/**
 * de get capture frame pointer
 */
typedef struct {
	UINT16 w;
	UINT16 h;
	UINT8 *p_y_frame;
	UINT8 *p_cbcr_frame;
}
LX_DE_FC_PARAM_T;

/**
 * de read/write video frame before CVI csc parameter for self-diagnosis.
 */
typedef struct
{
	LX_DE_GRAB_REGION_T region; ///< grapped region
	LX_DE_GRAB_COLOR_T	*color; ///< grapped pixels color value
	BOOLEAN bReadOnOff;			/// Read(True), Write(False)
}
LX_DE_CVI_RW_VIDEO_FRAME_T;

/**
 * input port for multi window
 */
typedef enum {
	LX_DE_PORT_MVI,
	LX_DE_PORT_CVD,
	LX_DE_PORT_ADC,
	LX_DE_PORT_HDMI
}
LX_DE_INPUT_PORT;

/**
 * de source for multi window
 */
typedef enum {
	LX_DE_MULTI_IN_CVD_ADC,
	LX_DE_MULTI_IN_CVD_HDMI,
	LX_DE_MULTI_IN_CVD_MVI,
	LX_DE_MULTI_IN_CVD_CPU,
	LX_DE_MULTI_IN_CVD_CVD,
	LX_DE_MULTI_IN_ADC_CVD,
	LX_DE_MULTI_IN_ADC_HDMI,
	LX_DE_MULTI_IN_ADC_MVI,
	LX_DE_MULTI_IN_ADC_CPU,
	LX_DE_MULTI_IN_ADC_ADC,
	LX_DE_MULTI_IN_HDMI_CVD,
	LX_DE_MULTI_IN_HDMI_ADC,
	LX_DE_MULTI_IN_HDMI_MVI,
	LX_DE_MULTI_IN_HDMI_CPU,
	LX_DE_MULTI_IN_HDMI_HDMI,
	LX_DE_MULTI_IN_MVI_CVD,
	LX_DE_MULTI_IN_MVI_ADC,
	LX_DE_MULTI_IN_MVI_HDMI,
	LX_DE_MULTI_IN_MVI_CPU,
	LX_DE_MULTI_IN_MVI_MVI,
	LX_DE_MULTI_IN_CPU_CVD,
	LX_DE_MULTI_IN_CPU_ADC,
	LX_DE_MULTI_IN_CPU_HDMI,
	LX_DE_MULTI_IN_CPU_MVI,
	LX_DE_MULTI_IN_CPU_CPU,

	LX_DE_MULTI_IN_MVA_MVB,
	LX_DE_MULTI_IN_HDMIA_HDMIB,
	LX_DE_MULTI_IN_MAX
}
LX_DE_MULTI_SRC_T;

/**
 * de input port for multi window source mapping
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;					///< window index
	LX_DE_INPUT_PORT in_port;			///< input port for multi window
}
LX_DE_MULTI_WIN_SRC_T;


/**
 * capture/freeze on or off for cvi capture
 */
typedef struct {
	BOOLEAN bCaptureOnOff;
	BOOLEAN bCviFreezeOnOff;			///< input port for multi window
}
LX_DE_CVI_CAPTURE_FREEZE_T;

/**
 * PQ Firmware Control
 */
typedef struct {
	UINT8 enable;
}
LX_DE_PQ_FIRMWARE_CTRL;

/**
 * PE1 Sharpness Coring Control_05
 */
typedef struct {
	UINT8 gt_th0;
	UINT8 gt_th1;
}
LX_DE_SHP_CORING_CTRL_05;

/**
 * PE1 Sharpness Coring Control_06
 */
typedef struct {
	UINT8 gt_th0a;
	UINT8 gt_th0b;
}
LX_DE_SHP_CORING_CTRL_06;

/**
 * PE1 Sharpness Coring Control_09
 */
typedef struct {
	UINT8 edge_gain_b;
	UINT8 edge_gain_w;
	UINT8 texture_gain_b;
    UINT8 texture_gain_w;
}
LX_DE_SHP_CORING_CTRL_09;

/**
 * PE1 Sharpness DP Control_01
 */
typedef struct {
	UINT8 edge_gain_b;
	UINT8 edge_gain_w;
	UINT8 texture_gain_b;
    UINT8 texture_gain_w;
}
LX_DE_SHP_DP_CTRL_01;


/**
 * PE1 Sharpness DERH Control_08
 */
typedef struct {
	UINT8  e_gain_th1;
	UINT8  e_gain_th2;
}
LX_DE_SHP_DERH_CTRL_0B;

/**
 * PE1 FMD Control
 */
typedef struct {
	UINT8 fmd_enable;
}
LX_DE_FMD_CTRL;

/**
 * Mute Control
 */
typedef struct {
	UINT8 mute_enable;
}
LX_DE_MUTE_CTRL;

/**
 * TNR Auto Control
 */
typedef struct {
	UINT8 auto_enable;
}
LX_DE_TNR_CTRL;

/**
 * Scaler Control
 */
typedef struct {
	UINT8 set_cnt;
}
LX_DE_SCL_CTRL;

/**
 * SRC Info
 */
typedef struct {
	UINT8 dtv_play_type;
}
LX_DE_SRC_INFO;

/**
 * PQ Firmware IPC Control
 */
typedef struct {
    LX_DE_PQ_FIRMWARE_CTRL    pq_firmware_ctrl;
    LX_DE_SHP_CORING_CTRL_05  shp_coring_ctrl_05;
	LX_DE_SHP_CORING_CTRL_06  shp_coring_ctrl_06;
    LX_DE_SHP_CORING_CTRL_09  shp_coring_ctrl_09;
    LX_DE_SHP_DP_CTRL_01      shp_dp_ctrl_01;
    LX_DE_SHP_DERH_CTRL_0B    shp_derh_ctrl_0B;
    LX_DE_FMD_CTRL            fmd_ctrl;
    LX_DE_MUTE_CTRL           mute_ctrl;
    LX_DE_TNR_CTRL            TNR_ctrl;
    LX_DE_SCL_CTRL            scl_ctrl;
    LX_DE_SRC_INFO            src_info;
}
LX_DE_PQ_IPC_CTRL;

typedef struct {
	UINT32 start : 12;
	UINT32 count : 12;
	UINT32 winId : 4;
} PQL_TABLE_HEAD_T;

/**
 * de cpu/mvi port.
 */
typedef enum
{
	LX_DE_CPU_MVI_A,               ///< A
	LX_DE_CPU_MVI_B,               ///< B
	LX_DE_CPU_MVI_C,               ///< C
	LX_DE_CPU_MVI_D               ///< D
}
LX_DE_CPU_MVI_PORT_T;


/**
 * de cpu/mvi port for multi window source mapping
 */
typedef struct {
	LX_DE_WIN_ID_T win_id;					///< window index
	LX_DE_CPU_MVI_PORT_T    cpu_mvi_port; 	///< input port for multi window
}
LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T;

/**
 * de set current 3D info through middleware(G-streamer)
 */
typedef struct {
	BOOLEAN                IsOverWriting;
	LX_DE_MVI_3D_INFO_T    mvi_3dfmt_info;
    LX_DE_MVI_3D_LR_ORDER_T mvi_3dlr_order;
}
LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T;


/**
 * de get par(pixel aspect ratio) width, height
 */
typedef struct
{
	UINT16      w;  ///< horizontal Size(Width)  in pixel
	UINT16      h;  ///< vertical   Size(Height) in pixel
}
LX_DE_PAR_RECT_T;

/**
 * de get window par(pixel aspect ratio) width, height
 */
typedef struct {
	LX_DE_WIN_ID_T    win_id;	///< window index
	LX_DE_PAR_RECT_T  rect;     ///< window demension(w,h)
}
LX_DE_PAR_WIN_RECT_T;

/**
 * de parameter as to capture raw image used for debugging
 */
typedef struct {
	UINT32	mode;
	UINT32	*base_addr;
	UINT32	size;
}
LX_DE_PAR_CAPTURE_RAW_IMAGE_T;

/**
 * de get low delay info
 */
typedef struct {
	UINT32	enable : 4;  // 3:0;
	UINT32	lock   : 4;  // 7:4;
	UINT32	time   : 14; // 21:8;
	UINT32	frame  : 10; // 31:22;
}
LX_DE_LOW_DELAY_T;

/**
 *  * 3D formatter running mode parameter.
 *   * select 3D formatter operation mode. it controls 3D mode ON/OFF.
 *    */
typedef enum
{
	LX_DE_3D_RUNMODE_OFF = 0,	///< 2D mode, 3D off(bypass)
	LX_DE_3D_RUNMODE_ON,		///< 3D mode, 3D on
	LX_DE_3D_RUNMODE_3DTO2D,	///< 3D input 2D output
	LX_DE_3D_RUNMODE_2DTO3D,	///< 3D input 2D output
	LX_DE_3D_RUNMODE_MAX		///< max number
}
LX_DE_3D_RUNMODE_T;

/**
 *  * 3D formatter image format parameter.
 *   * used for input image format and output image format.
 *    */
typedef enum {
	LX_DE_3D_IMG_IN_TOPNBOTTOM = 0,		///< top and bottom
	LX_DE_3D_IMG_IN_SIDEBYSIDE,			///< side by side
	LX_DE_3D_IMG_IN_QUINCUNX,				///< quincunx
	LX_DE_3D_IMG_IN_CHECKERBOARD,			///< check board
	LX_DE_3D_IMG_IN_FRAMEPACKING,			///< frame packing
	LX_DE_3D_IMG_IN_FRAMEINTERLACE,		///< frame packing interlace
	LX_DE_3D_IMG_IN_FIELDALTERNATE,		///< field alternate
	LX_DE_3D_IMG_IN_FRAMESEQ,				///< frame sequence
	LX_DE_3D_IMG_IN_LINEALTERNATIVE,		///< line alternative full
	LX_DE_3D_IMG_IN_SIDEBYSIDE_FULL,		///< side by side full
	LX_DE_3D_IMG_IN_DUAL_HD,				///< dual HD e.g.) One is mpeg-2 ts, the other is mpeg-4 ts scenario
	LX_DE_3D_IMG_IN_COLUMNALTERNATIVE,		///< column alternate(interleaving) - mpeg
	LX_DE_3D_IMG_IN_LINEALTERNATIVE_HALF,	///< line alternative half
	LX_DE_3D_IMG_IN_MAX					///< max number
}
LX_DE_3D_IMG_FMT_IN_T;

/**
 *  * 3D formatter image format parameter.
 *   * used for input image format and output image format.
 *    */
typedef enum {
	LX_DE_3D_IMG_OUT_SINGLE_2D    = 0,	///< single nomal
	LX_DE_3D_IMG_OUT_SINGLE_TB,			///< top and bottom
	LX_DE_3D_IMG_OUT_SINGLE_SS,			///< side by side
	LX_DE_3D_IMG_OUT_SINGLE_FS,			///< Frame Sequential(Interleaving)
	LX_DE_3D_IMG_OUT_DUAL_FULL,			///< dual screen
	LX_DE_3D_IMG_OUT_DUAL_TB,			///< dual top and bottom for H13 internal type
	LX_DE_3D_IMG_OUT_DUAL_SS,			///< dual side by side for H13 internal type
	//LX_3D_IMG_OUT_DUAL_FHD,			///< dual FHD for H13 internal type
	LX_DE_3D_IMG_OUT_MAX				///< max number
}
LX_DE_3D_IMG_FMT_OUT_T;

/**
 *  * 3D formatter Left Roght order parameter.
 *   * used for input image and output image.
 *    */
typedef enum
{
	LX_DE_3D_LR_ORDER_R_FIRST = 0,		///< right first
	LX_DE_3D_LR_ORDER_L_FIRST,			///< left first
	LX_DE_3D_LR_ORDER_MAX				///< max number
}
LX_DE_3D_LR_ORDER_T;

/**
 *  * 3D formatter input/output control type.
 *   *  0xFF   : invalid
 *    *  Others :   valid
 *     */
typedef struct {
	LX_DE_3D_RUNMODE_T		run_mode;			///< select formatter operation mode. it controls 3D mode ON/OFF.
	LX_DE_3D_IMG_FMT_IN_T		in_img_fmt;			///< input image format(top/bottom, sidebyside, checkboard, frame, field seq, dual 2d)
	LX_DE_3D_LR_ORDER_T 		in_lr_order;		///< input left/right first order
	LX_DE_3D_IMG_FMT_OUT_T 	out_img_fmt;		///< output image format(top/bottom, sidebyside, checkboard, frame, field seq)
	LX_DE_3D_LR_ORDER_T  	out_lr_order;		///< output left/right first order
}
LX_DE_3D_INOUT_CTRL_T;

/**
 * de Debug argument for evaluation. (시나리오 테스트 )
 */
typedef struct {
	LX_DE_EVAL_CMD_T cmd;
	LX_DE_EVAL_ARG_T arg;
	UINT32 *prm;
	UINT32 size;
}
LX_DE_SET_EVAL_DBG_T;

/////////////////////////H13//////////////////////////////////////////////////
typedef enum {
	LX_DE_HDMI444_NONE,
	LX_DE_HDMI444_OFF,
	LX_DE_HDMI444_ON,
	LX_DE_HDMI444_MAX
}	LX_DE_HDMI444_MODE_T;

typedef enum {
	LX_DE_DIRECT_INPUT,
	LX_DE_DIRECT_OUTPUT,
	LX_DE_DIRECT_MAX
}	LX_DE_DIRECT_T;

typedef enum
{
	LX_DE_RW_SET,
	LX_DE_RW_GET,
	LX_DE_RW_MAX
}	LX_DE_RW_T;

typedef struct {
	LX_DE_WIN_ID_T  		win_id;
	LX_DE_RECT_T 		rect;
	LX_DE_DIRECT_T		direct_type;
	LX_DE_RW_T			rw_type;
} LX_DE_WIN_CONFIG_T;


typedef enum {
	LX_DE_IN_SRC_NONE,
	LX_DE_IN_SRC_VGA,
	LX_DE_IN_SRC_YPBPR,
	LX_DE_IN_SRC_ATV,
	LX_DE_IN_SRC_CVBS,
	LX_DE_IN_SRC_SCART,
	LX_DE_IN_SRC_HDMI,
	LX_DE_IN_SRC_MVI,
	LX_DE_IN_SRC_CPU,
	LX_DE_IN_SRC_MAX
} LX_DE_IN_SRC_T;


typedef struct {
	LX_DE_WIN_ID_T 		win_id;			///< Display window index
	LX_DE_IN_SRC_T 		inputSrc;		///< Input source type
	UINT32				inputSrcPort;	///< Input port info (CVI_A,CVI_B, MVI_0,1,2,3)
	UINT32				inputResv;		///< Reserve parameter
} LX_DE_INPUT_CFG_T;


typedef enum
{
	LX_DE_OPER_ONE_WIN,				///< No Video
	LX_DE_OPER_TWO_WIN,
    	LX_DE_OPER_3D,
	LX_DE_OPER_UD,
	LX_DE_OPER_VENC,
	LX_DE_OPER_MAX
}	LX_DE_OPER_CONFIG_T;

typedef enum
{
	LX_DE_UD_OFF,
	LX_DE_UD_ON,		// 4k x 2k
	LX_DE_UD_HALF,		// 2k x 2k
	LX_DE_UD_MAX,		// 2k x 2k
} LX_DE_UD_CTRL_T;

typedef struct
{
	BOOLEAN bOnOff;
	LX_DE_SCAN_T scan;
	UINT16	hSize;
	UINT16 	vSize;
	UINT16 	frRate;
}	LX_DE_VENC_FMT_T;

/**
 *	DE operation.
 *
 */
typedef struct
{
	LX_DE_WIN_ID_T 		win_id;			///< De window index
	LX_DE_OPER_CONFIG_T	operation;		///< operation flag

	UINT32				multiCtrl;		// use Two window
	LX_DE_UD_CTRL_T	udCtrl;			// UD mode
	LX_DE_3D_INOUT_CTRL_T 	ctrl3D;		// use 3D mode
	LX_DE_VENC_FMT_T	vencCtrl;		// use for venc src format
}	LX_DE_OPERATION_CTRL_T;

typedef enum
{
	LX_DE_SUB_OPER_OFF,			///<
	LX_DE_SUB_OPER_CAPTURE,		///<
	LX_DE_SUB_OPER_VENC,			///<	
	LX_DE_SUB_OPER_MAX
}	LX_DE_SUB_OPER_CONFIG_T;

/**
 *	DE sub operation.
 *
 */
typedef struct
{
	LX_DE_WIN_ID_T 				win_id;			///< De window index
	LX_DE_SUB_OPER_CONFIG_T	operation;		///< De window index

	UINT32						capture_enable;	// for capture
	LX_DE_VENC_FMT_T			vencCtrl;		// use for venc src format	
}	LX_DE_SUB_OPERATION_CTRL_T;

/*
 * de location for capture.
 */
typedef enum
{
	LX_DE_LOCATION_SOURCE,		///< DE Input Source
	LX_DE_LOCATION_DISPLAY,		///< Display Source
	LX_DE_LOCATION_MAX			///< MAX
}	LX_DE_LOCATION_T;

/*
 * de pixel format parameter.
 */
typedef enum
{
	LX_DE_PIXEL_FORMAT_RGB_10,
	LX_DE_PIXEL_FORMAT_RGB_8,
	LX_DE_PIXEL_FORMAT_YCBCR444_10,
	LX_DE_PIXEL_FORMAT_YCBCR444_8,
	LX_DE_PIXEL_FORMAT_YCBCR422_10,
	LX_DE_PIXEL_FORMAT_YCBCR422_8,
	LX_DE_PIXEL_FORMAT_YCBCR420_10,
	LX_DE_PIXEL_FORMAT_YCBCR420_8,
	LX_DE_PIXEL_FORMAT_MAX
}	LX_DE_PIXEL_FORMAT_T;

/*
 * de capture type.
 */
typedef struct
{
	LX_DE_WIN_ID_T 			win_id;			///< De window index
	LX_DE_LOCATION_T		location;		///< direction info of source for capture
	LX_DE_RECT_T 			inWin;			///< input window for capture
	UINT16					wOutSize;		///< output width size for capture
	UINT16		 			hOutSize;		///< output height size for capture
	LX_DE_PIXEL_FORMAT_T	pixelFormat;	///< pixel data format
	UINT8 					*p_y_frame;		///< y frame data start address
	UINT8 					*p_cbcr_frame;	///< cbcr frame data start address

}	LX_DE_CAPTURE_CTRL_T;

typedef enum
{
	LX_DE_CONFIG_TYPE_ALL,			///<for setting all config
	LX_DE_CONFIG_TYPE_DISPLAY_DEVICE,
	LX_DE_CONFIG_TYPE_DISPLAY_MIRROR,
	LX_DE_CONFIG_TYPE_FRC,
	LX_DE_CONFIG_TYPE_3D,
	LX_DE_CONFIG_TYPE_MAX,
}	LX_DE_CONFIG_T;

typedef enum {
	LX_DE_DIS_DEV_LCD, 	///< LCD/LED device
	LX_DE_DIS_DEV_PDP,	///< PDP device
	LX_DE_DIS_DEV_OLED,	///< OLED device
	LX_DE_DIS_DEV_CP,		///< CP box device
	LX_DE_DIS_DEV_STB,	///< Set-top box device
	LX_DE_DIS_DEV_MAX		///< max number
}	LX_DE_DISPLAY_DEVICE_T;

typedef enum {
	LX_DE_DIS_MIRROR_OFF, 	///< diaplay mirror off
	LX_DE_DIS_MIRROR_X, 		///< diaplay mirror x position 
	LX_DE_DIS_MIRROR_Y, 		///< diaplay mirror y position 
	LX_DE_DIS_MIRROR_X_Y, 	///< diaplay mirror x, y position 
	LX_DE_DIS_MIRROR_MAX		///< max number
}	LX_DE_DISPLAY_MIRROR_T;

typedef enum
{
	LX_DE_FRC_PATH_INTERNAL,
	LX_DE_FRC_PATH_EXTERNAL,
	LX_DE_FRC_PATH_MAX,
} LX_DE_FRC_PATH_T;


typedef enum
{
	LX_DE_3D_CTRL_OFF,
	LX_DE_3D_CTRL_ON,
	LX_DE_3D_CTRL_MAX,
} LX_DE_3D_CTRL_T;

/*
 * default : DIS_DEV - LCD,  FRC Path - Internal, 3D ctrl -ON
 */
typedef	struct
{
	LX_DE_CONFIG_T	config_type;

	LX_DE_DISPLAY_DEVICE_T	display_type;
	LX_DE_DISPLAY_MIRROR_T display_mirror;
	LX_DE_FRC_PATH_T		frc_type;
	LX_DE_3D_CTRL_T			trid_type;
	
}	LX_DE_IF_CONFIG_T;


typedef enum
{
	LX_DE_SYS_STATUS_ALL,
	LX_DE_SYS_STATUS_DISPALY_DEVICE,
	LX_DE_SYS_STATUS_DISPALY_MIRROR,
	LX_DE_SYS_STATUS_FRC,
	LX_DE_SYS_STATUS_3D,
	LX_DE_SYS_STATUS_FC_MEM,
	LX_DE_SYS_STATUS_DISPALY_SIZE,
	LX_DE_SYS_STATUS_MAX
}	LX_DE_SYS_STATUS_CONFIG_T;


/*
 * default : DIS_DEV - LCD,  FRC Path - Internal, 3D ctrl -ON
 */
typedef	struct
{
	LX_DE_SYS_STATUS_CONFIG_T	status_type; //type

	LX_DE_DISPLAY_DEVICE_T	display_type;		///< display type
	LX_DE_DISPLAY_MIRROR_T 	display_mirror;		///< display mirror type
	LX_DE_FRC_PATH_T		frc_type;
	LX_DE_3D_CTRL_T			trid_type;
	UINT32 				 	fc_mem;		// DDR address for capture
	LX_DE_PANEL_TYPE_T 		display_size;		///< display size
}	LX_DE_SYS_STATUS_T;



typedef enum
{
	LX_DE_SRC_STATUS_ALL,
	LX_DE_SRC_STATUS_INPUT_SRC,
	LX_DE_SRC_STATUS_OPER,
	LX_DE_SRC_STATUS_SUB_OPER,
	LX_DE_SRC_STATUS_MAX
}	LX_DE_SRC_STATUS_CONFIG_T;


/*
 * default : DIS_DEV - LCD,  FRC Path - Internal, 3D ctrl -ON
 */
typedef	struct
{
	LX_DE_SRC_STATUS_CONFIG_T	status_type;

	LX_DE_IN_SRC_T 				inSrc[2];		///< Input source type
	UINT32						inSrcPort[2];	///< Input port info (CVI_A,CVI_B, MVI_0,1,2,3)

	LX_DE_OPER_CONFIG_T		operType;
	LX_DE_SUB_OPER_CONFIG_T	subOperType;
}	LX_DE_SRC_STATUS_T;


/*
 * de OSD Frame type.
 */
typedef struct
{
	LX_DE_WIN_ID_T 				win_id;			///< De window index
	UINT32						address;		///< physical header address
	UINT8						enable;			///< enable control
	UINT16						stride;			///< stride size
	LX_DE_SCALER_CSAMPLE_T		sampling;		///< data format
	UINT8 						*p_y_frame;		///< y frame data start address
	UINT8 						*p_cbcr_frame;	///< cbcr frame data start address
}	LX_DE_OSD_FRAME_CTRL_T;


/*
 * de Scaler Info type.
 */
typedef struct
{
	LX_DE_WIN_ID_T 				win_id;			///< De window index
	UINT16						width;			///< stride size
	UINT16						height;			///< stride size
	UINT32						stride;			///< stride size
	LX_DE_SCALER_CSAMPLE_T		sampling;		///< data format
	UINT8 						*p_y_frame;		///< y frame data start address
	UINT8 						*p_cbcr_frame;	///< cbcr frame data start address
}	LX_DE_SCALER_INFO_T;

#if 0	//CVI src type

/*
typedef enum
{
	LX_DE_CVI_NORMAL_SYNC_MODE,		///< sync mode for CVD, ADC,Internal Hactive is made by hsync and de
	LX_DE_CVI_DE_SYNC_MODE		///< sync mode for HDMI Internal Hactive is made by de (Hoffset & Voffset should be 0x0000)"
}
LX_DE_CVI_SYNC_MODE_T;

*/

typedef enum
{
	LX_DE_CVI_FIELD_AUTO,
	LX_DE_CVI_FIELD_AUTO_INVERSE,
	LX_DE_CVI_FIELD_INPUT,
	LX_DE_CVI_FIELD_INPUT_INVERSE,
	LX_DE_CVI_FIELD_MAX
} LX_DE_CVI_FIELD_MODE_T;


typedef struct {
	LX_DE_CVI_CHANNEL_T    cvi_channel; ///< CVI channel A or B

	BOOLEAN isYEnable;					///< fir enable
	UINT16 fir_y_coef[6];					///< fir coefficient

	BOOLEAN isCEnable;					///< fir enable
	UINT16 fir_c_coef[6];			///< CbCr fir coefficient, add from L9 B0, by sh.myoung 201108
}
LX_DE_CVI_FIR_H13_T;




typedef struct {
	LX_DE_CVI_CHANNEL_T		cvi_channel;			///< CVI channel A or B
	LX_DE_CVI_INPUT_SRC_T	  	cvi_inputSrc;		///< CVI source type Information.
	LX_DE_CVI_FORMAT_T			cvi_format;			///< CVI format infomation
	LX_DE_CVI_SYNC_MODE_T	   	cvi_de_mode;		///< internal data enable mode generated from sync(0) or de(1)
	LX_DE_COLOR_STD_T		   	cvi_color;			///< color space 601,709,PC
	LX_DE_CVI_SAMPLING_MODE_T	cvi_sampling;		///< data sampling: noraml(0), double(1), quadrature(2)
	LX_DE_SCALER_CSAMPLE_T	   	sc_cs_type;		 	///< scaler - chroma sampling mode YUV420(0) YUV422(1) YUV444(2)
	LX_DE_CVD_COLOR_STD_T	   	cvi_cvd_colorStd;	///< CVD color mode
//same parameter for debug???
	LX_DE_CVI_YC_DELAY_T	   	cvi_ycDelay;		///< ATV/CVBS
	LX_DE_CVI_FIELD_MODE_T		cvi_field;			///< input source field control
	LX_DE_CVI_BITRES_T		   	cvi_bitRes;			///< bit resolution 10bit(0) or 8bit(1)
	LX_DE_CVI_CSAMPLE_T		cvi_input_csample;	///< chroma sampling mode 422(0) or 444(1)
}
KADP_VP_CVI_SRC_CFG_T;
#endif

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_DRV_H_ */

/** @} */
