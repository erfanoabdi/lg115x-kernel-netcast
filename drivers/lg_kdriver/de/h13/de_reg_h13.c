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
#undef  USE_FRAME_COPY_TO_NFS_FILE

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <asm/io.h>

#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <asm/uaccess.h>

#include "base_types.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"

#ifndef USE_VIDEO_FOR_FPGA
//#include "h13/base_addr_sw_h13.h"
#endif

#ifdef USE_KDRV_CODES_FOR_H13
#include "de_kapi.h"
#include "de_def.h"
#include "de_prm_def.h"
#include "de_hal_def.h"
#include "de_cfg.h"
#include "de_drv.h"

#include "h13/de_cfg_h13.h"
#include "h13/de_ipc_def_h13.h"
#include "h13/de_int_def_h13.h"
#include "h13/de_reg_def_h13.h"
#include "h13/de_reg_h13.h"
#include "h13/de_prm_h13.h"

#include "h13/de_ctr_reg_h13.h"		  // 0x0000, 0x1000, 0x2000, 0x3000, 0x4000
#include "h13/de_cvi_reg_h13.h"		  // 0x0100, 0x0200
#include "h13/de_pe0_reg_h13.h"		  // 0x0400, 0x2400
#include "h13/de_mif_reg_h13.h"		  // 0x0800, 0x1b00, 0x2800, 0x3900, 0x5900
#include "h13/de_msc_reg_h13.h"		  // 0x1100, 0x3100
#include "h13/de_wcp_reg_h13.h"		  // 0x1200, 0x3200
#include "h13/de_ssc_reg_h13.h"		  // 0x2100
#include "h13/de_atp_reg_h13.h"	  	  // 0x3800
#include "h13/de_cvd_reg_h13.h"		  // 0x4100
#include "h13/de_vdi_reg_h13.h"		  // 0x4d00
#include "h13/de_ipc_reg_h13.h"		  // 0x4e00
#include "h13/de_dpp_reg_h13.h"		  // 0x5000
#include "h13/de_osd_reg_h13.h"		  // 0x5100
#include "h13/de_pe1_reg_h13.h"		  // 0x5300
#include "h13/de_dvr_reg_h13.h"		  // 0x5c00

#ifdef USE_CTOP_CODES_FOR_H13
#include "../sys/sys_regs.h"
#endif

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define  SIZE_OF_IPC_FOR_CPU 16
#ifndef USE_VIDEO_FOR_FPGA
//#define ADDR_SW_CONTROLLED_BY_CFG
#endif
#define ADDR_SW_CASE4
#define USE_VIDEO_MCU_RUN_IN_DDR0   0x00000000
#define USE_VIDEO_MCU_ROM_BASE_ADDR 0x50000000
#define USE_VIDEO_MCU_ROM_FW_OFFSET 0x00000000
#define DE_DDR_FIRMWARE_TAG_COUNT    2

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
DE_DEA_REG_H13_T gDE_DEA_H13;
DE_DEB_REG_H13_T gDE_DEB_H13;
DE_DEC_REG_H13_T gDE_DEC_H13;
DE_DED_REG_H13_T gDE_DED_H13;
DE_DEE_REG_H13_T gDE_DEE_H13;
DE_DEF_REG_H13_T gDE_DEF_H13;

DE_CVA_REG_H13_T gDE_CVA_H13;
DE_CVB_REG_H13_T gDE_CVB_H13;

//DE_DLR_REG_H13_T gDE_DLR_H13;

DE_P0L_REG_H13_T gDE_P0L_H13;
DE_P0R_REG_H13_T gDE_P0R_H13;
//DE_P0L_REG_H13B_T gDE_P0L_H13B;
//DE_P0R_REG_H13B_T gDE_P0R_H13B;

DE_MIA_REG_H13_T gDE_MIA_H13;
DE_MIB_REG_H13_T gDE_MIB_H13;
DE_MIC_REG_H13_T gDE_MIC_H13;
DE_MID_REG_H13_T gDE_MID_H13;
DE_MIF_REG_H13_T gDE_MIF_H13;

DE_MSL_REG_H13_T gDE_MSL_H13;
DE_MSR_REG_H13_T gDE_MSR_H13;

DE_OVL_REG_H13_T gDE_OVL_H13;
DE_OVR_REG_H13_T gDE_OVR_H13;

DE_DPP_REG_H13_T gDE_DPP_H13;

DE_P1L_REG_H13_T gDE_P1L_H13;
//DE_P1R_REG_H13_T gDE_P1R_H13;
//DE_P1L_REG_H13B_T gDE_P1L_H13B;
//DE_P1R_REG_H13B_T gDE_P1R_H13B;

DE_SSC_REG_H13_T gDE_SSC_H13;
//DE_T3D_REG_H13_T gDE_T3D_H13;
DE_OSD_REG_H13_T gDE_OSD_H13;
//DE_ATP_REG_H13_T gDE_ATP_H13;
//DE_OIF_REG_H13_T gDE_OIF_H13;
DE_CVD_REG_H13_T gDE_CVD_H13;

DE_VDI_REG_H13_T gDE_VDC_H13;
DE_VDI_REG_H13_T gDE_VDD_H13;
DE_IPC_REG_H13_T gDE_IPC_H13;
DE_DVR_REG_H13_T gDE_DVR_H13;


BOOLEAN g_b_PllMain_H13 = FALSE;
BOOLEAN g_b_pllFrc_H13	= FALSE;

BOOLEAN g_b_InitTPG_H13 = FALSE;
UINT32	g_patchEn_H13	= 0;

LX_DE_INPUT_PORT	g_WinSrc_H13[2] = { LX_DE_PORT_MVI,  LX_DE_PORT_MVI};
LX_DE_IN_SRC_T	g_WinsrcMap_H13[2] = { LX_DE_IN_SRC_MVI,	LX_DE_IN_SRC_MVI};
UINT32			g_WinsrcPort_H13[2] = { 0, 0};

LX_DE_OPER_CONFIG_T		g_SrcOperType_H13 = LX_DE_OPER_ONE_WIN;
LX_DE_SUB_OPER_CONFIG_T	g_SrcSubOperType_H13 = LX_DE_SUB_OPER_OFF;

LX_DE_DISPLAY_DEVICE_T	g_Display_type_H13 = LX_DE_DIS_DEV_LCD;
LX_DE_DISPLAY_MIRROR_T	g_Display_mirror_H13 = LX_DE_DIS_MIRROR_OFF;
LX_DE_PANEL_TYPE_T 		g_Display_size_H13 = LX_PANEL_TYPE_1920;
LX_DE_FRC_PATH_T		g_Frc_type_H13 = LX_DE_FRC_PATH_INTERNAL;
LX_DE_3D_CTRL_T			g_Trid_type_H13 = LX_DE_3D_CTRL_ON;

typedef struct {
	LX_DE_MULTI_SRC_T src;
	BOOLEAN used;
	UINT32 cvi_mux_sel;
	UINT32 exta_sel;
	UINT32 extb_sel;
}
LX_DE_SRC_CONFIG;

LX_DE_SRC_CONFIG sMultiSrc_map_H13[2][LX_DE_MULTI_IN_MAX + 1] =
{
	{	/* H13-A0 */
		{LX_DE_MULTI_IN_CVD_ADC,	TRUE,	 0x20, 1,	0}, /* NAME, on/off, cvi_mux_sel, exta_sel, extb_sel : (DEE_CVI_MUX_SEL) */
		{LX_DE_MULTI_IN_CVD_HDMI,	TRUE,	 0x21, 1,	2},
		{LX_DE_MULTI_IN_CVD_MVI,	TRUE,	 0x21, 1,	1},
		{LX_DE_MULTI_IN_CVD_CPU,	TRUE,	 0x21, 1,	1},
		{LX_DE_MULTI_IN_CVD_CVD,	TRUE,	 0x22, 1,	1},
		{LX_DE_MULTI_IN_ADC_CVD,	TRUE,	 0x02, 0,	1},
		{LX_DE_MULTI_IN_ADC_HDMI,	TRUE,	 0x01, 0,	2},
		{LX_DE_MULTI_IN_ADC_MVI,	TRUE,	 0x01, 0,	1},
		{LX_DE_MULTI_IN_ADC_CPU,	TRUE,	 0x01, 0,	1},
		{LX_DE_MULTI_IN_ADC_ADC,	TRUE,	 0x00, 0,	0},
		{LX_DE_MULTI_IN_HDMI_CVD,	TRUE,	 0x12, 2,	1},
		{LX_DE_MULTI_IN_HDMI_ADC,	TRUE,	 0x10, 2,	0},
		{LX_DE_MULTI_IN_HDMI_MVI,	TRUE,	 0x10, 2,	0},
		{LX_DE_MULTI_IN_HDMI_CPU,	TRUE,	 0x10, 2,	0},
		{LX_DE_MULTI_IN_HDMI_HDMI,	TRUE,	 0x11, 2,	2},
		{LX_DE_MULTI_IN_MVI_CVD,	TRUE,	 0x02, 1,	1},
		{LX_DE_MULTI_IN_MVI_ADC,	TRUE,	 0x00, 1,	0},
		{LX_DE_MULTI_IN_MVI_HDMI,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_MVI_CPU,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_MVI_MVI,	TRUE,	 0x00, 1,	1},
		{LX_DE_MULTI_IN_CPU_CVD,	TRUE,	 0x02, 1,	1},
		{LX_DE_MULTI_IN_CPU_ADC,	TRUE,	 0x00, 1,	0},
		{LX_DE_MULTI_IN_CPU_HDMI,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_CPU_MVI,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_CPU_CPU,	TRUE,	 0x00, 1,	1},
		{LX_DE_MULTI_IN_MVA_MVB,	TRUE,	 0x00, 1,	1},
		{LX_DE_MULTI_IN_HDMIA_HDMIB,TRUE,	 0x34, 2,	3},
		{LX_DE_MULTI_IN_MAX,		TRUE,	 0x43, 1,	1}
	},

	{	/* H13-B0 */
		{LX_DE_MULTI_IN_CVD_ADC,	TRUE,	 0x20, 1,	0}, /* NAME, on/off, cvi_mux_sel, exta_sel, extb_sel : (DEE_CVI_MUX_SEL) */
		{LX_DE_MULTI_IN_CVD_HDMI,	TRUE,	 0x21, 1,	2},
		{LX_DE_MULTI_IN_CVD_MVI,	TRUE,	 0x21, 1,	1},
		{LX_DE_MULTI_IN_CVD_CPU,	TRUE,	 0x21, 1,	1},
		{LX_DE_MULTI_IN_CVD_CVD,	TRUE,	 0x22, 1,	1},
		{LX_DE_MULTI_IN_ADC_CVD,	TRUE,	 0x02, 0,	1},
		{LX_DE_MULTI_IN_ADC_HDMI,	TRUE,	 0x01, 0,	2},
		{LX_DE_MULTI_IN_ADC_MVI,	TRUE,	 0x01, 0,	1},
		{LX_DE_MULTI_IN_ADC_CPU,	TRUE,	 0x01, 0,	1},
		{LX_DE_MULTI_IN_ADC_ADC,	TRUE,	 0x00, 0,	0},
		{LX_DE_MULTI_IN_HDMI_CVD,	TRUE,	 0x12, 2,	1},
		{LX_DE_MULTI_IN_HDMI_ADC,	TRUE,	 0x10, 2,	0},
		{LX_DE_MULTI_IN_HDMI_MVI,	TRUE,	 0x10, 2,	0},
		{LX_DE_MULTI_IN_HDMI_CPU,	TRUE,	 0x10, 2,	0},
		{LX_DE_MULTI_IN_HDMI_HDMI,	TRUE,	 0x11, 2,	2},
		{LX_DE_MULTI_IN_MVI_CVD,	TRUE,	 0x02, 1,	1},
		{LX_DE_MULTI_IN_MVI_ADC,	TRUE,	 0x00, 1,	0},
		{LX_DE_MULTI_IN_MVI_HDMI,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_MVI_CPU,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_MVI_MVI,	TRUE,	 0x00, 1,	1},
		{LX_DE_MULTI_IN_CPU_CVD,	TRUE,	 0x02, 1,	1},
		{LX_DE_MULTI_IN_CPU_ADC,	TRUE,	 0x00, 1,	0},
		{LX_DE_MULTI_IN_CPU_HDMI,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_CPU_MVI,	TRUE,	 0x01, 1,	2},
		{LX_DE_MULTI_IN_CPU_CPU,	TRUE,	 0x00, 1,	1},
		{LX_DE_MULTI_IN_MVA_MVB,	TRUE,	 0x00, 1,	1},
		{LX_DE_MULTI_IN_HDMIA_HDMIB,TRUE,	 0x34, 2,	3},
		{LX_DE_MULTI_IN_MAX,		TRUE,	 0x43, 1,	1}
	}
};

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_H13_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static UINT32		   *spVideoIPCofCPU[2]	  = {NULL};
static DE_DPLL_SET_T sDisplayPll_H13[] = {
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
	{ DCLK_148_5	,{ 0x4 ,0xA ,0x2 } },
	{ DCLK_85_86	,{ 0 ,0x2 ,0x2 } },
};

static BOOLEAN sbDeUdMode = FALSE;
static BOOLEAN sbDe3DFullMode = FALSE;
static LX_DE_CVI_SRC_TYPE_T sCviSrcType;
static LX_DE_MULTI_WIN_SRC_T sDeMultiWinSrc = {0,0};
LX_DE_CH_MEM_T *gpAdrPreW;
LX_DE_CH_MEM_T *gpAdrGrap;

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/

