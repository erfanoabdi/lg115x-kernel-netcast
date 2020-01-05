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


/** @file pe_3df.c
 *
 *  driver for 3d format auto detection. ( used only within kdriver )
 *	- functional functions regardless of modules
 *
 *	@author
 *	@version	0.1
 *	@note
 *	@date		2011.09.16
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
#include <linux/vmalloc.h>
#include <mach/platform.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "de_cfg_l9.h"
#include "de_ctr_reg_l9.h"
#include "de_mif_reg_l9.h"
#include "de_wcp_reg_l9.h"
#include "de_msc_reg_l9.h"
#include "de_ssc_reg_l9.h"

#include "pe_reg.h"
#include "pe_cfg.h"
#include "pe_def.h"
#include "pe_spd.h"
#include "pe_d3d.h"
#include "pe_cmn.h"
#include "pe_win.h"
#include "pe_dcm.h"
#include "pe_ccm.h"
#include "pe_nrd.h"

#include "../../venc/venc_cfg.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define DEFAULT_D_TPD_THR 	 182
#define DEFAULT_D_PTN_THR 	 64
#define DEFAULT_D_MTN2_THR 	 120 // 40
#define DEFAULT_D_MTN3_THR 	 3
#define DEFAULT_D_FMT_TH1 	 7
#define DEFAULT_D_FMT_TH2 	 8		  // 13 -> 5 -> 8 changed by won.hur
#define DEFAULT_D_FMT_TH3 	 100000   // 150k->100K changed by won.hur
#define DEFAULT_D_FMT_TH4 	 2000
#define DEFAULT_D_FMT_TH5 	 300000
#define DEFAULT_D_FMT_TH6 	 30000	  // 60k-> 30K changed by won.hur
#define DEFAULT_D_FMT_TH7 	 1500000
#define DEFAULT_D_FMT_TH8 	 250000
#define DEFAULT_D_FMT_TH9 	 12
#define DEFAULT_D_FMT_TH10 	 30000
#define DEFAULT_D_SKP_TH1 	 16
#define DEFAULT_D_SKP_TH2 	 30
#define DEFAULT_D_VLD_THR 	 4
#define DEFAULT_D_MBV_THR 	 1000000
#define DEFAULT_D_DFS2_THR 	 5000
#define DEFAULT_D_DFS3_THR 	 1000

#define DEFAULT_A_TPD_THR 	 170
#define DEFAULT_A_PTN_THR 	 64
#define DEFAULT_A_MTN2_THR 	 150
#define DEFAULT_A_MTN3_THR 	 4
#define DEFAULT_A_FMT_TH1 	 5
#define DEFAULT_A_FMT_TH2 	 6
#define DEFAULT_A_FMT_TH3 	 450000
#define DEFAULT_A_FMT_TH4 	 2000
#define DEFAULT_A_FMT_TH5 	 300000
#define DEFAULT_A_FMT_TH6 	 30000
#define DEFAULT_A_FMT_TH7 	 1600000
#define DEFAULT_A_FMT_TH8 	 250000
#define DEFAULT_A_FMT_TH9 	 12
#define DEFAULT_A_FMT_TH10 	 30000
#define DEFAULT_A_SKP_TH1 	 16
#define DEFAULT_A_SKP_TH2 	 30
#define DEFAULT_A_VLD_THR 	 4
#define DEFAULT_A_LRD_THR 	 1600
#define DEFAULT_A_MBV_THR 	 1000000
#define DEFAULT_A_DFS2_THR 	 5000
#define DEFAULT_A_DFS3_THR 	 1000

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
//#define PE_D3D_USE_DISPARITY
#define PE_D3D_STRICT_DECIDE
#define PE_D3D_AUTO_START
#define PE_D3D_WIN_RATIO	2
//#define PE_D3D_USE_VLINE

#define PE_D3D_ERROR	printk
#define PE_PRINT		printk
#define PE_MSG			if(_g_d3d_trace>=LX_PE_D3D_DEC_LOG)PE_PRINT
//#define PE_MSG			printk

#define PE_D3D_DBG_PRINT(fmt,args...)	if(_g_d3d_trace>=LX_PE_D3D_DEC_LOG) printk("[%x][%s,%d] "fmt,PE_CHIP_VER,__F__,__L__,##args)
#define PE_D3D_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_D3D_ERROR(fmt,##args);_action;}}

#define memset0(_var)	memset( &(_var), 0x00, sizeof(_var))

#define MAX2(a,b) (a>=b)? a:b
#define MIN2(a,b) (a<=b)? a:b
#define MIN3(a,b,c) (a<=b)? ((a<=c)?a:c): ((b<=c)?b:c)
#define DIFF(a,b) (a>=b)?abs(a-b):abs(b-a)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void DE_VSYNC_Register(int (*func)(void));
extern int DE_REG_L9_SetPeTestPatternGen(LX_DE_PE_TPG_T *pstParams);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern DE_DEB_REG_L9_T gDE_DEB_L9;
extern DE_DEC_REG_L9_T gDE_DEC_L9;
extern DE_P0L_REG_L9B_T gDE_P0L_L9B;
extern DE_P0R_REG_L9B_T gDE_P0R_L9B;
extern DE_P1L_REG_L9B_T gDE_P1L_L9B;
extern DE_P1R_REG_L9B_T gDE_P1R_L9B;
extern DE_MIB_REG_L9_T gDE_MIB_L9;
extern DE_MIF_REG_L9_T gDE_MIF_L9;
extern DE_OVL_REG_L9_T gDE_OVL_L9;
extern DE_MSL_REG_L9_T gDE_MSL_L9;
extern DE_SSC_REG_L9_T gDE_SSC_L9;

extern LX_VENC_MEM_CFG_S_T	*gpstVencMemConfig;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
PE_D3D_INFO_T       d3d_info;
LX_PE_D3D_THR_T     default_thr = {0, DEFAULT_D_TPD_THR, DEFAULT_D_PTN_THR, DEFAULT_D_MTN2_THR, DEFAULT_D_MTN3_THR, DEFAULT_D_FMT_TH1, DEFAULT_D_FMT_TH2, DEFAULT_D_FMT_TH3, DEFAULT_D_FMT_TH4,
									DEFAULT_D_FMT_TH5, DEFAULT_D_FMT_TH6, DEFAULT_D_FMT_TH7, DEFAULT_D_FMT_TH8, DEFAULT_D_FMT_TH9, DEFAULT_D_FMT_TH10, DEFAULT_D_SKP_TH1, DEFAULT_D_SKP_TH2, DEFAULT_D_VLD_THR, DEFAULT_D_MBV_THR,
									DEFAULT_D_DFS2_THR, DEFAULT_D_DFS3_THR};
LX_PE_D3D_THR_T     default_thr_d = {0, DEFAULT_D_TPD_THR, DEFAULT_D_PTN_THR, DEFAULT_D_MTN2_THR, DEFAULT_D_MTN3_THR, DEFAULT_D_FMT_TH1, DEFAULT_D_FMT_TH2, DEFAULT_D_FMT_TH3, DEFAULT_D_FMT_TH4,
									DEFAULT_D_FMT_TH5, DEFAULT_D_FMT_TH6, DEFAULT_D_FMT_TH7, DEFAULT_D_FMT_TH8, DEFAULT_D_FMT_TH9, DEFAULT_D_FMT_TH10, DEFAULT_D_SKP_TH1, DEFAULT_D_SKP_TH2, DEFAULT_D_VLD_THR, DEFAULT_D_MBV_THR,
									DEFAULT_D_DFS2_THR, DEFAULT_D_DFS3_THR};
LX_PE_D3D_THR_T     default_thr_a = {0, DEFAULT_A_TPD_THR, DEFAULT_A_PTN_THR, DEFAULT_A_MTN2_THR, DEFAULT_A_MTN3_THR, DEFAULT_A_FMT_TH1, DEFAULT_A_FMT_TH2, DEFAULT_A_FMT_TH3, DEFAULT_A_FMT_TH4,
									DEFAULT_A_FMT_TH5, DEFAULT_A_FMT_TH6, DEFAULT_A_FMT_TH7, DEFAULT_A_FMT_TH8, DEFAULT_A_FMT_TH9, DEFAULT_D_FMT_TH10, DEFAULT_A_SKP_TH1, DEFAULT_A_SKP_TH2, DEFAULT_A_VLD_THR, DEFAULT_A_MBV_THR,
									DEFAULT_A_DFS2_THR, DEFAULT_A_DFS3_THR};
LX_PE_D3D_FORMAT_T  initial_fmt;

PE_D3D_DISPARITY_T  depth_info;

volatile UINT8 *gpMBase_dpp;
volatile UINT8 *gpMBase_sav = NULL;

#ifdef PE_D3D_KANGSIK_YOON_TEST
UINT8	gInputSourceChangedFlag = 1;
#endif

PE_D3D_CAP_INFO_T cap_info;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_D3D_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_D3D_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_D3D_InitHardware(void);
static int PE_D3D_GetD3DInfo(LX_PE_D3D_INFO_T *pstParams);
static int PE_D3D_GetDSCInfo(LX_PE_D3D_DSC_INFO_T *pstParams);
static int PE_D3D_SetThreshold(LX_PE_D3D_THR_T *pstParams);
static int PE_D3D_GetMax3(UINT32 *g_diff, UINT32 *b_diff, UINT32 *r_diff, UINT32 *diff_max);
static int PE_D3D_GetMaxFromBuffer(UINT32 *pBuf, UINT32 count, UINT32 *pElect);
static int PE_D3D_GetMin3(UINT32 value0, UINT32 value1, UINT32 value2);
static int PE_D3D_GetDTWDistance(UINT32* s, UINT32* t, UINT32 N, UINT32 M, UINT32 wsize, UINT32 *diff);
#ifndef PE_D3D_STRICT_DECIDE
static int PE_D3D_GetHistDistance(UINT32* hist_l, UINT32* hist_r, UINT32 N, UINT32* dist_l, UINT32* dist_r);
static int PE_D3D_GetCount2Over3(UINT32 diff_g, UINT32 diff_b, UINT32 diff_r, UINT32 thr, UINT32* cnt);
#endif
static int PE_D3D_GetDiff(UINT32 bin, UINT32 *rd_L, UINT32 *rd_R, UINT32 *diff);
static int PE_D3D_EnableReadHIS(BOOLEAN flag);
static int PE_D3D_RequestHIS(PE_D3D_WIN_ID_T win, PE_D3D_HISTOGRAM_TYPE_T histo_type);
static int PE_D3D_ReleaseHIS(void);
static int PE_D3D_GetHIS(PE_D3D_WIN_ID_T win, PE_D3D_HISTOGRAM_TYPE_T histo_type, UINT32 *pBuf, UINT32 size);
static int PE_D3D_SetD3D(LX_PE_D3D_SETTINGS_T *pstParams);
static int PE_D3D_CollectBasicData(void);
static int PE_D3D_GetLrcrHistogram(void);
static int PE_D3D_GetDceHistogram(void);
static int PE_D3D_GetDCEDelta(UINT32 cur_dce_diff, UINT32 *delta);
#ifdef PE_D3D_USE_LINE_DIFF_BY_SW
static int PE_D3D_GetOVInfo(PE_D3D_CAP_SRC_T ov_src, PE_D3D_OV_INFO_T *ov_info);
static int PE_D3D_GetStripFromFrame(PE_D3D_OV_INFO_T *ov_info, PE_D3D_CAP_INFO_T *capture_info, UINT32 h_line_num, UINT32 h_line_width, UINT32 v_line_num, UINT32 v_line_width);
static int PE_D3D_MeasureLineDifference(PE_D3D_CAP_INFO_T *capture_info);
static int PE_D3D_InitFrameMemory(UINT32 h_max_line, UINT32 v_max_line);
//static int PE_D3D_UnInitFrameMemory(void);
static int PE_D3D_AccumulateFormat(LX_PE_D3D_FORMAT_T *cur_fmt);
#endif
static int PE_D3D_CheckStableFormat(BOOLEAN *pValid, LX_PE_D3D_FORMAT_T *cur_fmt);
#ifdef PE_D3D_USE_DISPARITY
static int PE_D3D_CheckDepthInfo(BOOLEAN *pValid);
#endif
static int PE_D3D_DumpHistogram(void);
static int PE_D3D_DumpAllData(void);
static int PE_D3D_DecideFormat(void);
static int PE_D3D_DisplayResult(void);
static int PE_D3D_DetectFormat(void);
#ifdef PE_D3D_KANGSIK_YOON_TEST
//static int PE_D3D_DetectSourceChange(void);
#endif

#include "pe_d3d_alg.c"

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static LX_PE_D3D_DEC_T _g_d3d_trace = LX_PE_D3D_DEC_OFF;	//default should be off.

#ifdef PE_D3D_KANGSIK_YOON_TEST
static	UINT16  thr_adj = 0;
static  UINT32  tmp_thr3 = 0, tmp_thr4 = 0, tmp_thr6 = 0, tmp_thr7 = 0;
static  UINT32  tmp_thr_const0 = 0, tmp_thr_const1 = 0, tmp_thr_const2 = 0, tmp_thr_const3 = 0;
#endif
/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * start all win simultaneous reg. setting mode
 *	- should call end mode after start mode, for used blocks.
 *
 * @param   mode_block [in] UINT32, see PE_SIMUL_MODE_PE0,SM,PE1
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */

/**
 * init d3d
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
 int PE_D3D_Init(void)
{
	int ret = RET_OK;
#ifdef PE_D3D_AUTO_START
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
#endif
	do {
		DE_VSYNC_Register(PE_D3D_DetectFormat);

#ifdef PE_D3D_USE_LINE_DIFF_BY_SW
		ret = PE_D3D_InitFrameMemory(/*h_max_line*/PE_D3D_MAX_LINE, /*v_max_line*/0);
		if (ret) break;
#endif
#ifdef PE_D3D_AUTO_START
		pCfg->enable         = LX_PE_D3D_DEC_ON;
		pCfg->sel_alg    = 1;
		pCfg->rb_bin_d3d = D3D_MAX_BIN; // ?
		pCfg->cap_enb        = LX_PE_D3D_CAP_OFF;
		pCfg->cap_h_line_num   = PE_D3D_MAX_LINE;
		pCfg->cap_v_line_num   = 0;
		pCfg->cap_h_line_width = 1;
		pCfg->cap_v_line_width = 0;
		ret = PE_D3D_SetThreshold(&default_thr_d);
#endif

		ret = PE_D3D_InitHardware();
		if (ret) break;

		PE_PRINT("%s : done\n", __F__);
	}while(0);

	return ret;
}

/**
 * standard function of d3d setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_D3D_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

	/* data null check */
	PE_D3D_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);

	switch(functype)
	{
		case PE_ITEM_PKTFUNC(LX_PE_D3D_SETTINGS_T):
		{
			LX_PE_D3D_SETTINGS_T *pRcvData;
			LX_PE_D3D_SETTINGS_T stParam;

			do{
				PE_D3D_DBG_PRINT("S LX_PE_D3D_CTRL_T\n");
				/* data size check */
				PE_D3D_CHECK_CODE(datasize!=sizeof(LX_PE_D3D_SETTINGS_T),break,"[%s,%d] size mismatch.\n",__F__,__L__);

				pRcvData = (LX_PE_D3D_SETTINGS_T *)data;
				memcpy(&stParam,pRcvData,datasize);
				_g_d3d_trace = stParam.enb;
				initial_fmt = stParam.fmt;
				ret = PE_D3D_SetD3D(&stParam);

				PE_D3D_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_SetFunction() error.\n",__F__,__L__);
				PE_D3D_DBG_PRINT("E LX_PE_D3D_CTRL_T\n");
			}while(0);
		}
		break;
		case PE_ITEM_PKTFUNC(LX_PE_D3D_THR_T):
		{
			LX_PE_D3D_THR_T *pRcvData;
			LX_PE_D3D_THR_T stParam;
			do{
				PE_D3D_DBG_PRINT("S LX_PE_D3D_THR_T\n");
				/* data size check */
				PE_D3D_CHECK_CODE(datasize!=sizeof(LX_PE_D3D_THR_T),break,"[%s,%d] size mismatch.\n",__F__,__L__);

				pRcvData = (LX_PE_D3D_THR_T *)data;
				memcpy(&stParam,pRcvData,datasize);
				ret = PE_D3D_SetThreshold(&stParam);
				PE_D3D_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_SetThreshold() error.\n",__F__,__L__);
				PE_D3D_DBG_PRINT("E LX_PE_D3D_THR_T\n");
			}while(0);
		}
		break;
		case PE_ITEM_PKTFUNC(LX_PE_DBG_SETTINGS_T):
		{
			LX_PE_DBG_SETTINGS_T *pRcvData;
			LX_PE_DBG_SETTINGS_T stParam;
			do{
				PE_D3D_DBG_PRINT("S LX_PE_DBG_SETTINGS_T\n");
				/* data size check */
				PE_D3D_CHECK_CODE(datasize!=sizeof(LX_PE_DBG_SETTINGS_T),break,"[%s,%d] size mismatch.\n",__F__,__L__);

				pRcvData = (LX_PE_DBG_SETTINGS_T *)data;
				memcpy(&stParam,pRcvData,datasize);
				ret = PE_D3D_SetDebugSettings(&stParam);
				PE_D3D_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_SetDebugSettings() error.\n",__F__,__L__);
				PE_D3D_DBG_PRINT("E LX_PE_DBG_SETTINGS_T\n");
			}while(0);
		}
		break;
		case PE_ITEM_PKTFUNC(LX_PE_DEFAULT_SETTINGS_T):
		{
			LX_PE_DEFAULT_SETTINGS_T *pRcvData;
			LX_PE_DEFAULT_SETTINGS_T stParam;
			do{
				PE_D3D_DBG_PRINT("S LX_PE_DEFAULT_SETTINGS_T\n");
				/* data size check */
				PE_D3D_CHECK_CODE(datasize!=sizeof(LX_PE_DEFAULT_SETTINGS_T),break,"[%s,%d] size mismatch.\n",__F__,__L__);

				pRcvData = (LX_PE_DEFAULT_SETTINGS_T *)data;
				//memcpy(&stParam,pRcvData,datasize);
				ret = PE_COPY_FROM_USER(PE_SUSPEND_D3D_SETDEFAULT, (void *)&stParam, (void *)pRcvData, datasize);
				PE_D3D_CHECK_CODE(ret,break,"[%s,%d] PE_SUSPEND_D3D_SETDEFAULT error.\n",__F__,__L__);

				ret = PE_D3D_SetDefaultSettings(&stParam);
				PE_D3D_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_SetDefaultSettings() error.\n",__F__,__L__);
				PE_D3D_DBG_PRINT("E LX_PE_DEFAULT_SETTINGS_T\n");
			}while(0);
		}
		break;
		default:
		{
			PE_D3D_ERROR("[%s,%d] functype default case.\n",__F__,__L__);
			ret = RET_ERROR;
		}
		break;
	}

	return ret;
}

