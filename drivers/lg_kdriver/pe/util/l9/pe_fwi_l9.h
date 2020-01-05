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


/** @file pe_fwi_l9.h
 *
 *  fw ipc interface header for pe device. ( used only within kdriver )
 *	- for L9
 *	
 *	@author		
 *	@version	0.1
 *	@note		
 *	@date		2011.09.20
 *	@see		
 */

#ifndef	_PE_FWI_L9_H_
#define	_PE_FWI_L9_H_

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
#define PE_FWI_L9_BASE_OFFSET					0
#define PE_FWI_L9_FW_CTRL_OFFSET				PE_FWI_L9_BASE_OFFSET
#define PE_FWI_L9_SHP_CORING_CTRL_05_OFFSET		(PE_FWI_L9_FW_CTRL_OFFSET+sizeof(PE_FWI_L9_FW_CTRL))
#define PE_FWI_L9_SHP_CORING_CTRL_06_OFFSET		(PE_FWI_L9_SHP_CORING_CTRL_05_OFFSET+sizeof(PE_FWI_L9_SHP_CORING_CTRL_05))
#define PE_FWI_L9_SHP_CORING_CTRL_09_OFFSET		(PE_FWI_L9_SHP_CORING_CTRL_06_OFFSET+sizeof(PE_FWI_L9_SHP_CORING_CTRL_06))
#define PE_FWI_L9_SHP_DP_CTRL_01_OFFSET			(PE_FWI_L9_SHP_CORING_CTRL_09_OFFSET+sizeof(PE_FWI_L9_SHP_CORING_CTRL_09))
#define PE_FWI_L9_SHP_DERH_CTRL_0B_OFFSET		(PE_FWI_L9_SHP_DP_CTRL_01_OFFSET+sizeof(PE_FWI_L9_SHP_DP_CTRL_01))
#define PE_FWI_L9_DNT_FMD_CTRL_OFFSET			(PE_FWI_L9_SHP_DERH_CTRL_0B_OFFSET+sizeof(PE_FWI_L9_SHP_DERH_CTRL_0B))
#define PE_FWI_L9_MUTE_CTRL_OFFSET				(PE_FWI_L9_DNT_FMD_CTRL_OFFSET+sizeof(PE_FWI_L9_DNT_FMD_CTRL))
#define PE_FWI_L9_TNR_CTRL_OFFSET				(PE_FWI_L9_MUTE_CTRL_OFFSET+sizeof(PE_FWI_L9_MUTE_CTRL))
#define PE_FWI_L9_SCL_CTRL_OFFSET				(PE_FWI_L9_TNR_CTRL_OFFSET+sizeof(PE_FWI_L9_TNR_CTRL))
#define PE_FWI_L9_SRC_INFO_OFFSET				(PE_FWI_L9_SCL_CTRL_OFFSET+sizeof(PE_FWI_L9_SCL_CTRL))

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/**
 * PE FW ctrl
 */
typedef struct {
	UINT8 win_id;	//0,1,2:on(0:L, 1:R, 2:All), 0xff:off
}
PE_FWI_L9_FW_CTRL;

/**
 * PE Sharpness Coring Control_05
 */
typedef struct {
	UINT8 gt_th0;
	UINT8 gt_th1;
}
PE_FWI_L9_SHP_CORING_CTRL_05;

/**
 * PE Sharpness Coring Control_06
 */
typedef struct {
	UINT8 gt_th0a;
	UINT8 gt_th0b;
}
PE_FWI_L9_SHP_CORING_CTRL_06;

/**
 * PE Sharpness Coring Control_09
 */
typedef struct {
	UINT8 edge_gain_b;
	UINT8 edge_gain_w;
	UINT8 texture_gain_b;
    UINT8 texture_gain_w;
}
PE_FWI_L9_SHP_CORING_CTRL_09;

/**
 * PE Sharpness DP Control_01
 */
typedef struct {
	UINT8 edge_gain_b;
	UINT8 edge_gain_w;
	UINT8 texture_gain_b;
    UINT8 texture_gain_w;
}
PE_FWI_L9_SHP_DP_CTRL_01;

/**
 * PE Sharpness DERH Control_08
 */
typedef struct {
	UINT8  e_gain_th1;
	UINT8  e_gain_th2;
}
PE_FWI_L9_SHP_DERH_CTRL_0B;

