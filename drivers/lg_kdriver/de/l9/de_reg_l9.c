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


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.18
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
#define USE_DE_CVI_ACCESS_REGISTER_ON_MCU_PART
#undef	USE_DE_DOES_RESET_IN_SUSPEND_RESUME

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#ifndef USE_VIDEO_FOR_FPGA
#include "l9/base_addr_sw_l9.h"
#endif

#include "de_model.h"
#include "de_ver_def.h"

#ifdef USE_KDRV_CODES_FOR_L9
#include "de_kapi.h"
#include "de_def.h"
#include "de_prm_def.h"
#include "de_hal_def.h"
#include "de_cfg.h"
#include "de_drv.h"

#include "l9/de_cfg_l9.h"
#include "l9/de_ipc_def_l9.h"
#include "l9/de_int_def_l9.h"
#include "l9/de_reg_def_l9.h"
#include "l9/de_reg_l9.h"
#include "l9/de_prm_l9.h"

#include "l9/de_ctr_reg_l9.h"		// 0x0000, 0x1000, 0x2000, 0x3000, 0x4000
#include "l9/de_cvi_reg_l9.h"		// 0x0100, 0x0200
#include "l9/de_dlr_reg_l9.h"		// 0x0300
#include "l9/de_pe0_reg_l9.h"		// 0x0400
#include "l9/de_mif_reg_l9.h"		// 0x0800, 0x1b00, 0x2800, 0x3e00
#include "l9/de_msc_reg_l9.h"		// 0x1100, 0x3100
#include "l9/de_wcp_reg_l9.h"		// 0x1200, 0x3200
#include "l9/de_pe1_reg_l9.h"		// 0x1300, 0x3300
#include "l9/de_ssc_reg_l9.h"		// 0x2100
#include "l9/de_t3d_reg_l9.h"		// 0x3920
#include "l9/de_osd_reg_l9.h"		// 0x3a00
//#include "l9/de_atp_reg_l9.h"		  // 0x3c00
#include "l9/de_oif_reg_l9.h"		// 0x3d00
#include "l9/de_cvd_reg_l9.h"		// 0x4100

#include "l9/de_vdi_reg_l9.h"		// 0x4d00
#include "l9/de_ipc_reg_l9.h"		// 0x4e00
#include "l9/de_dvr_reg_l9.h"		// 0x5400

//#include "../sys/ctop_regs.h"
#include "l9/ctop_ctrl_reg_l9.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define SIZE_OF_IPC_FOR_CPU 15
#define ADDR_SW_CONTROLLED_BY_CFG
#define ADDR_SW_CASE4

#define USE_DE_FIRMWARE_BOOT_OFFSET 0x30000000

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
#define MAX_PE_TPG_RECT 32
#define MAX_PE_TPG_RECT_B0 16
/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
extern LX_DE_MEM_CFG_T *gpDeMem;
#endif
//extern volatile VPORT_Reg_T *gVportReg;
//extern volatile HDMI_PHY3P_Reg_T *pstHdmiPhyReg;

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/
DE_DEA_REG_L9_T gDE_DEA_L9;
DE_DEB_REG_L9_T gDE_DEB_L9;
DE_DEC_REG_L9_T gDE_DEC_L9;
DE_DED_REG_L9_T gDE_DED_L9;
DE_DEE_REG_L9_T gDE_DEE_L9;
DE_DEF_REG_L9_T gDE_DEF_L9;

DE_CVA_REG_L9_T gDE_CVA_L9;
DE_CVB_REG_L9_T gDE_CVB_L9;

DE_DLR_REG_L9_T gDE_DLR_L9;

DE_P0L_REG_L9_T gDE_P0L_L9;
DE_P0R_REG_L9_T gDE_P0R_L9;
DE_P0L_REG_L9B_T gDE_P0L_L9B;
DE_P0R_REG_L9B_T gDE_P0R_L9B;

DE_MIA_REG_L9_T gDE_MIA_L9;
DE_MIB_REG_L9_T gDE_MIB_L9;
DE_MIC_REG_L9_T gDE_MIC_L9;
DE_MID_REG_L9_T gDE_MID_L9;
DE_MIF_REG_L9_T gDE_MIF_L9;

DE_MSL_REG_L9_T gDE_MSL_L9;
DE_MSR_REG_L9_T gDE_MSR_L9;

DE_OVL_REG_L9_T gDE_OVL_L9;
DE_OVR_REG_L9_T gDE_OVR_L9;

DE_P1L_REG_L9_T gDE_P1L_L9;
DE_P1R_REG_L9_T gDE_P1R_L9;
DE_P1L_REG_L9B_T gDE_P1L_L9B;
DE_P1R_REG_L9B_T gDE_P1R_L9B;

DE_SSC_REG_L9_T gDE_SSC_L9;
DE_T3D_REG_L9_T gDE_T3D_L9;
DE_OSD_REG_L9_T gDE_OSD_L9;
//DE_ATP_REG_L9_T gDE_ATP_L9;
DE_OIF_REG_L9_T gDE_OIF_L9;
DE_CVD_REG_L9_T gDE_CVD_L9;

DE_VDI_REG_L9_T gDE_VDC_L9;
DE_VDI_REG_L9_T gDE_VDD_L9;
DE_IPC_REG_L9_T gDE_IPC_L9;
DE_DVR_REG_L9_T gDE_DVR_L9;

CTOP_CTRL_REG_L9_T gDE_CTOP_L9;

BOOLEAN g_b_PllMain_L9 = FALSE;
BOOLEAN g_b_pllFrc_L9  = FALSE;

BOOLEAN g_b_InitTPG_L9 = FALSE;
UINT32	g_patchEn_L9   = 0;

LX_DE_INPUT_PORT	g_WinSrc_L9[2] = { LX_DE_PORT_MVI,	LX_DE_PORT_MVI};

typedef struct {
	LX_DE_MULTI_SRC_T src;
	BOOLEAN used;
	UINT32 cvi_mux_sel;
	UINT32 exta_sel;
	UINT32 extb_sel;
}
LX_DE_SRC_CONFIG;

LX_DE_SRC_CONFIG sMultiSrc_map_L9[4][LX_DE_MULTI_IN_MAX + 1] =
{
	{	/* L9-A0 No hdmi switch */
		{LX_DE_MULTI_IN_CVD_ADC,	 TRUE,	11, 0, 0},
		{LX_DE_MULTI_IN_CVD_HDMI,	 TRUE,	9,	0, 1},
		{LX_DE_MULTI_IN_CVD_MVI,	 TRUE,	9,	0, 1},
		{LX_DE_MULTI_IN_ADC_CVD,	 TRUE,	8,	0, 0},
		{LX_DE_MULTI_IN_ADC_HDMI,	 TRUE,	6,	0, 1},
		{LX_DE_MULTI_IN_ADC_MVI,	 TRUE,	6,	0, 1},
		{LX_DE_MULTI_IN_HDMI_CVD,	 TRUE,	2,	1, 0},
		{LX_DE_MULTI_IN_HDMI_ADC,	 TRUE,	1,	1, 0},
		{LX_DE_MULTI_IN_HDMI_MVI,	 TRUE,	1,	1, 0},
		{LX_DE_MULTI_IN_MVI_CVD,	 TRUE,	8,	0, 0},
		{LX_DE_MULTI_IN_MVI_ADC,	 TRUE,	1,	1, 0},
		{LX_DE_MULTI_IN_MVI_HDMI,	 TRUE,	6,	0, 1},
		{LX_DE_MULTI_IN_MVA_MVB,	 TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_HDMIA_HDMIB, TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_MAX,		 TRUE,	0,	0, 0}
	},

	{	/* L9-A0 hdmi switch */
		{LX_DE_MULTI_IN_CVD_ADC,	 TRUE,	11, 0, 0},
		{LX_DE_MULTI_IN_CVD_HDMI,	 TRUE,	10, 0, 2},
		{LX_DE_MULTI_IN_CVD_MVI,	 TRUE,	10, 0, 2},
		{LX_DE_MULTI_IN_ADC_CVD,	 TRUE,	8,	0, 0},
		{LX_DE_MULTI_IN_ADC_HDMI,	 TRUE,	7,	0, 2},
		{LX_DE_MULTI_IN_ADC_MVI,	 TRUE,	7,	0, 2},
		{LX_DE_MULTI_IN_HDMI_CVD,	 TRUE,	5,	2, 0},
		{LX_DE_MULTI_IN_HDMI_ADC,	 TRUE,	4,	2, 0},
		{LX_DE_MULTI_IN_HDMI_MVI,	 TRUE,	4,	2, 0},
		{LX_DE_MULTI_IN_MVI_CVD,	 TRUE,	8,	0, 0},
		{LX_DE_MULTI_IN_MVI_ADC,	 TRUE,	4,	2, 0},
		{LX_DE_MULTI_IN_MVI_HDMI,	 TRUE,	7,	0, 2},
		{LX_DE_MULTI_IN_MVA_MVB,	 TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_HDMIA_HDMIB, TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_MAX,		 TRUE,	0,	0, 0}
	},

	{	/* L9-A1 hdmi switch */
		{LX_DE_MULTI_IN_CVD_ADC,	 TRUE,	11, 2, 0},
		{LX_DE_MULTI_IN_CVD_HDMI,	 TRUE,	9,	2, 1},
		{LX_DE_MULTI_IN_CVD_MVI,	 TRUE,	9,	2, 1},
		{LX_DE_MULTI_IN_ADC_CVD,	 TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_ADC_HDMI,	 TRUE,	6,	0, 1},
		{LX_DE_MULTI_IN_ADC_MVI,	 TRUE,	6,	0, 1},
		{LX_DE_MULTI_IN_HDMI_CVD,	 TRUE,	0,	1, 0},
		{LX_DE_MULTI_IN_HDMI_ADC,	 TRUE,	1,	1, 0},
		{LX_DE_MULTI_IN_HDMI_MVI,	 TRUE,	1,	1, 0},
		{LX_DE_MULTI_IN_MVI_CVD,	 TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_MVI_ADC,	 TRUE,	11, 2, 0},
		{LX_DE_MULTI_IN_MVI_HDMI,	 TRUE,	9,	2, 1},
		{LX_DE_MULTI_IN_MVA_MVB,	 TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_HDMIA_HDMIB, TRUE,	0,	0, 0},
		{LX_DE_MULTI_IN_MAX,		 TRUE,	0,	0, 0}
	},

	{	/* L9-B0 */
	{LX_DE_MULTI_IN_CVD_ADC,	TRUE,	 0, 2,	1}, /* x, x, cvd_sel, cvia_sel, cvib_sel : (DEE_CVI_MUX_SEL) */
	{LX_DE_MULTI_IN_CVD_HDMI,	TRUE,	 0, 2,	1},
	{LX_DE_MULTI_IN_CVD_MVI,	TRUE,	 0, 2,	1},
	{LX_DE_MULTI_IN_CVD_CVD,	TRUE,	 0, 2,	1},
	{LX_DE_MULTI_IN_ADC_CVD,	TRUE,	 1, 0,	2},
	{LX_DE_MULTI_IN_ADC_HDMI,	TRUE,	 1, 0,	1},
	{LX_DE_MULTI_IN_ADC_MVI,	TRUE,	 1, 0,	1},
	{LX_DE_MULTI_IN_ADC_ADC,	TRUE,	 1, 0,	1},
	{LX_DE_MULTI_IN_HDMI_CVD,	TRUE,	 1, 0,	2},
	{LX_DE_MULTI_IN_HDMI_ADC,	TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_HDMI_MVI,	TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_HDMI_HDMI,	TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_MVI_CVD,	TRUE,	 1, 0,	2},
	{LX_DE_MULTI_IN_MVI_ADC,	TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_MVI_HDMI,	TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_MVI_MVI,	TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_MVA_MVB,	TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_HDMIA_HDMIB,TRUE,	 0, 0,	1},
	{LX_DE_MULTI_IN_MAX,		TRUE,	 0, 0,	0}
	}
};

BOOLEAN sbDeUdMode = FALSE;
BOOLEAN sbDe3DFullMode = FALSE;
static LX_DE_CVI_SRC_TYPE_T sCviSrcType;
LX_DE_MULTI_WIN_SRC_T sDeMultiWinSrc = {0,0};

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_L9_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static UINT32		   *spVideoIPCofCPU[2]	  = {NULL};
static DE_DPLL_SET_T sDisplayPll_L9[] = {
	{ DCLK_61_875	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_65		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_66_462	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_66_528	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_36_818	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_36_855	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_54		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_54_054	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_74_1758	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_74_25	,{ 0 ,0x2 ,0x3 } },
	{ DCLK_80_109	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_80_190	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_81		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_27		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_13_5		,{ 0 ,0x2 ,0x2 } },
	{ DCLK_27_027	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_13_5135	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_148_3516 ,{ 0 ,0x2 ,0x2 } },
	{ DCLK_148_5	,{ 0 ,0x2 ,0x2 } },
	{ DCLK_85_86	,{ 0 ,0x2 ,0x2 } },
};

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/
#ifdef USE_PWM_RUN_IN_KDRIVER
#define VIDEO_PWM_NUM 1
#define PWM_DUTY_MAX		255
#define DTV_STATUS_T	int
static DE_PWM_INFO_T gVideoPwmInfo[PWM_NUM_MAX];
DTV_STATUS_T DE_PWM_Init(void);
DTV_STATUS_T DE_PWM_SetCtrl(UINT32 pwmId, VIDEO_PWM_CTRL_TYPE_T ctrId, UINT32 ctrVal);
DTV_STATUS_T DE_PWM_SetTiming(UINT32 pwmId, VIDEO_PWM_ORD_T pwmOrd, UINT32 *pR1st, UINT32 *pFall, UINT32 *pR2nd);
DTV_STATUS_T DE_PWM_GetTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall);
DTV_STATUS_T DE_PWM_SetRegCtrl(UINT32 pwmId);
#endif

int DE_REG_L9_InitAddrSwitch(void)
{
#ifdef ADDR_SW_CONTROLLED_BY_CFG
	LX_ADDR_SW_CFG_T	addr_sw;
#endif

	printk("^g^ DE SIZE = %d\n", VIDEO_L9_MEM_SIZE_OF_FRAME_MEMORY );

#ifdef ADDR_SW_CONTROLLED_BY_CFG
	// DEA
	BASE_L9_GetAddrSwCfg(ADDR_SW_CFG_DE_A, &addr_sw);
	DE_DEA_L9_FLWr(dea_addr_sw_de_sav,		   addr_sw.de_sav);
	DE_DEA_L9_FLWr(dea_addr_sw_cpu_gpu,		   addr_sw.cpu_gpu);
	DE_DEA_L9_FLWr(dea_addr_sw_cpu_shadow,	   addr_sw.cpu_shadow);

	// DEB
	BASE_L9_GetAddrSwCfg(ADDR_SW_CFG_DE_B, &addr_sw);
	DE_DEB_L9_FLWr(deb_addr_sw_de_sav,		   addr_sw.de_sav);
	DE_DEB_L9_FLWr(deb_addr_sw_cpu_gpu,		   addr_sw.cpu_gpu);
	DE_DEB_L9_FLWr(deb_addr_sw_cpu_shadow,	   addr_sw.cpu_shadow);

	// DEC
	BASE_L9_GetAddrSwCfg(ADDR_SW_CFG_DE_C, &addr_sw);
	DE_DEC_L9_FLWr(dec_addr_sw_de_sav,		   addr_sw.de_sav);
	DE_DEC_L9_FLWr(dec_addr_sw_cpu_gpu,		   addr_sw.cpu_gpu);
	DE_DEC_L9_FLWr(dec_addr_sw_cpu_shadow,	   addr_sw.cpu_shadow);

	// DED
	BASE_L9_GetAddrSwCfg(ADDR_SW_CFG_DE_D, &addr_sw);
	DE_DED_L9_FLWr(ded_addr_sw_de_sav,		   addr_sw.de_sav);
	DE_DED_L9_FLWr(ded_addr_sw_cpu_gpu,		   addr_sw.cpu_gpu);
	DE_DED_L9_FLWr(ded_addr_sw_cpu_shadow,	   addr_sw.cpu_shadow);

	// DEE
	BASE_L9_GetAddrSwCfg(ADDR_SW_CFG_DE_E, &addr_sw);
	DE_DEE_L9_FLWr(dee_cvd_addr_sw_de_sav,	   addr_sw.de_sav);
	DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_gpu,    addr_sw.cpu_gpu);
	DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_shadow, addr_sw.cpu_shadow);

	// DEMCU
	BASE_L9_GetAddrSwCfg(ADDR_SW_CFG_DE,  &addr_sw);
	DE_DEE_L9_FLWr(dee_mcu_addr_sw_de_sav,	   addr_sw.de_sav);
	DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_gpu,    addr_sw.cpu_gpu);
	DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_shadow, addr_sw.cpu_shadow);
#elif defined(ADDR_SW_CASE4)
	/* address switch setting based on TARGET_PRODUCT */
	switch (lx_chip_plt()) {
		case LX_CHIP_PLATFORM_COSMO :
			//address switch setting as CASE2 for COSMO
			// DEA
			DE_DEA_L9_FLWr(dea_addr_sw_de_sav,		   0x24030210);
			DE_DEA_L9_FLWr(dea_addr_sw_cpu_gpu,		   0x20028058);
			DE_DEA_L9_FLWr(dea_addr_sw_cpu_shadow,	   0x04018208);

			// DEB
			DE_DEB_L9_FLWr(deb_addr_sw_de_sav,		   0x28030210);
			DE_DEB_L9_FLWr(deb_addr_sw_cpu_gpu,		   0x20028058);
			DE_DEB_L9_FLWr(deb_addr_sw_cpu_shadow,	   0x04018208);

			// DEC
			DE_DEC_L9_FLWr(dec_addr_sw_de_sav,		   0x2C030210);
			DE_DEC_L9_FLWr(dec_addr_sw_cpu_gpu,		   0x20028058);
			DE_DEC_L9_FLWr(dec_addr_sw_cpu_shadow,	   0x04018208);

			// DED
			DE_DED_L9_FLWr(ded_addr_sw_de_sav,		   0x30030210);
			DE_DED_L9_FLWr(ded_addr_sw_cpu_gpu,		   0x20028058);
			DE_DED_L9_FLWr(ded_addr_sw_cpu_shadow,	   0x04018208);

			// DEE
			DE_DEE_L9_FLWr(dee_cvd_addr_sw_de_sav,	   0x34030210);
			DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_gpu,    0x20028058);
			DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_shadow, 0x04018208);

			// DEMCU
			DE_DEE_L9_FLWr(dee_mcu_addr_sw_de_sav,	   0x24000210);
			DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_gpu,    0x20028058);
			DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_shadow, 0x04018208);
			break;
		case LX_CHIP_PLATFORM_GP :
		default :
			//address switch setting as CASE4 for GP
			// DEA
			DE_DEA_L9_FLWr(dea_addr_sw_de_sav,		   0x24030210);
			DE_DEA_L9_FLWr(dea_addr_sw_cpu_gpu,		   0x00020050);
			DE_DEA_L9_FLWr(dea_addr_sw_cpu_shadow,	   0x04010200);

			// DEB
			DE_DEB_L9_FLWr(deb_addr_sw_de_sav,		   0x28030210);
			DE_DEB_L9_FLWr(deb_addr_sw_cpu_gpu,		   0x00020050);
			DE_DEB_L9_FLWr(deb_addr_sw_cpu_shadow,	   0x04010200);

			// DEC
			DE_DEC_L9_FLWr(dec_addr_sw_de_sav,		   0x2C030210);
			DE_DEC_L9_FLWr(dec_addr_sw_cpu_gpu,		   0x00020050);
			DE_DEC_L9_FLWr(dec_addr_sw_cpu_shadow,	   0x04010200);

			// DED
			DE_DED_L9_FLWr(ded_addr_sw_de_sav,		   0x30030210);
			DE_DED_L9_FLWr(ded_addr_sw_cpu_gpu,		   0x00020050);
			DE_DED_L9_FLWr(ded_addr_sw_cpu_shadow,	   0x04010200);

			// DEE
			DE_DEE_L9_FLWr(dee_cvd_addr_sw_de_sav,	   0x34030210);
			DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_gpu,    0x00020050);
			DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_shadow, 0x04010200);

			// DEMCU
			DE_DEE_L9_FLWr(dee_mcu_addr_sw_de_sav,	   0x24000210);
			DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_gpu,    0x00020050);
			DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_shadow, 0x04010200);
			break;
	}
#else
	// DEA
	DE_DEA_L9_FLWr(dea_addr_sw_de_sav, 0x24030218);
	DE_DEA_L9_FLWr(dea_addr_sw_cpu_gpu, 0x20030058);
	DE_DEA_L9_FLWr(dea_addr_sw_cpu_shadow, 0x04018210);

	// DEB
	DE_DEB_L9_FLWr(deb_addr_sw_de_sav, 0x28030218);
	DE_DEB_L9_FLWr(deb_addr_sw_cpu_gpu, 0x20030058);
	DE_DEB_L9_FLWr(deb_addr_sw_cpu_shadow, 0x04018210);

	// DEC
	DE_DEC_L9_FLWr(dec_addr_sw_de_sav, 0x2C030218);
	DE_DEC_L9_FLWr(dec_addr_sw_cpu_gpu, 0x20030058);
	DE_DEC_L9_FLWr(dec_addr_sw_cpu_shadow, 0x04018210);

	// DED
	DE_DED_L9_FLWr(ded_addr_sw_de_sav, 0x30030218);
	DE_DED_L9_FLWr(ded_addr_sw_cpu_gpu, 0x20030058);
	DE_DED_L9_FLWr(ded_addr_sw_cpu_shadow, 0x04018210);

	// DEE
	DE_DEE_L9_FLWr(dee_cvd_addr_sw_de_sav, 0x34030218);
	DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_gpu, 0x20030058);
	DE_DEE_L9_FLWr(dee_cvd_addr_sw_cpu_shadow, 0x04018210);

	// DEMCU
	DE_DEE_L9_FLWr(dee_mcu_addr_sw_de_sav, 0x24000218);
	DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_gpu, 0x20030058);
	DE_DEE_L9_FLWr(dee_mcu_addr_sw_cpu_shadow, 0x04018210);
