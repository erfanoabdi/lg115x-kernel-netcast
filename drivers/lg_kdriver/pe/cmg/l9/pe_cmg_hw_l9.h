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


/** @file pe_cmg_hw_l9.h
 *
 *  driver header for picture enhance color management. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.15
 *	@see		
 */

#ifndef	_PE_CMG_HW_L9_H_
#define	_PE_CMG_HW_L9_H_

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
void PE_CMG_HW_L9_SetDbgPrint(UINT32 on_off);
int PE_CMG_HW_L9_Init(void);
int PE_CMG_HW_L9_SetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_HW_L9_GetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_HW_L9_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_HW_L9_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_HW_L9_SetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);
int PE_CMG_HW_L9_GetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMG_HW_L9_H_ */