/**
 * standard function of d3d getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_D3D_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

	/* data null check */
	PE_D3D_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);

	switch(functype)
	{
		case PE_ITEM_PKTFUNC(LX_PE_D3D_INFO_T):
		{
			LX_PE_D3D_INFO_T *pRcvData;
			LX_PE_D3D_INFO_T stParam;
			memset0(stParam);
			do{
				//PE_D3D_DBG_PRINT("S LX_PE_D3D_INFO_T\n");
				/* data size check */
				PE_D3D_CHECK_CODE(datasize!=sizeof(LX_PE_D3D_INFO_T),break,"[%s,%d] size mismatch.\n",__F__,__L__);

				pRcvData = (LX_PE_D3D_INFO_T *)data;
				stParam.d3d_inf = pRcvData->d3d_inf;
				ret = PE_D3D_GetD3DInfo(&stParam);
				if(_g_d3d_trace==LX_PE_D3D_DEC_FIX_3D)
				{
					stParam.d3d_inf = initial_fmt;
				}
				else if(_g_d3d_trace==LX_PE_D3D_DEC_FIX_2D)
				{
					stParam.d3d_inf = LX_PE_D3D_FMT_2D_2D;
				}
				PE_D3D_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_GetFunction() error.\n",__F__,__L__);
				memcpy(pRcvData,&stParam,datasize);
				//PE_D3D_DBG_PRINT("E LX_PE_D3D_INFO_T\n");
			}while(0);
		}
		break;
		case PE_ITEM_PKTFUNC(LX_PE_D3D_DSC_INFO_T):
		{
			LX_PE_D3D_DSC_INFO_T *pRcvData;
			LX_PE_D3D_DSC_INFO_T stParam;
			memset0(stParam);
			do{
				//PE_D3D_DBG_PRINT("S LX_PE_D3D_DSC_INFO_T\n");
				/* data size check */
				PE_D3D_CHECK_CODE(datasize!=sizeof(LX_PE_D3D_DSC_INFO_T),break,"[%s,%d] size mismatch.\n",__F__,__L__);

				pRcvData = (LX_PE_D3D_DSC_INFO_T *)data;
				ret = PE_D3D_GetDSCInfo(&stParam);
				PE_D3D_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_GetFunction() error.\n",__F__,__L__);
				memcpy(pRcvData,&stParam,datasize);
				//PE_D3D_DBG_PRINT("E LX_PE_D3D_DSC_INFO_T\n");
			}while(0);
		}
		break;
		default:
		{
			PE_D3D_ERROR("[%s,%d] functype default case.\n",__F__,__L__);
			ret = RET_ERROR;
		}
		break;
	}

	return ret;
}

static int PE_D3D_InitHardware(void)
{
	int ret = RET_OK;

	do {
		DE_P0L_L9B0_RdFL(tridfd_ctrl_00);
		DE_P0L_L9B0_RdFL(tridfd_ctrl_01);
		DE_P0L_L9B0_RdFL(tridfd_ctrl_02);
		DE_P0L_L9B0_RdFL(tridfd_ctrl_03);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_00, aw_offset_x, 0);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_00, aw_offset_y, 0);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_00, cb_th1, 0x3C);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_00, cb_th2, 0x14);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_01, cc_th1, 0x3C);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_01, cc_th2, 0x14);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_01, ll_th1, 0x3C);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_01, ll_th2, 0x14);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_02, pt_th, 0x80);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_02, sstb_th, 0x07);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_02, div_mode, 0);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_03, small_delta_en, 0);
		DE_P0L_L9B0_Wr01(tridfd_ctrl_03, small_delta_th, 0xFF);
		DE_P0L_L9B0_WrFL(tridfd_ctrl_00);
		DE_P0L_L9B0_WrFL(tridfd_ctrl_01);
		DE_P0L_L9B0_WrFL(tridfd_ctrl_02);
		DE_P0L_L9B0_WrFL(tridfd_ctrl_03);

		DE_DEB_L9B_RdFL(deb_intr_mask);
		DE_DEB_L9B_Wr01(deb_intr_mask, mask_disp_for_cpu, 0);  // unmasking interrupt from de
		DE_DEB_L9B_WrFL(deb_intr_mask);
	} while(0);

	return ret;
}

static int PE_D3D_GetD3DInfo(LX_PE_D3D_INFO_T *pstParams)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	LX_PE_D3D_THR_T *pThr = &d3d_info.thr;

	do{
		CHECK_KNULL(pstParams);
		pstParams->valid   = pCfg->valid;
		pstParams->d3d_inf = pCfg->d3d_fmt;
		memcpy(&pstParams->thr, pThr, sizeof(LX_PE_D3D_THR_T));

		PE_MSG("pCfg->acc_fmt [%d]\n", pCfg->acc_fmt);
		pCfg->cnt_start = FALSE;
	}while(0);

	return ret;
}

static int PE_D3D_GetDSCInfo(LX_PE_D3D_DSC_INFO_T *pstParams)
{
	int ret = RET_OK;
	PE_D3D_DTA_T *pData = &d3d_info.dta;

	do{
		CHECK_KNULL(pstParams);
		switch(pData->hw_fmt)
		{
			case 0 :
				pstParams->dsc_type = LX_PE_D3D_DSC_2D;
				break;
			case 8 :
				pstParams->dsc_type = LX_PE_D3D_DSC_SS;
				break;
			case 9 :
				pstParams->dsc_type = LX_PE_D3D_DSC_TB;
				break;
			default :
				pstParams->dsc_type = LX_PE_D3D_DSC_2D;
				break;
		}
	}while(0);

	return ret;
}

static int PE_D3D_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_D3D_DBG_PRINT("win id : %d, type : 0x%x, [0x%08x] print level : 0x%08x, bypass : 0x%08x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(D3D)),pstParams->print_lvl,pstParams->bypass);
	#if 0
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LEVEL)
			_g_d3d_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(D3D)))? 0x1:0x0;
	#endif

	}while(0);
	return ret;
}

static int PE_D3D_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
//	LX_PE_D3D_THR_T stParams;

	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_D3D_DBG_PRINT("[win id:%d] src:%d, fmt:%d, out:%d, fr:%d, scan:%d, dtv:%d\n",\
			pstParams->win_id,pstParams->src_type,pstParams->fmt_type,pstParams->out_type,\
			pstParams->fr_type,pstParams->scan_type,pstParams->dtv_type);

		switch(pstParams->src_type)
		{
			case LX_PE_SRC_ATV :
			case LX_PE_SRC_CVBS :
			case LX_PE_SRC_COMP :
			case LX_PE_SRC_RGBPC :
				memcpy(&default_thr, &default_thr_a, sizeof(LX_PE_D3D_THR_T));
				break;
			case LX_PE_SRC_DTV :
			case LX_PE_SRC_HDMI :
			default :
				memcpy(&default_thr, &default_thr_d, sizeof(LX_PE_D3D_THR_T));
				break;
		}
		ret = PE_D3D_SetThreshold(&default_thr);
	}while(0);
	return ret;
}

static int PE_D3D_SetThreshold(LX_PE_D3D_THR_T *pstParams)
{
    int ret = RET_OK;
	LX_PE_D3D_THR_T *pThr = &d3d_info.thr;

	do {
		CHECK_KNULL(pstParams);
		if(pstParams->isDefault == TRUE)
			memcpy(pThr, &default_thr, sizeof(LX_PE_D3D_THR_T));
		else
			memcpy(pThr, pstParams, sizeof(LX_PE_D3D_THR_T));
		if(_g_d3d_trace >= LX_PE_D3D_DEC_LOG)
		{
			PE_PRINT("isDefault [%d]\n", pstParams->isDefault);
			PE_PRINT("tpd_thr [%d]\n", pThr->tpd_thr);
			PE_PRINT("ptn_thr [%d]\n", pThr->ptn_thr);
			PE_PRINT("mtn_thr_2d [%d]\n", pThr->mtn_thr_2d);
			PE_PRINT("mtn_thr_3d [%d]\n", pThr->mtn_thr_3d);
			PE_PRINT("fmt_th1 [%d]\n", pThr->fmt_th1);
			PE_PRINT("fmt_th2 [%d]\n", pThr->fmt_th2);
			PE_PRINT("fmt_th3 [%d]\n", pThr->fmt_th3);
			PE_PRINT("fmt_th4 [%d]\n", pThr->fmt_th4);
			PE_PRINT("fmt_th5 [%d]\n", pThr->fmt_th5);
			PE_PRINT("fmt_th6 [%d]\n", pThr->fmt_th6);
			PE_PRINT("fmt_th7 [%d]\n", pThr->fmt_th7);
			PE_PRINT("fmt_th8 [%d]\n", pThr->fmt_th8);
			PE_PRINT("fmt_th9 [%d]\n", pThr->fmt_th9);
			PE_PRINT("skp_th1 [%d]\n", pThr->skp_th1);
			PE_PRINT("skp_th2 [%d]\n", pThr->skp_th2);
			PE_PRINT("vld_thr [%d]\n", pThr->vld_thr);
			PE_PRINT("mbv_thr [%d]\n", pThr->mbv_thr);
			PE_PRINT("dfs_thr_2d [%d]\n", pThr->dfs_thr_2d);
			PE_PRINT("dfs_thr_3d [%d]\n", pThr->dfs_thr_3d);
		}
	} while(0);
	return ret;
}

static int PE_D3D_GetMax3(UINT32 *g_diff, UINT32 *b_diff, UINT32 *r_diff, UINT32 *diff_max)
{
    int ret = RET_OK;

	do {
	    if(*g_diff>=*b_diff)
	    {
	    	if(*g_diff>=*r_diff)
	        	*diff_max = *g_diff;
	        else
				*diff_max = *r_diff;
	    }
	    else
	    {
	    	if(*b_diff>=*r_diff)
	        	*diff_max = *b_diff;
	        else
				*diff_max = *r_diff;
	    }
	} while(0);

    return ret;
}

static int PE_D3D_GetMaxFromBuffer(UINT32 *pBuf, UINT32 count, UINT32 *pElect)
{
    int ret = RET_OK;
	UINT32 i=0, j=0;
	UINT32 temp=0;

	do {
		for(i=0;i<count;i++)
		{
			for(j=0;j<count;j++)
			{
				if(pBuf[j] >= temp)
				{
					temp = pBuf[j];
				}
			}
		}
		*pElect = temp;
	} while(0);
	return ret;
}

static int PE_D3D_GetMin3(UINT32 value0, UINT32 value1, UINT32 value2)
{
	int diff_min;
    if(value0<=value1)
    {
    	if(value0<=value2)
        	diff_min = value0;
        else
        	diff_min = value2;
    }
    else
    {
    	if(value1<=value2)
        	diff_min = value1;
        else
			diff_min = value2;
    }
    return diff_min;
}

static UINT32 DTW[32][32];

static int PE_D3D_GetDTWDistance(UINT32* s, UINT32* t, UINT32 N, UINT32 M, UINT32 wsize, UINT32 *diff)
{
    int ret = RET_OK;
#if 1
	int i,j,cost;
	int JS, JE;
/*
	DTW = (int **)malloc((M+1)*sizeof(int *));
	for(j=0;j<(M+1);j++)
		DTW[j] = (int *)malloc((N+1)*sizeof(int));
*/
	for(j=1;j<=M;j++)
		DTW[j][0] = 100000000; //4,294,967,200; //
	for(i=1;i<=N;i++)
		DTW[0][i] = 100000000; //4,294,967,200; //
	DTW[0][0] = 0;

	for(i=1;i<=N;i++)
	{
		JS = MAX2(1, i-wsize);
		JE = MIN2(M, i+wsize);
		for(j=JS;j<=JE;j++)
		{
			cost = abs(s[i-1]-t[j-1]);
			#if 0
			DTW[j][i] = cost + MIN3(DTW[j  ][i-1], DTW[j-1][i  ], DTW[j-1][i-1]);
			#else
			DTW[j][i] = cost + PE_D3D_GetMin3(DTW[j  ][i-1],	// Insertion
									DTW[j-1][i  ],	// Deletion
									DTW[j-1][i-1]);	// Matching
			#endif
		}
	}
	*diff = DTW[M][N];
/*
	for(j=0;j<(M+1);j++)
		free(DTW[j]);
	free(DTW);
*/
#endif
    return ret;
}
#ifndef PE_D3D_STRICT_DECIDE
static int PE_D3D_GetHistDistance(UINT32* hist_l, UINT32* hist_r, UINT32 N, UINT32* dist_l, UINT32* dist_r)
{
	int ret = RET_OK;
	UINT32 i;
	UINT32 difference;

	do {
		*dist_l = *dist_r = 0;

		for(i=0;i<N-1; i++)
		{
			difference = DIFF(hist_l[i], hist_l[i+1]);
			difference = difference / 10000;
			*dist_l += (difference * difference);
			difference = DIFF(hist_r[i], hist_r[i+1]);
			difference = difference / 10000;
			*dist_r += (difference * difference);
		}
	} while(0);
	return ret;
}
#endif
static int PE_D3D_GetDiff(UINT32 bin, UINT32 *rd_L, UINT32 *rd_R, UINT32 *diff)
{
	int ret = RET_OK;
	UINT32 LR_Diff, Diff;
	UINT32 i;

	do {
		LR_Diff = 0;
		for ( i = 0; i < bin; i++ )
		{
			if(rd_L[i] > rd_R[i])
				Diff = rd_L[i] - rd_R[i];
			else
				Diff = rd_R[i] - rd_L[i];
	        //LR_Diff += abs(Diff);
			LR_Diff += Diff;
	    }
		*diff = LR_Diff;
	} while(0);

    return ret;
}
#ifndef PE_D3D_STRICT_DECIDE
static int PE_D3D_GetCount2Over3(UINT32 diff_g, UINT32 diff_b, UINT32 diff_r, UINT32 thr, UINT32* cnt)
{
	int ret = RET_OK;

	do {
		if(diff_g < thr)	*cnt += 1;
		if(diff_b < thr)	*cnt += 1;
		if(diff_r < thr)	*cnt += 1;
	} while(0);

	return ret;
}
#endif
static int PE_D3D_EnableReadHIS(BOOLEAN flag)
{
	int ret = RET_OK;

	do {
		if(flag == FALSE)
		{
			DE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
			DE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00, hist_rd_en, 0);
			DE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
		}
		else
		{
			DE_P1L_L9B0_RdFL(pe1_l_lrcr_ctrl_00);
			DE_P1L_L9B0_Wr01(pe1_l_lrcr_ctrl_00, hist_rd_en, 1);
			DE_P1L_L9B0_WrFL(pe1_l_lrcr_ctrl_00);
		}
	} while(0);

	return ret;
}

static int PE_D3D_RequestHIS(PE_D3D_WIN_ID_T win, PE_D3D_HISTOGRAM_TYPE_T histo_type)
{
	int ret = RET_OK;

	do {
		switch ( histo_type )
		{
			case D3D_HIS_GRE :
				if( win == D3D_WIN_LFT || win == D3D_WIN_TOP ) {
					DE_P1L_L9B0_RdFL(pe1_l_g_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_l_g_hist_ia_ctrl, hif_hist_enable, 0);
					DE_P1L_L9B0_Wr01(pe1_l_g_hist_ia_ctrl, hif_hist_ai, 1);
					DE_P1L_L9B0_WrFL(pe1_l_g_hist_ia_ctrl);
				} else {
					DE_P1L_L9B0_RdFL(pe1_r_g_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_r_g_hist_ia_ctrl, hif_hist_enable, 0);
					DE_P1L_L9B0_Wr01(pe1_r_g_hist_ia_ctrl, hif_hist_ai, 1);
					DE_P1L_L9B0_WrFL(pe1_r_g_hist_ia_ctrl);
				}
				break;
			case D3D_HIS_BLU :
				if( win == D3D_WIN_LFT || win == D3D_WIN_TOP ) {
					DE_P1L_L9B0_RdFL(pe1_l_b_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_l_b_hist_ia_ctrl, hif_hist_enable, 0);
					DE_P1L_L9B0_Wr01(pe1_l_b_hist_ia_ctrl, hif_hist_ai, 1);
					DE_P1L_L9B0_WrFL(pe1_l_b_hist_ia_ctrl);
				} else {
					DE_P1L_L9B0_RdFL(pe1_r_b_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_r_b_hist_ia_ctrl, hif_hist_enable, 0);
					DE_P1L_L9B0_Wr01(pe1_r_b_hist_ia_ctrl, hif_hist_ai, 1);
					DE_P1L_L9B0_WrFL(pe1_r_b_hist_ia_ctrl);
				}
				break;
			case D3D_HIS_RED :
				if( win == D3D_WIN_LFT || win == D3D_WIN_TOP ) {
					DE_P1L_L9B0_RdFL(pe1_l_r_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_l_r_hist_ia_ctrl, hif_hist_enable, 0);
					DE_P1L_L9B0_Wr01(pe1_l_r_hist_ia_ctrl, hif_hist_ai, 1);
					DE_P1L_L9B0_WrFL(pe1_l_r_hist_ia_ctrl);
				} else {
					DE_P1L_L9B0_RdFL(pe1_r_r_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hif_hist_enable, 0);
					DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hif_hist_ai, 1);
					DE_P1L_L9B0_WrFL(pe1_r_r_hist_ia_ctrl);
				}
				break;
			default :
				BREAK_WRONG(histo_type);
		}
	} while(0);

	return ret;
}

