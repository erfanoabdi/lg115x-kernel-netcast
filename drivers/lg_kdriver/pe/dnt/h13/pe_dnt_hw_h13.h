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


/** @file pe_dnt_hw_h13.h
 *
 *  driver header for picture enhance deinterlacer. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.12
 *	@see		
 */

#ifndef	_PE_DNT_HW_H13_H_
#define	_PE_DNT_HW_H13_H_

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
#define PE_DNT_HW_H13_IPC_2D		0x0
#define PE_DNT_HW_H13_IPC_3D		0x1
#define PE_DNT_HW_H13_IPC_MA		0x2
#define PE_DNT_HW_H13_CLC_OFF		0x0
#define PE_DNT_HW_H13_CLC__ON		0x1

/**	20130226, sj.youm,
*	define for set ipc mode and clc enable on pe thread,
*	because of ipc,clc artifact on pause for file play.
*/
#define PE_DNT_HW_H13_SET_IPC_CLC_ON_TASK

/**	20130307, sj.youm,
*	define for set only clc enable on pe thread,
*	because of ipc 2d shaking on starting some file play.
*/
#define PE_DNT_HW_H13_SET_ONLY_CLC_ON_TASK

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe dnt ipc fmt(for H13BX)
 */
typedef enum
{
	PE_DNT_H13B_IPC_ATV_480 = 0,	///< atv 480
	PE_DNT_H13B_IPC_ATV_576,		///< atv 576
	PE_DNT_H13B_IPC_AV_480,			///< av(cvd) 480
	PE_DNT_H13B_IPC_AV_576,			///< av(cvd) 576
	PE_DNT_H13B_IPC_SCARTRGB,		///< scart rgb
	PE_DNT_H13B_IPC_DTV_480,		///< dtv 480
	PE_DNT_H13B_IPC_DTV_576,		///< dtv 576
	PE_DNT_H13B_IPC_DTV_HD,			///< dtv hd
	PE_DNT_H13B_IPC_SD_480,			///< sd 480
	PE_DNT_H13B_IPC_SD_576,			///< sd 576
	PE_DNT_H13B_IPC_HD,				///< hd
	PE_DNT_H13B_IPC_PC,				///< pc(vflt hmc protect enable off)
	PE_DNT_H13B_IPC_NUM				///< max num
}
PE_DNT_HW_H13B_IPC_FMT;

/**
 *	pe dnt clc fmt(for H13BX)
 */
typedef enum
{
	PE_DNT_H13B_CLC_AV = 0,		///< av(cvd)
	PE_DNT_H13B_CLC_SD,			///< sd
	PE_DNT_H13B_CLC_HD,			///< hd
	PE_DNT_H13B_CLC_PC,			///< pc(clc off)
	PE_DNT_H13B_CLC_NUM			///< max num
}
PE_DNT_HW_H13B_CLC_FMT;

/**
 *	pe dnt v filter y fmt(for H13BX)
 */
typedef enum
{
	PE_DNT_H13B_VFY_SD = 0,			///< sd
	PE_DNT_H13B_VFY_HD_I,			///< hd i
	PE_DNT_H13B_VFY_HD_P,			///< hd p
	PE_DNT_H13B_VFY_PC,				///< pc
	PE_DNT_H13B_VFY_NUM				///< max num
}
PE_DNT_HW_H13B_VFY_FMT;

/**
 *	pe dnt ipc fmt(for H13AX)
 */
typedef enum
{
	PE_DNT_H13A_IPC_SD = 0,		///< sd
	PE_DNT_H13A_IPC_HD,			///< hd
	PE_DNT_H13A_IPC_AV,			///< av
	PE_DNT_H13A_IPC_DTV_SD,		///< dtv sd
	PE_DNT_H13A_IPC_NUM			///< max num
}
PE_DNT_HW_H13A_IPC_FMT;

/**
 *	pe dnt film mode fmt(for H13AX)
 */
typedef enum
{
	PE_DNT_H13A_FMD_ATV_60 = 0,		///< atv 60
	PE_DNT_H13A_FMD_ATV_50,			///< atv 50
	PE_DNT_H13A_FMD_AV_60,			///< cvbs 60
	PE_DNT_H13A_FMD_AV_50,			///< cvbs 50
	PE_DNT_H13A_FMD_DTV_SD_60,		///< dtv sd 60
	PE_DNT_H13A_FMD_DTV_SD_50,		///< dtv sd 50
	PE_DNT_H13A_FMD_DTV_HD,			///< dtv hd
	PE_DNT_H13A_FMD_HDMI_SD_60,		///< hdmi sd 60
	PE_DNT_H13A_FMD_HDMI_SD_50,		///< hdmi sd 50
	PE_DNT_H13A_FMD_HD,				///< hd
	PE_DNT_H13A_FMD_NUM				///< max num
}
PE_DNT_HW_H13A_FMD_FMT;

/**
 *	pe dnt module settings type
 */
typedef struct
{
	UINT32 cur_game_mode;				///< current p0l_ipc_ctrl_01 [19]cr_game_mode
	UINT32 cur_p0l_ipc_ctrl_00;			///< current p0l_ipc_ctrl_00
	UINT32 cur_p0r_ipc_ctrl_00;			///< current p0r_ipc_ctrl_00
	UINT32 cur_p0l_clc_ctrl_00;			///< current p0l_clc_ctrl_00
	UINT32 pre_ipc_y_md[LX_PE_WIN_NUM];	///< previous ipc y mode
	UINT32 pre_ipc_c_md[LX_PE_WIN_NUM];	///< previous ipc c mode
	UINT32 pre_clc_flt_en;				///< previous clc filter enable
	UINT32 pre_clc_det_en;				///< previous clc detect enable
}
PE_DNT_HW_H13_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_DNT_HW_H13_SetDbgPrint(UINT32 on_off);
int PE_DNT_HW_H13_Init(void);
int PE_DNT_HW_H13_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_DNT_HW_H13_RdDefault(LX_PE_ETC_DBG_T *pstParams);
int PE_DNT_HW_H13_SetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);
int PE_DNT_HW_H13_GetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);
int PE_DNT_HW_H13_SetIpcClcMode(PE_TSK_H13_CFG_T *pCfg);
int PE_DNT_HW_H13_GetCurDntSettings(PE_DNT_HW_H13_SETTINGS_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNT_HW_H13_H_ */
