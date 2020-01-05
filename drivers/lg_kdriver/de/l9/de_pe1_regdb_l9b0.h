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

#ifndef _DBG_PE1_h
#define _DBG_PE1_h

/*--------------------------------------------
	0x1300 PE1_L_TOP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TOP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load_time"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"load_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"load_type"                       },
};

/*--------------------------------------------
	0x1304 PE1_L_TOP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TOP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"width"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"height"                          },
};

/*--------------------------------------------
	0x1308 PE1_L_TOP_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TOP_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tpg_positon"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"chroma_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"disp_active_mux"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"async_delay_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,8  ,"vdpulse_pos"                     },
};

/*--------------------------------------------
	0x130c PE1_L_TOP_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TOP_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"vcnt"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"va_pe1_in"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"va_pe1_out"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"stat_tpg"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"stat_gt"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"stat_crg_lsr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"stat_crg_shp"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"stat_dce"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"stat_cen"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"stat_wb"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"stat_gmc"                        },
};

/*--------------------------------------------
	0x1320 PE1_L_WIN1_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN1_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"win_outside"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"win_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"bdr_alpha"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"bdr_wid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"bdr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"cr5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,21 ,"cb5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,26 ,"yy6"                             },
};

/*--------------------------------------------
	0x1324 PE1_L_WIN1_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN1_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x1328 PE1_L_WIN1_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN1_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x132c PE1_L_WIN1_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN1_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x1330 PE1_L_WIN1_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN1_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y1"                       },
};

/*--------------------------------------------
	0x1334 PE1_L_WIN2_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN2_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"win_outside"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"win_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"bdr_alpha"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"bdr_wid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"bdr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"cr5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,21 ,"cb5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,26 ,"yy6"                             },
};

/*--------------------------------------------
	0x1338 PE1_L_WIN2_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN2_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x133c PE1_L_WIN2_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN2_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x1340 PE1_L_WIN2_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN2_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x1344 PE1_L_WIN2_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN2_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y1"                       },
};

/*--------------------------------------------
	0x1350 PE1_L_APL_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"apl_win_ctrl_x0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"apl_win_ctrl_y0"                 },
};

/*--------------------------------------------
	0x1354 PE1_L_APL_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"apl_win_ctrl_x1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"apl_win_ctrl_y1"                 },
};

/*--------------------------------------------
	0x1358 PE1_L_APL_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"apl_position"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"apl_y_type"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"act_win_mode"                    },
};

/*--------------------------------------------
	0x135c PE1_L_APL_STAT_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_y"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"apl_rgb"                         },
};

/*--------------------------------------------
	0x1360 PE1_L_APL_STAT_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_b"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"apl_g"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"apl_r"                           },
};

/*--------------------------------------------
	0x1364 PE1_L_APL_STAT_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_STAT_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_y_other_side"                },
};

/*--------------------------------------------
	0x1368 PE1_L_APL_STAT_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_STAT_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_b_other_side"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"apl_g_other_side"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"apl_r_other_side"                },
};

/*--------------------------------------------
	0x1370 PE1_L_TPG_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tpg_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pattern_type"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"blend_alpha"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,8  ,"blt_size_x"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"blt_size_y"                      },
};

/*--------------------------------------------
	0x1374 PE1_L_TPG_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"gradation_stride"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"gradation_direction"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"gradation_bar_en"                },
};

/*--------------------------------------------
	0x1378 PE1_L_TPG_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"patch_en"                        },
};

/*--------------------------------------------
	0x137c PE1_L_TPG_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"patch_inout_sel"                 },
};

/*--------------------------------------------
	0x1380 PE1_L_TPG_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"bg_color_r"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"bg_color_b"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"bg_color_g"                      },
};

/*--------------------------------------------
	0x1384 PE1_L_TPG_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"tpg_indir_addr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"tpg_indir_ai_en"                 },
};

/*--------------------------------------------
	0x1388 PE1_L_TPG_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"tpg_indir_data"                  },
};

/*--------------------------------------------
	0x13a0 PE1_L_FILM_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_FILM_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vignetting_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"film_contrast_enable"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"contrast_alpha"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"contrast_delta_max"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vignetting_gain"                 },
};

/*--------------------------------------------
	0x13a4 PE1_L_FILM_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_FILM_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"noise_gen_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"noise_frame_rate"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"noise_size"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"noise_gain"                      },
};

/*--------------------------------------------
	0x13a8 PE1_L_FILM_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_FILM_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"tone_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"tone_offset"                     },
};

/*--------------------------------------------
	0x13b0 PE1_L_WIN3_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN3_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"win_outside"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"win_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"bdr_alpha"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"bdr_wid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"bdr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"cr5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,21 ,"cb5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,26 ,"yy6"                             },
};

/*--------------------------------------------
	0x13b4 PE1_L_WIN3_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN3_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x13b8 PE1_L_WIN3_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN3_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x13bc PE1_L_WIN3_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN3_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x13c0 PE1_L_WIN3_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN3_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y1"                       },
};

/*--------------------------------------------
	0x13d0 PE1_L_DERH_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vsum_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"hsum_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vsum121_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"vertical_min_max"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"a_flt_mux"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"a_e_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"t_mux"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"a_gen_width"                     },
};

/*--------------------------------------------
	0x13d4 PE1_L_DERH_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"a_gen_of_y"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"a_gen_of_c"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"avg_flt_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"avg_flt_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"max_flt_mode"                    },
};

/*--------------------------------------------
	0x13d8 PE1_L_DERH_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"a_exp_gain_ctrl_y0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"a_exp2_gain_ctrl_x0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"a_exp2_gain_ctrl_y1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"a_exp2_gain_ctrl_x1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"a_avg2_flt_wid"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"a_avg2_flt_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"a_exp_max2_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"y_sum_mode"                      },
};

/*--------------------------------------------
	0x13dc PE1_L_DERH_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"a_mux_for_edge_gaintable"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"a_mux_for_detail_filter"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"a_mux_for_edge_filter"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"a_scaling_flat_filter"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"a_mux_for_flat_filter"           },
};

/*--------------------------------------------
	0x13e0 PE1_L_DERH_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dbg_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"sum_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"enh_en_cc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"enh_en_yy"                       },
};

/*--------------------------------------------
	0x13e4 PE1_L_DERH_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vmm_param"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"csft_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"th_gain_edge"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"th_gain_flat"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"th_manual_th"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"th_manual_en"                    },
};

/*--------------------------------------------
	0x13e8 PE1_L_DERH_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"edge_filter_white_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"edge_filter_black_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"amean_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"edge_filter_v_tap"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edge_c_filter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"edge_y_filter_en"                },
};

/*--------------------------------------------
	0x13ec PE1_L_DERH_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"flat_filter_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"flat_filter_en"                  },
};

/*--------------------------------------------
	0x13f0 PE1_L_DERH_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl0_y0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl0_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"amod_ctrl0_y1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"amod_ctrl0_x1"                   },
};

/*--------------------------------------------
	0x13f4 PE1_L_DERH_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl1_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl1_x1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"y_c_mux_control"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,19 ,"chroma_weight"                   },
};

/*--------------------------------------------
	0x1400 PE1_L_DERV_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERV_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"der_v_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"der_gain_mapping"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"bif_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"output_mux"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"bif_manual_th"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"th_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"th_mode"                         },
};

/*--------------------------------------------
	0x1404 PE1_L_DERV_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERV_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"csft_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"csft_mode"                       },
};

/*--------------------------------------------
	0x1408 PE1_L_DERV_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERV_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"mmd_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"max_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"avg_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain_th1"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"gain_th2"                        },
};

/*--------------------------------------------
	0x140c PE1_L_DERV_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERV_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"gain_b"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"gain_w"                          },
};

/*--------------------------------------------
	0x1410 PE1_L_DP_CTRL_00
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1414 PE1_L_DP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"edge_gain_b"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"edge_gain_w"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"texture_gain_b"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"texture_gain_w"                  },
};

/*--------------------------------------------
	0x1418 PE1_L_DP_CTRL_02
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x141c PE1_L_DP_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1420 PE1_L_CORING_STAT_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"tm_h"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"tm_v"                            },
};

/*--------------------------------------------
	0x1424 PE1_L_CORING_STAT_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"tm_h"                            },
};

/*--------------------------------------------
	0x1428 PE1_L_CORING_STAT_02
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x142c PE1_L_CORING_STAT_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1470 PE1_L_DERH_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"a2g_mode_e"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"a2g_mode_f"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"a2g_mgain_e"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"a2g_mgain_f"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"debug_mode"                      },
};

/*--------------------------------------------
	0x1474 PE1_L_DERH_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"e_gain_th1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"e_gain_th2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"f_gain_th1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"f_gain_th2"                      },
};

/*--------------------------------------------
	0x1478 PE1_L_DERH_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DERH_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"e_gain_max"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"f_gain_max"                      },
};

/*--------------------------------------------
	0x147c PE1_L_DERH_CTRL_0D
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1490 PE1_L_SP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edge_enhance_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"edge_operator_selection"         },
};

/*--------------------------------------------
	0x1494 PE1_L_SP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vertical_gain"                   },
};

/*--------------------------------------------
	0x1498 PE1_L_SP_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sobel_weight"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"laplacian_weight"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sobel_manual_mode_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x149c PE1_L_SP_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x14a0 PE1_L_SP_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"display_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gx_weight_manual_mode"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gx_weight_manual_gain"           },
};

/*--------------------------------------------
	0x14a8 PE1_L_SP_CTRL_05
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x14ac PE1_L_SP_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"lap_h_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"lap_v_mode"                      },
};

/*--------------------------------------------
	0x14b0 PE1_L_SP_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gb_mode"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y1"                           },
};

/*--------------------------------------------
	0x14b4 PE1_L_SP_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gb_x2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y3"                           },
};

/*--------------------------------------------
	0x14b8 PE1_L_SP_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_x_l0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum1_x_h1"                       },
};

/*--------------------------------------------
	0x14bc PE1_L_SP_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_y0"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_y2"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_x_l0"                       },
};

/*--------------------------------------------
	0x14c0 PE1_L_SP_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum2_x_h1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_y0"                         },
};

/*--------------------------------------------
	0x14c4 PE1_L_SP_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SP_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_y2"                         },
};

/*--------------------------------------------
	0x14d0 PE1_L_DEBUG_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DEBUG_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_debug_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"show_sqm2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,10 ,"sqm2_debug_image"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,15 ,"show_bbd"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"bbd_line_width"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"show_apl"                        },
};

/*--------------------------------------------
	0x14d4 PE1_L_DEBUG_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DEBUG_CTRL_01[] = {
};

/*--------------------------------------------
	0x14f0 PE1_L_MP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edge_enhance_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"edge_operator_selection"         },
};

/*--------------------------------------------
	0x14f4 PE1_L_MP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vertical_gain"                   },
};

/*--------------------------------------------
	0x14f8 PE1_L_MP_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sobel_weight"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"laplacian_weight"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sobel_manual_mode_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x14fc PE1_L_MP_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1500 PE1_L_MP_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"display_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gx_weight_manual_mode"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gx_weight_manual_gain"           },
};

/*--------------------------------------------
	0x1508 PE1_L_MP_CTRL_05
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x150c PE1_L_MP_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"lap_h_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"lap_v_mode"                      },
};

/*--------------------------------------------
	0x1510 PE1_L_MP_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gb_mode"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y1"                           },
};

/*--------------------------------------------
	0x1514 PE1_L_MP_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gb_x2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y3"                           },
};

/*--------------------------------------------
	0x1518 PE1_L_MP_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_x_l0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum1_x_h1"                       },
};

/*--------------------------------------------
	0x151c PE1_L_MP_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_y0"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_y2"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_x_l0"                       },
};

/*--------------------------------------------
	0x1520 PE1_L_MP_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum2_x_h1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_y0"                         },
};

/*--------------------------------------------
	0x1524 PE1_L_MP_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_MP_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_y2"                         },
};

/*--------------------------------------------
	0x1530 PE1_L_CTI_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CTI_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"tap_size"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cti_gain"                        },
};

/*--------------------------------------------
	0x1534 PE1_L_CTI_CTRL_01
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1538 PE1_L_CTI_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CTI_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ycm_en0"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"ycm_en1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"ycm_band_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ycm_diff_th"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"ycm_y_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"ycm_c_gain"                      },
};

/*--------------------------------------------
	0x1550 PE1_L_BLUR_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BLUR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"coring_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"direction"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_min"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_max"                      },
};

/*--------------------------------------------
	0x1560 PE1_L_CORING_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"ga_max"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ga_th0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ga_th1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"amap1_sel"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"amap2_sel"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"edge_a_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"debug_a_sel"                     },
};

/*--------------------------------------------
	0x1564 PE1_L_CORING_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"max_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"avg_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"a2tw_min"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"a2tw_th0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"a2tw_th1"                        },
};

/*--------------------------------------------
	0x1568 PE1_L_CORING_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"nrv_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"nrv_th1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"nrv_th2"                         },
};

/*--------------------------------------------
	0x156c PE1_L_CORING_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"nrh_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"nrh_th1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"nrh_th2"                         },
};

/*--------------------------------------------
	0x1570 PE1_L_CORING_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"dflt_sel"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,4  ,"var_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"coring_mode1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"coring_mode2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"ac_direction"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"tflt_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"exp_mode"                        },
};

/*--------------------------------------------
	0x1574 PE1_L_CORING_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"gt_max"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gt_th0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gt_th1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"a2tw_en"                         },
};

/*--------------------------------------------
	0x1578 PE1_L_CORING_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gt_th0a"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gt_th0b"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"gt_gain0a"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"gt_gain0b"                       },
};

/*--------------------------------------------
	0x157c PE1_L_CORING_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"g_th0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"g_th1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"amap_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"tmap_gain"                       },
};

/*--------------------------------------------
	0x1580 PE1_L_CORING_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"mp_coring_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"sp_coring_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mp_coring_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"sp_coring_en"                    },
};

/*--------------------------------------------
	0x1584 PE1_L_CORING_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CORING_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"edge_gain_b"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"edge_gain_w"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"texture_gain_b"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"texture_gain_w"                  },
};

/*--------------------------------------------
	0x1590 PE1_L_DJ_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DJ_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edf_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"hv_filter_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"g0_feature_norm_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"g0_f2g_mapping_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"line_variation_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"l_type_protection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"center_blur_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"direction_type_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"count_diff_th"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"output_mux"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"n_avg_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"line_variation_diff_threshold"   },
};

/*--------------------------------------------
	0x1594 PE1_L_DJ_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DJ_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"level_th"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"protect_th"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"n_avg_gain"                      },
};

/*--------------------------------------------
	0x1598 PE1_L_DJ_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DJ_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"edf_count_min"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"edf_count_max"                   },
};

/*--------------------------------------------
	0x159c PE1_L_DJ_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DJ_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"dj_h_count_min"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"dj_h_count_max"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"dj_v_count_min"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,25 ,"dj_v_count_max"                  },
};

/*--------------------------------------------
	0x15a0 PE1_L_LEVEL_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LEVEL_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,4  ,"y_offset"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"y_gain"                          },
};

/*--------------------------------------------
	0x15a4 PE1_L_VSPYC_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_VSPYC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"graycolor_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"color_only_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cb_info"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cr_info"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"contrast"                        },
};

/*--------------------------------------------
	0x15a8 PE1_L_VSPYC_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_VSPYC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"brightness"                      },
};

/*--------------------------------------------
	0x15b0 PE1_L_VSPRGB_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_VSPRGB_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"contrast"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"brightness"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"enable"                          },
};

/*--------------------------------------------
	0x15c0 PE1_L_XVY_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"outputcsc_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"degamma_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pcc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"gamma_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"scaler_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"hsv_hsl_selection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"s_adpative_scaler_enable"        },
};

/*--------------------------------------------
	0x15c4 PE1_L_XVY_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef0"                     },
};

/*--------------------------------------------
	0x15c8 PE1_L_XVY_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef2"                     },
};

/*--------------------------------------------
	0x15cc PE1_L_XVY_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef5"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef4"                     },
};

/*--------------------------------------------
	0x15d0 PE1_L_XVY_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef7"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef6"                     },
};

/*--------------------------------------------
	0x15d4 PE1_L_XVY_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"r_csc_ofst0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef8"                     },
};

/*--------------------------------------------
	0x15d8 PE1_L_XVY_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"r_csc_ofst2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"r_csc_ofst1"                     },
};

/*--------------------------------------------
	0x15dc PE1_L_XVY_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"r_csc_ofst4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"r_csc_ofst3"                     },
};

/*--------------------------------------------
	0x15e0 PE1_L_XVY_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"r_csc_ofst5"                     },
};

/*--------------------------------------------
	0x15e4 PE1_L_XVY_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef1"                     },
};

/*--------------------------------------------
	0x15e8 PE1_L_XVY_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef3"                     },
};

/*--------------------------------------------
	0x15ec PE1_L_XVY_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef6"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef5"                     },
};

/*--------------------------------------------
	0x15f0 PE1_L_XVY_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef8"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef7"                     },
};

/*--------------------------------------------
	0x15f4 PE1_L_XVY_CTRL_0D
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_0D[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"scaler"                          },
};

/*--------------------------------------------
	0x1600 PE1_L_CEN_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CEN_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"select_hsv"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"select_rgb"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"vsp_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"global_apl_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cen_bypass"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cen_debug_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"debugging_mode_core"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"pe1_1st_core_gain_disable"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pe1_2nd_core_gain_disable"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"v_scaler_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"demo_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"win_control_mode"                },
};

/*--------------------------------------------
	0x1604 PE1_L_CEN_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CEN_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"show_color_region0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"show_color_region1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"color_region_en0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"color_region_en1"                },
};

/*--------------------------------------------
	0x1608 PE1_L_CEN_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CEN_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ihsv_sgain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ihsv_vgain"                      },
};

/*--------------------------------------------
	0x160c PE1_L_CEN_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CEN_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ihsv_hoffset"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ihsv_soffset"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ihsv_voffset"                    },
};

/*--------------------------------------------
	0x1610 PE1_L_CEN_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CEN_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"den_ctrl0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"den_apl_limit_high"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"den_gain"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"den_coring"                      },
};

/*--------------------------------------------
	0x1614 PE1_L_CEN_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CEN_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_cen_address"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"hif_cen_ai_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_cen_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_cen_enable"                  },
};

/*--------------------------------------------
	0x1618 PE1_L_CEN_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CEN_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_cen_y_wdata"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_cen_x_wdata"                 },
};

/*--------------------------------------------
	0x1630 PE1_L_LRCR_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"adjust_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"protection_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"adjust_en2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"r_hist_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"l_hist_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"r_proc_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"l_proc_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"ff_mode_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"ff_mode_parity"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"r_out_data_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"l_out_data_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"lrcr_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"hist_rd_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"hist_mode"                       },
};

/*--------------------------------------------
	0x1634 PE1_L_LRCR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"th_max_hist"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"th_valid_bins"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"th1"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"th0"                             },
};

/*--------------------------------------------
	0x1638 PE1_L_LRCR_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"hist_l_window_h_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hist_l_window_h_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"hist_l_window_v_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hist_l_window_v_en"              },
};

/*--------------------------------------------
	0x163c PE1_L_LRCR_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x1640 PE1_L_LRCR_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"hist_r_window_h_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hist_r_window_h_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"hist_r_window_v_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hist_r_window_v_en"              },
};

/*--------------------------------------------
	0x1644 PE1_L_LRCR_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x1648 PE1_L_LRCR_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"active_window_h_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"active_window_h_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"active_window_v_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"active_window_v_en"              },
};

/*--------------------------------------------
	0x164c PE1_L_LRCR_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x1650 PE1_L_LRCR_STAT_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_hist"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"n_valid_bins"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cdf_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cdf_x0"                          },
};

/*--------------------------------------------
	0x1654 PE1_L_LRCR_STAT_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_hist"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"n_valid_bins"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cdf_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cdf_x0"                          },
};

/*--------------------------------------------
	0x1658 PE1_L_LRCR_STAT_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_STAT_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_hist"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"n_valid_bins"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cdf_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cdf_x0"                          },
};

/*--------------------------------------------
	0x1670 PE1_L_DCE_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dynamic_contrast_en"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"hist_bin_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"hist_clear"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"window_mode_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"window_acquire"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"color_region0_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"color_region1_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"color_region2_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"color_region3_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"color_region4_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"color_region5_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"color_region6_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"color_region7_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"color_region8_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"color_region9_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"color_region10_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"color_region11_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"color_region12_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"color_region13_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"color_region14_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"color_region15_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"dce_domain_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"win_selection"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"histogram_mode"                  },
};

/*--------------------------------------------
	0x1674 PE1_L_DCE_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hist_bin_min_position"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hist_bin_max_position"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"color_region_gain"               },
};

/*--------------------------------------------
	0x1678 PE1_L_DCE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"color_region_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"color_debug_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"y_grad_gain"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cb_grad_gain"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cr_grad_gain"                    },
};

/*--------------------------------------------
	0x167c PE1_L_DCE_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_range_min"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"y_range_max"                     },
};

/*--------------------------------------------
	0x1680 PE1_L_DCE_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cb_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cb_range_max"                    },
};

/*--------------------------------------------
	0x1684 PE1_L_DCE_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cr_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cr_range_max"                    },
};

/*--------------------------------------------
	0x1688 PE1_L_DCE_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"hif_dyc_address"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hif_dce_load"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_dce_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_dce_enable"                  },
};

/*--------------------------------------------
	0x168c PE1_L_DCE_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dyc_wdata_y"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dyc_wdata_x"                 },
};

/*--------------------------------------------
	0x1690 PE1_L_DCE_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dyc_wdata_y_32nd"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dyc_wdata_x_32nd"            },
};

/*--------------------------------------------
	0x16a0 PE1_L_DCE_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DCE_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"hif_status_address"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hif_status_ai"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"hif_mask"                        },
};

/*--------------------------------------------
	0x16a4 PE1_L_DCE_HIST_IA_DATA1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x16a8 PE1_L_DCE_HSIT_IA_DATA2
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x16ac PE1_L_DSE_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DSE_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dynamic_saturation_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"window_mode_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"window_acquire"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"win_selection"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"color_region0_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"color_region1_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"color_region2_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"color_region3_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"color_region4_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"color_region5_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"color_region6_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"color_region7_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"color_region8_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"color_region9_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"color_region10_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"color_region11_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"color_region12_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"color_region13_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"color_region14_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"color_region15_sel"              },
};

/*--------------------------------------------
	0x16b0 PE1_L_DSE_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DSE_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"color_region_gain"               },
};

/*--------------------------------------------
	0x16b4 PE1_L_DSE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DSE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dse_wdata_y_32nd"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dse_wdata_x_32nd"            },
};

/*--------------------------------------------
	0x16b8 PE1_L_DSE_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DSE_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"hif_dse_address"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hif_dse_load"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_dse_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_dse_enable"                  },
};

/*--------------------------------------------
	0x16bc PE1_L_DSE_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DSE_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dse_wdata_y"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dse_wdata_x"                 },
};

/*--------------------------------------------
	0x16c0 PE1_L_WB_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WB_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"wb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"gamma_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"degamma_en"                      },
};

/*--------------------------------------------
	0x16c4 PE1_L_WB_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WB_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"user_ctrl_g_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctrl_b_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"user_ctrl_r_gain"                },
};

/*--------------------------------------------
	0x16c8 PE1_L_WB_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WB_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"user_ctrl_g_offset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctrl_b_offset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"user_ctrl_r_offset"              },
};

/*--------------------------------------------
	0x16f0 PE1_L_GMC_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_GMC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pxl_rep_xpos"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"lut_wmask_g"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"lut_wmask_b"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"lut_wmask_r"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pxl_rep_area"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pxl_rep_ypos"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pxl_rep_disable_g"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"pxl_rep_disable_b"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"pxl_rep_disable_r"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pxl_rep_enable"                  },
};

/*--------------------------------------------
	0x16f4 PE1_L_GMC_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_GMC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pxl_rep_width"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pxl_rep_height"                  },
};

/*--------------------------------------------
	0x16f8 PE1_L_GMC_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_GMC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"pxl_rep_value_g"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"pxl_rep_value_b"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"pxl_rep_value_r"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"gmc_mode"                        },
};

/*--------------------------------------------
	0x16fc PE1_L_GMC_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_GMC_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"capture_addr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"capture_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"capture_num"                     },
};

/*--------------------------------------------
	0x1700 PE1_L_GMC_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_GMC_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"lut_data_g"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"lut_data_b"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"lut_data_r"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"capture_stat_started"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"capture_stat_ended"              },
};

/*--------------------------------------------
	0x1704 PE1_L_GMC_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_GMC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dither_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"decontour_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"dither_random_freeze_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"demo_pattern_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"bit_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"decontour_gain_r"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"decontour_gain_g"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"decontour_gain_b"                },
};

/*--------------------------------------------
	0x1720 PE1_L_SQM_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"outmux_debugmap"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"iir"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"i_score"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"v_score"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"l_score"                         },
};

/*--------------------------------------------
	0x1724 PE1_L_SQM_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"v_limit"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"l_limit"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"score_threshold"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"flat_threshold"                  },
};

/*--------------------------------------------
	0x1728 PE1_L_SQM_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_y0"                          },
};

/*--------------------------------------------
	0x172c PE1_L_SQM_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_y1"                          },
};

/*--------------------------------------------
	0x1730 PE1_L_SQM_CTRL_4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"charcter_delta_limit"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"boundary_width"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"video_height"                    },
};

/*--------------------------------------------
	0x1734 PE1_L_SQM_CTRL_5
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pc_threshold"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"pc_delta_limit"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"pc_pixel_minimal_limit"          },
};

/*--------------------------------------------
	0x1738 PE1_L_SQM_STAT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_STAT[] = {
};

/*--------------------------------------------
	0x1750 PE1_L_BBD2D_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD2D_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"black_boundary_detection_enable" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"hysterisis_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"mode_selection"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cnt_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"diff_th"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vcnt"                            },
};

/*--------------------------------------------
	0x1754 PE1_L_BBD2D_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD2D_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y0"                          },
};

/*--------------------------------------------
	0x1758 PE1_L_BBD2D_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD2D_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y1"                          },
};

/*--------------------------------------------
	0x175c PE1_L_BBD2D_STAT_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD2D_STAT_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
};

/*--------------------------------------------
	0x1760 PE1_L_BBD2D_STAT_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD2D_STAT_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x1770 PE1_L_BBD3D_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD3D_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"black_boundary_detection_enable" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"hysterisis_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"pe1_3d_type"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"mode_selection"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cnt_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"diff_th"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vcnt"                            },
};

/*--------------------------------------------
	0x1774 PE1_L_BBD3D_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD3D_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"bbd_read_control"                },
};

/*--------------------------------------------
	0x1778 PE1_L_BBD3D_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD3D_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y1"                          },
};

/*--------------------------------------------
	0x177c PE1_L_BBD3D_STAT_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_BBD3D_STAT_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y"                               },
};

/*--------------------------------------------
	0x1790 PE1_WCP_CTRL_00
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1794 PE1_WCP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_WCP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"win_color_nact_cr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"win_color_nact_cb"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"win_color_nact_yy"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"win_color_dark_cr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"win_color_dark_cb"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"win_color_dark_yy"               },
};

/*--------------------------------------------
	0x1798 PE1_WCP_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_WCP_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"w0_blend_alpha"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"w1_blend_alpha"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"w0_blend_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"w1_blend_en"                     },
};

/*--------------------------------------------
	0x179c PE1_WCP_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_WCP_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"w0_imux_ctrl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"w0_dark_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"w1_imux_ctrl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"w1_dark_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osync_mux"                       },
};

/*--------------------------------------------
	0x17a0 PE1_WCP_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_WCP_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"palpha_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"palpha_reverse"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"palpha_clip_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ckey_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"ckey_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cc_reverse"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"yy_reverse"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ckey_th_yy1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ckey_th_yy0"                     },
};

/*--------------------------------------------
	0x17a4 PE1_WCP_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_WCP_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ckey_th_cr1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ckey_th_cr0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ckey_th_cb1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ckey_th_cb0"                     },
};

/*--------------------------------------------
	0x17a8 PE1_WCP_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_WCP_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cc_reverse_th_yy1"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cc_reverse_th_yy0"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,14 ,"cc_reverse_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"yy_reverse_th_cr"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"yy_reverse_th_cb"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"yy_reverse_mode"                 },
};

/*--------------------------------------------
	0x17b0 P1L_PE1_L_G_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1L_PE1_L_G_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_g_available"             },
};

/*--------------------------------------------
	0x17b4 P1L_PE1_L_G_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x17b8 P1L_PE1_L_B_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1L_PE1_L_B_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_b_available"             },
};

/*--------------------------------------------
	0x17bc P1L_PE1_L_B_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x17c0 P1L_PE1_L_R_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1L_PE1_L_R_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_r_available"             },
};

/*--------------------------------------------
	0x17c4 P1L_PE1_L_R_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x17c8 P1L_PE1_R_G_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1L_PE1_R_G_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_g_available"             },
};

/*--------------------------------------------
	0x17cc P1L_PE1_R_G_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x17d0 P1L_PE1_R_B_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1L_PE1_R_B_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_b_available"             },
};

/*--------------------------------------------
	0x17d4 P1L_PE1_R_B_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x17d8 P1L_PE1_R_R_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1L_PE1_R_R_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_r_available"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hist_rd_done"                    },
};

/*--------------------------------------------
	0x17dc P1L_PE1_R_R_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3300 PE1_R_TOP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TOP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load_time"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"load_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"load_type"                       },
};

/*--------------------------------------------
	0x3304 PE1_R_TOP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TOP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"width"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"height"                          },
};

/*--------------------------------------------
	0x3308 PE1_R_TOP_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TOP_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tpg_positon"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"chroma_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"disp_active_mux"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"async_delay_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,8  ,"vdpulse_pos"                     },
};

/*--------------------------------------------
	0x330c PE1_R_TOP_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TOP_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"vcnt"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"va_pe1_in"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"va_pe1_out"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"stat_tpg"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"stat_gt"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"stat_crg_lsr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"stat_crg_shp"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"stat_dce"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"stat_cen"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"stat_wb"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"stat_gmc"                        },
};

/*--------------------------------------------
	0x3320 PE1_R_WIN1_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN1_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"win_outside"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"win_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"bdr_alpha"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"bdr_wid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"bdr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"cr5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,21 ,"cb5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,26 ,"yy6"                             },
};

/*--------------------------------------------
	0x3324 PE1_R_WIN1_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN1_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x3328 PE1_R_WIN1_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN1_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x332c PE1_R_WIN1_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN1_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x3330 PE1_R_WIN1_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN1_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y1"                       },
};

/*--------------------------------------------
	0x3334 PE1_R_WIN2_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN2_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"win_outside"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"win_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"bdr_alpha"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"bdr_wid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"bdr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"cr5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,21 ,"cb5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,26 ,"yy6"                             },
};

/*--------------------------------------------
	0x3338 PE1_R_WIN2_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN2_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x333c PE1_R_WIN2_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN2_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x3340 PE1_R_WIN2_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN2_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x3344 PE1_R_WIN2_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN2_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y1"                       },
};

/*--------------------------------------------
	0x3350 PE1_R_APL_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"apl_win_ctrl_x0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"apl_win_ctrl_y0"                 },
};

/*--------------------------------------------
	0x3354 PE1_R_APL_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"apl_win_ctrl_x1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"apl_win_ctrl_y1"                 },
};

/*--------------------------------------------
	0x3358 PE1_R_APL_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"apl_position"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"apl_y_type"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"act_win_mode"                    },
};

/*--------------------------------------------
	0x335c PE1_R_APL_STAT_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_y"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"apl_rgb"                         },
};

/*--------------------------------------------
	0x3360 PE1_R_APL_STAT_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_b"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"apl_g"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"apl_r"                           },
};

/*--------------------------------------------
	0x3364 PE1_R_APL_STAT_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_STAT_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_y_other_side"                },
};

/*--------------------------------------------
	0x3368 PE1_R_APL_STAT_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_STAT_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_b_other_side"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"apl_g_other_side"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"apl_r_other_side"                },
};

/*--------------------------------------------
	0x33a0 PE1_R_FILM_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_FILM_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vignetting_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"film_contrast_enable"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"contrast_alpha"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"contrast_delta_max"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vignetting_gain"                 },
};

/*--------------------------------------------
	0x33a4 PE1_R_FILM_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_FILM_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"noise_gen_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"noise_frame_rate"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"noise_size"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"noise_gain"                      },
};

/*--------------------------------------------
	0x33a8 PE1_R_FILM_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_FILM_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"tone_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"tone_offset"                     },
};

/*--------------------------------------------
	0x33b0 PE1_R_WIN3_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN3_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"win_outside"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"win_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"bdr_alpha"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"bdr_wid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"bdr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"cr5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,21 ,"cb5"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,26 ,"yy6"                             },
};

/*--------------------------------------------
	0x33b4 PE1_R_WIN3_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN3_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x33b8 PE1_R_WIN3_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN3_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x33bc PE1_R_WIN3_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN3_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x33c0 PE1_R_WIN3_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN3_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y1"                       },
};

/*--------------------------------------------
	0x33d0 PE1_R_DERH_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vsum_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"hsum_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vsum121_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"vertical_min_max"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"a_flt_mux"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"a_e_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"t_mux"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"a_gen_width"                     },
};

/*--------------------------------------------
	0x33d4 PE1_R_DERH_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"a_gen_of_y"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"a_gen_of_c"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"avg_flt_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"avg_flt_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"max_flt_mode"                    },
};

/*--------------------------------------------
	0x33d8 PE1_R_DERH_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"a_exp_gain_ctrl_y0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"a_exp2_gain_ctrl_x0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"a_exp2_gain_ctrl_y1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"a_exp2_gain_ctrl_x1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"a_avg2_flt_wid"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"a_avg2_flt_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"a_exp_max2_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"y_sum_mode"                      },
};

/*--------------------------------------------
	0x33dc PE1_R_DERH_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"a_mux_for_edge_gaintable"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"a_mux_for_detail_filter"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"a_mux_for_edge_filter"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"a_scaling_flat_filter"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"a_mux_for_flat_filter"           },
};

/*--------------------------------------------
	0x33e0 PE1_R_DERH_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dbg_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"sum_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"enh_en_cc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"enh_en_yy"                       },
};

/*--------------------------------------------
	0x33e4 PE1_R_DERH_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vmm_param"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"csft_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"th_gain_edge"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"th_gain_flat"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"th_manual_th"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"th_manual_en"                    },
};

/*--------------------------------------------
	0x33e8 PE1_R_DERH_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"edge_filter_white_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"edge_filter_black_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"amean_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"edge_filter_v_tap"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edge_c_filter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"edge_y_filter_en"                },
};

/*--------------------------------------------
	0x33ec PE1_R_DERH_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"flat_filter_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"flat_filter_en"                  },
};

/*--------------------------------------------
	0x33f0 PE1_R_DERH_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl0_y0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl0_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"amod_ctrl0_y1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"amod_ctrl0_x1"                   },
};

/*--------------------------------------------
	0x33f4 PE1_R_DERH_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl1_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl1_x1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"y_c_mux_control"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,19 ,"chroma_weight"                   },
};

/*--------------------------------------------
	0x3400 PE1_R_DERV_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERV_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"der_v_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"der_gain_mapping"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"bif_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"output_mux"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"bif_manual_th"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"th_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"th_mode"                         },
};

/*--------------------------------------------
	0x3404 PE1_R_DERV_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERV_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"csft_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"csft_mode"                       },
};

/*--------------------------------------------
	0x3408 PE1_R_DERV_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERV_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"mmd_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"max_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"avg_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain_th1"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"gain_th2"                        },
};

/*--------------------------------------------
	0x340c PE1_R_DERV_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERV_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"gain_b"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"gain_w"                          },
};

/*--------------------------------------------
	0x3410 PE1_R_DP_CTRL_00
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3414 PE1_R_DP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"edge_gain_b"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"edge_gain_w"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"texture_gain_b"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"texture_gain_w"                  },
};

/*--------------------------------------------
	0x3418 PE1_R_DP_CTRL_02
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x341c PE1_R_DP_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3420 PE1_R_CORING_STAT_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"tm_h"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"tm_v"                            },
};

/*--------------------------------------------
	0x3424 PE1_R_CORING_STAT_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"tm_h"                            },
};

/*--------------------------------------------
	0x3428 PE1_R_CORING_STAT_02
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x342c PE1_R_CORING_STAT_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3470 PE1_R_DERH_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"a2g_mode_e"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"a2g_mode_f"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"a2g_mgain_e"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"a2g_mgain_f"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"debug_mode"                      },
};

/*--------------------------------------------
	0x3474 PE1_R_DERH_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"e_gain_th1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"e_gain_th2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"f_gain_th1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"f_gain_th2"                      },
};

/*--------------------------------------------
	0x3478 PE1_R_DERH_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DERH_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"e_gain_max"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"f_gain_max"                      },
};

/*--------------------------------------------
	0x347c PE1_R_DERH_CTRL_0D
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3490 PE1_R_SP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edge_enhance_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"edge_operator_selection"         },
};

/*--------------------------------------------
	0x3494 PE1_R_SP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vertical_gain"                   },
};

/*--------------------------------------------
	0x3498 PE1_R_SP_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sobel_weight"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"laplacian_weight"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sobel_manual_mode_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x349c PE1_R_SP_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x34a0 PE1_R_SP_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"display_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gx_weight_manual_mode"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gx_weight_manual_gain"           },
};

/*--------------------------------------------
	0x34a8 PE1_R_SP_CTRL_05
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x34ac PE1_R_SP_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"lap_h_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"lap_v_mode"                      },
};

/*--------------------------------------------
	0x34b0 PE1_R_SP_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gb_mode"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y1"                           },
};

/*--------------------------------------------
	0x34b4 PE1_R_SP_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gb_x2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y3"                           },
};

/*--------------------------------------------
	0x34b8 PE1_R_SP_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_x_l0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum1_x_h1"                       },
};

/*--------------------------------------------
	0x34bc PE1_R_SP_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_y0"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_y2"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_x_l0"                       },
};

/*--------------------------------------------
	0x34c0 PE1_R_SP_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum2_x_h1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_y0"                         },
};

/*--------------------------------------------
	0x34c4 PE1_R_SP_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SP_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_y2"                         },
};

/*--------------------------------------------
	0x34d0 PE1_R_DEBUG_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DEBUG_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_debug_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"show_sqm2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,10 ,"sqm2_debug_image"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,15 ,"show_bbd"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"bbd_line_width"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"show_apl"                        },
};

/*--------------------------------------------
	0x34d4 PE1_R_DEBUG_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DEBUG_CTRL_01[] = {
};

/*--------------------------------------------
	0x34f0 PE1_R_MP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edge_enhance_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"edge_operator_selection"         },
};

/*--------------------------------------------
	0x34f4 PE1_R_MP_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vertical_gain"                   },
};

/*--------------------------------------------
	0x34f8 PE1_R_MP_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sobel_weight"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"laplacian_weight"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sobel_manual_mode_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x34fc PE1_R_MP_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3500 PE1_R_MP_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"display_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gx_weight_manual_mode"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gx_weight_manual_gain"           },
};

/*--------------------------------------------
	0x3508 PE1_R_MP_CTRL_05
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x350c PE1_R_MP_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"lap_h_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"lap_v_mode"                      },
};

/*--------------------------------------------
	0x3510 PE1_R_MP_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gb_mode"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y1"                           },
};

/*--------------------------------------------
	0x3514 PE1_R_MP_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gb_x2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gb_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gb_y3"                           },
};

/*--------------------------------------------
	0x3518 PE1_R_MP_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_x_l0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum1_x_h1"                       },
};

/*--------------------------------------------
	0x351c PE1_R_MP_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum1_y0"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum1_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum1_y2"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_x_l0"                       },
};

/*--------------------------------------------
	0x3520 PE1_R_MP_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_x_l1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_x_h0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum2_x_h1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum2_y0"                         },
};

/*--------------------------------------------
	0x3524 PE1_R_MP_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_MP_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum2_y1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum2_y2"                         },
};

/*--------------------------------------------
	0x3530 PE1_R_CTI_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CTI_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"tap_size"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cti_gain"                        },
};

/*--------------------------------------------
	0x3534 PE1_R_CTI_CTRL_01
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3538 PE1_R_CTI_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CTI_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ycm_en0"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"ycm_en1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"ycm_band_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ycm_diff_th"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"ycm_y_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"ycm_c_gain"                      },
};

/*--------------------------------------------
	0x3550 PE1_R_BLUR_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BLUR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"coring_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"direction"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_min"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_max"                      },
};

/*--------------------------------------------
	0x3560 PE1_R_CORING_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"ga_max"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ga_th0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ga_th1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"amap1_sel"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"amap2_sel"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"edge_a_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"debug_a_sel"                     },
};

/*--------------------------------------------
	0x3564 PE1_R_CORING_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"max_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"avg_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"a2tw_min"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"a2tw_th0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"a2tw_th1"                        },
};

/*--------------------------------------------
	0x3568 PE1_R_CORING_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"nrv_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"nrv_th1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"nrv_th2"                         },
};

/*--------------------------------------------
	0x356c PE1_R_CORING_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"nrh_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"nrh_th1"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"nrh_th2"                         },
};

/*--------------------------------------------
	0x3570 PE1_R_CORING_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"dflt_sel"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,4  ,"var_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"coring_mode1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"coring_mode2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"ac_direction"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"tflt_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"exp_mode"                        },
};

/*--------------------------------------------
	0x3574 PE1_R_CORING_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"gt_max"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gt_th0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gt_th1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"a2tw_en"                         },
};

/*--------------------------------------------
	0x3578 PE1_R_CORING_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gt_th0a"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gt_th0b"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"gt_gain0a"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"gt_gain0b"                       },
};

/*--------------------------------------------
	0x357c PE1_R_CORING_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"g_th0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"g_th1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"amap_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"tmap_gain"                       },
};

/*--------------------------------------------
	0x3580 PE1_R_CORING_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"mp_coring_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"sp_coring_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mp_coring_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"sp_coring_en"                    },
};

/*--------------------------------------------
	0x3584 PE1_R_CORING_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CORING_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"edge_gain_b"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"edge_gain_w"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"texture_gain_b"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"texture_gain_w"                  },
};

/*--------------------------------------------
	0x3590 PE1_R_DJ_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edf_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"hv_filter_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"g0_feature_norm_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"g0_f2g_mapping_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"line_variation_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"l_type_protection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"center_blur_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"direction_type_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"count_diff_th"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"output_mux"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"n_avg_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"line_variation_diff_threshold"   },
};

/*--------------------------------------------
	0x3594 PE1_R_DJ_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"level_th"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"protect_th"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"n_avg_gain"                      },
};

/*--------------------------------------------
	0x3598 PE1_R_DJ_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"edf_count_min"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"edf_count_max"                   },
};

/*--------------------------------------------
	0x359c PE1_R_DJ_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"dj_h_count_min"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"dj_h_count_max"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"dj_v_count_min"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,25 ,"dj_v_count_max"                  },
};

/*--------------------------------------------
	0x35a0 PE1_R_LEVEL_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LEVEL_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,4  ,"y_offset"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"y_gain"                          },
};

/*--------------------------------------------
	0x35a4 PE1_R_VSPYC_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_VSPYC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"graycolor_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"color_only_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cb_info"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cr_info"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"contrast"                        },
};

/*--------------------------------------------
	0x35a8 PE1_R_VSPYC_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_VSPYC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"brightness"                      },
};

/*--------------------------------------------
	0x35b0 PE1_R_VSPRGB_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_VSPRGB_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"contrast"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"brightness"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"enable"                          },
};

/*--------------------------------------------
	0x35c0 PE1_R_XVY_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"outputcsc_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"degamma_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pcc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"gamma_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"scaler_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"hsv_hsl_selection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"s_adpative_scaler_enable"        },
};

/*--------------------------------------------
	0x35c4 PE1_R_XVY_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef0"                     },
};

/*--------------------------------------------
	0x35c8 PE1_R_XVY_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef2"                     },
};

/*--------------------------------------------
	0x35cc PE1_R_XVY_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef5"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef4"                     },
};

/*--------------------------------------------
	0x35d0 PE1_R_XVY_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_csc_coef7"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef6"                     },
};

/*--------------------------------------------
	0x35d4 PE1_R_XVY_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"r_csc_ofst0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_csc_coef8"                     },
};

/*--------------------------------------------
	0x35d8 PE1_R_XVY_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"r_csc_ofst2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"r_csc_ofst1"                     },
};

/*--------------------------------------------
	0x35dc PE1_R_XVY_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"r_csc_ofst4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"r_csc_ofst3"                     },
};

/*--------------------------------------------
	0x35e0 PE1_R_XVY_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"r_csc_ofst5"                     },
};

/*--------------------------------------------
	0x35e4 PE1_R_XVY_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef1"                     },
};

/*--------------------------------------------
	0x35e8 PE1_R_XVY_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef3"                     },
};

/*--------------------------------------------
	0x35ec PE1_R_XVY_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef6"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef5"                     },
};

/*--------------------------------------------
	0x35f0 PE1_R_XVY_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef8"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"r_pcc_coef7"                     },
};

/*--------------------------------------------
	0x35f4 PE1_R_XVY_CTRL_0D
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_0D[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"scaler"                          },
};

/*--------------------------------------------
	0x3600 PE1_R_CEN_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CEN_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"select_hsv"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"select_rgb"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"vsp_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"global_apl_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cen_bypass"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cen_debug_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"debugging_mode_core"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"pe1_1st_core_gain_disable"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pe1_2nd_core_gain_disable"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"v_scaler_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"demo_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"win_control_mode"                },
};

/*--------------------------------------------
	0x3604 PE1_R_CEN_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CEN_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"show_color_region0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"show_color_region1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"color_region_en0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"color_region_en1"                },
};

/*--------------------------------------------
	0x3608 PE1_R_CEN_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CEN_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ihsv_sgain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ihsv_vgain"                      },
};

/*--------------------------------------------
	0x360c PE1_R_CEN_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CEN_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ihsv_hoffset"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ihsv_soffset"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ihsv_voffset"                    },
};

/*--------------------------------------------
	0x3610 PE1_R_CEN_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CEN_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"den_ctrl0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"den_apl_limit_high"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"den_gain"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"den_coring"                      },
};

/*--------------------------------------------
	0x3614 PE1_R_CEN_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CEN_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_cen_address"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"hif_cen_ai_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_cen_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_cen_enable"                  },
};

/*--------------------------------------------
	0x3618 PE1_R_CEN_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CEN_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_cen_y_wdata"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_cen_x_wdata"                 },
};

/*--------------------------------------------
	0x3630 PE1_R_LRCR_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"adjust_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"protection_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"adjust_en2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"r_hist_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"l_hist_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"r_proc_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"l_proc_data_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"ff_mode_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"ff_mode_parity"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"r_out_data_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"l_out_data_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"lrcr_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"hist_rd_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"hist_mode"                       },
};

/*--------------------------------------------
	0x3634 PE1_R_LRCR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"th_max_hist"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"th_valid_bins"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"th1"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"th0"                             },
};

/*--------------------------------------------
	0x3638 PE1_R_LRCR_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"hist_l_window_h_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hist_l_window_h_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"hist_l_window_v_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hist_l_window_v_en"              },
};

/*--------------------------------------------
	0x363c PE1_R_LRCR_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x3640 PE1_R_LRCR_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"hist_r_window_h_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hist_r_window_h_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"hist_r_window_v_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hist_r_window_v_en"              },
};

/*--------------------------------------------
	0x3644 PE1_R_LRCR_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x3648 PE1_R_LRCR_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"active_window_h_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"active_window_h_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"active_window_v_bbd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"active_window_v_en"              },
};

/*--------------------------------------------
	0x364c PE1_R_LRCR_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x3650 PE1_R_LRCR_STAT_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_hist"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"n_valid_bins"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cdf_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cdf_x0"                          },
};

/*--------------------------------------------
	0x3654 PE1_R_LRCR_STAT_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_hist"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"n_valid_bins"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cdf_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cdf_x0"                          },
};

/*--------------------------------------------
	0x3658 PE1_R_LRCR_STAT_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_STAT_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_hist"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"n_valid_bins"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cdf_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cdf_x0"                          },
};

/*--------------------------------------------
	0x3670 PE1_R_DCE_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dynamic_contrast_en"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"hist_bin_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"hist_clear"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"window_mode_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"window_acquire"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"color_region0_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"color_region1_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"color_region2_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"color_region3_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"color_region4_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"color_region5_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"color_region6_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"color_region7_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"color_region8_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"color_region9_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"color_region10_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"color_region11_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"color_region12_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"color_region13_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"color_region14_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"color_region15_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"dce_domain_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"win_selection"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"histogram_mode"                  },
};

/*--------------------------------------------
	0x3674 PE1_R_DCE_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hist_bin_min_position"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hist_bin_max_position"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"color_region_gain"               },
};

/*--------------------------------------------
	0x3678 PE1_R_DCE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"color_region_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"color_debug_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"y_grad_gain"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cb_grad_gain"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cr_grad_gain"                    },
};

/*--------------------------------------------
	0x367c PE1_R_DCE_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_range_min"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"y_range_max"                     },
};

/*--------------------------------------------
	0x3680 PE1_R_DCE_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cb_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cb_range_max"                    },
};

/*--------------------------------------------
	0x3684 PE1_R_DCE_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cr_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cr_range_max"                    },
};

/*--------------------------------------------
	0x3688 PE1_R_DCE_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"hif_dyc_address"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hif_dce_load"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_dce_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_dce_enable"                  },
};

/*--------------------------------------------
	0x368c PE1_R_DCE_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dyc_wdata_y"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dyc_wdata_x"                 },
};

/*--------------------------------------------
	0x3690 PE1_R_DCE_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dyc_wdata_y_32nd"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dyc_wdata_x_32nd"            },
};

/*--------------------------------------------
	0x36a0 PE1_R_DCE_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DCE_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"hif_status_address"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hif_status_ai"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"hif_mask"                        },
};

/*--------------------------------------------
	0x36a4 PE1_R_DCE_HIST_IA_DATA1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x36a8 PE1_R_DCE_HSIT_IA_DATA2
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x36ac PE1_R_DSE_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DSE_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dynamic_saturation_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"window_mode_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"window_acquire"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"win_selection"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"color_region0_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"color_region1_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"color_region2_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"color_region3_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"color_region4_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"color_region5_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"color_region6_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"color_region7_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"color_region8_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"color_region9_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"color_region10_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"color_region11_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"color_region12_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"color_region13_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"color_region14_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"color_region15_sel"              },
};

/*--------------------------------------------
	0x36b0 PE1_R_DSE_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DSE_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"color_region_gain"               },
};

/*--------------------------------------------
	0x36b4 PE1_R_DSE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DSE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dse_wdata_y_32nd"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dse_wdata_x_32nd"            },
};

/*--------------------------------------------
	0x36b8 PE1_R_DSE_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DSE_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"hif_dse_address"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hif_dse_load"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_dse_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_dse_enable"                  },
};

/*--------------------------------------------
	0x36bc PE1_R_DSE_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DSE_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"hif_dse_wdata_y"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"hif_dse_wdata_x"                 },
};

/*--------------------------------------------
	0x36c0 PE1_R_WB_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WB_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"wb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"gamma_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"degamma_en"                      },
};

/*--------------------------------------------
	0x36c4 PE1_R_WB_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WB_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"user_ctrl_g_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctrl_b_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"user_ctrl_r_gain"                },
};

/*--------------------------------------------
	0x36c8 PE1_R_WB_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WB_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"user_ctrl_g_offset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctrl_b_offset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"user_ctrl_r_offset"              },
};

/*--------------------------------------------
	0x36f0 PE1_R_GMC_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_GMC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pxl_rep_xpos"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"lut_wmask_g"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"lut_wmask_b"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"lut_wmask_r"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pxl_rep_area"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pxl_rep_ypos"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pxl_rep_disable_g"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"pxl_rep_disable_b"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"pxl_rep_disable_r"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pxl_rep_enable"                  },
};

/*--------------------------------------------
	0x36f4 PE1_R_GMC_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_GMC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pxl_rep_width"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pxl_rep_height"                  },
};

/*--------------------------------------------
	0x36f8 PE1_R_GMC_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_GMC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"pxl_rep_value_g"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"pxl_rep_value_b"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"pxl_rep_value_r"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"gmc_mode"                        },
};

/*--------------------------------------------
	0x36fc PE1_R_GMC_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_GMC_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"capture_addr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"capture_ai"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"capture_num"                     },
};

/*--------------------------------------------
	0x3700 PE1_R_GMC_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_GMC_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"lut_data_g"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"lut_data_b"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"lut_data_r"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"capture_stat_started"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"capture_stat_ended"              },
};

/*--------------------------------------------
	0x3704 PE1_R_GMC_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_GMC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dither_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"decontour_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"dither_random_freeze_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"demo_pattern_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"bit_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"decontour_gain_r"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"decontour_gain_g"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"decontour_gain_b"                },
};

/*--------------------------------------------
	0x3720 PE1_R_SQM_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"outmux_debugmap"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"iir"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"i_score"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"v_score"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"l_score"                         },
};

/*--------------------------------------------
	0x3724 PE1_R_SQM_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"v_limit"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"l_limit"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"score_threshold"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"flat_threshold"                  },
};

/*--------------------------------------------
	0x3728 PE1_R_SQM_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_y0"                          },
};

/*--------------------------------------------
	0x372c PE1_R_SQM_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_y1"                          },
};

/*--------------------------------------------
	0x3730 PE1_R_SQM_CTRL_4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"charcter_delta_limit"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"boundary_width"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"video_height"                    },
};

/*--------------------------------------------
	0x3734 PE1_R_SQM_CTRL_5
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pc_threshold"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"pc_delta_limit"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"pc_pixel_minimal_limit"          },
};

/*--------------------------------------------
	0x3738 PE1_R_SQM_STAT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_STAT[] = {
};

/*--------------------------------------------
	0x3750 PE1_R_BBD2D_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD2D_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"black_boundary_detection_enable" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"hysterisis_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"mode_selection"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cnt_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"diff_th"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vcnt"                            },
};

/*--------------------------------------------
	0x3754 PE1_R_BBD2D_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD2D_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y0"                          },
};

/*--------------------------------------------
	0x3758 PE1_R_BBD2D_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD2D_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y1"                          },
};

/*--------------------------------------------
	0x375c PE1_R_BBD2D_STAT_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD2D_STAT_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                              },
};

/*--------------------------------------------
	0x3760 PE1_R_BBD2D_STAT_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD2D_STAT_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                              },
};

/*--------------------------------------------
	0x3770 PE1_R_BBD3D_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD3D_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"black_boundary_detection_enable" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"hysterisis_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"pe1_3d_type"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"mode_selection"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cnt_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"diff_th"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vcnt"                            },
};

/*--------------------------------------------
	0x3774 PE1_R_BBD3D_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD3D_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"bbd_read_control"                },
};

/*--------------------------------------------
	0x3778 PE1_R_BBD3D_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD3D_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"bbd_x1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bbd_y1"                          },
};

/*--------------------------------------------
	0x377c PE1_R_BBD3D_STAT_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_BBD3D_STAT_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y"                               },
};

/*--------------------------------------------
	0x37b0 P1R_PE1_L_G_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1R_PE1_L_G_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_g_available"             },
};

/*--------------------------------------------
	0x37b4 P1R_PE1_L_G_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x37b8 P1R_PE1_L_B_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1R_PE1_L_B_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_b_available"             },
};

/*--------------------------------------------
	0x37bc P1R_PE1_L_B_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x37c0 P1R_PE1_L_R_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1R_PE1_L_R_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_r_available"             },
};

/*--------------------------------------------
	0x37c4 P1R_PE1_L_R_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x37c8 P1R_PE1_R_G_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1R_PE1_R_G_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_g_available"             },
};

/*--------------------------------------------
	0x37cc P1R_PE1_R_G_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x37d0 P1R_PE1_R_B_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1R_PE1_R_B_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_b_available"             },
};

/*--------------------------------------------
	0x37d4 P1R_PE1_R_B_HIST_IA_DATA
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x37d8 P1R_PE1_R_R_HIST_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_P1R_PE1_R_R_HIST_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hif_hist_address"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_hist_ai"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_hist_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hist_rd_r_available"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hist_rd_done"                    },
};

/*--------------------------------------------
	0x37dc P1R_PE1_R_R_HIST_IA_DATA
--------------------------------------------*/
/* no field */

