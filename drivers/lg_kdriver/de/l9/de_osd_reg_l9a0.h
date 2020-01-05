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

#ifndef _REG_OSD_L9A0_h
#define _REG_OSD_L9A0_h

typedef struct { // 0x3a00
	UINT32 osd0_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 osd0_manual_address             : 1;   //     3
	UINT32 osd0_round                      : 3;   //  6: 4
	UINT32 osd0_pure_ck                    : 1;   //     7
	UINT32 osd0_hdr_ptr_bmp_sel            : 1;   //     8
	UINT32 osd0_hdr_ptr_plte_sel           : 1;   //     9
	UINT32 osd0_hdr_color_key_sel          : 1;   //    10
	UINT32 osd0_hdr_wpl_sel                : 1;   //    11
	UINT32 osd0_hdr_global_alpha_sel       : 1;   //    12
	UINT32 osd0_hdr_format_sel             : 1;   //    13
	UINT32 osd0_hdr_depth_sel              : 1;   //    14
	UINT32 osd0_hdr_h_out_sel              : 1;   //    15
	UINT32 osd0_hdr_w_out_sel              : 1;   //    16
	UINT32 osd0_hdr_global_alpha_en_sel    : 1;   //    17
	UINT32 osd0_hdr_pixel_order_sel        : 1;   //    18
	UINT32 osd0_hdr_h_mem_sel              : 1;   //    19
	UINT32 osd0_hdr_w_mem_sel              : 1;   //    20
	UINT32 osd0_hdr_ypos_sel               : 1;   //    21
	UINT32 osd0_hdr_xpos_sel               : 1;   //    22
	UINT32 osd0_hdr_color_key_en_sel       : 1;   //    23
	UINT32 osd0_ch_blue                    : 2;   // 25:24
	UINT32 osd0_ch_green                   : 2;   // 27:26
	UINT32 osd0_ch_red                     : 2;   // 29:28
	UINT32 osd0_ch_alpha                   : 2;   // 31:30
} L9A0_OSD0_CFG_T;

typedef struct { // 0x3a04
	UINT32 osd1_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 osd0_manual_address             : 1;   //     3
	UINT32 osd1_round                      : 3;   //  6: 4
	UINT32 osd1_pure_ck                    : 1;   //     7
	UINT32 osd1_hdr_ptr_bmp_sel            : 1;   //     8
	UINT32 osd1_hdr_ptr_plte_sel           : 1;   //     9
	UINT32 osd1_hdr_color_key_sel          : 1;   //    10
	UINT32 osd1_hdr_wpl_sel                : 1;   //    11
	UINT32 osd1_hdr_global_alpha_sel       : 1;   //    12
	UINT32 osd1_hdr_format_sel             : 1;   //    13
	UINT32 osd1_hdr_depth_sel              : 1;   //    14
	UINT32 osd1_hdr_h_out_sel              : 1;   //    15
	UINT32 osd1_hdr_w_out_sel              : 1;   //    16
	UINT32 osd1_hdr_global_alpha_en_sel    : 1;   //    17
	UINT32 osd1_hdr_pixel_order_sel        : 1;   //    18
	UINT32 osd1_hdr_h_mem_sel              : 1;   //    19
	UINT32 osd1_hdr_w_mem_sel              : 1;   //    20
	UINT32 osd1_hdr_ypos_sel               : 1;   //    21
	UINT32 osd1_hdr_xpos_sel               : 1;   //    22
	UINT32 osd1_hdr_color_key_en_sel       : 1;   //    23
	UINT32 osd1_ch_blue                    : 2;   // 25:24
	UINT32 osd1_ch_green                   : 2;   // 27:26
	UINT32 osd1_ch_red                     : 2;   // 29:28
	UINT32 osd1_ch_alpha                   : 2;   // 31:30
} L9A0_OSD1_CFG_T;

typedef struct { // 0x3a08
	UINT32 osd2_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 osd0_manual_address             : 1;   //     3
	UINT32 osd2_round                      : 3;   //  6: 4
	UINT32 osd2_pure_ck                    : 1;   //     7
	UINT32 osd2_hdr_ptr_bmp_sel            : 1;   //     8
	UINT32 osd2_hdr_ptr_plte_sel           : 1;   //     9
	UINT32 osd2_hdr_color_key_sel          : 1;   //    10
	UINT32 osd2_hdr_wpl_sel                : 1;   //    11
	UINT32 osd2_hdr_global_alpha_sel       : 1;   //    12
	UINT32 osd2_hdr_format_sel             : 1;   //    13
	UINT32 osd2_hdr_depth_sel              : 1;   //    14
	UINT32 osd2_hdr_h_out_sel              : 1;   //    15
	UINT32 osd2_hdr_w_out_sel              : 1;   //    16
	UINT32 osd2_hdr_global_alpha_en_sel    : 1;   //    17
	UINT32 osd2_hdr_pixel_order_sel        : 1;   //    18
	UINT32 osd2_hdr_h_mem_sel              : 1;   //    19
	UINT32 osd2_hdr_w_mem_sel              : 1;   //    20
	UINT32 osd2_hdr_ypos_sel               : 1;   //    21
	UINT32 osd2_hdr_xpos_sel               : 1;   //    22
	UINT32 osd2_hdr_color_key_en_sel       : 1;   //    23
	UINT32 osd2_ch_blue                    : 2;   // 25:24
	UINT32 osd2_ch_green                   : 2;   // 27:26
	UINT32 osd2_ch_red                     : 2;   // 29:28
	UINT32 osd2_ch_alpha                   : 2;   // 31:30
} L9A0_OSD2_CFG_T;

typedef struct { // 0x3a0c
	UINT32 version_date                    : 32;  // 31: 0
} L9A0_OSD_VERSION_DATE_T;

typedef struct { // 0x3a10
	UINT32 disp_h                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 disp_w                          : 12;  // 27:16
} L9A0_OSD_DISP_SIZE_T;

