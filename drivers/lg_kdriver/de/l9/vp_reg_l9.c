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
 * author	  justine.jeong
 * version	  1.0
 * date		  2012.05.04
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

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

#include "de_model.h"
#include "de_ver_def.h"

#ifdef USE_KDRV_CODES_FOR_L9
#include "de_kapi.h"
#include "de_def.h"
#include "de_hal_def.h"
#include "de_drv.h"

#include "l9/de_cfg_l9.h"
#include "l9/de_ipc_def_l9.h"
#include "l9/de_int_def_l9.h"
#include "l9/de_reg_l9.h"
#include "l9/vp_reg_l9.h"

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
#include "l9/de_oif_reg_l9.h"		// 0x3d00
#include "l9/de_cvd_reg_l9.h"		// 0x4100

#include "l9/de_vdi_reg_l9.h"		// 0x4d00
#include "l9/de_ipc_reg_l9.h"		// 0x4e00
#include "l9/de_dvr_reg_l9.h"		// 0x5400

#include "l9/ctop_ctrl_reg_l9.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/
extern DE_DEA_REG_L9_T gDE_DEA_L9;
extern DE_DEB_REG_L9_T gDE_DEB_L9;
extern DE_DEC_REG_L9_T gDE_DEC_L9;
extern DE_DED_REG_L9_T gDE_DED_L9;
extern DE_DEE_REG_L9_T gDE_DEE_L9;
extern DE_DEF_REG_L9_T gDE_DEF_L9;

extern DE_CVA_REG_L9_T gDE_CVA_L9;
extern DE_CVB_REG_L9_T gDE_CVB_L9;

extern DE_DLR_REG_L9_T gDE_DLR_L9;

extern DE_P0L_REG_L9_T gDE_P0L_L9;
extern DE_P0R_REG_L9_T gDE_P0R_L9;
extern DE_P0L_REG_L9B_T gDE_P0L_L9B;
extern DE_P0R_REG_L9B_T gDE_P0R_L9B;

extern DE_MIA_REG_L9_T gDE_MIA_L9;
extern DE_MIB_REG_L9_T gDE_MIB_L9;
extern DE_MIC_REG_L9_T gDE_MIC_L9;
extern DE_MID_REG_L9_T gDE_MID_L9;
extern DE_MIF_REG_L9_T gDE_MIF_L9;

extern DE_MSL_REG_L9_T gDE_MSL_L9;
extern DE_MSR_REG_L9_T gDE_MSR_L9;

extern DE_OVL_REG_L9_T gDE_OVL_L9;
extern DE_OVR_REG_L9_T gDE_OVR_L9;

extern DE_P1L_REG_L9_T gDE_P1L_L9;
extern DE_P1R_REG_L9_T gDE_P1R_L9;
extern DE_P1L_REG_L9B_T gDE_P1L_L9B;
extern DE_P1R_REG_L9B_T gDE_P1R_L9B;

extern DE_SSC_REG_L9_T gDE_SSC_L9;
extern DE_T3D_REG_L9_T gDE_T3D_L9;
extern DE_OSD_REG_L9_T gDE_OSD_L9;
//DE_ATP_REG_L9_T gDE_ATP_L9;
extern DE_OIF_REG_L9_T gDE_OIF_L9;
extern DE_CVD_REG_L9_T gDE_CVD_L9;

extern DE_VDI_REG_L9_T gDE_VDC_L9;
extern DE_VDI_REG_L9_T gDE_VDD_L9;
extern DE_IPC_REG_L9_T gDE_IPC_L9;
extern DE_DVR_REG_L9_T gDE_DVR_L9;

extern CTOP_CTRL_REG_L9_T gDE_CTOP_L9;


LX_DE_IN_SRC_T	g_WinsrcMap_L9[2] = { LX_DE_IN_SRC_MVI,	LX_DE_IN_SRC_MVI};

typedef struct {
	LX_DE_MULTI_SRC_T src;
	BOOLEAN used;
	UINT32 cvi_mux_sel;
	UINT32 exta_sel;
	UINT32 extb_sel;
}
LX_DE_SRC_PATH_CONFIG;

