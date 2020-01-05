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

#ifndef _DBG_PE0_h
#define _DBG_PE0_h

/*----------------------------------------
	0x0400 P0L_PE0_LOAD
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_LOAD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load_time"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"load_enable"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"load_type"                               },
};

/*----------------------------------------
	0x0404 P0L_PE0_INTR
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_INTR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"intr_enable"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"intr_src"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"intr_line_pos"                           },
};

/*----------------------------------------
	0x0408 P0L_PE0_STATUS0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_STATUS0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"tnr_frame_id"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"ipc_frame_id"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"tnrw_y_frame_id"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"tnrw_c_frame_id"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"dnr_frame_id"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"pic_init_frame_id"                       },
};

/*----------------------------------------
	0x040c P0L_PE0_STATUS1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_STATUS1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"line_cnt"                                },
};

/*----------------------------------------
	0x0410 P0L_PE0_OPMODE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_OPMODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tnr_c_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"tnr_y_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"ipc_c_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"ipc_y_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tnr_c_444_as_420"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"tnr_y2_en"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"force_420"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"mif_last_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ipc_force_44x"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"detour_enable"                           },
};

/*----------------------------------------
	0x0414 P0L_PE0_SRC_SIZE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_SRC_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"hsize"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"cs_type"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"vsize"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"scan_type"                               },
};

/*----------------------------------------
	0x0418 P0L_PE0_FIELD
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_FIELD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"field_id"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"field_mode"                              },
};

/*----------------------------------------
	0x041c P0L_PE0_PARAM_BY_DDR
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_PE0_PARAM_BY_DDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"stride"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vsize"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"endian"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"update_by_ddr"                           },
};

/*----------------------------------------
	0x0420 P0L_WIN_CTRL_0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_WIN_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y0"                                      },
};

/*----------------------------------------
	0x0424 P0L_WIN_CTRL_1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_WIN_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x0428 P0L_WIN_CTRL_2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_WIN_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"ac_bnr_feature_cal_mode"                 },
};

/*----------------------------------------
	0x042c P0L_WIN_CTRL_3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_WIN_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x0440 P0L_TNR_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tnr_enable"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"wa_enable"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"nt_lvl_hsub"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"frame_skip_enable_for_3d"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"calc_motion_sample_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"hist_motion_sample_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"hist_motion_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"calc_motion_flt_enable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"calc_motion_flt_type"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"calc_motion_max_yc"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"hist_motion_max_yc"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"nt_lvl_adjust_gm_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"nt_lvl_adjust_lpct_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"nt_lvl_adjust_xpeak_enable"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"nt_lvl_adjust_avg_ts_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"nt_lvl_adjust_lpct_sel"                  },
};

/*----------------------------------------
	0x0444 P0L_TNR_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_th_lo"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,12 ,"y_th_hi"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"svar_mux_ctrl"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_hist_n_pct"                       },
};

/*----------------------------------------
	0x0448 P0L_TNR_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"wa_flat_svar_th"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"alpha_lut_ind7"                          },
};

/*----------------------------------------
	0x044c P0L_TNR_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"wa_y0"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"wa_y1"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"wa_x0"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"wa_x1"                                   },
};

/*----------------------------------------
	0x0450 P0L_TNR_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_gm_y0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_gm_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_gm_y1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_gm_x1"                       },
};

/*----------------------------------------
	0x0454 P0L_TNR_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_min"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_max"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hist_svar_th"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adj_alpha_nt_lvl_th0"                    },
};

/*----------------------------------------
	0x0458 P0L_TNR_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"peak_0_th"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_iir_alpha"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"adj_alpha_k0"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adj_alpha_k1"                            },
};

/*----------------------------------------
	0x045c P0L_TNR_CTRL_07
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"alpha_lut_ind0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"alpha_lut_ind1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"alpha_lut_ind2"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"alpha_lut_ind3"                          },
};

/*----------------------------------------
	0x0460 P0L_TNR_CTRL_08
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"alpha_lut_ind4"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"alpha_lut_ind5"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"alpha_lut_ind6"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adj_alpha_nt_lvl_th1"                    },
};

/*----------------------------------------
	0x0464 P0L_TNR_CTRL_09
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"scene_change_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"scene_change_max_flt_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"scene_change_measure_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"scene_change_prev_hist_calc_en"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"scene_change_enforce"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"scene_change_max_flt_tap"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"scene_change_scale"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"scene_change_th"                         },
};

/*----------------------------------------
	0x0468 P0L_TNR_CTRL_10
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_10[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"dbg_show_tnr_param"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"dbg_status_sum_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dbg_force_wa"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"dbg_force_calc_motion"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"dbg_force_lut_alpha"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"dbg_force_adj_alpha"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dbg_force_final_alpha"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"ignore_active_window"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"dbg_tnrw_port_ctrl"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dbg_wa"                                  },
};

/*----------------------------------------
	0x046c P0L_TNR_CTRL_11
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_11[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dbg_calc_motion"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"dbg_alpha"                               },
};

/*----------------------------------------
	0x0470 P0L_TNR_CTRL_12
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_12[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_gm_y2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_gm_x2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_gm_y3"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_gm_x3"                       },
};

/*----------------------------------------
	0x0474 P0L_TNR_CTRL_13
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_13[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"force_nt_lvl"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"force_nt_lvl_val"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"adjust_nt_lvl"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adjust_nt_lvl_val"                       },
};

/*----------------------------------------
	0x0478 P0L_TNR_CTRL_14
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_14[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"noise_measure_win_en"                    },
};

/*----------------------------------------
	0x047c P0L_TNR_CTRL_15
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_15[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x0480 P0L_TNR_CTRL_16
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_16[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"show_dbg_bar_ctrl0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"show_dbg_bar_ctrl1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"show_dbg_bar_ctrl2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"show_dbg_bar_ctrl3"                      },
};

/*----------------------------------------
	0x0484 P0L_TNR_CTRL_17
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_17[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"show_dbg_bar_ctrl4"                      },
};

/*----------------------------------------
	0x0488 P0L_TNR_CTRL_18
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_18[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"crgn_gain_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"luma_gain_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"saturation_gain_enable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"input_for_luma"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"input_for_crgn_satr"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y_gain"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_gain"                                  },
};

/*----------------------------------------
	0x048c P0L_TNR_CTRL_19
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_19[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p0_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p1_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p2_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p3_x"                          },
};

/*----------------------------------------
	0x0490 P0L_TNR_CTRL_20
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_20[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p4_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p5_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p6_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p7_x"                          },
};

/*----------------------------------------
	0x0494 P0L_TNR_CTRL_21
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_21[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p0_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p1_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p2_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p3_y"                          },
};

/*----------------------------------------
	0x0498 P0L_TNR_CTRL_22
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_22[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p4_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p5_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p6_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p7_y"                          },
};

/*----------------------------------------
	0x049c P0L_TNR_CTRL_23
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_23[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p0_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p1_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p2_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p3_x"                    },
};

/*----------------------------------------
	0x04a0 P0L_TNR_CTRL_24
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_24[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p4_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p5_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p6_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p7_x"                    },
};

/*----------------------------------------
	0x04a4 P0L_TNR_CTRL_25
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_25[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p0_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p1_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p2_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p3_y"                    },
};

/*----------------------------------------
	0x04a8 P0L_TNR_CTRL_26
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_26[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p4_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p5_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p6_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p7_y"                    },
};

/*----------------------------------------
	0x04ac P0L_TNR_CTRL_27
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_27[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"crgn_gain_rgn0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"crgn_gain_rgn1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"crgn_gain_rgn2"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"crgn_gain_rgn3"                          },
};

/*----------------------------------------
	0x04b0 P0L_TNR_CTRL_28
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_28[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_st_y0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_st_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_st_y1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_st_x1"                       },
};

/*----------------------------------------
	0x04b4 P0L_TNR_CTRL_29
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_29[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"wa_y2"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"wa_y3"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"wa_x2"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"wa_x3"                                   },
};

/*----------------------------------------
	0x04b8 P0L_TNR_CTRL_30
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_30[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_st_y2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_st_x2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_st_y3"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_st_x3"                       },
};

/*----------------------------------------
	0x04bc P0L_TNR_CTRL_31
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_31[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"spatial_pre_flt_en_c"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"spatial_pre_flt_en_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"spatial_pre_flt_th_c"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"spatial_pre_flt_th_y"                    },
};

/*----------------------------------------
	0x04c0 P0L_TNR_STATUS_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_STATUS_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x_avg_t"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"x_peak_t2"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"scene_change"                            },
};

/*----------------------------------------
	0x04c4 P0L_TNR_STATUS_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_STATUS_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x_avg_s"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,8  ,"valid_cnt_motion_histogram"              },
};

/*----------------------------------------
	0x04c8 P0L_TNR_STATUS_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_STATUS_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gm"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lp"                                      },
};

/*----------------------------------------
	0x04cc P0L_TNR_STATUS_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_STATUS_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,0  ,"sum_of_temp_pel_diff"                    },
};

/*----------------------------------------
	0x04d0 P0L_TNR_MAIN_LUT_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_MAIN_LUT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"main_lut_indir_addr"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"main_lut_ai_enable"                      },
};

/*----------------------------------------
	0x04d4 P0L_TNR_MAIN_LUT_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_MAIN_LUT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"main_lut_indir_data0"                    },
};

/*----------------------------------------
	0x04d8 P0L_TNR_MAIN_LUT_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_MAIN_LUT_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"main_lut_indir_data1"                    },
};

/*----------------------------------------
	0x04e0 P0L_TNR_CTRL_32
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_32[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_lpct_y0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_lpct_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_lpct_y1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_lpct_x1"                     },
};

/*----------------------------------------
	0x04e4 P0L_TNR_CTRL_33
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_33[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_lpct_y2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_lpct_x2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_lpct_y3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_lpct_x3"                     },
};

/*----------------------------------------
	0x04e8 P0L_TNR_CTRL_34
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_34[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_xpeak_y0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_xpeak_x0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_xpeak_y1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_xpeak_x1"                    },
};

/*----------------------------------------
	0x04ec P0L_TNR_CTRL_35
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CTRL_35[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_xpeak_y2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_xpeak_x2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_xpeak_y3"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_xpeak_x3"                    },
};

/*----------------------------------------
	0x04f0 P0L_TNR_CRG_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CRG_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"crgn_ctrl_indir_addr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"crgn_ctrl_ai_enable"                     },
};

/*----------------------------------------
	0x04f4 P0L_TNR_CRG_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TNR_CRG_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crgn_ctrl_indir_data"                    },
};

/*----------------------------------------
	0x0500 P0L_IPC_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"luma_mode"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"luma_edi"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"chroma_mode"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"chroma_edi"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"chroma_adaptive_va_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"st_filter_mode"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"ipc_fake_v_repeat_va_ta"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"film_mode_apply_c"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"film_mode_apply_y"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"film_mode_enable"                        },
};

/*----------------------------------------
	0x0504 P0L_IPC_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_fuzzy_margin0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_fuzzy_margin1"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cr_tnr_debug_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"cr_black_mask_origline_when_tnr_debug"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"cr_5f_mode"                              },
};

/*----------------------------------------
	0x0508 P0L_IPC_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fuzzy_ctrl_point_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fuzzy_ctrl_point_x4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fuzzy_ctrl_point_x1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fuzzy_ctrl_point_y1"                     },
};

/*----------------------------------------
	0x050c P0L_IPC_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fuzzy_ctrl_point_x2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fuzzy_ctrl_point_y2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fuzzy_ctrl_point_x3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fuzzy_ctrl_point_y3"                     },
};

/*----------------------------------------
	0x0510 P0L_IPC_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"et_offset_s7"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"motion_x_tearing_gain"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"tearing_gain"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"motion_gain"                             },
};

/*----------------------------------------
	0x0514 P0L_IPC_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_ipc_c_motion_alpha"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_t_grad_weight"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_v_grad_weight"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cr_h_grad_weight"                        },
};

/*----------------------------------------
	0x0518 P0L_IPC_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cr_normalize_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cr_flat_only"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cr_tearing_normalize_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_normalize_base"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_normalize_center"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cr_motion_coring"                        },
};

/*----------------------------------------
	0x051c P0L_IPC_CTRL_07
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cr_v_en"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cr_45_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cr_15_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cr_postmedian_en"                        },
};

/*----------------------------------------
	0x0520 P0L_IPC_CTRL_08
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"fmd_caption_range_top"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"fmd_caption_range_bot"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"caption_flow_detected"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hmc_when_cap_not_detected"               },
};

/*----------------------------------------
	0x0524 P0L_IPC_CTRL_09
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"fmd_vedge_th"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"fmd_vedge_en"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"fmd_a_th"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"use_3field_err_t"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"two_field_delay_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd_margin_top"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fmd_margin_bottom"                       },
};

/*----------------------------------------
	0x0528 P0L_IPC_CTRL_10
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_10[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"film_inter_with"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"hw_film_enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tearing_detect_strength"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cross_check"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"usediffpelcount"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"pn_diff_th"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"scalemeasureforhd"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"loading_time_ctrl"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"fmd_sw_bad_edit_en"                      },
};

/*----------------------------------------
	0x052c P0L_IPC_CTRL_11
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_11[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"repeat_det_line_cnt_th"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"repeat_det_diff_pel_cnt_th"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"repeat_det_noise_th"                     },
};

/*----------------------------------------
	0x0530 P0L_IPC_CTRL_12
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_12[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fmd_32_enable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fmd_22_enable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"fmd_badediten"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"fmd_hw_bad_edit_mul_th"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd_hw_bad_edit_th_min"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"pcn_diff_th"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"fmd_arbitrary_6_4only"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fmd_stillconditition1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"fmd_stillconditition2"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"fmd_arbitrary_still"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"fmd_arbitrary_3_2only"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"fmd_still_cntth"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"fmd_still_cntth_en"                      },
};

/*----------------------------------------
	0x0534 P0L_IPC_CTRL_13
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_13[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fmd32_stillth_pn"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd32_stillthpcn"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd32_pn_maxvalue_minth0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fmd32_pn_maxvalue_minth1"                },
};

/*----------------------------------------
	0x0538 P0L_IPC_CTRL_14
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_14[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"fmd32_min_field_num"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd32_pn_minvalue_maxth"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"fmd32_pn_maxminratio0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"fmd32_pn_maxminratio1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"fmd_32_pcn_small_weight"                 },
};

/*----------------------------------------
	0x053c P0L_IPC_CTRL_15
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_15[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fmd22_stillth_pn"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd22_stillth_pcn"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bad_edit_sm_min_th"                      },
};

/*----------------------------------------
	0x0540 P0L_IPC_CTRL_16
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_16[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"fmd22_minfieldnum0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"fmd22_minfieldnum1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd22_minvaluemaxth1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd22_maxvalueminth1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"fmd22_maxminratio0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"fmd22_maxminratio1"                      },
};

/*----------------------------------------
	0x0544 P0L_IPC_CTRL_17
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_17[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fmd22_maxvalueminth0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd22_minvaluemaxth0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd32_minvaluemaxth0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fmd32_maxvalueminth0"                    },
};

/*----------------------------------------
	0x0548 P0L_IPC_CTRL_18
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_18[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_ud_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_lr_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_h_grad_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cr_v_grad_gain"                          },
};

/*----------------------------------------
	0x054c P0L_IPC_CTRL_19
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_19[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"center_vld_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"diff_vld_gain"                           },
};

/*----------------------------------------
	0x0550 P0L_IPC_STATUS_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_STATUS_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"pc_cnt"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"nc_cnt"                                  },
};

/*----------------------------------------
	0x0554 P0L_IPC_STATUS_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_STATUS_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"pn_cnt"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"same_cnt"                                },
};

/*----------------------------------------
	0x0558 P0L_IPC_STATUS_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_STATUS_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"fmd32_combwith"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"fmd32_detected"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,4  ,"fmd32_lockingcnt"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"fmd22_combwith"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"fmd22_detected"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd22_lockingcnt"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"fmd_comb_predict"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"bad_edit_detected_hw"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"fmd22_still_detected"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"fmd32_still_detected"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"repeat_detected"                         },
};

/*----------------------------------------
	0x055c P0L_IPC_STATUS_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_STATUS_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"fmd_badeditth_hw"                        },
};

/*----------------------------------------
	0x0560 CLC_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cl_filter_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"clc_detection_enable"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"motion_window"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"cl_pattern_dist"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cl_var_protect_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"cl_var_protect_v_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"cl_var_protect_h_dist"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cl_ab_ratio"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"cl_y_hdistance"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"cl_c_hdistance"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cl_y_protect_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"cl_motion_a_filter"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"cl_motion_b_filter"                      },
};

/*----------------------------------------
	0x0564 CLC_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cl_motion_a_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cl_motion_b_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cl_y_protect_th0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cl_y_protect_th1"                        },
};

/*----------------------------------------
	0x0568 CLC_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"cl_y_bound_th"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"cl_c_bound_th"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"cl_c_bound_type"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"cl_y_bound_width_chroma"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"cl_y_bound_ignore_cc"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"cl_y_bound_ignore_p2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cl_y_bound_ignore_p4"                    },
};

/*----------------------------------------
	0x056c CLC_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cl_sat_min"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cl_var_h_gain"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cl_var_v_gain"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cl_var_protect_th"                       },
};

/*----------------------------------------
	0x0570 CLC_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"cl_frame_min"                            },
};

/*----------------------------------------
	0x0574 CLC_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"clc_c_filter_when_cl_detected"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"clc_y_filter_when_cc_detected"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"clc_cc_line_mem_ctrl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"clc_c_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"clc_dbg_show_mask"                       },
};

/*----------------------------------------
	0x0578 CLC_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cc_c_filter_gain"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cc_y_filter_when_cc_detected"            },
};

/*----------------------------------------
	0x057c CLC_STAT_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CLC_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"cl_detection_count"                      },
};

/*----------------------------------------
	0x0580 P0L_VFLT_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_VFLT_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vfilterenable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"vfilterlocalenable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vfilter_strength"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"cb_filter_y"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vfilter_a_th"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vfilter_in_field_var"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"vfilter_use_mc_mask"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"vfilter_expand"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"vfilter_center"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"vfilter_ul4"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"dbgshow_level"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"dbgshow_enable"                          },
};

/*----------------------------------------
	0x0588 P0L_MNR_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_MNR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"mnr_enable"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"edge_gain_mapping_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"sel_sd_hd"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"debug_mode"                              },
};

/*----------------------------------------
	0x058c P0L_MNR_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_MNR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"hcoef_00"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"hcoef_01"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"hcoef_02"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"hcoef_03"                                },
};

/*----------------------------------------
	0x0590 P0L_MNR_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_MNR_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"hcoef_04"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"hcoef_05"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"hcoef_06"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"hcoef_07"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"hcoef_08"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"hcoef_09"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"hcoef_10"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"hcoef_11"                                },
};

/*----------------------------------------
	0x0594 P0L_MNR_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_MNR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"hcoef_12"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"hcoef_13"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"hcoef_14"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"hcoef_15"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"hcoef_16"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"x1_position"                             },
};

/*----------------------------------------
	0x0598 P0L_MNR_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_MNR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x2_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"x3_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"x4_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"y1_position"                             },
};

/*----------------------------------------
	0x059c P0L_MNR_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_MNR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"y2_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"y3_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y4_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"filter_threshold"                        },
};

/*----------------------------------------
	0x05a0 P0L_MNR_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_MNR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"vcoef0"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"vcoef1"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"vcoef2"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"vcoef3"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"vcoef4"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"vcoef5"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"vcoef6"                                  },
};

/*----------------------------------------
	0x05a8 P0L_VFILTER_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_VFILTER_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cr_vfilter_global_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cr_vfilter_force_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,2  ,"cr_global_frame_num_th"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,8  ,"cr_vfilter_global_th"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"tearing_count"                           },
};

/*----------------------------------------
	0x05ac P0L_BNR_DC_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_DC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dc_bnr_enable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"ac_blockiness_adaptive_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"motion_gain_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"sd_hd_sel"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"output_mux"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"motion_min"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"motion_max"                              },
};

/*----------------------------------------
	0x05b0 P0L_BNR_DC_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_DC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"blur_enable"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"ac_blockiness_multifly_x_n"              },
};

/*----------------------------------------
	0x05b4 P0L_BNR_DC_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_DC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dc_bnr_gain_ctrl_y2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"dc_bnr_gain_ctrl_x2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"dc_bnr_gain_ctrl_y3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dc_bnr_gain_ctrl_x3"                     },
};

/*----------------------------------------
	0x05b8 P0L_BNR_DC_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_DC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dc_bnr_gain_ctrl_y0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"dc_bnr_gain_ctrl_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"dc_bnr_gain_ctrl_y1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dc_bnr_gain_ctrl_x1"                     },
};

/*----------------------------------------
	0x05bc P0L_BNR_AC_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_AC_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ac_bnr_protect_motion_max"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ac_bnr_protect_motion_min"               },
};

/*----------------------------------------
	0x05c0 P0L_BNR_AC_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_AC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bnr_h_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"bnr_v_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"motion_protect_enable"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"source_type"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"status_read_type"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"status_read_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"hbmax_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"vbmax_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"strength_resolution"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"fiter_type"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"output_mux"                              },
};

/*----------------------------------------
	0x05c4 P0L_BNR_AC_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_AC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"strength_h_x0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"strength_h_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"strength_h_max"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"detect_min_th"                           },
};

/*----------------------------------------
	0x05c8 P0L_BNR_AC_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_AC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"strength_v_x0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"strength_v_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"strength_v_max"                          },
};

/*----------------------------------------
	0x05cc P0L_BNR_AC_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_AC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"h_offset_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"manual_offset_h_value"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"v_offset_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"manual_offset_v_value"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"use_of_hysterisis"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"t_filter_weight"                         },
};

/*----------------------------------------
	0x05d0 P0L_BNR_AC_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_AC_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_delta_th0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"max_delta_th1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"h_blockness_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"h_weight_max"                            },
};

/*----------------------------------------
	0x05d4 P0L_BNR_AC_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_AC_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"use_of_hysterisis"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"block_boundary_processing_type"          },
};

/*----------------------------------------
	0x05d8 P0L_DNR_MAX_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_DNR_MAX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_snr"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"enable_mnr"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"enable_der"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"enable_dc_bnr"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"enable_ac_bnr"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"debug_enable"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"debug_mode"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"debug_snr_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"debug_mnr_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"debug_der_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"debug_dc_bnr_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"debug_ac_bnr_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"win_control_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"border_enable"                           },
};

/*----------------------------------------
	0x05dc P0L_DNR_DBAR_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_DNR_DBAR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"debug_bar_en"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"show_debug_bar_for_bnr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"gain"                                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"sd_hd_sel"                               },
};

/*----------------------------------------
	0x05e0 P0L_BNR_STAT_0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BNR_STAT_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ac_bnr_h_status"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ac_bnr_v_status"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"dc_bnr_th"                               },
};

/*----------------------------------------
	0x05e4 P0L_DER_CTRL_0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_DER_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"der_en"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"gain2weight_mapping"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"bif_en"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"out_mux"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"bif_th"                                  },
};

/*----------------------------------------
	0x05e8 P0L_DER_CTRL_1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_DER_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gain_th0"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_th1"                                },
};

/*----------------------------------------
	0x05f0 P0L_IPC_CTRL_20
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_20[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cr_lock_dir_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cr_center_ratio"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cr_lr_diff_ratio"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cr_hmc_lock_filt_sizeh"                  },
};

/*----------------------------------------
	0x05f4 P0L_IPC_CTRL_21
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_21[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_lock_point_add"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_lock_point_penalty"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_lock_point_valid"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"cr_robustness"                           },
};

/*----------------------------------------
	0x05f8 P0L_IPC_CTRL_22
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x05fc P0L_IPC_CTRL_23
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_23[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"global_tbm_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"flim_panelty_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"es_offset_mode"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"err_mode"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"global_tbm_th"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hmc_2d_gain"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"errs_limit"                              },
};

/*----------------------------------------
	0x0600 P0L_IPC_CTRL_24
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_24[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"errs_gain"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"confidance_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"pe0_2d_offset"                           },
};

/*----------------------------------------
	0x0604 P0L_IPC_CTRL_25
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_25[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cubic_coef0"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cubic_coef1"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cubic_coef2"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cubic_coef3"                             },
};

/*----------------------------------------
	0x0608 P0L_IPC_CTRL_26
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_26[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"va_cubic"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"boundary_window"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"force_va"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"half_pel_va"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"dir_med_tap"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"diff_med_tap"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"va_blending_ctrl1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"wide_angle_protection_1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"va_blending_ctrl2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"errs_chroma_blend_gain"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"strong_global_th"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"narrow_angle_week"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"narrow_angle_protection"                 },
};

/*----------------------------------------
	0x060c P0L_IPC_CTRL_27
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_IPC_CTRL_27[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"dbg_show_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"dbg_show_black_mask"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dbg_pprv_to_curr"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"dbg_prv3_to_prev"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"dbg_curr_to_pprv"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"st_flt_ctrl_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"st_flt_ctrl_x1"                          },
};

/*----------------------------------------
	0x0640 P0L_TPD_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_TPD_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tpd_en"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"win_mode"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"quick_out"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"tpd_th_s_vl"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"tpd_th_s_vh"                             },
};

/*----------------------------------------
	0x0644 TPD_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"win_tpd_hen"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"win_tpd_ven"                             },
};

/*----------------------------------------
	0x0648 TPD_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x064c TPD_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"tpd_th_vl"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"tpd_th_vh"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vh_valid_th"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vh_max_th"                               },
};

/*----------------------------------------
	0x0650 TPD_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"tpd_th_s"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"sv_valid_th"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vl_valid_th"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vl_max_th"                               },
};

/*----------------------------------------
	0x0654 TPD_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"mid_level"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"tpd_th_sv_vl"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"tpd_th_sv_vh"                            },
};

/*----------------------------------------
	0x0658 TPD_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"mux_3"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"mux_2"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"mux_1"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"show_scale"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"bbd_show"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"show_bar_1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"show_bar_2"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"show_bar_3"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"show_bar_4"                              },
};

/*----------------------------------------
	0x065c TPD_CTRL_07
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"mux_4"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"hys_mode"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"tpd_th_s_sv"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,24 ,"tpd_th_sv"                               },
};

/*----------------------------------------
	0x0660 TPD_STAT_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tpd_value"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"tpd_by_s"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"tpd_by_vl"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"tpd_by_vh"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tpd_by_vl_max"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"tpd_by_vh_max"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"tpd_by_s_vl"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"tpd_by_s_vh"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"s_status"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vl_status"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vh_status"                               },
};

/*----------------------------------------
	0x0664 TPD_STAT_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TPD_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tpd_by_sv"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"tpd_by_sv_vl"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"tpd_by_sv_vh"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"tpd_by_s_sv"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"hys_tpd_value"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"sv_status"                               },
};

/*----------------------------------------
	0x0670 P0L_BBD_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BBD_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bbd_en"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,1  ,"hys_mode"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"op_mode"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cnt_th"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"diff_th"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"bbd_mux"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"apl_mux"                                 },
};

/*----------------------------------------
	0x0674 P0L_BBD_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BBD_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                                      },
};

/*----------------------------------------
	0x0678 P0L_BBD_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BBD_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x067c P0L_BBD_STAT_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BBD_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                                      },
};

/*----------------------------------------
	0x0680 P0L_BBD_STAT_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_BBD_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x0684 P0L_APL_STAT_00
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x0690 P0L_CTI_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0L_CTI_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti_enable"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cti_repeat_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cti_clipping_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cti_gain"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"cb_filter_c"                             },
};

/*----------------------------------------
	0x06a0 PE0_3DFD_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"aw_offset_x"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"aw_offset_y"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cb_th1"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cb_th2"                                  },
};

/*----------------------------------------
	0x06a4 PE0_3DFD_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cc_th1"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cc_th2"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ll_th1"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ll_th2"                                  },
};

/*----------------------------------------
	0x06a8 PE0_3DFD_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pt_th"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"sstb_th"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"debug_mode"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"div_mode"                                },
};

/*----------------------------------------
	0x06ac PE0_3DFD_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"small_delta_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"small_delta_en"                          },
};

/*----------------------------------------
	0x06b0 PE0_3DFD_STAT_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"cb_count"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"cc_count"                                },
};

/*----------------------------------------
	0x06b4 PE0_3DFD_STAT_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"ll_count"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"pe0_3d_format"                           },
};

/*----------------------------------------
	0x06b8 PE0_3DFD_STAT_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,0  ,"delta_ss_h"                              },
};

/*----------------------------------------
	0x06bc PE0_3DFD_STAT_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,1  ,"delta_ss_v"                              },
};

/*----------------------------------------
	0x06c0 PE0_3DFD_STAT_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,2  ,"delta_tb_v"                              },
};

/*----------------------------------------
	0x06c4 PE0_3DFD_STAT_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,3  ,"delta_tb_h"                              },
};

/*----------------------------------------
	0x06c8 PE0_3DFD_STAT_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,4  ,"ss_ratio"                                },
};

/*----------------------------------------
	0x06cc PE0_3DFD_STAT_07
----------------------------------------*/
const DBG_REG_FIELD_T dbg_PE0_3DFD_STAT_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,4  ,"tb_ratio"                                },
};