typedef struct { // 0x3a14
	UINT32 crsr_irq                        : 1;   //     0
	UINT32 osd2_irq                        : 1;   //     1
	UINT32 osd1_irq                        : 1;   //     2
	UINT32 osd0_irq                        : 1;   //     3
	UINT32 mixer_irq                       : 1;   //     4
	UINT32                                 : 11;  // 15: 5
	UINT32 crsr_irq_en                     : 1;   //    16
	UINT32 osd2_irq_en                     : 1;   //    17
	UINT32 osd1_irq_en                     : 1;   //    18
	UINT32 osd0_irq_en                     : 1;   //    19
	UINT32 mixer_irq_en                    : 1;   //    20
} L9A0_OSD_IRQ_T;

typedef struct { // 0x3a18
	UINT32 osd0_base_addr                  : 32;  // 31: 0
} L9A0_OSD0_BASE_ADDR_T;

typedef struct { // 0x3a1c
	UINT32 osd0_hdr_color_key_en           : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd0_hdr_xpos                   : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 osd0_hdr_ypos                   : 1;   //    31
} L9A0_OSD0_HDR0_T;

typedef struct { // 0x3a20
	UINT32 osd0_hdr_h_mem                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd0_hdr_w_mem                  : 11;  // 26:16
} L9A0_OSD0_HDR1_T;

typedef struct { // 0x3a24
	UINT32 osd0_hdr_h_out                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd0_hdr_w_out                  : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 osd0_hdr_pixel_order            : 1;   //    31
} L9A0_OSD0_HDR2_T;

typedef struct { // 0x3a28
	UINT32 osd0_hdr_wpl                    : 16;  // 15: 0
	UINT32 osd0_hdr_global_alpha           : 8;   // 23:16
	UINT32 osd0_hdr_format                 : 4;   // 27:24
	UINT32 osd0_hdr_depth                  : 3;   // 30:28
	UINT32 osd0_hdr_global_alpha_en        : 1;   //    31
} L9A0_OSD0_HDR3_T;

typedef struct { // 0x3a2c
	UINT32 osd0_hdr_color_key              : 32;  // 31: 0
} L9A0_OSD0_HDR4_T;

typedef struct { // 0x3a30
	UINT32 osd0_hdr_ptr_plte               : 32;  // 31: 0
} L9A0_OSD0_HDR5_T;

typedef struct { // 0x3a34
	UINT32 osd0_hdr_ptr_bmp                : 32;  // 31: 0
} L9A0_OSD0_HDR6_T;

typedef struct { // 0x3a38
	UINT32 osd0_lfsr_seed                  : 19;  // 18: 0
} L9A0_OSD0_LFSR_SEED_T;

typedef struct { // 0x3a3c
	UINT32 osd1_base_addr_f                : 32;   // 31: 0
} L9A0_OSD1_BASE_ADDR_T;

typedef struct { // 0x3a40
	UINT32 osd1_hdr_color_key_en           : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd1_hdr_xpos                   : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 osd1_hdr_ypos                   : 1;   //    31
} L9A0_OSD1_HDR0_T;

typedef struct { // 0x3a44
	UINT32 osd1_hdr_h_mem                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd1_hdr_w_mem                  : 11;  // 26:16
} L9A0_OSD1_HDR1_T;

typedef struct { // 0x3a48
	UINT32 osd1_hdr_h_out                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd1_hdr_w_out                  : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 osd1_hdr_pixel_order            : 1;   //    31
} L9A0_OSD1_HDR2_T;

typedef struct { // 0x3a4c
	UINT32 osd1_hdr_wpl                    : 16;  // 15: 0
	UINT32 osd1_hdr_global_alpha           : 8;   // 23:16
	UINT32 osd1_hdr_format                 : 4;   // 27:24
	UINT32 osd1_hdr_depth                  : 3;   // 30:28
	UINT32 osd1_hdr_global_alpha_en        : 1;   //    31
} L9A0_OSD1_HDR3_T;

typedef struct { // 0x3a50
	UINT32 osd1_hdr_color_key              : 32;  // 31: 0
} L9A0_OSD1_HDR4_T;

typedef struct { // 0x3a54
	UINT32 osd1_hdr_ptr_plte               : 32;  // 31: 0
} L9A0_OSD1_HDR5_T;

typedef struct { // 0x3a58
	UINT32 osd1_hdr_ptr_bmp                : 32;  // 31: 0
} L9A0_OSD1_HDR6_T;

typedef struct { // 0x3a5c
	UINT32 osd1_lfsr_seed                  : 19;  // 18: 0
} L9A0_OSD1_LFSR_SEED_T;

typedef struct { // 0x3a60
	UINT32 osd1_base_addr                  : 32;  // 31: 0
} L9A0_OSD2_BASE_ADDR_T;

typedef struct { // 0x3a64
	UINT32 osd2_hdr_color_key_en           : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd2_hdr_xpos                   : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 osd2_hdr_ypos                   : 1;   //    31
} L9A0_OSD2_HDR0_T;

typedef struct { // 0x3a68
	UINT32 osd2_hdr_h_mem                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd2_hdr_w_mem                  : 11;  // 26:16
} L9A0_OSD2_HDR1_T;

typedef struct { // 0x3a6c
	UINT32 osd2_hdr_h_out                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd2_hdr_w_out                  : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 osd2_hdr_pixel_order            : 1;   //    31
} L9A0_OSD2_HDR2_T;

typedef struct { // 0x3a70
	UINT32 osd2_hdr_wpl                    : 16;  // 15: 0
	UINT32 osd2_hdr_global_alpha           : 8;   // 23:16
	UINT32 osd2_hdr_format                 : 4;   // 27:24
	UINT32 osd2_hdr_depth                  : 3;   // 30:28
	UINT32 osd2_hdr_global_alpha_en        : 1;   //    31
} L9A0_OSD2_HDR3_T;