static int PE_D3D_ReleaseHIS(void)
{
    int ret = RET_OK;

	do {
		DE_P1L_L9B0_RdFL(pe1_r_r_hist_ia_ctrl);
		DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hist_rd_done, 1);
		DE_P1L_L9B0_WrFL(pe1_r_r_hist_ia_ctrl);
		DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hist_rd_done, 0);
		DE_P1L_L9B0_WrFL(pe1_r_r_hist_ia_ctrl);

		// host mode restore (read done)
		DE_P1L_L9B0_RdFL(pe1_l_g_hist_ia_ctrl);
		DE_P1L_L9B0_RdFL(pe1_l_b_hist_ia_ctrl);
		DE_P1L_L9B0_RdFL(pe1_l_r_hist_ia_ctrl);
		DE_P1L_L9B0_RdFL(pe1_r_g_hist_ia_ctrl);
		DE_P1L_L9B0_RdFL(pe1_r_b_hist_ia_ctrl);
		DE_P1L_L9B0_RdFL(pe1_r_r_hist_ia_ctrl);
		DE_P1L_L9B0_Wr01(pe1_l_g_hist_ia_ctrl, hif_hist_enable, 1);
		DE_P1L_L9B0_Wr01(pe1_l_g_hist_ia_ctrl, hif_hist_ai, 0);
		DE_P1L_L9B0_Wr01(pe1_l_b_hist_ia_ctrl, hif_hist_enable, 1);
		DE_P1L_L9B0_Wr01(pe1_l_b_hist_ia_ctrl, hif_hist_ai, 0);
		DE_P1L_L9B0_Wr01(pe1_l_r_hist_ia_ctrl, hif_hist_enable, 1);
		DE_P1L_L9B0_Wr01(pe1_l_r_hist_ia_ctrl, hif_hist_ai, 0);
		DE_P1L_L9B0_Wr01(pe1_r_g_hist_ia_ctrl, hif_hist_enable, 1);
		DE_P1L_L9B0_Wr01(pe1_r_g_hist_ia_ctrl, hif_hist_ai, 0);
		DE_P1L_L9B0_Wr01(pe1_r_b_hist_ia_ctrl, hif_hist_enable, 1);
		DE_P1L_L9B0_Wr01(pe1_r_b_hist_ia_ctrl, hif_hist_ai, 0);
		DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hif_hist_enable, 1);
		DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hif_hist_ai, 0);
		DE_P1L_L9B0_WrFL(pe1_l_g_hist_ia_ctrl);
		DE_P1L_L9B0_WrFL(pe1_l_b_hist_ia_ctrl);
		DE_P1L_L9B0_WrFL(pe1_l_r_hist_ia_ctrl);
		DE_P1L_L9B0_WrFL(pe1_r_g_hist_ia_ctrl);
		DE_P1L_L9B0_WrFL(pe1_r_b_hist_ia_ctrl);
		DE_P1L_L9B0_WrFL(pe1_r_r_hist_ia_ctrl);
	} while(0);
	return ret;
}

static int PE_D3D_GetHIS(PE_D3D_WIN_ID_T win, PE_D3D_HISTOGRAM_TYPE_T histo_type, UINT32 *pBuf, UINT32 size)
{
    int ret = RET_OK;
	UINT32 i;

	do {
		switch ( histo_type )
		{
			case D3D_HIS_GRE :
				if( win == D3D_WIN_LFT || win == D3D_WIN_TOP ) {
					for(i = 0; i < size; i++) {
						DE_P1L_L9B0_RdFL(pe1_l_g_hist_ia_data);
						pBuf[i] = DE_P1L_L9B0_Rd(pe1_l_g_hist_ia_data);
					}
					// host mode restore (read done)
					DE_P1L_L9B0_RdFL(pe1_l_g_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_l_g_hist_ia_ctrl, hif_hist_enable, 1);
					DE_P1L_L9B0_Wr01(pe1_l_g_hist_ia_ctrl, hif_hist_ai, 0);
					DE_P1L_L9B0_WrFL(pe1_l_g_hist_ia_ctrl);
				} else {
					for(i = 0; i < size; i++) {
						DE_P1L_L9B0_RdFL(pe1_r_g_hist_ia_data);
						pBuf[i] = DE_P1L_L9B0_Rd(pe1_r_g_hist_ia_data);
					}
					// host mode restore (read done)
					DE_P1L_L9B0_RdFL(pe1_r_g_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_r_g_hist_ia_ctrl, hif_hist_enable, 1);
					DE_P1L_L9B0_Wr01(pe1_r_g_hist_ia_ctrl, hif_hist_ai, 0);
					DE_P1L_L9B0_WrFL(pe1_r_g_hist_ia_ctrl);
				}
				break;
			case D3D_HIS_BLU :
				if( win == D3D_WIN_LFT || win == D3D_WIN_TOP ) {
					for(i = 0; i < size; i++) {
						DE_P1L_L9B0_RdFL(pe1_l_b_hist_ia_data);
						pBuf[i] = DE_P1L_L9B0_Rd(pe1_l_b_hist_ia_data);
					}
					DE_P1L_L9B0_RdFL(pe1_l_b_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_l_b_hist_ia_ctrl, hif_hist_enable, 1);
					DE_P1L_L9B0_Wr01(pe1_l_b_hist_ia_ctrl, hif_hist_ai, 0);
					DE_P1L_L9B0_WrFL(pe1_l_b_hist_ia_ctrl);
				} else {
					for(i = 0; i < size; i++) {
						DE_P1L_L9B0_RdFL(pe1_r_b_hist_ia_data);
						pBuf[i] = DE_P1L_L9B0_Rd(pe1_r_b_hist_ia_data);
					}
					DE_P1L_L9B0_RdFL(pe1_r_b_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_r_b_hist_ia_ctrl, hif_hist_enable, 1);
					DE_P1L_L9B0_Wr01(pe1_r_b_hist_ia_ctrl, hif_hist_ai, 0);
					DE_P1L_L9B0_WrFL(pe1_r_b_hist_ia_ctrl);
				}
				break;
			case D3D_HIS_RED :
				if( win == D3D_WIN_LFT || win == D3D_WIN_TOP ) {
					for(i = 0; i < size; i++) {
						DE_P1L_L9B0_RdFL(pe1_l_r_hist_ia_data);
						pBuf[i] = DE_P1L_L9B0_Rd(pe1_l_r_hist_ia_data);
					}
					DE_P1L_L9B0_RdFL(pe1_l_r_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_l_r_hist_ia_ctrl, hif_hist_enable, 1);
					DE_P1L_L9B0_Wr01(pe1_l_r_hist_ia_ctrl, hif_hist_ai, 0);
					DE_P1L_L9B0_WrFL(pe1_l_r_hist_ia_ctrl);
				} else {
					for(i = 0; i < size; i++) {
						DE_P1L_L9B0_RdFL(pe1_r_r_hist_ia_data);
						pBuf[i] = DE_P1L_L9B0_Rd(pe1_r_r_hist_ia_data);
					}
					DE_P1L_L9B0_RdFL(pe1_r_r_hist_ia_ctrl);
					DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hif_hist_enable, 1);
					DE_P1L_L9B0_Wr01(pe1_r_r_hist_ia_ctrl, hif_hist_ai, 0);
					DE_P1L_L9B0_WrFL(pe1_r_r_hist_ia_ctrl);
				}
				break;
			default :
				BREAK_WRONG(histo_type);
		}
	} while(0);

	return ret;
}

static int PE_D3D_SetD3D(LX_PE_D3D_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	LX_PE_D3D_THR_T stParams;
	UINT32 i;

	do {
		CHECK_KNULL(pstParams);

		pCfg->enable     = pstParams->enb;
		pCfg->sel_alg    = 1;
		pCfg->rb_bin_d3d = D3D_MAX_BIN; // ?
		pCfg->tmp_fmt    = LX_PE_D3D_FMT_2D_2D;
		pCfg->d3d_fmt    = LX_PE_D3D_FMT_2D_2D;
		pCfg->dep_fmt    = LX_PE_D3D_FMT_2D_2D;
		pCfg->cap_enb    = (pstParams->cap_info.cap_enb>=LX_PE_D3D_CAP_MAX)?0:pstParams->cap_info.cap_enb;
		pCfg->cap_h_line_num    = PE_D3D_MAX_LINE;;//pstParams->cap_info.h_line_num;
		pCfg->cap_v_line_num    = 0;//pstParams->cap_info.v_line_num;
		pCfg->cap_h_line_width  = 1;//pstParams->cap_info.h_line_width;
		pCfg->cap_v_line_width  = 0;//pstParams->cap_info.v_line_width;
		pCfg->cnt_start         = TRUE;

		if(gpMBase_sav == NULL)
		{
			if(gpstVencMemConfig->uiInBufBase != 0)
			{
				gpMBase_sav = (volatile UINT8 *)ioremap(gpstVencMemConfig->uiInBufBase, gpstVencMemConfig->uiInBufSize);
			}
		}

		for(i = 0;i < D3D_MAX_BAK_FMT;i++) pCfg->bak_fmt[i] = LX_PE_D3D_FMT_2D_2D;

		PE_MSG("###     pstParams->cap_enb     %d    #\n", pCfg->cap_enb);
#ifdef PE_D3D_USE_DISPARITY
		if(pstParams->sbs_disparity != NULL && pstParams->tnb_disparity != NULL)
		{
			memcpy(depth_info.disparity_sbs , pstParams->sbs_disparity, sizeof(UINT16)*8);
			memcpy(depth_info.disparity_tnb , pstParams->tnb_disparity, sizeof(UINT16)*8);
		}
#endif //#ifdef PE_D3D_USE_DISPARITY
		if(pstParams->thr.tpd_thr == 0xFFFFFFFF)
		{
			memcpy(&stParams, &default_thr_d, sizeof(LX_PE_D3D_THR_T));
			ret = PE_D3D_SetThreshold(&stParams);
		}
	} while (0);

	return ret;
}

static int PE_D3D_CollectBasicData(void)
{
    int ret = RET_OK;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	static UINT32 motion_l[4] = { 0 };
	static UINT32 motion_r[4] = { 0 };

	do {
		DE_P0L_L9B0_RdFL(tpd_stat_00);
		DE_P0L_L9B0_Rd01(tpd_stat_00, reg_s_status, pData->tpd);
		DE_P0L_L9B0_RdFL(tridfd_stat_00);
		DE_P0L_L9B0_Rd01(tridfd_stat_00, cb_count, pData->cb);
		DE_P0L_L9B0_RdFL(tridfd_stat_00);
		DE_P0L_L9B0_Rd01(tridfd_stat_00, cc_count, pData->cc);
		DE_P0L_L9B0_RdFL(tridfd_stat_01);
		DE_P0L_L9B0_Rd01(tridfd_stat_01, ll_count, pData->ll);
		DE_P0L_L9B0_Rd01(tridfd_stat_01, tridfd_format, pData->hw_fmt);

		DE_P0L_L9B0_RdFL(tridfd_stat_02);
		DE_P0L_L9B0_Rd01(tridfd_stat_02, delta_ss_h, pData->ssh);
		DE_P0L_L9B0_RdFL(tridfd_stat_03);
		DE_P0L_L9B0_Rd01(tridfd_stat_03, delta_ss_v, pData->ssv);
		DE_P0L_L9B0_RdFL(tridfd_stat_04);
		DE_P0L_L9B0_Rd01(tridfd_stat_04, delta_tb_v, pData->tbv);
		DE_P0L_L9B0_RdFL(tridfd_stat_05);
		DE_P0L_L9B0_Rd01(tridfd_stat_05, delta_tb_h, pData->tbh);

		DE_P0L_L9B0_RdFL(tridfd_stat_06);
		DE_P0L_L9B0_Rd01(tridfd_stat_06, ss_ratio, pData->ssr);
		DE_P0L_L9B0_RdFL(tridfd_stat_07);
		DE_P0L_L9B0_Rd01(tridfd_stat_07, tb_ratio, pData->tbr);

		DE_P0L_L9B0_RdFL(tnr_status_00);
		DE_P0L_L9B0_RdFL(tnr_status_01);
		DE_P0L_L9B0_RdFL(apl_stat_00);
		motion_l[3] = motion_l[2];
		motion_l[2] = motion_l[1];
		motion_l[1] = motion_l[0];
		DE_P0L_L9B0_Rd01(tnr_status_00, x_avg_t, motion_l[0]);
		ret = PE_D3D_GetMaxFromBuffer(motion_l, 4, &pData->motion_l);
		DE_P0L_L9B0_Rd01(tnr_status_00, nt_lvl, pData->nt_l);
		DE_P0L_L9B0_Rd01(tnr_status_01, x_avg_s, pData->spatial_l);
		DE_P0L_L9B0_Rd01(apl_stat_00, apl_stat_00, pData->apl_l);

		DE_P0R_L9B0_RdFL(tnr_status_00);
		DE_P0R_L9B0_RdFL(tnr_status_01);
		DE_P0R_L9B0_RdFL(apl_stat_00);
		motion_r[3] = motion_r[2];
		motion_r[2] = motion_r[1];
		motion_r[1] = motion_r[0];
		DE_P0R_L9B0_Rd01(tnr_status_00, x_avg_t, motion_r[0]);
		ret = PE_D3D_GetMaxFromBuffer(motion_r, 4, &pData->motion_r);
		DE_P0R_L9B0_Rd01(tnr_status_00, nt_lvl, pData->nt_r);
		DE_P0R_L9B0_Rd01(tnr_status_01, x_avg_s, pData->spatial_r);
		DE_P0R_L9B0_Rd01(apl_stat_00, apl_stat_00, pData->apl_r);
	}while(0);

	return ret;
}

