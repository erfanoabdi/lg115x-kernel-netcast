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


/** @file pe_ccm_hw_l9.h
 *
 *  driver header for picture enhance color correction module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CCM_HW_L9_H_
#define	_PE_CCM_HW_L9_H_

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

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_CCM_HW_L9_SetDbgPrint(UINT32 on_off);
int PE_CCM_HW_L9_Init(void);
int PE_CCM_HW_L9_SetDebugBypassSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CCM_HW_L9_SetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams);
int PE_CCM_HW_L9_GetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams);
int PE_CCM_HW_L9_SetAutoCrGain(PE_TSK_L9_CFG_T *pCfg);
int PE_CCM_HW_L9_SetGammaLutByDdr(LX_PE_CCM_GAMMALUT_T *pstParams);
int PE_CCM_HW_L9_SetAllGammaLutByDdr(LX_PE_CCM_GAMMALUT_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CCM_HW_L9_H_ */
