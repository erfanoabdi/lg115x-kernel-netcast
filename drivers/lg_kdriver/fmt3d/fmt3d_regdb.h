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
const DBG_REG_FIELD_T dbg_REG_IN_IMG_SIZE[] = {                  /* 0x0000 */
	{ REG_XS_N_RW,  0, 0,  0, 0, 10, 0, "in_img_width"                    },
	{ REG_XS_N_RW,  0, 0,  0, 0, 26,16, "in_img_height"                   },
};

/*-----------------------------------------------------------------------------
	0x0004 reg_in_img_format ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_IN_IMG_FORMAT[] = {                /* 0x0004 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  2, 0, "in_image_format"                 },
	{ REG_XS_N_RW,  0, 0,  0, 0,  5, 4, "color_format"                    },
	{ REG_XS_N_RW,  0, 0,  0, 0,  8, 8, "lr_in_order"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0, 13,13, "progressive"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0, 14,14, "double_pic"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 15,15, "in_bit_res"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 16,16, "sample_mode"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0, 18,17, "sample_comb"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0, 20,20, "spatial_flip"                    },
	{ REG_XS_N_RW,  0, 0,  0, 0, 21,21, "tl_frame_flip"                   },
};

/*-----------------------------------------------------------------------------
	0x0008 reg_proc_mode ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PROC_MODE[] = {                    /* 0x0008 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  0, 0, "pre3d_src_mux"                   },
	{ REG_XS_N_RW,  0, 0,  0, 0,  5, 4, "pre3d_run_mode"                  },
	{ REG_XS_N_RW,  0, 0,  0, 0,  8, 8, "display_format"                  },
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 9, "display_freq"                    },
	{ REG_XS_N_RW,  0, 0,  0, 0, 10,10, "lr_out_order"                    },
	{ REG_XS_N_RW,  0, 0,  0, 0, 24,16, "convergence"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0, 28,28, "convergence_mode"                },
};

/*-----------------------------------------------------------------------------
	0x000c reg_pre3d_scaler ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PRE3D_SCALER[] = {                 /* 0x000c */
	{ REG_XS_N_RW,  0, 0,  0, 0,  1, 0, "scl_filter_sum"                  },
	{ REG_XS_N_RW,  0, 0,  0, 0,  2, 2, "scl_vsc_mode"                    },
	{ REG_XS_N_RW,  0, 0,  0, 0,  3, 3, "scl_adaptive_on"                 },
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 8, "scl_th0"                         },
	{ REG_XS_N_RW,  0, 0,  0, 0, 11,10, "scl_th1"                         },
	{ REG_XS_N_RW,  0, 0,  0, 0, 13,12, "scl_th2"                         },
	{ REG_XS_N_RW,  0, 0,  0, 0, 15,14, "scl_th3"                         },
};

/*-----------------------------------------------------------------------------
	0x0010 reg_phase_ctrl ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PHASE_CTRL[] = {                   /* 0x0010 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  5, 0, "phase_addr"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0,  8, 8, "phase_sel"                       },
	{ REG_XS_N_RW,  0, 0,  0, 0, 12,12, "phase_rnw"                       },
};

/*-----------------------------------------------------------------------------
	0x0014 reg_phasewd0 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PHASEWD0[] = {                     /* 0x0014 */
	{ REG_XS_N_RW,  0, 0,  0, 0, 11, 0, "scl_coeff0"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 27,16, "scl_coeff1"                      },
};

/*-----------------------------------------------------------------------------
	0x0018 reg_phasewd1 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PHASEWD1[] = {                     /* 0x0018 */
	{ REG_XS_N_RW,  0, 0,  0, 0, 11, 0, "scl_coeff2"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 27,16, "scl_coeff3"                      },
};

/*-----------------------------------------------------------------------------
	0x001c reg_phasewd2 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PHASEWD2[] = {                     /* 0x001c */
	{ REG_XS_N_RW,  0, 0,  0, 0, 11, 0, "scl_coeff4"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 27,16, "scl_coeff5"                      },
};

