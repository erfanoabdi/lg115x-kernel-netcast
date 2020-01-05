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

#ifndef _REG_PE0_L9A0_h
#define _REG_PE0_L9A0_h

typedef struct { // 0x0400
	UINT32 load_time                           : 1;   //     0
	UINT32 load_enable                         : 1;   //     1
	UINT32 load_type                           : 1;   //     2
} L9A0_P0L_PE0_LOAD_T;

typedef struct { // 0x0404
	UINT32 intr_enable                         : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 intr_src                            : 3;   //  6: 4
	UINT32                                     : 9;   // 15: 7
	UINT32 intr_line_pos                       : 11;  // 26:16
} L9A0_P0L_PE0_INTR_T;

typedef struct { // 0x0408
	UINT32 tnr_frame_id                        : 4;   //  3: 0
	UINT32 ipc_frame_id                        : 4;   //  7: 4
	UINT32 tnrw_y_frame_id                     : 4;   // 11: 8
	UINT32 tnrw_c_frame_id                     : 4;   // 15:12
	UINT32 dnr_frame_id                        : 8;   // 23:16
	UINT32 pic_init_frame_id                   : 4;   // 27:24
} L9A0_P0L_PE0_STATUS0_T;

typedef struct { // 0x040c
	UINT32 line_cnt                            : 11;  // 10: 0
} L9A0_P0L_PE0_STATUS1_T;

typedef struct { // 0x0410
	UINT32 tnr_c_en                            : 1;   //     0
	UINT32 tnr_y_en                            : 1;   //     1
	UINT32 ipc_c_en                            : 1;   //     2
	UINT32 ipc_y_en                            : 1;   //     3
	UINT32 tnr_c_444_as_420                    : 1;   //     4
	UINT32 tnr_y2_en                           : 1;   //     5
	UINT32 force_420                           : 1;   //     6
	UINT32                                     : 1;   //     7
	UINT32 mif_last_mode                       : 3;   // 10: 8
	UINT32                                     : 5;   // 15:11
	UINT32 detour_enable                       : 1;   //    16
} L9A0_P0L_PE0_OPMODE_T;

typedef struct { // 0x0414
	UINT32 hsize                               : 11;  // 10: 0
	UINT32                                     : 2;   // 12:11
	UINT32 cs_type                             : 3;   // 15:13
	UINT32 vsize                               : 12;  // 27:16
	UINT32                                     : 3;   // 30:28
	UINT32 scan_type                           : 1;   //    31
} L9A0_P0L_PE0_SRC_SIZE_T;

typedef struct { // 0x0418
	UINT32 field_id                            : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 field_mode                          : 2;   //  5: 4
} L9A0_P0L_PE0_FIELD_T;

typedef struct { // 0x041c
	UINT32                                     : 9;   //  8: 0
	UINT32 stride                              : 2;   // 10: 9
	UINT32                                     : 5;   // 15:11
	UINT32 vsize                               : 8;   // 23:16
	UINT32                                     : 6;   // 29:24
	UINT32 endian                              : 1;   //    30
	UINT32 update_by_ddr                       : 1;   //    31
} L9A0_P0L_PE0_PARAM_BY_DDR_T;

typedef struct { // 0x0420
	UINT32 x0                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y0                                  : 11;  // 26:16
} L9A0_P0L_WIN_CTRL_0_T;

typedef struct { // 0x0424
	UINT32 x1                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y1                                  : 11;  // 26:16
} L9A0_P0L_WIN_CTRL_1_T;

typedef struct { // 0x0428
	UINT32 x0                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y0                                  : 11;  // 26:16
	UINT32                                     : 1;   //    27
	UINT32 ac_bnr_feature_cal_mode             : 2;   // 29:28
} L9A0_P0L_WIN_CTRL_2_T;

typedef struct { // 0x042c
	UINT32 x1                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y1                                  : 11;  // 26:16
} L9A0_P0L_WIN_CTRL_3_T;

typedef struct { // 0x0440
	UINT32 tnr_enable                          : 1;   //     0
	UINT32 wa2_enable                          : 1;   //     1
	UINT32 nt_lvl_hsub                         : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 calc_motion_3f_en                   : 1;   //     4
	UINT32 hist_motion_3f_en                   : 1;   //     5
	UINT32                                     : 1;   //     6
	UINT32 frame_skip_enable_for_3d            : 1;   //     7
	UINT32 calc_motion_sample_mode             : 2;   //  9: 8
	UINT32 hist_motion_sample_mode             : 2;   // 11:10
	UINT32                                     : 2;   // 13:12
	UINT32 calc_motion_flt_enable              : 1;   //    14
	UINT32 calc_motion_flt_type                : 1;   //    15
	UINT32 calc_motion_max_yc                  : 1;   //    16
	UINT32 hist_motion_max_yc                  : 1;   //    17
	UINT32 average_win_for_color_region        : 2;   // 19:18
	UINT32 average_win_for_nr_calc             : 2;   // 21:20
	UINT32                                     : 1;   //    22
	UINT32 variance_sample_mode                : 1;   //    23
} L9A0_P0L_TNR_CTRL_00_T;

