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

#ifndef _REG_CVI_L9A0_h
#define _REG_CVI_L9A0_h

typedef struct { // 0x0100
	UINT32 scan_type                       : 1;   //     0
	UINT32 field_gen_mode                  : 2;   //  2: 1
	UINT32 auto_field_gen                  : 2;   //  4: 3
	UINT32 data_bit_mode                   : 1;   //     5
	UINT32 chroma_sampling                 : 1;   //     6
	UINT32 aspect_ratio                    : 1;   //     7
	UINT32 yc_delay_mode_r                 : 2;   //  9: 8
	UINT32 yc_delay_mode_b                 : 2;   // 11:10
	UINT32 yc_delay_mode_g                 : 2;   // 13:12
	UINT32                                 : 5;   // 18:14
	UINT32 auto_sync_polarity              : 1;   //    19
	UINT32 manual_sync_polarity            : 2;   // 21:20
	UINT32 adc_cut_direction               : 1;   //    22
	UINT32 adc_bit_sel                     : 1;   //    23
	UINT32 br_port_swap                    : 1;   //    24
	UINT32 r_port_swap                     : 1;   //    25
	UINT32 b_port_swap                     : 1;   //    26
	UINT32 g_port_swap                     : 1;   //    27
	UINT32 bit_numbering_lsb2              : 3;   // 30:28
	UINT32 data_en_mode                    : 1;   //    31
} L9A0_CVA_TOP_CTRL_T;

typedef struct { // 0x0104
	UINT32 offset_h                        : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 offset_v                        : 12;  // 27:16
} L9A0_CVA_OFFSET_CTRL_T;

typedef struct { // 0x0108
	UINT32 size_h                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 size_v                          : 12;  // 27:16
} L9A0_CVA_SIZE_CTRL_T;

typedef struct { // 0x010c
	UINT32 res_hsync                       : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 res_hfp                         : 10;  // 25:16
} L9A0_CVA_INT_SYNC_CTRL0_T;

typedef struct { // 0x0110
	UINT32 res_vfp                         : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 res_vsync                       : 5;   // 12: 8
	UINT32 res_field_add_line              : 2;   // 14:13
	UINT32 res_field_sel                   : 1;   //    15
	UINT32 res_sync_sel                    : 1;   //    16
} L9A0_CVA_INT_SYNC_CTRL1_T;

typedef struct { // 0x0114
	UINT32 fir_coefficient1                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient0                : 10;  // 25:16
} L9A0_CVA_DIG_FILT_CTRL0_T;

typedef struct { // 0x0118
	UINT32 fir_coefficient3                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient2                : 10;  // 25:16
} L9A0_CVA_DIG_FILT_CTRL1_T;

typedef struct { // 0x011c
	UINT32 fir_coefficient5                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient4                : 10;  // 25:16
} L9A0_CVA_DIG_FILT_CTRL2_T;

typedef struct { // 0x0120
	UINT32 fir_coefficient7                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient6                : 10;  // 25:16
	UINT32 fir_coeff_load                  : 1;   //    26
	UINT32 fir_en                          : 1;   //    27
	UINT32 fir_sample_en                   : 1;   //    28
	UINT32 fir_sampling_rate               : 2;   // 30:29
	UINT32 fir_sample_c                    : 1;   //    31
} L9A0_CVA_DIG_FILT_CTRL3_T;

typedef struct { // 0x0124
	UINT32 csc_coefficient1                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient0                : 15;  // 30:16
} L9A0_CVA_CSC_CTRL0_T;

typedef struct { // 0x0128
	UINT32 csc_coefficient3                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient2                : 15;  // 30:16
} L9A0_CVA_CSC_CTRL1_T;

typedef struct { // 0x012c
	UINT32 csc_coefficient5                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient4                : 15;  // 30:16
} L9A0_CVA_CSC_CTRL2_T;

typedef struct { // 0x0130
	UINT32 csc_coefficient7                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient6                : 15;  // 30:16
} L9A0_CVA_CSC_CTRL3_T;

typedef struct { // 0x0134
	UINT32 csc_offset0                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 csc_coefficient8                : 15;  // 30:16
} L9A0_CVA_CSC_CTRL4_T;

typedef struct { // 0x0138
	UINT32 csc_offset2                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 csc_offset1                     : 11;  // 26:16
} L9A0_CVA_CSC_CTRL5_T;

typedef struct { // 0x013c
	UINT32 csc_offset4                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 csc_offset3                     : 11;  // 26:16
} L9A0_CVA_CSC_CTRL6_T;

typedef struct { // 0x0140
	UINT32 csc_coeff_load                  : 1;   //     0
	UINT32 csc_en                          : 1;   //     1
	UINT32 csc_msb_4b_only_mode            : 1;   //     2
	UINT32                                 : 13;  // 15: 3
	UINT32 csc_offset5                     : 11;  // 26:16
} L9A0_CVA_CSC_CTRL7_T;

