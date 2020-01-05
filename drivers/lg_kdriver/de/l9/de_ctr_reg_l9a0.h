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

#ifndef _REG_CTR_L9A0_h
#define _REG_CTR_L9A0_h

typedef struct { // 0x0000
	UINT32 cha_hsize               : 12;  // 11: 0
	UINT32                         : 1;   //    12
	UINT32 cha_csample             : 1;   //    13
	UINT32 cha_aspect              : 1;   //    14
	UINT32                         : 1;   //    15
	UINT32 cha_vsize               : 12;  // 27:16
	UINT32                         : 1;   //    28
	UINT32 cha_frame_lr            : 1;   //    29
	UINT32 cha_field_id            : 1;   //    30
	UINT32 cha_pr_sq               : 1;   //    31
} L9A0_DEA_CHA_INFO_T;

typedef struct { // 0x0004
	UINT32 chb_hsize               : 12;  // 11: 0
	UINT32                         : 1;   //    12
	UINT32 chb_csample             : 1;   //    13
	UINT32 chb_aspect              : 1;   //    14
	UINT32                         : 1;   //    15
	UINT32 chb_vsize               : 12;  // 27:16
	UINT32                         : 1;   //    28
	UINT32 chb_frame_lr            : 1;   //    29
	UINT32 chb_field_id            : 1;   //    30
	UINT32 chb_pr_sq               : 1;   //    31
} L9A0_DEA_CHB_INFO_T;

typedef struct { // 0x0008
	UINT32 pic_init_g0             : 1;   //     0
	UINT32 pic_init_g1             : 1;   //     1
} L9A0_DEA_PIC_INIT_T;

typedef struct { // 0x000c
	UINT32 pic_start_g0            : 1;   //     0
	UINT32 pic_start_g1            : 1;   //     1
} L9A0_DEA_PIC_START_T;

typedef struct { // 0x0010
	UINT32 o_c_fmt                 : 3;   //  2: 0
	UINT32                         : 1;   //     3
	UINT32 i_c_fmt                 : 3;   //  6: 4
	UINT32                         : 1;   //     7
	UINT32 dec3d_mux_sel           : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 prew_mux_sel            : 1;   //    12
	UINT32 d3_lr_sel               : 1;   //    13
	UINT32                         : 2;   // 15:14
	UINT32 cvi_mux_sel             : 2;   // 17:16
	UINT32                         : 2;   // 19:18
	UINT32 nline_inc               : 1;   //    20
	UINT32                         : 2;   // 22:21
	UINT32 wr_disalbe              : 1;   //    23
	UINT32 fieldid                 : 1;   //    24
	UINT32                         : 6;   // 30:25
	UINT32 pr_sq                   : 1;   //    31
} L9A0_DEA_SMUX_CTRL_T;

typedef struct { // 0x0014
	UINT32 hsize                   : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 vsize                   : 12;  // 27:16
} L9A0_DEA_SMUX_SIZE_T;

typedef struct { // 0x0018
	UINT32 mvi_vsize               : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 mvi_vblank              : 12;  // 27:16
} L9A0_DEA_MVI_V_INFO_T;

typedef struct { // 0x001c
	UINT32 mvi_hsize               : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 mvi_hblank              : 12;  // 27:16
} L9A0_DEA_MVI_H_INFO_T;

typedef struct { // 0x0020
	UINT32 mvi_i_c_fmt             : 3;   //  2: 0
	UINT32                         : 1;   //     3
	UINT32 mvi_field               : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 mvi_pr_sq               : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 mvi_cvi_stride          : 1;   //    12
} L9A0_DEA_MVI_CTRL_T;

typedef struct { // 0x0024
	UINT32 trans_mask_en           : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 cvi_select              : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 mvi_select              : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 mvi_cvi_select          : 1;   //    12
} L9A0_DEA_MSRC_SYNC_MUX_CTRL_T;

typedef struct { // 0x0028
	UINT32 msrc_sync_dly           : 28;  // 27: 0
} L9A0_DEA_MSRC_SYNC_DLY_T;

typedef struct { // 0x002c
	UINT32 mem_sync_period         : 28;  // 27: 0
} L9A0_DEA_MEM_SYNC_PERIOD_T;

typedef struct { // 0x0030
	UINT32 dco_mfc                 : 28;  // 27: 0
} L9A0_DEA_DCO_MFC_T;

typedef struct { // 0x0034
	UINT32 dco_dfc                 : 28;  // 27: 0
} L9A0_DEA_DCO_DFC_T;

typedef struct { // 0x0038
	UINT32 dco_dflc                : 12;  // 11: 0
} L9A0_DEA_DCO_DFLC_T;

typedef struct { // 0x003c
	UINT32 dco_fcw                 : 22;  // 21: 0
} L9A0_DEA_DCO_FCW_T;

typedef struct { // 0x0040
	UINT32 smux_ro_lcnt            : 12;  // 11: 0
} L9A0_DEA_SMUX_RO_LCNT_T;

typedef struct { // 0x0044
	UINT32 ask_cmd_dly_cnt         : 8;   //  7: 0
	UINT32                         : 8;   // 15: 8
	UINT32 ask_to_cnt              : 10;  // 25:16
} L9A0_DEA_GMAU_CTRL_T;

typedef struct { // 0x0048
	UINT32 ipc_en                  : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 clc_en                  : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 tnr_en                  : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 pe0_en                  : 1;   //    12
	UINT32                         : 3;   // 15:13
	UINT32 prew_en                 : 1;   //    16
	UINT32                         : 3;   // 19:17
	UINT32 smux_en                 : 1;   //    20
} L9A0_DEA_PIC_END_EN_T;

typedef struct { // 0x004c
	UINT32 pic_init_g0_timer       : 28;  // 27: 0
} L9A0_DEA_PIC_INIT_G0_TIMER_T;

typedef struct { // 0x0050
	UINT32 pic_init_g1_timer       : 28;  // 27: 0
} L9A0_DEA_PIC_INIT_G1_TIMER_T;

typedef struct { // 0x0054
	UINT32 pic_end_g0              : 5;   //  4: 0
	UINT32 pic_end_g1              : 8;   // 12: 5
} L9A0_DEA_PIC_END_INFO_T;

typedef struct { // 0x0058
	UINT32 pic_end_g0              : 1;   //     0
	UINT32 pic_end_g1              : 1;   //     1
	UINT32 cha_input_intr          : 1;   //     2
	UINT32 chb_input_intr          : 1;   //     3
	UINT32 cha_field_intr          : 1;   //     4
	UINT32 cha_frame_lr_intr       : 1;   //     5
	UINT32 chb_field_intr          : 1;   //     6
	UINT32 chb_frame_lr_intr       : 1;   //     7
	UINT32 pe0_intr                : 1;   //     8
	UINT32 smux_ow_intr            : 1;   //     9
	UINT32                         : 2;   // 11:10
	UINT32 gmau_flush_rd_done      : 1;   //    12
	UINT32 gmau_flush_wr_done      : 1;   //    13
	UINT32                         : 9;   // 22:14
	UINT32 src_intr                : 1;   //    23
} L9A0_DEA_INTR_REG_T;

