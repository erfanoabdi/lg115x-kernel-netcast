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

#ifndef _DBG_CVI_h
#define _DBG_CVI_h

/*----------------------------------------
	0x0100 CVA_TOP_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_TOP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"scan_type"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"field_gen_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,3  ,"auto_field_gen"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"data_bit_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"chroma_sampling"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"aspect_ratio"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"yc_delay_mode_r"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"yc_delay_mode_b"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"yc_delay_mode_g"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"auto_sync_polarity"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"manual_sync_polarity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"adc_cut_direction"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"adc_bit_sel"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"br_port_swap"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"r_port_swap"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"b_port_swap"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"g_port_swap"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"bit_numbering_lsb2"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"data_en_mode"                    },
};

/*----------------------------------------
	0x0104 CVA_OFFSET_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_OFFSET_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"offset_h"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"offset_v"                        },
};

/*----------------------------------------
	0x0108 CVA_SIZE_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"size_h"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"size_v"                          },
};

/*----------------------------------------
	0x010c CVA_INT_SYNC_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_INT_SYNC_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"res_hsync"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"res_hfp"                         },
};

/*----------------------------------------
	0x0110 CVA_INT_SYNC_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_INT_SYNC_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"res_vfp"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"res_vsync"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"res_field_add_line"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"res_field_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"res_sync_sel"                    },
};

/*----------------------------------------
	0x0114 CVA_DIG_FILT_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_DIG_FILT_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_coefficient1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_coefficient0"                },
};

/*----------------------------------------
	0x0118 CVA_DIG_FILT_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_DIG_FILT_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_coefficient3"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_coefficient2"                },
};

/*----------------------------------------
	0x011c CVA_DIG_FILT_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_DIG_FILT_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_coefficient5"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_coefficient4"                },
};

/*----------------------------------------
	0x0120 CVA_DIG_FILT_CTRL3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_DIG_FILT_CTRL3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"fir_sample_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"fir_coeff_load"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"fir_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"fir_y_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,29 ,"fir_sampling_rate"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"fir_c_en"                        },
};

/*----------------------------------------
	0x0124 CVA_CSC_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient0"                },
};

/*----------------------------------------
	0x0128 CVA_CSC_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient3"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient2"                },
};

/*----------------------------------------
	0x012c CVA_CSC_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient5"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient4"                },
};

/*----------------------------------------
	0x0130 CVA_CSC_CTRL3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient7"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient6"                },
};

/*----------------------------------------
	0x0134 CVA_CSC_CTRL4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"csc_offset0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient8"                },
};

/*----------------------------------------
	0x0138 CVA_CSC_CTRL5
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"csc_offset2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"csc_offset1"                     },
};

/*----------------------------------------
	0x013c CVA_CSC_CTRL6
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"csc_offset4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"csc_offset3"                     },
};

/*----------------------------------------
	0x0140 CVA_CSC_CTRL7
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CSC_CTRL7[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"csc_coeff_load"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"csc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"csc_msb_4b_only_mode"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"csc_offset5"                     },
};

/*----------------------------------------
	0x0144 CVA_MISC_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_MISC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"pattern_type"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pattern_csc"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"pattern_detail"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update_pulse"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"field_fix_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"auto_novalid_on"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"write_inhibit"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"sim_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"black_off"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"field_edge"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"ha_gen"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,17 ,"xsize_divide"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"update_position"                 },
};

/*----------------------------------------
	0x0148 CVA_OFFSET_READ
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_OFFSET_READ[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"hoffset_read"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"voffset_read"                    },
};

/*----------------------------------------
	0x014c CVA_PRE3D_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PRE3D_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pre3d_sync_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pre3d_sync_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pre3d_field_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"pre3d_frame_lr_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"pre3d_mid_vsync_bypass"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pre3d_field_bypass"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pre3d_active_line_num"           },
};

/*----------------------------------------
	0x0150 CVA_PRE3D_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PRE3D_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pre3d_active_space1_line_num"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pre3d_active_space2_line_num"    },
};

/*----------------------------------------
	0x0154 CVA_PRE3D_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PRE3D_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pre3d_front_porch_line_num"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pre3d_sync_line_num"             },
};

/*----------------------------------------
	0x0158 CVA_SIZE_STATUS1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_STATUS1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sd_hoffset_indurance_read"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"sd_voffset_indurance_read"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sd_hsync_fault_flag_read"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"sd_vsync_fault_flag_read"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"h_sync_polarity"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"v_sync_polarity"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"field_signal"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"hsync_at_vsync_fall"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"outfield_at_vactive_fall"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"hoffset_over"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"v_offset_over"                   },
};

/*----------------------------------------
	0x015c CVA_SIZE_STATUS2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_STATUS2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"de_line_size"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"de_line_count"                   },
};

/*----------------------------------------
	0x0160 CVA_SIZE_STATUS3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_STATUS3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hd_sync_size"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hd_line_size"                    },
};

/*----------------------------------------
	0x0164 CVA_SIZE_STATUS4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_STATUS4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"vd_sync_count"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"vd_line_count"                   },
};

/*----------------------------------------
	0x0168 CVA_PIX_SUM_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PIX_SUM_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"start_pos_x"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"end_pos_x"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pix_sum_enable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,29 ,"field_selection"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"debug_enable"                    },
};

/*----------------------------------------
	0x016c CVA_PIX_SUM_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PIX_SUM_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"start_pos_y"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"end_pos_y"                       },
};

/*----------------------------------------
	0x0170 CVA_PIX_SUM_STATUS0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PIX_SUM_STATUS0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pix_sum_g"                       },
};

/*----------------------------------------
	0x0174 CVA_PIX_SUM_STATUS1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PIX_SUM_STATUS1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pix_sum_b"                       },
};

/*----------------------------------------
	0x0178 CVA_PIX_SUM_STATUS2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PIX_SUM_STATUS2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pix_sum_r"                       },
};

/*----------------------------------------
	0x017c CVA_SYNC_FIL_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SYNC_FIL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hsync_fil_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"hsync_counter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vsync_fil_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"vsync_counter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"de_fil_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"de_counter_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"field_fil_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"field_counter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"line_count_sel"                  },
};

/*----------------------------------------
	0x0180 CVA_SYNC_FIL_STATUS
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SYNC_FIL_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hsync_coutner"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vsync_counter"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"de_counter"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"field_counter"                   },
};

/*----------------------------------------
	0x0184 CVA_CTI_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_CTI_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"master_enable"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cti_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"usm_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"repeat_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cti_gain"                        },
};

/*----------------------------------------
	0x0190 CVA_SYNC_REPEAT_CTRL
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x0194 CVA_SYNC_REPEAT_SIZE0
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x0198 CVA_SYNC_REPEAT_SIZE1
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x019c CVA_SYNC_REPEAT_SIZE2
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x01a0 CVA_SYNC_REPEAT_SIZE3
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x01a4 CVA_SYNC_REPEAT_SIZE4
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x01a8 CVA_SYNC_REPEAT_SIZE5
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x01ac CVA_DIG_FILT_CTRL4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_DIG_FILT_CTRL4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_c_coefficient1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_c_coefficient0"              },
};

/*----------------------------------------
	0x01b0 CVA_DIG_FILT_CTRL5
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_DIG_FILT_CTRL5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_c_coefficient3"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_c_coefficient2"              },
};

/*----------------------------------------
	0x01b4 CVA_DIG_FILT_CTRL6
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_DIG_FILT_CTRL6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_c_coefficient5"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_c_coefficient4"              },
};

/*----------------------------------------
	0x01c0 CVA_SIZE_DETECT_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_DETECT_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"sd_vd_range"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"sd_ext_range"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"intr_mask_node"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"intr_mask_nohsync"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"intrl_mask_novsync"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"intr_mask_abnormal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"intr_mask_invalid"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"intr_mask_de"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"intr_mask_hsync"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"intr_mask_vsync"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"intr_mask_normal"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"intr_mask_valid"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"sd_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"sd_frame_cnt"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"sd_novald_duration"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"sd_one_field"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"intr_mask_ext_diff"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"intr_mask_vd_diff"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"nosig_duration_de"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"nosig_duration_hsync"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"nosig_duration_vsync"            },
};

/*----------------------------------------
	0x01c4 CVA_SIZE_DETECT_READ
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_DETECT_READ[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"line_num_read"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"line_width_read"                 },
};

/*----------------------------------------
	0x01c8 CVA_SIZE_STATUS0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_STATUS0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"current_line_number_read"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"de_signal_detect"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"hsync_signal_detect"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"vsync_signal_detect"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"source_valid"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"sd_line_num"                     },
};

/*----------------------------------------
	0x01cc CVA_SIZE_STATUS5
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_STATUS5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"sd_2field_size"                  },
};

/*----------------------------------------
	0x01d0 CVA_SIZE_STATUS6
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_STATUS6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"diff_vd_vcnt"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"diff_ext_vcnt"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"vd_intr"                         },
};

/*----------------------------------------
	0x01d4 CVA_SIZE_DETECT_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_DETECT_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"abnormal0_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"abnormal1_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"abnormal2_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"abnormal3_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"abnormal4_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"abnormal5_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"abnormal6_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"abnormal7_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"abnormal0_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"abnormal1_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"abnormal2_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"abnormal3_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"abnormal4_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"abnormal5_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"abnormal6_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"abnormal7_flag"                  },
};

/*----------------------------------------
	0x01d8 CVA_SIZE_DETECT_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_SIZE_DETECT_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"abnormal_in_h"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"abnormal_out_h"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"abnormal_in_v"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"abnormal_out_v"                  },
};

/*----------------------------------------
	0x01dc CVA_PSEUDO_SYNC_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PSEUDO_SYNC_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vsync_pesudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"hsync_pesudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vactive_pesudo_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"hactive_pesudo_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"field_pesudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"y_pseudo_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cb_psuedo_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cr_psuedo_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"valid_pseudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"auto_pseudo_sync_en"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"pseudo_sync_ctrl_en"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"pseudo_y_data_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"pseudo_cb_data_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pseudo_cr_data_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"pseudo_y"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"pseudo_cb"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"pseudo_cr"                       },
};

/*----------------------------------------
	0x01e0 CVA_PSEUDO_SYNC_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PSEUDO_SYNC_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"pseudo_hfp"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"pseudo_hsync"                    },
};

/*----------------------------------------
	0x01e4 CVA_PSEUDO_SYNC_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PSEUDO_SYNC_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"pseudo_hblk"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"pseudo_hn"                       },
};

/*----------------------------------------
	0x01e8 CVA_PSEUDO_SYNC_CTRL3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PSEUDO_SYNC_CTRL3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pseudo_vfp"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pseudo_vsync"                    },
};

/*----------------------------------------
	0x01ec CVA_PSEUDO_SYNC_CTRL4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PSEUDO_SYNC_CTRL4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pseudo_vblk"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pseudo_vn"                       },
};

/*----------------------------------------
	0x01f0 CVA_PREADY_TIMER
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVA_PREADY_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"timer_count"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"timer_enable"                    },
};

/*----------------------------------------
	0x0200 CVB_TOP_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_TOP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"scan_type"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"field_gen_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,3  ,"auto_field_gen"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"data_bit_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"chroma_sampling"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"aspect_ratio"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"yc_delay_mode_r"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"yc_delay_mode_b"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"yc_delay_mode_g"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"auto_sync_polarity"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"manual_sync_polarity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"adc_cut_direction"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"adc_bit_sel"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"br_port_swap"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"r_port_swap"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"b_port_swap"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"g_port_swap"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"bit_numbering_lsb2"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"data_en_mode"                    },
};

/*----------------------------------------
	0x0204 CVB_OFFSET_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_OFFSET_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"offset_h"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"offset_v"                        },
};

/*----------------------------------------
	0x0208 CVB_SIZE_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"size_h"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"size_v"                          },
};

/*----------------------------------------
	0x020c CVB_INT_SYNC_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_INT_SYNC_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"res_hsync"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"res_hfp"                         },
};

/*----------------------------------------
	0x0210 CVB_INT_SYNC_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_INT_SYNC_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"res_vfp"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"res_vsync"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,13 ,"res_field_add_line"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"res_field_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"res_sync_sel"                    },
};

/*----------------------------------------
	0x0214 CVB_DIG_FILT_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_DIG_FILT_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_coefficient1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_coefficient0"                },
};

/*----------------------------------------
	0x0218 CVB_DIG_FILT_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_DIG_FILT_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_coefficient3"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_coefficient2"                },
};

/*----------------------------------------
	0x021c CVB_DIG_FILT_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_DIG_FILT_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_coefficient5"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_coefficient4"                },
};

/*----------------------------------------
	0x0220 CVB_DIG_FILT_CTRL3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_DIG_FILT_CTRL3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"fir_sample_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"fir_coeff_load"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"fir_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"fir_y_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,29 ,"fir_sampling_rate"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"fir_c_en"                        },
};

/*----------------------------------------
	0x0224 CVB_CSC_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient0"                },
};

/*----------------------------------------
	0x0228 CVB_CSC_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient3"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient2"                },
};

/*----------------------------------------
	0x022c CVB_CSC_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient5"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient4"                },
};

/*----------------------------------------
	0x0230 CVB_CSC_CTRL3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"csc_coefficient7"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient6"                },
};

/*----------------------------------------
	0x0234 CVB_CSC_CTRL4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"csc_offset0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"csc_coefficient8"                },
};

/*----------------------------------------
	0x0238 CVB_CSC_CTRL5
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"csc_offset2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"csc_offset1"                     },
};

/*----------------------------------------
	0x023c CVB_CSC_CTRL6
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"csc_offset4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"csc_offset3"                     },
};

/*----------------------------------------
	0x0240 CVB_CSC_CTRL7
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CSC_CTRL7[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"csc_coeff_load"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"csc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"csc_msb_4b_only_mode"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"csc_offset5"                     },
};

/*----------------------------------------
	0x0244 CVB_MISC_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_MISC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"pattern_type"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pattern_csc"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"pattern_detail"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"update_pulse"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"field_fix_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"auto_novalid_on"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"write_inhibit"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"sim_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"black_off"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"field_edge"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"ha_gen"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,17 ,"xsize_divide"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"update_position"                 },
};

/*----------------------------------------
	0x0248 CVB_OFFSET_READ
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_OFFSET_READ[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"hoffset_read"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"voffset_read"                    },
};

/*----------------------------------------
	0x024c CVB_PRE3D_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PRE3D_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pre3d_sync_enable"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pre3d_sync_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pre3d_field_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"pre3d_frame_lr_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"pre3d_mid_vsync_bypass"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pre3d_field_bypass"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pre3d_active_line_num"           },
};

/*----------------------------------------
	0x0250 CVB_PRE3D_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PRE3D_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pre3d_active_space1_line_num"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pre3d_active_space2_line_num"    },
};

/*----------------------------------------
	0x0254 CVB_PRE3D_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PRE3D_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pre3d_front_porch_line_num"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pre3d_sync_line_num"             },
};

/*----------------------------------------
	0x0258 CVB_SIZE_STATUS1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_STATUS1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sd_hoffset_indurance_read"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"sd_voffset_indurance_read"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sd_hsync_fault_flag_read"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"sd_vsync_fault_flag_read"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"h_sync_polarity"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"v_sync_polarity"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"field_signal"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"hsync_at_vsync_fall"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"outfield_at_vactive_fall"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"hoffset_over"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"v_offset_over"                   },
};

/*----------------------------------------
	0x025c CVB_SIZE_STATUS2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_STATUS2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"de_line_size"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"de_line_count"                   },
};

/*----------------------------------------
	0x0260 CVB_SIZE_STATUS3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_STATUS3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hd_sync_size"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hd_line_size"                    },
};

/*----------------------------------------
	0x0264 CVB_SIZE_STATUS4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_STATUS4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"vd_sync_count"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"vd_line_count"                   },
};

/*----------------------------------------
	0x0268 CVB_PIX_SUM_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PIX_SUM_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"start_pos_x"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"end_pos_x"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pix_sum_enable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,29 ,"field_selection"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"debug_enable"                    },
};

/*----------------------------------------
	0x026c CVB_PIX_SUM_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PIX_SUM_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"start_pos_y"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"end_pos_y"                       },
};

/*----------------------------------------
	0x0270 CVB_PIX_SUM_STATUS0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PIX_SUM_STATUS0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pix_sum_g"                       },
};

/*----------------------------------------
	0x0274 CVB_PIX_SUM_STATUS1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PIX_SUM_STATUS1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pix_sum_b"                       },
};

/*----------------------------------------
	0x0278 CVB_PIX_SUM_STATUS2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PIX_SUM_STATUS2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pix_sum_r"                       },
};

/*----------------------------------------
	0x027c CVB_SYNC_FIL_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SYNC_FIL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hsync_fil_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"hsync_counter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vsync_fil_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"vsync_counter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"de_fil_en"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"de_counter_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"field_fil_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"field_counter_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"line_count_sel"                  },
};

/*----------------------------------------
	0x0280 CVB_SYNC_FIL_STATUS
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SYNC_FIL_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hsync_coutner"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vsync_counter"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"de_counter"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"field_counter"                   },
};

/*----------------------------------------
	0x0284 CVB_CTI_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_CTI_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"master_enable"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cti_enable"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"usm_mode"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"repeat_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cti_gain"                        },
};

/*----------------------------------------
	0x0290 CVB_SYNC_REPEAT_CTRL
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x0294 CVB_SYNC_REPEAT_SIZE0
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x0298 CVB_SYNC_REPEAT_SIZE1
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x029c CVB_SYNC_REPEAT_SIZE2
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x02a0 CVB_SYNC_REPEAT_SIZE3
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x02a4 CVB_SYNC_REPEAT_SIZE4
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x02a8 CVB_SYNC_REPEAT_SIZE5
----------------------------------------*/
/* no field */