int DE_REG_H13_InitAddrSwitch(void)
{
#ifndef USE_KDRV_CODES_FOR_H13
#ifdef ADDR_SW_CONTROLLED_BY_CFG
	LX_ADDR_SW_CFG_T	addr_sw;
#endif

	printk("^g^ DE SIZE = %d\n", VIDEO_H13_MEM_SIZE_OF_FRAME_MEMORY );

#ifdef ADDR_SW_CONTROLLED_BY_CFG
	// DEA
	BASE_H13_GetAddrSwCfg(ADDR_SW_CFG_DE_A, &addr_sw);
	DE_DEA_H13_FLWr(dea_addr_sw_de_sav,			addr_sw.de_sav);
	DE_DEA_H13_FLWr(dea_addr_sw_cpu_gpu,		addr_sw.cpu_gpu);
	DE_DEA_H13_FLWr(dea_addr_sw_cpu_shadow,		addr_sw.cpu_shadow);

	// DEB
	BASE_H13_GetAddrSwCfg(ADDR_SW_CFG_DE_B, &addr_sw);
	DE_DEB_H13_FLWr(deb_addr_sw_de_sav,			addr_sw.de_sav);
	DE_DEB_H13_FLWr(deb_addr_sw_cpu_gpu,		addr_sw.cpu_gpu);
	DE_DEB_H13_FLWr(deb_addr_sw_cpu_shadow,		addr_sw.cpu_shadow);

	// DEC
	BASE_H13_GetAddrSwCfg(ADDR_SW_CFG_DE_C, &addr_sw);
	DE_DEC_H13_FLWr(dec_addr_sw_de_sav,			addr_sw.de_sav);
	DE_DEC_H13_FLWr(dec_addr_sw_cpu_gpu,		addr_sw.cpu_gpu);
	DE_DEC_H13_FLWr(dec_addr_sw_cpu_shadow,		addr_sw.cpu_shadow);

	// DED
	BASE_H13_GetAddrSwCfg(ADDR_SW_CFG_DE_D, &addr_sw);
	DE_DED_H13_FLWr(ded_addr_sw_de_sav,			addr_sw.de_sav);
	DE_DED_H13_FLWr(ded_addr_sw_cpu_gpu,		addr_sw.cpu_gpu);
	DE_DED_H13_FLWr(ded_addr_sw_cpu_shadow,		addr_sw.cpu_shadow);

	// DEE
	BASE_H13_GetAddrSwCfg(ADDR_SW_CFG_DE_E, &addr_sw);
	DE_DEE_H13_FLWr(dee_cvd_addr_sw_de_sav,		addr_sw.de_sav);
	DE_DEE_H13_FLWr(dee_cvd_addr_sw_cpu_gpu,	addr_sw.cpu_gpu);
	DE_DEE_H13_FLWr(dee_cvd_addr_sw_cpu_shadow, addr_sw.cpu_shadow);

	// DEMCU
	BASE_H13_GetAddrSwCfg(ADDR_SW_CFG_DE,  &addr_sw);
	DE_DEE_H13_FLWr(dee_mcu_addr_sw_de_sav,		addr_sw.de_sav);
	DE_DEE_H13_FLWr(dee_mcu_addr_sw_cpu_gpu,	addr_sw.cpu_gpu);
	DE_DEE_H13_FLWr(dee_mcu_addr_sw_cpu_shadow, addr_sw.cpu_shadow);
#elif defined(ADDR_SW_CASE4)
	if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) ) {
	} else {
	/* address switch setting based on TARGET_PRODUCT */
	switch (lx_chip_plt()) {
		case LX_CHIP_PLATFORM_COSMO :
			//address switch setting as CASE2 for COSMO
			// DEA
				DE_DEA_H13A_FLWr(dea_addr_sw_de_sav,			0x24030210);
				DE_DEA_H13A_FLWr(dea_addr_sw_cpu_gpu,		0x20028058);
				DE_DEA_H13A_FLWr(dea_addr_sw_cpu_shadow,		0x04018208);

			// DEB
#ifndef USE_VIDEO_FOR_FPGA
				DE_DEB_H13A_FLWr(deb_addr_sw_de_sav,			0x28030210);
				DE_DEB_H13A_FLWr(deb_addr_sw_cpu_gpu,		0x20028058);
				DE_DEB_H13A_FLWr(deb_addr_sw_cpu_shadow,		0x04018208);

			// DEC
				DE_DEC_H13A_FLWr(dec_addr_sw_de_sav,			0x2C030210);
				DE_DEC_H13A_FLWr(dec_addr_sw_cpu_gpu,		0x20028058);
				DE_DEC_H13A_FLWr(dec_addr_sw_cpu_shadow,		0x04018208);

			// DED
				DE_DED_H13A_FLWr(ded_addr_sw_de_sav,			0x30030210);
				DE_DED_H13A_FLWr(ded_addr_sw_cpu_gpu,		0x20028058);
				DE_DED_H13A_FLWr(ded_addr_sw_cpu_shadow,		0x04018208);

			// DEE
				DE_DEE_H13A_FLWr(dee_cvd_addr_sw_de_sav,		0x34030210);
				DE_DEE_H13A_FLWr(dee_cvd_addr_sw_cpu_gpu,	0x20028058);
				DE_DEE_H13A_FLWr(dee_cvd_addr_sw_cpu_shadow, 0x04018208);

			// DEMCU
				DE_DEE_H13A_FLWr(dee_mcu_addr_sw_de_sav,		0x24000210);
				DE_DEE_H13A_FLWr(dee_mcu_addr_sw_cpu_gpu,	0x20028058);
				DE_DEE_H13A_FLWr(dee_mcu_addr_sw_cpu_shadow, 0x04018208);
#endif
			break;
		case LX_CHIP_PLATFORM_GP :
		default :
			//address switch setting as CASE4 for GP
			// DEA
				DE_DEA_H13A_FLWr(dea_addr_sw_de_sav, 0x24030210);
				DE_DEA_H13A_FLWr(dea_addr_sw_cpu_gpu, 0x00020050);
				DE_DEA_H13A_FLWr(dea_addr_sw_cpu_shadow, 0x04010200);

			// DEB
#ifndef USE_VIDEO_FOR_FPGA
				DE_DEB_H13A_FLWr(deb_addr_sw_de_sav, 0x28030210);
				DE_DEB_H13A_FLWr(deb_addr_sw_cpu_gpu, 0x00020050);
				DE_DEB_H13A_FLWr(deb_addr_sw_cpu_shadow, 0x04010200);

			// DEC
				DE_DEC_H13A_FLWr(dec_addr_sw_de_sav, 0x2C030210);
				DE_DEC_H13A_FLWr(dec_addr_sw_cpu_gpu, 0x00020050);
				DE_DEC_H13A_FLWr(dec_addr_sw_cpu_shadow, 0x04010200);

			// DED
				DE_DED_H13A_FLWr(ded_addr_sw_de_sav, 0x30030210);
				DE_DED_H13A_FLWr(ded_addr_sw_cpu_gpu, 0x00020050);
				DE_DED_H13A_FLWr(ded_addr_sw_cpu_shadow, 0x04010200);

			// DEE
				DE_DEE_H13A_FLWr(dee_cvd_addr_sw_de_sav, 0x34030210);
				DE_DEE_H13A_FLWr(dee_cvd_addr_sw_cpu_gpu, 0x00020050);
				DE_DEE_H13A_FLWr(dee_cvd_addr_sw_cpu_shadow, 0x04010200);

			// DEMCU
				DE_DEE_H13A_FLWr(dee_mcu_addr_sw_de_sav, 0x24000210);
				DE_DEE_H13A_FLWr(dee_mcu_addr_sw_cpu_gpu, 0x00020050);
				DE_DEE_H13A_FLWr(dee_mcu_addr_sw_cpu_shadow, 0x04010200);
#endif
			break;
	}
	}
#else
	if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) ) {
	} else {
	// DEA
		DE_DEA_H13A_FLWr(dea_addr_sw_de_sav,			0x24030218);
		DE_DEA_H13A_FLWr(dea_addr_sw_cpu_gpu,		0x20030058);
		DE_DEA_H13A_FLWr(dea_addr_sw_cpu_shadow,		0x04018210);

	// DEB
		DE_DEB_H13A_FLWr(deb_addr_sw_de_sav,			0x28030218);
		DE_DEB_H13A_FLWr(deb_addr_sw_cpu_gpu,		0x20030058);
		DE_DEB_H13A_FLWr(deb_addr_sw_cpu_shadow,		0x04018210);

	// DEC
		DE_DEC_H13A_FLWr(dec_addr_sw_de_sav,			0x2C030218);
		DE_DEC_H13A_FLWr(dec_addr_sw_cpu_gpu,		0x20030058);
		DE_DEC_H13A_FLWr(dec_addr_sw_cpu_shadow,		0x04018210);

	// DED
		DE_DED_H13A_FLWr(ded_addr_sw_de_sav,			0x30030218);
		DE_DED_H13A_FLWr(ded_addr_sw_cpu_gpu,		0x20030058);
		DE_DED_H13A_FLWr(ded_addr_sw_cpu_shadow,		0x04018210);

	// DEE
		DE_DEE_H13A_FLWr(dee_cvd_addr_sw_de_sav,		0x34030218);
		DE_DEE_H13A_FLWr(dee_cvd_addr_sw_cpu_gpu,	0x20030058);
		DE_DEE_H13A_FLWr(dee_cvd_addr_sw_cpu_shadow, 0x04018210);

	// DEMCU
		DE_DEE_H13A_FLWr(dee_mcu_addr_sw_de_sav,		0x24000218);
		DE_DEE_H13A_FLWr(dee_mcu_addr_sw_cpu_gpu,	0x20030058);
		DE_DEE_H13A_FLWr(dee_mcu_addr_sw_cpu_shadow, 0x04018210);
	}
