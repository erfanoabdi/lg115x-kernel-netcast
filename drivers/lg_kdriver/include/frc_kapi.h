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



/** @file frc_kapi.h
 *
 *  application interface header for frc device
 *
 *  @author	sh.myoung (sh.myoung@lge.com)
 *  @version	0.8
 *  @date		2010.01.27
 *
 *  @addtogroup lg1150_frc
 *	@{
 */

#ifndef	_FRC_KAPI_H_
#define	_FRC_KAPI_H_

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
#define	FRC_IOC_MAGIC		'a'
/**
@name FRC IOCTL List
ioctl list for frc device.

@{
@def FRC_IOW_INIT
Initialize OIF module.

@def FRC_IOR_IS_STABLE
FRC Stable check.

@def FRC_IOW_SET_MEMC
Set Enable Moion compensation.

@def FRC_IOW_SET_MEMC_TYPE
Set Motion Compensation Type of FRC.
Set MC, Blur and Judder level.

@def FRC_IOW_SET_TRUEMOTION_DEMO
Enable FRC True Motion Demo.

@def FRC_IOW_SET_TRUEMOTION_DEMO_BAR
Control FRC True Motion Demo bar and color.
FRC Demo bar on/off and color change.

@def FRC_IOW_SET_SCAN_DIRECTION
Set Display Scan Direction.
0 : normal, 1 : reserve.

@def FRC_IOW_SET_FREEZE
Set FRC Display Freeze for debug

@def FRC_IOW_SET_OSD_CONTROL
FRC OSD control.
And Set OSD enable, region and Rectangle

@def FRC_IOW_SET_SPREAD_SPECTRUM
Set FRC Spread Spectrum for LVDS When using FRC.

@def FRC_IOW_SET_PWM_DUTY_CYCLE
Set PWM(Scanning Backlight) Duty Cycle of FRC.

@def FRC_IOW_SET_PWM_CONTROL
Set FRC PWM ouput Control.
OIF selects DE PWM(60Hz) or FRC PWM(120Hz).

@def FRC_IOW_SET_LOW_DELAY_MODE
FRC Set low delay mode.

@def FRC_IOW_SET_DISPLAY_OUTPUT
Set FRC Data(LVDS) Output On/OFF.

@def FRC_IOW_SET_FHD_MODE
Set FRC FHD/HD Mode.

@def FRC_IOW_SET_OUTPUT_FRAME_RATE
Set FRC Output Frame Rate.

@def FRC_IOW_SET_DISPLAY_MUTE
Set Display Mute(Rx, Tx, LVDS) of FRC.

@def FRC_IOR_GET_FIRMWARE_VERSION
Read FRC firmware version.

@def FRC_IOW_SET_JUDDER_LEVEL
Set Judder Level for debug.

@def FRC_IOW_SET_BLUR_LEVEL
Set Blur Level for debug.

@def FRC_IOW_SET_SLOW_FRAME_LOCK
Set FRC Slow frame lock.
Control a FrameLock speed when channel changes or FRC framerate changes.
Not supported at MW THEN RETURN NOT_OK.

@def FRC_IOW_UPDATE_FIREWARE
update FRC fireware.


*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define	FRC_IOW_INIT						_IOW(FRC_IOC_MAGIC,  0, LX_FRC_INIT_T )
#define	FRC_IO_RESET_SW						_IO(FRC_IOC_MAGIC,  1 )
#define FRC_IOR_IS_STABLE					_IOR(FRC_IOC_MAGIC,  2, LX_FRC_STABLE_T )
#define	FRC_IOW_SET_MEMC					_IOW(FRC_IOC_MAGIC,  3, BOOLEAN )
#define FRC_IOW_SET_MEMC_TYPE				_IOW(FRC_IOC_MAGIC,  4, LX_FRC_MC_TYPE_T )
#define FRC_IOW_SET_TRUEMOTION_DEMO			_IOW(FRC_IOC_MAGIC,  5, BOOLEAN )
#define FRC_IOW_SET_TRUEMOTION_DEMO_BAR		_IOW(FRC_IOC_MAGIC,  6, LX_FRC_DEMO_BAR_CTRL_T )
#define FRC_IOW_SET_SCAN_DIRECTION			_IOW(FRC_IOC_MAGIC,  7, BOOLEAN )
#define FRC_IOW_SET_FREEZE					_IOW(FRC_IOC_MAGIC,  8, BOOLEAN )
#define FRC_IOW_SET_OSD_CONTROL				_IOW(FRC_IOC_MAGIC,  9, LX_FRC_OSD_CTRL_T )
#define	FRC_IOW_SET_SPREAD_SPECTRUM			_IOW(FRC_IOC_MAGIC,  10, LX_FRC_SPREAD_SPECTRUM_T )
#define FRC_IOW_SET_PWM_DUTY_CYCLE			_IOW(FRC_IOC_MAGIC,  11, LX_FRC_PWM_PARAM_T )
#define FRC_IOW_SET_PWM_CONTROL				_IOW(FRC_IOC_MAGIC,  12, LX_FRC_PWM_CTRL_T )
#define FRC_IOW_SET_LOW_DELAY_MODE			_IOW(FRC_IOC_MAGIC,  13, LX_FRC_LOW_DELAY_T )
#define FRC_IOW_SET_DISPLAY_OUTPUT			_IOW(FRC_IOC_MAGIC,  14, BOOLEAN )
#define FRC_IOW_SET_FHD_MODE				_IOW(FRC_IOC_MAGIC,  15, LX_FRC_FHD_MODE_T )
#define FRC_IOW_SET_OUTPUT_FRAME_RATE		_IOW(FRC_IOC_MAGIC,  16, LX_FRC_FRAME_RATE_T )
#define FRC_IOW_SET_RGBYUV_MODE				_IOW(FRC_IOC_MAGIC,  17, LX_FRC_RGBYUV_MODE_T )
#define FRC_IOW_SET_DISPLAY_MUTE			_IOW(FRC_IOC_MAGIC,  18, LX_FRC_MUTE_CTRL_T )
#define FRC_IOR_GET_FIRMWARE_VERSION		_IOR(FRC_IOC_MAGIC,  19, LX_FRC_FIRMWARE_INFO_T )

//For debug
#define FRC_IOW_SET_JUDDER_LEVEL			_IOW(FRC_IOC_MAGIC,  21, UINT8 )
#define FRC_IOW_SET_BLUR_LEVEL				_IOW(FRC_IOC_MAGIC,  22, UINT8 )
#define FRC_IOR_REG_RD						_IOR(FRC_IOC_MAGIC,  23, UINT32)
#define FRC_IOW_REG_WR						_IOW(FRC_IOC_MAGIC,  24, LX_FRC_REG_WRITE_T)

#define FRC_IOC_MAXNR				25
/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * FRC MOTION COMPENSATION LEVEL.
 * FRC MOTION COMPENSATION LEVEL is defined.
 * @see LX_FRC_MC_TYPE_T
 *
 */