static int PE_D3D_GetLrcrHistogram(void)
{
    int ret = RET_OK;
	PE_D3D_STM_T *pStm = &d3d_info.stm;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	static LX_PE_OUT_TYPE prev_outtype = LX_PE_OUT_NUM;
	static UINT32 prev_act_x0 = 0;
	static UINT32 prev_act_y0 = 0;
	static UINT32 prev_act_x1 = 0;
	static UINT32 prev_act_y1 = 0;
	UINT32 use_dtwd = 0;

	do {
		if(prev_outtype != pCfg->out_type)
		{
			ret = PE_D3D_ReleaseHIS();
			if (ret) break;
#ifdef PE_D3D_KANGSIK_YOON_TEST
			pStm->win_pos = PE_WIN_LRTB_HAF1;
#else
			pStm->win_pos = PE_WIN_LRTB_FULL;
#endif
			ret = PE_WIN_SetLrcrWin(LX_PE_OUT_2D, pStm->win_pos);
			if (ret) break;
			ret = PE_WIN_SetLrcrInOutSel();
			if (ret) break;
		}
		else if((pCfg->out_type==LX_PE_OUT_FS || \
			pCfg->out_type==LX_PE_OUT_DUAL) && \
			(prev_act_x0!=pCfg->act_x0 || \
			prev_act_y0!=pCfg->act_y0 || \
			prev_act_x1!=pCfg->act_x1 || \
			prev_act_y1!=pCfg->act_y1))
		{
#ifdef PE_D3D_KANGSIK_YOON_TEST
			pStm->win_pos = PE_WIN_LRTB_HAF1;
#else
			pStm->win_pos = PE_WIN_LRTB_FULL;
#endif
			ret = PE_WIN_SetLrcrWin(LX_PE_OUT_2D, pStm->win_pos);
			if (ret) break;
		}
		prev_outtype = pCfg->out_type;
		prev_act_x0 = pCfg->act_x0;
		prev_act_y0 = pCfg->act_y0;
		prev_act_x1 = pCfg->act_x1;
		prev_act_y1 = pCfg->act_y1;
		if((pCfg->out_type != LX_PE_OUT_2D)||(!pCfg->enable))
		{
			pStm->nxt_stm = D3D_STM_HIS_RDY__LR;
			break;
		}

		pData->complete_flag = FALSE;
		pStm->cur_stm = pStm->nxt_stm;
		switch (pStm->cur_stm)
		{
			case D3D_STM_HIS_RDY__LR :
				pStm->win_pos++;	// change window position to next position (full -> half1 -> half2 -> full -> half1 -> ...)
				if(pCfg->enable == LX_PE_D3D_DEC_FIX_FULL_WIN || (PE_D3D_WIN_RATIO == 1)){if(pStm->win_pos >= PE_WIN_LRTB_HAF1) pStm->win_pos = PE_WIN_LRTB_FULL;}
				else{
#ifdef PE_D3D_KANGSIK_YOON_TEST
					if(pStm->win_pos >= PE_WIN_MAX) pStm->win_pos = PE_WIN_LRTB_HAF1;
#else
					if(pStm->win_pos >= PE_WIN_MAX) pStm->win_pos = PE_WIN_LRTB_FULL;
#endif
				}
				PE_WIN_SetLrcrWin(LX_PE_OUT_SS, pStm->win_pos);
				PE_WIN_SetLrcrInOutSel();
				pStm->nxt_stm = D3D_STM_HIS_RDY_LR1;
				break;
			case D3D_STM_HIS_RDY_LR1 :
				pStm->nxt_stm = D3D_STM_HIS_RDY_LR2;
				break;
			case D3D_STM_HIS_RDY_LR2 :
				pStm->nxt_stm = D3D_STM_HIS_RDY_LR3;
				break;
			case D3D_STM_HIS_RDY_LR3 :
				pStm->nxt_stm = D3D_STM_HIS_SET__LR;
				break;
			case D3D_STM_HIS_SET__LR :
				ret = PE_D3D_EnableReadHIS(TRUE);
				pStm->nxt_stm = D3D_STM_HIS_REQ__LR;
				break;
			case D3D_STM_HIS_REQ__LR :
				pStm->nxt_stm = D3D_STM_HIS_GET_LRG;
				break;
			case D3D_STM_HIS_GET_LRG :
				ret = PE_D3D_RequestHIS(D3D_WIN_LFT, D3D_HIS_GRE);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_LFT, D3D_HIS_GRE, pData->hist_l_g, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_RequestHIS(D3D_WIN_RGT, D3D_HIS_GRE);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_RGT, D3D_HIS_GRE, pData->hist_r_g, pCfg->rb_bin_d3d);
				if (ret) break;
				// cal G diff
				if(use_dtwd == 0)
					PE_D3D_GetDiff(pCfg->rb_bin_d3d, pData->hist_l_g, pData->hist_r_g, &pData->g_diff);
				else
					PE_D3D_GetDTWDistance(pData->hist_l_g, pData->hist_r_g, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, &pData->g_diff);
			#ifndef PE_D3D_STRICT_DECIDE
				ret = PE_D3D_GetHistDistance(pData->hist_l_g, pData->hist_r_g, pCfg->rb_bin_d3d, &pData->dist_l_g, &pData->dist_r_g);
			#endif
				pStm->nxt_stm = D3D_STM_HIS_GET_LRB;
				break;
			case D3D_STM_HIS_GET_LRB :
				ret = PE_D3D_RequestHIS(D3D_WIN_LFT, D3D_HIS_BLU);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_LFT, D3D_HIS_BLU, pData->hist_l_b, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_RequestHIS(D3D_WIN_RGT, D3D_HIS_BLU);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_RGT, D3D_HIS_BLU, pData->hist_r_b, pCfg->rb_bin_d3d);
				if (ret) break;
				// cal B diff
				if(use_dtwd == 0)
					PE_D3D_GetDiff(pCfg->rb_bin_d3d, pData->hist_l_b, pData->hist_r_b, &pData->b_diff);
				else
					PE_D3D_GetDTWDistance(pData->hist_l_b, pData->hist_r_b, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, &pData->b_diff);
			#ifndef PE_D3D_STRICT_DECIDE
				ret = PE_D3D_GetHistDistance(pData->hist_l_b, pData->hist_r_b, pCfg->rb_bin_d3d, &pData->dist_l_b, &pData->dist_r_b);
			#endif
				pStm->nxt_stm = D3D_STM_HIS_GET_LRR;
				break;
			case D3D_STM_HIS_GET_LRR :
				ret = PE_D3D_RequestHIS(D3D_WIN_LFT, D3D_HIS_RED);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_LFT, D3D_HIS_RED, pData->hist_l_r, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_RequestHIS(D3D_WIN_RGT, D3D_HIS_RED);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_RGT, D3D_HIS_RED, pData->hist_r_r, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_ReleaseHIS();
				if (ret) break;
				ret = PE_D3D_EnableReadHIS(FALSE);
				// cal R diff
				if(use_dtwd == 0)
					PE_D3D_GetDiff(pCfg->rb_bin_d3d, pData->hist_l_r, pData->hist_r_r, &pData->r_diff);
				else
					PE_D3D_GetDTWDistance(pData->hist_l_r, pData->hist_r_r, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, &pData->r_diff);
			#ifndef PE_D3D_STRICT_DECIDE
				ret = PE_D3D_GetHistDistance(pData->hist_l_r, pData->hist_r_r, pCfg->rb_bin_d3d, &pData->dist_l_r, &pData->dist_r_r);
			#endif
				// cal LR diff with g/b/r
				PE_D3D_GetMax3(&pData->g_diff, &pData->b_diff, &pData->r_diff, &pData->lr_diff);
				pStm->nxt_stm = D3D_STM_HIS_TMP;
			case D3D_STM_HIS_TMP :
				pStm->nxt_stm = D3D_STM_HIS_RDY__TB;
				break;
			case D3D_STM_HIS_RDY__TB :
				PE_WIN_SetLrcrWin(LX_PE_OUT_TB, pStm->win_pos);
				PE_WIN_SetLrcrInOutSel();
				pStm->nxt_stm = D3D_STM_HIS_SET__TB;
				break;
			case D3D_STM_HIS_SET__TB :
				ret = PE_D3D_EnableReadHIS(TRUE);
				pStm->nxt_stm = D3D_STM_HIS_REQ__TB;
				break;
			case D3D_STM_HIS_REQ__TB :
				pStm->nxt_stm = D3D_STM_HIS_GET_TBG;
				break;
			case D3D_STM_HIS_GET_TBG :
				ret = PE_D3D_RequestHIS(D3D_WIN_TOP, D3D_HIS_GRE);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_TOP, D3D_HIS_GRE, pData->hist_t_g, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_RequestHIS(D3D_WIN_BOT, D3D_HIS_GRE);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_BOT, D3D_HIS_GRE, pData->hist_b_g, pCfg->rb_bin_d3d);
				if (ret) break;
				// cal G diff
				if(use_dtwd == 0)
					PE_D3D_GetDiff(pCfg->rb_bin_d3d, pData->hist_t_g, pData->hist_b_g, &pData->g_diff);
				else
					PE_D3D_GetDTWDistance(pData->hist_t_g, pData->hist_b_g, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, &pData->g_diff);
			#ifndef PE_D3D_STRICT_DECIDE
				ret = PE_D3D_GetHistDistance(pData->hist_t_g, pData->hist_b_g, pCfg->rb_bin_d3d, &pData->dist_t_g, &pData->dist_b_g);
			#endif
				pStm->nxt_stm = D3D_STM_HIS_GET_TBB;
				break;
			case D3D_STM_HIS_GET_TBB :
				ret = PE_D3D_RequestHIS(D3D_WIN_TOP, D3D_HIS_BLU);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_TOP, D3D_HIS_BLU, pData->hist_t_b, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_RequestHIS(D3D_WIN_BOT, D3D_HIS_BLU);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_BOT, D3D_HIS_BLU, pData->hist_b_b, pCfg->rb_bin_d3d);
				if (ret) break;
				// cal B diff
				if(use_dtwd == 0)
					PE_D3D_GetDiff(pCfg->rb_bin_d3d, pData->hist_t_b, pData->hist_b_b, &pData->b_diff);
				else
					PE_D3D_GetDTWDistance(pData->hist_t_b, pData->hist_b_b, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, &pData->b_diff);
			#ifndef PE_D3D_STRICT_DECIDE
				ret = PE_D3D_GetHistDistance(pData->hist_t_b, pData->hist_b_b, pCfg->rb_bin_d3d, &pData->dist_t_b, &pData->dist_b_b);
			#endif
				pStm->nxt_stm = D3D_STM_HIS_GET_TBR;
				break;
			case D3D_STM_HIS_GET_TBR :
				ret = PE_D3D_RequestHIS(D3D_WIN_TOP, D3D_HIS_RED);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_TOP, D3D_HIS_RED, pData->hist_t_r, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_RequestHIS(D3D_WIN_BOT, D3D_HIS_RED);
				if (ret) break;
				ret = PE_D3D_GetHIS(D3D_WIN_BOT, D3D_HIS_RED, pData->hist_b_r, pCfg->rb_bin_d3d);
				if (ret) break;
				ret = PE_D3D_ReleaseHIS();
				if (ret) break;
				ret = PE_D3D_EnableReadHIS(FALSE);
				// cal R diff
				if(use_dtwd == 0)
					PE_D3D_GetDiff(pCfg->rb_bin_d3d, pData->hist_t_r, pData->hist_b_r, &pData->r_diff);
				else
					PE_D3D_GetDTWDistance(pData->hist_t_r, pData->hist_b_r, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, pCfg->rb_bin_d3d, &pData->r_diff);
			#ifndef PE_D3D_STRICT_DECIDE
				ret = PE_D3D_GetHistDistance(pData->hist_t_r, pData->hist_b_r, pCfg->rb_bin_d3d, &pData->dist_t_r, &pData->dist_b_r);
			#endif
				// cal TB diff with g/b/r
				PE_D3D_GetMax3(&pData->g_diff, &pData->b_diff, &pData->r_diff, &pData->tb_diff);
				pData->complete_flag = TRUE;
				pStm->nxt_stm = D3D_STM_HIS_RDY__LR;
				break;
			default :
				BREAK_WRONG(pStm->cur_stm);
		}
	} while(0);
	return ret;
}
static UINT32 PE_D3D_GetAcGain3dInfo(void)
{
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	UINT32 type_chg=0;
	static UINT32 d3d_chk=0;
	static LX_PE_D3D_FORMAT_T cur_fmt = LX_PE_D3D_FMT_MAX;
	static LX_PE_OUT_TYPE pre_out = LX_PE_OUT_NUM;
	static LX_PE_3D_IN_TYPE pre_in = LX_PE_3D_IN_NUM;

	do{
		/* 0. check pattern detect result */
		if(!pCfg->mute_en)
		{
			if(pre_out==LX_PE_OUT_2D && pCfg->out_type!=LX_PE_OUT_2D)
			{
				cur_fmt=pCfg->d3d_fmt;
			}
		}
		else
		{
			cur_fmt=LX_PE_D3D_FMT_MAX;
		}
		/* 1. check type change */
		if(pre_out!=pCfg->out_type||pre_in!=pCfg->in_type)
		{
			type_chg=1;
			pre_out = pCfg->out_type;
			pre_in = pCfg->in_type;
		}
		#ifdef PE_D3D_USE_LINE_DIFF_BY_SW
		/* 2. check d3d */
		if((pCfg->out_type==LX_PE_OUT_TB||pCfg->out_type==LX_PE_OUT_SS||\
			pCfg->out_type==LX_PE_OUT_FS||pCfg->out_type==LX_PE_OUT_DUAL)&&\
			(pCfg->in_type==LX_PE_3D_IN_TB||pCfg->in_type==LX_PE_3D_IN_SS))
		{
			if(type_chg && cur_fmt<LX_PE_D3D_FMT_MAX)
			{
				if(pCfg->in_type==LX_PE_3D_IN_SS && cur_fmt!=LX_PE_D3D_FMT_3D_SS)
				{
					d3d_chk=2;	//not ss
				}
				else if(pCfg->in_type==LX_PE_3D_IN_TB && cur_fmt!=LX_PE_D3D_FMT_3D_TB)
				{
					d3d_chk=1;	//not tb
				}
				else
				{
					d3d_chk=0;	//normal
				}
				/*printk("[%s,%d][chg:%d]o:%d,i:%d, cur_fmt:%d, -> chk:%d\n\n",__F__,__L__,\
					type_chg,pCfg->out_type,pCfg->in_type,cur_fmt,d3d_chk);*/
			}
			//else keep d3d_chk or don't care.
		}
		else
		{
			d3d_chk=0;	//normal
		}
		#endif
	}while(0);
	return d3d_chk;
}
static int PE_D3D_GetDceHistogram(void)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	PE_DCM_DCE_HISTO_T histo_info_0;
	PE_DCM_DCE_HISTO_T histo_info_1;
	static LX_PE_OUT_TYPE prev_outtype = LX_PE_OUT_NUM;
	PE_CCM_AC_GAIN_INFO_T ac_gain_info;

	UINT32 i;

	PE_D3D_DTA_T *pData = &d3d_info.dta;

	do {
		if(prev_outtype != pCfg->out_type)
		{
			PE_WIN_SetD3dDceHistoWin();
		}
		prev_outtype = pCfg->out_type;

		histo_info_0.win_id = LX_PE_WIN_MAIN;
		histo_info_0.bin_num = 32;
		histo_info_1.win_id = LX_PE_WIN_SUB;
		histo_info_1.bin_num = 32;
		PE_DCM_GetDceAllHistogram(&histo_info_0,&histo_info_1,&pCfg->validL, &pCfg->validR);

		pData->hist_max_bin_val = GET_BITS(histo_info_0.status[2],8,21);
		pData->hist_max_bin_num = GET_BITS(histo_info_0.status[2],0,6);
		pData->hist_diff_sum    = GET_BITS(histo_info_0.status[3],0,22);

		memcpy(pData->dce_l, histo_info_0.histogram, 32*sizeof(UINT32));
		memcpy(pData->dce_r, histo_info_1.histogram, 32*sizeof(UINT32));
	#ifndef PE_D3D_STRICT_DECIDE
		ret = PE_D3D_GetHistDistance(pData->dce_l, pData->dce_r, pCfg->rb_bin_d3d, &pData->dist_l, &pData->dist_r);
	#endif
		pData->dce_diff = 0;
		switch(pCfg->out_type)
		{
			case LX_PE_OUT_TB :
			case LX_PE_OUT_SS :
				for(i = 0; i < 32; i++)	pData->dce_diff += abs((pData->dce_l[i]>>1) - pData->dce_r[i]);
				break;
			case LX_PE_OUT_FS :
			case LX_PE_OUT_3D_2D :
			case LX_PE_OUT_DUAL :
			default :
				for(i = 0; i < 32; i++)	pData->dce_diff += abs((pData->dce_l[i]>>0) - pData->dce_r[i]);
				pData->dce_diff >>= 1;
				break;
		}

		/* set pe0 detour */
		ret = PE_CMN_SetFrontPeDetour();
		if (ret) break;
		/* set lrcr gain according to pattern detection */
		ac_gain_info.sat_status = histo_info_0.sat_status;
		ac_gain_info.d3d_chk=PE_D3D_GetAcGain3dInfo();
		ret = PE_CCM_SetAutoCrGain(&ac_gain_info);
		if (ret) break;
		/* set tnr measure window */
		ret = PE_NRD_SetMeasureWinCtrl();
		if (ret) break;
	} while(0);

	return ret;
}

static int PE_D3D_GetDCEDelta(UINT32 cur_dce_diff, UINT32 *delta)
{
	int ret = RET_OK;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	UINT32 i = 0;

	do {
		pData->dce_diff_delta[0] = cur_dce_diff;
		for(i = 0;i < D3D_MAX_DCE_DLT - 1;i++) pData->dce_diff_delta[D3D_MAX_DCE_DLT - 1 - i] = pData->dce_diff_delta[D3D_MAX_DCE_DLT - 2 - i];
		for(i = 0;i < D3D_MAX_DCE_DLT;i++)     *delta += abs(cur_dce_diff - pData->dce_diff_delta[i]);
		*delta /= D3D_MAX_DCE_DLT;
	} while(0);

	return ret;
}

#ifdef PE_D3D_USE_LINE_DIFF_BY_SW
static int PE_D3D_GetOVInfo(PE_D3D_CAP_SRC_T ov_src, PE_D3D_OV_INFO_T *ov_info)
{
	int ret = RET_OK;
	UINT32 stride;
	UINT32 intr_mask;

	do {
		switch (ov_src)
		{
			case D3D_CAP_SRC_L_OVR :
			{
				DE_DEC_L9B_RdFL(dec_intr_mask);
				DE_DEC_L9B_Rd01(dec_intr_mask, dec_intr_mask, intr_mask);
				ov_info->src_valid = ((intr_mask & (1<<23)) == 0)?TRUE:FALSE;

				DE_MIB_L9_RdFL(mifb_saddr_rd_ext0);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ext0, req_rd_saddr_8_ovm_y_msb4b, ov_info->y_msb);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ext0, req_rd_saddr_8_ovm_c_msb4b, ov_info->c_msb);

				DE_MIB_L9_RdFL(mifb_saddr_rd_ovm_y);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ovm_y, req_rd_saddr_8_ovm_y, ov_info->y_base);
				DE_MIB_L9_RdFL(mifb_saddr_rd_ovm_c);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ovm_c, req_rd_saddr_8_ovm_c, ov_info->c_base);

				DE_MIB_L9_RdFL(mifb_rd_set_10b);
				DE_MIB_L9_Rd01(mifb_rd_set_10b, set_10b_req_rd_ovm_y, ov_info->bpp);

				#if 0
				DE_MIB_L9_RdFL(mifb_rd_cmd_stride0);
				DE_MIB_L9_Rd01(mifb_rd_cmd_stride0, cmd_rd_stride_v_8_ovm_y, ov_info->stride);
				#else
				ov_info->stride = 2048;
				#endif

				DE_OVL_L9_RdFL(ovl_ov_msize);
				DE_OVL_L9_Rd01(ovl_ov_msize, m_hsize, ov_info->h);
				DE_OVL_L9_Rd01(ovl_ov_msize, m_vsize, ov_info->v);

				DE_MSL_L9_RdFL(msc_c_format_l);
				DE_MSL_L9_Rd01(msc_c_format_l, out_c_format, ov_info->sub_sample);
			}
			break;
			case D3D_CAP_SRC_S_CVR :
			{
				DE_DEC_L9B_RdFL(dec_intr_mask);
				DE_DEC_L9B_Rd01(dec_intr_mask, dec_intr_mask, intr_mask);
				ov_info->src_valid = ((intr_mask & (1<<16)) == 0)?TRUE:FALSE;

				DE_MIF_L9_RdFL(miff_saddr_rd_ext0);
				DE_MIF_L9_Rd01(miff_saddr_rd_ext0, req_rd_saddr_cve_y_msb4b, ov_info->y_msb);
				DE_MIF_L9_Rd01(miff_saddr_rd_ext0, req_rd_saddr_cve_c_msb4b, ov_info->c_msb);

				DE_MIF_L9_RdFL(miff_saddr_rd_cve_yc);
				DE_MIF_L9_Rd01(miff_saddr_rd_cve_yc, req_rd_saddr_cve_y, ov_info->y_base);
				DE_MIF_L9_Rd01(miff_saddr_rd_cve_yc, req_rd_saddr_cve_c, ov_info->c_base);
				#if 0
				DE_MIF_L9_RdFL(miff_rd_cmd_stride0);
				DE_MIF_L9_Rd01(miff_rd_cmd_stride0, cmd_rd_stride_v_cve_y, stride);
				#endif

				DE_SSC_L9_RdFL(ssc_win_out_size);
				DE_SSC_L9_Rd01(ssc_win_out_size, out_win_h_size, ov_info->h);
				DE_SSC_L9_Rd01(ssc_win_out_size, out_win_v_size, ov_info->v);

				DE_SSC_L9_RdFL(ssc_ctrl);
				DE_SSC_L9_Rd01(ssc_ctrl, dvr_write_mode, stride);
				if(stride)
					ov_info->stride = ((ov_info->h + 15) / 16) * 16;
				else
					ov_info->stride = 1024;

				DE_SSC_L9_RdFL(ssc_c_format);
				DE_SSC_L9_Rd01(ssc_c_format, out_c_format, ov_info->sub_sample);
			}
			break;
			case D3D_CAP_SRC_L_PRW :
			case D3D_CAP_SRC_L_TNR :
			case D3D_CAP_SRC_R_PRW :
			case D3D_CAP_SRC_R_TNR :
			case D3D_CAP_SRC_R_OVR :
			default :
				ov_info->src_valid = FALSE;
				break;
		}
	} while(0);

	return ret;
}

