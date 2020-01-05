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

#ifndef _REG_OIF_L9A0_h
#define _REG_OIF_L9A0_h

typedef struct { // 0x3d00
	UINT32 de1_out_sel                 : 1;   //     0
	UINT32 de2_out_sel                 : 1;   //     1
} L9A0_OUT_VIDEO_INFO_T;

typedef struct { // 0x3d04
	UINT32 b_data_from                 : 2;   //  1: 0
	UINT32 g_data_from                 : 2;   //  3: 2
	UINT32 r_data_from                 : 2;   //  5: 4
} L9A0_DATA_COLOR_FROM_T;

typedef struct { // 0x3d08
	UINT32 data_color_b                : 10;  //  9: 0
	UINT32 data_color_g                : 10;  // 19:10
	UINT32 data_color_r                : 10;  // 29:20
} L9A0_DATA_COLOR_T;

typedef struct { // 0x3d0c
	UINT32 sync_color_b                : 10;  //  9: 0
	UINT32 sync_color_g                : 10;  // 19:10
	UINT32 sync_color_r                : 10;  // 29:20
} L9A0_SYNC_COLOR_T;

typedef struct { // 0x3d10
	UINT32 b_delay_l                   : 3;   //  2: 0
	UINT32 g_delay_l                   : 3;   //  5: 3
	UINT32 r_delay_l                   : 3;   //  8: 6
	UINT32 de_delay_l                  : 4;   // 12: 9
	UINT32                             : 3;   // 15:13
	UINT32 b_delay_r                   : 3;   // 18:16
	UINT32 g_delay_r                   : 3;   // 21:19
	UINT32 r_delay_r                   : 3;   // 24:22
	UINT32 de_delay_r                  : 4;   // 28:25
} L9A0_DELAY_DATA_T;

typedef struct { // 0x3d14
	UINT32 de_pol                      : 1;   //     0
	UINT32 de_disable                  : 1;   //     1
	UINT32 hsync_pol                   : 1;   //     2
	UINT32 hsync_disable               : 1;   //     3
	UINT32 vsync_pol                   : 1;   //     4
	UINT32 vsync_disable               : 1;   //     5
	UINT32 alpha_sel_76                : 2;   //  7: 6
	UINT32 alpha_sel_54                : 2;   //  9: 8
	UINT32 alpha_sel_32                : 2;   // 11:10
	UINT32 alpha_sel_10                : 2;   // 13:12
} L9A0_SYNC_DE_CONTROL_T;

typedef struct { // 0x3d20
	UINT32 lvds_empty_data_ch1         : 2;   //  1: 0
	UINT32 lvds_empty_data_ch2         : 2;   //  3: 2
	UINT32 lvds_8bit_mode              : 1;   //     4
	UINT32 lvds_lsb_first              : 1;   //     5
	UINT32 lvds_sync_order             : 3;   //  8: 6
	UINT32 lvds_ch1_from               : 2;   // 10: 9
	UINT32 lvds_ch2_from               : 2;   // 12:11
	UINT32 dual_out_mode               : 1;   //    13
	UINT32 even_pix_sel                : 1;   //    14
	UINT32 lvds_d_lane_empty_data_ch1  : 3;   // 17:15
	UINT32 lvds_e_lane_empty_data_ch1  : 3;   // 20:18
	UINT32 lvds_d_lane_empty_data_ch2  : 3;   // 23:21
	UINT32 lvds_e_lane_empty_data_ch2  : 3;   // 26:24
} L9A0_LVDS_IF_CONTROL_T;

typedef struct { // 0x3d24
	UINT32 lvds_a_lane_sel_ch1         : 3;   //  2: 0
	UINT32 lvds_b_lane_sel_ch1         : 3;   //  5: 3
	UINT32 lvds_c_lane_sel_ch1         : 3;   //  8: 6
	UINT32 lvds_d_lane_sel_ch1         : 3;   // 11: 9
	UINT32 lvds_e_lane_sel_ch1         : 3;   // 14:12
	UINT32                             : 1;   //    15
	UINT32 lvds_a_lane_sel_ch2         : 3;   // 18:16
	UINT32 lvds_b_lane_sel_ch2         : 3;   // 21:19
	UINT32 lvds_c_lane_sel_ch2         : 3;   // 24:22
	UINT32 lvds_d_lane_sel_ch2         : 3;   // 27:25
	UINT32 lvds_e_lane_sel_ch2         : 3;   // 30:28
} L9A0_LVDS_PORT_SWAP_T;

typedef struct { // 0x3d38
	UINT32                             : 2;   //  1: 0
	UINT32 de1_hsync_en                : 1;   //     2
	UINT32 de1_vsyn_en                 : 1;   //     3
	UINT32                             : 2;   //  5: 4
	UINT32 de2_hsync_en                : 1;   //     6
	UINT32 de2_vsync_en                : 1;   //     7
} L9A0_LVDS_FORCE_DATA_EN_T;

typedef struct { // 0x3d3c
	UINT32 de1_empty_data0             : 1;   //     0
	UINT32 de1_empty_data1             : 1;   //     1
	UINT32 de1_hsync                   : 1;   //     2
	UINT32 de1_vsyn                    : 1;   //     3
	UINT32 de2_empty_data0             : 1;   //     4
	UINT32 de2_empty_data1             : 1;   //     5
	UINT32 de2_hsync                   : 1;   //     6
	UINT32 de2_vsync                   : 1;   //     7
} L9A0_LVDS_FORCE_DATA_T;

typedef struct {
	L9A0_OUT_VIDEO_INFO_T       out_video_info;              // 0x3d00
	L9A0_DATA_COLOR_FROM_T      data_color_from;             // 0x3d04
	L9A0_DATA_COLOR_T           data_color;                  // 0x3d08
	L9A0_SYNC_COLOR_T           sync_color;                  // 0x3d0c
	L9A0_DELAY_DATA_T           delay_data;                  // 0x3d10
	L9A0_SYNC_DE_CONTROL_T      sync_de_control;             // 0x3d14
	UINT32                      reserved0[2];                // 0x3d18~0x3d1c
	L9A0_LVDS_IF_CONTROL_T      lvds_if_control;             // 0x3d20
	L9A0_LVDS_PORT_SWAP_T       lvds_port_swap;              // 0x3d24
	UINT32                      reserved1[4];                // 0x3d28~0x3d34
	L9A0_LVDS_FORCE_DATA_EN_T   lvds_force_data_en;          // 0x3d38
	L9A0_LVDS_FORCE_DATA_T      lvds_force_data;             // 0x3d3c
} DE_OIF_REG_L9A0_T;

#endif