/*----------------------------------------
	0x2400 P0R_PE0_LOAD
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_LOAD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load_time"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"load_enable"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"load_type"                               },
};

/*----------------------------------------
	0x2404 P0R_PE0_INTR
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_INTR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"intr_enable"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"intr_src"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"intr_line_pos"                           },
};

/*----------------------------------------
	0x2408 P0R_PE0_STATUS0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_STATUS0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"tnr_frame_id"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"ipc_frame_id"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"tnrw_y_frame_id"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"tnrw_c_frame_id"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"dnr_frame_id"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"pic_init_frame_id"                       },
};

/*----------------------------------------
	0x240c P0R_PE0_STATUS1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_STATUS1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"line_cnt"                                },
};

/*----------------------------------------
	0x2410 P0R_PE0_OPMODE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_OPMODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tnr_c_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"tnr_y_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"ipc_c_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"ipc_y_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tnr_c_444_as_420"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"tnr_y2_en"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"force_420"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"mif_last_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ipc_force_44x"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"detour_enable"                           },
};

/*----------------------------------------
	0x2414 P0R_PE0_SRC_SIZE
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_SRC_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"hsize"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"cs_type"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"vsize"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"scan_type"                               },
};

/*----------------------------------------
	0x2418 P0R_PE0_FIELD
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_FIELD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"field_id"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"field_mode"                              },
};

/*----------------------------------------
	0x241c P0R_PE0_PARAM_BY_DDR
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_PE0_PARAM_BY_DDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"stride"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vsize"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"endian"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"update_by_ddr"                           },
};

/*----------------------------------------
	0x2420 P0R_WIN_CTRL_0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_WIN_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y0"                                      },
};

/*----------------------------------------
	0x2424 P0R_WIN_CTRL_1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_WIN_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x2428 P0R_WIN_CTRL_2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_WIN_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"ac_bnr_feature_cal_mode"                 },
};

/*----------------------------------------
	0x242c P0R_WIN_CTRL_3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_WIN_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x2440 P0R_TNR_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tnr_enable"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"wa_enable"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"nt_lvl_hsub"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"frame_skip_enable_for_3d"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"calc_motion_sample_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"hist_motion_sample_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"hist_motion_scale"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"calc_motion_flt_enable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"calc_motion_flt_type"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"calc_motion_max_yc"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"hist_motion_max_yc"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"nt_lvl_adjust_gm_enable"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"nt_lvl_adjust_lpct_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"nt_lvl_adjust_xpeak_enable"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"nt_lvl_adjust_avg_ts_enable"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"nt_lvl_adjust_lpct_sel"                  },
};

/*----------------------------------------
	0x2444 P0R_TNR_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"y_th_lo"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,12 ,"y_th_hi"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"svar_mux_ctrl"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_hist_n_pct"                       },
};

/*----------------------------------------
	0x2448 P0R_TNR_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"wa_flat_svar_th"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"alpha_lut_ind7"                          },
};

/*----------------------------------------
	0x244c P0R_TNR_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"wa_y0"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"wa_y1"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"wa_x0"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"wa_x1"                                   },
};

/*----------------------------------------
	0x2450 P0R_TNR_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_gm_y0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_gm_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_gm_y1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_gm_x1"                       },
};

/*----------------------------------------
	0x2454 P0R_TNR_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_min"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_max"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hist_svar_th"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adj_alpha_nt_lvl_th0"                    },
};

/*----------------------------------------
	0x2458 P0R_TNR_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"peak_0_th"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_iir_alpha"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"adj_alpha_k0"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adj_alpha_k1"                            },
};

/*----------------------------------------
	0x245c P0R_TNR_CTRL_07
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"alpha_lut_ind0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"alpha_lut_ind1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"alpha_lut_ind2"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"alpha_lut_ind3"                          },
};

/*----------------------------------------
	0x2460 P0R_TNR_CTRL_08
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"alpha_lut_ind4"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"alpha_lut_ind5"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"alpha_lut_ind6"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adj_alpha_nt_lvl_th1"                    },
};

/*----------------------------------------
	0x2464 P0R_TNR_CTRL_09
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"scene_change_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"scene_change_max_flt_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"scene_change_measure_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"scene_change_prev_hist_calc_en"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"scene_change_enforce"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"scene_change_max_flt_tap"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"scene_change_scale"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"scene_change_th"                         },
};

/*----------------------------------------
	0x2468 P0R_TNR_CTRL_10
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_10[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"dbg_show_tnr_param"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"dbg_status_sum_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dbg_force_wa"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"dbg_force_calc_motion"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"dbg_force_lut_alpha"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"dbg_force_adj_alpha"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dbg_force_final_alpha"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"ignore_active_window"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"dbg_tnrw_port_ctrl"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dbg_wa"                                  },
};

/*----------------------------------------
	0x246c P0R_TNR_CTRL_11
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_11[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dbg_calc_motion"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"dbg_alpha"                               },
};

/*----------------------------------------
	0x2470 P0R_TNR_CTRL_12
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_12[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_gm_y2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_gm_x2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_gm_y3"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_gm_x3"                       },
};

/*----------------------------------------
	0x2474 P0R_TNR_CTRL_13
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_13[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"force_nt_lvl"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"force_nt_lvl_val"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"adjust_nt_lvl"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"adjust_nt_lvl_val"                       },
};

/*----------------------------------------
	0x2478 P0R_TNR_CTRL_14
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_14[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"noise_measure_win_en"                    },
};

/*----------------------------------------
	0x247c P0R_TNR_CTRL_15
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_15[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x2480 P0R_TNR_CTRL_16
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_16[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"show_dbg_bar_ctrl0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"show_dbg_bar_ctrl1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"show_dbg_bar_ctrl2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"show_dbg_bar_ctrl3"                      },
};

/*----------------------------------------
	0x2484 P0R_TNR_CTRL_17
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_17[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"show_dbg_bar_ctrl4"                      },
};

/*----------------------------------------
	0x2488 P0R_TNR_CTRL_18
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_18[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"crgn_gain_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"luma_gain_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"saturation_gain_enable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"input_for_luma"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"input_for_crgn_satr"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y_gain"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_gain"                                  },
};

/*----------------------------------------
	0x248c P0R_TNR_CTRL_19
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_19[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p0_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p1_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p2_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p3_x"                          },
};

/*----------------------------------------
	0x2490 P0R_TNR_CTRL_20
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_20[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p4_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p5_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p6_x"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p7_x"                          },
};

/*----------------------------------------
	0x2494 P0R_TNR_CTRL_21
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_21[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p0_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p1_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p2_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p3_y"                          },
};

/*----------------------------------------
	0x2498 P0R_TNR_CTRL_22
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_22[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"luma_gain_p4_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"luma_gain_p5_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"luma_gain_p6_y"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"luma_gain_p7_y"                          },
};

/*----------------------------------------
	0x249c P0R_TNR_CTRL_23
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_23[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p0_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p1_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p2_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p3_x"                    },
};

/*----------------------------------------
	0x24a0 P0R_TNR_CTRL_24
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_24[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p4_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p5_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p6_x"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p7_x"                    },
};

/*----------------------------------------
	0x24a4 P0R_TNR_CTRL_25
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_25[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p0_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p1_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p2_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p3_y"                    },
};

/*----------------------------------------
	0x24a8 P0R_TNR_CTRL_26
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_26[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"saturation_gain_p4_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation_gain_p5_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"saturation_gain_p6_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"saturation_gain_p7_y"                    },
};

/*----------------------------------------
	0x24ac P0R_TNR_CTRL_27
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_27[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"crgn_gain_rgn0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"crgn_gain_rgn1"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"crgn_gain_rgn2"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"crgn_gain_rgn3"                          },
};

/*----------------------------------------
	0x24b0 P0R_TNR_CTRL_28
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_28[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_st_y0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_st_x0"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_st_y1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_st_x1"                       },
};

/*----------------------------------------
	0x24b4 P0R_TNR_CTRL_29
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_29[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"wa_y2"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"wa_y3"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"wa_x2"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"wa_x3"                                   },
};

/*----------------------------------------
	0x24b8 P0R_TNR_CTRL_30
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_30[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_st_y2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"nt_lvl_gain_st_x2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_st_y3"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"nt_lvl_gain_st_x3"                       },
};

/*----------------------------------------
	0x24bc P0R_TNR_CTRL_31
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_31[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"spatial_pre_flt_en_c"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"spatial_pre_flt_en_y"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"spatial_pre_flt_th_c"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"spatial_pre_flt_th_y"                    },
};

/*----------------------------------------
	0x24c0 P0R_TNR_STATUS_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_STATUS_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x_avg_t"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"x_peak_t2"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"scene_change"                            },
};

/*----------------------------------------
	0x24c4 P0R_TNR_STATUS_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_STATUS_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x_avg_s"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,8  ,"valid_cnt_motion_histogram"              },
};

/*----------------------------------------
	0x24c8 P0R_TNR_STATUS_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_STATUS_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"gm"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"lp"                                      },
};

/*----------------------------------------
	0x24cc P0R_TNR_STATUS_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_STATUS_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,0  ,"sum_of_temp_pel_diff"                    },
};

/*----------------------------------------
	0x24d0 P0R_TNR_MAIN_LUT_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_MAIN_LUT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"main_lut_indir_addr"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"main_lut_ai_enable"                      },
};

/*----------------------------------------
	0x24d4 P0R_TNR_MAIN_LUT_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_MAIN_LUT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"main_lut_indir_data0"                    },
};

/*----------------------------------------
	0x24d8 P0R_TNR_MAIN_LUT_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_MAIN_LUT_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"main_lut_indir_data1"                    },
};

/*----------------------------------------
	0x24e0 P0R_TNR_CTRL_32
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_32[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_lpct_y0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_lpct_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_lpct_y1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_lpct_x1"                     },
};

/*----------------------------------------
	0x24e4 P0R_TNR_CTRL_33
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_33[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_lpct_y2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_lpct_x2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_lpct_y3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_lpct_x3"                     },
};

/*----------------------------------------
	0x24e8 P0R_TNR_CTRL_34
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_34[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_xpeak_y0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_xpeak_x0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_xpeak_y1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_xpeak_x1"                    },
};

/*----------------------------------------
	0x24ec P0R_TNR_CTRL_35
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CTRL_35[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"nt_lvl_gain_xpeak_y2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"nt_lvl_gain_xpeak_x2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"nt_lvl_gain_xpeak_y3"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,24 ,"nt_lvl_gain_xpeak_x3"                    },
};

/*----------------------------------------
	0x24f0 P0R_TNR_CRG_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CRG_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"crgn_ctrl_indir_addr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"crgn_ctrl_ai_enable"                     },
};

/*----------------------------------------
	0x24f4 P0R_TNR_CRG_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TNR_CRG_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crgn_ctrl_indir_data"                    },
};

/*----------------------------------------
	0x2500 P0R_IPC_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"luma_mode"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"luma_edi"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"chroma_mode"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"chroma_edi"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"chroma_adaptive_va_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"st_filter_mode"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"ipc_fake_v_repeat_va_ta"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"film_mode_apply_c"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"film_mode_apply_y"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"film_mode_enable"                        },
};

/*----------------------------------------
	0x2504 P0R_IPC_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_fuzzy_margin0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_fuzzy_margin1"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cr_tnr_debug_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"cr_black_mask_origline_when_tnr_debug"   },
};

/*----------------------------------------
	0x2508 P0R_IPC_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fuzzy_ctrl_point_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fuzzy_ctrl_point_x4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fuzzy_ctrl_point_x1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fuzzy_ctrl_point_y1"                     },
};

/*----------------------------------------
	0x250c P0R_IPC_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fuzzy_ctrl_point_x2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fuzzy_ctrl_point_y2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fuzzy_ctrl_point_x3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fuzzy_ctrl_point_y3"                     },
};

/*----------------------------------------
	0x2510 P0R_IPC_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"et_offset_s7"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"motion_x_tearing_gain"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"tearing_gain"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"motion_gain"                             },
};

/*----------------------------------------
	0x2514 P0R_IPC_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_ipc_c_motion_alpha"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_t_grad_weight"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_v_grad_weight"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cr_h_grad_weight"                        },
};

/*----------------------------------------
	0x2518 P0R_IPC_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cr_normalize_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cr_flat_only"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cr_tearing_normalize_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_normalize_base"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_normalize_center"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cr_motion_coring"                        },
};

/*----------------------------------------
	0x251c P0R_IPC_CTRL_07
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_07[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cr_v_en"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cr_45_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cr_15_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cr_postmedian_en"                        },
};

/*----------------------------------------
	0x2520 P0R_IPC_CTRL_08
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_08[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"fmd_caption_range_top"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"fmd_caption_range_bot"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"caption_flow_detected"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"hmc_when_cap_not_detected"               },
};

/*----------------------------------------
	0x2524 P0R_IPC_CTRL_09
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_09[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"fmd_vedge_th"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"fmd_vedge_en"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"fmd_a_th"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"use_3field_err_t"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"two_field_delay_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd_margin_top"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fmd_margin_bottom"                       },
};

/*----------------------------------------
	0x2528 P0R_IPC_CTRL_10
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_10[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"film_inter_with"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"hw_film_enable"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tearing_detect_strength"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cross_check"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"usediffpelcount"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"pn_diff_th"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"scalemeasureforhd"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"loading_time_ctrl"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"fmd_sw_bad_edit_en"                      },
};

/*----------------------------------------
	0x252c P0R_IPC_CTRL_11
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_11[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"repeat_det_line_cnt_th"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"repeat_det_diff_pel_cnt_th"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"repeat_det_noise_th"                     },
};

/*----------------------------------------
	0x2530 P0R_IPC_CTRL_12
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_12[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fmd_32_enable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fmd_22_enable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"fmd_badediten"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"fmd_hw_bad_edit_mul_th"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd_hw_bad_edit_th_min"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"pcn_diff_th"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"fmd_arbitrary_6_4only"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fmd_stillconditition1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"fmd_stillconditition2"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"fmd_arbitrary_still"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"fmd_arbitrary_3_2only"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"fmd_still_cntth"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"fmd_still_cntth_en"                      },
};

/*----------------------------------------
	0x2534 P0R_IPC_CTRL_13
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_13[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fmd32_stillth_pn"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd32_stillthpcn"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd32_pn_maxvalue_minth0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fmd32_pn_maxvalue_minth1"                },
};

/*----------------------------------------
	0x2538 P0R_IPC_CTRL_14
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_14[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"fmd32_min_field_num"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd32_pn_minvalue_maxth"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"fmd32_pn_maxminratio0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"fmd32_pn_maxminratio1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"fmd_32_pcn_small_weight"                 },
};

/*----------------------------------------
	0x253c P0R_IPC_CTRL_15
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_15[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fmd22_stillth_pn"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd22_stillth_pcn"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"bad_edit_sm_min_th"                      },
};

/*----------------------------------------
	0x2540 P0R_IPC_CTRL_16
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_16[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"fmd22_minfieldnum0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"fmd22_minfieldnum1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd22_minvaluemaxth1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd22_maxvalueminth1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"fmd22_maxminratio0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"fmd22_maxminratio1"                      },
};

/*----------------------------------------
	0x2544 P0R_IPC_CTRL_17
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_17[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fmd22_maxvalueminth0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fmd22_minvaluemaxth0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd32_minvaluemaxth0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"fmd32_maxvalueminth0"                    },
};

/*----------------------------------------
	0x2548 P0R_IPC_CTRL_18
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_18[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_ud_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_lr_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_h_grad_gain"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cr_v_grad_gain"                          },
};

/*----------------------------------------
	0x254c P0R_IPC_CTRL_19
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_19[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"center_vld_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"diff_vld_gain"                           },
};

/*----------------------------------------
	0x2550 P0R_IPC_STATUS_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_STATUS_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"pc_cnt"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"nc_cnt"                                  },
};

/*----------------------------------------
	0x2554 P0R_IPC_STATUS_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_STATUS_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"pn_cnt"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"same_cnt"                                },
};

/*----------------------------------------
	0x2558 P0R_IPC_STATUS_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_STATUS_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"fmd32_combwith"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"fmd32_detected"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,4  ,"fmd32_lockingcnt"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"fmd22_combwith"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"fmd22_detected"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"fmd22_lockingcnt"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"fmd_comb_predict"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"bad_edit_detected_hw"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"fmd22_still_detected"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"fmd32_still_detected"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"repeat_detected"                         },
};

/*----------------------------------------
	0x255c P0R_IPC_STATUS_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_STATUS_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"fmd_badeditth_hw"                        },
};

/*----------------------------------------
	0x2580 P0R_VFLT_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_VFLT_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vfilterenable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"vfilterlocalenable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vfilter_strength"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"cb_filter_y"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vfilter_a_th"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vfilter_in_field_var"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"vfilter_use_mc_mask"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"vfilter_expand"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"vfilter_center"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"vfilter_ul4"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"dbgshow_level"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"dbgshow_enable"                          },
};

/*----------------------------------------
	0x2588 P0R_MNR_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_MNR_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"mnr_enable"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"edge_gain_mapping_enable"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"sel_sd_hd"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"debug_mode"                              },
};

/*----------------------------------------
	0x258c P0R_MNR_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_MNR_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"hcoef_00"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"hcoef_01"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"hcoef_02"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"hcoef_03"                                },
};

/*----------------------------------------
	0x2590 P0R_MNR_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_MNR_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"hcoef_04"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"hcoef_05"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"hcoef_06"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"hcoef_07"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"hcoef_08"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"hcoef_09"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"hcoef_10"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"hcoef_11"                                },
};

/*----------------------------------------
	0x2594 P0R_MNR_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_MNR_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"hcoef_12"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"hcoef_13"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"hcoef_14"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"hcoef_15"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"hcoef_16"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"x1_position"                             },
};

/*----------------------------------------
	0x2598 P0R_MNR_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_MNR_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"x2_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"x3_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"x4_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"y1_position"                             },
};

/*----------------------------------------
	0x259c P0R_MNR_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_MNR_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"y2_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"y3_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"y4_position"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"filter_threshold"                        },
};

/*----------------------------------------
	0x25a0 P0R_MNR_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_MNR_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"vcoef0"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"vcoef1"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"vcoef2"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"vcoef3"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"vcoef4"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"vcoef5"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"vcoef6"                                  },
};

/*----------------------------------------
	0x25a8 P0R_VFILTER_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_VFILTER_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cr_vfilter_global_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cr_vfilter_force_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,2  ,"cr_global_frame_num_th"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,8  ,"cr_vfilter_global_th"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"tearing_count"                           },
};

/*----------------------------------------
	0x25ac P0R_BNR_DC_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_DC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dc_bnr_enable"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"ac_blockiness_adaptive_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"motion_gain_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"sd_hd_sel"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"output_mux"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"motion_min"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"motion_max"                              },
};

/*----------------------------------------
	0x25b0 P0R_BNR_DC_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_DC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"blur_enable"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"ac_blockiness_multifly_x_n"              },
};

/*----------------------------------------
	0x25b4 P0R_BNR_DC_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_DC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dc_bnr_gain_ctrl_y2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"dc_bnr_gain_ctrl_x2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"dc_bnr_gain_ctrl_y3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dc_bnr_gain_ctrl_x3"                     },
};

/*----------------------------------------
	0x25b8 P0R_BNR_DC_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_DC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dc_bnr_gain_ctrl_y0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"dc_bnr_gain_ctrl_x0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"dc_bnr_gain_ctrl_y1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"dc_bnr_gain_ctrl_x1"                     },
};

/*----------------------------------------
	0x25bc P0R_BNR_AC_CTRL_06
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_AC_CTRL_06[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ac_bnr_protect_motion_max"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ac_bnr_protect_motion_min"               },
};

/*----------------------------------------
	0x25c0 P0R_BNR_AC_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_AC_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bnr_h_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"bnr_v_en"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"motion_protect_enable"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"source_type"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"status_read_type"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"status_read_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"hbmax_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"vbmax_gain"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"strength_resolution"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"fiter_type"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"output_mux"                              },
};

/*----------------------------------------
	0x25c4 P0R_BNR_AC_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_AC_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"strength_h_x0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"strength_h_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"strength_h_max"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"detect_min_th"                           },
};

/*----------------------------------------
	0x25c8 P0R_BNR_AC_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_AC_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"strength_v_x0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"strength_v_x1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"strength_v_max"                          },
};

/*----------------------------------------
	0x25cc P0R_BNR_AC_CTRL_03
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_AC_CTRL_03[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"h_offset_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"manual_offset_h_value"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"v_offset_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"manual_offset_v_value"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"use_of_hysterisis"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"t_filter_weight"                         },
};

/*----------------------------------------
	0x25d0 P0R_BNR_AC_CTRL_04
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_AC_CTRL_04[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"max_delta_th0"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"max_delta_th1"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"h_blockness_th"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"h_weight_max"                            },
};

/*----------------------------------------
	0x25d4 P0R_BNR_AC_CTRL_05
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_AC_CTRL_05[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"use_of_hysterisis"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"block_boundary_processing_type"          },
};

/*----------------------------------------
	0x25d8 P0R_DNR_MAX_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_DNR_MAX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"enable_snr"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"enable_mnr"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"enable_der"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"enable_dc_bnr"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"enable_ac_bnr"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"debug_enable"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"debug_mode"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"debug_snr_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"debug_mnr_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"debug_der_enable"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"debug_dc_bnr_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"debug_ac_bnr_enable"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"win_control_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"border_enable"                           },
};

/*----------------------------------------
	0x25dc P0R_DNR_DBAR_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_DNR_DBAR_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"debug_bar_en"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"show_debug_bar_for_bnr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"gain"                                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"sd_hd_sel"                               },
};

/*----------------------------------------
	0x25e0 P0R_BNR_STAT_0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BNR_STAT_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ac_bnr_h_status"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ac_bnr_v_status"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"dc_bnr_th"                               },
};

/*----------------------------------------
	0x25e4 P0R_DER_CTRL_0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_DER_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"der_en"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"out_mux"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"bif_en"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"gain2weight_mapping"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"bif_th"                                  },
};

/*----------------------------------------
	0x25e8 P0R_DER_CTRL_1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_DER_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"gain_th0"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"gain_th1"                                },
};

/*----------------------------------------
	0x25f0 P0R_IPC_CTRL_20
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_20[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cr_lock_dir_sel"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cr_center_ratio"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cr_lr_diff_ratio"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cr_hmc_lock_filt_sizeh"                  },
};

/*----------------------------------------
	0x25f4 P0R_IPC_CTRL_21
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_21[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cr_lock_point_add"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cr_lock_point_penalty"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cr_lock_point_valid"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"cr_robustness"                           },
};

/*----------------------------------------
	0x25f8 P0R_IPC_CTRL_22
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x25fc P0R_IPC_CTRL_23
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_23[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"global_tbm_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"flim_panelty_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"es_offset_mode"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"err_mode"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"global_tbm_th"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hmc_2d_gain"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"errs_limit"                              },
};

/*----------------------------------------
	0x2600 P0R_IPC_CTRL_24
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_24[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"errs_gain"                               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"confidance_gain"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"pe0_2d_offset"                           },
};

/*----------------------------------------
	0x2604 P0R_IPC_CTRL_25
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_25[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cubic_coef0"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cubic_coef1"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cubic_coef2"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cubic_coef3"                             },
};

/*----------------------------------------
	0x2608 P0R_IPC_CTRL_26
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_26[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"va_cubic"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"boundary_window"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"force_va"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"half_pel_va"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"dir_med_tap"                             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"diff_med_tap"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"va_blending_ctrl1"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"wide_angle_protection_1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"va_blending_ctrl2"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"errs_chroma_blend_gain"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"strong_global_th"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"narrow_angle_week"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"narrow_angle_protection"                 },
};

/*----------------------------------------
	0x260c P0R_IPC_CTRL_27
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_IPC_CTRL_27[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"dbg_show_mode"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"dbg_show_black_mask"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dbg_pprv_to_curr"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"dbg_prv3_to_prev"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"dbg_curr_to_pprv"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"st_flt_ctrl_x0"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"st_flt_ctrl_x1"                          },
};

/*----------------------------------------
	0x2640 P0R_TPD_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_TPD_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"mux_3"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"mux_2"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"mux_1"                                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"show_scale"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"show_bar_1"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"show_bar_2"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"show_bar_3"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"show_bar_4"                              },
};

/*----------------------------------------
	0x2670 P0R_BBD_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BBD_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"bbd_en"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,1  ,"hys_mode"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"op_mode"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cnt_th"                                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"diff_th"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"bbd_mux"                                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"apl_mux"                                 },
};

/*----------------------------------------
	0x2674 P0R_BBD_CTRL_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BBD_CTRL_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                                      },
};

/*----------------------------------------
	0x2678 P0R_BBD_CTRL_02
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BBD_CTRL_02[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x267c P0R_BBD_STAT_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BBD_STAT_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x0"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y0"                                      },
};

/*----------------------------------------
	0x2680 P0R_BBD_STAT_01
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_BBD_STAT_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"x1"                                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y1"                                      },
};

/*----------------------------------------
	0x2684 P0R_APL_STAT_00
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x2690 P0R_CTI_CTRL_00
----------------------------------------*/
const DBG_REG_FIELD_T dbg_P0R_CTI_CTRL_00[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti_enable"                              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cti_repeat_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cti_clipping_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cti_gain"                                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"cb_filter_c"                             },
};

