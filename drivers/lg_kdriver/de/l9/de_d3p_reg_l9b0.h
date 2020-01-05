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

#ifndef _REG_D3P_L9B0_h
#define _REG_D3P_L9B0_h

/*-----------------------------------------------------------------------------
	0x5d20 d3_pp_3dconv_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 d3p_3dconv_r_en         : 1;   //     0
	UINT32 fpacking_r_en           : 1;   //     1
	UINT32                         : 2;   //  2: 3 reserved
	UINT32 d3p_3dconv_l_en         : 1;   //     4
	UINT32 fpacking_l_en           : 1;   //     5
} L9B0_D3_PP_3DCONV_CTRL_00_T;

/*-----------------------------------------------------------------------------
	0x5d24 d3_pp_3dconv_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 offset_r                : 7;   //  0: 6
	UINT32                         : 9;   //  7:15 reserved
	UINT32 offset_l                : 7;   // 16:22
} L9B0_D3_PP_3DCONV_CTRL_01_T;

/*-----------------------------------------------------------------------------
	0x5d28 d3_pp_3dconv_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 bg_color_grey           : 8;   //  0: 7
} L9B0_D3_PP_3DCONV_CTRL_02_T;

/*-----------------------------------------------------------------------------
	0x5d40 d3_pp_pcap_l_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_xpos            : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 pxl_rep_ypos            : 12;  // 16:27
	UINT32 pxl_rep_in              : 1;   //    28
	UINT32 pxl_rep_out             : 1;   //    29
} L9B0_D3_PP_PCAP_L_CTRL_00_T;

/*-----------------------------------------------------------------------------
	0x5d44 d3_pp_pcap_l_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_width           : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 pxl_rep_height          : 12;  // 16:27
} L9B0_D3_PP_PCAP_L_CTRL_01_T;

/*-----------------------------------------------------------------------------
	0x5d48 d3_pp_pcap_l_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_value_g         : 10;  //  0: 9
	UINT32 pxl_rep_value_b         : 10;  // 10:19
	UINT32 pxl_rep_value_r         : 10;  // 20:29
	UINT32 pcap_mode               : 1;   //    30
} L9B0_D3_PP_PCAP_L_CTRL_02_T;

/*-----------------------------------------------------------------------------
	0x5d4c d3_pp_pcap_l_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_value_g         : 10;  //  0: 9
	UINT32 pxl_rep_value_b         : 10;  // 10:19
	UINT32 pxl_rep_value_r         : 10;  // 20:29
} L9B0_D3_PP_PCAP_L_CTRL_03_T;

/*-----------------------------------------------------------------------------
	0x5d50 d3_pp_pcap_l_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 capture_addr            : 8;   //  0: 7
	UINT32                         : 4;   //  8:11 reserved
	UINT32 capture_ai              : 1;   //    12
	UINT32                         : 3;   // 13:15 reserved
	UINT32 capture_num             : 9;   // 16:24
} L9B0_D3_PP_PCAP_L_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5d54 d3_pp_pcap_l_data ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 lut_data_g              : 10;  //  0: 9
	UINT32 lut_data_b              : 10;  // 10:19
	UINT32 lut_data_r              : 10;  // 20:29
	UINT32 capture_stat_started    : 1;   //    30
	UINT32 capture_stat_ended      : 1;   //    31
} L9B0_D3_PP_PCAP_L_DATA_T;

/*-----------------------------------------------------------------------------
	0x5d58 d3_pp_pcap_l_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 col_fil_g_valid         : 1;   //     0
	UINT32 col_fil_b_valid         : 1;   //     1
	UINT32 col_fil_r_valid         : 1;   //     2
	UINT32 col_fil_g_nvalid        : 1;   //     3
	UINT32 col_fil_b_nvalid        : 1;   //     4
	UINT32 col_fil_r_nvalid        : 1;   //     5
} L9B0_D3_PP_PCAP_L_CTRL_04_T;

/*-----------------------------------------------------------------------------
	0x5d70 d3_pp_pcap_r_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_xpos            : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 pxl_rep_ypos            : 12;  // 16:27
	UINT32 pxl_rep_in              : 1;   //    28
	UINT32 pxl_rep_out             : 1;   //    29
} L9B0_D3_PP_PCAP_R_CTRL_00_T;

/*-----------------------------------------------------------------------------
	0x5d74 d3_pp_pcap_r_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_width           : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 pxl_rep_height          : 12;  // 16:27
} L9B0_D3_PP_PCAP_R_CTRL_01_T;

/*-----------------------------------------------------------------------------
	0x5d78 d3_pp_pcap_r_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_value_g         : 10;  //  0: 9
	UINT32 pxl_rep_value_b         : 10;  // 10:19
	UINT32 pxl_rep_value_r         : 10;  // 20:29
	UINT32 pcap_mode               : 1;   //    30
} L9B0_D3_PP_PCAP_R_CTRL_02_T;

/*-----------------------------------------------------------------------------
	0x5d7c d3_pp_pcap_r_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_rep_value_g         : 10;  //  0: 9
	UINT32 pxl_rep_value_b         : 10;  // 10:19
	UINT32 pxl_rep_value_r         : 10;  // 20:29
} L9B0_D3_PP_PCAP_R_CTRL_03_T;

/*-----------------------------------------------------------------------------
	0x5d80 d3_pp_pcap_r_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 capture_addr            : 8;   //  0: 7
	UINT32                         : 4;   //  8:11 reserved
	UINT32 capture_ai              : 1;   //    12
	UINT32                         : 3;   // 13:15 reserved
	UINT32 capture_num             : 9;   // 16:24
} L9B0_D3_PP_PCAP_R_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5d84 d3_pp_pcap_r_data ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 lut_data_g              : 10;  //  0: 9
	UINT32 lut_data_b              : 10;  // 10:19
	UINT32 lut_data_r              : 10;  // 20:29
	UINT32 capture_stat_started    : 1;   //    30
	UINT32 capture_stat_ended      : 1;   //    31
} L9B0_D3_PP_PCAP_R_DATA_T;

/*-----------------------------------------------------------------------------
	0x5d88 d3_pp_pcap_r_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 col_fil_g_valid         : 1;   //     0
	UINT32 col_fil_b_valid         : 1;   //     1
	UINT32 col_fil_r_valid         : 1;   //     2
	UINT32 col_fil_g_nvalid        : 1;   //     3
	UINT32 col_fil_b_nvalid        : 1;   //     4
	UINT32 col_fil_r_nvalid        : 1;   //     5
} L9B0_D3_PP_PCAP_R_CTRL_04_T;

/*-----------------------------------------------------------------------------
	0x5da0 d3_pp_mux3d_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mux3d_en                : 1;   //     0
	UINT32                         : 3;   //  1: 3 reserved
	UINT32 l_outmux                : 2;   //  4: 5
	UINT32 r_outmux                : 2;   //  6: 7
	UINT32                         : 8;   //  8:15 reserved
	UINT32 alpha1_gain             : 8;   // 16:23
	UINT32 alpha0_gain             : 8;   // 24:31
} L9B0_D3_PP_MUX3D_CTRL_00_T;

/*-----------------------------------------------------------------------------
	0x5da4 d3_pp_mux3d_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                      : 12;  //  0:11
	UINT32                         : 3;   // 12:14 reserved
	UINT32 mux_l_window_h_en       : 1;   //    15
	UINT32 y0                      : 12;  // 16:27
	UINT32                         : 3;   // 28:30 reserved
	UINT32 mux_l_window_v_en       : 1;   //    31
} L9B0_D3_PP_MUX3D_CTRL_01_T;

/*-----------------------------------------------------------------------------
	0x5da8 d3_pp_mux3d_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                      : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 y1                      : 12;  // 16:27
} L9B0_D3_PP_MUX3D_CTRL_02_T;

/*-----------------------------------------------------------------------------
	0x5dac d3_pp_mux3d_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x0                      : 12;  //  0:11
	UINT32                         : 3;   // 12:14 reserved
	UINT32 mux_r_window_h_en       : 1;   //    15
	UINT32 y0                      : 12;  // 16:27
	UINT32                         : 3;   // 28:30 reserved
	UINT32 mux_r_window_v_en       : 1;   //    31
} L9B0_D3_PP_MUX3D_CTRL_03_T;

/*-----------------------------------------------------------------------------
	0x5db0 d3_pp_mux3d_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 x1                      : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 y1                      : 12;  // 16:27
} L9B0_D3_PP_MUX3D_CTRL_04_T;

/*-----------------------------------------------------------------------------
	0x5db4 d3_pp_mux3d_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 bg_color_r              : 8;   //  0: 7
	UINT32 bg_color_b              : 8;   //  8:15
	UINT32 bg_color_g              : 8;   // 16:23
} L9B0_D3_PP_MUX3D_CTRL_05_T;

typedef struct {
	L9B0_D3_PP_3DCONV_CTRL_00_T     d3_pp_3dconv_ctrl_00;            // 0x5d20
	L9B0_D3_PP_3DCONV_CTRL_01_T     d3_pp_3dconv_ctrl_01;            // 0x5d24
	L9B0_D3_PP_3DCONV_CTRL_02_T     d3_pp_3dconv_ctrl_02;            // 0x5d28
	UINT32                          reserved0[5];                    // 0x5d2c~0x5d3c
	L9B0_D3_PP_PCAP_L_CTRL_00_T     d3_pp_pcap_l_ctrl_00;            // 0x5d40
	L9B0_D3_PP_PCAP_L_CTRL_01_T     d3_pp_pcap_l_ctrl_01;            // 0x5d44
	L9B0_D3_PP_PCAP_L_CTRL_02_T     d3_pp_pcap_l_ctrl_02;            // 0x5d48
	L9B0_D3_PP_PCAP_L_CTRL_03_T     d3_pp_pcap_l_ctrl_03;            // 0x5d4c
	L9B0_D3_PP_PCAP_L_CTRL_T        d3_pp_pcap_l_ctrl;               // 0x5d50
	L9B0_D3_PP_PCAP_L_DATA_T        d3_pp_pcap_l_data;               // 0x5d54
	L9B0_D3_PP_PCAP_L_CTRL_04_T     d3_pp_pcap_l_ctrl_04;            // 0x5d58
	UINT32                          reserved1[5];                    // 0x5d5c~0x5d6c
	L9B0_D3_PP_PCAP_R_CTRL_00_T     d3_pp_pcap_r_ctrl_00;            // 0x5d70
	L9B0_D3_PP_PCAP_R_CTRL_01_T     d3_pp_pcap_r_ctrl_01;            // 0x5d74
	L9B0_D3_PP_PCAP_R_CTRL_02_T     d3_pp_pcap_r_ctrl_02;            // 0x5d78
	L9B0_D3_PP_PCAP_R_CTRL_03_T     d3_pp_pcap_r_ctrl_03;            // 0x5d7c
	L9B0_D3_PP_PCAP_R_CTRL_T        d3_pp_pcap_r_ctrl;               // 0x5d80
	L9B0_D3_PP_PCAP_R_DATA_T        d3_pp_pcap_r_data;               // 0x5d84
	L9B0_D3_PP_PCAP_R_CTRL_04_T     d3_pp_pcap_r_ctrl_04;            // 0x5d88
	UINT32                          reserved2[5];                    // 0x5d8c~0x5d9c
	L9B0_D3_PP_MUX3D_CTRL_00_T      d3_pp_mux3d_ctrl_00;             // 0x5da0
	L9B0_D3_PP_MUX3D_CTRL_01_T      d3_pp_mux3d_ctrl_01;             // 0x5da4
	L9B0_D3_PP_MUX3D_CTRL_02_T      d3_pp_mux3d_ctrl_02;             // 0x5da8
	L9B0_D3_PP_MUX3D_CTRL_03_T      d3_pp_mux3d_ctrl_03;             // 0x5dac
	L9B0_D3_PP_MUX3D_CTRL_04_T      d3_pp_mux3d_ctrl_04;             // 0x5db0
	L9B0_D3_PP_MUX3D_CTRL_05_T      d3_pp_mux3d_ctrl_05;             // 0x5db4
} DE_D3P_REG_L9B0_T;

#endif
