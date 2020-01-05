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

/*-----------------------------------------------------------------------------
	0x0000 reg_in_img_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	in_img_width                    :11,	//  0:10
	                                : 5,	// 11:15 reserved
	in_img_height                   :11;	// 16:26
} REG_IN_IMG_SIZE;

/*-----------------------------------------------------------------------------
	0x0004 reg_in_img_format ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	in_image_format                 : 3,	//  0: 2
	                                : 1,	//     3 reserved
	color_format                    : 2,	//  4: 5
	                                : 2,	//  6: 7 reserved
	lr_in_order                     : 1,	//     8
	                                : 4,	//  9:12 reserved
	progressive                     : 1,	//    13
	double_pic                      : 1,	//    14
	in_bit_res                      : 1,	//    15
	sample_mode                     : 1,	//    16
	sample_comb                     : 2,	// 17:18
	                                : 1,	//    19 reserved
	spatial_flip                    : 1,	//    20
	tl_frame_flip                   : 1;	//    21
} REG_IN_IMG_FORMAT;

/*-----------------------------------------------------------------------------
	0x0008 reg_proc_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pre3d_src_mux                   : 1,	//     0
	                                : 3,	//  1: 3 reserved
	pre3d_run_mode                  : 2,	//  4: 5
	                                : 2,	//  6: 7 reserved
	display_format                  : 1,	//     8
	display_freq                    : 1,	//     9
	lr_out_order                    : 1,	//    10
	                                : 5,	// 11:15 reserved
	convergence                     : 9,	// 16:24
	                                : 3,	// 25:27 reserved
	convergence_mode                : 1;	//    28
} REG_PROC_MODE;

/*-----------------------------------------------------------------------------
	0x000c reg_pre3d_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	scl_filter_sum                  : 2,	//  0: 1
	scl_vsc_mode                    : 1,	//     2
	scl_adaptive_on                 : 1,	//     3
	                                : 4,	//  4: 7 reserved
	scl_th0                         : 2,	//  8: 9
	scl_th1                         : 2,	// 10:11
	scl_th2                         : 2,	// 12:13
	scl_th3                         : 2;	// 14:15
} REG_PRE3D_SCALER;

/*-----------------------------------------------------------------------------
	0x0010 reg_phase_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	phase_addr                      : 6,	//  0: 5
	                                : 2,	//  6: 7 reserved
	phase_sel                       : 1,	//     8
	                                : 3,	//  9:11 reserved
	phase_rnw                       : 1;	//    12
} REG_PHASE_CTRL;

/*-----------------------------------------------------------------------------
	0x0014 reg_phasewd0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	scl_coeff0                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	scl_coeff1                      :12;	// 16:27
} REG_PHASEWD0;

/*-----------------------------------------------------------------------------
	0x0018 reg_phasewd1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	scl_coeff2                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	scl_coeff3                      :12;	// 16:27
} REG_PHASEWD1;

/*-----------------------------------------------------------------------------
	0x001c reg_phasewd2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	scl_coeff4                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	scl_coeff5                      :12;	// 16:27
} REG_PHASEWD2;

/*-----------------------------------------------------------------------------
	0x0020 reg_phasewd3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	scl_coeff6                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	scl_coeff7                      :12;	// 16:27
} REG_PHASEWD3;

/*-----------------------------------------------------------------------------
	0x0024 reg_phasewd4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	scl_coeff8                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	scl_coeff9                      :12;	// 16:27
} REG_PHASEWD4;

/*-----------------------------------------------------------------------------
	0x0028 reg_phasewd5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	scl_coeff10                     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	scl_coeff11                     :12;	// 16:27
} REG_PHASEWD5;

/*-----------------------------------------------------------------------------
	0x002c reg_quincunx_coeff0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	qx0_coeff0                      :10,	//  0: 9
	qx0_coeff1                      :10,	// 10:19
	qx0_coeff2                      :10;	// 20:29
} REG_QUINCUNX_COEFF0;

/*-----------------------------------------------------------------------------
	0x0030 reg_quincunx_coeff1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	qx0_coeff3                      :10,	//  0: 9
	qx0_coeff4                      :10,	// 10:19
	qx0_coeff5                      :10;	// 20:29
} REG_QUINCUNX_COEFF1;

/*-----------------------------------------------------------------------------
	0x0034 reg_quincunx_coeff2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	qx0_coeff6                      :10,	//  0: 9
	qx0_coeff7                      :10,	// 10:19
	qx0_coeff8                      :10;	// 20:29
} REG_QUINCUNX_COEFF2;

/*-----------------------------------------------------------------------------
	0x0038 reg_quincunx_coeff3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	qx0_coeff9                      :10,	//  0: 9
	qx0_coeff10                     :10,	// 10:19
	qx1_coeff0                      :10;	// 20:29
} REG_QUINCUNX_COEFF3;

/*-----------------------------------------------------------------------------
	0x003c reg_quincunx_coeff4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	qx1_coeff1                      :10,	//  0: 9
	qx1_coeff2                      :10,	// 10:19
	qx1_coeff3                      :10;	// 20:29
} REG_QUINCUNX_COEFF4;

/*-----------------------------------------------------------------------------
	0x0040 reg_quincunx_coeff5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	qx1_coeff4                      :10,	//  0: 9
	qx1_coeff5                      :10,	// 10:19
	qx1_coeff6                      :10;	// 20:29
} REG_QUINCUNX_COEFF5;

/*-----------------------------------------------------------------------------
	0x0044 reg_quincunx_coeff6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	qx1_coeff7                      :10,	//  0: 9
	qx1_coeff8                      :10,	// 10:19
	qx1_coeff9                      :10;	// 20:29
} REG_QUINCUNX_COEFF6;

/*-----------------------------------------------------------------------------
	0x0048 reg_3d_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pre3d_status                    : 4,	//  0: 3
	                                : 4,	//  4: 7 reserved
	line_luma                       :11,	//  8:18
	                                : 1,	//    19 reserved
	line_chroma                     :11;	// 20:30
} REG_3D_STATUS;

/*-----------------------------------------------------------------------------
	0x004c reg_pre3d_out_img_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	out_img_format                  : 3,	//  0: 2
	                                : 5,	//  3: 7 reserved
	out_img_width                   :11,	//  8:18
	                                : 1,	//    19 reserved
	out_img_height                  :11;	// 20:30
} REG_PRE3D_OUT_IMG_INFO;

/*-----------------------------------------------------------------------------
	0x0050 reg_frame_field_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	lr_frame_id                     : 1,	//     0
	                                : 7,	//  1: 7 reserved
	field_id                        : 1;	//     8
} REG_FRAME_FIELD_INFO;

/*-----------------------------------------------------------------------------
	0x0054 reg_pdp_sp_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pdp_sp_enable                   : 1,	//     0
	pdp_sp_mot_sel                  : 1,	//     1
	                                : 6,	//  2: 7 reserved
	pdp_sp_max_offset               : 4,	//  8:11
	pdp_sp_mot_pe0_cut              : 4,	// 12:15
	pdp_sp_fr_period                :16;	// 16:31
} REG_PDP_SP_CTRL0;

/*-----------------------------------------------------------------------------
	0x0058 reg_pdp_sp_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pdp_sp_still_cnt                :16,	//  0:15
	pdp_sp_mot_th                   : 8,	// 16:23
	pdp_sp_mot_iir                  : 8;	// 24:31
} REG_PDP_SP_CTRL1;

/*-----------------------------------------------------------------------------
	0x005c reg_pdp_sp_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pdp_sp_mot_mcu                  : 8,	//  0: 7
	pdp_sp_mot_pe0                  :22,	//  8:29
	pdp_sp_shift_inc                : 2;	// 30:31
} REG_PDP_SP_CTRL2;

/*-----------------------------------------------------------------------------
	0x0060 reg_crop_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hor_crop_size                   :10;	//  0: 9
} REG_CROP_SIZE;

/*-----------------------------------------------------------------------------
	0x0064 reg_convergence_range ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	conv_min                        : 9,	//  0: 8
	                                : 7,	//  9:15 reserved
	conv_max                        : 9;	// 16:24
} REG_CONVERGENCE_RANGE;

typedef struct {
	REG_IN_IMG_SIZE                 	reg_in_img_size                 ;	// 0x0000 : ''
	REG_IN_IMG_FORMAT               	reg_in_img_format               ;	// 0x0004 : ''
	REG_PROC_MODE                   	reg_proc_mode                   ;	// 0x0008 : ''
	REG_PRE3D_SCALER                	reg_pre3d_scaler                ;	// 0x000c : ''
	REG_PHASE_CTRL                  	reg_phase_ctrl                  ;	// 0x0010 : ''
	REG_PHASEWD0                    	reg_phasewd0                    ;	// 0x0014 : ''
	REG_PHASEWD1                    	reg_phasewd1                    ;	// 0x0018 : ''
	REG_PHASEWD2                    	reg_phasewd2                    ;	// 0x001c : ''
	REG_PHASEWD3                    	reg_phasewd3                    ;	// 0x0020 : ''
	REG_PHASEWD4                    	reg_phasewd4                    ;	// 0x0024 : ''
	REG_PHASEWD5                    	reg_phasewd5                    ;	// 0x0028 : ''
	REG_QUINCUNX_COEFF0             	reg_quincunx_coeff0             ;	// 0x002c : ''
	REG_QUINCUNX_COEFF1             	reg_quincunx_coeff1             ;	// 0x0030 : ''
	REG_QUINCUNX_COEFF2             	reg_quincunx_coeff2             ;	// 0x0034 : ''
	REG_QUINCUNX_COEFF3             	reg_quincunx_coeff3             ;	// 0x0038 : ''
	REG_QUINCUNX_COEFF4             	reg_quincunx_coeff4             ;	// 0x003c : ''
	REG_QUINCUNX_COEFF5             	reg_quincunx_coeff5             ;	// 0x0040 : ''
	REG_QUINCUNX_COEFF6             	reg_quincunx_coeff6             ;	// 0x0044 : ''
	REG_3D_STATUS                   	reg_3d_status                   ;	// 0x0048 : ''
	REG_PRE3D_OUT_IMG_INFO          	reg_pre3d_out_img_info          ;	// 0x004c : ''
	REG_FRAME_FIELD_INFO            	reg_frame_field_info            ;	// 0x0050 : ''
	REG_PDP_SP_CTRL0                	reg_pdp_sp_ctrl0                ;	// 0x0054 : ''
	REG_PDP_SP_CTRL1                	reg_pdp_sp_ctrl1                ;	// 0x0058 : ''
	REG_PDP_SP_CTRL2                	reg_pdp_sp_ctrl2                ;	// 0x005c : ''
	REG_CROP_SIZE                   	reg_crop_size                   ;	// 0x0060 : ''
	REG_CONVERGENCE_RANGE           	reg_convergence_range           ;	// 0x0064 : ''
} PRE3D_REG_T;
/* 26 regs, 26 types */

