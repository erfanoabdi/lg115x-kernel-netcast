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


/** @file pe_nrd_hw_h13.c
 *
 *  driver for picture enhance noise reduction functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.12
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
#include "pe_nrd_hw_h13a0.h"
#include "pe_nrd_hw_h13b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 352,288 = 704/2,576/2 */
#define PE_NRD_HW_H13_H_MIN			352
#define PE_NRD_HW_H13_V_MIN			288

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_H13_ERROR	printk

#define PE_NRD_HW_H13_DBG_PRINT(fmt,args...)	\
	if(_g_nrd_hw_h13_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_NRD_HW_H13_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_NRD_HW_H13_ERROR(fmt,##args);_action;}}
#define PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(_pre,_cur)	\
	PE_NRD_HW_H13_DBG_PRINT("%s(%d),%s(%d) : %s.\n",\
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
static int PE_NRD_HW_H13B_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_NRD_HW_H13A_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static PE_NRD_HW_H13B_TNR_FMT PE_NRD_HW_H13B_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_H13B_DNR_FMT PE_NRD_HW_H13B_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_H13A_TNR_FMT PE_NRD_HW_H13A_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_NRD_HW_H13A_DNR_FMT PE_NRD_HW_H13A_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT8 _g_nrd_hw_h13_trace=0x0;	//default should be off.

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
void PE_NRD_HW_H13_SetDbgPrint(UINT32 on_off)
{
	_g_nrd_hw_h13_trace = on_off? 1:0;
	return;
}

/**
 * init nrd
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_HW_H13_Init(void)
{
	int ret = RET_OK;
	UINT32 fw_msg;
	do{
		if(PE_KDRV_VER_H13BX)
		{
			PE_P0L_H13B0_QWr01(p0l_pe0_load,	load_time,	0x1);
			PE_P0R_H13B0_QWr01(p0r_pe0_load,	load_time,	0x1);
			fw_msg = FALSE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_crg_init_ia_h13b0,		PE_REG_H13_WRITE_BASE);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_alphalut_init_ia_h13b0,	PE_REG_H13_WRITE_BASE);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_crg_init_ia_h13b0,		PE_PE0_REG_H13_LRDIFF);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_alphalut_init_ia_h13b0,	PE_PE0_REG_H13_LRDIFF);
			PE_SET_REG_TABLE(NRD_HW_H13,nr_l_init_h13b0,PE_REG_H13_WRITE_BASE);
			PE_SET_REG_TABLE(NRD_HW_H13,nr_l_init_h13b0,PE_PE0_REG_H13_LRDIFF);
			fw_msg = TRUE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			PE_P0L_H13B0_QWr01(p0l_pe0_load,	load_time,	0x0);
			PE_P0R_H13B0_QWr01(p0r_pe0_load,	load_time,	0x0);
			/* enable tnr noise measure window */
			PE_P0L_H13B0_QWr01(p0l_tnr_ctrl_14,	noise_measure_win_en,	0x1);
			PE_P0R_H13B0_QWr01(p0r_tnr_ctrl_14,	noise_measure_win_en,	0x1);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_P0L_H13_QWr01(p0l_pe0_load,	load_time,	0x1);
			PE_P0R_H13_QWr01(p0r_pe0_load,	load_time,	0x1);
			fw_msg = FALSE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_crg_lut_init_ia_h13a0,0);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_alpha_lut_init_ia_h13a0,0);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_r_crg_lut_init_ia_h13a0,0);
			PE_SET_REG_TABLE(NRD_HW_H13,tnr_r_alpha_lut_init_ia_h13a0,0);
			PE_SET_REG_TABLE(NRD_HW_H13,nr_l_init_h13a0,0);
			PE_SET_REG_TABLE(NRD_HW_H13,nr_r_init_h13a0,0);
			fw_msg = TRUE;
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR_ENABLE, &fw_msg, sizeof(fw_msg));
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			PE_P0L_H13_QWr01(p0l_pe0_load,	load_time,	0x0);
			PE_P0R_H13_QWr01(p0r_pe0_load,	load_time,	0x0);
		}
		else
		{
			PE_NRD_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
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
int PE_NRD_HW_H13_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13BX)
		{
			ret = PE_NRD_HW_H13B_SetDefault(pstParams);
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_NRD_HW_H13B_SetDefault() error.\n",__F__,__L__);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			ret = PE_NRD_HW_H13A_SetDefault(pstParams);
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_NRD_HW_H13A_SetDefault() error.\n",__F__,__L__);
		}
		else
		{
			PE_NRD_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);	
	return ret;
}
/**
 * set nr default setting(for H13BX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_H13B_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_H13_TNR_CTRL fwi_tnr;
	PE_FWI_H13_SETTINGS_T fwi_inf;
	PE_INF_H13_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_NRD_HW_H13B_TNR_FMT cur0_tnr_fmt,cur1_tnr_fmt;
	PE_NRD_HW_H13B_DNR_FMT cur0_dnr_fmt,cur1_dnr_fmt;
	static PE_NRD_HW_H13B_TNR_FMT pre0_tnr_fmt = PE_NRD_H13B_TNR_NUM;
	static PE_NRD_HW_H13B_TNR_FMT pre1_tnr_fmt = PE_NRD_H13B_TNR_NUM;
	static PE_NRD_HW_H13B_DNR_FMT pre0_dnr_fmt = PE_NRD_H13B_DNR_NUM;
	static PE_NRD_HW_H13B_DNR_FMT pre1_dnr_fmt = PE_NRD_H13B_DNR_NUM;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_FWI_H13_GetCurFwiSettings(&fwi_inf);
		PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_GetCurFwiSettings() error.\n",__F__,__L__);
		ret = PE_INF_H13_GetCurInfSettings(&inf_set);
		PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_GetCurInfSettings() error.\n",__F__,__L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		/* L : tnr */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_tnr_fmt = PE_NRD_HW_H13B_ConvDispInfoToTnrFmt(cur0_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre0_tnr_fmt,cur0_tnr_fmt);
			if(pre0_tnr_fmt!=cur0_tnr_fmt)
			{
				switch(cur0_tnr_fmt)
				{
					case PE_NRD_H13B_TNR_SD:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_sd_default_h13b0,			PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_SD_MC_OFF:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_sd_mc_off_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_ATV:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_atv_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_DVR_ATV:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_dvr_atv_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_ATV_SECAM:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_atv_secam_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_AV:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_av_default_h13b0,			PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_AV_SECAM:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_av_secam_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_HD:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_hd_default_h13b0,			PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_TNR_UD:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_ud_default_h13b0,			PE_REG_H13_WRITE_BASE);
						break;
					default:
						break;
				}
				pre0_tnr_fmt=cur0_tnr_fmt;
			}
			/* fwi tnr ctrl */
			fwi_tnr.tnr_en = 1;
			fwi_tnr.m_fir_en = fwi_inf.tnr_ctrl[LX_PE_WIN_0].m_fir_en;
			/* sync with default, if sd or hd&interlace, turn on m_fir_en. otherwise,off */
			switch(cur0_inf->src_type)
			{
				case LX_PE_SRC_ATV:
				case LX_PE_SRC_CVBS:
					fwi_tnr.m_fir_en = 1;
					break;
				case LX_PE_SRC_COMP:
				case LX_PE_SRC_DTV:
				case LX_PE_SRC_HDMI:
				case LX_PE_SRC_PC:
				default:
					if(cur0_inf->fmt_type==LX_PE_FMT_SD)
					{
						fwi_tnr.m_fir_en = 1;
					}
					else
					{
						if(cur0_inf->scan_type==LX_PE_SCAN_INTERLACE)
							fwi_tnr.m_fir_en = 1;
						else
							fwi_tnr.m_fir_en = 0;
					}
					break;
			}
			ret = PE_FWI_H13_SetTnrCtrl(LX_PE_WIN_0,&fwi_tnr);
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetTnrCtrl() error.\n",__F__,__L__);
			PE_NRD_HW_H13_DBG_PRINT("set[0]tnr_en:%d,m_fir_en:%d\n",fwi_tnr.tnr_en,fwi_tnr.m_fir_en);
		}
		/* R : tnr */
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			cur1_tnr_fmt = PE_NRD_HW_H13B_ConvDispInfoToTnrFmt(cur1_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre1_tnr_fmt,cur1_tnr_fmt);
			if(pre1_tnr_fmt!=cur1_tnr_fmt)
			{
				switch(cur1_tnr_fmt)
				{
					case PE_NRD_H13B_TNR_SD:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_sd_default_h13b0,			PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_SD_MC_OFF:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_sd_mc_off_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_ATV:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_atv_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_DVR_ATV:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_dvr_atv_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_ATV_SECAM:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_atv_secam_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_AV:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_av_default_h13b0,			PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_AV_SECAM:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_av_secam_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_HD:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_hd_default_h13b0,			PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_TNR_UD:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_l_ud_default_h13b0,			PE_PE0_REG_H13_LRDIFF);
						break;
					default:
						break;
				}
				pre1_tnr_fmt=cur1_tnr_fmt;
			}
			/* fwi tnr ctrl */
			fwi_tnr.tnr_en = 1;
			fwi_tnr.m_fir_en = fwi_inf.tnr_ctrl[LX_PE_WIN_1].m_fir_en;
			/* sync with default, if sd or hd&interlace, turn on m_fir_en. otherwise,off */
			switch(cur1_inf->src_type)
			{
				case LX_PE_SRC_ATV:
				case LX_PE_SRC_CVBS:
					fwi_tnr.m_fir_en = 1;
					break;
				case LX_PE_SRC_COMP:
				case LX_PE_SRC_DTV:
				case LX_PE_SRC_HDMI:
				case LX_PE_SRC_PC:
				default:
					if(cur1_inf->fmt_type==LX_PE_FMT_SD)
					{
						fwi_tnr.m_fir_en = 1;
					}
					else
					{
						if(cur1_inf->scan_type==LX_PE_SCAN_INTERLACE)
							fwi_tnr.m_fir_en = 1;
						else
							fwi_tnr.m_fir_en = 0;
					}
					break;
			}
			ret = PE_FWI_H13_SetTnrCtrl(LX_PE_WIN_1,&fwi_tnr);
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetTnrCtrl() error.\n",__F__,__L__);
			PE_NRD_HW_H13_DBG_PRINT("set[1]tnr_en:%d,m_fir_en:%d\n",fwi_tnr.tnr_en,fwi_tnr.m_fir_en);
		}
		/* L : dnr */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_dnr_fmt = PE_NRD_HW_H13B_ConvDispInfoToDnrFmt(cur0_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre0_dnr_fmt,cur0_dnr_fmt);
			if(pre0_dnr_fmt!=cur0_dnr_fmt)
			{
				switch(cur0_dnr_fmt)
				{
					case PE_NRD_H13B_DNR_SD:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_sd_l_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_DNR_HD:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_hd_l_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_NRD_H13B_DNR_TP:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_tp_l_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					default:
						break;
				}
				pre0_dnr_fmt=cur0_dnr_fmt;
			}
		}
		/* R : dnr */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur1_dnr_fmt = PE_NRD_HW_H13B_ConvDispInfoToDnrFmt(cur1_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre1_dnr_fmt,cur1_dnr_fmt);
			if(pre1_dnr_fmt!=cur1_dnr_fmt)
			{
				switch(cur1_dnr_fmt)
				{
					case PE_NRD_H13B_DNR_SD:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_sd_l_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_DNR_HD:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_hd_l_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_NRD_H13B_DNR_TP:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_tp_l_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					default:
						break;
				}
				pre1_dnr_fmt=cur1_dnr_fmt;
			}
		}
	}while(0);	
	return ret;
}
/**
 * set nr default setting(for H13AX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_HW_H13A_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 yc_motion;
	PE_FWI_H13_TNR_CTRL fwi_tnr;
	PE_FWI_H13_SETTINGS_T fwi_inf;
	PE_INF_H13_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_NRD_HW_H13A_TNR_FMT cur0_tnr_fmt,cur1_tnr_fmt;
	PE_NRD_HW_H13A_DNR_FMT cur0_dnr_fmt,cur1_dnr_fmt;
	static PE_NRD_HW_H13A_TNR_FMT pre0_tnr_fmt = PE_NRD_H13A_TNR_NUM;
	static PE_NRD_HW_H13A_TNR_FMT pre1_tnr_fmt = PE_NRD_H13A_TNR_NUM;
	static PE_NRD_HW_H13A_DNR_FMT pre0_dnr_fmt = PE_NRD_H13A_DNR_NUM;
	static PE_NRD_HW_H13A_DNR_FMT pre1_dnr_fmt = PE_NRD_H13A_DNR_NUM;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_FWI_H13_GetCurFwiSettings(&fwi_inf);
		PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_GetCurFwiSettings() error.\n",__F__,__L__);
		ret = PE_INF_H13_GetCurInfSettings(&inf_set);
		PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_GetCurInfSettings() error.\n",__F__,__L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		/* L : tnr */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_tnr_fmt = PE_NRD_HW_H13A_ConvDispInfoToTnrFmt(cur0_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre0_tnr_fmt,cur0_tnr_fmt);
			if(pre0_tnr_fmt!=cur0_tnr_fmt)
			{
				switch(cur0_tnr_fmt)
				{
					case PE_NRD_H13A_TNR_SD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_sd_i_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_TNR_SD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_sd_p_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_TNR_HD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_hd_i_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_TNR_HD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_hd_p_l_default_h13a0,0);
						break;
					default:
						break;
				}
				pre0_tnr_fmt=cur0_tnr_fmt;
			}
			/* yc motion,motion_4f_en */
			yc_motion = ((cur0_inf->src_type==LX_PE_SRC_ATV||cur0_inf->src_type==LX_PE_SRC_CVBS) && \
						(cur0_inf->fmt_type==LX_PE_FMT_SECAM))? 0x0:0x1;
			/*m_4f_en = (cur0_inf->scan_type==LX_PE_SCAN_INTERLACE)? 0x1:0x0; --> move to default setting*/
			PE_P0L_H13_RdFL(p0l_tnr_ctrl_00);
			PE_P0L_H13_Wr01(p0l_tnr_ctrl_00, calc_motion_max_yc,	yc_motion);
			PE_P0L_H13_Wr01(p0l_tnr_ctrl_00, hist_motion_max_yc,	yc_motion);
			/*PE_P0L_H13_Wr01(p0l_tnr_ctrl_00, motion_4f_en,		m_4f_en);*/
			PE_P0L_H13_WrFL(p0l_tnr_ctrl_00);
			PE_NRD_HW_H13_DBG_PRINT("inf[0]src:%d,fmt:%d,scan:%d\n",\
				cur0_inf->src_type,cur0_inf->fmt_type,cur0_inf->scan_type);
			PE_NRD_HW_H13_DBG_PRINT("set[0]yc_motion:%d\n",yc_motion);
			/* fwi tnr ctrl */
			fwi_tnr.tnr_en = 1;
			fwi_tnr.m_fir_en = fwi_inf.tnr_ctrl[LX_PE_WIN_0].m_fir_en;
			/* sync with default, if sd or hd&interlace, turn on m_fir_en. otherwise,off */
			switch(cur0_inf->src_type)
			{
				case LX_PE_SRC_ATV:
				case LX_PE_SRC_CVBS:
					fwi_tnr.m_fir_en = 1;
					break;
				case LX_PE_SRC_COMP:
				case LX_PE_SRC_DTV:
				case LX_PE_SRC_HDMI:
				case LX_PE_SRC_PC:
				default:
					if(cur0_inf->fmt_type==LX_PE_FMT_SD)
					{
						fwi_tnr.m_fir_en = 1;
					}
					else
					{
						if(cur0_inf->scan_type==LX_PE_SCAN_INTERLACE)
							fwi_tnr.m_fir_en = 1;
						else
							fwi_tnr.m_fir_en = 0;
					}
					break;
			}
			ret = PE_FWI_H13_SetTnrCtrl(LX_PE_WIN_0,&fwi_tnr);
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetTnrCtrl() error.\n",__F__,__L__);
			PE_NRD_HW_H13_DBG_PRINT("set[0]tnr_en:%d,m_fir_en:%d\n",fwi_tnr.tnr_en,fwi_tnr.m_fir_en);
		}
		/* R : tnr */
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			cur1_tnr_fmt = PE_NRD_HW_H13A_ConvDispInfoToTnrFmt(cur1_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre1_tnr_fmt,cur1_tnr_fmt);
			if(pre1_tnr_fmt!=cur1_tnr_fmt)
			{
				switch(cur1_tnr_fmt)
				{
					case PE_NRD_H13A_TNR_SD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_sd_i_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_TNR_SD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_sd_p_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_TNR_HD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_hd_i_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_TNR_HD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,tnr_hd_p_r_default_h13a0,0);
						break;
					default:
						break;
				}
				pre1_tnr_fmt=cur1_tnr_fmt;
			}
			/* yc motion */
			yc_motion = ((cur1_inf->src_type==LX_PE_SRC_ATV||cur1_inf->src_type==LX_PE_SRC_CVBS) && \
						(cur1_inf->fmt_type==LX_PE_FMT_SECAM))? 0x0:0x1;
			/*m_4f_en = (cur1_inf->scan_type==LX_PE_SCAN_INTERLACE)? 0x1:0x0; --> move to default setting*/
			PE_P0R_H13_RdFL(p0r_tnr_ctrl_00);
			PE_P0R_H13_Wr01(p0r_tnr_ctrl_00, calc_motion_max_yc,	yc_motion);
			PE_P0R_H13_Wr01(p0r_tnr_ctrl_00, hist_motion_max_yc,	yc_motion);
			/*PE_P0R_H13_Wr01(p0r_tnr_ctrl_00, motion_4f_en,		m_4f_en);*/
			PE_P0R_H13_WrFL(p0r_tnr_ctrl_00);
			PE_NRD_HW_H13_DBG_PRINT("inf[1]src:%d,fmt:%d,scan:%d\n",\
				cur1_inf->src_type,cur1_inf->fmt_type,cur1_inf->scan_type);
			PE_NRD_HW_H13_DBG_PRINT("set[1]yc_motion:%d\n",yc_motion);
			/* fwi tnr ctrl */
			fwi_tnr.tnr_en = 1;
			fwi_tnr.m_fir_en = fwi_inf.tnr_ctrl[LX_PE_WIN_1].m_fir_en;
			/* sync with default, if sd or hd&interlace, turn on m_fir_en. otherwise,off */
			switch(cur1_inf->src_type)
			{
				case LX_PE_SRC_ATV:
				case LX_PE_SRC_CVBS:
					fwi_tnr.m_fir_en = 1;
					break;
				case LX_PE_SRC_COMP:
				case LX_PE_SRC_DTV:
				case LX_PE_SRC_HDMI:
				case LX_PE_SRC_PC:
				default:
					if(cur1_inf->fmt_type==LX_PE_FMT_SD)
					{
						fwi_tnr.m_fir_en = 1;
					}
					else
					{
						if(cur1_inf->scan_type==LX_PE_SCAN_INTERLACE)
							fwi_tnr.m_fir_en = 1;
						else
							fwi_tnr.m_fir_en = 0;
					}
					break;
			}
			ret = PE_FWI_H13_SetTnrCtrl(LX_PE_WIN_1,&fwi_tnr);
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetTnrCtrl() error.\n",__F__,__L__);
			PE_NRD_HW_H13_DBG_PRINT("set[1]tnr_en:%d,m_fir_en:%d\n",fwi_tnr.tnr_en,fwi_tnr.m_fir_en);
		}
		/* L : dnr */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_dnr_fmt = PE_NRD_HW_H13A_ConvDispInfoToDnrFmt(cur0_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre0_dnr_fmt,cur0_dnr_fmt);
			if(pre0_dnr_fmt!=cur0_dnr_fmt)
			{
				switch(cur0_dnr_fmt)
				{
					case PE_NRD_H13A_DNR_SD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_sd_i_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_SD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_sd_p_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_HD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_hd_i_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_HD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_hd_p_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_PC:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_pc_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_AV:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_av_l_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_DTV_SD:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_dtv_sd_l_default_h13a0,0);
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
			cur1_dnr_fmt = PE_NRD_HW_H13A_ConvDispInfoToDnrFmt(cur1_inf);
			PE_NRD_HW_H13_DBG_PRINT_FMT_STATE(pre1_dnr_fmt,cur1_dnr_fmt);
			if(pre1_dnr_fmt!=cur1_dnr_fmt)
			{
				switch(cur1_dnr_fmt)
				{
					case PE_NRD_H13A_DNR_SD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_sd_i_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_SD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_sd_p_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_HD_I:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_hd_i_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_HD_P:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_hd_p_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_PC:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_pc_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_AV:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_av_r_default_h13a0,0);
						break;
					case PE_NRD_H13A_DNR_DTV_SD:
						PE_SET_REG_TABLE(NRD_HW_H13,dnr_dtv_sd_r_default_h13a0,0);
						break;
					default:
						break;
				}
				pre1_dnr_fmt=cur1_dnr_fmt;
			}
		}
	}while(0);	
	return ret;
}
/**
 * get tnr fmt from display info.(for H13BX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_H13B_TNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_H13B_TNR_FMT PE_NRD_HW_H13B_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_H13B_TNR_FMT tnr_fmt = PE_NRD_H13B_TNR_NUM;
	if(disp_inf->out_type==LX_PE_OUT_UD)
	{
		tnr_fmt = PE_NRD_H13B_TNR_UD;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
				if(disp_inf->fmt_type==LX_PE_FMT_SECAM)
				{
					tnr_fmt = PE_NRD_H13B_TNR_ATV_SECAM;
				}
				else
				{
					tnr_fmt = PE_NRD_H13B_TNR_ATV;
				}
				break;
			case LX_PE_SRC_CVBS:
				if(disp_inf->fmt_type==LX_PE_FMT_SECAM)
				{
					tnr_fmt = PE_NRD_H13B_TNR_AV_SECAM;
				}
				else
				{
					tnr_fmt = PE_NRD_H13B_TNR_AV;
				}
				break;
			case LX_PE_SRC_DTV:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->dtv_type==LX_PE_DTV_HDDPLAY && (disp_inf->hdd_type==LX_PE_HDD_SRC_ATV60 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_ATV50 || disp_inf->hdd_type==LX_PE_HDD_SRC_AV60 || \
						disp_inf->hdd_type==LX_PE_HDD_SRC_AV50 || disp_inf->hdd_type==LX_PE_HDD_SRC_SCARTRGB))
					{
						if(disp_inf->hdd_type==LX_PE_HDD_SRC_ATV60 || disp_inf->hdd_type==LX_PE_HDD_SRC_ATV50)
						{
							tnr_fmt = PE_NRD_H13B_TNR_DVR_ATV;
						}
						else
						{
							tnr_fmt = PE_NRD_H13B_TNR_AV;
						}
					}
					else if(disp_inf->dtv_type==LX_PE_DTV_FILEPLAY && \
						(disp_inf->in_h_size<=PE_NRD_HW_H13_H_MIN && disp_inf->in_v_size<=PE_NRD_HW_H13_V_MIN))
					{
						tnr_fmt = PE_NRD_H13B_TNR_SD_MC_OFF;	//because of boundary noise on divx(<=352x288)
					}
					else
					{
						tnr_fmt = PE_NRD_H13B_TNR_SD;
					}
				}
				else
				{
					tnr_fmt = PE_NRD_H13B_TNR_HD;
				}
				break;
			case LX_PE_SRC_PC:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					tnr_fmt = PE_NRD_H13B_TNR_SD;
				}
				else
				{
					tnr_fmt = PE_NRD_H13B_TNR_HD;
				}
				break;
		}
	}
	return tnr_fmt;
}
/**
 * get dnr fmt from display info.(for H13BX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_H13B_DNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_H13B_DNR_FMT PE_NRD_HW_H13B_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_H13B_DNR_FMT dnr_fmt = PE_NRD_H13B_DNR_NUM;
	if(disp_inf->mode.is_tp)
	{
		dnr_fmt = PE_NRD_H13B_DNR_TP;
	}
	else
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
				{
					dnr_fmt = PE_NRD_H13B_DNR_SD;
				}
				break;
			case LX_PE_SRC_PC:
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					dnr_fmt = PE_NRD_H13B_DNR_SD;
				}
				else
				{
					dnr_fmt = PE_NRD_H13B_DNR_HD;
				}
				break;
		}
	}
	return dnr_fmt;
}
/**
 * get tnr fmt from display info.(for H13AX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_H13A_TNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_H13A_TNR_FMT PE_NRD_HW_H13A_ConvDispInfoToTnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_H13A_TNR_FMT tnr_fmt = PE_NRD_H13A_TNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
			{
				tnr_fmt = PE_NRD_H13A_TNR_SD_I;
			}
			break;
		case LX_PE_SRC_PC:
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					tnr_fmt = PE_NRD_H13A_TNR_SD_I;
				}
				else
				{
					tnr_fmt = PE_NRD_H13A_TNR_SD_P;
				}
			}
			else
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					tnr_fmt = PE_NRD_H13A_TNR_HD_I;
				}
				else
				{
					tnr_fmt = PE_NRD_H13A_TNR_HD_P;
				}
			}
			break;
	}
	return tnr_fmt;
}
/**
 * get dnr fmt from display info.(for H13AX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_NRD_HW_H13A_DNR_FMT
 * @see
 * @author
 */
