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

/*--------------------------------------------
	0x0000 DEA_CHA_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_CHA_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"cha_hsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"cha_csample"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"cha_aspect"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"cha_vsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"cha_frame_lr"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"cha_field_id"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"cha_pr_sq"               },
};

/*--------------------------------------------
	0x0004 DEA_CHB_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_CHB_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"chb_hsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"chb_csample"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"chb_aspect"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"chb_vsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"chb_frame_lr"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"chb_field_id"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"chb_pr_sq"               },
};

/*--------------------------------------------
	0x0008 DEA_PIC_INIT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"             },
};

/*--------------------------------------------
	0x000c DEA_PIC_START
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"            },
};

/*--------------------------------------------
	0x0010 DEA_SMUX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SMUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"o_c_fmt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"i_c_fmt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec3d_mux_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"prew_mux_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"d3_lr_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"cvi_mux_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"nline_inc"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"wr_disalbe"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fieldid"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pr_sq"                   },
};

/*--------------------------------------------
	0x0014 DEA_SMUX_SIZE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SMUX_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsize"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"vsize"                   },
};

/*--------------------------------------------
	0x0018 DEA_MVI_V_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MVI_V_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_vsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_vblank"              },
};

/*--------------------------------------------
	0x001c DEA_MVI_H_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MVI_H_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_hsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_hblank"              },
};

/*--------------------------------------------
	0x0020 DEA_MVI_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MVI_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"mvi_i_c_fmt"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mvi_field"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"mvi_pr_sq"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mvi_cvi_stride"          },
};

/*--------------------------------------------
	0x0024 DEA_MSRC_SYNC_MUX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MSRC_SYNC_MUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"trans_mask_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cvi_select"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"mvi_select"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mvi_cvi_select"          },
};

/*--------------------------------------------
	0x0028 DEA_MSRC_SYNC_DLY
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MSRC_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"msrc_sync_dly"           },
};

/*--------------------------------------------
	0x002c DEA_MEM_SYNC_PERIOD
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_MEM_SYNC_PERIOD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"mem_sync_period"         },
};

/*--------------------------------------------
	0x0030 DEA_DCO_MFC
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_MFC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dco_mfc"                 },
};

/*--------------------------------------------
	0x0034 DEA_DCO_DFC
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_DFC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dco_dfc"                 },
};

/*--------------------------------------------
	0x0038 DEA_DCO_DFLC
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_DFLC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"dco_dflc"                },
};

/*--------------------------------------------
	0x003c DEA_DCO_FCW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_DCO_FCW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"dco_fcw"                 },
};

/*--------------------------------------------
	0x0040 DEA_SMUX_RO_LCNT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SMUX_RO_LCNT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"smux_ro_lcnt"            },
};

/*--------------------------------------------
	0x0044 DEA_GMAU_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"              },
};

/*--------------------------------------------
	0x0048 DEA_PIC_END_EN
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ipc_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"clc_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"tnr_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pe0_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"prew_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"smux_en"                 },
};

/*--------------------------------------------
	0x004c DEA_PIC_INIT_G0_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g0_timer"       },
};

/*--------------------------------------------
	0x0050 DEA_PIC_INIT_G1_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer"       },
};

/*--------------------------------------------
	0x0054 DEA_PIC_END_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"pic_end_g0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,5  ,"pic_end_g1"              },
};

/*--------------------------------------------
	0x0058 DEA_INTR_REG
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"cha_input_intr"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"chb_input_intr"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cha_field_intr"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cha_frame_lr_intr"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"chb_field_intr"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"chb_frame_lr_intr"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pe0_intr"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"smux_ow_intr"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_rd_done"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gmau_flush_wr_done"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"src_intr"                },
};

/*--------------------------------------------
	0x005c DEA_INTR_MASK
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dea_intr_mask"           },
};

/*--------------------------------------------
	0x0060 DEA_INTR_MUX
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_INTR_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"dea_intr_mux"            },
};

/*--------------------------------------------
	0x0064 DEA_SRC_INTR_TIME_STP
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_SRC_INTR_TIME_STP[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"src_intr_time_stp"       },
};

/*--------------------------------------------
	0x0068 DE_GPIO_MUX
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DE_GPIO_MUX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"de_gpio_mux"             },
};

/*--------------------------------------------
	0x006c DEA_ADDR_SW_DE_SAV
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dea_addr_sav_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"dea_addr_default_bus"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dea_addr_de_bus"         },
};

/*--------------------------------------------
	0x0070 DEA_ADDR_SW_CPU_GPU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dea_addr_gpu_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dea_addr_gpu_logic"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"dea_addr_cpu_h_bus"      },
};

/*--------------------------------------------
	0x0074 DEA_ADDR_SW_CPU_SHADOW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dea_addr_shadow_bus"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dea_addr_shadow_logic"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dea_addr_cpu_l_bus"      },
};

/*--------------------------------------------
	0x0078 DEA_GMAU_FLUSH
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEA_GMAU_FLUSH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gmau_flush_rd_en"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gmau_flush_wr_en"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gmau_flush_rd_done"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gmau_flush_wr_done"      },
};

/*--------------------------------------------
	0x007c DE_VERSION
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DE_VERSION[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"de_version"              },
};

/*--------------------------------------------
	0x1000 DEB_PIC_INIT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"ov_auto_init"            },
};

/*--------------------------------------------
	0x1004 DEB_PIC_START
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"            },
};

/*--------------------------------------------
	0x1008 DEB_DISP_V_PORCH
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_V_PORCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"vsync_bp"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"vsync_fp"                },
};

/*--------------------------------------------
	0x100c DEB_DISP_VS_VA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_VS_VA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"disp_sync_va"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"vsync"                   },
};

/*--------------------------------------------
	0x1010 DEB_DISP_H_PORCH
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_H_PORCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hsync_bp"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"hsync_fp"                },
};

/*--------------------------------------------
	0x1014 DEB_DISP_HS_HA
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_HS_HA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"disp_sync_ha"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"hsync"                   },
};

/*--------------------------------------------
	0x1018 DEB_DISP_SYNC_DLY
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hoffset1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"voffset1"                },
};

/*--------------------------------------------
	0x101c DEB_DISP_PULSE_DLY
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1020 DEB_DISP_SYNC_PARAMS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DISP_SYNC_PARAMS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"hoffset0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"disp_frame_lr"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"force_update"            },
};

/*--------------------------------------------
	0x1024 DEB_PWM_R0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_R0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm0_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm0_r_v"                },
};

/*--------------------------------------------
	0x1028 DEB_PWM_F0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_F0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm0_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm0_f_v"                },
};

/*--------------------------------------------
	0x102c DEB_PWM_R1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_R1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm1_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm1_r_v"                },
};

/*--------------------------------------------
	0x1030 DEB_PWM_F1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_F1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm1_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm1_f_v"                },
};

/*--------------------------------------------
	0x1034 DEB_PWM_R2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_R2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm2_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm2_r_v"                },
};

/*--------------------------------------------
	0x1038 DEB_PWM_F2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_F2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm2_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm2_f_v"                },
};

/*--------------------------------------------
	0x103c DEB_PWM_R3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_R3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm3_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm3_r_v"                },
};

/*--------------------------------------------
	0x1040 DEB_PWM_F3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_F3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm3_f_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm3_f_v"                },
};

/*--------------------------------------------
	0x1044 DEB_PWM_R4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_R4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm4_r_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm4_r_v"                },
};

/*--------------------------------------------
	0x1048 DEB_PWM_F4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_F4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm4_f_h"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"pwm4_f_v"                },
};

/*--------------------------------------------
	0x104c DEB_PWM_SUB_R0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_SUB_R0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm0_sub_r_v"            },
};

/*--------------------------------------------
	0x1050 DEB_PWM_SUB_R1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_SUB_R1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm1_sub_r_v"            },
};

/*--------------------------------------------
	0x1054 DEB_PWM_SUB_R2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_SUB_R2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm2_sub_r_v"            },
};

/*--------------------------------------------
	0x1058 DEB_PWM_SUB_R3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_SUB_R3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm3_sub_r_v"            },
};

/*--------------------------------------------
	0x105c DEB_PWM_SUB_R4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_SUB_R4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"pwm4_sub_r_v"            },
};

/*--------------------------------------------
	0x1060 DEB_PWM_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"pwm_inv"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,5  ,"pwm_fc_l"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,10 ,"pwm_fc_h"                },
};

/*--------------------------------------------
	0x1064 DEB_PWM_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PWM_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"pwm_sel"                 },
};

/*--------------------------------------------
	0x1068 DEB_DPATH_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_DPATH_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"t3_mux_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fb_mux_sel"              },
};

/*--------------------------------------------
	0x106c DEB_GMAU_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"              },
};

/*--------------------------------------------
	0x1070 DEB_PIC_END_EN
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ov_ss_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ov_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"sm_en"                   },
};

/*--------------------------------------------
	0x1074 DEB_PIC_INIT_G0_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g0_timer"       },
};

/*--------------------------------------------
	0x1078 DEB_PIC_INIT_G1_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer"       },
};

/*--------------------------------------------
	0x107c DEB_PIC_END_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"pic_end_g0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,4  ,"pic_end_g1"              },
};

/*--------------------------------------------
	0x1080 DEB_INTR_REG
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"intr_end_g0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"disp_intr_for_cpu"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"intr_end_g1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"disp_intr_for_mcu"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"ov_underflow"            },
};

/*--------------------------------------------
	0x1084 DEB_INTR_MASK
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1088 DEB_INTR_MUX
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x108c DEB_DISP_INTR_TIME_STP
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1090 DEB_ADDR_SW_DE_SAV
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"deb_addr_sav_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"deb_addr_default_bus"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"deb_addr_de_bus"         },
};

/*--------------------------------------------
	0x1094 DEB_ADDR_SW_CPU_GPU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"deb_addr_gpu_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"deb_addr_gpu_logic"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"deb_addr_cpu_h_bus"      },
};

/*--------------------------------------------
	0x1098 DEB_ADDR_SW_CPU_SHADOW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEB_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"deb_addr_shadow_bus"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"deb_addr_shadow_logic"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"deb_addr_cpu_l_bus"      },
};

/*--------------------------------------------
	0x2000 DEC_PIC_INIT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_init_g2"             },
};

/*--------------------------------------------
	0x2004 DEC_PIC_START
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_start_g2"            },
};

/*--------------------------------------------
	0x2008 DEC_SMUX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SMUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"o_c_fmt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"i_c_fmt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec3d_mux_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"prew_mux_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"d3_lr_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"cvi_mux_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"nline_inc"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"wr_disalbe"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"fieldid"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pr_sq"                   },
};

/*--------------------------------------------
	0x200c DEC_SMUX_SIZE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SMUX_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"hsize"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"vsize"                   },
};

/*--------------------------------------------
	0x2010 DEC_MVI_V_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MVI_V_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_vsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_vblank"              },
};

/*--------------------------------------------
	0x2014 DEC_MVI_H_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MVI_H_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mvi_hsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"mvi_hblank"              },
};

/*--------------------------------------------
	0x2018 DEC_MVI_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MVI_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"mvi_i_c_fmt"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mvi_field"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"mvi_pr_sq"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"mvi_cvi_stride"          },
};

/*--------------------------------------------
	0x201c DEC_MSRC_SYNC_MUX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MSRC_SYNC_MUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"m_trans_mask_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"m_cvi_select"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"m_mvi_select"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"m_mvi_cvi_select"        },
};

/*--------------------------------------------
	0x2020 DEC_MSRC_SYNC_DLY
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MSRC_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"msrc_sync_dly"           },
};

/*--------------------------------------------
	0x2024 DEC_MEM0_SYNC_PERIOD
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MEM0_SYNC_PERIOD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"mem0_sync_period"        },
};

/*--------------------------------------------
	0x2028 DEC_MEM1_SYNC_PERIOD
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MEM1_SYNC_PERIOD[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"mem1_sync_period"        },
};

/*--------------------------------------------
	0x202c DEC_SSMUX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SSMUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"sub_o_c_fmt"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"sub_i_c_fmt"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"sub_src_mux_sel"         },
};

/*--------------------------------------------
	0x2030 DEC_SSRC_SYNC_MUX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SSRC_SYNC_MUX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"s_trans_mask_en"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"s_cvi_select"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"s_mvi_select"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"s_mvi_cvi_select"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"s_disp_select"           },
};

/*--------------------------------------------
	0x2034 DEC_SSRC_SYNC_DLY
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SSRC_SYNC_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"ssrc_sync_dly"           },
};

/*--------------------------------------------
	0x2038 DEC_MD_CSC_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load_md_csc_coef"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"md_csc_en"               },
};

/*--------------------------------------------
	0x203c DEC_MD_CSC_COEF0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef0"            },
};

/*--------------------------------------------
	0x2040 DEC_MD_CSC_COEF1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef3"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef2"            },
};

/*--------------------------------------------
	0x2044 DEC_MD_CSC_COEF2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef5"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef4"            },
};

/*--------------------------------------------
	0x2048 DEC_MD_CSC_COEF3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"md_csc_coef7"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"md_csc_coef6"            },
};

/*--------------------------------------------
	0x204c DEC_MD_CSC_COEF4
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_COEF4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"dec_md_csc_coef4"        },
};

/*--------------------------------------------
	0x2050 DEC_MD_CSC_OFFSET0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_OFFSET0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"md_csc_ofst1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"md_csc_ofst0"            },
};

/*--------------------------------------------
	0x2054 DEC_MD_CSC_OFFSET1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_OFFSET1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"md_csc_ofst3"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"md_csc_ofst2"            },
};

/*--------------------------------------------
	0x2058 DEC_MD_CSC_OFFSET2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_MD_CSC_OFFSET2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"md_csc_ofst5"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"md_csc_ofst4"            },
};

/*--------------------------------------------
	0x205c DEC_SMUX_RO_LCNT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_SMUX_RO_LCNT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"smux_ro_lcnt"            },
};

/*--------------------------------------------
	0x2060 DEC_GMAU_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"              },
};

/*--------------------------------------------
	0x2064 DEC_PIC_END_EN
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ipc_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tnr_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pe0_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"prew_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"smux_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"mvi_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"ss_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"ssm_en"                  },
};

/*--------------------------------------------
	0x2068 DEC_PIC_INIT_G0_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g0_timer"       },
};

/*--------------------------------------------
	0x206c DEC_PIC_INIT_G1_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer"       },
};

/*--------------------------------------------
	0x2070 DEC_PIC_INIT_G2_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_INIT_G2_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g2_timer"       },
};

/*--------------------------------------------
	0x2074 DEC_PIC_END_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"pic_end_g0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,5  ,"pic_end_g1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"pic_end_g2"              },
};

/*--------------------------------------------
	0x2078 DEC_INTR_REG
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_end_g2"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pe0_intr"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"smux_ow_intr"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"ssrc_intr"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"msrc_intr"               },
};

/*--------------------------------------------
	0x207c DEC_INTR_MASK
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x2080 DEC_INTR_MUX
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x2084 DEC_MSRC_INTR_TIME_STP
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x2088 DEC_SSRC_INTR_TIME_STP
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x208c DEC_ADDR_SW_DE_SAV
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dec_addr_sav_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"dec_addr_default_bus"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dec_addr_de_bus"         },
};

/*--------------------------------------------
	0x2090 DEC_ADDR_SW_CPU_GPU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dec_addr_gpu_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dec_addr_gpu_logic"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"dec_addr_cpu_h_bus"      },
};

/*--------------------------------------------
	0x2094 DEC_ADDR_SW_CPU_SHADOW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"dec_addr_shadow_bus"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"dec_addr_shadow_logic"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"dec_addr_cpu_l_bus"      },
};

/*--------------------------------------------
	0x3000 DED_PIC_INIT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_init_g0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_init_g1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_inti_g2"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_init_g3"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"osd_auto_init"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"atop_auto_init"          },
};

/*--------------------------------------------
	0x3004 DED_PIC_START
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_START[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_start_g0"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_start_g1"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_start_g2"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_start_g3"            },
};

/*--------------------------------------------
	0x3008 DED_DE_VENC_IF
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DE_VENC_IF[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"venc_vsync"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"venc_sel"                },
};

/*--------------------------------------------
	0x300c DED_DPATH_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_DPATH_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"t3_mux_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fb_mux_sel"              },
};

/*--------------------------------------------
	0x3010 DED_CVE_PARAM0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_CVE_PARAM0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"vertical_back_period"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"vertical_sync_period"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"vertical_front_period"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"vsync_polarity"          },
};

/*--------------------------------------------
	0x3014 DED_CVE_PARAM1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_CVE_PARAM1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"horizontal_back_period"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"horizontal_sync_period"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"horizontal_front_period" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"hsync_polarity"          },
};

/*--------------------------------------------
	0x3018 DED_CVE_PARAM2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_CVE_PARAM2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"v_hoffset1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,11 ,"v_hoffset0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"field_id_polarity"       },
};

/*--------------------------------------------
	0x301c DED_CVE_PARAM3
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_CVE_PARAM3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"cve_sync_ha"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"cve_sync_va"             },
};

/*--------------------------------------------
	0x3020 DED_CVE_PULSE_DLY
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_CVE_PULSE_DLY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"cve_pulse_dly"           },
};

/*--------------------------------------------
	0x3024 DED_GMAU_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_GMAU_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"ask_cmd_dly_cnt"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,16 ,"ask_to_cnt"              },
};

/*--------------------------------------------
	0x3028 DED_PIC_END_EN
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_END_EN[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"atop_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"ov_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"sm_en"                   },
};

/*--------------------------------------------
	0x302c DED_PIC_INIT_G0_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT_G0_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g0_timer"       },
};

/*--------------------------------------------
	0x3030 DED_PIC_INIT_G1_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT_G1_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g1_timer"       },
};

/*--------------------------------------------
	0x3034 DED_PIC_INIT_G2_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT_G2_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g2_timer"       },
};

/*--------------------------------------------
	0x3038 DED_PIC_INIT_G3_TIMER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_INIT_G3_TIMER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,0  ,"pic_init_g3_timer"       },
};

/*--------------------------------------------
	0x303c DED_PIC_END_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_PIC_END_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"pic_end_g0_info"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"pic_end_g1_info"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"pic_end_g2_info"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"pic_end_g3_info"         },
};

/*--------------------------------------------
	0x3040 DED_INTR_REG
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"pic_end_g0"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"pic_end_g1"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"pic_end_g2"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pic_end_g3"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ov_underflow"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"cve_pulse"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"cve_va_pulse"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"src_pulse"               },
};

/*--------------------------------------------
	0x3044 DED_INTR_MASK
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3048 DED_INTR_MUX
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x304c DED_CVE_INTR_TIME_STP
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3050 DED_ADDR_SW_DE_SAV
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"ded_addr_sav_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"ded_addr_default_bus"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"ded_addr_de_bus"         },
};

/*--------------------------------------------
	0x3054 DED_ADDR_SW_CPU_GPU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"ded_addr_gpu_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"ded_addr_gpu_logic"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"ded_addr_cpu_h_bus"      },
};

/*--------------------------------------------
	0x3058 DED_ADDR_SW_CPU_SHADOW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DED_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"ded_addr_shadow_bus"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"ded_addr_shadow_logic"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"ded_addr_cpu_l_bus"      },
};

/*--------------------------------------------
	0x4000 DEC_DE_INTR_FLAG_MCU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DE_INTR_FLAG_MCU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dea_dec_intr_mcu"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"deb_dec_intr_mcu"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec_dec_intr_mcu"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ded_dec_intr_mcu"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"dee_dec_intr_mcu"        },
};

/*--------------------------------------------
	0x4004 DEC_DE_INTR_FLAG_CPU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEC_DE_INTR_FLAG_CPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dea_dec_intr_cpu"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"deb_dec_intr_cpu"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"dec_dec_intr_cpu"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"ded_dec_intr_cpu"        },
};

/*--------------------------------------------
	0x4008 DEE_CVI_MUX_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVI_MUX_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cvi_mux_sel"             },
};

/*--------------------------------------------
	0x400c DEE_PE0_HIF_OFFSET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_PE0_HIF_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pe0_hif_offset_en"       },
};

/*--------------------------------------------
	0x4010 DEE_SM_HIF_OFFSET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_SM_HIF_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"sm_hif_offset_en"        },
};

/*--------------------------------------------
	0x4014 DEE_PE1_HIF_OFFSET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_PE1_HIF_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"pe1_hif_offset_en"       },
};

/*--------------------------------------------
	0x4018 DEE_CVD_ADDR_SW_DE_SAV
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVD_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"cvd_addr_sav_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"mcu_addr_default_bus"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"cvd_addr_de_bus"         },
};

/*--------------------------------------------
	0x401c DEE_CVD_ADDR_SW_CPU_GPU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVD_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"cvd_addr_gpu_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"cvd_addr_gpu_logic"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cvd_addr_cpu_h_bus"      },
};

/*--------------------------------------------
	0x4020 DEE_CVD_ADDR_SW_CPU_SHADOW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_CVD_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"cvd_addr_shadow_bus"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"cvd_addr_shadow_logic"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"cvd_addr_cpu_l_bus"      },
};

/*--------------------------------------------
	0x4024 DEE_MCU_ADDR_SW_DE_SAV
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_SW_DE_SAV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"mcu_addr_sav_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"mcu_addr_default_bus"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"mcu_addr_de_bus"         },
};

/*--------------------------------------------
	0x4028 DEE_MCU_ADDR_SW_CPU_GPU
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_SW_CPU_GPU[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"mcu_addr_gpu_bus"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"mcu_addr_gpu_logic"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"mcu_addr_cpu_h_bus"      },
};

/*--------------------------------------------
	0x402c DEE_MCU_ADDR_SW_CPU_SHADOW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_SW_CPU_SHADOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,3  ,"mcu_addr_shadow_bus"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,15 ,"mcu_addr_shadow_logic"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,24 ,"mcu_addr_cpu_l_bus"      },
};

/*--------------------------------------------
	0x4030 DEE_MCU_ADDR_WINDOW
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_MCU_ADDR_WINDOW[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"mcu_win_lower"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"mcu_win_upper"           },
};

/*--------------------------------------------
	0x4034 DEE_INTR_REG
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_INTR_REG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dee_src_cvd"             },
};

/*--------------------------------------------
	0x4038 DEE_INTR_MASK
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_DEE_INTR_MASK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dee_cvd_intr_mask"       },
};

DBG_REG_T gDbgRegCTR[] = {
	{ 0x0000 ,N_FLD(dbg_DEA_CHA_INFO)                    ,"DEA_CHA_INFO"                      ,dbg_DEA_CHA_INFO                    },
	{ 0x0004 ,N_FLD(dbg_DEA_CHB_INFO)                    ,"DEA_CHB_INFO"                      ,dbg_DEA_CHB_INFO                    },
	{ 0x0008 ,N_FLD(dbg_DEA_PIC_INIT)                    ,"DEA_PIC_INIT"                      ,dbg_DEA_PIC_INIT                    },
	{ 0x000c ,N_FLD(dbg_DEA_PIC_START)                   ,"DEA_PIC_START"                     ,dbg_DEA_PIC_START                   },
	{ 0x0010 ,N_FLD(dbg_DEA_SMUX_CTRL)                   ,"DEA_SMUX_CTRL"                     ,dbg_DEA_SMUX_CTRL                   },
	{ 0x0014 ,N_FLD(dbg_DEA_SMUX_SIZE)                   ,"DEA_SMUX_SIZE"                     ,dbg_DEA_SMUX_SIZE                   },
	{ 0x0018 ,N_FLD(dbg_DEA_MVI_V_INFO)                  ,"DEA_MVI_V_INFO"                    ,dbg_DEA_MVI_V_INFO                  },
	{ 0x001c ,N_FLD(dbg_DEA_MVI_H_INFO)                  ,"DEA_MVI_H_INFO"                    ,dbg_DEA_MVI_H_INFO                  },
	{ 0x0020 ,N_FLD(dbg_DEA_MVI_CTRL)                    ,"DEA_MVI_CTRL"                      ,dbg_DEA_MVI_CTRL                    },
	{ 0x0024 ,N_FLD(dbg_DEA_MSRC_SYNC_MUX_CTRL)          ,"DEA_MSRC_SYNC_MUX_CTRL"            ,dbg_DEA_MSRC_SYNC_MUX_CTRL          },
	{ 0x0028 ,N_FLD(dbg_DEA_MSRC_SYNC_DLY)               ,"DEA_MSRC_SYNC_DLY"                 ,dbg_DEA_MSRC_SYNC_DLY               },
	{ 0x002c ,N_FLD(dbg_DEA_MEM_SYNC_PERIOD)             ,"DEA_MEM_SYNC_PERIOD"               ,dbg_DEA_MEM_SYNC_PERIOD             },
	{ 0x0030 ,N_FLD(dbg_DEA_DCO_MFC)                     ,"DEA_DCO_MFC"                       ,dbg_DEA_DCO_MFC                     },
	{ 0x0034 ,N_FLD(dbg_DEA_DCO_DFC)                     ,"DEA_DCO_DFC"                       ,dbg_DEA_DCO_DFC                     },
	{ 0x0038 ,N_FLD(dbg_DEA_DCO_DFLC)                    ,"DEA_DCO_DFLC"                      ,dbg_DEA_DCO_DFLC                    },
	{ 0x003c ,N_FLD(dbg_DEA_DCO_FCW)                     ,"DEA_DCO_FCW"                       ,dbg_DEA_DCO_FCW                     },
	{ 0x0040 ,N_FLD(dbg_DEA_SMUX_RO_LCNT)                ,"DEA_SMUX_RO_LCNT"                  ,dbg_DEA_SMUX_RO_LCNT                },
	{ 0x0044 ,N_FLD(dbg_DEA_GMAU_CTRL)                   ,"DEA_GMAU_CTRL"                     ,dbg_DEA_GMAU_CTRL                   },
	{ 0x0048 ,N_FLD(dbg_DEA_PIC_END_EN)                  ,"DEA_PIC_END_EN"                    ,dbg_DEA_PIC_END_EN                  },
	{ 0x004c ,N_FLD(dbg_DEA_PIC_INIT_G0_TIMER)           ,"DEA_PIC_INIT_G0_TIMER"             ,dbg_DEA_PIC_INIT_G0_TIMER           },
	{ 0x0050 ,N_FLD(dbg_DEA_PIC_INIT_G1_TIMER)           ,"DEA_PIC_INIT_G1_TIMER"             ,dbg_DEA_PIC_INIT_G1_TIMER           },
	{ 0x0054 ,N_FLD(dbg_DEA_PIC_END_INFO)                ,"DEA_PIC_END_INFO"                  ,dbg_DEA_PIC_END_INFO                },
	{ 0x0058 ,N_FLD(dbg_DEA_INTR_REG)                    ,"DEA_INTR_REG"                      ,dbg_DEA_INTR_REG                    },
	{ 0x005c ,N_FLD(dbg_DEA_INTR_MASK)                   ,"DEA_INTR_MASK"                     ,dbg_DEA_INTR_MASK                   },
	{ 0x0060 ,N_FLD(dbg_DEA_INTR_MUX)                    ,"DEA_INTR_MUX"                      ,dbg_DEA_INTR_MUX                    },
	{ 0x0064 ,N_FLD(dbg_DEA_SRC_INTR_TIME_STP)           ,"DEA_SRC_INTR_TIME_STP"             ,dbg_DEA_SRC_INTR_TIME_STP           },
	{ 0x0068 ,N_FLD(dbg_DE_GPIO_MUX)                     ,"DE_GPIO_MUX"                       ,dbg_DE_GPIO_MUX                     },
	{ 0x006c ,N_FLD(dbg_DEA_ADDR_SW_DE_SAV)              ,"DEA_ADDR_SW_DE_SAV"                ,dbg_DEA_ADDR_SW_DE_SAV              },
	{ 0x0070 ,N_FLD(dbg_DEA_ADDR_SW_CPU_GPU)             ,"DEA_ADDR_SW_CPU_GPU"               ,dbg_DEA_ADDR_SW_CPU_GPU             },
	{ 0x0074 ,N_FLD(dbg_DEA_ADDR_SW_CPU_SHADOW)          ,"DEA_ADDR_SW_CPU_SHADOW"            ,dbg_DEA_ADDR_SW_CPU_SHADOW          },
	{ 0x0078 ,N_FLD(dbg_DEA_GMAU_FLUSH)                  ,"DEA_GMAU_FLUSH"                    ,dbg_DEA_GMAU_FLUSH                  },
	{ 0x007c ,N_FLD(dbg_DE_VERSION)                      ,"DE_VERSION"                        ,dbg_DE_VERSION                      },
	{ 0x1000 ,N_FLD(dbg_DEB_PIC_INIT)                    ,"DEB_PIC_INIT"                      ,dbg_DEB_PIC_INIT                    },
	{ 0x1004 ,N_FLD(dbg_DEB_PIC_START)                   ,"DEB_PIC_START"                     ,dbg_DEB_PIC_START                   },
	{ 0x1008 ,N_FLD(dbg_DEB_DISP_V_PORCH)                ,"DEB_DISP_V_PORCH"                  ,dbg_DEB_DISP_V_PORCH                },
	{ 0x100c ,N_FLD(dbg_DEB_DISP_VS_VA)                  ,"DEB_DISP_VS_VA"                    ,dbg_DEB_DISP_VS_VA                  },
	{ 0x1010 ,N_FLD(dbg_DEB_DISP_H_PORCH)                ,"DEB_DISP_H_PORCH"                  ,dbg_DEB_DISP_H_PORCH                },
	{ 0x1014 ,N_FLD(dbg_DEB_DISP_HS_HA)                  ,"DEB_DISP_HS_HA"                    ,dbg_DEB_DISP_HS_HA                  },
	{ 0x1018 ,N_FLD(dbg_DEB_DISP_SYNC_DLY)               ,"DEB_DISP_SYNC_DLY"                 ,dbg_DEB_DISP_SYNC_DLY               },
	{ 0x101c ,0                                          ,"DEB_DISP_PULSE_DLY"                ,NULL                                },
	{ 0x1020 ,N_FLD(dbg_DEB_DISP_SYNC_PARAMS)            ,"DEB_DISP_SYNC_PARAMS"              ,dbg_DEB_DISP_SYNC_PARAMS            },
	{ 0x1024 ,N_FLD(dbg_DEB_PWM_R0)                      ,"DEB_PWM_R0"                        ,dbg_DEB_PWM_R0                      },
	{ 0x1028 ,N_FLD(dbg_DEB_PWM_F0)                      ,"DEB_PWM_F0"                        ,dbg_DEB_PWM_F0                      },
	{ 0x102c ,N_FLD(dbg_DEB_PWM_R1)                      ,"DEB_PWM_R1"                        ,dbg_DEB_PWM_R1                      },
	{ 0x1030 ,N_FLD(dbg_DEB_PWM_F1)                      ,"DEB_PWM_F1"                        ,dbg_DEB_PWM_F1                      },
	{ 0x1034 ,N_FLD(dbg_DEB_PWM_R2)                      ,"DEB_PWM_R2"                        ,dbg_DEB_PWM_R2                      },
	{ 0x1038 ,N_FLD(dbg_DEB_PWM_F2)                      ,"DEB_PWM_F2"                        ,dbg_DEB_PWM_F2                      },
	{ 0x103c ,N_FLD(dbg_DEB_PWM_R3)                      ,"DEB_PWM_R3"                        ,dbg_DEB_PWM_R3                      },
	{ 0x1040 ,N_FLD(dbg_DEB_PWM_F3)                      ,"DEB_PWM_F3"                        ,dbg_DEB_PWM_F3                      },
	{ 0x1044 ,N_FLD(dbg_DEB_PWM_R4)                      ,"DEB_PWM_R4"                        ,dbg_DEB_PWM_R4                      },
	{ 0x1048 ,N_FLD(dbg_DEB_PWM_F4)                      ,"DEB_PWM_F4"                        ,dbg_DEB_PWM_F4                      },
	{ 0x104c ,N_FLD(dbg_DEB_PWM_SUB_R0)                  ,"DEB_PWM_SUB_R0"                    ,dbg_DEB_PWM_SUB_R0                  },
	{ 0x1050 ,N_FLD(dbg_DEB_PWM_SUB_R1)                  ,"DEB_PWM_SUB_R1"                    ,dbg_DEB_PWM_SUB_R1                  },
	{ 0x1054 ,N_FLD(dbg_DEB_PWM_SUB_R2)                  ,"DEB_PWM_SUB_R2"                    ,dbg_DEB_PWM_SUB_R2                  },
	{ 0x1058 ,N_FLD(dbg_DEB_PWM_SUB_R3)                  ,"DEB_PWM_SUB_R3"                    ,dbg_DEB_PWM_SUB_R3                  },
	{ 0x105c ,N_FLD(dbg_DEB_PWM_SUB_R4)                  ,"DEB_PWM_SUB_R4"                    ,dbg_DEB_PWM_SUB_R4                  },
	{ 0x1060 ,N_FLD(dbg_DEB_PWM_CTRL)                    ,"DEB_PWM_CTRL"                      ,dbg_DEB_PWM_CTRL                    },
	{ 0x1064 ,N_FLD(dbg_DEB_PWM_SEL)                     ,"DEB_PWM_SEL"                       ,dbg_DEB_PWM_SEL                     },
	{ 0x1068 ,N_FLD(dbg_DEB_DPATH_CTRL)                  ,"DEB_DPATH_CTRL"                    ,dbg_DEB_DPATH_CTRL                  },
	{ 0x106c ,N_FLD(dbg_DEB_GMAU_CTRL)                   ,"DEB_GMAU_CTRL"                     ,dbg_DEB_GMAU_CTRL                   },
	{ 0x1070 ,N_FLD(dbg_DEB_PIC_END_EN)                  ,"DEB_PIC_END_EN"                    ,dbg_DEB_PIC_END_EN                  },
	{ 0x1074 ,N_FLD(dbg_DEB_PIC_INIT_G0_TIMER)           ,"DEB_PIC_INIT_G0_TIMER"             ,dbg_DEB_PIC_INIT_G0_TIMER           },
	{ 0x1078 ,N_FLD(dbg_DEB_PIC_INIT_G1_TIMER)           ,"DEB_PIC_INIT_G1_TIMER"             ,dbg_DEB_PIC_INIT_G1_TIMER           },
	{ 0x107c ,N_FLD(dbg_DEB_PIC_END_INFO)                ,"DEB_PIC_END_INFO"                  ,dbg_DEB_PIC_END_INFO                },
	{ 0x1080 ,N_FLD(dbg_DEB_INTR_REG)                    ,"DEB_INTR_REG"                      ,dbg_DEB_INTR_REG                    },
	{ 0x1084 ,0                                          ,"DEB_INTR_MASK"                     ,NULL                                },
	{ 0x1088 ,0                                          ,"DEB_INTR_MUX"                      ,NULL                                },
	{ 0x108c ,0                                          ,"DEB_DISP_INTR_TIME_STP"            ,NULL                                },
	{ 0x1090 ,N_FLD(dbg_DEB_ADDR_SW_DE_SAV)              ,"DEB_ADDR_SW_DE_SAV"                ,dbg_DEB_ADDR_SW_DE_SAV              },
	{ 0x1094 ,N_FLD(dbg_DEB_ADDR_SW_CPU_GPU)             ,"DEB_ADDR_SW_CPU_GPU"               ,dbg_DEB_ADDR_SW_CPU_GPU             },
	{ 0x1098 ,N_FLD(dbg_DEB_ADDR_SW_CPU_SHADOW)          ,"DEB_ADDR_SW_CPU_SHADOW"            ,dbg_DEB_ADDR_SW_CPU_SHADOW          },
	{ 0x2000 ,N_FLD(dbg_DEC_PIC_INIT)                    ,"DEC_PIC_INIT"                      ,dbg_DEC_PIC_INIT                    },
	{ 0x2004 ,N_FLD(dbg_DEC_PIC_START)                   ,"DEC_PIC_START"                     ,dbg_DEC_PIC_START                   },
	{ 0x2008 ,N_FLD(dbg_DEC_SMUX_CTRL)                   ,"DEC_SMUX_CTRL"                     ,dbg_DEC_SMUX_CTRL                   },
	{ 0x200c ,N_FLD(dbg_DEC_SMUX_SIZE)                   ,"DEC_SMUX_SIZE"                     ,dbg_DEC_SMUX_SIZE                   },
	{ 0x2010 ,N_FLD(dbg_DEC_MVI_V_INFO)                  ,"DEC_MVI_V_INFO"                    ,dbg_DEC_MVI_V_INFO                  },
	{ 0x2014 ,N_FLD(dbg_DEC_MVI_H_INFO)                  ,"DEC_MVI_H_INFO"                    ,dbg_DEC_MVI_H_INFO                  },
	{ 0x2018 ,N_FLD(dbg_DEC_MVI_CTRL)                    ,"DEC_MVI_CTRL"                      ,dbg_DEC_MVI_CTRL                    },
	{ 0x201c ,N_FLD(dbg_DEC_MSRC_SYNC_MUX_CTRL)          ,"DEC_MSRC_SYNC_MUX_CTRL"            ,dbg_DEC_MSRC_SYNC_MUX_CTRL          },
	{ 0x2020 ,N_FLD(dbg_DEC_MSRC_SYNC_DLY)               ,"DEC_MSRC_SYNC_DLY"                 ,dbg_DEC_MSRC_SYNC_DLY               },
	{ 0x2024 ,N_FLD(dbg_DEC_MEM0_SYNC_PERIOD)            ,"DEC_MEM0_SYNC_PERIOD"              ,dbg_DEC_MEM0_SYNC_PERIOD            },
	{ 0x2028 ,N_FLD(dbg_DEC_MEM1_SYNC_PERIOD)            ,"DEC_MEM1_SYNC_PERIOD"              ,dbg_DEC_MEM1_SYNC_PERIOD            },
	{ 0x202c ,N_FLD(dbg_DEC_SSMUX_CTRL)                  ,"DEC_SSMUX_CTRL"                    ,dbg_DEC_SSMUX_CTRL                  },
	{ 0x2030 ,N_FLD(dbg_DEC_SSRC_SYNC_MUX_CTRL)          ,"DEC_SSRC_SYNC_MUX_CTRL"            ,dbg_DEC_SSRC_SYNC_MUX_CTRL          },
	{ 0x2034 ,N_FLD(dbg_DEC_SSRC_SYNC_DLY)               ,"DEC_SSRC_SYNC_DLY"                 ,dbg_DEC_SSRC_SYNC_DLY               },
	{ 0x2038 ,N_FLD(dbg_DEC_MD_CSC_CTRL)                 ,"DEC_MD_CSC_CTRL"                   ,dbg_DEC_MD_CSC_CTRL                 },
	{ 0x203c ,N_FLD(dbg_DEC_MD_CSC_COEF0)                ,"DEC_MD_CSC_COEF0"                  ,dbg_DEC_MD_CSC_COEF0                },
	{ 0x2040 ,N_FLD(dbg_DEC_MD_CSC_COEF1)                ,"DEC_MD_CSC_COEF1"                  ,dbg_DEC_MD_CSC_COEF1                },
	{ 0x2044 ,N_FLD(dbg_DEC_MD_CSC_COEF2)                ,"DEC_MD_CSC_COEF2"                  ,dbg_DEC_MD_CSC_COEF2                },
	{ 0x2048 ,N_FLD(dbg_DEC_MD_CSC_COEF3)                ,"DEC_MD_CSC_COEF3"                  ,dbg_DEC_MD_CSC_COEF3                },
	{ 0x204c ,N_FLD(dbg_DEC_MD_CSC_COEF4)                ,"DEC_MD_CSC_COEF4"                  ,dbg_DEC_MD_CSC_COEF4                },
	{ 0x2050 ,N_FLD(dbg_DEC_MD_CSC_OFFSET0)              ,"DEC_MD_CSC_OFFSET0"                ,dbg_DEC_MD_CSC_OFFSET0              },
	{ 0x2054 ,N_FLD(dbg_DEC_MD_CSC_OFFSET1)              ,"DEC_MD_CSC_OFFSET1"                ,dbg_DEC_MD_CSC_OFFSET1              },
	{ 0x2058 ,N_FLD(dbg_DEC_MD_CSC_OFFSET2)              ,"DEC_MD_CSC_OFFSET2"                ,dbg_DEC_MD_CSC_OFFSET2              },
	{ 0x205c ,N_FLD(dbg_DEC_SMUX_RO_LCNT)                ,"DEC_SMUX_RO_LCNT"                  ,dbg_DEC_SMUX_RO_LCNT                },
	{ 0x2060 ,N_FLD(dbg_DEC_GMAU_CTRL)                   ,"DEC_GMAU_CTRL"                     ,dbg_DEC_GMAU_CTRL                   },
	{ 0x2064 ,N_FLD(dbg_DEC_PIC_END_EN)                  ,"DEC_PIC_END_EN"                    ,dbg_DEC_PIC_END_EN                  },
	{ 0x2068 ,N_FLD(dbg_DEC_PIC_INIT_G0_TIMER)           ,"DEC_PIC_INIT_G0_TIMER"             ,dbg_DEC_PIC_INIT_G0_TIMER           },
	{ 0x206c ,N_FLD(dbg_DEC_PIC_INIT_G1_TIMER)           ,"DEC_PIC_INIT_G1_TIMER"             ,dbg_DEC_PIC_INIT_G1_TIMER           },
	{ 0x2070 ,N_FLD(dbg_DEC_PIC_INIT_G2_TIMER)           ,"DEC_PIC_INIT_G2_TIMER"             ,dbg_DEC_PIC_INIT_G2_TIMER           },
	{ 0x2074 ,N_FLD(dbg_DEC_PIC_END_INFO)                ,"DEC_PIC_END_INFO"                  ,dbg_DEC_PIC_END_INFO                },
	{ 0x2078 ,N_FLD(dbg_DEC_INTR_REG)                    ,"DEC_INTR_REG"                      ,dbg_DEC_INTR_REG                    },
	{ 0x207c ,0                                          ,"DEC_INTR_MASK"                     ,NULL                                },
	{ 0x2080 ,0                                          ,"DEC_INTR_MUX"                      ,NULL                                },
	{ 0x2084 ,0                                          ,"DEC_MSRC_INTR_TIME_STP"            ,NULL                                },
	{ 0x2088 ,0                                          ,"DEC_SSRC_INTR_TIME_STP"            ,NULL                                },
	{ 0x208c ,N_FLD(dbg_DEC_ADDR_SW_DE_SAV)              ,"DEC_ADDR_SW_DE_SAV"                ,dbg_DEC_ADDR_SW_DE_SAV              },
	{ 0x2090 ,N_FLD(dbg_DEC_ADDR_SW_CPU_GPU)             ,"DEC_ADDR_SW_CPU_GPU"               ,dbg_DEC_ADDR_SW_CPU_GPU             },
	{ 0x2094 ,N_FLD(dbg_DEC_ADDR_SW_CPU_SHADOW)          ,"DEC_ADDR_SW_CPU_SHADOW"            ,dbg_DEC_ADDR_SW_CPU_SHADOW          },
	{ 0x3000 ,N_FLD(dbg_DED_PIC_INIT)                    ,"DED_PIC_INIT"                      ,dbg_DED_PIC_INIT                    },
	{ 0x3004 ,N_FLD(dbg_DED_PIC_START)                   ,"DED_PIC_START"                     ,dbg_DED_PIC_START                   },
	{ 0x3008 ,N_FLD(dbg_DED_DE_VENC_IF)                  ,"DED_DE_VENC_IF"                    ,dbg_DED_DE_VENC_IF                  },
	{ 0x300c ,N_FLD(dbg_DED_DPATH_CTRL)                  ,"DED_DPATH_CTRL"                    ,dbg_DED_DPATH_CTRL                  },
	{ 0x3010 ,N_FLD(dbg_DED_CVE_PARAM0)                  ,"DED_CVE_PARAM0"                    ,dbg_DED_CVE_PARAM0                  },
	{ 0x3014 ,N_FLD(dbg_DED_CVE_PARAM1)                  ,"DED_CVE_PARAM1"                    ,dbg_DED_CVE_PARAM1                  },
	{ 0x3018 ,N_FLD(dbg_DED_CVE_PARAM2)                  ,"DED_CVE_PARAM2"                    ,dbg_DED_CVE_PARAM2                  },
	{ 0x301c ,N_FLD(dbg_DED_CVE_PARAM3)                  ,"DED_CVE_PARAM3"                    ,dbg_DED_CVE_PARAM3                  },
	{ 0x3020 ,N_FLD(dbg_DED_CVE_PULSE_DLY)               ,"DED_CVE_PULSE_DLY"                 ,dbg_DED_CVE_PULSE_DLY               },
	{ 0x3024 ,N_FLD(dbg_DED_GMAU_CTRL)                   ,"DED_GMAU_CTRL"                     ,dbg_DED_GMAU_CTRL                   },
	{ 0x3028 ,N_FLD(dbg_DED_PIC_END_EN)                  ,"DED_PIC_END_EN"                    ,dbg_DED_PIC_END_EN                  },
	{ 0x302c ,N_FLD(dbg_DED_PIC_INIT_G0_TIMER)           ,"DED_PIC_INIT_G0_TIMER"             ,dbg_DED_PIC_INIT_G0_TIMER           },
	{ 0x3030 ,N_FLD(dbg_DED_PIC_INIT_G1_TIMER)           ,"DED_PIC_INIT_G1_TIMER"             ,dbg_DED_PIC_INIT_G1_TIMER           },
	{ 0x3034 ,N_FLD(dbg_DED_PIC_INIT_G2_TIMER)           ,"DED_PIC_INIT_G2_TIMER"             ,dbg_DED_PIC_INIT_G2_TIMER           },
	{ 0x3038 ,N_FLD(dbg_DED_PIC_INIT_G3_TIMER)           ,"DED_PIC_INIT_G3_TIMER"             ,dbg_DED_PIC_INIT_G3_TIMER           },
	{ 0x303c ,N_FLD(dbg_DED_PIC_END_INFO)                ,"DED_PIC_END_INFO"                  ,dbg_DED_PIC_END_INFO                },
	{ 0x3040 ,N_FLD(dbg_DED_INTR_REG)                    ,"DED_INTR_REG"                      ,dbg_DED_INTR_REG                    },
	{ 0x3044 ,0                                          ,"DED_INTR_MASK"                     ,NULL                                },
	{ 0x3048 ,0                                          ,"DED_INTR_MUX"                      ,NULL                                },
	{ 0x304c ,0                                          ,"DED_CVE_INTR_TIME_STP"             ,NULL                                },
	{ 0x3050 ,N_FLD(dbg_DED_ADDR_SW_DE_SAV)              ,"DED_ADDR_SW_DE_SAV"                ,dbg_DED_ADDR_SW_DE_SAV              },
	{ 0x3054 ,N_FLD(dbg_DED_ADDR_SW_CPU_GPU)             ,"DED_ADDR_SW_CPU_GPU"               ,dbg_DED_ADDR_SW_CPU_GPU             },
	{ 0x3058 ,N_FLD(dbg_DED_ADDR_SW_CPU_SHADOW)          ,"DED_ADDR_SW_CPU_SHADOW"            ,dbg_DED_ADDR_SW_CPU_SHADOW          },
	{ 0x4000 ,N_FLD(dbg_DEC_DE_INTR_FLAG_MCU)            ,"DEC_DE_INTR_FLAG_MCU"              ,dbg_DEC_DE_INTR_FLAG_MCU            },
	{ 0x4004 ,N_FLD(dbg_DEC_DE_INTR_FLAG_CPU)            ,"DEC_DE_INTR_FLAG_CPU"              ,dbg_DEC_DE_INTR_FLAG_CPU            },
	{ 0x4008 ,N_FLD(dbg_DEE_CVI_MUX_SEL)                 ,"DEE_CVI_MUX_SEL"                   ,dbg_DEE_CVI_MUX_SEL                 },
	{ 0x400c ,N_FLD(dbg_DEE_PE0_HIF_OFFSET)              ,"DEE_PE0_HIF_OFFSET"                ,dbg_DEE_PE0_HIF_OFFSET              },
	{ 0x4010 ,N_FLD(dbg_DEE_SM_HIF_OFFSET)               ,"DEE_SM_HIF_OFFSET"                 ,dbg_DEE_SM_HIF_OFFSET               },
	{ 0x4014 ,N_FLD(dbg_DEE_PE1_HIF_OFFSET)              ,"DEE_PE1_HIF_OFFSET"                ,dbg_DEE_PE1_HIF_OFFSET              },
	{ 0x4018 ,N_FLD(dbg_DEE_CVD_ADDR_SW_DE_SAV)          ,"DEE_CVD_ADDR_SW_DE_SAV"            ,dbg_DEE_CVD_ADDR_SW_DE_SAV          },
	{ 0x401c ,N_FLD(dbg_DEE_CVD_ADDR_SW_CPU_GPU)         ,"DEE_CVD_ADDR_SW_CPU_GPU"           ,dbg_DEE_CVD_ADDR_SW_CPU_GPU         },
	{ 0x4020 ,N_FLD(dbg_DEE_CVD_ADDR_SW_CPU_SHADOW)      ,"DEE_CVD_ADDR_SW_CPU_SHADOW"        ,dbg_DEE_CVD_ADDR_SW_CPU_SHADOW      },
	{ 0x4024 ,N_FLD(dbg_DEE_MCU_ADDR_SW_DE_SAV)          ,"DEE_MCU_ADDR_SW_DE_SAV"            ,dbg_DEE_MCU_ADDR_SW_DE_SAV          },
	{ 0x4028 ,N_FLD(dbg_DEE_MCU_ADDR_SW_CPU_GPU)         ,"DEE_MCU_ADDR_SW_CPU_GPU"           ,dbg_DEE_MCU_ADDR_SW_CPU_GPU         },
	{ 0x402c ,N_FLD(dbg_DEE_MCU_ADDR_SW_CPU_SHADOW)      ,"DEE_MCU_ADDR_SW_CPU_SHADOW"        ,dbg_DEE_MCU_ADDR_SW_CPU_SHADOW      },
	{ 0x4030 ,N_FLD(dbg_DEE_MCU_ADDR_WINDOW)             ,"DEE_MCU_ADDR_WINDOW"               ,dbg_DEE_MCU_ADDR_WINDOW             },
	{ 0x4034 ,N_FLD(dbg_DEE_INTR_REG)                    ,"DEE_INTR_REG"                      ,dbg_DEE_INTR_REG                    },
	{ 0x4038 ,N_FLD(dbg_DEE_INTR_MASK)                   ,"DEE_INTR_MASK"                     ,dbg_DEE_INTR_MASK                   },
	{ 0 , } // end marker
};

#endif
