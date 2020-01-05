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


/** @file ovi_kapi.h
 *
 *  	application interface header for ovi device
 *
 *	@author	    	dj911.kim	
 *	@version		1.0
 *	@note		
 *	@date		2012.09.09
 *	@see		
 */

#ifndef	_OVI_KAPI_H_
#define	_OVI_KAPI_H_

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
#define	LX_OVI_IOC_MAGIC		'o'

/**
@name OVI IOCTL List
ioctl list for ovi device.

@{

@def LX_OVI_IOW_SET_LVDS
Set LVDS parameter

*/

#define LX_OVI_MAX_NUM_OF_MODE_INDEX_CHAR	50

/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define LX_OVI_IOW_SET_LVDS			_IOW(LX_OVI_IOC_MAGIC, 0, LX_OVI_LVDS_T)
#define LX_OVI_IOW_SET_VX1				_IOW(LX_OVI_IOC_MAGIC, 1, LX_OVI_VX1_T)
#define LX_OVI_IOW_SET_EPI				_IOW(LX_OVI_IOC_MAGIC, 2, LX_OVI_EPI_T)
#define LX_OVI_IOW_SET_DARK_SCREEN	_IOW(LX_OVI_IOC_MAGIC, 3, BOOLEAN)
#define LX_OVI_IOW_SET_REVERSE		_IOW(LX_OVI_IOC_MAGIC, 4, BOOLEAN)
#define LX_OVI_IOW_GET_TCON_BASEADDR	_IOR(LX_OVI_IOC_MAGIC, 5, UINT32)

#define LX_OVI_IOW_GET_INFO			_IOR(LX_OVI_IOC_MAGIC, 6, LX_OVI_INFO_T)

#define LX_OVI_IOR_GET_CONFIG_VER	_IOR(LX_OVI_IOC_MAGIC, 7, LX_OVI_CONFIG_VER_T) 
#define LX_OVI_IOW_SET_COMBINATION	_IOW(LX_OVI_IOC_MAGIC, 8, UINT32)
#define LX_OVI_IOW_SET_SPREAD_SPECTRUM	_IOW(LX_OVI_IOC_MAGIC, 9, LX_OVI_SPREAD_SPECTRUM_T)

#define LX_OVI_IOC_MAXNR				(_IOC_NR(LX_OVI_IOW_SET_SPREAD_SPECTRUM) +1 )

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions (Common)
----------------------------------------------------------------------------------------*/
	
typedef enum
{
	LX_OVI_8BIT,					///< 8bit depth
	LX_OVI_10BIT					///< 10bit depth
}
LX_OVI_BIT_DEPTH_T;

typedef enum {
	LX_OVI_BANDWIDTH_0CH = 0,		///< NONE
	LX_OVI_BANDWIDTH_1CH = 1,		///< DPPB IF CLK 74.25MHz
	LX_OVI_BANDWIDTH_2CH = 2,		///< DPPB IF CLK 148.5MHz
	LX_OVI_BANDWIDTH_4CH = 4		///< DPPB IF CLK 297MHz
}
LX_OVI_BANDWIDTH_T;

typedef enum {
	LX_OVI_H_720 = 720,
	LX_OVI_H_1920 = 1920,
	LX_OVI_H_3840 = 3840
}
LX_OVI_H_WIDTH_T;

typedef enum {
	LX_OVI_DISP_VID_D0,
	LX_OVI_DISP_VID_D1,
	LX_OVI_DISP_VID_D2,
	LX_OVI_DISP_VID_D3,
	LX_OVI_DISP_OSD_D0,
	LX_OVI_DISP_OSD_D1,
	LX_OVI_DISP_OSD_D2,
	LX_OVI_DISP_OSD_D3
}
LX_OVI_DISP_DCH_T;

typedef enum
{
	LX_OVI_LVDS_MODE_NORMAL,				///< Normal LVDS
	LX_OVI_LVDS_MODE_HS					///< HS(High Speed) LVDS
}
LX_OVI_LVDS_MODE_T;

