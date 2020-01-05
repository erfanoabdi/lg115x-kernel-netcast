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

#ifndef _REG_CTR_H13B0_h
#define _REG_CTR_H13B0_h

/*-----------------------------------------------------------------------------
	0x0000 dea_cha_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cha_hsize                               : 12;  //  0:11
	UINT32                                         : 1;   //    12 reserved
	UINT32 cha_csample                             : 1;   //    13
	UINT32 cha_aspect                              : 1;   //    14
	UINT32                                         : 1;   //    15 reserved
	UINT32 cha_vsize                               : 12;  // 16:27
	UINT32                                         : 1;   //    28 reserved
	UINT32 cha_frame_lr                            : 1;   //    29
	UINT32 cha_field_id                            : 1;   //    30
	UINT32 cha_pr_sq                               : 1;   //    31
} H13B0_DEA_CHA_INFO_T;

/*-----------------------------------------------------------------------------
	0x0004 dea_chb_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 chb_hsize                               : 12;  //  0:11
	UINT32                                         : 1;   //    12 reserved
	UINT32 chb_csample                             : 1;   //    13
	UINT32 chb_aspect                              : 1;   //    14
	UINT32                                         : 1;   //    15 reserved
	UINT32 chb_vsize                               : 12;  // 16:27
	UINT32                                         : 1;   //    28 reserved
	UINT32 chb_frame_lr                            : 1;   //    29
	UINT32 chb_field_id                            : 1;   //    30
	UINT32 chb_pr_sq                               : 1;   //    31
} H13B0_DEA_CHB_INFO_T;

/*-----------------------------------------------------------------------------
	0x0008 dea_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                             : 1;   //     0
	UINT32 pic_init_g1                             : 1;   //     1
	UINT32                                         : 1;   //     2 reserved
	UINT32 pic_init_g3                             : 1;   //     3
	UINT32                                         : 12;  //  4:15 reserved
	UINT32 smux_auto_init                          : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 pe0_auto_init                           : 1;   //    20
	UINT32                                         : 7;   // 21:27 reserved
	UINT32 smux1_auto_init                         : 1;   //    28
} H13B0_DEA_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x000c dea_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                            : 1;   //     0
	UINT32 pic_start_g1                            : 1;   //     1
	UINT32                                         : 1;   //     2 reserved
	UINT32 pic_start_g3                            : 1;   //     3
} H13B0_DEA_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x0010 dea_smux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 o_c_fmt                                 : 3;   //  0: 2
	UINT32 prew_rd_422                             : 1;   //     3
	UINT32 i_c_fmt                                 : 3;   //  4: 6
	UINT32                                         : 1;   //     7 reserved
	UINT32 dec3d_mux_sel                           : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 prew_mux_sel                            : 1;   //    12
	UINT32 dlr_sel                                 : 1;   //    13
	UINT32                                         : 2;   // 14:15 reserved
	UINT32 cvi_mux_sel                             : 3;   // 16:18
	UINT32                                         : 1;   //    19 reserved
	UINT32 nline_inc                               : 1;   //    20
	UINT32                                         : 2;   // 21:22 reserved
	UINT32 wr_disalbe                              : 1;   //    23
	UINT32 fieldid                                 : 1;   //    24
	UINT32 size                                    : 1;   //    25
	UINT32 set_mvi_val                             : 1;   //    26
	UINT32                                         : 1;   //    27 reserved
	UINT32 mvi_r                                   : 1;   //    28
	UINT32 mvi_w                                   : 1;   //    29
	UINT32                                         : 1;   //    30 reserved
	UINT32 pr_sq                                   : 1;   //    31
} H13B0_DEA_SMUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0014 dea_smux_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize                                   : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 vsize                                   : 12;  // 16:27
} H13B0_DEA_SMUX_SIZE_T;

/*-----------------------------------------------------------------------------
	0x0018 dea_mvi_v_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_vsize                               : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 mvi_vblank                              : 12;  // 16:27
} H13B0_DEA_MVI_V_INFO_T;

/*-----------------------------------------------------------------------------
	0x001c dea_mvi_h_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_hsize                               : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 mvi_hblank                              : 12;  // 16:27
} H13B0_DEA_MVI_H_INFO_T;

/*-----------------------------------------------------------------------------
	0x0020 dea_mvi_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_i_c_fmt                             : 3;   //  0: 2
	UINT32                                         : 1;   //     3 reserved
	UINT32 mvi_field                               : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 mvi_pr_sq                               : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 mvi_cvi_stride                          : 1;   //    12
} H13B0_DEA_MVI_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0024 dea_msrc_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 trans_mask_en                           : 1;   //     0
	UINT32 disp_sync_sel                           : 1;   //     1
	UINT32 vdec_vsync_inv                          : 1;   //     2
	UINT32 mem_vsync_inv                           : 1;   //     3
	UINT32 cvi_select                              : 1;   //     4
	UINT32 src_fall_pos_sel                        : 3;   //  5: 7
	UINT32 mvi_select                              : 1;   //     8
	UINT32 mvi_sync_select                         : 2;   //  9:10
	UINT32 src_pulse_base_pos_half_va              : 1;   //    11
	UINT32 mvi_cvi_select                          : 1;   //    12
	UINT32 cvia_vsync_inv                          : 1;   //    13
	UINT32 cvib_vsync_inv                          : 1;   //    14
	UINT32 disp_sync_inv                           : 1;   //    15
	UINT32 src_pulse_pos_sel                       : 6;   // 16:21
	UINT32                                         : 2;   // 22:23 reserved
	UINT32 disp_select                             : 1;   //    24
	UINT32 cvia_sync_sel                           : 1;   //    25
	UINT32 cvib_sync_sel                           : 1;   //    26
	UINT32 fb_sync_select                          : 1;   //    27
	UINT32 sync_manual_delay_en                    : 1;   //    28
	UINT32                                         : 2;   // 29:30 reserved
	UINT32 ignore_src_vsync_fal                    : 1;   //    31
} H13B0_DEA_MSRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0028 dea_msrc_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msrc_sync_dly                           : 28;  //  0:27
	UINT32 cnt_msrc_pulse                          : 4;   // 28:31
} H13B0_DEA_MSRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x002c dea_mem_sync_period ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem_sync_period                         : 28;  //  0:27
} H13B0_DEA_MEM_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
	0x0030 dea_dco_mfc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_mfc                                 : 28;  //  0:27
} H13B0_DEA_DCO_MFC_T;

/*-----------------------------------------------------------------------------
	0x0034 dea_dco_dfc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_dfc                                 : 28;  //  0:27
} H13B0_DEA_DCO_DFC_T;

/*-----------------------------------------------------------------------------
	0x0038 dea_dco_dflc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_dflc                                : 12;  //  0:11
} H13B0_DEA_DCO_DFLC_T;

/*-----------------------------------------------------------------------------
	0x003c dea_dco_fcw ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dco_fcw                                 : 22;  //  0:21
} H13B0_DEA_DCO_FCW_T;

/*-----------------------------------------------------------------------------
	0x0040 dea_smux_ro_lcnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 smux_ro_lcnt                            : 12;  //  0:11
} H13B0_DEA_SMUX_RO_LCNT_T;

/*-----------------------------------------------------------------------------
	0x0044 dea_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                         : 8;   //  0: 7
	UINT32                                         : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                              : 10;  // 16:25
} H13B0_DEA_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0048 dea_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_en                                  : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 clc_en                                  : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 tnr_en                                  : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 pe0_en                                  : 1;   //    12
	UINT32                                         : 3;   // 13:15 reserved
	UINT32 prew_en                                 : 1;   //    16
	UINT32 prew_wd_en                              : 1;   //    17
	UINT32                                         : 2;   // 18:19 reserved
	UINT32 smux_en                                 : 1;   //    20
} H13B0_DEA_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x004c dea_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0_timer                       : 28;  //  0:27
} H13B0_DEA_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x0050 dea_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer                       : 28;  //  0:27
} H13B0_DEA_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x0054 dea_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 5;   //  0: 4
	UINT32 pic_end_g1                              : 8;   //  5:12
} H13B0_DEA_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x0058 dea_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 1;   //     0
	UINT32 pic_end_g1                              : 1;   //     1
	UINT32 cha_input_intr                          : 1;   //     2
	UINT32 chb_input_intr                          : 1;   //     3
	UINT32 cha_field_intr                          : 1;   //     4
	UINT32 cha_frame_lr_intr                       : 1;   //     5
	UINT32 chb_field_intr                          : 1;   //     6
	UINT32 chb_frame_lr_intr                       : 1;   //     7
	UINT32 pe0_intr                                : 1;   //     8
	UINT32 smux_ow_intr                            : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //    12
	UINT32 gmau_flush_wr_done                      : 1;   //    13
	UINT32                                         : 6;   // 14:19 reserved
	UINT32 pic_end_g3                              : 1;   //    20
	UINT32                                         : 2;   // 21:22 reserved
	UINT32 src_intr                                : 1;   //    23
	UINT32 src1_intr                               : 1;   //    24
	UINT32                                         : 3;   // 25:27 reserved
	UINT32 fd3_intr                                : 1;   //    28
	UINT32 pic_end_fd3                             : 1;   //    29
} H13B0_DEA_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x005c dea_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_intr_mask                           : 28;  //  0:27
} H13B0_DEA_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x0060 dea_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_intr_mux                            : 28;  //  0:27
} H13B0_DEA_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x0064 dea_src_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_intr_time_stp                       : 32;  //  0:31
} H13B0_DEA_SRC_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x0068 de_gpio_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 de_gpio_mux                             : 2;   //  0: 1
} H13B0_DE_GPIO_MUX_T;

/*-----------------------------------------------------------------------------
	0x006c msrc_ro_vblk_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msrc_ro_vblk_cnt                        : 32;  //  0:31
} H13B0_MSRC_RO_VBLK_CNT_T;

/*-----------------------------------------------------------------------------
	0x0070 dea_ctrl_gap_irq_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_gap_irq_to_init                     : 28;  //  0:27
	UINT32 dea_ctrl_gap_irq_init                   : 4;   // 28:31
} H13B0_DEA_CTRL_GAP_IRQ_INIT_T;

/*-----------------------------------------------------------------------------
	0x0074 dea_msrc1_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 trans_mask_en                           : 1;   //     0
	UINT32 disp_sync_sel                           : 1;   //     1
	UINT32 vdec_vsync_inv                          : 1;   //     2
	UINT32 mem_vsync_inv                           : 1;   //     3
	UINT32 cvi_select                              : 1;   //     4
	UINT32 src_fall_pos_sel                        : 3;   //  5: 7
	UINT32 mvi_select                              : 1;   //     8
	UINT32 mvi_sync_select                         : 2;   //  9:10
	UINT32 src_pulse_base_pos_half_va              : 1;   //    11
	UINT32 mvi_cvi_select                          : 1;   //    12
	UINT32 cvia_vsync_inv                          : 1;   //    13
	UINT32 cvib_vsync_inv                          : 1;   //    14
	UINT32 disp_sync_inv                           : 1;   //    15
	UINT32 src_pulse_pos_sel                       : 6;   // 16:21
	UINT32                                         : 2;   // 22:23 reserved
	UINT32 disp_select                             : 1;   //    24
	UINT32 cvia_sync_sel                           : 1;   //    25
	UINT32 cvib_sync_sel                           : 1;   //    26
	UINT32 fb_sync_select                          : 1;   //    27
	UINT32 sync_manual_delay_en                    : 1;   //    28
	UINT32                                         : 2;   // 29:30 reserved
	UINT32 ignore_src_vsync_fal                    : 1;   //    31
} H13B0_DEA_MSRC1_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0078 dea_msrc1_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msrc1_sync_dly                          : 28;  //  0:27
	UINT32 cnt_msrc1_pulse                         : 4;   // 28:31
} H13B0_DEA_MSRC1_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x007c de_version ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 final_release_date                      : 32;  //  0:31
} H13B0_DE_VERSION_T;

/*-----------------------------------------------------------------------------
	0x0080 dea_smux_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_buf_size                            : 2;   //  0: 1
	UINT32                                         : 2;   //  2: 3 reserved
	UINT32 ud_split_mode                           : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 debug_mode                              : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 pic_end_sel                             : 1;   //    12
	UINT32                                         : 3;   // 13:15 reserved
	UINT32 line_diff_en                            : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 line_diff                               : 12;  // 20:31
} H13B0_DEA_SMUX_CTRL_1_T;

/*-----------------------------------------------------------------------------
	0x0084 dea_smux_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_req_pend_val                          : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 c_req_pend_val                          : 12;  // 16:27
} H13B0_DEA_SMUX_CTRL_2_T;

/*-----------------------------------------------------------------------------
	0x0088 dea_smux_ctrl_d ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 d_o_c_fmt                               : 3;   //  0: 2
	UINT32                                         : 1;   //     3 reserved
	UINT32 d_i_c_fmt                               : 3;   //  4: 6
	UINT32                                         : 9;   //  7:15 reserved
	UINT32 d_ch_mux_sel                            : 3;   // 16:18
	UINT32                                         : 6;   // 19:24 reserved
	UINT32 d_set_in_size                           : 1;   //    25
	UINT32 d_set_mvi_val                           : 1;   //    26
	UINT32                                         : 4;   // 27:30 reserved
	UINT32 d_pr_sq                                 : 1;   //    31
} H13B0_DEA_SMUX_CTRL_D_T;

/*-----------------------------------------------------------------------------
	0x008c dea_smux_size_d ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_d                                 : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 vsize_d                                 : 12;  // 16:27
} H13B0_DEA_SMUX_SIZE_D_T;

/*-----------------------------------------------------------------------------
	0x0090 msrc1_ro_vblk_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msrc1_ro_vblk_cnt                       : 32;  //  0:31
} H13B0_MSRC1_RO_VBLK_CNT_T;

/*-----------------------------------------------------------------------------
	0x0094 dea_vdec_vsync_src_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_src_sel                       : 2;   //  0: 1
	UINT32                                         : 14;  //  2:15 reserved
	UINT32 vdec_vsync_ready_off                    : 1;   //    16
} H13B0_DEA_VDEC_VSYNC_SRC_SEL_T;

/*-----------------------------------------------------------------------------
	0x00a0 dea_smux_size_i ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_i                                 : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 vsize_i                                 : 12;  // 16:27
} H13B0_DEA_SMUX_SIZE_I_T;

/*-----------------------------------------------------------------------------
	0x00a4 dea_smux_hsc_y_set_val_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_offset_y                          : 6;   //  0: 5
	UINT32                                         : 6;   //  6:11 reserved
	UINT32 aal_coef_0_y                            : 10;  // 12:21
} H13B0_DEA_SMUX_HSC_Y_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
	0x00a8 dea_smux_hsc_y_set_val_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_1_y                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_2_y                            : 10;  // 12:21
} H13B0_DEA_SMUX_HSC_Y_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
	0x00ac dea_smux_hsc_y_set_val_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_3_y                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_4_y                            : 10;  // 12:21
} H13B0_DEA_SMUX_HSC_Y_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
	0x00b0 dea_smux_hsc_c_set_val_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_offset_c                          : 6;   //  0: 5
	UINT32                                         : 6;   //  6:11 reserved
	UINT32 aal_coef_0_c                            : 10;  // 12:21
} H13B0_DEA_SMUX_HSC_C_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
	0x00b4 dea_smux_hsc_c_set_val_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_1_c                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_2_c                            : 10;  // 12:21
} H13B0_DEA_SMUX_HSC_C_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
	0x00b8 dea_smux_hsc_c_set_val_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_3_c                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_4_c                            : 10;  // 12:21
} H13B0_DEA_SMUX_HSC_C_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
	0x00bc dea_pic_init_src_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 g3_src_sel_src_pulse                    : 1;   //     0
	UINT32 g3_src_sel_start                        : 1;   //     1
	UINT32 g3_src_sel_init                         : 1;   //     2
	UINT32                                         : 1;   //     3 reserved
	UINT32 g2_src_sel_src_pulse                    : 1;   //     4
	UINT32 g2_src_sel_start                        : 1;   //     5
	UINT32 g2_src_sel_init                         : 1;   //     6
	UINT32                                         : 1;   //     7 reserved
	UINT32 g1_src_sel_src_pulse                    : 1;   //     8
	UINT32 g1_src_sel_start                        : 1;   //     9
	UINT32 g1_src_sel_init                         : 1;   //    10
	UINT32 prew_addr_load_src_sel                  : 1;   //    11
	UINT32 g0_src_sel_src_pulse                    : 1;   //    12
	UINT32 g0_src_sel_start                        : 1;   //    13
	UINT32 g0_src_sel_init                         : 1;   //    14
	UINT32 src_sel_dea_deb_src_pulse               : 1;   //    15
	UINT32 src_sel_pic_start_d_smux                : 2;   // 16:17
	UINT32 src_sel_pic_start_r_smux                : 2;   // 18:19
	UINT32 src_sel_pic_init_d_smux                 : 2;   // 20:21
	UINT32 src_sel_pic_init_r_smux                 : 2;   // 22:23
	UINT32 prew_wr_start_src_sel                   : 2;   // 24:25
	UINT32 prew_wr_start_src_sel_pulse_msrc1       : 1;   //    26
	UINT32 prew_wr_start_src_sel_pulse             : 1;   //    27
	UINT32 prew_wr_init_src_sel                    : 2;   // 28:29
	UINT32 prew_wr_init_src_sel_pulse_msrc1        : 1;   //    30
	UINT32 prew_wr_init_src_sel_pulse              : 1;   //    31
} H13B0_DEA_PIC_INIT_SRC_SEL_T;

/*-----------------------------------------------------------------------------
	0x00c0 dea_mvi_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_h_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 y_h_width                               : 12;  // 16:27
	UINT32                                         : 3;   // 28:30 reserved
	UINT32 mvi_3d_ctrl_en                          : 1;   //    31
} H13B0_DEA_MVI_CTRL_0_T;

/*-----------------------------------------------------------------------------
	0x00c4 dea_mvi_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_h_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 c_h_width                               : 12;  // 16:27
} H13B0_DEA_MVI_CTRL_1_T;

/*-----------------------------------------------------------------------------
	0x00c8 dea_mvi_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_v_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 y_v_height                              : 12;  // 16:27
} H13B0_DEA_MVI_CTRL_2_T;

/*-----------------------------------------------------------------------------
	0x00cc dea_mvi_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_v_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 c_v_height                              : 12;  // 16:27
} H13B0_DEA_MVI_CTRL_3_T;

/*-----------------------------------------------------------------------------
	0x00d0 dea_mvi_ctrl_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_sub_sample_step                       : 8;   //  0: 7
	UINT32 y_h_even_line_sub_sample_offset         : 8;   //  8:15
	UINT32                                         : 8;   // 16:23 reserved
	UINT32 y_h_odd_line_sub_sample_offset          : 8;   // 24:31
} H13B0_DEA_MVI_CTRL_4_T;

/*-----------------------------------------------------------------------------
	0x00d4 dea_mvi_ctrl_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 8;   //  0: 7 reserved
	UINT32 c_h_even_line_sub_sample_offset         : 8;   //  8:15
	UINT32                                         : 8;   // 16:23 reserved
	UINT32 c_h_odd_line_sub_sample_offset          : 8;   // 24:31
} H13B0_DEA_MVI_CTRL_5_T;

/*-----------------------------------------------------------------------------
	0x00d8 dea_mvi_ctrl_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_sub_sample_step                       : 8;   //  0: 7
	UINT32 y_v_sub_sample_offset                   : 8;   //  8:15
	UINT32                                         : 8;   // 16:23 reserved
	UINT32 c_v_sub_sample_offset                   : 8;   // 24:31
} H13B0_DEA_MVI_CTRL_6_T;

/*-----------------------------------------------------------------------------
	0x00e0 dea_pic_start_delay_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_delay_mvi                     : 1;   //     0
	UINT32 pic_start_delay_mvi_y_rd                : 1;   //     1
	UINT32 pic_start_delay_mvi_c_rd                : 1;   //     2
	UINT32 pic_start_delay_dec3d                   : 1;   //     3
	UINT32 pic_start_delay_smux                    : 1;   //     4
	UINT32 pic_start_delay_prew_y_rd               : 1;   //     5
	UINT32 pic_start_delay_prew_c_rd               : 1;   //     6
	UINT32 pic_start_delay_prew_y_wd               : 1;   //     7
	UINT32 pic_start_delay_prew_c_wd               : 1;   //     8
	UINT32                                         : 7;   //  9:15 reserved
	UINT32 pic_start_delay_pe0                     : 1;   //    16
	UINT32 pic_start_delay_tnr0_y_rd               : 1;   //    17
	UINT32 pic_start_delay_tnr1_y_rd               : 1;   //    18
	UINT32 pic_start_delay_tnr_c_rd                : 1;   //    19
	UINT32 pic_start_delay_tnr_y_wd                : 1;   //    20
	UINT32 pic_start_delay_tnr_c_wd                : 1;   //    21
	UINT32 pic_start_delay_ipc0_y_rd               : 1;   //    22
	UINT32 pic_start_delay_ipc1_y_rd               : 1;   //    23
	UINT32 pic_start_delay_ipc0_c_rd               : 1;   //    24
	UINT32 pic_start_delay_ipc1_c_rd               : 1;   //    25
	UINT32 pic_start_delay_ipc_m_rd                : 1;   //    26
	UINT32 pic_start_delay_ipc_m_wd                : 1;   //    27
	UINT32 pic_start_delay_r_smux                  : 1;   //    28
	UINT32 pic_start_delay_d_smux                  : 1;   //    29
} H13B0_DEA_PIC_START_DELAY_CTRL_T;

/*-----------------------------------------------------------------------------
	0x00e4 dea_pic_start_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0_timer                      : 28;  //  0:27
} H13B0_DEA_PIC_START_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x00e8 dea_pic_start_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g1_timer                      : 28;  //  0:27
} H13B0_DEA_PIC_START_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x00ec dea_pic_start_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g2_timer                      : 28;  //  0:27
} H13B0_DEA_PIC_START_G2_TIMER_T;

/*-----------------------------------------------------------------------------
	0x00f0 dea_pic_init_g3_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g3_timer                       : 32;  //  0:31
} H13B0_DEA_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
	0x00f4 dea_pic_end_force ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_pic_end_g0_force                    : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 dea_pic_end_g0_force_en                 : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 dea_pic_end_g1_force                    : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 dea_pic_end_g1_force_en                 : 1;   //    12
} H13B0_DEA_PIC_END_FORCE_T;

/*-----------------------------------------------------------------------------
	0x00f8 dea_fpga_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_fpga_ctrl                           : 32;  //  0:31
} H13B0_DEA_FPGA_CTRL_T;

/*-----------------------------------------------------------------------------
	0x00fc dea_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done                      : 1;   //    12
} H13B0_DEA_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x1000 deb_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                             : 1;   //     0
	UINT32 pic_init_g1                             : 1;   //     1
	UINT32                                         : 14;  //  2:15 reserved
	UINT32 sm_auto_init                            : 1;   //    16
	UINT32                                         : 7;   // 17:23 reserved
	UINT32 ov_auto_init                            : 1;   //    24
} H13B0_DEB_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x1004 deb_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                            : 1;   //     0
	UINT32 pic_start_g1                            : 1;   //     1
} H13B0_DEB_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x1008 deb_disp_v_porch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsync_bp                                : 16;  //  0:15
	UINT32 vsync_fp                                : 16;  // 16:31
} H13B0_DEB_DISP_V_PORCH_T;

/*-----------------------------------------------------------------------------
	0x100c deb_disp_vs_va ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_sync_va                            : 16;  //  0:15
	UINT32 vsync                                   : 16;  // 16:31
} H13B0_DEB_DISP_VS_VA_T;

/*-----------------------------------------------------------------------------
	0x1010 deb_disp_h_porch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsync_bp                                : 16;  //  0:15
	UINT32 hsync_fp                                : 16;  // 16:31
} H13B0_DEB_DISP_H_PORCH_T;

/*-----------------------------------------------------------------------------
	0x1014 deb_disp_hs_ha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_sync_ha                            : 16;  //  0:15
	UINT32 hsync                                   : 16;  // 16:31
} H13B0_DEB_DISP_HS_HA_T;

/*-----------------------------------------------------------------------------
	0x1018 deb_disp_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset1                                : 16;  //  0:15
	UINT32 voffset1                                : 16;  // 16:31
} H13B0_DEB_DISP_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x101c deb_disp_pulse_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_pulse_dly                          : 28;  //  0:27
} H13B0_DEB_DISP_PULSE_DLY_T;

/*-----------------------------------------------------------------------------
	0x1020 deb_disp_sync_params ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset0                                : 16;  //  0:15
	UINT32 force_update_auto_en                    : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 force_update_src_sel                    : 2;   // 20:21
	UINT32                                         : 1;   //    22 reserved
	UINT32 sync_polarity                           : 1;   //    23
	UINT32                                         : 3;   // 24:26 reserved
	UINT32 disp_frame_lr                           : 1;   //    27
	UINT32 disp_pulse_src_sel                      : 1;   //    28
	UINT32                                         : 2;   // 29:30 reserved
	UINT32 force_update                            : 1;   //    31
} H13B0_DEB_DISP_SYNC_PARAMS_T;

/*-----------------------------------------------------------------------------
	0x1028 debd_msdf_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msf_enable                              : 1;   //     0
	UINT32 msf_src_sel                             : 1;   //     1
	UINT32                                         : 2;   //  2: 3 reserved
	UINT32 mdf_src_sel                             : 2;   //  4: 5
	UINT32                                         : 10;  //  6:15 reserved
	UINT32 msdf_src_sel                            : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 msdf_disable                            : 1;   //    20
} H13B0_DEBD_MSDF_CTRL_0_T;

/*-----------------------------------------------------------------------------
	0x1030 debd_ctrl_path_osd_60hz ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 r_src_sel_h3d_d                         : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 r_src_sel_h3d_s                         : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 r_src_sel_osd                           : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 r_src_sel_bdpp                          : 1;   //    12
	UINT32                                         : 3;   // 13:15 reserved
	UINT32 l_src_sel_h3d_d                         : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 l_src_sel_h3d_s                         : 1;   //    20
	UINT32                                         : 3;   // 21:23 reserved
	UINT32 l_src_sel_osd                           : 1;   //    24
	UINT32                                         : 3;   // 25:27 reserved
	UINT32 l_src_sel_bdpp                          : 1;   //    28
} H13B0_DEBD_CTRL_PATH_OSD_60HZ_T;

/*-----------------------------------------------------------------------------
	0x106c deb_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                         : 8;   //  0: 7
	UINT32                                         : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                              : 10;  // 16:25
} H13B0_DEB_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1070 deb_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ov_ss_en                                : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 ov_en                                   : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 sm_en                                   : 1;   //     8
} H13B0_DEB_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x1074 deb_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0_timer                       : 28;  //  0:27
} H13B0_DEB_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x1078 deb_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer                       : 28;  //  0:27
} H13B0_DEB_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x107c deb_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 3;   //  0: 2
	UINT32                                         : 1;   //     3 reserved
	UINT32 pic_end_g1                              : 5;   //  4: 8
	UINT32                                         : 7;   //  9:15 reserved
	UINT32 pic_end_g1_c                            : 1;   //    16
} H13B0_DEB_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x1080 deb_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_pic_end_g0                         : 1;   //     0
	UINT32 intr_pic_end_g1                         : 1;   //     1
	UINT32 disp_intr_for_cpu                       : 1;   //     2
	UINT32 intr_ov_underflow                       : 1;   //     3
	UINT32                                         : 2;   //  4: 5 reserved
	UINT32 disp_intr_for_mcu                       : 1;   //     6
	UINT32 intr_src_pulse                          : 1;   //     7
	UINT32                                         : 1;   //     8 reserved
	UINT32 intr_pic_end_g1_c                       : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 intr_gmau_flush_wr_done                 : 1;   //    12
	UINT32 intr_gmau_flush_rd_done                 : 1;   //    13
} H13B0_DEB_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x1084 deb_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_pic_end_g0                         : 1;   //     0
	UINT32 mask_pic_end_g1                         : 1;   //     1
	UINT32 mask_disp_for_cpu                       : 1;   //     2
	UINT32 mask_ov_underflow                       : 1;   //     3
	UINT32                                         : 2;   //  4: 5 reserved
	UINT32 mask_disp_for_mcu                       : 1;   //     6
	UINT32 mask_src_pulse                          : 1;   //     7
	UINT32                                         : 1;   //     8 reserved
	UINT32 mask_pic_end_g1_c                       : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 mask_gmau_flush_wr_done                 : 1;   //    12
	UINT32 mask_gmau_flush_rd_done                 : 1;   //    13
} H13B0_DEB_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x1088 deb_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux_pic_end_g0                          : 1;   //     0
	UINT32 mux_pic_end_g1                          : 1;   //     1
	UINT32 mux_disp_for_cpu                        : 1;   //     2
	UINT32 mux_ov_underflow                        : 1;   //     3
	UINT32                                         : 2;   //  4: 5 reserved
	UINT32 mux_disp_for_mcu                        : 1;   //     6
	UINT32 mux_src_pulse                           : 1;   //     7
	UINT32                                         : 1;   //     8 reserved
	UINT32 mux_pic_end_g1_c                        : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 mux_gmau_flush_wr_done                  : 1;   //    12
	UINT32 mux_gmau_flush_rd_done                  : 1;   //    13
} H13B0_DEB_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x108c deb_disp_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_intr_time_stp                      : 32;  //  0:31
} H13B0_DEB_DISP_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x10d0 deb_ov_pic_start_dly_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_ov_pic_start_dly_en                 : 1;   //     0
	UINT32                                         : 15;  //  1:15 reserved
	UINT32 pic_end_g1_c_force_en                   : 1;   //    16
	UINT32 pic_end_g1_c_force_value                : 1;   //    17
} H13B0_DEB_OV_PIC_START_DLY_EN_T;

/*-----------------------------------------------------------------------------
	0x10d4 deb_pic_init_g1_timer_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer_c                     : 28;  //  0:27
} H13B0_DEB_PIC_INIT_G1_TIMER_C_T;

/*-----------------------------------------------------------------------------
	0x10f8 deb_fpga_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 deb_fpga_ctrl                           : 32;  //  0:31
} H13B0_DEB_FPGA_CTRL_T;

/*-----------------------------------------------------------------------------
	0x10fc deb_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done                      : 1;   //    12
} H13B0_DEB_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x2000 dec_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                             : 1;   //     0
	UINT32 pic_init_g1                             : 1;   //     1
	UINT32 pic_init_g2                             : 1;   //     2
	UINT32 pic_init_g3                             : 1;   //     3
	UINT32                                         : 12;  //  4:15 reserved
	UINT32 smux_auto_init                          : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 pe0_auto_init                           : 1;   //    20
	UINT32                                         : 3;   // 21:23 reserved
	UINT32 ssc_auto_init                           : 1;   //    24
	UINT32                                         : 3;   // 25:27 reserved
	UINT32 smux1_auto_init                         : 1;   //    28
} H13B0_DEC_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x2004 dec_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                            : 1;   //     0
	UINT32 pic_start_g1                            : 1;   //     1
	UINT32 pic_start_g2                            : 1;   //     2
	UINT32 pic_start_g3                            : 1;   //     3
} H13B0_DEC_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x2008 dec_smux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 o_c_fmt                                 : 3;   //  0: 2
	UINT32 prew_rd_422                             : 1;   //     3
	UINT32 i_c_fmt                                 : 3;   //  4: 6
	UINT32                                         : 1;   //     7 reserved
	UINT32 dec3d_mux_sel                           : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 prew_mux_sel                            : 1;   //    12
	UINT32 dlr_sel                                 : 1;   //    13
	UINT32                                         : 2;   // 14:15 reserved
	UINT32 cvi_mux_sel                             : 3;   // 16:18
	UINT32                                         : 1;   //    19 reserved
	UINT32 nline_inc                               : 1;   //    20
	UINT32                                         : 2;   // 21:22 reserved
	UINT32 wr_disalbe                              : 1;   //    23
	UINT32 fieldid                                 : 1;   //    24
	UINT32 size                                    : 1;   //    25
	UINT32 set_mvi_val                             : 1;   //    26
	UINT32                                         : 1;   //    27 reserved
	UINT32 mvi_r                                   : 1;   //    28
	UINT32 mvi_w                                   : 1;   //    29
	UINT32                                         : 1;   //    30 reserved
	UINT32 pr_sq                                   : 1;   //    31
} H13B0_DEC_SMUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x200c dec_smux_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize                                   : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 vsize                                   : 13;  // 16:28
} H13B0_DEC_SMUX_SIZE_T;

/*-----------------------------------------------------------------------------
	0x2010 dec_mvi_v_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_vsize                               : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 mvi_vblank                              : 12;  // 16:27
} H13B0_DEC_MVI_V_INFO_T;

/*-----------------------------------------------------------------------------
	0x2014 dec_mvi_h_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_hsize                               : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 mvi_hblank                              : 12;  // 16:27
} H13B0_DEC_MVI_H_INFO_T;

/*-----------------------------------------------------------------------------
	0x2018 dec_mvi_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_i_c_fmt                             : 3;   //  0: 2
	UINT32                                         : 1;   //     3 reserved
	UINT32 mvi_field                               : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 mvi_pr_sq                               : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 mvi_cvi_stride                          : 1;   //    12
} H13B0_DEC_MVI_CTRL_T;

/*-----------------------------------------------------------------------------
	0x201c dec_msrc_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 m_trans_mask_en                         : 1;   //     0
	UINT32 m_disp_sync_sel                         : 1;   //     1
	UINT32 m_vdec_vsync_inv                        : 1;   //     2
	UINT32 m_mem_vsync_inv                         : 1;   //     3
	UINT32 m_cvi_select                            : 1;   //     4
	UINT32 m_src_fall_pos_sel                      : 3;   //  5: 7
	UINT32 m_mvi_select                            : 1;   //     8
	UINT32 m_mvi_sync_select                       : 2;   //  9:10
	UINT32 m_src_pulse_base_pos_half_va            : 1;   //    11
	UINT32 m_mvi_cvi_select                        : 1;   //    12
	UINT32 m_cvia_vsync_inv                        : 1;   //    13
	UINT32 m_cvib_vsync_inv                        : 1;   //    14
	UINT32 m_disp_sync_inv                         : 1;   //    15
	UINT32 m_src_pulse_pos_sel                     : 6;   // 16:21
	UINT32                                         : 2;   // 22:23 reserved
	UINT32 m_disp_select                           : 1;   //    24
	UINT32 m_cvia_sync_sel                         : 1;   //    25
	UINT32 m_cvib_sync_sel                         : 1;   //    26
	UINT32 m_fb_sync_select                        : 1;   //    27
	UINT32 m_sync_manual_delay_en                  : 1;   //    28
	UINT32                                         : 2;   // 29:30 reserved
	UINT32 m_ignore_src_vsync_fal                  : 1;   //    31
} H13B0_DEC_MSRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2020 dec_msrc_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msrc_sync_dly                           : 28;  //  0:27
	UINT32 cnt_msrc_pulse                          : 4;   // 28:31
} H13B0_DEC_MSRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x2024 dec_mem0_sync_period ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem0_sync_period                        : 28;  //  0:27
} H13B0_DEC_MEM0_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
	0x2028 dec_mem1_sync_period ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mem1_sync_period                        : 28;  //  0:27
} H13B0_DEC_MEM1_SYNC_PERIOD_T;

/*-----------------------------------------------------------------------------
	0x202c src_sync_vblk_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 src_sync_vblk_cnt                       : 28;  //  0:27
	UINT32 sel_src_sync_vblk_cnt                   : 4;   // 28:31
} H13B0_SRC_SYNC_VBLK_CNT_T;

/*-----------------------------------------------------------------------------
	0x2030 dec_ssrc_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 s_trans_mask_en                         : 1;   //     0
	UINT32 s_disp_sync_sel                         : 1;   //     1
	UINT32 s_vdec_vsync_inv                        : 1;   //     2
	UINT32 s_mem_vsync_inv                         : 1;   //     3
	UINT32 s_cvi_select                            : 1;   //     4
	UINT32 s_src_fall_pos_sel                      : 3;   //  5: 7
	UINT32 s_mvi_select                            : 1;   //     8
	UINT32 s_mvi_sync_select                       : 2;   //  9:10
	UINT32 s_src_pulse_base_pos_half_va            : 1;   //    11
	UINT32 s_mvi_cvi_select                        : 1;   //    12
	UINT32 s_cvia_vsync_inv                        : 1;   //    13
	UINT32 s_cvib_vsync_inv                        : 1;   //    14
	UINT32 s_disp_sync_inv                         : 1;   //    15
	UINT32 s_src_pulse_pos_sel                     : 6;   // 16:21
	UINT32                                         : 2;   // 22:23 reserved
	UINT32 s_disp_select                           : 1;   //    24
	UINT32 s_cvia_sync_sel                         : 1;   //    25
	UINT32 s_cvib_sync_sel                         : 1;   //    26
	UINT32 s_fb_sync_select                        : 1;   //    27
	UINT32 s_sync_manual_delay_en                  : 1;   //    28
	UINT32                                         : 2;   // 29:30 reserved
	UINT32 s_ignore_src_vsync_fal                  : 1;   //    31
} H13B0_DEC_SSRC_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2034 dec_ssrc_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ssrc_sync_dly                           : 28;  //  0:27
	UINT32 cnt_ssrc_pulse                          : 4;   // 28:31
} H13B0_DEC_SSRC_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x2038 mvi_t_0_v_clip_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_offset                                : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 v_active                                : 12;  // 16:27
	UINT32                                         : 3;   // 28:30 reserved
	UINT32 v_clip_en                               : 1;   //    31
} H13B0_MVI_T_0_V_CLIP_CTRL_T;

/*-----------------------------------------------------------------------------
	0x203c mvi_t_1_v_clip_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_offset                                : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 v_active                                : 12;  // 16:27
	UINT32                                         : 3;   // 28:30 reserved
	UINT32 v_clip_en                               : 1;   //    31
} H13B0_MVI_T_1_V_CLIP_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2040 dec_smux_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sel_buf_size                            : 2;   //  0: 1
	UINT32                                         : 2;   //  2: 3 reserved
	UINT32 ud_split_mode                           : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 debug_mode                              : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 pic_end_sel                             : 1;   //    12
	UINT32                                         : 3;   // 13:15 reserved
	UINT32 line_diff_en                            : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 line_diff                               : 12;  // 20:31
} H13B0_DEC_SMUX_CTRL_1_T;

/*-----------------------------------------------------------------------------
	0x2044 dec_smux_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_req_pend_val                          : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 c_req_pend_val                          : 12;  // 16:27
} H13B0_DEC_SMUX_CTRL_2_T;

/*-----------------------------------------------------------------------------
	0x2048 dec_smux_ctrl_d ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 d_o_c_fmt                               : 3;   //  0: 2
	UINT32                                         : 1;   //     3 reserved
	UINT32 d_i_c_fmt                               : 3;   //  4: 6
	UINT32                                         : 9;   //  7:15 reserved
	UINT32 d_ch_mux_sel                            : 3;   // 16:18
	UINT32                                         : 6;   // 19:24 reserved
	UINT32 d_set_in_size                           : 1;   //    25
	UINT32 d_set_mvi_val                           : 1;   //    26
	UINT32                                         : 4;   // 27:30 reserved
	UINT32 d_pr_sq                                 : 1;   //    31
} H13B0_DEC_SMUX_CTRL_D_T;

/*-----------------------------------------------------------------------------
	0x204c dec_smux_size_d ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_d                                 : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 vsize_d                                 : 12;  // 16:27
} H13B0_DEC_SMUX_SIZE_D_T;

/*-----------------------------------------------------------------------------
	0x2050 dec_msrc1_sync_mux_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 trans_mask_en                           : 1;   //     0
	UINT32 disp_sync_sel                           : 1;   //     1
	UINT32 vdec_vsync_inv                          : 1;   //     2
	UINT32 mem_vsync_inv                           : 1;   //     3
	UINT32 cvi_select                              : 1;   //     4
	UINT32 src_fall_pos_sel                        : 3;   //  5: 7
	UINT32 mvi_select                              : 1;   //     8
	UINT32 mvi_sync_select                         : 2;   //  9:10
	UINT32 src_pulse_base_pos_half_va              : 1;   //    11
	UINT32 mvi_cvi_select                          : 1;   //    12
	UINT32 cvia_vsync_inv                          : 1;   //    13
	UINT32 cvib_vsync_inv                          : 1;   //    14
	UINT32 disp_sync_inv                           : 1;   //    15
	UINT32 src_pulse_pos_sel                       : 6;   // 16:21
	UINT32                                         : 2;   // 22:23 reserved
	UINT32 disp_select                             : 1;   //    24
	UINT32 cvia_sync_sel                           : 1;   //    25
	UINT32 cvib_sync_sel                           : 1;   //    26
	UINT32 fb_sync_select                          : 1;   //    27
	UINT32 sync_manual_delay_en                    : 1;   //    28
	UINT32                                         : 2;   // 29:30 reserved
	UINT32 ignore_src_vsync_fal                    : 1;   //    31
} H13B0_DEC_MSRC1_SYNC_MUX_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2054 dec_msrc1_sync_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msrc1_sync_dly                          : 28;  //  0:27
	UINT32 cnt_msrc1_pulse                         : 4;   // 28:31
} H13B0_DEC_MSRC1_SYNC_DLY_T;

/*-----------------------------------------------------------------------------
	0x2058 dec_ctrl_gap_irq_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_gap_irq_to_init                     : 28;  //  0:27
	UINT32 dec_ctrl_gap_irq_init                   : 4;   // 28:31
} H13B0_DEC_CTRL_GAP_IRQ_INIT_T;

/*-----------------------------------------------------------------------------
	0x205c dec_smux_ro_lcnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 smux_ro_lcnt                            : 12;  //  0:11
} H13B0_DEC_SMUX_RO_LCNT_T;

/*-----------------------------------------------------------------------------
	0x2060 dec_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                         : 8;   //  0: 7
	UINT32                                         : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                              : 10;  // 16:25
} H13B0_DEC_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2064 dec_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ipc_en                                  : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 tnr_en                                  : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 pe0_en                                  : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 prew_en                                 : 1;   //    12
	UINT32 prew_wd_en                              : 1;   //    13
	UINT32                                         : 2;   // 14:15 reserved
	UINT32 smux_en                                 : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 mvi_en                                  : 1;   //    20
	UINT32                                         : 3;   // 21:23 reserved
	UINT32 ss_en                                   : 1;   //    24
	UINT32                                         : 3;   // 25:27 reserved
	UINT32 ssm_en                                  : 1;   //    28
} H13B0_DEC_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x2068 dec_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0_timer                       : 28;  //  0:27
} H13B0_DEC_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x206c dec_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer                       : 28;  //  0:27
} H13B0_DEC_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x2070 dec_pic_init_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g2_timer                       : 28;  //  0:27
} H13B0_DEC_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
	0x2074 dec_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 5;   //  0: 4
	UINT32 pic_end_g1                              : 7;   //  5:11
	UINT32 pic_end_g2                              : 3;   // 12:14
} H13B0_DEC_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x2078 dec_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 1;   //     0
	UINT32 pic_end_g1                              : 1;   //     1
	UINT32 pic_end_g2                              : 1;   //     2
	UINT32 pe0_intr                                : 1;   //     3
	UINT32 smux_ow_intr                            : 1;   //     4
	UINT32                                         : 7;   //  5:11 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //    12
	UINT32 gmau_flush_wr_done                      : 1;   //    13
	UINT32                                         : 2;   // 14:15 reserved
	UINT32 ssrc_intr                               : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 pic_end_g3                              : 1;   //    20
	UINT32                                         : 2;   // 21:22 reserved
	UINT32 msrc_intr                               : 1;   //    23
	UINT32 msrc1_intr                              : 1;   //    24
} H13B0_DEC_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x207c dec_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_intr_mask                           : 32;  //  0:31
} H13B0_DEC_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x2080 dec_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_intr_mux                            : 32;  //  0:31
} H13B0_DEC_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x2084 dec_msrc_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 msrc_intr_timer_stp                     : 32;  //  0:31
} H13B0_DEC_MSRC_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x2088 dec_ssrc_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ssrc_intr_timer_stp                     : 32;  //  0:31
} H13B0_DEC_SSRC_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x208c dec_mvi_ready_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_t_1_ready_c_force_value             : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 mvi_t_1_ready_c_force_en                : 1;   //     4
	UINT32 mvi_t_1_ready_c_force_sync_en           : 1;   //     5
	UINT32 mvi_t_1_ready_c_force_sync_ris          : 1;   //     6
	UINT32                                         : 1;   //     7 reserved
	UINT32 mvi_t_1_ready_y_force_value             : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 mvi_t_1_ready_y_force_en                : 1;   //    12
	UINT32 mvi_t_1_ready_y_force_sync_en           : 1;   //    13
	UINT32 mvi_t_1_ready_y_force_sync_ris          : 1;   //    14
	UINT32                                         : 1;   //    15 reserved
	UINT32 mvi_t_0_ready_c_force_value             : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 mvi_t_0_ready_c_force_en                : 1;   //    20
	UINT32 mvi_t_0_ready_c_force_sync_en           : 1;   //    21
	UINT32 mvi_t_0_ready_c_force_sync_ris          : 1;   //    22
	UINT32                                         : 1;   //    23 reserved
	UINT32 mvi_t_0_ready_y_force_value             : 1;   //    24
	UINT32                                         : 3;   // 25:27 reserved
	UINT32 mvi_t_0_ready_y_force_en                : 1;   //    28
	UINT32 mvi_t_0_ready_y_force_sync_en           : 1;   //    29
	UINT32 mvi_t_0_ready_y_force_sync_ris          : 1;   //    30
} H13B0_DEC_MVI_READY_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2090 dec_mvi_path_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mvi_ssc_tb_path_sel                     : 2;   //  0: 1
	UINT32                                         : 2;   //  2: 3 reserved
	UINT32 mvi_ssc_ta_path_sel                     : 2;   //  4: 5
	UINT32                                         : 10;  //  6:15 reserved
	UINT32 dec_mvi_path_sel                        : 2;   // 16:17
	UINT32                                         : 2;   // 18:19 reserved
	UINT32 dea_mvi_path_sel                        : 2;   // 20:21
} H13B0_DEC_MVI_PATH_SEL_T;

/*-----------------------------------------------------------------------------
	0x2094 dec_vdec_vsync_src_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_src_sel                       : 3;   //  0: 2
	UINT32                                         : 1;   //     3 reserved
	UINT32 pic_start_const                         : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 mvi_t_simultaneous_input_en             : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 mvi_t_vsync_ready_for_deac_en           : 1;   //    12
	UINT32 mvi_t_vsync_ready_with_ssc_en           : 1;   //    13
	UINT32                                         : 2;   // 14:15 reserved
	UINT32 vdec_vsync_ready_off                    : 1;   //    16
} H13B0_DEC_VDEC_VSYNC_SRC_SEL_T;

/*-----------------------------------------------------------------------------
	0x20a0 dec_smux_size_i ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_i                                 : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 vsize_i                                 : 13;  // 16:28
} H13B0_DEC_SMUX_SIZE_I_T;

/*-----------------------------------------------------------------------------
	0x20a4 dec_smux_hsc_y_set_val_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_offset_y                          : 6;   //  0: 5
	UINT32                                         : 6;   //  6:11 reserved
	UINT32 aal_coef_0_y                            : 10;  // 12:21
} H13B0_DEC_SMUX_HSC_Y_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
	0x20a8 dec_smux_hsc_y_set_val_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_1_y                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_2_y                            : 10;  // 12:21
} H13B0_DEC_SMUX_HSC_Y_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
	0x20ac dec_smux_hsc_y_set_val_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_3_y                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_4_y                            : 10;  // 12:21
} H13B0_DEC_SMUX_HSC_Y_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
	0x20b0 dec_smux_hsc_c_set_val_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_offset_c                          : 6;   //  0: 5
	UINT32                                         : 6;   //  6:11 reserved
	UINT32 aal_coef_0_c                            : 10;  // 12:21
} H13B0_DEC_SMUX_HSC_C_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
	0x20b4 dec_smux_hsc_c_set_val_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_1_c                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_2_c                            : 10;  // 12:21
} H13B0_DEC_SMUX_HSC_C_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
	0x20b8 dec_smux_hsc_c_set_val_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_3_c                            : 10;  //  0: 9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 aal_coef_4_c                            : 10;  // 12:21
} H13B0_DEC_SMUX_HSC_C_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
	0x20bc dec_pic_init_src_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 g3_src_sel_src_pulse                    : 1;   //     0
	UINT32 g3_src_sel_start                        : 1;   //     1
	UINT32 g3_src_sel_init                         : 1;   //     2
	UINT32                                         : 1;   //     3 reserved
	UINT32 g2_src_sel_src_pulse                    : 1;   //     4
	UINT32 g2_src_sel_start                        : 1;   //     5
	UINT32 g2_src_sel_init                         : 1;   //     6
	UINT32                                         : 1;   //     7 reserved
	UINT32 g1_src_sel_src_pulse                    : 1;   //     8
	UINT32 g1_src_sel_start                        : 1;   //     9
	UINT32 g1_src_sel_init                         : 1;   //    10
	UINT32 prew_addr_load_src_sel                  : 1;   //    11
	UINT32 g0_src_sel_src_pulse                    : 1;   //    12
	UINT32 g0_src_sel_start                        : 1;   //    13
	UINT32 g0_src_sel_init                         : 1;   //    14
	UINT32 src_sel_dec_ded_src_pulse               : 1;   //    15
	UINT32 src_sel_pic_start_d_smux                : 2;   // 16:17
	UINT32 src_sel_pic_start_r_smux                : 2;   // 18:19
	UINT32 src_sel_pic_init_d_smux                 : 2;   // 20:21
	UINT32 src_sel_pic_init_r_smux                 : 2;   // 22:23
	UINT32 prew_wr_start_src_sel                   : 2;   // 24:25
	UINT32 prew_wr_start_src_sel_pulse_msrc1       : 1;   //    26
	UINT32 prew_wr_start_src_sel_pulse             : 1;   //    27
	UINT32 prew_wr_init_src_sel                    : 2;   // 28:29
	UINT32 prew_wr_init_src_sel_pulse_msrc1        : 1;   //    30
	UINT32 prew_wr_init_src_sel_pulse              : 1;   //    31
} H13B0_DEC_PIC_INIT_SRC_SEL_T;

/*-----------------------------------------------------------------------------
	0x20c0 dec_mvi_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_h_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 y_h_width                               : 12;  // 16:27
	UINT32                                         : 3;   // 28:30 reserved
	UINT32 mvi_3d_ctrl_en                          : 1;   //    31
} H13B0_DEC_MVI_CTRL_0_T;

/*-----------------------------------------------------------------------------
	0x20c4 dec_mvi_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_h_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 c_h_width                               : 12;  // 16:27
} H13B0_DEC_MVI_CTRL_1_T;

/*-----------------------------------------------------------------------------
	0x20c8 dec_mvi_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_v_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 y_v_height                              : 12;  // 16:27
} H13B0_DEC_MVI_CTRL_2_T;

/*-----------------------------------------------------------------------------
	0x20cc dec_mvi_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_v_offset                              : 12;  //  0:11
	UINT32                                         : 4;   // 12:15 reserved
	UINT32 c_v_height                              : 12;  // 16:27
} H13B0_DEC_MVI_CTRL_3_T;

/*-----------------------------------------------------------------------------
	0x20d0 dec_mvi_ctrl_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_sub_sample_step                       : 8;   //  0: 7
	UINT32 y_h_even_line_sub_sample_offset         : 8;   //  8:15
	UINT32                                         : 8;   // 16:23 reserved
	UINT32 y_h_odd_line_sub_sample_offset          : 8;   // 24:31
} H13B0_DEC_MVI_CTRL_4_T;

/*-----------------------------------------------------------------------------
	0x20d4 dec_mvi_ctrl_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 8;   //  0: 7 reserved
	UINT32 c_h_even_line_sub_sample_offset         : 8;   //  8:15
	UINT32                                         : 8;   // 16:23 reserved
	UINT32 c_h_odd_line_sub_sample_offset          : 8;   // 24:31
} H13B0_DEC_MVI_CTRL_5_T;

/*-----------------------------------------------------------------------------
	0x20d8 dec_mvi_ctrl_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_sub_sample_step                       : 8;   //  0: 7
	UINT32 y_v_sub_sample_offset                   : 8;   //  8:15
	UINT32                                         : 8;   // 16:23 reserved
	UINT32 c_v_sub_sample_offset                   : 8;   // 24:31
} H13B0_DEC_MVI_CTRL_6_T;

/*-----------------------------------------------------------------------------
	0x20e0 dec_pic_start_delay_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_delay_mvi                     : 1;   //     0
	UINT32 pic_start_delay_mvi_y_rd                : 1;   //     1
	UINT32 pic_start_delay_mvi_c_rd                : 1;   //     2
	UINT32 pic_start_delay_smux                    : 1;   //     3
	UINT32 pic_start_delay_prew_y_rd               : 1;   //     4
	UINT32 pic_start_delay_prew_c_rd               : 1;   //     5
	UINT32 pic_start_delay_prew_y_wd               : 1;   //     6
	UINT32 pic_start_delay_prew_c_wd               : 1;   //     7
	UINT32 pic_start_delay_pe0                     : 1;   //     8
	UINT32 pic_start_delay_tnr0_y_rd               : 1;   //     9
	UINT32 pic_start_delay_tnr_c_rd                : 1;   //    10
	UINT32 pic_start_delay_tnr_y_wd                : 1;   //    11
	UINT32 pic_start_delay_tnr_c_wd                : 1;   //    12
	UINT32 pic_start_delay_ipc0_y_rd               : 1;   //    13
	UINT32 pic_start_delay_ipc1_y_rd               : 1;   //    14
	UINT32 pic_start_delay_ipc_c_rd                : 1;   //    15
	UINT32 pic_start_delay_ss                      : 1;   //    16
	UINT32 pic_start_delay_ss_y_wd                 : 1;   //    17
	UINT32 pic_start_delay_ss_c_wd                 : 1;   //    18
	UINT32 pic_start_delay_ss_y_rd                 : 1;   //    19
	UINT32 pic_start_delay_ss_c_rd                 : 1;   //    20
	UINT32                                         : 3;   // 21:23 reserved
	UINT32 pic_start_delay_fd3                     : 1;   //    24
	UINT32                                         : 3;   // 25:27 reserved
	UINT32 pic_start_delay_r_smux                  : 1;   //    28
	UINT32 pic_start_delay_d_smux                  : 1;   //    29
} H13B0_DEC_PIC_START_DELAY_CTRL_T;

/*-----------------------------------------------------------------------------
	0x20e4 dec_pic_start_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0_timer                      : 28;  //  0:27
} H13B0_DEC_PIC_START_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x20e8 dec_pic_start_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g1_timer                      : 28;  //  0:27
} H13B0_DEC_PIC_START_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x20ec dec_pic_start_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g2_timer                      : 28;  //  0:27
} H13B0_DEC_PIC_START_G2_TIMER_T;

/*-----------------------------------------------------------------------------
	0x20f0 dec_pic_init_g3_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g3_timer                       : 32;  //  0:31
} H13B0_DEC_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
	0x20f4 dec_pic_end_force ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_pic_end_g0_force                    : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 dea_pic_end_g0_force_en                 : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 dea_pic_end_g1_force                    : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 dea_pic_end_g1_force_en                 : 1;   //    12
	UINT32                                         : 3;   // 13:15 reserved
	UINT32 dea_pic_end_g2_force                    : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 dea_pic_end_g2_force_en                 : 1;   //    20
} H13B0_DEC_PIC_END_FORCE_T;

/*-----------------------------------------------------------------------------
	0x20f8 dec_fpga_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_fpga_ctrl                           : 32;  //  0:31
} H13B0_DEC_FPGA_CTRL_T;

/*-----------------------------------------------------------------------------
	0x20fc dec_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done                      : 1;   //    12
} H13B0_DEC_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x3000 ded_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0                             : 1;   //     0
	UINT32 pic_init_g1                             : 1;   //     1
	UINT32                                         : 1;   //     2 reserved
	UINT32 pic_init_g3                             : 1;   //     3
	UINT32                                         : 12;  //  4:15 reserved
	UINT32 sm_auto_init                            : 1;   //    16
	UINT32                                         : 7;   // 17:23 reserved
	UINT32 ov_auto_init                            : 1;   //    24
	UINT32                                         : 6;   // 25:30 reserved
	UINT32 atop_auto_init                          : 1;   //    31
} H13B0_DED_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x3004 ded_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_start_g0                            : 1;   //     0
	UINT32 pic_start_g1                            : 1;   //     1
	UINT32                                         : 1;   //     2 reserved
	UINT32 pic_start_g3                            : 1;   //     3
} H13B0_DED_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x3008 ded_de_venc_if ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 venc_vsync                              : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 venc_sel                                : 1;   //     4
} H13B0_DED_DE_VENC_IF_T;

/*-----------------------------------------------------------------------------
	0x3010 ded_cve_param0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 vertical_back_period                    : 8;   //  0: 7
	UINT32 vertical_sync_period                    : 8;   //  8:15
	UINT32 vertical_front_period                   : 8;   // 16:23
	UINT32 vsync_polarity                          : 1;   //    24
} H13B0_DED_CVE_PARAM0_T;

/*-----------------------------------------------------------------------------
	0x3014 ded_cve_param1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 horizontal_back_period                  : 8;   //  0: 7
	UINT32 horizontal_sync_period                  : 8;   //  8:15
	UINT32 horizontal_front_period                 : 8;   // 16:23
	UINT32 hsync_polarity                          : 1;   //    24
} H13B0_DED_CVE_PARAM1_T;

/*-----------------------------------------------------------------------------
	0x3018 ded_cve_param2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 v_hoffset1                              : 11;  //  0:10
	UINT32 v_hoffset0                              : 11;  // 11:21
	UINT32                                         : 2;   // 22:23 reserved
	UINT32 field_id_polarity                       : 1;   //    24
} H13B0_DED_CVE_PARAM2_T;

/*-----------------------------------------------------------------------------
	0x301c ded_cve_param3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cve_sync_ha                             : 11;  //  0:10
	UINT32                                         : 5;   // 11:15 reserved
	UINT32 cve_sync_va                             : 11;  // 16:26
} H13B0_DED_CVE_PARAM3_T;

/*-----------------------------------------------------------------------------
	0x3020 ded_cve_pulse_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cve_pulse_dly                           : 28;  //  0:27
} H13B0_DED_CVE_PULSE_DLY_T;

/*-----------------------------------------------------------------------------
	0x3024 ded_gmau_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ask_cmd_dly_cnt                         : 8;   //  0: 7
	UINT32                                         : 8;   //  8:15 reserved
	UINT32 ask_to_cnt                              : 10;  // 16:25
} H13B0_DED_GMAU_CTRL_T;

/*-----------------------------------------------------------------------------
	0x3028 ded_pic_end_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 8;   //  0: 7 reserved
	UINT32 ov_en                                   : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 sm_en                                   : 1;   //    12
} H13B0_DED_PIC_END_EN_T;

/*-----------------------------------------------------------------------------
	0x302c ded_pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g0_timer                       : 28;  //  0:27
} H13B0_DED_PIC_INIT_G0_TIMER_T;

/*-----------------------------------------------------------------------------
	0x3030 ded_pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer                       : 28;  //  0:27
} H13B0_DED_PIC_INIT_G1_TIMER_T;

/*-----------------------------------------------------------------------------
	0x3038 ded_pic_init_g3_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g3_timer                       : 28;  //  0:27
} H13B0_DED_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
	0x303c ded_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0_info                         : 3;   //  0: 2
	UINT32                                         : 1;   //     3 reserved
	UINT32 pic_end_g1_info                         : 3;   //  4: 6
	UINT32                                         : 5;   //  7:11 reserved
	UINT32 pic_end_g3_info                         : 3;   // 12:14
} H13B0_DED_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x3040 ded_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 1;   //     0
	UINT32 pic_end_g1                              : 1;   //     1
	UINT32                                         : 1;   //     2 reserved
	UINT32 pic_end_g3                              : 1;   //     3
	UINT32 ov_underflow                            : 1;   //     4
	UINT32 cve_pulse                               : 1;   //     5
	UINT32 cve_va_pulse                            : 1;   //     6
	UINT32 src_pulse                               : 1;   //     7
	UINT32 pic_end_g1_c                            : 1;   //     8
	UINT32 cve_va_fal_pulse                        : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 gmau_flush_wr_don                       : 1;   //    12
	UINT32 gmau_flush_rd_done                      : 1;   //    13
} H13B0_DED_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x3044 ded_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 1;   //     0
	UINT32 pic_end_g1                              : 1;   //     1
	UINT32                                         : 1;   //     2 reserved
	UINT32 pic_end_g3                              : 1;   //     3
	UINT32 ov_underflow                            : 1;   //     4
	UINT32 cve_pulse                               : 1;   //     5
	UINT32 cve_va_pulse                            : 1;   //     6
	UINT32 src_pulse                               : 1;   //     7
	UINT32 pic_end_g1_c                            : 1;   //     8
	UINT32 cve_va_fal_pulse                        : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 gmau_flush_wr_don                       : 1;   //    12
	UINT32 gmau_flush_rd_done                      : 1;   //    13
} H13B0_DED_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x3048 ded_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0                              : 1;   //     0
	UINT32 pic_end_g1                              : 1;   //     1
	UINT32                                         : 1;   //     2 reserved
	UINT32 pic_end_g3                              : 1;   //     3
	UINT32 ov_underflow                            : 1;   //     4
	UINT32 cve_pulse                               : 1;   //     5
	UINT32 cve_va_pulse                            : 1;   //     6
	UINT32 src_pulse                               : 1;   //     7
	UINT32 pic_end_g1_c                            : 1;   //     8
	UINT32 cve_va_fal_pulse                        : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 gmau_flush_wr_don                       : 1;   //    12
	UINT32 gmau_flush_rd_done                      : 1;   //    13
} H13B0_DED_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x304c def_cve_intr_time_stp ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 def_cve_intr_time_stp_f                 : 32;   // 31: 0
} H13B0_DEF_CVE_INTR_TIME_STP_T;

/*-----------------------------------------------------------------------------
	0x3090 ded_disp_sync_dly_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_vsync                          : 16;  //  0:15
	UINT32 dly_sync_vfp                            : 16;  // 16:31
} H13B0_DED_DISP_SYNC_DLY_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x3094 ded_disp_sync_dly_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_va                             : 16;  //  0:15
	UINT32 dly_sync_vbp                            : 16;  // 16:31
} H13B0_DED_DISP_SYNC_DLY_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x3098 ded_disp_sync_dly_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_hsync                          : 16;  //  0:15
	UINT32 dly_sync_hfp                            : 16;  // 16:31
} H13B0_DED_DISP_SYNC_DLY_CTRL2_T;

/*-----------------------------------------------------------------------------
	0x309c ded_disp_sync_dly_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_ha                             : 16;  //  0:15
	UINT32 dly_sync_hbp                            : 16;  // 16:31
} H13B0_DED_DISP_SYNC_DLY_CTRL3_T;

/*-----------------------------------------------------------------------------
	0x30a0 ded_disp_sync_dly_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_line_start                     : 16;  //  0:15
	UINT32 dly_sync_force_update                   : 1;   //    16
} H13B0_DED_DISP_SYNC_DLY_CTRL4_T;

/*-----------------------------------------------------------------------------
	0x30a4 ded_disp_sync_dly_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_h_dly                          : 16;  //  0:15
	UINT32 dly_sync_v_dly                          : 16;  // 16:31
} H13B0_DED_DISP_SYNC_DLY_CTRL5_T;

/*-----------------------------------------------------------------------------
	0x30a8 disp_pulse_dly_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_pulse_dly_timer                    : 28;  //  0:27
	UINT32 disp_pulse_dly_cnt                      : 4;   // 28:31
} H13B0_DISP_PULSE_DLY_TIMER_T;

/*-----------------------------------------------------------------------------
	0x30ac ded_sync_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ov_ha_i_sel                             : 1;   //     0
	UINT32 ov_va_i_sel                             : 1;   //     1
	UINT32                                         : 14;  //  2:15 reserved
	UINT32 ov_auto_init_src_sel                    : 1;   //    16
} H13B0_DED_SYNC_CTRL_T;

/*-----------------------------------------------------------------------------
	0x30d0 ded_ov_pic_start_dly_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ded_ov_pic_start_dly_en                 : 1;   //     0
	UINT32                                         : 15;  //  1:15 reserved
	UINT32 pic_end_g1_c_force_en                   : 1;   //    16
	UINT32 pic_end_g1_c_force_value                : 1;   //    17
} H13B0_DED_OV_PIC_START_DLY_EN_T;

/*-----------------------------------------------------------------------------
	0x30d4 ded_pic_init_g1_timer_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g1_timer_c                     : 28;  //  0:27
} H13B0_DED_PIC_INIT_G1_TIMER_C_T;

/*-----------------------------------------------------------------------------
	0x30f8 ded_fpga_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ded_fpga_ctrl                           : 32;  //  0:31
} H13B0_DED_FPGA_CTRL_T;

/*-----------------------------------------------------------------------------
	0x30fc ded_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done                      : 1;   //    12
} H13B0_DED_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x4000 dec_de_intr_flag_mcu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dec_intr_mcu                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 deb_dec_intr_mcu                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 dec_dec_intr_mcu                        : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 ded_dec_intr_mcu                        : 1;   //    12
	UINT32                                         : 3;   // 13:15 reserved
	UINT32 dee_dec_intr_mcu                        : 1;   //    16
	UINT32                                         : 3;   // 17:19 reserved
	UINT32 intr_ipc_frc                            : 1;   //    20
} H13B0_DEC_DE_INTR_FLAG_MCU_T;

/*-----------------------------------------------------------------------------
	0x4004 dec_de_intr_flag_cpu ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dea_dec_intr_cpu                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 deb_dec_intr_cpu                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 dec_dec_intr_cpu                        : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 ded_dec_intr_cpu                        : 1;   //    12
	UINT32                                         : 7;   // 13:19 reserved
	UINT32 intr_ipc_frc                            : 1;   //    20
} H13B0_DEC_DE_INTR_FLAG_CPU_T;

/*-----------------------------------------------------------------------------
	0x4008 dee_cvi_mux_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvib_input_sel                  : 4;   //  0: 3
	UINT32 cvia_input_sel                  : 4;   //  4: 7
	UINT32                                 : 4;   //  8:11 reserved
	UINT32 lvds_type_sel                   : 1;   //    12
	UINT32                                 : 3;   // 13:15 reserved
	UINT32 scart_mode_en                   : 1;   //    16 
	UINT32                                 : 7;   // 17:23 reserved 
	UINT32 cvi_input_sel                   : 1;   //    24
	UINT32                                 : 7;   // 25:31 reserved
} H13B0_DEE_CVI_MUX_SEL_T;

/*-----------------------------------------------------------------------------
	0x400c dee_pe0_hif_offset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 28;  //  0:27 reserved
	UINT32 pe0_hif_offset_en                       : 1;   //    28
} H13B0_DEE_PE0_HIF_OFFSET_T;

/*-----------------------------------------------------------------------------
	0x4010 dee_sm_hif_offset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 28;  //  0:27 reserved
	UINT32 sm_hif_offset_en                        : 1;   //    28
} H13B0_DEE_SM_HIF_OFFSET_T;

/*-----------------------------------------------------------------------------
	0x4014 dee_pe1_hif_offset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 28;  //  0:27 reserved
	UINT32 pe1_hif_offset_en                       : 1;   //    28
} H13B0_DEE_PE1_HIF_OFFSET_T;

/*-----------------------------------------------------------------------------
	0x4030 dee_mcu_addr_window ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 12;  //  0:11 reserved
	UINT32 mcu_win_lower                           : 4;   // 12:15
	UINT32                                         : 12;  // 16:27 reserved
	UINT32 mcu_win_upper                           : 4;   // 28:31
} H13B0_DEE_MCU_ADDR_WINDOW_T;

/*-----------------------------------------------------------------------------
	0x4034 dee_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dee_src_cvd                             : 1;   //     0
	UINT32                                         : 1;   //     1 reserved
	UINT32 gmau_flush_wr_done                      : 1;   //     2
	UINT32 gmau_flush_rd_done                      : 1;   //     3
} H13B0_DEE_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x4038 dee_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dee_cvd_intr_mask                       : 1;   //     0
} H13B0_DEE_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x4050 dee_hdmi_bridge_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ctr_3dfr_mode                           : 2;   //  0: 1
	UINT32 input_sync_polarity                     : 1;   //     2
	UINT32 output_sync_polarity                    : 1;   //     3
	UINT32 field_polarity                          : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 ctr_3dfr_autoset                        : 1;   //     8
	UINT32 ud_autoset                              : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 sync_delay                              : 2;   // 12:13
} H13B0_DEE_HDMI_BRIDGE_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x4054 dee_hdmi_bridge_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_fir_coef0                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 y_fir_coef1                             : 10;  // 16:25
} H13B0_DEE_HDMI_BRIDGE_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x4058 dee_hdmi_bridge_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_fir_coef2                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 y_fir_coef3                             : 10;  // 16:25
} H13B0_DEE_HDMI_BRIDGE_CTRL2_T;

/*-----------------------------------------------------------------------------
	0x405c dee_hdmi_bridge_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_fir_coef4                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 y_fir_coef5                             : 10;  // 16:25
} H13B0_DEE_HDMI_BRIDGE_CTRL3_T;

/*-----------------------------------------------------------------------------
	0x4060 dee_hdmi_bridge_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_fir_coef6                             : 10;  //  0: 9
} H13B0_DEE_HDMI_BRIDGE_CTRL4_T;

/*-----------------------------------------------------------------------------
	0x4064 dee_hdmi_bridge_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_fir_coef0                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 c_fir_coef1                             : 10;  // 16:25
} H13B0_DEE_HDMI_BRIDGE_CTRL5_T;

/*-----------------------------------------------------------------------------
	0x4068 dee_hdmi_bridge_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_fir_coef2                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 c_fir_coef3                             : 10;  // 16:25
} H13B0_DEE_HDMI_BRIDGE_CTRL6_T;

/*-----------------------------------------------------------------------------
	0x406c dee_hdmi_bridge_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_fir_coef4                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 c_fir_coef5                             : 10;  // 16:25
} H13B0_DEE_HDMI_BRIDGE_CTRL7_T;

/*-----------------------------------------------------------------------------
	0x4070 dee_hdmi_bridge_ctrl8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_fir_coef6                             : 10;  //  0: 9
} H13B0_DEE_HDMI_BRIDGE_CTRL8_T;

/*-----------------------------------------------------------------------------
	0x4074 dee_hdmi_bridge_ctrl9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reserved                                : 32;  //  0:31 
} H13B0_DEE_HDMI_BRIDGE_CTRL9_T;

/*-----------------------------------------------------------------------------
	0x4078 dee_hdmi_bridge_ctrl10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 16;  //  0:15 reserved
	UINT32 ultra_h_active                          : 13;  // 16:28
} H13B0_DEE_HDMI_BRIDGE_CTRL10_T;

/*-----------------------------------------------------------------------------
	0x407c dee_hdmi_bridge_ctrl11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reserved                                : 32;  //  0:31 
} H13B0_DEE_HDMI_BRIDGE_CTRL11_T;

/*-----------------------------------------------------------------------------
	0x4080 dee_hdmi_bridge_ctrl12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reserved                                : 32;  // 16:28
} H13B0_DEE_HDMI_BRIDGE_CTRL12_T;

/*-----------------------------------------------------------------------------
	0x4084 dee_hdmi_bridge_ctrl13 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reserved                                : 32;  // 16:28
} H13B0_DEE_HDMI_BRIDGE_CTRL13_T;

/*-----------------------------------------------------------------------------
	0x40f8 dee_fpga_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dee_fpga_ctrl                           : 32;  //  0:31
} H13B0_DEE_FPGA_CTRL_T;

/*-----------------------------------------------------------------------------
	0x40fc dee_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done                      : 1;   //    12
} H13B0_DEE_GMAU_FLUSH_T;

/*-----------------------------------------------------------------------------
	0x5000 dppa_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 2;   //  0: 1 reserved
	UINT32 pic_inti_g2                             : 1;   //     2
	UINT32                                         : 24;  //  3:26 reserved
	UINT32 osd_auto_init                           : 1;   //    27
} H13B0_DPPA_PIC_INIT_T;

/*-----------------------------------------------------------------------------
	0x5004 dppa_pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 2;   //  0: 1 reserved
	UINT32 pic_start_g2                            : 1;   //     2
} H13B0_DPPA_PIC_START_T;

/*-----------------------------------------------------------------------------
	0x500c dppa_dpath_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd_pe_path_sel                         : 2;   //  0: 1
	UINT32                                         : 1;   //     2 reserved
	UINT32 de_into_osd                             : 1;   //     3
	UINT32 fb_mux_sel                              : 1;   //     4
} H13B0_DPPA_DPATH_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5010 dppa_sync_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dppa_dppb_ha_sel                        : 3;   //  0: 2
	UINT32 sep_osd_i_ha_sel                        : 1;   //     3
	UINT32 dppa_dppb_va_sel                        : 3;   //  4: 6
	UINT32 sep_osd_i_va_sel                        : 1;   //     7
	UINT32 dppa_dppb_hs_sel                        : 3;   //  8:10
	UINT32 sep_osd_o_hs_sel                        : 1;   //    11
	UINT32 dppa_dppb_vs_sel                        : 3;   // 12:14
	UINT32 sep_osd_o_vs_sel                        : 1;   //    15
	UINT32 osd_i_va_prev_sel                       : 3;   // 16:18
	UINT32 sep_osd_o_ha_sel                        : 1;   //    19
	UINT32 osd_sync_gen_vs_in                      : 1;   //    20
	UINT32 osd_sync_for_ud                         : 1;   //    21
	UINT32 sync_pe1_out                            : 1;   //    22
	UINT32 osd_sync_gen_hs_in                      : 1;   //    23
	UINT32 mof_sync_mask_en                        : 1;   //    24
	UINT32 sep_osd_o_va_sel                        : 1;   //    25
	UINT32 osd_sync_gen_ha_in                      : 1;   //    26
	UINT32 osd_sync_gen_va_in                      : 1;   //    27
	UINT32 mof_sync_mask_sel                       : 2;   // 28:29
} H13B0_DPPA_SYNC_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5020 dppa_disp_pulse_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp_pulse_timer                        : 28;  //  0:27
	UINT32 disp_pulse_src_sel                      : 1;   //    28
	UINT32 disp_pulse_src_inv                      : 1;   //    29
} H13B0_DPPA_DISP_PULSE_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5034 dppa_pic_init_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g2_timer                       : 28;  //  0:27
} H13B0_DPPA_PIC_INIT_G2_TIMER_T;

/*-----------------------------------------------------------------------------
	0x5038 dppa_pic_init_g3_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g3_timer                       : 28;  //  0:27
} H13B0_DPPA_PIC_INIT_G3_TIMER_T;

/*-----------------------------------------------------------------------------
	0x503c dppa_pic_end_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 8;   //  0: 7 reserved
	UINT32 pic_end_g2_info                         : 1;   //     8
} H13B0_DPPA_PIC_END_INFO_T;

/*-----------------------------------------------------------------------------
	0x5040 dppa_intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 2;   //  0: 1 reserved
	UINT32 pic_end_g2                              : 1;   //     2
	UINT32                                         : 9;   //  3:11 reserved
	UINT32 gmau_flush_wr_done_ris                  : 1;   //    12
	UINT32 gmau_flush_rd_done_ris                  : 1;   //    13
} H13B0_DPPA_INTR_REG_T;

/*-----------------------------------------------------------------------------
	0x5044 dppa_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dppa_intr_mask                          : 16;  //  0:15
} H13B0_DPPA_INTR_MASK_T;

/*-----------------------------------------------------------------------------
	0x5048 dppa_intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dppa_intr_mux                           : 16;  //  0:15
} H13B0_DPPA_INTR_MUX_T;

/*-----------------------------------------------------------------------------
	0x504c dppa_mif_2nd_pic_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_mif_2nd_en                         : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 osd2_mif_2nd_en                         : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 osd1_mif_2nd_en                         : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 osd0_mif_2nd_en                         : 1;   //    12
} H13B0_DPPA_MIF_2ND_PIC_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5050 dppa_disp60hz_pulse_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 disp60hz_pulse_timer                    : 28;  //  0:27
	UINT32 disp60hz_pulse_src_sel                  : 1;   //    28
	UINT32 disp60hz_pulse_src_inv                  : 1;   //    29
} H13B0_DPPA_DISP60HZ_PULSE_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5054 dppa_pic_init_g4_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_init_g4_timer                       : 28;  //  0:27
} H13B0_DPPA_PIC_INIT_G4_TIMER_T;

/*-----------------------------------------------------------------------------
	0x5058 dppa_mif_60hz_pic_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 osd3_mif_60hz_en                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 osd2_mif_60hz_en                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 osd1_mif_60hz_en                        : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 osd0_mif_60hz_en                        : 1;   //    12
} H13B0_DPPA_MIF_60HZ_PIC_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5060 dppa_mof_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_y_coef0                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 fir_y_coef1                             : 10;  // 16:25
} H13B0_DPPA_MOF_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x5064 dppa_mof_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_y_coef2                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 fir_y_coef3                             : 10;  // 16:25
} H13B0_DPPA_MOF_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x5068 dppa_mof_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_y_coef4                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 fir_y_coef5                             : 10;  // 16:25
} H13B0_DPPA_MOF_CTRL2_T;

/*-----------------------------------------------------------------------------
	0x506c dppa_mof_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_y_coef6                             : 10;  //  0: 9
} H13B0_DPPA_MOF_CTRL3_T;

/*-----------------------------------------------------------------------------
	0x5070 dppa_mof_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_c_coef0                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 fir_c_coef1                             : 10;  // 16:25
} H13B0_DPPA_MOF_CTRL4_T;

/*-----------------------------------------------------------------------------
	0x5074 dppa_mof_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_c_coef2                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 fir_c_coef3                             : 10;  // 16:25
} H13B0_DPPA_MOF_CTRL5_T;

/*-----------------------------------------------------------------------------
	0x5078 dppa_mof_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_c_coef4                             : 10;  //  0: 9
	UINT32                                         : 6;   // 10:15 reserved
	UINT32 fir_c_coef5                             : 10;  // 16:25
} H13B0_DPPA_MOF_CTRL6_T;

/*-----------------------------------------------------------------------------
	0x507c dppa_mof_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fir_c_coef6                             : 10;  //  0: 9
} H13B0_DPPA_MOF_CTRL7_T;

/*-----------------------------------------------------------------------------
	0x5080 dppa_mof_ctrl8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 csc_en                                  : 1;   //     0
	UINT32 down_scale_en                           : 1;   //     1
	UINT32 aal_en                                  : 1;   //     2
	UINT32                                         : 1;   //     3 reserved
	UINT32 v_down_scale_offset                     : 1;   //     4
} H13B0_DPPA_MOF_CTRL8_T;

/*-----------------------------------------------------------------------------
	0x5090 def_disp_sync_dly_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_actv_vsync                     : 16;  //  0:15
	UINT32 dly_sync_actv_vfp                       : 16;  // 16:31
} H13B0_DEF_DISP_SYNC_DLY_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x5094 def_disp_sync_dly_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_actv_va                        : 16;  //  0:15
	UINT32 dly_sync_actv_vbp                       : 16;  // 16:31
} H13B0_DEF_DISP_SYNC_DLY_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x5098 def_disp_sync_dly_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_actv_hsync                     : 16;  //  0:15
	UINT32 dly_sync_actv_hfp                       : 16;  // 16:31
} H13B0_DEF_DISP_SYNC_DLY_CTRL2_T;

/*-----------------------------------------------------------------------------
	0x509c def_disp_sync_dly_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_actv_ha                        : 16;  //  0:15
	UINT32 dly_sync_actv_hbp                       : 16;  // 16:31
} H13B0_DEF_DISP_SYNC_DLY_CTRL3_T;

/*-----------------------------------------------------------------------------
	0x50a0 def_disp_sync_dly_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_actv_line_start                : 16;  //  0:15
	UINT32 dly_sync_actv_sel_in_h_src              : 1;   //    16
	UINT32 dly_sync_actv_sel_in_v_src              : 1;   //    17
	UINT32 dly_sync_actv_sel_in_h_inv              : 1;   //    18
	UINT32 dly_sync_actv_sel_in_v_inv              : 1;   //    19
	UINT32 dly_sync_actv_sel_out_ha                : 1;   //    20
	UINT32 dly_sync_actv_sel_out_va                : 1;   //    21
	UINT32 dly_sync_actv_sel_out_hs                : 1;   //    22
	UINT32 dly_sync_actv_sel_out_vs                : 1;   //    23
	UINT32                                         : 7;   // 24:30 reserved
	UINT32 dly_sync_actv_force_update              : 1;   //    31
} H13B0_DEF_DISP_SYNC_DLY_CTRL4_T;

/*-----------------------------------------------------------------------------
	0x50a4 def_disp_sync_dly_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_sync_actv_h_dly                     : 16;  //  0:15
	UINT32 dly_sync_actv_v_dly                     : 16;  // 16:31
} H13B0_DEF_DISP_SYNC_DLY_CTRL5_T;

/*-----------------------------------------------------------------------------
	0x50a8 disp_prev_dly_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_prev_vsync                          : 16;  //  0:15
	UINT32 dly_prev_vfp                            : 16;  // 16:31
} H13B0_DISP_PREV_DLY_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x50ac disp_prev_dly_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_prev_va                             : 16;  //  0:15
	UINT32 dly_prev_vbp                            : 16;  // 16:31
} H13B0_DISP_PREV_DLY_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x50b0 disp_prev_dly_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_prev_hsync                          : 16;  //  0:15
	UINT32 dly_prev_hfp                            : 16;  // 16:31
} H13B0_DISP_PREV_DLY_CTRL2_T;

/*-----------------------------------------------------------------------------
	0x50b4 disp_prev_dly_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_prev_ha                             : 16;  //  0:15
	UINT32 dly_prev_hbp                            : 16;  // 16:31
} H13B0_DISP_PREV_DLY_CTRL3_T;

/*-----------------------------------------------------------------------------
	0x50b8 disp_prev_dly_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_prev_line_start                     : 16;  //  0:15
	UINT32 dly_prev_sel_in_h_src                   : 1;   //    16
	UINT32 dly_prev_sel_in_v_src                   : 1;   //    17
	UINT32 dly_prev_sel_in_h_inv                   : 1;   //    18
	UINT32 dly_prev_sel_in_v_inv                   : 1;   //    19
	UINT32 dly_prev_sel_out_ha                     : 1;   //    20
	UINT32 dly_prev_sel_out_va                     : 1;   //    21
	UINT32 dly_prev_sel_out_hs                     : 1;   //    22
	UINT32 dly_prev_sel_out_vs                     : 1;   //    23
	UINT32                                         : 7;   // 24:30 reserved
	UINT32 dly_prev_force_update                   : 1;   //    31
} H13B0_DISP_PREV_DLY_CTRL4_T;

/*-----------------------------------------------------------------------------
	0x50bc disp_prev_dly_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dly_prev_h_dly                          : 16;  //  0:15
	UINT32 dly_prev_v_dly                          : 16;  // 16:31
} H13B0_DISP_PREV_DLY_CTRL5_T;

/*-----------------------------------------------------------------------------
	0x50c0 osd_sync_gen_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sep_osd_sync_vsync                      : 16;  //  0:15
	UINT32 sep_osd_sync_vfp                        : 16;  // 16:31
} H13B0_OSD_SYNC_GEN_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x50c4 osd_sync_gen_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sep_osd_sync_va                         : 16;  //  0:15
	UINT32 sep_osd_sync_vbp                        : 16;  // 16:31
} H13B0_OSD_SYNC_GEN_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x50c8 osd_sync_gen_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sep_osd_sync_hsync                      : 16;  //  0:15
	UINT32 sep_osd_sync_hfp                        : 16;  // 16:31
} H13B0_OSD_SYNC_GEN_CTRL2_T;

/*-----------------------------------------------------------------------------
	0x50cc osd_sync_gen_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sep_osd_sync_ha                         : 16;  //  0:15
	UINT32 sep_osd_sync_hbp                        : 16;  // 16:31
} H13B0_OSD_SYNC_GEN_CTRL3_T;

/*-----------------------------------------------------------------------------
	0x50d0 osd_sync_gen_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                                         : 23;  //  0:22 reserved
	UINT32 sep_osd_sync_vsync_prev                 : 1;   //    23
	UINT32                                         : 7;   // 24:30 reserved
	UINT32 sep_osd_sync_vfp_prev                   : 1;   //    31
} H13B0_OSD_SYNC_GEN_CTRL4_T;

/*-----------------------------------------------------------------------------
	0x50d4 osd_sync_gen_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sep_osd_sync_va_prev                    : 16;  //  0:15
	UINT32 sep_osd_sync_vbp_prev                   : 16;  // 16:31
} H13B0_OSD_SYNC_GEN_CTRL5_T;

/*-----------------------------------------------------------------------------
	0x50d8 osd_sync_gen_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sep_osd_sync_line_start_pos             : 16;  //  0:15
	UINT32 osd_sync_free_run_mode_en               : 1;   //    16
	UINT32 osd_sync_i_vs_edge_sel                  : 1;   //    17
	UINT32 osd_sync_i_hs_edge_sel                  : 1;   //    18
	UINT32                                         : 2;   // 19:20 reserved
	UINT32 update_using_vs_i                       : 1;   //    21
	UINT32 update_at_vs_rise                       : 1;   //    22
	UINT32 sep_osd_sync_manual_reset_value_en_h    : 1;   //    23
	UINT32 sep_osd_sync_manual_reset_value_en_v    : 1;   //    24
	UINT32                                         : 6;   // 25:30 reserved
	UINT32 sep_osd_sync_update_force               : 1;   //    31
} H13B0_OSD_SYNC_GEN_CTRL6_T;

/*-----------------------------------------------------------------------------
	0x50dc osd_sync_gen_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 manual_reset_value_h                    : 16;  //  0:15
	UINT32 manual_reset_value_v                    : 16;  // 16:31
} H13B0_OSD_SYNC_GEN_CTRL7_T;

/*-----------------------------------------------------------------------------
	0x50f0 dppa_pic_end_force ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pic_end_g0_force_en                     : 1;   //     0
	UINT32 pic_end_g0_force                        : 1;   //     1
	UINT32                                         : 2;   //  2: 3 reserved
	UINT32 pic_end_g1_force_en                     : 1;   //     4
	UINT32 pic_end_g1_force                        : 1;   //     5
	UINT32                                         : 2;   //  6: 7 reserved
	UINT32 pic_end_g2_force_en                     : 1;   //     8
	UINT32 pic_end_g2_force                        : 1;   //     9
	UINT32                                         : 2;   // 10:11 reserved
	UINT32 pic_end_g3_force_en                     : 1;   //    12
	UINT32 pic_end_g3_force                        : 1;   //    13
	UINT32                                         : 2;   // 14:15 reserved
	UINT32 pic_end_g4_force_en                     : 1;   //    16
	UINT32 pic_end_g4_force                        : 1;   //    17
} H13B0_DPPA_PIC_END_FORCE_T;

/*-----------------------------------------------------------------------------
	0x50f8 dppa_fpga_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fpga_output_sel                         : 2;   //  0: 1
	UINT32                                         : 2;   //  2: 3 reserved
	UINT32 fpga_pe1_clk_sel                        : 1;   //     4
	UINT32 fpga_osd_clk_sel                        : 1;   //     5
	UINT32 fpga_det_clk_sel                        : 1;   //     6
	UINT32 fpga_out_clk_sel                        : 1;   //     7
	UINT32                                         : 20;  //  8:27 reserved
	UINT32 fpga_detour_en                          : 1;   //    28
} H13B0_DPPA_FPGA_CTRL_T;

/*-----------------------------------------------------------------------------
	0x50fc dppa_gmau_flush ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 gmau_flush_rd_en                        : 1;   //     0
	UINT32                                         : 3;   //  1: 3 reserved
	UINT32 gmau_flush_wr_en                        : 1;   //     4
	UINT32                                         : 3;   //  5: 7 reserved
	UINT32 gmau_flush_rd_done                      : 1;   //     8
	UINT32                                         : 3;   //  9:11 reserved
	UINT32 gmau_flush_wr_done                      : 1;   //    12
} H13B0_DPPA_GMAU_FLUSH_T;

typedef struct {
	H13B0_DEA_CHA_INFO_T                dea_cha_info;                        // 0x0000
	H13B0_DEA_CHB_INFO_T                dea_chb_info;                        // 0x0004
	H13B0_DEA_PIC_INIT_T                dea_pic_init;                        // 0x0008
	H13B0_DEA_PIC_START_T               dea_pic_start;                       // 0x000c
	H13B0_DEA_SMUX_CTRL_T               dea_smux_ctrl;                       // 0x0010
	H13B0_DEA_SMUX_SIZE_T               dea_smux_size;                       // 0x0014
	H13B0_DEA_MVI_V_INFO_T              dea_mvi_v_info;                      // 0x0018
	H13B0_DEA_MVI_H_INFO_T              dea_mvi_h_info;                      // 0x001c
	H13B0_DEA_MVI_CTRL_T                dea_mvi_ctrl;                        // 0x0020
	H13B0_DEA_MSRC_SYNC_MUX_CTRL_T      dea_msrc_sync_mux_ctrl;              // 0x0024
	H13B0_DEA_MSRC_SYNC_DLY_T           dea_msrc_sync_dly;                   // 0x0028
	H13B0_DEA_MEM_SYNC_PERIOD_T         dea_mem_sync_period;                 // 0x002c
	H13B0_DEA_DCO_MFC_T                 dea_dco_mfc;                         // 0x0030
	H13B0_DEA_DCO_DFC_T                 dea_dco_dfc;                         // 0x0034
	H13B0_DEA_DCO_DFLC_T                dea_dco_dflc;                        // 0x0038
	H13B0_DEA_DCO_FCW_T                 dea_dco_fcw;                         // 0x003c
	H13B0_DEA_SMUX_RO_LCNT_T            dea_smux_ro_lcnt;                    // 0x0040
	H13B0_DEA_GMAU_CTRL_T               dea_gmau_ctrl;                       // 0x0044
	H13B0_DEA_PIC_END_EN_T              dea_pic_end_en;                      // 0x0048
	H13B0_DEA_PIC_INIT_G0_TIMER_T       dea_pic_init_g0_timer;               // 0x004c
	H13B0_DEA_PIC_INIT_G1_TIMER_T       dea_pic_init_g1_timer;               // 0x0050
	H13B0_DEA_PIC_END_INFO_T            dea_pic_end_info;                    // 0x0054
	H13B0_DEA_INTR_REG_T                dea_intr_reg;                        // 0x0058
	H13B0_DEA_INTR_MASK_T               dea_intr_mask;                       // 0x005c
	H13B0_DEA_INTR_MUX_T                dea_intr_mux;                        // 0x0060
	H13B0_DEA_SRC_INTR_TIME_STP_T       dea_src_intr_time_stp;               // 0x0064
	H13B0_DE_GPIO_MUX_T                 de_gpio_mux;                         // 0x0068
	H13B0_MSRC_RO_VBLK_CNT_T            msrc_ro_vblk_cnt;                    // 0x006c
	H13B0_DEA_CTRL_GAP_IRQ_INIT_T       dea_ctrl_gap_irq_init;               // 0x0070
	H13B0_DEA_MSRC1_SYNC_MUX_CTRL_T     dea_msrc1_sync_mux_ctrl;             // 0x0074
	H13B0_DEA_MSRC1_SYNC_DLY_T          dea_msrc1_sync_dly;                  // 0x0078
	H13B0_DE_VERSION_T                  de_version;                          // 0x007c
	H13B0_DEA_SMUX_CTRL_1_T             dea_smux_ctrl_1;                     // 0x0080
	H13B0_DEA_SMUX_CTRL_2_T             dea_smux_ctrl_2;                     // 0x0084
	H13B0_DEA_SMUX_CTRL_D_T             dea_smux_ctrl_d;                     // 0x0088
	H13B0_DEA_SMUX_SIZE_D_T             dea_smux_size_d;                     // 0x008c
	H13B0_MSRC1_RO_VBLK_CNT_T           msrc1_ro_vblk_cnt;                   // 0x0090
	H13B0_DEA_VDEC_VSYNC_SRC_SEL_T      dea_vdec_vsync_src_sel;              // 0x0094
	UINT32                              reserved0[2];                        // 0x0098~0x009c
	H13B0_DEA_SMUX_SIZE_I_T             dea_smux_size_i;                     // 0x00a0
	H13B0_DEA_SMUX_HSC_Y_SET_VAL_0_T    dea_smux_hsc_y_set_val_0;            // 0x00a4
	H13B0_DEA_SMUX_HSC_Y_SET_VAL_1_T    dea_smux_hsc_y_set_val_1;            // 0x00a8
	H13B0_DEA_SMUX_HSC_Y_SET_VAL_2_T    dea_smux_hsc_y_set_val_2;            // 0x00ac
	H13B0_DEA_SMUX_HSC_C_SET_VAL_0_T    dea_smux_hsc_c_set_val_0;            // 0x00b0
	H13B0_DEA_SMUX_HSC_C_SET_VAL_1_T    dea_smux_hsc_c_set_val_1;            // 0x00b4
	H13B0_DEA_SMUX_HSC_C_SET_VAL_2_T    dea_smux_hsc_c_set_val_2;            // 0x00b8
	H13B0_DEA_PIC_INIT_SRC_SEL_T        dea_pic_init_src_sel;                // 0x00bc
	H13B0_DEA_MVI_CTRL_0_T              dea_mvi_ctrl_0;                      // 0x00c0
	H13B0_DEA_MVI_CTRL_1_T              dea_mvi_ctrl_1;                      // 0x00c4
	H13B0_DEA_MVI_CTRL_2_T              dea_mvi_ctrl_2;                      // 0x00c8
	H13B0_DEA_MVI_CTRL_3_T              dea_mvi_ctrl_3;                      // 0x00cc
	H13B0_DEA_MVI_CTRL_4_T              dea_mvi_ctrl_4;                      // 0x00d0
	H13B0_DEA_MVI_CTRL_5_T              dea_mvi_ctrl_5;                      // 0x00d4
	H13B0_DEA_MVI_CTRL_6_T              dea_mvi_ctrl_6;                      // 0x00d8
	UINT32                              reserved1;                           // 0x00dc
	H13B0_DEA_PIC_START_DELAY_CTRL_T    dea_pic_start_delay_ctrl;            // 0x00e0
	H13B0_DEA_PIC_START_G0_TIMER_T      dea_pic_start_g0_timer;              // 0x00e4
	H13B0_DEA_PIC_START_G1_TIMER_T      dea_pic_start_g1_timer;              // 0x00e8
	H13B0_DEA_PIC_START_G2_TIMER_T      dea_pic_start_g2_timer;              // 0x00ec
	H13B0_DEA_PIC_INIT_G3_TIMER_T       dea_pic_init_g3_timer;               // 0x00f0
	H13B0_DEA_PIC_END_FORCE_T           dea_pic_end_force;                   // 0x00f4
	H13B0_DEA_FPGA_CTRL_T               dea_fpga_ctrl;                       // 0x00f8
	H13B0_DEA_GMAU_FLUSH_T              dea_gmau_flush;                      // 0x00fc
} DE_DEA_REG_H13B0_T;

typedef struct {
	H13B0_DEB_PIC_INIT_T                deb_pic_init;                        // 0x1000
	H13B0_DEB_PIC_START_T               deb_pic_start;                       // 0x1004
	H13B0_DEB_DISP_V_PORCH_T            deb_disp_v_porch;                    // 0x1008
	H13B0_DEB_DISP_VS_VA_T              deb_disp_vs_va;                      // 0x100c
	H13B0_DEB_DISP_H_PORCH_T            deb_disp_h_porch;                    // 0x1010
	H13B0_DEB_DISP_HS_HA_T              deb_disp_hs_ha;                      // 0x1014
	H13B0_DEB_DISP_SYNC_DLY_T           deb_disp_sync_dly;                   // 0x1018
	H13B0_DEB_DISP_PULSE_DLY_T          deb_disp_pulse_dly;                  // 0x101c
	H13B0_DEB_DISP_SYNC_PARAMS_T        deb_disp_sync_params;                // 0x1020
	UINT32                              reserved2;                           // 0x1024
	H13B0_DEBD_MSDF_CTRL_0_T            debd_msdf_ctrl_0;                    // 0x1028
	UINT32                              reserved3;                           // 0x102c
	H13B0_DEBD_CTRL_PATH_OSD_60HZ_T     debd_ctrl_path_osd_60hz;             // 0x1030
	UINT32                              reserved4[14];                       // 0x1034~0x1068
	H13B0_DEB_GMAU_CTRL_T               deb_gmau_ctrl;                       // 0x106c
	H13B0_DEB_PIC_END_EN_T              deb_pic_end_en;                      // 0x1070
	H13B0_DEB_PIC_INIT_G0_TIMER_T       deb_pic_init_g0_timer;               // 0x1074
	H13B0_DEB_PIC_INIT_G1_TIMER_T       deb_pic_init_g1_timer;               // 0x1078
	H13B0_DEB_PIC_END_INFO_T            deb_pic_end_info;                    // 0x107c
	H13B0_DEB_INTR_REG_T                deb_intr_reg;                        // 0x1080
	H13B0_DEB_INTR_MASK_T               deb_intr_mask;                       // 0x1084
	H13B0_DEB_INTR_MUX_T                deb_intr_mux;                        // 0x1088
	H13B0_DEB_DISP_INTR_TIME_STP_T      deb_disp_intr_time_stp;              // 0x108c
	UINT32                              reserved5[16];                       // 0x1090~0x10cc
	H13B0_DEB_OV_PIC_START_DLY_EN_T     deb_ov_pic_start_dly_en;             // 0x10d0
	H13B0_DEB_PIC_INIT_G1_TIMER_C_T     deb_pic_init_g1_timer_c;             // 0x10d4
	UINT32                              reserved6[8];                        // 0x10d8~0x10f4
	H13B0_DEB_FPGA_CTRL_T               deb_fpga_ctrl;                       // 0x10f8
	H13B0_DEB_GMAU_FLUSH_T              deb_gmau_flush;                      // 0x10fc
} DE_DEB_REG_H13B0_T;

typedef struct {
	H13B0_DEC_PIC_INIT_T                dec_pic_init;                        // 0x2000
	H13B0_DEC_PIC_START_T               dec_pic_start;                       // 0x2004
	H13B0_DEC_SMUX_CTRL_T               dec_smux_ctrl;                       // 0x2008
	H13B0_DEC_SMUX_SIZE_T               dec_smux_size;                       // 0x200c
	H13B0_DEC_MVI_V_INFO_T              dec_mvi_v_info;                      // 0x2010
	H13B0_DEC_MVI_H_INFO_T              dec_mvi_h_info;                      // 0x2014
	H13B0_DEC_MVI_CTRL_T                dec_mvi_ctrl;                        // 0x2018
	H13B0_DEC_MSRC_SYNC_MUX_CTRL_T      dec_msrc_sync_mux_ctrl;              // 0x201c
	H13B0_DEC_MSRC_SYNC_DLY_T           dec_msrc_sync_dly;                   // 0x2020
	H13B0_DEC_MEM0_SYNC_PERIOD_T        dec_mem0_sync_period;                // 0x2024
	H13B0_DEC_MEM1_SYNC_PERIOD_T        dec_mem1_sync_period;                // 0x2028
	H13B0_SRC_SYNC_VBLK_CNT_T           src_sync_vblk_cnt;                   // 0x202c
	H13B0_DEC_SSRC_SYNC_MUX_CTRL_T      dec_ssrc_sync_mux_ctrl;              // 0x2030
	H13B0_DEC_SSRC_SYNC_DLY_T           dec_ssrc_sync_dly;                   // 0x2034
	H13B0_MVI_T_0_V_CLIP_CTRL_T         mvi_t_0_v_clip_ctrl;                 // 0x2038
	H13B0_MVI_T_1_V_CLIP_CTRL_T         mvi_t_1_v_clip_ctrl;                 // 0x203c
	H13B0_DEC_SMUX_CTRL_1_T             dec_smux_ctrl_1;                     // 0x2040
	H13B0_DEC_SMUX_CTRL_2_T             dec_smux_ctrl_2;                     // 0x2044
	H13B0_DEC_SMUX_CTRL_D_T             dec_smux_ctrl_d;                     // 0x2048
	H13B0_DEC_SMUX_SIZE_D_T             dec_smux_size_d;                     // 0x204c
	H13B0_DEC_MSRC1_SYNC_MUX_CTRL_T     dec_msrc1_sync_mux_ctrl;             // 0x2050
	H13B0_DEC_MSRC1_SYNC_DLY_T          dec_msrc1_sync_dly;                  // 0x2054
	H13B0_DEC_CTRL_GAP_IRQ_INIT_T       dec_ctrl_gap_irq_init;               // 0x2058
	H13B0_DEC_SMUX_RO_LCNT_T            dec_smux_ro_lcnt;                    // 0x205c
	H13B0_DEC_GMAU_CTRL_T               dec_gmau_ctrl;                       // 0x2060
	H13B0_DEC_PIC_END_EN_T              dec_pic_end_en;                      // 0x2064
	H13B0_DEC_PIC_INIT_G0_TIMER_T       dec_pic_init_g0_timer;               // 0x2068
	H13B0_DEC_PIC_INIT_G1_TIMER_T       dec_pic_init_g1_timer;               // 0x206c
	H13B0_DEC_PIC_INIT_G2_TIMER_T       dec_pic_init_g2_timer;               // 0x2070
	H13B0_DEC_PIC_END_INFO_T            dec_pic_end_info;                    // 0x2074
	H13B0_DEC_INTR_REG_T                dec_intr_reg;                        // 0x2078
	H13B0_DEC_INTR_MASK_T               dec_intr_mask;                       // 0x207c
	H13B0_DEC_INTR_MUX_T                dec_intr_mux;                        // 0x2080
	H13B0_DEC_MSRC_INTR_TIME_STP_T      dec_msrc_intr_time_stp;              // 0x2084
	H13B0_DEC_SSRC_INTR_TIME_STP_T      dec_ssrc_intr_time_stp;              // 0x2088
	H13B0_DEC_MVI_READY_CTRL_T          dec_mvi_ready_ctrl;                  // 0x208c
	H13B0_DEC_MVI_PATH_SEL_T            dec_mvi_path_sel;                    // 0x2090
	H13B0_DEC_VDEC_VSYNC_SRC_SEL_T      dec_vdec_vsync_src_sel;              // 0x2094
	UINT32                              reserved7[2];                        // 0x2098~0x209c
	H13B0_DEC_SMUX_SIZE_I_T             dec_smux_size_i;                     // 0x20a0
	H13B0_DEC_SMUX_HSC_Y_SET_VAL_0_T    dec_smux_hsc_y_set_val_0;            // 0x20a4
	H13B0_DEC_SMUX_HSC_Y_SET_VAL_1_T    dec_smux_hsc_y_set_val_1;            // 0x20a8
	H13B0_DEC_SMUX_HSC_Y_SET_VAL_2_T    dec_smux_hsc_y_set_val_2;            // 0x20ac
	H13B0_DEC_SMUX_HSC_C_SET_VAL_0_T    dec_smux_hsc_c_set_val_0;            // 0x20b0
	H13B0_DEC_SMUX_HSC_C_SET_VAL_1_T    dec_smux_hsc_c_set_val_1;            // 0x20b4
	H13B0_DEC_SMUX_HSC_C_SET_VAL_2_T    dec_smux_hsc_c_set_val_2;            // 0x20b8
	H13B0_DEC_PIC_INIT_SRC_SEL_T        dec_pic_init_src_sel;                // 0x20bc
	H13B0_DEC_MVI_CTRL_0_T              dec_mvi_ctrl_0;                      // 0x20c0
	H13B0_DEC_MVI_CTRL_1_T              dec_mvi_ctrl_1;                      // 0x20c4
	H13B0_DEC_MVI_CTRL_2_T              dec_mvi_ctrl_2;                      // 0x20c8
	H13B0_DEC_MVI_CTRL_3_T              dec_mvi_ctrl_3;                      // 0x20cc
	H13B0_DEC_MVI_CTRL_4_T              dec_mvi_ctrl_4;                      // 0x20d0
	H13B0_DEC_MVI_CTRL_5_T              dec_mvi_ctrl_5;                      // 0x20d4
	H13B0_DEC_MVI_CTRL_6_T              dec_mvi_ctrl_6;                      // 0x20d8
	UINT32                              reserved8;                           // 0x20dc
	H13B0_DEC_PIC_START_DELAY_CTRL_T    dec_pic_start_delay_ctrl;            // 0x20e0
	H13B0_DEC_PIC_START_G0_TIMER_T      dec_pic_start_g0_timer;              // 0x20e4
	H13B0_DEC_PIC_START_G1_TIMER_T      dec_pic_start_g1_timer;              // 0x20e8
	H13B0_DEC_PIC_START_G2_TIMER_T      dec_pic_start_g2_timer;              // 0x20ec
	H13B0_DEC_PIC_INIT_G3_TIMER_T       dec_pic_init_g3_timer;               // 0x20f0
	H13B0_DEC_PIC_END_FORCE_T           dec_pic_end_force;                   // 0x20f4
	H13B0_DEC_FPGA_CTRL_T               dec_fpga_ctrl;                       // 0x20f8
	H13B0_DEC_GMAU_FLUSH_T              dec_gmau_flush;                      // 0x20fc
} DE_DEC_REG_H13B0_T;

typedef struct {
	H13B0_DED_PIC_INIT_T                ded_pic_init;                        // 0x3000
	H13B0_DED_PIC_START_T               ded_pic_start;                       // 0x3004
	H13B0_DED_DE_VENC_IF_T              ded_de_venc_if;                      // 0x3008
	UINT32                              reserved9;                           // 0x300c
	H13B0_DED_CVE_PARAM0_T              ded_cve_param0;                      // 0x3010
	H13B0_DED_CVE_PARAM1_T              ded_cve_param1;                      // 0x3014
	H13B0_DED_CVE_PARAM2_T              ded_cve_param2;                      // 0x3018
	H13B0_DED_CVE_PARAM3_T              ded_cve_param3;                      // 0x301c
	H13B0_DED_CVE_PULSE_DLY_T           ded_cve_pulse_dly;                   // 0x3020
	H13B0_DED_GMAU_CTRL_T               ded_gmau_ctrl;                       // 0x3024
	H13B0_DED_PIC_END_EN_T              ded_pic_end_en;                      // 0x3028
	H13B0_DED_PIC_INIT_G0_TIMER_T       ded_pic_init_g0_timer;               // 0x302c
	H13B0_DED_PIC_INIT_G1_TIMER_T       ded_pic_init_g1_timer;               // 0x3030
	UINT32                              reserved10;                          // 0x3034
	H13B0_DED_PIC_INIT_G3_TIMER_T       ded_pic_init_g3_timer;               // 0x3038
	H13B0_DED_PIC_END_INFO_T            ded_pic_end_info;                    // 0x303c
	H13B0_DED_INTR_REG_T                ded_intr_reg;                        // 0x3040
	H13B0_DED_INTR_MASK_T               ded_intr_mask;                       // 0x3044
	H13B0_DED_INTR_MUX_T                ded_intr_mux;                        // 0x3048
	H13B0_DEF_CVE_INTR_TIME_STP_T       def_cve_intr_time_stp;               // 0x304c
	UINT32                              reserved11[16];                      // 0x3050~0x308c
	H13B0_DED_DISP_SYNC_DLY_CTRL0_T     ded_disp_sync_dly_ctrl0;             // 0x3090
	H13B0_DED_DISP_SYNC_DLY_CTRL1_T     ded_disp_sync_dly_ctrl1;             // 0x3094
	H13B0_DED_DISP_SYNC_DLY_CTRL2_T     ded_disp_sync_dly_ctrl2;             // 0x3098
	H13B0_DED_DISP_SYNC_DLY_CTRL3_T     ded_disp_sync_dly_ctrl3;             // 0x309c
	H13B0_DED_DISP_SYNC_DLY_CTRL4_T     ded_disp_sync_dly_ctrl4;             // 0x30a0
	H13B0_DED_DISP_SYNC_DLY_CTRL5_T     ded_disp_sync_dly_ctrl5;             // 0x30a4
	H13B0_DISP_PULSE_DLY_TIMER_T        disp_pulse_dly_timer;                // 0x30a8
	H13B0_DED_SYNC_CTRL_T               ded_sync_ctrl;                       // 0x30ac
	UINT32                              reserved12[8];                       // 0x30b0~0x30cc
	H13B0_DED_OV_PIC_START_DLY_EN_T     ded_ov_pic_start_dly_en;             // 0x30d0
	H13B0_DED_PIC_INIT_G1_TIMER_C_T     ded_pic_init_g1_timer_c;             // 0x30d4
	UINT32                              reserved13[8];                       // 0x30d8~0x30f4
	H13B0_DED_FPGA_CTRL_T               ded_fpga_ctrl;                       // 0x30f8
	H13B0_DED_GMAU_FLUSH_T              ded_gmau_flush;                      // 0x30fc
} DE_DED_REG_H13B0_T;

typedef struct {
	H13B0_DEC_DE_INTR_FLAG_MCU_T        dec_de_intr_flag_mcu;                // 0x4000
	H13B0_DEC_DE_INTR_FLAG_CPU_T        dec_de_intr_flag_cpu;                // 0x4004
	H13B0_DEE_CVI_MUX_SEL_T             dee_cvi_mux_sel;                     // 0x4008
	H13B0_DEE_PE0_HIF_OFFSET_T          dee_pe0_hif_offset;                  // 0x400c
	H13B0_DEE_SM_HIF_OFFSET_T           dee_sm_hif_offset;                   // 0x4010
	H13B0_DEE_PE1_HIF_OFFSET_T          dee_pe1_hif_offset;                  // 0x4014
	UINT32                              reserved14[6];                       // 0x4018~0x4030
	H13B0_DEE_INTR_REG_T                dee_intr_reg;                        // 0x4034
	H13B0_DEE_INTR_MASK_T               dee_intr_mask;                       // 0x4038
	UINT32                              reserved15[5];                       // 0x403c~0x404c
	H13B0_DEE_HDMI_BRIDGE_CTRL0_T       dee_hdmi_bridge_ctrl0;               // 0x4050
	H13B0_DEE_HDMI_BRIDGE_CTRL1_T       dee_hdmi_bridge_ctrl1;               // 0x4054
	H13B0_DEE_HDMI_BRIDGE_CTRL2_T       dee_hdmi_bridge_ctrl2;               // 0x4058
	H13B0_DEE_HDMI_BRIDGE_CTRL3_T       dee_hdmi_bridge_ctrl3;               // 0x405c
	H13B0_DEE_HDMI_BRIDGE_CTRL4_T       dee_hdmi_bridge_ctrl4;               // 0x4060
	H13B0_DEE_HDMI_BRIDGE_CTRL5_T       dee_hdmi_bridge_ctrl5;               // 0x4064
	H13B0_DEE_HDMI_BRIDGE_CTRL6_T       dee_hdmi_bridge_ctrl6;               // 0x4068
	H13B0_DEE_HDMI_BRIDGE_CTRL7_T       dee_hdmi_bridge_ctrl7;               // 0x406c
	H13B0_DEE_HDMI_BRIDGE_CTRL8_T       dee_hdmi_bridge_ctrl8;               // 0x4070
	H13B0_DEE_HDMI_BRIDGE_CTRL9_T       dee_hdmi_bridge_ctrl9;               // 0x4074
	H13B0_DEE_HDMI_BRIDGE_CTRL10_T      dee_hdmi_bridge_ctrl10;              // 0x4078
	H13B0_DEE_HDMI_BRIDGE_CTRL11_T      dee_hdmi_bridge_ctrl11;              // 0x407c
	H13B0_DEE_HDMI_BRIDGE_CTRL12_T      dee_hdmi_bridge_ctrl12;              // 0x4080
	H13B0_DEE_HDMI_BRIDGE_CTRL13_T      dee_hdmi_bridge_ctrl13;              // 0x4084
	UINT32                              reserved20[28];                      // 0x4088~0x40f4
	H13B0_DEE_FPGA_CTRL_T               dee_fpga_ctrl;                       // 0x40f8
	H13B0_DEE_GMAU_FLUSH_T              dee_gmau_flush;                      // 0x40fc
} DE_DEE_REG_H13B0_T;

typedef struct {
	H13B0_DPPA_PIC_INIT_T               dppa_pic_init;                       // 0x5000
	H13B0_DPPA_PIC_START_T              dppa_pic_start;                      // 0x5004
	UINT32                              reserved21;                          // 0x5008
	H13B0_DPPA_DPATH_CTRL_T             dppa_dpath_ctrl;                     // 0x500c
	H13B0_DPPA_SYNC_CTRL_T              dppa_sync_ctrl;                      // 0x5010
	UINT32                              reserved22[3];                       // 0x5014~0x501c
	H13B0_DPPA_DISP_PULSE_CTRL_T        dppa_disp_pulse_ctrl;                // 0x5020
	UINT32                              reserved23[4];                       // 0x5024~0x5030
	H13B0_DPPA_PIC_INIT_G2_TIMER_T      dppa_pic_init_g2_timer;              // 0x5034
	H13B0_DPPA_PIC_INIT_G3_TIMER_T      dppa_pic_init_g3_timer;              // 0x5038
	H13B0_DPPA_PIC_END_INFO_T           dppa_pic_end_info;                   // 0x503c
	H13B0_DPPA_INTR_REG_T               dppa_intr_reg;                       // 0x5040
	H13B0_DPPA_INTR_MASK_T              dppa_intr_mask;                      // 0x5044
	H13B0_DPPA_INTR_MUX_T               dppa_intr_mux;                       // 0x5048
	H13B0_DPPA_MIF_2ND_PIC_CTRL_T       dppa_mif_2nd_pic_ctrl;               // 0x504c
	H13B0_DPPA_DISP60HZ_PULSE_CTRL_T    dppa_disp60hz_pulse_ctrl;            // 0x5050
	H13B0_DPPA_PIC_INIT_G4_TIMER_T      dppa_pic_init_g4_timer;              // 0x5054
	H13B0_DPPA_MIF_60HZ_PIC_CTRL_T      dppa_mif_60hz_pic_ctrl;              // 0x5058
	UINT32                              reserved24;                          // 0x505c
	H13B0_DPPA_MOF_CTRL0_T              dppa_mof_ctrl0;                      // 0x5060
	H13B0_DPPA_MOF_CTRL1_T              dppa_mof_ctrl1;                      // 0x5064
	H13B0_DPPA_MOF_CTRL2_T              dppa_mof_ctrl2;                      // 0x5068
	H13B0_DPPA_MOF_CTRL3_T              dppa_mof_ctrl3;                      // 0x506c
	H13B0_DPPA_MOF_CTRL4_T              dppa_mof_ctrl4;                      // 0x5070
	H13B0_DPPA_MOF_CTRL5_T              dppa_mof_ctrl5;                      // 0x5074
	H13B0_DPPA_MOF_CTRL6_T              dppa_mof_ctrl6;                      // 0x5078
	H13B0_DPPA_MOF_CTRL7_T              dppa_mof_ctrl7;                      // 0x507c
	H13B0_DPPA_MOF_CTRL8_T              dppa_mof_ctrl8;                      // 0x5080
	UINT32                              reserved25[3];                       // 0x5084~0x508c
	H13B0_DEF_DISP_SYNC_DLY_CTRL0_T     def_disp_sync_dly_ctrl0;             // 0x5090
	H13B0_DEF_DISP_SYNC_DLY_CTRL1_T     def_disp_sync_dly_ctrl1;             // 0x5094
	H13B0_DEF_DISP_SYNC_DLY_CTRL2_T     def_disp_sync_dly_ctrl2;             // 0x5098
	H13B0_DEF_DISP_SYNC_DLY_CTRL3_T     def_disp_sync_dly_ctrl3;             // 0x509c
	H13B0_DEF_DISP_SYNC_DLY_CTRL4_T     def_disp_sync_dly_ctrl4;             // 0x50a0
	H13B0_DEF_DISP_SYNC_DLY_CTRL5_T     def_disp_sync_dly_ctrl5;             // 0x50a4
	H13B0_DISP_PREV_DLY_CTRL0_T         disp_prev_dly_ctrl0;                 // 0x50a8
	H13B0_DISP_PREV_DLY_CTRL1_T         disp_prev_dly_ctrl1;                 // 0x50ac
	H13B0_DISP_PREV_DLY_CTRL2_T         disp_prev_dly_ctrl2;                 // 0x50b0
	H13B0_DISP_PREV_DLY_CTRL3_T         disp_prev_dly_ctrl3;                 // 0x50b4
	H13B0_DISP_PREV_DLY_CTRL4_T         disp_prev_dly_ctrl4;                 // 0x50b8
	H13B0_DISP_PREV_DLY_CTRL5_T         disp_prev_dly_ctrl5;                 // 0x50bc
	H13B0_OSD_SYNC_GEN_CTRL0_T          osd_sync_gen_ctrl0;                  // 0x50c0
	H13B0_OSD_SYNC_GEN_CTRL1_T          osd_sync_gen_ctrl1;                  // 0x50c4
	H13B0_OSD_SYNC_GEN_CTRL2_T          osd_sync_gen_ctrl2;                  // 0x50c8
	H13B0_OSD_SYNC_GEN_CTRL3_T          osd_sync_gen_ctrl3;                  // 0x50cc
	H13B0_OSD_SYNC_GEN_CTRL4_T          osd_sync_gen_ctrl4;                  // 0x50d0
	H13B0_OSD_SYNC_GEN_CTRL5_T          osd_sync_gen_ctrl5;                  // 0x50d4
	H13B0_OSD_SYNC_GEN_CTRL6_T          osd_sync_gen_ctrl6;                  // 0x50d8
	H13B0_OSD_SYNC_GEN_CTRL7_T          osd_sync_gen_ctrl7;                  // 0x50dc
	UINT32                              reserved26[4];                       // 0x50e0~0x50ec
	H13B0_DPPA_PIC_END_FORCE_T          dppa_pic_end_force;                  // 0x50f0
	UINT32                              reserved27;                          // 0x50f4
	H13B0_DPPA_FPGA_CTRL_T              dppa_fpga_ctrl;                      // 0x50f8
	H13B0_DPPA_GMAU_FLUSH_T             dppa_gmau_flush;                     // 0x50fc
} DE_DEF_REG_H13B0_T;

#endif