typedef struct { // 0x0144
	UINT32 pattern_type                    : 3;   //  2: 0
	UINT32 pattern_csc                     : 1;   //     3
	UINT32 pattern_detail                  : 4;   //  7: 4
	UINT32 update_pulse                    : 1;   //     8
	UINT32 field_fix_mode                  : 2;   // 10: 9
	UINT32 auto_novalid_on                 : 1;   //    11
	UINT32 write_inhibit                   : 1;   //    12
	UINT32 sim_mode                        : 1;   //    13
	UINT32 black_off                       : 1;   //    14
	UINT32 field_edge                      : 1;   //    15
	UINT32 org_hoffset                     : 1;   //    16
	UINT32 org_voffset                     : 1;   //    17
	UINT32                                 : 10;  // 27:18
	UINT32 update_position                 : 4;   // 31:28
} L9A0_CVA_MISC_CTRL_T;

typedef struct { // 0x0148
	UINT32 hoffset_read                    : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 voffset_read                    : 11;  // 26:16
} L9A0_CVA_OFFSET_READ_T;

typedef struct { // 0x014c
	UINT32 sd_vd_range                     : 2;   //  1: 0
	UINT32 sd_ext_range                    : 2;   //  3: 2
	UINT32 intr_mask_node                  : 1;   //     4
	UINT32 intr_mask_nohsync               : 1;   //     5
	UINT32 intrl_mask_novsync              : 1;   //     6
	UINT32 intr_mask_abnormal              : 1;   //     7
	UINT32 intr_mask_invalid               : 1;   //     8
	UINT32 intr_mask_de                    : 1;   //     9
	UINT32 intr_mask_hsync                 : 1;   //    10
	UINT32 intr_mask_vsync                 : 1;   //    11
	UINT32 intr_mask_normal                : 1;   //    12
	UINT32 intr_mask_valid                 : 1;   //    13
	UINT32                                 : 1;   //    14
	UINT32 sd_en                           : 1;   //    15
	UINT32 sd_frame_cnt                    : 3;   // 18:16
	UINT32                                 : 1;   //    19
	UINT32 sd_novald_duration              : 2;   // 21:20
	UINT32                                 : 2;   // 23:22
	UINT32 sd_one_field                    : 1;   //    24
	UINT32 intr_mask_ext_diff              : 1;   //    25
	UINT32 intr_mask_vd_diff               : 1;   //    26
} L9A0_CVA_SIZE_DETECT_CTRL_T;

typedef struct { // 0x0150
	UINT32 line_num_read                   : 16;  // 15: 0
	UINT32 line_width_read                 : 16;  // 31:16
} L9A0_CVA_SIZE_DETECT_READ_T;

typedef struct { // 0x0154
	UINT32 pre3d_sync_enable               : 1;   //     0
	UINT32 pre3d_sync_mode                 : 2;   //  2: 1
	UINT32 pre3d_field_mode                : 1;   //     3
	UINT32 pre3d_frame_lr_mode             : 1;   //     4
	UINT32 pre3d_mid_vsync_bypass          : 1;   //     5
	UINT32 pre3d_field_bypass              : 1;   //     6
	UINT32                                 : 9;   // 15: 7
	UINT32 pre3d_active_line_num           : 12;  // 27:16
} L9A0_CVA_PRE3D_CTRL0_T;

typedef struct { // 0x0158
	UINT32 pre3d_active_space1_line_num    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pre3d_active_space2_line_num    : 12;  // 27:16
} L9A0_CVA_PRE3D_CTRL1_T;

typedef struct { // 0x015c
	UINT32 pre3d_front_porch_line_num      : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pre3d_sync_line_num             : 12;  // 27:16
} L9A0_CVA_PRE3D_CTRL2_T;

typedef struct { // 0x0160
	UINT32 current_line_number_read        : 12;  // 11: 0
	UINT32 de_signal_detect                : 1;   //    12
	UINT32 hsync_signal_detect             : 1;   //    13
	UINT32 vsync_signal_detect             : 1;   //    14
	UINT32 source_valid                    : 1;   //    15
	UINT32 sd_hsync_fault_flag_read        : 1;   //    16
	UINT32 sd_vsync_fault_flag_read        : 1;   //    17
	UINT32 sd_hsync_polarity               : 1;   //    18
	UINT32 sd_vsync_polarity               : 1;   //    19
	UINT32 sd_line_num                     : 12;  // 31:20
} L9A0_CVA_SIZE_STATUS0_T;

typedef struct { // 0x0164
	UINT32 sd_hoffset_indurance_read       : 8;   //  7: 0
	UINT32 sd_voffset_indurance_read       : 8;   // 15: 8
	UINT32 hoffset_over                    : 1;   //    16
	UINT32 v_offset_over                   : 1;   //    17
} L9A0_CVA_SIZE_STATUS1_T;