#endif
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
int DE_REG_H13_InitPHY2VIRT(void)
{
	int ret = RET_OK;

	if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) ) {
		gDE_DEA_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEA_REG_H13B0_T));
		gDE_DEB_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEB_REG_H13B0_T));
		gDE_DEC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEC_REG_H13B0_T));
		gDE_DED_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DED_REG_H13B0_T));
		gDE_DEE_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEE_REG_H13B0_T));
		gDE_DEF_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEF_REG_H13B0_T));

		gDE_CVA_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVA_REG_H13B0_T));
		gDE_CVB_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVB_REG_H13B0_T));

		//gDE_DLR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DLR_REG_H13B0_T));

		gDE_P0L_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_H13B0_T));
		gDE_P0R_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_H13B0_T));
		//gDE_P0L_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_H13B0_T));
		//gDE_P0R_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_H13B0_T));

		gDE_MIA_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIA_REG_H13B0_T));
		gDE_MIB_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIB_REG_H13B0_T));
		gDE_MIC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIC_REG_H13B0_T));
		gDE_MID_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MID_REG_H13B0_T));
		gDE_MIF_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIF_REG_H13B0_T));

		gDE_MSL_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MSL_REG_H13B0_T));
		gDE_MSR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MSR_REG_H13B0_T));

		gDE_OVL_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OVL_REG_H13B0_T));
		gDE_OVR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OVR_REG_H13B0_T));

		gDE_DPP_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DPP_REG_H13B0_T));

		gDE_P1L_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_H13B0_T));
		//gDE_P1R_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_H13B0_T));
		//gDE_P1L_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_H13B0_T));
		//gDE_P1R_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_H13B0_T));

		gDE_SSC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_SSC_REG_H13B0_T));
		//gDE_T3D_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_T3D_REG_H13B0_T));
		gDE_OSD_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OSD_REG_H13B0_T));
		//gDE_ATP_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_ATP_REG_H13B0_T));
		//gDE_OIF_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OIF_REG_H13B0_T));
		gDE_CVD_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVD_REG_H13B0_T));

		gDE_VDC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_H13B0_T));
		gDE_VDD_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_H13B0_T));

		gDE_IPC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_IPC_REG_H13B0_T));
		gDE_DVR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DVR_REG_H13B0_T));

		gDE_DEA_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEA_REG_H13_BASE, sizeof(DE_DEA_REG_H13B0_T));
		gDE_DEB_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEB_REG_H13_BASE, sizeof(DE_DEB_REG_H13B0_T));
		gDE_DEC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEC_REG_H13_BASE, sizeof(DE_DEC_REG_H13B0_T));
		gDE_DED_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DED_REG_H13_BASE, sizeof(DE_DED_REG_H13B0_T));
		gDE_DEE_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEE_REG_H13_BASE, sizeof(DE_DEE_REG_H13B0_T));
		gDE_DEF_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEF_REG_H13_BASE, sizeof(DE_DEE_REG_H13B0_T));

		gDE_CVA_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_CVA_REG_H13_BASE, sizeof(DE_CVA_REG_H13B0_T));
		gDE_CVB_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_CVB_REG_H13_BASE, sizeof(DE_CVB_REG_H13B0_T));

		//gDE_DLR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DLR_REG_H13_BASE, sizeof(DE_DLR_REG_H13B0_T));

		gDE_P0L_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P0L_REG_H13_BASE, sizeof(DE_P0L_REG_H13B0_T));
		gDE_P0R_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P0R_REG_H13_BASE, sizeof(DE_P0R_REG_H13B0_T));
		//gDE_P0L_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P0L_REG_H13_BASE, sizeof(DE_P0L_REG_H13B0_T));
		//gDE_P0R_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P0R_REG_H13_BASE, sizeof(DE_P0R_REG_H13B0_T));

		gDE_MIA_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIA_REG_H13_BASE, sizeof(DE_MIA_REG_H13B0_T));
		gDE_MIB_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIB_REG_H13_BASE, sizeof(DE_MIB_REG_H13B0_T));
		gDE_MIC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIC_REG_H13_BASE, sizeof(DE_MIC_REG_H13B0_T));
		gDE_MID_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MID_REG_H13_BASE, sizeof(DE_MID_REG_H13B0_T));
		gDE_MIF_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIF_REG_H13_BASE, sizeof(DE_MIF_REG_H13B0_T));

		gDE_MSL_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MSL_REG_H13_BASE, sizeof(DE_MSL_REG_H13B0_T));
		gDE_MSR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MSR_REG_H13_BASE, sizeof(DE_MSR_REG_H13B0_T));

		gDE_OVL_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OVL_REG_H13_BASE, sizeof(DE_OVL_REG_H13B0_T));
		gDE_OVR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OVR_REG_H13_BASE, sizeof(DE_OVR_REG_H13B0_T));

		gDE_DPP_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DPP_REG_H13_BASE, sizeof(DE_DPP_REG_H13B0_T));

		gDE_P1L_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P1L_REG_H13_BASE, sizeof(DE_P1L_REG_H13B0_T));
		//gDE_P1R_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P1R_REG_H13_BASE, sizeof(DE_P1R_REG_H13B0_T));
		//gDE_P1L_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P1L_REG_H13_BASE, sizeof(DE_P1L_REG_H13B0_T));
		//gDE_P1R_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P1R_REG_H13_BASE, sizeof(DE_P1R_REG_H13B0_T));

		gDE_SSC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_SSC_REG_H13_BASE, sizeof(DE_SSC_REG_H13B0_T));
		//gDE_T3D_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_T3D_REG_H13_BASE, sizeof(DE_T3D_REG_H13B0_T));
		gDE_OSD_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OSD_REG_H13_BASE, sizeof(DE_OSD_REG_H13B0_T));
		//gDE_ATP_H13.phys.addr = (volatile UINT32 *)ioremap(DE_ATP_REG_H13B0_BASE, sizeof(DE_ATP_REG_H13B0_T));
		//gDE_OIF_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OIF_REG_H13_BASE, sizeof(DE_OIF_REG_H13B0_T));
		gDE_CVD_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_CVD_REG_H13_BASE, sizeof(DE_CVD_REG_H13B0_T));

		gDE_IPC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_IPC_REG_H13_BASE, sizeof(DE_IPC_REG_H13B0_T));
		gDE_DVR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DVR_REG_H13_BASE, sizeof(DE_DVR_REG_H13B0_T));

		gDE_VDC_H13.phys.addr  = (volatile UINT32 *)ioremap(VDEC_CPC_IPC_BASE_B0, sizeof(DE_VDI_REG_H13B0_T));
		gDE_VDD_H13.phys.addr  = (volatile UINT32 *)ioremap(VDEC_CPD_IPC_BASE_B0, sizeof(DE_VDI_REG_H13B0_T));

	} else if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
		gDE_DEA_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEA_REG_H13A0_T));
		gDE_DEB_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEB_REG_H13A0_T));
		gDE_DEC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEC_REG_H13A0_T));
		gDE_DED_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DED_REG_H13A0_T));
		gDE_DEE_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEE_REG_H13A0_T));
		gDE_DEF_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DEF_REG_H13A0_T));

		gDE_CVA_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVA_REG_H13A0_T));
		gDE_CVB_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVB_REG_H13A0_T));

		//gDE_DLR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DLR_REG_H13A0_T));

		gDE_P0L_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_H13A0_T));
		gDE_P0R_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_H13A0_T));
		//gDE_P0L_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0L_REG_H13A0_T));
		//gDE_P0R_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P0R_REG_H13A0_T));

		gDE_MIA_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIA_REG_H13A0_T));
		gDE_MIB_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIB_REG_H13A0_T));
		gDE_MIC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIC_REG_H13A0_T));
		gDE_MID_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MID_REG_H13A0_T));
		gDE_MIF_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MIF_REG_H13A0_T));

		gDE_MSL_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MSL_REG_H13A0_T));
		gDE_MSR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_MSR_REG_H13A0_T));

		gDE_OVL_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OVL_REG_H13A0_T));
		gDE_OVR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OVR_REG_H13A0_T));

		gDE_DPP_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DPP_REG_H13A0_T));

		gDE_P1L_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_H13A0_T));
		//gDE_P1R_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_H13A0_T));
		//gDE_P1L_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1L_REG_H13A0_T));
		//gDE_P1R_H13B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_P1R_REG_H13A0_T));

		gDE_SSC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_SSC_REG_H13A0_T));
		//gDE_T3D_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_T3D_REG_H13A0_T));
		gDE_OSD_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OSD_REG_H13A0_T));
		//gDE_ATP_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DE_ATP_REG_H13A0_T));
		//gDE_OIF_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_OIF_REG_H13A0_T));
		gDE_CVD_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_CVD_REG_H13A0_T));

		gDE_VDC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_H13A0_T));
		gDE_VDD_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_VDI_REG_H13A0_T));

		gDE_IPC_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_IPC_REG_H13A0_T));
		gDE_DVR_H13.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_DVR_REG_H13A0_T));

		gDE_DEA_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEA_REG_H13_BASE, sizeof(DE_DEA_REG_H13A0_T));
		gDE_DEB_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEB_REG_H13_BASE, sizeof(DE_DEB_REG_H13A0_T));
		gDE_DEC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEC_REG_H13_BASE, sizeof(DE_DEC_REG_H13A0_T));
		gDE_DED_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DED_REG_H13_BASE, sizeof(DE_DED_REG_H13A0_T));
		gDE_DEE_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEE_REG_H13_BASE, sizeof(DE_DEE_REG_H13A0_T));
		gDE_DEF_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DEF_REG_H13_BASE, sizeof(DE_DEE_REG_H13A0_T));

		gDE_CVA_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_CVA_REG_H13_BASE, sizeof(DE_CVA_REG_H13A0_T));
		gDE_CVB_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_CVB_REG_H13_BASE, sizeof(DE_CVB_REG_H13A0_T));

		//gDE_DLR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DLR_REG_H13_BASE, sizeof(DE_DLR_REG_H13A0_T));

		gDE_P0L_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P0L_REG_H13_BASE, sizeof(DE_P0L_REG_H13A0_T));
		gDE_P0R_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P0R_REG_H13_BASE, sizeof(DE_P0R_REG_H13A0_T));
		//gDE_P0L_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P0L_REG_H13_BASE, sizeof(DE_P0L_REG_H13A0_T));
		//gDE_P0R_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P0R_REG_H13_BASE, sizeof(DE_P0R_REG_H13A0_T));

		gDE_MIA_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIA_REG_H13_BASE, sizeof(DE_MIA_REG_H13A0_T));
		gDE_MIB_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIB_REG_H13_BASE, sizeof(DE_MIB_REG_H13A0_T));
		gDE_MIC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIC_REG_H13_BASE, sizeof(DE_MIC_REG_H13A0_T));
		gDE_MID_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MID_REG_H13_BASE, sizeof(DE_MID_REG_H13A0_T));
		gDE_MIF_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MIF_REG_H13_BASE, sizeof(DE_MIF_REG_H13A0_T));

		gDE_MSL_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MSL_REG_H13_BASE, sizeof(DE_MSL_REG_H13A0_T));
		gDE_MSR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_MSR_REG_H13_BASE, sizeof(DE_MSR_REG_H13A0_T));

		gDE_OVL_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OVL_REG_H13_BASE, sizeof(DE_OVL_REG_H13A0_T));
		gDE_OVR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OVR_REG_H13_BASE, sizeof(DE_OVR_REG_H13A0_T));

		gDE_DPP_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DPP_REG_H13_BASE, sizeof(DE_DPP_REG_H13A0_T));

		gDE_P1L_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P1L_REG_H13_BASE, sizeof(DE_P1L_REG_H13A0_T));
		//gDE_P1R_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_P1R_REG_H13_BASE, sizeof(DE_P1R_REG_H13A0_T));
		//gDE_P1L_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P1L_REG_H13_BASE, sizeof(DE_P1L_REG_H13A0_T));
		//gDE_P1R_H13B.phys.addr = (volatile UINT32 *)ioremap(DE_P1R_REG_H13_BASE, sizeof(DE_P1R_REG_H13A0_T));

		gDE_SSC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_SSC_REG_H13_BASE, sizeof(DE_SSC_REG_H13A0_T));
		//gDE_T3D_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_T3D_REG_H13_BASE, sizeof(DE_T3D_REG_H13A0_T));
		gDE_OSD_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OSD_REG_H13_BASE, sizeof(DE_OSD_REG_H13A0_T));
		//gDE_ATP_H13.phys.addr = (volatile UINT32 *)ioremap(DE_ATP_REG_H13B0_BASE, sizeof(DE_ATP_REG_H13A0_T));
		//gDE_OIF_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_OIF_REG_H13_BASE, sizeof(DE_OIF_REG_H13A0_T));
		gDE_CVD_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_CVD_REG_H13_BASE, sizeof(DE_CVD_REG_H13A0_T));

		gDE_IPC_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_IPC_REG_H13_BASE, sizeof(DE_IPC_REG_H13A0_T));
		gDE_DVR_H13.phys.addr  = (volatile UINT32 *)ioremap(DE_DVR_REG_H13_BASE, sizeof(DE_DVR_REG_H13A0_T));

		gDE_VDC_H13.phys.addr  = (volatile UINT32 *)ioremap(VDEC_CPC_IPC_BASE, sizeof(DE_VDI_REG_H13A0_T));
		gDE_VDD_H13.phys.addr  = (volatile UINT32 *)ioremap(VDEC_CPD_IPC_BASE, sizeof(DE_VDI_REG_H13A0_T));
	}

	gpDeMem = &gMemCfgDe[1];
	gpAdrPreW = &gMemCfgDePreW[0];
	gpAdrGrap = &gMemCfgDeGrap[0];

	spVideoIPCofCPU[0] = (UINT32 *)gDE_VDC_H13.phys.addr;
	spVideoIPCofCPU[1] = (UINT32 *)gDE_VDD_H13.phys.addr;

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
int DE_REG_H13_FreePHY2VIRT(void)
{
	OS_Free((void *)gDE_DEA_H13.shdw.addr);
	OS_Free((void *)gDE_DEB_H13.shdw.addr);
	OS_Free((void *)gDE_DEC_H13.shdw.addr);
	OS_Free((void *)gDE_DED_H13.shdw.addr);
	OS_Free((void *)gDE_DEE_H13.shdw.addr);
	OS_Free((void *)gDE_DEF_H13.shdw.addr);

	OS_Free((void *)gDE_CVA_H13.shdw.addr);
	OS_Free((void *)gDE_CVB_H13.shdw.addr);

	//OS_Free((void *)gDE_DLR_H13.shdw.addr);

	OS_Free((void *)gDE_P0L_H13.shdw.addr);
	OS_Free((void *)gDE_P0R_H13.shdw.addr);
	//OS_Free((void *)gDE_P0L_H13B.shdw.addr);
	//OS_Free((void *)gDE_P0R_H13B.shdw.addr);

	OS_Free((void *)gDE_MIA_H13.shdw.addr);
	OS_Free((void *)gDE_MIB_H13.shdw.addr);
	OS_Free((void *)gDE_MIC_H13.shdw.addr);
	OS_Free((void *)gDE_MID_H13.shdw.addr);
	OS_Free((void *)gDE_MIF_H13.shdw.addr);

	OS_Free((void *)gDE_MSL_H13.shdw.addr);
	OS_Free((void *)gDE_MSR_H13.shdw.addr);

	OS_Free((void *)gDE_OVL_H13.shdw.addr);
	OS_Free((void *)gDE_OVR_H13.shdw.addr);

	OS_Free((void *)gDE_DPP_H13.shdw.addr);

	OS_Free((void *)gDE_P1L_H13.shdw.addr);
	//OS_Free((void *)gDE_P1R_H13.shdw.addr);
	//OS_Free((void *)gDE_P1L_H13B.shdw.addr);
	//OS_Free((void *)gDE_P1R_H13B.shdw.addr);

	OS_Free((void *)gDE_SSC_H13.shdw.addr);
	//OS_Free((void *)gDE_T3D_H13.shdw.addr);
	OS_Free((void *)gDE_OSD_H13.shdw.addr);
	//OS_Free((void *)gDE_ATP_H13.shdw.addr);
	//OS_Free((void *)gDE_OIF_H13.shdw.addr);
	OS_Free((void *)gDE_CVD_H13.shdw.addr);

	OS_Free((void *)gDE_VDC_H13.shdw.addr);
	OS_Free((void *)gDE_VDD_H13.shdw.addr);
	OS_Free((void *)gDE_IPC_H13.shdw.addr);
	OS_Free((void *)gDE_DVR_H13.shdw.addr);

	if (gDE_DEA_H13.phys.addr) iounmap((void *)gDE_DEA_H13.phys.addr);
	if (gDE_DEB_H13.phys.addr) iounmap((void *)gDE_DEB_H13.phys.addr);
	if (gDE_DEC_H13.phys.addr) iounmap((void *)gDE_DEC_H13.phys.addr);
	if (gDE_DED_H13.phys.addr) iounmap((void *)gDE_DED_H13.phys.addr);
	if (gDE_DEE_H13.phys.addr) iounmap((void *)gDE_DEE_H13.phys.addr);
	if (gDE_DEF_H13.phys.addr) iounmap((void *)gDE_DEF_H13.phys.addr);

	if (gDE_CVA_H13.phys.addr) iounmap((void *)gDE_CVA_H13.phys.addr);
	if (gDE_CVB_H13.phys.addr) iounmap((void *)gDE_CVB_H13.phys.addr);

	//if (gDE_DLR_H13.phys.addr) iounmap((void *)gDE_DLR_H13.phys.addr);

	if (gDE_P0L_H13.phys.addr) iounmap((void *)gDE_P0L_H13.phys.addr);
	if (gDE_P0R_H13.phys.addr) iounmap((void *)gDE_P0R_H13.phys.addr);
	//if (gDE_P0L_H13B.phys.addr) iounmap((void *)gDE_P0L_H13B.phys.addr);
	//if (gDE_P0R_H13B.phys.addr) iounmap((void *)gDE_P0R_H13B.phys.addr);

	if (gDE_MIA_H13.phys.addr) iounmap((void *)gDE_MIA_H13.phys.addr);
	if (gDE_MIB_H13.phys.addr) iounmap((void *)gDE_MIB_H13.phys.addr);
	if (gDE_MIC_H13.phys.addr) iounmap((void *)gDE_MIC_H13.phys.addr);
	if (gDE_MID_H13.phys.addr) iounmap((void *)gDE_MID_H13.phys.addr);
	if (gDE_MIF_H13.phys.addr) iounmap((void *)gDE_MIF_H13.phys.addr);

	if (gDE_MSL_H13.phys.addr) iounmap((void *)gDE_MSL_H13.phys.addr);
	if (gDE_MSR_H13.phys.addr) iounmap((void *)gDE_MSR_H13.phys.addr);

	if (gDE_OVL_H13.phys.addr) iounmap((void *)gDE_OVL_H13.phys.addr);
	if (gDE_OVR_H13.phys.addr) iounmap((void *)gDE_OVR_H13.phys.addr);

	if (gDE_DPP_H13.phys.addr) iounmap((void *)gDE_DPP_H13.phys.addr);

	if (gDE_P1L_H13.phys.addr) iounmap((void *)gDE_P1L_H13.phys.addr);
	//if (gDE_P1R_H13.phys.addr) iounmap((void *)gDE_P1R_H13.phys.addr);
	//if (gDE_P1L_H13B.phys.addr) iounmap((void *)gDE_P1L_H13B.phys.addr);
	//if (gDE_P1R_H13B.phys.addr) iounmap((void *)gDE_P1R_H13B.phys.addr);

	if (gDE_SSC_H13.phys.addr) iounmap((void *)gDE_SSC_H13.phys.addr);
	//if (gDE_T3D_H13.phys.addr) iounmap((void *)gDE_T3D_H13.phys.addr);
	if (gDE_OSD_H13.phys.addr) iounmap((void *)gDE_OSD_H13.phys.addr);
	//if (gDE_ATP_H13.phys.addr) iounmap((void *)gDE_ATP_H13.phys.addr);
	//if (gDE_OIF_H13.phys.addr) iounmap((void *)gDE_OIF_H13.phys.addr);
	if (gDE_CVD_H13.phys.addr) iounmap((void *)gDE_CVD_H13.phys.addr);

	if (gDE_VDC_H13.phys.addr) iounmap((void *)gDE_VDC_H13.phys.addr);
	if (gDE_VDD_H13.phys.addr) iounmap((void *)gDE_VDD_H13.phys.addr);
	if (gDE_IPC_H13.phys.addr) iounmap((void *)gDE_IPC_H13.phys.addr);
	if (gDE_DVR_H13.phys.addr) iounmap((void *)gDE_DVR_H13.phys.addr);

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
int DE_IPC_H13_GetStatusReg(VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
		case VIDEO_DMA_MCU :
		case VIDEO_JPG_MCU :
		case VIDEO_WEL_MCU :
		case VIDEO_WER_MCU :
			DE_IPC_H13_RdFL(int_intr_status);
			*pStatus = DE_IPC_H13_Rd(int_intr_status);
			break;
		case VIDEO_IPC_CPU :
		case VIDEO_DMA_CPU :
		case VIDEO_JPG_CPU :
		case VIDEO_WEL_CPU :
		case VIDEO_WER_CPU :
			DE_IPC_H13_RdFL(ext_intr_status);
			*pStatus = DE_IPC_H13_Rd(ext_intr_status);
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
int DE_WDG_H13_WakeUpReg(BOOLEAN turnOn)
{
	if (turnOn) {
		DE_IPC_H13_FLWf(ext_intr_event, wdg_interrupt_event, 1);
	} else {
		DE_IPC_H13_FLWf(ext_intr_clear, wdg_interrupt_clear, 1);
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
int DE_IPC_H13_WakeUpReg(VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn)
{
	int ret = RET_OK;

	turnOn &= 0x1;
	switch (ipcType) {
		case VIDEO_IPC_MCU :
			if (turnOn) {
				DE_IPC_H13_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_IPC_CPU :
			if (turnOn) {
				DE_IPC_H13_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_MCU :
			if (turnOn) {
				DE_IPC_H13_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_CPU :
			if (turnOn) {
				DE_IPC_H13_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_MCU :
			if (turnOn) {
				DE_IPC_H13_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_CPU :
			if (turnOn) {
				DE_IPC_H13_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_MCU :
			if (turnOn) {
				DE_IPC_H13_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_CPU :
			if (turnOn) {
				DE_IPC_H13_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_MCU :
			if (turnOn) {
				DE_IPC_H13_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_CPU :
			if (turnOn) {
				DE_IPC_H13_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_MCU :
			if (turnOn) {
				DE_IPC_H13_FLWf(int_intr_event, ipc_interrupt_event_mcu, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(int_intr_clear, ipc_interrupt_clear_mcu, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_CPU :
			if (turnOn) {
				DE_IPC_H13_FLWf(ext_intr_event, ipc_interrupt_event_arm, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_H13_FLWf(ext_intr_clear, ipc_interrupt_clear_arm, GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
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
int DE_REG_H13_WD(UINT32 addr, UINT32 value)
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
		if		(recvAddr <= 0x6000) recvAddr += DTVSOC_DE_H13_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_DE_H13_BASE;
		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;

		virtAddr = (UINT32)ioremap(currAddr, 0x8);
		if (currAddr == recvAddr) {
			REG_WD(virtAddr, value);
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
UINT32 DE_REG_H13_RD(UINT32 addr)
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
		if		(recvAddr <= 0x6000) recvAddr += DTVSOC_DE_H13_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_DE_H13_BASE;

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
int DE_REG_H13_SetFrRate(DE_DPLL_CLK_T dclk)
{
	int ret = RET_OK;
#ifdef USE_CTOP_CODES_FOR_H13
#ifdef USE_KDRV_CODES_FOR_H13
	DE_DPLL_DIV_T *pDisplayPll = NULL;
	int i;

	do {
		for (i=0;i<ARRAY_SIZE(sDisplayPll_H13);i++) {
			if (sDisplayPll_H13[i].clk != dclk) continue;
			pDisplayPll =  &sDisplayPll_H13[i].div;
			break;
		}
		CHECK_KNULL(pDisplayPll);
#if 1 //default  de = 148.5 MHz , dpll = 297MHz
		CTOP_CTRL_H13_RdFL(ctr83);
		CTOP_CTRL_H13_Wr01(ctr83, disp_nsc_ctrl,	   pDisplayPll->dpllM);
		CTOP_CTRL_H13_Wr01(ctr83, disp_npc_ctrl,	   pDisplayPll->dpllN);
		CTOP_CTRL_H13_WrFL(ctr83);
#endif
	} while (0);
#endif
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
int DE_REG_H13_GetFrRate(LX_DE_FR_RATE_T *pstParams)
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
int DE_REG_H13_SetBgColor(LX_DE_COLOR_T *pBackColor)
{
	int ret = RET_OK;

	DE_OVL_H13_RdFL(ovl_ov_ctrl2);

	pBackColor->r >>= 4;
	pBackColor->b >>= 4;
	DE_OVL_H13_Wr01(ovl_ov_ctrl2, back_color_cr, pBackColor->r);
	DE_OVL_H13_Wr01(ovl_ov_ctrl2, back_color_cb, pBackColor->b);
	DE_OVL_H13_Wr01(ovl_ov_ctrl2, back_color_yy, pBackColor->g);

	DE_OVL_H13_WrFL(ovl_ov_ctrl2);

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
int DE_REG_H13_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank)
{
	int ret = RET_OK;

	do {
		DE_OVL_H13_RdFL(ovl_ov_ctrl4);
		switch (pWinBlank->win_id) {
			case LX_DE_WIN_MAIN :
				DE_OVL_H13_Wr01(ovl_ov_ctrl4, w0_dark_en, pWinBlank->bEnable);
				break;
			case LX_DE_WIN_SUB :
				DE_OVL_H13_Wr01(ovl_ov_ctrl4, w1_dark_en, pWinBlank->bEnable);
				break;
			default :
				BREAK_WRONG(pWinBlank->win_id);
		}
		if (ret) break;
		DE_OVL_H13_WrFL(ovl_ov_ctrl4);

		pWinBlank->win_color.r >>= 4;
		pWinBlank->win_color.b >>= 4;
		DE_OVR_H13_RdFL(ovr_ov_ctrl2);
		DE_OVR_H13_Wr01(ovr_ov_ctrl2, dark_color_cr, pWinBlank->win_color.r);
		DE_OVR_H13_Wr01(ovr_ov_ctrl2, dark_color_cb, pWinBlank->win_color.b);
		DE_OVR_H13_Wr01(ovr_ov_ctrl2, dark_color_yy, pWinBlank->win_color.g);
		DE_OVR_H13_WrFL(ovr_ov_ctrl2);
	} while (0);

	return ret;
}

BOOLEAN DE_REG_H13_CheckIrq4Vsync(void)
{
	int ret;
	//DE_FUNC_INTR	de_func_intr;
	//DE1A_INTR_REG de1a_intr_reg;
	H13A0_DEC_DE_INTR_FLAG_CPU_T		 dec_de_intr_flag_cpu;				  // 0x4004
	H13A0_DEB_INTR_REG_T				 deb_intr_reg;						  // 0x1080
	UINT32 videoIntrDe;
	BOOLEAN vsyncIrq;

	do {
		vsyncIrq = 0;
		ret = DE_REG_H13_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_FUNC, &videoIntrDe);
		if (ret) break;

		dec_de_intr_flag_cpu  = *(H13A0_DEC_DE_INTR_FLAG_CPU_T	*)&videoIntrDe;
		if (!dec_de_intr_flag_cpu.deb_dec_intr_cpu) break;
		ret = DE_REG_H13_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_DEB, &videoIntrDe);
		if (ret) break;

		deb_intr_reg = *(H13A0_DEB_INTR_REG_T *)&videoIntrDe;
		if (!deb_intr_reg.disp_intr_for_cpu) break;
		vsyncIrq = 1;
	} while (0);

	return vsyncIrq;
}

int DE_REG_H13_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus)
{
	int ret = RET_OK;
	UINT32 intrReg;
	UINT32 intrMux;

	do {
		CHECK_KNULL(pVideoIrqStatus);
		switch (intrType) {
			case VIDEO_INTR_TYPE_DEA :
				DE_DEA_H13_RdFL(dea_intr_reg);
				DE_DEA_H13_WrFL(dea_intr_reg);
				*pVideoIrqStatus = DE_DEA_H13_Rd(dea_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DEB :
				DE_DEB_H13_RdFL(deb_intr_reg);
				DE_DEB_H13_RdFL(deb_intr_mux);
				intrReg = DE_DEB_H13_Rd(deb_intr_reg);
				intrMux = DE_DEB_H13_Rd(deb_intr_mux);
#ifdef USE_LINUX_KERNEL
				intrReg &=	intrMux;
#else
				intrReg &= ~intrMux;
#endif
				DE_DEB_H13_Wr(deb_intr_reg, intrReg);
				DE_DEB_H13_WrFL(deb_intr_reg);
				*pVideoIrqStatus = DE_DEB_H13_Rd(deb_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DEC :
				DE_DEC_H13_RdFL(dec_intr_reg);
				DE_DEC_H13_WrFL(dec_intr_reg);
				*pVideoIrqStatus = DE_DEC_H13_Rd(dec_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DED :
				DE_DED_H13_RdFL(ded_intr_reg);
				DE_DED_H13_WrFL(ded_intr_reg);
				*pVideoIrqStatus = DE_DED_H13_Rd(ded_intr_reg);
				break;
			case VIDEO_INTR_TYPE_DEE :
				DE_DEE_H13_RdFL(dee_intr_reg);
				DE_DEE_H13_WrFL(dee_intr_reg);
				*pVideoIrqStatus = DE_DEE_H13_Rd(dee_intr_reg);
				break;
			case VIDEO_INTR_TYPE_FUNC :
				DE_DEE_H13_RdFL(dec_de_intr_flag_cpu);
				*pVideoIrqStatus = DE_DEE_H13_Rd(dec_de_intr_flag_cpu);
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
int DE_REG_H13_GrabPixel(LX_DE_GRAB_PIXEL_T *pstParams)
{
	int ret = RET_OK;
#ifdef USE_FRAME_COPY_TO_NFS_FILE
    OS_FILE_T   fw_file;
    char filePath[200] = "/home/jaemo.kim/res/lglib/kdrv/";
    char fileName[200];
#endif
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
	UINT32 bankOffsetY;
	UINT32 bankOffsetC;
	UINT32 grabBaseAddr;
	UINT32 smuxSample;
	UINT8 colorDepth;
	UINT32 phyAddrY8;
	UINT32 phyAddrC8;
	UINT32 phyAddrY2;
	UINT32 phyAddrC2;

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
		colorDepth	   = GET_BITS(pstParams->region.colorDepth 	   ,0  ,4);

		grabSize  = grabW  * grabH;
		framSize  = frameW * frameH;
		if (!grabSize) break;
		if (!framSize) break;

		grabBaseAddr = GET_SVAL(pstParams->region.colorDepth,4,4,28);
		bankOffsetY  = bankPrewY * PIXEL_PER_BANK;
		bankOffsetC  = bankPrewC * PIXEL_PER_BANK;
		phyAddrY8 = (CONV_MEM_ROW2BYTE(phyFrameAddrY8) + bankOffsetY) | grabBaseAddr;
		phyAddrY2 = (CONV_MEM_ROW2BYTE(phyFrameAddrY2) + bankOffsetY) | grabBaseAddr;
		phyAddrC8 = (CONV_MEM_ROW2BYTE(phyFrameAddrC8) + bankOffsetC) | grabBaseAddr;
		phyAddrC2 = (CONV_MEM_ROW2BYTE(phyFrameAddrC2) + bankOffsetC) | grabBaseAddr;
		pFrameAddrY8 = (UINT8 *)ioremap(phyAddrY8, framSize);
		pFrameAddrY2 = (UINT8 *)ioremap(phyAddrY2, framSize/4);
		pFrameAddrC8 = (UINT8 *)ioremap(phyAddrC8, framSize*smuxSample);
		pFrameAddrC2 = (UINT8 *)ioremap(phyAddrC2, framSize/4*smuxSample);
#ifdef USE_FRAME_COPY_TO_NFS_FILE
		do {
			sprintf(fileName, "%sVideo_Grab__%dx%d.Y.img",filePath, frameW, frameH);
			printk("Writing %s\n", fileName);
			if ( RET_OK != OS_OpenFile( &fw_file, fileName, O_CREAT|O_RDWR|O_LARGEFILE, 0666 ) )
			{
				printk("<error> can't open fw_file (%s)\n", fileName);
				if (ret) BREAK_WRONG(ret);
			}
			ret = OS_WriteFile(&fw_file, (char *)pFrameAddrY8, framSize);
			if (ret != framSize) BREAK_WRONG(ret);
			ret = OS_CloseFile( &fw_file );
			if (ret) BREAK_WRONG(ret);
			printk("Done %s\n", fileName);

			sprintf(fileName, "%sVideo_Grab__%dx%d.C.img",filePath, frameW, frameH);
			printk("Writing %s\n", fileName);
			if ( RET_OK != OS_OpenFile( &fw_file, fileName, O_CREAT|O_RDWR|O_LARGEFILE, 0666 ) )
			{
				printk("<error> can't open fw_file (%s)\n", fileName);
				BREAK_WRONG(ret);
			}
			ret = OS_WriteFile(&fw_file, (char *)pFrameAddrC8, framSize*smuxSample);
			if (ret != framSize*smuxSample) BREAK_WRONG(ret);
			ret = OS_CloseFile( &fw_file );
			if (ret) BREAK_WRONG(ret);
			printk("Done %s\n", fileName);
		} while (0);
		if (ret) BREAK_WRONG(ret);
#endif
		pixelG8  = 0;
		pixelB8  = 0;
		pixelR8  = 0;
		pixelG2  = 0;
		pixelB2  = 0;
		pixelR2  = 0;
		grabSize = 0;
		offsetY  = 0;
		offsetC  = 0;
		for (y=0;y<grabH;y++) {
			startY = (grabY + y) * frameW + grabX;
			for (x=0;x<grabW;x++) {
				grabSize++;
				posY	 = offsetY + (startY + x);
				posC	 = offsetC + (startY + x) * smuxSample;
				posC    &= GET_RMSK(0,1);
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
int DE_REG_H13_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams)
{
	int ret = RET_OK;
#ifdef USE_FRAME_COPY_TO_NFS_FILE
    OS_FILE_T   fw_file;
    char filePath[200] = "/home/jaemo.kim/res/lglib/kdrv/";
    char fileName[200];
#endif
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
	UINT32 bankOffsetY;
	UINT32 bankOffsetC;
	UINT32 grabBaseAddr;
	UINT32 smuxSample;
	UINT8 colorDepth;
	UINT32 phyAddrY8;
	UINT32 phyAddrC8;
	UINT32 phyAddrY2;
	UINT32 phyAddrC2;

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
		colorDepth	   = GET_BITS(pstParams->region.colorDepth 	   ,0  ,4);

		grabSize = grabW  * grabH;
		framSize = frameW * frameH;
		if (!grabSize) break;
		if (!framSize) break;

		grabBaseAddr = GET_SVAL(pstParams->region.colorDepth,4,4,28);
		bankOffsetY  = bankPrewY * PIXEL_PER_BANK;
		bankOffsetC  = bankPrewC * PIXEL_PER_BANK;
		phyAddrY8 = (CONV_MEM_ROW2BYTE(phyFrameAddrY8) + bankOffsetY) | grabBaseAddr;
		phyAddrY2 = (CONV_MEM_ROW2BYTE(phyFrameAddrY2) + bankOffsetY) | grabBaseAddr;
		phyAddrC8 = (CONV_MEM_ROW2BYTE(phyFrameAddrC8) + bankOffsetC) | grabBaseAddr;
		phyAddrC2 = (CONV_MEM_ROW2BYTE(phyFrameAddrC2) + bankOffsetC) | grabBaseAddr;

		pFrameAddrY8 = (UINT8 *)ioremap(phyAddrY8, framSize);
		pFrameAddrY2 = (UINT8 *)ioremap(phyAddrY2, framSize/4);
		pFrameAddrC8 = (UINT8 *)ioremap(phyAddrC8, framSize*smuxSample);
		pFrameAddrC2 = (UINT8 *)ioremap(phyAddrC2, framSize/4*smuxSample);

#ifdef USE_FRAME_COPY_TO_NFS_FILE
		do {
			sprintf(fileName, "%sVideo_Prew__%dx%d.Y.img",filePath, frameW, frameH);
			printk("Writing %s\n", fileName);
			if ( RET_OK != OS_OpenFile( &fw_file, fileName, O_CREAT|O_RDWR|O_LARGEFILE, 0666 ) )
			{
				printk("<error> can't open fw_file (%s)\n", fileName);
				if (ret) BREAK_WRONG(ret);
			}
			ret = OS_WriteFile(&fw_file, (char *)pFrameAddrY8, framSize);
			if (ret != framSize) BREAK_WRONG(ret);
			ret = OS_CloseFile( &fw_file );
			if (ret) BREAK_WRONG(ret);
			printk("Done %s\n", fileName);

			sprintf(fileName, "%sVideo_Prew__%dx%d.C.img",filePath, frameW, frameH);
			printk("Writing %s\n", fileName);
			if ( RET_OK != OS_OpenFile( &fw_file, fileName, O_CREAT|O_RDWR|O_LARGEFILE, 0666 ) )
			{
				printk("<error> can't open fw_file (%s)\n", fileName);
				BREAK_WRONG(ret);
			}
			ret = OS_WriteFile(&fw_file, (char *)pFrameAddrC8, framSize*smuxSample);
			if (ret != framSize*smuxSample) BREAK_WRONG(ret);
			ret = OS_CloseFile( &fw_file );
			if (ret) BREAK_WRONG(ret);
			printk("Done %s\n", fileName);
		} while (0);
		if (ret) BREAK_WRONG(ret);
#endif
		grabSize = 0;
		offsetY  = 0;
		offsetC  = 0;
		for (y=0;y<grabH;y++) {
			startY = (grabY + y) * frameW + grabX;
			grabSize = y * grabStepW;
			for (x=0;x<grabW;x++) {
				pFrameColor = &pstParams->color[grabSize+x];
				posY  = offsetY + (startY + x);
				posC  = offsetC + (startY + x) * smuxSample;
				posC &= GET_RMSK(0,1);
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
int DE_REG_H13_SetInputSrc(LX_DE_SET_INPUT_T *pstParams)
{
#ifdef	USE_CTOP_CODES_FOR_H13
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
		CTOP_CTRL_H13_RdFL(ctr01_reg_clk_div_sel);
		CTOP_CTRL_H13_Wr01(ctr01_reg_clk_div_sel, dco_sel, reg); //setting disp clock from SDEC
		CTOP_CTRL_H13_WrFL(ctr01_reg_clk_div_sel);

	} while (0);
#endif
#endif

	return RET_OK;
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
int DE_REG_H13_SetInSrc(LX_DE_INPUT_CFG_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_MULTI_SRC_T multiSrc = LX_DE_MULTI_IN_MAX;
	LX_DE_SRC_CONFIG  *src_cfg = NULL;
	LX_DE_WIN_ID_T win_id = LX_DE_WIN_MAIN;
	LX_DE_WIN_ID_T other_win_id = LX_DE_WIN_SUB;
	LX_DE_IN_SRC_T in_port = LX_DE_IN_SRC_MVI;
	UINT32 cvi_mux_sel = 0;
	UINT32 exta_sel = 0;
	UINT32 extb_sel = 0;
	UINT32 cvd54_select = 0x0;
	UINT32 scart_mode_enable = 0x0;
	UINT32 i = 0;
	UINT32 srcPort = 0;

	if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
		src_cfg = sMultiSrc_map_H13[0];
	}

	do {
		CHECK_KNULL(src_cfg);
		CHECK_KNULL(pstParams);

		win_id  = pstParams->win_id;
		in_port = pstParams->inputSrc;
		srcPort = pstParams->inputSrcPort;
		if(in_port == LX_DE_IN_SRC_NONE) break;
		switch (win_id)
		{
			case LX_DE_WIN_MAIN :
				{
					if(in_port == g_WinsrcMap_H13[LX_DE_WIN_MAIN]) return ret;

					if(in_port == LX_DE_IN_SRC_CVBS ||in_port == LX_DE_IN_SRC_ATV || in_port == LX_DE_IN_SRC_SCART)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_SUB]) {
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_CVD_ADC;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_CVD_HDMI;
								break;
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_CVD_CVD;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_CVD_MVI;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_CVD_CPU;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_YPBPR || in_port == LX_DE_IN_SRC_VGA)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_SUB]) {
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_ADC_CVD;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_ADC_HDMI;
								break;
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_ADC_ADC;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_ADC_MVI;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_ADC_CPU;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_HDMI)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_SUB]) {
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART:
								multiSrc = LX_DE_MULTI_IN_HDMI_CVD;
								break;
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_HDMI_ADC;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_HDMI;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_HDMI_MVI;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_HDMI_CPU;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_MVI)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_SUB]) {
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_MVI_CVD;
								break;
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_MVI_ADC;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_MVI_HDMI;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_MVI;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_MVI_CPU;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_CPU)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_SUB]) {
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_CPU_CVD;
								break;
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_CPU_ADC;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_CPU_HDMI;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_CPU_MVI;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_CPU_CPU;
								break;
							default :
								break;
						}
					}

					g_WinsrcMap_H13[LX_DE_WIN_MAIN] = in_port;
					g_WinsrcPort_H13[LX_DE_WIN_MAIN] = srcPort;
					other_win_id = LX_DE_WIN_SUB;
				}
				break;
			case LX_DE_WIN_SUB :
				{
					if(in_port == g_WinsrcMap_H13[LX_DE_WIN_SUB]) return ret;

					if(in_port == LX_DE_IN_SRC_CVBS ||in_port == LX_DE_IN_SRC_ATV || in_port == LX_DE_IN_SRC_SCART)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_MAIN]) {
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_ADC_CVD;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_CVD;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_CVD;
								break;
							case LX_DE_IN_SRC_ATV:
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_CVD_CVD;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_CPU_CVD;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_YPBPR || in_port == LX_DE_IN_SRC_VGA)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_MAIN]) {
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_CVD_ADC;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_ADC;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_ADC;
								break;
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_ADC_ADC;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_CPU_ADC;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_HDMI)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_MAIN]) {
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_CVD_HDMI;
								break;
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_ADC_HDMI;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_HDMI;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_HDMI;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_CPU_HDMI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_MVI)
					{
						switch (g_WinsrcMap_H13[LX_DE_WIN_MAIN]) {
							case LX_DE_IN_SRC_ATV :
							case LX_DE_IN_SRC_CVBS :
							case LX_DE_IN_SRC_SCART :
								multiSrc = LX_DE_MULTI_IN_CVD_MVI;
								break;
							case LX_DE_IN_SRC_VGA :
							case LX_DE_IN_SRC_YPBPR :
								multiSrc = LX_DE_MULTI_IN_ADC_MVI;
								break;
							case LX_DE_IN_SRC_HDMI :
								multiSrc = LX_DE_MULTI_IN_HDMI_MVI;
								break;
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_MVI;
								break;
							case LX_DE_IN_SRC_CPU :
								multiSrc = LX_DE_MULTI_IN_CPU_MVI;
							default :
								break;
						}
					}

					g_WinsrcMap_H13[LX_DE_WIN_SUB] = in_port;
					g_WinsrcPort_H13[LX_DE_WIN_SUB] = srcPort;
					other_win_id = LX_DE_WIN_MAIN;
				}
				break;
			default :
				BREAK_WRONG(win_id);
		}
		if (ret) break;

		for (i = LX_DE_MULTI_IN_CVD_ADC; i < LX_DE_MULTI_IN_MAX; i++)
		{
			if (src_cfg[i].src  != multiSrc) continue;
			if (src_cfg[i].used != TRUE)     continue;

			cvi_mux_sel = src_cfg[i].cvi_mux_sel;
			exta_sel = src_cfg[i].exta_sel;
			extb_sel = src_cfg[i].extb_sel;
		}

		if (multiSrc >= LX_DE_MULTI_IN_MAX)
		{
			ret = RET_ERROR;
			DE_PRINT("\nInvalid mapping \n\n");
		}

		DE_PRINT("win_id[%d] in_port[%d] main/sub[%d/%d] \n",
				win_id, in_port, g_WinsrcMap_H13[LX_DE_WIN_MAIN], g_WinsrcMap_H13[LX_DE_WIN_SUB]);
		DE_PRINT(" => NONE(0)/VGA(1)/YPBPR(2)/ATV(3)/CVD(4)/SCART(5)/HDMI(6)/MVI(7)/CPU(8)\n");
		DE_PRINT(" => multiSrc[%d] cvi_mux_sel[0x%02X] exta_sel[%d] extb_sel[%d]\n",
				multiSrc, cvi_mux_sel, exta_sel, extb_sel);

		if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
			if( pstParams->inputSrc == LX_DE_IN_SRC_SCART || g_WinsrcMap_H13[other_win_id] == LX_DE_IN_SRC_SCART) {	// for SCART RGB inputs
				cvd54_select = 0x1;
				scart_mode_enable = 0x1;
				DE_PRINT("SCART RGB Mode\n");
			}
			else {
				cvd54_select = 0x0;
				scart_mode_enable = 0x0;
				DE_PRINT("Non SCART RGB Mode\n");
			}
			DE_DEE_H13_RdFL(dee_cvi_mux_sel);
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvia_input_sel, (cvi_mux_sel & 0xF0) >> 4);
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvib_input_sel, (cvi_mux_sel & 0x0F) >> 0);
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, lvds_type_sel, 0); // 0:VESA, 1:JEIDA
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvi_input_sel, 0); // 0:ADC output, 1:CVE output
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, scart_mode_en, scart_mode_enable);
			DE_DEE_H13_WrFL(dee_cvi_mux_sel);
#ifdef USE_CTOP_CODES_FOR_H13
			CTOP_CTRL_H13_RdFL(ctr26);
			CTOP_CTRL_H13_Wr01(ctr26, exta_sel, exta_sel);
			CTOP_CTRL_H13_Wr01(ctr26, extb_sel, extb_sel);
			CTOP_CTRL_H13A0_Wr01(ctr26, cvd54_sel, cvd54_select);
			CTOP_CTRL_H13_WrFL(ctr26);
#endif
		}
	} while(0);

	return ret;
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
int DE_REG_H13_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams)
{
	int ret = RET_OK;
	UINT32 cviSampling = 0;
	UINT32 xsize_divide = 0;
	UINT32 lvds_speed = 0x1;
	//UINT32 exta_sel = 0;
	//UINT32 extb_sel = 0;

	do {
		CHECK_KNULL(pstParams);
		memcpy(&sCviSrcType, pstParams, sizeof(LX_DE_CVI_SRC_TYPE_T));
		if( (pstParams->cvi_input_src == LX_DE_CVI_SRC_ATV) || (pstParams->cvi_input_src == LX_DE_CVI_SRC_CVBS) || (pstParams->cvi_input_src == LX_DE_CVI_SRC_SCART) ) {	// for CVD inputs
			//LVDS IF SEL
			// Set to High Speed Mode (ADC clock is over 72MHz)
#ifdef	USE_CTOP_CODES_FOR_H13
			CTOP_CTRL_H13A0_RdFL(ctr93);
			CTOP_CTRL_H13A0_Wr01(ctr93, rx0_sel_speed_en, lvds_speed);
			CTOP_CTRL_H13A0_WrFL(ctr93);
#endif
//			DE_PRINT("CVD Set LVDS SPEED to [%d]\n", lvds_speed);
		}
		else if (pstParams->cvi_input_src == LX_DE_CVI_SRC_YPBPR) {
			DE_PRINT("ADC vsize [%d]\n", pstParams->size_offset.vsize);
			if(pstParams->size_offset.vsize < 650) // for SD Videos (bitrates less than 27MHz)
				lvds_speed = 0x0;
			else
				lvds_speed = 0x1;

#ifdef	USE_CTOP_CODES_FOR_H13
			CTOP_CTRL_H13A0_RdFL(ctr93);
			CTOP_CTRL_H13A0_Wr01(ctr93, rx0_sel_speed_en, lvds_speed);
			CTOP_CTRL_H13A0_WrFL(ctr93);
#endif
//			DE_PRINT("ADC Set LVDS SPEED to [%d]\n", lvds_speed);
		}

		switch (pstParams->sampling) {
			case LX_DE_CVI_NORMAL_SAMPLING :
				cviSampling  = 0;
				xsize_divide = 0;
				break;
			case LX_DE_CVI_DOUBLE_SAMPLING :
				cviSampling  = 1;
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
				if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
#ifdef USE_CTOP_CODES_FOR_H13
					CTOP_CTRL_H13_RdFL(ctr26);
					CTOP_CTRL_H13_Wr01(ctr26, msclk_sel, xsize_divide);
					CTOP_CTRL_H13_WrFL(ctr26);
#endif
#ifndef USE_DE_CVI_ACCESS_REGISTER_ON_MCU_PART
					DE_CVA_H13B_RdFL(cva_dig_filt_ctrl3);
					DE_CVA_H13B_RdFL(cva_misc_ctrl);
					DE_CVA_H13B_Wr01(cva_dig_filt_ctrl3, fir_en,		(!cviSampling)?0:1);
					DE_CVA_H13B_WfCM(cva_dig_filt_ctrl3, fir_y_en,	  cviSampling, 0x1);
					//DE_CVA_H13B_WfCM(cva_dig_filt_ctrl3, fir_c_en,   cviSampling, 0x1); // control in DE_REG_H13_SetCviCsampleMode()
					DE_CVA_H13B_Wr01(cva_dig_filt_ctrl3, fir_sampling_rate, cviSampling);
					DE_CVA_H13B_Wr01(cva_misc_ctrl, xsize_divide, xsize_divide);
					DE_CVA_H13B_WrFL(cva_dig_filt_ctrl3);
					DE_CVA_H13B_WrFL(cva_misc_ctrl);
#endif
				}
				break;
			case LX_DE_CVI_CH_B :
				if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
#ifdef USE_CTOP_CODES_FOR_H13
					CTOP_CTRL_H13_RdFL(ctr26);
					CTOP_CTRL_H13_Wr01(ctr26, ssclk_sel, xsize_divide);
					CTOP_CTRL_H13_WrFL(ctr26);
#endif
#ifndef USE_DE_CVI_ACCESS_REGISTER_ON_MCU_PART
					DE_CVB_H13B_RdFL(cvb_dig_filt_ctrl3);
					DE_CVB_H13B_RdFL(cvb_misc_ctrl);
					DE_CVB_H13B_Wr01(cvb_dig_filt_ctrl3, fir_en,		(!cviSampling)?0:1);
					DE_CVB_H13B_WfCM(cvb_dig_filt_ctrl3, fir_y_en,	   cviSampling, 0x1);
					//DE_CVB_H13B_WfCM(cvb_dig_filt_ctrl3, fir_c_en,		cviSampling, 0x1); // control in DE_REG_H13_SetCviCsampleMode()
					DE_CVB_H13B_Wr01(cvb_dig_filt_ctrl3, fir_sampling_rate, cviSampling);
					DE_CVB_H13B_Wr01(cvb_misc_ctrl, xsize_divide, xsize_divide);
					DE_CVB_H13B_WrFL(cvb_dig_filt_ctrl3);
					DE_CVB_H13B_WrFL(cvb_misc_ctrl);
#endif

				}
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;

#ifdef USE_CTOP_CODES_FOR_H13
		if(pstParams->cvi_input_src != LX_DE_CVI_SRC_HDMI) break;
		CTOP_CTRL_H13_RdFL(ctr26);
		DE_DEE_H13_RdFL(dee_cvi_mux_sel);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl0);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl1);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl2);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl3);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl4);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl5);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl6);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl7);
		DE_DEE_H13_RdFL(dee_hdmi_bridge_ctrl8);
		switch(pstParams->trid_full_format)
		{
			case LX_DE_CVI_4K_2K :
				CTOP_CTRL_H13_Wr01(ctr26, exta_sel, 0x2);
				CTOP_CTRL_H13_Wr01(ctr26, extb_sel, 0x2);

				DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvia_input_sel, 0x3);
				DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvib_input_sel, 0x4);

				if(sbDeUdMode == 2) // half mode
				{
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, ctr_3dfr_mode, 0x2);       // 0:LR split with UD, 1:LR split with 297MHz 3D FRP, 2:half down with UD

					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl1, y_fir_coef0, 0x3FE);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl1, y_fir_coef1, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl2, y_fir_coef2, 0x40);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl2, y_fir_coef3, 0x84);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl3, y_fir_coef4, 0x40);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl3, y_fir_coef5, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl4, y_fir_coef6, 0x3FE);

					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl5, c_fir_coef0, 0x3FE);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl5, c_fir_coef1, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl6, c_fir_coef2, 0x40);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl6, c_fir_coef3, 0x84);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl7, c_fir_coef4, 0x40);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl7, c_fir_coef5, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl8, c_fir_coef6, 0x3FE);
				}
				else
				{
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, ctr_3dfr_mode, 0x0);       // 0:LR split with UD, 1:LR split with 297MHz 3D FRP, 2:half down with UD

					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl1, y_fir_coef0, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl1, y_fir_coef1, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl2, y_fir_coef2, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl2, y_fir_coef3, 0x100);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl3, y_fir_coef4, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl3, y_fir_coef5, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl4, y_fir_coef6, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl5, c_fir_coef0, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl5, c_fir_coef1, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl6, c_fir_coef2, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl6, c_fir_coef3, 0x100);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl7, c_fir_coef4, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl7, c_fir_coef5, 0x0);
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl8, c_fir_coef6, 0x0);
				}
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, input_sync_polarity, 0x1); // 0:positive polarity, 1:negative polarity
				if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) ) {
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, output_sync_polarity, 0x1);// 0:positive polarity, 1:negative polarity
				} else {
					DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, output_sync_polarity, 0x0);// 0:positive polarity, 1:negative polarity
				}
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, field_polarity, 0x0);      // 0:normal, 1:field inversion
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, ctr_3dfr_autoset, 0x0);    // 0:manual, 1:auto sync param (3DFR)
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, ud_autoset, 0x1);          // 0:manual, 1:auto sync param (UD src)
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, sync_delay, 0x2);          // sync delay
				break;

			case LX_DE_CVI_NORMAL_FORMAT :
			case LX_DE_CVI_3D_FRAMEPACK :
			case LX_DE_CVI_3D_SBSFULL :
			case LX_DE_CVI_3D_FIELD_ALTERNATIVE :
			case LX_DE_CVI_3D_ROW_INTERLEAVING :
			case LX_DE_CVI_3D_COLUMN_INTERLEAVING :
			default :
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, ctr_3dfr_mode, 0x0);       // 0:LR split with UD, 1:LR split with 297MHz 3D FRP, 2:half down with UD
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, input_sync_polarity, 0x1); // 0:positive polarity, 1:negative polarity
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, output_sync_polarity, 0x0);// 0:positive polarity, 1:negative polarity
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, field_polarity, 0x0);      // 0:normal, 1:field inversion
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, ctr_3dfr_autoset, 0x0);    // 0:manual, 1:auto sync param (3DFR)
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl0, ud_autoset, 0x0);          // 0:manual, 1:auto sync param (UD src)
				
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl1, y_fir_coef0, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl1, y_fir_coef1, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl2, y_fir_coef2, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl2, y_fir_coef3, 0x100);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl3, y_fir_coef4, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl3, y_fir_coef5, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl4, y_fir_coef6, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl5, c_fir_coef0, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl5, c_fir_coef1, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl6, c_fir_coef2, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl6, c_fir_coef3, 0x100);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl7, c_fir_coef4, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl7, c_fir_coef5, 0x0);
				DE_DEE_H13_Wr01(dee_hdmi_bridge_ctrl8, c_fir_coef6, 0x0);

				if(pstParams->cvi_channel == LX_DE_CVI_CH_A) {
					DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvia_input_sel, 0x1);
				}
				else {
					DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvib_input_sel, 0x1);
				}
				break;
		}
		CTOP_CTRL_H13_WrFL(ctr26);
		DE_DEE_H13_WrFL(dee_cvi_mux_sel);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl0);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl1);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl2);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl3);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl4);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl5);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl6);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl7);
		DE_DEE_H13_WrFL(dee_hdmi_bridge_ctrl8);