typedef enum {
	LX_FRC_MC_OFF = 0,			///< MEMC Off
	LX_FRC_MC_LOW,				///< MEMC Low
	LX_FRC_MC_HIGH,				///< MEMC High
	LX_FRC_MC_USER,				///< MEMC user
	LX_FRC_MC_55_PULLDOWN		///< MEMC 5:5 Pulldown -> 24Hz FILM Mode Register change: Auto to 5:5
} LX_FRC_MC_LEVEL_T;

/**
 * FRC OSD Region.
 * FRC OSD Region is defined.
 */
typedef enum {
	LX_FRC_OSD_REGION_0	= 0,		///< Resion 0
	LX_FRC_OSD_REGION_1,			///< Resion 1
	LX_FRC_OSD_REGION_2,			///< Resion 2
	LX_FRC_OSD_REGION_3,			///< Resion 3
	LX_FRC_OSD_REGION_4,			///< Resion 4 : not support L8
	LX_FRC_OSD_REGION_MAX			///< Resion all : All Clear
} LX_FRC_OSD_REGION_T;

/**
 * FRC PWM PIN.
 * FRC PWM PIN Info is defined.
 * @see LX_FRC_PWM_PARAM_T
 */
typedef enum {
	LX_FRC_PWM_PIN0	= 0,	///< PWM# 0
	LX_FRC_PWM_PIN1,		///< PWM# 1
	LX_FRC_PWM_PIN2,		///< PWM# 2
	LX_FRC_PWM_PIN3,		///< PWM# 3
	LX_FRC_PWM_PIN4,		///< PWM# 4
	LX_FRC_PWM_MAX,			///< PWM# MAX
} LX_FRC_PWM_NUM_T;

/**
 * FRC PWM PIN.
 * FRC PWM PIN Info is defined.
 * @see LX_FRC_PWM_CTRL_T
 */
typedef enum {
	LX_FRC_PWM_LOW 	= 0,		///< PWM Output Signal Cotrol - Low
	LX_FRC_PWM_NORMAL,			///< PWM Output Signal Cotrol - Normal
	LX_FRC_PWM_HIGH,			///< PWM Output Signal Cotrol - High
	LX_FRC_PWM_INVERSION,		///< PWM Output Signal Cotrol - Inversion
} LX_FRC_PWM_OUT_CTRL_T;

