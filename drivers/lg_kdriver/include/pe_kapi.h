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



/** @file pe_kapi.h
 *
 *  application interface header for picture enhance modules.
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_KAPI_H_
#define	_PE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifndef USE_XTENSA
#include "base_types.h"
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	PE_IOC_MAGIC		'a'
#define PE_IOC_MAXNR		100

#define LX_PE_CMG_TBLPOINT			8
#define LX_PE_CMG_REGION_MAX		15
#define LX_PE_CMG_REGION_NUM		(LX_PE_CMG_REGION_MAX+1)
#define LX_PE_CMG_DELTANUM			6
#define LX_PE_CMG_DELTA_SETNUM		2

/* pe debug print define, just for pe drv,io,reg,spd debug */
#undef PE_USE_DBG_PRINT

#define PE_NUM_OF_CSC_COEF	9
#define PE_NUM_OF_CSC_OFST	6

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_IOWR_PKT					_IOWR(PE_IOC_MAGIC, 0, LX_PE_PKT_T)

#define PE_ITEM_PKTRW(_str)			PE_PKTRW_##_str
#define PE_ITEM_PKTMODL(_str)		PE_PKTMODL_##_str
#define PE_ITEM_PKTFUNC(_str)		PE_PKTFUNC_##_str

#define PE_PKTINFO_RWTYPE_POS		24
#define PE_PKTINFO_RWTYPE_BITS		0x000000ff
#define PE_PKTINFO_MODLTYPE_POS		16
#define PE_PKTINFO_MODLTYPE_BITS	0x000000ff
#define PE_PKTINFO_FUNCTYPE_POS		0
#define PE_PKTINFO_FUNCTYPE_BITS	0x0000ffff

#define PE_PKTINFO_RWTYPE_MAXNUM	PE_PKTINFO_RWTYPE_BITS
#define PE_PKTINFO_MODLTYPE_MAXNUM	PE_PKTINFO_MODLTYPE_BITS
#define PE_PKTINFO_FUNCTYPE_MAXNUM	PE_PKTINFO_FUNCTYPE_BITS

#define PE_LSHIFT_DATA(_val, _bits, _pos)	(((_val)&(_bits))<<(_pos))
#define PE_DATA_MASK(_bits, _pos)			((_bits)<<(_pos))
#define PE_RSHIFT_DATA(_val, _bits, _pos)	(((_val)&PE_DATA_MASK((_bits),(_pos)))>>(_pos))

#define PE_SET_PKTINFO_RWTYPE(_info,_type)	\
	_info = (( (_info) & ~(PE_DATA_MASK(PE_PKTINFO_RWTYPE_BITS,PE_PKTINFO_RWTYPE_POS)) ) \
			| (PE_LSHIFT_DATA(_type,PE_PKTINFO_RWTYPE_BITS,PE_PKTINFO_RWTYPE_POS)))
#define PE_GET_PKTINFO_RWTYPE(_info)	PE_RSHIFT_DATA(_info, PE_PKTINFO_RWTYPE_BITS, PE_PKTINFO_RWTYPE_POS)

#define PE_SET_PKTINFO_MODLTYPE(_info,_type)	\
	_info = (( (_info) & ~(PE_DATA_MASK(PE_PKTINFO_MODLTYPE_BITS,PE_PKTINFO_MODLTYPE_POS)) ) \
			| (PE_LSHIFT_DATA(_type,PE_PKTINFO_MODLTYPE_BITS,PE_PKTINFO_MODLTYPE_POS)))
#define PE_GET_PKTINFO_MODLTYPE(_info)	PE_RSHIFT_DATA(_info, PE_PKTINFO_MODLTYPE_BITS, PE_PKTINFO_MODLTYPE_POS)

#define PE_SET_PKTINFO_FUNCTYPE(_info,_type)	\
	_info = (( (_info) & ~(PE_DATA_MASK(PE_PKTINFO_FUNCTYPE_BITS,PE_PKTINFO_FUNCTYPE_POS)) ) \
			| (PE_LSHIFT_DATA(_type,PE_PKTINFO_FUNCTYPE_BITS,PE_PKTINFO_FUNCTYPE_POS)))
#define PE_GET_PKTINFO_FUNCTYPE(_info)	PE_RSHIFT_DATA(_info, PE_PKTINFO_FUNCTYPE_BITS, PE_PKTINFO_FUNCTYPE_POS)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/**
 *	pe window index enumeration
 */
typedef enum
{
	LX_PE_WIN_0 = 0,				///< window 0
	LX_PE_WIN_1,					///< window 1

	LX_PE_WIN_ALL,					///< all window
	LX_PE_WIN_NUM = LX_PE_WIN_ALL,	///< number of windows
}
LX_PE_WIN_ID;

/**
 *	pe debug type enumeration
 */
typedef enum {
	LX_PE_DBG_NONE		= 0x0,	///< set nothing, reserved
	LX_PE_DBG_LV		= 0x1,	///< debug print level on, off
	LX_PE_DBG_BY		= 0x2,	///< bypass mode on, off
	LX_PE_DBG_FW		= 0x4,	///< fw ctrl on, off
	LX_PE_DBG_ALL		= LX_PE_DBG_LV|LX_PE_DBG_BY|LX_PE_DBG_FW	///< set all
}
LX_PE_DBG_TYPE;

/**
 *	pe level type enumeration
 */
typedef enum {
	LX_PE_LEVEL_MOTION		= 0x1,	///< select only motion level
	LX_PE_LEVEL_NOISE		= 0x2,	///< select only noise level
	LX_PE_LEVEL_PEAKPOS		= 0x4,	///< select only peak pos level
	LX_PE_LEVEL_ALL			= 0x7	///< set all
}
LX_PE_LEVEL_TYPE;

/**
 *	pe source type enumeration
 */
typedef enum {
	LX_PE_SRC_DTV = 0,	///< digital input
	LX_PE_SRC_ATV,		///< analog rf input
	LX_PE_SRC_CVBS,		///< analog cvbs, s-video input
	LX_PE_SRC_COMP,		///< externel input, component
	LX_PE_SRC_PC,		///< externel input, rgb-pc,hdmi-pc
	LX_PE_SRC_HDMI,		///< externel input, hdmi
	LX_PE_SRC_NUM		///< max num
}
LX_PE_SRC_TYPE;

/**
 *	pe format type enumeration
 */
typedef enum {
	LX_PE_FMT_HD = 0,		///< hd input
	LX_PE_FMT_SD,			///< sd input
	LX_PE_FMT_NTSC,			///< analog input, ntsc
	LX_PE_FMT_PAL,			///< analog input, pal
	LX_PE_FMT_SECAM,		///< analog input, secam
	LX_PE_FMT_SCARTRGB,		///< analog input, scartrgb
	LX_PE_FMT_NUM			///< max num
}
LX_PE_FMT_TYPE;

/**
 *	pe output type enumeration
 */
typedef enum {
	LX_PE_OUT_2D = 0,		///< single normal
	LX_PE_OUT_3D_2D,		///< 3d to 2d
	LX_PE_OUT_2D_3D,		///< 2d to 3d
	LX_PE_OUT_UD,			///< ud
	LX_PE_OUT_TB,			///< top and bottom
	LX_PE_OUT_SS,			///< side by side
	LX_PE_OUT_FS,			///< frame sequential
	LX_PE_OUT_DUAL_TB,		///< dual screen Top n Bottom
	LX_PE_OUT_DUAL_SS,		///< dual screen Side by Side
	LX_PE_OUT_DUAL_FULL,	///< dual screen Full
	LX_PE_OUT_PIP,			///< pip screen
	LX_PE_OUT_NUM			///< max num
}
LX_PE_OUT_TYPE;

/**
 *	pe frame rate type enumeration
 */
typedef enum {
	LX_PE_FR_60HZ = 0,	///< frame rate 60hz,30hz,24hz
	LX_PE_FR_50HZ,		///< frame rate 50hz,25hz
	LX_PE_FR_NUM		///< max num
}
LX_PE_FR_TYPE;

/**
 *	pe scan type enumeration
 */
typedef enum {
	LX_PE_SCAN_INTERLACE = 0,	///< scan type interlace
	LX_PE_SCAN_PROGRESS,		///< scan type progress
	LX_PE_SCAN_NUM				///< max num
}
LX_PE_SCAN_TYPE;

/**
 *	pe dtv play type enumeration
 */
typedef enum {
	LX_PE_DTV_NORMAL = 0,	///< dtv type normal
	LX_PE_DTV_FILEPLAY,		///< dtv type fileplay
	LX_PE_DTV_HDDPLAY,		///< dtv type hddplay
	LX_PE_DTV_PHOTOPLAY,	///< dtv type photoplay
	LX_PE_DTV_TESTPIC,		///< dtv type test picture
	LX_PE_DTV_INVALID,		///< dtv type invalid, not dtv
	LX_PE_DTV_NUM			///< max num
}
LX_PE_DTV_TYPE;

/**
 *	pe hdd src type enumeration
 */
typedef enum {
	LX_PE_HDD_SRC_DTV = 0,		///< hdd src dtv
	LX_PE_HDD_SRC_ATV60,		///< hdd src atv 60
	LX_PE_HDD_SRC_ATV50,		///< hdd src atv 50
	LX_PE_HDD_SRC_AV60,			///< hdd src av 60
	LX_PE_HDD_SRC_AV50,			///< hdd src av 50
	LX_PE_HDD_SRC_SCARTRGB,		///< hdd src scart rgb
	LX_PE_HDD_SRC_INVALID,		///< hdd src invalid, not hdd
	LX_PE_HDD_SRC_NUM			///< max num
}
LX_PE_HDD_SRC_TYPE;

/**
 * pe 3D formatter image format parameter.
 * see LX_3D_IMG_FMT_IN_T
 */
typedef enum {
	LX_PE_3D_IN_TB = 0,		///< top and bottom
	LX_PE_3D_IN_SS,			///< side by side
	LX_PE_3D_IN_QC,			///< quincunx
	LX_PE_3D_IN_CB,			///< check board
	LX_PE_3D_IN_FP,			///< frame packing
	LX_PE_3D_IN_FPI,		///< frame packing interlace
	LX_PE_3D_IN_FA,			///< field alternate
	LX_PE_3D_IN_FS,			///< frame sequence
	LX_PE_3D_IN_LA,			///< line alternate
	LX_PE_3D_IN_SSF,		///< side by side full
	LX_PE_3D_IN_DUAL,		///< dual HD
	LX_PE_3D_IN_CA,			///< column alternate
	LX_PE_3D_IN_LAH,		///< line alternate half
	LX_PE_3D_IN_NUM			///< max number
}
LX_PE_3D_IN_TYPE;

/**
 *	pe histogram bin mode enumeration
 */
typedef enum
{
	LX_PE_64_BINMODE = 0,	///< 64 bin mode
	LX_PE_32_BINMODE,		///< 32 bin mode
	LX_PE_16_BINMODE,		///< 16 bin mode
	LX_PE_BINMODE_NUM		///< max num
}
LX_PE_BINMODE;

/**
 *	pe dynamic contrast enhancement color domain enumeration
 */
