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


/** @file pe_ccm_hw_l9.c
 *
 *  driver for picture enhance color correction module functions. ( used only within kdriver )
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

#include "de_cfg_def.h"
#include "de_cfg_l9.h"
#include "de_cfg.h"

#include "pe_cfg.h"
#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc_hw.h"
#include "pe_ccm_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 20120521, sj.youm, preventing ddr gmc settings error on UD model */
#define PE_CCM_HW_L9_NEW_SET_GMC_BY_DDR

#define PE1_L9_L_TOP_CTRL_00_OFFSET	0x1300
#define PE1_L9_L_GMC_CTRL_02_OFFSET	0x16f8
#define PE1_L9_L_GMC_IA_CTRL_OFFSET	0x16fc
#define PE1_L9_L_GMC_IA_DATA_OFFSET	0x1700

#define PE1_L9_R_TOP_CTRL_00_OFFSET	0x3300
#define PE1_L9_R_GMC_CTRL_02_OFFSET	0x36f8
#define PE1_L9_R_GMC_IA_CTRL_OFFSET	0x36fc
#define PE1_L9_R_GMC_IA_DATA_OFFSET	0x3700

#define PE_CCM_HW_L9_SAT_STATUS_TH	200
#define PE_CCM_HW_L9_LRCR_GAIN		0xa

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CCM_HW_L9_ERROR	printk

#define PE_CCM_HW_L9_DBG_PRINT(fmt,args...)	\
	if(_g_ccm_hw_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CCM_HW_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_CCM_HW_L9_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	data_cnt                        :14,	//  0:13
	                                : 2,	// 14:15 reserved
	block_mode                      : 2,	// 16:17
	                                : 2,	// 18:19 reserved
	auto_inc                        : 1,	//    20
	                                :10,	// 21:30 reserved
	last_block                      : 1;	//    31
} VIDEO_L9_DDR_BLOCK_HEAD_T;

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
static UINT32 _g_ccm_hw_l9_trace=0x0;		//default should be off.

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
void PE_CCM_HW_L9_SetDbgPrint(UINT32 on_off)
{
	_g_ccm_hw_l9_trace = on_off? 1:0;
	return;
}

