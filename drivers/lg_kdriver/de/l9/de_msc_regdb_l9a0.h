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

#ifndef _DBG_MSC_h
#define _DBG_MSC_h

/*----------------------------------------
	0x1100 MSC_CTRL_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_CTRL_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bnd_pel_filtering_scheme"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"adaptive_fir_filter_en"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"v_scaler_config"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"filter_type_sel_luma"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"filter_type_sel_chroma"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"manual_sampling_mode"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"size_info_manual_load"           },
};

/*----------------------------------------
	0x1104 MSC_Y_INIT_POS_H_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_INIT_POS_H_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"y_init_pos_h"                    },
};

/*----------------------------------------
	0x1108 MSC_Y_INIT_POS_V_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_INIT_POS_V_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"y_init_pos_v"                    },
};

/*----------------------------------------
	0x110c MSC_C_INIT_POS_H_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_INIT_POS_H_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"c_init_pos_h"                    },
};

/*----------------------------------------
	0x1110 MSC_C_INIT_POS_V_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_INIT_POS_V_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"c_init_pos_v"                    },
};

/*----------------------------------------
	0x1114 MSC_ADAPTIVE_TH_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_ADAPTIVE_TH_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"reg_th"                          },
};

/*----------------------------------------
	0x1118 MSC_SCR_SIZE_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_SCR_SIZE_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"input_h_size"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"input_v_size"                    },
};

/*----------------------------------------
	0x111c MSC_WIN_OUT_SIZE_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WIN_OUT_SIZE_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"out_win_h_size"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"out_win_v_size"                  },
};

/*----------------------------------------
	0x1120 MSC_WIN_IN_OFFSET_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WIN_IN_OFFSET_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"in_win_h_offset"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"in_win_v_offset"                 },
};

/*----------------------------------------
	0x1124 MSC_WIN_IN_SIZE_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WIN_IN_SIZE_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"in_win_h_size"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"in_win_v_size"                   },
};

/*----------------------------------------
	0x1128 MSC_C_FORMAT_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FORMAT_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"in_c_format"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"out_c_format"                    },
};

/*----------------------------------------
	0x1130 MSC_Y_FIR_COEF_DATA0_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA0_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient1"                  },
};

/*----------------------------------------
	0x1134 MSC_Y_FIR_COEF_DATA1_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA1_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient3"                  },
};

/*----------------------------------------
	0x1138 MSC_Y_FIR_COEF_DATA2_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA2_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient4"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient5"                  },
};

/*----------------------------------------
	0x113c MSC_Y_FIR_COEF_DATA3_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA3_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient6"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient7"                  },
};

/*----------------------------------------
	0x1140 MSC_Y_FIR_COEF_DATA4_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA4_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient8"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient9"                  },
};

/*----------------------------------------
	0x1144 MSC_Y_FIR_COEF_DATA5_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA5_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient10"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient11"                 },
};

/*----------------------------------------
	0x1148 MSC_Y_FIR_COEF_CTRL_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_CTRL_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"addr"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"h_v_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"hidden_configure4"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"rnw"                             },
};

/*----------------------------------------
	0x1150 MSC_C_FIR_COEF_DATA0_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA0_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient1"                  },
};

/*----------------------------------------
	0x1154 MSC_C_FIR_COEF_DATA1_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA1_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient3"                  },
};

/*----------------------------------------
	0x1158 MSC_C_FIR_COEF_DATA2_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA2_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient4"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient5"                  },
};

/*----------------------------------------
	0x115c MSC_C_FIR_COEF_DATA3_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA3_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient6"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient7"                  },
};

/*----------------------------------------
	0x1160 MSC_C_FIR_COEF_CTRL_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_CTRL_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"addr"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"h_v_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"rnw"                             },
};

/*----------------------------------------
	0x1168 MSC_STATUS_REV_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_STATUS_REV_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_status"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_status"                        },
};

/*----------------------------------------
	0x116c MSC_MANUAL_LOAD_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_MANUAL_LOAD_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"update_input_frm_size"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"update_wout_size"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update_win_offset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"update_win_size"                 },
};

/*----------------------------------------
	0x1170 MSC_WOUT_OFFSET_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WOUT_OFFSET_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"wout_v_offset"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"wout_h_offset"                   },
};

/*----------------------------------------
	0x1174 MSC_CHROMA_TEAR_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_CHROMA_TEAR_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"tearing_count_result"            },
};

/*----------------------------------------
	0x1178 MSC_CHROMA_TEAR_CTRL_L
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_CHROMA_TEAR_CTRL_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"auto_chroma_filter_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"vsc_chroma_pre_filter_en"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vsc_chroma_median_filter_en"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"manual_chroma_pre_filter_on"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"manual_chroma_median_filter_on"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"detect_level_th"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"tearing_count_th"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"frame_count_th"                  },
};

/*----------------------------------------
	0x1180 MSC_MIN_MAX_CTRL_L_Y
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_MIN_MAX_CTRL_L_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"min_max_filter_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"h_filter_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,4  ,"min_max_th"                      },
};

/*----------------------------------------
	0x1184 MSC_MIN_MAX_CTRL_L_C
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_MIN_MAX_CTRL_L_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"min_max_filter_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"h_filter_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,4  ,"min_max_th"                      },
};

/*----------------------------------------
	0x1190 MSL_MANUAL_SAMPLING_Y_H
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSL_MANUAL_SAMPLING_Y_H[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

/*----------------------------------------
	0x1194 MSL_MANUAL_SAMPLING_Y_V
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSL_MANUAL_SAMPLING_Y_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

/*----------------------------------------
	0x1198 MSL_MANUAL_SAMPLING_C_H
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSL_MANUAL_SAMPLING_C_H[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

/*----------------------------------------
	0x119c MSL_MANUAL_SAMPLING_C_V
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSL_MANUAL_SAMPLING_C_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

/*----------------------------------------
	0x3100 MSC_CTRL_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_CTRL_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bnd_pel_filtering_scheme"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"adaptive_fir_filter_en"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"v_scaler_config"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"filter_type_sel_luma"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"filter_type_sel_chroma"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"manual_sampling_mode"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"size_info_manual_load"           },
};

/*----------------------------------------
	0x3104 MSC_Y_INIT_POS_H_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_INIT_POS_H_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"y_init_pos_h"                    },
};

/*----------------------------------------
	0x3108 MSC_Y_INIT_POS_V_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_INIT_POS_V_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"y_init_pos_v"                    },
};

/*----------------------------------------
	0x310c MSC_C_INIT_POS_H_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_INIT_POS_H_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"c_init_pos_h"                    },
};

/*----------------------------------------
	0x3110 MSC_C_INIT_POS_V_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_INIT_POS_V_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"c_init_pos_v"                    },
};

/*----------------------------------------
	0x3114 MSC_ADAPTIVE_TH_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_ADAPTIVE_TH_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"reg_th"                          },
};

/*----------------------------------------
	0x3118 MSC_SCR_SIZE_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_SCR_SIZE_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"input_h_size"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"input_v_size"                    },
};

/*----------------------------------------
	0x311c MSC_WIN_OUT_SIZE_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WIN_OUT_SIZE_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"out_win_h_size"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"out_win_v_size"                  },
};

/*----------------------------------------
	0x3120 MSC_WIN_IN_OFFSET_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WIN_IN_OFFSET_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"in_win_h_offset"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"in_win_v_offset"                 },
};

/*----------------------------------------
	0x3124 MSC_WIN_IN_SIZE_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WIN_IN_SIZE_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"in_win_h_size"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"in_win_v_size"                   },
};

/*----------------------------------------
	0x3128 MSC_C_FORMAT_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FORMAT_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"in_c_format"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"out_c_format"                    },
};

/*----------------------------------------
	0x3130 MSC_Y_FIR_COEF_DATA0_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA0_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient1"                  },
};

/*----------------------------------------
	0x3134 MSC_Y_FIR_COEF_DATA1_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA1_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient3"                  },
};

/*----------------------------------------
	0x3138 MSC_Y_FIR_COEF_DATA2_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA2_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient4"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient5"                  },
};

/*----------------------------------------
	0x313c MSC_Y_FIR_COEF_DATA3_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA3_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient6"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient7"                  },
};

/*----------------------------------------
	0x3140 MSC_Y_FIR_COEF_DATA4_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA4_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient8"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient9"                  },
};

/*----------------------------------------
	0x3144 MSC_Y_FIR_COEF_DATA5_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_DATA5_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_coefficient10"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_coefficient11"                 },
};

/*----------------------------------------
	0x3148 MSC_Y_FIR_COEF_CTRL_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_Y_FIR_COEF_CTRL_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"addr"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"h_v_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"hidden_configure4"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"rnw"                             },
};

/*----------------------------------------
	0x3150 MSC_C_FIR_COEF_DATA0_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA0_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient1"                  },
};

/*----------------------------------------
	0x3154 MSC_C_FIR_COEF_DATA1_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA1_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient3"                  },
};

/*----------------------------------------
	0x3158 MSC_C_FIR_COEF_DATA2_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA2_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient4"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient5"                  },
};

/*----------------------------------------
	0x315c MSC_C_FIR_COEF_DATA3_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_DATA3_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_coefficient6"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_coefficient7"                  },
};

/*----------------------------------------
	0x3160 MSC_C_FIR_COEF_CTRL_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_C_FIR_COEF_CTRL_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"addr"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"h_v_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"rnw"                             },
};

/*----------------------------------------
	0x3168 MSC_STATUS_REV_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_STATUS_REV_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_status"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_status"                        },
};

/*----------------------------------------
	0x316c MSC_MANUAL_ROAD_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_MANUAL_ROAD_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"update_input_frm_size"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"update_wout_size"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update_win_offset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"update_win_size"                 },
};

/*----------------------------------------
	0x3170 MSC_WOUT_OFFSET_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_WOUT_OFFSET_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"wout_v_offset"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"wout_h_offset"                   },
};

/*----------------------------------------
	0x3174 MSC_CHROMA_TEAR_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_CHROMA_TEAR_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"tearing_count_result"            },
};

/*----------------------------------------
	0x3178 MSC_CHROMA_TEAR_CTRL_R
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_CHROMA_TEAR_CTRL_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"auto_chroma_filter_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"vsc_chroma_pre_filter_en"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vsc_chroma_median_filter_en"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"manual_chroma_pre_filter_on"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"manual_chroma_median_filter_on"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"detect_level_th"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"tearing_count_th"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"frame_count_th"                  },
};

/*----------------------------------------
	0x3180 MSC_MIN_MAX_CTRL_R_Y
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_MIN_MAX_CTRL_R_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"min_max_filter_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"h_filter_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,4  ,"min_max_th"                      },
};

/*----------------------------------------
	0x3184 MSC_MIN_MAX_CTRL_R_C
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSC_MIN_MAX_CTRL_R_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"min_max_filter_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"h_filter_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,4  ,"min_max_th"                      },
};

/*----------------------------------------
	0x3190 MSR_MANUAL_SAMPLING_Y_H
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSR_MANUAL_SAMPLING_Y_H[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

/*----------------------------------------
	0x3194 MSR_MANUAL_SAMPLING_Y_V
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSR_MANUAL_SAMPLING_Y_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

/*----------------------------------------
	0x3198 MSR_MANUAL_SAMPLING_C_H
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSR_MANUAL_SAMPLING_C_H[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

/*----------------------------------------
	0x319c MSR_MANUAL_SAMPLING_C_V
----------------------------------------*/
const DBG_REG_FIELD_T dbg_MSR_MANUAL_SAMPLING_C_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"numerator"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"denominator"                     },
};

