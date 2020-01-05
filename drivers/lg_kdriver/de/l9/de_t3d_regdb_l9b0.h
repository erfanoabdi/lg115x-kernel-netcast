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

#ifndef _DBG_T3D_h
#define _DBG_T3D_h

/*--------------------------------
	0x1900 SOFT_RESET
--------------------------------*/
const DBG_REG_FIELD_T dbg_SOFT_RESET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"soft_reset"              },
};

/*--------------------------------
	0x1904 T3_CTRL
--------------------------------*/
const DBG_REG_FIELD_T dbg_T3_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"t3_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"t3_bypass_mode"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"t3_format_mode"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"t3_color"                },
};

/*--------------------------------
	0x1908 T3_INOUT_SIZE
--------------------------------*/
const DBG_REG_FIELD_T dbg_T3_INOUT_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"t3_height"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"t3_width"                },
};

/*--------------------------------
	0x190c T3_DEPTH_CTRL0
--------------------------------*/
const DBG_REG_FIELD_T dbg_T3_DEPTH_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"exp_disp_max"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"exp_disp_min"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"obj_depth_scale"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"depth_scale"             },
};

/*--------------------------------
	0x1910 T3_DEPTH_CTRL1
--------------------------------*/
const DBG_REG_FIELD_T dbg_T3_DEPTH_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"crop_size"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"convergence"             },
};

/*--------------------------------
	0x1914 T3_MUL_FACTOR
--------------------------------*/
const DBG_REG_FIELD_T dbg_T3_MUL_FACTOR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"mul_factor"              },
};

/*--------------------------------
	0x1930 INP_DEC_V
--------------------------------*/
const DBG_REG_FIELD_T dbg_INP_DEC_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"dec_v_filter3"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"dec_v_filter2_"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"dec_v_filter1_"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,24 ,"dec_v_filter0_"          },
};

/*--------------------------------
	0x1934 INP_DEC_H
--------------------------------*/
const DBG_REG_FIELD_T dbg_INP_DEC_H[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"dec_h_filter3"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"dec_h_filter2_"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"dec_h_filter1_"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,24 ,"dec_h_filter0_"          },
};

/*--------------------------------
	0x1938 CSC_RGB2Y_COEF0
--------------------------------*/
const DBG_REG_FIELD_T dbg_CSC_RGB2Y_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"inp_csc_y_g"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"inp_csc_y_r"             },
};

/*--------------------------------
	0x193c CSC_RGB2Y_COEF1
--------------------------------*/
const DBG_REG_FIELD_T dbg_CSC_RGB2Y_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"inp_csc_y_b"             },
};

/*--------------------------------
	0x1940 CSC_RGB2CB_COEF
--------------------------------*/
const DBG_REG_FIELD_T dbg_CSC_RGB2CB_COEF[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"inp_csc_cb_g"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"inp_csc_cb_r"            },
};

/*--------------------------------
	0x1944 CSC_RGB2CR_COEF
--------------------------------*/
const DBG_REG_FIELD_T dbg_CSC_RGB2CR_COEF[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"inp_csc_cr_b"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"inp_csc_cr_g"            },
};

/*--------------------------------
	0x1950 SEG_COL_PARAM0
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_COL_PARAM0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_col_param_2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"seg_col_param_1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"seg_col_param_0"         },
};

/*--------------------------------
	0x1954 SEG_COL_PARAM1
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_COL_PARAM1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_col_param_6"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"seg_col_param_5"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"seg_col_param_4"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"seg_col_param_3"         },
};

/*--------------------------------
	0x1958 SEG_COL_PARAM2
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_COL_PARAM2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_col_param_10"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"seg_col_param_9"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"seg_col_param_8"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"seg_col_param_7"         },
};

/*--------------------------------
	0x195c SEG_COL_PARAM3
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_COL_PARAM3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_col_param_14"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"seg_col_param_13"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"seg_col_param_12"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"seg_col_param_11"        },
};

/*--------------------------------
	0x1960 SEG_OBJ0
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_OBJ0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_ftr_param_3"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"seg_ftr_param_2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"seg_ftr_param_1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"seg_ftr_param_0"         },
};

/*--------------------------------
	0x1964 SEG_OBJ1
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_OBJ1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_ftr_param_7"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"seg_ftr_param_6"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"seg_ftr_param_5"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"seg_ftr_param_4"         },
};

/*--------------------------------
	0x1968 SEG_OBJ2_0
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_OBJ2_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_ftr_param_11"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"seg_ftr_param_10"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"seg_ftr_param_9"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"seg_ftr_param_8"         },
};

/*--------------------------------
	0x196c SEG_OBJ2_1
--------------------------------*/
const DBG_REG_FIELD_T dbg_SEG_OBJ2_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"seg_ftr_param_12"        },
};