typedef enum
{
	LX_PE_HSV_DOMAIN = 0,	///< scaled hsv domain
	LX_PE_YC_DOMAIN,		///< yc domain
	LX_PE_ORG_HSV_DOMAIN,	///< normal hsv domain
	LX_PE_HSL_DOMAIN,		///< hsl domain
	LX_PE_DOMAIN_NUM		///< max num
}
LX_PE_COLOR_DOMAIN;

/**
 *	pe color gamut csc type enumeration
 */
typedef enum
{
	PE_CSC_GAMUT_BYPASS = 0,	///< bypass
	PE_CSC_GAMUT_EBU,			///< ebu
	PE_CSC_GAMUT_SMPTE,			///< smpte
	PE_CSC_GAMUT_BT709,			///< bt709
	PE_CSC_GAMUT_NUM			///< max num
}
LX_PE_CSC_GAMUT_TYPE;

/**
 *	pe post csc type enumeration
 */
typedef enum
{
	PE_CSC_POST_BYPASS = 0,		///< bypass
	PE_CSC_POST_Y709_GBR256,	///< ycbcr709 to gbr256
	PE_CSC_POST_Y709_GBR220,	///< ycbcr709 to gbr220
	PE_CSC_POST_Y601_GBR256,	///< ycbcr601 to gbr256
	PE_CSC_POST_Y601_GBR220,	///< ycbcr601 to gbr220
	PE_CSC_POST_NUM				///< max num
}
LX_PE_CSC_POST_TYPE;

/**
 *	pe input csc type enumeration
 */
typedef enum
{
	PE_CSC_INPUT_BYPASS = 0,		///< ycbcr to ycbcr
	PE_CSC_INPUT_LIMIT,				///< ycbcr(0~255) to ycbcr(16~235)
	PE_CSC_INPUT_EXPEND,			///< ycbcr(32~235) to ycbcr(16~235)
	PE_CSC_INPUT_RGB_Y709_LINEAR,	///< rgb(16~235) to y709(16~235)
	PE_CSC_INPUT_RGB_Y709_LIMIT,	///< rgb(0~255) to y709(16~235)
	PE_CSC_INPUT_RGB_Y601_LINEAR,	///< rgb(16~235) to y601(16~235)
	PE_CSC_INPUT_RGB_Y601_LIMIT,	///< rgb(0~255) to y601(16~235)
	PE_CSC_INPUT_RGB_Y601_SECAM,	///< rgb(16~235) to y601(16~235), for secam
	PE_CSC_INPUT_NUM				///< max num
}
LX_PE_CSC_INPUT_TYPE;

/**
 *	pe d3d module format type enumeration
 */
typedef enum {
	LX_PE_D3D_FMT_2D_2D = 0,
	LX_PE_D3D_FMT_3D_3D,
	LX_PE_D3D_FMT_3D_CB = LX_PE_D3D_FMT_3D_3D,
	LX_PE_D3D_FMT_3D_CC,
	LX_PE_D3D_FMT_3D_LL,
	LX_PE_D3D_FMT_3D_SS,
	LX_PE_D3D_FMT_3D_TB,
	LX_PE_D3D_FMT_UNKNOWN,
	LX_PE_D3D_FMT_MAX
}
LX_PE_D3D_FORMAT;

/**
 *	pe d3d module debug type enumeration
 */
typedef enum {
	LX_PE_D3D_DEC_OFF,
	LX_PE_D3D_DEC_ON,
	LX_PE_D3D_DEC_PATTERN,
	LX_PE_D3D_DEC_LOG,
	LX_PE_D3D_DEC_FIX_2D,
	LX_PE_D3D_DEC_FIX_3D,
	LX_PE_D3D_DEC_FIX_FULL_WIN,	
	LX_PE_D3D_DEC_MAX
}
LX_PE_D3D_DEC;

/**
 *	pe d3d module capture debug type enumeration
 */
typedef enum {
	LX_PE_D3D_CAP_OFF,
	LX_PE_D3D_CAP_ON,
	LX_PE_D3D_CAP_FMT,
	LX_PE_D3D_CAP_TIME,
	LX_PE_D3D_CAP_DRAW,
	LX_PE_D3D_CAP_LOG,
	LX_PE_D3D_CAP_MAX
}
LX_PE_D3D_CAP;

/**
 *	pe d3d dual screen format type enumeration
 */
typedef enum {
	LX_PE_D3D_DSC_2D,
	LX_PE_D3D_DSC_SS,
	LX_PE_D3D_DSC_TB,
	LX_PE_D3D_DSC_MAX
}
LX_PE_D3D_DSC;

/**
 *	packet type descripter for read, write, init
 */
typedef enum
{
	PE_ITEM_PKTRW(INIT)	= 0,	///< init type
	PE_ITEM_PKTRW(SET)	= 1,	///< set type
	PE_ITEM_PKTRW(GET)	= 2,	///< get type
	PE_ITEM_PKTRW(NUM),			///< rw type number
	PE_ITEM_PKTRW(MAX)	= PE_PKTINFO_RWTYPE_MAXNUM	///< max
}
LX_PE_PKT_RWTYPE;

/**
 *	packet type descripter for pe modules
 */
typedef enum
{
	PE_ITEM_PKTMODL(INIT)		= 0,	///< using init module
	PE_ITEM_PKTMODL(DEFAULT)	= 1,	///< set default settings on each module
	PE_ITEM_PKTMODL(DBG)		= 2,	///< set debug settings on each module
	PE_ITEM_PKTMODL(CMN)		= 3,	///< using common module
	PE_ITEM_PKTMODL(CSC)		= 4,	///< using csc module
	PE_ITEM_PKTMODL(CMG)		= 5,	///< using color manege module
	PE_ITEM_PKTMODL(NRD)		= 6,	///< using noise reduction module
	PE_ITEM_PKTMODL(DNT)		= 7,	///< using deinterlacer module
	PE_ITEM_PKTMODL(SHP)		= 8,	///< using sharpness module
	PE_ITEM_PKTMODL(CCM)		= 9,	///< using color correction module
	PE_ITEM_PKTMODL(DCM)		= 10,	///< using dynamic contrast module
	PE_ITEM_PKTMODL(WIN)		= 11,	///< using window control module
	PE_ITEM_PKTMODL(ETC)		= 12,	///< using etc(misc) control module
	PE_ITEM_PKTMODL(NUM),				///< module type number
	PE_ITEM_PKTMODL(MAX)		= PE_PKTINFO_MODLTYPE_MAXNUM	///< max
}
LX_PE_PKT_MODLTYPE;

/**
 *	packet type descripter for functions
 */
typedef enum
{
	PE_ITEM_PKTFUNC(LX_PE_INIT_SETTINS_T)		= 10000,	///< using struct LX_PE_INIT_SETTINS_T
	PE_ITEM_PKTFUNC(LX_PE_DEFAULT_SETTINGS_T)	= 10001,	///< using struct LX_PE_DEFAULT_SETTINGS_T
	PE_ITEM_PKTFUNC(LX_PE_DBG_SETTINGS_T)		= 10002,	///< using struct LX_PE_DBG_SETTINGS_T

	PE_ITEM_PKTFUNC(LX_PE_CMN_CONTRAST_T)		= 11000,	///< using struct LX_PE_CMN_CONTRAST_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_BRIGHTNESS_T)		= 11001,	///< using struct LX_PE_CMN_BRIGHTNESS_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_SATURATION_T)		= 11002,	///< using struct LX_PE_CMN_SATURATION_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_HUE_T)			= 11003,	///< using struct LX_PE_CMN_HUE_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_LEVEL_CTRL_T)		= 11004,	///< using struct LX_PE_CMN_LEVEL_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMN_SUB_CONTRAST_T)	= 11005,	///< using struct LX_PE_CMN_SUB_CONTRAST_T

	PE_ITEM_PKTFUNC(LX_PE_CSC_XVYCC_T)			= 12000,	///< using struct LX_PE_CSC_XVYCC_T
	PE_ITEM_PKTFUNC(LX_PE_CSC_GAMUT_T)			= 12001,	///< using struct LX_PE_CSC_GAMUT_T
	PE_ITEM_PKTFUNC(LX_PE_CSC_POST_T)			= 12002,	///< using struct LX_PE_CSC_POST_T
	PE_ITEM_PKTFUNC(LX_PE_CSC_INPUT_T)			= 12003,	///< using struct LX_PE_CSC_INPUT_T

	PE_ITEM_PKTFUNC(LX_PE_CMG_ENABLE_T)			= 13000,	///< using struct LX_PE_CMG_ENABLE_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_ENABLE_T)	= 13001,	///< using struct LX_PE_CMG_REGION_ENABLE_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_T)			= 13002,	///< using struct LX_PE_CMG_REGION_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_REGION_CTRL_T)	= 13003,	///< using struct LX_PE_CMG_REGION_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_GLOBAL_CTRL_T)	= 13004,	///< using struct LX_PE_CMG_GLOBAL_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_COLOR_CTRL_T)		= 13005,	///< using struct LX_PE_CMG_COLOR_CTRL_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_CW_CTRL_T)		= 13006,	///< using struct LX_PE_CCM_CW_T
	PE_ITEM_PKTFUNC(LX_PE_CMG_CW_GAIN_CTRL_T)	= 13007,	///< using struct LX_PE_CMG_CW_GAIN_CTRL_T

	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR_CRGN_T)		= 14000,	///< using struct LX_PE_NRD_TNR_CRGN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR0_CMN_T)		= 14001,	///< using struct LX_PE_NRD_DNR0_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR0_CMN_T)		= 14002,	///< using struct LX_PE_NRD_TNR0_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR1_CMN_T)		= 14003,	///< using struct LX_PE_NRD_DNR1_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR1_DETAIL_T)	= 14004,	///< using struct LX_PE_NRD_DNR1_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR1_CMN_T)		= 14005,	///< using struct LX_PE_NRD_TNR1_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR1_DETAIL_T)	= 14006,	///< using struct LX_PE_NRD_TNR1_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR2_CMN_T)		= 14007,	///< using struct LX_PE_NRD_DNR2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_DNR2_DETAIL_T)	= 14008,	///< using struct LX_PE_NRD_DNR2_DETAIL_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2_CMN_T)		= 14009,	///< using struct LX_PE_NRD_TNR2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_NRD_TNR2_DETAIL_T)	= 14010,	///< using struct LX_PE_NRD_TNR2_DETAIL_T

	PE_ITEM_PKTFUNC(LX_PE_DNT_FILMMODE_T)		= 15000,	///< using struct LX_PE_DNT_FILMMODE_T
	PE_ITEM_PKTFUNC(LX_PE_DNT_LD_MODE_T)		= 15001,	///< using struct LX_PE_DNT_LD_MODE_T

	PE_ITEM_PKTFUNC(LX_PE_SHP_SCLFILTER_T)		= 16000,	///< using struct LX_PE_SHP_SCLFILTER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE0_CMN_T)		= 16001,	///< using struct LX_PE_SHP_RE0_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE0_HOR_T)		= 16002,	///< using struct LX_PE_SHP_RE0_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE0_VER_T)		= 16003,	///< using struct LX_PE_SHP_RE0_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_EE0_T)			= 16004,	///< using struct LX_PE_SHP_EE0_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_CMN_T)		= 16005,	///< using struct LX_PE_SHP_RE1_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_HOR_T)		= 16006,	///< using struct LX_PE_SHP_RE1_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_VER_T)		= 16007,	///< using struct LX_PE_SHP_RE1_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE1_MISC_T)		= 16008,	///< using struct LX_PE_SHP_RE1_MISC_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_EE1_T)			= 16009,	///< using struct LX_PE_SHP_EE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_DE1_T)			= 16010,	///< using struct LX_PE_SHP_DE1_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_CMN_T)		= 16011,	///< using struct LX_PE_SHP_RE2_CMN_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_HOR_T)		= 16012,	///< using struct LX_PE_SHP_RE2_HOR_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_VER_T)		= 16013,	///< using struct LX_PE_SHP_RE2_VER_T
	PE_ITEM_PKTFUNC(LX_PE_SHP_RE2_MISC_T)		= 16014,	///< using struct LX_PE_SHP_RE2_MISC_T

	PE_ITEM_PKTFUNC(LX_PE_CCM_GAMMALUT_T)		= 17000,	///< using struct LX_PE_CCM_GAMMALUT_T
	PE_ITEM_PKTFUNC(LX_PE_CCM_PIXEL_REPLACE_T)	= 17001,	///< using struct LX_PE_CCM_PIXEL_REPLACE_T
	PE_ITEM_PKTFUNC(LX_PE_CCM_WB_T)				= 17002,	///< using struct LX_PE_CCM_WB_T
	PE_ITEM_PKTFUNC(LX_PE_CCM_AUTO_CR_T)		= 17003,	///< using struct LX_PE_CCM_AUTO_CR_T

	PE_ITEM_PKTFUNC(LX_PE_DCM_HISTO_INFO_T)		= 18000,	///< using struct LX_PE_DCM_HISTO_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_CONF_T)		= 18001,	///< using struct LX_PE_DCM_DCE_CONF_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_LUT_T)		= 18002,	///< using struct LX_PE_DCM_DCE_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DSE_LUT_T)		= 18003,	///< using struct LX_PE_DCM_DSE_LUT_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_BLENDING_T)		= 18004,	///< using struct LX_PE_DCM_BLENDING_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_HISTO_CFG_T)		= 18005,	///< using struct LX_PE_DCM_HISTO_CFG_T
	PE_ITEM_PKTFUNC(LX_PE_DCM_DCE_SMOOTH_T)		= 18006,	///< using struct LX_PE_DCM_DCE_SMOOTH_T

	PE_ITEM_PKTFUNC(LX_PE_WIN_D3D_INFO_T)		= 19000,	///< using struct LX_PE_WIN_D3D_INFO_T

	PE_ITEM_PKTFUNC(LX_PE_ETC_DBG_T)			= 20000,	///< using struct LX_PE_ETC_DBG_T
	PE_ITEM_PKTFUNC(LX_PE_D3D_SETTINGS_T)		= 20001,	///< using struct LX_PE_D3D_SETTINGS_T
	PE_ITEM_PKTFUNC(LX_PE_D3D_INFO_T)			= 20002,	///< using struct LX_PE_D3D_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_D3D_DSC_INFO_T)		= 20003,	///< using struct LX_PE_D3D_DSC_INFO_T
	PE_ITEM_PKTFUNC(LX_PE_INF_DISPLAY_T)		= 20004,	///< using struct LX_PE_INF_DISPLAY_T
	PE_ITEM_PKTFUNC(LX_PE_INF_LEVEL_T)			= 20005,	///< using struct LX_PE_INF_LEVEL_T

	PE_ITEM_PKTFUNC(MAX)						= PE_PKTINFO_FUNCTYPE_MAXNUM	///< max
}
LX_PE_PKT_FUNCTYPE;