static int PE_D3D_GetStripFromFrame(PE_D3D_OV_INFO_T *ov_info, PE_D3D_CAP_INFO_T *capture_info, UINT32 h_line_num, UINT32 h_line_width, UINT32 v_line_num, UINT32 v_line_width)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	volatile UINT8 *pFrameBase;
	UINT32 i,j;
#ifdef PE_D3D_USE_VLINE
	UINT32 h_mem_offset = 0;
#endif
	UINT32 v_mem_offset = 0;
	UINT32 sampling_size = 0;
	UINT32 top_offset = 32;

	do {
		if( ov_info->src_valid == FALSE )
		{
			if(pCfg->cap_enb >= LX_PE_D3D_CAP_FMT) PE_PRINT("%s : src_valid [ %d ]\n", __F__, ov_info->src_valid);
			ret = RET_ERROR;
			break;
		}
		if(	(ov_info->y_base == 0)          || \
			(ov_info->h == 0)               || \
			(ov_info->v == 0)               || \
			(ov_info->stride == 0)          || \
			(ov_info->h > PE_D3D_MAX_HSIZE) || \
			(ov_info->v > PE_D3D_MAX_VSIZE) || \
			(ov_info->v < (top_offset<<1))  || \
			(ov_info->stride > 2048)        || \
			(h_line_num > PE_D3D_MAX_LINE)  || \
			(h_line_width > PE_D3D_MAX_STRIP_WIDTH))
		{
			if(pCfg->cap_enb >= LX_PE_D3D_CAP_FMT) PE_PRINT("h_size[%d]/v_size[%d]/y_base[%d]/h_line_num[%d]/h_line_width[%d]\n", capture_info->h_size, capture_info->v_size, ov_info->y_base, h_line_num, h_line_width);
			ret = RET_ERROR;
			break;
		}

		if(ov_info->y_msb == 0x7)
		{
			if((gpMBase_sav == NULL) || (gpstVencMemConfig->uiInBufBase == 0))
			{
				ret = RET_ERROR;
				return ret;
			}

			if((ov_info->y_base << 14) > (((gpstVencMemConfig->uiInBufBase - 0x70000000) + gpstVencMemConfig->uiInBufSize)) - (PE_D3D_MAX_HSIZE * PE_D3D_MAX_VSIZE))
			{
				/*if(pCfg->cap_enb >= LX_PE_D3D_CAP_FMT)*/ PE_PRINT("%s[%d] error : mem_base 0x%08x , size 0x%x < cur y_base  0x%08x\n", __F__, __L__, gpstVencMemConfig->uiInBufBase, gpstVencMemConfig->uiInBufSize, (ov_info->y_base << 14));
				ret = RET_ERROR;
				break;
			}
						
			pFrameBase = (volatile UINT8*)((UINT32)gpMBase_sav + ((ov_info->y_base << 14) - (gpstVencMemConfig->uiInBufBase - 0x70000000)));
		}
		else if(ov_info->y_msb == 0x8)
		{
			if((ov_info->y_base << 14) > (VIDEO_L9_MEM_SIZE_OF_FRAME_MEMORY - (PE_D3D_MAX_HSIZE * PE_D3D_MAX_VSIZE)))
			{
				/*if(pCfg->cap_enb >= LX_PE_D3D_CAP_FMT)*/ PE_PRINT("%s[%d] error : mem_base 0x%08x , size 0x%x < cur y_base  0x%08x\n", __F__, __L__, VIDEO_L9_FRAME_DDR_BASE, VIDEO_L9_MEM_SIZE_OF_FRAME_MEMORY, (ov_info->y_base << 14));
				ret = RET_ERROR;
				break;
			}

			pFrameBase = (volatile UINT8*)((UINT32)gpMBase_dpp + (ov_info->y_base << 14));
		}
		else
		{
			if(pCfg->cap_enb >= LX_PE_D3D_CAP_FMT) PE_PRINT("%s : un-defined msb [ 0x%X000 0000 ]\n", __F__, ov_info->y_msb & 0xF);
			ret = RET_ERROR;
			break;
		}

		capture_info->h_size = ov_info->h;
		capture_info->v_size = ov_info->v;
		capture_info->h_line_num = h_line_num;
		capture_info->h_pos_offset = ov_info->v / (h_line_num + 2);

		sampling_size = ((capture_info->v_size>>1) - top_offset)/(h_line_num>>1);

		if(sampling_size > (PE_D3D_MAX_VSIZE>>1))
		{
			if(pCfg->cap_enb >= LX_PE_D3D_CAP_FMT) PE_PRINT("sampling_size  %d\n", sampling_size);
			ret = RET_ERROR;
			break;
		}

		if(pCfg->cap_enb >= LX_PE_D3D_CAP_LOG) PE_PRINT("pFrameBase : 0x%08X, h/v/s[%d/%d/%d]  h_line/h_width/v_line/v_width [%d/%d/%d/%d] -> sampling_size[%d]\n",		\
										(ov_info->y_msb == 0x7)?(VIDEO_L9_CODEC_DDR_BASE + (ov_info->y_base << 14)):(VIDEO_L9_FRAME_DDR_BASE + (ov_info->y_base << 14)), ov_info->h, ov_info->v, ov_info->stride,	\
										h_line_num, h_line_width, v_line_num, v_line_width, sampling_size);

		// h line capture
		v_mem_offset = top_offset * ov_info->stride;
		for(i=0;i<h_line_num>>1;i++)
		{
			for(j=0;j<h_line_width;j++)
			{
				memcpy((UINT8*)(capture_info->pHLine[i] + ov_info->h * j), (UINT8*)(pFrameBase + v_mem_offset + ov_info->stride * j), ov_info->h);
				/*debug*/if(pCfg->cap_enb >= LX_PE_D3D_CAP_DRAW) memset((UINT8*)(pFrameBase + v_mem_offset + ov_info->stride * j), 0, ov_info->h);
			}
			v_mem_offset += sampling_size * ov_info->stride;
		}

		// h line capture for center difference (Delta)
		v_mem_offset = ((capture_info->v_size>>1) - (PE_D3D_MAX_CENTER_LINE>>1)) * ov_info->stride;
		for(i=0;i<PE_D3D_MAX_CENTER_LINE;i++)
		{
			memcpy((UINT8*)(capture_info->pHLineCenter[i]), (UINT8*)(pFrameBase + v_mem_offset + ov_info->stride * i), ov_info->h);
			/*debug*/if(pCfg->cap_enb >= LX_PE_D3D_CAP_DRAW) memset((UINT8*)(pFrameBase + v_mem_offset + ov_info->stride * i), 0x80, ov_info->h);
		}

		// center line drawing for debug
		v_mem_offset = ((capture_info->v_size>>1) - 1) * ov_info->stride;
		/*debug*/if(pCfg->cap_enb >= LX_PE_D3D_CAP_DRAW) memset((UINT8*)(pFrameBase + v_mem_offset + ov_info->stride * 1), 0, ov_info->h);

		// h line capture
		v_mem_offset = (top_offset + (capture_info->v_size>>1)) * ov_info->stride;
		for(i=h_line_num>>1;i<h_line_num;i++)
		{
			for(j=0;j<h_line_width;j++)
			{
				memcpy((UINT8*)(capture_info->pHLine[i] + ov_info->h * j), (UINT8*)(pFrameBase + v_mem_offset + ov_info->stride * j), ov_info->h);
				/*debug*/if(pCfg->cap_enb >= LX_PE_D3D_CAP_DRAW) memset((UINT8*)(pFrameBase + v_mem_offset + ov_info->stride * j), 0, ov_info->h);
			}
			v_mem_offset += sampling_size * ov_info->stride;
		}
#ifdef PE_D3D_USE_VLINE
		// v line capture
		capture_info->v_pos_offset = ov_info->h / (v_line_num + 1);
		capture_info->v_line_num = v_line_num;
		h_mem_offset = capture_info->v_pos_offset;
		for(i=0;i<v_line_num;i++)
		{
			for(j=0;j<ov_info->v;j++)
			{
				memcpy((UINT8*)(capture_info->pVLine[i] + v_line_width * j), (UINT8*)(pFrameBase + h_mem_offset + ov_info->stride * j), v_line_width);
				/*debug*/if(pCfg->cap_enb >= LX_PE_D3D_CAP_DRAW) memset((UINT8*)(pFrameBase + h_mem_offset + ov_info->stride * j), 16, v_line_width);
			}
			h_mem_offset += capture_info->v_pos_offset;
		}
#endif
	} while(0);

	return ret;
}

static int PE_D3D_InitFrameMemory(UINT32 h_max_line, UINT32 v_max_line)
{
	int ret = RET_OK;
	UINT32 i;

	do {
		if(h_max_line > PE_D3D_MAX_LINE)
			break;
		if(v_max_line > PE_D3D_MAX_LINE)
			break;

		for(i=0;i<h_max_line;i++) cap_info.pHLine[i] = NULL;
#ifdef PE_D3D_USE_VLINE
		for(i=0;i<v_max_line;i++) cap_info.pVLine[i] = NULL;
#endif
		for(i=0;i<PE_D3D_MAX_CENTER_LINE;i++) cap_info.pHLineCenter[i] = NULL;

		for(i=0;i<h_max_line;i++) cap_info.pHLine[i] = (UINT8*)vmalloc(PE_D3D_MAX_HSIZE * PE_D3D_MAX_STRIP_WIDTH);
#ifdef PE_D3D_USE_VLINE
		for(i=0;i<v_max_line;i++) cap_info.pVLine[i] = (UINT8*)vmalloc(PE_D3D_MAX_VSIZE * PE_D3D_MAX_STRIP_WIDTH);
#endif
		for(i=0;i<PE_D3D_MAX_CENTER_LINE;i++) cap_info.pHLineCenter[i] = (UINT8*)vmalloc(PE_D3D_MAX_HSIZE * PE_D3D_MAX_CENTER_LINE);

		gpMBase_dpp = (volatile UINT8 *)ioremap(VIDEO_L9_FRAME_DDR_BASE, VIDEO_L9_MEM_SIZE_OF_FRAME_MEMORY);
		//gpMBase_sav = (volatile UINT8 *)ioremap(VIDEO_L9_CODEC_DDR_BASE, VIDEO_L9_FRAME_DDR_BASE - VIDEO_L9_CODEC_DDR_BASE);
		//gpMBase_sav = (volatile UINT8 *)ioremap(0x79A25000, 5529600);
	} while(0);

	return ret;
}
#if 0
static int PE_D3D_UnInitFrameMemory(void)
{
	int ret = RET_OK;
	UINT32 i;

	do {
		for(i=0;i<PE_D3D_MAX_LINE;i++)	if(cap_info.pHLine[i] != NULL) OS_Free(cap_info.pHLine[i]);
#ifdef PE_D3D_USE_VLINE
		for(i=0;i<PE_D3D_MAX_LINE   ;i++) 	if(cap_info.pVLine[i] != NULL) OS_Free(cap_info.pVLine[i]);
#endif
		for(i=0;i<PE_D3D_MAX_CENTER_LINE;i++)	if(cap_info.pHLineCenter[i] != NULL) OS_Free(cap_info.pHLineCenter[i]);

		if (gpMBase_dpp) iounmap((void *)gpMBase_dpp);
		if (gpMBase_sav) iounmap((void *)gpMBase_sav);
	} while(0);

	return ret;
}
#endif

static int PE_D3D_CheckTime(char *fn_str, PE_D3D_GET_TIME_T location, PE_D3D_TIME_T pos)
{
	int ret = RET_OK;
	static PE_D3D_TIME_INFO_T time_info;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	UINT32 time_diff;

	do {
		switch(pos)
		{
			case D3D_GET_START :
				time_info.tick_start_time[location] = OS_GetMsecTicks_Tag();
				break;
			default :
			case D3D_GET_END :
				time_info.tick_end_time[location] = OS_GetMsecTicks_Tag();
				if(time_info.tick_end_time[location] >= time_info.tick_start_time[location])
					time_diff = time_info.tick_end_time[location] - time_info.tick_start_time[location];
				else
					time_diff = time_info.tick_start_time[location] + (0xFFFFFFFF - time_info.tick_end_time[location]);

				if(pCfg->cap_enb >= LX_PE_D3D_CAP_TIME)
					PE_PRINT("%s :	%d msec  elapsed\n", fn_str, (time_diff==0)?1:time_diff);
				break;
		}

	} while(0);

	return ret;
}

static int PE_D3D_CaptureFrame(void)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	PE_D3D_OV_INFO_T ov_info;
	PE_D3D_CAP_INFO_T *pCapture;
	static UINT32 cap_count = 1;

	do {
		cap_count++;
		#if 0
		if(cap_count != 60)
			break;
		else
			cap_count = 0;
		#endif

		pCapture = &cap_info;

		PE_D3D_CheckTime("Capture line", D3D_GET_TIME_CAP, D3D_GET_START);

		ret = PE_D3D_GetOVInfo(D3D_CAP_SRC_S_CVR, &ov_info);
		if (ret) break;
		ret = PE_D3D_GetStripFromFrame(&ov_info, pCapture, pCfg->cap_h_line_num, pCfg->cap_h_line_width, pCfg->cap_v_line_num, pCfg->cap_v_line_width);
		if (ret) break;

		PE_D3D_CheckTime("Capture line", D3D_GET_TIME_CAP, D3D_GET_END);

		PE_D3D_CheckTime("Measure difference", D3D_GET_TIME_MAT, D3D_GET_START);

		ret = PE_D3D_MeasureLineDifference(pCapture);
		if (ret) break;

		PE_D3D_CheckTime("Measure difference", D3D_GET_TIME_MAT, D3D_GET_END);
	} while(0);

	return ret;
}

static int PE_D3D_AccumulateFormat(LX_PE_D3D_FORMAT_T *cur_fmt)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	UINT32 sum = 0;
	UINT32 ratio_2d;
	UINT32 ratio_ss;
	UINT32 ratio_tb;
	UINT32 max;

	do {
		if(!pCfg->cnt_start)
		{
			pCfg->cnt_2d = 0;
			pCfg->cnt_ss = 0;
			pCfg->cnt_tb = 0;
			break;
		}
		else
		{
			if((*cur_fmt == LX_PE_D3D_FMT_2D_2D) || (*cur_fmt == LX_PE_D3D_FMT_UNKNOWN))
				pCfg->cnt_2d++;
			else if(*cur_fmt == LX_PE_D3D_FMT_3D_SS)
				pCfg->cnt_ss++;
			else if(*cur_fmt == LX_PE_D3D_FMT_3D_TB)
				pCfg->cnt_tb++;
			else
				pCfg->cnt_2d++;

			sum = pCfg->cnt_2d + pCfg->cnt_ss + pCfg->cnt_tb;
			ratio_2d = (UINT32)((pCfg->cnt_2d * 100) / sum);
			ratio_ss = (UINT32)((pCfg->cnt_ss * 100) / sum);
			ratio_tb = (UINT32)((pCfg->cnt_tb * 100) / sum);

			PE_D3D_GetMax3(&ratio_2d, &ratio_ss, &ratio_tb, &max);
			if(max < 50)
			{
				pCfg->acc_fmt = LX_PE_D3D_FMT_2D_2D;
				break;
			}

			if(ratio_2d >= ratio_ss)
			{
				if(ratio_tb > ratio_2d)
					pCfg->acc_fmt = LX_PE_D3D_FMT_3D_TB;
				else
					pCfg->acc_fmt = LX_PE_D3D_FMT_2D_2D;
			}
			else
			{
				if(ratio_tb > ratio_ss)
					pCfg->acc_fmt = LX_PE_D3D_FMT_3D_TB;
				else
					pCfg->acc_fmt = LX_PE_D3D_FMT_3D_SS;
			}
		}
	} while(0);

	return ret;
}
#endif // #ifdef PE_D3D_USE_LINE_DIFF_BY_SW


static int PE_D3D_CheckStableFormat(BOOLEAN *pValid, LX_PE_D3D_FORMAT_T *cur_fmt)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	LX_PE_D3D_THR_T *pThr = &d3d_info.thr;
	UINT32 i = 0;
	UINT32 vld_thr = 0;
#ifdef PE_D3D_KANGSIK_YOON_TEST // Added by won.hur 2011.12.13
	UINT32 vote_nominee[LX_PE_D3D_FMT_MAX];
	BOOLEAN	valid_flag = FALSE;
	UINT32 temp =0;
#else
	UINT32 count = 0;
