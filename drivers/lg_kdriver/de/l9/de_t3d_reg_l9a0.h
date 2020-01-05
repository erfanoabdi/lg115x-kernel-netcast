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

#ifndef _REG_T3D_L9A0_h
#define _REG_T3D_L9A0_h

typedef struct { // 0x3920
	UINT32 t3d_3dconv_r_en         : 1;   //     0
	UINT32 fpacking_r_en           : 1;   //     1
	UINT32                         : 2;   //  3: 2
	UINT32 t3d_3dconv_l_en         : 1;   //     4
	UINT32 fpacking_l_en           : 1;   //     5
} L9A0_D3_PP_3DCONV_CTRL_00_T;

typedef struct { // 0x3924
	UINT32 offset_r                : 7;   //  6: 0
	UINT32                         : 9;   // 15: 7
	UINT32 offset_l                : 7;   // 22:16
} L9A0_D3_PP_3DCONV_CTRL_01_T;

typedef struct { // 0x3928
	UINT32 bg_color_grey           : 8;   //  7: 0
} L9A0_D3_PP_3DCONV_CTRL_02_T;

typedef struct { // 0x3940
	UINT32 pxl_rep_xpos            : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 pxl_rep_ypos            : 12;  // 27:16
	UINT32 pxl_rep_in              : 1;   //    28
	UINT32 pxl_rep_out             : 1;   //    29
} L9A0_D3_PP_PCAP_L_CTRL_00_T;

typedef struct { // 0x3944
	UINT32 pxl_rep_width           : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 pxl_rep_height          : 12;  // 27:16
} L9A0_D3_PP_PCAP_L_CTRL_01_T;

typedef struct { // 0x3948
	UINT32 pxl_rep_value_g         : 10;  //  9: 0
	UINT32 pxl_rep_value_b         : 10;  // 19:10
	UINT32 pxl_rep_value_r         : 10;  // 29:20
	UINT32 pcap_mode               : 1;   //    30
} L9A0_D3_PP_PCAP_L_CTRL_02_T;

typedef struct { // 0x394c
	UINT32 pxl_rep_value_g         : 10;  //  9: 0
	UINT32 pxl_rep_value_b         : 10;  // 19:10
	UINT32 pxl_rep_value_r         : 10;  // 29:20
} L9A0_D3_PP_PCAP_L_CTRL_03_T;

typedef struct { // 0x3950
	UINT32 capture_addr            : 8;   //  7: 0
	UINT32                         : 4;   // 11: 8
	UINT32 capture_ai              : 1;   //    12
	UINT32                         : 3;   // 15:13
	UINT32 capture_num             : 9;   // 24:16
} L9A0_D3_PP_PCAP_L_CTRL_T;

typedef struct { // 0x3954
	UINT32 lut_data_g              : 10;  //  9: 0
	UINT32 lut_data_b              : 10;  // 19:10
	UINT32 lut_data_r              : 10;  // 29:20
	UINT32 capture_stat_started    : 1;   //    30
	UINT32 capture_stat_ended      : 1;   //    31
} L9A0_D3_PP_PCAP_L_DATA_T;

typedef struct { // 0x3970
	UINT32 pxl_rep_xpos            : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 pxl_rep_ypos            : 12;  // 27:16
	UINT32 pxl_rep_in              : 1;   //    28
	UINT32 pxl_rep_out             : 1;   //    29
} L9A0_D3_PP_PCAP_R_CTRL_00_T;

typedef struct { // 0x3974
	UINT32 pxl_rep_width           : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 pxl_rep_height          : 12;  // 27:16
} L9A0_D3_PP_PCAP_R_CTRL_01_T;

typedef struct { // 0x3978
	UINT32 pxl_rep_value_g         : 10;  //  9: 0
	UINT32 pxl_rep_value_b         : 10;  // 19:10
	UINT32 pxl_rep_value_r         : 10;  // 29:20
	UINT32 pcap_mode               : 1;   //    30
} L9A0_D3_PP_PCAP_R_CTRL_02_T;

typedef struct { // 0x397c
	UINT32 pxl_rep_value_g         : 10;  //  9: 0
	UINT32 pxl_rep_value_b         : 10;  // 19:10
	UINT32 pxl_rep_value_r         : 10;  // 29:20
} L9A0_D3_PP_PCAP_R_CTRL_03_T;

typedef struct { // 0x3980
	UINT32 capture_addr            : 8;   //  7: 0
	UINT32                         : 4;   // 11: 8
	UINT32 capture_ai              : 1;   //    12
	UINT32                         : 3;   // 15:13
	UINT32 capture_num             : 9;   // 24:16
} L9A0_D3_PP_PCAP_R_CTRL_T;

typedef struct { // 0x3984
	UINT32 lut_data_g              : 10;  //  9: 0
	UINT32 lut_data_b              : 10;  // 19:10
	UINT32 lut_data_r              : 10;  // 29:20
	UINT32 capture_stat_started    : 1;   //    30
	UINT32 capture_stat_ended      : 1;   //    31
} L9A0_D3_PP_PCAP_R_DATA_T;

