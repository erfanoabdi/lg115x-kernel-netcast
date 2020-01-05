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

#ifndef _DBG_CVD_h
#define _DBG_CVD_h

/*----------------------------------------
	0x4100 CVD_INTR1_ENABLE0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR1_ENABLE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr1_enable0"               },
};

/*----------------------------------------
	0x4104 CVD_INTR1_INTR0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR1_INTR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cvd_chromalock_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cvd_chromalock_ris"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cvd_vlock_fal"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cvd_vlock_ris"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cvd_hlock_fal"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cvd_hlock_ris"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cvd_no_signal_fal"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cvd_no_signal_ris"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cvd_noburst_detected_fal"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"cvd_noburst_detected_ris"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"cvd_vnon_standard_fal"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"cvd_vnon_standard_ris"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cvd_hnon_standard_fal"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"cvd_hnon_standard_ris"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"cvd_proscan_detected_fal"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"cvd_proscan_detected_ris"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cvd_vcr_fal"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"cvd_vcr_ris"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"cvd_noisy_fal"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"cvd_noisy_ris"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cvd_vline_625_detected_fal"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"cvd_vline_625_detected_ris"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"cvd_secam_detected_fal"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"cvd_secam_detected_ris"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cvd_pal_detected_fal"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"cvd_pal_detected_ris"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"cvd_vs_fal"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"cvd_vs_ris"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"cvd_ext_locked_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"cvd_ext_locked_ris"              },
};

/*----------------------------------------
	0x4108 CVD_INTR1_CLEAR0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR1_CLEAR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr1_clear0"                },
};

/*----------------------------------------
	0x410c CVD_INTR1_ENABLE1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR1_ENABLE1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr1_enable1"               },
};

/*----------------------------------------
	0x4110 CVD_INTR1_INTR1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR1_INTR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vbi_wss_rdy"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"vbi_cc_rdy"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vbi_data_in"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cvd_fb_rst"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cvd_mif_err"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cs_chromalock_fal"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cs_chromalock_ris"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cs_pal_detected_fal"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs_pal_detected_ris"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"cs_secam_detected_fal"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"cs_secam_detected_ris"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"cs1_chromalock_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cs1_chromalock_ris"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"cs1_pal_detected_fal"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"cs1_pal_detected_ris"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"cs1_secam_detected_fal"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cs1_secam_detected_ris"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"estfrdp_err_flag_fal"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"estfrdp_err_flag_ris"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"vdetect_vcount_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"vdetect_vcount_ris"              },
};

/*----------------------------------------
	0x4114 CVD_INTR1_CLEAR1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR1_CLEAR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr1_clear1"                },
};

/*----------------------------------------
	0x4118 CVD_INTR2_ENABLE0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR2_ENABLE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr2_enable0"               },
};

/*----------------------------------------
	0x411c CVD_INTR2_INTR0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR2_INTR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cvd_chromalock_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cvd_chromalock_ris"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cvd_vlock_fal"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cvd_vlock_ris"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cvd_hlock_fal"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cvd_hlock_ris"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cvd_no_signal_fal"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cvd_no_signal_ris"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cvd_noburst_detected_fal"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"cvd_noburst_detected_ris"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"cvd_vnon_standard_fal"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"cvd_vnon_standard_ris"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cvd_hnon_standard_fal"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"cvd_hnon_standard_ris"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"cvd_proscan_detected_fal"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"cvd_proscan_detected_ris"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cvd_vcr_fal"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"cvd_vcr_ris"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"cvd_noisy_fal"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"cvd_noisy_ris"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cvd_vline_625_detected_fal"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"cvd_vline_625_detected_ris"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"cvd_secam_detected_fal"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"cvd_secam_detected_ris"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cvd_pal_detected_fal"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"cvd_pal_detected_ris"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"cvd_vs_fal"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"cvd_vs_ris"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"cvd_ext_locked_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"cvd_ext_locked_ris"              },
};

/*----------------------------------------
	0x4120 CVD_INTR2_CLEAR0
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR2_CLEAR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr2_clear0"                },
};

/*----------------------------------------
	0x4124 CVD_INTR2_ENABLE1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR2_ENABLE1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr2_enable1"               },
};

/*----------------------------------------
	0x4128 CVD_INTR2_INTR1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR2_INTR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vbi_wss_rdy"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"vbi_cc_rdy"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"vbi_data_in"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"cvd_fb_rst"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cvd_mif_err"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cs_chromalock_fal"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cs_chromalock_ris"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"cs_pal_detected_fal"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs_pal_detected_ris"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"cs_secam_detected_fal"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"cs_secam_detected_ris"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"cs1_chromalock_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cs1_chromalock_ris"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"cs1_pal_detected_fal"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"cs1_pal_detected_ris"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"cs1_secam_detected_fal"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cs1_secam_detected_ris"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"estfrdp_err_flag_fal"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"estfrdp_err_flag_ris"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"vdetect_vcount_fal"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"vdetect_vcount_ris"              },
};

/*----------------------------------------
	0x412c CVD_INTR2_CLEAR1
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVD_INTR2_CLEAR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cvd_intr2_clear1"                },
};

/*----------------------------------------
	0x4130 TOP_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_TOP_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"iris_ver"                        },
};

/*----------------------------------------
	0x4140 IRIS_MIF_GMUA_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,0  ,"comb3_buffer_size"               },
};

/*----------------------------------------
	0x4144 IRIS_MIF_GMUA_002
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_002[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,0  ,"fld1_init_rd_pel"                },
};

/*----------------------------------------
	0x4148 IRIS_MIF_GMUA_003
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_003[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,0  ,"fld2_init_rd_pel"                },
};

/*----------------------------------------
	0x414c IRIS_MIF_GMUA_004
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_004[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,0  ,"fld3_init_rd_pel"                },
};

/*----------------------------------------
	0x4150 IRIS_MIF_GMUA_005
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_005[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,0  ,"fld4_init_rd_pel"                },
};

/*----------------------------------------
	0x4154 IRIS_MIF_GMUA_006
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_006[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"gmau_to_cnt"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"gmau_cmd_dly_cnt"                },
};

/*----------------------------------------
	0x4158 IRIS_MIF_GMUA_007
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_007[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"gmau_cmd_base"                   },
};

/*----------------------------------------
	0x4160 IRIS_MIF_GMUA_008
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_008[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_endian_sw"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"gmau_cmd_pri2"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"gmau_cmd_pri1"                   },
};

/*----------------------------------------
	0x4164 IRIS_MIF_GMUA_009
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_009[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"gmau_stride_size"                },
};

/*----------------------------------------
	0x4168 FASTBLANK_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"fb_latency"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,8  ,"fb3ch_delay"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"fb_blend_ratio"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fb_2line_delay"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"fb_en"                           },
};

/*----------------------------------------
	0x416c FASTBLANK_002
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_002[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"fb_csc_coef1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"fb_csc_coef0"                    },
};

/*----------------------------------------
	0x4170 FASTBLANK_003
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_003[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"fb_csc_coef3"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"fb_csc_coef2"                    },
};

/*----------------------------------------
	0x4174 FASTBLANK_004
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_004[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"fb_csc_coef5"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"fb_csc_coef4"                    },
};

/*----------------------------------------
	0x4178 FASTBLANK_005
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_005[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"fb_csc_coef7"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"fb_csc_coef6"                    },
};

/*----------------------------------------
	0x417c FASTBLANK_006
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_006[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"fb_csc_coef8"                    },
};

/*----------------------------------------
	0x4180 FASTBLANK_007
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_007[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"fb_csc_ofst1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"fb_csc_ofst0"                    },
};

/*----------------------------------------
	0x4184 FASTBLANK_008
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_008[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"fb_csc_ofst3"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"fb_csc_ofst2"                    },
};

/*----------------------------------------
	0x4188 FASTBLANK_009
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_009[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"fb_vstart_odd"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,8  ,"fb_csc_ofst5"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,20 ,"fb_csc_ofst4"                    },
};

/*----------------------------------------
	0x418c FASTBLANK_010
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FASTBLANK_010[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"fb_hstart"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"fb_height_half"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,16 ,"fb_vstart_even"                  },
};

/*----------------------------------------
	0x4190 IRIS_DE_CTRL_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_DE_CTRL_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"iris_hsout_width"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"iris_static_de_start"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"iris_static_de"                  },
};

/*----------------------------------------
	0x4194 VBI_CTRL_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vbi_little_endian"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vbi_bits_swap"                   },
};

/*----------------------------------------
	0x4198 VBI_CTRL_002
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_002[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi0_start_addr"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"vbi0_data_cnt"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"vbi_buffer_number"               },
};

/*----------------------------------------
	0x419c VBI_CTRL_003
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_003[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi0_end_addr"                   },
};

/*----------------------------------------
	0x41a0 VBI_CTRL_004
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_004[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi1_start_addr"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"vbi1_data_cnt"                   },
};

/*----------------------------------------
	0x41a4 VBI_CTRL_005
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_005[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi1_end_addr"                   },
};

/*----------------------------------------
	0x41a8 VBI_CTRL_006
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_006[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi2_start_addr"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"vbi2_data_cnt"                   },
};

/*----------------------------------------
	0x41ac VBI_CTRL_007
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_007[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi2_end_addr"                   },
};

/*----------------------------------------
	0x41b0 VBI_CTRL_008
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_008[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi3_start_addr"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"vbi3_data_cnt"                   },
};

/*----------------------------------------
	0x41b4 VBI_CTRL_009
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_CTRL_009[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"vbi3_end_addr"                   },
};

/*----------------------------------------
	0x41c0 FAST_BLANK_STATUS_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_FAST_BLANK_STATUS_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fb_state"                        },
};

/*----------------------------------------
	0x41c4 CVBSAFE_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_CVBSAFE_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cvbs2_gc_int"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cvbs1_gc_int"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"iris_fix_gain"                   },
};

/*----------------------------------------
	0x4200 IRIS_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"proscan_detected"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"mv_colourstripes"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"mv_vbi_detected"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"chromalock"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"vlock"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"hlock"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"no_signal"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"status_vdetect_vcount_chg"       },
};

/*----------------------------------------
	0x4204 IRIS_002
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_002[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"noisy"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vline_625_detected"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"secam_detected"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pal_detected"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"status_comb3d_off"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"noburst_detected"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"vnon_standard"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hnon_standard"                   },
};

/*----------------------------------------
	0x4208 IRIS_003
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_003[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vcr_rew"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vcr_ff"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vcr_trick"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"reg_vcr"                         },
};

/*----------------------------------------
	0x420c IRIS_004
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_004[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"status_burst_mag"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"status_hsync_width"              },
};

/*----------------------------------------
	0x4210 IRIS_005
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_005[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"status_hdto_inc"                 },
};

/*----------------------------------------
	0x4214 IRIS_006
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_006[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"status_cdto_inc"                 },
};

/*----------------------------------------
	0x4218 IRIS_007
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_007[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"status_cmag"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,8  ,"status_agc_gain"                 },
};

/*----------------------------------------
	0x421c IRIS_008
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_008[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"status_sync_height"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"status_cordic_freq"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,16 ,"status_cgain"                    },
};

/*----------------------------------------
	0x4220 IRIS_009
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_009[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"status_nstd"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"status_vbi_slicer_lvl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"status_noise"                    },
};

/*----------------------------------------
	0x4224 IRIS_010
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_010[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"status_comb3d_motion"            },
};

/*----------------------------------------
	0x4230 IRIS_011
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_011[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cvd_soft_reset"                  },
};

/*----------------------------------------
	0x4234 IRIS_012
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_012[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hv_delay"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"hpixel"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vline_625"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"colour_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"yc_src"                          },
};

/*----------------------------------------
	0x4238 IRIS_013
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_013[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cv_inv"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cv_src"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"luma_notch_bw"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"chroma_bw_lo"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"chroma_burst5or10"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"reg_ped"                         },
};

/*----------------------------------------
	0x423c IRIS_014
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_014[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hagc_field_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mv_hagc_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"dc_clamp_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dagc_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"agc_half_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cagc_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"hagc_en"                         },
};

/*----------------------------------------
	0x4240 IRIS_015
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_015[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pal60_mode"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ntsc443_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"adaptive_3dcomb_mode"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"colour_trap"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"adaptive_mode"                   },
};

/*----------------------------------------
	0x4244 IRIS_016
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_016[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"noise_thresh"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hagc"                            },
};

/*----------------------------------------
	0x4248 IRIS_017
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_017[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"force_vcr_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"force_vcr_rew"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"force_vcr_ff"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"force_vcr_trick"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"force_vcr"                       },
};

/*----------------------------------------
	0x424c IRIS_018
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_018[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"adc_updn_swap"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"adc_input_swap"                  },
};

/*----------------------------------------
	0x4250 IRIS_019
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_019[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ccir656_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cbcr_swap"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"blue_mode"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"yc_delay"                        },
};

/*----------------------------------------
	0x4254 IRIS_020
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_020[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"reg_hue"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"saturation"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"brightness"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"contrast"                        },
};

/*----------------------------------------
	0x4258 IRIS_021
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_021[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cagc"                            },
};

/*----------------------------------------
	0x425c IRIS_022
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_022[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"user_ckill_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vbi_ckill"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hlock_ckill"                     },
};

/*----------------------------------------
	0x4260 IRIS_023
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_023[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"nstd_hysis"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"disable_clamp_on_vsync"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"bypass"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"noburst_ckill"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"vnon_std_threshold"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,20 ,"hnon_std_threshold"              },
};

/*----------------------------------------
	0x4264 IRIS_024
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_024[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"agc_peak_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"agc_peak_cntl"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"agc_peak_nominal"                },
};

/*----------------------------------------
	0x4268 IRIS_025
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_025[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"blue_cr"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"blue_cb"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"blue_y"                          },
};

/*----------------------------------------
	0x426c IRIS_026
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_026[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hstate_fixed"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"disable_hfine"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hstate_unlocked"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"hstate_max"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"locked_count_noisy_max"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"locked_count_clean_max"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"hdetect_clamp_level"             },
};

/*----------------------------------------
	0x4270 IRIS_027
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_027[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"hlock_vsync_mode"                },
};

/*----------------------------------------
	0x4274 IRIS_028
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_028[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdto_inc"                        },
};

/*----------------------------------------
	0x4278 IRIS_029
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_029[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"hdto_inc"                        },
};

/*----------------------------------------
	0x427c IRIS_030
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_030[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hsync_gate_end"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hsync_gate_start"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hsync_phase_offset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"hsync_rising"                    },
};

/*----------------------------------------
	0x4280 IRIS_031
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_031[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hsync_similar"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"hsync_low"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hdetect_noise_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"hfine_lt_hcoarse"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"hlpf_clamp_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"hlpf_clamp_noisy_en"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"hlpf_clamp_vbi_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"hlpf_clamp_en"                   },
};

/*----------------------------------------
	0x4284 IRIS_032
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_032[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hsync_rising_end"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"hsync_rising_auto"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,12 ,"hsync_rising_start"              },
};

/*----------------------------------------
	0x4288 IRIS_033
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_033[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hblank_end"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hblank_start"                    },
};

/*----------------------------------------
	0x428c IRIS_034
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_034[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"burst_gate_end"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"burst_gate_start"                },
};

/*----------------------------------------
	0x4290 IRIS_035
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_035[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hactive_width"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hactive_start"                   },
};

/*----------------------------------------
	0x4294 IRIS_036
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_036[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vactive_height"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vactive_start"                   },
};

/*----------------------------------------
	0x4298 IRIS_037
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_037[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"vsync_h_max"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"vsync_h_min"                     },
};

/*----------------------------------------
	0x429c IRIS_038
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_038[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"vsync_agc_max"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"vsync_agc_min"                   },
};

/*----------------------------------------
	0x42a0 IRIS_039
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_039[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"vsync_vbi_max"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"vsync_vbi_min"                   },
};

/*----------------------------------------
	0x42a4 IRIS_040
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_040[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vlock_wide_range"                },
};

/*----------------------------------------
	0x42a8 IRIS_041
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_041[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"proscan_1field_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vsync_cntl_noisy"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vsync_cntl_ff_rew"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"vsync_cntl_trick"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"vsync_cntl_vcr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"vsync_cntl"                      },
};

/*----------------------------------------
	0x42ac IRIS_042
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_042[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"field_polarity"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"flip_field"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"veven_delayed"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"vodd_delayed"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"field_detect_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"vloop_tc"                        },
};

/*----------------------------------------
	0x42b0 IRIS_043
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_043[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dbg_syncs"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"muxdigital"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"muxanalogb"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"muxanaloga"                      },
};

/*----------------------------------------
	0x42b4 IRIS_044
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_044[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"secam_ybw"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"peak_range"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"peak_gain"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"peak_en"                         },
};

/*----------------------------------------
	0x42b8 IRIS_045
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_045[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"auto_secam_level"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"sv_bf"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"secam_pll"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"secam_sw_old"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"palsw_level"                     },
};

/*----------------------------------------
	0x42bc IRIS_046
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_046[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"lose_chromalock_mode"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"lose_chromalock_count"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"lose_chromalock_level"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"lose_chromalock_ckill"           },
};

/*----------------------------------------
	0x42c0 IRIS_047
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_047[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"cstripe_detect_control"          },
};

/*----------------------------------------
	0x42c4 IRIS_048
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_048[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hfine_vcr_trick_en"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"hfine_vcr_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hresampler_2up"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"cstate"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"fixed_cstate"                    },
};

/*----------------------------------------
	0x42c8 IRIS_049
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_049[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbi_pulse_ampl"                  },
};

/*----------------------------------------
	0x42cc IRIS_050
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_050[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cpump_delay"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cpump_adjust"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cpump_adjust_polarity"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,20 ,"cpump_adjust_delay"              },
};

/*----------------------------------------
	0x42d0 IRIS_051
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_051[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"mv_colourstripes_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mv_vbi_sel"                      },
};

/*----------------------------------------
	0x42d4 IRIS_052
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_052[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cpump_kill_cr"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cpump_kill_cb"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cpump_kill_y"                    },
};

/*----------------------------------------
	0x42d8 IRIS_053
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_053[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cpump_auto_stip_nobp"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cpump_auto_stip_unlocked"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cpump_auto_stip_no_signal"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cpump_auto_stip_noisy"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cpump_auto_stip_vactive"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"cpump_auto_stip_mode"            },
};

/*----------------------------------------
	0x42dc IRIS_054
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_054[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cpump_accum_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cpump_fixed_syncmid"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cpump_level_filter_gain"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cpump_noisy_filter_en"           },
};

/*----------------------------------------
	0x42e0 IRIS_055
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_055[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,0  ,"cpump_dn_max"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,8  ,"cpump_up_max"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cpump_vsync_blank_filter"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cpump_vsync_syncmid_filter"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"cpump_vsync_mode"                },
};

/*----------------------------------------
	0x42e4 IRIS_056
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_056[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cpump_diff_noisy_only"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,4  ,"cpump_dn_diff_max"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cpump_diff_signal_only"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,16 ,"cpump_up_diff_max"               },
};

/*----------------------------------------
	0x42e8 IRIS_057
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_057[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cpump_pr_override"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cpump_pb_override"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cpump_y_override"                },
};

/*----------------------------------------
	0x42ec IRIS_058
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_058[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"db_freq"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"dr_freq"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,24 ,"cvbs_y_delay"                    },
};

/*----------------------------------------
	0x42f0 IRIS_059
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_059[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vactivity_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vactivity_on2frame"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"vactivity_threshold"             },
};

/*----------------------------------------
	0x42f4 IRIS_060
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_060[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"horiz_diff_cgain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"horiz_diff_ygain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"chroma_vdiff_gain"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"lowfreq_vdiff_gain"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"noise_th_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,20 ,"noise_th"                        },
};

/*----------------------------------------
	0x42f8 IRIS_061
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_061[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vadap_burst_noise_th_gain"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"burst_noise_th_gain"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"c_noise_th_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"y_noise_th_gain"                 },
};

/*----------------------------------------
	0x42fc IRIS_062
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_062[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"adaptive_chroma_mode"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"dot_suppress_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"motion_mode"                     },
};

/*----------------------------------------
	0x4300 IRIS_063
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_063[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pal3dcomb_vactive_offset"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"fb_sync"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"fb_hold"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"fb_ctl"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"field_latency"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"lbadrgen_rst"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"comb2d_only"                     },
};

/*----------------------------------------
	0x4304 IRIS_064
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_064[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"md_noise_th_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,4  ,"md_noise_th"                     },
};

/*----------------------------------------
	0x4308 IRIS_065
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_065[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"schroma_peak_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"schroma_coring_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"schroma_peak"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pchroma_peak_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"pchroma_coring_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"pchroma_peak"                    },
};

/*----------------------------------------
	0x430c IRIS_066
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_066[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"ldpause_threshold"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vf_nstd_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vcr_auto_switch_en"              },
};

/*----------------------------------------
	0x4310 IRIS_067
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_067[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"comb_coring"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"tcomb_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"notch_gain"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"comb_gain"                       },
};

/*----------------------------------------
	0x4314 IRIS_068
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_068[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vactive_md_height"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vactive_md_start"                },
};

/*----------------------------------------
	0x4318 IRIS_069
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_069[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"hsync_pulse_width"               },
};

/*----------------------------------------
	0x431c IRIS_070
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_070[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"cagc_tc_ismall"                  },
};

/*----------------------------------------
	0x4320 IRIS_071
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_071[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cagc_coring_threshold"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cagc_unity_gain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"cagc_coring"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cagc_tc_p"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cagc_tc_ibig"                    },
};

/*----------------------------------------
	0x4324 IRIS_072
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_072[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"aaf_on"                          },
};

/*----------------------------------------
	0x4328 IRIS_073
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_073[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"dcrestore_accum_width"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dcrestore_no_bad_bp"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dcrestore_kill_enable"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"dcrestore_bp_delay"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"syncmid_nobp_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"syncmid_filter_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"dcrestore_gain"                  },
};

/*----------------------------------------
	0x432c IRIS_074
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_074[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dcrestore_kill_enable_noisy"     },
};

/*----------------------------------------
	0x4330 IRIS_075
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_075[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"dcrestore_hsync_mid"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"bp_kill_thresh"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hmgc"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"dcrestore_lpf_en"                },
};

/*----------------------------------------
	0x4334 IRIS_076
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_076[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"auto_min_sync_height"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,4  ,"min_sync_height"                 },
};

/*----------------------------------------
	0x4338 IRIS_077
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_077[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vcrtrick_proscan"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"veven_early_delayed"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vodd_early_delayed"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"vfield_hoffset_fixed"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vsync_no_signal_thresh"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vsync_signal_thresh"             },
};

/*----------------------------------------
	0x433c IRIS_078
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_078[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,0  ,"vfield_hoffset"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"vactive_half_lines"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"vdetect_noise_en"                },
};

/*----------------------------------------
	0x4340 IRIS_079
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_079[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dual_hedge_dis"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"dual_hedge_auto_width"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dual_fine_hedge_vbi"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"dual_coarse_hedge_vbi"           },
};

/*----------------------------------------
	0x4344 IRIS_080
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_080[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"mv_hsync_rising_end"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vcr_state2_long"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"slow_hdsw"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,16 ,"mv_hsync_rising_start"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"no_hsyncs_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"many_hsyncs_mode"                },
};

/*----------------------------------------
	0x4348 IRIS_081
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_081[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"no_hsyncs_weak"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"disable_hdsw_weak"               },
};

/*----------------------------------------
	0x434c IRIS_082
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_082[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vactive_hdsw_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"disable_hdsw_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"hsync_falling_filter"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"no_hsyncs_noisy"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"hloop_range"                     },
};

/*----------------------------------------
	0x4350 IRIS_083
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_083[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"md_hf_max"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"md_hf_shift"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"md_lf_sad"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"md_lf_shift"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"md_c_noise_th_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,20 ,"md_c_noise_th"                   },
};

/*----------------------------------------
	0x4354 IRIS_084
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_084[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"md_cf_cactivity_high"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,4  ,"md_cf_lactivity_high"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"md_cf_cactivity_low"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"md_cf_lactivity_low"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"md_cf_activity_enable"           },
};

/*----------------------------------------
	0x4358 IRIS_085
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_085[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"md_k_thresh"                     },
};

/*----------------------------------------
	0x435c IRIS_086
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_086[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"tcomb_chroma_level"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hf_luma_chroma_offset"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"spatial_luma_level"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"chroma_level"                    },
};

/*----------------------------------------
	0x4360 IRIS_087
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_087[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"chroma_activity_level"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"lf_luma_offset"                  },
};

/*----------------------------------------
	0x4364 IRIS_088
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_088[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"avg_freq_range"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,4  ,"issecam_th"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"freq_offset_range"               },
};

/*----------------------------------------
	0x4368 IRIS_089
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_089[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"chroma_bw_motion_th"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"motion_config"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hactive_md_width"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"hactive_md_start"                },
};

/*----------------------------------------
	0x436c IRIS_090
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_090[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"status_motion_mode"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"chroma_bw_motion"                },
};

/*----------------------------------------
	0x4370 IRIS_091
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_091[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"flat_chroma_offset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"flat_luma_offset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"flat_chroma_shift"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"flat_luma_shift"                 },
};

/*----------------------------------------
	0x4374 IRIS_092
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_092[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"motion_debug"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cf_flat_motion_shift"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"motion_c_mode"                   },
};

/*----------------------------------------
	0x4378 IRIS_093
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_093[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cordic_gate_end"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cordic_gate_start"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ispal_th"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"phase_offset_range"              },
};

/*----------------------------------------
	0x437c IRIS_094
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_094[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pal3tap_only_c"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"pal3tap_only_y"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"adc_cpump_swap"                  },
};

/*----------------------------------------
	0x4380 IRIS_095
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_095[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"ckill"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cagc_gate_end"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cagc_gate_start"                 },
};

/*----------------------------------------
	0x4384 IRIS_096
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_096[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"icburst_half_ampl"               },
};

/*----------------------------------------
	0x4388 IRIS_097
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_097[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"agc_bypass"                      },
};

/*----------------------------------------
	0x438c IRIS_098
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_098[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"clampagc_inv"                    },
};

/*----------------------------------------
	0x4390 IRIS_099
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_099[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vps_slicer_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"wss_slicer_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"tt_slicer_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cc_slicer_mode"                  },
};

/*----------------------------------------
	0x4394 IRIS_100
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_100[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"perr_on"                         },
};

/*----------------------------------------
	0x4398 IRIS_101
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_101[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"perr_dnref"                      },
};

/*----------------------------------------
	0x439c IRIS_102
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_102[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"cres_lpfa_coeff0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cres_lpfa_on"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"iris_cresampler_on"              },
};

/*----------------------------------------
	0x43a0 IRIS_103
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_103[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"cres_lpfa_coeff2"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"cres_lpfa_coeff1"                },
};

/*----------------------------------------
	0x43a4 IRIS_104
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_104[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"cres_lpfa_coeff4"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"cres_lpfa_coeff3"                },
};

/*----------------------------------------
	0x43a8 IRIS_105
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_105[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"cres_lpfa_coeff5"                },
};

/*----------------------------------------
	0x43ac IRIS_106
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_106[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"cres_lpfb_coeff0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cres_lpfb_on"                    },
};

/*----------------------------------------
	0x43b0 IRIS_107
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_107[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"cres_lpfb_coeff2"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"cres_lpfb_coeff1"                },
};

/*----------------------------------------
	0x43b4 IRIS_108
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_108[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"cres_lpfb_coeff4"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"cres_lpfb_coeff3"                },
};

/*----------------------------------------
	0x43b8 IRIS_109
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_109[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cres_blend_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"cres_blend_method"               },
};

/*----------------------------------------
	0x43bc IRIS_110
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_110[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"cres_blend_bcdefault"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cres_0px_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"cres_clksel"                     },
};

/*----------------------------------------
	0x43c0 IRIS_111
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_111[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"cres_blend_bcpara1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"cres_blend_bcpara0"              },
};

/*----------------------------------------
	0x43c4 IRIS_112
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_112[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"cres_blend_bcpara3"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"cres_blend_bcpara2"              },
};

/*----------------------------------------
	0x43c8 IRIS_113
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_113[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"cres_blend_bcpara5"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"cres_blend_bcpara4"              },
};

/*----------------------------------------
	0x43cc IRIS_114
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_114[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"cres_blend_bcpara7"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"cres_blend_bcpara6"              },
};

/*----------------------------------------
	0x43d0 IRIS_115
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_115[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cres_blend_diffth1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"cres_blend_diffth0"              },
};

/*----------------------------------------
	0x43d4 IRIS_116
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_116[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cres_alpha_off"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,8  ,"cres_blend_diffth2"              },
};

/*----------------------------------------
	0x43d8 IRIS_117
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_117[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"hrscbld_dnoff"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"hrscbld_upoff"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"hrsybld_dnoff"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"hrsybld_upoff"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"dtrs_dlysel"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"dtrs_revalpha_sel"               },
};

/*----------------------------------------
	0x43dc IRIS_118
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_118[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"oadj_y_offo"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"oadj_y_offi"                     },
};

/*----------------------------------------
	0x43e0 IRIS_119
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_119[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"oadj_y_coeff"                    },
};

/*----------------------------------------
	0x43e4 IRIS_120
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_120[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"oadj_c_offo"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"oadj_c_offi"                     },
};

/*----------------------------------------
	0x43e8 IRIS_121
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_121[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"oadj_c_coeff"                    },
};

/*----------------------------------------
	0x43ec IRIS_122
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_122[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"adc_unity_gain_value"            },
};

/*----------------------------------------
	0x43f0 IRIS_123
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_123[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"frame_motion_th1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"frame_motion_th0"                },
};

/*----------------------------------------
	0x43f4 IRIS_124
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_124[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"iblank_half_lvl0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,12 ,"isynctip_lvl0"                   },
};

/*----------------------------------------
	0x43f8 IRIS_125
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_125[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"sync_int_blank_lvl0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,12 ,"ipeak_chroma_m768_lvl0"          },
};

/*----------------------------------------
	0x43fc IRIS_126
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_126[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sync_int_blank_vid_lvl0"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,8  ,"int_black_ped_vid_lvl0"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"int_blank_vid_lvl0"              },
};

/*----------------------------------------
	0x4400 IRIS_127
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_127[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"int_vbi_blank_vid_lvl0"          },
};

/*----------------------------------------
	0x4404 IRIS_128
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_128[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"internal_sync_midpt"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"internal_sync_level"             },
};

/*----------------------------------------
	0x4408 IRIS_129
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_129[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"sync_internal_sync_midpt"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,12 ,"internal_blank_level"            },
};

/*----------------------------------------
	0x440c IRIS_130
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_130[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"adc_blank_level"                 },
};

/*----------------------------------------
	0x4410 IRIS_131
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_131[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hrs_alpha_croff"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hrs_alpha_cboff"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"hrs_alpha_yoff"                  },
};

/*----------------------------------------
	0x4414 IRIS_132
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_132[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"cphase_adjust"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cphase_adjust_sel"               },
};

/*----------------------------------------
	0x4418 IRIS_133
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_133[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"adap_clf_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"cb_delay"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"yc444"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ycadj_cr_p"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"oadj_swap"                       },
};

/*----------------------------------------
	0x441c IRIS_134
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_134[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"lpf_tap_0_0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"lpf_0_en"                        },
};

/*----------------------------------------
	0x4420 IRIS_135
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_135[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"lpf_tap_0_2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"lpf_tap_0_1"                     },
};

/*----------------------------------------
	0x4424 IRIS_136
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_136[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"lpf_tap_0_4"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"lpf_tap_0_3"                     },
};

/*----------------------------------------
	0x4428 IRIS_137
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_137[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"lpf_tap_0_6"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"lpf_tap_0_5"                     },
};

/*----------------------------------------
	0x442c IRIS_138
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_138[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"hs_missing_max"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"hs_match_max"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"hs_cnt_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"hs_sync_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"status_pseudo_sync"              },
};

/*----------------------------------------
	0x4430 IRIS_139
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_139[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"hs_length_prd_0"                 },
};

/*----------------------------------------
	0x4434 IRIS_140
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_140[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"hs_length_prd_th_0"              },
};

/*----------------------------------------
	0x4438 IRIS_141
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_141[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"hs_length_pos_0"                 },
};

/*----------------------------------------
	0x443c IRIS_142
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_142[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"hs_length_pos_th_0"              },
};

/*----------------------------------------
	0x4440 IRIS_143
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_143[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"hs_length_prd_1"                 },
};

/*----------------------------------------
	0x4444 IRIS_144
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_144[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"hs_length_prd_th_1"              },
};

/*----------------------------------------
	0x4448 IRIS_145
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_145[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"hs_length_pos_1"                 },
};

/*----------------------------------------
	0x444c IRIS_146
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_146[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vs_cnt_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"vs_sync_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,8  ,"hs_length_pos_th_1"              },
};

/*----------------------------------------
	0x4450 IRIS_147
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_147[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"vs_missing_max"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"vs_match_max"                    },
};

/*----------------------------------------
	0x4454 IRIS_148
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_148[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"vs_length_prd_0"                 },
};

/*----------------------------------------
	0x4458 IRIS_149
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_149[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"vs_length_prd_th_0"              },
};

/*----------------------------------------
	0x445c IRIS_150
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_150[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"vs_length_pos_0"                 },
};

/*----------------------------------------
	0x4460 IRIS_151
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_151[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"vs_length_pos_th_0"              },
};

/*----------------------------------------
	0x4464 IRIS_152
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_152[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"vs_length_prd_1"                 },
};

/*----------------------------------------
	0x4468 IRIS_153
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_153[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"vs_length_prd_th_1"              },
};

/*----------------------------------------
	0x446c IRIS_154
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_154[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"vs_length_pos_1"                 },
};

/*----------------------------------------
	0x4470 IRIS_155
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_155[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ha_cnt_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"ha_sync_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,8  ,"vs_length_pos_th_1"              },
};

/*----------------------------------------
	0x4474 IRIS_156
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_156[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"ha_missing_max"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"ha_match_max"                    },
};

/*----------------------------------------
	0x4478 IRIS_157
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_157[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"ha_length_prd_0"                 },
};

/*----------------------------------------
	0x447c IRIS_158
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_158[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"ha_length_prd_th_0"              },
};

/*----------------------------------------
	0x4480 IRIS_159
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_159[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"ha_length_pos_0"                 },
};

/*----------------------------------------
	0x4484 IRIS_160
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_160[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"ha_length_pos_th_0"              },
};

/*----------------------------------------
	0x4488 IRIS_161
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_161[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"ha_length_prd_1"                 },
};

/*----------------------------------------
	0x448c IRIS_162
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_162[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"ha_length_prd_th_1"              },
};

/*----------------------------------------
	0x4490 IRIS_163
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_163[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"ha_length_pos_1"                 },
};

/*----------------------------------------
	0x4494 IRIS_164
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_164[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"va_cnt_mode"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"va_sync_mode"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,8  ,"ha_length_pos_th_1"              },
};

/*----------------------------------------
	0x4498 IRIS_165
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_165[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"va_missing_max"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,8  ,"va_match_max"                    },
};

/*----------------------------------------
	0x449c IRIS_166
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_166[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_prd_0"                 },
};

/*----------------------------------------
	0x44a0 IRIS_167
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_167[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_prd_th_0"              },
};

/*----------------------------------------
	0x44a4 IRIS_168
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_168[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_pos_0"                 },
};

/*----------------------------------------
	0x44a8 IRIS_169
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_169[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_pos_th_0"              },
};

/*----------------------------------------
	0x44ac IRIS_170
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_170[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_prd_1"                 },
};

/*----------------------------------------
	0x44b0 IRIS_171
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_171[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_prd_th_1"              },
};

/*----------------------------------------
	0x44b4 IRIS_172
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_172[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_pos_1"                 },
};

/*----------------------------------------
	0x44b8 IRIS_173
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_173[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,0  ,"va_length_pos_th_1"              },
};

/*----------------------------------------
	0x44bc IRIS_174
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_174[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"sw_rst_blk"                      },
};

/*----------------------------------------
	0x44c0 IRIS_175
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_175[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,0  ,"status_cenable_f0cnt"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,20 ,"status_cenable_ctrl"             },
};

/*----------------------------------------
	0x44c4 IRIS_176
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_176[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"status_cenable_lcnt"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,12 ,"status_cenable_f1cnt"            },
};

/*----------------------------------------
	0x44c8 IRIS_177
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_177[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"status_updn_rst"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,4  ,"clampagc_updn"                   },
};

/*----------------------------------------
	0x44cc IRIS_178
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_178[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"status_updn"                     },
};

/*----------------------------------------
	0x44d0 IRIS_179
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_179[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs_secam_pll"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cs_secam_sw_old"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs_auto_secam_level"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"cs_chroma_activity_level"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"cs_adaptive_chroma_mode"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cs_sw_rst"                       },
};

/*----------------------------------------
	0x44d4 IRIS_180
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_180[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cs_phase_offset_range"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cs_avg_freq_range"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,12 ,"cs_issecam_th"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"cs_freq_offset_range"            },
};

/*----------------------------------------
	0x44d8 IRIS_181
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_181[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cs_db_freq"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"cs_dr_freq"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cs_ispal_th"                     },
};

/*----------------------------------------
	0x44dc IRIS_182
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_182[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs_cagc_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cs_chroma_burst5or10"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs_pal60_mode"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cs_ntsc443_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cs_colour_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"cs_adaptive_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"cs_secam_ybw"                    },
};

/*----------------------------------------
	0x44e0 IRIS_183
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_183[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cs_cagc_coring_threshold"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"cs_cagc_coring"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs_cagc_unity_gain"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cs_cagc_tc_p"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cs_cagc_tc_ibig"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"cs_cagc_tc_ismall"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cs_cagc"                         },
};

/*----------------------------------------
	0x44e4 IRIS_184
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_184[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"cs_chroma_bw_lo"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,4  ,"cs_ckill"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cs_hlock_ckill"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cs_vbi_ckill"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"cs_noburst_ckill"                },
};

/*----------------------------------------
	0x44e8 IRIS_185
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_185[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cs_cdto_inc"                     },
};

/*----------------------------------------
	0x44ec IRIS_186
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_186[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"cs_cstate"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cs_fixed_cstate"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cs_user_ckill_mode"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cs_lose_chromalock_mode"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cs_lose_chromalock_count"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"cs_lose_chromalock_level"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cs_lose_chromalock_ckill"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"cs_palsw_level"                  },
};

/*----------------------------------------
	0x44f0 IRIS_187
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_187[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs_chroma_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"cs_cphase_adjust"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs_cphase_adjust_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cs_mv_colourstripes_sel"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cs_cstripe_detect_control"       },
};

/*----------------------------------------
	0x44f4 IRIS_188
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_188[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs_secam_detected"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"cs_mv_colourstripes"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cs_status_cordic_freq"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"cs_status_burst_mag"             },
};

/*----------------------------------------
	0x44f8 IRIS_189
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_189[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs_chromalock"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,4  ,"cs_status_cgain"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"cs_status_cmag"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"cs_pal_detected"                 },
};

/*----------------------------------------
	0x44fc IRIS_190
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_190[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs1_secam_pll"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cs1_secam_sw_old"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs1_auto_secam_level"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"cs1_chroma_activity_level"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"cs1_adaptive_chroma_mode"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cs1_sw_rst"                      },
};

/*----------------------------------------
	0x4500 IRIS_191
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_191[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cs1_phase_offset_range"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cs1_avg_freq_range"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,12 ,"cs1_issecam_th"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"cs1_freq_offset_range"           },
};

/*----------------------------------------
	0x4504 IRIS_192
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_192[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cs1_db_freq"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"cs1_dr_freq"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cs1_ispal_th"                    },
};

/*----------------------------------------
	0x4508 IRIS_193
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_193[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs1_cagc_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cs1_chroma_burst5or10"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs1_pal60_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cs1_ntsc443_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cs1_colour_mode"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"cs1_adaptive_mode"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"cs1_secam_ybw"                   },
};

/*----------------------------------------
	0x450c IRIS_194
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_194[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cs1_cagc_coring_threshold"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"cs1_cagc_coring"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs1_cagc_unity_gain"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cs1_cagc_tc_p"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cs1_cagc_tc_ibig"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"cs1_cagc_tc_ismall"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cs1_cagc"                        },
};

/*----------------------------------------
	0x4510 IRIS_195
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_195[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"cs1_chroma_bw_lo"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,4  ,"cs1_ckill"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"cs1_hlock_ckill"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cs1_vbi_ckill"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"cs1_noburst_ckill"               },
};

/*----------------------------------------
	0x4514 IRIS_196
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_196[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cs1_cdto_inc"                    },
};

/*----------------------------------------
	0x4518 IRIS_197
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_197[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"cs1_cstate"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cs1_fixed_cstate"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"cs1_user_ckill_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"cs1_lose_chromalock_mode"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cs1_lose_chromalock_count"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"cs1_lose_chromalock_level"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cs1_lose_chromalock_ckill"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"cs1_palsw_level"                 },
};

/*----------------------------------------
	0x451c IRIS_198
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_198[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs1_chroma_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"cs1_cphase_adjust"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"cs1_cphase_adjust_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"cs1_mv_colourstripes_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"cs1_cstripe_detect_control"      },
};

/*----------------------------------------
	0x4520 IRIS_199
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_199[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs1_secam_detected"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"cs1_mv_colourstripes"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cs1_status_cordic_freq"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"cs1_status_burst_mag"            },
};

/*----------------------------------------
	0x4524 IRIS_200
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_200[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cs1_chromalock"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,4  ,"cs1_status_cgain"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"cs1_status_cmag"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"cs1_pal_detected"                },
};

/*----------------------------------------
	0x4528 IRIS_201
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_201[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"estfrdp_ctrl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"estfrdp_on"                      },
};

/*----------------------------------------
	0x452c IRIS_202
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_202[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,0  ,"estfrdp_tgt_cf0cnt"              },
};

/*----------------------------------------
	0x4530 IRIS_203
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_203[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,0  ,"estfrdp_tgt_cf1cnt"              },
};

/*----------------------------------------
	0x4534 IRIS_204
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_204[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"estfrdp_err_win1_u"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"estfrdp_err_win1_l"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"estfrdp_err_win0_u"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"estfrdp_err_win0_l"              },
};

/*----------------------------------------
	0x4538 IRIS_205
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_205[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"estfrdp_err_flag_th"             },
};

/*----------------------------------------
	0x453c IRIS_206
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_206[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"estfrdp_err"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"estfrdp_err_flag"                },
};

/*----------------------------------------
	0x4540 IRIS_207
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_207[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"vsync_width"                     },
};

/*----------------------------------------
	0x4544 IRIS_208
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_208[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl0"                  },
};

/*----------------------------------------
	0x4548 IRIS_209
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_209[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl1"                  },
};

/*----------------------------------------
	0x454c IRIS_210
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_210[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl2"                  },
};

/*----------------------------------------
	0x4550 IRIS_211
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_211[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl3"                  },
};

/*----------------------------------------
	0x4554 IRIS_212
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_212[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl4"                  },
};

/*----------------------------------------
	0x4558 IRIS_213
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_213[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl5"                  },
};

/*----------------------------------------
	0x455c IRIS_214
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_214[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl6"                  },
};

/*----------------------------------------
	0x4560 IRIS_215
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_215[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl7"                  },
};

/*----------------------------------------
	0x4564 IRIS_216
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_216[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl8"                  },
};

/*----------------------------------------
	0x4568 IRIS_217
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_217[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl9"                  },
};

/*----------------------------------------
	0x456c IRIS_218
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_218[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl10"                 },
};

/*----------------------------------------
	0x4570 IRIS_219
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_219[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl0"                  },
};

/*----------------------------------------
	0x4574 IRIS_220
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_220[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl1"                  },
};

/*----------------------------------------
	0x4578 IRIS_221
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_221[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl2"                  },
};

/*----------------------------------------
	0x457c IRIS_222
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_222[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl3"                  },
};

/*----------------------------------------
	0x4580 IRIS_223
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_223[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl4"                  },
};

/*----------------------------------------
	0x4584 IRIS_224
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_224[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl5"                  },
};

/*----------------------------------------
	0x4588 IRIS_225
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_225[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl6"                  },
};

/*----------------------------------------
	0x458c IRIS_226
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_226[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_ctrl7"                  },
};

/*----------------------------------------
	0x4590 IRIS_227
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_227[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl0"                  },
};

/*----------------------------------------
	0x4594 IRIS_228
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_228[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl1"                  },
};

/*----------------------------------------
	0x4598 IRIS_229
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_229[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl2"                  },
};

/*----------------------------------------
	0x459c IRIS_230
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_230[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl3"                  },
};

/*----------------------------------------
	0x45a0 IRIS_231
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_231[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl4"                  },
};

/*----------------------------------------
	0x45a4 IRIS_232
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_232[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl5"                  },
};

/*----------------------------------------
	0x45a8 IRIS_233
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_233[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl6"                  },
};

/*----------------------------------------
	0x45ac IRIS_234
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_234[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_st_ctrl7"                  },
};

/*----------------------------------------
	0x45b0 IRIS_235
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_235[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_blend_ctrl0"               },
};

/*----------------------------------------
	0x45b4 IRIS_236
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_236[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl11"                 },
};

/*----------------------------------------
	0x45b8 IRIS_237
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_237[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl12"                 },
};

/*----------------------------------------
	0x45bc IRIS_238
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_238[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl13"                 },
};

/*----------------------------------------
	0x45c0 IRIS_239
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_239[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl14"                 },
};

/*----------------------------------------
	0x45c4 IRIS_240
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_240[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl15"                 },
};

/*----------------------------------------
	0x45c8 IRIS_241
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_241[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl0"                     },
};

/*----------------------------------------
	0x45cc IRIS_242
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_242[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl1"                     },
};

/*----------------------------------------
	0x45d0 IRIS_243
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_243[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl2"                     },
};

/*----------------------------------------
	0x45d4 IRIS_244
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_244[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl3"                     },
};

/*----------------------------------------
	0x45d8 IRIS_245
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_245[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl4"                     },
};

/*----------------------------------------
	0x45dc IRIS_246
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_246[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl5"                     },
};

/*----------------------------------------
	0x45e0 IRIS_247
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_247[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl6"                     },
};

/*----------------------------------------
	0x45e4 IRIS_248
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_248[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl7"                     },
};

/*----------------------------------------
	0x45e8 IRIS_249
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_249[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl8"                     },
};

/*----------------------------------------
	0x45ec IRIS_250
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_250[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl9"                     },
};

/*----------------------------------------
	0x45f0 IRIS_251
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_251[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl10"                    },
};

/*----------------------------------------
	0x45f4 IRIS_252
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_252[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_0"              },
};

/*----------------------------------------
	0x45f8 IRIS_253
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_253[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_1"              },
};

/*----------------------------------------
	0x45fc IRIS_254
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_254[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_2"              },
};

/*----------------------------------------
	0x4600 IRIS_255
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_255[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_3"              },
};

/*----------------------------------------
	0x4604 IRIS_256
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_256[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_4"              },
};

/*----------------------------------------
	0x4608 IRIS_257
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_257[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_5"              },
};

/*----------------------------------------
	0x460c IRIS_258
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_258[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"hrs_cx2_coef2"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"hrs_cx2_coef1"                   },
};

/*----------------------------------------
	0x4610 IRIS_259
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_259[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"hrs_cx2_coef4"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"hrs_cx2_coef3"                   },
};

/*----------------------------------------
	0x4614 IRIS_260
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_260[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"hrs_cx2_coef6"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"hrs_cx2_coef5"                   },
};

/*----------------------------------------
	0x4618 IRIS_261
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_261[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"hrs_cx2_coef8"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"hrs_cx2_coef7"                   },
};

/*----------------------------------------
	0x461c IRIS_262
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_262[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"hrs_ha_width"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"hrs_ha_start"                    },
};

/*----------------------------------------
	0x4620 IRIS_263
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_263[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti0_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cti0_tap"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cti0_minmax_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,4  ,"cti0_gain"                       },
};

/*----------------------------------------
	0x4624 IRIS_264
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_264[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cti0_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"cti0_tap"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cti0_minmax_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,4  ,"cti0_gain"                       },
};

/*----------------------------------------
	0x4630 IRIS_265
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_265[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_3d_status0"                },
};

/*----------------------------------------
	0x4634 IRIS_266
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_266[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_6"              },
};

/*----------------------------------------
	0x4638 IRIS_267
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_267[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"cdetect_lpf_ctrl_7"              },
};

/*----------------------------------------
	0x463c IRIS_268
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_268[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycadjust_sat_ctrl_0"             },
};

/*----------------------------------------
	0x4640 IRIS_269
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_269[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl16"                 },
};

/*----------------------------------------
	0x4644 IRIS_270
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_270[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl17"                 },
};

/*----------------------------------------
	0x4648 IRIS_271
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_271[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"burst2_gate_end"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"burst2_gate_start"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"burst1_gate_end"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"burst1_gate_start"               },
};

/*----------------------------------------
	0x464c IRIS_272
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_272[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"cordic2_gate_end"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"cordic2_gate_start"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"cordic1_gate_end"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"cordic1_gate_start"              },
};

/*----------------------------------------
	0x4650 IRIS_273
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_273[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"secam_cbcr_ctrl"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"status_vdetect_vcount"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"vactive_height_auto"             },
};

/*----------------------------------------
	0x4654 IRIS_274
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_274[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"secam_y_notch_mode"              },
};

/*----------------------------------------
	0x4658 IRIS_275
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_275[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_2"            },
};

/*----------------------------------------
	0x465c IRIS_276
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_276[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_3"            },
};

/*----------------------------------------
	0x4660 IRIS_277
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_277[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_4"            },
};

/*----------------------------------------
	0x4664 IRIS_278
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_278[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_5"            },
};

/*----------------------------------------
	0x4668 IRIS_279
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_279[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_6"            },
};

/*----------------------------------------
	0x466c IRIS_280
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_280[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_7"            },
};

/*----------------------------------------
	0x4670 IRIS_281
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_281[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_8"            },
};

/*----------------------------------------
	0x4674 IRIS_282
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_282[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_y_notch_ctrl_9"            },
};

/*----------------------------------------
	0x4678 IRIS_283
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_283[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"secam_c_notch_sel"               },
};

/*----------------------------------------
	0x467c IRIS_284
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_284[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_2"            },
};

/*----------------------------------------
	0x4680 IRIS_285
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_285[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_3"            },
};

/*----------------------------------------
	0x4684 IRIS_286
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_286[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_4"            },
};

/*----------------------------------------
	0x4688 IRIS_287
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_287[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_5"            },
};

/*----------------------------------------
	0x468c IRIS_288
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_288[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_6"            },
};

/*----------------------------------------
	0x4690 IRIS_289
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_289[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_7"            },
};

/*----------------------------------------
	0x4694 IRIS_290
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_290[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_8"            },
};

/*----------------------------------------
	0x4698 IRIS_291
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_291[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,0  ,"secam_c_notch_ctrl_9"            },
};

/*----------------------------------------
	0x469c IRIS_292
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_292[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_ctrl11"                    },
};

/*----------------------------------------
	0x46a0 IRIS_293
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_293[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"secam_ybw2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,4  ,"secam_y_delay"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"secam_dcr_passthrough"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"v_valid_inv"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"secam_lb_en"                     },
};

/*----------------------------------------
	0x46a4 IRIS_294
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_294[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"secam_dcr_ctrl_0"                },
};

/*----------------------------------------
	0x46a8 IRIS_295
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_295[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"secam_dcr_ctrl_1"                },
};

/*----------------------------------------
	0x46ac IRIS_296
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_296[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"secam_dcr_ctrl_2"                },
};

/*----------------------------------------
	0x46b0 IRIS_297
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_297[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"yup_rise"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"ydn_cnt"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"yup_cnt"                         },
};

/*----------------------------------------
	0x46b4 IRIS_298
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_298[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"ydn_rise"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,12 ,"yup_fall"                        },
};

/*----------------------------------------
	0x46b8 IRIS_299
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_299[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"clmap_sel"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,4  ,"ydn_fall"                        },
};

/*----------------------------------------
	0x46bc IRIS_300
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_300[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl18"                 },
};

/*----------------------------------------
	0x46c0 IRIS_301
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_301[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl19"                 },
};

/*----------------------------------------
	0x46c4 IRIS_302
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_302[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"ycsep_2d_ctrl20"                 },
};

/*----------------------------------------
	0x46c8 IRIS_303
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_303[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"wmask_ctrl_0"                    },
};

/*----------------------------------------
	0x46cc IRIS_304
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_304[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"wmask_ctrl_1"                    },
};

/*----------------------------------------
	0x4800 VBI_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"wss625_rd_done"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cc_rd_done"                      },
};

/*----------------------------------------
	0x4804 VBI_002
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_002[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cc_rdy"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,4  ,"cc_data0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"cc_data1"                        },
};

/*----------------------------------------
	0x4808 VBI_003
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_003[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"wssdata0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"wssdata1"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"wssdata2"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"wss_rdy"                         },
};

/*----------------------------------------
	0x480c VBI_004
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_004[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"cc_short_start"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"vbi_muxout"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"vbi_hsyncout"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"adap_slvl_en"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"vbi_st_err_ignored"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"vbi_en"                          },
};

/*----------------------------------------
	0x4810 VBI_005
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_005[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vbi_lpf_bw"                      },
};

/*----------------------------------------
	0x4814 VBI_006
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_006[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbi_data_hlvl"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"start_code"                      },
};

/*----------------------------------------
	0x4818 VBI_007
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_007[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbil9"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vbil8"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vbil7"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vbil6"                           },
};

/*----------------------------------------
	0x481c VBI_008
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_008[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbil13"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vbil12"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vbil11"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vbil10"                          },
};

/*----------------------------------------
	0x4820 VBI_009
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_009[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbil17"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vbil16"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vbil15"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vbil14"                          },
};

/*----------------------------------------
	0x4824 VBI_010
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_010[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbil21"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vbil20"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vbil19"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vbil18"                          },
};

/*----------------------------------------
	0x4828 VBI_011
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_011[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbil25"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vbil24"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vbil23"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"vbil22"                          },
};

/*----------------------------------------
	0x482c VBI_012
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_012[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vbil26"                          },
};

/*----------------------------------------
	0x4830 VBI_013
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_013[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vbi_vps_lpfil_fine_gain"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"vbi_wss625_lpfil_fine_gain"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"vbi_tele_lpfil_fine_gain"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"vbi_cc_lpfil_fine_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"vbi_vps_slicer_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"vbi_wss_slicer_mode"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"vbi_tt_slicer_mode"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"vbi_cc_slicer_mode"              },
};

/*----------------------------------------
	0x4834 VBI_014
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_014[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"teletext_dto"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"caption_dto"                     },
};

/*----------------------------------------
	0x4838 VBI_015
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_015[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"vps_dto"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"wss625_dto"                      },
};

/*----------------------------------------
	0x483c VBI_016
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_016[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"vps_frame_start"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"teletext_frame_start"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"wss625_frame_start"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"caption_frame_start"             },
};

/*----------------------------------------
	0x4840 VBI_017
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_017[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"vbi_tele_lpfil_track_gain"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"vbi_tele_lpfil_acq_gain"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"vbi_cc_lpfil_track_gain"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"vbi_cc_lpfil_acq_gain"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"wssj_delta_ampl"                 },
};

/*----------------------------------------
	0x4844 VBI_018
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_018[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"vbi_vps_lpfil_track_gain"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"vbi_vps_lpfil_acq_gain"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"vbi_wss625_lpfil_track_gain"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"vbi_wss625_lpfil_acq_gain"       },
};

/*----------------------------------------
	0x4848 VBI_019
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_019[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"teletext_runin_accum_ampl"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"caption_runin_accum_ampl"        },
};

/*----------------------------------------
	0x484c VBI_020
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_020[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vps_start"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"teletext_start"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"wss625_start"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"caption_start"                   },
};

/*----------------------------------------
	0x4850 VBI_021
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_021[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"vbi_fixgate_en"                  },
};

/*----------------------------------------
	0x4854 VBI_022
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_022[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ttx_vbi_st_err_ignored"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"ttx_vbi_lpf_bw"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"ttx_vbi_hsyncout"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,12 ,"ttx_vbi_data_hlvl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"ttx_adap_slvl_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"ttx_vbi_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"ttx_out_sel"                     },
};

/*----------------------------------------
	0x4858 VBI_023
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_023[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ttx_teletext_start"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"ttx_vbi_tele_lpfil_fine_gain"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"ttx_vbi_tele_lpfil_track_gain"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"ttx_vbi_tele_lpfil_acq_gain"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,20 ,"ttx_teletext_runin_accum_ampl"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"ttx_tt_slicer_mode"              },
};

/*----------------------------------------
	0x485c VBI_024
----------------------------------------*/
const DBG_REG_FIELD_T dbg_VBI_024[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ttx_start_code"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"ttx_teletext_frame_start"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,12 ,"ttx_teletext_dto"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"ttx_vbi_fixgate_en"              },
};

