/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/

/** @file
 *
 *  #MOD# register details. ( used only within kdriver )
 *
 *  author     Juhee Park (user_name@lge.com)
 *  version    1.0
 *  date       2011.03.17
 *
 */

#ifndef _FBDEV_L9A0_OSD_REG_H_
#define _FBDEV_L9A0_OSD_REG_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
	0x1a00 osd0_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_en                         : 1,	//     0
	osd0_double_h                   : 1,	//     1
	osd0_double_w                   : 1,	//     2
	osd0_manual_address             : 1,	//     3
	osd0_round                      : 3,	//  4: 6
	osd0_pure_ck                    : 1,	//     7
	osd0_hdr_ptr_bmp_sel            : 1,	//     8
	osd0_hdr_ptr_plte_sel           : 1,	//     9
	osd0_hdr_color_key_sel          : 1,	//    10
	osd0_hdr_wpl_sel                : 1,	//    11
	osd0_hdr_global_alpha_sel       : 1,	//    12
	osd0_hdr_format_sel             : 1,	//    13
	osd0_hdr_depth_sel              : 1,	//    14
	osd0_hdr_h_out_sel              : 1,	//    15
	osd0_hdr_w_out_sel              : 1,	//    16
	osd0_hdr_global_alpha_en_sel    : 1,	//    17
	osd0_hdr_pixel_order_sel        : 1,	//    18
	osd0_hdr_h_mem_sel              : 1,	//    19
	osd0_hdr_w_mem_sel              : 1,	//    20
	osd0_hdr_ypos_sel               : 1,	//    21
	osd0_hdr_xpos_sel               : 1,	//    22
	osd0_hdr_color_key_en_sel       : 1,	//    23
	osd0_ch_blue                    : 2,	// 24:25
	osd0_ch_green                   : 2,	// 26:27
	osd0_ch_red                     : 2,	// 28:29
	osd0_ch_alpha                   : 2;	// 30:31
} OSD0_L9A0_CFG;