#endif

	return 0;
}
/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize Reigerter Physical Address to Virtual Address and Make Shadow Register
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_InitPHY2VIRT(void)
{
	int ret = RET_OK;

	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
		gDE_DEA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEA_REG_L9B0_T));
		gDE_DEB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEB_REG_L9B0_T));
		gDE_DEC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEC_REG_L9B0_T));
		gDE_DED_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DED_REG_L9B0_T));
		gDE_DEE_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEE_REG_L9B0_T));

		gDE_CVA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_CVA_REG_L9B0_T));
		gDE_CVB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_CVB_REG_L9B0_T));

		gDE_DLR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DLR_REG_L9B0_T));

		gDE_P0L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_L9B0_T));
		gDE_P0R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_L9B0_T));
		gDE_P0L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_L9B0_T));
		gDE_P0R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_L9B0_T));

		gDE_MIA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MIA_REG_L9B0_T));
		gDE_MIB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MIB_REG_L9B0_T));
		gDE_MIC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MIC_REG_L9B0_T));
		gDE_MID_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MID_REG_L9B0_T));
		gDE_MIF_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MIF_REG_L9B0_T));

		gDE_MSL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MSL_REG_L9B0_T));
		gDE_MSR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MSR_REG_L9B0_T));

		gDE_OVL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OVL_REG_L9B0_T));
		gDE_OVR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OVR_REG_L9B0_T));

		gDE_P1L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_L9B0_T));
		gDE_P1R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_L9B0_T));
		gDE_P1L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_L9B0_T));
		gDE_P1R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_L9B0_T));

		gDE_SSC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_SSC_REG_L9B0_T));
		gDE_T3D_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_T3D_REG_L9B0_T));
		gDE_OSD_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OSD_REG_L9B0_T));
		//gDE_ATP_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_ATP_REG_L9B0_T));
		gDE_OIF_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OIF_REG_L9B0_T));
		gDE_CVD_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_CVD_REG_L9B0_T));

		gDE_VDC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_L9B0_T));
		gDE_VDD_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_L9B0_T));

		gDE_IPC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_IPC_REG_L9B0_T));
		gDE_DVR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DVR_REG_L9B0_T));

		gDE_CTOP_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(CTOP_CTRL_REG_L9B0_T));

		gDE_DEA_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEA_REG_L9_BASE, sizeof(DE_DEA_REG_L9B0_T));
		gDE_DEB_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEB_REG_L9_BASE, sizeof(DE_DEB_REG_L9B0_T));
		gDE_DEC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEC_REG_L9_BASE, sizeof(DE_DEC_REG_L9B0_T));
		gDE_DED_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DED_REG_L9_BASE, sizeof(DE_DED_REG_L9B0_T));
		gDE_DEE_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEE_REG_L9_BASE, sizeof(DE_DEE_REG_L9B0_T));
		gDE_DEF_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEF_REG_L9B0_BASE, sizeof(DE_DEE_REG_L9B0_T));

		gDE_CVA_L9.phys.addr = (volatile UINT32 *)ioremap(DE_CVA_REG_L9_BASE, sizeof(DE_CVA_REG_L9B0_T));
		gDE_CVB_L9.phys.addr = (volatile UINT32 *)ioremap(DE_CVB_REG_L9_BASE, sizeof(DE_CVB_REG_L9B0_T));

		gDE_DLR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DLR_REG_L9_BASE, sizeof(DE_DLR_REG_L9B0_T));

		gDE_P0L_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P0L_REG_L9_BASE, sizeof(DE_P0L_REG_L9B0_T));
		gDE_P0R_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P0R_REG_L9_BASE, sizeof(DE_P0R_REG_L9B0_T));
		gDE_P0L_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P0L_REG_L9_BASE, sizeof(DE_P0L_REG_L9B0_T));
		gDE_P0R_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P0R_REG_L9_BASE, sizeof(DE_P0R_REG_L9B0_T));

		gDE_MIA_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MIA_REG_L9_BASE, sizeof(DE_MIA_REG_L9B0_T));
		gDE_MIB_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MIB_REG_L9_BASE, sizeof(DE_MIB_REG_L9B0_T));
		gDE_MIC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MIC_REG_L9_BASE, sizeof(DE_MIC_REG_L9B0_T));
		gDE_MID_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MID_REG_L9B0_BASE, sizeof(DE_MID_REG_L9B0_T));
		gDE_MIF_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MIF_REG_L9B0_BASE, sizeof(DE_MIF_REG_L9B0_T));

		gDE_MSL_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MSL_REG_L9_BASE, sizeof(DE_MSL_REG_L9B0_T));
		gDE_MSR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MSR_REG_L9_BASE, sizeof(DE_MSR_REG_L9B0_T));

		gDE_OVL_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OVL_REG_L9_BASE, sizeof(DE_OVL_REG_L9B0_T));
		gDE_OVR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OVR_REG_L9_BASE, sizeof(DE_OVR_REG_L9B0_T));

		gDE_P1L_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P1L_REG_L9_BASE, sizeof(DE_P1L_REG_L9B0_T));
		gDE_P1R_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P1R_REG_L9_BASE, sizeof(DE_P1R_REG_L9B0_T));
		gDE_P1L_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P1L_REG_L9_BASE, sizeof(DE_P1L_REG_L9B0_T));
		gDE_P1R_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P1R_REG_L9_BASE, sizeof(DE_P1R_REG_L9B0_T));

		gDE_SSC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_SSC_REG_L9_BASE, sizeof(DE_SSC_REG_L9B0_T));
		gDE_T3D_L9.phys.addr = (volatile UINT32 *)ioremap(DE_T3D_REG_L9_BASE, sizeof(DE_T3D_REG_L9B0_T));
		gDE_OSD_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OSD_REG_L9B0_BASE, sizeof(DE_OSD_REG_L9B0_T));
		//gDE_ATP_L9.phys.addr = (volatile UINT32 *)ioremap(DE_ATP_REG_L9B0_BASE, sizeof(DE_ATP_REG_L9B0_T));
		gDE_OIF_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OIF_REG_L9B0_BASE, sizeof(DE_OIF_REG_L9B0_T));
		gDE_CVD_L9.phys.addr = (volatile UINT32 *)ioremap(DE_CVD_REG_L9_BASE, sizeof(DE_CVD_REG_L9B0_T));

		gDE_IPC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_IPC_REG_L9_BASE, sizeof(DE_IPC_REG_L9B0_T));
		gDE_DVR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DVR_REG_L9_BASE, sizeof(DE_DVR_REG_L9B0_T));

		gDE_VDC_L9.phys.addr = (volatile UINT32 *)ioremap(VDEC_CPC_IPC_BASE, sizeof(DE_VDI_REG_L9B0_T));
		gDE_VDD_L9.phys.addr = (volatile UINT32 *)ioremap(VDEC_CPD_IPC_BASE, sizeof(DE_VDI_REG_L9B0_T));

		gDE_CTOP_L9.phys.addr = (volatile UINT32 *)ioremap(DTVSOC_CTOP_CTRL_L9_BASE, sizeof(CTOP_CTRL_REG_L9B0_T));
	} else {
		gDE_DEA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEA_REG_L9A0_T));
		gDE_DEB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEB_REG_L9A0_T));
		gDE_DEC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEC_REG_L9A0_T));
		gDE_DED_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DED_REG_L9A0_T));
		gDE_DEE_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DEE_REG_L9A0_T));

		gDE_CVA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_CVA_REG_L9A0_T));
		gDE_CVB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_CVB_REG_L9A0_T));

		gDE_DLR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DLR_REG_L9A0_T));

		gDE_P0L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_L9A0_T));
		gDE_P0R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_L9A0_T));
		gDE_P0L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_L9B0_T));
		gDE_P0R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_L9B0_T));

		gDE_MIA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MIA_REG_L9A0_T));
		gDE_MIB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MIB_REG_L9A0_T));
		gDE_MIC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MIC_REG_L9A0_T));
		gDE_MID_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MID_REG_L9A0_T));

		gDE_MSL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MSL_REG_L9A0_T));
		gDE_MSR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_MSR_REG_L9A0_T));

		gDE_OVL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OVL_REG_L9A0_T));
		gDE_OVR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OVR_REG_L9A0_T));

		gDE_P1L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_L9A0_T));
		gDE_P1R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_L9A0_T));
		gDE_P1L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_L9B0_T));
		gDE_P1R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_L9B0_T));

		gDE_SSC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_SSC_REG_L9A0_T));
		gDE_T3D_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_T3D_REG_L9A0_T));
		gDE_OSD_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OSD_REG_L9A0_T));
		//gDE_ATP_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_ATP_REG_L9A0_T));
		gDE_OIF_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_OIF_REG_L9A0_T));
		gDE_CVD_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_CVD_REG_L9A0_T));

		gDE_VDC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_L9A0_T));
		gDE_VDD_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_L9A0_T));

		gDE_IPC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_IPC_REG_L9A0_T));
		gDE_DVR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_DVR_REG_L9A0_T));

		gDE_CTOP_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(CTOP_CTRL_REG_L9_T));

		gDE_DEA_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEA_REG_L9_BASE, sizeof(DE_DEA_REG_L9A0_T));
		gDE_DEB_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEB_REG_L9_BASE, sizeof(DE_DEB_REG_L9A0_T));
		gDE_DEC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEC_REG_L9_BASE, sizeof(DE_DEC_REG_L9A0_T));
		gDE_DED_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DED_REG_L9_BASE, sizeof(DE_DED_REG_L9A0_T));
		gDE_DEE_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DEE_REG_L9_BASE, sizeof(DE_DEE_REG_L9A0_T));

		gDE_CVA_L9.phys.addr = (volatile UINT32 *)ioremap(DE_CVA_REG_L9_BASE, sizeof(DE_CVA_REG_L9A0_T));
		gDE_CVB_L9.phys.addr = (volatile UINT32 *)ioremap(DE_CVB_REG_L9_BASE, sizeof(DE_CVB_REG_L9A0_T));

		gDE_DLR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DLR_REG_L9_BASE, sizeof(DE_DLR_REG_L9A0_T));

		gDE_P0L_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P0L_REG_L9_BASE, sizeof(DE_P0L_REG_L9A0_T));
		gDE_P0R_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P0R_REG_L9_BASE, sizeof(DE_P0R_REG_L9A0_T));
		gDE_P0L_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P0L_REG_L9_BASE, sizeof(DE_P0L_REG_L9B0_T));
		gDE_P0R_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P0R_REG_L9_BASE, sizeof(DE_P0R_REG_L9B0_T));

		gDE_MIA_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MIA_REG_L9_BASE, sizeof(DE_MIA_REG_L9A0_T));
		gDE_MIB_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MIB_REG_L9_BASE, sizeof(DE_MIB_REG_L9A0_T));
		gDE_MIC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MIC_REG_L9_BASE, sizeof(DE_MIC_REG_L9A0_T));
		gDE_MID_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MID_REG_L9_BASE, sizeof(DE_MID_REG_L9A0_T));

		gDE_MSL_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MSL_REG_L9_BASE, sizeof(DE_MSL_REG_L9A0_T));
		gDE_MSR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_MSR_REG_L9_BASE, sizeof(DE_MSR_REG_L9A0_T));

		gDE_OVL_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OVL_REG_L9_BASE, sizeof(DE_OVL_REG_L9A0_T));
		gDE_OVR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OVR_REG_L9_BASE, sizeof(DE_OVR_REG_L9A0_T));

		gDE_P1L_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P1L_REG_L9_BASE, sizeof(DE_P1L_REG_L9A0_T));
		gDE_P1R_L9.phys.addr = (volatile UINT32 *)ioremap(DE_P1R_REG_L9_BASE, sizeof(DE_P1R_REG_L9A0_T));
		gDE_P1L_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P1L_REG_L9_BASE, sizeof(DE_P1L_REG_L9B0_T));
		gDE_P1R_L9B.phys.addr = (volatile UINT32 *)ioremap(DE_P1R_REG_L9_BASE, sizeof(DE_P1R_REG_L9B0_T));

		gDE_SSC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_SSC_REG_L9_BASE, sizeof(DE_SSC_REG_L9A0_T));
		gDE_T3D_L9.phys.addr = (volatile UINT32 *)ioremap(DE_T3D_REG_L9_BASE, sizeof(DE_T3D_REG_L9A0_T));
		gDE_OSD_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OSD_REG_L9_BASE, sizeof(DE_OSD_REG_L9A0_T));
		//gDE_ATP_L9.phys.addr = (volatile UINT32 *)ioremap(DE_ATP_REG_L9_BASE, sizeof(DE_ATP_REG_L9A0_T));
		gDE_OIF_L9.phys.addr = (volatile UINT32 *)ioremap(DE_OIF_REG_L9_BASE, sizeof(DE_OIF_REG_L9A0_T));
		gDE_CVD_L9.phys.addr = (volatile UINT32 *)ioremap(DE_CVD_REG_L9_BASE, sizeof(DE_CVD_REG_L9A0_T));

		gDE_IPC_L9.phys.addr = (volatile UINT32 *)ioremap(DE_IPC_REG_L9_BASE, sizeof(DE_IPC_REG_L9A0_T));
		gDE_DVR_L9.phys.addr = (volatile UINT32 *)ioremap(DE_DVR_REG_L9_BASE, sizeof(DE_DVR_REG_L9A0_T));

		gDE_VDC_L9.phys.addr = (volatile UINT32 *)ioremap(VDEC_CPC_IPC_BASE, sizeof(DE_VDI_REG_L9A0_T));
		gDE_VDD_L9.phys.addr = (volatile UINT32 *)ioremap(VDEC_CPD_IPC_BASE, sizeof(DE_VDI_REG_L9A0_T));

		gDE_CTOP_L9.phys.addr = (volatile UINT32 *)ioremap(DTVSOC_CTOP_CTRL_L9_BASE, sizeof(CTOP_CTRL_REG_L9A0_T));
	}

	gpDeMem = &gMemCfgDe[0];

	spVideoIPCofCPU[0] = (UINT32 *)gDE_VDC_L9.phys.addr;
	spVideoIPCofCPU[1] = (UINT32 *)gDE_VDD_L9.phys.addr;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Free memory alocated in Shadow Register
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_FreePHY2VIRT(void)
{
	OS_Free((void *)gDE_DEA_L9.shdw.addr);
	OS_Free((void *)gDE_DEB_L9.shdw.addr);
	OS_Free((void *)gDE_DEC_L9.shdw.addr);
	OS_Free((void *)gDE_DED_L9.shdw.addr);
	OS_Free((void *)gDE_DEE_L9.shdw.addr);
	OS_Free((void *)gDE_DEF_L9.shdw.addr);

	OS_Free((void *)gDE_CVA_L9.shdw.addr);
	OS_Free((void *)gDE_CVB_L9.shdw.addr);

	OS_Free((void *)gDE_DLR_L9.shdw.addr);

	OS_Free((void *)gDE_P0L_L9.shdw.addr);
	OS_Free((void *)gDE_P0R_L9.shdw.addr);
	OS_Free((void *)gDE_P0L_L9B.shdw.addr);
	OS_Free((void *)gDE_P0R_L9B.shdw.addr);

	OS_Free((void *)gDE_MIA_L9.shdw.addr);
	OS_Free((void *)gDE_MIB_L9.shdw.addr);
	OS_Free((void *)gDE_MIC_L9.shdw.addr);
	OS_Free((void *)gDE_MID_L9.shdw.addr);
	OS_Free((void *)gDE_MIF_L9.shdw.addr);

	OS_Free((void *)gDE_MSL_L9.shdw.addr);
	OS_Free((void *)gDE_MSR_L9.shdw.addr);

	OS_Free((void *)gDE_OVL_L9.shdw.addr);
	OS_Free((void *)gDE_OVR_L9.shdw.addr);

	OS_Free((void *)gDE_P1L_L9.shdw.addr);
	OS_Free((void *)gDE_P1R_L9.shdw.addr);
	OS_Free((void *)gDE_P1L_L9B.shdw.addr);
	OS_Free((void *)gDE_P1R_L9B.shdw.addr);

	OS_Free((void *)gDE_SSC_L9.shdw.addr);
	OS_Free((void *)gDE_T3D_L9.shdw.addr);
	OS_Free((void *)gDE_OSD_L9.shdw.addr);
	//OS_Free((void *)gDE_ATP_L9.shdw.addr);
	OS_Free((void *)gDE_OIF_L9.shdw.addr);
	OS_Free((void *)gDE_CVD_L9.shdw.addr);

	OS_Free((void *)gDE_VDC_L9.shdw.addr);
	OS_Free((void *)gDE_VDD_L9.shdw.addr);
	OS_Free((void *)gDE_IPC_L9.shdw.addr);
	OS_Free((void *)gDE_DVR_L9.shdw.addr);

	OS_Free((void *)gDE_CTOP_L9.shdw.addr);

	if (gDE_DEA_L9.phys.addr) iounmap((void *)gDE_DEA_L9.phys.addr);
	if (gDE_DEB_L9.phys.addr) iounmap((void *)gDE_DEB_L9.phys.addr);
	if (gDE_DEC_L9.phys.addr) iounmap((void *)gDE_DEC_L9.phys.addr);
	if (gDE_DED_L9.phys.addr) iounmap((void *)gDE_DED_L9.phys.addr);
	if (gDE_DEE_L9.phys.addr) iounmap((void *)gDE_DEE_L9.phys.addr);
	if (gDE_DEF_L9.phys.addr) iounmap((void *)gDE_DEF_L9.phys.addr);

	if (gDE_CVA_L9.phys.addr) iounmap((void *)gDE_CVA_L9.phys.addr);
	if (gDE_CVB_L9.phys.addr) iounmap((void *)gDE_CVB_L9.phys.addr);

	if (gDE_DLR_L9.phys.addr) iounmap((void *)gDE_DLR_L9.phys.addr);

	if (gDE_P0L_L9.phys.addr) iounmap((void *)gDE_P0L_L9.phys.addr);
	if (gDE_P0R_L9.phys.addr) iounmap((void *)gDE_P0R_L9.phys.addr);
	if (gDE_P0L_L9B.phys.addr) iounmap((void *)gDE_P0L_L9B.phys.addr);
	if (gDE_P0R_L9B.phys.addr) iounmap((void *)gDE_P0R_L9B.phys.addr);

	if (gDE_MIA_L9.phys.addr) iounmap((void *)gDE_MIA_L9.phys.addr);
	if (gDE_MIB_L9.phys.addr) iounmap((void *)gDE_MIB_L9.phys.addr);
	if (gDE_MIC_L9.phys.addr) iounmap((void *)gDE_MIC_L9.phys.addr);
	if (gDE_MID_L9.phys.addr) iounmap((void *)gDE_MID_L9.phys.addr);
	if (gDE_MIF_L9.phys.addr) iounmap((void *)gDE_MIF_L9.phys.addr);

	if (gDE_MSL_L9.phys.addr) iounmap((void *)gDE_MSL_L9.phys.addr);
	if (gDE_MSR_L9.phys.addr) iounmap((void *)gDE_MSR_L9.phys.addr);

	if (gDE_OVL_L9.phys.addr) iounmap((void *)gDE_OVL_L9.phys.addr);
	if (gDE_OVR_L9.phys.addr) iounmap((void *)gDE_OVR_L9.phys.addr);

	if (gDE_P1L_L9.phys.addr) iounmap((void *)gDE_P1L_L9.phys.addr);
	if (gDE_P1R_L9.phys.addr) iounmap((void *)gDE_P1R_L9.phys.addr);
	if (gDE_P1L_L9B.phys.addr) iounmap((void *)gDE_P1L_L9B.phys.addr);
	if (gDE_P1R_L9B.phys.addr) iounmap((void *)gDE_P1R_L9B.phys.addr);

	if (gDE_SSC_L9.phys.addr) iounmap((void *)gDE_SSC_L9.phys.addr);
	if (gDE_T3D_L9.phys.addr) iounmap((void *)gDE_T3D_L9.phys.addr);
	if (gDE_OSD_L9.phys.addr) iounmap((void *)gDE_OSD_L9.phys.addr);
	//if (gDE_ATP_L9.phys.addr) iounmap((void *)gDE_ATP_L9.phys.addr);
	if (gDE_OIF_L9.phys.addr) iounmap((void *)gDE_OIF_L9.phys.addr);
	if (gDE_CVD_L9.phys.addr) iounmap((void *)gDE_CVD_L9.phys.addr);

	if (gDE_VDC_L9.phys.addr) iounmap((void *)gDE_VDC_L9.phys.addr);
	if (gDE_VDD_L9.phys.addr) iounmap((void *)gDE_VDD_L9.phys.addr);
	if (gDE_IPC_L9.phys.addr) iounmap((void *)gDE_IPC_L9.phys.addr);
	if (gDE_DVR_L9.phys.addr) iounmap((void *)gDE_DVR_L9.phys.addr);

	if (gDE_CTOP_L9.phys.addr) iounmap((void *)gDE_CTOP_L9.phys.addr);
	return RET_OK;
}

 /**
 * @callgraph
 * @callergraph
 *
 * @brief Get Status of Interrupt which is one of either MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param pStatus [OUT] status pointer of Interrupt
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_L9_GetStatusReg(VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
		case VIDEO_DMA_MCU :
		case VIDEO_JPG_MCU :
		case VIDEO_WEL_MCU :
		case VIDEO_WER_MCU :
			DE_IPC_L9_RdFL(int_intr_status);
			*pStatus = DE_IPC_L9_Rd(int_intr_status);
			break;
		case VIDEO_IPC_CPU :
		case VIDEO_DMA_CPU :
		case VIDEO_JPG_CPU :
		case VIDEO_WEL_CPU :
		case VIDEO_WER_CPU :
			DE_IPC_L9_RdFL(ext_intr_status);
			*pStatus = DE_IPC_L9_Rd(ext_intr_status);
			break;
		default :
			BREAK_WRONG(ipcType);
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make inerrupt status for watch dog either happen or clear
 *
 * @param turnOn [IN] determine to turn On or Off
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_WDG_L9_WakeUpReg(BOOLEAN turnOn)
{
	if (turnOn) {
		DE_IPC_L9_FLWf(ext_intr_event, wdg_interrupt_event, 1);
	} else {
		DE_IPC_L9_FLWf(ext_intr_clear, wdg_interrupt_clear, 1);
	}

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make interrupt be happen according to ipcType which is either of MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param turnOn  [IN] maket Interrupt enable or clear
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_L9_WakeUpReg(VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn)
{
	int ret = RET_OK;

	turnOn &= 0x1;
	switch (ipcType) {
		case VIDEO_IPC_MCU :
			if (turnOn) {
				DE_IPC_L9_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_IPC_CPU :
			if (turnOn) {
				DE_IPC_L9_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_MCU :
			if (turnOn) {
				DE_IPC_L9_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_CPU :
			if (turnOn) {
				DE_IPC_L9_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_MCU :
			if (turnOn) {
				DE_IPC_L9_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_CPU :
			if (turnOn) {
				DE_IPC_L9_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_MCU :
			if (turnOn) {
				DE_IPC_L9_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_CPU :
			if (turnOn) {
				DE_IPC_L9_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_MCU :
			if (turnOn) {
				DE_IPC_L9_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_CPU :
			if (turnOn) {
				DE_IPC_L9_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_MCU :
			if (turnOn) {
				DE_IPC_L9_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_CPU :
			if (turnOn) {
				DE_IPC_L9_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_L9_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		default :
			BREAK_WRONG(ipcType);
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param addr [IN] accessing for register
 * @param value [IN] acccesing for register
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_WD(UINT32 addr, UINT32 value)
{
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 currValue;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	UINT32 virtAddr = 0;

	do {
		recvAddr = addr;
		if		(recvAddr <= 0x6000) recvAddr += DTVSOC_DE_L9_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_DE_L9_BASE;
		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;

		virtAddr = (UINT32)ioremap(currAddr, 0x8);
		if (currAddr == recvAddr) {
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(virtAddr);
		nextValue = REG_RD((virtAddr+4));

		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);

		currValue  = GET_BITS(currValue ,0	  ,dBit);
		currValue += GET_PVAL(value		,dBit ,wBit);

		nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
		nextValue += GET_BITS(value		,0	  ,dBit);
		REG_WD(virtAddr		,currValue);
		REG_WD((virtAddr+4) ,nextValue);
	} while (0);
	if (virtAddr) iounmap((void *)virtAddr);

		return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param addr [IN] accessing for register
 *
 * @return value of register
 */
UINT32 DE_REG_L9_RD(UINT32 addr)
{
	UINT32 value;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	UINT32 virtAddr = 0;

	do {
		recvAddr = addr;
		if		(recvAddr <= 0x6000) recvAddr += DTVSOC_DE_L9_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_DE_L9_BASE;

		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;
		virtAddr = (UINT32)ioremap(currAddr, 0x8);

		value = REG_RD(virtAddr);
		if (currAddr == recvAddr) break;

		nextValue = REG_RD(virtAddr+4);
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		value  = GET_BITS(value, dBit, wBit);
		value += GET_PVAL(nextValue, wBit, dBit);
	} while (0);
	if (virtAddr) iounmap((void *)virtAddr);
	//ffprintk("Reg[0x%08x] = 0x%08x\n", addr, value);

	return value;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetFrRate(DE_DPLL_CLK_T dclk)
{
	int ret = RET_OK;
#ifdef USE_CTOP_CODES_FOR_L9
	DE_DPLL_DIV_T *pDisplayPll = NULL;
	int i;

	do {
		DE_REG_L9_SetPwmFreerun();

		for (i=0;i<ARRAY_SIZE(sDisplayPll_L9);i++) {
			if (sDisplayPll_L9[i].clk != dclk) continue;
			pDisplayPll =  &sDisplayPll_L9[i].div;
			break;
		}
		CHECK_KNULL(pDisplayPll);

		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
			CTOP_CTRL_L9B_RdFL(ctr62_display_pll_ctrl);
			CTOP_CTRL_L9B_RdFL(ctr63_display_pll_ctrl);

			CTOP_CTRL_L9B_Wr01(ctr62_display_pll_ctrl, disp_od_fout_ctrl, pDisplayPll->dpllOd);
			CTOP_CTRL_L9B_Wr01(ctr63_display_pll_ctrl, disp_nsc_ctrl,	  pDisplayPll->dpllN);

			CTOP_CTRL_L9B_WrFL(ctr62_display_pll_ctrl);
			CTOP_CTRL_L9B_WrFL(ctr63_display_pll_ctrl);
		} else {
			CTOP_CTRL_L9A_RdFL(ctr62);
			CTOP_CTRL_L9A_RdFL(ctr63);

			CTOP_CTRL_L9A_Wr01(ctr62, disp_od_fout_ctrl, pDisplayPll->dpllOd);
			CTOP_CTRL_L9A_Wr01(ctr63, disp_nsc_ctrl,	 pDisplayPll->dpllN);

			CTOP_CTRL_L9A_WrFL(ctr62);
			CTOP_CTRL_L9A_WrFL(ctr63);
		}
	} while (0);
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get Frame rate of Display
 *
 * @param pFrRate [OUT] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_GetFrRate(LX_DE_FR_RATE_T *pstParams)
{
	int ret = RET_OK;

	pstParams->isForceFreeRun = FALSE;
	pstParams->fr_rate = 30;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set background color (non-active region color).
 *
 * @param [IN] structure pointer to carry infomation about non-active region color
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetBgColor(LX_DE_COLOR_T *pBackColor)
{
	int ret = RET_OK;

	DE_OVL_L9_RdFL(ov_ctrl2);

	pBackColor->r >>= 4;
	pBackColor->b >>= 4;
	DE_OVL_L9_Wr01(ov_ctrl2, back_color_cr, pBackColor->r);
	DE_OVL_L9_Wr01(ov_ctrl2, back_color_cb, pBackColor->b);
	DE_OVL_L9_Wr01(ov_ctrl2, back_color_yy, pBackColor->g);

	DE_OVL_L9_WrFL(ov_ctrl2);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set blank color of selected window
 *
 * @param pWinBlank [IN] structure pointer to carry information about window Id, whether Turn On or Off and blank color
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank)
{
	int ret = RET_OK;

	do {
		DE_OVL_L9_RdFL(ov_ctrl4);
		switch (pWinBlank->win_id) {
			case LX_DE_WIN_MAIN :
				DE_OVL_L9_Wr01(ov_ctrl4, w0_dark_en, pWinBlank->bEnable);
				break;
			case LX_DE_WIN_SUB :
				DE_OVL_L9_Wr01(ov_ctrl4, w1_dark_en, pWinBlank->bEnable);
				break;
			default :
				BREAK_WRONG(pWinBlank->win_id);
		}
		if (ret) break;
		DE_OVL_L9_WrFL(ov_ctrl4);

		pWinBlank->win_color.r >>= 4;
		pWinBlank->win_color.b >>= 4;
		DE_OVL_L9_RdFL(ov_ctrl2);
		DE_OVL_L9_Wr01(ov_ctrl2, dark_color_cr, pWinBlank->win_color.r);
		DE_OVL_L9_Wr01(ov_ctrl2, dark_color_cb, pWinBlank->win_color.b);
		DE_OVL_L9_Wr01(ov_ctrl2, dark_color_yy, pWinBlank->win_color.g);
		DE_OVL_L9_WrFL(ov_ctrl2);
	} while (0);

	return ret;
}

BOOLEAN DE_REG_L9_CheckIrq4Vsync(void)
{
	int ret;
	//DE_FUNC_INTR	de_func_intr;
	//DE1A_INTR_REG de1a_intr_reg;
	L9A0_DEC_DE_INTR_FLAG_CPU_T			dec_de_intr_flag_cpu;				 // 0x4004
	L9A0_DEB_INTR_REG_T					deb_intr_reg;						 // 0x1080
	UINT32 videoIntrDe;
	BOOLEAN vsyncIrq;

	do {
		vsyncIrq = 0;
		ret = DE_REG_L9_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_FUNC, &videoIntrDe);
		if (ret) break;

		dec_de_intr_flag_cpu  = *(L9A0_DEC_DE_INTR_FLAG_CPU_T  *)&videoIntrDe;
		if (!dec_de_intr_flag_cpu.deb_dec_intr_cpu) break;
		ret = DE_REG_L9_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_DEB, &videoIntrDe);
		if (ret) break;

		deb_intr_reg = *(L9A0_DEB_INTR_REG_T *)&videoIntrDe;
		if (!deb_intr_reg.disp_intr_for_cpu) break;
		vsyncIrq = 1;
	} while (0);

	return vsyncIrq;
}

