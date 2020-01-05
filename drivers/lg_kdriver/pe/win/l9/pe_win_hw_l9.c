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


/** @file pe_win_hw_l9.c
 *
 *  driver for picture enhance window control functions. ( used only within kdriver )
 *	- control window of each pe module
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.16
 *	@see		
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "pe_cfg.h"
#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc_hw.h"
#include "pe_win_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_WIN_HW_L9_FHD_H_MAX	1920
#define PE_WIN_HW_L9_FHD_V_MAX	1080
#define PE_WIN_HW_L9_FHD_H_HALF	960
#define PE_WIN_HW_L9_FHD_V_HALF	540

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_WIN_HW_L9_ERROR	printk

#define PE_WIN_HW_L9_DBG_PRINT(fmt,args...)	\
	if(_g_win_hw_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_WIN_HW_L9_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_WIN_HW_L9_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern PE_D3D_INFO_T d3d_info;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_win_hw_l9_trace=0x0;	//default should be off.
static PE_WIN_HW_L9_SETTINGS_T _g_pe_win_hw_l9_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * set debug print on off
 *
 * @param   on_off [in] UINT8
 * @return  void
 * @see
 * @author
 */
void PE_WIN_HW_L9_SetDbgPrint(UINT32 on_off)
{
	_g_win_hw_l9_trace = on_off? 1:0;
	return;
}
/**
 * init pe window
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_HW_L9_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			PE_WIN_HW_L9_DBG_PRINT("init global values.\n");
			memset0(_g_pe_win_hw_l9_info);
			_g_pe_win_hw_l9_info.force_ov_win_sync=1;	//use ov win sync for r ch
			if(_g_pe_win_hw_l9_info.force_ov_win_sync)
			{
				PE_P1R_L9B_QWr01(pe1_r_top_ctrl_02,	disp_active_mux,	0x1);	//disp_va, disp_ha -> (TPG) FILM1
				PE_DED_L9B_RdFL(ded_def_disp_sync_sel);
				PE_DED_L9B_Wr01(ded_def_disp_sync_sel, ded_def_pe1_r,	0x0);	//ded to def 0
				PE_DED_L9B_WrFL(ded_def_disp_sync_sel);
				PE_DED_L9B_RdFL(ded_dly_disp_sync_params);
				PE_DED_L9B_Wr01(ded_dly_disp_sync_params, h_dly,		0xc3);	//pixel delay : 195
				PE_DED_L9B_WrFL(ded_dly_disp_sync_params);
		        PE_P1R_L9B_QWr02(pe1_r_win1_ctrl_00,win_en,			0x0,\
	            									win_outside,	0x0);
		        PE_P1R_L9B_QWr02(pe1_r_win3_ctrl_00,win_en,			0x0,\
													win_outside,	0x0);
			}
			else
			{
				PE_P1R_L9B_QWr01(pe1_r_top_ctrl_02,	disp_active_mux,	0x0);	//pe1_va_in, pe1_ha_in-> (TPG) FILM1
				PE_DED_L9B_RdFL(ded_def_disp_sync_sel);
				PE_DED_L9B_Wr01(ded_def_disp_sync_sel, ded_def_pe1_r,	0x1);	//ded to def 1
				PE_DED_L9B_WrFL(ded_def_disp_sync_sel);
				PE_DED_L9B_RdFL(ded_dly_disp_sync_params);
				PE_DED_L9B_Wr01(ded_dly_disp_sync_params, h_dly,		0x13d);	//pixel delay : 317
				PE_DED_L9B_WrFL(ded_dly_disp_sync_params);
		        PE_P1R_L9B_QWr02(pe1_r_win1_ctrl_00,win_en,			0x1,\
	            									win_outside,	0x0);
		        PE_P1R_L9B_QWr02(pe1_r_win3_ctrl_00,win_en,			0x1,\
													win_outside,	0x0);
			}
			PE_WIN_HW_L9_DBG_PRINT("pe1 win ctrl init, inside.\n");
	        PE_P1L_L9B_QWr02(pe1_l_win1_ctrl_00,win_en,			0x1,\
            									win_outside,	0x0);
	        PE_P1L_L9B_QWr02(pe1_l_win2_ctrl_00,win_en,			0x1,\
            									win_outside,	0x0);
	        PE_P1L_L9B_QWr02(pe1_l_win3_ctrl_00,win_en,			0x1,\
            									win_outside,	0x0);
	        PE_P1R_L9B_QWr02(pe1_r_win2_ctrl_00,win_en,			0x1,\
												win_outside,	0x0);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_WIN_HW_L9_DBG_PRINT("pe1 win enable, inside.\n");
	        PE_P1L_L9A_QWr02(pe1_l_win_ctrl_00, win_en,			0x1,\
												win_outside,	0x0);
	        PE_P1R_L9A_QWr02(pe1_r_win_ctrl_00, win_en,			0x1,\
												win_outside,	0x0);
			PE_WIN_HW_L9_DBG_PRINT("bbd enable & manual setting.\n");
            PE_P1L_L9A_QWr02(pe1_l_bbd2d_ctrl_0,black_boundary_detection_enable,0x1,\
												mode_selection,					0x1);
            PE_P1R_L9A_QWr02(pe1_r_bbd2d_ctrl_0,black_boundary_detection_enable,0x1,\
												mode_selection,					0x1);
		}
		else
		{
			PE_WIN_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
int PE_WIN_HW_L9_SetWcpSync(PE_TSK_L9_CFG_T *pCfg)
{
	int ret = RET_OK;
	static UINT32 prev_ov_r_out_sync=0xff;
	UINT32 ov_r_out_sync;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_TSK_L9_DTA_T *pDta = &pCfg->dta;
	PE_WIN_HW_L9_SETTINGS_T *pInfo=&_g_pe_win_hw_l9_info;
	do {
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_L9BX)
		{
			/**************************************************************/
			/* pe sync control for R path */
			/**************************************************************/			
			switch(disp0_info->out_type)
			{
				case LX_PE_OUT_2D:
					ov_r_out_sync = 0;	//win sync
					break;
				case LX_PE_OUT_TB:
				case LX_PE_OUT_SS:
				case LX_PE_OUT_FS:
				case LX_PE_OUT_DUAL_TB:
				case LX_PE_OUT_DUAL_SS:
				case LX_PE_OUT_DUAL_FULL:
				case LX_PE_OUT_PIP:
					ov_r_out_sync = 1;	//display sync
					break;
				default:
					ov_r_out_sync = 0;	//win sync
					break;
			}
			if(pInfo->force_ov_win_sync)
			{
				ov_r_out_sync = 0;
			}
			if(prev_ov_r_out_sync != ov_r_out_sync)
			{
				PE_WIN_HW_L9_DBG_PRINT("set ov_r_out_sync:pre:0x%x,cur:0x%x\n",\
					prev_ov_r_out_sync,ov_r_out_sync);
				PE_OVR_L9B0_RdFL(ovr_ov_ctrl0);
				PE_OVR_L9B0_Wr01(ovr_ov_ctrl0, ov_out_sync_mux, ov_r_out_sync? 0x1:0x0);
				PE_OVR_L9B0_WrFL(ovr_ov_ctrl0);
				PE_P1R_L9B_QWr01(pe1_r_win1_ctrl_00, win_en,	ov_r_out_sync? 0x1:0x0);
				PE_P1R_L9B_QWr01(pe1_r_win3_ctrl_00, win_en,	ov_r_out_sync? 0x1:0x0);
				prev_ov_r_out_sync = ov_r_out_sync;
				pDta->ov_r_out_sync = ov_r_out_sync;
			}
			/**************************************************************/
		}
		else
		{
			PE_WIN_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
int PE_WIN_HW_L9_SetEnhancingWindow(PE_TSK_L9_CFG_T *pCfg)
{
	int ret = RET_OK;
	UINT32 x_ofst,y_ofst;
	UINT32 x0[LX_PE_WIN_NUM],y0[LX_PE_WIN_NUM],x1[LX_PE_WIN_NUM],y1[LX_PE_WIN_NUM];
	UINT32 act0_x0[LX_PE_WIN_NUM],act0_y0[LX_PE_WIN_NUM],act0_x1[LX_PE_WIN_NUM],act0_y1[LX_PE_WIN_NUM];
	UINT32 act1_x0[LX_PE_WIN_NUM],act1_y0[LX_PE_WIN_NUM],act1_x1[LX_PE_WIN_NUM],act1_y1[LX_PE_WIN_NUM];
	UINT32 win0_x0[LX_PE_WIN_NUM],win0_x1[LX_PE_WIN_NUM],win0_y0[LX_PE_WIN_NUM],win0_y1[LX_PE_WIN_NUM];
	UINT32 win1_x0[LX_PE_WIN_NUM],win1_x1[LX_PE_WIN_NUM],win1_y0[LX_PE_WIN_NUM],win1_y1[LX_PE_WIN_NUM];
	UINT32 h_max,v_max;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_L9_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_L9_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_TSK_L9_DTA_T *pDta = &pCfg->dta;
	PE_WIN_HW_L9_SETTINGS_T *pWinInfo=&_g_pe_win_hw_l9_info;
	do {
		CHECK_KNULL(pCfg);
		if(disp0_info->out_type==LX_PE_OUT_UD)
		{
			h_max=PE_WIN_HW_L9_FHD_H_MAX;
			v_max=PE_WIN_HW_L9_FHD_V_MAX<<1;
			x_ofst = y_ofst = 0;
		}
		else
		{
			h_max=PE_WIN_HW_L9_FHD_H_MAX;
			v_max=PE_WIN_HW_L9_FHD_V_MAX;
			x_ofst = y_ofst = 3;
		}

		if(ctrl0_info->m_win_h_size <= (x_ofst<<1) || \
			ctrl0_info->m_win_v_size <= (y_ofst<<1))
		{
			x0[LX_PE_WIN_0] = 0;
			y0[LX_PE_WIN_0] = 0;
			x1[LX_PE_WIN_0] = h_max-1;
			y1[LX_PE_WIN_0] = v_max-1;
		}
		else
		{
			x0[LX_PE_WIN_0] = ctrl0_info->m_win_h_ofst;
			y0[LX_PE_WIN_0] = ctrl0_info->m_win_v_ofst;
			x1[LX_PE_WIN_0] = x0[LX_PE_WIN_0]+ctrl0_info->m_win_h_size-1;
			y1[LX_PE_WIN_0] = y0[LX_PE_WIN_0]+ctrl0_info->m_win_v_size-1;
		}
		if(ctrl1_info->m_win_h_size <= (x_ofst<<1) || \
			ctrl1_info->m_win_v_size <= (y_ofst<<1))
		{
			x0[LX_PE_WIN_1] = 0;
			y0[LX_PE_WIN_1] = 0;
			x1[LX_PE_WIN_1] = h_max-1;
			y1[LX_PE_WIN_1] = v_max-1;
		}
		else
		{
			x0[LX_PE_WIN_1] = ctrl1_info->m_win_h_ofst;
			y0[LX_PE_WIN_1] = ctrl1_info->m_win_v_ofst;
			x1[LX_PE_WIN_1] = x0[LX_PE_WIN_1]+ctrl1_info->m_win_h_size-1;
			y1[LX_PE_WIN_1] = y0[LX_PE_WIN_1]+ctrl1_info->m_win_v_size-1;
		}

		switch(disp0_info->out_type)
		{
			case LX_PE_OUT_TB:
			case LX_PE_OUT_SS:
				{
					/* L : window 0 */
					act0_x0[LX_PE_WIN_0] = x0[LX_PE_WIN_0];
					act0_y0[LX_PE_WIN_0] = y0[LX_PE_WIN_0];
					act0_x1[LX_PE_WIN_0] = x1[LX_PE_WIN_0];
					act0_y1[LX_PE_WIN_0] = y1[LX_PE_WIN_0];
					win0_x0[LX_PE_WIN_0] = x0[LX_PE_WIN_0]+x_ofst;
					win0_y0[LX_PE_WIN_0] = y0[LX_PE_WIN_0]+y_ofst;
					win0_x1[LX_PE_WIN_0] = x1[LX_PE_WIN_0]-x_ofst;
					win0_y1[LX_PE_WIN_0] = y1[LX_PE_WIN_0]-y_ofst;
					/* L : window 1 */
					act1_x0[LX_PE_WIN_0] = x0[LX_PE_WIN_1];
					act1_y0[LX_PE_WIN_0] = y0[LX_PE_WIN_1];
					act1_x1[LX_PE_WIN_0] = x1[LX_PE_WIN_1];
					act1_y1[LX_PE_WIN_0] = y1[LX_PE_WIN_1];
					win1_x0[LX_PE_WIN_0] = x0[LX_PE_WIN_1]+x_ofst;
					win1_y0[LX_PE_WIN_0] = y0[LX_PE_WIN_1]+y_ofst;
					win1_x1[LX_PE_WIN_0] = x1[LX_PE_WIN_1]-x_ofst;
					win1_y1[LX_PE_WIN_0] = y1[LX_PE_WIN_1]-y_ofst;
					/* R : window 0 */
					act0_x0[LX_PE_WIN_1] = act1_x0[LX_PE_WIN_0];
					act0_y0[LX_PE_WIN_1] = act1_y0[LX_PE_WIN_0];
					act0_x1[LX_PE_WIN_1] = act1_x1[LX_PE_WIN_0];
					act0_y1[LX_PE_WIN_1] = act1_y1[LX_PE_WIN_0];
					win0_x0[LX_PE_WIN_1] = win1_x0[LX_PE_WIN_0];
					win0_y0[LX_PE_WIN_1] = win1_y0[LX_PE_WIN_0];
					win0_x1[LX_PE_WIN_1] = win1_x1[LX_PE_WIN_0];
					win0_y1[LX_PE_WIN_1] = win1_y1[LX_PE_WIN_0];
					/* R : window 1 */
					act1_x0[LX_PE_WIN_1] = 0;
					act1_y0[LX_PE_WIN_1] = 0;
					act1_x1[LX_PE_WIN_1] = 0;
					act1_y1[LX_PE_WIN_1] = 0;
					win1_x0[LX_PE_WIN_1] = 0;
					win1_y0[LX_PE_WIN_1] = 0;
					win1_x1[LX_PE_WIN_1] = 0;
					win1_y1[LX_PE_WIN_1] = 0;
				}
				break;
			default:
				{
					/* L : window 0 */
					act0_x0[LX_PE_WIN_0] = x0[LX_PE_WIN_0];
					act0_y0[LX_PE_WIN_0] = y0[LX_PE_WIN_0];
					act0_x1[LX_PE_WIN_0] = x1[LX_PE_WIN_0];
					act0_y1[LX_PE_WIN_0] = y1[LX_PE_WIN_0];
					win0_x0[LX_PE_WIN_0] = x0[LX_PE_WIN_0]+x_ofst;
					win0_y0[LX_PE_WIN_0] = y0[LX_PE_WIN_0]+y_ofst;
					win0_x1[LX_PE_WIN_0] = x1[LX_PE_WIN_0]-x_ofst;
					win0_y1[LX_PE_WIN_0] = y1[LX_PE_WIN_0]-y_ofst;
					/* L : window 1 */
					act1_x0[LX_PE_WIN_0] = 0;
					act1_y0[LX_PE_WIN_0] = 0;
					act1_x1[LX_PE_WIN_0] = 0;
					act1_y1[LX_PE_WIN_0] = 0;
					win1_x0[LX_PE_WIN_0] = 0;
					win1_y0[LX_PE_WIN_0] = 0;
					win1_x1[LX_PE_WIN_0] = 0;
					win1_y1[LX_PE_WIN_0] = 0;
					/* R : window 0 */
					act0_x0[LX_PE_WIN_1] = x0[LX_PE_WIN_1];
					act0_y0[LX_PE_WIN_1] = y0[LX_PE_WIN_1];
					act0_x1[LX_PE_WIN_1] = x1[LX_PE_WIN_1];
					act0_y1[LX_PE_WIN_1] = y1[LX_PE_WIN_1];
					win0_x0[LX_PE_WIN_1] = x0[LX_PE_WIN_1]+x_ofst;
					win0_y0[LX_PE_WIN_1] = y0[LX_PE_WIN_1]+y_ofst;
					win0_x1[LX_PE_WIN_1] = x1[LX_PE_WIN_1]-x_ofst;
					win0_y1[LX_PE_WIN_1] = y1[LX_PE_WIN_1]-y_ofst;
					/* R : window 1 */
					act1_x0[LX_PE_WIN_1] = 0;
					act1_y0[LX_PE_WIN_1] = 0;
					act1_x1[LX_PE_WIN_1] = 0;
					act1_y1[LX_PE_WIN_1] = 0;
					win1_x0[LX_PE_WIN_1] = 0;
					win1_y0[LX_PE_WIN_1] = 0;
					win1_x1[LX_PE_WIN_1] = 0;
					win1_y1[LX_PE_WIN_1] = 0;
				}
				break;
		}
		/* L : set act */
		if((pWinInfo->win_inf[LX_PE_WIN_0].act0_x0 != act0_x0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].act0_y0 != act0_y0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].act0_x1 != act0_x1[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].act0_y1 != act0_y1[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].act1_x0 != act1_x0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].act1_y0 != act1_y0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].act1_x1 != act1_x1[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].act1_y1 != act1_y1[LX_PE_WIN_0]))
		{
			PE_WIN_HW_L9_DBG_PRINT("[inf]out:%d,ov_sync:%d,ofst:%d,%d\n",\
				disp0_info->out_type,pDta->ov_r_out_sync,x_ofst,y_ofst);
			PE_WIN_HW_L9_DBG_PRINT("[inf]o_win[0]:%d,%d,%d,%d,o_win[1]:%d,%d,%d,%d\n",\
				ctrl0_info->m_win_h_ofst,ctrl0_info->m_win_v_ofst,ctrl0_info->m_win_h_size,\
				ctrl0_info->m_win_v_size,ctrl1_info->m_win_h_ofst,ctrl1_info->m_win_v_ofst,\
				ctrl1_info->m_win_h_size,ctrl1_info->m_win_v_size);
			PE_WIN_HW_L9_DBG_PRINT("[set]act0[0] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_0].act0_x0,pWinInfo->win_inf[LX_PE_WIN_0].act0_y0,\
				pWinInfo->win_inf[LX_PE_WIN_0].act0_x1,pWinInfo->win_inf[LX_PE_WIN_0].act0_y1,\
				act0_x0[LX_PE_WIN_0],act0_y0[LX_PE_WIN_0],act0_x1[LX_PE_WIN_0],act0_y1[LX_PE_WIN_0]);
			PE_WIN_HW_L9_DBG_PRINT("[set]act1[0] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_0].act1_x0,pWinInfo->win_inf[LX_PE_WIN_0].act1_y0,\
				pWinInfo->win_inf[LX_PE_WIN_0].act1_x1,pWinInfo->win_inf[LX_PE_WIN_0].act1_y1,\
				act1_x0[LX_PE_WIN_0],act1_y0[LX_PE_WIN_0],act1_x1[LX_PE_WIN_0],act1_y1[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win2_ctrl_01,win_w0_x0,	act0_x0[LX_PE_WIN_0],\
            									win_w0_y0,	act0_y0[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win2_ctrl_02,win_w0_x1,	act0_x1[LX_PE_WIN_0],\
            									win_w0_y1,	act0_y1[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win2_ctrl_03,win_w1_x0,	act1_x0[LX_PE_WIN_0],\
            									win_w1_y0,	act1_y0[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win2_ctrl_04,win_w1_x1,	act1_x1[LX_PE_WIN_0],\
            									win_w1_y1,	act1_y1[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_apl_ctrl_00,	apl_win_ctrl_x0, act0_x0[LX_PE_WIN_0],\
            									apl_win_ctrl_y0, act0_y0[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_apl_ctrl_01, apl_win_ctrl_x1, act0_x1[LX_PE_WIN_0],\
            									apl_win_ctrl_y1, act0_y1[LX_PE_WIN_0]);
			pWinInfo->win_inf[LX_PE_WIN_0].act0_x0 = act0_x0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].act0_y0 = act0_y0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].act0_x1 = act0_x1[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].act0_y1 = act0_y1[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].act1_x0 = act1_x0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].act1_y0 = act1_y0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].act1_x1 = act1_x1[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].act1_y1 = act1_y1[LX_PE_WIN_0];
		}
		/* R : set act */
		if((pWinInfo->win_inf[LX_PE_WIN_1].act0_x0 != act0_x0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].act0_y0 != act0_y0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].act0_x1 != act0_x1[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].act0_y1 != act0_y1[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].act1_x0 != act1_x0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].act1_y0 != act1_y0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].act1_x1 != act1_x1[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].act1_y1 != act1_y1[LX_PE_WIN_1]))
		{
			PE_WIN_HW_L9_DBG_PRINT("[inf]out:%d,ov_sync:%d,ofst:%d,%d\n",\
				disp0_info->out_type,pDta->ov_r_out_sync,x_ofst,y_ofst);
			PE_WIN_HW_L9_DBG_PRINT("[inf]o_win[0]:%d,%d,%d,%d,o_win[1]:%d,%d,%d,%d\n",\
				ctrl0_info->m_win_h_ofst,ctrl0_info->m_win_v_ofst,ctrl0_info->m_win_h_size,\
				ctrl0_info->m_win_v_size,ctrl1_info->m_win_h_ofst,ctrl1_info->m_win_v_ofst,\
				ctrl1_info->m_win_h_size,ctrl1_info->m_win_v_size);
			PE_WIN_HW_L9_DBG_PRINT("[set]act0[1] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_1].act0_x0,pWinInfo->win_inf[LX_PE_WIN_1].act0_y0,\
				pWinInfo->win_inf[LX_PE_WIN_1].act0_x1,pWinInfo->win_inf[LX_PE_WIN_1].act0_y1,\
				act0_x0[LX_PE_WIN_1],act0_y0[LX_PE_WIN_1],act0_x1[LX_PE_WIN_1],act0_y1[LX_PE_WIN_1]);
			PE_WIN_HW_L9_DBG_PRINT("[set]act1[1] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_1].act1_x0,pWinInfo->win_inf[LX_PE_WIN_1].act1_y0,\
				pWinInfo->win_inf[LX_PE_WIN_1].act1_x1,pWinInfo->win_inf[LX_PE_WIN_1].act1_y1,\
				act1_x0[LX_PE_WIN_1],act1_y0[LX_PE_WIN_1],act1_x1[LX_PE_WIN_1],act1_y1[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win2_ctrl_01,win_w0_x0,	act0_x0[LX_PE_WIN_1],\
            									win_w0_y0,	act0_y0[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win2_ctrl_02,win_w0_x1,	act0_x1[LX_PE_WIN_1],\
            									win_w0_y1,	act0_y1[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win2_ctrl_03,win_w1_x0,	act1_x0[LX_PE_WIN_1],\
            									win_w1_y0,	act1_y0[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win2_ctrl_04,win_w1_x1,	act1_x1[LX_PE_WIN_1],\
            									win_w1_y1,	act1_y1[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_apl_ctrl_00,	apl_win_ctrl_x0, act0_x0[LX_PE_WIN_1],\
            									apl_win_ctrl_y0, act0_y0[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_apl_ctrl_01,	apl_win_ctrl_x1, act0_x1[LX_PE_WIN_1],\
            									apl_win_ctrl_y1, act0_y1[LX_PE_WIN_1]);
			pWinInfo->win_inf[LX_PE_WIN_1].act0_x0 = act0_x0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].act0_y0 = act0_y0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].act0_x1 = act0_x1[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].act0_y1 = act0_y1[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].act1_x0 = act1_x0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].act1_y0 = act1_y0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].act1_x1 = act1_x1[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].act1_y1 = act1_y1[LX_PE_WIN_1];
		}
		/* L : set win */
		if((pWinInfo->win_inf[LX_PE_WIN_0].win0_x0 != win0_x0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].win0_y0 != win0_y0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].win0_x1 != win0_x1[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].win0_y1 != win0_y1[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].win1_x0 != win1_x0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].win1_y0 != win1_y0[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].win1_x1 != win1_x1[LX_PE_WIN_0])|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].win1_y1 != win1_y1[LX_PE_WIN_0]))
		{
			PE_WIN_HW_L9_DBG_PRINT("[inf]out:%d,ov_sync:%d,ofst:%d,%d\n",\
				disp0_info->out_type,pDta->ov_r_out_sync,x_ofst,y_ofst);
			PE_WIN_HW_L9_DBG_PRINT("[inf]o_win[0]:%d,%d,%d,%d,o_win[1]:%d,%d,%d,%d\n",\
				ctrl0_info->m_win_h_ofst,ctrl0_info->m_win_v_ofst,ctrl0_info->m_win_h_size,\
				ctrl0_info->m_win_v_size,ctrl1_info->m_win_h_ofst,ctrl1_info->m_win_v_ofst,\
				ctrl1_info->m_win_h_size,ctrl1_info->m_win_v_size);
			PE_WIN_HW_L9_DBG_PRINT("[set]win0[0] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_0].win0_x0,pWinInfo->win_inf[LX_PE_WIN_0].win0_y0,\
				pWinInfo->win_inf[LX_PE_WIN_0].win0_x1,pWinInfo->win_inf[LX_PE_WIN_0].win0_y1,\
				win0_x0[LX_PE_WIN_0],win0_y0[LX_PE_WIN_0],win0_x1[LX_PE_WIN_0],win0_y1[LX_PE_WIN_0]);
			PE_WIN_HW_L9_DBG_PRINT("[set]win1[0] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_0].win1_x0,pWinInfo->win_inf[LX_PE_WIN_0].win1_y0,\
				pWinInfo->win_inf[LX_PE_WIN_0].win1_x1,pWinInfo->win_inf[LX_PE_WIN_0].win1_y1,\
				win1_x0[LX_PE_WIN_0],win1_y0[LX_PE_WIN_0],win1_x1[LX_PE_WIN_0],win1_y1[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win1_ctrl_01,win_w0_x0,	win0_x0[LX_PE_WIN_0],\
            									win_w0_y0,	win0_y0[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win1_ctrl_02,win_w0_x1,	win0_x1[LX_PE_WIN_0],\
            									win_w0_y1,	win0_y1[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win1_ctrl_03,win_w1_x0,	win1_x0[LX_PE_WIN_0],\
            									win_w1_y0,	win1_y0[LX_PE_WIN_0]);
            PE_P1L_L9B_QWr02(pe1_l_win1_ctrl_04,win_w1_x1,	win1_x1[LX_PE_WIN_0],\
            									win_w1_y1,	win1_y1[LX_PE_WIN_0]);
			pWinInfo->win_inf[LX_PE_WIN_0].win0_x0 = win0_x0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].win0_y0 = win0_y0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].win0_x1 = win0_x1[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].win0_y1 = win0_y1[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].win1_x0 = win1_x0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].win1_y0 = win1_y0[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].win1_x1 = win1_x1[LX_PE_WIN_0];
			pWinInfo->win_inf[LX_PE_WIN_0].win1_y1 = win1_y1[LX_PE_WIN_0];
		}
		/* R : set win */
		if((pDta->ov_r_out_sync)&& \
			((pWinInfo->win_inf[LX_PE_WIN_1].win0_x0 != win0_x0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].win0_y0 != win0_y0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].win0_x1 != win0_x1[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].win0_y1 != win0_y1[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].win1_x0 != win1_x0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].win1_y0 != win1_y0[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].win1_x1 != win1_x1[LX_PE_WIN_1])|| \
			(pWinInfo->win_inf[LX_PE_WIN_1].win1_y1 != win1_y1[LX_PE_WIN_1])))
		{
			PE_WIN_HW_L9_DBG_PRINT("[inf]out:%d,ov_sync:%d,ofst:%d,%d\n",\
				disp0_info->out_type,pDta->ov_r_out_sync,x_ofst,y_ofst);
			PE_WIN_HW_L9_DBG_PRINT("[inf]o_win[0]:%d,%d,%d,%d,o_win[1]:%d,%d,%d,%d\n",\
				ctrl0_info->m_win_h_ofst,ctrl0_info->m_win_v_ofst,ctrl0_info->m_win_h_size,\
				ctrl0_info->m_win_v_size,ctrl1_info->m_win_h_ofst,ctrl1_info->m_win_v_ofst,\
				ctrl1_info->m_win_h_size,ctrl1_info->m_win_v_size);
			PE_WIN_HW_L9_DBG_PRINT("[set]win0[0] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_1].win0_x0,pWinInfo->win_inf[LX_PE_WIN_1].win0_y0,\
				pWinInfo->win_inf[LX_PE_WIN_1].win0_x1,pWinInfo->win_inf[LX_PE_WIN_1].win0_y1,\
				win0_x0[LX_PE_WIN_1],win0_y0[LX_PE_WIN_1],win0_x1[LX_PE_WIN_1],win0_y1[LX_PE_WIN_1]);
			PE_WIN_HW_L9_DBG_PRINT("[set]win1[0] : prev:%d,%d,%d,%d, cur:%d,%d,%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_1].win1_x0,pWinInfo->win_inf[LX_PE_WIN_1].win1_y0,\
				pWinInfo->win_inf[LX_PE_WIN_1].win1_x1,pWinInfo->win_inf[LX_PE_WIN_1].win1_y1,\
				win1_x0[LX_PE_WIN_1],win1_y0[LX_PE_WIN_1],win1_x1[LX_PE_WIN_1],win1_y1[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win1_ctrl_01,win_w0_x0,	win0_x0[LX_PE_WIN_1],\
            									win_w0_y0,	win0_y0[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win1_ctrl_02,win_w0_x1,	win0_x1[LX_PE_WIN_1],\
            									win_w0_y1,	win0_y1[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win1_ctrl_03,win_w1_x0,	win1_x0[LX_PE_WIN_1],\
            									win_w1_y0,	win1_y0[LX_PE_WIN_1]);
            PE_P1R_L9B_QWr02(pe1_r_win1_ctrl_04,win_w1_x1,	win1_x1[LX_PE_WIN_1],\
            									win_w1_y1,	win1_y1[LX_PE_WIN_1]);
			pWinInfo->win_inf[LX_PE_WIN_1].win0_x0 = win0_x0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].win0_y0 = win0_y0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].win0_x1 = win0_x1[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].win0_y1 = win0_y1[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].win1_x0 = win1_x0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].win1_y0 = win1_y0[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].win1_x1 = win1_x1[LX_PE_WIN_1];
			pWinInfo->win_inf[LX_PE_WIN_1].win1_y1 = win1_y1[LX_PE_WIN_1];
		}
		/* etc */
		if((pWinInfo->win_inf[LX_PE_WIN_0].h_max != h_max)|| \
			(pWinInfo->win_inf[LX_PE_WIN_0].v_max != v_max))
		{
			PE_WIN_HW_L9_DBG_PRINT("[inf]out:%d,ov_sync:%d,ofst:%d,%d\n",\
				disp0_info->out_type,pDta->ov_r_out_sync,x_ofst,y_ofst);
			PE_WIN_HW_L9_DBG_PRINT("[inf]o_win[0]:%d,%d,%d,%d,o_win[1]:%d,%d,%d,%d\n",\
				ctrl0_info->m_win_h_ofst,ctrl0_info->m_win_v_ofst,ctrl0_info->m_win_h_size,\
				ctrl0_info->m_win_v_size,ctrl1_info->m_win_h_ofst,ctrl1_info->m_win_v_ofst,\
				ctrl1_info->m_win_h_size,ctrl1_info->m_win_v_size);
			PE_WIN_HW_L9_DBG_PRINT("[set]h,v_max : prev:%d,%d, cur:%d,%d\n",\
				pWinInfo->win_inf[LX_PE_WIN_0].h_max,pWinInfo->win_inf[LX_PE_WIN_0].v_max,h_max,v_max);
            PE_P1L_L9B_QWr02(pe1_l_win3_ctrl_01,win_w0_x0,	0x0,\
            									win_w0_y0,	0x0);
            PE_P1L_L9B_QWr02(pe1_l_win3_ctrl_02,win_w0_x1,	(h_max-1),\
            									win_w0_y1,	(v_max-1));
            PE_P1L_L9B_QWr02(pe1_l_win3_ctrl_03,win_w1_x0,	0x0,\
            									win_w1_y0,	0x0);
            PE_P1L_L9B_QWr02(pe1_l_win3_ctrl_04,win_w1_x1,	0x0,\
            									win_w1_y1,	0x0);
			PE_P1L_L9B_QWr02(pe1_l_gmc_ctrl_00, pxl_rep_xpos,		0x0,\
												pxl_rep_ypos,		0x0);
			PE_P1L_L9B_QWr02(pe1_l_gmc_ctrl_01, pxl_rep_width,		h_max,\
												pxl_rep_height,		v_max);
			if(pDta->ov_r_out_sync)
			{
                PE_P1R_L9B_QWr02(pe1_r_win3_ctrl_01,win_w0_x0,	0x0,\
                									win_w0_y0,	0x0);
                PE_P1R_L9B_QWr02(pe1_r_win3_ctrl_02,win_w0_x1,	(h_max-1),\
                									win_w0_y1,	(v_max-1));
                PE_P1R_L9B_QWr02(pe1_r_win3_ctrl_03,win_w1_x0,	0x0,\
                									win_w1_y0,	0x0);
                PE_P1R_L9B_QWr02(pe1_r_win3_ctrl_04,win_w1_x1,	0x0,\
                									win_w1_y1,	0x0);
			}
			PE_P1R_L9B_QWr02(pe1_r_gmc_ctrl_00, pxl_rep_xpos,		0x0,\
												pxl_rep_ypos,		0x0);
			PE_P1R_L9B_QWr02(pe1_r_gmc_ctrl_01, pxl_rep_width,		h_max,\
												pxl_rep_height,		v_max);
			pWinInfo->win_inf[LX_PE_WIN_0].h_max = h_max;
			pWinInfo->win_inf[LX_PE_WIN_0].v_max = v_max;
		}
	}while(0);
	return ret;
}
int PE_WIN_HW_L9_SetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams)
{
	int ret = RET_OK;
	PE_WIN_HW_L9_SETTINGS_T *pInfo=&_g_pe_win_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		PE_WIN_HW_L9_DBG_PRINT("set : \n"\
		"top:%d,%d,%d,%d,btm:%d,%d,%d,%d,lft:%d,%d,%d,%d,rgt:%d,%d,%d,%d,ratio(1024=1.0): tb:%d,ss:%d\n",\
		pstParams->top.pos_x0,pstParams->top.pos_y0,pstParams->top.pos_x1,pstParams->top.pos_y1,\
		pstParams->bottom.pos_x0,pstParams->bottom.pos_y0,pstParams->bottom.pos_x1,pstParams->bottom.pos_y1,\
		pstParams->left.pos_x0,pstParams->left.pos_y0,pstParams->left.pos_x1,pstParams->left.pos_y1,\
		pstParams->right.pos_x0,pstParams->right.pos_y0,pstParams->right.pos_x1,pstParams->right.pos_y1,\
		pstParams->tb_ratio,pstParams->ss_ratio);
		memcpy(&(pInfo->d3d_info),pstParams,sizeof(LX_PE_WIN_D3D_INFO_T));
	} while (0);
	return ret;
}
int PE_WIN_HW_L9_GetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams)
{
	int ret = RET_OK;
	PE_WIN_HW_L9_SETTINGS_T *pInfo=&_g_pe_win_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		memcpy(pstParams,&(pInfo->d3d_info),sizeof(LX_PE_WIN_D3D_INFO_T));
		PE_WIN_HW_L9_DBG_PRINT("get : \n"\
		"top:%d,%d,%d,%d,btm:%d,%d,%d,%d,lft:%d,%d,%d,%d,rgt:%d,%d,%d,%d,ratio(1024=1.0): tb:%d,ss:%d\n",\
		pstParams->top.pos_x0,pstParams->top.pos_y0,pstParams->top.pos_x1,pstParams->top.pos_y1,\
		pstParams->bottom.pos_x0,pstParams->bottom.pos_y0,pstParams->bottom.pos_x1,pstParams->bottom.pos_y1,\
		pstParams->left.pos_x0,pstParams->left.pos_y0,pstParams->left.pos_x1,pstParams->left.pos_y1,\
		pstParams->right.pos_x0,pstParams->right.pos_y0,pstParams->right.pos_x1,pstParams->right.pos_y1,\
		pstParams->tb_ratio,pstParams->ss_ratio);
	} while (0);
	return ret;
}
int PE_WIN_HW_L9_SetD3dDceHistoWin(void)
{
	int ret = RET_OK;
	LX_PE_OUT_TYPE out_type;
	UINT32 act_l_x0,act_l_y0,act_l_x1,act_l_y1;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	do {
		if(PE_KDRV_VER_L9BX)
		{
			out_type = pCfg->out_type;
			act_l_x0 = pCfg->act_x0;
			act_l_y0 = pCfg->act_y0;
			act_l_x1 = pCfg->act_x1;
			act_l_y1 = pCfg->act_y1;
			PE_WIN_HW_L9_DBG_PRINT("get : out_type:%d, act_l_x0,y0,x1,y1 : %d,%d,%d,%d\n",\
				out_type,act_l_x0,act_l_y0,act_l_x1,act_l_y1);

			if(out_type==LX_PE_OUT_TB)
			{
				act_l_y0 += PE_WIN_HW_L9_FHD_V_HALF;
				act_l_y1 += PE_WIN_HW_L9_FHD_V_HALF;
			}
			else if(out_type==LX_PE_OUT_SS)
			{
				act_l_x0 += PE_WIN_HW_L9_FHD_H_HALF;
				act_l_x1 += PE_WIN_HW_L9_FHD_H_HALF;
			}
			PE_P1R_L9B_QWr02(pe1_r_win2_ctrl_01,win_w0_x0,	act_l_x0,\
            									win_w0_y0,	act_l_y0);
			PE_P1R_L9B_QWr02(pe1_r_win2_ctrl_02,win_w0_x1,	act_l_x1,\
            									win_w0_y1,	act_l_y1);

			PE_WIN_HW_L9_DBG_PRINT("set : out_type:%d, act_l_x0,y0,x1,y1 : %d,%d,%d,%d\n",\
				out_type,act_l_x0,act_l_y0,act_l_x1,act_l_y1);
		}
		else
		{
			PE_WIN_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}
int PE_WIN_HW_L9_SetLrcrInOutSel(void)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	do {
		if(PE_KDRV_VER_L9BX)
		{
			if(pCfg->out_type==LX_PE_OUT_2D)
			{
				PE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_hist_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_hist_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_proc_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_proc_data_sel,	0x0);	//L data
				//PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	ff_mode_en,			0x0);	//ff md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_out_data_sel,		0x1);	//R data, dont care
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_out_data_sel,		0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_rd_en,			0x0);	//rd md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_mode,			0x3);	//32 bin
				PE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
			}
			else if(pCfg->out_type==LX_PE_OUT_TB || pCfg->out_type==LX_PE_OUT_SS)
			{
				PE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_hist_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_hist_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_proc_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_proc_data_sel,	0x0);	//L data
				//PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	ff_mode_en,			0x0);	//ff md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_out_data_sel,		0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_out_data_sel,		0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_rd_en,			0x0);	//rd md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_mode,			0x0);	//256 bin
				PE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
			}
			else if(pCfg->out_type==LX_PE_OUT_FS || pCfg->out_type==LX_PE_OUT_DUAL_TB || \
				pCfg->out_type==LX_PE_OUT_DUAL_SS || pCfg->out_type==LX_PE_OUT_DUAL_FULL || \
				pCfg->out_type==LX_PE_OUT_PIP)
			{
				PE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_hist_data_sel,	0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_hist_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_proc_data_sel,	0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_proc_data_sel,	0x0);	//L data
				//PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	ff_mode_en,			0x0);	//ff md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_out_data_sel,		0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_out_data_sel,		0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_rd_en,			0x0);	//rd md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_mode,			0x0);	//256 bin
				PE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
			}
			else if(pCfg->out_type==LX_PE_OUT_UD)
			{
				if(pCfg->tp_mode)
				{
					PE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_hist_data_sel,	0x0);	//L data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_hist_data_sel,	0x0);	//L data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_proc_data_sel,	0x0);	//L data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_proc_data_sel,	0x0);	//L data
					//PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	ff_mode_en,			0x0);	//ff md off
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_out_data_sel,		0x1);	//R data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_out_data_sel,		0x1);	//R data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_rd_en,			0x0);	//rd md off
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_mode,			0x0);	//256 bin
					PE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
				}
				else
				{
					PE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_hist_data_sel,	0x1);	//R data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_hist_data_sel,	0x0);	//L data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_proc_data_sel,	0x1);	//R data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_proc_data_sel,	0x0);	//L data
					//PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	ff_mode_en,			0x0);	//ff md off
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_out_data_sel,		0x1);	//R data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_out_data_sel,		0x0);	//L data
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_rd_en,			0x0);	//rd md off
					PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_mode,			0x0);	//256 bin
					PE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
				}
			}
			else	// etc.
			{
				PE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_hist_data_sel,	0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_hist_data_sel,	0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_proc_data_sel,	0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_proc_data_sel,	0x0);	//L data
				//PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	ff_mode_en,			0x0);	//ff md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	r_out_data_sel,		0x1);	//R data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	l_out_data_sel,		0x0);	//L data
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_rd_en,			0x0);	//rd md off
				PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,	hist_mode,			0x0);	//256 bin
				PE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
			}
		}
		else
		{
			PE_WIN_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}