typedef struct { // 0x005c
	UINT32 dea_intr_mask           : 28;  // 27: 0
} L9A0_DEA_INTR_MASK_T;

typedef struct { // 0x0060
	UINT32 dea_intr_mux            : 28;  // 27: 0
} L9A0_DEA_INTR_MUX_T;

typedef struct { // 0x0064
	UINT32 src_intr_time_stp       : 32;  // 31: 0
} L9A0_DEA_SRC_INTR_TIME_STP_T;

typedef struct { // 0x0068
	UINT32 de_gpio_mux             : 2;   //  1: 0
} L9A0_DE_GPIO_MUX_T;

typedef struct { // 0x006c
	UINT32                         : 3;   //  2: 0
	UINT32 dea_addr_sav_bus        : 7;   //  9: 3
	UINT32                         : 6;   // 15:10
	UINT32 dea_addr_default_bus    : 2;   // 17:16
	UINT32                         : 6;   // 23:18
	UINT32 dea_addr_de_bus         : 6;   // 29:24
} L9A0_DEA_ADDR_SW_DE_SAV_T;

typedef struct { // 0x0070
	UINT32                         : 3;   //  2: 0
	UINT32 dea_addr_gpu_bus        : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 dea_addr_gpu_logic      : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 dea_addr_cpu_h_bus      : 4;   // 27:24
} L9A0_DEA_ADDR_SW_CPU_GPU_T;

typedef struct { // 0x0074
	UINT32                         : 3;   //  2: 0
	UINT32 dea_addr_shadow_bus     : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 dea_addr_shadow_logic   : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 dea_addr_cpu_l_bus      : 6;   // 29:24
} L9A0_DEA_ADDR_SW_CPU_SHADOW_T;

typedef struct { // 0x0078
	UINT32 gmau_flush_rd_en        : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 gmau_flush_wr_en        : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 gmau_flush_rd_done      : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 gmau_flush_wr_done      : 1;   //    12
} L9A0_DEA_GMAU_FLUSH_T;

typedef struct { // 0x007c
	UINT32 de_version              : 32;  // 31: 0
} L9A0_DE_VERSION_T;

typedef struct { // 0x1000
	UINT32 pic_init_g0             : 1;   //     0
	UINT32 pic_init_g1             : 1;   //     1
	UINT32                         : 14;  // 15: 2
	UINT32 ov_auto_init            : 1;   //    16
} L9A0_DEB_PIC_INIT_T;

typedef struct { // 0x1004
	UINT32 pic_start_g0            : 1;   //     0
	UINT32 pic_start_g1            : 1;   //     1
} L9A0_DEB_PIC_START_T;

typedef struct { // 0x1008
	UINT32 vsync_bp                : 16;  // 15: 0
	UINT32 vsync_fp                : 16;  // 31:16
} L9A0_DEB_DISP_V_PORCH_T;

typedef struct { // 0x100c
	UINT32 disp_sync_va            : 16;  // 15: 0
	UINT32 vsync                   : 16;  // 31:16
} L9A0_DEB_DISP_VS_VA_T;

typedef struct { // 0x1010
	UINT32 hsync_bp                : 16;  // 15: 0
	UINT32 hsync_fp                : 16;  // 31:16
} L9A0_DEB_DISP_H_PORCH_T;

typedef struct { // 0x1014
	UINT32 disp_sync_ha            : 16;  // 15: 0
	UINT32 hsync                   : 16;  // 31:16
} L9A0_DEB_DISP_HS_HA_T;

typedef struct { // 0x1018
	UINT32 hoffset1                : 16;  // 15: 0
	UINT32 voffset1                : 16;  // 31:16
} L9A0_DEB_DISP_SYNC_DLY_T;

typedef struct { // 0x101c
	UINT32 deb_disp_pulse_dly_f    : 32;   // 31: 0
} L9A0_DEB_DISP_PULSE_DLY_T;

typedef struct { // 0x1020
	UINT32 hoffset0                : 16;  // 15: 0
	UINT32                         : 11;  // 26:16
	UINT32 disp_frame_lr           : 1;   //    27
	UINT32                         : 3;   // 30:28
	UINT32 force_update            : 1;   //    31
} L9A0_DEB_DISP_SYNC_PARAMS_T;

typedef struct { // 0x1024
	UINT32 pwm0_r_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm0_r_v                : 11;  // 26:16
} L9A0_DEB_PWM_R0_T;

typedef struct { // 0x1028
	UINT32 pwm0_f_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm0_f_v                : 11;  // 26:16
} L9A0_DEB_PWM_F0_T;

typedef struct { // 0x102c
	UINT32 pwm1_r_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm1_r_v                : 11;  // 26:16
} L9A0_DEB_PWM_R1_T;

typedef struct { // 0x1030
	UINT32 pwm1_f_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm1_f_v                : 11;  // 26:16
} L9A0_DEB_PWM_F1_T;

typedef struct { // 0x1034
	UINT32 pwm2_r_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm2_r_v                : 11;  // 26:16
} L9A0_DEB_PWM_R2_T;

typedef struct { // 0x1038
	UINT32 pwm2_f_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm2_f_v                : 11;  // 26:16
} L9A0_DEB_PWM_F2_T;

typedef struct { // 0x103c
	UINT32 pwm3_r_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm3_r_v                : 11;  // 26:16
} L9A0_DEB_PWM_R3_T;

typedef struct { // 0x1040
	UINT32 pwm3_f_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm3_f_v                : 11;  // 26:16
} L9A0_DEB_PWM_F3_T;

typedef struct { // 0x1044
	UINT32 pwm4_r_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm4_r_v                : 11;  // 26:16
} L9A0_DEB_PWM_R4_T;

typedef struct { // 0x1048
	UINT32 pwm4_f_h                : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 pwm4_f_v                : 11;  // 26:16
} L9A0_DEB_PWM_F4_T;

typedef struct { // 0x104c
	UINT32 pwm0_sub_r_v            : 11;  // 10: 0
} L9A0_DEB_PWM_SUB_R0_T;

typedef struct { // 0x1050
	UINT32 pwm1_sub_r_v            : 11;  // 10: 0
} L9A0_DEB_PWM_SUB_R1_T;

typedef struct { // 0x1054
	UINT32 pwm2_sub_r_v            : 11;  // 10: 0
} L9A0_DEB_PWM_SUB_R2_T;

typedef struct { // 0x1058
	UINT32 pwm3_sub_r_v            : 11;  // 10: 0
} L9A0_DEB_PWM_SUB_R3_T;

typedef struct { // 0x105c
	UINT32 pwm4_sub_r_v            : 11;  // 10: 0
} L9A0_DEB_PWM_SUB_R4_T;

