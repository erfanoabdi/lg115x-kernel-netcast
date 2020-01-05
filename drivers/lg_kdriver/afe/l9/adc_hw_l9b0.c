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
 *	ADC hw control
 *
 *  author      won.hur (won.hur@lge.com)
 *  version     1.0
 *  date
 *  note        Additional information.
 *				Modified from original version for L9A1->L9B0 device driver migration
 *				Modifier : won.hur(won.hur@lge.com)
 *				Modified date : 2011.08.17
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/interrupt.h>	/** interrupt */
#include <linux/platform_device.h>
#include <linux/wait.h>		/** wait_event_interrupt_timeout	*/

#include "afe_kapi.h"

#include "l9/vport_reg_l9b0.h"
#include "ctop_regs.h"

#include "resolution.h"
#include "adc_module.h"
#include "adc_hw.h"
#include "afe_drv.h"
#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define INTERLACE_CHECK_COUNT 7

//#define ADC_DETECTION_INTERRUPT_MASK	0x0000068A
//#define ADC_DETECTION_INTERRUPT_MASK	0x00000E8A
#define ADC_AOGC_INTERRUPT_MASK			0x0000C000
//#define ADC_BOUNDARY_COMPENSATION

//#define BEFORE_REVISION
#define VPORT_REG_DIRECT_ACCESS 0
#define L9_RGB_WA_FOR_CLOCK_ADJUST

#define APA_LOOP_COUNT	10

#define	SUPPORT_SCART_RGB_ULTRA_BLACK

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
#define	SCART_RGB_OFFSET_ADD	0x4C	//16 level added
#endif
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

extern LX_AFE_PCMODE_MODETABLE_T *gPCTable;
extern int gResolution;
extern LX_AFE_ADC_INPUT_SOURCE_TYPE_T gADC_type;
extern int gPrevious_index;

extern OS_SEM_T	g_ADC_Sema;
extern ADC_SYNC_MODE g_ADC_Sync_Mode ;

extern LX_AFE_ADC_GAIN_VALUE_T user_gain_value;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static UINT32	gADC_APA_Enable = 1;


#ifdef	KDRV_CONFIG_PM
typedef	struct{
	S_SEL_PORT gstPmSelPortValue;
	S_EXTAU_VALUE gstPmExtauValue;
	S_RGB_POSITION gstPmPositionValue;
	unsigned int guiPmPhaseValue;
	LX_AFE_ADC_GAIN_VALUE_T gstPmGainValue;
	LX_AFE_ADC_OFFSET_VALUE_T gstPmOffsetValue;
	int giPmIndexValue;
	SINT16 giPmClockValue;
	unsigned int guiPmInterruptStatus;
}S_ADC_PM_DATA;

static S_ADC_PM_DATA *gAdcPMData;

static int gAdcPmInitial = -1;
#endif
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DECLARE_WAIT_QUEUE_HEAD(agoc_done);
static int giAgocIntDone = 0;

//static int giSelMuxBackup = 0;

//static UINT32	gADC_APA_Delay = 50;
static UINT32	gADC_APA_Delay = 200;
static UINT32 	gADC_APA_Same_Count = 1;
static UINT32 	gADC_APA_Enable_Print = 0;
/*========================================================================================
	Implementation Group
========================================================================================*/

int ADC_L9Bx_PowerOn(void)
{

	//FIXME juhee - check if the following sequence is right or not.
	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_biaspdb = 0;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	OS_MsecSleep(1);

	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 0;
	gllpll_0_bx.llpll_pdb = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_biaspdb = 1;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	OS_MsecSleep(10);

	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 1;
	gllpll_0_bx.llpll_pdb = 1;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_bpdb = 1;
	gafe_3ch_0_bx.afe3ch_gpdb = 1;
	gafe_3ch_0_bx.afe3ch_rpdb = 1;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	//FIXME juhee - check if removed is ok not to set.
#if 0
	VPORT_RdFL(cvbsafe_pdb_001);
	VPORT_Wr01(cvbsafe_pdb_001, afe3ch_vref_pdb, 1);
	VPORT_WrFL(cvbsafe_pdb_001);
#endif

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_pix = 1;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);

	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_pix = 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);

	//FIXME juhee - check if removed is ok not to set.
#if 0
	VPORT_RdFL(ch3_adc_015);
	VPORT_Wr01(ch3_adc_015, afe3ch_volbypas, 0);
	VPORT_WrFL(ch3_adc_015);

	VPORT_RdFL(ch3_adc_015);
	VPORT_Wr01(ch3_adc_015, afe3ch_envolclp, 1);
	VPORT_WrFL(ch3_adc_015);
#endif


//Enable Interrupt
	//gVportRegBx->intr_vp2_enable.intr_vp2_enable = ADC_DETECTION_INTERRUPT_MASK | ADC_AOGC_INTERRUPT_MASK;
	//FIXME juhee - no match
#if 0
	VPORT_RdFL(intr_vp2_enable);
	VPORT_Wr01(intr_vp2_enable, intr_vp2_enable, ADC_DETECTION_INTERRUPT_MASK);
	VPORT_WrFL(intr_vp2_enable);
#endif
	return 0;

}

int ADC_L9Bx_PowerOff(void)
{
	// reg_exta_sel , reg_extb_sel
	//gVportRegBx->reg_exta_sel.reg_exta_sel = 0x0;
	//gVportRegBx->reg_exta_sel.reg_extb_sel = 0x0;

	//FIXME juhee - check if removed is ok not to set.
#if 0
	VPORT_RdFL(cvbsafe_pdb_001);
	VPORT_Wr01(cvbsafe_pdb_001, afe3ch_vref_pdb, 0);
	VPORT_WrFL(cvbsafe_pdb_001);
#endif
	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_biaspdb = 0;
	gafe_3ch_0_bx.afe3ch_bpdb = 0;
	gafe_3ch_0_bx.afe3ch_gpdb = 0;
	gafe_3ch_0_bx.afe3ch_rpdb = 0;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	//FIXME juhee - what will be the right value??
#if 0
	VPORT_RdFL(top_003);
	VPORT_Wr01(top_003, reg_ch3pll_pdb, 0);
	VPORT_WrFL(top_003);
#endif

	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 0;
	gllpll_0_bx.llpll_pdb = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_pix = 1;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);

	return 0;

}

int ADC_L9Bx_InitDaughterBoard(void)
{
	S_OFFSET_INFORM offset;
	//ADC_PowerOn();

	// Release resets of HS-LVDS block
	ADC_L9Bx_LVDS_Reset_Control(0);

	//gVportRegBx->ch3_cst_002.cst_postcoast = 0x1f;	//Crunky vision pseudo Sync
	/* release swrst_f24m is move to i2c_coreinit
	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	//gsoft_reset_0_bx.swrst_pix = 0;
	gsoft_reset_0_bx.swrst_f24m = 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
	*/

	//powerory 111012 : MSPG_925FS
	VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_23_bx);
	gadc_dig_22_bx.precoast = 0x0D;	//Default Value : 0x0B
	gadc_dig_23_bx.postcoast = 0x1D;
	VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_23_bx);

	//FIXME : Juhee 3DCD is not possible
	VPORT_I2C_Read((UINT32*)&gadc_dig_112_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_113_bx);
	gadc_dig_112_bx.size_detect_ctrl_1 = 0x3D;
	gadc_dig_113_bx.size_detect_ctrl_0 = 0xCD;
	VPORT_I2C_Write((UINT32*)&gadc_dig_112_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_113_bx);

	// Modified by min 110922 // for L9B0 Bring-Up 110830 by dws
	VPORT_I2C_Read((UINT32*)&gafe_3ch_2_bx);
	gafe_3ch_2_bx.afe3ch_icon_buf	= 0x2;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_2_bx);

	// AFE3CH_CTL_ADD option moved to ADC_L9Bx_SetType
	/*
	VPORT_I2C_Read((UINT32*)&gafe_3ch_7_bx);
	gafe_3ch_7_bx.afe3ch_ctl_add	= 0x93;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_7_bx);
	*/

	//gVportRegBx->ch3_cst_003.cst_hspolover = 0x1; // 0825 new value from powerory
	//gVportRegBx->ch3_cst_003.cst_vspolover = 0x1; // 0825 new value from powerory
	//gVportRegBx->ch3_cst_003.cst_hspoluser = 0x0; // 0825 new value from powerory
	//gVportRegBx->ch3_cst_003.cst_vspoluser = 0x0; // 0825 new value from powerory

	//For no interrupt occurrence when resolution change between master 210(576i) to 209(480i)
	//gVportRegBx->ch3_llpll_010.llpll_lpf_clk_sel = 0x1;
	//110214

	VPORT_I2C_Read((UINT32*)&gllpll_18_bx);
	gllpll_18_bx.llpll_lpf_clk_sel = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_18_bx);

	ADC_PowerOn();

	//20110125
//	_iow(&gVportRegBx->ch3_digital_003 , 8 , 0 , 0x80);	// ch3reg_hspdeq_thr
	gadc_dig_54_bx.hsprdeq_thr = 0xC4;
	VPORT_I2C_Write((UINT32*)&gadc_dig_54_bx);

	//20110425
	//L9A0 Initial Resettings by powerory

	offset.offset_R = ADC_L9_R_PRE_OFFSET_VALUE;
	offset.offset_G = ADC_L9_G_PRE_OFFSET_VALUE;
	offset.offset_B = ADC_L9_B_PRE_OFFSET_VALUE;

	ADC_L9Bx_SetOffsetRGB( &offset);

	gadc_dig_52_bx.hsdiff_thr_1 = 0x0;
	gadc_dig_53_bx.hsdiff_thr_0 = 0x0;
	VPORT_I2C_Write((UINT32*)&gadc_dig_52_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_53_bx);

	//110426 by powerory
	gadc_dig_222_bx.clamp_init = 0x0F;
	VPORT_I2C_Write((UINT32*)&gadc_dig_222_bx);

	//110426 by powerory	(Clamp position adjust)
	//gadc_dig_203_bx.blank_sp_0 = 0x80;	// default 0x04;

	//110513 by min
	gadc_dig_203_bx.blank_sp_0 = 0x60;	// default 0x04;
	VPORT_I2C_Write((UINT32*)&gadc_dig_203_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_204_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_209_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_215_bx);
	gadc_dig_204_bx.r_blank_mode = 0x1;
	gadc_dig_209_bx.g_blank_mode = 0x1;
	gadc_dig_215_bx.b_blank_mode = 0x1;
	VPORT_I2C_Write((UINT32*)&gadc_dig_204_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_209_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_215_bx);

	gadc_dig_220_bx.clamp_width = 0x14;
	VPORT_I2C_Write((UINT32*)&gadc_dig_220_bx);

	//110720 : changed cst_diff_thr value to 1 for valid coast on 1080i component input of BH-200.
	//Default value '3' is for abnormal vsync pulse of Divico component signal.
	gadc_dig_26_bx.cst_diff_thr_1 = 0x0;
	gadc_dig_27_bx.cst_diff_thr_0 = 0x1;
	VPORT_I2C_Write((UINT32*)&gadc_dig_26_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_27_bx);

	//110901 : powerory
	gadc_dig_257_bx.apa_sampling_counter_max = 0x3;
	VPORT_I2C_Write((UINT32*)&gadc_dig_257_bx);

	//110901 : powerory
	gadc_dig_243_bx.apa_wait_counter_max_2 = 0x1;
	gadc_dig_244_bx.apa_wait_counter_max_1 = 0x0;
	gadc_dig_245_bx.apa_wait_counter_max_0 = 0x0;
	VPORT_I2C_Write((UINT32*)&gadc_dig_243_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_244_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_245_bx);

	//111006 by wonsik : enable ADC auto mute (when LLPLL status is '0'), and disable TPG mute
	VPORT_I2C_Read((UINT32*)&gadc_dig_230_bx);
	gadc_dig_230_bx.mute_ctrl = 0x2;	// Auto Mute
	//gadc_dig_230_bx.mute_ctrl = 0x1;	// Manual Mute
	//gadc_dig_230_bx.mute_ctrl = 0x0;	// Normal Mode
	VPORT_I2C_Write((UINT32*)&gadc_dig_230_bx);

#ifdef	KDRV_CONFIG_PM
	if(gAdcPmInitial < 0)
	{
		gAdcPMData = (S_ADC_PM_DATA *)kmalloc(sizeof(S_ADC_PM_DATA) , GFP_KERNEL);
		gAdcPMData->giPmIndexValue = -1;
		gAdcPmInitial = 0;
	}
#endif
//	OS_MsecSleep(100);

	return 0;
}


int ADC_L9Bx_GetBoundaryInform(ST_EXTAU *inform)
{
	UINT16 out16 = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_182_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_183_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_184_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_185_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_186_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_187_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_188_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_189_bx);

	// get extau_up
	out16 = 0;
	inform->extau_up = 0;
	out16 =  (gadc_dig_182_bx.extau_up_result_1)&0x0F;
	inform->extau_up |= out16 << 8;
	out16 =  gadc_dig_183_bx.extau_up_result_0;
	inform->extau_up |= out16;

	// get extau_down
	out16 = 0;
	inform->extau_down = 0;
	out16 =  (gadc_dig_184_bx.extau_down_result_1)&0x0F;
	inform->extau_down |= out16 << 8;
	out16 =  gadc_dig_185_bx.extau_down_result_0;
	inform->extau_down |= out16;

	// get extau_left
	out16 = 0;
	inform->extau_left = 0;
	out16 =  (gadc_dig_186_bx.extau_left_result_1)&0x0F;
	inform->extau_left |= out16 << 8;
	out16 =  gadc_dig_187_bx.extau_left_result_0;
	inform->extau_left |= out16;
#ifdef ADC_BOUNDARY_COMPENSATION
	if(inform->extau_left >= 1)
	{
		inform->extau_left -= 1;
	}
#endif

	// get extau_lest
	out16 = 0;
	inform->extau_right = 0;
	out16 =  (gadc_dig_188_bx.extau_right_result_1)&0x0F;
	inform->extau_right |= out16 << 8;
	out16 =  gadc_dig_189_bx.extau_right_result_0;
	inform->extau_right |= out16;
#ifdef ADC_BOUNDARY_COMPENSATION
	if(inform->extau_right >= 1)
	{
		inform->extau_right -= 1;
	}
#endif

	return 0;
}

int ADC_L9Bx_SetTAUInform(S_EXTAU_VALUE *value)
{
	UINT32 hsout_tmp;
	// Height
	VPORT_I2C_Read((UINT32*)&gadc_dig_176_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_177_bx);
	gadc_dig_176_bx.extau_down_offset_1 = (value->height_offset&0xFF00)>>8;
	gadc_dig_177_bx.extau_down_offset_0 = value->height_offset&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_176_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_177_bx);

	// WIDTH
	VPORT_I2C_Read((UINT32*)&gadc_dig_180_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_181_bx);
	gadc_dig_180_bx.extau_right_offset_1 = (value->width_offset&0xFF00)>>8;
	gadc_dig_181_bx.extau_right_offset_0 = value->width_offset&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_180_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_181_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_170_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_171_bx);
	gadc_dig_170_bx.extau_ctrl_1 = (value->control&0xFF00)>>8;
	gadc_dig_171_bx.extau_ctrl_0 = value->control&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_170_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_171_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_172_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_173_bx);
	gadc_dig_172_bx.extau_level_1 = (value->level&0xFF00)>>8;
	gadc_dig_173_bx.extau_level_0 = value->level&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_172_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_173_bx);

	// For Proper Boundary Detection in case of PC RGB Horizontal Sync Crosstalk on RGB Signal, Adjusted left_offset.
	// Enlarge Value to 10 1019 for PC geforce 8400GS
	VPORT_I2C_Read((UINT32*)&gadc_dig_75_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_76_bx);
	hsout_tmp = ((gadc_dig_75_bx.ro_hsout_width_1 << 8) & 0xF00) + gadc_dig_76_bx.ro_hsout_width_0;
	hsout_tmp += 10;
	gadc_dig_178_bx.extau_left_offset_1 = (hsout_tmp >> 8) & 0x00F;
	gadc_dig_179_bx.extau_left_offset_0 = hsout_tmp & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_178_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_179_bx);

	return 0;
}