int DE_REG_L9_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus)
{
	int ret = RET_OK;
	UINT32 intrReg;
	UINT32 intrMux;

	do {
		CHECK_KNULL(pVideoIrqStatus);
		switch (intrType) {
			case VIDEO_INTR_TYPE_DEA :
				DE_DEA_L9_RdFL(dea_intr_reg);
				DE_DEA_L9_WrFL(dea_intr_reg);
				*pVideoIrqStatus = DE_DEA_L9_Rd(dea_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DEB :
				DE_DEB_L9_RdFL(deb_intr_reg);
				DE_DEB_L9_RdFL(deb_intr_mux);
				intrReg = DE_DEB_L9_Rd(deb_intr_reg);
				intrMux = DE_DEB_L9_Rd(deb_intr_mux);
#ifdef USE_LINUX_KERNEL
				intrReg &=	intrMux;
#else
				intrReg &= ~intrMux;
#endif
				DE_DEB_L9_Wr(deb_intr_reg, intrReg);
				DE_DEB_L9_WrFL(deb_intr_reg);
				*pVideoIrqStatus = DE_DEB_L9_Rd(deb_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DEC :
				DE_DEC_L9_RdFL(dec_intr_reg);
				DE_DEC_L9_WrFL(dec_intr_reg);
				*pVideoIrqStatus = DE_DEC_L9_Rd(dec_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DED :
				DE_DED_L9_RdFL(ded_intr_reg);
				DE_DED_L9_WrFL(ded_intr_reg);
				*pVideoIrqStatus = DE_DED_L9_Rd(ded_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DEE :
				DE_DEE_L9_RdFL(dee_intr_reg);
				DE_DEE_L9_WrFL(dee_intr_reg);
				*pVideoIrqStatus = DE_DEE_L9_Rd(dee_intr_reg);
				break;
			case VIDEO_INTR_TYPE_FUNC :
				DE_DEE_L9_RdFL(dec_de_intr_flag_cpu);
				*pVideoIrqStatus = DE_DEE_L9_Rd(dec_de_intr_flag_cpu);
				break;
			default :
				BREAK_WRONG(intrType);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief grab video pixels of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_GrabPixel(LX_DE_GRAB_PIXEL_T *pstParams)
{
	int ret = RET_OK;
	UINT8  *pFrameAddrY8 = NULL;
	UINT8  *pFrameAddrC8 = NULL;
	UINT8  *pFrameAddrY2 = NULL;
	UINT8  *pFrameAddrC2 = NULL;
	UINT16 phyFrameAddrY8;
	UINT16 phyFrameAddrC8;
	UINT16 phyFrameAddrY2;
	UINT16 phyFrameAddrC2;

	UINT32 grabX;
	UINT32 grabY;
	UINT32 grabW;
	UINT32 grabH;
	UINT32 frameW;
	UINT32 frameH;
	UINT32 offsetY;
	UINT32 offsetC;
	UINT32 startY;
	UINT32 pixelG8;
	UINT32 pixelB8;
	UINT32 pixelR8;
	UINT32 pixelG2;
	UINT32 pixelB2;
	UINT32 pixelR2;
	UINT8  pixelY2;
	UINT8  pixelC2;
	UINT32 x;
	UINT32 y;
	UINT32 posY;
	UINT32 posC;
	UINT32 divY;
	UINT32 remY;
	UINT32 divC;
	UINT32 remC;
	UINT32 framSize;
	UINT32 grabSize;
	UINT32 bankPrewY;
	UINT32 bankPrewC;
	UINT32 smuxSample;
	UINT8 colorDepth;

	do {
		CHECK_KNULL(pstParams);

		phyFrameAddrY8 = GET_BITS(pstParams->region.realPixelGrabW ,16 ,16);
		phyFrameAddrY2 = GET_BITS(pstParams->region.realPixelGrabW ,0  ,16);
		phyFrameAddrC8 = GET_BITS(pstParams->region.realPixelGrabH ,16 ,16);
		phyFrameAddrC2 = GET_BITS(pstParams->region.realPixelGrabH ,0  ,16);

		grabW		   = GET_BITS(pstParams->region.pixelGrabW	   ,16 ,16);
		grabH		   = GET_BITS(pstParams->region.pixelGrabW	   ,0  ,16);
		grabX		   = GET_BITS(pstParams->region.pixelGrabH	   ,16 ,16);
		grabY		   = GET_BITS(pstParams->region.pixelGrabH	   ,0  ,16);
		frameW		   = GET_BITS(pstParams->region.pixelGrabX	   ,16 ,16);
		frameH		   = GET_BITS(pstParams->region.pixelGrabX	   ,0  ,16);

		smuxSample	   = GET_BITS(pstParams->region.pixelGrabY	   ,12 ,4);
		bankPrewY	   = GET_BITS(pstParams->region.colorSpace	   ,4  ,4);
		bankPrewC	   = GET_BITS(pstParams->region.colorSpace	   ,0  ,4);
		colorDepth	   = pstParams->region.colorDepth;

		grabSize  = grabW  * grabH;
		framSize  = frameW * frameH;
		if (!grabSize) break;
		if (!framSize) break;

		pFrameAddrY8 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrY8), framSize);
		pFrameAddrC8 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrC8), framSize*smuxSample);
		pFrameAddrY2 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrY2), framSize/4);
		pFrameAddrC2 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrC2), framSize/4*smuxSample);

		pixelG8  = 0;
		pixelB8  = 0;
		pixelR8  = 0;
		pixelG2  = 0;
		pixelB2  = 0;
		pixelR2  = 0;
		grabSize = 0;
		offsetY  = bankPrewY * frameW;
		offsetC  = bankPrewC * frameW;
		for (y=0;y<grabH;y++) {
			startY = (grabY + y) * frameW + grabX;
			for (x=0;x<grabW;x++) {
				grabSize++;
				posY	 = offsetY + (startY + x);
				posC	 = offsetC + (startY + x) * smuxSample;
				posC	&= ~0x1;
				pixelG8 += pFrameAddrY8[posY+0];
				pixelB8 += pFrameAddrC8[posC+0];
				pixelR8 += pFrameAddrC8[posC+1];

				if (10 != colorDepth) continue;
				divY = posY/4;
				remY = posY%4;
				divC = posC/4;
				remC = posC%4;
				pixelY2  = pFrameAddrY2[divY];
				pixelC2  = pFrameAddrC2[divC];
				pixelG2 += GET_BITS(pixelY2, (remY+0)*2, 2);
				pixelB2 += GET_BITS(pixelC2, (remC+0)*2, 2);
				pixelR2 += GET_BITS(pixelC2, (remC+1)*2, 2);
			}
		}
		if (!grabSize) BREAK_WRONG(grabSize);
		pixelG8  /= grabSize;
		pixelB8  /= grabSize;
		pixelR8  /= grabSize;
		pixelG2  /= grabSize;
		pixelB2  /= grabSize;
		pixelR2  /= grabSize;
		pixelG8 <<= 2;
		pixelB8 <<= 2;
		pixelR8 <<= 2;

		pstParams->color.pixelGrabY		 = pixelG8 + pixelG2;
		pstParams->color.pixelGrabCb	 = pixelB8 + pixelB2;
		pstParams->color.pixelGrabCr	 = pixelR8 + pixelR2;
		pstParams->region.realPixelGrabW = grabW;
		pstParams->region.realPixelGrabH = grabH;
		pstParams->region.colorSpace	 = 0;
	} while (0);

	if(pFrameAddrY8) iounmap(pFrameAddrY8);
	if(pFrameAddrC8) iounmap(pFrameAddrC8);
	if(pFrameAddrY2) iounmap(pFrameAddrY2);
	if(pFrameAddrC2) iounmap(pFrameAddrC2);

	return ret;
}
/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_GRAB_COLOR_T *pFrameColor = NULL;
	UINT8  *pFrameAddrY8 = NULL;
	UINT8  *pFrameAddrC8 = NULL;
	UINT8  *pFrameAddrY2 = NULL;
	UINT8  *pFrameAddrC2 = NULL;
	UINT16 phyFrameAddrY8;
	UINT16 phyFrameAddrC8;
	UINT16 phyFrameAddrY2;
	UINT16 phyFrameAddrC2;

	UINT32 grabX;
	UINT32 grabY;
	UINT32 grabW;
	UINT32 grabH;
	UINT32 frameW;
	UINT32 frameH;
	UINT32 offsetY;
	UINT32 offsetC;
	UINT32 startY;
	UINT32 pixelG8;
	UINT32 pixelB8;
	UINT32 pixelR8;
	UINT32 pixelG2;
	UINT32 pixelB2;
	UINT32 pixelR2;
	UINT8  pixelY2;
	UINT8  pixelC2;
	UINT32 x;
	UINT32 y;
	UINT32 posY;
	UINT32 posC;
	UINT32 divY;
	UINT32 remY;
	UINT32 divC;
	UINT32 remC;
	UINT32 framSize;
	UINT32 grabSize;
	UINT32 grabStepW;
	UINT32 bankPrewY;
	UINT32 bankPrewC;
	UINT32 smuxSample;
	UINT8 colorDepth;

	do {
		CHECK_KNULL(pstParams);

		phyFrameAddrY8 = GET_BITS(pstParams->region.realPixelGrabW ,16 ,16);
		phyFrameAddrY2 = GET_BITS(pstParams->region.realPixelGrabW ,0  ,16);
		phyFrameAddrC8 = GET_BITS(pstParams->region.realPixelGrabH ,16 ,16);
		phyFrameAddrC2 = GET_BITS(pstParams->region.realPixelGrabH ,0  ,16);

		grabW		   = GET_BITS(pstParams->region.pixelGrabW	   ,16 ,16);
		grabH		   = GET_BITS(pstParams->region.pixelGrabW	   ,0  ,16);
		grabX		   = GET_BITS(pstParams->region.pixelGrabH	   ,16 ,16);
		grabY		   = GET_BITS(pstParams->region.pixelGrabH	   ,0  ,16);
		frameW		   = GET_BITS(pstParams->region.pixelGrabX	   ,16 ,16);
		frameH		   = GET_BITS(pstParams->region.pixelGrabX	   ,0  ,16);

		smuxSample	   = GET_BITS(pstParams->region.pixelGrabY	   ,12 ,4);
		bankPrewY	   = GET_BITS(pstParams->region.colorSpace	   ,4  ,4);
		bankPrewC	   = GET_BITS(pstParams->region.colorSpace	   ,0  ,4);
		grabStepW	   = GET_BITS(pstParams->bReadOnOff			   ,16 ,16);
		colorDepth	   = pstParams->region.colorDepth;

		grabSize = grabW  * grabH;
		framSize = frameW * frameH;
		if (!grabSize) break;
		if (!framSize) break;

		pFrameAddrY8 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrY8), framSize);
		pFrameAddrC8 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrC8), framSize*smuxSample);
		pFrameAddrY2 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrY2), framSize/4);
		pFrameAddrC2 = (UINT8 *)ioremap(VIDEO_L9_ROW2PHY(phyFrameAddrC2), framSize/4*smuxSample);

		grabSize = 0;
		offsetY  = bankPrewY * frameW;
		offsetC  = bankPrewC * frameW;
		for (y=0;y<grabH;y++) {
			startY = (grabY + y) * frameW + grabX;
			grabSize = y * grabStepW;
			for (x=0;x<grabW;x++) {
				pFrameColor = &pstParams->color[grabSize+x];
				posY  = offsetY + (startY + x);
				posC  = offsetC + (startY + x) * smuxSample;
				posC &= ~0x1;
				if (GET_BITS(pstParams->bReadOnOff,0,1)) {
					pixelG8 = pFrameAddrY8[posY+0];
					pixelB8 = pFrameAddrC8[posC+0];
					pixelR8 = pFrameAddrC8[posC+1];
					pFrameColor->pixelGrabY  = GET_SVAL(pixelG8, 0,8,2);
					pFrameColor->pixelGrabCb = GET_SVAL(pixelB8, 0,8,2);
					pFrameColor->pixelGrabCr = GET_SVAL(pixelR8, 0,8,2);
				} else {
					pixelG8 = GET_BITS(pFrameColor->pixelGrabY	,2,8);
					pixelB8 = GET_BITS(pFrameColor->pixelGrabCb ,2,8);
					pixelR8 = GET_BITS(pFrameColor->pixelGrabCr ,2,8);
					pFrameAddrY8[posY+0] = pixelG8;
					pFrameAddrC8[posC+0] = pixelB8;
					pFrameAddrC8[posC+1] = pixelR8;
				}

				if (!colorDepth) continue;
				divY = posY/4;
				remY = posY%4;
				divC = posC/4;
				remC = posC%4;

				if (GET_BITS(pstParams->bReadOnOff,0,1)) {
					pixelY2 = pFrameAddrY2[divY];
					pixelC2 = pFrameAddrC2[divC];
					pixelG2 = GET_BITS(pixelY2, (remY+0)*2, 2);
					pixelB2 = GET_BITS(pixelC2, (remC+0)*2, 2);
					pixelR2 = GET_BITS(pixelC2, (remC+1)*2, 2);

					pFrameColor->pixelGrabY  |= GET_SVAL(pixelG2, 0,2,0);
					pFrameColor->pixelGrabCb |= GET_SVAL(pixelB2, 0,2,0);
					pFrameColor->pixelGrabCr |= GET_SVAL(pixelR2, 0,2,0);
				} else {
					pixelG2 = GET_BITS(pFrameColor->pixelGrabY	,0,2);
					pixelB2 = GET_BITS(pFrameColor->pixelGrabCb ,0,2);
					pixelR2 = GET_BITS(pFrameColor->pixelGrabCr ,0,2);

					pixelY2 = pFrameAddrY2[divY];
					pixelC2 = pFrameAddrC2[divC];
					pixelY2 |= GET_SVAL(pixelG2, 0, 2, (remY+0)*2);
					pixelC2 |= GET_SVAL(pixelB2, 0, 2, (remC+0)*2);
					pixelC2 |= GET_SVAL(pixelR2, 0, 2, (remC+1)*2);
					pFrameAddrY2[divY] = pixelY2;
					pFrameAddrC2[divC] = pixelC2;
				}
			}
		}
		pstParams->region.realPixelGrabW = grabW;
		pstParams->region.realPixelGrabH = grabH;
		pstParams->region.colorSpace	 = 0;
	} while (0);

	if(pFrameAddrY8) iounmap(pFrameAddrY8);
	if(pFrameAddrC8) iounmap(pFrameAddrC8);
	if(pFrameAddrY2) iounmap(pFrameAddrY2);
	if(pFrameAddrC2) iounmap(pFrameAddrC2);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetInputSrc(LX_DE_SET_INPUT_T *pstParams)
{
#ifdef	USE_CTOP_CODES_FOR_L9
#ifdef	USE_DE_SETTING_SDEC_CLK_FROM_MVI
	static LX_DE_INPUT_SRC_T inputSrc_Chk = 0xff;
	UINT32 reg;

	do {
		if (LX_DE_WIN_MAIN != pstParams->win_id) break;
		if (inputSrc_Chk == pstParams->inputSrc) break;
		inputSrc_Chk = pstParams->inputSrc;
		switch (pstParams->inputSrc) {
			case LX_DE_SRC_MVI :
			case LX_DE_SRC_CPU :
				reg = 1;
				break;
			case LX_DE_SRC_CVI :
			default :
				reg = 0;
				break;
		}
		CTOP_CTRL_L9_RdFL(ctr27);
		CTOP_CTRL_L9_Wr01(ctr27, dco_sel, reg); //setting disp clock from SDEC
		CTOP_CTRL_L9_WrFL(ctr27);
	} while (0);
#endif
#endif
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set information which is comming from CVI port
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams)
{
	int ret = RET_OK;
	UINT32 cviSampling = 0;
	UINT32 xsize_divide = 0;

	do {
		CHECK_KNULL(pstParams);
		memcpy(&sCviSrcType, pstParams, sizeof(LX_DE_CVI_SRC_TYPE_T));
		switch (pstParams->sampling) {
			case LX_DE_CVI_NORMAL_SAMPLING :
				cviSampling = 0;
				xsize_divide = 0;
				break;
			case LX_DE_CVI_DOUBLE_SAMPLING :
				cviSampling = 1;
				xsize_divide = 1;
				break;
			case LX_DE_CVI_QUAD_SAMPLING :
				cviSampling  = 3;
				xsize_divide = 2;
				break;
			default :
				BREAK_WRONG(pstParams->sampling);
		}
		if (ret) break;

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
					CTOP_CTRL_L9B_RdFL(ctr26_extclk_div_sel);
					CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, msclk_sel, xsize_divide);
					CTOP_CTRL_L9B_WrFL(ctr26_extclk_div_sel);
#ifndef USE_DE_CVI_ACCESS_REGISTER_ON_MCU_PART
					DE_CVA_L9B_RdFL(cva_dig_filt_ctrl3);
					DE_CVA_L9B_RdFL(cva_misc_ctrl);
					DE_CVA_L9B_Wr01(cva_dig_filt_ctrl3, fir_en,		(!cviSampling)?0:1);
					DE_CVA_L9B_WfCM(cva_dig_filt_ctrl3, fir_y_en,	  cviSampling, 0x1);
					//DE_CVA_L9B_WfCM(cva_dig_filt_ctrl3, fir_c_en,   cviSampling, 0x1); // control in DE_REG_L9_SetCviCsampleMode()
					DE_CVA_L9B_Wr01(cva_dig_filt_ctrl3, fir_sampling_rate, cviSampling);
					DE_CVA_L9B_Wr01(cva_misc_ctrl, xsize_divide, xsize_divide);
					DE_CVA_L9B_WrFL(cva_dig_filt_ctrl3);
					DE_CVA_L9B_WrFL(cva_misc_ctrl);
#endif
				} else {
					CTOP_CTRL_L9A_RdFL(ctr26);
					CTOP_CTRL_L9A_Wr01(ctr26, msclk_sel, cviSampling);
					CTOP_CTRL_L9A_WrFL(ctr26);
					DE_CVA_L9A_RdFL(cva_dig_filt_ctrl3);
					DE_CVA_L9A_WfCM(cva_dig_filt_ctrl3, fir_sample_en,	   cviSampling, 0x1);
					DE_CVA_L9A_Wr01(cva_dig_filt_ctrl3, fir_sampling_rate, cviSampling);
					DE_CVA_L9A_WrFL(cva_dig_filt_ctrl3);
				}
				break;
			case LX_DE_CVI_CH_B :
				if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
					CTOP_CTRL_L9B_RdFL(ctr26_extclk_div_sel);
					CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, ssclk_sel, xsize_divide);
					CTOP_CTRL_L9B_WrFL(ctr26_extclk_div_sel);
#ifndef USE_DE_CVI_ACCESS_REGISTER_ON_MCU_PART
					DE_CVB_L9B_RdFL(cvb_dig_filt_ctrl3);
					DE_CVB_L9B_RdFL(cvb_misc_ctrl);
					DE_CVB_L9B_Wr01(cvb_dig_filt_ctrl3, fir_en,		(!cviSampling)?0:1);
					DE_CVB_L9B_WfCM(cvb_dig_filt_ctrl3, fir_y_en,	  cviSampling, 0x1);
					//DE_CVB_L9B_WfCM(cvb_dig_filt_ctrl3, fir_c_en,		cviSampling, 0x1); // control in DE_REG_L9_SetCviCsampleMode()
					DE_CVB_L9B_Wr01(cvb_dig_filt_ctrl3, fir_sampling_rate, cviSampling);
					DE_CVB_L9B_Wr01(cvb_misc_ctrl, xsize_divide, xsize_divide);
					DE_CVB_L9B_WrFL(cvb_dig_filt_ctrl3);
					DE_CVB_L9B_WrFL(cvb_misc_ctrl);