/**
 *	pe packet
 */
typedef struct
{
	UINT32 info;	///< [31:24]LX_PE_PKT_RWTYPE | [23:16]LX_PE_PKT_MODLTYPE | [15:0]LX_PE_PKT_FUNCTYPE
	UINT32 size;	///< size of data
	void *data;		///< packet data
}
LX_PE_PKT_T;

/**
 *	pe firmware control parameter type
 */
typedef struct
{
	UINT32 use_fw;		///< use fw or not
	UINT32 ctrl_en;		//< fw control enable or not
	UINT32 dbg_en;		///< dbg print enable or not
}
LX_PE_DBG_FWI_CTRL_T;

/**
 *	pe debug settings control parameter type (only for debug)
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_DBG_TYPE	type;		///< debug type
	UINT32 print_lvl;			///< pe debug print level
	UINT32 bypass;				///< bypass each module
	LX_PE_DBG_FWI_CTRL_T fwc;	///< fw ctrl
}
LX_PE_DBG_SETTINGS_T;

/**
 *	pe default settings control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID	win_id;		///< window id
}
LX_PE_DEFAULT_SETTINGS_T;

/**
 *	pe initial settings control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 suspend_mode;		///< suspend mode, 0:off(default), 1:on
}
LX_PE_INIT_SETTINS_T;

/***************************************************************************/
/* CMN : Common */
/***************************************************************************/
/**
 *	pe contrast control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT16 contrast;		///< contrast value
}
LX_PE_CMN_CONTRAST_T;

/**
 *	pe brightness control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 brightness;		///< brightness value
}
LX_PE_CMN_BRIGHTNESS_T;

/**
 *	pe saturation control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 saturation;		///< saturation value
}
LX_PE_CMN_SATURATION_T;

/**
 *	pe hue control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 hue;				///< hue value
}
LX_PE_CMN_HUE_T;

/**
 *	pe level control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 offset;			///< display input y offset, 0~512~1023
    UINT16 center;			///< center position for y gain control, 0~128~255
    UINT16 gain;			///< display input y gain, 0~128~255
	UINT16 tp_on;			///< test pattern on,off
}
LX_PE_CMN_LEVEL_CTRL_T;

/**
 *	pe sub contrast control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
    UINT16 contrast;		///< sub contrast, 0~512~1023
}
LX_PE_CMN_SUB_CONTRAST_T;

/***************************************************************************/
/* CCM : Color Correctin Module */
/***************************************************************************/
/**
 *	pe gamma lut control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 size;			///< size of lut_data
	UINT32 *data;			///< [29:20]R | [19:10]B | [9:0]G
}
LX_PE_CCM_GAMMALUT_T;

/**
 *	pe gamma pixel replacement control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 pxl_rep_r;		///< R value for pixel replacement, 1:on, 0:off, default:0
	UINT8 pxl_rep_g;		///< G value for pixel replacement, 1:on, 0:off, default:0
	UINT8 pxl_rep_b;		///< B value for pixel replacement, 1:on, 0:off, default:0
}
LX_PE_CCM_PIXEL_REPLACE_T;

/**
 *	pe white balance control parameter type
 */
typedef struct {
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 r_gain;			///< red gain, 		0~255(192= 1.0 gain)
	UINT8 g_gain;			///< green gain, 	0~255(192= 1.0 gain)
	UINT8 b_gain;			///< blue gain, 	0~255(192= 1.0 gain)
	UINT8 r_offset; 		///< red offset,	0~255(128= zero offset)
	UINT8 g_offset; 		///< green offset,	0~255(128= zero offset)
	UINT8 b_offset; 		///< blue offset,	0~255(128= zero offset)
}
LX_PE_CCM_WB_T;

/**
 *	pe left right mismatch correction control parameter type
 */
typedef struct {
	UINT8 enable;			///< enable LRCR, 1:on, 0:off
	UINT8 th_max_hist;		///< if(max_hist > th_max_hist), auto cr does not apply
	UINT8 th_valid_bins;	///< if(n_valid_bins > th_valid_bins), auto cr does not apply
	UINT8 adj_th0;			///< adjustment threshold 0
	UINT8 adj_th1;			///< adjustment threshold 1
}
LX_PE_CCM_AUTO_CR_T;

/***************************************************************************/
/* DCM : Dynamic Contrast Module */
/***************************************************************************/
/**
 *	pe histogram information parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_COLOR_DOMAIN domain;	///< color domain
	UINT32 bin_num;				///< bin number 16 or 32(default:32)
	UINT32 histo_ready;			///< histogram is valid, if 1, invalid otherwise.
	UINT32 average[3];			///< the average of all luma in the specified region Y or RGB
    UINT32 min;					///< the min of all luma in the specified region
	UINT32 max;					///< the max of all luma in the specified region
    UINT32 histogram[64];		///< histogram data of luma([0~31]1st_histo,[32~63]2nd_histo)
    UINT32 sat_status;			///< saturation status
    UINT32 status[5];			///< histogram status
    UINT32 motion;				///< motion status(from tnr block)
}
LX_PE_DCM_HISTO_INFO_T;

/**
 *	pe dynamic contrast enhancement configuration parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	LX_PE_COLOR_DOMAIN domain;		///< dce color domain.
	LX_PE_BINMODE bin_mode;			///< histogram bin number mode
	UINT32 lut_step;				///< lut step
    UINT32 min_pos;					///< the min position, default "26"(0~255(0%~100%))
	UINT32 max_pos;					///< the max position, default "220"(0~255(0%~100%))
}
LX_PE_DCM_DCE_CONF_T;

/**
 *	pe dynamic contrast lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 size;				///< lut step, size of data, sync with the lut step on dce config
	UINT32 *data;				///< [9:0] y data, [25:16] x data
}
LX_PE_DCM_DCE_LUT_T;

/**
 *	pe dynamic saturation lut parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 size;				///< lut step, size of data, sync with the lut step on dce config
	UINT32 *data;				///< [9:0] y data, [25:16] x data
}
LX_PE_DCM_DSE_LUT_T;


/**
 *	pe dynamic contrast bypass blending control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 color_out_gain;	///< dce out gain, 1(0%)~128(200%)~255(400%) (forbidden 0)
	UINT32 region_sel;		///< LSB : select region 0
}
LX_PE_DCM_BLENDING_T;

/**
 *	pe histogram operation parameter type
 */
typedef struct
{
	UINT32 src_apl_op;	///< src apl loading operation, 0:run, 1:stop
	UINT32 src_hist_op;	///< src histogarm loading operation, 0:run, 1:stop
	UINT32 lrc_hist_op;	///< lrcr histogarm loading operation, 0:run, 1:stop
}
LX_PE_DCM_HISTO_OPR_T;

/**
 *	pe histogram configuration parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_DCM_HISTO_OPR_T opr;	///< histo operation
}
LX_PE_DCM_HISTO_CFG_T;

/**
 *	pe dynamic blur control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 avg_filter_tap;		///< luma blur for DCE
	UINT32 edge_map_tap;		///< edge-map tap size for blending
	UINT32 e_to_w_th_x0;		///< edge to weight : x0
	UINT32 e_to_w_th_x1;		///< edge to weight : x1
	UINT32 e_to_w_th_y0;		///< edge to weight : y0
	UINT32 e_to_w_th_y1;		///< edge to weight : y2
	UINT32 chroma_blur_mode;	///< chroma blur for DCE
	UINT32 blur_v_gain;			///< 0x0 : blur V <-> 0xF : original V 
}
LX_PE_DCM_DCE_SMOOTH_T;

/***************************************************************************/
/* WIN : Window control */
/***************************************************************************/