/**
 * PE FMD Control
 */
typedef struct {
	UINT8 fmd_enable;
}
PE_FWI_L9_DNT_FMD_CTRL;

/**
 * PE Mute Control
 */
typedef struct {
	UINT8 mute_enable;
}
PE_FWI_L9_MUTE_CTRL;

/**
 * PE TNR Control
 */
typedef struct {
	UINT8 auto_enable;
}
PE_FWI_L9_TNR_CTRL;

/**
 * PE SCL Control
 */
typedef struct {
	UINT8 set_cnt;
}
PE_FWI_L9_SCL_CTRL;

/**
 * PE SRC Info
 */
typedef struct {
	UINT8 dtv_play_type;	//0:normal, 1:file play, 2:hdd play
}
PE_FWI_L9_SRC_INFO;

/**
 * PQ Firmware IPC Control
 */
typedef struct {
	PE_FWI_L9_FW_CTRL				fw_ctrl;
	PE_FWI_L9_SHP_CORING_CTRL_05	shp_coring_ctrl_05;
	PE_FWI_L9_SHP_CORING_CTRL_06	shp_coring_ctrl_06;
	PE_FWI_L9_SHP_CORING_CTRL_09	shp_coring_ctrl_09;
	PE_FWI_L9_SHP_DP_CTRL_01		shp_dp_ctrl_01;
	PE_FWI_L9_SHP_DERH_CTRL_0B		shp_derh_ctrl_0B;
	PE_FWI_L9_DNT_FMD_CTRL			fmd_ctrl;
	PE_FWI_L9_MUTE_CTRL				mute_ctrl;
	PE_FWI_L9_TNR_CTRL				tnr_ctrl;
	PE_FWI_L9_SCL_CTRL				scl_ctrl;
	PE_FWI_L9_SRC_INFO				src_info;
}
PE_FWI_L9_PQ_IPC_CTRL;

/**
 *	pe etc settings type
 */
typedef struct
{
	PE_FWI_L9_FW_CTRL				fw_ctrl;					///< fwi ctrl
	PE_FWI_L9_SHP_CORING_CTRL_05	coring_05[LX_PE_WIN_NUM];	///< shp coring 05
	PE_FWI_L9_SHP_CORING_CTRL_06	coring_06[LX_PE_WIN_NUM];	///< shp coring 06
	PE_FWI_L9_SHP_CORING_CTRL_09	coring_09[LX_PE_WIN_NUM];	///< shp coring 09
	PE_FWI_L9_SHP_DP_CTRL_01		dp_01[LX_PE_WIN_NUM];		///< shp dp 01
	PE_FWI_L9_DNT_FMD_CTRL			fmd_ctrl[LX_PE_WIN_NUM];	///< film ctrl
	PE_FWI_L9_TNR_CTRL				tnr_ctrl;					///< tnr mode
	PE_FWI_L9_SRC_INFO				src_info;					///< dtv type, see LX_PE_DTV_TYPE
}
PE_FWI_L9_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

int PE_FWI_L9_Init(void);
int PE_FWI_L9_GetCurFwiSettings(PE_FWI_L9_SETTINGS_T *pstParams);
void PE_FWI_L9_SetDbgPrint(UINT32 on_off);
UINT32 PE_FWI_L9_GetDbgPrint(void);
int PE_FWI_L9_SetCtrlWin(UINT32 win_id);
int PE_FWI_L9_SetMuteState(PE_FWI_L9_MUTE_CTRL *pstParams);
int PE_FWI_L9_SetTnrAutoMode(LX_PE_NRD_TNR1_CMN_T *pstParams);
int PE_FWI_L9_SetSclSettingCnt(UINT32 cnt);
int PE_FWI_L9_SetSrcInfo(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_FWI_L9_SetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams);
int PE_FWI_L9_SetShpDefault(UINT32 win_id);
int PE_FWI_L9_SetReMiscCtrl(LX_PE_SHP_RE1_MISC_T *pstParams);
int PE_FWI_L9_SetReEdgeAndDetailCtrl(UINT32 win_id,LX_PE_SHP_EE1_T *pstEe,LX_PE_SHP_DE1_T *pstDe);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_FWI_L9_H_ */