int PE_WIN_HW_L9_SetLrcrWin(LX_PE_OUT_TYPE detect_type, PE_WIN_HW_L9_POS win_pos)
{
	int ret = RET_OK;
	LX_PE_OUT_TYPE cur_out_type;
	UINT32 act_l_x0,act_l_y0,act_l_x1,act_l_y1;
	UINT32 top_act_l_x0, top_act_l_y0, top_act_l_x1, top_act_l_y1;
	UINT32 bottom_act_l_x0, bottom_act_l_y0, bottom_act_l_x1, bottom_act_l_y1;
	UINT32 left_act_l_x0, left_act_l_y0, left_act_l_x1, left_act_l_y1;
	UINT32 right_act_l_x0, right_act_l_y0, right_act_l_x1, right_act_l_y1;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	PE_WIN_HW_L9_SETTINGS_T *pInfo=&_g_pe_win_hw_l9_info;
	do {
		if(PE_KDRV_VER_L9BX)
		{
			cur_out_type = pCfg->out_type;
			act_l_x0 = pCfg->act_x0;
			act_l_y0 = pCfg->act_y0;
			act_l_x1 = pCfg->act_x1;
			act_l_y1 = pCfg->act_y1;

			top_act_l_x0 = pInfo->d3d_info.top.pos_x0;
			top_act_l_y0 = pInfo->d3d_info.top.pos_y0;
			top_act_l_x1 = pInfo->d3d_info.top.pos_x1;
			top_act_l_y1 = pInfo->d3d_info.top.pos_y1;

			bottom_act_l_x0 = pInfo->d3d_info.bottom.pos_x0;
			bottom_act_l_y0 = pInfo->d3d_info.bottom.pos_y0;
			bottom_act_l_x1 = pInfo->d3d_info.bottom.pos_x1;
			bottom_act_l_y1 = pInfo->d3d_info.bottom.pos_y1;

			left_act_l_x0 = pInfo->d3d_info.left.pos_x0;
			left_act_l_y0 = pInfo->d3d_info.left.pos_y0;
			left_act_l_x1 = pInfo->d3d_info.left.pos_x1;
			left_act_l_y1 = pInfo->d3d_info.left.pos_y1;

			right_act_l_x0 = pInfo->d3d_info.right.pos_x0;
			right_act_l_y0 = pInfo->d3d_info.right.pos_y0;
			right_act_l_x1 = pInfo->d3d_info.right.pos_x1;
			right_act_l_y1 = pInfo->d3d_info.right.pos_y1;

			
			if(act_l_x1>PE_WIN_HW_L9_FHD_H_MAX)	act_l_x1=PE_WIN_HW_L9_FHD_H_MAX;
			if(act_l_y1>PE_WIN_HW_L9_FHD_V_MAX)	act_l_y1=PE_WIN_HW_L9_FHD_V_MAX;

			if(top_act_l_x1>PE_WIN_HW_L9_FHD_H_MAX)			top_act_l_x1=PE_WIN_HW_L9_FHD_H_MAX;
			if(top_act_l_y1>(PE_WIN_HW_L9_FHD_V_MAX>>1) )	    top_act_l_y1=(PE_WIN_HW_L9_FHD_V_MAX>>1);

			if(bottom_act_l_x1>PE_WIN_HW_L9_FHD_H_MAX)		bottom_act_l_x1=PE_WIN_HW_L9_FHD_H_MAX;
			if(bottom_act_l_y1>PE_WIN_HW_L9_FHD_V_MAX)		bottom_act_l_y1=PE_WIN_HW_L9_FHD_V_MAX;

			if(left_act_l_x1>(PE_WIN_HW_L9_FHD_H_MAX>>1))	    left_act_l_x1=(PE_WIN_HW_L9_FHD_H_MAX>>1);
			if(left_act_l_y1>PE_WIN_HW_L9_FHD_V_MAX )	        left_act_l_y1=PE_WIN_HW_L9_FHD_V_MAX;

			if(right_act_l_x1>PE_WIN_HW_L9_FHD_H_MAX)	        right_act_l_x1=PE_WIN_HW_L9_FHD_H_MAX;
			if(right_act_l_y1>PE_WIN_HW_L9_FHD_V_MAX)			right_act_l_y1=PE_WIN_HW_L9_FHD_V_MAX;
			
			if(cur_out_type==LX_PE_OUT_2D)
			{
				if(detect_type == LX_PE_OUT_TB)
				{
					if(win_pos == PE_WIN_LRTB_FULL)
					{
					/* L data:(0,0)~(1920,540), R data:(0,540)~(1920,1080) */
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		top_act_l_x0,\
															y0,		top_act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		top_act_l_x1,\
															y1,		top_act_l_y1);
					
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		bottom_act_l_x0,\
															y0,		bottom_act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		bottom_act_l_x1,\
															y1,		bottom_act_l_y1);
					
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0, 	act_l_x0,\
															y0, 	act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1, 	act_l_x1,\
															y1, 	act_l_y1);

//				    printk(" **********(PE_WIN_LRTB_FULL/TB) top_act_l_x0 = %d, top_act_l_y0 = %d, top_act_l_x1 = %d, top_act_l_y1 = %d *********\n", top_act_l_x0, top_act_l_y0, top_act_l_x1, top_act_l_y1);
//					printk(" **********(PE_WIN_LRTB_FULL/TB) bottom_act_l_x0 = %d, bottom_act_l_y0 = %d, bottom_act_l_x1 = %d, bottom_act_l_y1 = %d *********\n", bottom_act_l_x0, bottom_act_l_y0, bottom_act_l_x1, bottom_act_l_y1);
										
				}
					else if(win_pos == PE_WIN_LRTB_HAF1)
					{
						/* L data:(0,0)~(1920,270), R data:(0,540)~(1920,810) */
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		top_act_l_x0,\
																y0,		top_act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		top_act_l_x1,\
																y1,		top_act_l_y0 + ((top_act_l_y1 - top_act_l_y0)>>1) );										
																
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		bottom_act_l_x0,\
																y0,		bottom_act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		bottom_act_l_x1,\
																y1,		bottom_act_l_y0 + ((bottom_act_l_y1 - bottom_act_l_y0)>>1) );
						
						
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0, 	act_l_x0,\
																y0, 	act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1, 	act_l_x1,\
																y1, 	act_l_y1);

