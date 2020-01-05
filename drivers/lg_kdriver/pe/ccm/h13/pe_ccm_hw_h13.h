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


/** @file pe_ccm_hw_h13.h
 *
 *  driver header for picture enhance color correction module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.12
 *	@see		
 */

#ifndef	_PE_CCM_HW_H13_H_
#define	_PE_CCM_HW_H13_H_

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
/** h13b0
* #define : use pe1 gmc block(drv) for pixel replacement
* #undef  : use pe1 conversion block(f/w) for pixel replacement
*/
#undef PE_CCM_HW_H13B_USE_GMC_PXL_REP

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe ccm 3d fmt check type for auto cr gain setting
 */
typedef enum
{
	PE_CCM_HW_H13_D3D_CHK_NORMAL = 0,		///< normal
	PE_CCM_HW_H13_D3D_CHK_NOT_TB,			///< not tb(not normal)
	PE_CCM_HW_H13_D3D_CHK_NOT_SS,			///< not ss(not normal)
	PE_CCM_HW_H13_D3D_CHK_MAX				///< max num
}
PE_CCM_HW_H13_D3D_CHK;
/**
 *	pe ccm control type
 */
typedef struct
{
	UINT32 r_h_select;		///< lrcr r histo selection
	UINT32 l_h_select;		///< lrcr l histo selection
	UINT32 r_p_select;		///< lrcr r proc selection
	UINT32 l_p_select;		///< lrcr l proc selection
	UINT32 r_o_select;		///< lrcr r out selection
	UINT32 l_o_select;		///< lrcr l out selection
	UINT32 ppr_bypass;		///< lrcr r bypass
	UINT32 ppl_bypass;		///< lrcr l bypass
	UINT32 ff_mode_on;		///< lrcr ff mode enable
	UINT32 ll_mode_en;		///< lrcr line by line mode enable
	UINT32 histo_mode;		///< lrcr histo mode
	UINT32 lrcr_gain;		///< lrcr gain
}
PE_CCM_HW_H13_CTRL_T;
/**
 *	pe ccm settings type
 */
typedef struct
{
	PE_CCM_HW_H13_CTRL_T ccm_inf;	///< ccm info
}
PE_CCM_HW_H13_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_CCM_HW_H13_SetDbgPrint(UINT32 on_off);
int PE_CCM_HW_H13_Init(void);
int PE_CCM_HW_H13_SetDebugBypassSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CCM_HW_H13_SetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams);
int PE_CCM_HW_H13_GetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams);
int PE_CCM_HW_H13_SetLrcrConfig(PE_TSK_H13_CFG_T *pCfg);
int PE_CCM_HW_H13_SetAutoCrGain(PE_TSK_H13_CFG_T *pCfg);
int PE_CCM_HW_H13_GetCurCcmSettings(PE_CCM_HW_H13_SETTINGS_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CCM_HW_H13_H_ */
