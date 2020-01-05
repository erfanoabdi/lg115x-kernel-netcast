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

#ifndef _REG_MSC_L9A0_h
#define _REG_MSC_L9A0_h

typedef struct { // 0x1100
	UINT32 bnd_pel_filtering_scheme        : 1;   //     0
	UINT32 adaptive_fir_filter_en          : 1;   //     1
	UINT32 v_scaler_config                 : 1;   //     2
	UINT32                                 : 1;   //     3
	UINT32 filter_type_sel_luma            : 1;   //     4
	UINT32 filter_type_sel_chroma          : 1;   //     5
	UINT32 manual_sampling_mode            : 1;   //     6
	UINT32                                 : 1;   //     7
	UINT32 size_info_manual_load           : 1;   //     8
} L9A0_MSC_CTRL_L_T;

typedef struct { // 0x1104
	UINT32 y_init_pos_h                    : 6;   //  5: 0
} L9A0_MSC_Y_INIT_POS_H_L_T;

typedef struct { // 0x1108
	UINT32 y_init_pos_v                    : 6;   //  5: 0
} L9A0_MSC_Y_INIT_POS_V_L_T;

typedef struct { // 0x110c
	UINT32 c_init_pos_h                    : 6;   //  5: 0
} L9A0_MSC_C_INIT_POS_H_L_T;

typedef struct { // 0x1110
	UINT32 c_init_pos_v                    : 6;   //  5: 0
} L9A0_MSC_C_INIT_POS_V_L_T;

typedef struct { // 0x1114
	UINT32 reg_th                          : 2;   //  1: 0
} L9A0_MSC_ADAPTIVE_TH_L_T;

typedef struct { // 0x1118
	UINT32 input_h_size                    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 input_v_size                    : 12;  // 27:16
} L9A0_MSC_SCR_SIZE_L_T;

typedef struct { // 0x111c
	UINT32 out_win_h_size                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 out_win_v_size                  : 12;  // 27:16
} L9A0_MSC_WIN_OUT_SIZE_L_T;

typedef struct { // 0x1120
	UINT32 in_win_h_offset                 : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 in_win_v_offset                 : 12;  // 27:16
} L9A0_MSC_WIN_IN_OFFSET_L_T;

typedef struct { // 0x1124
	UINT32 in_win_h_size                   : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 in_win_v_size                   : 12;  // 27:16
} L9A0_MSC_WIN_IN_SIZE_L_T;

typedef struct { // 0x1128
	UINT32 in_c_format                     : 3;   //  2: 0
	UINT32                                 : 13;  // 15: 3
	UINT32 out_c_format                    : 3;   // 18:16
} L9A0_MSC_C_FORMAT_L_T;

