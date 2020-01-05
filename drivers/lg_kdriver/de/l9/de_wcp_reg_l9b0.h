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

#ifndef _REG_WCP_L9B0_h
#define _REG_WCP_L9B0_h

/*-----------------------------------------------------------------------------
	0x1200 ovl_ov_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_444                    : 1;   //     0
	UINT32                             : 1;   //     1 reserved
	UINT32 main_420                    : 1;   //     2
	UINT32                             : 1;   //     3 reserved
	UINT32 main_lsr_2b                 : 2;   //  4: 5
	UINT32 main_cflt_mode              : 2;   //  6: 7
	UINT32 sub_444                     : 1;   //     8
	UINT32                             : 1;   //     9 reserved
	UINT32 sub_420                     : 1;   //    10
	UINT32                             : 1;   //    11 reserved
	UINT32 sub_lsr_2b                  : 2;   // 12:13
	UINT32 sub_cflt_mode               : 2;   // 14:15
	UINT32 mif_last_mode               : 2;   // 16:17
	UINT32                             : 2;   // 18:19 reserved
	UINT32 ov_out_sync_mux             : 2;   // 20:21
} L9B0_OVL_OV_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x1204 ov_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 border_color_cr             : 4;   //  0: 3
	UINT32 border_color_cb             : 4;   //  4: 7
	UINT32 border_color_yy             : 8;   //  8:15
	UINT32 load_enable                 : 1;   //    16
	UINT32 load_type                   : 1;   //    17
} L9B0_OV_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x1208 ov_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 back_color_cr               : 4;   //  0: 3
	UINT32 back_color_cb               : 4;   //  4: 7
	UINT32 back_color_yy               : 8;   //  8:15
	UINT32 dark_color_cr               : 4;   // 16:19
	UINT32 dark_color_cb               : 4;   // 20:23
	UINT32 dark_color_yy               : 8;   // 24:31
} L9B0_OV_CTRL2_T;

/*-----------------------------------------------------------------------------
	0x120c ov_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 w0_blending_alpha           : 8;   //  0: 7
	UINT32 w1_blending_alpha           : 8;   //  8:15
	UINT32 w2_blending_alpha           : 8;   // 16:23
	UINT32 w0_blending_mode            : 2;   // 24:25
	UINT32 w1_blending_mode            : 2;   // 26:27
	UINT32 w2_blending_mode            : 2;   // 28:29
} L9B0_OV_CTRL3_T;

/*-----------------------------------------------------------------------------
	0x1210 ovl_ov_moffset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 m_hoffset                   : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 m_voffset                   : 12;  // 16:27
} L9B0_OVL_OV_MOFFSET_T;

/*-----------------------------------------------------------------------------
	0x1214 ovl_ov_msize ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 m_hsize                     : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 m_vsize                     : 12;  // 16:27
} L9B0_OVL_OV_MSIZE_T;

/*-----------------------------------------------------------------------------
	0x1218 ov_soffset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 s_hoffset                   : 11;  //  0:10
	UINT32                             : 5;   // 11:15 reserved
	UINT32 s_voffset                   : 11;  // 16:26
} L9B0_OV_SOFFSET_T;

/*-----------------------------------------------------------------------------
	0x121c ov_ssize ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 s_hsize                     : 11;  //  0:10
	UINT32                             : 5;   // 11:15 reserved
	UINT32 s_vsize                     : 11;  // 16:26
} L9B0_OV_SSIZE_T;

/*-----------------------------------------------------------------------------
	0x1220 ovl_ov_border_width ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 s_right_wid                 : 4;   //  0: 3
	UINT32 s_left_wid                  : 4;   //  4: 7
	UINT32 s_down_wid                  : 4;   //  8:11
	UINT32 s_up_wid                    : 4;   // 12:15
	UINT32 m_right_wid                 : 4;   // 16:19
	UINT32 m_left_wid                  : 4;   // 20:23
	UINT32 m_down_wid                  : 4;   // 24:27
	UINT32 m_up_wid                    : 4;   // 28:31
} L9B0_OVL_OV_BORDER_WIDTH_T;

/*-----------------------------------------------------------------------------
	0x1224 ovl_cflt_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cflt_coef_1                 : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 cflt_coef_0                 : 12;  // 16:27
} L9B0_OVL_CFLT_COEF0_T;

/*-----------------------------------------------------------------------------
	0x1228 ovl_cflt_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cflt_coef_3                 : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 cflt_coef_2                 : 12;  // 16:27
} L9B0_OVL_CFLT_COEF1_T;

/*-----------------------------------------------------------------------------
	0x1230 ovl_ov_param_by_ddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                             : 9;   //  0: 8 reserved
	UINT32 stride                      : 2;   //  9:10
	UINT32                             : 5;   // 11:15 reserved
	UINT32 vsize                       : 8;   // 16:23
	UINT32                             : 6;   // 24:29 reserved
	UINT32 endian_conversion           : 1;   //    30
	UINT32 update_by_ddr               : 1;   //    31
} L9B0_OVL_OV_PARAM_BY_DDR_T;

/*-----------------------------------------------------------------------------
	0x1240 ovl_ov_intr_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_enable                 : 1;   //     0
	UINT32 intr_line_pos_enable        : 1;   //     1
	UINT32                             : 6;   //  2: 7 reserved
	UINT32 intr_sbuf_c_empty_en        : 1;   //     8
	UINT32 intr_sbuf_y_empty_en        : 1;   //     9
	UINT32 intr_mbuf_c_empty_en        : 1;   //    10
	UINT32 intr_mbuf_y_empty_en        : 1;   //    11
	UINT32 intr_pdb_end_en             : 1;   //    12
	UINT32                             : 3;   // 13:15 reserved
	UINT32 line_position               : 11;  // 16:26
} L9B0_OVL_OV_INTR_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1244 ovl_ov_intr_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sbuf_c_empty                : 1;   //     0
	UINT32 sbuf_y_empty                : 1;   //     1
	UINT32 mbuf_c_empty                : 1;   //     2
	UINT32 mbuf_y_empty                : 1;   //     3
	UINT32                             : 12;  //  4:15 reserved
	UINT32 line_cnt                    : 11;  // 16:26
} L9B0_OVL_OV_INTR_STATUS_T;

/*-----------------------------------------------------------------------------
	0x1248 ov_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 w0_imux_ctrl                : 2;   //  0: 1
	UINT32 w0_dark_en                  : 1;   //     2
	UINT32                             : 1;   //     3 reserved
	UINT32 w1_imux_ctrl                : 2;   //  4: 5
	UINT32 w1_dark_en                  : 1;   //     6
	UINT32                             : 1;   //     7 reserved
	UINT32 w2_imux_ctrl                : 2;   //  8: 9
	UINT32 w2_dark_en                  : 1;   //    10
} L9B0_OV_CTRL4_T;

/*-----------------------------------------------------------------------------
	0x124c ov_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 pxl_alpha_en                : 1;   //     0
	UINT32 pxl_alpha_reverse           : 1;   //     1
	UINT32 pxl_alpha_clip_mode         : 2;   //  2: 3
	UINT32 ckey_en                     : 1;   //     4
	UINT32 ckey_mode                   : 1;   //     5
	UINT32 pxl_yy_reverse              : 1;   //     6
	UINT32 pxl_cc_reverse              : 1;   //     7
	UINT32                             : 8;   //  8:15 reserved
	UINT32 ckey_th_yy1                 : 8;   // 16:23
	UINT32 ckey_th_yy0                 : 8;   // 24:31
} L9B0_OV_CTRL5_T;

/*-----------------------------------------------------------------------------
	0x1250 ov_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 ckey_th_cr1                 : 8;   //  0: 7
	UINT32 ckey_th_cr0                 : 8;   //  8:15
	UINT32 ckey_th_cb1                 : 8;   // 16:23
	UINT32 ckey_th_cb0                 : 8;   // 24:31
} L9B0_OV_CTRL6_T;

/*-----------------------------------------------------------------------------
	0x1254 ov_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cc_reverse_th_yy1           : 4;   //  0: 3
	UINT32 cc_reverse_th_yy0           : 4;   //  4: 7
	UINT32                             : 6;   //  8:13 reserved
	UINT32 cc_reverse_mode             : 2;   // 14:15
	UINT32 yy_reverse_th_cr            : 4;   // 16:19
	UINT32 yy_reverse_th_cb            : 4;   // 20:23
	UINT32                             : 6;   // 24:29 reserved
	UINT32 yy_reverse_mode             : 2;   // 30:31
} L9B0_OV_CTRL7_T;

/*-----------------------------------------------------------------------------
	0x1258 ovl_ov_yc_delay ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_delay_h                   : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 c_delay_v                   : 12;  // 16:27
	UINT32                             : 2;   // 28:29 reserved
	UINT32 v_delay_mode                : 1;   //    30
	UINT32 delay_disable               : 1;   //    31
} L9B0_OVL_OV_YC_DELAY_T;

/*-----------------------------------------------------------------------------
	0x125c ov_mif_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_c_mif_line_offset      : 12;  //  0:11
	UINT32                             : 1;   //    12 reserved
	UINT32 main_c_mif_line_inc         : 2;   // 13:14
	UINT32 main_c_manual_mif_ctrl_en   : 1;   //    15
	UINT32 main_y_mif_line_offset      : 12;  // 16:27
	UINT32                             : 1;   //    28 reserved
	UINT32 main_y_mif_line_inc         : 2;   // 29:30
	UINT32 main_y_manual_mif_ctrl_en   : 1;   //    31
} L9B0_OV_MIF_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x1260 ov_mif_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sub_c_mif_line_offset       : 12;  //  0:11
	UINT32                             : 1;   //    12 reserved
	UINT32 sub_c_mif_line_inc          : 2;   // 13:14
	UINT32 sub_c_manual_mif_ctrl_en    : 1;   //    15
	UINT32 sub_y_mif_line_offset       : 12;  // 16:27
	UINT32                             : 1;   //    28 reserved
	UINT32 sub_y_mif_line_inc          : 2;   // 29:30
	UINT32 sub_y_manual_mif_ctrl_en    : 1;   //    31
} L9B0_OV_MIF_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x3200 ovr_ov_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_444                    : 1;   //     0
	UINT32                             : 1;   //     1 reserved
	UINT32 main_420                    : 1;   //     2
	UINT32                             : 3;   //  3: 5 reserved
	UINT32 main_cflt_mode              : 2;   //  6: 7
	UINT32                             : 8;   //  8:15 reserved
	UINT32 mif_last_mode               : 1;   //    16
	UINT32                             : 3;   // 17:19 reserved
	UINT32 ov_out_sync_mux             : 1;   //    20
} L9B0_OVR_OV_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x3210 ovr_ov_moffset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 m_hoffset                   : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 m_voffset                   : 12;  // 16:27
} L9B0_OVR_OV_MOFFSET_T;

/*-----------------------------------------------------------------------------
	0x3214 ovr_ov_msize ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 m_hsize                     : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 m_vsize                     : 12;  // 16:27
} L9B0_OVR_OV_MSIZE_T;

/*-----------------------------------------------------------------------------
	0x3220 ovr_ov_border_width ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                             : 16;  //  0:15 reserved
	UINT32 m_right_wid                 : 4;   // 16:19
	UINT32 m_left_wid                  : 4;   // 20:23
	UINT32 m_down_wid                  : 4;   // 24:27
	UINT32 m_up_wid                    : 4;   // 28:31
} L9B0_OVR_OV_BORDER_WIDTH_T;

/*-----------------------------------------------------------------------------
	0x3224 ovr_cflt_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cflt_coef_1                 : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 cflt_coef_0                 : 12;  // 16:27
} L9B0_OVR_CFLT_COEF0_T;

/*-----------------------------------------------------------------------------
	0x3228 ovr_cflt_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cflt_coef_3                 : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 cflt_coef_2                 : 12;  // 16:27
} L9B0_OVR_CFLT_COEF1_T;

/*-----------------------------------------------------------------------------
	0x3230 ovr_ov_param_by_ddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                             : 9;   //  0: 8 reserved
	UINT32 stride                      : 2;   //  9:10
	UINT32                             : 5;   // 11:15 reserved
	UINT32 vsize                       : 8;   // 16:23
	UINT32                             : 6;   // 24:29 reserved
	UINT32 endian_conversion           : 1;   //    30
	UINT32 update_by_ddr               : 1;   //    31
} L9B0_OVR_OV_PARAM_BY_DDR_T;

/*-----------------------------------------------------------------------------
	0x3240 ovr_ov_intr_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 intr_enable                 : 1;   //     0
	UINT32 intr_line_pos_enable        : 1;   //     1
	UINT32                             : 6;   //  2: 7 reserved
	UINT32 intr_sbuf_c_empty_en        : 1;   //     8
	UINT32 intr_sbuf_y_empty_en        : 1;   //     9
	UINT32 intr_mbuf_c_empty_en        : 1;   //    10
	UINT32 intr_mbuf_y_empty_en        : 1;   //    11
	UINT32 intr_pdb_end_en             : 1;   //    12
	UINT32                             : 3;   // 13:15 reserved
	UINT32 line_position               : 11;  // 16:26
} L9B0_OVR_OV_INTR_CTRL_T;

/*-----------------------------------------------------------------------------
	0x3244 ovr_ov_intr_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                             : 2;   //  0: 1 reserved
	UINT32 mbuf_c_empty                : 1;   //     2
	UINT32 mbuf_y_empty                : 1;   //     3
	UINT32                             : 12;  //  4:15 reserved
	UINT32 line_cnt                    : 11;  // 16:26
} L9B0_OVR_OV_INTR_STATUS_T;

/*-----------------------------------------------------------------------------
	0x3258 ovr_ov_yc_delay ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 c_delay_h                   : 12;  //  0:11
	UINT32                             : 4;   // 12:15 reserved
	UINT32 c_delay_v                   : 12;  // 16:27
	UINT32                             : 2;   // 28:29 reserved
	UINT32 v_delay_mode                : 1;   //    30
	UINT32 delay_disable               : 1;   //    31
} L9B0_OVR_OV_YC_DELAY_T;

/*-----------------------------------------------------------------------------
	0x325c ov_mif_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 main_c_mif_line_offset      : 12;  //  0:11
	UINT32                             : 1;   //    12 reserved
	UINT32 main_c_mif_line_inc         : 2;   // 13:14
	UINT32 main_c_manual_mif_ctrl_en   : 1;   //    15
	UINT32 main_y_mif_line_offset      : 12;  // 16:27
	UINT32                             : 1;   //    28 reserved
	UINT32 main_y_mif_line_inc         : 2;   // 29:30
	UINT32 main_y_manual_mif_ctrl_en   : 1;   //    31
} L9B0_OV_MIF_CTRL_T;

typedef struct {
	L9B0_OVL_OV_CTRL0_T         ovl_ov_ctrl0;                // 0x1200
	L9B0_OV_CTRL1_T             ov_ctrl1;                    // 0x1204
	L9B0_OV_CTRL2_T             ov_ctrl2;                    // 0x1208
	L9B0_OV_CTRL3_T             ov_ctrl3;                    // 0x120c
	L9B0_OVL_OV_MOFFSET_T       ovl_ov_moffset;              // 0x1210
	L9B0_OVL_OV_MSIZE_T         ovl_ov_msize;                // 0x1214
	L9B0_OV_SOFFSET_T           ov_soffset;                  // 0x1218
	L9B0_OV_SSIZE_T             ov_ssize;                    // 0x121c
	L9B0_OVL_OV_BORDER_WIDTH_T  ovl_ov_border_width;         // 0x1220
	L9B0_OVL_CFLT_COEF0_T       ovl_cflt_coef0;              // 0x1224
	L9B0_OVL_CFLT_COEF1_T       ovl_cflt_coef1;              // 0x1228
	UINT32                      reserved0;                   // 0x122c
	L9B0_OVL_OV_PARAM_BY_DDR_T  ovl_ov_param_by_ddr;         // 0x1230
	UINT32                      reserved1[3];                // 0x1234~0x123c
	L9B0_OVL_OV_INTR_CTRL_T     ovl_ov_intr_ctrl;            // 0x1240
	L9B0_OVL_OV_INTR_STATUS_T   ovl_ov_intr_status;          // 0x1244
	L9B0_OV_CTRL4_T             ov_ctrl4;                    // 0x1248
	L9B0_OV_CTRL5_T             ov_ctrl5;                    // 0x124c
	L9B0_OV_CTRL6_T             ov_ctrl6;                    // 0x1250
	L9B0_OV_CTRL7_T             ov_ctrl7;                    // 0x1254
	L9B0_OVL_OV_YC_DELAY_T      ovl_ov_yc_delay;             // 0x1258
	L9B0_OV_MIF_CTRL0_T         ov_mif_ctrl0;                // 0x125c
	L9B0_OV_MIF_CTRL1_T         ov_mif_ctrl1;                // 0x1260
} DE_OVL_REG_L9B0_T;

typedef struct {
	L9B0_OVR_OV_CTRL0_T         ovr_ov_ctrl0;                // 0x3200
	UINT32                      reserved2[3];                // 0x3204~0x320c
	L9B0_OVR_OV_MOFFSET_T       ovr_ov_moffset;              // 0x3210
	L9B0_OVR_OV_MSIZE_T         ovr_ov_msize;                // 0x3214
	UINT32                      reserved3[2];                // 0x3218~0x321c
	L9B0_OVR_OV_BORDER_WIDTH_T  ovr_ov_border_width;         // 0x3220
	L9B0_OVR_CFLT_COEF0_T       ovr_cflt_coef0;              // 0x3224
	L9B0_OVR_CFLT_COEF1_T       ovr_cflt_coef1;              // 0x3228
	UINT32                      reserved4;                   // 0x322c
	L9B0_OVR_OV_PARAM_BY_DDR_T  ovr_ov_param_by_ddr;         // 0x3230
	UINT32                      reserved5[3];                // 0x3234~0x323c
	L9B0_OVR_OV_INTR_CTRL_T     ovr_ov_intr_ctrl;            // 0x3240
	L9B0_OVR_OV_INTR_STATUS_T   ovr_ov_intr_status;          // 0x3244
	UINT32                      reserved6[4];                // 0x3248~0x3254
	L9B0_OVR_OV_YC_DELAY_T      ovr_ov_yc_delay;             // 0x3258
	L9B0_OV_MIF_CTRL_T          ov_mif_ctrl;                 // 0x325c
} DE_OVR_REG_L9B0_T;

#endif