typedef struct { // 0x1060
	UINT32 pwm_inv                 : 5;   //  4: 0
	UINT32 pwm_fc_l                : 5;   //  9: 5
	UINT32 pwm_fc_h                : 5;   // 14:10
} L9A0_DEB_PWM_CTRL_T;

typedef struct { // 0x1064
	UINT32 pwm_sel                 : 5;   //  4: 0
} L9A0_DEB_PWM_SEL_T;

typedef struct { // 0x1068
	UINT32 t3_mux_sel              : 2;   //  1: 0
	UINT32                         : 2;   //  3: 2
	UINT32 fb_mux_sel              : 1;   //     4
} L9A0_DEB_DPATH_CTRL_T;

typedef struct { // 0x106c
	UINT32 ask_cmd_dly_cnt         : 8;   //  7: 0
	UINT32                         : 8;   // 15: 8
	UINT32 ask_to_cnt              : 10;  // 25:16
} L9A0_DEB_GMAU_CTRL_T;

typedef struct { // 0x1070
	UINT32 ov_ss_en                : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 ov_en                   : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 sm_en                   : 1;   //     8
} L9A0_DEB_PIC_END_EN_T;

typedef struct { // 0x1074
	UINT32 pic_init_g0_timer       : 28;  // 27: 0
} L9A0_DEB_PIC_INIT_G0_TIMER_T;

typedef struct { // 0x1078
	UINT32 pic_init_g1_timer       : 28;  // 27: 0
} L9A0_DEB_PIC_INIT_G1_TIMER_T;

typedef struct { // 0x107c
	UINT32 pic_end_g0              : 3;   //  2: 0
	UINT32                         : 1;   //     3
	UINT32 pic_end_g1              : 5;   //  8: 4
} L9A0_DEB_PIC_END_INFO_T;

typedef struct { // 0x1080
	UINT32 intr_end_g0             : 1;   //     0
	UINT32                         : 1;   //     1
	UINT32 disp_intr_for_cpu       : 1;   //     2
	UINT32                         : 1;   //     3
	UINT32 intr_end_g1             : 1;   //     4
	UINT32                         : 1;   //     5
	UINT32 disp_intr_for_mcu       : 1;   //     6
	UINT32 ov_underflow            : 1;   //     7
} L9A0_DEB_INTR_REG_T;

typedef struct { // 0x1084
	UINT32 deb_intr_mask_f         : 32;   // 31: 0
} L9A0_DEB_INTR_MASK_T;

typedef struct { // 0x1088
	UINT32 deb_intr_mux_f          : 32;   // 31: 0
} L9A0_DEB_INTR_MUX_T;

typedef struct { // 0x108c
	UINT32 deb_disp_intr_time_stp_f: 32;   // 31: 0
} L9A0_DEB_DISP_INTR_TIME_STP_T;

typedef struct { // 0x1090
	UINT32                         : 3;   //  2: 0
	UINT32 deb_addr_sav_bus        : 7;   //  9: 3
	UINT32                         : 6;   // 15:10
	UINT32 deb_addr_default_bus    : 2;   // 17:16
	UINT32                         : 6;   // 23:18
	UINT32 deb_addr_de_bus         : 6;   // 29:24
} L9A0_DEB_ADDR_SW_DE_SAV_T;

typedef struct { // 0x1094
	UINT32                         : 3;   //  2: 0
	UINT32 deb_addr_gpu_bus        : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 deb_addr_gpu_logic      : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 deb_addr_cpu_h_bus      : 4;   // 27:24
} L9A0_DEB_ADDR_SW_CPU_GPU_T;

typedef struct { // 0x1098
	UINT32                         : 3;   //  2: 0
	UINT32 deb_addr_shadow_bus     : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 deb_addr_shadow_logic   : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 deb_addr_cpu_l_bus      : 6;   // 29:24
} L9A0_DEB_ADDR_SW_CPU_SHADOW_T;

typedef struct { // 0x2000
	UINT32 pic_init_g0             : 1;   //     0
	UINT32 pic_init_g1             : 1;   //     1
	UINT32 pic_init_g2             : 1;   //     2
} L9A0_DEC_PIC_INIT_T;

typedef struct { // 0x2004
	UINT32 pic_start_g0            : 1;   //     0
	UINT32 pic_start_g1            : 1;   //     1
	UINT32 pic_start_g2            : 1;   //     2
} L9A0_DEC_PIC_START_T;

typedef struct { // 0x2008
	UINT32 o_c_fmt                 : 3;   //  2: 0
	UINT32                         : 1;   //     3
	UINT32 i_c_fmt                 : 3;   //  6: 4
	UINT32                         : 1;   //     7
	UINT32 dec3d_mux_sel           : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 prew_mux_sel            : 1;   //    12
	UINT32 d3_lr_sel               : 1;   //    13
	UINT32                         : 2;   // 15:14
	UINT32 cvi_mux_sel             : 2;   // 17:16
	UINT32                         : 2;   // 19:18
	UINT32 nline_inc               : 1;   //    20
	UINT32                         : 2;   // 22:21
	UINT32 wr_disalbe              : 1;   //    23
	UINT32 fieldid                 : 1;   //    24
	UINT32                         : 6;   // 30:25
	UINT32 pr_sq                   : 1;   //    31
} L9A0_DEC_SMUX_CTRL_T;

typedef struct { // 0x200c
	UINT32 hsize                   : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 vsize                   : 13;  // 28:16
} L9A0_DEC_SMUX_SIZE_T;

typedef struct { // 0x2010
	UINT32 mvi_vsize               : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 mvi_vblank              : 12;  // 27:16
} L9A0_DEC_MVI_V_INFO_T;

typedef struct { // 0x2014
	UINT32 mvi_hsize               : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 mvi_hblank              : 12;  // 27:16
} L9A0_DEC_MVI_H_INFO_T;

typedef struct { // 0x2018
	UINT32 mvi_i_c_fmt             : 3;   //  2: 0
	UINT32                         : 1;   //     3
	UINT32 mvi_field               : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 mvi_pr_sq               : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 mvi_cvi_stride          : 1;   //    12
} L9A0_DEC_MVI_CTRL_T;

typedef struct { // 0x201c
	UINT32 m_trans_mask_en         : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 m_cvi_select            : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 m_mvi_select            : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 m_mvi_cvi_select        : 1;   //    12
} L9A0_DEC_MSRC_SYNC_MUX_CTRL_T;

typedef struct { // 0x2020
	UINT32 msrc_sync_dly           : 28;  // 27: 0
} L9A0_DEC_MSRC_SYNC_DLY_T;

typedef struct { // 0x2024
	UINT32 mem0_sync_period        : 28;  // 27: 0
} L9A0_DEC_MEM0_SYNC_PERIOD_T;

typedef struct { // 0x2028
	UINT32 mem1_sync_period        : 28;  // 27: 0
} L9A0_DEC_MEM1_SYNC_PERIOD_T;