typedef struct { // 0x0168
	UINT32 de_line_size                    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 de_line_count                   : 12;  // 27:16
} L9A0_CVA_SIZE_STATUS2_T;

typedef struct { // 0x016c
	UINT32 hd_sync_size                    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 hd_line_size                    : 12;  // 27:16
} L9A0_CVA_SIZE_STATUS3_T;

typedef struct { // 0x0170
	UINT32 vd_sync_count                   : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 vd_line_count                   : 12;  // 27:16
} L9A0_CVA_SIZE_STATUS4_T;

typedef struct { // 0x0174
	UINT32 sd_2field_size                  : 24;  // 23: 0
} L9A0_CVA_SIZE_STATUS5_T;

typedef struct { // 0x0178
	UINT32 vsync_pesudo_sel                : 1;   //     0
	UINT32 hsync_pesudo_sel                : 1;   //     1
	UINT32 vactive_pesudo_sel              : 1;   //     2
	UINT32 hactive_pesudo_sel              : 1;   //     3
	UINT32 field_pesudo_sel                : 1;   //     4
} L9A0_CVA_PSEUDO_SYNC_CTRL0_T;

typedef struct { // 0x017c
	UINT32 pseudo_hfp                      : 14;  // 13: 0
	UINT32                                 : 2;   // 15:14
	UINT32 pseudo_hsync                    : 14;  // 29:16
} L9A0_CVA_PSEUDO_SYNC_CTRL1_T;

typedef struct { // 0x0180
	UINT32 pseudo_hblk                     : 14;  // 13: 0
	UINT32                                 : 2;   // 15:14
	UINT32 pseudo_hn                       : 14;  // 29:16
} L9A0_CVA_PSEUDO_SYNC_CTRL2_T;

typedef struct { // 0x0184
	UINT32 pseudo_vfp                      : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pseudo_vsync                    : 12;  // 27:16
} L9A0_CVA_PSEUDO_SYNC_CTRL3_T;

typedef struct { // 0x0188
	UINT32 pseudo_vblk                     : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pseudo_vn                       : 12;  // 27:16
} L9A0_CVA_PSEUDO_SYNC_CTRL4_T;

typedef struct { // 0x018c
	UINT32 hd_pixel_delay                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 vd_line_delay                   : 12;  // 27:16
	UINT32                                 : 3;   // 30:28
	UINT32 pre_sync_ctrl_en                : 1;   //    31
} L9A0_CVA_PRE_SYNC_CTRL_T;

typedef struct { // 0x0190
	UINT32 diff_vd_vcnt                    : 16;  // 15: 0
	UINT32 diff_ext_vcnt                   : 12;  // 27:16
	UINT32                                 : 3;   // 30:28
	UINT32 vd_intr                         : 1;   //    31
} L9A0_CVA_SIZE_STATUS6_T;

typedef struct { // 0x0194
	UINT32 start_pos_x                     : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 end_pos_x                       : 12;  // 27:16
	UINT32 pix_sum_enable                  : 1;   //    28
	UINT32 field_selection                 : 2;   // 30:29
	UINT32 debug_enable                    : 1;   //    31
} L9A0_CVA_PIX_SUM_CTRL0_T;

typedef struct { // 0x0198
	UINT32 start_pos_y                     : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 end_pos_y                       : 12;  // 27:16
} L9A0_CVA_PIX_SUM_CTRL1_T;

typedef struct { // 0x019c
	UINT32 pix_sum_g                       : 32;  // 31: 0
} L9A0_CVA_PIX_SUM_STATUS0_T;

typedef struct { // 0x01a0
	UINT32 pix_sum_b                       : 32;  // 31: 0
} L9A0_CVA_PIX_SUM_STATUS1_T;

typedef struct { // 0x01a4
	UINT32 pix_sum_r                       : 32;  // 31: 0
} L9A0_CVA_PIX_SUM_STATUS2_T;

typedef struct { // 0x01a8
	UINT32 line_count_sel                  : 12;  // 11: 0
} L9A0_CVA_DE_COUNT_SEL_T;

typedef struct { // 0x01ac
	UINT32 minus_blank_hsize               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 minus_blank_vsize               : 12;  // 27:16
} L9A0_CVA_MINUS_BLANK_SIZE_T;