#endif
				} else {
					CTOP_CTRL_L9A_RdFL(ctr26);
					CTOP_CTRL_L9A_Wr01(ctr26, ssclk_sel, cviSampling);
					CTOP_CTRL_L9A_WrFL(ctr26);
					DE_CVB_L9A_RdFL(cvb_dig_filt_ctrl3);
					DE_CVB_L9A_WfCM(cvb_dig_filt_ctrl3, fir_sample_en,	   cviSampling, 0x1);
					DE_CVB_L9A_Wr01(cvb_dig_filt_ctrl3, fir_sampling_rate, cviSampling);
					DE_CVB_L9A_WrFL(cvb_dig_filt_ctrl3);
				}
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_Init(LX_DE_PANEL_TYPE_T *pstParams)
{
	DE_REG_L9_InitAddrSwitch();
	DE_PWM_Init();

	//DE_REG_L9_OIF_InitLvdsIfCtrl();

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get color space conversion matrix and offset for each external source information.
 *
 * @param [IN] structure pointer to carry infomation about non-active region color
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_GetCviCsc(LX_DE_CVI_CSC_T *pstParams)
{
	int ret = RET_OK;
	DE_PARAM_TYPE_T tableId = DE_CVM_CSC_COEF;
	UINT32 *cscTable = NULL;
	UINT32 matrixArraySize, offsetArraySize, tableArraySize;
	UINT32 inx = 0;
	int i;

	do {
		CHECK_KNULL(pstParams);
		matrixArraySize = ARRAY_SIZE(pstParams->CSC_matrix);
		offsetArraySize = ARRAY_SIZE(pstParams->CSC_offset);
		tableArraySize	= matrixArraySize + offsetArraySize;
		cscTable = OS_Malloc(sizeof(UINT32)*tableArraySize);
		CHECK_KNULL(cscTable);

		memset(cscTable, 0, (sizeof(UINT32)*tableArraySize));

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				tableId = DE_CVM_CSC_COEF;
				break;
			case LX_DE_CVI_CH_B :
				tableId = DE_CVS_CSC_COEF;
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
		ret = DE_PRM_L9_LoadTable(tableId, DE_PARAM_READ, pstParams->isEnable, cscTable, tableArraySize);
		if (ret) break;

		for (i=0;i<matrixArraySize;i++) pstParams->CSC_matrix[i] = cscTable[inx++];
		for (i=0;i<offsetArraySize;i++) pstParams->CSC_offset[i] = cscTable[inx++];
	} while (0);
	OS_Free(cscTable);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix and offset for each external source information.
 *
 * @param [IN] structure pointer to carry infomation about non-active region color
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetCviCsc(LX_DE_CVI_CSC_T *pstParams)
{
	int ret = RET_OK;
	DE_PARAM_TYPE_T tableId;
	UINT32 cscTable[ARRAY_SIZE(pstParams->CSC_matrix) + ARRAY_SIZE(pstParams->CSC_offset)];
	UINT32 inx = 0;
	int i;

	do {
		CHECK_KNULL(pstParams);
		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				tableId = DE_CVM_CSC_COEF;
				break;
			case LX_DE_CVI_CH_B :
				tableId = DE_CVS_CSC_COEF;
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
		for (i=0;i<ARRAY_SIZE(pstParams->CSC_matrix);i++) cscTable[inx++] = pstParams->CSC_matrix[i];
		for (i=0;i<ARRAY_SIZE(pstParams->CSC_offset);i++) cscTable[inx++] = pstParams->CSC_offset[i];

#ifdef USE_PARM_CODES_FOR_L9
		ret = DE_PRM_L9_LoadTable(tableId, DE_PARAM_WRITE, pstParams->isEnable, cscTable, ARRAY_SIZE(cscTable));
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get color space conversion matrix for post processing block
 *
 * @param [IN] structure pointer to carry infomation about non-active region color
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_GetPostCsc(LX_DE_POST_CSC_T *pstParams)
{
	int ret = RET_OK;
	UINT32 *cscTable = NULL;
	UINT32 matrixArraySize, offsetArraySize, tableArraySize;
	UINT32 inx = 0;
	int i;

	do {
		CHECK_KNULL(pstParams);
		matrixArraySize = ARRAY_SIZE(pstParams->CSC_matrix);
		offsetArraySize = ARRAY_SIZE(pstParams->CSC_offset);
		tableArraySize	= matrixArraySize + offsetArraySize;
		cscTable = OS_Malloc(sizeof(UINT32)*tableArraySize);
		CHECK_KNULL(cscTable);

		memset(cscTable, 0, (sizeof(UINT32)*tableArraySize));

		ret = DE_PRM_L9_LoadTable(DE_POST_CSC_COEF, DE_PARAM_READ, 0, cscTable, tableArraySize);
		if (ret) break;

		for (i=0;i<matrixArraySize;i++) pstParams->CSC_matrix[i] = cscTable[inx++];
		for (i=0;i<offsetArraySize;i++) pstParams->CSC_offset[i] = cscTable[inx++];
	} while (0);
	OS_Free(cscTable);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix for post processing block
 *
 * @param [IN] structure pointer to carry infomation about non-active region color
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetPostCsc(LX_DE_POST_CSC_T *pstParams)
{
	int ret = RET_OK;
	DE_PARAM_TYPE_T tableId;
	UINT32 cscTable[ARRAY_SIZE(pstParams->CSC_matrix) + ARRAY_SIZE(pstParams->CSC_offset)];
	UINT32 inx = 0;
	int i;

	do {
		CHECK_KNULL(pstParams);
#if 0 // to do for multi window
		switch (pstParams->win_id) {
			case LX_DE_WIN_MAIN :
				tableId = DE_POST_CSC_COEF;
				break;
			case LX_DE_WIN_SUB :
				tableId = DE_POST_CSC_COEF;  // 이부분 변경 필요
				break;
			default :
				BREAK_WRONG(pstParams->win_id);
		}
		if (ret) break;
#else
		tableId = DE_POST_CSC_COEF;
#endif
		for (i=0;i<ARRAY_SIZE(pstParams->CSC_matrix);i++) cscTable[inx++] = pstParams->CSC_matrix[i];
		for (i=0;i<ARRAY_SIZE(pstParams->CSC_offset);i++) cscTable[inx++] = pstParams->CSC_offset[i];

#ifdef USE_PARM_CODES_FOR_L9
		ret = DE_PRM_L9_LoadTable(tableId, DE_PARAM_WRITE, 0, cscTable, ARRAY_SIZE(cscTable));
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get MVI source colorimetry information.
 *
 * @param [OUT] structure pointer to carry infomation about mvi colorimetry
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_GetMviColorimetry(LX_DE_MVI_COLORIMETRY_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS spread spectrum for 60Hz mode (PDP).
 *
 * @param [OUT] structure pointer to carry information about spread spectrum period, duty, enable.
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetSpread(LX_DE_SET_SPREAD_T *pstParams)
{
	UINT16 msex[11][8] = {	{0, 0,	  0,	0,	 0,   0,   0,	0},		 // modulation speed = 0 KHz
							{0, 449,  269,	192, 149, 149, 122, 103},	 //  modulation speed = 10	KHz
							{0, 224,  134,	95,  74,  74,  60,	51},	 //  modulation speed = 20	KHz
							{0, 149,  89,	63,  49,  49,  40,	34},	 //  modulation speed = 30	KHz
							{0, 112,  67,	47,  37,  37,  30,	25},	 //  modulation speed = 40	KHz
							{0, 89,   53,	38,  29,  29,  24,	20},	 //  modulation speed = 50	KHz
							{0, 74,   44,	31,  24,  24,  19,	16},	 //  modulation speed = 60	KHz
							{0, 63,   38,	27,  20,  20,  17,	14},	 //  modulation speed = 70	KHz
							{0, 55,   33,	23,  18,  18,  14,	12},	 //  modulation speed = 80	KHz
							{0, 49,   29,	20,  16,  16,  13,	11},	 //  modulation speed = 90	KHz
							{0, 44,   26,	18,  14,  14,  11,	9}};	 //  modulation speed = 100 KHz
	UINT8 udex[8] = {0, 1, 2, 3, 4, 4, 5, 6};
#ifdef	USE_CTOP_CHECK_LATER
	UINT8 sr[8]   = {0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
	UINT8 ms[4]   = {0, 1, 4, 7};
#endif
	int idxPeriod;
	int idxPercent;
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		if (pstParams->bEnable)
		{
			if (pstParams->percent >= 200)//0.2%
				idxPercent = 7;
			else if (pstParams->percent >= 175)//1.75%
				idxPercent = 6;
			else if (pstParams->percent >= 150)//1.5%
				idxPercent = 5;
			else if (pstParams->percent >= 125)//1.25%
				idxPercent = 4;
			else if (pstParams->percent >= 100)//1.00%
				idxPercent = 3;
			else if (pstParams->percent >= 75)//0.75%
				idxPercent = 2;
			else if (pstParams->percent >= 50)//0.5%
				idxPercent = 1;
			else
				idxPercent = 0;//0%

			if (pstParams->period >= 100)		//	modulation speed = 100 KHz
				idxPeriod = 10;
			else if (pstParams->period >= 90)	//	modulation speed = 90 KHz
				idxPeriod = 9;
			else if (pstParams->period >= 80)	//	modulation speed = 80 KHz
				idxPeriod = 8;
			else if (pstParams->period >= 70)	//	modulation speed = 70 KHz
				idxPeriod = 7;
			else if (pstParams->period >= 60)	//	modulation speed = 60 KHz
				idxPeriod = 6;
			else if (pstParams->period >= 50)	//	modulation speed = 50 KHz
				idxPeriod = 5;
			else if (pstParams->period >= 40)	//	modulation speed = 40 KHz
				idxPeriod = 4;
			else if (pstParams->period >= 30)	//	modulation speed = 30 KHz
				idxPeriod = 3;
			else if (pstParams->period >= 20)	//	modulation speed = 20 KHz
				idxPeriod = 2;
			else if (pstParams->period >= 10)	//	modulation speed = 10 KHz
				idxPeriod = 1;
			else
				idxPeriod = 0;

		}
		else {
			idxPeriod = 0;
			idxPercent = 0;
		}

		switch (pstParams->type)
		{
			case LX_DE_SPREAD_SPECTRUM_MAIN :
				{
					if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
						CTOP_CTRL_L9B_RdFL(ctr67_main2_syspll_ctrl);
						CTOP_CTRL_L9B_RdFL(ctr69_main2_syspll_ctrl);
#if 1 // macro CTOP_CTRL_L9B_WfCM does not working ...
						CTOP_CTRL_L9B_Wr01(ctr67_main2_syspll_ctrl, m2_dr3p_cih_ctrl, 1);
						CTOP_CTRL_L9B_Wr01(ctr69_main2_syspll_ctrl, m1_dr3p_cih_ctrl, 1);
						CTOP_CTRL_L9B_Wr01(ctr67_main2_syspll_ctrl, m2_dr3p_lf_ctrl, 1);
						CTOP_CTRL_L9B_Wr01(ctr69_main2_syspll_ctrl, m1_dr3p_lf_ctrl, 1);
						CTOP_CTRL_L9B_Wr01(ctr67_main2_syspll_ctrl, m2_dr3p_msex_ctrl, msex[idxPeriod][idxPercent]);
						CTOP_CTRL_L9B_Wr01(ctr69_main2_syspll_ctrl, m1_dr3p_msex_ctrl, msex[idxPeriod][idxPercent]);
						CTOP_CTRL_L9B_Wr01(ctr67_main2_syspll_ctrl, m2_dr3p_udex_ctrl, udex[idxPercent]);
						CTOP_CTRL_L9B_Wr01(ctr69_main2_syspll_ctrl, m1_dr3p_udex_ctrl, udex[idxPercent]);
#else
						CTOP_CTRL_L9B_WfCM(ctr67_main2_syspll_ctrl, m2_dr3p_cih_ctrl, 1, 3);
						CTOP_CTRL_L9B_WfCM(ctr69_main2_syspll_ctrl, m1_dr3p_cih_ctrl, 1, 3);
						CTOP_CTRL_L9B_WfCM(ctr67_main2_syspll_ctrl, m2_dr3p_lf_ctrl, 1, 1);
						CTOP_CTRL_L9B_WfCM(ctr69_main2_syspll_ctrl, m1_dr3p_lf_ctrl, 1, 1);
						CTOP_CTRL_L9B_WfCM(ctr67_main2_syspll_ctrl, m2_dr3p_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						CTOP_CTRL_L9B_WfCM(ctr69_main2_syspll_ctrl, m1_dr3p_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						CTOP_CTRL_L9B_WfCM(ctr67_main2_syspll_ctrl, m2_dr3p_udex_ctrl, udex[idxPercent], 5);
						CTOP_CTRL_L9B_WfCM(ctr69_main2_syspll_ctrl, m1_dr3p_udex_ctrl, udex[idxPercent], 5);
#endif
						CTOP_CTRL_L9B_WrFL(ctr67_main2_syspll_ctrl);
						CTOP_CTRL_L9B_WrFL(ctr69_main2_syspll_ctrl);
					} else {
						CTOP_CTRL_L9A_RdFL(ctr67);
						CTOP_CTRL_L9A_RdFL(ctr69);
						CTOP_CTRL_L9A_WfCM(ctr67, m2_dr3p_cih_ctrl, 1, 3);
						CTOP_CTRL_L9A_WfCM(ctr69, m1_dr3p_cih_ctrl, 1, 3);
						CTOP_CTRL_L9A_WfCM(ctr67, m2_dr3p_lf_ctrl, 1, 1);
						CTOP_CTRL_L9A_WfCM(ctr69, m1_dr3p_lf_ctrl, 1, 1);
						CTOP_CTRL_L9A_WfCM(ctr67, m2_dr3p_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						CTOP_CTRL_L9A_WfCM(ctr69, m1_dr3p_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						CTOP_CTRL_L9A_WfCM(ctr67, m2_dr3p_udex_ctrl, udex[idxPercent], 5);
						CTOP_CTRL_L9A_WfCM(ctr69, m1_dr3p_udex_ctrl, udex[idxPercent], 5);
						CTOP_CTRL_L9A_WrFL(ctr67);
						CTOP_CTRL_L9A_WrFL(ctr69);
					}
					break;
				}
			case LX_DE_SPREAD_SPECTRUM_CPU :
				{
					if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
						CTOP_CTRL_L9B_RdFL(ctr71_cpupll_ctrl);
#if 1
						CTOP_CTRL_L9B_Wr01(ctr71_cpupll_ctrl, c_dr3p_cih_ctrl, 1);
						CTOP_CTRL_L9B_Wr01(ctr71_cpupll_ctrl, c_dr3p_lf_ctrl, 1);
						CTOP_CTRL_L9B_Wr01(ctr71_cpupll_ctrl, c_dr3p_msex_ctrl, msex[idxPeriod][idxPercent]);
						CTOP_CTRL_L9B_Wr01(ctr71_cpupll_ctrl, c_dr3p_udex_ctrl, udex[idxPercent]);
#else
						CTOP_CTRL_L9B_WfCM(ctr71_cpupll_ctrl, c_dr3p_cih_ctrl, 1, 3);
						CTOP_CTRL_L9B_WfCM(ctr71_cpupll_ctrl, c_dr3p_lf_ctrl, 1, 1);
						CTOP_CTRL_L9B_WfCM(ctr71_cpupll_ctrl, c_dr3p_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						CTOP_CTRL_L9B_WfCM(ctr71_cpupll_ctrl, c_dr3p_udex_ctrl, udex[idxPercent], 5);
#endif
						CTOP_CTRL_L9B_WrFL(ctr71_cpupll_ctrl);
					} else {
						CTOP_CTRL_L9A_RdFL(ctr71);
						CTOP_CTRL_L9A_WfCM(ctr71, c_dr3p_cih_ctrl, 1, 3);
						CTOP_CTRL_L9A_WfCM(ctr71, c_dr3p_lf_ctrl, 1, 1);
						CTOP_CTRL_L9A_WfCM(ctr71, c_dr3p_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						CTOP_CTRL_L9A_WfCM(ctr71, c_dr3p_udex_ctrl, udex[idxPercent], 5);
						CTOP_CTRL_L9A_WrFL(ctr71);
					}

					break;
				}
			case LX_DE_SPREAD_SPECTRUM_LVDS :
				{
					if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
						CTOP_CTRL_L9B_RdFL(ctr63_display_pll_ctrl);
						//CTOP_CTRL_L9B_WfCM(ctr63_display_pll_ctrl, disp_cih_ctrl, 1, 3); // This is removed because it is no need to set LVDS spread spectrum.
#if 1
						CTOP_CTRL_L9B_Wr01(ctr63_display_pll_ctrl, disp_lf_ctrl, 1);
						CTOP_CTRL_L9B_Wr01(ctr63_display_pll_ctrl, disp_msex_ctrl, msex[idxPeriod][idxPercent]);
						CTOP_CTRL_L9B_Wr01(ctr63_display_pll_ctrl, disp_udex_ctrl, udex[idxPercent]);
#else
						//CTOP_CTRL_L9B_WfCM(ctr63_display_pll_ctrl, disp_lf_ctrl, 1, 1);
						//CTOP_CTRL_L9B_WfCM(ctr63_display_pll_ctrl, disp_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						//CTOP_CTRL_L9B_WfCM(ctr63_display_pll_ctrl, disp_udex_ctrl, udex[idxPercent], 5);
#endif

						CTOP_CTRL_L9B_WrFL(ctr63_display_pll_ctrl);
					} else {
						CTOP_CTRL_L9A_RdFL(ctr63);
						//CTOP_CTRL_L9A_WfCM(ctr63, disp_cih_ctrl, 1, 3); // This is removed because it is no need to set LVDS spread spectrum.
						CTOP_CTRL_L9A_WfCM(ctr63, disp_lf_ctrl, 1, 1);
						CTOP_CTRL_L9A_WfCM(ctr63, disp_msex_ctrl, msex[idxPeriod][idxPercent], 9);
						CTOP_CTRL_L9A_WfCM(ctr63, disp_udex_ctrl, udex[idxPercent], 5);
						CTOP_CTRL_L9A_WrFL(ctr63);
					}
					break;
				}
			default :
				BREAK_WRONG(pstParams->type);
				break;
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set deinterlace on/off control
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetDeinterlace(BOOLEAN bEnable)
{
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de VCS parameter.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetVcs(LX_DE_VCS_IPC_T *pstParams)
{
	int ret = RET_OK;
	int channel;
	int inx;

	do {
		CHECK_KNULL(pstParams);
		channel = GET_BITS(pstParams->inx, 31,	1);
		inx		= GET_BITS(pstParams->inx,	0, 30);
		if (inx > SIZE_OF_IPC_FOR_CPU) BREAK_WRONG(inx);
		spVideoIPCofCPU[channel][inx] = pstParams->data;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Select LVDS type(VESA/JEIDA).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetVesaJeida(LX_DE_OIF_STD_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_DE_OIF_VESA :
			case LX_DE_OIF_JEIDA :
				DE_OIF_L9_RdFL(lvds_if_control);
				DE_OIF_L9_WfCM(lvds_if_control, lvds_lsb_first, (LX_DE_OIF_VESA == *pstParams), 1);
				DE_OIF_L9_WrFL(lvds_if_control);
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select LVDS inteface type(LVDS/mini-LVDS).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetPanelIf(LX_DE_OIF_PANEL_IF_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_DE_OIF_PANEL_LVDS :
			case LX_DE_OIF_PANEL_MINI_LVDS :
#ifdef	USE_CTOP_CODES_FOR_L9
#ifdef	USE_CTOP_CHECK_LATER
#if 0	// L9 does not support mini lvds  --  default LVDS
				CTOP_CTRL_L9_RdFL(ctr32);
				CTOP_CTRL_L9_WfCM(ctr32, mini_en, (LX_DE_OIF_PANEL_MINI_LVDS == *pstParams), 1);
				CTOP_CTRL_L9_WrFL(ctr32);
#endif
#endif
#endif
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS pixel type( single/dual/quad).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetPixel(LX_DE_OIF_PIXEL_T *pstParams)
{
	int ret = RET_OK;
	int oifPixel = -1;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_OIF_PIXEL_SINGLE :
			case LX_OIF_PIXEL_SDQ :
				oifPixel = 0x0;
				break;
			case LX_OIF_PIXEL_DUAL :
				oifPixel = 0x1;
				break;
			case LX_OIF_PIXEL_QUAD :
				oifPixel = 0x2;
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
		if (ret) break;

//		BREAK_WRONG(oifPixel);
#ifdef USE_DE_CHECK_LATER
#if 0	// L9 does not support out_sdq
		DE_OIF_L9_RdFL(sync_de_control);
		DE_OIF_L9_Wr01(sync_de_control, out_sdq, oifPixel);
		DE_OIF_L9_WrFL(sync_de_control);
#endif
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS bit resolution(10bit/8bit).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetBitDepth(LX_DE_OIF_BIT_DEPTH_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_DE_OIF_8BIT :
			case LX_DE_OIF_10BIT :
				DE_OIF_L9_RdFL(lvds_if_control);
				DE_OIF_L9_WfCM(lvds_if_control, lvds_8bit_mode, (LX_DE_OIF_8BIT == *pstParams), 1);
				DE_OIF_L9_WrFL(lvds_if_control);
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS signal path from DE/FRC/LED/(ODC removed)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SelectOutPath(LX_DE_OIF_OUTPUT_PATH_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_OIF_OUTPUT_DE :
			case LX_OIF_OUTPUT_FRC :
			case LX_OIF_OUTPUT_LED :
//				BREAK_WRONG(ret);
#ifdef USE_DE_CHECK_LATER
#if 0	// L9 has a direct DE output
				DE_OIF_L9_RdFL(out_video_info);
				DE_OIF_L9_Wr01(out_video_info, out_sel, *pstParams);
				DE_OIF_L9_WrFL(out_video_info);
#endif
#endif
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS signal path from DE/FRC/LED/ODC
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SelectLvdsPath(LX_DE_OIF_LVDS_PATH_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_OIF_LVDS_NOT_ODC :
			case LX_OIF_LVDS_ODC :
//				  BREAK_WRONG(ret);
#ifdef USE_DE_CHECK_LATER
#if 0	// L9 has a direct DE output to lvds
				DE_OIF_L9_RdFL(lvds_if_control);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_out_sel, 0x0 );
				DE_OIF_L9_WrFL(lvds_if_control);
#endif
#endif
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select output chanel number 1CH, 2CH according to resolution and frame rate
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SelectOutCh(LX_DE_OIF_OUTPUT_CH_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_OIF_1CH :	// single LVDS out mode
			case LX_OIF_2CH :	// dual LVDS out mode for even, odd pixel

				DE_OIF_L9_RdFL(lvds_if_control);
				DE_OIF_L9_Wr01(lvds_if_control, dual_out_mode, *pstParams);
				DE_OIF_L9_WrFL(lvds_if_control);

				break;
			case LX_OIF_4CH :
				//
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select LED input path from DE/FRC.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SelectLedPath(LX_DE_OIF_LED_IN_PATH_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_OIF_LED_IN_DE :
			case LX_OIF_LED_IN_FRC :
//				  BREAK_WRONG(ret);
#ifdef USE_DE_CHECK_LATER
#if 0	// not support
				DE_OIF_L9_RdFL(led_in_control);
				DE_OIF_L9_WfCM(led_in_control, led_in_control, (LX_OIF_LED_IN_DE == *pstParams), 1);
				DE_OIF_L9_WrFL(led_in_control);
#endif
#endif
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select PWM signal path from DE/FRC.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SelectPwmPath(LX_DE_OIF_PWM_PATH_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_OIF_PWM_DE :
			case LX_OIF_PWM_FRC :
//				BREAK_WRONG(ret);
#ifdef USE_DE_CHECK_LATER
#if 0	// not support
				DE_OIF_L9_RdFL(pwm_control);
				DE_OIF_L9_WfCM(pwm_control, pwm_sel, (LX_OIF_PWM_FRC == *pstParams), 1);
				DE_OIF_L9_WrFL(pwm_control);
#endif
#endif
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select LR signal path from DE/FRC.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SelectLrPath(LX_DE_OIF_LR_PATH_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		switch (*pstParams) {
			case LX_OIF_LR_DE :
			case LX_OIF_LR_FRC :
//				BREAK_WRONG(ret);
#ifdef USE_DE_CHECK_LATER
#if 0	// not support
				DE_OIF_L9_RdFL(lr_if_control);
				DE_OIF_L9_WfCM(lr_if_control, lr_if_control, (LX_OIF_LR_FRC == *pstParams), 1);
				DE_OIF_L9_WrFL(lr_if_control);
#endif
#endif
				break;
			default :
				BREAK_WRONG(*pstParams);
		}
	} while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize OIF module.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_Init(LX_DE_OIF_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		ret = DE_REG_L9_OIF_SetVesaJeida(&pstParams->eVesaJeida);
		if (ret) break;
		ret = DE_REG_L9_OIF_SetPanelIf(&pstParams->eLvdsMini);
		if (ret) break;
		ret = DE_REG_L9_OIF_SetPixel(&pstParams->ePixel);
		if (ret) break;
		ret = DE_REG_L9_OIF_SetBitDepth(&pstParams->eBitMode);
		if (ret) break;
		ret = DE_REG_L9_OIF_SelectOutPath(&pstParams->eOutVideo);
		if (ret) break;
		ret = DE_REG_L9_OIF_SelectLvdsPath(&pstParams->eOutLVDS);
		if (ret) break;
		ret = DE_REG_L9_OIF_SelectOutCh(&pstParams->eOutCH);
		if (ret) break;
		ret = DE_REG_L9_OIF_SelectLedPath(&pstParams->eLedIn);
		if (ret) break;
		ret = DE_REG_L9_OIF_SelectPwmPath(&pstParams->ePWM);
		if (ret) break;
		ret = DE_REG_L9_OIF_SelectLrPath(&pstParams->eLR);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Informatation of OIF module.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_GetInfo(LX_DE_OIF_INFO_T *pstParams)
{
	int ret = RET_OK;
#ifdef USE_DE_CHECK_LATER

	UINT32 readVal = 0;

	do {
		CHECK_KNULL(pstParams);
		DE_OIF_L9_RdFL(lvds_if_control);
		DE_OIF_L9_Rd01(lvds_if_control, lvds_lsb_first, readVal);
		pstParams->eVesaJeida = (1 == readVal)?LX_DE_OIF_VESA:LX_DE_OIF_JEIDA; // toggle polarity

#ifdef	USE_CTOP_CODES_FOR_L9
#ifdef	USE_CTOP_CHECK_LATER
#if 0	// mini-lvds removed from l9
		CTOP_CTRL_L9_RdFL(ctr32);
		CTOP_CTRL_L9_Rd01(ctr32, mini_en, readVal);
		pstParams->eLvdsMini = (0 == readVal)?LX_DE_OIF_PANEL_LVDS:LX_DE_OIF_PANEL_MINI_LVDS;
#endif
#endif
#endif

#ifdef USE_DE_CHECK_LATER
		DE_OIF_L9_RdFL(sync_de_control);
		DE_OIF_L9_Rd01(sync_de_control, out_sdq, readVal);
#endif
		switch (readVal) {
			case 0x0 :
				pstParams->ePixel = LX_OIF_PIXEL_SINGLE;
				break;
			case 0x1 :
				pstParams->ePixel = LX_OIF_PIXEL_DUAL;
				break;
			case 0x2 :
				pstParams->ePixel = LX_OIF_PIXEL_QUAD;
				break;
			default :
				BREAK_WRONG(readVal);
		}
		if (ret) break;

		//DE_OIF_L9_RdFL(lvds_if_control);
		DE_OIF_L9_Rd01(lvds_if_control, lvds_8bit_mode, readVal);
		pstParams->eBitMode = (1 == readVal)?LX_DE_OIF_8BIT:LX_DE_OIF_10BIT;	// toggle polarity

		DE_OIF_L9_RdFL(out_video_info);
		BREAK_WRONG(ret);
#ifdef USE_DE_CHECK_LATER
		DE_OIF_L9_Rd01(out_video_info, out_sel, readVal);
#endif
		switch (readVal) {
			case LX_OIF_OUTPUT_DE :
			case LX_OIF_OUTPUT_FRC :
			case LX_OIF_OUTPUT_LED :
				pstParams->eOutVideo = readVal;
				break;
			default :
				BREAK_WRONG(readVal);
		}
		if (ret) break;

		//DE_OIF_L9_RdFL(lvds_if_control);
#ifdef USE_DE_CHECK_LATER
		DE_OIF_L9_Rd01(lvds_if_control, lvds_out_sel, readVal);
#endif
		pstParams->eOutLVDS = (0 == readVal)?LX_OIF_LVDS_NOT_ODC:LX_OIF_LVDS_ODC;

#ifdef USE_DE_CHECK_LATER
		DE_OIF_L9_Rd01(out_video_info, out_ch_num, readVal);
#endif
		switch (readVal) {
			case LX_OIF_1CH :
			case LX_OIF_2CH :
			case LX_OIF_4CH :
				pstParams->eOutCH = readVal;
				break;
			default :
				BREAK_WRONG(readVal);
		}
		if (ret) break;

#ifdef USE_DE_CHECK_LATER
		DE_OIF_L9_RdFL(led_in_control);
		DE_OIF_L9_Rd01(led_in_control, led_in_control, readVal);
#endif
		pstParams->eLedIn = (1 == readVal)?LX_OIF_LED_IN_DE:LX_OIF_LED_IN_FRC;	// toggle polarity

#ifdef USE_DE_CHECK_LATER
		DE_OIF_L9_RdFL(pwm_control);
		DE_OIF_L9_Rd01(pwm_control, pwm_sel, readVal);
#endif
		pstParams->ePWM = (0 == readVal)?LX_OIF_PWM_DE:LX_OIF_PWM_FRC;

#ifdef USE_DE_CHECK_LATER
		DE_OIF_L9_RdFL(lr_if_control);
		DE_OIF_L9_Rd01(lr_if_control, lr_if_control, readVal);
#endif
		pstParams->eLR = (0 == readVal)?LX_OIF_LR_DE:LX_OIF_LR_FRC;

	} while (0);
#endif //#ifdef USE_DE_CHECK_LATER
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set LVDS OUTPUT Enable.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetLvdsOutput(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
//		DE_OIF_L9_RdFL(lvds_en);
//		DE_OIF_L9_WfCM(lvds_en, lvds_en, *pstParams, GET_BITS(0xFFFFFFFF, 0, 24));
//		DE_OIF_L9_WrFL(lvds_en);
#ifdef	USE_CTOP_CODES_FOR_L9
		//CTOP_CTRL_L9_RdFL(ctr32);
		//CTOP_CTRL_L9_WfCM(ctr32, en, *pstParams, GET_BITS(0xFFFFFFFF, 0, 24));
		//CTOP_CTRL_L9_WrFL(ctr32);
		//CTOP_CTRL_L9_FLCM(ctr73, lv_rmlvds_en_ctrl, *pstParams, 0x1);
		if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
			CTOP_CTRL_L9B_FLCM(ctr73_hslvds_tx_ctrl, lv_rmlvds_en_ctrl, (TRUE == *pstParams), 0x0);
		} else {
			CTOP_CTRL_L9A_FLCM(ctr73, lv_rmlvds_en_ctrl, (TRUE == *pstParams), 0x0);
		}
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set LVDS Power Enable.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetLvdsPower(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
#ifdef	USE_CTOP_CODES_FOR_L9
		//CTOP_CTRL_L9_RdFL(ctr32);
		//CTOP_CTRL_L9_WfCM(ctr32, pdb, (TRUE == *pstParams), 1);
		//CTOP_CTRL_L9_WrFL(ctr32);
		if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
			CTOP_CTRL_L9B_FLCM(ctr74_hslvds_tx_ctrl, lv_pdb_ctrl, (TRUE == *pstParams), 1);
		} else {
			CTOP_CTRL_L9A_FLCM(ctr74, lv_pdb_ctrl, (TRUE == *pstParams), 1);
		}
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set LVDS to black.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetDarkScreen(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		if( TRUE == *pstParams )
		{
			DE_OIF_L9_RdFL(data_color);
			DE_OIF_L9_Wr01(data_color, data_color_b, 0x0);
			DE_OIF_L9_Wr01(data_color, data_color_g, 0x0);
			DE_OIF_L9_Wr01(data_color, data_color_r, 0x0);
			DE_OIF_L9_WrFL(data_color);

			DE_OIF_L9_RdFL(sync_color);
			DE_OIF_L9_Wr01(sync_color, sync_color_b, 0x0);
			DE_OIF_L9_Wr01(sync_color, sync_color_g, 0x0);
			DE_OIF_L9_Wr01(sync_color, sync_color_r, 0x0);
			DE_OIF_L9_WrFL(sync_color);
		}
		DE_OIF_L9_RdFL(data_color_from);
		DE_OIF_L9_WfCV(data_color_from, b_data_from, ( TRUE == *pstParams ), 0x3, 0x2);
		DE_OIF_L9_WfCV(data_color_from, g_data_from, ( TRUE == *pstParams ), 0x3, 0x1);
		DE_OIF_L9_WfCV(data_color_from, r_data_from, ( TRUE == *pstParams ), 0x3, 0x0);
		DE_OIF_L9_WrFL(data_color_from);
	} while (0);


	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control LVDS LVDS output channel.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetLvdsOutCtrl(LX_DE_OIF_LVDS_OUT_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
			CTOP_CTRL_L9B_RdFL(ctr26_extclk_div_sel);
			CTOP_CTRL_L9B_RdFL(ctr69_main2_syspll_ctrl);
			CTOP_CTRL_L9B_RdFL(ctr72_hslvds_tx_ctrl);
			CTOP_CTRL_L9B_RdFL(ctr73_hslvds_tx_ctrl);
			CTOP_CTRL_L9B_RdFL(ctr74_hslvds_tx_ctrl);
			switch (pstParams->outMode) {
				case TRUE :
					CTOP_CTRL_L9B_Wr(ctr69_main2_syspll_ctrl, 0x883D8186);

					CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, lvds_clk_sel, 1);	// half of original (74.25 MHz)

					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_te1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_ta2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_tb2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_tc2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_tclk2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_td2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_te2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_flip_en_ctrl, 0);

					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_ta1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_tb1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_tc1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_tclk1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_td1_ctrl, 0);
					break;
				case FALSE :
					CTOP_CTRL_L9B_Wr(ctr69_main2_syspll_ctrl, 0x883D8186);

					CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, lvds_clk_sel, 0);	// original frequency (148.5MHz)

					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_te1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_ta2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_tb2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_tc2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_tclk2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_td2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_pemp_te2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr72_hslvds_tx_ctrl, lv_flip_en_ctrl, 0);

					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_ta1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_tb1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_tc1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_tclk1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_pemp_td1_ctrl, 0);

					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_swc_ta2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_swc_tb2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_swc_tc2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_swc_tclk2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_swc_td2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr73_hslvds_tx_ctrl, lv_swc_te2_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr74_hslvds_tx_ctrl, lv_swc_ta1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr74_hslvds_tx_ctrl, lv_swc_tb1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr74_hslvds_tx_ctrl, lv_swc_tc1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr74_hslvds_tx_ctrl, lv_swc_tclk1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr74_hslvds_tx_ctrl, lv_swc_td1_ctrl, 0);
					CTOP_CTRL_L9B_Wr01(ctr74_hslvds_tx_ctrl, lv_swc_te1_ctrl, 0);
					break;
				default :
					BREAK_WRONG(pstParams->outMode);
			}
			if (ret) break;

			CTOP_CTRL_L9B_WrFL(ctr26_extclk_div_sel);
			CTOP_CTRL_L9B_WrFL(ctr69_main2_syspll_ctrl);
			CTOP_CTRL_L9B_WrFL(ctr72_hslvds_tx_ctrl);
			CTOP_CTRL_L9B_WrFL(ctr73_hslvds_tx_ctrl);
			CTOP_CTRL_L9B_WrFL(ctr74_hslvds_tx_ctrl);

			DE_OIF_L9_RdFL(lvds_if_control);
			DE_OIF_L9_Wr01(lvds_if_control, dual_out_mode,	pstParams->outMode);

			/* raxis.lim (2010/09/10) -- lvds_ch2_from should be '3' to enable the separated OSD mode */
			DE_OIF_L9_Wr01(lvds_if_control, lvds_ch1_from,	(pstParams->ch1LVDS==2||pstParams->ch1LVDS==3)?3:pstParams->ch1LVDS);
			DE_OIF_L9_Wr01(lvds_if_control, lvds_ch2_from,	(pstParams->ch2LVDS==2||pstParams->ch2LVDS==3)?3:pstParams->ch2LVDS);

			if(pstParams->outMode == FALSE && pstParams->ch2LVDS == 2)	// lvds ch1 : video , lvds ch2 : osd
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 3); // OSD blending info for left
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 4); // frame_lr
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 1); // OSD alpha[0]
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 2); // OSD alpha[1]
			}
			else if(pstParams->outMode == FALSE && pstParams->ch1LVDS == 2) // lvds ch1 : osd , lvds ch2 : video
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 1);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 2);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 4);
			}
			else if(pstParams->outMode == FALSE)
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 4);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 4);
			}
			else if(pstParams->outMode == TRUE)
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 4);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 4);
			}

			DE_OIF_L9_WrFL(lvds_if_control);
		} else {
			CTOP_CTRL_L9A_RdFL(ctr27);
			CTOP_CTRL_L9A_RdFL(ctr72);
			CTOP_CTRL_L9A_RdFL(ctr73);
			CTOP_CTRL_L9A_RdFL(ctr74);
			switch (pstParams->outMode) {
				case TRUE :
					CTOP_CTRL_L9A_Wr01(ctr27, lvds_clk_sel, 1);  // half of original (74.25 MHz)

					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_te1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_ta2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_tb2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_tc2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_tclk2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_td2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_te2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_flip_en_ctrl, 0);

					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_ta1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_tb1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_tc1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_tclk1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_td1_ctrl, 0);
					break;
				case FALSE :
					CTOP_CTRL_L9A_Wr01(ctr27, lvds_clk_sel, 0);  // original frequency (148.5MHz)

					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_te1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_ta2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_tb2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_tc2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_tclk2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_td2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_pemp_te2_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr72, lv_flip_en_ctrl, 0);

					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_ta1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_tb1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_tc1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_tclk1_ctrl, 0);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_pemp_td1_ctrl, 0);

					CTOP_CTRL_L9A_Wr01(ctr73, lv_swc_ta2_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_swc_tb2_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_swc_tc2_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_swc_tclk2_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_swc_td2_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr73, lv_swc_te2_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr74, lv_swc_ta1_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr74, lv_swc_tb1_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr74, lv_swc_tc1_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr74, lv_swc_tclk1_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr74, lv_swc_td1_ctrl, 5);
					CTOP_CTRL_L9A_Wr01(ctr74, lv_swc_te1_ctrl, 5);
					break;
				default :
					BREAK_WRONG(pstParams->outMode);
			}
			if (ret) break;

			CTOP_CTRL_L9A_WrFL(ctr27);
			CTOP_CTRL_L9A_WrFL(ctr72);
			CTOP_CTRL_L9A_WrFL(ctr73);
			CTOP_CTRL_L9A_WrFL(ctr74);

			DE_OIF_L9_RdFL(lvds_if_control);
			DE_OIF_L9_Wr01(lvds_if_control, dual_out_mode,	pstParams->outMode);
			DE_OIF_L9_Wr01(lvds_if_control, lvds_ch1_from,	pstParams->ch1LVDS);
			DE_OIF_L9_Wr01(lvds_if_control, lvds_ch2_from,	pstParams->ch2LVDS);

			if(pstParams->outMode == FALSE && pstParams->ch2LVDS == 2)	// lvds ch1 : video , lvds ch2 : osd
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 3); // OSD blending info for left
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 4); // frame_lr
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 1); // OSD alpha[0]
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 2); // OSD alpha[1]
			}
			else if(pstParams->outMode == FALSE && pstParams->ch1LVDS == 2) // lvds ch1 : osd , lvds ch2 : video
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 1);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 2);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 4);
			}
			else if(pstParams->outMode == FALSE)
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 4);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 4);
			}
			else if(pstParams->outMode == TRUE)
			{
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch1, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch1, 4);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_d_lane_empty_data_ch2, 3);
				DE_OIF_L9_Wr01(lvds_if_control, lvds_e_lane_empty_data_ch2, 4);
			}

			DE_OIF_L9_WrFL(lvds_if_control);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control LVDS port swap.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_OIF_SetLvdsPortSwap(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		DE_OIF_L9_RdFL(lvds_port_swap);
		if(*pstParams == FALSE)	{ 	// default
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_a_lane_sel_ch1, 0);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_b_lane_sel_ch1, 1);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_c_lane_sel_ch1, 2);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_d_lane_sel_ch1, 3);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_e_lane_sel_ch1, 4);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_a_lane_sel_ch2, 0);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_b_lane_sel_ch2, 1);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_c_lane_sel_ch2, 2);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_d_lane_sel_ch2, 3);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_e_lane_sel_ch2, 4);
		}
		else {						// swap
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_a_lane_sel_ch1, 4);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_b_lane_sel_ch1, 3);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_c_lane_sel_ch1, 2);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_d_lane_sel_ch1, 1);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_e_lane_sel_ch1, 0);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_a_lane_sel_ch2, 4);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_b_lane_sel_ch2, 3);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_c_lane_sel_ch2, 2);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_d_lane_sel_ch2, 1);
			DE_OIF_L9_Wr01(lvds_port_swap, lvds_e_lane_sel_ch2, 0);
		}
		DE_OIF_L9_WrFL(lvds_port_swap);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Table.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetTable(LX_DE_SET_TABLE_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_REG_WR_T *pTable;
	UINT32 tableLength;
	int i;

	do {
		CHECK_KNULL(pstParams);
		pTable = (LX_DE_REG_WR_T *)pstParams->pTable;
		CHECK_KNULL(pTable);
		tableLength = pstParams->size/sizeof(LX_DE_REG_WR_T);
		for (i=0;i<tableLength;i++) DE_REG_L9_WD(pTable[i].wr_addr, pTable[i].wr_data);
	} while(0);

	return ret;
}

