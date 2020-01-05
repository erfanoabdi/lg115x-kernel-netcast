/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		won.hur
 *  @version	1.0
 *  @date		2011-08-19
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/uaccess.h>
#include <linux/irq.h>
#include "cvd_hw.h"
#include "afe_drv.h"
#include "linux/delay.h"

#include "ctop_regs.h"
#include "./../../afe/l9/vport_reg_l9b0.h"
#include "os_util.h"
//#include "pe_reg.h"
#include "de_pe0_reg_l9.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/
#define STANDARD_CDTO_INC_VALUE  0x21F07C1F

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/
#define VPORT_REG_DIRECT_ACCESS 0
#define	HSTART_SHIFT_DUE_TO_DE_CROP_WORKAROUND	1

// CVD Memory Map ( Base Addr:0x7bb00000, End Addr:0x7befffff, Addr Size:0x00400000)
#define CVD_BASE_ADDR	0x7BB00000

//#define L9_SLOW_AGC_WORKAROUND
//#define L9_USE_SYNCTIP_ONLY_MODE
#define USE_NEW_GATE_VALUES

#define L9_CVD_INIT_OADJ_C 	// 2012.02.24 won.hur

//#define CVD_REG_SATURATION_ADJUST
#define CVD_REG_OADJ_C_COEFF_ADJUST
/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/
// shadow register
extern volatile VPORT_L9B0_REG_T __iomem *gpRegVPORT_L9B0;
// real
extern volatile VPORT_L9B0_REG_T __iomem *gpRealRegVPORT_L9B0;

// shadow register
//extern volatile CHBCVD_L9_REG_T __iomem *gpRegCHBCVD_L9;
// real
//extern volatile CHBCVD_L9_REG_T __iomem *gpRealRegCHBCVD_L9;

extern DE_P0L_REG_L9B_T gDE_P0L_L9B;



//extern CVD_STATE_T	Current_State;
//extern CVD_STATE_T	Next_State;
extern int main_timer_state;
extern int chb_timer_state;

extern int gEnableScartFB;
//extern BOOLEAN g_CVD_RF_Input_Mode;
extern CVD_ADAPTIVE_PEAK_NOMINAL_CONTROL_T g_CVD_AGC_Peak_Nominal_Control ;
extern CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;
extern CVD_STATUS_3CS_T	g_CVD_Status_3CS ;
/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/

#ifdef L9_CVD_INIT_OADJ_C
static UINT32 g_initial_c_coeff = 0x1050;
#else
static UINT32 g_initial_c_coeff = 0;
#endif

/*========================================================================================
  Implementation Group
  ========================================================================================*/
int CVD_L9Bx_ClampAGC_OnOff(UINT8 on_off)
{
	//JUHEE : no more supported in L9
#if 0
	if(on_off)
	{
		VPORT_L9B0_RdFL(iris_099);
		VPORT_L9B0_Wr01(iris_099, cvd_cvd1_clampagc_on, 0x1);
		VPORT_L9B0_WrFL(iris_099);
	}
	else
	{
		VPORT_L9B0_RdFL(iris_099);
		VPORT_L9B0_Wr01(iris_099, cvd_cvd1_clampagc_on, 0x0);
		VPORT_L9B0_WrFL(iris_099);
	}
#endif
	return 0;
}

int CVD_L9Bx_Clamp_Current_Control(UINT8 value)
{
	if(value <= 0x3)
	{
		VPORT_I2C_Read((UINT32*)&gafe_cvbs_2_bx);
		gafe_cvbs_2_bx.cvbs_icon = value;
		VPORT_I2C_Write((UINT32*)&gafe_cvbs_2_bx);
		return 0;
	}
	return -1;
}

int CVD_L9Bx_Force_Color_Kill(UINT8 color_kill_enable)
{
	if(color_kill_enable)
	{
		VPORT_L9B0_RdFL(iris_095);
		VPORT_L9B0_Wr01(iris_095, reg_ckill, 0x0);
		VPORT_L9B0_WrFL(iris_095);
	}
	else
	{
		VPORT_L9B0_RdFL(iris_095);
		VPORT_L9B0_Wr01(iris_095, reg_ckill, 0x1c00);
		VPORT_L9B0_WrFL(iris_095);
	}
	return 0;
}

/* From L8B0 below Set_Picture_Enhancement function is not used */

void CVD_L9Bx_Set_Picture_Enhancement(BOOLEAN ycrdc_lcr_on, BOOLEAN cyrdc_lcr_on)
{


// Message from won.hur(won.hur@lge.com) @2011.08.22
// From L9A0 register header file, registers  related to "2dcomb" has been deleted!!
// So I will disable the code...
#if 0 // disabled by  won.hur

  Annotated by won.hur@2011.08.22
	CVD_DEBUG("Picture Enhancement Register Setting\n");
	VPORT_L9B0_RdFL(iris_155);
	VPORT_L9B0_Wr06(iris_155, cvd_2dcomb_byp, 0x0, cvd_2dcomb_cband_sel, 0x0, cvd_2dcomb_ccombo_sel, 0x0 , cvd_2dcomb_ycrdc_cvsel, 0x1, cvd_2dcomb_ycrdc_chsel, 0x0, cvd_2dcomb_ycrdc_lrsel, 0x1);
	VPORT_L9B0_WrFL(iris_155);
	VPORT_L9B0_RdFL(iris_156);
	VPORT_L9B0_Wr03(iris_156, cvd_2dcomb_divider_th, 0x2, cvd_2dcomb_ycrdc_yhsymth, 0x20, cvd_2dcomb_ycrdc_yhdiffth, 0x10);
	VPORT_L9B0_WrFL(iris_156);
	VPORT_L9B0_RdFL(iris_157);
	VPORT_L9B0_Wr01(iris_157, cvd_2dcomb_ycrdc_cvdiffth, 0x40);
	VPORT_L9B0_WrFL(iris_157);
	VPORT_L9B0_RdFL(iris_160);
	VPORT_L9B0_Wr05(iris_160, cvd_2dcomb_ycrdc_yvsel, 0x2, cvd_2dcomb_ycrdc_yhsel, 0xE, cvd_2dcomb_ycrdc_hth_on, 0x1, cvd_2dcomb_ycrdc_hth_sel, 0x2, cvd_2dcomb_ycrdc_hth, 0x40);
	VPORT_L9B0_WrFL(iris_160);
	VPORT_L9B0_RdFL(iris_158);
	VPORT_L9B0_Wr03(iris_158, cvd_2dcomb_ycrdc_lrtype, 0x0, cvd_2dcomb_ycrdc_dsel, 0x0, cvd_2dcomb_ycrdc_method, 0x0);
	VPORT_L9B0_WrFL(iris_158);
	if(ycrdc_lcr_on)
	{
		VPORT_L9B0_RdFL(iris_158);
		VPORT_L9B0_Wr01(iris_158, cvd_2dcomb_ycrdc_lcr_on, 0x7);
		VPORT_L9B0_WrFL(iris_158);
	}
	else
	{
		VPORT_L9B0_RdFL(iris_158);
		VPORT_L9B0_Wr01(iris_158, cvd_2dcomb_ycrdc_lcr_on, 0x0);
		VPORT_L9B0_WrFL(iris_158);
	}
#else	// won.hur
	return;
#endif // won.hur



}

void CVD_L9Bx_Program_Color_System_Main_cdto_only(CVD_SET_SYSTEM_MAIN_T *pSet_system_t)
{
	VPORT_L9B0_RdFL(iris_012);
	VPORT_L9B0_Wr03(iris_012, reg_colour_mode, pSet_system_t->reg_colour_mode, reg_vline_625, pSet_system_t->reg_vline_625, reg_hpixel, pSet_system_t->reg_hpixel);
	VPORT_L9B0_WrFL(iris_012);
	VPORT_L9B0_RdFL(iris_013);
	VPORT_L9B0_Wr01(iris_013, reg_ped, pSet_system_t->reg_ped);
	VPORT_L9B0_WrFL(iris_013);
	VPORT_L9B0_RdFL(iris_095);
	VPORT_L9B0_Wr02(iris_095, reg_cagc_gate_start, pSet_system_t->reg_cagc_gate_start, reg_cagc_gate_end, pSet_system_t->reg_cagc_gate_end);
	VPORT_L9B0_WrFL(iris_095);
	VPORT_L9B0_RdFL(iris_028);
	VPORT_L9B0_Wr01(iris_028, reg_cdto_inc, pSet_system_t->reg_cdto_inc);
	VPORT_L9B0_WrFL(iris_028);
	VPORT_L9B0_RdFL(iris_064);
	VPORT_L9B0_Wr01(iris_064, reg_md_noise_th, pSet_system_t->reg_md_noise_th);
	VPORT_L9B0_WrFL(iris_064);
}


// This Function's alogorithm must be modified!!
// L9A1->IRIS_158(2dcomb releated register) has been deleted on L9B0!
// See line 365!!
// It is rapped-up with conditional-compile-macro
void CVD_L9Bx_Program_Color_System_Main_Multi(CVD_SET_SYSTEM_MAIN_T *pSet_system_t)
{
	VPORT_L9B0_RdFL(iris_mif_gmua_001);
	VPORT_L9B0_Wr01(iris_mif_gmua_001, reg_comb3_buffer_size, pSet_system_t->reg_comb3_buffer_size_L9Bx);
	VPORT_L9B0_WrFL(iris_mif_gmua_001);
	VPORT_L9B0_RdFL(iris_mif_gmua_002);
	VPORT_L9B0_Wr01(iris_mif_gmua_002, reg_fld1_init_rd_pel, pSet_system_t->reg_fld1_init_rd_pel_L9Bx);
	VPORT_L9B0_WrFL(iris_mif_gmua_002);
	VPORT_L9B0_RdFL(iris_mif_gmua_003);
	VPORT_L9B0_Wr01(iris_mif_gmua_003, reg_fld2_init_rd_pel, pSet_system_t->reg_fld2_init_rd_pel_L9Bx);
	VPORT_L9B0_WrFL(iris_mif_gmua_003);
	VPORT_L9B0_RdFL(iris_mif_gmua_004);
	VPORT_L9B0_Wr01(iris_mif_gmua_004, reg_fld3_init_rd_pel, pSet_system_t->reg_fld3_init_rd_pel_L9Bx);
	VPORT_L9B0_WrFL(iris_mif_gmua_004);
	VPORT_L9B0_RdFL(iris_mif_gmua_005);
	VPORT_L9B0_Wr01(iris_mif_gmua_005, reg_fld4_init_rd_pel, pSet_system_t->reg_fld4_init_rd_pel_L9Bx);
	VPORT_L9B0_WrFL(iris_mif_gmua_005);


	// by Kim.min 2010/06/03
	VPORT_L9B0_RdFL(iris_012);
	VPORT_L9B0_Wr03(iris_012, reg_colour_mode, pSet_system_t->reg_colour_mode, reg_vline_625, pSet_system_t->reg_vline_625, reg_hpixel, pSet_system_t->reg_hpixel);
	VPORT_L9B0_WrFL(iris_012);
	VPORT_L9B0_RdFL(iris_013);
	VPORT_L9B0_Wr01(iris_013, reg_ped, pSet_system_t->reg_ped);
	VPORT_L9B0_WrFL(iris_013);
	//added 110411 by kim.min
	VPORT_L9B0_RdFL(iris_130);
	VPORT_L9B0_Wr01(iris_130, reg_adc_blank_level, pSet_system_t->reg_adc_blank_level);
	VPORT_L9B0_WrFL(iris_130);
	VPORT_L9B0_RdFL(iris_014);
	//110817 moved agc_half_en, dagc_en, dc_clamp_mode, mv_hagc_mode, hagc_field_mode to Reg_Init Function
	VPORT_L9B0_Wr02(iris_014, reg_hagc_en, pSet_system_t->reg_hagc_en, reg_cagc_en, pSet_system_t->reg_cagc_en );
	//VPORT_L9B0_Wr07(iris_014, reg_hagc_en, pSet_system_t->reg_hagc_en, reg_cagc_en, pSet_system_t->reg_cagc_en, reg_agc_half_en, pSet_system_t->reg_agc_half_en, reg_dagc_en, pSet_system_t->reg_dagc_en, reg_dc_clamp_mode, pSet_system_t->reg_dc_clamp_mode, reg_mv_hagc_mode, pSet_system_t->reg_mv_hagc_mode, reg_hagc_field_mode, pSet_system_t->reg_hagc_field_mode);
	VPORT_L9B0_WrFL(iris_014);
	/*
	   // moved to CVD PE
	VPORT_L9B0_RdFL(iris_013);
	VPORT_L9B0_Wr01(iris_013, reg_chroma_bw_lo, pSet_system_t->reg_chroma_bw_lo);
	VPORT_L9B0_WrFL(iris_013);
	*/

	/*		110828 L9 B0 N/A
	VPORT_L9B0_RdFL(iris_015);
	VPORT_L9B0_Wr02(iris_015, reg_adaptive_mode, pSet_system_t->reg_adaptive_mode, reg_adaptive_3dcomb_mode, pSet_system_t->reg_adaptive_3dcomb_mode);
	VPORT_L9B0_WrFL(iris_015);
	*/

	VPORT_L9B0_RdFL(iris_016);
	VPORT_L9B0_Wr01(iris_016, reg_hagc, pSet_system_t->reg_hagc);
	VPORT_L9B0_WrFL(iris_016);
	VPORT_L9B0_RdFL(iris_018);
	VPORT_L9B0_Wr01(iris_018, reg_adc_updn_swap, pSet_system_t->reg_adc_updn_swap);
	VPORT_L9B0_WrFL(iris_018);
	//yc_delay setting is moved to CVD PQ
	//gVportRegBx->iris_019.reg_yc_delay = pSet_system_t->reg_yc_delay;
	//VPORT_L9B0_RdFL(iris_019);
	//VPORT_L9B0_Wr01(iris_019, reg_yc_delay, pSet_system_t->reg_yc_delay);
	//VPORT_L9B0_WrFL(iris_019);
	// need Reg debug
	//
	VPORT_L9B0_RdFL(iris_095);
#ifdef USE_NEW_GATE_VALUES
	VPORT_L9B0_Wr02(iris_095, reg_cagc_gate_start, pSet_system_t->reg_cagc_gate_start_new, reg_cagc_gate_end, pSet_system_t->reg_cagc_gate_end_new);
#else
	VPORT_L9B0_Wr02(iris_095, reg_cagc_gate_start, pSet_system_t->reg_cagc_gate_start, reg_cagc_gate_end, pSet_system_t->reg_cagc_gate_end);
#endif
	VPORT_L9B0_WrFL(iris_095);
	VPORT_L9B0_RdFL(iris_028);
	VPORT_L9B0_Wr01(iris_028, reg_cdto_inc, pSet_system_t->reg_cdto_inc);
	VPORT_L9B0_WrFL(iris_028);
	VPORT_L9B0_RdFL(iris_029);
	VPORT_L9B0_Wr01(iris_029, reg_hdto_inc, pSet_system_t->reg_hdto_inc);
	VPORT_L9B0_WrFL(iris_029);


	//if(gpRealRegVPORT_L9B0->iris_110.reg_cres_clksel > 0)	// 54MHz sample clock
	if(1)	// L9Ax use 54MHz sample clock only.
	{
		VPORT_L9B0_RdFL(iris_035);
		VPORT_L9B0_Wr01(iris_035, reg_hactive_start, pSet_system_t->reg_hactive_start_54M);
		VPORT_L9B0_Wr01(iris_035, reg_hactive_width, pSet_system_t->reg_hactive_width_54M);
		VPORT_L9B0_WrFL(iris_035);
	}
	else
	{
		VPORT_L9B0_RdFL(iris_035);
		VPORT_L9B0_Wr01(iris_035, reg_hactive_width, pSet_system_t->reg_hactive_width);
		VPORT_L9B0_Wr01(iris_035, reg_hactive_start, pSet_system_t->reg_hactive_start);
		VPORT_L9B0_WrFL(iris_035);
	}

	// From L9B0 Vactive start value changed !!!!
	VPORT_L9B0_RdFL(iris_036);
	//VPORT_L9B0_Wr02(iris_036, reg_vactive_start, pSet_system_t->reg_vactive_start, reg_vactive_height, pSet_system_t->reg_vactive_height);
	VPORT_L9B0_Wr02(iris_036, reg_vactive_start, pSet_system_t->reg_vactive_start_L9B0, reg_vactive_height, pSet_system_t->reg_vactive_height);
	VPORT_L9B0_WrFL(iris_036);
	VPORT_L9B0_RdFL(iris_015);
	VPORT_L9B0_Wr01(iris_015, reg_ntsc443_mode, pSet_system_t->reg_ntsc443_mode);
	VPORT_L9B0_WrFL(iris_015);
	VPORT_L9B0_RdFL(iris_034);
	//VPORT_L9B0_Wr01(iris_034, reg_burst_gate_end, pSet_system_t->reg_burst_gate_end);
#ifdef USE_NEW_GATE_VALUES
	VPORT_L9B0_Wr02(iris_034, reg_burst_gate_start, pSet_system_t->reg_burst_gate_start_new, reg_burst_gate_end, pSet_system_t->reg_burst_gate_end_new);
#else
	VPORT_L9B0_Wr02(iris_034, reg_burst_gate_start, pSet_system_t->reg_burst_gate_start_3CS, reg_burst_gate_end, pSet_system_t->reg_burst_gate_end_3CS);
#endif
	VPORT_L9B0_WrFL(iris_034);

	// 110828: L9Bx moved to PE
	/*
	VPORT_L9B0_RdFL(iris_044);
	VPORT_L9B0_Wr01(iris_044, reg_secam_ybw, pSet_system_t->reg_secam_ybw);
	VPORT_L9B0_WrFL(iris_044);
	VPORT_L9B0_RdFL(iris_045);
	VPORT_L9B0_Wr01(iris_045, reg_auto_secam_level, pSet_system_t->reg_auto_secam_level);
	VPORT_L9B0_WrFL(iris_045);

	VPORT_L9B0_RdFL(iris_046);
	VPORT_L9B0_Wr01(iris_046, reg_lose_chromalock_mode, pSet_system_t->reg_lose_chromalock_mode);
	VPORT_L9B0_WrFL(iris_046);
	VPORT_L9B0_RdFL(iris_060);
	VPORT_L9B0_Wr06(iris_060, reg_noise_th, pSet_system_t->reg_noise_th, reg_noise_th_en, pSet_system_t->reg_noise_th_en, reg_lowfreq_vdiff_gain, pSet_system_t->reg_lowfreq_vdiff_gain, reg_chroma_vdiff_gain, pSet_system_t->reg_chroma_vdiff_gain, reg_horiz_diff_ygain, pSet_system_t->reg_horiz_diff_ygain, reg_horiz_diff_cgain, pSet_system_t->reg_horiz_diff_cgain);
	VPORT_L9B0_WrFL(iris_060);
	VPORT_L9B0_RdFL(iris_061);
	VPORT_L9B0_Wr04(iris_061, reg_y_noise_th_gain, pSet_system_t->reg_y_noise_th_gain, reg_c_noise_th_gain, pSet_system_t->reg_c_noise_th_gain, reg_burst_noise_th_gain, pSet_system_t->reg_burst_noise_th_gain, reg_vadap_burst_noise_th_gain, pSet_system_t->reg_vadap_burst_noise_th_gain);
	VPORT_L9B0_WrFL(iris_061);
	VPORT_L9B0_RdFL(iris_062);
	// 110623 : by kim.min adaptive_chroma_mode will be changed according to the input condition(RF or AV).
	//VPORT_L9B0_Wr02(iris_062, reg_motion_mode, pSet_system_t->reg_motion_mode, reg_adaptive_chroma_mode, pSet_system_t->reg_adaptive_chroma_mode);
	VPORT_L9B0_Wr01(iris_062, reg_motion_mode, pSet_system_t->reg_motion_mode);
	VPORT_L9B0_WrFL(iris_062);
	*/
	VPORT_L9B0_RdFL(iris_063);
	VPORT_L9B0_Wr02(iris_063, reg_comb2d_only, pSet_system_t->reg_comb2d_only, reg_fb_sync, pSet_system_t->reg_fb_sync);
	VPORT_L9B0_WrFL(iris_063);
	// 110828: L9Bx moved to PE
	/*
	VPORT_L9B0_RdFL(iris_064);
	VPORT_L9B0_Wr02(iris_064, reg_md_noise_th, pSet_system_t->reg_md_noise_th, reg_md_noise_th_en, pSet_system_t->reg_md_noise_th_en);
	VPORT_L9B0_WrFL(iris_064);
	*/
	VPORT_L9B0_RdFL(iris_068);
	VPORT_L9B0_Wr02(iris_068, reg_vactive_md_start, pSet_system_t->reg_vactive_md_start, reg_vactive_md_height, pSet_system_t->reg_vactive_md_height);
	VPORT_L9B0_WrFL(iris_068);
	VPORT_L9B0_RdFL(iris_089);
	// 110828: L9Bx "reg_motion_config" moved to PE
	//VPORT_L9B0_Wr03(iris_089, reg_hactive_md_start, pSet_system_t->reg_hactive_md_start, reg_hactive_md_width, pSet_system_t->reg_hactive_md_width, reg_motion_config, pSet_system_t->reg_motion_config);
	VPORT_L9B0_Wr02(iris_089, reg_hactive_md_start, pSet_system_t->reg_hactive_md_start, reg_hactive_md_width, pSet_system_t->reg_hactive_md_width);
	VPORT_L9B0_WrFL(iris_089);
	// 110828: L9Bx "reg_status_motion_mode" moved to PE
	/*
	VPORT_L9B0_RdFL(iris_090);
	VPORT_L9B0_Wr01(iris_090, reg_status_motion_mode, pSet_system_t->reg_status_motion_mode);
	VPORT_L9B0_WrFL(iris_090);
	*/
	// need Reg debug
	//	gVportRegBx->iris_091.reg_frame_motion_th = pSet_system_t->reg_frame_motion_th;
	//110127
	//	_iow(&gVportRegBx->iris_091, 8, 16, pSet_system_t->reg_frame_motion_th);
	// need Reg debug
	//	gVportRegBx->iris_086.reg_chroma_level = pSet_system_t->reg_chroma_level;
	//	gVportRegBx->iris_086.reg_hf_luma_chroma_offset = pSet_system_t->reg_hf_luma_chroma_offset;
	//	_iow(&gVportRegBx->iris_086, 8, 24, pSet_system_t->reg_chroma_level);
	//	_iow(&gVportRegBx->iris_086, 8, 8, pSet_system_t->reg_hf_luma_chroma_offset);



// won.hur : This part must be repaired!!
#if 0  // due to the deletion of 2dcomb-related function!!
	VPORT_L9B0_RdFL(iris_158);
	VPORT_L9B0_Wr01(iris_158, cvd_2dcomb_ycrdc_lcr_on, pSet_system_t->reg_2dcomb_ycrdc_lcr_on);
	VPORT_L9B0_WrFL(iris_158);
#endif //won.hur


	// kim.min 0622
	VPORT_L9B0_RdFL(iris_093);
#ifdef USE_NEW_GATE_VALUES
	VPORT_L9B0_Wr03(iris_093, reg_cordic_gate_end, pSet_system_t->reg_cordic_gate_end_new, reg_cordic_gate_start, pSet_system_t->reg_cordic_gate_start_new, reg_phase_offset_range, pSet_system_t->reg_phase_offset_range);
#else
	VPORT_L9B0_Wr03(iris_093, reg_cordic_gate_end, pSet_system_t->reg_cordic_gate_end_3CS, reg_cordic_gate_start, pSet_system_t->reg_cordic_gate_start_3CS, reg_phase_offset_range, pSet_system_t->reg_phase_offset_range);
#endif
	VPORT_L9B0_WrFL(iris_093);

	// kim.min 0716
	//	_iow(&gVportRegBx->iris_086, 8, 0, pSet_system_t->reg_tcomb_chroma_level);
	//	_iow(&gVportRegBx->iris_086, 8, 8, pSet_system_t->reg_hf_luma_chroma_offset);
	//	_iow(&gVportRegBx->iris_086, 8, 24, pSet_system_t->reg_chroma_level);
	//kim.min 1103
	// setting of below register is moved to _CVD_L9Ax_Set_Output_Range()
	//	gVportRegBx->iris_118.reg_oadj_y_offo = pSet_system_t->reg_oadj_y_offo;
	//kim.min 0906
	// setting of below register is moved to _CVD_L9Ax_Set_Output_Range()
	//	gVportRegBx->iris_119.reg_oadj_y_coeff = pSet_system_t->reg_oadj_y_coeff;
	VPORT_L9B0_RdFL(iris_015);
	VPORT_L9B0_Wr01(iris_015, reg_pal60_mode, pSet_system_t->reg_pal60_mode);
	VPORT_L9B0_WrFL(iris_015);
	//kim.min 0920
	VPORT_L9B0_RdFL(iris_026);
	VPORT_L9B0_Wr01(iris_026, reg_hstate_max, pSet_system_t->reg_hstate_max);
	VPORT_L9B0_WrFL(iris_026);

	//by dws : remove mdelay
	//mdelay(10); //0619
	OS_MsecSleep(5);

	//No use
//	VPORT_L9B0_RdFL(top_005);
//	VPORT_L9B0_Wr01(top_005, swrst_irisyc, 0);
//	VPORT_L9B0_WrFL(top_005);
	//added 0212 for better 3dcomb operation on RF signal.
	VPORT_L9B0_RdFL(iris_023);
	VPORT_L9B0_Wr01(iris_023, reg_hnon_std_threshold, pSet_system_t->reg_hnon_std_threshold);
	VPORT_L9B0_WrFL(iris_023);

	//added 110415 for Jo Jo Gunpo filed stream : no signal issue
	VPORT_L9B0_RdFL(iris_077);
	VPORT_L9B0_Wr01(iris_077, reg_vsync_signal_thresh, pSet_system_t->reg_vsync_signal_thresh);
	VPORT_L9B0_WrFL(iris_077);

   //added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
	/*
	VPORT_L9B0_RdFL(iris_048);
	VPORT_L9B0_Wr02(iris_048, reg_fixed_cstate, pSet_system_t->reg_fixed_cstate, cstate, pSet_system_t->reg_cstate);
	VPORT_L9B0_WrFL(iris_048);
	*/
	// For proper color system detection, at first set cstate value to default.

#if 0
   //gogosing added 110610 (for russia ATV field stream color system issue)	// 이곳에 두면 재현 잘 됨
   		VPORT_L9B0_RdFL(iris_182);
		VPORT_L9B0_Wr01(iris_182, reg_cs_chroma_burst5or10, pSet_system_t->cs_chroma_burst5or10);
		VPORT_L9B0_WrFL(iris_182);

		VPORT_L9B0_RdFL(iris_193);
		VPORT_L9B0_Wr01(iris_193, reg_cs1_chroma_burst5or10, pSet_system_t->cs1_chroma_burst5or10);
		VPORT_L9B0_WrFL(iris_193);
#endif

   //kim.min 0906
	VPORT_L9B0_RdFL(iris_262);
	VPORT_L9B0_Wr02(iris_262, reg_hrs_ha_start, pSet_system_t->reg_hrs_ha_start, reg_hrs_ha_width, pSet_system_t->reg_hrs_ha_width);
	VPORT_L9B0_WrFL(iris_262);

	//110901 : Start RGB Initail settings.
	//110919 : Modified to Set H/V offset of SCART RGB for each color system.
	VPORT_L9B0_RdFL(fastblank_009);
	VPORT_L9B0_RdFL(fastblank_010);
	VPORT_L9B0_Wr01(fastblank_009, reg_fb_vstart_odd, pSet_system_t->reg_fb_vstart_odd);
	VPORT_L9B0_Wr01(fastblank_010, reg_fb_vstart_even, pSet_system_t->reg_fb_vstart_even);
	VPORT_L9B0_Wr01(fastblank_010, reg_fb_height_half, pSet_system_t->reg_fb_height_half);
	VPORT_L9B0_Wr01(fastblank_010, reg_fb_hstart, pSet_system_t->reg_fb_hstart);
	VPORT_L9B0_WrFL(fastblank_009);
	VPORT_L9B0_WrFL(fastblank_010);

	//111129 wonsik.do
	VPORT_L9B0_RdFL(iris_073);
	VPORT_L9B0_Wr01(iris_073, reg_dcrestore_accum_width, pSet_system_t->reg_dcrestore_accum_width);
	VPORT_L9B0_WrFL(iris_073);

	VPORT_L9B0_RdFL(iris_075);
	VPORT_L9B0_Wr01(iris_075, reg_dcrestore_hsync_mid, pSet_system_t->reg_dcrestore_hsync_mid);
	VPORT_L9B0_WrFL(iris_075);

	if(g_CVD_Status_3CS.in_rf_mode == TRUE) {
		//111215 : added reg_contrast
		VPORT_L9B0_RdFL(iris_020);
		VPORT_L9B0_Wr01(iris_020, reg_contrast, pSet_system_t->reg_contrast);
		VPORT_L9B0_WrFL(iris_020);

		VPORT_L9B0_RdFL(iris_021);
		VPORT_L9B0_Wr01(iris_021, reg_cagc, pSet_system_t->reg_cagc);
		VPORT_L9B0_WrFL(iris_021);
	}
	else {	// AV mode
		//111215 : added reg_contrast
		VPORT_L9B0_RdFL(iris_020);
		VPORT_L9B0_Wr01(iris_020, reg_contrast, pSet_system_t->reg_contrast_av);
		VPORT_L9B0_WrFL(iris_020);

		VPORT_L9B0_RdFL(iris_021);
		VPORT_L9B0_Wr01(iris_021, reg_cagc, pSet_system_t->reg_cagc_av);
		VPORT_L9B0_WrFL(iris_021);
	}

   //120105 : added reg_saturation
	VPORT_L9B0_RdFL(iris_020);
	VPORT_L9B0_Wr01(iris_020, reg_saturation, pSet_system_t->reg_saturation);
	VPORT_L9B0_WrFL(iris_020);
}