//						printk(" **********(PE_WIN_LRTB_HAF1/TB) top_act_l_x0 = %d, top_act_l_y0 = %d, top_act_l_x1 = %d, top_act_l_y1 = %d *********\n", top_act_l_x0, top_act_l_y0, top_act_l_x1, top_act_l_y0 + ((top_act_l_y1 - top_act_l_y0)>>1));
//						printk(" **********(PE_WIN_LRTB_HAF1/TB) bottom_act_l_x0 = %d, bottom_act_l_y0 = %d, bottom_act_l_x1 = %d, bottom_act_l_y1 = %d *********\n", bottom_act_l_x0, bottom_act_l_y0, bottom_act_l_x1, bottom_act_l_y0 + ((bottom_act_l_y1 - bottom_act_l_y0)>>1));
					
					}
					else if(win_pos == PE_WIN_LRTB_HAF2)
					{
						/* L data:(0,270)~(1920,540), R data:(0,810)~(1920,1080) */
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		top_act_l_x0,\
																y0,		top_act_l_y0 + ((top_act_l_y1 - top_act_l_y0)>>1) );
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		top_act_l_x1,\
																y1,		top_act_l_y1);										
						
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		bottom_act_l_x0,\
																y0,		bottom_act_l_y0 + ((bottom_act_l_y1 - bottom_act_l_y0)>>1) );
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		bottom_act_l_x1,\
																y1,		bottom_act_l_y1);
						
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0, 	act_l_x0,\
																y0, 	act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1, 	act_l_x1,\
																y1, 	act_l_y1);
