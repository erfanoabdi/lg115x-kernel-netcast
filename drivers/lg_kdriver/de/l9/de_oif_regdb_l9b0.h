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

#ifndef _DBG_OIF_h
#define _DBG_OIF_h

/*------------------------------------
	0x5c00 OUT_VIDEO_INFO
------------------------------------*/
const DBG_REG_FIELD_T dbg_OUT_VIDEO_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"de1_out_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"de2_out_sel"                 },
};

/*------------------------------------
	0x5c04 DATA_COLOR_FROM
------------------------------------*/
const DBG_REG_FIELD_T dbg_DATA_COLOR_FROM[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"b_data_from"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"g_data_from"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"r_data_from"                 },
};

/*------------------------------------
	0x5c08 DATA_COLOR
------------------------------------*/
const DBG_REG_FIELD_T dbg_DATA_COLOR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"data_color_b"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"data_color_g"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"data_color_r"                },
};

/*------------------------------------
	0x5c0c SYNC_COLOR
------------------------------------*/
const DBG_REG_FIELD_T dbg_SYNC_COLOR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"sync_color_b"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"sync_color_g"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"sync_color_r"                },
};

/*------------------------------------
	0x5c10 DELAY_DATA
------------------------------------*/
const DBG_REG_FIELD_T dbg_DELAY_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"b_delay_l"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,3  ,"g_delay_l"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,6  ,"r_delay_l"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,9  ,"de_delay_l"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"b_delay_r"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,19 ,"g_delay_r"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,22 ,"r_delay_r"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,25 ,"de_delay_r"                  },
};

/*------------------------------------
	0x5c14 SYNC_DE_CONTROL
------------------------------------*/
const DBG_REG_FIELD_T dbg_SYNC_DE_CONTROL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"de_pol"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"de_disable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"hsync_pol"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"hsync_disable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vsync_pol"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"vsync_disable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"alpha_sel_76"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"alpha_sel_54"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"alpha_sel_32"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"alpha_sel_10"                },
};

/*------------------------------------
	0x5c20 LVDS_IF_CONTROL
------------------------------------*/
const DBG_REG_FIELD_T dbg_LVDS_IF_CONTROL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"lvds_empty_data_ch1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"lvds_empty_data_ch2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"lvds_8bit_mode"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"lvds_lsb_first"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,6  ,"lvds_sync_order"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"lvds_ch1_from"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,11 ,"lvds_ch2_from"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"dual_out_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"even_pix_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,15 ,"lvds_d_lane_empty_data_ch1"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,18 ,"lvds_e_lane_empty_data_ch1"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"lvds_d_lane_empty_data_ch2"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"lvds_e_lane_empty_data_ch2"  },
};

/*------------------------------------
	0x5c24 LVDS_PORT_SWAP
------------------------------------*/
const DBG_REG_FIELD_T dbg_LVDS_PORT_SWAP[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"lvds_a_lane_sel_ch1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,3  ,"lvds_b_lane_sel_ch1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,6  ,"lvds_c_lane_sel_ch1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"lvds_d_lane_sel_ch1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"lvds_e_lane_sel_ch1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"lvds_a_lane_sel_ch2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,19 ,"lvds_b_lane_sel_ch2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,22 ,"lvds_c_lane_sel_ch2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"lvds_d_lane_sel_ch2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"lvds_e_lane_sel_ch2"         },
};

/*------------------------------------
	0x5c38 LVDS_FORCE_DATA_EN
------------------------------------*/
const DBG_REG_FIELD_T dbg_LVDS_FORCE_DATA_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"de1_hsync_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"de1_vsyn_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"de2_hsync_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"de2_vsync_en"                },
};

/*------------------------------------
	0x5c3c LVDS_FORCE_DATA
------------------------------------*/
const DBG_REG_FIELD_T dbg_LVDS_FORCE_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"de1_empty_data0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"de1_empty_data1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"de1_hsync"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"de1_vsyn"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"de2_empty_data0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"de2_empty_data1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"de2_hsync"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"de2_vsync"                   },
};

DBG_REG_T gDbgRegOIF[] = {
	{ 0x5c00 ,N_FLD(dbg_OUT_VIDEO_INFO)          ,"OUT_VIDEO_INFO"            ,dbg_OUT_VIDEO_INFO          },
	{ 0x5c04 ,N_FLD(dbg_DATA_COLOR_FROM)         ,"DATA_COLOR_FROM"           ,dbg_DATA_COLOR_FROM         },
	{ 0x5c08 ,N_FLD(dbg_DATA_COLOR)              ,"DATA_COLOR"                ,dbg_DATA_COLOR              },
	{ 0x5c0c ,N_FLD(dbg_SYNC_COLOR)              ,"SYNC_COLOR"                ,dbg_SYNC_COLOR              },
	{ 0x5c10 ,N_FLD(dbg_DELAY_DATA)              ,"DELAY_DATA"                ,dbg_DELAY_DATA              },
	{ 0x5c14 ,N_FLD(dbg_SYNC_DE_CONTROL)         ,"SYNC_DE_CONTROL"           ,dbg_SYNC_DE_CONTROL         },
	{ 0x5c20 ,N_FLD(dbg_LVDS_IF_CONTROL)         ,"LVDS_IF_CONTROL"           ,dbg_LVDS_IF_CONTROL         },
	{ 0x5c24 ,N_FLD(dbg_LVDS_PORT_SWAP)          ,"LVDS_PORT_SWAP"            ,dbg_LVDS_PORT_SWAP          },
	{ 0x5c38 ,N_FLD(dbg_LVDS_FORCE_DATA_EN)      ,"LVDS_FORCE_DATA_EN"        ,dbg_LVDS_FORCE_DATA_EN      },
	{ 0x5c3c ,N_FLD(dbg_LVDS_FORCE_DATA)         ,"LVDS_FORCE_DATA"           ,dbg_LVDS_FORCE_DATA         },
	{ 0 , } // end marker
};

#endif