int DE_REG_L9_GPIO_Init(void)
{
#ifdef	USE_CTOP_CODES_FOR_L9
	if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
#ifdef USE_VIDEO_UART2_FOR_MCU
		CTOP_CTRL_L9B_RdFL(ctr29_swrst);
		CTOP_CTRL_L9B_RdFL(ctr36_uart_sel);
		CTOP_CTRL_L9B_Wr01(ctr29_swrst, jtag1_sel,	0x3);	// setting JTAG for DE
		CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, uart2_sel, 1);	  // UART2 -> DE
		CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, rx_sel_de, 2);	  // UART2 -> DE
		CTOP_CTRL_L9B_WrFL(ctr29_swrst);
		CTOP_CTRL_L9B_WrFL(ctr36_uart_sel);
#else
		CTOP_CTRL_L9B_FLWf(ctr29_swrst, jtag1_sel,	 0x0);	// setting JTAG for SP
		CTOP_CTRL_L9B_FLWf(ctr36_uart_sel, uart2_sel,  0x2);  // setting UART2 for CPU (Magic Remote)
#endif
	} else {
#ifdef USE_VIDEO_UART2_FOR_MCU
		CTOP_CTRL_L9A_RdFL(ctr29);
		CTOP_CTRL_L9A_RdFL(ctr36);
		CTOP_CTRL_L9A_Wr01(ctr29, jtag_sel,  0x3);	 // setting JTAG for DE
		CTOP_CTRL_L9A_Wr01(ctr36, uart2_sel, 1);	 // UART2 -> DE
		CTOP_CTRL_L9A_Wr01(ctr36, rx_sel_de, 2);	 // UART2 -> DE
		CTOP_CTRL_L9A_WrFL(ctr29);
		CTOP_CTRL_L9A_WrFL(ctr36);
#else
		CTOP_CTRL_L9A_FLWf(ctr29, jtag_sel,   0x0);  // setting JTAG for SP
		CTOP_CTRL_L9A_FLWf(ctr36, uart2_sel,  0x2);  // setting UART2 for CPU (Magic Remote)
#endif
	}
#endif

	return 0;
}

int DE_REG_L9_HDMI_Init(void)
{
	return 0;
}

int DE_REG_L9_LVDS_Init(void)
{
#if 0	// disable lvds off to remain bootlog image as long as possible. dongho7.park 2010.10.19
// bootlog 에 의해 enable 된 LVDS 를 여기서 off 하여 memory dummy pattern 을 없앤다. 2010 09 14 dongho7.park
	CTOP_CTRL_L9_Wr(ctr32, 0xf5000000);
	CTOP_CTRL_L9_WrFL(ctr32);
#endif
#if 0
	CTOP_CTRL_L9_Wr(ctr32, 0xb5ffffff);
	CTOP_CTRL_L9_Wr(ctr33, 0xffffff00);
	CTOP_CTRL_L9_Wr(ctr34, 0x00000000);
	CTOP_CTRL_L9_Wr(ctr38, 0x00000000);
	CTOP_CTRL_L9_Wr(ctr39, 0x007d1fff);
	CTOP_CTRL_L9_WrFL(ctr32);
	CTOP_CTRL_L9_WrFL(ctr33);
	CTOP_CTRL_L9_WrFL(ctr34);
	CTOP_CTRL_L9_WrFL(ctr38);
	CTOP_CTRL_L9_WrFL(ctr39);
#endif

	/* CLOCK - dco fcw */
	DE_DEA_L9_FLWr(dea_dco_fcw, 0x0011745D);

	return 0;
}

int DE_REG_L9_MISC_Init(void)
{
	DE_DEB_L9_RdFL(deb_disp_vs_va);
	DE_DEB_L9_Wr01(deb_disp_vs_va, disp_sync_va, 0x0438);
	DE_DEB_L9_Wr01(deb_disp_vs_va, vsync, 0x001F);
	DE_DEB_L9_WrFL(deb_disp_vs_va);

#if 0 // Uboot & ICOTL Setting by sh.myoung 2011.07.22
	/* LVDS  clk 1/2  for 60 Hz */
	CTOP_CTRL_L9_RdFL(ctr27);
	CTOP_CTRL_L9_Wr01(ctr27, lvds_clk_sel, 1);
	CTOP_CTRL_L9_WrFL(ctr27);

	/* OIF for 1080p60Hz  */
	DE_OIF_L9_RdFL(lvds_if_control);
	DE_OIF_L9_Wr01(lvds_if_control, lvds_lsb_first,  1);	// VESA
	DE_OIF_L9_Wr01(lvds_if_control, dual_out_mode,	 1);	// dual LVDS out mode for even, odd pixel
	DE_OIF_L9_WrFL(lvds_if_control);
#endif

	/*	Boot Logo가 사라진 후,
	 *	application 초기화하는 과정에서,
	 *	L9 LVDS garbage가 생김. 이를 방어하기 위해서, DE_LVDS_INIT에
	 *	OIF Dark Screen을 걸어주고, application의 video initialize에서
	 *	OIF Dark Screen을 풀어준다. (video_soc_ddi.c의 463line)
	 *	그리고 나서, Window Blank On을 해준다.
	 *	kangsik.yoon 2011.07.06
	 */
	DE_OIF_L9_RdFL(data_color);
	DE_OIF_L9_Wr01(data_color, data_color_b, 0x0);
	DE_OIF_L9_Wr01(data_color, data_color_g, 0x0);
	DE_OIF_L9_Wr01(data_color, data_color_r, 0x0);
	DE_OIF_L9_WrFL(data_color);

	DE_OIF_L9_RdFL(sync_color);
	DE_OIF_L9_Wr01(sync_color, sync_color_b, 0x0);
	DE_OIF_L9_Wr01(sync_color, sync_color_g, 0x0);
	DE_OIF_L9_Wr01(sync_color, sync_color_r, 0x0);
	DE_OIF_L9_WrFL(sync_color);

	DE_OIF_L9_RdFL(data_color_from);
	DE_OIF_L9_Wr01(data_color_from, b_data_from, 0x3);
	DE_OIF_L9_Wr01(data_color_from, g_data_from, 0x3);
	DE_OIF_L9_Wr01(data_color_from, r_data_from, 0x3);
	DE_OIF_L9_WrFL(data_color_from);

	if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
		CTOP_CTRL_L9B_RdFL(ctr26_extclk_div_sel);
		CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, exta_sel, 0);
		CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, extb_sel, 1);
		CTOP_CTRL_L9B_WrFL(ctr26_extclk_div_sel);
	} else {
	// force to high
		/* default dc PWM output from PWM2 port */
		DE_DEB_L9A_RdFL(deb_pwm_r2);
		DE_DEB_L9A_Wr01(deb_pwm_r2, pwm2_r_h, 0x0000);
		DE_DEB_L9A_Wr01(deb_pwm_r2, pwm2_r_v, 0x0000);
		DE_DEB_L9A_WrFL(deb_pwm_r2);
	}

	return 0;
}

int DE_REG_L9_OSD_Init(void)
{
	// osd layer 0/1/2 --> off
	DE_OSD_L9_FLWr(osd0_cfg, 0x1b000000);
	DE_OSD_L9_FLWr(osd1_cfg, 0x1b000000);
	DE_OSD_L9_FLWr(osd2_cfg, 0x1b000000);

	return 0;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set uart for MCU or CPU
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_Uart0_Switch(int whichUart)
{
	int ret = RET_OK;

#ifdef	USE_CTOP_CODES_FOR_L9
	if (lx_chip_rev() >= LX_CHIP_REV(L9,B0)) {
#ifdef USE_DE_SWITCH_UART
		CTOP_CTRL_L9B_RdFL(ctr36_uart_sel);
#if 1
		switch (whichUart)
		{
			case 0 :
				CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, uart0_sel, 2); // UART0 = cpu0
				CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, uart2_sel, 1); // UART2 = de
				CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, rx_sel_de, 2); // 2:DE from UART2
				break;
			case 1 :
				CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, uart0_sel, 1); // UART0 = de
				CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, uart2_sel, 2); // UART2 = cpu2
				CTOP_CTRL_L9B_Wr01(ctr36_uart_sel, rx_sel_de, 0); // 0:DE from UART0
				break;
			default :
				BREAK_WRONG(whichUart);
				break;
		}
#else
		CTOP_CTRL_L9B_WfCM(ctr36_uart_sel, uart0_sel, !whichUart, 0x1);   // 2:CPU , 1:DE
		CTOP_CTRL_L9B_WfCM(ctr36_uart_sel, rx_sel_de,  whichUart, 0x0);   // 0:DE from UART0 , 1:DE from UART1
#endif
		CTOP_CTRL_L9B_WrFL(ctr36_uart_sel);
#endif
	} else {
#ifdef USE_DE_SWITCH_UART
		CTOP_CTRL_L9A_RdFL(ctr36);
#if 1
		switch (whichUart)
		{
			case 0 :
				CTOP_CTRL_L9A_Wr01(ctr36, uart0_sel, 2); // UART0 = cpu0
				CTOP_CTRL_L9A_Wr01(ctr36, uart2_sel, 1); // UART2 = de
				CTOP_CTRL_L9A_Wr01(ctr36, rx_sel_de, 2); // 2:DE from UART2
				break;
			case 1 :
				CTOP_CTRL_L9A_Wr01(ctr36, uart0_sel, 1); // UART0 = de
				CTOP_CTRL_L9A_Wr01(ctr36, uart2_sel, 2); // UART2 = cpu2
				CTOP_CTRL_L9A_Wr01(ctr36, rx_sel_de, 0); // 0:DE from UART0
				break;
			default :
				BREAK_WRONG(whichUart);
				break;
		}
#else
		CTOP_CTRL_L9A_WfCM(ctr36, uart0_sel, !whichUart, 0x1);	 // 2:CPU , 1:DE
		CTOP_CTRL_L9A_WfCM(ctr36, rx_sel_de,  whichUart, 0x0);	 // 0:DE from UART0 , 1:DE from UART1
#endif
		CTOP_CTRL_L9A_WrFL(ctr36);
#endif
	}
#endif
	return ret;
}

#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_L9_FW_Download(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	char						*lpAddr = NULL;
	LX_DE_CH_MEM_T				*pFwMem = NULL;
	BOOLEAN						run_stall = 0;
#if   !defined(USE_DE_FIRMWARE_RUN_IN_PAK)
	BOOLEAN						tx_done = 0;
