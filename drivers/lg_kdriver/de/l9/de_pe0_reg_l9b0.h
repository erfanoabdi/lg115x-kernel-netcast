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

#ifndef _REG_PE0_L9B0_h
#define _REG_PE0_L9B0_h

/*-----------------------------------------------------------------------------
	0x0400 pe0_load ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load_time                       : 1;	//     0
	UINT32 load_enable                     : 1;	//     1
	UINT32 load_type                       : 1;	//     2
} L9B0_P0L_PE0_LOAD;

/*-----------------------------------------------------------------------------
	0x0404 pe0_intr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_enable                     : 1;	//     0
	UINT32                                 : 3;	//  1: 3 reserved
	UINT32 intr_src                        : 3;	//  4: 6
	UINT32                                 : 9;	//  7:15 reserved
	UINT32 intr_line_pos                   :11;	// 16:26
} L9B0_P0L_PE0_INTR;

/*-----------------------------------------------------------------------------
	0x0408 pe0_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tnr_frame_id                    : 4;	//  0: 3
	UINT32 ipc_frame_id                    : 4;	//  4: 7
	UINT32 tnrw_y_frame_id                 : 4;	//  8:11
	UINT32 tnrw_c_frame_id                 : 4;	// 12:15
	UINT32 dnr_frame_id                    : 8;	// 16:23
	UINT32 pic_init_frame_id               : 4;	// 24:27
} L9B0_P0L_PE0_STATUS0;

/*-----------------------------------------------------------------------------
	0x040c pe0_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 line_cnt                        :11;	//  0:10
} L9B0_P0L_PE0_STATUS1;

/*-----------------------------------------------------------------------------
	0x0410 pe0_opmode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tnr_c_en                        : 1;	//     0
	UINT32 tnr_y_en                        : 1;	//     1
	UINT32 ipc_c_en                        : 1;	//     2
	UINT32 ipc_y_en                        : 1;	//     3
	UINT32 tnr_c_444_as_420                : 1;	//     4
	UINT32 tnr_y2_en                       : 1;	//     5
	UINT32 force_420                       : 1;	//     6
	UINT32                                 : 1;	//     7 reserved
	UINT32 mif_last_mode                   : 3;	//  8:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 detour_enable                   : 1;	//    16
} L9B0_P0L_PE0_OPMODE;

/*-----------------------------------------------------------------------------
	0x0414 pe0_src_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize                           :11;	//  0:10
	UINT32                                 : 2;	// 11:12 reserved
	UINT32 cs_type                         : 3;	// 13:15
	UINT32 vsize                           :12;	// 16:27
	UINT32                                 : 3;	// 28:30 reserved
	UINT32 scan_type                       : 1;	//    31
} L9B0_P0L_PE0_SRC_SIZE;

/*-----------------------------------------------------------------------------
	0x0418 pe0_field ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 field_id                        : 1;	//     0
	UINT32                                 : 3;	//  1: 3 reserved
	UINT32 field_mode                      : 2;	//  4: 5
} L9B0_P0L_PE0_FIELD;

/*-----------------------------------------------------------------------------
	0x041c pe0_param_by_ddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 	                                : 9;	//  0: 8 reserved
	UINT32 stride                          : 2;	//  9:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 vsize                           : 8;	// 16:23
	UINT32                                 : 6;	// 24:29 reserved
	UINT32 endian                          : 1;	//    30
	UINT32 update_by_ddr                   : 1;	//    31
} L9B0_P0L_PE0_PARAM_BY_DDR;

/*-----------------------------------------------------------------------------
	0x0420 win_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y0                              :11;	// 16:26
} L9B0_P0L_WIN_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0424 win_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y1                              :11;	// 16:26
} L9B0_P0L_WIN_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0428 win_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y0                              :11;	// 16:26
	UINT32                                 : 1;	//    27 reserved
	UINT32 ac_bnr_feature_cal_mode         : 2;	// 28:29
} L9B0_P0L_WIN_CTRL_2;

/*-----------------------------------------------------------------------------
	0x042c win_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y1                              :11;	// 16:26
} L9B0_P0L_WIN_CTRL_3;

/*-----------------------------------------------------------------------------
	0x0440 tnr_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tnr_enable                      : 1;	//     0
	UINT32 wa_enable                       : 1;	//     1
	UINT32 nt_lvl_hsub                     : 1;	//     2
	UINT32                                 : 4;	//  3: 6 reserved
	UINT32 frame_skip_enable_for_3d        : 1;	//     7
	UINT32 calc_motion_sample_mode         : 2;	//  8: 9
	UINT32 hist_motion_sample_mode         : 2;	// 10:11
	UINT32 hist_motion_scale               : 2;	// 12:13
	UINT32 calc_motion_flt_enable          : 1;	//    14
	UINT32 calc_motion_flt_type            : 1;	//    15
	UINT32 calc_motion_max_yc              : 1;	//    16
	UINT32 hist_motion_max_yc              : 1;	//    17
	UINT32                                 : 6;	// 18:23 reserved
	UINT32 nt_lvl_adjust_gm_enable         : 1;	//    24
	UINT32 nt_lvl_adjust_lpct_enable       : 1;	//    25
	UINT32 nt_lvl_adjust_xpeak_enable      : 1;	//    26
	UINT32 nt_lvl_adjust_avg_ts_enable     : 1;	//    27
	UINT32 nt_lvl_adjust_lpct_sel          : 1;	//    28
} L9B0_P0L_TNR_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0444 tnr_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_th_lo                         :10;	//  0: 9
	UINT32                                 : 2;	// 10:11 reserved
	UINT32 y_th_hi                         :10;	// 12:21
	UINT32 svar_mux_ctrl                   : 2;	// 22:23
	UINT32 nt_lvl_hist_n_pct               : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0448 tnr_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wa_flat_svar_th                 : 8;	//  0: 7
	UINT32 alpha_lut_ind7                  : 8;	//  8:15
} L9B0_P0L_TNR_CTRL_02;

/*-----------------------------------------------------------------------------
	0x044c tnr_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wa_y0                           : 8;	//  0: 7
	UINT32 wa_y1                           : 8;	//  8:15
	UINT32 wa_x0                           : 8;	// 16:23
	UINT32 wa_x1                           : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0450 tnr_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_gm_y0               : 8;	//  0: 7
	UINT32 nt_lvl_gain_gm_x0               : 8;	//  8:15
	UINT32 nt_lvl_gain_gm_y1               : 8;	// 16:23
	UINT32 nt_lvl_gain_gm_x1               : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0454 tnr_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_min                          : 8;	//  0: 7
	UINT32 nt_max                          : 8;	//  8:15
	UINT32 hist_svar_th                    : 8;	// 16:23
	UINT32 adj_alpha_nt_lvl_th0            : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_05;

/*-----------------------------------------------------------------------------
	0x0458 tnr_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 peak_0_th                       : 8;	//  0: 7
	UINT32 nt_iir_alpha                    : 8;	//  8:15
	UINT32 adj_alpha_k0                    : 8;	// 16:23
	UINT32 adj_alpha_k1                    : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_06;

/*-----------------------------------------------------------------------------
	0x045c tnr_ctrl_07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 alpha_lut_ind0                  : 8;	//  0: 7
	UINT32 alpha_lut_ind1                  : 8;	//  8:15
	UINT32 alpha_lut_ind2                  : 8;	// 16:23
	UINT32 alpha_lut_ind3                  : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_07;

/*-----------------------------------------------------------------------------
	0x0460 tnr_ctrl_08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 alpha_lut_ind4                  : 8;	//  0: 7
	UINT32 alpha_lut_ind5                  : 8;	//  8:15
	UINT32 alpha_lut_ind6                  : 8;	// 16:23
	UINT32 adj_alpha_nt_lvl_th1            : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_08;

/*-----------------------------------------------------------------------------
	0x0464 tnr_ctrl_09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 scene_change_enable             : 1;	//     0
	UINT32 scene_change_max_flt_en         : 1;	//     1
	UINT32 scene_change_measure_sel        : 1;	//     2
	UINT32 scene_change_prev_hist_calc_en  : 1;	//     3
	UINT32 scene_change_enforce            : 1;	//     4
	UINT32                                 : 3;	//  5: 7 reserved
	UINT32 scene_change_max_flt_tap        : 2;	//  8: 9
	UINT32                                 : 2;	// 10:11 reserved
	UINT32 scene_change_scale              : 3;	// 12:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 scene_change_th                 : 8;	// 16:23
} L9B0_P0L_TNR_CTRL_09;

/*-----------------------------------------------------------------------------
	0x0468 tnr_ctrl_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dbg_show_tnr_param              : 4;	//  0: 3
	UINT32 dbg_status_sum_sel              : 2;	//  4: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 dbg_force_wa                    : 1;	//     8
	UINT32 dbg_force_calc_motion           : 1;	//     9
	UINT32 dbg_force_lut_alpha             : 1;	//    10
	UINT32 dbg_force_adj_alpha             : 1;	//    11
	UINT32 dbg_force_final_alpha           : 1;	//    12
	UINT32                                 : 2;	// 13:14 reserved
	UINT32 ignore_active_window            : 1;	//    15
	UINT32 dbg_tnrw_port_ctrl              : 2;	// 16:17
	UINT32                                 : 6;	// 18:23 reserved
	UINT32 dbg_wa                          : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_10;

/*-----------------------------------------------------------------------------
	0x046c tnr_ctrl_11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dbg_calc_motion                 : 8;	//  0: 7
	UINT32 dbg_alpha                       : 8;	//  8:15
} L9B0_P0L_TNR_CTRL_11;

/*-----------------------------------------------------------------------------
	0x0470 tnr_ctrl_12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_gm_y2               : 8;	//  0: 7
	UINT32 nt_lvl_gain_gm_x2               : 8;	//  8:15
	UINT32 nt_lvl_gain_gm_y3               : 8;	// 16:23
	UINT32 nt_lvl_gain_gm_x3               : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_12;

/*-----------------------------------------------------------------------------
	0x0474 tnr_ctrl_13 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 force_nt_lvl                    : 1;	//     0
	UINT32                                 : 7;	//  1: 7 reserved
	UINT32 force_nt_lvl_val                : 8;	//  8:15
	UINT32 adjust_nt_lvl                   : 1;	//    16
	UINT32                                 : 7;	// 17:23 reserved
	UINT32 adjust_nt_lvl_val               : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_13;

/*-----------------------------------------------------------------------------
	0x0478 tnr_ctrl_14 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y0                              :12;	// 16:27
	UINT32                                 : 3;	// 28:30 reserved
	UINT32 noise_measure_win_en            : 1;	//    31
} L9B0_P0L_TNR_CTRL_14;

/*-----------------------------------------------------------------------------
	0x047c tnr_ctrl_15 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y1                              :12;	// 16:27
} L9B0_P0L_TNR_CTRL_15;

/*-----------------------------------------------------------------------------
	0x0480 tnr_ctrl_16 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 show_dbg_bar_ctrl0              : 8;	//  0: 7
	UINT32 show_dbg_bar_ctrl1              : 8;	//  8:15
	UINT32 show_dbg_bar_ctrl2              : 8;	// 16:23
	UINT32 show_dbg_bar_ctrl3              : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_16;

/*-----------------------------------------------------------------------------
	0x0484 tnr_ctrl_17 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 show_dbg_bar_ctrl4              : 8;	//  0: 7
} L9B0_P0L_TNR_CTRL_17;

/*-----------------------------------------------------------------------------
	0x0488 tnr_ctrl_18 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crgn_gain_enable                : 1;	//     0
	UINT32 luma_gain_enable                : 1;	//     1
	UINT32 saturation_gain_enable          : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 input_for_luma                  : 2;	//  4: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 input_for_crgn_satr             : 1;	//     8
	UINT32                                 : 7;	//  9:15 reserved
	UINT32 y_gain                          : 8;	// 16:23
	UINT32 c_gain                          : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_18;

/*-----------------------------------------------------------------------------
	0x048c tnr_ctrl_19 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p0_x                  : 8;	//  0: 7
	UINT32 luma_gain_p1_x                  : 8;	//  8:15
	UINT32 luma_gain_p2_x                  : 8;	// 16:23
	UINT32 luma_gain_p3_x                  : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_19;

/*-----------------------------------------------------------------------------
	0x0490 tnr_ctrl_20 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p4_x                  : 8;	//  0: 7
	UINT32 luma_gain_p5_x                  : 8;	//  8:15
	UINT32 luma_gain_p6_x                  : 8;	// 16:23
	UINT32 luma_gain_p7_x                  : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_20;

/*-----------------------------------------------------------------------------
	0x0494 tnr_ctrl_21 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p0_y                  : 8;	//  0: 7
	UINT32 luma_gain_p1_y                  : 8;	//  8:15
	UINT32 luma_gain_p2_y                  : 8;	// 16:23
	UINT32 luma_gain_p3_y                  : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_21;

/*-----------------------------------------------------------------------------
	0x0498 tnr_ctrl_22 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p4_y                  : 8;	//  0: 7
	UINT32 luma_gain_p5_y                  : 8;	//  8:15
	UINT32 luma_gain_p6_y                  : 8;	// 16:23
	UINT32 luma_gain_p7_y                  : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_22;

/*-----------------------------------------------------------------------------
	0x049c tnr_ctrl_23 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p0_x            : 8;	//  0: 7
	UINT32 saturation_gain_p1_x            : 8;	//  8:15
	UINT32 saturation_gain_p2_x            : 8;	// 16:23
	UINT32 saturation_gain_p3_x            : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_23;

/*-----------------------------------------------------------------------------
	0x04a0 tnr_ctrl_24 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p4_x            : 8;	//  0: 7
	UINT32 saturation_gain_p5_x            : 8;	//  8:15
	UINT32 saturation_gain_p6_x            : 8;	// 16:23
	UINT32 saturation_gain_p7_x            : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_24;

/*-----------------------------------------------------------------------------
	0x04a4 tnr_ctrl_25 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p0_y            : 8;	//  0: 7
	UINT32 saturation_gain_p1_y            : 8;	//  8:15
	UINT32 saturation_gain_p2_y            : 8;	// 16:23
	UINT32 saturation_gain_p3_y            : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_25;

/*-----------------------------------------------------------------------------
	0x04a8 tnr_ctrl_26 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p4_y            : 8;	//  0: 7
	UINT32 saturation_gain_p5_y            : 8;	//  8:15
	UINT32 saturation_gain_p6_y            : 8;	// 16:23
	UINT32 saturation_gain_p7_y            : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_26;

/*-----------------------------------------------------------------------------
	0x04ac tnr_ctrl_27 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crgn_gain_rgn0                  : 8;	//  0: 7
	UINT32 crgn_gain_rgn1                  : 8;	//  8:15
	UINT32 crgn_gain_rgn2                  : 8;	// 16:23
	UINT32 crgn_gain_rgn3                  : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_27;

/*-----------------------------------------------------------------------------
	0x04b0 tnr_ctrl_28 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_st_y0               : 8;	//  0: 7
	UINT32 nt_lvl_gain_st_x0               : 8;	//  8:15
	UINT32 nt_lvl_gain_st_y1               : 8;	// 16:23
	UINT32 nt_lvl_gain_st_x1               : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_28;

/*-----------------------------------------------------------------------------
	0x04b4 tnr_ctrl_29 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wa_y2                           : 8;	//  0: 7
	UINT32 wa_y3                           : 8;	//  8:15
	UINT32 wa_x2                           : 8;	// 16:23
	UINT32 wa_x3                           : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_29;

/*-----------------------------------------------------------------------------
	0x04b8 tnr_ctrl_30 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_st_y2               : 8;	//  0: 7
	UINT32 nt_lvl_gain_st_x2               : 8;	//  8:15
	UINT32 nt_lvl_gain_st_y3               : 8;	// 16:23
	UINT32 nt_lvl_gain_st_x3               : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_30;

/*-----------------------------------------------------------------------------
	0x04bc tnr_ctrl_31 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 spatial_pre_flt_en_c            : 1;	//     0
	UINT32 spatial_pre_flt_en_y            : 1;	//     1
	UINT32                                 :14;	//  2:15 reserved
	UINT32 spatial_pre_flt_th_c            : 8;	// 16:23
	UINT32 spatial_pre_flt_th_y            : 8;	// 24:31
} L9B0_P0L_TNR_CTRL_31;

/*-----------------------------------------------------------------------------
	0x04c0 tnr_status_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x_avg_t                         : 8;	//  0: 7
	UINT32 x_peak_t2                       : 8;	//  8:15
	UINT32 nt_lvl                          : 8;	// 16:23
	UINT32 scene_change                    : 8;	// 24:31
} L9B0_P0L_TNR_STATUS_00;

/*-----------------------------------------------------------------------------
	0x04c4 tnr_status_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x_avg_s                         : 8;	//  0: 7
	UINT32 valid_cnt_motion_histogram      :24;	//  8:31
} L9B0_P0L_TNR_STATUS_01;

/*-----------------------------------------------------------------------------
	0x04c8 tnr_status_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 gm                              : 8;	// 16:23
	UINT32 lp                              : 8;	// 24:31
} L9B0_P0L_TNR_STATUS_02;

/*-----------------------------------------------------------------------------
	0x04cc tnr_status_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sum_of_temp_pel_diff            :29;	//  0:28
} L9B0_P0L_TNR_STATUS_03;

/*-----------------------------------------------------------------------------
	0x04d0 tnr_main_lut_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_lut_indir_addr             : 5;	//  0: 4
	UINT32                                 : 7;	//  5:11 reserved
	UINT32 main_lut_ai_enable              : 1;	//    12
} L9B0_P0L_TNR_MAIN_LUT_00;

/*-----------------------------------------------------------------------------
	0x04d4 tnr_main_lut_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_lut_indir_data0            ;  ;	// 31: 0
} L9B0_P0L_TNR_MAIN_LUT_01;

/*-----------------------------------------------------------------------------
	0x04d8 tnr_main_lut_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_lut_indir_data1            ;  ;	// 31: 0
} L9B0_P0L_TNR_MAIN_LUT_02;

/*-----------------------------------------------------------------------------
	0x04e0 tnr_ctrl_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_lpct_y0             : 8;	//  0: 7
	UINT32 nt_lvl_gain_lpct_x0             : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_lpct_y1             : 8;	// 16:23
	UINT32 nt_lvl_gain_lpct_x1             : 7;	// 24:30
} L9B0_P0L_TNR_CTRL_32;

/*-----------------------------------------------------------------------------
	0x04e4 tnr_ctrl_33 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_lpct_y2             : 8;	//  0: 7
	UINT32 nt_lvl_gain_lpct_x2             : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_lpct_y3             : 8;	// 16:23
	UINT32 nt_lvl_gain_lpct_x3             : 7;	// 24:30
} L9B0_P0L_TNR_CTRL_33;

/*-----------------------------------------------------------------------------
	0x04e8 tnr_ctrl_34 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_xpeak_y0            : 8;	//  0: 7
	UINT32 nt_lvl_gain_xpeak_x0            : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_xpeak_y1            : 8;	// 16:23
	UINT32 nt_lvl_gain_xpeak_x1            : 7;	// 24:30
} L9B0_P0L_TNR_CTRL_34;

/*-----------------------------------------------------------------------------
	0x04ec tnr_ctrl_35 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_xpeak_y2            : 8;	//  0: 7
	UINT32 nt_lvl_gain_xpeak_x2            : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_xpeak_y3            : 8;	// 16:23
	UINT32 nt_lvl_gain_xpeak_x3            : 7;	// 24:30
} L9B0_P0L_TNR_CTRL_35;

/*-----------------------------------------------------------------------------
	0x04f0 tnr_crg_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {

	UINT32 crgn_ctrl_indir_addr            : 8;	//  0: 7
	UINT32                                 : 4;	//  8:11 reserved
	UINT32 crgn_ctrl_ai_enable             : 1;	//    12
} L9B0_P0L_TNR_CRG_CTRL_00;

/*-----------------------------------------------------------------------------
	0x04f4 tnr_crg_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crgn_ctrl_indir_data            ;   	// 31: 0
} L9B0_P0L_TNR_CRG_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0500 ipc_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_mode                       : 2;	//  0: 1
	UINT32                                 : 1;	//     2 reserved
	UINT32 luma_edi                        : 1;	//     3
	UINT32 chroma_mode                     : 2;	//  4: 5
	UINT32                                 : 1;	//     6 reserved
	UINT32 chroma_edi                      : 1;	//     7
	UINT32 chroma_adaptive_va_enable       : 1;	//     8
	UINT32                                 : 1;	//     9 reserved
	UINT32 st_filter_mode                  : 2;	// 10:11
	UINT32                                 :12;	// 12:23 reserved
	UINT32 ipc__fake__v_repeat_va_ta       : 2;	// 24:25
	UINT32                                 : 3;	// 26:28 reserved
	UINT32 film_mode_apply_c               : 1;	//    29
	UINT32 film_mode_apply_y               : 1;	//    30
	UINT32 film_mode_enable                : 1;	//    31
} L9B0_P0L_IPC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0504 ipc_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_fuzzy_margin0                : 8;	//  0: 7
	UINT32 cr_fuzzy_margin1                : 8;	//  8:15
	UINT32                                 : 8;	// 16:23 reserved
	UINT32 cr_tnr_debug_mode               : 1;	//    24
	UINT32 cr_black_mask_origline_when_tnr_: 1;	//    25
	UINT32                                 : 5;	// 26:30 reserved
	UINT32 cr_5f_mode                      : 1;	//    31
} L9B0_P0L_IPC_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0508 ipc_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {

	UINT32 fuzzy_ctrl_point_x0             : 8;	//  0: 7
	UINT32 fuzzy_ctrl_point_x4             : 8;	//  8:15
	UINT32 fuzzy_ctrl_point_x1             : 8;	// 16:23
	UINT32 fuzzy_ctrl_point_y1             : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_02;

/*-----------------------------------------------------------------------------
	0x050c ipc_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fuzzy_ctrl_point_x2             : 8;	//  0: 7
	UINT32 fuzzy_ctrl_point_y2             : 8;	//  8:15
	UINT32 fuzzy_ctrl_point_x3             : 8;	// 16:23
	UINT32 fuzzy_ctrl_point_y3             : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0510 ipc_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 et_offset__s7                   : 8;	//  0: 7
	UINT32 motion_x_tearing_gain           : 8;	//  8:15
	UINT32 tearing_gain                    : 8;	// 16:23
	UINT32 motion_gain                     : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0514 ipc_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_ipc_c_motion_alpha           : 8;	//  0: 7
	UINT32 cr_t_grad_weight                : 8;	//  8:15
	UINT32 cr_v_grad_weight                : 8;	// 16:23
	UINT32 cr_h_grad_weight                : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_05;

/*-----------------------------------------------------------------------------
	0x0518 ipc_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_normalize_en                 : 1;	//     0
	UINT32 cr_flat_only                    : 1;	//     1
	UINT32                                 : 2;	//  2: 3 reserved
	UINT32 cr_tearing_normalize_en         : 1;	//     4
	UINT32                                 : 3;	//  5: 7 reserved
	UINT32 cr_normalize_base               : 8;	//  8:15
	UINT32 cr_normalize_center             : 8;	// 16:23
	UINT32 cr_motion_coring                : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_06;

/*-----------------------------------------------------------------------------
	0x051c ipc_ctrl_07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 1;	//     0 reserved
	UINT32 cr_v_en                         : 1;	//     1
	UINT32 cr_45_en                        : 1;	//     2
	UINT32 cr_15_en                        : 1;	//     3
	UINT32                                 :12;	//  4:15 reserved
	UINT32 cr_postmedian_en                : 1;	//    16
} L9B0_P0L_IPC_CTRL_07;

/*-----------------------------------------------------------------------------
	0x0520 ipc_ctrl_08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd_caption_range_top           :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 fmd_caption_range_bot           :12;	// 16:27
	UINT32                                 : 2;	// 28:29 reserved
	UINT32 caption_flow_detected           : 1;	//    30
	UINT32 hmc_when_cap_not_detected       : 1;	//    31
} L9B0_P0L_IPC_CTRL_08;

/*-----------------------------------------------------------------------------
	0x0524 ipc_ctrl_09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd_vedge_th                    : 7;	//  0: 6
	UINT32 fmd_vedge_en                    : 1;	//     7
	UINT32 fmd_a_th                        : 6;	//  8:13
	UINT32 use_3field_err_t                : 1;	//    14
	UINT32 two_field_delay_mode            : 1;	//    15
	UINT32 fmd_margin_top                  : 8;	// 16:23
	UINT32 fmd_margin_bottom               : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_09;

/*-----------------------------------------------------------------------------
	0x0528 ipc_ctrl_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 film_inter_with                 : 2;	//  0: 1
	UINT32 hw_film_enable                  : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 tearing_detect_strength         : 1;	//     4
	UINT32 cross_check                     : 1;	//     5
	UINT32                                 : 1;	//     6 reserved
	UINT32 usediffpelcount                 : 1;	//     7
	UINT32 pn_diff_th                      : 8;	//  8:15
	UINT32                                 :12;	// 16:27 reserved
	UINT32 scalemeasureforhd               : 2;	// 28:29
	UINT32 loading_time_ctrl               : 1;	//    30
	UINT32 fmd_sw_bad_edit_en              : 1;	//    31
} L9B0_P0L_IPC_CTRL_10;

/*-----------------------------------------------------------------------------
	0x052c ipc_ctrl_11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 repeat_det_line_cnt_th          : 8;	//  0: 7
	UINT32 repeat_det_diff_pel_cnt_th      : 8;	//  8:15
	UINT32 repeat_det_noise_th             : 4;	// 16:19
} L9B0_P0L_IPC_CTRL_11;

/*-----------------------------------------------------------------------------
	0x0530 ipc_ctrl_12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd_32_enable                   : 1;	//     0
	UINT32 fmd_22_enable                   : 1;	//     1
	UINT32 reg_fmd_badediten               : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 fmd_hw_bad_edit_mul_th          : 3;	//  4: 6
	UINT32                                 : 1;	//     7 reserved
	UINT32 fmd_hw_bad_edit_th_min          : 8;	//  8:15
	UINT32 reg_pcn_diff_th                 : 7;	// 16:22
	UINT32 reg_fmd_arbitrary_6_4only       : 1;	//    23
	UINT32 reg_fmd_stillconditition1       : 1;	//    24
	UINT32 reg_fmd_stillconditition2       : 1;	//    25
	UINT32 reg_fmd_arbitrary_still         : 1;	//    26
	UINT32 reg_fmd_arbitrary_3_2only       : 1;	//    27
	UINT32 reg_fmd_still_cntth             : 3;	// 28:30
	UINT32 reg_fmd_still_cntth_en          : 1;	//    31
} L9B0_P0L_IPC_CTRL_12;

/*-----------------------------------------------------------------------------
	0x0534 ipc_ctrl_13 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd32_stillth_pn                : 8;	//  0: 7
	UINT32 fmd32_stillthpcn                : 8;	//  8:15
	UINT32 fmd32_pn_maxvalue_minth0        : 8;	// 16:23
	UINT32 fmd32_pn_maxvalue_minth1        : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_13;

/*-----------------------------------------------------------------------------
	0x0538 ipc_ctrl_14 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd32_min_field_num             : 4;	//  0: 3
	UINT32                                 : 4;	//  4: 7 reserved
	UINT32 fmd32_pn_minvalue_maxth         : 8;	//  8:15
	UINT32 fmd32_pn_maxminratio0           : 4;	// 16:19
	UINT32 fmd32_pn_maxminratio1           : 4;	// 20:23
	UINT32 fmd_32_pcn_small_weight         : 3;	// 24:26
} L9B0_P0L_IPC_CTRL_14;

/*-----------------------------------------------------------------------------
	0x053c ipc_ctrl_15 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fmd22_stillth_pn            : 8;	//  0: 7
	UINT32 reg_fmd22_stillth_pcn           : 8;	//  8:15
	UINT32 reg_bad_edit_sm_min_th          :12;	// 16:27
	// fmd_22_min_val_max_th1 is removed from L9A0
	//UINT32 fmd_22_min_val_max_th1              : 8;   // 31:24
} L9B0_P0L_IPC_CTRL_15;

/*-----------------------------------------------------------------------------
	0x0540 ipc_ctrl_16 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fmd22_minfieldnum0          : 4;	//  0: 3
	UINT32 reg_fmd22_minfieldnum1          : 4;	//  4: 7
	UINT32 reg_fmd22_minvaluemaxth1        : 8;	//  8:15
	UINT32 reg_fmd22_maxvalueminth1        : 8;	// 16:23
	UINT32 reg_fmd22_maxminratio0          : 4;	// 24:27
	UINT32 reg_fmd22_maxminratio1          : 4;	// 28:31
} L9B0_P0L_IPC_CTRL_16;

/*-----------------------------------------------------------------------------
	0x0544 ipc_ctrl_17 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fmd22_maxvalueminth0        : 8;	//  0: 7
	UINT32 reg_fmd22_minvaluemaxth0        : 8;	//  8:15
	UINT32 reg_fmd32_minvaluemaxth0        : 8;	// 16:23
	UINT32 reg_fmd32_maxvalueminth0        : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_17;

/*-----------------------------------------------------------------------------
	0x0548 ipc_ctrl_18 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_ud_gain                      : 8;	//  0: 7
	UINT32 cr_lr_gain                      : 8;	//  8:15
	UINT32 cr_h_grad_gain                  : 8;	// 16:23
	UINT32 cr_v_grad_gain                  : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_18;

/*-----------------------------------------------------------------------------
	0x054c ipc_ctrl_19 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 reg_center_vld_gain             : 4;	// 16:19
	UINT32 reg_diff_vld_gain               : 4;	// 20:23
} L9B0_P0L_IPC_CTRL_19;

/*-----------------------------------------------------------------------------
	0x0550 ipc_status_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pc_cnt                          :16;	//  0:15
	UINT32 nc_cnt                          :16;	// 16:31
} L9B0_P0L_IPC_STATUS_00;

/*-----------------------------------------------------------------------------
	0x0554 ipc_status_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pn_cnt                          :16;	//  0:15
	UINT32 same_cnt                        :16;	// 16:31
} L9B0_P0L_IPC_STATUS_01;

/*-----------------------------------------------------------------------------
	0x0558 ipc_status_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd32_combwith                  : 2;	//  0: 1
	UINT32                                 : 1;	//     2 reserved
	UINT32 fmd32_detected                  : 1;	//     3
	UINT32 fmd32_lockingcnt                : 8;	//  4:11
	UINT32 fmd22_combwith                  : 2;	// 12:13
	UINT32                                 : 1;	//    14 reserved
	UINT32 fmd22_detected                  : 1;	//    15
	UINT32 fmd22_lockingcnt                : 8;	// 16:23
	UINT32 fmd_comb_predict                : 2;	// 24:25
	UINT32 bad_edit_detected__hw           : 1;	//    26
	UINT32 fmd22_still_detected            : 1;	//    27
	UINT32 fmd32_still_detected            : 1;	//    28
	UINT32 repeat_detected                 : 1;	//    29
} L9B0_P0L_IPC_STATUS_02;

/*-----------------------------------------------------------------------------
	0x055c ipc_status_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 fmd_badeditth_hw                :16;	// 16:31
} L9B0_P0L_IPC_STATUS_03;

/*-----------------------------------------------------------------------------
	0x0560 clc_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 1;	//     0 reserved
	UINT32 cl_filter_enable                : 1;	//     1
	UINT32 clc_detection_enable            : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 motion_window                   : 2;	//  4: 5
	UINT32 cl_pattern_dist                 : 2;	//  6: 7
	UINT32 cl_var_protect_en               : 1;	//     8
	UINT32 cl_var_protect_v_mode           : 1;	//     9
	UINT32 cl_var_protect_h_dist           : 2;	// 10:11
	UINT32 cl_ab_ratio                     : 4;	// 12:15
	UINT32 cl_y_hdistance                  : 2;	// 16:17
	UINT32 cl_c_hdistance                  : 2;	// 18:19
	UINT32 cl_y_protect_en                 : 1;	//    20
	UINT32                                 : 7;	// 21:27 reserved
	UINT32 cl_motion_a_filter              : 1;	//    28
	UINT32 cl_motion_b_filter              : 1;	//    29
} L9B0_P0L_CLC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0564 clc_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {

	UINT32 cl_motion_a_th                  : 8;	//  0: 7
	UINT32 cl_motion_b_th                  : 8;	//  8:15
	UINT32 cl_y_protect_th0                : 8;	// 16:23
	UINT32 cl_y_protect_th1                : 8;	// 24:31
} L9B0_P0L_CLC_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0568 clc_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cl_y_bound_th                   : 7;	//  0: 6
	UINT32                                 : 1;	//     7 reserved
	UINT32 cl_c_bound_th                   : 7;	//  8:14
	UINT32 cl_c_bound_type                 : 1;	//    15
	UINT32 cl_y_bound_width_chroma         : 2;	// 16:17
	UINT32 cl_y_bound_ignore_cc            : 1;	//    18
	UINT32 cl_y_bound_ignore_p2            : 1;	//    19
	UINT32 cl_y_bound_ignore_p4            : 1;	//    20
} L9B0_P0L_CLC_CTRL_02;

/*-----------------------------------------------------------------------------
	0x056c clc_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cl_sat_min                      : 8;	//  0: 7
	UINT32 cl_var_h_gain                   : 8;	//  8:15
	UINT32 cl_var_v_gain                   : 8;	// 16:23
	UINT32 cl_var_protect_th               : 8;	// 24:31
} L9B0_P0L_CLC_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0570 clc_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :12;	//  0:11 reserved
	UINT32 cl_frame_min                    :12;	// 12:23
} L9B0_P0L_CLC_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0574 clc_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 clc_c_filter_when_cl_detected   : 1;	//     0
	UINT32                                 : 1;	//     1 reserved
	UINT32 clc_y_filter_when_cc_detected   : 2;	//  2: 3
	UINT32 clc_cc_line_mem_ctrl            : 2;	//  4: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 clc_c_gain                      : 8;	//  8:15
	UINT32 clc_dbg_show_mask               :12;	// 16:27
} L9B0_P0L_CLC_CTRL_05;

/*-----------------------------------------------------------------------------
	0x0578 clc_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cc_c_filter_gain                : 8;	//  0: 7
	UINT32 cc_y_filter_when_cc_detected    : 1;	//     8
} L9B0_P0L_CLC_CTRL_06;

/*-----------------------------------------------------------------------------
	0x057c clc_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cc_detection_count              :16;	//  0:15
	UINT32 cl_detection_count              :16;	// 16:31
} L9B0_P0L_CLC_STAT_00;

/*-----------------------------------------------------------------------------
	0x0580 vflt_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vfilterenable                   : 1;	//     0
	UINT32 vfilterlocalenable              : 1;	//     1
	UINT32 vfilter_strength                : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 cb_filter_y                     : 2;	//  4: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 vfilter_a_th                    : 8;	//  8:15
	UINT32 vfilter_in_field_var            : 8;	// 16:23
	UINT32 vfilter_use_mc_mask             : 1;	//    24
	UINT32 vfilter_expand                  : 1;	//    25
	UINT32 vfilter_center                  : 1;	//    26
	UINT32 vfilter_ul4                     : 1;	//    27
	UINT32 dbgshow_level                   : 2;	// 28:29
	UINT32                                 : 1;	//    30 reserved
	UINT32 dbgshow_enable                  : 1;	//    31
} L9B0_P0L_VFLT_CTRL;

/*-----------------------------------------------------------------------------
	0x0588 mnr_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mnr_enable                      : 1;	//     0
	UINT32 edge_gain_mapping_enable        : 1;	//     1
	UINT32 sel_sd_hd                       : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 debug_mode                      : 3;	//  4: 6
} L9B0_P0L_MNR_CTRL_00;

/*-----------------------------------------------------------------------------
	0x058c mnr_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 hcoef_00                        : 4;	// 16:19
	UINT32 hcoef_01                        : 4;	// 20:23
	UINT32 hcoef_02                        : 4;	// 24:27
	UINT32 hcoef_03                        : 4;	// 28:31
} L9B0_P0L_MNR_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0590 mnr_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hcoef_04                        : 4;	//  0: 3
	UINT32 hcoef_05                        : 4;	//  4: 7
	UINT32 hcoef_06                        : 4;	//  8:11
	UINT32 hcoef_07                        : 4;	// 12:15
	UINT32 hcoef_08                        : 4;	// 16:19
	UINT32 hcoef_09                        : 4;	// 20:23
	UINT32 hcoef_10                        : 4;	// 24:27
	UINT32 hcoef_11                        : 4;	// 28:31
} L9B0_P0L_MNR_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0594 mnr_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hcoef_12                        : 4;	//  0: 3
	UINT32 hcoef_13                        : 4;	//  4: 7
	UINT32 hcoef_14                        : 4;	//  8:11
	UINT32 hcoef_15                        : 4;	// 12:15
	UINT32 hcoef_16                        : 4;	// 16:19
	UINT32                                 : 4;	// 20:23 reserved
	UINT32 x1_position                     : 8;	// 24:31
} L9B0_P0L_MNR_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0598 mnr_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x2_position                     : 8;	//  0: 7
	UINT32 x3_position                     : 8;	//  8:15
	UINT32 x4_position                     : 8;	// 16:23
	UINT32 y1_position                     : 8;	// 24:31
} L9B0_P0L_MNR_CTRL_04;

/*-----------------------------------------------------------------------------
	0x059c mnr_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y2_position                     : 8;	//  0: 7
	UINT32 y3_position                     : 8;	//  8:15
	UINT32 y4_position                     : 8;	// 16:23
	UINT32 filter_threshold                : 8;	// 24:31
} L9B0_P0L_MNR_CTRL_05;

/*-----------------------------------------------------------------------------
	0x05a0 mnr_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vcoef0                          : 4;	//  0: 3
	UINT32 vcoef1                          : 4;	//  4: 7
	UINT32 vcoef2                          : 4;	//  8:11
	UINT32 vcoef3                          : 4;	// 12:15
	UINT32 vcoef4                          : 4;	// 16:19
	UINT32 vcoef5                          : 4;	// 20:23
	UINT32 vcoef6                          : 4;	// 24:27
} L9B0_P0L_MNR_CTRL_06;

/*-----------------------------------------------------------------------------
	0x05a8 vfilter_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_vfilter_global_en            : 1;	//     0
	UINT32 cr_vfilter_force_en             : 1;	//     1
	UINT32 cr_global_frame_num_th          : 4;	//  2: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 cr_vfilter_global_th            :12;	//  8:19
	UINT32 tearing_count                   :12;	// 20:31
} L9B0_P0L_VFILTER_01;

/*-----------------------------------------------------------------------------
	0x05ac bnr_dc_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dc_bnr_enable                   : 1;	//     0
	UINT32 ac_blockiness_adaptive_mode     : 1;	//     1
	UINT32                                 : 1;	//     2 reserved
	UINT32 motion_gain_enable              : 1;	//     3
	UINT32 sd_hd_sel                       : 1;	//     4
	UINT32 output_mux                      : 3;	//  5: 7
	UINT32 motion_min                      : 4;	//  8:11
	UINT32 motion_max                      : 4;	// 12:15
} L9B0_P0L_BNR_DC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x05b0 bnr_dc_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 blur_enable                     : 2;	//  0: 1
	UINT32                                 :26;	//  2:27 reserved
	UINT32 ac_blockiness_multifly_x_n      : 4;	// 28:31
} L9B0_P0L_BNR_DC_CTRL_01;

/*-----------------------------------------------------------------------------
	0x05b4 bnr_dc_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dc_bnr_gain_ctrl_y2             : 8;	//  0: 7
	UINT32 dc_bnr_gain_ctrl_x2             : 8;	//  8:15
	UINT32 dc_bnr_gain_ctrl_y3             : 8;	// 16:23
	UINT32 dc_bnr_gain_ctrl_x3             : 8;	// 24:31
} L9B0_P0L_BNR_DC_CTRL_02;

/*-----------------------------------------------------------------------------
	0x05b8 bnr_dc_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dc_bnr_gain_ctrl_y0             : 8;	//  0: 7
	UINT32 dc_bnr_gain_ctrl_x0             : 8;	//  8:15
	UINT32 dc_bnr_gain_ctrl_y1             : 8;	// 16:23
	UINT32 dc_bnr_gain_ctrl_x1             : 8;	// 24:31
} L9B0_P0L_BNR_DC_CTRL_03;

/*-----------------------------------------------------------------------------
	0x05bc bnr_ac_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 ac_bnr_protect_motion_max       : 8;	// 16:23
	UINT32 ac_bnr_protect_motion_min       : 8;	// 24:31
} L9B0_P0L_BNR_AC_CTRL_06;

/*-----------------------------------------------------------------------------
	0x05c0 bnr_ac_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 bnr_h_en                        : 1;	//     0
	UINT32 bnr_v_en                        : 1;	//     1
	UINT32 motion_protect_enable           : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 source_type                     : 1;	//     4
	UINT32 status_read_type                : 1;	//     5
	UINT32 status_read_mode                : 2;	//  6: 7
	UINT32 hbmax_gain                      : 4;	//  8:11
	UINT32 vbmax_gain                      : 4;	// 12:15
	UINT32 strength_resolution             : 1;	//    16
	UINT32                                 : 3;	// 17:19 reserved
	UINT32 fiter_type                      : 1;	//    20
	UINT32                                 : 3;	// 21:23 reserved
	UINT32 output_mux                      : 2;	// 24:25
} L9B0_P0L_BNR_AC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x05c4 bnr_ac_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 strength_h_x0                   : 8;	//  0: 7
	UINT32 strength_h_x1                   : 8;	//  8:15
	UINT32 strength_h_max                  : 8;	// 16:23
	UINT32 detect_min_th                   : 8;	// 24:31
} L9B0_P0L_BNR_AC_CTRL_01;

/*-----------------------------------------------------------------------------
	0x05c8 bnr_ac_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 strength_v_x0                   : 8;	//  0: 7
	UINT32 strength_v_x1                   : 8;	//  8:15
	UINT32 strength_v_max                  : 8;	// 16:23
} L9B0_P0L_BNR_AC_CTRL_02;

/*-----------------------------------------------------------------------------
	0x05cc bnr_ac_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_offset_mode                   : 1;	//     0
	UINT32 manual_offset_h_value           : 3;	//  1: 3
	UINT32 v_offset_mode                   : 1;	//     4
	UINT32 manual_offset_v_value           : 3;	//  5: 7
	UINT32 use_of_hysterisis               : 4;	//  8:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 t_filter_weight                 : 8;	// 16:23
} L9B0_P0L_BNR_AC_CTRL_03;

/*-----------------------------------------------------------------------------
	0x05d0 bnr_ac_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 max_delta_th0                   : 8;	//  0: 7
	UINT32 max_delta_th1                   : 8;	//  8:15
	UINT32 h_blockness_th                  : 8;	// 16:23
	UINT32 h_weight_max                    : 8;	// 24:31
} L9B0_P0L_BNR_AC_CTRL_04;

/*-----------------------------------------------------------------------------
	0x05d4 bnr_ac_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 use_of_hysterisis               : 4;	//  0: 3
	UINT32 block_boundary_processing_type  : 1;	//     4
} L9B0_P0L_BNR_AC_CTRL_05;

/*-----------------------------------------------------------------------------
	0x05d8 dnr_max_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 enable_snr                      : 1;	//     0
	UINT32 enable_mnr                      : 1;	//     1
	UINT32 enable_der                      : 1;	//     2
	UINT32 enable_dc_bnr                   : 1;	//     3
	UINT32 enable_ac_bnr                   : 1;	//     4
	UINT32                                 : 3;	//  5: 7 reserved
	UINT32 debug_enable                    : 1;	//     8
	UINT32 debug_mode                      : 1;	//     9
	UINT32 debug_snr_enable                : 1;	//    10
	UINT32 debug_mnr_enable                : 1;	//    11
	UINT32 debug_der_enable                : 1;	//    12
	UINT32 debug_dc_bnr_enable             : 1;	//    13
	UINT32 debug_ac_bnr_enable             : 1;	//    14
	UINT32                                 : 1;	//    15 reserved
	UINT32 win_control_enable              : 1;	//    16
	UINT32 border_enable                   : 1;	//    17
} L9B0_P0L_DNR_MAX_CTRL;

/*-----------------------------------------------------------------------------
	0x05dc dnr_dbar_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 debug_bar_en                    : 1;	//     0
	UINT32                                 : 1;	//     1 reserved
	UINT32 show_debug_bar_for_bnr          : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 gain                            : 3;	//  4: 6
	UINT32                                 : 1;	//     7 reserved
	UINT32 sd_hd_sel                       : 2;	//  8: 9
} L9B0_P0L_DNR_DBAR_CTRL;

/*-----------------------------------------------------------------------------
	0x05e0 bnr_stat_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ac_bnr_h_status                 : 8;	//  0: 7
	UINT32 ac_bnr_v_status                 : 8;	//  8:15
	UINT32 dc_bnr_th                       :14;	// 16:29
} L9B0_P0L_BNR_STAT_0;

/*-----------------------------------------------------------------------------
	0x05e4 der_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 der_en                          : 1;	//     0
	UINT32                                 : 1;	//     1 reserved
	UINT32 gain2weight_mapping             : 1;	//     2
	UINT32 bif_en                          : 1;	//     3
	UINT32 out_mux                         : 4;	//  4: 7
	UINT32 bif_th                          : 8;	//  8:15
} L9B0_P0L_DER_CTRL_0;

/*-----------------------------------------------------------------------------
	0x05e8 der_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gain_th0                        : 8;	//  0: 7
	UINT32 gain_th1                        : 8;	//  8:15
} L9B0_P0L_DER_CTRL_1;

/*-----------------------------------------------------------------------------
	0x05f0 ipc_ctrl_20 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_lock_dir_sel                 : 1;	//     0
	UINT32                                 : 7;	//  1: 7 reserved
	UINT32 cr_center_ratio                 : 4;	//  8:11
	UINT32 cr_lr_diff_ratio                : 4;	// 12:15
	UINT32 cr_hmc_lock_filt_sizeh          : 3;	// 16:18
} L9B0_P0L_IPC_CTRL_20;

/*-----------------------------------------------------------------------------
	0x05f4 ipc_ctrl_21 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_lock_point_add               : 8;	//  0: 7
	UINT32 cr_lock_point_penalty           : 8;	//  8:15
	UINT32 cr_lock_point_valid             : 8;	// 16:23
	UINT32                                 : 6;	// 24:29 reserved
	UINT32 cr_robustness                   : 2;	// 30:31
} L9B0_P0L_IPC_CTRL_21;

/*-----------------------------------------------------------------------------
	0x05f8 ipc_ctrl_22 ''
------------------------------------------------------------------------------*/
/*	UINT32 no field */

