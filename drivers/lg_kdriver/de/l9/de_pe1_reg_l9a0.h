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

#ifndef _REG_PE1_L9A0_h
#define _REG_PE1_L9A0_h

typedef struct { // 0x1300
	UINT32 load_time                       : 1;   //     0
	UINT32 load_enable                     : 1;   //     1
	UINT32 load_type                       : 1;   //     2
} L9A0_PE1_L_TOP_CTRL_00_T;

typedef struct { // 0x1304
	UINT32 width                           : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 height                          : 12;  // 27:16
} L9A0_PE1_L_TOP_CTRL_01_T;

typedef struct { // 0x1308
	UINT32 tpg_positon                     : 1;   //     0
	UINT32                                 : 7;   //  7: 1
	UINT32 vdpulse_pos                     : 11;  // 18: 8
} L9A0_PE1_L_TOP_CTRL_02_T;

typedef struct { // 0x130c
	UINT32 vcnt                            : 12;  // 11: 0
	UINT32 va_pe1_in                       : 1;   //    12
	UINT32 va_pe1_out                      : 1;   //    13
	UINT32                                 : 2;   // 15:14
	UINT32 stat_tpg                        : 1;   //    16
	UINT32 stat_gt                         : 3;   // 19:17
	UINT32 stat_crg_lsr                    : 3;   // 22:20
	UINT32                                 : 1;   //    23
	UINT32 stat_crg_shp                    : 3;   // 26:24
	UINT32 stat_dce                        : 1;   //    27
	UINT32 stat_cen                        : 1;   //    28
	UINT32 stat_wb                         : 1;   //    29
	UINT32 stat_gmc                        : 2;   // 31:30
} L9A0_PE1_L_TOP_CTRL_03_T;

typedef struct { // 0x1320
	UINT32                                 : 6;   //  5: 0
	UINT32 win_outside                     : 1;   //     6
	UINT32 win_en                          : 1;   //     7
	UINT32 bdr_alpha                       : 5;   // 12: 8
	UINT32 bdr_wid                         : 2;   // 14:13
	UINT32 bdr_en                          : 1;   //    15
	UINT32 cr5                             : 5;   // 20:16
	UINT32 cb5                             : 5;   // 25:21
	UINT32 yy6                             : 6;   // 31:26
} L9A0_PE1_L_WIN_CTRL_00_T;

typedef struct { // 0x1324
	UINT32 win_w0_x0                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w0_y0                       : 11;  // 26:16
} L9A0_PE1_L_WIN_CTRL_01_T;

typedef struct { // 0x1328
	UINT32 win_w0_x1                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w0_y1                       : 11;  // 26:16
} L9A0_PE1_L_WIN_CTRL_02_T;

typedef struct { // 0x132c
	UINT32 win_w1_x0                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w1_y0                       : 11;  // 26:16
} L9A0_PE1_L_WIN_CTRL_03_T;

typedef struct { // 0x1330
	UINT32 win_w1_x1                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w1_y1                       : 11;  // 26:16
} L9A0_PE1_L_WIN_CTRL_04_T;

typedef struct { // 0x1350
	UINT32 apl_win_ctrl_x0                 : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 apl_win_ctrl_y0                 : 11;  // 26:16
} L9A0_PE1_L_APL_CTRL_00_T;

typedef struct { // 0x1354
	UINT32 apl_win_ctrl_x1                 : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 apl_win_ctrl_y1                 : 11;  // 26:16
} L9A0_PE1_L_APL_CTRL_01_T;

typedef struct { // 0x1358
	UINT32 apl_position                    : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 apl_y_type                      : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 act_win_mode                    : 1;   //     8
} L9A0_PE1_L_APL_CTRL_02_T;

typedef struct { // 0x135c
	UINT32 apl_y                           : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 apl_rgb                         : 10;  // 25:16
} L9A0_PE1_L_APL_CTRL_03_T;

typedef struct { // 0x1360
	UINT32 apl_b                           : 10;  //  9: 0
	UINT32 apl_g                           : 10;  // 19:10
	UINT32 apl_r                           : 10;  // 29:20
} L9A0_PE1_L_APL_CTRL_04_T;

typedef struct { // 0x1370
	UINT32 tpg_enable                      : 1;   //     0
	UINT32 pattern_type                    : 2;   //  2: 1
	UINT32                                 : 1;   //     3
	UINT32 blend_alpha                     : 4;   //  7: 4
	UINT32 blt_size_x                      : 12;  // 19: 8
	UINT32 blt_size_y                      : 12;  // 31:20
} L9A0_PE1_L_TPG_CTRL_00_T;

typedef struct { // 0x1374
	UINT32 gradation_stride                : 7;   //  6: 0
	UINT32 gradation_direction             : 1;   //     7
	UINT32 gradation_bar_en                : 4;   // 11: 8
	UINT32                                 : 4;   // 15:12
	UINT32 washing_num_of_bar_x            : 3;   // 18:16
	UINT32                                 : 1;   //    19
	UINT32 washing_num_of_bar_y            : 3;   // 22:20
	UINT32                                 : 1;   //    23
	UINT32 washing_speed                   : 8;   // 31:24
} L9A0_PE1_L_TPG_CTRL_01_T;

typedef struct { // 0x1378
	UINT32 patch_en                        : 32;  // 31: 0
} L9A0_PE1_L_TPG_CTRL_02_T;

typedef struct { // 0x137c
	UINT32 tpg_indir_addr                  : 7;   //  6: 0
	UINT32                                 : 5;   // 11: 7
	UINT32 tpg_indir_ai_en                 : 1;   //    12
} L9A0_PE1_L_TPG_IA_CTRL_T;

typedef struct { // 0x1380
	UINT32 tpg_indir_data                  : 32;  // 31: 0
} L9A0_PE1_L_TPG_IA_DATA_T;

typedef struct { // 0x13a0
	UINT32 vignetting_enable               : 1;   //     0
	UINT32 film_contrast_enable            : 1;   //     1
	UINT32                                 : 6;   //  7: 2
	UINT32 contrast_alpha                  : 8;   // 15: 8
	UINT32 contrast_delta_max              : 8;   // 23:16
	UINT32 vignetting_gain                 : 8;   // 31:24
} L9A0_PE1_L_FILM_CTRL_00_T;

typedef struct { // 0x13a4
	UINT32 noise_gen_enable                : 1;   //     0
	UINT32 noise_frame_rate                : 3;   //  3: 1
	UINT32 noise_size                      : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 noise_gain                      : 8;   // 15: 8
} L9A0_PE1_L_FILM_CTRL_01_T;

typedef struct { // 0x13a8
	UINT32 tone_gain                       : 7;   //  6: 0
	UINT32                                 : 1;   //     7
	UINT32 tone_offset                     : 6;   // 13: 8
} L9A0_PE1_L_FILM_CTRL_02_T;

typedef struct { // 0x13c0
	UINT32 flats_t0_fc0                    : 2;   //  1: 0
	UINT32 flats_t0_fcs                    : 2;   //  3: 2
	UINT32 flats_t1_fc0                    : 2;   //  5: 4
	UINT32 flats_t1_fc1                    : 2;   //  7: 6
	UINT32 flats_t0_fcp                    : 2;   //  9: 8
	UINT32 flats_t0_fcd                    : 2;   // 11:10
	UINT32 t0_bc0                          : 2;   // 13:12
	UINT32 t1_bc0                          : 2;   // 15:14
	UINT32 dth_t0_dth0                     : 7;   // 22:16
	UINT32 h_disable                       : 1;   //    23
	UINT32 dth_t0_dths                     : 8;   // 31:24
} L9A0_PE1_L_HFNR_CTRL_00_T;

typedef struct { // 0x13c4
	UINT32 dth_t0_dthp                     : 8;   //  7: 0
	UINT32 dth_t1_dth0                     : 4;   // 11: 8
	UINT32 dth_t1_dth1                     : 4;   // 15:12
} L9A0_PE1_L_HFNR_CTRL_01_T;

typedef struct { // 0x13d0
	UINT32 vsum_mode                       : 2;   //  1: 0
	UINT32 hsum_mode                       : 2;   //  3: 2
	UINT32 vsum121_en                      : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 vertical_min_max                : 2;   //  9: 8
	UINT32                                 : 6;   // 15:10
	UINT32 a_flt_mux                       : 2;   // 17:16
	UINT32 a_e_mux                         : 2;   // 19:18
	UINT32 t_mux                           : 1;   //    20
	UINT32                                 : 3;   // 23:21
	UINT32 a_gen_width                     : 4;   // 27:24
} L9A0_PE1_L_LSR_CTRL_00_T;

typedef struct { // 0x13d4
	UINT32 a_gen_of_y                      : 8;   //  7: 0
	UINT32 a_gen_of_c                      : 8;   // 15: 8
	UINT32 avg_flt_mode                    : 3;   // 18:16
	UINT32 avg_flt_en                      : 1;   //    19
	UINT32                                 : 4;   // 23:20
	UINT32 max_flt_mode                    : 3;   // 26:24
	UINT32 max_flt_en                      : 1;   //    27
} L9A0_PE1_L_LSR_CTRL_01_T;

typedef struct { // 0x13d8
	UINT32 a_exp_gain_ctrl_y0              : 4;   //  3: 0
	UINT32 a_exp2_gain_ctrl_x0             : 4;   //  7: 4
	UINT32 a_exp2_gain_ctrl_y1             : 4;   // 11: 8
	UINT32 a_exp2_gain_ctrl_x1             : 4;   // 15:12
	UINT32 a_avg2_flt_wid                  : 4;   // 19:16
	UINT32 a_avg2_flt_en                   : 1;   //    20
	UINT32                                 : 3;   // 23:21
	UINT32 a_exp_max2_en                   : 1;   //    24
	UINT32                                 : 1;   //    25
	UINT32 y_sum_mode                      : 2;   // 27:26
} L9A0_PE1_L_LSR_CTRL_02_T;

typedef struct { // 0x13dc
	UINT32                                 : 5;   //  4: 0
	UINT32 a_mux_for_edge_gaintable        : 3;   //  7: 5
	UINT32                                 : 9;   // 16: 8
	UINT32 a_mux_for_detail_filter         : 3;   // 19:17
	UINT32                                 : 1;   //    20
	UINT32 a_mux_for_edge_filter           : 3;   // 23:21
	UINT32 a_scaling_flat_filter_          : 4;   // 27:24
	UINT32                                 : 1;   //    28
	UINT32 a_mux_for_flat_filter           : 3;   // 31:29
} L9A0_PE1_L_LSR_CTRL_03_T;

typedef struct { // 0x13e0
	UINT32 dbg_scale                       : 4;   //  3: 0
	UINT32 sum_mux                         : 4;   //  7: 4
	UINT32 enh_en_cc                       : 3;   // 10: 8
	UINT32                                 : 1;   //    11
	UINT32 enh_en_yy                       : 3;   // 14:12
} L9A0_PE1_L_LSR_CTRL_04_T;

typedef struct { // 0x13e4
	UINT32 vmm_param                       : 2;   //  1: 0
	UINT32                                 : 6;   //  7: 2
	UINT32 csft_gain                       : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 th_gain_edge                    : 6;   // 21:16
	UINT32 th_gain_flat                    : 2;   // 23:22
	UINT32 th_manual_th                    : 7;   // 30:24
	UINT32 th_manual_en                    : 1;   //    31
} L9A0_PE1_L_LSR_CTRL_05_T;

typedef struct { // 0x13e8
	UINT32                                 : 8;   //  7: 0
	UINT32 edge_filter_white_gain          : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 edge_filter_black_gain          : 6;   // 21:16
	UINT32                                 : 2;   // 23:22
	UINT32 amean_en                        : 1;   //    24
	UINT32                                 : 1;   //    25
	UINT32 edge_filter_v_tap               : 2;   // 27:26
	UINT32                                 : 2;   // 29:28
	UINT32 edge_c_filter_en                : 1;   //    30
	UINT32 edge_y_filter_en                : 1;   //    31
} L9A0_PE1_L_LSR_CTRL_06_T;

typedef struct { // 0x13ec
	UINT32                                 : 24;  // 23: 0
	UINT32 flat_filter_gain                : 6;   // 29:24
	UINT32                                 : 1;   //    30
	UINT32 flat_filter_en                  : 1;   //    31
} L9A0_PE1_L_LSR_CTRL_07_T;

typedef struct { // 0x13f0
	UINT32 amod_ctrl0_y0                   : 8;   //  7: 0
	UINT32 amod_ctrl0_x0                   : 8;   // 15: 8
	UINT32 amod_ctrl0_y1                   : 8;   // 23:16
	UINT32 amod_ctrl0_x1                   : 8;   // 31:24
} L9A0_PE1_L_LSR_CTRL_08_T;

typedef struct { // 0x13f4
	UINT32 amod_ctrl1_x0                   : 8;   //  7: 0
	UINT32 amod_ctrl1_x1                   : 8;   // 15: 8
	UINT32 y_c_mux_control                 : 3;   // 18:16
	UINT32 chroma_weight                   : 5;   // 23:19
} L9A0_PE1_L_LSR_CTRL_09_T;

typedef struct { // 0x1400
	UINT32 der_v_en                        : 1;   //     0
	UINT32                                 : 1;   //     1
	UINT32 der_gain_mapping                : 1;   //     2
	UINT32 bif_en                          : 1;   //     3
	UINT32 output_mux                      : 4;   //  7: 4
} L9A0_PE1_L_DER_CTRL_0_T;

typedef struct { // 0x1404
	UINT32 gain_th0                        : 8;   //  7: 0
	UINT32 gain_th1                        : 8;   // 15: 8
} L9A0_PE1_L_DER_CTRL_1_T;

typedef struct { // 0x1410
	UINT32 detail_enhancer_enable          : 1;   //     0
	UINT32                                 : 2;   //  2: 1
	UINT32 debug_mode                      : 1;   //     3
	UINT32 debug_image                     : 4;   //  7: 4
	UINT32 gain_w                          : 8;   // 15: 8
	UINT32 gain_b                          : 8;   // 23:16
	UINT32                                 : 3;   // 26:24
	UINT32 detail_measure_for_sca          : 1;   //    27
} L9A0_PE1_L_LSR_DTL_CTRL_00_T;

