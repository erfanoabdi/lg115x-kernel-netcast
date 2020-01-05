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

#ifndef _REG_OSD_L9B0_h
#define _REG_OSD_L9B0_h

/*-----------------------------------------------------------------------------
	0x5100 osd0_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 osd0_manual_address             : 1;   //     3
	UINT32 osd0_round                      : 3;   //  4: 6
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
	UINT32 osd0_ch_blue                    : 2;   // 24:25
	UINT32 osd0_ch_green                   : 2;   // 26:27
	UINT32 osd0_ch_red                     : 2;   // 28:29
	UINT32 osd0_ch_alpha                   : 2;   // 30:31
} L9B0_OSD0_CFG_T;

/*-----------------------------------------------------------------------------
	0x5104 osd1_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 osd0_manual_address             : 1;   //     3
	UINT32 osd1_round                      : 3;   //  4: 6
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
	UINT32 osd1_ch_blue                    : 2;   // 24:25
	UINT32 osd1_ch_green                   : 2;   // 26:27
	UINT32 osd1_ch_red                     : 2;   // 28:29
	UINT32 osd1_ch_alpha                   : 2;   // 30:31
} L9B0_OSD1_CFG_T;

/*-----------------------------------------------------------------------------
	0x5108 osd2_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 osd0_manual_address             : 1;   //     3
	UINT32 osd2_round                      : 3;   //  4: 6
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
	UINT32 osd2_ch_blue                    : 2;   // 24:25
	UINT32 osd2_ch_green                   : 2;   // 26:27
	UINT32 osd2_ch_red                     : 2;   // 28:29
	UINT32 osd2_ch_alpha                   : 2;   // 30:31
} L9B0_OSD2_CFG_T;

/*-----------------------------------------------------------------------------
	0x510c osd_version_date ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_version_date_f              : 32;   // 31: 0
} L9B0_OSD_VERSION_DATE_T;

/*-----------------------------------------------------------------------------
	0x5110 osd_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_h                          : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 disp_w                          : 12;  // 16:27
} L9B0_OSD_DISP_SIZE_T;

/*-----------------------------------------------------------------------------
	0x5114 osd_irq ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_irq                        : 1;   //     0
	UINT32 osd2_irq                        : 1;   //     1
	UINT32 osd1_irq                        : 1;   //     2
	UINT32 osd0_irq                        : 1;   //     3
	UINT32 mixer_irq                       : 1;   //     4
	UINT32                                 : 11;  //  5:15 reserved
	UINT32 crsr_irq_en                     : 1;   //    16
	UINT32 osd2_irq_en                     : 1;   //    17
	UINT32 osd1_irq_en                     : 1;   //    18
	UINT32 osd0_irq_en                     : 1;   //    19
	UINT32 mixer_irq_en                    : 1;   //    20
} L9B0_OSD_IRQ_T;

/*-----------------------------------------------------------------------------
	0x5118 osd0_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_base_addr                  : 32;  //  0:31
} L9B0_OSD0_BASE_ADDR_T;

/*-----------------------------------------------------------------------------
	0x511c osd0_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_hdr_color_key_en           : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd0_hdr_xpos                   : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 osd0_hdr_ypos                   : 1;   //    31
} L9B0_OSD0_HDR0_T;

/*-----------------------------------------------------------------------------
	0x5120 osd0_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_hdr_h_mem                  : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd0_hdr_w_mem                  : 11;  // 16:26
} L9B0_OSD0_HDR1_T;

/*-----------------------------------------------------------------------------
	0x5124 osd0_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_hdr_h_out                  : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd0_hdr_w_out                  : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 osd0_hdr_pixel_order            : 1;   //    31
} L9B0_OSD0_HDR2_T;

/*-----------------------------------------------------------------------------
	0x5128 osd0_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_hdr_wpl                    : 16;  //  0:15
	UINT32 osd0_hdr_global_alpha           : 8;   // 16:23
	UINT32 osd0_hdr_format                 : 4;   // 24:27
	UINT32 osd0_hdr_depth                  : 3;   // 28:30
	UINT32 osd0_hdr_global_alpha_en        : 1;   //    31
} L9B0_OSD0_HDR3_T;

/*-----------------------------------------------------------------------------
	0x512c osd0_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_hdr_color_key              : 32;  //  0:31
} L9B0_OSD0_HDR4_T;

/*-----------------------------------------------------------------------------
	0x5130 osd0_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_hdr_ptr_plte               : 32;  //  0:31
} L9B0_OSD0_HDR5_T;

/*-----------------------------------------------------------------------------
	0x5134 osd0_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_hdr_ptr_bmp                : 32;  //  0:31
} L9B0_OSD0_HDR6_T;

/*-----------------------------------------------------------------------------
	0x5138 osd0_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_lfsr_seed                  : 19;  //  0:18
} L9B0_OSD0_LFSR_SEED_T;

/*-----------------------------------------------------------------------------
	0x513c osd1_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_base_addr_f                : 32;   // 31: 0
} L9B0_OSD1_BASE_ADDR_T;

/*-----------------------------------------------------------------------------
	0x5140 osd1_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_hdr_color_key_en           : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd1_hdr_xpos                   : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 osd1_hdr_ypos                   : 1;   //    31
} L9B0_OSD1_HDR0_T;

/*-----------------------------------------------------------------------------
	0x5144 osd1_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_hdr_h_mem                  : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd1_hdr_w_mem                  : 11;  // 16:26
} L9B0_OSD1_HDR1_T;

/*-----------------------------------------------------------------------------
	0x5148 osd1_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_hdr_h_out                  : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd1_hdr_w_out                  : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 osd1_hdr_pixel_order            : 1;   //    31
} L9B0_OSD1_HDR2_T;

/*-----------------------------------------------------------------------------
	0x514c osd1_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_hdr_wpl                    : 16;  //  0:15
	UINT32 osd1_hdr_global_alpha           : 8;   // 16:23
	UINT32 osd1_hdr_format                 : 4;   // 24:27
	UINT32 osd1_hdr_depth                  : 3;   // 28:30
	UINT32 osd1_hdr_global_alpha_en        : 1;   //    31
} L9B0_OSD1_HDR3_T;

/*-----------------------------------------------------------------------------
	0x5150 osd1_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_hdr_color_key              : 32;  //  0:31
} L9B0_OSD1_HDR4_T;

/*-----------------------------------------------------------------------------
	0x5154 osd1_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_hdr_ptr_plte               : 32;  //  0:31
} L9B0_OSD1_HDR5_T;

/*-----------------------------------------------------------------------------
	0x5158 osd1_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_hdr_ptr_bmp                : 32;  //  0:31
} L9B0_OSD1_HDR6_T;

/*-----------------------------------------------------------------------------
	0x515c osd1_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_lfsr_seed                  : 19;  //  0:18
} L9B0_OSD1_LFSR_SEED_T;

/*-----------------------------------------------------------------------------
	0x5160 osd2_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_base_addr                  : 32;  //  0:31
} L9B0_OSD2_BASE_ADDR_T;

/*-----------------------------------------------------------------------------
	0x5164 osd2_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_hdr_color_key_en           : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd2_hdr_xpos                   : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 osd2_hdr_ypos                   : 1;   //    31
} L9B0_OSD2_HDR0_T;

/*-----------------------------------------------------------------------------
	0x5168 osd2_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_hdr_h_mem                  : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd2_hdr_w_mem                  : 11;  // 16:26
} L9B0_OSD2_HDR1_T;

/*-----------------------------------------------------------------------------
	0x516c osd2_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_hdr_h_out                  : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd2_hdr_w_out                  : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 osd2_hdr_pixel_order            : 1;   //    31
} L9B0_OSD2_HDR2_T;

/*-----------------------------------------------------------------------------
	0x5170 osd2_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_hdr_wpl                    : 16;  //  0:15
	UINT32 osd2_hdr_global_alpha           : 8;   // 16:23
	UINT32 osd2_hdr_format                 : 4;   // 24:27
	UINT32 osd2_hdr_depth                  : 3;   // 28:30
	UINT32 osd2_hdr_global_alpha_en        : 1;   //    31
} L9B0_OSD2_HDR3_T;

/*-----------------------------------------------------------------------------
	0x5174 osd2_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_hdr_color_key              : 32;  //  0:31
} L9B0_OSD2_HDR4_T;

/*-----------------------------------------------------------------------------
	0x5178 osd2_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_hdr_ptr_plte               : 32;  //  0:31
} L9B0_OSD2_HDR5_T;

/*-----------------------------------------------------------------------------
	0x517c osd2_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_hdr_ptr_bmp                : 32;  //  0:31
} L9B0_OSD2_HDR6_T;

/*-----------------------------------------------------------------------------
	0x5180 osd2_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_lfsr_seed                  : 19;  //  0:18
} L9B0_OSD2_LFSR_SEED_T;

/*-----------------------------------------------------------------------------
	0x5184 osd0_sc_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_sc_vs_en                   : 1;   //     0
	UINT32 osd0_sc_hs_en                   : 1;   //     1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 osd0_sc_bc_sa                   : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 osd0_sc_bnd_mode                : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 osd0_sc_h2v_path                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 osd0_sc_h_phase_off             : 12;  // 16:27
	UINT32                                 : 3;   // 28:30 reserved
	UINT32 osd0_sc_buf_mode_en             : 1;   //    31
} L9B0_OSD0_SC_CFG_T;

/*-----------------------------------------------------------------------------
	0x5188 osd1_sc_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_sc_vs_en                   : 1;   //     0
	UINT32 osd1_sc_hs_en                   : 1;   //     1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 osd1_sc_bc_sa                   : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 osd1_sc_bnd_mode                : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 osd1_sc_h2v_path                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 osd1_sc_h_phase_off             : 12;  // 16:27
	UINT32                                 : 3;   // 28:30 reserved
	UINT32 osd1_sc_buf_mode_en             : 1;   //    31
} L9B0_OSD1_SC_CFG_T;

/*-----------------------------------------------------------------------------
	0x518c osd2_sc_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_sc_vs_en                   : 1;   //     0
	UINT32 osd2_sc_hs_en                   : 1;   //     1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 osd2_sc_bc_sa                   : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 osd2_sc_bnd_mode                : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 osd2_sc_h2v_path                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 osd2_sc_h_phase_off             : 12;  // 16:27
	UINT32                                 : 3;   // 28:30 reserved
	UINT32 osd2_sc_buf_mode_en             : 1;   //    31
} L9B0_OSD2_SC_CFG_T;

/*-----------------------------------------------------------------------------
	0x5190 osd_sc_v_phase_off ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_sc_v_phase_off              : 13;  //  0:12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 osd_sc_v_phase_off_index        : 2;   // 16:17
	UINT32                                 : 13;  // 18:30 reserved
	UINT32 osd_sc_v_phase_off_rw           : 1;   //    31
} L9B0_OSD_SC_V_PHASE_OFF_T;

/*-----------------------------------------------------------------------------
	0x51a4 osd0_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_bbs                        : 1;   //     0
	UINT32 osd0_bqws                       : 1;   //     1
	UINT32 osd0_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3 reserved
	UINT32 osd0_pbs                        : 1;   //     4
	UINT32 osd0_pqws                       : 1;   //     5
	UINT32 osd0_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7 reserved
	UINT32 osd0_hbs                        : 1;   //     8
	UINT32 osd0_hqws                       : 1;   //     9
	UINT32 osd0_hhws                       : 1;   //    10
} L9B0_OSD0_END_CONV_T;

/*-----------------------------------------------------------------------------
	0x51a8 osd1_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_bbs                        : 1;   //     0
	UINT32 osd1_bqws                       : 1;   //     1
	UINT32 osd1_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3 reserved
	UINT32 osd1_pbs                        : 1;   //     4
	UINT32 osd1_pqws                       : 1;   //     5
	UINT32 osd1_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7 reserved
	UINT32 osd1_hbs                        : 1;   //     8
	UINT32 osd1_hqws                       : 1;   //     9
	UINT32 osd1_hhws                       : 1;   //    10
} L9B0_OSD1_END_CONV_T;

/*-----------------------------------------------------------------------------
	0x51ac osd2_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_bbs                        : 1;   //     0
	UINT32 osd2_bqws                       : 1;   //     1
	UINT32 osd2_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3 reserved
	UINT32 osd2_pbs                        : 1;   //     4
	UINT32 osd2_pqws                       : 1;   //     5
	UINT32 osd2_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7 reserved
	UINT32 osd2_hbs                        : 1;   //     8
	UINT32 osd2_hqws                       : 1;   //     9
	UINT32 osd2_hhws                       : 1;   //    10
} L9B0_OSD2_END_CONV_T;

/*-----------------------------------------------------------------------------
	0x51b4 crsr_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_en                         : 1;   //     0
	UINT32 osd0_double_h                   : 1;   //     1
	UINT32 osd0_double_w                   : 1;   //     2
	UINT32 crsr_manual_address             : 1;   //     3
	UINT32 crsr_round                      : 3;   //  4: 6
	UINT32 crsr_pure_color_key             : 1;   //     7
	UINT32 crsr_hdr_ptr_bmp_sel            : 1;   //     8
	UINT32 crsr_hdr_ptr_plte_sel           : 1;   //     9
	UINT32 crsr_hdr_color_key_sel          : 1;   //    10
	UINT32 crsr_hdr_wpl_sel                : 1;   //    11
	UINT32 crsr_hdr_global_alpha_sel       : 1;   //    12
	UINT32 crsr_hdr_format_sel             : 1;   //    13
	UINT32 crsr_hdr_depth_sel              : 1;   //    14
	UINT32                                 : 2;   // 15:16 reserved
	UINT32 crsr_hdr_global_alpha_en_sel    : 1;   //    17
	UINT32 crsr_hdr_pixel_order_sel        : 1;   //    18
	UINT32 crsr_hdr_h_mem_sel              : 1;   //    19
	UINT32 crsr_hdr_w_mem_sel              : 1;   //    20
	UINT32 crsr_hdr_ypos_sel               : 1;   //    21
	UINT32 crsr_hdr_xpos_sel               : 1;   //    22
	UINT32 crsr_hdr_color_key_en_sel       : 1;   //    23
	UINT32 crsr_ch_blue                    : 2;   // 24:25
	UINT32 crsr_ch_green                   : 2;   // 26:27
	UINT32 crsr_ch_red                     : 2;   // 28:29
	UINT32 crsr_ch_alpha                   : 2;   // 30:31
} L9B0_CRSR_CFG_T;

/*-----------------------------------------------------------------------------
	0x51b8 crsr_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_base_addr                  : 32;  //  0:31
} L9B0_CRSR_BASE_ADDR_T;

/*-----------------------------------------------------------------------------
	0x51bc crsr_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_hdr_ypos                   : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 crsr_hdr_xpos                   : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 crsr_hdr_pos_load               : 1;   //    31
} L9B0_CRSR_HDR0_T;

/*-----------------------------------------------------------------------------
	0x51c0 crsr_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_hdr_h_mem                  : 12;  //  0:11
	UINT32                                 : 3;   // 12:14 reserved
	UINT32 crsr_hdr_pixel_order            : 1;   //    15
	UINT32 crsr_hdr_w_mem                  : 11;  // 16:26
	UINT32                                 : 4;   // 27:30 reserved
	UINT32 crsr_hdr_color_key_en           : 1;   //    31
} L9B0_CRSR_HDR1_T;

/*-----------------------------------------------------------------------------
	0x51c4 crsr_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_hdr_wpl                    : 16;  //  0:15
	UINT32 crsr_hdr_global_alpha           : 8;   // 16:23
	UINT32 crsr_hdr_format                 : 4;   // 24:27
	UINT32 crsr_hdr_depth                  : 3;   // 28:30
	UINT32 crsr_hdr_global_alpha_en        : 1;   //    31
} L9B0_CRSR_HDR2_T;

/*-----------------------------------------------------------------------------
	0x51c8 crsr_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_hdr_color_key              : 32;  //  0:31
} L9B0_CRSR_HDR3_T;

/*-----------------------------------------------------------------------------
	0x51cc crsr_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_hdr_ptr_plte               : 32;  //  0:31
} L9B0_CRSR_HDR4_T;

/*-----------------------------------------------------------------------------
	0x51d0 crsr_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_hdr_ptr_bmp                : 32;  //  0:31
} L9B0_CRSR_HDR5_T;

/*-----------------------------------------------------------------------------
	0x51d4 crsr_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_bbs                        : 1;   //     0
	UINT32 crsr_bqws                       : 1;   //     1
	UINT32 crsr_bhws                       : 1;   //     2
	UINT32                                 : 1;   //     3 reserved
	UINT32 crsr_pbs                        : 1;   //     4
	UINT32 crsr_pqws                       : 1;   //     5
	UINT32 crsr_phws                       : 1;   //     6
	UINT32                                 : 1;   //     7 reserved
	UINT32 crsr_hbs                        : 1;   //     8
	UINT32 crsr_hqws                       : 1;   //     9
	UINT32 crsr_hhws                       : 1;   //    10
} L9B0_CRSR_END_CONV_T;

/*-----------------------------------------------------------------------------
	0x51d8 crsr_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_lfsr_seed                  : 19;  //  0:18
} L9B0_CRSR_LFSR_SEED_T;

/*-----------------------------------------------------------------------------
	0x51f0 osd_layer_mux_left ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 layer_mux_3                     : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 layer_mux_2                     : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 layer_mux_1                     : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 layer_mux_0                     : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 video_layer_alpha               : 8;   // 16:23
} L9B0_OSD_LAYER_MUX_LEFT_T;

/*-----------------------------------------------------------------------------
	0x51f4 osd_layer_mux_right ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 layer_mux_3                     : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 layer_mux_2                     : 2;   //  4: 5
	UINT32                                 : 2;   //  6: 7 reserved
	UINT32 layer_mux_1                     : 2;   //  8: 9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 layer_mux_0                     : 2;   // 12:13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 video_layer_alpha               : 8;   // 16:23
} L9B0_OSD_LAYER_MUX_RIGHT_T;

/*-----------------------------------------------------------------------------
	0x51f8 osd_mixer_out_left ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mixer_out_blue                  : 10;  //  0: 9
	UINT32 mixer_out_green                 : 10;  // 10:19
	UINT32 mixer_out_red                   : 10;  // 20:29
	UINT32 mixer_mask_en                   : 1;   //    30
	UINT32 mixer_out_en                    : 1;   //    31
} L9B0_OSD_MIXER_OUT_LEFT_T;

/*-----------------------------------------------------------------------------
	0x51fc osd_mixer_out_right ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mixer_out_blue                  : 10;  //  0: 9
	UINT32 mixer_out_green                 : 10;  // 10:19
	UINT32 mixer_out_red                   : 10;  // 20:29
	UINT32 mixer_mask_en                   : 1;   //    30
	UINT32 mixer_out_en                    : 1;   //    31
} L9B0_OSD_MIXER_OUT_RIGHT_T;

/*-----------------------------------------------------------------------------
	0x5200 osd0_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_path_sel                   : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 osd0_path_buf_half              : 1;   //     4
	UINT32 osd0_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  //  6:15 reserved
	UINT32 osd0_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 osd0_3d_mode_sel                : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 osd0_3d_mode_dual               : 1;   //    24
} L9B0_OSD0_3D_PATH_MODE_T;

/*-----------------------------------------------------------------------------
	0x5204 osd0_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_rb_disparity_value         : 8;   //  0: 7
	UINT32 osd0_rb_disparity_sign_b08      : 1;   //     8
	UINT32                                 : 7;   //  9:15 reserved
	UINT32 osd0_lt_disparity_value         : 8;   // 16:23
	UINT32 osd0_rb_disparity_sign_b24      : 1;   //    24
} L9B0_OSD0_3D_DISPARITY_T;

/*-----------------------------------------------------------------------------
	0x5208 osd0_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_left_3d_blank              : 32;  //  0:31
} L9B0_OSD0_LEFT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x520c osd0_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_right_3d_blank             : 32;  //  0:31
} L9B0_OSD0_RIGHT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x5210 osd0_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_tb_line_space              : 12;  //  0:11
} L9B0_OSD0_TB_SPACE_T;

/*-----------------------------------------------------------------------------
	0x5220 osd1_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_path_sel                   : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 osd1_path_buf_half              : 1;   //     4
	UINT32 osd1_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  //  6:15 reserved
	UINT32 osd1_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 osd1_3d_mode_sel                : 1;   //    20
} L9B0_OSD1_3D_PATH_MODE_T;

/*-----------------------------------------------------------------------------
	0x5224 osd1_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_right_disparity            : 8;   //  0: 7
	UINT32 osd1_right_disparity_sign       : 1;   //     8
	UINT32                                 : 7;   //  9:15 reserved
	UINT32 osd1_left_disparity             : 8;   // 16:23
	UINT32 osd1_left_disparity_sign        : 1;   //    24
} L9B0_OSD1_3D_DISPARITY_T;

/*-----------------------------------------------------------------------------
	0x5228 osd1_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_left_3d_blank              : 32;  //  0:31
} L9B0_OSD1_LEFT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x522c osd1_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_right_3d_blank             : 32;  //  0:31
} L9B0_OSD1_RIGHT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x5230 osd1_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_tb_line_space              : 12;  //  0:11
} L9B0_OSD1_TB_SPACE_T;

/*-----------------------------------------------------------------------------
	0x5240 osd2_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_path_sel                   : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 osd2_path_buf_half              : 1;   //     4
	UINT32 osd2_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  //  6:15 reserved
	UINT32 osd2_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 osd2_3d_mode_sel                : 1;   //    20
} L9B0_OSD2_3D_PATH_MODE_T;

/*-----------------------------------------------------------------------------
	0x5244 osd2_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_right_disparity            : 8;   //  0: 7
	UINT32 osd2_right_disparity_sign       : 1;   //     8
	UINT32                                 : 7;   //  9:15 reserved
	UINT32 osd2_left_disparity             : 8;   // 16:23
	UINT32 osd2_left_disparity_sign        : 1;   //    24
} L9B0_OSD2_3D_DISPARITY_T;

/*-----------------------------------------------------------------------------
	0x5248 osd2_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_left_3d_blank              : 32;  //  0:31
} L9B0_OSD2_LEFT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x524c osd2_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_right_3d_blank             : 32;  //  0:31
} L9B0_OSD2_RIGHT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x5250 osd2_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_tb_line_space              : 12;  //  0:11
} L9B0_OSD2_TB_SPACE_T;

/*-----------------------------------------------------------------------------
	0x5260 osd3_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_path_sel                   : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 osd3_path_buf_half              : 1;   //     4
	UINT32 osd3_path_buf_repeat            : 1;   //     5
	UINT32                                 : 10;  //  6:15 reserved
	UINT32 osd3_3d_en                      : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 osd3_3d_mode_sel                : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 osd3_3d_mode_dual               : 1;   //    24
} L9B0_OSD3_3D_PATH_MODE_T;

/*-----------------------------------------------------------------------------
	0x5264 osd3_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_right_disparity            : 8;   //  0: 7
	UINT32 osd3_right_disparity_sign       : 1;   //     8
	UINT32                                 : 7;   //  9:15 reserved
	UINT32 osd3_left_disparity             : 8;   // 16:23
	UINT32 osd3_left_disparity_sign        : 1;   //    24
} L9B0_OSD3_3D_DISPARITY_T;

/*-----------------------------------------------------------------------------
	0x5268 osd3_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_left_3d_blank              : 32;  //  0:31
} L9B0_OSD3_LEFT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x526c osd3_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_right_3d_blank             : 32;  //  0:31
} L9B0_OSD3_RIGHT_3D_BLANK_T;

/*-----------------------------------------------------------------------------
	0x5270 osd3_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_tb_line_space              : 12;  //  0:11
} L9B0_OSD3_TB_SPACE_T;

/*-----------------------------------------------------------------------------
	0x52a0 osd_frc_if_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_frc_if_en                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 osd_frc_layer_sel               : 2;   //  4: 5
	UINT32 osd_frc_lr_sel                  : 1;   //     6
} L9B0_OSD_FRC_IF_CFG_T;

/*-----------------------------------------------------------------------------
	0x52a4 osd_frc_hdr_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_frc_hdr_0                   : 30;  //  0:29
} L9B0_OSD_FRC_HDR_0_T;

/*-----------------------------------------------------------------------------
	0x52a8 osd_frc_hdr_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 16;  //  0:15 reserved
	UINT32 osd_frc_hdr_1                   : 13;  // 16:28
} L9B0_OSD_FRC_HDR_1_T;

/*-----------------------------------------------------------------------------
	0x52ac osd_frc_hdr_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 15;  //  0:14 reserved
	UINT32 osd_frc_hdr_2                   : 1;   //    15
} L9B0_OSD_FRC_HDR_2_T;

/*-----------------------------------------------------------------------------
	0x52b0 osd_frc_hdr_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 16;  //  0:15 reserved
	UINT32 osd_frc_hdr_3                   : 8;   // 16:23
} L9B0_OSD_FRC_HDR_3_T;

/*-----------------------------------------------------------------------------
	0x52b4 osd_frc_hdr_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 16;  //  0:15 reserved
	UINT32 osd_frc_hdr_4                   : 13;  // 16:28
} L9B0_OSD_FRC_HDR_4_T;

/*-----------------------------------------------------------------------------
	0x52b8 osd_frc_hdr_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 16;  //  0:15 reserved
	UINT32 osd_frc_hdr_5                   : 13;  // 16:28
} L9B0_OSD_FRC_HDR_5_T;

/*-----------------------------------------------------------------------------
	0x52c0 osd_frc_ablend_th_l ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_external_blend_th_l        : 8;   //  0: 7
	UINT32 osd2_external_blend_th_l        : 8;   //  8:15
	UINT32 osd1_external_blend_th_l        : 8;   // 16:23
	UINT32 osd0_external_blend_th_l        : 8;   // 24:31
} L9B0_OSD_FRC_ABLEND_TH_L_T;

/*-----------------------------------------------------------------------------
	0x52c4 osd_frc_ablend_th_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_external_blend_th_r        : 8;   //  0: 7
	UINT32 osd2_external_blend_th_r        : 8;   //  8:15
	UINT32 osd1_external_blend_th_r        : 8;   // 16:23
	UINT32 osd0_external_blend_th_r        : 8;   // 24:31
} L9B0_OSD_FRC_ABLEND_TH_R_T;

/*-----------------------------------------------------------------------------
	0x52d4 osd_palette_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_palette_sel                 : 2;   //  0: 1
} L9B0_OSD_PALETTE_SEL_T;

/*-----------------------------------------------------------------------------
	0x52d8 osd_left_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_awb_blue                   : 1;   //     0
	UINT32 crsr_awb_green                  : 1;   //     1
	UINT32 crsr_awb_red                    : 1;   //     2
	UINT32                                 : 5;   //  3: 7 reserved
	UINT32 osd2_awb_blue                   : 1;   //     8
	UINT32 osd2_awb_green                  : 1;   //     9
	UINT32 osd2_awb_red                    : 1;   //    10
	UINT32                                 : 5;   // 11:15 reserved
	UINT32 osd1_awb_blue                   : 1;   //    16
	UINT32 osd1_awb_green                  : 1;   //    17
	UINT32 osd1_awb_red                    : 1;   //    18
	UINT32                                 : 5;   // 19:23 reserved
	UINT32 osd0_awb_blue                   : 1;   //    24
	UINT32 osd0_awb_green                  : 1;   //    25
	UINT32 osd0_awb_red                    : 1;   //    26
} L9B0_OSD_LEFT_AWB_T;

/*-----------------------------------------------------------------------------
	0x52dc osd_right_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crsr_awb_blue                   : 1;   //     0
	UINT32 crsr_awb_green                  : 1;   //     1
	UINT32 crsr_awb_red                    : 1;   //     2
	UINT32                                 : 5;   //  3: 7 reserved
	UINT32 osd2_awb_blue                   : 1;   //     8
	UINT32 osd2_awb_green                  : 1;   //     9
	UINT32 osd2_awb_red                    : 1;   //    10
	UINT32                                 : 5;   // 11:15 reserved
	UINT32 osd1_awb_blue                   : 1;   //    16
	UINT32 osd1_awb_green                  : 1;   //    17
	UINT32 osd1_awb_red                    : 1;   //    18
	UINT32                                 : 5;   // 19:23 reserved
	UINT32 osd0_awb_blue                   : 1;   //    24
	UINT32 osd0_awb_green                  : 1;   //    25
	UINT32 osd0_awb_red                    : 1;   //    26
} L9B0_OSD_RIGHT_AWB_T;

/*-----------------------------------------------------------------------------
	0x52e4 osd_l_mixer_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mixer_process_line_l            : 12;  //  0:11
} L9B0_OSD_L_MIXER_STATUS_T;

/*-----------------------------------------------------------------------------
	0x52e8 osd_r_mixer_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mixer_process_line_r            : 12;  //  0:11
} L9B0_OSD_R_MIXER_STATUS_T;

/*-----------------------------------------------------------------------------
	0x52ec osd_status_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_status_cfg                  : 4;   //  0: 3
} L9B0_OSD_STATUS_CFG_T;

/*-----------------------------------------------------------------------------
	0x52f0 osd_status_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd0_process_line               : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd0_process_state              : 3;   // 16:18
} L9B0_OSD_STATUS_0_T;

/*-----------------------------------------------------------------------------
	0x52f4 osd_status_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd1_process_line               : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd1_process_state              : 3;   // 16:18
} L9B0_OSD_STATUS_1_T;

/*-----------------------------------------------------------------------------
	0x52f8 osd_status_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd2_process_line               : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd2_process_state              : 3;   // 16:18
} L9B0_OSD_STATUS_2_T;

/*-----------------------------------------------------------------------------
	0x52fc osd_status_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_process_line               : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 osd3_process_state              : 3;   // 16:18
} L9B0_OSD_STATUS_3_T;

typedef struct {
	L9B0_OSD0_CFG_T             osd0_cfg;                    // 0x5100
	L9B0_OSD1_CFG_T             osd1_cfg;                    // 0x5104
	L9B0_OSD2_CFG_T             osd2_cfg;                    // 0x5108
	L9B0_OSD_VERSION_DATE_T     osd_version_date;            // 0x510c
	L9B0_OSD_DISP_SIZE_T        osd_disp_size;               // 0x5110
	L9B0_OSD_IRQ_T              osd_irq;                     // 0x5114
	L9B0_OSD0_BASE_ADDR_T       osd0_base_addr;              // 0x5118
	L9B0_OSD0_HDR0_T            osd0_hdr0;                   // 0x511c
	L9B0_OSD0_HDR1_T            osd0_hdr1;                   // 0x5120
	L9B0_OSD0_HDR2_T            osd0_hdr2;                   // 0x5124
	L9B0_OSD0_HDR3_T            osd0_hdr3;                   // 0x5128
	L9B0_OSD0_HDR4_T            osd0_hdr4;                   // 0x512c
	L9B0_OSD0_HDR5_T            osd0_hdr5;                   // 0x5130
	L9B0_OSD0_HDR6_T            osd0_hdr6;                   // 0x5134
	L9B0_OSD0_LFSR_SEED_T       osd0_lfsr_seed;              // 0x5138
	L9B0_OSD1_BASE_ADDR_T       osd1_base_addr;              // 0x513c
	L9B0_OSD1_HDR0_T            osd1_hdr0;                   // 0x5140
	L9B0_OSD1_HDR1_T            osd1_hdr1;                   // 0x5144
	L9B0_OSD1_HDR2_T            osd1_hdr2;                   // 0x5148
	L9B0_OSD1_HDR3_T            osd1_hdr3;                   // 0x514c
	L9B0_OSD1_HDR4_T            osd1_hdr4;                   // 0x5150
	L9B0_OSD1_HDR5_T            osd1_hdr5;                   // 0x5154
	L9B0_OSD1_HDR6_T            osd1_hdr6;                   // 0x5158
	L9B0_OSD1_LFSR_SEED_T       osd1_lfsr_seed;              // 0x515c
	L9B0_OSD2_BASE_ADDR_T       osd2_base_addr;              // 0x5160
	L9B0_OSD2_HDR0_T            osd2_hdr0;                   // 0x5164
	L9B0_OSD2_HDR1_T            osd2_hdr1;                   // 0x5168
	L9B0_OSD2_HDR2_T            osd2_hdr2;                   // 0x516c
	L9B0_OSD2_HDR3_T            osd2_hdr3;                   // 0x5170
	L9B0_OSD2_HDR4_T            osd2_hdr4;                   // 0x5174
	L9B0_OSD2_HDR5_T            osd2_hdr5;                   // 0x5178
	L9B0_OSD2_HDR6_T            osd2_hdr6;                   // 0x517c
	L9B0_OSD2_LFSR_SEED_T       osd2_lfsr_seed;              // 0x5180
	L9B0_OSD0_SC_CFG_T          osd0_sc_cfg;                 // 0x5184
	L9B0_OSD1_SC_CFG_T          osd1_sc_cfg;                 // 0x5188
	L9B0_OSD2_SC_CFG_T          osd2_sc_cfg;                 // 0x518c
	L9B0_OSD_SC_V_PHASE_OFF_T   osd_sc_v_phase_off;          // 0x5190
	UINT32                      reserved0[4];                // 0x5194~0x51a0
	L9B0_OSD0_END_CONV_T        osd0_end_conv;               // 0x51a4
	L9B0_OSD1_END_CONV_T        osd1_end_conv;               // 0x51a8
	L9B0_OSD2_END_CONV_T        osd2_end_conv;               // 0x51ac
	UINT32                      reserved1;                   // 0x51b0
	L9B0_CRSR_CFG_T             crsr_cfg;                    // 0x51b4
	L9B0_CRSR_BASE_ADDR_T       crsr_base_addr;              // 0x51b8
	L9B0_CRSR_HDR0_T            crsr_hdr0;                   // 0x51bc
	L9B0_CRSR_HDR1_T            crsr_hdr1;                   // 0x51c0
	L9B0_CRSR_HDR2_T            crsr_hdr2;                   // 0x51c4
	L9B0_CRSR_HDR3_T            crsr_hdr3;                   // 0x51c8
	L9B0_CRSR_HDR4_T            crsr_hdr4;                   // 0x51cc
	L9B0_CRSR_HDR5_T            crsr_hdr5;                   // 0x51d0
	L9B0_CRSR_END_CONV_T        crsr_end_conv;               // 0x51d4
	L9B0_CRSR_LFSR_SEED_T       crsr_lfsr_seed;              // 0x51d8
	UINT32                      reserved2[5];                // 0x51dc~0x51ec
	L9B0_OSD_LAYER_MUX_LEFT_T   osd_layer_mux_left;          // 0x51f0
	L9B0_OSD_LAYER_MUX_RIGHT_T  osd_layer_mux_right;         // 0x51f4
	L9B0_OSD_MIXER_OUT_LEFT_T   osd_mixer_out_left;          // 0x51f8
	L9B0_OSD_MIXER_OUT_RIGHT_T  osd_mixer_out_right;         // 0x51fc
	L9B0_OSD0_3D_PATH_MODE_T    osd0_3d_path_mode;           // 0x5200
	L9B0_OSD0_3D_DISPARITY_T    osd0_3d_disparity;           // 0x5204
	L9B0_OSD0_LEFT_3D_BLANK_T   osd0_left_3d_blank;          // 0x5208
	L9B0_OSD0_RIGHT_3D_BLANK_T  osd0_right_3d_blank;         // 0x520c
	L9B0_OSD0_TB_SPACE_T        osd0_tb_space;               // 0x5210
	UINT32                      reserved3[3];                // 0x5214~0x521c
	L9B0_OSD1_3D_PATH_MODE_T    osd1_3d_path_mode;           // 0x5220
	L9B0_OSD1_3D_DISPARITY_T    osd1_3d_disparity;           // 0x5224
	L9B0_OSD1_LEFT_3D_BLANK_T   osd1_left_3d_blank;          // 0x5228
	L9B0_OSD1_RIGHT_3D_BLANK_T  osd1_right_3d_blank;         // 0x522c
	L9B0_OSD1_TB_SPACE_T        osd1_tb_space;               // 0x5230
	UINT32                      reserved4[3];                // 0x5234~0x523c
	L9B0_OSD2_3D_PATH_MODE_T    osd2_3d_path_mode;           // 0x5240
	L9B0_OSD2_3D_DISPARITY_T    osd2_3d_disparity;           // 0x5244
	L9B0_OSD2_LEFT_3D_BLANK_T   osd2_left_3d_blank;          // 0x5248
	L9B0_OSD2_RIGHT_3D_BLANK_T  osd2_right_3d_blank;         // 0x524c
	L9B0_OSD2_TB_SPACE_T        osd2_tb_space;               // 0x5250
	UINT32                      reserved5[3];                // 0x5254~0x525c
	L9B0_OSD3_3D_PATH_MODE_T    osd3_3d_path_mode;           // 0x5260
	L9B0_OSD3_3D_DISPARITY_T    osd3_3d_disparity;           // 0x5264
	L9B0_OSD3_LEFT_3D_BLANK_T   osd3_left_3d_blank;          // 0x5268
	L9B0_OSD3_RIGHT_3D_BLANK_T  osd3_right_3d_blank;         // 0x526c
	L9B0_OSD3_TB_SPACE_T        osd3_tb_space;               // 0x5270
	UINT32                      reserved6[11];               // 0x5274~0x529c
	L9B0_OSD_FRC_IF_CFG_T       osd_frc_if_cfg;              // 0x52a0
	L9B0_OSD_FRC_HDR_0_T        osd_frc_hdr_0;               // 0x52a4
	L9B0_OSD_FRC_HDR_1_T        osd_frc_hdr_1;               // 0x52a8
	L9B0_OSD_FRC_HDR_2_T        osd_frc_hdr_2;               // 0x52ac
	L9B0_OSD_FRC_HDR_3_T        osd_frc_hdr_3;               // 0x52b0
	L9B0_OSD_FRC_HDR_4_T        osd_frc_hdr_4;               // 0x52b4
	L9B0_OSD_FRC_HDR_5_T        osd_frc_hdr_5;               // 0x52b8
	UINT32                      reserved7;                   // 0x52bc
	L9B0_OSD_FRC_ABLEND_TH_L_T  osd_frc_ablend_th_l;         // 0x52c0
	L9B0_OSD_FRC_ABLEND_TH_R_T  osd_frc_ablend_th_r;         // 0x52c4
	UINT32                      reserved8[3];                // 0x52c8~0x52d0
	L9B0_OSD_PALETTE_SEL_T      osd_palette_sel;             // 0x52d4
	L9B0_OSD_LEFT_AWB_T         osd_left_awb;                // 0x52d8
	L9B0_OSD_RIGHT_AWB_T        osd_right_awb;               // 0x52dc
	UINT32                      reserved9;                   // 0x52e0
	L9B0_OSD_L_MIXER_STATUS_T   osd_l_mixer_status;          // 0x52e4
	L9B0_OSD_R_MIXER_STATUS_T   osd_r_mixer_status;          // 0x52e8
	L9B0_OSD_STATUS_CFG_T       osd_status_cfg;              // 0x52ec
	L9B0_OSD_STATUS_0_T         osd_status_0;                // 0x52f0
	L9B0_OSD_STATUS_1_T         osd_status_1;                // 0x52f4
	L9B0_OSD_STATUS_2_T         osd_status_2;                // 0x52f8
	L9B0_OSD_STATUS_3_T         osd_status_3;                // 0x52fc
} DE_OSD_REG_L9B0_T;

#endif