/**
 * init ccm
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_L9_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			PE_CCM_HW_L9_DBG_PRINT("init wb.\n");
			PE_P1L_L9B_QWr03(pe1_l_wb_ctrl_00,	wb_en, 				0x1,\
												degamma_en, 		0x1,\
												gamma_en, 			0x1);
			PE_P1L_L9B_QWr03(pe1_l_wb_ctrl_01,	user_ctrl_g_gain,	0xc0,\
												user_ctrl_b_gain,	0xc0,\
												user_ctrl_r_gain,	0xc0);
			PE_P1L_L9B_QWr03(pe1_l_wb_ctrl_02,	user_ctrl_g_offset,	0x80,\
												user_ctrl_b_offset,	0x80,\
												user_ctrl_r_offset,	0x80);

			PE_P1R_L9B_QWr03(pe1_r_wb_ctrl_00,	wb_en, 				0x1,\
												degamma_en, 		0x1,\
												gamma_en, 			0x1);
			PE_P1R_L9B_QWr03(pe1_r_wb_ctrl_01,	user_ctrl_g_gain,	0xc0,\
												user_ctrl_b_gain,	0xc0,\
												user_ctrl_r_gain,	0xc0);
			PE_P1R_L9B_QWr03(pe1_r_wb_ctrl_02,	user_ctrl_g_offset,	0x80,\
												user_ctrl_b_offset,	0x80,\
												user_ctrl_r_offset,	0x80);

			PE_CCM_HW_L9_DBG_PRINT("init gmc.\n");
			PE_P1L_L9B_QWr07(pe1_l_gmc_ctrl_00, pxl_rep_enable,		0x0,\
												pxl_rep_area,		0x0,\
												pxl_rep_disable_r,	0x1,\
												pxl_rep_disable_g,	0x1,\
												pxl_rep_disable_b,	0x1,\
												pxl_rep_xpos,		0x0,\
												pxl_rep_ypos,		0x0);
			PE_P1L_L9B_QWr02(pe1_l_gmc_ctrl_01, pxl_rep_width,		0x780,\
												pxl_rep_height,		0x438);
			PE_P1L_L9B_QWr03(pe1_l_gmc_ctrl_02, pxl_rep_value_g,	0x0,\
												pxl_rep_value_b,	0x0,\
												pxl_rep_value_r,	0x0);

			PE_P1R_L9B_QWr07(pe1_r_gmc_ctrl_00, pxl_rep_enable,		0x0,\
												pxl_rep_area,		0x0,\
												pxl_rep_disable_r,	0x1,\
												pxl_rep_disable_g,	0x1,\
												pxl_rep_disable_b,	0x1,\
												pxl_rep_xpos,		0x0,\
												pxl_rep_ypos,		0x0);
			PE_P1R_L9B_QWr02(pe1_r_gmc_ctrl_01, pxl_rep_width,		0x780,\
												pxl_rep_height,		0x438);
			PE_P1R_L9B_QWr03(pe1_r_gmc_ctrl_02, pxl_rep_value_g,	0x0,\
												pxl_rep_value_b,	0x0,\
												pxl_rep_value_r,	0x0);

			PE_CCM_HW_L9_DBG_PRINT("init lrcr config.\n");
			PE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,enable,				0x0);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,adjust_en,			0x1);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,protection_en,		0x1);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,adjust_en2,			0x1);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,r_hist_data_sel,	0x1);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,l_hist_data_sel,	0x0);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,r_proc_data_sel,	0x1);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,l_proc_data_sel,	0x0);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,ff_mode_en,			0x0);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,ff_mode_parity,		0x0);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,r_out_data_sel,		0x1);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,l_out_data_sel,		0x0);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,reg_lrcr_gain,		PE_CCM_HW_L9_LRCR_GAIN);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,hist_rd_en,			0x0);
			PE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00,hist_mode,			0x0);	//256 bin
			PE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);

			PE_P1L_L9B_QWr04(pe1_l_lrcr_ctrl_01,th_max_hist,		0xe0,\
												th_valid_bins,		0x40,\
												th1,				0xe0,\
												th0,				0x4);
			PE_P1L_L9B_QWr04(pe1_l_lrcr_ctrl_02,hist_l_window_h_bbd,0x0,\
												hist_l_window_h_en,	0x1,\
												hist_l_window_v_bbd,0x0,\
												hist_l_window_v_en,	0x1);
			PE_P1L_L9B_QWr04(pe1_l_lrcr_ctrl_04,hist_r_window_h_bbd,0x0,\
												hist_r_window_h_en,	0x1,\
												hist_r_window_v_bbd,0x0,\
												hist_r_window_v_en,	0x1);
			PE_P1L_L9B_QWr04(pe1_l_lrcr_ctrl_06,active_window_h_bbd,0x0,\
												active_window_h_en,	0x1,\
												active_window_v_bbd,0x0,\
												active_window_v_en,	0x1);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_CCM_HW_L9_DBG_PRINT("init wb.\n");
			PE_P1L_L9_RdFL(pe1_l_wb_ctrl_00);
			PE_P1L_L9_RdFL(pe1_l_wb_ctrl_02);
			PE_P1L_L9_RdFL(pe1_l_wb_ctrl_03);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, wb_en, 				0x1);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, degamma_en, 			0x1);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, gamma_en, 				0x1);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_02, user_ctrl_g_gain,		0xc0);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_02, user_ctrl_b_gain,		0xc0);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_02, user_ctrl_r_gain,		0xc0);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_03, user_ctrl_g_offset,	0x80);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_03, user_ctrl_b_offset,	0x80);
			PE_P1L_L9_Wr01(pe1_l_wb_ctrl_03, user_ctrl_r_offset,	0x80);
			PE_P1L_L9_WrFL(pe1_l_wb_ctrl_00);
			PE_P1L_L9_WrFL(pe1_l_wb_ctrl_02);
			PE_P1L_L9_WrFL(pe1_l_wb_ctrl_03);

			PE_P1R_L9_RdFL(pe1_r_wb_ctrl_00);
			PE_P1R_L9_RdFL(pe1_r_wb_ctrl_02);
			PE_P1R_L9_RdFL(pe1_r_wb_ctrl_03);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, wb_en, 				0x1);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, degamma_en, 			0x1);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, gamma_en, 				0x1);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_02, user_ctrl_g_gain,		0xc0);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_02, user_ctrl_b_gain,		0xc0);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_02, user_ctrl_r_gain,		0xc0);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_03, user_ctrl_g_offset,	0x80);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_03, user_ctrl_b_offset,	0x80);
			PE_P1R_L9_Wr01(pe1_r_wb_ctrl_03, user_ctrl_r_offset,	0x80);
			PE_P1R_L9_WrFL(pe1_r_wb_ctrl_00);
			PE_P1R_L9_WrFL(pe1_r_wb_ctrl_02);
			PE_P1R_L9_WrFL(pe1_r_wb_ctrl_03);

			PE_CCM_HW_L9_DBG_PRINT("init gmc.\n");
			PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_00);
			PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_01);
			PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_02);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_enable,		0x0);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_area,			0x0); // 0:inside,1: outside
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_r,	0x1);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_g,	0x1);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_b,	0x1);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_xpos,			0x0);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_ypos,			0x0);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_01, pxl_rep_width,		0x780);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_01, pxl_rep_height,		0x438);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02, pxl_rep_value_g,		0x0);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02, pxl_rep_value_b,		0x0);
			PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02, pxl_rep_value_r,		0x0);
			PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_00);
			PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_01);
			PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_02);

			PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_00);
			PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_01);
			PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_02);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_enable,		0x0);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_area,			0x0); // 0:inside,1: outside
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_r,	0x1);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_g,	0x1);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_b,	0x1);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_xpos,			0x0);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_ypos,			0x0);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_01, pxl_rep_width,		0x780);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_01, pxl_rep_height,		0x438);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02, pxl_rep_value_g,		0x0);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02, pxl_rep_value_b,		0x0);
			PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02, pxl_rep_value_r,		0x0);
			PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_00);
			PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_01);
			PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_02);
		}
		else
		{
			PE_CCM_HW_L9_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);

	return ret;
}

/**
 * ccm Debug bypass setting
 *
 * @param   *pstParams [in/out] LX_PE_DBG_SETTINGS_T int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_L9_SetDebugBypassSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		if(PE_KDRV_VER_L9BX)
		{
			if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CCM)))
			{
				PE_CCM_HW_L9_DBG_PRINT("wb,degamma,gamma,pxl_rep_en : disable.\n");
				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					PE_P1L_L9B0_RdFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_00,	wb_en, 			0x0);
					PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_00, 	degamma_en, 	0x0);
					PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_00, 	gamma_en, 		0x0);
					PE_P1L_L9B0_WrFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_enable,	0x0);
					PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_02);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02, gmc_mode,		0x0);//read mode
					PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
				}
				if(PE_CHECK_WIN1(pstParams->win_id))
				{
					PE_P1R_L9B0_RdFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_00, 	wb_en, 			0x0);
					PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_00, 	degamma_en, 	0x0);
					PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_00, 	gamma_en, 		0x0);
					PE_P1R_L9B0_WrFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_enable,	0x0);
					PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_02);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02, gmc_mode,		0x0);//read mode
					PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
				}
			}
			else
			{
				PE_CCM_HW_L9_DBG_PRINT("wb,degamma,gamma,pxl_rep_en,pxl_rep_dis : enable.\n");
				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					PE_P1L_L9B0_RdFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_00, 	wb_en, 			0x1);
					PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_00, 	degamma_en, 	0x1);
					PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_00, 	gamma_en, 		0x1);
					PE_P1L_L9B0_WrFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_enable,	0x1);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_r,0x1);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_g,0x1);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_b,0x1);
					PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_02);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02, gmc_mode,		0x2);//normal mode
					PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
				}
				if(PE_CHECK_WIN1(pstParams->win_id))
				{
					PE_P1R_L9B0_RdFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_00, 	wb_en, 			0x1);
					PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_00, 	degamma_en, 	0x1);
					PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_00, 	gamma_en, 		0x1);
					PE_P1R_L9B0_WrFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_enable,	0x1);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_r,0x1);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_g,0x1);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_b,0x1);
					PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_02);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02, gmc_mode,		0x2);//normal mode
					PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
				}
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CCM)))
			{
				PE_CCM_HW_L9_DBG_PRINT("wb,degamma,gamma,pxl_rep_en : disable.\n");
				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					PE_P1L_L9_RdFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, 	wb_en, 			0x0);
					PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, 	degamma_en, 	0x0);
					PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, 	gamma_en, 		0x0);
					PE_P1L_L9_WrFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, 	pxl_rep_enable,	0x0);
					PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_02);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02, 	gmc_mode,		0x0);//read mode
					PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_02);
				}
				if(PE_CHECK_WIN1(pstParams->win_id))
				{
					PE_P1R_L9_RdFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, 	wb_en, 			0x0);
					PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, 	degamma_en, 	0x0);
					PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, 	gamma_en, 		0x0);
					PE_P1R_L9_WrFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, 	pxl_rep_enable,	0x0);
					PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_02);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02, 	gmc_mode,		0x0);//read mode
					PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_02);
				}
			}
			else
			{
				PE_CCM_HW_L9_DBG_PRINT("wb,degamma,gamma,pxl_rep_en,pxl_rep_dis : enable.\n");
				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					PE_P1L_L9_RdFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, 	wb_en, 			0x1);
					PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, 	degamma_en, 	0x1);
					PE_P1L_L9_Wr01(pe1_l_wb_ctrl_00, 	gamma_en, 		0x1);
					PE_P1L_L9_WrFL(pe1_l_wb_ctrl_00);
					PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, 	pxl_rep_enable,	0x1);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, 	pxl_rep_disable_r,0x1);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, 	pxl_rep_disable_g,0x1);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, 	pxl_rep_disable_b,0x1);
					PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_00);
					PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_02);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02, 	gmc_mode,		0x2);//normal mode
					PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_02);
				}
				if(PE_CHECK_WIN1(pstParams->win_id))
				{
					PE_P1R_L9_RdFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, 	wb_en, 			0x1);
					PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, 	degamma_en, 	0x1);
					PE_P1R_L9_Wr01(pe1_r_wb_ctrl_00, 	gamma_en, 		0x1);
					PE_P1R_L9_WrFL(pe1_r_wb_ctrl_00);
					PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, 	pxl_rep_enable,	0x1);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, 	pxl_rep_disable_r,0x1);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, 	pxl_rep_disable_g,0x1);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, 	pxl_rep_disable_b,0x1);
					PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_00);
					PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_02);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02, 	gmc_mode,		0x2);//normal mode
					PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_02);
				}
			}
		}
		else
		{
			PE_CCM_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set pixel replacement
 *
 * @param   *pstParams [in/out] LX_PE_CCM_PIXEL_REPLACE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_L9_SetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams)
{
	int ret = RET_OK;
	UINT32 pxl_en,r_rep_off,g_rep_off,b_rep_off;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_HW_L9_DBG_PRINT("set[%d] : r:%d,g:%d,b:%d\n",pstParams->win_id,\
			pstParams->pxl_rep_r,pstParams->pxl_rep_g,pstParams->pxl_rep_b);
		r_rep_off = (pstParams->pxl_rep_r)? 0x0:0x1;
		g_rep_off = (pstParams->pxl_rep_g)? 0x0:0x1;
		b_rep_off = (pstParams->pxl_rep_b)? 0x0:0x1;
		pxl_en = (pstParams->pxl_rep_r | pstParams->pxl_rep_g | pstParams->pxl_rep_b)? 0x1:0x0;
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_enable,		pxl_en);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_00);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_00);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_enable,		pxl_en);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_00);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_00);
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_enable,		pxl_en);
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
				PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_00);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_00);
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_enable,		pxl_en);
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
				PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_00);
			}
		}
		else
		{
			PE_CCM_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);

	return ret;
}
/**
 * get pixel replacement
 *
 * @param   *pstParams [in/out] LX_PE_CCM_PIXEL_REPLACE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_L9_GetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 r_rep_off=1,g_rep_off=1,b_rep_off=1;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_00);
				PE_P1L_L9B0_Rd01(pe1_l_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1L_L9B0_Rd01(pe1_l_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1L_L9B0_Rd01(pe1_l_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_00);
				PE_P1R_L9B0_Rd01(pe1_r_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1R_L9B0_Rd01(pe1_r_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1R_L9B0_Rd01(pe1_r_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_00);
				PE_P1L_L9_Rd01(pe1_l_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1L_L9_Rd01(pe1_l_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1L_L9_Rd01(pe1_l_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_00);
				PE_P1R_L9_Rd01(pe1_r_gmc_ctrl_00, pxl_rep_disable_r,	r_rep_off);
				PE_P1R_L9_Rd01(pe1_r_gmc_ctrl_00, pxl_rep_disable_g,	g_rep_off);
				PE_P1R_L9_Rd01(pe1_r_gmc_ctrl_00, pxl_rep_disable_b,	b_rep_off);
			}
		}
		else
		{
			PE_CCM_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		pstParams->pxl_rep_r = (r_rep_off)? 0x0:0x1;
		pstParams->pxl_rep_g = (g_rep_off)? 0x0:0x1;
		pstParams->pxl_rep_b = (b_rep_off)? 0x0:0x1;
		PE_CCM_HW_L9_DBG_PRINT("get[%d] : r:%d,g:%d,b:%d\n",pstParams->win_id,\
			pstParams->pxl_rep_r,pstParams->pxl_rep_g,pstParams->pxl_rep_b);
	}while(0);
	return ret;
}
/**
 * set auto correction gain, work around for lrcr error
 *
 * @param   *pCfg [in] PE_TSK_L9_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_L9_SetAutoCrGain(PE_TSK_L9_CFG_T *pCfg)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	UINT32 lrcr_gain = 0xff;
	PE_INF_L9_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	static UINT32 prev_lrcr_gain = 0xff;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_L9BX)
		{
			if(ctrl0_info->auto_cr_en && ctrl0_info->d3d_chk && \
				ctrl0_info->sat_status>PE_CCM_HW_L9_SAT_STATUS_TH)
			{
				lrcr_gain = 0x0;
			}
			else
			{
				lrcr_gain = PE_CCM_HW_L9_LRCR_GAIN;
			}
			if(prev_lrcr_gain!=lrcr_gain)
			{
				PE_P1L_L9B_QWr01(pe1_l_lrcr_ctrl_00,reg_lrcr_gain,		lrcr_gain);
				PE_CCM_HW_L9_DBG_PRINT("set gain : pre:0x%x -> cur:0x%x, en:%d,chk:%d,s_st:%d\n\n",\
					prev_lrcr_gain,lrcr_gain,ctrl0_info->auto_cr_en,ctrl0_info->d3d_chk,\
					ctrl0_info->sat_status);
				prev_lrcr_gain=lrcr_gain;
			}
			if(_g_ccm_hw_l9_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_CCM_HW_L9_DBG_PRINT("state : cur_gain:0x%x, en:%d,chk:%d,s_st:%d\n\n",\
						lrcr_gain,ctrl0_info->auto_cr_en,ctrl0_info->d3d_chk,\
						ctrl0_info->sat_status);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_CCM_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * set gamma correction lut by ddr
 *
 * @param   *pstParams [in] LX_PE_CCM_GAMMALUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_L9_SetGammaLutByDdr(LX_PE_CCM_GAMMALUT_T *pstParams)
{
	int ret = RET_OK;
	VIDEO_L9_DDR_BLOCK_HEAD_T gammaLutHead = {0};
	LX_DE_CH_MEM_T	*pFwMem      = NULL;
	UINT32          *lpDdrUpAddr = NULL;
	UINT32 			ddrUpAddr;
	UINT32 			regUpAddr;
	UINT32 			ddrStride = 512;
	int i;
	int ddrUpCount;
	PE_CCM_HW_L9_DBG_PRINT("set pstParams[%d] : lut_size:%d\n",pstParams->win_id, pstParams->size);
	do {
		if(PE_KDRV_VER_L9BX)
		{
			ddrUpCount = 0;
			CHECK_KNULL(pstParams);
			CHECK_KNULL(pstParams->data);
			if(!pstParams->size) break;
	        pFwMem = &gpDeMem->fw[2];
	        CHECK_KNULL(pFwMem);
			ddrUpAddr = pFwMem->fw_base + CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP);
	        lpDdrUpAddr = (UINT32 *)ioremap(ddrUpAddr, CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP));
			ddrUpAddr &= 0x0fffffff;
			ddrUpAddr |= 0x80000000;
	        CHECK_KNULL(lpDdrUpAddr);
			switch(pstParams->win_id)
			{
				case LX_PE_WIN_0 :
					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 6;

					PE_P1L_L9B0_RdFL(pe1_l_top_ctrl_00);
					PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_02);
					PE_P1L_L9B0_RdFL(pe1_l_gmc_ia_ctrl);
					PE_P1L_L9B0_Wr01(pe1_l_top_ctrl_00,	load_time,	  0x1);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	  0x1);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,	  0x1);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr, 0x0);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_top_ctrl_00;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_IA_CTRL_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_gmc_ia_ctrl;

					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 1;
					gammaLutHead.data_cnt   = pstParams->size + 1;

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_IA_DATA_OFFSET;
					for (i=0;i<pstParams->size;i++) lpDdrUpAddr[ddrUpCount++] = pstParams->data[i];

					gammaLutHead.last_block = 1;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 4;

					PE_P1L_L9B0_Wr01(pe1_l_top_ctrl_00,	load_time,	0x0);
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	0x2);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_top_ctrl_00;

					regUpAddr = (0x4 << 29) | GET_PVAL(ddrUpAddr, 11, 18);
					PE_MIB_L9B0_RdFL(mifb_saddr_param_update0_m);
					PE_MIB_L9B0_Wr01(mifb_saddr_param_update0_m, register_update_address0_m, GET_BITS(regUpAddr, 11, 21));
					PE_MIB_L9B0_Wr01(mifb_saddr_param_update0_m, load, 					 0x1);
					PE_MIB_L9B0_WrFL(mifb_saddr_param_update0_m);

					PE_OVL_L9B0_RdFL(ovl_ov_param_by_ddr);
					PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, update_by_ddr,     1);
					PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, endian_conversion, 0x0);
					PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, vsize,             (ddrUpCount * sizeof(UINT32) + ddrStride - 1)/ddrStride);
					PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, stride,            GET_BITS(ddrStride, 9, 2));
					PE_OVL_L9B0_WrFL(ovl_ov_param_by_ddr);
					break;

				case LX_PE_WIN_1 :
					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 6;

					PE_P1R_L9B0_RdFL(pe1_r_top_ctrl_00);
					PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_02);
					PE_P1R_L9B0_RdFL(pe1_r_gmc_ia_ctrl);
					PE_P1R_L9B0_Wr01(pe1_r_top_ctrl_00,	load_time,	  0x1);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	  0x1);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,	  0x1);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr, 0x0);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_top_ctrl_00;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_IA_CTRL_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_gmc_ia_ctrl;

					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 1;
					gammaLutHead.data_cnt   = pstParams->size + 1;

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_IA_DATA_OFFSET;
					for (i=0;i<pstParams->size;i++) lpDdrUpAddr[ddrUpCount++] = pstParams->data[i];

					gammaLutHead.last_block = 1;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 4;

					PE_P1R_L9B0_Wr01(pe1_r_top_ctrl_00,	load_time,	0x0);
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	0x2);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_top_ctrl_00;

					regUpAddr = (0x4 << 29) | GET_PVAL(ddrUpAddr, 11, 18);
					PE_MID_L9B0_RdFL(mifd_saddr_param_update0_m);
					PE_MID_L9B0_Wr01(mifd_saddr_param_update0_m, register_update_address0_m, GET_BITS(regUpAddr, 11, 21));
					PE_MID_L9B0_Wr01(mifd_saddr_param_update0_m, load, 					 0x1);
					PE_MID_L9B0_WrFL(mifd_saddr_param_update0_m);

					PE_OVR_L9B0_RdFL(ovr_ov_param_by_ddr);
					PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, update_by_ddr,     1);
					PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, endian_conversion, 0x0);
					PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, vsize,             (ddrUpCount * sizeof(UINT32) + ddrStride - 1)/ddrStride);
					PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, stride,            GET_BITS(ddrStride, 9, 2));
					PE_OVR_L9B0_WrFL(ovr_ov_param_by_ddr);
					break;

				default :
					BREAK_WRONG(pstParams->win_id);
			}
			if(lpDdrUpAddr) iounmap((void*)lpDdrUpAddr);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			ddrUpCount = 0;
			CHECK_KNULL(pstParams);
			CHECK_KNULL(pstParams->data);
			if(!pstParams->size) break;
	        pFwMem = &gpDeMem->fw[2];
	        CHECK_KNULL(pFwMem);
			ddrUpAddr = pFwMem->fw_base + CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP);
	        lpDdrUpAddr = (UINT32 *)ioremap(ddrUpAddr, CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP));
			ddrUpAddr &= 0x0fffffff;
			ddrUpAddr |= 0x80000000;
	        CHECK_KNULL(lpDdrUpAddr);
			switch(pstParams->win_id)
			{
				case LX_PE_WIN_0 :
					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 6;

					PE_P1L_L9_RdFL(pe1_l_top_ctrl_00);
					PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_02);
					PE_P1L_L9_RdFL(pe1_l_gmc_ia_ctrl);
					PE_P1L_L9_Wr01(pe1_l_top_ctrl_00,	load_time,	  0x1);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	  0x1);
					PE_P1L_L9_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,	  0x1);
					PE_P1L_L9_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr, 0x0);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9.shdw.a0->pe1_l_top_ctrl_00;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9.shdw.a0->pe1_l_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_IA_CTRL_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9.shdw.a0->pe1_l_gmc_ia_ctrl;

					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 1;
					gammaLutHead.data_cnt   = pstParams->size + 1;

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_IA_DATA_OFFSET;
					for (i=0;i<pstParams->size;i++) lpDdrUpAddr[ddrUpCount++] = pstParams->data[i];

					gammaLutHead.last_block = 1;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 4;

					PE_P1L_L9_Wr01(pe1_l_top_ctrl_00,	load_time,	0x0);
					PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	0x2);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9.shdw.a0->pe1_l_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_L_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1L_L9.shdw.a0->pe1_l_top_ctrl_00;

					regUpAddr = (0x4 << 29) | GET_PVAL(ddrUpAddr, 11, 18);
					PE_MIB_L9_RdFL(mifb_saddr_param_update0_m);
					PE_MIB_L9_Wr01(mifb_saddr_param_update0_m, register_update_address0_m, GET_BITS(regUpAddr, 11, 21));
					PE_MIB_L9_Wr01(mifb_saddr_param_update0_m, load, 					 0x1);
					PE_MIB_L9_WrFL(mifb_saddr_param_update0_m);

					PE_OVL_L9_RdFL(ovl_ov_param_by_ddr);
					PE_OVL_L9_Wr01(ovl_ov_param_by_ddr, update_by_ddr,     1);
					PE_OVL_L9_Wr01(ovl_ov_param_by_ddr, endian_conversion, 0x0);
					PE_OVL_L9_Wr01(ovl_ov_param_by_ddr, vsize,             (ddrUpCount * sizeof(UINT32) + ddrStride - 1)/ddrStride);
					PE_OVL_L9_Wr01(ovl_ov_param_by_ddr, stride,            GET_BITS(ddrStride, 9, 2));
					PE_OVL_L9_WrFL(ovl_ov_param_by_ddr);
					break;

				case LX_PE_WIN_1 :
					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 6;

					PE_P1R_L9_RdFL(pe1_r_top_ctrl_00);
					PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_02);
					PE_P1R_L9_RdFL(pe1_r_gmc_ia_ctrl);
					PE_P1R_L9_Wr01(pe1_r_top_ctrl_00,	load_time,	  0x1);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	  0x1);
					PE_P1R_L9_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,	  0x1);
					PE_P1R_L9_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr, 0x0);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9.shdw.a0->pe1_r_top_ctrl_00;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9.shdw.a0->pe1_r_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_IA_CTRL_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9.shdw.a0->pe1_r_gmc_ia_ctrl;

					gammaLutHead.last_block = 0;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 1;
					gammaLutHead.data_cnt   = pstParams->size + 1;

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_IA_DATA_OFFSET;
					for (i=0;i<pstParams->size;i++) lpDdrUpAddr[ddrUpCount++] = pstParams->data[i];

					gammaLutHead.last_block = 1;
					gammaLutHead.auto_inc   = 0;
					gammaLutHead.block_mode = 0;
					gammaLutHead.data_cnt   = 4;

					PE_P1R_L9_Wr01(pe1_r_top_ctrl_00,	load_time,	0x0);
					PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	0x2);

					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gammaLutHead;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_GMC_CTRL_02_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9.shdw.a0->pe1_r_gmc_ctrl_02;
					lpDdrUpAddr[ddrUpCount++] =  PE1_L9_R_TOP_CTRL_00_OFFSET;
					lpDdrUpAddr[ddrUpCount++] = *(UINT32 *)&gPE_P1R_L9.shdw.a0->pe1_r_top_ctrl_00;

					regUpAddr = (0x4 << 29) | GET_PVAL(ddrUpAddr, 11, 18);
					PE_MID_L9_RdFL(mifd_saddr_param_update0_m);
					PE_MID_L9_Wr01(mifd_saddr_param_update0_m, register_update_address0_m, GET_BITS(regUpAddr, 11, 21));
					PE_MID_L9_Wr01(mifd_saddr_param_update0_m, load, 					 0x1);
					PE_MID_L9_WrFL(mifd_saddr_param_update0_m);

					PE_OVR_L9_RdFL(ovr_ov_param_by_ddr);
					PE_OVR_L9_Wr01(ovr_ov_param_by_ddr, update_by_ddr,     1);
					PE_OVR_L9_Wr01(ovr_ov_param_by_ddr, endian_conversion, 0x0);
					PE_OVR_L9_Wr01(ovr_ov_param_by_ddr, vsize,             (ddrUpCount * sizeof(UINT32) + ddrStride - 1)/ddrStride);
					PE_OVR_L9_Wr01(ovr_ov_param_by_ddr, stride,            GET_BITS(ddrStride, 9, 2));
					PE_OVR_L9_WrFL(ovr_ov_param_by_ddr);
					break;

				default :
					BREAK_WRONG(pstParams->win_id);
			}
			if(lpDdrUpAddr) iounmap((void*)lpDdrUpAddr);
		}
		else
		{
			PE_CCM_HW_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set gamma correction lut by ddr for all window
 *
 * @param   *pstParams [in] LX_PE_CCM_GAMMALUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_HW_L9_SetAllGammaLutByDdr(LX_PE_CCM_GAMMALUT_T *pstParams)
{
	int ret = RET_OK;
	VIDEO_L9_DDR_BLOCK_HEAD_T gammaLutHead_l = {0};
	VIDEO_L9_DDR_BLOCK_HEAD_T gammaLutHead_r = {0};
	LX_DE_CH_MEM_T	*pFwMem      = NULL;
	UINT32          *lpDdrUpAddr_l = NULL;
	UINT32          *lpDdrUpAddr_r = NULL;
	UINT32 			ddrUpAddr_l=0,ddrUpAddr_r=0;
	UINT32 			regUpAddr_l,regUpAddr_r;
	UINT32 			ddrStride = 512;
	int i;
	int ddrUpCount_l=0,ddrUpCount_r=0;
	do {
		if(PE_KDRV_VER_L9BX)
		{
			CHECK_KNULL(pstParams);
			CHECK_KNULL(pstParams->data);
			PE_CCM_HW_L9_DBG_PRINT("set pstParams[%d] : size:%d\n",pstParams->win_id, pstParams->size);
			if(!pstParams->size) break;
	        pFwMem = &gpDeMem->fw[2];
	        CHECK_KNULL(pFwMem);
			#ifndef PE_CCM_HW_L9_NEW_SET_GMC_BY_DDR
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				ddrUpAddr_l = pFwMem->fw_base + CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP);
		        lpDdrUpAddr_l = (UINT32 *)ioremap(ddrUpAddr_l, CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP));
				ddrUpAddr_l &= 0x0fffffff;
				ddrUpAddr_l |= 0x80000000;
				CHECK_KNULL(lpDdrUpAddr_l);
				gammaLutHead_l.last_block = 0;
				gammaLutHead_l.auto_inc   = 0;
				gammaLutHead_l.block_mode = 0;
				gammaLutHead_l.data_cnt   = 6;
				PE_P1L_L9B0_RdFL(pe1_l_top_ctrl_00);
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ia_ctrl);
				//PE_P1L_L9B0_Wr01(pe1_l_top_ctrl_00,	load_time,	  0x1);
				//PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	  0x1);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,	  0x1);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr, 0x0);
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gammaLutHead_l;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_TOP_CTRL_00_OFFSET;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_top_ctrl_00;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_GMC_CTRL_02_OFFSET;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_gmc_ctrl_02;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_GMC_IA_CTRL_OFFSET;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_gmc_ia_ctrl;
				gammaLutHead_l.last_block = 0;
				gammaLutHead_l.auto_inc   = 0;
				gammaLutHead_l.block_mode = 1;
				gammaLutHead_l.data_cnt   = pstParams->size + 1;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gammaLutHead_l;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_GMC_IA_DATA_OFFSET;
				for (i=0;i<pstParams->size;i++) lpDdrUpAddr_l[ddrUpCount_l++] = pstParams->data[i];
				gammaLutHead_l.last_block = 1;
				gammaLutHead_l.auto_inc   = 0;
				gammaLutHead_l.block_mode = 0;
				gammaLutHead_l.data_cnt   = 4;
				//PE_P1L_L9B0_Wr01(pe1_l_top_ctrl_00,	load_time,	0x0);
				//PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	0x2);
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gammaLutHead_l;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_GMC_CTRL_02_OFFSET;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_gmc_ctrl_02;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_TOP_CTRL_00_OFFSET;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_top_ctrl_00;
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				ddrUpAddr_r = pFwMem->fw_base + CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP)+(2048)*sizeof(UINT32);
		        lpDdrUpAddr_r = (UINT32 *)ioremap(ddrUpAddr_r, CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP));
				ddrUpAddr_r &= 0x0fffffff;
				ddrUpAddr_r |= 0x80000000;
		        CHECK_KNULL(lpDdrUpAddr_r);
				gammaLutHead_r.last_block = 0;
				gammaLutHead_r.auto_inc   = 0;
				gammaLutHead_r.block_mode = 0;
				gammaLutHead_r.data_cnt   = 6;
				PE_P1R_L9B0_RdFL(pe1_r_top_ctrl_00);
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ia_ctrl);
				//PE_P1R_L9B0_Wr01(pe1_r_top_ctrl_00,	load_time,	  0x1);
				//PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	  0x1);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,	  0x1);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr, 0x0);
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gammaLutHead_r;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_TOP_CTRL_00_OFFSET;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_top_ctrl_00;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_GMC_CTRL_02_OFFSET;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_gmc_ctrl_02;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_GMC_IA_CTRL_OFFSET;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_gmc_ia_ctrl;
				gammaLutHead_r.last_block = 0;
				gammaLutHead_r.auto_inc   = 0;
				gammaLutHead_r.block_mode = 1;
				gammaLutHead_r.data_cnt   = pstParams->size + 1;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gammaLutHead_r;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_GMC_IA_DATA_OFFSET;
				for (i=0;i<pstParams->size;i++) lpDdrUpAddr_r[ddrUpCount_r++] = pstParams->data[i];
				gammaLutHead_r.last_block = 1;
				gammaLutHead_r.auto_inc   = 0;
				gammaLutHead_r.block_mode = 0;
				gammaLutHead_r.data_cnt   = 4;
				//PE_P1R_L9B0_Wr01(pe1_r_top_ctrl_00,	load_time,	0x0);
				//PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	0x2);
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gammaLutHead_r;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_GMC_CTRL_02_OFFSET;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_gmc_ctrl_02;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_TOP_CTRL_00_OFFSET;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_top_ctrl_00;
			}
			#else
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				ddrUpAddr_l = pFwMem->fw_base + CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP);
		        lpDdrUpAddr_l = (UINT32 *)ioremap(ddrUpAddr_l, CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP));
				ddrUpAddr_l &= 0x0fffffff;
				ddrUpAddr_l |= 0x80000000;
				CHECK_KNULL(lpDdrUpAddr_l);
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_02);
				gammaLutHead_l.last_block = 0;
				gammaLutHead_l.auto_inc   = 0;
				gammaLutHead_l.block_mode = 1;
				gammaLutHead_l.data_cnt   = pstParams->size + 1;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gammaLutHead_l;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_GMC_IA_DATA_OFFSET;
				for (i=0;i<pstParams->size;i++) lpDdrUpAddr_l[ddrUpCount_l++] = pstParams->data[i];
				gammaLutHead_l.last_block = 1;
				gammaLutHead_l.auto_inc   = 0;
				gammaLutHead_l.block_mode = 0;
				gammaLutHead_l.data_cnt   = 2;
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	0x2);
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gammaLutHead_l;
				lpDdrUpAddr_l[ddrUpCount_l++] =  PE1_L9_L_GMC_CTRL_02_OFFSET;
				lpDdrUpAddr_l[ddrUpCount_l++] = *(UINT32 *)&gPE_P1L_L9B.shdw.b0->pe1_l_gmc_ctrl_02;
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				ddrUpAddr_r = pFwMem->fw_base + CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_OFST_DDR_UP)+(2048)*sizeof(UINT32);
		        lpDdrUpAddr_r = (UINT32 *)ioremap(ddrUpAddr_r, CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_SIZE_DDR_UP));
				ddrUpAddr_r &= 0x0fffffff;
				ddrUpAddr_r |= 0x80000000;
		        CHECK_KNULL(lpDdrUpAddr_r);
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_02);
				gammaLutHead_r.last_block = 0;
				gammaLutHead_r.auto_inc   = 0;
				gammaLutHead_r.block_mode = 1;
				gammaLutHead_r.data_cnt   = pstParams->size + 1;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gammaLutHead_r;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_GMC_IA_DATA_OFFSET;
				for (i=0;i<pstParams->size;i++) lpDdrUpAddr_r[ddrUpCount_r++] = pstParams->data[i];
				gammaLutHead_r.last_block = 1;
				gammaLutHead_r.auto_inc   = 0;
				gammaLutHead_r.block_mode = 0;
				gammaLutHead_r.data_cnt   = 2;
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	0x2);
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gammaLutHead_r;
				lpDdrUpAddr_r[ddrUpCount_r++] =  PE1_L9_R_GMC_CTRL_02_OFFSET;
				lpDdrUpAddr_r[ddrUpCount_r++] = *(UINT32 *)&gPE_P1R_L9B.shdw.b0->pe1_r_gmc_ctrl_02;
			}
			#endif
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				regUpAddr_l = (0x4 << 29) | GET_PVAL(ddrUpAddr_l, 11, 18);
				PE_MIB_L9B0_RdFL(mifb_saddr_param_update0_m);
				PE_MIB_L9B0_Wr01(mifb_saddr_param_update0_m, register_update_address0_m, GET_BITS(regUpAddr_l, 11, 21));
				PE_MIB_L9B0_Wr01(mifb_saddr_param_update0_m, load, 					 0x1);
				PE_MIB_L9B0_WrFL(mifb_saddr_param_update0_m);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				regUpAddr_r = (0x4 << 29) | GET_PVAL(ddrUpAddr_r, 11, 18);
				PE_MID_L9B0_RdFL(mifd_saddr_param_update0_m);
				PE_MID_L9B0_Wr01(mifd_saddr_param_update0_m, register_update_address0_m, GET_BITS(regUpAddr_r, 11, 21));
				PE_MID_L9B0_Wr01(mifd_saddr_param_update0_m, load, 					 0x1);
				PE_MID_L9B0_WrFL(mifd_saddr_param_update0_m);
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_CCM_HW_L9_NEW_SET_GMC_BY_DDR
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ia_ctrl);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,	  0x1);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr, 0x0);
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ia_ctrl);
				#endif
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	  0x1);	//wr mode
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				#ifdef PE_CCM_HW_L9_NEW_SET_GMC_BY_DDR
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ia_ctrl);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,	  0x1);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr, 0x0);
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ia_ctrl);
				#endif
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	  0x1);	//wr mode
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_OVL_L9B0_RdFL(ovl_ov_param_by_ddr);
				PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, update_by_ddr,     1);
				PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, endian_conversion, 0x0);
				PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, vsize,             (ddrUpCount_l * sizeof(UINT32) + ddrStride - 1)/ddrStride);
				PE_OVL_L9B0_Wr01(ovl_ov_param_by_ddr, stride,            GET_BITS(ddrStride, 9, 2));
				PE_OVL_L9B0_WrFL(ovl_ov_param_by_ddr);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_OVR_L9B0_RdFL(ovr_ov_param_by_ddr);
				PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, update_by_ddr,     1);
				PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, endian_conversion, 0x0);
				PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, vsize,             (ddrUpCount_r * sizeof(UINT32) + ddrStride - 1)/ddrStride);
				PE_OVR_L9B0_Wr01(ovr_ov_param_by_ddr, stride,            GET_BITS(ddrStride, 9, 2));
				PE_OVR_L9B0_WrFL(ovr_ov_param_by_ddr);
			}
			#ifndef PE_CCM_HW_L9_NEW_SET_GMC_BY_DDR
			OS_MsecSleep(30);	// delay for L,R sync
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,	  0x2);	//normal mode
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,	  0x2);	//normal mode
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
			}
			#endif
		}
		else
		{
			PE_CCM_HW_L9_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	if(lpDdrUpAddr_l) iounmap((void*)lpDdrUpAddr_l);
	if(lpDdrUpAddr_r) iounmap((void*)lpDdrUpAddr_r);
	return ret;
}