int ADC_L9Bx_SetRGBPosition(S_RGB_POSITION *pos)
{
	VPORT_I2C_Read((UINT32*)&gadc_dig_130_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_131_bx);
	gadc_dig_130_bx.ap_xpos_b_1 = (pos->width_b&0xFF00)>>8;
	gadc_dig_131_bx.ap_xpos_b_0 = pos->width_b&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_130_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_131_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_122_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_123_bx);
	gadc_dig_122_bx.ap_xpos_g_1 = (pos->width_g&0xFF00)>>8;
	gadc_dig_123_bx.ap_xpos_g_0 = pos->width_g&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_122_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_123_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_138_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_139_bx);
	gadc_dig_138_bx.ap_xpos_r_1 = (pos->width_r&0xFF00)>>8;
	gadc_dig_139_bx.ap_xpos_r_0 = pos->width_r&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_138_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_139_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_134_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_135_bx);
	gadc_dig_134_bx.ap_ypos_b_1 = (pos->height_b&0xFF00)>>8;
	gadc_dig_135_bx.ap_ypos_b_0 = pos->height_b&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_134_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_135_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_126_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_127_bx);
	gadc_dig_126_bx.ap_ypos_g_1 = (pos->height_g&0xFF00)>>8;
	gadc_dig_127_bx.ap_ypos_g_0 = pos->height_g&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_126_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_127_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_142_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_143_bx);
	gadc_dig_142_bx.ap_ypos_r_1 = (pos->height_r&0xFF00)>>8;
	gadc_dig_143_bx.ap_ypos_r_0 = pos->height_r&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_142_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_143_bx);

	return 0;
}

int ADC_L9Bx_GetRGBResult(S_RGB_OUT *result)
{
	UINT32 out32 = 0;

	result->out_b = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_146_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_147_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_148_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_149_bx);
	out32 =  gadc_dig_146_bx.ap_out_b_3;
	result->out_b |= out32 << 24;
	out32 =  gadc_dig_147_bx.ap_out_b_2;
	result->out_b |= out32 << 16;
	out32 =  gadc_dig_148_bx.ap_out_b_1;
	result->out_b |= out32 << 8;
	out32 =  gadc_dig_149_bx.ap_out_b_0;
	result->out_b |= out32;

	out32 = 0;
	result->out_g =	0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_150_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_151_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_152_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_153_bx);
	out32 =  gadc_dig_150_bx.ap_out_g_3;
	result->out_g |= out32 << 24;
	out32 =  gadc_dig_151_bx.ap_out_g_2;
	result->out_g |= out32 << 16;
	out32 =  gadc_dig_152_bx.ap_out_g_1;
	result->out_g |= out32 << 8;
	out32 =  gadc_dig_153_bx.ap_out_g_0;
	result->out_g |= out32;

	out32 = 0;
	result->out_r =	0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_154_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_155_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_156_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_157_bx);
	out32 =  gadc_dig_154_bx.ap_out_r_3;
	result->out_r |= out32 << 24;
	out32 =  gadc_dig_155_bx.ap_out_r_2;
	result->out_r |= out32 << 16;
	out32 =  gadc_dig_156_bx.ap_out_r_1;
	result->out_r |= out32 << 8;
	out32 =  gadc_dig_157_bx.ap_out_r_0;
	result->out_r |= out32;

	return 0;
}

int ADC_L9Bx_GetRGBPosition(S_RGB_POSITION *pos)
{
	UINT16 out16 = 0;

	pos->width_b = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_130_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_131_bx);
	out16 =  (gadc_dig_130_bx.ap_xpos_b_1)&0x0F;
	pos->width_b |= out16 << 8;
	out16 =  gadc_dig_131_bx.ap_xpos_b_0;
	pos->width_b |= out16;

	out16 = 0;
	pos->width_g =	0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_122_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_123_bx);
	out16 =  (gadc_dig_122_bx.ap_xpos_g_1)&0x0F;
	pos->width_g |= out16 << 8;
	out16 =  gadc_dig_123_bx.ap_xpos_g_0;
	pos->width_g |= out16;

	out16 = 0;
	pos->width_r =	0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_138_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_139_bx);
	out16 =  (gadc_dig_138_bx.ap_xpos_r_1)&0x0F;
	pos->width_r |= out16 << 8;
	out16 =  gadc_dig_139_bx.ap_xpos_r_0;
	pos->width_r |= out16;

	out16 = 0;
	pos->height_b = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_134_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_135_bx);
	out16 =  (gadc_dig_134_bx.ap_ypos_b_1)&0x0F;
	pos->height_b |= out16 << 8;
	out16 =  gadc_dig_135_bx.ap_ypos_b_0;
	pos->height_b |= out16;

	out16 = 0;
	pos->height_g =	0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_126_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_127_bx);
	out16 =  (gadc_dig_126_bx.ap_ypos_g_1)&0x0F;
	pos->height_g |= out16 << 8;
	out16 =  gadc_dig_127_bx.ap_ypos_g_0;
	pos->height_g |= out16;

	out16 = 0;
	pos->height_r =	0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_142_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_143_bx);
	out16 =  (gadc_dig_142_bx.ap_ypos_r_1)&0x0F;
	pos->height_r |= out16 << 8;
	out16 =  gadc_dig_143_bx.ap_ypos_r_0;
	pos->height_r |= out16;

	return 0;
}

int ADC_L9Bx_SetRGBSize(S_RGB_SIZE *size)
{
	VPORT_I2C_Read((UINT32*)&gadc_dig_132_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_133_bx);
	gadc_dig_132_bx.ap_xsize_b_1 = (size->width_b&0xFF00)>>8;
	gadc_dig_133_bx.ap_xsize_b_0 = size->width_b&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_132_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_133_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_124_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_125_bx);
	gadc_dig_124_bx.ap_xsize_g_1 = (size->width_g&0xFF00)>>8;
	gadc_dig_125_bx.ap_xsize_g_0 = size->width_g&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_124_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_125_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_140_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_141_bx);
	gadc_dig_140_bx.ap_xsize_r_1 = (size->width_r&0xFF00)>>8;
	gadc_dig_141_bx.ap_xsize_r_0 = size->width_r&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_140_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_141_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_136_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_137_bx);
	gadc_dig_136_bx.ap_ysize_b_1 = (size->height_b&0xFF00)>>8;
	gadc_dig_137_bx.ap_ysize_b_0 = size->height_b&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_136_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_137_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_128_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_129_bx);
	gadc_dig_128_bx.ap_ysize_g_1 = (size->height_g&0xFF00)>>8;
	gadc_dig_129_bx.ap_ysize_g_0 = size->height_g&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_128_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_129_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_144_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_145_bx);
	gadc_dig_144_bx.ap_ysize_r_1 = (size->height_r&0xFF00)>>8;
	gadc_dig_145_bx.ap_ysize_r_0 = size->height_r&0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_144_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_145_bx);

	return 0;
}

int ADC_L9Bx_GetSizeValue(S_VIDEO_SIZE_INFORM *size)
{
	UINT16 out16 = 0;
	UINT32 out32 = 0;

	size->ext_vsize = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_114_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_115_bx);
	out16 =  (gadc_dig_114_bx.sd_ext_vsize_1)&0x0F;
	size->ext_vsize |= out16 << 8;
	out16 =  gadc_dig_115_bx.sd_ext_vsize_0;
	size->ext_vsize |= out16;

	out32 = 0;
	size->vd_vsize= 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_116_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_117_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_118_bx);
	out32 =  (gadc_dig_116_bx.sd_vd_vsize_2)&0x7F;
	size->vd_vsize |= out32 << 16;
	out32 =  gadc_dig_117_bx.sd_vd_vsize_1;
	size->vd_vsize |= out32 << 8;
	out32 =  gadc_dig_118_bx.sd_vd_vsize_0;
	size->vd_vsize |= out32;

	out16 = 0;
	size->vd_hsize= 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_119_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_120_bx);
	out16 =  (gadc_dig_119_bx.sd_vd_hsize_1)&0x1F;
	size->vd_hsize |= out16 << 8;
	out16 =  gadc_dig_120_bx.sd_vd_hsize_0;
	size->vd_hsize |= out16;

	VPORT_I2C_Read((UINT32*)&gadc_dig_29_bx);

	size->polarity = (gadc_dig_29_bx.ro_hspol<<1) | (gadc_dig_29_bx.ro_vspol);

	//111020 for composite sync support
#if 0
	if( gADC_type == LX_ADC_INPUT_SOURCE_RGB_PC)
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_34_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_35_bx);
		out16 =  (gadc_dig_34_bx.ro_vsprdref_1)&0x1F;
		out32 = out16 << 8;
		out16 =  gadc_dig_35_bx.ro_vsprdref_0;
		out32 |= out16;

		if(out32 < 100)
		{
			AFE_PRINT("VTotal [%d]\n", out32);
			VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
			gadc_dig_22_bx.compover = 0x1;
			gadc_dig_22_bx.compuser = 0x1;
			VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
		}
		else
		{
			VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
			gadc_dig_22_bx.compover = 0x1;
			gadc_dig_22_bx.compuser = 0x0;
			VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
		}
		//if(gadc_dig_29_bx.ro_interlaced)
		//{
		//	AFE_PRINT("RGB Interlaced mode\n");
		//	VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
		//	gadc_dig_22_bx.compover = 0x1;
		//	gadc_dig_22_bx.compuser = 0x1;
		//	VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
		//}
		//else
		//{
		//	VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
		//	gadc_dig_22_bx.compover = 0x1;
		//	gadc_dig_22_bx.compuser = 0x0;
		//	VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
		//}
	}
#endif

	return 0;
}

int ADC_L9Bx_SetPort(S_SEL_PORT *sel_port)
{

#ifdef	KDRV_CONFIG_PM
	memcpy((void *)&gAdcPMData->gstPmSelPortValue , (void *)sel_port , sizeof(S_SEL_PORT));
#endif
	//AFE_PRINT("ADC_SetPort \n");

	AFE_PRINT("ADC_SetPort : sel_port->port = [%d] \n", sel_port->port);

	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_selmux = sel_port->port;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	/*
	VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
	gadc_dig_22_bx.compover = sel_port->compover;
	gadc_dig_22_bx.compover = sel_port->compuser;
	VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
	*/

	return 0;
}

int ADC_L9Bx_GetSelectedPort(void)
{
	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);

	return	gafe_3ch_0_bx.afe3ch_selmux;
}

unsigned int ADC_L9Bx_GetPhaseValue(void)
{
	UINT32 ret = 0;

	VPORT_I2C_Read((UINT32*)&gllpll_4_bx);
// won.hur : Modified for L9A1->L9B0 migration=> llpll_shift_1 name has been changed to llpll_shift_man_1
	ret = gllpll_4_bx.llpll_shift_man_1;
	ret = ret << 8;
	VPORT_I2C_Read((UINT32*)&gllpll_5_bx);//fix bug 120502
// won.hur : Modified for L9A1->L9B0 migration=> llpll_shift_0 name has been changed to llpll_shift_man_0
	ret |= gllpll_5_bx.llpll_shift_man_0;

	return ret;
}

int ADC_L9Bx_SetPhaseValue(unsigned int phase)
{
	UINT16 tmp16 = 0;
//	AFE_PRINT("######### Set ADC Phase Register to [%d][0x%x]\n", phase,phase );
	ADC_DEBUG("%s entered with value [0x%x]\n", __func__, phase);

	tmp16 = phase;
	tmp16 = tmp16 >> 8;
// won.hur : Modified for L9A1->L9B0 migration=> llpll_shift_1 name has been changed to llpll_shift_man_1
	gllpll_4_bx.llpll_shift_man_1 = tmp16 & 0x3;
	tmp16 = phase & 0xFF;

// won.hur : Modified for L9A1->L9B0 migration=> llpll_shift_0 name has been changed to llpll_shift_man_0
	gllpll_5_bx.llpll_shift_man_0 = tmp16;

	VPORT_I2C_Write((UINT32*)&gllpll_4_bx);
	VPORT_I2C_Write((UINT32*)&gllpll_5_bx);

	return 0;
}

unsigned int ADC_L9Bx_GetScanType(void)
{
	unsigned int ret = 0, tmp = 0;
	UINT8	count=0;

	for(;count<INTERLACE_CHECK_COUNT;count++)
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_29_bx);

		tmp = gadc_dig_29_bx.ro_interlaced;
		ret += tmp^1;
	}

//	AFE_PRINT("* Interlace check count value = [%d]\n", ret);

	if(ret > (INTERLACE_CHECK_COUNT/2))
		return 1;
	else
		return 0;

}


int ADC_L9Bx_SetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain)
{
	int ret = 0;

	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, stGain->R_Gain_Value, stGain->G_Gain_Value, stGain->B_Gain_Value);

	gadc_dig_0_bx.r_pre_gain_1 = (stGain->R_Gain_Value >> 8) & 0x3F;
	gadc_dig_1_bx.r_pre_gain_0 = (stGain->R_Gain_Value ) & 0xFF;
	gadc_dig_2_bx.g_pre_gain_1 = (stGain->G_Gain_Value >> 8) & 0x3F;
	gadc_dig_3_bx.g_pre_gain_0 = (stGain->G_Gain_Value ) & 0xFF;
	gadc_dig_4_bx.b_pre_gain_1 = (stGain->B_Gain_Value >> 8) & 0x3F;
	gadc_dig_5_bx.b_pre_gain_0 = (stGain->B_Gain_Value ) & 0xFF;

	//111123 wonsik.do
	user_gain_value.R_Gain_Value = stGain->R_Gain_Value;
	user_gain_value.G_Gain_Value = stGain->G_Gain_Value;
	user_gain_value.B_Gain_Value = stGain->B_Gain_Value;

	VPORT_I2C_Write((UINT32*)&gadc_dig_0_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_1_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_2_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_3_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_4_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_5_bx);
	return ret;
}

int ADC_L9Bx_GetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain)
{
	int ret = 0;

	VPORT_I2C_Read((UINT32*)&gadc_dig_0_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_1_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_2_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_3_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_4_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_5_bx);
	stGain->R_Gain_Value = gadc_dig_0_bx.r_pre_gain_1 << 8 | gadc_dig_1_bx.r_pre_gain_0;
	stGain->G_Gain_Value = gadc_dig_2_bx.g_pre_gain_1 << 8 | gadc_dig_3_bx.g_pre_gain_0;
	stGain->B_Gain_Value = gadc_dig_4_bx.b_pre_gain_1 << 8 | gadc_dig_5_bx.b_pre_gain_0;

	return ret;
}


int ADC_L9Bx_SetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset)
{
	int ret = 0;

	gadc_dig_224_bx.r_pre_offset_1 = (stOffset->R_Offset_Value >> 8) & 0x1F;
	gadc_dig_225_bx.r_pre_offset_0 = stOffset->R_Offset_Value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_224_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_225_bx);

	gadc_dig_226_bx.g_pre_offset_1 = (stOffset->G_Offset_Value >> 8) & 0x1F;
	gadc_dig_227_bx.g_pre_offset_0 = stOffset->G_Offset_Value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_226_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_227_bx);

	gadc_dig_228_bx.b_pre_offset_1 = (stOffset->B_Offset_Value >> 8) & 0x1F;
	gadc_dig_229_bx.b_pre_offset_0 = stOffset->B_Offset_Value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_228_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_229_bx);


	return ret;
}

int ADC_L9Bx_GetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset)
{
	int ret = 0;

	VPORT_I2C_Read((UINT32*)&gadc_dig_224_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_225_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_226_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_227_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_228_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_229_bx);
	stOffset->R_Offset_Value = gadc_dig_224_bx.r_pre_offset_1 << 8 | gadc_dig_225_bx.r_pre_offset_0;
	stOffset->G_Offset_Value = gadc_dig_226_bx.g_pre_offset_1 << 8 | gadc_dig_227_bx.g_pre_offset_0;
	stOffset->B_Offset_Value = gadc_dig_228_bx.b_pre_offset_1 << 8 | gadc_dig_229_bx.b_pre_offset_0;

	return ret;
}


