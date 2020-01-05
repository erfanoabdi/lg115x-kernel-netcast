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


/** @file pe_inf_h13.c
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
#include "pe_win_hw.h"
#include "pe_shp_hw.h"
#include "pe_ccm_hw.h"
#include "pe_dcm_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_INF_H13_SCL_RESIZE_H_MAX		960		/* 1920 * 0.5 */
#define PE_INF_H13_SCL_RESIZE_V_MAX		540		/* 1080 * 0.5 */
#define PE_INF_H13_SCL_IS_HD_MIN		1024

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_INF_H13_ERROR	printk

#define PE_INF_H13_DBG_PRINT(fmt,args...)	\
	if(_g_pe_inf_h13_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_INF_H13_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_INF_H13_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

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
static UINT32 _g_pe_inf_h13_trace=0x0;		//default should be off.
static PE_INF_H13_SETTINGS_T _g_pe_inf_hw_h13_info;

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
void PE_INF_H13_SetDbgPrint(UINT32 on_off)
{
	_g_pe_inf_h13_trace = on_off? 1:0;
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
int PE_INF_H13_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_H13)
		{
			PE_INF_H13_DBG_PRINT("init global values.\n");
			memset0(_g_pe_inf_hw_h13_info);
		}
		else
		{
			PE_INF_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set display info
 *
 * @param   *pstParams [in] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_H13_SetDispInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_H13_SRC_INFO fwi_src;
	LX_PE_INF_DISPLAY_T *disp0_info = &_g_pe_inf_hw_h13_info.disp_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp1_info = &_g_pe_inf_hw_h13_info.disp_info[LX_PE_WIN_1];
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_INF_H13_DBG_PRINT("set[%d] : src:%d,fmt:%d,out:%d,fr:%d(%d)\n"\
			"h,v:%d,%d,scan:%d,dtv:%d,hdd:%d,3d_in:%d\n",\
			pstParams->win_id,pstParams->src_type,pstParams->fmt_type,pstParams->out_type,\
			pstParams->fr_type,pstParams->in_f_rate,pstParams->in_h_size,pstParams->in_v_size,\
			pstParams->scan_type,pstParams->dtv_type,pstParams->hdd_type,pstParams->in_type);
		if(PE_KDRV_VER_H13)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(disp0_info,pstParams,sizeof(LX_PE_INF_DISPLAY_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(disp1_info,pstParams,sizeof(LX_PE_INF_DISPLAY_T));
			}
			/* sync parameters with no relationship to window */
			disp0_info->out_type	= disp1_info->out_type	= pstParams->out_type;
			disp0_info->hdd_type	= disp1_info->hdd_type	= pstParams->hdd_type;
			disp0_info->in_type		= disp1_info->in_type	= pstParams->in_type;
			disp0_info->mode		= disp1_info->mode		= pstParams->mode;
			/* sync parameters when all win case(ud,3d) */
			if(pstParams->win_id==LX_PE_WIN_ALL)
			{
				disp0_info->src_type	= disp1_info->src_type	= pstParams->src_type;
				disp0_info->fmt_type	= disp1_info->fmt_type	= pstParams->fmt_type;
				disp0_info->fr_type		= disp1_info->fr_type	= pstParams->fr_type;
				disp0_info->scan_type	= disp1_info->scan_type	= pstParams->scan_type;
				disp0_info->dtv_type	= disp1_info->dtv_type	= pstParams->dtv_type;
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				fwi_src.dtv_mode = pstParams->dtv_type;
				fwi_src.hdd_mode = pstParams->hdd_type;
				ret = PE_FWI_H13_SetSrcInfo(&fwi_src);
				PE_INF_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetSrcInfo() error.\n",__F__,__L__);
			}
		}
		else
		{
			PE_INF_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * check(get) scaler info.
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_H13_CheckSclInfo(void)
{
	int ret = RET_OK;
	UINT32 r_data;
	PE_INF_H13_CTRL_T *ctrl0_info = &_g_pe_inf_hw_h13_info.ctrl_info[LX_PE_WIN_0];
	PE_INF_H13_CTRL_T *ctrl1_info = &_g_pe_inf_hw_h13_info.ctrl_info[LX_PE_WIN_1];
	PE_CCM_SETTINGS_T ccm_info;
	do {
		if(PE_KDRV_VER_H13BX)
		{
			ret = PE_CCM_GetCurCcmSettings(&ccm_info);
			if(ret)	{PE_INF_H13_ERROR("[%s,%d] PE_CCM_GetCurCcmSettings() error.\n",__F__,__L__);}
			/* L */
	        PE_MSL_H13B0_RdFL(msc_scr_size_l);
	        PE_MSL_H13B0_RdFL(msc_win_in_offset_l);
	        PE_MSL_H13B0_RdFL(msc_win_in_size_l);
	        PE_MSL_H13B0_RdFL(msc_win_out_size_l);
	        PE_MSL_H13B0_RdFL(msc_c_format_l);
	        PE_MSL_H13B0_Rd01(msc_scr_size_l, 		input_h_size,		ctrl0_info->scl_src_h);
	        PE_MSL_H13B0_Rd01(msc_scr_size_l, 		input_v_size,		ctrl0_info->scl_src_v);
	        PE_MSL_H13B0_Rd01(msc_win_in_offset_l, 	in_win_h_offset,	ctrl0_info->i_win_h_ofst);
	        PE_MSL_H13B0_Rd01(msc_win_in_offset_l, 	in_win_v_offset,	ctrl0_info->i_win_v_ofst);
	        PE_MSL_H13B0_Rd01(msc_win_in_size_l, 	in_win_h_size,		ctrl0_info->i_win_h_size);
	        PE_MSL_H13B0_Rd01(msc_win_in_size_l, 	in_win_v_size,		ctrl0_info->i_win_v_size);
	        PE_MSL_H13B0_Rd01(msc_win_out_size_l, 	out_win_h_size,		ctrl0_info->o_win_h_size);
	        PE_MSL_H13B0_Rd01(msc_win_out_size_l, 	out_win_v_size,		ctrl0_info->o_win_v_size);
	        PE_MSL_H13B0_Rd01(msc_c_format_l, 		in_c_format,		r_data);
			ctrl0_info->is_yuv444 = (r_data==0x6)? 0x1:0x0;	//"100":yuv420,"101":yuv422,"110":yuv444
			PE_OVL_H13B0_RdFL(ovl_ov_moffset);
			PE_OVL_H13B0_RdFL(ovl_ov_msize);
			PE_OVL_H13B0_Rd01(ovl_ov_moffset, 		m_hoffset,			ctrl0_info->m_win_h_ofst);
			PE_OVL_H13B0_Rd01(ovl_ov_moffset, 		m_voffset,			ctrl0_info->m_win_v_ofst);
			PE_OVL_H13B0_Rd01(ovl_ov_msize, 		m_hsize,			ctrl0_info->m_win_h_size);
			PE_OVL_H13B0_Rd01(ovl_ov_msize, 		m_vsize,			ctrl0_info->m_win_v_size);
			PE_P0L_H13B0_RdFL(p0l_pe0_src_size);
			PE_P0L_H13B0_Rd01(p0l_pe0_src_size, 	hsize,				ctrl0_info->pe0_src_h);
			PE_P0L_H13B0_Rd01(p0l_pe0_src_size, 	vsize,				ctrl0_info->pe0_src_v);
			ctrl0_info->scl_resize = (ctrl0_info->o_win_h_size<PE_INF_H13_SCL_RESIZE_H_MAX && \
								ctrl0_info->o_win_v_size<PE_INF_H13_SCL_RESIZE_V_MAX)? 1:0;
			ctrl0_info->scl_hd = (ctrl0_info->scl_src_h>=PE_INF_H13_SCL_IS_HD_MIN)? 1:0;
			/* R */
	        PE_MSR_H13B0_RdFL(msc_scr_size_r);
	        PE_MSR_H13B0_RdFL(msc_win_in_offset_r);
	        PE_MSR_H13B0_RdFL(msc_win_in_size_r);
	        PE_MSR_H13B0_RdFL(msc_win_out_size_r);
	        PE_MSR_H13B0_RdFL(msc_c_format_r);
	        PE_MSR_H13B0_Rd01(msc_scr_size_r, 		input_h_size,		ctrl1_info->scl_src_h);
	        PE_MSR_H13B0_Rd01(msc_scr_size_r,		input_v_size,		ctrl1_info->scl_src_v);
	        PE_MSR_H13B0_Rd01(msc_win_in_offset_r, 	in_win_h_offset,	ctrl1_info->i_win_h_ofst);
	        PE_MSR_H13B0_Rd01(msc_win_in_offset_r, 	in_win_v_offset,	ctrl1_info->i_win_v_ofst);
	        PE_MSR_H13B0_Rd01(msc_win_in_size_r, 	in_win_h_size,		ctrl1_info->i_win_h_size);
	        PE_MSR_H13B0_Rd01(msc_win_in_size_r, 	in_win_v_size,		ctrl1_info->i_win_v_size);
	        PE_MSR_H13B0_Rd01(msc_win_out_size_r, 	out_win_h_size,		ctrl1_info->o_win_h_size);
	        PE_MSR_H13B0_Rd01(msc_win_out_size_r, 	out_win_v_size,		ctrl1_info->o_win_v_size);
	        PE_MSR_H13B0_Rd01(msc_c_format_r,		in_c_format,		r_data);
			ctrl1_info->is_yuv444 = (r_data==0x6)? 0x1:0x0;	//"100":yuv420,"101":yuv422,"110":yuv444
			PE_OVR_H13B0_RdFL(ovr_ov_moffset);
			PE_OVR_H13B0_RdFL(ovr_ov_msize);
			PE_OVR_H13B0_Rd01(ovr_ov_moffset,		m_hoffset,			ctrl1_info->m_win_h_ofst);
			PE_OVR_H13B0_Rd01(ovr_ov_moffset,		m_voffset,			ctrl1_info->m_win_v_ofst);
			PE_OVR_H13B0_Rd01(ovr_ov_msize, 		m_hsize,			ctrl1_info->m_win_h_size);
			PE_OVR_H13B0_Rd01(ovr_ov_msize, 		m_vsize,			ctrl1_info->m_win_v_size);
			PE_P0R_H13B0_RdFL(p0r_pe0_src_size);
			PE_P0R_H13B0_Rd01(p0r_pe0_src_size,		hsize,				ctrl1_info->pe0_src_h);
			PE_P0R_H13B0_Rd01(p0r_pe0_src_size,		vsize,				ctrl1_info->pe0_src_v);
			ctrl1_info->scl_resize = (ctrl1_info->o_win_h_size<PE_INF_H13_SCL_RESIZE_H_MAX && \
								ctrl1_info->o_win_v_size<PE_INF_H13_SCL_RESIZE_V_MAX)? 1:0;
			ctrl1_info->scl_hd = (ctrl1_info->scl_src_h>=PE_INF_H13_SCL_IS_HD_MIN)? 1:0;
			/* sub scaler */
			PE_SSC_H13_RdFL(ssc_scr_size);
			PE_SSC_H13_RdFL(ssc_win_in_offset);
			PE_SSC_H13_RdFL(ssc_win_in_size);
			PE_SSC_H13_RdFL(ssc_win_out_size);
			PE_SSC_H13_Rd01(ssc_scr_size,			input_h_size,		ctrl0_info->ssc_src_h);
			PE_SSC_H13_Rd01(ssc_scr_size,			input_v_size,		ctrl0_info->ssc_src_v);
			PE_SSC_H13_Rd01(ssc_win_in_offset,		in_win_h_offset,	ctrl0_info->ssc_i_win_x);
			PE_SSC_H13_Rd01(ssc_win_in_offset,		in_win_v_offset,	ctrl0_info->ssc_i_win_y);
			PE_SSC_H13_Rd01(ssc_win_in_size,		in_win_h_size,		ctrl0_info->ssc_i_win_h);
			PE_SSC_H13_Rd01(ssc_win_in_size,		in_win_v_size,		ctrl0_info->ssc_i_win_v);
			PE_SSC_H13_Rd01(ssc_win_out_size,		out_win_h_size,		ctrl0_info->ssc_o_win_h);
			PE_SSC_H13_Rd01(ssc_win_out_size,		out_win_v_size,		ctrl0_info->ssc_o_win_v);
			ctrl1_info->ssc_src_h	= ctrl0_info->ssc_src_h;
			ctrl1_info->ssc_src_v	= ctrl0_info->ssc_src_v;
			ctrl1_info->ssc_i_win_x	= ctrl0_info->ssc_i_win_x;
			ctrl1_info->ssc_i_win_y	= ctrl0_info->ssc_i_win_y;
			ctrl1_info->ssc_i_win_h	= ctrl0_info->ssc_i_win_h;
			ctrl1_info->ssc_i_win_v	= ctrl0_info->ssc_i_win_v;
			ctrl1_info->ssc_o_win_h	= ctrl0_info->ssc_o_win_h;
			ctrl1_info->ssc_o_win_v	= ctrl0_info->ssc_o_win_v;
			/* etc */
			ctrl0_info->hv_same = (ctrl0_info->m_win_h_size==ctrl1_info->m_win_h_size && \
				ctrl0_info->m_win_v_size==ctrl1_info->m_win_v_size)? 1:0;
			ctrl1_info->hv_same = (ctrl0_info->m_win_h_size<=PE_INF_H13_SCL_RESIZE_H_MAX && \
				ctrl0_info->m_win_v_size<=PE_INF_H13_SCL_RESIZE_V_MAX)? 1:0;
			ret = PE_HST_HW_H13_GetDetected3dFmt(&r_data);
			if(ret)	{PE_INF_H13_ERROR("[%s,%d] PE_HST_HW_H13_GetDetected3dFmt() error.\n",__F__,__L__);}
			ctrl0_info->det_3df = r_data;
			ctrl0_info->auto_cr_en = ccm_info.auto_cr.enable? 1:0;
			ret = PE_HST_HW_H13_GetSaturationState(&r_data);
			if(ret)	{PE_INF_H13_ERROR("[%s,%d] PE_HST_HW_H13_GetSaturationState() error.\n",__F__,__L__);}
			ctrl0_info->sat_status = r_data;
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_03, pxl_rep_in,	ctrl0_info->mute_on);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_08, pxl_rep_in,	ctrl1_info->mute_on);
			PE_P1L_H13B0_QRd01(pe1_wb_ctrl_00,	reg_color_filter_status,	ctrl0_info->pxl_rp_st);
			PE_P1L_H13B0_QRd01(pe1_dse_ctrl_01,	reg_src_freeze,	ctrl0_info->is_src_frz);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			ret = PE_CCM_GetCurCcmSettings(&ccm_info);
			if(ret)	{PE_INF_H13_ERROR("[%s,%d] PE_CCM_GetCurCcmSettings() error.\n",__F__,__L__);}
			/* L */
	        PE_MSL_H13_RdFL(msc_scr_size_l);
	        PE_MSL_H13_RdFL(msc_win_in_offset_l);
	        PE_MSL_H13_RdFL(msc_win_in_size_l);
	        PE_MSL_H13_RdFL(msc_win_out_size_l);
	        PE_MSL_H13_RdFL(msc_c_format_l);
	        PE_MSL_H13_Rd01(msc_scr_size_l, 	input_h_size,		ctrl0_info->scl_src_h);
	        PE_MSL_H13_Rd01(msc_scr_size_l, 	input_v_size,		ctrl0_info->scl_src_v);
	        PE_MSL_H13_Rd01(msc_win_in_offset_l,in_win_h_offset,	ctrl0_info->i_win_h_ofst);
	        PE_MSL_H13_Rd01(msc_win_in_offset_l,in_win_v_offset,	ctrl0_info->i_win_v_ofst);
	        PE_MSL_H13_Rd01(msc_win_in_size_l, 	in_win_h_size,		ctrl0_info->i_win_h_size);
	        PE_MSL_H13_Rd01(msc_win_in_size_l, 	in_win_v_size,		ctrl0_info->i_win_v_size);
	        PE_MSL_H13_Rd01(msc_win_out_size_l, out_win_h_size,		ctrl0_info->o_win_h_size);
	        PE_MSL_H13_Rd01(msc_win_out_size_l, out_win_v_size,		ctrl0_info->o_win_v_size);
	        PE_MSL_H13_Rd01(msc_c_format_l, 	in_c_format,		r_data);
			ctrl0_info->is_yuv444 = (r_data==0x6)? 0x1:0x0;	//"100":yuv420,"101":yuv422,"110":yuv444
			PE_OVL_H13_RdFL(ovl_ov_moffset);
			PE_OVL_H13_RdFL(ovl_ov_msize);
			PE_OVL_H13_Rd01(ovl_ov_moffset, m_hoffset,	ctrl0_info->m_win_h_ofst);
			PE_OVL_H13_Rd01(ovl_ov_moffset, m_voffset,	ctrl0_info->m_win_v_ofst);
			PE_OVL_H13_Rd01(ovl_ov_msize, 	m_hsize,	ctrl0_info->m_win_h_size);
			PE_OVL_H13_Rd01(ovl_ov_msize, 	m_vsize,	ctrl0_info->m_win_v_size);
			PE_P0L_H13_RdFL(p0l_pe0_src_size);
			PE_P0L_H13_Rd01(p0l_pe0_src_size, hsize,	ctrl0_info->pe0_src_h);
			PE_P0L_H13_Rd01(p0l_pe0_src_size, vsize,	ctrl0_info->pe0_src_v);
			ctrl0_info->scl_resize = (ctrl0_info->o_win_h_size<PE_INF_H13_SCL_RESIZE_H_MAX && \
								ctrl0_info->o_win_v_size<PE_INF_H13_SCL_RESIZE_V_MAX)? 1:0;
			ctrl0_info->scl_hd = (ctrl0_info->scl_src_h>=PE_INF_H13_SCL_IS_HD_MIN)? 1:0;
			/* R */
	        PE_MSR_H13_RdFL(msc_scr_size_r);
	        PE_MSR_H13_RdFL(msc_win_in_offset_r);
	        PE_MSR_H13_RdFL(msc_win_in_size_r);
	        PE_MSR_H13_RdFL(msc_win_out_size_r);
	        PE_MSR_H13_RdFL(msc_c_format_r);
	        PE_MSR_H13_Rd01(msc_scr_size_r, 	input_h_size,		ctrl1_info->scl_src_h);
	        PE_MSR_H13_Rd01(msc_scr_size_r, 	input_v_size,		ctrl1_info->scl_src_v);
	        PE_MSR_H13_Rd01(msc_win_in_offset_r,in_win_h_offset,	ctrl1_info->i_win_h_ofst);
	        PE_MSR_H13_Rd01(msc_win_in_offset_r,in_win_v_offset,	ctrl1_info->i_win_v_ofst);
	        PE_MSR_H13_Rd01(msc_win_in_size_r, 	in_win_h_size,		ctrl1_info->i_win_h_size);
	        PE_MSR_H13_Rd01(msc_win_in_size_r, 	in_win_v_size,		ctrl1_info->i_win_v_size);
	        PE_MSR_H13_Rd01(msc_win_out_size_r, out_win_h_size,		ctrl1_info->o_win_h_size);
	        PE_MSR_H13_Rd01(msc_win_out_size_r, out_win_v_size,		ctrl1_info->o_win_v_size);
	        PE_MSR_H13_Rd01(msc_c_format_r, 	in_c_format,		r_data);
			ctrl1_info->is_yuv444 = (r_data==0x6)? 0x1:0x0;	//"100":yuv420,"101":yuv422,"110":yuv444
			PE_OVR_H13_RdFL(ovr_ov_moffset);
			PE_OVR_H13_RdFL(ovr_ov_msize);
			PE_OVR_H13_Rd01(ovr_ov_moffset, m_hoffset,	ctrl1_info->m_win_h_ofst);
			PE_OVR_H13_Rd01(ovr_ov_moffset, m_voffset,	ctrl1_info->m_win_v_ofst);
			PE_OVR_H13_Rd01(ovr_ov_msize, 	m_hsize,	ctrl1_info->m_win_h_size);
			PE_OVR_H13_Rd01(ovr_ov_msize, 	m_vsize,	ctrl1_info->m_win_v_size);
			PE_P0R_H13_RdFL(p0r_pe0_src_size);
			PE_P0R_H13_Rd01(p0r_pe0_src_size, hsize,	ctrl1_info->pe0_src_h);
			PE_P0R_H13_Rd01(p0r_pe0_src_size, vsize,	ctrl1_info->pe0_src_v);
			ctrl1_info->scl_resize = (ctrl1_info->o_win_h_size<PE_INF_H13_SCL_RESIZE_H_MAX && \
								ctrl1_info->o_win_v_size<PE_INF_H13_SCL_RESIZE_V_MAX)? 1:0;
			ctrl1_info->scl_hd = (ctrl1_info->scl_src_h>=PE_INF_H13_SCL_IS_HD_MIN)? 1:0;
			/* sub scaler */
			PE_SSC_H13_RdFL(ssc_scr_size);
			PE_SSC_H13_RdFL(ssc_win_in_offset);
			PE_SSC_H13_RdFL(ssc_win_in_size);
			PE_SSC_H13_RdFL(ssc_win_out_size);
			PE_SSC_H13_Rd01(ssc_scr_size,			input_h_size,		ctrl0_info->ssc_src_h);
			PE_SSC_H13_Rd01(ssc_scr_size,			input_v_size,		ctrl0_info->ssc_src_v);
			PE_SSC_H13_Rd01(ssc_win_in_offset,		in_win_h_offset,	ctrl0_info->ssc_i_win_x);
			PE_SSC_H13_Rd01(ssc_win_in_offset,		in_win_v_offset,	ctrl0_info->ssc_i_win_y);
			PE_SSC_H13_Rd01(ssc_win_in_size,		in_win_h_size,		ctrl0_info->ssc_i_win_h);
			PE_SSC_H13_Rd01(ssc_win_in_size,		in_win_v_size,		ctrl0_info->ssc_i_win_v);
			PE_SSC_H13_Rd01(ssc_win_out_size,		out_win_h_size,		ctrl0_info->ssc_o_win_h);
			PE_SSC_H13_Rd01(ssc_win_out_size,		out_win_v_size,		ctrl0_info->ssc_o_win_v);
			ctrl1_info->ssc_src_h	= ctrl0_info->ssc_src_h;
			ctrl1_info->ssc_src_v	= ctrl0_info->ssc_src_v;
			ctrl1_info->ssc_i_win_x	= ctrl0_info->ssc_i_win_x;
			ctrl1_info->ssc_i_win_y	= ctrl0_info->ssc_i_win_y;
			ctrl1_info->ssc_i_win_h	= ctrl0_info->ssc_i_win_h;
			ctrl1_info->ssc_i_win_v	= ctrl0_info->ssc_i_win_v;
			ctrl1_info->ssc_o_win_h	= ctrl0_info->ssc_o_win_h;
			ctrl1_info->ssc_o_win_v	= ctrl0_info->ssc_o_win_v;
			/* etc */
			ret = PE_HST_HW_H13_GetDetected3dFmt(&r_data);
			if(ret)	{PE_INF_H13_ERROR("[%s,%d] PE_HST_HW_H13_GetDetected3dFmt() error.\n",__F__,__L__);}
			ctrl0_info->det_3df = r_data;
			ctrl0_info->auto_cr_en = ccm_info.auto_cr.enable? 1:0;
			PE_P0L_H13_QRd01(p0l_tpd_stat_00, 	reg_s_status,	ctrl0_info->sat_status);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_03, 	pxl_rep_in,		ctrl0_info->mute_on);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_08, 	pxl_rep_in,		ctrl1_info->mute_on);
		}
		else
		{
			PE_INF_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get current info.
 *
 * @param   *pstParams [in/out] PE_INF_H13_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_H13_GetCurInfSettings(PE_INF_H13_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_INF_H13_SETTINGS_T *pInfo=&_g_pe_inf_hw_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			memcpy(pstParams,pInfo,sizeof(PE_INF_H13_SETTINGS_T));
			if(_g_pe_inf_h13_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_INF_H13_DBG_PRINT("disp[0] : src:%d,fmt:%d,out:%d,fr:%d(%d)\n",\
						pstParams->disp_info[LX_PE_WIN_0].src_type,pstParams->disp_info[LX_PE_WIN_0].fmt_type,\
						pstParams->disp_info[LX_PE_WIN_0].out_type,pstParams->disp_info[LX_PE_WIN_0].fr_type,\
						pstParams->disp_info[LX_PE_WIN_0].in_f_rate);
					PE_INF_H13_DBG_PRINT("disp[0] : h,v:%d,%d,scan:%d,dtv:%d,hdd:%d,3d_in:%d\n",\
						pstParams->disp_info[LX_PE_WIN_0].in_h_size,pstParams->disp_info[LX_PE_WIN_0].in_v_size,\
						pstParams->disp_info[LX_PE_WIN_0].scan_type,pstParams->disp_info[LX_PE_WIN_0].dtv_type,\
						pstParams->disp_info[LX_PE_WIN_0].hdd_type,pstParams->disp_info[LX_PE_WIN_0].in_type);
					PE_INF_H13_DBG_PRINT("disp[0] : is tp:%d,venc:%d,adpt_st:%d,ext_frc:%d,wb_wog:%d\n",\
						pstParams->disp_info[LX_PE_WIN_0].mode.is_tp,pstParams->disp_info[LX_PE_WIN_0].mode.is_venc,\
						pstParams->disp_info[LX_PE_WIN_0].mode.is_adpt_st,pstParams->disp_info[LX_PE_WIN_0].mode.is_ext_frc,\
						pstParams->disp_info[LX_PE_WIN_0].mode.is_wb_wog);
					PE_INF_H13_DBG_PRINT("ctrl[0] : src:%d,%d,scl:%d,%d,i_w:%d,%d,%d,%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_0].pe0_src_h,pInfo->ctrl_info[LX_PE_WIN_0].pe0_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_0].scl_src_h,pInfo->ctrl_info[LX_PE_WIN_0].scl_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_0].i_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_0].i_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_0].i_win_h_size,pInfo->ctrl_info[LX_PE_WIN_0].i_win_v_size);
					PE_INF_H13_DBG_PRINT("ctrl[0] : scl_o_w:%d,%d,ov_m_w:%d,%d,%d,%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_0].o_win_h_size,pInfo->ctrl_info[LX_PE_WIN_0].o_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_0].m_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_0].m_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_0].m_win_h_size,pInfo->ctrl_info[LX_PE_WIN_0].m_win_v_size);
					PE_INF_H13_DBG_PRINT("ctrl[0] : y444:%d,det_3df:%d,acr_en:%d,s_stat:%d,mute_on:%d,hv_same:%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_0].is_yuv444,pInfo->ctrl_info[LX_PE_WIN_0].det_3df,\
						pInfo->ctrl_info[LX_PE_WIN_0].auto_cr_en,pInfo->ctrl_info[LX_PE_WIN_0].sat_status,\
						pInfo->ctrl_info[LX_PE_WIN_0].mute_on,pInfo->ctrl_info[LX_PE_WIN_0].hv_same);
					PE_INF_H13_DBG_PRINT("ctrl[0] : sub_scl src:%d,%d, i_w:%d,%d,%d,%d, o_w:%d,%d, pxl_rp:%d, src_frz:%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_0].ssc_src_h,pInfo->ctrl_info[LX_PE_WIN_0].ssc_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_0].ssc_i_win_x,pInfo->ctrl_info[LX_PE_WIN_0].ssc_i_win_y,\
						pInfo->ctrl_info[LX_PE_WIN_0].ssc_i_win_h,pInfo->ctrl_info[LX_PE_WIN_0].ssc_i_win_v,\
						pInfo->ctrl_info[LX_PE_WIN_0].ssc_o_win_h,pInfo->ctrl_info[LX_PE_WIN_0].ssc_o_win_v,\
						pInfo->ctrl_info[LX_PE_WIN_0].pxl_rp_st,pInfo->ctrl_info[LX_PE_WIN_0].is_src_frz);
					PE_INF_H13_DBG_PRINT("disp[1] : src:%d,fmt:%d,out:%d,fr:%d(%d)\n",\
						pstParams->disp_info[LX_PE_WIN_1].src_type,pstParams->disp_info[LX_PE_WIN_1].fmt_type,\
						pstParams->disp_info[LX_PE_WIN_1].out_type,pstParams->disp_info[LX_PE_WIN_1].fr_type,\
						pstParams->disp_info[LX_PE_WIN_1].in_f_rate);
					PE_INF_H13_DBG_PRINT("disp[1] : h,v:%d,%d,scan:%d,dtv:%d,hdd:%d,3d_in:%d\n",\
						pstParams->disp_info[LX_PE_WIN_1].in_h_size,pstParams->disp_info[LX_PE_WIN_1].in_v_size,\
						pstParams->disp_info[LX_PE_WIN_1].scan_type,pstParams->disp_info[LX_PE_WIN_1].dtv_type,\
						pstParams->disp_info[LX_PE_WIN_1].hdd_type,pstParams->disp_info[LX_PE_WIN_1].in_type);
					PE_INF_H13_DBG_PRINT("disp[1] : is tp:%d,venc:%d,adpt_st:%d,ext_frc:%d,wb_wog:%d\n",\
						pstParams->disp_info[LX_PE_WIN_1].mode.is_tp,pstParams->disp_info[LX_PE_WIN_1].mode.is_venc,\
						pstParams->disp_info[LX_PE_WIN_1].mode.is_adpt_st,pstParams->disp_info[LX_PE_WIN_1].mode.is_ext_frc,\
						pstParams->disp_info[LX_PE_WIN_1].mode.is_wb_wog);
					PE_INF_H13_DBG_PRINT("ctrl[1] : src:%d,%d,scl:%d,%d,i_w:%d,%d,%d,%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_1].pe0_src_h,pInfo->ctrl_info[LX_PE_WIN_1].pe0_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_1].scl_src_h,pInfo->ctrl_info[LX_PE_WIN_1].scl_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_1].i_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_1].i_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_1].i_win_h_size,pInfo->ctrl_info[LX_PE_WIN_1].i_win_v_size);
					PE_INF_H13_DBG_PRINT("ctrl[1] : scl_o_w:%d,%d,ov_m_w:%d,%d,%d,%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_1].o_win_h_size,pInfo->ctrl_info[LX_PE_WIN_1].o_win_v_size,\
						pInfo->ctrl_info[LX_PE_WIN_1].m_win_h_ofst,pInfo->ctrl_info[LX_PE_WIN_1].m_win_v_ofst,\
						pInfo->ctrl_info[LX_PE_WIN_1].m_win_h_size,pInfo->ctrl_info[LX_PE_WIN_1].m_win_v_size);
					PE_INF_H13_DBG_PRINT("ctrl[1] : y444:%d,det_3df:%d,acr_en:%d,s_stat:%d,mute_on:%d,hv_same:%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_1].is_yuv444,pInfo->ctrl_info[LX_PE_WIN_1].det_3df,\
						pInfo->ctrl_info[LX_PE_WIN_1].auto_cr_en,pInfo->ctrl_info[LX_PE_WIN_1].sat_status,\
						pInfo->ctrl_info[LX_PE_WIN_1].mute_on,pInfo->ctrl_info[LX_PE_WIN_1].hv_same);
					PE_INF_H13_DBG_PRINT("ctrl[1] : sub_scl src:%d,%d, i_w:%d,%d,%d,%d, o_w:%d,%d, pxl_rp:%d, src_frz:%d\n",\
						pInfo->ctrl_info[LX_PE_WIN_1].ssc_src_h,pInfo->ctrl_info[LX_PE_WIN_1].ssc_src_v,\
						pInfo->ctrl_info[LX_PE_WIN_1].ssc_i_win_x,pInfo->ctrl_info[LX_PE_WIN_1].ssc_i_win_y,\
						pInfo->ctrl_info[LX_PE_WIN_1].ssc_i_win_h,pInfo->ctrl_info[LX_PE_WIN_1].ssc_i_win_v,\
						pInfo->ctrl_info[LX_PE_WIN_1].ssc_o_win_h,pInfo->ctrl_info[LX_PE_WIN_1].ssc_o_win_v,\
						pInfo->ctrl_info[LX_PE_WIN_1].pxl_rp_st,pInfo->ctrl_info[LX_PE_WIN_1].is_src_frz);
					PE_INF_H13_DBG_PRINT("\n");
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_INF_H13_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}
/**
 * get general(all) picture info
 *
 * @param   *pstParams [in] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_INF_H13_GetGeneralPicInfo(LX_PE_ETC_DBG_T *pstParams)
{
    int ret = RET_OK;
	UINT32 size_sum,offset,inf_size,win_size,shp_size,ccm_size;
	PE_WIN_HW_H13_SETTINGS_T win_set;
	PE_SHP_HW_H13_SETTINGS_T shp_set;
	PE_CCM_HW_H13_SETTINGS_T ccm_set;
	PE_INF_H13_SETTINGS_T *pInfo=&_g_pe_inf_hw_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			offset = 0;
			inf_size = sizeof(PE_INF_H13_SETTINGS_T);
			win_size = sizeof(PE_WIN_HW_H13_SETTINGS_T);
			shp_size = sizeof(PE_SHP_HW_H13_SETTINGS_T);
			ccm_size = sizeof(PE_CCM_HW_H13_SETTINGS_T);
			PE_INF_H13_DBG_PRINT("size : inf:%d,win:%d,shp:%d,ccm:%d\n",inf_size,win_size,shp_size,ccm_size);
			size_sum = inf_size+win_size+shp_size+ccm_size;
			PE_INF_H13_CHECK_CODE(pstParams->size!=(size_sum/sizeof(UINT32)),\
				break,"[%s,%d] size mismatch.(param_size:%d vs. (struct:%d)/(uint32:%d))\n",__F__,__L__,\
				pstParams->size,size_sum,sizeof(UINT32));
			/* get inf */
			memcpy(pstParams->data,pInfo,inf_size);
			/* get win settings */
			ret = PE_WIN_HW_H13_GetCurWinSettings(&win_set);
			PE_INF_H13_CHECK_CODE(ret,break,"[%s,%d] PE_WIN_HW_H13_GetCurWinSettings() error.\n",__F__,__L__);
			offset += (inf_size/sizeof(UINT32));
			memcpy(&pstParams->data[offset],&win_set,win_size);
			/* get shp settings */
			ret = PE_SHP_HW_H13_GetCurShpSettings(&shp_set);
			PE_INF_H13_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetCurShpSettings() error.\n",__F__,__L__);
			offset += (win_size/sizeof(UINT32));
			memcpy(&pstParams->data[offset],&shp_set,shp_size);
			/* get ccm settings */
			ret = PE_CCM_HW_H13_GetCurCcmSettings(&ccm_set);
			PE_INF_H13_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_H13_GetCurCcmSettings() error.\n",__F__,__L__);
			offset += (shp_size/sizeof(UINT32));
			memcpy(&pstParams->data[offset],&ccm_set,ccm_size);
		}
		else
		{
			PE_INF_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return ret;
}

/**
 * set PathMonitor operation
 *
 * @param   *pstParams [in] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_INF_H13_SetPathMonitor(LX_PE_ETC_DBG_T *pstParams)
{
    int ret = RET_OK;
	UINT32 *pData=NULL;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		PE_INF_H13_CHECK_CODE(pstParams->size!=90,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		pData = pstParams->data;
		if(PE_KDRV_VER_H13BX)
		{
			PE_P0L_H13B0_QWr01(p0l_pe0_opmode,		detour_enable,			(pData[1])? 0x1:0x0);
			PE_P0L_H13B0_QWr01(p0l_ipc_ctrl_00,		cr_luma_mode,			GET_BITS((pData[2]),0,2));
			PE_P0L_H13B0_QWr01(p0l_ipc_ctrl_00,		cr_chroma_mode,			GET_BITS((pData[3]),0,2));
			PE_P0R_H13B0_QWr01(p0r_pe0_opmode,		detour_enable,			(pData[4])? 0x1:0x0);
			PE_P0R_H13B0_QWr01(p0r_ipc_ctrl_00,		cr_luma_mode,			GET_BITS((pData[5]),0,2));
			PE_P0R_H13B0_QWr01(p0r_ipc_ctrl_00,		cr_chroma_mode,			GET_BITS((pData[6]),0,2));
			PE_MSL_H13B0_QWr01(msc_ctrl_l,			filter_type_sel_luma,	(pData[10])? 0x1:0x0);
			PE_MSR_H13B0_QWr01(msc_ctrl_r,			filter_type_sel_luma,	(pData[11])? 0x1:0x0);
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl4,		w0_dark_en,				(pData[20])? 0x1:0x0);
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl4,		w1_dark_en,				(pData[21])? 0x1:0x0);
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl2,		dark_color_yy,			GET_BITS((pData[22]),0,8));
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl2,		dark_color_cb,			GET_BITS((pData[23]),0,4));
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl2,		dark_color_cr,			GET_BITS((pData[24]),0,4));
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl2,		back_color_yy,			GET_BITS((pData[25]),0,8));
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl2,		back_color_cb,			GET_BITS((pData[26]),0,4));
			PE_OVL_H13B0_QWr01(ovl_ov_ctrl2,		back_color_cr,			GET_BITS((pData[27]),0,4));
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl4,		w0_dark_en,				(pData[30])? 0x1:0x0);
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl4,		w1_dark_en,				(pData[31])? 0x1:0x0);
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl2,		dark_color_yy,			GET_BITS((pData[32]),0,8));
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl2,		dark_color_cb,			GET_BITS((pData[33]),0,4));
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl2,		dark_color_cr,			GET_BITS((pData[34]),0,4));
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl2,		back_color_yy,			GET_BITS((pData[35]),0,8));
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl2,		back_color_cb,			GET_BITS((pData[36]),0,4));
			PE_OVR_H13B0_QWr01(ovr_ov_ctrl2,		back_color_cr,			GET_BITS((pData[37]),0,4));
			PE_P1L_H13B0_QWr01(pe1_top_ctrl_02,		pe1_detour,				(pData[40])? 0x1:0x0);
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_03,	pxl_rep_in,				(pData[41])? 0x1:0x0);
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_05,	pxl_rep_value_r,		GET_BITS((pData[42]),0,10));
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_05,	pxl_rep_value_g,		GET_BITS((pData[43]),0,10));
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_05,	pxl_rep_value_b,		GET_BITS((pData[44]),0,10));
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_08,	pxl_rep_in,				(pData[45])? 0x1:0x0);
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_0a,	pxl_rep_value_r,		GET_BITS((pData[46]),0,10));
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_0a,	pxl_rep_value_g,		GET_BITS((pData[47]),0,10));
			PE_P1L_H13B0_QWr01(pe1_conv_ctrl_0a,	pxl_rep_value_b,		GET_BITS((pData[48]),0,10));
			PE_CVA_H13B0_QWr01(cva_misc_ctrl,		pattern_type,			(pData[70])? 0x1:0x0);
			PE_CVA_H13B0_QWr01(cva_misc_ctrl,		pattern_csc,			(pData[71])? 0x1:0x0);
			PE_CVA_H13B0_QWr01(cva_misc_ctrl,		pattern_detail,			GET_BITS((pData[72]),0,4));
			PE_CVA_H13B0_QWr01(cva_dig_filt_ctrl3,	fir_en,					(pData[73])? 0x1:0x0);
			PE_CVA_H13B0_QWr01(cva_dig_filt_ctrl3,	fir_y_en,				(pData[74])? 0x1:0x0);
			PE_CVA_H13B0_QWr01(cva_dig_filt_ctrl3,	fir_c_en,				(pData[75])? 0x1:0x0);
			PE_CVB_H13B0_QWr01(cvb_misc_ctrl,		pattern_type,			(pData[76])? 0x1:0x0);
			PE_CVB_H13B0_QWr01(cvb_misc_ctrl,		pattern_csc,			(pData[77])? 0x1:0x0);
			PE_CVB_H13B0_QWr01(cvb_misc_ctrl,		pattern_detail,			GET_BITS((pData[78]),0,4));
			PE_CVB_H13B0_QWr01(cvb_dig_filt_ctrl3,	fir_en,					(pData[79])? 0x1:0x0);
			PE_CVB_H13B0_QWr01(cvb_dig_filt_ctrl3,	fir_y_en,				(pData[80])? 0x1:0x0);
			PE_CVB_H13B0_QWr01(cvb_dig_filt_ctrl3,	fir_c_en,				(pData[81])? 0x1:0x0);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_P0L_H13_QWr01(p0l_pe0_opmode,		detour_enable,			(pData[0])? 0x1:0x0);
			PE_P0L_H13_QWr01(p0l_ipc_ctrl_00,		luma_mode,				GET_BITS((pData[1]),0,2));
			PE_P0L_H13_QWr01(p0l_ipc_ctrl_00,		chroma_mode,			GET_BITS((pData[2]),0,2));
			PE_P0R_H13_QWr01(p0r_pe0_opmode,		detour_enable,			(pData[3])? 0x1:0x0);
			PE_P0R_H13_QWr01(p0r_ipc_ctrl_00,		luma_mode,				GET_BITS((pData[4]),0,2));
			PE_P0R_H13_QWr01(p0r_ipc_ctrl_00,		chroma_mode,			GET_BITS((pData[5]),0,2));
			PE_MSL_H13_QWr01(msc_ctrl_l,			filter_type_sel_luma,	(pData[10])? 0x1:0x0);
			PE_MSR_H13_QWr01(msc_ctrl_r,			filter_type_sel_luma,	(pData[11])? 0x1:0x0);
			PE_OVL_H13_QWr01(ov_ctrl4,				w0_dark_en,				(pData[20])? 0x1:0x0);
			PE_OVL_H13_QWr01(ov_ctrl4,				w1_dark_en,				(pData[21])? 0x1:0x0);
			PE_OVL_H13_QWr01(ovl_ov_ctrl2,			dark_color_yy,			GET_BITS((pData[22]),0,8));
			PE_OVL_H13_QWr01(ovl_ov_ctrl2,			dark_color_cb,			GET_BITS((pData[23]),0,4));
			PE_OVL_H13_QWr01(ovl_ov_ctrl2,			dark_color_cr,			GET_BITS((pData[24]),0,4));
			PE_OVL_H13_QWr01(ovl_ov_ctrl2,			back_color_yy,			GET_BITS((pData[25]),0,8));
			PE_OVL_H13_QWr01(ovl_ov_ctrl2,			back_color_cb,			GET_BITS((pData[26]),0,4));
			PE_OVL_H13_QWr01(ovl_ov_ctrl2,			back_color_cr,			GET_BITS((pData[27]),0,4));
			/*PE_OVR_H13_QWr01(ov_ctrl4,			w0_dark_en,				(pData[30])? 0x1:0x0);*/
			/*PE_OVR_H13_QWr01(ov_ctrl4,			w1_dark_en,				(pData[31])? 0x1:0x0);*/
			PE_OVR_H13_QWr01(ovr_ov_ctrl2,			dark_color_yy,			GET_BITS((pData[32]),0,8));
			PE_OVR_H13_QWr01(ovr_ov_ctrl2,			dark_color_cb,			GET_BITS((pData[33]),0,4));
			PE_OVR_H13_QWr01(ovr_ov_ctrl2,			dark_color_cr,			GET_BITS((pData[34]),0,4));
			PE_OVR_H13_QWr01(ovr_ov_ctrl2,			back_color_yy,			GET_BITS((pData[35]),0,8));
			PE_OVR_H13_QWr01(ovr_ov_ctrl2,			back_color_cb,			GET_BITS((pData[36]),0,4));
			PE_OVR_H13_QWr01(ovr_ov_ctrl2,			back_color_cr,			GET_BITS((pData[37]),0,4));
			PE_P1L_H13_QWr01(pe1_top_ctrl_02,		pe1_detour,				(pData[40])? 0x1:0x0);
			PE_P1L_H13_QWr01(pe1_conv_ctrl_03,		pxl_rep_in,				(pData[41])? 0x1:0x0);
			PE_P1L_H13_QWr01(pe1_conv_ctrl_05,		pxl_rep_value_r,		GET_BITS((pData[42]),0,10));
			PE_P1L_H13_QWr01(pe1_conv_ctrl_05,		pxl_rep_value_g,		GET_BITS((pData[43]),0,10));
			PE_P1L_H13_QWr01(pe1_conv_ctrl_05,		pxl_rep_value_b,		GET_BITS((pData[44]),0,10));
			PE_P1L_H13_QWr01(pe1_conv_ctrl_08,		pxl_rep_in,				(pData[45])? 0x1:0x0);
			PE_P1L_H13_QWr01(pe1_conv_ctrl_0a,		pxl_rep_value_r,		GET_BITS((pData[46]),0,10));
			PE_P1L_H13_QWr01(pe1_conv_ctrl_0a,		pxl_rep_value_g,		GET_BITS((pData[47]),0,10));
			PE_P1L_H13_QWr01(pe1_conv_ctrl_0a,		pxl_rep_value_b,		GET_BITS((pData[48]),0,10));
			PE_CVA_H13_QWr01(cva_misc_ctrl,			pattern_type,			(pData[70])? 0x1:0x0);
			PE_CVA_H13_QWr01(cva_misc_ctrl,			pattern_csc,			(pData[71])? 0x1:0x0);
			PE_CVA_H13_QWr01(cva_misc_ctrl,			pattern_detail,			GET_BITS((pData[72]),0,4));
			PE_CVA_H13_QWr01(cva_dig_filt_ctrl3,	fir_en,					(pData[73])? 0x1:0x0);
			PE_CVA_H13_QWr01(cva_dig_filt_ctrl3,	fir_y_en,				(pData[74])? 0x1:0x0);
			PE_CVA_H13_QWr01(cva_dig_filt_ctrl3,	fir_c_en,				(pData[75])? 0x1:0x0);
			PE_CVB_H13_QWr01(cvb_misc_ctrl,			pattern_type,			(pData[76])? 0x1:0x0);
			PE_CVB_H13_QWr01(cvb_misc_ctrl,			pattern_csc,			(pData[77])? 0x1:0x0);
			PE_CVB_H13_QWr01(cvb_misc_ctrl,			pattern_detail,			GET_BITS((pData[78]),0,4));
			PE_CVB_H13_QWr01(cvb_dig_filt_ctrl3,	fir_en,					(pData[79])? 0x1:0x0);
			PE_CVB_H13_QWr01(cvb_dig_filt_ctrl3,	fir_y_en,				(pData[80])? 0x1:0x0);
			PE_CVB_H13_QWr01(cvb_dig_filt_ctrl3,	fir_c_en,				(pData[81])? 0x1:0x0);
		}
		else
		{
			PE_INF_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return ret;
}
/**
 * get PathMonitor operation
 *
 * @param   *pstParams [in/out] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_INF_H13_GetPathMonitor(LX_PE_ETC_DBG_T *pstParams)
{
	int ret = RET_OK;
	UINT32 *pData=NULL;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		PE_INF_H13_CHECK_CODE(pstParams->size!=90,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		pData = pstParams->data;
		if(PE_KDRV_VER_H13BX)
		{
			PE_P0L_H13B0_QRd01(p0l_pe0_opmode,		detour_enable,			pData[1]);
			PE_P0L_H13B0_QRd01(p0l_ipc_ctrl_00,		cr_luma_mode,			pData[2]);
			PE_P0L_H13B0_QRd01(p0l_ipc_ctrl_00,		cr_chroma_mode,			pData[3]);
			PE_P0R_H13B0_QRd01(p0r_pe0_opmode,		detour_enable,			pData[4]);
			PE_P0R_H13B0_QRd01(p0r_ipc_ctrl_00,		cr_luma_mode,			pData[5]);
			PE_P0R_H13B0_QRd01(p0r_ipc_ctrl_00,		cr_chroma_mode,			pData[6]);
			PE_MSL_H13B0_QRd01(msc_ctrl_l,			filter_type_sel_luma,	pData[10]);
			PE_MSR_H13B0_QRd01(msc_ctrl_r,			filter_type_sel_luma,	pData[11]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl4,		w0_dark_en,				pData[20]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl4,		w1_dark_en,				pData[21]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl2,		dark_color_yy,			pData[22]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl2,		dark_color_cb,			pData[23]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl2,		dark_color_cr,			pData[24]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl2,		back_color_yy,			pData[25]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl2,		back_color_cb,			pData[26]);
			PE_OVL_H13B0_QRd01(ovl_ov_ctrl2,		back_color_cr,			pData[27]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl4,		w0_dark_en,				pData[30]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl4,		w1_dark_en,				pData[31]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl2,		dark_color_yy,			pData[32]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl2,		dark_color_cb,			pData[33]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl2,		dark_color_cr,			pData[34]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl2,		back_color_yy,			pData[35]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl2,		back_color_cb,			pData[36]);
			PE_OVR_H13B0_QRd01(ovr_ov_ctrl2,		back_color_cr,			pData[37]);
			PE_P1L_H13B0_QRd01(pe1_top_ctrl_02,		pe1_detour,				pData[40]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_03,	pxl_rep_in,				pData[41]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_05,	pxl_rep_value_r,		pData[42]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_05,	pxl_rep_value_g,		pData[43]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_05,	pxl_rep_value_b,		pData[44]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_08,	pxl_rep_in,				pData[45]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_0a,	pxl_rep_value_r,		pData[46]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_0a,	pxl_rep_value_g,		pData[47]);
			PE_P1L_H13B0_QRd01(pe1_conv_ctrl_0a,	pxl_rep_value_b,		pData[48]);
			PE_CVA_H13B0_QRd01(cva_misc_ctrl,		pattern_type,			pData[70]);
			PE_CVA_H13B0_QRd01(cva_misc_ctrl,		pattern_csc,			pData[71]);
			PE_CVA_H13B0_QRd01(cva_misc_ctrl,		pattern_detail,			pData[72]);
			PE_CVA_H13B0_QRd01(cva_dig_filt_ctrl3,	fir_en,					pData[73]);
			PE_CVA_H13B0_QRd01(cva_dig_filt_ctrl3,	fir_y_en,				pData[74]);
			PE_CVA_H13B0_QRd01(cva_dig_filt_ctrl3,	fir_c_en,				pData[75]);
			PE_CVB_H13B0_QRd01(cvb_misc_ctrl,		pattern_type,			pData[76]);
			PE_CVB_H13B0_QRd01(cvb_misc_ctrl,		pattern_csc,			pData[77]);
			PE_CVB_H13B0_QRd01(cvb_misc_ctrl,		pattern_detail,			pData[78]);
			PE_CVB_H13B0_QRd01(cvb_dig_filt_ctrl3,	fir_en,					pData[79]);
			PE_CVB_H13B0_QRd01(cvb_dig_filt_ctrl3,	fir_y_en,				pData[80]);
			PE_CVB_H13B0_QRd01(cvb_dig_filt_ctrl3,	fir_c_en,				pData[81]);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_P0L_H13_QRd01(p0l_pe0_opmode,		detour_enable,			pData[0]);
			PE_P0L_H13_QRd01(p0l_ipc_ctrl_00,		luma_mode,				pData[1]);
			PE_P0L_H13_QRd01(p0l_ipc_ctrl_00,		chroma_mode,			pData[2]);
			PE_P0R_H13_QRd01(p0r_pe0_opmode,		detour_enable,			pData[3]);
			PE_P0R_H13_QRd01(p0r_ipc_ctrl_00,		luma_mode,				pData[4]);
			PE_P0R_H13_QRd01(p0r_ipc_ctrl_00,		chroma_mode,			pData[5]);
			PE_MSL_H13_QRd01(msc_ctrl_l,			filter_type_sel_luma,	pData[10]);
			PE_MSR_H13_QRd01(msc_ctrl_r,			filter_type_sel_luma,	pData[11]);
			PE_OVL_H13_QRd01(ov_ctrl4,				w0_dark_en,				pData[20]);
			PE_OVL_H13_QRd01(ov_ctrl4,				w1_dark_en,				pData[21]);
			PE_OVL_H13_QRd01(ovl_ov_ctrl2,			dark_color_yy,			pData[22]);
			PE_OVL_H13_QRd01(ovl_ov_ctrl2,			dark_color_cb,			pData[23]);
			PE_OVL_H13_QRd01(ovl_ov_ctrl2,			dark_color_cr,			pData[24]);
			PE_OVL_H13_QRd01(ovl_ov_ctrl2,			back_color_yy,			pData[25]);
			PE_OVL_H13_QRd01(ovl_ov_ctrl2,			back_color_cb,			pData[26]);
			PE_OVL_H13_QRd01(ovl_ov_ctrl2,			back_color_cr,			pData[27]);
			pData[30] = 0;
			pData[31] = 0;
			PE_OVR_H13_QRd01(ovr_ov_ctrl2,			dark_color_yy,			pData[32]);
			PE_OVR_H13_QRd01(ovr_ov_ctrl2,			dark_color_cb,			pData[33]);
			PE_OVR_H13_QRd01(ovr_ov_ctrl2,			dark_color_cr,			pData[34]);
			PE_OVR_H13_QRd01(ovr_ov_ctrl2,			back_color_yy,			pData[35]);
			PE_OVR_H13_QRd01(ovr_ov_ctrl2,			back_color_cb,			pData[36]);
			PE_OVR_H13_QRd01(ovr_ov_ctrl2,			back_color_cr,			pData[37]);
			PE_P1L_H13_QRd01(pe1_top_ctrl_02,		pe1_detour,				pData[40]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_03,		pxl_rep_in,				pData[41]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_05,		pxl_rep_value_r,		pData[42]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_05,		pxl_rep_value_g,		pData[43]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_05,		pxl_rep_value_b,		pData[44]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_08,		pxl_rep_in,				pData[45]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_0a,		pxl_rep_value_r,		pData[46]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_0a,		pxl_rep_value_g,		pData[47]);
			PE_P1L_H13_QRd01(pe1_conv_ctrl_0a,		pxl_rep_value_b,		pData[48]);
			PE_CVA_H13_QRd01(cva_misc_ctrl,			pattern_type,			pData[70]);
			PE_CVA_H13_QRd01(cva_misc_ctrl,			pattern_csc,			pData[71]);
			PE_CVA_H13_QRd01(cva_misc_ctrl,			pattern_detail,			pData[72]);
			PE_CVA_H13_QRd01(cva_dig_filt_ctrl3,	fir_en,					pData[73]);
			PE_CVA_H13_QRd01(cva_dig_filt_ctrl3,	fir_y_en,				pData[74]);
			PE_CVA_H13_QRd01(cva_dig_filt_ctrl3,	fir_c_en,				pData[75]);
			PE_CVB_H13_QRd01(cvb_misc_ctrl,			pattern_type,			pData[76]);
			PE_CVB_H13_QRd01(cvb_misc_ctrl,			pattern_csc,			pData[77]);
			PE_CVB_H13_QRd01(cvb_misc_ctrl,			pattern_detail,			pData[78]);
			PE_CVB_H13_QRd01(cvb_dig_filt_ctrl3,	fir_en,					pData[79]);
			PE_CVB_H13_QRd01(cvb_dig_filt_ctrl3,	fir_y_en,				pData[80]);
			PE_CVB_H13_QRd01(cvb_dig_filt_ctrl3,	fir_c_en,				pData[81]);
		}
		else
		{
			PE_INF_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return ret;
}