void CVD_L9Bx_Program_Color_System_CS(CVD_SELECT_CDETECT_T cs_sel, CVD_SET_SYSTEM_MAIN_T *pSet_system_t)
{

	if (cs_sel == CVD_SEL_CS_CS0) // select cs0;
	{
		VPORT_L9B0_RdFL(iris_179);
		VPORT_L9B0_Wr01(iris_179, reg_cs_adaptive_chroma_mode, pSet_system_t->reg_adaptive_chroma_mode);
		VPORT_L9B0_Wr01(iris_179, reg_cs_auto_secam_level, pSet_system_t->reg_auto_secam_level);
		VPORT_L9B0_WrFL(iris_179);

		VPORT_L9B0_RdFL(iris_180);
		//gogoging SECAM threshold for keeping PAL stable 20110613
		VPORT_L9B0_Wr01(iris_180, reg_cs_issecam_th, pSet_system_t->cs_issecam_th);
		VPORT_L9B0_Wr01(iris_180, reg_cs_phase_offset_range, pSet_system_t->reg_phase_offset_range);
		VPORT_L9B0_WrFL(iris_180);

		VPORT_L9B0_RdFL(iris_182);
		VPORT_L9B0_Wr01(iris_182, reg_cs_secam_ybw, pSet_system_t->reg_secam_ybw);
		VPORT_L9B0_Wr01(iris_182, reg_cs_adaptive_mode, pSet_system_t->reg_adaptive_mode);
		VPORT_L9B0_Wr01(iris_182, reg_cs_colour_mode, pSet_system_t->reg_colour_mode);
		VPORT_L9B0_Wr01(iris_182, reg_cs_ntsc443_mode, pSet_system_t->reg_ntsc443_mode);
		VPORT_L9B0_Wr01(iris_182, reg_cs_pal60_mode, pSet_system_t->reg_pal60_mode);
		//gogosing PAL에서 0x5c  설정 시 FSC position  테스트 시 secam, pal transition 지속됨 --> 326e 원복 110627
		//cs0, cs1 burst gate width reg. ready
		VPORT_L9B0_Wr01(iris_182, reg_cs_chroma_burst5or10, pSet_system_t->cs_chroma_burst5or10);
		VPORT_L9B0_Wr01(iris_182, reg_cs_cagc_en, pSet_system_t->reg_cagc_en);
		VPORT_L9B0_WrFL(iris_182);

		VPORT_L9B0_RdFL(iris_183);
		VPORT_L9B0_Wr01(iris_183, reg_cs_cagc, pSet_system_t->reg_cagc);
		VPORT_L9B0_WrFL(iris_183);

		VPORT_L9B0_RdFL(iris_184);
		VPORT_L9B0_Wr01(iris_184, reg_cs_chroma_bw_lo, pSet_system_t->reg_chroma_bw_lo);
		VPORT_L9B0_WrFL(iris_184);

		VPORT_L9B0_RdFL(iris_185);
		VPORT_L9B0_Wr01(iris_185, reg_cs_cdto_inc, pSet_system_t->reg_cdto_inc);
		VPORT_L9B0_WrFL(iris_185);

		VPORT_L9B0_RdFL(iris_186);
		VPORT_L9B0_Wr01(iris_186, reg_cs_lose_chromalock_mode, pSet_system_t->reg_lose_chromalock_mode);
		VPORT_L9B0_WrFL(iris_186);

		//added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
		/*
		VPORT_L9B0_RdFL(iris_186);
		VPORT_L9B0_Wr02(iris_186, reg_cs_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cs_cstate, pSet_system_t->reg_cstate);
		VPORT_L9B0_WrFL(iris_186);
		*/

		//added 110908
		VPORT_L9B0_RdFL(iris_271);
#ifdef USE_NEW_GATE_VALUES
		VPORT_L9B0_Wr02(iris_271, reg_burst1_gate_start, pSet_system_t->reg_burst_gate_start_new, reg_burst1_gate_end, pSet_system_t->reg_burst_gate_end_new);
#else
		VPORT_L9B0_Wr02(iris_271, reg_burst1_gate_start, pSet_system_t->reg_burst_gate_start_3CS, reg_burst1_gate_end, pSet_system_t->reg_burst_gate_end_3CS);
#endif
		VPORT_L9B0_WrFL(iris_271);

		VPORT_L9B0_RdFL(iris_272);
#ifdef USE_NEW_GATE_VALUES
		VPORT_L9B0_Wr02(iris_272, reg_cordic1_gate_start, pSet_system_t->reg_cordic_gate_start_new, reg_cordic1_gate_end, pSet_system_t->reg_cordic_gate_end_new);
#else
		VPORT_L9B0_Wr02(iris_272, reg_cordic1_gate_start, pSet_system_t->reg_cordic_gate_start_3CS, reg_cordic1_gate_end, pSet_system_t->reg_cordic_gate_end_3CS);
#endif
		VPORT_L9B0_WrFL(iris_272);
	}
	else	// cs1 selected
	{
		VPORT_L9B0_RdFL(iris_190);
		VPORT_L9B0_Wr01(iris_190, reg_cs1_adaptive_chroma_mode, pSet_system_t->reg_adaptive_chroma_mode);
		VPORT_L9B0_Wr01(iris_190, reg_cs1_auto_secam_level, pSet_system_t->reg_auto_secam_level);
		VPORT_L9B0_WrFL(iris_190);

		VPORT_L9B0_RdFL(iris_191);
		VPORT_L9B0_Wr01(iris_191, reg_cs1_phase_offset_range, pSet_system_t->reg_phase_offset_range);
		VPORT_L9B0_WrFL(iris_191);

		VPORT_L9B0_RdFL(iris_193);
		VPORT_L9B0_Wr01(iris_193, reg_cs1_secam_ybw, pSet_system_t->reg_secam_ybw);
		VPORT_L9B0_Wr01(iris_193, reg_cs1_adaptive_mode, pSet_system_t->reg_adaptive_mode);
		VPORT_L9B0_Wr01(iris_193, reg_cs1_colour_mode, pSet_system_t->reg_colour_mode);
		VPORT_L9B0_Wr01(iris_193, reg_cs1_ntsc443_mode, pSet_system_t->reg_ntsc443_mode);
		VPORT_L9B0_Wr01(iris_193, reg_cs1_pal60_mode, pSet_system_t->reg_pal60_mode);
		//gogosing PAL에서 0x5c  설정 시 FSC position  테스트 시 secam, pal transition 지속됨 --> 326e 원복 110627
		//cs0, cs1 burst gate width reg. ready
		VPORT_L9B0_Wr01(iris_193, reg_cs1_chroma_burst5or10, pSet_system_t->cs1_chroma_burst5or10);
		VPORT_L9B0_Wr01(iris_193, reg_cs1_cagc_en, pSet_system_t->reg_cagc_en);
		VPORT_L9B0_WrFL(iris_193);

		VPORT_L9B0_RdFL(iris_194);
		VPORT_L9B0_Wr01(iris_194, reg_cs1_cagc, pSet_system_t->reg_cagc);
		VPORT_L9B0_WrFL(iris_194);

		VPORT_L9B0_RdFL(iris_195);
		VPORT_L9B0_Wr01(iris_195, reg_cs1_chroma_bw_lo, pSet_system_t->reg_chroma_bw_lo);
		VPORT_L9B0_WrFL(iris_195);

		VPORT_L9B0_RdFL(iris_196);
		VPORT_L9B0_Wr01(iris_196, reg_cs1_cdto_inc, pSet_system_t->reg_cdto_inc);
		VPORT_L9B0_WrFL(iris_196);

		VPORT_L9B0_RdFL(iris_197);
		VPORT_L9B0_Wr01(iris_197, reg_cs1_lose_chromalock_mode, pSet_system_t->reg_lose_chromalock_mode);
		VPORT_L9B0_WrFL(iris_197);

		//added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
		/*
		VPORT_L9B0_RdFL(iris_197);
		VPORT_L9B0_Wr02(iris_197, reg_cs1_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cs1_cstate, pSet_system_t->reg_cstate);
		VPORT_L9B0_WrFL(iris_197);
		*/

		//added 110908
		VPORT_L9B0_RdFL(iris_271);
#ifdef USE_NEW_GATE_VALUES
		VPORT_L9B0_Wr02(iris_271, reg_burst2_gate_start, pSet_system_t->reg_burst_gate_start_new, reg_burst2_gate_end, pSet_system_t->reg_burst_gate_end_new);
#else
		VPORT_L9B0_Wr02(iris_271, reg_burst2_gate_start, pSet_system_t->reg_burst_gate_start_3CS, reg_burst2_gate_end, pSet_system_t->reg_burst_gate_end_3CS);
#endif
		VPORT_L9B0_WrFL(iris_271);

		VPORT_L9B0_RdFL(iris_272);
#ifdef USE_NEW_GATE_VALUES
		VPORT_L9B0_Wr02(iris_272, reg_cordic2_gate_start, pSet_system_t->reg_cordic_gate_start_new, reg_cordic2_gate_end, pSet_system_t->reg_cordic_gate_end_new);
#else
		VPORT_L9B0_Wr02(iris_272, reg_cordic2_gate_start, pSet_system_t->reg_cordic_gate_start_3CS, reg_cordic2_gate_end, pSet_system_t->reg_cordic_gate_end_3CS);
#endif
		VPORT_L9B0_WrFL(iris_272);
	}

	return;
}

void CVD_L9Bx_Program_Color_System_PreJob(CVD_SET_SYSTEM_MAIN_T *pSet_system_t)
{
	// For proper color system detection, at first set cstate value to default.
	VPORT_L9B0_RdFL(iris_048);
	VPORT_L9B0_Wr02(iris_048, reg_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cstate, pSet_system_t->reg_cstate);
	VPORT_L9B0_WrFL(iris_048);
}

void CVD_L9Bx_Program_Color_System_PreJob2(void)
{
	CVD_DEBUG("%s entered \n",__func__);
   //added 111226 ( default register setting for fast 3Dcomb operation )
	// restore default values of reg_agc_half_en to '0', and reg_nstd_hysis to '7' for EBS field stream support.
	VPORT_L9B0_RdFL(iris_014);
	VPORT_L9B0_Wr01(iris_014, reg_agc_half_en, 0);
	VPORT_L9B0_WrFL(iris_014);
	VPORT_L9B0_RdFL(iris_023);
	VPORT_L9B0_Wr01(iris_023, reg_nstd_hysis, 7);
	VPORT_L9B0_WrFL(iris_023);


	//added 120114 for stable agc (restore default values)
	VPORT_L9B0_RdFL(iris_024);
	VPORT_L9B0_Wr01(iris_024, reg_agc_peak_cntl, 0x1);
	VPORT_L9B0_WrFL(iris_024);
	VPORT_L9B0_RdFL(iris_073);
	VPORT_L9B0_Wr01(iris_073, reg_dcrestore_gain, 0x0);
	VPORT_L9B0_WrFL(iris_073);
}

void CVD_L9Bx_Program_Color_System_PostJob(CVD_SET_SYSTEM_MAIN_T *pSet_system_t)
{
   //added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
	VPORT_L9B0_RdFL(iris_048);
	VPORT_L9B0_Wr02(iris_048, reg_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cstate, pSet_system_t->reg_cstate);
	VPORT_L9B0_WrFL(iris_048);
}

void CVD_L9Bx_Program_Color_System_PostJob2(void)
{
//	CVD_DEBUG("%s entered \n",__func__);
   //added 111226 ( for EBS 060225_1636 stream , change reg_agc_half_en to '1', reg_nstd_hysis to '0' )
	VPORT_L9B0_RdFL(iris_014);
	VPORT_L9B0_Wr01(iris_014, reg_agc_half_en, 1);
	VPORT_L9B0_WrFL(iris_014);
	VPORT_L9B0_RdFL(iris_023);
	VPORT_L9B0_Wr01(iris_023, reg_nstd_hysis, 0);
	VPORT_L9B0_WrFL(iris_023);

	//added 120114 for stable agc
	VPORT_L9B0_RdFL(iris_024);
	VPORT_L9B0_Wr01(iris_024, reg_agc_peak_cntl, 0x0);
	VPORT_L9B0_WrFL(iris_024);
	VPORT_L9B0_RdFL(iris_073);
	VPORT_L9B0_Wr01(iris_073, reg_dcrestore_gain, 0x3);
	VPORT_L9B0_WrFL(iris_073);
}