//						printk(" **********(PE_WIN_LRTB_HAF2/TB) top_act_l_x0 = %d, top_act_l_y0 = %d, top_act_l_x1 = %d, top_act_l_y1 = %d *********\n", top_act_l_x0, top_act_l_y0 + ((top_act_l_y1 - top_act_l_y0)>>1), top_act_l_x1, top_act_l_y1);
//						printk(" **********(PE_WIN_LRTB_HAF2/TB) bottom_act_l_x0 = %d, bottom_act_l_y0 = %d, bottom_act_l_x1 = %d, bottom_act_l_y1 = %d *********\n", bottom_act_l_x0, bottom_act_l_y0 + ((bottom_act_l_y1 - bottom_act_l_y0)>>1), bottom_act_l_x1, bottom_act_l_y1);
					}
				}
				else if(detect_type == LX_PE_OUT_SS)
				{
					if(win_pos == PE_WIN_LRTB_FULL)
					{
					/* L data:(0,0)~(960,1080), R data:(960,0)~(1920,1080) */
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		left_act_l_x0,\
															y0,		left_act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		left_act_l_x1,\
															y1,		left_act_l_y1);										
					
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		right_act_l_x0,\
															y0,		right_act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		right_act_l_x1,\
															y1,		right_act_l_y1);										
					
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0, 	act_l_x0,\
															y0, 	act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1, 	act_l_x1,\
															y1, 	act_l_y1);