/*----------------------------------------
	0x48a8 IRIS_MIF_GMUA_MON_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"ro_rbuf2_pel_cnt"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ro_rbuf2_empty"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"ro_rbuf1_pel_cnt"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"ro_rbuf1_empty"                  },
};

/*----------------------------------------
	0x48ac IRIS_MIF_GMUA_MON_002
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_002[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"ro_rbuf4_pel_cnt"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ro_rbuf4_empty"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"ro_rbuf3_pel_cnt"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"ro_rbuf3_empty"                  },
};

/*----------------------------------------
	0x48b0 IRIS_MIF_GMUA_MON_003
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_003[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,0  ,"ro_wbuf_word_cnt"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"ro_wbuf_empty"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ro_wbuf_full"                    },
};

/*----------------------------------------
	0x48b4 IRIS_MIF_GMUA_MON_004
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_004[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mon_wait_max_cnt"                },
};

/*----------------------------------------
	0x48b8 IRIS_MIF_GMUA_MON_005
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_005[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ro_mon_wr_wait_err"              },
};

/*----------------------------------------
	0x48bc IRIS_MIF_GMUA_MON_006
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_006[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ro_mon_rd4_wait_err"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"ro_mon_rd3_wait_err"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"ro_mon_rd2_wait_err"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"ro_mon_rd1_wait_err"             },
};

/*----------------------------------------
	0x48c0 IRIS_MIF_GMUA_MON_007
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_007[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"ro_mon_wr_req_num"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"ro_mon_wr_req_que_cnt"           },
};

/*----------------------------------------
	0x48c4 IRIS_MIF_GMUA_MON_008
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_008[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_wr_wait_cnt1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_wr_wait_cnt0"             },
};

/*----------------------------------------
	0x48c8 IRIS_MIF_GMUA_MON_009
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_009[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_wr_wait_cnt3"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_wr_wait_cnt2"             },
};

/*----------------------------------------
	0x48cc IRIS_MIF_GMUA_MON_010
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_010[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"ro_mon_rd1_req_num"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"ro_mon_rd1_req_que_cnt"          },
};

/*----------------------------------------
	0x48d0 IRIS_MIF_GMUA_MON_011
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_011[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd1_wait_cnt1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_rd1_wait_cnt0"            },
};

/*----------------------------------------
	0x48d4 IRIS_MIF_GMUA_MON_012
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_012[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd1_wait_cnt3"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_rd1_wait_cnt2"            },
};

/*----------------------------------------
	0x48d8 IRIS_MIF_GMUA_MON_013
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_013[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"ro_mon_rd2_req_num"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"ro_mon_rd2_req_que_cnt"          },
};

/*----------------------------------------
	0x48dc IRIS_MIF_GMUA_MON_014
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_014[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd2_wait_cnt1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_rd2_wait_cnt0"            },
};

/*----------------------------------------
	0x48e0 IRIS_MIF_GMUA_MON_015
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_015[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd2_wait_cnt3"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_rd2_wait_cnt2"            },
};

/*----------------------------------------
	0x48e4 IRIS_MIF_GMUA_MON_016
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_016[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"ro_mon_rd3_req_num"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"ro_mon_rd3_req_que_cnt"          },
};

/*----------------------------------------
	0x48e8 IRIS_MIF_GMUA_MON_017
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_017[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd3_wait_cnt1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_rd3_wait_cnt0"            },
};

/*----------------------------------------
	0x48ec IRIS_MIF_GMUA_MON_018
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_018[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd3_wait_cnt3"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_rd3_wait_cnt2"            },
};

/*----------------------------------------
	0x48f0 IRIS_MIF_GMUA_MON_019
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_019[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"ro_mon_rd4_req_num"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"ro_mon_rd4_req_que_cnt"          },
};

/*----------------------------------------
	0x48f4 IRIS_MIF_GMUA_MON_020
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_020[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd4_wait_cnt0"            },
};

/*----------------------------------------
	0x48f8 IRIS_MIF_GMUA_MON_021
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_021[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd4_wait_cnt1"            },
};

/*----------------------------------------
	0x48fc IRIS_MIF_GMUA_MON_022
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_MIF_GMUA_MON_022[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"ro_mon_rd4_wait_cnt3"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,12 ,"ro_mon_rd4_wait_cnt2"            },
};

/*----------------------------------------
	0x4900 IRIS_HIF_CTRL0_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_HIF_CTRL0_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pending_enable"                  },
};

/*----------------------------------------
	0x4904 IRIS_HIF_CTRL1_001
----------------------------------------*/
const DBG_REG_FIELD_T dbg_IRIS_HIF_CTRL1_001[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,0  ,"cv_timer_ctrl"                   },
};