DBG_REG_T gDbgRegPE1[] = {
	{ 0x1300 ,N_FLD(dbg_PE1_L_TOP_CTRL_00)               ,"PE1_L_TOP_CTRL_00"                 ,dbg_PE1_L_TOP_CTRL_00               },
	{ 0x1304 ,N_FLD(dbg_PE1_L_TOP_CTRL_01)               ,"PE1_L_TOP_CTRL_01"                 ,dbg_PE1_L_TOP_CTRL_01               },
	{ 0x1308 ,N_FLD(dbg_PE1_L_TOP_CTRL_02)               ,"PE1_L_TOP_CTRL_02"                 ,dbg_PE1_L_TOP_CTRL_02               },
	{ 0x130c ,N_FLD(dbg_PE1_L_TOP_CTRL_03)               ,"PE1_L_TOP_CTRL_03"                 ,dbg_PE1_L_TOP_CTRL_03               },
	{ 0x1320 ,N_FLD(dbg_PE1_L_WIN1_CTRL_00)              ,"PE1_L_WIN1_CTRL_00"                ,dbg_PE1_L_WIN1_CTRL_00              },
	{ 0x1324 ,N_FLD(dbg_PE1_L_WIN1_CTRL_01)              ,"PE1_L_WIN1_CTRL_01"                ,dbg_PE1_L_WIN1_CTRL_01              },
	{ 0x1328 ,N_FLD(dbg_PE1_L_WIN1_CTRL_02)              ,"PE1_L_WIN1_CTRL_02"                ,dbg_PE1_L_WIN1_CTRL_02              },
	{ 0x132c ,N_FLD(dbg_PE1_L_WIN1_CTRL_03)              ,"PE1_L_WIN1_CTRL_03"                ,dbg_PE1_L_WIN1_CTRL_03              },
	{ 0x1330 ,N_FLD(dbg_PE1_L_WIN1_CTRL_04)              ,"PE1_L_WIN1_CTRL_04"                ,dbg_PE1_L_WIN1_CTRL_04              },
	{ 0x1334 ,N_FLD(dbg_PE1_L_WIN2_CTRL_00)              ,"PE1_L_WIN2_CTRL_00"                ,dbg_PE1_L_WIN2_CTRL_00              },
	{ 0x1338 ,N_FLD(dbg_PE1_L_WIN2_CTRL_01)              ,"PE1_L_WIN2_CTRL_01"                ,dbg_PE1_L_WIN2_CTRL_01              },
	{ 0x133c ,N_FLD(dbg_PE1_L_WIN2_CTRL_02)              ,"PE1_L_WIN2_CTRL_02"                ,dbg_PE1_L_WIN2_CTRL_02              },
	{ 0x1340 ,N_FLD(dbg_PE1_L_WIN2_CTRL_03)              ,"PE1_L_WIN2_CTRL_03"                ,dbg_PE1_L_WIN2_CTRL_03              },
	{ 0x1344 ,N_FLD(dbg_PE1_L_WIN2_CTRL_04)              ,"PE1_L_WIN2_CTRL_04"                ,dbg_PE1_L_WIN2_CTRL_04              },
	{ 0x1350 ,N_FLD(dbg_PE1_L_APL_CTRL_00)               ,"PE1_L_APL_CTRL_00"                 ,dbg_PE1_L_APL_CTRL_00               },
	{ 0x1354 ,N_FLD(dbg_PE1_L_APL_CTRL_01)               ,"PE1_L_APL_CTRL_01"                 ,dbg_PE1_L_APL_CTRL_01               },
	{ 0x1358 ,N_FLD(dbg_PE1_L_APL_CTRL_02)               ,"PE1_L_APL_CTRL_02"                 ,dbg_PE1_L_APL_CTRL_02               },
	{ 0x135c ,N_FLD(dbg_PE1_L_APL_STAT_00)               ,"PE1_L_APL_STAT_00"                 ,dbg_PE1_L_APL_STAT_00               },
	{ 0x1360 ,N_FLD(dbg_PE1_L_APL_STAT_01)               ,"PE1_L_APL_STAT_01"                 ,dbg_PE1_L_APL_STAT_01               },
	{ 0x1364 ,N_FLD(dbg_PE1_L_APL_STAT_02)               ,"PE1_L_APL_STAT_02"                 ,dbg_PE1_L_APL_STAT_02               },
	{ 0x1368 ,N_FLD(dbg_PE1_L_APL_STAT_03)               ,"PE1_L_APL_STAT_03"                 ,dbg_PE1_L_APL_STAT_03               },
	{ 0x1370 ,N_FLD(dbg_PE1_L_TPG_CTRL_00)               ,"PE1_L_TPG_CTRL_00"                 ,dbg_PE1_L_TPG_CTRL_00               },
	{ 0x1374 ,N_FLD(dbg_PE1_L_TPG_CTRL_01)               ,"PE1_L_TPG_CTRL_01"                 ,dbg_PE1_L_TPG_CTRL_01               },
	{ 0x1378 ,N_FLD(dbg_PE1_L_TPG_CTRL_02)               ,"PE1_L_TPG_CTRL_02"                 ,dbg_PE1_L_TPG_CTRL_02               },
	{ 0x137c ,N_FLD(dbg_PE1_L_TPG_CTRL_03)               ,"PE1_L_TPG_CTRL_03"                 ,dbg_PE1_L_TPG_CTRL_03               },
	{ 0x1380 ,N_FLD(dbg_PE1_L_TPG_CTRL_04)               ,"PE1_L_TPG_CTRL_04"                 ,dbg_PE1_L_TPG_CTRL_04               },
	{ 0x1384 ,N_FLD(dbg_PE1_L_TPG_IA_CTRL)               ,"PE1_L_TPG_IA_CTRL"                 ,dbg_PE1_L_TPG_IA_CTRL               },
	{ 0x1388 ,N_FLD(dbg_PE1_L_TPG_IA_DATA)               ,"PE1_L_TPG_IA_DATA"                 ,dbg_PE1_L_TPG_IA_DATA               },
	{ 0x13a0 ,N_FLD(dbg_PE1_L_FILM_CTRL_00)              ,"PE1_L_FILM_CTRL_00"                ,dbg_PE1_L_FILM_CTRL_00              },
	{ 0x13a4 ,N_FLD(dbg_PE1_L_FILM_CTRL_01)              ,"PE1_L_FILM_CTRL_01"                ,dbg_PE1_L_FILM_CTRL_01              },
	{ 0x13a8 ,N_FLD(dbg_PE1_L_FILM_CTRL_02)              ,"PE1_L_FILM_CTRL_02"                ,dbg_PE1_L_FILM_CTRL_02              },
	{ 0x13b0 ,N_FLD(dbg_PE1_L_WIN3_CTRL_00)              ,"PE1_L_WIN3_CTRL_00"                ,dbg_PE1_L_WIN3_CTRL_00              },
	{ 0x13b4 ,N_FLD(dbg_PE1_L_WIN3_CTRL_01)              ,"PE1_L_WIN3_CTRL_01"                ,dbg_PE1_L_WIN3_CTRL_01              },
	{ 0x13b8 ,N_FLD(dbg_PE1_L_WIN3_CTRL_02)              ,"PE1_L_WIN3_CTRL_02"                ,dbg_PE1_L_WIN3_CTRL_02              },
	{ 0x13bc ,N_FLD(dbg_PE1_L_WIN3_CTRL_03)              ,"PE1_L_WIN3_CTRL_03"                ,dbg_PE1_L_WIN3_CTRL_03              },
	{ 0x13c0 ,N_FLD(dbg_PE1_L_WIN3_CTRL_04)              ,"PE1_L_WIN3_CTRL_04"                ,dbg_PE1_L_WIN3_CTRL_04              },
	{ 0x13d0 ,N_FLD(dbg_PE1_L_DERH_CTRL_00)              ,"PE1_L_DERH_CTRL_00"                ,dbg_PE1_L_DERH_CTRL_00              },
	{ 0x13d4 ,N_FLD(dbg_PE1_L_DERH_CTRL_01)              ,"PE1_L_DERH_CTRL_01"                ,dbg_PE1_L_DERH_CTRL_01              },
	{ 0x13d8 ,N_FLD(dbg_PE1_L_DERH_CTRL_02)              ,"PE1_L_DERH_CTRL_02"                ,dbg_PE1_L_DERH_CTRL_02              },
	{ 0x13dc ,N_FLD(dbg_PE1_L_DERH_CTRL_03)              ,"PE1_L_DERH_CTRL_03"                ,dbg_PE1_L_DERH_CTRL_03              },
	{ 0x13e0 ,N_FLD(dbg_PE1_L_DERH_CTRL_04)              ,"PE1_L_DERH_CTRL_04"                ,dbg_PE1_L_DERH_CTRL_04              },
	{ 0x13e4 ,N_FLD(dbg_PE1_L_DERH_CTRL_05)              ,"PE1_L_DERH_CTRL_05"                ,dbg_PE1_L_DERH_CTRL_05              },
	{ 0x13e8 ,N_FLD(dbg_PE1_L_DERH_CTRL_06)              ,"PE1_L_DERH_CTRL_06"                ,dbg_PE1_L_DERH_CTRL_06              },
	{ 0x13ec ,N_FLD(dbg_PE1_L_DERH_CTRL_07)              ,"PE1_L_DERH_CTRL_07"                ,dbg_PE1_L_DERH_CTRL_07              },
	{ 0x13f0 ,N_FLD(dbg_PE1_L_DERH_CTRL_08)              ,"PE1_L_DERH_CTRL_08"                ,dbg_PE1_L_DERH_CTRL_08              },
	{ 0x13f4 ,N_FLD(dbg_PE1_L_DERH_CTRL_09)              ,"PE1_L_DERH_CTRL_09"                ,dbg_PE1_L_DERH_CTRL_09              },
	{ 0x1400 ,N_FLD(dbg_PE1_L_DERV_CTRL_0)               ,"PE1_L_DERV_CTRL_0"                 ,dbg_PE1_L_DERV_CTRL_0               },
	{ 0x1404 ,N_FLD(dbg_PE1_L_DERV_CTRL_1)               ,"PE1_L_DERV_CTRL_1"                 ,dbg_PE1_L_DERV_CTRL_1               },
	{ 0x1408 ,N_FLD(dbg_PE1_L_DERV_CTRL_2)               ,"PE1_L_DERV_CTRL_2"                 ,dbg_PE1_L_DERV_CTRL_2               },
	{ 0x140c ,N_FLD(dbg_PE1_L_DERV_CTRL_3)               ,"PE1_L_DERV_CTRL_3"                 ,dbg_PE1_L_DERV_CTRL_3               },
	{ 0x1410 ,0                                          ,"PE1_L_DP_CTRL_00"                  ,NULL                                },
	{ 0x1414 ,N_FLD(dbg_PE1_L_DP_CTRL_01)                ,"PE1_L_DP_CTRL_01"                  ,dbg_PE1_L_DP_CTRL_01                },
	{ 0x1418 ,0                                          ,"PE1_L_DP_CTRL_02"                  ,NULL                                },
	{ 0x141c ,0                                          ,"PE1_L_DP_CTRL_03"                  ,NULL                                },
	{ 0x1420 ,N_FLD(dbg_PE1_L_CORING_STAT_00)            ,"PE1_L_CORING_STAT_00"              ,dbg_PE1_L_CORING_STAT_00            },
	{ 0x1424 ,N_FLD(dbg_PE1_L_CORING_STAT_01)            ,"PE1_L_CORING_STAT_01"              ,dbg_PE1_L_CORING_STAT_01            },
	{ 0x1428 ,0                                          ,"PE1_L_CORING_STAT_02"              ,NULL                                },
	{ 0x142c ,0                                          ,"PE1_L_CORING_STAT_03"              ,NULL                                },
	{ 0x1470 ,N_FLD(dbg_PE1_L_DERH_CTRL_0A)              ,"PE1_L_DERH_CTRL_0A"                ,dbg_PE1_L_DERH_CTRL_0A              },
	{ 0x1474 ,N_FLD(dbg_PE1_L_DERH_CTRL_0B)              ,"PE1_L_DERH_CTRL_0B"                ,dbg_PE1_L_DERH_CTRL_0B              },
	{ 0x1478 ,N_FLD(dbg_PE1_L_DERH_CTRL_0C)              ,"PE1_L_DERH_CTRL_0C"                ,dbg_PE1_L_DERH_CTRL_0C              },
	{ 0x147c ,0                                          ,"PE1_L_DERH_CTRL_0D"                ,NULL                                },
	{ 0x1490 ,N_FLD(dbg_PE1_L_SP_CTRL_00)                ,"PE1_L_SP_CTRL_00"                  ,dbg_PE1_L_SP_CTRL_00                },
	{ 0x1494 ,N_FLD(dbg_PE1_L_SP_CTRL_01)                ,"PE1_L_SP_CTRL_01"                  ,dbg_PE1_L_SP_CTRL_01                },
	{ 0x1498 ,N_FLD(dbg_PE1_L_SP_CTRL_02)                ,"PE1_L_SP_CTRL_02"                  ,dbg_PE1_L_SP_CTRL_02                },
	{ 0x149c ,0                                          ,"PE1_L_SP_CTRL_03"                  ,NULL                                },
	{ 0x14a0 ,N_FLD(dbg_PE1_L_SP_CTRL_04)                ,"PE1_L_SP_CTRL_04"                  ,dbg_PE1_L_SP_CTRL_04                },
	{ 0x14a8 ,0                                          ,"PE1_L_SP_CTRL_05"                  ,NULL                                },
	{ 0x14ac ,N_FLD(dbg_PE1_L_SP_CTRL_06)                ,"PE1_L_SP_CTRL_06"                  ,dbg_PE1_L_SP_CTRL_06                },
	{ 0x14b0 ,N_FLD(dbg_PE1_L_SP_CTRL_07)                ,"PE1_L_SP_CTRL_07"                  ,dbg_PE1_L_SP_CTRL_07                },
	{ 0x14b4 ,N_FLD(dbg_PE1_L_SP_CTRL_08)                ,"PE1_L_SP_CTRL_08"                  ,dbg_PE1_L_SP_CTRL_08                },
	{ 0x14b8 ,N_FLD(dbg_PE1_L_SP_CTRL_09)                ,"PE1_L_SP_CTRL_09"                  ,dbg_PE1_L_SP_CTRL_09                },
	{ 0x14bc ,N_FLD(dbg_PE1_L_SP_CTRL_0A)                ,"PE1_L_SP_CTRL_0A"                  ,dbg_PE1_L_SP_CTRL_0A                },
	{ 0x14c0 ,N_FLD(dbg_PE1_L_SP_CTRL_0B)                ,"PE1_L_SP_CTRL_0B"                  ,dbg_PE1_L_SP_CTRL_0B                },
	{ 0x14c4 ,N_FLD(dbg_PE1_L_SP_CTRL_0C)                ,"PE1_L_SP_CTRL_0C"                  ,dbg_PE1_L_SP_CTRL_0C                },
	{ 0x14d0 ,N_FLD(dbg_PE1_L_DEBUG_CTRL_00)             ,"PE1_L_DEBUG_CTRL_00"               ,dbg_PE1_L_DEBUG_CTRL_00             },
	{ 0x14d4 ,N_FLD(dbg_PE1_L_DEBUG_CTRL_01)             ,"PE1_L_DEBUG_CTRL_01"               ,dbg_PE1_L_DEBUG_CTRL_01             },
	{ 0x14f0 ,N_FLD(dbg_PE1_L_MP_CTRL_00)                ,"PE1_L_MP_CTRL_00"                  ,dbg_PE1_L_MP_CTRL_00                },
	{ 0x14f4 ,N_FLD(dbg_PE1_L_MP_CTRL_01)                ,"PE1_L_MP_CTRL_01"                  ,dbg_PE1_L_MP_CTRL_01                },
	{ 0x14f8 ,N_FLD(dbg_PE1_L_MP_CTRL_02)                ,"PE1_L_MP_CTRL_02"                  ,dbg_PE1_L_MP_CTRL_02                },
	{ 0x14fc ,0                                          ,"PE1_L_MP_CTRL_03"                  ,NULL                                },
	{ 0x1500 ,N_FLD(dbg_PE1_L_MP_CTRL_04)                ,"PE1_L_MP_CTRL_04"                  ,dbg_PE1_L_MP_CTRL_04                },
	{ 0x1508 ,0                                          ,"PE1_L_MP_CTRL_05"                  ,NULL                                },
	{ 0x150c ,N_FLD(dbg_PE1_L_MP_CTRL_06)                ,"PE1_L_MP_CTRL_06"                  ,dbg_PE1_L_MP_CTRL_06                },
	{ 0x1510 ,N_FLD(dbg_PE1_L_MP_CTRL_07)                ,"PE1_L_MP_CTRL_07"                  ,dbg_PE1_L_MP_CTRL_07                },
	{ 0x1514 ,N_FLD(dbg_PE1_L_MP_CTRL_08)                ,"PE1_L_MP_CTRL_08"                  ,dbg_PE1_L_MP_CTRL_08                },
	{ 0x1518 ,N_FLD(dbg_PE1_L_MP_CTRL_09)                ,"PE1_L_MP_CTRL_09"                  ,dbg_PE1_L_MP_CTRL_09                },
	{ 0x151c ,N_FLD(dbg_PE1_L_MP_CTRL_0A)                ,"PE1_L_MP_CTRL_0A"                  ,dbg_PE1_L_MP_CTRL_0A                },
	{ 0x1520 ,N_FLD(dbg_PE1_L_MP_CTRL_0B)                ,"PE1_L_MP_CTRL_0B"                  ,dbg_PE1_L_MP_CTRL_0B                },
	{ 0x1524 ,N_FLD(dbg_PE1_L_MP_CTRL_0C)                ,"PE1_L_MP_CTRL_0C"                  ,dbg_PE1_L_MP_CTRL_0C                },
	{ 0x1530 ,N_FLD(dbg_PE1_L_CTI_CTRL_00)               ,"PE1_L_CTI_CTRL_00"                 ,dbg_PE1_L_CTI_CTRL_00               },
	{ 0x1534 ,0                                          ,"PE1_L_CTI_CTRL_01"                 ,NULL                                },
	{ 0x1538 ,N_FLD(dbg_PE1_L_CTI_CTRL_02)               ,"PE1_L_CTI_CTRL_02"                 ,dbg_PE1_L_CTI_CTRL_02               },
	{ 0x1550 ,N_FLD(dbg_PE1_L_BLUR_CTRL)                 ,"PE1_L_BLUR_CTRL"                   ,dbg_PE1_L_BLUR_CTRL                 },
	{ 0x1560 ,N_FLD(dbg_PE1_L_CORING_CTRL_00)            ,"PE1_L_CORING_CTRL_00"              ,dbg_PE1_L_CORING_CTRL_00            },
	{ 0x1564 ,N_FLD(dbg_PE1_L_CORING_CTRL_01)            ,"PE1_L_CORING_CTRL_01"              ,dbg_PE1_L_CORING_CTRL_01            },
	{ 0x1568 ,N_FLD(dbg_PE1_L_CORING_CTRL_02)            ,"PE1_L_CORING_CTRL_02"              ,dbg_PE1_L_CORING_CTRL_02            },
	{ 0x156c ,N_FLD(dbg_PE1_L_CORING_CTRL_03)            ,"PE1_L_CORING_CTRL_03"              ,dbg_PE1_L_CORING_CTRL_03            },
	{ 0x1570 ,N_FLD(dbg_PE1_L_CORING_CTRL_04)            ,"PE1_L_CORING_CTRL_04"              ,dbg_PE1_L_CORING_CTRL_04            },
	{ 0x1574 ,N_FLD(dbg_PE1_L_CORING_CTRL_05)            ,"PE1_L_CORING_CTRL_05"              ,dbg_PE1_L_CORING_CTRL_05            },
	{ 0x1578 ,N_FLD(dbg_PE1_L_CORING_CTRL_06)            ,"PE1_L_CORING_CTRL_06"              ,dbg_PE1_L_CORING_CTRL_06            },
	{ 0x157c ,N_FLD(dbg_PE1_L_CORING_CTRL_07)            ,"PE1_L_CORING_CTRL_07"              ,dbg_PE1_L_CORING_CTRL_07            },
	{ 0x1580 ,N_FLD(dbg_PE1_L_CORING_CTRL_08)            ,"PE1_L_CORING_CTRL_08"              ,dbg_PE1_L_CORING_CTRL_08            },
	{ 0x1584 ,N_FLD(dbg_PE1_L_CORING_CTRL_09)            ,"PE1_L_CORING_CTRL_09"              ,dbg_PE1_L_CORING_CTRL_09            },
	{ 0x1590 ,N_FLD(dbg_PE1_L_DJ_CTRL_00)                ,"PE1_L_DJ_CTRL_00"                  ,dbg_PE1_L_DJ_CTRL_00                },
	{ 0x1594 ,N_FLD(dbg_PE1_L_DJ_CTRL_01)                ,"PE1_L_DJ_CTRL_01"                  ,dbg_PE1_L_DJ_CTRL_01                },
	{ 0x1598 ,N_FLD(dbg_PE1_L_DJ_CTRL_02)                ,"PE1_L_DJ_CTRL_02"                  ,dbg_PE1_L_DJ_CTRL_02                },
	{ 0x159c ,N_FLD(dbg_PE1_L_DJ_CTRL_03)                ,"PE1_L_DJ_CTRL_03"                  ,dbg_PE1_L_DJ_CTRL_03                },
	{ 0x15a0 ,N_FLD(dbg_PE1_L_LEVEL_CTRL_00)             ,"PE1_L_LEVEL_CTRL_00"               ,dbg_PE1_L_LEVEL_CTRL_00             },
	{ 0x15a4 ,N_FLD(dbg_PE1_L_VSPYC_CTRL_00)             ,"PE1_L_VSPYC_CTRL_00"               ,dbg_PE1_L_VSPYC_CTRL_00             },
	{ 0x15a8 ,N_FLD(dbg_PE1_L_VSPYC_CTRL_01)             ,"PE1_L_VSPYC_CTRL_01"               ,dbg_PE1_L_VSPYC_CTRL_01             },
	{ 0x15b0 ,N_FLD(dbg_PE1_L_VSPRGB_CTRL_00)            ,"PE1_L_VSPRGB_CTRL_00"              ,dbg_PE1_L_VSPRGB_CTRL_00            },
	{ 0x15c0 ,N_FLD(dbg_PE1_L_XVY_CTRL_00)               ,"PE1_L_XVY_CTRL_00"                 ,dbg_PE1_L_XVY_CTRL_00               },
	{ 0x15c4 ,N_FLD(dbg_PE1_L_XVY_CTRL_01)               ,"PE1_L_XVY_CTRL_01"                 ,dbg_PE1_L_XVY_CTRL_01               },
	{ 0x15c8 ,N_FLD(dbg_PE1_L_XVY_CTRL_02)               ,"PE1_L_XVY_CTRL_02"                 ,dbg_PE1_L_XVY_CTRL_02               },
	{ 0x15cc ,N_FLD(dbg_PE1_L_XVY_CTRL_03)               ,"PE1_L_XVY_CTRL_03"                 ,dbg_PE1_L_XVY_CTRL_03               },
	{ 0x15d0 ,N_FLD(dbg_PE1_L_XVY_CTRL_04)               ,"PE1_L_XVY_CTRL_04"                 ,dbg_PE1_L_XVY_CTRL_04               },
	{ 0x15d4 ,N_FLD(dbg_PE1_L_XVY_CTRL_05)               ,"PE1_L_XVY_CTRL_05"                 ,dbg_PE1_L_XVY_CTRL_05               },
	{ 0x15d8 ,N_FLD(dbg_PE1_L_XVY_CTRL_06)               ,"PE1_L_XVY_CTRL_06"                 ,dbg_PE1_L_XVY_CTRL_06               },
	{ 0x15dc ,N_FLD(dbg_PE1_L_XVY_CTRL_07)               ,"PE1_L_XVY_CTRL_07"                 ,dbg_PE1_L_XVY_CTRL_07               },
	{ 0x15e0 ,N_FLD(dbg_PE1_L_XVY_CTRL_08)               ,"PE1_L_XVY_CTRL_08"                 ,dbg_PE1_L_XVY_CTRL_08               },
	{ 0x15e4 ,N_FLD(dbg_PE1_L_XVY_CTRL_09)               ,"PE1_L_XVY_CTRL_09"                 ,dbg_PE1_L_XVY_CTRL_09               },
	{ 0x15e8 ,N_FLD(dbg_PE1_L_XVY_CTRL_0A)               ,"PE1_L_XVY_CTRL_0A"                 ,dbg_PE1_L_XVY_CTRL_0A               },
	{ 0x15ec ,N_FLD(dbg_PE1_L_XVY_CTRL_0B)               ,"PE1_L_XVY_CTRL_0B"                 ,dbg_PE1_L_XVY_CTRL_0B               },
	{ 0x15f0 ,N_FLD(dbg_PE1_L_XVY_CTRL_0C)               ,"PE1_L_XVY_CTRL_0C"                 ,dbg_PE1_L_XVY_CTRL_0C               },
	{ 0x15f4 ,N_FLD(dbg_PE1_L_XVY_CTRL_0D)               ,"PE1_L_XVY_CTRL_0D"                 ,dbg_PE1_L_XVY_CTRL_0D               },
	{ 0x1600 ,N_FLD(dbg_PE1_L_CEN_CTRL_00)               ,"PE1_L_CEN_CTRL_00"                 ,dbg_PE1_L_CEN_CTRL_00               },
	{ 0x1604 ,N_FLD(dbg_PE1_L_CEN_CTRL_01)               ,"PE1_L_CEN_CTRL_01"                 ,dbg_PE1_L_CEN_CTRL_01               },
	{ 0x1608 ,N_FLD(dbg_PE1_L_CEN_CTRL_02)               ,"PE1_L_CEN_CTRL_02"                 ,dbg_PE1_L_CEN_CTRL_02               },
	{ 0x160c ,N_FLD(dbg_PE1_L_CEN_CTRL_03)               ,"PE1_L_CEN_CTRL_03"                 ,dbg_PE1_L_CEN_CTRL_03               },
	{ 0x1610 ,N_FLD(dbg_PE1_L_CEN_CTRL_04)               ,"PE1_L_CEN_CTRL_04"                 ,dbg_PE1_L_CEN_CTRL_04               },
	{ 0x1614 ,N_FLD(dbg_PE1_L_CEN_IA_CTRL)               ,"PE1_L_CEN_IA_CTRL"                 ,dbg_PE1_L_CEN_IA_CTRL               },
	{ 0x1618 ,N_FLD(dbg_PE1_L_CEN_IA_DATA)               ,"PE1_L_CEN_IA_DATA"                 ,dbg_PE1_L_CEN_IA_DATA               },
	{ 0x1630 ,N_FLD(dbg_PE1_L_LRCR_CTRL_00)              ,"PE1_L_LRCR_CTRL_00"                ,dbg_PE1_L_LRCR_CTRL_00              },
	{ 0x1634 ,N_FLD(dbg_PE1_L_LRCR_CTRL_01)              ,"PE1_L_LRCR_CTRL_01"                ,dbg_PE1_L_LRCR_CTRL_01              },
	{ 0x1638 ,N_FLD(dbg_PE1_L_LRCR_CTRL_02)              ,"PE1_L_LRCR_CTRL_02"                ,dbg_PE1_L_LRCR_CTRL_02              },
	{ 0x163c ,N_FLD(dbg_PE1_L_LRCR_CTRL_03)              ,"PE1_L_LRCR_CTRL_03"                ,dbg_PE1_L_LRCR_CTRL_03              },
	{ 0x1640 ,N_FLD(dbg_PE1_L_LRCR_CTRL_04)              ,"PE1_L_LRCR_CTRL_04"                ,dbg_PE1_L_LRCR_CTRL_04              },
	{ 0x1644 ,N_FLD(dbg_PE1_L_LRCR_CTRL_05)              ,"PE1_L_LRCR_CTRL_05"                ,dbg_PE1_L_LRCR_CTRL_05              },
	{ 0x1648 ,N_FLD(dbg_PE1_L_LRCR_CTRL_06)              ,"PE1_L_LRCR_CTRL_06"                ,dbg_PE1_L_LRCR_CTRL_06              },
	{ 0x164c ,N_FLD(dbg_PE1_L_LRCR_CTRL_07)              ,"PE1_L_LRCR_CTRL_07"                ,dbg_PE1_L_LRCR_CTRL_07              },
	{ 0x1650 ,N_FLD(dbg_PE1_L_LRCR_STAT_00)              ,"PE1_L_LRCR_STAT_00"                ,dbg_PE1_L_LRCR_STAT_00              },
	{ 0x1654 ,N_FLD(dbg_PE1_L_LRCR_STAT_01)              ,"PE1_L_LRCR_STAT_01"                ,dbg_PE1_L_LRCR_STAT_01              },
	{ 0x1658 ,N_FLD(dbg_PE1_L_LRCR_STAT_02)              ,"PE1_L_LRCR_STAT_02"                ,dbg_PE1_L_LRCR_STAT_02              },
	{ 0x1670 ,N_FLD(dbg_PE1_L_DCE_CTRL_00)               ,"PE1_L_DCE_CTRL_00"                 ,dbg_PE1_L_DCE_CTRL_00               },
	{ 0x1674 ,N_FLD(dbg_PE1_L_DCE_CTRL_01)               ,"PE1_L_DCE_CTRL_01"                 ,dbg_PE1_L_DCE_CTRL_01               },
	{ 0x1678 ,N_FLD(dbg_PE1_L_DCE_CTRL_02)               ,"PE1_L_DCE_CTRL_02"                 ,dbg_PE1_L_DCE_CTRL_02               },
	{ 0x167c ,N_FLD(dbg_PE1_L_DCE_CTRL_03)               ,"PE1_L_DCE_CTRL_03"                 ,dbg_PE1_L_DCE_CTRL_03               },
	{ 0x1680 ,N_FLD(dbg_PE1_L_DCE_CTRL_04)               ,"PE1_L_DCE_CTRL_04"                 ,dbg_PE1_L_DCE_CTRL_04               },
	{ 0x1684 ,N_FLD(dbg_PE1_L_DCE_CTRL_05)               ,"PE1_L_DCE_CTRL_05"                 ,dbg_PE1_L_DCE_CTRL_05               },
	{ 0x1688 ,N_FLD(dbg_PE1_L_DCE_IA_CTRL)               ,"PE1_L_DCE_IA_CTRL"                 ,dbg_PE1_L_DCE_IA_CTRL               },
	{ 0x168c ,N_FLD(dbg_PE1_L_DCE_IA_DATA)               ,"PE1_L_DCE_IA_DATA"                 ,dbg_PE1_L_DCE_IA_DATA               },
	{ 0x1690 ,N_FLD(dbg_PE1_L_DCE_CTRL_08)               ,"PE1_L_DCE_CTRL_08"                 ,dbg_PE1_L_DCE_CTRL_08               },
	{ 0x16a0 ,N_FLD(dbg_PE1_L_DCE_HIST_IA_CTRL)          ,"PE1_L_DCE_HIST_IA_CTRL"            ,dbg_PE1_L_DCE_HIST_IA_CTRL          },
	{ 0x16a4 ,0                                          ,"PE1_L_DCE_HIST_IA_DATA1"           ,NULL                                },
	{ 0x16a8 ,0                                          ,"PE1_L_DCE_HSIT_IA_DATA2"           ,NULL                                },
	{ 0x16ac ,N_FLD(dbg_PE1_L_DSE_CTRL_00)               ,"PE1_L_DSE_CTRL_00"                 ,dbg_PE1_L_DSE_CTRL_00               },
	{ 0x16b0 ,N_FLD(dbg_PE1_L_DSE_CTRL_01)               ,"PE1_L_DSE_CTRL_01"                 ,dbg_PE1_L_DSE_CTRL_01               },
	{ 0x16b4 ,N_FLD(dbg_PE1_L_DSE_CTRL_02)               ,"PE1_L_DSE_CTRL_02"                 ,dbg_PE1_L_DSE_CTRL_02               },
	{ 0x16b8 ,N_FLD(dbg_PE1_L_DSE_IA_CTRL)               ,"PE1_L_DSE_IA_CTRL"                 ,dbg_PE1_L_DSE_IA_CTRL               },
	{ 0x16bc ,N_FLD(dbg_PE1_L_DSE_IA_DATA)               ,"PE1_L_DSE_IA_DATA"                 ,dbg_PE1_L_DSE_IA_DATA               },
	{ 0x16c0 ,N_FLD(dbg_PE1_L_WB_CTRL_00)                ,"PE1_L_WB_CTRL_00"                  ,dbg_PE1_L_WB_CTRL_00                },
	{ 0x16c4 ,N_FLD(dbg_PE1_L_WB_CTRL_01)                ,"PE1_L_WB_CTRL_01"                  ,dbg_PE1_L_WB_CTRL_01                },
	{ 0x16c8 ,N_FLD(dbg_PE1_L_WB_CTRL_02)                ,"PE1_L_WB_CTRL_02"                  ,dbg_PE1_L_WB_CTRL_02                },
	{ 0x16f0 ,N_FLD(dbg_PE1_L_GMC_CTRL_00)               ,"PE1_L_GMC_CTRL_00"                 ,dbg_PE1_L_GMC_CTRL_00               },
	{ 0x16f4 ,N_FLD(dbg_PE1_L_GMC_CTRL_01)               ,"PE1_L_GMC_CTRL_01"                 ,dbg_PE1_L_GMC_CTRL_01               },
	{ 0x16f8 ,N_FLD(dbg_PE1_L_GMC_CTRL_02)               ,"PE1_L_GMC_CTRL_02"                 ,dbg_PE1_L_GMC_CTRL_02               },
	{ 0x16fc ,N_FLD(dbg_PE1_L_GMC_IA_CTRL)               ,"PE1_L_GMC_IA_CTRL"                 ,dbg_PE1_L_GMC_IA_CTRL               },
	{ 0x1700 ,N_FLD(dbg_PE1_L_GMC_IA_DATA)               ,"PE1_L_GMC_IA_DATA"                 ,dbg_PE1_L_GMC_IA_DATA               },
	{ 0x1704 ,N_FLD(dbg_PE1_L_GMC_CTRL_03)               ,"PE1_L_GMC_CTRL_03"                 ,dbg_PE1_L_GMC_CTRL_03               },
	{ 0x1720 ,N_FLD(dbg_PE1_L_SQM_CTRL_0)                ,"PE1_L_SQM_CTRL_0"                  ,dbg_PE1_L_SQM_CTRL_0                },
	{ 0x1724 ,N_FLD(dbg_PE1_L_SQM_CTRL_1)                ,"PE1_L_SQM_CTRL_1"                  ,dbg_PE1_L_SQM_CTRL_1                },
	{ 0x1728 ,N_FLD(dbg_PE1_L_SQM_CTRL_2)                ,"PE1_L_SQM_CTRL_2"                  ,dbg_PE1_L_SQM_CTRL_2                },
	{ 0x172c ,N_FLD(dbg_PE1_L_SQM_CTRL_3)                ,"PE1_L_SQM_CTRL_3"                  ,dbg_PE1_L_SQM_CTRL_3                },
	{ 0x1730 ,N_FLD(dbg_PE1_L_SQM_CTRL_4)                ,"PE1_L_SQM_CTRL_4"                  ,dbg_PE1_L_SQM_CTRL_4                },
	{ 0x1734 ,N_FLD(dbg_PE1_L_SQM_CTRL_5)                ,"PE1_L_SQM_CTRL_5"                  ,dbg_PE1_L_SQM_CTRL_5                },
	{ 0x1738 ,N_FLD(dbg_PE1_L_SQM_STAT)                  ,"PE1_L_SQM_STAT"                    ,dbg_PE1_L_SQM_STAT                  },
	{ 0x1750 ,N_FLD(dbg_PE1_L_BBD2D_CTRL_0)              ,"PE1_L_BBD2D_CTRL_0"                ,dbg_PE1_L_BBD2D_CTRL_0              },
	{ 0x1754 ,N_FLD(dbg_PE1_L_BBD2D_CTRL_1)              ,"PE1_L_BBD2D_CTRL_1"                ,dbg_PE1_L_BBD2D_CTRL_1              },
	{ 0x1758 ,N_FLD(dbg_PE1_L_BBD2D_CTRL_2)              ,"PE1_L_BBD2D_CTRL_2"                ,dbg_PE1_L_BBD2D_CTRL_2              },
	{ 0x175c ,N_FLD(dbg_PE1_L_BBD2D_STAT_0)              ,"PE1_L_BBD2D_STAT_0"                ,dbg_PE1_L_BBD2D_STAT_0              },
	{ 0x1760 ,N_FLD(dbg_PE1_L_BBD2D_STAT_1)              ,"PE1_L_BBD2D_STAT_1"                ,dbg_PE1_L_BBD2D_STAT_1              },
	{ 0x1770 ,N_FLD(dbg_PE1_L_BBD3D_CTRL_00)             ,"PE1_L_BBD3D_CTRL_00"               ,dbg_PE1_L_BBD3D_CTRL_00             },
	{ 0x1774 ,N_FLD(dbg_PE1_L_BBD3D_CTRL_01)             ,"PE1_L_BBD3D_CTRL_01"               ,dbg_PE1_L_BBD3D_CTRL_01             },
	{ 0x1778 ,N_FLD(dbg_PE1_L_BBD3D_CTRL_02)             ,"PE1_L_BBD3D_CTRL_02"               ,dbg_PE1_L_BBD3D_CTRL_02             },
	{ 0x177c ,N_FLD(dbg_PE1_L_BBD3D_STAT_0)              ,"PE1_L_BBD3D_STAT_0"                ,dbg_PE1_L_BBD3D_STAT_0              },
	{ 0x1790 ,0                                          ,"PE1_WCP_CTRL_00"                   ,NULL                                },
	{ 0x1794 ,N_FLD(dbg_PE1_WCP_CTRL_01)                 ,"PE1_WCP_CTRL_01"                   ,dbg_PE1_WCP_CTRL_01                 },
	{ 0x1798 ,N_FLD(dbg_PE1_WCP_CTRL_02)                 ,"PE1_WCP_CTRL_02"                   ,dbg_PE1_WCP_CTRL_02                 },
	{ 0x179c ,N_FLD(dbg_PE1_WCP_CTRL_03)                 ,"PE1_WCP_CTRL_03"                   ,dbg_PE1_WCP_CTRL_03                 },
	{ 0x17a0 ,N_FLD(dbg_PE1_WCP_CTRL_04)                 ,"PE1_WCP_CTRL_04"                   ,dbg_PE1_WCP_CTRL_04                 },
	{ 0x17a4 ,N_FLD(dbg_PE1_WCP_CTRL_05)                 ,"PE1_WCP_CTRL_05"                   ,dbg_PE1_WCP_CTRL_05                 },
	{ 0x17a8 ,N_FLD(dbg_PE1_WCP_CTRL_06)                 ,"PE1_WCP_CTRL_06"                   ,dbg_PE1_WCP_CTRL_06                 },
	{ 0x17b0 ,N_FLD(dbg_P1L_PE1_L_G_HIST_IA_CTRL)        ,"P1L_PE1_L_G_HIST_IA_CTRL"          ,dbg_P1L_PE1_L_G_HIST_IA_CTRL        },
	{ 0x17b4 ,0                                          ,"P1L_PE1_L_G_HIST_IA_DATA"          ,NULL                                },
	{ 0x17b8 ,N_FLD(dbg_P1L_PE1_L_B_HIST_IA_CTRL)        ,"P1L_PE1_L_B_HIST_IA_CTRL"          ,dbg_P1L_PE1_L_B_HIST_IA_CTRL        },
	{ 0x17bc ,0                                          ,"P1L_PE1_L_B_HIST_IA_DATA"          ,NULL                                },
	{ 0x17c0 ,N_FLD(dbg_P1L_PE1_L_R_HIST_IA_CTRL)        ,"P1L_PE1_L_R_HIST_IA_CTRL"          ,dbg_P1L_PE1_L_R_HIST_IA_CTRL        },
	{ 0x17c4 ,0                                          ,"P1L_PE1_L_R_HIST_IA_DATA"          ,NULL                                },
	{ 0x17c8 ,N_FLD(dbg_P1L_PE1_R_G_HIST_IA_CTRL)        ,"P1L_PE1_R_G_HIST_IA_CTRL"          ,dbg_P1L_PE1_R_G_HIST_IA_CTRL        },
	{ 0x17cc ,0                                          ,"P1L_PE1_R_G_HIST_IA_DATA"          ,NULL                                },
	{ 0x17d0 ,N_FLD(dbg_P1L_PE1_R_B_HIST_IA_CTRL)        ,"P1L_PE1_R_B_HIST_IA_CTRL"          ,dbg_P1L_PE1_R_B_HIST_IA_CTRL        },
	{ 0x17d4 ,0                                          ,"P1L_PE1_R_B_HIST_IA_DATA"          ,NULL                                },
	{ 0x17d8 ,N_FLD(dbg_P1L_PE1_R_R_HIST_IA_CTRL)        ,"P1L_PE1_R_R_HIST_IA_CTRL"          ,dbg_P1L_PE1_R_R_HIST_IA_CTRL        },
	{ 0x17dc ,0                                          ,"P1L_PE1_R_R_HIST_IA_DATA"          ,NULL                                },
	{ 0x3300 ,N_FLD(dbg_PE1_R_TOP_CTRL_00)               ,"PE1_R_TOP_CTRL_00"                 ,dbg_PE1_R_TOP_CTRL_00               },
	{ 0x3304 ,N_FLD(dbg_PE1_R_TOP_CTRL_01)               ,"PE1_R_TOP_CTRL_01"                 ,dbg_PE1_R_TOP_CTRL_01               },
	{ 0x3308 ,N_FLD(dbg_PE1_R_TOP_CTRL_02)               ,"PE1_R_TOP_CTRL_02"                 ,dbg_PE1_R_TOP_CTRL_02               },
	{ 0x330c ,N_FLD(dbg_PE1_R_TOP_CTRL_03)               ,"PE1_R_TOP_CTRL_03"                 ,dbg_PE1_R_TOP_CTRL_03               },
	{ 0x3320 ,N_FLD(dbg_PE1_R_WIN1_CTRL_00)              ,"PE1_R_WIN1_CTRL_00"                ,dbg_PE1_R_WIN1_CTRL_00              },
	{ 0x3324 ,N_FLD(dbg_PE1_R_WIN1_CTRL_01)              ,"PE1_R_WIN1_CTRL_01"                ,dbg_PE1_R_WIN1_CTRL_01              },
	{ 0x3328 ,N_FLD(dbg_PE1_R_WIN1_CTRL_02)              ,"PE1_R_WIN1_CTRL_02"                ,dbg_PE1_R_WIN1_CTRL_02              },
	{ 0x332c ,N_FLD(dbg_PE1_R_WIN1_CTRL_03)              ,"PE1_R_WIN1_CTRL_03"                ,dbg_PE1_R_WIN1_CTRL_03              },
	{ 0x3330 ,N_FLD(dbg_PE1_R_WIN1_CTRL_04)              ,"PE1_R_WIN1_CTRL_04"                ,dbg_PE1_R_WIN1_CTRL_04              },
	{ 0x3334 ,N_FLD(dbg_PE1_R_WIN2_CTRL_00)              ,"PE1_R_WIN2_CTRL_00"                ,dbg_PE1_R_WIN2_CTRL_00              },
	{ 0x3338 ,N_FLD(dbg_PE1_R_WIN2_CTRL_01)              ,"PE1_R_WIN2_CTRL_01"                ,dbg_PE1_R_WIN2_CTRL_01              },
	{ 0x333c ,N_FLD(dbg_PE1_R_WIN2_CTRL_02)              ,"PE1_R_WIN2_CTRL_02"                ,dbg_PE1_R_WIN2_CTRL_02              },
	{ 0x3340 ,N_FLD(dbg_PE1_R_WIN2_CTRL_03)              ,"PE1_R_WIN2_CTRL_03"                ,dbg_PE1_R_WIN2_CTRL_03              },
	{ 0x3344 ,N_FLD(dbg_PE1_R_WIN2_CTRL_04)              ,"PE1_R_WIN2_CTRL_04"                ,dbg_PE1_R_WIN2_CTRL_04              },
	{ 0x3350 ,N_FLD(dbg_PE1_R_APL_CTRL_00)               ,"PE1_R_APL_CTRL_00"                 ,dbg_PE1_R_APL_CTRL_00               },
	{ 0x3354 ,N_FLD(dbg_PE1_R_APL_CTRL_01)               ,"PE1_R_APL_CTRL_01"                 ,dbg_PE1_R_APL_CTRL_01               },
	{ 0x3358 ,N_FLD(dbg_PE1_R_APL_CTRL_02)               ,"PE1_R_APL_CTRL_02"                 ,dbg_PE1_R_APL_CTRL_02               },
	{ 0x335c ,N_FLD(dbg_PE1_R_APL_STAT_00)               ,"PE1_R_APL_STAT_00"                 ,dbg_PE1_R_APL_STAT_00               },
	{ 0x3360 ,N_FLD(dbg_PE1_R_APL_STAT_01)               ,"PE1_R_APL_STAT_01"                 ,dbg_PE1_R_APL_STAT_01               },
	{ 0x3364 ,N_FLD(dbg_PE1_R_APL_STAT_02)               ,"PE1_R_APL_STAT_02"                 ,dbg_PE1_R_APL_STAT_02               },
	{ 0x3368 ,N_FLD(dbg_PE1_R_APL_STAT_03)               ,"PE1_R_APL_STAT_03"                 ,dbg_PE1_R_APL_STAT_03               },
	{ 0x33a0 ,N_FLD(dbg_PE1_R_FILM_CTRL_00)              ,"PE1_R_FILM_CTRL_00"                ,dbg_PE1_R_FILM_CTRL_00              },
	{ 0x33a4 ,N_FLD(dbg_PE1_R_FILM_CTRL_01)              ,"PE1_R_FILM_CTRL_01"                ,dbg_PE1_R_FILM_CTRL_01              },
	{ 0x33a8 ,N_FLD(dbg_PE1_R_FILM_CTRL_02)              ,"PE1_R_FILM_CTRL_02"                ,dbg_PE1_R_FILM_CTRL_02              },
	{ 0x33b0 ,N_FLD(dbg_PE1_R_WIN3_CTRL_00)              ,"PE1_R_WIN3_CTRL_00"                ,dbg_PE1_R_WIN3_CTRL_00              },
	{ 0x33b4 ,N_FLD(dbg_PE1_R_WIN3_CTRL_01)              ,"PE1_R_WIN3_CTRL_01"                ,dbg_PE1_R_WIN3_CTRL_01              },
	{ 0x33b8 ,N_FLD(dbg_PE1_R_WIN3_CTRL_02)              ,"PE1_R_WIN3_CTRL_02"                ,dbg_PE1_R_WIN3_CTRL_02              },
	{ 0x33bc ,N_FLD(dbg_PE1_R_WIN3_CTRL_03)              ,"PE1_R_WIN3_CTRL_03"                ,dbg_PE1_R_WIN3_CTRL_03              },
	{ 0x33c0 ,N_FLD(dbg_PE1_R_WIN3_CTRL_04)              ,"PE1_R_WIN3_CTRL_04"                ,dbg_PE1_R_WIN3_CTRL_04              },
	{ 0x33d0 ,N_FLD(dbg_PE1_R_DERH_CTRL_00)              ,"PE1_R_DERH_CTRL_00"                ,dbg_PE1_R_DERH_CTRL_00              },
	{ 0x33d4 ,N_FLD(dbg_PE1_R_DERH_CTRL_01)              ,"PE1_R_DERH_CTRL_01"                ,dbg_PE1_R_DERH_CTRL_01              },
	{ 0x33d8 ,N_FLD(dbg_PE1_R_DERH_CTRL_02)              ,"PE1_R_DERH_CTRL_02"                ,dbg_PE1_R_DERH_CTRL_02              },
	{ 0x33dc ,N_FLD(dbg_PE1_R_DERH_CTRL_03)              ,"PE1_R_DERH_CTRL_03"                ,dbg_PE1_R_DERH_CTRL_03              },
	{ 0x33e0 ,N_FLD(dbg_PE1_R_DERH_CTRL_04)              ,"PE1_R_DERH_CTRL_04"                ,dbg_PE1_R_DERH_CTRL_04              },
	{ 0x33e4 ,N_FLD(dbg_PE1_R_DERH_CTRL_05)              ,"PE1_R_DERH_CTRL_05"                ,dbg_PE1_R_DERH_CTRL_05              },
	{ 0x33e8 ,N_FLD(dbg_PE1_R_DERH_CTRL_06)              ,"PE1_R_DERH_CTRL_06"                ,dbg_PE1_R_DERH_CTRL_06              },
	{ 0x33ec ,N_FLD(dbg_PE1_R_DERH_CTRL_07)              ,"PE1_R_DERH_CTRL_07"                ,dbg_PE1_R_DERH_CTRL_07              },
	{ 0x33f0 ,N_FLD(dbg_PE1_R_DERH_CTRL_08)              ,"PE1_R_DERH_CTRL_08"                ,dbg_PE1_R_DERH_CTRL_08              },
	{ 0x33f4 ,N_FLD(dbg_PE1_R_DERH_CTRL_09)              ,"PE1_R_DERH_CTRL_09"                ,dbg_PE1_R_DERH_CTRL_09              },
	{ 0x3400 ,N_FLD(dbg_PE1_R_DERV_CTRL_0)               ,"PE1_R_DERV_CTRL_0"                 ,dbg_PE1_R_DERV_CTRL_0               },
	{ 0x3404 ,N_FLD(dbg_PE1_R_DERV_CTRL_1)               ,"PE1_R_DERV_CTRL_1"                 ,dbg_PE1_R_DERV_CTRL_1               },
	{ 0x3408 ,N_FLD(dbg_PE1_R_DERV_CTRL_2)               ,"PE1_R_DERV_CTRL_2"                 ,dbg_PE1_R_DERV_CTRL_2               },
	{ 0x340c ,N_FLD(dbg_PE1_R_DERV_CTRL_3)               ,"PE1_R_DERV_CTRL_3"                 ,dbg_PE1_R_DERV_CTRL_3               },
	{ 0x3410 ,0                                          ,"PE1_R_DP_CTRL_00"                  ,NULL                                },
	{ 0x3414 ,N_FLD(dbg_PE1_R_DP_CTRL_01)                ,"PE1_R_DP_CTRL_01"                  ,dbg_PE1_R_DP_CTRL_01                },
	{ 0x3418 ,0                                          ,"PE1_R_DP_CTRL_02"                  ,NULL                                },
	{ 0x341c ,0                                          ,"PE1_R_DP_CTRL_03"                  ,NULL                                },
	{ 0x3420 ,N_FLD(dbg_PE1_R_CORING_STAT_00)            ,"PE1_R_CORING_STAT_00"              ,dbg_PE1_R_CORING_STAT_00            },
	{ 0x3424 ,N_FLD(dbg_PE1_R_CORING_STAT_01)            ,"PE1_R_CORING_STAT_01"              ,dbg_PE1_R_CORING_STAT_01            },
	{ 0x3428 ,0                                          ,"PE1_R_CORING_STAT_02"              ,NULL                                },
	{ 0x342c ,0                                          ,"PE1_R_CORING_STAT_03"              ,NULL                                },
	{ 0x3470 ,N_FLD(dbg_PE1_R_DERH_CTRL_0A)              ,"PE1_R_DERH_CTRL_0A"                ,dbg_PE1_R_DERH_CTRL_0A              },
	{ 0x3474 ,N_FLD(dbg_PE1_R_DERH_CTRL_0B)              ,"PE1_R_DERH_CTRL_0B"                ,dbg_PE1_R_DERH_CTRL_0B              },
	{ 0x3478 ,N_FLD(dbg_PE1_R_DERH_CTRL_0C)              ,"PE1_R_DERH_CTRL_0C"                ,dbg_PE1_R_DERH_CTRL_0C              },
	{ 0x347c ,0                                          ,"PE1_R_DERH_CTRL_0D"                ,NULL                                },
	{ 0x3490 ,N_FLD(dbg_PE1_R_SP_CTRL_00)                ,"PE1_R_SP_CTRL_00"                  ,dbg_PE1_R_SP_CTRL_00                },
	{ 0x3494 ,N_FLD(dbg_PE1_R_SP_CTRL_01)                ,"PE1_R_SP_CTRL_01"                  ,dbg_PE1_R_SP_CTRL_01                },
	{ 0x3498 ,N_FLD(dbg_PE1_R_SP_CTRL_02)                ,"PE1_R_SP_CTRL_02"                  ,dbg_PE1_R_SP_CTRL_02                },
	{ 0x349c ,0                                          ,"PE1_R_SP_CTRL_03"                  ,NULL                                },
	{ 0x34a0 ,N_FLD(dbg_PE1_R_SP_CTRL_04)                ,"PE1_R_SP_CTRL_04"                  ,dbg_PE1_R_SP_CTRL_04                },
	{ 0x34a8 ,0                                          ,"PE1_R_SP_CTRL_05"                  ,NULL                                },
	{ 0x34ac ,N_FLD(dbg_PE1_R_SP_CTRL_06)                ,"PE1_R_SP_CTRL_06"                  ,dbg_PE1_R_SP_CTRL_06                },
	{ 0x34b0 ,N_FLD(dbg_PE1_R_SP_CTRL_07)                ,"PE1_R_SP_CTRL_07"                  ,dbg_PE1_R_SP_CTRL_07                },
	{ 0x34b4 ,N_FLD(dbg_PE1_R_SP_CTRL_08)                ,"PE1_R_SP_CTRL_08"                  ,dbg_PE1_R_SP_CTRL_08                },
	{ 0x34b8 ,N_FLD(dbg_PE1_R_SP_CTRL_09)                ,"PE1_R_SP_CTRL_09"                  ,dbg_PE1_R_SP_CTRL_09                },
	{ 0x34bc ,N_FLD(dbg_PE1_R_SP_CTRL_0A)                ,"PE1_R_SP_CTRL_0A"                  ,dbg_PE1_R_SP_CTRL_0A                },
	{ 0x34c0 ,N_FLD(dbg_PE1_R_SP_CTRL_0B)                ,"PE1_R_SP_CTRL_0B"                  ,dbg_PE1_R_SP_CTRL_0B                },
	{ 0x34c4 ,N_FLD(dbg_PE1_R_SP_CTRL_0C)                ,"PE1_R_SP_CTRL_0C"                  ,dbg_PE1_R_SP_CTRL_0C                },
	{ 0x34d0 ,N_FLD(dbg_PE1_R_DEBUG_CTRL_00)             ,"PE1_R_DEBUG_CTRL_00"               ,dbg_PE1_R_DEBUG_CTRL_00             },
	{ 0x34d4 ,N_FLD(dbg_PE1_R_DEBUG_CTRL_01)             ,"PE1_R_DEBUG_CTRL_01"               ,dbg_PE1_R_DEBUG_CTRL_01             },
	{ 0x34f0 ,N_FLD(dbg_PE1_R_MP_CTRL_00)                ,"PE1_R_MP_CTRL_00"                  ,dbg_PE1_R_MP_CTRL_00                },
	{ 0x34f4 ,N_FLD(dbg_PE1_R_MP_CTRL_01)                ,"PE1_R_MP_CTRL_01"                  ,dbg_PE1_R_MP_CTRL_01                },
	{ 0x34f8 ,N_FLD(dbg_PE1_R_MP_CTRL_02)                ,"PE1_R_MP_CTRL_02"                  ,dbg_PE1_R_MP_CTRL_02                },
	{ 0x34fc ,0                                          ,"PE1_R_MP_CTRL_03"                  ,NULL                                },
	{ 0x3500 ,N_FLD(dbg_PE1_R_MP_CTRL_04)                ,"PE1_R_MP_CTRL_04"                  ,dbg_PE1_R_MP_CTRL_04                },
	{ 0x3508 ,0                                          ,"PE1_R_MP_CTRL_05"                  ,NULL                                },
	{ 0x350c ,N_FLD(dbg_PE1_R_MP_CTRL_06)                ,"PE1_R_MP_CTRL_06"                  ,dbg_PE1_R_MP_CTRL_06                },
	{ 0x3510 ,N_FLD(dbg_PE1_R_MP_CTRL_07)                ,"PE1_R_MP_CTRL_07"                  ,dbg_PE1_R_MP_CTRL_07                },
	{ 0x3514 ,N_FLD(dbg_PE1_R_MP_CTRL_08)                ,"PE1_R_MP_CTRL_08"                  ,dbg_PE1_R_MP_CTRL_08                },
	{ 0x3518 ,N_FLD(dbg_PE1_R_MP_CTRL_09)                ,"PE1_R_MP_CTRL_09"                  ,dbg_PE1_R_MP_CTRL_09                },
	{ 0x351c ,N_FLD(dbg_PE1_R_MP_CTRL_0A)                ,"PE1_R_MP_CTRL_0A"                  ,dbg_PE1_R_MP_CTRL_0A                },
	{ 0x3520 ,N_FLD(dbg_PE1_R_MP_CTRL_0B)                ,"PE1_R_MP_CTRL_0B"                  ,dbg_PE1_R_MP_CTRL_0B                },
	{ 0x3524 ,N_FLD(dbg_PE1_R_MP_CTRL_0C)                ,"PE1_R_MP_CTRL_0C"                  ,dbg_PE1_R_MP_CTRL_0C                },
	{ 0x3530 ,N_FLD(dbg_PE1_R_CTI_CTRL_00)               ,"PE1_R_CTI_CTRL_00"                 ,dbg_PE1_R_CTI_CTRL_00               },
	{ 0x3534 ,0                                          ,"PE1_R_CTI_CTRL_01"                 ,NULL                                },
	{ 0x3538 ,N_FLD(dbg_PE1_R_CTI_CTRL_02)               ,"PE1_R_CTI_CTRL_02"                 ,dbg_PE1_R_CTI_CTRL_02               },
	{ 0x3550 ,N_FLD(dbg_PE1_R_BLUR_CTRL)                 ,"PE1_R_BLUR_CTRL"                   ,dbg_PE1_R_BLUR_CTRL                 },
	{ 0x3560 ,N_FLD(dbg_PE1_R_CORING_CTRL_00)            ,"PE1_R_CORING_CTRL_00"              ,dbg_PE1_R_CORING_CTRL_00            },
	{ 0x3564 ,N_FLD(dbg_PE1_R_CORING_CTRL_01)            ,"PE1_R_CORING_CTRL_01"              ,dbg_PE1_R_CORING_CTRL_01            },
	{ 0x3568 ,N_FLD(dbg_PE1_R_CORING_CTRL_02)            ,"PE1_R_CORING_CTRL_02"              ,dbg_PE1_R_CORING_CTRL_02            },
	{ 0x356c ,N_FLD(dbg_PE1_R_CORING_CTRL_03)            ,"PE1_R_CORING_CTRL_03"              ,dbg_PE1_R_CORING_CTRL_03            },
	{ 0x3570 ,N_FLD(dbg_PE1_R_CORING_CTRL_04)            ,"PE1_R_CORING_CTRL_04"              ,dbg_PE1_R_CORING_CTRL_04            },
	{ 0x3574 ,N_FLD(dbg_PE1_R_CORING_CTRL_05)            ,"PE1_R_CORING_CTRL_05"              ,dbg_PE1_R_CORING_CTRL_05            },
	{ 0x3578 ,N_FLD(dbg_PE1_R_CORING_CTRL_06)            ,"PE1_R_CORING_CTRL_06"              ,dbg_PE1_R_CORING_CTRL_06            },
	{ 0x357c ,N_FLD(dbg_PE1_R_CORING_CTRL_07)            ,"PE1_R_CORING_CTRL_07"              ,dbg_PE1_R_CORING_CTRL_07            },
	{ 0x3580 ,N_FLD(dbg_PE1_R_CORING_CTRL_08)            ,"PE1_R_CORING_CTRL_08"              ,dbg_PE1_R_CORING_CTRL_08            },
	{ 0x3584 ,N_FLD(dbg_PE1_R_CORING_CTRL_09)            ,"PE1_R_CORING_CTRL_09"              ,dbg_PE1_R_CORING_CTRL_09            },
	{ 0x3590 ,N_FLD(dbg_PE1_R_DJ_CTRL_00)                ,"PE1_R_DJ_CTRL_00"                  ,dbg_PE1_R_DJ_CTRL_00                },
	{ 0x3594 ,N_FLD(dbg_PE1_R_DJ_CTRL_01)                ,"PE1_R_DJ_CTRL_01"                  ,dbg_PE1_R_DJ_CTRL_01                },
	{ 0x3598 ,N_FLD(dbg_PE1_R_DJ_CTRL_02)                ,"PE1_R_DJ_CTRL_02"                  ,dbg_PE1_R_DJ_CTRL_02                },
	{ 0x359c ,N_FLD(dbg_PE1_R_DJ_CTRL_03)                ,"PE1_R_DJ_CTRL_03"                  ,dbg_PE1_R_DJ_CTRL_03                },
	{ 0x35a0 ,N_FLD(dbg_PE1_R_LEVEL_CTRL_00)             ,"PE1_R_LEVEL_CTRL_00"               ,dbg_PE1_R_LEVEL_CTRL_00             },
	{ 0x35a4 ,N_FLD(dbg_PE1_R_VSPYC_CTRL_00)             ,"PE1_R_VSPYC_CTRL_00"               ,dbg_PE1_R_VSPYC_CTRL_00             },
	{ 0x35a8 ,N_FLD(dbg_PE1_R_VSPYC_CTRL_01)             ,"PE1_R_VSPYC_CTRL_01"               ,dbg_PE1_R_VSPYC_CTRL_01             },
	{ 0x35b0 ,N_FLD(dbg_PE1_R_VSPRGB_CTRL_00)            ,"PE1_R_VSPRGB_CTRL_00"              ,dbg_PE1_R_VSPRGB_CTRL_00            },
	{ 0x35c0 ,N_FLD(dbg_PE1_R_XVY_CTRL_00)               ,"PE1_R_XVY_CTRL_00"                 ,dbg_PE1_R_XVY_CTRL_00               },
	{ 0x35c4 ,N_FLD(dbg_PE1_R_XVY_CTRL_01)               ,"PE1_R_XVY_CTRL_01"                 ,dbg_PE1_R_XVY_CTRL_01               },
	{ 0x35c8 ,N_FLD(dbg_PE1_R_XVY_CTRL_02)               ,"PE1_R_XVY_CTRL_02"                 ,dbg_PE1_R_XVY_CTRL_02               },
	{ 0x35cc ,N_FLD(dbg_PE1_R_XVY_CTRL_03)               ,"PE1_R_XVY_CTRL_03"                 ,dbg_PE1_R_XVY_CTRL_03               },
	{ 0x35d0 ,N_FLD(dbg_PE1_R_XVY_CTRL_04)               ,"PE1_R_XVY_CTRL_04"                 ,dbg_PE1_R_XVY_CTRL_04               },
	{ 0x35d4 ,N_FLD(dbg_PE1_R_XVY_CTRL_05)               ,"PE1_R_XVY_CTRL_05"                 ,dbg_PE1_R_XVY_CTRL_05               },
	{ 0x35d8 ,N_FLD(dbg_PE1_R_XVY_CTRL_06)               ,"PE1_R_XVY_CTRL_06"                 ,dbg_PE1_R_XVY_CTRL_06               },
	{ 0x35dc ,N_FLD(dbg_PE1_R_XVY_CTRL_07)               ,"PE1_R_XVY_CTRL_07"                 ,dbg_PE1_R_XVY_CTRL_07               },
	{ 0x35e0 ,N_FLD(dbg_PE1_R_XVY_CTRL_08)               ,"PE1_R_XVY_CTRL_08"                 ,dbg_PE1_R_XVY_CTRL_08               },
	{ 0x35e4 ,N_FLD(dbg_PE1_R_XVY_CTRL_09)               ,"PE1_R_XVY_CTRL_09"                 ,dbg_PE1_R_XVY_CTRL_09               },
	{ 0x35e8 ,N_FLD(dbg_PE1_R_XVY_CTRL_0A)               ,"PE1_R_XVY_CTRL_0A"                 ,dbg_PE1_R_XVY_CTRL_0A               },
	{ 0x35ec ,N_FLD(dbg_PE1_R_XVY_CTRL_0B)               ,"PE1_R_XVY_CTRL_0B"                 ,dbg_PE1_R_XVY_CTRL_0B               },
	{ 0x35f0 ,N_FLD(dbg_PE1_R_XVY_CTRL_0C)               ,"PE1_R_XVY_CTRL_0C"                 ,dbg_PE1_R_XVY_CTRL_0C               },
	{ 0x35f4 ,N_FLD(dbg_PE1_R_XVY_CTRL_0D)               ,"PE1_R_XVY_CTRL_0D"                 ,dbg_PE1_R_XVY_CTRL_0D               },
	{ 0x3600 ,N_FLD(dbg_PE1_R_CEN_CTRL_00)               ,"PE1_R_CEN_CTRL_00"                 ,dbg_PE1_R_CEN_CTRL_00               },
	{ 0x3604 ,N_FLD(dbg_PE1_R_CEN_CTRL_01)               ,"PE1_R_CEN_CTRL_01"                 ,dbg_PE1_R_CEN_CTRL_01               },
	{ 0x3608 ,N_FLD(dbg_PE1_R_CEN_CTRL_02)               ,"PE1_R_CEN_CTRL_02"                 ,dbg_PE1_R_CEN_CTRL_02               },
	{ 0x360c ,N_FLD(dbg_PE1_R_CEN_CTRL_03)               ,"PE1_R_CEN_CTRL_03"                 ,dbg_PE1_R_CEN_CTRL_03               },
	{ 0x3610 ,N_FLD(dbg_PE1_R_CEN_CTRL_04)               ,"PE1_R_CEN_CTRL_04"                 ,dbg_PE1_R_CEN_CTRL_04               },
	{ 0x3614 ,N_FLD(dbg_PE1_R_CEN_IA_CTRL)               ,"PE1_R_CEN_IA_CTRL"                 ,dbg_PE1_R_CEN_IA_CTRL               },
	{ 0x3618 ,N_FLD(dbg_PE1_R_CEN_IA_DATA)               ,"PE1_R_CEN_IA_DATA"                 ,dbg_PE1_R_CEN_IA_DATA               },
	{ 0x3630 ,N_FLD(dbg_PE1_R_LRCR_CTRL_00)              ,"PE1_R_LRCR_CTRL_00"                ,dbg_PE1_R_LRCR_CTRL_00              },
	{ 0x3634 ,N_FLD(dbg_PE1_R_LRCR_CTRL_01)              ,"PE1_R_LRCR_CTRL_01"                ,dbg_PE1_R_LRCR_CTRL_01              },
	{ 0x3638 ,N_FLD(dbg_PE1_R_LRCR_CTRL_02)              ,"PE1_R_LRCR_CTRL_02"                ,dbg_PE1_R_LRCR_CTRL_02              },
	{ 0x363c ,N_FLD(dbg_PE1_R_LRCR_CTRL_03)              ,"PE1_R_LRCR_CTRL_03"                ,dbg_PE1_R_LRCR_CTRL_03              },
	{ 0x3640 ,N_FLD(dbg_PE1_R_LRCR_CTRL_04)              ,"PE1_R_LRCR_CTRL_04"                ,dbg_PE1_R_LRCR_CTRL_04              },
	{ 0x3644 ,N_FLD(dbg_PE1_R_LRCR_CTRL_05)              ,"PE1_R_LRCR_CTRL_05"                ,dbg_PE1_R_LRCR_CTRL_05              },
	{ 0x3648 ,N_FLD(dbg_PE1_R_LRCR_CTRL_06)              ,"PE1_R_LRCR_CTRL_06"                ,dbg_PE1_R_LRCR_CTRL_06              },
	{ 0x364c ,N_FLD(dbg_PE1_R_LRCR_CTRL_07)              ,"PE1_R_LRCR_CTRL_07"                ,dbg_PE1_R_LRCR_CTRL_07              },
	{ 0x3650 ,N_FLD(dbg_PE1_R_LRCR_STAT_00)              ,"PE1_R_LRCR_STAT_00"                ,dbg_PE1_R_LRCR_STAT_00              },
	{ 0x3654 ,N_FLD(dbg_PE1_R_LRCR_STAT_01)              ,"PE1_R_LRCR_STAT_01"                ,dbg_PE1_R_LRCR_STAT_01              },
	{ 0x3658 ,N_FLD(dbg_PE1_R_LRCR_STAT_02)              ,"PE1_R_LRCR_STAT_02"                ,dbg_PE1_R_LRCR_STAT_02              },
	{ 0x3670 ,N_FLD(dbg_PE1_R_DCE_CTRL_00)               ,"PE1_R_DCE_CTRL_00"                 ,dbg_PE1_R_DCE_CTRL_00               },
	{ 0x3674 ,N_FLD(dbg_PE1_R_DCE_CTRL_01)               ,"PE1_R_DCE_CTRL_01"                 ,dbg_PE1_R_DCE_CTRL_01               },
	{ 0x3678 ,N_FLD(dbg_PE1_R_DCE_CTRL_02)               ,"PE1_R_DCE_CTRL_02"                 ,dbg_PE1_R_DCE_CTRL_02               },
	{ 0x367c ,N_FLD(dbg_PE1_R_DCE_CTRL_03)               ,"PE1_R_DCE_CTRL_03"                 ,dbg_PE1_R_DCE_CTRL_03               },
	{ 0x3680 ,N_FLD(dbg_PE1_R_DCE_CTRL_04)               ,"PE1_R_DCE_CTRL_04"                 ,dbg_PE1_R_DCE_CTRL_04               },
	{ 0x3684 ,N_FLD(dbg_PE1_R_DCE_CTRL_05)               ,"PE1_R_DCE_CTRL_05"                 ,dbg_PE1_R_DCE_CTRL_05               },
	{ 0x3688 ,N_FLD(dbg_PE1_R_DCE_IA_CTRL)               ,"PE1_R_DCE_IA_CTRL"                 ,dbg_PE1_R_DCE_IA_CTRL               },
	{ 0x368c ,N_FLD(dbg_PE1_R_DCE_IA_DATA)               ,"PE1_R_DCE_IA_DATA"                 ,dbg_PE1_R_DCE_IA_DATA               },
	{ 0x3690 ,N_FLD(dbg_PE1_R_DCE_CTRL_08)               ,"PE1_R_DCE_CTRL_08"                 ,dbg_PE1_R_DCE_CTRL_08               },
	{ 0x36a0 ,N_FLD(dbg_PE1_R_DCE_HIST_IA_CTRL)          ,"PE1_R_DCE_HIST_IA_CTRL"            ,dbg_PE1_R_DCE_HIST_IA_CTRL          },
	{ 0x36a4 ,0                                          ,"PE1_R_DCE_HIST_IA_DATA1"           ,NULL                                },
	{ 0x36a8 ,0                                          ,"PE1_R_DCE_HSIT_IA_DATA2"           ,NULL                                },
	{ 0x36ac ,N_FLD(dbg_PE1_R_DSE_CTRL_00)               ,"PE1_R_DSE_CTRL_00"                 ,dbg_PE1_R_DSE_CTRL_00               },
	{ 0x36b0 ,N_FLD(dbg_PE1_R_DSE_CTRL_01)               ,"PE1_R_DSE_CTRL_01"                 ,dbg_PE1_R_DSE_CTRL_01               },
	{ 0x36b4 ,N_FLD(dbg_PE1_R_DSE_CTRL_02)               ,"PE1_R_DSE_CTRL_02"                 ,dbg_PE1_R_DSE_CTRL_02               },
	{ 0x36b8 ,N_FLD(dbg_PE1_R_DSE_IA_CTRL)               ,"PE1_R_DSE_IA_CTRL"                 ,dbg_PE1_R_DSE_IA_CTRL               },
	{ 0x36bc ,N_FLD(dbg_PE1_R_DSE_IA_DATA)               ,"PE1_R_DSE_IA_DATA"                 ,dbg_PE1_R_DSE_IA_DATA               },
	{ 0x36c0 ,N_FLD(dbg_PE1_R_WB_CTRL_00)                ,"PE1_R_WB_CTRL_00"                  ,dbg_PE1_R_WB_CTRL_00                },
	{ 0x36c4 ,N_FLD(dbg_PE1_R_WB_CTRL_01)                ,"PE1_R_WB_CTRL_01"                  ,dbg_PE1_R_WB_CTRL_01                },
	{ 0x36c8 ,N_FLD(dbg_PE1_R_WB_CTRL_02)                ,"PE1_R_WB_CTRL_02"                  ,dbg_PE1_R_WB_CTRL_02                },
	{ 0x36f0 ,N_FLD(dbg_PE1_R_GMC_CTRL_00)               ,"PE1_R_GMC_CTRL_00"                 ,dbg_PE1_R_GMC_CTRL_00               },
	{ 0x36f4 ,N_FLD(dbg_PE1_R_GMC_CTRL_01)               ,"PE1_R_GMC_CTRL_01"                 ,dbg_PE1_R_GMC_CTRL_01               },
	{ 0x36f8 ,N_FLD(dbg_PE1_R_GMC_CTRL_02)               ,"PE1_R_GMC_CTRL_02"                 ,dbg_PE1_R_GMC_CTRL_02               },
	{ 0x36fc ,N_FLD(dbg_PE1_R_GMC_IA_CTRL)               ,"PE1_R_GMC_IA_CTRL"                 ,dbg_PE1_R_GMC_IA_CTRL               },
	{ 0x3700 ,N_FLD(dbg_PE1_R_GMC_IA_DATA)               ,"PE1_R_GMC_IA_DATA"                 ,dbg_PE1_R_GMC_IA_DATA               },
	{ 0x3704 ,N_FLD(dbg_PE1_R_GMC_CTRL_03)               ,"PE1_R_GMC_CTRL_03"                 ,dbg_PE1_R_GMC_CTRL_03               },
	{ 0x3720 ,N_FLD(dbg_PE1_R_SQM_CTRL_0)                ,"PE1_R_SQM_CTRL_0"                  ,dbg_PE1_R_SQM_CTRL_0                },
	{ 0x3724 ,N_FLD(dbg_PE1_R_SQM_CTRL_1)                ,"PE1_R_SQM_CTRL_1"                  ,dbg_PE1_R_SQM_CTRL_1                },
	{ 0x3728 ,N_FLD(dbg_PE1_R_SQM_CTRL_2)                ,"PE1_R_SQM_CTRL_2"                  ,dbg_PE1_R_SQM_CTRL_2                },
	{ 0x372c ,N_FLD(dbg_PE1_R_SQM_CTRL_3)                ,"PE1_R_SQM_CTRL_3"                  ,dbg_PE1_R_SQM_CTRL_3                },
	{ 0x3730 ,N_FLD(dbg_PE1_R_SQM_CTRL_4)                ,"PE1_R_SQM_CTRL_4"                  ,dbg_PE1_R_SQM_CTRL_4                },
	{ 0x3734 ,N_FLD(dbg_PE1_R_SQM_CTRL_5)                ,"PE1_R_SQM_CTRL_5"                  ,dbg_PE1_R_SQM_CTRL_5                },
	{ 0x3738 ,N_FLD(dbg_PE1_R_SQM_STAT)                  ,"PE1_R_SQM_STAT"                    ,dbg_PE1_R_SQM_STAT                  },
	{ 0x3750 ,N_FLD(dbg_PE1_R_BBD2D_CTRL_0)              ,"PE1_R_BBD2D_CTRL_0"                ,dbg_PE1_R_BBD2D_CTRL_0              },
	{ 0x3754 ,N_FLD(dbg_PE1_R_BBD2D_CTRL_1)              ,"PE1_R_BBD2D_CTRL_1"                ,dbg_PE1_R_BBD2D_CTRL_1              },
	{ 0x3758 ,N_FLD(dbg_PE1_R_BBD2D_CTRL_2)              ,"PE1_R_BBD2D_CTRL_2"                ,dbg_PE1_R_BBD2D_CTRL_2              },
	{ 0x375c ,N_FLD(dbg_PE1_R_BBD2D_STAT_0)              ,"PE1_R_BBD2D_STAT_0"                ,dbg_PE1_R_BBD2D_STAT_0              },
	{ 0x3760 ,N_FLD(dbg_PE1_R_BBD2D_STAT_1)              ,"PE1_R_BBD2D_STAT_1"                ,dbg_PE1_R_BBD2D_STAT_1              },
	{ 0x3770 ,N_FLD(dbg_PE1_R_BBD3D_CTRL_00)             ,"PE1_R_BBD3D_CTRL_00"               ,dbg_PE1_R_BBD3D_CTRL_00             },
	{ 0x3774 ,N_FLD(dbg_PE1_R_BBD3D_CTRL_01)             ,"PE1_R_BBD3D_CTRL_01"               ,dbg_PE1_R_BBD3D_CTRL_01             },
	{ 0x3778 ,N_FLD(dbg_PE1_R_BBD3D_CTRL_02)             ,"PE1_R_BBD3D_CTRL_02"               ,dbg_PE1_R_BBD3D_CTRL_02             },
	{ 0x377c ,N_FLD(dbg_PE1_R_BBD3D_STAT_0)              ,"PE1_R_BBD3D_STAT_0"                ,dbg_PE1_R_BBD3D_STAT_0              },
	{ 0x37b0 ,N_FLD(dbg_P1R_PE1_L_G_HIST_IA_CTRL)        ,"P1R_PE1_L_G_HIST_IA_CTRL"          ,dbg_P1R_PE1_L_G_HIST_IA_CTRL        },
	{ 0x37b4 ,0                                          ,"P1R_PE1_L_G_HIST_IA_DATA"          ,NULL                                },
	{ 0x37b8 ,N_FLD(dbg_P1R_PE1_L_B_HIST_IA_CTRL)        ,"P1R_PE1_L_B_HIST_IA_CTRL"          ,dbg_P1R_PE1_L_B_HIST_IA_CTRL        },
	{ 0x37bc ,0                                          ,"P1R_PE1_L_B_HIST_IA_DATA"          ,NULL                                },
	{ 0x37c0 ,N_FLD(dbg_P1R_PE1_L_R_HIST_IA_CTRL)        ,"P1R_PE1_L_R_HIST_IA_CTRL"          ,dbg_P1R_PE1_L_R_HIST_IA_CTRL        },
	{ 0x37c4 ,0                                          ,"P1R_PE1_L_R_HIST_IA_DATA"          ,NULL                                },
	{ 0x37c8 ,N_FLD(dbg_P1R_PE1_R_G_HIST_IA_CTRL)        ,"P1R_PE1_R_G_HIST_IA_CTRL"          ,dbg_P1R_PE1_R_G_HIST_IA_CTRL        },
	{ 0x37cc ,0                                          ,"P1R_PE1_R_G_HIST_IA_DATA"          ,NULL                                },
	{ 0x37d0 ,N_FLD(dbg_P1R_PE1_R_B_HIST_IA_CTRL)        ,"P1R_PE1_R_B_HIST_IA_CTRL"          ,dbg_P1R_PE1_R_B_HIST_IA_CTRL        },
	{ 0x37d4 ,0                                          ,"P1R_PE1_R_B_HIST_IA_DATA"          ,NULL                                },
	{ 0x37d8 ,N_FLD(dbg_P1R_PE1_R_R_HIST_IA_CTRL)        ,"P1R_PE1_R_R_HIST_IA_CTRL"          ,dbg_P1R_PE1_R_R_HIST_IA_CTRL        },
	{ 0x37dc ,0                                          ,"P1R_PE1_R_R_HIST_IA_DATA"          ,NULL                                },
	{ 0 , } // end marker
};

#endif