/**
 *	pe window position type
 */
typedef struct
{
	UINT16 pos_x0;				///< start position of window, x position
	UINT16 pos_y0;				///< start position of window, y position
	UINT16 pos_x1;				///< end position of window, x position
	UINT16 pos_y1;				///< end position of window, y position
}
LX_PE_WIN_POS_T;

/**
 *	pe auto detection info. parameter type
 */
typedef struct
{
	LX_PE_WIN_POS_T top;		///< valid position of TB top
	LX_PE_WIN_POS_T bottom;		///< valid position of TB bottom
	LX_PE_WIN_POS_T left;		///< valid position of SS left
	LX_PE_WIN_POS_T right;		///< valid position of SS right
	UINT16 tb_ratio;			///< detection ratio for tb (1024=100%)
	UINT16 ss_ratio;			///< detection ratio for ss (1024=100%)
}
LX_PE_WIN_D3D_INFO_T;

/***************************************************************************/
/* CSC : Color Space Conversion */
/***************************************************************************/

/**
 *	pe color gamut csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_CSC_GAMUT_TYPE type;	///< gamut csc type
}
LX_PE_CSC_GAMUT_CTRL_T;

/**
 *	pe post csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	LX_PE_CSC_POST_TYPE type;	///< post csc type
}
LX_PE_CSC_POST_CTRL_T;

/**
 *	pe input csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 enable;				///< input csc enable 0:off,1:on
	LX_PE_CSC_INPUT_TYPE type;	///< input csc type
}
LX_PE_CSC_INPUT_CTRL_T;

/**
 *	pe xvYCC control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 enable;			///< enable xvYCC, 1:on, 0:off
	UINT8 scaler;			///< scaling factor, 0~255(255 = x1.0)
}
LX_PE_CSC_XVYCC_T;

/**
 *	pe color gamut control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT16 matrix[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix, primary color correction
}
LX_PE_CSC_GAMUT_T;

/**
 *	pe post csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT16 matrix[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix
	UINT16 offset[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset
}
LX_PE_CSC_POST_T;

/**
 *	input csc control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT32 enable;						///< input csc enable, 0:off,1:on
	UINT16 matrix[PE_NUM_OF_CSC_COEF];	///< 3x3 matrix
	UINT16 offset[PE_NUM_OF_CSC_OFST];	///< in[3],out[3] offset
}
LX_PE_CSC_INPUT_T;

/***************************************************************************/
/* CMG : Color Management */
/***************************************************************************/

/**
 *	pe color enhancement enable parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 enable;			///< cen enable, 0:off,1:on
}
LX_PE_CMG_ENABLE_T;

/**
 *	pe color enhancement region enable parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT8 enable[LX_PE_CMG_REGION_NUM];			///< enable region 0 ~ 15
	UINT8 show_region[LX_PE_CMG_REGION_NUM];	///< show region 0 ~ 15, for debug
}
LX_PE_CMG_REGION_ENABLE_T;

/**
 *	pe color enhancement region parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;					///< window id
	UINT32 region_num;						///< region number, 0~15
	UINT16 hue_x[LX_PE_CMG_TBLPOINT];		///< hue input, 0~512~1023(0~360~720 degree)
	UINT8 hue_g[LX_PE_CMG_TBLPOINT];		///< hue gain, 0~127
	UINT8 sat_x[LX_PE_CMG_TBLPOINT];		///< saturation input, 0~100
	UINT8 sat_g[LX_PE_CMG_TBLPOINT];		///< saturation gain, 0~127
	UINT8 val_x[LX_PE_CMG_TBLPOINT];		///< value input, 0~255
	UINT8 val_g[LX_PE_CMG_TBLPOINT];		///< value gain, 0~127
}
LX_PE_CMG_REGION_T;

/**
 *	pe color enhancement region control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	UINT32 region_num;							///< region number, 0~15
	SINT8 region_delta[LX_PE_CMG_DELTANUM];		///< region delta(offset), -128 ~ 127, [0]h [1]s [2]v [3]g [4]b [5]r
	UINT8 master_gain;							///< region master gain, 0~128~255
}
LX_PE_CMG_REGION_CTRL_T;

/**
 *	pe color enhancement global control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;						///< window id
	SINT16 global_delta[LX_PE_CMG_DELTANUM];	///< global gain,-512 ~ 511, [0]h [1]s [2]v [3]g [4]b [5]r
}
LX_PE_CMG_GLOBAL_CTRL_T;

/**
 *	pe color enhancement color control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT16 saturation;		///< saturation gain
}
LX_PE_CMG_COLOR_CTRL_T;

/** 
 *  pe clear white control parameter type
 */
typedef struct {
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 cw_en;			///< clear white enable
	UINT32 gain_sel;		///< Y-CR gain sel, '0' = use Y level gain, '1' = use CR region gain
	UINT32 gain_x[5];		///< gain table x0~4
	UINT32 gain_y[5];		///< gain table y0~4
	UINT32 region_sel;		///< color region sel 1=enable, bit control.(0x0 ~ 0xff)
	UINT32 region_gain;		///< color region gain, default : "64"( 0 ~ 255(1~400%))
}
LX_PE_CMG_CW_CTRL_T;

/** 
 *  pe clear white rgb gain control parameter type
 */
typedef struct {
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 g_gain;			///< User Control, G_Gain  (resolution = 2^(-9), 0~192~255)
	UINT32 b_gain;			///< User Control, B_Gain  (resolution = 2^(-9), 0~192~255)
	UINT32 r_gain;			///< User Control, R_Gain  (resolution = 2^(-9), 0~192~255)
}
LX_PE_CMG_CW_GAIN_CTRL_T;

/***************************************************************************/
/* NRD : Noise Reduction*/
/***************************************************************************/

/**
 *	pe tnr color region gain control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 gain_rgn[4];			///< color region gain, 0(g0.0) ~ 32(default,g1.0) ~ 255(g8.0)
}
LX_PE_NRD_TNR_CRGN_T;

/**
 *	pe digital noise reduction control parameter type
 *	ver.0, for L9Ax,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 mnr_enable;		///< mosquito nr enable
	UINT32 ac_bnr_h_en;		///< horizontal ac block nr enable
	UINT32 ac_bnr_v_en;		///< vertical ac block nr enable
	UINT32 dc_bnr_en;		///< dc block nr enable
	UINT32 mnr_gain;		///< mosquito nr gain, filter threshold
	UINT32 ac_bnr_h_gain;	///< ac block nr gain, strength h max
	UINT32 ac_bnr_v_gain;	///< ac block nr gain, strength v max
	UINT32 dc_bnr_gain;		///< dc block nr gain
}
LX_PE_NRD_DNR0_CMN_T;

/**
 *	pe digital noise reduction common control parameter type
 *	ver.1, for L9Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* mnr */
	UINT8 mnr_enable;					///< mnr_enable
	UINT8 filter_threshold;				///< Bi-lateral filter threshold
	/* ac_bnr */
	UINT8 bnr_h_en;						///< bnr_h en
	UINT8 bnr_v_en;						///< bnr_v_en
	UINT8 ac_bnr_protect_motion_max;	///< AC_BNR_PROTECT_motion_max
	UINT8 ac_bnr_protect_motion_min;	///< AC_BNR_PROTECT_motion_min
	UINT8 hbmax_gain;					///< HBmax gain
	UINT8 vbmax_gain;					///< VBmax gain
	UINT8 strength_h_max;				///< strength_h_max
	UINT8 strength_v_max;				///< strength_v_max
	/* dc_bnr */
	UINT8 dc_bnr_enable;				///< DC BNR enable
	UINT8 motion_min;					///< Motion min
	UINT8 motion_max;					///< Motion max
	UINT8 ac_blockiness_multifly;		///< AC Blockiness Multifly
}
LX_PE_NRD_DNR1_CMN_T;

/**
 *	pe digital noise reduction detailed control parameter type
 *	ver.1, for L9Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* mnr */
	UINT8 edge_gain_mapping_enable;		///< edge gain mapping enable
	UINT8 sel_sd_hd;					///< Sel_SD_H
	UINT8 x1_position;					///< X1 position
	UINT8 x2_position;					///< X2 position
	UINT8 x3_position;					///< X3 position
	UINT8 x4_position;					///< X4 position
	UINT8 y1_position;					///< Y1 position
	UINT8 y2_position;					///< Y2 position
	UINT8 y3_position;					///< Y3 position
	UINT8 y4_position;					///< Y4 position
	/* ac_bnr */
	UINT8 motion_protect_enable;		///< motion protect enable
	UINT8 source_type;					///< source type
	UINT8 fiter_type;					///< fiter type
	UINT8 strength_h_x0;				///< strength_h_x0
	UINT8 strength_h_x1;				///< strength_h_x1
	UINT8 detect_min_th;				///< Block Line Detection Minimun Threshold
	UINT8 strength_v_x0;				///< strength_v_x0
	UINT8 strength_v_x1;				///< strength_v_x1
	/* dc_bnr */
	UINT8 ac_blockiness_adaptive_mode;	///< AC Blockiness Adaptive Mode
	UINT8 motion_gain_enable;			///< motion gain enable
	UINT8 sd_hd_sel;					///< sd_hd se
	UINT8 dc_bnr_gain_ctrl_y2;			///< dc_bnr_gain_ctrl_Y2
	UINT8 dc_bnr_gain_ctrl_x2;			///< dc_bnr_gain_ctrl_X2
	UINT8 dc_bnr_gain_ctrl_y3;			///< dc_bnr_gain_ctrl_Y3
	UINT8 dc_bnr_gain_ctrl_x3;			///< dc_bnr_gain_ctrl_X3
	UINT8 dc_bnr_gain_ctrl_y0;			///< dc_bnr_gain_ctrl_Y0
	UINT8 dc_bnr_gain_ctrl_x0;			///< dc_bnr_gain_ctrl_X0
	UINT8 dc_bnr_gain_ctrl_y1;			///< dc_bnr_gain_ctrl_Y1
	UINT8 dc_bnr_gain_ctrl_x1;			///< dc_bnr_gain_ctrl_X1
}
LX_PE_NRD_DNR1_DETAIL_T;

/**
 *	pe digital noise reduction detailed control parameter type
 *	ver.2, for H13Bx
 */