/*-----------------------------------------------------------------------------
	0x1a04 osd1_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_en                         : 1,	//     0
	osd1_double_h                   : 1,	//     1
	osd1_double_w                   : 1,	//     2
	osd1_manual_address             : 1,	//     3
	osd1_round                      : 3,	//  4: 6
	osd1_pure_ck                    : 1,	//     7
	osd1_hdr_ptr_bmp_sel            : 1,	//     8
	osd1_hdr_ptr_plte_sel           : 1,	//     9
	osd1_hdr_color_key_sel          : 1,	//    10
	osd1_hdr_wpl_sel                : 1,	//    11
	osd1_hdr_global_alpha_sel       : 1,	//    12
	osd1_hdr_format_sel             : 1,	//    13
	osd1_hdr_depth_sel              : 1,	//    14
	osd1_hdr_h_out_sel              : 1,	//    15
	osd1_hdr_w_out_sel              : 1,	//    16
	osd1_hdr_global_alpha_en_sel    : 1,	//    17
	osd1_hdr_pixel_order_sel        : 1,	//    18
	osd1_hdr_h_mem_sel              : 1,	//    19
	osd1_hdr_w_mem_sel              : 1,	//    20
	osd1_hdr_ypos_sel               : 1,	//    21
	osd1_hdr_xpos_sel               : 1,	//    22
	osd1_hdr_color_key_en_sel       : 1,	//    23
	osd1_ch_blue                    : 2,	// 24:25
	osd1_ch_green                   : 2,	// 26:27
	osd1_ch_red                     : 2,	// 28:29
	osd1_ch_alpha                   : 2;	// 30:31
} OSD1_L9A0_CFG;

/*-----------------------------------------------------------------------------
	0x1a08 osd2_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_en                         : 1,	//     0
	osd2_double_h                   : 1,	//     1
	osd2_double_w                   : 1,	//     2
	osd2_manual_address             : 1,	//     3
	osd2_round                      : 3,	//  4: 6
	osd2_pure_ck                    : 1,	//     7
	osd2_hdr_ptr_bmp_sel            : 1,	//     8
	osd2_hdr_ptr_plte_sel           : 1,	//     9
	osd2_hdr_color_key_sel          : 1,	//    10
	osd2_hdr_wpl_sel                : 1,	//    11
	osd2_hdr_global_alpha_sel       : 1,	//    12
	osd2_hdr_format_sel             : 1,	//    13
	osd2_hdr_depth_sel              : 1,	//    14
	osd2_hdr_h_out_sel              : 1,	//    15
	osd2_hdr_w_out_sel              : 1,	//    16
	osd2_hdr_global_alpha_en_sel    : 1,	//    17
	osd2_hdr_pixel_order_sel        : 1,	//    18
	osd2_hdr_h_mem_sel              : 1,	//    19
	osd2_hdr_w_mem_sel              : 1,	//    20
	osd2_hdr_ypos_sel               : 1,	//    21
	osd2_hdr_xpos_sel               : 1,	//    22
	osd2_hdr_color_key_en_sel       : 1,	//    23
	osd2_ch_blue                    : 2,	// 24:25
	osd2_ch_green                   : 2,	// 26:27
	osd2_ch_red                     : 2,	// 28:29
	osd2_ch_alpha                   : 2;	// 30:31
} OSD2_L9A0_CFG;

/*-----------------------------------------------------------------------------
	0x1a0c osd_version_date ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x1a10 osd_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	disp_h                          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	disp_w                          :12;	// 16:27
} OSD_L9A0_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x1a14 osd_irq ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_irq                        : 1,	//     0
	osd2_irq                        : 1,	//     1
	osd1_irq                        : 1,	//     2
	osd0_irq                        : 1,	//     3
	mixer_irq                       : 1,	//     4
	                                :11,	//  5:15 reserved
	crsr_irq_en                     : 1,	//    16
	osd2_irq_en                     : 1,	//    17
	osd1_irq_en                     : 1,	//    18
	osd0_irq_en                     : 1,	//    19
	mixer_irq_en                    : 1;	//    20
} OSD_L9A0_IRQ;

/*-----------------------------------------------------------------------------
	0x1a18 osd0_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_base_addr                  ;   	// 31: 0
} OSD0_L9A0_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x1a1c osd0_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_hdr_color_key_en           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd0_hdr_xpos                   :11,	// 16:26
	                                : 4,	// 27:30 reserved
	osd0_hdr_ypos                   : 1;	//    31
} OSD0_L9A0_HDR0;

/*-----------------------------------------------------------------------------
	0x1a20 osd0_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_hdr_h_mem                  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd0_hdr_w_mem                  :12;	// 16:27
} OSD0_L9A0_HDR1;

/*-----------------------------------------------------------------------------
	0x1a24 osd0_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_hdr_h_out                  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd0_hdr_w_out                  :11,	// 16:26
	                                : 4,	// 27:30 reserved
	osd0_hdr_pixel_order            : 1;	//    31
} OSD0_L9A0_HDR2;

/*-----------------------------------------------------------------------------
	0x1a28 osd0_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_hdr_wpl                    :16,	//  0:15
	osd0_hdr_global_alpha           : 8,	// 16:23
	osd0_hdr_format                 : 4,	// 24:27
	osd0_hdr_depth                  : 3,	// 28:30
	osd0_hdr_global_alpha_en        : 1;	//    31
} OSD0_L9A0_HDR3;

/*-----------------------------------------------------------------------------
	0x1a2c osd0_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_hdr_color_key              ;   	// 31: 0
} OSD0_L9A0_HDR4;

/*-----------------------------------------------------------------------------
	0x1a30 osd0_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_hdr_ptr_plte               ;   	// 31: 0
} OSD0_L9A0_HDR5;

/*-----------------------------------------------------------------------------
	0x1a34 osd0_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_hdr_ptr_bmp                ;   	// 31: 0
} OSD0_L9A0_HDR6;

/*-----------------------------------------------------------------------------
	0x1a38 osd0_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_lfsr_seed                  :19;	//  0:18
} OSD0_L9A0_LFSR_SEED;

/*-----------------------------------------------------------------------------
	0x1a3c osd1_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_base_addr                  ;   	// 31: 0
} OSD1_L9A0_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x1a40 osd1_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_hdr_color_key_en           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd1_hdr_xpos                   :11,	// 16:26
	                                : 4,	// 27:30 reserved
	osd1_hdr_ypos                   : 1;	//    31
} OSD1_L9A0_HDR0;

/*-----------------------------------------------------------------------------
	0x1a44 osd1_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_hdr_h_mem                  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd1_hdr_w_mem                  :12;	// 16:27
} OSD1_L9A0_HDR1;

/*-----------------------------------------------------------------------------
	0x1a48 osd1_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_hdr_h_out                  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd1_hdr_w_out                  :11,	// 16:26
	                                : 4,	// 27:30 reserved
	osd1_hdr_pixel_order            : 1;	//    31
} OSD1_L9A0_HDR2;

/*-----------------------------------------------------------------------------
	0x1a4c osd1_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_hdr_wpl                    :16,	//  0:15
	osd1_hdr_global_alpha           : 8,	// 16:23
	osd1_hdr_format                 : 4,	// 24:27
	osd1_hdr_depth                  : 3,	// 28:30
	osd1_hdr_global_alpha_en        : 1;	//    31
} OSD1_L9A0_HDR3;

/*-----------------------------------------------------------------------------
	0x1a50 osd1_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_hdr_color_key              ;   	// 31: 0
} OSD1_L9A0_HDR4;

/*-----------------------------------------------------------------------------
	0x1a54 osd1_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_hdr_ptr_plte               ;   	// 31: 0
} OSD1_L9A0_HDR5;

/*-----------------------------------------------------------------------------
	0x1a58 osd1_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_hdr_ptr_bmp                ;   	// 31: 0
} OSD1_L9A0_HDR6;

/*-----------------------------------------------------------------------------
	0x1a5c osd1_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_lfsr_seed                  :19;	//  0:18
} OSD1_L9A0_LFSR_SEED;

/*-----------------------------------------------------------------------------
	0x1a60 osd2_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_base_addr                  ;   	// 31: 0
} OSD2_L9A0_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x1a64 osd2_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_hdr_color_key_en           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd2_hdr_xpos                   :11,	// 16:26
	                                : 4,	// 27:30 reserved
	osd2_hdr_ypos                   : 1;	//    31
} OSD2_L9A0_HDR0;

/*-----------------------------------------------------------------------------
	0x1a68 osd2_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_hdr_h_mem                  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd2_hdr_w_mem                  :12;	// 16:27
} OSD2_L9A0_HDR1;

/*-----------------------------------------------------------------------------
	0x1a6c osd2_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_hdr_h_out                  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd2_hdr_w_out                  :11,	// 16:26
	                                : 4,	// 27:30 reserved
	osd2_hdr_pixel_order            : 1;	//    31
} OSD2_L9A0_HDR2;

/*-----------------------------------------------------------------------------
	0x1a70 osd2_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_hdr_wpl                    :16,	//  0:15
	osd2_hdr_global_alpha           : 8,	// 16:23
	osd2_hdr_format                 : 4,	// 24:27
	osd2_hdr_depth                  : 3,	// 28:30
	osd2_hdr_global_alpha_en        : 1;	//    31
} OSD2_L9A0_HDR3;

/*-----------------------------------------------------------------------------
	0x1a74 osd2_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_hdr_color_key              ;   	// 31: 0
} OSD2_L9A0_HDR4;

/*-----------------------------------------------------------------------------
	0x1a78 osd2_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_hdr_ptr_plte               ;   	// 31: 0
} OSD2_L9A0_HDR5;

/*-----------------------------------------------------------------------------
	0x1a7c osd2_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_hdr_ptr_bmp                ;   	// 31: 0
} OSD2_L9A0_HDR6;

/*-----------------------------------------------------------------------------
	0x1a80 osd2_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_lfsr_seed                  :19;	//  0:18
} OSD2_L9A0_LFSR_SEED;

/*-----------------------------------------------------------------------------
	0x1a84 osd0_sc_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_sc_vs_en                   : 1,	//     0
	osd0_sc_hs_en                   : 1,	//     1
	                                : 2,	//  2: 3 reserved
	osd0_sc_bc_sa                   : 3,	//  4: 6
	                                : 1,	//     7 reserved
	osd0_sc_bnd_mode                : 1,	//     8
	                                : 3,	//  9:11 reserved
	osd0_sc_h2v_path                : 1,	//    12
	                                : 3,	// 13:15 reserved
	osd0_sc_h_phase_off             :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd0_sc_buf_mode_en             : 1;	//    31
} OSD0_L9A0_SC_CFG;

/*-----------------------------------------------------------------------------
	0x1a88 osd1_sc_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_sc_vs_en                   : 1,	//     0
	osd1_sc_hs_en                   : 1,	//     1
	                                : 2,	//  2: 3 reserved
	osd1_sc_bc_sa                   : 3,	//  4: 6
	                                : 1,	//     7 reserved
	osd1_sc_bnd_mode                : 1,	//     8
	                                : 3,	//  9:11 reserved
	osd1_sc_h2v_path                : 1,	//    12
	                                : 3,	// 13:15 reserved
	osd1_sc_h_phase_off             :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd1_sc_buf_mode_en             : 1;	//    31
} OSD1_L9A0_SC_CFG;

/*-----------------------------------------------------------------------------
	0x1a8c osd2_sc_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_sc_vs_en                   : 1,	//     0
	osd2_sc_hs_en                   : 1,	//     1
	                                : 2,	//  2: 3 reserved
	osd2_sc_bc_sa                   : 3,	//  4: 6
	                                : 1,	//     7 reserved
	osd2_sc_bnd_mode                : 1,	//     8
	                                : 3,	//  9:11 reserved
	osd2_sc_h2v_path                : 1,	//    12
	                                : 3,	// 13:15 reserved
	osd2_sc_h_phase_off             :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd2_sc_buf_mode_en             : 1;	//    31
} OSD2_L9A0_SC_CFG;

/*-----------------------------------------------------------------------------
	0x1a90 osd_sc_v_phase_off ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sc_v_phase_off              :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_sc_v_phase_off_index        : 2,	// 16:17
	                                :13,	// 18:30 reserved
	osd_sc_v_phase_off_rw           : 1;	//    31
} OSD_L9A0_SC_V_PHASE_OFF;

/*-----------------------------------------------------------------------------
	0x1a94 osd0_csc_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_csc_data                   :11,	//  0:10
	osd0_csc_rw_n                   : 1,	//    11
	                                : 4,	// 12:15 reserved
	osd0_csc_bypass                 : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd0_csc_sel                    : 1,	//    20
	                                : 3,	// 21:23 reserved
	osd0_csc_out_ctrl               : 3,	// 24:26
	                                : 1,	//    27 reserved
	osd0_csc_in_ctrl                : 3;	// 28:30
} OSD0_L9A0_CSC_CTRL;

/*-----------------------------------------------------------------------------
	0x1a98 osd1_csc_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_csc_data                   :11,	//  0:10
	osd1_csc_rw_n                   : 1,	//    11
	                                : 4,	// 12:15 reserved
	osd1_csc_bypass                 : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd1_csc_sel                    : 1,	//    20
	                                : 3,	// 21:23 reserved
	osd1_csc_out_ctrl               : 3,	// 24:26
	                                : 1,	//    27 reserved
	osd1_csc_in_ctrl                : 3;	// 28:30
} OSD1_L9A0_CSC_CTRL;

/*-----------------------------------------------------------------------------
	0x1a9c osd2_csc_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_csc_data                   :11,	//  0:10
	osd2_csc_rw_n                   : 1,	//    11
	                                : 4,	// 12:15 reserved
	osd2_csc_bypass                 : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd2_csc_sel                    : 1,	//    20
	                                : 3,	// 21:23 reserved
	osd2_csc_out_ctrl               : 3,	// 24:26
	                                : 1,	//    27 reserved
	osd2_csc_in_ctrl                : 3;	// 28:30
} OSD2_L9A0_CSC_CTRL;

/*-----------------------------------------------------------------------------
	0x1aa4 osd0_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_bbs                        : 1,	//     0
	osd0_bqws                       : 1,	//     1
	osd0_bhws                       : 1,	//     2
	                                : 1,	//     3 reserved
	osd0_pbs                        : 1,	//     4
	osd0_pqws                       : 1,	//     5
	osd0_phws                       : 1,	//     6
	                                : 1,	//     7 reserved
	osd0_hbs                        : 1,	//     8
	osd0_hqws                       : 1,	//     9
	osd0_hhws                       : 1;	//    10
} OSD0_L9A0_END_CONV;

/*-----------------------------------------------------------------------------
	0x1aa8 osd1_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_bbs                        : 1,	//     0
	osd1_bqws                       : 1,	//     1
	osd1_bhws                       : 1,	//     2
	                                : 1,	//     3 reserved
	osd1_pbs                        : 1,	//     4
	osd1_pqws                       : 1,	//     5
	osd1_phws                       : 1,	//     6
	                                : 1,	//     7 reserved
	osd1_hbs                        : 1,	//     8
	osd1_hqws                       : 1,	//     9
	osd1_hhws                       : 1;	//    10
} OSD1_L9A0_END_CONV;

/*-----------------------------------------------------------------------------
	0x1aac osd2_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_bbs                        : 1,	//     0
	osd2_bqws                       : 1,	//     1
	osd2_bhws                       : 1,	//     2
	                                : 1,	//     3 reserved
	osd2_pbs                        : 1,	//     4
	osd2_pqws                       : 1,	//     5
	osd2_phws                       : 1,	//     6
	                                : 1,	//     7 reserved
	osd2_hbs                        : 1,	//     8
	osd2_hqws                       : 1,	//     9
	osd2_hhws                       : 1;	//    10
} OSD2_L9A0_END_CONV;

/*-----------------------------------------------------------------------------
	0x1ab4 crsr_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_en                         : 1,	//     0
	crsr_double_h                   : 1,	//     1
	crsr_double_w                   : 1,	//     2
	crsr_manual_address             : 1,	//     3
	crsr_round                      : 3,	//  4: 6
	crsr_pure_color_key             : 1,	//     7
	crsr_hdr_ptr_bmp_sel            : 1,	//     8
	crsr_hdr_ptr_plte_sel           : 1,	//     9
	crsr_hdr_color_key_sel          : 1,	//    10
	crsr_hdr_wpl_sel                : 1,	//    11
	crsr_hdr_global_alpha_sel       : 1,	//    12
	crsr_hdr_format_sel             : 1,	//    13
	crsr_hdr_depth_sel              : 1,	//    14
	                                : 2,	// 15:16 reserved
	crsr_hdr_global_alpha_en_sel    : 1,	//    17
	crsr_hdr_pixel_order_sel        : 1,	//    18
	crsr_hdr_h_mem_sel              : 1,	//    19
	crsr_hdr_w_mem_sel              : 1,	//    20
	crsr_hdr_ypos_sel               : 1,	//    21
	crsr_hdr_xpos_sel               : 1,	//    22
	crsr_hdr_color_key_en_sel       : 1,	//    23
	crsr_ch_blue                    : 2,	// 24:25
	crsr_ch_green                   : 2,	// 26:27
	crsr_ch_red                     : 2,	// 28:29
	crsr_ch_alpha                   : 2;	// 30:31
} CRSR_L9A0_CFG;

/*-----------------------------------------------------------------------------
	0x1ab8 crsr_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_base_addr                  ;   	// 31: 0
} CRSR_L9A0_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x1abc crsr_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_hdr_ypos                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	crsr_hdr_xpos                   :11,	// 16:26
	                                : 4,	// 27:30 reserved
	crsr_hdr_pos_load               : 1;	//    31
} CRSR_L9A0_HDR0;

/*-----------------------------------------------------------------------------
	0x1ac0 crsr_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_hdr_h_mem                  :12,	//  0:11
	                                : 3,	// 12:14 reserved
	crsr_hdr_pixel_order            : 1,	//    15
	crsr_hdr_w_mem                  :12,	// 16:27
	                                : 3,	// 28:30 reserved
	crsr_hdr_color_key_en           : 1;	//    31
} CRSR_L9A0_HDR1;

/*-----------------------------------------------------------------------------
	0x1ac4 crsr_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_hdr_wpl                    :16,	//  0:15
	crsr_hdr_global_alpha           : 8,	// 16:23
	crsr_hdr_format                 : 4,	// 24:27
	crsr_hdr_depth                  : 3,	// 28:30
	crsr_hdr_global_alpha_en        : 1;	//    31
} CRSR_L9A0_HDR2;

/*-----------------------------------------------------------------------------
	0x1ac8 crsr_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_hdr_color_key              ;   	// 31: 0
} CRSR_L9A0_HDR3;

/*-----------------------------------------------------------------------------
	0x1acc crsr_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_hdr_ptr_plte               ;   	// 31: 0
} CRSR_L9A0_HDR4;

/*-----------------------------------------------------------------------------
	0x1ad0 crsr_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_hdr_ptr_bmp                ;   	// 31: 0
} CRSR_L9A0_HDR5;

/*-----------------------------------------------------------------------------
	0x1ad4 crsr_end_conv ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_bbs                        : 1,	//     0
	crsr_bqws                       : 1,	//     1
	crsr_bhws                       : 1,	//     2
	                                : 1,	//     3 reserved
	crsr_pbs                        : 1,	//     4
	crsr_pqws                       : 1,	//     5
	crsr_phws                       : 1,	//     6
	                                : 1,	//     7 reserved
	crsr_hbs                        : 1,	//     8
	crsr_hqws                       : 1,	//     9
	crsr_hhws                       : 1;	//    10
} CRSR_L9A0_END_CONV;

/*-----------------------------------------------------------------------------
	0x1ad8 crsr_lfsr_seed ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_lfsr_seed                  :19;	//  0:18
} CRSR_L9A0_LFSR_SEED;

typedef struct {
	UINT32
	reg_osd_scaler_mux				: 2;	//  0:1
} OSD_L9A0_SCALER_MUX;

/*-----------------------------------------------------------------------------
	0x1af0 osd_layer_mux_left ''

	@note layer_mux_3 is top most and layer_mux_0 is bottom in zorder.
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	layer_mux_3                     : 2,	//  0: 1
	                                : 2,	//  2: 3 reserved
	layer_mux_2                     : 2,	//  4: 5
	                                : 2,	//  6: 7 reserved
	layer_mux_1                     : 2,	//  8: 9
	                                : 2,	// 10:11 reserved
	layer_mux_0                     : 2,	// 12:13
	                                : 2,	// 14:15 reserved
	video_layer_alpha               : 8;	// 16:23
} OSD_L9A0_LAYER_MUX_LEFT;

/*-----------------------------------------------------------------------------
	0x1af4 osd_layer_mux_right ''

	@note layer_mux_3 is top most and layer_mux_0 is bottom in zorder.
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	layer_mux_3                     : 2,	//  0: 1
	                                : 2,	//  2: 3 reserved
	layer_mux_2                     : 2,	//  4: 5
	                                : 2,	//  6: 7 reserved
	layer_mux_1                     : 2,	//  8: 9
	                                : 2,	// 10:11 reserved
	layer_mux_0                     : 2,	// 12:13
	                                : 2,	// 14:15 reserved
	video_layer_alpha               : 8;	// 16:23
} OSD_L9A0_LAYER_MUX_RIGHT;

/*-----------------------------------------------------------------------------
	0x1af8 osd_mixer_out_left ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mixer_out_blue                  :10,	//  0: 9
	mixer_out_green                 :10,	// 10:19
	mixer_out_red                   :10,	// 20:29
	mixer_mask_en                   : 1,	//    30
	mixer_out_en                    : 1;	//    31
} OSD_L9A0_MIXER_OUT_LEFT;

/*-----------------------------------------------------------------------------
	0x1afc osd_mixer_out_right ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mixer_out_blue                  :10,	//  0: 9
	mixer_out_green                 :10,	// 10:19
	mixer_out_red                   :10,	// 20:29
	mixer_mask_en                   : 1,	//    30
	mixer_out_en                    : 1;	//    31
} OSD_L9A0_MIXER_OUT_RIGHT;

/*-----------------------------------------------------------------------------
	0x1b00 osd0_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_path_sel                   : 2,	//  0: 1
	                                : 2,	//  2: 3 reserved
	osd0_path_buf_half              : 1,	//     4
	osd0_path_buf_repeat            : 1,	//     5
	                                :10,	//  6:15 reserved
	osd0_3d_en                      : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd0_3d_mode_sel                : 1;	//    20
} OSD0_L9A0_3D_PATH_MODE;

/*-----------------------------------------------------------------------------
	0x1b04 osd0_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_right_disparity_value         : 8,	//  0: 7
	osd0_right_disparity_sign          : 1,	//     8
	                                : 7,	//  9:15 reserved
	osd0_left_disparity_value         : 8,	// 16:23
	osd0_left_disparity_sign          : 1;	//    24
} OSD0_L9A0_3D_DISPARITY;

/*-----------------------------------------------------------------------------
	0x1b08 osd0_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_left_3d_blank              ;   	// 31: 0
} OSD0_L9A0_LEFT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b0c osd0_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_right_3d_blank             ;   	// 31: 0
} OSD0_L9A0_RIGHT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b10 osd0_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_tb_line_space	            :11;	//  0:11
} OSD0_L9A0_TB_SPACE;

/*-----------------------------------------------------------------------------
	0x1b20 osd1_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_path_sel                   : 2,	//  0: 1
	                                : 2,	//  2: 3 reserved
	osd1_path_buf_half              : 1,	//     4
	osd1_path_buf_repeat            : 1,	//     5
	                                :10,	//  6:15 reserved
	osd1_3d_en                      : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd1_3d_mode_sel                : 1;	//    20
} OSD1_L9A0_3D_PATH_MODE;

/*-----------------------------------------------------------------------------
	0x1b24 osd1_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_right_disparity_value      : 8,	//  0: 7
	osd1_right_disparity_sign       : 1,	//     8
	                                : 7,	//  9:15 reserved
	osd1_left_disparity_value       : 8,	// 16:23
	osd1_left_disparity_sign        : 1;	//    24
} OSD1_L9A0_3D_DISPARITY;

/*-----------------------------------------------------------------------------
	0x1b28 osd1_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_left_3d_blank              ;   	// 31: 0
} OSD1_L9A0_LEFT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b2c osd1_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_right_3d_blank             ;   	// 31: 0
} OSD1_L9A0_RIGHT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b30 osd1_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd1_tb_line_space	            :11;	//  0:11
} OSD1_L9A0_TB_SPACE;

/*-----------------------------------------------------------------------------
	0x1b40 osd2_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_path_sel                   : 2,	//  0: 1
	                                : 2,	//  2: 3 reserved
	osd2_path_buf_half              : 1,	//     4
	osd2_path_buf_repeat            : 1,	//     5
	                                :10,	//  6:15 reserved
	osd2_3d_en                      : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd2_3d_mode_sel                : 1;	//    20
} OSD2_L9A0_3D_PATH_MODE;

/*-----------------------------------------------------------------------------
	0x1b44 osd2_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_right_disparity_value      : 8,	//  0: 7
	osd2_right_disparity_sign       : 1,	//     8
	                                : 7,	//  9:15 reserved
	osd2_left_disparity_value       : 8,	// 16:23
	osd2_left_disparity_sign        : 1;	//    24
} OSD2_L9A0_3D_DISPARITY;

/*-----------------------------------------------------------------------------
	0x1b48 osd2_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_left_3d_blank              ;   	// 31: 0
} OSD2_L9A0_LEFT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b4c osd2_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_right_3d_blank             ;   	// 31: 0
} OSD2_L9A0_RIGHT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b50 osd2_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd2_tb_line_space	            :11;	//  0:11
} OSD2_L9A0_TB_SPACE;

/*-----------------------------------------------------------------------------
	0x1b60 crsr_3d_path_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_path_sel                   : 2,	//  0: 1
	                                : 2,	//  2: 3 reserved
	crsr_path_buf_half              : 1,	//     4
	crsr_path_buf_repeat            : 1,	//     5
	                                :10,	//  6:15 reserved
	crsr_3d_en                      : 1,	//    16
	                                : 3,	// 17:19 reserved
	crsr_3d_mode_sel                : 1;	//    20
} CRSR_L9A0_3D_PATH_MODE;

/*-----------------------------------------------------------------------------
	0x1b64 crsr_3d_disparity ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_right_disparity_value      : 8,	//  0: 7
	crsr_right_disparity_sign       : 1,	//     8
	                                : 7,	//  9:15 reserved
	crsr_left_disparity_value       : 8,	// 16:23
	crsr_left_disparity_sign        : 1;	//    24
} CRSR_L9A0_3D_DISPARITY;

/*-----------------------------------------------------------------------------
	0x1b68 crsr_left_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_left_3d_blank              ;   	// 31: 0
} CRSR_L9A0_LEFT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b6c crsr_right_3d_blank ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_right_3d_blank             ;   	// 31: 0
} CRSR_L9A0_RIGHT_3D_BLANK;

/*-----------------------------------------------------------------------------
	0x1b70 crsr_tb_space ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_tb_line_space	            :11;	//  0:11
} CRSR_L9A0_TB_SPACE;

/*-----------------------------------------------------------------------------
	0x1b80 reserved0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved0                       :16;	// 16:31
} RESERVED0;

/*-----------------------------------------------------------------------------
	0x1b84 reserved1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved1                       :16;	// 16:31
} RESERVED1;

/*-----------------------------------------------------------------------------
	0x1b88 reserved2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved2                       :16;	// 16:31
} RESERVED2;

/*-----------------------------------------------------------------------------
	0x1b8c reserved3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved3                       :16;	// 16:31
} RESERVED3;

/*-----------------------------------------------------------------------------
	0x1b90 reserved4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved4                       :16;	// 16:31
} RESERVED4;

/*-----------------------------------------------------------------------------
	0x1b94 reserved5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved5                       :16;	// 16:31
} RESERVED5;

/*-----------------------------------------------------------------------------
	0x1b98 reserved6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved6                       :16;	// 16:31
} RESERVED6;

/*-----------------------------------------------------------------------------
	0x1b9c reserved7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reserved7                       :16;	// 16:31
} RESERVED7;

/*-----------------------------------------------------------------------------
	0x1ba0 osd_frc_if_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_if_en					: 1,	//	0: 0 
	                                : 3,	//  0: 3 reserved
	osd_frc_layer_sel               : 2,	//  4: 5
	osd_frc_lr_sel                  : 1,	//     6
	                                : 1,	//     7 reserved
	osd_frc_dither_en               : 3;	//  8:10
} OSD_L9A0_FRC_IF_CFG;

/*-----------------------------------------------------------------------------
	0x1ba4 osd_frc_hdr_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_format              : 4,	//  0: 3
	osd_frc_hdr_po                  : 4,	//  4: 7
	                                : 2,	//  8: 9 reserved
	osd_frc_lr                      : 1,	//    10
	osd_frc_3d                      : 1,	//    11
	                                : 4,	// 12:15 reserved
#if 1
	osd_frc_hdr_frame_number		: 4,	// 16:19
	osd_frc_hdr_prefix				: 4;	// 20:23
#else
	osd_frc_hdr_code                : 8;	// 16:23
#endif
} OSD_L9A0_FRC_HDR_0;

/*-----------------------------------------------------------------------------
	0x1ba8 osd_frc_hdr_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_bmp_height          :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_frc_hdr_bmp_width           :13;	// 16:28
} OSD_L9A0_FRC_HDR_1;

/*-----------------------------------------------------------------------------
	0x1bac osd_frc_hdr_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_global_alpha        : 8,	//  0: 7
	                                : 4,	//  8:11 reserved
	osd_frc_hdr_pe                  : 1,	//    12
	osd_frc_hdr_ge                  : 1,	//    13
	osd_frc_hdr_ce                  : 1,	//    14
	osd_frc_hdr_ou                  : 1;	//    15
} OSD_L9A0_FRC_HDR_2;

/*-----------------------------------------------------------------------------
	0x1bb0 osd_frc_hdr_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_ck_b                : 8,	//  0: 7
	osd_frc_hdr_ck_g                : 8,	//  8:15
	osd_frc_hdr_ck_r                : 8;	// 16:23
} OSD_L9A0_FRC_HDR_3;

/*-----------------------------------------------------------------------------
	0x1bb4 osd_frc_hdr_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_yoffset             :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_frc_hdr_xoffset             :13;	// 16:28
} OSD_L9A0_FRC_HDR_4;

/*-----------------------------------------------------------------------------
	0x1bb8 osd_frc_hdr_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_disp_height         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_frc_hdr_disp_width          :13;	// 16:28
} OSD_L9A0_FRC_HDR_5;

/*-----------------------------------------------------------------------------
	0x1bc0 osd_frc_ablend_th_l ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_external_blend_th_l        : 8,	//  0: 7
	osd2_external_blend_th_l        : 8,	//  8:15
	osd1_external_blend_th_l        : 8,	// 16:23
	osd0_external_blend_th_l        : 8;	// 24:31
} OSD_L9A0_FRC_ABLEND_TH_L;

/*-----------------------------------------------------------------------------
	0x1bc4 osd_frc_ablend_th_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_external_blend_th_r        : 8,	//  0: 7
	osd2_external_blend_th_r        : 8,	//  8:15
	osd1_external_blend_th_r        : 8,	// 24:31
	osd0_external_blend_th_r        : 8;	// 24:31
} OSD_L9A0_FRC_ABLEND_TH_R;

/*-----------------------------------------------------------------------------
	0x1bd0 osd_ddr_addressing ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_layer_sel                   : 2,	//  0: 1
	                                : 2,	//  2: 3 reserved
	op_mode                         : 1,	//     4
	                                : 4,	//  5: 8 reserved
	osd_ddr_sel_bmp                 : 3,	//  9:11
	                                : 5,	// 12:16 reserved
	osd_ddr_sel_plt                 : 3,	// 17:19
	                                : 5,	// 20:24 reserved
	osd_ddr_sel_hdr                 : 3;	// 25:27
} OSD_L9A0_DDR_ADDRESSING;

/*-----------------------------------------------------------------------------
	0x1bd8 osd_left_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_awb_blue                   : 1,	//     0
	crsr_awb_green                  : 1,	//     1
	crsr_awb_red                    : 1,	//     2
	                                : 5,	//  3: 7 reserved
	osd2_awb_blue                   : 1,	//     8
	osd2_awb_green                  : 1,	//     9
	osd2_awb_red                    : 1,	//    10
	                                : 5,	// 11:15 reserved
	osd1_awb_blue                   : 1,	//    16
	osd1_awb_green                  : 1,	//    17
	osd1_awb_red                    : 1,	//    18
	                                : 5,	// 19:23 reserved
	osd0_awb_blue                   : 1,	//    24
	osd0_awb_green                  : 1,	//    25
	osd0_awb_red                    : 1;	//    26
} OSD_L9A0_LEFT_AWB;

/*-----------------------------------------------------------------------------
	0x1bdc osd_right_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crsr_awb_blue                   : 1,	//     0
	crsr_awb_green                  : 1,	//     1
	crsr_awb_red                    : 1,	//     2
	                                : 5,	//  3: 7 reserved
	osd2_awb_blue                   : 1,	//     8
	osd2_awb_green                  : 1,	//     9
	osd2_awb_red                    : 1,	//    10
	                                : 5,	// 11:15 reserved
	osd1_awb_blue                   : 1,	//    16
	osd1_awb_green                  : 1,	//    17
	osd1_awb_red                    : 1,	//    18
	                                : 5,	// 19:23 reserved
	osd0_awb_blue                   : 1,	//    24
	osd0_awb_green                  : 1,	//    25
	osd0_awb_red                    : 1;	//    26
} OSD_L9A0_RIGHT_AWB;

/*-----------------------------------------------------------------------------
	0x1be4 osd_l_mixer_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mixer_process_line_l            :12;	//  0:11
} OSD_L9A0_L_MIXER_STATUS;

/*-----------------------------------------------------------------------------
	0x1be8 osd_r_mixer_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mixer_process_line_r            :12;	//  0:11
} OSD_L9A0_R_MIXER_STATUS;

/*-----------------------------------------------------------------------------
	0x1bec osd_status_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_status_cfg                  : 4;	//  0: 3
} OSD_L9A0_STATUS_CFG;

/*-----------------------------------------------------------------------------
	0x1bf0 osd_status_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	inputed_data0_from_ddr          : 12,  	//  0:12
									: 4,	// reserved
	osd0_process_state              : 3;	// 16:18
} OSD_L9A0_STATUS_0;

/*-----------------------------------------------------------------------------
	0x1bf4 osd_status_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	inputed_data1_from_ddr          : 12,   //  0:120
									: 4,	// reserved
	osd1_process_state              : 3;	// 16:18
} OSD_L9A0_STATUS_1;

/*-----------------------------------------------------------------------------
	0x1bf8 osd_status_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	inputed_data2_from_ddr          : 12, 	//  0:12
									: 4,	// reserved
	osd2_process_state              : 3;	// 16:18
} OSD_L9A0_STATUS_2;

/*-----------------------------------------------------------------------------
	0x1bfc osd_status_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	inputed_data3_from_ddr          : 12,  	//  0:12
									: 4,	// reserved
	crsr_process_state              : 3;	// 16:18
} OSD_L9A0_STATUS_3;

/*-----------------------------------------------------------------------------
	extended ( generated by manual !!! )
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window0_en						:  1,	//  0: 0
									: 15,	//  1:15 reserved
	window0_alpha					:  8;	// 16:23
} OSD_L9A0_L_WINDOW0_CTRL0;

typedef struct {
	UINT32
	window0_y						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window0_x						: 12;	// 16:27
} OSD_L9A0_L_WINDOW0_CTRL1;

typedef struct {
	UINT32
	window0_h						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window0_w						: 12;	// 16:27
} OSD_L9A0_L_WINDOW0_CTRL2;

typedef struct {
	UINT32
	window1_en						:  1,	//  0: 0
									: 15,	//  1:15 reserved
	window1_alpha					:  8;	// 16:23
} OSD_L9A0_L_WINDOW1_CTRL0;

typedef struct {
	UINT32
	window1_y						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window1_x						: 12;	// 16:27
} OSD_L9A0_L_WINDOW1_CTRL1;

typedef struct {
	UINT32
	window1_h						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window1_w						: 12;	// 16:27
} OSD_L9A0_L_WINDOW1_CTRL2;


typedef struct {
	UINT32
	window2_en						:  1,	//  0: 0
									: 15,	//  1:15 reserved
	window2_alpha					:  8;	// 16:23
} OSD_L9A0_L_WINDOW2_CTRL0;

typedef struct {
	UINT32
	window2_y						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window2_x						: 12;	// 16:27
} OSD_L9A0_L_WINDOW2_CTRL1;

typedef struct {
	UINT32
	window2_h						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window2_w						: 12;	// 16:27
} OSD_L9A0_L_WINDOW2_CTRL2;

typedef struct {
	UINT32
	window0_en						:  1,	//  0: 0
									: 15,	//  1:15 reserved
	window0_alpha					:  8;	// 16:23
} OSD_L9A0_R_WINDOW0_CTRL0;

typedef struct {
	UINT32
	window0_y						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window0_x						: 12;	// 16:27
} OSD_L9A0_R_WINDOW0_CTRL1;

typedef struct {
	UINT32
	window0_h						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window0_w						: 12;	// 16:27
} OSD_L9A0_R_WINDOW0_CTRL2;

typedef struct {
	UINT32
	window1_en						:  1,	//  0: 0
									: 15,	//  1:15 reserved
	window1_alpha					:  8;	// 16:23
} OSD_L9A0_R_WINDOW1_CTRL0;

typedef struct {
	UINT32
	window1_y						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window1_x						: 12;	// 16:27
} OSD_L9A0_R_WINDOW1_CTRL1;

typedef struct {
	UINT32
	window1_h						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window1_w						: 12;	// 16:27
} OSD_L9A0_R_WINDOW1_CTRL2;


typedef struct {
	UINT32
	window2_en						:  1,	//  0: 0
									: 15,	//  1:15 reserved
	window2_alpha					:  8;	// 16:23
} OSD_L9A0_R_WINDOW2_CTRL0;

typedef struct {
	UINT32
	window2_y						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window2_x						: 12;	// 16:27
} OSD_L9A0_R_WINDOW2_CTRL1;

typedef struct {
	UINT32
	window2_h						: 12,	//  0:11
									:  4,	// 12:15 reserved
	window2_w						: 12;	// 16:27
} OSD_L9A0_R_WINDOW2_CTRL2;


typedef struct {
	OSD0_L9A0_CFG                        	osd0_cfg                        ;	// 0x1a00 : ''
	OSD1_L9A0_CFG                        	osd1_cfg                        ;	// 0x1a04 : ''
	OSD2_L9A0_CFG                        	osd2_cfg                        ;	// 0x1a08 : ''
	UINT32                          	osd_version_date                ;	// 0x1a0c : ''
	OSD_L9A0_DISP_SIZE                   	osd_disp_size                   ;	// 0x1a10 : ''
	OSD_L9A0_IRQ                         	osd_irq                         ;	// 0x1a14 : ''
	OSD0_L9A0_BASE_ADDR                  	osd0_base_addr                  ;	// 0x1a18 : ''
	OSD0_L9A0_HDR0                       	osd0_hdr0                       ;	// 0x1a1c : ''
	OSD0_L9A0_HDR1                       	osd0_hdr1                       ;	// 0x1a20 : ''
	OSD0_L9A0_HDR2                       	osd0_hdr2                       ;	// 0x1a24 : ''
	OSD0_L9A0_HDR3                       	osd0_hdr3                       ;	// 0x1a28 : ''
	OSD0_L9A0_HDR4                       	osd0_hdr4                       ;	// 0x1a2c : ''
	OSD0_L9A0_HDR5                       	osd0_hdr5                       ;	// 0x1a30 : ''
	OSD0_L9A0_HDR6                       	osd0_hdr6                       ;	// 0x1a34 : ''
	OSD0_L9A0_LFSR_SEED                  	osd0_lfsr_seed                  ;	// 0x1a38 : ''
	OSD1_L9A0_BASE_ADDR                  	osd1_base_addr                  ;	// 0x1a3c : ''
	OSD1_L9A0_HDR0                       	osd1_hdr0                       ;	// 0x1a40 : ''
	OSD1_L9A0_HDR1                       	osd1_hdr1                       ;	// 0x1a44 : ''
	OSD1_L9A0_HDR2                       	osd1_hdr2                       ;	// 0x1a48 : ''
	OSD1_L9A0_HDR3                       	osd1_hdr3                       ;	// 0x1a4c : ''
	OSD1_L9A0_HDR4                       	osd1_hdr4                       ;	// 0x1a50 : ''
	OSD1_L9A0_HDR5                       	osd1_hdr5                       ;	// 0x1a54 : ''
	OSD1_L9A0_HDR6                       	osd1_hdr6                       ;	// 0x1a58 : ''
	OSD1_L9A0_LFSR_SEED                  	osd1_lfsr_seed                  ;	// 0x1a5c : ''
	OSD2_L9A0_BASE_ADDR                  	osd2_base_addr                  ;	// 0x1a60 : ''
	OSD2_L9A0_HDR0                       	osd2_hdr0                       ;	// 0x1a64 : ''
	OSD2_L9A0_HDR1                       	osd2_hdr1                       ;	// 0x1a68 : ''
	OSD2_L9A0_HDR2                       	osd2_hdr2                       ;	// 0x1a6c : ''
	OSD2_L9A0_HDR3                       	osd2_hdr3                       ;	// 0x1a70 : ''
	OSD2_L9A0_HDR4                       	osd2_hdr4                       ;	// 0x1a74 : ''
	OSD2_L9A0_HDR5                       	osd2_hdr5                       ;	// 0x1a78 : ''
	OSD2_L9A0_HDR6                       	osd2_hdr6                       ;	// 0x1a7c : ''
	OSD2_L9A0_LFSR_SEED                  	osd2_lfsr_seed                  ;	// 0x1a80 : ''
	OSD0_L9A0_SC_CFG                     	osd0_sc_cfg                     ;	// 0x1a84 : ''
	OSD1_L9A0_SC_CFG                     	osd1_sc_cfg                     ;	// 0x1a88 : ''
	OSD2_L9A0_SC_CFG                     	osd2_sc_cfg                     ;	// 0x1a8c : ''
	OSD_L9A0_SC_V_PHASE_OFF              	osd_sc_v_phase_off              ;	// 0x1a90 : ''
	OSD0_L9A0_CSC_CTRL                   	osd0_csc_ctrl                   ;	// 0x1a94 : ''
	OSD1_L9A0_CSC_CTRL                   	osd1_csc_ctrl                   ;	// 0x1a98 : ''
	OSD2_L9A0_CSC_CTRL                   	osd2_csc_ctrl                   ;	// 0x1a9c : ''
	UINT32                          	                 __rsvd_00[   1];	// 0x1aa0
	OSD0_L9A0_END_CONV                   	osd0_end_conv                   ;	// 0x1aa4 : ''
	OSD1_L9A0_END_CONV                   	osd1_end_conv                   ;	// 0x1aa8 : ''
	OSD2_L9A0_END_CONV                   	osd2_end_conv                   ;	// 0x1aac : ''
	UINT32                          	                 __rsvd_01[   1];	// 0x1ab0
	CRSR_L9A0_CFG                        	crsr_cfg                        ;	// 0x1ab4 : ''
	CRSR_L9A0_BASE_ADDR                  	crsr_base_addr                  ;	// 0x1ab8 : ''
	CRSR_L9A0_HDR0                       	crsr_hdr0                       ;	// 0x1abc : ''
	CRSR_L9A0_HDR1                       	crsr_hdr1                       ;	// 0x1ac0 : ''
	CRSR_L9A0_HDR2                       	crsr_hdr2                       ;	// 0x1ac4 : ''
	CRSR_L9A0_HDR3                       	crsr_hdr3                       ;	// 0x1ac8 : ''
	CRSR_L9A0_HDR4                       	crsr_hdr4                       ;	// 0x1acc : ''
	CRSR_L9A0_HDR5                       	crsr_hdr5                       ;	// 0x1ad0 : ''
	CRSR_L9A0_END_CONV                   	crsr_end_conv                   ;	// 0x1ad4 : ''
	CRSR_L9A0_LFSR_SEED                  	crsr_lfsr_seed                  ;	// 0x1ad8 : ''
	UINT32                          	                 __rsvd_021[   1]	;	// 0x1adc ~ 0x1aec
	OSD_L9A0_SCALER_MUX						osd_scaler_mux					;
	UINT32												 __rsvd_022[   3]	;
	OSD_L9A0_LAYER_MUX_LEFT              	osd_layer_mux_left              ;	// 0x1af0 : ''
	OSD_L9A0_LAYER_MUX_RIGHT             	osd_layer_mux_right             ;	// 0x1af4 : ''
	OSD_L9A0_MIXER_OUT_LEFT              	osd_mixer_out_left              ;	// 0x1af8 : ''
	OSD_L9A0_MIXER_OUT_RIGHT             	osd_mixer_out_right             ;	// 0x1afc : ''
	OSD0_L9A0_3D_PATH_MODE               	osd0_3d_path_mode               ;	// 0x1b00 : ''
	OSD0_L9A0_3D_DISPARITY               	osd0_3d_disparity               ;	// 0x1b04 : ''
	OSD0_L9A0_LEFT_3D_BLANK              	osd0_left_3d_blank              ;	// 0x1b08 : ''
	OSD0_L9A0_RIGHT_3D_BLANK             	osd0_right_3d_blank             ;	// 0x1b0c : ''
	OSD0_L9A0_TB_SPACE                   	osd0_tb_space                   ;	// 0x1b10 : ''
	UINT32                          	                 __rsvd_03[   3];	// 0x1b14 ~ 0x1b1c
	OSD1_L9A0_3D_PATH_MODE               	osd1_3d_path_mode               ;	// 0x1b20 : ''
	OSD1_L9A0_3D_DISPARITY               	osd1_3d_disparity               ;	// 0x1b24 : ''
	OSD1_L9A0_LEFT_3D_BLANK              	osd1_left_3d_blank              ;	// 0x1b28 : ''
	OSD1_L9A0_RIGHT_3D_BLANK             	osd1_right_3d_blank             ;	// 0x1b2c : ''
	OSD1_L9A0_TB_SPACE                   	osd1_tb_space                   ;	// 0x1b30 : ''
	UINT32                          	                 __rsvd_04[   3];	// 0x1b34 ~ 0x1b3c
	OSD2_L9A0_3D_PATH_MODE               	osd2_3d_path_mode               ;	// 0x1b40 : ''
	OSD2_L9A0_3D_DISPARITY               	osd2_3d_disparity               ;	// 0x1b44 : ''
	OSD2_L9A0_LEFT_3D_BLANK              	osd2_left_3d_blank              ;	// 0x1b48 : ''
	OSD2_L9A0_RIGHT_3D_BLANK             	osd2_right_3d_blank             ;	// 0x1b4c : ''
	OSD2_L9A0_TB_SPACE                   	osd2_tb_space                   ;	// 0x1b50 : ''
	UINT32                          	                 __rsvd_05[   3];	// 0x1b54 ~ 0x1b5c
	CRSR_L9A0_3D_PATH_MODE               	crsr_3d_path_mode               ;	// 0x1b60 : ''
	CRSR_L9A0_3D_DISPARITY               	crsr_3d_disparity               ;	// 0x1b64 : ''
	CRSR_L9A0_LEFT_3D_BLANK              	crsr_left_3d_blank              ;	// 0x1b68 : ''
	CRSR_L9A0_RIGHT_3D_BLANK             	crsr_right_3d_blank             ;	// 0x1b6c : ''
	CRSR_L9A0_TB_SPACE                   	crsr_tb_space                   ;	// 0x1b70 : ''
	UINT32                          	                 __rsvd_06[   3];	// 0x1b74 ~ 0x1b7c
	RESERVED0                       	reserved0                       ;	// 0x1b80 : ''
	RESERVED1                       	reserved1                       ;	// 0x1b84 : ''
	RESERVED2                       	reserved2                       ;	// 0x1b88 : ''
	RESERVED3                       	reserved3                       ;	// 0x1b8c : ''
	RESERVED4                       	reserved4                       ;	// 0x1b90 : ''
	RESERVED5                       	reserved5                       ;	// 0x1b94 : ''
	RESERVED6                       	reserved6                       ;	// 0x1b98 : ''
	RESERVED7                       	reserved7                       ;	// 0x1b9c : ''
	OSD_L9A0_FRC_IF_CFG                  	osd_frc_if_cfg                  ;	// 0x1ba0 : ''
	OSD_L9A0_FRC_HDR_0                   	osd_frc_hdr_0                   ;	// 0x1ba4 : ''
	OSD_L9A0_FRC_HDR_1                   	osd_frc_hdr_1                   ;	// 0x1ba8 : ''
	OSD_L9A0_FRC_HDR_2                   	osd_frc_hdr_2                   ;	// 0x1bac : ''
	OSD_L9A0_FRC_HDR_3                   	osd_frc_hdr_3                   ;	// 0x1bb0 : ''
	OSD_L9A0_FRC_HDR_4                   	osd_frc_hdr_4                   ;	// 0x1bb4 : ''
	OSD_L9A0_FRC_HDR_5                   	osd_frc_hdr_5                   ;	// 0x1bb8 : ''
	UINT32                          	                 __rsvd_07[   1];	// 0x1bbc
	OSD_L9A0_FRC_ABLEND_TH_L             	osd_frc_ablend_th_l             ;	// 0x1bc0 : ''
	OSD_L9A0_FRC_ABLEND_TH_R             	osd_frc_ablend_th_r             ;	// 0x1bc4 : ''
	UINT32                          	                 __rsvd_08[   2];	// 0x1bc8 ~ 0x1bcc
	OSD_L9A0_DDR_ADDRESSING              	osd_ddr_addressing              ;	// 0x1bd0 : ''
	UINT32                          	                 __rsvd_09[   1];	// 0x1bd4
	OSD_L9A0_LEFT_AWB                    	osd_left_awb                    ;	// 0x1bd8 : ''
	OSD_L9A0_RIGHT_AWB                   	osd_right_awb                   ;	// 0x1bdc : ''
	UINT32                          	                 __rsvd_10[   1];	// 0x1be0
	OSD_L9A0_L_MIXER_STATUS              	osd_l_mixer_status              ;	// 0x1be4 : ''
	OSD_L9A0_R_MIXER_STATUS              	osd_r_mixer_status              ;	// 0x1be8 : ''
	OSD_L9A0_STATUS_CFG                  	osd_status_cfg                  ;	// 0x1bec : ''
	OSD_L9A0_STATUS_0                    	osd_status_0                    ;	// 0x1bf0 : ''
	OSD_L9A0_STATUS_1                    	osd_status_1                    ;	// 0x1bf4 : ''
	OSD_L9A0_STATUS_2                    	osd_status_2                    ;	// 0x1bf8 : ''
	OSD_L9A0_STATUS_3                    	osd_status_3                    ;	// 0x1bfc : ''

	/* extended */
	OSD_L9A0_L_WINDOW0_CTRL0				osd_l_window0_ctrl0				;
	OSD_L9A0_L_WINDOW0_CTRL1				osd_l_window0_ctrl1				;
	OSD_L9A0_L_WINDOW0_CTRL2				osd_l_window0_ctrl2				;
	OSD_L9A0_L_WINDOW1_CTRL0				osd_l_window1_ctrl0				;
	OSD_L9A0_L_WINDOW1_CTRL1				osd_l_window1_ctrl1				;
	OSD_L9A0_L_WINDOW1_CTRL2				osd_l_window1_ctrl2				;
	OSD_L9A0_L_WINDOW2_CTRL0				osd_l_window2_ctrl0				;
	OSD_L9A0_L_WINDOW2_CTRL1				osd_l_window2_ctrl1				;
	OSD_L9A0_L_WINDOW2_CTRL2				osd_l_window2_ctrl2				;

	OSD_L9A0_R_WINDOW0_CTRL0				osd_r_window0_ctrl0				;
	OSD_L9A0_R_WINDOW0_CTRL1				osd_r_window0_ctrl1				;
	OSD_L9A0_R_WINDOW0_CTRL2				osd_r_window0_ctrl2				;
	OSD_L9A0_R_WINDOW1_CTRL0				osd_r_window1_ctrl0				;
	OSD_L9A0_R_WINDOW1_CTRL1				osd_r_window1_ctrl1				;
	OSD_L9A0_R_WINDOW1_CTRL2				osd_r_window1_ctrl2				;
	OSD_L9A0_R_WINDOW2_CTRL0				osd_r_window2_ctrl0				;
	OSD_L9A0_R_WINDOW2_CTRL1				osd_r_window2_ctrl1				;
	OSD_L9A0_R_WINDOW2_CTRL2				osd_r_window2_ctrl2				;

} OSD_L9A0_REG_T;
/* 104 regs, 104 types */