typedef struct { // 0x202c
	UINT32 sub_o_c_fmt             : 3;   //  2: 0
	UINT32                         : 1;   //     3
	UINT32 sub_i_c_fmt             : 3;   //  6: 4
	UINT32                         : 1;   //     7
	UINT32 sub_src_mux_sel         : 2;   //  9: 8
} L9A0_DEC_SSMUX_CTRL_T;

typedef struct { // 0x2030
	UINT32 s_trans_mask_en         : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 s_cvi_select            : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 s_mvi_select            : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 s_mvi_cvi_select        : 1;   //    12
	UINT32                         : 11;  // 23:13
	UINT32 s_disp_select           : 1;   //    24
} L9A0_DEC_SSRC_SYNC_MUX_CTRL_T;

typedef struct { // 0x2034
	UINT32 ssrc_sync_dly           : 28;  // 27: 0
} L9A0_DEC_SSRC_SYNC_DLY_T;

typedef struct { // 0x2038
	UINT32 load_md_csc_coef        : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 md_csc_en               : 1;   //     4
} L9A0_DEC_MD_CSC_CTRL_T;

typedef struct { // 0x203c
	UINT32 md_csc_coef1            : 15;  // 14: 0
	UINT32                         : 1;   //    15
	UINT32 md_csc_coef0            : 15;  // 30:16
} L9A0_DEC_MD_CSC_COEF0_T;

typedef struct { // 0x2040
	UINT32 md_csc_coef3            : 15;  // 14: 0
	UINT32                         : 1;   //    15
	UINT32 md_csc_coef2            : 15;  // 30:16
} L9A0_DEC_MD_CSC_COEF1_T;

typedef struct { // 0x2044
	UINT32 md_csc_coef5            : 15;  // 14: 0
	UINT32                         : 1;   //    15
	UINT32 md_csc_coef4            : 15;  // 30:16
} L9A0_DEC_MD_CSC_COEF2_T;

typedef struct { // 0x2048
	UINT32 md_csc_coef7            : 15;  // 14: 0
	UINT32                         : 1;   //    15
	UINT32 md_csc_coef6            : 15;  // 30:16
} L9A0_DEC_MD_CSC_COEF3_T;

typedef struct { // 0x204c
	UINT32                         : 16;  // 15: 0
	UINT32 dec_md_csc_coef4        : 15;  // 30:16
} L9A0_DEC_MD_CSC_COEF4_T;

typedef struct { // 0x2050
	UINT32 md_csc_ofst1            : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 md_csc_ofst0            : 11;  // 26:16
} L9A0_DEC_MD_CSC_OFFSET0_T;

typedef struct { // 0x2054
	UINT32 md_csc_ofst3            : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 md_csc_ofst2            : 11;  // 26:16
} L9A0_DEC_MD_CSC_OFFSET1_T;

typedef struct { // 0x2058
	UINT32 md_csc_ofst5            : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 md_csc_ofst4            : 11;  // 26:16
} L9A0_DEC_MD_CSC_OFFSET2_T;

typedef struct { // 0x205c
	UINT32 smux_ro_lcnt            : 12;  // 11: 0
} L9A0_DEC_SMUX_RO_LCNT_T;

typedef struct { // 0x2060
	UINT32 ask_cmd_dly_cnt         : 8;   //  7: 0
	UINT32                         : 8;   // 15: 8
	UINT32 ask_to_cnt              : 10;  // 25:16
} L9A0_DEC_GMAU_CTRL_T;

typedef struct { // 0x2064
	UINT32 ipc_en                  : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 tnr_en                  : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 pe0_en                  : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 prew_en                 : 1;   //    12
	UINT32                         : 3;   // 15:13
	UINT32 smux_en                 : 1;   //    16
	UINT32                         : 3;   // 19:17
	UINT32 mvi_en                  : 1;   //    20
	UINT32                         : 3;   // 23:21
	UINT32 ss_en                   : 1;   //    24
	UINT32                         : 3;   // 27:25
	UINT32 ssm_en                  : 1;   //    28
} L9A0_DEC_PIC_END_EN_T;

typedef struct { // 0x2068
	UINT32 pic_init_g0_timer       : 28;  // 27: 0
} L9A0_DEC_PIC_INIT_G0_TIMER_T;

typedef struct { // 0x206c
	UINT32 pic_init_g1_timer       : 28;  // 27: 0
} L9A0_DEC_PIC_INIT_G1_TIMER_T;

typedef struct { // 0x2070
	UINT32 pic_init_g2_timer       : 28;  // 27: 0
} L9A0_DEC_PIC_INIT_G2_TIMER_T;

typedef struct { // 0x2074
	UINT32 pic_end_g0              : 5;   //  4: 0
	UINT32 pic_end_g1              : 7;   // 11: 5
	UINT32 pic_end_g2              : 3;   // 14:12
} L9A0_DEC_PIC_END_INFO_T;

typedef struct { // 0x2078
	UINT32 pic_end_g0              : 1;   //     0
	UINT32 pic_end_g1              : 1;   //     1
	UINT32 pic_end_g2              : 1;   //     2
	UINT32 pe0_intr                : 1;   //     3
	UINT32 smux_ow_intr            : 1;   //     4
	UINT32                         : 11;  // 15: 5
	UINT32 ssrc_intr               : 1;   //    16
	UINT32                         : 6;   // 22:17
	UINT32 msrc_intr               : 1;   //    23
} L9A0_DEC_INTR_REG_T;

typedef struct { // 0x207c
	UINT32 dec_intr_mask_f         : 32;   // 31: 0
} L9A0_DEC_INTR_MASK_T;

typedef struct { // 0x2080
	UINT32 dec_intr_mux_f          : 32;   // 31: 0
} L9A0_DEC_INTR_MUX_T;

typedef struct { // 0x2084
	UINT32 dec_msrc_intr_time_stp_f: 32;   // 31: 0
} L9A0_DEC_MSRC_INTR_TIME_STP_T;

typedef struct { // 0x2088
	UINT32 dec_ssrc_intr_time_stp_f: 32;   // 31: 0
} L9A0_DEC_SSRC_INTR_TIME_STP_T;

typedef struct { // 0x208c
	UINT32                         : 3;   //  2: 0
	UINT32 dec_addr_sav_bus        : 7;   //  9: 3
	UINT32                         : 6;   // 15:10
	UINT32 dec_addr_default_bus    : 2;   // 17:16
	UINT32                         : 6;   // 23:18
	UINT32 dec_addr_de_bus         : 6;   // 29:24
} L9A0_DEC_ADDR_SW_DE_SAV_T;

typedef struct { // 0x2090
	UINT32                         : 3;   //  2: 0
	UINT32 dec_addr_gpu_bus        : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 dec_addr_gpu_logic      : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 dec_addr_cpu_h_bus      : 4;   // 27:24
} L9A0_DEC_ADDR_SW_CPU_GPU_T;

typedef struct { // 0x2094
	UINT32                         : 3;   //  2: 0
	UINT32 dec_addr_shadow_bus     : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 dec_addr_shadow_logic   : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 dec_addr_cpu_l_bus      : 6;   // 29:24
} L9A0_DEC_ADDR_SW_CPU_SHADOW_T;