typedef struct { // 0x0200
	UINT32 scan_type                       : 1;   //     0
	UINT32 field_gen_mode                  : 2;   //  2: 1
	UINT32 auto_field_gen                  : 2;   //  4: 3
	UINT32 data_bit_mode                   : 1;   //     5
	UINT32 chroma_sampling                 : 1;   //     6
	UINT32 aspect_ratio                    : 1;   //     7
	UINT32 yc_delay_mode_r                 : 2;   //  9: 8
	UINT32 yc_delay_mode_b                 : 2;   // 11:10
	UINT32 yc_delay_mode_g                 : 2;   // 13:12
	UINT32                                 : 5;   // 18:14
	UINT32 auto_sync_polarity              : 1;   //    19
	UINT32 manual_sync_polarity            : 2;   // 21:20
	UINT32 adc_cut_direction               : 1;   //    22
	UINT32 adc_bit_sel                     : 1;   //    23
	UINT32 br_port_swap                    : 1;   //    24
	UINT32 r_port_swap                     : 1;   //    25
	UINT32 b_port_swap                     : 1;   //    26
	UINT32 g_port_swap                     : 1;   //    27
	UINT32 bit_numbering_lsb2              : 3;   // 30:28
	UINT32 data_en_mode                    : 1;   //    31
} L9A0_CVB_TOP_CTRL_T;

typedef struct { // 0x0204
	UINT32 offset_h                        : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 offset_v                        : 12;  // 27:16
} L9A0_CVB_OFFSET_CTRL_T;

typedef struct { // 0x0208
	UINT32 size_h                          : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 size_v                          : 12;  // 27:16
} L9A0_CVB_SIZE_CTRL_T;

typedef struct { // 0x020c
	UINT32 res_hsync                       : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 res_hfp                         : 10;  // 25:16
} L9A0_CVB_INT_SYNC_CTRL0_T;

typedef struct { // 0x0210
	UINT32 res_vfp                         : 5;   //  4: 0
	UINT32                                 : 3;   //  7: 5
	UINT32 res_vsync                       : 5;   // 12: 8
	UINT32 res_field_add_line              : 2;   // 14:13
	UINT32 res_field_sel                   : 1;   //    15
	UINT32 res_sync_sel                    : 1;   //    16
} L9A0_CVB_INT_SYNC_CTRL1_T;

typedef struct { // 0x0214
	UINT32 fir_coefficient1                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient0                : 10;  // 25:16
} L9A0_CVB_DIG_FILT_CTRL0_T;

typedef struct { // 0x0218
	UINT32 fir_coefficient3                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient2                : 10;  // 25:16
} L9A0_CVB_DIG_FILT_CTRL1_T;

typedef struct { // 0x021c
	UINT32 fir_coefficient5                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient4                : 10;  // 25:16
} L9A0_CVB_DIG_FILT_CTRL2_T;

typedef struct { // 0x0220
	UINT32 fir_coefficient7                : 10;  //  9: 0
	UINT32                                 : 6;   // 15:10
	UINT32 fir_coefficient6                : 10;  // 25:16
	UINT32 fir_coeff_load                  : 1;   //    26
	UINT32 fir_en                          : 1;   //    27
	UINT32 fir_sample_en                   : 1;   //    28
	UINT32 fir_sampling_rate               : 2;   // 30:29
	UINT32 fir_sample_c                    : 1;   //    31
} L9A0_CVB_DIG_FILT_CTRL3_T;

typedef struct { // 0x0224
	UINT32 csc_coefficient1                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient0                : 15;  // 30:16
} L9A0_CVB_CSC_CTRL0_T;

typedef struct { // 0x0228
	UINT32 csc_coefficient3                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient2                : 15;  // 30:16
} L9A0_CVB_CSC_CTRL1_T;

typedef struct { // 0x022c
	UINT32 csc_coefficient5                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient4                : 15;  // 30:16
} L9A0_CVB_CSC_CTRL2_T;

typedef struct { // 0x0230
	UINT32 csc_coefficient7                : 15;  // 14: 0
	UINT32                                 : 1;   //    15
	UINT32 csc_coefficient6                : 15;  // 30:16
} L9A0_CVB_CSC_CTRL3_T;

typedef struct { // 0x0234
	UINT32 csc_offset0                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 csc_coefficient8                : 15;  // 30:16
} L9A0_CVB_CSC_CTRL4_T;

typedef struct { // 0x0238
	UINT32 csc_offset2                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 csc_offset1                     : 11;  // 26:16
} L9A0_CVB_CSC_CTRL5_T;

typedef struct { // 0x023c
	UINT32 csc_offset4                     : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 csc_offset3                     : 11;  // 26:16
} L9A0_CVB_CSC_CTRL6_T;

typedef struct { // 0x0240
	UINT32 csc_coeff_load                  : 1;   //     0
	UINT32 csc_en                          : 1;   //     1
	UINT32 csc_msb_4b_only_mode            : 1;   //     2
	UINT32                                 : 13;  // 15: 3
	UINT32 csc_offset5                     : 11;  // 26:16
} L9A0_CVB_CSC_CTRL7_T;

