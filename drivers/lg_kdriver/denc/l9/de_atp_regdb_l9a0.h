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

#ifndef _DBG_ATP_h
#define _DBG_ATP_h

/*--------------------------------
	0x3c00 TTX_VER_CTRL0
--------------------------------*/
const DBG_REG_FIELD_T dbg_TTX_VER_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ttx_ovs"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ttx_ove"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ttx_evs"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ttx_eve"                     },
};

/*--------------------------------
	0x3c04 TTX_VER_CTRL1
--------------------------------*/
const DBG_REG_FIELD_T dbg_TTX_VER_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ttx_ovs8"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"ttx_ove8"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"ttx_evs8"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"ttx_eve8"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"ttx_iter_cnt"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"ttx_adj"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"ttx_err"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,14 ,"ttx_line"                    },
};

/*--------------------------------
	0x3c08 WSS_DATA
--------------------------------*/
const DBG_REG_FIELD_T dbg_WSS_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"ttx_hs"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,11 ,"comp_c_delay"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"wss_data"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"comp_y_lpf"                  },
};

/*--------------------------------
	0x3c0c CGMS_DATA
--------------------------------*/
const DBG_REG_FIELD_T dbg_CGMS_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,0  ,"cgms_enc_data"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"secam_burst_blank_end"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"secam_preem_scaling"         },
};

/*--------------------------------
	0x3c10 CVE_CONFIG
--------------------------------*/
const DBG_REG_FIELD_T dbg_CVE_CONFIG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"standard"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"enc_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"color_bar_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,5  ,"c_filter"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"color_on"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"y_filter"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"y_delay"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"ttx_sys"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"video_interface_sel"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"burst_amp"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,24 ,"secam_y_delay"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,29 ,"offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"invert"                      },
};

/*--------------------------------
	0x3c14 PHASE_INCR
--------------------------------*/
const DBG_REG_FIELD_T dbg_PHASE_INCR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"phase_incr"                  },
};

/*--------------------------------
	0x3c18 DENC_VBI_CTRL
--------------------------------*/
const DBG_REG_FIELD_T dbg_DENC_VBI_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"phase_offset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"secam_subcarrier_scaling"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,14 ,"secam_c_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cc1_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"cc2_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"cc1_full"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"cc2_full"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cgms_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"wss_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"ttx_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"fm_reset_on"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fm_reset_initial"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,25 ,"burst_phase_reset_strt"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"comp_c_gain"                 },
};

/*--------------------------------
	0x3c1c CC_DATA
--------------------------------*/
const DBG_REG_FIELD_T dbg_CC_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"cc_data_f1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"cc_data_f2"                  },
};

/*--------------------------------
	0x3c20 MV_N0_3
--------------------------------*/
const DBG_REG_FIELD_T dbg_MV_N0_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"mv_n0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"mv_n2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"mv_n1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"mv_n3"                       },
};

/*--------------------------------
	0x3c24 MV_N4_9
--------------------------------*/
const DBG_REG_FIELD_T dbg_MV_N4_9[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"mv_n4"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"mv_n22"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"mv_n8"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"mv_n7"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,18 ,"mv_n6"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"mv_n5"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"mv_n9"                       },
};

/*--------------------------------
	0x3c28 MV_N10_11
--------------------------------*/
const DBG_REG_FIELD_T dbg_MV_N10_11[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"mv_n10"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,6  ,"mv_n21"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"mv_n11"                      },
};

/*--------------------------------
	0x3c2c MV_N12_14
--------------------------------*/
const DBG_REG_FIELD_T dbg_MV_N12_14[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"mv_n12"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"mv_n14"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"mv_n13"                      },
};

/*--------------------------------
	0x3c30 MV_N15_20
--------------------------------*/
const DBG_REG_FIELD_T dbg_MV_N15_20[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"mv_n15"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"mv_n20"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"mv_n16"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"mv_n19"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"mv_n18"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"mv_n17"                      },
};

