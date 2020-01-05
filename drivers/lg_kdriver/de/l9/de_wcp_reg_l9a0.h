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

#ifndef _REG_WCP_L9A0_h
#define _REG_WCP_L9A0_h

typedef struct { // 0x1200
	UINT32 main_444                : 1;   //     0
	UINT32                         : 1;   //     1
	UINT32 main_420                : 1;   //     2
	UINT32                         : 1;   //     3
	UINT32 main_lsr_2b             : 2;   //  5: 4
	UINT32 main_cflt_mode          : 2;   //  7: 6
	UINT32 sub_444                 : 1;   //     8
	UINT32                         : 1;   //     9
	UINT32 sub_420                 : 1;   //    10
	UINT32                         : 1;   //    11
	UINT32 sub_lsr_2b              : 2;   // 13:12
	UINT32 sub_cflt_mode           : 2;   // 15:14
} L9A0_OVL_OV_CTRL0_T;

typedef struct { // 0x1204
	UINT32 border_color_cr         : 4;   //  3: 0
	UINT32 border_color_cb         : 4;   //  7: 4
	UINT32 border_color_yy         : 8;   // 15: 8
	UINT32 load_enable             : 1;   //    16
	UINT32 load_type               : 1;   //    17
} L9A0_OV_CTRL1_T;

typedef struct { // 0x1208
	UINT32 back_color_cr           : 4;   //  3: 0
	UINT32 back_color_cb           : 4;   //  7: 4
	UINT32 back_color_yy           : 8;   // 15: 8
	UINT32 dark_color_cr           : 4;   // 19:16
	UINT32 dark_color_cb           : 4;   // 23:20
	UINT32 dark_color_yy           : 8;   // 31:24
} L9A0_OV_CTRL2_T;

typedef struct { // 0x120c
	UINT32 w0_blending_alpha       : 8;   //  7: 0
	UINT32 w1_blending_alpha       : 8;   // 15: 8
	UINT32 w2_blending_alpha       : 8;   // 23:16
	UINT32 w0_blending_mode        : 2;   // 25:24
	UINT32 w1_blending_mode        : 2;   // 27:26
	UINT32 w2_blending_mode        : 2;   // 29:28
} L9A0_OV_CTRL3_T;

typedef struct { // 0x1210
	UINT32 m_hoffset               : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 m_voffset               : 12;  // 27:16
} L9A0_OVL_OV_MOFFSET_T;

typedef struct { // 0x1214
	UINT32 m_hsize                 : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 m_vsize                 : 12;  // 27:16
} L9A0_OVL_OV_MSIZE_T;

typedef struct { // 0x1218
	UINT32 s_hoffset               : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 s_voffset               : 11;  // 26:16
} L9A0_OV_SOFFSET_T;

typedef struct { // 0x121c
	UINT32 s_hsize                 : 11;  // 10: 0
	UINT32                         : 5;   // 15:11
	UINT32 s_vsize                 : 11;  // 26:16
} L9A0_OV_SSIZE_T;

typedef struct { // 0x1220
	UINT32 s_right_wid             : 4;   //  3: 0
	UINT32 s_left_wid              : 4;   //  7: 4
	UINT32 s_down_wid              : 4;   // 11: 8
	UINT32 s_up_wid                : 4;   // 15:12
	UINT32 m_right_wid             : 4;   // 19:16
	UINT32 m_left_wid              : 4;   // 23:20
	UINT32 m_down_wid              : 4;   // 27:24
	UINT32 m_up_wid                : 4;   // 31:28
} L9A0_OVL_OV_BORDER_WIDTH_T;

typedef struct { // 0x1224
	UINT32 cflt_coef_1             : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 cflt_coef_0             : 12;  // 27:16
} L9A0_OVL_CFLT_COEF0_T;

typedef struct { // 0x1228
	UINT32 cflt_coef_3             : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 cflt_coef_2             : 12;  // 27:16
} L9A0_OVL_CFLT_COEF1_T;

typedef struct { // 0x1230
	UINT32                         : 9;   //  8: 0
	UINT32 stride                  : 2;   // 10: 9
	UINT32                         : 5;   // 15:11
	UINT32 vsize                   : 8;   // 23:16
	UINT32                         : 6;   // 29:24
	UINT32 endian_conversion       : 1;   //    30
	UINT32 update_by_ddr           : 1;   //    31
} L9A0_OVL_OV_PARAM_BY_DDR_T;

