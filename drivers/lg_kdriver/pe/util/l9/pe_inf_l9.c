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


/** @file pe_inf_l9.c
 *
 *  information management for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.15
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
#include <linux/kthread.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "pe_cfg.h"
#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc.h"
#include "pe_ccm.h"
#include "pe_etc_hw.h"
#include "pe_dcm_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_INF_L9_SCL_RESIZE_H_MAX	960		/* 1920 * 0.5 */
#define PE_INF_L9_SCL_RESIZE_V_MAX	540		/* 1080 * 0.5 */
#define PE_INF_L9_SCL_IS_HD_MIN		1024

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_INF_L9_ERROR	printk

#define PE_INF_L9_DBG_PRINT(fmt,args...)	\
	if(_g_pe_inf_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_INF_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_INF_L9_ERROR(fmt,##args);_action;}}

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
static UINT32 _g_pe_inf_l9_trace=0x0;		//default should be off.
static PE_INF_L9_SETTINGS_T _g_pe_inf_hw_l9_info;

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
void PE_INF_L9_SetDbgPrint(UINT32 on_off)
{
	_g_pe_inf_l9_trace = on_off? 1:0;
	return;
}
/**
 * init inf
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_L9_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			PE_INF_L9_DBG_PRINT("init global values.\n");
			memset0(_g_pe_inf_hw_l9_info);
		}
		else
		{
			PE_INF_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
int PE_INF_L9_SetDispInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_l9_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_l9_info.disp_info[LX_PE_WIN_1];
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_INF_L9_DBG_PRINT("set[%d] : src:%d,fmt:%d,out:%d,fr:%d,scan:%d,dtv:%d,3d_in:%d\n",\
			pstParams->win_id,pstParams->src_type,pstParams->fmt_type,pstParams->out_type,\
			pstParams->fr_type,pstParams->scan_type,pstParams->dtv_type,pstParams->in_type);
		if(PE_KDRV_VER_L9)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(disp0_info,pstParams,sizeof(LX_PE_INF_DISPLAY_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(disp1_info,pstParams,sizeof(LX_PE_INF_DISPLAY_T));
			}
		}
		else
		{
			PE_INF_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
int PE_INF_L9_CheckSclInfo(void)
{
	int ret = RET_OK;
	UINT32 r_data;
	PE_D3D_CFG_T *pD3dCfg = &d3d_info.cfg;
	PE_INF_L9_CTRL_T *ctrl0_info = &_g_pe_inf_hw_l9_info.ctrl_info[LX_PE_WIN_0];
	PE_INF_L9_CTRL_T *ctrl1_info = &_g_pe_inf_hw_l9_info.ctrl_info[LX_PE_WIN_1];
	PE_DCM_HW_L9_SETTINGS_T dcm_info;
	PE_CCM_SETTINGS_T ccm_info;
	do {
		if(PE_KDRV_VER_L9BX)
		{
			ret = PE_CCM_GetCurCcmSettings(&ccm_info);
			if(ret)	{PE_INF_L9_ERROR("[%s,%d] PE_CCM_GetCurCcmSettings() error.\n",__F__,__L__);}
			ret = PE_DCM_HW_L9_GetCurDcmSettings(&dcm_info);
			if(ret)	{PE_INF_L9_ERROR("[%s,%d] PE_DCM_HW_L9_GetCurDcmSettings() error.\n",__F__,__L__);}
			/* L */
	        PE_MSL_L9_RdFL(msc_scr_size_l);
	        PE_MSL_L9_RdFL(msc_win_in_offset_l);
	        PE_MSL_L9_RdFL(msc_win_in_size_l);
	        PE_MSL_L9_RdFL(msc_win_out_size_l);
	        PE_MSL_L9_RdFL(msc_c_format_l);
	        PE_MSL_L9_Rd01(msc_scr_size_l,		input_h_size,		ctrl0_info->scl_src_h);
	        PE_MSL_L9_Rd01(msc_scr_size_l,		input_v_size,		ctrl0_info->scl_src_v);
	        PE_MSL_L9_Rd01(msc_win_in_offset_l,	in_win_h_offset,	ctrl0_info->i_win_h_ofst);
	        PE_MSL_L9_Rd01(msc_win_in_offset_l,	in_win_v_offset,	ctrl0_info->i_win_v_ofst);
	        PE_MSL_L9_Rd01(msc_win_in_size_l,	in_win_h_size,		ctrl0_info->i_win_h_size);
	        PE_MSL_L9_Rd01(msc_win_in_size_l,	in_win_v_size,		ctrl0_info->i_win_v_size);
	        PE_MSL_L9_Rd01(msc_win_out_size_l,	out_win_h_size,		ctrl0_info->o_win_h_size);
	        PE_MSL_L9_Rd01(msc_win_out_size_l,	out_win_v_size,		ctrl0_info->o_win_v_size);
	        PE_MSL_L9_Rd01(msc_c_format_l,		in_c_format,		r_data);
			ctrl0_info->is_yuv444 = (r_data==6)? 0x1:0x0;	//"100":yuv420,"101":yuv422,"110":yuv444
			PE_OVL_L9B0_RdFL(ovl_ov_moffset);
			PE_OVL_L9B0_RdFL(ovl_ov_msize);
			PE_OVL_L9B0_Rd01(ovl_ov_moffset, m_hoffset,	ctrl0_info->m_win_h_ofst);
			PE_OVL_L9B0_Rd01(ovl_ov_moffset, m_voffset,	ctrl0_info->m_win_v_ofst);
			PE_OVL_L9B0_Rd01(ovl_ov_msize, m_hsize,		ctrl0_info->m_win_h_size);
			PE_OVL_L9B0_Rd01(ovl_ov_msize, m_vsize,		ctrl0_info->m_win_v_size);
			PE_P0L_L9B_QRd02(pe0_src_size,	hsize,	ctrl0_info->pe0_src_h,	vsize,	ctrl0_info->pe0_src_v);
			ctrl0_info->scl_resize = (ctrl0_info->o_win_h_size<PE_INF_L9_SCL_RESIZE_H_MAX && \
								ctrl0_info->o_win_v_size<PE_INF_L9_SCL_RESIZE_V_MAX)? 1:0;
			ctrl0_info->scl_hd = (ctrl0_info->scl_src_h>=PE_INF_L9_SCL_IS_HD_MIN)? 1:0;
			/* R */
	        PE_MSR_L9_RdFL(msc_scr_size_r);
	        PE_MSR_L9_RdFL(msc_win_in_offset_r);
	        PE_MSR_L9_RdFL(msc_win_in_size_r);
	        PE_MSR_L9_RdFL(msc_win_out_size_r);
	        PE_MSR_L9_RdFL(msc_c_format_r);
	        PE_MSR_L9_Rd01(msc_scr_size_r,		input_h_size,		ctrl1_info->scl_src_h);
	        PE_MSR_L9_Rd01(msc_scr_size_r,		input_v_size,		ctrl1_info->scl_src_v);
	        PE_MSR_L9_Rd01(msc_win_in_offset_r,	in_win_h_offset,	ctrl1_info->i_win_h_ofst);
	        PE_MSR_L9_Rd01(msc_win_in_offset_r,	in_win_v_offset,	ctrl1_info->i_win_v_ofst);
	        PE_MSR_L9_Rd01(msc_win_in_size_r,	in_win_h_size,		ctrl1_info->i_win_h_size);
	        PE_MSR_L9_Rd01(msc_win_in_size_r,	in_win_v_size,		ctrl1_info->i_win_v_size);
	        PE_MSR_L9_Rd01(msc_win_out_size_r,	out_win_h_size,		ctrl1_info->o_win_h_size);
	        PE_MSR_L9_Rd01(msc_win_out_size_r,	out_win_v_size,		ctrl1_info->o_win_v_size);
	        PE_MSR_L9_Rd01(msc_c_format_r,		in_c_format,		r_data);
			ctrl1_info->is_yuv444 = (r_data==6)? 0x1:0x0;	//"100":yuv420,"101":yuv422,"110":yuv444
			PE_OVR_L9B0_RdFL(ovr_ov_moffset);
			PE_OVR_L9B0_RdFL(ovr_ov_msize);
			PE_OVR_L9B0_Rd01(ovr_ov_moffset, m_hoffset,	ctrl1_info->m_win_h_ofst);
			PE_OVR_L9B0_Rd01(ovr_ov_moffset, m_voffset,	ctrl1_info->m_win_v_ofst);
			PE_OVR_L9B0_Rd01(ovr_ov_msize, m_hsize,		ctrl1_info->m_win_h_size);
			PE_OVR_L9B0_Rd01(ovr_ov_msize, m_vsize,		ctrl1_info->m_win_v_size);
			PE_P0R_L9B_QRd02(pe0_src_size,	hsize,	ctrl1_info->pe0_src_h,	vsize,	ctrl1_info->pe0_src_v);
			ctrl1_info->scl_resize = (ctrl1_info->o_win_h_size<PE_INF_L9_SCL_RESIZE_H_MAX && \
								ctrl1_info->o_win_v_size<PE_INF_L9_SCL_RESIZE_V_MAX)? 1:0;
			ctrl1_info->scl_hd = (ctrl1_info->scl_src_h>=PE_INF_L9_SCL_IS_HD_MIN)? 1:0;
			/* etc */
			ctrl0_info->d3d_chk = pD3dCfg->d3d_chk;
			ctrl0_info->auto_cr_en = ccm_info.auto_cr.enable? 1:0;
			ctrl0_info->sat_status = dcm_info.histo_info[LX_PE_WIN_0].sat_status;
			ctrl0_info->mute_on = ctrl1_info->mute_on = 0;
		}
		else
		{
			PE_INF_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
int PE_INF_L9_GetCurInfSettings(PE_INF_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_INF_L9_SETTINGS_T *pInfo=&_g_pe_inf_hw_l9_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9)
		{
			memcpy(pstParams,pInfo,sizeof(PE_INF_L9_SETTINGS_T));
			if(_g_pe_inf_l9_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_INF_L9_DBG_PRINT("disp[0] : src:%d,fmt:%d,out:%d,fr:%d,scan:%d,dtv:%d,3d_in:%d\n",\
						pstParams->disp_info[LX_PE_WIN_0].src_type,pstParams->disp_info[LX_PE_WIN_0].fmt_type,\
						pstParams->disp_info[LX_PE_WIN_0].out_type,pstParams->disp_info[LX_PE_WIN_0].fr_type,\
						pstParams->disp_info[LX_PE_WIN_0].scan_type,pstParams->disp_info[LX_PE_WIN_0].dtv_type,\
						pstParams->disp_info[LX_PE_WIN_0].in_type);
					PE_INF_L9_DBG_PRINT("scl [0] : in:%d,%d,scl:%d,%d,i_w:%d,%d,%d,%d,o_w:%d,%d,m_w:%d,%d,%d,%d,y444:%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_0].pe0_src_h,pInfo->ctrl_info[LX_PE_WIN_0].pe0_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_0].scl_src_h,pInfo->ctrl_info[LX_PE_WIN_0].scl_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_0].i_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_0].i_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_0].i_win_h_size,pInfo->ctrl_info[LX_PE_WIN_0].i_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_0].o_win_h_size,pInfo->ctrl_info[LX_PE_WIN_0].o_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_0].m_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_0].m_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_0].m_win_h_size,pInfo->ctrl_info[LX_PE_WIN_0].m_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_0].is_yuv444);
					PE_INF_L9_DBG_PRINT("disp[1] : src:%d,fmt:%d,out:%d,fr:%d,scan:%d,dtv:%d,3d_in:%d\n",\
						pstParams->disp_info[LX_PE_WIN_1].src_type,pstParams->disp_info[LX_PE_WIN_1].fmt_type,\
						pstParams->disp_info[LX_PE_WIN_1].out_type,pstParams->disp_info[LX_PE_WIN_1].fr_type,\
						pstParams->disp_info[LX_PE_WIN_1].scan_type,pstParams->disp_info[LX_PE_WIN_1].dtv_type,\
						pstParams->disp_info[LX_PE_WIN_1].in_type);
					PE_INF_L9_DBG_PRINT("scl [1] : in:%d,%d,scl:%d,%d,i_w:%d,%d,%d,%d,o_w:%d,%d,m_w:%d,%d,%d,%d,y444:%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_1].pe0_src_h,pInfo->ctrl_info[LX_PE_WIN_1].pe0_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_1].scl_src_h,pInfo->ctrl_info[LX_PE_WIN_1].scl_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_1].i_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_1].i_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_1].i_win_h_size,pInfo->ctrl_info[LX_PE_WIN_1].i_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_1].o_win_h_size,pInfo->ctrl_info[LX_PE_WIN_1].o_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_1].m_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_1].m_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_1].m_win_h_size,pInfo->ctrl_info[LX_PE_WIN_1].m_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_1].is_yuv444);
					PE_INF_L9_DBG_PRINT("\n");
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_INF_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}