/**
 *
 * setting the LLPLL by index value which came from ADC_IFM_SearchTable
 *
 * @param	S_VIDEO_SIZE_INFORM
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_L9Bx_SetInputVideo(int iIndex)
{

//	int i;
	UINT32 hsout_width =0;
	//UINT8	llpll_filter_status;

	int ret = 0;

#ifdef	KDRV_CONFIG_PM
	gAdcPMData->giPmIndexValue = iIndex;
#endif
	ADC_DEBUG("%s entered with value [%d]\n", __func__, iIndex);

	VPORT_I2C_Read((UINT32*)&gadc_dig_74_bx);

	//For SCART RGB, Do not inverted field.
//	if((iIndex == 306)&& (gADC_type == LX_ADC_INPUT_SOURCE_YPBPR))// for Component 576i 50Hz field indication should be inverted
	// in case of input source change from scart RGB to component with same resolution fld_inv bit can't not be set.
	// inv_inv bit has no effect on SCART RGB input.
	if((iIndex == 306))
	{
		gadc_dig_74_bx.fld_inv = 0x1;
	}
	else
	{
		gadc_dig_74_bx.fld_inv = 0x0;
	}

	VPORT_I2C_Write((UINT32*)&gadc_dig_74_bx);

	hsout_width = HS_Out_Width[iIndex];

	//From L9B0 revisioin minimum hsync width is reduced to '4'
	if(hsout_width < 4)
		hsout_width = 4;

	ADC_DEBUG("Hsout_width = [%d]\n", hsout_width);

	VPORT_I2C_Read((UINT32*)&gadc_dig_59_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_60_bx);

#ifdef COMP_4X_OVERSAMPLING
	if( (iIndex == 303) || (iIndex == 306)|| (iIndex == 304)|| (iIndex == 307))	// component 480i / 576i/480p/576p
		hsout_width *= 4;
#else
	if( (iIndex == 303) || (iIndex == 306))	// component 480i / 576i
		hsout_width *= 2;
#endif

	gadc_dig_59_bx.hsout_width_1 = (hsout_width >> 8) & 0x0F;
	gadc_dig_60_bx.hsout_width_0 = hsout_width & 0xFF;

	VPORT_I2C_Write((UINT32*)&gadc_dig_59_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_60_bx);

#ifdef COMP_4X_OVERSAMPLING
	if(iIndex == 303)	// component 480i
	{
		iIndex = 336;	// 4X oversampling
		ADC_DEBUG("for Component 480i, enable subsampling\n");

		VPORT_I2C_Read((UINT32*)&gadc_dig_223_bx);
		gadc_dig_223_bx.sub_sampling_en = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_223_bx);
	}
	else if(iIndex == 304)	// component 480p
	{
		iIndex = 337;	// 4X oversampling
		ADC_DEBUG("for Component 480p, enable subsampling\n");

		VPORT_I2C_Read((UINT32*)&gadc_dig_223_bx);
		gadc_dig_223_bx.sub_sampling_en = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_223_bx);
	}
	else if(iIndex == 306)
	{
		iIndex = 338;	// 4X oversampling
		ADC_DEBUG("for Component 576i, enable subsampling\n");

		VPORT_I2C_Read((UINT32*)&gadc_dig_223_bx);
		gadc_dig_223_bx.sub_sampling_en = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_223_bx);
	}
	else if(iIndex == 307)	// component 480p
	{
		iIndex = 339;	// 4X oversampling
		ADC_DEBUG("for Component 576p, enable subsampling\n");

		VPORT_I2C_Read((UINT32*)&gadc_dig_223_bx);
		gadc_dig_223_bx.sub_sampling_en = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_223_bx);
	}
#else
	if(iIndex == 303)	// component 480i
	{
		iIndex = 304;	// Use 480P timing
		ADC_DEBUG("for Component 480i, enable subsampling\n");

		VPORT_I2C_Read((UINT32*)&gadc_dig_223_bx);
		gadc_dig_223_bx.sub_sampling_en = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_223_bx);
	}
	else if(iIndex == 306)
	{
		iIndex = 307;	// Use 576P timing
		ADC_DEBUG("for Component 576i, enable subsampling\n");

		VPORT_I2C_Read((UINT32*)&gadc_dig_223_bx);
		gadc_dig_223_bx.sub_sampling_en = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_223_bx);
	}
#endif
	else
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_223_bx);
		gadc_dig_223_bx.sub_sampling_en = 0x0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_223_bx);
	}

	//CH3_LLPLL_003
	VPORT_I2C_Read((UINT32*)&gllpll_1_bx);
	gllpll_1_bx.llpll_div_max = (LLPLL_div_max[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_1_bx);

	//LLPLL_counter_max
	VPORT_I2C_Read((UINT32*)&gllpll_2_bx);
	VPORT_I2C_Read((UINT32*)&gllpll_3_bx);
	gllpll_2_bx.llpll_counter_max_1 = ((LLPLL_counter_max[iIndex])&0xF00)>>8;
	gllpll_3_bx.llpll_counter_max_0 = (LLPLL_counter_max[iIndex])&0xFF;
	VPORT_I2C_Write((UINT32*)&gllpll_2_bx);
	VPORT_I2C_Write((UINT32*)&gllpll_3_bx);

	//LLPLL_shift 일단 0으로 초기화
	VPORT_I2C_Read((UINT32*)&gllpll_4_bx);
	VPORT_I2C_Read((UINT32*)&gllpll_5_bx);
	// won.hur : Modified for L9A1->L9B0 migration=> llpll_shift_1 name has been changed to llpll_shift_man_1
	gllpll_4_bx.llpll_shift_man_1 = 0;
	// won.hur : Modified for L9A1->L9B0 migration=> llpll_shift_0 name has been changed to llpll_shift_man_0
	gllpll_5_bx.llpll_shift_man_0 = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_4_bx);
	VPORT_I2C_Write((UINT32*)&gllpll_5_bx);

	//LLPLL_dco_max
	VPORT_I2C_Read((UINT32*)&gllpll_7_bx);
	gllpll_7_bx.llpll_dco_max = (LLPLL_dco_max[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_7_bx);

	//LLPLL_dco_min
	VPORT_I2C_Read((UINT32*)&gllpll_8_bx);
	gllpll_8_bx.llpll_dco_min = (LLPLL_dco_min[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_8_bx);

	//LLPLL_coarse_scale
	VPORT_I2C_Read((UINT32*)&gllpll_9_bx);
	gllpll_9_bx.llpll_coarse_scale = (LLPLL_coarse_scale[iIndex])&0xF;
	VPORT_I2C_Write((UINT32*)&gllpll_9_bx);

	//LLPLL_g1_nom
	VPORT_I2C_Read((UINT32*)&gllpll_10_bx);
	gllpll_10_bx.llpll_g1_nom = (LLPLL_g1_nom[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_10_bx);

	//LLPLL_g2_nom
	VPORT_I2C_Read((UINT32*)&gllpll_11_bx);
	gllpll_11_bx.llpll_g2_nom = (LLPLL_g2_nom[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_11_bx);

	//LLPLL_g3_p_nom
	VPORT_I2C_Read((UINT32*)&gllpll_12_bx);
	gllpll_12_bx.llpll_g3_p_nom = (LLPLL_g3_p_nom[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_12_bx);

	//LLPLL_g3_n_nom
	VPORT_I2C_Read((UINT32*)&gllpll_13_bx);
	gllpll_13_bx.llpll_g3_n_nom = (LLPLL_g3_n_nom[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_13_bx);

	//LLPLL_g1_fine
	VPORT_I2C_Read((UINT32*)&gllpll_14_bx);
	gllpll_14_bx.llpll_g1_fine = (LLPLL_g1_fine[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_14_bx);

	//LLPLL_g2_fine
	VPORT_I2C_Read((UINT32*)&gllpll_15_bx);
	gllpll_15_bx.llpll_g2_fine = (LLPLL_g2_fine[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_15_bx);

	//LLPLL_g3_p_fine
	VPORT_I2C_Read((UINT32*)&gllpll_16_bx);
	gllpll_16_bx.llpll_g3_p_fine = (LLPLL_g3_p_fine[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_16_bx);

	//LLPLL_g3_n_fine
	VPORT_I2C_Read((UINT32*)&gllpll_17_bx);
	gllpll_17_bx.llpll_g3_n_fine = (LLPLL_g3_n_fine[iIndex])&0x1F;
	VPORT_I2C_Write((UINT32*)&gllpll_17_bx);

	/*
	for( i = 0 ; i < 30 ; i++)
	{
		VPORT_I2C_Read((UINT32*)&gllpll_27_bx);
		llpll_filter_status = gllpll_27_bx.llpll_filter_status;
		if(llpll_filter_status == 3) break;
		OS_MsecSleep(5);
	}
	if(i==30)
	{
		AFE_PRINT("!!!!!!!!!!!! LLPLL UNLOCK !!!!!!!!!!!!!!!!!\n");
		ADC_Reset_LLPLL();
		ret = -1;
	}
	*/



	VPORT_I2C_Read((UINT32*)&gadc_dig_204_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_209_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_214_bx);

	gadc_dig_204_bx.r_blank_num_clear = 1;
	gadc_dig_209_bx.g_blank_num_clear = 1;
	gadc_dig_214_bx.b_blank_num_clear = 1;

	VPORT_I2C_Write((UINT32*)&gadc_dig_204_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_209_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_214_bx);

	gadc_dig_204_bx.r_blank_num_clear = 0;
	gadc_dig_209_bx.g_blank_num_clear = 0;
	gadc_dig_214_bx.b_blank_num_clear = 0;

	VPORT_I2C_Write((UINT32*)&gadc_dig_204_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_209_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_214_bx);

	/*
	if(i<100)
		return 0;
	else
		return -1;
		*/

	return ret;
}

int ADC_L9Bx_Check_LLPLL_status(void)
{
	int i;
	int ret = 0;

	//ADC_DEBUG("%s entered \n", __func__);

	for( i = 0 ; i < 30 ; i++)
	{
		VPORT_I2C_Read((UINT32*)&gllpll_27_bx);
		if(gllpll_27_bx.llpll_filter_status == 3) break;
		OS_MsecSleep(5);
	}
	if(i==30)
	{
		AFE_PRINT("!!!!!!!!!!!! LLPLL UNLOCK !!!!!!!!!!!!!!!!!\n");
		ADC_Reset_LLPLL();
		ret = -1;
	}

	return ret;
}

int ADC_L9Bx_AGOCInit(void)
{
	ST_GAIN_INFORM *gain_temp;

	ADC_DEBUG("%s entered \n", __func__);

	gain_temp = (ST_GAIN_INFORM *)kmalloc(sizeof(ST_GAIN_INFORM),GFP_KERNEL);

	//111123 wonsik.do
	VPORT_I2C_Read((UINT32*)&gadc_dig_89_bx);
	gadc_dig_89_bx.aogc_src_sel = 0x0;
	gadc_dig_89_bx.aogc_enable_sel = 0x0;
	VPORT_I2C_Write((UINT32*)&gadc_dig_89_bx);

	// aogc conter set as max
	VPORT_I2C_Read((UINT32*)&gadc_dig_99_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_100_bx);
	gadc_dig_99_bx.aogc_counter_max_1 = 0xFF;
	gadc_dig_100_bx.aogc_counter_max_0 = 0xFE;
	VPORT_I2C_Write((UINT32*)&gadc_dig_99_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_100_bx);

	VPORT_I2C_Read((UINT32*)&gadc_dig_98_bx);
	gadc_dig_98_bx.aogc_sample_count = 0x6;
	VPORT_I2C_Write((UINT32*)&gadc_dig_98_bx);

	//110504 by powerory
	VPORT_I2C_Read((UINT32*)&gadc_dig_96_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_97_bx);
	gadc_dig_96_bx.aogc_th_1 = 0x03;
	gadc_dig_97_bx.aogc_th_0 = 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_96_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_97_bx);

	//Add From B0 Revision(Auto Calibration)
	VPORT_I2C_Read((UINT32*)&gadc_dig_98_bx);
	gadc_dig_98_bx.aogc_sample_accum = 0;
	VPORT_I2C_Write((UINT32*)&gadc_dig_98_bx);

#if 0
	// removed from B0
	// aoc, agc sel register
	gVportRegBx->ch3reg_agc_ire.ch3reg_agc_ire = 3;
	gVportRegBx->ch3reg_agc_ire.ch3reg_aoc_ire = 4;
#endif
//	gVportRegBx->ch3_adc_007.afe3ch_ire_sel = 4;

	//TODO :dws
	// First set gain value to default
	gain_temp->gain_R = 0x1000;
	gain_temp->gain_G = 0x1000;
	gain_temp->gain_B = 0x1000;

	ADC_SetGainRGB(gain_temp);

	return 0;
}

/**
 *
 * setting ADC IRE test enable/disable
 *
 * @param	0 : inactive , 1 : active
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_L9Bx_SetIRETestMode(int sel , E_AGC_IRE mode)
{
	int ret = 0;


	if(sel)	// IRE Test mode inactive
	{
		//by dws 110520 : ADC_AGOCInit is already executed before.
		//ADC_AGOCInit();

		//VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
		//giSelMuxBackup = gafe_3ch_0_bx.afe3ch_selmux;

		// aogc test start
		VPORT_I2C_Read((UINT32*)&gadc_dig_89_bx);
		gadc_dig_89_bx.aogc_enable = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_89_bx);

		// 110503 by powerory
		// 111103 by wonsik.do : digital reset still needed on L9B0 ???
		ADC_L9Bx_Reset_Digital();

		OS_MsecSleep(20);
	}
	else	// IRE Test mode active
	{
		//VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
		//gafe_3ch_0_bx.afe3ch_selmux = giSelMuxBackup;
		//VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

		// aogc test stop
		VPORT_I2C_Read((UINT32*)&gadc_dig_89_bx);
		gadc_dig_89_bx.aogc_enable = 0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_89_bx);
	}
	return ret;
}

/**
 *
 * get RGB average value from register
 *
 * @param	ST_GAIN_INFORM
 * @return	0 : OK , -1 : NOK
 *
*/

int ADC_L9Bx_GetIRELevel( S_GAIN_TARGET *gain)
{
	int ret = 0;
	unsigned int temp_r, temp_g,temp_b;
	UINT32 out32 = 0;

	temp_r = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_102_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_103_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_104_bx);
	out32 =  gadc_dig_102_bx.ro_avg_r_2;
	temp_r |= out32 << 16;
	out32 =  gadc_dig_103_bx.ro_avg_r_1;
	temp_r |= out32 << 8;
	out32 =  gadc_dig_104_bx.ro_avg_r_0;
	temp_r |= out32;

	out32 = 0;
	temp_g = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_105_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_106_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_107_bx);
	out32 =  gadc_dig_105_bx.ro_avg_g_2;
	temp_g |= out32 << 16;
	out32 =  gadc_dig_106_bx.ro_avg_g_1;
	temp_g |= out32 << 8;
	out32 =  gadc_dig_107_bx.ro_avg_g_0;
	temp_g |= out32;

	out32 = 0;
	temp_b = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_108_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_109_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_110_bx);
	out32 =  gadc_dig_108_bx.ro_avg_b_2;
	temp_b |= out32 << 16;
	out32 =  gadc_dig_109_bx.ro_avg_b_1;
	temp_b |= out32 << 8;
	out32 =  gadc_dig_110_bx.ro_avg_b_0;
	temp_b |= out32;


// powerory 2010-12-10
	//gain->gain_R = (float)( (temp_r&0xffff00) >> 8) + (float)(temp_r&0xff)/256.0;
	//gain->gain_G = (float)( (temp_g&0xffff00) >> 8) + (float)(temp_g&0xff)/256.0;
	//gain->gain_B = (float)( (temp_b&0xffff00) >> 8) + (float)(temp_b&0xff)/256.0;
//~powerory

	//120103 wonsik.do : removed floating point in kernel driver
//	gain->gain_R = (float)( (temp_r&0xffc000) >> 14) + (float)(temp_r&0x3fff)/16384.0;
//	gain->gain_G = (float)( (temp_g&0xffc000) >> 14) + (float)(temp_g&0x3fff)/16384.0;
//	gain->gain_B = (float)( (temp_b&0xffc000) >> 14) + (float)(temp_b&0x3fff)/16384.0;
	gain->gain_R = temp_r;
	gain->gain_G = temp_g;
	gain->gain_B = temp_b;
	//by dws
	//gain->gain_R = (float)( (temp_r&0xffe000) >> 13) + (float)(temp_r&0x1fff)/8192.0;
	//gain->gain_G = (float)( (temp_g&0xffe000) >> 13) + (float)(temp_g&0x1fff)/8192.0;
	//gain->gain_B = (float)( (temp_b&0xffe000) >> 13) + (float)(temp_b&0x1fff)/8192.0;


	//ADC_DEBUG("IRE level 1 : R[%d] , G[%d] , B[%d] \n",(int)gain->gain_R, (int)gain->gain_G , (int)gain->gain_B );

	return ret;

}