typedef struct { // 0x3a74
	UINT32 osd2_hdr_color_key              : 32;  // 31: 0
} L9A0_OSD2_HDR4_T;

typedef struct { // 0x3a78
	UINT32 osd2_hdr_ptr_plte               : 32;  // 31: 0
} L9A0_OSD2_HDR5_T;

typedef struct { // 0x3a7c
	UINT32 osd2_hdr_ptr_bmp                : 32;  // 31: 0
} L9A0_OSD2_HDR6_T;

typedef struct { // 0x3a80
	UINT32 osd2_lfsr_seed                  : 19;  // 18: 0
} L9A0_OSD2_LFSR_SEED_T;

typedef struct { // 0x3a84
	UINT32 osd0_sc_vs_en                   : 1;   //     0
	UINT32 osd0_sc_hs_en                   : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 osd0_sc_bc_sa                   : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 osd0_sc_bnd_mode                : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 osd0_sc_h2v_path                : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 osd0_sc_h_phase_off             : 12;  // 27:16
	UINT32                                 : 3;   // 30:28
	UINT32 osd0_sc_buf_mode_en             : 1;   //    31
} L9A0_OSD0_SC_CFG_T;

typedef struct { // 0x3a88
	UINT32 osd1_sc_vs_en                   : 1;   //     0
	UINT32 osd1_sc_hs_en                   : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 osd1_sc_bc_sa                   : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 osd1_sc_bnd_mode                : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 osd1_sc_h2v_path                : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 osd1_sc_h_phase_off             : 12;  // 27:16
	UINT32                                 : 3;   // 30:28
	UINT32 osd1_sc_buf_mode_en             : 1;   //    31
} L9A0_OSD1_SC_CFG_T;

typedef struct { // 0x3a8c
	UINT32 osd2_sc_vs_en                   : 1;   //     0
	UINT32 osd2_sc_hs_en                   : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 osd2_sc_bc_sa                   : 3;   //  6: 4
	UINT32                                 : 1;   //     7
	UINT32 osd2_sc_bnd_mode                : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 osd2_sc_h2v_path                : 1;   //    12
	UINT32                                 : 3;   // 15:13
	UINT32 osd2_sc_h_phase_off             : 12;  // 27:16
	UINT32                                 : 3;   // 30:28
	UINT32 osd2_sc_buf_mode_en             : 1;   //    31
} L9A0_OSD2_SC_CFG_T;

typedef struct { // 0x3a90
	UINT32 osd_sc_v_phase_off              : 13;  // 12: 0
	UINT32                                 : 3;   // 15:13
	UINT32 osd_sc_v_phase_off_index        : 2;   // 17:16
	UINT32                                 : 13;  // 30:18
	UINT32 osd_sc_v_phase_off_rw           : 1;   //    31
} L9A0_OSD_SC_V_PHASE_OFF_T;

typedef struct { // 0x3a94
	UINT32 osd0_csc_data                   : 11;  // 10: 0
	UINT32 osd0_csc_rw_n                   : 1;   //    11
	UINT32                                 : 4;   // 15:12
	UINT32 osd0_csc_bypass                 : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 osd0_csc_sel                    : 1;   //    20
	UINT32                                 : 3;   // 23:21
	UINT32 osd0_csc_out_ctrl               : 3;   // 26:24
	UINT32                                 : 1;   //    27
	UINT32 osd0_csc_in_ctrl                : 3;   // 30:28
} L9A0_OSD0_CSC_CTRL_T;

typedef struct { // 0x3a98
	UINT32 osd1_csc_data                   : 11;  // 10: 0
	UINT32 osd1_csc_rw_n                   : 1;   //    11
	UINT32                                 : 4;   // 15:12
	UINT32 osd1_csc_bypass                 : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 osd1_csc_sel                    : 1;   //    20
	UINT32                                 : 3;   // 23:21
	UINT32 osd1_csc_out_ctrl               : 3;   // 26:24
	UINT32                                 : 1;   //    27
	UINT32 osd1_csc_in_ctrl                : 3;   // 30:28
} L9A0_OSD1_CSC_CTRL_T;

typedef struct { // 0x3a9c
	UINT32 osd2_csc_data                   : 11;  // 10: 0
	UINT32 osd2_csc_rw_n                   : 1;   //    11
	UINT32                                 : 4;   // 15:12
	UINT32 osd2_csc_bypass                 : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 osd2_csc_sel                    : 1;   //    20
	UINT32                                 : 3;   // 23:21
	UINT32 osd2_csc_out_ctrl               : 3;   // 26:24
	UINT32                                 : 1;   //    27
	UINT32 osd2_csc_in_ctrl                : 3;   // 30:28
} L9A0_OSD2_CSC_CTRL_T;

typedef struct { // 0x3aa4
	UINT32 osd0_bbs                        : 1;   //     0
	UINT32 osd0_bqws                       : 1;   //     1
	UINT32 osd0_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3
	UINT32 osd0_pbs                        : 1;   //     4
	UINT32 osd0_pqws                       : 1;   //     5
	UINT32 osd0_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7
	UINT32 osd0_hbs                        : 1;   //     8
	UINT32 osd0_hqws                       : 1;   //     9
	UINT32 osd0_hhws                       : 1;   //    10
} L9A0_OSD0_END_CONV_T;

typedef struct { // 0x3aa8
	UINT32 osd1_bbs                        : 1;   //     0
	UINT32 osd1_bqws                       : 1;   //     1
	UINT32 osd1_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3
	UINT32 osd1_pbs                        : 1;   //     4
	UINT32 osd1_pqws                       : 1;   //     5
	UINT32 osd1_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7
	UINT32 osd1_hbs                        : 1;   //     8
	UINT32 osd1_hqws                       : 1;   //     9
	UINT32 osd1_hhws                       : 1;   //    10
} L9A0_OSD1_END_CONV_T;