typedef struct { // 0x0244
	UINT32 pattern_type                    : 3;   //  2: 0
	UINT32 pattern_csc                     : 1;   //     3
	UINT32 pattern_detail                  : 4;   //  7: 4
	UINT32 update_pulse                    : 1;   //     8
	UINT32 field_fix_mode                  : 2;   // 10: 9
	UINT32 auto_novalid_on                 : 1;   //    11
	UINT32 write_inhibit                   : 1;   //    12
	UINT32 sim_mode                        : 1;   //    13
	UINT32 black_off                       : 1;   //    14
	UINT32 field_edge                      : 1;   //    15
	UINT32 org_hoffset                     : 1;   //    16
	UINT32 org_voffset                     : 1;   //    17
	UINT32                                 : 10;  // 27:18
	UINT32 update_position                 : 4;   // 31:28
} L9A0_CVB_MISC_CTRL_T;

typedef struct { // 0x0248
	UINT32 hoffset_read                    : 11;  // 10: 0
	UINT32                                 : 5;   // 15:11
	UINT32 voffset_read                    : 11;  // 26:16
} L9A0_CVB_OFFSET_READ_T;

typedef struct { // 0x024c
	UINT32 sd_vd_range                     : 2;   //  1: 0
	UINT32 sd_ext_range                    : 2;   //  3: 2
	UINT32 intr_mask_node                  : 1;   //     4
	UINT32 intr_mask_nohsync               : 1;   //     5
	UINT32 intrl_mask_novsync              : 1;   //     6
	UINT32 intr_mask_abnormal              : 1;   //     7
	UINT32 intr_mask_invalid               : 1;   //     8
	UINT32 intr_mask_de                    : 1;   //     9
	UINT32 intr_mask_hsync                 : 1;   //    10
	UINT32 intr_mask_vsync                 : 1;   //    11
	UINT32 intr_mask_normal                : 1;   //    12
	UINT32 intr_mask_valid                 : 1;   //    13
	UINT32                                 : 1;   //    14
	UINT32 sd_en                           : 1;   //    15
	UINT32 sd_frame_cnt                    : 3;   // 18:16
	UINT32                                 : 1;   //    19
	UINT32 sd_novald_duration              : 2;   // 21:20
	UINT32                                 : 2;   // 23:22
	UINT32 sd_one_field                    : 1;   //    24
	UINT32 intr_mask_ext_diff              : 1;   //    25
	UINT32 intr_mask_vd_diff               : 1;   //    26
} L9A0_CVB_SIZE_DETECT_CTRL_T;

typedef struct { // 0x0250
	UINT32 line_num_read                   : 16;  // 15: 0
	UINT32 line_width_read                 : 16;  // 31:16
} L9A0_CVB_SIZE_DETECT_READ_T;

typedef struct { // 0x0254
	UINT32 pre3d_sync_enable               : 1;   //     0
	UINT32 pre3d_sync_mode                 : 2;   //  2: 1
	UINT32 pre3d_field_mode                : 1;   //     3
	UINT32 pre3d_frame_lr_mode             : 1;   //     4
	UINT32 pre3d_mid_vsync_bypass          : 1;   //     5
	UINT32 pre3d_field_bypass              : 1;   //     6
	UINT32                                 : 9;   // 15: 7
	UINT32 pre3d_active_line_num           : 12;  // 27:16
} L9A0_CVB_PRE3D_CTRL0_T;

typedef struct { // 0x0258
	UINT32 pre3d_active_space1_line_num    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pre3d_active_space2_line_num    : 12;  // 27:16
} L9A0_CVB_PRE3D_CTRL1_T;

typedef struct { // 0x025c
	UINT32 pre3d_front_porch_line_num      : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pre3d_sync_line_num             : 12;  // 27:16
} L9A0_CVB_PRE3D_CTRL2_T;

typedef struct { // 0x0260
	UINT32 current_line_number_read        : 12;  // 11: 0
	UINT32 de_signal_detect                : 1;   //    12
	UINT32 hsync_signal_detect             : 1;   //    13
	UINT32 vsync_signal_detect             : 1;   //    14
	UINT32 source_valid                    : 1;   //    15
	UINT32 sd_hsync_fault_flag_read        : 1;   //    16
	UINT32 sd_vsync_fault_flag_read        : 1;   //    17
	UINT32 sd_hsync_polarity               : 1;   //    18
	UINT32 sd_vsync_polarity               : 1;   //    19
	UINT32 sd_line_num                     : 12;  // 31:20
} L9A0_CVB_SIZE_STATUS0_T;

typedef struct { // 0x0264
	UINT32 sd_hoffset_indurance_read       : 8;   //  7: 0
	UINT32 sd_voffset_indurance_read       : 8;   // 15: 8
	UINT32 hoffset_over                    : 1;   //    16
	UINT32 v_offset_over                   : 1;   //    17
} L9A0_CVB_SIZE_STATUS1_T;

