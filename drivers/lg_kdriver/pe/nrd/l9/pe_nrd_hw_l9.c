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


/** @file pe_nrd_hw_l9.c
 *
 *  driver for picture enhance noise reduction functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
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
#include "pe_etc.h"
#include "pe_etc_hw.h"
#include "pe_nrd_hw.h"
#include "pe_nrd_hw_l9a0.h"
#include "pe_nrd_hw_l9b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_L9_ERROR	printk

#define PE_NRD_HW_L9_DBG_PRINT(fmt,args...)	\
	if(_g_nrd_hw_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_NRD_HW_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_NRD_HW_L9_ERROR(fmt,##args);_action;}}
#define PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(_pre,_cur)	\
	PE_NRD_HW_L9_DBG_PRINT("%s(%d),%s(%d) : %s.\n",\
	#_pre,(_pre),#_cur,(_cur),((_pre)!=(_cur))? "different":"same")

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
static PE_NRD_HW_L9_TNR_FMT PE_NRD_HW_L9_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_L9_CRG_FMT PE_NRD_HW_L9_ConvDispInfoToCrgFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_L9_DNR_FMT PE_NRD_HW_L9_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_L9_CLC_FMT PE_NRD_HW_L9_ConvDispInfoToClcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_L9_VFY_FMT PE_NRD_HW_L9_ConvDispInfoToVfyFmt(LX_PE_INF_DISPLAY_T *disp_inf);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT8 _g_nrd_hw_l9_trace=0x0;	//default should be off.

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
void PE_NRD_HW_L9_SetDbgPrint(UINT32 on_off)
{
	_g_nrd_hw_l9_trace = on_off? 1:0;
	return;
}

/**
 * init nrd
 * 	- l9 tnr alpha lut loading sequence
 *		: load time on -> tnr off -> loading alpha lut -> tnr on -> load time off
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_L9_Init(void)
{
	int ret = RET_OK;
	UINT32 fw_msg;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			PE_P0L_L9B_QWr01(pe0_load,	load_time,	0x1);
			PE_P0R_L9B_QWr01(pe0_load,	load_time,	0x1);
			fw_msg = FALSE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);

			PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_init_param_l9b0,0);
			PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_init_param_l9b0,0);
			PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_alpha_lut_init_param_l9b0,0);
			PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_alpha_lut_init_param_l9b0,0);
			PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_crg_lut_init_param_l9b0,0);
			PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_crg_lut_init_param_l9b0,0);

			fw_msg = TRUE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			PE_P0L_L9B_QWr01(pe0_load,	load_time,	0x0);
			PE_P0R_L9B_QWr01(pe0_load,	load_time,	0x0);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			fw_msg = FALSE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);

			PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_init_param_l9a0,0);
			PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_init_param_l9a0,0);

			fw_msg = TRUE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
		}
		else
		{
			PE_NRD_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);	
	return ret;
}

/**
 * set nr default setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_L9_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 fw_msg;
	PE_INF_L9_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_NRD_HW_L9_TNR_FMT cur0_tnr_fmt,cur1_tnr_fmt;
	PE_NRD_HW_L9_CRG_FMT cur0_crg_fmt,cur1_crg_fmt;
	PE_NRD_HW_L9_DNR_FMT cur0_dnr_fmt,cur1_dnr_fmt;
	PE_NRD_HW_L9_CLC_FMT cur0_clc_fmt,cur1_clc_fmt;
	PE_NRD_HW_L9_VFY_FMT cur0_vfy_fmt,cur1_vfy_fmt;
	static PE_NRD_HW_L9_TNR_FMT pre0_tnr_fmt = PE_NRD_L9_TNR_NUM;
	static PE_NRD_HW_L9_TNR_FMT pre1_tnr_fmt = PE_NRD_L9_TNR_NUM;
	static PE_NRD_HW_L9_CRG_FMT pre0_crg_fmt = PE_NRD_L9_CRG_NUM;
	static PE_NRD_HW_L9_CRG_FMT pre1_crg_fmt = PE_NRD_L9_CRG_NUM;
	static PE_NRD_HW_L9_DNR_FMT pre0_dnr_fmt = PE_NRD_L9_DNR_NUM;
	static PE_NRD_HW_L9_DNR_FMT pre1_dnr_fmt = PE_NRD_L9_DNR_NUM;
	static PE_NRD_HW_L9_CLC_FMT pre0_clc_fmt = PE_NRD_L9_CLC_NUM;
	static PE_NRD_HW_L9_CLC_FMT pre1_clc_fmt = PE_NRD_L9_CLC_NUM;
	static PE_NRD_HW_L9_VFY_FMT pre0_vfy_fmt = PE_NRD_L9_VFY_NUM;
	static PE_NRD_HW_L9_VFY_FMT pre1_vfy_fmt = PE_NRD_L9_VFY_NUM;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_L9_GetCurInfSettings(&inf_set);
		PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		if(PE_KDRV_VER_L9BX)
		{
			fw_msg = FALSE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			/* L : tnr */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_tnr_fmt = PE_NRD_HW_L9_ConvDispInfoToTnrFmt(cur0_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre0_tnr_fmt,cur0_tnr_fmt);
				if(pre0_tnr_fmt!=cur0_tnr_fmt)
				{
					switch(cur0_tnr_fmt)
					{
						case PE_NRD_L9_TNR_ATV_SECAM:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_atv_secam_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_ATV_NT_PAL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_atv_nt_pal_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_AV_SECAM:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_av_secam_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_AV_NT_PAL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_av_nt_pal_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_PC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_pc_all_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_DTV_SD_60:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_dtv_480_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_DTV_SD_50:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_dtv_576_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_DTV_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_dtv_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_COMP_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_comp_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_COMP_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_comp_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_HDMI_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_HDMI_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_default_hdmi_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre0_tnr_fmt=cur0_tnr_fmt;
				}
			}
			/* R : tnr */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_tnr_fmt = PE_NRD_HW_L9_ConvDispInfoToTnrFmt(cur1_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre1_tnr_fmt,cur1_tnr_fmt);
				if(pre1_tnr_fmt!=cur1_tnr_fmt)
				{
					switch(cur1_tnr_fmt)
					{
						case PE_NRD_L9_TNR_ATV_SECAM:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_atv_secam_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_ATV_NT_PAL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_atv_nt_pal_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_AV_SECAM:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_av_secam_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_AV_NT_PAL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_av_nt_pal_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_PC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_pc_all_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_DTV_SD_60:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_dtv_480_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_DTV_SD_50:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_dtv_576_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_DTV_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_dtv_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_COMP_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_comp_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_COMP_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_comp_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_HDMI_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_TNR_HDMI_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_default_hdmi_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre1_tnr_fmt=cur1_tnr_fmt;
				}
			}
			fw_msg = TRUE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			/* L : tnr color region */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_crg_fmt = PE_NRD_HW_L9_ConvDispInfoToCrgFmt(cur0_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre0_crg_fmt,cur0_crg_fmt);
				if(pre0_crg_fmt!=cur0_crg_fmt)
				{
					switch(cur0_crg_fmt)
					{
						case PE_NRD_L9_CRG_ALL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_tnr_crg_default_all_param_l9b0,0);
							break; 
						default:
							break;
					}
					pre0_crg_fmt=cur0_crg_fmt;
				}
			}
			/* R : tnr color region */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_crg_fmt = PE_NRD_HW_L9_ConvDispInfoToCrgFmt(cur1_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre1_crg_fmt,cur1_crg_fmt);
				if(pre1_crg_fmt!=cur1_crg_fmt)
				{
					switch(cur1_crg_fmt)
					{
						case PE_NRD_L9_CRG_ALL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_tnr_crg_default_all_param_l9b0,0);
							break; 
						default:
							break;
					}
					pre1_crg_fmt=cur1_crg_fmt;
				}
			}
			/* L : dnr */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_dnr_fmt = PE_NRD_HW_L9_ConvDispInfoToDnrFmt(cur0_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre0_dnr_fmt,cur0_dnr_fmt);
				if(pre0_dnr_fmt!=cur0_dnr_fmt)
				{
					switch(cur0_dnr_fmt)
					{
						case PE_NRD_L9_DNR_SD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_all_sd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_SD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_all_sd_p_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_HD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_all_hd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_HD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_all_hd_p_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_SD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_comp_sd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_SD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_comp_sd_p_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_HD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_comp_hd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_HD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_dnr_default_comp_hd_p_param_l9b0,0);
							break;
						default:
							break;
					}
					pre0_dnr_fmt=cur0_dnr_fmt;
				}
			}
			/* R : dnr */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_dnr_fmt = PE_NRD_HW_L9_ConvDispInfoToDnrFmt(cur1_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre1_dnr_fmt,cur1_dnr_fmt);
				if(pre1_dnr_fmt!=cur1_dnr_fmt)
				{
					switch(cur1_dnr_fmt)
					{
						case PE_NRD_L9_DNR_SD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_all_sd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_SD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_all_sd_p_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_HD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_all_hd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_HD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_all_hd_p_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_SD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_comp_sd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_SD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_comp_sd_p_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_HD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_comp_hd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_DNR_COMP_HD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_dnr_default_comp_hd_p_param_l9b0,0);
							break;
						default:
							break;
					}
					pre1_dnr_fmt=cur1_dnr_fmt;
				}
			}
			/* L : clc */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_clc_fmt = PE_NRD_HW_L9_ConvDispInfoToClcFmt(cur0_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre0_clc_fmt,cur0_clc_fmt);
				if(pre0_clc_fmt!=cur0_clc_fmt)
				{
					switch(cur0_clc_fmt)
					{
						case PE_NRD_L9_CLC_ATV:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_atv_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_AV_NTSC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_av_ntsc_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_AV_PAL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_av_pal_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_DTV_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_dtv_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_DTV_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_dtv_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_PC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_pc_all_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_COMP_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_comp_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_COMP_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_comp_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_HDMI_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_HDMI_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_clc_default_hdmi_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre0_clc_fmt=cur0_clc_fmt;
				}
			}
			/* R : clc */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_clc_fmt = PE_NRD_HW_L9_ConvDispInfoToClcFmt(cur1_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre1_clc_fmt,cur1_clc_fmt);
				if(pre1_clc_fmt!=cur1_clc_fmt)
				{
					switch(cur1_clc_fmt)
					{
						case PE_NRD_L9_CLC_ATV:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_atv_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_AV_NTSC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_av_ntsc_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_AV_PAL:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_av_pal_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_DTV_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_dtv_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_DTV_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_dtv_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_PC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_pc_all_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_COMP_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_comp_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_COMP_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_comp_hd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_HDMI_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_hdmi_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_CLC_HDMI_HD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_clc_default_hdmi_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre1_clc_fmt=cur1_clc_fmt;
				}
			}
			/* L : v filter y */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_vfy_fmt = PE_NRD_HW_L9_ConvDispInfoToVfyFmt(cur0_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre0_vfy_fmt,cur0_vfy_fmt);
				if(pre0_vfy_fmt!=cur0_vfy_fmt)
				{
					switch(cur0_vfy_fmt)
					{
						case PE_NRD_L9_VFY_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_vflt_y_default_all_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_VFY_PC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_vflt_y_default_pc_all_param_l9b0,0);
							break;
						case PE_NRD_L9_VFY_HD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_vflt_y_default_all_hd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_VFY_HD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_vflt_y_default_all_hd_p_param_l9b0,0);
							break;
						default:
							break;
					}
					pre0_vfy_fmt=cur0_vfy_fmt;
				}
			}
			/* R : v filter y */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_vfy_fmt = PE_NRD_HW_L9_ConvDispInfoToVfyFmt(cur1_inf);
				PE_NRD_HW_L9_DBG_PRINT_FMT_STATE(pre1_vfy_fmt,cur1_vfy_fmt);
				if(pre1_vfy_fmt!=cur1_vfy_fmt)
				{
					switch(cur1_vfy_fmt)
					{
						case PE_NRD_L9_VFY_SD:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_vflt_y_default_all_sd_param_l9b0,0);
							break;
						case PE_NRD_L9_VFY_PC:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_vflt_y_default_pc_all_param_l9b0,0);
							break;
						case PE_NRD_L9_VFY_HD_I:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_vflt_y_default_all_hd_i_param_l9b0,0);
							break;
						case PE_NRD_L9_VFY_HD_P:
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_vflt_y_default_all_hd_p_param_l9b0,0);
							break;
						default:
							break;
					}
					pre1_vfy_fmt=cur1_vfy_fmt;
				}
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			fw_msg = FALSE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				switch(cur0_inf->src_type)
				{
					case LX_PE_SRC_DTV:
						if(cur0_inf->fmt_type==LX_PE_FMT_SD)
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_default_sd_dtv_param_l9a0,0);
						}
						else
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_default_hd_param_l9a0,0);
						}
						break;
					case LX_PE_SRC_ATV:
					case LX_PE_SRC_CVBS:
						if(cur0_inf->fmt_type==LX_PE_FMT_SECAM)
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_default_sd_ana_secam_param_l9a0,0);
						}
						else if(cur0_inf->src_type==LX_PE_SRC_ATV)
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_default_sd_ana_rf_param_l9a0,0);
						}
						else	//CVBS
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_default_sd_param_l9a0,0);
						}
						break;
					case LX_PE_SRC_COMP:
					case LX_PE_SRC_PC:
					case LX_PE_SRC_HDMI:
					default:
						if(cur0_inf->fmt_type==LX_PE_FMT_SD)
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_default_sd_param_l9a0,0);
						}
						else
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_l_default_hd_param_l9a0,0);
						}
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
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_default_sd_dtv_param_l9a0,0);
						}
						else
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_default_hd_param_l9a0,0);
						}
						break;
					case LX_PE_SRC_ATV:
					case LX_PE_SRC_CVBS:
						if(cur1_inf->fmt_type==LX_PE_FMT_SECAM)
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_default_sd_ana_secam_param_l9a0,0);
						}
						else if(cur1_inf->src_type==LX_PE_SRC_ATV)
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_default_sd_ana_rf_param_l9a0,0);
						}
						else	//CVBS
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_default_sd_param_l9a0,0);
						}
						break;
					case LX_PE_SRC_COMP:
					case LX_PE_SRC_PC:
					case LX_PE_SRC_HDMI:
					default:
						if(cur1_inf->fmt_type==LX_PE_FMT_SD)
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_default_sd_param_l9a0,0);
						}
						else
						{
							PE_SET_REG_TABLE(NRD_HW_L9,nrd_r_default_hd_param_l9a0,0);
						}
						break;
				}
			}
			/* tnr motion select */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				if((cur0_inf->src_type==LX_PE_SRC_ATV||cur0_inf->src_type==LX_PE_SRC_CVBS)&&
					(cur0_inf->fmt_type==LX_PE_FMT_SECAM))
				{
					PE_P0L_L9A_QWr02(p0l_tnr_ctrl_00,	calc_motion_max_yc, 	0x0,\
														hist_motion_max_yc, 	0x0);
				}
				else
				{
					PE_P0L_L9A_QWr02(p0l_tnr_ctrl_00,	calc_motion_max_yc, 	0x1,\
														hist_motion_max_yc, 	0x1);
				}
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				if((cur1_inf->src_type==LX_PE_SRC_ATV||cur1_inf->src_type==LX_PE_SRC_CVBS)&&
					(cur1_inf->fmt_type==LX_PE_FMT_SECAM))
				{
					PE_P0R_L9A_QWr02(p0r_tnr_ctrl_00,	calc_motion_max_yc, 	0x0,\
														hist_motion_max_yc, 	0x0);
				}
				else
				{
					PE_P0R_L9A_QWr02(p0r_tnr_ctrl_00,	calc_motion_max_yc, 	0x1,\
														hist_motion_max_yc, 	0x1);
				}
			}

			fw_msg = TRUE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
		}
		else
		{
			PE_NRD_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
static PE_NRD_HW_L9_TNR_FMT PE_NRD_HW_L9_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_L9_TNR_FMT tnr_fmt = PE_NRD_L9_TNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			if(disp_inf->fmt_type==LX_PE_FMT_SECAM)
			{
				tnr_fmt = PE_NRD_L9_TNR_ATV_SECAM;
			}
			else
			{
				tnr_fmt = PE_NRD_L9_TNR_ATV_NT_PAL;
			}
			break;
		case LX_PE_SRC_CVBS:
			if(disp_inf->fmt_type==LX_PE_FMT_SECAM)
			{
				tnr_fmt = PE_NRD_L9_TNR_AV_SECAM;
			}
			else
			{
				tnr_fmt = PE_NRD_L9_TNR_AV_NT_PAL;
			}
			break;
		case LX_PE_SRC_PC:
			{
				tnr_fmt = PE_NRD_L9_TNR_PC;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ || \
					disp_inf->dtv_type==LX_PE_DTV_FILEPLAY || \
					disp_inf->dtv_type==LX_PE_DTV_HDDPLAY)
				{
					tnr_fmt = PE_NRD_L9_TNR_DTV_SD_60;
				}
				else
				{
					tnr_fmt = PE_NRD_L9_TNR_DTV_SD_50;
				}
			}
			else
			{
				tnr_fmt = PE_NRD_L9_TNR_DTV_HD;
			}
			break;
		case LX_PE_SRC_COMP:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_L9_TNR_COMP_SD;
			}
			else
			{
				tnr_fmt = PE_NRD_L9_TNR_COMP_HD;
			}
			break;
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				tnr_fmt = PE_NRD_L9_TNR_HDMI_SD;
			}
			else
			{
				tnr_fmt = PE_NRD_L9_TNR_HDMI_HD;
			}
			break;
	}
	return tnr_fmt;
}
static PE_NRD_HW_L9_CRG_FMT PE_NRD_HW_L9_ConvDispInfoToCrgFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_L9_CRG_FMT crg_fmt = PE_NRD_L9_CRG_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
		case LX_PE_SRC_PC:
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			crg_fmt = PE_NRD_L9_CRG_ALL;
			break;
	}
	return crg_fmt;
}
static PE_NRD_HW_L9_DNR_FMT PE_NRD_HW_L9_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_L9_DNR_FMT dnr_fmt = PE_NRD_L9_DNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
			{
				dnr_fmt = PE_NRD_L9_DNR_SD_I;
			}
			break;
		case LX_PE_SRC_PC:
			{
				dnr_fmt = PE_NRD_L9_DNR_HD_P;
			}
			break;
		case LX_PE_SRC_COMP:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					dnr_fmt = PE_NRD_L9_DNR_COMP_SD_I;
				}
				else
				{
					dnr_fmt = PE_NRD_L9_DNR_COMP_SD_P;
				}
			}
			else
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					dnr_fmt = PE_NRD_L9_DNR_COMP_HD_I;
				}
				else
				{
					dnr_fmt = PE_NRD_L9_DNR_COMP_HD_P;
				}
			}
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					dnr_fmt = PE_NRD_L9_DNR_SD_I;
				}
				else
				{
					dnr_fmt = PE_NRD_L9_DNR_SD_P;
				}
			}
			else
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					dnr_fmt = PE_NRD_L9_DNR_HD_I;
				}
				else
				{
					dnr_fmt = PE_NRD_L9_DNR_HD_P;
				}
			}
			break;
	}
	return dnr_fmt;
}
static PE_NRD_HW_L9_CLC_FMT PE_NRD_HW_L9_ConvDispInfoToClcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_L9_CLC_FMT clc_fmt = PE_NRD_L9_CLC_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			{
				clc_fmt = PE_NRD_L9_CLC_ATV;
			}
		break;
		case LX_PE_SRC_CVBS:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				clc_fmt = PE_NRD_L9_CLC_AV_NTSC;
			}
			else
			{
				clc_fmt = PE_NRD_L9_CLC_AV_PAL;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				clc_fmt = PE_NRD_L9_CLC_DTV_SD;
			}
			else
			{
				if(disp_inf->dtv_type==LX_PE_DTV_TESTPIC)
				{
					clc_fmt = PE_NRD_L9_CLC_PC;
				}
				else
				{
					clc_fmt = PE_NRD_L9_CLC_DTV_HD;
				}
			}
			break;
		case LX_PE_SRC_PC:
			{
				clc_fmt = PE_NRD_L9_CLC_PC;
			}
			break;
		case LX_PE_SRC_COMP:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				clc_fmt = PE_NRD_L9_CLC_COMP_SD;
			}
			else
			{
				clc_fmt = PE_NRD_L9_CLC_COMP_HD;
			}
			break;
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				clc_fmt = PE_NRD_L9_CLC_HDMI_SD;
			}
			else
			{
				clc_fmt = PE_NRD_L9_CLC_HDMI_HD;
			}
			break;
	}
	return clc_fmt;
}
static PE_NRD_HW_L9_VFY_FMT PE_NRD_HW_L9_ConvDispInfoToVfyFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_L9_VFY_FMT vfy_fmt = PE_NRD_L9_VFY_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
			{
				vfy_fmt = PE_NRD_L9_VFY_SD;
			}
			break;
		case LX_PE_SRC_PC:
			{
				vfy_fmt = PE_NRD_L9_VFY_PC;
			}
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				vfy_fmt = PE_NRD_L9_VFY_SD;
			}
			else
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					vfy_fmt = PE_NRD_L9_VFY_HD_I;
				}
				else
				{
					vfy_fmt = PE_NRD_L9_VFY_HD_P;
				}
			}
			break;
	}
	return vfy_fmt;
}
/**
 * set tnr measure window
 *
 * @param   *pCfg [in] PE_TSK_L9_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_L9_SetMeasureWinCtrl(PE_TSK_L9_CFG_T *pCfg)
{
	int ret = RET_OK;
	UINT32 h_size[2],v_size[2];
	UINT32 h_ofst[2]={0,0};
	UINT32 v_ofst[2]={0,0};
	UINT32 cur_x0[2]={0,0};
	UINT32 cur_y0[2]={0,0};
	UINT32 cur_x1[2]={0,0};
	UINT32 cur_y1[2]={0,0};
	static UINT32 pre_h_size[2]={0xffff,0xffff};
	static UINT32 pre_v_size[2]={0xffff,0xffff};
	static UINT32 count = 0;
	PE_INF_L9_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_L9_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_L9BX)
		{
			h_size[0] = ctrl0_info->pe0_src_h;
			v_size[0] = ctrl0_info->pe0_src_v;
			h_size[1] = ctrl1_info->pe0_src_h;
			v_size[1] = ctrl1_info->pe0_src_v;
			if(pre_h_size[0]!=h_size[0] || pre_v_size[0]!=v_size[0])
			{
				h_ofst[0]=h_size[0]>>4;	// 1/16=6.25%
				v_ofst[0]=v_size[0]>>4;	// 1/16=6.25%
				cur_x0[0]=h_ofst[0];
				cur_y0[0]=v_ofst[0];
				cur_x1[0]=h_size[0]-h_ofst[0];
				cur_y1[0]=v_size[0]-v_ofst[0];
				PE_P0L_L9B_QWr02(tnr_ctrl_14,	x0,	cur_x0[0],\
												y0,	cur_y0[0]);
				PE_P0L_L9B_QWr02(tnr_ctrl_15,	x1,	cur_x1[0],\
												y1,	cur_y1[0]);
				PE_NRD_HW_L9_DBG_PRINT("[L][size:%4d,%4d -> %4d,%4d][ofst:%4d,%4d][x,y:%4d,%4d,%4d,%4d]\n\n",\
					pre_h_size[0],pre_v_size[0],h_size[0],v_size[0],h_ofst[0],v_ofst[0],\
					cur_x0[0],cur_y0[0],cur_x1[0],cur_y1[0]);
				pre_h_size[0]=h_size[0];
				pre_v_size[0]=v_size[0];
			}
			if(pre_h_size[1]!=h_size[1] || pre_v_size[1]!=v_size[1])
			{
				h_ofst[1]=h_size[1]>>4;	// 1/16=6.25%
				v_ofst[1]=v_size[1]>>4;	// 1/16=6.25%
				cur_x0[1]=h_ofst[1];
				cur_y0[1]=v_ofst[1];
				cur_x1[1]=h_size[1]-h_ofst[1];
				cur_y1[1]=v_size[1]-v_ofst[1];
				PE_P0R_L9B_QWr02(tnr_ctrl_14,	x0,	cur_x0[1],\
												y0,	cur_y0[1]);
				PE_P0R_L9B_QWr02(tnr_ctrl_15,	x1,	cur_x1[1],\
												y1,	cur_y1[1]);
				PE_NRD_HW_L9_DBG_PRINT("[R][size:%4d,%4d -> %4d,%4d][ofst:%4d,%4d][x,y:%4d,%4d,%4d,%4d]\n\n",\
					pre_h_size[1],pre_v_size[1],h_size[1],v_size[1],h_ofst[1],v_ofst[1],\
					cur_x0[1],cur_y0[1],cur_x1[1],cur_y1[1]);
				pre_h_size[1]=h_size[1];
				pre_v_size[1]=v_size[1];
			}
			if(_g_nrd_hw_l9_trace)
			{
				if(count>240)
				{
					PE_NRD_HW_L9_DBG_PRINT("[state][L:%4d,%4d][R:%4d,%4d]\n\n",\
						h_size[0],v_size[0],h_size[1],v_size[1]);
					count=1;
				}
				count++;
			}
		}
		else
		{
			PE_NRD_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return ret;
}