typedef struct { // 0x3aac
	UINT32 osd2_bbs                        : 1;   //     0
	UINT32 osd2_bqws                       : 1;   //     1
	UINT32 osd2_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3
	UINT32 osd2_pbs                        : 1;   //     4
	UINT32 osd2_pqws                       : 1;   //     5
	UINT32 osd2_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7
	UINT32 osd2_hbs                        : 1;   //     8
	UINT32 osd2_hqws                       : 1;   //     9
	UINT32 osd2_hhws                       : 1;   //    10
} L9A0_OSD2_END_CONV_T;

typedef struct { // 0x3ab4
	UINT32 crsr_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 crsr_manual_address             : 1;   //     3
	UINT32 crsr_round                      : 3;   //  6: 4
	UINT32 crsr_pure_color_key             : 1;   //     7
	UINT32 crsr_hdr_ptr_bmp_sel            : 1;   //     8
	UINT32 crsr_hdr_ptr_plte_sel           : 1;   //     9
	UINT32 crsr_hdr_color_key_sel          : 1;   //    10
	UINT32 crsr_hdr_wpl_sel                : 1;   //    11
	UINT32 crsr_hdr_global_alpha_sel       : 1;   //    12
	UINT32 crsr_hdr_format_sel             : 1;   //    13
	UINT32 crsr_hdr_depth_sel              : 1;   //    14
	UINT32                                 : 2;   // 16:15
	UINT32 crsr_hdr_global_alpha_en_sel    : 1;   //    17
	UINT32 crsr_hdr_pixel_order_sel        : 1;   //    18
	UINT32 crsr_hdr_h_mem_sel              : 1;   //    19
	UINT32 crsr_hdr_w_mem_sel              : 1;   //    20
	UINT32 crsr_hdr_ypos_sel               : 1;   //    21
	UINT32 crsr_hdr_xpos_sel               : 1;   //    22
	UINT32 crsr_hdr_color_key_en_sel       : 1;   //    23
	UINT32 crsr_ch_blue                    : 2;   // 25:24
	UINT32 crsr_ch_green                   : 2;   // 27:26
	UINT32 crsr_ch_red                     : 2;   // 29:28
	UINT32 crsr_ch_alpha                   : 2;   // 31:30
} L9A0_CRSR_CFG_T;

typedef struct { // 0x3ab8
	UINT32 crsr_base_addr                  : 32;  // 31: 0
} L9A0_CRSR_BASE_ADDR_T;

typedef struct { // 0x3abc
	UINT32 crsr_hdr_ypos                   : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 crsr_hdr_xpos                   : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 crsr_hdr_pos_load               : 1;   //    31
} L9A0_CRSR_HDR0_T;

typedef struct { // 0x3ac0
	UINT32 crsr_hdr_h_mem                  : 12;  // 11: 0
	UINT32                                 : 3;   // 14:12
	UINT32 crsr_hdr_pixel_order            : 1;   //    15
	UINT32 crsr_hdr_w_mem                  : 11;  // 26:16
	UINT32                                 : 4;   // 30:27
	UINT32 crsr_hdr_color_key_en           : 1;   //    31
} L9A0_CRSR_HDR1_T;

typedef struct { // 0x3ac4
	UINT32 crsr_hdr_wpl                    : 16;  // 15: 0
	UINT32 crsr_hdr_global_alpha           : 8;   // 23:16
	UINT32 crsr_hdr_format                 : 4;   // 27:24
	UINT32 crsr_hdr_depth                  : 3;   // 30:28
	UINT32 crsr_hdr_global_alpha_en        : 1;   //    31
} L9A0_CRSR_HDR2_T;

typedef struct { // 0x3ac8
	UINT32 crsr_hdr_color_key              : 32;  // 31: 0
} L9A0_CRSR_HDR3_T;

typedef struct { // 0x3acc
	UINT32 crsr_hdr_ptr_plte               : 32;  // 31: 0
} L9A0_CRSR_HDR4_T;

typedef struct { // 0x3ad0
	UINT32 crsr_hdr_ptr_bmp                : 32;  // 31: 0
} L9A0_CRSR_HDR5_T;

typedef struct { // 0x3ad4
	UINT32 crsr_bbs                        : 1;   //     0
	UINT32 crsr_bqws                       : 1;   //     1
	UINT32 crsr_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3
	UINT32 crsr_pbs                        : 1;   //     4
	UINT32 crsr_pqws                       : 1;   //     5
	UINT32 crsr_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7
	UINT32 crsr_hbs                        : 1;   //     8
	UINT32 crsr_hqws                       : 1;   //     9
	UINT32 crsr_hhws                       : 1;   //    10
} L9A0_CRSR_END_CONV_T;

typedef struct { // 0x3ad8
	UINT32 crsr_lfsr_seed                  : 19;  // 18: 0
} L9A0_CRSR_LFSR_SEED_T;

typedef struct { // 0x3af0
	UINT32 layer_mux_3                     : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 layer_mux_2                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 layer_mux_1                     : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 layer_mux_0                     : 2;   // 13:12
	UINT32                                 : 2;   // 15:14
	UINT32 video_layer_alpha               : 8;   // 23:16
} L9A0_OSD_LAYER_MUX_LEFT_T;

typedef struct { // 0x3af4
	UINT32 layer_mux_3                     : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 layer_mux_2                     : 2;   //  5: 4
	UINT32                                 : 2;   //  7: 6
	UINT32 layer_mux_1                     : 2;   //  9: 8
	UINT32                                 : 2;   // 11:10
	UINT32 layer_mux_0                     : 2;   // 13:12
	UINT32                                 : 2;   // 15:14
	UINT32 video_layer_alpha               : 8;   // 23:16
} L9A0_OSD_LAYER_MUX_RIGHT_T;

typedef struct { // 0x3af8
	UINT32 mixer_out_blue                  : 10;  //  9: 0
	UINT32 mixer_out_green                 : 10;  // 19:10
	UINT32 mixer_out_red                   : 10;  // 29:20
	UINT32 mixer_mask_en                   : 1;   //    30
	UINT32 mixer_out_en                    : 1;   //    31
} L9A0_OSD_MIXER_OUT_LEFT_T;