LX_DE_SRC_PATH_CONFIG sDualSrcMap_L9[1][LX_DE_MULTI_IN_MAX + 1] =
{
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

//LX_DE_MULTI_WIN_SRC_T gsDualWinSrc = {0,0};
static BOOLEAN gbUd3DMode = FALSE;

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/

int DE_REG_L9_Set3DFullMode1(LX_DE_3D_FULL_MODE_T *pstParams)
{
	int ret = RET_OK;
	BOOLEAN sbDe3DFullMode = FALSE;
	
	do {
		CHECK_KNULL(pstParams);
		sbDe3DFullMode = (LX_DE_3D_FULL_OFF != *pstParams)?TRUE:FALSE;
		ret = DE_REG_L9_SetCviDualSrc(sbDe3DFullMode);
	} while (0);

	return ret;
}

int DE_REG_L9_SetUdMode1(BOOLEAN *pstParams)
{
	int ret = RET_OK;
	BOOLEAN sbDeUdMode = FALSE;

	do {
		CHECK_KNULL(pstParams);
		sbDeUdMode = (*pstParams)?TRUE:FALSE;
		ret = DE_REG_L9_SetCviDualSrc(sbDeUdMode);
	} while (0);

	return ret;
}

int DE_REG_L9_SetCviDualSrc(BOOLEAN flag)
{
	int ret = RET_OK;
	BOOLEAN bCviA, bCviB;

	do {
		gbUd3DMode = flag;
		if (!flag) break;
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
 * mapping input port and de source
 */
int DE_REG_L9_SetInSrc(LX_DE_INPUT_CFG_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_MULTI_SRC_T multiSrc = LX_DE_MULTI_IN_MAX;
	LX_DE_SRC_PATH_CONFIG  *src_cfg = NULL;
	LX_DE_WIN_ID_T win_id = LX_DE_WIN_MAIN;
	LX_DE_IN_SRC_T in_port = LX_DE_IN_SRC_MVI;
	UINT32 cvi_mux_sel = 0;
	UINT32 exta_sel = 0;
	UINT32 extb_sel = 0;
	UINT32 i = 0;


	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) ) {
		src_cfg = sDualSrcMap_L9[0];
	}
	
	do {
		CHECK_KNULL(src_cfg);
		CHECK_KNULL(pstParams);
		
		win_id = pstParams->win_id;
		in_port = pstParams->inputSrc;

		switch (win_id)
		{
			case LX_DE_WIN_MAIN :
				{
					if(in_port == g_WinsrcMap_L9[LX_DE_WIN_MAIN]) return ret;

					if(in_port == LX_DE_IN_SRC_CVBS ||in_port == LX_DE_IN_SRC_ATV || in_port == LX_DE_IN_SRC_SCART)
					{
						switch (g_WinsrcMap_L9[LX_DE_WIN_SUB]) {
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
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_CVD_MVI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_YPBPR || in_port == LX_DE_IN_SRC_VGA)
					{
						switch (g_WinsrcMap_L9[LX_DE_WIN_SUB]) {
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
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_ADC_MVI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_HDMI)
					{
						switch (g_WinsrcMap_L9[LX_DE_WIN_SUB]) {
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
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_HDMI_MVI;
								break;
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_MVI)
					{
						switch (g_WinsrcMap_L9[LX_DE_WIN_SUB]) {
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
							case LX_DE_IN_SRC_MVI :
								multiSrc = LX_DE_MULTI_IN_MVI_HDMI;
								break;
							default :
								break;
						}
					}

					g_WinsrcMap_L9[LX_DE_WIN_MAIN] = in_port;
				}
				break;
			case LX_DE_WIN_SUB :
				{
					if(in_port == g_WinsrcMap_L9[LX_DE_WIN_SUB]) return ret;

					if(in_port == LX_DE_IN_SRC_CVBS ||in_port == LX_DE_IN_SRC_ATV || in_port == LX_DE_IN_SRC_SCART)
					{
						if ( lx_chip_rev() == LX_CHIP_REV(L9,A1) ) {
							DE_PRINT("Not supported path on A1\n");
						}
						switch (g_WinsrcMap_L9[LX_DE_WIN_MAIN]) {
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
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_YPBPR || in_port == LX_DE_IN_SRC_VGA)
					{
						switch (g_WinsrcMap_L9[LX_DE_WIN_MAIN]) {
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
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_HDMI)
					{
						switch (g_WinsrcMap_L9[LX_DE_WIN_MAIN]) {
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
							default :
								break;
						}
					}

					if(in_port == LX_DE_IN_SRC_MVI)
					{
						switch (g_WinsrcMap_L9[LX_DE_WIN_MAIN]) {
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
							default :
								break;
						}
					}

					g_WinsrcMap_L9[LX_DE_WIN_SUB] = in_port;
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

		//CTOP_CTRL_L9_RdFL(ctr27);
		//CTOP_CTRL_L9_Wr01(ctr27, dco_sel, reg); //setting disp clock from SDEC
		//CTOP_CTRL_L9_WrFL(ctr27);

		DE_PRINT("----------win_id[%d] in_port[%d] main/sub[%d/%d] (in_port => CVD/ADC/HDMI/MVI/CPU:1/2/3/4/5)\n", win_id, in_port, g_WinsrcMap_L9[LX_DE_WIN_MAIN], g_WinsrcMap_L9[LX_DE_WIN_SUB]);
		DE_PRINT("----------cvi_mux_sel[%d] exta_sel[%d] extb_sel[%d]\n", cvi_mux_sel, exta_sel, extb_sel);

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


#endif // #ifdef USE_KDRV_CODES_FOR_L9