/*-----------------------------------------------------------------------------
	0x05fc ipc_ctrl_23 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_global_tbm_en               : 1;	//     0
	UINT32 reg_flim_panelty_en             : 1;	//     1
	UINT32                                 : 2;	//  2: 3 reserved
	UINT32 reg_es_offset_mode              : 1;	//     4
	UINT32 reg_err_mode                    : 1;	//     5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 reg_global_tbm_th               : 8;	//  8:15
	UINT32 reg_hmc_2d_gain                 : 8;	// 16:23
	UINT32 reg_errs_limit                  : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_23;

/*-----------------------------------------------------------------------------
	0x0600 ipc_ctrl_24 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_errs_gain                   : 8;	//  0: 7
	UINT32 reg_confidance_gain             : 8;	//  8:15
	UINT32 reg_2d_offset                   : 8;	// 16:23
} L9B0_P0L_IPC_CTRL_24;

/*-----------------------------------------------------------------------------
	0x0604 ipc_ctrl_25 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cubic_coef0                 : 8;	//  0: 7
	UINT32 reg_cubic_coef1                 : 8;	//  8:15
	UINT32 reg_cubic_coef2                 : 8;	// 16:23
	UINT32 reg_cubic_coef3                 : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_25;

/*-----------------------------------------------------------------------------
	0x0608 ipc_ctrl_26 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_va_cubic                    : 1;	//     0
	UINT32 reg_boundary_window             : 1;	//     1
	UINT32 reg_force_va                    : 1;	//     2
	UINT32 reg_half_pel_va                 : 1;	//     3
	UINT32 reg_dir_med_tap                 : 2;	//  4: 5
	UINT32 reg_diff_med_tap                : 2;	//  6: 7
	UINT32 reg_va_blending_ctrl1           : 3;	//  8:10
	UINT32 reg_wide_angle_protection_1     : 1;	//    11
	UINT32 reg_va_blending_ctrl2           : 3;	// 12:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 reg_errs_chroma_blend_gain      : 8;	// 16:23
	UINT32 reg_strong_global_th            : 6;	// 24:29
	UINT32 narrow_angle_week               : 1;	//    30
	UINT32 narrow_angle_protection         : 1;	//    31
} L9B0_P0L_IPC_CTRL_26;

/*-----------------------------------------------------------------------------
	0x060c ipc_ctrl_27 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dbg_show_mode                   : 5;	//  0: 4
	UINT32                                 : 6;	//  5:10 reserved
	UINT32 dbg_show_black_mask             : 1;	//    11
	UINT32 dbg_pprv_to_curr                : 1;	//    12
	UINT32 dbg_prv3_to_prev                : 1;	//    13
	UINT32 dbg_curr_to_pprv                : 1;	//    14
	UINT32                                 : 1;	//    15 reserved
	UINT32 st_flt_ctrl_x0                  : 8;	// 16:23
	UINT32 st_flt_ctrl_x1                  : 8;	// 24:31
} L9B0_P0L_IPC_CTRL_27;

/*-----------------------------------------------------------------------------
	0x0640 tpd_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_tpd_en                      : 1;	//     0
	UINT32                                 : 1;	//     1 reserved
	UINT32 reg_win_mode                    : 1;	//     2
	UINT32                                 :12;	//  3:14 reserved
	UINT32 reg_quick_out                   : 1;	//    15
	UINT32 reg_tpd_th_s_vl                 : 8;	// 16:23
	UINT32 reg_tpd_th_s_vh                 : 8;	// 24:31
} L9B0_P0L_TPD_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0644 tpd_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :12;	//  0:11
	UINT32                                 : 3;	// 12:14 reserved
	UINT32 reg_win_tpd_hen                 : 1;	//    15
	UINT32 y0                              :12;	// 16:27
	UINT32                                 : 3;	// 28:30 reserved
	UINT32 reg_win_tpd_ven                 : 1;	//    31
} L9B0_P0L_TPD_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0648 tpd_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y1                              :12;	// 16:27
} L9B0_P0L_TPD_CTRL_02;

/*-----------------------------------------------------------------------------
	0x064c tpd_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_tpd_th_vl                   : 8;	//  0: 7
	UINT32 reg_tpd_th_vh                   : 8;	//  8:15
	UINT32 reg_vh_valid_th                 : 8;	// 16:23
	UINT32 reg_vh_max_th                   : 8;	// 24:31
} L9B0_P0L_TPD_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0650 tpd_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_tpd_th_s                    : 8;	//  0: 7
	UINT32 reg_sv_valid_th                 : 8;	//  8:15
	UINT32 reg_vl_valid_th                 : 8;	// 16:23
	UINT32 reg_vl_max_th                   : 8;	// 24:31
} L9B0_P0L_TPD_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0654 tpd_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_mid_level                   :10;	//  0: 9
	UINT32                                 : 6;	// 10:15 reserved
	UINT32 reg_tpd_th_sv_vl                : 8;	// 16:23
	UINT32 reg_tpd_th_sv_vh                : 8;	// 24:31
} L9B0_P0L_TPD_CTRL_05;

/*-----------------------------------------------------------------------------
	0x0658 tpd_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 4;	//  0: 3 reserved
	UINT32 reg_mux_3                       : 4;	//  4: 7
	UINT32                                 : 4;	//  8:11 reserved
	UINT32 reg_mux_2                       : 4;	// 12:15
	UINT32                                 : 4;	// 16:19 reserved
	UINT32 reg_mux_1                       : 4;	// 20:23
	UINT32 reg_show_scale                  : 3;	// 24:26
	UINT32 reg_bbd_show                    : 1;	//    27
	UINT32 reg_show_bar_1                  : 1;	//    28
	UINT32 reg_show_bar_2                  : 1;	//    29
	UINT32 reg_show_bar_3                  : 1;	//    30
	UINT32 reg_show_bar_4                  : 1;	//    31
} L9B0_P0L_TPD_CTRL_06;

/*-----------------------------------------------------------------------------
	0x065c tpd_ctrl_07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 4;	//  0: 3 reserved
	UINT32 reg_mux_4                       : 4;	//  4: 7
	UINT32 reg_hys_mode                    : 6;	//  8:13
	UINT32                                 : 2;	// 14:15 reserved
	UINT32 reg_tpd_th_s_sv                 : 5;	// 16:20
	UINT32                                 : 3;	// 21:23 reserved
	UINT32 reg_tpd_th_sv                   : 5;	// 24:28
} L9B0_P0L_TPD_CTRL_07;

/*-----------------------------------------------------------------------------
	0x0660 tpd_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_tpd_value                   : 1;	//     0
	UINT32 reg_tpd_by_s                    : 1;	//     1
	UINT32 reg_tpd_by_vl                   : 1;	//     2
	UINT32 reg_tpd_by_vh                   : 1;	//     3
	UINT32 reg_tpd_by_vl_max               : 1;	//     4
	UINT32 reg_tpd_by_vh_max               : 1;	//     5
	UINT32 reg_tpd_by_s_vl                 : 1;	//     6
	UINT32 reg_tpd_by_s_vh                 : 1;	//     7
	UINT32 reg_s_status                    : 8;	//  8:15
	UINT32 reg_vl_status                   : 8;	// 16:23
	UINT32 reg_vh_status                   : 8;	// 24:31
} L9B0_P0L_TPD_STAT_00;

/*-----------------------------------------------------------------------------
	0x0664 tpd_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_tpd_by_sv                   : 1;	//     0
	UINT32 reg_tpd_by_sv_vl                : 1;	//     1
	UINT32 reg_tpd_by_sv_vh                : 1;	//     2
	UINT32 reg_tpd_by_s_sv                 : 1;	//     3
	UINT32 reg_hys_tpd_value               : 1;	//     4
	UINT32                                 : 3;	//  5: 7 reserved
	UINT32 reg_sv_status                   : 5;	//  8:12
} L9B0_P0L_TPD_STAT_01;

/*-----------------------------------------------------------------------------
	0x0670 bbd_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_bbd_en                      : 1;	//     0
	UINT32 reg_hys_mode                    : 5;	//  1: 5
	UINT32 reg_op_mode                     : 1;	//     6
	UINT32                                 : 1;	//     7 reserved
	UINT32 reg_cnt_th                      : 8;	//  8:15
	UINT32 reg_diff_th                     : 8;	// 16:23
	UINT32 reg_bbd_mux                     : 3;	// 24:26
	UINT32                                 : 1;	//    27 reserved
	UINT32 reg_apl_mux                     : 3;	// 28:30
} L9B0_P0L_BBD_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0674 bbd_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y0                              :12;	// 16:27
} L9B0_P0L_BBD_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0678 bbd_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y1                              :12;	// 16:27
} L9B0_P0L_BBD_CTRL_02;

/*-----------------------------------------------------------------------------
	0x067c bbd_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y0                              :12;	// 16:27
} L9B0_P0L_BBD_STAT_00;

/*-----------------------------------------------------------------------------
	0x0680 bbd_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y1                              :12;	// 16:27
} L9B0_P0L_BBD_STAT_01;

/*-----------------------------------------------------------------------------
	0x0684 apl_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 apl_stat_00                     :10;	//  0: 9
} L9B0_P0L_APL_STAT_00;

/*-----------------------------------------------------------------------------
	0x0690 cti_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cti_enable                      : 1;	//     0
	UINT32 cti_repeat_en                   : 1;	//     1
	UINT32 cti_clipping_en                 : 1;	//     2
	UINT32                                 :13;	//  3:15 reserved
	UINT32 cti_gain                        : 8;	// 16:23
	UINT32 cb_filter_c                     : 2;	// 24:25
} L9B0_P0L_CTI_CTRL_00;

/*-----------------------------------------------------------------------------
	0x06a0 3dfd_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aw_offset_x                     : 8;	//  0: 7
	UINT32 aw_offset_y                     : 8;	//  8:15
	UINT32 cb_th1                          : 8;	// 16:23
	UINT32 cb_th2                          : 8;	// 24:31
} L9B0_P0L_3DFD_CTRL_00;

/*-----------------------------------------------------------------------------
	0x06a4 3dfd_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cc_th1                          : 8;	//  0: 7
	UINT32 cc_th2                          : 8;	//  8:15
	UINT32 ll_th1                          : 8;	// 16:23
	UINT32 ll_th2                          : 8;	// 24:31
} L9B0_P0L_3DFD_CTRL_01;

/*-----------------------------------------------------------------------------
	0x06a8 3dfd_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pt_th                           :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 sstb_th                         : 8;	// 16:23
	UINT32 debug_mode                      : 3;	// 24:26
	UINT32                                 : 1;	//    27 reserved
	UINT32 div_mode                        : 1;	//    28
} L9B0_P0L_3DFD_CTRL_02;

/*-----------------------------------------------------------------------------
	0x06ac 3dfd_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 small_delta_th                  :19;	//  0:18
	UINT32                                 : 5;	// 19:23 reserved
	UINT32 small_delta_en                  : 1;	//    24
} L9B0_P0L_3DFD_CTRL_03;

/*-----------------------------------------------------------------------------
	0x06b0 3dfd_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cb_count                        :16;	//  0:15
	UINT32 cc_count                        :16;	// 16:31
} L9B0_P0L_3DFD_STAT_00;

/*-----------------------------------------------------------------------------
	0x06b4 3dfd_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ll_count                        :16;	//  0:15
	UINT32 tridfd_format                   : 4;     // 16:19
} L9B0_P0L_3DFD_STAT_01;

/*-----------------------------------------------------------------------------
	0x06b8 3dfd_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 delta_ss_h                      :23;	//  0:22
} L9B0_P0L_3DFD_STAT_02;

/*-----------------------------------------------------------------------------
	0x06bc 3dfd_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 delta_ss_v                      :23;	//  0:22
} L9B0_P0L_3DFD_STAT_03;

/*-----------------------------------------------------------------------------
	0x06c0 3dfd_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 delta_tb_v                      :23;	//  0:22
} L9B0_P0L_3DFD_STAT_04;

/*-----------------------------------------------------------------------------
	0x06c4 3dfd_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 delta_tb_h                      :23;	//  0:22
} L9B0_P0L_3DFD_STAT_05;

/*-----------------------------------------------------------------------------
	0x06c8 3dfd_stat_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ss_ratio                        :23;	//  0:22
} L9B0_P0L_3DFD_STAT_06;

/*-----------------------------------------------------------------------------
	0x06cc 3dfd_stat_07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tb_ratio                        :23;	//  0:22
} L9B0_P0L_3DFD_STAT_07;

/*-----------------------------------------------------------------------------
	0x2400 pe0_load ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load_time                       : 1;	//     0
	UINT32 load_enable                     : 1;	//     1
	UINT32 load_type                       : 1;	//     2
} L9B0_P0R_PE0_LOAD;

/*-----------------------------------------------------------------------------
	0x2404 pe0_intr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_enable                     : 1;	//     0
	UINT32                                 : 3;	//  1: 3 reserved
	UINT32 intr_src                        : 3;	//  4: 6
	UINT32                                 : 9;	//  7:15 reserved
	UINT32 intr_line_pos                   :11;	// 16:26
} L9B0_P0R_PE0_INTR;

/*-----------------------------------------------------------------------------
	0x2408 pe0_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tnr_frame_id                    : 4;	//  0: 3
	UINT32 ipc_frame_id                    : 4;	//  4: 7
	UINT32 tnrw_y_frame_id                 : 4;	//  8:11
	UINT32 tnrw_c_frame_id                 : 4;	// 12:15
	UINT32 dnr_frame_id                    : 8;	// 16:23
	UINT32 pic_init_frame_id               : 4;	// 24:27
} L9B0_P0R_PE0_STATUS0;

/*-----------------------------------------------------------------------------
	0x240c pe0_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 line_cnt                        :11;	//  0:10
} L9B0_P0R_PE0_STATUS1;

/*-----------------------------------------------------------------------------
	0x2410 pe0_opmode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tnr_c_en                        : 1;	//     0
	UINT32 tnr_y_en                        : 1;	//     1
	UINT32 ipc_c_en                        : 1;	//     2
	UINT32 ipc_y_en                        : 1;	//     3
	UINT32 tnr_c_444_as_420                : 1;	//     4
	UINT32 tnr_y2_en                       : 1;	//     5
	UINT32 force_420                       : 1;	//     6
	UINT32                                 : 1;	//     7 reserved
	UINT32 mif_last_mode                   : 3;	//  8:10
	UINT32                                 : 1;	//    11 reserved
	UINT32 ipc_force_44x                   : 1;	//    12
	UINT32                                 : 3;	// 13:15 reserved
	UINT32 detour_enable                   : 1;	//    16
} L9B0_P0R_PE0_OPMODE;

/*-----------------------------------------------------------------------------
	0x2414 pe0_src_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize                           :11;	//  0:10
	UINT32                                 : 2;	// 11:12 reserved
	UINT32 cs_type                         : 3;	// 13:15
	UINT32 vsize                           :12;	// 16:27
	UINT32                                 : 3;	// 28:30 reserved
	UINT32 scan_type                       : 1;	//    31
} L9B0_P0R_PE0_SRC_SIZE;

/*-----------------------------------------------------------------------------
	0x2418 pe0_field ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 field_id                        : 1;	//     0
	UINT32                                 : 3;	//  1: 3 reserved
	UINT32 field_mode                      : 2;	//  4: 5
} L9B0_P0R_PE0_FIELD;

/*-----------------------------------------------------------------------------
	0x241c pe0_param_by_ddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 9;	//  0: 8 reserved
	UINT32 stride                          : 2;	//  9:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 vsize                           : 8;	// 16:23
	UINT32                                 : 6;	// 24:29 reserved
	UINT32 endian                          : 1;	//    30
	UINT32 update_by_ddr                   : 1;	//    31
} L9B0_P0R_PE0_PARAM_BY_DDR;

/*-----------------------------------------------------------------------------
	0x2420 win_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y0                              :11;	// 16:26
} L9B0_P0R_WIN_CTRL_0;

/*-----------------------------------------------------------------------------
	0x2424 win_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y1                              :11;	// 16:26
} L9B0_P0R_WIN_CTRL_1;

/*-----------------------------------------------------------------------------
	0x2428 win_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y0                              :11;	// 16:26
	UINT32                                 : 1;	//    27 reserved
	UINT32 ac_bnr_feature_cal_mode         : 2;	// 28:29
} L9B0_P0R_WIN_CTRL_2;

/*-----------------------------------------------------------------------------
	0x242c win_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y1                              :11;	// 16:26
} L9B0_P0R_WIN_CTRL_3;

/*-----------------------------------------------------------------------------
	0x2440 tnr_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tnr_enable                      : 1;	//     0
	UINT32 wa_enable                       : 1;	//     1
	UINT32 nt_lvl_hsub                     : 1;	//     2
	UINT32                                 : 4;	//  3: 6 reserved
	UINT32 frame_skip_enable_for_3d        : 1;	//     7
	UINT32 calc_motion_sample_mode         : 2;	//  8: 9
	UINT32 hist_motion_sample_mode         : 2;	// 10:11
	UINT32 hist_motion_scale               : 2;	// 12:13
	UINT32 calc_motion_flt_enable          : 1;	//    14
	UINT32 calc_motion_flt_type            : 1;	//    15
	UINT32 calc_motion_max_yc              : 1;	//    16
	UINT32 hist_motion_max_yc              : 1;	//    17
	UINT32                                 : 6;	// 18:23 reserved
	UINT32 nt_lvl_adjust_gm_enable         : 1;	//    24
	UINT32 nt_lvl_adjust_lpct_enable       : 1;	//    25
	UINT32 nt_lvl_adjust_xpeak_enable      : 1;	//    26
	UINT32 nt_lvl_adjust_avg_ts_enable     : 1;	//    27
	UINT32 nt_lvl_adjust_lpct_sel          : 1;	//    28
} L9B0_P0R_TNR_CTRL_00;

/*-----------------------------------------------------------------------------
	0x2444 tnr_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_th_lo                         :10;	//  0: 9
	UINT32                                 : 2;	// 10:11 reserved
	UINT32 y_th_hi                         :10;	// 12:21
	UINT32 svar_mux_ctrl                   : 2;	// 22:23
	UINT32 nt_lvl_hist_n_pct               : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_01;

/*-----------------------------------------------------------------------------
	0x2448 tnr_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wa_flat_svar_th                 : 8;	//  0: 7
	UINT32 alpha_lut_ind7                  : 8;	//  8:15
} L9B0_P0R_TNR_CTRL_02;

/*-----------------------------------------------------------------------------
	0x244c tnr_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wa_y0                           : 8;	//  0: 7
	UINT32 wa_y1                           : 8;	//  8:15
	UINT32 wa_x0                           : 8;	// 16:23
	UINT32 wa_x1                           : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_03;

/*-----------------------------------------------------------------------------
	0x2450 tnr_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_gm_y0               : 8;	//  0: 7
	UINT32 nt_lvl_gain_gm_x0               : 8;	//  8:15
	UINT32 nt_lvl_gain_gm_y1               : 8;	// 16:23
	UINT32 nt_lvl_gain_gm_x1               : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_04;

/*-----------------------------------------------------------------------------
	0x2454 tnr_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_min                          : 8;	//  0: 7
	UINT32 nt_max                          : 8;	//  8:15
	UINT32 hist_svar_th                    : 8;	// 16:23
	UINT32 adj_alpha_nt_lvl_th0            : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_05;

/*-----------------------------------------------------------------------------
	0x2458 tnr_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 peak_0_th                       : 8;	//  0: 7
	UINT32 nt_iir_alpha                    : 8;	//  8:15
	UINT32 adj_alpha_k0                    : 8;	// 16:23
	UINT32 adj_alpha_k1                    : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_06;

/*-----------------------------------------------------------------------------
	0x245c tnr_ctrl_07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 alpha_lut_ind0                  : 8;	//  0: 7
	UINT32 alpha_lut_ind1                  : 8;	//  8:15
	UINT32 alpha_lut_ind2                  : 8;	// 16:23
	UINT32 alpha_lut_ind3                  : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_07;

/*-----------------------------------------------------------------------------
	0x2460 tnr_ctrl_08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 alpha_lut_ind4                  : 8;	//  0: 7
	UINT32 alpha_lut_ind5                  : 8;	//  8:15
	UINT32 alpha_lut_ind6                  : 8;	// 16:23
	UINT32 adj_alpha_nt_lvl_th1            : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_08;

/*-----------------------------------------------------------------------------
	0x2464 tnr_ctrl_09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 scene_change_enable             : 1;	//     0
	UINT32 scene_change_max_flt_en         : 1;	//     1
	UINT32 scene_change_measure_sel        : 1;	//     2
	UINT32 scene_change_prev_hist_calc_en  : 1;	//     3
	UINT32 scene_change_enforce            : 1;	//     4
	UINT32                                 : 3;	//  5: 7 reserved
	UINT32 scene_change_max_flt_tap        : 2;	//  8: 9
	UINT32                                 : 2;	// 10:11 reserved
	UINT32 scene_change_scale              : 3;	// 12:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 scene_change_th                 : 8;	// 16:23
} L9B0_P0R_TNR_CTRL_09;

/*-----------------------------------------------------------------------------
	0x2468 tnr_ctrl_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dbg_show_tnr_param              : 4;	//  0: 3
	UINT32 dbg_status_sum_sel              : 2;	//  4: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 dbg_force_wa                    : 1;	//     8
	UINT32 dbg_force_calc_motion           : 1;	//     9
	UINT32 dbg_force_lut_alpha             : 1;	//    10
	UINT32 dbg_force_adj_alpha             : 1;	//    11
	UINT32 dbg_force_final_alpha           : 1;	//    12
	UINT32                                 : 2;	// 13:14 reserved
	UINT32 ignore_active_window            : 1;	//    15
	UINT32 dbg_tnrw_port_ctrl              : 2;	// 16:17
	UINT32                                 : 6;	// 18:23 reserved
	UINT32 dbg_wa                          : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_10;

/*-----------------------------------------------------------------------------
	0x246c tnr_ctrl_11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dbg_calc_motion                 : 8;	//  0: 7
	UINT32 dbg_alpha                       : 8;	//  8:15
} L9B0_P0R_TNR_CTRL_11;

/*-----------------------------------------------------------------------------
	0x2470 tnr_ctrl_12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_gm_y2               : 8;	//  0: 7
	UINT32 nt_lvl_gain_gm_x2               : 8;	//  8:15
	UINT32 nt_lvl_gain_gm_y3               : 8;	// 16:23
	UINT32 nt_lvl_gain_gm_x3               : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_12;

/*-----------------------------------------------------------------------------
	0x2474 tnr_ctrl_13 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 force_nt_lvl                    : 1;	//     0
	UINT32                                 : 7;	//  1: 7 reserved
	UINT32 force_nt_lvl_val                : 8;	//  8:15
	UINT32 adjust_nt_lvl                   : 1;	//    16
	UINT32                                 : 7;	// 17:23 reserved
	UINT32 adjust_nt_lvl_val               : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_13;

/*-----------------------------------------------------------------------------
	0x2478 tnr_ctrl_14 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y0                              :12;	// 16:27
	UINT32                                 : 3;	// 28:30 reserved
	UINT32 noise_measure_win_en            : 1;	//    31
} L9B0_P0R_TNR_CTRL_14;

/*-----------------------------------------------------------------------------
	0x247c tnr_ctrl_15 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :11;	//  0:10
	UINT32                                 : 5;	// 11:15 reserved
	UINT32 y1                              :12;	// 16:27
} L9B0_P0R_TNR_CTRL_15;

/*-----------------------------------------------------------------------------
	0x2480 tnr_ctrl_16 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 show_dbg_bar_ctrl0              : 8;	//  0: 7
	UINT32 show_dbg_bar_ctrl1              : 8;	//  8:15
	UINT32 show_dbg_bar_ctrl2              : 8;	// 16:23
	UINT32 show_dbg_bar_ctrl3              : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_16;

/*-----------------------------------------------------------------------------
	0x2484 tnr_ctrl_17 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 show_dbg_bar_ctrl4              : 8;	//  0: 7
} L9B0_P0R_TNR_CTRL_17;

/*-----------------------------------------------------------------------------
	0x2488 tnr_ctrl_18 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crgn_gain_enable                : 1;	//     0
	UINT32 luma_gain_enable                : 1;	//     1
	UINT32 saturation_gain_enable          : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 input_for_luma                  : 2;	//  4: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 input_for_crgn_satr             : 1;	//     8
	UINT32                                 : 7;	//  9:15 reserved
	UINT32 y_gain                          : 8;	// 16:23
	UINT32 c_gain                          : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_18;

/*-----------------------------------------------------------------------------
	0x248c tnr_ctrl_19 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p0_x                  : 8;	//  0: 7
	UINT32 luma_gain_p1_x                  : 8;	//  8:15
	UINT32 luma_gain_p2_x                  : 8;	// 16:23
	UINT32 luma_gain_p3_x                  : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_19;

/*-----------------------------------------------------------------------------
	0x2490 tnr_ctrl_20 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p4_x                  : 8;	//  0: 7
	UINT32 luma_gain_p5_x                  : 8;	//  8:15
	UINT32 luma_gain_p6_x                  : 8;	// 16:23
	UINT32 luma_gain_p7_x                  : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_20;

/*-----------------------------------------------------------------------------
	0x2494 tnr_ctrl_21 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p0_y                  : 8;	//  0: 7
	UINT32 luma_gain_p1_y                  : 8;	//  8:15
	UINT32 luma_gain_p2_y                  : 8;	// 16:23
	UINT32 luma_gain_p3_y                  : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_21;

/*-----------------------------------------------------------------------------
	0x2498 tnr_ctrl_22 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_gain_p4_y                  : 8;	//  0: 7
	UINT32 luma_gain_p5_y                  : 8;	//  8:15
	UINT32 luma_gain_p6_y                  : 8;	// 16:23
	UINT32 luma_gain_p7_y                  : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_22;

/*-----------------------------------------------------------------------------
	0x249c tnr_ctrl_23 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p0_x            : 8;	//  0: 7
	UINT32 saturation_gain_p1_x            : 8;	//  8:15
	UINT32 saturation_gain_p2_x            : 8;	// 16:23
	UINT32 saturation_gain_p3_x            : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_23;

/*-----------------------------------------------------------------------------
	0x24a0 tnr_ctrl_24 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p4_x            : 8;	//  0: 7
	UINT32 saturation_gain_p5_x            : 8;	//  8:15
	UINT32 saturation_gain_p6_x            : 8;	// 16:23
	UINT32 saturation_gain_p7_x            : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_24;

/*-----------------------------------------------------------------------------
	0x24a4 tnr_ctrl_25 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p0_y            : 8;	//  0: 7
	UINT32 saturation_gain_p1_y            : 8;	//  8:15
	UINT32 saturation_gain_p2_y            : 8;	// 16:23
	UINT32 saturation_gain_p3_y            : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_25;

/*-----------------------------------------------------------------------------
	0x24a8 tnr_ctrl_26 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 saturation_gain_p4_y            : 8;	//  0: 7
	UINT32 saturation_gain_p5_y            : 8;	//  8:15
	UINT32 saturation_gain_p6_y            : 8;	// 16:23
	UINT32 saturation_gain_p7_y            : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_26;

/*-----------------------------------------------------------------------------
	0x24ac tnr_ctrl_27 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crgn_gain_rgn0                  : 8;	//  0: 7
	UINT32 crgn_gain_rgn1                  : 8;	//  8:15
	UINT32 crgn_gain_rgn2                  : 8;	// 16:23
	UINT32 crgn_gain_rgn3                  : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_27;

/*-----------------------------------------------------------------------------
	0x24b0 tnr_ctrl_28 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_st_y0               : 8;	//  0: 7
	UINT32 nt_lvl_gain_st_x0               : 8;	//  8:15
	UINT32 nt_lvl_gain_st_y1               : 8;	// 16:23
	UINT32 nt_lvl_gain_st_x1               : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_28;

/*-----------------------------------------------------------------------------
	0x24b4 tnr_ctrl_29 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wa_y2                           : 8;	//  0: 7
	UINT32 wa_y3                           : 8;	//  8:15
	UINT32 wa_x2                           : 8;	// 16:23
	UINT32 wa_x3                           : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_29;

/*-----------------------------------------------------------------------------
	0x24b8 tnr_ctrl_30 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_st_y2               : 8;	//  0: 7
	UINT32 nt_lvl_gain_st_x2               : 8;	//  8:15
	UINT32 nt_lvl_gain_st_y3               : 8;	// 16:23
	UINT32 nt_lvl_gain_st_x3               : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_30;

/*-----------------------------------------------------------------------------
	0x24bc tnr_ctrl_31 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 spatial_pre_flt_en_c            : 1;	//     0
	UINT32 spatial_pre_flt_en_y            : 1;	//     1
	UINT32                                 :14;	//  2:15 reserved
	UINT32 spatial_pre_flt_th_c            : 8;	// 16:23
	UINT32 spatial_pre_flt_th_y            : 8;	// 24:31
} L9B0_P0R_TNR_CTRL_31;

/*-----------------------------------------------------------------------------
	0x24c0 tnr_status_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x_avg_t                         : 8;	//  0: 7
	UINT32 x_peak_t2                       : 8;	//  8:15
	UINT32 nt_lvl                          : 8;	// 16:23
	UINT32 scene_change                    : 8;	// 24:31
} L9B0_P0R_TNR_STATUS_00;

/*-----------------------------------------------------------------------------
	0x24c4 tnr_status_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x_avg_s                         : 8;	//  0: 7
	UINT32 valid_cnt_motion_histogram      :24;	//  8:31
} L9B0_P0R_TNR_STATUS_01;

/*-----------------------------------------------------------------------------
	0x24c8 tnr_status_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 gm                              : 8;	// 16:23
	UINT32 lp                              : 8;	// 24:31
} L9B0_P0R_TNR_STATUS_02;

/*-----------------------------------------------------------------------------
	0x24cc tnr_status_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sum_of_temp_pel_diff            :29;	//  0:28
} L9B0_P0R_TNR_STATUS_03;

/*-----------------------------------------------------------------------------
	0x24d0 tnr_main_lut_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_lut_indir_addr             : 5;	//  0: 4
	UINT32                                 : 7;	//  5:11 reserved
	UINT32 main_lut_ai_enable              : 1;	//    12
} L9B0_P0R_TNR_MAIN_LUT_00;

/*-----------------------------------------------------------------------------
	0x24d4 tnr_main_lut_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_lut_indir_data0            ;   	// 31: 0
} L9B0_P0R_TNR_MAIN_LUT_01;

/*-----------------------------------------------------------------------------
	0x24d8 tnr_main_lut_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_lut_indir_data1            ;   	// 31: 0
} L9B0_P0R_TNR_MAIN_LUT_02;

/*-----------------------------------------------------------------------------
	0x24e0 tnr_ctrl_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_lpct_y0             : 8;	//  0: 7
	UINT32 nt_lvl_gain_lpct_x0             : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_lpct_y1             : 8;	// 16:23
	UINT32 nt_lvl_gain_lpct_x1             : 7;	// 24:30
} L9B0_P0R_TNR_CTRL_32;

/*-----------------------------------------------------------------------------
	0x24e4 tnr_ctrl_33 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_lpct_y2             : 8;	//  0: 7
	UINT32 nt_lvl_gain_lpct_x2             : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_lpct_y3             : 8;	// 16:23
	UINT32 nt_lvl_gain_lpct_x3             : 7;	// 24:30
} L9B0_P0R_TNR_CTRL_33;

/*-----------------------------------------------------------------------------
	0x24e8 tnr_ctrl_34 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_xpeak_y0            : 8;	//  0: 7
	UINT32 nt_lvl_gain_xpeak_x0            : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_xpeak_y1            : 8;	// 16:23
	UINT32 nt_lvl_gain_xpeak_x1            : 7;	// 24:30
} L9B0_P0R_TNR_CTRL_34;

/*-----------------------------------------------------------------------------
	0x24ec tnr_ctrl_35 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nt_lvl_gain_xpeak_y2            : 8;	//  0: 7
	UINT32 nt_lvl_gain_xpeak_x2            : 7;	//  8:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 nt_lvl_gain_xpeak_y3            : 8;	// 16:23
	UINT32 nt_lvl_gain_xpeak_x3            : 7;	// 24:30
} L9B0_P0R_TNR_CTRL_35;

/*-----------------------------------------------------------------------------
	0x24f0 tnr_crg_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crgn_ctrl_indir_addr            : 8;	//  0: 7
	UINT32                                 : 4;	//  8:11 reserved
	UINT32 crgn_ctrl_ai_enable             : 1;	//    12
} L9B0_P0R_TNR_CRG_CTRL_00;

/*-----------------------------------------------------------------------------
	0x24f4 tnr_crg_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crgn_ctrl_indir_data            ;    // 31: 0
} L9B0_P0R_TNR_CRG_CTRL_01;

/*-----------------------------------------------------------------------------
	0x2500 ipc_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 luma_mode                       : 2;	//  0: 1
	UINT32                                 : 1;	//     2 reserved
	UINT32 luma_edi                        : 1;	//     3
	UINT32 chroma_mode                     : 2;	//  4: 5
	UINT32                                 : 1;	//     6 reserved
	UINT32 chroma_edi                      : 1;	//     7
	UINT32 chroma_adaptive_va_enable       : 1;	//     8
	UINT32                                 : 1;	//     9 reserved
	UINT32 st_filter_mode                  : 2;	// 10:11
	UINT32                                 :12;	// 12:23 reserved
	UINT32 ipc__fake__v_repeat_va_ta       : 2;	// 24:25
	UINT32                                 : 3;	// 26:28 reserved
	UINT32 film_mode_apply_c               : 1;	//    29
	UINT32 film_mode_apply_y               : 1;	//    30
	UINT32 film_mode_enable                : 1;	//    31
} L9B0_P0R_IPC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x2504 ipc_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_fuzzy_margin0                : 8;	//  0: 7
	UINT32 cr_fuzzy_margin1                : 8;	//  8:15
	UINT32                                 : 8;	// 16:23 reserved
	UINT32 cr_tnr_debug_mode               : 1;	//    24
	UINT32 cr_black_mask_origline_when_tnr_: 1;	//    25
} L9B0_P0R_IPC_CTRL_01;

/*-----------------------------------------------------------------------------
	0x2508 ipc_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fuzzy_ctrl_point_x0             : 8;	//  0: 7
	UINT32 fuzzy_ctrl_point_x4             : 8;	//  8:15
	UINT32 fuzzy_ctrl_point_x1             : 8;	// 16:23
	UINT32 fuzzy_ctrl_point_y1             : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_02;

/*-----------------------------------------------------------------------------
	0x250c ipc_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fuzzy_ctrl_point_x2             : 8;	//  0: 7
	UINT32 fuzzy_ctrl_point_y2             : 8;	//  8:15
	UINT32 fuzzy_ctrl_point_x3             : 8;	// 16:23
	UINT32 fuzzy_ctrl_point_y3             : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_03;

/*-----------------------------------------------------------------------------
	0x2510 ipc_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 et_offset__s7                   : 8;	//  0: 7
	UINT32 motion_x_tearing_gain           : 8;	//  8:15
	UINT32 tearing_gain                    : 8;	// 16:23
	UINT32 motion_gain                     : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_04;

/*-----------------------------------------------------------------------------
	0x2514 ipc_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_ipc_c_motion_alpha           : 8;	//  0: 7
	UINT32 cr_t_grad_weight                : 8;	//  8:15
	UINT32 cr_v_grad_weight                : 8;	// 16:23
	UINT32 cr_h_grad_weight                : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_05;

/*-----------------------------------------------------------------------------
	0x2518 ipc_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_normalize_en                 : 1;	//     0
	UINT32 cr_flat_only                    : 1;	//     1
	UINT32                                 : 2;	//  2: 3 reserved
	UINT32 cr_tearing_normalize_en         : 1;	//     4
	UINT32                                 : 3;	//  5: 7 reserved
	UINT32 cr_normalize_base               : 8;	//  8:15
	UINT32 cr_normalize_center             : 8;	// 16:23
	UINT32 cr_motion_coring                : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_06;

/*-----------------------------------------------------------------------------
	0x251c ipc_ctrl_07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 1;	//     0 reserved
	UINT32 cr_v_en                         : 1;	//     1
	UINT32 cr_45_en                        : 1;	//     2
	UINT32 cr_15_en                        : 1;	//     3
	UINT32                                 :12;	//  4:15 reserved
	UINT32 cr_postmedian_en                : 1;	//    16
} L9B0_P0R_IPC_CTRL_07;

/*-----------------------------------------------------------------------------
	0x2520 ipc_ctrl_08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd_caption_range_top           :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 fmd_caption_range_bot           :12;	// 16:27
	UINT32                                 : 2;	// 28:29 reserved
	UINT32 caption_flow_detected           : 1;	//    30
	UINT32 hmc_when_cap_not_detected       : 1;	//    31
} L9B0_P0R_IPC_CTRL_08;

/*-----------------------------------------------------------------------------
	0x2524 ipc_ctrl_09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd_vedge_th                    : 7;	//  0: 6
	UINT32 fmd_vedge_en                    : 1;	//     7
	UINT32 fmd_a_th                        : 6;	//  8:13
	UINT32 use_3field_err_t                : 1;	//    14
	UINT32 two_field_delay_mode            : 1;	//    15
	UINT32 fmd_margin_top                  : 8;	// 16:23
	UINT32 fmd_margin_bottom               : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_09;

/*-----------------------------------------------------------------------------
	0x2528 ipc_ctrl_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 film_inter_with                 : 2;	//  0: 1
	UINT32 hw_film_enable                  : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 tearing_detect_strength         : 1;	//     4
	UINT32 cross_check                     : 1;	//     5
	UINT32                                 : 1;	//     6 reserved
	UINT32 usediffpelcount                 : 1;	//     7
	UINT32 pn_diff_th                      : 8;	//  8:15
	UINT32                                 :12;	// 16:27 reserved
	UINT32 scalemeasureforhd               : 2;	// 28:29
	UINT32 loading_time_ctrl               : 1;	//    30
	UINT32 fmd_sw_bad_edit_en              : 1;	//    31
} L9B0_P0R_IPC_CTRL_10;

/*-----------------------------------------------------------------------------
	0x252c ipc_ctrl_11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 repeat_det_line_cnt_th          : 8;	//  0: 7
	UINT32 repeat_det_diff_pel_cnt_th      : 8;	//  8:15
	UINT32 repeat_det_noise_th             : 4;	// 16:19
} L9B0_P0R_IPC_CTRL_11;

/*-----------------------------------------------------------------------------
	0x2530 ipc_ctrl_12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd_32_enable                   : 1;	//     0
	UINT32 fmd_22_enable                   : 1;	//     1
	UINT32 reg_fmd_badediten               : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 fmd_hw_bad_edit_mul_th          : 3;	//  4: 6
	UINT32                                 : 1;	//     7 reserved
	UINT32 fmd_hw_bad_edit_th_min          : 8;	//  8:15
	UINT32 reg_pcn_diff_th                 : 7;	// 16:22
	UINT32 reg_fmd_arbitrary_6_4only       : 1;	//    23
	UINT32 reg_fmd_stillconditition1       : 1;	//    24
	UINT32 reg_fmd_stillconditition2       : 1;	//    25
	UINT32 reg_fmd_arbitrary_still         : 1;	//    26
	UINT32 reg_fmd_arbitrary_3_2only       : 1;	//    27
	UINT32 reg_fmd_still_cntth             : 3;	// 28:30
	UINT32 reg_fmd_still_cntth_en          : 1;	//    31
} L9B0_P0R_IPC_CTRL_12;

/*-----------------------------------------------------------------------------
	0x2534 ipc_ctrl_13 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd32_stillth_pn                : 8;	//  0: 7
	UINT32 fmd32_stillthpcn                : 8;	//  8:15
	UINT32 fmd32_pn_maxvalue_minth0        : 8;	// 16:23
	UINT32 fmd32_pn_maxvalue_minth1        : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_13;

/*-----------------------------------------------------------------------------
	0x2538 ipc_ctrl_14 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd32_min_field_num             : 4;	//  0: 3
	UINT32                                 : 4;	//  4: 7 reserved
	UINT32 fmd32_pn_minvalue_maxth         : 8;	//  8:15
	UINT32 fmd32_pn_maxminratio0           : 4;	// 16:19
	UINT32 fmd32_pn_maxminratio1           : 4;	// 20:23
	UINT32 fmd_32_pcn_small_weight         : 3;	// 24:26
} L9B0_P0R_IPC_CTRL_14;

/*-----------------------------------------------------------------------------
	0x253c ipc_ctrl_15 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fmd22_stillth_pn            : 8;	//  0: 7
	UINT32 reg_fmd22_stillth_pcn           : 8;	//  8:15
	UINT32 reg_bad_edit_sm_min_th          :12;	// 16:27
	// fmd_22_min_val_max_th1 is removed from L9A0
	//UINT32 fmd_22_min_val_max_th1              : 8;   // 31:24
} L9B0_P0R_IPC_CTRL_15;

/*-----------------------------------------------------------------------------
	0x2540 ipc_ctrl_16 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fmd22_minfieldnum0          : 4;	//  0: 3
	UINT32 reg_fmd22_minfieldnum1          : 4;	//  4: 7
	UINT32 reg_fmd22_minvaluemaxth1        : 8;	//  8:15
	UINT32 reg_fmd22_maxvalueminth1        : 8;	// 16:23
	UINT32 reg_fmd22_maxminratio0          : 4;	// 24:27
	UINT32 reg_fmd22_maxminratio1          : 4;	// 28:31
} L9B0_P0R_IPC_CTRL_16;

/*-----------------------------------------------------------------------------
	0x2544 ipc_ctrl_17 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fmd22_maxvalueminth0        : 8;	//  0: 7
	UINT32 reg_fmd22_minvaluemaxth0        : 8;	//  8:15
	UINT32 reg_fmd32_minvaluemaxth0        : 8;	// 16:23
	UINT32 reg_fmd32_maxvalueminth0        : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_17;

/*-----------------------------------------------------------------------------
	0x2548 ipc_ctrl_18 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_ud_gain                      : 8;	//  0: 7
	UINT32 cr_lr_gain                      : 8;	//  8:15
	UINT32 cr_h_grad_gain                  : 8;	// 16:23
	UINT32 cr_v_grad_gain                  : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_18;

/*-----------------------------------------------------------------------------
	0x254c ipc_ctrl_19 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 reg_center_vld_gain             : 4;	// 16:19
	UINT32 reg_diff_vld_gain               : 4;	// 20:23
} L9B0_P0R_IPC_CTRL_19;

/*-----------------------------------------------------------------------------
	0x2550 ipc_status_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pc_cnt                          :16;	//  0:15
	UINT32 nc_cnt                          :16;	// 16:31
} L9B0_P0R_IPC_STATUS_00;

/*-----------------------------------------------------------------------------
	0x2554 ipc_status_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pn_cnt                          :16;	//  0:15
	UINT32 same_cnt                        :16;	// 16:31
} L9B0_P0R_IPC_STATUS_01;

/*-----------------------------------------------------------------------------
	0x2558 ipc_status_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fmd32_combwith                  : 2;	//  0: 1
	UINT32                                 : 1;	//     2 reserved
	UINT32 fmd32_detected                  : 1;	//     3
	UINT32 fmd32_lockingcnt                : 8;	//  4:11
	UINT32 fmd22_combwith                  : 2;	// 12:13
	UINT32                                 : 1;	//    14 reserved
	UINT32 fmd22_detected                  : 1;	//    15
	UINT32 fmd22_lockingcnt                : 8;	// 16:23
	UINT32 fmd_comb_predict                : 2;	// 24:25
	UINT32 bad_edit_detected__hw           : 1;	//    26
	UINT32 fmd22_still_detected            : 1;	//    27
	UINT32 fmd32_still_detected            : 1;	//    28
	UINT32 repeat_detected                 : 1;	//    29
} L9B0_P0R_IPC_STATUS_02;

/*-----------------------------------------------------------------------------
	0x255c ipc_status_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 fmd_badeditth_hw                :16;	// 16:31
} L9B0_P0R_IPC_STATUS_03;

/*-----------------------------------------------------------------------------
	0x2580 vflt_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vfilterenable                   : 1;	//     0
	UINT32 vfilterlocalenable              : 1;	//     1
	UINT32 vfilter_strength                : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 cb_filter_y                     : 2;	//  4: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 vfilter_a_th                    : 8;	//  8:15
	UINT32 vfilter_in_field_var            : 8;	// 16:23
	UINT32 vfilter_use_mc_mask             : 1;	//    24
	UINT32 vfilter_expand                  : 1;	//    25
	UINT32 vfilter_center                  : 1;	//    26
	UINT32 vfilter_ul4                     : 1;	//    27
	UINT32 dbgshow_level                   : 2;	// 28:29
	UINT32                                 : 1;	//    30 reserved
	UINT32 dbgshow_enable                  : 1;	//    31
} L9B0_P0R_VFLT_CTRL;

/*-----------------------------------------------------------------------------
	0x2588 mnr_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mnr_enable                      : 1;	//     0
	UINT32 edge_gain_mapping_enable        : 1;	//     1
	UINT32 sel_sd_hd                       : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 debug_mode                      : 3;	//  4: 6
} L9B0_P0R_MNR_CTRL_00;

/*-----------------------------------------------------------------------------
	0x258c mnr_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 hcoef_00                        : 4;	// 16:19
	UINT32 hcoef_01                        : 4;	// 20:23
	UINT32 hcoef_02                        : 4;	// 24:27
	UINT32 hcoef_03                        : 4;	// 28:31
} L9B0_P0R_MNR_CTRL_01;

/*-----------------------------------------------------------------------------
	0x2590 mnr_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hcoef_04                        : 4;	//  0: 3
	UINT32 hcoef_05                        : 4;	//  4: 7
	UINT32 hcoef_06                        : 4;	//  8:11
	UINT32 hcoef_07                        : 4;	// 12:15
	UINT32 hcoef_08                        : 4;	// 16:19
	UINT32 hcoef_09                        : 4;	// 20:23
	UINT32 hcoef_10                        : 4;	// 24:27
	UINT32 hcoef_11                        : 4;	// 28:31
} L9B0_P0R_MNR_CTRL_02;

/*-----------------------------------------------------------------------------
	0x2594 mnr_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hcoef_12                        : 4;	//  0: 3
	UINT32 hcoef_13                        : 4;	//  4: 7
	UINT32 hcoef_14                        : 4;	//  8:11
	UINT32 hcoef_15                        : 4;	// 12:15
	UINT32 hcoef_16                        : 4;	// 16:19
	UINT32                                 : 4;	// 20:23 reserved
	UINT32 x1_position                     : 8;	// 24:31
} L9B0_P0R_MNR_CTRL_03;

/*-----------------------------------------------------------------------------
	0x2598 mnr_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x2_position                     : 8;	//  0: 7
	UINT32 x3_position                     : 8;	//  8:15
	UINT32 x4_position                     : 8;	// 16:23
	UINT32 y1_position                     : 8;	// 24:31
} L9B0_P0R_MNR_CTRL_04;

/*-----------------------------------------------------------------------------
	0x259c mnr_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y2_position                     : 8;	//  0: 7
	UINT32 y3_position                     : 8;	//  8:15
	UINT32 y4_position                     : 8;	// 16:23
	UINT32 filter_threshold                : 8;	// 24:31
} L9B0_P0R_MNR_CTRL_05;

/*-----------------------------------------------------------------------------
	0x25a0 mnr_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vcoef0                          : 4;	//  0: 3
	UINT32 vcoef1                          : 4;	//  4: 7
	UINT32 vcoef2                          : 4;	//  8:11
	UINT32 vcoef3                          : 4;	// 12:15
	UINT32 vcoef4                          : 4;	// 16:19
	UINT32 vcoef5                          : 4;	// 20:23
	UINT32 vcoef6                          : 4;	// 24:27
} L9B0_P0R_MNR_CTRL_06;

/*-----------------------------------------------------------------------------
	0x25a8 vfilter_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_vfilter_global_en            : 1;	//     0
	UINT32 cr_vfilter_force_en             : 1;	//     1
	UINT32 cr_global_frame_num_th          : 4;	//  2: 5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 cr_vfilter_global_th            :12;	//  8:19
	UINT32 tearing_count                   :12;	// 20:31
} L9B0_P0R_VFILTER_01;

/*-----------------------------------------------------------------------------
	0x25ac bnr_dc_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dc_bnr_enable                   : 1;	//     0
	UINT32 ac_blockiness_adaptive_mode     : 1;	//     1
	UINT32                                 : 1;	//     2 reserved
	UINT32 motion_gain_enable              : 1;	//     3
	UINT32 sd_hd_sel                       : 1;	//     4
	UINT32 output_mux                      : 3;	//  5: 7
	UINT32 motion_min                      : 4;	//  8:11
	UINT32 motion_max                      : 4;	// 12:15
} L9B0_P0R_BNR_DC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x25b0 bnr_dc_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 blur_enable                     : 2;	//  0: 1
	UINT32                                 :26;	//  2:27 reserved
	UINT32 ac_blockiness_multifly_x_n      : 4;	// 28:31
} L9B0_P0R_BNR_DC_CTRL_01;

/*-----------------------------------------------------------------------------
	0x25b4 bnr_dc_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dc_bnr_gain_ctrl_y2             : 8;	//  0: 7
	UINT32 dc_bnr_gain_ctrl_x2             : 8;	//  8:15
	UINT32 dc_bnr_gain_ctrl_y3             : 8;	// 16:23
	UINT32 dc_bnr_gain_ctrl_x3             : 8;	// 24:31
} L9B0_P0R_BNR_DC_CTRL_02;

/*-----------------------------------------------------------------------------
	0x25b8 bnr_dc_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dc_bnr_gain_ctrl_y0             : 8;	//  0: 7
	UINT32 dc_bnr_gain_ctrl_x0             : 8;	//  8:15
	UINT32 dc_bnr_gain_ctrl_y1             : 8;	// 16:23
	UINT32 dc_bnr_gain_ctrl_x1             : 8;	// 24:31
} L9B0_P0R_BNR_DC_CTRL_03;

/*-----------------------------------------------------------------------------
	0x25bc bnr_ac_ctrl_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 :16;	//  0:15 reserved
	UINT32 ac_bnr_protect_motion_max       : 8;	// 16:23
	UINT32 ac_bnr_protect_motion_min       : 8;	// 24:31
} L9B0_P0R_BNR_AC_CTRL_06;

/*-----------------------------------------------------------------------------
	0x25c0 bnr_ac_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 bnr_h_en                        : 1;	//     0
	UINT32 bnr_v_en                        : 1;	//     1
	UINT32 motion_protect_enable           : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 source_type                     : 1;	//     4
	UINT32 status_read_type                : 1;	//     5
	UINT32 status_read_mode                : 2;	//  6: 7
	UINT32 hbmax_gain                      : 4;	//  8:11
	UINT32 vbmax_gain                      : 4;	// 12:15
	UINT32 strength_resolution             : 1;	//    16
	UINT32                                 : 3;	// 17:19 reserved
	UINT32 fiter_type                      : 1;	//    20
	UINT32                                 : 3;	// 21:23 reserved
	UINT32 output_mux                      : 2;	// 24:25
} L9B0_P0R_BNR_AC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x25c4 bnr_ac_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 strength_h_x0                   : 8;	//  0: 7
	UINT32 strength_h_x1                   : 8;	//  8:15
	UINT32 strength_h_max                  : 8;	// 16:23
	UINT32 detect_min_th                   : 8;	// 24:31
} L9B0_P0R_BNR_AC_CTRL_01;

/*-----------------------------------------------------------------------------
	0x25c8 bnr_ac_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 strength_v_x0                   : 8;	//  0: 7
	UINT32 strength_v_x1                   : 8;	//  8:15
	UINT32 strength_v_max                  : 8;	// 16:23
} L9B0_P0R_BNR_AC_CTRL_02;

/*-----------------------------------------------------------------------------
	0x25cc bnr_ac_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_offset_mode                   : 1;	//     0
	UINT32 manual_offset_h_value           : 3;	//  1: 3
	UINT32 v_offset_mode                   : 1;	//     4
	UINT32 manual_offset_v_value           : 3;	//  5: 7
	UINT32 use_of_hysterisis               : 4;	//  8:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 t_filter_weight                 : 8;	// 16:23
} L9B0_P0R_BNR_AC_CTRL_03;

/*-----------------------------------------------------------------------------
	0x25d0 bnr_ac_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 max_delta_th0                   : 8;	//  0: 7
	UINT32 max_delta_th1                   : 8;	//  8:15
	UINT32 h_blockness_th                  : 8;	// 16:23
	UINT32 h_weight_max                    : 8;	// 24:31
} L9B0_P0R_BNR_AC_CTRL_04;

/*-----------------------------------------------------------------------------
	0x25d4 bnr_ac_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 use_of_hysterisis               : 4;	//  0: 3
	UINT32 block_boundary_processing_type  : 1;	//     4
} L9B0_P0R_BNR_AC_CTRL_05;

/*-----------------------------------------------------------------------------
	0x25d8 dnr_max_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 enable_snr                      : 1;	//     0
	UINT32 enable_mnr                      : 1;	//     1
	UINT32 enable_der                      : 1;	//     2
	UINT32 enable_dc_bnr                   : 1;	//     3
	UINT32 enable_ac_bnr                   : 1;	//     4
	UINT32                                 : 3;	//  5: 7 reserved
	UINT32 debug_enable                    : 1;	//     8
	UINT32 debug_mode                      : 1;	//     9
	UINT32 debug_snr_enable                : 1;	//    10
	UINT32 debug_mnr_enable                : 1;	//    11
	UINT32 debug_der_enable                : 1;	//    12
	UINT32 debug_dc_bnr_enable             : 1;	//    13
	UINT32 debug_ac_bnr_enable             : 1;	//    14
	UINT32                                 : 1;	//    15 reserved
	UINT32 win_control_enable              : 1;	//    16
	UINT32 border_enable                   : 1;	//    17
} L9B0_P0R_DNR_MAX_CTRL;

/*-----------------------------------------------------------------------------
	0x25dc dnr_dbar_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 debug_bar_en                    : 1;	//     0
	UINT32                                 : 1;	//     1 reserved
	UINT32 show_debug_bar_for_bnr          : 1;	//     2
	UINT32                                 : 1;	//     3 reserved
	UINT32 gain                            : 3;	//  4: 6
	UINT32                                 : 1;	//     7 reserved
	UINT32 sd_hd_sel                       : 2;	//  8: 9
} L9B0_P0R_DNR_DBAR_CTRL;

/*-----------------------------------------------------------------------------
	0x25e0 bnr_stat_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ac_bnr_h_status                 : 8;	//  0: 7
	UINT32 ac_bnr_v_status                 : 8;	//  8:15
	UINT32 dc_bnr_th                       :14;	// 16:29
} L9B0_P0R_BNR_STAT_0;

/*-----------------------------------------------------------------------------
	0x25e4 der_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 der_en                          : 1;	//     0
	UINT32 out_mux                         : 3;	//  1: 3
	UINT32 bif_en                          : 1;	//     4
	UINT32 gain2weight_mapping             : 1;	//     5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 bif_th                          : 8;	//  8:15
} L9B0_P0R_DER_CTRL_0;

/*-----------------------------------------------------------------------------
	0x25e8 der_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gain_th0                        : 8;	//  0: 7
	UINT32 gain_th1                        : 8;	//  8:15
} L9B0_P0R_DER_CTRL_1;

/*-----------------------------------------------------------------------------
	0x25f0 ipc_ctrl_20 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_lock_dir_sel                 : 1;	//     0
	UINT32                                 : 7;	//  1: 7 reserved
	UINT32 cr_center_ratio                 : 4;	//  8:11
	UINT32 cr_lr_diff_ratio                : 4;	// 12:15
	UINT32 cr_hmc_lock_filt_sizeh          : 3;	// 16:18
} L9B0_P0R_IPC_CTRL_20;

/*-----------------------------------------------------------------------------
	0x25f4 ipc_ctrl_21 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr_lock_point_add               : 8;	//  0: 7
	UINT32 cr_lock_point_penalty           : 8;	//  8:15
	UINT32 cr_lock_point_valid             : 8;	// 16:23
	UINT32                                 : 6;	// 24:29 reserved
	UINT32 cr_robustness                   : 2;	// 30:31
} L9B0_P0R_IPC_CTRL_21;

/*-----------------------------------------------------------------------------
	0x25f8 ipc_ctrl_22 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x25fc ipc_ctrl_23 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_global_tbm_en               : 1;	//     0
	UINT32 reg_flim_panelty_en             : 1;	//     1
	UINT32                                 : 2;	//  2: 3 reserved
	UINT32 reg_es_offset_mode              : 1;	//     4
	UINT32 reg_err_mode                    : 1;	//     5
	UINT32                                 : 2;	//  6: 7 reserved
	UINT32 reg_global_tbm_th               : 8;	//  8:15
	UINT32 reg_hmc_2d_gain                 : 8;	// 16:23
	UINT32 reg_errs_limit                  : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_23;

/*-----------------------------------------------------------------------------
	0x2600 ipc_ctrl_24 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_errs_gain                   : 8;	//  0: 7
	UINT32 reg_confidance_gain             : 8;	//  8:15
	UINT32 reg_2d_offset                   : 8;	// 16:23
} L9B0_P0R_IPC_CTRL_24;

/*-----------------------------------------------------------------------------
	0x2604 ipc_ctrl_25 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cubic_coef0                 : 8;	//  0: 7
	UINT32 reg_cubic_coef1                 : 8;	//  8:15
	UINT32 reg_cubic_coef2                 : 8;	// 16:23
	UINT32 reg_cubic_coef3                 : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_25;

/*-----------------------------------------------------------------------------
	0x2608 ipc_ctrl_26 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_va_cubic                    : 1;	//     0
	UINT32 reg_boundary_window             : 1;	//     1
	UINT32 reg_force_va                    : 1;	//     2
	UINT32 reg_half_pel_va                 : 1;	//     3
	UINT32 reg_dir_med_tap                 : 2;	//  4: 5
	UINT32 reg_diff_med_tap                : 2;	//  6: 7
	UINT32 reg_va_blending_ctrl1           : 3;	//  8:10
	UINT32 reg_wide_angle_protection_1     : 1;	//    11
	UINT32 reg_va_blending_ctrl2           : 3;	// 12:14
	UINT32                                 : 1;	//    15 reserved
	UINT32 reg_errs_chroma_blend_gain      : 8;	// 16:23
	UINT32 reg_strong_global_th            : 6;	// 24:29
	UINT32 narrow_angle_week               : 1;	//    30
	UINT32 narrow_angle_protection         : 1;	//    31
} L9B0_P0R_IPC_CTRL_26;

/*-----------------------------------------------------------------------------
	0x260c ipc_ctrl_27 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dbg_show_mode                   : 5;	//  0: 4
	UINT32                                 : 6;	//  5:10 reserved
	UINT32 dbg_show_black_mask             : 1;	//    11
	UINT32 dbg_pprv_to_curr                : 1;	//    12
	UINT32 dbg_prv3_to_prev                : 1;	//    13
	UINT32 dbg_curr_to_pprv                : 1;	//    14
	UINT32                                 : 1;	//    15 reserved
	UINT32 st_flt_ctrl_x0                  : 8;	// 16:23
	UINT32 st_flt_ctrl_x1                  : 8;	// 24:31
} L9B0_P0R_IPC_CTRL_27;

/*-----------------------------------------------------------------------------
	0x2640 tpd_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 4;	//  0: 3 reserved
	UINT32 reg_mux_3                       : 4;	//  4: 7
	UINT32                                 : 4;	//  8:11 reserved
	UINT32 reg_mux_2                       : 4;	// 12:15
	UINT32                                 : 4;	// 16:19 reserved
	UINT32 reg_mux_1                       : 4;	// 20:23
	UINT32 reg_show_scale                  : 3;	// 24:26
	UINT32                                 : 1;	//    27 reserved
	UINT32 reg_show_bar_1                  : 1;	//    28
	UINT32 reg_show_bar_2                  : 1;	//    29
	UINT32 reg_show_bar_3                  : 1;	//    30
	UINT32 reg_show_bar_4                  : 1;	//    31
} L9B0_P0R_TPD_CTRL_00;

/*-----------------------------------------------------------------------------
	0x2670 bbd_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_bbd_en                      : 1;	//     0
	UINT32 reg_hys_mode                    : 5;	//  1: 5
	UINT32 reg_op_mode                     : 1;	//     6
	UINT32                                 : 1;	//     7 reserved
	UINT32 reg_cnt_th                      : 8;	//  8:15
	UINT32 reg_diff_th                     : 8;	// 16:23
	UINT32 reg_bbd_mux                     : 3;	// 24:26
	UINT32                                 : 1;	//    27 reserved
	UINT32 reg_apl_mux                     : 3;	// 28:30
} L9B0_P0R_BBD_CTRL_00;

/*-----------------------------------------------------------------------------
	0x2674 bbd_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y0                              :12;	// 16:27
} L9B0_P0R_BBD_CTRL_01;

/*-----------------------------------------------------------------------------
	0x2678 bbd_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y1                              :12;	// 16:27
} L9B0_P0R_BBD_CTRL_02;

/*-----------------------------------------------------------------------------
	0x267c bbd_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y0                              :12;	// 16:27
} L9B0_P0R_BBD_STAT_00;

/*-----------------------------------------------------------------------------
	0x2680 bbd_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                              :12;	//  0:11
	UINT32                                 : 4;	// 12:15 reserved
	UINT32 y1                              :12;	// 16:27
} L9B0_P0R_BBD_STAT_01;

/*-----------------------------------------------------------------------------
	0x2684 apl_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 apl_stat_00                     :10;	//  0: 9
} L9B0_P0R_APL_STAT_00;

/*-----------------------------------------------------------------------------
	0x2690 cti_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cti_enable                      : 1;	//     0
	UINT32 cti_repeat_en                   : 1;	//     1
	UINT32 cti_clipping_en                 : 1;	//     2
	UINT32                                 :13;	//  3:15 reserved
	UINT32 cti_gain                        : 8;	// 16:23
	UINT32 cb_filter_c                     : 2;	// 24:25
} L9B0_P0R_CTI_CTRL_00;

typedef struct {
	L9B0_P0L_PE0_LOAD           pe0_load;			// 0x0400 : ''
	L9B0_P0L_PE0_INTR           pe0_intr;			// 0x0404 : ''
	L9B0_P0L_PE0_STATUS0        pe0_status0;		// 0x0408 : ''
	L9B0_P0L_PE0_STATUS1        pe0_status1;		// 0x040c : ''
	L9B0_P0L_PE0_OPMODE         pe0_opmode;			// 0x0410 : ''
	L9B0_P0L_PE0_SRC_SIZE       pe0_src_size;		// 0x0414 : ''
	L9B0_P0L_PE0_FIELD          pe0_field;			// 0x0418 : ''
	L9B0_P0L_PE0_PARAM_BY_DDR   pe0_param_by_ddr;	// 0x041c : ''
	L9B0_P0L_WIN_CTRL_0         win_ctrl_0;			// 0x0420 : ''
	L9B0_P0L_WIN_CTRL_1         win_ctrl_1;			// 0x0424 : ''
	L9B0_P0L_WIN_CTRL_2         win_ctrl_2;			// 0x0428 : ''
	L9B0_P0L_WIN_CTRL_3         win_ctrl_3;			// 0x042c : ''
	UINT32                      reserved00[4];		// 0x0430 ~ 0x043c
	L9B0_P0L_TNR_CTRL_00        tnr_ctrl_00;		// 0x0440 : ''
	L9B0_P0L_TNR_CTRL_01        tnr_ctrl_01;		// 0x0444 : ''
	L9B0_P0L_TNR_CTRL_02        tnr_ctrl_02;		// 0x0448 : ''
	L9B0_P0L_TNR_CTRL_03        tnr_ctrl_03;		// 0x044c : ''
	L9B0_P0L_TNR_CTRL_04        tnr_ctrl_04;		// 0x0450 : ''
	L9B0_P0L_TNR_CTRL_05        tnr_ctrl_05;		// 0x0454 : ''
	L9B0_P0L_TNR_CTRL_06        tnr_ctrl_06;		// 0x0458 : ''
	L9B0_P0L_TNR_CTRL_07        tnr_ctrl_07;		// 0x045c : ''
	L9B0_P0L_TNR_CTRL_08        tnr_ctrl_08;		// 0x0460 : ''
	L9B0_P0L_TNR_CTRL_09        tnr_ctrl_09;		// 0x0464 : ''
	L9B0_P0L_TNR_CTRL_10        tnr_ctrl_10;		// 0x0468 : ''
	L9B0_P0L_TNR_CTRL_11        tnr_ctrl_11;		// 0x046c : ''
	L9B0_P0L_TNR_CTRL_12        tnr_ctrl_12;		// 0x0470 : ''
	L9B0_P0L_TNR_CTRL_13        tnr_ctrl_13;		// 0x0474 : ''
	L9B0_P0L_TNR_CTRL_14        tnr_ctrl_14;		// 0x0478 : ''
	L9B0_P0L_TNR_CTRL_15        tnr_ctrl_15;		// 0x047c : ''
	L9B0_P0L_TNR_CTRL_16        tnr_ctrl_16;		// 0x0480 : ''
	L9B0_P0L_TNR_CTRL_17        tnr_ctrl_17;		// 0x0484 : ''
	L9B0_P0L_TNR_CTRL_18        tnr_ctrl_18;		// 0x0488 : ''
	L9B0_P0L_TNR_CTRL_19        tnr_ctrl_19;		// 0x048c : ''
	L9B0_P0L_TNR_CTRL_20        tnr_ctrl_20;		// 0x0490 : ''
	L9B0_P0L_TNR_CTRL_21        tnr_ctrl_21;		// 0x0494 : ''
	L9B0_P0L_TNR_CTRL_22        tnr_ctrl_22;		// 0x0498 : ''
	L9B0_P0L_TNR_CTRL_23        tnr_ctrl_23;		// 0x049c : ''
	L9B0_P0L_TNR_CTRL_24        tnr_ctrl_24;		// 0x04a0 : ''
	L9B0_P0L_TNR_CTRL_25        tnr_ctrl_25;		// 0x04a4 : ''
	L9B0_P0L_TNR_CTRL_26        tnr_ctrl_26;		// 0x04a8 : ''
	L9B0_P0L_TNR_CTRL_27        tnr_ctrl_27;		// 0x04ac : ''
	L9B0_P0L_TNR_CTRL_28        tnr_ctrl_28;		// 0x04b0 : ''
	L9B0_P0L_TNR_CTRL_29        tnr_ctrl_29;		// 0x04b4 : ''
	L9B0_P0L_TNR_CTRL_30        tnr_ctrl_30;		// 0x04b8 : ''
	L9B0_P0L_TNR_CTRL_31        tnr_ctrl_31;		// 0x04bc : ''
	L9B0_P0L_TNR_STATUS_00      tnr_status_00;		// 0x04c0 : ''
	L9B0_P0L_TNR_STATUS_01      tnr_status_01;		// 0x04c4 : ''
	L9B0_P0L_TNR_STATUS_02      tnr_status_02;		// 0x04c8 : ''
	L9B0_P0L_TNR_STATUS_03      tnr_status_03;		// 0x04cc : ''
	L9B0_P0L_TNR_MAIN_LUT_00    tnr_main_lut_00;	// 0x04d0 : ''
	L9B0_P0L_TNR_MAIN_LUT_01    tnr_main_lut_01;	// 0x04d4 : ''
	L9B0_P0L_TNR_MAIN_LUT_02    tnr_main_lut_02;	// 0x04d8 : ''
	UINT32                      reserved01;			// 0x04dc
	L9B0_P0L_TNR_CTRL_32        tnr_ctrl_32;		// 0x04e0 : ''
	L9B0_P0L_TNR_CTRL_33        tnr_ctrl_33;		// 0x04e4 : ''
	L9B0_P0L_TNR_CTRL_34        tnr_ctrl_34;		// 0x04e8 : ''
	L9B0_P0L_TNR_CTRL_35        tnr_ctrl_35;		// 0x04ec : ''
	L9B0_P0L_TNR_CRG_CTRL_00    tnr_crg_ctrl_00;	// 0x04f0 : ''
	L9B0_P0L_TNR_CRG_CTRL_01    tnr_crg_ctrl_01;	// 0x04f4 : ''
	UINT32                      reserved02[2];		// 0x04f8 ~ 0x04fc	
	L9B0_P0L_IPC_CTRL_00        ipc_ctrl_00;		// 0x0500 : ''
	L9B0_P0L_IPC_CTRL_01        ipc_ctrl_01;		// 0x0504 : ''
	L9B0_P0L_IPC_CTRL_02        ipc_ctrl_02;		// 0x0508 : ''
	L9B0_P0L_IPC_CTRL_03        ipc_ctrl_03;		// 0x050c : ''
	L9B0_P0L_IPC_CTRL_04        ipc_ctrl_04;		// 0x0510 : ''
	L9B0_P0L_IPC_CTRL_05        ipc_ctrl_05;		// 0x0514 : ''
	L9B0_P0L_IPC_CTRL_06        ipc_ctrl_06;		// 0x0518 : ''
	L9B0_P0L_IPC_CTRL_07        ipc_ctrl_07;		// 0x051c : ''
	L9B0_P0L_IPC_CTRL_08        ipc_ctrl_08;		// 0x0520 : ''
	L9B0_P0L_IPC_CTRL_09        ipc_ctrl_09;		// 0x0524 : ''
	L9B0_P0L_IPC_CTRL_10        ipc_ctrl_10;		// 0x0528 : ''
	L9B0_P0L_IPC_CTRL_11        ipc_ctrl_11;		// 0x052c : ''
	L9B0_P0L_IPC_CTRL_12        ipc_ctrl_12;		// 0x0530 : ''
	L9B0_P0L_IPC_CTRL_13        ipc_ctrl_13;		// 0x0534 : ''
	L9B0_P0L_IPC_CTRL_14        ipc_ctrl_14;		// 0x0538 : ''
	L9B0_P0L_IPC_CTRL_15        ipc_ctrl_15;		// 0x053c : ''
	L9B0_P0L_IPC_CTRL_16        ipc_ctrl_16;		// 0x0540 : ''
	L9B0_P0L_IPC_CTRL_17        ipc_ctrl_17;		// 0x0544 : ''
	L9B0_P0L_IPC_CTRL_18        ipc_ctrl_18;		// 0x0548 : ''
	L9B0_P0L_IPC_CTRL_19        ipc_ctrl_19;		// 0x054c : ''
	L9B0_P0L_IPC_STATUS_00      ipc_status_00;		// 0x0550 : ''
	L9B0_P0L_IPC_STATUS_01      ipc_status_01;		// 0x0554 : ''
	L9B0_P0L_IPC_STATUS_02      ipc_status_02;		// 0x0558 : ''
	L9B0_P0L_IPC_STATUS_03      ipc_status_03;		// 0x055c : ''
	L9B0_P0L_CLC_CTRL_00        clc_ctrl_00;		// 0x0560 : ''
	L9B0_P0L_CLC_CTRL_01        clc_ctrl_01;		// 0x0564 : ''
	L9B0_P0L_CLC_CTRL_02        clc_ctrl_02;		// 0x0568 : ''
	L9B0_P0L_CLC_CTRL_03        clc_ctrl_03;		// 0x056c : ''
	L9B0_P0L_CLC_CTRL_04        clc_ctrl_04;		// 0x0570 : ''
	L9B0_P0L_CLC_CTRL_05        clc_ctrl_05;		// 0x0574 : ''
	L9B0_P0L_CLC_CTRL_06        clc_ctrl_06;		// 0x0578 : ''
	L9B0_P0L_CLC_STAT_00        clc_stat_00;		// 0x057c : ''
	L9B0_P0L_VFLT_CTRL          vflt_ctrl;			// 0x0580 : ''
	UINT32                      reserved03;			// 0x0584
	L9B0_P0L_MNR_CTRL_00        mnr_ctrl_00;		// 0x0588 : ''
	L9B0_P0L_MNR_CTRL_01        mnr_ctrl_01;		// 0x058c : ''
	L9B0_P0L_MNR_CTRL_02        mnr_ctrl_02;		// 0x0590 : ''
	L9B0_P0L_MNR_CTRL_03        mnr_ctrl_03;		// 0x0594 : ''
	L9B0_P0L_MNR_CTRL_04        mnr_ctrl_04;		// 0x0598 : ''
	L9B0_P0L_MNR_CTRL_05        mnr_ctrl_05;		// 0x059c : ''
	L9B0_P0L_MNR_CTRL_06        mnr_ctrl_06;		// 0x05a0 : ''
	UINT32                      reserved04;			// 0x05a4
	L9B0_P0L_VFILTER_01         vfilter_01;			// 0x05a8 : ''
	L9B0_P0L_BNR_DC_CTRL_00     bnr_dc_ctrl_00;		// 0x05ac : ''
	L9B0_P0L_BNR_DC_CTRL_01     bnr_dc_ctrl_01;		// 0x05b0 : ''
	L9B0_P0L_BNR_DC_CTRL_02     bnr_dc_ctrl_02;		// 0x05b4 : ''
	L9B0_P0L_BNR_DC_CTRL_03     bnr_dc_ctrl_03;		// 0x05b8 : ''
	L9B0_P0L_BNR_AC_CTRL_06     bnr_ac_ctrl_06;		// 0x05bc : ''
	L9B0_P0L_BNR_AC_CTRL_00     bnr_ac_ctrl_00;		// 0x05c0 : ''
	L9B0_P0L_BNR_AC_CTRL_01     bnr_ac_ctrl_01;		// 0x05c4 : ''
	L9B0_P0L_BNR_AC_CTRL_02     bnr_ac_ctrl_02;		// 0x05c8 : ''
	L9B0_P0L_BNR_AC_CTRL_03     bnr_ac_ctrl_03;		// 0x05cc : ''
	L9B0_P0L_BNR_AC_CTRL_04     bnr_ac_ctrl_04;		// 0x05d0 : ''
	L9B0_P0L_BNR_AC_CTRL_05     bnr_ac_ctrl_05;		// 0x05d4 : ''
	L9B0_P0L_DNR_MAX_CTRL       dnr_max_ctrl  ;		// 0x05d8 : ''
	L9B0_P0L_DNR_DBAR_CTRL      dnr_dbar_ctrl ;		// 0x05dc : ''
	L9B0_P0L_BNR_STAT_0         bnr_stat_0;			// 0x05e0 : ''
	L9B0_P0L_DER_CTRL_0         der_ctrl_0;			// 0x05e4 : ''
	L9B0_P0L_DER_CTRL_1         der_ctrl_1;			// 0x05e8 : ''
	UINT32                      reserved05;			// 0x05ec
	L9B0_P0L_IPC_CTRL_20        ipc_ctrl_20;		// 0x05f0 : ''
	L9B0_P0L_IPC_CTRL_21        ipc_ctrl_21;		// 0x05f4 : ''
	UINT32                      ipc_ctrl_22;		// 0x05f8 : ''
	L9B0_P0L_IPC_CTRL_23        ipc_ctrl_23;		// 0x05fc : ''
	L9B0_P0L_IPC_CTRL_24        ipc_ctrl_24;		// 0x0600 : ''
	L9B0_P0L_IPC_CTRL_25        ipc_ctrl_25;		// 0x0604 : ''
	L9B0_P0L_IPC_CTRL_26        ipc_ctrl_26;		// 0x0608 : ''
	L9B0_P0L_IPC_CTRL_27        ipc_ctrl_27;		// 0x060c : ''
	UINT32                      reserved06[12];		// 0x0610 ~ 0x063c
	L9B0_P0L_TPD_CTRL_00        tpd_ctrl_00;		// 0x0640 : ''
	L9B0_P0L_TPD_CTRL_01        tpd_ctrl_01;		// 0x0644 : ''
	L9B0_P0L_TPD_CTRL_02        tpd_ctrl_02;		// 0x0648 : ''
	L9B0_P0L_TPD_CTRL_03        tpd_ctrl_03;		// 0x064c : ''
	L9B0_P0L_TPD_CTRL_04        tpd_ctrl_04;		// 0x0650 : ''
	L9B0_P0L_TPD_CTRL_05        tpd_ctrl_05;		// 0x0654 : ''
	L9B0_P0L_TPD_CTRL_06        tpd_ctrl_06;		// 0x0658 : ''
	L9B0_P0L_TPD_CTRL_07        tpd_ctrl_07;		// 0x065c : ''
	L9B0_P0L_TPD_STAT_00        tpd_stat_00;		// 0x0660 : ''
	L9B0_P0L_TPD_STAT_01        tpd_stat_01;		// 0x0664 : ''
	UINT32                      reserved07[2];		// 0x0668 ~ 0x066c
	L9B0_P0L_BBD_CTRL_00        bbd_ctrl_00;		// 0x0670 : ''
	L9B0_P0L_BBD_CTRL_01        bbd_ctrl_01;		// 0x0674 : ''
	L9B0_P0L_BBD_CTRL_02        bbd_ctrl_02;		// 0x0678 : ''
	L9B0_P0L_BBD_STAT_00        bbd_stat_00;		// 0x067c : ''
	L9B0_P0L_BBD_STAT_01        bbd_stat_01;		// 0x0680 : ''
	L9B0_P0L_APL_STAT_00        apl_stat_00;		// 0x0684 : ''
	UINT32                      reserved08[2];		// 0x0688 ~ 0x068c
	L9B0_P0L_CTI_CTRL_00        cti_ctrl_00;		// 0x0690 : ''
	UINT32                      reserved09[3];		// 0x0694 ~ 0x069c
	L9B0_P0L_3DFD_CTRL_00       tridfd_ctrl_00;		// 0x06a0 : ''
	L9B0_P0L_3DFD_CTRL_01       tridfd_ctrl_01;		// 0x06a4 : ''
	L9B0_P0L_3DFD_CTRL_02       tridfd_ctrl_02;		// 0x06a8 : ''
	L9B0_P0L_3DFD_CTRL_03       tridfd_ctrl_03;		// 0x06ac : ''
	L9B0_P0L_3DFD_STAT_00       tridfd_stat_00;		// 0x06b0 : ''
	L9B0_P0L_3DFD_STAT_01       tridfd_stat_01;		// 0x06b4 : ''
	L9B0_P0L_3DFD_STAT_02       tridfd_stat_02;		// 0x06b8 : ''
	L9B0_P0L_3DFD_STAT_03       tridfd_stat_03;		// 0x06bc : ''
	L9B0_P0L_3DFD_STAT_04       tridfd_stat_04;		// 0x06c0 : ''
	L9B0_P0L_3DFD_STAT_05       tridfd_stat_05;		// 0x06c4 : ''
	L9B0_P0L_3DFD_STAT_06       tridfd_stat_06;		// 0x06c8 : ''
	L9B0_P0L_3DFD_STAT_07       tridfd_stat_07;		// 0x06cc : ''
} DE_P0L_REG_L9B0_T;

typedef struct {
	L9B0_P0R_PE0_LOAD           pe0_load;			// 0x2400 : ''
	L9B0_P0R_PE0_INTR           pe0_intr;			// 0x2404 : ''
	L9B0_P0R_PE0_STATUS0        pe0_status0;		// 0x2408 : ''
	L9B0_P0R_PE0_STATUS1        pe0_status1;		// 0x240c : ''
	L9B0_P0R_PE0_OPMODE         pe0_opmode;			// 0x2410 : ''
	L9B0_P0R_PE0_SRC_SIZE       pe0_src_size;		// 0x2414 : ''
	L9B0_P0R_PE0_FIELD          pe0_field;			// 0x2418 : ''
	L9B0_P0R_PE0_PARAM_BY_DDR   pe0_param_by_ddr;	// 0x241c : ''
	L9B0_P0R_WIN_CTRL_0         win_ctrl_0;			// 0x2420 : ''
	L9B0_P0R_WIN_CTRL_1         win_ctrl_1;			// 0x2424 : ''
	L9B0_P0R_WIN_CTRL_2         win_ctrl_2;			// 0x2428 : ''
	L9B0_P0R_WIN_CTRL_3         win_ctrl_3;			// 0x242c : ''
	UINT32                      reserved10[4];		// 0x2430 ~ 0x243c
	L9B0_P0R_TNR_CTRL_00        tnr_ctrl_00;		// 0x2440 : ''
	L9B0_P0R_TNR_CTRL_01        tnr_ctrl_01;		// 0x2444 : ''
	L9B0_P0R_TNR_CTRL_02        tnr_ctrl_02;		// 0x2448 : ''
	L9B0_P0R_TNR_CTRL_03        tnr_ctrl_03;		// 0x244c : ''
	L9B0_P0R_TNR_CTRL_04        tnr_ctrl_04;		// 0x2450 : ''
	L9B0_P0R_TNR_CTRL_05        tnr_ctrl_05;		// 0x2454 : ''
	L9B0_P0R_TNR_CTRL_06        tnr_ctrl_06;		// 0x2458 : ''
	L9B0_P0R_TNR_CTRL_07        tnr_ctrl_07;		// 0x245c : ''
	L9B0_P0R_TNR_CTRL_08        tnr_ctrl_08;		// 0x2460 : ''
	L9B0_P0R_TNR_CTRL_09        tnr_ctrl_09;		// 0x2464 : ''
	L9B0_P0R_TNR_CTRL_10        tnr_ctrl_10;		// 0x2468 : ''
	L9B0_P0R_TNR_CTRL_11        tnr_ctrl_11;		// 0x246c : ''
	L9B0_P0R_TNR_CTRL_12        tnr_ctrl_12;		// 0x2470 : ''
	L9B0_P0R_TNR_CTRL_13        tnr_ctrl_13;		// 0x2474 : ''
	L9B0_P0R_TNR_CTRL_14        tnr_ctrl_14;		// 0x2478 : ''
	L9B0_P0R_TNR_CTRL_15        tnr_ctrl_15;		// 0x247c : ''
	L9B0_P0R_TNR_CTRL_16        tnr_ctrl_16;		// 0x2480 : ''
	L9B0_P0R_TNR_CTRL_17        tnr_ctrl_17;		// 0x2484 : ''
	L9B0_P0R_TNR_CTRL_18        tnr_ctrl_18;		// 0x2488 : ''
	L9B0_P0R_TNR_CTRL_19        tnr_ctrl_19;		// 0x248c : ''
	L9B0_P0R_TNR_CTRL_20        tnr_ctrl_20;		// 0x2490 : ''
	L9B0_P0R_TNR_CTRL_21        tnr_ctrl_21;		// 0x2494 : ''
	L9B0_P0R_TNR_CTRL_22        tnr_ctrl_22;		// 0x2498 : ''
	L9B0_P0R_TNR_CTRL_23        tnr_ctrl_23;		// 0x249c : ''
	L9B0_P0R_TNR_CTRL_24        tnr_ctrl_24;		// 0x24a0 : ''
	L9B0_P0R_TNR_CTRL_25        tnr_ctrl_25;		// 0x24a4 : ''
	L9B0_P0R_TNR_CTRL_26        tnr_ctrl_26;		// 0x24a8 : ''
	L9B0_P0R_TNR_CTRL_27        tnr_ctrl_27;		// 0x24ac : ''
	L9B0_P0R_TNR_CTRL_28        tnr_ctrl_28;		// 0x24b0 : ''
	L9B0_P0R_TNR_CTRL_29        tnr_ctrl_29;		// 0x24b4 : ''
	L9B0_P0R_TNR_CTRL_30        tnr_ctrl_30;		// 0x24b8 : ''
	L9B0_P0R_TNR_CTRL_31        tnr_ctrl_31;		// 0x24bc : ''
	L9B0_P0R_TNR_STATUS_00      tnr_status_00;		// 0x24c0 : ''
	L9B0_P0R_TNR_STATUS_01      tnr_status_01;		// 0x24c4 : ''
	L9B0_P0R_TNR_STATUS_02      tnr_status_02;		// 0x24c8 : ''
	L9B0_P0R_TNR_STATUS_03      tnr_status_03;		// 0x24cc : ''
	L9B0_P0R_TNR_MAIN_LUT_00    tnr_main_lut_00;	// 0x24d0 : ''
	L9B0_P0R_TNR_MAIN_LUT_01    tnr_main_lut_01;	// 0x24d4 : ''
	L9B0_P0R_TNR_MAIN_LUT_02    tnr_main_lut_02;	// 0x24d8 : ''
	UINT32                      reserved11;			// 0x24dc
	L9B0_P0R_TNR_CTRL_32        tnr_ctrl_32;		// 0x24e0 : ''
	L9B0_P0R_TNR_CTRL_33        tnr_ctrl_33;		// 0x24e4 : ''
	L9B0_P0R_TNR_CTRL_34        tnr_ctrl_34;		// 0x24e8 : ''
	L9B0_P0R_TNR_CTRL_35        tnr_ctrl_35;		// 0x24ec : ''
	L9B0_P0R_TNR_CRG_CTRL_00    tnr_crg_ctrl_00;	// 0x24f0 : ''
	L9B0_P0R_TNR_CRG_CTRL_01    tnr_crg_ctrl_01;	// 0x24f4 : ''
	UINT32                      reserved12[2];		// 0x24f8 ~ 0x24fc
	L9B0_P0R_IPC_CTRL_00        ipc_ctrl_00;		// 0x2500 : ''
	L9B0_P0R_IPC_CTRL_01        ipc_ctrl_01;		// 0x2504 : ''
	L9B0_P0R_IPC_CTRL_02        ipc_ctrl_02;		// 0x2508 : ''
	L9B0_P0R_IPC_CTRL_03        ipc_ctrl_03;		// 0x250c : ''
	L9B0_P0R_IPC_CTRL_04        ipc_ctrl_04;		// 0x2510 : ''
	L9B0_P0R_IPC_CTRL_05        ipc_ctrl_05;		// 0x2514 : ''
	L9B0_P0R_IPC_CTRL_06        ipc_ctrl_06;		// 0x2518 : ''
	L9B0_P0R_IPC_CTRL_07        ipc_ctrl_07;		// 0x251c : ''
	L9B0_P0R_IPC_CTRL_08        ipc_ctrl_08;		// 0x2520 : ''
	L9B0_P0R_IPC_CTRL_09        ipc_ctrl_09;		// 0x2524 : ''
	L9B0_P0R_IPC_CTRL_10        ipc_ctrl_10;		// 0x2528 : ''
	L9B0_P0R_IPC_CTRL_11        ipc_ctrl_11;		// 0x252c : ''
	L9B0_P0R_IPC_CTRL_12        ipc_ctrl_12;		// 0x2530 : ''
	L9B0_P0R_IPC_CTRL_13        ipc_ctrl_13;		// 0x2534 : ''
	L9B0_P0R_IPC_CTRL_14        ipc_ctrl_14;		// 0x2538 : ''
	L9B0_P0R_IPC_CTRL_15        ipc_ctrl_15;		// 0x253c : ''
	L9B0_P0R_IPC_CTRL_16        ipc_ctrl_16;		// 0x2540 : ''
	L9B0_P0R_IPC_CTRL_17        ipc_ctrl_17;		// 0x2544 : ''
	L9B0_P0R_IPC_CTRL_18        ipc_ctrl_18;		// 0x2548 : ''
	L9B0_P0R_IPC_CTRL_19        ipc_ctrl_19;		// 0x254c : ''
	L9B0_P0R_IPC_STATUS_00      ipc_status_00;		// 0x2550 : ''
	L9B0_P0R_IPC_STATUS_01      ipc_status_01;		// 0x2554 : ''
	L9B0_P0R_IPC_STATUS_02      ipc_status_02;		// 0x2558 : ''
	L9B0_P0R_IPC_STATUS_03      ipc_status_03;		// 0x255c : ''
	UINT32                      reserved13[8];		// 0x2560 ~ 0x257c
	L9B0_P0R_VFLT_CTRL          vflt_ctrl;			// 0x2580 : ''
	UINT32                      reserved14;			// 0x2584
	L9B0_P0R_MNR_CTRL_00        mnr_ctrl_00;		// 0x2588 : ''
	L9B0_P0R_MNR_CTRL_01        mnr_ctrl_01;		// 0x258c : ''
	L9B0_P0R_MNR_CTRL_02        mnr_ctrl_02;		// 0x2590 : ''
	L9B0_P0R_MNR_CTRL_03        mnr_ctrl_03;		// 0x2594 : ''
	L9B0_P0R_MNR_CTRL_04        mnr_ctrl_04;		// 0x2598 : ''
	L9B0_P0R_MNR_CTRL_05        mnr_ctrl_05;		// 0x259c : ''
	L9B0_P0R_MNR_CTRL_06        mnr_ctrl_06;		// 0x25a0 : ''
	UINT32                      reserved15;			// 0x25a4
	L9B0_P0R_VFILTER_01         vfilter_01;			// 0x25a8 : ''
	L9B0_P0R_BNR_DC_CTRL_00     bnr_dc_ctrl_00;		// 0x25ac : ''
	L9B0_P0R_BNR_DC_CTRL_01     bnr_dc_ctrl_01;		// 0x25b0 : ''
	L9B0_P0R_BNR_DC_CTRL_02     bnr_dc_ctrl_02;		// 0x25b4 : ''
	L9B0_P0R_BNR_DC_CTRL_03     bnr_dc_ctrl_03;		// 0x25b8 : ''
	L9B0_P0R_BNR_AC_CTRL_06     bnr_ac_ctrl_06;		// 0x25bc : ''
	L9B0_P0R_BNR_AC_CTRL_00     bnr_ac_ctrl_00;		// 0x25c0 : ''
	L9B0_P0R_BNR_AC_CTRL_01     bnr_ac_ctrl_01;		// 0x25c4 : ''
	L9B0_P0R_BNR_AC_CTRL_02     bnr_ac_ctrl_02;		// 0x25c8 : ''
	L9B0_P0R_BNR_AC_CTRL_03     bnr_ac_ctrl_03;		// 0x25cc : ''
	L9B0_P0R_BNR_AC_CTRL_04     bnr_ac_ctrl_04;		// 0x25d0 : ''
	L9B0_P0R_BNR_AC_CTRL_05     bnr_ac_ctrl_05;		// 0x25d4 : ''
	L9B0_P0R_DNR_MAX_CTRL       dnr_max_ctrl;		// 0x25d8 : ''
	L9B0_P0R_DNR_DBAR_CTRL      dnr_dbar_ctrl;		// 0x25dc : ''
	L9B0_P0R_BNR_STAT_0         bnr_stat_0;			// 0x25e0 : ''
	L9B0_P0R_DER_CTRL_0         der_ctrl_0;			// 0x25e4 : ''
	L9B0_P0R_DER_CTRL_1         der_ctrl_1;			// 0x25e8 : ''
	UINT32                      reserved16;			// 0x25ec
	L9B0_P0R_IPC_CTRL_20        ipc_ctrl_20;		// 0x25f0 : ''
	L9B0_P0R_IPC_CTRL_21        ipc_ctrl_21;		// 0x25f4 : ''
	UINT32                      ipc_ctrl_22;		// 0x25f8 : ''
	L9B0_P0R_IPC_CTRL_23        ipc_ctrl_23;		// 0x25fc : ''
	L9B0_P0R_IPC_CTRL_24        ipc_ctrl_24;		// 0x2600 : ''
	L9B0_P0R_IPC_CTRL_25        ipc_ctrl_25;		// 0x2604 : ''
	L9B0_P0R_IPC_CTRL_26        ipc_ctrl_26;		// 0x2608 : ''
	L9B0_P0R_IPC_CTRL_27        ipc_ctrl_27;		// 0x260c : ''
	UINT32                      reserved17[12];		// 0x2610 ~ 0x263c
	L9B0_P0R_TPD_CTRL_00        tpd_ctrl_00;		// 0x2640 : ''
	UINT32                      reserved18[11];		// 0x2644 ~ 0x266c
	L9B0_P0R_BBD_CTRL_00        bbd_ctrl_00;		// 0x2670 : ''
	L9B0_P0R_BBD_CTRL_01        bbd_ctrl_01;		// 0x2674 : ''
	L9B0_P0R_BBD_CTRL_02        bbd_ctrl_02;		// 0x2678 : ''
	L9B0_P0R_BBD_STAT_00        bbd_stat_00;		// 0x267c : ''
	L9B0_P0R_BBD_STAT_01        bbd_stat_01;		// 0x2680 : ''
	L9B0_P0R_APL_STAT_00        apl_stat_00;		// 0x2684 : ''
	UINT32                      reserved19[2];		// 0x2688 ~ 0x268c
	L9B0_P0R_CTI_CTRL_00        cti_ctrl_00;		// 0x2690 : ''
} DE_P0R_REG_L9B0_T;

#endif	//_REG_PE0_L9B0_h