/**
 *
 * set IRE value for R,G,B
 *
 * @param	S_VIDEO_SIZE_INFORM
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_L9Bx_SetIRELevel(E_AGC_IRE ire , S_GAIN_TARGET *gain)
{
	int ret = 0;
	unsigned short target_ire;
	int wait_count = 0;


	switch(ire)
	{
		case 	IRE0:
		case	IRE0_RGB:
		case	IRE0_COMP:
			target_ire = 0;
		break;
		case 	IRE73:		//1
			target_ire = 73;
			ire = IRE73_L9;		//0
		break;
		case 	IRE950:		//2
			target_ire = 950;
			ire = IRE950_L9;	//3
		break;
		case 	IRE1023:
			target_ire = 1023;
		break;

		default:
			target_ire = 0;
			AFE_PRINT("WARNING : Invalid E_AGC_IRE type\n");
		break;
	}

	// set IRE
	//gVportRegBx->ch3_adc_007.ch3reg_adc_ire_sel_man = ire;
	VPORT_I2C_Read((UINT32*)&gafe_3ch_1_bx);
	gafe_3ch_1_bx.afe3ch_ire_sel = ire;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_1_bx);

//	ADC_DEBUG("IRE level set %d\n",ire);

	// set target value
	if(ire == IRE0_COMP){
		gadc_dig_90_bx.r_compare_1 = ((512)&0x300)>>8;
		gadc_dig_91_bx.r_compare_0 = ((512)&0xFF);
		VPORT_I2C_Write((UINT32*)&gadc_dig_90_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_91_bx);

		gadc_dig_92_bx.g_compare_1 = ((target_ire)&0x300)>>8;
		gadc_dig_93_bx.g_compare_0 = ((target_ire)&0xFF);
		VPORT_I2C_Write((UINT32*)&gadc_dig_92_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_93_bx);

		gadc_dig_94_bx.b_compare_1 = ((512)&0x300)>>8;
		gadc_dig_95_bx.b_compare_0 = ((512)&0xFF);
		VPORT_I2C_Write((UINT32*)&gadc_dig_94_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_95_bx);
	}
	else
	{
		gadc_dig_90_bx.r_compare_1 = ((target_ire)&0x300)>>8;
		gadc_dig_91_bx.r_compare_0 = ((target_ire)&0xFF);
		VPORT_I2C_Write((UINT32*)&gadc_dig_90_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_91_bx);

		gadc_dig_92_bx.g_compare_1 = ((target_ire)&0x300)>>8;
		gadc_dig_93_bx.g_compare_0 = ((target_ire)&0xFF);
		VPORT_I2C_Write((UINT32*)&gadc_dig_92_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_93_bx);

		gadc_dig_94_bx.b_compare_1 = ((target_ire)&0x300)>>8;
		gadc_dig_95_bx.b_compare_0 = ((target_ire)&0xFF);
		VPORT_I2C_Write((UINT32*)&gadc_dig_94_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_95_bx);
	}

	giAgocIntDone = 0;		// prevent invoking the interrupt before on time
	ADC_SetIRETestMode(1 , ire);
//	OS_MsecSleep(500);

#if 0
	wait_event_interruptible_timeout(agoc_done , giAgocIntDone != 0 , msecs_to_jiffies(300) );

	giAgocIntDone = 0;
#else
	for(;wait_count < 50; wait_count++)
	{
		OS_MsecSleep(10);
		if(ADC_L9Bx_Read_AGOC_State() == 0)
			break;
		ADC_DEBUG("AGOC State Check loop [%d]\n", wait_count);
	}
	if(wait_count == 50)
		AFE_ERROR("@@@@@ AGOC NOT COMPLETED !!! @@@@@\n");

#endif

	ADC_L9Bx_GetIRELevel(gain);
	ADC_SetIRETestMode(0 , ire);
	return ret;
}

int ADC_L9Bx_SetAgocWakeup(void)
{

	giAgocIntDone = 1;
	wake_up_interruptible(&agoc_done);

	return 0;
}

int ADC_L9Bx_GetGainRGB( ST_GAIN_INFORM *gain)
{
	VPORT_I2C_Read((UINT32*)&gadc_dig_0_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_1_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_2_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_3_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_4_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_5_bx);
	gain->gain_R = gadc_dig_0_bx.r_pre_gain_1 << 8 | gadc_dig_1_bx.r_pre_gain_0;
	gain->gain_G = gadc_dig_2_bx.g_pre_gain_1 << 8 | gadc_dig_3_bx.g_pre_gain_0;
	gain->gain_B = gadc_dig_4_bx.b_pre_gain_1 << 8 | gadc_dig_5_bx.b_pre_gain_0;

	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, gain->gain_R, gain->gain_G, gain->gain_B);

	return 0;
}

int ADC_L9Bx_SetGainRGB( ST_GAIN_INFORM *gain)
{
	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, gain->gain_R, gain->gain_G, gain->gain_B);

	gadc_dig_0_bx.r_pre_gain_1 = (gain->gain_R >> 8) & 0x3F;
	gadc_dig_1_bx.r_pre_gain_0 = (gain->gain_R ) & 0xFF;
	gadc_dig_2_bx.g_pre_gain_1 = (gain->gain_G >> 8) & 0x3F;
	gadc_dig_3_bx.g_pre_gain_0 = (gain->gain_G ) & 0xFF;
	gadc_dig_4_bx.b_pre_gain_1 = (gain->gain_B >> 8) & 0x3F;
	gadc_dig_5_bx.b_pre_gain_0 = (gain->gain_B ) & 0xFF;

	VPORT_I2C_Write((UINT32*)&gadc_dig_0_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_1_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_2_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_3_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_4_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_5_bx);

	return 0;
}


int ADC_L9Bx_GetOffsetRGB( S_OFFSET_INFORM *offset)
{

	VPORT_I2C_Read((UINT32*)&gadc_dig_224_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_225_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_226_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_227_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_228_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_229_bx);
	offset->offset_R = gadc_dig_224_bx.r_pre_offset_1 << 8 | gadc_dig_225_bx.r_pre_offset_0;
	offset->offset_G = gadc_dig_226_bx.g_pre_offset_1 << 8 | gadc_dig_227_bx.g_pre_offset_0;
	offset->offset_B = gadc_dig_228_bx.b_pre_offset_1 << 8 | gadc_dig_229_bx.b_pre_offset_0;

	return 0;
}

int ADC_L9Bx_SetOffsetRGB( S_OFFSET_INFORM *offset)
{

	ADC_DEBUG("%s with value R[0x%x],G[0x%x],B[0x%x]\n", __func__, offset->offset_R, offset->offset_G, offset->offset_B);

	gadc_dig_224_bx.r_pre_offset_1 = (offset->offset_R >> 8) & 0x1F;
	gadc_dig_225_bx.r_pre_offset_0 = offset->offset_R & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_224_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_225_bx);

	gadc_dig_226_bx.g_pre_offset_1 = (offset->offset_G >> 8) & 0x1F;
	gadc_dig_227_bx.g_pre_offset_0 = offset->offset_G & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_226_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_227_bx);

	gadc_dig_228_bx.b_pre_offset_1 = (offset->offset_B >> 8) & 0x1F;
	gadc_dig_229_bx.b_pre_offset_0 = offset->offset_B & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_228_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_229_bx);


	return 0;
}


int ADC_L9Bx_GetSumRGB(S_RGB_SUM *sum)
{
	UINT32 out32 = 0;

	sum->sum_R = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_166_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_167_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_168_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_169_bx);
	out32 =  gadc_dig_166_bx.ap_sum_r_3;
	sum->sum_R |= out32 << 24;
	out32 =  gadc_dig_167_bx.ap_sum_r_2;
	sum->sum_R |= out32 << 16;
	out32 =  gadc_dig_168_bx.ap_sum_r_1;
	sum->sum_R |= out32 << 8;
	out32 =  gadc_dig_169_bx.ap_sum_r_0;
	sum->sum_R |= out32;

	out32 = 0;
	sum->sum_G = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_162_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_163_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_164_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_165_bx);
	out32 =  gadc_dig_162_bx.ap_sum_g_3;
	sum->sum_G |= out32 << 24;
	out32 =  gadc_dig_163_bx.ap_sum_g_2;
	sum->sum_G |= out32 << 16;
	out32 =  gadc_dig_164_bx.ap_sum_g_1;
	sum->sum_G |= out32 << 8;
	out32 =  gadc_dig_165_bx.ap_sum_g_0;
	sum->sum_G |= out32;

	out32 = 0;
	sum->sum_B = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_158_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_159_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_160_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_161_bx);
	out32 =  gadc_dig_158_bx.ap_sum_b_3;
	sum->sum_B |= out32 << 24;
	out32 =  gadc_dig_159_bx.ap_sum_b_2;
	sum->sum_B |= out32 << 16;
	out32 =  gadc_dig_160_bx.ap_sum_b_1;
	sum->sum_B |= out32 << 8;
	out32 =  gadc_dig_161_bx.ap_sum_b_0;
	sum->sum_B |= out32;

	return 0;
}

/**
 *
 * Enable SCART RGB input on component 2(from B0 revision board) port for EU model
 *
 * @param	BOOLEAN scart_enable(TRUE:Enable SCART RGB, FALSE:component mode)
 *
*/
int ADC_L9Bx_Enable_Scart_Mode(BOOLEAN scart_enable)
{
//	UINT32	VP2_Intr_Enable_Mask = 0xFFFFFBFC; // Disable Resolution change & SOY1 detection interrupt.
//	static UINT32 	VP2_Intr_Enable_Save = 0;

	ADC_DEBUG("%s entered with value [%d]\n", __func__, scart_enable);

	if (scart_enable == TRUE)
	{
		//Interrupt Disable for component1
#if 0
		VP2_Intr_Enable_Save = gVportRegBx->intr_vp2_enable.intr_vp2_enable;
		gVportRegBx->intr_vp2_enable.intr_vp2_enable = VP2_Intr_Enable_Save & VP2_Intr_Enable_Mask;
#endif
		VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
		//gafe_3ch_0_bx.afe3ch_selmux = 0x1;
		gafe_3ch_0_bx.afe3ch_selmux = 0x0;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	//	gVportRegBx->ch3_adc_003.afe3ch_sel_ck = 0x1; // select clock from CVD

		//120128 wonsik.do : ADC_SetType is also called in KADP_AFE_Set_Source_Type(ADC_SetInputFormat)
//		ADC_SetType(LX_ADC_INPUT_SOURCE_RGB_SCART); // for SCART RGB set port type to RGB
	}
	else
	{
		// No need to set interrupt enable for the scart input.
#if 0
		if(VP2_Intr_Enable_Save)
			gVportRegBx->intr_vp2_enable.intr_vp2_enable = VP2_Intr_Enable_Save;
#endif

		// Port selection should be called from DDI
		//gVportRegBx->ch3_adc_004.afe3ch_selmux = 0x0; // select component 1 port for ADC
		VPORT_I2C_Read((UINT32*)&gafe_3ch_3_bx);
		gafe_3ch_3_bx.afe3ch_sel_ck = 0;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_3_bx);
	}
	return 0;
}

void ADC_L9Bx_Vport_ALL_Power_Down(void)
{
	/* AFE3CH Power Down Setting */
	//gVportRegBx->cvbsafe_pdb_001.afe3ch_biaspdb = 0x0;
//	gVportRegBx->cvbsafe_pdb_001.afe3ch_biaspdb = 0;

	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_bpdb = 0;
	gafe_3ch_0_bx.afe3ch_gpdb = 0;
	gafe_3ch_0_bx.afe3ch_rpdb = 0;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	/* LLPLL PDB */
	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.llpll_pdb = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	/* LLPLL/CST SWRST & 3CH_DIG SWRST */
	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_pix = 1;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
}

int ADC_L9Bx_Channel_Power_Control(int vref_pdb, int bpdb, int gpdb, int rpdb)
{
//	AFE_PRINT("ADC Channel Power Control vfref_pdb[%d], bpdb[%d], gpdb[%d], rpdb[%d]\n", vref_pdb, bpdb, gpdb, rpdb);

	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	if(bpdb >= 0)
	{
		gafe_3ch_0_bx.afe3ch_bpdb = bpdb;
	}
	if(gpdb >= 0)
	{
		gafe_3ch_0_bx.afe3ch_gpdb = gpdb;
	}
	if(rpdb >= 0)
	{
		gafe_3ch_0_bx.afe3ch_rpdb = rpdb;
	}
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	return 0;
}

int ADC_L9Bx_SetType(LX_AFE_ADC_INPUT_SOURCE_TYPE_T sel_type)
{
	S_BLANK_INFORM blank_value;
	//AFE_PRINT("ADC_SetType \n");
#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
	S_OFFSET_INFORM offset;
#endif
	gADC_type = sel_type;

	if(sel_type == LX_ADC_INPUT_SOURCE_YPBPR)
	{
		ADC_DEBUG("Component Input Mode\n");
		VPORT_I2C_Read((UINT32*)&gafe_3ch_6_bx);
		gafe_3ch_6_bx.afe3ch_sog_outmux = 0;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_6_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_3_bx);
		VPORT_I2C_Read((UINT32*)&gafe_3ch_4_bx);
		gafe_3ch_3_bx.afe3ch_clpcur = 0x1;
		gafe_3ch_3_bx.afe3ch_rvclpsel = 1;
		gafe_3ch_3_bx.afe3ch_gvclpsel = 0;
		gafe_3ch_4_bx.afe3ch_bvclpsel = 1;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_3_bx);
		VPORT_I2C_Write((UINT32*)&gafe_3ch_4_bx);

		ADC_L9Bx_Set_Sync_Mode(ADC_COMPOSITE_SYNC_MODE);
		/*
		VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
		gadc_dig_22_bx.compover = 0x1;
		gadc_dig_22_bx.compuser = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
		*/

		blank_value.r_blank_target_value = 0x400;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.g_blank_target_value = 0x200;
		blank_value.g_blank_target_value = 0x240;
		blank_value.b_blank_target_value = 0x400;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.width = 0x4;
		blank_value.width = 0x1;
		blank_value.r_shift_value = 0x0;
		blank_value.g_shift_value = 0x0;
		blank_value.b_shift_value = 0x0;

		ADC_L9Bx_Set_Blank_Value(&blank_value);

		//added 0716
		VPORT_I2C_Read((UINT32*)&gadc_dig_58_bx);
		gadc_dig_58_bx.hsout_width_sel = 0x1;		// Set to Manual mode '1'  ( For L8 '0' is manual mode )
		VPORT_I2C_Write((UINT32*)&gadc_dig_58_bx);

		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block

		//0906
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x0;	// RGB shaking problem => H positon shift problem
		//1210 powerory
		//110928 by dws: if set to '0' with vsprdeq_thr value '0x2', 1080P 60Hz screen sometimes roll-down slowly.
		VPORT_I2C_Read((UINT32*)&gadc_dig_61_bx);
		//gadc_dig_61_bx.vsout_sel = 0x0;
		//111101 by wonsik.do : use vsync bypass mode to fix picture rolling up/down problem.
		gadc_dig_61_bx.vsout_sel = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_61_bx);

		//If vsout_sel is 0(vs_gen), sometimes vertical sync is not lock to video. Need more debuggint.
		//1214 powerory
		gadc_dig_62_bx.vsdiff_thr_2 = 0x0;
		gadc_dig_63_bx.vsdiff_thr_1 = 0x0;
		gadc_dig_64_bx.vsdiff_thr_0 = 0x80;
		VPORT_I2C_Write((UINT32*)&gadc_dig_62_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_63_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_64_bx);

		//gadc_dig_65_bx.vsprdeq_thr = 0x0E;
		// reduced vsprdeq_thr value for fast locking on 24/25/30Hz signals.(110712)
		//gadc_dig_65_bx.vsprdeq_thr = 0x02;
		//110928 by dws : better increase vsprdeq_thr value to '5', to use vsync locked mode (vsout_sel '0')
		//111101 by dws : increased vsprdeq_thr value to '7' from '5' (720P 50Hz sometimes roll-down )
		gadc_dig_65_bx.vsprdeq_thr = 0x07;
		VPORT_I2C_Write((UINT32*)&gadc_dig_65_bx);

		//20110114
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;
//		gVportRegBx->ch3_digital_003.ch3reg_hsoutover = 0;

		/*
		//20110124 powerory (480i 입력에서 문제점해결위해 수정)
		gadc_dig_52_bx.hsdiff_thr_1 = 0x0;
		gadc_dig_53_bx.hsdiff_thr_0 = 0x0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_52_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_53_bx);
		*/

		//20110125
		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block
		VPORT_I2C_Read((UINT32*)&gadc_dig_88_bx);
		gadc_dig_88_bx.hsync_sel = 0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_88_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_7_bx);
		//gafe_3ch_7_bx.afe3ch_ctl_add	= 0x93;
		gafe_3ch_7_bx.afe3ch_ctl_add	= 0x13;	 //by gogosing 111026 : shibasoku sync unstable problem.
		VPORT_I2C_Write((UINT32*)&gafe_3ch_7_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_5_bx);
		VPORT_I2C_Read((UINT32*)&gafe_3ch_6_bx);

		//New Value for L9B0 by Min 110915
		gafe_3ch_5_bx.afe3ch_soglvl = 0x6;
		gafe_3ch_5_bx.afe3ch_sog_hys = 0x1;
		gafe_3ch_6_bx.afe3ch_sog_bw = 0x3;
		//gafe_3ch_6_bx.afe3ch_sog_inbw = 0x3;			// select data clock
		// 111109 fix component shaking on shibasoku.
		gafe_3ch_6_bx.afe3ch_sog_inbw = 0x1;	//0x3	// select llpll clock

		VPORT_I2C_Write((UINT32*)&gafe_3ch_5_bx);
		VPORT_I2C_Write((UINT32*)&gafe_3ch_6_bx);

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
		offset.offset_R	= ADC_L9_R_PRE_OFFSET_VALUE;
		offset.offset_G	= ADC_L9_G_PRE_OFFSET_VALUE;
		offset.offset_B	= ADC_L9_B_PRE_OFFSET_VALUE;

		ADC_L9Bx_SetOffsetRGB(&offset);