/**
 * FRC video mute.
 * FRC video mute type is defined.
 */
typedef enum {
	LX_FRC_MUTE_TYPE_INPUT	= 0,	///< FRC Rx (receiver signal off)
	LX_FRC_MUTE_TYPE_OUTPUT,		///< FRC Tx (output black mute)
	LX_FRC_MUTE_TYPE_LVDS,			///< FRC LVDS (LVDS signal off)
	LX_FRC_MUTE_TYPE_MAX
} LX_FRC_MUTE_TYPE_T;

/**
 * FRC LOW DELAY MODE.
 * FRC LOW DELAY MODE is defined.
 * @see FRC_IOW_SET_LOW_DELAY_MODE
 */
typedef enum {
	LX_FRC_LOW_DELAY_OFF = 0,			///< Low delay off
	LX_FRC_LOW_DELAY_NORMAL,			///< Low delay Normal
	LX_FRC_LOW_DELAY_EXCEPT_24HZ,		///< Low delay except 24Hz
	LX_FRC_LOW_DELAY_RGB_MODE_ON,		///< Low delay RGB mode ON
	LX_FRC_LOW_DELAY_RGB_MODE_OFF		///< Low delay RGB mode Off
} LX_FRC_LOW_DELAY_T;

/**
 * FRC FHD Mode.
 * FRC FHD Mode type is defined.
 * TBD.
 * @see FRC_IOW_SET_FHD_MODE
 */
typedef enum {
	LX_FRC_FHD_MODE	= 0,	///< FHD mode (1920x1080)
	LX_FRC_HD_MODE		    ///< HD mode (1366x768)
} LX_FRC_FHD_MODE_T;

/**
 * FRC Output Frame Rate.
 * FRC Output Frame Rate is defined.
 * @see FRC_IOW_SET_OUTPUT_FRAME_RATE
 *
 */
typedef enum {
	LX_FRC_FR_50_60_HZ = 0, 	///< bypass
	LX_FRC_FR_100_120_HZ,		///< 120 Hz
	//LX_FRC_FR_200_240_HZ		///< TBD 240 Hz
} LX_FRC_FRAME_RATE_T;

/**
 * FRC STATBLE.
 * FRC STATBLE is defined.
 *
 */
typedef enum {
	LX_FRC_UNSTABLE = 0,		///< FRC Un stable
	LX_FRC_STABLE,				///< FRC stable
	LX_FRC_NOT_START,			///< FRC not start
	LX_LVDS_UNLOCK				///< LVDS unlock
} LX_FRC_STABLE_T;

/**
 * FRC RGB YUV MODE.
 * FRC RGB-YUV mode is defined.
 *
 */
typedef enum {
	LX_FRC_RGB = 0,			///< FRC RGB mode - PC input
	LX_FRC_YUV,				///< FRC YUV mode - MPEG      :: none compress
	LX_FRC_YUV_COMPRESS		///< FRC YUV compress mode :: L8 A0 memory issue - To do not use
} LX_FRC_RGBYUV_MODE_T;

/**
 * frc ioctl parameter.
 * MOTION COMPENSATION Parameter.
 * @see FRC_IOW_INIT
 */
typedef struct
{
	BOOLEAN		bMemc;						///< MEMC control 0 : Off, 1 : On.
	BOOLEAN		bReverse;					///< Reserse control 0 : normal, 1 : reverse.
	LX_FRC_FHD_MODE_T eResolution;			///< FHD / HD Mode
	LX_FRC_LOW_DELAY_T	eLowDelay;			///< Low Delay set
	//LX_FRC_MC_TYPE_T eMCType;				///< MEMC Type set
} LX_FRC_INIT_T;

/**
 * frc ioctl parameter.
 * MOTION COMPENSATION Parameter.
 * Set MC Type , Blur and Judder level.
 * @see FRC_IOW_SET_MEMC_TYPE
 */
typedef struct
{
	UINT8 blurLevel;						///< Blur level
	UINT8 judderLevel;						///< Judder level
	LX_FRC_MC_LEVEL_T eFrcMCLevel;			///< MC Level
} LX_FRC_MC_TYPE_T;

/**
 * frc ioctl parameter.
 * FRC DEMO BAR CONTROL Parameter.
 * Demo onoff bar info.
 * @see FRC_IOW_SET_TRUEMOTION_DEMO_BAR
 */