#endif
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
int DE_REG_H13_Init(LX_DE_PANEL_TYPE_T *pstParams)
{
	DE_REG_H13_InitAddrSwitch();

	g_Display_size_H13 = *pstParams;
	//DE_REG_H13_OIF_InitLvdsIfCtrl();

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
int DE_REG_H13_GetCviCsc(LX_DE_CVI_CSC_T *pstParams)
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
		ret = DE_PRM_H13_LoadTable(tableId, DE_PARAM_READ, pstParams->isEnable, cscTable, tableArraySize);
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
int DE_REG_H13_SetCviCsc(LX_DE_CVI_CSC_T *pstParams)
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

#ifdef USE_PARM_CODES_FOR_H13
		ret = DE_PRM_H13_LoadTable(tableId, DE_PARAM_WRITE, pstParams->isEnable, cscTable, ARRAY_SIZE(cscTable));
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
int DE_REG_H13_GetPostCsc(LX_DE_POST_CSC_T *pstParams)
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

		ret = DE_PRM_H13_LoadTable(DE_POST_CSC_COEF, DE_PARAM_READ, 0, cscTable, tableArraySize);
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
int DE_REG_H13_SetPostCsc(LX_DE_POST_CSC_T *pstParams)
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

#ifdef USE_PARM_CODES_FOR_H13
		ret = DE_PRM_H13_LoadTable(tableId, DE_PARAM_WRITE, 0, cscTable, ARRAY_SIZE(cscTable));
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
int DE_REG_H13_GetMviColorimetry(LX_DE_MVI_COLORIMETRY_T *pstParams)
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
int DE_REG_H13_SetSpread(LX_DE_SET_SPREAD_T *pstParams)
{
#if 0
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
					break;
				}
			case LX_DE_SPREAD_SPECTRUM_CPU :
				{
					break;
				}
			case LX_DE_SPREAD_SPECTRUM_LVDS :
				{
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
int DE_REG_H13_SetDeinterlace(BOOLEAN bEnable)
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
int DE_REG_H13_SetVcs(LX_DE_VCS_IPC_T *pstParams)
{
	int ret = RET_OK;
	int channel;
	int inx;

	do {
		CHECK_KNULL(pstParams);
		channel = GET_BITS(pstParams->inx, 31,	1);
		inx		= GET_BITS(pstParams->inx,	0, 30);
		if (inx > SIZE_OF_IPC_FOR_CPU ) BREAK_WRONG(inx);
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
int DE_REG_H13_OIF_SetVesaJeida(LX_DE_OIF_STD_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SetPanelIf(LX_DE_OIF_PANEL_IF_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SetPixel(LX_DE_OIF_PIXEL_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SetBitDepth(LX_DE_OIF_BIT_DEPTH_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SelectOutPath(LX_DE_OIF_OUTPUT_PATH_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SelectLvdsPath(LX_DE_OIF_LVDS_PATH_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SelectOutCh(LX_DE_OIF_OUTPUT_CH_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SelectLedPath(LX_DE_OIF_LED_IN_PATH_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SelectPwmPath(LX_DE_OIF_PWM_PATH_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SelectLrPath(LX_DE_OIF_LR_PATH_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_Init(LX_DE_OIF_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		ret = DE_REG_H13_OIF_SetVesaJeida(&pstParams->eVesaJeida);
		if (ret) break;
		ret = DE_REG_H13_OIF_SetPanelIf(&pstParams->eLvdsMini);
		if (ret) break;
		ret = DE_REG_H13_OIF_SetPixel(&pstParams->ePixel);
		if (ret) break;
		ret = DE_REG_H13_OIF_SetBitDepth(&pstParams->eBitMode);
		if (ret) break;
		ret = DE_REG_H13_OIF_SelectOutPath(&pstParams->eOutVideo);
		if (ret) break;
		ret = DE_REG_H13_OIF_SelectLvdsPath(&pstParams->eOutLVDS);
		if (ret) break;
		ret = DE_REG_H13_OIF_SelectOutCh(&pstParams->eOutCH);
		if (ret) break;
		ret = DE_REG_H13_OIF_SelectLedPath(&pstParams->eLedIn);
		if (ret) break;
		ret = DE_REG_H13_OIF_SelectPwmPath(&pstParams->ePWM);
		if (ret) break;
		ret = DE_REG_H13_OIF_SelectLrPath(&pstParams->eLR);
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
int DE_REG_H13_OIF_GetInfo(LX_DE_OIF_INFO_T *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SetLvdsOutput(BOOLEAN *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SetLvdsPower(BOOLEAN *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SetDarkScreen(BOOLEAN *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_OIF_SetLvdsOutCtrl(LX_DE_OIF_LVDS_OUT_CTRL_T *pstParams)
	{
		int ret = RET_OK;

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
int DE_REG_H13_OIF_SetLvdsPortSwap(BOOLEAN *pstParams)
{
	int ret = RET_OK;

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
int DE_REG_H13_SetTable(LX_DE_SET_TABLE_T *pstParams)
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
		for (i=0;i<tableLength;i++) DE_REG_H13_WD(pTable[i].wr_addr, pTable[i].wr_data);
	} while(0);

	return ret;
}

int DE_REG_H13_GPIO_Init(void)
{
#ifdef	USE_CTOP_CODES_FOR_H13
#ifdef USE_VIDEO_UART2_FOR_MCU
	CTOP_CTRL_H13_RdFL(ctr58);
	CTOP_CTRL_H13_Wr01(ctr58, uart0_sel, 2);	   // UART0 -> CPU0
	CTOP_CTRL_H13_Wr01(ctr58, uart1_sel, 1);	   // UART1 -> DE
	CTOP_CTRL_H13_Wr01(ctr58, uart2_sel, 2);	   // UART2 -> CPU2
	CTOP_CTRL_H13_Wr01(ctr58, rx_sel_hdpmcu0, 1);	   // UART1 -> DE
	CTOP_CTRL_H13_WrFL(ctr58);
	CTOP_CTRL_H13_RdFL(ctr32);
	CTOP_CTRL_H13_Wr01(ctr32, jtag1_sel, 3);	   // JTAG1 -> DE
	CTOP_CTRL_H13_WrFL(ctr32);
#else
//	CTOP_CTRL_H13_RdFL(ctr58);
//	CTOP_CTRL_H13_Wr01(ctr58, uart1_sel,	2);  // setting UART1 for CPU (Magic Remote)
//	CTOP_CTRL_H13_WrFL(ctr58);
#endif
#endif
	return 0;
}

int DE_REG_H13_HDMI_Init(void)
{
	return 0;
}

int DE_REG_H13_LVDS_Init(void)
{
	/* CLOCK - dco fcw */
	DE_DEA_H13_FLWr(dea_dco_fcw, 0x0011745D);

	return 0;
}

int DE_REG_H13_MISC_Init(void)
{
#if 0// removed 20120809, same thing is in lxboot  // dppA Sync delay
	// Video Sync Delay
	DE_DEF_H13A_RdFL(disp_sync_dly_ctrl5);
	DE_DEF_H13A_Wr01(disp_sync_dly_ctrl5, dly_sync_actv_h_dly, 0x0180);
	DE_DEF_H13A_Wr01(disp_sync_dly_ctrl5, dly_sync_actv_v_dly, 0x000D);
	DE_DEF_H13A_WrFL(disp_sync_dly_ctrl5);

	DE_DEF_H13A_RdFL(disp_sync_dly_ctrl4);
	DE_DEF_H13A_Wr01(disp_sync_dly_ctrl4, dly_sync_actv_line_start, 0x54);
	DE_DEF_H13A_Wr01(disp_sync_dly_ctrl4, dly_sync_actv_force_update, 1);
	DE_DEF_H13A_WrFL(disp_sync_dly_ctrl4);

	DE_DEF_H13A_RdFL(disp_sync_dly_ctrl4);
	DE_DEF_H13A_Wr01(disp_sync_dly_ctrl4, dly_sync_actv_force_update, 0);
	DE_DEF_H13A_WrFL(disp_sync_dly_ctrl4);

	// OSD Sync Delay
	DE_DEF_H13A_RdFL(disp_prev_dly_ctrl5);
	DE_DEF_H13A_Wr01(disp_prev_dly_ctrl5, dly_prev_h_dly, 0x0180);
	DE_DEF_H13A_Wr01(disp_prev_dly_ctrl5, dly_prev_v_dly, 0x000D);
	DE_DEF_H13A_WrFL(disp_prev_dly_ctrl5);

	DE_DEF_H13A_RdFL(disp_prev_dly_ctrl4);
	DE_DEF_H13A_Wr01(disp_prev_dly_ctrl4, dly_prev_line_start, 0x54);
	DE_DEF_H13A_Wr01(disp_prev_dly_ctrl4, dly_prev_force_update, 1);
	DE_DEF_H13A_WrFL(disp_prev_dly_ctrl4);

	DE_DEF_H13A_RdFL(disp_prev_dly_ctrl4);
	DE_DEF_H13A_Wr01(disp_prev_dly_ctrl4, dly_prev_force_update, 0);
	DE_DEF_H13A_WrFL(disp_prev_dly_ctrl4);
#endif
	return 0;
}

int DE_REG_H13_OSD_Init(void)
{

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
int DE_REG_H13_Uart0_Switch(int whichUart)
{
	int ret = RET_OK;

#ifdef	USE_CTOP_CODES_FOR_H13
#ifdef USE_DE_SWITCH_UART
	CTOP_CTRL_H13_RdFL(ctr58);
	switch (whichUart)
	{
		case 0 :
			CTOP_CTRL_H13_Wr01(ctr58, uart0_sel, 2); // UART0 = cpu0
			CTOP_CTRL_H13_Wr01(ctr58, uart1_sel, 1); // UART1 = de
			CTOP_CTRL_H13_Wr01(ctr58, rx_sel_hdpmcu0, 1); // 2:DE from UART1
			break;
		case 1 :
			CTOP_CTRL_H13_Wr01(ctr58, uart0_sel, 1); // UART0 = de
			CTOP_CTRL_H13_Wr01(ctr58, uart1_sel, 2); // UART1 = cpu0
			CTOP_CTRL_H13_Wr01(ctr58, rx_sel_hdpmcu0, 0); // 0:DE from UART0
			break;
		default :
			BREAK_WRONG(whichUart);
			break;
	}
	CTOP_CTRL_H13_WrFL(ctr58);
#endif
#endif
	return ret;
}

#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_REG_H13_FW_Download(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	char						*lpAddr = NULL;
	LX_DE_CH_MEM_T				*pFwMem = NULL;
	BOOLEAN						run_stall = 0;
#if !defined(USE_DE_FIRMWARE_RUN_IN_PAK_H13)
	BOOLEAN						tx_done = 0;
	UINT32						edma_ctrl;
#endif
	UINT32						fwBaseAddr;
	UINT32 						fwSize;
	UINT32 						*pPreWBase;

	do {
		CHECK_KNULL(pstParams);
		if (!pstParams->size) break;
		if (!pstParams->pData) break;
		DE_IPC_H13_RdFL(set_ctrl0);
		DE_IPC_H13_Rd01(set_ctrl0, run_stall, run_stall);
// do not check run_stall status for re-download
		//if (!run_stall) break;
		CTOP_CTRL_H13_RdFL(ctr25);
		CTOP_CTRL_H13_Wr01(ctr25, swrst_dee_de_dp, 1);
		CTOP_CTRL_H13_WrFL(ctr25);
		CTOP_CTRL_H13_Wr01(ctr25, swrst_dee_de_dp, 0);
		CTOP_CTRL_H13_WrFL(ctr25);
		DE_IPC_H13_Wr01(set_ctrl0, run_stall, 1);
		DE_IPC_H13_Wr01(set_ctrl0, sw_reset, 0);
		DE_IPC_H13_WrFL(set_ctrl0);

		DE_IPC_H13_FLWr(atlas_port_sel, 0x1345);

		pPreWBase = (UINT32 *)ioremap((gpDeMem->frame_base-DE_DDR_FIRMWARE_TAG_COUNT*sizeof(UINT32)), DE_DDR_FIRMWARE_TAG_COUNT*sizeof(UINT32));
		pPreWBase[0] = (gpAdrGrap->fw_base + 0x7FFC) & 0xFFFF8000; // for Row align (32KB)
		pPreWBase[1] = gpAdrPreW->fw_base;
		//*pPreWBase = 0x722a0000;
		if (pPreWBase) iounmap((void*)pPreWBase);
#ifdef USE_DE_FIRMWARE_DOWNLOAD_FROM_LBUS
		if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) )
			pFwMem = gMemCfgDeFW;         // firmware on L-BUS , temporal configuration for B0 evaluation
		else
			pFwMem = (LX_DE_CH_MEM_T *)&gpDeMem->fw[0];
#else
		pFwMem = (LX_DE_CH_MEM_T *)&gpDeMem->fw[0];
#endif
		CHECK_KNULL(pFwMem);
		fwBaseAddr = pFwMem->fw_base;
		fwSize     = pFwMem->fw_size;
		if (fwSize < pstParams->size) fwSize = pstParams->size;
		fwSize  = GET_RDUP(fwSize, 4);
#if defined(USE_VIDEO_MCU_RUN_IN_DDR0) && (USE_VIDEO_MCU_RUN_IN_DDR0 > USE_VIDEO_MCU_ROM_BASE_ADDR)
		lpAddr	= (char *)ioremap((USE_VIDEO_MCU_RUN_IN_DDR0+USE_VIDEO_MCU_ROM_FW_OFFSET), pstParams->size);
#else
		lpAddr	= (char *)ioremap((fwBaseAddr+USE_VIDEO_MCU_ROM_FW_OFFSET), pstParams->size);
#endif
		CHECK_KNULL(lpAddr);
		memcpy(lpAddr, pstParams->pData, pstParams->size);
		if (lpAddr) iounmap((void*)lpAddr);
		switch (pstParams->inx) {
#if !defined(USE_DE_FIRMWARE_RUN_IN_PAK_H13)
			case 2 :
			case 1 :
				if (1 == pstParams->inx)
				{
#ifdef USE_DE_FIRMWARE_LOAD_DRM_IRM_EACH
					DE_IPC_H13_FLWr(tx_dst_addr, 0x40000000);
#else
					break;
#endif
				} else
				{
					DE_IPC_H13_FLWr(tx_dst_addr, 0x3ffe0000);
				}
				DE_IPC_H13_FLWr(tx_src_addr, fwBaseAddr);
				DE_IPC_H13_FLWr(tx_length,	 (pstParams->size + sizeof(UINT32) -1)/sizeof(UINT32));
				DE_IPC_H13_FLWr(edma_ctrl,	 0x3);
				while (1) {
					DE_IPC_H13_FLRd(edma_ctrl, edma_ctrl);
					DE_IPC_H13_FLRf(edma_ctrl, tx_done, tx_done);
					msleep(1); // wait ddr to mcu-iram transition
					if (tx_done) break;
					msleep(1);
				}
#if   defined(USE_DE_FIRMWARE_RUN_IN_ROM_H13)
				DE_PRINT("Loading DE_FW_ROM_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				break;
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR_H13)
				DE_PRINT("Loading DE_FW_DDR_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				break;
#elif defined(USE_DE_FIRMWARE_LOAD_DRM_IRM_EACH)
				DE_PRINT("Loading DE_FW_RAM_%s\n", (1==pstParams->inx)?"IRM":"DRM");
				if (1==pstParams->inx) break;
#else
				DE_PRINT("Loading DE_FW_DIRAM\n");
#endif
#endif
#if defined(USE_DE_FIRMWARE_RUN_IN_ROM_H13) || defined(USE_DE_FIRMWARE_RUN_IN_DDR_H13) || defined(USE_DE_FIRMWARE_RUN_IN_PAK_H13)
			case 3 :
#endif
#if     defined(USE_DE_FIRMWARE_RUN_IN_PAK_H13)
				DE_PRINT("Loading DE_FW_PAK_ADR5\n");
				if (fwBaseAddr < USE_VIDEO_MCU_ROM_BASE_ADDR) BREAK_WRONG(fwBaseAddr);
				DE_IPC_H13_FLWr(srom_boot_offset, (fwBaseAddr - USE_VIDEO_MCU_ROM_BASE_ADDR));
				DE_IPC_H13_Wr01(set_ctrl0, start_vector_sel, 0);
				DE_IPC_H13_Wr01(set_ctrl0, sw_reset, 1);
#elif   defined(USE_DE_FIRMWARE_RUN_IN_ROM_H13)
				DE_PRINT("Loading DE_FW_ROM_ADR5\n");
#if defined(USE_VIDEO_MCU_RUN_IN_DDR0) && (USE_VIDEO_MCU_RUN_IN_DDR0 > USE_VIDEO_MCU_ROM_BASE_ADDR)
				DE_PRINT("FW_BASE_ADDR is %x\n", USE_VIDEO_MCU_RUN_IN_DDR0);
				DE_IPC_H13_FLWr(srom_boot_offset, (USE_VIDEO_MCU_RUN_IN_DDR0 - USE_VIDEO_MCU_ROM_BASE_ADDR));
#else
				if (fwBaseAddr < USE_VIDEO_MCU_ROM_BASE_ADDR) BREAK_WRONG(fwBaseAddr);
				DE_IPC_H13_FLWr(srom_boot_offset, (fwBaseAddr - USE_VIDEO_MCU_ROM_BASE_ADDR));
#endif
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR_H13)
				DE_IPC_H13_FLWr(atlas_port_sel, 0x1434);
				DE_PRINT("Loading DE_FW_DDR_ADR6\n");
#endif
				msleep(1); // wait ddr to ddr transition
				DE_IPC_H13_Wr01(set_ctrl0, run_stall, 0);
				DE_IPC_H13_WrFL(set_ctrl0);
			default :
				break;
		}
	} while (0);

	return ret;
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
int DE_REG_H13_SetCviFir(LX_DE_CVI_FIR_T *pstParams)
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
		for (i=0;i<ARRAY_SIZE(pstParams->fir_coef);i++) firTable[inx++] = pstParams->fir_coef[i];
		for (i=0;i<ARRAY_SIZE(pstParams->fir_coef_CbCr);i++) firTable[inx++] = pstParams->fir_coef_CbCr[i];

#ifdef USE_PARM_CODES_FOR_H13
		ret = DE_PRM_H13_LoadTable(tableId, DE_PARAM_WRITE, pstParams->isEnable, firTable, inx);
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
int DE_REG_H13_SetCviTpg(LX_DE_CVI_TPG_T *pstParams)
{
	int ret = RET_OK;
	unsigned char ptn_type;

	do {
		CHECK_KNULL(pstParams);
		//(TRUE==pstParams->isPtnOn)?(ptn_type = 0x1):(ptn_type= 0x0); // one color pattern or bypass
		ptn_type = (TRUE==pstParams->isPtnOn)?0x1:0x0; // one color pattern or bypass

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				DE_CVA_H13_RdFL(cva_misc_ctrl);
				DE_CVA_H13_Wr01(cva_misc_ctrl, pattern_type,   ptn_type);
				DE_CVA_H13_WfCM(cva_misc_ctrl, pattern_csc,    (TRUE==pstParams->isGBR),   0x1);
				DE_CVA_H13_WfCM(cva_misc_ctrl, write_inhibit,  (TRUE==pstParams->isFrzOn), 0x1);
				DE_CVA_H13_Wr01(cva_misc_ctrl, pattern_detail, pstParams->ptnColor);
				DE_CVA_H13_WrFL(cva_misc_ctrl);
				break;
			case LX_DE_CVI_CH_B :
				DE_CVB_H13_RdFL(cvb_misc_ctrl);
				DE_CVB_H13_Wr01(cvb_misc_ctrl, pattern_type,   ptn_type);
				DE_CVB_H13_WfCM(cvb_misc_ctrl, pattern_csc,    (TRUE==pstParams->isGBR),   0x1);
				DE_CVB_H13_WfCM(cvb_misc_ctrl, write_inhibit,  (TRUE==pstParams->isFrzOn), 0x1);
				DE_CVB_H13_Wr01(cvb_misc_ctrl, pattern_detail, pstParams->ptnColor);
				DE_CVB_H13_WrFL(cvb_misc_ctrl);
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
int DE_REG_H13_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
					DE_CVA_H13B_WfCM(cva_dig_filt_ctrl3, fir_c_en, (TRUE==pstParams->is3tap), 0x1);
				}
				break;
			case LX_DE_CVI_CH_B :
				if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
					DE_CVB_H13B_WfCM(cvb_dig_filt_ctrl3, fir_c_en, (TRUE==pstParams->is3tap), 0x1);
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
int DE_REG_H13_SetCviSyncReshape(LX_DE_CVI_SYNC_RESHAPE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->cvi_channel) {
			case LX_DE_CVI_CH_A :
				DE_CVA_H13_RdFL(cva_int_sync_ctrl0);
				DE_CVA_H13_RdFL(cva_int_sync_ctrl1);
				DE_CVA_H13_Wr01(cva_int_sync_ctrl0, res_hsync, pstParams->hsync_delay);
				DE_CVA_H13_Wr01(cva_int_sync_ctrl0, res_hfp,   pstParams->hfp_delay);
				DE_CVA_H13_Wr01(cva_int_sync_ctrl1, res_vfp,   pstParams->vfp_delay);
				DE_CVA_H13_Wr01(cva_int_sync_ctrl1, res_vsync, pstParams->vsync_delay);
				DE_CVA_H13_WfCM(cva_int_sync_ctrl1, res_sync_sel,(pstParams->isEnable == FALSE), 0x1);
				DE_CVA_H13_WrFL(cva_int_sync_ctrl0);
				DE_CVA_H13_WrFL(cva_int_sync_ctrl1);
				break;
			case LX_DE_CVI_CH_B :
				DE_CVB_H13_RdFL(cvb_int_sync_ctrl0);
				DE_CVB_H13_RdFL(cvb_int_sync_ctrl1);
				DE_CVB_H13_Wr01(cvb_int_sync_ctrl0, res_hsync, pstParams->hsync_delay);
				DE_CVB_H13_Wr01(cvb_int_sync_ctrl0, res_hfp,   pstParams->hfp_delay);
				DE_CVB_H13_Wr01(cvb_int_sync_ctrl1, res_vfp,   pstParams->vfp_delay);
				DE_CVB_H13_Wr01(cvb_int_sync_ctrl1, res_vsync, pstParams->vsync_delay);
				DE_CVB_H13_WfCM(cvb_int_sync_ctrl1, res_sync_sel,(pstParams->isEnable == FALSE), 0x1);
				DE_CVB_H13_WrFL(cvb_int_sync_ctrl0);
				DE_CVB_H13_WrFL(cvb_int_sync_ctrl1);
				break;
			default :
				BREAK_WRONG(pstParams->cvi_channel);
		}
		if (ret) break;
	} while (0);

	return ret;
}

void DE_REG_H13_InitPeTPG(void)
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

	if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) )  {
		DE_P1L_H13_RdFL(pe1_tpg_ctrl_00);
		DE_P1L_H13_Wr01(pe1_tpg_ctrl_00, tpg_enable, 0);
		DE_P1L_H13_WrFL(pe1_tpg_ctrl_00);

		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_addr,  0);  // Patch color
		DE_P1L_H13_WrFL(pe1_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT_B0 ; index++)
		{
			DE_P1L_H13_Wr01(pe1_tpg_ia_data, tpg_indir_data, color[index].g << 22 | color[index].b << 12 | color[index].r << 2);
			DE_P1L_H13_WrFL(pe1_tpg_ia_data);
		}

		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_addr,  0x20);  // Patch start position
		DE_P1L_H13_WrFL(pe1_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT_B0 ; index++)
		{
			DE_P1L_H13_Wr01(pe1_tpg_ia_data, tpg_indir_data, coordinate[index].x0 << 16 | coordinate[index].y0);
			DE_P1L_H13_WrFL(pe1_tpg_ia_data);
		}

		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_addr,  0x40);  // Patch end position
		DE_P1L_H13_WrFL(pe1_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT_B0 ; index++)
		{
			DE_P1L_H13_Wr01(pe1_tpg_ia_data, tpg_indir_data, coordinate[index].x1 << 16 | coordinate[index].y1);
			DE_P1L_H13_WrFL(pe1_tpg_ia_data);
		}

		DE_P1L_H13_Wr01(pe1_tpg_ctrl_00, tpg_enable, 1);

		DE_P1L_H13_WrFL(pe1_tpg_ctrl_00);
	} else {
		DE_P1L_H13_RdFL(pe1_tpg_ctrl_00);
		DE_P1L_H13_Wr01(pe1_tpg_ctrl_00, tpg_enable, 0);
		DE_P1L_H13_WrFL(pe1_tpg_ctrl_00);

		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_addr,	0);  // Patch color
		DE_P1L_H13_WrFL(pe1_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT ; index++)
		{
			DE_P1L_H13_Wr01(pe1_tpg_ia_data, tpg_indir_data, color[index].g << 22 | color[index].b << 12 | color[index].r << 2);
			DE_P1L_H13_WrFL(pe1_tpg_ia_data);
		}

		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_addr,	0x20);	// Patch start position
		DE_P1L_H13_WrFL(pe1_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT ; index++)
		{
			DE_P1L_H13_Wr01(pe1_tpg_ia_data, tpg_indir_data, coordinate[index].x0 << 16 | coordinate[index].y0);
			DE_P1L_H13_WrFL(pe1_tpg_ia_data);
		}

		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_ai_en, 1);
		DE_P1L_H13_Wr01(pe1_tpg_ia_ctrl, tpg_indir_addr,	0x40);	// Patch end position
		DE_P1L_H13_WrFL(pe1_tpg_ia_ctrl);

		for (index = 0; index < MAX_PE_TPG_RECT ; index++)
		{
			DE_P1L_H13_Wr01(pe1_tpg_ia_data, tpg_indir_data, coordinate[index].x1 << 16 | coordinate[index].y1);
			DE_P1L_H13_WrFL(pe1_tpg_ia_data);
		}

		DE_P1L_H13_Wr01(pe1_tpg_ctrl_00, tpg_enable, 1);

		DE_P1L_H13_WrFL(pe1_tpg_ctrl_00);
	}

	g_b_InitTPG_H13 = TRUE;
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
int DE_REG_H13_SetPeTestPatternGen(LX_DE_PE_TPG_T *pstParams)
{
	int ret = RET_OK;

	if (!g_b_InitTPG_H13)
		DE_REG_H13_InitPeTPG();

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->eControl)
		{
			case LX_DE_TPG_CLEAR_ALL  :		// layer 를 모두  clear 할 필요 있음
				{
						g_patchEn_H13 = 0;

					break;
				}

			case LX_DE_NONACTIVE_4_3 :		// 중국향 대응 layer 순서 바꿈( blue full screen > black pillar box )
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFFFC;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000003;

					break;
				}

			case LX_DE_WINBLANK_FULL :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFFFB;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000004;

					break;
				}

			case LX_DE_WINBLANK_FULL_BLUE :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFFF7;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000008;

					break;
				}

			case LX_DE_WINBLANK_WIN1_VCS :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFFEF;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000010;

					break;
				}

			case LX_DE_NONACTIVE_VCS :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFF1F;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x000000E0;

					break;
				}

			case LX_DE_TPG_D3D_PTN :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFEFF;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000100;

					break;
				}
			case LX_DE_TPG_D3D_2D :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFDFF;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000200;

					break;
				}
			case LX_DE_TPG_D3D_CB :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFFBFF;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000400;

				break;
				}
			case LX_DE_TPG_D3D_CC :
			case LX_DE_TPG_D3D_LL :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFF7FF;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00000800;

				break;
				}
			case LX_DE_TPG_D3D_SS :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFFCFFF;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x00003000;

				break;
				}
			case LX_DE_TPG_D3D_TB :
				{
					g_patchEn_H13 = g_patchEn_H13 & 0xFFFF3FFF;

					if (pstParams->bOnOff)
						g_patchEn_H13 |= 0x0000C000;

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
					if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) )  {
						 DE_P1L_H13_FLWf(pe1_top_ctrl_02, tpg_positon, 1);
					}
					break;
				}