typedef struct {
	LX_PE_WIN_ID win_id;				///< window id
	/* dnr main */
	UINT8 enable_ac_bnr;				///< enable_ac_bnr
	UINT8 enable_mnr;					///< enable_mnr
	UINT8 enable_dc_bnr;				///< enable_dc_bnr
	/* mnr */
	UINT8 reg_mnr_enable;				///< reg_mnr_enable
	UINT8 reg_mnr_master_gain;			///< reg_mnr_master_gain
	UINT8 reg_chroma_master_gain;		///< reg_chroma_master_gain
	UINT8 reg_mnr_h_gain;				///< reg_mnr_h_gain
	UINT8 reg_mnr_v_gain;				///< reg_mnr_v_gain
	/* ac_bnr */
	UINT8 bnr_h_en;						///< bnr_h_en
	UINT8 bnr_v_en;						///< bnr_v_en
	UINT8 ac_bnr_protect_motion_max;	///< ac_bnr_protect_motion_max
	UINT8 ac_bnr_protect_motion_min;	///< ac_bnr_protect_motion_min
	UINT8 hbmax_gain;					///< gain for maximum h-blockiness (0~7) d:4,(hmax * hbmaxgain) - hothers = hb
	UINT8 vbmax_gain;					///< gain for maximum v-blockiness (0~7) d:4,(vmax * vbmaxgain) - vothers = vb
	UINT8 strength_h_max;				///< strength_h_max
	UINT8 strength_v_max;				///< strength_v_max
	/* dc_bnr */
	UINT8 reg_dc_bnr_enable;			///< reg_dc_bnr_enable
	UINT8 reg_dc_bnr_mastergain;		///< reg_dc_bnr_mastergain
	UINT16 reg_dc_bnr_chromagain;		///< reg_dc_bnr_chromagain	
}LX_PE_NRD_DNR2_CMN_T;

typedef struct {
	LX_PE_WIN_ID win_id;				///< window id
	/* mnr */
	UINT8 reg_h_expend;					///< reg_h_expend
	UINT8 reg_gain_flt_size;			///< reg_gain_flt_size
	UINT8 reg_mnr_s1_mmd_min;			///< reg_mnr_s1_mmd_min
	UINT8 reg_mnr_s2_ratio_min;			///< reg_mnr_s2_ratio_min
	UINT8 reg_mnr_s2_ratio_max;			///< reg_mnr_s2_ratio_max
	UINT8 reg_mnr_s2_mmd_min;			///< reg_mnr_s2_mmd_min
	UINT8 reg_filter_x0;				///< reg_filter_x0
	UINT8 reg_filter_x1;				///< reg_filter_x1
	UINT8 reg_filter_y0;				///< reg_filter_y0
	UINT8 reg_filter_y1;				///< reg_filter_y1
	UINT8 reg_motion_mnr_en;			///< reg_motion_mnr_en
	UINT8 reg_motion_mnr_filter;		///< reg_motion_mnr_filter
	UINT8 reg_mnr_motion_min;			///< reg_mnr_motion_min
	UINT8 reg_mnr_motion_max;			///< reg_mnr_motion_max
	UINT8 reg_motion_mnr_x0;			///< reg_motion_mnr_x0
	UINT8 reg_motion_mnr_x1;			///< reg_motion_mnr_x1
	UINT8 reg_motion_mnr_y0;			///< reg_motion_mnr_y0
	UINT8 reg_motion_mnr_y1;			///< reg_motion_mnr_y1
	/* ac_bnr */
	UINT8 motion_protect_enable;		///< motion_protect_enable
	UINT8 source_type;					///< 0 := sd (9 lm),1 = hd (5 lm)
	UINT8 fiter_type;					///< 0  :=  normal 3-tap avg. 1 1 1, 1  =  center-weighted 3-tap avg : 1 2 1
	UINT8 strength_h_x0;				///< ( hb - offset ) * gain => graph
	UINT8 strength_h_x1;				///< strength_h_x1
	UINT8 detect_min_th;				///< minimun threshold of block line detection
	UINT8 strength_v_x0;				///< ( vb - offset ) * gain => graph
	UINT8 strength_v_x1;				///< strength_v_x1
	/* dc_bnr */
	UINT8 reg_dc_bnr_var_en;			///< reg_dc_bnr_var_en
	UINT8 reg_dc_bnr_motion_en;			///< reg_dc_bnr_motion_en
	UINT8 reg_dc_bnr_acadaptive;		///< reg_dc_bnr_acadaptive
	UINT8 reg_dc_bnr_sdhd_sel;			///< reg_dc_bnr_sdhd_sel
	UINT8 reg_dc_blur_sel;				///< reg_dc_blur_sel
	UINT8 reg_dc_protection_en;			///< reg_dc_protection_en
	UINT8 reg_dc_bnr_var_th0;			///< reg_dc_bnr_var_th0
	UINT8 reg_dc_bnr_var_th1;			///< reg_dc_bnr_var_th1
	UINT8 reg_dc_bnr_var_th2;			///< reg_dc_bnr_var_th2
	UINT8 reg_dc_bnr_var_th3;			///< reg_dc_bnr_var_th3
	UINT8 reg_dc_bnr_motion_th0;		///< reg_dc_bnr_motion_th0
	UINT8 reg_dc_bnr_motion_th1;		///< reg_dc_bnr_motion_th1
	UINT8 reg_dc_bnr_motion_th2;		///< reg_dc_bnr_motion_th2
	UINT8 reg_dc_bnr_motion_th3;		///< reg_dc_bnr_motion_th3
	UINT8 reg_dc_chroma_variance;		///< reg_dc_chroma_variance
	UINT8 reg_dc_var_h_gain;			///< reg_dc_var_h_gain
	UINT8 reg_dc_protection_th;			///< reg_dc_protection_th
}LX_PE_NRD_DNR2_DETAIL_T;

/**
 *	pe temporal noise reduction control parameter type
 *	ver.0, for L9Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 tnr_enable;		///< tnr enable
	UINT32 adj_nt_lvl_val;	///< adjust noise temporal level value
}
LX_PE_NRD_TNR0_CMN_T;

/**
 *	pe temporal noise reduction common control parameter type
 *	ver.1, for L9Bx,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	/* auto mode */
	UINT8 auto_mode;			///< auto nr mode, on(1),off(0)
	/* noise level gaining */
	UINT8 adjust_nt_lvl;		///< Adjust NT_Lvl enable
	UINT8 adjust_nt_lvl_val;	///< Adjust NT_Lvl value (8u, "this-128" will be added to Calculated NT_Lvl)
	/* alpha gain */
	UINT8 y_gain;				///< Y_TNR_Gain (3.5u)
	UINT8 c_gain;				///< C_TNR_Gain (3.5u)
}
LX_PE_NRD_TNR1_CMN_T;

/**
 *	pe temporal noise reduction detailed control parameter type
 *	ver.1, for L9Bx
 *	motion -> noise level(n-lvl) estimate -> n-lvl gaining -> n-lvl apply -> alpha gaining
 *         -> motion filter -> n-lvl apply
 *         -> scene change -> alpha gaining
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	/* adjust alpha(alpha gaining) */
	UINT8 wa_enable;					///< TNR strength adjust enable using spatial variance
	UINT8 wa_y0;						///< 0.8u,wa_Y0
	UINT8 wa_y1;						///< 0.8u,wa_Y1
	UINT8 wa_x0;						///< spatial variance threshold 0
	UINT8 wa_x1;						///< spatial variance threshold 1
	UINT8 adj_alpha_nt_lvl_th0;			///< adj_alpha_nt_lvl_th (LUTAlpha => finalAlpha)
	UINT8 adj_alpha_k0;					///< adj_alpha_k0 (LUTAlpha => finalAlpha) (4.4u, 6.0d=>0x20)
	UINT8 adj_alpha_k1;					///< adj_alpha_k1 (LUTAlpha => finalAlpha) (4.4u, 6.0d=>0x50)
	UINT8 adj_alpha_nt_lvl_th1;			///< adj_alpha_nt_lvl_th (LUTAlpha => finalAlpha)
	UINT8 wa_y2;						///< 0.8u,wa_Y2
	UINT8 wa_y3;						///< 0.8u,wa_Y3
	UINT8 wa_x2;						///< spatial variance threshold 2
	UINT8 wa_x3;						///< spatial variance threshold 3
	/* motion histo(n-lvl estimate) */
	UINT8 calc_motion_flt_enable;		///< motion filtering enable
	UINT8 calc_motion_flt_type;			///< motion filtering type
	UINT16 y_th_lo;						///< Y-Valid Range. tnr_y_th_lo (64d=>0x040)
	UINT16 y_th_hi;						///< Y-Valid Range. tnr_y_th_hi (1000d=>0x3E8)
	/* alpha gain(n-lvl gaining), gm,st gain */
	UINT8 nt_lvl_adjust_gm_enable;		///< noise level adjust (by the global motion amount) enable
	UINT8 nt_lvl_adjust_avg_ts_enable;	///< noise level adjust (by the (avg_t - avg_s))  enable
	UINT8 nt_lvl_gain_gm_y0;			///< 1.7u,nt_lvl_gain_gm_y0
	UINT8 nt_lvl_gain_gm_x0;			///< nt_lvl_gain_gm_x0
	UINT8 nt_lvl_gain_gm_y1;			///< 1.7u, nt_lvl_gain_gm_y1
	UINT8 nt_lvl_gain_gm_x1;			///< nt_lvl_gain_gm_x1
	UINT8 nt_lvl_gain_gm_y2;			///< 1.7u,nt_lvl_gain_gm_y2
	UINT8 nt_lvl_gain_gm_x2;			///< nt_lvl_gain_gm_x2
	UINT8 nt_lvl_gain_gm_y3;			///< 1.7u,nt_lvl_gain_gm_y3
	UINT8 nt_lvl_gain_gm_x3;			///< nt_lvl_gain_gm_x3
	UINT8 nt_lvl_gain_st_y0;			///< 1.7u,nt_lvl_gain_st_y0
	UINT8 nt_lvl_gain_st_x0;			///< 1.7u * avg_s,nt_lvl_gain_st_x0
	UINT8 nt_lvl_gain_st_y1;			///< 1.7u,nt_lvl_gain_st_y1
	UINT8 nt_lvl_gain_st_x1;			///< 1.7u * avg_s,nt_lvl_gain_st_x1
	UINT8 nt_lvl_gain_st_y2;			///< 1.7u,nt_lvl_gain_st_y2
	UINT8 nt_lvl_gain_st_x2;			///< 1.7u * avg_s,nt_lvl_gain_st_x2
	UINT8 nt_lvl_gain_st_y3;			///< 1.7u,nt_lvl_gain_st_y3
	UINT8 nt_lvl_gain_st_x3;			///< 1.7u * avg_s,nt_lvl_gain_st_x3
	/* alpha lut(n-lvl apply) */
	UINT8 alpha_lut_ind7;				///< alpha_lut_ind7 (NTLvl => Alpha LUT Curve) (52d=>0x34)
	UINT8 alpha_lut_ind0;				///< alpha_lut_ind0 (NTLvl => Alpha LUT Curve) (9d=>0x09)
	UINT8 alpha_lut_ind1;				///< alpha_lut_ind1 (NTLvl => Alpha LUT Curve) (17d=>0x11)
	UINT8 alpha_lut_ind2;				///< alpha_lut_ind2 (NTLvl => Alpha LUT Curve) (24d=>0x18)
	UINT8 alpha_lut_ind3;				///< alpha_lut_ind3 (NTLvl => Alpha LUT Curve) (30d=>0x1E) 
	UINT8 alpha_lut_ind4;				///< alpha_lut_ind4 (NTLvl => Alpha LUT Curve) (40d=>0x28)
	UINT8 alpha_lut_ind5;				///< alpha_lut_ind5 (NTLvl => Alpha LUT Curve) (46d=>0x2E)
	UINT8 alpha_lut_ind6;				///< alpha_lut_ind6 (NTLvl => Alpha LUT Curve) (52d=>0x34)
}
LX_PE_NRD_TNR1_DETAIL_T;