#endif
	do {
#ifdef PE_D3D_KANGSIK_YOON_TEST // Added by won.hur 2011.12.13
		vld_thr = pThr->vld_thr;
		for(i = 0;i< LX_PE_D3D_FMT_MAX; i++) vote_nominee[i] = 0;
		for(i = 0;i < vld_thr- 1;i++)
		{
			pCfg->bak_fmt[vld_thr - 1 - i] = pCfg->bak_fmt[vld_thr - 2 - i];
			temp = pCfg->bak_fmt[vld_thr - 1 - i];	 // To prevent latchup from dependency errors... (incase of error from out-of-order execution processor)
			if(gInputSourceChangedFlag)
			{
				if((i<(D3D_VOTE_STACK_SIZE_ON_FORMAT_CHANGE-1))&&(( temp>= LX_PE_D3D_FMT_2D_2D) && (temp < LX_PE_D3D_FMT_MAX))) vote_nominee[temp] += 1;
			}
			else
			{
				if(( temp>= LX_PE_D3D_FMT_2D_2D) && (temp < LX_PE_D3D_FMT_MAX)) vote_nominee[temp] += 1;
			}
		}
		pCfg->bak_fmt[0] = *cur_fmt;
		temp = *cur_fmt;					// To prevent latchup from dependency errors... (incase of error from out-of-order execution processor)
		vote_nominee[temp] += 1;

		for(i = 0;i< LX_PE_D3D_FMT_MAX; i++)
		{
			if(gInputSourceChangedFlag)
			{
				if((i != LX_PE_D3D_FMT_UNKNOWN)&&(vote_nominee[i] >= (D3D_VOTE_STACK_SIZE_ON_FORMAT_CHANGE - D3D_MAX_MINORITY_VOTE_VAL_CHANGED)))
				{
					valid_flag = TRUE;
					*cur_fmt = i;
				}
			}
			else
			{
				if((i != LX_PE_D3D_FMT_UNKNOWN)&&(vote_nominee[i] >= (vld_thr - D3D_MAX_MINORITY_VOTE_VAL_NORMAL)))
				{
					valid_flag = TRUE;
					*cur_fmt = i;
				}
			}
		}
		*pValid = valid_flag;
#else
		if(pThr->vld_thr > D3D_MAX_BAK_FMT)
			pThr->vld_thr = D3D_MAX_BAK_FMT;
		if(pCfg->tpd_flag == TRUE)
		{
			*pValid = FALSE;
			break;
		}

		for(i = 0;i < pThr->vld_thr - 1;i++) pCfg->bak_fmt[pThr->vld_thr - 1 - i] = pCfg->bak_fmt[pThr->vld_thr - 2 - i];
		pCfg->bak_fmt[0] = *cur_fmt;
		for(i = 0;i < pThr->vld_thr;i++)
		{
			if(*cur_fmt == pCfg->bak_fmt[i])
				count++;
		}
		//vld_thr = (pCfg->out_type!=LX_PE_OUT_2D) ? pThr->vld_thr : pThr->vld_thr>>1;
		vld_thr = pThr->vld_thr;
		if(count == vld_thr)
			*pValid = TRUE;
		else
			*pValid = FALSE;
#endif
	} while(0);
	return ret;
}


#ifdef PE_D3D_USE_DISPARITY
static int PE_D3D_CheckDepthInfo(BOOLEAN *pValid)
{
	int ret = RET_OK;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	UINT16 sbs_l_min, sbs_l_max, sbs_l_avg, sbs_r_min, sbs_r_max, sbs_r_avg;
	UINT16 tnb_t_min, tnb_t_max, tnb_t_avg, tnb_b_min, tnb_b_max, tnb_b_avg;

	do {
		*pValid = FALSE;
		if(depth_info.disparity_sbs[0] == 0xFFFF && depth_info.disparity_tnb[0] == 0xFFFF)
		{
			//*pValid = "";
			break;
		}

		memcpy(pData->dpt_sbs, depth_info.disparity_sbs, sizeof(UINT16) * 8);
		memcpy(pData->dpt_tnb, depth_info.disparity_tnb, sizeof(UINT16) * 8);

		PE_PRINT("\n\n\n");
		PE_PRINT("	SbS 			   TnB\n");
		PE_PRINT("	MIN [ %d	]	  MIN [ %d	]\n", depth_info.disparity_sbs[0], depth_info.disparity_tnb[0]);
		PE_PRINT("	MAX [ %d	]	  MAX [ %d	]\n", depth_info.disparity_sbs[1], depth_info.disparity_tnb[1]);
		PE_PRINT("L_MIN [ %d	]	L_MIN [ %d	]\n", depth_info.disparity_sbs[2], depth_info.disparity_tnb[2]);
		PE_PRINT("L_MAX [ %d	]	L_MAX [ %d	]\n", depth_info.disparity_sbs[3], depth_info.disparity_tnb[3]);
		PE_PRINT("L_AVG [ %d	]	L_AVG [ %d	]\n", depth_info.disparity_sbs[4], depth_info.disparity_tnb[4]);
		PE_PRINT("R_MIN [ %d	]	R_MIN [ %d	]\n", depth_info.disparity_sbs[5], depth_info.disparity_tnb[5]);
		PE_PRINT("R_MAX [ %d	]	R_MAX [ %d	]\n", depth_info.disparity_sbs[6], depth_info.disparity_tnb[6]);
		PE_PRINT("R_AVG [ %d	]	R_AVG [ %d	]\n", depth_info.disparity_sbs[7], depth_info.disparity_tnb[7]);
		PE_PRINT("\n\n\n");

		sbs_l_min = pData->dpt_sbs[2];
		sbs_l_max = pData->dpt_sbs[3];
		sbs_l_avg = pData->dpt_sbs[4];
		sbs_r_min = pData->dpt_sbs[5];
		sbs_r_max = pData->dpt_sbs[6];
		sbs_r_avg = pData->dpt_sbs[7];
		tnb_t_min = pData->dpt_tnb[2];
		tnb_t_max = pData->dpt_tnb[3];
		tnb_t_avg = pData->dpt_tnb[4];
		tnb_b_min = pData->dpt_tnb[5];
		tnb_b_max = pData->dpt_tnb[6];
		tnb_b_avg = pData->dpt_tnb[7];

		if( (sbs_l_min<2) && (sbs_r_min<2) && (tnb_t_min<2) && (tnb_b_min<2) )
		{
			pCfg->dep_fmt = LX_PE_D3D_FMT_2D_2D;
			#if 0
			if( (tnb_t_min==0) && (tnb_b_min==0) && (sbs_l_max!=0) && (sbs_r_max!=0) )	// case SS
			{
				if( (abs(sbs_l_min-sbs_r_min)<3) && (abs(sbs_l_max-sbs_r_max)<3) && (abs(sbs_l_avg-sbs_r_avg)<3) )
				{
					if( ((sbs_l_max+sbs_l_min)/2 <= sbs_l_avg) && ((sbs_r_max+sbs_r_min)/2 <= sbs_r_avg) && (sbs_l_max<=40) && (sbs_r_max<=40) )
						pCfg->dep_fmt = LX_PE_D3D_FMT_3D_SS;
				}
			}
			else if( (sbs_l_min==0) && (sbs_r_min==0) && (tnb_t_max!=0) && (tnb_b_max!=0) ) // case TB
			{
				if( (abs(tnb_t_min-tnb_b_min)<3) && (abs(tnb_t_max-tnb_b_max)<3) && (abs(tnb_t_avg-tnb_b_avg)<3) )
				{
					if( ((tnb_t_max+tnb_t_min)/2 <= tnb_t_avg) && ((tnb_b_max+tnb_b_min)/2 <= tnb_b_avg) && (tnb_t_max<=40) && (tnb_b_max<=40) )
						pCfg->dep_fmt = LX_PE_D3D_FMT_3D_TB;
				}
			}
			#endif
		}
		else if( (tnb_t_min<2) && (tnb_b_min<2) ) // case SS
		{
			if( (abs(sbs_l_min-sbs_r_min)<4) && (abs(sbs_l_max-sbs_r_max)<4) && (abs(sbs_l_avg-sbs_r_avg)<4) )	// L-R 의 각 disparity 값이 유사할 경우
				pCfg->dep_fmt = LX_PE_D3D_FMT_3D_SS;
			else
				pCfg->dep_fmt = LX_PE_D3D_FMT_2D_2D;
		}
		else if( (sbs_l_min<2) && (sbs_r_min<2) )	// case TB
		{
			if( (abs(tnb_t_min-tnb_b_min)<4) && (abs(tnb_t_max-tnb_b_max)<4) && (abs(tnb_t_avg-tnb_b_avg)<4) )	// T-B 의 각 disparity 값이 유사할 경우
				pCfg->dep_fmt = LX_PE_D3D_FMT_3D_TB;
			else
				pCfg->dep_fmt = LX_PE_D3D_FMT_2D_2D;
		}
		else
		{
			if( sbs_l_avg < tnb_t_avg && sbs_r_avg < tnb_b_avg)
			{
				if( (abs(sbs_l_min-sbs_r_min)<3) && (abs(sbs_l_max-sbs_r_max)<3) && (abs(sbs_l_avg-sbs_r_avg)<3) )
					pCfg->dep_fmt = LX_PE_D3D_FMT_3D_SS;
				else
					pCfg->dep_fmt = LX_PE_D3D_FMT_2D_2D;
			}
			else if ( tnb_t_avg < sbs_l_avg && tnb_b_avg < sbs_r_avg )
			{
				if ( (abs(tnb_t_min-tnb_b_min)<3) && (abs(tnb_t_max-tnb_b_max)<3) && (abs(tnb_t_avg-tnb_b_avg)<3) )
					pCfg->dep_fmt = LX_PE_D3D_FMT_3D_TB;
				else
					pCfg->dep_fmt = LX_PE_D3D_FMT_2D_2D;
			}
			else
				pCfg->dep_fmt = LX_PE_D3D_FMT_2D_2D;
		}
		*pValid = TRUE;
	} while(0);

	depth_info.disparity_sbs[0] = 0xFFFF;
	depth_info.disparity_tnb[0] = 0xFFFF;

	return ret;
}
#endif //#ifdef PE_D3D_USE_DISPARITY

static int PE_D3D_DumpHistogram(void)
{
	int ret = RET_OK;
	UINT32 itr = 0;
	UINT32 sum = 0;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	UINT32 lr_g_diff, lr_b_diff, lr_r_diff, tb_g_diff, tb_b_diff, tb_r_diff;
	UINT32 lr_g_sum = 0, lr_b_sum = 0, lr_r_sum = 0, tb_g_sum = 0, tb_b_sum = 0, tb_r_sum = 0;

	do {
		switch(pCfg->out_type)
		{
			case LX_PE_OUT_2D :
				#if 1
				PE_MSG("\nD3D : LR Correction HISTOGRAM\n");
				PE_MSG("     G [L][R]           B [L][R]           R [L][R]         :  G [T][B]           B [T][B]           R [T][B]\n");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++)
				{

					lr_g_diff = DIFF(pData->hist_l_g[itr], pData->hist_r_g[itr]);
					lr_b_diff = DIFF(pData->hist_l_b[itr], pData->hist_r_b[itr]);
					lr_r_diff = DIFF(pData->hist_l_r[itr], pData->hist_r_r[itr]);
					lr_g_sum += lr_g_diff;
					lr_b_sum += lr_b_diff;
					lr_r_sum += lr_r_diff;
					PE_MSG("%02d) [%07d][%07d] [%07d][%07d] [%07d][%07d]",itr,\
						pData->hist_l_g[itr], pData->hist_r_g[itr], pData->hist_l_b[itr], pData->hist_r_b[itr], pData->hist_l_r[itr], pData->hist_r_r[itr]);
					tb_g_diff = DIFF(pData->hist_t_g[itr], pData->hist_b_g[itr]);
					tb_b_diff = DIFF(pData->hist_t_b[itr], pData->hist_b_b[itr]);
					tb_r_diff = DIFF(pData->hist_t_r[itr], pData->hist_b_r[itr]);
					tb_g_sum += tb_g_diff;
					tb_b_sum += tb_b_diff;
					tb_r_sum += tb_r_diff;
					PE_MSG(": [%07d][%07d] [%07d][%07d] [%07d][%07d]\n",\
						pData->hist_t_g[itr], pData->hist_b_g[itr], pData->hist_t_b[itr], pData->hist_b_b[itr], pData->hist_t_r[itr], pData->hist_b_r[itr]);
				}
				PE_MSG("    Total diff\n");
				PE_MSG("     %07d            %07d            %07d          :  %07d            %07d            %07d\n", lr_g_sum, lr_b_sum, lr_r_sum, tb_g_sum, tb_b_sum, tb_r_sum);
				#else
				PE_MSG("D3D : === WIN 0  [G] LR HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_l_g[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 0  [B] LR HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_l_b[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 0  [R] LR HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_l_r[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 1  [G] LR HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_r_g[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 1  [B] LR HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_r_b[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 1  [R] LR HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_r_r[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 0  [G] TB HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_t_g[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 0  [B] TB HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_t_b[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 0  [R] TB HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_t_r[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 1  [G] TB HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_b_g[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 1  [B] TB HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_b_b[itr]);PE_PRINT("\n");
				PE_MSG("D3D : === WIN 1  [R] TB HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->hist_b_r[itr]);PE_PRINT("\n");
				#endif
				break;
			case LX_PE_OUT_TB :
			case LX_PE_OUT_SS :
			case LX_PE_OUT_FS :
			case LX_PE_OUT_3D_2D :
			case LX_PE_OUT_DUAL :
				#if 1
				PE_MSG("\nD3D : DCE HISTOGRAM\n");
				PE_MSG("L		: R\n");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++)
				{
					PE_MSG("%02d) [%07d]	: [%07d]", itr, pData->dce_l[itr], pData->dce_r[itr]);
					sum += DIFF(pData->dce_l[itr], pData->dce_r[itr]);
				}
				PE_MSG("    Total diff %d\n", sum);
				#else
				PE_MSG("D3D : === WIN 0   DCE HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->dce_l[itr]);
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) sum += pData->dce_l[itr];
				PE_MSG("\nD3D : Total : %d  pixels\n", sum);
				sum = 0;
				PE_MSG("D3D : === WIN 1   DCE HISTOGRAM\n     ");
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) PE_MSG("[%d]", pData->dce_r[itr]);
				for(itr=0;itr<pCfg->rb_bin_d3d;itr++) sum += pData->dce_r[itr];
				PE_MSG("\nD3D : Total : %d  pixels\n", sum);
				#endif
				break;
			default :
				break;
		}
	} while(0);
	return ret;
}

static int PE_D3D_DumpAllData(void)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
#ifndef PE_D3D_USE_DISPARITY
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	LX_PE_D3D_THR_T *pThr = &d3d_info.thr;
	PE_D3D_STM_T *pStm = &d3d_info.stm;
	UINT32 max_pd = 0;
	UINT32 win_half_size = 0;