/*
			case LX_DE_SETINNERPATTERN_R :
			case LX_DE_SETINNERPATTERN_G :
			case LX_DE_SETINNERPATTERN_B :
				{
					//DE_P1L_H13_RdFL(pe1_top_ctrl_02);
					DE_P1L_H13_FLWf(pe1_top_ctrl_02, tpg_positon, 0);
					//DE_P1L_H13_WrFL(pe1_top_ctrl_02);
					break;
				}
*/
			default :
				break;
		}

		if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) )  {
			 DE_P1L_H13_FLWf(pe1_tpg_ctrl_02, patch_en, g_patchEn_H13);
		}
	} while (0);

	return ret;
}
EXPORT_SYMBOL(DE_REG_H13_SetPeTestPatternGen);
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
int DE_REG_H13_SetEdgeCrop(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
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
int DE_REG_H13_SetPeBbdCtrl(LX_DE_PE_BBD_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		DE_P0L_H13_RdFL(p0l_bbd_ctrl_00);
		DE_P0L_H13_Wr01(p0l_bbd_ctrl_00, hys_mode ,pstParams->hysterisis);
		DE_P0L_H13_Wr01(p0l_bbd_ctrl_00, cnt_th   ,pstParams->cnt_th);
		DE_P0L_H13_Wr01(p0l_bbd_ctrl_00, diff_th  ,pstParams->diff_th);
		DE_P0L_H13_Wr01(p0l_bbd_ctrl_00, op_mode  ,0x0);	// assert auto boundary detection
		DE_P0L_H13_Wr01(p0l_bbd_ctrl_00, bbd_mux  ,0x1);	// New register from H13A0
#ifdef USE_PQL_REG_DEFINED_IN_DE
		DE_P0L_H13_WfCM(p0l_bbd_ctrl_00, bbd_en   ,(TRUE==pstParams->isOn) ,0x1);
#endif
		DE_P0L_H13_WrFL(p0l_bbd_ctrl_00);

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
int DE_REG_H13_GetPeBbdStatus(LX_DE_PE_COORDINATE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		DE_P0L_H13_RdFL(p0l_bbd_stat_00);
		DE_P0L_H13_RdFL(p0l_bbd_stat_01);

		DE_P0L_H13_Rd01(p0l_bbd_stat_00, x0 ,pstParams->x0);
		DE_P0L_H13_Rd01(p0l_bbd_stat_00, y0 ,pstParams->y0);
		DE_P0L_H13_Rd01(p0l_bbd_stat_01, x1 ,pstParams->x1);
		DE_P0L_H13_Rd01(p0l_bbd_stat_01, y1 ,pstParams->y1);
	} while (0);

	return ret;
}

int DE_REG_H13_ResetDE(BOOLEAN bReset)
{
	int ret = RET_OK;

#ifdef USE_DE_DOES_RESET_IN_SUSPEND_RESUME
	bReset = (bReset)?TRUE:FALSE;
#if 0//def	USE_CTOP_CODES_FOR_H13
	if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) ) {
		CTOP_CTRL_H13_FLWr(ctr05_swrs_of_de, bReset?GET_PMSK(0,32):0);
		CTOP_CTRL_H13_RdFL(ctr06_swrst);
		CTOP_CTRL_H13_WfCM(ctr06_swrst, swrst_de_vd   ,bReset, 1);
		CTOP_CTRL_H13_WfCM(ctr06_swrst, swrst_de_apb  ,bReset, 1);
		CTOP_CTRL_H13_WfCM(ctr06_swrst, swrst_cvda    ,bReset, 1);
		CTOP_CTRL_H13_WrFL(ctr06_swrst);
	}