DBG_REG_T gDbgRegPE0[] = {
	{ 0x0400 ,N_FLD(dbg_P0L_PE0_LOAD)                ,"P0L_PE0_LOAD"                  ,dbg_P0L_PE0_LOAD                },
	{ 0x0404 ,N_FLD(dbg_P0L_PE0_INTR)                ,"P0L_PE0_INTR"                  ,dbg_P0L_PE0_INTR                },
	{ 0x0408 ,N_FLD(dbg_P0L_PE0_STATUS0)             ,"P0L_PE0_STATUS0"               ,dbg_P0L_PE0_STATUS0             },
	{ 0x040c ,N_FLD(dbg_P0L_PE0_STATUS1)             ,"P0L_PE0_STATUS1"               ,dbg_P0L_PE0_STATUS1             },
	{ 0x0410 ,N_FLD(dbg_P0L_PE0_OPMODE)              ,"P0L_PE0_OPMODE"                ,dbg_P0L_PE0_OPMODE              },
	{ 0x0414 ,N_FLD(dbg_P0L_PE0_SRC_SIZE)            ,"P0L_PE0_SRC_SIZE"              ,dbg_P0L_PE0_SRC_SIZE            },
	{ 0x0418 ,N_FLD(dbg_P0L_PE0_FIELD)               ,"P0L_PE0_FIELD"                 ,dbg_P0L_PE0_FIELD               },
	{ 0x041c ,N_FLD(dbg_P0L_PE0_PARAM_BY_DDR)        ,"P0L_PE0_PARAM_BY_DDR"          ,dbg_P0L_PE0_PARAM_BY_DDR        },
	{ 0x0420 ,N_FLD(dbg_P0L_WIN_CTRL_0)              ,"P0L_WIN_CTRL_0"                ,dbg_P0L_WIN_CTRL_0              },
	{ 0x0424 ,N_FLD(dbg_P0L_WIN_CTRL_1)              ,"P0L_WIN_CTRL_1"                ,dbg_P0L_WIN_CTRL_1              },
	{ 0x0428 ,N_FLD(dbg_P0L_WIN_CTRL_2)              ,"P0L_WIN_CTRL_2"                ,dbg_P0L_WIN_CTRL_2              },
	{ 0x042c ,N_FLD(dbg_P0L_WIN_CTRL_3)              ,"P0L_WIN_CTRL_3"                ,dbg_P0L_WIN_CTRL_3              },
	{ 0x0440 ,N_FLD(dbg_P0L_TNR_CTRL_00)             ,"P0L_TNR_CTRL_00"               ,dbg_P0L_TNR_CTRL_00             },
	{ 0x0444 ,N_FLD(dbg_P0L_TNR_CTRL_01)             ,"P0L_TNR_CTRL_01"               ,dbg_P0L_TNR_CTRL_01             },
	{ 0x0448 ,N_FLD(dbg_P0L_TNR_CTRL_02)             ,"P0L_TNR_CTRL_02"               ,dbg_P0L_TNR_CTRL_02             },
	{ 0x044c ,N_FLD(dbg_P0L_TNR_CTRL_03)             ,"P0L_TNR_CTRL_03"               ,dbg_P0L_TNR_CTRL_03             },
	{ 0x0450 ,N_FLD(dbg_P0L_TNR_CTRL_04)             ,"P0L_TNR_CTRL_04"               ,dbg_P0L_TNR_CTRL_04             },
	{ 0x0454 ,N_FLD(dbg_P0L_TNR_CTRL_05)             ,"P0L_TNR_CTRL_05"               ,dbg_P0L_TNR_CTRL_05             },
	{ 0x0458 ,N_FLD(dbg_P0L_TNR_CTRL_06)             ,"P0L_TNR_CTRL_06"               ,dbg_P0L_TNR_CTRL_06             },
	{ 0x045c ,N_FLD(dbg_P0L_TNR_CTRL_07)             ,"P0L_TNR_CTRL_07"               ,dbg_P0L_TNR_CTRL_07             },
	{ 0x0460 ,N_FLD(dbg_P0L_TNR_CTRL_08)             ,"P0L_TNR_CTRL_08"               ,dbg_P0L_TNR_CTRL_08             },
	{ 0x0464 ,N_FLD(dbg_P0L_TNR_CTRL_09)             ,"P0L_TNR_CTRL_09"               ,dbg_P0L_TNR_CTRL_09             },
	{ 0x0468 ,N_FLD(dbg_P0L_TNR_CTRL_10)             ,"P0L_TNR_CTRL_10"               ,dbg_P0L_TNR_CTRL_10             },
	{ 0x046c ,N_FLD(dbg_P0L_TNR_CTRL_11)             ,"P0L_TNR_CTRL_11"               ,dbg_P0L_TNR_CTRL_11             },
	{ 0x0470 ,N_FLD(dbg_P0L_TNR_CTRL_12)             ,"P0L_TNR_CTRL_12"               ,dbg_P0L_TNR_CTRL_12             },
	{ 0x0474 ,N_FLD(dbg_P0L_TNR_CTRL_13)             ,"P0L_TNR_CTRL_13"               ,dbg_P0L_TNR_CTRL_13             },
	{ 0x0478 ,N_FLD(dbg_P0L_TNR_CTRL_14)             ,"P0L_TNR_CTRL_14"               ,dbg_P0L_TNR_CTRL_14             },
	{ 0x047c ,N_FLD(dbg_P0L_TNR_CTRL_15)             ,"P0L_TNR_CTRL_15"               ,dbg_P0L_TNR_CTRL_15             },
	{ 0x0480 ,N_FLD(dbg_P0L_TNR_CTRL_16)             ,"P0L_TNR_CTRL_16"               ,dbg_P0L_TNR_CTRL_16             },
	{ 0x0484 ,N_FLD(dbg_P0L_TNR_CTRL_17)             ,"P0L_TNR_CTRL_17"               ,dbg_P0L_TNR_CTRL_17             },
	{ 0x0488 ,N_FLD(dbg_P0L_TNR_CTRL_18)             ,"P0L_TNR_CTRL_18"               ,dbg_P0L_TNR_CTRL_18             },
	{ 0x048c ,N_FLD(dbg_P0L_TNR_CTRL_19)             ,"P0L_TNR_CTRL_19"               ,dbg_P0L_TNR_CTRL_19             },
	{ 0x0490 ,N_FLD(dbg_P0L_TNR_CTRL_20)             ,"P0L_TNR_CTRL_20"               ,dbg_P0L_TNR_CTRL_20             },
	{ 0x0494 ,N_FLD(dbg_P0L_TNR_CTRL_21)             ,"P0L_TNR_CTRL_21"               ,dbg_P0L_TNR_CTRL_21             },
	{ 0x0498 ,N_FLD(dbg_P0L_TNR_CTRL_22)             ,"P0L_TNR_CTRL_22"               ,dbg_P0L_TNR_CTRL_22             },
	{ 0x049c ,N_FLD(dbg_P0L_TNR_CTRL_23)             ,"P0L_TNR_CTRL_23"               ,dbg_P0L_TNR_CTRL_23             },
	{ 0x04a0 ,N_FLD(dbg_P0L_TNR_CTRL_24)             ,"P0L_TNR_CTRL_24"               ,dbg_P0L_TNR_CTRL_24             },
	{ 0x04a4 ,N_FLD(dbg_P0L_TNR_CTRL_25)             ,"P0L_TNR_CTRL_25"               ,dbg_P0L_TNR_CTRL_25             },
	{ 0x04a8 ,N_FLD(dbg_P0L_TNR_CTRL_26)             ,"P0L_TNR_CTRL_26"               ,dbg_P0L_TNR_CTRL_26             },
	{ 0x04ac ,N_FLD(dbg_P0L_TNR_CTRL_27)             ,"P0L_TNR_CTRL_27"               ,dbg_P0L_TNR_CTRL_27             },
	{ 0x04b0 ,N_FLD(dbg_P0L_TNR_CTRL_28)             ,"P0L_TNR_CTRL_28"               ,dbg_P0L_TNR_CTRL_28             },
	{ 0x04b4 ,N_FLD(dbg_P0L_TNR_CTRL_29)             ,"P0L_TNR_CTRL_29"               ,dbg_P0L_TNR_CTRL_29             },
	{ 0x04b8 ,N_FLD(dbg_P0L_TNR_CTRL_30)             ,"P0L_TNR_CTRL_30"               ,dbg_P0L_TNR_CTRL_30             },
	{ 0x04bc ,N_FLD(dbg_P0L_TNR_CTRL_31)             ,"P0L_TNR_CTRL_31"               ,dbg_P0L_TNR_CTRL_31             },
	{ 0x04c0 ,N_FLD(dbg_P0L_TNR_STATUS_00)           ,"P0L_TNR_STATUS_00"             ,dbg_P0L_TNR_STATUS_00           },
	{ 0x04c4 ,N_FLD(dbg_P0L_TNR_STATUS_01)           ,"P0L_TNR_STATUS_01"             ,dbg_P0L_TNR_STATUS_01           },
	{ 0x04c8 ,N_FLD(dbg_P0L_TNR_STATUS_02)           ,"P0L_TNR_STATUS_02"             ,dbg_P0L_TNR_STATUS_02           },
	{ 0x04cc ,N_FLD(dbg_P0L_TNR_STATUS_03)           ,"P0L_TNR_STATUS_03"             ,dbg_P0L_TNR_STATUS_03           },
	{ 0x04d0 ,N_FLD(dbg_P0L_TNR_MAIN_LUT_00)         ,"P0L_TNR_MAIN_LUT_00"           ,dbg_P0L_TNR_MAIN_LUT_00         },
	{ 0x04d4 ,N_FLD(dbg_P0L_TNR_MAIN_LUT_01)         ,"P0L_TNR_MAIN_LUT_01"           ,dbg_P0L_TNR_MAIN_LUT_01         },
	{ 0x04d8 ,N_FLD(dbg_P0L_TNR_MAIN_LUT_02)         ,"P0L_TNR_MAIN_LUT_02"           ,dbg_P0L_TNR_MAIN_LUT_02         },
	{ 0x04e0 ,N_FLD(dbg_P0L_TNR_CTRL_32)             ,"P0L_TNR_CTRL_32"               ,dbg_P0L_TNR_CTRL_32             },
	{ 0x04e4 ,N_FLD(dbg_P0L_TNR_CTRL_33)             ,"P0L_TNR_CTRL_33"               ,dbg_P0L_TNR_CTRL_33             },
	{ 0x04e8 ,N_FLD(dbg_P0L_TNR_CTRL_34)             ,"P0L_TNR_CTRL_34"               ,dbg_P0L_TNR_CTRL_34             },
	{ 0x04ec ,N_FLD(dbg_P0L_TNR_CTRL_35)             ,"P0L_TNR_CTRL_35"               ,dbg_P0L_TNR_CTRL_35             },
	{ 0x04f0 ,N_FLD(dbg_P0L_TNR_CRG_CTRL_00)         ,"P0L_TNR_CRG_CTRL_00"           ,dbg_P0L_TNR_CRG_CTRL_00         },
	{ 0x04f4 ,N_FLD(dbg_P0L_TNR_CRG_CTRL_01)         ,"P0L_TNR_CRG_CTRL_01"           ,dbg_P0L_TNR_CRG_CTRL_01         },
	{ 0x0500 ,N_FLD(dbg_P0L_IPC_CTRL_00)             ,"P0L_IPC_CTRL_00"               ,dbg_P0L_IPC_CTRL_00             },
	{ 0x0504 ,N_FLD(dbg_P0L_IPC_CTRL_01)             ,"P0L_IPC_CTRL_01"               ,dbg_P0L_IPC_CTRL_01             },
	{ 0x0508 ,N_FLD(dbg_P0L_IPC_CTRL_02)             ,"P0L_IPC_CTRL_02"               ,dbg_P0L_IPC_CTRL_02             },
	{ 0x050c ,N_FLD(dbg_P0L_IPC_CTRL_03)             ,"P0L_IPC_CTRL_03"               ,dbg_P0L_IPC_CTRL_03             },
	{ 0x0510 ,N_FLD(dbg_P0L_IPC_CTRL_04)             ,"P0L_IPC_CTRL_04"               ,dbg_P0L_IPC_CTRL_04             },
	{ 0x0514 ,N_FLD(dbg_P0L_IPC_CTRL_05)             ,"P0L_IPC_CTRL_05"               ,dbg_P0L_IPC_CTRL_05             },
	{ 0x0518 ,N_FLD(dbg_P0L_IPC_CTRL_06)             ,"P0L_IPC_CTRL_06"               ,dbg_P0L_IPC_CTRL_06             },
	{ 0x051c ,N_FLD(dbg_P0L_IPC_CTRL_07)             ,"P0L_IPC_CTRL_07"               ,dbg_P0L_IPC_CTRL_07             },
	{ 0x0520 ,N_FLD(dbg_P0L_IPC_CTRL_08)             ,"P0L_IPC_CTRL_08"               ,dbg_P0L_IPC_CTRL_08             },
	{ 0x0524 ,N_FLD(dbg_P0L_IPC_CTRL_09)             ,"P0L_IPC_CTRL_09"               ,dbg_P0L_IPC_CTRL_09             },
	{ 0x0528 ,N_FLD(dbg_P0L_IPC_CTRL_10)             ,"P0L_IPC_CTRL_10"               ,dbg_P0L_IPC_CTRL_10             },
	{ 0x052c ,N_FLD(dbg_P0L_IPC_CTRL_11)             ,"P0L_IPC_CTRL_11"               ,dbg_P0L_IPC_CTRL_11             },
	{ 0x0530 ,N_FLD(dbg_P0L_IPC_CTRL_12)             ,"P0L_IPC_CTRL_12"               ,dbg_P0L_IPC_CTRL_12             },
	{ 0x0534 ,N_FLD(dbg_P0L_IPC_CTRL_13)             ,"P0L_IPC_CTRL_13"               ,dbg_P0L_IPC_CTRL_13             },
	{ 0x0538 ,N_FLD(dbg_P0L_IPC_CTRL_14)             ,"P0L_IPC_CTRL_14"               ,dbg_P0L_IPC_CTRL_14             },
	{ 0x053c ,N_FLD(dbg_P0L_IPC_CTRL_15)             ,"P0L_IPC_CTRL_15"               ,dbg_P0L_IPC_CTRL_15             },
	{ 0x0540 ,N_FLD(dbg_P0L_IPC_CTRL_16)             ,"P0L_IPC_CTRL_16"               ,dbg_P0L_IPC_CTRL_16             },
	{ 0x0544 ,N_FLD(dbg_P0L_IPC_CTRL_17)             ,"P0L_IPC_CTRL_17"               ,dbg_P0L_IPC_CTRL_17             },
	{ 0x0548 ,N_FLD(dbg_P0L_IPC_CTRL_18)             ,"P0L_IPC_CTRL_18"               ,dbg_P0L_IPC_CTRL_18             },
	{ 0x054c ,N_FLD(dbg_P0L_IPC_CTRL_19)             ,"P0L_IPC_CTRL_19"               ,dbg_P0L_IPC_CTRL_19             },
	{ 0x0550 ,N_FLD(dbg_P0L_IPC_STATUS_00)           ,"P0L_IPC_STATUS_00"             ,dbg_P0L_IPC_STATUS_00           },
	{ 0x0554 ,N_FLD(dbg_P0L_IPC_STATUS_01)           ,"P0L_IPC_STATUS_01"             ,dbg_P0L_IPC_STATUS_01           },
	{ 0x0558 ,N_FLD(dbg_P0L_IPC_STATUS_02)           ,"P0L_IPC_STATUS_02"             ,dbg_P0L_IPC_STATUS_02           },
	{ 0x055c ,N_FLD(dbg_P0L_IPC_STATUS_03)           ,"P0L_IPC_STATUS_03"             ,dbg_P0L_IPC_STATUS_03           },
	{ 0x0560 ,N_FLD(dbg_CLC_CTRL_00)                 ,"CLC_CTRL_00"                   ,dbg_CLC_CTRL_00                 },
	{ 0x0564 ,N_FLD(dbg_CLC_CTRL_01)                 ,"CLC_CTRL_01"                   ,dbg_CLC_CTRL_01                 },
	{ 0x0568 ,N_FLD(dbg_CLC_CTRL_02)                 ,"CLC_CTRL_02"                   ,dbg_CLC_CTRL_02                 },
	{ 0x056c ,N_FLD(dbg_CLC_CTRL_03)                 ,"CLC_CTRL_03"                   ,dbg_CLC_CTRL_03                 },
	{ 0x0570 ,N_FLD(dbg_CLC_CTRL_04)                 ,"CLC_CTRL_04"                   ,dbg_CLC_CTRL_04                 },
	{ 0x0574 ,N_FLD(dbg_CLC_CTRL_05)                 ,"CLC_CTRL_05"                   ,dbg_CLC_CTRL_05                 },
	{ 0x0578 ,N_FLD(dbg_CLC_CTRL_06)                 ,"CLC_CTRL_06"                   ,dbg_CLC_CTRL_06                 },
	{ 0x057c ,N_FLD(dbg_CLC_STAT_00)                 ,"CLC_STAT_00"                   ,dbg_CLC_STAT_00                 },
	{ 0x0580 ,N_FLD(dbg_P0L_VFLT_CTRL)               ,"P0L_VFLT_CTRL"                 ,dbg_P0L_VFLT_CTRL               },
	{ 0x0588 ,N_FLD(dbg_P0L_MNR_CTRL_00)             ,"P0L_MNR_CTRL_00"               ,dbg_P0L_MNR_CTRL_00             },
	{ 0x058c ,N_FLD(dbg_P0L_MNR_CTRL_01)             ,"P0L_MNR_CTRL_01"               ,dbg_P0L_MNR_CTRL_01             },
	{ 0x0590 ,N_FLD(dbg_P0L_MNR_CTRL_02)             ,"P0L_MNR_CTRL_02"               ,dbg_P0L_MNR_CTRL_02             },
	{ 0x0594 ,N_FLD(dbg_P0L_MNR_CTRL_03)             ,"P0L_MNR_CTRL_03"               ,dbg_P0L_MNR_CTRL_03             },
	{ 0x0598 ,N_FLD(dbg_P0L_MNR_CTRL_04)             ,"P0L_MNR_CTRL_04"               ,dbg_P0L_MNR_CTRL_04             },
	{ 0x059c ,N_FLD(dbg_P0L_MNR_CTRL_05)             ,"P0L_MNR_CTRL_05"               ,dbg_P0L_MNR_CTRL_05             },
	{ 0x05a0 ,N_FLD(dbg_P0L_MNR_CTRL_06)             ,"P0L_MNR_CTRL_06"               ,dbg_P0L_MNR_CTRL_06             },
	{ 0x05a8 ,N_FLD(dbg_P0L_VFILTER_01)              ,"P0L_VFILTER_01"                ,dbg_P0L_VFILTER_01              },
	{ 0x05ac ,N_FLD(dbg_P0L_BNR_DC_CTRL_00)          ,"P0L_BNR_DC_CTRL_00"            ,dbg_P0L_BNR_DC_CTRL_00          },
	{ 0x05b0 ,N_FLD(dbg_P0L_BNR_DC_CTRL_01)          ,"P0L_BNR_DC_CTRL_01"            ,dbg_P0L_BNR_DC_CTRL_01          },
	{ 0x05b4 ,N_FLD(dbg_P0L_BNR_DC_CTRL_02)          ,"P0L_BNR_DC_CTRL_02"            ,dbg_P0L_BNR_DC_CTRL_02          },
	{ 0x05b8 ,N_FLD(dbg_P0L_BNR_DC_CTRL_03)          ,"P0L_BNR_DC_CTRL_03"            ,dbg_P0L_BNR_DC_CTRL_03          },
	{ 0x05bc ,N_FLD(dbg_P0L_BNR_AC_CTRL_06)          ,"P0L_BNR_AC_CTRL_06"            ,dbg_P0L_BNR_AC_CTRL_06          },
	{ 0x05c0 ,N_FLD(dbg_P0L_BNR_AC_CTRL_00)          ,"P0L_BNR_AC_CTRL_00"            ,dbg_P0L_BNR_AC_CTRL_00          },
	{ 0x05c4 ,N_FLD(dbg_P0L_BNR_AC_CTRL_01)          ,"P0L_BNR_AC_CTRL_01"            ,dbg_P0L_BNR_AC_CTRL_01          },
	{ 0x05c8 ,N_FLD(dbg_P0L_BNR_AC_CTRL_02)          ,"P0L_BNR_AC_CTRL_02"            ,dbg_P0L_BNR_AC_CTRL_02          },
	{ 0x05cc ,N_FLD(dbg_P0L_BNR_AC_CTRL_03)          ,"P0L_BNR_AC_CTRL_03"            ,dbg_P0L_BNR_AC_CTRL_03          },
	{ 0x05d0 ,N_FLD(dbg_P0L_BNR_AC_CTRL_04)          ,"P0L_BNR_AC_CTRL_04"            ,dbg_P0L_BNR_AC_CTRL_04          },
	{ 0x05d4 ,N_FLD(dbg_P0L_BNR_AC_CTRL_05)          ,"P0L_BNR_AC_CTRL_05"            ,dbg_P0L_BNR_AC_CTRL_05          },
	{ 0x05d8 ,N_FLD(dbg_P0L_DNR_MAX_CTRL)            ,"P0L_DNR_MAX_CTRL"              ,dbg_P0L_DNR_MAX_CTRL            },
	{ 0x05dc ,N_FLD(dbg_P0L_DNR_DBAR_CTRL)           ,"P0L_DNR_DBAR_CTRL"             ,dbg_P0L_DNR_DBAR_CTRL           },
	{ 0x05e0 ,N_FLD(dbg_P0L_BNR_STAT_0)              ,"P0L_BNR_STAT_0"                ,dbg_P0L_BNR_STAT_0              },
	{ 0x05e4 ,N_FLD(dbg_P0L_DER_CTRL_0)              ,"P0L_DER_CTRL_0"                ,dbg_P0L_DER_CTRL_0              },
	{ 0x05e8 ,N_FLD(dbg_P0L_DER_CTRL_1)              ,"P0L_DER_CTRL_1"                ,dbg_P0L_DER_CTRL_1              },
	{ 0x05f0 ,N_FLD(dbg_P0L_IPC_CTRL_20)             ,"P0L_IPC_CTRL_20"               ,dbg_P0L_IPC_CTRL_20             },
	{ 0x05f4 ,N_FLD(dbg_P0L_IPC_CTRL_21)             ,"P0L_IPC_CTRL_21"               ,dbg_P0L_IPC_CTRL_21             },
	{ 0x05f8 ,0                                      ,"P0L_IPC_CTRL_22"               ,NULL                            },
	{ 0x05fc ,N_FLD(dbg_P0L_IPC_CTRL_23)             ,"P0L_IPC_CTRL_23"               ,dbg_P0L_IPC_CTRL_23             },
	{ 0x0600 ,N_FLD(dbg_P0L_IPC_CTRL_24)             ,"P0L_IPC_CTRL_24"               ,dbg_P0L_IPC_CTRL_24             },
	{ 0x0604 ,N_FLD(dbg_P0L_IPC_CTRL_25)             ,"P0L_IPC_CTRL_25"               ,dbg_P0L_IPC_CTRL_25             },
	{ 0x0608 ,N_FLD(dbg_P0L_IPC_CTRL_26)             ,"P0L_IPC_CTRL_26"               ,dbg_P0L_IPC_CTRL_26             },
	{ 0x060c ,N_FLD(dbg_P0L_IPC_CTRL_27)             ,"P0L_IPC_CTRL_27"               ,dbg_P0L_IPC_CTRL_27             },
	{ 0x0640 ,N_FLD(dbg_P0L_TPD_CTRL_00)             ,"P0L_TPD_CTRL_00"               ,dbg_P0L_TPD_CTRL_00             },
	{ 0x0644 ,N_FLD(dbg_TPD_CTRL_01)                 ,"TPD_CTRL_01"                   ,dbg_TPD_CTRL_01                 },
	{ 0x0648 ,N_FLD(dbg_TPD_CTRL_02)                 ,"TPD_CTRL_02"                   ,dbg_TPD_CTRL_02                 },
	{ 0x064c ,N_FLD(dbg_TPD_CTRL_03)                 ,"TPD_CTRL_03"                   ,dbg_TPD_CTRL_03                 },
	{ 0x0650 ,N_FLD(dbg_TPD_CTRL_04)                 ,"TPD_CTRL_04"                   ,dbg_TPD_CTRL_04                 },
	{ 0x0654 ,N_FLD(dbg_TPD_CTRL_05)                 ,"TPD_CTRL_05"                   ,dbg_TPD_CTRL_05                 },
	{ 0x0658 ,N_FLD(dbg_TPD_CTRL_06)                 ,"TPD_CTRL_06"                   ,dbg_TPD_CTRL_06                 },
	{ 0x065c ,N_FLD(dbg_TPD_CTRL_07)                 ,"TPD_CTRL_07"                   ,dbg_TPD_CTRL_07                 },
	{ 0x0660 ,N_FLD(dbg_TPD_STAT_00)                 ,"TPD_STAT_00"                   ,dbg_TPD_STAT_00                 },
	{ 0x0664 ,N_FLD(dbg_TPD_STAT_01)                 ,"TPD_STAT_01"                   ,dbg_TPD_STAT_01                 },
	{ 0x0670 ,N_FLD(dbg_P0L_BBD_CTRL_00)             ,"P0L_BBD_CTRL_00"               ,dbg_P0L_BBD_CTRL_00             },
	{ 0x0674 ,N_FLD(dbg_P0L_BBD_CTRL_01)             ,"P0L_BBD_CTRL_01"               ,dbg_P0L_BBD_CTRL_01             },
	{ 0x0678 ,N_FLD(dbg_P0L_BBD_CTRL_02)             ,"P0L_BBD_CTRL_02"               ,dbg_P0L_BBD_CTRL_02             },
	{ 0x067c ,N_FLD(dbg_P0L_BBD_STAT_00)             ,"P0L_BBD_STAT_00"               ,dbg_P0L_BBD_STAT_00             },
	{ 0x0680 ,N_FLD(dbg_P0L_BBD_STAT_01)             ,"P0L_BBD_STAT_01"               ,dbg_P0L_BBD_STAT_01             },
	{ 0x0684 ,0                                      ,"P0L_APL_STAT_00"               ,NULL                            },
	{ 0x0690 ,N_FLD(dbg_P0L_CTI_CTRL_00)             ,"P0L_CTI_CTRL_00"               ,dbg_P0L_CTI_CTRL_00             },
	{ 0x06a0 ,N_FLD(dbg_PE0_3DFD_CTRL_00)            ,"PE0_3DFD_CTRL_00"              ,dbg_PE0_3DFD_CTRL_00            },
	{ 0x06a4 ,N_FLD(dbg_PE0_3DFD_CTRL_01)            ,"PE0_3DFD_CTRL_01"              ,dbg_PE0_3DFD_CTRL_01            },
	{ 0x06a8 ,N_FLD(dbg_PE0_3DFD_CTRL_02)            ,"PE0_3DFD_CTRL_02"              ,dbg_PE0_3DFD_CTRL_02            },
	{ 0x06ac ,N_FLD(dbg_PE0_3DFD_CTRL_03)            ,"PE0_3DFD_CTRL_03"              ,dbg_PE0_3DFD_CTRL_03            },
	{ 0x06b0 ,N_FLD(dbg_PE0_3DFD_STAT_00)            ,"PE0_3DFD_STAT_00"              ,dbg_PE0_3DFD_STAT_00            },
	{ 0x06b4 ,N_FLD(dbg_PE0_3DFD_STAT_01)            ,"PE0_3DFD_STAT_01"              ,dbg_PE0_3DFD_STAT_01            },
	{ 0x06b8 ,N_FLD(dbg_PE0_3DFD_STAT_02)            ,"PE0_3DFD_STAT_02"              ,dbg_PE0_3DFD_STAT_02            },
	{ 0x06bc ,N_FLD(dbg_PE0_3DFD_STAT_03)            ,"PE0_3DFD_STAT_03"              ,dbg_PE0_3DFD_STAT_03            },
	{ 0x06c0 ,N_FLD(dbg_PE0_3DFD_STAT_04)            ,"PE0_3DFD_STAT_04"              ,dbg_PE0_3DFD_STAT_04            },
	{ 0x06c4 ,N_FLD(dbg_PE0_3DFD_STAT_05)            ,"PE0_3DFD_STAT_05"              ,dbg_PE0_3DFD_STAT_05            },
	{ 0x06c8 ,N_FLD(dbg_PE0_3DFD_STAT_06)            ,"PE0_3DFD_STAT_06"              ,dbg_PE0_3DFD_STAT_06            },
	{ 0x06cc ,N_FLD(dbg_PE0_3DFD_STAT_07)            ,"PE0_3DFD_STAT_07"              ,dbg_PE0_3DFD_STAT_07            },
	{ 0x2400 ,N_FLD(dbg_P0R_PE0_LOAD)                ,"P0R_PE0_LOAD"                  ,dbg_P0R_PE0_LOAD                },
	{ 0x2404 ,N_FLD(dbg_P0R_PE0_INTR)                ,"P0R_PE0_INTR"                  ,dbg_P0R_PE0_INTR                },
	{ 0x2408 ,N_FLD(dbg_P0R_PE0_STATUS0)             ,"P0R_PE0_STATUS0"               ,dbg_P0R_PE0_STATUS0             },
	{ 0x240c ,N_FLD(dbg_P0R_PE0_STATUS1)             ,"P0R_PE0_STATUS1"               ,dbg_P0R_PE0_STATUS1             },
	{ 0x2410 ,N_FLD(dbg_P0R_PE0_OPMODE)              ,"P0R_PE0_OPMODE"                ,dbg_P0R_PE0_OPMODE              },
	{ 0x2414 ,N_FLD(dbg_P0R_PE0_SRC_SIZE)            ,"P0R_PE0_SRC_SIZE"              ,dbg_P0R_PE0_SRC_SIZE            },
	{ 0x2418 ,N_FLD(dbg_P0R_PE0_FIELD)               ,"P0R_PE0_FIELD"                 ,dbg_P0R_PE0_FIELD               },
	{ 0x241c ,N_FLD(dbg_P0R_PE0_PARAM_BY_DDR)        ,"P0R_PE0_PARAM_BY_DDR"          ,dbg_P0R_PE0_PARAM_BY_DDR        },
	{ 0x2420 ,N_FLD(dbg_P0R_WIN_CTRL_0)              ,"P0R_WIN_CTRL_0"                ,dbg_P0R_WIN_CTRL_0              },
	{ 0x2424 ,N_FLD(dbg_P0R_WIN_CTRL_1)              ,"P0R_WIN_CTRL_1"                ,dbg_P0R_WIN_CTRL_1              },
	{ 0x2428 ,N_FLD(dbg_P0R_WIN_CTRL_2)              ,"P0R_WIN_CTRL_2"                ,dbg_P0R_WIN_CTRL_2              },
	{ 0x242c ,N_FLD(dbg_P0R_WIN_CTRL_3)              ,"P0R_WIN_CTRL_3"                ,dbg_P0R_WIN_CTRL_3              },
	{ 0x2440 ,N_FLD(dbg_P0R_TNR_CTRL_00)             ,"P0R_TNR_CTRL_00"               ,dbg_P0R_TNR_CTRL_00             },
	{ 0x2444 ,N_FLD(dbg_P0R_TNR_CTRL_01)             ,"P0R_TNR_CTRL_01"               ,dbg_P0R_TNR_CTRL_01             },
	{ 0x2448 ,N_FLD(dbg_P0R_TNR_CTRL_02)             ,"P0R_TNR_CTRL_02"               ,dbg_P0R_TNR_CTRL_02             },
	{ 0x244c ,N_FLD(dbg_P0R_TNR_CTRL_03)             ,"P0R_TNR_CTRL_03"               ,dbg_P0R_TNR_CTRL_03             },
	{ 0x2450 ,N_FLD(dbg_P0R_TNR_CTRL_04)             ,"P0R_TNR_CTRL_04"               ,dbg_P0R_TNR_CTRL_04             },
	{ 0x2454 ,N_FLD(dbg_P0R_TNR_CTRL_05)             ,"P0R_TNR_CTRL_05"               ,dbg_P0R_TNR_CTRL_05             },
	{ 0x2458 ,N_FLD(dbg_P0R_TNR_CTRL_06)             ,"P0R_TNR_CTRL_06"               ,dbg_P0R_TNR_CTRL_06             },
	{ 0x245c ,N_FLD(dbg_P0R_TNR_CTRL_07)             ,"P0R_TNR_CTRL_07"               ,dbg_P0R_TNR_CTRL_07             },
	{ 0x2460 ,N_FLD(dbg_P0R_TNR_CTRL_08)             ,"P0R_TNR_CTRL_08"               ,dbg_P0R_TNR_CTRL_08             },
	{ 0x2464 ,N_FLD(dbg_P0R_TNR_CTRL_09)             ,"P0R_TNR_CTRL_09"               ,dbg_P0R_TNR_CTRL_09             },
	{ 0x2468 ,N_FLD(dbg_P0R_TNR_CTRL_10)             ,"P0R_TNR_CTRL_10"               ,dbg_P0R_TNR_CTRL_10             },
	{ 0x246c ,N_FLD(dbg_P0R_TNR_CTRL_11)             ,"P0R_TNR_CTRL_11"               ,dbg_P0R_TNR_CTRL_11             },
	{ 0x2470 ,N_FLD(dbg_P0R_TNR_CTRL_12)             ,"P0R_TNR_CTRL_12"               ,dbg_P0R_TNR_CTRL_12             },
	{ 0x2474 ,N_FLD(dbg_P0R_TNR_CTRL_13)             ,"P0R_TNR_CTRL_13"               ,dbg_P0R_TNR_CTRL_13             },
	{ 0x2478 ,N_FLD(dbg_P0R_TNR_CTRL_14)             ,"P0R_TNR_CTRL_14"               ,dbg_P0R_TNR_CTRL_14             },
	{ 0x247c ,N_FLD(dbg_P0R_TNR_CTRL_15)             ,"P0R_TNR_CTRL_15"               ,dbg_P0R_TNR_CTRL_15             },
	{ 0x2480 ,N_FLD(dbg_P0R_TNR_CTRL_16)             ,"P0R_TNR_CTRL_16"               ,dbg_P0R_TNR_CTRL_16             },
	{ 0x2484 ,N_FLD(dbg_P0R_TNR_CTRL_17)             ,"P0R_TNR_CTRL_17"               ,dbg_P0R_TNR_CTRL_17             },
	{ 0x2488 ,N_FLD(dbg_P0R_TNR_CTRL_18)             ,"P0R_TNR_CTRL_18"               ,dbg_P0R_TNR_CTRL_18             },
	{ 0x248c ,N_FLD(dbg_P0R_TNR_CTRL_19)             ,"P0R_TNR_CTRL_19"               ,dbg_P0R_TNR_CTRL_19             },
	{ 0x2490 ,N_FLD(dbg_P0R_TNR_CTRL_20)             ,"P0R_TNR_CTRL_20"               ,dbg_P0R_TNR_CTRL_20             },
	{ 0x2494 ,N_FLD(dbg_P0R_TNR_CTRL_21)             ,"P0R_TNR_CTRL_21"               ,dbg_P0R_TNR_CTRL_21             },
	{ 0x2498 ,N_FLD(dbg_P0R_TNR_CTRL_22)             ,"P0R_TNR_CTRL_22"               ,dbg_P0R_TNR_CTRL_22             },
	{ 0x249c ,N_FLD(dbg_P0R_TNR_CTRL_23)             ,"P0R_TNR_CTRL_23"               ,dbg_P0R_TNR_CTRL_23             },
	{ 0x24a0 ,N_FLD(dbg_P0R_TNR_CTRL_24)             ,"P0R_TNR_CTRL_24"               ,dbg_P0R_TNR_CTRL_24             },
	{ 0x24a4 ,N_FLD(dbg_P0R_TNR_CTRL_25)             ,"P0R_TNR_CTRL_25"               ,dbg_P0R_TNR_CTRL_25             },
	{ 0x24a8 ,N_FLD(dbg_P0R_TNR_CTRL_26)             ,"P0R_TNR_CTRL_26"               ,dbg_P0R_TNR_CTRL_26             },
	{ 0x24ac ,N_FLD(dbg_P0R_TNR_CTRL_27)             ,"P0R_TNR_CTRL_27"               ,dbg_P0R_TNR_CTRL_27             },
	{ 0x24b0 ,N_FLD(dbg_P0R_TNR_CTRL_28)             ,"P0R_TNR_CTRL_28"               ,dbg_P0R_TNR_CTRL_28             },
	{ 0x24b4 ,N_FLD(dbg_P0R_TNR_CTRL_29)             ,"P0R_TNR_CTRL_29"               ,dbg_P0R_TNR_CTRL_29             },
	{ 0x24b8 ,N_FLD(dbg_P0R_TNR_CTRL_30)             ,"P0R_TNR_CTRL_30"               ,dbg_P0R_TNR_CTRL_30             },
	{ 0x24bc ,N_FLD(dbg_P0R_TNR_CTRL_31)             ,"P0R_TNR_CTRL_31"               ,dbg_P0R_TNR_CTRL_31             },
	{ 0x24c0 ,N_FLD(dbg_P0R_TNR_STATUS_00)           ,"P0R_TNR_STATUS_00"             ,dbg_P0R_TNR_STATUS_00           },
	{ 0x24c4 ,N_FLD(dbg_P0R_TNR_STATUS_01)           ,"P0R_TNR_STATUS_01"             ,dbg_P0R_TNR_STATUS_01           },
	{ 0x24c8 ,N_FLD(dbg_P0R_TNR_STATUS_02)           ,"P0R_TNR_STATUS_02"             ,dbg_P0R_TNR_STATUS_02           },
	{ 0x24cc ,N_FLD(dbg_P0R_TNR_STATUS_03)           ,"P0R_TNR_STATUS_03"             ,dbg_P0R_TNR_STATUS_03           },
	{ 0x24d0 ,N_FLD(dbg_P0R_TNR_MAIN_LUT_00)         ,"P0R_TNR_MAIN_LUT_00"           ,dbg_P0R_TNR_MAIN_LUT_00         },
	{ 0x24d4 ,N_FLD(dbg_P0R_TNR_MAIN_LUT_01)         ,"P0R_TNR_MAIN_LUT_01"           ,dbg_P0R_TNR_MAIN_LUT_01         },
	{ 0x24d8 ,N_FLD(dbg_P0R_TNR_MAIN_LUT_02)         ,"P0R_TNR_MAIN_LUT_02"           ,dbg_P0R_TNR_MAIN_LUT_02         },
	{ 0x24e0 ,N_FLD(dbg_P0R_TNR_CTRL_32)             ,"P0R_TNR_CTRL_32"               ,dbg_P0R_TNR_CTRL_32             },
	{ 0x24e4 ,N_FLD(dbg_P0R_TNR_CTRL_33)             ,"P0R_TNR_CTRL_33"               ,dbg_P0R_TNR_CTRL_33             },
	{ 0x24e8 ,N_FLD(dbg_P0R_TNR_CTRL_34)             ,"P0R_TNR_CTRL_34"               ,dbg_P0R_TNR_CTRL_34             },
	{ 0x24ec ,N_FLD(dbg_P0R_TNR_CTRL_35)             ,"P0R_TNR_CTRL_35"               ,dbg_P0R_TNR_CTRL_35             },
	{ 0x24f0 ,N_FLD(dbg_P0R_TNR_CRG_CTRL_00)         ,"P0R_TNR_CRG_CTRL_00"           ,dbg_P0R_TNR_CRG_CTRL_00         },
	{ 0x24f4 ,N_FLD(dbg_P0R_TNR_CRG_CTRL_01)         ,"P0R_TNR_CRG_CTRL_01"           ,dbg_P0R_TNR_CRG_CTRL_01         },
	{ 0x2500 ,N_FLD(dbg_P0R_IPC_CTRL_00)             ,"P0R_IPC_CTRL_00"               ,dbg_P0R_IPC_CTRL_00             },
	{ 0x2504 ,N_FLD(dbg_P0R_IPC_CTRL_01)             ,"P0R_IPC_CTRL_01"               ,dbg_P0R_IPC_CTRL_01             },
	{ 0x2508 ,N_FLD(dbg_P0R_IPC_CTRL_02)             ,"P0R_IPC_CTRL_02"               ,dbg_P0R_IPC_CTRL_02             },
	{ 0x250c ,N_FLD(dbg_P0R_IPC_CTRL_03)             ,"P0R_IPC_CTRL_03"               ,dbg_P0R_IPC_CTRL_03             },
	{ 0x2510 ,N_FLD(dbg_P0R_IPC_CTRL_04)             ,"P0R_IPC_CTRL_04"               ,dbg_P0R_IPC_CTRL_04             },
	{ 0x2514 ,N_FLD(dbg_P0R_IPC_CTRL_05)             ,"P0R_IPC_CTRL_05"               ,dbg_P0R_IPC_CTRL_05             },
	{ 0x2518 ,N_FLD(dbg_P0R_IPC_CTRL_06)             ,"P0R_IPC_CTRL_06"               ,dbg_P0R_IPC_CTRL_06             },
	{ 0x251c ,N_FLD(dbg_P0R_IPC_CTRL_07)             ,"P0R_IPC_CTRL_07"               ,dbg_P0R_IPC_CTRL_07             },
	{ 0x2520 ,N_FLD(dbg_P0R_IPC_CTRL_08)             ,"P0R_IPC_CTRL_08"               ,dbg_P0R_IPC_CTRL_08             },
	{ 0x2524 ,N_FLD(dbg_P0R_IPC_CTRL_09)             ,"P0R_IPC_CTRL_09"               ,dbg_P0R_IPC_CTRL_09             },
	{ 0x2528 ,N_FLD(dbg_P0R_IPC_CTRL_10)             ,"P0R_IPC_CTRL_10"               ,dbg_P0R_IPC_CTRL_10             },
	{ 0x252c ,N_FLD(dbg_P0R_IPC_CTRL_11)             ,"P0R_IPC_CTRL_11"               ,dbg_P0R_IPC_CTRL_11             },
	{ 0x2530 ,N_FLD(dbg_P0R_IPC_CTRL_12)             ,"P0R_IPC_CTRL_12"               ,dbg_P0R_IPC_CTRL_12             },
	{ 0x2534 ,N_FLD(dbg_P0R_IPC_CTRL_13)             ,"P0R_IPC_CTRL_13"               ,dbg_P0R_IPC_CTRL_13             },
	{ 0x2538 ,N_FLD(dbg_P0R_IPC_CTRL_14)             ,"P0R_IPC_CTRL_14"               ,dbg_P0R_IPC_CTRL_14             },
	{ 0x253c ,N_FLD(dbg_P0R_IPC_CTRL_15)             ,"P0R_IPC_CTRL_15"               ,dbg_P0R_IPC_CTRL_15             },
	{ 0x2540 ,N_FLD(dbg_P0R_IPC_CTRL_16)             ,"P0R_IPC_CTRL_16"               ,dbg_P0R_IPC_CTRL_16             },
	{ 0x2544 ,N_FLD(dbg_P0R_IPC_CTRL_17)             ,"P0R_IPC_CTRL_17"               ,dbg_P0R_IPC_CTRL_17             },
	{ 0x2548 ,N_FLD(dbg_P0R_IPC_CTRL_18)             ,"P0R_IPC_CTRL_18"               ,dbg_P0R_IPC_CTRL_18             },
	{ 0x254c ,N_FLD(dbg_P0R_IPC_CTRL_19)             ,"P0R_IPC_CTRL_19"               ,dbg_P0R_IPC_CTRL_19             },
	{ 0x2550 ,N_FLD(dbg_P0R_IPC_STATUS_00)           ,"P0R_IPC_STATUS_00"             ,dbg_P0R_IPC_STATUS_00           },
	{ 0x2554 ,N_FLD(dbg_P0R_IPC_STATUS_01)           ,"P0R_IPC_STATUS_01"             ,dbg_P0R_IPC_STATUS_01           },
	{ 0x2558 ,N_FLD(dbg_P0R_IPC_STATUS_02)           ,"P0R_IPC_STATUS_02"             ,dbg_P0R_IPC_STATUS_02           },
	{ 0x255c ,N_FLD(dbg_P0R_IPC_STATUS_03)           ,"P0R_IPC_STATUS_03"             ,dbg_P0R_IPC_STATUS_03           },
	{ 0x2580 ,N_FLD(dbg_P0R_VFLT_CTRL)               ,"P0R_VFLT_CTRL"                 ,dbg_P0R_VFLT_CTRL               },
	{ 0x2588 ,N_FLD(dbg_P0R_MNR_CTRL_00)             ,"P0R_MNR_CTRL_00"               ,dbg_P0R_MNR_CTRL_00             },
	{ 0x258c ,N_FLD(dbg_P0R_MNR_CTRL_01)             ,"P0R_MNR_CTRL_01"               ,dbg_P0R_MNR_CTRL_01             },
	{ 0x2590 ,N_FLD(dbg_P0R_MNR_CTRL_02)             ,"P0R_MNR_CTRL_02"               ,dbg_P0R_MNR_CTRL_02             },
	{ 0x2594 ,N_FLD(dbg_P0R_MNR_CTRL_03)             ,"P0R_MNR_CTRL_03"               ,dbg_P0R_MNR_CTRL_03             },
	{ 0x2598 ,N_FLD(dbg_P0R_MNR_CTRL_04)             ,"P0R_MNR_CTRL_04"               ,dbg_P0R_MNR_CTRL_04             },
	{ 0x259c ,N_FLD(dbg_P0R_MNR_CTRL_05)             ,"P0R_MNR_CTRL_05"               ,dbg_P0R_MNR_CTRL_05             },
	{ 0x25a0 ,N_FLD(dbg_P0R_MNR_CTRL_06)             ,"P0R_MNR_CTRL_06"               ,dbg_P0R_MNR_CTRL_06             },
	{ 0x25a8 ,N_FLD(dbg_P0R_VFILTER_01)              ,"P0R_VFILTER_01"                ,dbg_P0R_VFILTER_01              },
	{ 0x25ac ,N_FLD(dbg_P0R_BNR_DC_CTRL_00)          ,"P0R_BNR_DC_CTRL_00"            ,dbg_P0R_BNR_DC_CTRL_00          },
	{ 0x25b0 ,N_FLD(dbg_P0R_BNR_DC_CTRL_01)          ,"P0R_BNR_DC_CTRL_01"            ,dbg_P0R_BNR_DC_CTRL_01          },
	{ 0x25b4 ,N_FLD(dbg_P0R_BNR_DC_CTRL_02)          ,"P0R_BNR_DC_CTRL_02"            ,dbg_P0R_BNR_DC_CTRL_02          },
	{ 0x25b8 ,N_FLD(dbg_P0R_BNR_DC_CTRL_03)          ,"P0R_BNR_DC_CTRL_03"            ,dbg_P0R_BNR_DC_CTRL_03          },
	{ 0x25bc ,N_FLD(dbg_P0R_BNR_AC_CTRL_06)          ,"P0R_BNR_AC_CTRL_06"            ,dbg_P0R_BNR_AC_CTRL_06          },
	{ 0x25c0 ,N_FLD(dbg_P0R_BNR_AC_CTRL_00)          ,"P0R_BNR_AC_CTRL_00"            ,dbg_P0R_BNR_AC_CTRL_00          },
	{ 0x25c4 ,N_FLD(dbg_P0R_BNR_AC_CTRL_01)          ,"P0R_BNR_AC_CTRL_01"            ,dbg_P0R_BNR_AC_CTRL_01          },
	{ 0x25c8 ,N_FLD(dbg_P0R_BNR_AC_CTRL_02)          ,"P0R_BNR_AC_CTRL_02"            ,dbg_P0R_BNR_AC_CTRL_02          },
	{ 0x25cc ,N_FLD(dbg_P0R_BNR_AC_CTRL_03)          ,"P0R_BNR_AC_CTRL_03"            ,dbg_P0R_BNR_AC_CTRL_03          },
	{ 0x25d0 ,N_FLD(dbg_P0R_BNR_AC_CTRL_04)          ,"P0R_BNR_AC_CTRL_04"            ,dbg_P0R_BNR_AC_CTRL_04          },
	{ 0x25d4 ,N_FLD(dbg_P0R_BNR_AC_CTRL_05)          ,"P0R_BNR_AC_CTRL_05"            ,dbg_P0R_BNR_AC_CTRL_05          },
	{ 0x25d8 ,N_FLD(dbg_P0R_DNR_MAX_CTRL)            ,"P0R_DNR_MAX_CTRL"              ,dbg_P0R_DNR_MAX_CTRL            },
	{ 0x25dc ,N_FLD(dbg_P0R_DNR_DBAR_CTRL)           ,"P0R_DNR_DBAR_CTRL"             ,dbg_P0R_DNR_DBAR_CTRL           },
	{ 0x25e0 ,N_FLD(dbg_P0R_BNR_STAT_0)              ,"P0R_BNR_STAT_0"                ,dbg_P0R_BNR_STAT_0              },
	{ 0x25e4 ,N_FLD(dbg_P0R_DER_CTRL_0)              ,"P0R_DER_CTRL_0"                ,dbg_P0R_DER_CTRL_0              },
	{ 0x25e8 ,N_FLD(dbg_P0R_DER_CTRL_1)              ,"P0R_DER_CTRL_1"                ,dbg_P0R_DER_CTRL_1              },
	{ 0x25f0 ,N_FLD(dbg_P0R_IPC_CTRL_20)             ,"P0R_IPC_CTRL_20"               ,dbg_P0R_IPC_CTRL_20             },
	{ 0x25f4 ,N_FLD(dbg_P0R_IPC_CTRL_21)             ,"P0R_IPC_CTRL_21"               ,dbg_P0R_IPC_CTRL_21             },
	{ 0x25f8 ,0                                      ,"P0R_IPC_CTRL_22"               ,NULL                            },
	{ 0x25fc ,N_FLD(dbg_P0R_IPC_CTRL_23)             ,"P0R_IPC_CTRL_23"               ,dbg_P0R_IPC_CTRL_23             },
	{ 0x2600 ,N_FLD(dbg_P0R_IPC_CTRL_24)             ,"P0R_IPC_CTRL_24"               ,dbg_P0R_IPC_CTRL_24             },
	{ 0x2604 ,N_FLD(dbg_P0R_IPC_CTRL_25)             ,"P0R_IPC_CTRL_25"               ,dbg_P0R_IPC_CTRL_25             },
	{ 0x2608 ,N_FLD(dbg_P0R_IPC_CTRL_26)             ,"P0R_IPC_CTRL_26"               ,dbg_P0R_IPC_CTRL_26             },
	{ 0x260c ,N_FLD(dbg_P0R_IPC_CTRL_27)             ,"P0R_IPC_CTRL_27"               ,dbg_P0R_IPC_CTRL_27             },
	{ 0x2640 ,N_FLD(dbg_P0R_TPD_CTRL_00)             ,"P0R_TPD_CTRL_00"               ,dbg_P0R_TPD_CTRL_00             },
	{ 0x2670 ,N_FLD(dbg_P0R_BBD_CTRL_00)             ,"P0R_BBD_CTRL_00"               ,dbg_P0R_BBD_CTRL_00             },
	{ 0x2674 ,N_FLD(dbg_P0R_BBD_CTRL_01)             ,"P0R_BBD_CTRL_01"               ,dbg_P0R_BBD_CTRL_01             },
	{ 0x2678 ,N_FLD(dbg_P0R_BBD_CTRL_02)             ,"P0R_BBD_CTRL_02"               ,dbg_P0R_BBD_CTRL_02             },
	{ 0x267c ,N_FLD(dbg_P0R_BBD_STAT_00)             ,"P0R_BBD_STAT_00"               ,dbg_P0R_BBD_STAT_00             },
	{ 0x2680 ,N_FLD(dbg_P0R_BBD_STAT_01)             ,"P0R_BBD_STAT_01"               ,dbg_P0R_BBD_STAT_01             },
	{ 0x2684 ,0                                      ,"P0R_APL_STAT_00"               ,NULL                            },
	{ 0x2690 ,N_FLD(dbg_P0R_CTI_CTRL_00)             ,"P0R_CTI_CTRL_00"               ,dbg_P0R_CTI_CTRL_00             },
	{ 0 , } // end marker
};

#endif
