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


/** @file pe_cmn_hw_h13.h
 *
 *  driver header for picture enhance common functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CMN_HW_H13_H_
#define	_PE_CMN_HW_H13_H_

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
 *	pe cmn operation mode type
 */
typedef struct{
	UINT32 pe1_mode_ud;		///< pe1 ud mode, 1:yes,0:no
	UINT32 pe1_mode_3d;		///< pe1 3d mode, 1:yes,0:no
}
PE_CMN_HW_H13_OPR_MODE_T;
/**
 *	pe common settings type
 */
typedef struct
{
	PE_CMN_HW_H13_OPR_MODE_T opr_inf;	///< operation info
}
PE_CMN_HW_H13_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_CMN_HW_H13_SetDbgPrint(UINT32 on_off);
int PE_CMN_HW_H13_Init(void);
int PE_CMN_HW_H13_SetOperationMode(PE_TSK_H13_CFG_T *pCfg);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMN_HW_H13_H_ */
