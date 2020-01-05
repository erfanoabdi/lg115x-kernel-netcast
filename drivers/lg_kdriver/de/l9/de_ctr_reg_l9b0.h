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

#ifndef _REG_CTR_L9B0_h
#define _REG_CTR_L9B0_h

/*-----------------------------------------------------------------------------
	0x0000 dea_cha_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cha_hsize                       : 12;  //  0:11
	UINT32                                 : 1;   //    12 reserved
	UINT32 cha_csample                     : 1;   //    13
	UINT32 cha_aspect                      : 1;   //    14
	UINT32                                 : 1;   //    15 reserved
	UINT32 cha_vsize                       : 12;  // 16:27
	UINT32                                 : 1;   //    28 reserved
	UINT32 cha_frame_lr                    : 1;   //    29
	UINT32 cha_field_id                    : 1;   //    30
	UINT32 cha_pr_sq                       : 1;   //    31
} L9B0_DEA_CHA_INFO_T;

/*-----------------------------------------------------------------------------
	0x0004 dea_chb_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 chb_hsize                       : 12;  //  0:11
	UINT32                                 : 1;   //    12 reserved
	UINT32 chb_csample                     : 1;   //    13
	UINT32 chb_aspect                      : 1;   //    14
	UINT32                                 : 1;   //    15 reserved
	UINT32 chb_vsize                       : 12;  // 16:27
	UINT32                                 : 1;   //    28 reserved
	UINT32 chb_frame_lr                    : 1;   //    29
	UINT32 chb_field_id                    : 1;   //    30
	UINT32 chb_pr_sq                       : 1;   //    31
} L9B0_DEA_CHB_INFO_T;

/*-----------------------------------------------------------------------------
	0x0008 dea_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                     : 1;   //     0
	UINT32 pic_init_g1                     : 1;   //     1
} L9B0_DEA_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x000c dea_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                    : 1;   //     0
	UINT32 pic_start_g1                    : 1;   //     1
} L9B0_DEA_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x0010 dea_smux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 o_c_fmt                         : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 i_c_fmt                         : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 dec3d_mux_sel                   : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 prew_mux_sel                    : 1;   //    12
	UINT32 d3_lr_sel                       : 1;   //    13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 cvi_mux_sel                     : 2;   // 16:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 nline_inc                       : 1;   //    20
	UINT32                                 : 2;   // 21:22 reserved
	UINT32 wr_disalbe                      : 1;   //    23
	UINT32 fieldid                         : 1;   //    24
	UINT32 input_size_en                   : 1;   //    25
	UINT32                                 : 5;   // 26:30 reserved
	UINT32 pr_sq                           : 1;   //    31
} L9B0_DEA_SMUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0014 dea_smux_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize                           : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 vsize                           : 12;  // 16:27
} L9B0_DEA_SMUX_SIZE_T;

/*-----------------------------------------------------------------------------
	0x0018 dea_mvi_v_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_vsize                       : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 mvi_vblank                      : 12;  // 16:27
} L9B0_DEA_MVI_V_INFO_T;

/*-----------------------------------------------------------------------------
	0x001c dea_mvi_h_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_hsize                       : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 mvi_hblank                      : 12;  // 16:27
} L9B0_DEA_MVI_H_INFO_T;

/*-----------------------------------------------------------------------------
	0x0020 dea_mvi_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_i_c_fmt                     : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 mvi_field                       : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 mvi_pr_sq                       : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 mvi_cvi_stride                  : 1;   //    12
} L9B0_DEA_MVI_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0024 dea_msrc_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 trans_mask_en                   : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 cvi_select                      : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 mvi_select                      : 1;   //     8
	UINT32 mvi_sync_select                 : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 mvi_cvi_select                  : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 cvia_vsync_inv                  : 1;   //    16
	UINT32 cvib_vsync_inv                  : 1;   //    17
	UINT32 vdec_vsync_inv                  : 1;   //    18
	UINT32 mem_vsync_inv                   : 1;   //    19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 cvia_sync_sel                   : 1;   //    24
	UINT32 cvib_sync_sel                   : 1;   //    25
	UINT32                                 : 2;   // 26:27 reserved
	UINT32 sync_manual_delay_en            : 1;   //    28
	UINT32                                 : 2;   // 29:30 reserved
	UINT32 ignore_src_vsync_fal            : 1;   //    31
} L9B0_DEA_MSRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0028 dea_msrc_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_msrc_sync_dly               : 28;  //  0:27
} L9B0_DEA_MSRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x002c dea_mem_sync_period ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_mem_sync_period             : 28;  //  0:27
} L9B0_DEA_MEM_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
	0x0030 dea_dco_mfc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dco_mfc                     : 28;  //  0:27
} L9B0_DEA_DCO_MFC_T;

/*-----------------------------------------------------------------------------
	0x0034 dea_dco_dfc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dco_dfc                     : 28;  //  0:27
} L9B0_DEA_DCO_DFC_T;

/*-----------------------------------------------------------------------------
	0x0038 dea_dco_dflc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dco_dflc                    : 12;  //  0:11
} L9B0_DEA_DCO_DFLC_T;

/*-----------------------------------------------------------------------------
	0x003c dea_dco_fcw ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dco_fcw                     : 22;  //  0:21
} L9B0_DEA_DCO_FCW_T;

/*-----------------------------------------------------------------------------
	0x0040 dea_smux_ro_lcnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_smux_ro_lcnt                : 12;  //  0:11
} L9B0_DEA_SMUX_RO_LCNT_T;

/*-----------------------------------------------------------------------------
	0x0044 dea_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                 : 8;   //  0: 7
	UINT32                                 : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                      : 10;  // 16:25
} L9B0_DEA_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0048 dea_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_en                          : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 clc_en                          : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 tnr_en                          : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 pe0_en                          : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 prew_en                         : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 smux_en                         : 1;   //    20
} L9B0_DEA_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x004c dea_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0_timer               : 28;  //  0:27
} L9B0_DEA_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x0050 dea_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer               : 28;  //  0:27
} L9B0_DEA_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x0054 dea_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 5;   //  0: 4
	UINT32 pic_end_g1                      : 8;   //  5:12
} L9B0_DEA_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x0058 dea_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 1;   //     0
	UINT32 pic_end_g1                      : 1;   //     1
	UINT32 cha_input_intr                  : 1;   //     2
	UINT32 chb_input_intr                  : 1;   //     3
	UINT32 cha_field_intr                  : 1;   //     4
	UINT32 cha_frame_lr_intr               : 1;   //     5
	UINT32 chb_field_intr                  : 1;   //     6
	UINT32 chb_frame_lr_intr               : 1;   //     7
	UINT32 pe0_intr                        : 1;   //     8
	UINT32 smux_ow_intr                    : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 gmau_flush_rd_done              : 1;   //    12
	UINT32 gmau_flush_wr_done              : 1;   //    13
	UINT32                                 : 9;   // 14:22 reserved
	UINT32 src_intr                        : 1;   //    23
} L9B0_DEA_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x005c dea_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 1;   //     0
	UINT32 pic_end_g1                      : 1;   //     1
	UINT32 cha_input_intr                  : 1;   //     2
	UINT32 chb_input_intr                  : 1;   //     3
	UINT32 cha_field_intr                  : 1;   //     4
	UINT32 cha_frame_lr_intr               : 1;   //     5
	UINT32 chb_field_intr                  : 1;   //     6
	UINT32 chb_frame_lr_intr               : 1;   //     7
	UINT32 pe0_intr                        : 1;   //     8
	UINT32 smux_ow_intr                    : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 gmau_flush_rd_done              : 1;   //    12
	UINT32 gmau_flush_wr_done              : 1;   //    13
	UINT32                                 : 9;   // 14:22 reserved
	UINT32 src_intr                        : 1;   //    23
} L9B0_DEA_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x0060 dea_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 1;   //     0
	UINT32 pic_end_g1                      : 1;   //     1
	UINT32 cha_input_intr                  : 1;   //     2
	UINT32 chb_input_intr                  : 1;   //     3
	UINT32 cha_field_intr                  : 1;   //     4
	UINT32 cha_frame_lr_intr               : 1;   //     5
	UINT32 chb_field_intr                  : 1;   //     6
	UINT32 chb_frame_lr_intr               : 1;   //     7
	UINT32 pe0_intr                        : 1;   //     8
	UINT32 smux_ow_intr                    : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 gmau_flush_rd_done              : 1;   //    12
	UINT32 gmau_flush_wr_done              : 1;   //    13
	UINT32                                 : 9;   // 14:22 reserved
	UINT32 src_intr                        : 1;   //    23
} L9B0_DEA_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x0064 dea_src_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_src_intr_time_stp           : 32;  //  0:31
} L9B0_DEA_SRC_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x0068 de_gpio_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 de_gpio_mux                     : 2;   //  0: 1
} L9B0_DE_GPIO_MUX_T;

/*-----------------------------------------------------------------------------
	0x006c dea_addr_sw_de_sav ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 dea_addr_sav_bus                : 7;   //  3: 9
	UINT32                                 : 6;   // 10:15 reserved
	UINT32 dea_addr_default_bus            : 2;   // 16:17
	UINT32                                 : 6;   // 18:23 reserved
	UINT32 dea_addr_de_bus                 : 6;   // 24:29
} L9B0_DEA_ADDR_SW_DE_SAV_T;

/*-----------------------------------------------------------------------------
	0x0070 dea_addr_sw_cpu_gpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 dea_addr_gpu_bus                : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 dea_addr_gpu_logic              : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 dea_addr_cpu_h_bus              : 4;   // 24:27
} L9B0_DEA_ADDR_SW_CPU_GPU_T;

/*-----------------------------------------------------------------------------
	0x0074 dea_addr_sw_cpu_shadow ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 dea_addr_shadow_bus             : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 dea_addr_shadow_logic           : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 dea_addr_cpu_l_bus              : 6;   // 24:29
} L9B0_DEA_ADDR_SW_CPU_SHADOW_T;

/*-----------------------------------------------------------------------------
	0x007c de_version ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 de_version                      : 32;  //  0:31
} L9B0_DE_VERSION_T;

/*-----------------------------------------------------------------------------
	0x0080 dea_smux_size_i ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_i                         : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 vsize_i                         : 12;  // 16:27
} L9B0_DEA_SMUX_SIZE_I_T;

/*-----------------------------------------------------------------------------
	0x00c0 dea_dea_mvi_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_h_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 y_h_width                       : 12;  // 16:27
	UINT32                                 : 3;   // 28:30 reserved
	UINT32 mvi_3d_ctrl_en                  : 1;   //    31
} L9B0_DEA_DEA_MVI_CTRL_0_T;

/*-----------------------------------------------------------------------------
	0x00c4 dea_dea_mvi_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_h_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 c_h_width                       : 12;  // 16:27
} L9B0_DEA_DEA_MVI_CTRL_1_T;

/*-----------------------------------------------------------------------------
	0x00c8 dea_dea_mvi_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_v_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 y_v_height                      : 12;  // 16:27
} L9B0_DEA_DEA_MVI_CTRL_2_T;

/*-----------------------------------------------------------------------------
	0x00cc dea_dea_mvi_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_v_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 c_v_height                      : 12;  // 16:27
} L9B0_DEA_DEA_MVI_CTRL_3_T;

/*-----------------------------------------------------------------------------
	0x00d0 dea_dea_mvi_ctrl_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_sub_sample_step               : 8;   //  0: 7
	UINT32 y_h_even_line_sub_sample_offset : 8;   //  8:15
	UINT32                                 : 8;   // 16:23 reserved
	UINT32 y_h_odd_line_sub_sample_offset  : 8;   // 24:31
} L9B0_DEA_DEA_MVI_CTRL_4_T;

/*-----------------------------------------------------------------------------
	0x00d4 dea_dea_mvi_ctrl_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 8;   //  0: 7 reserved
	UINT32 c_h_even_line_sub_sample_offset : 8;   //  8:15
	UINT32                                 : 8;   // 16:23 reserved
	UINT32 c_h_odd_line_sub_sample_offset  : 8;   // 24:31
} L9B0_DEA_DEA_MVI_CTRL_5_T;

/*-----------------------------------------------------------------------------
	0x00d8 dea_dea_mvi_ctrl_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_sub_sample_step               : 8;   //  0: 7
	UINT32 y_v_sub_sample_offset           : 8;   //  8:15
	UINT32                                 : 8;   // 16:23 reserved
	UINT32 c_v_sub_sample_offset           : 8;   // 24:31
} L9B0_DEA_DEA_MVI_CTRL_6_T;

/*-----------------------------------------------------------------------------
	0x00e0 dea_pic_start_delay_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_delay_mvi             : 1;   //     0
	UINT32 pic_start_delay_mvi_y_rd        : 1;   //     1
	UINT32 pic_start_delay_mvi_c_rd        : 1;   //     2
	UINT32 pic_start_delay_dec3d           : 1;   //     3
	UINT32 pic_start_delay_smux            : 1;   //     4
	UINT32 pic_start_delay_prew_y_rd       : 1;   //     5
	UINT32 pic_start_delay_prew_c_rd       : 1;   //     6
	UINT32 pic_start_delay_prew_y_wd       : 1;   //     7
	UINT32 pic_start_delay_prew_c_wd       : 1;   //     8
	UINT32                                 : 7;   //  9:15 reserved
	UINT32 pic_start_delay_pe0             : 1;   //    16
	UINT32 pic_start_delay_tnr0_y_rd       : 1;   //    17
	UINT32 pic_start_delay_tnr1_y_rd       : 1;   //    18
	UINT32 pic_start_delay_tnr_c_rd        : 1;   //    19
	UINT32 pic_start_delay_tnr_y_wd        : 1;   //    20
	UINT32 pic_start_delay_tnr_c_wd        : 1;   //    21
	UINT32 pic_start_delay_ipc0_y_rd       : 1;   //    22
	UINT32 pic_start_delay_ipc1_y_rd       : 1;   //    23
	UINT32 pic_start_delay_ipc_c_rd        : 1;   //    24
} L9B0_DEA_PIC_START_DELAY_CTRL_T;

/*-----------------------------------------------------------------------------
	0x00e4 dea_pic_start_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0_timer              : 28;  //  0:27
} L9B0_DEA_PIC_START_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x00e8 dea_pic_start_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g1_timer              : 28;  //  0:27
} L9B0_DEA_PIC_START_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x00f4 dea_pic_end_force ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_pic_end_g0_force            : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 dea_pic_end_g0_force_en         : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 dea_pic_end_g1_force            : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 dea_pic_end_g1_force_en         : 1;   //    12
} L9B0_DEA_PIC_END_FORCE_T;

/*-----------------------------------------------------------------------------
	0x00f8 dea_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done              : 1;   //    12
} L9B0_DEA_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x00fc dea_mg_ls_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_ls_override_mifa            : 1;   //     0
	UINT32 dea_ls_override_pe0_l           : 1;   //     1
	UINT32 dea_ls_override_smux_l          : 1;   //     2
	UINT32 dea_ls_override_cvi             : 1;   //     3
	UINT32                                 : 12;  //  4:15 reserved
	UINT32 dea_mg_override_mifa            : 1;   //    16
	UINT32 dea_mg_override_pe0_l           : 1;   //    17
	UINT32 dea_mg_override_smux_l          : 1;   //    18
	UINT32 dea_mg_override_cvi             : 1;   //    19
} L9B0_DEA_MG_LS_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1000 deb_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                     : 1;   //     0
	UINT32 pic_init_g1                     : 1;   //     1
	UINT32                                 : 14;  //  2:15 reserved
	UINT32 ov_auto_init                    : 1;   //    16
} L9B0_DEB_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x1004 deb_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                    : 1;   //     0
	UINT32 pic_start_g1                    : 1;   //     1
} L9B0_DEB_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x1008 deb_disp_v_porch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync_bp                        : 16;  //  0:15
	UINT32 vsync_fp                        : 16;  // 16:31
} L9B0_DEB_DISP_V_PORCH_T;

/*-----------------------------------------------------------------------------
	0x100c deb_disp_vs_va ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_sync_va                    : 16;  //  0:15
	UINT32 vsync                           : 16;  // 16:31
} L9B0_DEB_DISP_VS_VA_T;

/*-----------------------------------------------------------------------------
	0x1010 deb_disp_h_porch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync_bp                        : 16;  //  0:15
	UINT32 hsync_fp                        : 16;  // 16:31
} L9B0_DEB_DISP_H_PORCH_T;

/*-----------------------------------------------------------------------------
	0x1014 deb_disp_hs_ha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_sync_ha                    : 16;  //  0:15
	UINT32 hsync                           : 16;  // 16:31
} L9B0_DEB_DISP_HS_HA_T;

/*-----------------------------------------------------------------------------
	0x1018 deb_disp_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset1                        : 16;  //  0:15
	UINT32 voffset1                        : 16;  // 16:31
} L9B0_DEB_DISP_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x101c deb_disp_pulse_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_disp_pulse_dly              : 28;  //  0:27
} L9B0_DEB_DISP_PULSE_DLY_T;

/*-----------------------------------------------------------------------------
	0x1020 deb_disp_sync_params ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset0                        : 16;  //  0:15
	UINT32                                 : 11;  // 16:26 reserved
	UINT32 disp_frame_lr                   : 1;   //    27
	UINT32                                 : 3;   // 28:30 reserved
	UINT32 force_update                    : 1;   //    31
} L9B0_DEB_DISP_SYNC_PARAMS_T;

/*-----------------------------------------------------------------------------
	0x102c deb_pwm0_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm0_en                         : 1;   //     0
	UINT32 pwm0_freq_mode                  : 2;   //  1: 2
	UINT32 pwm0_method                     : 1;   //     3
	UINT32 pwm0_resolution                 : 2;   //  4: 5
	UINT32 pwm0_inv                        : 1;   //     6
	UINT32 pwm0_sel                        : 1;   //     7
	UINT32 pwm0_width_falling_pos          : 22;  //  8:29
	UINT32 pwm0_fc_h_disp                  : 1;   //    30
	UINT32 pwm0_fc_l_disp                  : 1;   //    31
} L9B0_DEB_PWM0_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x1030 deb_pwm0_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm0_intr_mask                  : 8;   //  0: 7
	UINT32 pwm0_free_width                 : 22;  //  8:29
} L9B0_DEB_PWM0_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x1034 deb_pwm1_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm1_en                         : 1;   //     0
	UINT32 pwm1_freq_mode                  : 2;   //  1: 2
	UINT32 pwm1_method                     : 1;   //     3
	UINT32 pwm1_resolution                 : 2;   //  4: 5
	UINT32 pwm1_inv                        : 1;   //     6
	UINT32 pwm1_sel                        : 1;   //     7
	UINT32 pwm1_width_falling_pos          : 22;  //  8:29
	UINT32 pwm1_fc_h_disp                  : 1;   //    30
	UINT32 pwm1_fc_l_disp                  : 1;   //    31
} L9B0_DEB_PWM1_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x1038 deb_pwm1_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm1_intr_mask                  : 8;   //  0: 7
	UINT32 pwm1_free_width                 : 22;  //  8:29
} L9B0_DEB_PWM1_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x103c deb_pwm2_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm2_en                         : 1;   //     0
	UINT32 pwm2_freq_mode                  : 2;   //  1: 2
	UINT32 pwm2_method                     : 1;   //     3
	UINT32 pwm2_resolution                 : 2;   //  4: 5
	UINT32 pwm2_inv                        : 1;   //     6
	UINT32 pwm2_sel                        : 1;   //     7
	UINT32 pwm2_width_falling_pos          : 22;  //  8:29
	UINT32 pwm2_fc_h_disp                  : 1;   //    30
	UINT32 pwm2_fc_l_disp                  : 1;   //    31
} L9B0_DEB_PWM2_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x1040 deb_pwm2_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm2_intr_mask                  : 8;   //  0: 7
	UINT32 pwm2_free_width                 : 22;  //  8:29
} L9B0_DEB_PWM2_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x1044 deb_pwm3_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_en                         : 1;   //     0
	UINT32 pwm3_freq_mode                  : 2;   //  1: 2
	UINT32 pwm3_intr_mask                  : 5;   //  3: 7
	UINT32 pwm3_threshold                  : 22;  //  8:29
} L9B0_DEB_PWM3_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1048 pwm3_0_low ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_0_low                      : 22;  //  0:21
} L9B0_PWM3_0_LOW_T;

/*-----------------------------------------------------------------------------
	0x104c pwm3_0_high ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_0_high                     : 22;  //  0:21
} L9B0_PWM3_0_HIGH_T;

/*-----------------------------------------------------------------------------
	0x1050 pwm3_1_low ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_1_low                      : 22;  //  0:21
} L9B0_PWM3_1_LOW_T;

/*-----------------------------------------------------------------------------
	0x1054 pwm3_1_high ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_1_high                     : 22;  //  0:21
} L9B0_PWM3_1_HIGH_T;

/*-----------------------------------------------------------------------------
	0x1058 pwm3_2_low ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_2_low                      : 22;  //  0:21
} L9B0_PWM3_2_LOW_T;

/*-----------------------------------------------------------------------------
	0x105c pwm3_2_high ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_2_high                     : 22;  //  0:21
} L9B0_PWM3_2_HIGH_T;

/*-----------------------------------------------------------------------------
	0x1060 pwm3_3_low ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_3_low                      : 22;  //  0:21
} L9B0_PWM3_3_LOW_T;

/*-----------------------------------------------------------------------------
	0x1064 pwm3_3_high ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm3_3_high                     : 22;  //  0:21
} L9B0_PWM3_3_HIGH_T;

/*-----------------------------------------------------------------------------
	0x1068 deb_dpath_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 t3_mux_sel                      : 2;   //  0: 1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 fb_mux_sel                      : 1;   //     4
} L9B0_DEB_DPATH_CTRL_T;

/*-----------------------------------------------------------------------------
	0x106c deb_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                 : 8;   //  0: 7
	UINT32                                 : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                      : 10;  // 16:25
} L9B0_DEB_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1070 deb_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ov_ss_en                        : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 ov_en                           : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 sm_en                           : 1;   //     8
} L9B0_DEB_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x1074 deb_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_pic_init_g0_timer           : 28;  //  0:27
} L9B0_DEB_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x1078 deb_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_pic_init_g1_timer           : 28;  //  0:27
} L9B0_DEB_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x107c deb_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 pic_end_g1                      : 5;   //  4: 8
} L9B0_DEB_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x1080 deb_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_pic_end_g0                 : 1;   //     0
	UINT32 intr_pic_end_g1                 : 1;   //     1
	UINT32 disp_pulse_for_cpu              : 1;   //     2
	UINT32 ov_underflow                    : 1;   //     3
	UINT32 intr_pwm                        : 1;   //     4
	UINT32                                 : 1;   //     5 reserved
	UINT32 disp_pulse_for_mcu              : 1;   //     6
	UINT32 src_pulse                       : 1;   //     7
	UINT32                                 : 1;   //     8 reserved
	UINT32 intr_pic_end_g1_c               : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 intr_gmau_flush_wr_done         : 1;   //    12
	UINT32 intr_gmau_flush_rd_done         : 1;   //    13
} L9B0_DEB_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x1084 deb_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_pic_end_g0                 : 1;   //     0
	UINT32 mask_pic_end_g1                 : 1;   //     1
	UINT32 mask_disp_for_cpu               : 1;   //     2
	UINT32 mask_ov_underflow               : 1;   //     3
	UINT32 mask_pwm                        : 1;   //     4
	UINT32                                 : 1;   //     5 reserved
	UINT32 mask_disp_for_mcu               : 1;   //     6
	UINT32 mask_src_pulse                  : 1;   //     7
	UINT32                                 : 1;   //     8 reserved
	UINT32 mask_pic_end_g1_c               : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 mask_gmau_flush_wr_done         : 1;   //    12
	UINT32 mask_gmau_flush_rd_done         : 1;   //    13
} L9B0_DEB_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x1088 deb_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_pic_end_g0                  : 1;   //     0
	UINT32 mux_pic_end_g1                  : 1;   //     1
	UINT32 mux_disp_for_cpu                : 1;   //     2
	UINT32 mux_ov_underflow                : 1;   //     3
	UINT32 mux_pwm                         : 1;   //     4
	UINT32                                 : 1;   //     5 reserved
	UINT32 mux_disp_for_mcu                : 1;   //     6
	UINT32 mux_src_pulse                   : 1;   //     7
	UINT32                                 : 1;   //     8 reserved
	UINT32 mux_pic_end_g1_c                : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 mux_gmau_flush_wr_done          : 1;   //    12
	UINT32 mux_gmau_flush_rd_done          : 1;   //    13
} L9B0_DEB_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x108c deb_disp_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_disp_intr_time_stp          : 32;  //  0:31
} L9B0_DEB_DISP_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x1090 deb_addr_sw_de_sav ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 deb_addr_sav_bus                : 7;   //  3: 9
	UINT32                                 : 6;   // 10:15 reserved
	UINT32 deb_addr_default_bus            : 2;   // 16:17
	UINT32                                 : 6;   // 18:23 reserved
	UINT32 deb_addr_de_bus                 : 6;   // 24:29
} L9B0_DEB_ADDR_SW_DE_SAV_T;

/*-----------------------------------------------------------------------------
	0x1094 deb_addr_sw_cpu_gpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 deb_addr_gpu_bus                : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 deb_addr_gpu_logic              : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 deb_addr_cpu_h_bus              : 4;   // 24:27
} L9B0_DEB_ADDR_SW_CPU_GPU_T;

/*-----------------------------------------------------------------------------
	0x1098 deb_addr_sw_cpu_shadow ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 deb_addr_shadow_bus             : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 deb_addr_shadow_logic           : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 deb_addr_cpu_l_bus              : 6;   // 24:29
} L9B0_DEB_ADDR_SW_CPU_SHADOW_T;

/*-----------------------------------------------------------------------------
	0x10a0 pwm0_v ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm0_x_f_v                      : 14;  //  0:13
	UINT32 pwm0_x_r_v                      : 14;  // 14:27
	UINT32 pwm0_v_id                       : 3;   // 28:30
	UINT32 pwm0_v_we                       : 1;   //    31
} L9B0_PWM0_V_T;

/*-----------------------------------------------------------------------------
	0x10a4 pwm1_v ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm1_x_f_v                      : 14;  //  0:13
	UINT32 pwm1_x_r_v                      : 14;  // 14:27
	UINT32 pwm1_v_id                       : 3;   // 28:30
	UINT32 pwm1_v_we                       : 1;   //    31
} L9B0_PWM1_V_T;

/*-----------------------------------------------------------------------------
	0x10a8 pwm2_v ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pwm2_x_f_v                      : 14;  //  0:13
	UINT32 pwm2_x_r_v                      : 14;  // 14:27
	UINT32 pwm2_v_id                       : 3;   // 28:30
	UINT32 pwm2_v_we                       : 1;   //    31
} L9B0_PWM2_V_T;

/*-----------------------------------------------------------------------------
	0x10b0 pwm0_v_sub ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 14;  //  0:13 reserved
	UINT32 pwm0_x_r_v_sub                  : 14;  // 14:27
	UINT32 pwm0_v_sub_id                   : 3;   // 28:30
	UINT32 pwm0_v_sub_we                       : 1;   //    31
} L9B0_PWM0_V_SUB_T;

/*-----------------------------------------------------------------------------
	0x10b4 pwm1_v_sub ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 14;  //  0:13 reserved
	UINT32 pwm1_x_r_v_sub                  : 14;  // 14:27
	UINT32 pwm1_v_sub_id                   : 3;   // 28:30
	UINT32 pwm1_v_sub_we                   : 1;   //    31
} L9B0_PWM1_V_SUB_T;

/*-----------------------------------------------------------------------------
	0x10b8 pwm2_v_sub ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 14;  //  0:13 reserved
	UINT32 pwm2_x_r_v_sub                  : 14;  // 14:27
	UINT32 pwm2_v_sub_id                   : 3;   // 28:30
	UINT32 pwm2_v_sub_we                   : 1;   //    31
} L9B0_PWM2_V_SUB_T;

/*-----------------------------------------------------------------------------
	0x10c0 deb_dly_disp_sync_dly_param ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_hoffset1                    : 16;  //  0:15
	UINT32 dly_voffset1                    : 16;  // 16:31
} L9B0_DEB_DLY_DISP_SYNC_DLY_PARAM_T;

/*-----------------------------------------------------------------------------
	0x10c4 deb_dly_disp_sync_update ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 31;  //  0:30 reserved
	UINT32 dly_force_update                : 1;   //    31
} L9B0_DEB_DLY_DISP_SYNC_UPDATE_T;

/*-----------------------------------------------------------------------------
	0x10c8 deb_dly_disp_sync_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_active                        : 1;   //     0
	UINT32 v_active                        : 1;   //     1
} L9B0_DEB_DLY_DISP_SYNC_CTRL_T;

/*-----------------------------------------------------------------------------
	0x10cc deb_def_disp_sync_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_def_fb_pe1                  : 1;   //     0
	UINT32 deb_def_fb_ov                   : 1;   //     1
	UINT32 deb_def_output                  : 1;   //     2
} L9B0_DEB_DEF_DISP_SYNC_SEL_T;

/*-----------------------------------------------------------------------------
	0x10d0 deb_ov_pic_start_dly_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_ov_pic_start_dly_en         : 1;   //     0
	UINT32                                 : 15;  //  1:15 reserved
	UINT32 pic_end_g1_c_force_en           : 1;   //    16
	UINT32 pic_end_g1_c_force_value        : 1;   //    17
} L9B0_DEB_OV_PIC_START_DLY_EN_T;

/*-----------------------------------------------------------------------------
	0x10d4 deb_pic_init_g1_timer_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer_c             : 28;  //  0:27
} L9B0_DEB_PIC_INIT_G1_TIMER_C_T;

/*-----------------------------------------------------------------------------
	0x10f8 deb_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done              : 1;   //    12
} L9B0_DEB_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x10fc deb_mg_ls_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_ls_override_mifb            : 1;   //     0
	UINT32 deb_ls_override_pe1_l           : 1;   //     1
	UINT32 deb_ls_override_ov_l            : 1;   //     2
	UINT32 deb_ls_override_sm_l            : 1;   //     3
	UINT32                                 : 12;  //  4:15 reserved
	UINT32 deb_mg_override_mifb            : 1;   //    16
	UINT32 deb_mg_override_pe1_l           : 1;   //    17
	UINT32 deb_mg_override_ov_l            : 1;   //    18
	UINT32 deb_mg_override_sm_l            : 1;   //    19
} L9B0_DEB_MG_LS_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2000 dec_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                     : 1;   //     0
	UINT32 pic_init_g1                     : 1;   //     1
	UINT32 pic_init_g2                     : 1;   //     2
} L9B0_DEC_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x2004 dec_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                    : 1;   //     0
	UINT32 pic_start_g1                    : 1;   //     1
	UINT32 pic_start_g2                    : 1;   //     2
} L9B0_DEC_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x2008 dec_smux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 o_c_fmt                         : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 i_c_fmt                         : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 dec3d_mux_sel                   : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 prew_mux_sel                    : 1;   //    12
	UINT32 d3_lr_sel                       : 1;   //    13
	UINT32                                 : 2;   // 14:15 reserved
	UINT32 cvi_mux_sel                     : 2;   // 16:17
	UINT32                                 : 2;   // 18:19 reserved
	UINT32 nline_inc                       : 1;   //    20
	UINT32                                 : 2;   // 21:22 reserved
	UINT32 wr_disalbe                      : 1;   //    23
	UINT32 fieldid                         : 1;   //    24
	UINT32 size                            : 1;   //    25
	UINT32                                 : 5;   // 26:30 reserved
	UINT32 pr_sq                           : 1;   //    31
} L9B0_DEC_SMUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x200c dec_smux_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize                           : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 vsize                           : 13;  // 16:28
} L9B0_DEC_SMUX_SIZE_T;

/*-----------------------------------------------------------------------------
	0x2010 dec_mvi_v_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_vsize                       : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 mvi_vblank                      : 12;  // 16:27
} L9B0_DEC_MVI_V_INFO_T;

/*-----------------------------------------------------------------------------
	0x2014 dec_mvi_h_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_hsize                       : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 mvi_hblank                      : 12;  // 16:27
} L9B0_DEC_MVI_H_INFO_T;

/*-----------------------------------------------------------------------------
	0x2018 dec_mvi_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_i_c_fmt                     : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 mvi_field                       : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 mvi_pr_sq                       : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 mvi_cvi_stride                  : 1;   //    12
} L9B0_DEC_MVI_CTRL_T;

/*-----------------------------------------------------------------------------
	0x201c dec_msrc_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 m_trans_mask_en                 : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 m_cvi_select                    : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 m_mvi_select                    : 1;   //     8
	UINT32 m_mvi_sync_select               : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 m_mvi_cvi_select                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 m_cvia_vsync_inv                : 1;   //    16
	UINT32 m_cvib_vsync_inv                : 1;   //    17
	UINT32 m_vdec_vsync_inv                : 1;   //    18
	UINT32 m_mem_vsync_inv                 : 1;   //    19
	UINT32 m_disp_sync_inv                 : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 m_disp_select                   : 1;   //    24
	UINT32 m_cvia_sync_sel                 : 1;   //    25
	UINT32 m_cvib_sync_sel                 : 1;   //    26
	UINT32                                 : 1;   //    27 reserved
	UINT32 m_sync_manual_delay_en          : 1;   //    28
	UINT32                                 : 2;   // 29:30 reserved
	UINT32 m_ignore_src_vsync_fal          : 1;   //    31
} L9B0_DEC_MSRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2020 dec_msrc_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_msrc_sync_dly               : 28;  //  0:27
} L9B0_DEC_MSRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x2024 dec_mem0_sync_period ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_mem0_sync_period            : 28;  //  0:27
} L9B0_DEC_MEM0_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
	0x2028 dec_mem1_sync_period ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_mem1_sync_period            : 28;  //  0:27
} L9B0_DEC_MEM1_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
	0x202c dec_ssmux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sub_o_c_fmt                     : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 sub_i_c_fmt                     : 3;   //  4: 6
	UINT32                                 : 1;   //     7 reserved
	UINT32 sub_src_mux_sel                 : 2;   //  8: 9
} L9B0_DEC_SSMUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2030 dec_ssrc_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 s_trans_mask_en                 : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 s_cvi_select                    : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 s_mvi_select                    : 1;   //     8
	UINT32 s_mvi_sync_select               : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 s_mvi_cvi_select                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 s_cvia_vsync_inv                : 1;   //    16
	UINT32 s_cvib_vsync_inv                : 1;   //    17
	UINT32 s_vdec_vsync_inv                : 1;   //    18
	UINT32 s_mem_vsync_inv                 : 1;   //    19
	UINT32 s_disp_sync_inv                 : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 s_disp_select                   : 1;   //    24
	UINT32 s_cvia_sync_sel                 : 1;   //    25
	UINT32 s_cvib_sync_sel                 : 1;   //    26
	UINT32                                 : 1;   //    27 reserved
	UINT32 s_sync_manual_delay_en          : 1;   //    28
	UINT32                                 : 2;   // 29:30 reserved
	UINT32 s_ignore_src_vsync_fal          : 1;   //    31
} L9B0_DEC_SSRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2034 dec_ssrc_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_ssrc_sync_dly               : 28;  //  0:27
} L9B0_DEC_SSRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x2038 dec_md_csc_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load_md_csc_coef                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 md_csc_en                       : 1;   //     4
} L9B0_DEC_MD_CSC_CTRL_T;

/*-----------------------------------------------------------------------------
	0x203c dec_md_csc_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_csc_coef1                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 md_csc_coef0                    : 15;  // 16:30
} L9B0_DEC_MD_CSC_COEF0_T;

/*-----------------------------------------------------------------------------
	0x2040 dec_md_csc_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_csc_coef3                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 md_csc_coef2                    : 15;  // 16:30
} L9B0_DEC_MD_CSC_COEF1_T;

/*-----------------------------------------------------------------------------
	0x2044 dec_md_csc_coef2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_csc_coef5                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 md_csc_coef4                    : 15;  // 16:30
} L9B0_DEC_MD_CSC_COEF2_T;

/*-----------------------------------------------------------------------------
	0x2048 dec_md_csc_coef3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_csc_coef7                    : 15;  //  0:14
	UINT32                                 : 1;   //    15 reserved
	UINT32 md_csc_coef6                    : 15;  // 16:30
} L9B0_DEC_MD_CSC_COEF3_T;

/*-----------------------------------------------------------------------------
	0x204c dec_md_csc_coef4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 16;  //  0:15 reserved
	UINT32 dec_md_csc_coef4                : 15;  // 16:30
} L9B0_DEC_MD_CSC_COEF4_T;

/*-----------------------------------------------------------------------------
	0x2050 dec_md_csc_offset0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_csc_ofst1                    : 11;  //  0:10
	UINT32                                 : 5;   // 11:15 reserved
	UINT32 md_csc_ofst0                    : 11;  // 16:26
} L9B0_DEC_MD_CSC_OFFSET0_T;

/*-----------------------------------------------------------------------------
	0x2054 dec_md_csc_offset1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_csc_ofst3                    : 11;  //  0:10
	UINT32                                 : 5;   // 11:15 reserved
	UINT32 md_csc_ofst2                    : 11;  // 16:26
} L9B0_DEC_MD_CSC_OFFSET1_T;

/*-----------------------------------------------------------------------------
	0x2058 dec_md_csc_offset2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 md_csc_ofst5                    : 11;  //  0:10
	UINT32                                 : 5;   // 11:15 reserved
	UINT32 md_csc_ofst4                    : 11;  // 16:26
} L9B0_DEC_MD_CSC_OFFSET2_T;

/*-----------------------------------------------------------------------------
	0x205c dec_smux_ro_lcnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_smux_ro_lcnt                : 12;  //  0:11
} L9B0_DEC_SMUX_RO_LCNT_T;

/*-----------------------------------------------------------------------------
	0x2060 dec_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                 : 8;   //  0: 7
	UINT32                                 : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                      : 10;  // 16:25
} L9B0_DEC_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2064 dec_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_en                          : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 tnr_en                          : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 pe0_en                          : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 prew_en                         : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 smux_en                         : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 mvi_en                          : 1;   //    20
	UINT32                                 : 3;   // 21:23 reserved
	UINT32 ss_en                           : 1;   //    24
	UINT32                                 : 3;   // 25:27 reserved
	UINT32 ssm_en                          : 1;   //    28
} L9B0_DEC_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x2068 dec_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0_timer               : 28;  //  0:27
} L9B0_DEC_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x206c dec_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer               : 28;  //  0:27
} L9B0_DEC_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x2070 dec_pic_init_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g2_timer               : 28;  //  0:27
} L9B0_DEC_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
	0x2074 dec_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 5;   //  0: 4
	UINT32 pic_end_g1                      : 7;   //  5:11
	UINT32 pic_end_g2                      : 3;   // 12:14
} L9B0_DEC_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x2078 dec_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 1;   //     0
	UINT32 pic_end_g1                      : 1;   //     1
	UINT32 pic_end_g2                      : 1;   //     2
	UINT32 pe0_intr                        : 1;   //     3
	UINT32 smux_ow_intr                    : 1;   //     4
	UINT32                                 : 11;  //  5:15 reserved
	UINT32 ssrc_intr                       : 1;   //    16
	UINT32                                 : 6;   // 17:22 reserved
	UINT32 msrc_intr                       : 1;   //    23
} L9B0_DEC_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x207c dec_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_intr_mask                   : 32;  //  0:31
} L9B0_DEC_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x2080 dec_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_intr_mux                    : 32;  //  0:31
} L9B0_DEC_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x2084 dec_msrc_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_msrc_intr_time_stp          : 32;  //  0:31
} L9B0_DEC_MSRC_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x2088 dec_ssrc_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_ssrc_intr_time_stp          : 32;  //  0:31
} L9B0_DEC_SSRC_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x208c dec_addr_sw_de_sav ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 dec_addr_sav_bus                : 7;   //  3: 9
	UINT32                                 : 6;   // 10:15 reserved
	UINT32 dec_addr_default_bus            : 2;   // 16:17
	UINT32                                 : 6;   // 18:23 reserved
	UINT32 dec_addr_de_bus                 : 6;   // 24:29
} L9B0_DEC_ADDR_SW_DE_SAV_T;

/*-----------------------------------------------------------------------------
	0x2090 dec_addr_sw_cpu_gpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 dec_addr_gpu_bus                : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 dec_addr_gpu_logic              : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 dec_addr_cpu_h_bus              : 4;   // 24:27
} L9B0_DEC_ADDR_SW_CPU_GPU_T;

/*-----------------------------------------------------------------------------
	0x2094 dec_addr_sw_cpu_shadow ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 dec_addr_shadow_bus             : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 dec_addr_shadow_logic           : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 dec_addr_cpu_l_bus              : 6;   // 24:29
} L9B0_DEC_ADDR_SW_CPU_SHADOW_T;

/*-----------------------------------------------------------------------------
	0x2098 dec_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done              : 1;   //    12
} L9B0_DEC_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x20a0 dec_smux_size_i ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_i                         : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 vsize_i                         : 13;  // 16:28
} L9B0_DEC_SMUX_SIZE_I_T;

/*-----------------------------------------------------------------------------
	0x20c0 dec_dea_mvi_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_h_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 y_h_width                       : 12;  // 16:27
	UINT32                                 : 3;   // 28:30 reserved
	UINT32 mvi_3d_ctrl_en                  : 1;   //    31
} L9B0_DEC_DEA_MVI_CTRL_0_T;

/*-----------------------------------------------------------------------------
	0x20c4 dec_dea_mvi_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_h_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 c_h_width                       : 12;  // 16:27
} L9B0_DEC_DEA_MVI_CTRL_1_T;

/*-----------------------------------------------------------------------------
	0x20c8 dec_dea_mvi_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_v_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 y_v_height                      : 12;  // 16:27
} L9B0_DEC_DEA_MVI_CTRL_2_T;

/*-----------------------------------------------------------------------------
	0x20cc dec_dea_mvi_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_v_offset                      : 12;  //  0:11
	UINT32                                 : 4;   // 12:15 reserved
	UINT32 c_v_height                      : 12;  // 16:27
} L9B0_DEC_DEA_MVI_CTRL_3_T;

/*-----------------------------------------------------------------------------
	0x20d0 dec_dea_mvi_ctrl_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_sub_sample_step               : 8;   //  0: 7
	UINT32 y_h_even_line_sub_sample_offset : 8;   //  8:15
	UINT32                                 : 8;   // 16:23 reserved
	UINT32 y_h_odd_line_sub_sample_offset  : 8;   // 24:31
} L9B0_DEC_DEA_MVI_CTRL_4_T;

/*-----------------------------------------------------------------------------
	0x20d4 dec_dea_mvi_ctrl_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 8;   //  0: 7 reserved
	UINT32 c_h_even_line_sub_sample_offset : 8;   //  8:15
	UINT32                                 : 8;   // 16:23 reserved
	UINT32 c_h_odd_line_sub_sample_offset  : 8;   // 24:31
} L9B0_DEC_DEA_MVI_CTRL_5_T;

/*-----------------------------------------------------------------------------
	0x20d8 dec_dea_mvi_ctrl_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_sub_sample_step               : 8;   //  0: 7
	UINT32 y_v_sub_sample_offset           : 8;   //  8:15
	UINT32                                 : 8;   // 16:23 reserved
	UINT32 c_v_sub_sample_offset           : 8;   // 24:31
} L9B0_DEC_DEA_MVI_CTRL_6_T;

/*-----------------------------------------------------------------------------
	0x20e0 dec_pic_start_delay_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_delay_mvi             : 1;   //     0
	UINT32 pic_start_delay_mvi_y_rd        : 1;   //     1
	UINT32 pic_start_delay_mvi_c_rd        : 1;   //     2
	UINT32 pic_start_delay_smux            : 1;   //     3
	UINT32 pic_start_delay_prew_y_rd       : 1;   //     4
	UINT32 pic_start_delay_prew_c_rd       : 1;   //     5
	UINT32 pic_start_delay_prew_y_wd       : 1;   //     6
	UINT32 pic_start_delay_prew_c_wd       : 1;   //     7
	UINT32 pic_start_delay_pe0             : 1;   //     8
	UINT32 pic_start_delay_tnr0_y_rd       : 1;   //     9
	UINT32 pic_start_delay_tnr_c_rd        : 1;   //    10
	UINT32 pic_start_delay_tnr_y_wd        : 1;   //    11
	UINT32 pic_start_delay_tnr_c_wd        : 1;   //    12
	UINT32 pic_start_delay_ipc0_y_rd       : 1;   //    13
	UINT32 pic_start_delay_ipc1_y_rd       : 1;   //    14
	UINT32 pic_start_delay_ipc_c_rd        : 1;   //    15
	UINT32 pic_start_delay_ss              : 1;   //    16
	UINT32 pic_start_delay_ss_y_wd         : 1;   //    17
	UINT32 pic_start_delay_ss_c_wd         : 1;   //    18
	UINT32 pic_start_delay_ss_y_rd         : 1;   //    19
	UINT32 pic_start_delay_ss_c_rd         : 1;   //    20
} L9B0_DEC_PIC_START_DELAY_CTRL_T;

/*-----------------------------------------------------------------------------
	0x20e4 dec_pic_start_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0_timer              : 28;  //  0:27
} L9B0_DEC_PIC_START_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x20e8 dec_pic_start_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g1_timer              : 28;  //  0:27
} L9B0_DEC_PIC_START_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x20ec dec_pic_start_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g2_timer              : 28;  //  0:27
} L9B0_DEC_PIC_START_G2_TIMER_T;

/*-----------------------------------------------------------------------------
	0x20f4 dec_pic_end_force ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_pic_end_g0_force            : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 dea_pic_end_g0_force_en         : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 dea_pic_end_g1_force            : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 dea_pic_end_g1_force_en         : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 dea_pic_end_g2_force            : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 dea_pic_end_g2_force_en         : 1;   //    20
} L9B0_DEC_PIC_END_FORCE_T;

/*-----------------------------------------------------------------------------
	0x20fc dec_mg_ls_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_ls_override_mifc            : 1;   //     0
	UINT32 dec_ls_override_pe0_r           : 1;   //     1
	UINT32 dec_ls_override_smux_r          : 1;   //     2
	UINT32 dec_ls_override_ss              : 1;   //     3
	UINT32                                 : 12;  //  4:15 reserved
	UINT32 dec_mg_override_mifc            : 1;   //    16
	UINT32 dec_mg_override_pe0_r           : 1;   //    17
	UINT32 dec_mg_override_smux_r          : 1;   //    18
	UINT32 dec_mg_override_ss              : 1;   //    19
} L9B0_DEC_MG_LS_CTRL_T;

/*-----------------------------------------------------------------------------
	0x3000 ded_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                     : 1;   //     0
	UINT32 pic_init_g1                     : 1;   //     1
	UINT32                                 : 21;  //  2:22 reserved
	UINT32 ov_auto_init                    : 1;   //    23
} L9B0_DED_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x3004 ded_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                    : 1;   //     0
	UINT32 pic_start_g1                    : 1;   //     1
} L9B0_DED_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x3024 ded_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                 : 8;   //  0: 7
	UINT32                                 : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                      : 10;  // 16:25
} L9B0_DED_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x3028 ded_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 8;   //  0: 7 reserved
	UINT32 ov_en                           : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 sm_en                           : 1;   //    12
} L9B0_DED_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x302c ded_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ded_pic_init_g0_timer           : 28;  //  0:27
} L9B0_DED_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x3030 ded_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ded_pic_init_g1_timer           : 28;  //  0:27
} L9B0_DED_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x303c ded_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0_info                 : 3;   //  0: 2
	UINT32                                 : 1;   //     3 reserved
	UINT32 pic_end_g1_info                 : 3;   //  4: 6
} L9B0_DED_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x3040 ded_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 1;   //     0
	UINT32 pic_end_g1                      : 1;   //     1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 ov_underflow                    : 1;   //     4
	UINT32                                 : 2;   //  5: 6 reserved
	UINT32 src_pulse                       : 1;   //     7
	UINT32 pic_end_g1_c                    : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_don               : 1;   //    12
	UINT32 gmau_flush_rd_done              : 1;   //    13
} L9B0_DED_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x3044 ded_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 1;   //     0
	UINT32 pic_end_g1                      : 1;   //     1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 ov_underflow                    : 1;   //     4
	UINT32                                 : 2;   //  5: 6 reserved
	UINT32 src_pulse                       : 1;   //     7
	UINT32 pic_end_g1_c                    : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_don               : 1;   //    12
	UINT32 gmau_flush_rd_done              : 1;   //    13
} L9B0_DED_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x3048 ded_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                      : 1;   //     0
	UINT32 pic_end_g1                      : 1;   //     1
	UINT32                                 : 2;   //  2: 3 reserved
	UINT32 ov_underflow                    : 1;   //     4
	UINT32                                 : 2;   //  5: 6 reserved
	UINT32 src_pulse                       : 1;   //     7
	UINT32 pic_end_g1_c                    : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_don               : 1;   //    12
	UINT32 gmau_flush_rd_done              : 1;   //    13
} L9B0_DED_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x3050 ded_addr_sw_de_sav ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 ded_addr_sav_bus                : 7;   //  3: 9
	UINT32                                 : 6;   // 10:15 reserved
	UINT32 ded_addr_default_bus            : 2;   // 16:17
	UINT32                                 : 6;   // 18:23 reserved
	UINT32 ded_addr_de_bus                 : 6;   // 24:29
} L9B0_DED_ADDR_SW_DE_SAV_T;

/*-----------------------------------------------------------------------------
	0x3054 ded_addr_sw_cpu_gpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 ded_addr_gpu_bus                : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 ded_addr_gpu_logic              : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 ded_addr_cpu_h_bus              : 4;   // 24:27
} L9B0_DED_ADDR_SW_CPU_GPU_T;

/*-----------------------------------------------------------------------------
	0x3058 ded_addr_sw_cpu_shadow ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 ded_addr_shadow_bus             : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 ded_addr_shadow_logic           : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 ded_addr_cpu_l_bus              : 6;   // 24:29
} L9B0_DED_ADDR_SW_CPU_SHADOW_T;

/*-----------------------------------------------------------------------------
	0x30c0 ded_dly_disp_sync_params ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_dly                           : 16;  //  0:15
	UINT32 v_dly                           : 16;  // 16:31
} L9B0_DED_DLY_DISP_SYNC_PARAMS_T;

/*-----------------------------------------------------------------------------
	0x30c4 ded_dly_disp_sync_force_update ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset0                        : 16;  //  0:15
	UINT32                                 : 15;  // 16:30 reserved
	UINT32 dly_force_update                : 1;   //    31
} L9B0_DED_DLY_DISP_SYNC_FORCE_UPDATE_T;

/*-----------------------------------------------------------------------------
	0x30c8 ded_dly_disp_sync_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_active                        : 1;   //     0
	UINT32 v_active                        : 1;   //     1
} L9B0_DED_DLY_DISP_SYNC_CTRL_T;

/*-----------------------------------------------------------------------------
	0x30cc ded_def_disp_sync_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ded_def_pe1_r                   : 1;   //     0
	UINT32 deb_def_ov_r                    : 1;   //     1
} L9B0_DED_DEF_DISP_SYNC_SEL_T;

/*-----------------------------------------------------------------------------
	0x30d0 ded_ov_pic_start_dly_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ded_ov_pic_start_dly_en         : 1;   //     0
	UINT32                                 : 15;  //  1:15 reserved
	UINT32 pic_end_g1_c_force_en           : 1;   //    16
	UINT32 pic_end_g1_c_force_value        : 1;   //    17
} L9B0_DED_OV_PIC_START_DLY_EN_T;

/*-----------------------------------------------------------------------------
	0x30d4 ded_pic_init_g1_timer_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer_c             : 28;  //  0:27
} L9B0_DED_PIC_INIT_G1_TIMER_C_T;

/*-----------------------------------------------------------------------------
	0x30e0 ded_dly_disp_v_porch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync_bp                        : 16;  //  0:15
	UINT32 vsync_fp                        : 16;  // 16:31
} L9B0_DED_DLY_DISP_V_PORCH_T;

/*-----------------------------------------------------------------------------
	0x30e4 ded_dly_disp_vs_va ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_sync_va                    : 16;  //  0:15
	UINT32 vsync                           : 16;  // 16:31
} L9B0_DED_DLY_DISP_VS_VA_T;

/*-----------------------------------------------------------------------------
	0x30e8 ded_dly_disp_h_porch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync_bp                        : 16;  //  0:15
	UINT32 hsync_fp                        : 16;  // 16:31
} L9B0_DED_DLY_DISP_H_PORCH_T;

/*-----------------------------------------------------------------------------
	0x30ec ded_dly_disp_hs_ha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_sync_ha                    : 16;  //  0:15
	UINT32 hsync                           : 16;  // 16:31
} L9B0_DED_DLY_DISP_HS_HA_T;

/*-----------------------------------------------------------------------------
	0x30f8 ded_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done              : 1;   //    12
} L9B0_DED_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x30fc ded_mg_ls_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ded_ls_override_mifd            : 1;   //     0
	UINT32 ded_ls_override_pe1_r           : 1;   //     1
	UINT32 ded_ls_override_sm_r            : 1;   //     2
	UINT32 ded_ls_override_ov_r            : 1;   //     3
	UINT32                                 : 12;  //  4:15 reserved
	UINT32 ded_mg_override_mifd            : 1;   //    16
	UINT32 ded_mg_override_pe1_r           : 1;   //    17
	UINT32 ded_mg_override_sm_r            : 1;   //    18
	UINT32 ded_mg_override_ov_r            : 1;   //    19
} L9B0_DED_MG_LS_CTRL_T;

/*-----------------------------------------------------------------------------
	0x4000 dec_de_intr_flag_mcu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dee_intr_mcu                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 deb_dee_intr_mcu                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 dec_dee_intr_mcu                : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 ded_dee_intr_mcu                : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 dee_dee_intr_mcu                : 1;   //    16
	UINT32                                 : 3;   // 17:19 reserved
	UINT32 def_dee_intr_mcu                : 1;   //    20
} L9B0_DEC_DE_INTR_FLAG_MCU_T;

/*-----------------------------------------------------------------------------
	0x4004 dec_de_intr_flag_cpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dee_intr_cpu                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 deb_dee_intr_cpu                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 dec_dee_intr_cpu                : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 ded_dee_intr_cpu                : 1;   //    12
	UINT32                                 : 7;   // 13:19 reserved
	UINT32 def_dee_intr_cpu                : 1;   //    20
} L9B0_DEC_DE_INTR_FLAG_CPU_T;

/*-----------------------------------------------------------------------------
	0x4008 dee_cvi_mux_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvib_sel                        : 2;   //  0: 1
	UINT32 cvia_sel                        : 2;   //  2: 3
	UINT32 extb_type                       : 1;   //     4
	UINT32 exta_type                       : 1;   //     5
	UINT32 cvd_input_sel                   : 1;   //     6
} L9B0_DEE_CVI_MUX_SEL_T;

/*-----------------------------------------------------------------------------
	0x400c dee_pe0_hif_offset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 28;  //  0:27 reserved
	UINT32 pe0_hif_offset_en               : 1;   //    28
} L9B0_DEE_PE0_HIF_OFFSET_T;

/*-----------------------------------------------------------------------------
	0x4010 dee_sm_hif_offset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 28;  //  0:27 reserved
	UINT32 sm_hif_offset_en                : 1;   //    28
} L9B0_DEE_SM_HIF_OFFSET_T;

/*-----------------------------------------------------------------------------
	0x4014 dee_pe1_hif_offset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 28;  //  0:27 reserved
	UINT32 pe1_hif_offset_en               : 1;   //    28
} L9B0_DEE_PE1_HIF_OFFSET_T;

/*-----------------------------------------------------------------------------
	0x4018 dee_cvd_addr_sw_de_sav ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 cvd_addr_sav_bus                : 7;   //  3: 9
	UINT32                                 : 6;   // 10:15 reserved
	UINT32 mcu_addr_default_bus            : 2;   // 16:17
	UINT32                                 : 6;   // 18:23 reserved
	UINT32 cvd_addr_de_bus                 : 6;   // 24:29
} L9B0_DEE_CVD_ADDR_SW_DE_SAV_T;

/*-----------------------------------------------------------------------------
	0x401c dee_cvd_addr_sw_cpu_gpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 cvd_addr_gpu_bus                : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 cvd_addr_gpu_logic              : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 cvd_addr_cpu_h_bus              : 4;   // 24:27
} L9B0_DEE_CVD_ADDR_SW_CPU_GPU_T;

/*-----------------------------------------------------------------------------
	0x4020 dee_cvd_addr_sw_cpu_shadow ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 cvd_addr_shadow_bus             : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 cvd_addr_shadow_logic           : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 cvd_addr_cpu_l_bus              : 6;   // 24:29
} L9B0_DEE_CVD_ADDR_SW_CPU_SHADOW_T;

/*-----------------------------------------------------------------------------
	0x4024 dee_mcu_addr_sw_de_sav ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 mcu_addr_sav_bus                : 7;   //  3: 9
	UINT32                                 : 6;   // 10:15 reserved
	UINT32 mcu_addr_default_bus            : 2;   // 16:17
	UINT32                                 : 6;   // 18:23 reserved
	UINT32 mcu_addr_de_bus                 : 6;   // 24:29
} L9B0_DEE_MCU_ADDR_SW_DE_SAV_T;

/*-----------------------------------------------------------------------------
	0x4028 dee_mcu_addr_sw_cpu_gpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 mcu_addr_gpu_bus                : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 mcu_addr_gpu_logic              : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 mcu_addr_cpu_h_bus              : 4;   // 24:27
} L9B0_DEE_MCU_ADDR_SW_CPU_GPU_T;

/*-----------------------------------------------------------------------------
	0x402c dee_mcu_addr_sw_cpu_shadow ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 mcu_addr_shadow_bus             : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 mcu_addr_shadow_logic           : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 mcu_addr_cpu_l_bus              : 6;   // 24:29
} L9B0_DEE_MCU_ADDR_SW_CPU_SHADOW_T;

/*-----------------------------------------------------------------------------
	0x4030 dee_mcu_addr_window ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 12;  //  0:11 reserved
	UINT32 mcu_win_lower                   : 4;   // 12:15
	UINT32                                 : 12;  // 16:27 reserved
	UINT32 mcu_win_upper                   : 4;   // 28:31
} L9B0_DEE_MCU_ADDR_WINDOW_T;

/*-----------------------------------------------------------------------------
	0x4034 dee_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dee_src_cvd                     : 1;   //     0
} L9B0_DEE_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x4038 dee_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dee_cvd_intr_mask               : 1;   //     0
} L9B0_DEE_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x403c dee_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done              : 1;   //    12
} L9B0_DEE_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x40fc dee_mg_ls_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dee_ls_override_cvd_b00         : 1;   //     0
	UINT32                                 : 15;  //  1:15 reserved
	UINT32 dee_ls_override_cvd_b16         : 1;   //    16
} L9B0_DEE_MG_LS_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5000 def_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 2;   //  0: 1 reserved
	UINT32 pic_inti_g2                     : 1;   //     2
	UINT32 pic_init_g3                     : 1;   //     3
	UINT32                                 : 23;  //  4:26 reserved
	UINT32 osd_auto_init                   : 1;   //    27
	UINT32                                 : 3;   // 28:30 reserved
	UINT32 atop_auto_init                  : 1;   //    31
} L9B0_DEF_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x5004 def_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 2;   //  0: 1 reserved
	UINT32 pic_start_g2                    : 1;   //     2
	UINT32 pic_start_g3                    : 1;   //     3
} L9B0_DEF_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x5008 def_de_venc_if ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 venc_vsync                      : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 venc_sel                        : 1;   //     4
} L9B0_DEF_DE_VENC_IF_T;

/*-----------------------------------------------------------------------------
	0x500c def_dpath_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 t3_mux_sel                      : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 fb_mux_sel                      : 1;   //     4
} L9B0_DEF_DPATH_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5010 def_cve_param0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vertical_back_period            : 8;   //  0: 7
	UINT32 vertical_sync_period            : 8;   //  8:15
	UINT32 vertical_front_period           : 8;   // 16:23
	UINT32 vsync_polarity                  : 1;   //    24
} L9B0_DEF_CVE_PARAM0_T;

/*-----------------------------------------------------------------------------
	0x5014 def_cve_param1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 horizontal_back_period          : 8;   //  0: 7
	UINT32 horizontal_sync_period          : 8;   //  8:15
	UINT32 horizontal_front_period         : 8;   // 16:23
	UINT32 hsync_polarity                  : 1;   //    24
} L9B0_DEF_CVE_PARAM1_T;

/*-----------------------------------------------------------------------------
	0x5018 def_cve_param2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_hoffset1                      : 11;  //  0:10
	UINT32 v_hoffset0                      : 11;  // 11:21
	UINT32                                 : 2;   // 22:23 reserved
	UINT32 field_id_polarity               : 1;   //    24
} L9B0_DEF_CVE_PARAM2_T;

/*-----------------------------------------------------------------------------
	0x501c def_cve_param3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cve_sync_ha                     : 11;  //  0:10
	UINT32                                 : 5;   // 11:15 reserved
	UINT32 cve_sync_va                     : 11;  // 16:26
} L9B0_DEF_CVE_PARAM3_T;

/*-----------------------------------------------------------------------------
	0x5020 def_cve_pulse_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_cve_pulse_dly               : 28;  //  0:27
} L9B0_DEF_CVE_PULSE_DLY_T;

/*-----------------------------------------------------------------------------
	0x5024 def_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                 : 8;   //  0: 7
	UINT32                                 : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                      : 10;  // 16:25
} L9B0_DEF_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5028 def_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 atop_en                         : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 osd_en                          : 1;   //     4
} L9B0_DEF_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x5034 def_pic_init_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_pic_init_g2_timer           : 28;  //  0:27
} L9B0_DEF_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
	0x5038 def_pic_init_g3_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_pic_init_g3_timer           : 28;  //  0:27
} L9B0_DEF_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
	0x503c def_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 8;   //  0: 7 reserved
	UINT32 pic_end_g2_info                 : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 pic_end_g3_info                 : 1;   //    12
} L9B0_DEF_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x5040 def_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 2;   //  0: 1 reserved
	UINT32 pic_end_g2                      : 1;   //     2
	UINT32 pic_end_g3                      : 1;   //     3
	UINT32                                 : 1;   //     4 reserved
	UINT32 cve_pulse                       : 1;   //     5
	UINT32 cve_va_pulse                    : 1;   //     6
	UINT32                                 : 2;   //  7: 8 reserved
	UINT32 cve_va_fal_pulse                : 1;   //     9
	UINT32                                 : 2;   // 10:11 reserved
	UINT32 gmau_flush_wr_done_ris          : 1;   //    12
	UINT32 gmau_flush_rd_done_ris          : 1;   //    13
} L9B0_DEF_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x5044 def_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_intr_mask                   : 16;  //  0:15
} L9B0_DEF_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x5048 def_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_intr_mux                    : 16;  //  0:15
} L9B0_DEF_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x504c def_cve_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_cve_intr_time_stp_f         : 32;   // 31: 0
} L9B0_DEF_CVE_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x5050 def_addr_sw_de_sav ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 def_addr_sav_bus                : 7;   //  3: 9
	UINT32                                 : 6;   // 10:15 reserved
	UINT32 def_addr_default_bus            : 2;   // 16:17
	UINT32                                 : 6;   // 18:23 reserved
	UINT32 def_addr_de_bus                 : 6;   // 24:29
} L9B0_DEF_ADDR_SW_DE_SAV_T;

/*-----------------------------------------------------------------------------
	0x5054 def_addr_sw_cpu_gpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 def_addr_gpu_bus                : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 def_addr_gpu_logic              : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 def_addr_cpu_h_bus              : 4;   // 24:27
} L9B0_DEF_ADDR_SW_CPU_GPU_T;

/*-----------------------------------------------------------------------------
	0x5058 def_addr_sw_cpu_shadow ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                 : 3;   //  0: 2 reserved
	UINT32 def_addr_shadow_bus             : 7;   //  3: 9
	UINT32                                 : 5;   // 10:14 reserved
	UINT32 def_addr_shadow_logic           : 5;   // 15:19
	UINT32                                 : 4;   // 20:23 reserved
	UINT32 def_addr_cpu_l_bus              : 6;   // 24:29
} L9B0_DEF_ADDR_SW_CPU_SHADOW_T;

/*-----------------------------------------------------------------------------
	0x50f8 def_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                : 1;   //     0
	UINT32                                 : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                : 1;   //     4
	UINT32                                 : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done              : 1;   //     8
	UINT32                                 : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done              : 1;   //    12
} L9B0_DEF_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x50fc def_mg_ls_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_ls_override_miff            : 1;   //     0
	UINT32 def_ls_override_d3pp            : 1;   //     1
	UINT32 def_ls_override_osd             : 1;   //     2
	UINT32 def_ls_override_atop            : 1;   //     3
	UINT32                                 : 12;  //  4:15 reserved
	UINT32 def_mg_override_miff            : 1;   //    16
	UINT32 def_mg_override_d3pp            : 1;   //    17
	UINT32 def_mg_override_osd             : 1;   //    18
	UINT32 def_mg_override_atop            : 1;   //    19
} L9B0_DEF_MG_LS_CTRL_T;

typedef struct {
	L9B0_DEA_CHA_INFO_T                     dea_cha_info;                            // 0x0000
	L9B0_DEA_CHB_INFO_T                     dea_chb_info;                            // 0x0004
	L9B0_DEA_PIC_INIT_T                     dea_pic_init;                            // 0x0008
	L9B0_DEA_PIC_START_T                    dea_pic_start;                           // 0x000c
	L9B0_DEA_SMUX_CTRL_T                    dea_smux_ctrl;                           // 0x0010
	L9B0_DEA_SMUX_SIZE_T                    dea_smux_size;                           // 0x0014
	L9B0_DEA_MVI_V_INFO_T                   dea_mvi_v_info;                          // 0x0018
	L9B0_DEA_MVI_H_INFO_T                   dea_mvi_h_info;                          // 0x001c
	L9B0_DEA_MVI_CTRL_T                     dea_mvi_ctrl;                            // 0x0020
	L9B0_DEA_MSRC_SYNC_MUX_CTRL_T           dea_msrc_sync_mux_ctrl;                  // 0x0024
	L9B0_DEA_MSRC_SYNC_DLY_T                dea_msrc_sync_dly;                       // 0x0028
	L9B0_DEA_MEM_SYNC_PERIOD_T              dea_mem_sync_period;                     // 0x002c
	L9B0_DEA_DCO_MFC_T                      dea_dco_mfc;                             // 0x0030
	L9B0_DEA_DCO_DFC_T                      dea_dco_dfc;                             // 0x0034
	L9B0_DEA_DCO_DFLC_T                     dea_dco_dflc;                            // 0x0038
	L9B0_DEA_DCO_FCW_T                      dea_dco_fcw;                             // 0x003c
	L9B0_DEA_SMUX_RO_LCNT_T                 dea_smux_ro_lcnt;                        // 0x0040
	L9B0_DEA_GMAU_CTRL_T                    dea_gmau_ctrl;                           // 0x0044
	L9B0_DEA_PIC_END_EN_T                   dea_pic_end_en;                          // 0x0048
	L9B0_DEA_PIC_INIT_G0_TIMER_T            dea_pic_init_g0_timer;                   // 0x004c
	L9B0_DEA_PIC_INIT_G1_TIMER_T            dea_pic_init_g1_timer;                   // 0x0050
	L9B0_DEA_PIC_END_INFO_T                 dea_pic_end_info;                        // 0x0054
	L9B0_DEA_INTR_REG_T                     dea_intr_reg;                            // 0x0058
	L9B0_DEA_INTR_MASK_T                    dea_intr_mask;                           // 0x005c
	L9B0_DEA_INTR_MUX_T                     dea_intr_mux;                            // 0x0060
	L9B0_DEA_SRC_INTR_TIME_STP_T            dea_src_intr_time_stp;                   // 0x0064
	L9B0_DE_GPIO_MUX_T                      de_gpio_mux;                             // 0x0068
	L9B0_DEA_ADDR_SW_DE_SAV_T               dea_addr_sw_de_sav;                      // 0x006c
	L9B0_DEA_ADDR_SW_CPU_GPU_T              dea_addr_sw_cpu_gpu;                     // 0x0070
	L9B0_DEA_ADDR_SW_CPU_SHADOW_T           dea_addr_sw_cpu_shadow;                  // 0x0074
	UINT32                                  reserved0;                               // 0x0078
	L9B0_DE_VERSION_T                       de_version;                              // 0x007c
	L9B0_DEA_SMUX_SIZE_I_T                  dea_smux_size_i;                         // 0x0080
	UINT32                                  reserved1[15];                           // 0x0084~0x00bc
	L9B0_DEA_DEA_MVI_CTRL_0_T               dea_dea_mvi_ctrl_0;                      // 0x00c0
	L9B0_DEA_DEA_MVI_CTRL_1_T               dea_dea_mvi_ctrl_1;                      // 0x00c4
	L9B0_DEA_DEA_MVI_CTRL_2_T               dea_dea_mvi_ctrl_2;                      // 0x00c8
	L9B0_DEA_DEA_MVI_CTRL_3_T               dea_dea_mvi_ctrl_3;                      // 0x00cc
	L9B0_DEA_DEA_MVI_CTRL_4_T               dea_dea_mvi_ctrl_4;                      // 0x00d0
	L9B0_DEA_DEA_MVI_CTRL_5_T               dea_dea_mvi_ctrl_5;                      // 0x00d4
	L9B0_DEA_DEA_MVI_CTRL_6_T               dea_dea_mvi_ctrl_6;                      // 0x00d8
	UINT32                                  reserved2;                               // 0x00dc
	L9B0_DEA_PIC_START_DELAY_CTRL_T         dea_pic_start_delay_ctrl;                // 0x00e0
	L9B0_DEA_PIC_START_G0_TIMER_T           dea_pic_start_g0_timer;                  // 0x00e4
	L9B0_DEA_PIC_START_G1_TIMER_T           dea_pic_start_g1_timer;                  // 0x00e8
	UINT32                                  reserved3[2];                            // 0x00ec~0x00f0
	L9B0_DEA_PIC_END_FORCE_T                dea_pic_end_force;                       // 0x00f4
	L9B0_DEA_GMAU_FLUSH_T                   dea_gmau_flush;                          // 0x00f8
	L9B0_DEA_MG_LS_CTRL_T                   dea_mg_ls_ctrl;                          // 0x00fc
} DE_DEA_REG_L9B0_T;

typedef struct {
	L9B0_DEB_PIC_INIT_T                     deb_pic_init;                            // 0x1000
	L9B0_DEB_PIC_START_T                    deb_pic_start;                           // 0x1004
	L9B0_DEB_DISP_V_PORCH_T                 deb_disp_v_porch;                        // 0x1008
	L9B0_DEB_DISP_VS_VA_T                   deb_disp_vs_va;                          // 0x100c
	L9B0_DEB_DISP_H_PORCH_T                 deb_disp_h_porch;                        // 0x1010
	L9B0_DEB_DISP_HS_HA_T                   deb_disp_hs_ha;                          // 0x1014
	L9B0_DEB_DISP_SYNC_DLY_T                deb_disp_sync_dly;                       // 0x1018
	L9B0_DEB_DISP_PULSE_DLY_T               deb_disp_pulse_dly;                      // 0x101c
	L9B0_DEB_DISP_SYNC_PARAMS_T             deb_disp_sync_params;                    // 0x1020
	UINT32                                  reserved4[2];                            // 0x1024~0x1028
	L9B0_DEB_PWM0_CTRL0_T                   deb_pwm0_ctrl0;                          // 0x102c
	L9B0_DEB_PWM0_CTRL1_T                   deb_pwm0_ctrl1;                          // 0x1030
	L9B0_DEB_PWM1_CTRL0_T                   deb_pwm1_ctrl0;                          // 0x1034
	L9B0_DEB_PWM1_CTRL1_T                   deb_pwm1_ctrl1;                          // 0x1038
	L9B0_DEB_PWM2_CTRL0_T                   deb_pwm2_ctrl0;                          // 0x103c
	L9B0_DEB_PWM2_CTRL1_T                   deb_pwm2_ctrl1;                          // 0x1040
	L9B0_DEB_PWM3_CTRL_T                    deb_pwm3_ctrl;                           // 0x1044
	L9B0_PWM3_0_LOW_T                       pwm3_0_low;                              // 0x1048
	L9B0_PWM3_0_HIGH_T                      pwm3_0_high;                             // 0x104c
	L9B0_PWM3_1_LOW_T                       pwm3_1_low;                              // 0x1050
	L9B0_PWM3_1_HIGH_T                      pwm3_1_high;                             // 0x1054
	L9B0_PWM3_2_LOW_T                       pwm3_2_low;                              // 0x1058
	L9B0_PWM3_2_HIGH_T                      pwm3_2_high;                             // 0x105c
	L9B0_PWM3_3_LOW_T                       pwm3_3_low;                              // 0x1060
	L9B0_PWM3_3_HIGH_T                      pwm3_3_high;                             // 0x1064
	L9B0_DEB_DPATH_CTRL_T                   deb_dpath_ctrl;                          // 0x1068
	L9B0_DEB_GMAU_CTRL_T                    deb_gmau_ctrl;                           // 0x106c
	L9B0_DEB_PIC_END_EN_T                   deb_pic_end_en;                          // 0x1070
	L9B0_DEB_PIC_INIT_G0_TIMER_T            deb_pic_init_g0_timer;                   // 0x1074
	L9B0_DEB_PIC_INIT_G1_TIMER_T            deb_pic_init_g1_timer;                   // 0x1078
	L9B0_DEB_PIC_END_INFO_T                 deb_pic_end_info;                        // 0x107c
	L9B0_DEB_INTR_REG_T                     deb_intr_reg;                            // 0x1080
	L9B0_DEB_INTR_MASK_T                    deb_intr_mask;                           // 0x1084
	L9B0_DEB_INTR_MUX_T                     deb_intr_mux;                            // 0x1088
	L9B0_DEB_DISP_INTR_TIME_STP_T           deb_disp_intr_time_stp;                  // 0x108c
	L9B0_DEB_ADDR_SW_DE_SAV_T               deb_addr_sw_de_sav;                      // 0x1090
	L9B0_DEB_ADDR_SW_CPU_GPU_T              deb_addr_sw_cpu_gpu;                     // 0x1094
	L9B0_DEB_ADDR_SW_CPU_SHADOW_T           deb_addr_sw_cpu_shadow;                  // 0x1098
	UINT32                                  reserved5;                               // 0x109c
	L9B0_PWM0_V_T                           pwm0_v;                                  // 0x10a0
	L9B0_PWM1_V_T                           pwm1_v;                                  // 0x10a4
	L9B0_PWM2_V_T                           pwm2_v;                                  // 0x10a8
	UINT32                                  reserved6;                               // 0x10ac
	L9B0_PWM0_V_SUB_T                       pwm0_v_sub;                              // 0x10b0
	L9B0_PWM1_V_SUB_T                       pwm1_v_sub;                              // 0x10b4
	L9B0_PWM2_V_SUB_T                       pwm2_v_sub;                              // 0x10b8
	UINT32                                  reserved7;                               // 0x10bc
	L9B0_DEB_DLY_DISP_SYNC_DLY_PARAM_T      deb_dly_disp_sync_dly_param;             // 0x10c0
	L9B0_DEB_DLY_DISP_SYNC_UPDATE_T         deb_dly_disp_sync_update;                // 0x10c4
	L9B0_DEB_DLY_DISP_SYNC_CTRL_T           deb_dly_disp_sync_ctrl;                  // 0x10c8
	L9B0_DEB_DEF_DISP_SYNC_SEL_T            deb_def_disp_sync_sel;                   // 0x10cc
	L9B0_DEB_OV_PIC_START_DLY_EN_T          deb_ov_pic_start_dly_en;                 // 0x10d0
	L9B0_DEB_PIC_INIT_G1_TIMER_C_T          deb_pic_init_g1_timer_c;                 // 0x10d4
	UINT32                                  reserved8[8];                            // 0x10d8~0x10f4
	L9B0_DEB_GMAU_FLUSH_T                   deb_gmau_flush;                          // 0x10f8
	L9B0_DEB_MG_LS_CTRL_T                   deb_mg_ls_ctrl;                          // 0x10fc
} DE_DEB_REG_L9B0_T;

typedef struct {
	L9B0_DEC_PIC_INIT_T                     dec_pic_init;                            // 0x2000
	L9B0_DEC_PIC_START_T                    dec_pic_start;                           // 0x2004
	L9B0_DEC_SMUX_CTRL_T                    dec_smux_ctrl;                           // 0x2008
	L9B0_DEC_SMUX_SIZE_T                    dec_smux_size;                           // 0x200c
	L9B0_DEC_MVI_V_INFO_T                   dec_mvi_v_info;                          // 0x2010
	L9B0_DEC_MVI_H_INFO_T                   dec_mvi_h_info;                          // 0x2014
	L9B0_DEC_MVI_CTRL_T                     dec_mvi_ctrl;                            // 0x2018
	L9B0_DEC_MSRC_SYNC_MUX_CTRL_T           dec_msrc_sync_mux_ctrl;                  // 0x201c
	L9B0_DEC_MSRC_SYNC_DLY_T                dec_msrc_sync_dly;                       // 0x2020
	L9B0_DEC_MEM0_SYNC_PERIOD_T             dec_mem0_sync_period;                    // 0x2024
	L9B0_DEC_MEM1_SYNC_PERIOD_T             dec_mem1_sync_period;                    // 0x2028
	L9B0_DEC_SSMUX_CTRL_T                   dec_ssmux_ctrl;                          // 0x202c
	L9B0_DEC_SSRC_SYNC_MUX_CTRL_T           dec_ssrc_sync_mux_ctrl;                  // 0x2030
	L9B0_DEC_SSRC_SYNC_DLY_T                dec_ssrc_sync_dly;                       // 0x2034
	L9B0_DEC_MD_CSC_CTRL_T                  dec_md_csc_ctrl;                         // 0x2038
	L9B0_DEC_MD_CSC_COEF0_T                 dec_md_csc_coef0;                        // 0x203c
	L9B0_DEC_MD_CSC_COEF1_T                 dec_md_csc_coef1;                        // 0x2040
	L9B0_DEC_MD_CSC_COEF2_T                 dec_md_csc_coef2;                        // 0x2044
	L9B0_DEC_MD_CSC_COEF3_T                 dec_md_csc_coef3;                        // 0x2048
	L9B0_DEC_MD_CSC_COEF4_T                 dec_md_csc_coef4;                        // 0x204c
	L9B0_DEC_MD_CSC_OFFSET0_T               dec_md_csc_offset0;                      // 0x2050
	L9B0_DEC_MD_CSC_OFFSET1_T               dec_md_csc_offset1;                      // 0x2054
	L9B0_DEC_MD_CSC_OFFSET2_T               dec_md_csc_offset2;                      // 0x2058
	L9B0_DEC_SMUX_RO_LCNT_T                 dec_smux_ro_lcnt;                        // 0x205c
	L9B0_DEC_GMAU_CTRL_T                    dec_gmau_ctrl;                           // 0x2060
	L9B0_DEC_PIC_END_EN_T                   dec_pic_end_en;                          // 0x2064
	L9B0_DEC_PIC_INIT_G0_TIMER_T            dec_pic_init_g0_timer;                   // 0x2068
	L9B0_DEC_PIC_INIT_G1_TIMER_T            dec_pic_init_g1_timer;                   // 0x206c
	L9B0_DEC_PIC_INIT_G2_TIMER_T            dec_pic_init_g2_timer;                   // 0x2070
	L9B0_DEC_PIC_END_INFO_T                 dec_pic_end_info;                        // 0x2074
	L9B0_DEC_INTR_REG_T                     dec_intr_reg;                            // 0x2078
	L9B0_DEC_INTR_MASK_T                    dec_intr_mask;                           // 0x207c
	L9B0_DEC_INTR_MUX_T                     dec_intr_mux;                            // 0x2080
	L9B0_DEC_MSRC_INTR_TIME_STP_T           dec_msrc_intr_time_stp;                  // 0x2084
	L9B0_DEC_SSRC_INTR_TIME_STP_T           dec_ssrc_intr_time_stp;                  // 0x2088
	L9B0_DEC_ADDR_SW_DE_SAV_T               dec_addr_sw_de_sav;                      // 0x208c
	L9B0_DEC_ADDR_SW_CPU_GPU_T              dec_addr_sw_cpu_gpu;                     // 0x2090
	L9B0_DEC_ADDR_SW_CPU_SHADOW_T           dec_addr_sw_cpu_shadow;                  // 0x2094
	L9B0_DEC_GMAU_FLUSH_T                   dec_gmau_flush;                          // 0x2098
	UINT32                                  reserved9;                               // 0x209c
	L9B0_DEC_SMUX_SIZE_I_T                  dec_smux_size_i;                         // 0x20a0
	UINT32                                  reserved10[7];                           // 0x20a4~0x20bc
	L9B0_DEC_DEA_MVI_CTRL_0_T               dec_dea_mvi_ctrl_0;                      // 0x20c0
	L9B0_DEC_DEA_MVI_CTRL_1_T               dec_dea_mvi_ctrl_1;                      // 0x20c4
	L9B0_DEC_DEA_MVI_CTRL_2_T               dec_dea_mvi_ctrl_2;                      // 0x20c8
	L9B0_DEC_DEA_MVI_CTRL_3_T               dec_dea_mvi_ctrl_3;                      // 0x20cc
	L9B0_DEC_DEA_MVI_CTRL_4_T               dec_dea_mvi_ctrl_4;                      // 0x20d0
	L9B0_DEC_DEA_MVI_CTRL_5_T               dec_dea_mvi_ctrl_5;                      // 0x20d4
	L9B0_DEC_DEA_MVI_CTRL_6_T               dec_dea_mvi_ctrl_6;                      // 0x20d8
	UINT32                                  reserved11;                              // 0x20dc
	L9B0_DEC_PIC_START_DELAY_CTRL_T         dec_pic_start_delay_ctrl;                // 0x20e0
	L9B0_DEC_PIC_START_G0_TIMER_T           dec_pic_start_g0_timer;                  // 0x20e4
	L9B0_DEC_PIC_START_G1_TIMER_T           dec_pic_start_g1_timer;                  // 0x20e8
	L9B0_DEC_PIC_START_G2_TIMER_T           dec_pic_start_g2_timer;                  // 0x20ec
	UINT32                                  reserved12;                              // 0x20f0
	L9B0_DEC_PIC_END_FORCE_T                dec_pic_end_force;                       // 0x20f4
	UINT32                                  reserved13;                              // 0x20f8
	L9B0_DEC_MG_LS_CTRL_T                   dec_mg_ls_ctrl;                          // 0x20fc
} DE_DEC_REG_L9B0_T;

typedef struct {
	L9B0_DED_PIC_INIT_T                     ded_pic_init;                            // 0x3000
	L9B0_DED_PIC_START_T                    ded_pic_start;                           // 0x3004
	UINT32                                  reserved14[7];                           // 0x3008~0x3020
	L9B0_DED_GMAU_CTRL_T                    ded_gmau_ctrl;                           // 0x3024
	L9B0_DED_PIC_END_EN_T                   ded_pic_end_en;                          // 0x3028
	L9B0_DED_PIC_INIT_G0_TIMER_T            ded_pic_init_g0_timer;                   // 0x302c
	L9B0_DED_PIC_INIT_G1_TIMER_T            ded_pic_init_g1_timer;                   // 0x3030
	UINT32                                  reserved15[2];                           // 0x3034~0x3038
	L9B0_DED_PIC_END_INFO_T                 ded_pic_end_info;                        // 0x303c
	L9B0_DED_INTR_REG_T                     ded_intr_reg;                            // 0x3040
	L9B0_DED_INTR_MASK_T                    ded_intr_mask;                           // 0x3044
	L9B0_DED_INTR_MUX_T                     ded_intr_mux;                            // 0x3048
	UINT32                                  reserved16;                              // 0x304c
	L9B0_DED_ADDR_SW_DE_SAV_T               ded_addr_sw_de_sav;                      // 0x3050
	L9B0_DED_ADDR_SW_CPU_GPU_T              ded_addr_sw_cpu_gpu;                     // 0x3054
	L9B0_DED_ADDR_SW_CPU_SHADOW_T           ded_addr_sw_cpu_shadow;                  // 0x3058
	UINT32                                  reserved17[25];                          // 0x305c~0x30bc
	L9B0_DED_DLY_DISP_SYNC_PARAMS_T         ded_dly_disp_sync_params;                // 0x30c0
	L9B0_DED_DLY_DISP_SYNC_FORCE_UPDATE_T   ded_dly_disp_sync_force_update;          // 0x30c4
	L9B0_DED_DLY_DISP_SYNC_CTRL_T           ded_dly_disp_sync_ctrl;                  // 0x30c8
	L9B0_DED_DEF_DISP_SYNC_SEL_T            ded_def_disp_sync_sel;                   // 0x30cc
	L9B0_DED_OV_PIC_START_DLY_EN_T          ded_ov_pic_start_dly_en;                 // 0x30d0
	L9B0_DED_PIC_INIT_G1_TIMER_C_T          ded_pic_init_g1_timer_c;                 // 0x30d4
	UINT32                                  reserved18[2];                           // 0x30d8~0x30dc
	L9B0_DED_DLY_DISP_V_PORCH_T             ded_dly_disp_v_porch;                    // 0x30e0
	L9B0_DED_DLY_DISP_VS_VA_T               ded_dly_disp_vs_va;                      // 0x30e4
	L9B0_DED_DLY_DISP_H_PORCH_T             ded_dly_disp_h_porch;                    // 0x30e8
	L9B0_DED_DLY_DISP_HS_HA_T               ded_dly_disp_hs_ha;                      // 0x30ec
	UINT32                                  reserved19[2];                           // 0x30f0~0x30f4
	L9B0_DED_GMAU_FLUSH_T                   ded_gmau_flush;                          // 0x30f8
	L9B0_DED_MG_LS_CTRL_T                   ded_mg_ls_ctrl;                          // 0x30fc
} DE_DED_REG_L9B0_T;

typedef struct {
	L9B0_DEC_DE_INTR_FLAG_MCU_T             dec_de_intr_flag_mcu;                    // 0x4000
	L9B0_DEC_DE_INTR_FLAG_CPU_T             dec_de_intr_flag_cpu;                    // 0x4004
	L9B0_DEE_CVI_MUX_SEL_T                  dee_cvi_mux_sel;                         // 0x4008
	L9B0_DEE_PE0_HIF_OFFSET_T               dee_pe0_hif_offset;                      // 0x400c
	L9B0_DEE_SM_HIF_OFFSET_T                dee_sm_hif_offset;                       // 0x4010
	L9B0_DEE_PE1_HIF_OFFSET_T               dee_pe1_hif_offset;                      // 0x4014
	L9B0_DEE_CVD_ADDR_SW_DE_SAV_T           dee_cvd_addr_sw_de_sav;                  // 0x4018
	L9B0_DEE_CVD_ADDR_SW_CPU_GPU_T          dee_cvd_addr_sw_cpu_gpu;                 // 0x401c
	L9B0_DEE_CVD_ADDR_SW_CPU_SHADOW_T       dee_cvd_addr_sw_cpu_shadow;              // 0x4020
	L9B0_DEE_MCU_ADDR_SW_DE_SAV_T           dee_mcu_addr_sw_de_sav;                  // 0x4024
	L9B0_DEE_MCU_ADDR_SW_CPU_GPU_T          dee_mcu_addr_sw_cpu_gpu;                 // 0x4028
	L9B0_DEE_MCU_ADDR_SW_CPU_SHADOW_T       dee_mcu_addr_sw_cpu_shadow;              // 0x402c
	L9B0_DEE_MCU_ADDR_WINDOW_T              dee_mcu_addr_window;                     // 0x4030
	L9B0_DEE_INTR_REG_T                     dee_intr_reg;                            // 0x4034
	L9B0_DEE_INTR_MASK_T                    dee_intr_mask;                           // 0x4038
	L9B0_DEE_GMAU_FLUSH_T                   dee_gmau_flush;                          // 0x403c
	UINT32                                  reserved20[47];                          // 0x4040~0x40f8
	L9B0_DEE_MG_LS_CTRL_T                   dee_mg_ls_ctrl;                          // 0x40fc
} DE_DEE_REG_L9B0_T;

typedef struct {
	L9B0_DEF_PIC_INIT_T                     def_pic_init;                            // 0x5000
	L9B0_DEF_PIC_START_T                    def_pic_start;                           // 0x5004
	L9B0_DEF_DE_VENC_IF_T                   def_de_venc_if;                          // 0x5008
	L9B0_DEF_DPATH_CTRL_T                   def_dpath_ctrl;                          // 0x500c
	L9B0_DEF_CVE_PARAM0_T                   def_cve_param0;                          // 0x5010
	L9B0_DEF_CVE_PARAM1_T                   def_cve_param1;                          // 0x5014
	L9B0_DEF_CVE_PARAM2_T                   def_cve_param2;                          // 0x5018
	L9B0_DEF_CVE_PARAM3_T                   def_cve_param3;                          // 0x501c
	L9B0_DEF_CVE_PULSE_DLY_T                def_cve_pulse_dly;                       // 0x5020
	L9B0_DEF_GMAU_CTRL_T                    def_gmau_ctrl;                           // 0x5024
	L9B0_DEF_PIC_END_EN_T                   def_pic_end_en;                          // 0x5028
	UINT32                                  reserved21[2];                           // 0x502c~0x5030
	L9B0_DEF_PIC_INIT_G2_TIMER_T            def_pic_init_g2_timer;                   // 0x5034
	L9B0_DEF_PIC_INIT_G3_TIMER_T            def_pic_init_g3_timer;                   // 0x5038
	L9B0_DEF_PIC_END_INFO_T                 def_pic_end_info;                        // 0x503c
	L9B0_DEF_INTR_REG_T                     def_intr_reg;                            // 0x5040
	L9B0_DEF_INTR_MASK_T                    def_intr_mask;                           // 0x5044
	L9B0_DEF_INTR_MUX_T                     def_intr_mux;                            // 0x5048
	L9B0_DEF_CVE_INTR_TIME_STP_T            def_cve_intr_time_stp;                   // 0x504c
	L9B0_DEF_ADDR_SW_DE_SAV_T               def_addr_sw_de_sav;                      // 0x5050
	L9B0_DEF_ADDR_SW_CPU_GPU_T              def_addr_sw_cpu_gpu;                     // 0x5054
	L9B0_DEF_ADDR_SW_CPU_SHADOW_T           def_addr_sw_cpu_shadow;                  // 0x5058
	UINT32                                  reserved22[39];                          // 0x505c~0x50f4
	L9B0_DEF_GMAU_FLUSH_T                   def_gmau_flush;                          // 0x50f8
	L9B0_DEF_MG_LS_CTRL_T                   def_mg_ls_ctrl;                          // 0x50fc
} DE_DEF_REG_L9B0_T;

#endif