typedef struct { // 0x3afc
	UINT32 mixer_out_blue                  : 10;  //  9: 0
	UINT32 mixer_out_green                 : 10;  // 19:10
	UINT32 mixer_out_red                   : 10;  // 29:20
	UINT32 mixer_mask_en                   : 1;   //    30
	UINT32 mixer_out_en                    : 1;   //    31
} L9A0_OSD_MIXER_OUT_RIGHT_T;

typedef struct { // 0x3b00
	UINT32 osd0_path_sel                   : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 osd0_path_buf_half              : 1;   //     4
	UINT32 osd0_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  // 15: 6
	UINT32 osd0_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 osd0_3d_mode_sel                : 1;   //    20
} L9A0_OSD0_3D_PATH_MODE_T;

typedef struct { // 0x3b04
	UINT32 osd0_right_disparity            : 8;   //  7: 0
	UINT32 osd0_right_disparity_sign       : 1;   //     8
	UINT32                                 : 7;   // 15: 9
	UINT32 osd0_left_disparity             : 8;   // 23:16
	UINT32 osd0_left_disparity_sign        : 1;   //    24
} L9A0_OSD0_3D_DISPARITY_T;

typedef struct { // 0x3b08
	UINT32 osd0_left_3d_blank              : 32;  // 31: 0
} L9A0_OSD0_LEFT_3D_BLANK_T;

typedef struct { // 0x3b0c
	UINT32 osd0_right_3d_blank             : 32;  // 31: 0
} L9A0_OSD0_RIGHT_3D_BLANK_T;

typedef struct { // 0x3b10
	UINT32 osd0_tb_line_space              : 12;  // 11: 0
} L9A0_OSD0_TB_SPACE_T;

typedef struct { // 0x3b20
	UINT32 osd1_path_sel                   : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 osd1_path_buf_half              : 1;   //     4
	UINT32 osd1_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  // 15: 6
	UINT32 osd1_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 osd1_3d_mode_sel                : 1;   //    20
} L9A0_OSD1_3D_PATH_MODE_T;

typedef struct { // 0x3b24
	UINT32 osd1_right_disparity            : 8;   //  7: 0
	UINT32 osd1_right_disparity_sign       : 1;   //     8
	UINT32                                 : 7;   // 15: 9
	UINT32 osd1_left_disparity             : 8;   // 23:16
	UINT32 osd1_left_disparity_sign        : 1;   //    24
} L9A0_OSD1_3D_DISPARITY_T;

typedef struct { // 0x3b28
	UINT32 osd1_left_3d_blank              : 32;  // 31: 0
} L9A0_OSD1_LEFT_3D_BLANK_T;

typedef struct { // 0x3b2c
	UINT32 osd1_right_3d_blank             : 32;  // 31: 0
} L9A0_OSD1_RIGHT_3D_BLANK_T;

typedef struct { // 0x3b30
	UINT32 osd1_tb_line_space              : 12;  // 11: 0
} L9A0_OSD1_TB_SPACE_T;

typedef struct { // 0x3b40
	UINT32 osd2_path_sel                   : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 osd2_path_buf_half              : 1;   //     4
	UINT32 osd2_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  // 15: 6
	UINT32 osd2_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 osd2_3d_mode_sel                : 1;   //    20
} L9A0_OSD2_3D_PATH_MODE_T;

typedef struct { // 0x3b44
	UINT32 osd2_right_disparity            : 8;   //  7: 0
	UINT32 osd2_right_disparity_sign       : 1;   //     8
	UINT32                                 : 7;   // 15: 9
	UINT32 osd2_left_disparity             : 8;   // 23:16
	UINT32 osd2_left_disparity_sign        : 1;   //    24
} L9A0_OSD2_3D_DISPARITY_T;

typedef struct { // 0x3b48
	UINT32 osd2_left_3d_blank              : 32;  // 31: 0
} L9A0_OSD2_LEFT_3D_BLANK_T;

typedef struct { // 0x3b4c
	UINT32 osd2_right_3d_blank             : 32;  // 31: 0
} L9A0_OSD2_RIGHT_3D_BLANK_T;

typedef struct { // 0x3b50
	UINT32 osd2_tb_line_space              : 12;  // 11: 0
} L9A0_OSD2_TB_SPACE_T;

typedef struct { // 0x3b60
	UINT32 osd3_path_sel                   : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 osd3_path_buf_half              : 1;   //     4
	UINT32 osd3_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  // 15: 6
	UINT32 osd3_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 19:17
	UINT32 osd3_3d_mode_sel                : 1;   //    20
} L9A0_OSD3_3D_PATH_MODE_T;

typedef struct { // 0x3b64
	UINT32 osd3_right_disparity            : 8;   //  7: 0
	UINT32 osd3_right_disparity_sign       : 1;   //     8
	UINT32                                 : 7;   // 15: 9
	UINT32 osd3_left_disparity             : 8;   // 23:16
	UINT32 osd3_left_disparity_sign        : 1;   //    24
} L9A0_OSD3_3D_DISPARITY_T;

typedef struct { // 0x3b68
	UINT32 osd3_left_3d_blank              : 32;  // 31: 0
} L9A0_OSD3_LEFT_3D_BLANK_T;

typedef struct { // 0x3b6c
	UINT32 osd3_right_3d_blank             : 32;  // 31: 0
} L9A0_OSD3_RIGHT_3D_BLANK_T;

typedef struct { // 0x3b70
	UINT32 osd3_tb_line_space              : 12;  // 11: 0
} L9A0_OSD3_TB_SPACE_T;

