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


/** @file pe_hst_hw_h13.c
 *
 *  driver for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	- histogram information
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.07.04
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
#include "pe_dcm_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_HST_HW_H13_SRC_APL_BM	0x000003ff
#define PE_HST_HW_H13_HIST_OP_RUN	0
#define PE_HST_HW_H13_HIST_OP_STOP	1

#define PE_HST_HW_H13_HIST_INVALID	0
#define PE_HST_HW_H13_HIST_VALID	1

#define PE_HST_HW_H13_HIST_SET_CNT	255

/* bin count(>(3840x2160=8294400)) when the histo is not available. */
#define PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE	9999999

#define PE_HST0		0
#define PE_HST1		1
#define PE_HST2		2

#define PE_RD_DONE_OFF	0
#define PE_RD_DONE_ON	1
#define PE_RD_EN_OFF	0
#define PE_RD_EN_ON		1

/* h13b0 temporally workaround for lrcr histo read error */
#define PE_HST_HW_H13B_USE_WORKAROUND_FOR_LRC_HIST_RD_ERROR

/* h13b0 check src histo y,h,s only */
#define PE_HST_HW_H13B_CHK_SRC_HIST_YHS_ONLY

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_HST_HW_H13_ERROR	printk

#define PE_HST_HW_H13_DBG_PRINT(fmt,args...)	\
	if(_g_hst_hw_h13_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
		
#define PE_HST_HW_H13_CHECK_CODE(_checker,_action,fmt,args...) \
			{if(_checker){PE_HST_HW_H13_ERROR(fmt,##args);_action;}}

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
static void PE_HST_HW_H13_PrintSrcHisto(char *str, UINT32 *data);
static void PE_HST_HW_H13_PrintHistogram(char *str, UINT32 *data);
static int PE_HST_HW_H13_ReadyToSetSrcApl(PE_HST_HW_H13_SRC_APL_CTRL_T *cur_ctrl);
static int PE_HST_HW_H13_UpdateSrcApl(PE_HST_HW_H13_SRC_APL_CTRL_T *cur_ctrl);
static int PE_HST_HW_H13_CheckSrcAplInfo(PE_TSK_H13_CFG_T *pCfg);
static void PE_HST_HW_H13_SetSrcHistoInit(void);
static void PE_HST_HW_H13_SetSrcHistoWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
static void PE_HST_HW_H13_SetSrcHistoMux(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
static void PE_HST_HW_H13_SetSrcHistoMode(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
static void PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_ID wId, UINT32 *data);
static void PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_ID wId, UINT32 sel, PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
static void PE_HST_HW_H13_UpdateSrcHisto(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
static void PE_HST_HW_H13_GetSrcHistoInfo(UINT32 sel, PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
static void PE_HST_HW_H13B_SetSrcHistoRdEnable(UINT32 rd_en);
static void PE_HST_HW_H13B_SetSrcHistoRdDone(UINT32 rd_done);
static void PE_HST_HW_H13_ReadyToSetSrcHisto(void);
static void PE_HST_HW_H13_ReleaseToSetSrcHisto(UINT32 rd_done);
#ifdef PE_HST_HW_H13B_CHK_SRC_HIST_YHS_ONLY
static void PE_HST_HW_H13_CheckSrcHistoInfoForYhsFullWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
#else
static void PE_HST_HW_H13_CheckSrcHistoInfoForHalfWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
#endif
static void PE_HST_HW_H13_CheckSrcHistoInfoForFullWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl);
static int PE_HST_HW_H13_CheckSrcHistoInfo(PE_TSK_H13_CFG_T *pCfg);
static void PE_HST_HW_H13_ReadyToSetLrcHisto(void);
static void PE_HST_HW_H13_GetLrcHistoFromReg(UINT32 hst_sel, UINT32 *l_data, UINT32 *r_data);
static void PE_HST_HW_H13_UpdateLrcHisto(PE_HST_HW_H13_LRC_HST_CTRL_T *cur_ctrl);
static void PE_HST_HW_H13_ReleaseToSetLrcHisto(void);
static void PE_HST_HW_H13_UpdateLrcCtrl(PE_TSK_H13_LRC_HST_CTRL_T *ctrl);
static void PE_HST_HW_H13_GetHistDiff(UINT32 *l_data, UINT32 *r_data, UINT32 *diff);
static void PE_HST_HW_H13_GetHistDiffFromFh(UINT32 *full, UINT32 *half, UINT32 *diff);
static void PE_HST_HW_H13_UpdateLrcInfo(PE_TSK_H13_LRC_HST_CTRL_T *ctrl);
static int PE_HST_HW_H13_CheckLrcrHistoInfo(PE_TSK_H13_CFG_T *pCfg);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_hst_hw_h13_trace=0x0;	//default should be off.
static PE_HST_HW_H13_SETTINGS_T _g_pe_hst_hw_h13_info;

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
void PE_HST_HW_H13_SetDbgPrint(UINT32 on_off)
{
	_g_hst_hw_h13_trace = on_off? 1:0;
	return;
}
/**
 * init histogram module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_HW_H13_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_H13)
		{
			PE_HST_HW_H13_DBG_PRINT("init general histo info.\n");
			memset0(_g_pe_hst_hw_h13_info);
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * print 32bin histogram and valid
 *
 * @param   *str [in] char
 * @param   *data [in] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_PrintSrcHisto(char *str, UINT32 *data)
{
	if(!str)	return;
	if(!data)	return;
	PE_HST_HW_H13_DBG_PRINT("%s (valid:%d)\n"\
		"[00] %7d [01] %7d [02] %7d [03] %7d [04] %7d [05] %7d [06] %7d [07] %7d\n"\
		"[08] %7d [09] %7d [10] %7d [11] %7d [12] %7d [13] %7d [14] %7d [15] %7d\n"\
		"[16] %7d [17] %7d [18] %7d [19] %7d [20] %7d [21] %7d [22] %7d [23] %7d\n"\
		"[24] %7d [25] %7d [26] %7d [27] %7d [28] %7d [29] %7d [30] %7d [31] %7d\n",\
		str,data[32],data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],\
		data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15],\
		data[16],data[17],data[18],data[19],data[20],data[21],data[22],data[23],\
		data[24],data[25],data[26],data[27],data[28],data[29],data[30],data[31]);
	return;
}

/**
 * print 32bin histogram
 *
 * @param   *str [in] char
 * @param   *data [in] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_PrintHistogram(char *str, UINT32 *data)
{
	if(!str)	return;
	if(!data)	return;
	PE_HST_HW_H13_DBG_PRINT("%s\n"\
		"[00] %7d [01] %7d [02] %7d [03] %7d [04] %7d [05] %7d [06] %7d [07] %7d\n"\
		"[08] %7d [09] %7d [10] %7d [11] %7d [12] %7d [13] %7d [14] %7d [15] %7d\n"\
		"[16] %7d [17] %7d [18] %7d [19] %7d [20] %7d [21] %7d [22] %7d [23] %7d\n"\
		"[24] %7d [25] %7d [26] %7d [27] %7d [28] %7d [29] %7d [30] %7d [31] %7d\n",\
		str,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],\
		data[8],data[9],data[10],data[11],data[12],data[13],data[14],data[15],\
		data[16],data[17],data[18],data[19],data[20],data[21],data[22],data[23],\
		data[24],data[25],data[26],data[27],data[28],data[29],data[30],data[31]);
	return;
}
/**
 * get histo diff
 *
 * @param   *l_data [in] UINT32
 * @param   *r_data [in] UINT32
 * @param   *diff [in/out] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_GetHistDiff(UINT32 *l_data, UINT32 *r_data, UINT32 *diff)
{
	int ret = RET_OK;
	UINT32 i,lr_diff,diff_sum;
	do{
		CHECK_KNULL(l_data);
		CHECK_KNULL(r_data);
		CHECK_KNULL(diff);
		/* protection in case of histo not available */
		if(l_data[0]==PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE || \
			r_data[0]==PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE)
		{
			*diff = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
		}
		else
		{
			diff_sum = 0;
			for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
			{
				lr_diff = (l_data[i]>r_data[i])? (l_data[i]-r_data[i]):(r_data[i]-l_data[i]);
				diff_sum += lr_diff;
			}
			*diff = diff_sum;
		}
	}while(0);
	return;
}
/**
 * get histo diff from full and half images
 *
 * @param   *full [in] UINT32
 * @param   *half [in] UINT32
 * @param   *diff [in/out] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_GetHistDiffFromFh(UINT32 *full, UINT32 *half, UINT32 *diff)
{
	int ret = RET_OK;
	UINT32 i,half_2x,lr_diff,diff_sum;
	do{
		CHECK_KNULL(full);
		CHECK_KNULL(half);
		CHECK_KNULL(diff);
		/* protection in case of histo not available */
		if(full[0]==PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE || \
			half[0]==PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE)
		{
			*diff = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
		}
		else
		{
			diff_sum = 0;
			for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
			{
				half_2x = half[i]<<1;
				lr_diff = (full[i]>half_2x)? (full[i]-half_2x):(half_2x-full[i]);
				diff_sum += lr_diff;
			}
			*diff = diff_sum;
		}
	}while(0);
	return;
}
/**
 * ready to set src apl
 *
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_APL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HST_HW_H13_ReadyToSetSrcApl(PE_HST_HW_H13_SRC_APL_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	UINT32 cur_mux_sel=0x0,op_md;
	UINT32 h_ofst,v_ofst,cur_x0,cur_y0,cur_x1,cur_y1;
	PE_HST_HW_H13_SRC_APL_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_apl.ctrl;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			/* set src apl L window */
			if(pre_ctrl->h_size[LX_PE_WIN_0] != cur_ctrl->h_size[LX_PE_WIN_0] || \
				pre_ctrl->v_size[LX_PE_WIN_0] != cur_ctrl->v_size[LX_PE_WIN_0])
			{
				h_ofst = cur_ctrl->h_size[LX_PE_WIN_0]>>4;	// 1/16=6.25%
				v_ofst = cur_ctrl->v_size[LX_PE_WIN_0]>>4;	// 1/16=6.25%
				cur_x0 = h_ofst;
				cur_y0 = v_ofst;
				cur_x1 = cur_ctrl->h_size[LX_PE_WIN_0]-h_ofst;
				cur_y1 = cur_ctrl->v_size[LX_PE_WIN_0]-v_ofst;
				PE_P0L_H13B0_RdFL(p0l_bbd_ctrl_01);
				PE_P0L_H13B0_Wr01(p0l_bbd_ctrl_01, x0,	cur_x0);
				PE_P0L_H13B0_Wr01(p0l_bbd_ctrl_01, y0,	cur_y0);
				PE_P0L_H13B0_WrFL(p0l_bbd_ctrl_01);
				PE_P0L_H13B0_RdFL(p0l_bbd_ctrl_02);
				PE_P0L_H13B0_Wr01(p0l_bbd_ctrl_02, x1,	cur_x1);
				PE_P0L_H13B0_Wr01(p0l_bbd_ctrl_02, y1,	cur_y1);
				PE_P0L_H13B0_WrFL(p0l_bbd_ctrl_02);
				pre_ctrl->h_size[LX_PE_WIN_0] = cur_ctrl->h_size[LX_PE_WIN_0];
				pre_ctrl->v_size[LX_PE_WIN_0] = cur_ctrl->v_size[LX_PE_WIN_0];
			}
			/* set src apl R window */
			if(pre_ctrl->h_size[LX_PE_WIN_1] != cur_ctrl->h_size[LX_PE_WIN_1] || \
				pre_ctrl->v_size[LX_PE_WIN_1] != cur_ctrl->v_size[LX_PE_WIN_1])
			{
				h_ofst = cur_ctrl->h_size[LX_PE_WIN_1]>>4;	// 1/16=6.25%
				v_ofst = cur_ctrl->v_size[LX_PE_WIN_1]>>4;	// 1/16=6.25%
				cur_x0 = h_ofst;
				cur_y0 = v_ofst;
				cur_x1 = cur_ctrl->h_size[LX_PE_WIN_1]-h_ofst;
				cur_y1 = cur_ctrl->v_size[LX_PE_WIN_1]-v_ofst;
				PE_P0R_H13B0_RdFL(p0r_bbd_ctrl_01);
				PE_P0R_H13B0_Wr01(p0r_bbd_ctrl_01, x0,	cur_x0);
				PE_P0R_H13B0_Wr01(p0r_bbd_ctrl_01, y0,	cur_y0);
				PE_P0R_H13B0_WrFL(p0r_bbd_ctrl_01);
				PE_P0R_H13B0_RdFL(p0r_bbd_ctrl_02);
				PE_P0R_H13B0_Wr01(p0r_bbd_ctrl_02, x1,	cur_x1);
				PE_P0R_H13B0_Wr01(p0r_bbd_ctrl_02, y1,	cur_y1);
				PE_P0R_H13B0_WrFL(p0r_bbd_ctrl_02);
				pre_ctrl->h_size[LX_PE_WIN_1] = cur_ctrl->h_size[LX_PE_WIN_1];
				pre_ctrl->v_size[LX_PE_WIN_1] = cur_ctrl->v_size[LX_PE_WIN_1];
			}
			/* set src apl mux selection */
			switch(cur_ctrl->apl_sel)
			{
				case PE_HST_HW_H13_SRC_APL_SEL_YUV0:
					cur_mux_sel = 0x0;	//YCbCr
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_GBR0:
					cur_mux_sel = 0x1;	//GBR
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_HSV0:
					cur_mux_sel = 0x2;	//HSV
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_INIT:
				case PE_HST_HW_H13_SRC_APL_SEL_BBD0:
				default:
					cur_mux_sel = 0x0;	//YCbCr
					op_md = (cur_ctrl->apl_sel==PE_HST_HW_H13_SRC_APL_SEL_BBD0)? 0x0:0x1;
					/* pe0 L bbd init */
					PE_P0L_H13B0_RdFL(p0l_bbd_ctrl_00);
					PE_P0L_H13B0_Wr01(p0l_bbd_ctrl_00, reg_bbd_en,	0x1);
					PE_P0L_H13B0_Wr01(p0l_bbd_ctrl_00, reg_op_mode,	op_md);	//0:auto,1:manual
					PE_P0L_H13B0_WrFL(p0l_bbd_ctrl_00);
					/* pe0 R bbd init */
					PE_P0R_H13B0_RdFL(p0r_bbd_ctrl_00);
					PE_P0R_H13B0_Wr01(p0r_bbd_ctrl_00, reg_bbd_en,	0x1);
					PE_P0R_H13B0_Wr01(p0r_bbd_ctrl_00, reg_op_mode,	op_md);	//0:auto,1:manual
					PE_P0R_H13B0_WrFL(p0r_bbd_ctrl_00);
					break;
			}
			if(pre_ctrl->mux_sel != cur_mux_sel)
			{
				PE_P0L_H13B0_RdFL(p0l_bbd_ctrl_00);
				PE_P0L_H13B0_Wr01(p0l_bbd_ctrl_00, reg_apl_mux,	cur_mux_sel);
				PE_P0L_H13B0_WrFL(p0l_bbd_ctrl_00);
				PE_P0R_H13B0_RdFL(p0r_bbd_ctrl_00);
				PE_P0R_H13B0_Wr01(p0r_bbd_ctrl_00, reg_apl_mux,	cur_mux_sel);
				PE_P0R_H13B0_WrFL(p0r_bbd_ctrl_00);
				pre_ctrl->mux_sel = cur_mux_sel;
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			/* set src apl L window */
			if(pre_ctrl->h_size[LX_PE_WIN_0] != cur_ctrl->h_size[LX_PE_WIN_0] || \
				pre_ctrl->v_size[LX_PE_WIN_0] != cur_ctrl->v_size[LX_PE_WIN_0])
			{
				h_ofst = cur_ctrl->h_size[LX_PE_WIN_0]>>4;	// 1/16=6.25%
				v_ofst = cur_ctrl->v_size[LX_PE_WIN_0]>>4;	// 1/16=6.25%
				cur_x0 = h_ofst;
				cur_y0 = v_ofst;
				cur_x1 = cur_ctrl->h_size[LX_PE_WIN_0]-h_ofst;
				cur_y1 = cur_ctrl->v_size[LX_PE_WIN_0]-v_ofst;
				PE_P0L_H13_RdFL(p0l_bbd_ctrl_01);
				PE_P0L_H13_Wr01(p0l_bbd_ctrl_01, x0,	cur_x0);
				PE_P0L_H13_Wr01(p0l_bbd_ctrl_01, y0,	cur_y0);
				PE_P0L_H13_WrFL(p0l_bbd_ctrl_01);
				PE_P0L_H13_RdFL(p0l_bbd_ctrl_02);
				PE_P0L_H13_Wr01(p0l_bbd_ctrl_02, x1,	cur_x1);
				PE_P0L_H13_Wr01(p0l_bbd_ctrl_02, y1,	cur_y1);
				PE_P0L_H13_WrFL(p0l_bbd_ctrl_02);
				pre_ctrl->h_size[LX_PE_WIN_0] = cur_ctrl->h_size[LX_PE_WIN_0];
				pre_ctrl->v_size[LX_PE_WIN_0] = cur_ctrl->v_size[LX_PE_WIN_0];
			}
			/* set src apl R window */
			if(pre_ctrl->h_size[LX_PE_WIN_1] != cur_ctrl->h_size[LX_PE_WIN_1] || \
				pre_ctrl->v_size[LX_PE_WIN_1] != cur_ctrl->v_size[LX_PE_WIN_1])
			{
				h_ofst = cur_ctrl->h_size[LX_PE_WIN_1]>>4;	// 1/16=6.25%
				v_ofst = cur_ctrl->v_size[LX_PE_WIN_1]>>4;	// 1/16=6.25%
				cur_x0 = h_ofst;
				cur_y0 = v_ofst;
				cur_x1 = cur_ctrl->h_size[LX_PE_WIN_1]-h_ofst;
				cur_y1 = cur_ctrl->v_size[LX_PE_WIN_1]-v_ofst;
				PE_P0R_H13_RdFL(p0r_bbd_ctrl_01);
				PE_P0R_H13_Wr01(p0r_bbd_ctrl_01, x0,	cur_x0);
				PE_P0R_H13_Wr01(p0r_bbd_ctrl_01, y0,	cur_y0);
				PE_P0R_H13_WrFL(p0r_bbd_ctrl_01);
				PE_P0R_H13_RdFL(p0r_bbd_ctrl_02);
				PE_P0R_H13_Wr01(p0r_bbd_ctrl_02, x1,	cur_x1);
				PE_P0R_H13_Wr01(p0r_bbd_ctrl_02, y1,	cur_y1);
				PE_P0R_H13_WrFL(p0r_bbd_ctrl_02);
				pre_ctrl->h_size[LX_PE_WIN_1] = cur_ctrl->h_size[LX_PE_WIN_1];
				pre_ctrl->v_size[LX_PE_WIN_1] = cur_ctrl->v_size[LX_PE_WIN_1];
			}
			/* set src apl mux selection */
			switch(cur_ctrl->apl_sel)
			{
				case PE_HST_HW_H13_SRC_APL_SEL_YUV0:
					cur_mux_sel = 0x0;	//Y
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_HSV0:
					cur_mux_sel = 0x1;	//S
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_GBR0:
					cur_mux_sel = 0x2;	//G
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_GBR1:
					cur_mux_sel = 0x3;	//B
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_GBR2:
					cur_mux_sel = 0x4;	//R
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_INIT:
				default:
					cur_mux_sel = 0x0;	//Y
					/* pe0 L bbd init */
					PE_P0L_H13_RdFL(p0l_bbd_ctrl_00);
					PE_P0L_H13_Wr01(p0l_bbd_ctrl_00, reg_bbd_en,	0x1);
					PE_P0L_H13_Wr01(p0l_bbd_ctrl_00, reg_op_mode,	0x1);	//0:auto,1:manual
					PE_P0L_H13_WrFL(p0l_bbd_ctrl_00);
					/* pe0 R bbd init */
					PE_P0R_H13_RdFL(p0r_bbd_ctrl_00);
					PE_P0R_H13_Wr01(p0r_bbd_ctrl_00, reg_bbd_en,	0x1);
					PE_P0R_H13_Wr01(p0r_bbd_ctrl_00, reg_op_mode,	0x1);	//0:auto,1:manual
					PE_P0R_H13_WrFL(p0r_bbd_ctrl_00);
					break;
			}
			if(pre_ctrl->mux_sel != cur_mux_sel)
			{
				PE_P0L_H13_RdFL(p0l_bbd_ctrl_00);
				PE_P0L_H13_Wr01(p0l_bbd_ctrl_00, reg_apl_mux,	cur_mux_sel);
				PE_P0L_H13_WrFL(p0l_bbd_ctrl_00);
				PE_P0R_H13_RdFL(p0r_bbd_ctrl_00);
				PE_P0R_H13_Wr01(p0r_bbd_ctrl_00, reg_apl_mux,	cur_mux_sel);
				PE_P0R_H13_WrFL(p0r_bbd_ctrl_00);
				pre_ctrl->mux_sel = cur_mux_sel;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * update src apl
 *
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_APL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HST_HW_H13_UpdateSrcApl(PE_HST_HW_H13_SRC_APL_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	UINT32 temp,r_data[LX_PE_WIN_NUM][2],bit_shift;
	PE_HST_HW_H13_SRC_APL_DATA_T *apl_data = &_g_pe_hst_hw_h13_info.src_apl.data;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			if(cur_ctrl->apl_sel==PE_HST_HW_H13_SRC_APL_SEL_BBD0)
			{
				/* get bbd x,y coordinate */
				PE_P0L_H13_RdFL(p0l_bbd_stat_00);
				PE_P0L_H13_RdFL(p0l_bbd_stat_01);
				PE_P0R_H13_RdFL(p0r_bbd_stat_00);
				PE_P0R_H13_RdFL(p0r_bbd_stat_01);
				r_data[LX_PE_WIN_0][0] = PE_P0L_H13_Rd(p0l_bbd_stat_00);
				r_data[LX_PE_WIN_0][1] = PE_P0L_H13_Rd(p0l_bbd_stat_01);
				r_data[LX_PE_WIN_1][0] = PE_P0R_H13_Rd(p0r_bbd_stat_00);
				r_data[LX_PE_WIN_1][1] = PE_P0R_H13_Rd(p0r_bbd_stat_01);
				if(apl_data->bb0[LX_PE_WIN_0] != r_data[LX_PE_WIN_0][0])
				{
					PE_BVE_H13_RdFL(bbd_stat_00);
					PE_BVE_H13_Wr(bbd_stat_00,	r_data[LX_PE_WIN_0][0]);
					PE_BVE_H13_WrFL(bbd_stat_00);
					apl_data->bb0[LX_PE_WIN_0] = r_data[LX_PE_WIN_0][0];
				}
				if(apl_data->bb1[LX_PE_WIN_0] != r_data[LX_PE_WIN_0][1])
				{
					PE_BVE_H13_RdFL(bbd_stat_01);
					PE_BVE_H13_Wr(bbd_stat_01,	r_data[LX_PE_WIN_0][1]);
					PE_BVE_H13_WrFL(bbd_stat_01);
					apl_data->bb1[LX_PE_WIN_0] = r_data[LX_PE_WIN_0][1];
				}
				if(apl_data->bb0[LX_PE_WIN_1] != r_data[LX_PE_WIN_1][0])
				{
					PE_BVE_H13_RdFL(bbd_stat_02);
					PE_BVE_H13_Wr(bbd_stat_02,	r_data[LX_PE_WIN_1][0]);
					PE_BVE_H13_WrFL(bbd_stat_02);
					apl_data->bb0[LX_PE_WIN_1] = r_data[LX_PE_WIN_1][0];
				}
				if(apl_data->bb1[LX_PE_WIN_1] != r_data[LX_PE_WIN_1][1])
				{
					PE_BVE_H13_RdFL(bbd_stat_03);
					PE_BVE_H13_Wr(bbd_stat_03,	r_data[LX_PE_WIN_1][1]);
					PE_BVE_H13_WrFL(bbd_stat_03);
					apl_data->bb1[LX_PE_WIN_1] = r_data[LX_PE_WIN_1][1];
				}
			}
			else
			{
				/* get src apl */
				PE_P0L_H13B0_RdFL(p0l_apl_stat_00);
				r_data[LX_PE_WIN_0][0] = PE_P0L_H13B0_Rd(p0l_apl_stat_00);
				PE_P0R_H13B0_RdFL(p0r_apl_stat_00);
				r_data[LX_PE_WIN_1][0] = PE_P0R_H13B0_Rd(p0r_apl_stat_00);
				switch(cur_ctrl->apl_sel)
				{
					case PE_HST_HW_H13_SRC_APL_SEL_GBR0:
						apl_data->gbr[LX_PE_WIN_0] = r_data[LX_PE_WIN_0][0];
						apl_data->gbr[LX_PE_WIN_1] = r_data[LX_PE_WIN_1][0];
						break;
					case PE_HST_HW_H13_SRC_APL_SEL_HSV0:
						apl_data->hsv[LX_PE_WIN_0] = r_data[LX_PE_WIN_0][0];
						apl_data->hsv[LX_PE_WIN_1] = r_data[LX_PE_WIN_1][0];
						PE_P1L_H13B0_RdFL(pe1_wb_ctrl_00);
						PE_P1L_H13B0_Wr01(pe1_wb_ctrl_00, reg_s_apl_0,	GET_BITS(r_data[LX_PE_WIN_0][0],12,8));
						PE_P1L_H13B0_WrFL(pe1_wb_ctrl_00);
						break;
					case PE_HST_HW_H13_SRC_APL_SEL_YUV0:
					case PE_HST_HW_H13_SRC_APL_SEL_INIT:
					default:
						apl_data->yuv[LX_PE_WIN_0] = r_data[LX_PE_WIN_0][0];
						apl_data->yuv[LX_PE_WIN_1] = r_data[LX_PE_WIN_1][0];
						break;
				}
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			/* get src apl */
			PE_P0L_H13_RdFL(p0l_apl_stat_00);
			r_data[LX_PE_WIN_0][0] = PE_P0L_H13_Rd(p0l_apl_stat_00);
			r_data[LX_PE_WIN_0][0] = GET_BITS(r_data[LX_PE_WIN_0][0], 0, 10);
			PE_P0R_H13_RdFL(p0r_apl_stat_00);
			r_data[LX_PE_WIN_1][0] = PE_P0R_H13_Rd(p0r_apl_stat_00);
			r_data[LX_PE_WIN_1][0] = GET_BITS(r_data[LX_PE_WIN_1][0], 0, 10);
			switch(cur_ctrl->apl_sel)
			{
				case PE_HST_HW_H13_SRC_APL_SEL_GBR0:
					bit_shift = 0;	//G
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_GBR1:
					bit_shift = 10;	//B
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_GBR2:
					bit_shift = 20;	//R
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_HSV0:
					bit_shift = 10;	//S
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_YUV0:
				case PE_HST_HW_H13_SRC_APL_SEL_INIT:
				default:
					bit_shift = 0;	//Y
					break;
			}
			switch(cur_ctrl->apl_sel)
			{
				case PE_HST_HW_H13_SRC_APL_SEL_GBR0:
				case PE_HST_HW_H13_SRC_APL_SEL_GBR1:
				case PE_HST_HW_H13_SRC_APL_SEL_GBR2:
					r_data[LX_PE_WIN_0][0] = r_data[LX_PE_WIN_0][0]<<bit_shift;
					temp = apl_data->gbr[LX_PE_WIN_0]&(~(PE_HST_HW_H13_SRC_APL_BM<<bit_shift));
					apl_data->gbr[LX_PE_WIN_0] = (temp)|(r_data[LX_PE_WIN_0][0]);
					r_data[LX_PE_WIN_1][0] = r_data[LX_PE_WIN_1][0]<<bit_shift;
					temp = apl_data->gbr[LX_PE_WIN_1]&(~(PE_HST_HW_H13_SRC_APL_BM<<bit_shift));
					apl_data->gbr[LX_PE_WIN_1] = (temp)|(r_data[LX_PE_WIN_1][0]);
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_HSV0:
					r_data[LX_PE_WIN_0][0] = r_data[LX_PE_WIN_0][0]<<bit_shift;
					temp = apl_data->hsv[LX_PE_WIN_0]&(~(PE_HST_HW_H13_SRC_APL_BM<<bit_shift));
					apl_data->hsv[LX_PE_WIN_0] = (temp)|(r_data[LX_PE_WIN_0][0]);
					r_data[LX_PE_WIN_1][0] = r_data[LX_PE_WIN_1][0]<<bit_shift;
					temp = apl_data->hsv[LX_PE_WIN_1]&(~(PE_HST_HW_H13_SRC_APL_BM<<bit_shift));
					apl_data->hsv[LX_PE_WIN_1] = (temp)|(r_data[LX_PE_WIN_1][0]);
					break;
				case PE_HST_HW_H13_SRC_APL_SEL_YUV0:
				case PE_HST_HW_H13_SRC_APL_SEL_INIT:
				default:
					r_data[LX_PE_WIN_0][0] = r_data[LX_PE_WIN_0][0]<<bit_shift;
					temp = apl_data->yuv[LX_PE_WIN_0]&(~(PE_HST_HW_H13_SRC_APL_BM<<bit_shift));
					apl_data->yuv[LX_PE_WIN_0] = (temp)|(r_data[LX_PE_WIN_0][0]);
					r_data[LX_PE_WIN_1][0] = r_data[LX_PE_WIN_1][0]<<bit_shift;
					temp = apl_data->yuv[LX_PE_WIN_1]&(~(PE_HST_HW_H13_SRC_APL_BM<<bit_shift));
					apl_data->yuv[LX_PE_WIN_1] = (temp)|(r_data[LX_PE_WIN_1][0]);
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * check src apl info
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HST_HW_H13_CheckSrcAplInfo(PE_TSK_H13_CFG_T *pCfg)
{
	int ret = RET_OK;
	PE_HST_HW_H13_SRC_APL_CTRL_T cur_ctrl;
	PE_INF_H13_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_H13_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_HST_HW_H13_STATE_T *apl_state = &_g_pe_hst_hw_h13_info.src_apl.state;
	LX_PE_DCM_HISTO_OPR_T *hist_opr = &_g_pe_hst_hw_h13_info.cfg[LX_PE_WIN_0].opr;
	PE_HST_HW_H13_SRC_APL_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_apl.ctrl;
	do {
		CHECK_KNULL(pCfg);
		if(((ctrl0_info->pe0_src_h==0||ctrl0_info->pe0_src_v==0)&& \
			(ctrl1_info->pe0_src_h==0||ctrl1_info->pe0_src_v==0)) || \
			hist_opr->src_apl_op==PE_HST_HW_H13_HIST_OP_STOP)
		{
			apl_state->next = PE_HST_HW_H13_SRC_APL_STM_ALL_INIT;
			break;
		}
		/* update the cur_ctrl because it is a local variable */
		cur_ctrl.h_size[LX_PE_WIN_0] = ctrl0_info->pe0_src_h;
		cur_ctrl.v_size[LX_PE_WIN_0] = ctrl0_info->pe0_src_v;
		cur_ctrl.h_size[LX_PE_WIN_1] = ctrl1_info->pe0_src_h;
		cur_ctrl.v_size[LX_PE_WIN_1] = ctrl1_info->pe0_src_v;
		cur_ctrl.apl_sel = pre_ctrl->apl_sel;
		apl_state->curr = apl_state->next;
		if(PE_KDRV_VER_H13BX)
		{
			switch(apl_state->curr)
			{
				case PE_HST_HW_H13_SRC_APL_STM_ALL_INIT:
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_INIT;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_YUV_RDY0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_YUV_RDY0:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_YUV_GET0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_YUV_GET0:
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_YUV0;
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_HSV0;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_HSV_RDY0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_HSV_RDY0:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_HSV_GET0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_HSV_GET0:
					/*cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_HSV0;*/
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR0;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_RDY0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_RDY0:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_GET0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_GET0:
					/*cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR0;*/
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_BBD0;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_BBD_RDY0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_BBD_RDY0:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_BBD_GET0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_BBD_GET0:
					/*cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_BBD0;*/
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_YUV0;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_YUV_RDY0;
					break;
				default:
					PE_HST_HW_H13_DBG_PRINT("apl_state->curr:%d, wrong type.\n",apl_state->curr);
					break;
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			switch(apl_state->curr)
			{
				case PE_HST_HW_H13_SRC_APL_STM_ALL_INIT:
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_INIT;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_YUV_RDY0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_YUV_RDY0:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_YUV_GET0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_YUV_GET0:
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_YUV0;
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_HSV0;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_HSV_RDY0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_HSV_RDY0:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_HSV_GET0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_HSV_GET0:
					/*cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_HSV0;*/
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR0;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_RDY0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_RDY0:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_GET0;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_GET0:
					/*cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR0;*/
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR1;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_RDY1;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_RDY1:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_GET1;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_GET1:
					/*cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR1;*/
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR2;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_RDY2;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_RDY2:
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_GBR_GET2;
					break;
				case PE_HST_HW_H13_SRC_APL_STM_GBR_GET2:
					/*cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_GBR2;*/
					ret = PE_HST_HW_H13_UpdateSrcApl(&cur_ctrl);
					if(ret)	break;
					cur_ctrl.apl_sel = PE_HST_HW_H13_SRC_APL_SEL_YUV0;
					ret = PE_HST_HW_H13_ReadyToSetSrcApl(&cur_ctrl);
					if(ret)	break;
					apl_state->next = PE_HST_HW_H13_SRC_APL_STM_YUV_RDY0;
					break;
				default:
					PE_HST_HW_H13_DBG_PRINT("apl_state->curr:%d, wrong type.\n",apl_state->curr);
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		pre_ctrl->apl_sel = cur_ctrl.apl_sel;
	}while(0);
	return ret;
}
/**
 * set src histo init
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static void PE_HST_HW_H13_SetSrcHistoInit(void)
{
	if(PE_KDRV_VER_H13BX)
	{
		/* pe0 l hist init */
		PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_01);
		PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_01, reg_wina_hen,			0x1);	//0:full, 1:manual
		PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_01, reg_wina_ven,			0x1);	//0:full, 1:manual
		PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_01);
		PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_02);
		PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_02, reg_hist_hsv_hsl_sel,	0x1);	//0:HSL, 1:HSV
		PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_02, reg_hist_vscaling_en,	0x1);	//0:HSV, 1:sHSV
		PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_02);
		PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_03);
		PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_03, reg_winb_hen,			0x1);	//0:full, 1:manual
		PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_03, reg_winb_ven,			0x1);	//0:full, 1:manual
		PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_03);
		PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
		PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl, hif_hist_address,	0x0);
		PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl, hif_hist_ai,		0x0);
		PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl, hif_hist_enable,	0x1);	//0:host,1:normal
		PE_P0L_H13B0_WrFL(p0l_tpd_hist_ai_ctrl);
		/* pe0 r hist init */
		PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_01);
		PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_01, reg_wina_hen,			0x1);	//0:full, 1:manual
		PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_01, reg_wina_ven,			0x1);	//0:full, 1:manual
		PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_01);
		PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_02);
		PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_02, reg_hist_hsv_hsl_sel,	0x1);	//0:HSL, 1:HSV
		PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_02, reg_hist_vscaling_en,	0x1);	//0:HSV, 1:sHSV
		PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_02);
		PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_03);
		PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_03, reg_winb_hen,			0x1);	//0:full, 1:manual
		PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_03, reg_winb_ven,			0x1);	//0:full, 1:manual
		PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_03);
		PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_ctrl);
		PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl, hif_hist_address,	0x0);
		PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl, hif_hist_ai,		0x0);
		PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl, hif_hist_enable,	0x1);	//0:host,1:normal
		PE_P0R_H13B0_WrFL(p0r_tpd_hist_ai_ctrl);
	}
	else if(PE_KDRV_VER_H13AX)
	{
		/* debd_pp hist init */
		PE_DPP_H13_RdFL(debd_pp_hist_ctrl_00);
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_l_ch_sel,		0x0);	//0:L data, 1:R data
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_r_ch_sel,		0x1);	//0:L data, 1:R data
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_l_data_sel,		0x8);	//sV
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_r_data_sel,		0x8);	//sV
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_rd_en,			0x0);
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, csc_l_hsv_hsl_sel,	0x1);	//0:HSL, 1:HSV
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, csc_l_vscaling_en,	0x1);	//0:HSL, 1:sHSV
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, csc_r_hsv_hsl_sel,	0x1);	//0:HSL, 1:HSV
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, csc_r_vscaling_en,	0x1);	//0:HSL, 1:sHSV
		PE_DPP_H13_WrFL(debd_pp_hist_ctrl_00);
		PE_DPP_H13_RdFL(debd_pp_hist_ctrl_01);
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_01, hist_l_window_h_en,	0x1);	//0:full, 1:manual
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_01, hist_l_window_v_en,	0x1);	//0:full, 1:manual
		PE_DPP_H13_WrFL(debd_pp_hist_ctrl_01);
		PE_DPP_H13_RdFL(debd_pp_hist_ctrl_03);
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_03, hist_r_window_h_en,	0x1);	//0:full, 1:manual
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_03, hist_r_window_v_en,	0x1);	//0:full, 1:manual
		PE_DPP_H13_WrFL(debd_pp_hist_ctrl_03);
		PE_DPP_H13_RdFL(debd_pp_l_hist_ia_ctrl);
		PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_address,	0x0);
		PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_ai,		0x0);
		PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
		PE_DPP_H13_WrFL(debd_pp_l_hist_ia_ctrl);
		PE_DPP_H13_RdFL(debd_pp_r_hist_ia_ctrl);
		PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_address,	0x0);
		PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_ai,		0x0);
		PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
		PE_DPP_H13_WrFL(debd_pp_r_hist_ia_ctrl);
	}
	else
	{
		PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
	}
	return;
}
/**
 * set src histo window
 *
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_SetSrcHistoWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	UINT32 x0[LX_PE_WIN_NUM][2],y0[LX_PE_WIN_NUM][2];
	UINT32 x1[LX_PE_WIN_NUM][2],y1[LX_PE_WIN_NUM][2];
	UINT32 sel[LX_PE_WIN_NUM][3];
	PE_HST_HW_H13_SRC_HST_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_hist.ctrl;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			switch(cur_ctrl->mod_sel)
			{
				case PE_HST_HW_H13_SRC_HST_MOD_SEL_TB:
					/* pe0 l win_a(full) */
					x0[LX_PE_WIN_0][0] = cur_ctrl->x_ofst[LX_PE_WIN_0];
					y0[LX_PE_WIN_0][0] = cur_ctrl->y_ofst[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][0] = x0[LX_PE_WIN_0][0]+cur_ctrl->h_size[LX_PE_WIN_0];
					y1[LX_PE_WIN_0][0] = y0[LX_PE_WIN_0][0]+cur_ctrl->v_size[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][0] = (x1[LX_PE_WIN_0][0]>0)? (x1[LX_PE_WIN_0][0]-1):0;
					y1[LX_PE_WIN_0][0] = (y1[LX_PE_WIN_0][0]>0)? (y1[LX_PE_WIN_0][0]-1):0;
					/* pe0 l win_b(half) */
					x0[LX_PE_WIN_0][1] = cur_ctrl->x_ofst[LX_PE_WIN_0];
					y0[LX_PE_WIN_0][1] = cur_ctrl->y_ofst[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][1] = x0[LX_PE_WIN_0][1]+cur_ctrl->h_size[LX_PE_WIN_0];
					y1[LX_PE_WIN_0][1] = y0[LX_PE_WIN_0][1]+(cur_ctrl->v_size[LX_PE_WIN_0]>>1);
					x1[LX_PE_WIN_0][1] = (x1[LX_PE_WIN_0][1]>0)? (x1[LX_PE_WIN_0][1]-1):0;
					y1[LX_PE_WIN_0][1] = (y1[LX_PE_WIN_0][1]>0)? (y1[LX_PE_WIN_0][1]-1):0;
					/* pe0 r win_a */
					x0[LX_PE_WIN_1][0] = y0[LX_PE_WIN_1][0] = 0;
					x1[LX_PE_WIN_1][0] = y1[LX_PE_WIN_1][0] = 0;
					/* pe0 r win_b */
					x0[LX_PE_WIN_1][1] = y0[LX_PE_WIN_1][1] = 0;
					x1[LX_PE_WIN_1][1] = y1[LX_PE_WIN_1][1] = 0;
					/* pe0 l win sel */
					sel[LX_PE_WIN_0][0] = 1;	//win b(half)
					sel[LX_PE_WIN_0][1] = 0;	//win a(full), a only(hw fix)
					sel[LX_PE_WIN_0][2] = 0;	//win a(full), a only(hw fix)
					/* pe0 r win sel */
					sel[LX_PE_WIN_1][0] = 0;	//not use, dont care
					sel[LX_PE_WIN_1][1] = 0;	//not use, dont care, a only(hw fix)
					sel[LX_PE_WIN_1][2] = 0;	//not use, dont care, a only(hw fix)
					break;
				case PE_HST_HW_H13_SRC_HST_MOD_SEL_SS:
					/* pe0 l win_a(full) */
					x0[LX_PE_WIN_0][0] = cur_ctrl->x_ofst[LX_PE_WIN_0];
					y0[LX_PE_WIN_0][0] = cur_ctrl->y_ofst[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][0] = x0[LX_PE_WIN_0][0]+cur_ctrl->h_size[LX_PE_WIN_0];
					y1[LX_PE_WIN_0][0] = y0[LX_PE_WIN_0][0]+cur_ctrl->v_size[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][0] = (x1[LX_PE_WIN_0][0]>0)? (x1[LX_PE_WIN_0][0]-1):0;
					y1[LX_PE_WIN_0][0] = (y1[LX_PE_WIN_0][0]>0)? (y1[LX_PE_WIN_0][0]-1):0;
					/* pe0 l win_b(half) */
					x0[LX_PE_WIN_0][1] = cur_ctrl->x_ofst[LX_PE_WIN_0];
					y0[LX_PE_WIN_0][1] = cur_ctrl->y_ofst[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][1] = x0[LX_PE_WIN_0][1]+(cur_ctrl->h_size[LX_PE_WIN_0]>>1);
					y1[LX_PE_WIN_0][1] = y0[LX_PE_WIN_0][1]+cur_ctrl->v_size[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][1] = (x1[LX_PE_WIN_0][1]>0)? (x1[LX_PE_WIN_0][1]-1):0;
					y1[LX_PE_WIN_0][1] = (y1[LX_PE_WIN_0][1]>0)? (y1[LX_PE_WIN_0][1]-1):0;
					/* pe0 r win_a */
					x0[LX_PE_WIN_1][0] = y0[LX_PE_WIN_1][0] = 0;
					x1[LX_PE_WIN_1][0] = y1[LX_PE_WIN_1][0] = 0;
					/* pe0 r win_b */
					x0[LX_PE_WIN_1][1] = y0[LX_PE_WIN_1][1] = 0;
					x1[LX_PE_WIN_1][1] = y1[LX_PE_WIN_1][1] = 0;
					/* pe0 l win sel */
					sel[LX_PE_WIN_0][0] = 1;	//win b(half)
					sel[LX_PE_WIN_0][1] = 0;	//win a(full), a only(hw fix)
					sel[LX_PE_WIN_0][2] = 0;	//win a(full), a only(hw fix)
					/* pe0 r win sel */
					sel[LX_PE_WIN_1][0] = 0;	//not use, dont care
					sel[LX_PE_WIN_1][1] = 0;	//not use, dont care, a only(hw fix)
					sel[LX_PE_WIN_1][2] = 0;	//not use, dont care, a only(hw fix)
					break;
				case PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL:
				default:
					/* pe0 l win_a(full) */
					x0[LX_PE_WIN_0][0] = cur_ctrl->x_ofst[LX_PE_WIN_0];
					y0[LX_PE_WIN_0][0] = cur_ctrl->y_ofst[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][0] = x0[LX_PE_WIN_0][0]+cur_ctrl->h_size[LX_PE_WIN_0];
					y1[LX_PE_WIN_0][0] = y0[LX_PE_WIN_0][0]+cur_ctrl->v_size[LX_PE_WIN_0];
					x1[LX_PE_WIN_0][0] = (x1[LX_PE_WIN_0][0]>0)? (x1[LX_PE_WIN_0][0]-1):0;
					y1[LX_PE_WIN_0][0] = (y1[LX_PE_WIN_0][0]>0)? (y1[LX_PE_WIN_0][0]-1):0;
					/* pe0 l win_b */
					x0[LX_PE_WIN_0][1] = y0[LX_PE_WIN_0][1] = 0;
					x1[LX_PE_WIN_0][1] = y1[LX_PE_WIN_0][1] = 0;
					/* pe0 r win_a(full) */
					x0[LX_PE_WIN_1][0] = cur_ctrl->x_ofst[LX_PE_WIN_1];
					y0[LX_PE_WIN_1][0] = cur_ctrl->y_ofst[LX_PE_WIN_1];
					x1[LX_PE_WIN_1][0] = x0[LX_PE_WIN_1][0]+cur_ctrl->h_size[LX_PE_WIN_1];
					y1[LX_PE_WIN_1][0] = y0[LX_PE_WIN_1][0]+cur_ctrl->v_size[LX_PE_WIN_1];
					x1[LX_PE_WIN_1][0] = (x1[LX_PE_WIN_1][0]>0)? (x1[LX_PE_WIN_1][0]-1):0;
					y1[LX_PE_WIN_1][0] = (y1[LX_PE_WIN_1][0]>0)? (y1[LX_PE_WIN_1][0]-1):0;
					/* pe0 r win_b */
					x0[LX_PE_WIN_1][1] = y0[LX_PE_WIN_1][1] = 0;
					x1[LX_PE_WIN_1][1] = y1[LX_PE_WIN_1][1] = 0;
					/* pe0 l win sel */
					sel[LX_PE_WIN_0][0] = 0;	//win a(full)
					sel[LX_PE_WIN_0][1] = 0;	//win a(full), a only(hw fix)
					sel[LX_PE_WIN_0][2] = 0;	//win a(full), a only(hw fix)
					/* pe0 r win sel */
					sel[LX_PE_WIN_1][0] = 0;	//win a(full)
					sel[LX_PE_WIN_1][1] = 0;	//win a(full), a only(hw fix)
					sel[LX_PE_WIN_1][2] = 0;	//win a(full), a only(hw fix)
					break;
			}
			/* set src histo window : pe0 l win_a */
			if(pre_ctrl->x0_pos[LX_PE_WIN_0][0] != x0[LX_PE_WIN_0][0] || \
				pre_ctrl->y0_pos[LX_PE_WIN_0][0] != y0[LX_PE_WIN_0][0] || \
				pre_ctrl->x1_pos[LX_PE_WIN_0][0] != x1[LX_PE_WIN_0][0] || \
				pre_ctrl->y1_pos[LX_PE_WIN_0][0] != y1[LX_PE_WIN_0][0])
			{
				PE_HST_HW_H13_DBG_PRINT("[W0A]inf:%d,%d,%d,%d, x,y:%d,%d,%d,%d to %d,%d,%d,%d\n",\
					cur_ctrl->x_ofst[LX_PE_WIN_0],cur_ctrl->y_ofst[LX_PE_WIN_0],\
					cur_ctrl->h_size[LX_PE_WIN_0],cur_ctrl->v_size[LX_PE_WIN_0],\
					pre_ctrl->x0_pos[LX_PE_WIN_0][0],pre_ctrl->y0_pos[LX_PE_WIN_0][0],\
					pre_ctrl->x1_pos[LX_PE_WIN_0][0],pre_ctrl->y1_pos[LX_PE_WIN_0][0],\
					x0[LX_PE_WIN_0][0],y0[LX_PE_WIN_0][0],x1[LX_PE_WIN_0][0],y1[LX_PE_WIN_0][0]);
				PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_01);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_01, wina_x0,	x0[LX_PE_WIN_0][0]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_01, wina_y0,	y0[LX_PE_WIN_0][0]);
				PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_01);
				PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_02);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_02, wina_x1,	x1[LX_PE_WIN_0][0]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_02, wina_y1,	y1[LX_PE_WIN_0][0]);
				PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_02);
				pre_ctrl->x0_pos[LX_PE_WIN_0][0] = x0[LX_PE_WIN_0][0];
				pre_ctrl->y0_pos[LX_PE_WIN_0][0] = y0[LX_PE_WIN_0][0];
				pre_ctrl->x1_pos[LX_PE_WIN_0][0] = x1[LX_PE_WIN_0][0];
				pre_ctrl->y1_pos[LX_PE_WIN_0][0] = y1[LX_PE_WIN_0][0];
			}
			/* set src histo window : pe0 l win_b */
			if(pre_ctrl->x0_pos[LX_PE_WIN_0][1] != x0[LX_PE_WIN_0][1] || \
				pre_ctrl->y0_pos[LX_PE_WIN_0][1] != y0[LX_PE_WIN_0][1] || \
				pre_ctrl->x1_pos[LX_PE_WIN_0][1] != x1[LX_PE_WIN_0][1] || \
				pre_ctrl->y1_pos[LX_PE_WIN_0][1] != y1[LX_PE_WIN_0][1])
			{
				PE_HST_HW_H13_DBG_PRINT("[W0B]inf:%d,%d,%d,%d, x,y:%d,%d,%d,%d to %d,%d,%d,%d\n",\
					cur_ctrl->x_ofst[LX_PE_WIN_0],cur_ctrl->y_ofst[LX_PE_WIN_0],\
					cur_ctrl->h_size[LX_PE_WIN_0],cur_ctrl->v_size[LX_PE_WIN_0],\
					pre_ctrl->x0_pos[LX_PE_WIN_0][1],pre_ctrl->y0_pos[LX_PE_WIN_0][1],\
					pre_ctrl->x1_pos[LX_PE_WIN_0][1],pre_ctrl->y1_pos[LX_PE_WIN_0][1],\
					x0[LX_PE_WIN_0][1],y0[LX_PE_WIN_0][1],x1[LX_PE_WIN_0][1],y1[LX_PE_WIN_0][1]);
				PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_03);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_03, winb_x0,	x0[LX_PE_WIN_0][1]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_03, winb_y0,	y0[LX_PE_WIN_0][1]);
				PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_03);
				PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_04);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_04, winb_x1,	x1[LX_PE_WIN_0][1]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_04, winb_y1,	y1[LX_PE_WIN_0][1]);
				PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_04);
				pre_ctrl->x0_pos[LX_PE_WIN_0][1] = x0[LX_PE_WIN_0][1];
				pre_ctrl->y0_pos[LX_PE_WIN_0][1] = y0[LX_PE_WIN_0][1];
				pre_ctrl->x1_pos[LX_PE_WIN_0][1] = x1[LX_PE_WIN_0][1];
				pre_ctrl->y1_pos[LX_PE_WIN_0][1] = y1[LX_PE_WIN_0][1];
			}
			/* set src histo window : pe0 r win_a */
			if(pre_ctrl->x0_pos[LX_PE_WIN_1][0] != x0[LX_PE_WIN_1][0] || \
				pre_ctrl->y0_pos[LX_PE_WIN_1][0] != y0[LX_PE_WIN_1][0] || \
				pre_ctrl->x1_pos[LX_PE_WIN_1][0] != x1[LX_PE_WIN_1][0] || \
				pre_ctrl->y1_pos[LX_PE_WIN_1][0] != y1[LX_PE_WIN_1][0])
			{
				PE_HST_HW_H13_DBG_PRINT("[W1A]inf:%d,%d,%d,%d, x,y:%d,%d,%d,%d to %d,%d,%d,%d\n",\
					cur_ctrl->x_ofst[LX_PE_WIN_1],cur_ctrl->y_ofst[LX_PE_WIN_1],\
					cur_ctrl->h_size[LX_PE_WIN_1],cur_ctrl->v_size[LX_PE_WIN_1],\
					pre_ctrl->x0_pos[LX_PE_WIN_1][0],pre_ctrl->y0_pos[LX_PE_WIN_1][0],\
					pre_ctrl->x1_pos[LX_PE_WIN_1][0],pre_ctrl->y1_pos[LX_PE_WIN_1][0],\
					x0[LX_PE_WIN_1][0],y0[LX_PE_WIN_1][0],x1[LX_PE_WIN_1][0],y1[LX_PE_WIN_1][0]);
				PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_01);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_01, wina_x0,	x0[LX_PE_WIN_1][0]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_01, wina_y0,	y0[LX_PE_WIN_1][0]);
				PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_01);
				PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_02);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_02, wina_x1,	x1[LX_PE_WIN_1][0]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_02, wina_y1,	y1[LX_PE_WIN_1][0]);
				PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_02);
				pre_ctrl->x0_pos[LX_PE_WIN_1][0] = x0[LX_PE_WIN_1][0];
				pre_ctrl->y0_pos[LX_PE_WIN_1][0] = y0[LX_PE_WIN_1][0];
				pre_ctrl->x1_pos[LX_PE_WIN_1][0] = x1[LX_PE_WIN_1][0];
				pre_ctrl->y1_pos[LX_PE_WIN_1][0] = y1[LX_PE_WIN_1][0];
			}
			/* set src histo window : pe0 r win_b */
			if(pre_ctrl->x0_pos[LX_PE_WIN_1][1] != x0[LX_PE_WIN_1][1] || \
				pre_ctrl->y0_pos[LX_PE_WIN_1][1] != y0[LX_PE_WIN_1][1] || \
				pre_ctrl->x1_pos[LX_PE_WIN_1][1] != x1[LX_PE_WIN_1][1] || \
				pre_ctrl->y1_pos[LX_PE_WIN_1][1] != y1[LX_PE_WIN_1][1])
			{
				PE_HST_HW_H13_DBG_PRINT("[W1B]inf:%d,%d,%d,%d, x,y:%d,%d,%d,%d to %d,%d,%d,%d\n",\
					cur_ctrl->x_ofst[LX_PE_WIN_1],cur_ctrl->y_ofst[LX_PE_WIN_1],\
					cur_ctrl->h_size[LX_PE_WIN_1],cur_ctrl->v_size[LX_PE_WIN_1],\
					pre_ctrl->x0_pos[LX_PE_WIN_1][1],pre_ctrl->y0_pos[LX_PE_WIN_1][1],\
					pre_ctrl->x1_pos[LX_PE_WIN_1][1],pre_ctrl->y1_pos[LX_PE_WIN_1][1],\
					x0[LX_PE_WIN_1][1],y0[LX_PE_WIN_1][1],x1[LX_PE_WIN_1][1],y1[LX_PE_WIN_1][1]);
				PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_03);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_03, winb_x0,	x0[LX_PE_WIN_1][1]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_03, winb_y0,	y0[LX_PE_WIN_1][1]);
				PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_03);
				PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_04);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_04, winb_x1,	x1[LX_PE_WIN_1][1]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_04, winb_y1,	y1[LX_PE_WIN_1][1]);
				PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_04);
				pre_ctrl->x0_pos[LX_PE_WIN_1][1] = x0[LX_PE_WIN_1][1];
				pre_ctrl->y0_pos[LX_PE_WIN_1][1] = y0[LX_PE_WIN_1][1];
				pre_ctrl->x1_pos[LX_PE_WIN_1][1] = x1[LX_PE_WIN_1][1];
				pre_ctrl->y1_pos[LX_PE_WIN_1][1] = y1[LX_PE_WIN_1][1];
			}
			/* set win sel : pe0 l */
			if(pre_ctrl->win_sel[LX_PE_WIN_0][0] != sel[LX_PE_WIN_0][0] || \
				pre_ctrl->win_sel[LX_PE_WIN_0][1] != sel[LX_PE_WIN_0][1] || \
				pre_ctrl->win_sel[LX_PE_WIN_0][2] != sel[LX_PE_WIN_0][2])
			{
				PE_HST_HW_H13_DBG_PRINT("[W0]win sel:%d,%d,%d to %d,%d,%d\n",\
					pre_ctrl->win_sel[LX_PE_WIN_0][0],pre_ctrl->win_sel[LX_PE_WIN_0][1],\
					pre_ctrl->win_sel[LX_PE_WIN_0][2],sel[LX_PE_WIN_0][0],\
					sel[LX_PE_WIN_0][1],sel[LX_PE_WIN_0][2]);
				PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_00);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, reg_hist0_win_sel,	sel[LX_PE_WIN_0][0]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, reg_hist1_win_sel,	sel[LX_PE_WIN_0][1]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, reg_hist2_win_sel,	sel[LX_PE_WIN_0][2]);
				PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_00);
				pre_ctrl->win_sel[LX_PE_WIN_0][0] = sel[LX_PE_WIN_0][0];
				pre_ctrl->win_sel[LX_PE_WIN_0][1] = sel[LX_PE_WIN_0][1];
				pre_ctrl->win_sel[LX_PE_WIN_0][2] = sel[LX_PE_WIN_0][2];
			}
			/* set win sel : pe0 r */
			if(pre_ctrl->win_sel[LX_PE_WIN_1][0] != sel[LX_PE_WIN_1][0] || \
				pre_ctrl->win_sel[LX_PE_WIN_1][1] != sel[LX_PE_WIN_1][1] || \
				pre_ctrl->win_sel[LX_PE_WIN_1][2] != sel[LX_PE_WIN_1][2])
			{
				PE_HST_HW_H13_DBG_PRINT("[W1]win sel:%d,%d,%d to %d,%d,%d\n",\
					pre_ctrl->win_sel[LX_PE_WIN_1][0],pre_ctrl->win_sel[LX_PE_WIN_1][1],\
					pre_ctrl->win_sel[LX_PE_WIN_1][2],sel[LX_PE_WIN_1][0],\
					sel[LX_PE_WIN_1][1],sel[LX_PE_WIN_1][2]);
				PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_00);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, reg_hist0_win_sel,	sel[LX_PE_WIN_1][0]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, reg_hist1_win_sel,	sel[LX_PE_WIN_1][1]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, reg_hist2_win_sel,	sel[LX_PE_WIN_1][2]);
				PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_00);
				pre_ctrl->win_sel[LX_PE_WIN_1][0] = sel[LX_PE_WIN_1][0];
				pre_ctrl->win_sel[LX_PE_WIN_1][1] = sel[LX_PE_WIN_1][1];
				pre_ctrl->win_sel[LX_PE_WIN_1][2] = sel[LX_PE_WIN_1][2];
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			x0[LX_PE_WIN_0][0] = cur_ctrl->x_ofst[LX_PE_WIN_0];
			y0[LX_PE_WIN_0][0] = cur_ctrl->y_ofst[LX_PE_WIN_0];
			x1[LX_PE_WIN_0][0] = x0[LX_PE_WIN_0][0]+cur_ctrl->h_size[LX_PE_WIN_0];
			y1[LX_PE_WIN_0][0] = y0[LX_PE_WIN_0][0]+cur_ctrl->v_size[LX_PE_WIN_0];
			x1[LX_PE_WIN_0][0] = (x1[LX_PE_WIN_0][0]>0)? (x1[LX_PE_WIN_0][0]-1):0;
			y1[LX_PE_WIN_0][0] = (y1[LX_PE_WIN_0][0]>0)? (y1[LX_PE_WIN_0][0]-1):0;
			x0[LX_PE_WIN_1][0] = cur_ctrl->x_ofst[LX_PE_WIN_1];
			y0[LX_PE_WIN_1][0] = cur_ctrl->y_ofst[LX_PE_WIN_1];
			x1[LX_PE_WIN_1][0] = x0[LX_PE_WIN_1][0]+cur_ctrl->h_size[LX_PE_WIN_1];
			y1[LX_PE_WIN_1][0] = y0[LX_PE_WIN_1][0]+cur_ctrl->v_size[LX_PE_WIN_1];
			x1[LX_PE_WIN_1][0] = (x1[LX_PE_WIN_1][0]>0)? (x1[LX_PE_WIN_1][0]-1):0;
			y1[LX_PE_WIN_1][0] = (y1[LX_PE_WIN_1][0]>0)? (y1[LX_PE_WIN_1][0]-1):0;
			/* set src histo window */
			if(pre_ctrl->x0_pos[LX_PE_WIN_0][0] != x0[LX_PE_WIN_0][0] || \
				pre_ctrl->y0_pos[LX_PE_WIN_0][0] != y0[LX_PE_WIN_0][0] || \
				pre_ctrl->x1_pos[LX_PE_WIN_0][0] != x1[LX_PE_WIN_0][0] || \
				pre_ctrl->y1_pos[LX_PE_WIN_0][0] != y1[LX_PE_WIN_0][0])
			{
				PE_DPP_H13_RdFL(debd_pp_hist_ctrl_01);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_01, x0,	x0[LX_PE_WIN_0][0]);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_01, y0,	y0[LX_PE_WIN_0][0]);
				PE_DPP_H13_WrFL(debd_pp_hist_ctrl_01);
				PE_DPP_H13_RdFL(debd_pp_hist_ctrl_02);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_02, x1,	x1[LX_PE_WIN_0][0]);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_02, y1,	y1[LX_PE_WIN_0][0]);
				PE_DPP_H13_WrFL(debd_pp_hist_ctrl_02);
				pre_ctrl->x0_pos[LX_PE_WIN_0][0] = x0[LX_PE_WIN_0][0];
				pre_ctrl->y0_pos[LX_PE_WIN_0][0] = y0[LX_PE_WIN_0][0];
				pre_ctrl->x1_pos[LX_PE_WIN_0][0] = x1[LX_PE_WIN_0][0];
				pre_ctrl->y1_pos[LX_PE_WIN_0][0] = y1[LX_PE_WIN_0][0];
			}
			if(pre_ctrl->x0_pos[LX_PE_WIN_1][0] != x0[LX_PE_WIN_1][0] || \
				pre_ctrl->y0_pos[LX_PE_WIN_1][0] != y0[LX_PE_WIN_1][0] || \
				pre_ctrl->x1_pos[LX_PE_WIN_1][0] != x1[LX_PE_WIN_1][0] || \
				pre_ctrl->y1_pos[LX_PE_WIN_1][0] != y1[LX_PE_WIN_1][0])
			{
				PE_DPP_H13_RdFL(debd_pp_hist_ctrl_03);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_03, x0,	x0[LX_PE_WIN_1][0]);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_03, y0,	y0[LX_PE_WIN_1][0]);
				PE_DPP_H13_WrFL(debd_pp_hist_ctrl_03);
				PE_DPP_H13_RdFL(debd_pp_hist_ctrl_04);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_04, x1,	x1[LX_PE_WIN_1][0]);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_04, y1,	y1[LX_PE_WIN_1][0]);
				PE_DPP_H13_WrFL(debd_pp_hist_ctrl_04);
				pre_ctrl->x0_pos[LX_PE_WIN_1][0] = x0[LX_PE_WIN_1][0];
				pre_ctrl->y0_pos[LX_PE_WIN_1][0] = y0[LX_PE_WIN_1][0];
				pre_ctrl->x1_pos[LX_PE_WIN_1][0] = x1[LX_PE_WIN_1][0];
				pre_ctrl->y1_pos[LX_PE_WIN_1][0] = y1[LX_PE_WIN_1][0];
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * set src histo mux
 *
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_SetSrcHistoMux(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	PE_HST_HW_H13_SRC_HST_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_hist.ctrl;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			if((pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] != cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0]) || \
				(pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] != cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1]) || \
				(pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] != cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2]))
			{
				PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_00);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, reg_hist0_data_mux,	cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, reg_hist1_data_mux,	cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1]);
				PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, reg_hist2_data_mux,	cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2]);
				PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_00);
				pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0];
				pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1];
				pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2];
			}
			if((pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] != cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0]) || \
				(pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] != cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1]) || \
				(pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] != cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2]))
			{
				PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_00);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, reg_hist0_data_mux,	cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, reg_hist1_data_mux,	cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1]);
				PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, reg_hist2_data_mux,	cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2]);
				PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_00);
				pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0];
				pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1];
				pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2];
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] != cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0])
			{
				PE_DPP_H13_RdFL(debd_pp_hist_ctrl_00);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_l_data_sel,	cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0]);
				PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_r_data_sel,	cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0]);
				PE_DPP_H13_WrFL(debd_pp_hist_ctrl_00);
				pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0];
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * set histo mode before ready to set src histo
 *
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_SetSrcHistoMode(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(cur_ctrl);
		/* set src histo window */
		PE_HST_HW_H13_SetSrcHistoWin(cur_ctrl);
		/* set src histo mux selection */
		PE_HST_HW_H13_SetSrcHistoMux(cur_ctrl);
	}while(0);
	return;
}
/**
 * get src histo from register
 *
 * @param   wId [in] LX_PE_WIN_ID
 * @param   *data [in] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_ID wId, UINT32 *data)
{
	int ret = RET_OK;
	UINT32 i,r_data;
	do {
		CHECK_KNULL(data);
		if(PE_KDRV_VER_H13BX)
		{
			if(wId==LX_PE_WIN_0)
			{
				PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
				PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	hif_hist_address,	0x0);
				PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	hif_hist_ai,		0x1);
				PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
				PE_P0L_H13B0_WrFL(p0l_tpd_hist_ai_ctrl);
				PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
				PE_P0L_H13B0_Rd01(p0l_tpd_hist_ai_ctrl,	hist_rd_available,	r_data);
				if(r_data)
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_data);
						r_data= PE_P0L_H13B0_Rd(p0l_tpd_hist_ai_data);
						data[i] = GET_BITS(r_data,0,22);
					}
					data[PE_HST_HW_H13_HST_BIN_NUM]=PE_HST_HW_H13_HIST_VALID;
				}
				else
				{
					data[PE_HST_HW_H13_HST_BIN_NUM]=PE_HST_HW_H13_HIST_INVALID;
				}
				PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
				PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	hif_hist_address,	0x0);
				PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	hif_hist_ai,		0x0);
				PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
				PE_P0L_H13B0_WrFL(p0l_tpd_hist_ai_ctrl);
			}
			else
			{
				PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_ctrl);
				PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl,	hif_hist_address,	0x0);
				PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl,	hif_hist_ai,		0x1);
				PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
				PE_P0R_H13B0_WrFL(p0r_tpd_hist_ai_ctrl);
				PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_ctrl);
				PE_P0R_H13B0_Rd01(p0r_tpd_hist_ai_ctrl,	hist_rd_available,	r_data);
				if(r_data)
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_data);
						r_data= PE_P0R_H13B0_Rd(p0r_tpd_hist_ai_data);
						data[i] = GET_BITS(r_data,0,22);
					}
					data[PE_HST_HW_H13_HST_BIN_NUM]=PE_HST_HW_H13_HIST_VALID;
				}
				else
				{
					data[PE_HST_HW_H13_HST_BIN_NUM]=PE_HST_HW_H13_HIST_INVALID;
				}
				PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_ctrl);
				PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl,	hif_hist_address,	0x0);
				PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl,	hif_hist_ai,		0x0);
				PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
				PE_P0R_H13B0_WrFL(p0r_tpd_hist_ai_ctrl);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(wId==LX_PE_WIN_0)
			{
				PE_DPP_H13_RdFL(debd_pp_l_hist_ia_ctrl);
				PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_address,	0x0);
				PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_ai,		0x1);
				PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
				PE_DPP_H13_WrFL(debd_pp_l_hist_ia_ctrl);
				PE_DPP_H13_RdFL(debd_pp_l_hist_ia_ctrl);
				PE_DPP_H13_Rd01(debd_pp_l_hist_ia_ctrl,	hist_rd_available,	r_data);
				if(r_data)
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						PE_DPP_H13_RdFL(debd_pp_l_hist_ia_data);
						r_data= PE_DPP_H13_Rd(debd_pp_l_hist_ia_data);
						data[i] = GET_BITS(r_data,0,22);
					}
				}
				else
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
					}
				}
				PE_DPP_H13_RdFL(debd_pp_l_hist_ia_ctrl);
				PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_address,	0x0);
				PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_ai,		0x0);
				PE_DPP_H13_Wr01(debd_pp_l_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
				PE_DPP_H13_WrFL(debd_pp_l_hist_ia_ctrl);
			}
			else
			{
				PE_DPP_H13_RdFL(debd_pp_r_hist_ia_ctrl);
				PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_address,	0x0);
				PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_ai,		0x1);
				PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
				PE_DPP_H13_WrFL(debd_pp_r_hist_ia_ctrl);
				PE_DPP_H13_RdFL(debd_pp_r_hist_ia_ctrl);
				PE_DPP_H13_Rd01(debd_pp_r_hist_ia_ctrl,	hist_rd_available,	r_data);
				if(r_data)
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						PE_DPP_H13_RdFL(debd_pp_r_hist_ia_data);
						r_data= PE_DPP_H13_Rd(debd_pp_r_hist_ia_data);
						data[i] = GET_BITS(r_data,0,22);
					}
				}
				else
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
					}
				}
				PE_DPP_H13_RdFL(debd_pp_r_hist_ia_ctrl);
				PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_address,	0x0);
				PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_ai,		0x0);
				PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
				PE_DPP_H13_WrFL(debd_pp_r_hist_ia_ctrl);
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * get src histo
 *
 * @param   wId [in] LX_PE_WIN_ID
 * @param   sel [in] UINT32, histo selection, hist0~2
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_ID wId, UINT32 sel, PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	UINT32 pxl_cnt0,pxl_cnt1;
	PE_HST_HW_H13_SRC_HST_DATA_T *hist_data = &_g_pe_hst_hw_h13_info.src_hist.data;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			/* update histo */
			if(cur_ctrl->mod_sel==PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL)
			{
				if(wId==LX_PE_WIN_0)
				{
					PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
					PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	reg_read_hist_sel,	sel);//0:hist0,1:hist1,etc:hist2
					PE_P0L_H13B0_WrFL(p0l_tpd_hist_ai_ctrl);
					switch(cur_ctrl->mux_sel[LX_PE_WIN_0][sel])
					{
						case PE_HST_HW_H13_SRC_HST_SEL_CB:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cb0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_CR:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cr0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_G:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->g0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_B:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->b0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_R:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->r0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_H:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->h0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_S:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->s0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_V:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->v0[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_Y:
						default:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->y0[0]));
							break;
					}
				}
				else	//LX_PE_WIN_1
				{
					PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_ctrl);
					PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl,	reg_read_hist_sel,	sel);//0:hist0,1:hist1,etc:hist2
					PE_P0R_H13B0_WrFL(p0r_tpd_hist_ai_ctrl);
					switch(cur_ctrl->mux_sel[LX_PE_WIN_1][sel])
					{
						case PE_HST_HW_H13_SRC_HST_SEL_CB:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->cb1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_CR:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->cr1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_G:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->g1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_B:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->b1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_R:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->r1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_H:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->h1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_S:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->s1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_V:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->v1[0]));
							break;
						case PE_HST_HW_H13_SRC_HST_SEL_Y:
						default:
							PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->y1[0]));
							break;
					}
				}
			}
			else	//PE_HST_HW_H13_SRC_HST_MOD_SEL_TB, PE_HST_HW_H13_SRC_HST_MOD_SEL_SS
			{
				if(wId==LX_PE_WIN_0)
				{
					PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
					PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl,	reg_read_hist_sel,	sel);//0:hist0,1:hist1,etc:hist2
					PE_P0L_H13B0_WrFL(p0l_tpd_hist_ai_ctrl);
					/* store y0:full(hist1,2), y1:half(hist0), same for others */
					if(sel==PE_HST0)
					{
						switch(cur_ctrl->mux_sel[LX_PE_WIN_0][sel])
						{
							case PE_HST_HW_H13_SRC_HST_SEL_CB:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cb1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_CR:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cr1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_G:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->g1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_B:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->b1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_R:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->r1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_H:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->h1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_S:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->s1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_V:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->v1[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_Y:
							default:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->y1[0]));
								break;
						}
					}
					else
					{
						switch(cur_ctrl->mux_sel[LX_PE_WIN_0][sel])
						{
							case PE_HST_HW_H13_SRC_HST_SEL_CB:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cb0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_CR:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cr0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_G:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->g0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_B:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->b0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_R:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->r0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_H:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->h0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_S:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->s0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_V:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->v0[0]));
								break;
							case PE_HST_HW_H13_SRC_HST_SEL_Y:
							default:
								PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->y0[0]));
								break;
						}
					}
				}
			}
			/* update pixel count */
			/* PE_HST0 is half, PE_HST1,2 is full for PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL */
			/* PE_HST0,1,2 is full for PE_HST_HW_H13_SRC_HST_MOD_SEL_SS,TB */
			if(sel==PE_HST1 && wId==LX_PE_WIN_0)
			{
				/* update win0 pxl cnt for HST1 only */
				PE_P0L_H13B0_RdFL(p0l_tpd_stat_00);
				PE_P0L_H13B0_Rd01(p0l_tpd_stat_00,	hist_pixel_count,	pxl_cnt0);
				hist_data->pxl_cnt[LX_PE_WIN_0] = GET_BITS(pxl_cnt0,0,22);
			}
			else if(sel==PE_HST0 && wId==LX_PE_WIN_1 && \
				cur_ctrl->mod_sel==PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL)
			{
				/* update win1 cnt for HST0 only and PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL */
				PE_P0R_H13B0_RdFL(p0r_tpd_stat_00);
				PE_P0R_H13B0_Rd01(p0r_tpd_stat_00,	hist_pixel_count,	pxl_cnt1);
				hist_data->pxl_cnt[LX_PE_WIN_1] = GET_BITS(pxl_cnt1,0,22);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			switch(cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0])
			{
				case PE_HST_HW_H13_SRC_HST_SEL_CB:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cb0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->cb1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_CR:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->cr0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->cr1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_G:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->g0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->g1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_B:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->b0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->b1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_R:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->r0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->r1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_H:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->h0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->h1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_S:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->s0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->s1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_V:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->v0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->v1[0]));
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_Y:
				default:
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_0, &(hist_data->y0[0]));
					PE_HST_HW_H13_GetSrcHistoFromReg(LX_PE_WIN_1, &(hist_data->y1[0]));
					break;
			}
			PE_DPP_H13_RdFL(debd_pp_hist_stat_00);
			PE_DPP_H13_Rd01(debd_pp_hist_stat_00,	pixel_count,	pxl_cnt0);
			hist_data->pxl_cnt[LX_PE_WIN_0] = GET_BITS(pxl_cnt0,0,22);
			PE_DPP_H13_RdFL(debd_pp_hist_stat_01);
			PE_DPP_H13_Rd01(debd_pp_hist_stat_01,	pixel_count,	pxl_cnt1);
			hist_data->pxl_cnt[LX_PE_WIN_1] = GET_BITS(pxl_cnt1,0,22);
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");;
		}
	}while(0);
	return;
}
/**
 * update src histo
 *
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_UpdateSrcHisto(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	UINT32 sum_total,sum_low,sum_high,s_state;
	PE_HST_HW_H13_SRC_HST_DATA_T *hist_data = &_g_pe_hst_hw_h13_info.src_hist.data;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_0,PE_HST0,cur_ctrl);	/* pe0 l hist0 */
			PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_0,PE_HST1,cur_ctrl);	/* pe0 l hist1 */
			PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_0,PE_HST2,cur_ctrl);	/* pe0 l hist2 */
			PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_1,PE_HST0,cur_ctrl);	/* pe0 r hist0 */
			PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_1,PE_HST1,cur_ctrl);	/* pe0 r hist1 */
			PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_1,PE_HST2,cur_ctrl);	/* pe0 r hist2 */
			/* get s_state */
			if(cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2]==PE_HST_HW_H13_SRC_HST_SEL_S)
			{
				/* protection in case of histo not available */
				if(hist_data->s0[0]!=PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE)
				{
					sum_low = hist_data->s0[0]+hist_data->s0[1]+hist_data->s0[2];
					sum_high = hist_data->s0[29]+hist_data->s0[30]+hist_data->s0[31];
					sum_total = (hist_data->pxl_cnt[LX_PE_WIN_0]>>8);
					s_state = (sum_total)? ((sum_low+sum_high)/sum_total):0;
					hist_data->s_state[LX_PE_WIN_0] = (s_state<256)? s_state:255;
				}
			}
			if(cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2]==PE_HST_HW_H13_SRC_HST_SEL_S)
			{
				/* protection in case of histo not available */
				if(hist_data->s1[0]!=PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE)
				{
					sum_low = hist_data->s1[0]+hist_data->s1[1]+hist_data->s1[2];
					sum_high = hist_data->s1[29]+hist_data->s1[30]+hist_data->s1[31];
					sum_total = (hist_data->pxl_cnt[LX_PE_WIN_1]>>8);
					s_state = (sum_total)? ((sum_low+sum_high)/sum_total):0;
					hist_data->s_state[LX_PE_WIN_1] = (s_state<256)? s_state:255;
				}
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_HST_HW_H13_GetSrcHisto(LX_PE_WIN_0,PE_HST0,cur_ctrl);	/* bdpp hist */
			/* get s_state */
			if(cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0]==PE_HST_HW_H13_SRC_HST_SEL_S)
			{
				sum_low = hist_data->s0[0]+hist_data->s0[1]+hist_data->s0[2];
				sum_high = hist_data->s0[29]+hist_data->s0[30]+hist_data->s0[31];
				sum_total = (hist_data->pxl_cnt[LX_PE_WIN_0]>>8);
				s_state = (sum_total)? ((sum_low+sum_high)/sum_total):0;
				hist_data->s_state[LX_PE_WIN_0] = (s_state<256)? s_state:255;
				sum_low = hist_data->s1[0]+hist_data->s1[1]+hist_data->s1[2];
				sum_high = hist_data->s1[29]+hist_data->s1[30]+hist_data->s1[31];
				sum_total = (hist_data->pxl_cnt[LX_PE_WIN_1]>>8);
				s_state = (sum_total)? ((sum_low+sum_high)/sum_total):0;
				hist_data->s_state[LX_PE_WIN_1] = (s_state<256)? s_state:255;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * update src histo difference
 *
 * @param   sel [in] UINT32
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_GetSrcHistoInfo(UINT32 sel, PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	UINT32 diff,idx;
	PE_HST_HW_H13_SRC_HST_DATA_T *hist_data = &_g_pe_hst_hw_h13_info.src_hist.data;
	PE_HST_HW_H13_SRC_INFO_T *hist_info = &_g_pe_hst_hw_h13_info.hist_inf.src_inf;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			if(sel>PE_HST2)	sel=PE_HST0;
			if(cur_ctrl->mod_sel==PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL)
			{
				switch(cur_ctrl->mux_sel[LX_PE_WIN_0][sel])
				{
					case PE_HST_HW_H13_SRC_HST_SEL_CB:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->cb0[0]),&(hist_data->cb1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_CR:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->cr0[0]),&(hist_data->cr1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_G:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->g0[0]),&(hist_data->g1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_B:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->b0[0]),&(hist_data->b1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_R:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->r0[0]),&(hist_data->r1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_H:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->h0[0]),&(hist_data->h1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_S:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->s0[0]),&(hist_data->s1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_V:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->v0[0]),&(hist_data->v1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_Y:
					default:
						PE_HST_HW_H13_GetHistDiff(&(hist_data->y0[0]),&(hist_data->y1[0]),&diff);
						break;
				}
				/* [0,1]y tb,ss,[2,3]cb,[4,5]cr, [6,7]g,[8,9]b,[10,11]r, [12,13]h,[14,15]s,[16,17]v */
				idx = cur_ctrl->mux_sel[LX_PE_WIN_0][sel]<<1;
				if((idx+1)>=PE_HST_HW_H13_SRC_INF_NUM)	idx=0;
				/* protection in case of histo not available */
				if(diff!=PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE)
					hist_info->dif_cnt[idx] = hist_info->dif_cnt[idx+1] = diff;
				/********************************************/
				hist_info->pxl_cnt[idx] = hist_data->pxl_cnt[LX_PE_WIN_0];
				hist_info->pxl_cnt[idx+1] = hist_data->pxl_cnt[LX_PE_WIN_1];
				if(hist_info->set_cnt[idx]<PE_HST_HW_H13_HIST_SET_CNT)
					hist_info->set_cnt[idx]++;
				else
					hist_info->set_cnt[idx]=0;
				if(hist_info->set_cnt[idx+1]<PE_HST_HW_H13_HIST_SET_CNT)
					hist_info->set_cnt[idx+1]++;
				else
					hist_info->set_cnt[idx+1]=0;
			}
			else	//PE_HST_HW_H13_SRC_HST_MOD_SEL_TB, PE_HST_HW_H13_SRC_HST_MOD_SEL_SS
			{
				/* we stored y0:full(hist1,2), y1:half(hist0), same for others */
				switch(cur_ctrl->mux_sel[LX_PE_WIN_0][sel])
				{
					case PE_HST_HW_H13_SRC_HST_SEL_CB:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->cb0[0]),&(hist_data->cb1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_CR:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->cr0[0]),&(hist_data->cr1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_G:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->g0[0]),&(hist_data->g1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_B:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->b0[0]),&(hist_data->b1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_R:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->r0[0]),&(hist_data->r1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_H:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->h0[0]),&(hist_data->h1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_S:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->s0[0]),&(hist_data->s1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_V:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->v0[0]),&(hist_data->v1[0]),&diff);
						break;
					case PE_HST_HW_H13_SRC_HST_SEL_Y:
					default:
						PE_HST_HW_H13_GetHistDiffFromFh(&(hist_data->y0[0]),&(hist_data->y1[0]),&diff);
						break;
				}
				/* [0,1]y tb,ss,[2,3]cb,[4,5]cr, [6,7]g,[8,9]b,[10,11]r, [12,13]h,[14,15]s,[16,17]v */
				idx = cur_ctrl->mux_sel[LX_PE_WIN_0][sel]<<1;
				if((idx+1)>=PE_HST_HW_H13_SRC_INF_NUM)	idx=0;
				if(cur_ctrl->mod_sel==PE_HST_HW_H13_SRC_HST_MOD_SEL_TB)
				{
					/* protection in case of histo not available */
					if(diff!=PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE)
						hist_info->dif_cnt[idx] = diff;
					/********************************************/
					hist_info->pxl_cnt[idx] = hist_data->pxl_cnt[LX_PE_WIN_0];
					if(hist_info->set_cnt[idx]<PE_HST_HW_H13_HIST_SET_CNT)
						hist_info->set_cnt[idx]++;
					else
						hist_info->set_cnt[idx]=0;
				}
				else	//PE_HST_HW_H13_SRC_HST_MOD_SEL_SS
				{
					/* protection in case of histo not available */
					if(diff!=PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE)
						hist_info->dif_cnt[idx+1] = diff;
					/********************************************/
					hist_info->pxl_cnt[idx+1] = hist_data->pxl_cnt[LX_PE_WIN_0];
					if(hist_info->set_cnt[idx+1]<PE_HST_HW_H13_HIST_SET_CNT)
						hist_info->set_cnt[idx+1]++;
					else
						hist_info->set_cnt[idx+1]=0;
				}
			}
			/* get s_state */
			if(sel==PE_HST0)	// for update once
			{
				if(cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2]==PE_HST_HW_H13_SRC_HST_SEL_S)
				{
					if(hist_info->s_state[LX_PE_WIN_0]!=hist_data->s_state[LX_PE_WIN_0])
					{
						PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
						PE_P1L_H13B0_Wr01(pe1_dse_ctrl_01, reg_s_status_0,	GET_BITS(hist_data->s_state[LX_PE_WIN_0],0,8));
						PE_P1L_H13B0_WrFL(pe1_dse_ctrl_01);
						hist_info->s_state[LX_PE_WIN_0] = hist_data->s_state[LX_PE_WIN_0];
					}
				}
				if(cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2]==PE_HST_HW_H13_SRC_HST_SEL_S)
				{
					if(hist_info->s_state[LX_PE_WIN_1]!=hist_data->s_state[LX_PE_WIN_1])
					{
						PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
						PE_P1L_H13B0_Wr01(pe1_dse_ctrl_01, reg_s_status_1,	GET_BITS(hist_data->s_state[LX_PE_WIN_1],0,8));
						PE_P1L_H13B0_WrFL(pe1_dse_ctrl_01);
						hist_info->s_state[LX_PE_WIN_1] = hist_data->s_state[LX_PE_WIN_1];
					}
				}
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(sel>PE_HST0)	sel=PE_HST0;
			switch(cur_ctrl->mux_sel[LX_PE_WIN_0][sel])
			{
				case PE_HST_HW_H13_SRC_HST_SEL_CB:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->cb0[0]),&(hist_data->cb1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_CR:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->cr0[0]),&(hist_data->cr1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_G:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->g0[0]),&(hist_data->g1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_B:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->b0[0]),&(hist_data->b1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_R:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->r0[0]),&(hist_data->r1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_H:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->h0[0]),&(hist_data->h1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_S:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->s0[0]),&(hist_data->s1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_V:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->v0[0]),&(hist_data->v1[0]),&diff);
					break;
				case PE_HST_HW_H13_SRC_HST_SEL_Y:
				default:
					PE_HST_HW_H13_GetHistDiff(&(hist_data->y0[0]),&(hist_data->y1[0]),&diff);
					break;
			}
			/* [0,1]y tb,ss,[2,3]cb,[4,5]cr, [6,7]g,[8,9]b,[10,11]r, [12,13]h,[14,15]s,[16,17]v */
			idx = cur_ctrl->mux_sel[LX_PE_WIN_0][sel]<<1;
			if((idx+1)>=PE_HST_HW_H13_SRC_INF_NUM)	idx=0;
			hist_info->dif_cnt[idx] = diff;
			hist_info->pxl_cnt[idx] = hist_data->pxl_cnt[LX_PE_WIN_0];
			if(hist_info->set_cnt[idx]<PE_HST_HW_H13_HIST_SET_CNT)
				hist_info->set_cnt[idx]++;
			else
				hist_info->set_cnt[idx]=0;
			hist_info->dif_cnt[idx+1] = diff;
			hist_info->pxl_cnt[idx+1] = hist_data->pxl_cnt[LX_PE_WIN_1];
			if(hist_info->set_cnt[idx+1]<PE_HST_HW_H13_HIST_SET_CNT)
				hist_info->set_cnt[idx+1]++;
			else
				hist_info->set_cnt[idx+1]=0;
			/* get s_state */
			if(cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0]==PE_HST_HW_H13_SRC_HST_SEL_S)
			{
				hist_info->s_state[LX_PE_WIN_0] = hist_data->s_state[LX_PE_WIN_0];
				hist_info->s_state[LX_PE_WIN_1] = hist_data->s_state[LX_PE_WIN_1];
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * update src histo info
 *
 * @param   *ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_UpdateSrcHistoInfo(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			if(cur_ctrl->mod_sel==PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL)
			{
				PE_HST_HW_H13_GetSrcHistoInfo(PE_HST0, cur_ctrl);
				PE_HST_HW_H13_GetSrcHistoInfo(PE_HST1, cur_ctrl);
				PE_HST_HW_H13_GetSrcHistoInfo(PE_HST2, cur_ctrl);
			}
			else	//PE_HST_HW_H13_SRC_HST_MOD_SEL_TB, PE_HST_HW_H13_SRC_HST_MOD_SEL_SS
			{
				PE_HST_HW_H13_GetSrcHistoInfo(PE_HST0, cur_ctrl);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_HST_HW_H13_GetSrcHistoInfo(PE_HST0, cur_ctrl);
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * set rd enable
 *
 * @param   rd_en [in] UINT32.
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13B_SetSrcHistoRdEnable(UINT32 rd_en)
{
	if(PE_KDRV_VER_H13BX)
	{
		if(rd_en==PE_RD_EN_OFF)
		{
			PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_00);
			PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, hist_rd_en,	0x0);	// rd off
			PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_00);
			PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_00);
			PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, hist_rd_en,	0x0);	// rd off
			PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_00);
		}
		else	//PE_RD_EN_ON
		{
			PE_P0L_H13B0_RdFL(p0l_tpd_ctrl_00);
			PE_P0L_H13B0_Wr01(p0l_tpd_ctrl_00, hist_rd_en,	0x1);	// rd on
			PE_P0L_H13B0_WrFL(p0l_tpd_ctrl_00);
			PE_P0R_H13B0_RdFL(p0r_tpd_ctrl_00);
			PE_P0R_H13B0_Wr01(p0r_tpd_ctrl_00, hist_rd_en,	0x1);	// rd on
			PE_P0R_H13B0_WrFL(p0r_tpd_ctrl_00);
		}
	}
	else
	{
		PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
	}
	return;
}
/**
 * set rd done
 *
 * @param   rd_done [in] UINT32.
 * @return  void.
 * @see
 * @author
 */