typedef struct { // 0x3000
	UINT32 pic_init_g0             : 1;   //     0
	UINT32 pic_init_g1             : 1;   //     1
	UINT32 pic_inti_g2             : 1;   //     2
	UINT32 pic_init_g3             : 1;   //     3
	UINT32                         : 23;  // 26: 4
	UINT32 osd_auto_init           : 1;   //    27
	UINT32                         : 3;   // 30:28
	UINT32 atop_auto_init          : 1;   //    31
} L9A0_DED_PIC_INIT_T;

typedef struct { // 0x3004
	UINT32 pic_start_g0            : 1;   //     0
	UINT32 pic_start_g1            : 1;   //     1
	UINT32 pic_start_g2            : 1;   //     2
	UINT32 pic_start_g3            : 1;   //     3
} L9A0_DED_PIC_START_T;

typedef struct { // 0x3008
	UINT32 venc_vsync              : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 venc_sel                : 1;   //     4
} L9A0_DED_DE_VENC_IF_T;

typedef struct { // 0x300c
	UINT32 t3_mux_sel              : 2;   //  1: 0
	UINT32                         : 2;   //  3: 2
	UINT32 fb_mux_sel              : 1;   //     4
} L9A0_DED_DPATH_CTRL_T;

typedef struct { // 0x3010
	UINT32 vertical_back_period    : 8;   //  7: 0
	UINT32 vertical_sync_period    : 8;   // 15: 8
	UINT32 vertical_front_period   : 8;   // 23:16
	UINT32 vsync_polarity          : 1;   //    24
} L9A0_DED_CVE_PARAM0_T;

typedef struct { // 0x3014
	UINT32 horizontal_back_period  : 8;   //  7: 0
	UINT32 horizontal_sync_period  : 8;   // 15: 8
	UINT32 horizontal_front_period : 8;   // 23:16
	UINT32 hsync_polarity          : 1;   //    24
} L9A0_DED_CVE_PARAM1_T;

typedef struct { // 0x3018
	UINT32 v_hoffset1              : 11;  // 10: 0
	UINT32 v_hoffset0              : 11;  // 21:11
	UINT32                         : 2;   // 23:22
	UINT32 field_id_polarity       : 1;   //    24
} L9A0_DED_CVE_PARAM2_T;

typedef struct { // 0x301c
	UINT32 cve_sync_ha             : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 cve_sync_va             : 11;  // 26:16
} L9A0_DED_CVE_PARAM3_T;

typedef struct { // 0x3020
	UINT32 cve_pulse_dly           : 28;  // 27: 0
} L9A0_DED_CVE_PULSE_DLY_T;

typedef struct { // 0x3024
	UINT32 ask_cmd_dly_cnt         : 8;   //  7: 0
	UINT32                         : 8;   // 15: 8
	UINT32 ask_to_cnt              : 10;  // 25:16
} L9A0_DED_GMAU_CTRL_T;

typedef struct { // 0x3028
	UINT32 atop_en                 : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 osd_en                  : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 ov_en                   : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 sm_en                   : 1;   //    12
} L9A0_DED_PIC_END_EN_T;

typedef struct { // 0x302c
	UINT32 pic_init_g0_timer       : 28;  // 27: 0
} L9A0_DED_PIC_INIT_G0_TIMER_T;

typedef struct { // 0x3030
	UINT32 pic_init_g1_timer       : 28;  // 27: 0
} L9A0_DED_PIC_INIT_G1_TIMER_T;

typedef struct { // 0x3034
	UINT32 pic_init_g2_timer       : 28;  // 27: 0
} L9A0_DED_PIC_INIT_G2_TIMER_T;

typedef struct { // 0x3038
	UINT32 pic_init_g3_timer       : 28;  // 27: 0
} L9A0_DED_PIC_INIT_G3_TIMER_T;

typedef struct { // 0x303c
	UINT32 pic_end_g0_info         : 3;   //  2: 0
	UINT32                         : 1;   //     3
	UINT32 pic_end_g1_info         : 3;   //  6: 4
	UINT32                         : 1;   //     7
	UINT32 pic_end_g2_info         : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 pic_end_g3_info         : 1;   //    12
} L9A0_DED_PIC_END_INFO_T;

typedef struct { // 0x3040
	UINT32 pic_end_g0              : 1;   //     0
	UINT32 pic_end_g1              : 1;   //     1
	UINT32 pic_end_g2              : 1;   //     2
	UINT32 pic_end_g3              : 1;   //     3
	UINT32 ov_underflow            : 1;   //     4
	UINT32 cve_pulse               : 1;   //     5
	UINT32 cve_va_pulse            : 1;   //     6
	UINT32 src_pulse               : 1;   //     7
} L9A0_DED_INTR_REG_T;

typedef struct { // 0x3044
	UINT32 ded_intr_mask_f         : 32;   // 31: 0
} L9A0_DED_INTR_MASK_T;

typedef struct { // 0x3048
	UINT32 ded_intr_mux_f          : 32;   // 31: 0
} L9A0_DED_INTR_MUX_T;

typedef struct { // 0x304c
	UINT32 ded_cve_intr_time_stp_f : 32;   // 31: 0
} L9A0_DED_CVE_INTR_TIME_STP_T;

typedef struct { // 0x3050
	UINT32                         : 3;   //  2: 0
	UINT32 ded_addr_sav_bus        : 7;   //  9: 3
	UINT32                         : 6;   // 15:10
	UINT32 ded_addr_default_bus    : 2;   // 17:16
	UINT32                         : 6;   // 23:18
	UINT32 ded_addr_de_bus         : 6;   // 29:24
} L9A0_DED_ADDR_SW_DE_SAV_T;

typedef struct { // 0x3054
	UINT32                         : 3;   //  2: 0
	UINT32 ded_addr_gpu_bus        : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 ded_addr_gpu_logic      : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 ded_addr_cpu_h_bus      : 4;   // 27:24
} L9A0_DED_ADDR_SW_CPU_GPU_T;

typedef struct { // 0x3058
	UINT32                         : 3;   //  2: 0
	UINT32 ded_addr_shadow_bus     : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 ded_addr_shadow_logic   : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 ded_addr_cpu_l_bus      : 6;   // 29:24
} L9A0_DED_ADDR_SW_CPU_SHADOW_T;

typedef struct { // 0x4000
	UINT32 dea_dec_intr_mcu        : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 deb_dec_intr_mcu        : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 dec_dec_intr_mcu        : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 ded_dec_intr_mcu        : 1;   //    12
	UINT32                         : 3;   // 15:13
	UINT32 dee_dec_intr_mcu        : 1;   //    16
} L9A0_DEC_DE_INTR_FLAG_MCU_T;