typedef struct { // 0x3ba0
	UINT32                                 : 4;   //  3: 0
	UINT32 osd_frc_layer_sel               : 2;   //  5: 4
	UINT32 osd_frc_lr_sel                  : 1;   //     6
	UINT32                                 : 1;   //     7
	UINT32 osd_frc_dither_en               : 3;   // 10: 8
} L9A0_OSD_FRC_IF_CFG_T;

typedef struct { // 0x3ba4
	UINT32 osd_frc_hdr_format              : 4;   //  3: 0
	UINT32 osd_frc_hdr_po                  : 4;   //  7: 4
	UINT32                                 : 2;   //  9: 8
	UINT32 osd_frc_lr                      : 1;   //    10
	UINT32 osd_frc_3d                      : 1;   //    11
	UINT32                                 : 4;   // 15:12
	UINT32 osd_frc_hdr_code                : 8;   // 23:16
} L9A0_OSD_FRC_HDR_0_T;

typedef struct { // 0x3ba8
	UINT32 osd_frc_hdr_bmp_height          : 13;  // 12: 0
	UINT32                                 : 3;   // 15:13
	UINT32 osd_frc_hdr_bmp_width           : 13;  // 28:16
} L9A0_OSD_FRC_HDR_1_T;

typedef struct { // 0x3bac
	UINT32 osd_frc_hdr_global_alpha        : 8;   //  7: 0
	UINT32                                 : 4;   // 11: 8
	UINT32 osd_frc_hdr_pe                  : 1;   //    12
	UINT32 osd_frc_hdr_ge                  : 1;   //    13
	UINT32 osd_frc_hdr_ce                  : 1;   //    14
	UINT32 osd_frc_hdr_ou                  : 1;   //    15
} L9A0_OSD_FRC_HDR_2_T;

typedef struct { // 0x3bb0
	UINT32 osd_frc_hdr_ck_b                : 8;   //  7: 0
	UINT32 osd_frc_hdr_ck_g                : 8;   // 15: 8
	UINT32 osd_frc_hdr_ck_r                : 8;   // 23:16
} L9A0_OSD_FRC_HDR_3_T;

typedef struct { // 0x3bb4
	UINT32 osd_frc_hdr_yoffset             : 13;  // 12: 0
	UINT32                                 : 3;   // 15:13
	UINT32 osd_frc_hdr_xoffset             : 13;  // 28:16
} L9A0_OSD_FRC_HDR_4_T;

typedef struct { // 0x3bb8
	UINT32 osd_frc_hdr_disp_height         : 13;  // 12: 0
	UINT32                                 : 3;   // 15:13
	UINT32 osd_frc_hdr_disp_width          : 13;  // 28:16
} L9A0_OSD_FRC_HDR_5_T;

typedef struct { // 0x3bc0
	UINT32 osd3_external_blend_th_l        : 8;   //  7: 0
	UINT32 osd2_external_blend_th_l        : 8;   // 15: 8
	UINT32 osd1_external_blend_th_l        : 8;   // 23:16
	UINT32 osd0_external_blend_th_l        : 8;   // 31:24
} L9A0_OSD_FRC_ABLEND_TH_L_T;

typedef struct { // 0x3bc4
	UINT32 osd3_external_blend_th_r        : 8;   //  7: 0
	UINT32 osd2_external_blend_th_r        : 8;   // 15: 8
	UINT32 osd1_external_blend_th_r        : 8;   // 23:16
	UINT32 osd0_external_blend_th_r        : 8;   // 31:24
} L9A0_OSD_FRC_ABLEND_TH_R_T;

typedef struct { // 0x3bd0
	UINT32 osd_layer_sel                   : 2;   //  1: 0
	UINT32                                 : 2;   //  3: 2
	UINT32 op_mode                         : 1;   //     4
	UINT32                                 : 4;   //  8: 5
	UINT32 osd_ddr_sel_bmp                 : 3;   // 11: 9
	UINT32                                 : 5;   // 16:12
	UINT32 osd_ddr_sel_plt                 : 3;   // 19:17
	UINT32                                 : 5;   // 24:20
	UINT32 osd_ddr_sel_hdr                 : 3;   // 27:25
} L9A0_OSD_DDR_ADDRESSING_T;

typedef struct { // 0x3bd8
	UINT32 crsr_awb_blue                   : 1;   //     0
	UINT32 crsr_awb_green                  : 1;   //     1
	UINT32 crsr_awb_red                    : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 osd2_awb_blue                   : 1;   //     8
	UINT32 osd2_awb_green                  : 1;   //     9
	UINT32 osd2_awb_red                    : 1;   //    10
	UINT32                                 : 5;   // 15:11
	UINT32 osd1_awb_blue                   : 1;   //    16
	UINT32 osd1_awb_green                  : 1;   //    17
	UINT32 osd1_awb_red                    : 1;   //    18
	UINT32                                 : 5;   // 23:19
	UINT32 osd0_awb_blue                   : 1;   //    24
	UINT32 osd0_awb_green                  : 1;   //    25
	UINT32 osd0_awb_red                    : 1;   //    26
} L9A0_OSD_LEFT_AWB_T;

typedef struct { // 0x3bdc
	UINT32 crsr_awb_blue                   : 1;   //     0
	UINT32 crsr_awb_green                  : 1;   //     1
	UINT32 crsr_awb_red                    : 1;   //     2
	UINT32                                 : 5;   //  7: 3
	UINT32 osd2_awb_blue                   : 1;   //     8
	UINT32 osd2_awb_green                  : 1;   //     9
	UINT32 osd2_awb_red                    : 1;   //    10
	UINT32                                 : 5;   // 15:11
	UINT32 osd1_awb_blue                   : 1;   //    16
	UINT32 osd1_awb_green                  : 1;   //    17
	UINT32 osd1_awb_red                    : 1;   //    18
	UINT32                                 : 5;   // 23:19
	UINT32 osd0_awb_blue                   : 1;   //    24
	UINT32 osd0_awb_green                  : 1;   //    25
	UINT32 osd0_awb_red                    : 1;   //    26
} L9A0_OSD_RIGHT_AWB_T;