//				    printk(" **********(PE_WIN_LRTB_FULL/SS) left_act_l_x0 = %d, left_act_l_y0 = %d, left_act_l_x1 = %d, left_act_l_y1 = %d *********\n", left_act_l_x0, left_act_l_y0, left_act_l_x1, left_act_l_y1);
//					printk(" **********(PE_WIN_LRTB_FULL/SS) right_act_l_x0 = %d, right_act_l_y0 = %d, right_act_l_x1 = %d, right_act_l_y1 = %d *********\n", right_act_l_x0, right_act_l_y0, right_act_l_x1, right_act_l_y1);
															
				}
					else if(win_pos == PE_WIN_LRTB_HAF1)
					{
						/* L data:(0,0)~(960,540), R data:(960,0)~(1920,540) */
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		left_act_l_x0,\
																y0,		left_act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		left_act_l_x1,\
																y1,		left_act_l_y0 + ((left_act_l_y1-left_act_l_y0) >>1) );										
																
						
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		right_act_l_x0,\
																y0,		right_act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		right_act_l_x1,\
																y1,		right_act_l_y0 + ((right_act_l_y1-right_act_l_y0) >>1) );																				
						
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0, 	act_l_x0,\
																y0, 	act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1, 	act_l_x1,\
																y1, 	act_l_y1);					