#endif
#endif
	return ret;
}

BOOLEAN DE_REG_H13_IPCisAlive(void)
{
	BOOLEAN isFwDownloaded = FALSE;
	DE_IPC_H13_FLRf(int_intr_enable, ipc_interrupt_enable_mcu, isFwDownloaded);
#ifdef USE_IPC_CONTROL_INTERRUPT_A_BIT
	return isFwDownloaded;
#else
	return GET_BITS(isFwDownloaded, VIDEO_IPC_INTERRUPT_ARM_BIT, 1);
#endif
}

int DE_REG_H13_OIF_InitLvdsIfCtrl(void)
{
#ifndef USE_KDRV_CODES_FOR_H13
#ifndef USE_VIDEO_FOR_FPGA
	DE_OIF_H13_RdFL(lvds_if_control);
	DE_OIF_H13_Wr01(lvds_if_control, lvds_ch2_from,   2);
	DE_OIF_H13_Wr01(lvds_if_control, lvds_ch1_from,   1);
	DE_OIF_H13_WrFL(lvds_if_control);
#endif
#endif

	return RET_OK;
}

int DE_REG_H13_SetPwmFreerun(void)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_H13_SetPwmControl(LX_DE_PWM_CTRL_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_H13_SetPwmDutyCycle(LX_DE_PWM_PARAM_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_H13_GetPwmDutyCycle(LX_DE_EXTERNAL_PWM_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_H13_SetPwmFrequency(LX_DE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_H13_SetPwmPulseWidth(LX_DE_PWM_PULSE_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_H13_Set3DFullMode(LX_DE_3D_FULL_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sbDe3DFullMode = (LX_DE_3D_FULL_OFF != *pstParams)?TRUE:FALSE;
		if(sbDe3DFullMode)
		sCviSrcType.cvi_channel = LX_DE_CVI_CH_B;
		ret = DE_REG_H13_SetCviSrcType(&sCviSrcType);
		//if (ret) break;
		//g_de_CviCsc.cvi_channel = LX_DE_CVI_CH_B;
		//ret = DE_HAL_SetCviCsc(&g_de_CviCsc);
	} while (0);

	return ret;
}

int DE_REG_H13_SetUdMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sbDeUdMode = *pstParams;
		if(sbDeUdMode == 1) sCviSrcType.cvi_channel = LX_DE_CVI_CH_B;
		ret = DE_REG_H13_SetCviSrcType(&sCviSrcType);
		//if (ret) break;
		//g_de_CviCsc.cvi_channel = LX_DE_CVI_CH_B;
		//ret = DE_HAL_SetCviCsc(&g_de_CviCsc);
	} while (0);

	return ret;
}

int DE_REG_H13_SetFrameToOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = VIDEO_H13_FIRMWARE_MEM_BASE_WEB_OS;
	} while (0);

	return ret;
}