/**
 *	pe temporal noise reduction control parameter type
 *	ver.2, for H13Bx
 */
typedef struct {
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 auto_mode_en;					///< auto nr mode en, on(1),off(0)
	UINT8 adjust_nt_lvl;				///< dbg_ctrl. adjust nt_lvl enable
	UINT8 adjust_nt_lvl_val;			///< dbg_ctrl. adjust nt_lvl value (8u, "this-128" will be added to calculated nt_lvl),bypass 0x80
	UINT8 y_gain;						///< 0x00 ~ 0xfe = strongest ~ weakest,0x20 := normal operation,0xff = special case. luma-tnr off (alphay=1.0)
	UINT8 c_gain;						///< 0x00 ~ 0xfe = strongest ~ weakest,0x20 := normal operation,0xff = special case. chroma-tnr off (alphac=1.0)
}LX_PE_NRD_TNR2_CMN_T;

/**
 *	pe temporal noise reduction detailed control parameter type
 *	ver.2, for H13Bx
 */
typedef struct {
	LX_PE_WIN_ID win_id;		///< window id
	/*ma: motion 16*/
	UINT8 m_coring_en_c;				///< gain accordint to result of ma, mc blending 
	UINT8 m_coring_en_y;				///< motion coring enable y
	UINT8 m_gain_c;						///< motion gain c: 2.2u
	UINT8 m_gain_y;						///< max = 3.9999
	UINT8 m_coring_th;					///< m_coring_th
	UINT8 m_offset_mode_en;				///< 0 := motion gain mode,1 = motion offset mode
	UINT8 m_gain_en_var;				///< motion gain enable by variance
	UINT8 a_gain_en_var;				///< alpha gain enable by variance
	UINT8 wa_y0;						///< variance-adaptive motion/alpha gain : 0.8u
	UINT8 wa_y1;						///< variance-adaptive motion/alpha gain : 0.8u
	UINT8 wa_y2;						///< variance-adaptive motion/alpha gain : 0.8u
	UINT8 wa_y3;						///< variance-adaptive motion/alpha gain : 0.8u
	UINT8 wa_x0;						///< spatial variance threshold 0
	UINT8 wa_x1;						///< spatial variance threshold 1
	UINT8 wa_x2;						///< spatial variance threshold 2
	UINT8 wa_x3;						///< spatial variance threshold 3
	/*ma: alpha gain 8*/
	UINT8 luma_gain_p0_x;				///< luma_gain_p0_x
	UINT8 luma_gain_p1_x;				///< luma_gain_p1_x
	UINT8 luma_gain_p2_x;				///< luma_gain_p2_x
	UINT8 luma_gain_p3_x;				///< luma_gain_p3_x
	UINT8 luma_gain_p0_y;				///< luma_gain_p0_y
	UINT8 luma_gain_p1_y;				///< luma_gain_p1_y
	UINT8 luma_gain_p2_y;				///< luma_gain_p2_y
	UINT8 luma_gain_p3_y;				///< luma_gain_p3_y
	/*ma: alhpa remapping 19*/
	UINT8 alpha_avg_en;					///< alpha spatial avg enable
	UINT8 alpha_mapping_y_en;			///< alpha mapping for y enable
	UINT8 alpha_mapping_c_en;			///< alpha mapping for c enable
	UINT8 alpha_mapping_y_x0;			///< alpha_mapping_y_x0
	UINT8 alpha_mapping_y_x1;			///< alpha_mapping_y_x1
	UINT8 alpha_mapping_y_x2;			///< alpha_mapping_y_x2
	UINT8 alpha_mapping_y_x3;			///< alpha_mapping_y_x3
	UINT8 alpha_mapping_y_y0;			///< alpha_mapping_y_y0
	UINT8 alpha_mapping_y_y1;			///< alpha_mapping_y_y1
	UINT8 alpha_mapping_y_y2;			///< alpha_mapping_y_y2
	UINT8 alpha_mapping_y_y3;			///< alpha_mapping_y_y3
	UINT8 alpha_mapping_c_x0;			///< alpha_mapping_c_x0
	UINT8 alpha_mapping_c_x1;			///< alpha_mapping_c_x1
	UINT8 alpha_mapping_c_x2;			///< alpha_mapping_c_x2
	UINT8 alpha_mapping_c_x3;			///< alpha_mapping_c_x3
	UINT8 alpha_mapping_c_y0;			///< alpha_mapping_c_y0
	UINT8 alpha_mapping_c_y1;			///< alpha_mapping_c_y1
	UINT8 alpha_mapping_c_y2;			///< alpha_mapping_c_y2
	UINT8 alpha_mapping_c_y3;			///< alpha_mapping_c_y3
	/*ma: noise level adjust gain 54*/
	UINT8 nt_lvl_adjust_gm_enable;		///< noise level adjust (by the global motion amount) enable
	UINT8 nt_lvl_adjust_lpct_enable;	///< noise level adjust (by the percent of smooth area) enable
	UINT8 nt_lvl_adjust_avg_ts_enable;	///< (by the (avg_t - avg_s))  enable,avg_t : frame average of temporal difference,avg_s : frame average of spatial variance
	UINT8 nt_lvl_adjust_lpct_sel;		///< 0 := the percent of smooth area in a picture
	UINT8 nt_lvl_gain_gm_x0;			///< nt_lvl_gain_gm_x0
	UINT8 nt_lvl_gain_gm_x1;			///< nt_lvl_gain_gm_x1
	UINT8 nt_lvl_gain_gm_x2;			///< nt_lvl_gain_gm_x2
	UINT8 nt_lvl_gain_gm_x3;			///< nt_lvl_gain_gm_x3
	UINT8 nt_lvl_gain_gm_y0;			///< nt_lvl_gain_gm_y0
	UINT8 nt_lvl_gain_gm_y1;			///< nt_lvl_gain_gm_y1
	UINT8 nt_lvl_gain_gm_y2;			///< nt_lvl_gain_gm_y2
	UINT8 nt_lvl_gain_gm_y3;			///< nt_lvl_gain_gm_y3
	UINT8 nt_lvl_gain_st_x0;			///< nt_lvl_gain_st_x0
	UINT8 nt_lvl_gain_st_x1;			///< nt_lvl_gain_st_x1
	UINT8 nt_lvl_gain_st_x2;			///< nt_lvl_gain_st_x2
	UINT8 nt_lvl_gain_st_x3;			///< nt_lvl_gain_st_x3
	UINT8 nt_lvl_gain_st_y0;			///< nt_lvl_gain_st_y0
	UINT8 nt_lvl_gain_st_y1;			///< nt_lvl_gain_st_y1
	UINT8 nt_lvl_gain_st_y2;			///< nt_lvl_gain_st_y2
	UINT8 nt_lvl_gain_st_y3;			///< nt_lvl_gain_st_y3
	UINT8 nt_lvl_gain_lpct_x0;			///< nt_lvl_gain_lpct_x0
	UINT8 nt_lvl_gain_lpct_x1;			///< nt_lvl_gain_lpct_x1
	UINT8 nt_lvl_gain_lpct_x2;			///< nt_lvl_gain_lpct_x2
	UINT8 nt_lvl_gain_lpct_x3;			///< nt_lvl_gain_lpct_x3
	UINT8 nt_lvl_gain_lpct_y0;			///< nt_lvl_gain_lpct_y0
	UINT8 nt_lvl_gain_lpct_y1;			///< nt_lvl_gain_lpct_y1
	UINT8 nt_lvl_gain_lpct_y2;			///< nt_lvl_gain_lpct_y2
	UINT8 nt_lvl_gain_lpct_y3;			///< nt_lvl_gain_lpct_y3
	/* map*/
	UINT8 m_gain_en_var2;				///< motion gain enable by variance. this motion goes to motion-adaptive spatial blur
	UINT8 m_gain_ctrl2_x0;				///< m_gain_ctrl2_x0
	UINT8 m_gain_ctrl2_x1;				///< m_gain_ctrl2_x1
	UINT8 m_gain_ctrl2_y0;				///< m_gain_ctrl2_y0
	UINT8 m_gain_ctrl2_y1;				///< m_gain_ctrl2_y1
	UINT8 sf_map_flt_en;				///< spatial var. map filtering enable,spatial variance filtering,spatial variance adaptive
	UINT8 sf_map_tap;					///< "01" : 7-tap 7x3,"10" : 5-tap  5x3,"11" : 3-tap  3x3
	UINT8 sf_map_gain;					///< spatial var. map gain(3.3u)
	UINT8 sf_th0;						///< spatial var-to-filter gain 
	UINT8 sf_th1;						///< lager than th0, smaller than th1, 3-tap recommand
	UINT8 sf_th2;						///< th2 5-tap
	UINT8 sf_th3;						///< th3 7-tap
	UINT8 sf_th4;						///< th4 9-tap
	UINT8 sf_mb_x0;						///< x0 x motion
	UINT8 sf_mb_x1;						///< sf_mb_x1
	UINT8 sf_mb_x2;						///< sf_mb_x2
	UINT8 sf_mb_x3;						///< sf_mb_x3
	UINT8 sf_mb_y0;						///< y0  y gain : bigger gain cause blurer
	UINT8 sf_mb_y1;						///< sf_mb_y1
	UINT8 sf_mb_y2;						///< sf_mb_y2
	UINT8 sf_mb_y3;						///< sf_mb_y3
	/* bluring gain */
	UINT8 sf_gain_mode;					///< 0' : disable gain control,'1' : enable gain control,master gain
	UINT8 sf_gain;						///< sf gain(0.4u)
	UINT8 sf_blend_en_y;				///< motion-adaptive blending enable of blurred data and bypass data: y
	UINT8 sf_blend_en_c;				///< motion-adaptive blending enable of blurred data and bypass data: c
	UINT8 sf_blend_motion_exp_mode;		///< 0:= no expand,1 = 11-tap expand,2 = 9-tap expand,3 = 5-tap expand
	/*mc*/
	UINT8 sad_sel_pels;					///< 0 := sad_ma,1 = alpha_blend(sad_mc, sad_ma)
	UINT8 sad_mamc_blend;				///< 0xff -> sad of mc,0x00 -> sad of ma
	UINT8 mamc_blend_sel;				///< 0:= spatial variance, 1 = motion vector consistency
	UINT8 mamc_blend_x0;				///< spatial variance threshold
	UINT8 mamc_blend_x1;				///< mamc_blend_x1
	UINT8 mamc_blend_y0;				///< 0xff: mc filter, 0x00: ma filter
	UINT8 mamc_blend_y1;				///< mamc_blend_y1
	/*me*/
	UINT8 hme_half_pel_en;				///< half pel search enable for motion estimation
	UINT8 mv_cost_smooth_gain;			///< 0.5u
	UINT8 mv_cost_smooth_en;			///< enable for temporal smoothness constraint for block matching cost
	UINT8 mv_cost_gmv_smooth_gain;		///< mv_cost_gmv_smooth_gain
	UINT8 mv_cost_gmv_smooth_en;		///< mv_cost_gmv_smooth_en
	UINT8 mv0_protect_th;				///< sad threshold for zero-motion vector protection
	UINT8 mv0_protect_en;				///< zero-motion vector protection enable
	UINT8 sad_protect_en;				///< sad-based zero-motion vector protection enable 
	UINT8 sad_protect_gm_en;			///< zero-motion vector protection enable by global motion
	UINT8 mv_protect_control_x0;		///< variance threshold for 0-motion vector protection
	UINT8 mv_protect_control_x1;		///< mv_protect_control_x1
	UINT8 mv_protect_control_y0;		///< sad threshold for 0-motion vector protection
	UINT8 mv_protect_control_y1;		///< mv_protect_control_y1
}LX_PE_NRD_TNR2_DETAIL_T;