typedef struct { // 0x0444
	UINT32 y_th_lo                             : 10;  //  9: 0
	UINT32                                     : 2;   // 11:10
	UINT32 y_th_hi                             : 10;  // 21:12
	UINT32 svar_mux_ctrl                       : 2;   // 23:22
	UINT32 svar_hist_n_pct                     : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_01_T;

typedef struct { // 0x0448
	UINT32 ns_g_fit_th0                        : 8;   //  7: 0
	UINT32 ns_g_fit_th1                        : 8;   // 15: 8
	UINT32 ns_x_pn_minus                       : 4;   // 19:16
	UINT32                                     : 4;   // 23:20
	UINT32 ns_iir_alpha                        : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_02_T;

typedef struct { // 0x044c
	UINT32 wa_min                              : 8;   //  7: 0
	UINT32 wa_max                              : 8;   // 15: 8
	UINT32 wa_k                                : 7;   // 22:16
	UINT32                                     : 1;   //    23
	UINT32 tnr_hist_wa_th                      : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_03_T;

typedef struct { // 0x0450
	UINT32 nl_peak0                            : 8;   //  7: 0
	UINT32 nl_peak1                            : 8;   // 15: 8
	UINT32 nl_peak2                            : 8;   // 23:16
	UINT32 nl_peak3                            : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_04_T;

typedef struct { // 0x0454
	UINT32 nt_min                              : 8;   //  7: 0
	UINT32 nt_max                              : 8;   // 15: 8
	UINT32 gm_low                              : 8;   // 23:16
	UINT32 gm_high                             : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_05_T;

typedef struct { // 0x0458
	UINT32 nt_at_as_th                         : 8;   //  7: 0
	UINT32 nt_iir_alpha                        : 8;   // 15: 8
	UINT32 adj_alpha_k0                        : 8;   // 23:16
	UINT32 adj_alpha_k1                        : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_06_T;

typedef struct { // 0x045c
	UINT32 alpha_lut_ind0                      : 8;   //  7: 0
	UINT32 alpha_lut_ind1                      : 8;   // 15: 8
	UINT32 alpha_lut_ind2                      : 8;   // 23:16
	UINT32 alpha_lut_ind3                      : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_07_T;

typedef struct { // 0x0460
	UINT32 alpha_lut_ind4                      : 8;   //  7: 0
	UINT32 alpha_lut_ind5                      : 8;   // 15: 8
	UINT32 alpha_lut_ind6                      : 8;   // 23:16
	UINT32 adj_alpha_nt_lvl_th                 : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_08_T;

typedef struct { // 0x0464
	UINT32 scene_change_enable                 : 1;   //     0
	UINT32 scene_change_max_flt_en             : 1;   //     1
	UINT32 scene_change_measure_sel            : 1;   //     2
	UINT32 scene_change_prev_hist_calc_en      : 1;   //     3
	UINT32 scene_change_manual_set             : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 scene_change_max_flt_tap            : 2;   //  9: 8
	UINT32                                     : 2;   // 11:10
	UINT32 scene_change_scale                  : 3;   // 14:12
	UINT32                                     : 1;   //    15
	UINT32 scene_change_th                     : 8;   // 23:16
} L9A0_P0L_TNR_CTRL_09_T;

typedef struct { // 0x0468
	UINT32 dbg_show_tnr_param                  : 5;   //  4: 0
	UINT32                                     : 3;   //  7: 5
	UINT32 dbg_force_wa                        : 1;   //     8
	UINT32 dbg_force_calc_motion               : 1;   //     9
	UINT32 dbg_force_lut_alpha                 : 1;   //    10
	UINT32 dbg_force_adj_alpha                 : 1;   //    11
	UINT32 dbg_force_final_alpha               : 1;   //    12
	UINT32                                     : 1;   //    13
	UINT32 chroma_polarity_check               : 1;   //    14
	UINT32 ignore_active_window                : 1;   //    15
	UINT32 dbg_tnrw_port_ctrl                  : 2;   // 17:16
} L9A0_P0L_TNR_CTRL_10_T;

typedef struct { // 0x046c
	UINT32 dbg_calc_motion                     : 8;   //  7: 0
	UINT32 dbg_alpha                           : 8;   // 15: 8
} L9A0_P0L_TNR_CTRL_11_T;

typedef struct { // 0x0470
	UINT32 force_ns_lvl                        : 1;   //     0
	UINT32                                     : 7;   //  7: 1
	UINT32 force_ns_lvl_val                    : 8;   // 15: 8
	UINT32 adjust_ns_lvl                       : 1;   //    16
	UINT32                                     : 7;   // 23:17
	UINT32 adjust_ns_lvl_val                   : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_12_T;

typedef struct { // 0x0474
	UINT32 force_nt_lvl                        : 1;   //     0
	UINT32                                     : 7;   //  7: 1
	UINT32 force_nt_lvl_val                    : 8;   // 15: 8
	UINT32 adjust_nt_lvl                       : 1;   //    16
	UINT32                                     : 7;   // 23:17
	UINT32 adjust_nt_lvl_val                   : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_13_T;

typedef struct { // 0x0478
	UINT32 x0                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y0                                  : 11;  // 26:16
	UINT32                                     : 4;   // 30:27
	UINT32 noise_measure_win_en                : 1;   //    31
} L9A0_P0L_TNR_CTRL_14_T;

typedef struct { // 0x047c
	UINT32 x1                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y1                                  : 11;  // 26:16
} L9A0_P0L_TNR_CTRL_15_T;

typedef struct { // 0x0480
	UINT32 show_dbg_bar_ctrl0                  : 8;   //  7: 0
	UINT32 show_dbg_bar_ctrl1                  : 8;   // 15: 8
	UINT32 show_dbg_bar_ctrl2                  : 8;   // 23:16
	UINT32 show_dbg_bar_ctrl3                  : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_16_T;

typedef struct { // 0x0484
	UINT32 show_dbg_bar_ctrl4                  : 8;   //  7: 0
} L9A0_P0L_TNR_CTRL_17_T;

typedef struct { // 0x0488
	UINT32 crgn_gain_enable                    : 1;   //     0
	UINT32 luma_gain_enable                    : 1;   //     1
	UINT32 saturation_gain_enable              : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 input_for_luma                      : 2;   //  5: 4
	UINT32                                     : 2;   //  7: 6
	UINT32 input_for_crgn_satr                 : 1;   //     8
	UINT32                                     : 7;   // 15: 9
	UINT32 y_gain                              : 8;   // 23:16
	UINT32 c_gain                              : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_18_T;

typedef struct { // 0x048c
	UINT32 luma_gain_p0_x                      : 8;   //  7: 0
	UINT32 luma_gain_p1_x                      : 8;   // 15: 8
	UINT32 luma_gain_p2_x                      : 8;   // 23:16
	UINT32 luma_gain_p3_x                      : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_19_T;

typedef struct { // 0x0490
	UINT32 luma_gain_p4_x                      : 8;   //  7: 0
	UINT32 luma_gain_p5_x                      : 8;   // 15: 8
	UINT32 luma_gain_p6_x                      : 8;   // 23:16
	UINT32 luma_gain_p7_x                      : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_20_T;

typedef struct { // 0x0494
	UINT32 luma_gain_p0_y                      : 8;   //  7: 0
	UINT32 luma_gain_p1_y                      : 8;   // 15: 8
	UINT32 luma_gain_p2_y                      : 8;   // 23:16
	UINT32 luma_gain_p3_y                      : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_21_T;

typedef struct { // 0x0498
	UINT32 luma_gain_p4_y                      : 8;   //  7: 0
	UINT32 luma_gain_p5_y                      : 8;   // 15: 8
	UINT32 luma_gain_p6_y                      : 8;   // 23:16
	UINT32 luma_gain_p7_y                      : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_22_T;

typedef struct { // 0x049c
	UINT32 saturation_gain_p0_x                : 8;   //  7: 0
	UINT32 saturation_gain_p1_x                : 8;   // 15: 8
	UINT32 saturation_gain_p2_x                : 8;   // 23:16
	UINT32 saturation_gain_p3_x                : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_23_T;

typedef struct { // 0x04a0
	UINT32 saturation_gain_p4_x                : 8;   //  7: 0
	UINT32 saturation_gain_p5_x                : 8;   // 15: 8
	UINT32 saturation_gain_p6_x                : 8;   // 23:16
	UINT32 saturation_gain_p7_x                : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_24_T;

typedef struct { // 0x04a4
	UINT32 saturation_gain_p0_y                : 8;   //  7: 0
	UINT32 saturation_gain_p1_y                : 8;   // 15: 8
	UINT32 saturation_gain_p2_y                : 8;   // 23:16
	UINT32 saturation_gain_p3_y                : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_25_T;

typedef struct { // 0x04a8
	UINT32 saturation_gain_p4_y                : 8;   //  7: 0
	UINT32 saturation_gain_p5_y                : 8;   // 15: 8
	UINT32 saturation_gain_p6_y                : 8;   // 23:16
	UINT32 saturation_gain_p7_y                : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_26_T;

typedef struct { // 0x04ac
	UINT32 crgn_gain_in_rgn0                   : 8;   //  7: 0
	UINT32 crgn_gain_out_rgn0                  : 8;   // 15: 8
	UINT32 crgn_gain_in_rgn1                   : 8;   // 23:16
	UINT32 crgn_gain_out_rgn1                  : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_27_T;

typedef struct { // 0x04b0
	UINT32 crgn_gain_in_rgn2                   : 8;   //  7: 0
	UINT32 crgn_gain_out_rgn2                  : 8;   // 15: 8
	UINT32 crgn_gain_in_rgn3                   : 8;   // 23:16
	UINT32 crgn_gain_out_rgn3                  : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_28_T;

typedef struct { // 0x04b4
	UINT32 wa2_min_slope                       : 8;   //  7: 0
	UINT32 wa2_max_slope                       : 8;   // 15: 8
	UINT32 wa2_cc                              : 8;   // 23:16
} L9A0_P0L_TNR_CTRL_29_T;

typedef struct { // 0x04b8
	UINT32 wa2_min                             : 8;   //  7: 0
	UINT32 wa2_max                             : 8;   // 15: 8
} L9A0_P0L_TNR_CTRL_30_T;

typedef struct { // 0x04bc
	UINT32 spatial_pre_flt_en_c                : 1;   //     0
	UINT32 spatial_pre_flt_en_y                : 1;   //     1
	UINT32                                     : 14;  // 15: 2
	UINT32 spatial_pre_flt_th_c                : 8;   // 23:16
	UINT32 spatial_pre_flt_th_y                : 8;   // 31:24
} L9A0_P0L_TNR_CTRL_31_T;

typedef struct { // 0x04c0
	UINT32 x_avg_t                             : 8;   //  7: 0
	UINT32 x_peak_t2                           : 8;   // 15: 8
	UINT32 nt_lvl                              : 8;   // 23:16
	UINT32 scene_change                        : 8;   // 31:24
} L9A0_P0L_TNR_STATUS_00_T;

typedef struct { // 0x04c4
	UINT32 x_avg_s                             : 8;   //  7: 0
	UINT32 x_peak_s                            : 8;   // 15: 8
	UINT32 ns_lvl                              : 8;   // 23:16
} L9A0_P0L_TNR_STATUS_01_T;

typedef struct { // 0x04c8
	UINT32 g_fit                               : 8;   //  7: 0
	UINT32 x_pn_s                              : 8;   // 15: 8
	UINT32 gm                                  : 8;   // 23:16
	UINT32 lp                                  : 8;   // 31:24
} L9A0_P0L_TNR_STATUS_02_T;

typedef struct { // 0x04cc
	UINT32 sum_of_temp_pel_diff                : 29;  // 28: 0
} L9A0_P0L_TNR_STATUS_03_T;

typedef struct { // 0x04d0
	UINT32 main_lut_indir_addr                 : 4;   //  3: 0
	UINT32                                     : 8;   // 11: 4
	UINT32 main_lut_ai_enable                  : 1;   //    12
} L9A0_P0L_TNR_MAIN_LUT_00_T;

typedef struct { // 0x04d4
	UINT32 main_lut_indir_data0                : 32;  // 31: 0
} L9A0_P0L_TNR_MAIN_LUT_01_T;

typedef struct { // 0x04d8
	UINT32 main_lut_indir_data1                : 32;  // 31: 0
} L9A0_P0L_TNR_MAIN_LUT_02_T;

typedef struct { // 0x04dc
	UINT32 ti_h_enable                         : 1;   //     0
	UINT32 ti_h_filter                         : 1;   //     1
	UINT32                                     : 6;   //  7: 2
	UINT32 ti_v_enable                         : 1;   //     8
	UINT32 ti_v_filter                         : 1;   //     9
	UINT32                                     : 6;   // 15:10
	UINT32 ti_h_gain                           : 8;   // 23:16
	UINT32 ti_v_gain                           : 8;   // 31:24
} L9A0_P0L_TI_CTRL_T;

typedef struct { // 0x04e0
	UINT32 nt_lvl_lut_indir_addr               : 3;   //  2: 0
	UINT32                                     : 9;   // 11: 3
	UINT32 nt_lvl_lut_ai_enable                : 1;   //    12
} L9A0_P0L_TNR_NT_LVL_LUT_00_T;

typedef struct { // 0x04e4
	UINT32 nt_lvl_lut_indir_data0              : 32;  // 31: 0
} L9A0_P0L_TNR_NT_LVL_LUT_01_T;

typedef struct { // 0x04e8
	UINT32 nt_lvl_lut_indir_data1              : 32;  // 31: 0
} L9A0_P0L_TNR_NT_LVL_LUT_02_T;

typedef struct { // 0x04ec
	UINT32 nt_lvl_lut_indir_data2              : 32;  // 31: 0
} L9A0_P0L_TNR_NT_LVL_LUT_03_T;

typedef struct { // 0x04f0
	UINT32 crgn_ctrl_indir_addr                : 8;   //  7: 0
	UINT32 crgn_ctrl_crgn_sel                  : 3;   // 10: 8
	UINT32                                     : 1;   //    11
	UINT32 crgn_ctrl_ai_enable                 : 1;   //    12
	UINT32 crgn_ctrl_hsv_csc_scaler_en         : 1;   //    13
	UINT32 crgn_ctrl_csc_sel                   : 1;   //    14
	UINT32 crgn_ctrl_access_off                : 1;   //    15
} L9A0_P0L_TNR_CRG_CTRL_00_T;

typedef struct { // 0x04f4
	UINT32 crgn_ctrl_indir_data                : 32;  // 31: 0
} L9A0_P0L_TNR_CRG_CTRL_01_T;

typedef struct { // 0x0500
	UINT32 luma_mode                           : 2;   //  1: 0
	UINT32                                     : 1;   //     2
	UINT32 luma_edi                            : 1;   //     3
	UINT32 chroma_mode                         : 2;   //  5: 4
	UINT32                                     : 1;   //     6
	UINT32 chroma_edi                          : 1;   //     7
	UINT32 chroma_adaptive_va_enable           : 1;   //     8
	UINT32 luma_adaptive_va_enable             : 1;   //     9
	UINT32 st_filter_mode                      : 2;   // 11:10
	UINT32                                     : 12;  // 23:12
	UINT32 ipc__fake__v_repeat_va_ta           : 2;   // 25:24
	UINT32                                     : 3;   // 28:26
	UINT32 film_mode_apply_c                   : 1;   //    29
	UINT32 film_mode_apply_y                   : 1;   //    30
	UINT32 film_mode_enable                    : 1;   //    31
} L9A0_P0L_IPC_CTRL_00_T;

typedef struct { // 0x0504
	UINT32 spatial_alpha_th0                   : 8;   //  7: 0
	UINT32 spatial_alpha_th1                   : 8;   // 15: 8
	UINT32 spatial_filter_tap_ctrl             : 8;   // 23:16
	UINT32                                     : 7;   // 30:24
	UINT32 texture_alpha_use_global_max        : 1;   //    31
} L9A0_P0L_IPC_CTRL_01_T;

typedef struct { // 0x0508
	UINT32 fuzzy_ctrl_point_x0                 : 8;   //  7: 0
	UINT32 fuzzy_ctrl_point_x4                 : 8;   // 15: 8
	UINT32 fuzzy_ctrl_point_x1                 : 8;   // 23:16
	UINT32 fuzzy_ctrl_point_y1                 : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_02_T;

typedef struct { // 0x050c
	UINT32 fuzzy_ctrl_point_x2                 : 8;   //  7: 0
	UINT32 fuzzy_ctrl_point_y2                 : 8;   // 15: 8
	UINT32 fuzzy_ctrl_point_x3                 : 8;   // 23:16
	UINT32 fuzzy_ctrl_point_y3                 : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_03_T;

typedef struct { // 0x0510
	UINT32 hmc_filter_range_top                : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 hmc_filter_range_bot                : 12;  // 27:16
} L9A0_P0L_IPC_CTRL_04_T;

typedef struct { // 0x0514
	UINT32 hmc_search_range                    : 4;   //  3: 0
	UINT32                                     : 4;   //  7: 4
	UINT32 hmc_h_motion_ratio                  : 6;   // 13: 8
	UINT32                                     : 2;   // 15:14
	UINT32 hmc_lock_filter_half_size           : 3;   // 18:16
	UINT32                                     : 5;   // 23:19
	UINT32 hmc_lock_filter_expand              : 1;   //    24
	UINT32 protect_filtering_enable            : 1;   //    25
	UINT32 protect_th                          : 6;   // 31:26
} L9A0_P0L_IPC_CTRL_05_T;

typedef struct { // 0x0518
	UINT32 hmc_point_max                       : 8;   //  7: 0
	UINT32 hmc_point_penalty                   : 8;   // 15: 8
	UINT32 hmc_point_valid_th                  : 8;   // 23:16
} L9A0_P0L_IPC_CTRL_06_T;

typedef struct { // 0x051c
	UINT32 hmc_enable                          : 1;   //     0
	UINT32 hmc_protection_errt__b07_01         : 7;   //  7: 1
	UINT32 hmc_protection_blend_alpha          : 8;   // 15: 8
	UINT32 hmc_protection_errt__b23_16         : 8;   // 23:16
	UINT32 hmc_protection_pndiff               : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_07_T;

typedef struct { // 0x0520
	UINT32 st_fuzzy_margin_0                   : 8;   //  7: 0
	UINT32 st_fuzzy_margin_1                   : 8;   // 15: 8
	UINT32                                     : 8;   // 23:16
	UINT32 tnr_debug_mode                      : 1;   //    24
	UINT32 tnr_debug_black_mask                : 1;   //    25
} L9A0_P0L_IPC_CTRL_08_T;

typedef struct { // 0x0524
	UINT32 fmd_vedge_th                        : 7;   //  6: 0
	UINT32 fmd_vedge_en                        : 1;   //     7
	UINT32 fmd_a_th                            : 6;   // 13: 8
	UINT32 use_3field_err_t                    : 1;   //    14
	UINT32 two_field_delay_mode                : 1;   //    15
	UINT32 fmd_margin_top                      : 8;   // 23:16
	UINT32 fmd_margin_bottom                   : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_09_T;

typedef struct { // 0x0528
	UINT32 film_inter_with                     : 2;   //  1: 0
	UINT32 hw_film_enable                      : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 tearing_detect_strength             : 1;   //     4
	UINT32 cross_check                         : 1;   //     5
	UINT32                                     : 1;   //     6
	UINT32 usediffpelcount                     : 1;   //     7
	UINT32 pn_diff_th                          : 8;   // 15: 8
	UINT32                                     : 12;  // 27:16
	UINT32 scalemeasureforhd                   : 2;   // 29:28
	UINT32 loading_time_ctrl                   : 1;   //    30
	UINT32 fmd_sw_bad_edit_en                  : 1;   //    31
} L9A0_P0L_IPC_CTRL_10_T;

typedef struct { // 0x052c
	UINT32 fmd_caption_range_top               : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 fmd_caption_range_bot               : 12;  // 27:16
	UINT32                                     : 2;   // 29:28
	UINT32 caption_flow_detected               : 1;   //    30
	UINT32 hmc_when_cap_not_detected           : 1;   //    31
} L9A0_P0L_IPC_CTRL_11_T;

typedef struct { // 0x0530
	UINT32 fmd_32_enable                       : 1;   //     0
	UINT32 fmd_22_enable                       : 1;   //     1
	UINT32 fmd_badediten                       : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 fmd_hw_bad_edit_mul_th              : 3;   //  6: 4
	UINT32                                     : 1;   //     7
	UINT32 fmd_hw_bad_edit_th_min              : 8;   // 15: 8
	UINT32 pcn_diff_th                         : 7;   // 22:16
	UINT32 fmd_arbitrary_6_4only               : 1;   //    23
	UINT32 fmd_stillconditition1               : 1;   //    24
	UINT32 fmd_stillconditition2               : 1;   //    25
	UINT32 fmd_arbitrary_still                 : 1;   //    26
	UINT32 fmd_arbitrary_3_2only               : 1;   //    27
	UINT32 fmd_still_cntth                     : 3;   // 30:28
	UINT32 fmd_still_cntth_en                  : 1;   //    31
} L9A0_P0L_IPC_CTRL_12_T;

typedef struct { // 0x0534
	UINT32 fmd32_stillth_pn                    : 8;   //  7: 0
	UINT32 fmd32_stillthpcn                    : 8;   // 15: 8
	UINT32 fmd32_pn_maxvalue_minth0            : 8;   // 23:16
	UINT32 fmd32_pn_maxvalue_minth1            : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_13_T;

typedef struct { // 0x0538
	UINT32 fmd32_min_field_num                 : 4;   //  3: 0
	UINT32                                     : 4;   //  7: 4
	UINT32 fmd32_pn_minvalue_maxth             : 8;   // 15: 8
	UINT32 fmd32_pn_maxminratio0               : 4;   // 19:16
	UINT32 fmd32_pn_maxminratio1               : 4;   // 23:20
	UINT32 fmd_32_pcn_small_weight             : 3;   // 26:24
} L9A0_P0L_IPC_CTRL_14_T;

typedef struct { // 0x053c
	UINT32 fmd22_stillth_pn                    : 8;   //  7: 0
	UINT32 fmd22_stillth_pcn                   : 8;   // 15: 8
	UINT32 bad_edit_sm_min_th                  : 12;  // 27:16
// fmd_22_min_val_max_th1 is removed from L9A0
//	UINT32 fmd_22_min_val_max_th1              : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_15_T;

typedef struct { // 0x0540
	UINT32 fmd22_minfieldnum0                  : 4;   //  3: 0
	UINT32 fmd22_minfieldnum1                  : 4;   //  7: 4
	UINT32 fmd22_minvaluemaxth1                : 8;   // 15: 8
	UINT32 fmd22_maxvalueminth1                : 8;   // 23:16
	UINT32 fmd22_maxminratio0                  : 4;   // 27:24
	UINT32 fmd22_maxminratio1                  : 4;   // 31:28
} L9A0_P0L_IPC_CTRL_16_T;

typedef struct { // 0x0544
	UINT32 dbg_show_mode                       : 5;   //  4: 0
	UINT32                                     : 6;   // 10: 5
	UINT32 dbg_show_black_mask                 : 1;   //    11
	UINT32 dbg_pprv_to_curr                    : 1;   //    12
	UINT32 dbg_prv3_to_prev                    : 1;   //    13
	UINT32 dbg_curr_to_pprv                    : 1;   //    14
	UINT32                                     : 1;   //    15
	UINT32 st_flt_ctrl_x0                      : 8;   // 23:16
	UINT32 st_flt_ctrl_x1                      : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_17_T;

typedef struct { // 0x0548
	UINT32 v_filt_ctrl_v_filt_range_top        : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 v_filt_ctrl_v_filt_range_bot        : 11;  // 26:16
	UINT32                                     : 4;   // 30:27
	UINT32 v_filt_ctrl_hmc_line_info_en        : 1;   //    31
} L9A0_P0L_IPC_CTRL_18_T;

typedef struct { // 0x054c
	UINT32 repeat_det_line_cnt_th              : 8;   //  7: 0
	UINT32 repeat_det_diff_pel_cnt_th          : 8;   // 15: 8
	UINT32 repeat_det_noise_th                 : 4;   // 19:16
} L9A0_P0L_IPC_CTRL_19_T;

typedef struct { // 0x0550
	UINT32 pc_cnt                              : 16;  // 15: 0
	UINT32 nc_cnt                              : 16;  // 31:16
} L9A0_P0L_IPC_STATUS_00_T;

typedef struct { // 0x0554
	UINT32 pn_cnt                              : 16;  // 15: 0
	UINT32 same_cnt                            : 16;  // 31:16
} L9A0_P0L_IPC_STATUS_01_T;

typedef struct { // 0x0558
	UINT32 fmd32_combwith                      : 2;   //  1: 0
	UINT32                                     : 1;   //     2
	UINT32 fmd32_detected                      : 1;   //     3
	UINT32 fmd32_lockingcnt                    : 8;   // 11: 4
	UINT32 fmd22_combwith                      : 2;   // 13:12
	UINT32                                     : 1;   //    14
	UINT32 fmd22_detected                      : 1;   //    15
	UINT32 fmd22_lockingcnt                    : 8;   // 23:16
	UINT32 fmd_comb_predict                    : 2;   // 25:24
	UINT32 bad_edit_detected_                  : 1;   //    26
	UINT32 fmd22_still_detected                : 1;   //    27
	UINT32 fmd32_still_detected                : 1;   //    28
	UINT32 repeat_detected                     : 1;   //    29
} L9A0_P0L_IPC_STATUS_02_T;

typedef struct { // 0x055c
	UINT32                                     : 16;  // 15: 0
	UINT32 fmd_badeditth_hw                    : 16;  // 31:16
} L9A0_P0L_IPC_STATUS_03_T;

typedef struct { // 0x0560
	UINT32 cc_filter_enable                    : 1;   //     0
	UINT32 cl_filter_enable                    : 1;   //     1
	UINT32 clc_detection_enable                : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 cc_cross_gain0                      : 4;   //  7: 4
	UINT32 cc_cross_gain1                      : 4;   // 11: 8
	UINT32 cl_ab_ratio                         : 4;   // 15:12
	UINT32 cl_y_hdistance                      : 2;   // 17:16
	UINT32 cl_c_hdistance                      : 2;   // 19:18
	UINT32 cl_var_th                           : 5;   // 24:20
	UINT32                                     : 1;   //    25
	UINT32 cc_margin128                        : 2;   // 27:26
	UINT32 cl_motion_a_filter                  : 1;   //    28
	UINT32 cl_motion_b_filter                  : 1;   //    29
	UINT32 cc_motion_a_filter                  : 1;   //    30
	UINT32 cc_motion_b_filter                  : 1;   //    31
} L9A0_P0L_CLC_CTRL_00_T;

typedef struct { // 0x0564
	UINT32 cl_motion_a_th                      : 8;   //  7: 0
	UINT32 cl_motion_b_th                      : 8;   // 15: 8
	UINT32 cc_motion_a_th                      : 8;   // 23:16
	UINT32 cc_motion_b_th                      : 8;   // 31:24
} L9A0_P0L_CLC_CTRL_01_T;

typedef struct { // 0x0568
	UINT32 cl_y_bound_th                       : 7;   //  6: 0
	UINT32                                     : 1;   //     7
	UINT32 cl_c_bound_th                       : 7;   // 14: 8
	UINT32 cl_c_bound_type                     : 1;   //    15
	UINT32 cl_y_bound_width_chroma             : 2;   // 17:16
	UINT32 cl_y_bound_ignore_cc                : 1;   //    18
	UINT32 cl_y_bound_ignore_p2                : 1;   //    19
	UINT32 cl_y_bound_ignore_p4                : 1;   //    20
} L9A0_P0L_CLC_CTRL_02_T;

typedef struct { // 0x056c
	UINT32 cl_sat_min                          : 8;   //  7: 0
	UINT32 cc_sat_min                          : 8;   // 15: 8
	UINT32 cc_sat_max                          : 8;   // 23:16
} L9A0_P0L_CLC_CTRL_03_T;

typedef struct { // 0x0570
	UINT32 p0l_clc_ctrl_04_f                   : 32;   // 31: 0
} L9A0_P0L_CLC_CTRL_04_T;

typedef struct { // 0x0574
	UINT32 clc_c_filter_when_cl_detected       : 1;   //     0
	UINT32                                     : 1;   //     1
	UINT32 clc_y_filter_when_cc_detected       : 2;   //  3: 2
	UINT32 clc_cc_line_mem_ctrl                : 2;   //  5: 4
	UINT32                                     : 2;   //  7: 6
	UINT32 clc_c_gain                          : 8;   // 15: 8
	UINT32 clc_dbg_show_mask                   : 12;  // 27:16
} L9A0_P0L_CLC_CTRL_05_T;

typedef struct { // 0x0578
	UINT32 cc_c_filter_gain                    : 8;   //  7: 0
	UINT32 cc_y_filter_when_cc_detected        : 1;   //     8
} L9A0_P0L_CLC_CTRL_06_T;

typedef struct { // 0x057c
	UINT32 cc_detection_count                  : 16;  // 15: 0
	UINT32 cl_detection_count                  : 16;  // 31:16
} L9A0_P0L_CLC_STAT_00_T;

typedef struct { // 0x0580
	UINT32 vfilterenable                       : 1;   //     0
	UINT32 vfilterlocalenable                  : 1;   //     1
	UINT32 vfilter_strength                    : 1;   //     2
	UINT32                                     : 5;   //  7: 3
	UINT32 vfilter_a_th                        : 8;   // 15: 8
	UINT32 vfilter_in_field_var                : 8;   // 23:16
	UINT32 vfilter_use_mc_mask                 : 1;   //    24
	UINT32 vfilter_expand                      : 1;   //    25
	UINT32 vfilter_center                      : 1;   //    26
	UINT32 vfilter_ul4                         : 1;   //    27
	UINT32 dbgshow_level                       : 2;   // 29:28
	UINT32                                     : 1;   //    30
	UINT32 dbgshow_enable                      : 1;   //    31
} L9A0_P0L_VFLT_CTRL_T;

typedef struct { // 0x0584
	UINT32 snr_enable                          : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 display_mode                        : 3;   //  6: 4
	UINT32                                     : 1;   //     7
	UINT32 normalization                       : 4;   // 11: 8
	UINT32 scaling_factor                      : 3;   // 14:12
	UINT32                                     : 1;   //    15
	UINT32 coring_factor                       : 8;   // 23:16
} L9A0_P0L_SNR_CTRL_00_T;

typedef struct { // 0x0588
	UINT32 mnr_enable                          : 1;   //     0
	UINT32 edge_gain_mapping_enable            : 1;   //     1
	UINT32 sel_sd_hd                           : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 debug_mode                          : 3;   //  6: 4
} L9A0_P0L_MNR_CTRL_00_T;

typedef struct { // 0x058c
	UINT32                                     : 16;  // 15: 0
	UINT32 hcoef_00                            : 4;   // 19:16
	UINT32 hcoef_01                            : 4;   // 23:20
	UINT32 hcoef_02                            : 4;   // 27:24
	UINT32 hcoef_03                            : 4;   // 31:28
} L9A0_P0L_MNR_CTRL_01_T;

typedef struct { // 0x0590
	UINT32 hcoef_04                            : 4;   //  3: 0
	UINT32 hcoef_05                            : 4;   //  7: 4
	UINT32 hcoef_06                            : 4;   // 11: 8
	UINT32 hcoef_07                            : 4;   // 15:12
	UINT32 hcoef_08                            : 4;   // 19:16
	UINT32 hcoef_09                            : 4;   // 23:20
	UINT32 hcoef_10                            : 4;   // 27:24
	UINT32 hcoef_11                            : 4;   // 31:28
} L9A0_P0L_MNR_CTRL_02_T;

typedef struct { // 0x0594
	UINT32 hcoef_12                            : 4;   //  3: 0
	UINT32 hcoef_13                            : 4;   //  7: 4
	UINT32 hcoef_14                            : 4;   // 11: 8
	UINT32 hcoef_15                            : 4;   // 15:12
	UINT32 hcoef_16                            : 4;   // 19:16
	UINT32                                     : 4;   // 23:20
	UINT32 x1_position                         : 8;   // 31:24
} L9A0_P0L_MNR_CTRL_03_T;

typedef struct { // 0x0598
	UINT32 x2_position                         : 8;   //  7: 0
	UINT32 x3_position                         : 8;   // 15: 8
	UINT32 x4_position                         : 8;   // 23:16
	UINT32 y1_position                         : 8;   // 31:24
} L9A0_P0L_MNR_CTRL_04_T;

typedef struct { // 0x059c
	UINT32 y2_position                         : 8;   //  7: 0
	UINT32 y3_position                         : 8;   // 15: 8
	UINT32 y4_position                         : 8;   // 23:16
	UINT32 filter_threshold                    : 8;   // 31:24
} L9A0_P0L_MNR_CTRL_05_T;

typedef struct { // 0x05a0
	UINT32 vcoef0                              : 4;   //  3: 0
	UINT32 vcoef1                              : 4;   //  7: 4
	UINT32 vcoef2                              : 4;   // 11: 8
	UINT32 vcoef3                              : 4;   // 15:12
	UINT32 vcoef4                              : 4;   // 19:16
	UINT32 vcoef5                              : 4;   // 23:20
	UINT32 vcoef6                              : 4;   // 27:24
} L9A0_P0L_MNR_CTRL_06_T;

typedef struct { // 0x05a8
	UINT32 cr_vfilter_global_en                : 1;   //     0
	UINT32 cr_vfilter_force_en                 : 1;   //     1
	UINT32 cr_global_frame_num_th              : 4;   //  5: 2
	UINT32                                     : 2;   //  7: 6
	UINT32 cr_vfilter_global_th                : 12;  // 19: 8
	UINT32 tearing_count                       : 12;  // 31:20
} L9A0_P0L_VFILTER_01_T;

typedef struct { // 0x05ac
	UINT32 dc_bnr_enable                       : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 sd_hd_sel                           : 1;   //     4
	UINT32 output_mux                          : 3;   //  7: 5
	UINT32 offset                              : 13;  // 20: 8
	UINT32                                     : 3;   // 23:21
	UINT32 gain                                : 8;   // 31:24
} L9A0_P0L_BNR_DC_CTRL_00_T;

typedef struct { // 0x05b0
	UINT32 blur_enable                         : 2;   //  1: 0
} L9A0_P0L_BNR_DC_CTRL_01_T;

typedef struct { // 0x05b4
	UINT32 dc_bnr_gain_ctrl_y2                 : 8;   //  7: 0
	UINT32 dc_bnr_gain_ctrl_x2                 : 8;   // 15: 8
	UINT32 dc_bnr_gain_ctrl_y3                 : 8;   // 23:16
	UINT32 dc_bnr_gain_ctrl_x3                 : 8;   // 31:24
} L9A0_P0L_BNR_DC_CTRL_02_T;

typedef struct { // 0x05b8
	UINT32 dc_bnr_gain_ctrl_y0                 : 8;   //  7: 0
	UINT32 dc_bnr_gain_ctrl_x0                 : 8;   // 15: 8
	UINT32 dc_bnr_gain_ctrl_y1                 : 8;   // 23:16
	UINT32 dc_bnr_gain_ctrl_x1                 : 8;   // 31:24
} L9A0_P0L_BNR_DC_CTRL_03_T;

typedef struct { // 0x05bc
	UINT32 ac_bnr_protect_lvl_4                : 8;   //  7: 0
	UINT32 ac_bnr_protect_lvl_3                : 8;   // 15: 8
	UINT32 ac_bnr_protect_lvl_2                : 8;   // 23:16
	UINT32 ac_bnr_protect_lvl_1                : 8;   // 31:24
} L9A0_P0L_BNR_AC_CTRL_06_T;

typedef struct { // 0x05c0
	UINT32 bnr_h_en                            : 1;   //     0
	UINT32 bnr_v_en                            : 1;   //     1
	UINT32                                     : 2;   //  3: 2
	UINT32 source_type                         : 1;   //     4
	UINT32 status_read_type                    : 1;   //     5
	UINT32 status_read_mode                    : 2;   //  7: 6
	UINT32 hbmax_gain                          : 4;   // 11: 8
	UINT32 vbmax_gain                          : 4;   // 15:12
	UINT32 strength_resolution                 : 1;   //    16
	UINT32                                     : 3;   // 19:17
	UINT32 fiter_type                          : 1;   //    20
	UINT32                                     : 3;   // 23:21
	UINT32 output_mux                          : 2;   // 25:24
} L9A0_P0L_BNR_AC_CTRL_00_T;

typedef struct { // 0x05c4
	UINT32 strength_h_x0                       : 8;   //  7: 0
	UINT32 strength_h_x1                       : 8;   // 15: 8
	UINT32 strength_h_max                      : 8;   // 23:16
} L9A0_P0L_BNR_AC_CTRL_01_T;

typedef struct { // 0x05c8
	UINT32 strength_v_x0                       : 8;   //  7: 0
	UINT32 strength_v_x1                       : 8;   // 15: 8
	UINT32 strength_v_max                      : 8;   // 23:16
} L9A0_P0L_BNR_AC_CTRL_02_T;

typedef struct { // 0x05cc
	UINT32 h_offset_mode                       : 1;   //     0
	UINT32 manual_offset_h_value               : 3;   //  3: 1
	UINT32 v_offset_mode                       : 1;   //     4
	UINT32 manual_offset_v_value               : 3;   //  7: 5
	UINT32 use_of_hysterisis                   : 4;   // 11: 8
	UINT32                                     : 4;   // 15:12
	UINT32 t_filter_weight                     : 8;   // 23:16
} L9A0_P0L_BNR_AC_CTRL_03_T;

typedef struct { // 0x05d0
	UINT32 max_delta_th0                       : 8;   //  7: 0
	UINT32 max_delta_th1                       : 8;   // 15: 8
	UINT32 h_blockness_th                      : 8;   // 23:16
	UINT32 h_weight_max                        : 8;   // 31:24
} L9A0_P0L_BNR_AC_CTRL_04_T;

typedef struct { // 0x05d4
	UINT32 use_of_hysterisis                   : 4;   //  3: 0
	UINT32 block_boundary_processing_type      : 1;   //     4
} L9A0_P0L_BNR_AC_CTRL_05_T;

typedef struct { // 0x05d8
	UINT32 enable_snr                          : 1;   //     0
	UINT32 enable_mnr                          : 1;   //     1
	UINT32 enable_der                          : 1;   //     2
	UINT32 enable_dc_bnr                       : 1;   //     3
	UINT32 enable_ac_bnr                       : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 debug_enable                        : 1;   //     8
	UINT32 debug_mode                          : 1;   //     9
	UINT32 debug_snr_enable                    : 1;   //    10
	UINT32 debug_mnr_enable                    : 1;   //    11
	UINT32 debug_der_enable                    : 1;   //    12
	UINT32 debug_dc_bnr_enable                 : 1;   //    13
	UINT32 debug_ac_bnr_enable                 : 1;   //    14
	UINT32                                     : 1;   //    15
	UINT32 win_control_enable                  : 1;   //    16
	UINT32 border_enable                       : 1;   //    17
} L9A0_P0L_DNR_MAX_CTRL_T;

typedef struct { // 0x05dc
	UINT32 debug_bar_en                        : 1;   //     0
	UINT32                                     : 1;   //     1
	UINT32 show_debug_bar_for_bnr              : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 gain                                : 3;   //  6: 4
	UINT32                                     : 1;   //     7
	UINT32 sd_hd_sel                           : 2;   //  9: 8
} L9A0_P0L_DNR_DBAR_CTRL_T;

typedef struct { // 0x05e0
	UINT32 ac_bnr_h_status                     : 8;   //  7: 0
	UINT32 ac_bnr_v_status                     : 8;   // 15: 8
	UINT32 dc_bnr_th                           : 14;  // 29:16
} L9A0_P0L_BNR_STAT_0_T;

typedef struct { // 0x05e4
	UINT32 der_en                              : 1;   //     0
	UINT32 out_mux                             : 3;   //  3: 1
	UINT32 bif_en                              : 1;   //     4
	UINT32 gain2weight_mapping                 : 1;   //     5
	UINT32                                     : 2;   //  7: 6
	UINT32 bif_th                              : 8;   // 15: 8
} L9A0_P0L_DER_CTRL_0_T;

typedef struct { // 0x05e8
	UINT32 gain_th0                            : 8;   //  7: 0
	UINT32 gain_th1                            : 8;   // 15: 8
} L9A0_P0L_DER_CTRL_1_T;

typedef struct { // 0x05f0
	UINT32 et_offset_                          : 8;   //  7: 0
	UINT32 motion_x_tearing_gain               : 8;   // 15: 8
	UINT32 tearing_gain                        : 8;   // 23:16
	UINT32 motion_gain                         : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_20_T;

typedef struct { // 0x05f4
	UINT32 motion_chroma_alpha                 : 8;   //  7: 0
	UINT32                                     : 8;   // 15: 8
	UINT32 v_gradiant_weight                   : 8;   // 23:16
	UINT32 h_gradiant_weight                   : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_21_T;

typedef struct { // 0x05f8
	UINT32 normalize_enable_motion             : 1;   //     0
	UINT32 increase_only_mode                  : 1;   //     1
	UINT32                                     : 2;   //  3: 2
	UINT32 normalize_enable_tearing            : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 normalize_base                      : 8;   // 15: 8
	UINT32 normalize_center                    : 8;   // 23:16
	UINT32 coring                              : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_22_T;

typedef struct { // 0x05fc
	UINT32 cr_wide_v_en                        : 1;   //     0
	UINT32 cr_narrow_v_en                      : 1;   //     1
	UINT32 cr_45_en                            : 1;   //     2
	UINT32 cr_15_en                            : 1;   //     3
	UINT32                                     : 12;  // 15: 4
	UINT32 post_median_enable                  : 1;   //    16
} L9A0_P0L_IPC_CTRL_23_T;

typedef struct { // 0x0600
	UINT32 ta_to_direction                     : 1;   //     0
	UINT32 ta_to_e_s                           : 1;   //     1
	UINT32                                     : 6;   //  7: 2
	UINT32 motion_max                          : 8;   // 15: 8
	UINT32 motion_min                          : 8;   // 23:16
	UINT32 ta_gain                             : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_24_T;

typedef struct { // 0x0604
	UINT32                                     : 16;  // 15: 0
	UINT32 h_gradiant_weight_                  : 8;   // 23:16
	UINT32 v_gradiant_weight_                  : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_25_T;

typedef struct { // 0x0608
	UINT32 ud_diff___b07_00                    : 8;   //  7: 0
	UINT32 ud_diff___b15_08                    : 8;   // 15: 8
	UINT32 lr_diff___b23_16                    : 8;   // 23:16
	UINT32 lr_diff___b31_24                    : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_26_T;

typedef struct { // 0x060c
	UINT32 new_va_enable                       : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 pe0_2d_dir_half_direction_enable    : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 e_s_offset_                         : 8;   // 15: 8
	UINT32 confidence_gain                     : 8;   // 23:16
	UINT32 e_s_gain                            : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_27_T;

typedef struct { // 0x0610
	UINT32 adaptive_va_enable                  : 1;   //     0
	UINT32 va_gain_inverse                     : 1;   //     1
	UINT32                                     : 6;   //  7: 2
	UINT32 motion_max                          : 8;   // 15: 8
	UINT32 motion_min                          : 8;   // 23:16
	UINT32 va_base                             : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_28_T;

typedef struct { // 0x0614
	UINT32 fmd22_maxvalueminth0                : 8;   //  7: 0
	UINT32 fmd22_minvaluemaxth0                : 8;   // 15: 8
	UINT32 fmd32_minvaluemaxth0                : 8;   // 23:16
	UINT32 fmd32_maxvalueminth0                : 8;   // 31:24
} L9A0_P0L_IPC_CTRL_29_T;

typedef struct { // 0x0640
	UINT32                                     : 4;   //  3: 0
	UINT32 mux_3                               : 4;   //  7: 4
	UINT32                                     : 4;   // 11: 8
	UINT32 mux_2                               : 4;   // 15:12
	UINT32                                     : 4;   // 19:16
	UINT32 mux_1                               : 4;   // 23:20
	UINT32 show_scale                          : 3;   // 26:24
	UINT32                                     : 1;   //    27
	UINT32 show_bar_1                          : 1;   //    28
	UINT32 show_bar_2                          : 1;   //    29
	UINT32 show_bar_3                          : 1;   //    30
	UINT32 show_bar_4                          : 1;   //    31
} L9A0_P0L_TPD_CTRL_00_T;

typedef struct { // 0x0670
	UINT32 bbd_en                              : 1;   //     0
	UINT32 hys_mode                            : 5;   //  5: 1
	UINT32 op_mode                             : 1;   //     6
	UINT32                                     : 1;   //     7
	UINT32 cnt_th                              : 8;   // 15: 8
	UINT32 diff_th                             : 8;   // 23:16
	UINT32 bbd_mux                             : 3;   // 26:24
	UINT32                                     : 1;   //    27
	UINT32 apl_mux                             : 3;   // 30:28
} L9A0_P0L_BBD_CTRL_00_T;

typedef struct { // 0x0674
	UINT32 x0                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y0                                  : 12;  // 27:16
} L9A0_P0L_BBD_CTRL_01_T;

typedef struct { // 0x0678
	UINT32 x1                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y1                                  : 12;  // 27:16
} L9A0_P0L_BBD_CTRL_02_T;

typedef struct { // 0x067c
	UINT32 x0                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y0                                  : 12;  // 27:16
} L9A0_P0L_BBD_STAT_00_T;

typedef struct { // 0x0680
	UINT32 x1                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y1                                  : 12;  // 27:16
} L9A0_P0L_BBD_STAT_01_T;

typedef struct { // 0x0684
	UINT32 p0l_apl_stat_00_f                   : 32;   // 31: 0
} L9A0_P0L_APL_STAT_00_T;

typedef struct { // 0x2400
	UINT32 load_time                           : 1;   //     0
	UINT32 load_enable                         : 1;   //     1
	UINT32 load_type                           : 1;   //     2
} L9A0_P0R_PE0_LOAD_T;

typedef struct { // 0x2404
	UINT32 intr_enable                         : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 intr_src                            : 3;   //  6: 4
	UINT32                                     : 9;   // 15: 7
	UINT32 intr_line_pos                       : 11;  // 26:16
} L9A0_P0R_PE0_INTR_T;

typedef struct { // 0x2408
	UINT32 tnr_frame_id                        : 4;   //  3: 0
	UINT32 ipc_frame_id                        : 4;   //  7: 4
	UINT32 tnrw_y_frame_id                     : 4;   // 11: 8
	UINT32 tnrw_c_frame_id                     : 4;   // 15:12
	UINT32 dnr_frame_id                        : 8;   // 23:16
	UINT32 pic_init_frame_id                   : 4;   // 27:24
} L9A0_P0R_PE0_STATUS0_T;

typedef struct { // 0x240c
	UINT32 line_cnt                            : 11;  // 10: 0
} L9A0_P0R_PE0_STATUS1_T;

typedef struct { // 0x2410
	UINT32 tnr_c_en                            : 1;   //     0
	UINT32 tnr_y_en                            : 1;   //     1
	UINT32 ipc_c_en                            : 1;   //     2
	UINT32 ipc_y_en                            : 1;   //     3
	UINT32 tnr_c_444_as_420                    : 1;   //     4
	UINT32 tnr_y2_en                           : 1;   //     5
	UINT32 force_420                           : 1;   //     6
	UINT32                                     : 1;   //     7
	UINT32 mif_last_mode                       : 3;   // 10: 8
	UINT32                                     : 5;   // 15:11
	UINT32 detour_enable                       : 1;   //    16
} L9A0_P0R_PE0_OPMODE_T;

typedef struct { // 0x2414
	UINT32 hsize                               : 11;  // 10: 0
	UINT32                                     : 2;   // 12:11
	UINT32 cs_type                             : 3;   // 15:13
	UINT32 vsize                               : 12;  // 27:16
	UINT32                                     : 3;   // 30:28
	UINT32 scan_type                           : 1;   //    31
} L9A0_P0R_PE0_SRC_SIZE_T;

typedef struct { // 0x2418
	UINT32 field_id                            : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 field_mode                          : 2;   //  5: 4
} L9A0_P0R_PE0_FIELD_T;

typedef struct { // 0x241c
	UINT32                                     : 9;   //  8: 0
	UINT32 stride                              : 2;   // 10: 9
	UINT32                                     : 5;   // 15:11
	UINT32 vsize                               : 8;   // 23:16
	UINT32                                     : 6;   // 29:24
	UINT32 endian                              : 1;   //    30
	UINT32 update_by_ddr                       : 1;   //    31
} L9A0_P0R_PE0_PARAM_BY_DDR_T;

typedef struct { // 0x2420
	UINT32 x0                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y0                                  : 11;  // 26:16
} L9A0_P0R_WIN_CTRL_0_T;

typedef struct { // 0x2424
	UINT32 x1                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y1                                  : 11;  // 26:16
} L9A0_P0R_WIN_CTRL_1_T;

typedef struct { // 0x2428
	UINT32 x0                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y0                                  : 11;  // 26:16
	UINT32                                     : 1;   //    27
	UINT32 ac_bnr_feature_cal_mode             : 2;   // 29:28
} L9A0_P0R_WIN_CTRL_2_T;

typedef struct { // 0x242c
	UINT32 x1                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y1                                  : 11;  // 26:16
} L9A0_P0R_WIN_CTRL_3_T;

typedef struct { // 0x2440
	UINT32 tnr_enable                          : 1;   //     0
	UINT32 wa2_enable                          : 1;   //     1
	UINT32 nt_lvl_hsub                         : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 calc_motion_3f_en                   : 1;   //     4
	UINT32 hist_motion_3f_en                   : 1;   //     5
	UINT32                                     : 1;   //     6
	UINT32 frame_skip_enable_for_3d            : 1;   //     7
	UINT32 calc_motion_sample_mode             : 2;   //  9: 8
	UINT32 hist_motion_sample_mode             : 2;   // 11:10
	UINT32                                     : 2;   // 13:12
	UINT32 calc_motion_flt_enable              : 1;   //    14
	UINT32 calc_motion_flt_type                : 1;   //    15
	UINT32 calc_motion_max_yc                  : 1;   //    16
	UINT32 hist_motion_max_yc                  : 1;   //    17
	UINT32 average_win_for_color_region        : 2;   // 19:18
	UINT32 average_win_for_nr_calc             : 2;   // 21:20
	UINT32                                     : 1;   //    22
	UINT32 variance_sample_mode                : 1;   //    23
} L9A0_P0R_TNR_CTRL_00_T;

typedef struct { // 0x2444
	UINT32 y_th_lo                             : 10;  //  9: 0
	UINT32                                     : 2;   // 11:10
	UINT32 y_th_hi                             : 10;  // 21:12
	UINT32 svar_mux_ctrl                       : 2;   // 23:22
	UINT32 svar_hist_n_pct                     : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_01_T;

typedef struct { // 0x2448
	UINT32 ns_g_fit_th0                        : 8;   //  7: 0
	UINT32 ns_g_fit_th1                        : 8;   // 15: 8
	UINT32 ns_x_pn_minus                       : 4;   // 19:16
	UINT32                                     : 4;   // 23:20
	UINT32 ns_iir_alpha                        : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_02_T;

typedef struct { // 0x244c
	UINT32 wa_min                              : 8;   //  7: 0
	UINT32 wa_max                              : 8;   // 15: 8
	UINT32 wa_k                                : 7;   // 22:16
	UINT32                                     : 1;   //    23
	UINT32 tnr_hist_wa_th                      : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_03_T;

typedef struct { // 0x2450
	UINT32 nl_peak0                            : 8;   //  7: 0
	UINT32 nl_peak1                            : 8;   // 15: 8
	UINT32 nl_peak2                            : 8;   // 23:16
	UINT32 nl_peak3                            : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_04_T;

typedef struct { // 0x2454
	UINT32 nt_min                              : 8;   //  7: 0
	UINT32 nt_max                              : 8;   // 15: 8
	UINT32 gm_low                              : 8;   // 23:16
	UINT32 gm_high                             : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_05_T;

typedef struct { // 0x2458
	UINT32 nt_at_as_th                         : 8;   //  7: 0
	UINT32 nt_iir_alpha                        : 8;   // 15: 8
	UINT32 adj_alpha_k0                        : 8;   // 23:16
	UINT32 adj_alpha_k1                        : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_06_T;

typedef struct { // 0x245c
	UINT32 alpha_lut_ind0                      : 8;   //  7: 0
	UINT32 alpha_lut_ind1                      : 8;   // 15: 8
	UINT32 alpha_lut_ind2                      : 8;   // 23:16
	UINT32 alpha_lut_ind3                      : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_07_T;

typedef struct { // 0x2460
	UINT32 alpha_lut_ind4                      : 8;   //  7: 0
	UINT32 alpha_lut_ind5                      : 8;   // 15: 8
	UINT32 alpha_lut_ind6                      : 8;   // 23:16
	UINT32 adj_alpha_nt_lvl_th                 : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_08_T;

typedef struct { // 0x2464
	UINT32 scene_change_enable                 : 1;   //     0
	UINT32 scene_change_max_flt_en             : 1;   //     1
	UINT32 scene_change_measure_sel            : 1;   //     2
	UINT32 scene_change_prev_hist_calc_en      : 1;   //     3
	UINT32 scene_change_manual_set             : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 scene_change_max_flt_tap            : 2;   //  9: 8
	UINT32                                     : 2;   // 11:10
	UINT32 scene_change_scale                  : 3;   // 14:12
	UINT32                                     : 1;   //    15
	UINT32 scene_change_th                     : 8;   // 23:16
} L9A0_P0R_TNR_CTRL_09_T;

typedef struct { // 0x2468
	UINT32 dbg_show_tnr_param                  : 5;   //  4: 0
	UINT32                                     : 3;   //  7: 5
	UINT32 dbg_force_wa                        : 1;   //     8
	UINT32 dbg_force_calc_motion               : 1;   //     9
	UINT32 dbg_force_lut_alpha                 : 1;   //    10
	UINT32 dbg_force_adj_alpha                 : 1;   //    11
	UINT32 dbg_force_final_alpha               : 1;   //    12
	UINT32                                     : 1;   //    13
	UINT32 chroma_polarity_check               : 1;   //    14
	UINT32 ignore_active_window                : 1;   //    15
	UINT32 dbg_tnrw_port_ctrl                  : 2;   // 17:16
} L9A0_P0R_TNR_CTRL_10_T;

typedef struct { // 0x246c
	UINT32 dbg_calc_motion                     : 8;   //  7: 0
	UINT32 dbg_alpha                           : 8;   // 15: 8
} L9A0_P0R_TNR_CTRL_11_T;

typedef struct { // 0x2470
	UINT32 force_ns_lvl                        : 1;   //     0
	UINT32                                     : 7;   //  7: 1
	UINT32 force_ns_lvl_val                    : 8;   // 15: 8
	UINT32 adjust_ns_lvl                       : 1;   //    16
	UINT32                                     : 7;   // 23:17
	UINT32 adjust_ns_lvl_val                   : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_12_T;

typedef struct { // 0x2474
	UINT32 force_nt_lvl                        : 1;   //     0
	UINT32                                     : 7;   //  7: 1
	UINT32 force_nt_lvl_val                    : 8;   // 15: 8
	UINT32 adjust_nt_lvl                       : 1;   //    16
	UINT32                                     : 7;   // 23:17
	UINT32 adjust_nt_lvl_val                   : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_13_T;

typedef struct { // 0x2478
	UINT32 x0                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y0                                  : 11;  // 26:16
	UINT32                                     : 4;   // 30:27
	UINT32 noise_measure_win_en                : 1;   //    31
} L9A0_P0R_TNR_CTRL_14_T;

typedef struct { // 0x247c
	UINT32 x1                                  : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 y1                                  : 11;  // 26:16
} L9A0_P0R_TNR_CTRL_15_T;

typedef struct { // 0x2480
	UINT32 show_dbg_bar_ctrl0                  : 8;   //  7: 0
	UINT32 show_dbg_bar_ctrl1                  : 8;   // 15: 8
	UINT32 show_dbg_bar_ctrl2                  : 8;   // 23:16
	UINT32 show_dbg_bar_ctrl3                  : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_16_T;

typedef struct { // 0x2484
	UINT32 show_dbg_bar_ctrl4                  : 8;   //  7: 0
} L9A0_P0R_TNR_CTRL_17_T;

typedef struct { // 0x2488
	UINT32 crgn_gain_enable                    : 1;   //     0
	UINT32 luma_gain_enable                    : 1;   //     1
	UINT32 saturation_gain_enable              : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 input_for_luma                      : 2;   //  5: 4
	UINT32                                     : 2;   //  7: 6
	UINT32 input_for_crgn_satr                 : 1;   //     8
	UINT32                                     : 7;   // 15: 9
	UINT32 y_gain                              : 8;   // 23:16
	UINT32 c_gain                              : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_18_T;

typedef struct { // 0x248c
	UINT32 luma_gain_p0_x                      : 8;   //  7: 0
	UINT32 luma_gain_p1_x                      : 8;   // 15: 8
	UINT32 luma_gain_p2_x                      : 8;   // 23:16
	UINT32 luma_gain_p3_x                      : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_19_T;

typedef struct { // 0x2490
	UINT32 luma_gain_p4_x                      : 8;   //  7: 0
	UINT32 luma_gain_p5_x                      : 8;   // 15: 8
	UINT32 luma_gain_p6_x                      : 8;   // 23:16
	UINT32 luma_gain_p7_x                      : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_20_T;

typedef struct { // 0x2494
	UINT32 luma_gain_p0_y                      : 8;   //  7: 0
	UINT32 luma_gain_p1_y                      : 8;   // 15: 8
	UINT32 luma_gain_p2_y                      : 8;   // 23:16
	UINT32 luma_gain_p3_y                      : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_21_T;

typedef struct { // 0x2498
	UINT32 luma_gain_p4_y                      : 8;   //  7: 0
	UINT32 luma_gain_p5_y                      : 8;   // 15: 8
	UINT32 luma_gain_p6_y                      : 8;   // 23:16
	UINT32 luma_gain_p7_y                      : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_22_T;

typedef struct { // 0x249c
	UINT32 saturation_gain_p0_x                : 8;   //  7: 0
	UINT32 saturation_gain_p1_x                : 8;   // 15: 8
	UINT32 saturation_gain_p2_x                : 8;   // 23:16
	UINT32 saturation_gain_p3_x                : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_23_T;

typedef struct { // 0x24a0
	UINT32 saturation_gain_p4_x                : 8;   //  7: 0
	UINT32 saturation_gain_p5_x                : 8;   // 15: 8
	UINT32 saturation_gain_p6_x                : 8;   // 23:16
	UINT32 saturation_gain_p7_x                : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_24_T;

typedef struct { // 0x24a4
	UINT32 saturation_gain_p0_y                : 8;   //  7: 0
	UINT32 saturation_gain_p1_y                : 8;   // 15: 8
	UINT32 saturation_gain_p2_y                : 8;   // 23:16
	UINT32 saturation_gain_p3_y                : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_25_T;

typedef struct { // 0x24a8
	UINT32 saturation_gain_p4_y                : 8;   //  7: 0
	UINT32 saturation_gain_p5_y                : 8;   // 15: 8
	UINT32 saturation_gain_p6_y                : 8;   // 23:16
	UINT32 saturation_gain_p7_y                : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_26_T;

typedef struct { // 0x24ac
	UINT32 crgn_gain_in_rgn0                   : 8;   //  7: 0
	UINT32 crgn_gain_out_rgn0                  : 8;   // 15: 8
	UINT32 crgn_gain_in_rgn1                   : 8;   // 23:16
	UINT32 crgn_gain_out_rgn1                  : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_27_T;

typedef struct { // 0x24b0
	UINT32 crgn_gain_in_rgn2                   : 8;   //  7: 0
	UINT32 crgn_gain_out_rgn2                  : 8;   // 15: 8
	UINT32 crgn_gain_in_rgn3                   : 8;   // 23:16
	UINT32 crgn_gain_out_rgn3                  : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_28_T;

typedef struct { // 0x24b4
	UINT32 wa2_min_slope	                   : 8;   //  7: 0
	UINT32 wa2_max_slope	                   : 8;	  // 15: 8
	UINT32 wa2_cc			                   : 8;	  // 23:16	
} L9A0_P0R_TNR_CTRL_29_T;

typedef struct { // 0x24b8
	UINT32 wa2_min			                   : 8;   //  7: 0
	UINT32 wa2_max	    		               : 8;	  // 15: 8
} L9A0_P0R_TNR_CTRL_30_T;

typedef struct { // 0x24bc
	UINT32 spatial_pre_flt_en_c                : 1;   //     0
	UINT32 spatial_pre_flt_en_y                : 1;   //     1
	UINT32            						   : 14;  // 15: 2
	UINT32 spatial_pre_flt_th_c                : 8;   // 23:16
	UINT32 spatial_pre_flt_th_y                : 8;   // 31:24
} L9A0_P0R_TNR_CTRL_31_T;

typedef struct { // 0x24c0
	UINT32 x_avg_t                             : 8;   //  7: 0
	UINT32 x_peak_t2                           : 8;   // 15: 8
	UINT32 nt_lvl                              : 8;   // 23:16
	UINT32 scene_change                        : 8;   // 31:24
} L9A0_P0R_TNR_STATUS_00_T;

typedef struct { // 0x24c4
	UINT32 x_avg_s                             : 8;   //  7: 0
	UINT32 x_peak_s                            : 8;   // 15: 8
	UINT32 ns_lvl                              : 8;   // 23:16
} L9A0_P0R_TNR_STATUS_01_T;

typedef struct { // 0x24c8
	UINT32 g_fit                               : 8;   //  7: 0
	UINT32 x_pn_s                              : 8;   // 15: 8
	UINT32 gm                                  : 8;   // 23:16
	UINT32 lp                                  : 8;   // 31:24
} L9A0_P0R_TNR_STATUS_02_T;

typedef struct { // 0x24cc
	UINT32 sum_of_temp_pel_diff                : 29;  // 28: 0
} L9A0_P0R_TNR_STATUS_03_T;

typedef struct { // 0x24d0
	UINT32 main_lut_indir_addr                 : 4;   //  3: 0
	UINT32                                     : 8;   // 11: 4
	UINT32 main_lut_ai_enable                  : 1;   //    12
} L9A0_P0R_TNR_MAIN_LUT_00_T;

typedef struct { // 0x24d4
	UINT32 main_lut_indir_data0                : 32;  // 31: 0
} L9A0_P0R_TNR_MAIN_LUT_01_T;

typedef struct { // 0x24d8
	UINT32 main_lut_indir_data1                : 32;  // 31: 0
} L9A0_P0R_TNR_MAIN_LUT_02_T;

typedef struct { // 0x24dc
	UINT32 ti_h_enable                         : 1;   //     0
	UINT32 ti_h_filter                         : 1;   //     1
	UINT32                                     : 6;   //  7: 2
	UINT32 ti_v_enable                         : 1;   //     8
	UINT32 ti_v_filter                         : 1;   //     9
	UINT32                                     : 6;   // 15:10
	UINT32 ti_h_gain                           : 8;   // 23:16
	UINT32 ti_v_gain                           : 8;   // 31:24
} L9A0_P0R_TI_CTRL_T;

typedef struct { // 0x24e0
	UINT32 nt_lvl_lut_indir_addr               : 3;   //  2: 0
	UINT32                                     : 9;   // 11: 3
	UINT32 nt_lvl_lut_ai_enable                : 1;   //    12
} L9A0_P0R_TNR_NT_LVL_LUT_00_T;

typedef struct { // 0x24e4
	UINT32 nt_lvl_lut_indir_data0              : 32;  // 31: 0
} L9A0_P0R_TNR_NT_LVL_LUT_01_T;

typedef struct { // 0x24e8
	UINT32 nt_lvl_lut_indir_data1              : 32;  // 31: 0
} L9A0_P0R_TNR_NT_LVL_LUT_02_T;

typedef struct { // 0x24ec
	UINT32 nt_lvl_lut_indir_data2              : 32;  // 31: 0
} L9A0_P0R_TNR_NT_LVL_LUT_03_T;

typedef struct { // 0x24f0
	UINT32 crgn_ctrl_indir_addr                : 8;   //  7: 0
	UINT32 crgn_ctrl_crgn_sel                  : 3;   // 10: 8
	UINT32                                     : 1;   //    11
	UINT32 crgn_ctrl_ai_enable                 : 1;   //    12
	UINT32 crgn_ctrl_hsv_csc_scaler_en         : 1;   //    13
	UINT32 crgn_ctrl_csc_sel                   : 1;   //    14
	UINT32 crgn_ctrl_access_off                : 1;   //    15
} L9A0_P0R_TNR_CRG_CTRL_00_T;

typedef struct { // 0x24f4
	UINT32 crgn_ctrl_indir_data                : 32;  // 31: 0
} L9A0_P0R_TNR_CRG_CTRL_01_T;

typedef struct { // 0x2500
	UINT32 luma_mode                           : 2;   //  1: 0
	UINT32                                     : 1;   //     2
	UINT32 luma_edi                            : 1;   //     3
	UINT32 chroma_mode                         : 2;   //  5: 4
	UINT32                                     : 1;   //     6
	UINT32 chroma_edi                          : 1;   //     7
	UINT32 chroma_adaptive_va_enable           : 1;   //     8
	UINT32 luma_adaptive_va_enable             : 1;   //     9
	UINT32 st_filter_mode                      : 2;   // 11:10
	UINT32                                     : 12;  // 23:12
	UINT32 ipc__fake__v_repeat_va_ta           : 2;   // 25:24
	UINT32                                     : 3;   // 28:26
	UINT32 film_mode_apply_c                   : 1;   //    29
	UINT32 film_mode_apply_y                   : 1;   //    30
	UINT32 film_mode_enable                    : 1;   //    31
} L9A0_P0R_IPC_CTRL_00_T;

typedef struct { // 0x2504
	UINT32 spatial_alpha_th0                   : 8;   //  7: 0
	UINT32 spatial_alpha_th1                   : 8;   // 15: 8
	UINT32 spatial_filter_tap_ctrl             : 8;   // 23:16
	UINT32                                     : 7;   // 30:24
	UINT32 texture_alpha_use_global_max        : 1;   //    31
} L9A0_P0R_IPC_CTRL_01_T;

typedef struct { // 0x2508
	UINT32 fuzzy_ctrl_point_x0                 : 8;   //  7: 0
	UINT32 fuzzy_ctrl_point_x4                 : 8;   // 15: 8
	UINT32 fuzzy_ctrl_point_x1                 : 8;   // 23:16
	UINT32 fuzzy_ctrl_point_y1                 : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_02_T;

typedef struct { // 0x250c
	UINT32 fuzzy_ctrl_point_x2                 : 8;   //  7: 0
	UINT32 fuzzy_ctrl_point_y2                 : 8;   // 15: 8
	UINT32 fuzzy_ctrl_point_x3                 : 8;   // 23:16
	UINT32 fuzzy_ctrl_point_y3                 : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_03_T;

typedef struct { // 0x2510
	UINT32 hmc_filter_range_top                : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 hmc_filter_range_bot                : 12;  // 27:16
} L9A0_P0R_IPC_CTRL_04_T;

typedef struct { // 0x2514
	UINT32 hmc_search_range                    : 4;   //  3: 0
	UINT32                                     : 4;   //  7: 4
	UINT32 hmc_h_motion_ratio                  : 6;   // 13: 8
	UINT32                                     : 2;   // 15:14
	UINT32 hmc_lock_filter_half_size           : 3;   // 18:16
	UINT32                                     : 5;   // 23:19
	UINT32 hmc_lock_filter_expand              : 1;   //    24
	UINT32 protect_filtering_enable            : 1;   //    25
	UINT32 protect_th                          : 6;   // 31:26
} L9A0_P0R_IPC_CTRL_05_T;

typedef struct { // 0x2518
	UINT32 hmc_point_max                       : 8;   //  7: 0
	UINT32 hmc_point_penalty                   : 8;   // 15: 8
	UINT32 hmc_point_valid_th                  : 8;   // 23:16
} L9A0_P0R_IPC_CTRL_06_T;

typedef struct { // 0x251c
	UINT32 hmc_enable                          : 1;   //     0
	UINT32 hmc_protection_errt__b07_01         : 7;   //  7: 1
	UINT32 hmc_protection_blend_alpha          : 8;   // 15: 8
	UINT32 hmc_protection_errt__b23_16         : 8;   // 23:16
	UINT32 hmc_protection_pndiff               : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_07_T;

typedef struct { // 0x2520
	UINT32 st_fuzzy_margin_0                   : 8;   //  7: 0
	UINT32 st_fuzzy_margin_1                   : 8;   // 15: 8
	UINT32                                     : 8;   // 23:16
	UINT32 tnr_debug_mode                      : 1;   //    24
	UINT32 tnr_debug_black_mask                : 1;   //    25
} L9A0_P0R_IPC_CTRL_08_T;

typedef struct { // 0x2524
	UINT32 fmd_vedge_th                        : 7;   //  6: 0
	UINT32 fmd_vedge_en                        : 1;   //     7
	UINT32 fmd_a_th                            : 6;   // 13: 8
	UINT32 use_3field_err_t                    : 1;   //    14
	UINT32 two_field_delay_mode                : 1;   //    15
	UINT32 fmd_margin_top                      : 8;   // 23:16
	UINT32 fmd_margin_bottom                   : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_09_T;

typedef struct { // 0x2528
	UINT32 film_inter_with                     : 2;   //  1: 0
	UINT32 hw_film_enable                      : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 tearing_detect_strength             : 1;   //     4
	UINT32 cross_check                         : 1;   //     5
	UINT32                                     : 1;   //     6
	UINT32 usediffpelcount                     : 1;   //     7
	UINT32 pn_diff_th                          : 8;   // 15: 8
	UINT32                                     : 12;  // 27:16
	UINT32 scalemeasureforhd                   : 2;   // 29:28
	UINT32 loading_time_ctrl                   : 1;   //    30
	UINT32 fmd_sw_bad_edit_en                  : 1;   //    31
} L9A0_P0R_IPC_CTRL_10_T;

typedef struct { // 0x252c
	UINT32 fmd_caption_range_top               : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 fmd_caption_range_bot               : 12;  // 27:16
	UINT32                                     : 2;   // 29:28
	UINT32 caption_flow_detected               : 1;   //    30
	UINT32 hmc_when_cap_not_detected           : 1;   //    31
} L9A0_P0R_IPC_CTRL_11_T;

typedef struct { // 0x2530
	UINT32 fmd_32_enable                       : 1;   //     0
	UINT32 fmd_22_enable                       : 1;   //     1
	UINT32 fmd_badediten                       : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 fmd_hw_bad_edit_mul_th              : 3;   //  6: 4
	UINT32                                     : 1;   //     7
	UINT32 fmd_hw_bad_edit_th_min              : 8;   // 15: 8
	UINT32 pcn_diff_th                         : 7;   // 22:16
	UINT32 fmd_arbitrary_6_4only               : 1;   //    23
	UINT32 fmd_stillconditition1               : 1;   //    24
	UINT32 fmd_stillconditition2               : 1;   //    25
	UINT32 fmd_arbitrary_still                 : 1;   //    26
	UINT32 fmd_arbitrary_3_2only               : 1;   //    27
	UINT32 fmd_still_cntth                     : 3;   // 30:28
	UINT32 fmd_still_cntth_en                  : 1;   //    31
} L9A0_P0R_IPC_CTRL_12_T;

typedef struct { // 0x2534
	UINT32 fmd32_stillth_pn                    : 8;   //  7: 0
	UINT32 fmd32_stillthpcn                    : 8;   // 15: 8
	UINT32 fmd32_pn_maxvalue_minth0            : 8;   // 23:16
	UINT32 fmd32_pn_maxvalue_minth1            : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_13_T;

typedef struct { // 0x2538
	UINT32 fmd32_min_field_num                 : 4;   //  3: 0
	UINT32                                     : 4;   //  7: 4
	UINT32 fmd32_pn_minvalue_maxth             : 8;   // 15: 8
	UINT32 fmd32_pn_maxminratio0               : 4;   // 19:16
	UINT32 fmd32_pn_maxminratio1               : 4;   // 23:20
	UINT32 fmd_32_pcn_small_weight             : 3;   // 26:24
} L9A0_P0R_IPC_CTRL_14_T;

typedef struct { // 0x253c
	UINT32 fmd22_stillth_pn                    : 8;   //  7: 0
	UINT32 fmd22_stillth_pcn                   : 8;   // 15: 8
	UINT32 bad_edit_sm_min_th                  : 12;  // 27:16
	// fmd_22_min_val_max_th1 is removed from L9A0
	//UINT32 fmd_22_min_val_max_th1              : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_15_T;

typedef struct { // 0x2540
	UINT32 fmd22_minfieldnum0                  : 4;   //  3: 0
	UINT32 fmd22_minfieldnum1                  : 4;   //  7: 4
	UINT32 fmd22_minvaluemaxth1                : 8;   // 15: 8
	UINT32 fmd22_maxvalueminth1                : 8;   // 23:16
	UINT32 fmd22_maxminratio0                  : 4;   // 27:24
	UINT32 fmd22_maxminratio1                  : 4;   // 31:28
} L9A0_P0R_IPC_CTRL_16_T;

typedef struct { // 0x2544
	UINT32 dbg_show_mode                       : 5;   //  4: 0
	UINT32                                     : 6;   // 10: 5
	UINT32 dbg_show_black_mask                 : 1;   //    11
	UINT32 dbg_pprv_to_curr                    : 1;   //    12
	UINT32 dbg_prv3_to_prev                    : 1;   //    13
	UINT32 dbg_curr_to_pprv                    : 1;   //    14
	UINT32                                     : 1;   //    15
	UINT32 st_flt_ctrl_x0                      : 8;   // 23:16
	UINT32 st_flt_ctrl_x1                      : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_17_T;

typedef struct { // 0x2548
	UINT32 v_filt_ctrl_v_filt_range_top        : 11;  // 10: 0
	UINT32                                     : 5;   // 15:11
	UINT32 v_filt_ctrl_v_filt_range_bot        : 11;  // 26:16
	UINT32                                     : 4;   // 30:27
	UINT32 v_filt_ctrl_hmc_line_info_en        : 1;   //    31
} L9A0_P0R_IPC_CTRL_18_T;

typedef struct { // 0x254c
	UINT32 repeat_det_line_cnt_th              : 8;   //  7: 0
	UINT32 repeat_det_diff_pel_cnt_th          : 8;   // 15: 8
	UINT32 repeat_det_noise_th                 : 4;   // 19:16
} L9A0_P0R_IPC_CTRL_19_T;

typedef struct { // 0x2550
	UINT32 pc_cnt                              : 16;  // 15: 0
	UINT32 nc_cnt                              : 16;  // 31:16
} L9A0_P0R_IPC_STATUS_00_T;

typedef struct { // 0x2554
	UINT32 pn_cnt                              : 16;  // 15: 0
	UINT32 same_cnt                            : 16;  // 31:16
} L9A0_P0R_IPC_STATUS_01_T;

typedef struct { // 0x2558
	UINT32 fmd32_combwith                      : 2;   //  1: 0
	UINT32                                     : 1;   //     2
	UINT32 fmd32_detected                      : 1;   //     3
	UINT32 fmd32_lockingcnt                    : 8;   // 11: 4
	UINT32 fmd22_combwith                      : 2;   // 13:12
	UINT32                                     : 1;   //    14
	UINT32 fmd22_detected                      : 1;   //    15
	UINT32 fmd22_lockingcnt                    : 8;   // 23:16
	UINT32 fmd_comb_predict                    : 2;   // 25:24
	UINT32 bad_edit_detected_                  : 1;   //    26
	UINT32 fmd22_still_detected                : 1;   //    27
	UINT32 fmd32_still_detected                : 1;   //    28
	UINT32 repeat_detected                     : 1;   //    29
} L9A0_P0R_IPC_STATUS_02_T;

typedef struct { // 0x255c
	UINT32                                     : 16;  // 15: 0
	UINT32 fmd_badeditth_hw                    : 16;  // 31:16
} L9A0_P0R_IPC_STATUS_03_T;

typedef struct { // 0x2560
	UINT32 cc_filter_enable                    : 1;   //     0
	UINT32 cl_filter_enable                    : 1;   //     1
	UINT32 clc_detection_enable                : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 cc_cross_gain0                      : 4;   //  7: 4
	UINT32 cc_cross_gain1                      : 4;   // 11: 8
	UINT32 cl_ab_ratio                         : 4;   // 15:12
	UINT32 cl_y_hdistance                      : 2;   // 17:16
	UINT32 cl_c_hdistance                      : 2;   // 19:18
	UINT32 cl_var_th                           : 5;   // 24:20
	UINT32                                     : 1;   //    25
	UINT32 cc_margin128                        : 2;   // 27:26
	UINT32 cl_motion_a_filter                  : 1;   //    28
	UINT32 cl_motion_b_filter                  : 1;   //    29
	UINT32 cc_motion_a_filter                  : 1;   //    30
	UINT32 cc_motion_b_filter                  : 1;   //    31
} L9A0_P0R_CLC_CTRL_00_T;

typedef struct { // 0x2564
	UINT32 cl_motion_a_th                      : 8;   //  7: 0
	UINT32 cl_motion_b_th                      : 8;   // 15: 8
	UINT32 cc_motion_a_th                      : 8;   // 23:16
	UINT32 cc_motion_b_th                      : 8;   // 31:24
} L9A0_P0R_CLC_CTRL_01_T;

typedef struct { // 0x2568
	UINT32 cl_y_bound_th                       : 7;   //  6: 0
	UINT32                                     : 1;   //     7
	UINT32 cl_c_bound_th                       : 7;   // 14: 8
	UINT32 cl_c_bound_type                     : 1;   //    15
	UINT32 cl_y_bound_width_chroma             : 2;   // 17:16
	UINT32 cl_y_bound_ignore_cc                : 1;   //    18
	UINT32 cl_y_bound_ignore_p2                : 1;   //    19
	UINT32 cl_y_bound_ignore_p4                : 1;   //    20
} L9A0_P0R_CLC_CTRL_02_T;

typedef struct { // 0x256c
	UINT32 cl_sat_min                          : 8;   //  7: 0
	UINT32 cc_sat_min                          : 8;   // 15: 8
	UINT32 cc_sat_max                          : 8;   // 23:16
} L9A0_P0R_CLC_CTRL_03_T;

typedef struct { // 0x2570
	UINT32 p0r_clc_ctrl_04_f                   : 32;   // 31: 0
} L9A0_P0R_CLC_CTRL_04_T;

typedef struct { // 0x2574
	UINT32 clc_c_filter_when_cl_detected       : 1;   //     0
	UINT32                                     : 1;   //     1
	UINT32 clc_y_filter_when_cc_detected       : 2;   //  3: 2
	UINT32 clc_cc_line_mem_ctrl                : 2;   //  5: 4
	UINT32                                     : 2;   //  7: 6
	UINT32 clc_c_gain                          : 8;   // 15: 8
	UINT32 clc_dbg_show_mask                   : 12;  // 27:16
} L9A0_P0R_CLC_CTRL_05_T;

typedef struct { // 0x2578
	UINT32 cc_c_filter_gain                    : 8;   //  7: 0
	UINT32 cc_y_filter_when_cc_detected        : 1;   //     8
} L9A0_P0R_CLC_CTRL_06_T;

typedef struct { // 0x257c
	UINT32 cc_detection_count                  : 16;  // 15: 0
	UINT32 cl_detection_count                  : 16;  // 31:16
} L9A0_P0R_CLC_STAT_00_T;

typedef struct { // 0x2580
	UINT32 vfilterenable                       : 1;   //     0
	UINT32 vfilterlocalenable                  : 1;   //     1
	UINT32 vfilter_strength                    : 1;   //     2
	UINT32                                     : 5;   //  7: 3
	UINT32 vfilter_a_th                        : 8;   // 15: 8
	UINT32 vfilter_in_field_var                : 8;   // 23:16
	UINT32 vfilter_use_mc_mask                 : 1;   //    24
	UINT32 vfilter_expand                      : 1;   //    25
	UINT32 vfilter_center                      : 1;   //    26
	UINT32 vfilter_ul4                         : 1;   //    27
	UINT32 dbgshow_level                       : 2;   // 29:28
	UINT32                                     : 1;   //    30
	UINT32 dbgshow_enable                      : 1;   //    31
} L9A0_P0R_VFLT_CTRL_T;

typedef struct { // 0x2584
	UINT32 snr_enable                          : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 display_mode                        : 3;   //  6: 4
	UINT32                                     : 1;   //     7
	UINT32 normalization                       : 4;   // 11: 8
	UINT32 scaling_factor                      : 3;   // 14:12
	UINT32                                     : 1;   //    15
	UINT32 coring_factor                       : 8;   // 23:16
} L9A0_P0R_SNR_CTRL_00_T;

typedef struct { // 0x2588
	UINT32 mnr_enable                          : 1;   //     0
	UINT32 edge_gain_mapping_enable            : 1;   //     1
	UINT32 sel_sd_hd                           : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 debug_mode                          : 3;   //  6: 4
} L9A0_P0R_MNR_CTRL_00_T;

typedef struct { // 0x258c
	UINT32                                     : 16;  // 15: 0
	UINT32 hcoef_00                            : 4;   // 19:16
	UINT32 hcoef_01                            : 4;   // 23:20
	UINT32 hcoef_02                            : 4;   // 27:24
	UINT32 hcoef_03                            : 4;   // 31:28
} L9A0_P0R_MNR_CTRL_01_T;

typedef struct { // 0x2590
	UINT32 hcoef_04                            : 4;   //  3: 0
	UINT32 hcoef_05                            : 4;   //  7: 4
	UINT32 hcoef_06                            : 4;   // 11: 8
	UINT32 hcoef_07                            : 4;   // 15:12
	UINT32 hcoef_08                            : 4;   // 19:16
	UINT32 hcoef_09                            : 4;   // 23:20
	UINT32 hcoef_10                            : 4;   // 27:24
	UINT32 hcoef_11                            : 4;   // 31:28
} L9A0_P0R_MNR_CTRL_02_T;

typedef struct { // 0x2594
	UINT32 hcoef_12                            : 4;   //  3: 0
	UINT32 hcoef_13                            : 4;   //  7: 4
	UINT32 hcoef_14                            : 4;   // 11: 8
	UINT32 hcoef_15                            : 4;   // 15:12
	UINT32 hcoef_16                            : 4;   // 19:16
	UINT32                                     : 4;   // 23:20
	UINT32 x1_position                         : 8;   // 31:24
} L9A0_P0R_MNR_CTRL_03_T;

typedef struct { // 0x2598
	UINT32 x2_position                         : 8;   //  7: 0
	UINT32 x3_position                         : 8;   // 15: 8
	UINT32 x4_position                         : 8;   // 23:16
	UINT32 y1_position                         : 8;   // 31:24
} L9A0_P0R_MNR_CTRL_04_T;

typedef struct { // 0x259c
	UINT32 y2_position                         : 8;   //  7: 0
	UINT32 y3_position                         : 8;   // 15: 8
	UINT32 y4_position                         : 8;   // 23:16
	UINT32 filter_threshold                    : 8;   // 31:24
} L9A0_P0R_MNR_CTRL_05_T;

typedef struct { // 0x25a0
	UINT32 vcoef0                              : 4;   //  3: 0
	UINT32 vcoef1                              : 4;   //  7: 4
	UINT32 vcoef2                              : 4;   // 11: 8
	UINT32 vcoef3                              : 4;   // 15:12
	UINT32 vcoef4                              : 4;   // 19:16
	UINT32 vcoef5                              : 4;   // 23:20
	UINT32 vcoef6                              : 4;   // 27:24
} L9A0_P0R_MNR_CTRL_06_T;

typedef struct { // 0x25a8
	UINT32 cr_vfilter_global_en                : 1;   //     0
	UINT32 cr_vfilter_force_en                 : 1;   //     1
	UINT32 cr_global_frame_num_th              : 4;   //  5: 2
	UINT32                                     : 2;   //  7: 6
	UINT32 cr_vfilter_global_th                : 12;  // 19: 8
	UINT32 tearing_count                       : 12;  // 31:20
} L9A0_P0R_VFILTER_01_T;

typedef struct { // 0x25ac
	UINT32 dc_bnr_enable                       : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 sd_hd_sel                           : 1;   //     4
	UINT32 output_mux                          : 3;   //  7: 5
	UINT32 offset                              : 13;  // 20: 8
	UINT32                                     : 3;   // 23:21
	UINT32 gain                                : 8;   // 31:24
} L9A0_P0R_BNR_DC_CTRL_00_T;

typedef struct { // 0x25b0
	UINT32 blur_enable                         : 2;   //  1: 0
} L9A0_P0R_BNR_DC_CTRL_01_T;

typedef struct { // 0x25b4
	UINT32 dc_bnr_gain_ctrl_y2                 : 8;   //  7: 0
	UINT32 dc_bnr_gain_ctrl_x2                 : 8;   // 15: 8
	UINT32 dc_bnr_gain_ctrl_y3                 : 8;   // 23:16
	UINT32 dc_bnr_gain_ctrl_x3                 : 8;   // 31:24
} L9A0_P0R_BNR_DC_CTRL_02_T;

typedef struct { // 0x25b8
	UINT32 dc_bnr_gain_ctrl_y0                 : 8;   //  7: 0
	UINT32 dc_bnr_gain_ctrl_x0                 : 8;   // 15: 8
	UINT32 dc_bnr_gain_ctrl_y1                 : 8;   // 23:16
	UINT32 dc_bnr_gain_ctrl_x1                 : 8;   // 31:24
} L9A0_P0R_BNR_DC_CTRL_03_T;

typedef struct { // 0x25bc
	UINT32 ac_bnr_protect_lvl_4                : 8;   //  7: 0
	UINT32 ac_bnr_protect_lvl_3                : 8;   // 15: 8
	UINT32 ac_bnr_protect_lvl_2                : 8;   // 23:16
	UINT32 ac_bnr_protect_lvl_1                : 8;   // 31:24
} L9A0_P0R_BNR_AC_CTRL_06_T;

typedef struct { // 0x25c0
	UINT32 bnr_h_en                            : 1;   //     0
	UINT32 bnr_v_en                            : 1;   //     1
	UINT32                                     : 2;   //  3: 2
	UINT32 source_type                         : 1;   //     4
	UINT32 status_read_type                    : 1;   //     5
	UINT32 status_read_mode                    : 2;   //  7: 6
	UINT32 hbmax_gain                          : 4;   // 11: 8
	UINT32 vbmax_gain                          : 4;   // 15:12
	UINT32 strength_resolution                 : 1;   //    16
	UINT32                                     : 3;   // 19:17
	UINT32 fiter_type                          : 1;   //    20
	UINT32                                     : 3;   // 23:21
	UINT32 output_mux                          : 2;   // 25:24
} L9A0_P0R_BNR_AC_CTRL_00_T;

typedef struct { // 0x25c4
	UINT32 strength_h_x0                       : 8;   //  7: 0
	UINT32 strength_h_x1                       : 8;   // 15: 8
	UINT32 strength_h_max                      : 8;   // 23:16
} L9A0_P0R_BNR_AC_CTRL_01_T;

typedef struct { // 0x25c8
	UINT32 strength_v_x0                       : 8;   //  7: 0
	UINT32 strength_v_x1                       : 8;   // 15: 8
	UINT32 strength_v_max                      : 8;   // 23:16
} L9A0_P0R_BNR_AC_CTRL_02_T;

typedef struct { // 0x25cc
	UINT32 h_offset_mode                       : 1;   //     0
	UINT32 manual_offset_h_value               : 3;   //  3: 1
	UINT32 v_offset_mode                       : 1;   //     4
	UINT32 manual_offset_v_value               : 3;   //  7: 5
	UINT32 use_of_hysterisis                   : 4;   // 11: 8
	UINT32                                     : 4;   // 15:12
	UINT32 t_filter_weight                     : 8;   // 23:16
} L9A0_P0R_BNR_AC_CTRL_03_T;

typedef struct { // 0x25d0
	UINT32 max_delta_th0                       : 8;   //  7: 0
	UINT32 max_delta_th1                       : 8;   // 15: 8
	UINT32 h_blockness_th                      : 8;   // 23:16
	UINT32 h_weight_max                        : 8;   // 31:24
} L9A0_P0R_BNR_AC_CTRL_04_T;

typedef struct { // 0x25d4
	UINT32 use_of_hysterisis                   : 4;   //  3: 0
	UINT32 block_boundary_processing_type      : 1;   //     4
} L9A0_P0R_BNR_AC_CTRL_05_T;

typedef struct { // 0x25d8
	UINT32 enable_snr                          : 1;   //     0
	UINT32 enable_mnr                          : 1;   //     1
	UINT32 enable_der                          : 1;   //     2
	UINT32 enable_dc_bnr                       : 1;   //     3
	UINT32 enable_ac_bnr                       : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 debug_enable                        : 1;   //     8
	UINT32 debug_mode                          : 1;   //     9
	UINT32 debug_snr_enable                    : 1;   //    10
	UINT32 debug_mnr_enable                    : 1;   //    11
	UINT32 debug_der_enable                    : 1;   //    12
	UINT32 debug_dc_bnr_enable                 : 1;   //    13
	UINT32 debug_ac_bnr_enable                 : 1;   //    14
	UINT32                                     : 1;   //    15
	UINT32 win_control_enable                  : 1;   //    16
	UINT32 border_enable                       : 1;   //    17
} L9A0_P0R_DNR_MAX_CTRL_T;

typedef struct { // 0x25dc
	UINT32 debug_bar_en                        : 1;   //     0
	UINT32                                     : 1;   //     1
	UINT32 show_debug_bar_for_bnr              : 1;   //     2
	UINT32                                     : 1;   //     3
	UINT32 gain                                : 3;   //  6: 4
	UINT32                                     : 1;   //     7
	UINT32 sd_hd_sel                           : 2;   //  9: 8
} L9A0_P0R_DNR_DBAR_CTRL_T;

typedef struct { // 0x25e0
	UINT32 ac_bnr_h_status                     : 8;   //  7: 0
	UINT32 ac_bnr_v_status                     : 8;   // 15: 8
	UINT32 dc_bnr_th                           : 14;  // 29:16
} L9A0_P0R_BNR_STAT_0_T;

typedef struct { // 0x25e4
	UINT32 der_en                              : 1;   //     0
	UINT32 out_mux                             : 3;   //  3: 1
	UINT32 bif_en                              : 1;   //     4
	UINT32 gain2weight_mapping                 : 1;   //     5
	UINT32                                     : 2;   //  7: 6
	UINT32 bif_th                              : 8;   // 15: 8
} L9A0_P0R_DER_CTRL_0_T;

typedef struct { // 0x25e8
	UINT32 gain_th0                            : 8;   //  7: 0
	UINT32 gain_th1                            : 8;   // 15: 8
} L9A0_P0R_DER_CTRL_1_T;

typedef struct { // 0x25f0
	UINT32 et_offset_                          : 8;   //  7: 0
	UINT32 motion_x_tearing_gain               : 8;   // 15: 8
	UINT32 tearing_gain                        : 8;   // 23:16
	UINT32 motion_gain                         : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_20_T;

typedef struct { // 0x25f4
	UINT32 motion_chroma_alpha                 : 8;   //  7: 0
	UINT32                                     : 8;   // 15: 8
	UINT32 v_gradiant_weight                   : 8;   // 23:16
	UINT32 h_gradiant_weight                   : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_21_T;

typedef struct { // 0x25f8
	UINT32 normalize_enable_motion             : 1;   //     0
	UINT32 increase_only_mode                  : 1;   //     1
	UINT32                                     : 2;   //  3: 2
	UINT32 normalize_enable_tearing            : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 normalize_base                      : 8;   // 15: 8
	UINT32 normalize_center                    : 8;   // 23:16
	UINT32 coring                              : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_22_T;

typedef struct { // 0x25fc
	UINT32 cr_wide_v_en                        : 1;   //     0
	UINT32 cr_narrow_v_en                      : 1;   //     1
	UINT32 cr_45_en                            : 1;   //     2
	UINT32 cr_15_en                            : 1;   //     3
	UINT32                                     : 12;  // 15: 4
	UINT32 post_median_enable                  : 1;   //    16
} L9A0_P0R_IPC_CTRL_23_T;

typedef struct { // 0x2600
	UINT32 ta_to_direction                     : 1;   //     0
	UINT32 ta_to_e_s                           : 1;   //     1
	UINT32                                     : 6;   //  7: 2
	UINT32 motion_max                          : 8;   // 15: 8
	UINT32 motion_min                          : 8;   // 23:16
	UINT32 ta_gain                             : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_24_T;

typedef struct { // 0x2604
	UINT32                                     : 16;  // 15: 0
	UINT32 h_gradiant_weight_                  : 8;   // 23:16
	UINT32 v_gradiant_weight_                  : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_25_T;

typedef struct { // 0x2608
	UINT32 ud_diff___b07_00                    : 8;   //  7: 0
	UINT32 ud_diff___b15_08                    : 8;   // 15: 8
	UINT32 lr_diff___b23_16                    : 8;   // 23:16
	UINT32 lr_diff___b31_24                    : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_26_T;

typedef struct { // 0x260c
	UINT32 new_va_enable                       : 1;   //     0
	UINT32                                     : 3;   //  3: 1
	UINT32 pe0_2d_dir_half_direction_enable    : 1;   //     4
	UINT32                                     : 3;   //  7: 5
	UINT32 e_s_offset_                         : 8;   // 15: 8
	UINT32 confidence_gain                     : 8;   // 23:16
	UINT32 e_s_gain                            : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_27_T;

typedef struct { // 0x2610
	UINT32 adaptive_va_enable                  : 1;   //     0
	UINT32 va_gain_inverse                     : 1;   //     1
	UINT32                                     : 6;   //  7: 2
	UINT32 motion_max                          : 8;   // 15: 8
	UINT32 motion_min                          : 8;   // 23:16
	UINT32 va_base                             : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_28_T;

typedef struct { // 0x2614
	UINT32 fmd22_maxvalueminth0                : 8;   //  7: 0
	UINT32 fmd22_minvaluemaxth0                : 8;   // 15: 8
	UINT32 fmd32_minvaluemaxth0                : 8;   // 23:16
	UINT32 fmd32_maxvalueminth0                : 8;   // 31:24
} L9A0_P0R_IPC_CTRL_29_T;

typedef struct { // 0x2640
	UINT32                                     : 4;   //  3: 0
	UINT32 mux_3                               : 4;   //  7: 4
	UINT32                                     : 4;   // 11: 8
	UINT32 mux_2                               : 4;   // 15:12
	UINT32                                     : 4;   // 19:16
	UINT32 mux_1                               : 4;   // 23:20
	UINT32 show_scale                          : 3;   // 26:24
	UINT32                                     : 1;   //    27
	UINT32 show_bar_1                          : 1;   //    28
	UINT32 show_bar_2                          : 1;   //    29
	UINT32 show_bar_3                          : 1;   //    30
	UINT32 show_bar_4                          : 1;   //    31
} L9A0_P0R_TPD_CTRL_00_T;

typedef struct { // 0x2670
	UINT32 bbd_en                              : 1;   //     0
	UINT32 hys_mode                            : 5;   //  5: 1
	UINT32 op_mode                             : 1;   //     6
	UINT32                                     : 1;   //     7
	UINT32 cnt_th                              : 8;   // 15: 8
	UINT32 diff_th                             : 8;   // 23:16
	UINT32 bbd_mux                             : 3;   // 26:24
	UINT32                                     : 1;   //    27
	UINT32 apl_mux                             : 3;   // 30:28
} L9A0_P0R_BBD_CTRL_00_T;

typedef struct { // 0x2674
	UINT32 x0                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y0                                  : 12;  // 27:16
} L9A0_P0R_BBD_CTRL_01_T;

typedef struct { // 0x2678
	UINT32 x1                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y1                                  : 12;  // 27:16
} L9A0_P0R_BBD_CTRL_02_T;

typedef struct { // 0x267c
	UINT32 x0                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y0                                  : 12;  // 27:16
} L9A0_P0R_BBD_STAT_00_T;

typedef struct { // 0x2680
	UINT32 x1                                  : 12;  // 11: 0
	UINT32                                     : 4;   // 15:12
	UINT32 y1                                  : 12;  // 27:16
} L9A0_P0R_BBD_STAT_01_T;

typedef struct { // 0x2684
	UINT32 p0r_apl_stat_00_f                   : 32;   // 31: 0
} L9A0_P0R_APL_STAT_00_T;

typedef struct {
	L9A0_P0L_PE0_LOAD_T             p0l_pe0_load;                    // 0x0400
	L9A0_P0L_PE0_INTR_T             p0l_pe0_intr;                    // 0x0404
	L9A0_P0L_PE0_STATUS0_T          p0l_pe0_status0;                 // 0x0408
	L9A0_P0L_PE0_STATUS1_T          p0l_pe0_status1;                 // 0x040c
	L9A0_P0L_PE0_OPMODE_T           p0l_pe0_opmode;                  // 0x0410
	L9A0_P0L_PE0_SRC_SIZE_T         p0l_pe0_src_size;                // 0x0414
	L9A0_P0L_PE0_FIELD_T            p0l_pe0_field;                   // 0x0418
	L9A0_P0L_PE0_PARAM_BY_DDR_T     p0l_pe0_param_by_ddr;            // 0x041c
	L9A0_P0L_WIN_CTRL_0_T           p0l_win_ctrl_0;                  // 0x0420
	L9A0_P0L_WIN_CTRL_1_T           p0l_win_ctrl_1;                  // 0x0424
	L9A0_P0L_WIN_CTRL_2_T           p0l_win_ctrl_2;                  // 0x0428
	L9A0_P0L_WIN_CTRL_3_T           p0l_win_ctrl_3;                  // 0x042c
	UINT32                          reserved0[4];                    // 0x0430~0x043c
	L9A0_P0L_TNR_CTRL_00_T          p0l_tnr_ctrl_00;                 // 0x0440
	L9A0_P0L_TNR_CTRL_01_T          p0l_tnr_ctrl_01;                 // 0x0444
	L9A0_P0L_TNR_CTRL_02_T          p0l_tnr_ctrl_02;                 // 0x0448
	L9A0_P0L_TNR_CTRL_03_T          p0l_tnr_ctrl_03;                 // 0x044c
	L9A0_P0L_TNR_CTRL_04_T          p0l_tnr_ctrl_04;                 // 0x0450
	L9A0_P0L_TNR_CTRL_05_T          p0l_tnr_ctrl_05;                 // 0x0454
	L9A0_P0L_TNR_CTRL_06_T          p0l_tnr_ctrl_06;                 // 0x0458
	L9A0_P0L_TNR_CTRL_07_T          p0l_tnr_ctrl_07;                 // 0x045c
	L9A0_P0L_TNR_CTRL_08_T          p0l_tnr_ctrl_08;                 // 0x0460
	L9A0_P0L_TNR_CTRL_09_T          p0l_tnr_ctrl_09;                 // 0x0464
	L9A0_P0L_TNR_CTRL_10_T          p0l_tnr_ctrl_10;                 // 0x0468
	L9A0_P0L_TNR_CTRL_11_T          p0l_tnr_ctrl_11;                 // 0x046c
	L9A0_P0L_TNR_CTRL_12_T          p0l_tnr_ctrl_12;                 // 0x0470
	L9A0_P0L_TNR_CTRL_13_T          p0l_tnr_ctrl_13;                 // 0x0474
	L9A0_P0L_TNR_CTRL_14_T          p0l_tnr_ctrl_14;                 // 0x0478
	L9A0_P0L_TNR_CTRL_15_T          p0l_tnr_ctrl_15;                 // 0x047c
	L9A0_P0L_TNR_CTRL_16_T          p0l_tnr_ctrl_16;                 // 0x0480
	L9A0_P0L_TNR_CTRL_17_T          p0l_tnr_ctrl_17;                 // 0x0484
	L9A0_P0L_TNR_CTRL_18_T          p0l_tnr_ctrl_18;                 // 0x0488
	L9A0_P0L_TNR_CTRL_19_T          p0l_tnr_ctrl_19;                 // 0x048c
	L9A0_P0L_TNR_CTRL_20_T          p0l_tnr_ctrl_20;                 // 0x0490
	L9A0_P0L_TNR_CTRL_21_T          p0l_tnr_ctrl_21;                 // 0x0494
	L9A0_P0L_TNR_CTRL_22_T          p0l_tnr_ctrl_22;                 // 0x0498
	L9A0_P0L_TNR_CTRL_23_T          p0l_tnr_ctrl_23;                 // 0x049c
	L9A0_P0L_TNR_CTRL_24_T          p0l_tnr_ctrl_24;                 // 0x04a0
	L9A0_P0L_TNR_CTRL_25_T          p0l_tnr_ctrl_25;                 // 0x04a4
	L9A0_P0L_TNR_CTRL_26_T          p0l_tnr_ctrl_26;                 // 0x04a8
	L9A0_P0L_TNR_CTRL_27_T          p0l_tnr_ctrl_27;                 // 0x04ac
	L9A0_P0L_TNR_CTRL_28_T          p0l_tnr_ctrl_28;                 // 0x04b0
	L9A0_P0L_TNR_CTRL_29_T          p0l_tnr_ctrl_29;                 // 0x04b4
	L9A0_P0L_TNR_CTRL_30_T          p0l_tnr_ctrl_30;                 // 0x04b8
	L9A0_P0L_TNR_CTRL_31_T          p0l_tnr_ctrl_31;                 // 0x04bc
	L9A0_P0L_TNR_STATUS_00_T        p0l_tnr_status_00;               // 0x04c0
	L9A0_P0L_TNR_STATUS_01_T        p0l_tnr_status_01;               // 0x04c4
	L9A0_P0L_TNR_STATUS_02_T        p0l_tnr_status_02;               // 0x04c8
	L9A0_P0L_TNR_STATUS_03_T        p0l_tnr_status_03;               // 0x04cc
	L9A0_P0L_TNR_MAIN_LUT_00_T      p0l_tnr_main_lut_00;             // 0x04d0
	L9A0_P0L_TNR_MAIN_LUT_01_T      p0l_tnr_main_lut_01;             // 0x04d4
	L9A0_P0L_TNR_MAIN_LUT_02_T      p0l_tnr_main_lut_02;             // 0x04d8
	L9A0_P0L_TI_CTRL_T              p0l_ti_ctrl;                     // 0x04dc
	L9A0_P0L_TNR_NT_LVL_LUT_00_T    p0l_tnr_nt_lvl_lut_00;           // 0x04e0
	L9A0_P0L_TNR_NT_LVL_LUT_01_T    p0l_tnr_nt_lvl_lut_01;           // 0x04e4
	L9A0_P0L_TNR_NT_LVL_LUT_02_T    p0l_tnr_nt_lvl_lut_02;           // 0x04e8
	L9A0_P0L_TNR_NT_LVL_LUT_03_T    p0l_tnr_nt_lvl_lut_03;           // 0x04ec
	L9A0_P0L_TNR_CRG_CTRL_00_T      p0l_tnr_crg_ctrl_00;             // 0x04f0
	L9A0_P0L_TNR_CRG_CTRL_01_T      p0l_tnr_crg_ctrl_01;             // 0x04f4
	UINT32                          reserved1[2];                    // 0x04f8~0x04fc
	L9A0_P0L_IPC_CTRL_00_T          p0l_ipc_ctrl_00;                 // 0x0500
	L9A0_P0L_IPC_CTRL_01_T          p0l_ipc_ctrl_01;                 // 0x0504
	L9A0_P0L_IPC_CTRL_02_T          p0l_ipc_ctrl_02;                 // 0x0508
	L9A0_P0L_IPC_CTRL_03_T          p0l_ipc_ctrl_03;                 // 0x050c
	L9A0_P0L_IPC_CTRL_04_T          p0l_ipc_ctrl_04;                 // 0x0510
	L9A0_P0L_IPC_CTRL_05_T          p0l_ipc_ctrl_05;                 // 0x0514
	L9A0_P0L_IPC_CTRL_06_T          p0l_ipc_ctrl_06;                 // 0x0518
	L9A0_P0L_IPC_CTRL_07_T          p0l_ipc_ctrl_07;                 // 0x051c
	L9A0_P0L_IPC_CTRL_08_T          p0l_ipc_ctrl_08;                 // 0x0520
	L9A0_P0L_IPC_CTRL_09_T          p0l_ipc_ctrl_09;                 // 0x0524
	L9A0_P0L_IPC_CTRL_10_T          p0l_ipc_ctrl_10;                 // 0x0528
	L9A0_P0L_IPC_CTRL_11_T          p0l_ipc_ctrl_11;                 // 0x052c
	L9A0_P0L_IPC_CTRL_12_T          p0l_ipc_ctrl_12;                 // 0x0530
	L9A0_P0L_IPC_CTRL_13_T          p0l_ipc_ctrl_13;                 // 0x0534
	L9A0_P0L_IPC_CTRL_14_T          p0l_ipc_ctrl_14;                 // 0x0538
	L9A0_P0L_IPC_CTRL_15_T          p0l_ipc_ctrl_15;                 // 0x053c
	L9A0_P0L_IPC_CTRL_16_T          p0l_ipc_ctrl_16;                 // 0x0540
	L9A0_P0L_IPC_CTRL_17_T          p0l_ipc_ctrl_17;                 // 0x0544
	L9A0_P0L_IPC_CTRL_18_T          p0l_ipc_ctrl_18;                 // 0x0548
	L9A0_P0L_IPC_CTRL_19_T          p0l_ipc_ctrl_19;                 // 0x054c
	L9A0_P0L_IPC_STATUS_00_T        p0l_ipc_status_00;               // 0x0550
	L9A0_P0L_IPC_STATUS_01_T        p0l_ipc_status_01;               // 0x0554
	L9A0_P0L_IPC_STATUS_02_T        p0l_ipc_status_02;               // 0x0558
	L9A0_P0L_IPC_STATUS_03_T        p0l_ipc_status_03;               // 0x055c
	L9A0_P0L_CLC_CTRL_00_T          p0l_clc_ctrl_00;                 // 0x0560
	L9A0_P0L_CLC_CTRL_01_T          p0l_clc_ctrl_01;                 // 0x0564
	L9A0_P0L_CLC_CTRL_02_T          p0l_clc_ctrl_02;                 // 0x0568
	L9A0_P0L_CLC_CTRL_03_T          p0l_clc_ctrl_03;                 // 0x056c
	L9A0_P0L_CLC_CTRL_04_T          p0l_clc_ctrl_04;                 // 0x0570
	L9A0_P0L_CLC_CTRL_05_T          p0l_clc_ctrl_05;                 // 0x0574
	L9A0_P0L_CLC_CTRL_06_T          p0l_clc_ctrl_06;                 // 0x0578
	L9A0_P0L_CLC_STAT_00_T          p0l_clc_stat_00;                 // 0x057c
	L9A0_P0L_VFLT_CTRL_T            p0l_vflt_ctrl;                   // 0x0580
	L9A0_P0L_SNR_CTRL_00_T          p0l_snr_ctrl_00;                 // 0x0584
	L9A0_P0L_MNR_CTRL_00_T          p0l_mnr_ctrl_00;                 // 0x0588
	L9A0_P0L_MNR_CTRL_01_T          p0l_mnr_ctrl_01;                 // 0x058c
	L9A0_P0L_MNR_CTRL_02_T          p0l_mnr_ctrl_02;                 // 0x0590
	L9A0_P0L_MNR_CTRL_03_T          p0l_mnr_ctrl_03;                 // 0x0594
	L9A0_P0L_MNR_CTRL_04_T          p0l_mnr_ctrl_04;                 // 0x0598
	L9A0_P0L_MNR_CTRL_05_T          p0l_mnr_ctrl_05;                 // 0x059c
	L9A0_P0L_MNR_CTRL_06_T          p0l_mnr_ctrl_06;                 // 0x05a0
	UINT32                          reserved2;                       // 0x05a4
	L9A0_P0L_VFILTER_01_T           p0l_vfilter_01;                  // 0x05a8
	L9A0_P0L_BNR_DC_CTRL_00_T       p0l_bnr_dc_ctrl_00;              // 0x05ac
	L9A0_P0L_BNR_DC_CTRL_01_T       p0l_bnr_dc_ctrl_01;              // 0x05b0
	L9A0_P0L_BNR_DC_CTRL_02_T       p0l_bnr_dc_ctrl_02;              // 0x05b4
	L9A0_P0L_BNR_DC_CTRL_03_T       p0l_bnr_dc_ctrl_03;              // 0x05b8
	L9A0_P0L_BNR_AC_CTRL_06_T       p0l_bnr_ac_ctrl_06;              // 0x05bc
	L9A0_P0L_BNR_AC_CTRL_00_T       p0l_bnr_ac_ctrl_00;              // 0x05c0
	L9A0_P0L_BNR_AC_CTRL_01_T       p0l_bnr_ac_ctrl_01;              // 0x05c4
	L9A0_P0L_BNR_AC_CTRL_02_T       p0l_bnr_ac_ctrl_02;              // 0x05c8
	L9A0_P0L_BNR_AC_CTRL_03_T       p0l_bnr_ac_ctrl_03;              // 0x05cc
	L9A0_P0L_BNR_AC_CTRL_04_T       p0l_bnr_ac_ctrl_04;              // 0x05d0
	L9A0_P0L_BNR_AC_CTRL_05_T       p0l_bnr_ac_ctrl_05;              // 0x05d4
	L9A0_P0L_DNR_MAX_CTRL_T         p0l_dnr_max_ctrl;                // 0x05d8
	L9A0_P0L_DNR_DBAR_CTRL_T        p0l_dnr_dbar_ctrl;               // 0x05dc
	L9A0_P0L_BNR_STAT_0_T           p0l_bnr_stat_0;                  // 0x05e0
	L9A0_P0L_DER_CTRL_0_T           p0l_der_ctrl_0;                  // 0x05e4
	L9A0_P0L_DER_CTRL_1_T           p0l_der_ctrl_1;                  // 0x05e8
	UINT32                          reserved3;                       // 0x05ec
	L9A0_P0L_IPC_CTRL_20_T          p0l_ipc_ctrl_20;                 // 0x05f0
	L9A0_P0L_IPC_CTRL_21_T          p0l_ipc_ctrl_21;                 // 0x05f4
	L9A0_P0L_IPC_CTRL_22_T          p0l_ipc_ctrl_22;                 // 0x05f8
	L9A0_P0L_IPC_CTRL_23_T          p0l_ipc_ctrl_23;                 // 0x05fc
	L9A0_P0L_IPC_CTRL_24_T          p0l_ipc_ctrl_24;                 // 0x0600
	L9A0_P0L_IPC_CTRL_25_T          p0l_ipc_ctrl_25;                 // 0x0604
	L9A0_P0L_IPC_CTRL_26_T          p0l_ipc_ctrl_26;                 // 0x0608
	L9A0_P0L_IPC_CTRL_27_T          p0l_ipc_ctrl_27;                 // 0x060c
	L9A0_P0L_IPC_CTRL_28_T          p0l_ipc_ctrl_28;                 // 0x0610
	L9A0_P0L_IPC_CTRL_29_T          p0l_ipc_ctrl_29;                 // 0x0614
	UINT32                          reserved4[10];                   // 0x0618~0x063c
	L9A0_P0L_TPD_CTRL_00_T          p0l_tpd_ctrl_00;                 // 0x0640
	UINT32                          reserved5[11];                   // 0x0644~0x066c
	L9A0_P0L_BBD_CTRL_00_T          p0l_bbd_ctrl_00;                 // 0x0670
	L9A0_P0L_BBD_CTRL_01_T          p0l_bbd_ctrl_01;                 // 0x0674
	L9A0_P0L_BBD_CTRL_02_T          p0l_bbd_ctrl_02;                 // 0x0678
	L9A0_P0L_BBD_STAT_00_T          p0l_bbd_stat_00;                 // 0x067c
	L9A0_P0L_BBD_STAT_01_T          p0l_bbd_stat_01;                 // 0x0680
	L9A0_P0L_APL_STAT_00_T          p0l_apl_stat_00;                 // 0x0684
} DE_P0L_REG_L9A0_T;

typedef struct {
	L9A0_P0R_PE0_LOAD_T             p0r_pe0_load;                    // 0x2400
	L9A0_P0R_PE0_INTR_T             p0r_pe0_intr;                    // 0x2404
	L9A0_P0R_PE0_STATUS0_T          p0r_pe0_status0;                 // 0x2408
	L9A0_P0R_PE0_STATUS1_T          p0r_pe0_status1;                 // 0x240c
	L9A0_P0R_PE0_OPMODE_T           p0r_pe0_opmode;                  // 0x2410
	L9A0_P0R_PE0_SRC_SIZE_T         p0r_pe0_src_size;                // 0x2414
	L9A0_P0R_PE0_FIELD_T            p0r_pe0_field;                   // 0x2418
	L9A0_P0R_PE0_PARAM_BY_DDR_T     p0r_pe0_param_by_ddr;            // 0x241c
	L9A0_P0R_WIN_CTRL_0_T           p0r_win_ctrl_0;                  // 0x2420
	L9A0_P0R_WIN_CTRL_1_T           p0r_win_ctrl_1;                  // 0x2424
	L9A0_P0R_WIN_CTRL_2_T           p0r_win_ctrl_2;                  // 0x2428
	L9A0_P0R_WIN_CTRL_3_T           p0r_win_ctrl_3;                  // 0x242c
	UINT32                          reserved6[4];                    // 0x2430~0x243c
	L9A0_P0R_TNR_CTRL_00_T          p0r_tnr_ctrl_00;                 // 0x2440
	L9A0_P0R_TNR_CTRL_01_T          p0r_tnr_ctrl_01;                 // 0x2444
	L9A0_P0R_TNR_CTRL_02_T          p0r_tnr_ctrl_02;                 // 0x2448
	L9A0_P0R_TNR_CTRL_03_T          p0r_tnr_ctrl_03;                 // 0x244c
	L9A0_P0R_TNR_CTRL_04_T          p0r_tnr_ctrl_04;                 // 0x2450
	L9A0_P0R_TNR_CTRL_05_T          p0r_tnr_ctrl_05;                 // 0x2454
	L9A0_P0R_TNR_CTRL_06_T          p0r_tnr_ctrl_06;                 // 0x2458
	L9A0_P0R_TNR_CTRL_07_T          p0r_tnr_ctrl_07;                 // 0x245c
	L9A0_P0R_TNR_CTRL_08_T          p0r_tnr_ctrl_08;                 // 0x2460
	L9A0_P0R_TNR_CTRL_09_T          p0r_tnr_ctrl_09;                 // 0x2464
	L9A0_P0R_TNR_CTRL_10_T          p0r_tnr_ctrl_10;                 // 0x2468
	L9A0_P0R_TNR_CTRL_11_T          p0r_tnr_ctrl_11;                 // 0x246c
	L9A0_P0R_TNR_CTRL_12_T          p0r_tnr_ctrl_12;                 // 0x2470
	L9A0_P0R_TNR_CTRL_13_T          p0r_tnr_ctrl_13;                 // 0x2474
	L9A0_P0R_TNR_CTRL_14_T          p0r_tnr_ctrl_14;                 // 0x2478
	L9A0_P0R_TNR_CTRL_15_T          p0r_tnr_ctrl_15;                 // 0x247c
	L9A0_P0R_TNR_CTRL_16_T          p0r_tnr_ctrl_16;                 // 0x2480
	L9A0_P0R_TNR_CTRL_17_T          p0r_tnr_ctrl_17;                 // 0x2484
	L9A0_P0R_TNR_CTRL_18_T          p0r_tnr_ctrl_18;                 // 0x2488
	L9A0_P0R_TNR_CTRL_19_T          p0r_tnr_ctrl_19;                 // 0x248c
	L9A0_P0R_TNR_CTRL_20_T          p0r_tnr_ctrl_20;                 // 0x2490
	L9A0_P0R_TNR_CTRL_21_T          p0r_tnr_ctrl_21;                 // 0x2494
	L9A0_P0R_TNR_CTRL_22_T          p0r_tnr_ctrl_22;                 // 0x2498
	L9A0_P0R_TNR_CTRL_23_T          p0r_tnr_ctrl_23;                 // 0x249c
	L9A0_P0R_TNR_CTRL_24_T          p0r_tnr_ctrl_24;                 // 0x24a0
	L9A0_P0R_TNR_CTRL_25_T          p0r_tnr_ctrl_25;                 // 0x24a4
	L9A0_P0R_TNR_CTRL_26_T          p0r_tnr_ctrl_26;                 // 0x24a8
	L9A0_P0R_TNR_CTRL_27_T          p0r_tnr_ctrl_27;                 // 0x24ac
	L9A0_P0R_TNR_CTRL_28_T          p0r_tnr_ctrl_28;                 // 0x24b0
	L9A0_P0R_TNR_CTRL_29_T          p0r_tnr_ctrl_29;                 // 0x24b4
	L9A0_P0R_TNR_CTRL_30_T          p0r_tnr_ctrl_30;                 // 0x24b8
	L9A0_P0R_TNR_CTRL_31_T          p0r_tnr_ctrl_31;                 // 0x24bc
	L9A0_P0R_TNR_STATUS_00_T        p0r_tnr_status_00;               // 0x24c0
	L9A0_P0R_TNR_STATUS_01_T        p0r_tnr_status_01;               // 0x24c4
	L9A0_P0R_TNR_STATUS_02_T        p0r_tnr_status_02;               // 0x24c8
	L9A0_P0R_TNR_STATUS_03_T        p0r_tnr_status_03;               // 0x24cc
	L9A0_P0R_TNR_MAIN_LUT_00_T      p0r_tnr_main_lut_00;             // 0x24d0
	L9A0_P0R_TNR_MAIN_LUT_01_T      p0r_tnr_main_lut_01;             // 0x24d4
	L9A0_P0R_TNR_MAIN_LUT_02_T      p0r_tnr_main_lut_02;             // 0x24d8
	L9A0_P0R_TI_CTRL_T              p0r_ti_ctrl;                     // 0x24dc
	L9A0_P0R_TNR_NT_LVL_LUT_00_T    p0r_tnr_nt_lvl_lut_00;           // 0x24e0
	L9A0_P0R_TNR_NT_LVL_LUT_01_T    p0r_tnr_nt_lvl_lut_01;           // 0x24e4
	L9A0_P0R_TNR_NT_LVL_LUT_02_T    p0r_tnr_nt_lvl_lut_02;           // 0x24e8
	L9A0_P0R_TNR_NT_LVL_LUT_03_T    p0r_tnr_nt_lvl_lut_03;           // 0x24ec
	L9A0_P0R_TNR_CRG_CTRL_00_T      p0r_tnr_crg_ctrl_00;             // 0x24f0
	L9A0_P0R_TNR_CRG_CTRL_01_T      p0r_tnr_crg_ctrl_01;             // 0x24f4
	UINT32                          reserved7[2];                    // 0x24f8~0x24fc
	L9A0_P0R_IPC_CTRL_00_T          p0r_ipc_ctrl_00;                 // 0x2500
	L9A0_P0R_IPC_CTRL_01_T          p0r_ipc_ctrl_01;                 // 0x2504
	L9A0_P0R_IPC_CTRL_02_T          p0r_ipc_ctrl_02;                 // 0x2508
	L9A0_P0R_IPC_CTRL_03_T          p0r_ipc_ctrl_03;                 // 0x250c
	L9A0_P0R_IPC_CTRL_04_T          p0r_ipc_ctrl_04;                 // 0x2510
	L9A0_P0R_IPC_CTRL_05_T          p0r_ipc_ctrl_05;                 // 0x2514
	L9A0_P0R_IPC_CTRL_06_T          p0r_ipc_ctrl_06;                 // 0x2518
	L9A0_P0R_IPC_CTRL_07_T          p0r_ipc_ctrl_07;                 // 0x251c
	L9A0_P0R_IPC_CTRL_08_T          p0r_ipc_ctrl_08;                 // 0x2520
	L9A0_P0R_IPC_CTRL_09_T          p0r_ipc_ctrl_09;                 // 0x2524
	L9A0_P0R_IPC_CTRL_10_T          p0r_ipc_ctrl_10;                 // 0x2528
	L9A0_P0R_IPC_CTRL_11_T          p0r_ipc_ctrl_11;                 // 0x252c
	L9A0_P0R_IPC_CTRL_12_T          p0r_ipc_ctrl_12;                 // 0x2530
	L9A0_P0R_IPC_CTRL_13_T          p0r_ipc_ctrl_13;                 // 0x2534
	L9A0_P0R_IPC_CTRL_14_T          p0r_ipc_ctrl_14;                 // 0x2538
	L9A0_P0R_IPC_CTRL_15_T          p0r_ipc_ctrl_15;                 // 0x253c
	L9A0_P0R_IPC_CTRL_16_T          p0r_ipc_ctrl_16;                 // 0x2540
	L9A0_P0R_IPC_CTRL_17_T          p0r_ipc_ctrl_17;                 // 0x2544
	L9A0_P0R_IPC_CTRL_18_T          p0r_ipc_ctrl_18;                 // 0x2548
	L9A0_P0R_IPC_CTRL_19_T          p0r_ipc_ctrl_19;                 // 0x254c
	L9A0_P0R_IPC_STATUS_00_T        p0r_ipc_status_00;               // 0x2550
	L9A0_P0R_IPC_STATUS_01_T        p0r_ipc_status_01;               // 0x2554
	L9A0_P0R_IPC_STATUS_02_T        p0r_ipc_status_02;               // 0x2558
	L9A0_P0R_IPC_STATUS_03_T        p0r_ipc_status_03;               // 0x255c
	L9A0_P0R_CLC_CTRL_00_T          p0r_clc_ctrl_00;                 // 0x2560
	L9A0_P0R_CLC_CTRL_01_T          p0r_clc_ctrl_01;                 // 0x2564
	L9A0_P0R_CLC_CTRL_02_T          p0r_clc_ctrl_02;                 // 0x2568
	L9A0_P0R_CLC_CTRL_03_T          p0r_clc_ctrl_03;                 // 0x256c
	L9A0_P0R_CLC_CTRL_04_T          p0r_clc_ctrl_04;                 // 0x2570
	L9A0_P0R_CLC_CTRL_05_T          p0r_clc_ctrl_05;                 // 0x2574
	L9A0_P0R_CLC_CTRL_06_T          p0r_clc_ctrl_06;                 // 0x2578
	L9A0_P0R_CLC_STAT_00_T          p0r_clc_stat_00;                 // 0x257c
	L9A0_P0R_VFLT_CTRL_T            p0r_vflt_ctrl;                   // 0x2580
	L9A0_P0R_SNR_CTRL_00_T          p0r_snr_ctrl_00;                 // 0x2584
	L9A0_P0R_MNR_CTRL_00_T          p0r_mnr_ctrl_00;                 // 0x2588
	L9A0_P0R_MNR_CTRL_01_T          p0r_mnr_ctrl_01;                 // 0x258c
	L9A0_P0R_MNR_CTRL_02_T          p0r_mnr_ctrl_02;                 // 0x2590
	L9A0_P0R_MNR_CTRL_03_T          p0r_mnr_ctrl_03;                 // 0x2594
	L9A0_P0R_MNR_CTRL_04_T          p0r_mnr_ctrl_04;                 // 0x2598
	L9A0_P0R_MNR_CTRL_05_T          p0r_mnr_ctrl_05;                 // 0x259c
	L9A0_P0R_MNR_CTRL_06_T          p0r_mnr_ctrl_06;                 // 0x25a0
	UINT32                          reserved8;                       // 0x25a4
	L9A0_P0R_VFILTER_01_T           p0r_vfilter_01;                  // 0x25a8
	L9A0_P0R_BNR_DC_CTRL_00_T       p0r_bnr_dc_ctrl_00;              // 0x25ac
	L9A0_P0R_BNR_DC_CTRL_01_T       p0r_bnr_dc_ctrl_01;              // 0x25b0
	L9A0_P0R_BNR_DC_CTRL_02_T       p0r_bnr_dc_ctrl_02;              // 0x25b4
	L9A0_P0R_BNR_DC_CTRL_03_T       p0r_bnr_dc_ctrl_03;              // 0x25b8
	L9A0_P0R_BNR_AC_CTRL_06_T       p0r_bnr_ac_ctrl_06;              // 0x25bc
	L9A0_P0R_BNR_AC_CTRL_00_T       p0r_bnr_ac_ctrl_00;              // 0x25c0
	L9A0_P0R_BNR_AC_CTRL_01_T       p0r_bnr_ac_ctrl_01;              // 0x25c4
	L9A0_P0R_BNR_AC_CTRL_02_T       p0r_bnr_ac_ctrl_02;              // 0x25c8
	L9A0_P0R_BNR_AC_CTRL_03_T       p0r_bnr_ac_ctrl_03;              // 0x25cc
	L9A0_P0R_BNR_AC_CTRL_04_T       p0r_bnr_ac_ctrl_04;              // 0x25d0
	L9A0_P0R_BNR_AC_CTRL_05_T       p0r_bnr_ac_ctrl_05;              // 0x25d4
	L9A0_P0R_DNR_MAX_CTRL_T         p0r_dnr_max_ctrl;                // 0x25d8
	L9A0_P0R_DNR_DBAR_CTRL_T        p0r_dnr_dbar_ctrl;               // 0x25dc
	L9A0_P0R_BNR_STAT_0_T           p0r_bnr_stat_0;                  // 0x25e0
	L9A0_P0R_DER_CTRL_0_T           p0r_der_ctrl_0;                  // 0x25e4
	L9A0_P0R_DER_CTRL_1_T           p0r_der_ctrl_1;                  // 0x25e8
	UINT32                          reserved9;                       // 0x25ec
	L9A0_P0R_IPC_CTRL_20_T          p0r_ipc_ctrl_20;                 // 0x25f0
	L9A0_P0R_IPC_CTRL_21_T          p0r_ipc_ctrl_21;                 // 0x25f4
	L9A0_P0R_IPC_CTRL_22_T          p0r_ipc_ctrl_22;                 // 0x25f8
	L9A0_P0R_IPC_CTRL_23_T          p0r_ipc_ctrl_23;                 // 0x25fc
	L9A0_P0R_IPC_CTRL_24_T          p0r_ipc_ctrl_24;                 // 0x2600
	L9A0_P0R_IPC_CTRL_25_T          p0r_ipc_ctrl_25;                 // 0x2604
	L9A0_P0R_IPC_CTRL_26_T          p0r_ipc_ctrl_26;                 // 0x2608
	L9A0_P0R_IPC_CTRL_27_T          p0r_ipc_ctrl_27;                 // 0x260c
	L9A0_P0R_IPC_CTRL_28_T          p0r_ipc_ctrl_28;                 // 0x2610
	L9A0_P0R_IPC_CTRL_29_T          p0r_ipc_ctrl_29;                 // 0x2614
	UINT32                          reserved10[10];                  // 0x2618~0x263c
	L9A0_P0R_TPD_CTRL_00_T          p0r_tpd_ctrl_00;                 // 0x2640
	UINT32                          reserved11[11];                  // 0x2644~0x266c
	L9A0_P0R_BBD_CTRL_00_T          p0r_bbd_ctrl_00;                 // 0x2670
	L9A0_P0R_BBD_CTRL_01_T          p0r_bbd_ctrl_01;                 // 0x2674
	L9A0_P0R_BBD_CTRL_02_T          p0r_bbd_ctrl_02;                 // 0x2678
	L9A0_P0R_BBD_STAT_00_T          p0r_bbd_stat_00;                 // 0x267c
	L9A0_P0R_BBD_STAT_01_T          p0r_bbd_stat_01;                 // 0x2680
	L9A0_P0R_APL_STAT_00_T          p0r_apl_stat_00;                 // 0x2684
} DE_P0R_REG_L9A0_T;

#endif