/* 26 regs, 26 types in Total*/

/*
 * @{
 * Naming for register pointer.
 * gpRealRegPRE3D : real register of PRE3D.
 * gpRegPRE3D     : shadow register.
 *
 * @def PRE3D_RdFL: Read  FLushing : Shadow <- Real.
 * @def PRE3D_WrFL: Write FLushing : Shadow -> Real.
 * @def PRE3D_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def PRE3D_Wr  : Write whole register(UINT32) from Shadow register.
 * @def PRE3D_Rd01 ~ PRE3D_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def PRE3D_Wr01 ~ PRE3D_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define PRE3D_RdFL(_r)			((gpRegPRE3D->_r)=(gpRealRegPRE3D->_r))
#define PRE3D_WrFL(_r)			((gpRealRegPRE3D->_r)=(gpRegPRE3D->_r))

#define PRE3D_Rd(_r)			*((UINT32*)(&(gpRegPRE3D->_r)))
#define PRE3D_Wr(_r,_v)			((PRE3D_Rd(_r))=((UINT32)(_v)))

#define PRE3D_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
								} while(0)

#define PRE3D_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
								} while(0)

#define PRE3D_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
								} while(0)

#define PRE3D_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
								} while(0)

#define PRE3D_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
								} while(0)

#define PRE3D_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
								} while(0)

#define PRE3D_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
								} while(0)

#define PRE3D_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
								} while(0)

#define PRE3D_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
								} while(0)

#define PRE3D_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
									(_v10) = (gpRegPRE3D->_r._f10);				\
								} while(0)

#define PRE3D_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
									(_v10) = (gpRegPRE3D->_r._f10);				\
									(_v11) = (gpRegPRE3D->_r._f11);				\
								} while(0)

#define PRE3D_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
									(_v10) = (gpRegPRE3D->_r._f10);				\
									(_v11) = (gpRegPRE3D->_r._f11);				\
									(_v12) = (gpRegPRE3D->_r._f12);				\
								} while(0)

#define PRE3D_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
									(_v10) = (gpRegPRE3D->_r._f10);				\
									(_v11) = (gpRegPRE3D->_r._f11);				\
									(_v12) = (gpRegPRE3D->_r._f12);				\
									(_v13) = (gpRegPRE3D->_r._f13);				\
								} while(0)

#define PRE3D_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
									(_v10) = (gpRegPRE3D->_r._f10);				\
									(_v11) = (gpRegPRE3D->_r._f11);				\
									(_v12) = (gpRegPRE3D->_r._f12);				\
									(_v13) = (gpRegPRE3D->_r._f13);				\
									(_v14) = (gpRegPRE3D->_r._f14);				\
								} while(0)

#define PRE3D_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
									(_v10) = (gpRegPRE3D->_r._f10);				\
									(_v11) = (gpRegPRE3D->_r._f11);				\
									(_v12) = (gpRegPRE3D->_r._f12);				\
									(_v13) = (gpRegPRE3D->_r._f13);				\
									(_v14) = (gpRegPRE3D->_r._f14);				\
									(_v15) = (gpRegPRE3D->_r._f15);				\
								} while(0)

#define PRE3D_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (gpRegPRE3D->_r._f01);				\
									(_v02) = (gpRegPRE3D->_r._f02);				\
									(_v03) = (gpRegPRE3D->_r._f03);				\
									(_v04) = (gpRegPRE3D->_r._f04);				\
									(_v05) = (gpRegPRE3D->_r._f05);				\
									(_v06) = (gpRegPRE3D->_r._f06);				\
									(_v07) = (gpRegPRE3D->_r._f07);				\
									(_v08) = (gpRegPRE3D->_r._f08);				\
									(_v09) = (gpRegPRE3D->_r._f09);				\
									(_v10) = (gpRegPRE3D->_r._f10);				\
									(_v11) = (gpRegPRE3D->_r._f11);				\
									(_v12) = (gpRegPRE3D->_r._f12);				\
									(_v13) = (gpRegPRE3D->_r._f13);				\
									(_v14) = (gpRegPRE3D->_r._f14);				\
									(_v15) = (gpRegPRE3D->_r._f15);				\
									(_v16) = (gpRegPRE3D->_r._f16);				\
								} while(0)


#define PRE3D_Wr01(_r,_f01,_v01)													\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
								} while(0)

#define PRE3D_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
								} while(0)

#define PRE3D_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
								} while(0)

#define PRE3D_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
								} while(0)

#define PRE3D_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
								} while(0)

#define PRE3D_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
								} while(0)

#define PRE3D_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
								} while(0)

#define PRE3D_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
								} while(0)

#define PRE3D_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
								} while(0)

#define PRE3D_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
									(gpRegPRE3D->_r._f10) = (_v10);				\
								} while(0)

#define PRE3D_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
									(gpRegPRE3D->_r._f10) = (_v10);				\
									(gpRegPRE3D->_r._f11) = (_v11);				\
								} while(0)

#define PRE3D_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
									(gpRegPRE3D->_r._f10) = (_v10);				\
									(gpRegPRE3D->_r._f11) = (_v11);				\
									(gpRegPRE3D->_r._f12) = (_v12);				\
								} while(0)

#define PRE3D_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
									(gpRegPRE3D->_r._f10) = (_v10);				\
									(gpRegPRE3D->_r._f11) = (_v11);				\
									(gpRegPRE3D->_r._f12) = (_v12);				\
									(gpRegPRE3D->_r._f13) = (_v13);				\
								} while(0)

#define PRE3D_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
									(gpRegPRE3D->_r._f10) = (_v10);				\
									(gpRegPRE3D->_r._f11) = (_v11);				\
									(gpRegPRE3D->_r._f12) = (_v12);				\
									(gpRegPRE3D->_r._f13) = (_v13);				\
									(gpRegPRE3D->_r._f14) = (_v14);				\
								} while(0)

#define PRE3D_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
									(gpRegPRE3D->_r._f10) = (_v10);				\
									(gpRegPRE3D->_r._f11) = (_v11);				\
									(gpRegPRE3D->_r._f12) = (_v12);				\
									(gpRegPRE3D->_r._f13) = (_v13);				\
									(gpRegPRE3D->_r._f14) = (_v14);				\
									(gpRegPRE3D->_r._f15) = (_v15);				\
								} while(0)

#define PRE3D_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(gpRegPRE3D->_r._f01) = (_v01);				\
									(gpRegPRE3D->_r._f02) = (_v02);				\
									(gpRegPRE3D->_r._f03) = (_v03);				\
									(gpRegPRE3D->_r._f04) = (_v04);				\
									(gpRegPRE3D->_r._f05) = (_v05);				\
									(gpRegPRE3D->_r._f06) = (_v06);				\
									(gpRegPRE3D->_r._f07) = (_v07);				\
									(gpRegPRE3D->_r._f08) = (_v08);				\
									(gpRegPRE3D->_r._f09) = (_v09);				\
									(gpRegPRE3D->_r._f10) = (_v10);				\
									(gpRegPRE3D->_r._f11) = (_v11);				\
									(gpRegPRE3D->_r._f12) = (_v12);				\
									(gpRegPRE3D->_r._f13) = (_v13);				\
									(gpRegPRE3D->_r._f14) = (_v14);				\
									(gpRegPRE3D->_r._f15) = (_v15);				\
									(gpRegPRE3D->_r._f16) = (_v16);				\
								} while(0)

/* Indexed Register Access.
 *
 * There is in-direct field specified by 'index' field within a register.
 * Normally a register has only one meaning for a 'field_name', but indexed register
 * can hold several data for a 'field_name' specifed by 'index' field of indexed register.
 * When writing an 3rd data for given 'field_name' register, you need to set 'rw' = 0, 'index' = 2,
 * and 'load' = 0.
 *
 * ASSUMPTION
 * For Writing indexed register load bit
 *
 * parameter list
 * _r     : name of register
 * _lname : name of load  bit field	: shall be 0 after macro executed.
 * _rwname: name of rw    bit field : shall be 0 after PRE3D_Wind(), 1 for PRE3D_Rind()
 * _iname : name of index bit field
 * _ival  : index value
 * _fname : field name
 * _fval  : field variable that field value shall be stored.
 *
 * PRE3D_Rind : General indexed register Read.(
 * PRE3D_Wind : General indexed register Read.
 *
 * PRE3D_Ridx : For 'index', 'rw', 'load' field name
 * PRE3D_Widx : For 'index', 'rw', 'load' field name and NO_LOAD.
 */
#define PRE3D_Rind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
							do {												\
								PRE3D_Wr03(_r,_lname,0,_rwname,1,_iname,_ival);	\
								PRE3D_WrFL(_r);									\
								PRE3D_RdFL(_r);									\
								PRE3D_Rd01(_r,_fname,_fval);						\
							} while (0)

#define PRE3D_Wind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
				PRE3D_Wr04(_r, _lname,0, _rwname,0, _iname,_ival, _fname,_fval)


#define PRE3D_Ridx(_r, _ival, _fname, _fval)	PRE3D_Rind(_r,load,rw,index,_ival,_fname,_fval)

#define PRE3D_Widx(_r, _ival, _fname, _fval)	PRE3D_Wind(_r,load,rw,index,_ival,_fname,_fval)

/* from 'LGDT1150_DE_Pre3D v1.0.csv' 20100311 00:54:21   대한민국 표준시 by getregs v2.3 */