typedef struct { // 0x39a0
	UINT32 mux3d_en                : 1;   //     0
	UINT32                         : 3;   //  3: 1
	UINT32 bypass_r_en             : 1;   //     4
	UINT32 bypass_l_en             : 1;   //     5
	UINT32                         : 2;   //  7: 6
	UINT32 lr_outmux               : 1;   //     8
	UINT32                         : 7;   // 15: 9
	UINT32 alpha1_gain             : 8;   // 23:16
	UINT32 alpha0_gain             : 8;   // 31:24
} L9A0_D3_PP_MUX3D_CTRL_00_T;

typedef struct { // 0x39a4
	UINT32 x0                      : 12;  // 11: 0
	UINT32                         : 3;   // 14:12
	UINT32 mux_l_window_h_en       : 1;   //    15
	UINT32 y0                      : 12;  // 27:16
	UINT32                         : 3;   // 30:28
	UINT32 mux_l_window_v_en       : 1;   //    31
} L9A0_D3_PP_MUX3D_CTRL_01_T;

typedef struct { // 0x39a8
	UINT32 x1                      : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 y1                      : 11;  // 26:16
} L9A0_D3_PP_MUX3D_CTRL_02_T;

typedef struct { // 0x39ac
	UINT32 x0                      : 11;  // 10: 0
	UINT32                         : 4;   // 14:11
	UINT32 mux_r_window_h_en       : 1;   //    15
	UINT32 y0                      : 11;  // 26:16
	UINT32                         : 4;   // 30:27
	UINT32 mux_r_window_v_en       : 1;   //    31
} L9A0_D3_PP_MUX3D_CTRL_03_T;

typedef struct { // 0x39b0
	UINT32 x1                      : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 y1                      : 11;  // 26:16
} L9A0_D3_PP_MUX3D_CTRL_04_T;

typedef struct { // 0x39b4
	UINT32 bg_color_r              : 8;   //  7: 0
	UINT32 bg_color_b              : 8;   // 15: 8
	UINT32 bg_color_g              : 8;   // 23:16
} L9A0_D3_PP_MUX3D_CTRL_05_T;

typedef struct {
	L9A0_D3_PP_3DCONV_CTRL_00_T     d3_pp_3dconv_ctrl_00;            // 0x3920
	L9A0_D3_PP_3DCONV_CTRL_01_T     d3_pp_3dconv_ctrl_01;            // 0x3924
	L9A0_D3_PP_3DCONV_CTRL_02_T     d3_pp_3dconv_ctrl_02;            // 0x3928
	UINT32                          reserved0[5];                    // 0x392c~0x393c
	L9A0_D3_PP_PCAP_L_CTRL_00_T     d3_pp_pcap_l_ctrl_00;            // 0x3940
	L9A0_D3_PP_PCAP_L_CTRL_01_T     d3_pp_pcap_l_ctrl_01;            // 0x3944
	L9A0_D3_PP_PCAP_L_CTRL_02_T     d3_pp_pcap_l_ctrl_02;            // 0x3948
	L9A0_D3_PP_PCAP_L_CTRL_03_T     d3_pp_pcap_l_ctrl_03;            // 0x394c
	L9A0_D3_PP_PCAP_L_CTRL_T        d3_pp_pcap_l_ctrl;               // 0x3950
	L9A0_D3_PP_PCAP_L_DATA_T        d3_pp_pcap_l_data;               // 0x3954
	UINT32                          reserved1[6];                    // 0x3958~0x396c
	L9A0_D3_PP_PCAP_R_CTRL_00_T     d3_pp_pcap_r_ctrl_00;            // 0x3970
	L9A0_D3_PP_PCAP_R_CTRL_01_T     d3_pp_pcap_r_ctrl_01;            // 0x3974
	L9A0_D3_PP_PCAP_R_CTRL_02_T     d3_pp_pcap_r_ctrl_02;            // 0x3978
	L9A0_D3_PP_PCAP_R_CTRL_03_T     d3_pp_pcap_r_ctrl_03;            // 0x397c
	L9A0_D3_PP_PCAP_R_CTRL_T        d3_pp_pcap_r_ctrl;               // 0x3980
	L9A0_D3_PP_PCAP_R_DATA_T        d3_pp_pcap_r_data;               // 0x3984
	UINT32                          reserved2[6];                    // 0x3988~0x399c
	L9A0_D3_PP_MUX3D_CTRL_00_T      d3_pp_mux3d_ctrl_00;             // 0x39a0
	L9A0_D3_PP_MUX3D_CTRL_01_T      d3_pp_mux3d_ctrl_01;             // 0x39a4
	L9A0_D3_PP_MUX3D_CTRL_02_T      d3_pp_mux3d_ctrl_02;             // 0x39a8
	L9A0_D3_PP_MUX3D_CTRL_03_T      d3_pp_mux3d_ctrl_03;             // 0x39ac
	L9A0_D3_PP_MUX3D_CTRL_04_T      d3_pp_mux3d_ctrl_04;             // 0x39b0
	L9A0_D3_PP_MUX3D_CTRL_05_T      d3_pp_mux3d_ctrl_05;             // 0x39b4
} DE_T3D_REG_L9A0_T;

#endif