typedef struct { // 0x0268
	UINT32 de_line_size                    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 de_line_count                   : 12;  // 27:16
} L9A0_CVB_SIZE_STATUS2_T;

typedef struct { // 0x026c
	UINT32 hd_sync_size                    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 hd_line_size                    : 12;  // 27:16
} L9A0_CVB_SIZE_STATUS3_T;

typedef struct { // 0x0270
	UINT32 vd_sync_count                   : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 vd_line_count                   : 12;  // 27:16
} L9A0_CVB_SIZE_STATUS4_T;

typedef struct { // 0x0274
	UINT32 sd_2field_size                  : 24;  // 23: 0
} L9A0_CVB_SIZE_STATUS5_T;

typedef struct { // 0x0278
	UINT32 vsync_pesudo_sel                : 1;   //     0
	UINT32 hsync_pesudo_sel                : 1;   //     1
	UINT32 vactive_pesudo_sel              : 1;   //     2
	UINT32 hactive_pesudo_sel              : 1;   //     3
	UINT32 field_pesudo_sel                : 1;   //     4
} L9A0_CVB_PSEUDO_SYNC_CTRL0_T;

typedef struct { // 0x027c
	UINT32 pseudo_hfp                      : 14;  // 13: 0
	UINT32                                 : 2;   // 15:14
	UINT32 pseudo_hsync                    : 14;  // 29:16
} L9A0_CVB_PSEUDO_SYNC_CTRL1_T;

typedef struct { // 0x0280
	UINT32 pseudo_hblk                     : 14;  // 13: 0
	UINT32                                 : 2;   // 15:14
	UINT32 pseudo_hn                       : 14;  // 29:16
} L9A0_CVB_PSEUDO_SYNC_CTRL2_T;

typedef struct { // 0x0284
	UINT32 pseudo_vfp                      : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pseudo_vsync                    : 12;  // 27:16
} L9A0_CVB_PSEUDO_SYNC_CTRL3_T;

typedef struct { // 0x0288
	UINT32 pseudo_vblk                     : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 pseudo_vn                       : 12;  // 27:16
} L9A0_CVB_PSEUDO_SYNC_CTRL4_T;

typedef struct { // 0x028c
	UINT32 hd_pixel_delay                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 vd_line_delay                   : 12;  // 27:16
	UINT32                                 : 3;   // 30:28
	UINT32 pre_sync_ctrl_en                : 1;   //    31
} L9A0_CVB_PRE_SYNC_CTRL_T;

typedef struct { // 0x0290
	UINT32 diff_vd_vcnt                    : 16;  // 15: 0
	UINT32 diff_ext_vcnt                   : 12;  // 27:16
	UINT32                                 : 3;   // 30:28
	UINT32 vd_intr                         : 1;   //    31
} L9A0_CVB_SIZE_STATUS6_T;

typedef struct { // 0x0294
	UINT32 start_pos_x                     : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 end_pos_x                       : 12;  // 27:16
	UINT32 pix_sum_enable                  : 1;   //    28
	UINT32 field_selection                 : 2;   // 30:29
	UINT32 debug_enable                    : 1;   //    31
} L9A0_CVB_PIX_SUM_CTRL0_T;

typedef struct { // 0x0298
	UINT32 start_pos_y                     : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 end_pos_y                       : 12;  // 27:16
} L9A0_CVB_PIX_SUM_CTRL1_T;

typedef struct { // 0x029c
	UINT32 pix_sum_g                       : 32;  // 31: 0
} L9A0_CVB_PIX_SUM_STATUS0_T;

typedef struct { // 0x02a0
	UINT32 pix_sum_b                       : 32;  // 31: 0
} L9A0_CVB_PIX_SUM_STATUS1_T;

typedef struct { // 0x02a4
	UINT32 pix_sum_r                       : 32;  // 31: 0
} L9A0_CVB_PIX_SUM_STATUS2_T;

typedef struct { // 0x02a8
	UINT32 line_count_sel                  : 12;  // 11: 0
} L9A0_CVB_DE_COUNT_SEL_T;

typedef struct { // 0x02ac
	UINT32 minus_blank_hsize               : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 minus_blank_vsize               : 12;  // 27:16
} L9A0_CVB_MINUS_BLANK_SIZE_T;