/*-----------------------------------------------------------------------------
	0x0020 reg_phasewd3 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PHASEWD3[] = {                     /* 0x0020 */
	{ REG_XS_N_RW,  0, 0,  0, 0, 11, 0, "scl_coeff6"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 27,16, "scl_coeff7"                      },
};

/*-----------------------------------------------------------------------------
	0x0024 reg_phasewd4 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PHASEWD4[] = {                     /* 0x0024 */
	{ REG_XS_N_RW,  0, 0,  0, 0, 11, 0, "scl_coeff8"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 27,16, "scl_coeff9"                      },
};

/*-----------------------------------------------------------------------------
	0x0028 reg_phasewd5 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PHASEWD5[] = {                     /* 0x0028 */
	{ REG_XS_N_RW,  0, 0,  0, 0, 11, 0, "scl_coeff10"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0, 27,16, "scl_coeff11"                     },
};

/*-----------------------------------------------------------------------------
	0x002c reg_quincunx_coeff0 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_QUINCUNX_COEFF0[] = {              /* 0x002c */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "qx0_coeff0"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 19,10, "qx0_coeff1"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29,20, "qx0_coeff2"                      },
};

/*-----------------------------------------------------------------------------
	0x0030 reg_quincunx_coeff1 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_QUINCUNX_COEFF1[] = {              /* 0x0030 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "qx0_coeff3"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 19,10, "qx0_coeff4"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29,20, "qx0_coeff5"                      },
};

/*-----------------------------------------------------------------------------
	0x0034 reg_quincunx_coeff2 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_QUINCUNX_COEFF2[] = {              /* 0x0034 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "qx0_coeff6"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 19,10, "qx0_coeff7"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29,20, "qx0_coeff8"                      },
};

/*-----------------------------------------------------------------------------
	0x0038 reg_quincunx_coeff3 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_QUINCUNX_COEFF3[] = {              /* 0x0038 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "qx0_coeff9"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 19,10, "qx0_coeff10"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29,20, "qx1_coeff0"                      },
};

/*-----------------------------------------------------------------------------
	0x003c reg_quincunx_coeff4 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_QUINCUNX_COEFF4[] = {              /* 0x003c */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "qx1_coeff1"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 19,10, "qx1_coeff2"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29,20, "qx1_coeff3"                      },
};

/*-----------------------------------------------------------------------------
	0x0040 reg_quincunx_coeff5 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_QUINCUNX_COEFF5[] = {              /* 0x0040 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "qx1_coeff4"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 19,10, "qx1_coeff5"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29,20, "qx1_coeff6"                      },
};

/*-----------------------------------------------------------------------------
	0x0044 reg_quincunx_coeff6 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_QUINCUNX_COEFF6[] = {              /* 0x0044 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "qx1_coeff7"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 19,10, "qx1_coeff8"                      },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29,20, "qx1_coeff9"                      },
};

/*-----------------------------------------------------------------------------
	0x0048 reg_3d_status ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_3D_STATUS[] = {                    /* 0x0048 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  3, 0, "pre3d_status"                    },
	{ REG_XS_N_RW,  0, 0,  0, 0, 18, 8, "line_luma"                       },
	{ REG_XS_N_RW,  0, 0,  0, 0, 30,20, "line_chroma"                     },
};

/*-----------------------------------------------------------------------------
	0x004c reg_pre3d_out_img_info ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PRE3D_OUT_IMG_INFO[] = {           /* 0x004c */
	{ REG_XS_N_RW,  0, 0,  0, 0,  2, 0, "out_img_format"                  },
	{ REG_XS_N_RW,  0, 0,  0, 0, 18, 8, "out_img_width"                   },
	{ REG_XS_N_RW,  0, 0,  0, 0, 30,20, "out_img_height"                  },
};

