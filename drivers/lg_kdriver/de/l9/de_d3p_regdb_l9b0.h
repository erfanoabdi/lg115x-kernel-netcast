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

#ifndef _DBG_D3P_h
#define _DBG_D3P_h

/*----------------------------------------
	0x5d20 D3_PP_3DCONV_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_3DCONV_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"d3p_3dconv_r_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fpacking_r_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"d3p_3dconv_l_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"fpacking_l_en"           },
};

/*----------------------------------------
	0x5d24 D3_PP_3DCONV_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_3DCONV_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"offset_r"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"offset_l"                },
};

/*----------------------------------------
	0x5d28 D3_PP_3DCONV_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_3DCONV_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"bg_color_grey"           },
};

/*----------------------------------------
	0x5d40 D3_PP_PCAP_L_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_L_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pxl_rep_xpos"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pxl_rep_ypos"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pxl_rep_in"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"pxl_rep_out"             },
};

/*----------------------------------------
	0x5d44 D3_PP_PCAP_L_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_L_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pxl_rep_width"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pxl_rep_height"          },
};

/*----------------------------------------
	0x5d48 D3_PP_PCAP_L_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_L_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"pxl_rep_value_g"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"pxl_rep_value_b"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"pxl_rep_value_r"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"pcap_mode"               },
};

/*----------------------------------------
	0x5d4c D3_PP_PCAP_L_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_L_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"pxl_rep_value_g"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"pxl_rep_value_b"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"pxl_rep_value_r"         },
};

/*----------------------------------------
	0x5d50 D3_PP_PCAP_L_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_L_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"capture_addr"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"capture_ai"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,16 ,"capture_num"             },
};

/*----------------------------------------
	0x5d54 D3_PP_PCAP_L_DATA
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_L_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"lut_data_g"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"lut_data_b"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"lut_data_r"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"capture_stat_started"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"capture_stat_ended"      },
};

/*----------------------------------------
	0x5d58 D3_PP_PCAP_L_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_L_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"col_fil_g_valid"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"col_fil_b_valid"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"col_fil_r_valid"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"col_fil_g_nvalid"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"col_fil_b_nvalid"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"col_fil_r_nvalid"        },
};

/*----------------------------------------
	0x5d70 D3_PP_PCAP_R_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_R_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pxl_rep_xpos"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pxl_rep_ypos"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pxl_rep_in"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"pxl_rep_out"             },
};

/*----------------------------------------
	0x5d74 D3_PP_PCAP_R_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_R_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pxl_rep_width"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pxl_rep_height"          },
};

/*----------------------------------------
	0x5d78 D3_PP_PCAP_R_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_R_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"pxl_rep_value_g"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"pxl_rep_value_b"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"pxl_rep_value_r"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"pcap_mode"               },
};

/*----------------------------------------
	0x5d7c D3_PP_PCAP_R_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_R_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"pxl_rep_value_g"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"pxl_rep_value_b"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"pxl_rep_value_r"         },
};

/*----------------------------------------
	0x5d80 D3_PP_PCAP_R_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_R_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"capture_addr"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"capture_ai"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,16 ,"capture_num"             },
};

/*----------------------------------------
	0x5d84 D3_PP_PCAP_R_DATA
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_R_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"lut_data_g"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"lut_data_b"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"lut_data_r"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"capture_stat_started"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"capture_stat_ended"      },
};

/*----------------------------------------
	0x5d88 D3_PP_PCAP_R_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_PCAP_R_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"col_fil_g_valid"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"col_fil_b_valid"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"col_fil_r_valid"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"col_fil_g_nvalid"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"col_fil_b_nvalid"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"col_fil_r_nvalid"        },
};

/*----------------------------------------
	0x5da0 D3_PP_MUX3D_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_MUX3D_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"mux3d_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"l_outmux"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"r_outmux"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"alpha1_gain"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"alpha0_gain"             },
};

/*----------------------------------------
	0x5da4 D3_PP_MUX3D_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_MUX3D_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"mux_l_window_h_en"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mux_l_window_v_en"       },
};

/*----------------------------------------
	0x5da8 D3_PP_MUX3D_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_MUX3D_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                      },
};

/*----------------------------------------
	0x5dac D3_PP_MUX3D_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_MUX3D_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"mux_r_window_h_en"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mux_r_window_v_en"       },
};

/*----------------------------------------
	0x5db0 D3_PP_MUX3D_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_MUX3D_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                      },
};

/*----------------------------------------
	0x5db4 D3_PP_MUX3D_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_D3_PP_MUX3D_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"bg_color_r"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"bg_color_b"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"bg_color_g"              },
};

DBG_REG_T gDbgRegD3P[] = {
	{ 0x5d20 ,N_FLD(dbg_D3_PP_3DCONV_CTRL_00)        ,"D3_PP_3DCONV_CTRL_00"          ,dbg_D3_PP_3DCONV_CTRL_00        },
	{ 0x5d24 ,N_FLD(dbg_D3_PP_3DCONV_CTRL_01)        ,"D3_PP_3DCONV_CTRL_01"          ,dbg_D3_PP_3DCONV_CTRL_01        },
	{ 0x5d28 ,N_FLD(dbg_D3_PP_3DCONV_CTRL_02)        ,"D3_PP_3DCONV_CTRL_02"          ,dbg_D3_PP_3DCONV_CTRL_02        },
	{ 0x5d40 ,N_FLD(dbg_D3_PP_PCAP_L_CTRL_00)        ,"D3_PP_PCAP_L_CTRL_00"          ,dbg_D3_PP_PCAP_L_CTRL_00        },
	{ 0x5d44 ,N_FLD(dbg_D3_PP_PCAP_L_CTRL_01)        ,"D3_PP_PCAP_L_CTRL_01"          ,dbg_D3_PP_PCAP_L_CTRL_01        },
	{ 0x5d48 ,N_FLD(dbg_D3_PP_PCAP_L_CTRL_02)        ,"D3_PP_PCAP_L_CTRL_02"          ,dbg_D3_PP_PCAP_L_CTRL_02        },
	{ 0x5d4c ,N_FLD(dbg_D3_PP_PCAP_L_CTRL_03)        ,"D3_PP_PCAP_L_CTRL_03"          ,dbg_D3_PP_PCAP_L_CTRL_03        },
	{ 0x5d50 ,N_FLD(dbg_D3_PP_PCAP_L_CTRL)           ,"D3_PP_PCAP_L_CTRL"             ,dbg_D3_PP_PCAP_L_CTRL           },
	{ 0x5d54 ,N_FLD(dbg_D3_PP_PCAP_L_DATA)           ,"D3_PP_PCAP_L_DATA"             ,dbg_D3_PP_PCAP_L_DATA           },
	{ 0x5d58 ,N_FLD(dbg_D3_PP_PCAP_L_CTRL_04)        ,"D3_PP_PCAP_L_CTRL_04"          ,dbg_D3_PP_PCAP_L_CTRL_04        },
	{ 0x5d70 ,N_FLD(dbg_D3_PP_PCAP_R_CTRL_00)        ,"D3_PP_PCAP_R_CTRL_00"          ,dbg_D3_PP_PCAP_R_CTRL_00        },
	{ 0x5d74 ,N_FLD(dbg_D3_PP_PCAP_R_CTRL_01)        ,"D3_PP_PCAP_R_CTRL_01"          ,dbg_D3_PP_PCAP_R_CTRL_01        },
	{ 0x5d78 ,N_FLD(dbg_D3_PP_PCAP_R_CTRL_02)        ,"D3_PP_PCAP_R_CTRL_02"          ,dbg_D3_PP_PCAP_R_CTRL_02        },
	{ 0x5d7c ,N_FLD(dbg_D3_PP_PCAP_R_CTRL_03)        ,"D3_PP_PCAP_R_CTRL_03"          ,dbg_D3_PP_PCAP_R_CTRL_03        },
	{ 0x5d80 ,N_FLD(dbg_D3_PP_PCAP_R_CTRL)           ,"D3_PP_PCAP_R_CTRL"             ,dbg_D3_PP_PCAP_R_CTRL           },
	{ 0x5d84 ,N_FLD(dbg_D3_PP_PCAP_R_DATA)           ,"D3_PP_PCAP_R_DATA"             ,dbg_D3_PP_PCAP_R_DATA           },
	{ 0x5d88 ,N_FLD(dbg_D3_PP_PCAP_R_CTRL_04)        ,"D3_PP_PCAP_R_CTRL_04"          ,dbg_D3_PP_PCAP_R_CTRL_04        },
	{ 0x5da0 ,N_FLD(dbg_D3_PP_MUX3D_CTRL_00)         ,"D3_PP_MUX3D_CTRL_00"           ,dbg_D3_PP_MUX3D_CTRL_00         },
	{ 0x5da4 ,N_FLD(dbg_D3_PP_MUX3D_CTRL_01)         ,"D3_PP_MUX3D_CTRL_01"           ,dbg_D3_PP_MUX3D_CTRL_01         },
	{ 0x5da8 ,N_FLD(dbg_D3_PP_MUX3D_CTRL_02)         ,"D3_PP_MUX3D_CTRL_02"           ,dbg_D3_PP_MUX3D_CTRL_02         },
	{ 0x5dac ,N_FLD(dbg_D3_PP_MUX3D_CTRL_03)         ,"D3_PP_MUX3D_CTRL_03"           ,dbg_D3_PP_MUX3D_CTRL_03         },
	{ 0x5db0 ,N_FLD(dbg_D3_PP_MUX3D_CTRL_04)         ,"D3_PP_MUX3D_CTRL_04"           ,dbg_D3_PP_MUX3D_CTRL_04         },
	{ 0x5db4 ,N_FLD(dbg_D3_PP_MUX3D_CTRL_05)         ,"D3_PP_MUX3D_CTRL_05"           ,dbg_D3_PP_MUX3D_CTRL_05         },
	{ 0 , } // end marker
};

#endif