#endif
	do {
#ifndef PE_D3D_USE_DISPARITY
		if(pStm->win_pos != PE_WIN_LRTB_FULL)
			win_half_size = PE_D3D_WIN_RATIO;
		else
			win_half_size = 1;

		PE_D3D_GetMax3(&pData->cb, &pData->cc, &pData->ll, &max_pd);

		PE_MSG("D3D : == value	/  threshold  ====	[outtype %d  %dx%d] [sel_alg %d] \n", pCfg->out_type, pCfg->out_win_x, pCfg->out_win_y, pCfg->sel_alg);
		PE_MSG("tpd[%d] / %d	 ,	 motion_l[%d] / 2d-%d 3d-%d , motion_r[%d]\n", pData->tpd, pThr->tpd_thr, pData->motion_l, pThr->mtn_thr_2d, pThr->mtn_thr_3d, pData->motion_r);
		PE_MSG("cb[%d] cc[%d] ll[%d] -> max_pd[%d] / %d\n", pData->cb, pData->cc, pData->ll, max_pd, pThr->ptn_thr);
		PE_MSG("ssr[%d] tbr[%d] / 2D->3D[%d] , 3D->2D[%d]\n", pData->ssr, pData->tbr, pThr->fmt_th2, pThr->fmt_th1);
		PE_MSG("ssh[%d] ssv[%d] tbh[%d] tbv[%d] \n", pData->ssh, pData->ssv, pData->tbh, pData->tbv);
		PE_MSG("LRCR win_pos[%d] (0:LRTB_FULL,1:LRTB_HAF1,2:LRTB_HAF2) \n", pStm->win_pos);

#ifdef PE_D3D_KANGSIK_YOON_TEST
		PE_MSG("thr_adj[%d] lr_diff[%d] tb_diff[%d] / fmt_th3[%d] ,  lr-tb[%d] / fmt_th4[%d] , / fmt_th6[%d] fmt_th7[%d] fmt_th8[%d] fmt_th9[%d] fmt_th10[%d]\n", \
		thr_adj, pData->lr_diff, pData->tb_diff, tmp_thr3, (int)abs(pData->lr_diff - pData->tb_diff), \
		tmp_thr4, tmp_thr6, tmp_thr7, pThr->fmt_th8, pThr->fmt_th9, pThr->fmt_th10);
#else
		PE_MSG("lr_diff[%d] tb_diff[%d] / %d ,  lr-tb[%d] / %d , / th6[%d] th7[%d] th8[%d] th9[%d] th10[%d]\n", \
		pData->lr_diff, pData->tb_diff, pThr->fmt_th3/win_half_size, (int)abs(pData->lr_diff - pData->tb_diff), \
		pThr->fmt_th4/win_half_size, pThr->fmt_th6/win_half_size, pThr->fmt_th7/win_half_size, pThr->fmt_th8, pThr->fmt_th9, pThr->fmt_th10);
#endif
		PE_MSG("dce_diff[%d] / %d  \n",	pData->dce_diff, pThr->fmt_th5);
		PE_MSG("hist_max_bin_val[%d] / %d , hist_max_bin_num[%d] , hist_diff_sum[%d] / 2d-%d 3d-%d\n",pData->hist_max_bin_val,pThr->mbv_thr,pData->hist_max_bin_num,pData->hist_diff_sum,pThr->dfs_thr_2d, pThr->dfs_thr_3d);
		PE_MSG("skp_th1[%d] skp_th2[%d] vld_thr[%d] \n",  pThr->skp_th1, pThr->skp_th2, pThr->vld_thr);
		PE_MSG("motion[%d/%d], spatial[%d/%d], apl[%d/%d], noise[%d/%d],  dual_screen_fmt[%d](0:2D,8:SS,9:TB)\n", pData->motion_l, pData->motion_r, pData->spatial_l, pData->spatial_r, pData->apl_l, pData->apl_r, pData->nt_l, pData->nt_r, pData->hw_fmt);
		PE_MSG("LRCR HistDistance l_g[%d] r_g[%d] l_b[%d] r_b[%d] l_r[%d] r_r[%d] , t_g[%d] b_g[%d] t_b[%d] b_b[%d] t_r[%d] b_r[%d]\n",\
				pData->dist_l_g, pData->dist_r_g, pData->dist_l_b, pData->dist_r_b, pData->dist_l_r, pData->dist_r_r,\
				pData->dist_t_g, pData->dist_b_g, pData->dist_t_b, pData->dist_b_b, pData->dist_t_r, pData->dist_b_r);
		PE_MSG("DCE HistDistance l[%d] r[%d]\n", pData->dist_l, pData->dist_r);
#else
		PE_MSG("from Depth controller ===>	[%d]\n", pCfg->dep_fmt);
#endif
#ifdef PE_D3D_KANGSIK_YOON_TEST	// Added by won.hur 2011.12.13
		PE_MSG("D3D : ==>> Format tmp[%d] final[%d]		(0:2D,1:CB,2:LL,3:CC,4:SS,5:TB,6:UNKNOWN)  Test pattern(%d)\n", pCfg->tmp_fmt, pCfg->d3d_fmt, pCfg->tpd_flag);
		PE_MSG("\nD3D_MESSAGE_A= %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",\
																					  pCfg->out_type,pCfg->out_win_x,pCfg->out_win_y,pData->tpd,pThr->tpd_thr,pData->motion_l,pThr->mtn_thr_2d,pThr->mtn_thr_3d,pData->motion_r,pData->cb,pData->cc,pData->ll,max_pd,pThr->ptn_thr,pData->ssr,pData->tbr,\
  																					  pThr->fmt_th2,pThr->fmt_th1,pData->ssh,pData->ssv,pData->tbh,pData->tbv,pData->lr_diff,pData->tb_diff,pThr->fmt_th3,pThr->fmt_th4,pThr->fmt_th6,pThr->fmt_th7,pThr->fmt_th8, pThr->fmt_th9, pThr->fmt_th10, pData->dce_diff);
		PE_MSG("D3D_MESSAGE_B= %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d \n",\
																			pThr->fmt_th5,pData->hist_max_bin_val,pThr->mbv_thr,pData->hist_max_bin_num,pData->hist_diff_sum,pThr->dfs_thr_2d,pThr->dfs_thr_3d,pThr->skp_th1,pThr->skp_th2,pThr->vld_thr,pData->motion_l,pData->motion_r,pData->spatial_l,pData->spatial_r,pData->apl_l,pData->apl_r,pData->nt_l,\
																						pData->nt_r,pData->hw_fmt,pData->dist_l_g,pData->dist_r_g,pData->dist_l_b,pData->dist_r_b,pData->dist_l_r,pData->dist_r_r,pData->dist_t_g,pData->dist_b_g,pData->dist_t_b,pData->dist_b_b,pData->dist_t_r,pData->dist_b_r);

#else
		PE_MSG("D3D : ==>> Format tmp[%d] final[%d]		(0:2D,1:CB,2:LL,3:CC,4:SS,5:TB)  Test pattern(%d)\n", pCfg->tmp_fmt, pCfg->d3d_fmt, pCfg->tpd_flag);
#endif
		PE_MSG("\n\n");
	} while(0);
	return ret;
}

static int PE_D3D_DecideFormat(void)
{
	int ret = RET_OK;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	PE_D3D_DTA_T *pData = &d3d_info.dta;
	LX_PE_D3D_THR_T *pThr = &d3d_info.thr;
	PE_D3D_STM_T *pStm = &d3d_info.stm;

	BOOLEAN valid;
#ifdef PE_D3D_USE_DISPARITY
	BOOLEAN depth_valid = FALSE;
#endif
	UINT32 max_pd = 0;
	UINT32 delta_avg = 0;
	static LX_PE_OUT_TYPE prev_outtype = LX_PE_OUT_NUM;
	static UINT32 out_type_change_flag = 0;
	static UINT32 out_type_change_count = 0;
	static UINT32 temmporal_skip_count = 0;
	static UINT32 force_skip_flag = 0;

#ifdef PE_D3D_KANGSIK_YOON_TEST // Added by won.hur 2011.12.13
	static UINT32 tb_prev_dif = 0;
	static UINT32 lr_prev_dif = 0;
#endif
	UINT32 lr_dif = 0;
	UINT32 tb_dif = 0;
	UINT32 thr3, thr4, thr6, thr7;
	UINT32 thr_const0, thr_const1, thr_const2, thr_const3;
#ifndef PE_D3D_STRICT_DECIDE
	UINT32 lr_over, tb_over, lr_avg, tb_avg;
#endif

	do {
		/* check stable state after changing out-type */
		if(prev_outtype != pCfg->out_type)
		{
			out_type_change_flag = 1;
			force_skip_flag = 0;
		}

#ifndef PE_D3D_KANGSIK_YOON_TEST
		/* out window 크기가 4:3 화면 보다 작을 경우 및 PIP 경우, auto detection 하지 않음. */
		if((pCfg->out_win_x < 1440 || pCfg->out_win_y < 768)||(pCfg->out_type==LX_PE_OUT_PIP))
		{
			if(pData->complete_flag == FALSE) break;
			pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;

			goto LABEL_DECIDE_FMT;
		}
#else
		/* out window 크기가 4:3 화면 보다 작을 경우 및 PIP 경우, auto detection 하지 않음. */
		if(pCfg->out_type==LX_PE_OUT_PIP)
		{
			pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;

			goto LABEL_DECIDE_FMT;
		}
#endif

#ifdef PE_D3D_KANGSIK_YOON_TEST
		if( (pStm->nxt_stm >= D3D_STM_HIS_RDY__LR)  && (pStm->nxt_stm <=D3D_STM_HIS_GET_LRR) )
		{
			thr_adj = pCfg->ss_ratio;
#if 0
			if(1)
			{
				static UINT32 ss_ratio_count = 0;
				if(++ss_ratio_count%10== 0 )
				{
						printk(" ********** ss_ratio = %d *********\n",  thr_adj);
					ss_ratio_count = 0;
				}
			}
#endif

		}else if( (pStm->nxt_stm >= D3D_STM_HIS_RDY__TB) && (pStm->nxt_stm <= D3D_STM_HIS_GET_TBR) )
		{
			thr_adj = pCfg->tb_ratio;
#if 0
			if(1)
			{
				static UINT32 tb_ratio_count = 0;
				if(++tb_ratio_count%10== 0 )
				{
						printk(" ********** tb_ratio = %d *********\n",  thr_adj);
					tb_ratio_count = 0;
				}
			}
#endif
		}

		if(pStm->win_pos == PE_WIN_LRTB_FULL)
		{
			tmp_thr3   = (pThr->fmt_th3 * thr_adj)>>10;
			tmp_thr4   = (pThr->fmt_th4 * thr_adj)>>10;
			tmp_thr6   = (pThr->fmt_th6 * thr_adj)>>10;
			tmp_thr7   = (pThr->fmt_th7 * thr_adj)>>10;
			tmp_thr_const0 = (2000 * thr_adj)>>10;
			tmp_thr_const1 = (5000 * thr_adj)>>10;
			tmp_thr_const2 = (200 * thr_adj)>>10;
			tmp_thr_const3 = (70 * thr_adj)>>10;

//				printk(" **********(PE_WIN_LRTB_FULL) tmp_thr3 = %d, tmp_thr4 = %d, tmp_thr6 = %d, tmp_thr7 = %d *********\n",  tmp_thr3, tmp_thr4, tmp_thr6, tmp_thr7);
//				printk(" **********(PE_WIN_LRTB_FULL) tmp_thr_const0 = %d, tmp_thr_const1 = %d, tmp_thr_const2 = %d, tmp_thr_const3 = %d*********\n",  tmp_thr_const0, tmp_thr_const1, tmp_thr_const2, tmp_thr_const3);
		}
		else if(pStm->win_pos == PE_WIN_LRTB_HAF1 || \
				pStm->win_pos == PE_WIN_LRTB_HAF2 || \
				pStm->win_pos == PE_WIN_MAX)
		{
			tmp_thr3   = ( (pThr->fmt_th3 * thr_adj) >>1)>>10;
			tmp_thr4   = ( (pThr->fmt_th4 * thr_adj) >>1)>>10;
			tmp_thr6   = ( (pThr->fmt_th6 * thr_adj) >>1)>>10;
			tmp_thr7   = ( (pThr->fmt_th7 * thr_adj) >>1)>>10;
			tmp_thr_const0 = ( (2000 * thr_adj) >>1)>>10;
			tmp_thr_const1 = ( (5000 * thr_adj) >>1)>>10;
			tmp_thr_const2 = ( (200 * thr_adj) >>1)>>10;
			tmp_thr_const3 = ( (70 * thr_adj) >>1)>>10;

//				printk(" **********(PE_WIN_LRTB_HAF1) tmp_thr3 = %d, tmp_thr4 = %d, tmp_thr6 = %d, tmp_thr7 = %d *********\n",  tmp_thr3, tmp_thr4, tmp_thr6, tmp_thr7);
//				printk(" **********(PE_WIN_LRTB_HAF1) tmp_thr_const0 = %d, tmp_thr_const1 = %d, tmp_thr_const2 = %d, tmp_thr_const3 = %d*********\n",  tmp_thr_const0, tmp_thr_const1, tmp_thr_const2, tmp_thr_const3);
		}
#endif

		if(pCfg->out_type == LX_PE_OUT_2D)
		{
			if(pData->complete_flag == FALSE) break;

			if(pCfg->sel_alg == 0)
			{
				if(pData->tpd > pThr->tpd_thr)
				{
					pCfg->tpd_flag = TRUE;
#ifdef PE_D3D_KANGSIK_YOON_TEST		// Added by won.hur 2011.12.13
					PE_MSG(" MSG from W.H[0-1] : PE is going UNKNOWN status!\n");
					pCfg->tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
#else
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
#endif
					goto LABEL_DECIDE_FMT;
				}
				else
				{
					pCfg->tpd_flag = FALSE;
					pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_3D;
				}

				PE_D3D_GetMax3(&pData->cb, &pData->cc, &pData->ll, &max_pd);

				if(max_pd >= pThr->ptn_thr)
				{
#ifdef PE_D3D_KANGSIK_YOON_TEST
					if(max_pd == pData->cb)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					else if(max_pd == pData->cc)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					else if(max_pd == pData->ll)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
#else
					if(max_pd == pData->cb)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_CB;
					else if(max_pd == pData->cc)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_CC;
					else if(max_pd == pData->ll)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_LL;
#endif
					goto LABEL_DECIDE_FMT;
				}
				else
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				}

				if(pData->motion_l < pThr->mtn_thr_2d)
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					PE_MSG("@1@ ");
					goto LABEL_DECIDE_FMT;
				}
			}
			else if(pCfg->sel_alg == 1)	// 20111020 개선 알고리즘
			{
				if(pData->tpd > pThr->tpd_thr)
				{
					if(pData->motion_l < pThr->mtn_thr_2d || pData->motion_l == 255)// 움직임이 없는 테스트 패텬 영상 || PC 화면인 경우 (TNR off 444 영상에서. 동영상은 제외)  -> (dqms : 1110-08276, 1110-09207, 1110-09326, 1110-09998)
					{
						pCfg->tpd_flag = TRUE;
#ifdef PE_D3D_KANGSIK_YOON_TEST		// Added by won.hur 2011.12.13
						PE_MSG(" MSG from W.H[0-2] : PE is going UNKNOWN status!\n");
						pCfg->tmp_fmt = LX_PE_D3D_FMT_UNKNOWN;
#else
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
#endif
						goto LABEL_DECIDE_FMT;
					}
					else // 움직임이 있는 태스트 패턴 영상  (BD 3D 테스트 타이틀 - 그래픽 영상 )
					{
						// go to next step
					}
				}
				else // 일반적인 자연 화면
				{
					if(0)//pData->hist_max_bin_num < 3 && pData->hist_max_bin_val > pThr->mbv_thr)	// 전체화면이 어두운 경우, 3D를 판별할 수 없음 -> (dqms : 1110-09939, 1110-11665)
					{
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;	// Histogram 값은 밝기(Luminance)에 대해서만 적용되므로  어두운 배경의 화면은 detection 하지 못함.
						goto LABEL_DECIDE_FMT;
					}
					// go to next step
				}
				pCfg->tpd_flag = FALSE;

				PE_D3D_GetMax3(&pData->cb, &pData->cc, &pData->ll, &max_pd);

				if(max_pd >= pThr->ptn_thr)
				{
#ifdef PE_D3D_KANGSIK_YOON_TEST
					if(max_pd == pData->cb)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					else if(max_pd == pData->cc)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					else if(max_pd == pData->ll)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
#else
					if(max_pd == pData->cb)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_CB;
					else if(max_pd == pData->cc)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_CC;
					else if(max_pd == pData->ll)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_LL;
#endif
					goto LABEL_DECIDE_FMT;
				}
				else
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				}
			}

#ifdef PE_D3D_KANGSIK_YOON_TEST
			lr_dif = pData->lr_diff;
			tb_dif = pData->tb_diff;
			thr3   = tmp_thr3;
			thr4   = tmp_thr4;
			thr6   = tmp_thr6;
			thr7   = tmp_thr7;
			thr_const0 = tmp_thr_const0;
			thr_const1 = tmp_thr_const1;
			thr_const2 = tmp_thr_const2;
			thr_const3 = tmp_thr_const3;
#else
			if(pStm->win_pos == PE_WIN_LRTB_FULL)
			{
				lr_dif = pData->lr_diff;
				tb_dif = pData->tb_diff;
				thr3   = pThr->fmt_th3;
				thr4   = pThr->fmt_th4;
				thr6   = pThr->fmt_th6;
				thr7   = pThr->fmt_th7;
				thr_const0 = 2000;
				thr_const1 = 5000;
				thr_const2 = 200;
				thr_const3 = 70;
			}
			else if(pStm->win_pos == PE_WIN_LRTB_HAF1 || \
					pStm->win_pos == PE_WIN_LRTB_HAF2 || \
					pStm->win_pos == PE_WIN_MAX)
			{
				lr_dif = pData->lr_diff;
				tb_dif = pData->tb_diff;
				thr3   = pThr->fmt_th3 / PE_D3D_WIN_RATIO;
				thr4   = pThr->fmt_th4 / PE_D3D_WIN_RATIO;
				thr6   = pThr->fmt_th6 / PE_D3D_WIN_RATIO;
				thr7   = pThr->fmt_th7 / PE_D3D_WIN_RATIO;
				thr_const0 = 2000 / PE_D3D_WIN_RATIO;
				thr_const1 = 5000 / PE_D3D_WIN_RATIO;
				thr_const2 = 200 / PE_D3D_WIN_RATIO;
				thr_const3 = 10;
			}
#endif

			// Histogram diff measure
			if((lr_dif >= thr3 && tb_dif >= thr3) \
					|| (lr_dif < thr3 && tb_dif < thr3))
			{
				pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				PE_MSG("@2@ ");
			}
			else
			{
				if(abs(lr_dif - tb_dif) < thr4)
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					PE_MSG("@3@ ");
				}
				else
				{
					if(lr_dif >= tb_dif)
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_TB;
					else
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_SS;
					PE_MSG("@4@ ");
				}
			}

			if (pCfg->tmp_fmt == LX_PE_D3D_FMT_2D_2D)
			{
				PE_MSG("@5@ ");
				if(lr_dif > tb_dif)
				{
					if(tb_dif > thr7)
						goto LABEL_DECIDE_FMT;
					else if(tb_dif < thr_const0)		// 3D 그래픽 테스트 영상인 경우
					{
						PE_MSG("@W1@ ");
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_TB;
						goto LABEL_DECIDE_FMT;
					}
				}
				else
				{
					if(lr_dif > thr7)
						goto LABEL_DECIDE_FMT;
					else if(lr_dif < thr_const0)		// 3D 그래픽 테스트 영상인 경우
					{
						PE_MSG("@W2@ ");
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_SS;
						goto LABEL_DECIDE_FMT;
					}
				}
			}
			else if(pCfg->tmp_fmt == LX_PE_D3D_FMT_3D_SS && lr_dif < thr6)
			{
#ifdef PE_D3D_KANGSIK_YOON_TEST 	// Added by won.hur 2011.12.13
				if(lr_prev_dif >= thr6)
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					PE_MSG("@W3_1@ ");
				}
				else
				{
					PE_MSG("@W3_2@ ");
				}
#endif
				if(tb_dif > D3D_MAX_HISTOGRAM_ON_CASE3)
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					PE_MSG("@W3_3 ");
				}

				PE_MSG("@6@ ");
				goto LABEL_DECIDE_FMT;
			}
			else if(pCfg->tmp_fmt == LX_PE_D3D_FMT_3D_TB && tb_dif < thr6)
			{


#ifdef PE_D3D_KANGSIK_YOON_TEST 	// Added by won.hur 2011.12.13
				if(tb_prev_dif >= thr6)
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					PE_MSG("@W4_1@ ");
				}
				else
				{
					PE_MSG("@W4_2@ ");
				}
