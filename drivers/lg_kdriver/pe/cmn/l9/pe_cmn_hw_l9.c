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


/** @file pe_cmn_hw_l9.c
 *
 *  driver for picture enhance common functions. ( used only within kdriver )
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
#include "pe_cmn_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMN_HW_L9_ERROR	printk

#define PE_CMN_HW_L9_DBG_PRINT(fmt,args...)	\
	if(_g_cmn_hw_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMN_HW_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_CMN_HW_L9_ERROR(fmt,##args);_action;}}

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
static UINT32 _g_cmn_hw_l9_trace=0x0;		//default should be off.
static PE_CMN_HW_L9_SETTINGS_T _g_pe_cmn_hw_l9_info;

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
void PE_CMN_HW_L9_SetDbgPrint(UINT32 on_off)
{
	_g_cmn_hw_l9_trace = on_off? 1:0;
	return;
}

/**
 * init cmn
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_L9_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			memset0(_g_pe_cmn_hw_l9_info);
			PE_P1L_L9B_QWr02(pe1_l_top_ctrl_00,		load_type,		0x0,\
													load_time,		0x0);
			PE_P1R_L9B_QWr02(pe1_r_top_ctrl_00,		load_type,		0x0,\
													load_time,		0x0);
			PE_CMN_HW_L9_DBG_PRINT("vsp-yc,rgb : enable.\n");
			PE_P1L_L9B_QWr04(pe1_l_level_ctrl_00,	enable,			0x1,\
													y_offset,		0x200,\
													center_position,0x80,\
													y_gain,			0x80);
			PE_P1L_L9B_QWr03(pe1_l_vspyc_ctrl_00,	enable,			0x1,\
													center_position,0x0,\
													contrast,		0x200);
			PE_P1L_L9B_QWr02(pe1_l_vspyc_ctrl_01,	saturation,		0x80,\
													brightness,		0x200);
			PE_P1L_L9B_QWr04(pe1_l_vsprgb_ctrl_00,	enable,			0x1,\
													contrast,		0x200,\
													center_position,0x0,\
													brightness,		0x200);
			PE_P1R_L9B_QWr04(pe1_r_level_ctrl_00,	enable,			0x1,\
													y_offset,		0x200,\
													center_position,0x80,\
													y_gain,			0x80);
			PE_P1R_L9B_QWr03(pe1_r_vspyc_ctrl_00,	enable,			0x1,\
													center_position,0x0,\
													contrast,		0x200);
			PE_P1R_L9B_QWr02(pe1_r_vspyc_ctrl_01,	saturation,		0x80,\
													brightness,		0x200);
			PE_P1R_L9B_QWr04(pe1_r_vsprgb_ctrl_00,	enable,			0x1,\
													contrast,		0x200,\
													center_position,0x0,\
													brightness,		0x200);
		}
		else
		{
			PE_CMN_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * set pe0 detour, work around for 444 mode line repeat
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_L9_SetFrontPeDetour(void)
{
	int ret = RET_OK;
	UINT32 l_data,r_data,detour_l_onoff,detour_r_onoff;
	static UINT32 count = 0;
	static UINT32 pre_l_data = 0xff;
	static UINT32 pre_r_data = 0xff;
	static UINT32 pre_detour_l_onoff = 0xff;
	static UINT32 pre_detour_r_onoff = 0xff;
	PE_CMN_HW_L9_SETTINGS_T *pInfo=&_g_pe_cmn_hw_l9_info;
	do{
		if(PE_KDRV_VER_L9BX)
		{				
			PE_P0L_L9B0_RdFL(pe0_opmode);
			PE_P0R_L9B0_RdFL(pe0_opmode);
			PE_P0L_L9B0_Rd01(pe0_opmode,	tnr_y_en,	l_data);
			PE_P0R_L9B0_Rd01(pe0_opmode,	tnr_y_en,	r_data);
			if(pre_l_data!=l_data)
			{
				if(l_data)	//use tnr memory
				{
					detour_l_onoff = 0x0;
				}
				else		//not use tnr memory
				{
					detour_l_onoff = 0x1;
				}
				pInfo->pe0_bypass[LX_PE_WIN_0] = detour_l_onoff;	//reset
				PE_CMN_HW_L9_DBG_PRINT("[CH L][new tnr_y_en]tnr_y_en:%d->%d, by_set:%d, detour_l_onoff:%d->%d\n\n",\
					pre_l_data,l_data,pInfo->pe0_bypass[LX_PE_WIN_0],pre_detour_l_onoff,detour_l_onoff);
				pre_l_data=l_data;
			}
			else
			{
				if(l_data)	//use tnr memory
				{
					detour_l_onoff = 0x0;
				}
				else		//not use tnr memory
				{
					detour_l_onoff = (pInfo->pe0_bypass[LX_PE_WIN_0])? 0x1:0x0;
				}
			}
			if(pre_detour_l_onoff != detour_l_onoff)
			{
				PE_P0L_L9B0_Wr01(pe0_opmode,	detour_enable,	detour_l_onoff);
				PE_P0L_L9B0_WrFL(pe0_opmode);
				PE_CMN_HW_L9_DBG_PRINT("[CH L][set detour]tnr_y_en:%d->%d, by_set:%d, detour_l_onoff:%d->%d\n\n",\
					pre_l_data,l_data,pInfo->pe0_bypass[LX_PE_WIN_0],pre_detour_l_onoff,detour_l_onoff);
				pre_detour_l_onoff = detour_l_onoff;
			}
			if(pre_r_data!=r_data)
			{
				if(r_data)	//use tnr memory
				{
					detour_r_onoff = 0x0;
				}
				else		//not use tnr memory
				{
					detour_r_onoff = 0x1;
				}
				pInfo->pe0_bypass[LX_PE_WIN_1] = detour_r_onoff;	//reset
				PE_CMN_HW_L9_DBG_PRINT("[CH R][new tnr_y_en]tnr_y_en:%d->%d, by_set:%d, detour_r_onoff:%d->%d\n\n",\
					pre_r_data,r_data,pInfo->pe0_bypass[LX_PE_WIN_1],pre_detour_r_onoff,detour_r_onoff);
				pre_r_data=r_data;
			}
			else
			{
				if(r_data)	//use tnr memory
				{
					detour_r_onoff = 0x0;
				}
				else		//not use tnr memory
				{
					detour_r_onoff = (pInfo->pe0_bypass[LX_PE_WIN_1])? 0x1:0x0;
				}
			}
			if(pre_detour_r_onoff != detour_r_onoff)
			{
				PE_P0R_L9B0_Wr01(pe0_opmode,	detour_enable,	detour_r_onoff);
				PE_P0R_L9B0_WrFL(pe0_opmode);
				PE_CMN_HW_L9_DBG_PRINT("[CH R][set detour]tnr_y_en:%d->%d, by_set:%d, detour_r_onoff:%d->%d\n\n",\
					pre_r_data,r_data,pInfo->pe0_bypass[LX_PE_WIN_1],pre_detour_r_onoff,detour_r_onoff);
				pre_detour_r_onoff = detour_r_onoff;
			}
			if(_g_cmn_hw_l9_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_CMN_HW_L9_DBG_PRINT("[CH L][monitoring]tnr_y_en:%d->%d, by_set:%d, detour_l_onoff:%d->%d\n",\
						pre_l_data,l_data,pInfo->pe0_bypass[LX_PE_WIN_0],pre_detour_l_onoff,detour_l_onoff);
					PE_CMN_HW_L9_DBG_PRINT("[CH R][monitoring]tnr_y_en:%d->%d, by_set:%d, detour_r_onoff:%d->%d\n\n",\
						pre_r_data,r_data,pInfo->pe0_bypass[LX_PE_WIN_1],pre_detour_r_onoff,detour_r_onoff);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_CMN_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set pic enhance bypass
 *
 * @param   on_off [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_L9_SetPeBypass(UINT32 on_off)
{
	int ret = RET_OK;
	PE_CMN_HW_L9_SETTINGS_T *pInfo=&_g_pe_cmn_hw_l9_info;
	do{
		PE_CMN_HW_L9_DBG_PRINT("set on_off : %d\n",on_off);
		if(PE_KDRV_VER_L9BX)
		{
			pInfo->pe0_bypass[LX_PE_WIN_0] = pInfo->pe0_bypass[LX_PE_WIN_1] = on_off;
		}
		else
		{
			PE_CMN_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set manual load mode
 *
 * @param   on_off [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_L9_SetManualLoadMode(UINT32 on_off)
{
	int ret = RET_OK;
	UINT32 cur_on;
	PE_INF_L9_SETTINGS_T inf_set;
	static UINT32 pre_on = 0x0;	//init by PE_CMN_Init()
	static UINT32 wb_gm_off = 0x0;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			ret = PE_INF_L9_GetCurInfSettings(&inf_set);
			PE_CMN_HW_L9_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
			if(inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_UD)
			{
				cur_on = on_off? 1:0;
			}
			else
			{
				cur_on = 0;	//off
			}
			PE_CMN_HW_L9_DBG_PRINT("out:%d,on_off:%d,on[pre:%d,cur:%d]\n",\
				inf_set.disp_info[LX_PE_WIN_0].out_type,on_off,pre_on,cur_on);
			if(pre_on!=cur_on)
			{
				if(cur_on && !wb_gm_off)
				{
					PE_P1L_L9B_QWr02(pe1_l_wb_ctrl_00,	degamma_en,		0x0,\
														gamma_en,		0x0);
					PE_P1R_L9B_QWr02(pe1_r_wb_ctrl_00,	degamma_en,		0x0,\
														gamma_en,		0x0);
					wb_gm_off = 0x1;
				}
				PE_CMN_HW_L9_DBG_PRINT("set cur_on:%d\n\n",cur_on);
				OS_MsecSleep(30);
				if(cur_on)
				{
					PE_P1R_L9B_QWr02(pe1_r_top_ctrl_00,	load_type,		0x1,\
														load_time,		0x1);
					PE_P1L_L9B_QWr02(pe1_l_top_ctrl_00,	load_type,		0x1,\
														load_time,		0x1);
				}
				else
				{
					PE_P1R_L9B_QWr02(pe1_r_top_ctrl_00,	load_type,		0x0,\
														load_time,		0x0);
					PE_P1L_L9B_QWr02(pe1_l_top_ctrl_00,	load_type,		0x0,\
														load_time,		0x0);
				}
				pre_on=cur_on;
				OS_MsecSleep(30);
			}
		}
		else
		{
			PE_CMN_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get cmn hw l9 settings
 *
 * @param   *pstParams [in] PE_CMN_HW_L9_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_L9_GetCurCmnSettings(PE_CMN_HW_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_HW_L9_SETTINGS_T *pInfo=&_g_pe_cmn_hw_l9_info;
	do{
		CHECK_KNULL(pstParams);
		memcpy(pstParams,pInfo,sizeof(PE_CMN_HW_L9_SETTINGS_T));
	}while(0);
	return ret;
}