/*-----------------------------------------------------------------------------
	0x0050 reg_frame_field_info ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_FRAME_FIELD_INFO[] = {             /* 0x0050 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  0, 0, "lr_frame_id"                     },
	{ REG_XS_N_RW,  0, 0,  0, 0,  8, 8, "field_id"                        },
};

/*-----------------------------------------------------------------------------
	0x0054 reg_pdp_sp_ctrl0 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PDP_SP_CTRL0[] = {                 /* 0x0054 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  0, 0, "pdp_sp_enable"                   },
	{ REG_XS_N_RW,  0, 0,  0, 0,  1, 1, "pdp_sp_mot_sel"                  },
	{ REG_XS_N_RW,  0, 0,  0, 0, 11, 8, "pdp_sp_max_offset"               },
	{ REG_XS_N_RW,  0, 0,  0, 0, 15,12, "pdp_sp_mot_pe0_cut"              },
	{ REG_XS_N_RW,  0, 0,  0, 0, 31,16, "pdp_sp_fr_period"                },
};

/*-----------------------------------------------------------------------------
	0x0058 reg_pdp_sp_ctrl1 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PDP_SP_CTRL1[] = {                 /* 0x0058 */
	{ REG_XS_N_RW,  0, 0,  0, 0, 15, 0, "pdp_sp_still_cnt"                },
	{ REG_XS_N_RW,  0, 0,  0, 0, 23,16, "pdp_sp_mot_th"                   },
	{ REG_XS_N_RW,  0, 0,  0, 0, 31,24, "pdp_sp_mot_iir"                  },
};

/*-----------------------------------------------------------------------------
	0x005c reg_pdp_sp_ctrl2 ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_PDP_SP_CTRL2[] = {                 /* 0x005c */
	{ REG_XS_N_RW,  0, 0,  0, 0,  7, 0, "pdp_sp_mot_mcu"                  },
	{ REG_XS_N_RW,  0, 0,  0, 0, 29, 8, "pdp_sp_mot_pe0"                  },
	{ REG_XS_N_RW,  0, 0,  0, 0, 31,30, "pdp_sp_shift_inc"                },
};

/*-----------------------------------------------------------------------------
	0x0060 reg_crop_size ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_CROP_SIZE[] = {                    /* 0x0060 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  9, 0, "hor_crop_size"                   },
};

/*-----------------------------------------------------------------------------
	0x0064 reg_convergence_range ''
------------------------------------------------------------------------------*/
const DBG_REG_FIELD_T dbg_REG_CONVERGENCE_RANGE[] = {            /* 0x0064 */
	{ REG_XS_N_RW,  0, 0,  0, 0,  8, 0, "conv_min"                        },
	{ REG_XS_N_RW,  0, 0,  0, 0, 24,16, "conv_max"                        },
};