#endif
	}
	else if(sel_type == LX_ADC_INPUT_SOURCE_RGB_SCART)
	{
		ADC_DEBUG("SCART RGB Input Mode\n");
		VPORT_I2C_Read((UINT32*)&gafe_3ch_6_bx);
		gafe_3ch_6_bx.afe3ch_sog_outmux = 0;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_6_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_3_bx);
		VPORT_I2C_Read((UINT32*)&gafe_3ch_4_bx);
		gafe_3ch_3_bx.afe3ch_clpcur = 0x3;
		gafe_3ch_3_bx.afe3ch_rvclpsel = 0;
		gafe_3ch_3_bx.afe3ch_gvclpsel = 0;
		gafe_3ch_4_bx.afe3ch_bvclpsel = 0;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_3_bx);
		VPORT_I2C_Write((UINT32*)&gafe_3ch_4_bx);

		ADC_L9Bx_Set_Sync_Mode(ADC_COMPOSITE_SYNC_MODE);
		/*
		VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
		gadc_dig_22_bx.compover = 0x1;
		gadc_dig_22_bx.compuser = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
		*/

		blank_value.r_blank_target_value = 0x200;
		blank_value.g_blank_target_value = 0x200;
		blank_value.b_blank_target_value = 0x200;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.width = 0x4;
		blank_value.width = 0x1;
		blank_value.r_shift_value = 0x0;
		blank_value.g_shift_value = 0x0;
		blank_value.b_shift_value = 0x0;
		ADC_L9Bx_Set_Blank_Value(&blank_value);

		//added 0716
		VPORT_I2C_Read((UINT32*)&gadc_dig_58_bx);
		gadc_dig_58_bx.hsout_width_sel = 0x1;		// Set to Manual mode '1'  ( For L8 '0' is manual mode )
		VPORT_I2C_Write((UINT32*)&gadc_dig_58_bx);

		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block

		//0906
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x0;	// RGB shaking problem => H positon shift problem
		//1210 powerory
		VPORT_I2C_Read((UINT32*)&gadc_dig_61_bx);
		gadc_dig_61_bx.vsout_sel = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_61_bx);

		//If vsout_sel is 0(vs_gen), sometimes vertical sync is not lock to video. Need more debuggint.
		//1214 powerory
		gadc_dig_62_bx.vsdiff_thr_2 = 0x0;
		gadc_dig_63_bx.vsdiff_thr_1 = 0x0;
		gadc_dig_64_bx.vsdiff_thr_0 = 0x80;
		VPORT_I2C_Write((UINT32*)&gadc_dig_62_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_63_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_64_bx);

		//gadc_dig_65_bx.vsprdeq_thr = 0x0E;
		// reduced vsprdeq_thr value for fast locking on 24/25/30Hz signals.(110712)
		/*
		gadc_dig_65_bx.vsprdeq_thr = 0x0F;
		VPORT_I2C_Write((UINT32*)&gadc_dig_65_bx);
		*/

		//20110114
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;
//		gVportRegBx->ch3_digital_003.ch3reg_hsoutover = 0;

		/*
		//20110124 powerory (480i 입력에서 문제점해결위해 수정)
		gadc_dig_52_bx.hsdiff_thr_1 = 0x0;
		gadc_dig_53_bx.hsdiff_thr_0 = 0x0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_52_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_53_bx);
		*/

		//20110125
		//gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // Select feedback LLPLL Hsync for digital block
		VPORT_I2C_Read((UINT32*)&gadc_dig_88_bx);
		gadc_dig_88_bx.hsync_sel = 0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_88_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_7_bx);
		//gafe_3ch_7_bx.afe3ch_ctl_add	= 0x96;		// For SCART RGB set SOG BW to 2.5M => 1 line on/off pattern benting
		//gafe_3ch_7_bx.afe3ch_ctl_add	= 0x94;		// 111220 by bh.min => unstable!!!
		//gafe_3ch_7_bx.afe3ch_ctl_add	= 0x95;		// 111221 : need more test
		//gafe_3ch_7_bx.afe3ch_ctl_add	= 0x96;		// 120104 : for PM5518 noisy CVBS
		gafe_3ch_7_bx.afe3ch_ctl_add	= 0x16;		// 120116 : for Clamp operation on LLPLL status '1'
		VPORT_I2C_Write((UINT32*)&gafe_3ch_7_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_5_bx);
		VPORT_I2C_Read((UINT32*)&gafe_3ch_6_bx);

		//New Value for L9B0 by Min 110915
		//gafe_3ch_5_bx.afe3ch_soglvl = 0x6;
		//120104 : New Value for L9B0 SCART RGB test
		gafe_3ch_5_bx.afe3ch_soglvl = 0x4;
		gafe_3ch_5_bx.afe3ch_sog_hys = 0x1;
		gafe_3ch_6_bx.afe3ch_sog_bw = 0x3;
		// 110919 fix SCART RGB shaking problem
		gafe_3ch_6_bx.afe3ch_sog_inbw = 0x1;	//0x3

		VPORT_I2C_Write((UINT32*)&gafe_3ch_5_bx);
		VPORT_I2C_Write((UINT32*)&gafe_3ch_6_bx);

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
		offset.offset_R	= ADC_L9_R_PRE_OFFSET_VALUE + SCART_RGB_OFFSET_ADD;
		offset.offset_G	= ADC_L9_G_PRE_OFFSET_VALUE + SCART_RGB_OFFSET_ADD;
		offset.offset_B	= ADC_L9_B_PRE_OFFSET_VALUE + SCART_RGB_OFFSET_ADD;

		ADC_L9Bx_SetOffsetRGB(&offset);
#endif
	}
	else
	{
		ADC_DEBUG("RGB Input Mode\n");
		VPORT_I2C_Read((UINT32*)&gafe_3ch_6_bx);
		gafe_3ch_6_bx.afe3ch_sog_outmux = 1;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_6_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_3_bx);
		VPORT_I2C_Read((UINT32*)&gafe_3ch_4_bx);
		gafe_3ch_3_bx.afe3ch_clpcur = 0x1;
		gafe_3ch_3_bx.afe3ch_rvclpsel = 0;
		gafe_3ch_3_bx.afe3ch_gvclpsel = 0;
		gafe_3ch_4_bx.afe3ch_bvclpsel = 0;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_3_bx);
		VPORT_I2C_Write((UINT32*)&gafe_3ch_4_bx);

		ADC_L9Bx_Set_Sync_Mode(ADC_SEPERATED_SYNC_MODE);
		/*
		VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
		gadc_dig_22_bx.compover = 0x1;
		gadc_dig_22_bx.compuser = 0x0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
		*/

		blank_value.r_blank_target_value = 0x200;
		blank_value.g_blank_target_value = 0x200;
		blank_value.b_blank_target_value = 0x200;
		// by powerory 11.07.29 for valid pixel value read
		//blank_value.width = 0x4;
		blank_value.width = 0x1;
		blank_value.r_shift_value = 0x0;
		blank_value.g_shift_value = 0x0;
		blank_value.b_shift_value = 0x0;
		ADC_L9Bx_Set_Blank_Value(&blank_value);

		//added 0716
		//gVportRegBx->ch3_digital_004.ch3reg_hsout_width_sel = 0x1; // Select Auto Hsync output sync width

		// for horizontal sync re-shape in ADC

		//TEMP for L9B0 Bring-UP	: 110832 by dws
		// if hsout width is set to '2', output image collapses.
		VPORT_I2C_Read((UINT32*)&gadc_dig_58_bx);
		gadc_dig_58_bx.hsout_width_sel = 0x1;
		//gadc_dig_58_bx.hsout_width_sel = 0x0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_58_bx);

//		gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x0; // Select internal Hsync for digital block
//		gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // powerory  <== CAN NOT CHANGE HSIZE BY 1 STEP
//		gVportRegBx->ch3_digital_005.ch3reg_hsync_sel = 0x1; // B0 Revision Fixed bug(HSIZE 1 STEP)

		//0906
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;	// RGB shaking problem => H positon shift problem
		//1210 powerory
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x0;
		VPORT_I2C_Read((UINT32*)&gadc_dig_61_bx);
		gadc_dig_61_bx.vsout_sel = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_61_bx);

		/*
		//20110114
		//gVportRegBx->ch3_digital_063.ch3reg_hsdiff_thr = 0x2;
		gadc_dig_52_bx.hsdiff_thr_1 = 0x0;
		gadc_dig_53_bx.hsdiff_thr_0 = 0x0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_52_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_53_bx);
		*/

//		gVportRegBx->ch3_digital_003.ch3reg_hsoutover = 1;
//		gVportRegBx->ch3_digital_003.ch3reg_hsoutcnt = gVportRegBx->ch3_llpll_003.llpll_counter_max - 1;
		//20110125
		VPORT_I2C_Read((UINT32*)&gadc_dig_88_bx);
		gadc_dig_88_bx.hsync_sel = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_88_bx);

		VPORT_I2C_Read((UINT32*)&gafe_3ch_7_bx);
		gafe_3ch_7_bx.afe3ch_ctl_add	= 0x93;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_7_bx);

		//110921 : Is sog_inbw setting needed on RGB mode ???
		VPORT_I2C_Read((UINT32*)&gafe_3ch_6_bx);
		gafe_3ch_6_bx.afe3ch_sog_inbw = 0x3;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_6_bx);

#ifdef	SUPPORT_SCART_RGB_ULTRA_BLACK
		offset.offset_R	= ADC_L9_R_PRE_OFFSET_VALUE;
		offset.offset_G	= ADC_L9_G_PRE_OFFSET_VALUE;
		offset.offset_B	= ADC_L9_B_PRE_OFFSET_VALUE;

		ADC_L9Bx_SetOffsetRGB(&offset);
#endif
	}

	return 0;
}

int ADC_L9Bx_Set_LLPLL(UINT32 arg)
{

	if(arg >= PARAM_NUM)
		return -1;

		AFE_PRINT("Setting LLPLL to Index Number [%d]\n", arg);

	//ADC_SetInputVideo(arg);

	if(ADC_SetInputVideo(arg) == 0)
		gPrevious_index = 0xffff;

	return 0;

}

int ADC_L9Bx_SetClock(int iIndex, SINT16 value)
{
	UINT16 clock_value;
#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	UINT8 dco_max_value, dco_min_value;
#endif
	//	AFE_PRINT("%s entered\n", __func__);
	//LLPLL_counter_max
	clock_value = LLPLL_counter_max[iIndex];

	//	AFE_PRINT("Clock Value =[%d +(%d)], \n", clock_value, value);

	// No Need to Write Same Value
	/*
	   if(gVportRegBx->ch3_llpll_003.llpll_counter_max == (clock_value + value))
	   return 0;
	 */

#ifdef	KDRV_CONFIG_PM
	gAdcPMData->giPmClockValue = value;
#endif
	clock_value += value;
	//ADC_Ext_Clamp(1);

	VPORT_I2C_Read((UINT32*)&gllpll_2_bx);
	VPORT_I2C_Read((UINT32*)&gllpll_3_bx);
	gllpll_2_bx.llpll_counter_max_1 = (clock_value&0xF00)>>8;
	gllpll_3_bx.llpll_counter_max_0 = clock_value&0xFF;
	VPORT_I2C_Write((UINT32*)&gllpll_2_bx);
	VPORT_I2C_Write((UINT32*)&gllpll_3_bx);

	//by dws : remove mdelay
	//mdelay(10);
	OS_MsecSleep(5);

#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	ADC_L9Bx_Get_DCO_MinMax_Value(&dco_min_value, &dco_max_value);
	ADC_L9Bx_Set_DCO_MinMax_Value(0, 0);
#endif

	//by dws : remove mdelay
	//mdelay(10);
	OS_MsecSleep(5);

#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	ADC_L9Bx_Set_DCO_MinMax_Value(dco_min_value, dco_max_value);
#endif
	OS_MsecSleep(30);

#ifdef L9_RGB_WA_FOR_CLOCK_ADJUST
	// for MSPG 68 timing (1152*720) : sometimes LLPLL unlock occur durring size adjust
	ADC_L9Bx_Check_LLPLL_status();
#endif

	return 0;
}

int ADC_L9Bx_Reset_Digital(void)
{
	ADC_DEBUG("%s entered\n", __func__);

#ifdef L8_RGB_FEEDBACK_HSYNC_WORKAROUND
	ADC_Channel_Power_Control(-1, 0, -1, 0);
#endif

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_pix = 1;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);

	//by dws : remove mdelay
//	mdelay(5);
	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_pix = 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);

#ifdef L8_RGB_FEEDBACK_HSYNC_WORKAROUND
	ADC_Channel_Power_Control(-1, 1, -1, 1);
#endif

	return 0;
}


int ADC_L9Bx_Reset_Digital_24MHZ(void)
{
	ADC_DEBUG("%s entered\n", __func__);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_f24m = 1;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);

	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
	gsoft_reset_0_bx.swrst_f24m = 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);

	return 0;
}


int ADC_L9Bx_Reset_Digital_Control(int enable_reset)
{
	ADC_DEBUG("%s entered [%d]\n", __func__, enable_reset);

	if(enable_reset)
	{
		VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
		gsoft_reset_0_bx.swrst_pix = 1;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&gsoft_reset_0_bx);
		gsoft_reset_0_bx.swrst_pix = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_0_bx);
	}

	return 0;
}

int ADC_L9Bx_Reset_LLPLL(void)
{
	ADC_DEBUG("%s entered\n", __func__);

	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	//by dws : remove mdelay
	//mdelay(5);
	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 1;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	return 0;
}

int ADC_L9Bx_Reset_LLPLL_Control(int enable_reset)
{
	ADC_DEBUG("%s entered [%d]\n", __func__, enable_reset);

	if(enable_reset)
	{
		VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
		gllpll_0_bx.reset_n = 0;
		VPORT_I2C_Write((UINT32*)&gllpll_0_bx);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
		gllpll_0_bx.reset_n = 1;
		VPORT_I2C_Write((UINT32*)&gllpll_0_bx);
	}

	return 0;
}

int ADC_L9Bx_Sync_Polarity_Override(int set)
{
	ADC_DEBUG("%s entered\n", __func__);
	if(set)
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_21_bx);
		gadc_dig_21_bx.hspolover = 0x1;
		gadc_dig_21_bx.vspolover = 0x1;
		gadc_dig_21_bx.hspoluser = 0x1;
		gadc_dig_21_bx.vspoluser = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_21_bx);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_21_bx);
		gadc_dig_21_bx.hspolover = 0;
		gadc_dig_21_bx.vspolover = 0;
//		gadc_dig_21_bx.hspoluser = 0;
//		gadc_dig_21_bx.vspoluser = 0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_21_bx);
	}

	return 0;
}



int ADC_L9Bx_Check_Sync_Exist(void)
{

	UINT8	vsdet_value, hsdet_value;

	VPORT_I2C_Read((UINT32*)&gadc_dig_28_bx);

	hsdet_value = gadc_dig_28_bx.ro_hsdet;
	vsdet_value = gadc_dig_28_bx.ro_vsdet;

	if ( ( ( gADC_type == LX_ADC_INPUT_SOURCE_RGB_PC) && (hsdet_value == 1) /*&& (vsdet_value == 1)*/ ) || ( ( gADC_type != LX_ADC_INPUT_SOURCE_RGB_PC) && (hsdet_value == 1) ) )
		return 0;
#if 0
	UINT8	no_signal;

	VPORT_I2C_Read((UINT32*)&gadc_dig_121_bx);

	no_signal = gadc_dig_121_bx.no_signal;

	if(no_signal < 1) // signal exist
		return 0;
#endif

	return -1;

}

int ADC_L9Bx_Enable_Detection_Interrupt(int enable)
{
	ADC_DEBUG("%s entered\n", __func__);

	return 0;
}

int ADC_L9Bx_Enable_AOGC_Interrupt(int enable)
{
	ADC_DEBUG("%s entered\n", __func__);
	return 0;
}

int ADC_L9Bx_Mute_Enable(int enable)
{
	ADC_DEBUG("%s entered [%d]\n", __func__, enable);
	if(enable)
	{
		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
			VPORT_I2C_Read((UINT32*)&gadc_dig_89_bx);
			gadc_dig_89_bx.signedout = 5;
			VPORT_I2C_Write((UINT32*)&gadc_dig_89_bx);
		}
		VPORT_I2C_Read((UINT32*)&gafe_3ch_1_bx);
		gafe_3ch_1_bx.adc_ire_test = 0x1;
		VPORT_I2C_Write((UINT32*)&gafe_3ch_1_bx);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_89_bx);
		VPORT_I2C_Read((UINT32*)&gafe_3ch_1_bx);
		gadc_dig_89_bx.signedout = 0;
		gafe_3ch_1_bx.adc_ire_test = 0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_89_bx);
		VPORT_I2C_Write((UINT32*)&gafe_3ch_1_bx);
	}

	return 0;
}