typedef struct { // 0x4004
	UINT32 dea_dec_intr_cpu        : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 deb_dec_intr_cpu        : 1;   //     4
	UINT32                         : 3;   //  7: 5
	UINT32 dec_dec_intr_cpu        : 1;   //     8
	UINT32                         : 3;   // 11: 9
	UINT32 ded_dec_intr_cpu        : 1;   //    12
} L9A0_DEC_DE_INTR_FLAG_CPU_T;

typedef struct { // 0x4008
	UINT32 cvi_mux_sel             : 4;   //  3: 0
} L9A0_DEE_CVI_MUX_SEL_T;

typedef struct { // 0x400c
	UINT32                         : 28;  // 27: 0
	UINT32 pe0_hif_offset_en       : 1;   //    28
} L9A0_DEE_PE0_HIF_OFFSET_T;

typedef struct { // 0x4010
	UINT32                         : 28;  // 27: 0
	UINT32 sm_hif_offset_en        : 1;   //    28
} L9A0_DEE_SM_HIF_OFFSET_T;

typedef struct { // 0x4014
	UINT32                         : 28;  // 27: 0
	UINT32 pe1_hif_offset_en       : 1;   //    28
} L9A0_DEE_PE1_HIF_OFFSET_T;

typedef struct { // 0x4018
	UINT32                         : 3;   //  2: 0
	UINT32 cvd_addr_sav_bus        : 7;   //  9: 3
	UINT32                         : 6;   // 15:10
	UINT32 mcu_addr_default_bus    : 2;   // 17:16
	UINT32                         : 6;   // 23:18
	UINT32 cvd_addr_de_bus         : 6;   // 29:24
} L9A0_DEE_CVD_ADDR_SW_DE_SAV_T;

typedef struct { // 0x401c
	UINT32                         : 3;   //  2: 0
	UINT32 cvd_addr_gpu_bus        : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 cvd_addr_gpu_logic      : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 cvd_addr_cpu_h_bus      : 4;   // 27:24
} L9A0_DEE_CVD_ADDR_SW_CPU_GPU_T;

typedef struct { // 0x4020
	UINT32                         : 3;   //  2: 0
	UINT32 cvd_addr_shadow_bus     : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 cvd_addr_shadow_logic   : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 cvd_addr_cpu_l_bus      : 6;   // 29:24
} L9A0_DEE_CVD_ADDR_SW_CPU_SHADOW_T;

typedef struct { // 0x4024
	UINT32                         : 3;   //  2: 0
	UINT32 mcu_addr_sav_bus        : 7;   //  9: 3
	UINT32                         : 6;   // 15:10
	UINT32 mcu_addr_default_bus    : 2;   // 17:16
	UINT32                         : 6;   // 23:18
	UINT32 mcu_addr_de_bus         : 6;   // 29:24
} L9A0_DEE_MCU_ADDR_SW_DE_SAV_T;

typedef struct { // 0x4028
	UINT32                         : 3;   //  2: 0
	UINT32 mcu_addr_gpu_bus        : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 mcu_addr_gpu_logic      : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 mcu_addr_cpu_h_bus      : 4;   // 27:24
} L9A0_DEE_MCU_ADDR_SW_CPU_GPU_T;

typedef struct { // 0x402c
	UINT32                         : 3;   //  2: 0
	UINT32 mcu_addr_shadow_bus     : 7;   //  9: 3
	UINT32                         : 5;   // 14:10
	UINT32 mcu_addr_shadow_logic   : 5;   // 19:15
	UINT32                         : 4;   // 23:20
	UINT32 mcu_addr_cpu_l_bus      : 6;   // 29:24
} L9A0_DEE_MCU_ADDR_SW_CPU_SHADOW_T;

typedef struct { // 0x4030
	UINT32                         : 12;  // 11: 0
	UINT32 mcu_win_lower           : 4;   // 15:12
	UINT32                         : 12;  // 27:16
	UINT32 mcu_win_upper           : 4;   // 31:28
} L9A0_DEE_MCU_ADDR_WINDOW_T;

typedef struct { // 0x4034
	UINT32 dee_src_cvd             : 1;   //     0
} L9A0_DEE_INTR_REG_T;

typedef struct { // 0x4038
	UINT32 dee_cvd_intr_mask       : 1;   //     0
} L9A0_DEE_INTR_MASK_T;

typedef struct {
	L9A0_DEA_CHA_INFO_T                 dea_cha_info;                        // 0x0000
	L9A0_DEA_CHB_INFO_T                 dea_chb_info;                        // 0x0004
	L9A0_DEA_PIC_INIT_T                 dea_pic_init;                        // 0x0008
	L9A0_DEA_PIC_START_T                dea_pic_start;                       // 0x000c
	L9A0_DEA_SMUX_CTRL_T                dea_smux_ctrl;                       // 0x0010
	L9A0_DEA_SMUX_SIZE_T                dea_smux_size;                       // 0x0014
	L9A0_DEA_MVI_V_INFO_T               dea_mvi_v_info;                      // 0x0018
	L9A0_DEA_MVI_H_INFO_T               dea_mvi_h_info;                      // 0x001c
	L9A0_DEA_MVI_CTRL_T                 dea_mvi_ctrl;                        // 0x0020
	L9A0_DEA_MSRC_SYNC_MUX_CTRL_T       dea_msrc_sync_mux_ctrl;              // 0x0024
	L9A0_DEA_MSRC_SYNC_DLY_T            dea_msrc_sync_dly;                   // 0x0028
	L9A0_DEA_MEM_SYNC_PERIOD_T          dea_mem_sync_period;                 // 0x002c
	L9A0_DEA_DCO_MFC_T                  dea_dco_mfc;                         // 0x0030
	L9A0_DEA_DCO_DFC_T                  dea_dco_dfc;                         // 0x0034
	L9A0_DEA_DCO_DFLC_T                 dea_dco_dflc;                        // 0x0038
	L9A0_DEA_DCO_FCW_T                  dea_dco_fcw;                         // 0x003c
	L9A0_DEA_SMUX_RO_LCNT_T             dea_smux_ro_lcnt;                    // 0x0040
	L9A0_DEA_GMAU_CTRL_T                dea_gmau_ctrl;                       // 0x0044
	L9A0_DEA_PIC_END_EN_T               dea_pic_end_en;                      // 0x0048
	L9A0_DEA_PIC_INIT_G0_TIMER_T        dea_pic_init_g0_timer;               // 0x004c
	L9A0_DEA_PIC_INIT_G1_TIMER_T        dea_pic_init_g1_timer;               // 0x0050
	L9A0_DEA_PIC_END_INFO_T             dea_pic_end_info;                    // 0x0054
	L9A0_DEA_INTR_REG_T                 dea_intr_reg;                        // 0x0058
	L9A0_DEA_INTR_MASK_T                dea_intr_mask;                       // 0x005c
	L9A0_DEA_INTR_MUX_T                 dea_intr_mux;                        // 0x0060
	L9A0_DEA_SRC_INTR_TIME_STP_T        dea_src_intr_time_stp;               // 0x0064
	L9A0_DE_GPIO_MUX_T                  de_gpio_mux;                         // 0x0068
	L9A0_DEA_ADDR_SW_DE_SAV_T           dea_addr_sw_de_sav;                  // 0x006c
	L9A0_DEA_ADDR_SW_CPU_GPU_T          dea_addr_sw_cpu_gpu;                 // 0x0070
	L9A0_DEA_ADDR_SW_CPU_SHADOW_T       dea_addr_sw_cpu_shadow;              // 0x0074
	L9A0_DEA_GMAU_FLUSH_T               dea_gmau_flush;                      // 0x0078
	L9A0_DE_VERSION_T                   de_version;                          // 0x007c
} DE_DEA_REG_L9A0_T;