typedef struct { // 0x1414
	UINT32 pe1_l_lsr_dtl_ctrl_01_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_DTL_CTRL_01_T;

typedef struct { // 0x1418
	UINT32 pe1_l_lsr_dtl_ctrl_02_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_DTL_CTRL_02_T;

typedef struct { // 0x141c
	UINT32                                 : 1;   //     0
	UINT32 um3x3_type                      : 1;   //     1
	UINT32                                 : 6;   //  7: 2
	UINT32 um3x3_gain                      : 8;   // 15: 8
} L9A0_PE1_L_LSR_DTL_CTRL_03_T;

typedef struct { // 0x1420
	UINT32 pe1_l_lsr_dtl_ctrl_04_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_DTL_CTRL_04_T;

typedef struct { // 0x1424
	UINT32 manual_coring_enable            : 1;   //     0
	UINT32 coring_post_filtering_type      : 2;   //  2: 1
	UINT32 coring_post_filtering_enable    : 1;   //     3
	UINT32 coring_mmd_size                 : 2;   //  5: 4
} L9A0_PE1_L_LSR_DTL_CTRL_05_T;

typedef struct { // 0x1428
	UINT32 pe1_l_lsr_dtl_ctrl_06_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_DTL_CTRL_06_T;

typedef struct { // 0x142c
	UINT32 coring_mmd_th_l1                : 8;   //  7: 0
	UINT32 coring_mmd_th_l2                : 8;   // 15: 8
	UINT32 coring_mmd_th_h1                : 8;   // 23:16
	UINT32 coring_mmd_th_h2                : 8;   // 31:24
} L9A0_PE1_L_LSR_DTL_CTRL_07_T;

typedef struct { // 0x1430
	UINT32 post_filterig_enable            : 1;   //     0
	UINT32                                 : 7;   //  7: 1
	UINT32 post_filtering_y_delta          : 4;   // 11: 8
	UINT32 post_filtering_y_th             : 4;   // 15:12
} L9A0_PE1_L_LSR_DTL_CTRL_08_T;

typedef struct { // 0x1434
	UINT32 lgain_en                        : 1;   //     0
	UINT32 lgain_mode                      : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 lgain_apl_type                  : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 lgain_low_th0                   : 8;   // 15: 8
	UINT32 lgain_low_th1                   : 8;   // 23:16
} L9A0_PE1_L_LSR_DTL_CTRL_09_T;

typedef struct { // 0x1438
	UINT32 lgain_high_th0                  : 8;   //  7: 0
	UINT32 lgain_high_th1                  : 8;   // 15: 8
} L9A0_PE1_L_LSR_DTL_CTRL_0A_T;

typedef struct { // 0x143c
	UINT32 gain_balancing_on_off           : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 delta_axis_resolution           : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 ed_x1                           : 8;   // 15: 8
	UINT32 ed_x2                           : 8;   // 23:16
} L9A0_PE1_L_LSR_DTL_CTRL_0B_T;

typedef struct { // 0x1440
	UINT32 ed_y1                           : 8;   //  7: 0
	UINT32 ed_y2                           : 8;   // 15: 8
	UINT32 ed_y3                           : 8;   // 23:16
} L9A0_PE1_L_LSR_DTL_CTRL_0C_T;

typedef struct { // 0x1444
	UINT32 pe1_l_lsr_dtl_ctrl_0d_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_DTL_CTRL_0D_T;

typedef struct { // 0x1450
	UINT32 pe1_l_lsr_dtl_ee_ctrl_00_f      : 32;   // 31: 0
} L9A0_PE1_L_LSR_DTL_EE_CTRL_00_T;

typedef struct { // 0x1454
	UINT32 pe1_l_lsr_dtl_ee_ctrl_01_f      : 32;   // 31: 0
} L9A0_PE1_L_LSR_DTL_EE_CTRL_01_T;

typedef struct { // 0x1458
	UINT32 enable                          : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 filter_sel                      : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 lap_gain                        : 8;   // 15: 8
	UINT32 sobel_gx_gain                   : 8;   // 23:16
	UINT32 sobel_manual_gain               : 8;   // 31:24
} L9A0_PE1_L_LSR_DTL_EE_CTRL_02_T;

typedef struct { // 0x145c
	UINT32 white_gain                      : 7;   //  6: 0
	UINT32                                 : 1;   //     7
	UINT32 black_gain                      : 7;   // 14: 8
	UINT32                                 : 1;   //    15
	UINT32 h_gain                          : 8;   // 23:16
	UINT32 v_gain                          : 8;   // 31:24
} L9A0_PE1_L_LSR_DTL_EE_CTRL_03_T;

typedef struct { // 0x1460
	UINT32 gain_balancing_on_off           : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 delta_axis_resolution           : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 ed_x1                           : 8;   // 15: 8
	UINT32 ed_x2                           : 8;   // 23:16
} L9A0_PE1_L_LSR_DTL_EE_CTRL_04_T;

typedef struct { // 0x1464
	UINT32 ed_y1                           : 8;   //  7: 0
	UINT32 ed_y2                           : 8;   // 15: 8
	UINT32 ed_y3                           : 8;   // 23:16
} L9A0_PE1_L_LSR_DTL_EE_CTRL_05_T;

typedef struct { // 0x1470
	UINT32 gt_detail_mode                  : 1;   //     0
	UINT32 gt_edge_mode                    : 1;   //     1
	UINT32 gt_flat_mode                    : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 gt_detail_manual_gain           : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 gt_edge_manual_gain             : 6;   // 21:16
	UINT32                                 : 2;   // 23:22
	UINT32 gt_flat_manual_gain             : 6;   // 29:24
} L9A0_PE1_L_LSR_GT_CTRL_00_T;

typedef struct { // 0x1474
	UINT32 gt_interpolation_type           : 2;   //  1: 0
	UINT32                                 : 6;   //  7: 2
	UINT32 interpol_x0                     : 8;   // 15: 8
	UINT32 interpol_x1                     : 8;   // 23:16
	UINT32 interpol_x2                     : 8;   // 31:24
} L9A0_PE1_L_LSR_GT_CTRL_01_T;

typedef struct { // 0x1478
	UINT32 th1                             : 8;   //  7: 0
	UINT32 th2                             : 8;   // 15: 8
	UINT32 th3                             : 8;   // 23:16
	UINT32 pcm_th                          : 8;   // 31:24
} L9A0_PE1_L_LSR_GT_CTRL_02_T;

typedef struct { // 0x147c
	UINT32 enable_manual_sqa_measure       : 1;   //     0
	UINT32 auto_sqa_measure_type           : 1;   //     1
	UINT32 hdm_pcm_selection               : 1;   //     2
	UINT32 sqm_bit_resolution              : 1;   //     3
	UINT32                                 : 4;   //  7: 4
	UINT32 manual_sqa_value                : 8;   // 15: 8
	UINT32 hd_measure                      : 8;   // 23:16
	UINT32 pc_measure                      : 8;   // 31:24
} L9A0_PE1_L_LSR_GT_CTRL_03_T;

typedef struct { // 0x1480
	UINT32 source_quality_measure          : 8;   //  7: 0
} L9A0_PE1_L_LSR_GT_CTRL_04_T;

typedef struct { // 0x1484
	UINT32 index                           : 6;   //  5: 0
	UINT32                                 : 2;   //  7: 6
	UINT32 edf                             : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 auto_increment                  : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 gt_enable                       : 1;   //    15
} L9A0_PE1_L_LSR_GT_IA_CTRL_T;

typedef struct { // 0x1488
	UINT32 gt_wdata0                       : 6;   //  5: 0
	UINT32                                 : 2;   //  7: 6
	UINT32 gt_wdata1                       : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 gt_wdata2                       : 6;   // 21:16
} L9A0_PE1_L_LSR_GT_IA_DATA_T;

typedef struct { // 0x14a0
	UINT32                                 : 8;   //  7: 0
	UINT32 sca_gain_display                : 4;   // 11: 8
} L9A0_PE1_L_LSR_SCA_CTRL_00_T;

typedef struct { // 0x14a4
	UINT32 sca_en                          : 1;   //     0
	UINT32                                 : 7;   //  7: 1
	UINT32 sca_gain                        : 6;   // 13: 8
} L9A0_PE1_L_LSR_SCA_CTRL_01_T;

typedef struct { // 0x14a8
	UINT32 pe1_l_lsr_sca_ctrl_02_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_SCA_CTRL_02_T;

typedef struct { // 0x14ac
	UINT32 pe1_l_lsr_sca_ctrl_03_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_SCA_CTRL_03_T;

typedef struct { // 0x14b0
	UINT32                                 : 16;  // 15: 0
	UINT32 enable_sca_to_flat_filter       : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 gain_of_sca_to_flat_filter      : 4;   // 23:20
} L9A0_PE1_L_LSR_SCA_CTRL_04_T;

typedef struct { // 0x14b4
	UINT32 pe1_l_lsr_sca_ctrl_05_f         : 32;   // 31: 0
} L9A0_PE1_L_LSR_SCA_CTRL_05_T;

typedef struct { // 0x14b8
	UINT32 enable_debug_mode               : 1;   //     0
	UINT32 show_sqm1                       : 1;   //     1
	UINT32 show_cr_info                    : 1;   //     2
	UINT32 debug_bar_gain_position         : 1;   //     3
	UINT32 measure_display_gain            : 3;   //  6: 4
	UINT32 show_tpg                        : 1;   //     7
	UINT32 show_hdm_pcm_area               : 1;   //     8
	UINT32 show_sqm2                       : 1;   //     9
	UINT32 sqm2_debug_image                : 4;   // 13:10
	UINT32                                 : 1;   //    14
	UINT32 show_bbd                        : 2;   // 16:15
	UINT32 bbd_line_width                  : 3;   // 19:17
	UINT32 show_apl                        : 1;   //    20
} L9A0_PE1_L_LSR_SCA_CTRL_06_T;

typedef struct { // 0x14bc
	UINT32                                 : 4;   //  3: 0
	UINT32 y_grad_gain                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 cb_grad_gain                    : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 cr_grad_gain                    : 2;   // 13:12
} L9A0_PE1_L_LSR_SCA_CTRL_07_T;

typedef struct { // 0x14c0
	UINT32 y_range_min                     : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 y_range_max                     : 10;  // 25:16
} L9A0_PE1_L_LSR_SCA_CTRL_08_T;

typedef struct { // 0x14c4
	UINT32 cb_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cb_range_max                    : 10;  // 25:16
} L9A0_PE1_L_LSR_SCA_CTRL_09_T;

typedef struct { // 0x14c8
	UINT32 cr_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cr_range_max                    : 10;  // 25:16
} L9A0_PE1_L_LSR_SCA_CTRL_0A_T;

typedef struct { // 0x14cc
	UINT32 gain_type                       : 2;   //  1: 0
	UINT32 color_region                    : 3;   //  4: 2
	UINT32                                 : 7;   // 11: 5
	UINT32 auto_increment                  : 1;   //    12
} L9A0_PE1_L_LSR_SCA_IA_CTRL_T;

typedef struct { // 0x14d0
	UINT32 x1                              : 8;   //  7: 0
	UINT32 x2                              : 8;   // 15: 8
	UINT32 g1                              : 6;   // 21:16
	UINT32                                 : 2;   // 23:22
	UINT32 g2                              : 6;   // 29:24
} L9A0_PE1_L_LSR_SCA_IA_DATA_T;

typedef struct { // 0x14e0
	UINT32 hif_crg_lsr_address             : 4;   //  3: 0
	UINT32                                 : 8;   // 11: 4
	UINT32 hif_crg_lsr_ai                  : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_crg_lsr_wr                  : 1;   //    15
} L9A0_PE1_L_LSR_CRG_IA_CTRL_T;

typedef struct { // 0x14e4
	UINT32 value                           : 8;   //  7: 0
	UINT32                                 : 2;   //  9: 8
	UINT32 saturation                      : 7;   // 16:10
	UINT32                                 : 3;   // 19:17
	UINT32 hue                             : 10;  // 29:20
} L9A0_PE1_L_LSR_CRG_IA_DATA_T;

typedef struct { // 0x14f0
	UINT32 edge_enhance_enable             : 1;   //     0
	UINT32 edge_enhance_mode               : 1;   //     1
	UINT32 lm_mode                         : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 lti_level                       : 4;   // 11: 8
	UINT32 edge_operator_selection         : 2;   // 13:12
} L9A0_PE1_L_SHP_EDGE_CTRL_00_T;

typedef struct { // 0x14f4
	UINT32 white_gain                      : 7;   //  6: 0
	UINT32                                 : 1;   //     7
	UINT32 black_gain                      : 7;   // 14: 8
	UINT32                                 : 1;   //    15
	UINT32 horizontal_gain                 : 8;   // 23:16
	UINT32 vertical_gain                   : 8;   // 31:24
} L9A0_PE1_L_SHP_EDGE_CTRL_01_T;

typedef struct { // 0x14f8
	UINT32 sobel_weight                    : 8;   //  7: 0
	UINT32 laplacian_weight                : 8;   // 15: 8
	UINT32 sobel_manual_mode_en            : 1;   //    16
	UINT32                                 : 7;   // 23:17
	UINT32 sobel_manual_gain               : 8;   // 31:24
} L9A0_PE1_L_SHP_EDGE_CTRL_02_T;

typedef struct { // 0x14fc
	UINT32 lum_low_th1                     : 8;   //  7: 0
	UINT32 lum_low_th2                     : 8;   // 15: 8
	UINT32 lum_high_th1                    : 8;   // 23:16
	UINT32 lum_high_th2                    : 8;   // 31:24
} L9A0_PE1_L_SHP_EDGE_CTRL_03_T;

typedef struct { // 0x1500
	UINT32 laplacian_offset                : 8;   //  7: 0
	UINT32 debug_selection                 : 3;   // 10: 8
	UINT32 debug_enable                    : 1;   //    11
	UINT32 gx_weight_manual_mode           : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 gx_weight_manual_gain           : 8;   // 23:16
	UINT32 par_filter_sel                  : 3;   // 26:24
	UINT32                                 : 1;   //    27
	UINT32 par_out_sel                     : 2;   // 29:28
} L9A0_PE1_L_SHP_EDGE_CTRL_04_T;

typedef struct { // 0x1508
	UINT32 coring_enable                   : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 coring_mmd_h                    : 2;   //  5: 4
	UINT32 coring_mmd_v                    : 2;   //  7: 6
	UINT32 coring_low_th_resol             : 1;   //     8
	UINT32                                 : 7;   // 15: 9
	UINT32 coring_low_th1                  : 8;   // 23:16
	UINT32 coring_low_th2                  : 8;   // 31:24
} L9A0_PE1_L_SHP_EDGE_CTRL_05_T;

typedef struct { // 0x150c
	UINT32 pe1_l_shp_edge_ctrl_06_f        : 32;   // 31: 0
} L9A0_PE1_L_SHP_EDGE_CTRL_06_T;

typedef struct { // 0x1510
	UINT32 pe1_l_shp_edge_ctrl_07_f        : 32;   // 31: 0
} L9A0_PE1_L_SHP_EDGE_CTRL_07_T;

typedef struct { // 0x1514
	UINT32 pe1_l_shp_edge_ctrl_08_f        : 32;   // 31: 0
} L9A0_PE1_L_SHP_EDGE_CTRL_08_T;

typedef struct { // 0x1520
	UINT32 cti_en                          : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 tap_size                        : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 cti_gain                        : 8;   // 15: 8
} L9A0_PE1_L_CTI_CTRL_00_T;

typedef struct { // 0x1524
	UINT32 pe1_l_cti_ctrl_01_f             : 32;   // 31: 0
} L9A0_PE1_L_CTI_CTRL_01_T;

typedef struct { // 0x1528
	UINT32 ycm_en0                         : 1;   //     0
	UINT32 ycm_en1                         : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 ycm_band_sel                    : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 ycm_diff_th                     : 8;   // 15: 8
	UINT32 ycm_y_gain                      : 4;   // 19:16
	UINT32 ycm_c_gain                      : 4;   // 23:20
} L9A0_PE1_L_CTI_CTRL_02_T;

typedef struct { // 0x1530
	UINT32 enable                          : 1;   //     0
	UINT32 coring_en                       : 1;   //     1
	UINT32 coring_diff_sel                 : 1;   //     2
	UINT32 filter_tap                      : 1;   //     3
	UINT32 avg_type                        : 1;   //     4
	UINT32 coring_mmd_sel                  : 2;   //  6: 5
	UINT32                                 : 1;   //     7
	UINT32 gain_w                          : 8;   // 15: 8
	UINT32 gain_b                          : 8;   // 23:16
} L9A0_PE1_L_SHP_UM_CTRL_0_T;

typedef struct { // 0x1534
	UINT32 coring_th_low1                  : 8;   //  7: 0
	UINT32 coring_th_low2                  : 8;   // 15: 8
	UINT32 coring_th_high1                 : 8;   // 23:16
	UINT32 coring_th_high2                 : 8;   // 31:24
} L9A0_PE1_L_SHP_UM_CTRL_1_T;

typedef struct { // 0x1538
	UINT32 lgain_en                        : 1;   //     0
	UINT32 lgain_mode                      : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 lgain_apl_type                  : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 lgain_low_th0                   : 8;   // 15: 8
	UINT32 lgain_low_th1                   : 8;   // 23:16
} L9A0_PE1_L_SHP_UM_CTRL_2_T;

typedef struct { // 0x153c
	UINT32 lgain_high_th0                  : 8;   //  7: 0
	UINT32 lgain_high_th1                  : 8;   // 15: 8
	UINT32 sca_en                          : 1;   //    16
	UINT32                                 : 7;   // 23:17
	UINT32 sca_gain                        : 6;   // 29:24
} L9A0_PE1_L_SHP_UM_CTRL_3_T;

typedef struct { // 0x1540
	UINT32                                 : 4;   //  3: 0
	UINT32 y_grad_gain                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 cb_grad_gain                    : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 cr_grad_gain                    : 2;   // 13:12
} L9A0_PE1_L_SHP_UM_CTRL_4_T;

typedef struct { // 0x1544
	UINT32 y_range_min                     : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 y_range_max                     : 10;  // 25:16
} L9A0_PE1_L_SHP_UM_CTRL_5_T;

typedef struct { // 0x1548
	UINT32 cb_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cb_range_max                    : 10;  // 25:16
} L9A0_PE1_L_SHP_UM_CTRL_6_T;

typedef struct { // 0x154c
	UINT32 cr_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cr_range_max                    : 10;  // 25:16
} L9A0_PE1_L_SHP_UM_CTRL_7_T;

typedef struct { // 0x1550
	UINT32 enable                          : 1;   //     0
	UINT32 coring_en                       : 1;   //     1
	UINT32                                 : 6;   //  7: 2
	UINT32 gain                            : 8;   // 15: 8
	UINT32 coring_min                      : 8;   // 23:16
	UINT32 coring_max                      : 8;   // 31:24
} L9A0_PE1_L_SHP_BLUR_CTRL_T;

typedef struct { // 0x1560
	UINT32 dbg_scale                       : 4;   //  3: 0
	UINT32 sum_mux                         : 4;   //  7: 4
	UINT32 enh_en_cc                       : 3;   // 10: 8
	UINT32                                 : 1;   //    11
	UINT32 enh_en_yy                       : 3;   // 14:12
} L9A0_PE1_L_SHP_SUM_CTRL_T;

typedef struct { // 0x1570
	UINT32 pe1_l_ti_ctrl_0_f               : 32;   // 31: 0
} L9A0_PE1_L_TI_CTRL_0_T;

typedef struct { // 0x1574
	UINT32 enable                          : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 coring_step                     : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 coring_th                       : 8;   // 15: 8
	UINT32 ti_gain                         : 8;   // 23:16
} L9A0_PE1_L_TI_CTRL_1_T;

typedef struct { // 0x1578
	UINT32 enable                          : 1;   //     0
	UINT32 debug_coring                    : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 coring_step                     : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 coring_th                       : 8;   // 15: 8
	UINT32 y_gain                          : 8;   // 23:16
	UINT32 c_gain                          : 8;   // 31:24
} L9A0_PE1_L_TI_CTRL_2_T;

typedef struct { // 0x157c
	UINT32 enable                          : 1;   //     0
	UINT32 debug_coring                    : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 coring_step                     : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 coring_th                       : 8;   // 15: 8
	UINT32 y_gain                          : 8;   // 23:16
	UINT32 c_gain                          : 8;   // 31:24
} L9A0_PE1_L_TI_CTRL_3_T;

typedef struct { // 0x1580
	UINT32 gain0_en                        : 1;   //     0
	UINT32 gain1_en                        : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 output_mux                      : 2;   //  5: 4
	UINT32                                 : 10;  // 15: 6
	UINT32 gain0_th0                       : 8;   // 23:16
	UINT32 gain0_th1                       : 8;   // 31:24
} L9A0_PE1_L_TI_CTRL_4_T;

typedef struct { // 0x1584
	UINT32 gain1_div_mode                  : 2;   //  1: 0
} L9A0_PE1_L_TI_CTRL_5_T;

typedef struct { // 0x1590
	UINT32 edf_en                          : 1;   //     0
	UINT32 hv_filter_en                    : 1;   //     1
	UINT32 g0_feature_norm_en              : 1;   //     2
	UINT32 g0_f2g_mapping_en               : 1;   //     3
	UINT32 line_variation_mode             : 1;   //     4
	UINT32 l_type_protection               : 1;   //     5
	UINT32 center_blur_en                  : 1;   //     6
	UINT32 direction_type_mode             : 1;   //     7
	UINT32 count_diff_th                   : 5;   // 12: 8
	UINT32                                 : 3;   // 15:13
	UINT32 output_mux                      : 3;   // 18:16
	UINT32                                 : 3;   // 21:19
	UINT32 n_avg_mode                      : 1;   //    22
	UINT32                                 : 1;   //    23
	UINT32 line_variation_diff             : 8;   // 31:24
} L9A0_PE1_L_DJ_CTRL_00_T;

typedef struct { // 0x1594
	UINT32 level_th                        : 8;   //  7: 0
	UINT32 protect_th                      : 8;   // 15: 8
	UINT32 n_avg_gain                      : 8;   // 23:16
} L9A0_PE1_L_DJ_CTRL_01_T;

typedef struct { // 0x1598
	UINT32 edf_count_min                   : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 edf_count_max                   : 5;   // 12: 8
} L9A0_PE1_L_DJ_CTRL_02_T;

typedef struct { // 0x159c
	UINT32 dj_h_count_min                  : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 dj_h_count_max                  : 5;   // 12: 8
	UINT32                                 : 3;   // 15:13
	UINT32 dj_v_count_min                  : 5;   // 20:16
	UINT32                                 : 3;   // 23:21
	UINT32 dj_v_count_max                  : 5;   // 28:24
} L9A0_PE1_L_DJ_CTRL_03_T;

typedef struct { // 0x15b0
	UINT32 enable                          : 1;   //     0
	UINT32 graycolor_enable                : 1;   //     1
	UINT32 color_only_enable               : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 center_position                 : 8;   // 15: 8
	UINT32 contrast                        : 8;   // 23:16
	UINT32 brightness                      : 8;   // 31:24
} L9A0_PE1_L_VSP_CTRL_00_T;

typedef struct { // 0x15c0
	UINT32 icsc_en                         : 1;   //     0
	UINT32 degamma_en                      : 1;   //     1
	UINT32 pcc_en                          : 1;   //     2
	UINT32 gamma                           : 1;   //     3
	UINT32 scaler_en                       : 1;   //     4
	UINT32 hsv_hsl_selection               : 1;   //     5
	UINT32 s_adpative_scaler               : 1;   //     6
} L9A0_PE1_L_XVY_CTRL_00_T;

typedef struct { // 0x15c4
	UINT32 r_csc_coef1                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef0                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_01_T;

typedef struct { // 0x15c8
	UINT32 r_csc_coef3                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef2                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_02_T;

typedef struct { // 0x15cc
	UINT32 r_csc_coef5                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef4                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_03_T;

typedef struct { // 0x15d0
	UINT32 r_csc_coef7                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef6                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_04_T;

typedef struct { // 0x15d4
	UINT32 r_csc_ofst0                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 r_csc_coef8                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_05_T;

typedef struct { // 0x15d8
	UINT32 r_csc_ofst2                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 r_csc_ofst1                     : 11;  // 26:16
} L9A0_PE1_L_XVY_CTRL_06_T;

typedef struct { // 0x15dc
	UINT32 r_csc_ofst4                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 r_csc_ofst3                     : 11;  // 26:16
} L9A0_PE1_L_XVY_CTRL_07_T;

typedef struct { // 0x15e0
	UINT32 r_pcc_coef0                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_ofst5                     : 11;  // 26:16
} L9A0_PE1_L_XVY_CTRL_08_T;

typedef struct { // 0x15e4
	UINT32 r_pcc_coef2                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef1                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_09_T;

typedef struct { // 0x15e8
	UINT32 r_pcc_coef4                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef3                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_0A_T;

typedef struct { // 0x15ec
	UINT32 r_pcc_coef6                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef5                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_0B_T;

typedef struct { // 0x15f0
	UINT32 r_pcc_coef8                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef7                     : 15;  // 30:16
} L9A0_PE1_L_XVY_CTRL_0C_T;

typedef struct { // 0x15f4
	UINT32 scaler                          : 8;   //  7: 0
} L9A0_PE1_L_XVY_CTRL_0D_T;

typedef struct { // 0x1600
	UINT32                                 : 2;   //  1: 0
	UINT32 select_hsv                      : 1;   //     2
	UINT32 select_rgb                      : 1;   //     3
	UINT32                                 : 1;   //     4
	UINT32 vsp_sel                         : 1;   //     5
	UINT32 global_apl_sel                  : 1;   //     6
	UINT32 cen_bypass                      : 1;   //     7
	UINT32 cen_debug_mode                  : 1;   //     8
	UINT32 debugging_mode_core             : 1;   //     9
	UINT32 pe1_1st_core_gain_disable       : 1;   //    10
	UINT32 pe1_2nd_core_gain_disable       : 1;   //    11
	UINT32 v_scaler_en                     : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 demo_mode                       : 8;   // 23:16
	UINT32                                 : 7;   // 30:24
	UINT32 win_control_mode                : 1;   //    31
} L9A0_PE1_L_CEN_CTRL_00_T;

typedef struct { // 0x1604
	UINT32 show_color_region0              : 8;   //  7: 0
	UINT32 show_color_region1              : 8;   // 15: 8
	UINT32 color_region_en0                : 8;   // 23:16
	UINT32 color_region_en1                : 8;   // 31:24
} L9A0_PE1_L_CEN_CTRL_01_T;

typedef struct { // 0x1608
	UINT32 ihsv_sgain                      : 8;   //  7: 0
	UINT32 ihsv_vgain                      : 8;   // 15: 8
} L9A0_PE1_L_CEN_CTRL_02_T;

typedef struct { // 0x160c
	UINT32 ihsv_hoffset                    : 8;   //  7: 0
	UINT32 ihsv_soffset                    : 8;   // 15: 8
	UINT32 ihsv_voffset                    : 8;   // 23:16
} L9A0_PE1_L_CEN_CTRL_03_T;

typedef struct { // 0x1610
	UINT32 den_ctrl0                       : 8;   //  7: 0
	UINT32 den_apl_limit_high              : 8;   // 15: 8
	UINT32 den_gain                        : 8;   // 23:16
	UINT32 den_coring                      : 8;   // 31:24
} L9A0_PE1_L_CEN_CTRL_04_T;

typedef struct { // 0x1614
	UINT32 hif_cen_address                 : 8;   //  7: 0
	UINT32 hif_cen_ai_sel                  : 3;   // 10: 8
	UINT32                                 : 1;   //    11
	UINT32 hif_cen_ai                      : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_cen_enable                  : 1;   //    15
} L9A0_PE1_L_CEN_IA_CTRL_T;

typedef struct { // 0x1618
	UINT32 hif_cen_y_wdata                 : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 hif_cen_x_wdata                 : 10;  // 25:16
} L9A0_PE1_L_CEN_IA_DATA_T;

typedef struct { // 0x1630
	UINT32 enable                          : 1;   //     0
	UINT32 adjust_en                       : 1;   //     1
	UINT32 protection_en                   : 1;   //     2
	UINT32 adjust_en2                      : 1;   //     3
	UINT32 r_hist_data_sel                 : 1;   //     4
	UINT32 l_hist_data_sel                 : 1;   //     5
	UINT32 r_proc_data_sel                 : 1;   //     6
	UINT32 l_proc_data_sel                 : 1;   //     7
	UINT32 ff_mode_en                      : 1;   //     8
	UINT32 ff_mode_parity                  : 1;   //     9
	UINT32                                 : 2;   // 11:10
	UINT32 r_out_data_sel                  : 1;   //    12
	UINT32 l_out_data_sel                  : 1;   //    13
	UINT32                                 : 2;   // 15:14
	UINT32 lrcr_gain                       : 4;   // 19:16
} L9A0_PE1_L_LRCR_CTRL_00_T;

typedef struct { // 0x1634
	UINT32 th_max_hist                     : 8;   //  7: 0
	UINT32 th_valid_bins                   : 8;   // 15: 8
} L9A0_PE1_L_LRCR_CTRL_01_T;

typedef struct { // 0x1638
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 2;   // 13:12
	UINT32 hist_l_window_h_bbd             : 1;   //    14
	UINT32 hist_l_window_h_en              : 1;   //    15
	UINT32 y0                              : 12;  // 27:16
	UINT32                                 : 2;   // 29:28
	UINT32 hist_l_window_v_bbd             : 1;   //    30
	UINT32 hist_l_window_v_en              : 1;   //    31
} L9A0_PE1_L_LRCR_CTRL_02_T;

typedef struct { // 0x163c
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_L_LRCR_CTRL_03_T;

typedef struct { // 0x1640
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 2;   // 13:12
	UINT32 hist_r_window_h_bbd             : 1;   //    14
	UINT32 hist_r_window_h_en              : 1;   //    15
	UINT32 y0                              : 12;  // 27:16
	UINT32                                 : 2;   // 29:28
	UINT32 hist_r_window_v_bbd             : 1;   //    30
	UINT32 hist_r_window_v_en              : 1;   //    31
} L9A0_PE1_L_LRCR_CTRL_04_T;

typedef struct { // 0x1644
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_L_LRCR_CTRL_05_T;

typedef struct { // 0x1648
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 2;   // 13:12
	UINT32 active_window_h_bbd             : 1;   //    14
	UINT32 active_window_h_en              : 1;   //    15
	UINT32 y0                              : 12;  // 27:16
	UINT32                                 : 2;   // 29:28
	UINT32 active_window_v_bbd             : 1;   //    30
	UINT32 active_window_v_en              : 1;   //    31
} L9A0_PE1_L_LRCR_CTRL_06_T;

typedef struct { // 0x164c
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_L_LRCR_CTRL_07_T;

typedef struct { // 0x1650
	UINT32 max_hist                        : 8;   //  7: 0
	UINT32 n_valid_bins                    : 8;   // 15: 8
	UINT32 cdf_x1                          : 8;   // 23:16
	UINT32 cdf_x0                          : 8;   // 31:24
} L9A0_PE1_L_LRCR_STAT_00_T;

typedef struct { // 0x1654
	UINT32 max_hist                        : 8;   //  7: 0
	UINT32 n_valid_bins                    : 8;   // 15: 8
	UINT32 cdf_x1                          : 8;   // 23:16
	UINT32 cdf_x0                          : 8;   // 31:24
} L9A0_PE1_L_LRCR_STAT_01_T;

typedef struct { // 0x1658
	UINT32 max_hist                        : 8;   //  7: 0
	UINT32 n_valid_bins                    : 8;   // 15: 8
	UINT32 cdf_x1                          : 8;   // 23:16
	UINT32 cdf_x0                          : 8;   // 31:24
} L9A0_PE1_L_LRCR_STAT_02_T;

typedef struct { // 0x1670
	UINT32 dynamic_contrast_en             : 1;   //     0
	UINT32 hist_bin_mode                   : 2;   //  2: 1
	UINT32 hist_clear                      : 1;   //     3
	UINT32 hist_bin_bitwidth_mode          : 2;   //  5: 4
	UINT32 window_mode_en                  : 1;   //     6
	UINT32 window_acquire                  : 1;   //     7
	UINT32 color_region0_sel               : 1;   //     8
	UINT32 color_region1_sel               : 1;   //     9
	UINT32 color_region2_sel               : 1;   //    10
	UINT32 color_region3_sel               : 1;   //    11
	UINT32 color_region4_sel               : 1;   //    12
	UINT32 color_region5_sel               : 1;   //    13
	UINT32 color_region6_sel               : 1;   //    14
	UINT32 color_region7_sel               : 1;   //    15
	UINT32 color_region8_sel               : 1;   //    16
	UINT32 color_region9_sel               : 1;   //    17
	UINT32 color_region10_sel              : 1;   //    18
	UINT32 color_region11_sel              : 1;   //    19
	UINT32 color_region12_sel              : 1;   //    20
	UINT32 color_region13_sel              : 1;   //    21
	UINT32 color_region14_sel              : 1;   //    22
	UINT32 color_region15_sel              : 1;   //    23
	UINT32 dce_domain_sel                  : 1;   //    24
	UINT32 win_selection                   : 1;   //    25
} L9A0_PE1_L_DCE_CTRL_00_T;

typedef struct { // 0x1674
	UINT32 hist_bin_min_position           : 8;   //  7: 0
	UINT32 hist_bin_max_position           : 8;   // 15: 8
	UINT32 color_region_gain               : 8;   // 23:16
} L9A0_PE1_L_DCE_CTRL_01_T;

typedef struct { // 0x1678
	UINT32 color_region_en                 : 1;   //     0
	UINT32 color_debug_en                  : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 y_grad_gain                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 cb_grad_gain                    : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 cr_grad_gain                    : 2;   // 13:12
} L9A0_PE1_L_DCE_CTRL_02_T;

typedef struct { // 0x167c
	UINT32 y_range_min                     : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 y_range_max                     : 10;  // 25:16
} L9A0_PE1_L_DCE_CTRL_03_T;

typedef struct { // 0x1680
	UINT32 cb_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cb_range_max                    : 10;  // 25:16
} L9A0_PE1_L_DCE_CTRL_04_T;

typedef struct { // 0x1684
	UINT32 cr_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cr_range_max                    : 10;  // 25:16
} L9A0_PE1_L_DCE_CTRL_05_T;

typedef struct { // 0x1688
	UINT32 hif_dyc_address                 : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 hif_dce_load                    : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 hif_dce_ai                      : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_dce_enable                  : 1;   //    15
} L9A0_PE1_L_DCE_IA_CTRL_T;

typedef struct { // 0x168c
	UINT32 hif_dyc_wdata_y                 : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 hif_dyc_wdata_x                 : 10;  // 25:16
} L9A0_PE1_L_DCE_IA_DATA_T;

typedef struct { // 0x1690
	UINT32 hif_dyc_wdata_y_32nd            : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 hif_dyc_wdata_x_32nd            : 10;  // 25:16
} L9A0_PE1_L_DCE_CTRL_08_T;

typedef struct { // 0x16a0
	UINT32 hif_hist_address                : 6;   //  5: 0
	UINT32                                 : 6;   // 11: 6
	UINT32 hif_hist_ai                     : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_hist_enable                 : 1;   //    15
	UINT32 hif_status_address              : 3;   // 18:16
	UINT32                                 : 9;   // 27:19
	UINT32 hif_status_ai                   : 1;   //    28
	UINT32 hif_mask                        : 1;   //    29
} L9A0_PE1_L_DCE_HIST_IA_CTRL_T;

typedef struct { // 0x16a4
	UINT32 pe1_l_dce_hist_ia_data1_f       : 32;   // 31: 0
} L9A0_PE1_L_DCE_HIST_IA_DATA1_T;

typedef struct { // 0x16a8
	UINT32 pe1_l_dce_hsit_ia_data2_f       : 32;   // 31: 0
} L9A0_PE1_L_DCE_HSIT_IA_DATA2_T;

typedef struct { // 0x16c0
	UINT32 wb_en                           : 1;   //     0
	UINT32 apl_gain_bypass                 : 1;   //     1
	UINT32 wb_user_ctrl_bypass             : 1;   //     2
	UINT32 max_to_one_bypass               : 1;   //     3
	UINT32                                 : 3;   //  6: 4
	UINT32 use_apl_than_ctemp              : 1;   //     7
	UINT32 user_ctemp                      : 8;   // 15: 8
	UINT32 ire_csc_offset                  : 10;  // 25:16
	UINT32                                 : 4;   // 29:26
	UINT32 degamma_en                      : 1;   //    30
	UINT32 gamma_en                        : 1;   //    31
} L9A0_PE1_L_WB_CTRL_00_T;

typedef struct { // 0x16c4
	UINT32 ire_csc_g_coeff                 : 10;  //  9: 0
	UINT32 ire_csc_b_coeff                 : 10;  // 19:10
	UINT32 ire_csc_r_coeff                 : 10;  // 29:20
} L9A0_PE1_L_WB_CTRL_01_T;

typedef struct { // 0x16c8
	UINT32 user_ctrl_g_gain                : 8;   //  7: 0
	UINT32 user_ctrl_b_gain                : 8;   // 15: 8
	UINT32 user_ctrl_r_gain                : 8;   // 23:16
} L9A0_PE1_L_WB_CTRL_02_T;

typedef struct { // 0x16cc
	UINT32 user_ctrl_g_offset              : 8;   //  7: 0
	UINT32 user_ctrl_b_offset              : 8;   // 15: 8
	UINT32 user_ctrl_r_offset              : 8;   // 23:16
} L9A0_PE1_L_WB_CTRL_03_T;

typedef struct { // 0x16f0
	UINT32 pxl_rep_xpos                    : 11;  // 10: 0
	UINT32                                 : 1;   //    11
	UINT32 lut_wmask_g                     : 1;   //    12
	UINT32 lut_wmask_b                     : 1;   //    13
	UINT32 lut_wmask_r                     : 1;   //    14
	UINT32                                 : 1;   //    15
	UINT32 pxl_rep_ypos                    : 11;  // 26:16
	UINT32 pxl_rep_area                    : 1;   //    27
	UINT32 pxl_rep_disable_g               : 1;   //    28
	UINT32 pxl_rep_disable_b               : 1;   //    29
	UINT32 pxl_rep_disable_r               : 1;   //    30
	UINT32 pxl_rep_enable                  : 1;   //    31
} L9A0_PE1_L_GMC_CTRL_00_T;

typedef struct { // 0x16f4
	UINT32 pxl_rep_width                   : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 pxl_rep_height                  : 11;  // 26:16
} L9A0_PE1_L_GMC_CTRL_01_T;

typedef struct { // 0x16f8
	UINT32 pxl_rep_value_g                 : 10;  //  9: 0
	UINT32 pxl_rep_value_b                 : 10;  // 19:10
	UINT32 pxl_rep_value_r                 : 10;  // 29:20
	UINT32 gmc_mode                        : 2;   // 31:30
} L9A0_PE1_L_GMC_CTRL_02_T;

typedef struct { // 0x16fc
	UINT32 capture_addr                    : 10;  //  9: 0
	UINT32                                 : 2;   // 11:10
	UINT32 capture_ai                      : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 capture_num                     : 11;  // 26:16
} L9A0_PE1_L_GMC_IA_CTRL_T;

typedef struct { // 0x1700
	UINT32 lut_data_g                      : 10;  //  9: 0
	UINT32 lut_data_b                      : 10;  // 19:10
	UINT32 lut_data_r                      : 10;  // 29:20
	UINT32 capture_stat_started            : 1;   //    30
	UINT32 capture_stat_ended              : 1;   //    31
} L9A0_PE1_L_GMC_IA_DATA_T;

typedef struct { // 0x1704
	UINT32 dither_en                       : 1;   //     0
	UINT32 dcountour_en                    : 1;   //     1
	UINT32                                 : 1;   //     2
	UINT32 bit_mode_8                      : 1;   //     3
	UINT32                                 : 4;   //  7: 4
	UINT32 decontour_gain_r                : 8;   // 15: 8
	UINT32 decontour_gain_g                : 8;   // 23:16
	UINT32 decontour_gain_b                : 8;   // 31:24
} L9A0_PE1_L_GMC_CTRL_03_T;

typedef struct { // 0x1720
	UINT32 outmux_debugmap_                : 4;   //  3: 0
	UINT32 iir                             : 4;   //  7: 4
	UINT32 i_score                         : 8;   // 15: 8
	UINT32 v_score                         : 8;   // 23:16
	UINT32 l_score                         : 8;   // 31:24
} L9A0_PE1_L_SQM_CTRL_0_T;

typedef struct { // 0x1724
	UINT32 v_limit                         : 8;   //  7: 0
	UINT32 l_limit                         : 8;   // 15: 8
	UINT32 score_threshold                 : 8;   // 23:16
	UINT32 flat_threshold                  : 8;   // 31:24
} L9A0_PE1_L_SQM_CTRL_1_T;

typedef struct { // 0x1728
	UINT32 win_x0                          : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_y0                          : 11;  // 26:16
} L9A0_PE1_L_SQM_CTRL_2_T;

typedef struct { // 0x172c
	UINT32 win_x1                          : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_y1                          : 11;  // 26:16
} L9A0_PE1_L_SQM_CTRL_3_T;

typedef struct { // 0x1730
	UINT32 charcter_delta_limit            : 8;   //  7: 0
	UINT32 boundary_width                  : 8;   // 15: 8
	UINT32 video_height                    : 8;   // 23:16
} L9A0_PE1_L_SQM_CTRL_4_T;

typedef struct { // 0x1734
	UINT32 pc_threshold                    : 8;   //  7: 0
	UINT32 pc_delta_limit                  : 8;   // 15: 8
	UINT32 pc_pixel_minimal_limit          : 8;   // 23:16
} L9A0_PE1_L_SQM_CTRL_5_T;

typedef struct { // 0x1738
	UINT32 pe1_l_sqm_stat_f                : 32;   // 31: 0
} L9A0_PE1_L_SQM_STAT_T;

typedef struct { // 0x1750
	UINT32 black_boundary_detection_enable : 1;   //     0
	UINT32 hysterisis_mode                 : 3;   //  3: 1
	UINT32                                 : 3;   //  6: 4
	UINT32 mode_selection                  : 1;   //     7
	UINT32 cnt_th                          : 8;   // 15: 8
	UINT32 diff_th                         : 8;   // 23:16
	UINT32 vcnt                            : 8;   // 31:24
} L9A0_PE1_L_BBD2D_CTRL_0_T;

typedef struct { // 0x1754
	UINT32 bbd_x0                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y0                          : 12;  // 27:16
} L9A0_PE1_L_BBD2D_CTRL_1_T;

typedef struct { // 0x1758
	UINT32 bbd_x1                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y1                          : 12;  // 27:16
} L9A0_PE1_L_BBD2D_CTRL_2_T;

typedef struct { // 0x175c
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y0                              : 12;  // 27:16
} L9A0_PE1_L_BBD2D_STAT_0_T;

typedef struct { // 0x1760
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_L_BBD2D_STAT_1_T;

typedef struct { // 0x1770
	UINT32 black_boundary_detection_enable : 1;   //     0
	UINT32 hysterisis_mode                 : 3;   //  3: 1
	UINT32 pe1_3d_type                     : 3;   //  6: 4
	UINT32 mode_selection                  : 1;   //     7
	UINT32 cnt_th                          : 8;   // 15: 8
	UINT32 diff_th                         : 8;   // 23:16
	UINT32 vcnt                            : 8;   // 31:24
} L9A0_PE1_L_BBD3D_CTRL_00_T;

typedef struct { // 0x1774
	UINT32 bbd_x0                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y0                          : 12;  // 27:16
	UINT32 bbd_read_control                : 2;   // 29:28
} L9A0_PE1_L_BBD3D_CTRL_01_T;

typedef struct { // 0x1778
	UINT32 bbd_x1                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y1                          : 12;  // 27:16
} L9A0_PE1_L_BBD3D_CTRL_02_T;

typedef struct { // 0x177c
	UINT32 x                               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y                               : 12;  // 27:16
} L9A0_PE1_L_BBD3D_STAT_0_T;

typedef struct { // 0x3300
	UINT32 load_time                       : 1;   //     0
	UINT32 load_enable                     : 1;   //     1
	UINT32 load_type                       : 1;   //     2
} L9A0_PE1_R_TOP_CTRL_00_T;

typedef struct { // 0x3304
	UINT32 width                           : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 height                          : 12;  // 27:16
} L9A0_PE1_R_TOP_CTRL_01_T;

typedef struct { // 0x3308
	UINT32 tpg_positon                     : 1;   //     0
	UINT32                                 : 7;   //  7: 1
	UINT32 vdpulse_pos                     : 11;  // 18: 8
} L9A0_PE1_R_TOP_CTRL_02_T;

typedef struct { // 0x330c
	UINT32 vcnt                            : 12;  // 11: 0
	UINT32 va_pe1_in                       : 1;   //    12
	UINT32 va_pe1_out                      : 1;   //    13
	UINT32                                 : 2;   // 15:14
	UINT32 stat_tpg                        : 1;   //    16
	UINT32 stat_gt                         : 3;   // 19:17
	UINT32 stat_crg_lsr                    : 3;   // 22:20
	UINT32                                 : 1;   //    23
	UINT32 stat_crg_shp                    : 3;   // 26:24
	UINT32 stat_dce                        : 1;   //    27
	UINT32 stat_cen                        : 1;   //    28
	UINT32 stat_wb                         : 1;   //    29
	UINT32 stat_gmc                        : 2;   // 31:30
} L9A0_PE1_R_TOP_CTRL_03_T;

typedef struct { // 0x3320
	UINT32                                 : 6;   //  5: 0
	UINT32 win_outside                     : 1;   //     6
	UINT32 win_en                          : 1;   //     7
	UINT32 bdr_alpha                       : 5;   // 12: 8
	UINT32 bdr_wid                         : 2;   // 14:13
	UINT32 bdr_en                          : 1;   //    15
	UINT32 cr5                             : 5;   // 20:16
	UINT32 cb5                             : 5;   // 25:21
	UINT32 yy6                             : 6;   // 31:26
} L9A0_PE1_R_WIN_CTRL_00_T;

typedef struct { // 0x3324
	UINT32 win_w0_x0                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w0_y0                       : 11;  // 26:16
} L9A0_PE1_R_WIN_CTRL_01_T;

typedef struct { // 0x3328
	UINT32 win_w0_x1                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w0_y1                       : 11;  // 26:16
} L9A0_PE1_R_WIN_CTRL_02_T;

typedef struct { // 0x332c
	UINT32 win_w1_x0                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w1_y0                       : 11;  // 26:16
} L9A0_PE1_R_WIN_CTRL_03_T;

typedef struct { // 0x3330
	UINT32 win_w1_x1                       : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_w1_y1                       : 11;  // 26:16
} L9A0_PE1_R_WIN_CTRL_04_T;

typedef struct { // 0x3350
	UINT32 apl_win_ctrl_x0                 : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 apl_win_ctrl_y0                 : 11;  // 26:16
} L9A0_PE1_R_APL_CTRL_00_T;

typedef struct { // 0x3354
	UINT32 apl_win_ctrl_x1                 : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 apl_win_ctrl_y1                 : 11;  // 26:16
} L9A0_PE1_R_APL_CTRL_01_T;

typedef struct { // 0x3358
	UINT32 apl_position                    : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 apl_y_type                      : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 act_win_mode                    : 1;   //     8
} L9A0_PE1_R_APL_CTRL_02_T;

typedef struct { // 0x335c
	UINT32 apl_y                           : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 apl_rgb                         : 10;  // 25:16
} L9A0_PE1_R_APL_CTRL_03_T;

typedef struct { // 0x3360
	UINT32 apl_b                           : 10;  //  9: 0
	UINT32 apl_g                           : 10;  // 19:10
	UINT32 apl_r                           : 10;  // 29:20
} L9A0_PE1_R_APL_CTRL_04_T;

typedef struct { // 0x3370
	UINT32 tpg_enable                      : 1;   //     0
	UINT32 pattern_type                    : 2;   //  2: 1
	UINT32                                 : 1;   //     3
	UINT32 blend_alpha                     : 4;   //  7: 4
	UINT32 blt_size_x                      : 12;  // 19: 8
	UINT32 blt_size_y                      : 12;  // 31:20
} L9A0_PE1_R_TPG_CTRL_00_T;

typedef struct { // 0x3374
	UINT32 gradation_stride                : 7;   //  6: 0
	UINT32 gradation_direction             : 1;   //     7
	UINT32 gradation_bar_en                : 4;   // 11: 8
	UINT32                                 : 4;   // 15:12
	UINT32 washing_num_of_bar_x            : 3;   // 18:16
	UINT32                                 : 1;   //    19
	UINT32 washing_num_of_bar_y            : 3;   // 22:20
	UINT32                                 : 1;   //    23
	UINT32 washing_speed                   : 8;   // 31:24
} L9A0_PE1_R_TPG_CTRL_01_T;

typedef struct { // 0x3378
	UINT32 patch_en                        : 32;  // 31: 0
} L9A0_PE1_R_TPG_CTRL_02_T;

typedef struct { // 0x337c
	UINT32 tpg_indir_addr                  : 7;   //  6: 0
	UINT32                                 : 5;   // 11: 7
	UINT32 tpg_indir_ai_en                 : 1;   //    12
} L9A0_PE1_R_TPG_IA_CTRL_T;

typedef struct { // 0x3380
	UINT32 tpg_indir_data                  : 32;  // 31: 0
} L9A0_PE1_R_TPG_IA_DATA_T;

typedef struct { // 0x33a0
	UINT32 vignetting_enable               : 1;   //     0
	UINT32 film_contrast_enable            : 1;   //     1
	UINT32                                 : 6;   //  7: 2
	UINT32 contrast_alpha                  : 8;   // 15: 8
	UINT32 contrast_delta_max              : 8;   // 23:16
	UINT32 vignetting_gain                 : 8;   // 31:24
} L9A0_PE1_R_FILM_CTRL_00_T;

typedef struct { // 0x33a4
	UINT32 noise_gen_enable                : 1;   //     0
	UINT32 noise_frame_rate                : 3;   //  3: 1
	UINT32 noise_size                      : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 noise_gain                      : 8;   // 15: 8
} L9A0_PE1_R_FILM_CTRL_01_T;

typedef struct { // 0x33a8
	UINT32 tone_gain                       : 7;   //  6: 0
	UINT32                                 : 1;   //     7
	UINT32 tone_offset                     : 6;   // 13: 8
} L9A0_PE1_R_FILM_CTRL_02_T;

typedef struct { // 0x33c0
	UINT32 flats_t0_fc0                    : 2;   //  1: 0
	UINT32 flats_t0_fcs                    : 2;   //  3: 2
	UINT32 flats_t1_fc0                    : 2;   //  5: 4
	UINT32 flats_t1_fc1                    : 2;   //  7: 6
	UINT32 flats_t0_fcp                    : 2;   //  9: 8
	UINT32 flats_t0_fcd                    : 2;   // 11:10
	UINT32 t0_bc0                          : 2;   // 13:12
	UINT32 t1_bc0                          : 2;   // 15:14
	UINT32 dth_t0_dth0                     : 7;   // 22:16
	UINT32 h_disable                       : 1;   //    23
	UINT32 dth_t0_dths                     : 8;   // 31:24
} L9A0_PE1_R_HFNR_CTRL_00_T;

typedef struct { // 0x33c4
	UINT32 dth_t0_dthp                     : 8;   //  7: 0
	UINT32 dth_t1_dth0                     : 4;   // 11: 8
	UINT32 dth_t1_dth1                     : 4;   // 15:12
} L9A0_PE1_R_HFNR_CTRL_01_T;

typedef struct { // 0x33d0
	UINT32 vsum_mode                       : 2;   //  1: 0
	UINT32 hsum_mode                       : 2;   //  3: 2
	UINT32 vsum121_en                      : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 vertical_min_max                : 2;   //  9: 8
	UINT32                                 : 6;   // 15:10
	UINT32 a_flt_mux                       : 2;   // 17:16
	UINT32 a_e_mux                         : 2;   // 19:18
	UINT32 t_mux                           : 1;   //    20
	UINT32                                 : 3;   // 23:21
	UINT32 a_gen_width                     : 4;   // 27:24
} L9A0_PE1_R_LSR_CTRL_00_T;

typedef struct { // 0x33d4
	UINT32 a_gen_of_y                      : 8;   //  7: 0
	UINT32 a_gen_of_c                      : 8;   // 15: 8
	UINT32 avg_flt_mode                    : 3;   // 18:16
	UINT32 avg_flt_en                      : 1;   //    19
	UINT32                                 : 4;   // 23:20
	UINT32 max_flt_mode                    : 3;   // 26:24
} L9A0_PE1_R_LSR_CTRL_01_T;

typedef struct { // 0x33d8
	UINT32 a_exp_gain_ctrl_y0              : 4;   //  3: 0
	UINT32 a_exp2_gain_ctrl_x0             : 4;   //  7: 4
	UINT32 a_exp2_gain_ctrl_y1             : 4;   // 11: 8
	UINT32 a_exp2_gain_ctrl_x1             : 4;   // 15:12
	UINT32 a_avg2_flt_wid                  : 4;   // 19:16
	UINT32 a_avg2_flt_en                   : 1;   //    20
	UINT32                                 : 3;   // 23:21
	UINT32 a_exp_max2_en                   : 1;   //    24
	UINT32                                 : 1;   //    25
	UINT32 y_sum_mode                      : 2;   // 27:26
} L9A0_PE1_R_LSR_CTRL_02_T;

typedef struct { // 0x33dc
	UINT32                                 : 5;   //  4: 0
	UINT32 a_mux_for_edge_gaintable        : 3;   //  7: 5
	UINT32                                 : 9;   // 16: 8
	UINT32 a_mux_for_detail_filter         : 3;   // 19:17
	UINT32                                 : 1;   //    20
	UINT32 a_mux_for_edge_filter           : 3;   // 23:21
	UINT32 a_scaling_flat_filter_          : 4;   // 27:24
	UINT32                                 : 1;   //    28
	UINT32 a_mux_for_flat_filter           : 3;   // 31:29
} L9A0_PE1_R_LSR_CTRL_03_T;

typedef struct { // 0x33e0
	UINT32                                 : 1;   //     0
	UINT32 dbg_scale                       : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 sum_mux                         : 4;   //  7: 4
	UINT32 enh_en_cc                       : 3;   // 10: 8
	UINT32                                 : 1;   //    11
	UINT32 enh_en_yy                       : 3;   // 14:12
} L9A0_PE1_R_LSR_CTRL_04_T;

typedef struct { // 0x33e4
	UINT32 vmm_param                       : 2;   //  1: 0
	UINT32                                 : 6;   //  7: 2
	UINT32 csft_gain                       : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 th_gain_edge                    : 6;   // 21:16
	UINT32 th_gain_flat                    : 2;   // 23:22
	UINT32 th_manual_th                    : 7;   // 30:24
	UINT32 th_manual_en                    : 1;   //    31
} L9A0_PE1_R_LSR_CTRL_05_T;

typedef struct { // 0x33e8
	UINT32                                 : 8;   //  7: 0
	UINT32 edge_filter_white_gain          : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 edge_filter_black_gain          : 6;   // 21:16
	UINT32                                 : 2;   // 23:22
	UINT32 amean_en                        : 1;   //    24
	UINT32                                 : 1;   //    25
	UINT32 edge_filter_v_tap               : 2;   // 27:26
	UINT32                                 : 2;   // 29:28
	UINT32 edge_c_filter_en                : 1;   //    30
	UINT32 edge_y_filter_en                : 1;   //    31
} L9A0_PE1_R_LSR_CTRL_06_T;

typedef struct { // 0x33ec
	UINT32                                 : 24;  // 23: 0
	UINT32 flat_filter_gain                : 6;   // 29:24
	UINT32                                 : 1;   //    30
	UINT32 flat_filter_en                  : 1;   //    31
} L9A0_PE1_R_LSR_CTRL_07_T;

typedef struct { // 0x33f0
	UINT32 amod_ctrl0_y0                   : 8;   //  7: 0
	UINT32 amod_ctrl0_x0                   : 8;   // 15: 8
	UINT32 amod_ctrl0_y1                   : 8;   // 23:16
	UINT32 amod_ctrl0_x1                   : 8;   // 31:24
} L9A0_PE1_R_LSR_CTRL_08_T;

typedef struct { // 0x33f4
	UINT32 amod_ctrl1_x0                   : 8;   //  7: 0
	UINT32 amod_ctrl1_x1                   : 8;   // 15: 8
	UINT32 y_c_mux_control                 : 3;   // 18:16
	UINT32 chroma_weight                   : 5;   // 23:19
} L9A0_PE1_R_LSR_CTRL_09_T;

typedef struct { // 0x3400
	UINT32 der_v_en                        : 1;   //     0
	UINT32                                 : 1;   //     1
	UINT32 der_gain_mapping                : 1;   //     2
	UINT32 bif_en                          : 1;   //     3
	UINT32 output_mux                      : 4;   //  7: 4
} L9A0_PE1_R_DER_CTRL_0_T;

typedef struct { // 0x3404
	UINT32 gain_th0                        : 8;   //  7: 0
	UINT32 gain_th1                        : 8;   // 15: 8
} L9A0_PE1_R_DER_CTRL_1_T;

typedef struct { // 0x3410
	UINT32 detail_enhancer_enable          : 1;   //     0
	UINT32                                 : 2;   //  2: 1
	UINT32 debug_mode                      : 1;   //     3
	UINT32 debug_image                     : 4;   //  7: 4
	UINT32 gain_w                          : 8;   // 15: 8
	UINT32 gain_b                          : 8;   // 23:16
	UINT32 filter_coef_normalization       : 2;   // 25:24
	UINT32 freq_selective_filter_type      : 1;   //    26
	UINT32 detail_measure_for_sca          : 1;   //    27
} L9A0_PE1_R_LSR_DTL_CTRL_00_T;

typedef struct { // 0x3414
	UINT32 f2_gain                         : 8;   //  7: 0
	UINT32 f3_gain                         : 8;   // 15: 8
	UINT32 f4_gain                         : 8;   // 23:16
	UINT32 f5_gain                         : 8;   // 31:24
} L9A0_PE1_R_LSR_DTL_CTRL_01_T;

typedef struct { // 0x3418
	UINT32 t5_gain                         : 8;   //  7: 0
} L9A0_PE1_R_LSR_DTL_CTRL_02_T;

typedef struct { // 0x341c
	UINT32                                 : 1;   //     0
	UINT32 um3x3_type                      : 1;   //     1
	UINT32                                 : 6;   //  7: 2
	UINT32 um3x3_gain                      : 8;   // 15: 8
} L9A0_PE1_R_LSR_DTL_CTRL_03_T;

typedef struct { // 0x3420
	UINT32 pe1_r_lsr_dtl_ctrl_04_f         : 32;   // 31: 0
} L9A0_PE1_R_LSR_DTL_CTRL_04_T;

typedef struct { // 0x3424
	UINT32 manual_coring_enable            : 1;   //     0
	UINT32 coring_post_filtering_type      : 2;   //  2: 1
	UINT32 coring_post_filtering_enable    : 1;   //     3
	UINT32 local_min_max_mode              : 2;   //  5: 4
	UINT32 coring_mmd_type                 : 2;   //  7: 6
	UINT32                                 : 4;   // 11: 8
	UINT32 dbg_diff_gain                   : 3;   // 14:12
	UINT32                                 : 1;   //    15
	UINT32 c_mmd_th                        : 4;   // 19:16
	UINT32 c_mmd_scale                     : 4;   // 23:20
	UINT32 c_mmd_type                      : 2;   // 25:24
} L9A0_PE1_R_LSR_DTL_CTRL_05_T;

typedef struct { // 0x3428
	UINT32 pe1_r_lsr_dtl_ctrl_06_f         : 32;   // 31: 0
} L9A0_PE1_R_LSR_DTL_CTRL_06_T;

typedef struct { // 0x342c
	UINT32 coring_mmd_th_l1                : 8;   //  7: 0
	UINT32 coring_mmd_th_l2                : 8;   // 15: 8
	UINT32 coring_mmd_th_h1                : 8;   // 23:16
	UINT32 coring_mmd_th_h2                : 8;   // 31:24
} L9A0_PE1_R_LSR_DTL_CTRL_07_T;

typedef struct { // 0x3430
	UINT32 post_filterig_enable            : 1;   //     0
	UINT32                                 : 7;   //  7: 1
	UINT32 post_filtering_y_delta          : 4;   // 11: 8
	UINT32 post_filtering_y_th             : 4;   // 15:12
} L9A0_PE1_R_LSR_DTL_CTRL_08_T;

typedef struct { // 0x3434
	UINT32 lgain_en                        : 1;   //     0
	UINT32 lgain_mode                      : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 lgain_apl_type                  : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 lgain_low_th0                   : 8;   // 15: 8
	UINT32 lgain_low_th1                   : 8;   // 23:16
} L9A0_PE1_R_LSR_DTL_CTRL_09_T;

typedef struct { // 0x3438
	UINT32 lgain_high_th0                  : 8;   //  7: 0
	UINT32 lgain_high_th1                  : 8;   // 15: 8
} L9A0_PE1_R_LSR_DTL_CTRL_0A_T;

typedef struct { // 0x343c
	UINT32 gain_balancing_on_off           : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 delta_axis_resolution           : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 ed_x1                           : 8;   // 15: 8
	UINT32 ed_x2                           : 8;   // 23:16
} L9A0_PE1_R_LSR_DTL_CTRL_0B_T;

typedef struct { // 0x3440
	UINT32 ed_y1                           : 8;   //  7: 0
	UINT32 ed_y2                           : 8;   // 15: 8
	UINT32 ed_y3                           : 8;   // 23:16
} L9A0_PE1_R_LSR_DTL_CTRL_0C_T;

typedef struct { // 0x3444
	UINT32 pe1_r_lsr_dtl_ctrl_0d_f         : 32;   // 31: 0
} L9A0_PE1_R_LSR_DTL_CTRL_0D_T;

typedef struct { // 0x3450
	UINT32 extreme_enhancer_enable         : 1;   //     0
	UINT32                                 : 7;   //  7: 1
	UINT32 um1_enable                      : 1;   //     8
	UINT32 um2_enable                      : 1;   //     9
	UINT32 um3_enable                      : 1;   //    10
	UINT32 um4_enable                      : 1;   //    11
	UINT32 um1_filter_type                 : 1;   //    12
	UINT32 um2_filter_type                 : 1;   //    13
	UINT32 um3_filter_type                 : 1;   //    14
	UINT32 um4_filter_type                 : 1;   //    15
	UINT32 ee_gain_b                       : 4;   // 19:16
	UINT32 ee_gain_w                       : 4;   // 23:20
} L9A0_PE1_R_LSR_DTL_EE_CTRL_00_T;

typedef struct { // 0x3454
	UINT32 um1_gain_b                      : 4;   //  3: 0
	UINT32 um1_gain_w                      : 4;   //  7: 4
	UINT32 um2_gain_b                      : 4;   // 11: 8
	UINT32 um2_gain_w                      : 4;   // 15:12
	UINT32 um3_gain_b                      : 4;   // 19:16
	UINT32 um3_gain_w                      : 4;   // 23:20
	UINT32 um4_gain_b                      : 4;   // 27:24
	UINT32 um4_gain_w                      : 4;   // 31:28
} L9A0_PE1_R_LSR_DTL_EE_CTRL_01_T;

typedef struct { // 0x3458
	UINT32 enable                          : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 filter_sel                      : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 lap_gain                        : 8;   // 15: 8
	UINT32 sobel_gx_gain                   : 8;   // 23:16
	UINT32 sobel_manual_gain               : 8;   // 31:24
} L9A0_PE1_R_LSR_DTL_EE_CTRL_02_T;

typedef struct { // 0x345c
	UINT32 white_gain                      : 7;   //  6: 0
	UINT32                                 : 1;   //     7
	UINT32 black_gain                      : 7;   // 14: 8
	UINT32                                 : 1;   //    15
	UINT32 h_gain                          : 8;   // 23:16
	UINT32 v_gain                          : 8;   // 31:24
} L9A0_PE1_R_LSR_DTL_EE_CTRL_03_T;

typedef struct { // 0x3460
	UINT32 gain_balancing_on_off           : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 delta_axis_resolution           : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 ed_x1                           : 8;   // 15: 8
	UINT32 ed_x2                           : 8;   // 23:16
} L9A0_PE1_R_LSR_DTL_EE_CTRL_04_T;

typedef struct { // 0x3464
	UINT32 ed_y1                           : 8;   //  7: 0
	UINT32 ed_y2                           : 8;   // 15: 8
	UINT32 ed_y3                           : 8;   // 23:16
} L9A0_PE1_R_LSR_DTL_EE_CTRL_05_T;

typedef struct { // 0x3470
	UINT32 gt_detail_mode                  : 1;   //     0
	UINT32 gt_edge_mode                    : 1;   //     1
	UINT32 gt_flat_mode                    : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 gt_detail_manual_gain           : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 gt_edge_manual_gain             : 6;   // 21:16
	UINT32                                 : 2;   // 23:22
	UINT32 gt_flat_manual_gain             : 6;   // 29:24
} L9A0_PE1_R_LSR_GT_CTRL_00_T;

typedef struct { // 0x3474
	UINT32 gt_interpolation_type           : 2;   //  1: 0
	UINT32                                 : 6;   //  7: 2
	UINT32 interpol_x0                     : 8;   // 15: 8
	UINT32 interpol_x1                     : 8;   // 23:16
	UINT32 interpol_x2                     : 8;   // 31:24
} L9A0_PE1_R_LSR_GT_CTRL_01_T;

typedef struct { // 0x3478
	UINT32 th1                             : 8;   //  7: 0
	UINT32 th2                             : 8;   // 15: 8
	UINT32 th3                             : 8;   // 23:16
	UINT32 pcm_th                          : 8;   // 31:24
} L9A0_PE1_R_LSR_GT_CTRL_02_T;

typedef struct { // 0x347c
	UINT32 enable_manual_sqa_measure       : 1;   //     0
	UINT32 auto_sqa_measure_type           : 1;   //     1
	UINT32 hdm_pcm_selection               : 1;   //     2
	UINT32 sqm_bit_resolution              : 1;   //     3
	UINT32                                 : 4;   //  7: 4
	UINT32 manual_sqa_value                : 8;   // 15: 8
	UINT32 hd_measure                      : 8;   // 23:16
	UINT32 pc_measure                      : 8;   // 31:24
} L9A0_PE1_R_LSR_GT_CTRL_03_T;

typedef struct { // 0x3480
	UINT32 source_quality_measure          : 8;   //  7: 0
} L9A0_PE1_R_LSR_GT_CTRL_04_T;

typedef struct { // 0x3484
	UINT32 index                           : 6;   //  5: 0
	UINT32                                 : 2;   //  7: 6
	UINT32 edf                             : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 auto_increment                  : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 gt_enable                       : 1;   //    15
} L9A0_PE1_R_LSR_GT_IA_CTRL_T;

typedef struct { // 0x3488
	UINT32 gt_wdata0                       : 6;   //  5: 0
	UINT32                                 : 2;   //  7: 6
	UINT32 gt_wdata1                       : 6;   // 13: 8
	UINT32                                 : 2;   // 15:14
	UINT32 gt_wdata2                       : 6;   // 21:16
} L9A0_PE1_R_LSR_GT_IA_DATA_T;

typedef struct { // 0x34a0
	UINT32                                 : 8;   //  7: 0
	UINT32 sca_gain_display                : 4;   // 11: 8
} L9A0_PE1_R_LSR_SCA_CTRL_00_T;

typedef struct { // 0x34a4
	UINT32 sca_en                          : 1;   //     0
	UINT32                                 : 7;   //  7: 1
	UINT32 sca_gain                        : 6;   // 13: 8
} L9A0_PE1_R_LSR_SCA_CTRL_01_T;

typedef struct { // 0x34a8
	UINT32 pe1_r_lsr_sca_ctrl_02_f         : 32;   // 31: 0
} L9A0_PE1_R_LSR_SCA_CTRL_02_T;

typedef struct { // 0x34ac
	UINT32 pe1_r_lsr_sca_ctrl_03_f         : 32;   // 31: 0
} L9A0_PE1_R_LSR_SCA_CTRL_03_T;

typedef struct { // 0x34b0
	UINT32                                 : 16;  // 15: 0
	UINT32 enable_sca_to_flat_filter       : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 gain_of_sca_to_flat_filter      : 4;   // 23:20
} L9A0_PE1_R_LSR_SCA_CTRL_04_T;

typedef struct { // 0x34b4
	UINT32 pe1_r_lsr_sca_ctrl_05_f         : 32;   // 31: 0
} L9A0_PE1_R_LSR_SCA_CTRL_05_T;

typedef struct { // 0x34b8
	UINT32 enable_debug_mode               : 1;   //     0
	UINT32 show_sqm1                       : 1;   //     1
	UINT32 show_cr_info                    : 1;   //     2
	UINT32 debug_bar_gain_position         : 1;   //     3
	UINT32 measure_display_gain            : 3;   //  6: 4
	UINT32 show_tpg                        : 1;   //     7
	UINT32 show_hdm_pcm_area               : 1;   //     8
	UINT32 show_sqm2                       : 1;   //     9
	UINT32 sqm2_debug_image                : 4;   // 13:10
	UINT32                                 : 1;   //    14
	UINT32 show_bbd                        : 2;   // 16:15
	UINT32 bbd_line_width                  : 3;   // 19:17
	UINT32 show_apl                        : 1;   //    20
} L9A0_PE1_R_LSR_SCA_CTRL_06_T;

typedef struct { // 0x34bc
	UINT32                                 : 4;   //  3: 0
	UINT32 y_grad_gain                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 cb_grad_gain                    : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 cr_grad_gain                    : 2;   // 13:12
} L9A0_PE1_R_LSR_SCA_CTRL_07_T;

typedef struct { // 0x34c0
	UINT32 y_range_min                     : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 y_range_max                     : 10;  // 25:16
} L9A0_PE1_R_LSR_SCA_CTRL_08_T;

typedef struct { // 0x34c4
	UINT32 cb_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cb_range_max                    : 10;  // 25:16
} L9A0_PE1_R_LSR_SCA_CTRL_09_T;

typedef struct { // 0x34c8
	UINT32 cr_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cr_range_max                    : 10;  // 25:16
} L9A0_PE1_R_LSR_SCA_CTRL_0A_T;

typedef struct { // 0x34cc
	UINT32 gain_type                       : 2;   //  1: 0
	UINT32 color_region                    : 3;   //  4: 2
	UINT32                                 : 7;   // 11: 5
	UINT32 auto_increment                  : 1;   //    12
} L9A0_PE1_R_LSR_SCA_IA_CTRL_T;

typedef struct { // 0x34d0
	UINT32 x1                              : 8;   //  7: 0
	UINT32 x2                              : 8;   // 15: 8
	UINT32 g1                              : 6;   // 21:16
	UINT32                                 : 2;   // 23:22
	UINT32 g2                              : 6;   // 29:24
} L9A0_PE1_R_LSR_SCA_IA_DATA_T;

typedef struct { // 0x34e0
	UINT32 hif_crg_lsr_address             : 4;   //  3: 0
	UINT32                                 : 8;   // 11: 4
	UINT32 hif_crg_lsr_ai                  : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_crg_lsr_wr                  : 1;   //    15
} L9A0_PE1_R_LSR_CRG_IA_CTRL_T;

typedef struct { // 0x34e4
	UINT32 value                           : 8;   //  7: 0
	UINT32                                 : 2;   //  9: 8
	UINT32 saturation                      : 7;   // 16:10
	UINT32                                 : 3;   // 19:17
	UINT32 hue                             : 10;  // 29:20
} L9A0_PE1_R_LSR_CRG_IA_DATA_T;

typedef struct { // 0x34f0
	UINT32 edge_enhance_enable             : 1;   //     0
	UINT32 edge_enhance_mode               : 1;   //     1
	UINT32 lm_mode                         : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 lti_level                       : 4;   // 11: 8
	UINT32 edge_operator_selection         : 2;   // 13:12
} L9A0_PE1_R_SHP_EDGE_CTRL_00_T;

typedef struct { // 0x34f4
	UINT32 white_gain                      : 7;   //  6: 0
	UINT32                                 : 1;   //     7
	UINT32 black_gain                      : 7;   // 14: 8
	UINT32                                 : 1;   //    15
	UINT32 horizontal_gain                 : 8;   // 23:16
	UINT32 vertical_gain                   : 8;   // 31:24
} L9A0_PE1_R_SHP_EDGE_CTRL_01_T;

typedef struct { // 0x34f8
	UINT32 sobel_weight                    : 8;   //  7: 0
	UINT32 laplacian_weight                : 8;   // 15: 8
	UINT32 sobel_manual_mode_en            : 1;   //    16
	UINT32                                 : 7;   // 23:17
	UINT32 sobel_manual_gain               : 8;   // 31:24
} L9A0_PE1_R_SHP_EDGE_CTRL_02_T;

typedef struct { // 0x34fc
	UINT32 lum_low_th1                     : 8;   //  7: 0
	UINT32 lum_low_th2                     : 8;   // 15: 8
	UINT32 lum_high_th1                    : 8;   // 23:16
	UINT32 lum_high_th2                    : 8;   // 31:24
} L9A0_PE1_R_SHP_EDGE_CTRL_03_T;

typedef struct { // 0x3500
	UINT32 laplacian_offset                : 8;   //  7: 0
	UINT32 debug_selection                 : 3;   // 10: 8
	UINT32 debug_enable                    : 1;   //    11
	UINT32 gx_weight_manual_mode           : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 gx_weight_manual_gain           : 8;   // 23:16
	UINT32 par_filter_sel                  : 3;   // 26:24
	UINT32                                 : 1;   //    27
	UINT32 par_out_sel                     : 2;   // 29:28
} L9A0_PE1_R_SHP_EDGE_CTRL_04_T;

typedef struct { // 0x3508
	UINT32 coring_enable                   : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 coring_mmd_sel                  : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 coring_low_th_resol             : 1;   //     8
	UINT32                                 : 7;   // 15: 9
	UINT32 coring_low_th1                  : 8;   // 23:16
	UINT32 coring_low_th2                  : 8;   // 31:24
} L9A0_PE1_R_SHP_EDGE_CTRL_05_T;

typedef struct { // 0x350c
	UINT32 pf_en                           : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 pf_debug_mode                   : 3;   //  6: 4
	UINT32 pf_display_mode                 : 1;   //     7
	UINT32 pf_p1_flt_type_concave          : 1;   //     8
	UINT32 pf_p1_flt_type_convex           : 1;   //     9
	UINT32 pf_p2_flt_type_concave          : 1;   //    10
	UINT32 pf_p2_flt_type_convex           : 1;   //    11
	UINT32 pf_p12_mode                     : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 pf_gain                         : 4;   // 19:16
} L9A0_PE1_R_SHP_EDGE_CTRL_06_T;

typedef struct { // 0x3510
	UINT32 pf_p0_th1                       : 8;   //  7: 0
	UINT32 pf_p0_th2                       : 8;   // 15: 8
	UINT32 pf_p1_th1                       : 8;   // 23:16
	UINT32 pf_p1_th2                       : 8;   // 31:24
} L9A0_PE1_R_SHP_EDGE_CTRL_07_T;

typedef struct { // 0x3514
	UINT32 pf_p1_th3                       : 8;   //  7: 0
	UINT32 pf_p2_th1                       : 8;   // 15: 8
	UINT32 pf_p2_th2                       : 8;   // 23:16
	UINT32 pf_p2_th3                       : 8;   // 31:24
} L9A0_PE1_R_SHP_EDGE_CTRL_08_T;

typedef struct { // 0x3520
	UINT32 cti_en                          : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 tap_size                        : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 cti_gain                        : 8;   // 15: 8
} L9A0_PE1_R_CTI_CTRL_00_T;

typedef struct { // 0x3524
	UINT32 pe1_r_cti_ctrl_01_f             : 32;   // 31: 0
} L9A0_PE1_R_CTI_CTRL_01_T;

typedef struct { // 0x3528
	UINT32 ycm_en0                         : 1;   //     0
	UINT32 ycm_en1                         : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 ycm_band_sel                    : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 ycm_diff_th                     : 8;   // 15: 8
	UINT32 ycm_y_gain                      : 4;   // 19:16
	UINT32 ycm_c_gain                      : 4;   // 23:20
} L9A0_PE1_R_CTI_CTRL_02_T;

typedef struct { // 0x3530
	UINT32 enable                          : 1;   //     0
	UINT32 coring_en                       : 1;   //     1
	UINT32 coring_diff_sel                 : 1;   //     2
	UINT32 filter_tap                      : 1;   //     3
	UINT32 avg_type                        : 1;   //     4
	UINT32 coring_mmd_sel                  : 2;   //  6: 5
	UINT32                                 : 1;   //     7
	UINT32 gain_w                          : 8;   // 15: 8
	UINT32 gain_b                          : 8;   // 23:16
} L9A0_PE1_R_SHP_UM_CTRL_0_T;

typedef struct { // 0x3534
	UINT32 coring_th_low1                  : 8;   //  7: 0
	UINT32 coring_th_low2                  : 8;   // 15: 8
	UINT32 coring_th_high1                 : 8;   // 23:16
	UINT32 coring_th_high2                 : 8;   // 31:24
} L9A0_PE1_R_SHP_UM_CTRL_1_T;

typedef struct { // 0x3538
	UINT32 lgain_en                        : 1;   //     0
	UINT32 lgain_mode                      : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 lgain_apl_type                  : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 lgain_low_th0                   : 8;   // 15: 8
	UINT32 lgain_low_th1                   : 8;   // 23:16
} L9A0_PE1_R_SHP_UM_CTRL_2_T;

typedef struct { // 0x353c
	UINT32 lgain_high_th0                  : 8;   //  7: 0
	UINT32 lgain_high_th1                  : 8;   // 15: 8
	UINT32 sca_en                          : 1;   //    16
	UINT32                                 : 7;   // 23:17
	UINT32 sca_gain                        : 6;   // 29:24
} L9A0_PE1_R_SHP_UM_CTRL_3_T;

typedef struct { // 0x3540
	UINT32                                 : 4;   //  3: 0
	UINT32 y_grad_gain                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 cb_grad_gain                    : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 cr_grad_gain                    : 2;   // 13:12
} L9A0_PE1_R_SHP_UM_CTRL_4_T;

typedef struct { // 0x3544
	UINT32 y_range_min                     : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 y_range_max                     : 10;  // 25:16
} L9A0_PE1_R_SHP_UM_CTRL_5_T;

typedef struct { // 0x3548
	UINT32 cb_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cb_range_max                    : 10;  // 25:16
} L9A0_PE1_R_SHP_UM_CTRL_6_T;

typedef struct { // 0x354c
	UINT32 cr_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cr_range_max                    : 10;  // 25:16
} L9A0_PE1_R_SHP_UM_CTRL_7_T;

typedef struct { // 0x3550
	UINT32 enable                          : 1;   //     0
	UINT32 coring_en                       : 1;   //     1
	UINT32                                 : 6;   //  7: 2
	UINT32 gain                            : 8;   // 15: 8
	UINT32 coring_min                      : 8;   // 23:16
	UINT32 coring_max                      : 8;   // 31:24
} L9A0_PE1_R_SHP_BLUR_CTRL_T;

typedef struct { // 0x3560
	UINT32 dbg_scale                       : 4;   //  3: 0
	UINT32 sum_mux                         : 4;   //  7: 4
	UINT32 enh_en_cc                       : 3;   // 10: 8
	UINT32                                 : 1;   //    11
	UINT32 enh_en_yy                       : 3;   // 14:12
} L9A0_PE1_R_SHP_SUM_CTRL_T;

typedef struct { // 0x3570
	UINT32 pe1_r_ti_ctrl_0_f               : 32;   // 31: 0
} L9A0_PE1_R_TI_CTRL_0_T;

typedef struct { // 0x3574
	UINT32 enable                          : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 coring_step                     : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 coring_th                       : 8;   // 15: 8
	UINT32 ti_gain                         : 8;   // 23:16
} L9A0_PE1_R_TI_CTRL_1_T;

typedef struct { // 0x3578
	UINT32 enable                          : 1;   //     0
	UINT32 debug_coring                    : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 coring_step                     : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 coring_th                       : 8;   // 15: 8
	UINT32 y_gain                          : 8;   // 23:16
	UINT32 c_gain                          : 8;   // 31:24
} L9A0_PE1_R_TI_CTRL_2_T;

typedef struct { // 0x357c
	UINT32 enable                          : 1;   //     0
	UINT32 debug_coring                    : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 coring_step                     : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 coring_th                       : 8;   // 15: 8
	UINT32 y_gain                          : 8;   // 23:16
	UINT32 c_gain                          : 8;   // 31:24
} L9A0_PE1_R_TI_CTRL_3_T;

typedef struct { // 0x3580
	UINT32 gain0_en                        : 1;   //     0
	UINT32 gain1_en                        : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 output_mux                      : 2;   //  5: 4
	UINT32                                 : 10;  // 15: 6
	UINT32 gain0_th0                       : 8;   // 23:16
	UINT32 gain0_th1                       : 8;   // 31:24
} L9A0_PE1_R_TI_CTRL_4_T;

typedef struct { // 0x3584
	UINT32 gain1_div_mode                  : 2;   //  1: 0
} L9A0_PE1_R_TI_CTRL_5_T;

typedef struct { // 0x3590
	UINT32 edf_en                          : 1;   //     0
	UINT32 dj_en                           : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 edf_artifact_reduction          : 1;   //     4
	UINT32 l_pro_en                        : 1;   //     5
	UINT32                                 : 2;   //  7: 6
	UINT32 smoothness                      : 8;   // 15: 8
} L9A0_PE1_R_DJ_CTRL_00_T;

typedef struct { // 0x3594
	UINT32 level_threshold                 : 8;   //  7: 0
	UINT32 protect_delta                   : 8;   // 15: 8
} L9A0_PE1_R_DJ_CTRL_01_T;

typedef struct { // 0x3598
	UINT32 edf_pixel_diff_min              : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 edf_pixel_diff_max              : 5;   // 12: 8
} L9A0_PE1_R_DJ_CTRL_02_T;

typedef struct { // 0x359c
	UINT32 h_cnt_min                       : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 h_cnt_max                       : 5;   // 12: 8
	UINT32                                 : 3;   // 15:13
	UINT32 v_cnt_min                       : 5;   // 20:16
	UINT32                                 : 3;   // 23:21
	UINT32 v_cnt_max                       : 5;   // 28:24
} L9A0_PE1_R_DJ_CTRL_03_T;

typedef struct { // 0x35b0
	UINT32 enable                          : 1;   //     0
	UINT32 graycolor_enable                : 1;   //     1
	UINT32 color_only_enable               : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 center_position                 : 8;   // 15: 8
	UINT32 contrast                        : 8;   // 23:16
	UINT32 brightness                      : 8;   // 31:24
} L9A0_PE1_R_VSP_CTRL_00_T;

typedef struct { // 0x35c0
	UINT32 icsc_en                         : 1;   //     0
	UINT32 degamma_en                      : 1;   //     1
	UINT32 pcc_en                          : 1;   //     2
	UINT32 gamma                           : 1;   //     3
	UINT32 scaler_en                       : 1;   //     4
	UINT32 hsv_hsl_selection               : 1;   //     5
	UINT32 s_adpative_scaler               : 1;   //     6
} L9A0_PE1_R_XVY_CTRL_00_T;

typedef struct { // 0x35c4
	UINT32 r_csc_coef1                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef0                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_01_T;

typedef struct { // 0x35c8
	UINT32 r_csc_coef3                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef2                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_02_T;

typedef struct { // 0x35cc
	UINT32 r_csc_coef5                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef4                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_03_T;

typedef struct { // 0x35d0
	UINT32 r_csc_coef7                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_coef6                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_04_T;

typedef struct { // 0x35d4
	UINT32 r_csc_ofst0                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 r_csc_coef8                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_05_T;

typedef struct { // 0x35d8
	UINT32 r_csc_ofst2                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 r_csc_ofst1                     : 11;  // 26:16
} L9A0_PE1_R_XVY_CTRL_06_T;

typedef struct { // 0x35dc
	UINT32 r_csc_ofst4                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 r_csc_ofst3                     : 11;  // 26:16
} L9A0_PE1_R_XVY_CTRL_07_T;

typedef struct { // 0x35e0
	UINT32 r_pcc_coef0                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_csc_ofst5                     : 11;  // 26:16
} L9A0_PE1_R_XVY_CTRL_08_T;

typedef struct { // 0x35e4
	UINT32 r_pcc_coef2                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef1                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_09_T;

typedef struct { // 0x35e8
	UINT32 r_pcc_coef4                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef3                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_0A_T;

typedef struct { // 0x35ec
	UINT32 r_pcc_coef6                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef5                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_0B_T;

typedef struct { // 0x35f0
	UINT32 r_pcc_coef8                     : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 r_pcc_coef7                     : 15;  // 30:16
} L9A0_PE1_R_XVY_CTRL_0C_T;

typedef struct { // 0x35f4
	UINT32 scaler                          : 8;   //  7: 0
} L9A0_PE1_R_XVY_CTRL_0D_T;

typedef struct { // 0x3600
	UINT32                                 : 2;   //  1: 0
	UINT32 select_hsv                      : 1;   //     2
	UINT32 select_rgb                      : 1;   //     3
	UINT32                                 : 1;   //     4
	UINT32 vsp_sel                         : 1;   //     5
	UINT32 global_apl_sel                  : 1;   //     6
	UINT32 cen_bypass                      : 1;   //     7
	UINT32 cen_debug_mode                  : 1;   //     8
	UINT32 debugging_mode_core             : 1;   //     9
	UINT32 pe1_1st_core_gain_disable       : 1;   //    10
	UINT32 pe1_2nd_core_gain_disable       : 1;   //    11
	UINT32 v_scaler_en                     : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 demo_mode                       : 8;   // 23:16
	UINT32                                 : 7;   // 30:24
	UINT32 win_control_mode                : 1;   //    31
} L9A0_PE1_R_CEN_CTRL_00_T;

typedef struct { // 0x3604
	UINT32 show_color_region0              : 8;   //  7: 0
	UINT32 show_color_region1              : 8;   // 15: 8
	UINT32 color_region_en0                : 8;   // 23:16
	UINT32 color_region_en1                : 8;   // 31:24
} L9A0_PE1_R_CEN_CTRL_01_T;

typedef struct { // 0x3608
	UINT32 ihsv_sgain                      : 8;   //  7: 0
	UINT32 ihsv_vgain                      : 8;   // 15: 8
} L9A0_PE1_R_CEN_CTRL_02_T;

typedef struct { // 0x360c
	UINT32 ihsv_hoffset                    : 8;   //  7: 0
	UINT32 ihsv_soffset                    : 8;   // 15: 8
	UINT32 ihsv_voffset                    : 8;   // 23:16
} L9A0_PE1_R_CEN_CTRL_03_T;

typedef struct { // 0x3610
	UINT32 den_ctrl0                       : 8;   //  7: 0
	UINT32 den_apl_limit_high              : 8;   // 15: 8
	UINT32 den_gain                        : 8;   // 23:16
	UINT32 den_coring                      : 8;   // 31:24
} L9A0_PE1_R_CEN_CTRL_04_T;

typedef struct { // 0x3614
	UINT32 hif_cen_address                 : 8;   //  7: 0
	UINT32 hif_cen_ai_sel                  : 3;   // 10: 8
	UINT32                                 : 1;   //    11
	UINT32 hif_cen_ai                      : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_cen_enable                  : 1;   //    15
} L9A0_PE1_R_CEN_IA_CTRL_T;

typedef struct { // 0x3618
	UINT32 hif_cen_y_wdata                 : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 hif_cen_x_wdata                 : 10;  // 25:16
} L9A0_PE1_R_CEN_IA_DATA_T;

typedef struct { // 0x3630
	UINT32 enable                          : 1;   //     0
	UINT32 adjust_en                       : 1;   //     1
	UINT32 protection_en                   : 1;   //     2
	UINT32 adjust_en2                      : 1;   //     3
	UINT32 r_hist_data_sel                 : 1;   //     4
	UINT32 l_hist_data_sel                 : 1;   //     5
	UINT32 r_proc_data_sel                 : 1;   //     6
	UINT32 l_proc_data_sel                 : 1;   //     7
	UINT32 ff_mode_en                      : 1;   //     8
	UINT32 ff_mode_parity                  : 1;   //     9
} L9A0_PE1_R_LRCR_CTRL_00_T;

typedef struct { // 0x3634
	UINT32 th_max_hist                     : 8;   //  7: 0
	UINT32 th_valid_bins                   : 8;   // 15: 8
} L9A0_PE1_R_LRCR_CTRL_01_T;

typedef struct { // 0x3638
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 2;   // 13:12
	UINT32 hist_l_window_h_bbd             : 1;   //    14
	UINT32 hist_l_window_h_en              : 1;   //    15
	UINT32 y0                              : 12;  // 27:16
	UINT32                                 : 2;   // 29:28
	UINT32 hist_l_window_v_bbd             : 1;   //    30
	UINT32 hist_l_window_v_en              : 1;   //    31
} L9A0_PE1_R_LRCR_CTRL_02_T;

typedef struct { // 0x363c
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_R_LRCR_CTRL_03_T;

typedef struct { // 0x3640
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 2;   // 13:12
	UINT32 hist_r_window_h_bbd             : 1;   //    14
	UINT32 hist_r_window_h_en              : 1;   //    15
	UINT32 y0                              : 12;  // 27:16
	UINT32                                 : 2;   // 29:28
	UINT32 hist_r_window_v_bbd             : 1;   //    30
	UINT32 hist_r_window_v_en              : 1;   //    31
} L9A0_PE1_R_LRCR_CTRL_04_T;

typedef struct { // 0x3644
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_R_LRCR_CTRL_05_T;

typedef struct { // 0x3648
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 2;   // 13:12
	UINT32 active_window_h_bbd             : 1;   //    14
	UINT32 active_window_h_en              : 1;   //    15
	UINT32 y0                              : 12;  // 27:16
	UINT32                                 : 2;   // 29:28
	UINT32 active_window_v_bbd             : 1;   //    30
	UINT32 active_window_v_en              : 1;   //    31
} L9A0_PE1_R_LRCR_CTRL_06_T;

typedef struct { // 0x364c
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_R_LRCR_CTRL_07_T;

typedef struct { // 0x3650
	UINT32 max_hist                        : 8;   //  7: 0
	UINT32 n_valid_bins                    : 8;   // 15: 8
	UINT32 cdf_x1                          : 8;   // 23:16
	UINT32 cdf_x0                          : 8;   // 31:24
} L9A0_PE1_R_LRCR_STAT_00_T;

typedef struct { // 0x3654
	UINT32 max_hist                        : 8;   //  7: 0
	UINT32 n_valid_bins                    : 8;   // 15: 8
	UINT32 cdf_x1                          : 8;   // 23:16
	UINT32 cdf_x0                          : 8;   // 31:24
} L9A0_PE1_R_LRCR_STAT_01_T;

typedef struct { // 0x3658
	UINT32 max_hist                        : 8;   //  7: 0
	UINT32 n_valid_bins                    : 8;   // 15: 8
	UINT32 cdf_x1                          : 8;   // 23:16
	UINT32 cdf_x0                          : 8;   // 31:24
} L9A0_PE1_R_LRCR_STAT_02_T;

typedef struct { // 0x3670
	UINT32 dynamic_contrast_en             : 1;   //     0
	UINT32 hist_bin_mode                   : 2;   //  2: 1
	UINT32 hist_clear                      : 1;   //     3
	UINT32 hist_bin_bitwidth_mode          : 2;   //  5: 4
	UINT32 window_mode_en                  : 1;   //     6
	UINT32 window_acquire                  : 1;   //     7
	UINT32 color_region0_sel               : 1;   //     8
	UINT32 color_region1_sel               : 1;   //     9
	UINT32 color_region2_sel               : 1;   //    10
	UINT32 color_region3_sel               : 1;   //    11
	UINT32 color_region4_sel               : 1;   //    12
	UINT32 color_region5_sel               : 1;   //    13
	UINT32 color_region6_sel               : 1;   //    14
	UINT32 color_region7_sel               : 1;   //    15
	UINT32 color_region8_sel               : 1;   //    16
	UINT32 color_region9_sel               : 1;   //    17
	UINT32 color_region10_sel              : 1;   //    18
	UINT32 color_region11_sel              : 1;   //    19
	UINT32 color_region12_sel              : 1;   //    20
	UINT32 color_region13_sel              : 1;   //    21
	UINT32 color_region14_sel              : 1;   //    22
	UINT32 color_region15_sel              : 1;   //    23
	UINT32 dce_domain_sel                  : 1;   //    24
	UINT32 win_selection                   : 1;   //    25
} L9A0_PE1_R_DCE_CTRL_00_T;

typedef struct { // 0x3674
	UINT32 hist_bin_min_position           : 8;   //  7: 0
	UINT32 hist_bin_max_position           : 8;   // 15: 8
	UINT32 color_region_gain               : 8;   // 23:16
} L9A0_PE1_R_DCE_CTRL_01_T;

typedef struct { // 0x3678
	UINT32 color_region_en                 : 1;   //     0
	UINT32 color_debug_en                  : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 y_grad_gain                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 cb_grad_gain                    : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 cr_grad_gain                    : 2;   // 13:12
} L9A0_PE1_R_DCE_CTRL_02_T;

typedef struct { // 0x367c
	UINT32 y_range_min                     : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 y_range_max                     : 10;  // 25:16
} L9A0_PE1_R_DCE_CTRL_03_T;

typedef struct { // 0x3680
	UINT32 cb_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cb_range_max                    : 10;  // 25:16
} L9A0_PE1_R_DCE_CTRL_04_T;

typedef struct { // 0x3684
	UINT32 cr_range_min                    : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 cr_range_max                    : 10;  // 25:16
} L9A0_PE1_R_DCE_CTRL_05_T;

typedef struct { // 0x3688
	UINT32 hif_dyc_address                 : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 hif_dce_load                    : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 hif_dce_ai                      : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_dce_enable                  : 1;   //    15
} L9A0_PE1_R_DCE_IA_CTRL_T;

typedef struct { // 0x368c
	UINT32 hif_dyc_wdata_y                 : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 hif_dyc_wdata_x                 : 10;  // 25:16
} L9A0_PE1_R_DCE_IA_DATA_T;

typedef struct { // 0x3690
	UINT32 hif_dyc_wdata_y_32nd            : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 hif_dyc_wdata_x_32nd            : 10;  // 25:16
} L9A0_PE1_R_DCE_CTRL_08_T;

typedef struct { // 0x36a0
	UINT32 hif_hist_address                : 6;   //  5: 0
	UINT32                                 : 6;   // 11: 6
	UINT32 hif_hist_ai                     : 1;   //    12
	UINT32                                 : 2;   // 14:13
	UINT32 hif_hist_enable                 : 1;   //    15
	UINT32 hif_status_address              : 3;   // 18:16
	UINT32                                 : 9;   // 27:19
	UINT32 hif_status_ai                   : 1;   //    28
	UINT32 hif_mask                        : 1;   //    29
} L9A0_PE1_R_DCE_HIST_IA_CTRL_T;

typedef struct { // 0x36a4
	UINT32 pe1_r_dce_hist_ia_data1_f       : 32;   // 31: 0
} L9A0_PE1_R_DCE_HIST_IA_DATA1_T;

typedef struct { // 0x36a8
	UINT32 pe1_r_dce_hsit_ia_data2_f       : 32;   // 31: 0
} L9A0_PE1_R_DCE_HSIT_IA_DATA2_T;

typedef struct { // 0x36c0
	UINT32 wb_en                           : 1;   //     0
	UINT32 apl_gain_bypass                 : 1;   //     1
	UINT32 wb_user_ctrl_bypass             : 1;   //     2
	UINT32 max_to_one_bypass               : 1;   //     3
	UINT32                                 : 3;   //  6: 4
	UINT32 use_apl_than_ctemp              : 1;   //     7
	UINT32 user_ctemp                      : 8;   // 15: 8
	UINT32 ire_csc_offset                  : 10;  // 25:16
	UINT32                                 : 4;   // 29:26
	UINT32 degamma_en                      : 1;   //    30
	UINT32 gamma_en                        : 1;   //    31
} L9A0_PE1_R_WB_CTRL_00_T;

typedef struct { // 0x36c4
	UINT32 ire_csc_g_coeff                 : 10;  //  9: 0
	UINT32 ire_csc_b_coeff                 : 10;  // 19:10
	UINT32 ire_csc_r_coeff                 : 10;  // 29:20
} L9A0_PE1_R_WB_CTRL_01_T;

typedef struct { // 0x36c8
	UINT32 user_ctrl_g_gain                : 8;   //  7: 0
	UINT32 user_ctrl_b_gain                : 8;   // 15: 8
	UINT32 user_ctrl_r_gain                : 8;   // 23:16
} L9A0_PE1_R_WB_CTRL_02_T;

typedef struct { // 0x36cc
	UINT32 user_ctrl_g_offset              : 8;   //  7: 0
	UINT32 user_ctrl_b_offset              : 8;   // 15: 8
	UINT32 user_ctrl_r_offset              : 8;   // 23:16
} L9A0_PE1_R_WB_CTRL_03_T;

typedef struct { // 0x36f0
	UINT32 pxl_rep_xpos                    : 11;  // 10: 0
	UINT32                                 : 1;   //    11
	UINT32 lut_wmask_g                     : 1;   //    12
	UINT32 lut_wmask_b                     : 1;   //    13
	UINT32 lut_wmask_r                     : 1;   //    14
	UINT32                                 : 1;   //    15
	UINT32 pxl_rep_ypos                    : 11;  // 26:16
	UINT32 pxl_rep_area                    : 1;   //    27
	UINT32 pxl_rep_disable_g               : 1;   //    28
	UINT32 pxl_rep_disable_b               : 1;   //    29
	UINT32 pxl_rep_disable_r               : 1;   //    30
	UINT32 pxl_rep_enable                  : 1;   //    31
} L9A0_PE1_R_GMC_CTRL_00_T;

typedef struct { // 0x36f4
	UINT32 pxl_rep_width                   : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 pxl_rep_height                  : 11;  // 26:16
} L9A0_PE1_R_GMC_CTRL_01_T;

typedef struct { // 0x36f8
	UINT32 pxl_rep_value_g                 : 10;  //  9: 0
	UINT32 pxl_rep_value_b                 : 10;  // 19:10
	UINT32 pxl_rep_value_r                 : 10;  // 29:20
	UINT32 gmc_mode                        : 2;   // 31:30
} L9A0_PE1_R_GMC_CTRL_02_T;

typedef struct { // 0x36fc
	UINT32 capture_addr                    : 10;  //  9: 0
	UINT32                                 : 2;   // 11:10
	UINT32 capture_ai                      : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 capture_num                     : 11;  // 26:16
} L9A0_PE1_R_GMC_IA_CTRL_T;

typedef struct { // 0x3700
	UINT32 lut_data_g                      : 10;  //  9: 0
	UINT32 lut_data_b                      : 10;  // 19:10
	UINT32 lut_data_r                      : 10;  // 29:20
	UINT32 capture_stat_started            : 1;   //    30
	UINT32 capture_stat_ended              : 1;   //    31
} L9A0_PE1_R_GMC_IA_DATA_T;

typedef struct { // 0x3704
	UINT32 dither_en                       : 1;   //     0
	UINT32 dcountour_en                    : 1;   //     1
	UINT32                                 : 1;   //     2
	UINT32 bit_mode_8                      : 1;   //     3
	UINT32                                 : 4;   //  7: 4
	UINT32 decontour_gain_r                : 8;   // 15: 8
	UINT32 decontour_gain_g                : 8;   // 23:16
	UINT32 decontour_gain_b                : 8;   // 31:24
} L9A0_PE1_R_GMC_CTRL_03_T;

typedef struct { // 0x3720
	UINT32 outmux_debugmap_                : 4;   //  3: 0
	UINT32 iir                             : 4;   //  7: 4
	UINT32 i_score                         : 8;   // 15: 8
	UINT32 v_score                         : 8;   // 23:16
	UINT32 l_score                         : 8;   // 31:24
} L9A0_PE1_R_SQM_CTRL_0_T;

typedef struct { // 0x3724
	UINT32 v_limit                         : 8;   //  7: 0
	UINT32 l_limit                         : 8;   // 15: 8
	UINT32 score_threshold                 : 8;   // 23:16
	UINT32 flat_threshold                  : 8;   // 31:24
} L9A0_PE1_R_SQM_CTRL_1_T;

typedef struct { // 0x3728
	UINT32 win_x0                          : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_y0                          : 11;  // 26:16
} L9A0_PE1_R_SQM_CTRL_2_T;

typedef struct { // 0x372c
	UINT32 win_x1                          : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 win_y1                          : 11;  // 26:16
} L9A0_PE1_R_SQM_CTRL_3_T;

typedef struct { // 0x3730
	UINT32 charcter_delta_limit            : 8;   //  7: 0
	UINT32 boundary_width                  : 8;   // 15: 8
	UINT32 video_height                    : 8;   // 23:16
} L9A0_PE1_R_SQM_CTRL_4_T;

typedef struct { // 0x3734
	UINT32 pc_threshold                    : 8;   //  7: 0
	UINT32 pc_delta_limit                  : 8;   // 15: 8
	UINT32 pc_pixel_minimal_limit          : 8;   // 23:16
} L9A0_PE1_R_SQM_CTRL_5_T;

typedef struct { // 0x3738
	UINT32 pe1_r_sqm_stat_f                : 32;   // 31: 0
} L9A0_PE1_R_SQM_STAT_T;

typedef struct { // 0x3750
	UINT32 black_boundary_detection_enable : 1;   //     0
	UINT32 hysterisis_mode                 : 3;   //  3: 1
	UINT32                                 : 3;   //  6: 4
	UINT32 mode_selection                  : 1;   //     7
	UINT32 cnt_th                          : 8;   // 15: 8
	UINT32 diff_th                         : 8;   // 23:16
	UINT32 vcnt                            : 8;   // 31:24
} L9A0_PE1_R_BBD2D_CTRL_0_T;

typedef struct { // 0x3754
	UINT32 bbd_x0                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y0                          : 12;  // 27:16
} L9A0_PE1_R_BBD2D_CTRL_1_T;

typedef struct { // 0x3758
	UINT32 bbd_x1                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y1                          : 12;  // 27:16
} L9A0_PE1_R_BBD2D_CTRL_2_T;

typedef struct { // 0x375c
	UINT32 x0                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y0                              : 12;  // 27:16
} L9A0_PE1_R_BBD2D_STAT_0_T;

typedef struct { // 0x3760
	UINT32 x1                              : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y1                              : 12;  // 27:16
} L9A0_PE1_R_BBD2D_STAT_1_T;

typedef struct { // 0x3770
	UINT32 black_boundary_detection_enable : 1;   //     0
	UINT32 hysterisis_mode                 : 3;   //  3: 1
	UINT32 pe1_3d_type                     : 3;   //  6: 4
	UINT32 mode_selection                  : 1;   //     7
	UINT32 cnt_th                          : 8;   // 15: 8
	UINT32 diff_th                         : 8;   // 23:16
	UINT32 vcnt                            : 8;   // 31:24
} L9A0_PE1_R_BBD3D_CTRL_00_T;

typedef struct { // 0x3774
	UINT32 bbd_x0                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y0                          : 12;  // 27:16
	UINT32 bbd_read_control                : 2;   // 29:28
} L9A0_PE1_R_BBD3D_CTRL_01_T;

typedef struct { // 0x3778
	UINT32 bbd_x1                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 bbd_y1                          : 12;  // 27:16
} L9A0_PE1_R_BBD3D_CTRL_02_T;

typedef struct { // 0x377c
	UINT32 x                               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y                               : 12;  // 27:16
} L9A0_PE1_R_BBD3D_STAT_0_T;

typedef struct {
	L9A0_PE1_L_TOP_CTRL_00_T            pe1_l_top_ctrl_00;                   // 0x1300
	L9A0_PE1_L_TOP_CTRL_01_T            pe1_l_top_ctrl_01;                   // 0x1304
	L9A0_PE1_L_TOP_CTRL_02_T            pe1_l_top_ctrl_02;                   // 0x1308
	L9A0_PE1_L_TOP_CTRL_03_T            pe1_l_top_ctrl_03;                   // 0x130c
	UINT32                              reserved0[4];                        // 0x1310~0x131c
	L9A0_PE1_L_WIN_CTRL_00_T            pe1_l_win_ctrl_00;                   // 0x1320
	L9A0_PE1_L_WIN_CTRL_01_T            pe1_l_win_ctrl_01;                   // 0x1324
	L9A0_PE1_L_WIN_CTRL_02_T            pe1_l_win_ctrl_02;                   // 0x1328
	L9A0_PE1_L_WIN_CTRL_03_T            pe1_l_win_ctrl_03;                   // 0x132c
	L9A0_PE1_L_WIN_CTRL_04_T            pe1_l_win_ctrl_04;                   // 0x1330
	UINT32                              reserved1[7];                        // 0x1334~0x134c
	L9A0_PE1_L_APL_CTRL_00_T            pe1_l_apl_ctrl_00;                   // 0x1350
	L9A0_PE1_L_APL_CTRL_01_T            pe1_l_apl_ctrl_01;                   // 0x1354
	L9A0_PE1_L_APL_CTRL_02_T            pe1_l_apl_ctrl_02;                   // 0x1358
	L9A0_PE1_L_APL_CTRL_03_T            pe1_l_apl_ctrl_03;                   // 0x135c
	L9A0_PE1_L_APL_CTRL_04_T            pe1_l_apl_ctrl_04;                   // 0x1360
	UINT32                              reserved2[3];                        // 0x1364~0x136c
	L9A0_PE1_L_TPG_CTRL_00_T            pe1_l_tpg_ctrl_00;                   // 0x1370
	L9A0_PE1_L_TPG_CTRL_01_T            pe1_l_tpg_ctrl_01;                   // 0x1374
	L9A0_PE1_L_TPG_CTRL_02_T            pe1_l_tpg_ctrl_02;                   // 0x1378
	L9A0_PE1_L_TPG_IA_CTRL_T            pe1_l_tpg_ia_ctrl;                   // 0x137c
	L9A0_PE1_L_TPG_IA_DATA_T            pe1_l_tpg_ia_data;                   // 0x1380
	UINT32                              reserved3[7];                        // 0x1384~0x139c
	L9A0_PE1_L_FILM_CTRL_00_T           pe1_l_film_ctrl_00;                  // 0x13a0
	L9A0_PE1_L_FILM_CTRL_01_T           pe1_l_film_ctrl_01;                  // 0x13a4
	L9A0_PE1_L_FILM_CTRL_02_T           pe1_l_film_ctrl_02;                  // 0x13a8
	UINT32                              reserved4[5];                        // 0x13ac~0x13bc
	L9A0_PE1_L_HFNR_CTRL_00_T           pe1_l_hfnr_ctrl_00;                  // 0x13c0
	L9A0_PE1_L_HFNR_CTRL_01_T           pe1_l_hfnr_ctrl_01;                  // 0x13c4
	UINT32                              reserved5[2];                        // 0x13c8~0x13cc
	L9A0_PE1_L_LSR_CTRL_00_T            pe1_l_lsr_ctrl_00;                   // 0x13d0
	L9A0_PE1_L_LSR_CTRL_01_T            pe1_l_lsr_ctrl_01;                   // 0x13d4
	L9A0_PE1_L_LSR_CTRL_02_T            pe1_l_lsr_ctrl_02;                   // 0x13d8
	L9A0_PE1_L_LSR_CTRL_03_T            pe1_l_lsr_ctrl_03;                   // 0x13dc
	L9A0_PE1_L_LSR_CTRL_04_T            pe1_l_lsr_ctrl_04;                   // 0x13e0
	L9A0_PE1_L_LSR_CTRL_05_T            pe1_l_lsr_ctrl_05;                   // 0x13e4
	L9A0_PE1_L_LSR_CTRL_06_T            pe1_l_lsr_ctrl_06;                   // 0x13e8
	L9A0_PE1_L_LSR_CTRL_07_T            pe1_l_lsr_ctrl_07;                   // 0x13ec
	L9A0_PE1_L_LSR_CTRL_08_T            pe1_l_lsr_ctrl_08;                   // 0x13f0
	L9A0_PE1_L_LSR_CTRL_09_T            pe1_l_lsr_ctrl_09;                   // 0x13f4
	UINT32                              reserved6[2];                        // 0x13f8~0x13fc
	L9A0_PE1_L_DER_CTRL_0_T             pe1_l_der_ctrl_0;                    // 0x1400
	L9A0_PE1_L_DER_CTRL_1_T             pe1_l_der_ctrl_1;                    // 0x1404
	UINT32                              reserved7[2];                        // 0x1408~0x140c
	L9A0_PE1_L_LSR_DTL_CTRL_00_T        pe1_l_lsr_dtl_ctrl_00;               // 0x1410
	L9A0_PE1_L_LSR_DTL_CTRL_01_T        pe1_l_lsr_dtl_ctrl_01;               // 0x1414
	L9A0_PE1_L_LSR_DTL_CTRL_02_T        pe1_l_lsr_dtl_ctrl_02;               // 0x1418
	L9A0_PE1_L_LSR_DTL_CTRL_03_T        pe1_l_lsr_dtl_ctrl_03;               // 0x141c
	L9A0_PE1_L_LSR_DTL_CTRL_04_T        pe1_l_lsr_dtl_ctrl_04;               // 0x1420
	L9A0_PE1_L_LSR_DTL_CTRL_05_T        pe1_l_lsr_dtl_ctrl_05;               // 0x1424
	L9A0_PE1_L_LSR_DTL_CTRL_06_T        pe1_l_lsr_dtl_ctrl_06;               // 0x1428
	L9A0_PE1_L_LSR_DTL_CTRL_07_T        pe1_l_lsr_dtl_ctrl_07;               // 0x142c
	L9A0_PE1_L_LSR_DTL_CTRL_08_T        pe1_l_lsr_dtl_ctrl_08;               // 0x1430
	L9A0_PE1_L_LSR_DTL_CTRL_09_T        pe1_l_lsr_dtl_ctrl_09;               // 0x1434
	L9A0_PE1_L_LSR_DTL_CTRL_0A_T        pe1_l_lsr_dtl_ctrl_0a;               // 0x1438
	L9A0_PE1_L_LSR_DTL_CTRL_0B_T        pe1_l_lsr_dtl_ctrl_0b;               // 0x143c
	L9A0_PE1_L_LSR_DTL_CTRL_0C_T        pe1_l_lsr_dtl_ctrl_0c;               // 0x1440
	L9A0_PE1_L_LSR_DTL_CTRL_0D_T        pe1_l_lsr_dtl_ctrl_0d;               // 0x1444
	UINT32                              reserved8[2];                        // 0x1448~0x144c
	L9A0_PE1_L_LSR_DTL_EE_CTRL_00_T     pe1_l_lsr_dtl_ee_ctrl_00;            // 0x1450
	L9A0_PE1_L_LSR_DTL_EE_CTRL_01_T     pe1_l_lsr_dtl_ee_ctrl_01;            // 0x1454
	L9A0_PE1_L_LSR_DTL_EE_CTRL_02_T     pe1_l_lsr_dtl_ee_ctrl_02;            // 0x1458
	L9A0_PE1_L_LSR_DTL_EE_CTRL_03_T     pe1_l_lsr_dtl_ee_ctrl_03;            // 0x145c
	L9A0_PE1_L_LSR_DTL_EE_CTRL_04_T     pe1_l_lsr_dtl_ee_ctrl_04;            // 0x1460
	L9A0_PE1_L_LSR_DTL_EE_CTRL_05_T     pe1_l_lsr_dtl_ee_ctrl_05;            // 0x1464
	UINT32                              reserved9[2];                        // 0x1468~0x146c
	L9A0_PE1_L_LSR_GT_CTRL_00_T         pe1_l_lsr_gt_ctrl_00;                // 0x1470
	L9A0_PE1_L_LSR_GT_CTRL_01_T         pe1_l_lsr_gt_ctrl_01;                // 0x1474
	L9A0_PE1_L_LSR_GT_CTRL_02_T         pe1_l_lsr_gt_ctrl_02;                // 0x1478
	L9A0_PE1_L_LSR_GT_CTRL_03_T         pe1_l_lsr_gt_ctrl_03;                // 0x147c
	L9A0_PE1_L_LSR_GT_CTRL_04_T         pe1_l_lsr_gt_ctrl_04;                // 0x1480
	L9A0_PE1_L_LSR_GT_IA_CTRL_T         pe1_l_lsr_gt_ia_ctrl;                // 0x1484
	L9A0_PE1_L_LSR_GT_IA_DATA_T         pe1_l_lsr_gt_ia_data;                // 0x1488
	UINT32                              reserved10[5];                       // 0x148c~0x149c
	L9A0_PE1_L_LSR_SCA_CTRL_00_T        pe1_l_lsr_sca_ctrl_00;               // 0x14a0
	L9A0_PE1_L_LSR_SCA_CTRL_01_T        pe1_l_lsr_sca_ctrl_01;               // 0x14a4
	L9A0_PE1_L_LSR_SCA_CTRL_02_T        pe1_l_lsr_sca_ctrl_02;               // 0x14a8
	L9A0_PE1_L_LSR_SCA_CTRL_03_T        pe1_l_lsr_sca_ctrl_03;               // 0x14ac
	L9A0_PE1_L_LSR_SCA_CTRL_04_T        pe1_l_lsr_sca_ctrl_04;               // 0x14b0
	L9A0_PE1_L_LSR_SCA_CTRL_05_T        pe1_l_lsr_sca_ctrl_05;               // 0x14b4
	L9A0_PE1_L_LSR_SCA_CTRL_06_T        pe1_l_lsr_sca_ctrl_06;               // 0x14b8
	L9A0_PE1_L_LSR_SCA_CTRL_07_T        pe1_l_lsr_sca_ctrl_07;               // 0x14bc
	L9A0_PE1_L_LSR_SCA_CTRL_08_T        pe1_l_lsr_sca_ctrl_08;               // 0x14c0
	L9A0_PE1_L_LSR_SCA_CTRL_09_T        pe1_l_lsr_sca_ctrl_09;               // 0x14c4
	L9A0_PE1_L_LSR_SCA_CTRL_0A_T        pe1_l_lsr_sca_ctrl_0a;               // 0x14c8
	L9A0_PE1_L_LSR_SCA_IA_CTRL_T        pe1_l_lsr_sca_ia_ctrl;               // 0x14cc
	L9A0_PE1_L_LSR_SCA_IA_DATA_T        pe1_l_lsr_sca_ia_data;               // 0x14d0
	UINT32                              reserved11[3];                       // 0x14d4~0x14dc
	L9A0_PE1_L_LSR_CRG_IA_CTRL_T        pe1_l_lsr_crg_ia_ctrl;               // 0x14e0
	L9A0_PE1_L_LSR_CRG_IA_DATA_T        pe1_l_lsr_crg_ia_data;               // 0x14e4
	UINT32                              reserved12[2];                       // 0x14e8~0x14ec
	L9A0_PE1_L_SHP_EDGE_CTRL_00_T       pe1_l_shp_edge_ctrl_00;              // 0x14f0
	L9A0_PE1_L_SHP_EDGE_CTRL_01_T       pe1_l_shp_edge_ctrl_01;              // 0x14f4
	L9A0_PE1_L_SHP_EDGE_CTRL_02_T       pe1_l_shp_edge_ctrl_02;              // 0x14f8
	L9A0_PE1_L_SHP_EDGE_CTRL_03_T       pe1_l_shp_edge_ctrl_03;              // 0x14fc
	L9A0_PE1_L_SHP_EDGE_CTRL_04_T       pe1_l_shp_edge_ctrl_04;              // 0x1500
	UINT32                              reserved13;                          // 0x1504
	L9A0_PE1_L_SHP_EDGE_CTRL_05_T       pe1_l_shp_edge_ctrl_05;              // 0x1508
	L9A0_PE1_L_SHP_EDGE_CTRL_06_T       pe1_l_shp_edge_ctrl_06;              // 0x150c
	L9A0_PE1_L_SHP_EDGE_CTRL_07_T       pe1_l_shp_edge_ctrl_07;              // 0x1510
	L9A0_PE1_L_SHP_EDGE_CTRL_08_T       pe1_l_shp_edge_ctrl_08;              // 0x1514
	UINT32                              reserved14[2];                       // 0x1518~0x151c
	L9A0_PE1_L_CTI_CTRL_00_T            pe1_l_cti_ctrl_00;                   // 0x1520
	L9A0_PE1_L_CTI_CTRL_01_T            pe1_l_cti_ctrl_01;                   // 0x1524
	L9A0_PE1_L_CTI_CTRL_02_T            pe1_l_cti_ctrl_02;                   // 0x1528
	UINT32                              reserved15;                          // 0x152c
	L9A0_PE1_L_SHP_UM_CTRL_0_T          pe1_l_shp_um_ctrl_0;                 // 0x1530
	L9A0_PE1_L_SHP_UM_CTRL_1_T          pe1_l_shp_um_ctrl_1;                 // 0x1534
	L9A0_PE1_L_SHP_UM_CTRL_2_T          pe1_l_shp_um_ctrl_2;                 // 0x1538
	L9A0_PE1_L_SHP_UM_CTRL_3_T          pe1_l_shp_um_ctrl_3;                 // 0x153c
	L9A0_PE1_L_SHP_UM_CTRL_4_T          pe1_l_shp_um_ctrl_4;                 // 0x1540
	L9A0_PE1_L_SHP_UM_CTRL_5_T          pe1_l_shp_um_ctrl_5;                 // 0x1544
	L9A0_PE1_L_SHP_UM_CTRL_6_T          pe1_l_shp_um_ctrl_6;                 // 0x1548
	L9A0_PE1_L_SHP_UM_CTRL_7_T          pe1_l_shp_um_ctrl_7;                 // 0x154c
	L9A0_PE1_L_SHP_BLUR_CTRL_T          pe1_l_shp_blur_ctrl;                 // 0x1550
	UINT32                              reserved16[3];                       // 0x1554~0x155c
	L9A0_PE1_L_SHP_SUM_CTRL_T           pe1_l_shp_sum_ctrl;                  // 0x1560
	UINT32                              reserved17[3];                       // 0x1564~0x156c
	L9A0_PE1_L_TI_CTRL_0_T              pe1_l_ti_ctrl_0;                     // 0x1570
	L9A0_PE1_L_TI_CTRL_1_T              pe1_l_ti_ctrl_1;                     // 0x1574
	L9A0_PE1_L_TI_CTRL_2_T              pe1_l_ti_ctrl_2;                     // 0x1578
	L9A0_PE1_L_TI_CTRL_3_T              pe1_l_ti_ctrl_3;                     // 0x157c
	L9A0_PE1_L_TI_CTRL_4_T              pe1_l_ti_ctrl_4;                     // 0x1580
	L9A0_PE1_L_TI_CTRL_5_T              pe1_l_ti_ctrl_5;                     // 0x1584
	UINT32                              reserved18[2];                       // 0x1588~0x158c
	L9A0_PE1_L_DJ_CTRL_00_T             pe1_l_dj_ctrl_00;                    // 0x1590
	L9A0_PE1_L_DJ_CTRL_01_T             pe1_l_dj_ctrl_01;                    // 0x1594
	L9A0_PE1_L_DJ_CTRL_02_T             pe1_l_dj_ctrl_02;                    // 0x1598
	L9A0_PE1_L_DJ_CTRL_03_T             pe1_l_dj_ctrl_03;                    // 0x159c
	UINT32                              reserved19[4];                       // 0x15a0~0x15ac
	L9A0_PE1_L_VSP_CTRL_00_T            pe1_l_vsp_ctrl_00;                   // 0x15b0
	UINT32                              reserved20[3];                       // 0x15b4~0x15bc
	L9A0_PE1_L_XVY_CTRL_00_T            pe1_l_xvy_ctrl_00;                   // 0x15c0
	L9A0_PE1_L_XVY_CTRL_01_T            pe1_l_xvy_ctrl_01;                   // 0x15c4
	L9A0_PE1_L_XVY_CTRL_02_T            pe1_l_xvy_ctrl_02;                   // 0x15c8
	L9A0_PE1_L_XVY_CTRL_03_T            pe1_l_xvy_ctrl_03;                   // 0x15cc
	L9A0_PE1_L_XVY_CTRL_04_T            pe1_l_xvy_ctrl_04;                   // 0x15d0
	L9A0_PE1_L_XVY_CTRL_05_T            pe1_l_xvy_ctrl_05;                   // 0x15d4
	L9A0_PE1_L_XVY_CTRL_06_T            pe1_l_xvy_ctrl_06;                   // 0x15d8
	L9A0_PE1_L_XVY_CTRL_07_T            pe1_l_xvy_ctrl_07;                   // 0x15dc
	L9A0_PE1_L_XVY_CTRL_08_T            pe1_l_xvy_ctrl_08;                   // 0x15e0
	L9A0_PE1_L_XVY_CTRL_09_T            pe1_l_xvy_ctrl_09;                   // 0x15e4
	L9A0_PE1_L_XVY_CTRL_0A_T            pe1_l_xvy_ctrl_0a;                   // 0x15e8
	L9A0_PE1_L_XVY_CTRL_0B_T            pe1_l_xvy_ctrl_0b;                   // 0x15ec
	L9A0_PE1_L_XVY_CTRL_0C_T            pe1_l_xvy_ctrl_0c;                   // 0x15f0
	L9A0_PE1_L_XVY_CTRL_0D_T            pe1_l_xvy_ctrl_0d;                   // 0x15f4
	UINT32                              reserved21[2];                       // 0x15f8~0x15fc
	L9A0_PE1_L_CEN_CTRL_00_T            pe1_l_cen_ctrl_00;                   // 0x1600
	L9A0_PE1_L_CEN_CTRL_01_T            pe1_l_cen_ctrl_01;                   // 0x1604
	L9A0_PE1_L_CEN_CTRL_02_T            pe1_l_cen_ctrl_02;                   // 0x1608
	L9A0_PE1_L_CEN_CTRL_03_T            pe1_l_cen_ctrl_03;                   // 0x160c
	L9A0_PE1_L_CEN_CTRL_04_T            pe1_l_cen_ctrl_04;                   // 0x1610
	L9A0_PE1_L_CEN_IA_CTRL_T            pe1_l_cen_ia_ctrl;                   // 0x1614
	L9A0_PE1_L_CEN_IA_DATA_T            pe1_l_cen_ia_data;                   // 0x1618
	UINT32                              reserved22[5];                       // 0x161c~0x162c
	L9A0_PE1_L_LRCR_CTRL_00_T           pe1_l_lrcr_ctrl_00;                  // 0x1630
	L9A0_PE1_L_LRCR_CTRL_01_T           pe1_l_lrcr_ctrl_01;                  // 0x1634
	L9A0_PE1_L_LRCR_CTRL_02_T           pe1_l_lrcr_ctrl_02;                  // 0x1638
	L9A0_PE1_L_LRCR_CTRL_03_T           pe1_l_lrcr_ctrl_03;                  // 0x163c
	L9A0_PE1_L_LRCR_CTRL_04_T           pe1_l_lrcr_ctrl_04;                  // 0x1640
	L9A0_PE1_L_LRCR_CTRL_05_T           pe1_l_lrcr_ctrl_05;                  // 0x1644
	L9A0_PE1_L_LRCR_CTRL_06_T           pe1_l_lrcr_ctrl_06;                  // 0x1648
	L9A0_PE1_L_LRCR_CTRL_07_T           pe1_l_lrcr_ctrl_07;                  // 0x164c
	L9A0_PE1_L_LRCR_STAT_00_T           pe1_l_lrcr_stat_00;                  // 0x1650
	L9A0_PE1_L_LRCR_STAT_01_T           pe1_l_lrcr_stat_01;                  // 0x1654
	L9A0_PE1_L_LRCR_STAT_02_T           pe1_l_lrcr_stat_02;                  // 0x1658
	UINT32                              reserved23[5];                       // 0x165c~0x166c
	L9A0_PE1_L_DCE_CTRL_00_T            pe1_l_dce_ctrl_00;                   // 0x1670
	L9A0_PE1_L_DCE_CTRL_01_T            pe1_l_dce_ctrl_01;                   // 0x1674
	L9A0_PE1_L_DCE_CTRL_02_T            pe1_l_dce_ctrl_02;                   // 0x1678
	L9A0_PE1_L_DCE_CTRL_03_T            pe1_l_dce_ctrl_03;                   // 0x167c
	L9A0_PE1_L_DCE_CTRL_04_T            pe1_l_dce_ctrl_04;                   // 0x1680
	L9A0_PE1_L_DCE_CTRL_05_T            pe1_l_dce_ctrl_05;                   // 0x1684
	L9A0_PE1_L_DCE_IA_CTRL_T            pe1_l_dce_ia_ctrl;                   // 0x1688
	L9A0_PE1_L_DCE_IA_DATA_T            pe1_l_dce_ia_data;                   // 0x168c
	L9A0_PE1_L_DCE_CTRL_08_T            pe1_l_dce_ctrl_08;                   // 0x1690
	UINT32                              reserved24[3];                       // 0x1694~0x169c
	L9A0_PE1_L_DCE_HIST_IA_CTRL_T       pe1_l_dce_hist_ia_ctrl;              // 0x16a0
	L9A0_PE1_L_DCE_HIST_IA_DATA1_T      pe1_l_dce_hist_ia_data1;             // 0x16a4
	L9A0_PE1_L_DCE_HSIT_IA_DATA2_T      pe1_l_dce_hsit_ia_data2;             // 0x16a8
	UINT32                              reserved25[5];                       // 0x16ac~0x16bc
	L9A0_PE1_L_WB_CTRL_00_T             pe1_l_wb_ctrl_00;                    // 0x16c0
	L9A0_PE1_L_WB_CTRL_01_T             pe1_l_wb_ctrl_01;                    // 0x16c4
	L9A0_PE1_L_WB_CTRL_02_T             pe1_l_wb_ctrl_02;                    // 0x16c8
	L9A0_PE1_L_WB_CTRL_03_T             pe1_l_wb_ctrl_03;                    // 0x16cc
	UINT32                              reserved26[8];                       // 0x16d0~0x16ec
	L9A0_PE1_L_GMC_CTRL_00_T            pe1_l_gmc_ctrl_00;                   // 0x16f0
	L9A0_PE1_L_GMC_CTRL_01_T            pe1_l_gmc_ctrl_01;                   // 0x16f4
	L9A0_PE1_L_GMC_CTRL_02_T            pe1_l_gmc_ctrl_02;                   // 0x16f8
	L9A0_PE1_L_GMC_IA_CTRL_T            pe1_l_gmc_ia_ctrl;                   // 0x16fc
	L9A0_PE1_L_GMC_IA_DATA_T            pe1_l_gmc_ia_data;                   // 0x1700
	L9A0_PE1_L_GMC_CTRL_03_T            pe1_l_gmc_ctrl_03;                   // 0x1704
	UINT32                              reserved27[6];                       // 0x1708~0x171c
	L9A0_PE1_L_SQM_CTRL_0_T             pe1_l_sqm_ctrl_0;                    // 0x1720
	L9A0_PE1_L_SQM_CTRL_1_T             pe1_l_sqm_ctrl_1;                    // 0x1724
	L9A0_PE1_L_SQM_CTRL_2_T             pe1_l_sqm_ctrl_2;                    // 0x1728
	L9A0_PE1_L_SQM_CTRL_3_T             pe1_l_sqm_ctrl_3;                    // 0x172c
	L9A0_PE1_L_SQM_CTRL_4_T             pe1_l_sqm_ctrl_4;                    // 0x1730
	L9A0_PE1_L_SQM_CTRL_5_T             pe1_l_sqm_ctrl_5;                    // 0x1734
	L9A0_PE1_L_SQM_STAT_T               pe1_l_sqm_stat;                      // 0x1738
	UINT32                              reserved28[5];                       // 0x173c~0x174c
	L9A0_PE1_L_BBD2D_CTRL_0_T           pe1_l_bbd2d_ctrl_0;                  // 0x1750
	L9A0_PE1_L_BBD2D_CTRL_1_T           pe1_l_bbd2d_ctrl_1;                  // 0x1754
	L9A0_PE1_L_BBD2D_CTRL_2_T           pe1_l_bbd2d_ctrl_2;                  // 0x1758
	L9A0_PE1_L_BBD2D_STAT_0_T           pe1_l_bbd2d_stat_0;                  // 0x175c
	L9A0_PE1_L_BBD2D_STAT_1_T           pe1_l_bbd2d_stat_1;                  // 0x1760
	UINT32                              reserved29[3];                       // 0x1764~0x176c
	L9A0_PE1_L_BBD3D_CTRL_00_T          pe1_l_bbd3d_ctrl_00;                 // 0x1770
	L9A0_PE1_L_BBD3D_CTRL_01_T          pe1_l_bbd3d_ctrl_01;                 // 0x1774
	L9A0_PE1_L_BBD3D_CTRL_02_T          pe1_l_bbd3d_ctrl_02;                 // 0x1778
	L9A0_PE1_L_BBD3D_STAT_0_T           pe1_l_bbd3d_stat_0;                  // 0x177c
} DE_P1L_REG_L9A0_T;

typedef struct {
	L9A0_PE1_R_TOP_CTRL_00_T            pe1_r_top_ctrl_00;                   // 0x3300
	L9A0_PE1_R_TOP_CTRL_01_T            pe1_r_top_ctrl_01;                   // 0x3304
	L9A0_PE1_R_TOP_CTRL_02_T            pe1_r_top_ctrl_02;                   // 0x3308
	L9A0_PE1_R_TOP_CTRL_03_T            pe1_r_top_ctrl_03;                   // 0x330c
	UINT32                              reserved30[4];                       // 0x3310~0x331c
	L9A0_PE1_R_WIN_CTRL_00_T            pe1_r_win_ctrl_00;                   // 0x3320
	L9A0_PE1_R_WIN_CTRL_01_T            pe1_r_win_ctrl_01;                   // 0x3324
	L9A0_PE1_R_WIN_CTRL_02_T            pe1_r_win_ctrl_02;                   // 0x3328
	L9A0_PE1_R_WIN_CTRL_03_T            pe1_r_win_ctrl_03;                   // 0x332c
	L9A0_PE1_R_WIN_CTRL_04_T            pe1_r_win_ctrl_04;                   // 0x3330
	UINT32                              reserved31[7];                       // 0x3334~0x334c
	L9A0_PE1_R_APL_CTRL_00_T            pe1_r_apl_ctrl_00;                   // 0x3350
	L9A0_PE1_R_APL_CTRL_01_T            pe1_r_apl_ctrl_01;                   // 0x3354
	L9A0_PE1_R_APL_CTRL_02_T            pe1_r_apl_ctrl_02;                   // 0x3358
	L9A0_PE1_R_APL_CTRL_03_T            pe1_r_apl_ctrl_03;                   // 0x335c
	L9A0_PE1_R_APL_CTRL_04_T            pe1_r_apl_ctrl_04;                   // 0x3360
	UINT32                              reserved32[3];                       // 0x3364~0x336c
	L9A0_PE1_R_TPG_CTRL_00_T            pe1_r_tpg_ctrl_00;                   // 0x3370
	L9A0_PE1_R_TPG_CTRL_01_T            pe1_r_tpg_ctrl_01;                   // 0x3374
	L9A0_PE1_R_TPG_CTRL_02_T            pe1_r_tpg_ctrl_02;                   // 0x3378
	L9A0_PE1_R_TPG_IA_CTRL_T            pe1_r_tpg_ia_ctrl;                   // 0x337c
	L9A0_PE1_R_TPG_IA_DATA_T            pe1_r_tpg_ia_data;                   // 0x3380
	UINT32                              reserved33[7];                       // 0x3384~0x339c
	L9A0_PE1_R_FILM_CTRL_00_T           pe1_r_film_ctrl_00;                  // 0x33a0
	L9A0_PE1_R_FILM_CTRL_01_T           pe1_r_film_ctrl_01;                  // 0x33a4
	L9A0_PE1_R_FILM_CTRL_02_T           pe1_r_film_ctrl_02;                  // 0x33a8
	UINT32                              reserved34[5];                       // 0x33ac~0x33bc
	L9A0_PE1_R_HFNR_CTRL_00_T           pe1_r_hfnr_ctrl_00;                  // 0x33c0
	L9A0_PE1_R_HFNR_CTRL_01_T           pe1_r_hfnr_ctrl_01;                  // 0x33c4
	UINT32                              reserved35[2];                       // 0x33c8~0x33cc
	L9A0_PE1_R_LSR_CTRL_00_T            pe1_r_lsr_ctrl_00;                   // 0x33d0
	L9A0_PE1_R_LSR_CTRL_01_T            pe1_r_lsr_ctrl_01;                   // 0x33d4
	L9A0_PE1_R_LSR_CTRL_02_T            pe1_r_lsr_ctrl_02;                   // 0x33d8
	L9A0_PE1_R_LSR_CTRL_03_T            pe1_r_lsr_ctrl_03;                   // 0x33dc
	L9A0_PE1_R_LSR_CTRL_04_T            pe1_r_lsr_ctrl_04;                   // 0x33e0
	L9A0_PE1_R_LSR_CTRL_05_T            pe1_r_lsr_ctrl_05;                   // 0x33e4
	L9A0_PE1_R_LSR_CTRL_06_T            pe1_r_lsr_ctrl_06;                   // 0x33e8
	L9A0_PE1_R_LSR_CTRL_07_T            pe1_r_lsr_ctrl_07;                   // 0x33ec
	L9A0_PE1_R_LSR_CTRL_08_T            pe1_r_lsr_ctrl_08;                   // 0x33f0
	L9A0_PE1_R_LSR_CTRL_09_T            pe1_r_lsr_ctrl_09;                   // 0x33f4
	UINT32                              reserved36[2];                       // 0x33f8~0x33fc
	L9A0_PE1_R_DER_CTRL_0_T             pe1_r_der_ctrl_0;                    // 0x3400
	L9A0_PE1_R_DER_CTRL_1_T             pe1_r_der_ctrl_1;                    // 0x3404
	UINT32                              reserved37[2];                       // 0x3408~0x340c
	L9A0_PE1_R_LSR_DTL_CTRL_00_T        pe1_r_lsr_dtl_ctrl_00;               // 0x3410
	L9A0_PE1_R_LSR_DTL_CTRL_01_T        pe1_r_lsr_dtl_ctrl_01;               // 0x3414
	L9A0_PE1_R_LSR_DTL_CTRL_02_T        pe1_r_lsr_dtl_ctrl_02;               // 0x3418
	L9A0_PE1_R_LSR_DTL_CTRL_03_T        pe1_r_lsr_dtl_ctrl_03;               // 0x341c
	L9A0_PE1_R_LSR_DTL_CTRL_04_T        pe1_r_lsr_dtl_ctrl_04;               // 0x3420
	L9A0_PE1_R_LSR_DTL_CTRL_05_T        pe1_r_lsr_dtl_ctrl_05;               // 0x3424
	L9A0_PE1_R_LSR_DTL_CTRL_06_T        pe1_r_lsr_dtl_ctrl_06;               // 0x3428
	L9A0_PE1_R_LSR_DTL_CTRL_07_T        pe1_r_lsr_dtl_ctrl_07;               // 0x342c
	L9A0_PE1_R_LSR_DTL_CTRL_08_T        pe1_r_lsr_dtl_ctrl_08;               // 0x3430
	L9A0_PE1_R_LSR_DTL_CTRL_09_T        pe1_r_lsr_dtl_ctrl_09;               // 0x3434
	L9A0_PE1_R_LSR_DTL_CTRL_0A_T        pe1_r_lsr_dtl_ctrl_0a;               // 0x3438
	L9A0_PE1_R_LSR_DTL_CTRL_0B_T        pe1_r_lsr_dtl_ctrl_0b;               // 0x343c
	L9A0_PE1_R_LSR_DTL_CTRL_0C_T        pe1_r_lsr_dtl_ctrl_0c;               // 0x3440
	L9A0_PE1_R_LSR_DTL_CTRL_0D_T        pe1_r_lsr_dtl_ctrl_0d;               // 0x3444
	UINT32                              reserved38[2];                       // 0x3448~0x344c
	L9A0_PE1_R_LSR_DTL_EE_CTRL_00_T     pe1_r_lsr_dtl_ee_ctrl_00;            // 0x3450
	L9A0_PE1_R_LSR_DTL_EE_CTRL_01_T     pe1_r_lsr_dtl_ee_ctrl_01;            // 0x3454
	L9A0_PE1_R_LSR_DTL_EE_CTRL_02_T     pe1_r_lsr_dtl_ee_ctrl_02;            // 0x3458
	L9A0_PE1_R_LSR_DTL_EE_CTRL_03_T     pe1_r_lsr_dtl_ee_ctrl_03;            // 0x345c
	L9A0_PE1_R_LSR_DTL_EE_CTRL_04_T     pe1_r_lsr_dtl_ee_ctrl_04;            // 0x3460
	L9A0_PE1_R_LSR_DTL_EE_CTRL_05_T     pe1_r_lsr_dtl_ee_ctrl_05;            // 0x3464
	UINT32                              reserved39[2];                       // 0x3468~0x346c
	L9A0_PE1_R_LSR_GT_CTRL_00_T         pe1_r_lsr_gt_ctrl_00;                // 0x3470
	L9A0_PE1_R_LSR_GT_CTRL_01_T         pe1_r_lsr_gt_ctrl_01;                // 0x3474
	L9A0_PE1_R_LSR_GT_CTRL_02_T         pe1_r_lsr_gt_ctrl_02;                // 0x3478
	L9A0_PE1_R_LSR_GT_CTRL_03_T         pe1_r_lsr_gt_ctrl_03;                // 0x347c
	L9A0_PE1_R_LSR_GT_CTRL_04_T         pe1_r_lsr_gt_ctrl_04;                // 0x3480
	L9A0_PE1_R_LSR_GT_IA_CTRL_T         pe1_r_lsr_gt_ia_ctrl;                // 0x3484
	L9A0_PE1_R_LSR_GT_IA_DATA_T         pe1_r_lsr_gt_ia_data;                // 0x3488
	UINT32                              reserved40[5];                       // 0x348c~0x349c
	L9A0_PE1_R_LSR_SCA_CTRL_00_T        pe1_r_lsr_sca_ctrl_00;               // 0x34a0
	L9A0_PE1_R_LSR_SCA_CTRL_01_T        pe1_r_lsr_sca_ctrl_01;               // 0x34a4
	L9A0_PE1_R_LSR_SCA_CTRL_02_T        pe1_r_lsr_sca_ctrl_02;               // 0x34a8
	L9A0_PE1_R_LSR_SCA_CTRL_03_T        pe1_r_lsr_sca_ctrl_03;               // 0x34ac
	L9A0_PE1_R_LSR_SCA_CTRL_04_T        pe1_r_lsr_sca_ctrl_04;               // 0x34b0
	L9A0_PE1_R_LSR_SCA_CTRL_05_T        pe1_r_lsr_sca_ctrl_05;               // 0x34b4
	L9A0_PE1_R_LSR_SCA_CTRL_06_T        pe1_r_lsr_sca_ctrl_06;               // 0x34b8
	L9A0_PE1_R_LSR_SCA_CTRL_07_T        pe1_r_lsr_sca_ctrl_07;               // 0x34bc
	L9A0_PE1_R_LSR_SCA_CTRL_08_T        pe1_r_lsr_sca_ctrl_08;               // 0x34c0
	L9A0_PE1_R_LSR_SCA_CTRL_09_T        pe1_r_lsr_sca_ctrl_09;               // 0x34c4
	L9A0_PE1_R_LSR_SCA_CTRL_0A_T        pe1_r_lsr_sca_ctrl_0a;               // 0x34c8
	L9A0_PE1_R_LSR_SCA_IA_CTRL_T        pe1_r_lsr_sca_ia_ctrl;               // 0x34cc
	L9A0_PE1_R_LSR_SCA_IA_DATA_T        pe1_r_lsr_sca_ia_data;               // 0x34d0
	UINT32                              reserved41[3];                       // 0x34d4~0x34dc
	L9A0_PE1_R_LSR_CRG_IA_CTRL_T        pe1_r_lsr_crg_ia_ctrl;               // 0x34e0
	L9A0_PE1_R_LSR_CRG_IA_DATA_T        pe1_r_lsr_crg_ia_data;               // 0x34e4
	UINT32                              reserved42[2];                       // 0x34e8~0x34ec
	L9A0_PE1_R_SHP_EDGE_CTRL_00_T       pe1_r_shp_edge_ctrl_00;              // 0x34f0
	L9A0_PE1_R_SHP_EDGE_CTRL_01_T       pe1_r_shp_edge_ctrl_01;              // 0x34f4
	L9A0_PE1_R_SHP_EDGE_CTRL_02_T       pe1_r_shp_edge_ctrl_02;              // 0x34f8
	L9A0_PE1_R_SHP_EDGE_CTRL_03_T       pe1_r_shp_edge_ctrl_03;              // 0x34fc
	L9A0_PE1_R_SHP_EDGE_CTRL_04_T       pe1_r_shp_edge_ctrl_04;              // 0x3500
	UINT32                              reserved43;                          // 0x3504
	L9A0_PE1_R_SHP_EDGE_CTRL_05_T       pe1_r_shp_edge_ctrl_05;              // 0x3508
	L9A0_PE1_R_SHP_EDGE_CTRL_06_T       pe1_r_shp_edge_ctrl_06;              // 0x350c
	L9A0_PE1_R_SHP_EDGE_CTRL_07_T       pe1_r_shp_edge_ctrl_07;              // 0x3510
	L9A0_PE1_R_SHP_EDGE_CTRL_08_T       pe1_r_shp_edge_ctrl_08;              // 0x3514
	UINT32                              reserved44[2];                       // 0x3518~0x351c
	L9A0_PE1_R_CTI_CTRL_00_T            pe1_r_cti_ctrl_00;                   // 0x3520
	L9A0_PE1_R_CTI_CTRL_01_T            pe1_r_cti_ctrl_01;                   // 0x3524
	L9A0_PE1_R_CTI_CTRL_02_T            pe1_r_cti_ctrl_02;                   // 0x3528
	UINT32                              reserved45;                          // 0x352c
	L9A0_PE1_R_SHP_UM_CTRL_0_T          pe1_r_shp_um_ctrl_0;                 // 0x3530
	L9A0_PE1_R_SHP_UM_CTRL_1_T          pe1_r_shp_um_ctrl_1;                 // 0x3534
	L9A0_PE1_R_SHP_UM_CTRL_2_T          pe1_r_shp_um_ctrl_2;                 // 0x3538
	L9A0_PE1_R_SHP_UM_CTRL_3_T          pe1_r_shp_um_ctrl_3;                 // 0x353c
	L9A0_PE1_R_SHP_UM_CTRL_4_T          pe1_r_shp_um_ctrl_4;                 // 0x3540
	L9A0_PE1_R_SHP_UM_CTRL_5_T          pe1_r_shp_um_ctrl_5;                 // 0x3544
	L9A0_PE1_R_SHP_UM_CTRL_6_T          pe1_r_shp_um_ctrl_6;                 // 0x3548
	L9A0_PE1_R_SHP_UM_CTRL_7_T          pe1_r_shp_um_ctrl_7;                 // 0x354c
	L9A0_PE1_R_SHP_BLUR_CTRL_T          pe1_r_shp_blur_ctrl;                 // 0x3550
	UINT32                              reserved46[3];                       // 0x3554~0x355c
	L9A0_PE1_R_SHP_SUM_CTRL_T           pe1_r_shp_sum_ctrl;                  // 0x3560
	UINT32                              reserved47[3];                       // 0x3564~0x356c
	L9A0_PE1_R_TI_CTRL_0_T              pe1_r_ti_ctrl_0;                     // 0x3570
	L9A0_PE1_R_TI_CTRL_1_T              pe1_r_ti_ctrl_1;                     // 0x3574
	L9A0_PE1_R_TI_CTRL_2_T              pe1_r_ti_ctrl_2;                     // 0x3578
	L9A0_PE1_R_TI_CTRL_3_T              pe1_r_ti_ctrl_3;                     // 0x357c
	L9A0_PE1_R_TI_CTRL_4_T              pe1_r_ti_ctrl_4;                     // 0x3580
	L9A0_PE1_R_TI_CTRL_5_T              pe1_r_ti_ctrl_5;                     // 0x3584
	UINT32                              reserved48[2];                       // 0x3588~0x358c
	L9A0_PE1_R_DJ_CTRL_00_T             pe1_r_dj_ctrl_00;                    // 0x3590
	L9A0_PE1_R_DJ_CTRL_01_T             pe1_r_dj_ctrl_01;                    // 0x3594
	L9A0_PE1_R_DJ_CTRL_02_T             pe1_r_dj_ctrl_02;                    // 0x3598
	L9A0_PE1_R_DJ_CTRL_03_T             pe1_r_dj_ctrl_03;                    // 0x359c
	UINT32                              reserved49[4];                       // 0x35a0~0x35ac
	L9A0_PE1_R_VSP_CTRL_00_T            pe1_r_vsp_ctrl_00;                   // 0x35b0
	UINT32                              reserved50[3];                       // 0x35b4~0x35bc
	L9A0_PE1_R_XVY_CTRL_00_T            pe1_r_xvy_ctrl_00;                   // 0x35c0
	L9A0_PE1_R_XVY_CTRL_01_T            pe1_r_xvy_ctrl_01;                   // 0x35c4
	L9A0_PE1_R_XVY_CTRL_02_T            pe1_r_xvy_ctrl_02;                   // 0x35c8
	L9A0_PE1_R_XVY_CTRL_03_T            pe1_r_xvy_ctrl_03;                   // 0x35cc
	L9A0_PE1_R_XVY_CTRL_04_T            pe1_r_xvy_ctrl_04;                   // 0x35d0
	L9A0_PE1_R_XVY_CTRL_05_T            pe1_r_xvy_ctrl_05;                   // 0x35d4
	L9A0_PE1_R_XVY_CTRL_06_T            pe1_r_xvy_ctrl_06;                   // 0x35d8
	L9A0_PE1_R_XVY_CTRL_07_T            pe1_r_xvy_ctrl_07;                   // 0x35dc
	L9A0_PE1_R_XVY_CTRL_08_T            pe1_r_xvy_ctrl_08;                   // 0x35e0
	L9A0_PE1_R_XVY_CTRL_09_T            pe1_r_xvy_ctrl_09;                   // 0x35e4
	L9A0_PE1_R_XVY_CTRL_0A_T            pe1_r_xvy_ctrl_0a;                   // 0x35e8
	L9A0_PE1_R_XVY_CTRL_0B_T            pe1_r_xvy_ctrl_0b;                   // 0x35ec
	L9A0_PE1_R_XVY_CTRL_0C_T            pe1_r_xvy_ctrl_0c;                   // 0x35f0
	L9A0_PE1_R_XVY_CTRL_0D_T            pe1_r_xvy_ctrl_0d;                   // 0x35f4
	UINT32                              reserved51[2];                       // 0x35f8~0x35fc
	L9A0_PE1_R_CEN_CTRL_00_T            pe1_r_cen_ctrl_00;                   // 0x3600
	L9A0_PE1_R_CEN_CTRL_01_T            pe1_r_cen_ctrl_01;                   // 0x3604
	L9A0_PE1_R_CEN_CTRL_02_T            pe1_r_cen_ctrl_02;                   // 0x3608
	L9A0_PE1_R_CEN_CTRL_03_T            pe1_r_cen_ctrl_03;                   // 0x360c
	L9A0_PE1_R_CEN_CTRL_04_T            pe1_r_cen_ctrl_04;                   // 0x3610
	L9A0_PE1_R_CEN_IA_CTRL_T            pe1_r_cen_ia_ctrl;                   // 0x3614
	L9A0_PE1_R_CEN_IA_DATA_T            pe1_r_cen_ia_data;                   // 0x3618
	UINT32                              reserved52[5];                       // 0x361c~0x362c
	L9A0_PE1_R_LRCR_CTRL_00_T           pe1_r_lrcr_ctrl_00;                  // 0x3630
	L9A0_PE1_R_LRCR_CTRL_01_T           pe1_r_lrcr_ctrl_01;                  // 0x3634
	L9A0_PE1_R_LRCR_CTRL_02_T           pe1_r_lrcr_ctrl_02;                  // 0x3638
	L9A0_PE1_R_LRCR_CTRL_03_T           pe1_r_lrcr_ctrl_03;                  // 0x363c
	L9A0_PE1_R_LRCR_CTRL_04_T           pe1_r_lrcr_ctrl_04;                  // 0x3640
	L9A0_PE1_R_LRCR_CTRL_05_T           pe1_r_lrcr_ctrl_05;                  // 0x3644
	L9A0_PE1_R_LRCR_CTRL_06_T           pe1_r_lrcr_ctrl_06;                  // 0x3648
	L9A0_PE1_R_LRCR_CTRL_07_T           pe1_r_lrcr_ctrl_07;                  // 0x364c
	L9A0_PE1_R_LRCR_STAT_00_T           pe1_r_lrcr_stat_00;                  // 0x3650
	L9A0_PE1_R_LRCR_STAT_01_T           pe1_r_lrcr_stat_01;                  // 0x3654
	L9A0_PE1_R_LRCR_STAT_02_T           pe1_r_lrcr_stat_02;                  // 0x3658
	UINT32                              reserved53[5];                       // 0x365c~0x366c
	L9A0_PE1_R_DCE_CTRL_00_T            pe1_r_dce_ctrl_00;                   // 0x3670
	L9A0_PE1_R_DCE_CTRL_01_T            pe1_r_dce_ctrl_01;                   // 0x3674
	L9A0_PE1_R_DCE_CTRL_02_T            pe1_r_dce_ctrl_02;                   // 0x3678
	L9A0_PE1_R_DCE_CTRL_03_T            pe1_r_dce_ctrl_03;                   // 0x367c
	L9A0_PE1_R_DCE_CTRL_04_T            pe1_r_dce_ctrl_04;                   // 0x3680
	L9A0_PE1_R_DCE_CTRL_05_T            pe1_r_dce_ctrl_05;                   // 0x3684
	L9A0_PE1_R_DCE_IA_CTRL_T            pe1_r_dce_ia_ctrl;                   // 0x3688
	L9A0_PE1_R_DCE_IA_DATA_T            pe1_r_dce_ia_data;                   // 0x368c
	L9A0_PE1_R_DCE_CTRL_08_T            pe1_r_dce_ctrl_08;                   // 0x3690
	UINT32                              reserved54[3];                       // 0x3694~0x369c
	L9A0_PE1_R_DCE_HIST_IA_CTRL_T       pe1_r_dce_hist_ia_ctrl;              // 0x36a0
	L9A0_PE1_R_DCE_HIST_IA_DATA1_T      pe1_r_dce_hist_ia_data1;             // 0x36a4
	L9A0_PE1_R_DCE_HSIT_IA_DATA2_T      pe1_r_dce_hsit_ia_data2;             // 0x36a8
	UINT32                              reserved55[5];                       // 0x36ac~0x36bc
	L9A0_PE1_R_WB_CTRL_00_T             pe1_r_wb_ctrl_00;                    // 0x36c0
	L9A0_PE1_R_WB_CTRL_01_T             pe1_r_wb_ctrl_01;                    // 0x36c4
	L9A0_PE1_R_WB_CTRL_02_T             pe1_r_wb_ctrl_02;                    // 0x36c8
	L9A0_PE1_R_WB_CTRL_03_T             pe1_r_wb_ctrl_03;                    // 0x36cc
	UINT32                              reserved56[8];                       // 0x36d0~0x36ec
	L9A0_PE1_R_GMC_CTRL_00_T            pe1_r_gmc_ctrl_00;                   // 0x36f0
	L9A0_PE1_R_GMC_CTRL_01_T            pe1_r_gmc_ctrl_01;                   // 0x36f4
	L9A0_PE1_R_GMC_CTRL_02_T            pe1_r_gmc_ctrl_02;                   // 0x36f8
	L9A0_PE1_R_GMC_IA_CTRL_T            pe1_r_gmc_ia_ctrl;                   // 0x36fc
	L9A0_PE1_R_GMC_IA_DATA_T            pe1_r_gmc_ia_data;                   // 0x3700
	L9A0_PE1_R_GMC_CTRL_03_T            pe1_r_gmc_ctrl_03;                   // 0x3704
	UINT32                              reserved57[6];                       // 0x3708~0x371c
	L9A0_PE1_R_SQM_CTRL_0_T             pe1_r_sqm_ctrl_0;                    // 0x3720
	L9A0_PE1_R_SQM_CTRL_1_T             pe1_r_sqm_ctrl_1;                    // 0x3724
	L9A0_PE1_R_SQM_CTRL_2_T             pe1_r_sqm_ctrl_2;                    // 0x3728
	L9A0_PE1_R_SQM_CTRL_3_T             pe1_r_sqm_ctrl_3;                    // 0x372c
	L9A0_PE1_R_SQM_CTRL_4_T             pe1_r_sqm_ctrl_4;                    // 0x3730
	L9A0_PE1_R_SQM_CTRL_5_T             pe1_r_sqm_ctrl_5;                    // 0x3734
	L9A0_PE1_R_SQM_STAT_T               pe1_r_sqm_stat;                      // 0x3738
	UINT32                              reserved58[5];                       // 0x373c~0x374c
	L9A0_PE1_R_BBD2D_CTRL_0_T           pe1_r_bbd2d_ctrl_0;                  // 0x3750
	L9A0_PE1_R_BBD2D_CTRL_1_T           pe1_r_bbd2d_ctrl_1;                  // 0x3754
	L9A0_PE1_R_BBD2D_CTRL_2_T           pe1_r_bbd2d_ctrl_2;                  // 0x3758
	L9A0_PE1_R_BBD2D_STAT_0_T           pe1_r_bbd2d_stat_0;                  // 0x375c
	L9A0_PE1_R_BBD2D_STAT_1_T           pe1_r_bbd2d_stat_1;                  // 0x3760
	UINT32                              reserved59[3];                       // 0x3764~0x376c
	L9A0_PE1_R_BBD3D_CTRL_00_T          pe1_r_bbd3d_ctrl_00;                 // 0x3770
	L9A0_PE1_R_BBD3D_CTRL_01_T          pe1_r_bbd3d_ctrl_01;                 // 0x3774
	L9A0_PE1_R_BBD3D_CTRL_02_T          pe1_r_bbd3d_ctrl_02;                 // 0x3778
	L9A0_PE1_R_BBD3D_STAT_0_T           pe1_r_bbd3d_stat_0;                  // 0x377c
} DE_P1R_REG_L9A0_T;

#endif
