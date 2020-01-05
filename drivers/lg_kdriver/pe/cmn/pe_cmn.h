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


/** @file pe_cmn.h
 *
 *  driver header for picture enhance common functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_CMN_H_
#define	_PE_CMN_H_

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
 *	pe common settings type
 */
typedef struct
{
	UINT32 use_pe_fw;								///< 0:not use, 1:use pe fw
	UINT32 dbg_print_lvl;							///< pe debug print level
	UINT32 dbg_bypass[LX_PE_WIN_NUM];				///< bypass each module
	LX_PE_DEFAULT_SETTINGS_T dflt[LX_PE_WIN_NUM];	///< default info
	LX_PE_CMN_CONTRAST_T con[LX_PE_WIN_NUM];		///< contrast
	LX_PE_CMN_BRIGHTNESS_T bri[LX_PE_WIN_NUM];		///< brightness
	LX_PE_CMN_SATURATION_T sat[LX_PE_WIN_NUM];		///< saturation
	LX_PE_CMN_HUE_T hue[LX_PE_WIN_NUM];				///< hue
}
PE_CMN_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_CMN_Init(void);
int PE_CMN_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_CMN_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_CMN_GetCurCmnSettings(PE_CMN_SETTINGS_T *pstParams);
int PE_CMN_InitPicEnhanceModule(void);
int PE_CMN_CleanupPicEnhanceModule(void);
int PE_CMN_OpenPicEnhanceModule(void);
int PE_CMN_ClosePicEnhanceModule(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMN_H_ */