typedef struct {
	L9A0_DEB_PIC_INIT_T                 deb_pic_init;                        // 0x1000
	L9A0_DEB_PIC_START_T                deb_pic_start;                       // 0x1004
	L9A0_DEB_DISP_V_PORCH_T             deb_disp_v_porch;                    // 0x1008
	L9A0_DEB_DISP_VS_VA_T               deb_disp_vs_va;                      // 0x100c
	L9A0_DEB_DISP_H_PORCH_T             deb_disp_h_porch;                    // 0x1010
	L9A0_DEB_DISP_HS_HA_T               deb_disp_hs_ha;                      // 0x1014
	L9A0_DEB_DISP_SYNC_DLY_T            deb_disp_sync_dly;                   // 0x1018
	L9A0_DEB_DISP_PULSE_DLY_T           deb_disp_pulse_dly;                  // 0x101c
	L9A0_DEB_DISP_SYNC_PARAMS_T         deb_disp_sync_params;                // 0x1020
	L9A0_DEB_PWM_R0_T                   deb_pwm_r0;                          // 0x1024
	L9A0_DEB_PWM_F0_T                   deb_pwm_f0;                          // 0x1028
	L9A0_DEB_PWM_R1_T                   deb_pwm_r1;                          // 0x102c
	L9A0_DEB_PWM_F1_T                   deb_pwm_f1;                          // 0x1030
	L9A0_DEB_PWM_R2_T                   deb_pwm_r2;                          // 0x1034
	L9A0_DEB_PWM_F2_T                   deb_pwm_f2;                          // 0x1038
	L9A0_DEB_PWM_R3_T                   deb_pwm_r3;                          // 0x103c
	L9A0_DEB_PWM_F3_T                   deb_pwm_f3;                          // 0x1040
	L9A0_DEB_PWM_R4_T                   deb_pwm_r4;                          // 0x1044
	L9A0_DEB_PWM_F4_T                   deb_pwm_f4;                          // 0x1048
	L9A0_DEB_PWM_SUB_R0_T               deb_pwm_sub_r0;                      // 0x104c
	L9A0_DEB_PWM_SUB_R1_T               deb_pwm_sub_r1;                      // 0x1050
	L9A0_DEB_PWM_SUB_R2_T               deb_pwm_sub_r2;                      // 0x1054
	L9A0_DEB_PWM_SUB_R3_T               deb_pwm_sub_r3;                      // 0x1058
	L9A0_DEB_PWM_SUB_R4_T               deb_pwm_sub_r4;                      // 0x105c
	L9A0_DEB_PWM_CTRL_T                 deb_pwm_ctrl;                        // 0x1060
	L9A0_DEB_PWM_SEL_T                  deb_pwm_sel;                         // 0x1064
	L9A0_DEB_DPATH_CTRL_T               deb_dpath_ctrl;                      // 0x1068
	L9A0_DEB_GMAU_CTRL_T                deb_gmau_ctrl;                       // 0x106c
	L9A0_DEB_PIC_END_EN_T               deb_pic_end_en;                      // 0x1070
	L9A0_DEB_PIC_INIT_G0_TIMER_T        deb_pic_init_g0_timer;               // 0x1074
	L9A0_DEB_PIC_INIT_G1_TIMER_T        deb_pic_init_g1_timer;               // 0x1078
	L9A0_DEB_PIC_END_INFO_T             deb_pic_end_info;                    // 0x107c
	L9A0_DEB_INTR_REG_T                 deb_intr_reg;                        // 0x1080
	L9A0_DEB_INTR_MASK_T                deb_intr_mask;                       // 0x1084
	L9A0_DEB_INTR_MUX_T                 deb_intr_mux;                        // 0x1088
	L9A0_DEB_DISP_INTR_TIME_STP_T       deb_disp_intr_time_stp;              // 0x108c
	L9A0_DEB_ADDR_SW_DE_SAV_T           deb_addr_sw_de_sav;                  // 0x1090
	L9A0_DEB_ADDR_SW_CPU_GPU_T          deb_addr_sw_cpu_gpu;                 // 0x1094
	L9A0_DEB_ADDR_SW_CPU_SHADOW_T       deb_addr_sw_cpu_shadow;              // 0x1098
} DE_DEB_REG_L9A0_T;