typedef struct {
	L9A0_CVA_TOP_CTRL_T             cva_top_ctrl;                    // 0x0100
	L9A0_CVA_OFFSET_CTRL_T          cva_offset_ctrl;                 // 0x0104
	L9A0_CVA_SIZE_CTRL_T            cva_size_ctrl;                   // 0x0108
	L9A0_CVA_INT_SYNC_CTRL0_T       cva_int_sync_ctrl0;              // 0x010c
	L9A0_CVA_INT_SYNC_CTRL1_T       cva_int_sync_ctrl1;              // 0x0110
	L9A0_CVA_DIG_FILT_CTRL0_T       cva_dig_filt_ctrl0;              // 0x0114
	L9A0_CVA_DIG_FILT_CTRL1_T       cva_dig_filt_ctrl1;              // 0x0118
	L9A0_CVA_DIG_FILT_CTRL2_T       cva_dig_filt_ctrl2;              // 0x011c
	L9A0_CVA_DIG_FILT_CTRL3_T       cva_dig_filt_ctrl3;              // 0x0120
	L9A0_CVA_CSC_CTRL0_T            cva_csc_ctrl0;                   // 0x0124
	L9A0_CVA_CSC_CTRL1_T            cva_csc_ctrl1;                   // 0x0128
	L9A0_CVA_CSC_CTRL2_T            cva_csc_ctrl2;                   // 0x012c
	L9A0_CVA_CSC_CTRL3_T            cva_csc_ctrl3;                   // 0x0130
	L9A0_CVA_CSC_CTRL4_T            cva_csc_ctrl4;                   // 0x0134
	L9A0_CVA_CSC_CTRL5_T            cva_csc_ctrl5;                   // 0x0138
	L9A0_CVA_CSC_CTRL6_T            cva_csc_ctrl6;                   // 0x013c
	L9A0_CVA_CSC_CTRL7_T            cva_csc_ctrl7;                   // 0x0140
	L9A0_CVA_MISC_CTRL_T            cva_misc_ctrl;                   // 0x0144
	L9A0_CVA_OFFSET_READ_T          cva_offset_read;                 // 0x0148
	L9A0_CVA_SIZE_DETECT_CTRL_T     cva_size_detect_ctrl;            // 0x014c
	L9A0_CVA_SIZE_DETECT_READ_T     cva_size_detect_read;            // 0x0150
	L9A0_CVA_PRE3D_CTRL0_T          cva_pre3d_ctrl0;                 // 0x0154
	L9A0_CVA_PRE3D_CTRL1_T          cva_pre3d_ctrl1;                 // 0x0158
	L9A0_CVA_PRE3D_CTRL2_T          cva_pre3d_ctrl2;                 // 0x015c
	L9A0_CVA_SIZE_STATUS0_T         cva_size_status0;                // 0x0160
	L9A0_CVA_SIZE_STATUS1_T         cva_size_status1;                // 0x0164
	L9A0_CVA_SIZE_STATUS2_T         cva_size_status2;                // 0x0168
	L9A0_CVA_SIZE_STATUS3_T         cva_size_status3;                // 0x016c
	L9A0_CVA_SIZE_STATUS4_T         cva_size_status4;                // 0x0170
	L9A0_CVA_SIZE_STATUS5_T         cva_size_status5;                // 0x0174
	L9A0_CVA_PSEUDO_SYNC_CTRL0_T    cva_pseudo_sync_ctrl0;           // 0x0178
	L9A0_CVA_PSEUDO_SYNC_CTRL1_T    cva_pseudo_sync_ctrl1;           // 0x017c
	L9A0_CVA_PSEUDO_SYNC_CTRL2_T    cva_pseudo_sync_ctrl2;           // 0x0180
	L9A0_CVA_PSEUDO_SYNC_CTRL3_T    cva_pseudo_sync_ctrl3;           // 0x0184
	L9A0_CVA_PSEUDO_SYNC_CTRL4_T    cva_pseudo_sync_ctrl4;           // 0x0188
	L9A0_CVA_PRE_SYNC_CTRL_T        cva_pre_sync_ctrl;               // 0x018c
	L9A0_CVA_SIZE_STATUS6_T         cva_size_status6;                // 0x0190
	L9A0_CVA_PIX_SUM_CTRL0_T        cva_pix_sum_ctrl0;               // 0x0194
	L9A0_CVA_PIX_SUM_CTRL1_T        cva_pix_sum_ctrl1;               // 0x0198
	L9A0_CVA_PIX_SUM_STATUS0_T      cva_pix_sum_status0;             // 0x019c
	L9A0_CVA_PIX_SUM_STATUS1_T      cva_pix_sum_status1;             // 0x01a0
	L9A0_CVA_PIX_SUM_STATUS2_T      cva_pix_sum_status2;             // 0x01a4
	L9A0_CVA_DE_COUNT_SEL_T         cva_de_count_sel;                // 0x01a8
	L9A0_CVA_MINUS_BLANK_SIZE_T     cva_minus_blank_size;            // 0x01ac
} DE_CVA_REG_L9A0_T;