/*--------------------------------
	0x3c34 VPS_CTRL
--------------------------------*/
const DBG_REG_FIELD_T dbg_VPS_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"index"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"lpf_bypass"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"vbi_odd"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"vbi_even"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"vps_enable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vps_wr_done"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"vps_data"                    },
};

/*--------------------------------
	0x3c38 TTX_DATA
--------------------------------*/
const DBG_REG_FIELD_T dbg_TTX_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ttx_data"                    },
};

/*--------------------------------
	0x3c3c TTX_LOAD
--------------------------------*/
const DBG_REG_FIELD_T dbg_TTX_LOAD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ttx_load"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mv_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ttx_write_addr"              },
};

/*--------------------------------
	0x3c80 FIELD_MODE
--------------------------------*/
const DBG_REG_FIELD_T dbg_FIELD_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"interlaced_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"top_field"                   },
};

/*--------------------------------
	0x3c84 A_TOP_STATUS
--------------------------------*/
const DBG_REG_FIELD_T dbg_A_TOP_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_status"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"c_status"                    },
};

DBG_REG_T gDbgRegATP[] = {
	{ 0x3c00 ,N_FLD(dbg_TTX_VER_CTRL0)       ,"TTX_VER_CTRL0"         ,dbg_TTX_VER_CTRL0       },
	{ 0x3c04 ,N_FLD(dbg_TTX_VER_CTRL1)       ,"TTX_VER_CTRL1"         ,dbg_TTX_VER_CTRL1       },
	{ 0x3c08 ,N_FLD(dbg_WSS_DATA)            ,"WSS_DATA"              ,dbg_WSS_DATA            },
	{ 0x3c0c ,N_FLD(dbg_CGMS_DATA)           ,"CGMS_DATA"             ,dbg_CGMS_DATA           },
	{ 0x3c10 ,N_FLD(dbg_CVE_CONFIG)          ,"CVE_CONFIG"            ,dbg_CVE_CONFIG          },
	{ 0x3c14 ,N_FLD(dbg_PHASE_INCR)          ,"PHASE_INCR"            ,dbg_PHASE_INCR          },
	{ 0x3c18 ,N_FLD(dbg_DENC_VBI_CTRL)       ,"DENC_VBI_CTRL"         ,dbg_DENC_VBI_CTRL       },
	{ 0x3c1c ,N_FLD(dbg_CC_DATA)             ,"CC_DATA"               ,dbg_CC_DATA             },
	{ 0x3c20 ,N_FLD(dbg_MV_N0_3)             ,"MV_N0_3"               ,dbg_MV_N0_3             },
	{ 0x3c24 ,N_FLD(dbg_MV_N4_9)             ,"MV_N4_9"               ,dbg_MV_N4_9             },
	{ 0x3c28 ,N_FLD(dbg_MV_N10_11)           ,"MV_N10_11"             ,dbg_MV_N10_11           },
	{ 0x3c2c ,N_FLD(dbg_MV_N12_14)           ,"MV_N12_14"             ,dbg_MV_N12_14           },
	{ 0x3c30 ,N_FLD(dbg_MV_N15_20)           ,"MV_N15_20"             ,dbg_MV_N15_20           },
	{ 0x3c34 ,N_FLD(dbg_VPS_CTRL)            ,"VPS_CTRL"              ,dbg_VPS_CTRL            },
	{ 0x3c38 ,N_FLD(dbg_TTX_DATA)            ,"TTX_DATA"              ,dbg_TTX_DATA            },
	{ 0x3c3c ,N_FLD(dbg_TTX_LOAD)            ,"TTX_LOAD"              ,dbg_TTX_LOAD            },
	{ 0x3c80 ,N_FLD(dbg_FIELD_MODE)          ,"FIELD_MODE"            ,dbg_FIELD_MODE          },
	{ 0x3c84 ,N_FLD(dbg_A_TOP_STATUS)        ,"A_TOP_STATUS"          ,dbg_A_TOP_STATUS        },
	{ 0 , } // end marker
};

#endif