typedef struct { // 0x1240
	UINT32 intr_enable             : 1;   //     0
	UINT32 intr_line_pos_enable    : 1;   //     1
	UINT32                         : 6;   //  7: 2
	UINT32 intr_sbuf_c_empty_en    : 1;   //     8
	UINT32 intr_sbuf_y_empty_en    : 1;   //     9
	UINT32 intr_mbuf_c_empty_en    : 1;   //    10
	UINT32 intr_mbuf_y_empty_en    : 1;   //    11
	UINT32 intr_pdb_end_en         : 1;   //    12
	UINT32                         : 3;   // 15:13
	UINT32 line_position           : 11;  // 26:16
} L9A0_OVL_OV_INTR_CTRL_T;

typedef struct { // 0x1244
	UINT32 sbuf_c_empty            : 1;   //     0
	UINT32 sbuf_y_empty            : 1;   //     1
	UINT32 mbuf_c_empty            : 1;   //     2
	UINT32 mbuf_y_empty            : 1;   //     3
	UINT32                         : 12;  // 15: 4
	UINT32 line_cnt                : 11;  // 26:16
} L9A0_OVL_OV_INTR_STATUS_T;

typedef struct { // 0x1248
	UINT32 w0_imux_ctrl            : 2;   //  1: 0
	UINT32 w0_dark_en              : 1;   //     2
	UINT32                         : 1;   //     3
	UINT32 w1_imux_ctrl            : 2;   //  5: 4
	UINT32 w1_dark_en              : 1;   //     6
	UINT32                         : 1;   //     7
	UINT32 w2_imux_ctrl            : 2;   //  9: 8
	UINT32 w2_dark_en              : 1;   //    10
} L9A0_OV_CTRL4_T;

typedef struct { // 0x124c
	UINT32 pxl_alpha_en            : 1;   //     0
	UINT32 pxl_alpha_reverse       : 1;   //     1
	UINT32 pxl_alpha_clip_mode     : 2;   //  3: 2
	UINT32 ckey_en                 : 1;   //     4
	UINT32 ckey_mode               : 1;   //     5
	UINT32 pxl_yy_reverse          : 1;   //     6
	UINT32 pxl_cc_reverse          : 1;   //     7
	UINT32                         : 8;   // 15: 8
	UINT32 ckey_th_yy1             : 8;   // 23:16
	UINT32 ckey_th_yy0             : 8;   // 31:24
} L9A0_OV_CTRL5_T;

typedef struct { // 0x1250
	UINT32 ckey_th_cr1             : 8;   //  7: 0
	UINT32 ckey_th_cr0             : 8;   // 15: 8
	UINT32 ckey_th_cb1             : 8;   // 23:16
	UINT32 ckey_th_cb0             : 8;   // 31:24
} L9A0_OV_CTRL6_T;

typedef struct { // 0x3200
	UINT32 main_444                : 1;   //     0
	UINT32                         : 1;   //     1
	UINT32 main_420                : 1;   //     2
	UINT32                         : 3;   //  5: 3
	UINT32 main_cflt_mode          : 2;   //  7: 6
} L9A0_OVR_OV_CTRL0_T;

typedef struct { // 0x3210
	UINT32 m_hoffset               : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 m_voffset               : 12;  // 27:16
} L9A0_OVR_OV_MOFFSET_T;

typedef struct { // 0x3214
	UINT32 m_hsize                 : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 m_vsize                 : 12;  // 27:16
} L9A0_OVR_OV_MSIZE_T;

typedef struct { // 0x3220
	UINT32                         : 16;  // 15: 0
	UINT32 m_right_wid             : 4;   // 19:16
	UINT32 m_left_wid              : 4;   // 23:20
	UINT32 m_down_wid              : 4;   // 27:24
	UINT32 m_up_wid                : 4;   // 31:28
} L9A0_OVR_OV_BORDER_WIDTH_T;

typedef struct { // 0x3224
	UINT32 cflt_coef_1             : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 cflt_coef_0             : 12;  // 27:16
} L9A0_OVR_CFLT_COEF0_T;

typedef struct { // 0x3228
	UINT32 cflt_coef_3             : 12;  // 11: 0
	UINT32                         : 4;   // 15:12
	UINT32 cflt_coef_2             : 12;  // 27:16
} L9A0_OVR_CFLT_COEF1_T;

typedef struct { // 0x3230
	UINT32                         : 9;   //  8: 0
	UINT32 stride                  : 2;   // 10: 9
	UINT32                         : 5;   // 15:11
	UINT32 vsize                   : 8;   // 23:16
	UINT32                         : 6;   // 29:24
	UINT32 endian_conversion       : 1;   //    30
	UINT32 update_by_ddr           : 1;   //    31
} L9A0_OVR_OV_PARAM_BY_DDR_T;