#endif
	UINT32						fwBaseAddr;
	UINT32 						fwSize;

	do {
		CHECK_KNULL(pstParams);
		if (!pstParams->size) break;
		if (!pstParams->pData) break;
		DE_IPC_L9_RdFL(set_ctrl0);
		DE_IPC_L9_Rd01(set_ctrl0, run_stall, run_stall);
		if (!run_stall) break;
		DE_IPC_L9_FLWr(atlas_port_sel, 0x1344);
#if defined(USE_DE_FIRMWARE_RUN_IN_PAK)
		pFwMem = (LX_DE_CH_MEM_T *)&gpDeMem->fw[1];
#else
		pFwMem = (LX_DE_CH_MEM_T *)&gpDeMem->fw[0];
#endif
		CHECK_KNULL(pFwMem);
		fwBaseAddr = pFwMem->fw_base;
		fwSize     = pFwMem->fw_size;
		if (fwSize < pstParams->size) fwSize = pstParams->size;
		fwSize = GET_RDUP(fwSize, 4);
		lpAddr = (char *)ioremap(fwBaseAddr, fwSize);
		CHECK_KNULL(lpAddr);
		memcpy(lpAddr, pstParams->pData, pstParams->size);
		if (lpAddr) iounmap((void*)lpAddr);
		switch (pstParams->inx) {
#if   !defined(USE_DE_FIRMWARE_RUN_IN_PAK)
			case 2 :
#if defined(USE_DE_FIRMWARE_RUN_IN_ROM) || defined(USE_DE_FIRMWARE_RUN_IN_DDR)
			case 1 :
				if (1 == pstParams->inx)
				{
#ifdef USE_DE_FIRMWARE_LOAD_DRM_IRM_EACH
					DE_IPC_L9_FLWr(tx_dst_addr, 0x40000000);
#else
					break;
#endif
				} else
#endif
				{
					DE_IPC_L9_FLWr(tx_dst_addr, 0x3ffe0000);
				}
				DE_IPC_L9_FLWr(tx_src_addr, fwBaseAddr);
				DE_IPC_L9_FLWr(tx_length,	(pstParams->size + sizeof(UINT32) -1)/sizeof(UINT32));
				DE_IPC_L9_FLWr(edma_ctrl,	0x3);
				while (1) {
					DE_IPC_L9_FLRf(edma_ctrl, tx_done, tx_done);
					if (tx_done) break;
					msleep(1);
				}
#if   defined(USE_DE_FIRMWARE_RUN_IN_ROM)
				DE_PRINT("Loading DE_FW_ROM_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				break;
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR)
				DE_PRINT("Loading DE_FW_DDR_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				break;
#else
				DE_PRINT("Loading DE_FW_DIRAM\n");
#endif
#endif
#if defined(USE_DE_FIRMWARE_RUN_IN_ROM) || defined(USE_DE_FIRMWARE_RUN_IN_DDR) || defined(USE_DE_FIRMWARE_RUN_IN_PAK)
			case 3 :
#endif
#if   defined(USE_DE_FIRMWARE_RUN_IN_PAK)
				DE_PRINT("Loading DE_FW_PAK_ADR5\n");
				DE_IPC_L9_FLWr(srom_boot_offset, USE_DE_FIRMWARE_BOOT_OFFSET);
				if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
					DE_IPC_L9_Wr01(set_ctrl0, start_vector_sel, 0);
					DE_IPC_L9_Wr01(set_ctrl0, sw_reset, 1);
				}
#elif defined(USE_DE_FIRMWARE_RUN_IN_ROM)
				DE_PRINT("Loading DE_FW_ROM_ADR5\n");
				DE_IPC_L9_FLWr(srom_boot_offset, USE_DE_FIRMWARE_BOOT_OFFSET);
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR)
				DE_IPC_L9_FLWr(atlas_port_sel, 0x1434);
				DE_PRINT("Loading DE_FW_DDR_ADR6\n");
#endif
				DE_IPC_L9_Wr01(set_ctrl0, run_stall, 0);
				DE_IPC_L9_WrFL(set_ctrl0);
			default :
				break;
		}
	} while (0);

	return RET_OK;
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix and offset for each external source information.
 *
 * @param [IN] structure pointer to carry infomation about cvi FIR filter
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetCviFir(LX_DE_CVI_FIR_T *pstParams)
{
	int ret = RET_OK;
	DE_PARAM_TYPE_T tableId;
	UINT32 firTable[ARRAY_SIZE(pstParams->fir_coef)+ARRAY_SIZE(pstParams->fir_coef_CbCr)];
	UINT32 inx = 0;
	int i;

	do {
		CHECK_KNULL(pstParams);
		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				tableId = DE_CVM_FIR_COEF;
				break;
			case LX_DE_CVI_CH_B :
				tableId = DE_CVS_FIR_COEF;
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
		for (i=0;i<ARRAY_SIZE(pstParams->fir_coef);i++)		 firTable[inx++] = pstParams->fir_coef[i];
		for (i=0;i<ARRAY_SIZE(pstParams->fir_coef_CbCr);i++) firTable[inx++] = pstParams->fir_coef_CbCr[i];

#ifdef USE_PARM_CODES_FOR_L9
		ret = DE_PRM_L9_LoadTable(tableId, DE_PARAM_WRITE, pstParams->isEnable, firTable, inx);
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video test pattern generator to mono-tone color.
 *
 * @param [IN] structure pointer to carry infomation about captured test pattern generator parameter.
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetCviTpg(LX_DE_CVI_TPG_T *pstParams)
{
	int ret = RET_OK;
	unsigned char ptn_type;

	do {
		CHECK_KNULL(pstParams);
		//(TRUE==pstParams->isPtnOn)?(ptn_type = 0x1):(ptn_type= 0x0); // one color pattern or bypass
		ptn_type = (TRUE==pstParams->isPtnOn)?0x1:0x0; // one color pattern or bypass

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				DE_CVA_L9_RdFL(cva_misc_ctrl);
				DE_CVA_L9_Wr01(cva_misc_ctrl, pattern_type,   ptn_type);
				DE_CVA_L9_WfCM(cva_misc_ctrl, pattern_csc,	  (TRUE==pstParams->isGBR),   0x1);
				DE_CVA_L9_WfCM(cva_misc_ctrl, write_inhibit,  (TRUE==pstParams->isFrzOn), 0x1);
				DE_CVA_L9_Wr01(cva_misc_ctrl, pattern_detail, pstParams->ptnColor);
				DE_CVA_L9_WrFL(cva_misc_ctrl);
				break;
			case LX_DE_CVI_CH_B :
				DE_CVB_L9_RdFL(cvb_misc_ctrl);
				DE_CVB_L9_Wr01(cvb_misc_ctrl, pattern_type,   ptn_type);
				DE_CVB_L9_WfCM(cvb_misc_ctrl, pattern_csc,	  (TRUE==pstParams->isGBR),   0x1);
				DE_CVB_L9_WfCM(cvb_misc_ctrl, write_inhibit,  (TRUE==pstParams->isFrzOn), 0x1);
				DE_CVB_L9_Wr01(cvb_misc_ctrl, pattern_detail, pstParams->ptnColor);
				DE_CVB_L9_WrFL(cvb_misc_ctrl);
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video color sampling mode(sub sampling or 3 tap filtering).
 *
 * @param [IN] structure pointer to carry infomation about captured color sampling parameter.
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
					DE_CVA_L9B_WfCM(cva_dig_filt_ctrl3, fir_c_en, (TRUE==pstParams->is3tap), 0x1);
				} else {
					DE_CVA_L9A_FLCM(cva_dig_filt_ctrl3, fir_sample_c, (TRUE==pstParams->is3tap), 0x1);
				}
				break;
			case LX_DE_CVI_CH_B :
				if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
					DE_CVB_L9B_WfCM(cvb_dig_filt_ctrl3, fir_c_en, (TRUE==pstParams->is3tap), 0x1);
				} else {
					DE_CVB_L9A_FLCM(cvb_dig_filt_ctrl3, fir_sample_c, (TRUE==pstParams->is3tap), 0x1);
				}
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief reshape sync of captured video for PC input.
 *
 * @param [IN] structure pointer to carry infomation about sync parameter.
 *
 * @return RET_OK(0)
 */
int DE_REG_L9_SetCviSyncReshape(LX_DE_CVI_SYNC_RESHAPE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				DE_CVA_L9_RdFL(cva_int_sync_ctrl0);
				DE_CVA_L9_RdFL(cva_int_sync_ctrl1);
				DE_CVA_L9_Wr01(cva_int_sync_ctrl0, res_hsync, pstParams->hsync_delay);
				DE_CVA_L9_Wr01(cva_int_sync_ctrl0, res_hfp,   pstParams->hfp_delay);
				DE_CVA_L9_Wr01(cva_int_sync_ctrl1, res_vfp,   pstParams->vfp_delay);
				DE_CVA_L9_Wr01(cva_int_sync_ctrl1, res_vsync, pstParams->vsync_delay);
				DE_CVA_L9_WfCM(cva_int_sync_ctrl1, res_sync_sel,(pstParams->isEnable == FALSE), 0x1);
				DE_CVA_L9_WrFL(cva_int_sync_ctrl0);
				DE_CVA_L9_WrFL(cva_int_sync_ctrl1);
				break;
			case LX_DE_CVI_CH_B :
				DE_CVB_L9_RdFL(cvb_int_sync_ctrl0);
				DE_CVB_L9_RdFL(cvb_int_sync_ctrl1);
				DE_CVB_L9_Wr01(cvb_int_sync_ctrl0, res_hsync, pstParams->hsync_delay);
				DE_CVB_L9_Wr01(cvb_int_sync_ctrl0, res_hfp,   pstParams->hfp_delay);
				DE_CVB_L9_Wr01(cvb_int_sync_ctrl1, res_vfp,   pstParams->vfp_delay);
				DE_CVB_L9_Wr01(cvb_int_sync_ctrl1, res_vsync, pstParams->vsync_delay);
				DE_CVB_L9_WfCM(cvb_int_sync_ctrl1, res_sync_sel,(pstParams->isEnable == FALSE), 0x1);
				DE_CVB_L9_WrFL(cvb_int_sync_ctrl0);
				DE_CVB_L9_WrFL(cvb_int_sync_ctrl1);
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
	} while (0);

	return ret;
}

void DE_REG_L9_InitPeTPG(void)
{
	LX_DE_PE_COORDINATE_T coordinate[MAX_PE_TPG_RECT] = {
		{0, 0, 240, 1080}, {1680, 0, 1920, 1080}, // 1. LX_DE_NONACTIVE_4_3 Left 2. LX_DE_NONACTIVE_4_3 Right
		{0, 0, 1920, 1080}, // 3. LX_DE_WINBLANK_FULL
		{0, 0, 1920, 1080}, // 4. LX_DE_WINBLANK_FULL_BLUE
		{44, 212, 548, 582}, // 5. LX_DE_WINBLANK_WIN1_VCS
		{0, 0, 44, 1080}, {44, 990, 1800, 1080}, {1800, 0, 1920, 1080}, // 6. 7. 8.  LX_DE_SETWIN_VCS
		{0, 0, 160, 160}, // 9. TPD
		{160, 0, 320, 160}, // 10. 2D
		{0, 160, 160, 320},  // 11. 3D - CB
		{160, 160, 320, 320},  // 12. 3D - CC/LL
		{0, 160, 80, 320}, // 13. 3D - SS - L
		{80, 160, 160, 320}, // 14. 3D - SS - R
		{0, 160, 160, 240},  // 15. 3D - TB - T
		{0, 240, 160, 320}, // 16. 3D - TB - B
		{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}
	};
	LX_DE_COLOR_T color[MAX_PE_TPG_RECT] = {
		{0, 0, 0}, {0, 0, 0}, // 1. LX_DE_NONACTIVE_4_3 Left 2. LX_DE_NONACTIVE_4_3 Right
		{0, 0, 0}, // 3. LX_DE_WINBLANK_FULL
		{0, 0, 200}, // 4. LX_DE_WINBLANK_FULL_BLUE
		{0, 0, 0}, // 5. LX_DE_WINBLANK_WIN1_VCS
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, // 6. 7. 8. LX_DE_SETWIN_VCS
		{150, 0, 0}, // 9. TPD
		{0, 200, 200},		 // 10. 2D
		{255, 255, 255},	 // 11. 3D - CB
		{255, 0, 255},	   // 12. 3D - CC/LL
		{255, 0, 0},	 // 13. 3D - SS - L
		{0, 0, 255},	   // 14. 3D - SS - R
		{255, 0, 0},	   // 15. 3D - TB - T
		{0, 0, 255},		// 16. 3D - TB - B
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
	};

	UINT8 index;

	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
		DE_P1L_L9B0_RdFL(pe1_l_tpg_ctrl_00);
		DE_P1L_L9B0_Wr01(pe1_l_tpg_ctrl_00, tpg_enable, 0);
		DE_P1L_L9B0_WrFL(pe1_l_tpg_ctrl_00);

		DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_addr,  0);  // Patch color
		DE_P1L_L9B0_WrFL(pe1_l_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT_B0 ; index++)
		{
			DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_data, tpg_indir_data, color[index].g << 22 | color[index].b << 12 | color[index].r << 2);
			DE_P1L_L9B0_WrFL(pe1_l_tpg_ia_data);
		}

		DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_addr,  0x20);  // Patch start position
		DE_P1L_L9B0_WrFL(pe1_l_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT_B0 ; index++)
		{
			DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_data, tpg_indir_data, coordinate[index].x0 << 16 | coordinate[index].y0);
			DE_P1L_L9B0_WrFL(pe1_l_tpg_ia_data);
		}

		DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_addr,  0x40);  // Patch end position
		DE_P1L_L9B0_WrFL(pe1_l_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT_B0 ; index++)
		{
			DE_P1L_L9B0_Wr01(pe1_l_tpg_ia_data, tpg_indir_data, coordinate[index].x1 << 16 | coordinate[index].y1);
			DE_P1L_L9B0_WrFL(pe1_l_tpg_ia_data);
		}

		DE_P1L_L9B0_Wr01(pe1_l_tpg_ctrl_00, tpg_enable, 1);

		DE_P1L_L9B0_WrFL(pe1_l_tpg_ctrl_00);
	} else {
		DE_P1L_L9_RdFL(pe1_l_tpg_ctrl_00);
		DE_P1L_L9_Wr01(pe1_l_tpg_ctrl_00, tpg_enable, 0);
		DE_P1L_L9_WrFL(pe1_l_tpg_ctrl_00);

		DE_P1L_L9_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_L9_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_addr,  0);	// Patch color
		DE_P1L_L9_WrFL(pe1_l_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT ; index++)
		{
			DE_P1L_L9_Wr01(pe1_l_tpg_ia_data, tpg_indir_data, color[index].g << 22 | color[index].b << 12 | color[index].r << 2);
			DE_P1L_L9_WrFL(pe1_l_tpg_ia_data);
		}

		DE_P1L_L9_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_L9_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_addr,  0x20);  // Patch start position
		DE_P1L_L9_WrFL(pe1_l_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT ; index++)
		{
			DE_P1L_L9_Wr01(pe1_l_tpg_ia_data, tpg_indir_data, coordinate[index].x0 << 16 | coordinate[index].y0);
			DE_P1L_L9_WrFL(pe1_l_tpg_ia_data);
		}

		DE_P1L_L9_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_L9_Wr01(pe1_l_tpg_ia_ctrl, tpg_indir_addr,  0x40);  // Patch end position
		DE_P1L_L9_WrFL(pe1_l_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT ; index++)
		{
			DE_P1L_L9_Wr01(pe1_l_tpg_ia_data, tpg_indir_data, coordinate[index].x1 << 16 | coordinate[index].y1);
			DE_P1L_L9_WrFL(pe1_l_tpg_ia_data);
		}

		DE_P1L_L9_Wr01(pe1_l_tpg_ctrl_00, tpg_enable, 1);

		DE_P1L_L9_WrFL(pe1_l_tpg_ctrl_00);
	}

	g_b_InitTPG_L9 = TRUE;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief generate Test Pattern in PE region.
 *
 * @param [IN] structure pointer to carry information about PE gamma LUT region.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetPeTestPatternGen(LX_DE_PE_TPG_T *pstParams)
{
	int ret = RET_OK;

	if (!g_b_InitTPG_L9)
		DE_REG_L9_InitPeTPG();

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->eControl)
		{
			case LX_DE_TPG_CLEAR_ALL  :		// layer 를 모두  clear 할 필요 있음
				{
						g_patchEn_L9 = 0;

					break;
				}

			case LX_DE_NONACTIVE_4_3 :		// 중국향 대응 layer 순서 바꿈( blue full screen > black pillar box )
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFFFC;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000003;

					break;
				}

			case LX_DE_WINBLANK_FULL :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFFFB;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000004;

					break;
				}

			case LX_DE_WINBLANK_FULL_BLUE :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFFF7;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000008;

					break;
				}

			case LX_DE_WINBLANK_WIN1_VCS :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFFEF;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000010;

					break;
				}

			case LX_DE_NONACTIVE_VCS :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFF1F;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x000000E0;

					break;
				}

			case LX_DE_TPG_D3D_PTN :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFEFF;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000100;

					break;
				}
			case LX_DE_TPG_D3D_2D :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFDFF;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000200;

				break;
				}
			case LX_DE_TPG_D3D_CB :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFFBFF;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000400;

					break;
				}
			case LX_DE_TPG_D3D_CC :
			case LX_DE_TPG_D3D_LL :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFF7FF;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00000800;

				break;
				}
			case LX_DE_TPG_D3D_SS :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFFCFFF;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x00003000;

				break;
				}
			case LX_DE_TPG_D3D_TB :
				{
					g_patchEn_L9 = g_patchEn_L9 & 0xFFFF3FFF;

					if (pstParams->bOnOff)
						g_patchEn_L9 |= 0x0000C000;

				break;
				}
			default :
				break;
		}

		switch (pstParams->eControl)
		{
			case LX_DE_WINBLANK_FULL :
			case LX_DE_WINBLANK_FULL_BLUE :
			case LX_DE_WINBLANK_WIN1_VCS :
			case LX_DE_NONACTIVE_VCS :
			case LX_DE_NONACTIVE_4_3 :
				{
					if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
						DE_P1L_L9B0_FLWf(pe1_l_top_ctrl_02, tpg_positon, 1);
					} else {
						DE_P1L_L9_FLWf(pe1_l_top_ctrl_02, tpg_positon, 1);
					}
					break;
				}
/*
			case LX_DE_SETINNERPATTERN_R :
			case LX_DE_SETINNERPATTERN_G :
			case LX_DE_SETINNERPATTERN_B :
				{
					//DE_P1L_L9_RdFL(pe1_l_top_ctrl_02);
					DE_P1L_L9_FLWf(pe1_l_top_ctrl_02, tpg_positon, 0);
					//DE_P1L_L9_WrFL(pe1_l_top_ctrl_02);
					break;
				}
*/
			default :
				break;
		}

		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
			DE_P1L_L9B0_FLWf(pe1_l_tpg_ctrl_02, patch_en, g_patchEn_L9);
		} else {
			DE_P1L_L9_FLWf(pe1_l_tpg_ctrl_02, patch_en, g_patchEn_L9);
		}
	} while (0);

	return ret;
}
EXPORT_SYMBOL(DE_REG_L9_SetPeTestPatternGen);
/**
 * @callgraph
 * @callergraph
 *
 * @brief set edge crop
 *
 * @param [IN] structure pointer to carry infomation about PE0 black boundary detection status.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetEdgeCrop(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	do {
		;
	} while (0);
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set PE0 black boundary detection control.
 *
 * @param [IN] structure pointer to carry infomation about PE0 black boundary detection control.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_SetPeBbdCtrl(LX_DE_PE_BBD_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		DE_P0L_L9_RdFL(p0l_bbd_ctrl_00);
		DE_P0L_L9_Wr01(p0l_bbd_ctrl_00, hys_mode ,pstParams->hysterisis);
		DE_P0L_L9_Wr01(p0l_bbd_ctrl_00, cnt_th	 ,pstParams->cnt_th);
		DE_P0L_L9_Wr01(p0l_bbd_ctrl_00, diff_th  ,pstParams->diff_th);
		DE_P0L_L9_Wr01(p0l_bbd_ctrl_00, op_mode  ,0x0);    // assert auto boundary detection
		DE_P0L_L9_Wr01(p0l_bbd_ctrl_00, bbd_mux  ,0x1);    // New register from L9A0
#ifdef USE_PQL_REG_DEFINED_IN_DE
		DE_P0L_L9_WfCM(p0l_bbd_ctrl_00, bbd_en	 ,(TRUE==pstParams->isOn) ,0x1);
#endif
		DE_P0L_L9_WrFL(p0l_bbd_ctrl_00);

	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get PE0 black boundary detection status.
 *
 * @param [IN] structure pointer to carry infomation about PE0 black boundary detection status.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_L9_GetPeBbdStatus(LX_DE_PE_COORDINATE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		DE_P0L_L9_RdFL(p0l_bbd_stat_00);
		DE_P0L_L9_RdFL(p0l_bbd_stat_01);

		DE_P0L_L9_Rd01(p0l_bbd_stat_00, x0 ,pstParams->x0);
		DE_P0L_L9_Rd01(p0l_bbd_stat_00, y0 ,pstParams->y0);
		DE_P0L_L9_Rd01(p0l_bbd_stat_01, x1 ,pstParams->x1);
		DE_P0L_L9_Rd01(p0l_bbd_stat_01, y1 ,pstParams->y1);
	} while (0);

	return ret;
}

int DE_REG_L9_ResetDE(BOOLEAN bReset)
{
	int ret = RET_OK;

#ifdef USE_DE_DOES_RESET_IN_SUSPEND_RESUME
	bReset = (bReset)?TRUE:FALSE;
#ifdef	USE_CTOP_CODES_FOR_L9
	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
		CTOP_CTRL_L9B_FLWr(ctr05_swrs_of_de, bReset?GET_PMSK(0,32):0);
		CTOP_CTRL_L9B_RdFL(ctr06_swrst);
		CTOP_CTRL_L9B_WfCM(ctr06_swrst, swrst_de_vd   ,bReset, 1);
		CTOP_CTRL_L9B_WfCM(ctr06_swrst, swrst_de_apb  ,bReset, 1);
		CTOP_CTRL_L9B_WfCM(ctr06_swrst, swrst_cvda	  ,bReset, 1);
		CTOP_CTRL_L9B_WrFL(ctr06_swrst);
	} else {
		CTOP_CTRL_L9A_RdFL(ctr06);
		CTOP_CTRL_L9A_WfCM(ctr06, swrst_de_dp  ,bReset, 1);
		CTOP_CTRL_L9A_WfCM(ctr06, swrst_de_de  ,bReset, 1);
		CTOP_CTRL_L9A_WfCM(ctr06, swrst_cvda   ,bReset, 1);
		CTOP_CTRL_L9A_WfCM(ctr06, swrst_de_dp  ,bReset, 1);
		CTOP_CTRL_L9A_WfCM(ctr06, swrst_dea    ,bReset, 1);
		CTOP_CTRL_L9A_WfCM(ctr06, swrst_de_apb ,bReset, 1);
		CTOP_CTRL_L9A_WrFL(ctr06);
	}
#endif
#endif
	return ret;
}

BOOLEAN DE_REG_L9_IPCisAlive(void)
{
	BOOLEAN isFwDownloaded = FALSE;
	DE_IPC_L9_FLRf(int_intr_enable, ipc_interrupt_enable_mcu, isFwDownloaded);
#ifdef USE_IPC_CONTROL_INTERRUPT_A_BIT
	return isFwDownloaded;
#else
	return GET_BITS(isFwDownloaded, 29, 1);
#endif
	//return gpRealRegSPP_MCU->int_interrupt_enable.ipc_intterupt_enalbe_108;
}

int DE_REG_L9_OIF_InitLvdsIfCtrl(void)
{
	DE_OIF_L9_RdFL(lvds_if_control);
	DE_OIF_L9_Wr01(lvds_if_control, lvds_ch2_from,	 2);
	DE_OIF_L9_Wr01(lvds_if_control, lvds_ch1_from,	 1);
	DE_OIF_L9_WrFL(lvds_if_control);

	return RET_OK;
}

int DE_REG_L9_SetPwmFreerun(void)
{
	int ret = RET_OK;
	LX_DE_PWM_FREQ_T freq_param;
	LX_DE_PWM_PARAM_T duty_param;
	UINT32 i;

	do {
		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
			for(i=0;i<PWM_NUM_MAX;i++)
			{
				freq_param.port		 = i;
				freq_param.frequency = gVideoPwmInfo[i].freq;
				if(!freq_param.frequency)
					continue;

				duty_param.port		 = i;
				duty_param.duty		 = gVideoPwmInfo[i].duty;
				duty_param.offset	 = gVideoPwmInfo[i].offs;
				if(!duty_param.duty)
					continue;

				if(gVideoPwmInfo[i].ctrl.pwm_method == PWM_FREE_OFF)
				{
					DE_PWM_SetCtrl(i, PWM_CTRL_FRE, PWM_FREE_ON);
					DE_REG_L9_SetPwmFrequency(&freq_param);
					DE_REG_L9_SetPwmDutyCycle(&duty_param);

					DE_PWM_SetCtrl(i, PWM_CTRL_FRE, PWM_FREE_OFF);
					DE_REG_L9_SetPwmFrequency(&freq_param);
				}
			}
		}
	} while(0);

	return ret;
}

int DE_REG_L9_SetPwmControl(LX_DE_PWM_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {

			DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_ENB, pstParams->enable); // force to high
			if(!pstParams->enable)
				break;
			switch (pstParams->PWMOutput)
			{
				case LX_DE_PWM_LOW :
					DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_LOW, TRUE);
					break;
				case LX_DE_PWM_NORMAL :
					DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_LOW, FALSE);
					DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_HIG, FALSE);
					DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_INV, FALSE);
					break;
				case LX_DE_PWM_HIGH :
					DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_HIG, TRUE);
					break;
				case LX_DE_PWM_INVERSION :
					DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_INV, TRUE);
					break;
				default :
					BREAK_WRONG(pstParams->PWMOutput);
			}

			DE_PWM_SetCtrl(pstParams->port, PWM_CTRL_FRE, (pstParams->pwmMode)?PWM_FREE_ON:PWM_FREE_OFF);
		}
	} while(0);

	return ret;
}

int DE_REG_L9_SetPwmDutyCycle(LX_DE_PWM_PARAM_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	UINT32 ordr;
	UINT32 offs;
	UINT32 high;
	UINT32 falt;
	UINT32 unit_pixel;

	do {
		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {

			if(pstParams->duty > PWM_DUTY_MAX)
				break;
			gVideoPwmInfo[pstParams->port].duty = pstParams->duty;
			gVideoPwmInfo[pstParams->port].offs = pstParams->offset;

			unit_pixel = gVideoPwmInfo[pstParams->port].pxls / gVideoPwmInfo[pstParams->port].unit;
			ordr	   = gVideoPwmInfo[pstParams->port].ordr;

			if((pstParams->offset + pstParams->duty) > PWM_DUTY_MAX)
				BREAK_WRONG(pstParams->offset);

			for(i=PWM_ORD_1ST;i<ordr+1;i++)
			{
				offs = (unit_pixel * ((pstParams->offset*100)/PWM_DUTY_MAX))/100;
				high = (unit_pixel * ((pstParams->duty*100)/PWM_DUTY_MAX))/100;
				falt = offs + high;

				//DE_PRINT("Port[%d] : ordr[%d] -  unit_pixel[%d] offs[%d] falt[%d] high[%d] \n", pstParams->port, i, unit_pixel, offs, falt, high);

				ret = DE_PWM_SetTiming(pstParams->port, i, &offs, &falt, &offs);
				if(ret) break;
			}
			ret = DE_PWM_SetRegCtrl(pstParams->port);
		}
	} while(0);

	return ret;
}

int DE_REG_L9_GetPwmDutyCycle(LX_DE_EXTERNAL_PWM_T *pstParams)
{
	int ret = RET_OK;
	UINT32 freq_mode = 0;
	UINT32 time_low[4] = { 0 };
	UINT32 time_high[4] = { 0 };
	UINT32 i=0, iteration=0;
	UINT32 duty = 0, duty_sum = 0;
	static UINT16 prev_freq = 0;

	do {
		CHECK_KNULL(pstParams);
		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
			switch (pstParams->frequency)
			{
				case 48 :
				case 50 :
				case 60 :
					freq_mode = PWM_FREQ_60HZ;
					iteration = 1;
					break;
				case 96 :
				case 100 :
				case 120 :
					freq_mode = PWM_FREQ_120HZ;
					iteration = 2;
					break;
				case 192 :
				case 200 :
				case 240 :
					freq_mode = PWM_FREQ_240HZ;
					iteration = 4;
					break;
				default :
					freq_mode = PWM_FREQ_120HZ;
					iteration = 2;
					break;
			}

			if(prev_freq != pstParams->frequency)
			{
				 ret = DE_PWM_SetCtrl(PWM_NUM_ID3, PWM_CTRL_FRQ, freq_mode);
				 if(ret) break;
				 ret = DE_PWM_SetRegCtrl(PWM_NUM_ID3);
				 if(ret) break;
			}
			prev_freq = pstParams->frequency;

			for(i=0;i<iteration;i++)
			{
				DE_PWM_GetTiming(i, &time_low[i], &time_high[i]);
				if(time_low[i] == 0 && time_high[i] == 0)
				{
					//DE_PRINT("%s : low & high are zero  (ord %d)\n", __F__, i);
					pstParams->duty = 0;
					break;
				}
				duty = (time_high[i] * 1023) / (time_low[i] + time_high[i]);
				duty_sum += duty;
				//DE_PRINT("%d : high[%d] low[%d] -> duty[%d]\n", i, time_high[i], time_low[i], duty);
			}
			pstParams->duty = duty_sum/iteration;
			//DE_PRINT("avg duty[%d]\n", duty_sum/iteration);
		}
	} while(0);

	return ret;
}

int DE_REG_L9_SetPwmFrequency(LX_DE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_PWM_PARAM_T stParams;

	do {
		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {

			gVideoPwmInfo[pstParams->port].unit = 1024;
			gVideoPwmInfo[pstParams->port].freq = pstParams->frequency;

			if( gVideoPwmInfo[pstParams->port].ctrl.pwm_method == PWM_FREE_OFF ) // locking mode
			{
				switch ( pstParams->frequency )
				{
					case 384 :
					case 400 :
					case 480 :
						gVideoPwmInfo[pstParams->port].ordr				  = PWM_ORD_8TH;
						gVideoPwmInfo[pstParams->port].pxls				  = 309000;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 3;
						break;
					case 192 :
					case 200 :
					case 240 :
						gVideoPwmInfo[pstParams->port].ordr				  = PWM_ORD_4TH;
						gVideoPwmInfo[pstParams->port].pxls				  = 628000;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 2;
						break;
					case 96 :
					case 100 :
					case 120 :
						gVideoPwmInfo[pstParams->port].ordr				  = PWM_ORD_2ND;
						gVideoPwmInfo[pstParams->port].pxls				  = 1237000;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 1;
						break;
					case 48 :
					case 50 :
					case 60 :
						gVideoPwmInfo[pstParams->port].ordr				  = PWM_ORD_1ST;
						gVideoPwmInfo[pstParams->port].pxls				  = 2475000;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 0;
						break;
					case 24 :
					case 25 :
					case 30 :
						gVideoPwmInfo[pstParams->port].ordr               = PWM_ORD_1ST;
						//gVideoPwmInfo[pstParams->port].pxls               = 2475000;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_method    = TRUE;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 0;
						break;
					case 180 :
					case 160 :
					default :
						gVideoPwmInfo[pstParams->port].ordr				  = PWM_ORD_1ST;
						gVideoPwmInfo[pstParams->port].pxls				  = 2475000 * 60 / pstParams->frequency;
						gVideoPwmInfo[pstParams->port].ctl1.pwm_free_width= 2475000 * 60 / pstParams->frequency;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_method	  = TRUE;
						gVideoPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 0;
						break;
				}

				{
					/*
					 * h      = hactive + hsync + h_bp + h_fp
					 * v      = vactive + vsync + v_bp + v_fp
					 * pixels = h * v
					 *
					 * result ->
					 * 60_h   = 1920    + 44    + 148  + 88   = 2200
					 * 60_v   = 1080    +  5    + 36   + 4    = 1125
					 *    h*v = 2475000
					 * 50_h   = 1920    + 44    + 148  + 88   = 2200
					 * 50_v   = 1080    +  5    + 36   + 229  = 1350
					 *    h*v = 2970000
					 * 48_h   = 1920    + 44    + 148  + 638  = 2750
					 * 48_v   = 1080    +  5    + 36   + 4    = 1125
					 *    h*v = 3093750
					 *
					 *    for UD (3820x2160 30p,25p,24p)
					 * 30_h   = 1920    + 44    + 88   + 72   = 2124
					 * 30_v   = 2160    + 148   + 10   + 8    = 2326
					 *    h*v = 4940424
					 * 25_h   = 1920    + 44    + 88   + 72   = 2124
					 * 25_v   = 2160    + 148   + 10   + 458  = 2776
					 *    h*v = 5896224
					 * 24_h   = 1920    + 44    + 638  + 72   = 2674
					 * 24_v   = 2160    + 148   + 10   + 8    = 2326
					 *    h*v = 6219724

					 */
					#define PWM_PIXELS_60HZ	2475000
					#define PWM_PIXELS_50HZ	2970000
					#define PWM_PIXELS_48HZ	3093750
					#define PWM_PIXELS_30HZ 4940424
					#define PWM_PIXELS_25HZ 5896224
					#define PWM_PIXELS_24HZ 6219724
					switch ( pstParams->frequency )
					{
						case 384 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 3; break;
						case 400 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 3; break;
						case 480 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 3; break;
						case 192 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 2; break;
						case 200 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 2; break;
						case 240 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 2; break;
						case  96 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 1; break;
						case 100 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 1; break;
						case 120 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 1; break;
						case  48 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 0; break;
						case  50 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 0; break;
						case  60 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 0; break;
						case  30 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_30HZ >> 0; break;
						case  25 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_25HZ >> 0; break;
						case  24 : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_24HZ >> 0; break;
						default  : gVideoPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 0; break;
					}
				}
			}
			else	// freeeun mode
			{
				gVideoPwmInfo[pstParams->port].ordr				   = PWM_ORD_1ST;
				gVideoPwmInfo[pstParams->port].pxls				   = 2475000 * 60 / pstParams->frequency;
				gVideoPwmInfo[pstParams->port].ctl1.pwm_free_width = 2475000 * 60 / pstParams->frequency;
				gVideoPwmInfo[pstParams->port].ctrl.pwm_method	   = TRUE;
				gVideoPwmInfo[pstParams->port].ctrl.pwm_freq_mode  = 0;
			}

			stParams.port	= pstParams->port;
			stParams.offset = gVideoPwmInfo[pstParams->port].offs;
			stParams.duty	= gVideoPwmInfo[pstParams->port].duty;
			ret = DE_REG_L9_SetPwmDutyCycle(&stParams);
		}
	} while(0);

	return ret;
}

