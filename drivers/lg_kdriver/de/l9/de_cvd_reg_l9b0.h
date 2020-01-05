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

#ifndef _REG_CVD_L9B0_h
#define _REG_CVD_L9B0_h

/*-----------------------------------------------------------------------------
	0x4100 cvd_intr1_enable0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_enable0               : 32;  //  0:31
} L9B0_CVD_INTR1_ENABLE0_T;

/*-----------------------------------------------------------------------------
	0x4104 cvd_intr1_intr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_chromalock_fal              : 1;   //     0
	UINT32 cvd_chromalock_ris              : 1;   //     1
	UINT32 cvd_vlock_fal                   : 1;   //     2
	UINT32 cvd_vlock_ris                   : 1;   //     3
	UINT32 cvd_hlock_fal                   : 1;   //     4
	UINT32 cvd_hlock_ris                   : 1;   //     5
	UINT32 cvd_no_signal_fal               : 1;   //     6
	UINT32 cvd_no_signal_ris               : 1;   //     7
	UINT32 cvd_noburst_detected_fal        : 1;   //     8
	UINT32 cvd_noburst_detected_ris        : 1;   //     9
	UINT32 cvd_vnon_standard_fal           : 1;   //    10
	UINT32 cvd_vnon_standard_ris           : 1;   //    11
	UINT32 cvd_hnon_standard_fal           : 1;   //    12
	UINT32 cvd_hnon_standard_ris           : 1;   //    13
	UINT32 cvd_proscan_detected_fal        : 1;   //    14
	UINT32 cvd_proscan_detected_ris        : 1;   //    15
	UINT32 cvd_vcr_fal                     : 1;   //    16
	UINT32 cvd_vcr_ris                     : 1;   //    17
	UINT32 cvd_noisy_fal                   : 1;   //    18
	UINT32 cvd_noisy_ris                   : 1;   //    19
	UINT32 cvd_vline_625_detected_fal      : 1;   //    20
	UINT32 cvd_vline_625_detected_ris      : 1;   //    21
	UINT32 cvd_secam_detected_fal          : 1;   //    22
	UINT32 cvd_secam_detected_ris          : 1;   //    23
	UINT32 cvd_pal_detected_fal            : 1;   //    24
	UINT32 cvd_pal_detected_ris            : 1;   //    25
	UINT32 cvd_vs_fal                      : 1;   //    26
	UINT32 cvd_vs_ris                      : 1;   //    27
	UINT32 cvd_ext_locked_fal              : 1;   //    28
	UINT32 cvd_ext_locked_ris              : 1;   //    29
} L9B0_CVD_INTR1_INTR0_T;

/*-----------------------------------------------------------------------------
	0x4108 cvd_intr1_clear0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_clear0                : 32;  //  0:31
} L9B0_CVD_INTR1_CLEAR0_T;

/*-----------------------------------------------------------------------------
	0x410c cvd_intr1_enable1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_enable1               : 32;  //  0:31
} L9B0_CVD_INTR1_ENABLE1_T;

/*-----------------------------------------------------------------------------
	0x4110 cvd_intr1_intr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_wss_rdy                     : 1;   //     0
	UINT32 vbi_cc_rdy                      : 1;   //     1
	UINT32 vbi_data_in                     : 1;   //     2
	UINT32 cvd_fb_rst                      : 1;   //     3
	UINT32 cvd_mif_err                     : 1;   //     4
	UINT32 cs_chromalock_fal               : 1;   //     5
	UINT32 cs_chromalock_ris               : 1;   //     6
	UINT32 cs_pal_detected_fal             : 1;   //     7
	UINT32 cs_pal_detected_ris             : 1;   //     8
	UINT32 cs_secam_detected_fal           : 1;   //     9
	UINT32 cs_secam_detected_ris           : 1;   //    10
	UINT32 cs1_chromalock_fal              : 1;   //    11
	UINT32 cs1_chromalock_ris              : 1;   //    12
	UINT32 cs1_pal_detected_fal            : 1;   //    13
	UINT32 cs1_pal_detected_ris            : 1;   //    14
	UINT32 cs1_secam_detected_fal          : 1;   //    15
	UINT32 cs1_secam_detected_ris          : 1;   //    16
	UINT32 estfrdp_err_flag_fal            : 1;   //    17
	UINT32 estfrdp_err_flag_ris            : 1;   //    18
	UINT32 vdetect_vcount_fal              : 1;   //    19
	UINT32 vdetect_vcount_ris              : 1;   //    20
} L9B0_CVD_INTR1_INTR1_T;

/*-----------------------------------------------------------------------------
	0x4114 cvd_intr1_clear1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_clear1                : 32;  //  0:31
} L9B0_CVD_INTR1_CLEAR1_T;

/*-----------------------------------------------------------------------------
	0x4118 cvd_intr2_enable0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_enable0               : 32;  //  0:31
} L9B0_CVD_INTR2_ENABLE0_T;

/*-----------------------------------------------------------------------------
	0x411c cvd_intr2_intr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_chromalock_fal              : 1;   //     0
	UINT32 cvd_chromalock_ris              : 1;   //     1
	UINT32 cvd_vlock_fal                   : 1;   //     2
	UINT32 cvd_vlock_ris                   : 1;   //     3
	UINT32 cvd_hlock_fal                   : 1;   //     4
	UINT32 cvd_hlock_ris                   : 1;   //     5
	UINT32 cvd_no_signal_fal               : 1;   //     6
	UINT32 cvd_no_signal_ris               : 1;   //     7
	UINT32 cvd_noburst_detected_fal        : 1;   //     8
	UINT32 cvd_noburst_detected_ris        : 1;   //     9
	UINT32 cvd_vnon_standard_fal           : 1;   //    10
	UINT32 cvd_vnon_standard_ris           : 1;   //    11
	UINT32 cvd_hnon_standard_fal           : 1;   //    12
	UINT32 cvd_hnon_standard_ris           : 1;   //    13
	UINT32 cvd_proscan_detected_fal        : 1;   //    14
	UINT32 cvd_proscan_detected_ris        : 1;   //    15
	UINT32 cvd_vcr_fal                     : 1;   //    16
	UINT32 cvd_vcr_ris                     : 1;   //    17
	UINT32 cvd_noisy_fal                   : 1;   //    18
	UINT32 cvd_noisy_ris                   : 1;   //    19
	UINT32 cvd_vline_625_detected_fal      : 1;   //    20
	UINT32 cvd_vline_625_detected_ris      : 1;   //    21
	UINT32 cvd_secam_detected_fal          : 1;   //    22
	UINT32 cvd_secam_detected_ris          : 1;   //    23
	UINT32 cvd_pal_detected_fal            : 1;   //    24
	UINT32 cvd_pal_detected_ris            : 1;   //    25
	UINT32 cvd_vs_fal                      : 1;   //    26
	UINT32 cvd_vs_ris                      : 1;   //    27
	UINT32 cvd_ext_locked_fal              : 1;   //    28
	UINT32 cvd_ext_locked_ris              : 1;   //    29
} L9B0_CVD_INTR2_INTR0_T;

/*-----------------------------------------------------------------------------
	0x4120 cvd_intr2_clear0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_clear0                : 32;  //  0:31
} L9B0_CVD_INTR2_CLEAR0_T;

/*-----------------------------------------------------------------------------
	0x4124 cvd_intr2_enable1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_enable1               : 32;  //  0:31
} L9B0_CVD_INTR2_ENABLE1_T;

/*-----------------------------------------------------------------------------
	0x4128 cvd_intr2_intr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_wss_rdy                     : 1;   //     0
	UINT32 vbi_cc_rdy                      : 1;   //     1
	UINT32 vbi_data_in                     : 1;   //     2
	UINT32 cvd_fb_rst                      : 1;   //     3
	UINT32 cvd_mif_err                     : 1;   //     4
	UINT32 cs_chromalock_fal               : 1;   //     5
	UINT32 cs_chromalock_ris               : 1;   //     6
	UINT32 cs_pal_detected_fal             : 1;   //     7
	UINT32 cs_pal_detected_ris             : 1;   //     8
	UINT32 cs_secam_detected_fal           : 1;   //     9
	UINT32 cs_secam_detected_ris           : 1;   //    10
	UINT32 cs1_chromalock_fal              : 1;   //    11
	UINT32 cs1_chromalock_ris              : 1;   //    12
	UINT32 cs1_pal_detected_fal            : 1;   //    13
	UINT32 cs1_pal_detected_ris            : 1;   //    14
	UINT32 cs1_secam_detected_fal          : 1;   //    15
	UINT32 cs1_secam_detected_ris          : 1;   //    16
	UINT32 estfrdp_err_flag_fal            : 1;   //    17
	UINT32 estfrdp_err_flag_ris            : 1;   //    18
	UINT32 vdetect_vcount_fal              : 1;   //    19
	UINT32 vdetect_vcount_ris              : 1;   //    20
} L9B0_CVD_INTR2_INTR1_T;

/*-----------------------------------------------------------------------------
	0x412c cvd_intr2_clear1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_clear1                : 32;  //  0:31
} L9B0_CVD_INTR2_CLEAR1_T;

/*-----------------------------------------------------------------------------
	0x4130 top_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 iris_ver                        : 32;  //  0:31
} L9B0_TOP_001_T;

/*-----------------------------------------------------------------------------
	0x4140 iris_mif_gmua_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 comb3_buffer_size               : 23;  //  0:22
} L9B0_IRIS_MIF_GMUA_001_T;

/*-----------------------------------------------------------------------------
	0x4144 iris_mif_gmua_002 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fld1_init_rd_pel                : 23;  //  0:22
} L9B0_IRIS_MIF_GMUA_002_T;

/*-----------------------------------------------------------------------------
	0x4148 iris_mif_gmua_003 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fld2_init_rd_pel                : 23;  //  0:22
} L9B0_IRIS_MIF_GMUA_003_T;

/*-----------------------------------------------------------------------------
	0x414c iris_mif_gmua_004 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fld3_init_rd_pel                : 23;  //  0:22
} L9B0_IRIS_MIF_GMUA_004_T;

/*-----------------------------------------------------------------------------
	0x4150 iris_mif_gmua_005 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fld4_init_rd_pel                : 23;  //  0:22
} L9B0_IRIS_MIF_GMUA_005_T;

/*-----------------------------------------------------------------------------
	0x4154 iris_mif_gmua_006 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_to_cnt                     : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 gmau_cmd_dly_cnt                : 4;   // 12:15
} L9B0_IRIS_MIF_GMUA_006_T;

/*-----------------------------------------------------------------------------
	0x4158 iris_mif_gmua_007 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_cmd_base                   : 32;  //  0:31
} L9B0_IRIS_MIF_GMUA_007_T;

/*-----------------------------------------------------------------------------
	0x4160 iris_mif_gmua_008 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_endian_sw                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 gmau_cmd_pri2                   : 4;   //  4: 7
	UINT32 gmau_cmd_pri1                   : 4;   //  8:11
} L9B0_IRIS_MIF_GMUA_008_T;

/*-----------------------------------------------------------------------------
	0x4164 iris_mif_gmua_009 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_stride_size                : 32;  //  0:31
} L9B0_IRIS_MIF_GMUA_009_T;

/*-----------------------------------------------------------------------------
	0x4168 fastblank_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_latency                      : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 fb3ch_delay                     : 5;   //  8:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 fb_blend_ratio                  : 5;   // 16:20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 fb_2line_delay                  : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 fb_en                           : 1;   //    28
} L9B0_FASTBLANK_001_T;

/*-----------------------------------------------------------------------------
	0x416c fastblank_002 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_csc_coef1                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 fb_csc_coef0                    : 15;  // 16:30
} L9B0_FASTBLANK_002_T;

/*-----------------------------------------------------------------------------
	0x4170 fastblank_003 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_csc_coef3                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 fb_csc_coef2                    : 15;  // 16:30
} L9B0_FASTBLANK_003_T;

/*-----------------------------------------------------------------------------
	0x4174 fastblank_004 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_csc_coef5                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 fb_csc_coef4                    : 15;  // 16:30
} L9B0_FASTBLANK_004_T;

/*-----------------------------------------------------------------------------
	0x4178 fastblank_005 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_csc_coef7                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 fb_csc_coef6                    : 15;  // 16:30
} L9B0_FASTBLANK_005_T;

/*-----------------------------------------------------------------------------
	0x417c fastblank_006 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_csc_coef8                    : 15;  //  0:14
} L9B0_FASTBLANK_006_T;

/*-----------------------------------------------------------------------------
	0x4180 fastblank_007 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_csc_ofst1                    : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 fb_csc_ofst0                    : 11;  // 12:22
} L9B0_FASTBLANK_007_T;

/*-----------------------------------------------------------------------------
	0x4184 fastblank_008 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_csc_ofst3                    : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 fb_csc_ofst2                    : 11;  // 12:22
} L9B0_FASTBLANK_008_T;

/*-----------------------------------------------------------------------------
	0x4188 fastblank_009 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_vstart_odd                   : 5;   //  0: 4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 fb_csc_ofst5                    : 11;  //  8:18
	UINT32                                 : 1;   //    19 reserved
	UINT32 fb_csc_ofst4                    : 11;  // 20:30
} L9B0_FASTBLANK_009_T;

/*-----------------------------------------------------------------------------
	0x418c fastblank_010 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_hstart                       : 8;   //  0: 7
	UINT32 fb_height_half                  : 8;   //  8:15
	UINT32 fb_vstart_even                  : 5;   // 16:20
} L9B0_FASTBLANK_010_T;

/*-----------------------------------------------------------------------------
	0x4190 iris_de_ctrl_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 iris_hsout_width                : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 iris_static_de_start            : 12;  // 12:23
	UINT32 iris_static_de                  : 1;   //    24
} L9B0_IRIS_DE_CTRL_001_T;

/*-----------------------------------------------------------------------------
	0x4194 vbi_ctrl_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_little_endian               : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 vbi_bits_swap                   : 1;   //     4
} L9B0_VBI_CTRL_001_T;

/*-----------------------------------------------------------------------------
	0x4198 vbi_ctrl_002 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi0_start_addr                 : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 vbi0_data_cnt                   : 12;  // 12:23
	UINT32 vbi_buffer_number               : 2;   // 24:25
} L9B0_VBI_CTRL_002_T;

/*-----------------------------------------------------------------------------
	0x419c vbi_ctrl_003 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi0_end_addr                   : 10;  //  0: 9
} L9B0_VBI_CTRL_003_T;

/*-----------------------------------------------------------------------------
	0x41a0 vbi_ctrl_004 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi1_start_addr                 : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 vbi1_data_cnt                   : 12;  // 12:23
} L9B0_VBI_CTRL_004_T;

/*-----------------------------------------------------------------------------
	0x41a4 vbi_ctrl_005 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi1_end_addr                   : 10;  //  0: 9
} L9B0_VBI_CTRL_005_T;

/*-----------------------------------------------------------------------------
	0x41a8 vbi_ctrl_006 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi2_start_addr                 : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 vbi2_data_cnt                   : 12;  // 12:23
} L9B0_VBI_CTRL_006_T;

/*-----------------------------------------------------------------------------
	0x41ac vbi_ctrl_007 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi2_end_addr                   : 10;  //  0: 9
} L9B0_VBI_CTRL_007_T;

/*-----------------------------------------------------------------------------
	0x41b0 vbi_ctrl_008 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi3_start_addr                 : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 vbi3_data_cnt                   : 12;  // 12:23
} L9B0_VBI_CTRL_008_T;

/*-----------------------------------------------------------------------------
	0x41b4 vbi_ctrl_009 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi3_end_addr                   : 10;  //  0: 9
} L9B0_VBI_CTRL_009_T;

/*-----------------------------------------------------------------------------
	0x41c0 fast_blank_status_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fb_state                        : 1;   //     0
} L9B0_FAST_BLANK_STATUS_001_T;

/*-----------------------------------------------------------------------------
	0x41c4 cvbsafe_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvbs2_gc_int                    : 4;   //  0: 3
	UINT32 cvbs1_gc_int                    : 4;   //  4: 7
	UINT32 iris_fix_gain                   : 1;   //     8
} L9B0_CVBSAFE_001_T;

/*-----------------------------------------------------------------------------
	0x4200 iris_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 proscan_detected                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 mv_colourstripes                : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 mv_vbi_detected                 : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 chromalock                      : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 vlock                           : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 hlock                           : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 no_signal                       : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 status_vdetect_vcount_chg       : 1;   //    28
} L9B0_IRIS_001_T;

/*-----------------------------------------------------------------------------
	0x4204 iris_002 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 noisy                           : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 vline_625_detected              : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 secam_detected                  : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 pal_detected                    : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 status_comb3d_off               : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 noburst_detected                : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 vnon_standard                   : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 hnon_standard                   : 1;   //    28
} L9B0_IRIS_002_T;

/*-----------------------------------------------------------------------------
	0x4208 iris_003 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vcr_rew                         : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 vcr_ff                          : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 vcr_trick                       : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 reg_vcr                         : 1;   //    12
} L9B0_IRIS_003_T;

/*-----------------------------------------------------------------------------
	0x420c iris_004 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_burst_mag                : 16;  //  0:15
	UINT32 status_hsync_width              : 8;   // 16:23
} L9B0_IRIS_004_T;

/*-----------------------------------------------------------------------------
	0x4210 iris_005 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_hdto_inc                 : 30;  //  0:29
} L9B0_IRIS_005_T;

/*-----------------------------------------------------------------------------
	0x4214 iris_006 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_cdto_inc                 : 30;  //  0:29
} L9B0_IRIS_006_T;

/*-----------------------------------------------------------------------------
	0x4218 iris_007 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_cmag                     : 8;   //  0: 7
	UINT32 status_agc_gain                 : 16;  //  8:23
} L9B0_IRIS_007_T;

/*-----------------------------------------------------------------------------
	0x421c iris_008 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_sync_height              : 8;   //  0: 7
	UINT32 status_cordic_freq              : 8;   //  8:15
	UINT32 status_cgain                    : 14;  // 16:29
} L9B0_IRIS_008_T;

/*-----------------------------------------------------------------------------
	0x4220 iris_009 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_nstd                     : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 status_vbi_slicer_lvl           : 8;   // 12:19
	UINT32 status_noise                    : 10;  // 20:29
} L9B0_IRIS_009_T;

/*-----------------------------------------------------------------------------
	0x4224 iris_010 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_comb3d_motion            : 32;  //  0:31
} L9B0_IRIS_010_T;

/*-----------------------------------------------------------------------------
	0x4230 iris_011 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_soft_reset                  : 1;   //     0
} L9B0_IRIS_011_T;

/*-----------------------------------------------------------------------------
	0x4234 iris_012 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hv_delay                        : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 hpixel                          : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 vline_625                       : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 colour_mode                     : 3;   // 12:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 yc_src                          : 1;   //    16
} L9B0_IRIS_012_T;

/*-----------------------------------------------------------------------------
	0x4238 iris_013 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cv_inv                          : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cv_src                          : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 luma_notch_bw                   : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 chroma_bw_lo                    : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 chroma_burst5or10               : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 reg_ped                         : 1;   //    20
} L9B0_IRIS_013_T;

/*-----------------------------------------------------------------------------
	0x423c iris_014 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hagc_field_mode                 : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 mv_hagc_mode                    : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 dc_clamp_mode                   : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 dagc_en                         : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 agc_half_en                     : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 cagc_en                         : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 hagc_en                         : 1;   //    24
} L9B0_IRIS_014_T;

/*-----------------------------------------------------------------------------
	0x4240 iris_015 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pal60_mode                      : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 ntsc443_mode                    : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 adaptive_3dcomb_mode            : 3;   //  8:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 colour_trap                     : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 adaptive_mode                   : 3;   // 16:18
} L9B0_IRIS_015_T;

/*-----------------------------------------------------------------------------
	0x4244 iris_016 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 noise_thresh                    : 8;   //  0: 7
	UINT32 hagc                            : 8;   //  8:15
} L9B0_IRIS_016_T;

/*-----------------------------------------------------------------------------
	0x4248 iris_017 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 force_vcr_en                    : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 force_vcr_rew                   : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 force_vcr_ff                    : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 force_vcr_trick                 : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 force_vcr                       : 1;   //    16
} L9B0_IRIS_017_T;

/*-----------------------------------------------------------------------------
	0x424c iris_018 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 adc_updn_swap                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 adc_input_swap                  : 1;   //     4
} L9B0_IRIS_018_T;

/*-----------------------------------------------------------------------------
	0x4250 iris_019 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ccir656_en                      : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cbcr_swap                       : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 blue_mode                       : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 yc_delay                        : 4;   // 12:15
} L9B0_IRIS_019_T;

/*-----------------------------------------------------------------------------
	0x4254 iris_020 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hue                         : 8;   //  0: 7
	UINT32 saturation                      : 8;   //  8:15
	UINT32 brightness                      : 8;   // 16:23
	UINT32 contrast                        : 8;   // 24:31
} L9B0_IRIS_020_T;

/*-----------------------------------------------------------------------------
	0x4258 iris_021 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cagc                            : 8;   //  0: 7
} L9B0_IRIS_021_T;

/*-----------------------------------------------------------------------------
	0x425c iris_022 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 user_ckill_mode                 : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 vbi_ckill                       : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 hlock_ckill                     : 1;   //     8
} L9B0_IRIS_022_T;

/*-----------------------------------------------------------------------------
	0x4260 iris_023 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 nstd_hysis                      : 4;   //  0: 3
	UINT32 disable_clamp_on_vsync          : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 bypass                          : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 noburst_ckill                   : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 vnon_std_threshold              : 2;   // 16:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 hnon_std_threshold              : 6;   // 20:25
} L9B0_IRIS_023_T;

/*-----------------------------------------------------------------------------
	0x4264 iris_024 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 agc_peak_en                     : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 agc_peak_cntl                   : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 agc_peak_nominal                : 7;   //  8:14
} L9B0_IRIS_024_T;

/*-----------------------------------------------------------------------------
	0x4268 iris_025 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 blue_cr                         : 8;   //  0: 7
	UINT32 blue_cb                         : 8;   //  8:15
	UINT32 blue_y                          : 8;   // 16:23
} L9B0_IRIS_025_T;

/*-----------------------------------------------------------------------------
	0x426c iris_026 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hstate_fixed                    : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 disable_hfine                   : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 hstate_unlocked                 : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 hstate_max                      : 3;   // 12:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 locked_count_noisy_max          : 4;   // 16:19
	UINT32 locked_count_clean_max          : 4;   // 20:23
	UINT32 hdetect_clamp_level             : 8;   // 24:31
} L9B0_IRIS_026_T;

/*-----------------------------------------------------------------------------
	0x4270 iris_027 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hlock_vsync_mode                : 2;   //  0: 1
} L9B0_IRIS_027_T;

/*-----------------------------------------------------------------------------
	0x4274 iris_028 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdto_inc                        : 32;  //  0:31
} L9B0_IRIS_028_T;

/*-----------------------------------------------------------------------------
	0x4278 iris_029 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hdto_inc                        : 32;  //  0:31
} L9B0_IRIS_029_T;

/*-----------------------------------------------------------------------------
	0x427c iris_030 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync_gate_end                  : 8;   //  0: 7
	UINT32 hsync_gate_start                : 8;   //  8:15
	UINT32 hsync_phase_offset              : 8;   // 16:23
	UINT32 hsync_rising                    : 8;   // 24:31
} L9B0_IRIS_030_T;

/*-----------------------------------------------------------------------------
	0x4280 iris_031 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync_similar                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 hsync_low                       : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 hdetect_noise_en                : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 hfine_lt_hcoarse                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 hlpf_clamp_sel                  : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 hlpf_clamp_noisy_en             : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 hlpf_clamp_vbi_en               : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 hlpf_clamp_en                   : 1;   //    28
} L9B0_IRIS_031_T;

/*-----------------------------------------------------------------------------
	0x4284 iris_032 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync_rising_end                : 8;   //  0: 7
	UINT32 hsync_rising_auto               : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 hsync_rising_start              : 6;   // 12:17
} L9B0_IRIS_032_T;

/*-----------------------------------------------------------------------------
	0x4288 iris_033 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hblank_end                      : 8;   //  0: 7
	UINT32 hblank_start                    : 8;   //  8:15
} L9B0_IRIS_033_T;

/*-----------------------------------------------------------------------------
	0x428c iris_034 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 burst_gate_end                  : 8;   //  0: 7
	UINT32 burst_gate_start                : 8;   //  8:15
} L9B0_IRIS_034_T;

/*-----------------------------------------------------------------------------
	0x4290 iris_035 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hactive_width                   : 8;   //  0: 7
	UINT32 hactive_start                   : 8;   //  8:15
} L9B0_IRIS_035_T;

/*-----------------------------------------------------------------------------
	0x4294 iris_036 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vactive_height                  : 8;   //  0: 7
	UINT32 vactive_start                   : 8;   //  8:15
} L9B0_IRIS_036_T;

/*-----------------------------------------------------------------------------
	0x4298 iris_037 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync_h_max                     : 7;   //  0: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 vsync_h_min                     : 7;   //  8:14
} L9B0_IRIS_037_T;

/*-----------------------------------------------------------------------------
	0x429c iris_038 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync_agc_max                   : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 vsync_agc_min                   : 7;   //  8:14
} L9B0_IRIS_038_T;

/*-----------------------------------------------------------------------------
	0x42a0 iris_039 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync_vbi_max                   : 7;   //  0: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 vsync_vbi_min                   : 7;   //  8:14
} L9B0_IRIS_039_T;

/*-----------------------------------------------------------------------------
	0x42a4 iris_040 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vlock_wide_range                : 1;   //     0
} L9B0_IRIS_040_T;

/*-----------------------------------------------------------------------------
	0x42a8 iris_041 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 proscan_1field_mode             : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 vsync_cntl_noisy                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 vsync_cntl_ff_rew               : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 vsync_cntl_trick                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 vsync_cntl_vcr                  : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 vsync_cntl                      : 2;   // 20:21
} L9B0_IRIS_041_T;

/*-----------------------------------------------------------------------------
	0x42ac iris_042 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 field_polarity                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 flip_field                      : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 veven_delayed                   : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 vodd_delayed                    : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 field_detect_mode               : 2;   // 16:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 vloop_tc                        : 2;   // 20:21
} L9B0_IRIS_042_T;

/*-----------------------------------------------------------------------------
	0x42b0 iris_043 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dbg_syncs                       : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 muxdigital                      : 4;   //  4: 7
	UINT32 muxanalogb                      : 4;   //  8:11
	UINT32 muxanaloga                      : 4;   // 12:15
} L9B0_IRIS_043_T;

/*-----------------------------------------------------------------------------
	0x42b4 iris_044 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_ybw                       : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 peak_range                      : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 peak_gain                       : 3;   //  8:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 peak_en                         : 1;   //    12
} L9B0_IRIS_044_T;

/*-----------------------------------------------------------------------------
	0x42b8 iris_045 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 auto_secam_level                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 sv_bf                           : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 secam_pll                       : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 secam_sw_old                    : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 palsw_level                     : 2;   // 16:17
} L9B0_IRIS_045_T;

/*-----------------------------------------------------------------------------
	0x42bc iris_046 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 lose_chromalock_mode            : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 lose_chromalock_count           : 4;   //  4: 7
	UINT32 lose_chromalock_level           : 3;   //  8:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 lose_chromalock_ckill           : 1;   //    12
} L9B0_IRIS_046_T;

/*-----------------------------------------------------------------------------
	0x42c0 iris_047 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cstripe_detect_control          : 3;   //  0: 2
} L9B0_IRIS_047_T;

/*-----------------------------------------------------------------------------
	0x42c4 iris_048 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hfine_vcr_trick_en              : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 hfine_vcr_en                    : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 hresampler_2up                  : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cstate                          : 3;   // 12:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 fixed_cstate                    : 1;   //    16
} L9B0_IRIS_048_T;

/*-----------------------------------------------------------------------------
	0x42c8 iris_049 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_pulse_ampl                  : 8;   //  0: 7
} L9B0_IRIS_049_T;

/*-----------------------------------------------------------------------------
	0x42cc iris_050 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpump_delay                     : 8;   //  0: 7
	UINT32 cpump_adjust                    : 8;   //  8:15
	UINT32 cpump_adjust_polarity           : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 cpump_adjust_delay              : 6;   // 20:25
} L9B0_IRIS_050_T;

/*-----------------------------------------------------------------------------
	0x42d0 iris_051 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mv_colourstripes_sel            : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 mv_vbi_sel                      : 1;   //     4
} L9B0_IRIS_051_T;

/*-----------------------------------------------------------------------------
	0x42d4 iris_052 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpump_kill_cr                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cpump_kill_cb                   : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cpump_kill_y                    : 1;   //     8
} L9B0_IRIS_052_T;

/*-----------------------------------------------------------------------------
	0x42d8 iris_053 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpump_auto_stip_nobp            : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cpump_auto_stip_unlocked        : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cpump_auto_stip_no_signal       : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cpump_auto_stip_noisy           : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cpump_auto_stip_vactive         : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 cpump_auto_stip_mode            : 2;   // 20:21
} L9B0_IRIS_053_T;

/*-----------------------------------------------------------------------------
	0x42dc iris_054 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpump_accum_mode                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cpump_fixed_syncmid             : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cpump_level_filter_gain         : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 cpump_noisy_filter_en           : 1;   //    12
} L9B0_IRIS_054_T;

/*-----------------------------------------------------------------------------
	0x42e0 iris_055 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpump_dn_max                    : 7;   //  0: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 cpump_up_max                    : 7;   //  8:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 cpump_vsync_blank_filter        : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 cpump_vsync_syncmid_filter      : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 cpump_vsync_mode                : 2;   // 24:25
} L9B0_IRIS_055_T;

/*-----------------------------------------------------------------------------
	0x42e4 iris_056 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpump_diff_noisy_only           : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cpump_dn_diff_max               : 7;   //  4:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 cpump_diff_signal_only          : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cpump_up_diff_max               : 7;   // 16:22
} L9B0_IRIS_056_T;

/*-----------------------------------------------------------------------------
	0x42e8 iris_057 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpump_pr_override               : 8;   //  0: 7
	UINT32 cpump_pb_override               : 8;   //  8:15
	UINT32 cpump_y_override                : 8;   // 16:23
} L9B0_IRIS_057_T;

/*-----------------------------------------------------------------------------
	0x42ec iris_058 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 db_freq                         : 12;  //  0:11
	UINT32 dr_freq                         : 12;  // 12:23
	UINT32 cvbs_y_delay                    : 5;   // 24:28
} L9B0_IRIS_058_T;

/*-----------------------------------------------------------------------------
	0x42f0 iris_059 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vactivity_en                    : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 vactivity_on2frame              : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 vactivity_threshold             : 6;   //  8:13
} L9B0_IRIS_059_T;

/*-----------------------------------------------------------------------------
	0x42f4 iris_060 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 horiz_diff_cgain                : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 horiz_diff_ygain                : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 chroma_vdiff_gain               : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 lowfreq_vdiff_gain              : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 noise_th_en                     : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 noise_th                        : 7;   // 20:26
} L9B0_IRIS_060_T;

/*-----------------------------------------------------------------------------
	0x42f8 iris_061 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vadap_burst_noise_th_gain       : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 burst_noise_th_gain             : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 c_noise_th_gain                 : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 y_noise_th_gain                 : 2;   // 12:13
} L9B0_IRIS_061_T;

/*-----------------------------------------------------------------------------
	0x42fc iris_062 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 adaptive_chroma_mode            : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 dot_suppress_mode               : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 motion_mode                     : 2;   //  8: 9
} L9B0_IRIS_062_T;

/*-----------------------------------------------------------------------------
	0x4300 iris_063 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pal3dcomb_vactive_offset        : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 fb_sync                         : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 fb_hold                         : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 fb_ctl                          : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 field_latency                   : 3;   // 16:18
	UINT32                                 : 1;   //    19 reserved
	UINT32 lbadrgen_rst                    : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 comb2d_only                     : 1;   //    24
} L9B0_IRIS_063_T;

/*-----------------------------------------------------------------------------
	0x4304 iris_064 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_noise_th_en                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 md_noise_th                     : 7;   //  4:10
} L9B0_IRIS_064_T;

/*-----------------------------------------------------------------------------
	0x4308 iris_065 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 schroma_peak_en                 : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 schroma_coring_en               : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 schroma_peak                    : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 pchroma_peak_en                 : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 pchroma_coring_en               : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 pchroma_peak                    : 2;   // 20:21
} L9B0_IRIS_065_T;

/*-----------------------------------------------------------------------------
	0x430c iris_066 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ldpause_threshold               : 4;   //  0: 3
	UINT32 vf_nstd_en                      : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 vcr_auto_switch_en              : 1;   //     8
} L9B0_IRIS_066_T;

/*-----------------------------------------------------------------------------
	0x4310 iris_067 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 comb_coring                     : 4;   //  0: 3
	UINT32 tcomb_gain                      : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 notch_gain                      : 3;   //  8:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 comb_gain                       : 3;   // 12:14
} L9B0_IRIS_067_T;

/*-----------------------------------------------------------------------------
	0x4314 iris_068 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vactive_md_height               : 8;   //  0: 7
	UINT32 vactive_md_start                : 8;   //  8:15
} L9B0_IRIS_068_T;

/*-----------------------------------------------------------------------------
	0x4318 iris_069 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync_pulse_width               : 4;   //  0: 3
} L9B0_IRIS_069_T;

/*-----------------------------------------------------------------------------
	0x431c iris_070 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cagc_tc_ismall                  : 3;   //  0: 2
} L9B0_IRIS_070_T;

/*-----------------------------------------------------------------------------
	0x4320 iris_071 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cagc_coring_threshold           : 4;   //  0: 3
	UINT32 cagc_unity_gain                 : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cagc_coring                     : 3;   //  8:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 cagc_tc_p                       : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 cagc_tc_ibig                    : 3;   // 16:18
} L9B0_IRIS_071_T;

/*-----------------------------------------------------------------------------
	0x4324 iris_072 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aaf_on                          : 1;   //     0
} L9B0_IRIS_072_T;

/*-----------------------------------------------------------------------------
	0x4328 iris_073 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dcrestore_accum_width           : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 dcrestore_no_bad_bp             : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 dcrestore_kill_enable           : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 dcrestore_bp_delay              : 2;   // 16:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 syncmid_nobp_en                 : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 syncmid_filter_en               : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 dcrestore_gain                  : 2;   // 28:29
} L9B0_IRIS_073_T;

/*-----------------------------------------------------------------------------
	0x432c iris_074 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dcrestore_kill_enable_noisy     : 1;   //     0
} L9B0_IRIS_074_T;

/*-----------------------------------------------------------------------------
	0x4330 iris_075 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dcrestore_hsync_mid             : 8;   //  0: 7
	UINT32 bp_kill_thresh                  : 8;   //  8:15
	UINT32 hmgc                            : 8;   // 16:23
	UINT32 dcrestore_lpf_en                : 1;   //    24
} L9B0_IRIS_075_T;

/*-----------------------------------------------------------------------------
	0x4334 iris_076 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 auto_min_sync_height            : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 min_sync_height                 : 7;   //  4:10
} L9B0_IRIS_076_T;

/*-----------------------------------------------------------------------------
	0x4338 iris_077 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vcrtrick_proscan                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 veven_early_delayed             : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 vodd_early_delayed              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 vfield_hoffset_fixed            : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 vsync_no_signal_thresh          : 8;   // 16:23
	UINT32 vsync_signal_thresh             : 8;   // 24:31
} L9B0_IRIS_077_T;

/*-----------------------------------------------------------------------------
	0x433c iris_078 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vfield_hoffset                  : 9;   //  0: 8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 vactive_half_lines              : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 vdetect_noise_en                : 1;   //    16
} L9B0_IRIS_078_T;

/*-----------------------------------------------------------------------------
	0x4340 iris_079 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dual_hedge_dis                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 dual_hedge_auto_width           : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 dual_fine_hedge_vbi             : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 dual_coarse_hedge_vbi           : 2;   // 12:13
} L9B0_IRIS_079_T;

/*-----------------------------------------------------------------------------
	0x4344 iris_080 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mv_hsync_rising_end             : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 vcr_state2_long                 : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 slow_hdsw                       : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 mv_hsync_rising_start           : 6;   // 16:21
	UINT32                                 : 2;   // 22:23 reserved
	UINT32 no_hsyncs_mode                  : 2;   // 24:25
	UINT32                                 : 2;   // 26:27 reserved
	UINT32 many_hsyncs_mode                : 1;   //    28
} L9B0_IRIS_080_T;

/*-----------------------------------------------------------------------------
	0x4348 iris_081 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 no_hsyncs_weak                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 disable_hdsw_weak               : 1;   //     4
} L9B0_IRIS_081_T;

/*-----------------------------------------------------------------------------
	0x434c iris_082 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vactive_hdsw_mode               : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 disable_hdsw_mode               : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 hsync_falling_filter            : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 no_hsyncs_noisy                 : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 hloop_range                     : 2;   // 16:17
} L9B0_IRIS_082_T;

/*-----------------------------------------------------------------------------
	0x4350 iris_083 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_hf_max                       : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 md_hf_shift                     : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 md_lf_sad                       : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 md_lf_shift                     : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 md_c_noise_th_en                : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 md_c_noise_th                   : 7;   // 20:26
} L9B0_IRIS_083_T;

/*-----------------------------------------------------------------------------
	0x4354 iris_084 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_cf_cactivity_high            : 4;   //  0: 3
	UINT32 md_cf_lactivity_high            : 8;   //  4:11
	UINT32 md_cf_cactivity_low             : 8;   // 12:19
	UINT32 md_cf_lactivity_low             : 8;   // 20:27
	UINT32 md_cf_activity_enable           : 2;   // 28:29
} L9B0_IRIS_084_T;

/*-----------------------------------------------------------------------------
	0x4358 iris_085 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_k_thresh                     : 8;   //  0: 7
} L9B0_IRIS_085_T;

/*-----------------------------------------------------------------------------
	0x435c iris_086 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 tcomb_chroma_level              : 8;   //  0: 7
	UINT32 hf_luma_chroma_offset           : 8;   //  8:15
	UINT32 spatial_luma_level              : 8;   // 16:23
	UINT32 chroma_level                    : 8;   // 24:31
} L9B0_IRIS_086_T;

/*-----------------------------------------------------------------------------
	0x4360 iris_087 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 chroma_activity_level           : 8;   //  0: 7
	UINT32 lf_luma_offset                  : 8;   //  8:15
} L9B0_IRIS_087_T;

/*-----------------------------------------------------------------------------
	0x4364 iris_088 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 avg_freq_range                  : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 issecam_th                      : 6;   //  4: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 freq_offset_range               : 8;   // 12:19
} L9B0_IRIS_088_T;

/*-----------------------------------------------------------------------------
	0x4368 iris_089 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 chroma_bw_motion_th             : 8;   //  0: 7
	UINT32 motion_config                   : 8;   //  8:15
	UINT32 hactive_md_width                : 8;   // 16:23
	UINT32 hactive_md_start                : 8;   // 24:31
} L9B0_IRIS_089_T;

/*-----------------------------------------------------------------------------
	0x436c iris_090 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_motion_mode              : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 chroma_bw_motion                : 2;   //  4: 5
} L9B0_IRIS_090_T;

/*-----------------------------------------------------------------------------
	0x4370 iris_091 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 flat_chroma_offset              : 8;   //  0: 7
	UINT32 flat_luma_offset                : 8;   //  8:15
	UINT32 flat_chroma_shift               : 2;   // 16:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 flat_luma_shift                 : 2;   // 20:21
} L9B0_IRIS_091_T;

/*-----------------------------------------------------------------------------
	0x4374 iris_092 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 motion_debug                    : 8;   //  0: 7
	UINT32 cf_flat_motion_shift            : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 motion_c_mode                   : 2;   // 12:13
} L9B0_IRIS_092_T;

/*-----------------------------------------------------------------------------
	0x4378 iris_093 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cordic_gate_end                 : 8;   //  0: 7
	UINT32 cordic_gate_start               : 8;   //  8:15
	UINT32 ispal_th                        : 8;   // 16:23
	UINT32 phase_offset_range              : 8;   // 24:31
} L9B0_IRIS_093_T;

/*-----------------------------------------------------------------------------
	0x437c iris_094 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pal3tap_only_c                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 pal3tap_only_y                  : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 adc_cpump_swap                  : 6;   //  8:13
} L9B0_IRIS_094_T;

/*-----------------------------------------------------------------------------
	0x4380 iris_095 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ckill                           : 16;  //  0:15
	UINT32 cagc_gate_end                   : 8;   // 16:23
	UINT32 cagc_gate_start                 : 8;   // 24:31
} L9B0_IRIS_095_T;

/*-----------------------------------------------------------------------------
	0x4384 iris_096 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 icburst_half_ampl               : 10;  //  0: 9
} L9B0_IRIS_096_T;

/*-----------------------------------------------------------------------------
	0x4388 iris_097 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 agc_bypass                      : 1;   //     0
} L9B0_IRIS_097_T;

/*-----------------------------------------------------------------------------
	0x438c iris_098 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 clampagc_inv                    : 4;   //  0: 3
} L9B0_IRIS_098_T;

/*-----------------------------------------------------------------------------
	0x4390 iris_099 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vps_slicer_mode                 : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 wss_slicer_mode                 : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 tt_slicer_mode                  : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 cc_slicer_mode                  : 2;   // 12:13
} L9B0_IRIS_099_T;

/*-----------------------------------------------------------------------------
	0x4394 iris_100 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 perr_on                         : 1;   //     0
} L9B0_IRIS_100_T;

/*-----------------------------------------------------------------------------
	0x4398 iris_101 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 perr_dnref                      : 32;  //  0:31
} L9B0_IRIS_101_T;

/*-----------------------------------------------------------------------------
	0x439c iris_102 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_lpfa_coeff0                : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cres_lpfa_on                    : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 iris_cresampler_on              : 1;   //    20
} L9B0_IRIS_102_T;

/*-----------------------------------------------------------------------------
	0x43a0 iris_103 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_lpfa_coeff2                : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cres_lpfa_coeff1                : 13;  // 16:28
} L9B0_IRIS_103_T;

/*-----------------------------------------------------------------------------
	0x43a4 iris_104 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_lpfa_coeff4                : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cres_lpfa_coeff3                : 13;  // 16:28
} L9B0_IRIS_104_T;

/*-----------------------------------------------------------------------------
	0x43a8 iris_105 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_lpfa_coeff5                : 13;  //  0:12
} L9B0_IRIS_105_T;

/*-----------------------------------------------------------------------------
	0x43ac iris_106 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_lpfb_coeff0                : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cres_lpfb_on                    : 1;   //    16
} L9B0_IRIS_106_T;

/*-----------------------------------------------------------------------------
	0x43b0 iris_107 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_lpfb_coeff2                : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cres_lpfb_coeff1                : 13;  // 16:28
} L9B0_IRIS_107_T;

/*-----------------------------------------------------------------------------
	0x43b4 iris_108 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_lpfb_coeff4                : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cres_lpfb_coeff3                : 13;  // 16:28
} L9B0_IRIS_108_T;

/*-----------------------------------------------------------------------------
	0x43b8 iris_109 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_blend_sel                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cres_blend_method               : 3;   //  4: 6
} L9B0_IRIS_109_T;

/*-----------------------------------------------------------------------------
	0x43bc iris_110 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_blend_bcdefault            : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 cres_0px_sel                    : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cres_clksel                     : 2;   // 16:17
} L9B0_IRIS_110_T;

/*-----------------------------------------------------------------------------
	0x43c0 iris_111 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_blend_bcpara1              : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 cres_blend_bcpara0              : 11;  // 12:22
} L9B0_IRIS_111_T;

/*-----------------------------------------------------------------------------
	0x43c4 iris_112 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_blend_bcpara3              : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 cres_blend_bcpara2              : 11;  // 12:22
} L9B0_IRIS_112_T;

/*-----------------------------------------------------------------------------
	0x43c8 iris_113 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_blend_bcpara5              : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 cres_blend_bcpara4              : 11;  // 12:22
} L9B0_IRIS_113_T;

/*-----------------------------------------------------------------------------
	0x43cc iris_114 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_blend_bcpara7              : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 cres_blend_bcpara6              : 11;  // 12:22
} L9B0_IRIS_114_T;

/*-----------------------------------------------------------------------------
	0x43d0 iris_115 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_blend_diffth1              : 12;  //  0:11
	UINT32 cres_blend_diffth0              : 12;  // 12:23
} L9B0_IRIS_115_T;

/*-----------------------------------------------------------------------------
	0x43d4 iris_116 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cres_alpha_off                  : 8;   //  0: 7
	UINT32 cres_blend_diffth2              : 12;  //  8:19
} L9B0_IRIS_116_T;

/*-----------------------------------------------------------------------------
	0x43d8 iris_117 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hrscbld_dnoff                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 hrscbld_upoff                   : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 hrsybld_dnoff                   : 3;   //  8:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 hrsybld_upoff                   : 4;   // 12:15
	UINT32 dtrs_dlysel                     : 4;   // 16:19
	UINT32 dtrs_revalpha_sel               : 2;   // 20:21
} L9B0_IRIS_117_T;

/*-----------------------------------------------------------------------------
	0x43dc iris_118 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 oadj_y_offo                     : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 oadj_y_offi                     : 11;  // 12:22
} L9B0_IRIS_118_T;

/*-----------------------------------------------------------------------------
	0x43e0 iris_119 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 oadj_y_coeff                    : 14;  //  0:13
} L9B0_IRIS_119_T;

/*-----------------------------------------------------------------------------
	0x43e4 iris_120 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 oadj_c_offo                     : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 oadj_c_offi                     : 11;  // 12:22
} L9B0_IRIS_120_T;

/*-----------------------------------------------------------------------------
	0x43e8 iris_121 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 oadj_c_coeff                    : 14;  //  0:13
} L9B0_IRIS_121_T;

/*-----------------------------------------------------------------------------
	0x43ec iris_122 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 adc_unity_gain_value            : 4;   //  0: 3
} L9B0_IRIS_122_T;

/*-----------------------------------------------------------------------------
	0x43f0 iris_123 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 frame_motion_th1                : 16;  //  0:15
	UINT32 frame_motion_th0                : 16;  // 16:31
} L9B0_IRIS_123_T;

/*-----------------------------------------------------------------------------
	0x43f4 iris_124 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 iblank_half_lvl0                : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 isynctip_lvl0                   : 10;  // 12:21
} L9B0_IRIS_124_T;

/*-----------------------------------------------------------------------------
	0x43f8 iris_125 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sync_int_blank_lvl0             : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 ipeak_chroma_m768_lvl0          : 10;  // 12:21
} L9B0_IRIS_125_T;

/*-----------------------------------------------------------------------------
	0x43fc iris_126 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sync_int_blank_vid_lvl0         : 8;   //  0: 7
	UINT32 int_black_ped_vid_lvl0          : 10;  //  8:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 int_blank_vid_lvl0              : 10;  // 20:29
} L9B0_IRIS_126_T;

/*-----------------------------------------------------------------------------
	0x4400 iris_127 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 int_vbi_blank_vid_lvl0          : 8;   //  0: 7
} L9B0_IRIS_127_T;

/*-----------------------------------------------------------------------------
	0x4404 iris_128 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 internal_sync_midpt             : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 internal_sync_level             : 13;  // 16:28
} L9B0_IRIS_128_T;

/*-----------------------------------------------------------------------------
	0x4408 iris_129 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sync_internal_sync_midpt        : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 internal_blank_level            : 13;  // 12:24
} L9B0_IRIS_129_T;

/*-----------------------------------------------------------------------------
	0x440c iris_130 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 adc_blank_level                 : 10;  //  0: 9
} L9B0_IRIS_130_T;

/*-----------------------------------------------------------------------------
	0x4410 iris_131 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hrs_alpha_croff                 : 8;   //  0: 7
	UINT32 hrs_alpha_cboff                 : 8;   //  8:15
	UINT32 hrs_alpha_yoff                  : 8;   // 16:23
} L9B0_IRIS_131_T;

/*-----------------------------------------------------------------------------
	0x4414 iris_132 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cphase_adjust                   : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 cphase_adjust_sel               : 1;   //     4
} L9B0_IRIS_132_T;

/*-----------------------------------------------------------------------------
	0x4418 iris_133 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 adap_clf_mode                   : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 cb_delay                        : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 yc444                           : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 ycadj_cr_p                      : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 oadj_swap                       : 1;   //    16
} L9B0_IRIS_133_T;

/*-----------------------------------------------------------------------------
	0x441c iris_134 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 lpf_tap_0_0                     : 16;  //  0:15
	UINT32 lpf_0_en                        : 1;   //    16
} L9B0_IRIS_134_T;

/*-----------------------------------------------------------------------------
	0x4420 iris_135 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 lpf_tap_0_2                     : 16;  //  0:15
	UINT32 lpf_tap_0_1                     : 16;  // 16:31
} L9B0_IRIS_135_T;

/*-----------------------------------------------------------------------------
	0x4424 iris_136 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 lpf_tap_0_4                     : 16;  //  0:15
	UINT32 lpf_tap_0_3                     : 16;  // 16:31
} L9B0_IRIS_136_T;

/*-----------------------------------------------------------------------------
	0x4428 iris_137 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 lpf_tap_0_6                     : 16;  //  0:15
	UINT32 lpf_tap_0_5                     : 16;  // 16:31
} L9B0_IRIS_137_T;

/*-----------------------------------------------------------------------------
	0x442c iris_138 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_missing_max                  : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 hs_match_max                    : 6;   //  8:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 hs_cnt_mode                     : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 hs_sync_mode                    : 3;   // 20:22
	UINT32                                 : 1;   //    23 reserved
	UINT32 status_pseudo_sync              : 4;   // 24:27
} L9B0_IRIS_138_T;

/*-----------------------------------------------------------------------------
	0x4430 iris_139 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_length_prd_0                 : 24;  //  0:23
} L9B0_IRIS_139_T;

/*-----------------------------------------------------------------------------
	0x4434 iris_140 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_length_prd_th_0              : 24;  //  0:23
} L9B0_IRIS_140_T;

/*-----------------------------------------------------------------------------
	0x4438 iris_141 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_length_pos_0                 : 24;  //  0:23
} L9B0_IRIS_141_T;

/*-----------------------------------------------------------------------------
	0x443c iris_142 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_length_pos_th_0              : 24;  //  0:23
} L9B0_IRIS_142_T;

/*-----------------------------------------------------------------------------
	0x4440 iris_143 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_length_prd_1                 : 24;  //  0:23
} L9B0_IRIS_143_T;

/*-----------------------------------------------------------------------------
	0x4444 iris_144 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_length_prd_th_1              : 24;  //  0:23
} L9B0_IRIS_144_T;

/*-----------------------------------------------------------------------------
	0x4448 iris_145 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hs_length_pos_1                 : 24;  //  0:23
} L9B0_IRIS_145_T;

/*-----------------------------------------------------------------------------
	0x444c iris_146 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_cnt_mode                     : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 vs_sync_mode                    : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 hs_length_pos_th_1              : 24;  //  8:31
} L9B0_IRIS_146_T;

/*-----------------------------------------------------------------------------
	0x4450 iris_147 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_missing_max                  : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 vs_match_max                    : 6;   //  8:13
} L9B0_IRIS_147_T;

/*-----------------------------------------------------------------------------
	0x4454 iris_148 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_length_prd_0                 : 24;  //  0:23
} L9B0_IRIS_148_T;

/*-----------------------------------------------------------------------------
	0x4458 iris_149 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_length_prd_th_0              : 24;  //  0:23
} L9B0_IRIS_149_T;

/*-----------------------------------------------------------------------------
	0x445c iris_150 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_length_pos_0                 : 24;  //  0:23
} L9B0_IRIS_150_T;

/*-----------------------------------------------------------------------------
	0x4460 iris_151 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_length_pos_th_0              : 24;  //  0:23
} L9B0_IRIS_151_T;

/*-----------------------------------------------------------------------------
	0x4464 iris_152 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_length_prd_1                 : 24;  //  0:23
} L9B0_IRIS_152_T;

/*-----------------------------------------------------------------------------
	0x4468 iris_153 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_length_prd_th_1              : 24;  //  0:23
} L9B0_IRIS_153_T;

/*-----------------------------------------------------------------------------
	0x446c iris_154 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vs_length_pos_1                 : 24;  //  0:23
} L9B0_IRIS_154_T;

/*-----------------------------------------------------------------------------
	0x4470 iris_155 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_cnt_mode                     : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 ha_sync_mode                    : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 vs_length_pos_th_1              : 24;  //  8:31
} L9B0_IRIS_155_T;

/*-----------------------------------------------------------------------------
	0x4474 iris_156 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_missing_max                  : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 ha_match_max                    : 6;   //  8:13
} L9B0_IRIS_156_T;

/*-----------------------------------------------------------------------------
	0x4478 iris_157 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_length_prd_0                 : 24;  //  0:23
} L9B0_IRIS_157_T;

/*-----------------------------------------------------------------------------
	0x447c iris_158 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_length_prd_th_0              : 24;  //  0:23
} L9B0_IRIS_158_T;

/*-----------------------------------------------------------------------------
	0x4480 iris_159 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_length_pos_0                 : 24;  //  0:23
} L9B0_IRIS_159_T;

/*-----------------------------------------------------------------------------
	0x4484 iris_160 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_length_pos_th_0              : 24;  //  0:23
} L9B0_IRIS_160_T;

/*-----------------------------------------------------------------------------
	0x4488 iris_161 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_length_prd_1                 : 24;  //  0:23
} L9B0_IRIS_161_T;

/*-----------------------------------------------------------------------------
	0x448c iris_162 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_length_prd_th_1              : 24;  //  0:23
} L9B0_IRIS_162_T;

/*-----------------------------------------------------------------------------
	0x4490 iris_163 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ha_length_pos_1                 : 24;  //  0:23
} L9B0_IRIS_163_T;

/*-----------------------------------------------------------------------------
	0x4494 iris_164 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_cnt_mode                     : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 va_sync_mode                    : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 ha_length_pos_th_1              : 24;  //  8:31
} L9B0_IRIS_164_T;

/*-----------------------------------------------------------------------------
	0x4498 iris_165 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_missing_max                  : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 va_match_max                    : 6;   //  8:13
} L9B0_IRIS_165_T;

/*-----------------------------------------------------------------------------
	0x449c iris_166 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_prd_0                 : 24;  //  0:23
} L9B0_IRIS_166_T;

/*-----------------------------------------------------------------------------
	0x44a0 iris_167 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_prd_th_0              : 24;  //  0:23
} L9B0_IRIS_167_T;

/*-----------------------------------------------------------------------------
	0x44a4 iris_168 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_pos_0                 : 24;  //  0:23
} L9B0_IRIS_168_T;

/*-----------------------------------------------------------------------------
	0x44a8 iris_169 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_pos_th_0              : 24;  //  0:23
} L9B0_IRIS_169_T;

/*-----------------------------------------------------------------------------
	0x44ac iris_170 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_prd_1                 : 24;  //  0:23
} L9B0_IRIS_170_T;

/*-----------------------------------------------------------------------------
	0x44b0 iris_171 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_prd_th_1              : 24;  //  0:23
} L9B0_IRIS_171_T;

/*-----------------------------------------------------------------------------
	0x44b4 iris_172 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_pos_1                 : 24;  //  0:23
} L9B0_IRIS_172_T;

/*-----------------------------------------------------------------------------
	0x44b8 iris_173 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 va_length_pos_th_1              : 24;  //  0:23
} L9B0_IRIS_173_T;

/*-----------------------------------------------------------------------------
	0x44bc iris_174 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sw_rst_blk                      : 8;   //  0: 7
} L9B0_IRIS_174_T;

/*-----------------------------------------------------------------------------
	0x44c0 iris_175 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_cenable_f0cnt            : 20;  //  0:19
	UINT32 status_cenable_ctrl             : 7;   // 20:26
} L9B0_IRIS_175_T;

/*-----------------------------------------------------------------------------
	0x44c4 iris_176 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_cenable_lcnt             : 12;  //  0:11
	UINT32 status_cenable_f1cnt            : 20;  // 12:31
} L9B0_IRIS_176_T;

/*-----------------------------------------------------------------------------
	0x44c8 iris_177 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_updn_rst                 : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 clampagc_updn                   : 5;   //  4: 8
} L9B0_IRIS_177_T;

/*-----------------------------------------------------------------------------
	0x44cc iris_178 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 status_updn                     : 32;  //  0:31
} L9B0_IRIS_178_T;

/*-----------------------------------------------------------------------------
	0x44d0 iris_179 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_secam_pll                    : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs_secam_sw_old                 : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cs_auto_secam_level             : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs_chroma_activity_level        : 8;   // 12:19
	UINT32 cs_adaptive_chroma_mode         : 2;   // 20:21
	UINT32                                 : 2;   // 22:23 reserved
	UINT32 cs_sw_rst                       : 1;   //    24
} L9B0_IRIS_179_T;

/*-----------------------------------------------------------------------------
	0x44d4 iris_180 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_phase_offset_range           : 8;   //  0: 7
	UINT32 cs_avg_freq_range               : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 cs_issecam_th                   : 6;   // 12:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 cs_freq_offset_range            : 8;   // 20:27
} L9B0_IRIS_180_T;

/*-----------------------------------------------------------------------------
	0x44d8 iris_181 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_db_freq                      : 12;  //  0:11
	UINT32 cs_dr_freq                      : 12;  // 12:23
	UINT32 cs_ispal_th                     : 8;   // 24:31
} L9B0_IRIS_181_T;

/*-----------------------------------------------------------------------------
	0x44dc iris_182 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_cagc_en                      : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs_chroma_burst5or10            : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cs_pal60_mode                   : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs_ntsc443_mode                 : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cs_colour_mode                  : 3;   // 16:18
	UINT32                                 : 1;   //    19 reserved
	UINT32 cs_adaptive_mode                : 3;   // 20:22
	UINT32                                 : 1;   //    23 reserved
	UINT32 cs_secam_ybw                    : 2;   // 24:25
} L9B0_IRIS_182_T;

/*-----------------------------------------------------------------------------
	0x44e0 iris_183 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_cagc_coring_threshold        : 4;   //  0: 3
	UINT32 cs_cagc_coring                  : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 cs_cagc_unity_gain              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs_cagc_tc_p                    : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 cs_cagc_tc_ibig                 : 3;   // 16:18
	UINT32                                 : 1;   //    19 reserved
	UINT32 cs_cagc_tc_ismall               : 3;   // 20:22
	UINT32                                 : 1;   //    23 reserved
	UINT32 cs_cagc                         : 8;   // 24:31
} L9B0_IRIS_183_T;

/*-----------------------------------------------------------------------------
	0x44e4 iris_184 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_chroma_bw_lo                 : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 cs_ckill                        : 16;  //  4:19
	UINT32 cs_hlock_ckill                  : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 cs_vbi_ckill                    : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 cs_noburst_ckill                : 1;   //    28
} L9B0_IRIS_184_T;

/*-----------------------------------------------------------------------------
	0x44e8 iris_185 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_cdto_inc                     : 32;  //  0:31
} L9B0_IRIS_185_T;

/*-----------------------------------------------------------------------------
	0x44ec iris_186 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_cstate                       : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 cs_fixed_cstate                 : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cs_user_ckill_mode              : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 cs_lose_chromalock_mode         : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 cs_lose_chromalock_count        : 4;   // 16:19
	UINT32 cs_lose_chromalock_level        : 3;   // 20:22
	UINT32                                 : 1;   //    23 reserved
	UINT32 cs_lose_chromalock_ckill        : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 cs_palsw_level                  : 2;   // 28:29
} L9B0_IRIS_186_T;

/*-----------------------------------------------------------------------------
	0x44f0 iris_187 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_chroma_sel                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs_cphase_adjust                : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 cs_cphase_adjust_sel            : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs_mv_colourstripes_sel         : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cs_cstripe_detect_control       : 3;   // 16:18
} L9B0_IRIS_187_T;

/*-----------------------------------------------------------------------------
	0x44f4 iris_188 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_secam_detected               : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs_mv_colourstripes             : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 cs_status_cordic_freq           : 8;   //  8:15
	UINT32 cs_status_burst_mag             : 16;  // 16:31
} L9B0_IRIS_188_T;

/*-----------------------------------------------------------------------------
	0x44f8 iris_189 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs_chromalock                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs_status_cgain                 : 14;  //  4:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 cs_status_cmag                  : 8;   // 20:27
	UINT32 cs_pal_detected                 : 1;   //    28
} L9B0_IRIS_189_T;

/*-----------------------------------------------------------------------------
	0x44fc iris_190 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_secam_pll                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs1_secam_sw_old                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cs1_auto_secam_level            : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs1_chroma_activity_level       : 8;   // 12:19
	UINT32 cs1_adaptive_chroma_mode        : 2;   // 20:21
	UINT32                                 : 2;   // 22:23 reserved
	UINT32 cs1_sw_rst                      : 1;   //    24
} L9B0_IRIS_190_T;

/*-----------------------------------------------------------------------------
	0x4500 iris_191 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_phase_offset_range          : 8;   //  0: 7
	UINT32 cs1_avg_freq_range              : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 cs1_issecam_th                  : 6;   // 12:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 cs1_freq_offset_range           : 8;   // 20:27
} L9B0_IRIS_191_T;

/*-----------------------------------------------------------------------------
	0x4504 iris_192 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_db_freq                     : 12;  //  0:11
	UINT32 cs1_dr_freq                     : 12;  // 12:23
	UINT32 cs1_ispal_th                    : 8;   // 24:31
} L9B0_IRIS_192_T;

/*-----------------------------------------------------------------------------
	0x4508 iris_193 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_cagc_en                     : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs1_chroma_burst5or10           : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cs1_pal60_mode                  : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs1_ntsc443_mode                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cs1_colour_mode                 : 3;   // 16:18
	UINT32                                 : 1;   //    19 reserved
	UINT32 cs1_adaptive_mode               : 3;   // 20:22
	UINT32                                 : 1;   //    23 reserved
	UINT32 cs1_secam_ybw                   : 2;   // 24:25
} L9B0_IRIS_193_T;

/*-----------------------------------------------------------------------------
	0x450c iris_194 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_cagc_coring_threshold       : 4;   //  0: 3
	UINT32 cs1_cagc_coring                 : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 cs1_cagc_unity_gain             : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs1_cagc_tc_p                   : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 cs1_cagc_tc_ibig                : 3;   // 16:18
	UINT32                                 : 1;   //    19 reserved
	UINT32 cs1_cagc_tc_ismall              : 3;   // 20:22
	UINT32                                 : 1;   //    23 reserved
	UINT32 cs1_cagc                        : 8;   // 24:31
} L9B0_IRIS_194_T;

/*-----------------------------------------------------------------------------
	0x4510 iris_195 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_chroma_bw_lo                : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 cs1_ckill                       : 16;  //  4:19
	UINT32 cs1_hlock_ckill                 : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 cs1_vbi_ckill                   : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 cs1_noburst_ckill               : 1;   //    28
} L9B0_IRIS_195_T;

/*-----------------------------------------------------------------------------
	0x4514 iris_196 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_cdto_inc                    : 32;  //  0:31
} L9B0_IRIS_196_T;

/*-----------------------------------------------------------------------------
	0x4518 iris_197 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_cstate                      : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 cs1_fixed_cstate                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 cs1_user_ckill_mode             : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 cs1_lose_chromalock_mode        : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 cs1_lose_chromalock_count       : 4;   // 16:19
	UINT32 cs1_lose_chromalock_level       : 3;   // 20:22
	UINT32                                 : 1;   //    23 reserved
	UINT32 cs1_lose_chromalock_ckill       : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 cs1_palsw_level                 : 2;   // 28:29
} L9B0_IRIS_197_T;

/*-----------------------------------------------------------------------------
	0x451c iris_198 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_chroma_sel                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs1_cphase_adjust               : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 cs1_cphase_adjust_sel           : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 cs1_mv_colourstripes_sel        : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cs1_cstripe_detect_control      : 3;   // 16:18
} L9B0_IRIS_198_T;

/*-----------------------------------------------------------------------------
	0x4520 iris_199 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_secam_detected              : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs1_mv_colourstripes            : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 cs1_status_cordic_freq          : 8;   //  8:15
	UINT32 cs1_status_burst_mag            : 16;  // 16:31
} L9B0_IRIS_199_T;

/*-----------------------------------------------------------------------------
	0x4524 iris_200 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cs1_chromalock                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cs1_status_cgain                : 14;  //  4:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 cs1_status_cmag                 : 8;   // 20:27
	UINT32 cs1_pal_detected                : 1;   //    28
} L9B0_IRIS_200_T;

/*-----------------------------------------------------------------------------
	0x4528 iris_201 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 estfrdp_ctrl                    : 5;   //  0: 4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 estfrdp_on                      : 1;   //     8
} L9B0_IRIS_201_T;

/*-----------------------------------------------------------------------------
	0x452c iris_202 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 estfrdp_tgt_cf0cnt              : 20;  //  0:19
} L9B0_IRIS_202_T;

/*-----------------------------------------------------------------------------
	0x4530 iris_203 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 estfrdp_tgt_cf1cnt              : 20;  //  0:19
} L9B0_IRIS_203_T;

/*-----------------------------------------------------------------------------
	0x4534 iris_204 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 estfrdp_err_win1_u              : 8;   //  0: 7
	UINT32 estfrdp_err_win1_l              : 8;   //  8:15
	UINT32 estfrdp_err_win0_u              : 8;   // 16:23
	UINT32 estfrdp_err_win0_l              : 8;   // 24:31
} L9B0_IRIS_204_T;

/*-----------------------------------------------------------------------------
	0x4538 iris_205 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 estfrdp_err_flag_th             : 8;   //  0: 7
} L9B0_IRIS_205_T;

/*-----------------------------------------------------------------------------
	0x453c iris_206 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 estfrdp_err                     : 8;   //  0: 7
	UINT32 estfrdp_err_flag                : 1;   //     8
} L9B0_IRIS_206_T;

/*-----------------------------------------------------------------------------
	0x4540 iris_207 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync_width                     : 4;   //  0: 3
} L9B0_IRIS_207_T;

/*-----------------------------------------------------------------------------
	0x4544 iris_208 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl0                  : 32;  //  0:31
} L9B0_IRIS_208_T;

/*-----------------------------------------------------------------------------
	0x4548 iris_209 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl1                  : 32;  //  0:31
} L9B0_IRIS_209_T;

/*-----------------------------------------------------------------------------
	0x454c iris_210 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl2                  : 32;  //  0:31
} L9B0_IRIS_210_T;

/*-----------------------------------------------------------------------------
	0x4550 iris_211 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl3                  : 32;  //  0:31
} L9B0_IRIS_211_T;

/*-----------------------------------------------------------------------------
	0x4554 iris_212 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl4                  : 32;  //  0:31
} L9B0_IRIS_212_T;

/*-----------------------------------------------------------------------------
	0x4558 iris_213 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl5                  : 32;  //  0:31
} L9B0_IRIS_213_T;

/*-----------------------------------------------------------------------------
	0x455c iris_214 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl6                  : 32;  //  0:31
} L9B0_IRIS_214_T;

/*-----------------------------------------------------------------------------
	0x4560 iris_215 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl7                  : 32;  //  0:31
} L9B0_IRIS_215_T;

/*-----------------------------------------------------------------------------
	0x4564 iris_216 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl8                  : 32;  //  0:31
} L9B0_IRIS_216_T;

/*-----------------------------------------------------------------------------
	0x4568 iris_217 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl9                  : 32;  //  0:31
} L9B0_IRIS_217_T;

/*-----------------------------------------------------------------------------
	0x456c iris_218 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl10                 : 32;  //  0:31
} L9B0_IRIS_218_T;

/*-----------------------------------------------------------------------------
	0x4570 iris_219 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl0                  : 32;  //  0:31
} L9B0_IRIS_219_T;

/*-----------------------------------------------------------------------------
	0x4574 iris_220 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl1                  : 32;  //  0:31
} L9B0_IRIS_220_T;

/*-----------------------------------------------------------------------------
	0x4578 iris_221 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl2                  : 32;  //  0:31
} L9B0_IRIS_221_T;

/*-----------------------------------------------------------------------------
	0x457c iris_222 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl3                  : 32;  //  0:31
} L9B0_IRIS_222_T;

/*-----------------------------------------------------------------------------
	0x4580 iris_223 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl4                  : 32;  //  0:31
} L9B0_IRIS_223_T;

/*-----------------------------------------------------------------------------
	0x4584 iris_224 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl5                  : 32;  //  0:31
} L9B0_IRIS_224_T;

/*-----------------------------------------------------------------------------
	0x4588 iris_225 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl6                  : 32;  //  0:31
} L9B0_IRIS_225_T;

/*-----------------------------------------------------------------------------
	0x458c iris_226 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_ctrl7                  : 32;  //  0:31
} L9B0_IRIS_226_T;

/*-----------------------------------------------------------------------------
	0x4590 iris_227 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl0                  : 32;  //  0:31
} L9B0_IRIS_227_T;

/*-----------------------------------------------------------------------------
	0x4594 iris_228 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl1                  : 32;  //  0:31
} L9B0_IRIS_228_T;

/*-----------------------------------------------------------------------------
	0x4598 iris_229 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl2                  : 32;  //  0:31
} L9B0_IRIS_229_T;

/*-----------------------------------------------------------------------------
	0x459c iris_230 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl3                  : 32;  //  0:31
} L9B0_IRIS_230_T;

/*-----------------------------------------------------------------------------
	0x45a0 iris_231 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl4                  : 32;  //  0:31
} L9B0_IRIS_231_T;

/*-----------------------------------------------------------------------------
	0x45a4 iris_232 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl5                  : 32;  //  0:31
} L9B0_IRIS_232_T;

/*-----------------------------------------------------------------------------
	0x45a8 iris_233 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl6                  : 32;  //  0:31
} L9B0_IRIS_233_T;

/*-----------------------------------------------------------------------------
	0x45ac iris_234 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_st_ctrl7                  : 32;  //  0:31
} L9B0_IRIS_234_T;

/*-----------------------------------------------------------------------------
	0x45b0 iris_235 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_blend_ctrl0               : 32;  //  0:31
} L9B0_IRIS_235_T;

/*-----------------------------------------------------------------------------
	0x45b4 iris_236 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl11                 : 32;  //  0:31
} L9B0_IRIS_236_T;

/*-----------------------------------------------------------------------------
	0x45b8 iris_237 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl12                 : 32;  //  0:31
} L9B0_IRIS_237_T;

/*-----------------------------------------------------------------------------
	0x45bc iris_238 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl13                 : 32;  //  0:31
} L9B0_IRIS_238_T;

/*-----------------------------------------------------------------------------
	0x45c0 iris_239 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl14                 : 32;  //  0:31
} L9B0_IRIS_239_T;

/*-----------------------------------------------------------------------------
	0x45c4 iris_240 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl15                 : 32;  //  0:31
} L9B0_IRIS_240_T;

/*-----------------------------------------------------------------------------
	0x45c8 iris_241 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl0                     : 32;  //  0:31
} L9B0_IRIS_241_T;

/*-----------------------------------------------------------------------------
	0x45cc iris_242 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl1                     : 32;  //  0:31
} L9B0_IRIS_242_T;

/*-----------------------------------------------------------------------------
	0x45d0 iris_243 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl2                     : 32;  //  0:31
} L9B0_IRIS_243_T;

/*-----------------------------------------------------------------------------
	0x45d4 iris_244 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl3                     : 32;  //  0:31
} L9B0_IRIS_244_T;

/*-----------------------------------------------------------------------------
	0x45d8 iris_245 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl4                     : 32;  //  0:31
} L9B0_IRIS_245_T;

/*-----------------------------------------------------------------------------
	0x45dc iris_246 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl5                     : 32;  //  0:31
} L9B0_IRIS_246_T;

/*-----------------------------------------------------------------------------
	0x45e0 iris_247 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl6                     : 32;  //  0:31
} L9B0_IRIS_247_T;

/*-----------------------------------------------------------------------------
	0x45e4 iris_248 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl7                     : 32;  //  0:31
} L9B0_IRIS_248_T;

/*-----------------------------------------------------------------------------
	0x45e8 iris_249 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl8                     : 32;  //  0:31
} L9B0_IRIS_249_T;

/*-----------------------------------------------------------------------------
	0x45ec iris_250 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl9                     : 32;  //  0:31
} L9B0_IRIS_250_T;

/*-----------------------------------------------------------------------------
	0x45f0 iris_251 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl10                    : 32;  //  0:31
} L9B0_IRIS_251_T;

/*-----------------------------------------------------------------------------
	0x45f4 iris_252 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_0              : 32;  //  0:31
} L9B0_IRIS_252_T;

/*-----------------------------------------------------------------------------
	0x45f8 iris_253 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_1              : 32;  //  0:31
} L9B0_IRIS_253_T;

/*-----------------------------------------------------------------------------
	0x45fc iris_254 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_2              : 32;  //  0:31
} L9B0_IRIS_254_T;

/*-----------------------------------------------------------------------------
	0x4600 iris_255 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_3              : 32;  //  0:31
} L9B0_IRIS_255_T;

/*-----------------------------------------------------------------------------
	0x4604 iris_256 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_4              : 32;  //  0:31
} L9B0_IRIS_256_T;

/*-----------------------------------------------------------------------------
	0x4608 iris_257 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_5              : 32;  //  0:31
} L9B0_IRIS_257_T;

/*-----------------------------------------------------------------------------
	0x460c iris_258 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hrs_cx2_coef2                   : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 hrs_cx2_coef1                   : 11;  // 12:22
} L9B0_IRIS_258_T;

/*-----------------------------------------------------------------------------
	0x4610 iris_259 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hrs_cx2_coef4                   : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 hrs_cx2_coef3                   : 11;  // 12:22
} L9B0_IRIS_259_T;

/*-----------------------------------------------------------------------------
	0x4614 iris_260 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hrs_cx2_coef6                   : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 hrs_cx2_coef5                   : 11;  // 12:22
} L9B0_IRIS_260_T;

/*-----------------------------------------------------------------------------
	0x4618 iris_261 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hrs_cx2_coef8                   : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 hrs_cx2_coef7                   : 11;  // 12:22
} L9B0_IRIS_261_T;

/*-----------------------------------------------------------------------------
	0x461c iris_262 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hrs_ha_width                    : 8;   //  0: 7
	UINT32 hrs_ha_start                    : 8;   //  8:15
} L9B0_IRIS_262_T;

/*-----------------------------------------------------------------------------
	0x4620 iris_263 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cti0_en                         : 1;   //     0
	UINT32 cti0_tap                        : 1;   //     1
	UINT32 cti0_minmax_en                  : 1;   //     2
	UINT32                                 : 1;   //     3 reserved
	UINT32 cti0_gain                       : 8;   //  4:11
} L9B0_IRIS_263_T;

/*-----------------------------------------------------------------------------
	0x4624 iris_264 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cti0_en                         : 1;   //     0
	UINT32 cti0_tap                        : 1;   //     1
	UINT32 cti0_minmax_en                  : 1;   //     2
	UINT32                                 : 1;   //     3 reserved
	UINT32 cti0_gain                       : 8;   //  4:11
} L9B0_IRIS_264_T;

/*-----------------------------------------------------------------------------
	0x4630 iris_265 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_3d_status0                : 32;  //  0:31
} L9B0_IRIS_265_T;

/*-----------------------------------------------------------------------------
	0x4634 iris_266 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_6              : 32;  //  0:31
} L9B0_IRIS_266_T;

/*-----------------------------------------------------------------------------
	0x4638 iris_267 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cdetect_lpf_ctrl_7              : 32;  //  0:31
} L9B0_IRIS_267_T;

/*-----------------------------------------------------------------------------
	0x463c iris_268 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycadjust_sat_ctrl_0             : 32;  //  0:31
} L9B0_IRIS_268_T;

/*-----------------------------------------------------------------------------
	0x4640 iris_269 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl16                 : 32;  //  0:31
} L9B0_IRIS_269_T;

/*-----------------------------------------------------------------------------
	0x4644 iris_270 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl17                 : 32;  //  0:31
} L9B0_IRIS_270_T;

/*-----------------------------------------------------------------------------
	0x4648 iris_271 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 burst2_gate_end                 : 8;   //  0: 7
	UINT32 burst2_gate_start               : 8;   //  8:15
	UINT32 burst1_gate_end                 : 8;   // 16:23
	UINT32 burst1_gate_start               : 8;   // 24:31
} L9B0_IRIS_271_T;

/*-----------------------------------------------------------------------------
	0x464c iris_272 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cordic2_gate_end                : 8;   //  0: 7
	UINT32 cordic2_gate_start              : 8;   //  8:15
	UINT32 cordic1_gate_end                : 8;   // 16:23
	UINT32 cordic1_gate_start              : 8;   // 24:31
} L9B0_IRIS_272_T;

/*-----------------------------------------------------------------------------
	0x4650 iris_273 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_cbcr_ctrl                 : 16;  //  0:15
	UINT32 status_vdetect_vcount           : 10;  // 16:25
	UINT32                                 : 2;   // 26:27 reserved
	UINT32 vactive_height_auto             : 1;   //    28
} L9B0_IRIS_273_T;

/*-----------------------------------------------------------------------------
	0x4654 iris_274 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_1            : 17;  //  0:16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 secam_y_notch_mode              : 1;   //    20
} L9B0_IRIS_274_T;

/*-----------------------------------------------------------------------------
	0x4658 iris_275 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_2            : 17;  //  0:16
} L9B0_IRIS_275_T;

/*-----------------------------------------------------------------------------
	0x465c iris_276 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_3            : 17;  //  0:16
} L9B0_IRIS_276_T;

/*-----------------------------------------------------------------------------
	0x4660 iris_277 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_4            : 17;  //  0:16
} L9B0_IRIS_277_T;

/*-----------------------------------------------------------------------------
	0x4664 iris_278 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_5            : 17;  //  0:16
} L9B0_IRIS_278_T;

/*-----------------------------------------------------------------------------
	0x4668 iris_279 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_6            : 17;  //  0:16
} L9B0_IRIS_279_T;

/*-----------------------------------------------------------------------------
	0x466c iris_280 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_7            : 17;  //  0:16
} L9B0_IRIS_280_T;

/*-----------------------------------------------------------------------------
	0x4670 iris_281 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_8            : 17;  //  0:16
} L9B0_IRIS_281_T;

/*-----------------------------------------------------------------------------
	0x4674 iris_282 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_y_notch_ctrl_9            : 17;  //  0:16
} L9B0_IRIS_282_T;

/*-----------------------------------------------------------------------------
	0x4678 iris_283 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_1            : 17;  //  0:16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 secam_c_notch_sel               : 1;   //    20
} L9B0_IRIS_283_T;

/*-----------------------------------------------------------------------------
	0x467c iris_284 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_2            : 17;  //  0:16
} L9B0_IRIS_284_T;

/*-----------------------------------------------------------------------------
	0x4680 iris_285 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_3            : 17;  //  0:16
} L9B0_IRIS_285_T;

/*-----------------------------------------------------------------------------
	0x4684 iris_286 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_4            : 17;  //  0:16
} L9B0_IRIS_286_T;

/*-----------------------------------------------------------------------------
	0x4688 iris_287 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_5            : 17;  //  0:16
} L9B0_IRIS_287_T;

/*-----------------------------------------------------------------------------
	0x468c iris_288 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_6            : 17;  //  0:16
} L9B0_IRIS_288_T;

/*-----------------------------------------------------------------------------
	0x4690 iris_289 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_7            : 17;  //  0:16
} L9B0_IRIS_289_T;

/*-----------------------------------------------------------------------------
	0x4694 iris_290 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_8            : 17;  //  0:16
} L9B0_IRIS_290_T;

/*-----------------------------------------------------------------------------
	0x4698 iris_291 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_c_notch_ctrl_9            : 17;  //  0:16
} L9B0_IRIS_291_T;

/*-----------------------------------------------------------------------------
	0x469c iris_292 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_ctrl11                    : 32;  //  0:31
} L9B0_IRIS_292_T;

/*-----------------------------------------------------------------------------
	0x46a0 iris_293 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_ybw2                      : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 secam_y_delay                   : 6;   //  4: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 secam_dcr_passthrough           : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 v_valid_inv                     : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 secam_lb_en                     : 1;   //    20
} L9B0_IRIS_293_T;

/*-----------------------------------------------------------------------------
	0x46a4 iris_294 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_dcr_ctrl_0                : 32;  //  0:31
} L9B0_IRIS_294_T;

/*-----------------------------------------------------------------------------
	0x46a8 iris_295 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_dcr_ctrl_1                : 32;  //  0:31
} L9B0_IRIS_295_T;

/*-----------------------------------------------------------------------------
	0x46ac iris_296 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 secam_dcr_ctrl_2                : 32;  //  0:31
} L9B0_IRIS_296_T;

/*-----------------------------------------------------------------------------
	0x46b0 iris_297 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 yup_rise                        : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 ydn_cnt                         : 8;   // 12:19
	UINT32 yup_cnt                         : 8;   // 20:27
} L9B0_IRIS_297_T;

/*-----------------------------------------------------------------------------
	0x46b4 iris_298 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ydn_rise                        : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 yup_fall                        : 11;  // 12:22
} L9B0_IRIS_298_T;

/*-----------------------------------------------------------------------------
	0x46b8 iris_299 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 clmap_sel                       : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 ydn_fall                        : 11;  //  4:14
} L9B0_IRIS_299_T;

/*-----------------------------------------------------------------------------
	0x46bc iris_300 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl18                 : 32;  //  0:31
} L9B0_IRIS_300_T;

/*-----------------------------------------------------------------------------
	0x46c0 iris_301 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl19                 : 32;  //  0:31
} L9B0_IRIS_301_T;

/*-----------------------------------------------------------------------------
	0x46c4 iris_302 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ycsep_2d_ctrl20                 : 32;  //  0:31
} L9B0_IRIS_302_T;

/*-----------------------------------------------------------------------------
	0x46c8 iris_303 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wmask_ctrl_0                    : 32;  //  0:31
} L9B0_IRIS_303_T;

/*-----------------------------------------------------------------------------
	0x46cc iris_304 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wmask_ctrl_1                    : 32;  //  0:31
} L9B0_IRIS_304_T;

/*-----------------------------------------------------------------------------
	0x4800 vbi_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wss625_rd_done                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cc_rd_done                      : 1;   //     4
} L9B0_VBI_001_T;

/*-----------------------------------------------------------------------------
	0x4804 vbi_002 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cc_rdy                          : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cc_data0                        : 8;   //  4:11
	UINT32 cc_data1                        : 8;   // 12:19
} L9B0_VBI_002_T;

/*-----------------------------------------------------------------------------
	0x4808 vbi_003 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 wssdata0                        : 8;   //  0: 7
	UINT32 wssdata1                        : 8;   //  8:15
	UINT32 wssdata2                        : 8;   // 16:23
	UINT32 wss_rdy                         : 1;   //    24
} L9B0_VBI_003_T;

/*-----------------------------------------------------------------------------
	0x480c vbi_004 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cc_short_start                  : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 vbi_muxout                      : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 vbi_hsyncout                    : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 adap_slvl_en                    : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 vbi_st_err_ignored              : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 vbi_en                          : 1;   //    20
} L9B0_VBI_004_T;

/*-----------------------------------------------------------------------------
	0x4810 vbi_005 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_lpf_bw                      : 2;   //  0: 1
} L9B0_VBI_005_T;

/*-----------------------------------------------------------------------------
	0x4814 vbi_006 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_data_hlvl                   : 8;   //  0: 7
	UINT32 start_code                      : 8;   //  8:15
} L9B0_VBI_006_T;

/*-----------------------------------------------------------------------------
	0x4818 vbi_007 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbil9                           : 8;   //  0: 7
	UINT32 vbil8                           : 8;   //  8:15
	UINT32 vbil7                           : 8;   // 16:23
	UINT32 vbil6                           : 8;   // 24:31
} L9B0_VBI_007_T;

/*-----------------------------------------------------------------------------
	0x481c vbi_008 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbil13                          : 8;   //  0: 7
	UINT32 vbil12                          : 8;   //  8:15
	UINT32 vbil11                          : 8;   // 16:23
	UINT32 vbil10                          : 8;   // 24:31
} L9B0_VBI_008_T;

/*-----------------------------------------------------------------------------
	0x4820 vbi_009 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbil17                          : 8;   //  0: 7
	UINT32 vbil16                          : 8;   //  8:15
	UINT32 vbil15                          : 8;   // 16:23
	UINT32 vbil14                          : 8;   // 24:31
} L9B0_VBI_009_T;

/*-----------------------------------------------------------------------------
	0x4824 vbi_010 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbil21                          : 8;   //  0: 7
	UINT32 vbil20                          : 8;   //  8:15
	UINT32 vbil19                          : 8;   // 16:23
	UINT32 vbil18                          : 8;   // 24:31
} L9B0_VBI_010_T;

/*-----------------------------------------------------------------------------
	0x4828 vbi_011 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbil25                          : 8;   //  0: 7
	UINT32 vbil24                          : 8;   //  8:15
	UINT32 vbil23                          : 8;   // 16:23
	UINT32 vbil22                          : 8;   // 24:31
} L9B0_VBI_011_T;

/*-----------------------------------------------------------------------------
	0x482c vbi_012 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbil26                          : 8;   //  0: 7
} L9B0_VBI_012_T;

/*-----------------------------------------------------------------------------
	0x4830 vbi_013 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_vps_lpfil_fine_gain         : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 vbi_wss625_lpfil_fine_gain      : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 vbi_tele_lpfil_fine_gain        : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 vbi_cc_lpfil_fine_gain          : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 vbi_vps_slicer_mode             : 2;   // 16:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 vbi_wss_slicer_mode             : 2;   // 20:21
	UINT32                                 : 2;   // 22:23 reserved
	UINT32 vbi_tt_slicer_mode              : 2;   // 24:25
	UINT32                                 : 2;   // 26:27 reserved
	UINT32 vbi_cc_slicer_mode              : 2;   // 28:29
} L9B0_VBI_013_T;

/*-----------------------------------------------------------------------------
	0x4834 vbi_014 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 teletext_dto                    : 16;  //  0:15
	UINT32 caption_dto                     : 16;  // 16:31
} L9B0_VBI_014_T;

/*-----------------------------------------------------------------------------
	0x4838 vbi_015 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vps_dto                         : 16;  //  0:15
	UINT32 wss625_dto                      : 16;  // 16:31
} L9B0_VBI_015_T;

/*-----------------------------------------------------------------------------
	0x483c vbi_016 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vps_frame_start                 : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 teletext_frame_start            : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 wss625_frame_start              : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 caption_frame_start             : 2;   // 12:13
} L9B0_VBI_016_T;

/*-----------------------------------------------------------------------------
	0x4840 vbi_017 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_tele_lpfil_track_gain       : 4;   //  0: 3
	UINT32 vbi_tele_lpfil_acq_gain         : 4;   //  4: 7
	UINT32 vbi_cc_lpfil_track_gain         : 4;   //  8:11
	UINT32 vbi_cc_lpfil_acq_gain           : 4;   // 12:15
	UINT32 wssj_delta_ampl                 : 8;   // 16:23
} L9B0_VBI_017_T;

/*-----------------------------------------------------------------------------
	0x4844 vbi_018 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_vps_lpfil_track_gain        : 4;   //  0: 3
	UINT32 vbi_vps_lpfil_acq_gain          : 4;   //  4: 7
	UINT32 vbi_wss625_lpfil_track_gain     : 4;   //  8:11
	UINT32 vbi_wss625_lpfil_acq_gain       : 4;   // 12:15
} L9B0_VBI_018_T;

/*-----------------------------------------------------------------------------
	0x4848 vbi_019 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 teletext_runin_accum_ampl       : 8;   //  0: 7
	UINT32 caption_runin_accum_ampl        : 8;   //  8:15
} L9B0_VBI_019_T;

/*-----------------------------------------------------------------------------
	0x484c vbi_020 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vps_start                       : 8;   //  0: 7
	UINT32 teletext_start                  : 8;   //  8:15
	UINT32 wss625_start                    : 8;   // 16:23
	UINT32 caption_start                   : 8;   // 24:31
} L9B0_VBI_020_T;

/*-----------------------------------------------------------------------------
	0x4850 vbi_021 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_fixgate_en                  : 1;   //     0
} L9B0_VBI_021_T;

/*-----------------------------------------------------------------------------
	0x4854 vbi_022 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_vbi_st_err_ignored          : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 ttx_vbi_lpf_bw                  : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 ttx_vbi_hsyncout                : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 ttx_vbi_data_hlvl               : 8;   // 12:19
	UINT32 ttx_adap_slvl_en                : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 ttx_vbi_en                      : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 ttx_out_sel                     : 1;   //    28
} L9B0_VBI_022_T;

/*-----------------------------------------------------------------------------
	0x4858 vbi_023 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_teletext_start              : 8;   //  0: 7
	UINT32 ttx_vbi_tele_lpfil_fine_gain    : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 ttx_vbi_tele_lpfil_track_gain   : 4;   // 12:15
	UINT32 ttx_vbi_tele_lpfil_acq_gain     : 4;   // 16:19
	UINT32 ttx_teletext_runin_accum_ampl   : 8;   // 20:27
	UINT32 ttx_tt_slicer_mode              : 2;   // 28:29
} L9B0_VBI_023_T;

/*-----------------------------------------------------------------------------
	0x485c vbi_024 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_start_code                  : 8;   //  0: 7
	UINT32 ttx_teletext_frame_start        : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 ttx_teletext_dto                : 16;  // 12:27
	UINT32 ttx_vbi_fixgate_en              : 1;   //    28
} L9B0_VBI_024_T;

/*-----------------------------------------------------------------------------
	0x48a8 iris_mif_gmua_mon_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf2_pel_cnt                : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 ro_rbuf2_empty                  : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 ro_rbuf1_pel_cnt                : 11;  // 16:26
	UINT32                                 : 1;   //    27 reserved
	UINT32 ro_rbuf1_empty                  : 1;   //    28
} L9B0_IRIS_MIF_GMUA_MON_001_T;

/*-----------------------------------------------------------------------------
	0x48ac iris_mif_gmua_mon_002 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf4_pel_cnt                : 11;  //  0:10
	UINT32                                 : 1;   //    11 reserved
	UINT32 ro_rbuf4_empty                  : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 ro_rbuf3_pel_cnt                : 11;  // 16:26
	UINT32                                 : 1;   //    27 reserved
	UINT32 ro_rbuf3_empty                  : 1;   //    28
} L9B0_IRIS_MIF_GMUA_MON_002_T;

/*-----------------------------------------------------------------------------
	0x48b0 iris_mif_gmua_mon_003 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_wbuf_word_cnt                : 6;   //  0: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 ro_wbuf_empty                   : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 ro_wbuf_full                    : 1;   //    12
} L9B0_IRIS_MIF_GMUA_MON_003_T;

/*-----------------------------------------------------------------------------
	0x48b4 iris_mif_gmua_mon_004 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mon_wait_max_cnt                : 12;  //  0:11
} L9B0_IRIS_MIF_GMUA_MON_004_T;

/*-----------------------------------------------------------------------------
	0x48b8 iris_mif_gmua_mon_005 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_wr_wait_err              : 8;   //  0: 7
} L9B0_IRIS_MIF_GMUA_MON_005_T;

/*-----------------------------------------------------------------------------
	0x48bc iris_mif_gmua_mon_006 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd4_wait_err             : 8;   //  0: 7
	UINT32 ro_mon_rd3_wait_err             : 8;   //  8:15
	UINT32 ro_mon_rd2_wait_err             : 8;   // 16:23
	UINT32 ro_mon_rd1_wait_err             : 8;   // 24:31
} L9B0_IRIS_MIF_GMUA_MON_006_T;

/*-----------------------------------------------------------------------------
	0x48c0 iris_mif_gmua_mon_007 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_wr_req_num               : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 ro_mon_wr_req_que_cnt           : 3;   // 12:14
} L9B0_IRIS_MIF_GMUA_MON_007_T;

/*-----------------------------------------------------------------------------
	0x48c4 iris_mif_gmua_mon_008 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_wr_wait_cnt1             : 12;  //  0:11
	UINT32 ro_mon_wr_wait_cnt0             : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_008_T;

/*-----------------------------------------------------------------------------
	0x48c8 iris_mif_gmua_mon_009 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_wr_wait_cnt3             : 12;  //  0:11
	UINT32 ro_mon_wr_wait_cnt2             : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_009_T;

/*-----------------------------------------------------------------------------
	0x48cc iris_mif_gmua_mon_010 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd1_req_num              : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 ro_mon_rd1_req_que_cnt          : 3;   // 12:14
} L9B0_IRIS_MIF_GMUA_MON_010_T;

/*-----------------------------------------------------------------------------
	0x48d0 iris_mif_gmua_mon_011 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd1_wait_cnt1            : 12;  //  0:11
	UINT32 ro_mon_rd1_wait_cnt0            : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_011_T;

/*-----------------------------------------------------------------------------
	0x48d4 iris_mif_gmua_mon_012 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd1_wait_cnt3            : 12;  //  0:11
	UINT32 ro_mon_rd1_wait_cnt2            : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_012_T;

/*-----------------------------------------------------------------------------
	0x48d8 iris_mif_gmua_mon_013 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd2_req_num              : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 ro_mon_rd2_req_que_cnt          : 3;   // 12:14
} L9B0_IRIS_MIF_GMUA_MON_013_T;

/*-----------------------------------------------------------------------------
	0x48dc iris_mif_gmua_mon_014 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd2_wait_cnt1            : 12;  //  0:11
	UINT32 ro_mon_rd2_wait_cnt0            : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_014_T;

/*-----------------------------------------------------------------------------
	0x48e0 iris_mif_gmua_mon_015 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd2_wait_cnt3            : 12;  //  0:11
	UINT32 ro_mon_rd2_wait_cnt2            : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_015_T;

/*-----------------------------------------------------------------------------
	0x48e4 iris_mif_gmua_mon_016 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd3_req_num              : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 ro_mon_rd3_req_que_cnt          : 3;   // 12:14
} L9B0_IRIS_MIF_GMUA_MON_016_T;

/*-----------------------------------------------------------------------------
	0x48e8 iris_mif_gmua_mon_017 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd3_wait_cnt1            : 12;  //  0:11
	UINT32 ro_mon_rd3_wait_cnt0            : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_017_T;

/*-----------------------------------------------------------------------------
	0x48ec iris_mif_gmua_mon_018 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd3_wait_cnt3            : 12;  //  0:11
	UINT32 ro_mon_rd3_wait_cnt2            : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_018_T;

/*-----------------------------------------------------------------------------
	0x48f0 iris_mif_gmua_mon_019 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd4_req_num              : 10;  //  0: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 ro_mon_rd4_req_que_cnt          : 3;   // 12:14
} L9B0_IRIS_MIF_GMUA_MON_019_T;

/*-----------------------------------------------------------------------------
	0x48f4 iris_mif_gmua_mon_020 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd4_wait_cnt0            : 12;  //  0:11
} L9B0_IRIS_MIF_GMUA_MON_020_T;

/*-----------------------------------------------------------------------------
	0x48f8 iris_mif_gmua_mon_021 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd4_wait_cnt1            : 12;  //  0:11
} L9B0_IRIS_MIF_GMUA_MON_021_T;

/*-----------------------------------------------------------------------------
	0x48fc iris_mif_gmua_mon_022 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_mon_rd4_wait_cnt3            : 12;  //  0:11
	UINT32 ro_mon_rd4_wait_cnt2            : 12;  // 12:23
} L9B0_IRIS_MIF_GMUA_MON_022_T;

/*-----------------------------------------------------------------------------
	0x4900 iris_hif_ctrl0_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pending_enable                  : 1;   //     0
} L9B0_IRIS_HIF_CTRL0_001_T;

/*-----------------------------------------------------------------------------
	0x4904 iris_hif_ctrl1_001 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cv_timer_ctrl                   : 9;   //  0: 8
} L9B0_IRIS_HIF_CTRL1_001_T;

typedef struct {
	L9B0_CVD_INTR1_ENABLE0_T        cvd_intr1_enable0;               // 0x4100
	L9B0_CVD_INTR1_INTR0_T          cvd_intr1_intr0;                 // 0x4104
	L9B0_CVD_INTR1_CLEAR0_T         cvd_intr1_clear0;                // 0x4108
	L9B0_CVD_INTR1_ENABLE1_T        cvd_intr1_enable1;               // 0x410c
	L9B0_CVD_INTR1_INTR1_T          cvd_intr1_intr1;                 // 0x4110
	L9B0_CVD_INTR1_CLEAR1_T         cvd_intr1_clear1;                // 0x4114
	L9B0_CVD_INTR2_ENABLE0_T        cvd_intr2_enable0;               // 0x4118
	L9B0_CVD_INTR2_INTR0_T          cvd_intr2_intr0;                 // 0x411c
	L9B0_CVD_INTR2_CLEAR0_T         cvd_intr2_clear0;                // 0x4120
	L9B0_CVD_INTR2_ENABLE1_T        cvd_intr2_enable1;               // 0x4124
	L9B0_CVD_INTR2_INTR1_T          cvd_intr2_intr1;                 // 0x4128
	L9B0_CVD_INTR2_CLEAR1_T         cvd_intr2_clear1;                // 0x412c
	L9B0_TOP_001_T                  top_001;                         // 0x4130
	UINT32                          reserved0[3];                    // 0x4134~0x413c
	L9B0_IRIS_MIF_GMUA_001_T        iris_mif_gmua_001;               // 0x4140
	L9B0_IRIS_MIF_GMUA_002_T        iris_mif_gmua_002;               // 0x4144
	L9B0_IRIS_MIF_GMUA_003_T        iris_mif_gmua_003;               // 0x4148
	L9B0_IRIS_MIF_GMUA_004_T        iris_mif_gmua_004;               // 0x414c
	L9B0_IRIS_MIF_GMUA_005_T        iris_mif_gmua_005;               // 0x4150
	L9B0_IRIS_MIF_GMUA_006_T        iris_mif_gmua_006;               // 0x4154
	L9B0_IRIS_MIF_GMUA_007_T        iris_mif_gmua_007;               // 0x4158
	UINT32                          reserved1;                       // 0x415c
	L9B0_IRIS_MIF_GMUA_008_T        iris_mif_gmua_008;               // 0x4160
	L9B0_IRIS_MIF_GMUA_009_T        iris_mif_gmua_009;               // 0x4164
	L9B0_FASTBLANK_001_T            fastblank_001;                   // 0x4168
	L9B0_FASTBLANK_002_T            fastblank_002;                   // 0x416c
	L9B0_FASTBLANK_003_T            fastblank_003;                   // 0x4170
	L9B0_FASTBLANK_004_T            fastblank_004;                   // 0x4174
	L9B0_FASTBLANK_005_T            fastblank_005;                   // 0x4178
	L9B0_FASTBLANK_006_T            fastblank_006;                   // 0x417c
	L9B0_FASTBLANK_007_T            fastblank_007;                   // 0x4180
	L9B0_FASTBLANK_008_T            fastblank_008;                   // 0x4184
	L9B0_FASTBLANK_009_T            fastblank_009;                   // 0x4188
	L9B0_FASTBLANK_010_T            fastblank_010;                   // 0x418c
	L9B0_IRIS_DE_CTRL_001_T         iris_de_ctrl_001;                // 0x4190
	L9B0_VBI_CTRL_001_T             vbi_ctrl_001;                    // 0x4194
	L9B0_VBI_CTRL_002_T             vbi_ctrl_002;                    // 0x4198
	L9B0_VBI_CTRL_003_T             vbi_ctrl_003;                    // 0x419c
	L9B0_VBI_CTRL_004_T             vbi_ctrl_004;                    // 0x41a0
	L9B0_VBI_CTRL_005_T             vbi_ctrl_005;                    // 0x41a4
	L9B0_VBI_CTRL_006_T             vbi_ctrl_006;                    // 0x41a8
	L9B0_VBI_CTRL_007_T             vbi_ctrl_007;                    // 0x41ac
	L9B0_VBI_CTRL_008_T             vbi_ctrl_008;                    // 0x41b0
	L9B0_VBI_CTRL_009_T             vbi_ctrl_009;                    // 0x41b4
	UINT32                          reserved2[2];                    // 0x41b8~0x41bc
	L9B0_FAST_BLANK_STATUS_001_T    fast_blank_status_001;           // 0x41c0
	L9B0_CVBSAFE_001_T              cvbsafe_001;                     // 0x41c4
	UINT32                          reserved3[14];                   // 0x41c8~0x41fc
	L9B0_IRIS_001_T                 iris_001;                        // 0x4200
	L9B0_IRIS_002_T                 iris_002;                        // 0x4204
	L9B0_IRIS_003_T                 iris_003;                        // 0x4208
	L9B0_IRIS_004_T                 iris_004;                        // 0x420c
	L9B0_IRIS_005_T                 iris_005;                        // 0x4210
	L9B0_IRIS_006_T                 iris_006;                        // 0x4214
	L9B0_IRIS_007_T                 iris_007;                        // 0x4218
	L9B0_IRIS_008_T                 iris_008;                        // 0x421c
	L9B0_IRIS_009_T                 iris_009;                        // 0x4220
	L9B0_IRIS_010_T                 iris_010;                        // 0x4224
	UINT32                          reserved4[2];                    // 0x4228~0x422c
	L9B0_IRIS_011_T                 iris_011;                        // 0x4230
	L9B0_IRIS_012_T                 iris_012;                        // 0x4234
	L9B0_IRIS_013_T                 iris_013;                        // 0x4238
	L9B0_IRIS_014_T                 iris_014;                        // 0x423c
	L9B0_IRIS_015_T                 iris_015;                        // 0x4240
	L9B0_IRIS_016_T                 iris_016;                        // 0x4244
	L9B0_IRIS_017_T                 iris_017;                        // 0x4248
	L9B0_IRIS_018_T                 iris_018;                        // 0x424c
	L9B0_IRIS_019_T                 iris_019;                        // 0x4250
	L9B0_IRIS_020_T                 iris_020;                        // 0x4254
	L9B0_IRIS_021_T                 iris_021;                        // 0x4258
	L9B0_IRIS_022_T                 iris_022;                        // 0x425c
	L9B0_IRIS_023_T                 iris_023;                        // 0x4260
	L9B0_IRIS_024_T                 iris_024;                        // 0x4264
	L9B0_IRIS_025_T                 iris_025;                        // 0x4268
	L9B0_IRIS_026_T                 iris_026;                        // 0x426c
	L9B0_IRIS_027_T                 iris_027;                        // 0x4270
	L9B0_IRIS_028_T                 iris_028;                        // 0x4274
	L9B0_IRIS_029_T                 iris_029;                        // 0x4278
	L9B0_IRIS_030_T                 iris_030;                        // 0x427c
	L9B0_IRIS_031_T                 iris_031;                        // 0x4280
	L9B0_IRIS_032_T                 iris_032;                        // 0x4284
	L9B0_IRIS_033_T                 iris_033;                        // 0x4288
	L9B0_IRIS_034_T                 iris_034;                        // 0x428c
	L9B0_IRIS_035_T                 iris_035;                        // 0x4290
	L9B0_IRIS_036_T                 iris_036;                        // 0x4294
	L9B0_IRIS_037_T                 iris_037;                        // 0x4298
	L9B0_IRIS_038_T                 iris_038;                        // 0x429c
	L9B0_IRIS_039_T                 iris_039;                        // 0x42a0
	L9B0_IRIS_040_T                 iris_040;                        // 0x42a4
	L9B0_IRIS_041_T                 iris_041;                        // 0x42a8
	L9B0_IRIS_042_T                 iris_042;                        // 0x42ac
	L9B0_IRIS_043_T                 iris_043;                        // 0x42b0
	L9B0_IRIS_044_T                 iris_044;                        // 0x42b4
	L9B0_IRIS_045_T                 iris_045;                        // 0x42b8
	L9B0_IRIS_046_T                 iris_046;                        // 0x42bc
	L9B0_IRIS_047_T                 iris_047;                        // 0x42c0
	L9B0_IRIS_048_T                 iris_048;                        // 0x42c4
	L9B0_IRIS_049_T                 iris_049;                        // 0x42c8
	L9B0_IRIS_050_T                 iris_050;                        // 0x42cc
	L9B0_IRIS_051_T                 iris_051;                        // 0x42d0
	L9B0_IRIS_052_T                 iris_052;                        // 0x42d4
	L9B0_IRIS_053_T                 iris_053;                        // 0x42d8
	L9B0_IRIS_054_T                 iris_054;                        // 0x42dc
	L9B0_IRIS_055_T                 iris_055;                        // 0x42e0
	L9B0_IRIS_056_T                 iris_056;                        // 0x42e4
	L9B0_IRIS_057_T                 iris_057;                        // 0x42e8
	L9B0_IRIS_058_T                 iris_058;                        // 0x42ec
	L9B0_IRIS_059_T                 iris_059;                        // 0x42f0
	L9B0_IRIS_060_T                 iris_060;                        // 0x42f4
	L9B0_IRIS_061_T                 iris_061;                        // 0x42f8
	L9B0_IRIS_062_T                 iris_062;                        // 0x42fc
	L9B0_IRIS_063_T                 iris_063;                        // 0x4300
	L9B0_IRIS_064_T                 iris_064;                        // 0x4304
	L9B0_IRIS_065_T                 iris_065;                        // 0x4308
	L9B0_IRIS_066_T                 iris_066;                        // 0x430c
	L9B0_IRIS_067_T                 iris_067;                        // 0x4310
	L9B0_IRIS_068_T                 iris_068;                        // 0x4314
	L9B0_IRIS_069_T                 iris_069;                        // 0x4318
	L9B0_IRIS_070_T                 iris_070;                        // 0x431c
	L9B0_IRIS_071_T                 iris_071;                        // 0x4320
	L9B0_IRIS_072_T                 iris_072;                        // 0x4324
	L9B0_IRIS_073_T                 iris_073;                        // 0x4328
	L9B0_IRIS_074_T                 iris_074;                        // 0x432c
	L9B0_IRIS_075_T                 iris_075;                        // 0x4330
	L9B0_IRIS_076_T                 iris_076;                        // 0x4334
	L9B0_IRIS_077_T                 iris_077;                        // 0x4338
	L9B0_IRIS_078_T                 iris_078;                        // 0x433c
	L9B0_IRIS_079_T                 iris_079;                        // 0x4340
	L9B0_IRIS_080_T                 iris_080;                        // 0x4344
	L9B0_IRIS_081_T                 iris_081;                        // 0x4348
	L9B0_IRIS_082_T                 iris_082;                        // 0x434c
	L9B0_IRIS_083_T                 iris_083;                        // 0x4350
	L9B0_IRIS_084_T                 iris_084;                        // 0x4354
	L9B0_IRIS_085_T                 iris_085;                        // 0x4358
	L9B0_IRIS_086_T                 iris_086;                        // 0x435c
	L9B0_IRIS_087_T                 iris_087;                        // 0x4360
	L9B0_IRIS_088_T                 iris_088;                        // 0x4364
	L9B0_IRIS_089_T                 iris_089;                        // 0x4368
	L9B0_IRIS_090_T                 iris_090;                        // 0x436c
	L9B0_IRIS_091_T                 iris_091;                        // 0x4370
	L9B0_IRIS_092_T                 iris_092;                        // 0x4374
	L9B0_IRIS_093_T                 iris_093;                        // 0x4378
	L9B0_IRIS_094_T                 iris_094;                        // 0x437c
	L9B0_IRIS_095_T                 iris_095;                        // 0x4380
	L9B0_IRIS_096_T                 iris_096;                        // 0x4384
	L9B0_IRIS_097_T                 iris_097;                        // 0x4388
	L9B0_IRIS_098_T                 iris_098;                        // 0x438c
	L9B0_IRIS_099_T                 iris_099;                        // 0x4390
	L9B0_IRIS_100_T                 iris_100;                        // 0x4394
	L9B0_IRIS_101_T                 iris_101;                        // 0x4398
	L9B0_IRIS_102_T                 iris_102;                        // 0x439c
	L9B0_IRIS_103_T                 iris_103;                        // 0x43a0
	L9B0_IRIS_104_T                 iris_104;                        // 0x43a4
	L9B0_IRIS_105_T                 iris_105;                        // 0x43a8
	L9B0_IRIS_106_T                 iris_106;                        // 0x43ac
	L9B0_IRIS_107_T                 iris_107;                        // 0x43b0
	L9B0_IRIS_108_T                 iris_108;                        // 0x43b4
	L9B0_IRIS_109_T                 iris_109;                        // 0x43b8
	L9B0_IRIS_110_T                 iris_110;                        // 0x43bc
	L9B0_IRIS_111_T                 iris_111;                        // 0x43c0
	L9B0_IRIS_112_T                 iris_112;                        // 0x43c4
	L9B0_IRIS_113_T                 iris_113;                        // 0x43c8
	L9B0_IRIS_114_T                 iris_114;                        // 0x43cc
	L9B0_IRIS_115_T                 iris_115;                        // 0x43d0
	L9B0_IRIS_116_T                 iris_116;                        // 0x43d4
	L9B0_IRIS_117_T                 iris_117;                        // 0x43d8
	L9B0_IRIS_118_T                 iris_118;                        // 0x43dc
	L9B0_IRIS_119_T                 iris_119;                        // 0x43e0
	L9B0_IRIS_120_T                 iris_120;                        // 0x43e4
	L9B0_IRIS_121_T                 iris_121;                        // 0x43e8
	L9B0_IRIS_122_T                 iris_122;                        // 0x43ec
	L9B0_IRIS_123_T                 iris_123;                        // 0x43f0
	L9B0_IRIS_124_T                 iris_124;                        // 0x43f4
	L9B0_IRIS_125_T                 iris_125;                        // 0x43f8
	L9B0_IRIS_126_T                 iris_126;                        // 0x43fc
	L9B0_IRIS_127_T                 iris_127;                        // 0x4400
	L9B0_IRIS_128_T                 iris_128;                        // 0x4404
	L9B0_IRIS_129_T                 iris_129;                        // 0x4408
	L9B0_IRIS_130_T                 iris_130;                        // 0x440c
	L9B0_IRIS_131_T                 iris_131;                        // 0x4410
	L9B0_IRIS_132_T                 iris_132;                        // 0x4414
	L9B0_IRIS_133_T                 iris_133;                        // 0x4418
	L9B0_IRIS_134_T                 iris_134;                        // 0x441c
	L9B0_IRIS_135_T                 iris_135;                        // 0x4420
	L9B0_IRIS_136_T                 iris_136;                        // 0x4424
	L9B0_IRIS_137_T                 iris_137;                        // 0x4428
	L9B0_IRIS_138_T                 iris_138;                        // 0x442c
	L9B0_IRIS_139_T                 iris_139;                        // 0x4430
	L9B0_IRIS_140_T                 iris_140;                        // 0x4434
	L9B0_IRIS_141_T                 iris_141;                        // 0x4438
	L9B0_IRIS_142_T                 iris_142;                        // 0x443c
	L9B0_IRIS_143_T                 iris_143;                        // 0x4440
	L9B0_IRIS_144_T                 iris_144;                        // 0x4444
	L9B0_IRIS_145_T                 iris_145;                        // 0x4448
	L9B0_IRIS_146_T                 iris_146;                        // 0x444c
	L9B0_IRIS_147_T                 iris_147;                        // 0x4450
	L9B0_IRIS_148_T                 iris_148;                        // 0x4454
	L9B0_IRIS_149_T                 iris_149;                        // 0x4458
	L9B0_IRIS_150_T                 iris_150;                        // 0x445c
	L9B0_IRIS_151_T                 iris_151;                        // 0x4460
	L9B0_IRIS_152_T                 iris_152;                        // 0x4464
	L9B0_IRIS_153_T                 iris_153;                        // 0x4468
	L9B0_IRIS_154_T                 iris_154;                        // 0x446c
	L9B0_IRIS_155_T                 iris_155;                        // 0x4470
	L9B0_IRIS_156_T                 iris_156;                        // 0x4474
	L9B0_IRIS_157_T                 iris_157;                        // 0x4478
	L9B0_IRIS_158_T                 iris_158;                        // 0x447c
	L9B0_IRIS_159_T                 iris_159;                        // 0x4480
	L9B0_IRIS_160_T                 iris_160;                        // 0x4484
	L9B0_IRIS_161_T                 iris_161;                        // 0x4488
	L9B0_IRIS_162_T                 iris_162;                        // 0x448c
	L9B0_IRIS_163_T                 iris_163;                        // 0x4490
	L9B0_IRIS_164_T                 iris_164;                        // 0x4494
	L9B0_IRIS_165_T                 iris_165;                        // 0x4498
	L9B0_IRIS_166_T                 iris_166;                        // 0x449c
	L9B0_IRIS_167_T                 iris_167;                        // 0x44a0
	L9B0_IRIS_168_T                 iris_168;                        // 0x44a4
	L9B0_IRIS_169_T                 iris_169;                        // 0x44a8
	L9B0_IRIS_170_T                 iris_170;                        // 0x44ac
	L9B0_IRIS_171_T                 iris_171;                        // 0x44b0
	L9B0_IRIS_172_T                 iris_172;                        // 0x44b4
	L9B0_IRIS_173_T                 iris_173;                        // 0x44b8
	L9B0_IRIS_174_T                 iris_174;                        // 0x44bc
	L9B0_IRIS_175_T                 iris_175;                        // 0x44c0
	L9B0_IRIS_176_T                 iris_176;                        // 0x44c4
	L9B0_IRIS_177_T                 iris_177;                        // 0x44c8
	L9B0_IRIS_178_T                 iris_178;                        // 0x44cc
	L9B0_IRIS_179_T                 iris_179;                        // 0x44d0
	L9B0_IRIS_180_T                 iris_180;                        // 0x44d4
	L9B0_IRIS_181_T                 iris_181;                        // 0x44d8
	L9B0_IRIS_182_T                 iris_182;                        // 0x44dc
	L9B0_IRIS_183_T                 iris_183;                        // 0x44e0
	L9B0_IRIS_184_T                 iris_184;                        // 0x44e4
	L9B0_IRIS_185_T                 iris_185;                        // 0x44e8
	L9B0_IRIS_186_T                 iris_186;                        // 0x44ec
	L9B0_IRIS_187_T                 iris_187;                        // 0x44f0
	L9B0_IRIS_188_T                 iris_188;                        // 0x44f4
	L9B0_IRIS_189_T                 iris_189;                        // 0x44f8
	L9B0_IRIS_190_T                 iris_190;                        // 0x44fc
	L9B0_IRIS_191_T                 iris_191;                        // 0x4500
	L9B0_IRIS_192_T                 iris_192;                        // 0x4504
	L9B0_IRIS_193_T                 iris_193;                        // 0x4508
	L9B0_IRIS_194_T                 iris_194;                        // 0x450c
	L9B0_IRIS_195_T                 iris_195;                        // 0x4510
	L9B0_IRIS_196_T                 iris_196;                        // 0x4514
	L9B0_IRIS_197_T                 iris_197;                        // 0x4518
	L9B0_IRIS_198_T                 iris_198;                        // 0x451c
	L9B0_IRIS_199_T                 iris_199;                        // 0x4520
	L9B0_IRIS_200_T                 iris_200;                        // 0x4524
	L9B0_IRIS_201_T                 iris_201;                        // 0x4528
	L9B0_IRIS_202_T                 iris_202;                        // 0x452c
	L9B0_IRIS_203_T                 iris_203;                        // 0x4530
	L9B0_IRIS_204_T                 iris_204;                        // 0x4534
	L9B0_IRIS_205_T                 iris_205;                        // 0x4538
	L9B0_IRIS_206_T                 iris_206;                        // 0x453c
	L9B0_IRIS_207_T                 iris_207;                        // 0x4540
	L9B0_IRIS_208_T                 iris_208;                        // 0x4544
	L9B0_IRIS_209_T                 iris_209;                        // 0x4548
	L9B0_IRIS_210_T                 iris_210;                        // 0x454c
	L9B0_IRIS_211_T                 iris_211;                        // 0x4550
	L9B0_IRIS_212_T                 iris_212;                        // 0x4554
	L9B0_IRIS_213_T                 iris_213;                        // 0x4558
	L9B0_IRIS_214_T                 iris_214;                        // 0x455c
	L9B0_IRIS_215_T                 iris_215;                        // 0x4560
	L9B0_IRIS_216_T                 iris_216;                        // 0x4564
	L9B0_IRIS_217_T                 iris_217;                        // 0x4568
	L9B0_IRIS_218_T                 iris_218;                        // 0x456c
	L9B0_IRIS_219_T                 iris_219;                        // 0x4570
	L9B0_IRIS_220_T                 iris_220;                        // 0x4574
	L9B0_IRIS_221_T                 iris_221;                        // 0x4578
	L9B0_IRIS_222_T                 iris_222;                        // 0x457c
	L9B0_IRIS_223_T                 iris_223;                        // 0x4580
	L9B0_IRIS_224_T                 iris_224;                        // 0x4584
	L9B0_IRIS_225_T                 iris_225;                        // 0x4588
	L9B0_IRIS_226_T                 iris_226;                        // 0x458c
	L9B0_IRIS_227_T                 iris_227;                        // 0x4590
	L9B0_IRIS_228_T                 iris_228;                        // 0x4594
	L9B0_IRIS_229_T                 iris_229;                        // 0x4598
	L9B0_IRIS_230_T                 iris_230;                        // 0x459c
	L9B0_IRIS_231_T                 iris_231;                        // 0x45a0
	L9B0_IRIS_232_T                 iris_232;                        // 0x45a4
	L9B0_IRIS_233_T                 iris_233;                        // 0x45a8
	L9B0_IRIS_234_T                 iris_234;                        // 0x45ac
	L9B0_IRIS_235_T                 iris_235;                        // 0x45b0
	L9B0_IRIS_236_T                 iris_236;                        // 0x45b4
	L9B0_IRIS_237_T                 iris_237;                        // 0x45b8
	L9B0_IRIS_238_T                 iris_238;                        // 0x45bc
	L9B0_IRIS_239_T                 iris_239;                        // 0x45c0
	L9B0_IRIS_240_T                 iris_240;                        // 0x45c4
	L9B0_IRIS_241_T                 iris_241;                        // 0x45c8
	L9B0_IRIS_242_T                 iris_242;                        // 0x45cc
	L9B0_IRIS_243_T                 iris_243;                        // 0x45d0
	L9B0_IRIS_244_T                 iris_244;                        // 0x45d4
	L9B0_IRIS_245_T                 iris_245;                        // 0x45d8
	L9B0_IRIS_246_T                 iris_246;                        // 0x45dc
	L9B0_IRIS_247_T                 iris_247;                        // 0x45e0
	L9B0_IRIS_248_T                 iris_248;                        // 0x45e4
	L9B0_IRIS_249_T                 iris_249;                        // 0x45e8
	L9B0_IRIS_250_T                 iris_250;                        // 0x45ec
	L9B0_IRIS_251_T                 iris_251;                        // 0x45f0
	L9B0_IRIS_252_T                 iris_252;                        // 0x45f4
	L9B0_IRIS_253_T                 iris_253;                        // 0x45f8
	L9B0_IRIS_254_T                 iris_254;                        // 0x45fc
	L9B0_IRIS_255_T                 iris_255;                        // 0x4600
	L9B0_IRIS_256_T                 iris_256;                        // 0x4604
	L9B0_IRIS_257_T                 iris_257;                        // 0x4608
	L9B0_IRIS_258_T                 iris_258;                        // 0x460c
	L9B0_IRIS_259_T                 iris_259;                        // 0x4610
	L9B0_IRIS_260_T                 iris_260;                        // 0x4614
	L9B0_IRIS_261_T                 iris_261;                        // 0x4618
	L9B0_IRIS_262_T                 iris_262;                        // 0x461c
	L9B0_IRIS_263_T                 iris_263;                        // 0x4620
	L9B0_IRIS_264_T                 iris_264;                        // 0x4624
	UINT32                          reserved5[2];                    // 0x4628~0x462c
	L9B0_IRIS_265_T                 iris_265;                        // 0x4630
	L9B0_IRIS_266_T                 iris_266;                        // 0x4634
	L9B0_IRIS_267_T                 iris_267;                        // 0x4638
	L9B0_IRIS_268_T                 iris_268;                        // 0x463c
	L9B0_IRIS_269_T                 iris_269;                        // 0x4640
	L9B0_IRIS_270_T                 iris_270;                        // 0x4644
	L9B0_IRIS_271_T                 iris_271;                        // 0x4648
	L9B0_IRIS_272_T                 iris_272;                        // 0x464c
	L9B0_IRIS_273_T                 iris_273;                        // 0x4650
	L9B0_IRIS_274_T                 iris_274;                        // 0x4654
	L9B0_IRIS_275_T                 iris_275;                        // 0x4658
	L9B0_IRIS_276_T                 iris_276;                        // 0x465c
	L9B0_IRIS_277_T                 iris_277;                        // 0x4660
	L9B0_IRIS_278_T                 iris_278;                        // 0x4664
	L9B0_IRIS_279_T                 iris_279;                        // 0x4668
	L9B0_IRIS_280_T                 iris_280;                        // 0x466c
	L9B0_IRIS_281_T                 iris_281;                        // 0x4670
	L9B0_IRIS_282_T                 iris_282;                        // 0x4674
	L9B0_IRIS_283_T                 iris_283;                        // 0x4678
	L9B0_IRIS_284_T                 iris_284;                        // 0x467c
	L9B0_IRIS_285_T                 iris_285;                        // 0x4680
	L9B0_IRIS_286_T                 iris_286;                        // 0x4684
	L9B0_IRIS_287_T                 iris_287;                        // 0x4688
	L9B0_IRIS_288_T                 iris_288;                        // 0x468c
	L9B0_IRIS_289_T                 iris_289;                        // 0x4690
	L9B0_IRIS_290_T                 iris_290;                        // 0x4694
	L9B0_IRIS_291_T                 iris_291;                        // 0x4698
	L9B0_IRIS_292_T                 iris_292;                        // 0x469c
	L9B0_IRIS_293_T                 iris_293;                        // 0x46a0
	L9B0_IRIS_294_T                 iris_294;                        // 0x46a4
	L9B0_IRIS_295_T                 iris_295;                        // 0x46a8
	L9B0_IRIS_296_T                 iris_296;                        // 0x46ac
	L9B0_IRIS_297_T                 iris_297;                        // 0x46b0
	L9B0_IRIS_298_T                 iris_298;                        // 0x46b4
	L9B0_IRIS_299_T                 iris_299;                        // 0x46b8
	L9B0_IRIS_300_T                 iris_300;                        // 0x46bc
	L9B0_IRIS_301_T                 iris_301;                        // 0x46c0
	L9B0_IRIS_302_T                 iris_302;                        // 0x46c4
	L9B0_IRIS_303_T                 iris_303;                        // 0x46c8
	L9B0_IRIS_304_T                 iris_304;                        // 0x46cc
	UINT32                          reserved6[76];                   // 0x46d0~0x47fc
	L9B0_VBI_001_T                  vbi_001;                         // 0x4800
	L9B0_VBI_002_T                  vbi_002;                         // 0x4804
	L9B0_VBI_003_T                  vbi_003;                         // 0x4808
	L9B0_VBI_004_T                  vbi_004;                         // 0x480c
	L9B0_VBI_005_T                  vbi_005;                         // 0x4810
	L9B0_VBI_006_T                  vbi_006;                         // 0x4814
	L9B0_VBI_007_T                  vbi_007;                         // 0x4818
	L9B0_VBI_008_T                  vbi_008;                         // 0x481c
	L9B0_VBI_009_T                  vbi_009;                         // 0x4820
	L9B0_VBI_010_T                  vbi_010;                         // 0x4824
	L9B0_VBI_011_T                  vbi_011;                         // 0x4828
	L9B0_VBI_012_T                  vbi_012;                         // 0x482c
	L9B0_VBI_013_T                  vbi_013;                         // 0x4830
	L9B0_VBI_014_T                  vbi_014;                         // 0x4834
	L9B0_VBI_015_T                  vbi_015;                         // 0x4838
	L9B0_VBI_016_T                  vbi_016;                         // 0x483c
	L9B0_VBI_017_T                  vbi_017;                         // 0x4840
	L9B0_VBI_018_T                  vbi_018;                         // 0x4844
	L9B0_VBI_019_T                  vbi_019;                         // 0x4848
	L9B0_VBI_020_T                  vbi_020;                         // 0x484c
	L9B0_VBI_021_T                  vbi_021;                         // 0x4850
	L9B0_VBI_022_T                  vbi_022;                         // 0x4854
	L9B0_VBI_023_T                  vbi_023;                         // 0x4858
	L9B0_VBI_024_T                  vbi_024;                         // 0x485c
	UINT32                          reserved7[18];                   // 0x4860~0x48a4
	L9B0_IRIS_MIF_GMUA_MON_001_T    iris_mif_gmua_mon_001;           // 0x48a8
	L9B0_IRIS_MIF_GMUA_MON_002_T    iris_mif_gmua_mon_002;           // 0x48ac
	L9B0_IRIS_MIF_GMUA_MON_003_T    iris_mif_gmua_mon_003;           // 0x48b0
	L9B0_IRIS_MIF_GMUA_MON_004_T    iris_mif_gmua_mon_004;           // 0x48b4
	L9B0_IRIS_MIF_GMUA_MON_005_T    iris_mif_gmua_mon_005;           // 0x48b8
	L9B0_IRIS_MIF_GMUA_MON_006_T    iris_mif_gmua_mon_006;           // 0x48bc
	L9B0_IRIS_MIF_GMUA_MON_007_T    iris_mif_gmua_mon_007;           // 0x48c0
	L9B0_IRIS_MIF_GMUA_MON_008_T    iris_mif_gmua_mon_008;           // 0x48c4
	L9B0_IRIS_MIF_GMUA_MON_009_T    iris_mif_gmua_mon_009;           // 0x48c8
	L9B0_IRIS_MIF_GMUA_MON_010_T    iris_mif_gmua_mon_010;           // 0x48cc
	L9B0_IRIS_MIF_GMUA_MON_011_T    iris_mif_gmua_mon_011;           // 0x48d0
	L9B0_IRIS_MIF_GMUA_MON_012_T    iris_mif_gmua_mon_012;           // 0x48d4
	L9B0_IRIS_MIF_GMUA_MON_013_T    iris_mif_gmua_mon_013;           // 0x48d8
	L9B0_IRIS_MIF_GMUA_MON_014_T    iris_mif_gmua_mon_014;           // 0x48dc
	L9B0_IRIS_MIF_GMUA_MON_015_T    iris_mif_gmua_mon_015;           // 0x48e0
	L9B0_IRIS_MIF_GMUA_MON_016_T    iris_mif_gmua_mon_016;           // 0x48e4
	L9B0_IRIS_MIF_GMUA_MON_017_T    iris_mif_gmua_mon_017;           // 0x48e8
	L9B0_IRIS_MIF_GMUA_MON_018_T    iris_mif_gmua_mon_018;           // 0x48ec
	L9B0_IRIS_MIF_GMUA_MON_019_T    iris_mif_gmua_mon_019;           // 0x48f0
	L9B0_IRIS_MIF_GMUA_MON_020_T    iris_mif_gmua_mon_020;           // 0x48f4
	L9B0_IRIS_MIF_GMUA_MON_021_T    iris_mif_gmua_mon_021;           // 0x48f8
	L9B0_IRIS_MIF_GMUA_MON_022_T    iris_mif_gmua_mon_022;           // 0x48fc
	L9B0_IRIS_HIF_CTRL0_001_T       iris_hif_ctrl0_001;              // 0x4900
	L9B0_IRIS_HIF_CTRL1_001_T       iris_hif_ctrl1_001;              // 0x4904
} DE_CVD_REG_L9B0_T;

#endif