int DE_REG_H13_GetFrameForOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
/*
		if(pstParams->win_id  ==  0)
			ret = VIDEO_WEL_WaitVsync();
		else if(pstParams->win_id  ==  1)
			ret = VIDEO_WER_WaitVsync();
		else
			ret = RET_INVALID_PARAMS;
*/		
	} while (0);

	return ret;
}

int DE_REG_H13_SetLAMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		if(!*pstParams)	break;

		sCviSrcType.cvi_channel = LX_DE_CVI_CH_A;
		ret = DE_REG_H13_SetCviSrcType(&sCviSrcType);
		if (ret) break;
		sCviSrcType.cvi_channel = LX_DE_CVI_CH_B;
		ret = DE_REG_H13_SetCviSrcType(&sCviSrcType);

	} while (0);

	return ret;
}

int DE_REG_H13_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		sDeMultiWinSrc = *pstParams;
	} while (0);

	return ret;
}

/**
 * mapping input port and de cvi source
 */
int DE_REG_H13_SetMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
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


	if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
		src_cfg = sMultiSrc_map_H13[0];
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
					if(in_port == g_WinSrc_H13[LX_DE_WIN_MAIN]) return ret;

					if(in_port == LX_DE_PORT_CVD)
					{
						switch (g_WinSrc_H13[LX_DE_WIN_SUB]) {
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
						switch (g_WinSrc_H13[LX_DE_WIN_SUB]) {
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
						switch (g_WinSrc_H13[LX_DE_WIN_SUB]) {
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
						switch (g_WinSrc_H13[LX_DE_WIN_SUB]) {
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

					g_WinSrc_H13[LX_DE_WIN_MAIN] = in_port;
				}
				break;
			case LX_DE_WIN_SUB :
				{
					if(in_port == g_WinSrc_H13[LX_DE_WIN_SUB]) return ret;

					if(in_port == LX_DE_PORT_CVD)
					{
						switch (g_WinSrc_H13[LX_DE_WIN_MAIN]) {
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
						switch (g_WinSrc_H13[LX_DE_WIN_MAIN]) {
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
						switch (g_WinSrc_H13[LX_DE_WIN_MAIN]) {
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
						switch (g_WinSrc_H13[LX_DE_WIN_MAIN]) {
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

					g_WinSrc_H13[LX_DE_WIN_SUB] = in_port;
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

		DE_PRINT("win_id[%d] in_port[%d] main/sub[%d/%d] (in_port => MVI/CVD/ADC/HDMI:0/1/2/3)\n", win_id, in_port, g_WinSrc_H13[LX_DE_WIN_MAIN], g_WinSrc_H13[LX_DE_WIN_SUB]);
		DE_PRINT("cvi_mux_sel[%d] exta_sel[%d] extb_sel[%d]\n", cvi_mux_sel, exta_sel, extb_sel);

		if ( lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
#ifndef USE_VIDEO_FOR_FPGA
			DE_DEE_H13_RdFL(dee_cvi_mux_sel);
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvia_input_sel, (cvi_mux_sel & 0xF0) >> 4);
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvib_input_sel, (cvi_mux_sel & 0x0F) >> 0);
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, lvds_type_sel, 0); // 0:VESA, 1:JEIDA
			DE_DEE_H13_Wr01(dee_cvi_mux_sel, cvi_input_sel, 0); // 0:ADC output, 1:CVE output
			DE_DEE_H13_WrFL(dee_cvi_mux_sel);
#ifdef USE_CTOP_CODES_FOR_H13
			CTOP_CTRL_H13_RdFL(ctr26);
			CTOP_CTRL_H13_Wr01(ctr26, exta_sel, exta_sel);
			CTOP_CTRL_H13_Wr01(ctr26, extb_sel, extb_sel);
			CTOP_CTRL_H13_WrFL(ctr26);
#endif
#endif
		}
	} while(0);

	return ret;
}

/**
 * get cvi source information
 */
int DE_REG_H13_GetCviInfo(LX_DE_CVI_INFO_T *pstParams)
{
	int ret = RET_OK;
	UINT32 line_num = 0;
	UINT32 line_width = 0;

	do {
		CHECK_KNULL(pstParams);
		switch (pstParams->win_id) {
			case LX_DE_WIN_MAIN :
				if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) ) {
					DE_CVA_H13B_RdFL(cva_size_detect_read);
					DE_CVA_H13B_Rd01(cva_size_detect_read, line_num_read, line_num);
					DE_CVA_H13B_Rd01(cva_size_detect_read, line_width_read, line_width);
				} else {
					DE_CVA_H13_RdFL(cva_size_detect_read);
					DE_CVA_H13_Rd01(cva_size_detect_read, line_num_read, line_num);
					DE_CVA_H13_Rd01(cva_size_detect_read, line_width_read, line_width);
				}
				break;
			case LX_DE_WIN_SUB :
				if ( lx_chip_rev() >= LX_CHIP_REV(H13,B0) ) {
					DE_CVB_H13B_RdFL(cvb_size_detect_read);
					DE_CVB_H13B_Rd01(cvb_size_detect_read, line_num_read, line_num);
					DE_CVB_H13B_Rd01(cvb_size_detect_read, line_width_read, line_width);
				} else {
					DE_CVB_H13_RdFL(cvb_size_detect_read);
					DE_CVB_H13_Rd01(cvb_size_detect_read, line_num_read, line_num);
					DE_CVB_H13_Rd01(cvb_size_detect_read, line_width_read, line_width);
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
int DE_REG_H13_GetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;


	return ret;
}

/**
 * set debug data
 */
int DE_REG_H13_SetDebug(LX_DE_SET_DBG_T *pstParams)
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
							DE_CVA_H13_RdFL(cva_top_ctrl);
							DE_CVA_H13_Wr01(cva_top_ctrl, yc_delay_mode_r, 1);
							DE_CVA_H13_Wr01(cva_top_ctrl, yc_delay_mode_g, 3);
							DE_CVA_H13_Wr01(cva_top_ctrl, yc_delay_mode_b, 3);
							DE_CVA_H13_WrFL(cva_top_ctrl);
						}
						else
						{
							DE_CVA_H13_RdFL(cva_top_ctrl);
							DE_CVA_H13_Wr01(cva_top_ctrl, yc_delay_mode_r, 0);
							DE_CVA_H13_Wr01(cva_top_ctrl, yc_delay_mode_g, 0);
							DE_CVA_H13_Wr01(cva_top_ctrl, yc_delay_mode_b, 0);
							DE_CVA_H13_WrFL(cva_top_ctrl);
						}
					}
					else
					{
						if (pstParams->bParam == 1)
						{
							DE_CVB_H13_RdFL(cvb_top_ctrl);
							DE_CVB_H13_Wr01(cvb_top_ctrl, yc_delay_mode_r, 0x1);
							DE_CVB_H13_Wr01(cvb_top_ctrl, yc_delay_mode_g, 0x3);
							DE_CVB_H13_Wr01(cvb_top_ctrl, yc_delay_mode_b, 0x3);
							DE_CVB_H13_WrFL(cvb_top_ctrl);
						}
						else
						{
							DE_CVB_H13_RdFL(cvb_top_ctrl);
							DE_CVB_H13_Wr01(cvb_top_ctrl, yc_delay_mode_r, 0x0);
							DE_CVB_H13_Wr01(cvb_top_ctrl, yc_delay_mode_g, 0x0);
							DE_CVB_H13_Wr01(cvb_top_ctrl, yc_delay_mode_b, 0x0);
							DE_CVB_H13_WrFL(cvb_top_ctrl);
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
							DE_CVA_H13B_RdFL(cva_size_detect_read);
							DE_CVA_H13B_Rd01(cva_size_detect_read, line_width_read, line_width);
							syncPosition = pstParams->u32Param - pstParams->u32ParamOne;		// vTotal - vActive
							//printk("DE_REG_H13_SetDebug (vTotal(%d) vActive(%d) syncPosition(%d) line_width(%d) \n", pstParams->u32Param,pstParams->u32ParamOne, syncPosition, line_width);
							syncPosition = ( syncPosition * line_width) >> 3;
						}
						else
						{
							syncPosition = 0;
						}

						DE_DEA_H13B_RdFL(dea_msrc_sync_dly);
						DE_DEA_H13B_Wr01(dea_msrc_sync_dly, dea_msrc_sync_dly, syncPosition);
						DE_DEA_H13B_WrFL(dea_msrc_sync_dly);
						//printk("DE_REG_H13_SetDebug syncPosition = %d \n", syncPosition);
					}
					else
					{
						if (pstParams->bParam == 1)
						{
							DE_CVB_H13B_RdFL(cvb_size_detect_read);
							DE_CVB_H13B_Rd01(cvb_size_detect_read, line_width_read, line_width);
							syncPosition = pstParams->u32Param - pstParams->u32ParamOne;		// vTotal - vActive
							syncPosition = ( syncPosition * line_width) >> 3;
						}
						else
						{
							syncPosition = 0;
						}

						DE_DEC_H13B_RdFL(dec_msrc_sync_dly);
						DE_DEC_H13B_Wr01(dec_msrc_sync_dly, dec_msrc_sync_dly, syncPosition);
						DE_DEC_H13B_WrFL(dec_msrc_sync_dly);
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
int DE_REG_H13_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->config_type) {
			case LX_DE_CONFIG_TYPE_ALL :
				g_Display_type_H13 = pstParams->display_type;
				g_Display_mirror_H13 = pstParams->display_mirror;
				g_Frc_type_H13 = pstParams->frc_type;
				g_Trid_type_H13 = pstParams->trid_type;
				break;
			case LX_DE_CONFIG_TYPE_DISPLAY_DEVICE :
				g_Display_type_H13 = pstParams->display_type;
				break;
			case LX_DE_CONFIG_TYPE_DISPLAY_MIRROR:
				g_Display_mirror_H13 = pstParams->display_mirror;
				break;
			case LX_DE_CONFIG_TYPE_FRC :
				g_Frc_type_H13 = pstParams->frc_type;
				break;
			case LX_DE_CONFIG_TYPE_3D :
				g_Trid_type_H13 = pstParams->trid_type;
				break;
			case LX_DE_CONFIG_TYPE_MAX :
			default :
				BREAK_WRONG(pstParams->config_type);
		}
	} while (0);

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
int DE_REG_H13_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SYS_STATUS_ALL :
				pstParams->display_type = g_Display_type_H13;
				pstParams->display_mirror = g_Display_mirror_H13;
				pstParams->frc_type = g_Frc_type_H13;
				pstParams->trid_type = g_Trid_type_H13;
				pstParams->fc_mem = 0;
				pstParams->display_size = g_Display_size_H13;				
				break;
			case LX_DE_SYS_STATUS_DISPALY_DEVICE :
				pstParams->display_type = g_Display_type_H13;
				break;
			case LX_DE_SYS_STATUS_DISPALY_MIRROR:
				pstParams->display_mirror = g_Display_mirror_H13;
				break;				
			case LX_DE_SYS_STATUS_FRC :
				pstParams->frc_type = g_Frc_type_H13;
				break;
			case LX_DE_SYS_STATUS_3D :
				pstParams->trid_type = g_Trid_type_H13;
				break;
			case LX_DE_SYS_STATUS_FC_MEM:
				pstParams->fc_mem = 0;
				break;
			case LX_DE_SYS_STATUS_DISPALY_SIZE:
				pstParams->display_size = g_Display_size_H13;
				break;
			case LX_DE_SYS_STATUS_MAX :
			default :
				BREAK_WRONG(pstParams->status_type);
		}

	} while (0);

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
int DE_REG_H13_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SRC_STATUS_ALL :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_H13[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_H13[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB]	 = g_WinsrcMap_H13[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_H13[LX_DE_WIN_SUB];

				pstParams->operType= g_SrcOperType_H13;

				pstParams->subOperType =  g_SrcSubOperType_H13;
				break;
			case LX_DE_SRC_STATUS_INPUT_SRC :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_H13[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_H13[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB] = g_WinsrcMap_H13[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_H13[LX_DE_WIN_SUB];
				break;
			case LX_DE_SRC_STATUS_OPER :
				pstParams->operType  = g_SrcOperType_H13;
				break;

			case LX_DE_SRC_STATUS_SUB_OPER :
				pstParams->subOperType =  g_SrcSubOperType_H13;
				break;

			case LX_DE_SRC_STATUS_MAX :
			default :
				BREAK_WRONG(pstParams->status_type);
		}
	} while (0);

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
int DE_REG_H13_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_OPER_CONFIG_T	type = LX_DE_OPER_ONE_WIN;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->operation) {
			case LX_DE_OPER_ONE_WIN :
				type = LX_DE_OPER_ONE_WIN;
				break;

			case LX_DE_OPER_TWO_WIN :
				if(pstParams->multiCtrl != FALSE)		type = LX_DE_OPER_TWO_WIN;
				break;
			case LX_DE_OPER_3D :
				if(pstParams->ctrl3D.run_mode != LX_DE_3D_RUNMODE_OFF && pstParams->ctrl3D.run_mode != LX_DE_3D_RUNMODE_MAX)
				{
					type = LX_DE_OPER_3D;
				}
				break;

			case LX_DE_OPER_UD :
				if(pstParams->udCtrl != LX_DE_UD_OFF && pstParams->udCtrl != LX_DE_UD_MAX)
				{
					type = LX_DE_OPER_UD;
				}
				break;

			case LX_DE_OPER_VENC :
#if 0
				if(pstParams->vencCtrl.bOnOff != FALSE) {
					type = LX_DE_OPER_VENC;
					enable = TRUE;
				}
				break;
#endif
			case LX_DE_OPER_MAX :
			default :
				BREAK_WRONG(pstParams->operation);
		}

		g_SrcOperType_H13 = type;
	} while (0);

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
int DE_REG_H13_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->operation) {
			case LX_DE_SUB_OPER_OFF :
				g_SrcSubOperType_H13 = LX_DE_SUB_OPER_OFF;
				break;
			case LX_DE_SUB_OPER_CAPTURE:
				g_SrcSubOperType_H13 = LX_DE_SUB_OPER_CAPTURE;
				break;
			case LX_DE_SUB_OPER_VENC:
				g_SrcSubOperType_H13 = LX_DE_OPER_VENC;
				break;			

			case LX_DE_SUB_OPER_MAX :
			default :
				BREAK_WRONG(pstParams->operation);
		}
	} while (0);

	return ret;
}

#ifndef KDRV_GLOBAL_LINK
#ifdef USE_PQL_REG_DEFINED_IN_DE
EXPORT_SYMBOL(gDE_P0L_H13);
EXPORT_SYMBOL(gDE_P1L_H13);
EXPORT_SYMBOL(gDE_P0R_H13);
//EXPORT_SYMBOL(gDE_P1R_H13);
//EXPORT_SYMBOL(gDE_P0L_H13B);
//EXPORT_SYMBOL(gDE_P0R_H13B);
//EXPORT_SYMBOL(gDE_P1L_H13B);
//EXPORT_SYMBOL(gDE_P1R_H13B);
#endif
#endif
#endif
/**  @} */