/*----------------------------------------
	0x02ac CVB_DIG_FILT_CTRL4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_DIG_FILT_CTRL4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_c_coefficient1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_c_coefficient0"              },
};

/*----------------------------------------
	0x02b0 CVB_DIG_FILT_CTRL5
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_DIG_FILT_CTRL5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_c_coefficient3"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_c_coefficient2"              },
};

/*----------------------------------------
	0x02b4 CVB_DIG_FILT_CTRL6
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_DIG_FILT_CTRL6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"fir_c_coefficient5"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"fir_c_coefficient4"              },
};

/*----------------------------------------
	0x02c0 CVB_SIZE_DETECT_CTRL
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_DETECT_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"sd_vd_range"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"sd_ext_range"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"intr_mask_node"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"intr_mask_nohsync"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"intrl_mask_novsync"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"intr_mask_abnormal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"intr_mask_invalid"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"intr_mask_de"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"intr_mask_hsync"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"intr_mask_vsync"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"intr_mask_normal"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"intr_mask_valid"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"sd_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"sd_frame_cnt"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"sd_novald_duration"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"sd_one_field"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"intr_mask_ext_diff"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"intr_mask_vd_diff"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"nosig_duration_de"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"nosig_duration_hsync"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"nosig_duration_vsync"            },
};

/*----------------------------------------
	0x02c4 CVB_SIZE_DETECT_READ
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_DETECT_READ[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"line_num_read"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"line_width_read"                 },
};

/*----------------------------------------
	0x02c8 CVB_SIZE_STATUS0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_STATUS0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"current_line_number_read"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"de_signal_detect"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"hsync_signal_detect"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"vsync_signal_detect"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"source_valid"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"sd_line_num"                     },
};

/*----------------------------------------
	0x02cc CVB_SIZE_STATUS5
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_STATUS5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"sd_2field_size"                  },
};

/*----------------------------------------
	0x02d0 CVB_SIZE_STATUS6
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_STATUS6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"diff_vd_vcnt"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"diff_ext_vcnt"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"vd_intr"                         },
};

/*----------------------------------------
	0x02d4 CVB_SIZE_DETECT_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_DETECT_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"abnormal0_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"abnormal1_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"abnormal2_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"abnormal3_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"abnormal4_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"abnormal5_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"abnormal6_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"abnormal7_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"abnormal0_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"abnormal1_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"abnormal2_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"abnormal3_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"abnormal4_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"abnormal5_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"abnormal6_flag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"abnormal7_flag"                  },
};

/*----------------------------------------
	0x02d8 CVB_SIZE_DETECT_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_SIZE_DETECT_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"abnormal_in_h"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"abnormal_out_h"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"abnormal_in_v"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"abnormal_out_v"                  },
};

/*----------------------------------------
	0x02dc CVB_PSEUDO_SYNC_CTRL0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PSEUDO_SYNC_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vsync_pesudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"hsync_pesudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vactive_pesudo_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"hactive_pesudo_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"field_pesudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"y_pseudo_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cb_psuedo_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cr_psuedo_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"valid_pseudo_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"auto_pseudo_sync_en"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"pseudo_sync_ctrl_en"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"pseudo_y_data_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"pseudo_cb_data_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pseudo_cr_data_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"pseudo_y"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"pseudo_cb"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"pseudo_cr"                       },
};

/*----------------------------------------
	0x02e0 CVB_PSEUDO_SYNC_CTRL1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PSEUDO_SYNC_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"pseudo_hfp"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"pseudo_hsync"                    },
};

/*----------------------------------------
	0x02e4 CVB_PSEUDO_SYNC_CTRL2
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PSEUDO_SYNC_CTRL2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"pseudo_hblk"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"pseudo_hn"                       },
};

/*----------------------------------------
	0x02e8 CVB_PSEUDO_SYNC_CTRL3
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PSEUDO_SYNC_CTRL3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pseudo_vfp"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pseudo_vsync"                    },
};

/*----------------------------------------
	0x02ec CVB_PSEUDO_SYNC_CTRL4
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PSEUDO_SYNC_CTRL4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"pseudo_vblk"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"pseudo_vn"                       },
};

/*----------------------------------------
	0x02f0 CVB_PREADY_TIMER
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVB_PREADY_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"timer_count"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"timer_enable"                    },
};

DBG_REG_T gDbgRegCVI[] = {
	{ 0x0100 ,N_FLD(dbg_CVA_TOP_CTRL)                ,"CVA_TOP_CTRL"                  ,dbg_CVA_TOP_CTRL                },
	{ 0x0104 ,N_FLD(dbg_CVA_OFFSET_CTRL)             ,"CVA_OFFSET_CTRL"               ,dbg_CVA_OFFSET_CTRL             },
	{ 0x0108 ,N_FLD(dbg_CVA_SIZE_CTRL)               ,"CVA_SIZE_CTRL"                 ,dbg_CVA_SIZE_CTRL               },
	{ 0x010c ,N_FLD(dbg_CVA_INT_SYNC_CTRL0)          ,"CVA_INT_SYNC_CTRL0"            ,dbg_CVA_INT_SYNC_CTRL0          },
	{ 0x0110 ,N_FLD(dbg_CVA_INT_SYNC_CTRL1)          ,"CVA_INT_SYNC_CTRL1"            ,dbg_CVA_INT_SYNC_CTRL1          },
	{ 0x0114 ,N_FLD(dbg_CVA_DIG_FILT_CTRL0)          ,"CVA_DIG_FILT_CTRL0"            ,dbg_CVA_DIG_FILT_CTRL0          },
	{ 0x0118 ,N_FLD(dbg_CVA_DIG_FILT_CTRL1)          ,"CVA_DIG_FILT_CTRL1"            ,dbg_CVA_DIG_FILT_CTRL1          },
	{ 0x011c ,N_FLD(dbg_CVA_DIG_FILT_CTRL2)          ,"CVA_DIG_FILT_CTRL2"            ,dbg_CVA_DIG_FILT_CTRL2          },
	{ 0x0120 ,N_FLD(dbg_CVA_DIG_FILT_CTRL3)          ,"CVA_DIG_FILT_CTRL3"            ,dbg_CVA_DIG_FILT_CTRL3          },
	{ 0x0124 ,N_FLD(dbg_CVA_CSC_CTRL0)               ,"CVA_CSC_CTRL0"                 ,dbg_CVA_CSC_CTRL0               },
	{ 0x0128 ,N_FLD(dbg_CVA_CSC_CTRL1)               ,"CVA_CSC_CTRL1"                 ,dbg_CVA_CSC_CTRL1               },
	{ 0x012c ,N_FLD(dbg_CVA_CSC_CTRL2)               ,"CVA_CSC_CTRL2"                 ,dbg_CVA_CSC_CTRL2               },
	{ 0x0130 ,N_FLD(dbg_CVA_CSC_CTRL3)               ,"CVA_CSC_CTRL3"                 ,dbg_CVA_CSC_CTRL3               },
	{ 0x0134 ,N_FLD(dbg_CVA_CSC_CTRL4)               ,"CVA_CSC_CTRL4"                 ,dbg_CVA_CSC_CTRL4               },
	{ 0x0138 ,N_FLD(dbg_CVA_CSC_CTRL5)               ,"CVA_CSC_CTRL5"                 ,dbg_CVA_CSC_CTRL5               },
	{ 0x013c ,N_FLD(dbg_CVA_CSC_CTRL6)               ,"CVA_CSC_CTRL6"                 ,dbg_CVA_CSC_CTRL6               },
	{ 0x0140 ,N_FLD(dbg_CVA_CSC_CTRL7)               ,"CVA_CSC_CTRL7"                 ,dbg_CVA_CSC_CTRL7               },
	{ 0x0144 ,N_FLD(dbg_CVA_MISC_CTRL)               ,"CVA_MISC_CTRL"                 ,dbg_CVA_MISC_CTRL               },
	{ 0x0148 ,N_FLD(dbg_CVA_OFFSET_READ)             ,"CVA_OFFSET_READ"               ,dbg_CVA_OFFSET_READ             },
	{ 0x014c ,N_FLD(dbg_CVA_PRE3D_CTRL0)             ,"CVA_PRE3D_CTRL0"               ,dbg_CVA_PRE3D_CTRL0             },
	{ 0x0150 ,N_FLD(dbg_CVA_PRE3D_CTRL1)             ,"CVA_PRE3D_CTRL1"               ,dbg_CVA_PRE3D_CTRL1             },
	{ 0x0154 ,N_FLD(dbg_CVA_PRE3D_CTRL2)             ,"CVA_PRE3D_CTRL2"               ,dbg_CVA_PRE3D_CTRL2             },
	{ 0x0158 ,N_FLD(dbg_CVA_SIZE_STATUS1)            ,"CVA_SIZE_STATUS1"              ,dbg_CVA_SIZE_STATUS1            },
	{ 0x015c ,N_FLD(dbg_CVA_SIZE_STATUS2)            ,"CVA_SIZE_STATUS2"              ,dbg_CVA_SIZE_STATUS2            },
	{ 0x0160 ,N_FLD(dbg_CVA_SIZE_STATUS3)            ,"CVA_SIZE_STATUS3"              ,dbg_CVA_SIZE_STATUS3            },
	{ 0x0164 ,N_FLD(dbg_CVA_SIZE_STATUS4)            ,"CVA_SIZE_STATUS4"              ,dbg_CVA_SIZE_STATUS4            },
	{ 0x0168 ,N_FLD(dbg_CVA_PIX_SUM_CTRL0)           ,"CVA_PIX_SUM_CTRL0"             ,dbg_CVA_PIX_SUM_CTRL0           },
	{ 0x016c ,N_FLD(dbg_CVA_PIX_SUM_CTRL1)           ,"CVA_PIX_SUM_CTRL1"             ,dbg_CVA_PIX_SUM_CTRL1           },
	{ 0x0170 ,N_FLD(dbg_CVA_PIX_SUM_STATUS0)         ,"CVA_PIX_SUM_STATUS0"           ,dbg_CVA_PIX_SUM_STATUS0         },
	{ 0x0174 ,N_FLD(dbg_CVA_PIX_SUM_STATUS1)         ,"CVA_PIX_SUM_STATUS1"           ,dbg_CVA_PIX_SUM_STATUS1         },
	{ 0x0178 ,N_FLD(dbg_CVA_PIX_SUM_STATUS2)         ,"CVA_PIX_SUM_STATUS2"           ,dbg_CVA_PIX_SUM_STATUS2         },
	{ 0x017c ,N_FLD(dbg_CVA_SYNC_FIL_CTRL)           ,"CVA_SYNC_FIL_CTRL"             ,dbg_CVA_SYNC_FIL_CTRL           },
	{ 0x0180 ,N_FLD(dbg_CVA_SYNC_FIL_STATUS)         ,"CVA_SYNC_FIL_STATUS"           ,dbg_CVA_SYNC_FIL_STATUS         },
	{ 0x0184 ,N_FLD(dbg_CVA_CTI_CTRL)                ,"CVA_CTI_CTRL"                  ,dbg_CVA_CTI_CTRL                },
	{ 0x0190 ,0                                      ,"CVA_SYNC_REPEAT_CTRL"          ,NULL                            },
	{ 0x0194 ,0                                      ,"CVA_SYNC_REPEAT_SIZE0"         ,NULL                            },
	{ 0x0198 ,0                                      ,"CVA_SYNC_REPEAT_SIZE1"         ,NULL                            },
	{ 0x019c ,0                                      ,"CVA_SYNC_REPEAT_SIZE2"         ,NULL                            },
	{ 0x01a0 ,0                                      ,"CVA_SYNC_REPEAT_SIZE3"         ,NULL                            },
	{ 0x01a4 ,0                                      ,"CVA_SYNC_REPEAT_SIZE4"         ,NULL                            },
	{ 0x01a8 ,0                                      ,"CVA_SYNC_REPEAT_SIZE5"         ,NULL                            },
	{ 0x01ac ,N_FLD(dbg_CVA_DIG_FILT_CTRL4)          ,"CVA_DIG_FILT_CTRL4"            ,dbg_CVA_DIG_FILT_CTRL4          },
	{ 0x01b0 ,N_FLD(dbg_CVA_DIG_FILT_CTRL5)          ,"CVA_DIG_FILT_CTRL5"            ,dbg_CVA_DIG_FILT_CTRL5          },
	{ 0x01b4 ,N_FLD(dbg_CVA_DIG_FILT_CTRL6)          ,"CVA_DIG_FILT_CTRL6"            ,dbg_CVA_DIG_FILT_CTRL6          },
	{ 0x01c0 ,N_FLD(dbg_CVA_SIZE_DETECT_CTRL)        ,"CVA_SIZE_DETECT_CTRL"          ,dbg_CVA_SIZE_DETECT_CTRL        },
	{ 0x01c4 ,N_FLD(dbg_CVA_SIZE_DETECT_READ)        ,"CVA_SIZE_DETECT_READ"          ,dbg_CVA_SIZE_DETECT_READ        },
	{ 0x01c8 ,N_FLD(dbg_CVA_SIZE_STATUS0)            ,"CVA_SIZE_STATUS0"              ,dbg_CVA_SIZE_STATUS0            },
	{ 0x01cc ,N_FLD(dbg_CVA_SIZE_STATUS5)            ,"CVA_SIZE_STATUS5"              ,dbg_CVA_SIZE_STATUS5            },
	{ 0x01d0 ,N_FLD(dbg_CVA_SIZE_STATUS6)            ,"CVA_SIZE_STATUS6"              ,dbg_CVA_SIZE_STATUS6            },
	{ 0x01d4 ,N_FLD(dbg_CVA_SIZE_DETECT_CTRL1)       ,"CVA_SIZE_DETECT_CTRL1"         ,dbg_CVA_SIZE_DETECT_CTRL1       },
	{ 0x01d8 ,N_FLD(dbg_CVA_SIZE_DETECT_CTRL2)       ,"CVA_SIZE_DETECT_CTRL2"         ,dbg_CVA_SIZE_DETECT_CTRL2       },
	{ 0x01dc ,N_FLD(dbg_CVA_PSEUDO_SYNC_CTRL0)       ,"CVA_PSEUDO_SYNC_CTRL0"         ,dbg_CVA_PSEUDO_SYNC_CTRL0       },
	{ 0x01e0 ,N_FLD(dbg_CVA_PSEUDO_SYNC_CTRL1)       ,"CVA_PSEUDO_SYNC_CTRL1"         ,dbg_CVA_PSEUDO_SYNC_CTRL1       },
	{ 0x01e4 ,N_FLD(dbg_CVA_PSEUDO_SYNC_CTRL2)       ,"CVA_PSEUDO_SYNC_CTRL2"         ,dbg_CVA_PSEUDO_SYNC_CTRL2       },
	{ 0x01e8 ,N_FLD(dbg_CVA_PSEUDO_SYNC_CTRL3)       ,"CVA_PSEUDO_SYNC_CTRL3"         ,dbg_CVA_PSEUDO_SYNC_CTRL3       },
	{ 0x01ec ,N_FLD(dbg_CVA_PSEUDO_SYNC_CTRL4)       ,"CVA_PSEUDO_SYNC_CTRL4"         ,dbg_CVA_PSEUDO_SYNC_CTRL4       },
	{ 0x01f0 ,N_FLD(dbg_CVA_PREADY_TIMER)            ,"CVA_PREADY_TIMER"              ,dbg_CVA_PREADY_TIMER            },
	{ 0x0200 ,N_FLD(dbg_CVB_TOP_CTRL)                ,"CVB_TOP_CTRL"                  ,dbg_CVB_TOP_CTRL                },
	{ 0x0204 ,N_FLD(dbg_CVB_OFFSET_CTRL)             ,"CVB_OFFSET_CTRL"               ,dbg_CVB_OFFSET_CTRL             },
	{ 0x0208 ,N_FLD(dbg_CVB_SIZE_CTRL)               ,"CVB_SIZE_CTRL"                 ,dbg_CVB_SIZE_CTRL               },
	{ 0x020c ,N_FLD(dbg_CVB_INT_SYNC_CTRL0)          ,"CVB_INT_SYNC_CTRL0"            ,dbg_CVB_INT_SYNC_CTRL0          },
	{ 0x0210 ,N_FLD(dbg_CVB_INT_SYNC_CTRL1)          ,"CVB_INT_SYNC_CTRL1"            ,dbg_CVB_INT_SYNC_CTRL1          },
	{ 0x0214 ,N_FLD(dbg_CVB_DIG_FILT_CTRL0)          ,"CVB_DIG_FILT_CTRL0"            ,dbg_CVB_DIG_FILT_CTRL0          },
	{ 0x0218 ,N_FLD(dbg_CVB_DIG_FILT_CTRL1)          ,"CVB_DIG_FILT_CTRL1"            ,dbg_CVB_DIG_FILT_CTRL1          },
	{ 0x021c ,N_FLD(dbg_CVB_DIG_FILT_CTRL2)          ,"CVB_DIG_FILT_CTRL2"            ,dbg_CVB_DIG_FILT_CTRL2          },
	{ 0x0220 ,N_FLD(dbg_CVB_DIG_FILT_CTRL3)          ,"CVB_DIG_FILT_CTRL3"            ,dbg_CVB_DIG_FILT_CTRL3          },
	{ 0x0224 ,N_FLD(dbg_CVB_CSC_CTRL0)               ,"CVB_CSC_CTRL0"                 ,dbg_CVB_CSC_CTRL0               },
	{ 0x0228 ,N_FLD(dbg_CVB_CSC_CTRL1)               ,"CVB_CSC_CTRL1"                 ,dbg_CVB_CSC_CTRL1               },
	{ 0x022c ,N_FLD(dbg_CVB_CSC_CTRL2)               ,"CVB_CSC_CTRL2"                 ,dbg_CVB_CSC_CTRL2               },
	{ 0x0230 ,N_FLD(dbg_CVB_CSC_CTRL3)               ,"CVB_CSC_CTRL3"                 ,dbg_CVB_CSC_CTRL3               },
	{ 0x0234 ,N_FLD(dbg_CVB_CSC_CTRL4)               ,"CVB_CSC_CTRL4"                 ,dbg_CVB_CSC_CTRL4               },
	{ 0x0238 ,N_FLD(dbg_CVB_CSC_CTRL5)               ,"CVB_CSC_CTRL5"                 ,dbg_CVB_CSC_CTRL5               },
	{ 0x023c ,N_FLD(dbg_CVB_CSC_CTRL6)               ,"CVB_CSC_CTRL6"                 ,dbg_CVB_CSC_CTRL6               },
	{ 0x0240 ,N_FLD(dbg_CVB_CSC_CTRL7)               ,"CVB_CSC_CTRL7"                 ,dbg_CVB_CSC_CTRL7               },
	{ 0x0244 ,N_FLD(dbg_CVB_MISC_CTRL)               ,"CVB_MISC_CTRL"                 ,dbg_CVB_MISC_CTRL               },
	{ 0x0248 ,N_FLD(dbg_CVB_OFFSET_READ)             ,"CVB_OFFSET_READ"               ,dbg_CVB_OFFSET_READ             },
	{ 0x024c ,N_FLD(dbg_CVB_PRE3D_CTRL0)             ,"CVB_PRE3D_CTRL0"               ,dbg_CVB_PRE3D_CTRL0             },
	{ 0x0250 ,N_FLD(dbg_CVB_PRE3D_CTRL1)             ,"CVB_PRE3D_CTRL1"               ,dbg_CVB_PRE3D_CTRL1             },
	{ 0x0254 ,N_FLD(dbg_CVB_PRE3D_CTRL2)             ,"CVB_PRE3D_CTRL2"               ,dbg_CVB_PRE3D_CTRL2             },
	{ 0x0258 ,N_FLD(dbg_CVB_SIZE_STATUS1)            ,"CVB_SIZE_STATUS1"              ,dbg_CVB_SIZE_STATUS1            },
	{ 0x025c ,N_FLD(dbg_CVB_SIZE_STATUS2)            ,"CVB_SIZE_STATUS2"              ,dbg_CVB_SIZE_STATUS2            },
	{ 0x0260 ,N_FLD(dbg_CVB_SIZE_STATUS3)            ,"CVB_SIZE_STATUS3"              ,dbg_CVB_SIZE_STATUS3            },
	{ 0x0264 ,N_FLD(dbg_CVB_SIZE_STATUS4)            ,"CVB_SIZE_STATUS4"              ,dbg_CVB_SIZE_STATUS4            },
	{ 0x0268 ,N_FLD(dbg_CVB_PIX_SUM_CTRL0)           ,"CVB_PIX_SUM_CTRL0"             ,dbg_CVB_PIX_SUM_CTRL0           },
	{ 0x026c ,N_FLD(dbg_CVB_PIX_SUM_CTRL1)           ,"CVB_PIX_SUM_CTRL1"             ,dbg_CVB_PIX_SUM_CTRL1           },
	{ 0x0270 ,N_FLD(dbg_CVB_PIX_SUM_STATUS0)         ,"CVB_PIX_SUM_STATUS0"           ,dbg_CVB_PIX_SUM_STATUS0         },
	{ 0x0274 ,N_FLD(dbg_CVB_PIX_SUM_STATUS1)         ,"CVB_PIX_SUM_STATUS1"           ,dbg_CVB_PIX_SUM_STATUS1         },
	{ 0x0278 ,N_FLD(dbg_CVB_PIX_SUM_STATUS2)         ,"CVB_PIX_SUM_STATUS2"           ,dbg_CVB_PIX_SUM_STATUS2         },
	{ 0x027c ,N_FLD(dbg_CVB_SYNC_FIL_CTRL)           ,"CVB_SYNC_FIL_CTRL"             ,dbg_CVB_SYNC_FIL_CTRL           },
	{ 0x0280 ,N_FLD(dbg_CVB_SYNC_FIL_STATUS)         ,"CVB_SYNC_FIL_STATUS"           ,dbg_CVB_SYNC_FIL_STATUS         },
	{ 0x0284 ,N_FLD(dbg_CVB_CTI_CTRL)                ,"CVB_CTI_CTRL"                  ,dbg_CVB_CTI_CTRL                },
	{ 0x0290 ,0                                      ,"CVB_SYNC_REPEAT_CTRL"          ,NULL                            },
	{ 0x0294 ,0                                      ,"CVB_SYNC_REPEAT_SIZE0"         ,NULL                            },
	{ 0x0298 ,0                                      ,"CVB_SYNC_REPEAT_SIZE1"         ,NULL                            },
	{ 0x029c ,0                                      ,"CVB_SYNC_REPEAT_SIZE2"         ,NULL                            },
	{ 0x02a0 ,0                                      ,"CVB_SYNC_REPEAT_SIZE3"         ,NULL                            },
	{ 0x02a4 ,0                                      ,"CVB_SYNC_REPEAT_SIZE4"         ,NULL                            },
	{ 0x02a8 ,0                                      ,"CVB_SYNC_REPEAT_SIZE5"         ,NULL                            },
	{ 0x02ac ,N_FLD(dbg_CVB_DIG_FILT_CTRL4)          ,"CVB_DIG_FILT_CTRL4"            ,dbg_CVB_DIG_FILT_CTRL4          },
	{ 0x02b0 ,N_FLD(dbg_CVB_DIG_FILT_CTRL5)          ,"CVB_DIG_FILT_CTRL5"            ,dbg_CVB_DIG_FILT_CTRL5          },
	{ 0x02b4 ,N_FLD(dbg_CVB_DIG_FILT_CTRL6)          ,"CVB_DIG_FILT_CTRL6"            ,dbg_CVB_DIG_FILT_CTRL6          },
	{ 0x02c0 ,N_FLD(dbg_CVB_SIZE_DETECT_CTRL)        ,"CVB_SIZE_DETECT_CTRL"          ,dbg_CVB_SIZE_DETECT_CTRL        },
	{ 0x02c4 ,N_FLD(dbg_CVB_SIZE_DETECT_READ)        ,"CVB_SIZE_DETECT_READ"          ,dbg_CVB_SIZE_DETECT_READ        },
	{ 0x02c8 ,N_FLD(dbg_CVB_SIZE_STATUS0)            ,"CVB_SIZE_STATUS0"              ,dbg_CVB_SIZE_STATUS0            },
	{ 0x02cc ,N_FLD(dbg_CVB_SIZE_STATUS5)            ,"CVB_SIZE_STATUS5"              ,dbg_CVB_SIZE_STATUS5            },
	{ 0x02d0 ,N_FLD(dbg_CVB_SIZE_STATUS6)            ,"CVB_SIZE_STATUS6"              ,dbg_CVB_SIZE_STATUS6            },
	{ 0x02d4 ,N_FLD(dbg_CVB_SIZE_DETECT_CTRL1)       ,"CVB_SIZE_DETECT_CTRL1"         ,dbg_CVB_SIZE_DETECT_CTRL1       },
	{ 0x02d8 ,N_FLD(dbg_CVB_SIZE_DETECT_CTRL2)       ,"CVB_SIZE_DETECT_CTRL2"         ,dbg_CVB_SIZE_DETECT_CTRL2       },
	{ 0x02dc ,N_FLD(dbg_CVB_PSEUDO_SYNC_CTRL0)       ,"CVB_PSEUDO_SYNC_CTRL0"         ,dbg_CVB_PSEUDO_SYNC_CTRL0       },
	{ 0x02e0 ,N_FLD(dbg_CVB_PSEUDO_SYNC_CTRL1)       ,"CVB_PSEUDO_SYNC_CTRL1"         ,dbg_CVB_PSEUDO_SYNC_CTRL1       },
	{ 0x02e4 ,N_FLD(dbg_CVB_PSEUDO_SYNC_CTRL2)       ,"CVB_PSEUDO_SYNC_CTRL2"         ,dbg_CVB_PSEUDO_SYNC_CTRL2       },
	{ 0x02e8 ,N_FLD(dbg_CVB_PSEUDO_SYNC_CTRL3)       ,"CVB_PSEUDO_SYNC_CTRL3"         ,dbg_CVB_PSEUDO_SYNC_CTRL3       },
	{ 0x02ec ,N_FLD(dbg_CVB_PSEUDO_SYNC_CTRL4)       ,"CVB_PSEUDO_SYNC_CTRL4"         ,dbg_CVB_PSEUDO_SYNC_CTRL4       },
	{ 0x02f0 ,N_FLD(dbg_CVB_PREADY_TIMER)            ,"CVB_PREADY_TIMER"              ,dbg_CVB_PREADY_TIMER            },
	{ 0 , } // end marker
};

#endif
