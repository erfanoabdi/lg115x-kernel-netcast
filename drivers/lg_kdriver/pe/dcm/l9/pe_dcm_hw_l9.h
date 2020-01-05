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


/** @file pe_dcm_hw_l9.h
 *
 *  driver header for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_DCM_HW_L9_H_
#define	_PE_DCM_HW_L9_H_

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
 *	pe histogram information parameter type
 */
typedef struct
{
	UINT32 bin_num;				///< bin number 16 or 32
    UINT32 histogram[64];		///< histogram data of luma
    UINT32 status[5];			///< histogram status
    UINT32 sat_status;			///< saturation status
}
PE_DCM_HW_L9_HISTO_T;
/**
 *	pe dyn cont module settings type
 */
typedef struct
{
	LX_PE_DCM_DCE_CONF_T conf[LX_PE_WIN_NUM];		///< dcm config
	PE_DCM_HW_L9_HISTO_T histo_info[LX_PE_WIN_NUM];	///< histogram info
	UINT32 dse_lut[LX_PE_WIN_NUM][32];				///< dse lut
}
PE_DCM_HW_L9_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_DCM_HW_L9_SetDbgPrint(UINT32 on_off);
int PE_DCM_HW_L9_Init(void);
int PE_DCM_HW_L9_GetHistogramInfo(LX_PE_DCM_HISTO_INFO_T *pstParams);
int PE_DCM_HW_L9_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
int PE_DCM_HW_L9_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
int PE_DCM_HW_L9_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_HW_L9_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_HW_L9_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
int PE_DCM_HW_L9_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
int PE_DCM_HW_L9_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
int PE_DCM_HW_L9_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
int PE_DCM_HW_L9_GetDceAllHistogram(PE_DCM_HW_L9_HISTO_T *pstMainParams,\
	PE_DCM_HW_L9_HISTO_T *pstSubParams,UINT32 *validL,UINT32 *validR);
int PE_DCM_HW_L9_GetCurDcmSettings(PE_DCM_HW_L9_SETTINGS_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DCM_HW_L9_H_ */