void CVD_L9Bx_Program_Color_System_CHB_NTSC(void)
{

#ifdef CHBCVD_SUPPORT
	// the reg. name "swrst_chbcvd" is changed to "chbreg_soft_reset"
	//VPORT_L9B0_RdFL(top_007);
	//VPORT_L9B0_Wr01(top_007, swrst_chbcvd, 1);
	//VPORT_L9B0_WrFL(top_007);
	CHBCVD_L9_RdFL(chbcvd_001);
	CHBCVD_L9_Wr01(chbcvd_001, chbreg_soft_reset, 1);
	CHBCVD_L9_WrFL(chbcvd_001);

	CHBCVD_L9_RdFL(chbcvd_001);
	CHBCVD_L9_Wr03(chbcvd_001, chbreg_colour_mode, 0x0, chbreg_vline_625, 0x0, chbreg_hpixel, 0x0);
	CHBCVD_L9_WrFL(chbcvd_001);
	CHBCVD_L9_RdFL(chbcvd_002);
	CHBCVD_L9_Wr01(chbcvd_002, chbreg_ped, 0x1);
	CHBCVD_L9_WrFL(chbcvd_002);
	//	gVportRegBx->chbcvd_003.chbreg_cagc_en = 0x1;
	//	gVportRegBx->chbcvd_002.chbreg_hagc_half_en = 0x1;		//check
	//	gVportRegBx->chbcvd_002.chbreg_dc_clamp_mode = 0x0;
	//	gVportRegBx->chbcvd_002.chbreg_hagc_field_mode = 0x0;
	//	gVportRegBx->chbcvd_002.chbreg_chroma_bw_lo = 0x0;
	//	gVportRegBx->chbcvd_004.chbreg_adaptive_mode = 0x0;
	CHBCVD_L9_RdFL(chbcvd_004);
	CHBCVD_L9_Wr01(chbcvd_004, chbreg_hagc, 0xdd);
	CHBCVD_L9_WrFL(chbcvd_004);
	CHBCVD_L9_RdFL(chbcvd_010);
	CHBCVD_L9_Wr01(chbcvd_010, chbreg_cagc, 0xa8);
	CHBCVD_L9_WrFL(chbcvd_010);
	CHBCVD_L9_RdFL(chbcvd_017);
	CHBCVD_L9_Wr01(chbcvd_017, chbreg_cdto_inc, 0x21f07c1f);
	CHBCVD_L9_WrFL(chbcvd_017);
	CHBCVD_L9_RdFL(chbcvd_022);
	CHBCVD_L9_Wr02(chbcvd_022, chbreg_dr_freq, 0x00, chbreg_db_freq, 0x00);
	CHBCVD_L9_WrFL(chbcvd_022);
	CHBCVD_L9_RdFL(chbcvd_024);
	CHBCVD_L9_Wr02(chbcvd_024, chbreg_hactive_start, 0x82, chbreg_hactive_width, 0x50);
	CHBCVD_L9_WrFL(chbcvd_024);
	CHBCVD_L9_RdFL(chbcvd_027);
	CHBCVD_L9_Wr02(chbcvd_027, chbreg_vactive_start, 0x22, chbreg_vactive_height, 0x61);
	CHBCVD_L9_WrFL(chbcvd_027);
	CHBCVD_L9_RdFL(chbcvd_048);
	CHBCVD_L9_Wr01(chbcvd_048, chbreg_lose_chromalock_mode, 0x3);
	CHBCVD_L9_WrFL(chbcvd_048);
	CHBCVD_L9_RdFL(chbcvd_056);
	CHBCVD_L9_Wr01(chbcvd_056, chbreg_cagc_tc_ibig, 0x4);
	CHBCVD_L9_WrFL(chbcvd_056);
	//add by ok. 20110317
	CHBCVD_L9_RdFL(chbcvd_057);
	CHBCVD_L9_Wr02(chbcvd_057, chbreg_dcrestore_no_bad_bp, 0x1, chbreg_dcrestore_kill_enable, 0x1);
	CHBCVD_L9_WrFL(chbcvd_057);
	CHBCVD_L9_RdFL(chbcvd_034);
	CHBCVD_L9_Wr03(chbcvd_034, chbreg_cpump_auto_stip_unlocked, 0x1, chbreg_cpump_auto_stip_no_signal, 0x1, chbreg_cpump_auto_stip_noisy, 0x1);
	CHBCVD_L9_WrFL(chbcvd_034);
	CHBCVD_L9_RdFL(chbcvd_036);
	CHBCVD_L9_Wr04(chbcvd_036, chbreg_cpump_up_max, 0x7f, chbreg_cpump_diff_signal_only, 0x1, chbreg_cpump_up_diff_max, 0x7f, chbreg_cpump_diff_noisy_only, 0x1);
	CHBCVD_L9_WrFL(chbcvd_036);
	CHBCVD_L9_RdFL(chbcvd_037);
	CHBCVD_L9_Wr01(chbcvd_037, chbreg_cpump_dn_diff_max, 0x0);
	CHBCVD_L9_WrFL(chbcvd_037);
	/*
	   gVportRegBx->chbreg_adc_updn_swap.chbreg_adc_updn_swap = 0x1;
	   gVportRegBx->chbreg_yc_delay.chbreg_yc_delay = 0x0;
	   gVportRegBx->chbreg_hdto_inc.chbreg_hdto_inc = 0x20000000;
	   gVportRegBx->chbcvd_022.chbreg_dr_freq	= 0x0;
	   gVportRegBx->chbcvd_022.chbreg_db_freq	= 0x0;
	   gVportRegBx->chbcvd_001.chbreg_ntsc443_mode = 0x0;
	   _iow(&gVportRegBx->chbcvd_023, 8, 0, 0x46); // chbreg_burst_gate_end
	   gVportRegBx->chbcvd_047.chbreg_secam_ybw = 0x0;
	   gVportRegBx->chbcvd_047.chbreg_auto_secam_level = 0x0;
	   gVportRegBx->chbcvd_052.chbreg_noise_th = 0x2;
	   gVportRegBx->chbreg_cpump_adjust_polarity.chbreg_noise_th_en = 0x0;
	   gVportRegBx->chbcvd_004.chbreg_adaptive_chroma_mode = 0x1;
	 */
	CHBCVD_L9_RdFL(chbcvd_001);
	CHBCVD_L9_Wr01(chbcvd_001, chbreg_soft_reset, 0);
	CHBCVD_L9_WrFL(chbcvd_001);
#endif
}

#if 0
void CVD_L9Ax_ALL_Power_Down(void)
{
	/*CVBS ADC Power Down Setting */
	VPORT_I2C_Read((UINT32*)&gafe_cvbs_1_bx);
	VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
	VPORT_I2C_Read((UINT32*)&gafe_vdac_0_bx);
	VPORT_I2C_Read((UINT32*)&gafe_vdac_1_bx);
	VPORT_I2C_Read((UINT32*)&gafe_vbuf_0_bx);
	VPORT_I2C_Read((UINT32*)&gafe_vbuf_1_bx);

	gafe_cvbs_1_bx.cvbs_pdbm = 0;
	gafe_cvbs_3_bx.cvbs_pdb = 0;

	/* VDAC & BUFFER Power Down Setting */
	gafe_vdac_0_bx.vdac_pdb = 0;
	gafe_vdac_1_bx.vdicnt = 0x3;
	gafe_vbuf_1_bx.buf_pdb1 = 0;
	gafe_vbuf_0_bx.buf_pdb2 = 0;

	VPORT_I2C_Write((UINT32*)&gafe_cvbs_1_bx);
	VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
	VPORT_I2C_Write((UINT32*)&gafe_vdac_0_bx);
	VPORT_I2C_Write((UINT32*)&gafe_vdac_1_bx);
	VPORT_I2C_Write((UINT32*)&gafe_vbuf_0_bx);
	VPORT_I2C_Write((UINT32*)&gafe_vbuf_1_bx);


	/* AFE3CH Power Down Setting */
	/* LLPLL PDB */
	VPORT_I2C_Read((UINT32*)&gmain_pll_4_bx);
	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gmain_pll_4_bx.dr3p_pdb = 0;
	gllpll_0_bx.reset_n = 0;
	gllpll_0_bx.llpll_pdb = 0;
	VPORT_I2C_Write((UINT32*)&gmain_pll_4_bx);
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	/* LLPLL/CST SWRST & 3CH_DIG SWRST */
	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_pix = 1;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
}
#endif

void CVD_L9Bx_SW_Reset(LX_AFE_CVD_SELECT_T select_main_sub)
{
		// SET SW reset registers to '1'
		//		gVportRegBx->reg_swrst_exta.reg_swrst_exta = 1;
		//		gVportRegBx->reg_swrst_exta.reg_swrst_extb = 1;
		//from cvd_test.cmm
		VPORT_L9B0_RdFL(iris_011);
		/*
		VPORT_L9B0_Rd01(iris_011, reg_cvd_soft_reset, temp);
		AFE_PRINT("top_001 :  %x \n",(UINT32)&gpRealRegVPORT_L9B0->top_001- (UINT32)gpRealRegVPORT_L9B0);
		AFE_PRINT("iris_mif_gmua_001 :  %x \n",(UINT32)&gpRealRegVPORT_L9B0->iris_mif_gmua_001- (UINT32)gpRealRegVPORT_L9B0);
		AFE_PRINT("iris_mif_gmua_008 :  %x \n",(UINT32)&gpRealRegVPORT_L9B0->iris_mif_gmua_008- (UINT32)gpRealRegVPORT_L9B0);
		AFE_PRINT("iris_de_ctrl_001 :  %x \n",(UINT32)&gpRealRegVPORT_L9B0->iris_de_ctrl_001 - (UINT32)gpRealRegVPORT_L9B0);
		AFE_PRINT("fast_blank_status_001 :  %x \n",(UINT32)&gpRealRegVPORT_L9B0->fast_blank_status_001 - (UINT32)gpRealRegVPORT_L9B0);
		AFE_PRINT("iris_001 :  %x \n",(UINT32)&gpRealRegVPORT_L9B0->iris_001- (UINT32)gpRealRegVPORT_L9B0);
		AFE_PRINT("iris_011 :  %x \n",(UINT32)&gpRealRegVPORT_L9B0->iris_011- (UINT32)gpRealRegVPORT_L9B0);
		AFE_PRINT("cvd_soft_reset status before set to 1 : [%x]\n", temp);
		AFE_PRINT("iris_011 value:[%x]\n", REG_RD(0xc0024230));
		REG_WD(0xc0024230		,1);
		*/
		VPORT_L9B0_Wr01(iris_011, reg_cvd_soft_reset, 1);
		VPORT_L9B0_WrFL(iris_011);

		/* LLPLL/CST SWRST & 3CH_DIG SWRST */
		VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
		VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
		gsoft_reset_0_bx.swrst_pix = 1;
		gllpll_0_bx.reset_n = 0;
		gllpll_0_bx.llpll_pdb = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
		VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

		// dws added
		//by dws : remove mdelay
		//mdelay(10); //0809
		OS_MsecSleep(5);
		//gVportRegBx->iris_063.reg_lbadrgen_rst = 1;
		//Clear SW Reset Registers to '0'
		//		gVportRegBx->reg_swrst_exta.reg_swrst_exta = 0;
		//		gVportRegBx->reg_swrst_exta.reg_swrst_extb = 0;
		//from cvd_test.cmm
		VPORT_L9B0_RdFL(iris_011);
		VPORT_L9B0_Wr01(iris_011, reg_cvd_soft_reset, 0);
		VPORT_L9B0_WrFL(iris_011);

		/* LLPLL/CST SWRST & 3CH_DIG SWRST */
		VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
		VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
		gsoft_reset_0_bx.swrst_pix = 0;
		gllpll_0_bx.reset_n = 1;
		gllpll_0_bx.llpll_pdb = 1;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
		VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

		// dws added
		//gVportRegBx->iris_063.reg_lbadrgen_rst = 0;

}

// BOOLEAN PowerOnOff
// TRUE : Power Down
// FALSE : Power Up
void CVD_L9Bx_Power_Down(LX_AFE_CVD_SELECT_T select_main_sub, BOOLEAN PowerOnOFF)
{
	if(select_main_sub == LX_CVD_MAIN)
	{
		//if(PowerOnOFF==TRUE)
		if(PowerOnOFF==FALSE) // from cvd_test.cmm
		{
			// At First, dr3p_pdb should be turned off(Workaround code for denc latchup)
			// Move to I2C for support L9A Internel I2C 8MHz - 20110623 by sh.myoung -
			//VPORT_I2C_Read((UINT32*)&gmain_pll_4_bx);
			//gmain_pll_4_bx.dr3p_pdb = 0;
			//VPORT_I2C_Write((UINT32*)&gmain_pll_4_bx);

			//VPORT_I2C_Read((UINT32*)&gmain_pll_4_bx);
			//gmain_pll_4_bx.dr3p_pdb = 1;
			//VPORT_I2C_Write((UINT32*)&gmain_pll_4_bx);

			//	mdelay(10);

			//cvd on
			// CVD Power On (Default settings)
			VPORT_I2C_Read((UINT32*)&gafe_cvbs_1_bx);
			VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
			gafe_cvbs_1_bx.cvbs_pdbm = 0x1;
			gafe_cvbs_3_bx.cvbs_pdb = 0x1;
			VPORT_I2C_Write((UINT32*)&gafe_cvbs_1_bx);
			VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);

			VPORT_I2C_Read((UINT32*)&gafe_vbuf_0_bx);
			VPORT_I2C_Read((UINT32*)&gafe_vbuf_1_bx);

			/* VDAC & BUFFER Power Down Setting */
			gafe_vbuf_1_bx.buf_pdb1 = 1;
			// buf2 is not used.
			gafe_vbuf_0_bx.buf_pdb2 = 0;

			VPORT_I2C_Write((UINT32*)&gafe_vbuf_0_bx);
			VPORT_I2C_Write((UINT32*)&gafe_vbuf_1_bx);
		}
		else
		{
			//CVD off

			VPORT_I2C_Read((UINT32*)&gmain_pll_4_bx);
			VPORT_I2C_Read((UINT32*)&gafe_cvbs_1_bx);
			VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
			gafe_cvbs_1_bx.cvbs_pdbm = 0;
			gafe_cvbs_3_bx.cvbs_pdb = 0;
			gmain_pll_4_bx.dr3p_pdb = 0;
			VPORT_I2C_Write((UINT32*)&gmain_pll_4_bx);
			VPORT_I2C_Write((UINT32*)&gafe_cvbs_1_bx);
			VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);

			VPORT_I2C_Read((UINT32*)&gafe_vbuf_0_bx);
			VPORT_I2C_Read((UINT32*)&gafe_vbuf_1_bx);

			/* VDAC & BUFFER Power Down Setting */
			gafe_vbuf_1_bx.buf_pdb1 = 0;
			gafe_vbuf_0_bx.buf_pdb2 = 0;

			VPORT_I2C_Write((UINT32*)&gafe_vbuf_0_bx);
			VPORT_I2C_Write((UINT32*)&gafe_vbuf_1_bx);
		}
	}
	else
	{
		//if(PowerOnOFF==TRUE)
		if(PowerOnOFF==FALSE)// from cvd_test.cmm
		{
			//L8B0 Code
			/*
			VPORT_L9B0_RdFL(cvbsafe_007);
			VPORT_L9B0_Wr08(cvbsafe_007, cb_lpf, 0x1, cb_pdb, 0x1, cb_icon, 0x2, cb_cp, 0x1, cb_selref, 0x2, cb_dcsel, 0x2, cb_cnt, 0x1, cb_cns, 0x0);
			VPORT_L9B0_WrFL(cvbsafe_007);
			*/
			// L9에 cb_cnt, cb_cns 찾을 수 없음 ???
			VPORT_I2C_Read((UINT32*)&gafe_cb_0_bx);
			VPORT_I2C_Read((UINT32*)&gafe_cb_1_bx);
			gafe_cb_1_bx.cb_lpf = 1;
			gafe_cb_0_bx.cb_pdb = 1;
			gafe_cb_1_bx.cb_icon = 2;
			gafe_cb_0_bx.cb_cp = 1;
			gafe_cb_1_bx.cb_selref = 2;
			gafe_cb_1_bx.cb_dcsel = 2;
			VPORT_I2C_Write((UINT32*)&gafe_cb_0_bx);
			VPORT_I2C_Write((UINT32*)&gafe_cb_1_bx);
		}
		else
		{
			//L8B0 Code
			/*
			VPORT_L9B0_RdFL(cvbsafe_007);
			VPORT_L9B0_Wr01(cvbsafe_007, cb_pdb, 0);
			VPORT_L9B0_WrFL(cvbsafe_007);
			*/
			VPORT_I2C_Read((UINT32*)&gafe_cb_0_bx);
			gafe_cb_0_bx.cb_pdb = 0;
			VPORT_I2C_Write((UINT32*)&gafe_cb_0_bx);
		}
	}
}

void CVD_L9Bx_Reg_Init(LX_AFE_CVD_SELECT_T select_main_sub)
{
	//110915 : release f54m, cvbs reset first.
	VPORT_I2C_Read((UINT32*)&gsoft_reset_5_bx);
	gsoft_reset_5_bx.swrst_f54m = 0;
	gsoft_reset_5_bx.swrst_cvbs = 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_5_bx);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	VPORT_I2C_Read((UINT32*)&gdata_bridge_0_bx);
	VPORT_I2C_Read((UINT32*)&gclock_control_2_bx);
	gsoft_reset_0_bx.swrst_f24m = 0;
	gdata_bridge_0_bx.reg_cvbs_clock_rate = 1;
	gclock_control_2_bx.sel_inv_f54m_clock = 1;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
	VPORT_I2C_Write((UINT32*)&gdata_bridge_0_bx);
	VPORT_I2C_Write((UINT32*)&gclock_control_2_bx);

	// CTop CVD Clock Settings
	// 110828 : L9B Ctop Register
	CTOP_CTRL_L9B_RdFL(ctr27_reg_extclk_swrst);
	CTOP_CTRL_L9B_Wr01(ctr27_reg_extclk_swrst, reg_swrst_cvd54, 0x0);
	CTOP_CTRL_L9B_Wr01(ctr27_reg_extclk_swrst, reg_swrst_cvd27, 0x0);
	CTOP_CTRL_L9B_Wr01(ctr27_reg_extclk_swrst, reg_swrst_vbi, 0x0);
	CTOP_CTRL_L9B_Wr01(ctr27_reg_extclk_swrst, reg_swrst_scart, 0x0);
	CTOP_CTRL_L9B_WrFL(ctr27_reg_extclk_swrst);

	/*
	   CTOP_CTRL_L9_RdFL(ctr27);
	   CTOP_CTRL_L9_Wr01(ctr27, swrst_cvd54, 0x0);
	   CTOP_CTRL_L9_Wr01(ctr27, swrst_cvd27, 0x0);
	   CTOP_CTRL_L9_Wr01(ctr27, swrst_vbi, 0x0);
	   CTOP_CTRL_L9_Wr01(ctr27, swrst_scart, 0x0);
	   CTOP_CTRL_L9_WrFL(ctr27);
	 */
	// 110901 : L9B0 Scart RGB register setting.
	// Moved to Reg_Init
	CTOP_CTRL_L9B_RdFL(ctr26_reg_extclk_div_sel);
	CTOP_CTRL_L9B_Wr01(ctr26_reg_extclk_div_sel, reg_ch3pix_clk_sel, 0x1);
	CTOP_CTRL_L9B_WrFL(ctr26_reg_extclk_div_sel);

	// 3D Comb memory mapping
	VPORT_L9B0_RdFL(iris_mif_gmua_007);
	VPORT_L9B0_Wr01(iris_mif_gmua_007, reg_gmau_cmd_base, gpCvdMemCfg->memory_base);
	VPORT_L9B0_WrFL(iris_mif_gmua_007);

	VPORT_L9B0_RdFL(iris_019);
	VPORT_L9B0_Wr01(iris_019, reg_blue_mode, 0x0);
	VPORT_L9B0_WrFL(iris_019);
	// 0909 by kim.min(same setting with FPGA)

	VPORT_I2C_Read((UINT32*)&gafe_cvbs_1_bx);
	VPORT_I2C_Read((UINT32*)&gafe_cvbs_2_bx);

	gafe_cvbs_1_bx.cvbs_lpf = 1;
	gafe_cvbs_2_bx.cvbs_bw = 0;
	gafe_cvbs_2_bx.cvbs_byp = 1;

	VPORT_I2C_Write((UINT32*)&gafe_cvbs_1_bx);
	VPORT_I2C_Write((UINT32*)&gafe_cvbs_2_bx);

	// 1210 Invert Odd/Even Field on B0 Revision(H/W Change or DE Firmware Change?)
	// But This has problem on CC data slicing.
	//gVportRegBx->iris_044.reg_flip_field = 1;
	// Initial Register Setting For Scart Fast Blanking.
	VPORT_L9B0_RdFL(fastblank_001);
	// Blend Ratio 0x08 is for test only
	//VPORT_L9B0_Wr04(fastblank_001, reg_fb_2line_delay, 0x1, reg_fb_blend_ratio, 0x08, reg_fb3ch_delay, 0xC, reg_fb_latency, 0x16);
	VPORT_L9B0_Wr04(fastblank_001, reg_fb_2line_delay, 0x1, reg_fb_blend_ratio, 0x10, reg_fb3ch_delay, 0xC, reg_fb_latency, 0x16);
	VPORT_L9B0_WrFL(fastblank_001);
	//For Test, Mix CVBS & RGB signal
	//gVportRegBx->fastblank_001.reg_fb_blend_ratio = 0x10;
	// For Faster 3D Comb lock(kim.min 20110110)
	// But, This produced 3D-Comb Lock-Unlocking problem on NTSC RF Signal
	// Setting reg_hnon_std_threshold to 0x0c(0x06) solve lock-unlock problem(20110221)
	VPORT_L9B0_RdFL(iris_023);
	//111007 by kim.min
	//VPORT_L9B0_Wr01(iris_023, reg_nstd_hysis, 0x3);
	//VPORT_L9B0_Wr01(iris_023, reg_nstd_hysis, 0x9);
	//111121 by kim.min
	VPORT_L9B0_Wr01(iris_023, reg_nstd_hysis, 0x7);
	VPORT_L9B0_WrFL(iris_023);

	//111122 by gogosing
	VPORT_L9B0_RdFL(iris_063);
	VPORT_L9B0_Wr01(iris_063, reg_field_latency, 0x5);	//from default value 0x3
	VPORT_L9B0_WrFL(iris_063);

#if 0
	// 110506 by kim.min
	//gogosing dcrestore_accum_width value change 0x1b --> 0x25 for stable clamp 20110815
	VPORT_L9B0_RdFL(iris_073);
	VPORT_L9B0_Wr02(iris_073, reg_syncmid_filter_en, 0x0, reg_dcrestore_accum_width, 0x25);//gogosing
	VPORT_L9B0_WrFL(iris_073);