int ADC_L9Bx_Power_OnOff(void)
{
	ADC_DEBUG("%s entered\n", __func__);

	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_biaspdb = 0;
	gafe_3ch_0_bx.afe3ch_bpdb = 0;
	gafe_3ch_0_bx.afe3ch_gpdb = 0;
	gafe_3ch_0_bx.afe3ch_rpdb = 0;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	//gVportRegBx->ch3_digital_002.ch3reg_extclampsel = 1;
	//gVportRegBx->ch3_digital_002.ch3reg_clamppolover = 1;
	//gVportRegBx->ch3_digital_002.ch3reg_clamppoluser = 1;


	//by dws : remove mdelay
	//mdelay(5);
	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gafe_3ch_0_bx);
	gafe_3ch_0_bx.afe3ch_biaspdb = 1;
	gafe_3ch_0_bx.afe3ch_bpdb = 1;
	gafe_3ch_0_bx.afe3ch_gpdb = 1;
	gafe_3ch_0_bx.afe3ch_rpdb = 1;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_0_bx);

	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 0;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	//by dws : remove mdelay
	//mdelay(5);
	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gllpll_0_bx);
	gllpll_0_bx.reset_n = 1;
	VPORT_I2C_Write((UINT32*)&gllpll_0_bx);

	return 0;
}

int ADC_L9Bx_Ext_Clamp(int sel_ext)
{
//	static int g_ph_value = 4;

	ADC_DEBUG("%s entered [%d]\n", __func__, sel_ext);
	if(sel_ext)
	{
		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
//			ADC_Channel_Power_Control(0);
	//		gVportRegBx->top_008.reg_swrst_llpll = 0x1;
//			gVportRegBx->top_008.reg_swrst_ch3pix = 0x1;
			/*
			VPORT_RdFL(ch3_adc_005);
			VPORT_Wr01(ch3_adc_005, afe3ch_g_ph, 1);
			VPORT_WrFL(ch3_adc_005);
			AFE_PRINT("Set g_ph value to 0 \n");
			*/
		}

//		mdelay(10);

		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
//			mdelay(5);
//			ADC_Channel_Power_Control(1);
//			mdelay(5);
		}
		// powerory
		//gVportRegBx->ch3_digital_002.ch3reg_extclampsel = 1;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppolover = 1;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppoluser = 1;
		//~powerory
#if 0
		if(gADC_type != LX_ADC_INPUT_SOURCE_YPBPR)	// 1019 Workaround for CVI Vsync Unstable on component input(VENICE 1080i)
			gVportRegBx->top_008.reg_swrst_ch3pix = 0x1;
		//mdelay(1000);
#endif
	}
	else
	{
		// powerory
		//gVportRegBx->ch3_digital_002.ch3reg_extclampsel = 0;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppolover = 0;
		//gVportRegBx->ch3_digital_002.ch3reg_clamppoluser = 0;
		//~powerory
		if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
		{
//			mdelay(5);
	//		gVportRegBx->top_008.reg_swrst_llpll = 0x0;
//			mdelay(300);
//			gVportRegBx->top_008.reg_swrst_ch3pix = 0x0;
			/*
			VPORT_RdFL(ch3_adc_005);
			VPORT_Wr01(ch3_adc_005, afe3ch_g_ph, g_ph_value);
			VPORT_WrFL(ch3_adc_005);
			AFE_PRINT("Restore g_ph value to [%d]\n",g_ph_value);
			*/
		}
		//mdelay(30);
	}

	return 0;
}

int ADC_L9Bx_Set_Clamp(UINT8 clamp_base, UINT8 clamp_place, UINT8 clamp_width)
{
	if(clamp_base)
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_50_bx);
		gadc_dig_50_bx.clamp_base = clamp_base & 0x3;
		VPORT_I2C_Write((UINT32*)&gadc_dig_50_bx);
	}

	if(clamp_place)
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_51_bx);
		gadc_dig_51_bx.clamp_place = clamp_place;
		VPORT_I2C_Write((UINT32*)&gadc_dig_51_bx);
	}

	if(clamp_width)
	{
		VPORT_I2C_Read((UINT32*)&gadc_dig_220_bx);
		gadc_dig_220_bx.clamp_width = clamp_width;
		VPORT_I2C_Write((UINT32*)&gadc_dig_220_bx);
	}

	return 0;
}

#ifdef	KDRV_CONFIG_PM
int ADC_L9Bx_RunSuspend(void)
{
	// confirm initialization done
	if(gVportRegBx == NULL)
		return -1;

	// TAU inform
	gAdcPMData->gstPmExtauValue.height_offset = gVportRegBx->ch3_digital_026.ch3reg_extau_down_offset;
	gAdcPMData->gstPmExtauValue.width_offset = gVportRegBx->ch3_digital_028.ch3reg_extau_right_offset;
	gAdcPMData->gstPmExtauValue.width_offset = gVportRegBx->ch3_digital_023.ch3reg_extau_ctrl;

	//
	ADC_GetRGBPosition(&gAdcPMData->gstPmPositionValue);
	// phase
	gAdcPMData->guiPmPhaseValue = ADC_GetPhaseValue();

	ADC_GetGainValue(&gAdcPMData->gstPmGainValue);

	ADC_GetOffsetValue(&gAdcPMData->gstPmOffsetValue);


	gAdcPMData->guiPmInterruptStatus = gVportRegBx->intr_vp2_enable.intr_vp2_enable;

	ADC_Vport_ALL_Power_Down();

	return 0;
}

int ADC_L9Bx_RunResume(void)
{

	ADC_InitDaughterBoard();

	if(gAdcPMData->gstPmSelPortValue.port == 0xfffffff)
		return 0;

	VPORT_RdFL(ch3_digital_026);
	VPORT_Wr01(ch3_digital_026, ch3reg_extau_down_offset, gAdcPMData->gstPmExtauValue.height_offset);
	VPORT_WrFL(ch3_digital_026);

	gVportRegBx->ch3_digital_028.ch3reg_extau_right_offset = gAdcPMData->gstPmExtauValue.width_offset;
	gVportRegBx->ch3_digital_023.ch3reg_extau_ctrl = gAdcPMData->gstPmExtauValue.width_offset;

	gVportRegBx->intr_vp2_enable.intr_vp2_enable = gAdcPMData->guiPmInterruptStatus;

	if(gAdcPMData->giPmIndexValue < 0)
		return 0;

	ADC_SetRGBPosition(&gAdcPMData->gstPmPositionValue);

	ADC_SetPhaseValue(gAdcPMData->guiPmPhaseValue);

	ADC_SetGainValue(&gAdcPMData->gstPmGainValue);

	ADC_SetOffsetValue(&gAdcPMData->gstPmOffsetValue);

	if(gAdcPMData->giPmIndexValue >= 0)
	{
		ADC_SetInputVideo(gAdcPMData->giPmIndexValue);
		ADC_SetClock(gAdcPMData->giPmIndexValue ,gAdcPMData->giPmClockValue);
	}

	return 0;
}
#endif


/**
 *
 * ADC_GetPCmodeInfo : Return current mode index
 *
 * @param	struct work_struct
 * @return	0 : OK , -1 : NOK
 *
*/
int ADC_L9Bx_GetPCModeInfo(LX_AFE_PCMODE_INFO_T *stPCModeInfo)
{
	UINT16	Vline, Vlowline, width16, out16;

	if(gResolution >= 0)
	{
		memset((void *)stPCModeInfo, 0, sizeof(LX_AFE_PCMODE_INFO_T));
		stPCModeInfo->u8_Mode_Idx = gResolution;

		width16 = 0;
		VPORT_I2C_Read((UINT32*)&gadc_dig_75_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_76_bx);
		width16 = (gadc_dig_75_bx.ro_hsout_width_1)&0xF;
		width16 = width16 << 8;
		width16 |= gadc_dig_76_bx.ro_hsout_width_0;
		stPCModeInfo->u16_HSyncWidth = width16;

		out16 = 0;
		Vline = 0;
		VPORT_I2C_Read((UINT32*)&gadc_dig_34_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_35_bx);
		out16 =  (gadc_dig_34_bx.ro_vsprdref_1)&0x1F;
		Vline |= out16 << 8;
		out16 =  gadc_dig_35_bx.ro_vsprdref_0;
		Vline |= out16;

		out16 = 0;
		Vlowline = 0;
		VPORT_I2C_Read((UINT32*)&gadc_dig_36_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_37_bx);
		out16 =  (gadc_dig_36_bx.ro_vslowref_1)&0x1F;
		Vlowline |= out16 << 8;
		out16 =  gadc_dig_37_bx.ro_vslowref_0;
		Vlowline |= out16;

		stPCModeInfo->u8_UI_Phase = ADC_Phase_Convert_to_UI_Value(ADC_GetPhaseValue(), gResolution);
		if(Vlowline > (Vline>>1))
		{
			// Active High VSync Pulse
			stPCModeInfo->u16_VSyncWidth = Vline - Vlowline;
		}
		else
		{
			stPCModeInfo->u16_VSyncWidth = Vlowline;
		}

		return 0;
	}
	else
	{
		memset((void *)stPCModeInfo, 0, sizeof(LX_AFE_PCMODE_INFO_T));
		stPCModeInfo->u8_Mode_Idx = 0xff;
		return 0;
	}
}

int ADC_L9Bx_Get_LLPLL_Filter_Status(void)
{
	VPORT_I2C_Read((UINT32*)&gllpll_27_bx);

	return gllpll_27_bx.llpll_filter_status;
}

int ADC_L9Bx_Set_Coast(UINT8 precoast, UINT8 postcoast)
{
	VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_23_bx);
	gadc_dig_22_bx.precoast = precoast&0x1F;
	gadc_dig_23_bx.postcoast = postcoast&0x1F;
	VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_23_bx);

	return 0;
}

int ADC_L9Bx_Set_Hsync_Sel(UINT8 select)
{
	VPORT_I2C_Read((UINT32*)&gadc_dig_88_bx);

	if(select > 0)
	{
		// Select feedback LLPLL Hsync for digital block
		gadc_dig_88_bx.hsync_sel = 0x1;
	}
	else
	{
		gadc_dig_88_bx.hsync_sel = 0;
	}

	VPORT_I2C_Write((UINT32*)&gadc_dig_88_bx);

	return 0;
}

int ADC_L9Bx_CVI_Sync_Exist(void)
{
	//FIXME L8B0 bug, Check if L9 has the same problem.
#if 0
	UINT32 hsync_exist, vsync_exist, src_valid;
	CHA_CVI_RdFL(cha_size_status0);
	CHA_CVI_Rd03(cha_size_status0, hsync_signal_detect, hsync_exist, vsync_signal_detect, vsync_exist, source_valid, src_valid);

	AFE_PRINT("hsync = [%d], vsync = [%d], valid = [%d]\n", hsync_exist, vsync_exist, src_valid);

	if(hsync_exist && vsync_exist/* && src_valid*/)
		return 1;
	else
#endif
	return 0;
}

int ADC_L9Bx_Set_SOG_Level(UINT32 level)
{
	if(level > 0x1F)
		return -1;

	VPORT_I2C_Read((UINT32*)&gafe_3ch_5_bx);
	gafe_3ch_5_bx.afe3ch_soglvl = level&0x1F;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_5_bx);

	ADC_DEBUG("Set SOG Level = [0x%x]\n", level);

	return 0;
}

int ADC_L9Bx_Get_SOG_Level(UINT32 *level)
{
	VPORT_I2C_Read((UINT32*)&gafe_3ch_5_bx);
	*level = gafe_3ch_5_bx.afe3ch_soglvl;

	ADC_DEBUG("Get SOG Level = [0x%x]\n", *level);

	return 0;
}

int ADC_L9Bx_Check_Htotal_Diff(UINT8 count, int Kadp_Index)
{
	UINT8 i;
	UINT16 maxCnt16 = 0;
	UINT16 hsoutprd16 = 0;

	static int hsprd_wrong_count = 0;
	static int hsprd_one_count = 0;

	UINT32	phase_value;
	for(i = 0; i < count;i++)
	{
		maxCnt16 = 0;
		hsoutprd16 = 0;

		VPORT_I2C_Read((UINT32*)&gllpll_2_bx);
		VPORT_I2C_Read((UINT32*)&gllpll_3_bx);
		maxCnt16 = (gllpll_2_bx.llpll_counter_max_1)&0xF;
		maxCnt16 = maxCnt16 << 8;
		maxCnt16 |=gllpll_3_bx.llpll_counter_max_0;

		VPORT_I2C_Read((UINT32*)&gadc_dig_81_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_82_bx);
		hsoutprd16 = (gadc_dig_81_bx.ro_hsoutprd_1)&0xF;
		hsoutprd16 = hsoutprd16 << 8;
		hsoutprd16 |= gadc_dig_82_bx.ro_hsoutprd_0;

#ifdef COMP_4X_OVERSAMPLING
#else
		if( (Kadp_Index == 59) || (Kadp_Index == 61))
		{
			//ADC_DEBUG("##### 480i/576i [%d]!!!\n", hsoutprd16);
			hsoutprd16 = hsoutprd16 >> 1;
		}
#endif

		if(abs(maxCnt16 - hsoutprd16) > 0)
		{
			if(hsoutprd16 == 1)
				hsprd_one_count ++;
			else
				hsprd_wrong_count ++;

			if(hsprd_wrong_count >= 5) {
				ADC_Reset_Digital();

				AFE_PRINT("##### Htotal diff [%d] [0x%x][0x%x]!!!\n", i, maxCnt16 , hsoutprd16);
				hsprd_wrong_count = 0;
			}
			if(hsprd_one_count >= 5) {
				phase_value = ADC_L9Bx_GetPhaseValue();
				AFE_PRINT("##### Htotal one [%d] [0x%x][0x%x]!!!\n", i, maxCnt16 , hsoutprd16);
				AFE_PRINT("##### Prev Phase Value [0x%x]\n",  phase_value);

				if(phase_value >= 5)
					phase_value -= 5;
				else
					phase_value += 5;

				AFE_PRINT("##### Modified Phase Value [0x%x]\n",  phase_value);
				ADC_L9Bx_SetPhaseValue(phase_value);

				hsprd_one_count = 0;
			}

			OS_MsecSleep(10);
		}
		else {
			hsprd_wrong_count = 0;
			hsprd_one_count = 0;

			return 0;
		}

	}
	return -1;
}

int ADC_L9Bx_Read_Pixel_Value(LX_AFE_ADC_PIXEL_VALUE_T *pixel_value_t)
{
	int ret = 0;
	S_RGB_SUM sum;

	gadc_dig_138_bx.ap_xpos_r_1 = (pixel_value_t->X_Pos&0x0F00)>>8;
	gadc_dig_139_bx.ap_xpos_r_0 = (pixel_value_t->X_Pos&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_138_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_139_bx);

	gadc_dig_140_bx.ap_xsize_r_1 = (pixel_value_t->X_Size&0x0F00)>>8;
	gadc_dig_141_bx.ap_xsize_r_0 = (pixel_value_t->X_Size&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_140_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_141_bx);

	gadc_dig_142_bx.ap_ypos_r_1 = (pixel_value_t->Y_Pos&0x0F00)>>8;
	gadc_dig_143_bx.ap_ypos_r_0 = (pixel_value_t->Y_Pos&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_142_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_143_bx);

	gadc_dig_144_bx.ap_ysize_r_1 = (pixel_value_t->Y_Size&0x0F00)>>8;
	gadc_dig_145_bx.ap_ysize_r_0 = (pixel_value_t->Y_Size&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_144_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_145_bx);

	gadc_dig_122_bx.ap_xpos_g_1 = (pixel_value_t->X_Pos&0x0F00)>>8;
	gadc_dig_123_bx.ap_xpos_g_0 = (pixel_value_t->X_Pos&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_122_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_123_bx);

	gadc_dig_124_bx.ap_xsize_g_1 = (pixel_value_t->X_Size&0x0F00)>>8;
	gadc_dig_125_bx.ap_xsize_g_0 = (pixel_value_t->X_Size&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_124_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_125_bx);

	gadc_dig_126_bx.ap_ypos_g_1 = (pixel_value_t->Y_Pos&0x0F00)>>8;
	gadc_dig_127_bx.ap_ypos_g_0 = (pixel_value_t->Y_Pos&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_126_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_127_bx);

	gadc_dig_128_bx.ap_ysize_g_1 = (pixel_value_t->Y_Size&0x0F00)>>8;
	gadc_dig_129_bx.ap_ysize_g_0 = (pixel_value_t->Y_Size&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_128_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_129_bx);

	gadc_dig_130_bx.ap_xpos_b_1 = (pixel_value_t->X_Pos&0x0F00)>>8;
	gadc_dig_131_bx.ap_xpos_b_0 = (pixel_value_t->X_Pos&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_130_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_131_bx);

	gadc_dig_132_bx.ap_xsize_b_1 = (pixel_value_t->X_Size&0x0F00)>>8;
	gadc_dig_133_bx.ap_xsize_b_0 = (pixel_value_t->X_Size&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_132_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_133_bx);

	gadc_dig_134_bx.ap_ypos_b_1 = (pixel_value_t->Y_Pos&0x0F00)>>8;
	gadc_dig_135_bx.ap_ypos_b_0 = (pixel_value_t->Y_Pos&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_134_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_135_bx);

	gadc_dig_136_bx.ap_ysize_b_1 = (pixel_value_t->Y_Size&0x0F00)>>8;
	gadc_dig_137_bx.ap_ysize_b_0 = (pixel_value_t->Y_Size&0xFF);
	VPORT_I2C_Write((UINT32*)&gadc_dig_136_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_137_bx);

	OS_MsecSleep(100);

	ADC_L9Bx_GetSumRGB(&sum);

	pixel_value_t->Sum_R_Value = sum.sum_R;
	pixel_value_t->Sum_G_Value = sum.sum_G;
	pixel_value_t->Sum_B_Value = sum.sum_B;

	return ret;
}

