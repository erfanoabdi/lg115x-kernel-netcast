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


/** @file pe_dnt_hw_l9.c
 *
 *  driver for picture enhance deinterlacer functions. ( used only within kdriver )
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
#include "pe_etc_hw.h"
#include "pe_dnt_hw.h"
#include "pe_dnt_hw_l9a0.h"
#include "pe_dnt_hw_l9b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DNT_HW_L9_ERROR	printk

#define PE_DNT_HW_L9_DBG_PRINT(fmt,args...)	\
	if(_g_dnt_hw_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_DNT_HW_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_DNT_HW_L9_ERROR(fmt,##args);_action;}}
#define PE_DNT_HW_L9_DBG_PRINT_FMT_STATE(_pre,_cur)	\
	PE_DNT_HW_L9_DBG_PRINT("%s(%d),%s(%d) : %s.\n",\
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
static PE_DNT_HW_L9_IPC_FMT PE_DNT_HW_L9_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_DNT_HW_L9_FMD_FMT PE_DNT_HW_L9_ConvDispInfoToFmdFmt(LX_PE_INF_DISPLAY_T *disp_inf);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_dnt_hw_l9_trace=0x0;		//default should be off.

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
void PE_DNT_HW_L9_SetDbgPrint(UINT32 on_off)
{
	_g_dnt_hw_l9_trace = on_off? 1:0;
	return;
}
/**
 * init dnt
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_L9_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			PE_DNT_HW_L9_DBG_PRINT("init param.\n");
			PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_init_param_l9b0,0);
			PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_init_param_l9b0,0);
			PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fim_init_param_l9b0,0);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_DNT_HW_L9_DBG_PRINT("init param.\n");
			PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_init_param_l9a0,0);
			PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_init_param_l9a0,0);
		}
		else
		{
			PE_DNT_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);	
	return ret;
}
int PE_DNT_HW_L9_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_INF_L9_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_DNT_HW_L9_IPC_FMT cur0_ipc_fmt,cur1_ipc_fmt;
	PE_DNT_HW_L9_FMD_FMT cur0_fmd_fmt,cur1_fmd_fmt;
	static PE_DNT_HW_L9_IPC_FMT pre0_ipc_fmt = PE_DNT_L9_IPC_NUM;
	static PE_DNT_HW_L9_IPC_FMT pre1_ipc_fmt = PE_DNT_L9_IPC_NUM;
	static PE_DNT_HW_L9_FMD_FMT pre0_fmd_fmt = PE_DNT_L9_FMD_NUM;
	static PE_DNT_HW_L9_FMD_FMT pre1_fmd_fmt = PE_DNT_L9_FMD_NUM;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_L9_GetCurInfSettings(&inf_set);
		PE_DNT_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		if(PE_KDRV_VER_L9BX)
		{
			/* L : ipc,hmc */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_ipc_fmt = PE_DNT_HW_L9_ConvDispInfoToIpcFmt(cur0_inf);
				PE_DNT_HW_L9_DBG_PRINT_FMT_STATE(pre0_ipc_fmt,cur0_ipc_fmt);
				if(pre0_ipc_fmt!=cur0_ipc_fmt)
				{
					switch(cur0_ipc_fmt)
					{
						case PE_DNT_L9_IPC_ATV_NTSC:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_atv_ntsc_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_atv_ntsc_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_ATV_PAL:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_atv_pal_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_atv_pal_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_AV_NTSC:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_av_ntsc_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_av_ntsc_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_AV_PAL:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_av_ntsc_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_av_ntsc_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_DTV_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_dtv_atsc_sd_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_dtv_atsc_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_DTV_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_dtv_dvb_sd_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_dtv_dvb_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_HDMI_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_hdmi_atsc_sd_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_hdmi_atsc_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_HDMI_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_hdmi_pal_sd_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_hdmi_pal_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_HD:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_ipc_default_all_hd_param_l9b0,0);
							P0L_L9B0_DNT_SET_HMC(dnt_l_ipc_hmc_default_all_hd_param_l9b0[0]);
							break;
						default:
							break;
					}
					pre0_ipc_fmt=cur0_ipc_fmt;
				}
			}
			/* R : ipc,hmc */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_ipc_fmt = PE_DNT_HW_L9_ConvDispInfoToIpcFmt(cur1_inf);
				PE_DNT_HW_L9_DBG_PRINT_FMT_STATE(pre1_ipc_fmt,cur1_ipc_fmt);
				if(pre1_ipc_fmt!=cur1_ipc_fmt)
				{
					switch(cur1_ipc_fmt)
					{
						case PE_DNT_L9_IPC_ATV_NTSC:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_atv_ntsc_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_atv_ntsc_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_ATV_PAL:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_atv_pal_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_atv_pal_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_AV_NTSC:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_av_ntsc_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_av_ntsc_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_AV_PAL:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_av_ntsc_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_av_ntsc_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_DTV_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_dtv_atsc_sd_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_dtv_atsc_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_DTV_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_dtv_dvb_sd_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_dtv_dvb_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_HDMI_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_hdmi_atsc_sd_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_hdmi_atsc_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_HDMI_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_hdmi_pal_sd_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_hdmi_pal_sd_param_l9b0[0]);
							break;
						case PE_DNT_L9_IPC_HD:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_ipc_default_all_hd_param_l9b0,0);
							P0R_L9B0_DNT_SET_HMC(dnt_r_ipc_hmc_default_all_hd_param_l9b0[0]);
							break;
						default:
							break;
					}
					pre1_ipc_fmt=cur1_ipc_fmt;
				}
			}
			/* L : fmd */
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				cur0_fmd_fmt = PE_DNT_HW_L9_ConvDispInfoToFmdFmt(cur0_inf);
				PE_DNT_HW_L9_DBG_PRINT_FMT_STATE(pre0_fmd_fmt,cur0_fmd_fmt);
				if(pre0_fmd_fmt!=cur0_fmd_fmt)
				{
					switch(cur0_fmd_fmt)
					{
						case PE_DNT_L9_FMD_ATV_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_atv_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_ATV_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_atv_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_AV_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_av_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_AV_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_av_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_DTV_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_dtv_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_DTV_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_dtv_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_DTV_HD:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_dtv_hd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_HDMI_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_hdmi_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_HDMI_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_hdmi_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_HD:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_l_fmd_default_all_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre0_fmd_fmt=cur0_fmd_fmt;
				}
			}
			/* R : fmd */
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cur1_fmd_fmt = PE_DNT_HW_L9_ConvDispInfoToFmdFmt(cur1_inf);
				PE_DNT_HW_L9_DBG_PRINT_FMT_STATE(pre1_fmd_fmt,cur1_fmd_fmt);
				if(pre1_fmd_fmt!=cur1_fmd_fmt)
				{
					switch(cur1_fmd_fmt)
					{
						case PE_DNT_L9_FMD_ATV_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_atv_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_ATV_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_atv_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_AV_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_av_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_AV_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_av_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_DTV_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_dtv_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_DTV_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_dtv_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_DTV_HD:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_dtv_hd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_HDMI_SD_60:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_hdmi_60hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_HDMI_SD_50:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_hdmi_50hz_sd_param_l9b0,0);
							break;
						case PE_DNT_L9_FMD_HD:
							PE_SET_REG_TABLE(DNT_HW_L9,dnt_r_fmd_default_all_hd_param_l9b0,0);
							break;
						default:
							break;
					}
					pre1_fmd_fmt=cur1_fmd_fmt;
				}
			}
		}
		else
		{
			PE_DNT_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
static PE_DNT_HW_L9_IPC_FMT PE_DNT_HW_L9_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_L9_IPC_FMT ipc_fmt = PE_DNT_L9_IPC_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				ipc_fmt = PE_DNT_L9_IPC_ATV_NTSC;
			}
			else
			{
				ipc_fmt = PE_DNT_L9_IPC_ATV_PAL;
			}
			break;
		case LX_PE_SRC_CVBS:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				ipc_fmt = PE_DNT_L9_IPC_AV_NTSC;
			}
			else
			{
				ipc_fmt = PE_DNT_L9_IPC_AV_PAL;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					ipc_fmt = PE_DNT_L9_IPC_DTV_SD_60;
				}
				else
				{
					ipc_fmt = PE_DNT_L9_IPC_DTV_SD_50;
				}
			}
			else
			{
				ipc_fmt = PE_DNT_L9_IPC_HD;
			}
			break;
		case LX_PE_SRC_COMP:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				ipc_fmt = PE_DNT_L9_IPC_ATV_NTSC;
			}
			else	//hd
			{
				ipc_fmt = PE_DNT_L9_IPC_HD;
			}
			break;
		case LX_PE_SRC_PC:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					ipc_fmt = PE_DNT_L9_IPC_HDMI_SD_60;
				}
				else
				{
					ipc_fmt = PE_DNT_L9_IPC_HDMI_SD_50;
				}
			}
			else	//hd
			{
				ipc_fmt = PE_DNT_L9_IPC_HD;
			}
			break;
	}
	return ipc_fmt;
}
static PE_DNT_HW_L9_FMD_FMT PE_DNT_HW_L9_ConvDispInfoToFmdFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_L9_FMD_FMT fmd_fmt = PE_DNT_L9_FMD_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				fmd_fmt = PE_DNT_L9_FMD_ATV_60;
			}
			else
			{
				fmd_fmt = PE_DNT_L9_FMD_ATV_50;
			}
			break;
		case LX_PE_SRC_CVBS:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				fmd_fmt = PE_DNT_L9_FMD_AV_60;
			}
			else
			{
				fmd_fmt = PE_DNT_L9_FMD_AV_50;
			}
			break;
		case LX_PE_SRC_COMP:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					fmd_fmt = PE_DNT_L9_FMD_AV_60;
				}
				else
				{
					fmd_fmt = PE_DNT_L9_FMD_AV_50;
				}
			}
			else	//hd
			{
				fmd_fmt = PE_DNT_L9_FMD_HD;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					fmd_fmt = PE_DNT_L9_FMD_DTV_SD_60;
				}
				else
				{
					fmd_fmt = PE_DNT_L9_FMD_DTV_SD_50;
				}
			}
			else	//hd
			{
				fmd_fmt = PE_DNT_L9_FMD_DTV_HD;
			}
			break;
		case LX_PE_SRC_PC:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					fmd_fmt = PE_DNT_L9_FMD_HDMI_SD_60;
				}
				else
				{
					fmd_fmt = PE_DNT_L9_FMD_HDMI_SD_50;
				}
			}
			else	//hd
			{
				fmd_fmt = PE_DNT_L9_FMD_HD;
			}
			break;
	}
	return fmd_fmt;
}