#endif
				if(lr_dif > D3D_MAX_HISTOGRAM_ON_CASE3)
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					PE_MSG("@W4_3 ");
				}

				PE_MSG("@7@ ");
				goto LABEL_DECIDE_FMT;
			}
		#ifndef PE_D3D_STRICT_DECIDE
			ret = PE_D3D_GetCount2Over3(DIFF(pData->dist_l_g,pData->dist_r_g), DIFF(pData->dist_l_b,pData->dist_r_b), DIFF(pData->dist_l_r,pData->dist_r_r), thr_const2, &lr_over);
			ret = PE_D3D_GetCount2Over3(DIFF(pData->dist_t_g,pData->dist_b_g), DIFF(pData->dist_t_b,pData->dist_b_b), DIFF(pData->dist_t_r,pData->dist_b_r), thr_const2, &tb_over);
			lr_avg = (pData->dist_l_g + pData->dist_r_g + pData->dist_l_b + pData->dist_r_b + pData->dist_l_r + pData->dist_r_r)/6;
			tb_avg = (pData->dist_t_g + pData->dist_b_g + pData->dist_t_b + pData->dist_b_b + pData->dist_t_r + pData->dist_b_r)/6;
		#endif
			// Delta measure
			if(pCfg->tmp_fmt == LX_PE_D3D_FMT_2D_2D)
			{
				if(pData->ssr > pData->tbr)
				{
					if(pData->ssr > pThr->fmt_th2 && (lr_dif + thr_const1) < tb_dif) // 두가지 조건을 동시에 만족할 경우  - 2011/10/21
					{
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_SS;
						PE_MSG("@W5@ ");
					}
					#ifndef PE_D3D_STRICT_DECIDE
					else if(pData->ssr > pThr->fmt_th2)// && lr_dif > tb_dif)			// delta가 있지만 좌우 차이가 큰 경우
					{
						if(lr_dif < thr3 && tb_dif < thr3) // delta가 존재하면서, 좌우/위아래가 유사할 경우 -> 일단 2D로 한다
						{
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
							PE_MSG("@8@ ");
						}
						else
						{
							if(lr_over >= 2)
							{
								PE_MSG("1.SS by Histogram Distance\n");
								pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_SS;
							}
							else
								pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
						}
					}
					else // delta는 없지만, 좌우 차이가 작은 경우
					{
						if(lr_over >= 3 && lr_avg >= thr_const3) // RGB 모두가 유사하고, L/R 간 histogram distance들의 평균이 100 이상일 경우
						{
							PE_MSG("2.SS by Histogram Distance\n");
							pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_SS;
						}
						else
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					}
					#endif //#ifndef PE_D3D_STRICT_DECIDE
				}
				else if(pData->ssr < pData->tbr)
				{
					if(pData->tbr > pThr->fmt_th2 && (tb_dif + thr_const1) < lr_dif) // 두가지 조건을 동시에 만족할 경우 - 2011/10/21
					{
						pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_TB;
						PE_MSG("@W6@ ");
					}
					#ifndef PE_D3D_STRICT_DECIDE
					else if(pData->tbr > pThr->fmt_th2)// && tb_dif > lr_dif)			// delta가 있지만 위아래 차이가 큰 경우
					{
						if(lr_dif < thr3 && tb_dif < thr3) // delta가 존재하면서, 좌우/위아래가 유사할 경우 -> 일단 2D로 한다
						{
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
							PE_MSG("@9@ ");
						}
						else
						{
							if(tb_over >= 2)
							{
								PE_MSG("1.TB by Histogram Distance\n");
								pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_TB;
							}
							else
								pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
						}
					}
					else // delta는 없지만, 위아래 차이가 작은 경우
					{
						if(tb_over >= 3 && tb_avg >= thr_const3) // RGB 모두가 유사하고, T/B 간 histogram distance들의 평균이 100 이상일 경우
						{
							PE_MSG("2.TB by Histogram Distance\n");
							pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_TB;
						}
						else
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					}
					#endif //#ifndef PE_D3D_STRICT_DECIDE
				}
				PE_MSG("@A@ ");
			}
			else
			{
				if(pData->ssr > pData->tbr && lr_dif < tb_dif)
				{
					if(pData->ssr > pThr->fmt_th1)
					{
						PE_MSG("@W7@ ");
						if(pCfg->tmp_fmt != LX_PE_D3D_FMT_3D_SS)
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					}
#ifdef PE_D3D_KANGSIK_YOON_TEST 	// Added by won.hur 2011.12.19
					else if(pData->ssr - pData->tbr <= D3D_MIN_TB_SS_RATIO_THRESHOLD)
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
#endif
					#ifndef PE_D3D_STRICT_DECIDE
					else
					{
						if(lr_over >= 2 && tb_over < 2)
						{
							PE_MSG("3.SS by Histogram Distance\n");
							pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_SS;
						}
						else
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					}
					#endif //#ifndef PE_D3D_STRICT_DECIDE
					PE_MSG("@B@ ");
				}
				else if(pData->tbr > pData->ssr && tb_dif < lr_dif)
				{
					if(pData->tbr > pThr->fmt_th1)
					{
						PE_MSG("@W8@ ");
						if(pCfg->tmp_fmt != LX_PE_D3D_FMT_3D_TB)
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					}
#ifdef PE_D3D_KANGSIK_YOON_TEST 	// Added by won.hur 2011.12.19
					else if(pData->tbr - pData->ssr <= D3D_MIN_TB_SS_RATIO_THRESHOLD)
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
#endif
					#ifndef PE_D3D_STRICT_DECIDE
					else
					{
						if(tb_over >= 2 && lr_over < 2)
						{
							PE_MSG("3.TB by Histogram Distance\n");
							pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_TB;
						}
						else
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					}
					#endif //#ifndef PE_D3D_STRICT_DECIDE
					PE_MSG("@C@ ");
				}
				else
				{
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
					PE_MSG("@D@ ");
				}
			}
		}
		else if(pCfg->out_type == LX_PE_OUT_TB    || \
			    pCfg->out_type == LX_PE_OUT_SS    || \
			    pCfg->out_type == LX_PE_OUT_FS    || \
				pCfg->out_type == LX_PE_OUT_3D_2D || \
			    pCfg->out_type == LX_PE_OUT_DUAL )
		{
			if(out_type_change_flag == 1)
				out_type_change_count++;

			if(out_type_change_flag == 1 && out_type_change_count < pThr->skp_th1)
			{
				break;
			}
			else
			{
				prev_outtype = pCfg->out_type;
				out_type_change_flag  = 0;
				out_type_change_count = 0;
			}
			/* end of checking out type */

			if(temmporal_skip_count++ != pThr->skp_th2)	// per xx ticks (60Hz)
				break;
			else
				temmporal_skip_count = 0;
		#ifndef PE_D3D_STRICT_DECIDE
			lr_avg = (pData->dist_l + pData->dist_r)/2;
		#endif
			if(pData->dce_diff > pThr->fmt_th5)
			{
				if(DIFF(pData->motion_l, pData->motion_r) > 30 || DIFF(pData->spatial_l, pData->spatial_r) > 30)
					pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
				PE_MSG("#0# ");
			}
			else
			{
				ret = PE_D3D_GetDCEDelta(pData->dce_diff, &delta_avg);

				if(pData->tpd > pThr->tpd_thr)
				{
					if(0)//pData->hist_diff_sum > pThr->dfs_thr_3d)		// 움직임이 큰 경우 (temporal differrence)
					{
						pCfg->tmp_fmt = pCfg->d3d_fmt;
						goto LABEL_DECIDE_FMT;
					}
					else											// 움직임이 작으면서
					{
						if(pData->dce_diff > pThr->fmt_th10)		// LR/TB 차이가 큰 경우 (spatial differrence)
						{
							if(DIFF(pData->motion_l, pData->motion_r) > 30 || DIFF(pData->spatial_l, pData->spatial_r) > 20) // L-R/T-B 가 시간적 / 공간적으로 다를 경우 - 2011/10/21
							{
								pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
								PE_MSG("#1# ");
								goto LABEL_DECIDE_FMT;
							}
							else
							{
								PE_MSG("#2# ");
							}
						}
					}
				}
				else
				{
					if(0)//pData->dce_diff > pThr->fmt_th8)				// LR/TB 차이가 큰 경우
					{
						pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
						PE_MSG("#3# ");
					}
					else
					{
						if(DIFF(pData->motion_l, pData->motion_r) > 40 || DIFF(pData->spatial_l, pData->spatial_r) > 40) // L-R/T-B 가 시간적 / 공간적으로 다를 경우 - 2011/10/21
						{
							pCfg->tmp_fmt = LX_PE_D3D_FMT_2D_2D;
							PE_MSG("#4# ");
							goto LABEL_DECIDE_FMT;
						}

						if(pCfg->d3d_fmt == LX_PE_D3D_FMT_3D_SS)
						{
							if(pData->tbr > pThr->fmt_th9 && pData->ssr < pThr->fmt_th9)
							{
								pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_TB;
								PE_MSG("#5# ");
							}
						}
						else if(pCfg->d3d_fmt == LX_PE_D3D_FMT_3D_TB)
						{
							if(pData->ssr > pThr->fmt_th9 && pData->tbr < pThr->fmt_th9)
							{
								pCfg->tmp_fmt = LX_PE_D3D_FMT_3D_SS;
								PE_MSG("#6# ");
							}
						}
					}
				}
			}
		}
		else
		{
			pCfg->d3d_fmt = LX_PE_D3D_FMT_2D_2D;
			//PE_MSG("D3D : not supported out_type [%d]\n", pCfg->out_type);
			break;
		}

LABEL_DECIDE_FMT :
#ifdef PE_D3D_USE_LINE_DIFF_BY_SW
		if(pCfg->out_type == LX_PE_OUT_2D)
		{
//			if((pCfg->tmp_fmt == LX_PE_D3D_FMT_2D_2D) || (pCfg->tmp_fmt == LX_PE_D3D_FMT_UNKNOWN))
//			{
				if(pCfg->cap_enb)
				{
				   ret = PE_D3D_CaptureFrame();
					if (ret)
					{
						pCfg->d3d_fmt = LX_PE_D3D_FMT_2D_2D;
						break;
					}
				}
//			}
		}
#endif // #ifdef PE_D3D_USE_LINE_DIFF_BY_SW

#ifdef PE_D3D_KANGSIK_YOON_TEST 	// Added by won.hur 2011.12.13
		lr_prev_dif = lr_dif;
		tb_prev_dif = tb_dif;
#endif
		if(0)//force_skip_flag)
		{
			pThr->skp_th2 = 15;
			PE_MSG("D3D : fast decision mode.  skp_th2[%d]\n", pThr->skp_th2);
		}
		else
		{
			pThr->skp_th2 = default_thr.skp_th2;
		}

		// voting
		PE_D3D_CheckStableFormat(&valid, &pCfg->tmp_fmt);
#ifdef PE_D3D_USE_LINE_DIFF_BY_SW
		// accumulating
		PE_D3D_AccumulateFormat(&pCfg->tmp_fmt);
#endif

#ifdef PE_D3D_USE_DISPARITY
		PE_D3D_CheckDepthInfo(&depth_valid);
		if(depth_valid)
		{
			if( pCfg->d3d_fmt == pCfg->dep_fmt )
			{
				// 유지
			}
			else if(	(pCfg->d3d_fmt == LX_PE_D3D_FMT_3D_SS && pCfg->dep_fmt == LX_PE_D3D_FMT_3D_TB) ||\
						(pCfg->d3d_fmt == LX_PE_D3D_FMT_3D_TB && pCfg->dep_fmt == LX_PE_D3D_FMT_3D_SS) )
			{
				//pCfg->d3d_fmt = pCfg->tmp_fmt;	// Histogram 우선
				// 유지
			}
			else if(pCfg->d3d_fmt == LX_PE_D3D_FMT_2D_2D && pCfg->dep_fmt != LX_PE_D3D_FMT_2D_2D)
			{
				#if 1 // 수영장 scene에서 좌우 화면 밝기 차가 큰 경우 (오히려 위아래 차이가 더 적음)
				pCfg->d3d_fmt = pCfg->dep_fmt;	// Disparity 우선
				#else
				if(	(lr_dif < tb_dif && pCfg->dep_fmt == LX_PE_D3D_FMT_3D_SS) ||\
					(tb_dif < lr_dif && pCfg->dep_fmt == LX_PE_D3D_FMT_3D_TB))
					pCfg->d3d_fmt = pCfg->dep_fmt;	// Disparity 우선
				else
					pCfg->d3d_fmt = LX_PE_D3D_FMT_2D_2D;
				#endif
			}
			else
			{
				if(valid)	pCfg->d3d_fmt = pCfg->tmp_fmt;
			}
		}
#else
		if(valid)	pCfg->d3d_fmt = pCfg->tmp_fmt;
#endif

		if(1)
		{
			static UINT32 count = 0;
			if(/*++count%10== 0*/1 && pCfg->out_type == LX_PE_OUT_2D)
			{
				//PE_D3D_DumpHistogram();
				PE_D3D_DumpAllData();
				count = 0;
			}
			if(count==100)PE_D3D_DumpHistogram();
		}
	} while(0);

	return ret;
}

static int PE_D3D_DisplayResult(void)
{
	int ret = RET_OK;
	LX_DE_PE_TPG_T tpg;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;
	UINT32 i;

	do {
		for(i=LX_DE_TPG_D3D_PTN; i < LX_DE_TPG_MAX;i++)
		{
			tpg.eControl = i;
			tpg.bOnOff = 0;
			DE_REG_L9_SetPeTestPatternGen(&tpg);
		}
		switch (pCfg->d3d_fmt)
			{
			case LX_PE_D3D_FMT_2D_2D :
				tpg.eControl = LX_DE_TPG_D3D_2D;
					break;
			case LX_PE_D3D_FMT_3D_CB :
				tpg.eControl = LX_DE_TPG_D3D_CB;
					break;
			case LX_PE_D3D_FMT_3D_CC :
			case LX_PE_D3D_FMT_3D_LL :
				tpg.eControl = LX_DE_TPG_D3D_CC;
					break;
			case LX_PE_D3D_FMT_3D_SS :
				tpg.eControl = LX_DE_TPG_D3D_SS;
					break;
			case LX_PE_D3D_FMT_3D_TB :
				tpg.eControl = LX_DE_TPG_D3D_TB;
					break;
				default :
				tpg.eControl = LX_DE_TPG_D3D_2D;
				BREAK_WRONG(pCfg->d3d_fmt);
			}
#ifndef PE_D3D_USE_LINE_DIFF_BY_SW
		if(pCfg->tpd_flag == TRUE) tpg.eControl = LX_DE_TPG_D3D_PTN;
#endif

		tpg.bOnOff = (_g_d3d_trace>=LX_PE_D3D_DEC_PATTERN)?TRUE:FALSE;
		DE_REG_L9_SetPeTestPatternGen(&tpg);
	} while(0);

	return ret;
}

static int PE_D3D_DetectFormat(void)
{
	int ret = RET_OK;
	LX_PE_D3D_SETTINGS_T setting;
	PE_WIN_SETTINGS_T win_set;
	PE_CMN_SETTINGS_T cmn_set;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;

	do {
		win_set.win_id = LX_PE_WIN_MAIN;
		cmn_set.win_id = LX_PE_WIN_MAIN;
		ret = PE_WIN_GetCurWinSettings(&win_set);
		if (ret) break;
		ret = PE_CMN_GetCurCmnSettings(&cmn_set);
		if (ret) break;
		pCfg->out_type  = win_set.out_type;
		pCfg->in_type   = win_set.in_type;
		pCfg->out_win_x = win_set.act_x1 - win_set.act_x0;
		pCfg->out_win_y = win_set.act_y1 - win_set.act_y0;
		pCfg->act_x0 = win_set.act_x0;
		pCfg->act_y0 = win_set.act_y0;
		pCfg->act_x1 = win_set.act_x1;
		pCfg->act_y1 = win_set.act_y1;
		pCfg->tb_ratio = win_set.tb_ratio;
		pCfg->ss_ratio = win_set.ss_ratio;
		pCfg->mute_en= cmn_set.mute_en;
#ifdef PE_D3D_KANGSIK_YOON_TEST
		//gInputSourceChangedFlag = PE_D3D_DetectSourceChange();
#endif
		ret = PE_D3D_CollectBasicData();
		if (ret) break;
		ret = PE_D3D_GetLrcrHistogram();
		if (ret) break;
		ret = PE_D3D_GetDceHistogram();
		if (ret) break;
		if(!pCfg->enable) break;
		ret = PE_D3D_DecideFormat();
		//if (ret) break;
		ret = PE_D3D_DisplayResult();
		if (ret) break;
	} while(0);

	if (ret)
	{
		PE_PRINT("%s : leave stm\n", __F__);
		setting.enb = FALSE;
		ret = PE_D3D_SetD3D(&setting);
	}

	return ret;
}

#ifdef PE_D3D_KANGSIK_YOON_TEST
#if 0
static int PE_D3D_DetectSourceChange(void)
{
	int ret = 0;
	static UINT8  D3DResultOfDetect	  = 0;
	static UINT32 D3DDetectChangeCur  = 0;
	static UINT32 D3DDetectChangePrev = 0;
	static unsigned int D3DDetectCurTime =0;
	static unsigned int D3DDetectPrevTime =0;
	PE_D3D_CFG_T *pCfg = &d3d_info.cfg;


	D3DDetectCurTime = jiffies_to_msecs(jiffies);
	D3DDetectChangeCur = pCfg->mute_en;

	if(D3DDetectChangeCur != D3DDetectChangePrev)
	{
		D3DDetectChangePrev = D3DDetectChangeCur;
		if(D3DDetectChangeCur == 0)
		{
			D3DResultOfDetect = 1;
		    D3DDetectPrevTime = D3DDetectCurTime;
		}
	}

	if(D3DResultOfDetect == 1)
	{
		if((D3DDetectCurTime - D3DDetectPrevTime) > D3D_ADJUSTABLE_VOTING_MSEC) D3DResultOfDetect = 0;
	}

	ret = D3DResultOfDetect;

	return ret;
}
#endif
#endif