/* 104 regs, 104 types in Total*/

/*
 * @{
 * Naming for register pointer.
 * g_fbdev_l9_reg : real register of OSD.
 * gpRegOSD_L9A0     : shadow register.
 *
 * @def OSD_L9A0_RdFL: Read  FLushing : Shadow <- Real.
 * @def OSD_L9A0_WrFL: Write FLushing : Shadow -> Real.
 * @def OSD_L9A0_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def OSD_L9A0_Wr  : Write whole register(UINT32) from Shadow register.
 * @def OSD_L9A0_Rd01 ~ OSD_L9A0_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def OSD_L9A0_Wr01 ~ OSD_L9A0_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define OSD_L9A0_RdFL(_r)			((g_fbdev_l9_reg_cached->_r)=g_fbdev_l9_reg->_r)
#define OSD_L9A0_WrFL(_r)			(g_fbdev_l9_reg->_r)=(g_fbdev_l9_reg_cached->_r)

#define OSD_L9A0_Rd(_r)				*((UINT32*)(&(g_fbdev_l9_reg_cached->_r)))
#define OSD_L9A0_Wr(_r,_v)			((OSD_L9A0_Rd(_r))=((UINT32)(_v)))

#define OSD_L9A0_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
								} while(0)

#define OSD_L9A0_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
								} while(0)

#define OSD_L9A0_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
								} while(0)

#define OSD_L9A0_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
								} while(0)

#define OSD_L9A0_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
								} while(0)

#define OSD_L9A0_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
								} while(0)

#define OSD_L9A0_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
								} while(0)

#define OSD_L9A0_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
								} while(0)

#define OSD_L9A0_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
								} while(0)

#define OSD_L9A0_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
									(_v10) = (g_fbdev_l9_reg_cached->_r._f10);				\
								} while(0)

#define OSD_L9A0_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
									(_v10) = (g_fbdev_l9_reg_cached->_r._f10);				\
									(_v11) = (g_fbdev_l9_reg_cached->_r._f11);				\
								} while(0)

#define OSD_L9A0_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
									(_v10) = (g_fbdev_l9_reg_cached->_r._f10);				\
									(_v11) = (g_fbdev_l9_reg_cached->_r._f11);				\
									(_v12) = (g_fbdev_l9_reg_cached->_r._f12);				\
								} while(0)

#define OSD_L9A0_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
									(_v10) = (g_fbdev_l9_reg_cached->_r._f10);				\
									(_v11) = (g_fbdev_l9_reg_cached->_r._f11);				\
									(_v12) = (g_fbdev_l9_reg_cached->_r._f12);				\
									(_v13) = (g_fbdev_l9_reg_cached->_r._f13);				\
								} while(0)

#define OSD_L9A0_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
									(_v10) = (g_fbdev_l9_reg_cached->_r._f10);				\
									(_v11) = (g_fbdev_l9_reg_cached->_r._f11);				\
									(_v12) = (g_fbdev_l9_reg_cached->_r._f12);				\
									(_v13) = (g_fbdev_l9_reg_cached->_r._f13);				\
									(_v14) = (g_fbdev_l9_reg_cached->_r._f14);				\
								} while(0)

#define OSD_L9A0_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
									(_v10) = (g_fbdev_l9_reg_cached->_r._f10);				\
									(_v11) = (g_fbdev_l9_reg_cached->_r._f11);				\
									(_v12) = (g_fbdev_l9_reg_cached->_r._f12);				\
									(_v13) = (g_fbdev_l9_reg_cached->_r._f13);				\
									(_v14) = (g_fbdev_l9_reg_cached->_r._f14);				\
									(_v15) = (g_fbdev_l9_reg_cached->_r._f15);				\
								} while(0)

#define OSD_L9A0_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (g_fbdev_l9_reg_cached->_r._f01);				\
									(_v02) = (g_fbdev_l9_reg_cached->_r._f02);				\
									(_v03) = (g_fbdev_l9_reg_cached->_r._f03);				\
									(_v04) = (g_fbdev_l9_reg_cached->_r._f04);				\
									(_v05) = (g_fbdev_l9_reg_cached->_r._f05);				\
									(_v06) = (g_fbdev_l9_reg_cached->_r._f06);				\
									(_v07) = (g_fbdev_l9_reg_cached->_r._f07);				\
									(_v08) = (g_fbdev_l9_reg_cached->_r._f08);				\
									(_v09) = (g_fbdev_l9_reg_cached->_r._f09);				\
									(_v10) = (g_fbdev_l9_reg_cached->_r._f10);				\
									(_v11) = (g_fbdev_l9_reg_cached->_r._f11);				\
									(_v12) = (g_fbdev_l9_reg_cached->_r._f12);				\
									(_v13) = (g_fbdev_l9_reg_cached->_r._f13);				\
									(_v14) = (g_fbdev_l9_reg_cached->_r._f14);				\
									(_v15) = (g_fbdev_l9_reg_cached->_r._f15);				\
									(_v16) = (g_fbdev_l9_reg_cached->_r._f16);				\
								} while(0)


#define OSD_L9A0_Wr01(_r,_f01,_v01)													\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
								} while(0)

#define OSD_L9A0_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
								} while(0)

#define OSD_L9A0_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
								} while(0)

#define OSD_L9A0_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
								} while(0)

#define OSD_L9A0_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
								} while(0)

#define OSD_L9A0_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
								} while(0)

#define OSD_L9A0_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
								} while(0)

#define OSD_L9A0_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
								} while(0)

#define OSD_L9A0_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
								} while(0)

#define OSD_L9A0_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
									(g_fbdev_l9_reg_cached->_r._f10) = (_v10);				\
								} while(0)

#define OSD_L9A0_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
									(g_fbdev_l9_reg_cached->_r._f10) = (_v10);				\
									(g_fbdev_l9_reg_cached->_r._f11) = (_v11);				\
								} while(0)

#define OSD_L9A0_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
									(g_fbdev_l9_reg_cached->_r._f10) = (_v10);				\
									(g_fbdev_l9_reg_cached->_r._f11) = (_v11);				\
									(g_fbdev_l9_reg_cached->_r._f12) = (_v12);				\
								} while(0)

#define OSD_L9A0_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
									(g_fbdev_l9_reg_cached->_r._f10) = (_v10);				\
									(g_fbdev_l9_reg_cached->_r._f11) = (_v11);				\
									(g_fbdev_l9_reg_cached->_r._f12) = (_v12);				\
									(g_fbdev_l9_reg_cached->_r._f13) = (_v13);				\
								} while(0)

#define OSD_L9A0_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
									(g_fbdev_l9_reg_cached->_r._f10) = (_v10);				\
									(g_fbdev_l9_reg_cached->_r._f11) = (_v11);				\
									(g_fbdev_l9_reg_cached->_r._f12) = (_v12);				\
									(g_fbdev_l9_reg_cached->_r._f13) = (_v13);				\
									(g_fbdev_l9_reg_cached->_r._f14) = (_v14);				\
								} while(0)

#define OSD_L9A0_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
									(g_fbdev_l9_reg_cached->_r._f10) = (_v10);				\
									(g_fbdev_l9_reg_cached->_r._f11) = (_v11);				\
									(g_fbdev_l9_reg_cached->_r._f12) = (_v12);				\
									(g_fbdev_l9_reg_cached->_r._f13) = (_v13);				\
									(g_fbdev_l9_reg_cached->_r._f14) = (_v14);				\
									(g_fbdev_l9_reg_cached->_r._f15) = (_v15);				\
								} while(0)

#define OSD_L9A0_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(g_fbdev_l9_reg_cached->_r._f01) = (_v01);				\
									(g_fbdev_l9_reg_cached->_r._f02) = (_v02);				\
									(g_fbdev_l9_reg_cached->_r._f03) = (_v03);				\
									(g_fbdev_l9_reg_cached->_r._f04) = (_v04);				\
									(g_fbdev_l9_reg_cached->_r._f05) = (_v05);				\
									(g_fbdev_l9_reg_cached->_r._f06) = (_v06);				\
									(g_fbdev_l9_reg_cached->_r._f07) = (_v07);				\
									(g_fbdev_l9_reg_cached->_r._f08) = (_v08);				\
									(g_fbdev_l9_reg_cached->_r._f09) = (_v09);				\
									(g_fbdev_l9_reg_cached->_r._f10) = (_v10);				\
									(g_fbdev_l9_reg_cached->_r._f11) = (_v11);				\
									(g_fbdev_l9_reg_cached->_r._f12) = (_v12);				\
									(g_fbdev_l9_reg_cached->_r._f13) = (_v13);				\
									(g_fbdev_l9_reg_cached->_r._f14) = (_v14);				\
									(g_fbdev_l9_reg_cached->_r._f15) = (_v15);				\
									(g_fbdev_l9_reg_cached->_r._f16) = (_v16);				\
								} while(0)

/* Indexed Register Access.
 * 
 * There is in-direct field specified by 'index' field within a register.
 * Normally a register has only one meaning for a 'field_name', but indexed register
 * can hold several data for a 'field_name' specifed by 'index' field of indexed register.
 * When writing an 3rd data for given 'field_name' register, you need to set 'rw' = 0, 'index' = 2,
 * and 'load' = 0.
 * 
 * ASSUMPTION
 * For Writing indexed register load bit 
 * 
 * parameter list
 * _r     : name of register
 * _lname : name of load  bit field	: shall be 0 after macro executed.
 * _rwname: name of rw    bit field : shall be 0 after OSD_L9A0_Wind(), 1 for OSD_L9A0_Rind()
 * _iname : name of index bit field
 * _ival  : index value
 * _fname : field name
 * _fval  : field variable that field value shall be stored.
 *
 * OSD_L9A0_Rind : General indexed register Read.(
 * OSD_L9A0_Wind : General indexed register Read.
 *
 * OSD_L9A0_Ridx : For 'index', 'rw', 'load' field name
 * OSD_L9A0_Widx : For 'index', 'rw', 'load' field name and NO_LOAD.
 */
#define OSD_L9A0_Rind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
							do {												\
								OSD_L9A0_Wr03(_r,_lname,0,_rwname,1,_iname,_ival);	\
								OSD_L9A0_WrFL(_r);									\
								OSD_L9A0_RdFL(_r);									\
								OSD_L9A0_Rd01(_r,_fname,_fval);						\
							} while (0)

#define OSD_L9A0_Wind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
				OSD_L9A0_Wr04(_r, _lname,0, _rwname,0, _iname,_ival, _fname,_fval)


#define OSD_L9A0_Ridx(_r, _ival, _fname, _fval)	OSD_L9A0_Rind(_r,load,rw,index,_ival,_fname,_fval)

#define OSD_L9A0_Widx(_r, _ival, _fname, _fval)	OSD_L9A0_Wind(_r,load,rw,index,_ival,_fname,_fval)

/** @} *//* end of macro documentation */

#ifdef __cplusplus
}
#endif

#endif	/* _FBDEV_L9A0_OSD_REG_H_ */

/* from 'L9_DE_OSD_L9A0_RegFile.csv' 20110317 18:03:54   ´ëÇÑ¹Î±¹ Ç¥ÁØ½Ã by getregs v2.7 */