static void PE_HST_HW_H13B_SetSrcHistoRdDone(UINT32 rd_done)
{
	if(PE_KDRV_VER_H13BX)
	{
		if(rd_done==PE_RD_DONE_OFF)
		{
			PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
			PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl, hist_read_done,	0x0);
			PE_P0L_H13B0_WrFL(p0l_tpd_hist_ai_ctrl);
			PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_ctrl);
			PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl, hist_read_done,	0x0);
			PE_P0R_H13B0_WrFL(p0r_tpd_hist_ai_ctrl);
		}
		else	//PE_RD_DONE_ON
		{
			PE_P0L_H13B0_RdFL(p0l_tpd_hist_ai_ctrl);
			PE_P0L_H13B0_Wr01(p0l_tpd_hist_ai_ctrl, hist_read_done,	0x1);
			PE_P0L_H13B0_WrFL(p0l_tpd_hist_ai_ctrl);
			PE_P0R_H13B0_RdFL(p0r_tpd_hist_ai_ctrl);
			PE_P0R_H13B0_Wr01(p0r_tpd_hist_ai_ctrl, hist_read_done,	0x1);
			PE_P0R_H13B0_WrFL(p0r_tpd_hist_ai_ctrl);
		}
	}
	else
	{
		PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
	}
	return;
}
/**
 * ready to set src histo
 *
 * @param   void
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_ReadyToSetSrcHisto(void)
{
	if(PE_KDRV_VER_H13BX)
	{
		PE_HST_HW_H13B_SetSrcHistoRdEnable(PE_RD_EN_ON);	// rd on
	}
	else if(PE_KDRV_VER_H13AX)
	{
		PE_DPP_H13_RdFL(debd_pp_hist_ctrl_00);
		PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00, hist_rd_en,	0x1);	// rd on
		PE_DPP_H13_WrFL(debd_pp_hist_ctrl_00);
	}
	else
	{
		PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
	}
	return;
}
/**
 * release to set src histo
 *
 * @param   rd_done [in] UINT32.
 * @return  void.
 * @see
 * @author
 */