/*--------------------------------
	0x1970 EGA_MASK_TH
--------------------------------*/
const DBG_REG_FIELD_T dbg_EGA_MASK_TH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mask_threshold1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mask_threshold0"         },
};

/*--------------------------------
	0x1974 SMD_OFFSET0
--------------------------------*/
const DBG_REG_FIELD_T dbg_SMD_OFFSET0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,0  ,"y0_offset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,16 ,"x0_offset"               },
};

/*--------------------------------
	0x1978 SMD_OFFSET1
--------------------------------*/
const DBG_REG_FIELD_T dbg_SMD_OFFSET1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,0  ,"y1_offset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,16 ,"x1_offset"               },
};

/*--------------------------------
	0x197c SMD_HISTOGRAM
--------------------------------*/
const DBG_REG_FIELD_T dbg_SMD_HISTOGRAM[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,0  ,"histogram_step"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"histogram_block"         },
};

/*--------------------------------
	0x1980 SMD_EDGE_TH
--------------------------------*/
const DBG_REG_FIELD_T dbg_SMD_EDGE_TH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"edge_threshold"          },
};

/*--------------------------------
	0x1984 SMD_BLK_TH
--------------------------------*/
const DBG_REG_FIELD_T dbg_SMD_BLK_TH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"min_blk_threshold"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"gen_blk_threshold"       },
};

/*--------------------------------
	0x1988 BGD_PARAM0
--------------------------------*/
const DBG_REG_FIELD_T dbg_BGD_PARAM0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"flat_dominant_seg"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"obj_eg_in_frm"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"obj_flat_in_frm"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"flat_in_blk"             },
};

/*--------------------------------
	0x198c BGD_PARAM1
--------------------------------*/
const DBG_REG_FIELD_T dbg_BGD_PARAM1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"local_flat_flag"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"obj0_detect_mode"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"f_flat_in_blk_flat"      },
};

/*--------------------------------
	0x1990 BLACK_CTRL
--------------------------------*/
const DBG_REG_FIELD_T dbg_BLACK_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bg_h_blk_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"bg_v_blk_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"black_bar_th"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"black_x_offset"          },
};

/*--------------------------------
	0x1994 ODG_COLOR_TH
--------------------------------*/
const DBG_REG_FIELD_T dbg_ODG_COLOR_TH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"color_th_h"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"color_th_m"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"color_th_l"              },
};

/*--------------------------------
	0x1998 ODG_MONO_RANGE
--------------------------------*/
const DBG_REG_FIELD_T dbg_ODG_MONO_RANGE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"mono_range_h"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"mono_range_l"            },
};

/*--------------------------------
	0x199c ODG_CTRL0
--------------------------------*/
const DBG_REG_FIELD_T dbg_ODG_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"obj0_factor"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"bg_factor1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"bg_factor0"              },
};

/*--------------------------------
	0x19a0 ODG_CTRL1
--------------------------------*/
const DBG_REG_FIELD_T dbg_ODG_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"edge_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"edge_scale"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"offset_minus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"edge_factor"             },
};

/*--------------------------------
	0x19a4 OBJ0_SCN_SLOPE
--------------------------------*/
const DBG_REG_FIELD_T dbg_OBJ0_SCN_SLOPE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"obj0_scn_slope"          },
};

/*--------------------------------
	0x19a8 SCD_CTRL
--------------------------------*/
const DBG_REG_FIELD_T dbg_SCD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"scene_change_threshold"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"scene_change_size"       },
};

/*--------------------------------
	0x19ac INT_Q_PEL_COEF0
--------------------------------*/
const DBG_REG_FIELD_T dbg_INT_Q_PEL_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"q_pel_coef1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"q_pel_coef0"             },
};

/*--------------------------------
	0x19b0 INT_Q_PEL_COEF1
--------------------------------*/
const DBG_REG_FIELD_T dbg_INT_Q_PEL_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"q_pel_coef3"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"q_pel_coef2"             },
};

