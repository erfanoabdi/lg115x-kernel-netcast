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

#ifndef _DBG_WCP_h
#define _DBG_WCP_h

/*------------------------------------
	0x1200 OVL_OV_CTRL0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_OV_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"main_444"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"main_420"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"main_lsr_2b"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"main_cflt_mode"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"sub_444"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"sub_420"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"sub_lsr_2b"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,14 ,"sub_cflt_mode"           },
};

/*------------------------------------
	0x1204 OV_CTRL1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"border_color_cr"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"border_color_cb"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"border_color_yy"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_type"               },
};

/*------------------------------------
	0x1208 OV_CTRL2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"back_color_cr"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"back_color_cb"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"back_color_yy"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"dark_color_cr"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"dark_color_cb"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dark_color_yy"           },
};

/*------------------------------------
	0x120c OV_CTRL3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_CTRL3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"w0_blending_alpha"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"w1_blending_alpha"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"w2_blending_alpha"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"w0_blending_mode"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"w1_blending_mode"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"w2_blending_mode"        },
};

/*------------------------------------
	0x1210 OVL_OV_MOFFSET
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_OV_MOFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"m_hoffset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"m_voffset"               },
};

/*------------------------------------
	0x1214 OVL_OV_MSIZE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_OV_MSIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"m_hsize"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"m_vsize"                 },
};

/*------------------------------------
	0x1218 OV_SOFFSET
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_SOFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"s_hoffset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"s_voffset"               },
};

/*------------------------------------
	0x121c OV_SSIZE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_SSIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"s_hsize"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"s_vsize"                 },
};

/*------------------------------------
	0x1220 OVL_OV_BORDER_WIDTH
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_OV_BORDER_WIDTH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"s_right_wid"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"s_left_wid"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"s_down_wid"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"s_up_wid"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"m_right_wid"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"m_left_wid"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"m_down_wid"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"m_up_wid"                },
};

/*------------------------------------
	0x1224 OVL_CFLT_COEF0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_CFLT_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cflt_coef_1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"cflt_coef_0"             },
};

/*------------------------------------
	0x1228 OVL_CFLT_COEF1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_CFLT_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cflt_coef_3"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"cflt_coef_2"             },
};

/*------------------------------------
	0x1230 OVL_OV_PARAM_BY_DDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_OV_PARAM_BY_DDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"stride"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vsize"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"endian_conversion"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"update_by_ddr"           },
};

/*------------------------------------
	0x1240 OVL_OV_INTR_CTRL
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_OV_INTR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"intr_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"intr_line_pos_enable"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"intr_sbuf_c_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"intr_sbuf_y_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"intr_mbuf_c_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"intr_mbuf_y_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"intr_pdb_end_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"line_position"           },
};

/*------------------------------------
	0x1244 OVL_OV_INTR_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVL_OV_INTR_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"sbuf_c_empty"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"sbuf_y_empty"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"mbuf_c_empty"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"mbuf_y_empty"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"line_cnt"                },
};

/*------------------------------------
	0x1248 OV_CTRL4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_CTRL4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"w0_imux_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"w0_dark_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"w1_imux_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"w1_dark_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"w2_imux_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"w2_dark_en"              },
};

/*------------------------------------
	0x124c OV_CTRL5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_CTRL5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pxl_alpha_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pxl_alpha_reverse"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"pxl_alpha_clip_mode"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ckey_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"ckey_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pxl_yy_reverse"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pxl_cc_reverse"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ckey_th_yy1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ckey_th_yy0"             },
};

/*------------------------------------
	0x1250 OV_CTRL6
------------------------------------*/
const DBG_REG_FIELD_T dbg_OV_CTRL6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ckey_th_cr1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ckey_th_cr0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ckey_th_cb1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ckey_th_cb0"             },
};