#else
	// 110823 by kim.min
	VPORT_L9B0_RdFL(iris_073);
	//VPORT_L9B0_Wr02(iris_073, reg_syncmid_filter_en, 0x1, reg_dcrestore_accum_width, 0x1b);
	// 111102 by kim.min : for brazil PAL-M weak RF
	//VPORT_L9B0_Wr06(iris_073, reg_dcrestore_gain, 0x3, reg_syncmid_nobp_en, 0x1, reg_dcrestore_kill_enable, 0x1, reg_dcrestore_no_bad_bp, 0x1, reg_syncmid_filter_en, 0x1, reg_dcrestore_accum_width, 0x25);
	// 111114 by kim.min : modified reg_dcrestore_gain to 0x1(from 0x3, default 0x0) to fix H/V unlock problem on full white pattern.
	// 111121 by kim.min : modified reg_dcrestore_gain to 0x0(from 0x3, default 0x0)
	// 111121 by kim.min : modified reg_syncmid_nobp_en to 0x0(from 0x1, default 0x0)
	//VPORT_L9B0_Wr06(iris_073, reg_dcrestore_gain, 0x0, reg_syncmid_nobp_en, 0x0, reg_dcrestore_kill_enable, 0x1, reg_dcrestore_no_bad_bp, 0x1, reg_syncmid_filter_en, 0x1, reg_dcrestore_accum_width, 0x25);
	//111129 wonsik.do : dcrestore_accum_width is need to changed by color system
	VPORT_L9B0_Wr05(iris_073, reg_dcrestore_gain, 0x0, reg_syncmid_nobp_en, 0x0, reg_dcrestore_kill_enable, 0x1, reg_dcrestore_no_bad_bp, 0x1, reg_syncmid_filter_en, 0x1);
	VPORT_L9B0_WrFL(iris_073);
#endif
	// 111102 by kim.min : for brazil PAL-M weak RF
	VPORT_L9B0_RdFL(iris_070);
	VPORT_L9B0_Wr01(iris_070, reg_cagc_tc_ismall, 0x2);
	VPORT_L9B0_WrFL(iris_070);
	VPORT_L9B0_RdFL(iris_071);
	VPORT_L9B0_Wr02(iris_071, reg_cagc_tc_ibig, 0x1, reg_cagc_tc_p, 0x3);
	VPORT_L9B0_WrFL(iris_071);
	VPORT_L9B0_RdFL(iris_183);
	VPORT_L9B0_Wr03(iris_183, reg_cs_cagc_tc_ismall, 0x2, reg_cs_cagc_tc_ibig, 0x1, reg_cs_cagc_tc_p, 0x3);
	VPORT_L9B0_WrFL(iris_183);
	VPORT_L9B0_RdFL(iris_194);
	VPORT_L9B0_Wr03(iris_194, reg_cs1_cagc_tc_ismall, 0x2, reg_cs1_cagc_tc_ibig, 0x1, reg_cs1_cagc_tc_p, 0x3);
	VPORT_L9B0_WrFL(iris_194);


	// 110929 wonsik.do : restore to default value(agc_peak), for AWC test
	// Fast AGC operation : 110729
#ifdef L9_SLOW_AGC_WORKAROUND
	VPORT_L9B0_RdFL(iris_024);
	VPORT_L9B0_Wr01(iris_024, reg_agc_peak_nominal, 0x7F);	//Default : 0x0A
	VPORT_L9B0_Wr01(iris_024, reg_agc_peak_cntl, 0x0);		//Default : 0x1
	VPORT_L9B0_WrFL(iris_024);
#endif

	// At first, VDAC power should be turned off to hide transient artifact : 110803
	CVD_L9Bx_OnOff_VDAC(FALSE);

#if 0
	// by gogosing
	// Use fixed syncmid point, to enhance sync stability on weak RF signal.
	VPORT_L9B0_RdFL(iris_054);
	VPORT_L9B0_Wr01(iris_054, reg_cpump_fixed_syncmid, 0x1);
	// always reset accumulators when no-signal// gogosing 원복 as default 0x01
	//VPORT_L9B0_Wr01(iris_054, reg_cpump_accum_mode, 0x0);
	VPORT_L9B0_WrFL(iris_054);
#else
	VPORT_L9B0_RdFL(iris_054);
	VPORT_L9B0_Wr01(iris_054, reg_cpump_fixed_syncmid, 0x0);
	VPORT_L9B0_Wr01(iris_054, reg_cpump_accum_mode, 0x0);
	VPORT_L9B0_WrFL(iris_054);
#endif

	// #### iris_014 Register Settings From Program_Color_System_Main_Multi ####
	VPORT_L9B0_RdFL(iris_014);
	// For faster agc speed at channel change, set agc_half_en value to '0'
	VPORT_L9B0_Wr01(iris_014, reg_agc_half_en, 0);
	// For faster agc speed at channel change, set hagc_field_mode value to '1'
	//VPORT_L9B0_Wr01(iris_014, reg_hagc_field_mode, 1);
	VPORT_L9B0_WrFL(iris_014);

#ifdef L9_USE_SYNCTIP_ONLY_MODE
	//gogosing reg_hmgc 0x40 --> 0x60 with sync tip mode clamp
	VPORT_L9B0_RdFL(iris_075);
	VPORT_L9B0_Wr01(iris_075, reg_hmgc, 0x60);
	VPORT_L9B0_WrFL(iris_075);

	VPORT_L9B0_RdFL(iris_014);
	// dc_clamp_mode : 0(auto), 1(backporch), 2(synctip), 3(off)
	VPORT_L9B0_Wr01(iris_014, reg_dc_clamp_mode, 0x2);
	VPORT_L9B0_WrFL(iris_014);
#else
	VPORT_L9B0_RdFL(iris_075);
	VPORT_L9B0_Wr01(iris_075, reg_hmgc, 0x60);
	VPORT_L9B0_WrFL(iris_075);

	VPORT_L9B0_RdFL(iris_014);
	// dc_clamp_mode : 0(auto), 1(backporch), 2(synctip), 3(off)
	VPORT_L9B0_Wr01(iris_014, reg_dc_clamp_mode, 0x0);
	VPORT_L9B0_WrFL(iris_014);
#endif

	//110823 : New setting values by kim.min
	VPORT_L9B0_RdFL(iris_053);
	VPORT_L9B0_Wr01(iris_053, reg_cpump_auto_stip_noisy, 0x1);
	VPORT_L9B0_Wr01(iris_053, reg_cpump_auto_stip_no_signal, 0x1);
	VPORT_L9B0_Wr01(iris_053, reg_cpump_auto_stip_unlocked, 0x1);
	VPORT_L9B0_WrFL(iris_053);


	/*
	//110901 : Start RGB Initail settings.
	VPORT_L9B0_RdFL(fastblank_009);
	VPORT_L9B0_RdFL(fastblank_010);
	VPORT_L9B0_Wr01(fastblank_009, reg_fb_vstart_odd, 0x9);
	VPORT_L9B0_Wr01(fastblank_010, reg_fb_vstart_even, 0xa);
	//VPORT_L9B0_Wr01(fastblank_010, reg_fb_height_half, 0x9);
	VPORT_L9B0_Wr01(fastblank_010, reg_fb_hstart, 0x96);
	VPORT_L9B0_WrFL(fastblank_009);
	VPORT_L9B0_WrFL(fastblank_010);
	 */

	//0906 : filed inversion is needed ???
	//0909 : CVD filed inversion
	VPORT_L9B0_RdFL(iris_042);
	//VPORT_L9B0_Wr01(iris_042, reg_field_polarity, 0x1);	// setting to '1' inverts CVD odd/even field
	VPORT_L9B0_Wr01(iris_042, reg_field_polarity, 0x0);	// setting to '1' inverts CVD odd/even field
	VPORT_L9B0_WrFL(iris_042);

	//111104 by kim.min : picture blinking on weak RF signal
	VPORT_L9B0_RdFL(iris_016);
	VPORT_L9B0_Wr01(iris_016, reg_noise_thresh, 0x80);	// default 0x32
	VPORT_L9B0_WrFL(iris_016);

	//111121 kim.min : modified SCART RGB CSC.
	CVD_L9Bx_Set_SCART_CSC();

	//111221 by kim.min for better color standard detection performance
	VPORT_L9B0_RdFL(iris_187);
	VPORT_L9B0_Wr01(iris_187, reg_cs_chroma_sel, 0x1);	// default 0x0
	VPORT_L9B0_WrFL(iris_187);
	VPORT_L9B0_RdFL(iris_198);
	VPORT_L9B0_Wr01(iris_198, reg_cs1_chroma_sel, 0x1);	// default 0x0
	VPORT_L9B0_WrFL(iris_198);

#ifdef L9_CVD_INIT_OADJ_C
	VPORT_L9B0_RdFL(iris_120);
	VPORT_L9B0_Wr01(iris_120, reg_oadj_c_offi, 0x600);	// 2012.02.24 won.hur
	VPORT_L9B0_Wr01(iris_120, reg_oadj_c_offo, 0x200);	// 2012.02.24 won.hur
	VPORT_L9B0_WrFL(iris_120);

	VPORT_L9B0_RdFL(iris_121);
	VPORT_L9B0_Wr01(iris_121, reg_oadj_c_coeff, 0x1000);	// 2012.02.24 won.hur
	VPORT_L9B0_WrFL(iris_121);
#endif


#ifdef L9_FAST_3DCOMB_WORKAROUND
	//120218 for fast 3D Comb operation
	VPORT_L9B0_RdFL(iris_066);
	VPORT_L9B0_Wr01(iris_066, reg_vf_nstd_en, 0x0);	// default 0x1
	VPORT_L9B0_WrFL(iris_066);
#endif

}

int CVD_L9Bx_Set_Source_Type(UINT32 arg)
{
	LX_AFE_CVD_SET_INPUT_T	cvd_input_info;
	//AFE_PRINT("Entered CVD_Set_Source_Type\n");
	if (copy_from_user(&cvd_input_info, (void __user *)arg, sizeof(LX_AFE_CVD_SET_INPUT_T)))
	{
		AFE_PRINT("Error return at CVD_Set_Source_Type\n");
		return -1;
	}
	//		AFE_PRINT("Main CVD input\n");

	//120118 : first disable SCART FB at source change
	CVD_L9Bx_Set_Scart_FB_En(0);
	gEnableScartFB = 0;

	if(cvd_input_info.cvd_input_source_type == LX_CVD_INPUT_SOURCE_CVBS) // for composite
	{

		/*
		//TODO:dws (below CTOP register settings should be move to source control function.
		CTOP_CTRL_L9_RdFL(ctr26);
		//exta select to ch3afe clock
		CTOP_CTRL_L9_Wr01(ctr26, exta_sel, 0x0);
		// Clock divider selection for channel input A into DE to 1/2
		CTOP_CTRL_L9_Wr01(ctr26, msclk_sel, 0x1);
		CTOP_CTRL_L9_WrFL(ctr26);

		// lvds clock select to 1/2
		CTOP_CTRL_L9_RdFL(ctr27);
		CTOP_CTRL_L9_Wr01(ctr27, lvds_clk_sel, 0x1);
		CTOP_CTRL_L9_Wr01(ctr27, swrst_cvd54, 0x0);
		CTOP_CTRL_L9_Wr01(ctr27, swrst_cvd27, 0x0);
		CTOP_CTRL_L9_Wr01(ctr27, swrst_vbi, 0x0);
		CTOP_CTRL_L9_Wr01(ctr27, swrst_scart, 0x0);
		CTOP_CTRL_L9_WrFL(ctr27);
		 */

		//			AFE_PRINT("Composite input\n");
		VPORT_L9B0_RdFL(iris_012);
		VPORT_L9B0_Wr01(iris_012, reg_yc_src, 0);
		VPORT_L9B0_WrFL(iris_012);
		CVD_DEBUG("Input source = [%d]\n", cvd_input_info.cvbs_input_port);
		//gVportRegBx->top_002.reg_exta_sel = 0;	// from cvd_test.cmm
		//gVportRegBx->top_002.reg_extb_sel = 0;	// from cvd_test.cmm
		switch(cvd_input_info.cvbs_input_port)
		{
			case LX_AFE_CVBS_IN1:
				VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
				gafe_cvbs_3_bx.cvbs_insel = 0x2;
				VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
				break;
			case LX_AFE_CVBS_IN2:
				VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
				gafe_cvbs_3_bx.cvbs_insel = 0x3;
				VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
				break;
			case LX_AFE_CVBS_IN3:
				VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
				gafe_cvbs_3_bx.cvbs_insel = 0x0;
				VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
				break;
			case LX_AFE_CVBS_IN4:
				VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
				gafe_cvbs_3_bx.cvbs_insel = 0x1;
				VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
				break;
			case LX_AFE_CVBS_IN5:
				VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
				gafe_cvbs_3_bx.cvbs_insel = 0x4;
				VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
				break;
			case LX_AFE_CVBS_IN6:
				VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
				gafe_cvbs_3_bx.cvbs_insel = 0x5;
				VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
				break;
			default:
				break;
		}
	}
	else // for S-Video
	{
		AFE_PRINT("S-Video is not supported.\n");
	}
	//Current_State = CVD_STATE_VideoNotReady;
	//Next_State = CVD_STATE_VideoNotReady;
	return 0;
}

int CVD_L9Bx_Set_Scart_Overlay(BOOLEAN arg)
{
	if(arg == TRUE)
	{
		// 110901 : L9B0 Scart RGB register setting.
		// Moved to Reg_Init
		/*
		CTOP_CTRL_L9B_RdFL(ctr26_reg_extclk_div_sel);
		CTOP_CTRL_L9B_Wr01(ctr26_reg_extclk_div_sel, reg_ch3pix_clk_sel, 0x1);
		CTOP_CTRL_L9B_WrFL(ctr26_reg_extclk_div_sel);
		*/

		//20111110 : modified not to directly set reg_fb_en register. reg_fb_en is set in ADC periodic task.
		gEnableScartFB = 1;
		/*
		VPORT_L9B0_RdFL(fastblank_001);
		VPORT_L9B0_Wr01(fastblank_001, reg_fb_en, 0x1);
		VPORT_L9B0_WrFL(fastblank_001);
		*/
		// Following Register settings were move to CVD_L9Ax_Reg_Init
		/*
		   gVportRegBx->fastblank_001.reg_fb_2line_delay = 0x1;
		   gVportRegBx->fastblank_001.reg_fb_blend_ratio = 0x8;
		   gVportRegBx->fastblank_001.reg_fb3ch_delay = 0xC;
		   gVportRegBx->fastblank_001.reg_fb_latency = 0x16;
		 */
	}
	else
	{
		//20111110 : modified not to directly set reg_fb_en register. reg_fb_en is set in ADC periodic task.
		gEnableScartFB = 0;
		//20111221 : scart FB enable should be disabled immediately (ADC periodic task can go to sleep state on AV/ATV input condition)
		//20120118 : If SCART Fast Blanking toggle, immediate call to Scart FB EN result in screen flickering.
	//	CVD_L9Bx_Set_Scart_FB_En(0);	// Disable FB_EN
		/*
		VPORT_L9B0_RdFL(fastblank_001);
		VPORT_L9B0_Wr01(fastblank_001, reg_fb_en, 0x0);
		VPORT_L9B0_WrFL(fastblank_001);
		*/
		//		gVportRegBx->fastblank_001.reg_fb_blend_ratio = 0x8;
	}
	return 0;
}

int CVD_L9Bx_Get_Scart_FB_En(void)
{
	int ret;
	VPORT_L9B0_RdFL(fastblank_001);
	VPORT_L9B0_Rd01(fastblank_001, reg_fb_en, ret);
	return ret;
}

int CVD_L9Bx_Set_Scart_FB_En(int fb_en_ctrl)
{
	int ret = 0;
	static int fb_en_status = 0;
	VPORT_L9B0_RdFL(fastblank_001);

	if( (fb_en_ctrl > 0) && (fb_en_status == 0))  {
		VPORT_L9B0_Wr01(fastblank_001, reg_fb_en, 0x1);
		fb_en_status = 1;
	}
	else if ( (fb_en_ctrl == 0) && (fb_en_status > 0) ) {
		VPORT_L9B0_Wr01(fastblank_001, reg_fb_en, 0x0);
		fb_en_status = 0;
	}
	else
		ret = -1;

	VPORT_L9B0_WrFL(fastblank_001);
	return ret;
}