typedef struct { // 0x3240
	UINT32 intr_enable             : 1;   //     0
	UINT32 intr_line_pos_enable    : 1;   //     1
	UINT32                         : 6;   //  7: 2
	UINT32 intr_sbuf_c_empty_en    : 1;   //     8
	UINT32 intr_sbuf_y_empty_en    : 1;   //     9
	UINT32 intr_mbuf_c_empty_en    : 1;   //    10
	UINT32 intr_mbuf_y_empty_en    : 1;   //    11
	UINT32 intr_pdb_end_en         : 1;   //    12
	UINT32                         : 3;   // 15:13
	UINT32 line_position           : 11;  // 26:16
} L9A0_OVR_OV_INTR_CTRL_T;

typedef struct { // 0x3244
	UINT32                         : 2;   //  1: 0
	UINT32 mbuf_c_empty            : 1;   //     2
	UINT32 mbuf_y_empty            : 1;   //     3
	UINT32                         : 12;  // 15: 4
	UINT32 line_cnt                : 11;  // 26:16
} L9A0_OVR_OV_INTR_STATUS_T;

typedef struct {
	L9A0_OVL_OV_CTRL0_T         ovl_ov_ctrl0;                // 0x1200
	L9A0_OV_CTRL1_T             ov_ctrl1;                    // 0x1204
	L9A0_OV_CTRL2_T             ov_ctrl2;                    // 0x1208
	L9A0_OV_CTRL3_T             ov_ctrl3;                    // 0x120c
	L9A0_OVL_OV_MOFFSET_T       ovl_ov_moffset;              // 0x1210
	L9A0_OVL_OV_MSIZE_T         ovl_ov_msize;                // 0x1214
	L9A0_OV_SOFFSET_T           ov_soffset;                  // 0x1218
	L9A0_OV_SSIZE_T             ov_ssize;                    // 0x121c
	L9A0_OVL_OV_BORDER_WIDTH_T  ovl_ov_border_width;         // 0x1220
	L9A0_OVL_CFLT_COEF0_T       ovl_cflt_coef0;              // 0x1224
	L9A0_OVL_CFLT_COEF1_T       ovl_cflt_coef1;              // 0x1228
	UINT32                      reserved0;                   // 0x122c
	L9A0_OVL_OV_PARAM_BY_DDR_T  ovl_ov_param_by_ddr;         // 0x1230
	UINT32                      reserved1[3];                // 0x1234~0x123c
	L9A0_OVL_OV_INTR_CTRL_T     ovl_ov_intr_ctrl;            // 0x1240
	L9A0_OVL_OV_INTR_STATUS_T   ovl_ov_intr_status;          // 0x1244
	L9A0_OV_CTRL4_T             ov_ctrl4;                    // 0x1248
	L9A0_OV_CTRL5_T             ov_ctrl5;                    // 0x124c
	L9A0_OV_CTRL6_T             ov_ctrl6;                    // 0x1250
} DE_OVL_REG_L9A0_T;

typedef struct {
	L9A0_OVR_OV_CTRL0_T         ovr_ov_ctrl0;                // 0x3200
	UINT32                      reserved2[3];                // 0x3204~0x320c
	L9A0_OVR_OV_MOFFSET_T       ovr_ov_moffset;              // 0x3210
	L9A0_OVR_OV_MSIZE_T         ovr_ov_msize;                // 0x3214
	UINT32                      reserved3[2];                // 0x3218~0x321c
	L9A0_OVR_OV_BORDER_WIDTH_T  ovr_ov_border_width;         // 0x3220
	L9A0_OVR_CFLT_COEF0_T       ovr_cflt_coef0;              // 0x3224
	L9A0_OVR_CFLT_COEF1_T       ovr_cflt_coef1;              // 0x3228
	UINT32                      reserved4;                   // 0x322c
	L9A0_OVR_OV_PARAM_BY_DDR_T  ovr_ov_param_by_ddr;         // 0x3230
	UINT32                      reserved5[3];                // 0x3234~0x323c
	L9A0_OVR_OV_INTR_CTRL_T     ovr_ov_intr_ctrl;            // 0x3240
	L9A0_OVR_OV_INTR_STATUS_T   ovr_ov_intr_status;          // 0x3244
} DE_OVR_REG_L9A0_T;

#endif