/*------------------------------------
	0x3200 OVR_OV_CTRL0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_OV_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"main_444"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"main_420"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"main_cflt_mode"          },
};

/*------------------------------------
	0x3210 OVR_OV_MOFFSET
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_OV_MOFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"m_hoffset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"m_voffset"               },
};

/*------------------------------------
	0x3214 OVR_OV_MSIZE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_OV_MSIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"m_hsize"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"m_vsize"                 },
};

/*------------------------------------
	0x3220 OVR_OV_BORDER_WIDTH
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_OV_BORDER_WIDTH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"m_right_wid"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"m_left_wid"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"m_down_wid"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"m_up_wid"                },
};

/*------------------------------------
	0x3224 OVR_CFLT_COEF0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_CFLT_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cflt_coef_1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"cflt_coef_0"             },
};

/*------------------------------------
	0x3228 OVR_CFLT_COEF1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_CFLT_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cflt_coef_3"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"cflt_coef_2"             },
};

/*------------------------------------
	0x3230 OVR_OV_PARAM_BY_DDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_OV_PARAM_BY_DDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"stride"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vsize"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"endian_conversion"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"update_by_ddr"           },
};

/*------------------------------------
	0x3240 OVR_OV_INTR_CTRL
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_OV_INTR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"intr_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"intr_line_pos_enable"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"intr_sbuf_c_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"intr_sbuf_y_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"intr_mbuf_c_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"intr_mbuf_y_empty_en"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"intr_pdb_end_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"line_position"           },
};

/*------------------------------------
	0x3244 OVR_OV_INTR_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_OVR_OV_INTR_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"mbuf_c_empty"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"mbuf_y_empty"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"line_cnt"                },
};

DBG_REG_T gDbgRegWCP[] = {
	{ 0x1200 ,N_FLD(dbg_OVL_OV_CTRL0)            ,"OVL_OV_CTRL0"              ,dbg_OVL_OV_CTRL0            },
	{ 0x1204 ,N_FLD(dbg_OV_CTRL1)                ,"OV_CTRL1"                  ,dbg_OV_CTRL1                },
	{ 0x1208 ,N_FLD(dbg_OV_CTRL2)                ,"OV_CTRL2"                  ,dbg_OV_CTRL2                },
	{ 0x120c ,N_FLD(dbg_OV_CTRL3)                ,"OV_CTRL3"                  ,dbg_OV_CTRL3                },
	{ 0x1210 ,N_FLD(dbg_OVL_OV_MOFFSET)          ,"OVL_OV_MOFFSET"            ,dbg_OVL_OV_MOFFSET          },
	{ 0x1214 ,N_FLD(dbg_OVL_OV_MSIZE)            ,"OVL_OV_MSIZE"              ,dbg_OVL_OV_MSIZE            },
	{ 0x1218 ,N_FLD(dbg_OV_SOFFSET)              ,"OV_SOFFSET"                ,dbg_OV_SOFFSET              },
	{ 0x121c ,N_FLD(dbg_OV_SSIZE)                ,"OV_SSIZE"                  ,dbg_OV_SSIZE                },
	{ 0x1220 ,N_FLD(dbg_OVL_OV_BORDER_WIDTH)     ,"OVL_OV_BORDER_WIDTH"       ,dbg_OVL_OV_BORDER_WIDTH     },
	{ 0x1224 ,N_FLD(dbg_OVL_CFLT_COEF0)          ,"OVL_CFLT_COEF0"            ,dbg_OVL_CFLT_COEF0          },
	{ 0x1228 ,N_FLD(dbg_OVL_CFLT_COEF1)          ,"OVL_CFLT_COEF1"            ,dbg_OVL_CFLT_COEF1          },
	{ 0x1230 ,N_FLD(dbg_OVL_OV_PARAM_BY_DDR)     ,"OVL_OV_PARAM_BY_DDR"       ,dbg_OVL_OV_PARAM_BY_DDR     },
	{ 0x1240 ,N_FLD(dbg_OVL_OV_INTR_CTRL)        ,"OVL_OV_INTR_CTRL"          ,dbg_OVL_OV_INTR_CTRL        },
	{ 0x1244 ,N_FLD(dbg_OVL_OV_INTR_STATUS)      ,"OVL_OV_INTR_STATUS"        ,dbg_OVL_OV_INTR_STATUS      },
	{ 0x1248 ,N_FLD(dbg_OV_CTRL4)                ,"OV_CTRL4"                  ,dbg_OV_CTRL4                },
	{ 0x124c ,N_FLD(dbg_OV_CTRL5)                ,"OV_CTRL5"                  ,dbg_OV_CTRL5                },
	{ 0x1250 ,N_FLD(dbg_OV_CTRL6)                ,"OV_CTRL6"                  ,dbg_OV_CTRL6                },
	{ 0x3200 ,N_FLD(dbg_OVR_OV_CTRL0)            ,"OVR_OV_CTRL0"              ,dbg_OVR_OV_CTRL0            },
	{ 0x3210 ,N_FLD(dbg_OVR_OV_MOFFSET)          ,"OVR_OV_MOFFSET"            ,dbg_OVR_OV_MOFFSET          },
	{ 0x3214 ,N_FLD(dbg_OVR_OV_MSIZE)            ,"OVR_OV_MSIZE"              ,dbg_OVR_OV_MSIZE            },
	{ 0x3220 ,N_FLD(dbg_OVR_OV_BORDER_WIDTH)     ,"OVR_OV_BORDER_WIDTH"       ,dbg_OVR_OV_BORDER_WIDTH     },
	{ 0x3224 ,N_FLD(dbg_OVR_CFLT_COEF0)          ,"OVR_CFLT_COEF0"            ,dbg_OVR_CFLT_COEF0          },
	{ 0x3228 ,N_FLD(dbg_OVR_CFLT_COEF1)          ,"OVR_CFLT_COEF1"            ,dbg_OVR_CFLT_COEF1          },
	{ 0x3230 ,N_FLD(dbg_OVR_OV_PARAM_BY_DDR)     ,"OVR_OV_PARAM_BY_DDR"       ,dbg_OVR_OV_PARAM_BY_DDR     },
	{ 0x3240 ,N_FLD(dbg_OVR_OV_INTR_CTRL)        ,"OVR_OV_INTR_CTRL"          ,dbg_OVR_OV_INTR_CTRL        },
	{ 0x3244 ,N_FLD(dbg_OVR_OV_INTR_STATUS)      ,"OVR_OV_INTR_STATUS"        ,dbg_OVR_OV_INTR_STATUS      },
	{ 0 , } // end marker
};

#endif