int ADC_L9Bx_Green_Mid_Level_Select(UINT8 value)
{
	VPORT_I2C_Read((UINT32*)&gafe_3ch_3_bx);
	gafe_3ch_3_bx.afe3ch_gvclpsel = value & 0x1;
	VPORT_I2C_Write((UINT32*)&gafe_3ch_3_bx);

	return 0;
}

int ADC_L9Bx_Read_VSync_Width(UINT32 *pvs_width)
{
	UINT32 v_line_count, v_low_line_count;
	UINT16 out16 = 0;

	if( gADC_type == LX_ADC_INPUT_SOURCE_RGB_PC)
	{
		out16 = 0;
		v_line_count = 0;
		VPORT_I2C_Read((UINT32*)&gadc_dig_34_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_35_bx);
		out16 =  (gadc_dig_34_bx.ro_vsprdref_1)&0x1F;
		v_line_count |= out16 << 8;
		out16 =  gadc_dig_35_bx.ro_vsprdref_0;
		v_line_count |= out16;

		out16 = 0;
		v_low_line_count = 0;
		VPORT_I2C_Read((UINT32*)&gadc_dig_36_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_37_bx);
		out16 =  (gadc_dig_36_bx.ro_vslowref_1)&0x1F;
		v_low_line_count |= out16 << 8;
		out16 =  gadc_dig_37_bx.ro_vslowref_0;
		v_low_line_count |= out16;

		if((v_line_count /2) > v_low_line_count)	// Active Low VSync
			*pvs_width = v_low_line_count;
		else										// Active High VSync
			*pvs_width = v_line_count - v_low_line_count;
	}
	else		//for component & SCART-RGB
	{
		out16 = 0;
		VPORT_I2C_Read((UINT32*)&gadc_dig_77_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_78_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_79_bx);

		*pvs_width = (gadc_dig_77_bx.ro_vsout_width_2 << 16) | (gadc_dig_78_bx.ro_vsout_width_1 << 8) | gadc_dig_79_bx.ro_vsout_width_0;
	}

	return 0;
}

int ADC_L9Bx_Read_HSync_Width(UINT32 *phs_width)
{
	UINT32 h_line_count, h_low_line_count;
	UINT16 out16 = 0;

	out16 = 0;
	h_line_count = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_30_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_31_bx);
	out16 =  (gadc_dig_30_bx.ro_hsprdref_1)&0x1F;
	h_line_count |= out16 << 8;
	out16 =  gadc_dig_31_bx.ro_hsprdref_0;
	h_line_count |= out16;

	out16 = 0;
	h_low_line_count = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_32_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_33_bx);
	out16 =  (gadc_dig_32_bx.ro_hslowref_1)&0x1F;
	h_low_line_count |= out16 << 8;
	out16 =  gadc_dig_33_bx.ro_hslowref_0;
	h_low_line_count |= out16;

	if((h_line_count /2) > h_low_line_count)	// Active Low VSync
		*phs_width = h_low_line_count;
	else										// Active High VSync
		*phs_width = h_line_count - h_low_line_count;

	return 0;
}


void ADC_L9Bx_LVDS_Control(int enable)
{
/*
	if(enable > 0)
	{
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_0);
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_1);
		ghslvdstx2_0.pdb3 = 0x1;
		ghslvdstx2_1.ch_en3 = 0x3f;
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_0);
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_1);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_0);
		VPORT_I2C_Read((UINT32*)&ghslvdstx2_1);
		ghslvdstx2_0.pdb3 = 0x0;
		ghslvdstx2_1.ch_en3 = 0x0;
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_0);
		VPORT_I2C_Write((UINT32*)&ghslvdstx2_1);
	}
*/
	return;
}


void ADC_L9Bx_Set_Blank(int blank_sp)
{
	if(blank_sp > 0)
	{
		//for MSB 2bit
		gadc_dig_202_bx.blank_sp_1 = (blank_sp>>8) & 0x3;
		VPORT_I2C_Write((UINT32*)&gadc_dig_202_bx);
		//for LSB 8bit
		gadc_dig_203_bx.blank_sp_0 = blank_sp & 0xFF;
		VPORT_I2C_Write((UINT32*)&gadc_dig_203_bx);
	}
	return;
}


int ADC_L9Bx_Set_Blank_Value(S_BLANK_INFORM *blank_value_t)
{
	int r_blank_high_value, r_blank_low_value;
	int g_blank_high_value, g_blank_low_value;
	int b_blank_high_value, b_blank_low_value;

	r_blank_high_value = blank_value_t->r_blank_target_value + blank_value_t->width + blank_value_t->r_shift_value;
	r_blank_low_value = blank_value_t->r_blank_target_value - blank_value_t->width + blank_value_t->r_shift_value;

	g_blank_high_value = blank_value_t->g_blank_target_value + blank_value_t->width + blank_value_t->g_shift_value;
	g_blank_low_value = blank_value_t->g_blank_target_value - blank_value_t->width + blank_value_t->g_shift_value;

	b_blank_high_value = blank_value_t->b_blank_target_value + blank_value_t->width + blank_value_t->b_shift_value;
	b_blank_low_value = blank_value_t->b_blank_target_value - blank_value_t->width + blank_value_t->b_shift_value;

	gadc_dig_205_bx.r_blank_high_1 = (r_blank_high_value >> 8) & 0x7;
	gadc_dig_206_bx.r_blank_high_0 = r_blank_high_value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_205_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_206_bx);

	gadc_dig_210_bx.g_blank_high_1 = (g_blank_high_value >> 8) & 0x7;
	gadc_dig_211_bx.g_blank_high_0 = g_blank_high_value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_210_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_211_bx);

	gadc_dig_216_bx.b_blank_high_1 = (b_blank_high_value >> 8) & 0x7;
	gadc_dig_217_bx.b_blank_high_0 = b_blank_high_value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_216_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_217_bx);

	gadc_dig_207_bx.r_blank_low_1 = (r_blank_low_value >> 8) & 0x7;
	gadc_dig_208_bx.r_blank_low_0 = r_blank_low_value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_207_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_208_bx);

	gadc_dig_212_bx.g_blank_low_1 = (g_blank_low_value >> 8) & 0x7;
	gadc_dig_213_bx.g_blank_low_0 = g_blank_low_value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_212_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_213_bx);

	gadc_dig_218_bx.b_blank_low_1 = (b_blank_low_value >> 8) & 0x7;
	gadc_dig_219_bx.b_blank_low_0 = b_blank_low_value & 0xFF;
	VPORT_I2C_Write((UINT32*)&gadc_dig_218_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_219_bx);


	return 0;
}

int ADC_L9Bx_Set_DCO_MinMax_Value(UINT8 dco_min, UINT8 dco_max)
{
	//LLPLL_dco_max
	VPORT_I2C_Read((UINT32*)&gllpll_7_bx);
	VPORT_I2C_Read((UINT32*)&gllpll_8_bx);

	gllpll_7_bx.llpll_dco_max = dco_max;
	gllpll_8_bx.llpll_dco_min = dco_min;

	VPORT_I2C_Write((UINT32*)&gllpll_7_bx);
	VPORT_I2C_Write((UINT32*)&gllpll_8_bx);

	return 0;
}

int ADC_L9Bx_Get_DCO_MinMax_Value(UINT8 *pdco_min, UINT8 *pdco_max)
{
	//LLPLL_dco_max
	VPORT_I2C_Read((UINT32*)&gllpll_7_bx);
	VPORT_I2C_Read((UINT32*)&gllpll_8_bx);

	*pdco_max = gllpll_7_bx.llpll_dco_max;
	*pdco_min = gllpll_8_bx.llpll_dco_min;

	return 0;
}

/***
  	Release/Enable Reset of HS-LVDS 0/1
	set reset_enable to '0' to release reset
 ***/
int ADC_L9Bx_LVDS_Reset_Control(int reset_enable)
{
	ADC_DEBUG("%s [%d]\n", __func__, reset_enable);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_7_bx);

	if(reset_enable)
	{
		gsoft_reset_7_bx.swrst_hs1_lvds = 0x1;
		gsoft_reset_7_bx.swrst_hs0_lvds = 0x1;
	}
	else
	{
	//	VPORT_I2C_Read((UINT32*)&ghslvdstx0_0_bx);
		VPORT_I2C_Read((UINT32*)&ghslvdstx0_1_bx);
//		VPORT_I2C_Read((UINT32*)&ghslvdstx1_0_bx);
		VPORT_I2C_Read((UINT32*)&ghslvdstx1_1_bx);
		VPORT_I2C_Read((UINT32*)&ghslvdstx1_2_bx);

	//	ghslvdstx0_0_bx.pdb1 = 1;
		ghslvdstx0_1_bx.flip_en1 = 0;
		ghslvdstx0_1_bx.ch_en1 = 0x3f;

	//	ghslvdstx1_0_bx.pdb2 = 1;
		ghslvdstx1_1_bx.flip_en2 = 0;
		ghslvdstx1_1_bx.ch_en2 = 0x3f;
		ghslvdstx1_2_bx.rs2 = 0x3f;
		ghslvdstx1_2_bx.rf2 = 0;

//		VPORT_I2C_Write((UINT32*)&ghslvdstx0_0_bx);
		VPORT_I2C_Write((UINT32*)&ghslvdstx0_1_bx);
//		VPORT_I2C_Write((UINT32*)&ghslvdstx1_0_bx);
		VPORT_I2C_Write((UINT32*)&ghslvdstx1_1_bx);
		VPORT_I2C_Write((UINT32*)&ghslvdstx1_2_bx);

		gsoft_reset_7_bx.swrst_hs1_lvds = 0;
		gsoft_reset_7_bx.swrst_hs0_lvds = 0;
	}

	VPORT_I2C_Write((UINT32*)&gsoft_reset_7_bx);

	return 0;
}

/***
	A-Die HS-LVDS Source Control Function
 ***/
int ADC_L9Bx_LVDS_Src_Control(LX_AFE_LVDS_SRC_CONTROL_T *pLVDS_Control_t)
{
	ADC_DEBUG("%s lvds[%d],power[%d],type[%d],source[%d],mix mode[%d]\n", __func__, pLVDS_Control_t->lvds_sel, pLVDS_Control_t->lvds_power, pLVDS_Control_t->lvds_type, pLVDS_Control_t->lvds_source, pLVDS_Control_t->lvds_mode);

	if(pLVDS_Control_t->lvds_mode != LX_AFE_LVDS_MODE_NO_CHANGE)
	{
		VPORT_I2C_Read((UINT32*)&gdata_bridge_23_bx);
		gdata_bridge_23_bx.reg_scart_mix_mode = pLVDS_Control_t->lvds_mode;
		VPORT_I2C_Write((UINT32*)&gdata_bridge_23_bx);
	}

	if(pLVDS_Control_t->lvds_power != LX_AFE_LVDS_POWER_NO_CHANGE)
	{
		if(pLVDS_Control_t->lvds_sel == LX_AFE_LVDS0_SEL)
		{
			VPORT_I2C_Read((UINT32*)&ghslvdstx0_0_bx);
			ghslvdstx0_0_bx.pdb1 = pLVDS_Control_t->lvds_power;
			VPORT_I2C_Write((UINT32*)&ghslvdstx0_0_bx);
		}
		else
		{
			VPORT_I2C_Read((UINT32*)&ghslvdstx1_0_bx);
			ghslvdstx1_0_bx.pdb2 = pLVDS_Control_t->lvds_power;
			VPORT_I2C_Write((UINT32*)&ghslvdstx1_0_bx);
		}
	}

	if(pLVDS_Control_t->lvds_sel == LX_AFE_LVDS0_SEL)
	{
		VPORT_I2C_Read((UINT32*)&gdata_bridge_21_bx);

		if(pLVDS_Control_t->lvds_type != LX_AFE_LVDS_TYPE_NO_CHANGE)
			gdata_bridge_21_bx.reg_lvds0_type = pLVDS_Control_t->lvds_type;

		if(pLVDS_Control_t->lvds_source != LX_AFE_LVDS_SOURCE_NO_CHANGE)
			gdata_bridge_21_bx.reg_lvds0_src = pLVDS_Control_t->lvds_source;

		VPORT_I2C_Write((UINT32*)&gdata_bridge_21_bx);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&gdata_bridge_22_bx);

		if(pLVDS_Control_t->lvds_type != LX_AFE_LVDS_TYPE_NO_CHANGE)
			gdata_bridge_22_bx.reg_lvds1_type = pLVDS_Control_t->lvds_type;

		if(pLVDS_Control_t->lvds_source != LX_AFE_LVDS_SOURCE_NO_CHANGE)
			gdata_bridge_22_bx.reg_lvds1_src = pLVDS_Control_t->lvds_source;

		VPORT_I2C_Write((UINT32*)&gdata_bridge_22_bx);
	}

	return 0;
}