static void PE_HST_HW_H13_ReleaseToSetSrcHisto(UINT32 rd_done)
{
	if(PE_KDRV_VER_H13BX)
	{
		if(rd_done==PE_RD_DONE_OFF)
		{
			PE_HST_HW_H13B_SetSrcHistoRdDone(PE_RD_DONE_OFF);
			PE_HST_HW_H13B_SetSrcHistoRdEnable(PE_RD_EN_OFF);	// rd off
		}
		else	//PE_RD_DONE_ON
		{
			PE_HST_HW_H13B_SetSrcHistoRdDone(PE_RD_DONE_ON);
		}
	}
	else if(PE_KDRV_VER_H13AX)
	{
		if(rd_done==PE_RD_DONE_OFF)
		{
			PE_DPP_H13_RdFL(debd_pp_r_hist_ia_ctrl);
			PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hist_read_done,		0x0);
			PE_DPP_H13_WrFL(debd_pp_r_hist_ia_ctrl);
			PE_DPP_H13_RdFL(debd_pp_hist_ctrl_00);
			PE_DPP_H13_Wr01(debd_pp_hist_ctrl_00,	hist_rd_en,			0x0);
			PE_DPP_H13_WrFL(debd_pp_hist_ctrl_00);
		}
		else	//PE_RD_DONE_ON
		{
			PE_DPP_H13_RdFL(debd_pp_r_hist_ia_ctrl);
			PE_DPP_H13_Wr01(debd_pp_r_hist_ia_ctrl,	hist_read_done,		0x1);
			PE_DPP_H13_WrFL(debd_pp_r_hist_ia_ctrl);
		}
	}
	else
	{
		PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
	}
	return;
}
#ifdef PE_HST_HW_H13B_CHK_SRC_HIST_YHS_ONLY
/**
 * check src histo info of Y,H,S domain for full window 
 *	- get Y full,H full and S full
 *
 * @param   *cur_ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_CheckSrcHistoInfoForYhsFullWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	UINT32 under_30hz;
	PE_HST_HW_H13_STATE_T *hist_state = &_g_pe_hst_hw_h13_info.src_hist.state;
	PE_HST_HW_H13_SRC_HST_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_hist.ctrl;
	do {
		CHECK_KNULL(cur_ctrl);
		hist_state->curr = hist_state->next;
		/* update the cur_ctrl because it is a local variable */
		cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0];
		cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1];
		cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2];
		cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0];
		cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1];
		cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2];
		cur_ctrl->mod_sel = pre_ctrl->mod_sel;
		under_30hz = (cur_ctrl->in_f_rate < 305)? 1:0;
		if(PE_KDRV_VER_H13BX)
		{
			switch(hist_state->curr)
			{
				/* 0. start */
				case PE_HST_HW_H13_SRC_HST_STM_START:
					PE_HST_HW_H13_SetSrcHistoInit();
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = under_30hz? PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0:\
						PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0;
					break;
				/* 1. y,h,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0:
					PE_HST_HW_H13B_SetSrcHistoRdDone(PE_RD_DONE_OFF);
					PE_HST_HW_H13B_SetSrcHistoRdEnable(PE_RD_EN_ON);
					hist_state->next = under_30hz? PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1:\
						PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1:
					hist_state->next = under_30hz? PE_HST_HW_H13_SRC_HST_STM_GET_01ST:\
						PE_HST_HW_H13_SRC_HST_STM_GET_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_01ST:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_02ND:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13B_SetSrcHistoRdDone(PE_RD_DONE_ON);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					PE_HST_HW_H13B_SetSrcHistoRdEnable(PE_RD_EN_OFF);
					hist_state->next = under_30hz? PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0:\
						PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0;
					break;
				default:
					PE_HST_HW_H13_DBG_PRINT("hist_state(%d) wrong type.\n",hist_state->curr);
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
		pre_ctrl->mod_sel = cur_ctrl->mod_sel;
	}while(0);
	return;
}
#else	//PE_HST_HW_H13B_CHK_SRC_HIST_YHS_ONLY
/**
 * check src histo info for half window
 *
 * @param   *cur_ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_CheckSrcHistoInfoForHalfWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	PE_HST_HW_H13_STATE_T *hist_state = &_g_pe_hst_hw_h13_info.src_hist.state;
	PE_HST_HW_H13_SRC_HST_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_hist.ctrl;
	do {
		CHECK_KNULL(cur_ctrl);
		hist_state->curr = hist_state->next;
		if(PE_KDRV_VER_H13BX)
		{
			/* update the cur_ctrl because it is a local variable */
			cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0];
			cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1];
			cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2];
			cur_ctrl->mod_sel = pre_ctrl->mod_sel;
			/* don't use pe0 r histo in half win case */
			cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
			cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_Y;
			cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_Y;
			switch(hist_state->curr)
			{
				/* 00. start */
				case PE_HST_HW_H13_SRC_HST_STM_START:
					PE_HST_HW_H13_SetSrcHistoInit();
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0;
					break;
				/* 01. y tb : y full,y half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_01ST;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_01ST:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_01ST;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_01ST:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0;
					break;
				/* 02. y ss : y full,y half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_02ND:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_02ND:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_0;
					break;
				/* 03. cb tb : cb full,cb half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_03RD;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_03RD:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_03RD;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_03RD:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_0;
					break;
				/* 04. cb ss : cb full,cb half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_04TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_04TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_04TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_04TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CR;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CR;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_0;
					break;
				/* 05. cr tb : cr full,cr half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_05TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_05TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_05TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_05TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CR;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CR;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_0;
					break;
				/* 06. cr ss : cr full,cr half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_06TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_06TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_06TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_06TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_G;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_G;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_0;
					break;
				/* 07. g tb : g full,g half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_07TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_07TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_07TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_07TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_G;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_G;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_0;
					break;
				/* 08. g ss : g full,g half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_08TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_08TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_08TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_08TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_B;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_B;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_0;
					break;
				/* 09. b tb : b full,b half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_09TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_09TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_09TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_09TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_B;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_B;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_10TH_0;
					break;
				/* 10. b ss : b full,b half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_10TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_10TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_10TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_10TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_10TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_10TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_10TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_R;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_R;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_11TH_0;
					break;
				/* 11. r tb : r full,r half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_11TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_11TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_11TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_11TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_11TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_11TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_11TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_R;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_R;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_12TH_0;
					break;
				/* 12. r ss : r full,r half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_12TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_12TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_12TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_12TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_12TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_12TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_12TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_13TH_0;
					break;
				/* 13. h tb : h full,h half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_13TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_13TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_13TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_13TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_13TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_13TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_13TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_14TH_0;
					break;
				/* 14. h ss : h full,h half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_14TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_14TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_14TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_14TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_14TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_14TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_14TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_15TH_0;
					break;
				/* 15. s tb : s full,s half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_15TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_15TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_15TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_15TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_15TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_15TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_15TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_16TH_0;
					break;
				/* 16. s ss : s full,s half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_16TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_16TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_16TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_16TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_16TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_16TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_16TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_V;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_V;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_17TH_0;
					break;
				/* 17. v tb : v full,v half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_17TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_17TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_17TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_17TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_17TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_17TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_17TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_V;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_V;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_SS;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_18TH_0;
					break;
				/* 18. v ss : v full,v half,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_18TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_18TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_18TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_18TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_18TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_18TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_18TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_TB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0;
					break;
				default:
					PE_HST_HW_H13_DBG_PRINT("hist_state(%d) wrong type.\n",hist_state->curr);
					break;
			}
			pre_ctrl->mod_sel = cur_ctrl->mod_sel;
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
#endif	//PE_HST_HW_H13B_CHK_SRC_HIST_YHS_ONLY
/**
 * check src histo info for full window
 *
 * @param   *cur_ctrl [in] PE_HST_HW_H13_SRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_CheckSrcHistoInfoForFullWin(PE_HST_HW_H13_SRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	PE_HST_HW_H13_STATE_T *hist_state = &_g_pe_hst_hw_h13_info.src_hist.state;
	PE_HST_HW_H13_SRC_HST_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_hist.ctrl;
	do {
		CHECK_KNULL(cur_ctrl);
		hist_state->curr = hist_state->next;
		/* update the cur_ctrl because it is a local variable */
		cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0];
		cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1];
		cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = pre_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2];
		cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0];
		cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1];
		cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = pre_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2];
		cur_ctrl->mod_sel = pre_ctrl->mod_sel;
		if(PE_KDRV_VER_H13BX)
		{
			switch(hist_state->curr)
			{
				/* 0. start */
				case PE_HST_HW_H13_SRC_HST_STM_START:
					PE_HST_HW_H13_SetSrcHistoInit();
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mod_sel = PE_HST_HW_H13_SRC_HST_MOD_SEL_FULL;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0;
					break;
				/* 1. y,cb,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_01ST;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_01ST:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_01ST;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_01ST:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CR;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_G;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CR;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_G;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0;
					break;
				/* 2. cr,g,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_02ND:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_02ND:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_B;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_R;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_B;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_R;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_0;
					break;
				/* 3. b,r,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_03RD;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_03RD:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_03RD;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_03RD:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_V;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_H;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_V;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_0;
					break;
				/* 4. h,v,s full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_04TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_04TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_04TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_04TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST1] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					cur_ctrl->mux_sel[LX_PE_WIN_1][PE_HST2] = PE_HST_HW_H13_SRC_HST_SEL_S;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0;
					break;
				default:
					PE_HST_HW_H13_DBG_PRINT("hist_state(%d) wrong type.\n",hist_state->curr);
					break;
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			switch(hist_state->curr)
			{
				/* 0. start */
				case PE_HST_HW_H13_SRC_HST_STM_START:
					PE_HST_HW_H13_SetSrcHistoInit();
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0;
					break;
				/* 1. y, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_01ST;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_01ST:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_01ST;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_01ST:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CB;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0;
					break;
				/* 2. cb, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_02ND_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_02ND:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_02ND;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_02ND:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_CR;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_0;
					break;
				/* 3. cr, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_03RD_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_03RD;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_03RD:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_03RD;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_03RD:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_G;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_0;
					break;
				/* 4. g, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_04TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_04TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_04TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_04TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_04TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_B;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_0;
					break;
				/* 5. b, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_05TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_05TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_05TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_05TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_05TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_R;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_0;
					break;
				/* 6. r, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_06TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_06TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_06TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_06TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_06TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_H;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_0;
					break;
				/* 7. h, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_07TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_07TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_07TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_07TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_07TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_S;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_0;
					break;
				/* 8. s, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_08TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_08TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_08TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_08TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_08TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_V;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_0;
					break;
				/* 9. v, full */
				case PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_0:
					PE_HST_HW_H13_ReadyToSetSrcHisto();
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_1;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RDY_09TH_1:
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_GET_09TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_GET_09TH:
					PE_HST_HW_H13_UpdateSrcHisto(cur_ctrl);
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RLS_09TH;
					break;
				case PE_HST_HW_H13_SRC_HST_STM_RLS_09TH:
					PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
					PE_HST_HW_H13_UpdateSrcHistoInfo(cur_ctrl);
					/* set next histo mode */
					cur_ctrl->mux_sel[LX_PE_WIN_0][PE_HST0] = PE_HST_HW_H13_SRC_HST_SEL_Y;
					PE_HST_HW_H13_SetSrcHistoMode(cur_ctrl);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_RDY_01ST_0;
					break;
				default:
					PE_HST_HW_H13_DBG_PRINT("hist_state(%d) wrong type.\n",hist_state->curr);
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
		pre_ctrl->mod_sel = cur_ctrl->mod_sel;
	}while(0);
	return;
}
/**
 * check src histo info
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HST_HW_H13_CheckSrcHistoInfo(PE_TSK_H13_CFG_T *pCfg)
{
	int ret = RET_OK;
	PE_HST_HW_H13_SRC_HST_CTRL_T cur_ctrl;
	PE_INF_H13_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_H13_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_HST_HW_H13_STATE_T *hist_state = &_g_pe_hst_hw_h13_info.src_hist.state;
	LX_PE_DCM_HISTO_OPR_T *hist_opr = &_g_pe_hst_hw_h13_info.cfg[LX_PE_WIN_0].opr;
	PE_HST_HW_H13_SRC_INFO_T *hist_info = &_g_pe_hst_hw_h13_info.hist_inf.src_inf;
	PE_HST_HW_H13_SRC_HST_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.src_hist.ctrl;
	do {
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_H13)
		{
			cur_ctrl.out_type = disp0_info->out_type;
			cur_ctrl.in_f_rate = disp0_info->in_f_rate;
			if(pre_ctrl->out_type!=cur_ctrl.out_type)
			{
				hist_state->next = PE_HST_HW_H13_SRC_HST_STM_START;
				/* reset set cnt */
				memset(hist_info->set_cnt,0,sizeof(UINT32)*PE_HST_HW_H13_SRC_INF_NUM);
				PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_ON);
				PE_HST_HW_H13_ReleaseToSetSrcHisto(PE_RD_DONE_OFF);
				PE_HST_HW_H13_DBG_PRINT("Release src hist, outtype change(%d to %d).\n",\
					pre_ctrl->out_type,cur_ctrl.out_type);
				pre_ctrl->out_type=cur_ctrl.out_type;
			}
			if(((ctrl0_info->pe0_src_h==0||ctrl0_info->pe0_src_v==0)&& \
				(ctrl1_info->pe0_src_h==0||ctrl1_info->pe0_src_v==0)) || \
				hist_opr->src_hist_op==PE_HST_HW_H13_HIST_OP_STOP)
			{
				hist_state->next = PE_HST_HW_H13_SRC_HST_STM_START;
				break;
			}
			if(PE_KDRV_VER_H13BX)
			{
				cur_ctrl.x_ofst[LX_PE_WIN_0] = 0;
				cur_ctrl.y_ofst[LX_PE_WIN_0] = 0;
				cur_ctrl.h_size[LX_PE_WIN_0] = ctrl0_info->pe0_src_h;
				cur_ctrl.v_size[LX_PE_WIN_0] = ctrl0_info->pe0_src_v;
				cur_ctrl.x_ofst[LX_PE_WIN_1] = 0;
				cur_ctrl.y_ofst[LX_PE_WIN_1] = 0;
				cur_ctrl.h_size[LX_PE_WIN_1] = ctrl1_info->pe0_src_h;
				cur_ctrl.v_size[LX_PE_WIN_1] = ctrl1_info->pe0_src_v;
				#ifdef PE_HST_HW_H13B_CHK_SRC_HIST_YHS_ONLY
				if(pre_ctrl->h_size[LX_PE_WIN_0]!=cur_ctrl.h_size[LX_PE_WIN_0] || \
					pre_ctrl->v_size[LX_PE_WIN_0]!=cur_ctrl.v_size[LX_PE_WIN_0] || \
					pre_ctrl->h_size[LX_PE_WIN_1]!=cur_ctrl.h_size[LX_PE_WIN_1] || \
					pre_ctrl->v_size[LX_PE_WIN_1]!=cur_ctrl.v_size[LX_PE_WIN_1])
				{
					PE_HST_HW_H13_DBG_PRINT("size change([w0]%d,%d to %d,%d, [w1]%d,%d to %d,%d)\n",\
						pre_ctrl->h_size[LX_PE_WIN_0],pre_ctrl->v_size[LX_PE_WIN_0],\
						cur_ctrl.h_size[LX_PE_WIN_0],cur_ctrl.v_size[LX_PE_WIN_0],\
						pre_ctrl->h_size[LX_PE_WIN_1],pre_ctrl->v_size[LX_PE_WIN_1],\
						cur_ctrl.h_size[LX_PE_WIN_1],cur_ctrl.v_size[LX_PE_WIN_1]);
					hist_state->next = PE_HST_HW_H13_SRC_HST_STM_START;
				}
				PE_HST_HW_H13_CheckSrcHistoInfoForYhsFullWin(&cur_ctrl);
				#else
				/* Both out type 2d and 2d_3d are 2D for src histo. */
				if(cur_ctrl.out_type==LX_PE_OUT_2D || cur_ctrl.out_type==LX_PE_OUT_2D_3D)
				{
					PE_HST_HW_H13_CheckSrcHistoInfoForHalfWin(&cur_ctrl);
				}
				else	// 3d,pip,ud
				{
					PE_HST_HW_H13_CheckSrcHistoInfoForFullWin(&cur_ctrl);
				}
				#endif
			}
			else	//PE_KDRV_VER_H13AX
			{
				cur_ctrl.x_ofst[LX_PE_WIN_0] = ctrl0_info->m_win_h_ofst;
				cur_ctrl.y_ofst[LX_PE_WIN_0] = ctrl0_info->m_win_v_ofst;
				cur_ctrl.h_size[LX_PE_WIN_0] = ctrl0_info->m_win_h_size;
				cur_ctrl.v_size[LX_PE_WIN_0] = ctrl0_info->m_win_v_size;
				cur_ctrl.x_ofst[LX_PE_WIN_1] = ctrl1_info->m_win_h_ofst;
				cur_ctrl.y_ofst[LX_PE_WIN_1] = ctrl1_info->m_win_v_ofst;
				cur_ctrl.h_size[LX_PE_WIN_1] = ctrl1_info->m_win_h_size;
				cur_ctrl.v_size[LX_PE_WIN_1] = ctrl1_info->m_win_v_size;
				PE_HST_HW_H13_CheckSrcHistoInfoForFullWin(&cur_ctrl);
			}
			pre_ctrl->in_f_rate=cur_ctrl.in_f_rate;
			pre_ctrl->x_ofst[LX_PE_WIN_0]=cur_ctrl.x_ofst[LX_PE_WIN_0];
			pre_ctrl->y_ofst[LX_PE_WIN_0]=cur_ctrl.y_ofst[LX_PE_WIN_0];
			pre_ctrl->h_size[LX_PE_WIN_0]=cur_ctrl.h_size[LX_PE_WIN_0];
			pre_ctrl->v_size[LX_PE_WIN_0]=cur_ctrl.v_size[LX_PE_WIN_0];
			pre_ctrl->x_ofst[LX_PE_WIN_1]=cur_ctrl.x_ofst[LX_PE_WIN_1];
			pre_ctrl->y_ofst[LX_PE_WIN_1]=cur_ctrl.y_ofst[LX_PE_WIN_1];
			pre_ctrl->h_size[LX_PE_WIN_1]=cur_ctrl.h_size[LX_PE_WIN_1];
			pre_ctrl->v_size[LX_PE_WIN_1]=cur_ctrl.v_size[LX_PE_WIN_1];
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * ready to set lrcr histo
 *
 * @param   void
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_ReadyToSetLrcHisto(void)
{
	if(PE_KDRV_VER_H13BX)
	{
		PE_P1L_H13B0_RdFL(pe1_lrcr_ctrl_00);
		PE_P1L_H13B0_Wr01(pe1_lrcr_ctrl_00, hist_rd_en, 1);
		PE_P1L_H13B0_WrFL(pe1_lrcr_ctrl_00);
	}
	else if(PE_KDRV_VER_H13AX)
	{
		PE_DPP_H13_RdFL(debd_pp_lrcr_ctrl_00);
		PE_DPP_H13_Wr01(debd_pp_lrcr_ctrl_00, hist_rd_en, 1);
		PE_DPP_H13_WrFL(debd_pp_lrcr_ctrl_00);
	}
	else
	{
		PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
	}
	return;
}
/**
 * get lrcr histo from register
 *
 * @param   hst_sel [in] UINT32
 * @param   *l_data [in] UINT32
 * @param   *r_data [in] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_GetLrcHistoFromReg(UINT32 hst_sel, UINT32 *l_data, UINT32 *r_data)
{
	int ret = RET_OK;
	UINT32 i,rd_data;
	do {
		CHECK_KNULL(l_data);
		CHECK_KNULL(r_data);
		if(PE_KDRV_VER_H13BX)
		{
			switch(hst_sel)
			{
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_GRN:
					PE_P1L_H13B0_RdFL(pe1_l_g_hist_ia_ctrl);
					PE_P1L_H13B0_Rd01(pe1_l_g_hist_ia_ctrl,	hist_rd_g_available,	rd_data);
					if(rd_data)
					{
						#ifdef PE_HST_HW_H13B_USE_WORKAROUND_FOR_LRC_HIST_RD_ERROR
						PE_P1L_H13B0_RdFL(pe1_l_g_hist_ia_data);
						#endif
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_P1L_H13B0_RdFL(pe1_l_g_hist_ia_data);
							rd_data= PE_P1L_H13B0_Rd(pe1_l_g_hist_ia_data);
							l_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							l_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					PE_P1L_H13B0_RdFL(pe1_r_g_hist_ia_ctrl);
					PE_P1L_H13B0_Rd01(pe1_r_g_hist_ia_ctrl,	hist_rd_g_available,	rd_data);
					if(rd_data)
					{
						#ifdef PE_HST_HW_H13B_USE_WORKAROUND_FOR_LRC_HIST_RD_ERROR
						PE_P1L_H13B0_RdFL(pe1_r_g_hist_ia_data);
						#endif
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_P1L_H13B0_RdFL(pe1_r_g_hist_ia_data);
							rd_data= PE_P1L_H13B0_Rd(pe1_r_g_hist_ia_data);
							r_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							r_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_BLU:
					PE_P1L_H13B0_RdFL(pe1_l_b_hist_ia_ctrl);
					PE_P1L_H13B0_Rd01(pe1_l_b_hist_ia_ctrl,	hist_rd_b_available,	rd_data);
					if(rd_data)
					{
						#ifdef PE_HST_HW_H13B_USE_WORKAROUND_FOR_LRC_HIST_RD_ERROR
						PE_P1L_H13B0_RdFL(pe1_l_b_hist_ia_data);
						#endif
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_P1L_H13B0_RdFL(pe1_l_b_hist_ia_data);
							rd_data= PE_P1L_H13B0_Rd(pe1_l_b_hist_ia_data);
							l_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							l_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					PE_P1L_H13B0_RdFL(pe1_r_b_hist_ia_ctrl);
					PE_P1L_H13B0_Rd01(pe1_r_b_hist_ia_ctrl,	hist_rd_b_available,	rd_data);
					if(rd_data)
					{
						#ifdef PE_HST_HW_H13B_USE_WORKAROUND_FOR_LRC_HIST_RD_ERROR
						PE_P1L_H13B0_RdFL(pe1_r_b_hist_ia_data);
						#endif
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_P1L_H13B0_RdFL(pe1_r_b_hist_ia_data);
							rd_data= PE_P1L_H13B0_Rd(pe1_r_b_hist_ia_data);
							r_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							r_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_RED:
				default:
					PE_P1L_H13B0_RdFL(pe1_l_r_hist_ia_ctrl);
					PE_P1L_H13B0_Rd01(pe1_l_r_hist_ia_ctrl,	hist_rd_r_available,	rd_data);
					if(rd_data)
					{
						#ifdef PE_HST_HW_H13B_USE_WORKAROUND_FOR_LRC_HIST_RD_ERROR
						PE_P1L_H13B0_RdFL(pe1_l_r_hist_ia_data);
						#endif
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_P1L_H13B0_RdFL(pe1_l_r_hist_ia_data);
							rd_data= PE_P1L_H13B0_Rd(pe1_l_r_hist_ia_data);
							l_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							l_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					PE_P1L_H13B0_RdFL(pe1_r_r_hist_ia_ctrl);
					PE_P1L_H13B0_Rd01(pe1_r_r_hist_ia_ctrl,	hist_rd_r_available,	rd_data);
					if(rd_data)
					{
						#ifdef PE_HST_HW_H13B_USE_WORKAROUND_FOR_LRC_HIST_RD_ERROR
						PE_P1L_H13B0_RdFL(pe1_r_r_hist_ia_data);
						#endif
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_P1L_H13B0_RdFL(pe1_r_r_hist_ia_data);
							rd_data= PE_P1L_H13B0_Rd(pe1_r_r_hist_ia_data);
							r_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							r_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					break;
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			switch(hst_sel)
			{
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_GRN:
					PE_DPP_H13_RdFL(debd_pp_l_g_hist_ia_ctrl);
					PE_DPP_H13_Rd01(debd_pp_l_g_hist_ia_ctrl,	hist_rd_g_available,	rd_data);
					if(rd_data)
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_DPP_H13_RdFL(debd_pp_l_g_hist_ia_data);
							rd_data= PE_DPP_H13_Rd(debd_pp_l_g_hist_ia_data);
							l_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							l_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					PE_DPP_H13_RdFL(debd_pp_r_g_hist_ia_ctrl);
					PE_DPP_H13_Rd01(debd_pp_r_g_hist_ia_ctrl,	hist_rd_g_available,	rd_data);
					if(rd_data)
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_DPP_H13_RdFL(debd_pp_r_g_hist_ia_data);
							rd_data= PE_DPP_H13_Rd(debd_pp_r_g_hist_ia_data);
							r_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							r_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_BLU:
					PE_DPP_H13_RdFL(debd_pp_l_b_hist_ia_ctrl);
					PE_DPP_H13_Rd01(debd_pp_l_b_hist_ia_ctrl,	hist_rd_b_available,	rd_data);
					if(rd_data)
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_DPP_H13_RdFL(debd_pp_l_b_hist_ia_data);
							rd_data= PE_DPP_H13_Rd(debd_pp_l_b_hist_ia_data);
							l_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							l_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					PE_DPP_H13_RdFL(debd_pp_r_b_hist_ia_ctrl);
					PE_DPP_H13_Rd01(debd_pp_r_b_hist_ia_ctrl,	hist_rd_b_available,	rd_data);
					if(rd_data)
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_DPP_H13_RdFL(debd_pp_r_b_hist_ia_data);
							rd_data= PE_DPP_H13_Rd(debd_pp_r_b_hist_ia_data);
							r_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							r_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_RED:
				default:
					PE_DPP_H13_RdFL(debd_pp_l_r_hist_ia_ctrl);
					PE_DPP_H13_Rd01(debd_pp_l_r_hist_ia_ctrl,	hist_rd_r_available,	rd_data);
					if(rd_data)
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_DPP_H13_RdFL(debd_pp_l_r_hist_ia_data);
							rd_data= PE_DPP_H13_Rd(debd_pp_l_r_hist_ia_data);
							l_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							l_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					PE_DPP_H13_RdFL(debd_pp_r_r_hist_ia_ctrl);
					PE_DPP_H13_Rd01(debd_pp_r_r_hist_ia_ctrl,	hist_rd_r_available,	rd_data);
					if(rd_data)
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							PE_DPP_H13_RdFL(debd_pp_r_r_hist_ia_data);
							rd_data= PE_DPP_H13_Rd(debd_pp_r_r_hist_ia_data);
							r_data[i] = GET_BITS(rd_data,0,22);
						}
					}
					else
					{
						for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
						{
							r_data[i] = PE_HST_HW_H13_HIST_BIN_NOTAVAILABLE;
						}
					}
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * update lrcr histo
 *
 * @param   *ctrl [in] PE_HST_HW_H13_LRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_UpdateLrcHisto(PE_HST_HW_H13_LRC_HST_CTRL_T *cur_ctrl)
{
	int ret = RET_OK;
	PE_HST_HW_H13_LRC_HST_DATA_T *hist_data = &_g_pe_hst_hw_h13_info.lrc_hist.data;
	do {
		CHECK_KNULL(cur_ctrl);
		if(PE_KDRV_VER_H13BX)
		{
			switch(cur_ctrl->hst_sel)
			{
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_GRN:
					PE_P1L_H13B0_RdFL(pe1_l_g_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_l_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_l_g_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_P1L_H13B0_Wr01(pe1_l_g_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_l_g_hist_ia_ctrl);
					PE_P1L_H13B0_RdFL(pe1_r_g_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_r_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_r_g_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_P1L_H13B0_Wr01(pe1_r_g_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_r_g_hist_ia_ctrl);
					if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB0_GRN)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb0_t_grn[0]),&(hist_data->tb0_b_grn[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_SS0_GRN)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss0_l_grn[0]),&(hist_data->ss0_r_grn[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB1_GRN)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb1_t_grn[0]),&(hist_data->tb1_b_grn[0]));
					}
					else	//PE_HST_HW_H13_LRC_HST_SEL_SS1_GRN
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss1_l_grn[0]),&(hist_data->ss1_r_grn[0]));
					}
					PE_P1L_H13B0_RdFL(pe1_l_g_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_l_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_l_g_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_P1L_H13B0_Wr01(pe1_l_g_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_l_g_hist_ia_ctrl);
					PE_P1L_H13B0_RdFL(pe1_r_g_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_r_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_r_g_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_P1L_H13B0_Wr01(pe1_r_g_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_r_g_hist_ia_ctrl);
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_BLU:
					PE_P1L_H13B0_RdFL(pe1_l_b_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_l_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_l_b_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_P1L_H13B0_Wr01(pe1_l_b_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_l_b_hist_ia_ctrl);
					PE_P1L_H13B0_RdFL(pe1_r_b_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_r_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_r_b_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_P1L_H13B0_Wr01(pe1_r_b_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_r_b_hist_ia_ctrl);
					if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB0_BLU)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb0_t_blu[0]),&(hist_data->tb0_b_blu[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_SS0_BLU)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss0_l_blu[0]),&(hist_data->ss0_r_blu[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB1_BLU)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb1_t_blu[0]),&(hist_data->tb1_b_blu[0]));
					}
					else	//PE_HST_HW_H13_LRC_HST_SEL_SS1_BLU
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss1_l_blu[0]),&(hist_data->ss1_r_blu[0]));
					}
					PE_P1L_H13B0_RdFL(pe1_l_b_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_l_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_l_b_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_P1L_H13B0_Wr01(pe1_l_b_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_l_b_hist_ia_ctrl);
					PE_P1L_H13B0_RdFL(pe1_r_b_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_r_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_r_b_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_P1L_H13B0_Wr01(pe1_r_b_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_r_b_hist_ia_ctrl);
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_RED:
					PE_P1L_H13B0_RdFL(pe1_l_r_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_l_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_l_r_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_P1L_H13B0_Wr01(pe1_l_r_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_l_r_hist_ia_ctrl);
					PE_P1L_H13B0_RdFL(pe1_r_r_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_r_r_hist_ia_ctrl);
					if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB0_RED)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb0_t_red[0]),&(hist_data->tb0_b_red[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_SS0_RED)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss0_l_red[0]),&(hist_data->ss0_r_red[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB1_RED)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb1_t_red[0]),&(hist_data->tb1_b_red[0]));
					}
					else	//PE_HST_HW_H13_LRC_HST_SEL_SS1_RED
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss1_l_red[0]),&(hist_data->ss1_r_red[0]));
					}
					PE_P1L_H13B0_RdFL(pe1_l_r_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_l_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_l_r_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_P1L_H13B0_Wr01(pe1_l_r_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_l_r_hist_ia_ctrl);
					PE_P1L_H13B0_RdFL(pe1_r_r_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_P1L_H13B0_WrFL(pe1_r_r_hist_ia_ctrl);
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_RD_DONE:
				default:
					PE_P1L_H13B0_RdFL(pe1_r_r_hist_ia_ctrl);
					PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hist_rd_done,	0x1);
					PE_P1L_H13B0_WrFL(pe1_r_r_hist_ia_ctrl);
					break;
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			switch(cur_ctrl->hst_sel)
			{
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_GRN:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_GRN:
					PE_DPP_H13_RdFL(debd_pp_l_g_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_l_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_l_g_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_DPP_H13_Wr01(debd_pp_l_g_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_l_g_hist_ia_ctrl);
					PE_DPP_H13_RdFL(debd_pp_r_g_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_r_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_r_g_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_DPP_H13_Wr01(debd_pp_r_g_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_r_g_hist_ia_ctrl);
					if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB0_GRN)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb0_t_grn[0]),&(hist_data->tb0_b_grn[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_SS0_GRN)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss0_l_grn[0]),&(hist_data->ss0_r_grn[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB1_GRN)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb1_t_grn[0]),&(hist_data->tb1_b_grn[0]));
					}
					else	//PE_HST_HW_H13_LRC_HST_SEL_SS1_GRN
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss1_l_grn[0]),&(hist_data->ss1_r_grn[0]));
					}
					PE_DPP_H13_RdFL(debd_pp_l_g_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_l_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_l_g_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_DPP_H13_Wr01(debd_pp_l_g_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_l_g_hist_ia_ctrl);
					PE_DPP_H13_RdFL(debd_pp_r_g_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_r_g_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_r_g_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_DPP_H13_Wr01(debd_pp_r_g_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_r_g_hist_ia_ctrl);
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_BLU:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_BLU:
					PE_DPP_H13_RdFL(debd_pp_l_b_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_l_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_l_b_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_DPP_H13_Wr01(debd_pp_l_b_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_l_b_hist_ia_ctrl);
					PE_DPP_H13_RdFL(debd_pp_r_b_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_r_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_r_b_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_DPP_H13_Wr01(debd_pp_r_b_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_r_b_hist_ia_ctrl);
					if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB0_BLU)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb0_t_blu[0]),&(hist_data->tb0_b_blu[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_SS0_BLU)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss0_l_blu[0]),&(hist_data->ss0_r_blu[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB1_BLU)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb1_t_blu[0]),&(hist_data->tb1_b_blu[0]));
					}
					else	//PE_HST_HW_H13_LRC_HST_SEL_SS1_BLU
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss1_l_blu[0]),&(hist_data->ss1_r_blu[0]));
					}
					PE_DPP_H13_RdFL(debd_pp_l_b_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_l_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_l_b_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_DPP_H13_Wr01(debd_pp_l_b_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_l_b_hist_ia_ctrl);
					PE_DPP_H13_RdFL(debd_pp_r_b_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_r_b_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_r_b_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_DPP_H13_Wr01(debd_pp_r_b_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_r_b_hist_ia_ctrl);
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_TB0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_TB1_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS0_RED:
				case PE_HST_HW_H13_LRC_HST_SEL_SS1_RED:
					PE_DPP_H13_RdFL(debd_pp_l_r_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_l_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_l_r_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_DPP_H13_Wr01(debd_pp_l_r_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_l_r_hist_ia_ctrl);
					PE_DPP_H13_RdFL(debd_pp_r_r_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hif_hist_ai,		0x1);
					PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hif_hist_enable,	0x0);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_r_r_hist_ia_ctrl);
					if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB0_RED)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb0_t_red[0]),&(hist_data->tb0_b_red[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_SS0_RED)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss0_l_red[0]),&(hist_data->ss0_r_red[0]));
					}
					else if(cur_ctrl->hst_sel==PE_HST_HW_H13_LRC_HST_SEL_TB1_RED)
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->tb1_t_red[0]),&(hist_data->tb1_b_red[0]));
					}
					else	//PE_HST_HW_H13_LRC_HST_SEL_SS1_RED
					{
						PE_HST_HW_H13_GetLrcHistoFromReg(cur_ctrl->hst_sel,\
							&(hist_data->ss1_l_red[0]),&(hist_data->ss1_r_red[0]));
					}
					PE_DPP_H13_RdFL(debd_pp_l_r_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_l_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_l_r_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_DPP_H13_Wr01(debd_pp_l_r_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_l_r_hist_ia_ctrl);
					PE_DPP_H13_RdFL(debd_pp_r_r_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hif_hist_address,	0x0);
					PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hif_hist_ai,		0x0);
					PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hif_hist_enable,	0x1);	//0:host,1:normal
					PE_DPP_H13_WrFL(debd_pp_r_r_hist_ia_ctrl);
					break;
				case PE_HST_HW_H13_LRC_HST_SEL_RD_DONE:
				default:
					PE_DPP_H13_RdFL(debd_pp_r_r_hist_ia_ctrl);
					PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hist_rd_done,	0x1);
					PE_DPP_H13_WrFL(debd_pp_r_r_hist_ia_ctrl);
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * release to set lrcr histo
 *
 * @param   void
 * @return  void.
 * @see
 * @author
 */