typedef struct { // 0x1130
	UINT32 y_coefficient0                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient1                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA0_L_T;

typedef struct { // 0x1134
	UINT32 y_coefficient2                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient3                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA1_L_T;

typedef struct { // 0x1138
	UINT32 y_coefficient4                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient5                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA2_L_T;

typedef struct { // 0x113c
	UINT32 y_coefficient6                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient7                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA3_L_T;

typedef struct { // 0x1140
	UINT32 y_coefficient8                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient9                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA4_L_T;

typedef struct { // 0x1144
	UINT32 y_coefficient10                 : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient11                 : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA5_L_T;

typedef struct { // 0x1148
	UINT32 addr                            : 4;   //  3: 0
	UINT32 h_v_sel                         : 1;   //     4
	UINT32 hidden_configure4               : 1;   //     5
	UINT32                                 : 2;   //  7: 6
	UINT32 update                          : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 rnw                             : 1;   //    12
} L9A0_MSC_Y_FIR_COEF_CTRL_L_T;

typedef struct { // 0x1150
	UINT32 c_coefficient0                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient1                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA0_L_T;

typedef struct { // 0x1154
	UINT32 c_coefficient2                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient3                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA1_L_T;

typedef struct { // 0x1158
	UINT32 c_coefficient4                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient5                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA2_L_T;

typedef struct { // 0x115c
	UINT32 c_coefficient6                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient7                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA3_L_T;

typedef struct { // 0x1160
	UINT32 addr                            : 4;   //  3: 0
	UINT32 h_v_sel                         : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 update                          : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 rnw                             : 1;   //    12
} L9A0_MSC_C_FIR_COEF_CTRL_L_T;

typedef struct { // 0x1168
	UINT32 y_status                        : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_status                        : 12;  // 27:16
} L9A0_MSC_STATUS_REV_L_T;

typedef struct { // 0x116c
	UINT32 update_input_frm_size           : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 update_wout_size                : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 update_win_offset               : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 update_win_size                 : 1;   //    12
} L9A0_MSC_MANUAL_LOAD_L_T;

typedef struct { // 0x1170
	UINT32 wout_v_offset                   : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 wout_h_offset                   : 12;  // 27:16
} L9A0_MSC_WOUT_OFFSET_L_T;

typedef struct { // 0x1174
	UINT32 tearing_count_result            : 8;   //  7: 0
} L9A0_MSC_CHROMA_TEAR_L_T;

typedef struct { // 0x1178
	UINT32 auto_chroma_filter_en           : 1;   //     0
	UINT32 vsc_chroma_pre_filter_en        : 1;   //     1
	UINT32 vsc_chroma_median_filter_en     : 1;   //     2
	UINT32 manual_chroma_pre_filter_on     : 1;   //     3
	UINT32 manual_chroma_median_filter_on  : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 detect_level_th                 : 8;   // 15: 8
	UINT32 tearing_count_th                : 8;   // 23:16
	UINT32 frame_count_th                  : 4;   // 27:24
} L9A0_MSC_CHROMA_TEAR_CTRL_L_T;

typedef struct { // 0x1180
	UINT32 min_max_filter_en               : 1;   //     0
	UINT32 h_filter_en                     : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 min_max_th                      : 10;  // 13: 4
} L9A0_MSC_MIN_MAX_CTRL_L_Y_T;

typedef struct { // 0x1184
	UINT32 min_max_filter_en               : 1;   //     0
	UINT32 h_filter_en                     : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 min_max_th                      : 10;  // 13: 4
} L9A0_MSC_MIN_MAX_CTRL_L_C_T;

typedef struct { // 0x1190
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSL_MANUAL_SAMPLING_Y_H_T;

typedef struct { // 0x1194
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSL_MANUAL_SAMPLING_Y_V_T;

typedef struct { // 0x1198
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSL_MANUAL_SAMPLING_C_H_T;

typedef struct { // 0x119c
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSL_MANUAL_SAMPLING_C_V_T;

typedef struct { // 0x3100
	UINT32 bnd_pel_filtering_scheme        : 1;   //     0
	UINT32 adaptive_fir_filter_en          : 1;   //     1
	UINT32 v_scaler_config                 : 1;   //     2
	UINT32                                 : 1;   //     3
	UINT32 filter_type_sel_luma            : 1;   //     4
	UINT32 filter_type_sel_chroma          : 1;   //     5
	UINT32 manual_sampling_mode            : 1;   //     6
	UINT32                                 : 1;   //     7
	UINT32 size_info_manual_load           : 1;   //     8
} L9A0_MSC_CTRL_R_T;

typedef struct { // 0x3104
	UINT32 y_init_pos_h                    : 6;   //  5: 0
} L9A0_MSC_Y_INIT_POS_H_R_T;

typedef struct { // 0x3108
	UINT32 y_init_pos_v                    : 6;   //  5: 0
} L9A0_MSC_Y_INIT_POS_V_R_T;

typedef struct { // 0x310c
	UINT32 c_init_pos_h                    : 6;   //  5: 0
} L9A0_MSC_C_INIT_POS_H_R_T;

typedef struct { // 0x3110
	UINT32 c_init_pos_v                    : 6;   //  5: 0
} L9A0_MSC_C_INIT_POS_V_R_T;

typedef struct { // 0x3114
	UINT32 reg_th                          : 2;   //  1: 0
} L9A0_MSC_ADAPTIVE_TH_R_T;

typedef struct { // 0x3118
	UINT32 input_h_size                    : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 input_v_size                    : 12;  // 27:16
} L9A0_MSC_SCR_SIZE_R_T;

typedef struct { // 0x311c
	UINT32 out_win_h_size                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 out_win_v_size                  : 12;  // 27:16
} L9A0_MSC_WIN_OUT_SIZE_R_T;

typedef struct { // 0x3120
	UINT32 in_win_h_offset                 : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 in_win_v_offset                 : 12;  // 27:16
} L9A0_MSC_WIN_IN_OFFSET_R_T;

typedef struct { // 0x3124
	UINT32 in_win_h_size                   : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 in_win_v_size                   : 12;  // 27:16
} L9A0_MSC_WIN_IN_SIZE_R_T;

typedef struct { // 0x3128
	UINT32 in_c_format                     : 3;   //  2: 0
	UINT32                                 : 13;  // 15: 3
	UINT32 out_c_format                    : 3;   // 18:16
} L9A0_MSC_C_FORMAT_R_T;

typedef struct { // 0x3130
	UINT32 y_coefficient0                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient1                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA0_R_T;

typedef struct { // 0x3134
	UINT32 y_coefficient2                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient3                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA1_R_T;

typedef struct { // 0x3138
	UINT32 y_coefficient4                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient5                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA2_R_T;

typedef struct { // 0x313c
	UINT32 y_coefficient6                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient7                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA3_R_T;

typedef struct { // 0x3140
	UINT32 y_coefficient8                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient9                  : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA4_R_T;

typedef struct { // 0x3144
	UINT32 y_coefficient10                 : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 y_coefficient11                 : 12;  // 27:16
} L9A0_MSC_Y_FIR_COEF_DATA5_R_T;

typedef struct { // 0x3148
	UINT32 addr                            : 4;   //  3: 0
	UINT32 h_v_sel                         : 1;   //     4
	UINT32 hidden_configure4               : 1;   //     5
	UINT32                                 : 2;   //  7: 6
	UINT32 update                          : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 rnw                             : 1;   //    12
} L9A0_MSC_Y_FIR_COEF_CTRL_R_T;

typedef struct { // 0x3150
	UINT32 c_coefficient0                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient1                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA0_R_T;

typedef struct { // 0x3154
	UINT32 c_coefficient2                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient3                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA1_R_T;

typedef struct { // 0x3158
	UINT32 c_coefficient4                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient5                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA2_R_T;

typedef struct { // 0x315c
	UINT32 c_coefficient6                  : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_coefficient7                  : 12;  // 27:16
} L9A0_MSC_C_FIR_COEF_DATA3_R_T;

typedef struct { // 0x3160
	UINT32 addr                            : 4;   //  3: 0
	UINT32 h_v_sel                         : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 update                          : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 rnw                             : 1;   //    12
} L9A0_MSC_C_FIR_COEF_CTRL_R_T;

typedef struct { // 0x3168
	UINT32 y_status                        : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 c_status                        : 12;  // 27:16
} L9A0_MSC_STATUS_REV_R_T;

typedef struct { // 0x316c
	UINT32 update_input_frm_size           : 1;   //     0
	UINT32                                 : 3;   //  3: 1
	UINT32 update_wout_size                : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 update_win_offset               : 1;   //     8
	UINT32                                 : 3;   // 11: 9
	UINT32 update_win_size                 : 1;   //    12
} L9A0_MSC_MANUAL_ROAD_R_T;

typedef struct { // 0x3170
	UINT32 wout_v_offset                   : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 wout_h_offset                   : 12;  // 27:16
} L9A0_MSC_WOUT_OFFSET_R_T;

typedef struct { // 0x3174
	UINT32 tearing_count_result            : 8;   //  7: 0
} L9A0_MSC_CHROMA_TEAR_R_T;

typedef struct { // 0x3178
	UINT32 auto_chroma_filter_en           : 1;   //     0
	UINT32 vsc_chroma_pre_filter_en        : 1;   //     1
	UINT32 vsc_chroma_median_filter_en     : 1;   //     2
	UINT32 manual_chroma_pre_filter_on     : 1;   //     3
	UINT32 manual_chroma_median_filter_on  : 1;   //     4
	UINT32                                 : 3;   //  7: 5
	UINT32 detect_level_th                 : 8;   // 15: 8
	UINT32 tearing_count_th                : 8;   // 23:16
	UINT32 frame_count_th                  : 4;   // 27:24
} L9A0_MSC_CHROMA_TEAR_CTRL_R_T;

typedef struct { // 0x3180
	UINT32 min_max_filter_en               : 1;   //     0
	UINT32 h_filter_en                     : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 min_max_th                      : 10;  // 13: 4
} L9A0_MSC_MIN_MAX_CTRL_R_Y_T;

typedef struct { // 0x3184
	UINT32 min_max_filter_en               : 1;   //     0
	UINT32 h_filter_en                     : 1;   //     1
	UINT32                                 : 2;   //  3: 2
	UINT32 min_max_th                      : 10;  // 13: 4
} L9A0_MSC_MIN_MAX_CTRL_R_C_T;

typedef struct { // 0x3190
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSR_MANUAL_SAMPLING_Y_H_T;

typedef struct { // 0x3194
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSR_MANUAL_SAMPLING_Y_V_T;

typedef struct { // 0x3198
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSR_MANUAL_SAMPLING_C_H_T;

typedef struct { // 0x319c
	UINT32 numerator                       : 12;  // 11: 0
	UINT32                                 : 4;   // 15:12
	UINT32 denominator                     : 12;  // 27:16
} L9A0_MSR_MANUAL_SAMPLING_C_V_T;

typedef struct {
	L9A0_MSC_CTRL_L_T               msc_ctrl_l;                      // 0x1100
	L9A0_MSC_Y_INIT_POS_H_L_T       msc_y_init_pos_h_l;              // 0x1104
	L9A0_MSC_Y_INIT_POS_V_L_T       msc_y_init_pos_v_l;              // 0x1108
	L9A0_MSC_C_INIT_POS_H_L_T       msc_c_init_pos_h_l;              // 0x110c
	L9A0_MSC_C_INIT_POS_V_L_T       msc_c_init_pos_v_l;              // 0x1110
	L9A0_MSC_ADAPTIVE_TH_L_T        msc_adaptive_th_l;               // 0x1114
	L9A0_MSC_SCR_SIZE_L_T           msc_scr_size_l;                  // 0x1118
	L9A0_MSC_WIN_OUT_SIZE_L_T       msc_win_out_size_l;              // 0x111c
	L9A0_MSC_WIN_IN_OFFSET_L_T      msc_win_in_offset_l;             // 0x1120
	L9A0_MSC_WIN_IN_SIZE_L_T        msc_win_in_size_l;               // 0x1124
	L9A0_MSC_C_FORMAT_L_T           msc_c_format_l;                  // 0x1128
	UINT32                          reserved0;                       // 0x112c
	L9A0_MSC_Y_FIR_COEF_DATA0_L_T   msc_y_fir_coef_data0_l;          // 0x1130
	L9A0_MSC_Y_FIR_COEF_DATA1_L_T   msc_y_fir_coef_data1_l;          // 0x1134
	L9A0_MSC_Y_FIR_COEF_DATA2_L_T   msc_y_fir_coef_data2_l;          // 0x1138
	L9A0_MSC_Y_FIR_COEF_DATA3_L_T   msc_y_fir_coef_data3_l;          // 0x113c
	L9A0_MSC_Y_FIR_COEF_DATA4_L_T   msc_y_fir_coef_data4_l;          // 0x1140
	L9A0_MSC_Y_FIR_COEF_DATA5_L_T   msc_y_fir_coef_data5_l;          // 0x1144
	L9A0_MSC_Y_FIR_COEF_CTRL_L_T    msc_y_fir_coef_ctrl_l;           // 0x1148
	UINT32                          reserved1;                       // 0x114c
	L9A0_MSC_C_FIR_COEF_DATA0_L_T   msc_c_fir_coef_data0_l;          // 0x1150
	L9A0_MSC_C_FIR_COEF_DATA1_L_T   msc_c_fir_coef_data1_l;          // 0x1154
	L9A0_MSC_C_FIR_COEF_DATA2_L_T   msc_c_fir_coef_data2_l;          // 0x1158
	L9A0_MSC_C_FIR_COEF_DATA3_L_T   msc_c_fir_coef_data3_l;          // 0x115c
	L9A0_MSC_C_FIR_COEF_CTRL_L_T    msc_c_fir_coef_ctrl_l;           // 0x1160
	UINT32                          reserved2;                       // 0x1164
	L9A0_MSC_STATUS_REV_L_T         msc_status_rev_l;                // 0x1168
	L9A0_MSC_MANUAL_LOAD_L_T        msc_manual_load_l;               // 0x116c
	L9A0_MSC_WOUT_OFFSET_L_T        msc_wout_offset_l;               // 0x1170
	L9A0_MSC_CHROMA_TEAR_L_T        msc_chroma_tear_l;               // 0x1174
	L9A0_MSC_CHROMA_TEAR_CTRL_L_T   msc_chroma_tear_ctrl_l;          // 0x1178
	UINT32                          reserved3;                       // 0x117c
	L9A0_MSC_MIN_MAX_CTRL_L_Y_T     msc_min_max_ctrl_l_y;            // 0x1180
	L9A0_MSC_MIN_MAX_CTRL_L_C_T     msc_min_max_ctrl_l_c;            // 0x1184
	UINT32                          reserved4[2];                    // 0x1188~0x118c
	L9A0_MSL_MANUAL_SAMPLING_Y_H_T  msl_manual_sampling_y_h;         // 0x1190
	L9A0_MSL_MANUAL_SAMPLING_Y_V_T  msl_manual_sampling_y_v;         // 0x1194
	L9A0_MSL_MANUAL_SAMPLING_C_H_T  msl_manual_sampling_c_h;         // 0x1198
	L9A0_MSL_MANUAL_SAMPLING_C_V_T  msl_manual_sampling_c_v;         // 0x119c
} DE_MSL_REG_L9A0_T;

typedef struct {
	L9A0_MSC_CTRL_R_T               msc_ctrl_r;                      // 0x3100
	L9A0_MSC_Y_INIT_POS_H_R_T       msc_y_init_pos_h_r;              // 0x3104
	L9A0_MSC_Y_INIT_POS_V_R_T       msc_y_init_pos_v_r;              // 0x3108
	L9A0_MSC_C_INIT_POS_H_R_T       msc_c_init_pos_h_r;              // 0x310c
	L9A0_MSC_C_INIT_POS_V_R_T       msc_c_init_pos_v_r;              // 0x3110
	L9A0_MSC_ADAPTIVE_TH_R_T        msc_adaptive_th_r;               // 0x3114
	L9A0_MSC_SCR_SIZE_R_T           msc_scr_size_r;                  // 0x3118
	L9A0_MSC_WIN_OUT_SIZE_R_T       msc_win_out_size_r;              // 0x311c
	L9A0_MSC_WIN_IN_OFFSET_R_T      msc_win_in_offset_r;             // 0x3120
	L9A0_MSC_WIN_IN_SIZE_R_T        msc_win_in_size_r;               // 0x3124
	L9A0_MSC_C_FORMAT_R_T           msc_c_format_r;                  // 0x3128
	UINT32                          reserved5;                       // 0x312c
	L9A0_MSC_Y_FIR_COEF_DATA0_R_T   msc_y_fir_coef_data0_r;          // 0x3130
	L9A0_MSC_Y_FIR_COEF_DATA1_R_T   msc_y_fir_coef_data1_r;          // 0x3134
	L9A0_MSC_Y_FIR_COEF_DATA2_R_T   msc_y_fir_coef_data2_r;          // 0x3138
	L9A0_MSC_Y_FIR_COEF_DATA3_R_T   msc_y_fir_coef_data3_r;          // 0x313c
	L9A0_MSC_Y_FIR_COEF_DATA4_R_T   msc_y_fir_coef_data4_r;          // 0x3140
	L9A0_MSC_Y_FIR_COEF_DATA5_R_T   msc_y_fir_coef_data5_r;          // 0x3144
	L9A0_MSC_Y_FIR_COEF_CTRL_R_T    msc_y_fir_coef_ctrl_r;           // 0x3148
	UINT32                          reserved6;                       // 0x314c
	L9A0_MSC_C_FIR_COEF_DATA0_R_T   msc_c_fir_coef_data0_r;          // 0x3150
	L9A0_MSC_C_FIR_COEF_DATA1_R_T   msc_c_fir_coef_data1_r;          // 0x3154
	L9A0_MSC_C_FIR_COEF_DATA2_R_T   msc_c_fir_coef_data2_r;          // 0x3158
	L9A0_MSC_C_FIR_COEF_DATA3_R_T   msc_c_fir_coef_data3_r;          // 0x315c
	L9A0_MSC_C_FIR_COEF_CTRL_R_T    msc_c_fir_coef_ctrl_r;           // 0x3160
	UINT32                          reserved7;                       // 0x3164
	L9A0_MSC_STATUS_REV_R_T         msc_status_rev_r;                // 0x3168
	L9A0_MSC_MANUAL_ROAD_R_T        msc_manual_road_r;               // 0x316c
	L9A0_MSC_WOUT_OFFSET_R_T        msc_wout_offset_r;               // 0x3170
	L9A0_MSC_CHROMA_TEAR_R_T        msc_chroma_tear_r;               // 0x3174
	L9A0_MSC_CHROMA_TEAR_CTRL_R_T   msc_chroma_tear_ctrl_r;          // 0x3178
	UINT32                          reserved8;                       // 0x317c
	L9A0_MSC_MIN_MAX_CTRL_R_Y_T     msc_min_max_ctrl_r_y;            // 0x3180
	L9A0_MSC_MIN_MAX_CTRL_R_C_T     msc_min_max_ctrl_r_c;            // 0x3184
	UINT32                          reserved9[2];                    // 0x3188~0x318c
	L9A0_MSR_MANUAL_SAMPLING_Y_H_T  msr_manual_sampling_y_h;         // 0x3190
	L9A0_MSR_MANUAL_SAMPLING_Y_V_T  msr_manual_sampling_y_v;         // 0x3194
	L9A0_MSR_MANUAL_SAMPLING_C_H_T  msr_manual_sampling_c_h;         // 0x3198
	L9A0_MSR_MANUAL_SAMPLING_C_V_T  msr_manual_sampling_c_v;         // 0x319c
} DE_MSR_REG_L9A0_T;

#endif
