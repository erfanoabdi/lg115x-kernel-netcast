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

#ifndef _REG_T3D_L9B0_h
#define _REG_T3D_L9B0_h

/*-----------------------------------------------------------------------------
	0x1900 soft_reset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 soft_reset              : 1;   //     0
} L9B0_SOFT_RESET_T;

/*-----------------------------------------------------------------------------
	0x1904 t3_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 t3_enable               : 1;   //     0
	UINT32 t3_bypass_mode          : 1;   //     1
	UINT32 t3_format_mode          : 2;   //  2: 3
	UINT32 t3_color                : 1;   //     4
} L9B0_T3_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1908 t3_inout_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 t3_height               : 11;  //  0:10
	UINT32                         : 5;   // 11:15 reserved
	UINT32 t3_width                : 11;  // 16:26
} L9B0_T3_INOUT_SIZE_T;

/*-----------------------------------------------------------------------------
	0x190c t3_depth_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 exp_disp_max            : 7;   //  0: 6
	UINT32                         : 1;   //     7 reserved
	UINT32 exp_disp_min            : 7;   //  8:14
	UINT32                         : 1;   //    15 reserved
	UINT32 obj_depth_scale         : 8;   // 16:23
	UINT32 depth_scale             : 8;   // 24:31
} L9B0_T3_DEPTH_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x1910 t3_depth_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 crop_size               : 8;   //  0: 7
	UINT32                         : 8;   //  8:15 reserved
	UINT32 convergence             : 7;   // 16:22
} L9B0_T3_DEPTH_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x1914 t3_mul_factor ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mul_factor              : 8;   //  0: 7
} L9B0_T3_MUL_FACTOR_T;

/*-----------------------------------------------------------------------------
	0x1930 inp_dec_v ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_v_filter3           : 5;   //  0: 4
	UINT32                         : 3;   //  5: 7 reserved
	UINT32 dec_v_filter2_          : 5;   //  8:12
	UINT32                         : 3;   // 13:15 reserved
	UINT32 dec_v_filter1_          : 5;   // 16:20
	UINT32                         : 3;   // 21:23 reserved
	UINT32 dec_v_filter0_          : 5;   // 24:28
} L9B0_INP_DEC_V_T;

/*-----------------------------------------------------------------------------
	0x1934 inp_dec_h ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 dec_h_filter3           : 5;   //  0: 4
	UINT32                         : 3;   //  5: 7 reserved
	UINT32 dec_h_filter2_          : 5;   //  8:12
	UINT32                         : 3;   // 13:15 reserved
	UINT32 dec_h_filter1_          : 5;   // 16:20
	UINT32                         : 3;   // 21:23 reserved
	UINT32 dec_h_filter0_          : 5;   // 24:28
} L9B0_INP_DEC_H_T;

/*-----------------------------------------------------------------------------
	0x1938 csc_rgb2y_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 inp_csc_y_g             : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 inp_csc_y_r             : 12;  // 16:27
} L9B0_CSC_RGB2Y_COEF0_T;

/*-----------------------------------------------------------------------------
	0x193c csc_rgb2y_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                         : 16;  //  0:15 reserved
	UINT32 inp_csc_y_b             : 12;  // 16:27
} L9B0_CSC_RGB2Y_COEF1_T;

/*-----------------------------------------------------------------------------
	0x1940 csc_rgb2cb_coef ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 inp_csc_cb_g            : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 inp_csc_cb_r            : 12;  // 16:27
} L9B0_CSC_RGB2CB_COEF_T;

/*-----------------------------------------------------------------------------
	0x1944 csc_rgb2cr_coef ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 inp_csc_cr_b            : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 inp_csc_cr_g            : 12;  // 16:27
} L9B0_CSC_RGB2CR_COEF_T;

/*-----------------------------------------------------------------------------
	0x1950 seg_col_param0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_col_param_2         : 8;   //  0: 7
	UINT32 seg_col_param_1         : 8;   //  8:15
	UINT32 seg_col_param_0         : 8;   // 16:23
} L9B0_SEG_COL_PARAM0_T;

/*-----------------------------------------------------------------------------
	0x1954 seg_col_param1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_col_param_6         : 8;   //  0: 7
	UINT32 seg_col_param_5         : 8;   //  8:15
	UINT32 seg_col_param_4         : 8;   // 16:23
	UINT32 seg_col_param_3         : 8;   // 24:31
} L9B0_SEG_COL_PARAM1_T;

/*-----------------------------------------------------------------------------
	0x1958 seg_col_param2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_col_param_10        : 8;   //  0: 7
	UINT32 seg_col_param_9         : 8;   //  8:15
	UINT32 seg_col_param_8         : 8;   // 16:23
	UINT32 seg_col_param_7         : 8;   // 24:31
} L9B0_SEG_COL_PARAM2_T;

/*-----------------------------------------------------------------------------
	0x195c seg_col_param3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_col_param_14        : 8;   //  0: 7
	UINT32 seg_col_param_13        : 8;   //  8:15
	UINT32 seg_col_param_12        : 8;   // 16:23
	UINT32 seg_col_param_11        : 8;   // 24:31
} L9B0_SEG_COL_PARAM3_T;

/*-----------------------------------------------------------------------------
	0x1960 seg_obj0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_ftr_param_3         : 8;   //  0: 7
	UINT32 seg_ftr_param_2         : 8;   //  8:15
	UINT32 seg_ftr_param_1         : 8;   // 16:23
	UINT32 seg_ftr_param_0         : 8;   // 24:31
} L9B0_SEG_OBJ0_T;

/*-----------------------------------------------------------------------------
	0x1964 seg_obj1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_ftr_param_7         : 8;   //  0: 7
	UINT32 seg_ftr_param_6         : 8;   //  8:15
	UINT32 seg_ftr_param_5         : 8;   // 16:23
	UINT32 seg_ftr_param_4         : 8;   // 24:31
} L9B0_SEG_OBJ1_T;

/*-----------------------------------------------------------------------------
	0x1968 seg_obj2_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_ftr_param_11        : 8;   //  0: 7
	UINT32 seg_ftr_param_10        : 8;   //  8:15
	UINT32 seg_ftr_param_9         : 8;   // 16:23
	UINT32 seg_ftr_param_8         : 8;   // 24:31
} L9B0_SEG_OBJ2_0_T;

/*-----------------------------------------------------------------------------
	0x196c seg_obj2_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 seg_ftr_param_12        : 8;   //  0: 7
} L9B0_SEG_OBJ2_1_T;

/*-----------------------------------------------------------------------------
	0x1970 ega_mask_th ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mask_threshold1         : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 mask_threshold0         : 12;  // 16:27
} L9B0_EGA_MASK_TH_T;

/*-----------------------------------------------------------------------------
	0x1974 smd_offset0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y0_offset               : 9;   //  0: 8
	UINT32                         : 7;   //  9:15 reserved
	UINT32 x0_offset               : 9;   // 16:24
} L9B0_SMD_OFFSET0_T;

/*-----------------------------------------------------------------------------
	0x1978 smd_offset1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y1_offset               : 9;   //  0: 8
	UINT32                         : 7;   //  9:15 reserved
	UINT32 x1_offset               : 9;   // 16:24
} L9B0_SMD_OFFSET1_T;

/*-----------------------------------------------------------------------------
	0x197c smd_histogram ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 histogram_step          : 9;   //  0: 8
	UINT32                         : 7;   //  9:15 reserved
	UINT32 histogram_block         : 2;   // 16:17
} L9B0_SMD_HISTOGRAM_T;

/*-----------------------------------------------------------------------------
	0x1980 smd_edge_th ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 edge_threshold          : 17;  //  0:16
} L9B0_SMD_EDGE_TH_T;

/*-----------------------------------------------------------------------------
	0x1984 smd_blk_th ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 min_blk_threshold       : 16;  //  0:15
	UINT32 gen_blk_threshold       : 16;  // 16:31
} L9B0_SMD_BLK_TH_T;

/*-----------------------------------------------------------------------------
	0x1988 bgd_param0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 flat_dominant_seg       : 7;   //  0: 6
	UINT32                         : 1;   //     7 reserved
	UINT32 obj_eg_in_frm           : 7;   //  8:14
	UINT32                         : 1;   //    15 reserved
	UINT32 obj_flat_in_frm         : 7;   // 16:22
	UINT32                         : 1;   //    23 reserved
	UINT32 flat_in_blk             : 7;   // 24:30
} L9B0_BGD_PARAM0_T;

/*-----------------------------------------------------------------------------
	0x198c bgd_param1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 local_flat_flag         : 4;   //  0: 3
	UINT32                         : 4;   //  4: 7 reserved
	UINT32 obj0_detect_mode        : 7;   //  8:14
	UINT32                         : 1;   //    15 reserved
	UINT32 f_flat_in_blk_flat      : 7;   // 16:22
} L9B0_BGD_PARAM1_T;

/*-----------------------------------------------------------------------------
	0x1990 black_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 bg_h_blk_sel            : 1;   //     0
	UINT32                         : 3;   //  1: 3 reserved
	UINT32 bg_v_blk_sel            : 1;   //     4
	UINT32                         : 3;   //  5: 7 reserved
	UINT32 black_bar_th            : 8;   //  8:15
	UINT32 black_x_offset          : 8;   // 16:23
} L9B0_BLACK_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1994 odg_color_th ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 color_th_h              : 8;   //  0: 7
	UINT32 color_th_m              : 8;   //  8:15
	UINT32 color_th_l              : 8;   // 16:23
} L9B0_ODG_COLOR_TH_T;

/*-----------------------------------------------------------------------------
	0x1998 odg_mono_range ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mono_range_h            : 8;   //  0: 7
	UINT32 mono_range_l            : 8;   //  8:15
} L9B0_ODG_MONO_RANGE_T;

/*-----------------------------------------------------------------------------
	0x199c odg_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 obj0_factor             : 8;   //  0: 7
	UINT32 bg_factor1              : 8;   //  8:15
	UINT32 bg_factor0              : 8;   // 16:23
} L9B0_ODG_CTRL0_T;

/*-----------------------------------------------------------------------------
	0x19a0 odg_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 edge_mode               : 2;   //  0: 1
	UINT32                         : 2;   //  2: 3 reserved
	UINT32 edge_scale              : 3;   //  4: 6
	UINT32                         : 1;   //     7 reserved
	UINT32 offset_minus            : 8;   //  8:15
	UINT32 edge_factor             : 8;   // 16:23
} L9B0_ODG_CTRL1_T;

/*-----------------------------------------------------------------------------
	0x19a4 obj0_scn_slope ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 obj0_scn_slope          : 4;   //  0: 3
} L9B0_OBJ0_SCN_SLOPE_T;

/*-----------------------------------------------------------------------------
	0x19a8 scd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 scene_change_threshold  : 4;   //  0: 3
	UINT32                         : 12;  //  4:15 reserved
	UINT32 scene_change_size       : 16;  // 16:31
} L9B0_SCD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x19ac int_q_pel_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 q_pel_coef1             : 11;  //  0:10
	UINT32                         : 5;   // 11:15 reserved
	UINT32 q_pel_coef0             : 11;  // 16:26
} L9B0_INT_Q_PEL_COEF0_T;

/*-----------------------------------------------------------------------------
	0x19b0 int_q_pel_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 q_pel_coef3             : 11;  //  0:10
	UINT32                         : 5;   // 11:15 reserved
	UINT32 q_pel_coef2             : 11;  // 16:26
} L9B0_INT_Q_PEL_COEF1_T;

/*-----------------------------------------------------------------------------
	0x19b4 int_h_pel_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_pel_coef1             : 11;  //  0:10
	UINT32                         : 5;   // 11:15 reserved
	UINT32 h_pel_coef0             : 11;  // 16:26
} L9B0_INT_H_PEL_COEF0_T;

/*-----------------------------------------------------------------------------
	0x19b8 int_h_pel_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 h_pel_coef3             : 11;  //  0:10
	UINT32                         : 5;   // 11:15 reserved
	UINT32 h_pel_coef2             : 11;  // 16:26
} L9B0_INT_H_PEL_COEF1_T;

/*-----------------------------------------------------------------------------
	0x19bc scg_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sm_buffer_size          : 3;   //  0: 2
	UINT32                         : 5;   //  3: 7 reserved
	UINT32 depth_resolution        : 1;   //     8
	UINT32                         : 7;   //  9:15 reserved
	UINT32 angle                   : 10;  // 16:25
} L9B0_SCG_CTRL_T;

/*-----------------------------------------------------------------------------
	0x19c0 sdg_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sdg_addr                : 7;   //  0: 6
} L9B0_SDG_ADDR_T;

/*-----------------------------------------------------------------------------
	0x19c4 sdg_data ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 sdg_data                : 13;  //  0:12
} L9B0_SDG_DATA_T;

/*-----------------------------------------------------------------------------
	0x19c8 vsyn_hsc_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsc_coef1               : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 hsc_coef0               : 12;  // 16:27
} L9B0_VSYN_HSC_COEF0_T;

/*-----------------------------------------------------------------------------
	0x19cc vsyn_hsc_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsc_coef3               : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 hsc_coef2               : 12;  // 16:27
} L9B0_VSYN_HSC_COEF1_T;

/*-----------------------------------------------------------------------------
	0x19d0 vsyn_hsc_coef2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsc_coef5               : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 hsc_coef4               : 12;  // 16:27
} L9B0_VSYN_HSC_COEF2_T;

/*-----------------------------------------------------------------------------
	0x19d4 vsyn_hsc_coef3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsc_coef7               : 12;  //  0:11
	UINT32                         : 4;   // 12:15 reserved
	UINT32 hsc_coef6               : 12;  // 16:27
} L9B0_VSYN_HSC_COEF3_T;

/*-----------------------------------------------------------------------------
	0x1a00 yc2rgb_coef0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cb2r                    : 15;  //  0:14
	UINT32                         : 1;   //    15 reserved
	UINT32 y2r                     : 15;  // 16:30
} L9B0_YC2RGB_COEF0_T;

/*-----------------------------------------------------------------------------
	0x1a04 yc2rgb_coef1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 y2g                     : 15;  //  0:14
	UINT32                         : 1;   //    15 reserved
	UINT32 cr2r                    : 15;  // 16:30
} L9B0_YC2RGB_COEF1_T;

/*-----------------------------------------------------------------------------
	0x1a08 yc2rgb_coef2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr2g                    : 15;  //  0:14
	UINT32                         : 1;   //    15 reserved
	UINT32 cb2g                    : 15;  // 16:30
} L9B0_YC2RGB_COEF2_T;

/*-----------------------------------------------------------------------------
	0x1a0c yc2rgb_coef3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cb2b                    : 15;  //  0:14
	UINT32                         : 1;   //    15 reserved
	UINT32 y2b                     : 15;  // 16:30
} L9B0_YC2RGB_COEF3_T;

/*-----------------------------------------------------------------------------
	0x1a10 yc2rgb_coef4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                         : 16;  //  0:15 reserved
	UINT32 cr2b                    : 15;  // 16:30
} L9B0_YC2RGB_COEF4_T;

/*-----------------------------------------------------------------------------
	0x1a20 t3_proc_y0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 t3_vana_proc_y          : 16;  //  0:15
	UINT32 t3_inp_proc_y           : 16;  // 16:31
} L9B0_T3_PROC_Y0_T;

/*-----------------------------------------------------------------------------
	0x1a24 t3_proc_y1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 t3_vsyn_proc_y          : 16;  //  0:15
	UINT32 t3_dgen_proc_y          : 16;  // 16:31
} L9B0_T3_PROC_Y1_T;

typedef struct {
	L9B0_SOFT_RESET_T       soft_reset;              // 0x1900
	L9B0_T3_CTRL_T          t3_ctrl;                 // 0x1904
	L9B0_T3_INOUT_SIZE_T    t3_inout_size;           // 0x1908
	L9B0_T3_DEPTH_CTRL0_T   t3_depth_ctrl0;          // 0x190c
	L9B0_T3_DEPTH_CTRL1_T   t3_depth_ctrl1;          // 0x1910
	L9B0_T3_MUL_FACTOR_T    t3_mul_factor;           // 0x1914
	UINT32                  reserved0[6];            // 0x1918~0x192c
	L9B0_INP_DEC_V_T        inp_dec_v;               // 0x1930
	L9B0_INP_DEC_H_T        inp_dec_h;               // 0x1934
	L9B0_CSC_RGB2Y_COEF0_T  csc_rgb2y_coef0;         // 0x1938
	L9B0_CSC_RGB2Y_COEF1_T  csc_rgb2y_coef1;         // 0x193c
	L9B0_CSC_RGB2CB_COEF_T  csc_rgb2cb_coef;         // 0x1940
	L9B0_CSC_RGB2CR_COEF_T  csc_rgb2cr_coef;         // 0x1944
	UINT32                  reserved1[2];            // 0x1948~0x194c
	L9B0_SEG_COL_PARAM0_T   seg_col_param0;          // 0x1950
	L9B0_SEG_COL_PARAM1_T   seg_col_param1;          // 0x1954
	L9B0_SEG_COL_PARAM2_T   seg_col_param2;          // 0x1958
	L9B0_SEG_COL_PARAM3_T   seg_col_param3;          // 0x195c
	L9B0_SEG_OBJ0_T         seg_obj0;                // 0x1960
	L9B0_SEG_OBJ1_T         seg_obj1;                // 0x1964
	L9B0_SEG_OBJ2_0_T       seg_obj2_0;              // 0x1968
	L9B0_SEG_OBJ2_1_T       seg_obj2_1;              // 0x196c
	L9B0_EGA_MASK_TH_T      ega_mask_th;             // 0x1970
	L9B0_SMD_OFFSET0_T      smd_offset0;             // 0x1974
	L9B0_SMD_OFFSET1_T      smd_offset1;             // 0x1978
	L9B0_SMD_HISTOGRAM_T    smd_histogram;           // 0x197c
	L9B0_SMD_EDGE_TH_T      smd_edge_th;             // 0x1980
	L9B0_SMD_BLK_TH_T       smd_blk_th;              // 0x1984
	L9B0_BGD_PARAM0_T       bgd_param0;              // 0x1988
	L9B0_BGD_PARAM1_T       bgd_param1;              // 0x198c
	L9B0_BLACK_CTRL_T       black_ctrl;              // 0x1990
	L9B0_ODG_COLOR_TH_T     odg_color_th;            // 0x1994
	L9B0_ODG_MONO_RANGE_T   odg_mono_range;          // 0x1998
	L9B0_ODG_CTRL0_T        odg_ctrl0;               // 0x199c
	L9B0_ODG_CTRL1_T        odg_ctrl1;               // 0x19a0
	L9B0_OBJ0_SCN_SLOPE_T   obj0_scn_slope;          // 0x19a4
	L9B0_SCD_CTRL_T         scd_ctrl;                // 0x19a8
	L9B0_INT_Q_PEL_COEF0_T  int_q_pel_coef0;         // 0x19ac
	L9B0_INT_Q_PEL_COEF1_T  int_q_pel_coef1;         // 0x19b0
	L9B0_INT_H_PEL_COEF0_T  int_h_pel_coef0;         // 0x19b4
	L9B0_INT_H_PEL_COEF1_T  int_h_pel_coef1;         // 0x19b8
	L9B0_SCG_CTRL_T         scg_ctrl;                // 0x19bc
	L9B0_SDG_ADDR_T         sdg_addr;                // 0x19c0
	L9B0_SDG_DATA_T         sdg_data;                // 0x19c4
	L9B0_VSYN_HSC_COEF0_T   vsyn_hsc_coef0;          // 0x19c8
	L9B0_VSYN_HSC_COEF1_T   vsyn_hsc_coef1;          // 0x19cc
	L9B0_VSYN_HSC_COEF2_T   vsyn_hsc_coef2;          // 0x19d0
	L9B0_VSYN_HSC_COEF3_T   vsyn_hsc_coef3;          // 0x19d4
	UINT32                  reserved2[10];           // 0x19d8~0x19fc
	L9B0_YC2RGB_COEF0_T     yc2rgb_coef0;            // 0x1a00
	L9B0_YC2RGB_COEF1_T     yc2rgb_coef1;            // 0x1a04
	L9B0_YC2RGB_COEF2_T     yc2rgb_coef2;            // 0x1a08
	L9B0_YC2RGB_COEF3_T     yc2rgb_coef3;            // 0x1a0c
	L9B0_YC2RGB_COEF4_T     yc2rgb_coef4;            // 0x1a10
	UINT32                  reserved3[3];            // 0x1a14~0x1a1c
	L9B0_T3_PROC_Y0_T       t3_proc_y0;              // 0x1a20
	L9B0_T3_PROC_Y1_T       t3_proc_y1;              // 0x1a24
} DE_T3D_REG_L9B0_T;

#endif