/*--------------------------------
	0x19b4 INT_H_PEL_COEF0
--------------------------------*/
const DBG_REG_FIELD_T dbg_INT_H_PEL_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"h_pel_coef1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"h_pel_coef0"             },
};

/*--------------------------------
	0x19b8 INT_H_PEL_COEF1
--------------------------------*/
const DBG_REG_FIELD_T dbg_INT_H_PEL_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"h_pel_coef3"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"h_pel_coef2"             },
};

/*--------------------------------
	0x19bc SCG_CTRL
--------------------------------*/
const DBG_REG_FIELD_T dbg_SCG_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"sm_buffer_size"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"depth_resolution"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"angle"                   },
};

/*--------------------------------
	0x19c0 SDG_ADDR
--------------------------------*/
const DBG_REG_FIELD_T dbg_SDG_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"sdg_addr"                },
};

/*--------------------------------
	0x19c4 SDG_DATA
--------------------------------*/
const DBG_REG_FIELD_T dbg_SDG_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"sdg_data"                },
};

/*--------------------------------
	0x19c8 VSYN_HSC_COEF0
--------------------------------*/
const DBG_REG_FIELD_T dbg_VSYN_HSC_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsc_coef1"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hsc_coef0"               },
};

/*--------------------------------
	0x19cc VSYN_HSC_COEF1
--------------------------------*/
const DBG_REG_FIELD_T dbg_VSYN_HSC_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsc_coef3"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hsc_coef2"               },
};

/*--------------------------------
	0x19d0 VSYN_HSC_COEF2
--------------------------------*/
const DBG_REG_FIELD_T dbg_VSYN_HSC_COEF2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsc_coef5"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hsc_coef4"               },
};

/*--------------------------------
	0x19d4 VSYN_HSC_COEF3
--------------------------------*/
const DBG_REG_FIELD_T dbg_VSYN_HSC_COEF3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsc_coef7"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hsc_coef6"               },
};

/*--------------------------------
	0x1a00 YC2RGB_COEF0
--------------------------------*/
const DBG_REG_FIELD_T dbg_YC2RGB_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"cb2r"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"y2r"                     },
};

/*--------------------------------
	0x1a04 YC2RGB_COEF1
--------------------------------*/
const DBG_REG_FIELD_T dbg_YC2RGB_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"y2g"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"cr2r"                    },
};

/*--------------------------------
	0x1a08 YC2RGB_COEF2
--------------------------------*/
const DBG_REG_FIELD_T dbg_YC2RGB_COEF2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"cr2g"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"cb2g"                    },
};

/*--------------------------------
	0x1a0c YC2RGB_COEF3
--------------------------------*/
const DBG_REG_FIELD_T dbg_YC2RGB_COEF3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"cb2b"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"y2b"                     },
};

/*--------------------------------
	0x1a10 YC2RGB_COEF4
--------------------------------*/
const DBG_REG_FIELD_T dbg_YC2RGB_COEF4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"cr2b"                    },
};

/*--------------------------------
	0x1a20 T3_PROC_Y0
--------------------------------*/
const DBG_REG_FIELD_T dbg_T3_PROC_Y0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"t3_vana_proc_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"t3_inp_proc_y"           },
};

/*--------------------------------
	0x1a24 T3_PROC_Y1
--------------------------------*/
const DBG_REG_FIELD_T dbg_T3_PROC_Y1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"t3_vsyn_proc_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"t3_dgen_proc_y"          },
};