typedef struct {
	L9A0_DEC_PIC_INIT_T                 dec_pic_init;                        // 0x2000
	L9A0_DEC_PIC_START_T                dec_pic_start;                       // 0x2004
	L9A0_DEC_SMUX_CTRL_T                dec_smux_ctrl;                       // 0x2008
	L9A0_DEC_SMUX_SIZE_T                dec_smux_size;                       // 0x200c
	L9A0_DEC_MVI_V_INFO_T               dec_mvi_v_info;                      // 0x2010
	L9A0_DEC_MVI_H_INFO_T               dec_mvi_h_info;                      // 0x2014
	L9A0_DEC_MVI_CTRL_T                 dec_mvi_ctrl;                        // 0x2018
	L9A0_DEC_MSRC_SYNC_MUX_CTRL_T       dec_msrc_sync_mux_ctrl;              // 0x201c
	L9A0_DEC_MSRC_SYNC_DLY_T            dec_msrc_sync_dly;                   // 0x2020
	L9A0_DEC_MEM0_SYNC_PERIOD_T         dec_mem0_sync_period;                // 0x2024
	L9A0_DEC_MEM1_SYNC_PERIOD_T         dec_mem1_sync_period;                // 0x2028
	L9A0_DEC_SSMUX_CTRL_T               dec_ssmux_ctrl;                      // 0x202c
	L9A0_DEC_SSRC_SYNC_MUX_CTRL_T       dec_ssrc_sync_mux_ctrl;              // 0x2030
	L9A0_DEC_SSRC_SYNC_DLY_T            dec_ssrc_sync_dly;                   // 0x2034
	L9A0_DEC_MD_CSC_CTRL_T              dec_md_csc_ctrl;                     // 0x2038
	L9A0_DEC_MD_CSC_COEF0_T             dec_md_csc_coef0;                    // 0x203c
	L9A0_DEC_MD_CSC_COEF1_T             dec_md_csc_coef1;                    // 0x2040
	L9A0_DEC_MD_CSC_COEF2_T             dec_md_csc_coef2;                    // 0x2044
	L9A0_DEC_MD_CSC_COEF3_T             dec_md_csc_coef3;                    // 0x2048
	L9A0_DEC_MD_CSC_COEF4_T             dec_md_csc_coef4;                    // 0x204c
	L9A0_DEC_MD_CSC_OFFSET0_T           dec_md_csc_offset0;                  // 0x2050
	L9A0_DEC_MD_CSC_OFFSET1_T           dec_md_csc_offset1;                  // 0x2054
	L9A0_DEC_MD_CSC_OFFSET2_T           dec_md_csc_offset2;                  // 0x2058
	L9A0_DEC_SMUX_RO_LCNT_T             dec_smux_ro_lcnt;                    // 0x205c
	L9A0_DEC_GMAU_CTRL_T                dec_gmau_ctrl;                       // 0x2060
	L9A0_DEC_PIC_END_EN_T               dec_pic_end_en;                      // 0x2064
	L9A0_DEC_PIC_INIT_G0_TIMER_T        dec_pic_init_g0_timer;               // 0x2068
	L9A0_DEC_PIC_INIT_G1_TIMER_T        dec_pic_init_g1_timer;               // 0x206c
	L9A0_DEC_PIC_INIT_G2_TIMER_T        dec_pic_init_g2_timer;               // 0x2070
	L9A0_DEC_PIC_END_INFO_T             dec_pic_end_info;                    // 0x2074
	L9A0_DEC_INTR_REG_T                 dec_intr_reg;                        // 0x2078
	L9A0_DEC_INTR_MASK_T                dec_intr_mask;                       // 0x207c
	L9A0_DEC_INTR_MUX_T                 dec_intr_mux;                        // 0x2080
	L9A0_DEC_MSRC_INTR_TIME_STP_T       dec_msrc_intr_time_stp;              // 0x2084
	L9A0_DEC_SSRC_INTR_TIME_STP_T       dec_ssrc_intr_time_stp;              // 0x2088
	L9A0_DEC_ADDR_SW_DE_SAV_T           dec_addr_sw_de_sav;                  // 0x208c
	L9A0_DEC_ADDR_SW_CPU_GPU_T          dec_addr_sw_cpu_gpu;                 // 0x2090
	L9A0_DEC_ADDR_SW_CPU_SHADOW_T       dec_addr_sw_cpu_shadow;              // 0x2094
} DE_DEC_REG_L9A0_T;

typedef struct {
	L9A0_DED_PIC_INIT_T                 ded_pic_init;                        // 0x3000
	L9A0_DED_PIC_START_T                ded_pic_start;                       // 0x3004
	L9A0_DED_DE_VENC_IF_T               ded_de_venc_if;                      // 0x3008
	L9A0_DED_DPATH_CTRL_T               ded_dpath_ctrl;                      // 0x300c
	L9A0_DED_CVE_PARAM0_T               ded_cve_param0;                      // 0x3010
	L9A0_DED_CVE_PARAM1_T               ded_cve_param1;                      // 0x3014
	L9A0_DED_CVE_PARAM2_T               ded_cve_param2;                      // 0x3018
	L9A0_DED_CVE_PARAM3_T               ded_cve_param3;                      // 0x301c
	L9A0_DED_CVE_PULSE_DLY_T            ded_cve_pulse_dly;                   // 0x3020
	L9A0_DED_GMAU_CTRL_T                ded_gmau_ctrl;                       // 0x3024
	L9A0_DED_PIC_END_EN_T               ded_pic_end_en;                      // 0x3028
	L9A0_DED_PIC_INIT_G0_TIMER_T        ded_pic_init_g0_timer;               // 0x302c
	L9A0_DED_PIC_INIT_G1_TIMER_T        ded_pic_init_g1_timer;               // 0x3030
	L9A0_DED_PIC_INIT_G2_TIMER_T        ded_pic_init_g2_timer;               // 0x3034
	L9A0_DED_PIC_INIT_G3_TIMER_T        ded_pic_init_g3_timer;               // 0x3038
	L9A0_DED_PIC_END_INFO_T             ded_pic_end_info;                    // 0x303c
	L9A0_DED_INTR_REG_T                 ded_intr_reg;                        // 0x3040
	L9A0_DED_INTR_MASK_T                ded_intr_mask;                       // 0x3044
	L9A0_DED_INTR_MUX_T                 ded_intr_mux;                        // 0x3048
	L9A0_DED_CVE_INTR_TIME_STP_T        ded_cve_intr_time_stp;               // 0x304c
	L9A0_DED_ADDR_SW_DE_SAV_T           ded_addr_sw_de_sav;                  // 0x3050
	L9A0_DED_ADDR_SW_CPU_GPU_T          ded_addr_sw_cpu_gpu;                 // 0x3054
	L9A0_DED_ADDR_SW_CPU_SHADOW_T       ded_addr_sw_cpu_shadow;              // 0x3058
} DE_DED_REG_L9A0_T;

typedef struct {
	L9A0_DEC_DE_INTR_FLAG_MCU_T         dec_de_intr_flag_mcu;                // 0x4000
	L9A0_DEC_DE_INTR_FLAG_CPU_T         dec_de_intr_flag_cpu;                // 0x4004
	L9A0_DEE_CVI_MUX_SEL_T              dee_cvi_mux_sel;                     // 0x4008
	L9A0_DEE_PE0_HIF_OFFSET_T           dee_pe0_hif_offset;                  // 0x400c
	L9A0_DEE_SM_HIF_OFFSET_T            dee_sm_hif_offset;                   // 0x4010
	L9A0_DEE_PE1_HIF_OFFSET_T           dee_pe1_hif_offset;                  // 0x4014
	L9A0_DEE_CVD_ADDR_SW_DE_SAV_T       dee_cvd_addr_sw_de_sav;              // 0x4018
	L9A0_DEE_CVD_ADDR_SW_CPU_GPU_T      dee_cvd_addr_sw_cpu_gpu;             // 0x401c
	L9A0_DEE_CVD_ADDR_SW_CPU_SHADOW_T   dee_cvd_addr_sw_cpu_shadow;          // 0x4020
	L9A0_DEE_MCU_ADDR_SW_DE_SAV_T       dee_mcu_addr_sw_de_sav;              // 0x4024
	L9A0_DEE_MCU_ADDR_SW_CPU_GPU_T      dee_mcu_addr_sw_cpu_gpu;             // 0x4028
	L9A0_DEE_MCU_ADDR_SW_CPU_SHADOW_T   dee_mcu_addr_sw_cpu_shadow;          // 0x402c
	L9A0_DEE_MCU_ADDR_WINDOW_T          dee_mcu_addr_window;                 // 0x4030
	L9A0_DEE_INTR_REG_T                 dee_intr_reg;                        // 0x4034
	L9A0_DEE_INTR_MASK_T                dee_intr_mask;                       // 0x4038
} DE_DEE_REG_L9A0_T;

#endif