DBG_REG_T gDbgRegFMT3D[] = {
	{0x0200,N_FLD(dbg_REG_IN_IMG_SIZE),                 "REG_IN_IMG_SIZE"                 ,dbg_REG_IN_IMG_SIZE                 }, //
	{0x0204,N_FLD(dbg_REG_IN_IMG_FORMAT),               "REG_IN_IMG_FORMAT"               ,dbg_REG_IN_IMG_FORMAT               }, //
	{0x0208,N_FLD(dbg_REG_PROC_MODE),                   "REG_PROC_MODE"                   ,dbg_REG_PROC_MODE                   }, //
	{0x020c,N_FLD(dbg_REG_PRE3D_SCALER),                "REG_PRE3D_SCALER"                ,dbg_REG_PRE3D_SCALER                }, //
	{0x0210,N_FLD(dbg_REG_PHASE_CTRL),                  "REG_PHASE_CTRL"                  ,dbg_REG_PHASE_CTRL                  }, //
	{0x0214,N_FLD(dbg_REG_PHASEWD0),                    "REG_PHASEWD0"                    ,dbg_REG_PHASEWD0                    }, //
	{0x0218,N_FLD(dbg_REG_PHASEWD1),                    "REG_PHASEWD1"                    ,dbg_REG_PHASEWD1                    }, //
	{0x021c,N_FLD(dbg_REG_PHASEWD2),                    "REG_PHASEWD2"                    ,dbg_REG_PHASEWD2                    }, //
	{0x0220,N_FLD(dbg_REG_PHASEWD3),                    "REG_PHASEWD3"                    ,dbg_REG_PHASEWD3                    }, //
	{0x0224,N_FLD(dbg_REG_PHASEWD4),                    "REG_PHASEWD4"                    ,dbg_REG_PHASEWD4                    }, //
	{0x0228,N_FLD(dbg_REG_PHASEWD5),                    "REG_PHASEWD5"                    ,dbg_REG_PHASEWD5                    }, //
	{0x022c,N_FLD(dbg_REG_QUINCUNX_COEFF0),             "REG_QUINCUNX_COEFF0"             ,dbg_REG_QUINCUNX_COEFF0             }, //
	{0x0230,N_FLD(dbg_REG_QUINCUNX_COEFF1),             "REG_QUINCUNX_COEFF1"             ,dbg_REG_QUINCUNX_COEFF1             }, //
	{0x0234,N_FLD(dbg_REG_QUINCUNX_COEFF2),             "REG_QUINCUNX_COEFF2"             ,dbg_REG_QUINCUNX_COEFF2             }, //
	{0x0238,N_FLD(dbg_REG_QUINCUNX_COEFF3),             "REG_QUINCUNX_COEFF3"             ,dbg_REG_QUINCUNX_COEFF3             }, //
	{0x023c,N_FLD(dbg_REG_QUINCUNX_COEFF4),             "REG_QUINCUNX_COEFF4"             ,dbg_REG_QUINCUNX_COEFF4             }, //
	{0x0240,N_FLD(dbg_REG_QUINCUNX_COEFF5),             "REG_QUINCUNX_COEFF5"             ,dbg_REG_QUINCUNX_COEFF5             }, //
	{0x0244,N_FLD(dbg_REG_QUINCUNX_COEFF6),             "REG_QUINCUNX_COEFF6"             ,dbg_REG_QUINCUNX_COEFF6             }, //
	{0x0248,N_FLD(dbg_REG_3D_STATUS),                   "REG_3D_STATUS"                   ,dbg_REG_3D_STATUS                   }, //
	{0x024c,N_FLD(dbg_REG_PRE3D_OUT_IMG_INFO),          "REG_PRE3D_OUT_IMG_INFO"          ,dbg_REG_PRE3D_OUT_IMG_INFO          }, //
	{0x0250,N_FLD(dbg_REG_FRAME_FIELD_INFO),            "REG_FRAME_FIELD_INFO"            ,dbg_REG_FRAME_FIELD_INFO            }, //
	{0x0254,N_FLD(dbg_REG_PDP_SP_CTRL0),                "REG_PDP_SP_CTRL0"                ,dbg_REG_PDP_SP_CTRL0                }, //
	{0x0258,N_FLD(dbg_REG_PDP_SP_CTRL1),                "REG_PDP_SP_CTRL1"                ,dbg_REG_PDP_SP_CTRL1                }, //
	{0x025c,N_FLD(dbg_REG_PDP_SP_CTRL2),                "REG_PDP_SP_CTRL2"                ,dbg_REG_PDP_SP_CTRL2                }, //
	{0x0260,N_FLD(dbg_REG_CROP_SIZE),                   "REG_CROP_SIZE"                   ,dbg_REG_CROP_SIZE                   }, //
	{0x0264,N_FLD(dbg_REG_CONVERGENCE_RANGE),           "REG_CONVERGENCE_RANGE"           ,dbg_REG_CONVERGENCE_RANGE           }, //
};

/* 26 regs, 26 types in Total*/

/* from 'LGDT1150_DE_Pre3D v1.0.csv' 20100311 00:54:21   대한민국 표준시 by getregs v2.3 */