DBG_REG_T gDbgRegT3D[] = {
	{ 0x1900 ,N_FLD(dbg_SOFT_RESET)          ,"SOFT_RESET"            ,dbg_SOFT_RESET          },
	{ 0x1904 ,N_FLD(dbg_T3_CTRL)             ,"T3_CTRL"               ,dbg_T3_CTRL             },
	{ 0x1908 ,N_FLD(dbg_T3_INOUT_SIZE)       ,"T3_INOUT_SIZE"         ,dbg_T3_INOUT_SIZE       },
	{ 0x190c ,N_FLD(dbg_T3_DEPTH_CTRL0)      ,"T3_DEPTH_CTRL0"        ,dbg_T3_DEPTH_CTRL0      },
	{ 0x1910 ,N_FLD(dbg_T3_DEPTH_CTRL1)      ,"T3_DEPTH_CTRL1"        ,dbg_T3_DEPTH_CTRL1      },
	{ 0x1914 ,N_FLD(dbg_T3_MUL_FACTOR)       ,"T3_MUL_FACTOR"         ,dbg_T3_MUL_FACTOR       },
	{ 0x1930 ,N_FLD(dbg_INP_DEC_V)           ,"INP_DEC_V"             ,dbg_INP_DEC_V           },
	{ 0x1934 ,N_FLD(dbg_INP_DEC_H)           ,"INP_DEC_H"             ,dbg_INP_DEC_H           },
	{ 0x1938 ,N_FLD(dbg_CSC_RGB2Y_COEF0)     ,"CSC_RGB2Y_COEF0"       ,dbg_CSC_RGB2Y_COEF0     },
	{ 0x193c ,N_FLD(dbg_CSC_RGB2Y_COEF1)     ,"CSC_RGB2Y_COEF1"       ,dbg_CSC_RGB2Y_COEF1     },
	{ 0x1940 ,N_FLD(dbg_CSC_RGB2CB_COEF)     ,"CSC_RGB2CB_COEF"       ,dbg_CSC_RGB2CB_COEF     },
	{ 0x1944 ,N_FLD(dbg_CSC_RGB2CR_COEF)     ,"CSC_RGB2CR_COEF"       ,dbg_CSC_RGB2CR_COEF     },
	{ 0x1950 ,N_FLD(dbg_SEG_COL_PARAM0)      ,"SEG_COL_PARAM0"        ,dbg_SEG_COL_PARAM0      },
	{ 0x1954 ,N_FLD(dbg_SEG_COL_PARAM1)      ,"SEG_COL_PARAM1"        ,dbg_SEG_COL_PARAM1      },
	{ 0x1958 ,N_FLD(dbg_SEG_COL_PARAM2)      ,"SEG_COL_PARAM2"        ,dbg_SEG_COL_PARAM2      },
	{ 0x195c ,N_FLD(dbg_SEG_COL_PARAM3)      ,"SEG_COL_PARAM3"        ,dbg_SEG_COL_PARAM3      },
	{ 0x1960 ,N_FLD(dbg_SEG_OBJ0)            ,"SEG_OBJ0"              ,dbg_SEG_OBJ0            },
	{ 0x1964 ,N_FLD(dbg_SEG_OBJ1)            ,"SEG_OBJ1"              ,dbg_SEG_OBJ1            },
	{ 0x1968 ,N_FLD(dbg_SEG_OBJ2_0)          ,"SEG_OBJ2_0"            ,dbg_SEG_OBJ2_0          },
	{ 0x196c ,N_FLD(dbg_SEG_OBJ2_1)          ,"SEG_OBJ2_1"            ,dbg_SEG_OBJ2_1          },
	{ 0x1970 ,N_FLD(dbg_EGA_MASK_TH)         ,"EGA_MASK_TH"           ,dbg_EGA_MASK_TH         },
	{ 0x1974 ,N_FLD(dbg_SMD_OFFSET0)         ,"SMD_OFFSET0"           ,dbg_SMD_OFFSET0         },
	{ 0x1978 ,N_FLD(dbg_SMD_OFFSET1)         ,"SMD_OFFSET1"           ,dbg_SMD_OFFSET1         },
	{ 0x197c ,N_FLD(dbg_SMD_HISTOGRAM)       ,"SMD_HISTOGRAM"         ,dbg_SMD_HISTOGRAM       },
	{ 0x1980 ,N_FLD(dbg_SMD_EDGE_TH)         ,"SMD_EDGE_TH"           ,dbg_SMD_EDGE_TH         },
	{ 0x1984 ,N_FLD(dbg_SMD_BLK_TH)          ,"SMD_BLK_TH"            ,dbg_SMD_BLK_TH          },
	{ 0x1988 ,N_FLD(dbg_BGD_PARAM0)          ,"BGD_PARAM0"            ,dbg_BGD_PARAM0          },
	{ 0x198c ,N_FLD(dbg_BGD_PARAM1)          ,"BGD_PARAM1"            ,dbg_BGD_PARAM1          },
	{ 0x1990 ,N_FLD(dbg_BLACK_CTRL)          ,"BLACK_CTRL"            ,dbg_BLACK_CTRL          },
	{ 0x1994 ,N_FLD(dbg_ODG_COLOR_TH)        ,"ODG_COLOR_TH"          ,dbg_ODG_COLOR_TH        },
	{ 0x1998 ,N_FLD(dbg_ODG_MONO_RANGE)      ,"ODG_MONO_RANGE"        ,dbg_ODG_MONO_RANGE      },
	{ 0x199c ,N_FLD(dbg_ODG_CTRL0)           ,"ODG_CTRL0"             ,dbg_ODG_CTRL0           },
	{ 0x19a0 ,N_FLD(dbg_ODG_CTRL1)           ,"ODG_CTRL1"             ,dbg_ODG_CTRL1           },
	{ 0x19a4 ,N_FLD(dbg_OBJ0_SCN_SLOPE)      ,"OBJ0_SCN_SLOPE"        ,dbg_OBJ0_SCN_SLOPE      },
	{ 0x19a8 ,N_FLD(dbg_SCD_CTRL)            ,"SCD_CTRL"              ,dbg_SCD_CTRL            },
	{ 0x19ac ,N_FLD(dbg_INT_Q_PEL_COEF0)     ,"INT_Q_PEL_COEF0"       ,dbg_INT_Q_PEL_COEF0     },
	{ 0x19b0 ,N_FLD(dbg_INT_Q_PEL_COEF1)     ,"INT_Q_PEL_COEF1"       ,dbg_INT_Q_PEL_COEF1     },
	{ 0x19b4 ,N_FLD(dbg_INT_H_PEL_COEF0)     ,"INT_H_PEL_COEF0"       ,dbg_INT_H_PEL_COEF0     },
	{ 0x19b8 ,N_FLD(dbg_INT_H_PEL_COEF1)     ,"INT_H_PEL_COEF1"       ,dbg_INT_H_PEL_COEF1     },
	{ 0x19bc ,N_FLD(dbg_SCG_CTRL)            ,"SCG_CTRL"              ,dbg_SCG_CTRL            },
	{ 0x19c0 ,N_FLD(dbg_SDG_ADDR)            ,"SDG_ADDR"              ,dbg_SDG_ADDR            },
	{ 0x19c4 ,N_FLD(dbg_SDG_DATA)            ,"SDG_DATA"              ,dbg_SDG_DATA            },
	{ 0x19c8 ,N_FLD(dbg_VSYN_HSC_COEF0)      ,"VSYN_HSC_COEF0"        ,dbg_VSYN_HSC_COEF0      },
	{ 0x19cc ,N_FLD(dbg_VSYN_HSC_COEF1)      ,"VSYN_HSC_COEF1"        ,dbg_VSYN_HSC_COEF1      },
	{ 0x19d0 ,N_FLD(dbg_VSYN_HSC_COEF2)      ,"VSYN_HSC_COEF2"        ,dbg_VSYN_HSC_COEF2      },
	{ 0x19d4 ,N_FLD(dbg_VSYN_HSC_COEF3)      ,"VSYN_HSC_COEF3"        ,dbg_VSYN_HSC_COEF3      },
	{ 0x1a00 ,N_FLD(dbg_YC2RGB_COEF0)        ,"YC2RGB_COEF0"          ,dbg_YC2RGB_COEF0        },
	{ 0x1a04 ,N_FLD(dbg_YC2RGB_COEF1)        ,"YC2RGB_COEF1"          ,dbg_YC2RGB_COEF1        },
	{ 0x1a08 ,N_FLD(dbg_YC2RGB_COEF2)        ,"YC2RGB_COEF2"          ,dbg_YC2RGB_COEF2        },
	{ 0x1a0c ,N_FLD(dbg_YC2RGB_COEF3)        ,"YC2RGB_COEF3"          ,dbg_YC2RGB_COEF3        },
	{ 0x1a10 ,N_FLD(dbg_YC2RGB_COEF4)        ,"YC2RGB_COEF4"          ,dbg_YC2RGB_COEF4        },
	{ 0x1a20 ,N_FLD(dbg_T3_PROC_Y0)          ,"T3_PROC_Y0"            ,dbg_T3_PROC_Y0          },
	{ 0x1a24 ,N_FLD(dbg_T3_PROC_Y1)          ,"T3_PROC_Y1"            ,dbg_T3_PROC_Y1          },
	{ 0 , } // end marker
};

#endif