static PE_NRD_HW_H13A_DNR_FMT PE_NRD_HW_H13A_ConvDispInfoToDnrFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_NRD_HW_H13A_DNR_FMT dnr_fmt = PE_NRD_H13A_DNR_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			{
				dnr_fmt = PE_NRD_H13A_DNR_SD_I;
			}
			break;
		case LX_PE_SRC_CVBS:
			{
				dnr_fmt = PE_NRD_H13A_DNR_AV;
			}
			break;
		case LX_PE_SRC_PC:
			{
				dnr_fmt = PE_NRD_H13A_DNR_PC;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				dnr_fmt = PE_NRD_H13A_DNR_DTV_SD;
			}
			else
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					dnr_fmt = PE_NRD_H13A_DNR_HD_I;
				}
				else
				{
					dnr_fmt = PE_NRD_H13A_DNR_HD_P;
				}
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					dnr_fmt = PE_NRD_H13A_DNR_SD_I;
				}
				else
				{
					dnr_fmt = PE_NRD_H13A_DNR_SD_P;
				}
			}
			else
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					dnr_fmt = PE_NRD_H13A_DNR_HD_I;
				}
				else
				{
					dnr_fmt = PE_NRD_H13A_DNR_HD_P;
				}
			}
			break;
	}
	return dnr_fmt;
}

