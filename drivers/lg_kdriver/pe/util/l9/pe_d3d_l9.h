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


/** @file pe_d3d_l9.h
 *
 *  driver header for picture enhance etc functions. ( used only within kdriver )
 *	
 *	@author		
 *	@version	0.1
 *	@note		
 *	@date		2011.09.16
 *	@see		
 */

#ifndef	_PE_D3D_L9_H_
#define	_PE_D3D_L9_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "de_kapi.h"
#include "pe_kapi.h"
#include "pe_win_hw.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_D3D_USE_NEW_ALGO
#define PE_D3D_USE_LINE_DIFF_BY_SW

#define D3D_MAX_BIN	32
#define D3D_MAX_BAK_FMT	16
#define D3D_MAX_DCE_DLT	4


#define D3D_MAX_HISTOGRAM_ON_CASE3	1000000

#ifdef PE_D3D_USE_NEW_ALGO	// Added by won.hur 2011.12.13
#define D3D_MAX_MINORITY_VOTE_VAL_NORMAL	2
#define D3D_MAX_MINORITY_VOTE_VAL_CHANGED	1
#define D3D_VOTE_STACK_SIZE_ON_FORMAT_CHANGE	4
#define D3D_MIN_TB_SS_RATIO_THRESHOLD		5
#define D3D_ADJUSTABLE_VOTING_MSEC			5000	// 5000 msec = 5 sec
#endif
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	D3D_CAP_SRC_L_PRW,
	D3D_CAP_SRC_L_TNR,
	D3D_CAP_SRC_L_OVR,
	D3D_CAP_SRC_R_PRW,
	D3D_CAP_SRC_R_TNR,
	D3D_CAP_SRC_R_OVR,
	D3D_CAP_SRC_S_CVR,
	D3D_CAP_SRC_MAX
} PE_D3D_CAP_SRC_T;

typedef enum {
	D3D_GET_START,
	D3D_GET_END
} PE_D3D_TIME_T;

typedef enum {
	D3D_GET_TIME_HIS,
	D3D_GET_TIME_DEC,
	D3D_GET_TIME_CAP,
	D3D_GET_TIME_MAT,
	D3D_GET_TIME_MAX
} PE_D3D_GET_TIME_T;

typedef enum {
	D3D_WIN_LFT,
	D3D_WIN_RGT,
	D3D_WIN_TOP,
	D3D_WIN_BOT,
	D3D_WIN_MAX
} PE_D3D_WIN_ID_T;

typedef enum {
	D3D_WIN_HIS,
	D3D_WIN_DCE
} PE_D3D_WIN_TYPE_T;

typedef enum {
	D3D_HIS_GRE,
	D3D_HIS_BLU,
	D3D_HIS_RED,
	D3D_HIS_MAX
} PE_D3D_HISTOGRAM_TYPE_T;

typedef enum {
	D3D_STM_HIS_RDY__LR,
	D3D_STM_HIS_RDY_LR1,
	D3D_STM_HIS_RDY_LR2,
	D3D_STM_HIS_RDY_LR3,

	D3D_STM_HIS_SET__LR,
	D3D_STM_HIS_REQ__LR,
	D3D_STM_HIS_GET_LRG,
	D3D_STM_HIS_GET_LRB,
	D3D_STM_HIS_GET_LRR,

	D3D_STM_HIS_TMP,
	D3D_STM_HIS_RDY__TB,
	D3D_STM_HIS_SET__TB,
	D3D_STM_HIS_REQ__TB,
	D3D_STM_HIS_GET_TBG,// = 0xA,
	D3D_STM_HIS_GET_TBB,
	D3D_STM_HIS_GET_TBR,

	D3D_STM_MAX
} PE_D3D_STM_MOD_T;

typedef struct {
	PE_D3D_STM_MOD_T cur_stm;
	PE_D3D_STM_MOD_T nxt_stm;
	PE_WIN_HW_L9_POS win_pos;
} PE_D3D_STM_T;