typedef struct { // 0x3be4
	UINT32 mixer_process_line_l            : 12;  // 11: 0
} L9A0_OSD_L_MIXER_STATUS_T;

typedef struct { // 0x3be8
	UINT32 mixer_process_line_r            : 12;  // 11: 0
} L9A0_OSD_R_MIXER_STATUS_T;

typedef struct { // 0x3bec
	UINT32 osd_status_cfg                  : 4;   //  3: 0
} L9A0_OSD_STATUS_CFG_T;

typedef struct { // 0x3bf0
	UINT32 osd0_process_line               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd0_process_state              : 3;   // 18:16
} L9A0_OSD_STATUS_0_T;

typedef struct { // 0x3bf4
	UINT32 osd1_process_line               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd1_process_state              : 3;   // 18:16
} L9A0_OSD_STATUS_1_T;

typedef struct { // 0x3bf8
	UINT32 osd2_process_line               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd2_process_state              : 3;   // 18:16
} L9A0_OSD_STATUS_2_T;

typedef struct { // 0x3bfc
	UINT32 osd3_process_line               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 osd3_process_state              : 3;   // 18:16
} L9A0_OSD_STATUS_3_T;

typedef struct {
	L9A0_OSD0_CFG_T             osd0_cfg;                    // 0x3a00
	L9A0_OSD1_CFG_T             osd1_cfg;                    // 0x3a04
	L9A0_OSD2_CFG_T             osd2_cfg;                    // 0x3a08
	L9A0_OSD_VERSION_DATE_T     osd_version_date;            // 0x3a0c
	L9A0_OSD_DISP_SIZE_T        osd_disp_size;               // 0x3a10
	L9A0_OSD_IRQ_T              osd_irq;                     // 0x3a14
	L9A0_OSD0_BASE_ADDR_T       osd0_base_addr;              // 0x3a18
	L9A0_OSD0_HDR0_T            osd0_hdr0;                   // 0x3a1c
	L9A0_OSD0_HDR1_T            osd0_hdr1;                   // 0x3a20
	L9A0_OSD0_HDR2_T            osd0_hdr2;                   // 0x3a24
	L9A0_OSD0_HDR3_T            osd0_hdr3;                   // 0x3a28
	L9A0_OSD0_HDR4_T            osd0_hdr4;                   // 0x3a2c
	L9A0_OSD0_HDR5_T            osd0_hdr5;                   // 0x3a30
	L9A0_OSD0_HDR6_T            osd0_hdr6;                   // 0x3a34
	L9A0_OSD0_LFSR_SEED_T       osd0_lfsr_seed;              // 0x3a38
	L9A0_OSD1_BASE_ADDR_T       osd1_base_addr;              // 0x3a3c
	L9A0_OSD1_HDR0_T            osd1_hdr0;                   // 0x3a40
	L9A0_OSD1_HDR1_T            osd1_hdr1;                   // 0x3a44
	L9A0_OSD1_HDR2_T            osd1_hdr2;                   // 0x3a48
	L9A0_OSD1_HDR3_T            osd1_hdr3;                   // 0x3a4c
	L9A0_OSD1_HDR4_T            osd1_hdr4;                   // 0x3a50
	L9A0_OSD1_HDR5_T            osd1_hdr5;                   // 0x3a54
	L9A0_OSD1_HDR6_T            osd1_hdr6;                   // 0x3a58
	L9A0_OSD1_LFSR_SEED_T       osd1_lfsr_seed;              // 0x3a5c
	L9A0_OSD2_BASE_ADDR_T       osd2_base_addr;              // 0x3a60
	L9A0_OSD2_HDR0_T            osd2_hdr0;                   // 0x3a64
	L9A0_OSD2_HDR1_T            osd2_hdr1;                   // 0x3a68
	L9A0_OSD2_HDR2_T            osd2_hdr2;                   // 0x3a6c
	L9A0_OSD2_HDR3_T            osd2_hdr3;                   // 0x3a70
	L9A0_OSD2_HDR4_T            osd2_hdr4;                   // 0x3a74
	L9A0_OSD2_HDR5_T            osd2_hdr5;                   // 0x3a78
	L9A0_OSD2_HDR6_T            osd2_hdr6;                   // 0x3a7c
	L9A0_OSD2_LFSR_SEED_T       osd2_lfsr_seed;              // 0x3a80
	L9A0_OSD0_SC_CFG_T          osd0_sc_cfg;                 // 0x3a84
	L9A0_OSD1_SC_CFG_T          osd1_sc_cfg;                 // 0x3a88
	L9A0_OSD2_SC_CFG_T          osd2_sc_cfg;                 // 0x3a8c
	L9A0_OSD_SC_V_PHASE_OFF_T   osd_sc_v_phase_off;          // 0x3a90
	L9A0_OSD0_CSC_CTRL_T        osd0_csc_ctrl;               // 0x3a94
	L9A0_OSD1_CSC_CTRL_T        osd1_csc_ctrl;               // 0x3a98
	L9A0_OSD2_CSC_CTRL_T        osd2_csc_ctrl;               // 0x3a9c
	UINT32                      reserved0;                   // 0x3aa0
	L9A0_OSD0_END_CONV_T        osd0_end_conv;               // 0x3aa4
	L9A0_OSD1_END_CONV_T        osd1_end_conv;               // 0x3aa8
	L9A0_OSD2_END_CONV_T        osd2_end_conv;               // 0x3aac
	UINT32                      reserved1;                   // 0x3ab0
	L9A0_CRSR_CFG_T             crsr_cfg;                    // 0x3ab4
	L9A0_CRSR_BASE_ADDR_T       crsr_base_addr;              // 0x3ab8
	L9A0_CRSR_HDR0_T            crsr_hdr0;                   // 0x3abc
	L9A0_CRSR_HDR1_T            crsr_hdr1;                   // 0x3ac0
	L9A0_CRSR_HDR2_T            crsr_hdr2;                   // 0x3ac4
	L9A0_CRSR_HDR3_T            crsr_hdr3;                   // 0x3ac8
	L9A0_CRSR_HDR4_T            crsr_hdr4;                   // 0x3acc
	L9A0_CRSR_HDR5_T            crsr_hdr5;                   // 0x3ad0
	L9A0_CRSR_END_CONV_T        crsr_end_conv;               // 0x3ad4
	L9A0_CRSR_LFSR_SEED_T       crsr_lfsr_seed;              // 0x3ad8
	UINT32                      reserved2[5];                // 0x3adc~0x3aec
	L9A0_OSD_LAYER_MUX_LEFT_T   osd_layer_mux_left;          // 0x3af0
	L9A0_OSD_LAYER_MUX_RIGHT_T  osd_layer_mux_right;         // 0x3af4
	L9A0_OSD_MIXER_OUT_LEFT_T   osd_mixer_out_left;          // 0x3af8
	L9A0_OSD_MIXER_OUT_RIGHT_T  osd_mixer_out_right;         // 0x3afc
	L9A0_OSD0_3D_PATH_MODE_T    osd0_3d_path_mode;           // 0x3b00
	L9A0_OSD0_3D_DISPARITY_T    osd0_3d_disparity;           // 0x3b04
	L9A0_OSD0_LEFT_3D_BLANK_T   osd0_left_3d_blank;          // 0x3b08
	L9A0_OSD0_RIGHT_3D_BLANK_T  osd0_right_3d_blank;         // 0x3b0c
	L9A0_OSD0_TB_SPACE_T        osd0_tb_space;               // 0x3b10
	UINT32                      reserved3[3];                // 0x3b14~0x3b1c
	L9A0_OSD1_3D_PATH_MODE_T    osd1_3d_path_mode;           // 0x3b20
	L9A0_OSD1_3D_DISPARITY_T    osd1_3d_disparity;           // 0x3b24
	L9A0_OSD1_LEFT_3D_BLANK_T   osd1_left_3d_blank;          // 0x3b28
	L9A0_OSD1_RIGHT_3D_BLANK_T  osd1_right_3d_blank;         // 0x3b2c
	L9A0_OSD1_TB_SPACE_T        osd1_tb_space;               // 0x3b30
	UINT32                      reserved4[3];                // 0x3b34~0x3b3c
	L9A0_OSD2_3D_PATH_MODE_T    osd2_3d_path_mode;           // 0x3b40
	L9A0_OSD2_3D_DISPARITY_T    osd2_3d_disparity;           // 0x3b44
	L9A0_OSD2_LEFT_3D_BLANK_T   osd2_left_3d_blank;          // 0x3b48
	L9A0_OSD2_RIGHT_3D_BLANK_T  osd2_right_3d_blank;         // 0x3b4c
	L9A0_OSD2_TB_SPACE_T        osd2_tb_space;               // 0x3b50
	UINT32                      reserved5[3];                // 0x3b54~0x3b5c
	L9A0_OSD3_3D_PATH_MODE_T    osd3_3d_path_mode;           // 0x3b60
	L9A0_OSD3_3D_DISPARITY_T    osd3_3d_disparity;           // 0x3b64
	L9A0_OSD3_LEFT_3D_BLANK_T   osd3_left_3d_blank;          // 0x3b68
	L9A0_OSD3_RIGHT_3D_BLANK_T  osd3_right_3d_blank;         // 0x3b6c
	L9A0_OSD3_TB_SPACE_T        osd3_tb_space;               // 0x3b70
	UINT32                      reserved6[11];               // 0x3b74~0x3b9c
	L9A0_OSD_FRC_IF_CFG_T       osd_frc_if_cfg;              // 0x3ba0
	L9A0_OSD_FRC_HDR_0_T        osd_frc_hdr_0;               // 0x3ba4
	L9A0_OSD_FRC_HDR_1_T        osd_frc_hdr_1;               // 0x3ba8
	L9A0_OSD_FRC_HDR_2_T        osd_frc_hdr_2;               // 0x3bac
	L9A0_OSD_FRC_HDR_3_T        osd_frc_hdr_3;               // 0x3bb0
	L9A0_OSD_FRC_HDR_4_T        osd_frc_hdr_4;               // 0x3bb4
	L9A0_OSD_FRC_HDR_5_T        osd_frc_hdr_5;               // 0x3bb8
	UINT32                      reserved7;                   // 0x3bbc
	L9A0_OSD_FRC_ABLEND_TH_L_T  osd_frc_ablend_th_l;         // 0x3bc0
	L9A0_OSD_FRC_ABLEND_TH_R_T  osd_frc_ablend_th_r;         // 0x3bc4
	UINT32                      reserved8[2];                // 0x3bc8~0x3bcc
	L9A0_OSD_DDR_ADDRESSING_T   osd_ddr_addressing;          // 0x3bd0
	UINT32                      reserved9;                   // 0x3bd4
	L9A0_OSD_LEFT_AWB_T         osd_left_awb;                // 0x3bd8
	L9A0_OSD_RIGHT_AWB_T        osd_right_awb;               // 0x3bdc
	UINT32                      reserved10;                  // 0x3be0
	L9A0_OSD_L_MIXER_STATUS_T   osd_l_mixer_status;          // 0x3be4
	L9A0_OSD_R_MIXER_STATUS_T   osd_r_mixer_status;          // 0x3be8
	L9A0_OSD_STATUS_CFG_T       osd_status_cfg;              // 0x3bec
	L9A0_OSD_STATUS_0_T         osd_status_0;                // 0x3bf0
	L9A0_OSD_STATUS_1_T         osd_status_1;                // 0x3bf4
	L9A0_OSD_STATUS_2_T         osd_status_2;                // 0x3bf8
	L9A0_OSD_STATUS_3_T         osd_status_3;                // 0x3bfc
} DE_OSD_REG_L9A0_T;

#endif
