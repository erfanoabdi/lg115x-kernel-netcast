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


/** @file pe_cmn_hw_h13.c
 *
 *  driver for picture enhance common functions. ( used only within kdriver )
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
#include "pe_etc_hw.h"
#include "pe_cmn_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMN_HW_H13_ERROR	printk
#define PE_CMN_HW_H13_DBG_PRINT(fmt,args...)	\
	if(_g_cmn_hw_h13_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMN_HW_H13_CHECK_CODE(_checker,_action,fmt,args...)	\
	if(_checker){PE_CMN_HW_H13_ERROR(fmt,##args);_action;}

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
static UINT32 _g_cmn_hw_h13_trace=0x0;		//default should be off.
static PE_CMN_HW_H13_SETTINGS_T _g_pe_cmn_hw_h13_info;

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
void PE_CMN_HW_H13_SetDbgPrint(UINT32 on_off)
{
	_g_cmn_hw_h13_trace = on_off? 1:0;
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
int PE_CMN_HW_H13_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_H13BX)
		{
			memset0(_g_pe_cmn_hw_h13_info);
			PE_P1L_H13B0_QWr02(pe1_top_ctrl_00,			load_type,			0x0,\
														load_time,			0x0);
			PE_CMN_HW_H13_DBG_PRINT("vsp-yc,rgb : enable.\n");
			PE_P0L_H13B0_QWr04(p0l_lvcrtl_ctrl_00,		enable,				0x1,\
														y_offset,			0x200,\
														center_position,	0x80,\
														y_gain,				0x80);
			PE_P0R_H13B0_QWr04(p0r_lvcrtl_ctrl_00,		enable,				0x1,\
														y_offset,			0x200,\
														center_position,	0x80,\
														y_gain,				0x80);
			/* 20130104, sj.youm, vspyc center_position 0x0->0x10(related with 16~235 range) */
			PE_P1L_H13B0_QWr04(pe1_vspyc_ctrl_00,		enable,				0x1,\
														graycolor_enable,	0x0,\
														center_position,	0x10,\
														contrast,			0x200);
			PE_P1L_H13B0_QWr02(pe1_vspyc_ctrl_01,		saturation,			0x80,\
														brightness,			0x200);
		}	
		else if(PE_KDRV_VER_H13AX)
		{
			memset0(_g_pe_cmn_hw_h13_info);
			PE_P1L_H13_QWr02(pe1_top_ctrl_00,			load_type,			0x0,\
														load_time,			0x0);
			PE_CMN_HW_H13_DBG_PRINT("vsp-yc,rgb : enable.\n");
			PE_DPP_H13_QWr04(debd_pp_l_level_ctrl_00,	enable,				0x1,\
														y_offset,			0x200,\
														center_position,	0x80,\
														y_gain,				0x80);
			PE_DPP_H13_QWr04(debd_pp_l_vspyc_ctrl_00,	enable,				0x1,\
														graycolor_enable,	0x0,\
														center_position,	0x10,\
														contrast,			0x200);
			PE_DPP_H13_QWr02(debd_pp_l_vspyc_ctrl_01,	saturation,			0x80,\
														brightness,			0x200);
			PE_DPP_H13_QWr04(debd_pp_r_level_ctrl_00,	enable,				0x1,\
														y_offset,			0x200,\
														center_position,	0x80,\
														y_gain,				0x80);
			PE_DPP_H13_QWr04(debd_pp_r_vspyc_ctrl_00,	enable,				0x1,\
														graycolor_enable,	0x0,\
														center_position,	0x10,\
														contrast,			0x200);
			PE_DPP_H13_QWr02(debd_pp_r_vspyc_ctrl_01,	saturation,			0x80,\
														brightness,			0x200);
			
		}
		else
		{
			PE_CMN_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set pe cmn operation periodically
 *	- ud,3d mode on pe1 operation
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_H13_SetOperationMode(PE_TSK_H13_CFG_T *pCfg)
{
	int ret = RET_OK;
	PE_CMN_HW_H13_OPR_MODE_T cur_param;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_CMN_HW_H13_OPR_MODE_T *opr_info=&_g_pe_cmn_hw_h13_info.opr_inf;
	do {
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_H13BX)
		{
			/* pe1 ud mode */
			switch(disp0_info->out_type)
			{
				case LX_PE_OUT_UD:
					cur_param.pe1_mode_ud = 1;
					break;
				case LX_PE_OUT_2D:
				case LX_PE_OUT_3D_2D:
				case LX_PE_OUT_2D_3D:
				case LX_PE_OUT_TB:
				case LX_PE_OUT_SS:
				case LX_PE_OUT_PIP:
				case LX_PE_OUT_FS:
				case LX_PE_OUT_DUAL_TB:
				case LX_PE_OUT_DUAL_SS:
				case LX_PE_OUT_DUAL_FULL:
				default:
					cur_param.pe1_mode_ud = 0;
					break;
			}
			/* pe1 3d mode(interleaving) */
			if(disp0_info->mode.is_ext_frc)	/* external frc */
			{
				cur_param.pe1_mode_3d = 0;
			}
			else	/* internal frc */
			{
				switch(disp0_info->out_type)
				{
					case LX_PE_OUT_DUAL_TB:
					case LX_PE_OUT_DUAL_SS:
					case LX_PE_OUT_DUAL_FULL:
					case LX_PE_OUT_2D_3D:
						cur_param.pe1_mode_3d = 1;
						break;
					case LX_PE_OUT_2D:
					case LX_PE_OUT_3D_2D:
					case LX_PE_OUT_UD:
					case LX_PE_OUT_TB:
					case LX_PE_OUT_SS:
					case LX_PE_OUT_FS:
					case LX_PE_OUT_PIP:
					default:
						cur_param.pe1_mode_3d = 0;
						break;
				}
			}
			/* set pe1 top ctrl : ud,3d mode */
			if((opr_info->pe1_mode_ud != cur_param.pe1_mode_ud)|| \
				(opr_info->pe1_mode_3d != cur_param.pe1_mode_3d))
			{
				PE_CMN_HW_H13_DBG_PRINT("[inf]is_ext_frc:%d,out:%d\n",\
					disp0_info->mode.is_ext_frc,disp0_info->out_type);
				PE_CMN_HW_H13_DBG_PRINT("[set]ud,3d mode : prev:%d,%d, cur:%d,%d\n",\
					opr_info->pe1_mode_ud,opr_info->pe1_mode_3d,\
					cur_param.pe1_mode_ud,cur_param.pe1_mode_3d);
	            PE_P1L_H13B0_RdFL(pe1_top_ctrl_02);
	            PE_P1L_H13B0_Wr01(pe1_top_ctrl_02,	ud_mode,	cur_param.pe1_mode_ud);
	            PE_P1L_H13B0_Wr01(pe1_top_ctrl_02,	mode_3d,	cur_param.pe1_mode_3d);
				PE_P1L_H13B0_WrFL(pe1_top_ctrl_02);
				opr_info->pe1_mode_ud = cur_param.pe1_mode_ud;
				opr_info->pe1_mode_3d = cur_param.pe1_mode_3d;
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			/* pe1 ud mode */
			switch(disp0_info->out_type)
			{
				case LX_PE_OUT_UD:
					cur_param.pe1_mode_ud = 1;
					break;
				case LX_PE_OUT_2D:
				case LX_PE_OUT_3D_2D:
				case LX_PE_OUT_2D_3D:
				case LX_PE_OUT_TB:
				case LX_PE_OUT_SS:
				case LX_PE_OUT_PIP:
				case LX_PE_OUT_FS:
				case LX_PE_OUT_DUAL_TB:
				case LX_PE_OUT_DUAL_SS:
				case LX_PE_OUT_DUAL_FULL:
				default:
					cur_param.pe1_mode_ud = 0;
					break;
			}
			/* pe1 3d mode(interleaving) */
			if(disp0_info->mode.is_ext_frc)	/* external frc */
			{
				cur_param.pe1_mode_3d = 0;
			}
			else	/* internal frc */
			{
				switch(disp0_info->out_type)
				{
					case LX_PE_OUT_DUAL_TB:
					case LX_PE_OUT_DUAL_SS:
					case LX_PE_OUT_DUAL_FULL:
					case LX_PE_OUT_2D_3D:
						cur_param.pe1_mode_3d = 1;
						break;
					case LX_PE_OUT_2D:
					case LX_PE_OUT_3D_2D:
					case LX_PE_OUT_UD:
					case LX_PE_OUT_TB:
					case LX_PE_OUT_SS:
					case LX_PE_OUT_FS:
					case LX_PE_OUT_PIP:
					default:
						cur_param.pe1_mode_3d = 0;
						break;
				}
			}
			/* set pe1 top ctrl : ud,3d mode */
			if((opr_info->pe1_mode_ud != cur_param.pe1_mode_ud)|| \
				(opr_info->pe1_mode_3d != cur_param.pe1_mode_3d))
			{
				PE_CMN_HW_H13_DBG_PRINT("[inf]is_ext_frc:%d,out:%d\n",\
					disp0_info->mode.is_ext_frc,disp0_info->out_type);
				PE_CMN_HW_H13_DBG_PRINT("[set]ud,3d mode : prev:%d,%d, cur:%d,%d\n",\
					opr_info->pe1_mode_ud,opr_info->pe1_mode_3d,\
					cur_param.pe1_mode_ud,cur_param.pe1_mode_3d);
	            PE_P1L_H13_RdFL(pe1_top_ctrl_02);
	            PE_P1L_H13_Wr01(pe1_top_ctrl_02,	ud_mode,	cur_param.pe1_mode_ud);
	            PE_P1L_H13_Wr01(pe1_top_ctrl_02,	mode_3d,	cur_param.pe1_mode_3d);
				PE_P1L_H13_WrFL(pe1_top_ctrl_02);
				opr_info->pe1_mode_ud = cur_param.pe1_mode_ud;
				opr_info->pe1_mode_3d = cur_param.pe1_mode_3d;
			}
		}
		else
		{
			PE_CMN_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

