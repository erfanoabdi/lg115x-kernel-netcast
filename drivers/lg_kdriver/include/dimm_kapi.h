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



/** @file dimm_kapi.h
 *
 *  application interface header for dimm device
 *
 *  @author	sh.myoung (sh.myoung@lge.com)
 *  @version	0.8
 *  @date		2010.01.27
 *
 *  @addtogroup lg1150_dimm
 *	@{
 */

#ifndef	_DIMM_KAPI_H_
#define	_DIMM_KAPI_H_

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
#define	DIMM_IOC_MAGIC		'a'
/**
@name DIMM IOCTL List
ioctl list for dimm device.

@{
@def DIMM_IOW_INIT
Initialize Local Dimming module.

@def DIMM_IOW_LOCALDIMMING_CONTROL
Control local-dimming-on.
SPI_CMD registor : 1 : Dimming On

@def DIMM_IOW_STORE_DEMO
Control Dimming Store Demo Mode.

@def DIMM_IOW_LINE_DEMO
Control Dimming Line Demo Mode.

@def DIMM_IOW_CONTROL_PIXEL_COMPENSATION
Control Pixel Compensation.

@def DIMM_IOW_LUT_CONTROL
Set Pixel Compensation LUT A~D according to mode.
OFF/LOW/HIGH mode.

@def DIMM_IOW_STORE_CONTROL
Local Dimming Control for Store Mode.

@def DIMM_IOW_WBCOLOR_CONTROL
White Balance Color Control in the Local Dimming.

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define	DIMM_IOW_INIT							_IOW(DIMM_IOC_MAGIC, 0, LX_DIMM_INFO_T )
#define DIMM_IOW_LOCALDIMMING_CONTROL			_IOW(DIMM_IOC_MAGIC, 1, BOOLEAN )
#define DIMM_IOW_STORE_DEMO						_IOW(DIMM_IOC_MAGIC, 2, BOOLEAN )
#define DIMM_IOW_LINE_DEMO						_IOW(DIMM_IOC_MAGIC, 3, LX_DIMM_LINE_CTRL_T )
#define DIMM_IOW_PIXELCOMPENSATION_CONTROL		_IOW(DIMM_IOC_MAGIC, 4, BOOLEAN )
#define DIMM_IOW_LUT_CONTROL					_IOW(DIMM_IOC_MAGIC, 5, LX_DIMM_LUT_CTRL_T )
#define DIMM_IOW_STORE_CONTROL					_IOW(DIMM_IOC_MAGIC, 6, BOOLEAN )
#define DIMM_IOW_WBCOLOR_CONTROL				_IOW(DIMM_IOC_MAGIC, 7, LX_DIMM_WBCOLOR_CTRL_T )

// for DIMM debug
#define DIMM_IOR_REG_RD							_IOR(DIMM_IOC_MAGIC, 10, UINT32)
#define DIMM_IOW_REG_WR							_IOW(DIMM_IOC_MAGIC, 11, LX_DIMM_REG_WRITE_T)

#define DIMM_IOC_MAXNR				12
/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * dimm ioctl parameter.
 * DIMM Panel Backlight type
 */
typedef enum
{
	LX_BL_CCFL = 0,
	LX_BL_NOR_LED,		///< Back_Light_Uint : Direct-lit
	LX_BL_EDGE_LED,		///< Back_Light_Uint : Edge-lit(Top/Bottom)
	LX_BL_IOP_LED,		///< Back_Light_Uint : Direct-lit
	LX_BL_ALEF_LED,		///< Back_Light_Uint : Direct-lit
	LX_BL_IOL_LED		///< Back_Light_Uint : Direct-lit
} LX_DIMM_BACKLIGHT_TYPE_T;

/**
 * dimm ioctl parameter.
 * DIMM Demo Pattern Mode Info.
 */
typedef enum
{
	LX_DIMM_DEMO_PATTERN_NORMAL = 0,
	LX_DIMM_DEMO_PATTERN_SQUARE = 1,
	LX_DIMM_DEMO_PATTERN_GRID	= 2,
	LX_DIMM_DEMO_PATTERN_GRADATION_R = 4,
	LX_DIMM_DEMO_PATTERN_GRADATION_G = 8,
	LX_DIMM_DEMO_PATTERN_GRADATION_B = 16,
	LX_DIMM_DEMO_PATTERN_COLOR_BAR = 32,
	LX_DIMM_DEMO_PATTERN_RESERVED
} LX_DIMM_PATTERN_MODE_T;
/**
 * dimm ioctl parameter.
 * DIMM INIT INFO.
 * @see DIMM_IOW_INIT
 */
typedef struct
{
	LX_DIMM_BACKLIGHT_TYPE_T 	blType;			///< Panel Back Light Info.
	const UINT32 *InitData;						///< Local Dimming Coefficient data
	UINT32 						u32length;		///< Init data length
} LX_DIMM_INFO_T;

/**
 * dimm ioctl parameter.
 * DIMM Line Demo CTRL param.
 * @see DIMM_IOW_LINE_DEMO
 */
typedef struct
{
	BOOLEAN 				bEnable;	///< Dimming Line Demo Control enable : 1
	LX_DIMM_PATTERN_MODE_T	ePatEn;		///< Dimming Demo Pattern mode
	UINT8					u8Vppf;		///< Vertical speed of the pattern in square and gradaion mode
	UINT8					u8Hppf;  	///< Horizontal speed of the pattern in square mode
} LX_DIMM_LINE_CTRL_T;

/**
 * dimm ioctl parameter.
 * DIMM White Balance Color CTRL param.
 * @see DIMM_IOW_WBCOLOR_CONTROL
 */
typedef struct
{
	UINT32		rOffsetGain;	///< Red OffsetGain.
	UINT32		gOffsetGain;	///< Green OffsetGain.
	UINT32		bOffsetGain;	///< Blue OffsetGain.
} LX_DIMM_WBCOLOR_CTRL_T;

/**
 * DIMM Pixel Compensation LUT according to Mode.
 * Set DIMM PC LUT according to Mode.
 * @see DIMM_IOW_LUT_CONTROL
 */
typedef struct
{
	const UINT32 *pLut;
	UINT32 u32Num;
} LX_DIMM_LUT_CTRL_T;

/**
 * DIMM register value write type.
 * @see DIMM_IOW_REG_WR
 */
typedef struct {
	UINT32 wr_addr;			///< register address
	UINT32 wr_data;			///< write data
} LX_DIMM_REG_WRITE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DIMM_DRV_H_ */

/** @} */