/***************************************************************************/
/* DNT : Deinterlace */
/***************************************************************************/

/**
 *	pe deinterlacer, film(3:2,2:2 pull down) mode control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 enable;			///< enable film mode, 1:on, 0:off
}
LX_PE_DNT_FILMMODE_T;

/**
 *	pe deinterlacer, low delay mode control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT32 enable;			///< enable low delay mode, 1:on, 0:off
}
LX_PE_DNT_LD_MODE_T;

/***************************************************************************/
/* SHP : Sharpness */
/***************************************************************************/
/**
 *	scaler filter coefficient control parameter type
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT32 h_luma_id;			///< horizontal luma index
	UINT32 v_luma_id;			///< vertical luma index
	UINT32 h_chrm_id;			///< horizontal chroma index
	UINT32 v_chrm_id;			///< vertical chroma index
}
LX_PE_SHP_SCLFILTER_T;

/**
 *	pe resolution enhancement module normal control parameter type
 *	ver.0, for L9Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 peaking_w_gain;		///< peaking white gain
	UINT8 peaking_b_gain;		///< peaking black gain
	UINT8 detail_master_b_gain;	///< detail master black gain
	UINT8 detail_master_w_gain;	///< detail master white gain
	UINT8 detail_lap_gain;		///< detail laplacian gain
	UINT8 detail_sobel_gain;	///< detail sobel gain
	UINT8 detail_lap_w_gain;	///< detail laplacian white gain
	UINT8 detail_lap_b_gain;	///< detail laplacian black gain
}
LX_PE_SHP_RE0_CMN_T;

/**
 *	pe resolution enhancement module horizontal control parameter type
 *	ver.0, for L9Ax
 *	- dr:deringing, ti:transition improvement
 *	- cti:color transition improvement, ycm:y(luma) chroma matching
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 peaking_hor_gain;		///< peaking, horiznotal gain
	UINT8 dr_csft_gain;			///< dr, center shift gain
	UINT8 dr_edgef_w_gain;		///< dr, edge filter white gain
	UINT8 dr_edgef_b_gain;		///< dr, edge filter black gain
	UINT8 ti_hpre_ygain;		///< ti, horizontal y gain(pre)
	UINT8 ti_hpre_cgain;		///< ti, horizontal c gain(pre)
	UINT8 ti_hpost_ygain;		///< ti, horizontal y gain(post)
	UINT8 ti_hpost_cgain;		///< ti, horizontal c gain(post)
	UINT8 cti_tap_size;			///< cti, tap size
	UINT8 cti_gain;				///< cti, gain
	UINT8 cti_ycm_band_sel;		///< cti, ycm band selection
	UINT8 cti_ycm_diff_th;		///< cti, ycm diff threshold
	UINT8 cti_ycm_y_gain;		///< cti, ycm y gain
	UINT8 cti_ycm_c_gain;		///< cti, ycm c gain
}
LX_PE_SHP_RE0_HOR_T;

/**
 *	pe resolution enhancement module vertical control parameter type
 *	ver.0, for L9Ax
 *	- dr:deringing, ti:transition improvement
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 dr_vbif_th;			///< dr, vertical bilateral filter threshold
	UINT8 peaking_ver_gain;		///< peaking, vertical gain
    UINT8 ti_v_gain;			///< ti, vertical gain(pre)
}
LX_PE_SHP_RE0_VER_T;

/**
 *	pe resolution enhancement module edge control parameter type
 *	ver.0, for L9Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 sharp_intensity;		///< sharp intensity, 0(low), 1(high)
	UINT8 edge_intensity;		///< edge intensity, 0(low) ~ 2(high)
}
LX_PE_SHP_EE0_T;

/**
 *	pe resolution enhancement(RE) normal control(ver.1) parameter type
 *	ver.1, for L9Bx,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 mp_white_gain;	///< white gain
	UINT8 mp_black_gain;	///< black gain
	UINT8 sp_white_gain;	///< white gain
	UINT8 sp_black_gain;	///< black gain
	/* cti */
	UINT8 cti_en;			///< cti enable
	UINT8 tap_size;			///< "000" 21 ta
	UINT8 cti_gain;			///< gain (3.5u)
	UINT8 ycm_y_gain;		///< ycm_y_gain
	UINT8 ycm_c_gain;		///< ycm_c_gain
}
LX_PE_SHP_RE1_CMN_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.1, for L9Bx,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	UINT8 edge_y_filter_en;			///< edge_Y_filter_en
	UINT8 reg_csft_gain;			///< reg_csft_gain: center shift gain(1.5u)
	UINT8 edge_filter_white_gain;	///< edge filter white gain
	UINT8 edge_filter_black_gain;	///< edge filter black gain
	UINT8 a_gen_width;				///< a_gen_widt
	UINT8 mp_horizontal_gain;		///< horizontal gain(3.5u)
	UINT8 sp_horizontal_gain;		///< horizontal gain(3.5u)
}
LX_PE_SHP_RE1_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.1, for L9Bx,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 der_v_en;			///< der-v enable
	UINT8 bif_manual_th;	///< bilateral filter threshold
	UINT8 csft_gain;		///< center-shift gain (1.5u)
	UINT8 gain_b;			///< gain(b) : 2.5u
	UINT8 gain_w;			///< gain(w): 2.5u
	UINT8 der_gain_mapping;	///< weight selection for weighted average of bif and inpu
	UINT8 mmd_sel;			///< a-gen. siz
	UINT8 mp_vertical_gain;	///< vertical gain(3.5u)
	UINT8 sp_vertical_gain;	///< vertical gain(3.5u)
}
LX_PE_SHP_RE1_VER_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.1, for L9Bx,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	/* e-map */
	UINT8 amap2_sel;			///< A-map generation
	UINT8 ga_max;				///< A to Edge weight control
	UINT8 ga_th0;				///< th0
	UINT8 ga_th1;				///< th1
	/* t-map */
	UINT8 amap1_sel;			///< A-map generatio for texture enahcer
	UINT8 max_sel;				///< A-map expansion for texture-enhance
	UINT8 tmap_gain;			///< T-to-texture weight
	UINT8 gt_th0;				///< th0
	UINT8 gt_th0a;				///< th0a
	UINT8 gt_th0b;				///< th0b
	UINT8 gt_th1;				///< th1
	UINT8 gt_gain0a;			///< gain(th0a) : 1.5u
	UINT8 gt_gain0b;			///< gain(th0b) : 1.5u
	UINT8 gt_max;				///< gain(th1) :1.5u
	UINT8 coring_mode1;			///< t-map(H/V) coring mode
	UINT16 var_th;				///< flat region rejection threshold,11bit
	/* d-jag */
	UINT8 center_blur_en;		///< center-pixel averaging for edge-direction calculatio
	UINT8 level_th;				///< g0: level threshold
	UINT8 protect_th;			///< G1: protect threshold
	UINT8 n_avg_gain;			///< neighborhood pixel averaing : gain
}
LX_PE_SHP_RE1_MISC_T;

/**
 *	pe edge enhancement(EE) control parameter type
 *	ver.1, for L9Bx,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;	///< window id
	UINT8 mp_edge_gain_b;	///< MP: edge gain(b) : 2.5u
	UINT8 mp_edge_gain_w;	///< MP: edge gain(w)
	UINT8 sp_edge_gain_b;	///< SP: edge gain(b) : 2.5u
	UINT8 sp_edge_gain_w;	///< SP: edge gain(w)
}
LX_PE_SHP_EE1_T;

/**
 *	pe detail enhancement(DE) control parameter type
 *	ver.1, for L9Bx,H13Ax
 */
typedef struct
{
	LX_PE_WIN_ID win_id;		///< window id
	UINT8 mp_texture_gain_b;	///< MP: texture gain(b)
	UINT8 mp_texture_gain_w;	///< MP: texture gain(w) 
	UINT8 sp_texture_gain_b;	///< SP: texture gain(b)
	UINT8 sp_texture_gain_w;	///< SP: texture gain(w) 
}
LX_PE_SHP_DE1_T;

/**
 *	pe resolution enhancement(RE) normal control(ver.2) parameter type
 *	ver.2, for H13Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 mp_white_gain;				///< white gain
	UINT8 mp_black_gain;				///< black gain
	UINT8 sp_white_gain;				///< white gain
	UINT8 sp_black_gain;				///< black gain
	//UINT8 flat_gain;					///< gain
	/* cti */
	UINT8 tap_size;						///< "000" 21 tap,"001" 19 tap,"010" 17 tap,"011" 15 tap,"100" 13 tap,"101" 11 tap,"110"  9 tap
	UINT8 cti_gain;						///< gain (3.5u)
	UINT8 ycm_y_gain;					///< ycm_y_gain
	UINT8 ycm_c_gain;					///< ycm_c_gain
}
LX_PE_SHP_RE2_CMN_T;

/**
 *	pe resolution enhancement(RE) horizontal control(ver.1) parameter type
 *	ver.2, for H13Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 reg_csft_gain;				///< reg_csft_gain: center shift gain(1.5u)
	UINT8 edge_filter_white_gain;		///< edge filter white gain upper 2bit: int, lower 4 bit: float, max: 63(dec) 3.9999
	UINT8 edge_filter_black_gain;		///< edge filter black gain 
	UINT8 a_gen_width;					///< width size for dynamic range
	UINT8 mp_horizontal_gain;			///< horizontal gain(3.5u)
	UINT8 sp_horizontal_gain;			///< horizontal gain(3.5u)
	UINT8 e_gain_th1;					///< a to edge gain: th1
	UINT8 e_gain_th2;					///< a to edge gain: th2
	UINT8 f_gain_th1;					///< a to flat gain: th1
	UINT8 f_gain_th2;					///< a to flat gain: th2
	UINT8 coring_th;					///< coring_th
	UINT8 y_gain;						///< y_gain
	UINT8 c_gain;						///< c_gain
}
LX_PE_SHP_RE2_HOR_T;

/**
 *	pe resolution enhancement(RE) vertical control(ver.1) parameter type
 *	ver.2, for H13Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	UINT8 bif_manual_th;				///< bilateral filter threshold
	UINT8 csft_gain;					///< center-shift gain (1.5u)
	UINT8 gain_b;						///< gain(b) : 2.5u
	UINT8 gain_w;						///< gain(w): 2.5u
	UINT8 mmd_sel;						///< "000" : 11 tap,"001" : 9-tap,"010" : 7-tap,"011" : 5-tap,"100" : 3-tap ,o.w   : 11-tap
	UINT8 mp_vertical_gain;				///< vertical gain(3.5u)
	UINT8 sp_vertical_gain;				///< vertical gain(3.5u)
	UINT8 gain_th1;						///< a-to-weight: th1
	UINT8 gain_th2;						///< a-to-weight: th2
}
LX_PE_SHP_RE2_VER_T;

/**
 *	pe resolution enhancement(RE) misc. control parameter type
 *	ver.2, for H13Bx
 */