static void PE_HST_HW_H13_ReleaseToSetLrcHisto(void)
{
	if(PE_KDRV_VER_H13BX)
	{
		PE_P1L_H13B0_RdFL(pe1_r_r_hist_ia_ctrl);
		PE_P1L_H13B0_Wr01(pe1_r_r_hist_ia_ctrl,	hist_rd_done,	0x0);
		PE_P1L_H13B0_WrFL(pe1_r_r_hist_ia_ctrl);
		PE_P1L_H13B0_RdFL(pe1_lrcr_ctrl_00);
		PE_P1L_H13B0_Wr01(pe1_lrcr_ctrl_00, hist_rd_en, 	0x0);
		PE_P1L_H13B0_WrFL(pe1_lrcr_ctrl_00);
	}
	else if(PE_KDRV_VER_H13AX)
	{
		PE_DPP_H13_RdFL(debd_pp_r_r_hist_ia_ctrl);
		PE_DPP_H13_Wr01(debd_pp_r_r_hist_ia_ctrl,	hist_rd_done,	0x0);
		PE_DPP_H13_WrFL(debd_pp_r_r_hist_ia_ctrl);
		PE_DPP_H13_RdFL(debd_pp_lrcr_ctrl_00);
		PE_DPP_H13_Wr01(debd_pp_lrcr_ctrl_00, hist_rd_en, 	0x0);
		PE_DPP_H13_WrFL(debd_pp_lrcr_ctrl_00);
	}
	else
	{
		PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
	}
	return;
}
/**
 * update lrcr ctrl
 *
 * @param   *ctrl [in] PE_TSK_H13_LRC_HST_CTRL_T
 * @return  void.
 * @see
 * @author
 */