UINT8 CVD_L9Bx_Get_FC_Flag(LX_AFE_CVD_SELECT_T select_main_sub)
{
	UINT8 cordic_freq_status = 0;

	VPORT_L9B0_RdFL(iris_008);
	VPORT_L9B0_Rd01(iris_008, reg_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	if(cordic_freq_status > FC_MORE_THRESHOLD)
		return CVD_FC_MORE_FLAG;
	else if(cordic_freq_status < FC_LESS_THRESHOLD)
		return CVD_FC_LESS_FLAG;
	else
		return CVD_FC_SAME_FLAG;
}

#if 1
//gogosing burst mag status check for color burst level test (color 틀어짐 대응) 2011.06.11
UINT8 CVD_L9Bx_Get_CVD_Burst_Mag_Flag(CVD_STATE_T	color_system)
{
	UINT16 burst_mag_status;
	VPORT_L9B0_RdFL(iris_004);
	VPORT_L9B0_Rd01(iris_004,reg_status_burst_mag,burst_mag_status);

	//111212 by kd.park for MBC low burst magnitude
	if(color_system == CVD_STATE_NTSC) {
		if (g_CVD_Pattern_Detection_t.pattern_found == 1 ) {	// New Pattern Detection using Global Motion Value
			if(burst_mag_status > 0x650)
				return CVD_BURST_MAG_STATE_BIG; // big : 3
			else if(burst_mag_status < 0x520 && burst_mag_status > 0x420)
				return CVD_BURST_MAG_STATE_SMALL; // small : 2
			else if(burst_mag_status < 0x240)
				return CVD_BURST_MAG_STATE_VERY_SMALL; //very small : 1
			else
				return CVD_BURST_MAG_STATE_SAME; // same : 0
		}
		else
			return CVD_BURST_MAG_STATE_BIG; // big : 3
	}
	else {
	// Pattern detection for PAL disabled
	//	if (g_CVD_AGC_Peak_Nominal_Control.pattern_found == 1 ) {	// PAL RF with test pattern detected ???
			if(burst_mag_status > 0x520)//0x620 --> 0x520
				return CVD_BURST_MAG_STATE_BIG; // big : 3
			else if(burst_mag_status < 0x420 && burst_mag_status > 0x320)
				return CVD_BURST_MAG_STATE_SMALL; // small : 2
			else if(burst_mag_status < 0x240)
				return CVD_BURST_MAG_STATE_VERY_SMALL; //very small : 1
			else
				return CVD_BURST_MAG_STATE_SAME; // same : 0
	//	}
	//	else
	//		return CVD_BURST_MAG_STATE_BIG; // big : 3
	}
}

int CVD_L9Bx_Set_CVD_CAGC(UINT8 state,CVD_SET_SYSTEM_MAIN_T *pSet_system_t, CVD_STATE_T	color_system)
{
#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
	int color_compensator_value;
	int oadj_c_coeff_value;
#endif
#ifdef CVD_REG_SATURATION_ADJUST
	int saturation_value;
#endif

	if(state==0)
 		return 0;//not changed

    switch(state)
	{
		case 3: //big
			VPORT_L9B0_RdFL(iris_021);
			if(g_CVD_Status_3CS.in_rf_mode == TRUE) {
				VPORT_L9B0_Wr01(iris_021, reg_cagc, pSet_system_t->reg_cagc);

				CVD_DEBUG("CAGC Value : [0x%x]\n", pSet_system_t->reg_cagc);
				if(color_system == CVD_STATE_NTSC) {

#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
					color_compensator_value = 0 ;
					oadj_c_coeff_value = color_compensator_value + g_initial_c_coeff;
					VPORT_L9B0_RdFL(iris_121);
					VPORT_L9B0_Wr01(iris_121, reg_oadj_c_coeff, oadj_c_coeff_value);
					VPORT_L9B0_WrFL(iris_121);
					CVD_DEBUG("Saturation Value : [0x%x]\n", oadj_c_coeff_value);
#endif
#ifdef CVD_REG_SATURATION_ADJUST
					saturation_value = pSet_system_t->reg_saturation ;
					VPORT_L9B0_RdFL(iris_020);
					VPORT_L9B0_Wr01(iris_020, reg_saturation, saturation_value);
					VPORT_L9B0_WrFL(iris_020);
//					CVD_DEBUG("Saturation Value : [0x%x]\n", saturation_value);
#endif
				}
			}
			else
				VPORT_L9B0_Wr01(iris_021, reg_cagc, pSet_system_t->reg_cagc_av);
			VPORT_L9B0_WrFL(iris_021);
			break;

		case 2: // small
			VPORT_L9B0_RdFL(iris_021);
			if(color_system == CVD_STATE_NTSC) {
				if (g_CVD_AGC_Peak_Nominal_Control.pattern_found == 1 ) {	// NTSC RF with test pattern detected ???
					VPORT_L9B0_Wr01(iris_021, reg_cagc,0x50); //120109 by kd.park for test pattern
					CVD_DEBUG("CAGC Value : [0x%x]\n", 0x50);
				}
				else {
					VPORT_L9B0_Wr01(iris_021, reg_cagc,0x50); //111212 by kd.park for MBC low burst magnitude
					CVD_DEBUG("CAGC Value : [0x%x]\n", 0x50);
				}
			}
			else {
				VPORT_L9B0_Wr01(iris_021, reg_cagc,0x45); //0x45); color 수평 noise 대응 0x45 --> 0x2c
				CVD_DEBUG("CAGC Value : [0x%x]\n", 0x45);
			}
			VPORT_L9B0_WrFL(iris_021);
			break;

		case 1: // very small
			VPORT_L9B0_RdFL(iris_021);

			if(color_system == CVD_STATE_NTSC) {
				VPORT_L9B0_Wr01(iris_021, reg_cagc,0x20); //120127 : by kd.park

				CVD_DEBUG("CAGC Value : [0x%x]\n", 0x20);
#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
				color_compensator_value = (0x80 - 0x20) * 0x20 ;
				oadj_c_coeff_value = color_compensator_value + g_initial_c_coeff;
				VPORT_L9B0_RdFL(iris_121);
				VPORT_L9B0_Wr01(iris_121, reg_oadj_c_coeff, oadj_c_coeff_value);
				VPORT_L9B0_WrFL(iris_121);
				CVD_DEBUG("Saturation Value : [0x%x]\n", oadj_c_coeff_value);
#endif
#ifdef CVD_REG_SATURATION_ADJUST
				saturation_value = pSet_system_t->reg_saturation + (0x80 - 0x20);
				VPORT_L9B0_RdFL(iris_020);
				VPORT_L9B0_Wr01(iris_020, reg_saturation, saturation_value);
				VPORT_L9B0_WrFL(iris_020);
				//					CVD_DEBUG("Saturation Value : [0x%x]\n", saturation_value);
#endif
			}
			else
				VPORT_L9B0_Wr01(iris_021, reg_cagc,0x2c); //0x45); color 수평 noise 대응 0x45 --> 0x2c

			VPORT_L9B0_WrFL(iris_021);
			break;

		default:
			if( (color_system == CVD_STATE_NTSC) && (state >= 20)) {

				if(state > 0x80)
					state = 0x80;

				VPORT_L9B0_RdFL(iris_021);

				VPORT_L9B0_Wr01(iris_021, reg_cagc, state);

				VPORT_L9B0_WrFL(iris_021);
				CVD_DEBUG("CAGC Value : [0x%x]\n", state);

#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
					color_compensator_value = (0x80 - state) * 0x20 ;
					oadj_c_coeff_value = color_compensator_value + g_initial_c_coeff;
					VPORT_L9B0_RdFL(iris_121);
					VPORT_L9B0_Wr01(iris_121, reg_oadj_c_coeff, oadj_c_coeff_value);
					VPORT_L9B0_WrFL(iris_121);
					CVD_DEBUG("Saturation Value : [0x%x]\n", oadj_c_coeff_value);
#endif
#ifdef CVD_REG_SATURATION_ADJUST
				saturation_value = pSet_system_t->reg_saturation + (0x80 - state);
				VPORT_L9B0_RdFL(iris_020);
				VPORT_L9B0_Wr01(iris_020, reg_saturation, saturation_value);
				VPORT_L9B0_WrFL(iris_020);

//				CVD_DEBUG("Saturation Value : [0x%x]\n", saturation_value);
#endif
			}

			break;
	}

	return 0;
}
#endif

UINT8 CVD_L9Bx_Get_Cordic_Freq(LX_AFE_CVD_SELECT_T select_main_sub)
{
	UINT8 cordic_freq_status = 0;

	VPORT_L9B0_RdFL(iris_008);
	VPORT_L9B0_Rd01(iris_008, reg_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	return cordic_freq_status;
}

UINT8 CVD_L9Bx_Get_Cordic_Freq_CS0(void)
{
	UINT8 cordic_freq_status;
	VPORT_L9B0_RdFL(iris_188);
	VPORT_L9B0_Rd01(iris_188, reg_cs_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);
	return cordic_freq_status;
}

UINT8 CVD_L9Bx_Get_FC_Flag_CS0(void)
{
	UINT8 cordic_freq_status;

	VPORT_L9B0_RdFL(iris_188);
	VPORT_L9B0_Rd01(iris_188, reg_cs_status_cordic_freq, cordic_freq_status);

	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	if(cordic_freq_status > FC_MORE_THRESHOLD)
		return CVD_FC_MORE_FLAG;
	else if(cordic_freq_status < FC_LESS_THRESHOLD)
		return CVD_FC_LESS_FLAG;
	else
		return CVD_FC_SAME_FLAG;
}

UINT8 CVD_L9Bx_Get_Cordic_Freq_CS1(void)
{
	UINT8 cordic_freq_status;
	VPORT_L9B0_RdFL(iris_199);
	VPORT_L9B0_Rd01(iris_199, reg_cs1_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);
	return cordic_freq_status;
}

UINT8 CVD_L9Bx_Get_FC_Flag_CS1(void)
{
	UINT8 cordic_freq_status;

	VPORT_L9B0_RdFL(iris_199);
	VPORT_L9B0_Rd01(iris_199, reg_cs1_status_cordic_freq, cordic_freq_status);

	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	if(cordic_freq_status > FC_MORE_THRESHOLD)
		return CVD_FC_MORE_FLAG;
	else if(cordic_freq_status < FC_LESS_THRESHOLD)
		return CVD_FC_LESS_FLAG;
	else
		return CVD_FC_SAME_FLAG;
}

int CVD_L9Bx_Get_FB_Status(UINT32 arg)
{
	LX_AFE_SCART_MODE_T		scart_fb_mode;
	UINT8	scart_fb_state;
	VPORT_L9B0_RdFL(fast_blank_status_001);
	VPORT_L9B0_Rd01(fast_blank_status_001, reg_fb_state, scart_fb_state);
	if(scart_fb_state > 0)
		scart_fb_mode = LX_SCART_MODE_RGB;
	else
		scart_fb_mode = LX_SCART_MODE_CVBS;
	if (copy_to_user((UINT32*)arg, (UINT32*)&scart_fb_mode, sizeof(LX_AFE_SCART_MODE_T)))
	{
		return -EFAULT;
	}
	return 0;
}

int CVD_L9Bx_Get_Scart_AR(UINT32 arg)
{
	LX_AFE_SCART_AR_INFO_T	scart_ar_param;
	UINT8	sc1_sid1, sc1_sid2;
	if (copy_from_user(&scart_ar_param, (void __user *)arg, sizeof(LX_AFE_SCART_AR_INFO_T)))
	{
		return -EFAULT;
	}
	if(scart_ar_param.Scart_Id == LX_SCART_ID_1)
	{
		VPORT_I2C_Read((UINT32*)&gafe_3ch_6_bx);
		sc1_sid1 = gafe_3ch_6_bx.afe3ch_sc1_sid1;
		sc1_sid2 = gafe_3ch_6_bx.afe3ch_sc1_sid2;

		if((sc1_sid2==0)&&(sc1_sid1==0))
			scart_ar_param.Scart_AR = LX_SCART_AR_INVALID;
		else if((sc1_sid2==1)&&(sc1_sid1==1))
			scart_ar_param.Scart_AR = LX_SCART_AR_4_3;
		else
			scart_ar_param.Scart_AR = LX_SCART_AR_16_9;
	}

	if (copy_to_user((UINT32*)arg, (UINT32*)&scart_ar_param, sizeof(LX_AFE_SCART_AR_INFO_T)))
	{
		return -EFAULT;
	}
	return 0;
}

void CVD_L9Bx_Print_Vport_Version(void)
{
	UINT32 vport_version = 0;
	VPORT_L9B0_RdFL(top_001);
	VPORT_L9B0_Rd01(top_001, iris_ver, vport_version);
	AFE_PRINT("Vport Version : [%x]\n", vport_version);
}

int CVD_L9Bx_Vport_Output(UINT32 arg)
{
	// No more use

	return 0;
}

int CVD_L9Bx_Vport_Reg_Read(UINT32 arg)
{
	UINT32 value;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	LX_AFE_REG_RW_T reg_addr_data_t;
	if (copy_from_user(&reg_addr_data_t, (void __user *)arg, sizeof(LX_AFE_REG_RW_T)))
	{
		return -EFAULT;
	}
	do {
		recvAddr = reg_addr_data_t.addr;
		/*
		   if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DE_BASE;
		   else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;
		 */
		recvAddr += (UINT32)gpRealRegVPORT_L9B0;
		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;
		value = REG_RD(currAddr);
		if (currAddr == recvAddr) break;
		nextValue = REG_RD(currAddr+4);
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		value  = GET_BITS(value, dBit, wBit);
		value += GET_PVAL(nextValue, wBit, dBit);
	} while (0);
	reg_addr_data_t.data = value;
	if (copy_to_user((UINT32*)arg, (UINT32*)&reg_addr_data_t, sizeof(LX_AFE_REG_RW_T)))
	{
		return -EFAULT;
	}
	return 0;
}

int CVD_L9Bx_Vport_Reg_Write(UINT32 arg)
{
	UINT32 value;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 currValue;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	LX_AFE_REG_RW_T reg_addr_data_t;
	if (copy_from_user(&reg_addr_data_t, (void __user *)arg, sizeof(LX_AFE_REG_RW_T)))
	{
		return -EFAULT;
	}
	do {
		recvAddr = reg_addr_data_t.addr;
		value = reg_addr_data_t.data;
		/*
		   if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DE_BASE;
		   else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;
		 */
		recvAddr += (UINT32)gpRealRegVPORT_L9B0;
		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;
		if (currAddr == recvAddr) {
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(currAddr);
		nextValue = REG_RD((currAddr+4));
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		currValue  = GET_BITS(currValue ,0	  ,dBit);
		currValue += GET_PVAL(value		,dBit ,wBit);
		nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
		nextValue += GET_BITS(value		,0	  ,dBit);
		REG_WD(currAddr		,currValue);
		REG_WD((currAddr+4) ,nextValue);
	} while (0);
	return 0;
}

int CVD_L9Bx_Get_No_Signal_Flag(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_001);
	VPORT_L9B0_Rd01(iris_001, reg_no_signal, ret);
	return ret;
}

int CVD_L9Bx_Get_HLock_Flag(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_001);
	VPORT_L9B0_Rd01(iris_001, reg_hlock, ret);
	return ret;
}

int CVD_L9Bx_Get_VLock_Flag(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_001);
	VPORT_L9B0_Rd01(iris_001, reg_vlock, ret);
	return ret;
}

int CVD_L9Bx_Get_Vline_625_Flag(void)
{
	//return 1;
	static int wrong_vline_count = 0;
	static int vline_625_count = 0;
	static int vline_525_count = 0;
	int ret, vline_reg, vcount;
	VPORT_L9B0_RdFL(iris_002);
	VPORT_L9B0_Rd01(iris_002, reg_vline_625_detected, ret);

	VPORT_L9B0_RdFL(iris_012);
	VPORT_L9B0_Rd01(iris_012, reg_vline_625, vline_reg);

	VPORT_L9B0_RdFL(iris_273);
	VPORT_L9B0_Rd01(iris_273, reg_status_vdetect_vcount, vcount);

	if( (vline_reg == 0x1) && (ret == 0x1) && (vcount > 0x340) && (vcount < 0x350) && (CVD_L9Bx_Get_VLock_Flag() > 0))			// 0x344
	{
		CVD_DEBUG("!525 line ???, vcount = [0x%x]\n", vcount);
		wrong_vline_count ++;
	}
	else
		wrong_vline_count = 0;

	if( (vline_reg == 0x0) && (ret == 0x1) && (CVD_L9Bx_Get_VLock_Flag() > 0) &&( vcount < 0x250) && (vcount > 0x230) )	// 0x23e
	{
		CVD_DEBUG("625 line ???, vcount = [0x%x]\n", vcount);
		vline_625_count ++;
	}
	else
		vline_625_count = 0;

	if( (vline_reg == 0x1) && (ret == 0x0) && (CVD_L9Bx_Get_VLock_Flag() > 0))	// 0x23e
	{
		CVD_DEBUG("525 line ???, vcount = [0x%x]\n", vcount);
		vline_525_count ++;
	}
	else
		vline_525_count = 0;

	if (wrong_vline_count > 1)
	{
		wrong_vline_count = 0;
		CVD_DEBUG("Force Set vline to 525 line\n");
		VPORT_L9B0_Wr01(iris_012, reg_vline_625, 0);
		VPORT_L9B0_WrFL(iris_012);
	}
	else if( vline_625_count > 1)
	{
		vline_625_count = 0;
		CVD_DEBUG("Set vline to 625 line\n");
		VPORT_L9B0_Wr01(iris_012, reg_vline_625, 1);
		VPORT_L9B0_WrFL(iris_012);
	}
	else if( vline_525_count > 1)
	{
		vline_525_count = 0;
		CVD_DEBUG("Set vline to 525 line\n");
		VPORT_L9B0_Wr01(iris_012, reg_vline_625, 0);
		VPORT_L9B0_WrFL(iris_012);
	}

	return ret;
}

int CVD_L9Bx_Get_Vdetect_Vcount_625_Flag(void)
{
	//return 1;
	static int vline_625_flag = 0;
	int vcount;
	VPORT_L9B0_RdFL(iris_273);
	VPORT_L9B0_Rd01(iris_273, reg_status_vdetect_vcount, vcount);

	if( (vcount > 0x1FC) && (vcount < 0x21c))
		vline_625_flag = 0;
	else if( (vcount > 0x260) && (vcount < 0x280))
		vline_625_flag = 1;
	else
		CVD_DEBUG("vcount unstable [%d]\n", vcount);

	return vline_625_flag;
}


int CVD_L9Bx_Get_PAL_Flag(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_002);
	VPORT_L9B0_Rd01(iris_002, reg_pal_detected, ret);
	return ret;
}

int CVD_L9Bx_Get_SECAM_Flag(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_002);
	VPORT_L9B0_Rd01(iris_002, reg_secam_detected, ret);
	return ret;
}

int CVD_L9Bx_Get_Chromalock_Flag(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_001);
	VPORT_L9B0_Rd01(iris_001, reg_chromalock, ret);
	return ret;
}

int CVD_L9Bx_Get_PAL_Flag_CS0(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_189);
	VPORT_L9B0_Rd01(iris_189, reg_cs_pal_detected, ret);
	return ret;
}

int CVD_L9Bx_Get_SECAM_Flag_CS0(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_188);
	VPORT_L9B0_Rd01(iris_188, reg_cs_secam_detected, ret);
	return ret;
}

int CVD_L9Bx_Get_Chromalock_Flag_CS0(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_189);
	VPORT_L9B0_Rd01(iris_189, reg_cs_chromalock, ret);
	return ret;
}

int CVD_L9Bx_Get_PAL_Flag_CS1(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_200);
	VPORT_L9B0_Rd01(iris_200, reg_cs1_pal_detected, ret);
	return ret;
}

int CVD_L9Bx_Get_SECAM_Flag_CS1(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_199);
	VPORT_L9B0_Rd01(iris_199, reg_cs1_secam_detected, ret);
	return ret;
}

int CVD_L9Bx_Get_Chromalock_Flag_CS1(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_200);
	VPORT_L9B0_Rd01(iris_200, reg_cs1_chromalock, ret);
	return ret;
}

int CVD_L9Bx_Get_Noise_Status(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_009);
	VPORT_L9B0_Rd01(iris_009, reg_status_noise, ret);
	return ret;
}

int CVD_L9Bx_Get_NoBurst_Flag(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_002);
	VPORT_L9B0_Rd01(iris_002, reg_noburst_detected, ret);
	return ret;
}

int CVD_L9Bx_Get_CHB_No_Signal_Flag(void)
{
	/* //L8 Code
	VPORT_L9B0_RdFL(chbcvd_039);
	VPORT_L9B0_Rd01(chbcvd_039, chbreg_no_signal, ret);
	*/
#ifdef CHBCVD_SUPPORT
	CHBCVD_L9_RdFL(chbcvd_039);
	CHBCVD_L9_Rd01(chbcvd_039, chbreg_no_signal, ret);
#endif
	return 0;
}

int CVD_L9Bx_Get_CHB_HLock_Flag(void)
{
	/* L8 Code
	VPORT_L9B0_RdFL(chbcvd_039);
	VPORT_L9B0_Rd01(chbcvd_039, chbreg_hlock, ret);
	*/
#ifdef CHBCVD_SUPPORT
	CHBCVD_L9_RdFL(chbcvd_039);
	CHBCVD_L9_Rd01(chbcvd_039, chbreg_hlock, ret);
#endif
	return 0;
}

int CVD_L9Bx_Get_CHB_VLock_Flag(void)
{
	//L8 Code
	//VPORT_L9B0_RdFL(chbcvd_039);
	//VPORT_L9B0_Rd01(chbcvd_039, chbreg_vlock, ret);
#ifdef CHBCVD_SUPPORT
	CHBCVD_L9_RdFL(chbcvd_039);
	CHBCVD_L9_Rd01(chbcvd_039, chbreg_vlock, ret);
#endif
	return 0;
}

int CVD_L9Bx_Get_CHB_Chromalock_Flag(void)
{
	//L8 Code
	//VPORT_L9B0_RdFL(chbcvd_039);
	//VPORT_L9B0_Rd01(chbcvd_039, chbreg_chromalock, ret);
#ifdef CHBCVD_SUPPORT
	CHBCVD_L9_RdFL(chbcvd_039);
	CHBCVD_L9_Rd01(chbcvd_039, chbreg_chromalock, ret);
#endif
	return 0;
}

int CVD_L9Bx_Get_CHB_PAL_Flag(void)
{
	//L8 Code
	//VPORT_L9B0_RdFL(chbcvd_040);
	//VPORT_L9B0_Rd01(chbcvd_040, chbreg_pal_detected, ret);
#ifdef CHBCVD_SUPPORT
	CHBCVD_L9_RdFL(chbcvd_040);
	CHBCVD_L9_Rd01(chbcvd_040, chbreg_pal_detected, ret);
#endif
	return 0;
}

int CVD_L9Bx_Get_CHB_Vline_625_Flag(void)
{
	//L8 Code
	//VPORT_L9B0_RdFL(chbcvd_040);
	//VPORT_L9B0_Rd01(chbcvd_040, chbreg_vline_625_detected, ret);
#ifdef CHBCVD_SUPPORT
	CHBCVD_L9_RdFL(chbcvd_040);
	CHBCVD_L9_Rd01(chbcvd_040, chbreg_vline_625_detected, ret);
#endif
	return 0;
}

int CVD_L9Bx_Get_CHB_SECAM_Flag(void)
{
	//L8 Code
	//VPORT_L9B0_RdFL(chbcvd_040);
	//VPORT_L9B0_Rd01(chbcvd_040, chbreg_secam_detected, ret);
#ifdef CHBCVD_SUPPORT
	CHBCVD_L9_RdFL(chbcvd_040);
	CHBCVD_L9_Rd01(chbcvd_040, chbreg_secam_detected, ret);
#endif
	return 0;
}

int CVD_L9Bx_Reset_irisyc(int enable)
{
	if(enable > 0)
	{
		VPORT_I2C_Read((UINT32*)&gsoft_reset_5_bx);
		gsoft_reset_5_bx.swrst_f54m = 1;
		gsoft_reset_5_bx.swrst_cvbs = 1;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_5_bx);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&gsoft_reset_5_bx);
		gsoft_reset_5_bx.swrst_f54m = 0;
		gsoft_reset_5_bx.swrst_cvbs = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_5_bx);
	}

	return 0;
}

int CVD_L9Bx_Reset_hdct(int enable)
{
	if(enable >0)
	{
		VPORT_L9B0_RdFL(iris_174);
		VPORT_L9B0_Wr01(iris_174, swrst_hdct, 1);
		VPORT_L9B0_WrFL(iris_174);
	}
	else
	{
		VPORT_L9B0_RdFL(iris_174);
		VPORT_L9B0_Wr01(iris_174, swrst_hdct, 0);
		VPORT_L9B0_WrFL(iris_174);
	}
	return 0;
}

int CVD_L9Bx_Reset_cdct(int enable)
{
	if(enable >0)
	{
		VPORT_L9B0_RdFL(iris_174);
		VPORT_L9B0_Wr01(iris_174, swrst_cdct, 1);
		VPORT_L9B0_WrFL(iris_174);
	}
	else
	{
		VPORT_L9B0_RdFL(iris_174);
		VPORT_L9B0_Wr01(iris_174, swrst_cdct, 0);
		VPORT_L9B0_WrFL(iris_174);
	}
	return 0;
}

#if 0
void CVD_L9Bx_Set_AAF_Params(CVD_L9Ax_SET_AAF_T *pSet_aaf_t)
{
	VPORT_L9B0_RdFL(iris_134);
	VPORT_L9B0_Wr01(iris_134, reg_lpf_0_en, pSet_aaf_t->reg_lpf_0_en);
	VPORT_L9B0_Wr01(iris_134, reg_lpf_tap_0_0, pSet_aaf_t->reg_lpf_tap_0_0);
	VPORT_L9B0_WrFL(iris_134);

	VPORT_L9B0_RdFL(iris_135);
	VPORT_L9B0_Wr01(iris_135, reg_lpf_tap_0_1, pSet_aaf_t->reg_lpf_tap_0_1);
	VPORT_L9B0_Wr01(iris_135, reg_lpf_tap_0_2, pSet_aaf_t->reg_lpf_tap_0_2);
	VPORT_L9B0_WrFL(iris_135);

	VPORT_L9B0_RdFL(iris_136);
	VPORT_L9B0_Wr01(iris_136, reg_lpf_tap_0_3, pSet_aaf_t->reg_lpf_tap_0_3);
	VPORT_L9B0_Wr01(iris_136, reg_lpf_tap_0_4, pSet_aaf_t->reg_lpf_tap_0_4);
	VPORT_L9B0_WrFL(iris_136);

	VPORT_L9B0_RdFL(iris_137);
	VPORT_L9B0_Wr01(iris_137, reg_lpf_tap_0_5, pSet_aaf_t->reg_lpf_tap_0_5);
	VPORT_L9B0_Wr01(iris_137, reg_lpf_tap_0_6, pSet_aaf_t->reg_lpf_tap_0_6);
	VPORT_L9B0_WrFL(iris_137);
}