typedef struct {
	UINT32 complete_flag;

	/* pattern */
	UINT32 tpd;
	UINT32 cb;
	UINT32 cc;
	UINT32 ll;
	UINT32 ssr;
	UINT32 tbr;
	UINT32 ssh;
	UINT32 ssv;	
	UINT32 tbh;
	UINT32 tbv;	
	UINT32 lr_diff;
	UINT32 tb_diff;

	/* LRCR Histogram */
	UINT32 hist_l_g[D3D_MAX_BIN];
	UINT32 hist_r_g[D3D_MAX_BIN];
	UINT32 hist_l_b[D3D_MAX_BIN];
	UINT32 hist_r_b[D3D_MAX_BIN];
	UINT32 hist_l_r[D3D_MAX_BIN];
	UINT32 hist_r_r[D3D_MAX_BIN];
	UINT32 hist_t_g[D3D_MAX_BIN];
	UINT32 hist_b_g[D3D_MAX_BIN];
	UINT32 hist_t_b[D3D_MAX_BIN];
	UINT32 hist_b_b[D3D_MAX_BIN];
	UINT32 hist_t_r[D3D_MAX_BIN];
	UINT32 hist_b_r[D3D_MAX_BIN];
	UINT32 g_diff;
	UINT32 b_diff;
	UINT32 r_diff;

	UINT32 dist_l_g;
	UINT32 dist_r_g;
	UINT32 dist_l_b;
	UINT32 dist_r_b;
	UINT32 dist_l_r;
	UINT32 dist_r_r;

	UINT32 dist_t_g;
	UINT32 dist_b_g;
	UINT32 dist_t_b;
	UINT32 dist_b_b;
	UINT32 dist_t_r;
	UINT32 dist_b_r;

	/* DCE Histogram */	
	UINT32 dce_l[D3D_MAX_BIN];
	UINT32 dce_r[D3D_MAX_BIN];
	UINT32 dce_diff;
	UINT32 dce_diff_delta[D3D_MAX_DCE_DLT];
	UINT32 hist_max_bin_val;
	UINT32 hist_max_bin_num;
	UINT32 hist_diff_sum;
	UINT32 dist_l;
	UINT32 dist_r;

	/* tnr */
	UINT32 motion_l;
	UINT32 motion_r;	
	UINT32 spatial_l;
	UINT32 spatial_r;
	UINT32 apl_l;
	UINT32 apl_r;
	UINT32 nt_l;
	UINT32 nt_r;

	/* disparity from depth controller */
	UINT16 dpt_sbs[8];
	UINT16 dpt_tnb[8];

	/* detection for dual play screen */
	UINT32 hw_fmt;
} PE_D3D_DTA_T;

typedef struct {
	/* disparity from depth controller */
	UINT16 disparity_sbs[8];
	UINT16 disparity_tnb[8];
} PE_D3D_DISPARITY_T;

typedef struct {
	LX_PE_D3D_FORMAT   cur_fmt;
	LX_PE_D3D_FORMAT   tmp_fmt;
	LX_PE_D3D_FORMAT   d3d_fmt;
	LX_PE_D3D_FORMAT   bak_fmt[D3D_MAX_BAK_FMT];
	LX_PE_D3D_FORMAT   dep_fmt; // from depth
	LX_PE_D3D_FORMAT   acc_fmt;	
	BOOLEAN            valid;
	UINT32             validL;
	UINT32             validR;
	UINT32             tpd_flag;
	UINT32             rb_bin_d3d;
	UINT32             sel_alg;
	UINT32             chk_dlt;	
	LX_PE_D3D_DEC      enable;
	LX_PE_OUT_TYPE     out_type;
	LX_PE_3D_IN_TYPE   in_type;
	UINT32             out_win_x;
	UINT32             out_win_y;
	UINT32             act_x0;
	UINT32             act_y0;
	UINT32             act_x1;
	UINT32             act_y1;
	UINT32             tp_mode;		//inner pattern mode
	UINT16             tb_ratio;	//detect ratio for tb, 1024=100%
	UINT16             ss_ratio;	//detect ratio for ss, 1024=100%
	UINT32             mute_en;		//mute on,off state
	UINT32             d3d_chk;		// 0:normal,1:not tb,2:not ss
	LX_PE_D3D_CAP      cap_enb;
	UINT32             cap_h_line_num;
	UINT32             cap_v_line_num;
	UINT32             cap_h_line_width;
	UINT32             cap_v_line_width;

	UINT32             cnt_start;
	UINT32             cnt_2d;
	UINT32             cnt_ss;
	UINT32             cnt_tb;
} PE_D3D_CFG_T;