//						printk(" **********(PE_WIN_LRTB_HAF1/SS) left_act_l_x0 = %d, left_act_l_y0 = %d, left_act_l_x1 = %d, left_act_l_y1 = %d *********\n", left_act_l_x0, left_act_l_y0, left_act_l_x1, left_act_l_y0 + ((left_act_l_y1-left_act_l_y0) >>1));
//						printk(" **********(PE_WIN_LRTB_HAF1/SS) right_act_l_x0 = %d, right_act_l_y0 = %d, right_act_l_x1 = %d, right_act_l_y1 = %d *********\n", right_act_l_x0, right_act_l_y0, right_act_l_x1, right_act_l_y0 + ((right_act_l_y1-right_act_l_y0) >>1));
					}
					else if(win_pos == PE_WIN_LRTB_HAF2)
					{
						/* L data:(0,540)~(960,1080), R data:(960,540)~(1920,1080) */
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		left_act_l_x0,\
																y0,		left_act_l_y0 + ((left_act_l_y1 - left_act_l_y0) >>1) );
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		left_act_l_x1,\
																y1,		left_act_l_y1);										
						
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		right_act_l_x0,\
																y0,		right_act_l_y0 + ((right_act_l_y1 - right_act_l_y0) >>1) );
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		right_act_l_x1,\
																y1,		right_act_l_y1);												
						
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0, 	act_l_x0,\
																y0, 	act_l_y0);
						PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1, 	act_l_x1,\
																y1, 	act_l_y1);					