void CVD_L9Bx_Set_ADC_Params(CVD_L9Ax_SET_CRES54MHZ_T *pSet_cresampler_t)
{
	/*
	VPORT_I2C_Read((UINT32*)&gmain_pll_0_bx);
	VPORT_I2C_Read((UINT32*)&gmain_pll_1_bx);
	VPORT_I2C_Read((UINT32*)&gmain_pll_2_bx);
	VPORT_I2C_Read((UINT32*)&gmain_pll_3_bx);
	VPORT_I2C_Read((UINT32*)&gmain_pll_4_bx);

	gmain_pll_0_bx.dr3p_nsc = pSet_cresampler_t->DR3P_NSC;
	gmain_pll_1_bx.dr3p_npc = pSet_cresampler_t->DR3P_NPC;
	gmain_pll_2_bx.dr3p_m = pSet_cresampler_t->DR3P_M;
	gmain_pll_3_bx.dr3p_od_cvdclk = pSet_cresampler_t->DR3P_OD_CVDCLK;
	gmain_pll_3_bx.dr3p_od_recclk = pSet_cresampler_t->DR3P_OD_RECCLK;
	gmain_pll_4_bx.dr3p_ps23c = pSet_cresampler_t->DR3P_PS23C;
	gmain_pll_4_bx.dr3p_cih = pSet_cresampler_t->DR3P_CIH;

	VPORT_I2C_Write((UINT32*)&gmain_pll_0_bx);
	VPORT_I2C_Write((UINT32*)&gmain_pll_1_bx);
	VPORT_I2C_Write((UINT32*)&gmain_pll_2_bx);
	VPORT_I2C_Write((UINT32*)&gmain_pll_3_bx);
	VPORT_I2C_Write((UINT32*)&gmain_pll_4_bx);
	*/
}

void CVD_L9Bx_Set_Cresampler_Params(CVD_L9Ax_SET_CRES54MHZ_T *pSet_cresampler_t)
{
	VPORT_L9B0_RdFL(iris_110);
	VPORT_L9B0_Wr01(iris_110, reg_cres_clksel, pSet_cresampler_t->reg_cres_clksel);
	VPORT_L9B0_Wr01(iris_110, reg_cres_0px_sel, pSet_cresampler_t->reg_cres_0px_sel);
	VPORT_L9B0_Wr01(iris_110, reg_cres_blend_bcdefault, pSet_cresampler_t->reg_cres_blend_bcdefault);
	VPORT_L9B0_WrFL(iris_110);

	VPORT_L9B0_RdFL(iris_102);
	VPORT_L9B0_Wr01(iris_102, reg_iris_cresampler_on, pSet_cresampler_t->reg_iris_cresampler_on);
	VPORT_L9B0_Wr01(iris_102, reg_cres_lpfa_on, pSet_cresampler_t->reg_cres_lpfa_on);
	VPORT_L9B0_Wr01(iris_102, reg_cres_lpfa_coeff0, pSet_cresampler_t->reg_cres_lpfa_coeff0);
	VPORT_L9B0_WrFL(iris_102);

	VPORT_L9B0_RdFL(iris_103);
	VPORT_L9B0_Wr01(iris_103, reg_cres_lpfa_coeff1, pSet_cresampler_t->reg_cres_lpfa_coeff1);
	VPORT_L9B0_Wr01(iris_103, reg_cres_lpfa_coeff2, pSet_cresampler_t->reg_cres_lpfa_coeff2);
	VPORT_L9B0_WrFL(iris_103);

	VPORT_L9B0_RdFL(iris_104);
	VPORT_L9B0_Wr01(iris_104, reg_cres_lpfa_coeff3, pSet_cresampler_t->reg_cres_lpfa_coeff3);
	VPORT_L9B0_Wr01(iris_104, reg_cres_lpfa_coeff4, pSet_cresampler_t->reg_cres_lpfa_coeff4);
	VPORT_L9B0_WrFL(iris_104);

	VPORT_L9B0_RdFL(iris_105);
	VPORT_L9B0_Wr01(iris_105, reg_cres_lpfa_coeff5, pSet_cresampler_t->reg_cres_lpfa_coeff5);
	VPORT_L9B0_WrFL(iris_105);

	VPORT_L9B0_RdFL(iris_106);
	VPORT_L9B0_Wr01(iris_106, reg_cres_lpfb_on, pSet_cresampler_t->reg_cres_lpfb_on);
	VPORT_L9B0_Wr01(iris_106, reg_cres_lpfb_coeff0, pSet_cresampler_t->reg_cres_lpfb_coeff0);
	VPORT_L9B0_WrFL(iris_106);

	VPORT_L9B0_RdFL(iris_107);
	VPORT_L9B0_Wr01(iris_107, reg_cres_lpfb_coeff1, pSet_cresampler_t->reg_cres_lpfb_coeff1);
	VPORT_L9B0_Wr01(iris_107, reg_cres_lpfb_coeff2, pSet_cresampler_t->reg_cres_lpfb_coeff2);
	VPORT_L9B0_WrFL(iris_107);

	VPORT_L9B0_RdFL(iris_108);
	VPORT_L9B0_Wr01(iris_108, reg_cres_lpfb_coeff3, pSet_cresampler_t->reg_cres_lpfb_coeff3);
	VPORT_L9B0_Wr01(iris_108, reg_cres_lpfb_coeff4, pSet_cresampler_t->reg_cres_lpfb_coeff4);
	VPORT_L9B0_WrFL(iris_108);

	VPORT_L9B0_RdFL(iris_117);
	VPORT_L9B0_Wr01(iris_117, reg_dtrs_revalpha_sel, pSet_cresampler_t->reg_dtrs_revalpha_sel);
	VPORT_L9B0_Wr01(iris_117, reg_dtrs_dlysel, pSet_cresampler_t->reg_dtrs_dlysel);
	VPORT_L9B0_WrFL(iris_117);
	//added 20110126
	VPORT_L9B0_RdFL(iris_109);
	VPORT_L9B0_Wr01(iris_109, reg_cres_blend_method, pSet_cresampler_t->reg_cres_blend_method);
	VPORT_L9B0_Wr01(iris_109, reg_cres_blend_sel, pSet_cresampler_t->reg_cres_blend_sel);
	VPORT_L9B0_WrFL(iris_109);
}



// won.hur : This Function must be repaired or deleted due to the delection of
// 2dcomb-related function
// The code related to 2dcomb-function is disabled!
void CVD_L9Bx_Set_Dot_Crawl_Params(CVD_L9Ax_SET_DOT_CRAWL_T *pSet_dotcrawl_t)
{

#if 0 // won.hur Disabled code due to the delection of 2dcomb-related-register

	VPORT_L9B0_RdFL(iris_155);
	VPORT_L9B0_Wr01(iris_155, cvd_2dcomb_byp, pSet_dotcrawl_t->reg_2dcomb_byp);
	VPORT_L9B0_Wr01(iris_155, cvd_2dcomb_cband_sel, pSet_dotcrawl_t->reg_2dcomb_cband_sel);
	VPORT_L9B0_Wr01(iris_155, cvd_2dcomb_ccombo_sel, pSet_dotcrawl_t->reg_2dcomb_ccombo_sel);
	VPORT_L9B0_Wr01(iris_155, cvd_2dcomb_ycrdc_cvsel, pSet_dotcrawl_t->reg_2dcomb_ycrdc_cvsel);
	VPORT_L9B0_Wr01(iris_155, cvd_2dcomb_ycrdc_chsel, pSet_dotcrawl_t->reg_2dcomb_ycrdc_chsel);
	VPORT_L9B0_Wr01(iris_155, cvd_2dcomb_ycrdc_lrsel, pSet_dotcrawl_t->reg_2dcomb_ycrdc_lrsel);
	VPORT_L9B0_WrFL(iris_155);

	VPORT_L9B0_RdFL(iris_156);
	VPORT_L9B0_Wr01(iris_156, cvd_2dcomb_ycrdc_yhsymth, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yhsymth);
	VPORT_L9B0_Wr01(iris_156, cvd_2dcomb_ycrdc_yhdiffth, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yhdiffth);
	VPORT_L9B0_WrFL(iris_156);

	VPORT_L9B0_RdFL(iris_157);
	VPORT_L9B0_Wr01(iris_157, cvd_2dcomb_ycrdc_cvdiffth, pSet_dotcrawl_t->reg_2dcomb_ycrdc_cvdiffth);
	VPORT_L9B0_WrFL(iris_157);

	VPORT_L9B0_RdFL(iris_160);
	VPORT_L9B0_Wr01(iris_160, cvd_2dcomb_ycrdc_yvsel, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvsel);
	VPORT_L9B0_Wr01(iris_160, cvd_2dcomb_ycrdc_yhsel, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yhsel);
	VPORT_L9B0_Wr01(iris_160, cvd_2dcomb_ycrdc_hth_on, pSet_dotcrawl_t->reg_2dcomb_ycrdc_hth_on);
	VPORT_L9B0_Wr01(iris_160, cvd_2dcomb_ycrdc_hth_sel, pSet_dotcrawl_t->reg_2dcomb_ycrdc_hth_sel);
	VPORT_L9B0_Wr01(iris_160, cvd_2dcomb_ycrdc_hth, pSet_dotcrawl_t->reg_2dcomb_ycrdc_hth);
	VPORT_L9B0_WrFL(iris_160);

	VPORT_L9B0_RdFL(iris_158);
	VPORT_L9B0_Wr01(iris_158, cvd_2dcomb_ycrdc_lrtype, pSet_dotcrawl_t->reg_2dcomb_ycrdc_lrtype);
	VPORT_L9B0_Wr01(iris_158, cvd_2dcomb_ycrdc_dsel, pSet_dotcrawl_t->reg_2dcomb_ycrdc_dsel);
	VPORT_L9B0_Wr01(iris_158, cvd_2dcomb_ycrdc_lcr_on, pSet_dotcrawl_t->reg_2dcomb_ycrdc_lcr_on);
	VPORT_L9B0_Wr01(iris_158, cvd_2dcomb_ycrdc_method, pSet_dotcrawl_t->reg_2dcomb_ycrdc_method);
	VPORT_L9B0_WrFL(iris_158);

	VPORT_L9B0_RdFL(iris_225);
	VPORT_L9B0_Wr01(iris_225, cvd_2dcomb_ycrdc_yvdiv_th0, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvdiv_th0);
	VPORT_L9B0_WrFL(iris_225);


	VPORT_L9B0_RdFL(iris_226);
	VPORT_L9B0_Wr01(iris_226, cvd_2dcomb_ycrdc_yvdiv_th1, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvdiv_th1);
	VPORT_L9B0_Wr01(iris_226, cvd_2dcomb_ycrdc_yvdiv_th2, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvdiv_th2);
	VPORT_L9B0_WrFL(iris_226);

	VPORT_L9B0_RdFL(iris_227);
	VPORT_L9B0_Wr01(iris_227, cvd_2dcomb_ycrdc_yvdiv_th3, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvdiv_th3);
	VPORT_L9B0_Wr01(iris_227, cvd_2dcomb_ycrdc_yvdiv_th4, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvdiv_th4);
	VPORT_L9B0_WrFL(iris_227);

	VPORT_L9B0_RdFL(iris_228);
	VPORT_L9B0_Wr01(iris_228, cvd_2dcomb_ycrdc_yvdiv_th5, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvdiv_th5);
	VPORT_L9B0_Wr01(iris_228, cvd_2dcomb_ycrdc_yvdiv_th6, pSet_dotcrawl_t->reg_2dcomb_ycrdc_yvdiv_th6);
	VPORT_L9B0_WrFL(iris_228);

#endif //won.hur

}

//won.hur : This Functino must be repaired or deleted due to the delection of
// 2dcomb-related function
// The code related to 2dcomb-function is disabled!
void CVD_L9Bx_Set_Cross_Color_Reducer(CVD_L9Ax_SET_CROSS_COLOR_REDUCER_T *pSet_crosscolor_t)
{
#if 0 // won.hur : Disabled code due to the delection of 2dcomb-related-register
	VPORT_L9B0_RdFL(iris_161);
	VPORT_L9B0_Wr01(iris_161, cvd_2dcomb_cyrdc_method, pSet_crosscolor_t->reg_2dcomb_cyrdc_method);
	VPORT_L9B0_Wr01(iris_161, cvd_2dcomb_cyrdc_lcr_on, pSet_crosscolor_t->reg_2dcomb_cyrdc_lcr_on);
	VPORT_L9B0_Wr01(iris_161, cvd_2dcomb_cyrdc_crvalid, pSet_crosscolor_t->reg_2dcomb_cyrdc_crvalid);
	VPORT_L9B0_Wr01(iris_161, cvd_2dcomb_cyrdc_lrtype, pSet_crosscolor_t->reg_2dcomb_cyrdc_lrtype);
	VPORT_L9B0_Wr01(iris_161, cvd_2dcomb_cyrdc_dsel, pSet_crosscolor_t->reg_2dcomb_cyrdc_dsel);
	VPORT_L9B0_Wr01(iris_161, cvd_2dcomb_cyrdc_dsel1, pSet_crosscolor_t->reg_2dcomb_cyrdc_dsel1);
	VPORT_L9B0_WrFL(iris_161);

	VPORT_L9B0_RdFL(iris_162);
	VPORT_L9B0_Wr01(iris_162, cvd_2dcomb_cyrdc_chsymth, pSet_crosscolor_t->reg_2dcomb_cyrdc_chsymth);
	VPORT_L9B0_Wr01(iris_162, cvd_2dcomb_cyrdc_chsymth1, pSet_crosscolor_t->reg_2dcomb_cyrdc_chsymth1);
	VPORT_L9B0_WrFL(iris_162);

	VPORT_L9B0_RdFL(iris_230);
	VPORT_L9B0_Wr01(iris_230, cvd_2dcomb_cyrdc_hvth, pSet_crosscolor_t->reg_2dcomb_cyrdc_hvth);
	VPORT_L9B0_Wr01(iris_230, cvd_2dcomb_cyrdc_cvdiv_xsel, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_xsel);
	VPORT_L9B0_Wr01(iris_230, cvd_2dcomb_cyrdc_cvdiv_th0, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_th0);
	VPORT_L9B0_WrFL(iris_230);

	VPORT_L9B0_RdFL(iris_231);
	VPORT_L9B0_Wr01(iris_231, cvd_2dcomb_cyrdc_cvdiv_th1, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_th1);
	VPORT_L9B0_Wr01(iris_231, cvd_2dcomb_cyrdc_cvdiv_th2, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_th2);
	VPORT_L9B0_WrFL(iris_231);

	VPORT_L9B0_RdFL(iris_232);
	VPORT_L9B0_Wr01(iris_232, cvd_2dcomb_cyrdc_cvdiv_th3, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_th3);
	VPORT_L9B0_Wr01(iris_232, cvd_2dcomb_cyrdc_cvdiv_th4, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_th4);
	VPORT_L9B0_WrFL(iris_232);

	VPORT_L9B0_RdFL(iris_233);
	VPORT_L9B0_Wr01(iris_233, cvd_2dcomb_cyrdc_cvdiv_th5, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_th5);
	VPORT_L9B0_Wr01(iris_233, cvd_2dcomb_cyrdc_cvdiv_th6, pSet_crosscolor_t->reg_2dcomb_cyrdc_cvdiv_th6);
	VPORT_L9B0_WrFL(iris_233);

	VPORT_L9B0_RdFL(iris_163);
	VPORT_L9B0_Wr01(iris_163, cvd_2dcomb_cyrdc_chdiffth, pSet_crosscolor_t->reg_2dcomb_cyrdc_chdiffth);
	VPORT_L9B0_WrFL(iris_163);

	VPORT_L9B0_RdFL(iris_164);
	VPORT_L9B0_Wr01(iris_164, cvd_2dcomb_cyrdc_chdiffon, pSet_crosscolor_t->reg_2dcomb_cyrdc_chdiffon);
	VPORT_L9B0_Wr01(iris_164, cvd_2dcomb_cyrdc_chdiffsel, pSet_crosscolor_t->reg_2dcomb_cyrdc_chdiffsel);
	VPORT_L9B0_WrFL(iris_164);

	VPORT_L9B0_RdFL(iris_228);
	VPORT_L9B0_Wr01(iris_228, cvd_2dcomb_cyrdc_dir_on, pSet_crosscolor_t->reg_2dcomb_cyrdc_dir_on);
	VPORT_L9B0_Wr01(iris_228, cvd_2dcomb_cyrdc_v0b1_dinsel, pSet_crosscolor_t->reg_2dcomb_cyrdc_v0b1_dinsel);
	VPORT_L9B0_WrFL(iris_228);

	VPORT_L9B0_RdFL(iris_229);
	VPORT_L9B0_Wr01(iris_229, cvd_2dcomb_cyrdc_v1b4_cinsel, pSet_crosscolor_t->reg_2dcomb_cyrdc_v1b4_cinsel);
	VPORT_L9B0_Wr01(iris_229, cvd_2dcomb_cyrdc_v1b4_dinsel, pSet_crosscolor_t->reg_2dcomb_cyrdc_v1b4_dinsel);
	VPORT_L9B0_Wr01(iris_229, cvd_2dcomb_cyrdc_v1b4_th, pSet_crosscolor_t->reg_2dcomb_cyrdc_v1b4_th);
	VPORT_L9B0_WrFL(iris_229);

	VPORT_L9B0_RdFL(iris_165);
	VPORT_L9B0_Wr01(iris_165, cvd_2dcomb_cyrdc_hth_on, pSet_crosscolor_t->reg_2dcomb_cyrdc_hth_on);
	VPORT_L9B0_Wr01(iris_165, cvd_2dcomb_cyrdc_hth, pSet_crosscolor_t->reg_2dcomb_cyrdc_hth);
	VPORT_L9B0_WrFL(iris_165);

#endif // won.hur

}


// This Function needs to be repaired or delected due to delection of IRIS_189 register
// Code related to IRIS_189 through IRIS_192 is disabled!!
void CVD_L9Bx_Set_Motion_Detector(CVD_L9Ax_SET_MOTION_DETECTOR_T *pSet_motiondetector_t)
{
	VPORT_L9B0_RdFL(iris_062);
	VPORT_L9B0_Wr01(iris_062, reg_motion_mode, pSet_motiondetector_t->reg_motion_mode           );
	VPORT_L9B0_Wr01(iris_062, reg_dot_suppress_mode, pSet_motiondetector_t->reg_dot_suppress_mode     );
//	VPORT_L9B0_Wr01(iris_062, reg_adaptive_chroma_mode, pSet_motiondetector_t->reg_adaptive_chroma_mode  );
	VPORT_L9B0_WrFL(iris_062);

	VPORT_L9B0_RdFL(iris_089);
	VPORT_L9B0_Wr01(iris_089, reg_motion_config, pSet_motiondetector_t->reg_motion_config         );
	VPORT_L9B0_WrFL(iris_089);

	VPORT_L9B0_RdFL(iris_090);
	VPORT_L9B0_Wr01(iris_090, reg_status_motion_mode, pSet_motiondetector_t->reg_status_motion_mode    );
	VPORT_L9B0_WrFL(iris_090);

	VPORT_L9B0_RdFL(iris_091);
	VPORT_L9B0_Wr01(iris_091, reg_flat_luma_shift, pSet_motiondetector_t->reg_flat_luma_shift       );
	VPORT_L9B0_Wr01(iris_091, reg_flat_chroma_shift, pSet_motiondetector_t->reg_flat_chroma_shift     );
	VPORT_L9B0_Wr01(iris_091, reg_flat_luma_offset, pSet_motiondetector_t->reg_flat_luma_offset      );
	VPORT_L9B0_Wr01(iris_091, reg_flat_chroma_offset, pSet_motiondetector_t->reg_flat_chroma_offset    );
	VPORT_L9B0_WrFL(iris_091);

	VPORT_L9B0_RdFL(iris_123);
	VPORT_L9B0_Wr01(iris_123, reg_frame_motion_th0, pSet_motiondetector_t->reg_frame_motion_th0      );
	VPORT_L9B0_Wr01(iris_123, reg_frame_motion_th1, pSet_motiondetector_t->reg_frame_motion_th1      );
	VPORT_L9B0_WrFL(iris_123);

	VPORT_L9B0_RdFL(iris_086);
	VPORT_L9B0_Wr01(iris_086, reg_chroma_level, pSet_motiondetector_t->reg_chroma_level          );
	VPORT_L9B0_Wr01(iris_086, reg_tcomb_chroma_level, pSet_motiondetector_t->reg_tcomb_chroma_level    );
	VPORT_L9B0_WrFL(iris_086);


#if 0 // won.hur : This code is disabled due to the delection of IRIS_189 register
	VPORT_L9B0_RdFL(iris_189);
	VPORT_L9B0_Wr01(iris_189, cvd_3dcomb_mdy_dir, pSet_motiondetector_t->reg_3dcomb_mdy_dir              );
	VPORT_L9B0_Wr01(iris_189, cvd_3dcomb_mdy_disel, pSet_motiondetector_t->reg_3dcomb_mdy_disel            );
	VPORT_L9B0_WrFL(iris_189);

	VPORT_L9B0_RdFL(iris_192);
	VPORT_L9B0_Wr01(iris_192, cvd_3dcomb_mdi_sadsel, pSet_motiondetector_t->reg_3dcomb_mdi_sadsel);
	VPORT_L9B0_WrFL(iris_192);
#endif
}