typedef struct
{
	LX_PE_WIN_ID win_id;				///< window id
	/* cti */
	UINT8 cti_en;						///< cti enable
	UINT8 coring_th0;					///< th with coring th0 mmd
	UINT8 coring_th1;					///< coring_th1
	UINT8 coring_map_filter;			///< "000" : no ,"001" : 5-tap ,"010" : 7-tap ,"011" : 9-tap ,100: : 11-tap ,"101" : 13-tap 
	UINT8 coring_tap_size;				///< "000" 21 tap,"001" 19 tap,"010" 17 tap,"011" 15 tap,"100" 13 tap,"101" 11 tap,"110"  9 tap
	UINT8 ycm_en1;						///< y c miss matching.
	UINT8 ycm_band_sel;					///< ycm_band_sel
	UINT8 ycm_diff_th;					///< ycm_diff_th
	/* h */
	UINT8 edge_y_filter_en;				///< edge_y_filter_en
	UINT8 e_gain_max;					///< a to edge weight: gain
	UINT8 f_gain_max;					///< a to flat weight: gain
	UINT8 mp_lap_h_mode;				///< "000" : h3,"001" : h4,"010" : h5,"011" : h6,"100" : h7
	UINT8 sp_lap_h_mode;				///< "00" : h3,"01" : h5,"10" : h7,"11" : not used
	/* v */
	UINT8 der_v_en;						///< der-v enable
	UINT8 der_gain_mapping;				///< "00" : a-to weight,"01" : a-map,"10  : a-to weight,"11" : a-map
	UINT8 max_sel;						///< ,"000" : do not expand,"001" : 3-tap,"010" : 5-tap,"011" : 7-tap,"100" : 9-tap,"101" : 11-tap,o.w   : do not expand
	UINT8 mp_lap_v_mode;				///< laplacian v mode,"000" : v3,"001" : v4,"010" : v5,"011" : v6,"100" : v7
	UINT8 sp_lap_v_mode;				///< 0' : v3,'1' : v5
	/* cmm */
	UINT8 mp_sobel_weight;				///< weight for sobel operator output
	UINT8 mp_laplacian_weight;			///< weight for laplacian operator output
	UINT8 sp_sobel_weight;				///< weight for sobel operator output
	UINT8 sp_laplacian_weight;			///< weight for laplacian operator output	
	UINT8 flat_en;						///< flat-filter enable
	UINT8 flat_filter_type;				///< '0' : bi-lateral filter,'1': average filter	
	/*d_jag*/
	UINT8 edf_en;						///< edge-directional de-jagging enable
	UINT8 center_blur_en;				///< '0' : use original pixel,'1' : use avg. pixel
	UINT8 count_diff_th;				///< matchness threshod for edge-direction decision
	UINT8 n_avg_mode;					///< mode for dual edges,'0' : use 12 direction results,'1' : use 36 direction results
	UINT8 line_variation_diff_th;		///< line-variation threshold for edge-direction decision
	UINT8 level_th;						///< g0: level threshold
	UINT8 protect_th;					///< g1: protect threshold
	UINT8 n_avg_gain;					///< neighborhood pixel averaing : gain
	UINT8 edf_count_min;				///< g0 : edf_count_min
	UINT8 edf_count_max;				///< g0 : edf_count_max
	UINT8 dj_h_count_min;				///< g0 : dj_h_count_min
	UINT8 dj_h_count_max;				///< g0 : dj_h_count_max
	UINT8 dj_v_count_min;				///< g0 : dj_v_count_min
	UINT8 dj_v_count_max;				///< g0 : dj_v_count_max
	/*e_map*/
	UINT8 amap2_sel;					///< "00" : 5-tap,"01" : 7-tap,"10" : 9-tap,"11" : 15-tap
	UINT8 amap_gain;					///< edge-map gain
	UINT8 ga_max;						///< <a to edge weight control>
	UINT8 ga_th0;						///< th0
	UINT8 ga_th1;						///< th1
	/*t_map*/
	UINT8 amap1_sel;					///< "00" : 15-tap,"01" : 9-tap,"10" : 7-tap,"11" : 5-tap
	UINT8 tmap_max_sel;						///< "000" : bypass,"001" : 5-tap,"010" : 7-tap,"011" : 9-tap,"100" : 11-tap,"101" : 13-tap,"110" : 15-tap,"111" : 17-tap
	UINT8 avg_sel;						///< "00" : bypass,"01" : 3x1 average [1 2 1],"10" : 5x1 average [1 2 2 2 1 ],"11" : bypass
	UINT8 tmap_gain;					///< texture-map gain(2.5u)
	UINT8 gt_th0;						///< th0
	UINT8 gt_th0a;						///< th0a
	UINT8 gt_th0b;						///< th0b
	UINT8 gt_th1;						///< th1
	UINT8 gt_gain0a;					///< gain(th0a) : 1.5u
	UINT8 gt_gain0b;					///< gain(th0b) : 1.5u
	UINT8 gt_max;						///< gain(th1) :1.5u
	UINT8 a2tw_en;						///< strong edge protection ,'0': disable,'1': enable
	UINT8 a2tw_th0;						///< strong edge: th0
	UINT8 a2tw_th1;						///< strong edge: th1
	UINT8 exp_mode;						///< "00" : bypass,"01" : 3-tap expansion,"10" : 5-tap expansion,"11" : bypass
	UINT8 coring_mode1;					///< coring mode "00" : remove 0,"01" : remove 0/1,"10" : remove 0/1/2,"11" : remove 0/1/2/3
	UINT8 coring_mode2;					///< coring mode,"00" : remove 0,"01" : remove 0/1,"10" : remove 0/1/2,"11" : remove 0/1/2/3
	UINT8 g_th0;						///< <edge/texture blending> th0
	UINT8 g_th1;						///< th1
	UINT16 var_th;						///< flat region rejection threshold if variance < var_th, reject the region
	/*ti-h*/
	UINT8 enable;					///< ti-h enable
	UINT8 coring_step;					///< n : 2^n (transition width)
	UINT8 gain0_en;						///< gain0 enable
	UINT8 gain1_en;						///< gain1 enable
	UINT8 gain0_th0;					///< gain0_th0
	UINT8 gain1_th1;					///< gain1_th1
	UINT8 gain1_div_mode;				///< gain1: div mode,"00" : div by 32,"01" : div by 16,"10" : div by 8,"11" : div by 64
}
LX_PE_SHP_RE2_MISC_T;

/***************************************************************************/
/* ETC : misc. */
/***************************************************************************/
/**
 *	pe misc. debug parameter type
 */
typedef struct
{
	UINT32 func_num;			///< func number(depending on chip version)
	UINT32 size;				///< the number of data
	UINT32 *data;				///< user data
}
LX_PE_ETC_DBG_T;

/***************************************************************************/
/* ETC : info. */
/***************************************************************************/
/**
 *	pe operation mode
 */
typedef struct
{
	UINT32 is_tp        : 1;	///< 0, test pattern mode, 1:yes,0:no
	UINT32 is_venc      : 1;	///< 1, video encoder mode, 1:yes,0:no
	UINT32 is_adpt_st   : 1;	///< 2, adaptive stream mode, 1:yes,0:no
	UINT32 is_ext_frc   : 1;	///< 3, external frc mode, 1:yes,0:no
	UINT32 is_wb_wog    : 1;	///< 4, wb without degamma,gamma, 1:yes,0:no(with)
	UINT32 is_reverse   : 1;	///< 5, reverse mode, 1:yes,0:no(default)
}
LX_PE_INF_OP_MODE_T;

/**
 *	pe display info.
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	LX_PE_SRC_TYPE src_type;		///< pe source type
	LX_PE_FMT_TYPE fmt_type;		///< pe format type
	LX_PE_OUT_TYPE out_type;		///< pe out type
	LX_PE_FR_TYPE fr_type;			///< pe frame rate type
	UINT32 in_f_rate;				///< input frame rate(x10 hz)
	UINT32 in_h_size;				///< input horizontal active size
	UINT32 in_v_size;				///< input vertical active size
	LX_PE_SCAN_TYPE scan_type;		///< pe scan type
	LX_PE_DTV_TYPE dtv_type;		///< pe dtv play type
	LX_PE_HDD_SRC_TYPE hdd_type;	///< hdd src type
	LX_PE_3D_IN_TYPE in_type;		///< 3d input type
	LX_PE_INF_OP_MODE_T mode;		///< operation mode
}
LX_PE_INF_DISPLAY_T;

/**
 *	pe level info.
 */
typedef struct
{
	LX_PE_WIN_ID win_id;			///< window id
	LX_PE_LEVEL_TYPE sel;			///< pe level select. see LX_PE_LEVEL_TYPE
	UINT32 noise_level;				///< pe tnr noise level
	UINT32 peakpos_level;			///< pe tnr peak pos level
	UINT32 motion_level;			///< pe motion level
}
LX_PE_INF_LEVEL_T;


/***************************************************************************/
/* ETC : detection 3d */
/***************************************************************************/

/**
 *	pe d3d frame capture info type
 */
typedef struct {
	LX_PE_D3D_CAP cap_enb;
	UINT32 h_line_num;
	UINT32 v_line_num;
	UINT32 h_line_width;
	UINT32 v_line_width;
} LX_PE_D3D_CAP_INFO_T;

/**
 *	pe d3d setting control parameter type
 */
typedef struct
{
	LX_PE_D3D_DEC enb;
	UINT32 sel_alg;
	LX_PE_D3D_CAP_INFO_T cap_info;
	LX_PE_D3D_FORMAT fmt;
	UINT16 *sbs_disparity;
	UINT16 *tnb_disparity;
} LX_PE_D3D_SETTINGS_T;

/**
 *	pe d3d information control parameter type
 */
typedef struct
{
	BOOLEAN valid;
	LX_PE_D3D_FORMAT d3d_inf;
} LX_PE_D3D_INFO_T;

/**
 *	pe dual screen information control parameter type
 */
typedef struct
{
	LX_PE_D3D_DSC dsc_type;
} LX_PE_D3D_DSC_INFO_T;

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_KAPI_H_ */