//						printk(" **********(PE_WIN_LRTB_HAF2/SS) left_act_l_x0 = %d, left_act_l_y0 = %d, left_act_l_x1 = %d, left_act_l_y1 = %d *********\n", left_act_l_x0, left_act_l_y0 + ((left_act_l_y1 - left_act_l_y0) >>1), left_act_l_x1, left_act_l_y1);
//						printk(" **********(PE_WIN_LRTB_HAF2/SS) right_act_l_x0 = %d, right_act_l_y0 = %d, right_act_l_x1 = %d, right_act_l_y1 = %d *********\n", right_act_l_x0, right_act_l_y0 + ((right_act_l_y1 - right_act_l_y0) >>1), right_act_l_x1, right_act_l_y1);
												

					}
				}
				else
				{
					/* L:(0,0)~(1920,1080), R:(0,0)~(1920,1080) */
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0, 	act_l_x0,\
															y0, 	act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1, 	act_l_x1,\
															y1, 	act_l_y1);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0, 	act_l_x0,\
															y0, 	act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1, 	act_l_x1,\
															y1, 	act_l_y1);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0, 	act_l_x0,\
															y0, 	act_l_y0);
					PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1, 	act_l_x1,\
															y1, 	act_l_y1);
				}

			}
			else if(cur_out_type==LX_PE_OUT_TB)
			{
				/* L:(0,0)~(1920,540), R:(0,540)~(1920,1080) */
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_HALF);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		0,\
														y0,		(PE_WIN_HW_L9_FHD_V_HALF));
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0,		0,\
														y0,		(PE_WIN_HW_L9_FHD_V_HALF));
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
			}
			else if(cur_out_type==LX_PE_OUT_SS)
			{
				/* L:(0,0)~(960,1080), R:(960,0)~(1920,1080) */
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		PE_WIN_HW_L9_FHD_H_HALF,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		(PE_WIN_HW_L9_FHD_H_HALF),\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0,		(PE_WIN_HW_L9_FHD_H_HALF),\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
			}
			else if(cur_out_type==LX_PE_OUT_UD)
			{
				/* L:(0,0)~(1920,2160), R:(0,0)~(1920,2160) */
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		(PE_WIN_HW_L9_FHD_V_MAX<<1));
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		(PE_WIN_HW_L9_FHD_V_MAX<<1));
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		(PE_WIN_HW_L9_FHD_V_MAX<<1));
			}
			else if(cur_out_type==LX_PE_OUT_FS ||  cur_out_type==LX_PE_OUT_DUAL_TB || \
				cur_out_type==LX_PE_OUT_DUAL_SS || cur_out_type==LX_PE_OUT_DUAL_FULL )
			{
				/* L,R: according to output window */
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		act_l_x0,\
														y0,		act_l_y0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		act_l_x1,\
														y1,		act_l_y1);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		act_l_x0,\
														y0,		act_l_y0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		act_l_x1,\
														y1,		act_l_y1);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0,		act_l_x0,\
														y0,		act_l_y0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1,		act_l_x1,\
														y1,		act_l_y1);
			}
			else	// LX_PE_OUT_3D_2D || LX_PE_OUT_PIP || LX_PE_OUT_2D_3D
			{
				/* L:(0,0)~(1920,1080), R:(0,0)~(1920,1080) */
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_02,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_03,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_04,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_05,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_06,	x0,		0,\
														y0,		0);
				PE_P1L_L9B_QWr02(pe1_l_lrcr_ctrl_07,	x1,		PE_WIN_HW_L9_FHD_H_MAX,\
														y1,		PE_WIN_HW_L9_FHD_V_MAX);
			}
		}
		else
		{
			PE_WIN_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}
int PE_WIN_HW_L9_GetCurWinSettings(PE_WIN_HW_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_WIN_HW_L9_SETTINGS_T *pInfo=&_g_pe_win_hw_l9_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9)
		{
			memcpy(pstParams,pInfo,sizeof(PE_WIN_HW_L9_SETTINGS_T));
			if(_g_win_hw_l9_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_WIN_HW_L9_DBG_PRINT("get pstParams[0] : act0_x,y:%d,%d,%d,%d,ratio:tb:%d,ss:%d\n",\
						pstParams->win_inf[LX_PE_WIN_0].act0_x0,pstParams->win_inf[LX_PE_WIN_0].act0_y0,\
						pstParams->win_inf[LX_PE_WIN_0].act0_x1,pstParams->win_inf[LX_PE_WIN_0].act0_y1,\
						pstParams->d3d_info.tb_ratio,pstParams->d3d_info.ss_ratio);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_WIN_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}