DBG_REG_T gDbgRegMSC[] = {
	{ 0x1100 ,N_FLD(dbg_MSC_CTRL_L)                  ,"MSC_CTRL_L"                    ,dbg_MSC_CTRL_L                  },
	{ 0x1104 ,N_FLD(dbg_MSC_Y_INIT_POS_H_L)          ,"MSC_Y_INIT_POS_H_L"            ,dbg_MSC_Y_INIT_POS_H_L          },
	{ 0x1108 ,N_FLD(dbg_MSC_Y_INIT_POS_V_L)          ,"MSC_Y_INIT_POS_V_L"            ,dbg_MSC_Y_INIT_POS_V_L          },
	{ 0x110c ,N_FLD(dbg_MSC_C_INIT_POS_H_L)          ,"MSC_C_INIT_POS_H_L"            ,dbg_MSC_C_INIT_POS_H_L          },
	{ 0x1110 ,N_FLD(dbg_MSC_C_INIT_POS_V_L)          ,"MSC_C_INIT_POS_V_L"            ,dbg_MSC_C_INIT_POS_V_L          },
	{ 0x1114 ,N_FLD(dbg_MSC_ADAPTIVE_TH_L)           ,"MSC_ADAPTIVE_TH_L"             ,dbg_MSC_ADAPTIVE_TH_L           },
	{ 0x1118 ,N_FLD(dbg_MSC_SCR_SIZE_L)              ,"MSC_SCR_SIZE_L"                ,dbg_MSC_SCR_SIZE_L              },
	{ 0x111c ,N_FLD(dbg_MSC_WIN_OUT_SIZE_L)          ,"MSC_WIN_OUT_SIZE_L"            ,dbg_MSC_WIN_OUT_SIZE_L          },
	{ 0x1120 ,N_FLD(dbg_MSC_WIN_IN_OFFSET_L)         ,"MSC_WIN_IN_OFFSET_L"           ,dbg_MSC_WIN_IN_OFFSET_L         },
	{ 0x1124 ,N_FLD(dbg_MSC_WIN_IN_SIZE_L)           ,"MSC_WIN_IN_SIZE_L"             ,dbg_MSC_WIN_IN_SIZE_L           },
	{ 0x1128 ,N_FLD(dbg_MSC_C_FORMAT_L)              ,"MSC_C_FORMAT_L"                ,dbg_MSC_C_FORMAT_L              },
	{ 0x1130 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA0_L)      ,"MSC_Y_FIR_COEF_DATA0_L"        ,dbg_MSC_Y_FIR_COEF_DATA0_L      },
	{ 0x1134 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA1_L)      ,"MSC_Y_FIR_COEF_DATA1_L"        ,dbg_MSC_Y_FIR_COEF_DATA1_L      },
	{ 0x1138 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA2_L)      ,"MSC_Y_FIR_COEF_DATA2_L"        ,dbg_MSC_Y_FIR_COEF_DATA2_L      },
	{ 0x113c ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA3_L)      ,"MSC_Y_FIR_COEF_DATA3_L"        ,dbg_MSC_Y_FIR_COEF_DATA3_L      },
	{ 0x1140 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA4_L)      ,"MSC_Y_FIR_COEF_DATA4_L"        ,dbg_MSC_Y_FIR_COEF_DATA4_L      },
	{ 0x1144 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA5_L)      ,"MSC_Y_FIR_COEF_DATA5_L"        ,dbg_MSC_Y_FIR_COEF_DATA5_L      },
	{ 0x1148 ,N_FLD(dbg_MSC_Y_FIR_COEF_CTRL_L)       ,"MSC_Y_FIR_COEF_CTRL_L"         ,dbg_MSC_Y_FIR_COEF_CTRL_L       },
	{ 0x1150 ,N_FLD(dbg_MSC_C_FIR_COEF_DATA0_L)      ,"MSC_C_FIR_COEF_DATA0_L"        ,dbg_MSC_C_FIR_COEF_DATA0_L      },
	{ 0x1154 ,N_FLD(dbg_MSC_C_FIR_COEF_DATA1_L)      ,"MSC_C_FIR_COEF_DATA1_L"        ,dbg_MSC_C_FIR_COEF_DATA1_L      },
	{ 0x1158 ,N_FLD(dbg_MSC_C_FIR_COEF_DATA2_L)      ,"MSC_C_FIR_COEF_DATA2_L"        ,dbg_MSC_C_FIR_COEF_DATA2_L      },
	{ 0x115c ,N_FLD(dbg_MSC_C_FIR_COEF_DATA3_L)      ,"MSC_C_FIR_COEF_DATA3_L"        ,dbg_MSC_C_FIR_COEF_DATA3_L      },
	{ 0x1160 ,N_FLD(dbg_MSC_C_FIR_COEF_CTRL_L)       ,"MSC_C_FIR_COEF_CTRL_L"         ,dbg_MSC_C_FIR_COEF_CTRL_L       },
	{ 0x1168 ,N_FLD(dbg_MSC_STATUS_REV_L)            ,"MSC_STATUS_REV_L"              ,dbg_MSC_STATUS_REV_L            },
	{ 0x116c ,N_FLD(dbg_MSC_MANUAL_LOAD_L)           ,"MSC_MANUAL_LOAD_L"             ,dbg_MSC_MANUAL_LOAD_L           },
	{ 0x1170 ,N_FLD(dbg_MSC_WOUT_OFFSET_L)           ,"MSC_WOUT_OFFSET_L"             ,dbg_MSC_WOUT_OFFSET_L           },
	{ 0x1174 ,N_FLD(dbg_MSC_CHROMA_TEAR_L)           ,"MSC_CHROMA_TEAR_L"             ,dbg_MSC_CHROMA_TEAR_L           },
	{ 0x1178 ,N_FLD(dbg_MSC_CHROMA_TEAR_CTRL_L)      ,"MSC_CHROMA_TEAR_CTRL_L"        ,dbg_MSC_CHROMA_TEAR_CTRL_L      },
	{ 0x1180 ,N_FLD(dbg_MSC_MIN_MAX_CTRL_L_Y)        ,"MSC_MIN_MAX_CTRL_L_Y"          ,dbg_MSC_MIN_MAX_CTRL_L_Y        },
	{ 0x1184 ,N_FLD(dbg_MSC_MIN_MAX_CTRL_L_C)        ,"MSC_MIN_MAX_CTRL_L_C"          ,dbg_MSC_MIN_MAX_CTRL_L_C        },
	{ 0x1190 ,N_FLD(dbg_MSL_MANUAL_SAMPLING_Y_H)     ,"MSL_MANUAL_SAMPLING_Y_H"       ,dbg_MSL_MANUAL_SAMPLING_Y_H     },
	{ 0x1194 ,N_FLD(dbg_MSL_MANUAL_SAMPLING_Y_V)     ,"MSL_MANUAL_SAMPLING_Y_V"       ,dbg_MSL_MANUAL_SAMPLING_Y_V     },
	{ 0x1198 ,N_FLD(dbg_MSL_MANUAL_SAMPLING_C_H)     ,"MSL_MANUAL_SAMPLING_C_H"       ,dbg_MSL_MANUAL_SAMPLING_C_H     },
	{ 0x119c ,N_FLD(dbg_MSL_MANUAL_SAMPLING_C_V)     ,"MSL_MANUAL_SAMPLING_C_V"       ,dbg_MSL_MANUAL_SAMPLING_C_V     },
	{ 0x3100 ,N_FLD(dbg_MSC_CTRL_R)                  ,"MSC_CTRL_R"                    ,dbg_MSC_CTRL_R                  },
	{ 0x3104 ,N_FLD(dbg_MSC_Y_INIT_POS_H_R)          ,"MSC_Y_INIT_POS_H_R"            ,dbg_MSC_Y_INIT_POS_H_R          },
	{ 0x3108 ,N_FLD(dbg_MSC_Y_INIT_POS_V_R)          ,"MSC_Y_INIT_POS_V_R"            ,dbg_MSC_Y_INIT_POS_V_R          },
	{ 0x310c ,N_FLD(dbg_MSC_C_INIT_POS_H_R)          ,"MSC_C_INIT_POS_H_R"            ,dbg_MSC_C_INIT_POS_H_R          },
	{ 0x3110 ,N_FLD(dbg_MSC_C_INIT_POS_V_R)          ,"MSC_C_INIT_POS_V_R"            ,dbg_MSC_C_INIT_POS_V_R          },
	{ 0x3114 ,N_FLD(dbg_MSC_ADAPTIVE_TH_R)           ,"MSC_ADAPTIVE_TH_R"             ,dbg_MSC_ADAPTIVE_TH_R           },
	{ 0x3118 ,N_FLD(dbg_MSC_SCR_SIZE_R)              ,"MSC_SCR_SIZE_R"                ,dbg_MSC_SCR_SIZE_R              },
	{ 0x311c ,N_FLD(dbg_MSC_WIN_OUT_SIZE_R)          ,"MSC_WIN_OUT_SIZE_R"            ,dbg_MSC_WIN_OUT_SIZE_R          },
	{ 0x3120 ,N_FLD(dbg_MSC_WIN_IN_OFFSET_R)         ,"MSC_WIN_IN_OFFSET_R"           ,dbg_MSC_WIN_IN_OFFSET_R         },
	{ 0x3124 ,N_FLD(dbg_MSC_WIN_IN_SIZE_R)           ,"MSC_WIN_IN_SIZE_R"             ,dbg_MSC_WIN_IN_SIZE_R           },
	{ 0x3128 ,N_FLD(dbg_MSC_C_FORMAT_R)              ,"MSC_C_FORMAT_R"                ,dbg_MSC_C_FORMAT_R              },
	{ 0x3130 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA0_R)      ,"MSC_Y_FIR_COEF_DATA0_R"        ,dbg_MSC_Y_FIR_COEF_DATA0_R      },
	{ 0x3134 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA1_R)      ,"MSC_Y_FIR_COEF_DATA1_R"        ,dbg_MSC_Y_FIR_COEF_DATA1_R      },
	{ 0x3138 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA2_R)      ,"MSC_Y_FIR_COEF_DATA2_R"        ,dbg_MSC_Y_FIR_COEF_DATA2_R      },
	{ 0x313c ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA3_R)      ,"MSC_Y_FIR_COEF_DATA3_R"        ,dbg_MSC_Y_FIR_COEF_DATA3_R      },
	{ 0x3140 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA4_R)      ,"MSC_Y_FIR_COEF_DATA4_R"        ,dbg_MSC_Y_FIR_COEF_DATA4_R      },
	{ 0x3144 ,N_FLD(dbg_MSC_Y_FIR_COEF_DATA5_R)      ,"MSC_Y_FIR_COEF_DATA5_R"        ,dbg_MSC_Y_FIR_COEF_DATA5_R      },
	{ 0x3148 ,N_FLD(dbg_MSC_Y_FIR_COEF_CTRL_R)       ,"MSC_Y_FIR_COEF_CTRL_R"         ,dbg_MSC_Y_FIR_COEF_CTRL_R       },
	{ 0x3150 ,N_FLD(dbg_MSC_C_FIR_COEF_DATA0_R)      ,"MSC_C_FIR_COEF_DATA0_R"        ,dbg_MSC_C_FIR_COEF_DATA0_R      },
	{ 0x3154 ,N_FLD(dbg_MSC_C_FIR_COEF_DATA1_R)      ,"MSC_C_FIR_COEF_DATA1_R"        ,dbg_MSC_C_FIR_COEF_DATA1_R      },
	{ 0x3158 ,N_FLD(dbg_MSC_C_FIR_COEF_DATA2_R)      ,"MSC_C_FIR_COEF_DATA2_R"        ,dbg_MSC_C_FIR_COEF_DATA2_R      },
	{ 0x315c ,N_FLD(dbg_MSC_C_FIR_COEF_DATA3_R)      ,"MSC_C_FIR_COEF_DATA3_R"        ,dbg_MSC_C_FIR_COEF_DATA3_R      },
	{ 0x3160 ,N_FLD(dbg_MSC_C_FIR_COEF_CTRL_R)       ,"MSC_C_FIR_COEF_CTRL_R"         ,dbg_MSC_C_FIR_COEF_CTRL_R       },
	{ 0x3168 ,N_FLD(dbg_MSC_STATUS_REV_R)            ,"MSC_STATUS_REV_R"              ,dbg_MSC_STATUS_REV_R            },
	{ 0x316c ,N_FLD(dbg_MSC_MANUAL_ROAD_R)           ,"MSC_MANUAL_ROAD_R"             ,dbg_MSC_MANUAL_ROAD_R           },
	{ 0x3170 ,N_FLD(dbg_MSC_WOUT_OFFSET_R)           ,"MSC_WOUT_OFFSET_R"             ,dbg_MSC_WOUT_OFFSET_R           },
	{ 0x3174 ,N_FLD(dbg_MSC_CHROMA_TEAR_R)           ,"MSC_CHROMA_TEAR_R"             ,dbg_MSC_CHROMA_TEAR_R           },
	{ 0x3178 ,N_FLD(dbg_MSC_CHROMA_TEAR_CTRL_R)      ,"MSC_CHROMA_TEAR_CTRL_R"        ,dbg_MSC_CHROMA_TEAR_CTRL_R      },
	{ 0x3180 ,N_FLD(dbg_MSC_MIN_MAX_CTRL_R_Y)        ,"MSC_MIN_MAX_CTRL_R_Y"          ,dbg_MSC_MIN_MAX_CTRL_R_Y        },
	{ 0x3184 ,N_FLD(dbg_MSC_MIN_MAX_CTRL_R_C)        ,"MSC_MIN_MAX_CTRL_R_C"          ,dbg_MSC_MIN_MAX_CTRL_R_C        },
	{ 0x3190 ,N_FLD(dbg_MSR_MANUAL_SAMPLING_Y_H)     ,"MSR_MANUAL_SAMPLING_Y_H"       ,dbg_MSR_MANUAL_SAMPLING_Y_H     },
	{ 0x3194 ,N_FLD(dbg_MSR_MANUAL_SAMPLING_Y_V)     ,"MSR_MANUAL_SAMPLING_Y_V"       ,dbg_MSR_MANUAL_SAMPLING_Y_V     },
	{ 0x3198 ,N_FLD(dbg_MSR_MANUAL_SAMPLING_C_H)     ,"MSR_MANUAL_SAMPLING_C_H"       ,dbg_MSR_MANUAL_SAMPLING_C_H     },
	{ 0x319c ,N_FLD(dbg_MSR_MANUAL_SAMPLING_C_V)     ,"MSR_MANUAL_SAMPLING_C_V"       ,dbg_MSR_MANUAL_SAMPLING_C_V     },
	{ 0 , } // end marker
};

#endif
