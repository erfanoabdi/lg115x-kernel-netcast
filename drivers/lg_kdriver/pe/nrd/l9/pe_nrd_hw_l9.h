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


/** @file pe_nrd_hw_l9.h
 *
 *  driver header for picture enhance noise reduction. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_NRD_HW_L9_H_
#define	_PE_NRD_HW_L9_H_

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
 *	pe nrd tnr fmt
 */
typedef enum
{
	PE_NRD_L9_TNR_ATV_SECAM = 0,	///< atv secam
	PE_NRD_L9_TNR_ATV_NT_PAL,		///< atv ntsc,pal
	PE_NRD_L9_TNR_AV_SECAM,			///< av secam
	PE_NRD_L9_TNR_AV_NT_PAL,		///< av ntsc,pal
	PE_NRD_L9_TNR_PC,				///< pc
	PE_NRD_L9_TNR_DTV_SD_60,		///< dtv sd 60
	PE_NRD_L9_TNR_DTV_SD_50,		///< dtv sd 50
	PE_NRD_L9_TNR_DTV_HD,			///< dtv hd
	PE_NRD_L9_TNR_COMP_SD,			///< comp sd
	PE_NRD_L9_TNR_COMP_HD,			///< comp hd
	PE_NRD_L9_TNR_HDMI_SD,			///< hdmi sd
	PE_NRD_L9_TNR_HDMI_HD,			///< hdmi hd
	PE_NRD_L9_TNR_NUM,				///< max num
}
PE_NRD_HW_L9_TNR_FMT;
/**
 *	pe nrd tnr color region fmt
 */
typedef enum
{
	PE_NRD_L9_CRG_ALL,				///< hd
	PE_NRD_L9_CRG_NUM,				///< max num
}
PE_NRD_HW_L9_CRG_FMT;
/**
 *	pe nrd dnr fmt
 */
typedef enum
{
	PE_NRD_L9_DNR_SD_I = 0,			///< sd interlace
	PE_NRD_L9_DNR_SD_P,				///< sd progress
	PE_NRD_L9_DNR_HD_I,				///< hd interlace
	PE_NRD_L9_DNR_HD_P,				///< hd progress
	PE_NRD_L9_DNR_COMP_SD_I,		///< comp sd interlace
	PE_NRD_L9_DNR_COMP_SD_P,		///< comp sd progress
	PE_NRD_L9_DNR_COMP_HD_I,		///< comp hd interlace
	PE_NRD_L9_DNR_COMP_HD_P,		///< comp hd progress
	PE_NRD_L9_DNR_NUM,				///< max num
}
PE_NRD_HW_L9_DNR_FMT;
/**
 *	pe nrd clc fmt
 */
typedef enum
{
	PE_NRD_L9_CLC_ATV = 0,			///< atv
	PE_NRD_L9_CLC_AV_NTSC,			///< av ntsc
	PE_NRD_L9_CLC_AV_PAL,			///< av pal, secam
	PE_NRD_L9_CLC_DTV_SD,			///< dtv sd
	PE_NRD_L9_CLC_DTV_HD,			///< dtv hd
	PE_NRD_L9_CLC_PC,				///< pc
	PE_NRD_L9_CLC_COMP_SD,			///< comp sd
	PE_NRD_L9_CLC_COMP_HD,			///< comp hd
	PE_NRD_L9_CLC_HDMI_SD,			///< hdmi sd
	PE_NRD_L9_CLC_HDMI_HD,			///< hdmi hd
	PE_NRD_L9_CLC_NUM,				///< max num
}
PE_NRD_HW_L9_CLC_FMT;
/**
 *	pe nrd v filter y fmt
 */
typedef enum
{
	PE_NRD_L9_VFY_SD = 0,			///< sd
	PE_NRD_L9_VFY_PC,				///< pc
	PE_NRD_L9_VFY_HD_I,				///< hd interlace
	PE_NRD_L9_VFY_HD_P,				///< hd progress
	PE_NRD_L9_VFY_NUM,				///< max num
}
PE_NRD_HW_L9_VFY_FMT;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_NRD_HW_L9_SetDbgPrint(UINT32 on_off);
int PE_NRD_HW_L9_Init(void);
int PE_NRD_HW_L9_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_NRD_HW_L9_SetMeasureWinCtrl(PE_TSK_L9_CFG_T *pCfg);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_NRD_HW_L9_H_ */
