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

#ifndef _DBG_CTR_h
#define _DBG_CTR_h

/*------------------------------------------------
	0x0000 DEA_CHA_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_CHA_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cha_hsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"cha_csample"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"cha_aspect"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"cha_vsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"cha_frame_lr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"cha_field_id"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"cha_pr_sq"                       },
};

/*------------------------------------------------
	0x0004 DEA_CHB_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_CHB_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"chb_hsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"chb_csample"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"chb_aspect"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"chb_vsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"chb_frame_lr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"chb_field_id"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"chb_pr_sq"                       },
};

/*------------------------------------------------
	0x0008 DEA_PIC_INIT
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"                     },
};

/*------------------------------------------------
	0x000c DEA_PIC_START
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"                    },
};

/*------------------------------------------------
	0x0010 DEA_SMUX_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SMUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"o_c_fmt"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"i_c_fmt"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec3d_mux_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"prew_mux_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"d3_lr_sel"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"cvi_mux_sel"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"nline_inc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"wr_disalbe"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fieldid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"input_size_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pr_sq"                           },
};

/*------------------------------------------------
	0x0014 DEA_SMUX_SIZE
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SMUX_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsize"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"vsize"                           },
};

/*------------------------------------------------
	0x0018 DEA_MVI_V_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MVI_V_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_vsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_vblank"                      },
};

/*------------------------------------------------
	0x001c DEA_MVI_H_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MVI_H_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_hsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_hblank"                      },
};

/*------------------------------------------------
	0x0020 DEA_MVI_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MVI_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"mvi_i_c_fmt"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mvi_field"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"mvi_pr_sq"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mvi_cvi_stride"                  },
};

/*------------------------------------------------
	0x0024 DEA_MSRC_SYNC_MUX_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MSRC_SYNC_MUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"trans_mask_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cvi_select"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"mvi_select"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"mvi_sync_select"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mvi_cvi_select"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"cvia_vsync_inv"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"cvib_vsync_inv"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"vdec_vsync_inv"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"mem_vsync_inv"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cvia_sync_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"cvib_sync_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"sync_manual_delay_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"ignore_src_vsync_fal"            },
};

/*------------------------------------------------
	0x0028 DEA_MSRC_SYNC_DLY
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MSRC_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dea_msrc_sync_dly"               },
};

/*------------------------------------------------
	0x002c DEA_MEM_SYNC_PERIOD
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MEM_SYNC_PERIOD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dea_mem_sync_period"             },
};

/*------------------------------------------------
	0x0030 DEA_DCO_MFC
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_MFC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dea_dco_mfc"                     },
};

/*------------------------------------------------
	0x0034 DEA_DCO_DFC
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_DFC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dea_dco_dfc"                     },
};

/*------------------------------------------------
	0x0038 DEA_DCO_DFLC
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_DFLC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"dea_dco_dflc"                    },
};

/*------------------------------------------------
	0x003c DEA_DCO_FCW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_FCW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"dea_dco_fcw"                     },
};

/*------------------------------------------------
	0x0040 DEA_SMUX_RO_LCNT
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SMUX_RO_LCNT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"dea_smux_ro_lcnt"                },
};

/*------------------------------------------------
	0x0044 DEA_GMAU_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"                      },
};

/*------------------------------------------------
	0x0048 DEA_PIC_END_EN
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ipc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"clc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"tnr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pe0_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"prew_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"smux_en"                         },
};

/*------------------------------------------------
	0x004c DEA_PIC_INIT_G0_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g0_timer"               },
};

/*------------------------------------------------
	0x0050 DEA_PIC_INIT_G1_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer"               },
};

/*------------------------------------------------
	0x0054 DEA_PIC_END_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,5  ,"pic_end_g1"                      },
};

/*------------------------------------------------
	0x0058 DEA_INTR_REG
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cha_input_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"chb_input_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cha_field_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cha_frame_lr_intr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"chb_field_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"chb_frame_lr_intr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pe0_intr"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"smux_ow_intr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_wr_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"src_intr"                        },
};

/*------------------------------------------------
	0x005c DEA_INTR_MASK
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cha_input_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"chb_input_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cha_field_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cha_frame_lr_intr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"chb_field_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"chb_frame_lr_intr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pe0_intr"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"smux_ow_intr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_wr_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"src_intr"                        },
};

/*------------------------------------------------
	0x0060 DEA_INTR_MUX
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_INTR_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cha_input_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"chb_input_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cha_field_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cha_frame_lr_intr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"chb_field_intr"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"chb_frame_lr_intr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pe0_intr"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"smux_ow_intr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_wr_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"src_intr"                        },
};

/*------------------------------------------------
	0x0064 DEA_SRC_INTR_TIME_STP
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SRC_INTR_TIME_STP[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"dea_src_intr_time_stp"           },
};

/*------------------------------------------------
	0x0068 DE_GPIO_MUX
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DE_GPIO_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"de_gpio_mux"                     },
};

/*------------------------------------------------
	0x006c DEA_ADDR_SW_DE_SAV
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dea_addr_sav_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"dea_addr_default_bus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dea_addr_de_bus"                 },
};

/*------------------------------------------------
	0x0070 DEA_ADDR_SW_CPU_GPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dea_addr_gpu_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dea_addr_gpu_logic"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"dea_addr_cpu_h_bus"              },
};

/*------------------------------------------------
	0x0074 DEA_ADDR_SW_CPU_SHADOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dea_addr_shadow_bus"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dea_addr_shadow_logic"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dea_addr_cpu_l_bus"              },
};

/*------------------------------------------------
	0x007c DE_VERSION
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DE_VERSION[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"de_version"                      },
};

/*------------------------------------------------
	0x0080 DEA_SMUX_SIZE_I
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SMUX_SIZE_I[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsize_i"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"vsize_i"                         },
};

/*------------------------------------------------
	0x00c0 DEA_DEA_MVI_CTRL_0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DEA_MVI_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_h_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_h_width"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mvi_3d_ctrl_en"                  },
};

/*------------------------------------------------
	0x00c4 DEA_DEA_MVI_CTRL_1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DEA_MVI_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_h_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_h_width"                       },
};

/*------------------------------------------------
	0x00c8 DEA_DEA_MVI_CTRL_2
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DEA_MVI_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_v_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_v_height"                      },
};

/*------------------------------------------------
	0x00cc DEA_DEA_MVI_CTRL_3
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DEA_MVI_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_v_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_v_height"                      },
};

/*------------------------------------------------
	0x00d0 DEA_DEA_MVI_CTRL_4
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DEA_MVI_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"h_sub_sample_step"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"y_h_even_line_sub_sample_offset" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"y_h_odd_line_sub_sample_offset"  },
};

/*------------------------------------------------
	0x00d4 DEA_DEA_MVI_CTRL_5
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DEA_MVI_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"c_h_even_line_sub_sample_offset" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_h_odd_line_sub_sample_offset"  },
};

/*------------------------------------------------
	0x00d8 DEA_DEA_MVI_CTRL_6
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DEA_MVI_CTRL_6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"v_sub_sample_step"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"y_v_sub_sample_offset"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_v_sub_sample_offset"           },
};

/*------------------------------------------------
	0x00e0 DEA_PIC_START_DELAY_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_START_DELAY_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_delay_mvi"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_delay_mvi_y_rd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_start_delay_mvi_c_rd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_start_delay_dec3d"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"pic_start_delay_smux"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"pic_start_delay_prew_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pic_start_delay_prew_c_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pic_start_delay_prew_y_wd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pic_start_delay_prew_c_wd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"pic_start_delay_pe0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"pic_start_delay_tnr0_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"pic_start_delay_tnr1_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pic_start_delay_tnr_c_rd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"pic_start_delay_tnr_y_wd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"pic_start_delay_tnr_c_wd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"pic_start_delay_ipc0_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pic_start_delay_ipc1_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"pic_start_delay_ipc_c_rd"        },
};

/*------------------------------------------------
	0x00e4 DEA_PIC_START_G0_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_START_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_start_g0_timer"              },
};

/*------------------------------------------------
	0x00e8 DEA_PIC_START_G1_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_START_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_start_g1_timer"              },
};

/*------------------------------------------------
	0x00f4 DEA_PIC_END_FORCE
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_END_FORCE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dea_pic_end_g0_force"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"dea_pic_end_g0_force_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dea_pic_end_g1_force"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dea_pic_end_g1_force_en"         },
};

/*------------------------------------------------
	0x00f8 DEA_GMAU_FLUSH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_GMAU_FLUSH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_flush_rd_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gmau_flush_wr_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done"              },
};

/*------------------------------------------------
	0x00fc DEA_MG_LS_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MG_LS_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dea_ls_override_mifa"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dea_ls_override_pe0_l"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"dea_ls_override_smux_l"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"dea_ls_override_cvi"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"dea_mg_override_mifa"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"dea_mg_override_pe0_l"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"dea_mg_override_smux_l"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"dea_mg_override_cvi"             },
};

/*------------------------------------------------
	0x1000 DEB_PIC_INIT
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"ov_auto_init"                    },
};

/*------------------------------------------------
	0x1004 DEB_PIC_START
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"                    },
};

/*------------------------------------------------
	0x1008 DEB_DISP_V_PORCH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_V_PORCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"vsync_bp"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"vsync_fp"                        },
};

/*------------------------------------------------
	0x100c DEB_DISP_VS_VA
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_VS_VA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"disp_sync_va"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"vsync"                           },
};

/*------------------------------------------------
	0x1010 DEB_DISP_H_PORCH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_H_PORCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hsync_bp"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"hsync_fp"                        },
};

/*------------------------------------------------
	0x1014 DEB_DISP_HS_HA
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_HS_HA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"disp_sync_ha"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"hsync"                           },
};

/*------------------------------------------------
	0x1018 DEB_DISP_SYNC_DLY
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hoffset1"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"voffset1"                        },
};

/*------------------------------------------------
	0x101c DEB_DISP_PULSE_DLY
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_PULSE_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"deb_disp_pulse_dly"              },
};

/*------------------------------------------------
	0x1020 DEB_DISP_SYNC_PARAMS
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_SYNC_PARAMS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hoffset0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"disp_frame_lr"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"force_update"                    },
};

/*------------------------------------------------
	0x102c DEB_PWM0_CTRL0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM0_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pwm0_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pwm0_freq_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pwm0_method"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"pwm0_resolution"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pwm0_inv"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pwm0_sel"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,8  ,"pwm0_width_falling_pos"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"pwm0_fc_h_disp"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm0_fc_l_disp"                  },
};

/*------------------------------------------------
	0x1030 DEB_PWM0_CTRL1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM0_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pwm0_intr_mask"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,8  ,"pwm0_free_width"                 },
};

/*------------------------------------------------
	0x1034 DEB_PWM1_CTRL0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM1_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pwm1_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pwm1_freq_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pwm1_method"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"pwm1_resolution"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pwm1_inv"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pwm1_sel"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,8  ,"pwm1_width_falling_pos"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"pwm1_fc_h_disp"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm1_fc_l_disp"                  },
};

/*------------------------------------------------
	0x1038 DEB_PWM1_CTRL1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM1_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pwm1_intr_mask"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,8  ,"pwm1_free_width"                 },
};

/*------------------------------------------------
	0x103c DEB_PWM2_CTRL0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM2_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pwm2_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pwm2_freq_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pwm2_method"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"pwm2_resolution"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pwm2_inv"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pwm2_sel"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,8  ,"pwm2_width_falling_pos"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"pwm2_fc_h_disp"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm2_fc_l_disp"                  },
};

/*------------------------------------------------
	0x1040 DEB_PWM2_CTRL1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM2_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pwm2_intr_mask"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,8  ,"pwm2_free_width"                 },
};

/*------------------------------------------------
	0x1044 DEB_PWM3_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM3_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pwm3_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"pwm3_freq_mode"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,3  ,"pwm3_intr_mask"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,8  ,"pwm3_threshold"                  },
};

/*------------------------------------------------
	0x1048 PWM3_0_LOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_0_LOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_0_low"                      },
};

/*------------------------------------------------
	0x104c PWM3_0_HIGH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_0_HIGH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_0_high"                     },
};

/*------------------------------------------------
	0x1050 PWM3_1_LOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_1_LOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_1_low"                      },
};

/*------------------------------------------------
	0x1054 PWM3_1_HIGH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_1_HIGH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_1_high"                     },
};

/*------------------------------------------------
	0x1058 PWM3_2_LOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_2_LOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_2_low"                      },
};

/*------------------------------------------------
	0x105c PWM3_2_HIGH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_2_HIGH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_2_high"                     },
};

/*------------------------------------------------
	0x1060 PWM3_3_LOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_3_LOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_3_low"                      },
};

/*------------------------------------------------
	0x1064 PWM3_3_HIGH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM3_3_HIGH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"pwm3_3_high"                     },
};

/*------------------------------------------------
	0x1068 DEB_DPATH_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DPATH_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"t3_mux_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fb_mux_sel"                      },
};

/*------------------------------------------------
	0x106c DEB_GMAU_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"                      },
};

/*------------------------------------------------
	0x1070 DEB_PIC_END_EN
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ov_ss_en"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ov_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"sm_en"                           },
};

/*------------------------------------------------
	0x1074 DEB_PIC_INIT_G0_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"deb_pic_init_g0_timer"           },
};

/*------------------------------------------------
	0x1078 DEB_PIC_INIT_G1_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"deb_pic_init_g1_timer"           },
};

/*------------------------------------------------
	0x107c DEB_PIC_END_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,4  ,"pic_end_g1"                      },
};

/*------------------------------------------------
	0x1080 DEB_INTR_REG
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"intr_pic_end_g0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"intr_pic_end_g1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"disp_pulse_for_cpu"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"ov_underflow"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"intr_pwm"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"disp_pulse_for_mcu"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"src_pulse"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"intr_pic_end_g1_c"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"intr_gmau_flush_wr_done"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"intr_gmau_flush_rd_done"         },
};

/*------------------------------------------------
	0x1084 DEB_INTR_MASK
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"mask_pic_end_g0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"mask_pic_end_g1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"mask_disp_for_cpu"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"mask_ov_underflow"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mask_pwm"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"mask_disp_for_mcu"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"mask_src_pulse"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"mask_pic_end_g1_c"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mask_gmau_flush_wr_done"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"mask_gmau_flush_rd_done"         },
};

/*------------------------------------------------
	0x1088 DEB_INTR_MUX
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_INTR_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"mux_pic_end_g0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"mux_pic_end_g1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"mux_disp_for_cpu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"mux_ov_underflow"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mux_pwm"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"mux_disp_for_mcu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"mux_src_pulse"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"mux_pic_end_g1_c"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mux_gmau_flush_wr_done"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"mux_gmau_flush_rd_done"          },
};

/*------------------------------------------------
	0x108c DEB_DISP_INTR_TIME_STP
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_INTR_TIME_STP[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"deb_disp_intr_time_stp"          },
};

/*------------------------------------------------
	0x1090 DEB_ADDR_SW_DE_SAV
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"deb_addr_sav_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"deb_addr_default_bus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"deb_addr_de_bus"                 },
};

/*------------------------------------------------
	0x1094 DEB_ADDR_SW_CPU_GPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"deb_addr_gpu_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"deb_addr_gpu_logic"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"deb_addr_cpu_h_bus"              },
};

/*------------------------------------------------
	0x1098 DEB_ADDR_SW_CPU_SHADOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"deb_addr_shadow_bus"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"deb_addr_shadow_logic"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"deb_addr_cpu_l_bus"              },
};

/*------------------------------------------------
	0x10a0 PWM0_V
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM0_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"pwm0_x_f_v"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,14 ,"pwm0_x_r_v"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"pwm0_v_id"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm0_v_we"                       },
};

/*------------------------------------------------
	0x10a4 PWM1_V
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM1_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"pwm1_x_f_v"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,14 ,"pwm1_x_r_v"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"pwm1_v_id"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm1_v_we"                       },
};

/*------------------------------------------------
	0x10a8 PWM2_V
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM2_V[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,0  ,"pwm2_x_f_v"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,14 ,"pwm2_x_r_v"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"pwm2_v_id"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm2_v_we"                       },
};

/*------------------------------------------------
	0x10b0 PWM0_V_SUB
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM0_V_SUB[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,14 ,"pwm0_x_r_v_sub"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"pwm0_v_sub_id"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm0_v_we"                       },
};

/*------------------------------------------------
	0x10b4 PWM1_V_SUB
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM1_V_SUB[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,14 ,"pwm1_x_r_v_sub"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"pwm1_v_sub_id"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm1_v_sub_we"                   },
};

/*------------------------------------------------
	0x10b8 PWM2_V_SUB
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_PWM2_V_SUB[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,14 ,"pwm2_x_r_v_sub"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"pwm2_v_sub_id"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pwm2_v_sub_we"                   },
};

/*------------------------------------------------
	0x10c0 DEB_DLY_DISP_SYNC_DLY_PARAM
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DLY_DISP_SYNC_DLY_PARAM[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"dly_hoffset1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"dly_voffset1"                    },
};

/*------------------------------------------------
	0x10c4 DEB_DLY_DISP_SYNC_UPDATE
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DLY_DISP_SYNC_UPDATE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"dly_force_update"                },
};

/*------------------------------------------------
	0x10c8 DEB_DLY_DISP_SYNC_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DLY_DISP_SYNC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"h_active"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"v_active"                        },
};

/*------------------------------------------------
	0x10cc DEB_DEF_DISP_SYNC_SEL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DEF_DISP_SYNC_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"deb_def_fb_pe1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"deb_def_fb_ov"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"deb_def_output"                  },
};

/*------------------------------------------------
	0x10d0 DEB_OV_PIC_START_DLY_EN
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_OV_PIC_START_DLY_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"deb_ov_pic_start_dly_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"pic_end_g1_c_force_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"pic_end_g1_c_force_value"        },
};

/*------------------------------------------------
	0x10d4 DEB_PIC_INIT_G1_TIMER_C
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_INIT_G1_TIMER_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer_c"             },
};

/*------------------------------------------------
	0x10f8 DEB_GMAU_FLUSH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_GMAU_FLUSH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_flush_rd_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gmau_flush_wr_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done"              },
};

/*------------------------------------------------
	0x10fc DEB_MG_LS_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_MG_LS_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"deb_ls_override_mifb"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"deb_ls_override_pe1_l"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"deb_ls_override_ov_l"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"deb_ls_override_sm_l"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"deb_mg_override_mifb"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"deb_mg_override_pe1_l"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"deb_mg_override_ov_l"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"deb_mg_override_sm_l"            },
};

/*------------------------------------------------
	0x2000 DEC_PIC_INIT
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_init_g2"                     },
};

/*------------------------------------------------
	0x2004 DEC_PIC_START
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_start_g2"                    },
};

/*------------------------------------------------
	0x2008 DEC_SMUX_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SMUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"o_c_fmt"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"i_c_fmt"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec3d_mux_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"prew_mux_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"d3_lr_sel"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"cvi_mux_sel"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"nline_inc"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"wr_disalbe"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fieldid"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"size"                            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pr_sq"                           },
};

/*------------------------------------------------
	0x200c DEC_SMUX_SIZE
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SMUX_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsize"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"vsize"                           },
};

/*------------------------------------------------
	0x2010 DEC_MVI_V_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MVI_V_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_vsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_vblank"                      },
};

/*------------------------------------------------
	0x2014 DEC_MVI_H_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MVI_H_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_hsize"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_hblank"                      },
};

/*------------------------------------------------
	0x2018 DEC_MVI_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MVI_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"mvi_i_c_fmt"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mvi_field"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"mvi_pr_sq"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mvi_cvi_stride"                  },
};

/*------------------------------------------------
	0x201c DEC_MSRC_SYNC_MUX_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MSRC_SYNC_MUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"m_trans_mask_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"m_cvi_select"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"m_mvi_select"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"m_mvi_sync_select"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"m_mvi_cvi_select"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"m_cvia_vsync_inv"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"m_cvib_vsync_inv"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"m_vdec_vsync_inv"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"m_mem_vsync_inv"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"m_disp_sync_inv"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"m_disp_select"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"m_cvia_sync_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"m_cvib_sync_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"m_sync_manual_delay_en"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"m_ignore_src_vsync_fal"          },
};

/*------------------------------------------------
	0x2020 DEC_MSRC_SYNC_DLY
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MSRC_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dec_msrc_sync_dly"               },
};

/*------------------------------------------------
	0x2024 DEC_MEM0_SYNC_PERIOD
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MEM0_SYNC_PERIOD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dec_mem0_sync_period"            },
};

/*------------------------------------------------
	0x2028 DEC_MEM1_SYNC_PERIOD
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MEM1_SYNC_PERIOD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dec_mem1_sync_period"            },
};

/*------------------------------------------------
	0x202c DEC_SSMUX_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SSMUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"sub_o_c_fmt"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"sub_i_c_fmt"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"sub_src_mux_sel"                 },
};

/*------------------------------------------------
	0x2030 DEC_SSRC_SYNC_MUX_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SSRC_SYNC_MUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"s_trans_mask_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"s_cvi_select"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"s_mvi_select"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"s_mvi_sync_select"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"s_mvi_cvi_select"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"s_cvia_vsync_inv"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"s_cvib_vsync_inv"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"s_vdec_vsync_inv"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"s_mem_vsync_inv"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"s_disp_sync_inv"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"s_disp_select"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"s_cvia_sync_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"s_cvib_sync_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"s_sync_manual_delay_en"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"s_ignore_src_vsync_fal"          },
};

/*------------------------------------------------
	0x2034 DEC_SSRC_SYNC_DLY
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SSRC_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dec_ssrc_sync_dly"               },
};

/*------------------------------------------------
	0x2038 DEC_MD_CSC_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load_md_csc_coef"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"md_csc_en"                       },
};

/*------------------------------------------------
	0x203c DEC_MD_CSC_COEF0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef0"                    },
};

/*------------------------------------------------
	0x2040 DEC_MD_CSC_COEF1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef3"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef2"                    },
};

/*------------------------------------------------
	0x2044 DEC_MD_CSC_COEF2
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef5"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef4"                    },
};

/*------------------------------------------------
	0x2048 DEC_MD_CSC_COEF3
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef7"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef6"                    },
};

/*------------------------------------------------
	0x204c DEC_MD_CSC_COEF4
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"dec_md_csc_coef4"                },
};

/*------------------------------------------------
	0x2050 DEC_MD_CSC_OFFSET0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_OFFSET0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"md_csc_ofst1"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"md_csc_ofst0"                    },
};

/*------------------------------------------------
	0x2054 DEC_MD_CSC_OFFSET1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_OFFSET1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"md_csc_ofst3"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"md_csc_ofst2"                    },
};

/*------------------------------------------------
	0x2058 DEC_MD_CSC_OFFSET2
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_OFFSET2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"md_csc_ofst5"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"md_csc_ofst4"                    },
};

/*------------------------------------------------
	0x205c DEC_SMUX_RO_LCNT
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SMUX_RO_LCNT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"dec_smux_ro_lcnt"                },
};

/*------------------------------------------------
	0x2060 DEC_GMAU_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"                      },
};

/*------------------------------------------------
	0x2064 DEC_PIC_END_EN
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ipc_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tnr_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pe0_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"prew_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"smux_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"mvi_en"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"ss_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"ssm_en"                          },
};

/*------------------------------------------------
	0x2068 DEC_PIC_INIT_G0_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g0_timer"               },
};

/*------------------------------------------------
	0x206c DEC_PIC_INIT_G1_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer"               },
};

/*------------------------------------------------
	0x2070 DEC_PIC_INIT_G2_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT_G2_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g2_timer"               },
};

/*------------------------------------------------
	0x2074 DEC_PIC_END_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,5  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"pic_end_g2"                      },
};

/*------------------------------------------------
	0x2078 DEC_INTR_REG
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_end_g2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pe0_intr"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"smux_ow_intr"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"ssrc_intr"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"msrc_intr"                       },
};

/*------------------------------------------------
	0x207c DEC_INTR_MASK
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"dec_intr_mask"                   },
};

/*------------------------------------------------
	0x2080 DEC_INTR_MUX
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_INTR_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"dec_intr_mux"                    },
};

/*------------------------------------------------
	0x2084 DEC_MSRC_INTR_TIME_STP
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MSRC_INTR_TIME_STP[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"dec_msrc_intr_time_stp"          },
};

/*------------------------------------------------
	0x2088 DEC_SSRC_INTR_TIME_STP
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SSRC_INTR_TIME_STP[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"dec_ssrc_intr_time_stp"          },
};

/*------------------------------------------------
	0x208c DEC_ADDR_SW_DE_SAV
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dec_addr_sav_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"dec_addr_default_bus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dec_addr_de_bus"                 },
};

/*------------------------------------------------
	0x2090 DEC_ADDR_SW_CPU_GPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dec_addr_gpu_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dec_addr_gpu_logic"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"dec_addr_cpu_h_bus"              },
};

/*------------------------------------------------
	0x2094 DEC_ADDR_SW_CPU_SHADOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dec_addr_shadow_bus"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dec_addr_shadow_logic"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dec_addr_cpu_l_bus"              },
};

/*------------------------------------------------
	0x2098 DEC_GMAU_FLUSH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_GMAU_FLUSH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_flush_rd_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gmau_flush_wr_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done"              },
};

/*------------------------------------------------
	0x20a0 DEC_SMUX_SIZE_I
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SMUX_SIZE_I[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsize_i"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"vsize_i"                         },
};

/*------------------------------------------------
	0x20c0 DEC_DEA_MVI_CTRL_0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DEA_MVI_CTRL_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_h_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_h_width"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mvi_3d_ctrl_en"                  },
};

/*------------------------------------------------
	0x20c4 DEC_DEA_MVI_CTRL_1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DEA_MVI_CTRL_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_h_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_h_width"                       },
};

/*------------------------------------------------
	0x20c8 DEC_DEA_MVI_CTRL_2
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DEA_MVI_CTRL_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_v_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"y_v_height"                      },
};

/*------------------------------------------------
	0x20cc DEC_DEA_MVI_CTRL_3
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DEA_MVI_CTRL_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_v_offset"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"c_v_height"                      },
};

/*------------------------------------------------
	0x20d0 DEC_DEA_MVI_CTRL_4
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DEA_MVI_CTRL_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"h_sub_sample_step"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"y_h_even_line_sub_sample_offset" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"y_h_odd_line_sub_sample_offset"  },
};

/*------------------------------------------------
	0x20d4 DEC_DEA_MVI_CTRL_5
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DEA_MVI_CTRL_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"c_h_even_line_sub_sample_offset" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_h_odd_line_sub_sample_offset"  },
};

/*------------------------------------------------
	0x20d8 DEC_DEA_MVI_CTRL_6
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DEA_MVI_CTRL_6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"v_sub_sample_step"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"y_v_sub_sample_offset"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"c_v_sub_sample_offset"           },
};

/*------------------------------------------------
	0x20e0 DEC_PIC_START_DELAY_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_START_DELAY_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_delay_mvi"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_delay_mvi_y_rd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_start_delay_mvi_c_rd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_start_delay_smux"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"pic_start_delay_prew_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"pic_start_delay_prew_c_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pic_start_delay_prew_y_wd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pic_start_delay_prew_c_wd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pic_start_delay_pe0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"pic_start_delay_tnr0_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"pic_start_delay_tnr_c_rd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pic_start_delay_tnr_y_wd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pic_start_delay_tnr_c_wd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"pic_start_delay_ipc0_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"pic_start_delay_ipc1_y_rd"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pic_start_delay_ipc_c_rd"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"pic_start_delay_ss"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"pic_start_delay_ss_y_wd"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"pic_start_delay_ss_c_wd"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pic_start_delay_ss_y_rd"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"pic_start_delay_ss_c_rd"         },
};

/*------------------------------------------------
	0x20e4 DEC_PIC_START_G0_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_START_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_start_g0_timer"              },
};

/*------------------------------------------------
	0x20e8 DEC_PIC_START_G1_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_START_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_start_g1_timer"              },
};

/*------------------------------------------------
	0x20ec DEC_PIC_START_G2_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_START_G2_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_start_g2_timer"              },
};

/*------------------------------------------------
	0x20f4 DEC_PIC_END_FORCE
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_END_FORCE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dea_pic_end_g0_force"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"dea_pic_end_g0_force_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dea_pic_end_g1_force"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"dea_pic_end_g1_force_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"dea_pic_end_g2_force"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"dea_pic_end_g2_force_en"         },
};

/*------------------------------------------------
	0x20fc DEC_MG_LS_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MG_LS_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dec_ls_override_mifc"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"dec_ls_override_pe0_r"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"dec_ls_override_smux_r"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"dec_ls_override_ss"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"dec_mg_override_mifc"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"dec_mg_override_pe0_r"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"dec_mg_override_smux_r"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"dec_mg_override_ss"              },
};

/*------------------------------------------------
	0x3000 DED_PIC_INIT
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"ov_auto_init"                    },
};

/*------------------------------------------------
	0x3004 DED_PIC_START
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"                    },
};

/*------------------------------------------------
	0x3024 DED_GMAU_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"                      },
};

/*------------------------------------------------
	0x3028 DED_PIC_END_EN
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"ov_en"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"sm_en"                           },
};

/*------------------------------------------------
	0x302c DED_PIC_INIT_G0_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"ded_pic_init_g0_timer"           },
};

/*------------------------------------------------
	0x3030 DED_PIC_INIT_G1_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"ded_pic_init_g1_timer"           },
};

/*------------------------------------------------
	0x303c DED_PIC_END_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"pic_end_g0_info"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"pic_end_g1_info"                 },
};

/*------------------------------------------------
	0x3040 DED_INTR_REG
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ov_underflow"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"src_pulse"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pic_end_g1_c"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_don"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_rd_done"              },
};

/*------------------------------------------------
	0x3044 DED_INTR_MASK
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ov_underflow"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"src_pulse"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pic_end_g1_c"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_don"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_rd_done"              },
};

/*------------------------------------------------
	0x3048 DED_INTR_MUX
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_INTR_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ov_underflow"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"src_pulse"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pic_end_g1_c"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_don"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_rd_done"              },
};

/*------------------------------------------------
	0x3050 DED_ADDR_SW_DE_SAV
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"ded_addr_sav_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"ded_addr_default_bus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"ded_addr_de_bus"                 },
};

/*------------------------------------------------
	0x3054 DED_ADDR_SW_CPU_GPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"ded_addr_gpu_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"ded_addr_gpu_logic"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"ded_addr_cpu_h_bus"              },
};

/*------------------------------------------------
	0x3058 DED_ADDR_SW_CPU_SHADOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"ded_addr_shadow_bus"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"ded_addr_shadow_logic"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"ded_addr_cpu_l_bus"              },
};

/*------------------------------------------------
	0x30c0 DED_DLY_DISP_SYNC_PARAMS
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DLY_DISP_SYNC_PARAMS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"h_dly"                           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"v_dly"                           },
};

/*------------------------------------------------
	0x30c4 DED_DLY_DISP_SYNC_FORCE_UPDATE
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DLY_DISP_SYNC_FORCE_UPDATE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hoffset0"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"dly_force_update"                },
};

/*------------------------------------------------
	0x30c8 DED_DLY_DISP_SYNC_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DLY_DISP_SYNC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"h_active"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"v_active"                        },
};

/*------------------------------------------------
	0x30cc DED_DEF_DISP_SYNC_SEL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DEF_DISP_SYNC_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ded_def_pe1_r"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"deb_def_ov_r"                    },
};

/*------------------------------------------------
	0x30d0 DED_OV_PIC_START_DLY_EN
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_OV_PIC_START_DLY_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ded_ov_pic_start_dly_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"pic_end_g1_c_force_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"pic_end_g1_c_force_value"        },
};

/*------------------------------------------------
	0x30d4 DED_PIC_INIT_G1_TIMER_C
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT_G1_TIMER_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer_c"             },
};

/*------------------------------------------------
	0x30e0 DED_DLY_DISP_V_PORCH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DLY_DISP_V_PORCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"vsync_bp"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"vsync_fp"                        },
};

/*------------------------------------------------
	0x30e4 DED_DLY_DISP_VS_VA
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DLY_DISP_VS_VA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"disp_sync_va"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"vsync"                           },
};

/*------------------------------------------------
	0x30e8 DED_DLY_DISP_H_PORCH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DLY_DISP_H_PORCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hsync_bp"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"hsync_fp"                        },
};

/*------------------------------------------------
	0x30ec DED_DLY_DISP_HS_HA
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DLY_DISP_HS_HA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"disp_sync_ha"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"hsync"                           },
};

/*------------------------------------------------
	0x30f8 DED_GMAU_FLUSH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_GMAU_FLUSH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_flush_rd_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gmau_flush_wr_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done"              },
};

/*------------------------------------------------
	0x30fc DED_MG_LS_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_MG_LS_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ded_ls_override_mifd"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"ded_ls_override_pe1_r"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"ded_ls_override_sm_r"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"ded_ls_override_ov_r"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"ded_mg_override_mifd"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"ded_mg_override_pe1_r"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"ded_mg_override_sm_r"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"ded_mg_override_ov_r"            },
};

/*------------------------------------------------
	0x4000 DEC_DE_INTR_FLAG_MCU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DE_INTR_FLAG_MCU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dea_dee_intr_mcu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"deb_dee_intr_mcu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec_dee_intr_mcu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ded_dee_intr_mcu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"dee_dee_intr_mcu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"def_dee_intr_mcu"                },
};

/*------------------------------------------------
	0x4004 DEC_DE_INTR_FLAG_CPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DE_INTR_FLAG_CPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dea_dee_intr_cpu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"deb_dee_intr_cpu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec_dee_intr_cpu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ded_dee_intr_cpu"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"def_dee_intr_cpu"                },
};

/*------------------------------------------------
	0x4008 DEE_CVI_MUX_SEL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVI_MUX_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"cvib_sel"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"cvia_sel"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"extb_type"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"exta_type"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cvd_input_sel"                   },
};

/*------------------------------------------------
	0x400c DEE_PE0_HIF_OFFSET
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_PE0_HIF_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pe0_hif_offset_en"               },
};

/*------------------------------------------------
	0x4010 DEE_SM_HIF_OFFSET
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_SM_HIF_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"sm_hif_offset_en"                },
};

/*------------------------------------------------
	0x4014 DEE_PE1_HIF_OFFSET
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_PE1_HIF_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pe1_hif_offset_en"               },
};

/*------------------------------------------------
	0x4018 DEE_CVD_ADDR_SW_DE_SAV
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVD_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"cvd_addr_sav_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"mcu_addr_default_bus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"cvd_addr_de_bus"                 },
};

/*------------------------------------------------
	0x401c DEE_CVD_ADDR_SW_CPU_GPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVD_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"cvd_addr_gpu_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"cvd_addr_gpu_logic"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cvd_addr_cpu_h_bus"              },
};

/*------------------------------------------------
	0x4020 DEE_CVD_ADDR_SW_CPU_SHADOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVD_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"cvd_addr_shadow_bus"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"cvd_addr_shadow_logic"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"cvd_addr_cpu_l_bus"              },
};

/*------------------------------------------------
	0x4024 DEE_MCU_ADDR_SW_DE_SAV
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"mcu_addr_sav_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"mcu_addr_default_bus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"mcu_addr_de_bus"                 },
};

/*------------------------------------------------
	0x4028 DEE_MCU_ADDR_SW_CPU_GPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"mcu_addr_gpu_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"mcu_addr_gpu_logic"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"mcu_addr_cpu_h_bus"              },
};

/*------------------------------------------------
	0x402c DEE_MCU_ADDR_SW_CPU_SHADOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"mcu_addr_shadow_bus"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"mcu_addr_shadow_logic"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"mcu_addr_cpu_l_bus"              },
};

/*------------------------------------------------
	0x4030 DEE_MCU_ADDR_WINDOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_WINDOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"mcu_win_lower"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"mcu_win_upper"                   },
};

/*------------------------------------------------
	0x4034 DEE_INTR_REG
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dee_src_cvd"                     },
};

/*------------------------------------------------
	0x4038 DEE_INTR_MASK
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dee_cvd_intr_mask"               },
};

/*------------------------------------------------
	0x403c DEE_GMAU_FLUSH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_GMAU_FLUSH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_flush_rd_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gmau_flush_wr_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done"              },
};

/*------------------------------------------------
	0x40fc DEE_MG_LS_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MG_LS_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dee_ls_override_cvd_b00"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"dee_ls_override_cvd_b16"         },
};

/*------------------------------------------------
	0x5000 DEF_PIC_INIT
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_inti_g2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_init_g3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"osd_auto_init"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"atop_auto_init"                  },
};

/*------------------------------------------------
	0x5004 DEF_PIC_START
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_start_g2"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_start_g3"                    },
};

/*------------------------------------------------
	0x5008 DEF_DE_VENC_IF
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_DE_VENC_IF[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"venc_vsync"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"venc_sel"                        },
};

/*------------------------------------------------
	0x500c DEF_DPATH_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_DPATH_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"t3_mux_sel"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fb_mux_sel"                      },
};

/*------------------------------------------------
	0x5010 DEF_CVE_PARAM0
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_CVE_PARAM0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vertical_back_period"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vertical_sync_period"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vertical_front_period"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"vsync_polarity"                  },
};

/*------------------------------------------------
	0x5014 DEF_CVE_PARAM1
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_CVE_PARAM1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"horizontal_back_period"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"horizontal_sync_period"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_front_period"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"hsync_polarity"                  },
};

/*------------------------------------------------
	0x5018 DEF_CVE_PARAM2
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_CVE_PARAM2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"v_hoffset1"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,11 ,"v_hoffset0"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"field_id_polarity"               },
};

/*------------------------------------------------
	0x501c DEF_CVE_PARAM3
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_CVE_PARAM3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"cve_sync_ha"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"cve_sync_va"                     },
};

/*------------------------------------------------
	0x5020 DEF_CVE_PULSE_DLY
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_CVE_PULSE_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"def_cve_pulse_dly"               },
};

/*------------------------------------------------
	0x5024 DEF_GMAU_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"                      },
};

/*------------------------------------------------
	0x5028 DEF_PIC_END_EN
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"atop_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd_en"                          },
};

/*------------------------------------------------
	0x5034 DEF_PIC_INIT_G2_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_PIC_INIT_G2_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"def_pic_init_g2_timer"           },
};

/*------------------------------------------------
	0x5038 DEF_PIC_INIT_G3_TIMER
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_PIC_INIT_G3_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"def_pic_init_g3_timer"           },
};

/*------------------------------------------------
	0x503c DEF_PIC_END_INFO
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pic_end_g2_info"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pic_end_g3_info"                 },
};

/*------------------------------------------------
	0x5040 DEF_INTR_REG
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_end_g2"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_end_g3"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cve_pulse"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cve_va_pulse"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"cve_va_fal_pulse"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done_ris"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_rd_done_ris"          },
};

/*------------------------------------------------
	0x5044 DEF_INTR_MASK
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"def_intr_mask"                   },
};

/*------------------------------------------------
	0x5048 DEF_INTR_MUX
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_INTR_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"def_intr_mux"                    },
};

/*------------------------------------------------
	0x504c DEF_CVE_INTR_TIME_STP
------------------------------------------------*/
/* no field */