// won.hur : This function needs to be modified or deleted due to the delection
// of registers IRiS_189 through IRIS_233
// code related to these registers are disabled!
void CVD_L9Bx_Set_Global_Classifier(   CVD_L9Ax_SET_GLOBAL_CLASSIFIER_T *pSet_globalclassifier)
{

#if 0 // won.hur : Disabled due to delection of IRIS 189 ~ IRIS233
	VPORT_L9B0_RdFL(iris_189);
	VPORT_L9B0_Wr01(iris_189, cvd_3dcomb_md_mode, pSet_globalclassifier->reg_3dcomb_md_mode              );
	VPORT_L9B0_Wr01(iris_189, cvd_3dcomb_mdy_disel1, pSet_globalclassifier->reg_3dcomb_mdy_disel1     );
	VPORT_L9B0_Wr01(iris_189, cvd_3dcomb_mdy_sel, pSet_globalclassifier->reg_3dcomb_mdy_sel              );
	VPORT_L9B0_WrFL(iris_189);

	VPORT_L9B0_RdFL(iris_197);
	VPORT_L9B0_Wr01(iris_197, cvd_3dcomb_mdlf_actv_sel, pSet_globalclassifier->reg_3dcomb_mdlf_actv_sel        );
	VPORT_L9B0_Wr01(iris_197, cvd_3dcomb_mdlf_actv_th, pSet_globalclassifier->reg_3dcomb_mdlf_actv_th         );
	VPORT_L9B0_Wr01(iris_197, cvd_3dcomb_mdhf_actv_th, pSet_globalclassifier->reg_3dcomb_mdhf_actv_th         );
	VPORT_L9B0_WrFL(iris_197);

	VPORT_L9B0_RdFL(iris_198);
	VPORT_L9B0_Wr01(iris_198, cvd_3dcomb_mdlf_blk_th, pSet_globalclassifier->reg_3dcomb_mdlf_blk_th          );
	VPORT_L9B0_Wr01(iris_198, cvd_3dcomb_mdhf_blk_th, pSet_globalclassifier->reg_3dcomb_mdhf_blk_th          );
	VPORT_L9B0_WrFL(iris_198);

	VPORT_L9B0_RdFL(iris_196);
	VPORT_L9B0_Wr01(iris_196, cvd_3dcomb_mdclass_csel, pSet_globalclassifier->reg_3dcomb_mdclass_csel         );
	VPORT_L9B0_Wr01(iris_196, cvd_3dcomb_mdclass_dsel, pSet_globalclassifier->reg_3dcomb_mdclass_dsel         );
	VPORT_L9B0_Wr01(iris_196, cvd_3dcomb_mdclass_fldsel, pSet_globalclassifier->reg_3dcomb_mdclass_fldsel       );
	VPORT_L9B0_WrFL(iris_196);

	VPORT_L9B0_RdFL(iris_199);
	VPORT_L9B0_Wr01(iris_199, cvd_3dcomb_mdlf_fld_th0, pSet_globalclassifier->reg_3dcomb_mdlf_fld_th0         );
	VPORT_L9B0_Wr01(iris_199, cvd_3dcomb_mdlf_fld_th1, pSet_globalclassifier->reg_3dcomb_mdlf_fld_th1         );
	VPORT_L9B0_WrFL(iris_199);

	VPORT_L9B0_RdFL(iris_200);
	VPORT_L9B0_Wr01(iris_200, cvd_3dcomb_mdlf_fld_th2, pSet_globalclassifier->reg_3dcomb_mdlf_fld_th2         );
	VPORT_L9B0_Wr01(iris_200, cvd_3dcomb_mdlf_fld_th3, pSet_globalclassifier->reg_3dcomb_mdlf_fld_th3         );
	VPORT_L9B0_Wr01(iris_200, cvd_3dcomb_mdhf_fld_sel, pSet_globalclassifier->reg_3dcomb_mdhf_fld_sel         );
	VPORT_L9B0_WrFL(iris_200);

	VPORT_L9B0_RdFL(iris_201);
	VPORT_L9B0_Wr01(iris_201, cvd_3dcomb_mdhf_fld_th0, pSet_globalclassifier->reg_3dcomb_mdhf_fld_th0         );
	VPORT_L9B0_Wr01(iris_201, cvd_3dcomb_mdhf_fld_th1, pSet_globalclassifier->reg_3dcomb_mdhf_fld_th1         );
	VPORT_L9B0_WrFL(iris_201);

	VPORT_L9B0_RdFL(iris_202);
	VPORT_L9B0_Wr01(iris_202, cvd_3dcomb_mdhf_fld_th2, pSet_globalclassifier->reg_3dcomb_mdhf_fld_th2         );
	VPORT_L9B0_Wr01(iris_202, cvd_3dcomb_mdhf_fld_th3, pSet_globalclassifier->reg_3dcomb_mdhf_fld_th3         );
	VPORT_L9B0_WrFL(iris_202);

	VPORT_L9B0_RdFL(iris_203);
	VPORT_L9B0_Wr01(iris_203, cvd_3dcomb_mdhlf_fld_sub_th0, pSet_globalclassifier->reg_3dcomb_mdhlf_fld_sub_th0    );
	VPORT_L9B0_Wr01(iris_203, cvd_3dcomb_mdlf_fld_grd, pSet_globalclassifier->reg_3dcomb_mdlf_fld_grd         );
	VPORT_L9B0_Wr01(iris_203, cvd_3dcomb_mdhf_fld_grd, pSet_globalclassifier->reg_3dcomb_mdhf_fld_grd         );
	VPORT_L9B0_WrFL(iris_203);

	VPORT_L9B0_RdFL(iris_204);
	VPORT_L9B0_Wr01(iris_204, cvd_3dcomb_mdlf_fld_grd_alp, pSet_globalclassifier->reg_3dcomb_mdlf_fld_grd_alp     );
	VPORT_L9B0_WrFL(iris_204);

	VPORT_L9B0_RdFL(iris_205);
	VPORT_L9B0_Wr01(iris_205, cvd_3dcomb_mdlf_fld_grd_alp__2, pSet_globalclassifier->reg_3dcomb_mdlf_fld_grd_alp__2);
	VPORT_L9B0_WrFL(iris_205);

	VPORT_L9B0_RdFL(iris_206);
	VPORT_L9B0_Wr01(iris_206, cvd_3dcomb_mdhf_fld_grd_alp, pSet_globalclassifier->reg_3dcomb_mdhf_fld_grd_alp     );
	VPORT_L9B0_WrFL(iris_206);

	VPORT_L9B0_RdFL(iris_207);
	VPORT_L9B0_Wr01(iris_207, cvd_3dcomb_mdhf_fld_grd_alp__2, pSet_globalclassifier->reg_3dcomb_mdhf_fld_grd_alp__2);
	VPORT_L9B0_WrFL(iris_207);

	VPORT_L9B0_RdFL(iris_209);
	VPORT_L9B0_Wr01(iris_209, cvd_3dcomb_mdpd32_on, pSet_globalclassifier->reg_3dcomb_mdpd32_on            );
	VPORT_L9B0_Wr01(iris_209, cvd_3dcomb_mdpd32_sel, pSet_globalclassifier->reg_3dcomb_mdpd32_sel           );
	VPORT_L9B0_WrFL(iris_209);

	VPORT_L9B0_RdFL(iris_210);
	VPORT_L9B0_Wr01(iris_210, cvd_3dcomb_mdpd32_th, pSet_globalclassifier->reg_3dcomb_mdpd32_th            );
	VPORT_L9B0_Wr01(iris_210, cvd_3dcomb_mdglo_mode, pSet_globalclassifier->reg_3dcomb_mdglo_mode     );
	VPORT_L9B0_WrFL(iris_210);

	VPORT_L9B0_RdFL(iris_211);
	VPORT_L9B0_Wr01(iris_211, cvd_3dcomb_mdglo_m1_lth0, pSet_globalclassifier->reg_3dcomb_mdglo_m1_lth0  );
	VPORT_L9B0_Wr01(iris_211, cvd_3dcomb_mdglo_m1_uth0, pSet_globalclassifier->reg_3dcomb_mdglo_m1_uth0  );
	VPORT_L9B0_Wr01(iris_211, cvd_3dcomb_mdglo_m1_sameth, pSet_globalclassifier->reg_3dcomb_mdglo_m1_sameth);
	VPORT_L9B0_WrFL(iris_211);
#else
	return;
#endif // won.hur
}


// won.hur : This function needs to be modified or deleted due to delection of
// registers : IRIS_185~188
void CVD_L9Bx_Set_Blending( CVD_L9Ax_SET_BLENDING_T	*pSet_blending)
{

#if 0 // won.hur
	VPORT_L9B0_RdFL(iris_185);
	VPORT_L9B0_Wr01(iris_185, cvd_3dcomb_coefi_pow, pSet_blending->reg_3dcomb_coefi_pow            );
	VPORT_L9B0_WrFL(iris_185);

	VPORT_L9B0_RdFL(iris_186);
	VPORT_L9B0_Wr01(iris_186, cvd_3dcomb_coefi, pSet_blending->reg_3dcomb_coefi);
	VPORT_L9B0_WrFL(iris_186);

	VPORT_L9B0_RdFL(iris_187);
	VPORT_L9B0_Wr01(iris_187, cvd_3dcomb_coefi__2, pSet_blending->reg_3dcomb_coefi__2           );
	VPORT_L9B0_WrFL(iris_187);

	VPORT_L9B0_RdFL(iris_188);
	VPORT_L9B0_Wr01(iris_188, cvd_3dcomb_coefi__3, pSet_blending->reg_3dcomb_coefi__3           );
	VPORT_L9B0_WrFL(iris_188);
#else
	return;
#endif // won.hur

}

void CVD_L9Bx_Set_Chroma_Demode(CVD_L9Ax_SET_CHROMA_DEMODE_T	*pSet_chromademode_t)
{
	VPORT_L9B0_RdFL(iris_062);
	VPORT_L9B0_Wr01(iris_062, reg_adaptive_chroma_mode, pSet_chromademode_t->reg_adaptive_chroma_mode  );
	VPORT_L9B0_WrFL(iris_062);

	VPORT_L9B0_RdFL(iris_013);
	VPORT_L9B0_Wr01(iris_013, reg_chroma_bw_lo, pSet_chromademode_t->reg_chroma_bw_lo);
	VPORT_L9B0_WrFL(iris_013);
}

void CVD_L9Bx_Set_Output_Delay( CVD_L9Ax_SET_OUPUT_DELAY_T        	*pSet_outputdelay_t)
{
	VPORT_L9B0_RdFL(iris_131);
	VPORT_L9B0_Wr01(iris_131, reg_hrs_alpha_yoff, pSet_outputdelay_t->reg_hrs_alpha_yoff 	);
	VPORT_L9B0_Wr01(iris_131, reg_hrs_alpha_cboff, pSet_outputdelay_t->reg_hrs_alpha_cboff);
	VPORT_L9B0_Wr01(iris_131, reg_hrs_alpha_croff, pSet_outputdelay_t->reg_hrs_alpha_croff);
	VPORT_L9B0_WrFL(iris_131);
	//added 0126
	VPORT_L9B0_RdFL(iris_019);
	VPORT_L9B0_Wr01(iris_019, reg_yc_delay, pSet_outputdelay_t->reg_yc_delay);
	VPORT_L9B0_WrFL(iris_019);

	VPORT_L9B0_RdFL(iris_133);
	VPORT_L9B0_Wr01(iris_133, reg_cb_delay, pSet_outputdelay_t->reg_cb_delay);
	VPORT_L9B0_WrFL(iris_133);
}

void CVD_L9Bx_Set_Output_Range(CVD_L9Ax_SET_OUPUT_RANGE_T	*pSet_outputrange_t)
{
	VPORT_L9B0_RdFL(iris_118);
	VPORT_L9B0_Wr01(iris_118, reg_oadj_y_offi, pSet_outputrange_t->reg_oadj_y_offi);
	VPORT_L9B0_Wr01(iris_118, reg_oadj_y_offo, pSet_outputrange_t->reg_oadj_y_offo);
	VPORT_L9B0_WrFL(iris_118);

	VPORT_L9B0_RdFL(iris_119);
	VPORT_L9B0_Wr01(iris_119, reg_oadj_y_coeff, pSet_outputrange_t->reg_oadj_y_coeff);
	VPORT_L9B0_WrFL(iris_119);

	VPORT_L9B0_RdFL(iris_120);
	VPORT_L9B0_Wr01(iris_120, reg_oadj_c_offi, pSet_outputrange_t->reg_oadj_c_offi);
	VPORT_L9B0_Wr01(iris_120, reg_oadj_c_offo, pSet_outputrange_t->reg_oadj_c_offo);
	VPORT_L9B0_WrFL(iris_120);

	VPORT_L9B0_RdFL(iris_121);
	VPORT_L9B0_Wr01(iris_121, reg_oadj_c_coeff, pSet_outputrange_t->reg_oadj_c_coeff);
	VPORT_L9B0_WrFL(iris_121);
}

void CVD_L9Bx_Set_Luma_Peaking(CVD_L9Ax_SET_LUMA_PEAKING_T	*pSet_lumapeaking_t)
{
	VPORT_L9B0_RdFL(iris_044);
	VPORT_L9B0_Wr01(iris_044, reg_peak_en, pSet_lumapeaking_t->reg_peak_en);
	VPORT_L9B0_Wr01(iris_044, reg_peak_gain, pSet_lumapeaking_t->reg_peak_gain);
	VPORT_L9B0_Wr01(iris_044, reg_peak_range, pSet_lumapeaking_t->reg_peak_range);
	VPORT_L9B0_Wr01(iris_044, reg_secam_ybw, pSet_lumapeaking_t->reg_secam_ybw);
	VPORT_L9B0_WrFL(iris_044);
}

void CVD_L9Bx_Set_Secam_Freq(CVD_L9Ax_SET_SECAM_FREQ_T	*pSet_secamfreq_t)
{
	VPORT_L9B0_RdFL(iris_058);
	VPORT_L9B0_Wr01(iris_058, reg_dr_freq, pSet_secamfreq_t->reg_dr_freq);
	VPORT_L9B0_Wr01(iris_058, reg_db_freq, pSet_secamfreq_t->reg_db_freq);
	VPORT_L9B0_WrFL(iris_058);
}

#endif




// This function needs to be modified or deleted due to the delection of
// IRIS_208 register.
// Code related to this register is disabled!
int	CVD_L9Bx_Read_fld_cnt_value(UINT16 *pfld_hfcnt_value, UINT16 *pfld_lfcnt_value)
{
#if 0 //won.hur
	VPORT_L9B0_RdFL(iris_208);
	VPORT_L9B0_Rd02(iris_208, status_fld_lfcnt, *pfld_lfcnt_value, status_fld_hfcnt, *pfld_hfcnt_value);
	return 0;
#else
	return -1;
#endif
}


// This function needs to be modified or deleted due to the delection of
// IRIS_189 register.
// Code related to this register is disabled!
int CVD_L9Bx_Set_motion_mode(UINT8	md_mode_value, UINT8 motion_mode_value)
{

#if 0 // won.hur
	VPORT_L9B0_RdFL(iris_189);
	VPORT_L9B0_Wr01(iris_189, cvd_3dcomb_md_mode, md_mode_value);
	VPORT_L9B0_WrFL(iris_189);
#endif // won.hur

	VPORT_L9B0_RdFL(iris_062);
	VPORT_L9B0_Wr01(iris_062, reg_motion_mode, motion_mode_value);
	VPORT_L9B0_WrFL(iris_062);
	return 0;
}



// won.hur : This function needs to be changed!!!
// This is because L9B0 has no ghslvdstx2
// This part is disabled!!
int CVD_L9Bx_Channel_Power_Control(UINT32 on_off)
{
	if(on_off)
	{
		if( lx_chip_rev( ) == LX_CHIP_REV(L9,A0) )
		{
			//L9A Workaround CVBS through AFE3CH_G
			VPORT_I2C_Read((UINT32*)&gafe_3ch_3_bx);
			gafe_3ch_3_bx.afe3ch_sel_ck = 0x1;
			VPORT_I2C_Write((UINT32*)&gafe_3ch_3_bx);

			VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
			gafe_3ch_0_bx.afe3ch_gpdb = 0x1;
			gafe_3ch_0_bx.afe3ch_biaspdb = 0x1;
			VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);
		}

#if 0   // won.hur
		//L9A_DIE TX to L9D_DIE on
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_0_bx);
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_1_bx);
		ghslvdstx2_0_bx.pdb3 = 1;
		ghslvdstx2_1_bx.ch_en3 = 0x3f;
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_0_bx);
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_1_bx);
#endif


		// Normal condition
		VPORT_I2C_Read((UINT32*)&gmain_pll_4_bx);
		VPORT_I2C_Read((UINT32*)&gafe_cvbs_1_bx);
		VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);
		gafe_cvbs_1_bx.cvbs_pdbm = 0x1;
		gafe_cvbs_3_bx.cvbs_pdb = 0x1;
		gmain_pll_4_bx.dr3p_pdb = 0x1;

		//added 110622 : by tommy.lee to disable clamp control on power down condition
		gafe_cvbs_3_bx.cvbs_cp = 1;
		VPORT_I2C_Write((UINT32*)&gmain_pll_4_bx);
		VPORT_I2C_Write((UINT32*)&gafe_cvbs_1_bx);
		VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);

		//by dws : remove mdelay
		//mdelay(5);
		OS_MsecSleep(5);

		VPORT_L9B0_RdFL(iris_011);
		VPORT_L9B0_Wr01(iris_011, reg_cvd_soft_reset, 1);
		VPORT_L9B0_WrFL(iris_011);

		//by dws : remove mdelay
		//mdelay(5);
		OS_MsecSleep(5);

		VPORT_L9B0_RdFL(iris_011);
		VPORT_L9B0_Wr01(iris_011, reg_cvd_soft_reset, 0);
		VPORT_L9B0_WrFL(iris_011);

/*
		VPORT_I2C_Read((UINT32*)&gsoft_reset_5_bx);
		gsoft_reset_5_bx.swrst_f54m = 0;
		gsoft_reset_5_bx.swrst_cvbs = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_5_bx);
		*/
	}
	else
	{
		if( lx_chip_rev( ) == LX_CHIP_REV(L9,A0) )
		{
			//L9A Workaround CVBS through AFE3CH_G
			VPORT_I2C_Read((UINT32*)&gafe_3ch_3_bx);
			gafe_3ch_3_bx.afe3ch_sel_ck = 0x0;
			VPORT_I2C_Write((UINT32*)&gafe_3ch_3_bx);

			VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
			gafe_3ch_0_bx.afe3ch_gpdb = 0x0;
			// Bias PDB should not turned off
			//		gafe_3ch_0_bx.afe3ch_biaspdb = 0x0;
			VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);
		}

#if 0 // won.hur
		//L9A_DIE TX to L9D_DIE off
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_0_bx);
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_1_bx);
		ghslvdstx2_0_bx.pdb3 = 0;
		ghslvdstx2_1_bx.ch_en3 = 0;
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_0_bx);
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_1_bx);
#endif // won.hur

		// Power down
		/*
		VPORT_I2C_Read((UINT32*)&gsoft_reset_5_bx);
		gsoft_reset_5_bx.swrst_f54m = 0x1;
		gsoft_reset_5_bx.swrst_cvbs = 0x1;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_5_bx);
		*/

		VPORT_I2C_Read((UINT32*)&gafe_cvbs_1_bx);
		VPORT_I2C_Read((UINT32*)&gafe_cvbs_3_bx);

		//Do Not Turn Off CVBS_PDBM, to enable clock  for DENC
		//gafe_cvbs_1_bx.cvbs_pdbm = 0;
		gafe_cvbs_3_bx.cvbs_pdb = 0;

		//added 110622 : by tommy.lee to disable clamp control on power down condition
		gafe_cvbs_3_bx.cvbs_cp = 0;
		VPORT_I2C_Write((UINT32*)&gafe_cvbs_1_bx);
		VPORT_I2C_Write((UINT32*)&gafe_cvbs_3_bx);
	}
	return 0;
}

int CVD_L9Bx_Reset_Clampagc(void)
{
	//ADC_DEBUG("Reset Clampagc Entered\n");
	VPORT_L9B0_RdFL(iris_174);
	VPORT_L9B0_Wr01(iris_174, iris_clampagc_v2, 0x1);
	VPORT_L9B0_WrFL(iris_174);
	//by dws : remove mdelay
	//mdelay(5);
	OS_MsecSleep(5);
	VPORT_L9B0_RdFL(iris_174);
	VPORT_L9B0_Wr01(iris_174, iris_clampagc_v2, 0x0);
	VPORT_L9B0_WrFL(iris_174);
	return 0;
}

int CVD_L9Bx_Bypass_Control(LX_AFE_CVD_BYPASS_CONTROL_T *cvd_bypass_control_t)
{
	VPORT_I2C_Read((UINT32*)&gafe_vbuf_1_bx);
	VPORT_I2C_Read((UINT32*)&gafe_vbuf_0_bx);

	switch(cvd_bypass_control_t->buf_out_1_sel)
	{
		case CVD_BYPASS_DAC:
			gafe_vbuf_1_bx.buf_sel1 = 0x4;
			break;

		case CVD_BYPASS_CVBS_WITH_CLAMPING:
			gafe_vbuf_1_bx.buf_sel1 = 0x5;
			break;

		case CVD_BYPASS_CVBS_WITHOUT_CLAMPING:
			gafe_vbuf_1_bx.buf_sel1 = 0x7;
			break;

		default:
			break;
	}

	switch(cvd_bypass_control_t->buf_out_2_sel)
	{
		case CVD_BYPASS_DAC:
			gafe_vbuf_1_bx.buf_sel2 = 0x4;
			break;

		case CVD_BYPASS_CVBS_WITH_CLAMPING:
			gafe_vbuf_1_bx.buf_sel2 = 0x5;
			break;

		case CVD_BYPASS_CVBS_WITHOUT_CLAMPING:
			gafe_vbuf_1_bx.buf_sel2 = 0x7;
			break;

		default:
			break;
	}

	if(cvd_bypass_control_t->cvbs_source_sel == CVD_BYPASS_CVBS_IN1)
		gafe_vbuf_0_bx.buf_ycm = 0x0;
	else
		gafe_vbuf_0_bx.buf_ycm = 0x1;

	VPORT_I2C_Write((UINT32*)&gafe_vbuf_1_bx);
	VPORT_I2C_Write((UINT32*)&gafe_vbuf_0_bx);

	return 0;
}

int CVD_L9Bx_Get_Vline_625_Reg(void)
{
	int ret;
	VPORT_L9B0_RdFL(iris_012);
	VPORT_L9B0_Rd01(iris_012, reg_vline_625, ret);
	return ret;
}