/**
 * read nrd default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_NRD_HW_H13_RdDefault(LX_PE_ETC_DBG_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i,param_size,table_size,ofst;
	UINT32 *pData=NULL;
	PE_REG_PARAM_T *table=NULL;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		PE_NRD_HW_H13_CHECK_CODE(pstParams->size!=300,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		pData = pstParams->data;
		if(PE_KDRV_VER_H13BX)
		{
			ofst=0;
			if(pData[ofst]==0||pData[ofst]==1)	//tnr
			{
				table_size = sizeof(tnr_l_sd_default_h13b0);
				table = (PE_REG_PARAM_T *)OS_Malloc(table_size);
				param_size = table_size/sizeof(PE_REG_PARAM_T);
				for(i=0;i<param_size;i++)
				{
					table[i].addr = tnr_l_sd_default_h13b0[i].addr;
					if(pData[ofst]==1)	table[i].addr += PE_PE0_REG_H13_LRDIFF;
				}
			}
			else	//2,3 : dnr
			{
				table_size = sizeof(dnr_sd_l_default_h13b0);
				table = (PE_REG_PARAM_T *)OS_Malloc(table_size);
				param_size = table_size/sizeof(PE_REG_PARAM_T);
				for(i=0;i<param_size;i++)
				{
					table[i].addr = dnr_sd_l_default_h13b0[i].addr;
					if(pData[ofst]==3)	table[i].addr += PE_PE0_REG_H13_LRDIFF;
				}
			}
			ret = PE_REG_GetTable(table,0,table_size);
			PE_NRD_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
			ofst += 1;
			pData[ofst] = param_size;
			ofst += 1;
			for(i=0;i<param_size;i++)
			{
				pData[ofst+i*2]=table[i].addr;
				pData[ofst+i*2+1]=table[i].data;
			}
			ofst += 1;
		}
		else
		{
			PE_NRD_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	if(table){OS_Free(table);}\
	return ret;
}