static void PE_HST_HW_H13_UpdateLrcCtrl(PE_TSK_H13_LRC_HST_CTRL_T *ctrl)
{
	int ret = RET_OK;
	UINT32 i;
	PE_HST_HW_H13_LRC_HST_CTRL_T *hist_ctrl = &_g_pe_hst_hw_h13_info.lrc_hist.ctrl;
	do {
		CHECK_KNULL(ctrl);
		if(PE_KDRV_VER_H13)
		{
			switch(ctrl->win_mod)
			{
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_TB0:
					hist_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_TB0;
					for(i=0;i<4;i++)
					{
						hist_ctrl->tb0_t_pos[i] = ctrl->tb0_t_pos[i];
						hist_ctrl->tb0_b_pos[i] = ctrl->tb0_b_pos[i];
					}
					break;
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_SS0:
					hist_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_SS0;
					for(i=0;i<4;i++)
					{
						hist_ctrl->ss0_l_pos[i] = ctrl->ss0_l_pos[i];
						hist_ctrl->ss0_r_pos[i] = ctrl->ss0_r_pos[i];
					}
					break;
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_TB1:
					hist_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_TB1;
					for(i=0;i<4;i++)
					{
						hist_ctrl->tb1_t_pos[i] = ctrl->tb1_t_pos[i];
						hist_ctrl->tb1_b_pos[i] = ctrl->tb1_b_pos[i];
					}
					break;
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_SS1:
					hist_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_SS1;
					for(i=0;i<4;i++)
					{
						hist_ctrl->ss1_l_pos[i] = ctrl->ss1_l_pos[i];
						hist_ctrl->ss1_r_pos[i] = ctrl->ss1_r_pos[i];
					}
					break;
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_2D:
				default:
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * update lrcr info
 *
 * @param   *ctrl [in] PE_TSK_H13_LRC_HST_CTRL_T
 * @return  void
 * @see
 * @author
 */
static void PE_HST_HW_H13_UpdateLrcInfo(PE_TSK_H13_LRC_HST_CTRL_T *ctrl)
{
	int ret = RET_OK;
	UINT32 g_diff,b_diff,r_diff,idx;
	PE_HST_HW_H13_LRC_HST_DATA_T *hist_data = &_g_pe_hst_hw_h13_info.lrc_hist.data;
	PE_HST_HW_H13_LRC_INFO_T *hist_info = &_g_pe_hst_hw_h13_info.hist_inf.lrc_inf;
	do {
		CHECK_KNULL(ctrl);
		if(PE_KDRV_VER_H13)
		{
			if(ctrl->win_mod==PE_HST_HW_H13_LRC_HST_WIN_MOD_2D)
			{
				PE_HST_HW_H13_DBG_PRINT("nothing to do for win_mod 2D.\n");
				break;
			}
			switch(ctrl->win_mod)
			{
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_TB0:
					idx = 0;
					PE_HST_HW_H13_GetHistDiff(&(hist_data->tb0_t_grn[0]),&(hist_data->tb0_b_grn[0]),&g_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->tb0_t_blu[0]),&(hist_data->tb0_b_blu[0]),&b_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->tb0_t_red[0]),&(hist_data->tb0_b_red[0]),&r_diff);
					break;
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_SS0:
					idx = 1;
					PE_HST_HW_H13_GetHistDiff(&(hist_data->ss0_l_grn[0]),&(hist_data->ss0_r_grn[0]),&g_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->ss0_l_blu[0]),&(hist_data->ss0_r_blu[0]),&b_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->ss0_l_red[0]),&(hist_data->ss0_r_red[0]),&r_diff);
					break;
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_TB1:
					idx = 2;
					PE_HST_HW_H13_GetHistDiff(&(hist_data->tb1_t_grn[0]),&(hist_data->tb1_b_grn[0]),&g_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->tb1_t_blu[0]),&(hist_data->tb1_b_blu[0]),&b_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->tb1_t_red[0]),&(hist_data->tb1_b_red[0]),&r_diff);
					break;
				case PE_HST_HW_H13_LRC_HST_WIN_MOD_SS1:
				default:
					idx = 3;
					PE_HST_HW_H13_GetHistDiff(&(hist_data->ss1_l_grn[0]),&(hist_data->ss1_r_grn[0]),&g_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->ss1_l_blu[0]),&(hist_data->ss1_r_blu[0]),&b_diff);
					PE_HST_HW_H13_GetHistDiff(&(hist_data->ss1_l_red[0]),&(hist_data->ss1_r_red[0]),&r_diff);
					break;
			}
			hist_info->dif_max[idx] = PE_GET_MAX(g_diff,b_diff,r_diff);
			hist_info->pxl_cnt[idx] = ctrl->pxl_cnt[idx];
			if(hist_info->set_cnt[idx]<PE_HST_HW_H13_HIST_SET_CNT)
				hist_info->set_cnt[idx]++;
			else
				hist_info->set_cnt[idx]=0;
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return;
}
/**
 * check lrcr histo info
 *  - The lrcr of out type 2d_3d works like 2d,
 *    on [h13b0 with external frc] and [h13a0].
 *	  But it does like 3d(dual tb) on [h13b0 with internal frc]
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HST_HW_H13_CheckLrcrHistoInfo(PE_TSK_H13_CFG_T *pCfg)
{
	int ret = RET_OK;
	UINT32 is_2d_case,wId = 0;
	PE_HST_HW_H13_LRC_HST_CTRL_T cur_ctrl;
	PE_TSK_H13_LRC_HST_CTRL_T *lrc_ctrl = &pCfg->lrc;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_H13_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_HST_HW_H13_STATE_T *hist_state = &_g_pe_hst_hw_h13_info.lrc_hist.state;
	LX_PE_DCM_HISTO_OPR_T *hist_opr = &_g_pe_hst_hw_h13_info.cfg[wId].opr;
	PE_HST_HW_H13_LRC_INFO_T *hist_info = &_g_pe_hst_hw_h13_info.hist_inf.lrc_inf;
	PE_HST_HW_H13_LRC_HST_CTRL_T *pre_ctrl = &_g_pe_hst_hw_h13_info.lrc_hist.ctrl;
	do {
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_H13)
		{
			cur_ctrl.out_type = disp0_info->out_type;
			if(pre_ctrl->out_type!=cur_ctrl.out_type)
			{
				lrc_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_2D;	/* to set lrcr win */
				hist_state->next = PE_HST_HW_H13_LRC_HST_STM_INIT;
				/* reset set cnt */
				hist_info->set_cnt[0]=hist_info->set_cnt[1]=0;
				hist_info->set_cnt[2]=hist_info->set_cnt[3]=0;
				/**********************************************************/
				/* caution : need to turn rd done on before release histo */
				cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_RD_DONE;
				PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
				/**********************************************************/
				PE_HST_HW_H13_ReleaseToSetLrcHisto();
				pre_ctrl->out_type=cur_ctrl.out_type;
			}
			if(PE_KDRV_VER_H13BX)
			{
				if(disp0_info->mode.is_ext_frc)	/* external frc */
				{
					is_2d_case = (cur_ctrl.out_type==LX_PE_OUT_2D || \
						cur_ctrl.out_type==LX_PE_OUT_2D_3D)? 1:0;
				}
				else	/* internal frc */
				{
					is_2d_case = (cur_ctrl.out_type==LX_PE_OUT_2D || \
						cur_ctrl.out_type==LX_PE_OUT_2D_3D)? 1:0;
				}
			}
			else if(PE_KDRV_VER_H13AX)
			{
				is_2d_case = (cur_ctrl.out_type==LX_PE_OUT_2D || \
					cur_ctrl.out_type==LX_PE_OUT_2D_3D)? 1:0;
			}
			else
			{
				is_2d_case=0;
			}
			if((is_2d_case && (ctrl0_info->pe0_src_h==0||ctrl0_info->pe0_src_v==0)) || \
				(!is_2d_case) || (hist_opr->lrc_hist_op==PE_HST_HW_H13_HIST_OP_STOP))
			{
				break;
			}
			hist_state->curr = hist_state->next;
			switch(hist_state->curr)
			{
				/* init */
				case PE_HST_HW_H13_LRC_HST_STM_INIT:
					lrc_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_TB0;	/* to set lrcr win tb0 */
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY0_0;
					break;
				/* tb0 */
				case PE_HST_HW_H13_LRC_HST_STM_RDY0_0:
					PE_HST_HW_H13_ReadyToSetLrcHisto();
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY0_1;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RDY0_1:
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_GET0;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_GET0:
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_TB0_GRN;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_TB0_BLU;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_TB0_RED;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_RD_DONE;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RLS0;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RLS0:
					PE_HST_HW_H13_ReleaseToSetLrcHisto();
					PE_HST_HW_H13_UpdateLrcCtrl(lrc_ctrl);
					PE_HST_HW_H13_UpdateLrcInfo(lrc_ctrl);
					lrc_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_SS0;	/* to set lrcr win ss0 */
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY1_0;
					break;
				/* ss0 */
				case PE_HST_HW_H13_LRC_HST_STM_RDY1_0:
					PE_HST_HW_H13_ReadyToSetLrcHisto();
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY1_1;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RDY1_1:
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_GET1;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_GET1:
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_SS0_GRN;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_SS0_BLU;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_SS0_RED;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_RD_DONE;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RLS1;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RLS1:
					PE_HST_HW_H13_ReleaseToSetLrcHisto();
					PE_HST_HW_H13_UpdateLrcCtrl(lrc_ctrl);
					PE_HST_HW_H13_UpdateLrcInfo(lrc_ctrl);
					lrc_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_TB1;	/* to set lrcr win tb1 */
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY2_0;
					break;
				/* tb1 */
				case PE_HST_HW_H13_LRC_HST_STM_RDY2_0:
					PE_HST_HW_H13_ReadyToSetLrcHisto();
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY2_1;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RDY2_1:
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_GET2;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_GET2:
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_TB1_GRN;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_TB1_BLU;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_TB1_RED;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_RD_DONE;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RLS2;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RLS2:
					PE_HST_HW_H13_ReleaseToSetLrcHisto();
					PE_HST_HW_H13_UpdateLrcCtrl(lrc_ctrl);
					PE_HST_HW_H13_UpdateLrcInfo(lrc_ctrl);
					lrc_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_SS1;	/* to set lrcr win ss1 */
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY3_0;
					break;
				/* ss1 */
				case PE_HST_HW_H13_LRC_HST_STM_RDY3_0:
					PE_HST_HW_H13_ReadyToSetLrcHisto();
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY3_1;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RDY3_1:
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_GET3;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_GET3:
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_SS1_GRN;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_SS1_BLU;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_SS1_RED;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					cur_ctrl.hst_sel = PE_HST_HW_H13_LRC_HST_SEL_RD_DONE;
					PE_HST_HW_H13_UpdateLrcHisto(&cur_ctrl);
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RLS3;
					break;
				case PE_HST_HW_H13_LRC_HST_STM_RLS3:
					PE_HST_HW_H13_ReleaseToSetLrcHisto();
					PE_HST_HW_H13_UpdateLrcCtrl(lrc_ctrl);
					PE_HST_HW_H13_UpdateLrcInfo(lrc_ctrl);
					lrc_ctrl->win_mod = PE_HST_HW_H13_LRC_HST_WIN_MOD_TB0;	/* to set lrcr win tb0 */
					hist_state->next = PE_HST_HW_H13_LRC_HST_STM_RDY0_0;
					break;
				default:
					PE_HST_HW_H13_DBG_PRINT("hist_state->curr:%d, wrong type.\n",hist_state->curr);
					break;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get global histogram info state
 *
 * @param   *pstParams [in] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_HW_H13_GetGlobalHistInfo(LX_PE_ETC_DBG_T *pstParams)
{
    int ret = RET_OK;
	PE_HST_HW_H13_SRC_APL_T *src_apl = &_g_pe_hst_hw_h13_info.src_apl;
	PE_HST_HW_H13_SRC_HST_T *src_hist = &_g_pe_hst_hw_h13_info.src_hist;
	PE_HST_HW_H13_LRC_HST_T *lrc_hist = &_g_pe_hst_hw_h13_info.lrc_hist;
	PE_HST_HW_H13_INFO_T *hst_info = &_g_pe_hst_hw_h13_info.hist_inf;
	UINT32 ofst,size_sum,apl_size,s_hst_size,l_hst_size,hst_inf_size;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			ofst = 0;
			apl_size = sizeof(PE_HST_HW_H13_SRC_APL_T);
			s_hst_size = sizeof(PE_HST_HW_H13_SRC_HST_T);
			l_hst_size = sizeof(PE_HST_HW_H13_LRC_HST_T);
			hst_inf_size = sizeof(PE_HST_HW_H13_INFO_T);
			PE_HST_HW_H13_DBG_PRINT("size : apl:%d,s_hst:%d,l_hst:%d,hst_inf:%d\n",\
				apl_size,s_hst_size,l_hst_size,hst_inf_size);
			size_sum = apl_size+s_hst_size+l_hst_size+hst_inf_size;
			PE_HST_HW_H13_CHECK_CODE(pstParams->size!=(size_sum/sizeof(UINT32)),\
				break,"[%s,%d] size mismatch.(param_size:%d vs. (struct:%d)/(uint32:%d))\n",__F__,__L__,\
				pstParams->size,size_sum,sizeof(UINT32));
			/* get apl inf */
			memcpy(pstParams->data,src_apl,apl_size);
			/* get src histo inf */
			ofst += (apl_size/sizeof(UINT32));
			memcpy(&pstParams->data[ofst],src_hist,s_hst_size);
			/* get lrc histo inf */
			ofst += (s_hst_size/sizeof(UINT32));
			memcpy(&pstParams->data[ofst],lrc_hist,l_hst_size);
			/* get histo inf */
			ofst += (l_hst_size/sizeof(UINT32));
			memcpy(&pstParams->data[ofst],hst_info,hst_inf_size);
			/********************************************/
			/* print result */
			/********************************************/
			ofst = 0;
			PE_HST_HW_H13_DBG_PRINT("\n\n\n");
			PE_HST_HW_H13_DBG_PRINT("src_apl : state cur[%2d], pre[%2d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1]);
			PE_HST_HW_H13_DBG_PRINT("src_apl : sel[%2d], h[%4d][%4d], v[%4d][%4d], mux[%2d]\n",\
				pstParams->data[ofst+2],pstParams->data[ofst+3],pstParams->data[ofst+4],\
				pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			PE_HST_HW_H13_DBG_PRINT("src_apl : yuv w0[%4d,%4d,%4d] w1[%4d,%4d,%4d]\n",\
				GET_BITS(pstParams->data[ofst+8],0,10),GET_BITS(pstParams->data[ofst+8],10,10),\
				GET_BITS(pstParams->data[ofst+8],20,10),GET_BITS(pstParams->data[ofst+9],0,10),\
				GET_BITS(pstParams->data[ofst+9],10,10),GET_BITS(pstParams->data[ofst+9],20,10));
			PE_HST_HW_H13_DBG_PRINT("src_apl : hsv w0[%4d,%4d,%4d] w1[%4d,%4d,%4d]\n",\
				GET_BITS(pstParams->data[ofst+10],0,10),GET_BITS(pstParams->data[ofst+10],10,10),\
				GET_BITS(pstParams->data[ofst+10],20,10),GET_BITS(pstParams->data[ofst+11],0,10),\
				GET_BITS(pstParams->data[ofst+11],10,10),GET_BITS(pstParams->data[ofst+11],20,10));
			PE_HST_HW_H13_DBG_PRINT("src_apl : gbr w0[%4d,%4d,%4d] w1[%4d,%4d,%4d]\n",\
				GET_BITS(pstParams->data[ofst+12],0,10),GET_BITS(pstParams->data[ofst+12],10,10),\
				GET_BITS(pstParams->data[ofst+12],20,10),GET_BITS(pstParams->data[ofst+13],0,10),\
				GET_BITS(pstParams->data[ofst+13],10,10),GET_BITS(pstParams->data[ofst+13],20,10));
			PE_HST_HW_H13_DBG_PRINT("src_bbd : xy0 w0[%4d,%4d] w1[%4d,%4d]\n",\
				GET_BITS(pstParams->data[ofst+14],0,12),GET_BITS(pstParams->data[ofst+14],16,12),\
				GET_BITS(pstParams->data[ofst+15],0,12),GET_BITS(pstParams->data[ofst+15],16,12));
			PE_HST_HW_H13_DBG_PRINT("src_bbd : xy1 w0[%4d,%4d] w1[%4d,%4d]\n",\
				GET_BITS(pstParams->data[ofst+16],0,12),GET_BITS(pstParams->data[ofst+16],16,12),\
				GET_BITS(pstParams->data[ofst+17],0,12),GET_BITS(pstParams->data[ofst+17],16,12));
			ofst += 18;
			PE_HST_HW_H13_DBG_PRINT("src_hst : state cur[%2d],pre[%2d], out[%2d],in_fr[%3d],mod[%2d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4]);
			PE_HST_HW_H13_DBG_PRINT("src_hst : mux_sel[%2d,%2d,%2d][%2d,%2d,%2d]\n",\
				pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7],\
				pstParams->data[ofst+8],pstParams->data[ofst+9],pstParams->data[ofst+10]);
			PE_HST_HW_H13_DBG_PRINT("src_hst : win_sel[%2d,%2d,%2d][%2d,%2d,%2d]\n",\
				pstParams->data[ofst+11],pstParams->data[ofst+12],pstParams->data[ofst+13],\
				pstParams->data[ofst+14],pstParams->data[ofst+15],pstParams->data[ofst+16]);
			ofst += 17;
			PE_HST_HW_H13_DBG_PRINT("src_hst : x[%4d][%4d],y[%4d][%4d],h[%4d][%4d],v[%4d][%4d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3],\
				pstParams->data[ofst+4],pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			ofst += 8;
			PE_HST_HW_H13_DBG_PRINT("src_hst : x0[%4d,%4d][%4d,%4d],y0[%4d,%4d][%4d,%4d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3],\
				pstParams->data[ofst+4],pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			ofst += 8;
			PE_HST_HW_H13_DBG_PRINT("src_hst : x1[%4d,%4d][%4d,%4d],y1[%4d,%4d][%4d,%4d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3],\
				pstParams->data[ofst+4],pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			ofst += 8;
			PE_HST_HW_H13_PrintSrcHisto("src_hst Y0",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst Y1",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst Cb0",&(pstParams->data[ofst]));	ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst Cb1",&(pstParams->data[ofst]));	ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst Cr0",&(pstParams->data[ofst]));	ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst Cr1",&(pstParams->data[ofst]));	ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst G0",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst G1",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst B0",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst B1",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst R0",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst R1",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst H0",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst H1",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst S0",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst S1",&(pstParams->data[ofst]));		ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst sV0",&(pstParams->data[ofst]));	ofst += 33;
			PE_HST_HW_H13_PrintSrcHisto("src_hst sV1",&(pstParams->data[ofst]));	ofst += 33;
			PE_HST_HW_H13_DBG_PRINT("src_hst : pxl_cnt[%07d, %07d], s_state[%d,%d]\n",pstParams->data[ofst],\
				pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3]);
			ofst += 4;
			PE_HST_HW_H13_DBG_PRINT("lrc hst : state cur[%2d], pre[%2d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1]);
			PE_HST_HW_H13_DBG_PRINT("lrc hst : out[%d],hst_sel[%d],win_mod[%d]\n",\
				pstParams->data[ofst+2],pstParams->data[ofst+3],pstParams->data[ofst+4]);
			ofst += 5;
			PE_HST_HW_H13_DBG_PRINT("lrc hst : tb0 t[%4d,%4d,%4d,%4d],b[%4d,%4d,%4d,%4d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3],\
				pstParams->data[ofst+4],pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			ofst += 8;
			PE_HST_HW_H13_DBG_PRINT("lrc hst : ss0 l[%4d,%4d,%4d,%4d],r[%4d,%4d,%4d,%4d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3],\
				pstParams->data[ofst+4],pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			ofst += 8;
			PE_HST_HW_H13_DBG_PRINT("lrc hst : tb1 t[%4d,%4d,%4d,%4d],b[%4d,%4d,%4d,%4d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3],\
				pstParams->data[ofst+4],pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			ofst += 8;
			PE_HST_HW_H13_DBG_PRINT("lrc hst : ss1 l[%4d,%4d,%4d,%4d],r[%4d,%4d,%4d,%4d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3],\
				pstParams->data[ofst+4],pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			ofst += 8;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb0_t_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb0_b_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb0_t_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb0_b_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb0_t_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb0_b_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss0_l_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss0_r_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss0_l_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss0_r_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss0_l_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss0_r_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb1_t_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb1_b_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb1_t_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb1_b_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb1_t_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst tb1_b_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss1_l_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss1_r_grn",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss1_l_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss1_r_blu",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss1_l_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_PrintHistogram("lrc_hst ss1_r_red",&(pstParams->data[ofst]));		ofst += 32;
			PE_HST_HW_H13_DBG_PRINT("det 3df : [%d]\n",pstParams->data[ofst]);
			PE_HST_HW_H13_DBG_PRINT("hst dis : src_type[%d],out_type[%d]\n",\
				pstParams->data[ofst+1],pstParams->data[ofst+2]);
			ofst += 3;
			PE_HST_HW_H13_DBG_PRINT("lrc hst : dif_max[%7d,%7d,%7d,%7d]\n",pstParams->data[ofst],\
				pstParams->data[ofst+1],pstParams->data[ofst+2],pstParams->data[ofst+3]);
			PE_HST_HW_H13_DBG_PRINT("lrc hst : pxl_cnt[%7d,%7d,%7d,%7d]\n",pstParams->data[ofst+4],\
				pstParams->data[ofst+5],pstParams->data[ofst+6],pstParams->data[ofst+7]);
			PE_HST_HW_H13_DBG_PRINT("lrc hst : set_cnt[%7d,%7d,%7d,%7d]\n",pstParams->data[ofst+8],\
				pstParams->data[ofst+9],pstParams->data[ofst+10],pstParams->data[ofst+11]);
			ofst += 12;
			PE_HST_HW_H13_DBG_PRINT("src hst : s_state[%3d,%3d]\n",\
				pstParams->data[ofst],pstParams->data[ofst+1]);
			ofst += 2;
			PE_HST_HW_H13_DBG_PRINT("src hst : dif_cnt y[%7d,%7d],cb[%7d,%7d],cr[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : dif_cnt g[%7d,%7d], b[%7d,%7d], r[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : dif_cnt h[%7d,%7d], s[%7d,%7d], v[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : pxl_cnt y[%7d,%7d],cb[%7d,%7d],cr[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : pxl_cnt g[%7d,%7d], b[%7d,%7d], r[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : pxl_cnt h[%7d,%7d], s[%7d,%7d], v[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : set_cnt y[%7d,%7d],cb[%7d,%7d],cr[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : set_cnt g[%7d,%7d], b[%7d,%7d], r[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
			PE_HST_HW_H13_DBG_PRINT("src hst : set_cnt h[%7d,%7d], s[%7d,%7d], v[%7d,%7d]\n",
				pstParams->data[ofst],pstParams->data[ofst+1],pstParams->data[ofst+2],\
				pstParams->data[ofst+3],pstParams->data[ofst+4],pstParams->data[ofst+5]);
			ofst += 6;
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * update histo display info
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_HST_HW_H13_UpdateHistoDispInfo(PE_TSK_H13_CFG_T *pCfg)
{
	int ret = RET_OK;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_HST_HW_H13_DIS_INFO_T *hist_info = &_g_pe_hst_hw_h13_info.hist_inf.dis_inf;
	do {
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_H13)
		{
			hist_info->src_type = disp0_info->src_type;
			hist_info->out_type = disp0_info->out_type;
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * check global histo info
 *	- src apl, src histo, lrcr histo
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_HW_H13_CheckGlobalHistoInfo(PE_TSK_H13_CFG_T *pCfg)
{
    int ret = RET_OK;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_H13)
		{
			ret = PE_HST_HW_H13_UpdateHistoDispInfo(pCfg);
			PE_HST_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_HST_HW_H13_UpdateHistoDispInfo() error.\n",__F__,__L__);
			ret = PE_HST_HW_H13_CheckSrcAplInfo(pCfg);
			PE_HST_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_HST_HW_H13_CheckSrcAplInfo() error.\n",__F__,__L__);
			ret = PE_HST_HW_H13_CheckSrcHistoInfo(pCfg);
			PE_HST_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_HST_HW_H13_CheckSrcHistoInfo() error.\n",__F__,__L__);
			ret = PE_HST_HW_H13_CheckLrcrHistoInfo(pCfg);
			PE_HST_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_HST_HW_H13_CheckLrcrHistoInfo() error.\n",__F__,__L__);
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set histo config
 *
 * @param   *pstParams [in] LX_PE_DCM_HISTO_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_HW_H13_SetHistoConfig(LX_PE_DCM_HISTO_CFG_T *pstParams)
{
	int ret = RET_OK;
	PE_HST_HW_H13_SETTINGS_T *pInfo=&_g_pe_hst_hw_h13_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HST_HW_H13_DBG_PRINT("set pstParams[%d] : op:src_apl:%d,src_hist:%d,lrc_hist:%d\n",\
			pstParams->win_id,pstParams->opr.src_apl_op,pstParams->opr.src_hist_op,pstParams->opr.lrc_hist_op);
		if(PE_KDRV_VER_H13)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(&(pInfo->cfg[LX_PE_WIN_0]),pstParams,sizeof(LX_PE_DCM_HISTO_CFG_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(&(pInfo->cfg[LX_PE_WIN_1]),pstParams,sizeof(LX_PE_DCM_HISTO_CFG_T));
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get histo config
 *
 * @param   *pstParams [in] LX_PE_DCM_HISTO_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_HW_H13_GetHistoConfig(LX_PE_DCM_HISTO_CFG_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_HST_HW_H13_SETTINGS_T *pInfo=&_g_pe_hst_hw_h13_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_H13)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				pInfo->cfg[LX_PE_WIN_0].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->cfg[LX_PE_WIN_0]),sizeof(LX_PE_DCM_HISTO_CFG_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pInfo->cfg[LX_PE_WIN_1].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->cfg[LX_PE_WIN_1]),sizeof(LX_PE_DCM_HISTO_CFG_T));
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_HST_HW_H13_DBG_PRINT("get pstParams[%d] : op:src_apl:%d,src_hist:%d,lrc_hist:%d\n",\
			pstParams->win_id,pstParams->opr.src_apl_op,pstParams->opr.src_hist_op,pstParams->opr.lrc_hist_op);
	}while(0);
	return ret;
}
/**
 * update detected 3d format and get histo info
 *
 * @param   *pstParams [in/out] PE_HST_HW_H13_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_HW_H13_GetHistoInfo(PE_HST_HW_H13_INFO_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_HST_HW_H13_INFO_T *pInfo = &_g_pe_hst_hw_h13_info.hist_inf;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			pInfo->det_3df = pstParams->det_3df;
			memcpy(pstParams,pInfo,sizeof(PE_HST_HW_H13_INFO_T));
			if(_g_hst_hw_h13_trace)
			{
				if(count>(PE_PRINT_COUNT_NUM>>3))
				{
					PE_HST_HW_H13_DBG_PRINT("det_3df[%d],src_type[%d],out_type[%d]\n",\
						pstParams->det_3df,pstParams->dis_inf.src_type,pstParams->dis_inf.out_type);
					PE_HST_HW_H13_DBG_PRINT("lrc : dif_max[%7d,%7d,%7d,%7d]\n",pstParams->lrc_inf.dif_max[0],\
						pstParams->lrc_inf.dif_max[1],pstParams->lrc_inf.dif_max[2],pstParams->lrc_inf.dif_max[3]);
					PE_HST_HW_H13_DBG_PRINT("lrc : pxl_cnt[%7d,%7d,%7d,%7d]\n",pstParams->lrc_inf.pxl_cnt[0],\
						pstParams->lrc_inf.pxl_cnt[1],pstParams->lrc_inf.pxl_cnt[2],pstParams->lrc_inf.pxl_cnt[3]);
					PE_HST_HW_H13_DBG_PRINT("lrc : set_cnt[%7d,%7d,%7d,%7d]\n",pstParams->lrc_inf.set_cnt[0],\
						pstParams->lrc_inf.set_cnt[1],pstParams->lrc_inf.set_cnt[2],pstParams->lrc_inf.set_cnt[3]);
					PE_HST_HW_H13_DBG_PRINT("src : s_state[%3d,%3d]\n",\
						pstParams->src_inf.s_state[0],pstParams->src_inf.s_state[1]);
					PE_HST_HW_H13_DBG_PRINT("src : dif_cnt y[%7d,%7d],cb[%7d,%7d],cr[%7d,%7d]\n",
						pstParams->src_inf.dif_cnt[0],pstParams->src_inf.dif_cnt[1],pstParams->src_inf.dif_cnt[2],\
						pstParams->src_inf.dif_cnt[3],pstParams->src_inf.dif_cnt[4],pstParams->src_inf.dif_cnt[5]);
					PE_HST_HW_H13_DBG_PRINT("src : dif_cnt g[%7d,%7d], b[%7d,%7d], r[%7d,%7d]\n",
						pstParams->src_inf.dif_cnt[6],pstParams->src_inf.dif_cnt[7],pstParams->src_inf.dif_cnt[8],\
						pstParams->src_inf.dif_cnt[9],pstParams->src_inf.dif_cnt[10],pstParams->src_inf.dif_cnt[11]);
					PE_HST_HW_H13_DBG_PRINT("src : dif_cnt h[%7d,%7d], s[%7d,%7d], v[%7d,%7d]\n",
						pstParams->src_inf.dif_cnt[12],pstParams->src_inf.dif_cnt[13],pstParams->src_inf.dif_cnt[14],\
						pstParams->src_inf.dif_cnt[15],pstParams->src_inf.dif_cnt[16],pstParams->src_inf.dif_cnt[17]);
					PE_HST_HW_H13_DBG_PRINT("src : pxl_cnt y[%7d,%7d],cb[%7d,%7d],cr[%7d,%7d]\n",
						pstParams->src_inf.pxl_cnt[0],pstParams->src_inf.pxl_cnt[1],pstParams->src_inf.pxl_cnt[2],\
						pstParams->src_inf.pxl_cnt[3],pstParams->src_inf.pxl_cnt[4],pstParams->src_inf.pxl_cnt[5]);
					PE_HST_HW_H13_DBG_PRINT("src : pxl_cnt g[%7d,%7d], b[%7d,%7d], r[%7d,%7d]\n",
						pstParams->src_inf.pxl_cnt[6],pstParams->src_inf.pxl_cnt[7],pstParams->src_inf.pxl_cnt[8],\
						pstParams->src_inf.pxl_cnt[9],pstParams->src_inf.pxl_cnt[10],pstParams->src_inf.pxl_cnt[11]);
					PE_HST_HW_H13_DBG_PRINT("src : pxl_cnt h[%7d,%7d], s[%7d,%7d], v[%7d,%7d]\n",
						pstParams->src_inf.pxl_cnt[12],pstParams->src_inf.pxl_cnt[13],pstParams->src_inf.pxl_cnt[14],\
						pstParams->src_inf.pxl_cnt[15],pstParams->src_inf.pxl_cnt[16],pstParams->src_inf.pxl_cnt[17]);
					PE_HST_HW_H13_DBG_PRINT("src : set_cnt y[%7d,%7d],cb[%7d,%7d],cr[%7d,%7d]\n",
						pstParams->src_inf.set_cnt[0],pstParams->src_inf.set_cnt[1],pstParams->src_inf.set_cnt[2],\
						pstParams->src_inf.set_cnt[3],pstParams->src_inf.set_cnt[4],pstParams->src_inf.set_cnt[5]);
					PE_HST_HW_H13_DBG_PRINT("src : set_cnt g[%7d,%7d], b[%7d,%7d], r[%7d,%7d]\n",
						pstParams->src_inf.set_cnt[6],pstParams->src_inf.set_cnt[7],pstParams->src_inf.set_cnt[8],\
						pstParams->src_inf.set_cnt[9],pstParams->src_inf.set_cnt[10],pstParams->src_inf.set_cnt[11]);
					PE_HST_HW_H13_DBG_PRINT("src : set_cnt h[%7d,%7d], s[%7d,%7d], v[%7d,%7d]\n",
						pstParams->src_inf.set_cnt[12],pstParams->src_inf.set_cnt[13],pstParams->src_inf.set_cnt[14],\
						pstParams->src_inf.set_cnt[15],pstParams->src_inf.set_cnt[16],pstParams->src_inf.set_cnt[17]);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get detected 3d format
 *
 * @param   *pstParams [in/out] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		PE_HST_HW_H13_DET_3D_FMT
 * @author
 */
int PE_HST_HW_H13_GetDetected3dFmt(UINT32 *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_HST_HW_H13_INFO_T *pInfo = &_g_pe_hst_hw_h13_info.hist_inf;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			*pstParams = (UINT32)pInfo->det_3df;
			if(_g_hst_hw_h13_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_HST_HW_H13_DBG_PRINT("det_3df[%d]\n",pInfo->det_3df);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get saturation state
 *
 * @param   *pstParams [in/out] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see		
 * @author
 */
int PE_HST_HW_H13_GetSaturationState(UINT32 *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_HST_HW_H13_SRC_HST_DATA_T *hist_data = &_g_pe_hst_hw_h13_info.src_hist.data;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			*pstParams = hist_data->s_state[LX_PE_WIN_0];
			if(_g_hst_hw_h13_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_HST_HW_H13_DBG_PRINT("s_state[%d][%d]\n",\
						hist_data->s_state[LX_PE_WIN_0],hist_data->s_state[LX_PE_WIN_1]);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get src(pe0) histo bin(32bin)
 *
 * @param   *pstParams [in/out] UINT32
 * @param   hst_sel [in] PE_HST_HW_H13_SRC_HST_SEL
 * @return  OK if success, ERROR otherwise.
 * @see		
 * @author
 */
int PE_HST_HW_H13_GetSrcHistoBin(UINT32 *pstParams, PE_HST_HW_H13_SRC_HST_SEL hst_sel)
{
	int ret = RET_OK;
	UINT32 i;
	PE_HST_HW_H13_SRC_HST_CTRL_T *hist_ctrl = &_g_pe_hst_hw_h13_info.src_hist.ctrl;
	PE_HST_HW_H13_SRC_HST_DATA_T *hist_data = &_g_pe_hst_hw_h13_info.src_hist.data;
	do{
		CHECK_KNULL(pstParams);
		PE_HST_HW_H13_CHECK_CODE((hst_sel!=PE_HST_HW_H13_SRC_HST_SEL_S)&&\
			(hst_sel!=PE_HST_HW_H13_SRC_HST_SEL_H)&&(hst_sel!=PE_HST_HW_H13_SRC_HST_SEL_Y),\
			break,"[%s,%d] hst_sel(%d) is wrong.\n",__F__,__L__,hst_sel);
		if(PE_KDRV_VER_H13)
		{
			/* check twin path mode(ud,3d) and get average of y0 and y1 */
			if(hist_ctrl->out_type==LX_PE_OUT_UD || hist_ctrl->out_type==LX_PE_OUT_TB || \
				hist_ctrl->out_type==LX_PE_OUT_SS || hist_ctrl->out_type==LX_PE_OUT_FS || \
				hist_ctrl->out_type==LX_PE_OUT_DUAL_TB || \
				hist_ctrl->out_type==LX_PE_OUT_DUAL_SS || \
				hist_ctrl->out_type==LX_PE_OUT_DUAL_FULL)
			{
				if(hst_sel==PE_HST_HW_H13_SRC_HST_SEL_S)
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						pstParams[i]=(hist_data->s0[i]+hist_data->s1[i]);
					}
				}
				else if(hst_sel==PE_HST_HW_H13_SRC_HST_SEL_H)
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						pstParams[i]=(hist_data->h0[i]+hist_data->h1[i]);
					}
				}
				else	//PE_HST_HW_H13_SRC_HST_SEL_Y
				{
					for(i=0;i<PE_HST_HW_H13_HST_BIN_NUM;i++)
					{
						pstParams[i]=(hist_data->y0[i]+hist_data->y1[i]);
					}
				}
			}
			else
			{
				if(hst_sel==PE_HST_HW_H13_SRC_HST_SEL_S)
				{
					memcpy(pstParams,&(hist_data->s0[0]),sizeof(UINT32)*PE_HST_HW_H13_HST_BIN_NUM);
				}
				else if(hst_sel==PE_HST_HW_H13_SRC_HST_SEL_H)
				{
					memcpy(pstParams,&(hist_data->h0[0]),sizeof(UINT32)*PE_HST_HW_H13_HST_BIN_NUM);
				}
				else	//PE_HST_HW_H13_SRC_HST_SEL_Y
				{
					memcpy(pstParams,&(hist_data->y0[0]),sizeof(UINT32)*PE_HST_HW_H13_HST_BIN_NUM);
				}
			}
		}
		else
		{
			PE_HST_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