int ADC_L9Bx_Component_APA(int iIndex)
{

	int iPhaseMax, Phase_Result, Phase_Compare;
	int Prev_Phase_Result = 0xffffffff;
	int repeat = 0;
	int same_count = 0;
	int apa_array[APA_LOOP_COUNT];

	ADC_DEBUG("%s entered \n", __func__);

	if(gADC_type == LX_ADC_INPUT_SOURCE_YPBPR)
	{
#ifdef COMP_4X_OVERSAMPLING
//		if( gADC_APA_Enable == 1)
		if( (gADC_APA_Enable == 1) && (TB_WIDTH[ConvertTable[gResolution]] > 720) )
#else
									// Do not execute APA on 480i/480p inputs
		if( (gADC_APA_Enable == 1) && (TB_WIDTH[ConvertTable[gResolution]] > 720) )
#endif
		{
			OS_MsecSleep(gADC_APA_Delay);
			if(gADC_APA_Enable_Print)
				AFE_PRINT("%s msec sleep[%d] \n", __func__, gADC_APA_Delay);

			for(;repeat < APA_LOOP_COUNT;repeat ++)
			{
				gadc_dig_240_bx.apa_enable = 0;
				VPORT_I2C_Write((UINT32*)&gadc_dig_240_bx);

#ifdef COMP_4X_OVERSAMPLING
	if(iIndex == 303)	// component 480i
		iIndex = 336;	// 4X oversampling
	else if(iIndex == 304)	// component 480p
		iIndex = 337;	// 4X oversampling
	else if(iIndex == 306)
		iIndex = 338;	// 4X oversampling
	else if(iIndex == 307)	// component 480p
		iIndex = 339;	// 4X oversampling
#endif
				//120103 wonsik.do : removed floating point in kernel driver
				iPhaseMax = (1000000000 / (TB_FS[iIndex] * 130) +2); //0918 by powerory
				ADC_L9Bx_Reset_Digital();
				ADC_DEBUG("%s PhaseMax [0x%x] \n",__func__, iPhaseMax);

				//111123 wonsik.do
				gadc_dig_257_bx.apa_sampling_counter_max = 0x3;
				VPORT_I2C_Write((UINT32*)&gadc_dig_257_bx);

				gadc_dig_255_bx.apa_hsfal_offset = 0x81;
				VPORT_I2C_Write((UINT32*)&gadc_dig_257_bx);


				gadc_dig_259_bx.apa_phase_max_0 = iPhaseMax & 0xFF;
				gadc_dig_258_bx.apa_phase_max_1 = (iPhaseMax>>8) & 0x03;
				VPORT_I2C_Write((UINT32*)&gadc_dig_259_bx);
				VPORT_I2C_Write((UINT32*)&gadc_dig_258_bx);

				gadc_dig_298_bx.llpll_shift_sel = 0;
				VPORT_I2C_Write((UINT32*)&gadc_dig_298_bx);

				OS_MsecSleep(30);

				gadc_dig_240_bx.apa_enable = 1;
				VPORT_I2C_Write((UINT32*)&gadc_dig_240_bx);

				OS_MsecSleep(100);

				VPORT_I2C_Read((UINT32*)&gadc_dig_267_bx);
				VPORT_I2C_Read((UINT32*)&gadc_dig_268_bx);

				Phase_Result = (gadc_dig_267_bx.apa_phase1_ro_1<<8)|gadc_dig_268_bx.apa_phase1_ro_0;
				if(gADC_APA_Enable_Print)
					AFE_PRINT("[%d] Phase Result[%d] \n", repeat, Phase_Result);

				if(abs(Phase_Result - Prev_Phase_Result) <= 1)
				{
					if(gADC_APA_Enable_Print)
						AFE_PRINT("Same with Prev Phase value \n");
					same_count ++;
				}
				else
					same_count = 0;

				apa_array[repeat] = Phase_Result;

				Prev_Phase_Result = Phase_Result;

				if(gADC_APA_Enable_Print)
				{
					VPORT_I2C_Read((UINT32*)&gadc_dig_250_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_251_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_265_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_266_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_267_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_268_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_269_bx);
					AFE_PRINT("apa_blank_avg_ro = 	[0x%x]\n", (gadc_dig_250_bx.apa_blank_avg_ro_1<<8)|gadc_dig_251_bx.apa_blank_avg_ro_0);
					AFE_PRINT("apa_phase1_ro =		[0x%x]\n", (gadc_dig_267_bx.apa_phase1_ro_1<<8)|gadc_dig_268_bx.apa_phase1_ro_0);
					AFE_PRINT("apa_data1_ro = 		[0x%x]\n", (gadc_dig_265_bx.apa_data1_ro_1<<8)|gadc_dig_266_bx.apa_data1_ro_0);
					AFE_PRINT("apa_pos1_ro = 		[0x%x]\n", gadc_dig_269_bx.apa_pos1_ro);

					VPORT_I2C_Read((UINT32*)&gadc_dig_272_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_273_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_270_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_271_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_274_bx);
					AFE_PRINT("apa_phase2_ro =		[0x%x]\n", (gadc_dig_272_bx.apa_phase2_ro_1<<8)|gadc_dig_273_bx.apa_phase2_ro_0);
					AFE_PRINT("apa_data2_ro = 		[0x%x]\n", (gadc_dig_270_bx.apa_data2_ro_1<<8)|gadc_dig_271_bx.apa_data2_ro_0);
					AFE_PRINT("apa_pos2_ro = 		[0x%x]\n", gadc_dig_274_bx.apa_pos2_ro);

					VPORT_I2C_Read((UINT32*)&gadc_dig_277_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_278_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_275_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_276_bx);
					VPORT_I2C_Read((UINT32*)&gadc_dig_279_bx);
					AFE_PRINT("apa_phase3_ro =		[0x%x]\n", (gadc_dig_277_bx.apa_phase3_ro_1<<8)|gadc_dig_278_bx.apa_phase3_ro_0);
					AFE_PRINT("apa_data3_ro = 		[0x%x]\n", (gadc_dig_275_bx.apa_data3_ro_1<<8)|gadc_dig_276_bx.apa_data3_ro_0);
					AFE_PRINT("apa_pos3_ro = 		[0x%x]\n", gadc_dig_279_bx.apa_pos3_ro);

				}
				if(same_count >= gADC_APA_Same_Count)
					break;
			}

			if(repeat == APA_LOOP_COUNT)
			{
				Phase_Result = ( apa_array[APA_LOOP_COUNT-1] + apa_array[APA_LOOP_COUNT-2] + apa_array[APA_LOOP_COUNT-3] + apa_array[APA_LOOP_COUNT-4] ) >> 2;
				ADC_DEBUG("Apa value not conversed, use average value [0x%x] <= [0x%x],[0x%x],[0x%x],[0x%x]", Phase_Result, apa_array[APA_LOOP_COUNT-1] , apa_array[APA_LOOP_COUNT-2] , apa_array[APA_LOOP_COUNT-3] , apa_array[APA_LOOP_COUNT-4] );
			}

			VPORT_I2C_Read((UINT32*)&gadc_dig_267_bx);
			VPORT_I2C_Read((UINT32*)&gadc_dig_268_bx);

			Phase_Compare = (gadc_dig_267_bx.apa_phase1_ro_1<<8)|gadc_dig_268_bx.apa_phase1_ro_0;
			if(Phase_Result != Phase_Compare)
				AFE_PRINT("\n ###### Phase Result DIFF [0x%x]!=[0x%x] ######\n", Phase_Compare, Phase_Result);

			gadc_dig_298_bx.llpll_shift_sel = 1;
			VPORT_I2C_Write((UINT32*)&gadc_dig_298_bx);

			// for 1080P 50/60Hz
			//120103 wonsik.do : removed floating point in kernel driver
			if( TB_FS[ConvertTable[gResolution]] > 100000)
			{
				if(Phase_Result >= 2)
					Phase_Result -= 2;
			}
			else
			{
				if(Phase_Result >= iPhaseMax/6)
					Phase_Result -= iPhaseMax/6;
				else
					Phase_Result = iPhaseMax + Phase_Result - iPhaseMax/6;
			}
			if(gADC_APA_Enable_Print)
				AFE_PRINT("Calculated Phase Result =[0x%x] \n", Phase_Result);

			ADC_SetPhaseValue(Phase_Result); // by dws

			gadc_dig_240_bx.apa_enable = 0;
			VPORT_I2C_Write((UINT32*)&gadc_dig_240_bx);

		}
		else
		{
			ADC_DEBUG("%s Do not execute APA \n", __func__);
			gadc_dig_298_bx.llpll_shift_sel = 1;
			VPORT_I2C_Write((UINT32*)&gadc_dig_298_bx);

			ADC_SetPhaseValue((gPCTable+gResolution)->u16_ADC_Phase); // by dws
		}

	}
	else
	{
		gadc_dig_298_bx.llpll_shift_sel = 1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_298_bx);
	}

	return 0;
}

int ADC_L9Bx_Component_APA_Test(UINT32 ADC_APA_Delay, UINT32 ADC_APA_Enable, UINT32 ADC_APA_Same_Count, UINT32 ADC_APA_Execute, UINT32 ADC_APA_Enable_Print)
{
	if(ADC_APA_Execute)
	{
		ADC_APA_Enable = 1;

		ADC_L9Bx_Component_APA(ConvertTable[gResolution]);
	}
	else
	{
		gADC_APA_Delay = ADC_APA_Delay;
		gADC_APA_Enable = ADC_APA_Enable;
		gADC_APA_Same_Count = ADC_APA_Same_Count;
		gADC_APA_Enable_Print = ADC_APA_Enable_Print;
	}
	return 0;
}

int ADC_L9Bx_Get_Vtotal_Value(void)
{
	int out16 = 0;
	int Vline = 0;
	VPORT_I2C_Read((UINT32*)&gadc_dig_34_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_35_bx);
	out16 =  (gadc_dig_34_bx.ro_vsprdref_1)&0x1F;
	Vline |= out16 << 8;
	out16 =  gadc_dig_35_bx.ro_vsprdref_0;
	Vline |= out16;
	return Vline;
}

int ADC_L9Bx_Set_Sync_Mode(ADC_SYNC_MODE sync_mode)
{
	int ret = 0;

	OS_LockMutex(&g_ADC_Sema);

	if(sync_mode == ADC_COMPOSITE_SYNC_MODE)
	{
		ADC_DEBUG("ADC Composite Sync Mode\n");
		VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
		gadc_dig_22_bx.compover = 0x1;
		gadc_dig_22_bx.compuser = 0x1;
		VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);

		g_ADC_Sync_Mode = ADC_COMPOSITE_SYNC_MODE;
	}
	else if (sync_mode == ADC_SEPERATED_SYNC_MODE)
	{
		ADC_DEBUG("ADC Seperated Sync Mode\n");
		VPORT_I2C_Read((UINT32*)&gadc_dig_22_bx);
		gadc_dig_22_bx.compover = 0x1;
		gadc_dig_22_bx.compuser = 0x0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_22_bx);

		g_ADC_Sync_Mode = ADC_SEPERATED_SYNC_MODE;
	}
	else
		ret = -1;

	OS_UnlockMutex(&g_ADC_Sema);

	return ret;
}

int ADC_L9Bx_Mute_Control(ADC_MUTE_CTRL adc_mute_control)
{
	int ret = 0;

	VPORT_I2C_Read((UINT32*)&gadc_dig_230_bx);

	switch(adc_mute_control)
	{
		case ADC_MUTE_CTRL_NORMAL:
			gadc_dig_230_bx.mute_ctrl = 0x0;
			break;

		case ADC_MUTE_CTRL_MUTE:
			gadc_dig_230_bx.mute_ctrl = 0x1;
			break;

		case ADC_MUTE_CTRL_AUTO:
			gadc_dig_230_bx.mute_ctrl = 0x2;
			break;

		default:
				ret = -1;
			break;
	}

	VPORT_I2C_Write((UINT32*)&gadc_dig_230_bx);

	ADC_DEBUG("%s entered with value [%d]\n", __func__, adc_mute_control);

	return ret;
}

int ADC_L9Bx_Set_Ctl_Add(UINT32 sel_fs, UINT32 sinking_current, UINT32 source_current, UINT32 sog_input_filter_bw)
{
	int ret = 0;

	//VPORT_I2C_Read((UINT32*)&gafe_3ch_7_bx);
	gafe_3ch_7_bx.afe3ch_ctl_add	= (sel_fs & 0x1) << 7;
	gafe_3ch_7_bx.afe3ch_ctl_add	|= (sinking_current & 0x3) << 5;
	gafe_3ch_7_bx.afe3ch_ctl_add	|= (source_current & 0x3) << 3;
	gafe_3ch_7_bx.afe3ch_ctl_add	|= (sog_input_filter_bw & 0x7);
	VPORT_I2C_Write((UINT32*)&gafe_3ch_7_bx);

	ADC_DEBUG("%s entered with value [0x%x]\n", __func__, gafe_3ch_7_bx.afe3ch_ctl_add);

	return ret;
}

int ADC_L9Bx_Read_AGOC_State(void)
{

	VPORT_I2C_Read((UINT32*)&gadc_dig_101_bx);
	return gadc_dig_101_bx.ro_aogc_state;

}

// 111123 wonsik.do : for post gain control for 110% white saturation test.
int ADC_L9Bx_Enable_Sync_Low_Level_Read(int enable)
{
	if(enable)
	{
		gadc_dig_257_bx.apa_sampling_counter_max = 0x2;
		VPORT_I2C_Write((UINT32*)&gadc_dig_257_bx);

		gadc_dig_255_bx.apa_hsfal_offset = 0x8;
		VPORT_I2C_Write((UINT32*)&gadc_dig_255_bx);

		gadc_dig_259_bx.apa_phase_max_0 = 0x1;
		gadc_dig_258_bx.apa_phase_max_1 = 0;

		VPORT_I2C_Write((UINT32*)&gadc_dig_259_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_258_bx);

		//apa_phase_step : 0x1 : default

#if 0
		VPORT_I2C_Read((UINT32*)&gadc_dig_89_bx);
		gadc_dig_89_bx.aogc_src_sel = 0x1;
		gadc_dig_89_bx.aogc_enable_sel = 0x2;
		VPORT_I2C_Write((UINT32*)&gadc_dig_89_bx);

		VPORT_I2C_Read((UINT32*)&gadc_dig_99_bx);
		VPORT_I2C_Read((UINT32*)&gadc_dig_100_bx);
		gadc_dig_99_bx.aogc_counter_max_1 = 0x00;
		gadc_dig_100_bx.aogc_counter_max_0 = 0x02;
		VPORT_I2C_Write((UINT32*)&gadc_dig_99_bx);
		VPORT_I2C_Write((UINT32*)&gadc_dig_100_bx);

		VPORT_I2C_Read((UINT32*)&gadc_dig_98_bx);
		gadc_dig_98_bx.aogc_sample_count = 0x3;
		VPORT_I2C_Write((UINT32*)&gadc_dig_98_bx);

		VPORT_I2C_Read((UINT32*)&gadc_dig_98_bx);
		gadc_dig_98_bx.aogc_sample_accum = 0;
		VPORT_I2C_Write((UINT32*)&gadc_dig_98_bx);
#endif
	}
	return 0;
}

// 111123 wonsik.do : for post gain control for 110% white saturation test.
int ADC_L9Bx_Read_Sync_Low_Level(void)
{
	int level;

	gadc_dig_240_bx.apa_enable = 1;
	VPORT_I2C_Write((UINT32*)&gadc_dig_240_bx);
	OS_MsecSleep(5);

	VPORT_I2C_Read((UINT32*)&gadc_dig_265_bx);
	VPORT_I2C_Read((UINT32*)&gadc_dig_266_bx);

	level = (gadc_dig_265_bx.apa_data1_ro_1<<8)|gadc_dig_266_bx.apa_data1_ro_0;

//	ADC_DEBUG("apa_data1_ro = 		[0x%x]\n", level);

	gadc_dig_240_bx.apa_enable = 0;
	VPORT_I2C_Write((UINT32*)&gadc_dig_240_bx);

	return level;
}

// 111123 wonsik.do : for post gain control for 110% white saturation test.
int ADC_L9Bx_Post_Gain_Control(int percent)
{
	int G_Gain;

//	VPORT_I2C_Read((UINT32*)&gadc_dig_8_bx);
//	VPORT_I2C_Read((UINT32*)&gadc_dig_9_bx);
//	G_Gain = gadc_dig_8_bx.g_gain_1 << 8 | gadc_dig_9_bx.g_gain_0;

	//120103 wonsik.do : removed floating point in kernel driver
	//G_Gain = 0x1000 * (percent / 100.0);
	G_Gain = (0x1000 * percent) / 100;

	ADC_DEBUG("%s entered with value [0x%x]\n", __func__, G_Gain);

	gadc_dig_8_bx.g_gain_1 = (G_Gain >> 8) & 0x3F;
	gadc_dig_9_bx.g_gain_0 = (G_Gain) & 0xFF;

	VPORT_I2C_Write((UINT32*)&gadc_dig_8_bx);
	VPORT_I2C_Write((UINT32*)&gadc_dig_9_bx);

	return 0;
}

int ADC_L9Bx_LVDS_Channel_Enable_Control(int enable)
{
	ADC_DEBUG("%s entered : enable [%d]\n", __func__, enable);

	VPORT_I2C_Read((UINT32*)&gdata_bridge_21_bx);
	VPORT_I2C_Read((UINT32*)&gdata_bridge_22_bx);

	// LVDS CH0 is selected for 3CH ADC?
	if(gdata_bridge_21_bx.reg_lvds0_src == LX_AFE_LVDS_SOURCE_3CH) {
		VPORT_I2C_Read((UINT32*)&ghslvdstx0_1_bx);
		if(enable)
			ghslvdstx0_1_bx.ch_en1 = 0x3f;
		else
			ghslvdstx0_1_bx.ch_en1 = 0x0;
		VPORT_I2C_Write((UINT32*)&ghslvdstx0_1_bx);
	}

	// LVDS CH1 is selected for 3CH ADC?
	if(gdata_bridge_22_bx.reg_lvds1_src == LX_AFE_LVDS_SOURCE_3CH) {
		VPORT_I2C_Read((UINT32*)&ghslvdstx1_1_bx);
		if(enable)
			ghslvdstx1_1_bx.ch_en2 = 0x3f;
		else
			ghslvdstx1_1_bx.ch_en2 = 0x0;
		VPORT_I2C_Write((UINT32*)&ghslvdstx1_1_bx);
	}

	return 0;
}

/**
 * @brief set component SOG parameter settings
 *
 * @param width			: picture width
 * @param progressive	: interlace(0) or progressive(1)
 *
 * @return 
 */
int ADC_L9Bx_Set_Comp_Params(int width, int progressive, int v_freq)
{
	int ret = 0;

	if(width < 1024) {
		ADC_L9Bx_Set_Ctl_Add(0x0, 0x0, 0x2, 0x4);
		//120207 : use internal hsync for 480/576 I/P Component
		ADC_L9Bx_Set_Hsync_Sel(0);

		// 111123 wonsik.do : for post gain control for 110% white saturation test.
		if(progressive < 1)
			ADC_L9Bx_Enable_Sync_Low_Level_Read(1);
	}
	else {
		ADC_L9Bx_Set_Ctl_Add(0x0, 0x0, 0x2, 0x3);
		//120207 : use feedback hsync for 720P/1080IP Component Video
		ADC_L9Bx_Set_Hsync_Sel(1);
	}

	return ret;
}

/**
 * @brief Read A-Die Register Value
 *
 * @param addr
 * @param value
 *
 * @return 
 */
int ADC_L9Bx_Read_ACE_Reg(UINT32 addr , UINT32 *value)
{
	VPORT_I2C_DATA_T *i2cData = (VPORT_I2C_DATA_T*)&addr;

	VPORT_I2C_Read((UINT32*)i2cData);

	*value = i2cData->data;

	return 0;
}


/**
 * @brief Write data to A-Die Register
 *
 * @param addr
 * @param value
 *
 * @return 
 */
int ADC_L9Bx_Write_ACE_Reg(UINT32 addr , UINT32 value)
{
	VPORT_I2C_DATA_T *i2cData = (VPORT_I2C_DATA_T*)&addr;
	i2cData->data = (UINT8)(value&0x000000ff);

	VPORT_I2C_Write((UINT32*)i2cData);

	return 0;
}