int DE_REG_L9_SetPwmPulseWidth(LX_DE_PWM_PULSE_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_L9_Set3DFullMode(LX_DE_3D_FULL_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sbDe3DFullMode = (LX_DE_3D_FULL_OFF != *pstParams)?TRUE:FALSE;
		ret = DE_REG_L9_SetCviSrc();
		if(ret != RET_OK) break;
		if(sbDe3DFullMode)
		sCviSrcType.cvi_channel = LX_DE_CVI_CH_B;
		ret = DE_REG_L9_SetCviSrcType(&sCviSrcType);
	} while (0);

	return ret;
}

int DE_REG_L9_SetUdMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sbDeUdMode = (*pstParams)?TRUE:FALSE;
		ret = DE_REG_L9_SetCviSrc();
		if(ret != RET_OK) break;
		if(sbDeUdMode)
		sCviSrcType.cvi_channel = LX_DE_CVI_CH_B;
		ret = DE_REG_L9_SetCviSrcType(&sCviSrcType);
	} while (0);

	return ret;
}

int DE_REG_L9_SetFrameToOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = VIDEO_L9_FIRMWARE_MEM_BASE_WEB_OS;
	} while (0);

	return ret;
}

int DE_REG_L9_SetLAMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
#ifdef USE_COLUMN_ALTERNATIVE_HALF_CLOCK
		if (*pstParams) sCviSrcType.sampling = LX_DE_CVI_DOUBLE_SAMPLING;
#endif
		sCviSrcType.cvi_channel = LX_DE_CVI_CH_A;
		ret = DE_REG_L9_SetCviSrcType(&sCviSrcType);
		if (ret) break;
		sCviSrcType.cvi_channel = LX_DE_CVI_CH_B;
		ret = DE_REG_L9_SetCviSrcType(&sCviSrcType);

	} while (0);

	return ret;
}
int DE_REG_L9_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sDeMultiWinSrc = *pstParams;
		ret = DE_REG_L9_SetCviSrc();
	} while (0);

	return ret;
}

int DE_REG_L9_SetCviSrc(void)
{
	int ret = RET_OK;
	BOOLEAN bUd3DMode;
	BOOLEAN bCviA, bCviB;

	do {
		bUd3DMode = TRUE;
		if (sbDe3DFullMode) break;
		if (sbDeUdMode) break;
		bUd3DMode = FALSE;
		ret = DE_REG_L9_SetMultiWinSrc(&sDeMultiWinSrc);
	} while (0);

	do {
		if (!bUd3DMode) break;
		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
			DE_DEE_L9B_RdFL(dee_cvi_mux_sel);
			DE_DEE_L9B_Rd01(dee_cvi_mux_sel, cvia_sel, bCviA);
			DE_DEE_L9B_Rd01(dee_cvi_mux_sel, cvib_sel, bCviB);

			if (bCviA != 0 || bCviB != 1)
			{
				DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvia_sel, 0);
				DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvib_sel, 1);
				DE_DEE_L9B_WrFL(dee_cvi_mux_sel);
			}
		}
		else if ( lx_chip_rev() >= LX_CHIP_REV(L9,A1) ) {
			DE_DEE_L9A_FLWf(dee_cvi_mux_sel, cvi_mux_sel, 3);
			CTOP_CTRL_L9A_RdFL(ctr26);
			CTOP_CTRL_L9A_Wr01(ctr26, exta_sel, 1);
			CTOP_CTRL_L9A_Wr01(ctr26, extb_sel, 2);
			CTOP_CTRL_L9A_WrFL(ctr26);
		} else {
			DE_DEE_L9A_FLWf(dee_cvi_mux_sel, cvi_mux_sel, 3);
			CTOP_CTRL_L9A_RdFL(ctr26);
			CTOP_CTRL_L9A_Wr01(ctr26, exta_sel, 2);
			CTOP_CTRL_L9A_Wr01(ctr26, extb_sel, 1);
			CTOP_CTRL_L9A_WrFL(ctr26);
		}
	} while (0);

	return ret;
}

/**
 * mapping input port and de cvi source
 */
int DE_REG_L9_SetMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_MULTI_SRC_T multiSrc = LX_DE_MULTI_IN_MAX;
	LX_DE_SRC_CONFIG  *src_cfg = NULL;
	LX_DE_WIN_ID_T win_id = LX_DE_WIN_MAIN;
	LX_DE_INPUT_PORT in_port = LX_DE_PORT_MVI;
	UINT32 cvi_mux_sel = 0;
	UINT32 exta_sel = 0;
	UINT32 extb_sel = 0;
	UINT32 i = 0;


	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
		src_cfg = sMultiSrc_map_L9[3];
	}

	else if ( lx_chip_rev() >= LX_CHIP_REV(L9,A1) ) {
		src_cfg = sMultiSrc_map_L9[2];
	}
#ifdef L9_KDRV_EVAL_ENV
	else if (lx_chip_rev() >= LX_CHIP_REV(L9,A0) ) {
		src_cfg = sMultiSrc_map_L9[0];
	}
#endif
	else if (lx_chip_rev() >= LX_CHIP_REV(L9,A0) ) {
		src_cfg = sMultiSrc_map_L9[1];
	}
	do {
		CHECK_KNULL(src_cfg);
		CHECK_KNULL(pstParams);
		win_id = pstParams->win_id;
		in_port = pstParams->in_port;

		switch (win_id)
		{
			case LX_DE_WIN_MAIN :
				{
					if(in_port == g_WinSrc_L9[LX_DE_WIN_MAIN]) return ret;

					if(in_port == LX_DE_PORT_CVD)
					{
						switch (g_WinSrc_L9[LX_DE_WIN_SUB]) {
							case LX_DE_PORT_ADC :
								multiSrc = LX_DE_MULTI_IN_CVD_ADC;
								break;
							case LX_DE_PORT_HDMI :
								multiSrc = LX_DE_MULTI_IN_CVD_HDMI;
								break;
							case LX_DE_PORT_CVD :
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_CVD_MVI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_PORT_ADC)
					{
						switch (g_WinSrc_L9[LX_DE_WIN_SUB]) {
							case LX_DE_PORT_CVD :
								multiSrc = LX_DE_MULTI_IN_ADC_CVD;
								break;
							case LX_DE_PORT_HDMI :
								multiSrc = LX_DE_MULTI_IN_ADC_HDMI;
								break;
							case LX_DE_PORT_ADC :
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_ADC_MVI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_PORT_HDMI)
					{
						switch (g_WinSrc_L9[LX_DE_WIN_SUB]) {
							case LX_DE_PORT_CVD :
								multiSrc = LX_DE_MULTI_IN_HDMI_CVD;
								break;
							case LX_DE_PORT_ADC :
								multiSrc = LX_DE_MULTI_IN_HDMI_ADC;
								break;
							case LX_DE_PORT_HDMI :
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_HDMI_MVI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_PORT_MVI)
					{
						switch (g_WinSrc_L9[LX_DE_WIN_SUB]) {
							case LX_DE_PORT_CVD :
								multiSrc = LX_DE_MULTI_IN_MVI_CVD;
								break;
							case LX_DE_PORT_ADC :
								multiSrc = LX_DE_MULTI_IN_MVI_ADC;
								break;
							case LX_DE_PORT_HDMI :
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_HDMI;
								break;
							default :
								break;
						}
					}

					g_WinSrc_L9[LX_DE_WIN_MAIN] = in_port;
				}
				break;
			case LX_DE_WIN_SUB :
				{
					if(in_port == g_WinSrc_L9[LX_DE_WIN_SUB]) return ret;

					if(in_port == LX_DE_PORT_CVD)
					{
						if ( lx_chip_rev() == LX_CHIP_REV(L9,A1) ) {
							DE_PRINT("Not supported path on A1\n");
						}
						switch (g_WinSrc_L9[LX_DE_WIN_MAIN]) {
							case LX_DE_PORT_ADC :
								multiSrc = LX_DE_MULTI_IN_ADC_CVD;
								break;
							case LX_DE_PORT_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_CVD;
								break;
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_CVD;
								break;
							case LX_DE_PORT_CVD :
								multiSrc = LX_DE_MULTI_IN_CVD_CVD;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_PORT_ADC)
					{
						switch (g_WinSrc_L9[LX_DE_WIN_MAIN]) {
							case LX_DE_PORT_CVD :
								multiSrc = LX_DE_MULTI_IN_CVD_ADC;
								break;
							case LX_DE_PORT_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_ADC;
								break;
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_ADC;
								break;
							case LX_DE_PORT_ADC :
								multiSrc = LX_DE_MULTI_IN_ADC_ADC;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_PORT_HDMI)
					{
						switch (g_WinSrc_L9[LX_DE_WIN_MAIN]) {
							case LX_DE_PORT_CVD :
								multiSrc = LX_DE_MULTI_IN_CVD_HDMI;
								break;
							case LX_DE_PORT_ADC :
								multiSrc = LX_DE_MULTI_IN_ADC_HDMI;
								break;
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_HDMI;
								break;
							case LX_DE_PORT_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_HDMI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_PORT_MVI)
					{
						switch (g_WinSrc_L9[LX_DE_WIN_MAIN]) {
							case LX_DE_PORT_CVD :
								multiSrc = LX_DE_MULTI_IN_CVD_MVI;
								break;
							case LX_DE_PORT_ADC :
								multiSrc = LX_DE_MULTI_IN_ADC_MVI;
								break;
							case LX_DE_PORT_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_MVI;
								break;
							case LX_DE_PORT_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_MVI;
								break;
							default :
								break;
						}
					}

					g_WinSrc_L9[LX_DE_WIN_SUB] = in_port;
				}
				break;
			default :
				BREAK_WRONG(win_id);
		}
		if (ret) break;

		for (i = LX_DE_MULTI_IN_CVD_ADC; i < LX_DE_MULTI_IN_MAX; i++)
		{
			if (src_cfg[i].src != multiSrc) continue;
			if (src_cfg[i].used != TRUE) BREAK_WRONG(multiSrc);

			cvi_mux_sel = src_cfg[i].cvi_mux_sel;
			exta_sel = src_cfg[i].exta_sel;
			extb_sel = src_cfg[i].extb_sel;
		}

		if (multiSrc >= LX_DE_MULTI_IN_MAX)
		{
			ret = RET_ERROR;
			DE_PRINT("\nInvalid mapping \n\n");
		}

		DE_PRINT("win_id[%d] in_port[%d] main/sub[%d/%d] (in_port => MVI/CVD/ADC/HDMI:0/1/2/3)\n", win_id, in_port, g_WinSrc_L9[LX_DE_WIN_MAIN], g_WinSrc_L9[LX_DE_WIN_SUB]);
		DE_PRINT("cvi_mux_sel[%d] exta_sel[%d] extb_sel[%d]\n", cvi_mux_sel, exta_sel, extb_sel);

		if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
			DE_DEE_L9B_RdFL(dee_cvi_mux_sel);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvd_input_sel, cvi_mux_sel);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvia_sel, exta_sel);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvib_sel, extb_sel);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, exta_type, 0);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, extb_type, 0);
			DE_DEE_L9B_WrFL(dee_cvi_mux_sel);
		} else {
			DE_DEE_L9A_FLWf(dee_cvi_mux_sel, cvi_mux_sel, cvi_mux_sel);

			CTOP_CTRL_L9A_RdFL(ctr26);
			CTOP_CTRL_L9A_Wr01(ctr26, exta_sel, exta_sel);
			CTOP_CTRL_L9A_Wr01(ctr26, extb_sel, extb_sel);
			CTOP_CTRL_L9A_WrFL(ctr26);
		}
	} while(0);

	return ret;
}

int DE_REG_L9_Set_SCART_RGB_Bypass_Mode(int Bypass_Enable)
{
	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
		if (Bypass_Enable > 0) {

			DE_DEE_L9B_RdFL(dee_cvi_mux_sel);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvd_input_sel, cvi_mux_sel);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvd_input_sel, 0);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvia_sel, 1);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvib_sel, extb_sel);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, exta_type, 0);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, extb_type, 0);
			DE_DEE_L9B_WrFL(dee_cvi_mux_sel);
			CTOP_CTRL_L9B_RdFL(ctr26_extclk_div_sel);
			CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, exta_sel, 1);
			//CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, extb_sel, 1);
			CTOP_CTRL_L9B_WrFL(ctr26_extclk_div_sel);

		} else {

			DE_DEE_L9B_RdFL(dee_cvi_mux_sel);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvd_input_sel, cvi_mux_sel);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvd_input_sel, 0);
			DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvia_sel, 2);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, cvib_sel, extb_sel);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, exta_type, 0);
			//DE_DEE_L9B_Wr01(dee_cvi_mux_sel, extb_type, 0);
			DE_DEE_L9B_WrFL(dee_cvi_mux_sel);
			CTOP_CTRL_L9B_RdFL(ctr26_extclk_div_sel);
			CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, exta_sel, 0);
			//CTOP_CTRL_L9B_Wr01(ctr26_extclk_div_sel, extb_sel, 1);
			CTOP_CTRL_L9B_WrFL(ctr26_extclk_div_sel);

		}
	}
	return 0;
}
/**
 * get cvi source information
 */
int DE_REG_L9_GetCviInfo(LX_DE_CVI_INFO_T *pstParams)
{
	int ret = RET_OK;
	UINT32 line_num = 0;
	UINT32 line_width = 0;

	do {
		CHECK_KNULL(pstParams);
		switch (pstParams->win_id) {
			case LX_DE_WIN_MAIN :
				if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
					DE_CVA_L9B_RdFL(cva_size_detect_read);
					DE_CVA_L9B_Rd01(cva_size_detect_read, line_num_read, line_num);
					DE_CVA_L9B_Rd01(cva_size_detect_read, line_width_read, line_width);
				} else {
					DE_CVA_L9_RdFL(cva_size_detect_read);
					DE_CVA_L9_Rd01(cva_size_detect_read, line_num_read, line_num);
					DE_CVA_L9_Rd01(cva_size_detect_read, line_width_read, line_width);
				}
				break;
			case LX_DE_WIN_SUB :
				if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
					DE_CVB_L9B_RdFL(cvb_size_detect_read);
					DE_CVB_L9B_Rd01(cvb_size_detect_read, line_num_read, line_num);
					DE_CVB_L9B_Rd01(cvb_size_detect_read, line_width_read, line_width);
				} else {
					DE_CVB_L9_RdFL(cvb_size_detect_read);
					DE_CVB_L9_Rd01(cvb_size_detect_read, line_num_read, line_num);
					DE_CVB_L9_Rd01(cvb_size_detect_read, line_width_read, line_width);
				}
				break;
			default :
				BREAK_WRONG(pstParams->win_id);
		}

		pstParams->line_num		= line_num;
		pstParams->line_width	= line_width;

		if( line_num == 0 )
		{
			pstParams->fr_rate = 9999;
		}
		else
		{
			pstParams->fr_rate = (UINT16)(1980000000 / (line_num * 1024));

			if( pstParams->fr_rate > 1200 ) //120Hz
				pstParams->fr_rate = 1200;
		}
	}while(0);

	return ret;
}

/**
 * get debug data
 */
int DE_REG_L9_GetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;


	return ret;
}

/**
 * set debug data
 */
int DE_REG_L9_SetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;

#ifndef USE_DE_CVI_DELAY_ON_MCU_PART
	UINT32 line_width = 0;
	UINT32 syncPosition = 0;
#endif

	do {
		CHECK_KNULL(pstParams);
		switch (pstParams->type) {
			case LX_DE_DBG_PIXEL_SHIFT :
#ifndef USE_DE_CVI_DELAY_ON_MCU_PART
				{
					if (pstParams->win_id == 0)
					{
						if (pstParams->bParam == 1)
						{
							DE_CVA_L9_RdFL(cva_top_ctrl);
							DE_CVA_L9_Wr01(cva_top_ctrl, yc_delay_mode_r, 1);
							DE_CVA_L9_Wr01(cva_top_ctrl, yc_delay_mode_g, 3);
							DE_CVA_L9_Wr01(cva_top_ctrl, yc_delay_mode_b, 3);
							DE_CVA_L9_WrFL(cva_top_ctrl);
						}
						else
						{
							DE_CVA_L9_RdFL(cva_top_ctrl);
							DE_CVA_L9_Wr01(cva_top_ctrl, yc_delay_mode_r, 0);
							DE_CVA_L9_Wr01(cva_top_ctrl, yc_delay_mode_g, 0);
							DE_CVA_L9_Wr01(cva_top_ctrl, yc_delay_mode_b, 0);
							DE_CVA_L9_WrFL(cva_top_ctrl);
						}
					}
					else
					{
						if (pstParams->bParam == 1)
						{
							DE_CVB_L9_RdFL(cvb_top_ctrl);
							DE_CVB_L9_Wr01(cvb_top_ctrl, yc_delay_mode_r, 0x1);
							DE_CVB_L9_Wr01(cvb_top_ctrl, yc_delay_mode_g, 0x3);
							DE_CVB_L9_Wr01(cvb_top_ctrl, yc_delay_mode_b, 0x3);
							DE_CVB_L9_WrFL(cvb_top_ctrl);
						}
						else
						{
							DE_CVB_L9_RdFL(cvb_top_ctrl);
							DE_CVB_L9_Wr01(cvb_top_ctrl, yc_delay_mode_r, 0x0);
							DE_CVB_L9_Wr01(cvb_top_ctrl, yc_delay_mode_g, 0x0);
							DE_CVB_L9_Wr01(cvb_top_ctrl, yc_delay_mode_b, 0x0);
							DE_CVB_L9_WrFL(cvb_top_ctrl);
						}
					}
				}
#endif
				break;

			case LX_DE_DBG_SYNC_POSITION :
#ifndef USE_DE_CVI_DELAY_ON_MCU_PART
				{
					if (pstParams->win_id == 0)
					{
						if (pstParams->bParam == 1)
						{
							DE_CVA_L9B_RdFL(cva_size_detect_read);
							DE_CVA_L9B_Rd01(cva_size_detect_read, line_width_read, line_width);
							syncPosition = pstParams->u32Param - pstParams->u32ParamOne; // vTotal - vActive
							//printk("DE_REG_L9_SetDebug (vTotal(%d) vActive(%d) syncPosition(%d) line_width(%d) \n", pstParams->u32Param, pstParams->u32ParamOne, syncPosition, line_width);
							syncPosition = ( syncPosition * line_width ) >> 3;
						}
						else
						{
							syncPosition = 0;
						}

						DE_DEA_L9B_RdFL(dea_msrc_sync_dly);
						DE_DEA_L9B_Wr01(dea_msrc_sync_dly, dea_msrc_sync_dly, syncPosition);
						DE_DEA_L9B_WrFL(dea_msrc_sync_dly);
						//printk("DE_REG_L9_SetDebug syncPosition =%d \n", syncPosition);
					}
					else
					{
						if (pstParams->bParam == 1)
						{
							DE_CVB_L9B_RdFL(cvb_size_detect_read);
							DE_CVB_L9B_Rd01(cvb_size_detect_read, line_width_read, line_width);
							syncPosition = pstParams->u32Param - pstParams->u32ParamOne; // vTotal - vActive
							syncPosition = ( syncPosition * line_width ) >> 3;
						}
						else
						{
							syncPosition = 0;
						}

						DE_DEC_L9B_RdFL(dec_msrc_sync_dly);
						DE_DEC_L9B_Wr01(dec_msrc_sync_dly, dec_msrc_sync_dly, syncPosition);
						DE_DEC_L9B_WrFL(dec_msrc_sync_dly);
					}
				}
#endif
				break;
			case LX_DE_DBG_CVI_RESET :			// ON MCU Part
			default :
				break;
		}
	} while (0);
	return ret;
}

