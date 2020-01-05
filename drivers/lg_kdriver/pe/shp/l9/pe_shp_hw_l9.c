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


/** @file pe_shp_hw_l9.c
 *
 *  driver for picture enhance sharpness functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
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
#include "pe_shp_hw.h"
#include "pe_shp_hw_l9a0.h"
#include "pe_shp_hw_l9b0.h"
#include "pe_shp_scl_hw_l9a0.h"
#include "pe_shp_scl_hw_l9b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_L9_FHD_H_MAX		1920
#define PE_SHP_HW_L9_FHD_V_MAX		1080
#define PE_SHP_HW_L9_SCL_IN_H_MIN	160
#define PE_SHP_HW_L9_SCL_IN_V_MIN	120
#define PE_SHP_HW_L9_IDX_Y_DFLT		15
#define PE_SHP_HW_L9_IDX_C_DFLT		39

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_HW_L9_ERROR	printk

#define PE_SHP_HW_L9_DBG_PRINT(fmt,args...)	\
	if(_g_shp_hw_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_SHP_HW_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_SHP_HW_L9_ERROR(fmt,##args);_action;}}
#define PE_SHP_HW_L9_DBG_PRINT_FMT_STATE(_pre,_cur)	\
	PE_SHP_HW_L9_DBG_PRINT("%s(%d),%s(%d) : %s.\n",\
	#_pre,(_pre),#_cur,(_cur),((_pre)!=(_cur))? "different":"same")
#define PE_SHP_HW_L9_DBG_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_SHP_HW_L9_DBG_PRINT(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
*	avoid double setting scaler filter
*/
typedef struct
{
	UINT8 h_y;	///< horizontal luma
	UINT8 v_y;	///< vertical luma
	UINT8 h_c;	///< horizontal chroma
	UINT8 v_c;	///< vertical chroma
}
PE_SHP_HW_L9_FLAG_T;

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
static PE_SHP_HW_L9_RES_FMT PE_SHP_HW_L9_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_SHP_HW_L9_VFC_FMT PE_SHP_HW_L9_ConvDispInfoToVfcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static int PE_SHP_HW_L9_GetScalerFilterValue(PE_TSK_L9_CFG_T *pCfg,PE_SHP_HW_L9_SETTINGS_T *pstParams);
static void PE_SHP_HW_L9_CheckValidScalerFilterValue(PE_SHP_HW_L9_SETTINGS_T *pstParams);
static PE_SHP_HW_L9_FLAG_T PE_SHP_HW_L9_GetDoubleSetFlag(LX_PE_WIN_ID win_id,LX_PE_SHP_SCLFILTER_T pre_idx,PE_SHP_HW_L9_SETTINGS_T *cur_param);
static int PE_SHP_HW_L9_SetSclCoeff(LX_PE_WIN_ID win_id, PE_SHP_HW_L9_FLAG_T flag, PE_SHP_HW_L9_SETTINGS_T *pstParams);
static int PE_SHP_HW_L9_SetSclSettingCnt(PE_SHP_HW_L9_FLAG_T flag, PE_SHP_HW_L9_SETTINGS_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT8 _g_shp_hw_l9_trace=0x0;	//default should be off.
static PE_SHP_HW_L9_SETTINGS_T _g_pe_shp_hw_l9_info;

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/
/**
 * set debug print on off
 *
 * @param   on_off [in] UINT8
 * @return  void
 * @see
 * @author
 */
void PE_SHP_HW_L9_SetDbgPrint(UINT32 on_off)
{
	_g_shp_hw_l9_trace = on_off? 1:0;
	return;
}

/**
 * init shp
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_HW_L9_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			PE_SHP_HW_L9_DBG_PRINT("init param.\n");
			memset0(_g_pe_shp_hw_l9_info);
			PE_SET_REG_TABLE(SHP_HW_L9,shp_l_init_param_l9b0,0);
			PE_SET_REG_TABLE(SHP_HW_L9,shp_r_init_param_l9b0,0);
			/* h,v min_max_filter enable */
	        PE_MSL_L9_RdFL(msc_min_max_ctrl_l_y);
	        PE_MSL_L9_RdFL(msc_min_max_ctrl_l_c);
	        PE_MSL_L9_Wr01(msc_min_max_ctrl_l_y, min_max_filter_en,	0x1);
	        PE_MSL_L9_Wr01(msc_min_max_ctrl_l_c, min_max_filter_en,	0x1);
	        PE_MSL_L9_Wr01(msc_min_max_ctrl_l_c, h_filter_en,		0x1);
	        PE_MSL_L9_WrFL(msc_min_max_ctrl_l_y);
	        PE_MSL_L9_WrFL(msc_min_max_ctrl_l_c);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_SHP_HW_L9_DBG_PRINT("init param.\n");
			memset0(_g_pe_shp_hw_l9_info);
			PE_SET_REG_TABLE(SHP_HW_L9,shp_l_init_param_l9a0,0);
			PE_SET_REG_TABLE(SHP_HW_L9,shp_r_init_param_l9a0,0);
		}
		else
		{
			PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

int PE_SHP_HW_L9_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_INF_L9_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_SHP_HW_L9_RES_FMT cur0_res_fmt,cur1_res_fmt;
	PE_SHP_HW_L9_VFC_FMT cur0_vfc_fmt,cur1_vfc_fmt;
	static PE_SHP_HW_L9_RES_FMT pre0_res_fmt = PE_SHP_L9_RES_NUM;
	static PE_SHP_HW_L9_RES_FMT pre1_res_fmt = PE_SHP_L9_RES_NUM;
	static PE_SHP_HW_L9_VFC_FMT pre0_vfc_fmt = PE_SHP_L9_VFC_NUM;
	static PE_SHP_HW_L9_VFC_FMT pre1_vfc_fmt = PE_SHP_L9_VFC_NUM;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_L9_GetCurInfSettings(&inf_set);
		PE_SHP_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		if(PE_KDRV_VER_L9BX)
		{
			/* L : resolution enhance */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_res_fmt = PE_SHP_HW_L9_ConvDispInfoToResFmt(cur0_inf);
				PE_SHP_HW_L9_DBG_PRINT_FMT_STATE(pre0_res_fmt,cur0_res_fmt);
				if(pre0_res_fmt!=cur0_res_fmt)
				{
					switch(cur0_res_fmt)
					{
						case PE_SHP_L9_RES_3D:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_3d_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_ATV_NTSC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_atv_sd_ntsc_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_ATV_PAL:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_atv_sd_pal_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_AV_NTSC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_av_sd_ntsc_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_AV_SCARTRGB:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_av_sd_scartrgb_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_AV_PAL:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_av_sd_pal_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_PC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_pc_all_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_DTV_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_dtv_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_DTV_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_dtv_hd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_COMP_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_comp_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_COMP_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_comp_hd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_HDMI_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_HDMI_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_hdmi_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre0_res_fmt=cur0_res_fmt;
				}
			}
			/* R : resolution enhance */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_res_fmt = PE_SHP_HW_L9_ConvDispInfoToResFmt(cur1_inf);
				PE_SHP_HW_L9_DBG_PRINT_FMT_STATE(pre1_res_fmt,cur1_res_fmt);
				if(pre1_res_fmt!=cur1_res_fmt)
				{
					switch(cur1_res_fmt)
					{
						case PE_SHP_L9_RES_3D:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_3d_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_ATV_NTSC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_atv_sd_ntsc_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_ATV_PAL:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_atv_sd_pal_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_AV_NTSC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_av_sd_ntsc_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_AV_SCARTRGB:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_av_sd_scartrgb_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_AV_PAL:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_av_sd_pal_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_PC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_pc_all_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_DTV_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_dtv_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_DTV_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_dtv_hd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_COMP_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_comp_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_COMP_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_comp_hd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_HDMI_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_RES_HDMI_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_hdmi_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre1_res_fmt=cur1_res_fmt;
				}
			}
			/* L : vertical filter chroma */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_vfc_fmt = PE_SHP_HW_L9_ConvDispInfoToVfcFmt(cur0_inf);
				PE_SHP_HW_L9_DBG_PRINT_FMT_STATE(pre0_vfc_fmt,cur0_vfc_fmt);
				if(pre0_vfc_fmt!=cur0_vfc_fmt)
				{
					switch(cur0_vfc_fmt)
					{
						case PE_SHP_L9_VFC_RF_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_vflt_c_default_rf_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_AV_SECAM:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_vflt_c_default_av_secam_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_AV_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_vflt_c_default_av_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_PC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_vflt_c_default_pc_all_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_HDMI_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_vflt_c_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_vflt_c_default_all_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre0_vfc_fmt=cur0_vfc_fmt;
				}
			}
			/* R : vertical filter chroma */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_vfc_fmt = PE_SHP_HW_L9_ConvDispInfoToVfcFmt(cur1_inf);
				PE_SHP_HW_L9_DBG_PRINT_FMT_STATE(pre1_vfc_fmt,cur1_vfc_fmt);
				if(pre1_vfc_fmt!=cur1_vfc_fmt)
				{
					switch(cur1_vfc_fmt)
					{
						case PE_SHP_L9_VFC_RF_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_vflt_c_default_rf_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_AV_SECAM:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_vflt_c_default_av_secam_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_AV_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_vflt_c_default_av_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_PC:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_vflt_c_default_pc_all_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_HDMI_SD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_vflt_c_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_SHP_L9_VFC_HD:
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_vflt_c_default_all_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre1_vfc_fmt=cur1_vfc_fmt;
				}
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			/* resolution default */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				switch(cur0_inf->src_type)
				{
					case LX_PE_SRC_ATV:
					case LX_PE_SRC_CVBS:
						PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_sd_param_l9a0,0);
						break;
					case LX_PE_SRC_DTV:
					case LX_PE_SRC_COMP:
					case LX_PE_SRC_PC:
					case LX_PE_SRC_HDMI:
					default:
						if(cur0_inf->fmt_type==LX_PE_FMT_SD)
						{
							PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_sd_param_l9a0,0);
						}
						else	//hd
						{
							if(cur0_inf->out_type==LX_PE_OUT_TB)
							{
								PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_hd_3d_tb_param_l9a0,0);
							}
							else
							{
								PE_SET_REG_TABLE(SHP_HW_L9,shp_l_default_hd_param_l9a0,0);
							}
						}
						break;
				}
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				switch(cur1_inf->src_type)
				{
					case LX_PE_SRC_ATV:
					case LX_PE_SRC_CVBS:
						PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_sd_param_l9a0,0);
						break;
					case LX_PE_SRC_DTV:
					case LX_PE_SRC_COMP:
					case LX_PE_SRC_PC:
					case LX_PE_SRC_HDMI:
					default:
						if(cur1_inf->fmt_type==LX_PE_FMT_SD)
						{
							PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_sd_param_l9a0,0);
						}
						else	//hd
						{
							if(cur1_inf->out_type==LX_PE_OUT_TB)
							{
								PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_hd_3d_tb_param_l9a0,0);
							}
							else
							{
								PE_SET_REG_TABLE(SHP_HW_L9,shp_r_default_hd_param_l9a0,0);
							}
						}
						break;
				}
			}
			/* chroma filter default */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				switch(cur0_inf->src_type)
				{
					case LX_PE_SRC_DTV:
						if(cur0_inf->fmt_type==LX_PE_FMT_SD)
						{
					        PE_MSL_L9_RdFL(msc_chroma_tear_ctrl_l);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, vsc_chroma_pre_filter_en,	0x1);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, manual_chroma_pre_filter_on,	0x1);
					        PE_MSL_L9_WrFL(msc_chroma_tear_ctrl_l);
						}
						else
						{
					        PE_MSL_L9_RdFL(msc_chroma_tear_ctrl_l);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, vsc_chroma_pre_filter_en,	0x0);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, manual_chroma_pre_filter_on,	0x0);
					        PE_MSL_L9_WrFL(msc_chroma_tear_ctrl_l);
						}
						break;
					case LX_PE_SRC_ATV:
					case LX_PE_SRC_CVBS:
						if(cur0_inf->fmt_type==LX_PE_FMT_SECAM)
						{
					        PE_MSL_L9_RdFL(msc_chroma_tear_ctrl_l);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, vsc_chroma_pre_filter_en,	0x1);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, manual_chroma_pre_filter_on,	0x1);
					        PE_MSL_L9_WrFL(msc_chroma_tear_ctrl_l);
						}
						else
						{
					        PE_MSL_L9_RdFL(msc_chroma_tear_ctrl_l);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, vsc_chroma_pre_filter_en,	0x0);
					        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, manual_chroma_pre_filter_on,	0x0);
					        PE_MSL_L9_WrFL(msc_chroma_tear_ctrl_l);
						}
						break;
					case LX_PE_SRC_COMP:
					case LX_PE_SRC_PC:
					case LX_PE_SRC_HDMI:
					default:
				        PE_MSL_L9_RdFL(msc_chroma_tear_ctrl_l);
				        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, vsc_chroma_pre_filter_en,	0x0);
				        PE_MSL_L9_Wr01(msc_chroma_tear_ctrl_l, manual_chroma_pre_filter_on,	0x0);
				        PE_MSL_L9_WrFL(msc_chroma_tear_ctrl_l);
						break;
				}
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				switch(cur1_inf->src_type)
				{
					case LX_PE_SRC_DTV:
						if(cur1_inf->fmt_type==LX_PE_FMT_SD)
						{
					        PE_MSR_L9_RdFL(msc_chroma_tear_ctrl_r);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, vsc_chroma_pre_filter_en,	0x1);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, manual_chroma_pre_filter_on,	0x1);
					        PE_MSR_L9_WrFL(msc_chroma_tear_ctrl_r);
						}
						else
						{
					        PE_MSR_L9_RdFL(msc_chroma_tear_ctrl_r);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, vsc_chroma_pre_filter_en,	0x0);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, manual_chroma_pre_filter_on,	0x0);
					        PE_MSR_L9_WrFL(msc_chroma_tear_ctrl_r);
						}
						break;
					case LX_PE_SRC_ATV:
					case LX_PE_SRC_CVBS:
						if(cur1_inf->fmt_type==LX_PE_FMT_SECAM)
						{
					        PE_MSR_L9_RdFL(msc_chroma_tear_ctrl_r);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, vsc_chroma_pre_filter_en,	0x1);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, manual_chroma_pre_filter_on,	0x1);
					        PE_MSR_L9_WrFL(msc_chroma_tear_ctrl_r);
						}
						else
						{
					        PE_MSR_L9_RdFL(msc_chroma_tear_ctrl_r);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, vsc_chroma_pre_filter_en,	0x0);
					        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, manual_chroma_pre_filter_on,	0x0);
					        PE_MSR_L9_WrFL(msc_chroma_tear_ctrl_r);
						}
						break;
					case LX_PE_SRC_COMP:
					case LX_PE_SRC_PC:
					case LX_PE_SRC_HDMI:
					default:
				        PE_MSR_L9_RdFL(msc_chroma_tear_ctrl_r);
				        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, vsc_chroma_pre_filter_en,	0x0);
				        PE_MSR_L9_Wr01(msc_chroma_tear_ctrl_r, manual_chroma_pre_filter_on,	0x0);
				        PE_MSR_L9_WrFL(msc_chroma_tear_ctrl_r);
						break;
				}
			}
		}
		else
		{
			PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
static PE_SHP_HW_L9_RES_FMT PE_SHP_HW_L9_ConvDispInfoToResFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_L9_RES_FMT res_fmt = PE_SHP_L9_RES_NUM;
	if((disp_inf->out_type>=LX_PE_OUT_TB) && (disp_inf->out_type<=LX_PE_OUT_DUAL_FULL))
	{
		res_fmt = PE_SHP_L9_RES_3D;
	}
	else	//2D
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
				{
					res_fmt = PE_SHP_L9_RES_ATV_NTSC;
				}
				else	//pal, secam
				{
					res_fmt = PE_SHP_L9_RES_ATV_PAL;
				}
				break;
			case LX_PE_SRC_CVBS:
				if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
				{
					res_fmt = PE_SHP_L9_RES_AV_NTSC;
				}
				else if(disp_inf->fmt_type==LX_PE_FMT_SCARTRGB)
				{
					res_fmt = PE_SHP_L9_RES_AV_SCARTRGB;
				}
				else	//pal, secam
				{
					res_fmt = PE_SHP_L9_RES_AV_PAL;
				}
				break;
			case LX_PE_SRC_PC:
				{
					res_fmt = PE_SHP_L9_RES_PC;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_L9_RES_DTV_SD;
				}
				else
				{
					res_fmt = PE_SHP_L9_RES_DTV_HD;
				}
				break;
			case LX_PE_SRC_COMP:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_L9_RES_COMP_SD;
				}
				else
				{
					res_fmt = PE_SHP_L9_RES_COMP_HD;
				}
				break;
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					res_fmt = PE_SHP_L9_RES_HDMI_SD;
				}
				else
				{
					res_fmt = PE_SHP_L9_RES_HDMI_HD;
				}
				break;
		}
	}
	return res_fmt;
}
static PE_SHP_HW_L9_VFC_FMT PE_SHP_HW_L9_ConvDispInfoToVfcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_SHP_HW_L9_VFC_FMT vfc_fmt = PE_SHP_L9_VFC_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			{
				vfc_fmt = PE_SHP_L9_VFC_RF_SD;
			}
			break;
		case LX_PE_SRC_CVBS:
			if(disp_inf->fmt_type==LX_PE_FMT_SECAM)
			{
				vfc_fmt = PE_SHP_L9_VFC_AV_SECAM;
			}
			else
			{
				vfc_fmt = PE_SHP_L9_VFC_AV_SD;
			}
			break;
		case LX_PE_SRC_PC:
			{
				vfc_fmt = PE_SHP_L9_VFC_PC;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				vfc_fmt = PE_SHP_L9_VFC_RF_SD;
			}
			else
			{
				vfc_fmt = PE_SHP_L9_VFC_HD;
			}
			break;
		case LX_PE_SRC_COMP:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				vfc_fmt = PE_SHP_L9_VFC_AV_SD;
			}
			else
			{
				vfc_fmt = PE_SHP_L9_VFC_HD;
			}
			break;
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				vfc_fmt = PE_SHP_L9_VFC_HDMI_SD;
			}
			else
			{
				vfc_fmt = PE_SHP_L9_VFC_HD;
			}
			break;
	}
	return vfc_fmt;
}
int PE_SHP_HW_L9_SetReEnableCtrl(PE_TSK_L9_CFG_T *pCfg)
{
	int ret = RET_OK;
	UINT32 cur_en[LX_PE_WIN_NUM];
	static UINT32 pre_en[LX_PE_WIN_NUM]={0xff,0xff};
	PE_INF_L9_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_L9_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	do {
		CHECK_KNULL(pCfg);
		/* if it's a resize, turn off resolution enable. */
		cur_en[LX_PE_WIN_0] = (ctrl0_info->scl_resize)? 0:1;
		cur_en[LX_PE_WIN_1] = (ctrl1_info->scl_resize)? 0:1;
		if(pre_en[LX_PE_WIN_0]!=cur_en[LX_PE_WIN_0])
		{
			PE_SHP_HW_L9_DBG_PRINT("set[0] : m_h,v:%d,%d, en:%d -> %d\n",ctrl0_info->m_win_h_size,\
				ctrl0_info->m_win_v_size,pre_en[LX_PE_WIN_0],cur_en[LX_PE_WIN_0]);
			if(PE_KDRV_VER_L9BX)
			{
				PE_P1L_L9B_QWr01(pe1_l_sp_ctrl_00, edge_enhance_enable,	cur_en[LX_PE_WIN_0]);
				PE_P1L_L9B_QWr01(pe1_l_mp_ctrl_00, edge_enhance_enable,	cur_en[LX_PE_WIN_0]);
			}
			else if(PE_KDRV_VER_L9AX)
			{
				PE_P1L_L9A_QWr01(pe1_l_lsr_dtl_ctrl_00, detail_enhancer_enable,	cur_en[LX_PE_WIN_0]);
				PE_P1L_L9A_QWr01(pe1_l_lsr_ctrl_06, edge_y_filter_en,			cur_en[LX_PE_WIN_0]);
				PE_P1L_L9A_QWr01(pe1_l_lsr_ctrl_06, edge_c_filter_en,			cur_en[LX_PE_WIN_0]);
				PE_P1L_L9A_QWr01(pe1_l_shp_edge_ctrl_00, edge_enhance_enable,	cur_en[LX_PE_WIN_0]);
			}
			else
			{
				PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");
			}
			pre_en[LX_PE_WIN_0]=cur_en[LX_PE_WIN_0];
		}
		if(pre_en[LX_PE_WIN_1]!=cur_en[LX_PE_WIN_1])
		{
			PE_SHP_HW_L9_DBG_PRINT("set[1] : m_h,v:%d,%d, en:%d -> %d\n",ctrl1_info->m_win_h_size,\
				ctrl1_info->m_win_v_size,pre_en[LX_PE_WIN_1],cur_en[LX_PE_WIN_1]);
			if(PE_KDRV_VER_L9BX)
			{
				PE_P1R_L9B_QWr01(pe1_r_sp_ctrl_00, edge_enhance_enable,	cur_en[LX_PE_WIN_1]);
				PE_P1R_L9B_QWr01(pe1_r_mp_ctrl_00, edge_enhance_enable,	cur_en[LX_PE_WIN_1]);
			}
			else if(PE_KDRV_VER_L9AX)
			{
				PE_P1R_L9A_QWr01(pe1_r_lsr_dtl_ctrl_00, detail_enhancer_enable,	cur_en[LX_PE_WIN_1]);
				PE_P1R_L9A_QWr01(pe1_r_lsr_ctrl_06, edge_y_filter_en,			cur_en[LX_PE_WIN_1]);
				PE_P1R_L9A_QWr01(pe1_r_lsr_ctrl_06, edge_c_filter_en,			cur_en[LX_PE_WIN_1]);
				PE_P1R_L9A_QWr01(pe1_r_shp_edge_ctrl_00, edge_enhance_enable,	cur_en[LX_PE_WIN_1]);
			}
			else
			{
				PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");
			}
			pre_en[LX_PE_WIN_1]=cur_en[LX_PE_WIN_1];
		}
	} while (0);
	return ret;
}
int PE_SHP_HW_L9_SetScalerFilterCoeff(LX_PE_SHP_SCLFILTER_T *pstParams)
{
	int ret = RET_OK;
	PE_SHP_HW_L9_SETTINGS_T *pInfo=&_g_pe_shp_hw_l9_info;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_SHP_HW_L9_DBG_PRINT("set[%d]:idx_y:%d,%d,idx_c:%d,%d\n",pstParams->win_id,\
			pstParams->h_luma_id,pstParams->v_luma_id,pstParams->h_chrm_id,pstParams->v_chrm_id);
		if(PE_KDRV_VER_L9)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(&pInfo->scl_idx[LX_PE_WIN_0],pstParams,sizeof(LX_PE_SHP_SCLFILTER_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(&pInfo->scl_idx[LX_PE_WIN_1],pstParams,sizeof(LX_PE_SHP_SCLFILTER_T));
			}
		}
		else
		{
			PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
int PE_SHP_HW_L9_GetCurShpSettings(PE_SHP_HW_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_SHP_HW_L9_SETTINGS_T *pInfo=&_g_pe_shp_hw_l9_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9)
		{
			memcpy(pstParams,pInfo,sizeof(PE_SHP_HW_L9_SETTINGS_T));
			if(_g_shp_hw_l9_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_SHP_HW_L9_DBG_PRINT("get[0]:idx_y:%d,%d,idx_c:%d,%d\n",\
						pstParams->scl_idx[LX_PE_WIN_0].h_luma_id,pstParams->scl_idx[LX_PE_WIN_0].v_luma_id,\
						pstParams->scl_idx[LX_PE_WIN_0].h_chrm_id,pstParams->scl_idx[LX_PE_WIN_0].v_chrm_id);
					PE_SHP_HW_L9_DBG_PRINT("get[1]:idx_y:%d,%d,idx_c:%d,%d\n",\
						pstParams->scl_idx[LX_PE_WIN_1].h_luma_id,pstParams->scl_idx[LX_PE_WIN_1].v_luma_id,\
						pstParams->scl_idx[LX_PE_WIN_1].h_chrm_id,pstParams->scl_idx[LX_PE_WIN_1].v_chrm_id);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}
int PE_SHP_HW_L9_SetScalerFilterCtrl(PE_TSK_L9_CFG_T *pCfg)
{
	int ret = RET_OK;
	static LX_PE_SHP_SCLFILTER_T pre_idx[LX_PE_WIN_NUM]={{0,0xff,0xff,0xff,0xff},{1,0xff,0xff,0xff,0xff}};
	PE_SHP_HW_L9_SETTINGS_T cur_param;
	PE_SHP_HW_L9_SETTINGS_T *pInfo=&_g_pe_shp_hw_l9_info;
	PE_SHP_HW_L9_FLAG_T set_flag;
	UINT32 type_sel_luma,type_sel_chroma,scaler_config,adap_filter_en;
	do {
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_L9)
		{
			memset0(cur_param);
			/* get fir,tap,index */
			ret = PE_SHP_HW_L9_GetScalerFilterValue(pCfg,&cur_param);
			PE_SHP_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_L9_GetScalerFilterValue() error.\n",__F__,__L__);
			/* check index is valid & re-setting index */
			PE_SHP_HW_L9_CheckValidScalerFilterValue(&cur_param);
			/* L : compare & filtering */
			if(pre_idx[LX_PE_WIN_0].h_luma_id!=cur_param.scl_idx[LX_PE_WIN_0].h_luma_id || \
				pre_idx[LX_PE_WIN_0].v_luma_id!=cur_param.scl_idx[LX_PE_WIN_0].v_luma_id || \
				pre_idx[LX_PE_WIN_0].h_chrm_id!=cur_param.scl_idx[LX_PE_WIN_0].h_chrm_id || \
				pre_idx[LX_PE_WIN_0].v_chrm_id!=cur_param.scl_idx[LX_PE_WIN_0].v_chrm_id || \
				pInfo->h_y_tap[LX_PE_WIN_0]!=cur_param.h_y_tap[LX_PE_WIN_0] || \
				pInfo->v_y_tap[LX_PE_WIN_0]!=cur_param.v_y_tap[LX_PE_WIN_0] || \
				pInfo->h_c_tap[LX_PE_WIN_0]!=cur_param.h_c_tap[LX_PE_WIN_0] || \
				pInfo->v_c_tap[LX_PE_WIN_0]!=cur_param.v_c_tap[LX_PE_WIN_0] || \
				pInfo->y_fir[LX_PE_WIN_0]!=cur_param.y_fir[LX_PE_WIN_0] || \
				pInfo->c_fir[LX_PE_WIN_0]!=cur_param.c_fir[LX_PE_WIN_0])
			{
				PE_SHP_HW_L9_DBG_PRINT("set[0]:[idx_hy,vy,hc,vc][pre:%d,%d,%d,%d][cur:%d,%d,%d,%d]\n",\
					pre_idx[LX_PE_WIN_0].h_luma_id,pre_idx[LX_PE_WIN_0].v_luma_id,\
					pre_idx[LX_PE_WIN_0].h_chrm_id,pre_idx[LX_PE_WIN_0].v_chrm_id,\
					cur_param.scl_idx[LX_PE_WIN_0].h_luma_id,cur_param.scl_idx[LX_PE_WIN_0].v_luma_id,\
					cur_param.scl_idx[LX_PE_WIN_0].h_chrm_id,cur_param.scl_idx[LX_PE_WIN_0].v_chrm_id);
				PE_SHP_HW_L9_DBG_PRINT("set[0]:[tap_hy,vy,hc,vc][pre:%d,%d,%d,%d][cur:%d,%d,%d,%d]\n",\
					pInfo->h_y_tap[LX_PE_WIN_0],pInfo->v_y_tap[LX_PE_WIN_0],\
					pInfo->h_c_tap[LX_PE_WIN_0],pInfo->v_c_tap[LX_PE_WIN_0],\
					cur_param.h_y_tap[LX_PE_WIN_0],cur_param.v_y_tap[LX_PE_WIN_0],\
					cur_param.h_c_tap[LX_PE_WIN_0],cur_param.v_c_tap[LX_PE_WIN_0]);
				PE_SHP_HW_L9_DBG_PRINT("set[0]:[fir_y,c][pre:%d,%d][cur:%d,%d]\n",\
					pInfo->y_fir[LX_PE_WIN_0],pInfo->c_fir[LX_PE_WIN_0],\
					cur_param.y_fir[LX_PE_WIN_0],cur_param.c_fir[LX_PE_WIN_0]);
				/* set config */
				if(pInfo->h_y_tap[LX_PE_WIN_0]!=cur_param.h_y_tap[LX_PE_WIN_0] || \
					pInfo->y_fir[LX_PE_WIN_0]!=cur_param.y_fir[LX_PE_WIN_0] || \
					pInfo->c_fir[LX_PE_WIN_0]!=cur_param.c_fir[LX_PE_WIN_0])
				{
					scaler_config	= (cur_param.h_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_12TAP)? 0x0:0x1;
					adap_filter_en	= (cur_param.h_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_12TAP)? 0x1:0x0;
					type_sel_luma	= (cur_param.y_fir[LX_PE_WIN_0]==PE_SHP_HW_L9_FIR_BILINEAR)? 0x1:0x0;
					type_sel_chroma	= (cur_param.c_fir[LX_PE_WIN_0]==PE_SHP_HW_L9_FIR_BILINEAR)? 0x1:0x0;
			        PE_MSL_L9_RdFL(msc_ctrl_l);
			        PE_MSL_L9_Wr01(msc_ctrl_l, filter_type_sel_luma       ,type_sel_luma);
			        PE_MSL_L9_Wr01(msc_ctrl_l, filter_type_sel_chroma     ,type_sel_chroma);
			        PE_MSL_L9_Wr01(msc_ctrl_l, v_scaler_config            ,scaler_config);
			        PE_MSL_L9_Wr01(msc_ctrl_l, adaptive_fir_filter_en     ,adap_filter_en);
			        PE_MSL_L9_WrFL(msc_ctrl_l);
				}
				/* check double setting flag*/
				set_flag = PE_SHP_HW_L9_GetDoubleSetFlag(LX_PE_WIN_0,pre_idx[LX_PE_WIN_0],&cur_param);
				/* set scl coeff */
				ret = PE_SHP_HW_L9_SetSclCoeff(LX_PE_WIN_0,set_flag,&cur_param);
				PE_SHP_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_L9_SetSclCoeff() error.\n",__F__,__L__);
				/* set scl cnt */
				ret = PE_SHP_HW_L9_SetSclSettingCnt(set_flag,&cur_param);
				PE_SHP_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_SetSclSettingCnt() error.\n",__F__,__L__);
				pre_idx[LX_PE_WIN_0].h_luma_id=cur_param.scl_idx[LX_PE_WIN_0].h_luma_id;
				pre_idx[LX_PE_WIN_0].v_luma_id=cur_param.scl_idx[LX_PE_WIN_0].v_luma_id;
				pre_idx[LX_PE_WIN_0].h_chrm_id=cur_param.scl_idx[LX_PE_WIN_0].h_chrm_id;
				pre_idx[LX_PE_WIN_0].v_chrm_id=cur_param.scl_idx[LX_PE_WIN_0].v_chrm_id;
				pInfo->h_y_tap[LX_PE_WIN_0]=cur_param.h_y_tap[LX_PE_WIN_0];
				pInfo->v_y_tap[LX_PE_WIN_0]=cur_param.v_y_tap[LX_PE_WIN_0];
				pInfo->h_c_tap[LX_PE_WIN_0]=cur_param.h_c_tap[LX_PE_WIN_0];
				pInfo->v_c_tap[LX_PE_WIN_0]=cur_param.v_c_tap[LX_PE_WIN_0];
				pInfo->y_fir[LX_PE_WIN_0]=cur_param.y_fir[LX_PE_WIN_0];
				pInfo->c_fir[LX_PE_WIN_0]=cur_param.c_fir[LX_PE_WIN_0];
			}
			/* R : compare & filtering */
			if(pre_idx[LX_PE_WIN_1].h_luma_id!=cur_param.scl_idx[LX_PE_WIN_1].h_luma_id || \
				pre_idx[LX_PE_WIN_1].v_luma_id!=cur_param.scl_idx[LX_PE_WIN_1].v_luma_id || \
				pre_idx[LX_PE_WIN_1].h_chrm_id!=cur_param.scl_idx[LX_PE_WIN_1].h_chrm_id || \
				pre_idx[LX_PE_WIN_1].v_chrm_id!=cur_param.scl_idx[LX_PE_WIN_1].v_chrm_id || \
				pInfo->h_y_tap[LX_PE_WIN_1]!=cur_param.h_y_tap[LX_PE_WIN_1] || \
				pInfo->v_y_tap[LX_PE_WIN_1]!=cur_param.v_y_tap[LX_PE_WIN_1] || \
				pInfo->h_c_tap[LX_PE_WIN_1]!=cur_param.h_c_tap[LX_PE_WIN_1] || \
				pInfo->v_c_tap[LX_PE_WIN_1]!=cur_param.v_c_tap[LX_PE_WIN_1] || \
				pInfo->y_fir[LX_PE_WIN_1]!=cur_param.y_fir[LX_PE_WIN_1] || \
				pInfo->c_fir[LX_PE_WIN_1]!=cur_param.c_fir[LX_PE_WIN_1])
			{
				PE_SHP_HW_L9_DBG_PRINT("set[1]:[idx_hy,vy,hc,vc][pre:%d,%d,%d,%d][cur:%d,%d,%d,%d]\n",\
					pre_idx[LX_PE_WIN_1].h_luma_id,pre_idx[LX_PE_WIN_1].v_luma_id,\
					pre_idx[LX_PE_WIN_1].h_chrm_id,pre_idx[LX_PE_WIN_1].v_chrm_id,\
					cur_param.scl_idx[LX_PE_WIN_1].h_luma_id,cur_param.scl_idx[LX_PE_WIN_1].v_luma_id,\
					cur_param.scl_idx[LX_PE_WIN_1].h_chrm_id,cur_param.scl_idx[LX_PE_WIN_1].v_chrm_id);
				PE_SHP_HW_L9_DBG_PRINT("set[1]:[tap_hy,vy,hc,vc][pre:%d,%d,%d,%d][cur:%d,%d,%d,%d]\n",\
					pInfo->h_y_tap[LX_PE_WIN_1],pInfo->v_y_tap[LX_PE_WIN_1],\
					pInfo->h_c_tap[LX_PE_WIN_1],pInfo->v_c_tap[LX_PE_WIN_1],\
					cur_param.h_y_tap[LX_PE_WIN_1],cur_param.v_y_tap[LX_PE_WIN_1],\
					cur_param.h_c_tap[LX_PE_WIN_1],cur_param.v_c_tap[LX_PE_WIN_1]);
				PE_SHP_HW_L9_DBG_PRINT("set[1]:[fir_y,c][pre:%d,%d][cur:%d,%d]\n",\
					pInfo->y_fir[LX_PE_WIN_1],pInfo->c_fir[LX_PE_WIN_1],\
					cur_param.y_fir[LX_PE_WIN_1],cur_param.c_fir[LX_PE_WIN_1]);
				/* set config */
				if(pInfo->h_y_tap[LX_PE_WIN_1]!=cur_param.h_y_tap[LX_PE_WIN_1] || \
					pInfo->y_fir[LX_PE_WIN_1]!=cur_param.y_fir[LX_PE_WIN_1] || \
					pInfo->c_fir[LX_PE_WIN_1]!=cur_param.c_fir[LX_PE_WIN_1])
				{
					scaler_config	= (cur_param.h_y_tap[LX_PE_WIN_1]==PE_SHP_HW_L9_SCL_12TAP)? 0x0:0x1;
					adap_filter_en	= (cur_param.h_y_tap[LX_PE_WIN_1]==PE_SHP_HW_L9_SCL_12TAP)? 0x1:0x0;
					type_sel_luma	= (cur_param.y_fir[LX_PE_WIN_1]==PE_SHP_HW_L9_FIR_BILINEAR)? 0x1:0x0;
					type_sel_chroma	= (cur_param.c_fir[LX_PE_WIN_1]==PE_SHP_HW_L9_FIR_BILINEAR)? 0x1:0x0;
			        PE_MSR_L9_RdFL(msc_ctrl_r);
			        PE_MSR_L9_Wr01(msc_ctrl_r, filter_type_sel_luma      ,type_sel_luma);
			        PE_MSR_L9_Wr01(msc_ctrl_r, filter_type_sel_chroma    ,type_sel_chroma);
					if(PE_KDRV_VER_L9AX)
					{
			        	PE_MSR_L9A_Wr01(msc_ctrl_r, v_scaler_config      ,scaler_config);
					}
			        PE_MSR_L9_Wr01(msc_ctrl_r, adaptive_fir_filter_en    ,adap_filter_en);
			        PE_MSR_L9_WrFL(msc_ctrl_r);
				}
				/* check double setting flag*/
				set_flag = PE_SHP_HW_L9_GetDoubleSetFlag(LX_PE_WIN_1,pre_idx[LX_PE_WIN_1],&cur_param);
				/* set scl coeff */
				ret = PE_SHP_HW_L9_SetSclCoeff(LX_PE_WIN_1,set_flag,&cur_param);
				PE_SHP_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_L9_SetSclCoeff() error.\n",__F__,__L__);
				pre_idx[LX_PE_WIN_1].h_luma_id=cur_param.scl_idx[LX_PE_WIN_1].h_luma_id;
				pre_idx[LX_PE_WIN_1].v_luma_id=cur_param.scl_idx[LX_PE_WIN_1].v_luma_id;
				pre_idx[LX_PE_WIN_1].h_chrm_id=cur_param.scl_idx[LX_PE_WIN_1].h_chrm_id;
				pre_idx[LX_PE_WIN_1].v_chrm_id=cur_param.scl_idx[LX_PE_WIN_1].v_chrm_id;
				pInfo->h_y_tap[LX_PE_WIN_1]=cur_param.h_y_tap[LX_PE_WIN_1];
				pInfo->v_y_tap[LX_PE_WIN_1]=cur_param.v_y_tap[LX_PE_WIN_1];
				pInfo->h_c_tap[LX_PE_WIN_1]=cur_param.h_c_tap[LX_PE_WIN_1];
				pInfo->v_c_tap[LX_PE_WIN_1]=cur_param.v_c_tap[LX_PE_WIN_1];
				pInfo->y_fir[LX_PE_WIN_1]=cur_param.y_fir[LX_PE_WIN_1];
				pInfo->c_fir[LX_PE_WIN_1]=cur_param.c_fir[LX_PE_WIN_1];
			}
		}
		else
		{
			PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
static int PE_SHP_HW_L9_GetScalerFilterValue(PE_TSK_L9_CFG_T *pCfg,PE_SHP_HW_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 type6Tap[LX_PE_WIN_NUM],h_ratio[LX_PE_WIN_NUM],v_ratio[LX_PE_WIN_NUM];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_L9_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_L9_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_SHP_HW_L9_SETTINGS_T *pIdx_Info=&_g_pe_shp_hw_l9_info;
	do {
		CHECK_KNULL(pCfg);
		/* L,R : check fir type */
		if((disp0_info->src_type==LX_PE_SRC_HDMI || disp0_info->src_type==LX_PE_SRC_COMP) && \
			ctrl0_info->scl_src_h==PE_SHP_HW_L9_FHD_H_MAX && \
			ctrl0_info->scl_src_v==PE_SHP_HW_L9_FHD_V_MAX && \
			ctrl0_info->i_win_h_size==PE_SHP_HW_L9_FHD_H_MAX && \
			ctrl0_info->i_win_v_size==PE_SHP_HW_L9_FHD_V_MAX && \
			ctrl0_info->o_win_h_size==PE_SHP_HW_L9_FHD_H_MAX && \
			ctrl0_info->o_win_v_size==PE_SHP_HW_L9_FHD_V_MAX && \
			disp0_info->out_type==LX_PE_OUT_2D)
		{
			pstParams->y_fir[LX_PE_WIN_0] = PE_SHP_HW_L9_FIR_BILINEAR;
			pstParams->c_fir[LX_PE_WIN_0] = PE_SHP_HW_L9_FIR_BILINEAR;
		}
		else
		{
			pstParams->y_fir[LX_PE_WIN_0] = PE_SHP_HW_L9_FIR_POLYPHASE;
			pstParams->c_fir[LX_PE_WIN_0] = (ctrl0_info->is_yuv444)? PE_SHP_HW_L9_FIR_BILINEAR:PE_SHP_HW_L9_FIR_POLYPHASE;
		}
		pstParams->y_fir[LX_PE_WIN_1] = PE_SHP_HW_L9_FIR_POLYPHASE;
		pstParams->c_fir[LX_PE_WIN_1] = PE_SHP_HW_L9_FIR_POLYPHASE;
		/* 6tap case:src_hsize:0(abnormal),over1024(2_line_memory),resize,yuv444,3d,adaptive_stream */
		type6Tap[LX_PE_WIN_0] = (!ctrl0_info->scl_src_h || ctrl0_info->scl_hd || ctrl0_info->scl_resize || \
								ctrl0_info->is_yuv444 || disp0_info->mode.is_adpt_st || \
								disp0_info->out_type==LX_PE_OUT_TB || disp0_info->out_type==LX_PE_OUT_SS || \
								disp0_info->out_type==LX_PE_OUT_FS || disp0_info->out_type==LX_PE_OUT_DUAL_TB || \
								disp0_info->out_type==LX_PE_OUT_DUAL_SS || disp0_info->out_type==LX_PE_OUT_DUAL_FULL )? \
								1:0;
		type6Tap[LX_PE_WIN_1] = 1;
		/* L : check y tap */
		if(type6Tap[LX_PE_WIN_0])
		{
			/* check in vs. out ratio */
			if(ctrl0_info->o_win_h_size >= PE_SHP_HW_L9_SCL_IN_H_MIN && \
				ctrl0_info->o_win_v_size >= PE_SHP_HW_L9_SCL_IN_V_MIN && \
				ctrl0_info->i_win_h_size && ctrl0_info->i_win_v_size)
			{
				h_ratio[LX_PE_WIN_0] = (ctrl0_info->o_win_h_size<<10)/ctrl0_info->i_win_h_size;
				v_ratio[LX_PE_WIN_0] = (ctrl0_info->o_win_v_size<<10)/ctrl0_info->i_win_v_size;
			}
			else
			{
				h_ratio[LX_PE_WIN_0] = 1024;	//1.0
				v_ratio[LX_PE_WIN_0] = 1024;	//1.0
			}
			/* tap */
			if( h_ratio[LX_PE_WIN_0] >= 875 )		{	pstParams->h_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;}
			else if ( h_ratio[LX_PE_WIN_0] >= 625 )	{	pstParams->h_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_DOWN75;}
			else if ( h_ratio[LX_PE_WIN_0] >= 375 )	{	pstParams->h_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_DOWN50;}
			else									{	pstParams->h_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_DOWN25;}
			if( v_ratio[LX_PE_WIN_0] >= 875 )		{	pstParams->v_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;}
			else if ( v_ratio[LX_PE_WIN_0] >= 625 )	{	pstParams->v_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_DOWN75;}
			else if ( v_ratio[LX_PE_WIN_0] >= 375 )	{	pstParams->v_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_DOWN50;}
			else									{	pstParams->v_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_DOWN25;}
			/* check vertical half mode */
			if((pstParams->v_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_06TAP_NORMAL) && \
				(ctrl0_info->o_win_v_size<=(ctrl0_info->i_win_v_size>>1)))
			{
				pstParams->v_y_tap[LX_PE_WIN_0]=PE_SHP_HW_L9_SCL_06TAP_HALF;
			}
		}
		else
		{
			pstParams->h_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_12TAP;
			pstParams->v_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_12TAP;
		}
		/* R : check y tap */
		if(type6Tap[LX_PE_WIN_1])
		{
			/* check in vs. out ratio */
			if(ctrl1_info->o_win_h_size >= PE_SHP_HW_L9_SCL_IN_H_MIN && \
				ctrl1_info->o_win_v_size >= PE_SHP_HW_L9_SCL_IN_V_MIN && \
				ctrl1_info->i_win_h_size && ctrl1_info->i_win_v_size)
			{
				h_ratio[LX_PE_WIN_1] = (ctrl1_info->o_win_h_size<<10)/ctrl1_info->i_win_h_size;
				v_ratio[LX_PE_WIN_1] = (ctrl1_info->o_win_v_size<<10)/ctrl1_info->i_win_v_size;
			}
			else
			{
				h_ratio[LX_PE_WIN_1] = 1024;	//1.0
				v_ratio[LX_PE_WIN_1] = 1024;	//1.0
			}
			/* tap */
			if( h_ratio[LX_PE_WIN_1] >= 875 )		{	pstParams->h_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;}
			else if ( h_ratio[LX_PE_WIN_1] >= 625 )	{	pstParams->h_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_DOWN75;}
			else if ( h_ratio[LX_PE_WIN_1] >= 375 )	{	pstParams->h_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_DOWN50;}
			else									{	pstParams->h_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_DOWN25;}
			if( v_ratio[LX_PE_WIN_1] >= 875 )		{	pstParams->v_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;}
			else if ( v_ratio[LX_PE_WIN_1] >= 625 )	{	pstParams->v_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_DOWN75;}
			else if ( v_ratio[LX_PE_WIN_1] >= 375 )	{	pstParams->v_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_DOWN50;}
			else									{	pstParams->v_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_DOWN25;}
			/* check vertical half mode */
			if((pstParams->v_y_tap[LX_PE_WIN_1]==PE_SHP_HW_L9_SCL_06TAP_NORMAL) && \
				(ctrl1_info->o_win_v_size<=(ctrl1_info->i_win_v_size>>1)))
			{
				pstParams->v_y_tap[LX_PE_WIN_1]=PE_SHP_HW_L9_SCL_06TAP_HALF;
			}
		}
		else
		{
			pstParams->h_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;	//6tap only for R
			pstParams->v_y_tap[LX_PE_WIN_1] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;	//6tap only for R
		}
		/* L : double-check y,c tap & idx */
		if(disp0_info->src_type==LX_PE_SRC_DTV && disp0_info->dtv_type==LX_PE_DTV_NORMAL)
		{
			/* 20110921, sj.youm, for dtv hd 31-3 LG logo jagging */
			pstParams->h_c_tap[LX_PE_WIN_0] = (ctrl0_info->scl_hd && \
				pstParams->h_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_06TAP_NORMAL)? \
				PE_SHP_HW_L9_SCL_06TAP_DOWN50:pstParams->h_y_tap[LX_PE_WIN_0];
			pstParams->v_c_tap[LX_PE_WIN_0] = (ctrl0_info->scl_hd && \
				pstParams->v_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_06TAP_NORMAL)? \
				PE_SHP_HW_L9_SCL_06TAP_DOWN50:pstParams->v_y_tap[LX_PE_WIN_0];
			pstParams->scl_idx[LX_PE_WIN_0].h_luma_id = pIdx_Info->scl_idx[LX_PE_WIN_0].h_luma_id;
			pstParams->scl_idx[LX_PE_WIN_0].v_luma_id = pIdx_Info->scl_idx[LX_PE_WIN_0].v_luma_id;
			pstParams->scl_idx[LX_PE_WIN_0].h_chrm_id = pIdx_Info->scl_idx[LX_PE_WIN_0].h_chrm_id;
			pstParams->scl_idx[LX_PE_WIN_0].v_chrm_id = pIdx_Info->scl_idx[LX_PE_WIN_0].v_chrm_id;
		}
		else if(disp0_info->src_type==LX_PE_SRC_DTV && disp0_info->mode.is_adpt_st)
		{
			/* 20111203, sj.youm, fix 6tap for adaptive stream */
			if(pstParams->h_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_12TAP)
			{
				pstParams->h_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;
				pstParams->h_c_tap[LX_PE_WIN_0] = pstParams->h_y_tap[LX_PE_WIN_0];
			}
			if(pstParams->v_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_12TAP)
			{
				pstParams->v_y_tap[LX_PE_WIN_0] = PE_SHP_HW_L9_SCL_06TAP_NORMAL;
				pstParams->v_c_tap[LX_PE_WIN_0] = pstParams->v_y_tap[LX_PE_WIN_0];
			}
			pstParams->scl_idx[LX_PE_WIN_0].h_luma_id = PE_SHP_HW_L9_IDX_Y_DFLT;
			pstParams->scl_idx[LX_PE_WIN_0].v_luma_id = PE_SHP_HW_L9_IDX_Y_DFLT;
			pstParams->scl_idx[LX_PE_WIN_0].h_chrm_id = PE_SHP_HW_L9_IDX_C_DFLT;
			pstParams->scl_idx[LX_PE_WIN_0].v_chrm_id = PE_SHP_HW_L9_IDX_C_DFLT;
		}
		else
		{
			pstParams->h_c_tap[LX_PE_WIN_0] = pstParams->h_y_tap[LX_PE_WIN_0];
			pstParams->v_c_tap[LX_PE_WIN_0] = pstParams->v_y_tap[LX_PE_WIN_0];
			pstParams->scl_idx[LX_PE_WIN_0].h_luma_id = pIdx_Info->scl_idx[LX_PE_WIN_0].h_luma_id;
			pstParams->scl_idx[LX_PE_WIN_0].v_luma_id = pIdx_Info->scl_idx[LX_PE_WIN_0].v_luma_id;
			pstParams->scl_idx[LX_PE_WIN_0].h_chrm_id = pIdx_Info->scl_idx[LX_PE_WIN_0].h_chrm_id;
			pstParams->scl_idx[LX_PE_WIN_0].v_chrm_id = pIdx_Info->scl_idx[LX_PE_WIN_0].v_chrm_id;
		}
		/* R : double-check y,c tap & idx */
		if(disp0_info->mode.is_venc)
		{
			pstParams->h_c_tap[LX_PE_WIN_1] = pstParams->h_y_tap[LX_PE_WIN_1];
			pstParams->v_c_tap[LX_PE_WIN_1] = pstParams->v_y_tap[LX_PE_WIN_1];
			pstParams->scl_idx[LX_PE_WIN_1].h_luma_id = PE_SHP_HW_L9_IDX_Y_DFLT;
			pstParams->scl_idx[LX_PE_WIN_1].v_luma_id = PE_SHP_HW_L9_IDX_Y_DFLT;
			pstParams->scl_idx[LX_PE_WIN_1].h_chrm_id = PE_SHP_HW_L9_IDX_C_DFLT;
			pstParams->scl_idx[LX_PE_WIN_1].v_chrm_id = PE_SHP_HW_L9_IDX_C_DFLT;
		}
		else
		{
			pstParams->h_c_tap[LX_PE_WIN_1] = pstParams->h_y_tap[LX_PE_WIN_1];
			pstParams->v_c_tap[LX_PE_WIN_1] = pstParams->v_y_tap[LX_PE_WIN_1];
			pstParams->scl_idx[LX_PE_WIN_1].h_luma_id = pIdx_Info->scl_idx[LX_PE_WIN_1].h_luma_id;
			pstParams->scl_idx[LX_PE_WIN_1].v_luma_id = pIdx_Info->scl_idx[LX_PE_WIN_1].v_luma_id;
			pstParams->scl_idx[LX_PE_WIN_1].h_chrm_id = pIdx_Info->scl_idx[LX_PE_WIN_1].h_chrm_id;
			pstParams->scl_idx[LX_PE_WIN_1].v_chrm_id = pIdx_Info->scl_idx[LX_PE_WIN_1].v_chrm_id;
		}
	}while(0);
	return ret;
}
static void PE_SHP_HW_L9_CheckValidScalerFilterValue(PE_SHP_HW_L9_SETTINGS_T *pstParams)
{
	LX_PE_SHP_SCLFILTER_T *idx0 = &pstParams->scl_idx[LX_PE_WIN_0];
	LX_PE_SHP_SCLFILTER_T *idx1 = &pstParams->scl_idx[LX_PE_WIN_1];
	PE_SHP_HW_L9_SCL hy_tap0 = pstParams->h_y_tap[LX_PE_WIN_0];
	PE_SHP_HW_L9_SCL hc_tap0 = pstParams->h_c_tap[LX_PE_WIN_0];
	PE_SHP_HW_L9_SCL vy_tap0 = pstParams->v_y_tap[LX_PE_WIN_0];
	PE_SHP_HW_L9_SCL vc_tap0 = pstParams->v_c_tap[LX_PE_WIN_0];
	PE_SHP_HW_L9_SCL hy_tap1 = pstParams->h_y_tap[LX_PE_WIN_1];
	PE_SHP_HW_L9_SCL hc_tap1 = pstParams->h_c_tap[LX_PE_WIN_1];
	PE_SHP_HW_L9_SCL vy_tap1 = pstParams->v_y_tap[LX_PE_WIN_1];
	PE_SHP_HW_L9_SCL vc_tap1 = pstParams->v_c_tap[LX_PE_WIN_1];
	do{
		if(PE_KDRV_VER_L9BX)
		{
			/* L : h luma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE((hy_tap0==PE_SHP_HW_L9_SCL_12TAP&&\
				idx0->h_luma_id>=PE_SHP_SCL_COEFF_LUMA_H_12_L9B0_NUM),\
				idx0->h_luma_id=PE_SHP_HW_L9_IDX_Y_DFLT,\
				"[%s,%d] hy_tap0(%d), h_luma_id(%d) is out of range.\n",\
				__F__,__L__,hy_tap0,idx0->h_luma_id);
			PE_SHP_HW_L9_DBG_CHECK_CODE((hy_tap0==PE_SHP_HW_L9_SCL_06TAP_NORMAL&&\
				idx0->h_luma_id>=PE_SHP_SCL_COEFF_LUMA_H_06_L9B0_NUM),\
				idx0->h_luma_id=PE_SHP_HW_L9_IDX_Y_DFLT,\
				"[%s,%d] hy_tap0(%d), h_luma_id(%d) is out of range.\n",\
				__F__,__L__,hy_tap0,idx0->h_luma_id);
			/* L : v luma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE((vy_tap0==PE_SHP_HW_L9_SCL_12TAP&&\
				idx0->v_luma_id>=PE_SHP_SCL_COEFF_LUMA_V_12_L9B0_NUM),\
				idx0->v_luma_id=PE_SHP_HW_L9_IDX_Y_DFLT,\
				"[%s,%d] vy_tap0(%d), v_luma_id(%d) is out of range.\n",\
				__F__,__L__,vy_tap0,idx0->v_luma_id);
			PE_SHP_HW_L9_DBG_CHECK_CODE(((vy_tap0==PE_SHP_HW_L9_SCL_06TAP_NORMAL||\
				vy_tap0==PE_SHP_HW_L9_SCL_06TAP_HALF)&&\
				idx0->v_luma_id>=PE_SHP_SCL_COEFF_LUMA_V_06_L9B0_NUM),\
				idx0->v_luma_id=PE_SHP_HW_L9_IDX_Y_DFLT,\
				"[%s,%d] vy_tap0(%d), v_luma_id(%d) is out of range.\n",\
				__F__,__L__,vy_tap0,idx0->v_luma_id);
			/* L : h chroma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE(((hc_tap0==PE_SHP_HW_L9_SCL_12TAP||\
				hc_tap0==PE_SHP_HW_L9_SCL_06TAP_NORMAL)&&\
				idx0->h_chrm_id>=PE_SHP_SCL_COEFF_CHROMA_H_L9B0_NUM),\
				idx0->h_chrm_id=PE_SHP_HW_L9_IDX_C_DFLT,\
				"[%s,%d] hc_tap0(%d), h_chrm_id(%d) is out of range.\n",\
				__F__,__L__,hc_tap0,idx0->h_chrm_id);
			/* L : v chroma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE(((vc_tap0==PE_SHP_HW_L9_SCL_12TAP||\
				vc_tap0==PE_SHP_HW_L9_SCL_06TAP_NORMAL||\
				vc_tap0==PE_SHP_HW_L9_SCL_06TAP_HALF)&&\
				idx0->v_chrm_id>=PE_SHP_SCL_COEFF_CHROMA_V_L9B0_NUM),\
				idx0->v_chrm_id=PE_SHP_HW_L9_IDX_C_DFLT,\
				"[%s,%d] vc_tap0(%d), v_chrm_id(%d) is out of range.\n",\
				__F__,__L__,vc_tap0,idx0->v_chrm_id);
			/* R : h luma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE((hy_tap1==PE_SHP_HW_L9_SCL_12TAP),\
				hy_tap1=PE_SHP_HW_L9_SCL_06TAP_NORMAL,\
				"[%s,%d] hy_tap1(%d), is not support.\n",\
				__F__,__L__,hy_tap1);
			PE_SHP_HW_L9_DBG_CHECK_CODE((hy_tap1==PE_SHP_HW_L9_SCL_06TAP_NORMAL&&\
				idx1->h_luma_id>=PE_SHP_SCL_COEFF_LUMA_H_06_L9B0_NUM),\
				idx1->h_luma_id=PE_SHP_HW_L9_IDX_Y_DFLT,\
				"[%s,%d] hy_tap1(%d), h_luma_id(%d) is out of range.\n",\
				__F__,__L__,hy_tap1,idx1->h_luma_id);
			/* R : v luma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE((vy_tap1==PE_SHP_HW_L9_SCL_12TAP),\
				vy_tap1=PE_SHP_HW_L9_SCL_06TAP_NORMAL,\
				"[%s,%d] vy_tap1(%d), is not support.\n",\
				__F__,__L__,vy_tap1);
			PE_SHP_HW_L9_DBG_CHECK_CODE(((vy_tap1==PE_SHP_HW_L9_SCL_06TAP_NORMAL||\
				vy_tap1==PE_SHP_HW_L9_SCL_06TAP_HALF)&&\
				idx1->v_luma_id>=PE_SHP_SCL_COEFF_LUMA_V_06_L9B0_NUM),\
				idx1->v_luma_id=PE_SHP_HW_L9_IDX_Y_DFLT,\
				"[%s,%d] vy_tap1(%d), v_luma_id(%d) is out of range.\n",\
				__F__,__L__,vy_tap1,idx1->v_luma_id);
			/* R : h chroma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE((hc_tap1==PE_SHP_HW_L9_SCL_12TAP),\
				hc_tap1=PE_SHP_HW_L9_SCL_06TAP_NORMAL,\
				"[%s,%d] hc_tap1(%d), is not support.\n",\
				__F__,__L__,hc_tap1);
			PE_SHP_HW_L9_DBG_CHECK_CODE((hc_tap1==PE_SHP_HW_L9_SCL_06TAP_NORMAL&&\
				idx1->h_chrm_id>=PE_SHP_SCL_COEFF_CHROMA_H_L9B0_NUM),\
				idx1->h_chrm_id=PE_SHP_HW_L9_IDX_C_DFLT,\
				"[%s,%d] hc_tap0(%d), h_chrm_id(%d) is out of range.\n",\
				__F__,__L__,hc_tap1,idx1->h_chrm_id);
			/* R : v chroma id check */
			PE_SHP_HW_L9_DBG_CHECK_CODE((vc_tap1==PE_SHP_HW_L9_SCL_12TAP),\
				vc_tap1=PE_SHP_HW_L9_SCL_06TAP_NORMAL,\
				"[%s,%d] vc_tap1(%d), is not support.\n",\
				__F__,__L__,vc_tap1);
			PE_SHP_HW_L9_DBG_CHECK_CODE(((vc_tap1==PE_SHP_HW_L9_SCL_06TAP_NORMAL||\
				vc_tap1==PE_SHP_HW_L9_SCL_06TAP_HALF)&&\
				idx1->v_chrm_id>=PE_SHP_SCL_COEFF_CHROMA_V_L9B0_NUM),\
				idx1->v_chrm_id=PE_SHP_HW_L9_IDX_C_DFLT,\
				"[%s,%d] vc_tap1(%d), v_chrm_id(%d) is out of range.\n",\
				__F__,__L__,vc_tap1,idx1->v_chrm_id);

			/* idx control, down scale case */
			if(hy_tap0>=PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				hy_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				hy_tap0<=PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx0->h_luma_id=0;
			}
			if(vy_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				vy_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				vy_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx0->v_luma_id=0;
			}
			if(hc_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				hc_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				hc_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx0->h_chrm_id=0;
			}
			if(vc_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				vc_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				vc_tap0==PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx0->v_chrm_id=0;
			}
			if(hy_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				hy_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				hy_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx1->h_luma_id=0;
			}
			if(vy_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				vy_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				vy_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx1->v_luma_id=0;
			}
			if(hc_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				hc_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				hc_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx1->h_chrm_id=0;
			}
			if(vc_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN75 ||\
				vc_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN50 ||\
				vc_tap1==PE_SHP_HW_L9_SCL_06TAP_DOWN25)
			{
				idx1->v_chrm_id=0;
			}
		}
		else
		{
			PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n"); 
			idx0->h_luma_id=idx0->v_luma_id=idx0->h_chrm_id=idx0->v_chrm_id=0;
			idx1->h_luma_id=idx1->v_luma_id=idx1->h_chrm_id=idx1->v_chrm_id=0;
		}
	}while(0);
	return;
}
static PE_SHP_HW_L9_FLAG_T PE_SHP_HW_L9_GetDoubleSetFlag(LX_PE_WIN_ID win_id,LX_PE_SHP_SCLFILTER_T pre_idx,PE_SHP_HW_L9_SETTINGS_T *cur_param)
{
	PE_SHP_HW_L9_FLAG_T flag = {0,0,0,0};
	PE_SHP_HW_L9_SETTINGS_T *pre_tap=&_g_pe_shp_hw_l9_info;
	PE_SHP_HW_L9_CHECK_CODE(win_id>=LX_PE_WIN_NUM,return flag,"[%s,%d] win_id(%d) error.\n",__F__,__L__,win_id);
	if(pre_tap->h_y_tap[win_id]!=cur_param->h_y_tap[win_id])
	{
		flag.h_y=1;
		/* 12tap filter can not set h only.(h&v or v) */
		if(cur_param->h_y_tap[win_id]==PE_SHP_HW_L9_SCL_12TAP)
		{
			if(cur_param->scl_idx[win_id].h_luma_id!=cur_param->scl_idx[win_id].v_luma_id)
				flag.v_y=1;
		}
	}
	else if((cur_param->h_y_tap[win_id]==PE_SHP_HW_L9_SCL_12TAP) ||
		(cur_param->h_y_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_NORMAL) ||
		(cur_param->h_y_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_HALF))
	{
		if(pre_idx.h_luma_id!=cur_param->scl_idx[win_id].h_luma_id)
		{
			flag.h_y=1;
			/* 12tap filter can not set h only.(h&v or v) */
			if(pre_tap->h_y_tap[win_id]==PE_SHP_HW_L9_SCL_12TAP)
			{
				if(cur_param->scl_idx[win_id].h_luma_id!=cur_param->scl_idx[win_id].v_luma_id)
					flag.v_y=1;
			}
		}
	}
	if(pre_tap->h_c_tap[win_id]!=cur_param->h_c_tap[win_id])
	{
		flag.h_c=1;
	}
	else if((cur_param->h_c_tap[win_id]==PE_SHP_HW_L9_SCL_12TAP) ||
		(cur_param->h_c_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_NORMAL) ||
		(cur_param->h_c_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_HALF))
	{
		if(pre_idx.h_chrm_id!=cur_param->scl_idx[win_id].h_chrm_id)
			flag.h_c=1;
	}
	if(pre_tap->v_y_tap[win_id]!=cur_param->v_y_tap[win_id])
	{
		flag.v_y=1;
	}
	else if((cur_param->v_y_tap[win_id]==PE_SHP_HW_L9_SCL_12TAP) ||
		(cur_param->v_y_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_NORMAL) ||
		(cur_param->v_y_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_HALF))
	{
		if(pre_idx.v_luma_id!=cur_param->scl_idx[win_id].v_luma_id)
			flag.v_y=1;
	}
	if(pre_tap->v_c_tap[win_id]!=cur_param->v_c_tap[win_id])
	{
		flag.v_c=1;
	}
	else if((cur_param->v_c_tap[win_id]==PE_SHP_HW_L9_SCL_12TAP) ||
		(cur_param->v_c_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_NORMAL) ||
		(cur_param->v_c_tap[win_id]==PE_SHP_HW_L9_SCL_06TAP_HALF))
	{
		if(pre_idx.v_chrm_id!=cur_param->scl_idx[win_id].v_chrm_id)
			flag.v_c=1;
	}
	PE_SHP_HW_L9_DBG_PRINT("set[%d] flag y(h,v):%d,%d, c(h,v):%d,%d\n",win_id,flag.h_y,flag.v_y,flag.h_c,flag.v_c);
	return flag;
}
static int PE_SHP_HW_L9_SetSclCoeff(LX_PE_WIN_ID win_id, PE_SHP_HW_L9_FLAG_T flag, PE_SHP_HW_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 data_size,base_addr;
	UINT8 h_y_idx,h_c_idx,v_y_idx,v_c_idx;
	PE_SHP_HW_L9_SCL h_y_tap,h_c_tap,v_y_tap,v_c_tap;
	base_addr = (win_id==LX_PE_WIN_0)? 0x0:0x2000;
	PE_SHP_HW_L9_CHECK_CODE(win_id>=LX_PE_WIN_NUM,return RET_ERROR,"[%s,%d] win_id(%d) error.\n",__F__,__L__,win_id);
	h_y_idx = pstParams->scl_idx[win_id].h_luma_id;
	h_c_idx = pstParams->scl_idx[win_id].h_chrm_id;
	v_y_idx = pstParams->scl_idx[win_id].v_luma_id;
	v_c_idx = pstParams->scl_idx[win_id].v_chrm_id;
	h_y_tap = pstParams->h_y_tap[win_id];
	h_c_tap = pstParams->h_c_tap[win_id];
	v_y_tap = pstParams->v_y_tap[win_id];
	v_c_tap = pstParams->v_c_tap[win_id];
	if(flag.h_y)
	{
		switch(h_y_tap)
		{
			case PE_SHP_HW_L9_SCL_12TAP:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_h_12tap_coeff_l9b0[%d]\n",h_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_H_12_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_h_12tap_coeff_l9b0[h_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_h_12tap_coeff_l9a0[%d]\n",h_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_H_12_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_h_12tap_coeff_l9a0[h_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN75:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_h_dn_75_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_H_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_h_dn_75_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN50:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_h_dn_50_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_H_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_h_dn_50_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN25:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_h_dn_25_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_H_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_h_dn_25_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_NORMAL:
			case PE_SHP_HW_L9_SCL_06TAP_HALF:
			default:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_h_06tap_coeff_l9b0[%d]\n",h_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_H_06_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_h_06tap_coeff_l9b0[h_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_h_06tap_coeff_l9a0[%d]\n",h_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_H_06_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_h_06tap_coeff_l9a0[h_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
		}
	}
	if(flag.h_c)
	{
		switch(h_c_tap)
		{
			case PE_SHP_HW_L9_SCL_12TAP:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_h_coeff_l9b0[%d]\n",h_c_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_H_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_h_coeff_l9b0[h_c_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
					flag.v_c = 0;	// avoid double setting
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_def_12tap_coeff_l9a0\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_12_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_def_12tap_coeff_l9a0,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
					flag.v_c = 0;	// avoid double setting
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN75:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_h_dn_75_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_H_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_h_dn_75_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN50:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_h_dn_50_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_H_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_h_dn_50_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN25:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_h_dn_25_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_H_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_h_dn_25_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_NORMAL:
			case PE_SHP_HW_L9_SCL_06TAP_HALF:
			default:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_h_coeff_l9b0[%d]\n",h_c_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_H_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_h_coeff_l9b0[h_c_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_h_06tap_coeff_l9a0\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_H_06_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_h_06tap_coeff_l9a0,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
		}
	}
	if(flag.v_y)
	{
		switch(v_y_tap)
		{
			case PE_SHP_HW_L9_SCL_12TAP:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_12tap_coeff_l9b0[%d]\n",v_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_12_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_12tap_coeff_l9b0[v_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_12tap_coeff_l9a0[%d]\n",v_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_12_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_12tap_coeff_l9a0[v_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_HALF:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_half_06tap_coeff_l9b0[%d]\n",v_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_06_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_half_06tap_coeff_l9b0[v_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_half_06tap_coeff_l9a0[%d]\n",v_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_06_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_half_06tap_coeff_l9a0[v_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN75:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_dn_75_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_dn_75_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
			break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN50:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_dn_50_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_dn_50_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
			break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN25:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_dn_25_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_dn_25_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
			break;
			case PE_SHP_HW_L9_SCL_06TAP_NORMAL:
			default:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_06tap_coeff_l9b0[%d]\n",v_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_06_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_06tap_coeff_l9b0[v_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_luma_v_06tap_coeff_l9a0[%d]\n",v_y_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_LUMA_V_06_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_luma_v_06tap_coeff_l9a0[v_y_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
		}
	}
	if(flag.v_c)
	{
		switch(v_c_tap)
		{
			case PE_SHP_HW_L9_SCL_12TAP:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_h_coeff_l9b0[%d]\n",v_c_idx);
					/* v12t mode : v_c_flt share h_c_flt coeff. */
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_H_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_h_coeff_l9b0[v_c_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_def_12tap_coeff_l9a0\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_12_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_def_12tap_coeff_l9a0,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN75:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_v_dn_75_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_V_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_v_dn_75_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN50:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_v_dn_50_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_V_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_v_dn_50_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_DOWN25:
				if(PE_KDRV_VER_L9)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_v_dn_25_06tap_coeff_l9\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_V_06_L9_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_v_dn_25_06tap_coeff_l9,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
			case PE_SHP_HW_L9_SCL_06TAP_NORMAL:
			case PE_SHP_HW_L9_SCL_06TAP_HALF:
			default:
				if(PE_KDRV_VER_L9BX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_v_coeff_l9b0[%d]\n",v_c_idx);
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_V_L9B0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_v_coeff_l9b0[v_c_idx],base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				else if(PE_KDRV_VER_L9AX)
				{
					PE_SHP_HW_L9_DBG_PRINT("set shp_scl_chroma_v_06tap_coeff_l9a0\n");
					data_size = sizeof(PE_REG_PARAM_T)*PE_SHP_SCL_CHROMA_V_06_L9A0_NUM;
					ret = PE_REG_SetTable(shp_scl_chroma_v_06tap_coeff_l9a0,base_addr,data_size);
					PE_SHP_HW_L9_CHECK_CODE(ret,return ret,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
				}
				break;
		}
	}
	return ret;
}
static int PE_SHP_HW_L9_SetSclSettingCnt(PE_SHP_HW_L9_FLAG_T flag, PE_SHP_HW_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 cnt = 0;
	do {
		CHECK_KNULL(pstParams);
		PE_SHP_HW_L9_DBG_PRINT("set: flag: hy:%d,vy:%d, tap: h_y:%d,v_y:%d\n",\
			flag.h_y,flag.v_y,pstParams->h_y_tap[LX_PE_WIN_0],pstParams->v_y_tap[LX_PE_WIN_0]);
		if(PE_KDRV_VER_L9)
		{
			if((flag.h_y && pstParams->h_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_12TAP)||\
				(flag.v_y && pstParams->v_y_tap[LX_PE_WIN_0]==PE_SHP_HW_L9_SCL_12TAP))
			{
				if(cnt>200)	cnt=0;
				else		cnt++;
				ret = PE_FWI_L9_SetSclSettingCnt(cnt);
				PE_SHP_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetSclSettingCnt() error.\n",__F__,__L__);
				PE_SHP_HW_L9_DBG_PRINT("set fwi scl cnt : %d\n",cnt);
			}
		}
		else
		{
			PE_SHP_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}

