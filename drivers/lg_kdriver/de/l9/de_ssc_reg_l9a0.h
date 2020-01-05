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

#ifndef _REG_SSC_L9A0_h
#define _REG_SSC_L9A0_h

typedef struct { // 0x2100
	UINT32 bnd_pel_filtering_scheme    : 1;   //     0
	UINT32 fir_config                  : 1;   //     1
	UINT32 filter_type_sel             : 1;   //     2
	UINT32 size_info_manual_load       : 1;   //     3
	UINT32                             : 1;   //     4
	UINT32 ddr_update_endian_change    : 1;   //     5
	UINT32 stride_cvi_mode             : 1;   //     6
	UINT32 dvr_write_mode              : 1;   //     7
	UINT32 source_sel                  : 2;   //  9: 8
} L9A0_SSC_CTRL_T;

typedef struct { // 0x2104
	UINT32 interlace_mode              : 1;   //     0
	UINT32 curr_field                  : 1;   //     1
	UINT32 mpeg_stream                 : 1;   //     2
} L9A0_SSC_FIELD_T;

typedef struct { // 0x2108
	UINT32 y_init_pos_h                : 6;   //  5: 0
} L9A0_SSC_Y_INIT_POS_H_T;

typedef struct { // 0x210c
	UINT32 y_init_pos_v                : 6;   //  5: 0
} L9A0_SSC_Y_INIT_POS_V_T;

typedef struct { // 0x2110
	UINT32 c_init_pos_h                : 6;   //  5: 0
} L9A0_SSC_C_INIT_POS_H_T;

typedef struct { // 0x2114
	UINT32 c_init_pos_v                : 6;   //  5: 0
} L9A0_SSC_C_INIT_POS_V_T;

typedef struct { // 0x2118
	UINT32 input_h_size                : 11;  // 10: 0
	UINT32                             : 5;   // 15:11
	UINT32 input_v_size                : 11;  // 26:16
} L9A0_SSC_SCR_SIZE_T;

typedef struct { // 0x211c
	UINT32 out_win_h_size              : 11;  // 10: 0
	UINT32                             : 5;   // 15:11
	UINT32 out_win_v_size              : 11;  // 26:16
} L9A0_SSC_WIN_OUT_SIZE_T;

typedef struct { // 0x2120
	UINT32 in_win_h_offset             : 11;  // 10: 0
	UINT32                             : 5;   // 15:11
	UINT32 in_win_v_offset             : 11;  // 26:16
} L9A0_SSC_WIN_IN_OFFSET_T;

typedef struct { // 0x2124
	UINT32 in_win_h_size               : 11;  // 10: 0
	UINT32                             : 5;   // 15:11
	UINT32 in_win_v_size               : 11;  // 26:16
} L9A0_SSC_WIN_IN_SIZE_T;

typedef struct { // 0x2128
	UINT32 in_c_format                 : 3;   //  2: 0
	UINT32                             : 13;  // 15: 3
	UINT32 out_c_format                : 3;   // 18:16
} L9A0_SSC_C_FORMAT_T;

typedef struct { // 0x2130
	UINT32 h_coefficient0              : 10;  //  9: 0
	UINT32                             : 6;   // 15:10
	UINT32 h_coefficient1              : 10;  // 25:16
} L9A0_SSC_H_FIR_COEF_DATA0_T;

typedef struct { // 0x2134
	UINT32 h_coefficient2              : 10;  //  9: 0
	UINT32                             : 6;   // 15:10
	UINT32 h_coefficient3              : 10;  // 25:16
} L9A0_SSC_H_FIR_COEF_DATA1_T;

typedef struct { // 0x2138
	UINT32 h_coefficient4              : 10;  //  9: 0
	UINT32                             : 6;   // 15:10
	UINT32 h_coefficient5              : 10;  // 25:16
} L9A0_SSC_H_FIR_COEF_DATA2_T;

typedef struct { // 0x213c
	UINT32 h_coefficient6              : 10;  //  9: 0
	UINT32                             : 6;   // 15:10
	UINT32 h_coefficient7              : 10;  // 25:16
} L9A0_SSC_H_FIR_COEF_DATA3_T;