DBG_REG_T gDbgRegCVD[] = {
	{ 0x4100 ,N_FLD(dbg_CVD_INTR1_ENABLE0)           ,"CVD_INTR1_ENABLE0"             ,dbg_CVD_INTR1_ENABLE0           },
	{ 0x4104 ,N_FLD(dbg_CVD_INTR1_INTR0)             ,"CVD_INTR1_INTR0"               ,dbg_CVD_INTR1_INTR0             },
	{ 0x4108 ,N_FLD(dbg_CVD_INTR1_CLEAR0)            ,"CVD_INTR1_CLEAR0"              ,dbg_CVD_INTR1_CLEAR0            },
	{ 0x410c ,N_FLD(dbg_CVD_INTR1_ENABLE1)           ,"CVD_INTR1_ENABLE1"             ,dbg_CVD_INTR1_ENABLE1           },
	{ 0x4110 ,N_FLD(dbg_CVD_INTR1_INTR1)             ,"CVD_INTR1_INTR1"               ,dbg_CVD_INTR1_INTR1             },
	{ 0x4114 ,N_FLD(dbg_CVD_INTR1_CLEAR1)            ,"CVD_INTR1_CLEAR1"              ,dbg_CVD_INTR1_CLEAR1            },
	{ 0x4118 ,N_FLD(dbg_CVD_INTR2_ENABLE0)           ,"CVD_INTR2_ENABLE0"             ,dbg_CVD_INTR2_ENABLE0           },
	{ 0x411c ,N_FLD(dbg_CVD_INTR2_INTR0)             ,"CVD_INTR2_INTR0"               ,dbg_CVD_INTR2_INTR0             },
	{ 0x4120 ,N_FLD(dbg_CVD_INTR2_CLEAR0)            ,"CVD_INTR2_CLEAR0"              ,dbg_CVD_INTR2_CLEAR0            },
	{ 0x4124 ,N_FLD(dbg_CVD_INTR2_ENABLE1)           ,"CVD_INTR2_ENABLE1"             ,dbg_CVD_INTR2_ENABLE1           },
	{ 0x4128 ,N_FLD(dbg_CVD_INTR2_INTR1)             ,"CVD_INTR2_INTR1"               ,dbg_CVD_INTR2_INTR1             },
	{ 0x412c ,N_FLD(dbg_CVD_INTR2_CLEAR1)            ,"CVD_INTR2_CLEAR1"              ,dbg_CVD_INTR2_CLEAR1            },
	{ 0x4130 ,N_FLD(dbg_TOP_001)                     ,"TOP_001"                       ,dbg_TOP_001                     },
	{ 0x4140 ,N_FLD(dbg_IRIS_MIF_GMUA_001)           ,"IRIS_MIF_GMUA_001"             ,dbg_IRIS_MIF_GMUA_001           },
	{ 0x4144 ,N_FLD(dbg_IRIS_MIF_GMUA_002)           ,"IRIS_MIF_GMUA_002"             ,dbg_IRIS_MIF_GMUA_002           },
	{ 0x4148 ,N_FLD(dbg_IRIS_MIF_GMUA_003)           ,"IRIS_MIF_GMUA_003"             ,dbg_IRIS_MIF_GMUA_003           },
	{ 0x414c ,N_FLD(dbg_IRIS_MIF_GMUA_004)           ,"IRIS_MIF_GMUA_004"             ,dbg_IRIS_MIF_GMUA_004           },
	{ 0x4150 ,N_FLD(dbg_IRIS_MIF_GMUA_005)           ,"IRIS_MIF_GMUA_005"             ,dbg_IRIS_MIF_GMUA_005           },
	{ 0x4154 ,N_FLD(dbg_IRIS_MIF_GMUA_006)           ,"IRIS_MIF_GMUA_006"             ,dbg_IRIS_MIF_GMUA_006           },
	{ 0x4158 ,N_FLD(dbg_IRIS_MIF_GMUA_007)           ,"IRIS_MIF_GMUA_007"             ,dbg_IRIS_MIF_GMUA_007           },
	{ 0x4160 ,N_FLD(dbg_IRIS_MIF_GMUA_008)           ,"IRIS_MIF_GMUA_008"             ,dbg_IRIS_MIF_GMUA_008           },
	{ 0x4164 ,N_FLD(dbg_IRIS_MIF_GMUA_009)           ,"IRIS_MIF_GMUA_009"             ,dbg_IRIS_MIF_GMUA_009           },
	{ 0x4168 ,N_FLD(dbg_FASTBLANK_001)               ,"FASTBLANK_001"                 ,dbg_FASTBLANK_001               },
	{ 0x416c ,N_FLD(dbg_FASTBLANK_002)               ,"FASTBLANK_002"                 ,dbg_FASTBLANK_002               },
	{ 0x4170 ,N_FLD(dbg_FASTBLANK_003)               ,"FASTBLANK_003"                 ,dbg_FASTBLANK_003               },
	{ 0x4174 ,N_FLD(dbg_FASTBLANK_004)               ,"FASTBLANK_004"                 ,dbg_FASTBLANK_004               },
	{ 0x4178 ,N_FLD(dbg_FASTBLANK_005)               ,"FASTBLANK_005"                 ,dbg_FASTBLANK_005               },
	{ 0x417c ,N_FLD(dbg_FASTBLANK_006)               ,"FASTBLANK_006"                 ,dbg_FASTBLANK_006               },
	{ 0x4180 ,N_FLD(dbg_FASTBLANK_007)               ,"FASTBLANK_007"                 ,dbg_FASTBLANK_007               },
	{ 0x4184 ,N_FLD(dbg_FASTBLANK_008)               ,"FASTBLANK_008"                 ,dbg_FASTBLANK_008               },
	{ 0x4188 ,N_FLD(dbg_FASTBLANK_009)               ,"FASTBLANK_009"                 ,dbg_FASTBLANK_009               },
	{ 0x418c ,N_FLD(dbg_FASTBLANK_010)               ,"FASTBLANK_010"                 ,dbg_FASTBLANK_010               },
	{ 0x4190 ,N_FLD(dbg_IRIS_DE_CTRL_001)            ,"IRIS_DE_CTRL_001"              ,dbg_IRIS_DE_CTRL_001            },
	{ 0x4194 ,N_FLD(dbg_VBI_CTRL_001)                ,"VBI_CTRL_001"                  ,dbg_VBI_CTRL_001                },
	{ 0x4198 ,N_FLD(dbg_VBI_CTRL_002)                ,"VBI_CTRL_002"                  ,dbg_VBI_CTRL_002                },
	{ 0x419c ,N_FLD(dbg_VBI_CTRL_003)                ,"VBI_CTRL_003"                  ,dbg_VBI_CTRL_003                },
	{ 0x41a0 ,N_FLD(dbg_VBI_CTRL_004)                ,"VBI_CTRL_004"                  ,dbg_VBI_CTRL_004                },
	{ 0x41a4 ,N_FLD(dbg_VBI_CTRL_005)                ,"VBI_CTRL_005"                  ,dbg_VBI_CTRL_005                },
	{ 0x41a8 ,N_FLD(dbg_VBI_CTRL_006)                ,"VBI_CTRL_006"                  ,dbg_VBI_CTRL_006                },
	{ 0x41ac ,N_FLD(dbg_VBI_CTRL_007)                ,"VBI_CTRL_007"                  ,dbg_VBI_CTRL_007                },
	{ 0x41b0 ,N_FLD(dbg_VBI_CTRL_008)                ,"VBI_CTRL_008"                  ,dbg_VBI_CTRL_008                },
	{ 0x41b4 ,N_FLD(dbg_VBI_CTRL_009)                ,"VBI_CTRL_009"                  ,dbg_VBI_CTRL_009                },
	{ 0x41c0 ,N_FLD(dbg_FAST_BLANK_STATUS_001)       ,"FAST_BLANK_STATUS_001"         ,dbg_FAST_BLANK_STATUS_001       },
	{ 0x41c4 ,N_FLD(dbg_CVBSAFE_001)                 ,"CVBSAFE_001"                   ,dbg_CVBSAFE_001                 },
	{ 0x4200 ,N_FLD(dbg_IRIS_001)                    ,"IRIS_001"                      ,dbg_IRIS_001                    },
	{ 0x4204 ,N_FLD(dbg_IRIS_002)                    ,"IRIS_002"                      ,dbg_IRIS_002                    },
	{ 0x4208 ,N_FLD(dbg_IRIS_003)                    ,"IRIS_003"                      ,dbg_IRIS_003                    },
	{ 0x420c ,N_FLD(dbg_IRIS_004)                    ,"IRIS_004"                      ,dbg_IRIS_004                    },
	{ 0x4210 ,N_FLD(dbg_IRIS_005)                    ,"IRIS_005"                      ,dbg_IRIS_005                    },
	{ 0x4214 ,N_FLD(dbg_IRIS_006)                    ,"IRIS_006"                      ,dbg_IRIS_006                    },
	{ 0x4218 ,N_FLD(dbg_IRIS_007)                    ,"IRIS_007"                      ,dbg_IRIS_007                    },
	{ 0x421c ,N_FLD(dbg_IRIS_008)                    ,"IRIS_008"                      ,dbg_IRIS_008                    },
	{ 0x4220 ,N_FLD(dbg_IRIS_009)                    ,"IRIS_009"                      ,dbg_IRIS_009                    },
	{ 0x4224 ,N_FLD(dbg_IRIS_010)                    ,"IRIS_010"                      ,dbg_IRIS_010                    },
	{ 0x4230 ,N_FLD(dbg_IRIS_011)                    ,"IRIS_011"                      ,dbg_IRIS_011                    },
	{ 0x4234 ,N_FLD(dbg_IRIS_012)                    ,"IRIS_012"                      ,dbg_IRIS_012                    },
	{ 0x4238 ,N_FLD(dbg_IRIS_013)                    ,"IRIS_013"                      ,dbg_IRIS_013                    },
	{ 0x423c ,N_FLD(dbg_IRIS_014)                    ,"IRIS_014"                      ,dbg_IRIS_014                    },
	{ 0x4240 ,N_FLD(dbg_IRIS_015)                    ,"IRIS_015"                      ,dbg_IRIS_015                    },
	{ 0x4244 ,N_FLD(dbg_IRIS_016)                    ,"IRIS_016"                      ,dbg_IRIS_016                    },
	{ 0x4248 ,N_FLD(dbg_IRIS_017)                    ,"IRIS_017"                      ,dbg_IRIS_017                    },
	{ 0x424c ,N_FLD(dbg_IRIS_018)                    ,"IRIS_018"                      ,dbg_IRIS_018                    },
	{ 0x4250 ,N_FLD(dbg_IRIS_019)                    ,"IRIS_019"                      ,dbg_IRIS_019                    },
	{ 0x4254 ,N_FLD(dbg_IRIS_020)                    ,"IRIS_020"                      ,dbg_IRIS_020                    },
	{ 0x4258 ,N_FLD(dbg_IRIS_021)                    ,"IRIS_021"                      ,dbg_IRIS_021                    },
	{ 0x425c ,N_FLD(dbg_IRIS_022)                    ,"IRIS_022"                      ,dbg_IRIS_022                    },
	{ 0x4260 ,N_FLD(dbg_IRIS_023)                    ,"IRIS_023"                      ,dbg_IRIS_023                    },
	{ 0x4264 ,N_FLD(dbg_IRIS_024)                    ,"IRIS_024"                      ,dbg_IRIS_024                    },
	{ 0x4268 ,N_FLD(dbg_IRIS_025)                    ,"IRIS_025"                      ,dbg_IRIS_025                    },
	{ 0x426c ,N_FLD(dbg_IRIS_026)                    ,"IRIS_026"                      ,dbg_IRIS_026                    },
	{ 0x4270 ,N_FLD(dbg_IRIS_027)                    ,"IRIS_027"                      ,dbg_IRIS_027                    },
	{ 0x4274 ,N_FLD(dbg_IRIS_028)                    ,"IRIS_028"                      ,dbg_IRIS_028                    },
	{ 0x4278 ,N_FLD(dbg_IRIS_029)                    ,"IRIS_029"                      ,dbg_IRIS_029                    },
	{ 0x427c ,N_FLD(dbg_IRIS_030)                    ,"IRIS_030"                      ,dbg_IRIS_030                    },
	{ 0x4280 ,N_FLD(dbg_IRIS_031)                    ,"IRIS_031"                      ,dbg_IRIS_031                    },
	{ 0x4284 ,N_FLD(dbg_IRIS_032)                    ,"IRIS_032"                      ,dbg_IRIS_032                    },
	{ 0x4288 ,N_FLD(dbg_IRIS_033)                    ,"IRIS_033"                      ,dbg_IRIS_033                    },
	{ 0x428c ,N_FLD(dbg_IRIS_034)                    ,"IRIS_034"                      ,dbg_IRIS_034                    },
	{ 0x4290 ,N_FLD(dbg_IRIS_035)                    ,"IRIS_035"                      ,dbg_IRIS_035                    },
	{ 0x4294 ,N_FLD(dbg_IRIS_036)                    ,"IRIS_036"                      ,dbg_IRIS_036                    },
	{ 0x4298 ,N_FLD(dbg_IRIS_037)                    ,"IRIS_037"                      ,dbg_IRIS_037                    },
	{ 0x429c ,N_FLD(dbg_IRIS_038)                    ,"IRIS_038"                      ,dbg_IRIS_038                    },
	{ 0x42a0 ,N_FLD(dbg_IRIS_039)                    ,"IRIS_039"                      ,dbg_IRIS_039                    },
	{ 0x42a4 ,N_FLD(dbg_IRIS_040)                    ,"IRIS_040"                      ,dbg_IRIS_040                    },
	{ 0x42a8 ,N_FLD(dbg_IRIS_041)                    ,"IRIS_041"                      ,dbg_IRIS_041                    },
	{ 0x42ac ,N_FLD(dbg_IRIS_042)                    ,"IRIS_042"                      ,dbg_IRIS_042                    },
	{ 0x42b0 ,N_FLD(dbg_IRIS_043)                    ,"IRIS_043"                      ,dbg_IRIS_043                    },
	{ 0x42b4 ,N_FLD(dbg_IRIS_044)                    ,"IRIS_044"                      ,dbg_IRIS_044                    },
	{ 0x42b8 ,N_FLD(dbg_IRIS_045)                    ,"IRIS_045"                      ,dbg_IRIS_045                    },
	{ 0x42bc ,N_FLD(dbg_IRIS_046)                    ,"IRIS_046"                      ,dbg_IRIS_046                    },
	{ 0x42c0 ,N_FLD(dbg_IRIS_047)                    ,"IRIS_047"                      ,dbg_IRIS_047                    },
	{ 0x42c4 ,N_FLD(dbg_IRIS_048)                    ,"IRIS_048"                      ,dbg_IRIS_048                    },
	{ 0x42c8 ,N_FLD(dbg_IRIS_049)                    ,"IRIS_049"                      ,dbg_IRIS_049                    },
	{ 0x42cc ,N_FLD(dbg_IRIS_050)                    ,"IRIS_050"                      ,dbg_IRIS_050                    },
	{ 0x42d0 ,N_FLD(dbg_IRIS_051)                    ,"IRIS_051"                      ,dbg_IRIS_051                    },
	{ 0x42d4 ,N_FLD(dbg_IRIS_052)                    ,"IRIS_052"                      ,dbg_IRIS_052                    },
	{ 0x42d8 ,N_FLD(dbg_IRIS_053)                    ,"IRIS_053"                      ,dbg_IRIS_053                    },
	{ 0x42dc ,N_FLD(dbg_IRIS_054)                    ,"IRIS_054"                      ,dbg_IRIS_054                    },
	{ 0x42e0 ,N_FLD(dbg_IRIS_055)                    ,"IRIS_055"                      ,dbg_IRIS_055                    },
	{ 0x42e4 ,N_FLD(dbg_IRIS_056)                    ,"IRIS_056"                      ,dbg_IRIS_056                    },
	{ 0x42e8 ,N_FLD(dbg_IRIS_057)                    ,"IRIS_057"                      ,dbg_IRIS_057                    },
	{ 0x42ec ,N_FLD(dbg_IRIS_058)                    ,"IRIS_058"                      ,dbg_IRIS_058                    },
	{ 0x42f0 ,N_FLD(dbg_IRIS_059)                    ,"IRIS_059"                      ,dbg_IRIS_059                    },
	{ 0x42f4 ,N_FLD(dbg_IRIS_060)                    ,"IRIS_060"                      ,dbg_IRIS_060                    },
	{ 0x42f8 ,N_FLD(dbg_IRIS_061)                    ,"IRIS_061"                      ,dbg_IRIS_061                    },
	{ 0x42fc ,N_FLD(dbg_IRIS_062)                    ,"IRIS_062"                      ,dbg_IRIS_062                    },
	{ 0x4300 ,N_FLD(dbg_IRIS_063)                    ,"IRIS_063"                      ,dbg_IRIS_063                    },
	{ 0x4304 ,N_FLD(dbg_IRIS_064)                    ,"IRIS_064"                      ,dbg_IRIS_064                    },
	{ 0x4308 ,N_FLD(dbg_IRIS_065)                    ,"IRIS_065"                      ,dbg_IRIS_065                    },
	{ 0x430c ,N_FLD(dbg_IRIS_066)                    ,"IRIS_066"                      ,dbg_IRIS_066                    },
	{ 0x4310 ,N_FLD(dbg_IRIS_067)                    ,"IRIS_067"                      ,dbg_IRIS_067                    },
	{ 0x4314 ,N_FLD(dbg_IRIS_068)                    ,"IRIS_068"                      ,dbg_IRIS_068                    },
	{ 0x4318 ,N_FLD(dbg_IRIS_069)                    ,"IRIS_069"                      ,dbg_IRIS_069                    },
	{ 0x431c ,N_FLD(dbg_IRIS_070)                    ,"IRIS_070"                      ,dbg_IRIS_070                    },
	{ 0x4320 ,N_FLD(dbg_IRIS_071)                    ,"IRIS_071"                      ,dbg_IRIS_071                    },
	{ 0x4324 ,N_FLD(dbg_IRIS_072)                    ,"IRIS_072"                      ,dbg_IRIS_072                    },
	{ 0x4328 ,N_FLD(dbg_IRIS_073)                    ,"IRIS_073"                      ,dbg_IRIS_073                    },
	{ 0x432c ,N_FLD(dbg_IRIS_074)                    ,"IRIS_074"                      ,dbg_IRIS_074                    },
	{ 0x4330 ,N_FLD(dbg_IRIS_075)                    ,"IRIS_075"                      ,dbg_IRIS_075                    },
	{ 0x4334 ,N_FLD(dbg_IRIS_076)                    ,"IRIS_076"                      ,dbg_IRIS_076                    },
	{ 0x4338 ,N_FLD(dbg_IRIS_077)                    ,"IRIS_077"                      ,dbg_IRIS_077                    },
	{ 0x433c ,N_FLD(dbg_IRIS_078)                    ,"IRIS_078"                      ,dbg_IRIS_078                    },
	{ 0x4340 ,N_FLD(dbg_IRIS_079)                    ,"IRIS_079"                      ,dbg_IRIS_079                    },
	{ 0x4344 ,N_FLD(dbg_IRIS_080)                    ,"IRIS_080"                      ,dbg_IRIS_080                    },
	{ 0x4348 ,N_FLD(dbg_IRIS_081)                    ,"IRIS_081"                      ,dbg_IRIS_081                    },
	{ 0x434c ,N_FLD(dbg_IRIS_082)                    ,"IRIS_082"                      ,dbg_IRIS_082                    },
	{ 0x4350 ,N_FLD(dbg_IRIS_083)                    ,"IRIS_083"                      ,dbg_IRIS_083                    },
	{ 0x4354 ,N_FLD(dbg_IRIS_084)                    ,"IRIS_084"                      ,dbg_IRIS_084                    },
	{ 0x4358 ,N_FLD(dbg_IRIS_085)                    ,"IRIS_085"                      ,dbg_IRIS_085                    },
	{ 0x435c ,N_FLD(dbg_IRIS_086)                    ,"IRIS_086"                      ,dbg_IRIS_086                    },
	{ 0x4360 ,N_FLD(dbg_IRIS_087)                    ,"IRIS_087"                      ,dbg_IRIS_087                    },
	{ 0x4364 ,N_FLD(dbg_IRIS_088)                    ,"IRIS_088"                      ,dbg_IRIS_088                    },
	{ 0x4368 ,N_FLD(dbg_IRIS_089)                    ,"IRIS_089"                      ,dbg_IRIS_089                    },
	{ 0x436c ,N_FLD(dbg_IRIS_090)                    ,"IRIS_090"                      ,dbg_IRIS_090                    },
	{ 0x4370 ,N_FLD(dbg_IRIS_091)                    ,"IRIS_091"                      ,dbg_IRIS_091                    },
	{ 0x4374 ,N_FLD(dbg_IRIS_092)                    ,"IRIS_092"                      ,dbg_IRIS_092                    },
	{ 0x4378 ,N_FLD(dbg_IRIS_093)                    ,"IRIS_093"                      ,dbg_IRIS_093                    },
	{ 0x437c ,N_FLD(dbg_IRIS_094)                    ,"IRIS_094"                      ,dbg_IRIS_094                    },
	{ 0x4380 ,N_FLD(dbg_IRIS_095)                    ,"IRIS_095"                      ,dbg_IRIS_095                    },
	{ 0x4384 ,N_FLD(dbg_IRIS_096)                    ,"IRIS_096"                      ,dbg_IRIS_096                    },
	{ 0x4388 ,N_FLD(dbg_IRIS_097)                    ,"IRIS_097"                      ,dbg_IRIS_097                    },
	{ 0x438c ,N_FLD(dbg_IRIS_098)                    ,"IRIS_098"                      ,dbg_IRIS_098                    },
	{ 0x4390 ,N_FLD(dbg_IRIS_099)                    ,"IRIS_099"                      ,dbg_IRIS_099                    },
	{ 0x4394 ,N_FLD(dbg_IRIS_100)                    ,"IRIS_100"                      ,dbg_IRIS_100                    },
	{ 0x4398 ,N_FLD(dbg_IRIS_101)                    ,"IRIS_101"                      ,dbg_IRIS_101                    },
	{ 0x439c ,N_FLD(dbg_IRIS_102)                    ,"IRIS_102"                      ,dbg_IRIS_102                    },
	{ 0x43a0 ,N_FLD(dbg_IRIS_103)                    ,"IRIS_103"                      ,dbg_IRIS_103                    },
	{ 0x43a4 ,N_FLD(dbg_IRIS_104)                    ,"IRIS_104"                      ,dbg_IRIS_104                    },
	{ 0x43a8 ,N_FLD(dbg_IRIS_105)                    ,"IRIS_105"                      ,dbg_IRIS_105                    },
	{ 0x43ac ,N_FLD(dbg_IRIS_106)                    ,"IRIS_106"                      ,dbg_IRIS_106                    },
	{ 0x43b0 ,N_FLD(dbg_IRIS_107)                    ,"IRIS_107"                      ,dbg_IRIS_107                    },
	{ 0x43b4 ,N_FLD(dbg_IRIS_108)                    ,"IRIS_108"                      ,dbg_IRIS_108                    },
	{ 0x43b8 ,N_FLD(dbg_IRIS_109)                    ,"IRIS_109"                      ,dbg_IRIS_109                    },
	{ 0x43bc ,N_FLD(dbg_IRIS_110)                    ,"IRIS_110"                      ,dbg_IRIS_110                    },
	{ 0x43c0 ,N_FLD(dbg_IRIS_111)                    ,"IRIS_111"                      ,dbg_IRIS_111                    },
	{ 0x43c4 ,N_FLD(dbg_IRIS_112)                    ,"IRIS_112"                      ,dbg_IRIS_112                    },
	{ 0x43c8 ,N_FLD(dbg_IRIS_113)                    ,"IRIS_113"                      ,dbg_IRIS_113                    },
	{ 0x43cc ,N_FLD(dbg_IRIS_114)                    ,"IRIS_114"                      ,dbg_IRIS_114                    },
	{ 0x43d0 ,N_FLD(dbg_IRIS_115)                    ,"IRIS_115"                      ,dbg_IRIS_115                    },
	{ 0x43d4 ,N_FLD(dbg_IRIS_116)                    ,"IRIS_116"                      ,dbg_IRIS_116                    },
	{ 0x43d8 ,N_FLD(dbg_IRIS_117)                    ,"IRIS_117"                      ,dbg_IRIS_117                    },
	{ 0x43dc ,N_FLD(dbg_IRIS_118)                    ,"IRIS_118"                      ,dbg_IRIS_118                    },
	{ 0x43e0 ,N_FLD(dbg_IRIS_119)                    ,"IRIS_119"                      ,dbg_IRIS_119                    },
	{ 0x43e4 ,N_FLD(dbg_IRIS_120)                    ,"IRIS_120"                      ,dbg_IRIS_120                    },
	{ 0x43e8 ,N_FLD(dbg_IRIS_121)                    ,"IRIS_121"                      ,dbg_IRIS_121                    },
	{ 0x43ec ,N_FLD(dbg_IRIS_122)                    ,"IRIS_122"                      ,dbg_IRIS_122                    },
	{ 0x43f0 ,N_FLD(dbg_IRIS_123)                    ,"IRIS_123"                      ,dbg_IRIS_123                    },
	{ 0x43f4 ,N_FLD(dbg_IRIS_124)                    ,"IRIS_124"                      ,dbg_IRIS_124                    },
	{ 0x43f8 ,N_FLD(dbg_IRIS_125)                    ,"IRIS_125"                      ,dbg_IRIS_125                    },
	{ 0x43fc ,N_FLD(dbg_IRIS_126)                    ,"IRIS_126"                      ,dbg_IRIS_126                    },
	{ 0x4400 ,N_FLD(dbg_IRIS_127)                    ,"IRIS_127"                      ,dbg_IRIS_127                    },
	{ 0x4404 ,N_FLD(dbg_IRIS_128)                    ,"IRIS_128"                      ,dbg_IRIS_128                    },
	{ 0x4408 ,N_FLD(dbg_IRIS_129)                    ,"IRIS_129"                      ,dbg_IRIS_129                    },
	{ 0x440c ,N_FLD(dbg_IRIS_130)                    ,"IRIS_130"                      ,dbg_IRIS_130                    },
	{ 0x4410 ,N_FLD(dbg_IRIS_131)                    ,"IRIS_131"                      ,dbg_IRIS_131                    },
	{ 0x4414 ,N_FLD(dbg_IRIS_132)                    ,"IRIS_132"                      ,dbg_IRIS_132                    },
	{ 0x4418 ,N_FLD(dbg_IRIS_133)                    ,"IRIS_133"                      ,dbg_IRIS_133                    },
	{ 0x441c ,N_FLD(dbg_IRIS_134)                    ,"IRIS_134"                      ,dbg_IRIS_134                    },
	{ 0x4420 ,N_FLD(dbg_IRIS_135)                    ,"IRIS_135"                      ,dbg_IRIS_135                    },
	{ 0x4424 ,N_FLD(dbg_IRIS_136)                    ,"IRIS_136"                      ,dbg_IRIS_136                    },
	{ 0x4428 ,N_FLD(dbg_IRIS_137)                    ,"IRIS_137"                      ,dbg_IRIS_137                    },
	{ 0x442c ,N_FLD(dbg_IRIS_138)                    ,"IRIS_138"                      ,dbg_IRIS_138                    },
	{ 0x4430 ,N_FLD(dbg_IRIS_139)                    ,"IRIS_139"                      ,dbg_IRIS_139                    },
	{ 0x4434 ,N_FLD(dbg_IRIS_140)                    ,"IRIS_140"                      ,dbg_IRIS_140                    },
	{ 0x4438 ,N_FLD(dbg_IRIS_141)                    ,"IRIS_141"                      ,dbg_IRIS_141                    },
	{ 0x443c ,N_FLD(dbg_IRIS_142)                    ,"IRIS_142"                      ,dbg_IRIS_142                    },
	{ 0x4440 ,N_FLD(dbg_IRIS_143)                    ,"IRIS_143"                      ,dbg_IRIS_143                    },
	{ 0x4444 ,N_FLD(dbg_IRIS_144)                    ,"IRIS_144"                      ,dbg_IRIS_144                    },
	{ 0x4448 ,N_FLD(dbg_IRIS_145)                    ,"IRIS_145"                      ,dbg_IRIS_145                    },
	{ 0x444c ,N_FLD(dbg_IRIS_146)                    ,"IRIS_146"                      ,dbg_IRIS_146                    },
	{ 0x4450 ,N_FLD(dbg_IRIS_147)                    ,"IRIS_147"                      ,dbg_IRIS_147                    },
	{ 0x4454 ,N_FLD(dbg_IRIS_148)                    ,"IRIS_148"                      ,dbg_IRIS_148                    },
	{ 0x4458 ,N_FLD(dbg_IRIS_149)                    ,"IRIS_149"                      ,dbg_IRIS_149                    },
	{ 0x445c ,N_FLD(dbg_IRIS_150)                    ,"IRIS_150"                      ,dbg_IRIS_150                    },
	{ 0x4460 ,N_FLD(dbg_IRIS_151)                    ,"IRIS_151"                      ,dbg_IRIS_151                    },
	{ 0x4464 ,N_FLD(dbg_IRIS_152)                    ,"IRIS_152"                      ,dbg_IRIS_152                    },
	{ 0x4468 ,N_FLD(dbg_IRIS_153)                    ,"IRIS_153"                      ,dbg_IRIS_153                    },
	{ 0x446c ,N_FLD(dbg_IRIS_154)                    ,"IRIS_154"                      ,dbg_IRIS_154                    },
	{ 0x4470 ,N_FLD(dbg_IRIS_155)                    ,"IRIS_155"                      ,dbg_IRIS_155                    },
	{ 0x4474 ,N_FLD(dbg_IRIS_156)                    ,"IRIS_156"                      ,dbg_IRIS_156                    },
	{ 0x4478 ,N_FLD(dbg_IRIS_157)                    ,"IRIS_157"                      ,dbg_IRIS_157                    },
	{ 0x447c ,N_FLD(dbg_IRIS_158)                    ,"IRIS_158"                      ,dbg_IRIS_158                    },
	{ 0x4480 ,N_FLD(dbg_IRIS_159)                    ,"IRIS_159"                      ,dbg_IRIS_159                    },
	{ 0x4484 ,N_FLD(dbg_IRIS_160)                    ,"IRIS_160"                      ,dbg_IRIS_160                    },
	{ 0x4488 ,N_FLD(dbg_IRIS_161)                    ,"IRIS_161"                      ,dbg_IRIS_161                    },
	{ 0x448c ,N_FLD(dbg_IRIS_162)                    ,"IRIS_162"                      ,dbg_IRIS_162                    },
	{ 0x4490 ,N_FLD(dbg_IRIS_163)                    ,"IRIS_163"                      ,dbg_IRIS_163                    },
	{ 0x4494 ,N_FLD(dbg_IRIS_164)                    ,"IRIS_164"                      ,dbg_IRIS_164                    },
	{ 0x4498 ,N_FLD(dbg_IRIS_165)                    ,"IRIS_165"                      ,dbg_IRIS_165                    },
	{ 0x449c ,N_FLD(dbg_IRIS_166)                    ,"IRIS_166"                      ,dbg_IRIS_166                    },
	{ 0x44a0 ,N_FLD(dbg_IRIS_167)                    ,"IRIS_167"                      ,dbg_IRIS_167                    },
	{ 0x44a4 ,N_FLD(dbg_IRIS_168)                    ,"IRIS_168"                      ,dbg_IRIS_168                    },
	{ 0x44a8 ,N_FLD(dbg_IRIS_169)                    ,"IRIS_169"                      ,dbg_IRIS_169                    },
	{ 0x44ac ,N_FLD(dbg_IRIS_170)                    ,"IRIS_170"                      ,dbg_IRIS_170                    },
	{ 0x44b0 ,N_FLD(dbg_IRIS_171)                    ,"IRIS_171"                      ,dbg_IRIS_171                    },
	{ 0x44b4 ,N_FLD(dbg_IRIS_172)                    ,"IRIS_172"                      ,dbg_IRIS_172                    },
	{ 0x44b8 ,N_FLD(dbg_IRIS_173)                    ,"IRIS_173"                      ,dbg_IRIS_173                    },
	{ 0x44bc ,N_FLD(dbg_IRIS_174)                    ,"IRIS_174"                      ,dbg_IRIS_174                    },
	{ 0x44c0 ,N_FLD(dbg_IRIS_175)                    ,"IRIS_175"                      ,dbg_IRIS_175                    },
	{ 0x44c4 ,N_FLD(dbg_IRIS_176)                    ,"IRIS_176"                      ,dbg_IRIS_176                    },
	{ 0x44c8 ,N_FLD(dbg_IRIS_177)                    ,"IRIS_177"                      ,dbg_IRIS_177                    },
	{ 0x44cc ,N_FLD(dbg_IRIS_178)                    ,"IRIS_178"                      ,dbg_IRIS_178                    },
	{ 0x44d0 ,N_FLD(dbg_IRIS_179)                    ,"IRIS_179"                      ,dbg_IRIS_179                    },
	{ 0x44d4 ,N_FLD(dbg_IRIS_180)                    ,"IRIS_180"                      ,dbg_IRIS_180                    },
	{ 0x44d8 ,N_FLD(dbg_IRIS_181)                    ,"IRIS_181"                      ,dbg_IRIS_181                    },
	{ 0x44dc ,N_FLD(dbg_IRIS_182)                    ,"IRIS_182"                      ,dbg_IRIS_182                    },
	{ 0x44e0 ,N_FLD(dbg_IRIS_183)                    ,"IRIS_183"                      ,dbg_IRIS_183                    },
	{ 0x44e4 ,N_FLD(dbg_IRIS_184)                    ,"IRIS_184"                      ,dbg_IRIS_184                    },
	{ 0x44e8 ,N_FLD(dbg_IRIS_185)                    ,"IRIS_185"                      ,dbg_IRIS_185                    },
	{ 0x44ec ,N_FLD(dbg_IRIS_186)                    ,"IRIS_186"                      ,dbg_IRIS_186                    },
	{ 0x44f0 ,N_FLD(dbg_IRIS_187)                    ,"IRIS_187"                      ,dbg_IRIS_187                    },
	{ 0x44f4 ,N_FLD(dbg_IRIS_188)                    ,"IRIS_188"                      ,dbg_IRIS_188                    },
	{ 0x44f8 ,N_FLD(dbg_IRIS_189)                    ,"IRIS_189"                      ,dbg_IRIS_189                    },
	{ 0x44fc ,N_FLD(dbg_IRIS_190)                    ,"IRIS_190"                      ,dbg_IRIS_190                    },
	{ 0x4500 ,N_FLD(dbg_IRIS_191)                    ,"IRIS_191"                      ,dbg_IRIS_191                    },
	{ 0x4504 ,N_FLD(dbg_IRIS_192)                    ,"IRIS_192"                      ,dbg_IRIS_192                    },
	{ 0x4508 ,N_FLD(dbg_IRIS_193)                    ,"IRIS_193"                      ,dbg_IRIS_193                    },
	{ 0x450c ,N_FLD(dbg_IRIS_194)                    ,"IRIS_194"                      ,dbg_IRIS_194                    },
	{ 0x4510 ,N_FLD(dbg_IRIS_195)                    ,"IRIS_195"                      ,dbg_IRIS_195                    },
	{ 0x4514 ,N_FLD(dbg_IRIS_196)                    ,"IRIS_196"                      ,dbg_IRIS_196                    },
	{ 0x4518 ,N_FLD(dbg_IRIS_197)                    ,"IRIS_197"                      ,dbg_IRIS_197                    },
	{ 0x451c ,N_FLD(dbg_IRIS_198)                    ,"IRIS_198"                      ,dbg_IRIS_198                    },
	{ 0x4520 ,N_FLD(dbg_IRIS_199)                    ,"IRIS_199"                      ,dbg_IRIS_199                    },
	{ 0x4524 ,N_FLD(dbg_IRIS_200)                    ,"IRIS_200"                      ,dbg_IRIS_200                    },
	{ 0x4528 ,N_FLD(dbg_IRIS_201)                    ,"IRIS_201"                      ,dbg_IRIS_201                    },
	{ 0x452c ,N_FLD(dbg_IRIS_202)                    ,"IRIS_202"                      ,dbg_IRIS_202                    },
	{ 0x4530 ,N_FLD(dbg_IRIS_203)                    ,"IRIS_203"                      ,dbg_IRIS_203                    },
	{ 0x4534 ,N_FLD(dbg_IRIS_204)                    ,"IRIS_204"                      ,dbg_IRIS_204                    },
	{ 0x4538 ,N_FLD(dbg_IRIS_205)                    ,"IRIS_205"                      ,dbg_IRIS_205                    },
	{ 0x453c ,N_FLD(dbg_IRIS_206)                    ,"IRIS_206"                      ,dbg_IRIS_206                    },
	{ 0x4540 ,N_FLD(dbg_IRIS_207)                    ,"IRIS_207"                      ,dbg_IRIS_207                    },
	{ 0x4544 ,N_FLD(dbg_IRIS_208)                    ,"IRIS_208"                      ,dbg_IRIS_208                    },
	{ 0x4548 ,N_FLD(dbg_IRIS_209)                    ,"IRIS_209"                      ,dbg_IRIS_209                    },
	{ 0x454c ,N_FLD(dbg_IRIS_210)                    ,"IRIS_210"                      ,dbg_IRIS_210                    },
	{ 0x4550 ,N_FLD(dbg_IRIS_211)                    ,"IRIS_211"                      ,dbg_IRIS_211                    },
	{ 0x4554 ,N_FLD(dbg_IRIS_212)                    ,"IRIS_212"                      ,dbg_IRIS_212                    },
	{ 0x4558 ,N_FLD(dbg_IRIS_213)                    ,"IRIS_213"                      ,dbg_IRIS_213                    },
	{ 0x455c ,N_FLD(dbg_IRIS_214)                    ,"IRIS_214"                      ,dbg_IRIS_214                    },
	{ 0x4560 ,N_FLD(dbg_IRIS_215)                    ,"IRIS_215"                      ,dbg_IRIS_215                    },
	{ 0x4564 ,N_FLD(dbg_IRIS_216)                    ,"IRIS_216"                      ,dbg_IRIS_216                    },
	{ 0x4568 ,N_FLD(dbg_IRIS_217)                    ,"IRIS_217"                      ,dbg_IRIS_217                    },
	{ 0x456c ,N_FLD(dbg_IRIS_218)                    ,"IRIS_218"                      ,dbg_IRIS_218                    },
	{ 0x4570 ,N_FLD(dbg_IRIS_219)                    ,"IRIS_219"                      ,dbg_IRIS_219                    },
	{ 0x4574 ,N_FLD(dbg_IRIS_220)                    ,"IRIS_220"                      ,dbg_IRIS_220                    },
	{ 0x4578 ,N_FLD(dbg_IRIS_221)                    ,"IRIS_221"                      ,dbg_IRIS_221                    },
	{ 0x457c ,N_FLD(dbg_IRIS_222)                    ,"IRIS_222"                      ,dbg_IRIS_222                    },
	{ 0x4580 ,N_FLD(dbg_IRIS_223)                    ,"IRIS_223"                      ,dbg_IRIS_223                    },
	{ 0x4584 ,N_FLD(dbg_IRIS_224)                    ,"IRIS_224"                      ,dbg_IRIS_224                    },
	{ 0x4588 ,N_FLD(dbg_IRIS_225)                    ,"IRIS_225"                      ,dbg_IRIS_225                    },
	{ 0x458c ,N_FLD(dbg_IRIS_226)                    ,"IRIS_226"                      ,dbg_IRIS_226                    },
	{ 0x4590 ,N_FLD(dbg_IRIS_227)                    ,"IRIS_227"                      ,dbg_IRIS_227                    },
	{ 0x4594 ,N_FLD(dbg_IRIS_228)                    ,"IRIS_228"                      ,dbg_IRIS_228                    },
	{ 0x4598 ,N_FLD(dbg_IRIS_229)                    ,"IRIS_229"                      ,dbg_IRIS_229                    },
	{ 0x459c ,N_FLD(dbg_IRIS_230)                    ,"IRIS_230"                      ,dbg_IRIS_230                    },
	{ 0x45a0 ,N_FLD(dbg_IRIS_231)                    ,"IRIS_231"                      ,dbg_IRIS_231                    },
	{ 0x45a4 ,N_FLD(dbg_IRIS_232)                    ,"IRIS_232"                      ,dbg_IRIS_232                    },
	{ 0x45a8 ,N_FLD(dbg_IRIS_233)                    ,"IRIS_233"                      ,dbg_IRIS_233                    },
	{ 0x45ac ,N_FLD(dbg_IRIS_234)                    ,"IRIS_234"                      ,dbg_IRIS_234                    },
	{ 0x45b0 ,N_FLD(dbg_IRIS_235)                    ,"IRIS_235"                      ,dbg_IRIS_235                    },
	{ 0x45b4 ,N_FLD(dbg_IRIS_236)                    ,"IRIS_236"                      ,dbg_IRIS_236                    },
	{ 0x45b8 ,N_FLD(dbg_IRIS_237)                    ,"IRIS_237"                      ,dbg_IRIS_237                    },
	{ 0x45bc ,N_FLD(dbg_IRIS_238)                    ,"IRIS_238"                      ,dbg_IRIS_238                    },
	{ 0x45c0 ,N_FLD(dbg_IRIS_239)                    ,"IRIS_239"                      ,dbg_IRIS_239                    },
	{ 0x45c4 ,N_FLD(dbg_IRIS_240)                    ,"IRIS_240"                      ,dbg_IRIS_240                    },
	{ 0x45c8 ,N_FLD(dbg_IRIS_241)                    ,"IRIS_241"                      ,dbg_IRIS_241                    },
	{ 0x45cc ,N_FLD(dbg_IRIS_242)                    ,"IRIS_242"                      ,dbg_IRIS_242                    },
	{ 0x45d0 ,N_FLD(dbg_IRIS_243)                    ,"IRIS_243"                      ,dbg_IRIS_243                    },
	{ 0x45d4 ,N_FLD(dbg_IRIS_244)                    ,"IRIS_244"                      ,dbg_IRIS_244                    },
	{ 0x45d8 ,N_FLD(dbg_IRIS_245)                    ,"IRIS_245"                      ,dbg_IRIS_245                    },
	{ 0x45dc ,N_FLD(dbg_IRIS_246)                    ,"IRIS_246"                      ,dbg_IRIS_246                    },
	{ 0x45e0 ,N_FLD(dbg_IRIS_247)                    ,"IRIS_247"                      ,dbg_IRIS_247                    },
	{ 0x45e4 ,N_FLD(dbg_IRIS_248)                    ,"IRIS_248"                      ,dbg_IRIS_248                    },
	{ 0x45e8 ,N_FLD(dbg_IRIS_249)                    ,"IRIS_249"                      ,dbg_IRIS_249                    },
	{ 0x45ec ,N_FLD(dbg_IRIS_250)                    ,"IRIS_250"                      ,dbg_IRIS_250                    },
	{ 0x45f0 ,N_FLD(dbg_IRIS_251)                    ,"IRIS_251"                      ,dbg_IRIS_251                    },
	{ 0x45f4 ,N_FLD(dbg_IRIS_252)                    ,"IRIS_252"                      ,dbg_IRIS_252                    },
	{ 0x45f8 ,N_FLD(dbg_IRIS_253)                    ,"IRIS_253"                      ,dbg_IRIS_253                    },
	{ 0x45fc ,N_FLD(dbg_IRIS_254)                    ,"IRIS_254"                      ,dbg_IRIS_254                    },
	{ 0x4600 ,N_FLD(dbg_IRIS_255)                    ,"IRIS_255"                      ,dbg_IRIS_255                    },
	{ 0x4604 ,N_FLD(dbg_IRIS_256)                    ,"IRIS_256"                      ,dbg_IRIS_256                    },
	{ 0x4608 ,N_FLD(dbg_IRIS_257)                    ,"IRIS_257"                      ,dbg_IRIS_257                    },
	{ 0x460c ,N_FLD(dbg_IRIS_258)                    ,"IRIS_258"                      ,dbg_IRIS_258                    },
	{ 0x4610 ,N_FLD(dbg_IRIS_259)                    ,"IRIS_259"                      ,dbg_IRIS_259                    },
	{ 0x4614 ,N_FLD(dbg_IRIS_260)                    ,"IRIS_260"                      ,dbg_IRIS_260                    },
	{ 0x4618 ,N_FLD(dbg_IRIS_261)                    ,"IRIS_261"                      ,dbg_IRIS_261                    },
	{ 0x461c ,N_FLD(dbg_IRIS_262)                    ,"IRIS_262"                      ,dbg_IRIS_262                    },
	{ 0x4620 ,N_FLD(dbg_IRIS_263)                    ,"IRIS_263"                      ,dbg_IRIS_263                    },
	{ 0x4624 ,N_FLD(dbg_IRIS_264)                    ,"IRIS_264"                      ,dbg_IRIS_264                    },
	{ 0x4630 ,N_FLD(dbg_IRIS_265)                    ,"IRIS_265"                      ,dbg_IRIS_265                    },
	{ 0x4634 ,N_FLD(dbg_IRIS_266)                    ,"IRIS_266"                      ,dbg_IRIS_266                    },
	{ 0x4638 ,N_FLD(dbg_IRIS_267)                    ,"IRIS_267"                      ,dbg_IRIS_267                    },
	{ 0x463c ,N_FLD(dbg_IRIS_268)                    ,"IRIS_268"                      ,dbg_IRIS_268                    },
	{ 0x4640 ,N_FLD(dbg_IRIS_269)                    ,"IRIS_269"                      ,dbg_IRIS_269                    },
	{ 0x4644 ,N_FLD(dbg_IRIS_270)                    ,"IRIS_270"                      ,dbg_IRIS_270                    },
	{ 0x4648 ,N_FLD(dbg_IRIS_271)                    ,"IRIS_271"                      ,dbg_IRIS_271                    },
	{ 0x464c ,N_FLD(dbg_IRIS_272)                    ,"IRIS_272"                      ,dbg_IRIS_272                    },
	{ 0x4650 ,N_FLD(dbg_IRIS_273)                    ,"IRIS_273"                      ,dbg_IRIS_273                    },
	{ 0x4654 ,N_FLD(dbg_IRIS_274)                    ,"IRIS_274"                      ,dbg_IRIS_274                    },
	{ 0x4658 ,N_FLD(dbg_IRIS_275)                    ,"IRIS_275"                      ,dbg_IRIS_275                    },
	{ 0x465c ,N_FLD(dbg_IRIS_276)                    ,"IRIS_276"                      ,dbg_IRIS_276                    },
	{ 0x4660 ,N_FLD(dbg_IRIS_277)                    ,"IRIS_277"                      ,dbg_IRIS_277                    },
	{ 0x4664 ,N_FLD(dbg_IRIS_278)                    ,"IRIS_278"                      ,dbg_IRIS_278                    },
	{ 0x4668 ,N_FLD(dbg_IRIS_279)                    ,"IRIS_279"                      ,dbg_IRIS_279                    },
	{ 0x466c ,N_FLD(dbg_IRIS_280)                    ,"IRIS_280"                      ,dbg_IRIS_280                    },
	{ 0x4670 ,N_FLD(dbg_IRIS_281)                    ,"IRIS_281"                      ,dbg_IRIS_281                    },
	{ 0x4674 ,N_FLD(dbg_IRIS_282)                    ,"IRIS_282"                      ,dbg_IRIS_282                    },
	{ 0x4678 ,N_FLD(dbg_IRIS_283)                    ,"IRIS_283"                      ,dbg_IRIS_283                    },
	{ 0x467c ,N_FLD(dbg_IRIS_284)                    ,"IRIS_284"                      ,dbg_IRIS_284                    },
	{ 0x4680 ,N_FLD(dbg_IRIS_285)                    ,"IRIS_285"                      ,dbg_IRIS_285                    },
	{ 0x4684 ,N_FLD(dbg_IRIS_286)                    ,"IRIS_286"                      ,dbg_IRIS_286                    },
	{ 0x4688 ,N_FLD(dbg_IRIS_287)                    ,"IRIS_287"                      ,dbg_IRIS_287                    },
	{ 0x468c ,N_FLD(dbg_IRIS_288)                    ,"IRIS_288"                      ,dbg_IRIS_288                    },
	{ 0x4690 ,N_FLD(dbg_IRIS_289)                    ,"IRIS_289"                      ,dbg_IRIS_289                    },
	{ 0x4694 ,N_FLD(dbg_IRIS_290)                    ,"IRIS_290"                      ,dbg_IRIS_290                    },
	{ 0x4698 ,N_FLD(dbg_IRIS_291)                    ,"IRIS_291"                      ,dbg_IRIS_291                    },
	{ 0x469c ,N_FLD(dbg_IRIS_292)                    ,"IRIS_292"                      ,dbg_IRIS_292                    },
	{ 0x46a0 ,N_FLD(dbg_IRIS_293)                    ,"IRIS_293"                      ,dbg_IRIS_293                    },
	{ 0x46a4 ,N_FLD(dbg_IRIS_294)                    ,"IRIS_294"                      ,dbg_IRIS_294                    },
	{ 0x46a8 ,N_FLD(dbg_IRIS_295)                    ,"IRIS_295"                      ,dbg_IRIS_295                    },
	{ 0x46ac ,N_FLD(dbg_IRIS_296)                    ,"IRIS_296"                      ,dbg_IRIS_296                    },
	{ 0x46b0 ,N_FLD(dbg_IRIS_297)                    ,"IRIS_297"                      ,dbg_IRIS_297                    },
	{ 0x46b4 ,N_FLD(dbg_IRIS_298)                    ,"IRIS_298"                      ,dbg_IRIS_298                    },
	{ 0x46b8 ,N_FLD(dbg_IRIS_299)                    ,"IRIS_299"                      ,dbg_IRIS_299                    },
	{ 0x46bc ,N_FLD(dbg_IRIS_300)                    ,"IRIS_300"                      ,dbg_IRIS_300                    },
	{ 0x46c0 ,N_FLD(dbg_IRIS_301)                    ,"IRIS_301"                      ,dbg_IRIS_301                    },
	{ 0x46c4 ,N_FLD(dbg_IRIS_302)                    ,"IRIS_302"                      ,dbg_IRIS_302                    },
	{ 0x46c8 ,N_FLD(dbg_IRIS_303)                    ,"IRIS_303"                      ,dbg_IRIS_303                    },
	{ 0x46cc ,N_FLD(dbg_IRIS_304)                    ,"IRIS_304"                      ,dbg_IRIS_304                    },
	{ 0x4800 ,N_FLD(dbg_VBI_001)                     ,"VBI_001"                       ,dbg_VBI_001                     },
	{ 0x4804 ,N_FLD(dbg_VBI_002)                     ,"VBI_002"                       ,dbg_VBI_002                     },
	{ 0x4808 ,N_FLD(dbg_VBI_003)                     ,"VBI_003"                       ,dbg_VBI_003                     },
	{ 0x480c ,N_FLD(dbg_VBI_004)                     ,"VBI_004"                       ,dbg_VBI_004                     },
	{ 0x4810 ,N_FLD(dbg_VBI_005)                     ,"VBI_005"                       ,dbg_VBI_005                     },
	{ 0x4814 ,N_FLD(dbg_VBI_006)                     ,"VBI_006"                       ,dbg_VBI_006                     },
	{ 0x4818 ,N_FLD(dbg_VBI_007)                     ,"VBI_007"                       ,dbg_VBI_007                     },
	{ 0x481c ,N_FLD(dbg_VBI_008)                     ,"VBI_008"                       ,dbg_VBI_008                     },
	{ 0x4820 ,N_FLD(dbg_VBI_009)                     ,"VBI_009"                       ,dbg_VBI_009                     },
	{ 0x4824 ,N_FLD(dbg_VBI_010)                     ,"VBI_010"                       ,dbg_VBI_010                     },
	{ 0x4828 ,N_FLD(dbg_VBI_011)                     ,"VBI_011"                       ,dbg_VBI_011                     },
	{ 0x482c ,N_FLD(dbg_VBI_012)                     ,"VBI_012"                       ,dbg_VBI_012                     },
	{ 0x4830 ,N_FLD(dbg_VBI_013)                     ,"VBI_013"                       ,dbg_VBI_013                     },
	{ 0x4834 ,N_FLD(dbg_VBI_014)                     ,"VBI_014"                       ,dbg_VBI_014                     },
	{ 0x4838 ,N_FLD(dbg_VBI_015)                     ,"VBI_015"                       ,dbg_VBI_015                     },
	{ 0x483c ,N_FLD(dbg_VBI_016)                     ,"VBI_016"                       ,dbg_VBI_016                     },
	{ 0x4840 ,N_FLD(dbg_VBI_017)                     ,"VBI_017"                       ,dbg_VBI_017                     },
	{ 0x4844 ,N_FLD(dbg_VBI_018)                     ,"VBI_018"                       ,dbg_VBI_018                     },
	{ 0x4848 ,N_FLD(dbg_VBI_019)                     ,"VBI_019"                       ,dbg_VBI_019                     },
	{ 0x484c ,N_FLD(dbg_VBI_020)                     ,"VBI_020"                       ,dbg_VBI_020                     },
	{ 0x4850 ,N_FLD(dbg_VBI_021)                     ,"VBI_021"                       ,dbg_VBI_021                     },
	{ 0x4854 ,N_FLD(dbg_VBI_022)                     ,"VBI_022"                       ,dbg_VBI_022                     },
	{ 0x4858 ,N_FLD(dbg_VBI_023)                     ,"VBI_023"                       ,dbg_VBI_023                     },
	{ 0x485c ,N_FLD(dbg_VBI_024)                     ,"VBI_024"                       ,dbg_VBI_024                     },
	{ 0x48a8 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_001)       ,"IRIS_MIF_GMUA_MON_001"         ,dbg_IRIS_MIF_GMUA_MON_001       },
	{ 0x48ac ,N_FLD(dbg_IRIS_MIF_GMUA_MON_002)       ,"IRIS_MIF_GMUA_MON_002"         ,dbg_IRIS_MIF_GMUA_MON_002       },
	{ 0x48b0 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_003)       ,"IRIS_MIF_GMUA_MON_003"         ,dbg_IRIS_MIF_GMUA_MON_003       },
	{ 0x48b4 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_004)       ,"IRIS_MIF_GMUA_MON_004"         ,dbg_IRIS_MIF_GMUA_MON_004       },
	{ 0x48b8 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_005)       ,"IRIS_MIF_GMUA_MON_005"         ,dbg_IRIS_MIF_GMUA_MON_005       },
	{ 0x48bc ,N_FLD(dbg_IRIS_MIF_GMUA_MON_006)       ,"IRIS_MIF_GMUA_MON_006"         ,dbg_IRIS_MIF_GMUA_MON_006       },
	{ 0x48c0 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_007)       ,"IRIS_MIF_GMUA_MON_007"         ,dbg_IRIS_MIF_GMUA_MON_007       },
	{ 0x48c4 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_008)       ,"IRIS_MIF_GMUA_MON_008"         ,dbg_IRIS_MIF_GMUA_MON_008       },
	{ 0x48c8 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_009)       ,"IRIS_MIF_GMUA_MON_009"         ,dbg_IRIS_MIF_GMUA_MON_009       },
	{ 0x48cc ,N_FLD(dbg_IRIS_MIF_GMUA_MON_010)       ,"IRIS_MIF_GMUA_MON_010"         ,dbg_IRIS_MIF_GMUA_MON_010       },
	{ 0x48d0 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_011)       ,"IRIS_MIF_GMUA_MON_011"         ,dbg_IRIS_MIF_GMUA_MON_011       },
	{ 0x48d4 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_012)       ,"IRIS_MIF_GMUA_MON_012"         ,dbg_IRIS_MIF_GMUA_MON_012       },
	{ 0x48d8 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_013)       ,"IRIS_MIF_GMUA_MON_013"         ,dbg_IRIS_MIF_GMUA_MON_013       },
	{ 0x48dc ,N_FLD(dbg_IRIS_MIF_GMUA_MON_014)       ,"IRIS_MIF_GMUA_MON_014"         ,dbg_IRIS_MIF_GMUA_MON_014       },
	{ 0x48e0 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_015)       ,"IRIS_MIF_GMUA_MON_015"         ,dbg_IRIS_MIF_GMUA_MON_015       },
	{ 0x48e4 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_016)       ,"IRIS_MIF_GMUA_MON_016"         ,dbg_IRIS_MIF_GMUA_MON_016       },
	{ 0x48e8 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_017)       ,"IRIS_MIF_GMUA_MON_017"         ,dbg_IRIS_MIF_GMUA_MON_017       },
	{ 0x48ec ,N_FLD(dbg_IRIS_MIF_GMUA_MON_018)       ,"IRIS_MIF_GMUA_MON_018"         ,dbg_IRIS_MIF_GMUA_MON_018       },
	{ 0x48f0 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_019)       ,"IRIS_MIF_GMUA_MON_019"         ,dbg_IRIS_MIF_GMUA_MON_019       },
	{ 0x48f4 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_020)       ,"IRIS_MIF_GMUA_MON_020"         ,dbg_IRIS_MIF_GMUA_MON_020       },
	{ 0x48f8 ,N_FLD(dbg_IRIS_MIF_GMUA_MON_021)       ,"IRIS_MIF_GMUA_MON_021"         ,dbg_IRIS_MIF_GMUA_MON_021       },
	{ 0x48fc ,N_FLD(dbg_IRIS_MIF_GMUA_MON_022)       ,"IRIS_MIF_GMUA_MON_022"         ,dbg_IRIS_MIF_GMUA_MON_022       },
	{ 0x4900 ,N_FLD(dbg_IRIS_HIF_CTRL0_001)          ,"IRIS_HIF_CTRL0_001"            ,dbg_IRIS_HIF_CTRL0_001          },
	{ 0x4904 ,N_FLD(dbg_IRIS_HIF_CTRL1_001)          ,"IRIS_HIF_CTRL1_001"            ,dbg_IRIS_HIF_CTRL1_001          },
	{ 0 , } // end marker
};

#endif