typedef enum
{
	LX_OVI_LVDS_OUT_JEIDA,				///< JEIDA LVDS
	LX_OVI_LVDS_OUT_VESA					///< VESA LVDS
}
LX_OVI_LVDS_OUT_STD_T;

typedef enum {
	LX_OVI_EPI_6LANE,
	LX_OVI_EPI_12LANE,
	LX_OVI_EPI_16LANE
}
LX_OVI_EPI_LANE_T;

typedef enum {
	LX_OVI_SPREAD_RATIO_1,	// 0.75%
	LX_OVI_SPREAD_RATIO_2,	// 1.00%
	LX_OVI_SPREAD_RATIO_3,	// 1.25%
	LX_OVI_SPREAD_RATIO_4,	// 1.50%
	LX_OVI_SPREAD_RATIO_DEFAULT = LX_OVI_SPREAD_RATIO_3
}
LX_OVI_SPREAD_RATIO_T;

#define LX_OVI_SPREAD_SPECTRUM_DEFAULT_PERIOD	70

typedef struct
{
	LX_OVI_DISP_DCH_T ePort0Input;	
	LX_OVI_DISP_DCH_T ePort1Input;
	LX_OVI_DISP_DCH_T ePort2Input;
	LX_OVI_DISP_DCH_T ePort3Input;
} LX_OVI_LVDS_PORT_SEL_T;

/* IOCTL parameter */
typedef struct
{
	UINT32 version;
} LX_OVI_CONFIG_VER_T;

typedef struct
{
	LX_OVI_LVDS_MODE_T eMode;
	BOOLEAN bEnable;
	BOOLEAN bPowDn;
	BOOLEAN bSwapEn;
	LX_OVI_H_WIDTH_T eVideoHWidth;
	LX_OVI_H_WIDTH_T eOsdHWidth;
	LX_OVI_LVDS_OUT_STD_T eOutputStd;
	LX_OVI_BIT_DEPTH_T eBitDepth;
	LX_OVI_BANDWIDTH_T eVideoBandwidth;
	LX_OVI_BANDWIDTH_T eOsdBandwidth;
	LX_OVI_LVDS_PORT_SEL_T outputPortSel;
} LX_OVI_LVDS_T;

typedef struct
{
	BOOLEAN bEnable;
	BOOLEAN bPowDn;
	LX_OVI_H_WIDTH_T eVideoHWidth;
	LX_OVI_H_WIDTH_T eOsdHWidth;
	LX_OVI_BIT_DEPTH_T eBitDepth;
	LX_OVI_BANDWIDTH_T eVideoBandwidth;
	LX_OVI_BANDWIDTH_T eOsdBandwidth;
} LX_OVI_VX1_T;

typedef struct
{
	BOOLEAN bEnable;
	BOOLEAN bPowDn;
	LX_OVI_BIT_DEPTH_T eBitDepth;
	LX_OVI_EPI_LANE_T eOutput;
} LX_OVI_EPI_T;

typedef struct
{
	LX_OVI_LVDS_T lvds;
	LX_OVI_VX1_T vx1;
	LX_OVI_EPI_T epi;
} LX_OVI_INFO_T;

typedef struct
{
	BOOLEAN bEnable;
	LX_OVI_SPREAD_RATIO_T eSpreadRatio;
	UINT16 u16Period;	// default value : LX_OVI_SPREAD_SPECTRUM_DEFAULT_PERIOD
} LX_OVI_SPREAD_SPECTRUM_T;

typedef struct
{
	unsigned int	addr;
	unsigned int	value;
}	LX_OVI_REG_T;

typedef struct
{
	char index[LX_OVI_MAX_NUM_OF_MODE_INDEX_CHAR];
	LX_OVI_REG_T* regs;
	UINT32 count;
} LX_OVI_OUTPUT_MODE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _OVI_DRV_H_ */

/** @} */

