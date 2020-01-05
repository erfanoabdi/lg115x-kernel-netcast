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


/** @file pe_inf_l9.h
 *
 *  information management for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.15
 *	@see		
 */

#ifndef	_PE_INF_L9_H_
#define	_PE_INF_L9_H_

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
 *	pe control inf
 */
typedef struct
{
	UINT32 pe0_src_h;		///< pe input horizontal size
	UINT32 pe0_src_v;		///< pe input vertical size	
	UINT32 scl_src_h;		///< scaler input horizontal size
	UINT32 scl_src_v;		///< scaler input vertical size
	UINT32 scl_resize;		///< scaler resize case, 1:yes, 0:no
	UINT32 scl_hd;			///< scaler hd case, 1:yes, 0:no
	UINT32 i_win_h_ofst;	///< scaler input window horizontal offset
	UINT32 i_win_v_ofst;	///< scaler input window vertical offset
	UINT32 i_win_h_size;	///< scaler input window horizontal size
	UINT32 i_win_v_size;	///< scaler input window vertical size
	UINT32 o_win_h_size;	///< scaler output window horizontal size
	UINT32 o_win_v_size;	///< scaler output window vertical size
	UINT32 m_win_h_ofst;	///< ov m window horizontal offset
	UINT32 m_win_v_ofst;	///< ov m window vertical offset
	UINT32 m_win_h_size;	///< ov m window horizontal size
	UINT32 m_win_v_size;	///< ov m window vertical size
	UINT32 is_yuv444;		///< scaler input color format, 0x1:444,0x0:422or420
	UINT32 d3d_chk;			///< 0:normal,1:not tb,2:not ss
	UINT32 auto_cr_en;		///< enable LRCR, 1:on, 0:off
	UINT32 sat_status;		///< saturation status
	UINT32 mute_on;			///< mute on, 1:on, 0:off
}
PE_INF_L9_CTRL_T;

/**
 *	pe inf settings type
 */
typedef struct
{
	LX_PE_INF_DISPLAY_T disp_info[LX_PE_WIN_NUM];	///< display info
	PE_INF_L9_CTRL_T ctrl_info[LX_PE_WIN_NUM];		///< control info
}
PE_INF_L9_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
void PE_INF_L9_SetDbgPrint(UINT32 on_off);
int PE_INF_L9_Init(void);
int PE_INF_L9_SetDispInfo(LX_PE_INF_DISPLAY_T *pstParams);
int PE_INF_L9_CheckSclInfo(void);
int PE_INF_L9_GetCurInfSettings(PE_INF_L9_SETTINGS_T *pstParams);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_INF_L9_H_ */