/**
 *	pe d3d threshold control parameter type
 */
typedef struct {
	UINT32 isDefault;        ///< Is default setting ?
	UINT32 tpd_thr;          ///< for test pattern
	UINT32 ptn_thr;          ///< for cb/cc/ll 
	UINT32 mtn_thr_2d;       ///< for motion check (2D)
	UINT32 mtn_thr_3d;       ///< for motion check	(3D)
	UINT32 fmt_th1;          ///< th1 in algorothm
	UINT32 fmt_th2;          ///< th2 in algorothm 
	UINT32 fmt_th3;	         ///< th3 in algorothm
	UINT32 fmt_th4;          ///< th4 in algorothm
	UINT32 fmt_th5;          ///< th5 in algorothm
	UINT32 fmt_th6;          ///< th6 in algorothm
	UINT32 fmt_th7;          ///< th7 in algorothm
	UINT32 fmt_th8;          ///< th8 in algorothm
	UINT32 fmt_th9;          ///< th9 in algorothm
	UINT32 fmt_th10;         ///< th10 in algorothm
	UINT32 skp_th1;          ///< initial delay for 3D->2D detection (60Hz domain)
	UINT32 skp_th2;          ///< period(ticks) for 3D->2D detection (60Hz domain)
	UINT32 vld_thr;          ///< size of buffer for valid cahek (2D->3D, 3D->2D)
	UINT32 mbv_thr;          ///< hist_max_bin_val
	UINT32 dfs_thr_2d;       ///< hist_diff_sum (2D)
	UINT32 dfs_thr_3d;       ///< hist_diff_sum (3D)
} PE_D3D_THR_T;

typedef struct {
	PE_D3D_CFG_T	cfg;
	PE_D3D_STM_T	stm;
	PE_D3D_DTA_T	dta;
	PE_D3D_THR_T	thr;
} PE_D3D_INFO_T;

#define PE_D3D_MAX_LINE		80//128
#define PE_D3D_MAX_CENTER_LINE	8
#define PE_D3D_MAX_HSIZE	1280
#define PE_D3D_MAX_VSIZE	720
#define PE_D3D_MAX_STRIP_WIDTH	1

#define VIDEO_L9_CODEC_DDR_OFFSET 0x075c4000


typedef struct {
	UINT32 y_base;
	UINT32 c_base;
	UINT32 y_msb;
	UINT32 c_msb;
	UINT32 h;
	UINT32 v;
	UINT32 bpp;
	UINT32 stride;
	UINT32 sub_sample;	// 0:420, 1:422, 2:444
	UINT32 src_valid;
} PE_D3D_OV_INFO_T;

typedef struct {
	UINT8 *pHLine[PE_D3D_MAX_LINE];
	UINT32 h_size;
	UINT32 h_pos_offset;
	UINT32 h_line_num;

	UINT8 *pHLineCenter[PE_D3D_MAX_CENTER_LINE];
	
	UINT8 *pVLine[PE_D3D_MAX_LINE];
	UINT32 v_size;
	UINT32 v_pos_offset;
	UINT32 v_line_num;
} PE_D3D_CAP_INFO_T;

typedef struct {
	UINT32 tick_start_time[D3D_GET_TIME_MAX];
	UINT32 tick_end_time[D3D_GET_TIME_MAX];
} PE_D3D_TIME_INFO_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_D3D_L9_Init(void);
int PE_D3D_L9_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_D3D_L9_DBG_SetThreshold(LX_PE_ETC_DBG_T *pstParams);
int PE_D3D_L9_DBG_GetThreshold(LX_PE_ETC_DBG_T *pstParams);
int PE_D3D_L9_SetD3D(LX_PE_D3D_SETTINGS_T *pstParams);
int PE_D3D_L9_GetD3DInfo(LX_PE_D3D_INFO_T *pstParams);
int PE_D3D_L9_GetDSCInfo(LX_PE_D3D_DSC_INFO_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_D3D_L9_H_ */