typedef struct { // 0x2140
	UINT32 addr                        : 4;   //  3: 0
	UINT32 h_v_sel                     : 1;   //     4
	UINT32                             : 3;   //  7: 5
	UINT32 update                      : 1;   //     8
	UINT32                             : 3;   // 11: 9
	UINT32 rnw                         : 1;   //    12
} L9A0_SSC_H_FIR_COEF_CTRL_T;

typedef struct { // 0x2160
	UINT32 ddr_stride                  : 11;  // 10: 0
	UINT32                             : 5;   // 15:11
	UINT32 ddr_line_cnt                : 8;   // 23:16
	UINT32                             : 7;   // 30:24
	UINT32 ddr_update_on               : 1;   //    31
} L9A0_SSC_UPDATE_FROM_DDR_T;

typedef struct { // 0x2168
	UINT32 y_status                    : 11;  // 10: 0
	UINT32                             : 5;   // 15:11
	UINT32 c_status                    : 11;  // 26:16
} L9A0_SSC_STATUS_REV_T;

typedef struct { // 0x216c
	UINT32 update_input_frm_size       : 1;   //     0
	UINT32                             : 3;   //  3: 1
	UINT32 update_wout_size            : 1;   //     4
	UINT32                             : 3;   //  7: 5
	UINT32 update_win_offset           : 1;   //     8
	UINT32                             : 3;   // 11: 9
	UINT32 update_win_size             : 1;   //    12
} L9A0_SSC_MANUAL_LOAD_T;

typedef struct { // 0x2170
	UINT32 h_offset                    : 8;   //  7: 0
	UINT32                             : 8;   // 15: 8
	UINT32 v_offset                    : 11;  // 26:16
} L9A0_SSC_CANVAS_MODE_T;

typedef struct {
	L9A0_SSC_CTRL_T                 ssc_ctrl;                        // 0x2100
	L9A0_SSC_FIELD_T                ssc_field;                       // 0x2104
	L9A0_SSC_Y_INIT_POS_H_T         ssc_y_init_pos_h;                // 0x2108
	L9A0_SSC_Y_INIT_POS_V_T         ssc_y_init_pos_v;                // 0x210c
	L9A0_SSC_C_INIT_POS_H_T         ssc_c_init_pos_h;                // 0x2110
	L9A0_SSC_C_INIT_POS_V_T         ssc_c_init_pos_v;                // 0x2114
	L9A0_SSC_SCR_SIZE_T             ssc_scr_size;                    // 0x2118
	L9A0_SSC_WIN_OUT_SIZE_T         ssc_win_out_size;                // 0x211c
	L9A0_SSC_WIN_IN_OFFSET_T        ssc_win_in_offset;               // 0x2120
	L9A0_SSC_WIN_IN_SIZE_T          ssc_win_in_size;                 // 0x2124
	L9A0_SSC_C_FORMAT_T             ssc_c_format;                    // 0x2128
	UINT32                          reserved0;                       // 0x212c
	L9A0_SSC_H_FIR_COEF_DATA0_T     ssc_h_fir_coef_data0;            // 0x2130
	L9A0_SSC_H_FIR_COEF_DATA1_T     ssc_h_fir_coef_data1;            // 0x2134
	L9A0_SSC_H_FIR_COEF_DATA2_T     ssc_h_fir_coef_data2;            // 0x2138
	L9A0_SSC_H_FIR_COEF_DATA3_T     ssc_h_fir_coef_data3;            // 0x213c
	L9A0_SSC_H_FIR_COEF_CTRL_T      ssc_h_fir_coef_ctrl;             // 0x2140
	UINT32                          reserved1[7];                    // 0x2144~0x215c
	L9A0_SSC_UPDATE_FROM_DDR_T      ssc_update_from_ddr;             // 0x2160
	UINT32                          reserved2;                       // 0x2164
	L9A0_SSC_STATUS_REV_T           ssc_status_rev;                  // 0x2168
	L9A0_SSC_MANUAL_LOAD_T          ssc_manual_load;                 // 0x216c
	L9A0_SSC_CANVAS_MODE_T          ssc_canvas_mode;                 // 0x2170
} DE_SSC_REG_L9A0_T;

#endif