int CVD_L9Bx_OnOff_VDAC(BOOLEAN bonoff)
{

	CVD_DEBUG("%s entered :  %d \n",__func__, bonoff);

	if(bonoff)
		gafe_vdac_0_bx.vdac_pdb = 0x1;
	else
		gafe_vdac_0_bx.vdac_pdb = 0x0;

	CVD_DEBUG("%s vdac pdb set to :  %d \n",__func__, gafe_vdac_0_bx.vdac_pdb);

	VPORT_I2C_Write((UINT32*)&gafe_vdac_0_bx);

	return 0;
}

int CVD_L9Bx_Set_PE_Params(CVD_REG_PARAM_T	*pCVD_PE_Param_t, UINT32 size, LX_AFE_CVD_PQ_MODE_T cvd_pq_mode)
{
	int count;
	UINT32 value;
	UINT32 recvAddr;

	CVD_DEBUG("%s \n", __func__);

	for(count=0; count < size;count ++)
	{

		recvAddr = pCVD_PE_Param_t->cvd_phy_addr;
		value = pCVD_PE_Param_t->cvd_pe_value;
		/*
		   if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DE_BASE;
		   else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;
		 */
		//120201 : for NTSC CAGC adjust
		if(recvAddr == 0x43e8)
			g_initial_c_coeff = value;

		recvAddr = recvAddr + (UINT32)gpRealRegVPORT_L9B0 - 0x4100;
		REG_WD(recvAddr, value);

	//	CVD_DEBUG("%s [0x%x:0x%x]\n", __func__, recvAddr, value);

		pCVD_PE_Param_t ++;

	}

	//111104 wonsik.do : default PE settings are for L9B1 revision, for L9B0 following register setttings are neede
	if( lx_chip_rev( ) == LX_CHIP_REV(L9,B0) )
	{
		CVD_DEBUG("L9B0 detected : Modified CVD PE Setting\n");
		//reg_ifcomp_en
		recvAddr = 0x4620 + (UINT32)gpRealRegVPORT_L9B0 - 0x4100;
		value = 0x00000FF6;
		REG_WD(recvAddr, value);

		if(cvd_pq_mode == LX_CVD_PQ_SECAM)
		{
			CVD_DEBUG("L9B0 SECAM AV Setting\n");
			//Y line dly
			recvAddr = 0x45F4 + (UINT32)gpRealRegVPORT_L9B0 - 0x4100;
			value = 0x80000030;
			REG_WD(recvAddr, value);
			//C line dly
			recvAddr = 0x4650 + (UINT32)gpRealRegVPORT_L9B0 - 0x4100;
			value = 0x02700001;
			REG_WD(recvAddr, value);
		}
		else if(cvd_pq_mode == LX_CVD_PQ_SECAM_RF)
		{
			CVD_DEBUG("L9B0 SECAM RF Setting\n");
			//Y line dly
			recvAddr = 0x45F4 + (UINT32)gpRealRegVPORT_L9B0 - 0x4100;
			value = 0x80000070;
			REG_WD(recvAddr, value);
			//C line dly
			recvAddr = 0x4650 + (UINT32)gpRealRegVPORT_L9B0 - 0x4100;
			value = 0x02700001;
			REG_WD(recvAddr, value);
		}

	}
	return 0;
}

int CVD_L9Bx_swrst_CS(CVD_SELECT_CDETECT_T cs_sel)
{
	if (cs_sel == CVD_SEL_CS_CS0) // select cs0;
	{
		VPORT_L9B0_RdFL(iris_179);
		VPORT_L9B0_Wr01(iris_179,  reg_cs_sw_rst, 1);
		VPORT_L9B0_WrFL(iris_179);

		OS_MsecSleep(5);

		VPORT_L9B0_RdFL(iris_179);
		VPORT_L9B0_Wr01(iris_179,  reg_cs_sw_rst, 0);
		VPORT_L9B0_WrFL(iris_179);
	}
	else if (cs_sel == CVD_SEL_CS_CS1) // select cs1;
	{
		VPORT_L9B0_RdFL(iris_190);
		VPORT_L9B0_Wr01(iris_190,  reg_cs1_sw_rst, 1);
		VPORT_L9B0_WrFL(iris_190);

		OS_MsecSleep(5);

		VPORT_L9B0_RdFL(iris_190);
		VPORT_L9B0_Wr01(iris_190,  reg_cs1_sw_rst, 0);
		VPORT_L9B0_WrFL(iris_190);
	}
	else
		return -1;

	return 0;
}

int CVD_L9Bx_Set_Hstate_Max(UINT32	hstate_max_value)
{

//	CVD_DEBUG("%s entered :  %d \n",__func__, hstate_max_value);

	if(hstate_max_value > 5)
		return -1;

	VPORT_L9B0_RdFL(iris_026);
	VPORT_L9B0_Wr01(iris_026,  reg_hstate_max, hstate_max_value);
	VPORT_L9B0_WrFL(iris_026);

	return 0;
}

int CVD_L9Bx_Set_Hstate_Fixed(UINT32	value)
{

//	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	value &= 0x1;

	VPORT_L9B0_RdFL(iris_026);
	VPORT_L9B0_Wr01(iris_026,  reg_hstate_fixed, value);
	VPORT_L9B0_WrFL(iris_026);

	return 0;
}


int CVD_L9Bx_AGC_Bypass(int Bypass_Enable)
{

	CVD_DEBUG("%s entered :  %d \n",__func__, Bypass_Enable);

	if(Bypass_Enable == 1) {

		VPORT_L9B0_RdFL(iris_097);
		VPORT_L9B0_Wr01(iris_097,  reg_agc_bypass, 0x1);
		VPORT_L9B0_WrFL(iris_097);
	}
	else {
		VPORT_L9B0_RdFL(iris_097);
		VPORT_L9B0_Wr01(iris_097,  reg_agc_bypass, 0x0);
		VPORT_L9B0_WrFL(iris_097);
	}

	return 0;
}

int CVD_L9Bx_Set_dcrestore_accum_width(int value)
{

	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	VPORT_L9B0_RdFL(iris_073);
	VPORT_L9B0_Wr01(iris_073, reg_dcrestore_accum_width, value);
	VPORT_L9B0_WrFL(iris_073);

	return 0;
}

int CVD_L9Bx_Set_SCART_CSC(void)
{
	CVD_DEBUG("%s entered \n",__func__);

	VPORT_L9B0_RdFL(fastblank_002);
	VPORT_L9B0_RdFL(fastblank_003);
	VPORT_L9B0_RdFL(fastblank_004);
	VPORT_L9B0_RdFL(fastblank_005);
	VPORT_L9B0_RdFL(fastblank_006);
	VPORT_L9B0_RdFL(fastblank_009);

	VPORT_L9B0_Wr02(fastblank_002, reg_fb_csc_coef0, 0x0810, reg_fb_csc_coef1, 0x0191 );
	VPORT_L9B0_Wr02(fastblank_003, reg_fb_csc_coef2, 0x041D, reg_fb_csc_coef3, 0x7B58 );
	VPORT_L9B0_Wr02(fastblank_004, reg_fb_csc_coef4, 0x0706, reg_fb_csc_coef5, 0x7DA2 );
	VPORT_L9B0_Wr02(fastblank_005, reg_fb_csc_coef6, 0x7A1D, reg_fb_csc_coef7, 0x7EDD );
	VPORT_L9B0_Wr01(fastblank_006, reg_fb_csc_coef8, 0x0706 );
	VPORT_L9B0_Wr02(fastblank_009, reg_fb_csc_ofst4, 0x202, reg_fb_csc_ofst5, 0x204 );

	VPORT_L9B0_WrFL(fastblank_002);
	VPORT_L9B0_WrFL(fastblank_003);
	VPORT_L9B0_WrFL(fastblank_004);
	VPORT_L9B0_WrFL(fastblank_005);
	VPORT_L9B0_WrFL(fastblank_006);
	VPORT_L9B0_WrFL(fastblank_009);

	return 0;
}

int CVD_L9Bx_Set_comb2d_only(int value)
{

//	CVD_DEBUG("%s entered :  %d \n",__func__, value);
	value &= 0x1;

	VPORT_L9B0_RdFL(iris_063);
	VPORT_L9B0_Wr01(iris_063, reg_comb2d_only, value);
	VPORT_L9B0_WrFL(iris_063);
	VPORT_L9B0_RdFL(iris_063);
	VPORT_L9B0_Wr01(iris_063, reg_lbadrgen_rst, value);
	VPORT_L9B0_WrFL(iris_063);

	return 0;
}

int CVD_L9Bx_Set_Noise_Threshold(int value)
{

	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	VPORT_L9B0_RdFL(iris_016);
	VPORT_L9B0_Wr01(iris_016, reg_noise_thresh, value);	// default 0x32
	VPORT_L9B0_WrFL(iris_016);

	return 0;
}

int CVD_L9Bx_Set_AGC_Peak_Nominal(UINT8	value)	// 7bit value
{
	value &= 0x7F;

	VPORT_L9B0_RdFL(iris_024);
	VPORT_L9B0_Wr01(iris_024, reg_agc_peak_nominal, value);	//Default : 0x0A
	VPORT_L9B0_WrFL(iris_024);

	return 0;
}

int CVD_L9Bx_Get_AGC_Peak_Nominal(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_024);
	VPORT_L9B0_Rd01(iris_024, reg_agc_peak_nominal, ret);	//Default : 0x0A

	return ret;
}

int CVD_L9Bx_Get_PE0_Motion_Value(int *p_tnr_x_avg_t, int *p_tnr_x_avg_s, int *p_tpd_s_status)
{
	DE_P0L_L9B0_RdFL(tnr_status_00);
	DE_P0L_L9B0_RdFL(tnr_status_01);
	DE_P0L_L9B0_RdFL(tpd_stat_00);
	DE_P0L_L9B0_Rd01(tnr_status_00, x_avg_t, *p_tnr_x_avg_t);
	DE_P0L_L9B0_Rd01(tnr_status_01, x_avg_s, *p_tnr_x_avg_s);
	DE_P0L_L9B0_Rd01(tpd_stat_00, reg_s_status, *p_tpd_s_status);

	return 0;
}

int CVD_L9Bx_Set_Contrast_Brightness(int contrast, int brightness)
{
	VPORT_L9B0_RdFL(iris_020);
	VPORT_L9B0_Wr01(iris_020, reg_contrast, contrast);
	VPORT_L9B0_Wr01(iris_020, reg_brightness, brightness);
	VPORT_L9B0_WrFL(iris_020);

	return 0;
}

int CVD_L9Bx_Set_Dcrestore_Gain(int value)
{
	value &= 0x3;

	VPORT_L9B0_RdFL(iris_073);
	// Inital Value is '0'
	// Set reg_dcrestore_gain to '3' on weak RF signal for sync stability
	VPORT_L9B0_Wr01(iris_073, reg_dcrestore_gain, value);
	VPORT_L9B0_WrFL(iris_073);

	return 0;
}

//set reg_agc_bypass & reg_dcrestore_gain to default value
void CVD_L9Bx_Set_for_Normal_Signal(void)
{
	CVD_DEBUG("%s entered \n",__func__);
	CVD_L9Bx_AGC_Bypass(0x0);
//	CVD_L9Bx_Set_Dcrestore_Gain(0x0);
}

//set AGC to Bypass, and set DCrestore gain to 1/8 on weak RF signal ( status nois is max value 0x3FF)
void CVD_L9Bx_Set_for_Noisy_Signal(void)
{
	CVD_DEBUG("%s entered \n",__func__);
	CVD_L9Bx_AGC_Bypass(0x1);
//	CVD_L9Bx_Set_Dcrestore_Gain(0x3);
}

int CVD_L9Bx_Get_Status_AGC_Gain(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_007);
	VPORT_L9B0_Rd01(iris_007, reg_status_agc_gain, ret);

	return ret;
}

int CVD_L9Bx_Set_AGC_Peak_En(int enable)
{
	enable &= 0x1;

//	CVD_DEBUG("%s entered :  %d \n",__func__, enable);

	VPORT_L9B0_RdFL(iris_024);
	VPORT_L9B0_Wr01(iris_024, reg_agc_peak_en, enable);
	VPORT_L9B0_WrFL(iris_024);

	return 0;

}

int CVD_L9Bx_Get_HNon_Standard_Flag(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_002);
	VPORT_L9B0_Rd01(iris_002, reg_hnon_standard, ret);

	return ret;
}

int CVD_L9Bx_Get_VNon_Standard_Flag(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_002);
	VPORT_L9B0_Rd01(iris_002, reg_vnon_standard, ret);

	return ret;
}

int CVD_L9Bx_Set_Noburst_Ckill(unsigned int value)
{
	value &= 0x1;

//	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	VPORT_L9B0_RdFL(iris_023);
	VPORT_L9B0_Wr01(iris_023, reg_noburst_ckill, value);
	VPORT_L9B0_WrFL(iris_023);

	return 0;

}

int CVD_L9Bx_Get_Global_Motion_Value(void)
{
	int ret;

	unsigned int value;

	VPORT_L9B0_RdFL(iris_265);
	VPORT_L9B0_Rd01(iris_265, reg_ycsep_3d_status0, value);

	ret = value & 0xFF;

	return ret;
}

/* This Function is workaround code for JOJO Gunpo stream (vsync unstable)*/
int CVD_L9Bx_Set_for_Stable_Vsync(UINT32	Enable)
{
//	CVD_DEBUG("%s entered :  %d \n",__func__, Enable);

	if(Enable == 1) {
		VPORT_L9B0_RdFL(iris_041);
		VPORT_L9B0_Wr01(iris_041,  reg_vsync_cntl, 0x2);
		VPORT_L9B0_Wr01(iris_041,  reg_vsync_cntl_noisy, 0x1);
		VPORT_L9B0_WrFL(iris_041);

		VPORT_L9B0_RdFL(iris_042);
		VPORT_L9B0_Wr01(iris_042,  reg_vloop_tc, 0x3);
		VPORT_L9B0_WrFL(iris_042);
	}
	else if(Enable == 2)
	{
		VPORT_L9B0_RdFL(iris_041);
		VPORT_L9B0_Wr01(iris_041,  reg_vsync_cntl, 0x3);
		VPORT_L9B0_WrFL(iris_041);
	}
	else if(Enable == 3)
	{
		VPORT_L9B0_RdFL(iris_041);
		VPORT_L9B0_Wr01(iris_041,  reg_vsync_cntl, 0x0);
		VPORT_L9B0_WrFL(iris_041);

	}
	else {
		VPORT_L9B0_RdFL(iris_041);
		VPORT_L9B0_Wr01(iris_041,  reg_vsync_cntl, 0x1);
		VPORT_L9B0_Wr01(iris_041,  reg_vsync_cntl_noisy, 0x0);
		VPORT_L9B0_WrFL(iris_041);

		VPORT_L9B0_RdFL(iris_042);
		VPORT_L9B0_Wr01(iris_042,  reg_vloop_tc, 0x2);
		VPORT_L9B0_WrFL(iris_042);
	}
	return 0;
}

/* This Function is used for workaround code as to fix dong-go-dong-rak */
int CVD_L9Bx_Set_for_Field_Detect_Mode(UINT32 mode)
{

	VPORT_L9B0_RdFL(iris_042);

	if(mode == 3) 		VPORT_L9B0_Wr01(iris_042,  reg_field_detect_mode, 0x3);
	else if(mode == 2)  VPORT_L9B0_Wr01(iris_042,  reg_field_detect_mode, 0x2);
	else if(mode == 1)  VPORT_L9B0_Wr01(iris_042,  reg_field_detect_mode, 0x1);
	else if(mode == 0)  VPORT_L9B0_Wr01(iris_042,  reg_field_detect_mode, 0x0);
	else VPORT_L9B0_Wr01(iris_042,  reg_field_detect_mode, 0x2);	// Go to default value

	VPORT_L9B0_WrFL(iris_042);

	return 0;
}

/* This function is used for workaround code for brasil color instable issue */
int CVD_L9Bx_Set_for_Burst_Gate_End_On_Noisy(UINT8 original_value, UINT32 Enable)
{
	if(Enable == 0)
	{
		VPORT_L9B0_RdFL(iris_034);
		VPORT_L9B0_Wr01(iris_034,  reg_burst_gate_end, original_value);
		VPORT_L9B0_WrFL(iris_034);
		//AFE_PRINT("BURST GATE END 0x51\n");
	}
	else
	{
		VPORT_L9B0_RdFL(iris_034);
		VPORT_L9B0_Wr01(iris_034,  reg_burst_gate_end, 0x61);
		VPORT_L9B0_WrFL(iris_034);
		//AFE_PRINT("BURST GATE END 0x61\n");
	}

	return 0;
}


/* This function is used for workaround code for brasil color instable issue */
UINT32 CVD_L9Bx_Differential_Status_Cdto_Inc_Value(void)
{
	int ret = 0;
	UINT32 Current_Inc_Value = 0;
	static UINT32 Prev_Inc_Value = STANDARD_CDTO_INC_VALUE;
	UINT32 Difference_Value = 0;


	VPORT_L9B0_RdFL(iris_006);
	VPORT_L9B0_Rd01(iris_006, reg_status_cdto_inc, Current_Inc_Value);

	Difference_Value = abs(Current_Inc_Value - Prev_Inc_Value);
	Prev_Inc_Value = Current_Inc_Value;

	//AFE_PRINT("CVD_CDTO : Variance[%d]\n", Difference_Value);

	ret = Difference_Value;
	return ret;
}


UINT32 CVD_L9Bx_Read_Cordic_Freq_Value(void)
{
	int ret = 0;
	UINT8 Cordic_Value = 0;


	VPORT_L9B0_RdFL(iris_008);
	VPORT_L9B0_Rd01(iris_008, reg_status_cordic_freq, Cordic_Value);

	Cordic_Value = (UINT8)((SINT8)Cordic_Value + 0x80);

	ret = Cordic_Value;
	return ret;
}


int	CVD_L9Bx_Read_VCR_Detected(void)
{
	int ret = 0;
	UINT32 VCR_Detected_Flag = 0;

	VPORT_L9B0_RdFL(iris_003);
	VPORT_L9B0_Rd01(iris_003, reg_vcr, VCR_Detected_Flag);

	if(VCR_Detected_Flag) ret = 1;
	else ret = 0;

	return ret;
}

int CVD_L9Bx_Get_CVD_Burst_Mag_Value(void)
{
	UINT16 burst_mag_status;
	VPORT_L9B0_RdFL(iris_004);
	VPORT_L9B0_Rd01(iris_004,reg_status_burst_mag,burst_mag_status);

	return (int)burst_mag_status;
}

int CVD_L9Bx_Set_CVD_Saturation_Value(int value)
{
	value &= 0xFF;

	VPORT_L9B0_RdFL(iris_020);
	VPORT_L9B0_Wr01(iris_020, reg_saturation, value);
	VPORT_L9B0_WrFL(iris_020);

	return 0;
}

int CVD_L9Bx_Get_CAGC_Value(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_021);
	VPORT_L9B0_Rd01(iris_021, reg_cagc, ret);

	return ret;
}

int CVD_L9Bx_Get_Saturation_Value(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_020);
	VPORT_L9B0_Rd01(iris_020, reg_saturation, ret);

	return ret;
}

int CVD_L9Bx_Get_AGC_Peak_En_Value(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_024);
	VPORT_L9B0_Rd01(iris_024, reg_agc_peak_en, ret);

	return ret;
}

int CVD_L9Bx_Get_AGC_Bypass_Value(void)
{
	int ret;

	VPORT_L9B0_RdFL(iris_097);
	VPORT_L9B0_Rd01(iris_097,  reg_agc_bypass, ret);

	return ret;
}
int CVD_L9Bx_Get_Vdetect_Vcount_Value(void)
{
	int vcount;
	VPORT_L9B0_RdFL(iris_273);
	VPORT_L9B0_Rd01(iris_273, reg_status_vdetect_vcount, vcount);

	return vcount;
}

int CVD_L9Bx_Get_oadj_c_coeff_value(void)
{
	int oadj_c_coeff_value;
	VPORT_L9B0_RdFL(iris_121);
	VPORT_L9B0_Rd01(iris_121, reg_oadj_c_coeff, oadj_c_coeff_value);

	return oadj_c_coeff_value;
}

int CVD_L9Bx_OnOff_Chromalock_Ckill(BOOLEAN bonoff)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, bonoff);
	VPORT_L9B0_RdFL(iris_046);

	if(bonoff)
		VPORT_L9B0_Wr01(iris_046, reg_lose_chromalock_ckill, 0x1);
	else
		VPORT_L9B0_Wr01(iris_046, reg_lose_chromalock_ckill, 0x0);

	VPORT_L9B0_WrFL(iris_046);
	return 0;
}

int CVD_L9Bx_Reset_mif(int enable)
{
	if(enable >0)
	{
		VPORT_L9B0_RdFL(iris_174);
		VPORT_L9B0_Wr01(iris_174, iris_mif_gmau, 1);
		VPORT_L9B0_WrFL(iris_174);
	}
	else
	{
		VPORT_L9B0_RdFL(iris_174);
		VPORT_L9B0_Wr01(iris_174, iris_mif_gmau, 0);
		VPORT_L9B0_WrFL(iris_174);
	}
	return 0;
}

int CVD_L9Bx_Set_HNon_Standard_Threshold(int value)
{
	int threshold;
	VPORT_L9B0_RdFL(iris_023);
	VPORT_L9B0_Rd01(iris_023, reg_hnon_std_threshold, threshold);
	if(threshold != value) {
		CVD_DEBUG("HNon_Std_Threshold to [0x%x]\n", value);
		VPORT_L9B0_Wr01(iris_023, reg_hnon_std_threshold, value);
		VPORT_L9B0_WrFL(iris_023);
	}

	return 0;
}

int CVD_L9Bx_Get_Crunky_Status(LX_AFE_CVD_CK_T *pCK_Detection_t)
{
	VPORT_L9B0_RdFL(iris_001);
	VPORT_L9B0_Rd02(iris_001, reg_mv_vbi_detected, pCK_Detection_t->ck_vbi_detected , reg_mv_colourstripes, pCK_Detection_t->ck_colorstrip_detected);

	return 0;
}