typedef struct
{
	BOOLEAN bEnable;		///< 0 : Demo off, 1 : Demo On
	UINT8 rBar;				///< Red Bar[3bit]
	UINT8 gBar;				///< Green Bar[3bit]
	UINT8 bBar;				///< Blue Bar[2bit]
	UINT8 thick;			///< Wire Farme Thickness,  default : 8
} LX_FRC_DEMO_BAR_CTRL_T;

/**
 * frc ioctl parameter.
 * FRC MUTE CONTROL Parameter.
 * Set Mute Info.
 * @see FRC_IOW_SET_DISPLAY_MUTE
 */
typedef struct
{
	BOOLEAN bEnable;					///< 1 : Mute Enanble
	LX_FRC_MUTE_TYPE_T	eFrcMute;		///< FRC MUTE Type
} LX_FRC_MUTE_CTRL_T;

/**
 * frc ioctl parameter.
 * FRC OSD Position Parameter.
 * Set FRC OSD Position.
 * @see LX_FRC_OSD_CTRL_T
 */

typedef struct {
	UINT16  u16Hsize;  			///< OSD RECT Hsize(w) position
	UINT16  u16Vsize;  			///< OSD RECT Vsize(h) position
	UINT16  u16Hstart;  		///< OSD RECT Hstart(x) position
	UINT16  u16Vstart;  		///< OSD RECT Vstart(y) position
} LX_FRC_OSD_RECT_T;

/**
 * frc ioctl parameter.
 * FRC OSD Control Parameter.
 * Set FRC OSD Enable, Region and RECT.
 * @see FRC_IOW_OSD_CONTORL
 */
typedef struct {
	BOOLEAN bOnOff;						///< 1:Region on, 0: Region off
	LX_FRC_OSD_REGION_T eOSDRegion;		///< Region (0~3: region, 4:all Region)
	LX_FRC_OSD_RECT_T	tOSDRect;		///< Rectangle (x,y,w,h 1920*1080 resolution)
} LX_FRC_OSD_CTRL_T;

/**
 * frc ioctl parameter.
 * FRC SPREAD SPECTRUM Parameter.
 * Set FRC SPREAD SPECTRUM Info.
 * @see FRC_IOW_SET_SPREAD_SPECTRUM
 */
typedef struct
{
	UINT16 u16Period; 		///< spread period (The unit is 100Hz)
	UINT16 u16Percent; 		///< spread ratio (0 ~ 100)
	BOOLEAN bEnable; 		///< spread spectrum enable
	BOOLEAN bMiuLVDS;		///< Miu LVDS( 1: MIU(DDR Spread Spectrum control), 0 : LVDS)
} LX_FRC_SPREAD_SPECTRUM_T;

/**
 * frc ioctl parameter.
 * Parameter for setting PWM duty cycle of FRC(120Hz).
 * @see FRC_IOW_SET_PWM_DUTY_CYCLE
 */
typedef struct
{
    LX_FRC_PWM_NUM_T	ePWMIndex;			///< PWM number: PWM0~4.
    UINT16				u16Duty;			///< Set duty of PWM (0 ~ 100%).
    UINT16				u16StartPosition;	///< PWM Start Position of FRC(1~1125).
} LX_FRC_PWM_PARAM_T;

/**
 * frc ioctl parameter.
 * Parameter for PWM Control.
 * @see FRC_IOW_SET_PWM_CONTROL
 */
typedef struct
{
    LX_FRC_PWM_NUM_T		ePWMIndex;			///< PWM number: PWM0~4.
    LX_FRC_PWM_OUT_CTRL_T	ePWMOutput;			///< PWM Output signal control
} LX_FRC_PWM_CTRL_T;

/**
 * frc ioctl parameter.
 * Date Parameter for Firmware Version.
 * @see LX_FRC_FIRMWARE_INFO_T
 */
typedef struct {
    UINT16 year;			///< year
    UINT16 month;			///< month
    UINT16 day;				///< day
} LX_FRC_DATE_T;

/**
 * frc ioctl parameter.
 * Parameter for Firmware Version.
 * @see FRC_IOR_GET_FIRMWARE_VERSION
 */
typedef struct
{
    UINT32  version;		///< firmware version
    LX_FRC_DATE_T date;		///< updated date
} LX_FRC_FIRMWARE_INFO_T;

/**
 * FRC register value write type.
 * @see FRC_IOW_REG_WR
 */
typedef struct {
	UINT32 wr_addr;			///< register address
	UINT32 wr_data;			///< write data
} LX_FRC_REG_WRITE_T;
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _FRC_DRV_H_ */

/** @} */
