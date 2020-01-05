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


/** @file pe_win_hw_l9.h
 *
 *  driver header for picture enhance window control functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.12
 *	@see		
 */

#ifndef	_PE_WIN_HW_L9_H_
#define	_PE_WIN_HW_L9_H_

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
 *  pe lrcr window position type enumeration
 */
typedef enum
{
	PE_WIN_LRTB_FULL,		///< lrcr win full
	PE_WIN_LRTB_HAF1,		///< lrcr win half1
	PE_WIN_LRTB_HAF2,		///< lrcr win half2
	PE_WIN_MAX				///< max num
}
PE_WIN_HW_L9_POS;

/**
 *	pe active window settings type
 */
typedef struct
{
	UINT32 act0_x0;		///< pe actual window0, x0 position
	UINT32 act0_y0;		///< pe actual window0, y0 position
	UINT32 act0_x1;		///< pe actual window0, x1 position
	UINT32 act0_y1;		///< pe actual window0, y1 position
	UINT32 act1_x0;		///< pe actual window1, x0 position
	UINT32 act1_y0;		///< pe actual window1, y0 position
	UINT32 act1_x1;		///< pe actual window1, x1 position
	UINT32 act1_y1;		///< pe actual window1, y1 position
	UINT32 win0_x0;		///< pe actual window0 with offset, x0 position
	UINT32 win0_y0;		///< pe actual window0 with offset, y0 position
	UINT32 win0_x1;		///< pe actual window0 with offset, x1 position
	UINT32 win0_y1;		///< pe actual window0 with offset, y1 position
	UINT32 win1_x0;		///< pe actual window1 with offset, x0 position
	UINT32 win1_y0;		///< pe actual window1 with offset, y0 position
	UINT32 win1_x1;		///< pe actual window1 with offset, x1 position
	UINT32 win1_y1;		///< pe actual window1 with offset, y1 position
	UINT32 h_max;		///< pe horizontal max size
	UINT32 v_max;		///< pe vertical max size
}
PE_WIN_HW_L9_CTRL_T;
/**
 *	pe window settings type
 */
typedef struct
{
	LX_PE_WIN_D3D_INFO_T d3d_info;				///< d3d info
	UINT32 force_ov_win_sync;					///< force to use ov out win sync
	PE_WIN_HW_L9_CTRL_T win_inf[LX_PE_WIN_NUM];	///< window info
}
PE_WIN_HW_L9_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_WIN_HW_L9_SetDbgPrint(UINT32 on_off);
int PE_WIN_HW_L9_Init(void);
int PE_WIN_HW_L9_SetWcpSync(PE_TSK_L9_CFG_T *pCfg);
int PE_WIN_HW_L9_SetEnhancingWindow(PE_TSK_L9_CFG_T *pCfg);
int PE_WIN_HW_L9_SetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams);
int PE_WIN_HW_L9_GetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams);
int PE_WIN_HW_L9_SetD3dDceHistoWin(void);
int PE_WIN_HW_L9_SetLrcrInOutSel(void);
int PE_WIN_HW_L9_SetLrcrWin(LX_PE_OUT_TYPE detect_type, PE_WIN_HW_L9_POS win_pos);
int PE_WIN_HW_L9_GetCurWinSettings(PE_WIN_HW_L9_SETTINGS_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_WIN_HW_L9_H_ */

