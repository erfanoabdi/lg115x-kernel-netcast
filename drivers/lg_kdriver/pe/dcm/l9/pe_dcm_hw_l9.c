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


/** @file pe_dcm_hw_l9.c
 *
 *  driver for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	- dynamic contrast enhancement, histogram information and configuration.
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
#include "pe_dcm_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_L9_ERROR	printk

#define PE_DCM_HW_L9_DBG_PRINT(fmt,args...)	\
	if(_g_dcm_hw_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_DCM_HW_L9_CHECK_CODE(_checker,_action,fmt,args...) \
	{if(_checker){PE_DCM_HW_L9_ERROR(fmt,##args);_action;}}

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
static PE_DCM_HW_L9_SETTINGS_T _g_pe_dcm_hw_l9_info;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_dcm_hw_l9_trace=0x0;	//default should be off.

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
void PE_DCM_HW_L9_SetDbgPrint(UINT32 on_off)
{
	_g_dcm_hw_l9_trace = on_off? 1:0;
	return;
}
/**
 * init dynamic contrast module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_HW_L9_Init(void)
{
	int ret = RET_OK;
	LX_PE_DCM_DCE_CONF_T stParams;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			PE_DCM_HW_L9_DBG_PRINT("init histo info\n");
			memset0(_g_pe_dcm_hw_l9_info);
			PE_DCM_HW_L9_DBG_PRINT("init dce config\n");
			stParams.domain = LX_PE_HSV_DOMAIN;
			stParams.bin_mode = LX_PE_32_BINMODE;
			stParams.lut_step = 16;
			stParams.min_pos = 7;
			stParams.max_pos = 210;
			stParams.win_id = LX_PE_WIN_ALL;
			ret = PE_DCM_HW_L9_SetDceConfig(&stParams);
			PE_DCM_HW_L9_CHECK_CODE(ret,break,"[%s,%d][win all] PE_DCM_HW_L9_SetDceConfig() error.\n",__F__,__L__);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_DCM_HW_L9_DBG_PRINT("init histo info\n");
			memset0(_g_pe_dcm_hw_l9_info);
			PE_DCM_HW_L9_DBG_PRINT("init dce config\n");
			stParams.domain = LX_PE_HSV_DOMAIN;
			stParams.bin_mode = LX_PE_32_BINMODE;
			stParams.lut_step = 16;
			stParams.min_pos = 7;
			stParams.max_pos = 210;
			stParams.win_id = LX_PE_WIN_ALL;
			ret = PE_DCM_HW_L9_SetDceConfig(&stParams);
			PE_DCM_HW_L9_CHECK_CODE(ret,break,"[%s,%d][win all] PE_DCM_HW_L9_SetDceConfig() error.\n",__F__,__L__);
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
int PE_DCM_HW_L9_GetHistogramInfo(LX_PE_DCM_HISTO_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 histo_data;
	UINT32 histoUpdateMask=0;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	PE_DCM_HW_L9_SETTINGS_T *pInfo=&_g_pe_dcm_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_INF_L9_SETTINGS_T inf_set;
				UINT32 avrg_l[3],avrg_r[3],min[2],max[2],temp_sum[2];
				ret = PE_INF_L9_GetCurInfSettings(&inf_set);
				PE_DCM_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
				if(inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_UD || \
					inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_TB || \
					inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_SS || \
					inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_FS || \
					inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_DUAL_TB || \
					inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_DUAL_SS || \
					inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_DUAL_FULL)
				{
					if(pstParams->domain==LX_PE_YC_DOMAIN)
					{
						PE_P1L_L9B0_RdFL(pe1_l_apl_stat_00);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_00,	apl_y,		avrg_l[0]);
						PE_P1R_L9B0_RdFL(pe1_r_apl_stat_00);
						PE_P1R_L9B0_Rd01(pe1_r_apl_stat_00,	apl_y,		avrg_r[0]);
						avrg_l[2] = avrg_l[1] = avrg_l[0];
						avrg_r[2] = avrg_r[1] = avrg_r[0];
					}
					else
					{
						PE_P1L_L9B0_RdFL(pe1_l_apl_stat_01);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_01,	apl_r,		avrg_l[0]);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_01,	apl_g,		avrg_l[1]);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_01,	apl_b,		avrg_l[2]);
						PE_P1R_L9B0_RdFL(pe1_r_apl_stat_01);
						PE_P1R_L9B0_Rd01(pe1_r_apl_stat_01,	apl_r,		avrg_r[0]);
						PE_P1R_L9B0_Rd01(pe1_r_apl_stat_01,	apl_g,		avrg_r[1]);
						PE_P1R_L9B0_Rd01(pe1_r_apl_stat_01,	apl_b,		avrg_r[2]);
					}
					pstParams->average[0] = (avrg_l[0]+avrg_r[0])>>1;
					pstParams->average[1] = (avrg_l[1]+avrg_r[1])>>1;
					pstParams->average[2] = (avrg_l[2]+avrg_r[2])>>1;
				}
				else
				{
					if(pstParams->domain==LX_PE_YC_DOMAIN)
					{
						PE_P1L_L9B0_RdFL(pe1_l_apl_stat_00);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_00,	apl_y,		avrg_l[0]);
						avrg_l[2] = avrg_l[1] = avrg_l[0];
					}
					else
					{
						PE_P1L_L9B0_RdFL(pe1_l_apl_stat_01);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_01,	apl_r,		avrg_l[0]);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_01,	apl_g,		avrg_l[1]);
						PE_P1L_L9B0_Rd01(pe1_l_apl_stat_01,	apl_b,		avrg_l[2]);
					}
					pstParams->average[0] = avrg_l[0];
					pstParams->average[1] = avrg_l[1];
					pstParams->average[2] = avrg_l[2];
				}
				if(inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_UD)
				{
					for(count=0;count<pstParams->bin_num;count++)
					{
						pstParams->histogram[count] = \
							(pInfo->histo_info[LX_PE_WIN_0].histogram[count]+\
							pInfo->histo_info[LX_PE_WIN_1].histogram[count])>>2;
					}
					min[0]=GET_BITS(pInfo->histo_info[LX_PE_WIN_0].status[0],0,10);
					min[1]=GET_BITS(pInfo->histo_info[LX_PE_WIN_1].status[0],0,10);
					max[0]=GET_BITS(pInfo->histo_info[LX_PE_WIN_0].status[0],16,10);
					max[1]=GET_BITS(pInfo->histo_info[LX_PE_WIN_1].status[0],16,10);
					pstParams->min = (min[0]<min[1])? min[0]:min[1];
					pstParams->max = (max[0]>max[1])? max[0]:max[1];
					pstParams->status[0] = pstParams->min | (pstParams->max<<16);
					temp_sum[0] = pInfo->histo_info[LX_PE_WIN_0].status[3];
					temp_sum[1] = pInfo->histo_info[LX_PE_WIN_1].status[3];
					pstParams->status[3]=(temp_sum[0]+temp_sum[1])>>2;
					temp_sum[0] = pInfo->histo_info[LX_PE_WIN_0].status[4];
					temp_sum[1] = pInfo->histo_info[LX_PE_WIN_1].status[4];
					pstParams->status[4]=(temp_sum[0]+temp_sum[1]);
				}
				else
				{
					for(count=0;count<pstParams->bin_num;count++)
					{
						pstParams->histogram[count] = pInfo->histo_info[LX_PE_WIN_0].histogram[count];
					}
					pstParams->min = GET_BITS(pInfo->histo_info[LX_PE_WIN_0].status[0],0,10);
					pstParams->max = GET_BITS(pInfo->histo_info[LX_PE_WIN_0].status[0],16,10);
					pstParams->status[0] = pInfo->histo_info[LX_PE_WIN_0].status[0];
					pstParams->status[3] = pInfo->histo_info[LX_PE_WIN_0].status[3];
					pstParams->status[4] = pInfo->histo_info[LX_PE_WIN_0].status[4];
				}
				pstParams->status[1] = pInfo->histo_info[LX_PE_WIN_0].status[1];
				pstParams->status[2] = pInfo->histo_info[LX_PE_WIN_0].status[2];
				pstParams->histo_ready = 1;
				pstParams->sat_status = pInfo->histo_info[LX_PE_WIN_0].sat_status;
				pstParams->motion = pData->motion_l;
			}
			if(PE_CHECK_WIN1(win_id))
			{
				if(pstParams->domain==LX_PE_YC_DOMAIN)
				{
					PE_P1R_L9B0_RdFL(pe1_r_apl_stat_00);
					PE_P1R_L9B0_Rd01(pe1_r_apl_stat_00,	apl_y,		pstParams->average[0]);
				}
				else
				{
					PE_P1R_L9B0_RdFL(pe1_r_apl_stat_01);
					PE_P1R_L9B0_Rd01(pe1_r_apl_stat_01,	apl_r,		pstParams->average[0]);
					PE_P1R_L9B0_Rd01(pe1_r_apl_stat_01,	apl_g,		pstParams->average[1]);
					PE_P1R_L9B0_Rd01(pe1_r_apl_stat_01,	apl_b,		pstParams->average[2]);
				}
				pstParams->min = GET_BITS(pInfo->histo_info[LX_PE_WIN_1].status[0],0,10);
				pstParams->max = GET_BITS(pInfo->histo_info[LX_PE_WIN_1].status[0],16,10);
				pstParams->status[0] = pInfo->histo_info[LX_PE_WIN_1].status[0];
				pstParams->status[1] = pInfo->histo_info[LX_PE_WIN_1].status[1];
				pstParams->status[2] = pInfo->histo_info[LX_PE_WIN_1].status[2];
				pstParams->status[3] = pInfo->histo_info[LX_PE_WIN_1].status[3];
				pstParams->status[4] = pInfo->histo_info[LX_PE_WIN_1].status[4];
				pstParams->histo_ready = 1;
				for(count=0;count<pstParams->bin_num;count++)
				{
					pstParams->histogram[count] = pInfo->histo_info[LX_PE_WIN_1].histogram[count];
				}
				pstParams->sat_status = 0;
				pstParams->motion = pData->motion_r;
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				if(pstParams->domain==LX_PE_YC_DOMAIN)
				{
					PE_P1L_L9_RdFL(pe1_l_apl_ctrl_03);
					PE_P1L_L9_Rd01(pe1_l_apl_ctrl_03,	apl_y,		pstParams->average[0]);
				}
				else
				{
					PE_P1L_L9_RdFL(pe1_l_apl_ctrl_04);
					PE_P1L_L9_Rd01(pe1_l_apl_ctrl_04,	apl_r,		pstParams->average[0]);
					PE_P1L_L9_Rd01(pe1_l_apl_ctrl_04,	apl_g,		pstParams->average[1]);
					PE_P1L_L9_Rd01(pe1_l_apl_ctrl_04,	apl_b,		pstParams->average[2]);
				}
				PE_P1L_L9_RdFL(pe1_l_dce_hist_ia_ctrl);
				PE_P1L_L9_RdFL(pe1_l_dce_hsit_ia_data2);
				histo_data = PE_P1L_L9_Rd(pe1_l_dce_hsit_ia_data2);
				pstParams->min = GET_BITS(histo_data,0,10);
				pstParams->max = GET_BITS(histo_data,16,10);
				PE_P1L_L9_Rd01(pe1_l_dce_hist_ia_ctrl,	hif_mask,	histoUpdateMask);
				if(histoUpdateMask)	{	pstParams->histo_ready = 0;break;	}
				else				{	pstParams->histo_ready = 1;			}
				PE_P1L_L9_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:read mode, 1:normal mode
				PE_P1L_L9_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_ai,		0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_address,	0x0);	//bin address
				PE_P1L_L9_WrFL(pe1_l_dce_hist_ia_ctrl);
				for(count=0;count<pstParams->bin_num;count++)
				{
					PE_P1L_L9_RdFL(pe1_l_dce_hist_ia_data1);
					pstParams->histogram[count] = PE_P1L_L9_Rd(pe1_l_dce_hist_ia_data1);
				}
				PE_P1L_L9_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:read mode, 1:normal mode
				PE_P1L_L9_WrFL(pe1_l_dce_hist_ia_ctrl);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				if(pstParams->domain==LX_PE_YC_DOMAIN)
				{
					PE_P1R_L9_RdFL(pe1_r_apl_ctrl_03);
					PE_P1R_L9_Rd01(pe1_r_apl_ctrl_03,	apl_y,		pstParams->average[0]);
				}
				else
				{
					PE_P1R_L9_RdFL(pe1_r_apl_ctrl_04);
					PE_P1R_L9_Rd01(pe1_r_apl_ctrl_04,	apl_r,		pstParams->average[0]);
					PE_P1R_L9_Rd01(pe1_r_apl_ctrl_04,	apl_g,		pstParams->average[1]);
					PE_P1R_L9_Rd01(pe1_r_apl_ctrl_04,	apl_b,		pstParams->average[2]);
				}
				PE_P1R_L9_RdFL(pe1_r_dce_hist_ia_ctrl);
				PE_P1R_L9_RdFL(pe1_r_dce_hsit_ia_data2);				
				histo_data = PE_P1R_L9_Rd(pe1_r_dce_hsit_ia_data2);
				pstParams->min = GET_BITS(histo_data,0,10);
				pstParams->max = GET_BITS(histo_data,16,10);		
				PE_P1R_L9_Rd01(pe1_r_dce_hist_ia_ctrl,	hif_mask,	histoUpdateMask);
				if(histoUpdateMask)	{	pstParams->histo_ready = 0;break;	}
				else				{	pstParams->histo_ready = 1;			}
				PE_P1R_L9_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:read mode, 1:normal mode
				PE_P1R_L9_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_ai,		0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_address,	0x0);	//bin address
				PE_P1R_L9_WrFL(pe1_r_dce_hist_ia_ctrl);
				for(count=0;count<pstParams->bin_num;count++)
				{
					PE_P1R_L9_RdFL(pe1_r_dce_hist_ia_data1);
					pstParams->histogram[count] = PE_P1R_L9_Rd(pe1_r_dce_hist_ia_data1);
				}
				PE_P1R_L9_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_enable,	0x1);	//[15]	0:read mode, 1:normal mode
				PE_P1R_L9_WrFL(pe1_r_dce_hist_ia_ctrl);
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
int PE_DCM_HW_L9_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	PE_DCM_HW_L9_SETTINGS_T *pInfo=&_g_pe_dcm_hw_l9_info;
	UINT32 count, bin_mode, domain, min_pos, max_pos, lut_data, lut_step, step_unit;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		if(pstParams->domain==LX_PE_HSV_DOMAIN)				{domain=0;}	//scaled hsv
		else if(pstParams->domain==LX_PE_YC_DOMAIN)			{domain=1;}	//yc
		else if(pstParams->domain==LX_PE_ORG_HSV_DOMAIN)	{domain=2;}	//normal hsv
		else												{domain=3;}	//hsl
		if(pstParams->lut_step>32)		{lut_step=32;}
		else if(pstParams->lut_step==0)	{lut_step=1;}
		else							{lut_step=pstParams->lut_step;}
		min_pos = pstParams->min_pos;
		max_pos = pstParams->max_pos;
		if(lut_step==16)		{step_unit = 64;}
		else if(lut_step==32)	{step_unit = 32;}
		else					{step_unit = 1024/lut_step;}		// to make linear
		if(PE_KDRV_VER_L9BX)
		{
			if(pstParams->bin_mode==LX_PE_32_BINMODE)	{bin_mode=0x0;}
			else										{bin_mode=0x1;}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				/* dce config */
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_01);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ia_ctrl);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ia_data);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_08);
				//PE_P1L_L9B0_RdFL(pe1_l_dce_hist_ia_ctrl);
				PE_P1L_L9B0_RdFL(pe1_l_apl_ctrl_02);
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	hist_bin_mode,			bin_mode);				//32bin mode
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	window_mode_en,			0x1);					//window sync
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	window_acquire,			0x1);					//window acquire on
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	dce_domain_sel,			(domain==1)? 0x1:0x0);	//HSV or YC domain
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
				//PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_status_address,	0x0);				//V value for range
				PE_P1L_L9B0_Wr01(pe1_l_apl_ctrl_02,	apl_position,			(domain==1)? 0x0:0x2);	//0x0:PE1 input(Y/C),0x2:cen input(RGB)
				PE_P1L_L9B0_WrFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9B0_WrFL(pe1_l_dce_ctrl_01);
				//PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
				PE_P1L_L9B0_WrFL(pe1_l_apl_ctrl_02);
				if(domain!=1)	/* should set CEN block ON to use HSV DCE */
				{
					PE_P1L_L9B0_RdFL(pe1_l_cen_ctrl_00);
					PE_P1L_L9B0_Wr01(pe1_l_cen_ctrl_00,	reg_cen_bypass,	0x1);					//CEN block ON
					PE_P1L_L9B0_Wr01(pe1_l_cen_ctrl_00,	v_scaler_en,	(domain==0)? 0x1:0x0);	//v scaler en
					PE_P1L_L9B0_Wr01(pe1_l_cen_ctrl_00,	demo_mode,		0x0);
					PE_P1L_L9B0_Wr01(pe1_l_cen_ctrl_00,	vsp_sel,		(domain==3)? 0x0:0x1);	//0:hsl,1:hsv
					PE_P1L_L9B0_WrFL(pe1_l_cen_ctrl_00);
				}
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1L_L9B0_WrFL(pe1_l_dce_ia_ctrl);
				pInfo->conf[LX_PE_WIN_0].lut_step = lut_step;
				lut_data = 0;
				for(count=0;count<32;count++)
				{
					if(lut_data>0x3ff)	lut_data=0x3ff;
					PE_P1L_L9B0_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1L_L9B0_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,0,10));	//x data
					PE_P1L_L9B0_WrFL(pe1_l_dce_ia_data);
					lut_data += step_unit;
				}
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_08,	hif_dyc_wdata_y_32nd,	0x3ff);	//y data
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_08,	hif_dyc_wdata_x_32nd,	0x3ff);	//x data
				PE_P1L_L9B0_WrFL(pe1_l_dce_ctrl_08);
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable,		0x1);		//0:host access, 1:normal mode
				PE_P1L_L9B0_WrFL(pe1_l_dce_ia_ctrl);

				/* dse config */
				PE_P1L_L9B0_RdFL(pe1_l_dse_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_dse_ctrl_00,	dynamic_saturation_en,	0x1);
				PE_P1L_L9B0_Wr01(pe1_l_dse_ctrl_00,	window_mode_en,			0x1);	//window sync
				PE_P1L_L9B0_Wr01(pe1_l_dse_ctrl_00,	window_acquire,			0x1);	//window acquire on
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
				PE_P1L_L9B0_WrFL(pe1_l_dse_ctrl_00);

				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_load,	 	0x0);		//0:clear, 1:enable
				PE_P1L_L9B0_WrFL(pe1_l_dse_ia_ctrl);
				lut_data = 0;
				for(count=0;count<32;count++)
				{
					if(lut_data>0x3ff)	lut_data=0x3ff;
					pInfo->dse_lut[LX_PE_WIN_0][count]=((lut_data<<16)|(lut_data));
					PE_P1L_L9B0_Wr01(pe1_l_dse_ia_data,	hif_dse_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1L_L9B0_Wr01(pe1_l_dse_ia_data,	hif_dse_wdata_x,	GET_BITS(lut_data,0,10));	//x data
					PE_P1L_L9B0_WrFL(pe1_l_dse_ia_data);
					lut_data += step_unit;
				}
				PE_P1L_L9B0_Wr01(pe1_l_dse_ctrl_02,	hif_dse_wdata_y_32nd,	0x3ff);	//y data
				PE_P1L_L9B0_Wr01(pe1_l_dse_ctrl_02,	hif_dse_wdata_x_32nd,	0x3ff);	//x data
				PE_P1L_L9B0_WrFL(pe1_l_dse_ctrl_02);
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_load,	 	0x1);		//0:clear, 1:enable
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_P1L_L9B0_WrFL(pe1_l_dse_ia_ctrl);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_01);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ia_ctrl);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ia_data);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_08);
				//PE_P1R_L9B0_RdFL(pe1_r_dce_hist_ia_ctrl);
				PE_P1R_L9B0_RdFL(pe1_r_apl_ctrl_02);
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	hist_bin_mode,			bin_mode);				//32bin mode
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	window_mode_en,			0x1);					//window sync
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	window_acquire,			0x1);					//window acquire on
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	dce_domain_sel,			(domain==1)? 0x1:0x0);	//HSV or YC ddomain
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	win_selection,			0x0);					//from pe1 win2
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
				//PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_status_address,	0x0);				//V value for range
				PE_P1R_L9B0_Wr01(pe1_r_apl_ctrl_02,	apl_position,			(domain==1)? 0x0:0x2);	//0x0:PE1 input(Y/C),0x2:cen input(RGB)
				PE_P1R_L9B0_WrFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9B0_WrFL(pe1_r_dce_ctrl_01);
				//PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);
				PE_P1R_L9B0_WrFL(pe1_r_apl_ctrl_02);
				if(domain!=1)	/* should set CEN block ON to use HSV DCE */
				{
					PE_P1R_L9B0_RdFL(pe1_r_cen_ctrl_00);
					PE_P1R_L9B0_Wr01(pe1_r_cen_ctrl_00,	reg_cen_bypass,	0x1);					//CEN block ON
					PE_P1R_L9B0_Wr01(pe1_r_cen_ctrl_00,	v_scaler_en,	(domain==0)? 0x1:0x0);	//v scaler en
					PE_P1R_L9B0_Wr01(pe1_r_cen_ctrl_00,	demo_mode,		0x0);
					PE_P1R_L9B0_Wr01(pe1_r_cen_ctrl_00,	vsp_sel,		(domain==3)? 0x0:0x1);	//0:hsl,1:hsv
					PE_P1R_L9B0_WrFL(pe1_r_cen_ctrl_00);
				}
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1R_L9B0_WrFL(pe1_r_dce_ia_ctrl);
				pInfo->conf[LX_PE_WIN_1].lut_step = lut_step;
				lut_data = 0;
				for(count=0;count<32;count++)
				{
					if(lut_data>0x3ff)	lut_data=0x3ff;		
					PE_P1R_L9B0_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1R_L9B0_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,0,10));	//x data
					PE_P1R_L9B0_WrFL(pe1_r_dce_ia_data);
					lut_data += step_unit;
				}
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_08,	hif_dyc_wdata_y_32nd,	0x3ff);	//y data
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_08,	hif_dyc_wdata_x_32nd,	0x3ff);	//x data
				PE_P1R_L9B0_WrFL(pe1_r_dce_ctrl_08);
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable,		0x1);		//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_P1R_L9B0_WrFL(pe1_r_dce_ia_ctrl);

				/* dse config */
				PE_P1R_L9B0_RdFL(pe1_r_dse_ctrl_00);
				PE_P1R_L9B0_Wr01(pe1_r_dse_ctrl_00,	dynamic_saturation_en,	0x1);
				PE_P1R_L9B0_Wr01(pe1_r_dse_ctrl_00,	window_mode_en,			0x1);	//window sync
				PE_P1R_L9B0_Wr01(pe1_r_dse_ctrl_00,	window_acquire,			0x1);	//window acquire on
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	win_selection,			0x0);	//from pe1 win2
				PE_P1R_L9B0_WrFL(pe1_r_dse_ctrl_00);

				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_P1R_L9B0_WrFL(pe1_r_dse_ia_ctrl);
				lut_data = 0;
				for(count=0;count<32;count++)
				{
					if(lut_data>0x3ff)	lut_data=0x3ff;
					pInfo->dse_lut[LX_PE_WIN_1][count]=((lut_data<<16)|(lut_data));
					PE_P1R_L9B0_Wr01(pe1_r_dse_ia_data,	hif_dse_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1R_L9B0_Wr01(pe1_r_dse_ia_data,	hif_dse_wdata_x,	GET_BITS(lut_data,0,10));	//x data
					PE_P1R_L9B0_WrFL(pe1_r_dse_ia_data);
					lut_data += step_unit;
				}
				PE_P1R_L9B0_Wr01(pe1_r_dse_ctrl_02,	hif_dse_wdata_y_32nd,	0x3ff);	//y data
				PE_P1R_L9B0_Wr01(pe1_r_dse_ctrl_02,	hif_dse_wdata_x_32nd,	0x3ff);	//x data
				PE_P1R_L9B0_WrFL(pe1_r_dse_ctrl_02);
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_enable,		0x1);		//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_P1R_L9B0_WrFL(pe1_r_dse_ia_ctrl);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(pstParams->bin_mode==LX_PE_16_BINMODE)		{bin_mode=0x2;}
			else if(pstParams->bin_mode==LX_PE_32_BINMODE)	{bin_mode=0x1;}
			else											{bin_mode=0x0;}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9_RdFL(pe1_l_dce_ctrl_01);
				PE_P1L_L9_RdFL(pe1_l_dce_ia_ctrl);
				PE_P1L_L9_RdFL(pe1_l_dce_ia_data);
				PE_P1L_L9_RdFL(pe1_l_dce_ctrl_08);
				PE_P1L_L9_RdFL(pe1_l_dce_hist_ia_ctrl);
				PE_P1L_L9_RdFL(pe1_l_apl_ctrl_02);
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_00,	hist_bin_mode,			bin_mode);				//32bin mode
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_00,	hist_bin_bitwidth_mode,	0x0);					//21bit full read
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_00,	window_mode_en,			0x1);					//window sync
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_00,	window_acquire,			0x1);					//window acquire on
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_00,	dce_domain_sel,			(domain==1)? 0x1:0x0);	//HSV or YC domain
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_00,	win_selection,			0x1);					//from bbd
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
				PE_P1L_L9_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_status_address,	0x0);					//Maximum V value for one frame
				PE_P1L_L9_Wr01(pe1_l_apl_ctrl_02,	apl_position,			(domain==1)? 0x0:0x2);	//0x0:PE1 input(Y/C),0x2:cen input(RGB)
				PE_P1L_L9_WrFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9_WrFL(pe1_l_dce_ctrl_01);
				PE_P1L_L9_WrFL(pe1_l_dce_hist_ia_ctrl);
				PE_P1L_L9_WrFL(pe1_l_apl_ctrl_02);
				if(domain!=1)	/* should set CEN block ON to use HSV DCE */
				{
					PE_P1L_L9_RdFL(pe1_l_cen_ctrl_00);
					PE_P1L_L9_Wr01(pe1_l_cen_ctrl_00,	cen_bypass,		0x1);					//CEN block ON
					PE_P1L_L9_Wr01(pe1_l_cen_ctrl_00,	v_scaler_en,	(domain==0)? 0x1:0x0);	//v scaler en
					PE_P1L_L9_WrFL(pe1_l_cen_ctrl_00);
				}
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1L_L9_WrFL(pe1_l_dce_ia_ctrl);
				pInfo->conf[LX_PE_WIN_0].lut_step = lut_step;
				lut_data = 0;
				for(count=0;count<32;count++)
				{
					if(lut_data>0x3ff)	lut_data=0x3ff;
					PE_P1L_L9_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1L_L9_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,0,10));	//x data
					PE_P1L_L9_WrFL(pe1_l_dce_ia_data);
					lut_data += step_unit;
				}
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_08,	hif_dyc_wdata_y_32nd,	0x3ff);	//y data
				PE_P1L_L9_Wr01(pe1_l_dce_ctrl_08,	hif_dyc_wdata_x_32nd,	0x3ff);	//x data
				PE_P1L_L9_WrFL(pe1_l_dce_ctrl_08);
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable,		0x1);		//0:host access, 1:normal mode
				PE_P1L_L9_WrFL(pe1_l_dce_ia_ctrl);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9_RdFL(pe1_r_dce_ctrl_01);
				PE_P1R_L9_RdFL(pe1_r_dce_ia_ctrl);
				PE_P1R_L9_RdFL(pe1_r_dce_ia_data);
				PE_P1R_L9_RdFL(pe1_r_dce_ctrl_08);
				PE_P1R_L9_RdFL(pe1_r_dce_hist_ia_ctrl);
				PE_P1R_L9_RdFL(pe1_r_apl_ctrl_02);
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_00,	dynamic_contrast_en,	0x1);					//enable
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_00,	hist_bin_mode,			bin_mode);				//32bin mode
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_00,	hist_bin_bitwidth_mode,	0x0);					//21bit full read
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_00,	window_mode_en,			0x1);					//window sync
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_00,	window_acquire,			0x1);					//window acquire on
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_00,	dce_domain_sel,			(domain==1)? 0x1:0x0);	//HSV or YC ddomain
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_00,	win_selection,			0x1);					//from bbd
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_01,	hist_bin_min_position,	min_pos);				//min position
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_01,	hist_bin_max_position,	max_pos);				//max position
				PE_P1R_L9_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_status_address,	0x0);					//Maximum V value for one frame
				PE_P1R_L9_Wr01(pe1_r_apl_ctrl_02,	apl_position,			(domain==1)? 0x0:0x2);	//0x0:PE1 input(Y/C),0x2:cen input(RGB)
				PE_P1R_L9_WrFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9_WrFL(pe1_r_dce_ctrl_01);
				PE_P1R_L9_WrFL(pe1_r_dce_hist_ia_ctrl);
				PE_P1R_L9_WrFL(pe1_r_apl_ctrl_02);
				if(domain!=1)	/* should set CEN block ON to use HSV DCE */
				{
					PE_P1R_L9_RdFL(pe1_r_cen_ctrl_00);
					PE_P1R_L9_Wr01(pe1_r_cen_ctrl_00,	cen_bypass,		0x1);					//CEN block ON
					PE_P1R_L9_Wr01(pe1_r_cen_ctrl_00,	v_scaler_en,	(domain==0)? 0x1:0x0);	//v scaler en
					PE_P1R_L9_WrFL(pe1_r_cen_ctrl_00);
				}
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1R_L9_WrFL(pe1_r_dce_ia_ctrl);
				pInfo->conf[LX_PE_WIN_1].lut_step = lut_step;
				lut_data = 0;
				for(count=0;count<32;count++)
				{
					if(lut_data>0x3ff)	lut_data=0x3ff;		
					PE_P1R_L9_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1R_L9_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,0,10));	//x data
					PE_P1R_L9_WrFL(pe1_r_dce_ia_data);
					lut_data += step_unit;
				}
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_08,	hif_dyc_wdata_y_32nd,	0x3ff);	//y data
				PE_P1R_L9_Wr01(pe1_r_dce_ctrl_08,	hif_dyc_wdata_x_32nd,	0x3ff);	//x data
				PE_P1R_L9_WrFL(pe1_r_dce_ctrl_08);
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable,		0x1);		//0:host access, 1:normal mode
				PE_P1R_L9_WrFL(pe1_r_dce_ia_ctrl);
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
int PE_DCM_HW_L9_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 bin_mode=0;
	UINT32 domain=0;
	UINT32 min_pos=0;
	UINT32 max_pos=0;
	UINT32 v_scl_en=0;
	PE_DCM_HW_L9_SETTINGS_T *pInfo=&_g_pe_dcm_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_01);
				PE_P1L_L9B0_RdFL(pe1_l_cen_ctrl_00);
				PE_P1L_L9B0_Rd01(pe1_l_dce_ctrl_00,	hist_bin_mode,			bin_mode);	//32bin mode
				PE_P1L_L9B0_Rd01(pe1_l_dce_ctrl_00,	dce_domain_sel,			domain);	//HSV or YC domain
				PE_P1L_L9B0_Rd01(pe1_l_dce_ctrl_01,	hist_bin_min_position,	min_pos);	//min position
				PE_P1L_L9B0_Rd01(pe1_l_dce_ctrl_01,	hist_bin_max_position,	max_pos);	//max position
				PE_P1L_L9B0_Rd01(pe1_l_cen_ctrl_00,	v_scaler_en,			v_scl_en);	//V scaler en
				pstParams->bin_mode = bin_mode? LX_PE_16_BINMODE:LX_PE_32_BINMODE;
				pstParams->domain = domain? LX_PE_YC_DOMAIN:(v_scl_en? LX_PE_HSV_DOMAIN:LX_PE_ORG_HSV_DOMAIN);
				pstParams->min_pos = min_pos;
				pstParams->max_pos = max_pos;
				pstParams->lut_step = pInfo->conf[LX_PE_WIN_0].lut_step;
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_01);
				PE_P1R_L9B0_RdFL(pe1_r_cen_ctrl_00);
				PE_P1R_L9B0_Rd01(pe1_r_dce_ctrl_00,	hist_bin_mode,			bin_mode);	//32bin mode
				PE_P1R_L9B0_Rd01(pe1_r_dce_ctrl_00,	dce_domain_sel,			domain);	//HSV or YC domain
				PE_P1R_L9B0_Rd01(pe1_r_dce_ctrl_01,	hist_bin_min_position,	min_pos);	//min position
				PE_P1R_L9B0_Rd01(pe1_r_dce_ctrl_01,	hist_bin_max_position,	max_pos);	//max position
				PE_P1R_L9B0_Rd01(pe1_r_cen_ctrl_00,	v_scaler_en,			v_scl_en);	//V scaler en
				pstParams->bin_mode = bin_mode? LX_PE_16_BINMODE:LX_PE_32_BINMODE;
				pstParams->domain = domain? LX_PE_YC_DOMAIN:(v_scl_en? LX_PE_HSV_DOMAIN:LX_PE_ORG_HSV_DOMAIN);
				pstParams->min_pos = min_pos;
				pstParams->max_pos = max_pos;
				pstParams->lut_step = pInfo->conf[LX_PE_WIN_1].lut_step;
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9_RdFL(pe1_l_dce_ctrl_01);
				PE_P1L_L9_RdFL(pe1_l_cen_ctrl_00);
				PE_P1L_L9_Rd01(pe1_l_dce_ctrl_00,	hist_bin_mode,			bin_mode);	//32bin mode
				PE_P1L_L9_Rd01(pe1_l_dce_ctrl_00,	dce_domain_sel,			domain);	//HSV or YC domain
				PE_P1L_L9_Rd01(pe1_l_dce_ctrl_01,	hist_bin_min_position,	min_pos);	//min position
				PE_P1L_L9_Rd01(pe1_l_dce_ctrl_01,	hist_bin_max_position,	max_pos);	//max position
				PE_P1L_L9_Rd01(pe1_l_cen_ctrl_00,	v_scaler_en,			v_scl_en);	//V scaler en		
				pstParams->bin_mode = (LX_PE_BINMODE)bin_mode;
				pstParams->domain = domain? LX_PE_YC_DOMAIN:(v_scl_en? LX_PE_HSV_DOMAIN:LX_PE_ORG_HSV_DOMAIN);
				pstParams->min_pos = min_pos;
				pstParams->max_pos = max_pos;
				pstParams->lut_step = pInfo->conf[LX_PE_WIN_0].lut_step;
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9_RdFL(pe1_r_dce_ctrl_01);
				PE_P1R_L9_RdFL(pe1_r_cen_ctrl_00);
				PE_P1R_L9_Rd01(pe1_r_dce_ctrl_00,	hist_bin_mode,			bin_mode);	//32bin mode
				PE_P1R_L9_Rd01(pe1_r_dce_ctrl_00,	dce_domain_sel,			domain);	//HSV or YC domain
				PE_P1R_L9_Rd01(pe1_r_dce_ctrl_01,	hist_bin_min_position,	min_pos);	//min position
				PE_P1R_L9_Rd01(pe1_r_dce_ctrl_01,	hist_bin_max_position,	max_pos);	//max position
				PE_P1R_L9_Rd01(pe1_r_cen_ctrl_00,	v_scaler_en,			v_scl_en);	//V scaler en
				pstParams->bin_mode = (LX_PE_BINMODE)bin_mode;
				pstParams->domain = domain? LX_PE_YC_DOMAIN:(v_scl_en? LX_PE_HSV_DOMAIN:LX_PE_ORG_HSV_DOMAIN);
				pstParams->min_pos = min_pos;
				pstParams->max_pos = max_pos;
				pstParams->lut_step = pInfo->conf[LX_PE_WIN_1].lut_step;
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
int PE_DCM_HW_L9_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count=0;
	UINT32 lut_data=0;
	UINT32 lut_step=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		if(pstParams->size>32)		{lut_step=32;}
		else if(pstParams->size==0)	{lut_step=1;}
		else						{lut_step=pstParams->size;}
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_dce_ia_ctrl);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ia_data);
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1L_L9B0_WrFL(pe1_l_dce_ia_ctrl);
				for(count=0;count<lut_step;count++)
				{
					lut_data = pstParams->data[count];
					PE_P1L_L9B0_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1L_L9B0_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,16,10));	//x data
					PE_P1L_L9B0_WrFL(pe1_l_dce_ia_data);
				}
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_P1L_L9B0_WrFL(pe1_l_dce_ia_ctrl);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_dce_ia_ctrl);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ia_data);
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1R_L9B0_WrFL(pe1_r_dce_ia_ctrl);
				for(count=0;count<lut_step;count++)
				{
					lut_data = pstParams->data[count];		
					PE_P1R_L9B0_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1R_L9B0_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,16,10));	//x data
					PE_P1R_L9B0_WrFL(pe1_r_dce_ia_data);
				}
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_P1R_L9B0_WrFL(pe1_r_dce_ia_ctrl);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_dce_ia_ctrl);
				PE_P1L_L9_RdFL(pe1_l_dce_ia_data);
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1L_L9_WrFL(pe1_l_dce_ia_ctrl);
				for(count=0;count<lut_step;count++)
				{
					lut_data = pstParams->data[count];
					PE_P1L_L9_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1L_L9_Wr01(pe1_l_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,16,10));	//x data
					PE_P1L_L9_WrFL(pe1_l_dce_ia_data);
				}
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_P1L_L9_WrFL(pe1_l_dce_ia_ctrl);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_dce_ia_ctrl);
				PE_P1R_L9_RdFL(pe1_r_dce_ia_data);
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1R_L9_WrFL(pe1_r_dce_ia_ctrl);
				for(count=0;count<lut_step;count++)
				{
					lut_data = pstParams->data[count];		
					PE_P1R_L9_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1R_L9_Wr01(pe1_r_dce_ia_data,	hif_dyc_wdata_x,	GET_BITS(lut_data,16,10));	//x data
					PE_P1R_L9_WrFL(pe1_r_dce_ia_data);
				}
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_load,	 	0x1);	//0:clear, 1:enable
				PE_P1R_L9_WrFL(pe1_r_dce_ia_ctrl);
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
int PE_DCM_HW_L9_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_dce_ia_ctrl);
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1L_L9B0_WrFL(pe1_l_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					PE_P1L_L9B0_RdFL(pe1_l_dce_ia_data);
					pstParams->data[count] = PE_P1L_L9B0_Rd(pe1_l_dce_ia_data);
				}
				PE_P1L_L9B0_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1L_L9B0_WrFL(pe1_l_dce_ia_ctrl);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_dce_ia_ctrl);
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1R_L9B0_WrFL(pe1_r_dce_ia_ctrl);		
				for(count=0;count<(pstParams->size);count++)
				{
					PE_P1R_L9B0_RdFL(pe1_r_dce_ia_data);
					pstParams->data[count] = PE_P1R_L9B0_Rd(pe1_r_dce_ia_data);
				}
				PE_P1R_L9B0_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1R_L9B0_WrFL(pe1_r_dce_ia_ctrl);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_dce_ia_ctrl);
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1L_L9_WrFL(pe1_l_dce_ia_ctrl);
				for(count=0;count<(pstParams->size);count++)
				{
					PE_P1L_L9_RdFL(pe1_l_dce_ia_data);
					pstParams->data[count] = PE_P1L_L9_Rd(pe1_l_dce_ia_data);
				}
				PE_P1L_L9_Wr01(pe1_l_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1L_L9_WrFL(pe1_l_dce_ia_ctrl);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_dce_ia_ctrl);
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable, 	0x0);	//0:host access, 1:normal mode
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_ai, 		0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dyc_address,	0x0);	//address
				PE_P1R_L9_WrFL(pe1_r_dce_ia_ctrl);		
				for(count=0;count<(pstParams->size);count++)
				{
					PE_P1R_L9_RdFL(pe1_r_dce_ia_data);
					pstParams->data[count] = PE_P1R_L9_Rd(pe1_r_dce_ia_data);
				}
				PE_P1R_L9_Wr01(pe1_r_dce_ia_ctrl,	hif_dce_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1R_L9_WrFL(pe1_r_dce_ia_ctrl);
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
int PE_DCM_HW_L9_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count=0;
	UINT32 lut_data=0;
	UINT32 lut_step=0;
	PE_DCM_HW_L9_SETTINGS_T *pInfo=&_g_pe_dcm_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		if(pstParams->size>32)		{lut_step=32;}
		else if(pstParams->size==0)	{lut_step=1;}
		else						{lut_step=pstParams->size;}
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_dse_ia_ctrl);
				PE_P1L_L9B0_RdFL(pe1_l_dse_ia_data);
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_P1L_L9B0_WrFL(pe1_l_dse_ia_ctrl);
				for(count=0;count<lut_step;count++)
				{
					lut_data = pstParams->data[count];
					pInfo->dse_lut[LX_PE_WIN_0][count]=((lut_data<<16)|(lut_data));
					PE_P1L_L9B0_Wr01(pe1_l_dse_ia_data,	hif_dse_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1L_L9B0_Wr01(pe1_l_dse_ia_data,	hif_dse_wdata_x,	GET_BITS(lut_data,16,10));	//x data
					PE_P1L_L9B0_WrFL(pe1_l_dse_ia_data);
				}
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1L_L9B0_Wr01(pe1_l_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_P1L_L9B0_WrFL(pe1_l_dse_ia_ctrl);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_dse_ia_ctrl);
				PE_P1R_L9B0_RdFL(pe1_r_dse_ia_data);
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_enable,		0x0);	//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_ai,			0x1);	//ai 0:disable, 1:enable
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_address,	0x0);	//address
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_load,	 	0x0);	//0:clear, 1:enable
				PE_P1R_L9B0_WrFL(pe1_r_dse_ia_ctrl);
				for(count=0;count<lut_step;count++)
				{
					lut_data = pstParams->data[count];
					pInfo->dse_lut[LX_PE_WIN_1][count]=((lut_data<<16)|(lut_data));
					PE_P1R_L9B0_Wr01(pe1_r_dse_ia_data,	hif_dse_wdata_y,	GET_BITS(lut_data,0,10));	//y data
					PE_P1R_L9B0_Wr01(pe1_r_dse_ia_data,	hif_dse_wdata_x,	GET_BITS(lut_data,16,10));	//x data
					PE_P1R_L9B0_WrFL(pe1_r_dse_ia_data);
				}
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_enable, 	0x1);	//0:host access, 1:normal mode
				PE_P1R_L9B0_Wr01(pe1_r_dse_ia_ctrl,	hif_dse_load,	 	0x1);	//0:clear, 1:enable
				PE_P1R_L9B0_WrFL(pe1_r_dse_ia_ctrl);
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
int PE_DCM_HW_L9_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	PE_DCM_HW_L9_SETTINGS_T *pInfo=&_g_pe_dcm_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				for(count=0;count<(pstParams->size);count++)
				{
					pstParams->data[count] = pInfo->dse_lut[LX_PE_WIN_0][count];
				}
			}
			if(PE_CHECK_WIN1(win_id))
			{	
				for(count=0;count<(pstParams->size);count++)
				{
					pstParams->data[count] = pInfo->dse_lut[LX_PE_WIN_1][count];
				}
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
int PE_DCM_HW_L9_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	UINT32 color_out_gain;
	UINT32 region_sel;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		color_out_gain = pstParams->color_out_gain;
		region_sel = pstParams->region_sel;
		PE_DCM_HW_L9_CHECK_CODE(!color_out_gain,return RET_ERROR,"[%s,%d] color_out_gain is zero.\n",__F__,__L__);
		PE_DCM_HW_L9_CHECK_CODE(color_out_gain>0xff,return RET_ERROR,\
			"[%s,%d] color_out_gain(%d) is over.\n",__F__,__L__,color_out_gain);
		PE_DCM_HW_L9_DBG_PRINT("set pstParams[%d] : color_out_gain:%d\n",pstParams->win_id,color_out_gain);
		if(_g_dcm_hw_l9_trace)
		{
			UINT32 i,sel;
			for(i=0;i<16;i++)
			{
				sel = ((region_sel>>i)&0x1);
				PE_DCM_HW_L9_DBG_PRINT("[%2d]%d\n",i,sel);
			}
		}
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_01);
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region0_sel,	GET_BITS(region_sel,0,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region1_sel,	GET_BITS(region_sel,1,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region2_sel,	GET_BITS(region_sel,2,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region3_sel,	GET_BITS(region_sel,3,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region4_sel,	GET_BITS(region_sel,4,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region5_sel,	GET_BITS(region_sel,5,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region6_sel,	GET_BITS(region_sel,6,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region7_sel,	GET_BITS(region_sel,7,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region8_sel,	GET_BITS(region_sel,8,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region9_sel,	GET_BITS(region_sel,9,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region10_sel,	GET_BITS(region_sel,10,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region11_sel,	GET_BITS(region_sel,11,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region12_sel,	GET_BITS(region_sel,12,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region13_sel,	GET_BITS(region_sel,13,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region14_sel,	GET_BITS(region_sel,14,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	color_region15_sel,	GET_BITS(region_sel,15,1));
				PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_01,	color_region_gain,	GET_BITS(color_out_gain,0,8));
				PE_P1L_L9B0_WrFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9B0_WrFL(pe1_l_dce_ctrl_01);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_01);
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region0_sel,	GET_BITS(region_sel,0,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region1_sel,	GET_BITS(region_sel,1,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region2_sel,	GET_BITS(region_sel,2,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region3_sel,	GET_BITS(region_sel,3,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region4_sel,	GET_BITS(region_sel,4,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region5_sel,	GET_BITS(region_sel,5,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region6_sel,	GET_BITS(region_sel,6,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region7_sel,	GET_BITS(region_sel,7,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region8_sel,	GET_BITS(region_sel,8,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region9_sel,	GET_BITS(region_sel,9,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region10_sel,	GET_BITS(region_sel,10,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region11_sel,	GET_BITS(region_sel,11,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region12_sel,	GET_BITS(region_sel,12,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region13_sel,	GET_BITS(region_sel,13,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region14_sel,	GET_BITS(region_sel,14,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_00,	color_region15_sel,	GET_BITS(region_sel,15,1));
				PE_P1R_L9B0_Wr01(pe1_r_dce_ctrl_01,	color_region_gain,	GET_BITS(color_out_gain,0,8));
				PE_P1R_L9B0_WrFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9B0_WrFL(pe1_r_dce_ctrl_01);
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);	
	return ret;
}
int PE_DCM_HW_L9_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 r_data;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_00);
				PE_P1L_L9B0_RdFL(pe1_l_dce_ctrl_01);
				PE_P1L_L9B0_Rd01(pe1_l_dce_ctrl_01,	color_region_gain,	pstParams->color_out_gain);
				r_data = PE_P1L_L9B0_Rd(pe1_l_dce_ctrl_00);
				pstParams->region_sel = GET_BITS(r_data,8,16);	//[23:8]
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_00);
				PE_P1R_L9B0_RdFL(pe1_r_dce_ctrl_01);
				PE_P1R_L9B0_Rd01(pe1_r_dce_ctrl_01,	color_region_gain,	pstParams->color_out_gain);
				r_data = PE_P1R_L9B0_Rd(pe1_r_dce_ctrl_00);
				pstParams->region_sel = GET_BITS(r_data,8,16);	//[23:8]
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do.\n");
		}
		PE_DCM_HW_L9_DBG_PRINT("get pstParams[%d] : color_out_gain:%d\n",pstParams->win_id,pstParams->color_out_gain);
		if(_g_dcm_hw_l9_trace)
		{
			UINT32 i,sel;
			for(i=0;i<16;i++)
			{
				sel = ((pstParams->region_sel>>i)&0x1);
				PE_DCM_HW_L9_DBG_PRINT("[%2d]%d\n",i,sel);
			}
		}
	} while (0);	
	return ret;
}
int PE_DCM_HW_L9_GetDceAllHistogram(PE_DCM_HW_L9_HISTO_T *pstMainParams,PE_DCM_HW_L9_HISTO_T *pstSubParams,UINT32 *validL,UINT32 *validR)
{
	int ret = RET_OK;
	UINT32 count=0, r_data=0;
	UINT32 histoUpdateMaskL=0,histoUpdateMaskR=0;
	PE_DCM_HW_L9_SETTINGS_T *pInfo=&_g_pe_dcm_hw_l9_info;
	do {
		CHECK_KNULL(pstMainParams);
		CHECK_KNULL(pstSubParams);
		if(PE_KDRV_VER_L9BX)
		{
			*validL = *validR = 0;
			PE_P1L_L9B0_RdFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1R_L9B0_RdFL(pe1_r_dce_hist_ia_ctrl);
			PE_P1L_L9B0_Rd01(pe1_l_dce_hist_ia_ctrl,	hif_mask,	histoUpdateMaskL);
			PE_P1R_L9B0_Rd01(pe1_r_dce_hist_ia_ctrl,	hif_mask,	histoUpdateMaskR);
			if(histoUpdateMaskL || histoUpdateMaskR)
			{
				for(count=0;count<pstMainParams->bin_num;count++)
				{
					pstMainParams->histogram[count]	= pInfo->histo_info[LX_PE_WIN_0].histogram[count];
					pstSubParams->histogram[count]	= pInfo->histo_info[LX_PE_WIN_1].histogram[count];
				}
				*validL = histoUpdateMaskL;
				*validR = histoUpdateMaskR;
				ret = RET_OK;
				break;
			}
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:read mode, 1:normal mode
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_ai,		0x1);	//ai 0:disable, 1:enable
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_address,	0x0);	//bin address
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:read mode, 1:normal mode
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_ai,		0x1);	//ai 0:disable, 1:enable
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_address,	0x0);	//bin address
			PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);
			for(count=0;count<pstMainParams->bin_num;count++)
			{
				PE_P1L_L9B0_RdFL(pe1_l_dce_hist_ia_data1);
				pstMainParams->histogram[count] = PE_P1L_L9B0_Rd(pe1_l_dce_hist_ia_data1);
				pInfo->histo_info[LX_PE_WIN_0].histogram[count] = pstMainParams->histogram[count];
				PE_P1R_L9B0_RdFL(pe1_r_dce_hist_ia_data1);
				pstSubParams->histogram[count] = PE_P1R_L9B0_Rd(pe1_r_dce_hist_ia_data1);
				pInfo->histo_info[LX_PE_WIN_1].histogram[count] = pstSubParams->histogram[count];
			}
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:read mode, 1:normal mode
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:read mode, 1:normal mode
			PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);

			PE_P1L_L9B0_RdFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1R_L9B0_RdFL(pe1_r_dce_hist_ia_ctrl);
			/* Rd status 0 */
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_status_address,	0x0);
			PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1L_L9B0_RdFL(pe1_l_dce_hsit_ia_data2);
			r_data = PE_P1L_L9B0_Rd(pe1_l_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_0].status[0] = pstMainParams->status[0] = r_data;
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_status_address,	0x0);
			PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);
			PE_P1R_L9B0_RdFL(pe1_r_dce_hsit_ia_data2);
			r_data = PE_P1R_L9B0_Rd(pe1_r_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_1].status[0] = pstSubParams->status[0] = r_data;
			/* Rd status 1 */
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_status_address,	0x1);
			PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1L_L9B0_RdFL(pe1_l_dce_hsit_ia_data2);
			r_data = PE_P1L_L9B0_Rd(pe1_l_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_0].status[1] = pstMainParams->status[1] = r_data;
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_status_address,	0x1);
			PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);
			PE_P1R_L9B0_RdFL(pe1_r_dce_hsit_ia_data2);
			r_data = PE_P1R_L9B0_Rd(pe1_r_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_1].status[1] = pstSubParams->status[1] = r_data;
			/* Rd status 2 */
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_status_address,	0x2);
			PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1L_L9B0_RdFL(pe1_l_dce_hsit_ia_data2);
			r_data = PE_P1L_L9B0_Rd(pe1_l_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_0].status[2] = pstMainParams->status[2] = r_data;
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_status_address,	0x2);
			PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);
			PE_P1R_L9B0_RdFL(pe1_r_dce_hsit_ia_data2);
			r_data = PE_P1R_L9B0_Rd(pe1_r_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_1].status[2] = pstSubParams->status[2] = r_data;
			/* Rd status 3 */
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_status_address,	0x3);
			PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1L_L9B0_RdFL(pe1_l_dce_hsit_ia_data2);
			r_data = PE_P1L_L9B0_Rd(pe1_l_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_0].status[3] = pstMainParams->status[3] = r_data;
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_status_address,	0x3);
			PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);
			PE_P1R_L9B0_RdFL(pe1_r_dce_hsit_ia_data2);
			r_data = PE_P1R_L9B0_Rd(pe1_r_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_1].status[3] = pstSubParams->status[3] = r_data;
			/* Rd status 4 */
			PE_P1L_L9B0_Wr01(pe1_l_dce_hist_ia_ctrl,	hif_status_address,	0x4);
			PE_P1L_L9B0_WrFL(pe1_l_dce_hist_ia_ctrl);
			PE_P1L_L9B0_RdFL(pe1_l_dce_hsit_ia_data2);
			r_data = PE_P1L_L9B0_Rd(pe1_l_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_0].status[4] = pstMainParams->status[4] = r_data;
			PE_P1R_L9B0_Wr01(pe1_r_dce_hist_ia_ctrl,	hif_status_address,	0x4);
			PE_P1R_L9B0_WrFL(pe1_r_dce_hist_ia_ctrl);
			PE_P1R_L9B0_RdFL(pe1_r_dce_hsit_ia_data2);
			r_data = PE_P1R_L9B0_Rd(pe1_r_dce_hsit_ia_data2);
			pInfo->histo_info[LX_PE_WIN_1].status[4] = pstSubParams->status[4] = r_data;
			/* Rd saturation status */
			PE_P0L_L9B_QRd01(tpd_stat_00,	reg_s_status,	r_data);
			pInfo->histo_info[LX_PE_WIN_0].sat_status = pstMainParams->sat_status = r_data;
			pInfo->histo_info[LX_PE_WIN_1].sat_status = pstSubParams->sat_status = r_data;
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
int PE_DCM_HW_L9_GetCurDcmSettings(PE_DCM_HW_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 count=0;
	PE_DCM_HW_L9_SETTINGS_T *pInfo=&_g_pe_dcm_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9BX)
		{
			pstParams->histo_info[LX_PE_WIN_0].sat_status=pInfo->histo_info[LX_PE_WIN_0].sat_status;
			if(_g_dcm_hw_l9_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_DCM_HW_L9_DBG_PRINT("get pstParams : sat_stat[0]:%d\n",\
						pstParams->histo_info[LX_PE_WIN_0].sat_status);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_DCM_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return ret;
}

