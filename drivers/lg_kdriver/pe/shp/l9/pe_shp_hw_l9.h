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


/** @file pe_shp_hw_l9.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_SHP_HW_L9_H_
#define	_PE_SHP_HW_L9_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe shp resolution enhance fmt
 */
typedef enum
{
	PE_SHP_L9_RES_3D = 0,			///< 3d
	PE_SHP_L9_RES_ATV_NTSC,			///< atv ntsc
	PE_SHP_L9_RES_ATV_PAL,			///< atv pal,secam
	PE_SHP_L9_RES_AV_NTSC,			///< av ntsc
	PE_SHP_L9_RES_AV_SCARTRGB,		///< av scart rgb
	PE_SHP_L9_RES_AV_PAL,			///< av pal,secam
	PE_SHP_L9_RES_PC,				///< pc
	PE_SHP_L9_RES_DTV_SD,			///< dtv sd
	PE_SHP_L9_RES_DTV_HD,			///< dtv hd
	PE_SHP_L9_RES_COMP_SD,			///< comp sd
	PE_SHP_L9_RES_COMP_HD,			///< comp hd
	PE_SHP_L9_RES_HDMI_SD,			///< hdmi sd
	PE_SHP_L9_RES_HDMI_HD,			///< hdmi hd
	PE_SHP_L9_RES_NUM,				///< max num
}
PE_SHP_HW_L9_RES_FMT;

/**
 *	pe shp v filter c fmt
 */
typedef enum
{
	PE_SHP_L9_VFC_RF_SD = 0,		///< rf sd
	PE_SHP_L9_VFC_AV_SECAM,			///< av secam
	PE_SHP_L9_VFC_AV_SD,			///< av,sd
	PE_SHP_L9_VFC_PC,				///< pc
	PE_SHP_L9_VFC_HDMI_SD,			///< hdmi sd
	PE_SHP_L9_VFC_HD,				///< hd
	PE_SHP_L9_VFC_NUM,				///< max num
}
PE_SHP_HW_L9_VFC_FMT;

/**
 *	scaler fir filter type enumeration
 */
typedef enum
{
	PE_SHP_HW_L9_FIR_BILINEAR = 0,	///< bilinear filter
	PE_SHP_HW_L9_FIR_POLYPHASE,		///< polyphase filter
	PE_SHP_HW_L9_FIR_NUM			///< max num
}
PE_SHP_HW_L9_FIR;

/**
 *	scaler filter tap type enumeration
 */
typedef enum
{
	PE_SHP_HW_L9_SCL_12TAP = 0,		///< 12 tap filter
	PE_SHP_HW_L9_SCL_06TAP_NORMAL,	///< 6 tap filter, normal case
	PE_SHP_HW_L9_SCL_06TAP_HALF,	///< 6 tap filter, half case
	PE_SHP_HW_L9_SCL_06TAP_DOWN75,	///< 6 tap filter, 75% down scaling case
	PE_SHP_HW_L9_SCL_06TAP_DOWN50,	///< 6 tap filter, 50% down scaling case
	PE_SHP_HW_L9_SCL_06TAP_DOWN25,	///< 6 tap filter, 25% down scaling case
	PE_SHP_HW_L9_SCL_NUM			///< max num
}
PE_SHP_HW_L9_SCL;

/**
 *	pe sharpness module settings type
 */
typedef struct
{
	LX_PE_SHP_SCLFILTER_T scl_idx[LX_PE_WIN_NUM];	///< scaler filter index
	PE_SHP_HW_L9_SCL h_y_tap[LX_PE_WIN_NUM];		///< scaler filter horizontal luma tap type
	PE_SHP_HW_L9_SCL h_c_tap[LX_PE_WIN_NUM];		///< scaler filter horizontal chroma tap type
	PE_SHP_HW_L9_SCL v_y_tap[LX_PE_WIN_NUM];		///< scaler filter vertical luma tap type
	PE_SHP_HW_L9_SCL v_c_tap[LX_PE_WIN_NUM];		///< scaler filter vertical chroma tap type
	PE_SHP_HW_L9_FIR y_fir[LX_PE_WIN_NUM];			///< fir type, luma
	PE_SHP_HW_L9_FIR c_fir[LX_PE_WIN_NUM];			///< fir type, chroma
}
PE_SHP_HW_L9_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_SHP_HW_L9_SetDbgPrint(UINT32 on_off);
int PE_SHP_HW_L9_Init(void);
int PE_SHP_HW_L9_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_SHP_HW_L9_SetReEnableCtrl(PE_TSK_L9_CFG_T *pCfg);
int PE_SHP_HW_L9_SetScalerFilterCoeff(LX_PE_SHP_SCLFILTER_T *pstParams);
int PE_SHP_HW_L9_GetCurShpSettings(PE_SHP_HW_L9_SETTINGS_T *pstParams);
int PE_SHP_HW_L9_SetScalerFilterCtrl(PE_TSK_L9_CFG_T *pCfg);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_SHP_HW_L9_H_ */