typedef struct {
	L9A0_CVB_TOP_CTRL_T             cvb_top_ctrl;                    // 0x0200
	L9A0_CVB_OFFSET_CTRL_T          cvb_offset_ctrl;                 // 0x0204
	L9A0_CVB_SIZE_CTRL_T            cvb_size_ctrl;                   // 0x0208
	L9A0_CVB_INT_SYNC_CTRL0_T       cvb_int_sync_ctrl0;              // 0x020c
	L9A0_CVB_INT_SYNC_CTRL1_T       cvb_int_sync_ctrl1;              // 0x0210
	L9A0_CVB_DIG_FILT_CTRL0_T       cvb_dig_filt_ctrl0;              // 0x0214
	L9A0_CVB_DIG_FILT_CTRL1_T       cvb_dig_filt_ctrl1;              // 0x0218
	L9A0_CVB_DIG_FILT_CTRL2_T       cvb_dig_filt_ctrl2;              // 0x021c
	L9A0_CVB_DIG_FILT_CTRL3_T       cvb_dig_filt_ctrl3;              // 0x0220
	L9A0_CVB_CSC_CTRL0_T            cvb_csc_ctrl0;                   // 0x0224
	L9A0_CVB_CSC_CTRL1_T            cvb_csc_ctrl1;                   // 0x0228
	L9A0_CVB_CSC_CTRL2_T            cvb_csc_ctrl2;                   // 0x022c
	L9A0_CVB_CSC_CTRL3_T            cvb_csc_ctrl3;                   // 0x0230
	L9A0_CVB_CSC_CTRL4_T            cvb_csc_ctrl4;                   // 0x0234
	L9A0_CVB_CSC_CTRL5_T            cvb_csc_ctrl5;                   // 0x0238
	L9A0_CVB_CSC_CTRL6_T            cvb_csc_ctrl6;                   // 0x023c
	L9A0_CVB_CSC_CTRL7_T            cvb_csc_ctrl7;                   // 0x0240
	L9A0_CVB_MISC_CTRL_T            cvb_misc_ctrl;                   // 0x0244
	L9A0_CVB_OFFSET_READ_T          cvb_offset_read;                 // 0x0248
	L9A0_CVB_SIZE_DETECT_CTRL_T     cvb_size_detect_ctrl;            // 0x024c
	L9A0_CVB_SIZE_DETECT_READ_T     cvb_size_detect_read;            // 0x0250
	L9A0_CVB_PRE3D_CTRL0_T          cvb_pre3d_ctrl0;                 // 0x0254
	L9A0_CVB_PRE3D_CTRL1_T          cvb_pre3d_ctrl1;                 // 0x0258
	L9A0_CVB_PRE3D_CTRL2_T          cvb_pre3d_ctrl2;                 // 0x025c
	L9A0_CVB_SIZE_STATUS0_T         cvb_size_status0;                // 0x0260
	L9A0_CVB_SIZE_STATUS1_T         cvb_size_status1;                // 0x0264
	L9A0_CVB_SIZE_STATUS2_T         cvb_size_status2;                // 0x0268
	L9A0_CVB_SIZE_STATUS3_T         cvb_size_status3;                // 0x026c
	L9A0_CVB_SIZE_STATUS4_T         cvb_size_status4;                // 0x0270
	L9A0_CVB_SIZE_STATUS5_T         cvb_size_status5;                // 0x0274
	L9A0_CVB_PSEUDO_SYNC_CTRL0_T    cvb_pseudo_sync_ctrl0;           // 0x0278
	L9A0_CVB_PSEUDO_SYNC_CTRL1_T    cvb_pseudo_sync_ctrl1;           // 0x027c
	L9A0_CVB_PSEUDO_SYNC_CTRL2_T    cvb_pseudo_sync_ctrl2;           // 0x0280
	L9A0_CVB_PSEUDO_SYNC_CTRL3_T    cvb_pseudo_sync_ctrl3;           // 0x0284
	L9A0_CVB_PSEUDO_SYNC_CTRL4_T    cvb_pseudo_sync_ctrl4;           // 0x0288
	L9A0_CVB_PRE_SYNC_CTRL_T        cvb_pre_sync_ctrl;               // 0x028c
	L9A0_CVB_SIZE_STATUS6_T         cvb_size_status6;                // 0x0290
	L9A0_CVB_PIX_SUM_CTRL0_T        cvb_pix_sum_ctrl0;               // 0x0294
	L9A0_CVB_PIX_SUM_CTRL1_T        cvb_pix_sum_ctrl1;               // 0x0298
	L9A0_CVB_PIX_SUM_STATUS0_T      cvb_pix_sum_status0;             // 0x029c
	L9A0_CVB_PIX_SUM_STATUS1_T      cvb_pix_sum_status1;             // 0x02a0
	L9A0_CVB_PIX_SUM_STATUS2_T      cvb_pix_sum_status2;             // 0x02a4
	L9A0_CVB_DE_COUNT_SEL_T         cvb_de_count_sel;                // 0x02a8
	L9A0_CVB_MINUS_BLANK_SIZE_T     cvb_minus_blank_size;            // 0x02ac
} DE_CVB_REG_L9A0_T;

#endif
