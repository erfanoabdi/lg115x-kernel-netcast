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
	0x1320 PE1_L_WIN_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN_CTRL_00[] = {
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
	0x1324 PE1_L_WIN_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x1328 PE1_L_WIN_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x132c PE1_L_WIN_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x1330 PE1_L_WIN_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WIN_CTRL_04[] = {
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
	0x135c PE1_L_APL_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_y"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"apl_rgb"                         },
};

/*--------------------------------------------
	0x1360 PE1_L_APL_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_APL_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_b"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"apl_g"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"apl_r"                           },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"washing_num_of_bar_x"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"washing_num_of_bar_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"washing_speed"                   },
};

/*--------------------------------------------
	0x1378 PE1_L_TPG_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"patch_en"                        },
};

/*--------------------------------------------
	0x137c PE1_L_TPG_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TPG_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"tpg_indir_addr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"tpg_indir_ai_en"                 },
};

/*--------------------------------------------
	0x1380 PE1_L_TPG_IA_DATA
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
	0x13c0 PE1_L_HFNR_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_HFNR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"flats_t0_fc0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"flats_t0_fcs"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"flats_t1_fc0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"flats_t1_fc1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"flats_t0_fcp"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"flats_t0_fcd"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"t0_bc0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,14 ,"t1_bc0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"dth_t0_dth0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"h_disable"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dth_t0_dths"                     },
};

/*--------------------------------------------
	0x13c4 PE1_L_HFNR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_HFNR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dth_t0_dthp"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"dth_t1_dth0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"dth_t1_dth1"                     },
};

/*--------------------------------------------
	0x13d0 PE1_L_LSR_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vsum_mode"                       },
};

/*--------------------------------------------
	0x13d4 PE1_L_LSR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"a_gen_of_y"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"a_gen_of_c"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"avg_flt_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"avg_flt_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"max_flt_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"max_flt_en"                      },
};

/*--------------------------------------------
	0x13d8 PE1_L_LSR_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_02[] = {
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
	0x13dc PE1_L_LSR_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"a_mux_for_edge_gaintable"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"a_mux_for_detail_filter"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"a_mux_for_edge_filter"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"a_scaling_flat_filter_"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"a_mux_for_flat_filter"           },
};

/*--------------------------------------------
	0x13e0 PE1_L_LSR_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"dbg_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"sum_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"enh_en_cc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"enh_en_yy"                       },
};

/*--------------------------------------------
	0x13e4 PE1_L_LSR_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vmm_param"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"csft_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"th_gain_edge"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"th_gain_flat"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"th_manual_th"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"th_manual_en"                    },
};

/*--------------------------------------------
	0x13e8 PE1_L_LSR_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"edge_filter_white_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"edge_filter_black_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"amean_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"edge_filter_v_tap"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edge_c_filter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"edge_y_filter_en"                },
};

/*--------------------------------------------
	0x13ec PE1_L_LSR_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"flat_filter_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"flat_filter_en"                  },
};

/*--------------------------------------------
	0x13f0 PE1_L_LSR_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl0_y0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl0_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"amod_ctrl0_y1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"amod_ctrl0_x1"                   },
};

/*--------------------------------------------
	0x13f4 PE1_L_LSR_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl1_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl1_x1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"y_c_mux_control"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,19 ,"chroma_weight"                   },
};

/*--------------------------------------------
	0x1400 PE1_L_DER_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DER_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"der_v_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"der_gain_mapping"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"bif_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"output_mux"                      },
};

/*--------------------------------------------
	0x1404 PE1_L_DER_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_DER_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gain_th0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_th1"                        },
};

/*--------------------------------------------
	0x1410 PE1_L_LSR_DTL_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"detail_enhancer_enable"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"debug_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"debug_image"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_w"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain_b"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"detail_measure_for_sca"          },
};

/*--------------------------------------------
	0x1414 PE1_L_LSR_DTL_CTRL_01
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1418 PE1_L_LSR_DTL_CTRL_02
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x141c PE1_L_LSR_DTL_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"um3x3_type"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"um3x3_gain"                      },
};

/*--------------------------------------------
	0x1420 PE1_L_LSR_DTL_CTRL_04
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1424 PE1_L_LSR_DTL_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"manual_coring_enable"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"coring_post_filtering_type"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"coring_post_filtering_enable"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"coring_mmd_size"                 },
};

/*--------------------------------------------
	0x1428 PE1_L_LSR_DTL_CTRL_06
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x142c PE1_L_LSR_DTL_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"coring_mmd_th_l1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_mmd_th_l2"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_mmd_th_h1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_mmd_th_h2"                },
};

/*--------------------------------------------
	0x1430 PE1_L_LSR_DTL_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"post_filterig_enable"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"post_filtering_y_delta"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"post_filtering_y_th"             },
};

/*--------------------------------------------
	0x1434 PE1_L_LSR_DTL_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"lgain_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"lgain_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"lgain_apl_type"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_low_th0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lgain_low_th1"                   },
};

/*--------------------------------------------
	0x1438 PE1_L_LSR_DTL_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lgain_high_th0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_high_th1"                  },
};

/*--------------------------------------------
	0x143c PE1_L_LSR_DTL_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gain_balancing_on_off"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"delta_axis_resolution"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_x2"                           },
};

/*--------------------------------------------
	0x1440 PE1_L_LSR_DTL_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ed_y1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_y3"                           },
};

/*--------------------------------------------
	0x1444 PE1_L_LSR_DTL_CTRL_0D
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_CTRL_0D[] = {
};

/*--------------------------------------------
	0x1450 PE1_L_LSR_DTL_EE_CTRL_00
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1454 PE1_L_LSR_DTL_EE_CTRL_01
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1458 PE1_L_LSR_DTL_EE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_EE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"filter_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lap_gain"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"sobel_gx_gain"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x145c PE1_L_LSR_DTL_EE_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_EE_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"h_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"v_gain"                          },
};

/*--------------------------------------------
	0x1460 PE1_L_LSR_DTL_EE_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_EE_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gain_balancing_on_off"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"delta_axis_resolution"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_x2"                           },
};

/*--------------------------------------------
	0x1464 PE1_L_LSR_DTL_EE_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_DTL_EE_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ed_y1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_y3"                           },
};

/*--------------------------------------------
	0x1470 PE1_L_LSR_GT_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_GT_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gt_detail_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"gt_edge_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"gt_flat_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"gt_detail_manual_gain"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"gt_edge_manual_gain"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"gt_flat_manual_gain"             },
};

/*--------------------------------------------
	0x1474 PE1_L_LSR_GT_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_GT_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"gt_interpolation_type"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"interpol_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"interpol_x1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"interpol_x2"                     },
};

/*--------------------------------------------
	0x1478 PE1_L_LSR_GT_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_GT_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"th1"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"th2"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"th3"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"pcm_th"                          },
};

/*--------------------------------------------
	0x147c PE1_L_LSR_GT_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_GT_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_manual_sqa_measure"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"auto_sqa_measure_type"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"hdm_pcm_selection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"sqm_bit_resolution"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"manual_sqa_value"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hd_measure"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"pc_measure"                      },
};

/*--------------------------------------------
	0x1480 PE1_L_LSR_GT_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_GT_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"source_quality_measure"          },
};

/*--------------------------------------------
	0x1484 PE1_L_LSR_GT_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_GT_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"index"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"edf"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"auto_increment"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gt_enable"                       },
};

/*--------------------------------------------
	0x1488 PE1_L_LSR_GT_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_GT_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"gt_wdata0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"gt_wdata1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"gt_wdata2"                       },
};

/*--------------------------------------------
	0x14a0 PE1_L_LSR_SCA_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"sca_gain_display"                },
};

/*--------------------------------------------
	0x14a4 PE1_L_LSR_SCA_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"sca_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"sca_gain"                        },
};

/*--------------------------------------------
	0x14a8 PE1_L_LSR_SCA_CTRL_02
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x14ac PE1_L_LSR_SCA_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x14b0 PE1_L_LSR_SCA_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"enable_sca_to_flat_filter"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"gain_of_sca_to_flat_filter"      },
};

/*--------------------------------------------
	0x14b4 PE1_L_LSR_SCA_CTRL_05
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x14b8 PE1_L_LSR_SCA_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_debug_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"show_sqm1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"show_cr_info"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"debug_bar_gain_position"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"measure_display_gain"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"show_tpg"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"show_hdm_pcm_area"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"show_sqm2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,10 ,"sqm2_debug_image"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,15 ,"show_bbd"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"bbd_line_width"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"show_apl"                        },
};

/*--------------------------------------------
	0x14bc PE1_L_LSR_SCA_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"y_grad_gain"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cb_grad_gain"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cr_grad_gain"                    },
};

/*--------------------------------------------
	0x14c0 PE1_L_LSR_SCA_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_range_min"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"y_range_max"                     },
};

/*--------------------------------------------
	0x14c4 PE1_L_LSR_SCA_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cb_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cb_range_max"                    },
};

/*--------------------------------------------
	0x14c8 PE1_L_LSR_SCA_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cr_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cr_range_max"                    },
};

/*--------------------------------------------
	0x14cc PE1_L_LSR_SCA_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"gain_type"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,2  ,"color_region"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"auto_increment"                  },
};

/*--------------------------------------------
	0x14d0 PE1_L_LSR_SCA_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_SCA_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"x2"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"g1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"g2"                              },
};

/*--------------------------------------------
	0x14e0 PE1_L_LSR_CRG_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CRG_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"hif_crg_lsr_address"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_crg_lsr_ai"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_crg_lsr_wr"                  },
};

/*--------------------------------------------
	0x14e4 PE1_L_LSR_CRG_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LSR_CRG_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"value"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,10 ,"saturation"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"hue"                             },
};

/*--------------------------------------------
	0x14f0 PE1_L_SHP_EDGE_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_EDGE_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edge_enhance_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"edge_enhance_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"lm_mode"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"lti_level"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"edge_operator_selection"         },
};

/*--------------------------------------------
	0x14f4 PE1_L_SHP_EDGE_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_EDGE_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vertical_gain"                   },
};

/*--------------------------------------------
	0x14f8 PE1_L_SHP_EDGE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_EDGE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sobel_weight"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"laplacian_weight"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sobel_manual_mode_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x14fc PE1_L_SHP_EDGE_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_EDGE_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum_low_th1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum_low_th2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum_high_th1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum_high_th2"                    },
};

/*--------------------------------------------
	0x1500 PE1_L_SHP_EDGE_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_EDGE_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"laplacian_offset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"debug_selection"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"debug_enable"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gx_weight_manual_mode"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gx_weight_manual_gain"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"par_filter_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"par_out_sel"                     },
};

/*--------------------------------------------
	0x1508 PE1_L_SHP_EDGE_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_EDGE_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"coring_enable"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"coring_mmd_h"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"coring_mmd_v"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"coring_low_th_resol"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_low_th1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_low_th2"                  },
};

/*--------------------------------------------
	0x150c PE1_L_SHP_EDGE_CTRL_06
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1510 PE1_L_SHP_EDGE_CTRL_07
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1514 PE1_L_SHP_EDGE_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_EDGE_CTRL_08[] = {
};

/*--------------------------------------------
	0x1520 PE1_L_CTI_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_CTI_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"tap_size"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cti_gain"                        },
};

/*--------------------------------------------
	0x1524 PE1_L_CTI_CTRL_01
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1528 PE1_L_CTI_CTRL_02
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
	0x1530 PE1_L_SHP_UM_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"coring_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"coring_diff_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"filter_tap"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"avg_type"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,5  ,"coring_mmd_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_w"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain_b"                          },
};

/*--------------------------------------------
	0x1534 PE1_L_SHP_UM_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"coring_th_low1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th_low2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_th_high1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_th_high2"                 },
};

/*--------------------------------------------
	0x1538 PE1_L_SHP_UM_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"lgain_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"lgain_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"lgain_apl_type"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_low_th0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lgain_low_th1"                   },
};

/*--------------------------------------------
	0x153c PE1_L_SHP_UM_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lgain_high_th0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_high_th1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sca_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"sca_gain"                        },
};

/*--------------------------------------------
	0x1540 PE1_L_SHP_UM_CTRL_4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"y_grad_gain"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cb_grad_gain"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cr_grad_gain"                    },
};

/*--------------------------------------------
	0x1544 PE1_L_SHP_UM_CTRL_5
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_range_min"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"y_range_max"                     },
};

/*--------------------------------------------
	0x1548 PE1_L_SHP_UM_CTRL_6
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cb_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cb_range_max"                    },
};

/*--------------------------------------------
	0x154c PE1_L_SHP_UM_CTRL_7
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_UM_CTRL_7[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cr_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cr_range_max"                    },
};

/*--------------------------------------------
	0x1550 PE1_L_SHP_BLUR_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_BLUR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"coring_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_min"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_max"                      },
};

/*--------------------------------------------
	0x1560 PE1_L_SHP_SUM_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SHP_SUM_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"dbg_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"sum_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"enh_en_cc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"enh_en_yy"                       },
};

/*--------------------------------------------
	0x1570 PE1_L_TI_CTRL_0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1574 PE1_L_TI_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TI_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"coring_step"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ti_gain"                         },
};

/*--------------------------------------------
	0x1578 PE1_L_TI_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TI_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"debug_coring"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"coring_step"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_gain"                          },
};

/*--------------------------------------------
	0x157c PE1_L_TI_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TI_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"debug_coring"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"coring_step"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_gain"                          },
};

/*--------------------------------------------
	0x1580 PE1_L_TI_CTRL_4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TI_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gain0_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"gain1_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"output_mux"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain0_th0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"gain0_th1"                       },
};

/*--------------------------------------------
	0x1584 PE1_L_TI_CTRL_5
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_TI_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"gain1_div_mode"                  },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"line_variation_diff"             },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,24 ,"dj_v_count_max"                  },
};

/*--------------------------------------------
	0x15b0 PE1_L_VSP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_VSP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"graycolor_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"color_only_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"contrast"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"brightness"                      },
};

/*--------------------------------------------
	0x15c0 PE1_L_XVY_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"icsc_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"degamma_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pcc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"gamma"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"scaler_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"hsv_hsl_selection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"s_adpative_scaler"               },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"r_csc_ofst4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"r_csc_ofst3"                     },
};

/*--------------------------------------------
	0x15e0 PE1_L_XVY_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_XVY_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"r_csc_ofst5"                     },
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
};

/*--------------------------------------------
	0x1634 PE1_L_LRCR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_LRCR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"th_max_hist"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"th_valid_bins"                   },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"hist_bin_bitwidth_mode"          },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"hif_hist_address"                },
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
const DBG_REG_FIELD_T dbg_PE1_L_DCE_HSIT_IA_DATA2[] = {
};

/*--------------------------------------------
	0x16c0 PE1_L_WB_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WB_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"wb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"apl_gain_bypass"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"wb_user_ctrl_bypass"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"max_to_one_bypass"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"use_apl_than_ctemp"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctemp"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ire_csc_offset"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"degamma_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gamma_en"                        },
};

/*--------------------------------------------
	0x16c4 PE1_L_WB_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WB_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"ire_csc_g_coeff"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"ire_csc_b_coeff"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"ire_csc_r_coeff"                 },
};

/*--------------------------------------------
	0x16c8 PE1_L_WB_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WB_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"user_ctrl_g_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctrl_b_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"user_ctrl_r_gain"                },
};

/*--------------------------------------------
	0x16cc PE1_L_WB_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_WB_CTRL_03[] = {
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pxl_rep_ypos"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pxl_rep_area"                    },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dcountour_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"bit_mode_8"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"decontour_gain_r"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"decontour_gain_g"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"decontour_gain_b"                },
};

/*--------------------------------------------
	0x1720 PE1_L_SQM_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_L_SQM_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"outmux_debugmap_"                },
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
	0x3320 PE1_R_WIN_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN_CTRL_00[] = {
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
	0x3324 PE1_R_WIN_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y0"                       },
};

/*--------------------------------------------
	0x3328 PE1_R_WIN_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w0_x1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w0_y1"                       },
};

/*--------------------------------------------
	0x332c PE1_R_WIN_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"win_w1_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"win_w1_y0"                       },
};

/*--------------------------------------------
	0x3330 PE1_R_WIN_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WIN_CTRL_04[] = {
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
	0x335c PE1_R_APL_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_y"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"apl_rgb"                         },
};

/*--------------------------------------------
	0x3360 PE1_R_APL_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_APL_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"apl_b"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"apl_g"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"apl_r"                           },
};

/*--------------------------------------------
	0x3370 PE1_R_TPG_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TPG_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tpg_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pattern_type"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"blend_alpha"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,8  ,"blt_size_x"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"blt_size_y"                      },
};

/*--------------------------------------------
	0x3374 PE1_R_TPG_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TPG_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"gradation_stride"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"gradation_direction"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"gradation_bar_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"washing_num_of_bar_x"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"washing_num_of_bar_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"washing_speed"                   },
};

/*--------------------------------------------
	0x3378 PE1_R_TPG_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TPG_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"patch_en"                        },
};

/*--------------------------------------------
	0x337c PE1_R_TPG_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TPG_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"tpg_indir_addr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"tpg_indir_ai_en"                 },
};

/*--------------------------------------------
	0x3380 PE1_R_TPG_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TPG_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"tpg_indir_data"                  },
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
	0x33c0 PE1_R_HFNR_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_HFNR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"flats_t0_fc0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"flats_t0_fcs"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"flats_t1_fc0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"flats_t1_fc1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"flats_t0_fcp"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"flats_t0_fcd"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"t0_bc0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,14 ,"t1_bc0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"dth_t0_dth0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"h_disable"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dth_t0_dths"                     },
};

/*--------------------------------------------
	0x33c4 PE1_R_HFNR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_HFNR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dth_t0_dthp"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"dth_t1_dth0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"dth_t1_dth1"                     },
};

/*--------------------------------------------
	0x33d0 PE1_R_LSR_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_00[] = {
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
	0x33d4 PE1_R_LSR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"a_gen_of_y"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"a_gen_of_c"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"avg_flt_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"avg_flt_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"max_flt_mode"                    },
};

/*--------------------------------------------
	0x33d8 PE1_R_LSR_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_02[] = {
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
	0x33dc PE1_R_LSR_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"a_mux_for_edge_gaintable"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"a_mux_for_detail_filter"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"a_mux_for_edge_filter"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"a_scaling_flat_filter_"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"a_mux_for_flat_filter"           },
};

/*--------------------------------------------
	0x33e0 PE1_R_LSR_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dbg_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"sum_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"enh_en_cc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"enh_en_yy"                       },
};

/*--------------------------------------------
	0x33e4 PE1_R_LSR_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vmm_param"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"csft_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"th_gain_edge"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"th_gain_flat"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"th_manual_th"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"th_manual_en"                    },
};

/*--------------------------------------------
	0x33e8 PE1_R_LSR_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"edge_filter_white_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"edge_filter_black_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"amean_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"edge_filter_v_tap"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edge_c_filter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"edge_y_filter_en"                },
};

/*--------------------------------------------
	0x33ec PE1_R_LSR_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"flat_filter_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"flat_filter_en"                  },
};

/*--------------------------------------------
	0x33f0 PE1_R_LSR_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl0_y0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl0_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"amod_ctrl0_y1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"amod_ctrl0_x1"                   },
};

/*--------------------------------------------
	0x33f4 PE1_R_LSR_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"amod_ctrl1_x0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"amod_ctrl1_x1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"y_c_mux_control"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,19 ,"chroma_weight"                   },
};

/*--------------------------------------------
	0x3400 PE1_R_DER_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DER_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"der_v_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"der_gain_mapping"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"bif_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"output_mux"                      },
};

/*--------------------------------------------
	0x3404 PE1_R_DER_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DER_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gain_th0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_th1"                        },
};

/*--------------------------------------------
	0x3410 PE1_R_LSR_DTL_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"detail_enhancer_enable"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"debug_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"debug_image"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_w"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain_b"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"filter_coef_normalization"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"freq_selective_filter_type"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"detail_measure_for_sca"          },
};

/*--------------------------------------------
	0x3414 PE1_R_LSR_DTL_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"f2_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"f3_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"f4_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"f5_gain"                         },
};

/*--------------------------------------------
	0x3418 PE1_R_LSR_DTL_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"t5_gain"                         },
};

/*--------------------------------------------
	0x341c PE1_R_LSR_DTL_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"um3x3_type"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"um3x3_gain"                      },
};

/*--------------------------------------------
	0x3420 PE1_R_LSR_DTL_CTRL_04
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3424 PE1_R_LSR_DTL_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"manual_coring_enable"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"coring_post_filtering_type"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"coring_post_filtering_enable"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"local_min_max_mode"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"coring_mmd_type"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"dbg_diff_gain"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"c_mmd_th"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"c_mmd_scale"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"c_mmd_type"                      },
};

/*--------------------------------------------
	0x3428 PE1_R_LSR_DTL_CTRL_06
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x342c PE1_R_LSR_DTL_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"coring_mmd_th_l1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_mmd_th_l2"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_mmd_th_h1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_mmd_th_h2"                },
};

/*--------------------------------------------
	0x3430 PE1_R_LSR_DTL_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"post_filterig_enable"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"post_filtering_y_delta"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"post_filtering_y_th"             },
};

/*--------------------------------------------
	0x3434 PE1_R_LSR_DTL_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"lgain_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"lgain_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"lgain_apl_type"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_low_th0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lgain_low_th1"                   },
};

/*--------------------------------------------
	0x3438 PE1_R_LSR_DTL_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lgain_high_th0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_high_th1"                  },
};

/*--------------------------------------------
	0x343c PE1_R_LSR_DTL_CTRL_0B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_0B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gain_balancing_on_off"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"delta_axis_resolution"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_x2"                           },
};

/*--------------------------------------------
	0x3440 PE1_R_LSR_DTL_CTRL_0C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_0C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ed_y1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_y3"                           },
};

/*--------------------------------------------
	0x3444 PE1_R_LSR_DTL_CTRL_0D
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_CTRL_0D[] = {
};

/*--------------------------------------------
	0x3450 PE1_R_LSR_DTL_EE_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_EE_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"extreme_enhancer_enable"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"um1_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"um2_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"um3_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"um4_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"um1_filter_type"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"um2_filter_type"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"um3_filter_type"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"um4_filter_type"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"ee_gain_b"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"ee_gain_w"                       },
};

/*--------------------------------------------
	0x3454 PE1_R_LSR_DTL_EE_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_EE_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"um1_gain_b"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"um1_gain_w"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"um2_gain_b"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"um2_gain_w"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"um3_gain_b"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"um3_gain_w"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"um4_gain_b"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"um4_gain_w"                      },
};

/*--------------------------------------------
	0x3458 PE1_R_LSR_DTL_EE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_EE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"filter_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lap_gain"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"sobel_gx_gain"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x345c PE1_R_LSR_DTL_EE_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_EE_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"h_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"v_gain"                          },
};

/*--------------------------------------------
	0x3460 PE1_R_LSR_DTL_EE_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_EE_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gain_balancing_on_off"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"delta_axis_resolution"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_x2"                           },
};

/*--------------------------------------------
	0x3464 PE1_R_LSR_DTL_EE_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_DTL_EE_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ed_y1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ed_y2"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ed_y3"                           },
};

/*--------------------------------------------
	0x3470 PE1_R_LSR_GT_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_GT_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gt_detail_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"gt_edge_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"gt_flat_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"gt_detail_manual_gain"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"gt_edge_manual_gain"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"gt_flat_manual_gain"             },
};

/*--------------------------------------------
	0x3474 PE1_R_LSR_GT_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_GT_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"gt_interpolation_type"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"interpol_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"interpol_x1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"interpol_x2"                     },
};

/*--------------------------------------------
	0x3478 PE1_R_LSR_GT_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_GT_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"th1"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"th2"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"th3"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"pcm_th"                          },
};

/*--------------------------------------------
	0x347c PE1_R_LSR_GT_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_GT_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_manual_sqa_measure"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"auto_sqa_measure_type"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"hdm_pcm_selection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"sqm_bit_resolution"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"manual_sqa_value"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hd_measure"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"pc_measure"                      },
};

/*--------------------------------------------
	0x3480 PE1_R_LSR_GT_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_GT_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"source_quality_measure"          },
};

/*--------------------------------------------
	0x3484 PE1_R_LSR_GT_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_GT_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"index"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"edf"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"auto_increment"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gt_enable"                       },
};

/*--------------------------------------------
	0x3488 PE1_R_LSR_GT_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_GT_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"gt_wdata0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"gt_wdata1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"gt_wdata2"                       },
};

/*--------------------------------------------
	0x34a0 PE1_R_LSR_SCA_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"sca_gain_display"                },
};

/*--------------------------------------------
	0x34a4 PE1_R_LSR_SCA_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"sca_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"sca_gain"                        },
};

/*--------------------------------------------
	0x34a8 PE1_R_LSR_SCA_CTRL_02
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x34ac PE1_R_LSR_SCA_CTRL_03
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x34b0 PE1_R_LSR_SCA_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"enable_sca_to_flat_filter"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"gain_of_sca_to_flat_filter"      },
};

/*--------------------------------------------
	0x34b4 PE1_R_LSR_SCA_CTRL_05
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x34b8 PE1_R_LSR_SCA_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_debug_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"show_sqm1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"show_cr_info"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"debug_bar_gain_position"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"measure_display_gain"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"show_tpg"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"show_hdm_pcm_area"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"show_sqm2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,10 ,"sqm2_debug_image"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,15 ,"show_bbd"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"bbd_line_width"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"show_apl"                        },
};

/*--------------------------------------------
	0x34bc PE1_R_LSR_SCA_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"y_grad_gain"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cb_grad_gain"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cr_grad_gain"                    },
};

/*--------------------------------------------
	0x34c0 PE1_R_LSR_SCA_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_range_min"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"y_range_max"                     },
};

/*--------------------------------------------
	0x34c4 PE1_R_LSR_SCA_CTRL_09
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cb_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cb_range_max"                    },
};

/*--------------------------------------------
	0x34c8 PE1_R_LSR_SCA_CTRL_0A
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_CTRL_0A[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cr_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cr_range_max"                    },
};

/*--------------------------------------------
	0x34cc PE1_R_LSR_SCA_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"gain_type"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,2  ,"color_region"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"auto_increment"                  },
};

/*--------------------------------------------
	0x34d0 PE1_R_LSR_SCA_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_SCA_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"x2"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"g1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"g2"                              },
};

/*--------------------------------------------
	0x34e0 PE1_R_LSR_CRG_IA_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CRG_IA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"hif_crg_lsr_address"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hif_crg_lsr_ai"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"hif_crg_lsr_wr"                  },
};

/*--------------------------------------------
	0x34e4 PE1_R_LSR_CRG_IA_DATA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LSR_CRG_IA_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"value"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,10 ,"saturation"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"hue"                             },
};

/*--------------------------------------------
	0x34f0 PE1_R_SHP_EDGE_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edge_enhance_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"edge_enhance_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"lm_mode"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"lti_level"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"edge_operator_selection"         },
};

/*--------------------------------------------
	0x34f4 PE1_R_SHP_EDGE_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"white_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"black_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vertical_gain"                   },
};

/*--------------------------------------------
	0x34f8 PE1_R_SHP_EDGE_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sobel_weight"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"laplacian_weight"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sobel_manual_mode_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"sobel_manual_gain"               },
};

/*--------------------------------------------
	0x34fc PE1_R_SHP_EDGE_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lum_low_th1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lum_low_th2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lum_high_th1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lum_high_th2"                    },
};

/*--------------------------------------------
	0x3500 PE1_R_SHP_EDGE_CTRL_04
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"laplacian_offset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"debug_selection"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"debug_enable"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gx_weight_manual_mode"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gx_weight_manual_gain"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"par_filter_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"par_out_sel"                     },
};

/*--------------------------------------------
	0x3508 PE1_R_SHP_EDGE_CTRL_05
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"coring_enable"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"coring_mmd_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"coring_low_th_resol"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_low_th1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_low_th2"                  },
};

/*--------------------------------------------
	0x350c PE1_R_SHP_EDGE_CTRL_06
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pf_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"pf_debug_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pf_display_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pf_p1_flt_type_concave"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"pf_p1_flt_type_convex"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"pf_p2_flt_type_concave"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pf_p2_flt_type_convex"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pf_p12_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"pf_gain"                         },
};

/*--------------------------------------------
	0x3510 PE1_R_SHP_EDGE_CTRL_07
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pf_p0_th1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"pf_p0_th2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"pf_p1_th1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"pf_p1_th2"                       },
};

/*--------------------------------------------
	0x3514 PE1_R_SHP_EDGE_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_EDGE_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pf_p1_th3"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"pf_p2_th1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"pf_p2_th2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"pf_p2_th3"                       },
};

/*--------------------------------------------
	0x3520 PE1_R_CTI_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_CTI_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"tap_size"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cti_gain"                        },
};

/*--------------------------------------------
	0x3524 PE1_R_CTI_CTRL_01
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3528 PE1_R_CTI_CTRL_02
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
	0x3530 PE1_R_SHP_UM_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"coring_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"coring_diff_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"filter_tap"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"avg_type"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,5  ,"coring_mmd_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_w"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain_b"                          },
};

/*--------------------------------------------
	0x3534 PE1_R_SHP_UM_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"coring_th_low1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th_low2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_th_high1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_th_high2"                 },
};

/*--------------------------------------------
	0x3538 PE1_R_SHP_UM_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"lgain_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"lgain_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"lgain_apl_type"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_low_th0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"lgain_low_th1"                   },
};

/*--------------------------------------------
	0x353c PE1_R_SHP_UM_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"lgain_high_th0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lgain_high_th1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sca_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"sca_gain"                        },
};

/*--------------------------------------------
	0x3540 PE1_R_SHP_UM_CTRL_4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"y_grad_gain"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cb_grad_gain"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cr_grad_gain"                    },
};

/*--------------------------------------------
	0x3544 PE1_R_SHP_UM_CTRL_5
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_range_min"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"y_range_max"                     },
};

/*--------------------------------------------
	0x3548 PE1_R_SHP_UM_CTRL_6
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cb_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cb_range_max"                    },
};

/*--------------------------------------------
	0x354c PE1_R_SHP_UM_CTRL_7
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_UM_CTRL_7[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"cr_range_min"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"cr_range_max"                    },
};

/*--------------------------------------------
	0x3550 PE1_R_SHP_BLUR_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_BLUR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"coring_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"coring_min"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"coring_max"                      },
};

/*--------------------------------------------
	0x3560 PE1_R_SHP_SUM_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SHP_SUM_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"dbg_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"sum_mux"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"enh_en_cc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"enh_en_yy"                       },
};

/*--------------------------------------------
	0x3570 PE1_R_TI_CTRL_0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3574 PE1_R_TI_CTRL_1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TI_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"coring_step"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ti_gain"                         },
};

/*--------------------------------------------
	0x3578 PE1_R_TI_CTRL_2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TI_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"debug_coring"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"coring_step"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_gain"                          },
};

/*--------------------------------------------
	0x357c PE1_R_TI_CTRL_3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TI_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"debug_coring"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"coring_step"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"coring_th"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_gain"                          },
};

/*--------------------------------------------
	0x3580 PE1_R_TI_CTRL_4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TI_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gain0_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"gain1_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"output_mux"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gain0_th0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"gain0_th1"                       },
};

/*--------------------------------------------
	0x3584 PE1_R_TI_CTRL_5
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_TI_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"gain1_div_mode"                  },
};

/*--------------------------------------------
	0x3590 PE1_R_DJ_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"edf_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dj_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"edf_artifact_reduction"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"l_pro_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"smoothness"                      },
};

/*--------------------------------------------
	0x3594 PE1_R_DJ_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"level_threshold"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"protect_delta"                   },
};

/*--------------------------------------------
	0x3598 PE1_R_DJ_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"edf_pixel_diff_min"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"edf_pixel_diff_max"              },
};

/*--------------------------------------------
	0x359c PE1_R_DJ_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_DJ_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"h_cnt_min"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"h_cnt_max"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"v_cnt_min"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,24 ,"v_cnt_max"                       },
};

/*--------------------------------------------
	0x35b0 PE1_R_VSP_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_VSP_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"graycolor_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"color_only_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"center_position"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"contrast"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"brightness"                      },
};

/*--------------------------------------------
	0x35c0 PE1_R_XVY_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"icsc_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"degamma_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pcc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"gamma"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"scaler_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"hsv_hsl_selection"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"s_adpative_scaler"               },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"r_csc_ofst4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"r_csc_ofst3"                     },
};

/*--------------------------------------------
	0x35e0 PE1_R_XVY_CTRL_08
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_XVY_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"r_pcc_coef0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"r_csc_ofst5"                     },
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
};

/*--------------------------------------------
	0x3634 PE1_R_LRCR_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_LRCR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"th_max_hist"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"th_valid_bins"                   },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"hist_bin_bitwidth_mode"          },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"hif_hist_address"                },
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
const DBG_REG_FIELD_T dbg_PE1_R_DCE_HSIT_IA_DATA2[] = {
};

/*--------------------------------------------
	0x36c0 PE1_R_WB_CTRL_00
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WB_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"wb_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"apl_gain_bypass"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"wb_user_ctrl_bypass"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"max_to_one_bypass"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"use_apl_than_ctemp"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctemp"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ire_csc_offset"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"degamma_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gamma_en"                        },
};

/*--------------------------------------------
	0x36c4 PE1_R_WB_CTRL_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WB_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"ire_csc_g_coeff"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"ire_csc_b_coeff"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"ire_csc_r_coeff"                 },
};

/*--------------------------------------------
	0x36c8 PE1_R_WB_CTRL_02
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WB_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"user_ctrl_g_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"user_ctrl_b_gain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"user_ctrl_r_gain"                },
};

/*--------------------------------------------
	0x36cc PE1_R_WB_CTRL_03
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_WB_CTRL_03[] = {
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pxl_rep_ypos"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pxl_rep_area"                    },
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
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dcountour_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"bit_mode_8"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"decontour_gain_r"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"decontour_gain_g"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"decontour_gain_b"                },
};

/*--------------------------------------------
	0x3720 PE1_R_SQM_CTRL_0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_PE1_R_SQM_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"outmux_debugmap_"                },
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

DBG_REG_T gDbgRegPE1[] = {
	{ 0x1300 ,N_FLD(dbg_PE1_L_TOP_CTRL_00)               ,"PE1_L_TOP_CTRL_00"                 ,dbg_PE1_L_TOP_CTRL_00               },
	{ 0x1304 ,N_FLD(dbg_PE1_L_TOP_CTRL_01)               ,"PE1_L_TOP_CTRL_01"                 ,dbg_PE1_L_TOP_CTRL_01               },
	{ 0x1308 ,N_FLD(dbg_PE1_L_TOP_CTRL_02)               ,"PE1_L_TOP_CTRL_02"                 ,dbg_PE1_L_TOP_CTRL_02               },
	{ 0x130c ,N_FLD(dbg_PE1_L_TOP_CTRL_03)               ,"PE1_L_TOP_CTRL_03"                 ,dbg_PE1_L_TOP_CTRL_03               },
	{ 0x1320 ,N_FLD(dbg_PE1_L_WIN_CTRL_00)               ,"PE1_L_WIN_CTRL_00"                 ,dbg_PE1_L_WIN_CTRL_00               },
	{ 0x1324 ,N_FLD(dbg_PE1_L_WIN_CTRL_01)               ,"PE1_L_WIN_CTRL_01"                 ,dbg_PE1_L_WIN_CTRL_01               },
	{ 0x1328 ,N_FLD(dbg_PE1_L_WIN_CTRL_02)               ,"PE1_L_WIN_CTRL_02"                 ,dbg_PE1_L_WIN_CTRL_02               },
	{ 0x132c ,N_FLD(dbg_PE1_L_WIN_CTRL_03)               ,"PE1_L_WIN_CTRL_03"                 ,dbg_PE1_L_WIN_CTRL_03               },
	{ 0x1330 ,N_FLD(dbg_PE1_L_WIN_CTRL_04)               ,"PE1_L_WIN_CTRL_04"                 ,dbg_PE1_L_WIN_CTRL_04               },
	{ 0x1350 ,N_FLD(dbg_PE1_L_APL_CTRL_00)               ,"PE1_L_APL_CTRL_00"                 ,dbg_PE1_L_APL_CTRL_00               },
	{ 0x1354 ,N_FLD(dbg_PE1_L_APL_CTRL_01)               ,"PE1_L_APL_CTRL_01"                 ,dbg_PE1_L_APL_CTRL_01               },
	{ 0x1358 ,N_FLD(dbg_PE1_L_APL_CTRL_02)               ,"PE1_L_APL_CTRL_02"                 ,dbg_PE1_L_APL_CTRL_02               },
	{ 0x135c ,N_FLD(dbg_PE1_L_APL_CTRL_03)               ,"PE1_L_APL_CTRL_03"                 ,dbg_PE1_L_APL_CTRL_03               },
	{ 0x1360 ,N_FLD(dbg_PE1_L_APL_CTRL_04)               ,"PE1_L_APL_CTRL_04"                 ,dbg_PE1_L_APL_CTRL_04               },
	{ 0x1370 ,N_FLD(dbg_PE1_L_TPG_CTRL_00)               ,"PE1_L_TPG_CTRL_00"                 ,dbg_PE1_L_TPG_CTRL_00               },
	{ 0x1374 ,N_FLD(dbg_PE1_L_TPG_CTRL_01)               ,"PE1_L_TPG_CTRL_01"                 ,dbg_PE1_L_TPG_CTRL_01               },
	{ 0x1378 ,N_FLD(dbg_PE1_L_TPG_CTRL_02)               ,"PE1_L_TPG_CTRL_02"                 ,dbg_PE1_L_TPG_CTRL_02               },
	{ 0x137c ,N_FLD(dbg_PE1_L_TPG_IA_CTRL)               ,"PE1_L_TPG_IA_CTRL"                 ,dbg_PE1_L_TPG_IA_CTRL               },
	{ 0x1380 ,N_FLD(dbg_PE1_L_TPG_IA_DATA)               ,"PE1_L_TPG_IA_DATA"                 ,dbg_PE1_L_TPG_IA_DATA               },
	{ 0x13a0 ,N_FLD(dbg_PE1_L_FILM_CTRL_00)              ,"PE1_L_FILM_CTRL_00"                ,dbg_PE1_L_FILM_CTRL_00              },
	{ 0x13a4 ,N_FLD(dbg_PE1_L_FILM_CTRL_01)              ,"PE1_L_FILM_CTRL_01"                ,dbg_PE1_L_FILM_CTRL_01              },
	{ 0x13a8 ,N_FLD(dbg_PE1_L_FILM_CTRL_02)              ,"PE1_L_FILM_CTRL_02"                ,dbg_PE1_L_FILM_CTRL_02              },
	{ 0x13c0 ,N_FLD(dbg_PE1_L_HFNR_CTRL_00)              ,"PE1_L_HFNR_CTRL_00"                ,dbg_PE1_L_HFNR_CTRL_00              },
	{ 0x13c4 ,N_FLD(dbg_PE1_L_HFNR_CTRL_01)              ,"PE1_L_HFNR_CTRL_01"                ,dbg_PE1_L_HFNR_CTRL_01              },
	{ 0x13d0 ,N_FLD(dbg_PE1_L_LSR_CTRL_00)               ,"PE1_L_LSR_CTRL_00"                 ,dbg_PE1_L_LSR_CTRL_00               },
	{ 0x13d4 ,N_FLD(dbg_PE1_L_LSR_CTRL_01)               ,"PE1_L_LSR_CTRL_01"                 ,dbg_PE1_L_LSR_CTRL_01               },
	{ 0x13d8 ,N_FLD(dbg_PE1_L_LSR_CTRL_02)               ,"PE1_L_LSR_CTRL_02"                 ,dbg_PE1_L_LSR_CTRL_02               },
	{ 0x13dc ,N_FLD(dbg_PE1_L_LSR_CTRL_03)               ,"PE1_L_LSR_CTRL_03"                 ,dbg_PE1_L_LSR_CTRL_03               },
	{ 0x13e0 ,N_FLD(dbg_PE1_L_LSR_CTRL_04)               ,"PE1_L_LSR_CTRL_04"                 ,dbg_PE1_L_LSR_CTRL_04               },
	{ 0x13e4 ,N_FLD(dbg_PE1_L_LSR_CTRL_05)               ,"PE1_L_LSR_CTRL_05"                 ,dbg_PE1_L_LSR_CTRL_05               },
	{ 0x13e8 ,N_FLD(dbg_PE1_L_LSR_CTRL_06)               ,"PE1_L_LSR_CTRL_06"                 ,dbg_PE1_L_LSR_CTRL_06               },
	{ 0x13ec ,N_FLD(dbg_PE1_L_LSR_CTRL_07)               ,"PE1_L_LSR_CTRL_07"                 ,dbg_PE1_L_LSR_CTRL_07               },
	{ 0x13f0 ,N_FLD(dbg_PE1_L_LSR_CTRL_08)               ,"PE1_L_LSR_CTRL_08"                 ,dbg_PE1_L_LSR_CTRL_08               },
	{ 0x13f4 ,N_FLD(dbg_PE1_L_LSR_CTRL_09)               ,"PE1_L_LSR_CTRL_09"                 ,dbg_PE1_L_LSR_CTRL_09               },
	{ 0x1400 ,N_FLD(dbg_PE1_L_DER_CTRL_0)                ,"PE1_L_DER_CTRL_0"                  ,dbg_PE1_L_DER_CTRL_0                },
	{ 0x1404 ,N_FLD(dbg_PE1_L_DER_CTRL_1)                ,"PE1_L_DER_CTRL_1"                  ,dbg_PE1_L_DER_CTRL_1                },
	{ 0x1410 ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_00)           ,"PE1_L_LSR_DTL_CTRL_00"             ,dbg_PE1_L_LSR_DTL_CTRL_00           },
	{ 0x1414 ,0                                          ,"PE1_L_LSR_DTL_CTRL_01"             ,NULL                                },
	{ 0x1418 ,0                                          ,"PE1_L_LSR_DTL_CTRL_02"             ,NULL                                },
	{ 0x141c ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_03)           ,"PE1_L_LSR_DTL_CTRL_03"             ,dbg_PE1_L_LSR_DTL_CTRL_03           },
	{ 0x1420 ,0                                          ,"PE1_L_LSR_DTL_CTRL_04"             ,NULL                                },
	{ 0x1424 ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_05)           ,"PE1_L_LSR_DTL_CTRL_05"             ,dbg_PE1_L_LSR_DTL_CTRL_05           },
	{ 0x1428 ,0                                          ,"PE1_L_LSR_DTL_CTRL_06"             ,NULL                                },
	{ 0x142c ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_07)           ,"PE1_L_LSR_DTL_CTRL_07"             ,dbg_PE1_L_LSR_DTL_CTRL_07           },
	{ 0x1430 ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_08)           ,"PE1_L_LSR_DTL_CTRL_08"             ,dbg_PE1_L_LSR_DTL_CTRL_08           },
	{ 0x1434 ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_09)           ,"PE1_L_LSR_DTL_CTRL_09"             ,dbg_PE1_L_LSR_DTL_CTRL_09           },
	{ 0x1438 ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_0A)           ,"PE1_L_LSR_DTL_CTRL_0A"             ,dbg_PE1_L_LSR_DTL_CTRL_0A           },
	{ 0x143c ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_0B)           ,"PE1_L_LSR_DTL_CTRL_0B"             ,dbg_PE1_L_LSR_DTL_CTRL_0B           },
	{ 0x1440 ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_0C)           ,"PE1_L_LSR_DTL_CTRL_0C"             ,dbg_PE1_L_LSR_DTL_CTRL_0C           },
	{ 0x1444 ,N_FLD(dbg_PE1_L_LSR_DTL_CTRL_0D)           ,"PE1_L_LSR_DTL_CTRL_0D"             ,dbg_PE1_L_LSR_DTL_CTRL_0D           },
	{ 0x1450 ,0                                          ,"PE1_L_LSR_DTL_EE_CTRL_00"          ,NULL                                },
	{ 0x1454 ,0                                          ,"PE1_L_LSR_DTL_EE_CTRL_01"          ,NULL                                },
	{ 0x1458 ,N_FLD(dbg_PE1_L_LSR_DTL_EE_CTRL_02)        ,"PE1_L_LSR_DTL_EE_CTRL_02"          ,dbg_PE1_L_LSR_DTL_EE_CTRL_02        },
	{ 0x145c ,N_FLD(dbg_PE1_L_LSR_DTL_EE_CTRL_03)        ,"PE1_L_LSR_DTL_EE_CTRL_03"          ,dbg_PE1_L_LSR_DTL_EE_CTRL_03        },
	{ 0x1460 ,N_FLD(dbg_PE1_L_LSR_DTL_EE_CTRL_04)        ,"PE1_L_LSR_DTL_EE_CTRL_04"          ,dbg_PE1_L_LSR_DTL_EE_CTRL_04        },
	{ 0x1464 ,N_FLD(dbg_PE1_L_LSR_DTL_EE_CTRL_05)        ,"PE1_L_LSR_DTL_EE_CTRL_05"          ,dbg_PE1_L_LSR_DTL_EE_CTRL_05        },
	{ 0x1470 ,N_FLD(dbg_PE1_L_LSR_GT_CTRL_00)            ,"PE1_L_LSR_GT_CTRL_00"              ,dbg_PE1_L_LSR_GT_CTRL_00            },
	{ 0x1474 ,N_FLD(dbg_PE1_L_LSR_GT_CTRL_01)            ,"PE1_L_LSR_GT_CTRL_01"              ,dbg_PE1_L_LSR_GT_CTRL_01            },
	{ 0x1478 ,N_FLD(dbg_PE1_L_LSR_GT_CTRL_02)            ,"PE1_L_LSR_GT_CTRL_02"              ,dbg_PE1_L_LSR_GT_CTRL_02            },
	{ 0x147c ,N_FLD(dbg_PE1_L_LSR_GT_CTRL_03)            ,"PE1_L_LSR_GT_CTRL_03"              ,dbg_PE1_L_LSR_GT_CTRL_03            },
	{ 0x1480 ,N_FLD(dbg_PE1_L_LSR_GT_CTRL_04)            ,"PE1_L_LSR_GT_CTRL_04"              ,dbg_PE1_L_LSR_GT_CTRL_04            },
	{ 0x1484 ,N_FLD(dbg_PE1_L_LSR_GT_IA_CTRL)            ,"PE1_L_LSR_GT_IA_CTRL"              ,dbg_PE1_L_LSR_GT_IA_CTRL            },
	{ 0x1488 ,N_FLD(dbg_PE1_L_LSR_GT_IA_DATA)            ,"PE1_L_LSR_GT_IA_DATA"              ,dbg_PE1_L_LSR_GT_IA_DATA            },
	{ 0x14a0 ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_00)           ,"PE1_L_LSR_SCA_CTRL_00"             ,dbg_PE1_L_LSR_SCA_CTRL_00           },
	{ 0x14a4 ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_01)           ,"PE1_L_LSR_SCA_CTRL_01"             ,dbg_PE1_L_LSR_SCA_CTRL_01           },
	{ 0x14a8 ,0                                          ,"PE1_L_LSR_SCA_CTRL_02"             ,NULL                                },
	{ 0x14ac ,0                                          ,"PE1_L_LSR_SCA_CTRL_03"             ,NULL                                },
	{ 0x14b0 ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_04)           ,"PE1_L_LSR_SCA_CTRL_04"             ,dbg_PE1_L_LSR_SCA_CTRL_04           },
	{ 0x14b4 ,0                                          ,"PE1_L_LSR_SCA_CTRL_05"             ,NULL                                },
	{ 0x14b8 ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_06)           ,"PE1_L_LSR_SCA_CTRL_06"             ,dbg_PE1_L_LSR_SCA_CTRL_06           },
	{ 0x14bc ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_07)           ,"PE1_L_LSR_SCA_CTRL_07"             ,dbg_PE1_L_LSR_SCA_CTRL_07           },
	{ 0x14c0 ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_08)           ,"PE1_L_LSR_SCA_CTRL_08"             ,dbg_PE1_L_LSR_SCA_CTRL_08           },
	{ 0x14c4 ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_09)           ,"PE1_L_LSR_SCA_CTRL_09"             ,dbg_PE1_L_LSR_SCA_CTRL_09           },
	{ 0x14c8 ,N_FLD(dbg_PE1_L_LSR_SCA_CTRL_0A)           ,"PE1_L_LSR_SCA_CTRL_0A"             ,dbg_PE1_L_LSR_SCA_CTRL_0A           },
	{ 0x14cc ,N_FLD(dbg_PE1_L_LSR_SCA_IA_CTRL)           ,"PE1_L_LSR_SCA_IA_CTRL"             ,dbg_PE1_L_LSR_SCA_IA_CTRL           },
	{ 0x14d0 ,N_FLD(dbg_PE1_L_LSR_SCA_IA_DATA)           ,"PE1_L_LSR_SCA_IA_DATA"             ,dbg_PE1_L_LSR_SCA_IA_DATA           },
	{ 0x14e0 ,N_FLD(dbg_PE1_L_LSR_CRG_IA_CTRL)           ,"PE1_L_LSR_CRG_IA_CTRL"             ,dbg_PE1_L_LSR_CRG_IA_CTRL           },
	{ 0x14e4 ,N_FLD(dbg_PE1_L_LSR_CRG_IA_DATA)           ,"PE1_L_LSR_CRG_IA_DATA"             ,dbg_PE1_L_LSR_CRG_IA_DATA           },
	{ 0x14f0 ,N_FLD(dbg_PE1_L_SHP_EDGE_CTRL_00)          ,"PE1_L_SHP_EDGE_CTRL_00"            ,dbg_PE1_L_SHP_EDGE_CTRL_00          },
	{ 0x14f4 ,N_FLD(dbg_PE1_L_SHP_EDGE_CTRL_01)          ,"PE1_L_SHP_EDGE_CTRL_01"            ,dbg_PE1_L_SHP_EDGE_CTRL_01          },
	{ 0x14f8 ,N_FLD(dbg_PE1_L_SHP_EDGE_CTRL_02)          ,"PE1_L_SHP_EDGE_CTRL_02"            ,dbg_PE1_L_SHP_EDGE_CTRL_02          },
	{ 0x14fc ,N_FLD(dbg_PE1_L_SHP_EDGE_CTRL_03)          ,"PE1_L_SHP_EDGE_CTRL_03"            ,dbg_PE1_L_SHP_EDGE_CTRL_03          },
	{ 0x1500 ,N_FLD(dbg_PE1_L_SHP_EDGE_CTRL_04)          ,"PE1_L_SHP_EDGE_CTRL_04"            ,dbg_PE1_L_SHP_EDGE_CTRL_04          },
	{ 0x1508 ,N_FLD(dbg_PE1_L_SHP_EDGE_CTRL_05)          ,"PE1_L_SHP_EDGE_CTRL_05"            ,dbg_PE1_L_SHP_EDGE_CTRL_05          },
	{ 0x150c ,0                                          ,"PE1_L_SHP_EDGE_CTRL_06"            ,NULL                                },
	{ 0x1510 ,0                                          ,"PE1_L_SHP_EDGE_CTRL_07"            ,NULL                                },
	{ 0x1514 ,N_FLD(dbg_PE1_L_SHP_EDGE_CTRL_08)          ,"PE1_L_SHP_EDGE_CTRL_08"            ,dbg_PE1_L_SHP_EDGE_CTRL_08          },
	{ 0x1520 ,N_FLD(dbg_PE1_L_CTI_CTRL_00)               ,"PE1_L_CTI_CTRL_00"                 ,dbg_PE1_L_CTI_CTRL_00               },
	{ 0x1524 ,0                                          ,"PE1_L_CTI_CTRL_01"                 ,NULL                                },
	{ 0x1528 ,N_FLD(dbg_PE1_L_CTI_CTRL_02)               ,"PE1_L_CTI_CTRL_02"                 ,dbg_PE1_L_CTI_CTRL_02               },
	{ 0x1530 ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_0)             ,"PE1_L_SHP_UM_CTRL_0"               ,dbg_PE1_L_SHP_UM_CTRL_0             },
	{ 0x1534 ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_1)             ,"PE1_L_SHP_UM_CTRL_1"               ,dbg_PE1_L_SHP_UM_CTRL_1             },
	{ 0x1538 ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_2)             ,"PE1_L_SHP_UM_CTRL_2"               ,dbg_PE1_L_SHP_UM_CTRL_2             },
	{ 0x153c ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_3)             ,"PE1_L_SHP_UM_CTRL_3"               ,dbg_PE1_L_SHP_UM_CTRL_3             },
	{ 0x1540 ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_4)             ,"PE1_L_SHP_UM_CTRL_4"               ,dbg_PE1_L_SHP_UM_CTRL_4             },
	{ 0x1544 ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_5)             ,"PE1_L_SHP_UM_CTRL_5"               ,dbg_PE1_L_SHP_UM_CTRL_5             },
	{ 0x1548 ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_6)             ,"PE1_L_SHP_UM_CTRL_6"               ,dbg_PE1_L_SHP_UM_CTRL_6             },
	{ 0x154c ,N_FLD(dbg_PE1_L_SHP_UM_CTRL_7)             ,"PE1_L_SHP_UM_CTRL_7"               ,dbg_PE1_L_SHP_UM_CTRL_7             },
	{ 0x1550 ,N_FLD(dbg_PE1_L_SHP_BLUR_CTRL)             ,"PE1_L_SHP_BLUR_CTRL"               ,dbg_PE1_L_SHP_BLUR_CTRL             },
	{ 0x1560 ,N_FLD(dbg_PE1_L_SHP_SUM_CTRL)              ,"PE1_L_SHP_SUM_CTRL"                ,dbg_PE1_L_SHP_SUM_CTRL              },
	{ 0x1570 ,0                                          ,"PE1_L_TI_CTRL_0"                   ,NULL                                },
	{ 0x1574 ,N_FLD(dbg_PE1_L_TI_CTRL_1)                 ,"PE1_L_TI_CTRL_1"                   ,dbg_PE1_L_TI_CTRL_1                 },
	{ 0x1578 ,N_FLD(dbg_PE1_L_TI_CTRL_2)                 ,"PE1_L_TI_CTRL_2"                   ,dbg_PE1_L_TI_CTRL_2                 },
	{ 0x157c ,N_FLD(dbg_PE1_L_TI_CTRL_3)                 ,"PE1_L_TI_CTRL_3"                   ,dbg_PE1_L_TI_CTRL_3                 },
	{ 0x1580 ,N_FLD(dbg_PE1_L_TI_CTRL_4)                 ,"PE1_L_TI_CTRL_4"                   ,dbg_PE1_L_TI_CTRL_4                 },
	{ 0x1584 ,N_FLD(dbg_PE1_L_TI_CTRL_5)                 ,"PE1_L_TI_CTRL_5"                   ,dbg_PE1_L_TI_CTRL_5                 },
	{ 0x1590 ,N_FLD(dbg_PE1_L_DJ_CTRL_00)                ,"PE1_L_DJ_CTRL_00"                  ,dbg_PE1_L_DJ_CTRL_00                },
	{ 0x1594 ,N_FLD(dbg_PE1_L_DJ_CTRL_01)                ,"PE1_L_DJ_CTRL_01"                  ,dbg_PE1_L_DJ_CTRL_01                },
	{ 0x1598 ,N_FLD(dbg_PE1_L_DJ_CTRL_02)                ,"PE1_L_DJ_CTRL_02"                  ,dbg_PE1_L_DJ_CTRL_02                },
	{ 0x159c ,N_FLD(dbg_PE1_L_DJ_CTRL_03)                ,"PE1_L_DJ_CTRL_03"                  ,dbg_PE1_L_DJ_CTRL_03                },
	{ 0x15b0 ,N_FLD(dbg_PE1_L_VSP_CTRL_00)               ,"PE1_L_VSP_CTRL_00"                 ,dbg_PE1_L_VSP_CTRL_00               },
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
	{ 0x16a8 ,N_FLD(dbg_PE1_L_DCE_HSIT_IA_DATA2)         ,"PE1_L_DCE_HSIT_IA_DATA2"           ,dbg_PE1_L_DCE_HSIT_IA_DATA2         },
	{ 0x16c0 ,N_FLD(dbg_PE1_L_WB_CTRL_00)                ,"PE1_L_WB_CTRL_00"                  ,dbg_PE1_L_WB_CTRL_00                },
	{ 0x16c4 ,N_FLD(dbg_PE1_L_WB_CTRL_01)                ,"PE1_L_WB_CTRL_01"                  ,dbg_PE1_L_WB_CTRL_01                },
	{ 0x16c8 ,N_FLD(dbg_PE1_L_WB_CTRL_02)                ,"PE1_L_WB_CTRL_02"                  ,dbg_PE1_L_WB_CTRL_02                },
	{ 0x16cc ,N_FLD(dbg_PE1_L_WB_CTRL_03)                ,"PE1_L_WB_CTRL_03"                  ,dbg_PE1_L_WB_CTRL_03                },
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
	{ 0x3300 ,N_FLD(dbg_PE1_R_TOP_CTRL_00)               ,"PE1_R_TOP_CTRL_00"                 ,dbg_PE1_R_TOP_CTRL_00               },
	{ 0x3304 ,N_FLD(dbg_PE1_R_TOP_CTRL_01)               ,"PE1_R_TOP_CTRL_01"                 ,dbg_PE1_R_TOP_CTRL_01               },
	{ 0x3308 ,N_FLD(dbg_PE1_R_TOP_CTRL_02)               ,"PE1_R_TOP_CTRL_02"                 ,dbg_PE1_R_TOP_CTRL_02               },
	{ 0x330c ,N_FLD(dbg_PE1_R_TOP_CTRL_03)               ,"PE1_R_TOP_CTRL_03"                 ,dbg_PE1_R_TOP_CTRL_03               },
	{ 0x3320 ,N_FLD(dbg_PE1_R_WIN_CTRL_00)               ,"PE1_R_WIN_CTRL_00"                 ,dbg_PE1_R_WIN_CTRL_00               },
	{ 0x3324 ,N_FLD(dbg_PE1_R_WIN_CTRL_01)               ,"PE1_R_WIN_CTRL_01"                 ,dbg_PE1_R_WIN_CTRL_01               },
	{ 0x3328 ,N_FLD(dbg_PE1_R_WIN_CTRL_02)               ,"PE1_R_WIN_CTRL_02"                 ,dbg_PE1_R_WIN_CTRL_02               },
	{ 0x332c ,N_FLD(dbg_PE1_R_WIN_CTRL_03)               ,"PE1_R_WIN_CTRL_03"                 ,dbg_PE1_R_WIN_CTRL_03               },
	{ 0x3330 ,N_FLD(dbg_PE1_R_WIN_CTRL_04)               ,"PE1_R_WIN_CTRL_04"                 ,dbg_PE1_R_WIN_CTRL_04               },
	{ 0x3350 ,N_FLD(dbg_PE1_R_APL_CTRL_00)               ,"PE1_R_APL_CTRL_00"                 ,dbg_PE1_R_APL_CTRL_00               },
	{ 0x3354 ,N_FLD(dbg_PE1_R_APL_CTRL_01)               ,"PE1_R_APL_CTRL_01"                 ,dbg_PE1_R_APL_CTRL_01               },
	{ 0x3358 ,N_FLD(dbg_PE1_R_APL_CTRL_02)               ,"PE1_R_APL_CTRL_02"                 ,dbg_PE1_R_APL_CTRL_02               },
	{ 0x335c ,N_FLD(dbg_PE1_R_APL_CTRL_03)               ,"PE1_R_APL_CTRL_03"                 ,dbg_PE1_R_APL_CTRL_03               },
	{ 0x3360 ,N_FLD(dbg_PE1_R_APL_CTRL_04)               ,"PE1_R_APL_CTRL_04"                 ,dbg_PE1_R_APL_CTRL_04               },
	{ 0x3370 ,N_FLD(dbg_PE1_R_TPG_CTRL_00)               ,"PE1_R_TPG_CTRL_00"                 ,dbg_PE1_R_TPG_CTRL_00               },
	{ 0x3374 ,N_FLD(dbg_PE1_R_TPG_CTRL_01)               ,"PE1_R_TPG_CTRL_01"                 ,dbg_PE1_R_TPG_CTRL_01               },
	{ 0x3378 ,N_FLD(dbg_PE1_R_TPG_CTRL_02)               ,"PE1_R_TPG_CTRL_02"                 ,dbg_PE1_R_TPG_CTRL_02               },
	{ 0x337c ,N_FLD(dbg_PE1_R_TPG_IA_CTRL)               ,"PE1_R_TPG_IA_CTRL"                 ,dbg_PE1_R_TPG_IA_CTRL               },
	{ 0x3380 ,N_FLD(dbg_PE1_R_TPG_IA_DATA)               ,"PE1_R_TPG_IA_DATA"                 ,dbg_PE1_R_TPG_IA_DATA               },
	{ 0x33a0 ,N_FLD(dbg_PE1_R_FILM_CTRL_00)              ,"PE1_R_FILM_CTRL_00"                ,dbg_PE1_R_FILM_CTRL_00              },
	{ 0x33a4 ,N_FLD(dbg_PE1_R_FILM_CTRL_01)              ,"PE1_R_FILM_CTRL_01"                ,dbg_PE1_R_FILM_CTRL_01              },
	{ 0x33a8 ,N_FLD(dbg_PE1_R_FILM_CTRL_02)              ,"PE1_R_FILM_CTRL_02"                ,dbg_PE1_R_FILM_CTRL_02              },
	{ 0x33c0 ,N_FLD(dbg_PE1_R_HFNR_CTRL_00)              ,"PE1_R_HFNR_CTRL_00"                ,dbg_PE1_R_HFNR_CTRL_00              },
	{ 0x33c4 ,N_FLD(dbg_PE1_R_HFNR_CTRL_01)              ,"PE1_R_HFNR_CTRL_01"                ,dbg_PE1_R_HFNR_CTRL_01              },
	{ 0x33d0 ,N_FLD(dbg_PE1_R_LSR_CTRL_00)               ,"PE1_R_LSR_CTRL_00"                 ,dbg_PE1_R_LSR_CTRL_00               },
	{ 0x33d4 ,N_FLD(dbg_PE1_R_LSR_CTRL_01)               ,"PE1_R_LSR_CTRL_01"                 ,dbg_PE1_R_LSR_CTRL_01               },
	{ 0x33d8 ,N_FLD(dbg_PE1_R_LSR_CTRL_02)               ,"PE1_R_LSR_CTRL_02"                 ,dbg_PE1_R_LSR_CTRL_02               },
	{ 0x33dc ,N_FLD(dbg_PE1_R_LSR_CTRL_03)               ,"PE1_R_LSR_CTRL_03"                 ,dbg_PE1_R_LSR_CTRL_03               },
	{ 0x33e0 ,N_FLD(dbg_PE1_R_LSR_CTRL_04)               ,"PE1_R_LSR_CTRL_04"                 ,dbg_PE1_R_LSR_CTRL_04               },
	{ 0x33e4 ,N_FLD(dbg_PE1_R_LSR_CTRL_05)               ,"PE1_R_LSR_CTRL_05"                 ,dbg_PE1_R_LSR_CTRL_05               },
	{ 0x33e8 ,N_FLD(dbg_PE1_R_LSR_CTRL_06)               ,"PE1_R_LSR_CTRL_06"                 ,dbg_PE1_R_LSR_CTRL_06               },
	{ 0x33ec ,N_FLD(dbg_PE1_R_LSR_CTRL_07)               ,"PE1_R_LSR_CTRL_07"                 ,dbg_PE1_R_LSR_CTRL_07               },
	{ 0x33f0 ,N_FLD(dbg_PE1_R_LSR_CTRL_08)               ,"PE1_R_LSR_CTRL_08"                 ,dbg_PE1_R_LSR_CTRL_08               },
	{ 0x33f4 ,N_FLD(dbg_PE1_R_LSR_CTRL_09)               ,"PE1_R_LSR_CTRL_09"                 ,dbg_PE1_R_LSR_CTRL_09               },
	{ 0x3400 ,N_FLD(dbg_PE1_R_DER_CTRL_0)                ,"PE1_R_DER_CTRL_0"                  ,dbg_PE1_R_DER_CTRL_0                },
	{ 0x3404 ,N_FLD(dbg_PE1_R_DER_CTRL_1)                ,"PE1_R_DER_CTRL_1"                  ,dbg_PE1_R_DER_CTRL_1                },
	{ 0x3410 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_00)           ,"PE1_R_LSR_DTL_CTRL_00"             ,dbg_PE1_R_LSR_DTL_CTRL_00           },
	{ 0x3414 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_01)           ,"PE1_R_LSR_DTL_CTRL_01"             ,dbg_PE1_R_LSR_DTL_CTRL_01           },
	{ 0x3418 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_02)           ,"PE1_R_LSR_DTL_CTRL_02"             ,dbg_PE1_R_LSR_DTL_CTRL_02           },
	{ 0x341c ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_03)           ,"PE1_R_LSR_DTL_CTRL_03"             ,dbg_PE1_R_LSR_DTL_CTRL_03           },
	{ 0x3420 ,0                                          ,"PE1_R_LSR_DTL_CTRL_04"             ,NULL                                },
	{ 0x3424 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_05)           ,"PE1_R_LSR_DTL_CTRL_05"             ,dbg_PE1_R_LSR_DTL_CTRL_05           },
	{ 0x3428 ,0                                          ,"PE1_R_LSR_DTL_CTRL_06"             ,NULL                                },
	{ 0x342c ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_07)           ,"PE1_R_LSR_DTL_CTRL_07"             ,dbg_PE1_R_LSR_DTL_CTRL_07           },
	{ 0x3430 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_08)           ,"PE1_R_LSR_DTL_CTRL_08"             ,dbg_PE1_R_LSR_DTL_CTRL_08           },
	{ 0x3434 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_09)           ,"PE1_R_LSR_DTL_CTRL_09"             ,dbg_PE1_R_LSR_DTL_CTRL_09           },
	{ 0x3438 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_0A)           ,"PE1_R_LSR_DTL_CTRL_0A"             ,dbg_PE1_R_LSR_DTL_CTRL_0A           },
	{ 0x343c ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_0B)           ,"PE1_R_LSR_DTL_CTRL_0B"             ,dbg_PE1_R_LSR_DTL_CTRL_0B           },
	{ 0x3440 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_0C)           ,"PE1_R_LSR_DTL_CTRL_0C"             ,dbg_PE1_R_LSR_DTL_CTRL_0C           },
	{ 0x3444 ,N_FLD(dbg_PE1_R_LSR_DTL_CTRL_0D)           ,"PE1_R_LSR_DTL_CTRL_0D"             ,dbg_PE1_R_LSR_DTL_CTRL_0D           },
	{ 0x3450 ,N_FLD(dbg_PE1_R_LSR_DTL_EE_CTRL_00)        ,"PE1_R_LSR_DTL_EE_CTRL_00"          ,dbg_PE1_R_LSR_DTL_EE_CTRL_00        },
	{ 0x3454 ,N_FLD(dbg_PE1_R_LSR_DTL_EE_CTRL_01)        ,"PE1_R_LSR_DTL_EE_CTRL_01"          ,dbg_PE1_R_LSR_DTL_EE_CTRL_01        },
	{ 0x3458 ,N_FLD(dbg_PE1_R_LSR_DTL_EE_CTRL_02)        ,"PE1_R_LSR_DTL_EE_CTRL_02"          ,dbg_PE1_R_LSR_DTL_EE_CTRL_02        },
	{ 0x345c ,N_FLD(dbg_PE1_R_LSR_DTL_EE_CTRL_03)        ,"PE1_R_LSR_DTL_EE_CTRL_03"          ,dbg_PE1_R_LSR_DTL_EE_CTRL_03        },
	{ 0x3460 ,N_FLD(dbg_PE1_R_LSR_DTL_EE_CTRL_04)        ,"PE1_R_LSR_DTL_EE_CTRL_04"          ,dbg_PE1_R_LSR_DTL_EE_CTRL_04        },
	{ 0x3464 ,N_FLD(dbg_PE1_R_LSR_DTL_EE_CTRL_05)        ,"PE1_R_LSR_DTL_EE_CTRL_05"          ,dbg_PE1_R_LSR_DTL_EE_CTRL_05        },
	{ 0x3470 ,N_FLD(dbg_PE1_R_LSR_GT_CTRL_00)            ,"PE1_R_LSR_GT_CTRL_00"              ,dbg_PE1_R_LSR_GT_CTRL_00            },
	{ 0x3474 ,N_FLD(dbg_PE1_R_LSR_GT_CTRL_01)            ,"PE1_R_LSR_GT_CTRL_01"              ,dbg_PE1_R_LSR_GT_CTRL_01            },
	{ 0x3478 ,N_FLD(dbg_PE1_R_LSR_GT_CTRL_02)            ,"PE1_R_LSR_GT_CTRL_02"              ,dbg_PE1_R_LSR_GT_CTRL_02            },
	{ 0x347c ,N_FLD(dbg_PE1_R_LSR_GT_CTRL_03)            ,"PE1_R_LSR_GT_CTRL_03"              ,dbg_PE1_R_LSR_GT_CTRL_03            },
	{ 0x3480 ,N_FLD(dbg_PE1_R_LSR_GT_CTRL_04)            ,"PE1_R_LSR_GT_CTRL_04"              ,dbg_PE1_R_LSR_GT_CTRL_04            },
	{ 0x3484 ,N_FLD(dbg_PE1_R_LSR_GT_IA_CTRL)            ,"PE1_R_LSR_GT_IA_CTRL"              ,dbg_PE1_R_LSR_GT_IA_CTRL            },
	{ 0x3488 ,N_FLD(dbg_PE1_R_LSR_GT_IA_DATA)            ,"PE1_R_LSR_GT_IA_DATA"              ,dbg_PE1_R_LSR_GT_IA_DATA            },
	{ 0x34a0 ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_00)           ,"PE1_R_LSR_SCA_CTRL_00"             ,dbg_PE1_R_LSR_SCA_CTRL_00           },
	{ 0x34a4 ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_01)           ,"PE1_R_LSR_SCA_CTRL_01"             ,dbg_PE1_R_LSR_SCA_CTRL_01           },
	{ 0x34a8 ,0                                          ,"PE1_R_LSR_SCA_CTRL_02"             ,NULL                                },
	{ 0x34ac ,0                                          ,"PE1_R_LSR_SCA_CTRL_03"             ,NULL                                },
	{ 0x34b0 ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_04)           ,"PE1_R_LSR_SCA_CTRL_04"             ,dbg_PE1_R_LSR_SCA_CTRL_04           },
	{ 0x34b4 ,0                                          ,"PE1_R_LSR_SCA_CTRL_05"             ,NULL                                },
	{ 0x34b8 ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_06)           ,"PE1_R_LSR_SCA_CTRL_06"             ,dbg_PE1_R_LSR_SCA_CTRL_06           },
	{ 0x34bc ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_07)           ,"PE1_R_LSR_SCA_CTRL_07"             ,dbg_PE1_R_LSR_SCA_CTRL_07           },
	{ 0x34c0 ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_08)           ,"PE1_R_LSR_SCA_CTRL_08"             ,dbg_PE1_R_LSR_SCA_CTRL_08           },
	{ 0x34c4 ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_09)           ,"PE1_R_LSR_SCA_CTRL_09"             ,dbg_PE1_R_LSR_SCA_CTRL_09           },
	{ 0x34c8 ,N_FLD(dbg_PE1_R_LSR_SCA_CTRL_0A)           ,"PE1_R_LSR_SCA_CTRL_0A"             ,dbg_PE1_R_LSR_SCA_CTRL_0A           },
	{ 0x34cc ,N_FLD(dbg_PE1_R_LSR_SCA_IA_CTRL)           ,"PE1_R_LSR_SCA_IA_CTRL"             ,dbg_PE1_R_LSR_SCA_IA_CTRL           },
	{ 0x34d0 ,N_FLD(dbg_PE1_R_LSR_SCA_IA_DATA)           ,"PE1_R_LSR_SCA_IA_DATA"             ,dbg_PE1_R_LSR_SCA_IA_DATA           },
	{ 0x34e0 ,N_FLD(dbg_PE1_R_LSR_CRG_IA_CTRL)           ,"PE1_R_LSR_CRG_IA_CTRL"             ,dbg_PE1_R_LSR_CRG_IA_CTRL           },
	{ 0x34e4 ,N_FLD(dbg_PE1_R_LSR_CRG_IA_DATA)           ,"PE1_R_LSR_CRG_IA_DATA"             ,dbg_PE1_R_LSR_CRG_IA_DATA           },
	{ 0x34f0 ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_00)          ,"PE1_R_SHP_EDGE_CTRL_00"            ,dbg_PE1_R_SHP_EDGE_CTRL_00          },
	{ 0x34f4 ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_01)          ,"PE1_R_SHP_EDGE_CTRL_01"            ,dbg_PE1_R_SHP_EDGE_CTRL_01          },
	{ 0x34f8 ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_02)          ,"PE1_R_SHP_EDGE_CTRL_02"            ,dbg_PE1_R_SHP_EDGE_CTRL_02          },
	{ 0x34fc ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_03)          ,"PE1_R_SHP_EDGE_CTRL_03"            ,dbg_PE1_R_SHP_EDGE_CTRL_03          },
	{ 0x3500 ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_04)          ,"PE1_R_SHP_EDGE_CTRL_04"            ,dbg_PE1_R_SHP_EDGE_CTRL_04          },
	{ 0x3508 ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_05)          ,"PE1_R_SHP_EDGE_CTRL_05"            ,dbg_PE1_R_SHP_EDGE_CTRL_05          },
	{ 0x350c ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_06)          ,"PE1_R_SHP_EDGE_CTRL_06"            ,dbg_PE1_R_SHP_EDGE_CTRL_06          },
	{ 0x3510 ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_07)          ,"PE1_R_SHP_EDGE_CTRL_07"            ,dbg_PE1_R_SHP_EDGE_CTRL_07          },
	{ 0x3514 ,N_FLD(dbg_PE1_R_SHP_EDGE_CTRL_08)          ,"PE1_R_SHP_EDGE_CTRL_08"            ,dbg_PE1_R_SHP_EDGE_CTRL_08          },
	{ 0x3520 ,N_FLD(dbg_PE1_R_CTI_CTRL_00)               ,"PE1_R_CTI_CTRL_00"                 ,dbg_PE1_R_CTI_CTRL_00               },
	{ 0x3524 ,0                                          ,"PE1_R_CTI_CTRL_01"                 ,NULL                                },
	{ 0x3528 ,N_FLD(dbg_PE1_R_CTI_CTRL_02)               ,"PE1_R_CTI_CTRL_02"                 ,dbg_PE1_R_CTI_CTRL_02               },
	{ 0x3530 ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_0)             ,"PE1_R_SHP_UM_CTRL_0"               ,dbg_PE1_R_SHP_UM_CTRL_0             },
	{ 0x3534 ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_1)             ,"PE1_R_SHP_UM_CTRL_1"               ,dbg_PE1_R_SHP_UM_CTRL_1             },
	{ 0x3538 ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_2)             ,"PE1_R_SHP_UM_CTRL_2"               ,dbg_PE1_R_SHP_UM_CTRL_2             },
	{ 0x353c ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_3)             ,"PE1_R_SHP_UM_CTRL_3"               ,dbg_PE1_R_SHP_UM_CTRL_3             },
	{ 0x3540 ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_4)             ,"PE1_R_SHP_UM_CTRL_4"               ,dbg_PE1_R_SHP_UM_CTRL_4             },
	{ 0x3544 ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_5)             ,"PE1_R_SHP_UM_CTRL_5"               ,dbg_PE1_R_SHP_UM_CTRL_5             },
	{ 0x3548 ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_6)             ,"PE1_R_SHP_UM_CTRL_6"               ,dbg_PE1_R_SHP_UM_CTRL_6             },
	{ 0x354c ,N_FLD(dbg_PE1_R_SHP_UM_CTRL_7)             ,"PE1_R_SHP_UM_CTRL_7"               ,dbg_PE1_R_SHP_UM_CTRL_7             },
	{ 0x3550 ,N_FLD(dbg_PE1_R_SHP_BLUR_CTRL)             ,"PE1_R_SHP_BLUR_CTRL"               ,dbg_PE1_R_SHP_BLUR_CTRL             },
	{ 0x3560 ,N_FLD(dbg_PE1_R_SHP_SUM_CTRL)              ,"PE1_R_SHP_SUM_CTRL"                ,dbg_PE1_R_SHP_SUM_CTRL              },
	{ 0x3570 ,0                                          ,"PE1_R_TI_CTRL_0"                   ,NULL                                },
	{ 0x3574 ,N_FLD(dbg_PE1_R_TI_CTRL_1)                 ,"PE1_R_TI_CTRL_1"                   ,dbg_PE1_R_TI_CTRL_1                 },
	{ 0x3578 ,N_FLD(dbg_PE1_R_TI_CTRL_2)                 ,"PE1_R_TI_CTRL_2"                   ,dbg_PE1_R_TI_CTRL_2                 },
	{ 0x357c ,N_FLD(dbg_PE1_R_TI_CTRL_3)                 ,"PE1_R_TI_CTRL_3"                   ,dbg_PE1_R_TI_CTRL_3                 },
	{ 0x3580 ,N_FLD(dbg_PE1_R_TI_CTRL_4)                 ,"PE1_R_TI_CTRL_4"                   ,dbg_PE1_R_TI_CTRL_4                 },
	{ 0x3584 ,N_FLD(dbg_PE1_R_TI_CTRL_5)                 ,"PE1_R_TI_CTRL_5"                   ,dbg_PE1_R_TI_CTRL_5                 },
	{ 0x3590 ,N_FLD(dbg_PE1_R_DJ_CTRL_00)                ,"PE1_R_DJ_CTRL_00"                  ,dbg_PE1_R_DJ_CTRL_00                },
	{ 0x3594 ,N_FLD(dbg_PE1_R_DJ_CTRL_01)                ,"PE1_R_DJ_CTRL_01"                  ,dbg_PE1_R_DJ_CTRL_01                },
	{ 0x3598 ,N_FLD(dbg_PE1_R_DJ_CTRL_02)                ,"PE1_R_DJ_CTRL_02"                  ,dbg_PE1_R_DJ_CTRL_02                },
	{ 0x359c ,N_FLD(dbg_PE1_R_DJ_CTRL_03)                ,"PE1_R_DJ_CTRL_03"                  ,dbg_PE1_R_DJ_CTRL_03                },
	{ 0x35b0 ,N_FLD(dbg_PE1_R_VSP_CTRL_00)               ,"PE1_R_VSP_CTRL_00"                 ,dbg_PE1_R_VSP_CTRL_00               },
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
	{ 0x36a8 ,N_FLD(dbg_PE1_R_DCE_HSIT_IA_DATA2)         ,"PE1_R_DCE_HSIT_IA_DATA2"           ,dbg_PE1_R_DCE_HSIT_IA_DATA2         },
	{ 0x36c0 ,N_FLD(dbg_PE1_R_WB_CTRL_00)                ,"PE1_R_WB_CTRL_00"                  ,dbg_PE1_R_WB_CTRL_00                },
	{ 0x36c4 ,N_FLD(dbg_PE1_R_WB_CTRL_01)                ,"PE1_R_WB_CTRL_01"                  ,dbg_PE1_R_WB_CTRL_01                },
	{ 0x36c8 ,N_FLD(dbg_PE1_R_WB_CTRL_02)                ,"PE1_R_WB_CTRL_02"                  ,dbg_PE1_R_WB_CTRL_02                },
	{ 0x36cc ,N_FLD(dbg_PE1_R_WB_CTRL_03)                ,"PE1_R_WB_CTRL_03"                  ,dbg_PE1_R_WB_CTRL_03                },
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
	{ 0 , } // end marker
};

#endif