int DE_REG_L9_SetTtx(VIDEO_TTX_PACK_T *pTtxPack)
{
	int ret = RET_OK;
	LX_DE_CH_MEM_T	 *pFwMem = NULL;
	VIDEO_TTX_BUFF_T *gpVideoTtxBuff = NULL;
	UINT32 wInx;

	do {
		CHECK_KNULL(pTtxPack);
		pFwMem = &gpDeMem->fw[2];
		CHECK_KNULL(pFwMem);
		gpVideoTtxBuff = ioremap(pFwMem->fw_base + CONV_ROW2BYTE(VIDEO_L9_FIRMWARE_ROW_OFST_OF_TTX), sizeof(VIDEO_TTX_BUFF_T));
		CHECK_KNULL(gpVideoTtxBuff);

		wInx = gpVideoTtxBuff->wInx;
		wInx++; wInx %= gpVideoTtxBuff->iMax;
		//if (gpVideoTtxBuff->rInx==wInx) break;
		gpVideoTtxBuff->wInx = wInx;
		gpVideoTtxBuff->ttxPack[wInx] = *pTtxPack;
	} while (0);
	if (gpVideoTtxBuff) iounmap((void *)gpVideoTtxBuff);
	return ret;
}

#ifdef USE_PWM_RUN_IN_KDRIVER
DTV_STATUS_T DE_PWM_InitCtrl(void)
{
	DTV_STATUS_T ret = RET_OK;
	UINT32 pwmId;

	for (pwmId=0;pwmId<PWM_NUM_MAX;pwmId++) {
		gVideoPwmInfo[pwmId].ctrl.pwm_en				 = FALSE;
		gVideoPwmInfo[pwmId].ctrl.pwm_freq_mode			 = PWM_FREQ_60HZ;
		gVideoPwmInfo[pwmId].ctrl.pwm_method			 = PWM_FREE_OFF;
		gVideoPwmInfo[pwmId].ctrl.pwm_resolution		 = PWM_RES_1024;
		gVideoPwmInfo[pwmId].ctrl.pwm_inv				 = FALSE;
		gVideoPwmInfo[pwmId].ctrl.pwm_sel				 = PWM_MODE_DUTY;
		gVideoPwmInfo[pwmId].ctrl.pwm_width_falling_pos  = 0;
		gVideoPwmInfo[pwmId].ctrl.pwm_fc_h_disp			 = FALSE;
		gVideoPwmInfo[pwmId].ctrl.pwm_fc_l_disp			 = FALSE;
		gVideoPwmInfo[pwmId].wdth						 = 0;
		gVideoPwmInfo[pwmId].mask						 = 0xff;
		gVideoPwmInfo[pwmId].unit						 = 2417;
	}

	return ret;
}

DTV_STATUS_T DE_PWM_SetCtrl(UINT32 pwmId, VIDEO_PWM_CTRL_TYPE_T ctrId, UINT32 ctrVal)
{
	DTV_STATUS_T ret = RET_OK;

	switch (ctrId) {
		case PWM_CTRL_ENB :
			gVideoPwmInfo[pwmId].ctrl.pwm_en				= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_FRQ :
			gVideoPwmInfo[pwmId].ctrl.pwm_freq_mode			= ctrVal & 0x3;
			break;
		case PWM_CTRL_FRE :
			gVideoPwmInfo[pwmId].ctrl.pwm_method			= ctrVal & 0x1;
			break;
		case PWM_CTRL_RES :
			gVideoPwmInfo[pwmId].ctrl.pwm_resolution		= ctrVal & 0x3;
			break;
		case PWM_CTRL_INV :
			gVideoPwmInfo[pwmId].ctrl.pwm_inv				= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_MOD :
			gVideoPwmInfo[pwmId].ctrl.pwm_sel				= ctrVal;
			break;
		case PWM_CTRL_POS :
			gVideoPwmInfo[pwmId].ctrl.pwm_width_falling_pos = ctrVal & 0x3FFFFF;
			break;
		case PWM_CTRL_LOW :
			gVideoPwmInfo[pwmId].ctrl.pwm_fc_h_disp			= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_HIG :
			gVideoPwmInfo[pwmId].ctrl.pwm_fc_l_disp			= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_WDH :
			gVideoPwmInfo[pwmId].wdth						= ctrVal;
			break;
		case PWM_CTRL_MSK :
			gVideoPwmInfo[pwmId].mask						= ctrVal;
			break;
		default :
			break;
	}

	return ret;
}

DTV_STATUS_T VIDEO_REG_SetPwmCtrl(UINT32 pwmId)
{
	DTV_STATUS_T ret = RET_OK;

	switch (pwmId) {
		case 0 :
			//gpVideoDebReg->deb_pwm0_ctrl0  = *(DEB_PWM0_CTRL0_T*)&gVideoPwmInfo[pwmId].ctrl;
			DE_DEB_L9B_RdFL(deb_pwm0_ctrl0);
			DE_DEB_L9B_RdFL(deb_pwm0_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_en, gVideoPwmInfo[pwmId].ctrl.pwm_en);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_freq_mode, gVideoPwmInfo[pwmId].ctrl.pwm_freq_mode);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_method, gVideoPwmInfo[pwmId].ctrl.pwm_method);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_resolution, gVideoPwmInfo[pwmId].ctrl.pwm_resolution);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_inv, gVideoPwmInfo[pwmId].ctrl.pwm_inv);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_sel, gVideoPwmInfo[pwmId].ctrl.pwm_sel);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_width_falling_pos, gVideoPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_fc_h_disp, gVideoPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl0, pwm0_fc_l_disp, gVideoPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl1, pwm0_free_width, gVideoPwmInfo[pwmId].ctl1.pwm_free_width);
			DE_DEB_L9B_WrFL(deb_pwm0_ctrl0);
			DE_DEB_L9B_WrFL(deb_pwm0_ctrl1);
			break;
		case 1 :
			//gpVideoDebReg->deb_pwm1_ctrl0  = *(DEB_PWM1_CTRL0_T*)&gVideoPwmInfo[pwmId].ctrl;
			DE_DEB_L9B_RdFL(deb_pwm1_ctrl0);
			DE_DEB_L9B_RdFL(deb_pwm1_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_en, gVideoPwmInfo[pwmId].ctrl.pwm_en);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_freq_mode, gVideoPwmInfo[pwmId].ctrl.pwm_freq_mode);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_method, gVideoPwmInfo[pwmId].ctrl.pwm_method);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_resolution, gVideoPwmInfo[pwmId].ctrl.pwm_resolution);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_inv, gVideoPwmInfo[pwmId].ctrl.pwm_inv);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_sel, gVideoPwmInfo[pwmId].ctrl.pwm_sel);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_width_falling_pos, gVideoPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_fc_h_disp, gVideoPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl0, pwm1_fc_l_disp, gVideoPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl1, pwm1_free_width, gVideoPwmInfo[pwmId].ctl1.pwm_free_width);
			DE_DEB_L9B_WrFL(deb_pwm1_ctrl0);
			DE_DEB_L9B_WrFL(deb_pwm1_ctrl1);
			break;
		case 2 :
			//gpVideoDebReg->deb_pwm2_ctrl0  = *(DEB_PWM2_CTRL0_T*)&gVideoPwmInfo[pwmId].ctrl;
			DE_DEB_L9B_RdFL(deb_pwm2_ctrl0);
			DE_DEB_L9B_RdFL(deb_pwm2_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_en, gVideoPwmInfo[pwmId].ctrl.pwm_en);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_freq_mode, gVideoPwmInfo[pwmId].ctrl.pwm_freq_mode);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_method, gVideoPwmInfo[pwmId].ctrl.pwm_method);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_resolution, gVideoPwmInfo[pwmId].ctrl.pwm_resolution);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_inv, gVideoPwmInfo[pwmId].ctrl.pwm_inv);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_sel, gVideoPwmInfo[pwmId].ctrl.pwm_sel);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_width_falling_pos, gVideoPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_fc_h_disp, gVideoPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl0, pwm2_fc_l_disp, gVideoPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl1, pwm2_free_width, gVideoPwmInfo[pwmId].ctl1.pwm_free_width);
			DE_DEB_L9B_WrFL(deb_pwm2_ctrl0);
			DE_DEB_L9B_WrFL(deb_pwm2_ctrl1);
			break;
		case 3 :
			DE_DEB_L9B_RdFL(deb_pwm3_ctrl);
			DE_DEB_L9B_Wr01(deb_pwm3_ctrl, pwm3_en, gVideoPwmInfo[pwmId].ctrl.pwm_en);
			DE_DEB_L9B_Wr01(deb_pwm3_ctrl, pwm3_freq_mode, gVideoPwmInfo[pwmId].ctrl.pwm_freq_mode);
			DE_DEB_L9B_WrFL(deb_pwm3_ctrl);
			break;
		default :
			BREAK_WRONG(pwmId);
	}

	return ret;
}

DTV_STATUS_T VIDEO_REG_SetPwmMask(UINT32 pwmId)
{
	DTV_STATUS_T ret = RET_OK;

	switch (pwmId) {
		case 0 :
			//deb_pwm0_ctrl1 = gpVideoDebReg->deb_pwm0_ctrl1;
			//deb_pwm0_ctrl1.pwm0_intr_mask = gVideoPwmInfo[pwmId].mask;
			//gpVideoDebReg->deb_pwm0_ctrl1 = deb_pwm0_ctrl1;
			DE_DEB_L9B_RdFL(deb_pwm0_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl1, pwm0_intr_mask, gVideoPwmInfo[pwmId].mask);
			DE_DEB_L9B_WrFL(deb_pwm0_ctrl1);
			break;
		case 1 :
			//deb_pwm1_ctrl1 = gpVideoDebReg->deb_pwm1_ctrl1;
			//deb_pwm1_ctrl1.pwm1_intr_mask = gVideoPwmInfo[pwmId].mask;
			//gpVideoDebReg->deb_pwm1_ctrl1 = deb_pwm1_ctrl1;
			DE_DEB_L9B_RdFL(deb_pwm1_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl1, pwm1_intr_mask, gVideoPwmInfo[pwmId].mask);
			DE_DEB_L9B_WrFL(deb_pwm1_ctrl1);
			break;
		case 2 :
			//deb_pwm2_ctrl1 = gpVideoDebReg->deb_pwm2_ctrl1;
			//deb_pwm2_ctrl1.pwm2_intr_mask = gVideoPwmInfo[pwmId].mask;
			//gpVideoDebReg->deb_pwm2_ctrl1 = deb_pwm2_ctrl1;
			DE_DEB_L9B_RdFL(deb_pwm2_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl1, pwm2_intr_mask, gVideoPwmInfo[pwmId].mask);
			DE_DEB_L9B_WrFL(deb_pwm2_ctrl1);
			break;
		default :
			BREAK_WRONG(pwmId);
	}

	return ret;
}

DTV_STATUS_T VIDEO_REG_SetPwmWidth(UINT32 pwmId)
{
	DTV_STATUS_T ret = RET_OK;

	switch (pwmId) {
		case 0 :
			//deb_pwm0_ctrl1 = gpVideoDebReg->deb_pwm0_ctrl1;
			//deb_pwm0_ctrl1.pwm0_free_width = gVideoPwmInfo[pwmId].wdth;
			//gpVideoDebReg->deb_pwm0_ctrl1 = deb_pwm0_ctrl1;
			DE_DEB_L9B_RdFL(deb_pwm0_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm0_ctrl1, pwm0_free_width, gVideoPwmInfo[pwmId].mask);
			DE_DEB_L9B_WrFL(deb_pwm0_ctrl1);
			break;
		case 1 :
			//deb_pwm1_ctrl1 = gpVideoDebReg->deb_pwm1_ctrl1;
			//deb_pwm1_ctrl1.pwm1_free_width = gVideoPwmInfo[pwmId].wdth;
			//gpVideoDebReg->deb_pwm1_ctrl1 = deb_pwm1_ctrl1;
			DE_DEB_L9B_RdFL(deb_pwm1_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm1_ctrl1, pwm1_free_width, gVideoPwmInfo[pwmId].mask);
			DE_DEB_L9B_WrFL(deb_pwm1_ctrl1);
			break;
		case 2 :
			//deb_pwm2_ctrl1 = gpVideoDebReg->deb_pwm2_ctrl1;
			//deb_pwm2_ctrl1.pwm2_free_width = gVideoPwmInfo[pwmId].wdth;
			//gpVideoDebReg->deb_pwm2_ctrl1 = deb_pwm2_ctrl1;
			DE_DEB_L9B_RdFL(deb_pwm2_ctrl1);
			DE_DEB_L9B_Wr01(deb_pwm2_ctrl1, pwm2_free_width, gVideoPwmInfo[pwmId].mask);
			DE_DEB_L9B_WrFL(deb_pwm2_ctrl1);
			break;
		default :
			BREAK_WRONG(pwmId);
	}

	return ret;
}

DTV_STATUS_T VIDEO_REG_SetPwmTiming(UINT32 pwmId)
{
	DTV_STATUS_T ret = RET_OK;

	switch (pwmId) {
		case 0 :
			//gpVideoDebReg->pwm0_v		 = *(L9B0_PWM0_V_T*)&gVideoPwmInfo[pwmId].t1st;
			//gpVideoDebReg->pwm0_v_sub = *(L9B0_PWM0_V_SUB_T*)&gVideoPwmInfo[pwmId].t2nd;
			DE_DEB_L9B_RdFL(pwm0_v);
			DE_DEB_L9B_RdFL(pwm0_v_sub);
			DE_DEB_L9B_Wr01(pwm0_v, pwm0_x_f_v, gVideoPwmInfo[pwmId].t1st.pwm_x_f_v);
			DE_DEB_L9B_Wr01(pwm0_v, pwm0_x_r_v, gVideoPwmInfo[pwmId].t1st.pwm_x_r_v);
			DE_DEB_L9B_Wr01(pwm0_v, pwm0_v_id, gVideoPwmInfo[pwmId].t1st.pwm_v_id);
			DE_DEB_L9B_Wr01(pwm0_v, pwm0_v_we, gVideoPwmInfo[pwmId].t1st.pwm_v_we);
			DE_DEB_L9B_Wr01(pwm0_v_sub, pwm0_x_r_v_sub, gVideoPwmInfo[pwmId].t2nd.pwm_x_r_v);
			DE_DEB_L9B_Wr01(pwm0_v_sub, pwm0_v_sub_id, gVideoPwmInfo[pwmId].t2nd.pwm_v_id);
			DE_DEB_L9B_Wr01(pwm0_v_sub, pwm0_v_sub_we, gVideoPwmInfo[pwmId].t2nd.pwm_v_we);
			DE_DEB_L9B_WrFL(pwm0_v);
			DE_DEB_L9B_WrFL(pwm0_v_sub);
			break;
		case 1 :
			//gpVideoDebReg->pwm1_v		 = *(L9B0_PWM1_V_T*)&gVideoPwmInfo[pwmId].t1st;
			//gpVideoDebReg->pwm1_v_sub = *(L9B0_PWM1_V_SUB_T*)&gVideoPwmInfo[pwmId].t2nd;
			DE_DEB_L9B_RdFL(pwm1_v);
			DE_DEB_L9B_RdFL(pwm1_v_sub);
			DE_DEB_L9B_Wr01(pwm1_v, pwm1_x_f_v, gVideoPwmInfo[pwmId].t1st.pwm_x_f_v);
			DE_DEB_L9B_Wr01(pwm1_v, pwm1_x_r_v, gVideoPwmInfo[pwmId].t1st.pwm_x_r_v);
			DE_DEB_L9B_Wr01(pwm1_v, pwm1_v_id, gVideoPwmInfo[pwmId].t1st.pwm_v_id);
			DE_DEB_L9B_Wr01(pwm1_v, pwm1_v_we, gVideoPwmInfo[pwmId].t1st.pwm_v_we);
			DE_DEB_L9B_Wr01(pwm1_v_sub, pwm1_x_r_v_sub, gVideoPwmInfo[pwmId].t2nd.pwm_x_r_v);
			DE_DEB_L9B_Wr01(pwm1_v_sub, pwm1_v_sub_id, gVideoPwmInfo[pwmId].t2nd.pwm_v_id);
			DE_DEB_L9B_Wr01(pwm1_v_sub, pwm1_v_sub_we, gVideoPwmInfo[pwmId].t2nd.pwm_v_we);
			DE_DEB_L9B_WrFL(pwm1_v);
			DE_DEB_L9B_WrFL(pwm1_v_sub);
			break;
		case 2 :
			//gpVideoDebReg->pwm2_v		 = *(L9B0_PWM2_V_T*)&gVideoPwmInfo[pwmId].t1st;
			//gpVideoDebReg->pwm2_v_sub = *(L9B0_PWM2_V_SUB_T*)&gVideoPwmInfo[pwmId].t2nd;
			DE_DEB_L9B_RdFL(pwm2_v);
			DE_DEB_L9B_RdFL(pwm2_v_sub);
			DE_DEB_L9B_Wr01(pwm2_v, pwm2_x_f_v, gVideoPwmInfo[pwmId].t1st.pwm_x_f_v);
			DE_DEB_L9B_Wr01(pwm2_v, pwm2_x_r_v, gVideoPwmInfo[pwmId].t1st.pwm_x_r_v);
			DE_DEB_L9B_Wr01(pwm2_v, pwm2_v_id, gVideoPwmInfo[pwmId].t1st.pwm_v_id);
			DE_DEB_L9B_Wr01(pwm2_v, pwm2_v_we, gVideoPwmInfo[pwmId].t1st.pwm_v_we);
			DE_DEB_L9B_Wr01(pwm2_v_sub, pwm2_x_r_v_sub, gVideoPwmInfo[pwmId].t2nd.pwm_x_r_v);
			DE_DEB_L9B_Wr01(pwm2_v_sub, pwm2_v_sub_id, gVideoPwmInfo[pwmId].t2nd.pwm_v_id);
			DE_DEB_L9B_Wr01(pwm2_v_sub, pwm2_v_sub_we, gVideoPwmInfo[pwmId].t2nd.pwm_v_we);
			DE_DEB_L9B_WrFL(pwm2_v);
			DE_DEB_L9B_WrFL(pwm2_v_sub);
			break;
		default :
			BREAK_WRONG(pwmId);
	}

	return ret;
}

DTV_STATUS_T VIDEO_REG_GetPwmTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall)
{
	DTV_STATUS_T ret = RET_OK;

	do {
		switch (freq_mode)
		{
			case 0 :
				DE_DEB_L9B_RdFL(pwm3_0_low);
				DE_DEB_L9B_RdFL(pwm3_0_high);
				DE_DEB_L9B_Rd01(pwm3_0_low, pwm3_0_low, *pRising);
				DE_DEB_L9B_Rd01(pwm3_0_high, pwm3_0_high, *pFall);
				break;
			case 1 :
				DE_DEB_L9B_RdFL(pwm3_1_low);
				DE_DEB_L9B_RdFL(pwm3_1_high);
				DE_DEB_L9B_Rd01(pwm3_1_low, pwm3_1_low, *pRising);
				DE_DEB_L9B_Rd01(pwm3_1_high, pwm3_1_high, *pFall);
				break;
			case 2 :
				DE_DEB_L9B_RdFL(pwm3_2_low);
				DE_DEB_L9B_RdFL(pwm3_2_high);
				DE_DEB_L9B_Rd01(pwm3_2_low, pwm3_2_low, *pRising);
				DE_DEB_L9B_Rd01(pwm3_2_high, pwm3_2_high, *pFall);
				break;
			case 3 :
				DE_DEB_L9B_RdFL(pwm3_3_low);
				DE_DEB_L9B_RdFL(pwm3_3_high);
				DE_DEB_L9B_Rd01(pwm3_3_low, pwm3_3_low, *pRising);
				DE_DEB_L9B_Rd01(pwm3_3_high, pwm3_3_high, *pFall);
				break;
			default :
				BREAK_WRONG(freq_mode);
		}
	} while(0);

	return ret;
}

DTV_STATUS_T DE_PWM_SetTiming(UINT32 pwmId, VIDEO_PWM_ORD_T pwmOrd, UINT32 *pR1st, UINT32 *pFall, UINT32 *pR2nd)
{
	VIDEO_PWM_TIMING_T t1st;
	VIDEO_PWM_TIMING_T t2nd;

	t1st = gVideoPwmInfo[pwmId].t1st;
	t2nd = gVideoPwmInfo[pwmId].t2nd;
	t1st.pwm_v_id = pwmOrd & 0x7;
	t2nd.pwm_v_id = pwmOrd & 0x7;
	t1st.pwm_v_we = TRUE;
	t2nd.pwm_v_we = TRUE;
	do {
		if (pR1st) t1st.pwm_x_r_v = *pR1st;
		if (pFall) t1st.pwm_x_f_v = *pFall;
		if (pR2nd) t2nd.pwm_x_r_v = *pR2nd;
		if (pR2nd) break;
		if (pR1st) t2nd.pwm_x_r_v = *pR1st;
	} while ( 0 );
	gVideoPwmInfo[pwmId].t1st = t1st;
	gVideoPwmInfo[pwmId].t2nd = t2nd;

	return VIDEO_REG_SetPwmTiming(pwmId);
}

DTV_STATUS_T DE_PWM_GetTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall)
{
	DTV_STATUS_T ret = RET_OK;

	ret = VIDEO_REG_GetPwmTiming(freq_mode, pRising, pFall);

	return ret;
}

DTV_STATUS_T DE_PWM_SetRegCtrl(UINT32 pwmId)
{
	DTV_STATUS_T ret = RET_OK;

	ret = VIDEO_REG_SetPwmCtrl(pwmId);

	return ret;
}

DTV_STATUS_T DE_PWM_Init(void)
{
	DTV_STATUS_T ret = RET_OK;
	VIDEO_PWM_NUM_T pwmId;
	static UINT8 init_flag = FALSE;

	DE_PRINT("%s : enter\n", __F__);

	do {
		if(init_flag) break;
		ret = DE_PWM_InitCtrl();
		if (ret) break;
		pwmId = PWM_NUM_ID2;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_ENB, TRUE);
		if (ret) break;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_FRQ, PWM_FREQ_120HZ);
		if (ret) break;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_MOD, PWM_MODE_DUTY);
		if (ret) break;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_FRE, PWM_FREE_ON);
		if (ret) break;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_RES, PWM_RES_1024);
		//if (ret) break;
		//ret = VIDEO_REG_SetPwmCtrl(pwmId);
		if (ret) break;

		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_MSK, 0x00);	// mask intr
		if (ret) break;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_WDH, FALSE);	// duty mode

		//if (ret) break;
		//ret = VIDEO_REG_SetPwmMask(pwmId);
		//if (ret) break;
		//ret = VIDEO_REG_SetPwmWidth(pwmId);
		if (ret) break;

#if 0
		ret = DE_PWM_SetTiming(pwmId, PWM_ORD_1ST, NULL, NULL, NULL);
		if (ret) break;
#endif

		pwmId = PWM_NUM_ID3;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_ENB, TRUE);
		if (ret) break;
		ret = DE_PWM_SetCtrl(pwmId, PWM_CTRL_FRQ, PWM_FREQ_120HZ);
		if (ret) break;
		ret = VIDEO_REG_SetPwmCtrl(pwmId);
		init_flag = TRUE;
	} while ( 0 );

	DE_PRINT("%s : done.\n", __F__);

	return ret;
}

#endif

#ifndef KDRV_GLOBAL_LINK
#ifdef USE_PQL_REG_DEFINED_IN_DE
EXPORT_SYMBOL(gDE_P0L_L9);
EXPORT_SYMBOL(gDE_P1L_L9);
EXPORT_SYMBOL(gDE_P0R_L9);
EXPORT_SYMBOL(gDE_P1R_L9);
EXPORT_SYMBOL(gDE_P0L_L9B);
EXPORT_SYMBOL(gDE_P0R_L9B);
EXPORT_SYMBOL(gDE_P1L_L9B);
EXPORT_SYMBOL(gDE_P1R_L9B);
EXPORT_SYMBOL(gDE_CTOP_L9);
#endif
#endif
#endif
/**  @} */
