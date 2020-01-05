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

#ifndef _DBG_SSC_h
#define _DBG_SSC_h

/*----------------------------------------
	0x2100 SSC_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bnd_pel_filtering_scheme"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fir_config"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"filter_type_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"size_info_manual_load"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"ddr_update_endian_change"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"stride_cvi_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"dvr_write_mode"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"source_sel"                  },
};

/*----------------------------------------
	0x2104 SSC_FIELD
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_FIELD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"interlace_mode"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"curr_field"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"mpeg_stream"                 },
};

/*----------------------------------------
	0x2108 SSC_Y_INIT_POS_H
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_Y_INIT_POS_H[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"y_init_pos_h"                },
};

/*----------------------------------------
	0x210c SSC_Y_INIT_POS_V
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_Y_INIT_POS_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"y_init_pos_v"                },
};

/*----------------------------------------
	0x2110 SSC_C_INIT_POS_H
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_C_INIT_POS_H[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"c_init_pos_h"                },
};

/*----------------------------------------
	0x2114 SSC_C_INIT_POS_V
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_C_INIT_POS_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"c_init_pos_v"                },
};

/*----------------------------------------
	0x2118 SSC_SCR_SIZE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_SCR_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"input_h_size"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"input_v_size"                },
};

/*----------------------------------------
	0x211c SSC_WIN_OUT_SIZE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_WIN_OUT_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"out_win_h_size"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"out_win_v_size"              },
};

/*----------------------------------------
	0x2120 SSC_WIN_IN_OFFSET
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_WIN_IN_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"in_win_h_offset"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"in_win_v_offset"             },
};

/*----------------------------------------
	0x2124 SSC_WIN_IN_SIZE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_WIN_IN_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"in_win_h_size"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"in_win_v_size"               },
};

/*----------------------------------------
	0x2128 SSC_C_FORMAT
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_C_FORMAT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"in_c_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"out_c_format"                },
};

/*----------------------------------------
	0x2130 SSC_H_FIR_COEF_DATA0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_H_FIR_COEF_DATA0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"h_coefficient0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"h_coefficient1"              },
};

/*----------------------------------------
	0x2134 SSC_H_FIR_COEF_DATA1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_H_FIR_COEF_DATA1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"h_coefficient2"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"h_coefficient3"              },
};

/*----------------------------------------
	0x2138 SSC_H_FIR_COEF_DATA2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_H_FIR_COEF_DATA2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"h_coefficient4"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"h_coefficient5"              },
};

/*----------------------------------------
	0x213c SSC_H_FIR_COEF_DATA3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_H_FIR_COEF_DATA3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"h_coefficient6"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"h_coefficient7"              },
};

/*----------------------------------------
	0x2140 SSC_H_FIR_COEF_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_H_FIR_COEF_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"addr"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"h_v_sel"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"rnw"                         },
};

/*----------------------------------------
	0x2168 SSC_STATUS_REV
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_STATUS_REV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"y_status"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"c_status"                    },
};

/*----------------------------------------
	0x216c SSC_MANUAL_LOAD
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_MANUAL_LOAD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"update_input_frm_size"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"update_wout_size"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update_win_offset"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"update_win_size"             },
};

/*----------------------------------------
	0x2170 SSC_CANVAS_MODE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_SSC_CANVAS_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"h_offset"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"v_offset"                    },
};

DBG_REG_T gDbgRegSSC[] = {
	{ 0x2100 ,N_FLD(dbg_SSC_CTRL)                    ,"SSC_CTRL"                      ,dbg_SSC_CTRL                    },
	{ 0x2104 ,N_FLD(dbg_SSC_FIELD)                   ,"SSC_FIELD"                     ,dbg_SSC_FIELD                   },
	{ 0x2108 ,N_FLD(dbg_SSC_Y_INIT_POS_H)            ,"SSC_Y_INIT_POS_H"              ,dbg_SSC_Y_INIT_POS_H            },
	{ 0x210c ,N_FLD(dbg_SSC_Y_INIT_POS_V)            ,"SSC_Y_INIT_POS_V"              ,dbg_SSC_Y_INIT_POS_V            },
	{ 0x2110 ,N_FLD(dbg_SSC_C_INIT_POS_H)            ,"SSC_C_INIT_POS_H"              ,dbg_SSC_C_INIT_POS_H            },
	{ 0x2114 ,N_FLD(dbg_SSC_C_INIT_POS_V)            ,"SSC_C_INIT_POS_V"              ,dbg_SSC_C_INIT_POS_V            },
	{ 0x2118 ,N_FLD(dbg_SSC_SCR_SIZE)                ,"SSC_SCR_SIZE"                  ,dbg_SSC_SCR_SIZE                },
	{ 0x211c ,N_FLD(dbg_SSC_WIN_OUT_SIZE)            ,"SSC_WIN_OUT_SIZE"              ,dbg_SSC_WIN_OUT_SIZE            },
	{ 0x2120 ,N_FLD(dbg_SSC_WIN_IN_OFFSET)           ,"SSC_WIN_IN_OFFSET"             ,dbg_SSC_WIN_IN_OFFSET           },
	{ 0x2124 ,N_FLD(dbg_SSC_WIN_IN_SIZE)             ,"SSC_WIN_IN_SIZE"               ,dbg_SSC_WIN_IN_SIZE             },
	{ 0x2128 ,N_FLD(dbg_SSC_C_FORMAT)                ,"SSC_C_FORMAT"                  ,dbg_SSC_C_FORMAT                },
	{ 0x2130 ,N_FLD(dbg_SSC_H_FIR_COEF_DATA0)        ,"SSC_H_FIR_COEF_DATA0"          ,dbg_SSC_H_FIR_COEF_DATA0        },
	{ 0x2134 ,N_FLD(dbg_SSC_H_FIR_COEF_DATA1)        ,"SSC_H_FIR_COEF_DATA1"          ,dbg_SSC_H_FIR_COEF_DATA1        },
	{ 0x2138 ,N_FLD(dbg_SSC_H_FIR_COEF_DATA2)        ,"SSC_H_FIR_COEF_DATA2"          ,dbg_SSC_H_FIR_COEF_DATA2        },
	{ 0x213c ,N_FLD(dbg_SSC_H_FIR_COEF_DATA3)        ,"SSC_H_FIR_COEF_DATA3"          ,dbg_SSC_H_FIR_COEF_DATA3        },
	{ 0x2140 ,N_FLD(dbg_SSC_H_FIR_COEF_CTRL)         ,"SSC_H_FIR_COEF_CTRL"           ,dbg_SSC_H_FIR_COEF_CTRL         },
	{ 0x2168 ,N_FLD(dbg_SSC_STATUS_REV)              ,"SSC_STATUS_REV"                ,dbg_SSC_STATUS_REV              },
	{ 0x216c ,N_FLD(dbg_SSC_MANUAL_LOAD)             ,"SSC_MANUAL_LOAD"               ,dbg_SSC_MANUAL_LOAD             },
	{ 0x2170 ,N_FLD(dbg_SSC_CANVAS_MODE)             ,"SSC_CANVAS_MODE"               ,dbg_SSC_CANVAS_MODE             },
	{ 0 , } // end marker
};

#endif