/*------------------------------------------------
	0x5050 DEF_ADDR_SW_DE_SAV
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"def_addr_sav_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"def_addr_default_bus"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"def_addr_de_bus"                 },
};

/*------------------------------------------------
	0x5054 DEF_ADDR_SW_CPU_GPU
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"def_addr_gpu_bus"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"def_addr_gpu_logic"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"def_addr_cpu_h_bus"              },
};

/*------------------------------------------------
	0x5058 DEF_ADDR_SW_CPU_SHADOW
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"def_addr_shadow_bus"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"def_addr_shadow_logic"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"def_addr_cpu_l_bus"              },
};

/*------------------------------------------------
	0x50f8 DEF_GMAU_FLUSH
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_GMAU_FLUSH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_flush_rd_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gmau_flush_wr_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gmau_flush_rd_done"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done"              },
};

/*------------------------------------------------
	0x50fc DEF_MG_LS_CTRL
------------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEF_MG_LS_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"def_ls_override_miff"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"def_ls_override_d3pp"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"def_ls_override_osd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"def_ls_override_atop"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"def_mg_override_miff"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"def_mg_override_d3pp"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"def_mg_override_osd"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"def_mg_override_atop"            },
};

DBG_REG_T gDbgRegCTR[] = {
	{ 0x0000 ,N_FLD(dbg_DEA_CHA_INFO)                        ,"DEA_CHA_INFO"                          ,dbg_DEA_CHA_INFO                        },
	{ 0x0004 ,N_FLD(dbg_DEA_CHB_INFO)                        ,"DEA_CHB_INFO"                          ,dbg_DEA_CHB_INFO                        },
	{ 0x0008 ,N_FLD(dbg_DEA_PIC_INIT)                        ,"DEA_PIC_INIT"                          ,dbg_DEA_PIC_INIT                        },
	{ 0x000c ,N_FLD(dbg_DEA_PIC_START)                       ,"DEA_PIC_START"                         ,dbg_DEA_PIC_START                       },
	{ 0x0010 ,N_FLD(dbg_DEA_SMUX_CTRL)                       ,"DEA_SMUX_CTRL"                         ,dbg_DEA_SMUX_CTRL                       },
	{ 0x0014 ,N_FLD(dbg_DEA_SMUX_SIZE)                       ,"DEA_SMUX_SIZE"                         ,dbg_DEA_SMUX_SIZE                       },
	{ 0x0018 ,N_FLD(dbg_DEA_MVI_V_INFO)                      ,"DEA_MVI_V_INFO"                        ,dbg_DEA_MVI_V_INFO                      },
	{ 0x001c ,N_FLD(dbg_DEA_MVI_H_INFO)                      ,"DEA_MVI_H_INFO"                        ,dbg_DEA_MVI_H_INFO                      },
	{ 0x0020 ,N_FLD(dbg_DEA_MVI_CTRL)                        ,"DEA_MVI_CTRL"                          ,dbg_DEA_MVI_CTRL                        },
	{ 0x0024 ,N_FLD(dbg_DEA_MSRC_SYNC_MUX_CTRL)              ,"DEA_MSRC_SYNC_MUX_CTRL"                ,dbg_DEA_MSRC_SYNC_MUX_CTRL              },
	{ 0x0028 ,N_FLD(dbg_DEA_MSRC_SYNC_DLY)                   ,"DEA_MSRC_SYNC_DLY"                     ,dbg_DEA_MSRC_SYNC_DLY                   },
	{ 0x002c ,N_FLD(dbg_DEA_MEM_SYNC_PERIOD)                 ,"DEA_MEM_SYNC_PERIOD"                   ,dbg_DEA_MEM_SYNC_PERIOD                 },
	{ 0x0030 ,N_FLD(dbg_DEA_DCO_MFC)                         ,"DEA_DCO_MFC"                           ,dbg_DEA_DCO_MFC                         },
	{ 0x0034 ,N_FLD(dbg_DEA_DCO_DFC)                         ,"DEA_DCO_DFC"                           ,dbg_DEA_DCO_DFC                         },
	{ 0x0038 ,N_FLD(dbg_DEA_DCO_DFLC)                        ,"DEA_DCO_DFLC"                          ,dbg_DEA_DCO_DFLC                        },
	{ 0x003c ,N_FLD(dbg_DEA_DCO_FCW)                         ,"DEA_DCO_FCW"                           ,dbg_DEA_DCO_FCW                         },
	{ 0x0040 ,N_FLD(dbg_DEA_SMUX_RO_LCNT)                    ,"DEA_SMUX_RO_LCNT"                      ,dbg_DEA_SMUX_RO_LCNT                    },
	{ 0x0044 ,N_FLD(dbg_DEA_GMAU_CTRL)                       ,"DEA_GMAU_CTRL"                         ,dbg_DEA_GMAU_CTRL                       },
	{ 0x0048 ,N_FLD(dbg_DEA_PIC_END_EN)                      ,"DEA_PIC_END_EN"                        ,dbg_DEA_PIC_END_EN                      },
	{ 0x004c ,N_FLD(dbg_DEA_PIC_INIT_G0_TIMER)               ,"DEA_PIC_INIT_G0_TIMER"                 ,dbg_DEA_PIC_INIT_G0_TIMER               },
	{ 0x0050 ,N_FLD(dbg_DEA_PIC_INIT_G1_TIMER)               ,"DEA_PIC_INIT_G1_TIMER"                 ,dbg_DEA_PIC_INIT_G1_TIMER               },
	{ 0x0054 ,N_FLD(dbg_DEA_PIC_END_INFO)                    ,"DEA_PIC_END_INFO"                      ,dbg_DEA_PIC_END_INFO                    },
	{ 0x0058 ,N_FLD(dbg_DEA_INTR_REG)                        ,"DEA_INTR_REG"                          ,dbg_DEA_INTR_REG                        },
	{ 0x005c ,N_FLD(dbg_DEA_INTR_MASK)                       ,"DEA_INTR_MASK"                         ,dbg_DEA_INTR_MASK                       },
	{ 0x0060 ,N_FLD(dbg_DEA_INTR_MUX)                        ,"DEA_INTR_MUX"                          ,dbg_DEA_INTR_MUX                        },
	{ 0x0064 ,N_FLD(dbg_DEA_SRC_INTR_TIME_STP)               ,"DEA_SRC_INTR_TIME_STP"                 ,dbg_DEA_SRC_INTR_TIME_STP               },
	{ 0x0068 ,N_FLD(dbg_DE_GPIO_MUX)                         ,"DE_GPIO_MUX"                           ,dbg_DE_GPIO_MUX                         },
	{ 0x006c ,N_FLD(dbg_DEA_ADDR_SW_DE_SAV)                  ,"DEA_ADDR_SW_DE_SAV"                    ,dbg_DEA_ADDR_SW_DE_SAV                  },
	{ 0x0070 ,N_FLD(dbg_DEA_ADDR_SW_CPU_GPU)                 ,"DEA_ADDR_SW_CPU_GPU"                   ,dbg_DEA_ADDR_SW_CPU_GPU                 },
	{ 0x0074 ,N_FLD(dbg_DEA_ADDR_SW_CPU_SHADOW)              ,"DEA_ADDR_SW_CPU_SHADOW"                ,dbg_DEA_ADDR_SW_CPU_SHADOW              },
	{ 0x007c ,N_FLD(dbg_DE_VERSION)                          ,"DE_VERSION"                            ,dbg_DE_VERSION                          },
	{ 0x0080 ,N_FLD(dbg_DEA_SMUX_SIZE_I)                     ,"DEA_SMUX_SIZE_I"                       ,dbg_DEA_SMUX_SIZE_I                     },
	{ 0x00c0 ,N_FLD(dbg_DEA_DEA_MVI_CTRL_0)                  ,"DEA_DEA_MVI_CTRL_0"                    ,dbg_DEA_DEA_MVI_CTRL_0                  },
	{ 0x00c4 ,N_FLD(dbg_DEA_DEA_MVI_CTRL_1)                  ,"DEA_DEA_MVI_CTRL_1"                    ,dbg_DEA_DEA_MVI_CTRL_1                  },
	{ 0x00c8 ,N_FLD(dbg_DEA_DEA_MVI_CTRL_2)                  ,"DEA_DEA_MVI_CTRL_2"                    ,dbg_DEA_DEA_MVI_CTRL_2                  },
	{ 0x00cc ,N_FLD(dbg_DEA_DEA_MVI_CTRL_3)                  ,"DEA_DEA_MVI_CTRL_3"                    ,dbg_DEA_DEA_MVI_CTRL_3                  },
	{ 0x00d0 ,N_FLD(dbg_DEA_DEA_MVI_CTRL_4)                  ,"DEA_DEA_MVI_CTRL_4"                    ,dbg_DEA_DEA_MVI_CTRL_4                  },
	{ 0x00d4 ,N_FLD(dbg_DEA_DEA_MVI_CTRL_5)                  ,"DEA_DEA_MVI_CTRL_5"                    ,dbg_DEA_DEA_MVI_CTRL_5                  },
	{ 0x00d8 ,N_FLD(dbg_DEA_DEA_MVI_CTRL_6)                  ,"DEA_DEA_MVI_CTRL_6"                    ,dbg_DEA_DEA_MVI_CTRL_6                  },
	{ 0x00e0 ,N_FLD(dbg_DEA_PIC_START_DELAY_CTRL)            ,"DEA_PIC_START_DELAY_CTRL"              ,dbg_DEA_PIC_START_DELAY_CTRL            },
	{ 0x00e4 ,N_FLD(dbg_DEA_PIC_START_G0_TIMER)              ,"DEA_PIC_START_G0_TIMER"                ,dbg_DEA_PIC_START_G0_TIMER              },
	{ 0x00e8 ,N_FLD(dbg_DEA_PIC_START_G1_TIMER)              ,"DEA_PIC_START_G1_TIMER"                ,dbg_DEA_PIC_START_G1_TIMER              },
	{ 0x00f4 ,N_FLD(dbg_DEA_PIC_END_FORCE)                   ,"DEA_PIC_END_FORCE"                     ,dbg_DEA_PIC_END_FORCE                   },
	{ 0x00f8 ,N_FLD(dbg_DEA_GMAU_FLUSH)                      ,"DEA_GMAU_FLUSH"                        ,dbg_DEA_GMAU_FLUSH                      },
	{ 0x00fc ,N_FLD(dbg_DEA_MG_LS_CTRL)                      ,"DEA_MG_LS_CTRL"                        ,dbg_DEA_MG_LS_CTRL                      },
	{ 0x1000 ,N_FLD(dbg_DEB_PIC_INIT)                        ,"DEB_PIC_INIT"                          ,dbg_DEB_PIC_INIT                        },
	{ 0x1004 ,N_FLD(dbg_DEB_PIC_START)                       ,"DEB_PIC_START"                         ,dbg_DEB_PIC_START                       },
	{ 0x1008 ,N_FLD(dbg_DEB_DISP_V_PORCH)                    ,"DEB_DISP_V_PORCH"                      ,dbg_DEB_DISP_V_PORCH                    },
	{ 0x100c ,N_FLD(dbg_DEB_DISP_VS_VA)                      ,"DEB_DISP_VS_VA"                        ,dbg_DEB_DISP_VS_VA                      },
	{ 0x1010 ,N_FLD(dbg_DEB_DISP_H_PORCH)                    ,"DEB_DISP_H_PORCH"                      ,dbg_DEB_DISP_H_PORCH                    },
	{ 0x1014 ,N_FLD(dbg_DEB_DISP_HS_HA)                      ,"DEB_DISP_HS_HA"                        ,dbg_DEB_DISP_HS_HA                      },
	{ 0x1018 ,N_FLD(dbg_DEB_DISP_SYNC_DLY)                   ,"DEB_DISP_SYNC_DLY"                     ,dbg_DEB_DISP_SYNC_DLY                   },
	{ 0x101c ,N_FLD(dbg_DEB_DISP_PULSE_DLY)                  ,"DEB_DISP_PULSE_DLY"                    ,dbg_DEB_DISP_PULSE_DLY                  },
	{ 0x1020 ,N_FLD(dbg_DEB_DISP_SYNC_PARAMS)                ,"DEB_DISP_SYNC_PARAMS"                  ,dbg_DEB_DISP_SYNC_PARAMS                },
	{ 0x102c ,N_FLD(dbg_DEB_PWM0_CTRL0)                      ,"DEB_PWM0_CTRL0"                        ,dbg_DEB_PWM0_CTRL0                      },
	{ 0x1030 ,N_FLD(dbg_DEB_PWM0_CTRL1)                      ,"DEB_PWM0_CTRL1"                        ,dbg_DEB_PWM0_CTRL1                      },
	{ 0x1034 ,N_FLD(dbg_DEB_PWM1_CTRL0)                      ,"DEB_PWM1_CTRL0"                        ,dbg_DEB_PWM1_CTRL0                      },
	{ 0x1038 ,N_FLD(dbg_DEB_PWM1_CTRL1)                      ,"DEB_PWM1_CTRL1"                        ,dbg_DEB_PWM1_CTRL1                      },
	{ 0x103c ,N_FLD(dbg_DEB_PWM2_CTRL0)                      ,"DEB_PWM2_CTRL0"                        ,dbg_DEB_PWM2_CTRL0                      },
	{ 0x1040 ,N_FLD(dbg_DEB_PWM2_CTRL1)                      ,"DEB_PWM2_CTRL1"                        ,dbg_DEB_PWM2_CTRL1                      },
	{ 0x1044 ,N_FLD(dbg_DEB_PWM3_CTRL)                       ,"DEB_PWM3_CTRL"                         ,dbg_DEB_PWM3_CTRL                       },
	{ 0x1048 ,N_FLD(dbg_PWM3_0_LOW)                          ,"PWM3_0_LOW"                            ,dbg_PWM3_0_LOW                          },
	{ 0x104c ,N_FLD(dbg_PWM3_0_HIGH)                         ,"PWM3_0_HIGH"                           ,dbg_PWM3_0_HIGH                         },
	{ 0x1050 ,N_FLD(dbg_PWM3_1_LOW)                          ,"PWM3_1_LOW"                            ,dbg_PWM3_1_LOW                          },
	{ 0x1054 ,N_FLD(dbg_PWM3_1_HIGH)                         ,"PWM3_1_HIGH"                           ,dbg_PWM3_1_HIGH                         },
	{ 0x1058 ,N_FLD(dbg_PWM3_2_LOW)                          ,"PWM3_2_LOW"                            ,dbg_PWM3_2_LOW                          },
	{ 0x105c ,N_FLD(dbg_PWM3_2_HIGH)                         ,"PWM3_2_HIGH"                           ,dbg_PWM3_2_HIGH                         },
	{ 0x1060 ,N_FLD(dbg_PWM3_3_LOW)                          ,"PWM3_3_LOW"                            ,dbg_PWM3_3_LOW                          },
	{ 0x1064 ,N_FLD(dbg_PWM3_3_HIGH)                         ,"PWM3_3_HIGH"                           ,dbg_PWM3_3_HIGH                         },
	{ 0x1068 ,N_FLD(dbg_DEB_DPATH_CTRL)                      ,"DEB_DPATH_CTRL"                        ,dbg_DEB_DPATH_CTRL                      },
	{ 0x106c ,N_FLD(dbg_DEB_GMAU_CTRL)                       ,"DEB_GMAU_CTRL"                         ,dbg_DEB_GMAU_CTRL                       },
	{ 0x1070 ,N_FLD(dbg_DEB_PIC_END_EN)                      ,"DEB_PIC_END_EN"                        ,dbg_DEB_PIC_END_EN                      },
	{ 0x1074 ,N_FLD(dbg_DEB_PIC_INIT_G0_TIMER)               ,"DEB_PIC_INIT_G0_TIMER"                 ,dbg_DEB_PIC_INIT_G0_TIMER               },
	{ 0x1078 ,N_FLD(dbg_DEB_PIC_INIT_G1_TIMER)               ,"DEB_PIC_INIT_G1_TIMER"                 ,dbg_DEB_PIC_INIT_G1_TIMER               },
	{ 0x107c ,N_FLD(dbg_DEB_PIC_END_INFO)                    ,"DEB_PIC_END_INFO"                      ,dbg_DEB_PIC_END_INFO                    },
	{ 0x1080 ,N_FLD(dbg_DEB_INTR_REG)                        ,"DEB_INTR_REG"                          ,dbg_DEB_INTR_REG                        },
	{ 0x1084 ,N_FLD(dbg_DEB_INTR_MASK)                       ,"DEB_INTR_MASK"                         ,dbg_DEB_INTR_MASK                       },
	{ 0x1088 ,N_FLD(dbg_DEB_INTR_MUX)                        ,"DEB_INTR_MUX"                          ,dbg_DEB_INTR_MUX                        },
	{ 0x108c ,N_FLD(dbg_DEB_DISP_INTR_TIME_STP)              ,"DEB_DISP_INTR_TIME_STP"                ,dbg_DEB_DISP_INTR_TIME_STP              },
	{ 0x1090 ,N_FLD(dbg_DEB_ADDR_SW_DE_SAV)                  ,"DEB_ADDR_SW_DE_SAV"                    ,dbg_DEB_ADDR_SW_DE_SAV                  },
	{ 0x1094 ,N_FLD(dbg_DEB_ADDR_SW_CPU_GPU)                 ,"DEB_ADDR_SW_CPU_GPU"                   ,dbg_DEB_ADDR_SW_CPU_GPU                 },
	{ 0x1098 ,N_FLD(dbg_DEB_ADDR_SW_CPU_SHADOW)              ,"DEB_ADDR_SW_CPU_SHADOW"                ,dbg_DEB_ADDR_SW_CPU_SHADOW              },
	{ 0x10a0 ,N_FLD(dbg_PWM0_V)                              ,"PWM0_V"                                ,dbg_PWM0_V                              },
	{ 0x10a4 ,N_FLD(dbg_PWM1_V)                              ,"PWM1_V"                                ,dbg_PWM1_V                              },
	{ 0x10a8 ,N_FLD(dbg_PWM2_V)                              ,"PWM2_V"                                ,dbg_PWM2_V                              },
	{ 0x10b0 ,N_FLD(dbg_PWM0_V_SUB)                          ,"PWM0_V_SUB"                            ,dbg_PWM0_V_SUB                          },
	{ 0x10b4 ,N_FLD(dbg_PWM1_V_SUB)                          ,"PWM1_V_SUB"                            ,dbg_PWM1_V_SUB                          },
	{ 0x10b8 ,N_FLD(dbg_PWM2_V_SUB)                          ,"PWM2_V_SUB"                            ,dbg_PWM2_V_SUB                          },
	{ 0x10c0 ,N_FLD(dbg_DEB_DLY_DISP_SYNC_DLY_PARAM)         ,"DEB_DLY_DISP_SYNC_DLY_PARAM"           ,dbg_DEB_DLY_DISP_SYNC_DLY_PARAM         },
	{ 0x10c4 ,N_FLD(dbg_DEB_DLY_DISP_SYNC_UPDATE)            ,"DEB_DLY_DISP_SYNC_UPDATE"              ,dbg_DEB_DLY_DISP_SYNC_UPDATE            },
	{ 0x10c8 ,N_FLD(dbg_DEB_DLY_DISP_SYNC_CTRL)              ,"DEB_DLY_DISP_SYNC_CTRL"                ,dbg_DEB_DLY_DISP_SYNC_CTRL              },
	{ 0x10cc ,N_FLD(dbg_DEB_DEF_DISP_SYNC_SEL)               ,"DEB_DEF_DISP_SYNC_SEL"                 ,dbg_DEB_DEF_DISP_SYNC_SEL               },
	{ 0x10d0 ,N_FLD(dbg_DEB_OV_PIC_START_DLY_EN)             ,"DEB_OV_PIC_START_DLY_EN"               ,dbg_DEB_OV_PIC_START_DLY_EN             },
	{ 0x10d4 ,N_FLD(dbg_DEB_PIC_INIT_G1_TIMER_C)             ,"DEB_PIC_INIT_G1_TIMER_C"               ,dbg_DEB_PIC_INIT_G1_TIMER_C             },
	{ 0x10f8 ,N_FLD(dbg_DEB_GMAU_FLUSH)                      ,"DEB_GMAU_FLUSH"                        ,dbg_DEB_GMAU_FLUSH                      },
	{ 0x10fc ,N_FLD(dbg_DEB_MG_LS_CTRL)                      ,"DEB_MG_LS_CTRL"                        ,dbg_DEB_MG_LS_CTRL                      },
	{ 0x2000 ,N_FLD(dbg_DEC_PIC_INIT)                        ,"DEC_PIC_INIT"                          ,dbg_DEC_PIC_INIT                        },
	{ 0x2004 ,N_FLD(dbg_DEC_PIC_START)                       ,"DEC_PIC_START"                         ,dbg_DEC_PIC_START                       },
	{ 0x2008 ,N_FLD(dbg_DEC_SMUX_CTRL)                       ,"DEC_SMUX_CTRL"                         ,dbg_DEC_SMUX_CTRL                       },
	{ 0x200c ,N_FLD(dbg_DEC_SMUX_SIZE)                       ,"DEC_SMUX_SIZE"                         ,dbg_DEC_SMUX_SIZE                       },
	{ 0x2010 ,N_FLD(dbg_DEC_MVI_V_INFO)                      ,"DEC_MVI_V_INFO"                        ,dbg_DEC_MVI_V_INFO                      },
	{ 0x2014 ,N_FLD(dbg_DEC_MVI_H_INFO)                      ,"DEC_MVI_H_INFO"                        ,dbg_DEC_MVI_H_INFO                      },
	{ 0x2018 ,N_FLD(dbg_DEC_MVI_CTRL)                        ,"DEC_MVI_CTRL"                          ,dbg_DEC_MVI_CTRL                        },
	{ 0x201c ,N_FLD(dbg_DEC_MSRC_SYNC_MUX_CTRL)              ,"DEC_MSRC_SYNC_MUX_CTRL"                ,dbg_DEC_MSRC_SYNC_MUX_CTRL              },
	{ 0x2020 ,N_FLD(dbg_DEC_MSRC_SYNC_DLY)                   ,"DEC_MSRC_SYNC_DLY"                     ,dbg_DEC_MSRC_SYNC_DLY                   },
	{ 0x2024 ,N_FLD(dbg_DEC_MEM0_SYNC_PERIOD)                ,"DEC_MEM0_SYNC_PERIOD"                  ,dbg_DEC_MEM0_SYNC_PERIOD                },
	{ 0x2028 ,N_FLD(dbg_DEC_MEM1_SYNC_PERIOD)                ,"DEC_MEM1_SYNC_PERIOD"                  ,dbg_DEC_MEM1_SYNC_PERIOD                },
	{ 0x202c ,N_FLD(dbg_DEC_SSMUX_CTRL)                      ,"DEC_SSMUX_CTRL"                        ,dbg_DEC_SSMUX_CTRL                      },
	{ 0x2030 ,N_FLD(dbg_DEC_SSRC_SYNC_MUX_CTRL)              ,"DEC_SSRC_SYNC_MUX_CTRL"                ,dbg_DEC_SSRC_SYNC_MUX_CTRL              },
	{ 0x2034 ,N_FLD(dbg_DEC_SSRC_SYNC_DLY)                   ,"DEC_SSRC_SYNC_DLY"                     ,dbg_DEC_SSRC_SYNC_DLY                   },
	{ 0x2038 ,N_FLD(dbg_DEC_MD_CSC_CTRL)                     ,"DEC_MD_CSC_CTRL"                       ,dbg_DEC_MD_CSC_CTRL                     },
	{ 0x203c ,N_FLD(dbg_DEC_MD_CSC_COEF0)                    ,"DEC_MD_CSC_COEF0"                      ,dbg_DEC_MD_CSC_COEF0                    },
	{ 0x2040 ,N_FLD(dbg_DEC_MD_CSC_COEF1)                    ,"DEC_MD_CSC_COEF1"                      ,dbg_DEC_MD_CSC_COEF1                    },
	{ 0x2044 ,N_FLD(dbg_DEC_MD_CSC_COEF2)                    ,"DEC_MD_CSC_COEF2"                      ,dbg_DEC_MD_CSC_COEF2                    },
	{ 0x2048 ,N_FLD(dbg_DEC_MD_CSC_COEF3)                    ,"DEC_MD_CSC_COEF3"                      ,dbg_DEC_MD_CSC_COEF3                    },
	{ 0x204c ,N_FLD(dbg_DEC_MD_CSC_COEF4)                    ,"DEC_MD_CSC_COEF4"                      ,dbg_DEC_MD_CSC_COEF4                    },
	{ 0x2050 ,N_FLD(dbg_DEC_MD_CSC_OFFSET0)                  ,"DEC_MD_CSC_OFFSET0"                    ,dbg_DEC_MD_CSC_OFFSET0                  },
	{ 0x2054 ,N_FLD(dbg_DEC_MD_CSC_OFFSET1)                  ,"DEC_MD_CSC_OFFSET1"                    ,dbg_DEC_MD_CSC_OFFSET1                  },
	{ 0x2058 ,N_FLD(dbg_DEC_MD_CSC_OFFSET2)                  ,"DEC_MD_CSC_OFFSET2"                    ,dbg_DEC_MD_CSC_OFFSET2                  },
	{ 0x205c ,N_FLD(dbg_DEC_SMUX_RO_LCNT)                    ,"DEC_SMUX_RO_LCNT"                      ,dbg_DEC_SMUX_RO_LCNT                    },
	{ 0x2060 ,N_FLD(dbg_DEC_GMAU_CTRL)                       ,"DEC_GMAU_CTRL"                         ,dbg_DEC_GMAU_CTRL                       },
	{ 0x2064 ,N_FLD(dbg_DEC_PIC_END_EN)                      ,"DEC_PIC_END_EN"                        ,dbg_DEC_PIC_END_EN                      },
	{ 0x2068 ,N_FLD(dbg_DEC_PIC_INIT_G0_TIMER)               ,"DEC_PIC_INIT_G0_TIMER"                 ,dbg_DEC_PIC_INIT_G0_TIMER               },
	{ 0x206c ,N_FLD(dbg_DEC_PIC_INIT_G1_TIMER)               ,"DEC_PIC_INIT_G1_TIMER"                 ,dbg_DEC_PIC_INIT_G1_TIMER               },
	{ 0x2070 ,N_FLD(dbg_DEC_PIC_INIT_G2_TIMER)               ,"DEC_PIC_INIT_G2_TIMER"                 ,dbg_DEC_PIC_INIT_G2_TIMER               },
	{ 0x2074 ,N_FLD(dbg_DEC_PIC_END_INFO)                    ,"DEC_PIC_END_INFO"                      ,dbg_DEC_PIC_END_INFO                    },
	{ 0x2078 ,N_FLD(dbg_DEC_INTR_REG)                        ,"DEC_INTR_REG"                          ,dbg_DEC_INTR_REG                        },
	{ 0x207c ,N_FLD(dbg_DEC_INTR_MASK)                       ,"DEC_INTR_MASK"                         ,dbg_DEC_INTR_MASK                       },
	{ 0x2080 ,N_FLD(dbg_DEC_INTR_MUX)                        ,"DEC_INTR_MUX"                          ,dbg_DEC_INTR_MUX                        },
	{ 0x2084 ,N_FLD(dbg_DEC_MSRC_INTR_TIME_STP)              ,"DEC_MSRC_INTR_TIME_STP"                ,dbg_DEC_MSRC_INTR_TIME_STP              },
	{ 0x2088 ,N_FLD(dbg_DEC_SSRC_INTR_TIME_STP)              ,"DEC_SSRC_INTR_TIME_STP"                ,dbg_DEC_SSRC_INTR_TIME_STP              },
	{ 0x208c ,N_FLD(dbg_DEC_ADDR_SW_DE_SAV)                  ,"DEC_ADDR_SW_DE_SAV"                    ,dbg_DEC_ADDR_SW_DE_SAV                  },
	{ 0x2090 ,N_FLD(dbg_DEC_ADDR_SW_CPU_GPU)                 ,"DEC_ADDR_SW_CPU_GPU"                   ,dbg_DEC_ADDR_SW_CPU_GPU                 },
	{ 0x2094 ,N_FLD(dbg_DEC_ADDR_SW_CPU_SHADOW)              ,"DEC_ADDR_SW_CPU_SHADOW"                ,dbg_DEC_ADDR_SW_CPU_SHADOW              },
	{ 0x2098 ,N_FLD(dbg_DEC_GMAU_FLUSH)                      ,"DEC_GMAU_FLUSH"                        ,dbg_DEC_GMAU_FLUSH                      },
	{ 0x20a0 ,N_FLD(dbg_DEC_SMUX_SIZE_I)                     ,"DEC_SMUX_SIZE_I"                       ,dbg_DEC_SMUX_SIZE_I                     },
	{ 0x20c0 ,N_FLD(dbg_DEC_DEA_MVI_CTRL_0)                  ,"DEC_DEA_MVI_CTRL_0"                    ,dbg_DEC_DEA_MVI_CTRL_0                  },
	{ 0x20c4 ,N_FLD(dbg_DEC_DEA_MVI_CTRL_1)                  ,"DEC_DEA_MVI_CTRL_1"                    ,dbg_DEC_DEA_MVI_CTRL_1                  },
	{ 0x20c8 ,N_FLD(dbg_DEC_DEA_MVI_CTRL_2)                  ,"DEC_DEA_MVI_CTRL_2"                    ,dbg_DEC_DEA_MVI_CTRL_2                  },
	{ 0x20cc ,N_FLD(dbg_DEC_DEA_MVI_CTRL_3)                  ,"DEC_DEA_MVI_CTRL_3"                    ,dbg_DEC_DEA_MVI_CTRL_3                  },
	{ 0x20d0 ,N_FLD(dbg_DEC_DEA_MVI_CTRL_4)                  ,"DEC_DEA_MVI_CTRL_4"                    ,dbg_DEC_DEA_MVI_CTRL_4                  },
	{ 0x20d4 ,N_FLD(dbg_DEC_DEA_MVI_CTRL_5)                  ,"DEC_DEA_MVI_CTRL_5"                    ,dbg_DEC_DEA_MVI_CTRL_5                  },
	{ 0x20d8 ,N_FLD(dbg_DEC_DEA_MVI_CTRL_6)                  ,"DEC_DEA_MVI_CTRL_6"                    ,dbg_DEC_DEA_MVI_CTRL_6                  },
	{ 0x20e0 ,N_FLD(dbg_DEC_PIC_START_DELAY_CTRL)            ,"DEC_PIC_START_DELAY_CTRL"              ,dbg_DEC_PIC_START_DELAY_CTRL            },
	{ 0x20e4 ,N_FLD(dbg_DEC_PIC_START_G0_TIMER)              ,"DEC_PIC_START_G0_TIMER"                ,dbg_DEC_PIC_START_G0_TIMER              },
	{ 0x20e8 ,N_FLD(dbg_DEC_PIC_START_G1_TIMER)              ,"DEC_PIC_START_G1_TIMER"                ,dbg_DEC_PIC_START_G1_TIMER              },
	{ 0x20ec ,N_FLD(dbg_DEC_PIC_START_G2_TIMER)              ,"DEC_PIC_START_G2_TIMER"                ,dbg_DEC_PIC_START_G2_TIMER              },
	{ 0x20f4 ,N_FLD(dbg_DEC_PIC_END_FORCE)                   ,"DEC_PIC_END_FORCE"                     ,dbg_DEC_PIC_END_FORCE                   },
	{ 0x20fc ,N_FLD(dbg_DEC_MG_LS_CTRL)                      ,"DEC_MG_LS_CTRL"                        ,dbg_DEC_MG_LS_CTRL                      },
	{ 0x3000 ,N_FLD(dbg_DED_PIC_INIT)                        ,"DED_PIC_INIT"                          ,dbg_DED_PIC_INIT                        },
	{ 0x3004 ,N_FLD(dbg_DED_PIC_START)                       ,"DED_PIC_START"                         ,dbg_DED_PIC_START                       },
	{ 0x3024 ,N_FLD(dbg_DED_GMAU_CTRL)                       ,"DED_GMAU_CTRL"                         ,dbg_DED_GMAU_CTRL                       },
	{ 0x3028 ,N_FLD(dbg_DED_PIC_END_EN)                      ,"DED_PIC_END_EN"                        ,dbg_DED_PIC_END_EN                      },
	{ 0x302c ,N_FLD(dbg_DED_PIC_INIT_G0_TIMER)               ,"DED_PIC_INIT_G0_TIMER"                 ,dbg_DED_PIC_INIT_G0_TIMER               },
	{ 0x3030 ,N_FLD(dbg_DED_PIC_INIT_G1_TIMER)               ,"DED_PIC_INIT_G1_TIMER"                 ,dbg_DED_PIC_INIT_G1_TIMER               },
	{ 0x303c ,N_FLD(dbg_DED_PIC_END_INFO)                    ,"DED_PIC_END_INFO"                      ,dbg_DED_PIC_END_INFO                    },
	{ 0x3040 ,N_FLD(dbg_DED_INTR_REG)                        ,"DED_INTR_REG"                          ,dbg_DED_INTR_REG                        },
	{ 0x3044 ,N_FLD(dbg_DED_INTR_MASK)                       ,"DED_INTR_MASK"                         ,dbg_DED_INTR_MASK                       },
	{ 0x3048 ,N_FLD(dbg_DED_INTR_MUX)                        ,"DED_INTR_MUX"                          ,dbg_DED_INTR_MUX                        },
	{ 0x3050 ,N_FLD(dbg_DED_ADDR_SW_DE_SAV)                  ,"DED_ADDR_SW_DE_SAV"                    ,dbg_DED_ADDR_SW_DE_SAV                  },
	{ 0x3054 ,N_FLD(dbg_DED_ADDR_SW_CPU_GPU)                 ,"DED_ADDR_SW_CPU_GPU"                   ,dbg_DED_ADDR_SW_CPU_GPU                 },
	{ 0x3058 ,N_FLD(dbg_DED_ADDR_SW_CPU_SHADOW)              ,"DED_ADDR_SW_CPU_SHADOW"                ,dbg_DED_ADDR_SW_CPU_SHADOW              },
	{ 0x30c0 ,N_FLD(dbg_DED_DLY_DISP_SYNC_PARAMS)            ,"DED_DLY_DISP_SYNC_PARAMS"              ,dbg_DED_DLY_DISP_SYNC_PARAMS            },
	{ 0x30c4 ,N_FLD(dbg_DED_DLY_DISP_SYNC_FORCE_UPDATE)      ,"DED_DLY_DISP_SYNC_FORCE_UPDATE"        ,dbg_DED_DLY_DISP_SYNC_FORCE_UPDATE      },
	{ 0x30c8 ,N_FLD(dbg_DED_DLY_DISP_SYNC_CTRL)              ,"DED_DLY_DISP_SYNC_CTRL"                ,dbg_DED_DLY_DISP_SYNC_CTRL              },
	{ 0x30cc ,N_FLD(dbg_DED_DEF_DISP_SYNC_SEL)               ,"DED_DEF_DISP_SYNC_SEL"                 ,dbg_DED_DEF_DISP_SYNC_SEL               },
	{ 0x30d0 ,N_FLD(dbg_DED_OV_PIC_START_DLY_EN)             ,"DED_OV_PIC_START_DLY_EN"               ,dbg_DED_OV_PIC_START_DLY_EN             },
	{ 0x30d4 ,N_FLD(dbg_DED_PIC_INIT_G1_TIMER_C)             ,"DED_PIC_INIT_G1_TIMER_C"               ,dbg_DED_PIC_INIT_G1_TIMER_C             },
	{ 0x30e0 ,N_FLD(dbg_DED_DLY_DISP_V_PORCH)                ,"DED_DLY_DISP_V_PORCH"                  ,dbg_DED_DLY_DISP_V_PORCH                },
	{ 0x30e4 ,N_FLD(dbg_DED_DLY_DISP_VS_VA)                  ,"DED_DLY_DISP_VS_VA"                    ,dbg_DED_DLY_DISP_VS_VA                  },
	{ 0x30e8 ,N_FLD(dbg_DED_DLY_DISP_H_PORCH)                ,"DED_DLY_DISP_H_PORCH"                  ,dbg_DED_DLY_DISP_H_PORCH                },
	{ 0x30ec ,N_FLD(dbg_DED_DLY_DISP_HS_HA)                  ,"DED_DLY_DISP_HS_HA"                    ,dbg_DED_DLY_DISP_HS_HA                  },
	{ 0x30f8 ,N_FLD(dbg_DED_GMAU_FLUSH)                      ,"DED_GMAU_FLUSH"                        ,dbg_DED_GMAU_FLUSH                      },
	{ 0x30fc ,N_FLD(dbg_DED_MG_LS_CTRL)                      ,"DED_MG_LS_CTRL"                        ,dbg_DED_MG_LS_CTRL                      },
	{ 0x4000 ,N_FLD(dbg_DEC_DE_INTR_FLAG_MCU)                ,"DEC_DE_INTR_FLAG_MCU"                  ,dbg_DEC_DE_INTR_FLAG_MCU                },
	{ 0x4004 ,N_FLD(dbg_DEC_DE_INTR_FLAG_CPU)                ,"DEC_DE_INTR_FLAG_CPU"                  ,dbg_DEC_DE_INTR_FLAG_CPU                },
	{ 0x4008 ,N_FLD(dbg_DEE_CVI_MUX_SEL)                     ,"DEE_CVI_MUX_SEL"                       ,dbg_DEE_CVI_MUX_SEL                     },
	{ 0x400c ,N_FLD(dbg_DEE_PE0_HIF_OFFSET)                  ,"DEE_PE0_HIF_OFFSET"                    ,dbg_DEE_PE0_HIF_OFFSET                  },
	{ 0x4010 ,N_FLD(dbg_DEE_SM_HIF_OFFSET)                   ,"DEE_SM_HIF_OFFSET"                     ,dbg_DEE_SM_HIF_OFFSET                   },
	{ 0x4014 ,N_FLD(dbg_DEE_PE1_HIF_OFFSET)                  ,"DEE_PE1_HIF_OFFSET"                    ,dbg_DEE_PE1_HIF_OFFSET                  },
	{ 0x4018 ,N_FLD(dbg_DEE_CVD_ADDR_SW_DE_SAV)              ,"DEE_CVD_ADDR_SW_DE_SAV"                ,dbg_DEE_CVD_ADDR_SW_DE_SAV              },
	{ 0x401c ,N_FLD(dbg_DEE_CVD_ADDR_SW_CPU_GPU)             ,"DEE_CVD_ADDR_SW_CPU_GPU"               ,dbg_DEE_CVD_ADDR_SW_CPU_GPU             },
	{ 0x4020 ,N_FLD(dbg_DEE_CVD_ADDR_SW_CPU_SHADOW)          ,"DEE_CVD_ADDR_SW_CPU_SHADOW"            ,dbg_DEE_CVD_ADDR_SW_CPU_SHADOW          },
	{ 0x4024 ,N_FLD(dbg_DEE_MCU_ADDR_SW_DE_SAV)              ,"DEE_MCU_ADDR_SW_DE_SAV"                ,dbg_DEE_MCU_ADDR_SW_DE_SAV              },
	{ 0x4028 ,N_FLD(dbg_DEE_MCU_ADDR_SW_CPU_GPU)             ,"DEE_MCU_ADDR_SW_CPU_GPU"               ,dbg_DEE_MCU_ADDR_SW_CPU_GPU             },
	{ 0x402c ,N_FLD(dbg_DEE_MCU_ADDR_SW_CPU_SHADOW)          ,"DEE_MCU_ADDR_SW_CPU_SHADOW"            ,dbg_DEE_MCU_ADDR_SW_CPU_SHADOW          },
	{ 0x4030 ,N_FLD(dbg_DEE_MCU_ADDR_WINDOW)                 ,"DEE_MCU_ADDR_WINDOW"                   ,dbg_DEE_MCU_ADDR_WINDOW                 },
	{ 0x4034 ,N_FLD(dbg_DEE_INTR_REG)                        ,"DEE_INTR_REG"                          ,dbg_DEE_INTR_REG                        },
	{ 0x4038 ,N_FLD(dbg_DEE_INTR_MASK)                       ,"DEE_INTR_MASK"                         ,dbg_DEE_INTR_MASK                       },
	{ 0x403c ,N_FLD(dbg_DEE_GMAU_FLUSH)                      ,"DEE_GMAU_FLUSH"                        ,dbg_DEE_GMAU_FLUSH                      },
	{ 0x40fc ,N_FLD(dbg_DEE_MG_LS_CTRL)                      ,"DEE_MG_LS_CTRL"                        ,dbg_DEE_MG_LS_CTRL                      },
	{ 0x5000 ,N_FLD(dbg_DEF_PIC_INIT)                        ,"DEF_PIC_INIT"                          ,dbg_DEF_PIC_INIT                        },
	{ 0x5004 ,N_FLD(dbg_DEF_PIC_START)                       ,"DEF_PIC_START"                         ,dbg_DEF_PIC_START                       },
	{ 0x5008 ,N_FLD(dbg_DEF_DE_VENC_IF)                      ,"DEF_DE_VENC_IF"                        ,dbg_DEF_DE_VENC_IF                      },
	{ 0x500c ,N_FLD(dbg_DEF_DPATH_CTRL)                      ,"DEF_DPATH_CTRL"                        ,dbg_DEF_DPATH_CTRL                      },
	{ 0x5010 ,N_FLD(dbg_DEF_CVE_PARAM0)                      ,"DEF_CVE_PARAM0"                        ,dbg_DEF_CVE_PARAM0                      },
	{ 0x5014 ,N_FLD(dbg_DEF_CVE_PARAM1)                      ,"DEF_CVE_PARAM1"                        ,dbg_DEF_CVE_PARAM1                      },
	{ 0x5018 ,N_FLD(dbg_DEF_CVE_PARAM2)                      ,"DEF_CVE_PARAM2"                        ,dbg_DEF_CVE_PARAM2                      },
	{ 0x501c ,N_FLD(dbg_DEF_CVE_PARAM3)                      ,"DEF_CVE_PARAM3"                        ,dbg_DEF_CVE_PARAM3                      },
	{ 0x5020 ,N_FLD(dbg_DEF_CVE_PULSE_DLY)                   ,"DEF_CVE_PULSE_DLY"                     ,dbg_DEF_CVE_PULSE_DLY                   },
	{ 0x5024 ,N_FLD(dbg_DEF_GMAU_CTRL)                       ,"DEF_GMAU_CTRL"                         ,dbg_DEF_GMAU_CTRL                       },
	{ 0x5028 ,N_FLD(dbg_DEF_PIC_END_EN)                      ,"DEF_PIC_END_EN"                        ,dbg_DEF_PIC_END_EN                      },
	{ 0x5034 ,N_FLD(dbg_DEF_PIC_INIT_G2_TIMER)               ,"DEF_PIC_INIT_G2_TIMER"                 ,dbg_DEF_PIC_INIT_G2_TIMER               },
	{ 0x5038 ,N_FLD(dbg_DEF_PIC_INIT_G3_TIMER)               ,"DEF_PIC_INIT_G3_TIMER"                 ,dbg_DEF_PIC_INIT_G3_TIMER               },
	{ 0x503c ,N_FLD(dbg_DEF_PIC_END_INFO)                    ,"DEF_PIC_END_INFO"                      ,dbg_DEF_PIC_END_INFO                    },
	{ 0x5040 ,N_FLD(dbg_DEF_INTR_REG)                        ,"DEF_INTR_REG"                          ,dbg_DEF_INTR_REG                        },
	{ 0x5044 ,N_FLD(dbg_DEF_INTR_MASK)                       ,"DEF_INTR_MASK"                         ,dbg_DEF_INTR_MASK                       },
	{ 0x5048 ,N_FLD(dbg_DEF_INTR_MUX)                        ,"DEF_INTR_MUX"                          ,dbg_DEF_INTR_MUX                        },
	{ 0x504c ,0                                              ,"DEF_CVE_INTR_TIME_STP"                 ,NULL                                    },
	{ 0x5050 ,N_FLD(dbg_DEF_ADDR_SW_DE_SAV)                  ,"DEF_ADDR_SW_DE_SAV"                    ,dbg_DEF_ADDR_SW_DE_SAV                  },
	{ 0x5054 ,N_FLD(dbg_DEF_ADDR_SW_CPU_GPU)                 ,"DEF_ADDR_SW_CPU_GPU"                   ,dbg_DEF_ADDR_SW_CPU_GPU                 },
	{ 0x5058 ,N_FLD(dbg_DEF_ADDR_SW_CPU_SHADOW)              ,"DEF_ADDR_SW_CPU_SHADOW"                ,dbg_DEF_ADDR_SW_CPU_SHADOW              },
	{ 0x50f8 ,N_FLD(dbg_DEF_GMAU_FLUSH)                      ,"DEF_GMAU_FLUSH"                        ,dbg_DEF_GMAU_FLUSH                      },
	{ 0x50fc ,N_FLD(dbg_DEF_MG_LS_CTRL)                      ,"DEF_MG_LS_CTRL"                        ,dbg_DEF_MG_LS_CTRL                      },
	{ 0 , } // end marker
};

#endif
