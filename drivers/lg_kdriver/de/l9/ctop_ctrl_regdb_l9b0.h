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

#ifndef _DBG_CTOP_CTRL_h
#define _DBG_CTOP_CTRL_h

/*--------------------------------------------
	0xfd300010 CTR00_CLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR00_CLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"gfx_aclk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"gfx_pclk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"cvda_clk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"de_apb_clk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_usb_bt_init"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"slt_apbclk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_usb_init"              },
};

/*--------------------------------------------
	0xfd300014 CTR01_CLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR01_CLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"te_ahclk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"te_teclk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"ve_aclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,11 ,"ve270clk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,14 ,"veclk_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"sive_apbclk_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"gpu1clk_off_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"gpuclk_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"gpu_apbclk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"gpu0clk_off_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"gfx_clk_sel"                 },
};

/*--------------------------------------------
	0xfd300018 CTR02_CLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR02_CLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,2  ,"vd_declk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"vd_teclk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"vd_aclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,11 ,"vd2clk_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,14 ,"vd1clk_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"vdclk_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"vd_apbclk_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"icod_aclk_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"icodclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"te_aclk_sel"                 },
};

/*--------------------------------------------
	0xfd30001c CTR03_CLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR03_CLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,2  ,"f0_aclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"flexnoc2_aclk_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"flexnoc1_aclk_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,11 ,"flexnoc0_aclk_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,14 ,"aud_veclk_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"aud_teclk_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"aud_apbclk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"aud_aclk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"aud_dsp1aclk_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"aud_dsp0aclk_sel"            },
};

/*--------------------------------------------
	0xfd300020 CTR04_CLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR04_CLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"at2_apbclk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,11 ,"at1_apbclk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,14 ,"at0_apbclk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"s2_aclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"s1_aclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"s0_aclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"f2_aclk_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"f1_aclk_sel"                 },
};

/*--------------------------------------------
	0xfd300024 CTR05_SWRS_OF_DE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR05_SWRS_OF_DE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"swrst_def_vcr_de_dp"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"swrst_def_mif_de_dp"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"swrst_def_mif_de"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"swrst_def_mif_dea"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"swrst_dee_de_dp"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"swrst_dee_de"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"swrst_ded_de_dp"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"swrst_ded_de"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"swrst_ded_dea_dp"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"swrst_ded_dea"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"swrst_dec_ssc_de"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"swrst_dec_pe0_de"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"swrst_dec_mif_de"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"swrst_dec_mif_dea"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_deb_de_dp"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"swrst_deb_de"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"swrst_deb_dea"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"swrst_dea_de"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_dea_dea"               },
};

/*--------------------------------------------
	0xfd300028 CTR06_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR06_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"swrst_te_te1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"swrst_noc2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"swrst_noc1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"swrst_noc0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"swrst_de_vd"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"swrst_te_vd"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"swrst_vda"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"swrst_vd1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"swrst_vd2"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"swrst_vd"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"swrst_vd_apb"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"swrst_icoda"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"swrst_icod"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"swrst_tea"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"swrst_teah"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"swrst_te_te"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"swrst_te_ve"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"swrst_vea"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"swrst_ve"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"swrst_icod_p"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"swrst_te_apb"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"swrst_ve_apb"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"swrst_gpu1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"swrst_gpu0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"swrst_gpu_p"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_gfx"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"swrst_gfx_a"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"swrst_gfx_p"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"swrst_cvda"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_de_apb"                },
};

/*--------------------------------------------
	0xfd30002c CTR07_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR07_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"swrst_f2_a"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"swrst_f1_a"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"swrst_f0_a"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_slt_p"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"swrst_at2_p"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"swrst_at1_p"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_at0_p"                 },
};

/*--------------------------------------------
	0xfd300030 CTR08_CLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR08_CLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"def_vcr_de_clk_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,11 ,"def_mif_de_clk_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,14 ,"dee_de_clk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"ded_de_clk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"trace_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"dbgvsoc_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"atvsoc_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"atclk_sel"                   },
};

/*--------------------------------------------
	0xfd300034 CTR09_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR09_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"isol_en_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"pclken_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"ahbclken_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"swrst_ptmpg"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"swrst_ptm"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"swrst_prsys"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"swrst_prdbg"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"swrst_dbg1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"swrst_dbg0"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"swrst_dbgpg"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_at"                    },
};

/*--------------------------------------------
	0xfd300038 CTR10_AHBCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR10_AHBCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"ahb7_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"ahb6_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"ahb5_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"ahb4_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"ahb3_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"ahb2_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"ahb1_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"ahb0_sel"                    },
};

/*--------------------------------------------
	0xfd30003c CTR11_AHBCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR11_AHBCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"rmii_clkoff_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"ahb22_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"ahb21_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"ahb20_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"ahb19_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"ahb18_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"ahb17_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"ahb9_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"ahb8_sel"                    },
};

/*--------------------------------------------
	0xfd300040 CTR12_RMIICLK_OFF
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR12_RMIICLK_OFF[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,2  ,"dec_ssc_de_clk_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"dec_pe0_de_clk_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"dec_mif_de_clk_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,11 ,"deb_de_clk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,14 ,"dea_de_clk_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"def_mif_dea_clk_sel"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"ded_dea_clk_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"dec_mif_dea_clk_sel"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"deb_dea_clk_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"dea_dea_clk_sel"             },
};

/*--------------------------------------------
	0xfd300044 CTR13_AHBCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR13_AHBCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"ahb30_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"ahb29_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"ahb24_sel"                   },
};

/*--------------------------------------------
	0xfd300048 CTR14_AHB_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR14_AHB_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"swrst_ahb31"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"swrst_ahb30"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"swrst_ahb29"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"swrst_ahb28"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"swrst_ahb27"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"swrst_ahb26"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"swrst_ahb25"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"swrst_ahb24"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"swrst_ahb23"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"swrst_ahb22"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"swrst_ahb21"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"swrst_ahb20"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"swrst_ahb19"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"swrst_ahb18"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"swrst_ahb17"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"swrst_ahb16"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"swrst_ahb15"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"swrst_ahb14"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"swrst_ahb13"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"swrst_ahb12"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"swrst_ahb11"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"swrst_ahb10"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"swrst_ahb9"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"swrst_ahb8"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"swrst_ahb7"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"swrst_ahb6"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"swrst_ahb5"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_ahb4"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"swrst_ahb3"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"swrst_ahb2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"swrst_ahb1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_ahb0"                  },
};

/*--------------------------------------------
	0xfd30004c CTR15_AHB_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR15_AHB_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"swrst_ahb37"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_ahb36"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"swrst_ahb35"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"swrst_ahb34"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"swrst_ahb33"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_ahb32"                 },
};

/*--------------------------------------------
	0xfd300050 CTR16_BUSCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR16_BUSCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"bus7_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"bus6_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"bus5_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"bus4_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"bus3_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"bus2_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"bus1_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"bus0_sel"                    },
};

/*--------------------------------------------
	0xfd300054 CTR17_BUSCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR17_BUSCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"bus10_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"bus9_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"bus8_sel"                    },
};

/*--------------------------------------------
	0xfd300058 CTR18_REB_CPUBUS_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR18_REB_CPUBUS_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"swrst_bus10"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"swrst_bus9"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"swrst_bus8"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"swrst_bus7"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"swrst_bus6"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"swrst_bus5"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_bus4"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"swrst_bus3"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"swrst_bus2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"swrst_bus1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_bus0"                  },
};

/*--------------------------------------------
	0xfd30005c CTR19_APBCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR19_APBCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"apb0_7_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"apb0_6_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"apb0_5_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"apb0_4_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"apb0_3_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"apb0_2_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"apb0_1_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"apb0_0_sel"                  },
};

/*--------------------------------------------
	0xfd300060 CTR20_APBCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR20_APBCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"apb1_7_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"apb1_6_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"apb1_5_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"apb1_4_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"apb1_3_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"apb1_2_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"apb1_1_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"apb1_0_sel"                  },
};

/*--------------------------------------------
	0xfd300064 CTR21_APBCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR21_APBCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"apb1_15_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"apb1_14_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"apb1_13_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"apb1_12_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"apb1_11_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"apb1_10_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"apb1_9_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"apb1_8_sel"                  },
};

/*--------------------------------------------
	0xfd300068 CTR22_APBCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR22_APBCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"apb1_19_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"apb1_18_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"apb1_17_sel"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"apb1_16_sel"                 },
};

/*--------------------------------------------
	0xfd300070 CTR24_APB_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR24_APB_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"swrst_apb1_19"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"swrst_apb1_18"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"swrst_apb1_17"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"swrst_apb1_16"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"swrst_apb1_15"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"swrst_apb1_14"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"swrst_apb1_13"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"swrst_apb1_12"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"swrst_apb1_11"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"swrst_apb1_10"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"swrst_apb1_9"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"swrst_apb1_8"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"swrst_apb1_7"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"swrst_apb1_6"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"swrst_apb1_5"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"swrst_apb1_4"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"swrst_apb1_3"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"swrst_apb1_2"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"swrst_apb1_1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"swrst_apb1_0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"swrst_apb0_7"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"swrst_apb0_6"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"swrst_apb0_5"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"swrst_apb0_4"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"swrst_apb0_3"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"swrst_apb0_2"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"swrst_apb0_1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst_apb0_0"                },
};

/*--------------------------------------------
	0xfd300074 CTR25_DE_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR25_DE_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"swrst_def_disp"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"swrst_ded_disp"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"swrst_decssc_disp"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"swrst_decmif_disp"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"swrst_deb_disp"              },
};

/*--------------------------------------------
	0xfd300078 CTR26_EXTCLK_DIV_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR26_EXTCLK_DIV_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"lvds_clk_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"dco_sel"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"ssclk_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"msclk_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"extb_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,14 ,"exta_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"reg_ch3pix_clk_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"reg_ch3pix_clk_inv"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"cvbs27_sel_inv"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,25 ,"cvbs54_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"reg_se_clk_inv"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"reg_cve27_clk_inv"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"reg_cve54_clk_inv"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"reg_cvd27_clk_inv"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"reg_cvd54_clk_inv"           },
};

/*--------------------------------------------
	0xfd30007c CTR27_EXTCLK_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR27_EXTCLK_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ext_en_i"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"f27_18_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,2  ,"sc_ext_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"reg_slt_disp"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"reg_s_te"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"reg_sys"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"reg_disp_h"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"reg_disp_def_p"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"reg_disp_def"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"reg_disp_ded_p"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"reg_disp_ded"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"reg_disp_ssc"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"reg_disp_mif"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"reg_disp_dp"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"reg_disp_de"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"reg_swrst_se"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"reg_swrst_chb"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"reg_swrst_cha"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"reg_swrst_extb"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"reg_swrst_exta"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"reg_swrst_ch3"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"reg_swrst_scart"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"reg_swrst_vbi"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"reg_swrst_cvbs27"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"reg_swrst_cvbs54"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"reg_swrst_cvd27"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"reg_swrst_cvd54"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"reg_swrst_cve27"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"reg_swrst_cve54"             },
};

/*--------------------------------------------
	0xfd300080 CTR28_CPU_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR28_CPU_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"reg_wd1_reset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"reg_wd0_reset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"reg_neon1_reset"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"reg_neon0_reset"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"reg_scu_reset"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"reg_cpu_h"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"reg_periph_reset"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"reg_cpu1_reset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"reg_cpu0_reset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"reg_l2_reset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"a_stdby_cpu"                 },
};

/*--------------------------------------------
	0xfd300084 CTR29_SWRST
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR29_SWRST[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"ext_intr_pol_sel0"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"ext_intr_pol_sel1"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"ext_intr_pol_sel2"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"ext_intr_pol_sel3"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"cam_vcc_pol"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"pll_sel_core"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"pll_sel_m2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pll_sel_m1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"jtag1_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"aud_jtag_no"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"jtag0_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"gpu_high_speed"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"reg_m2_q_reset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"reg_m2_h_reset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"reg_m2_reset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"a_stdby_m2"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"reg_m1_h_reset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"reg_m1_reset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,25 ,"a_stdby_m1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"reg_m0_q_reset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"reg_m0_h_reset"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"reg_m0_reset"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"a_stdby_m0"                  },
};

/*--------------------------------------------
	0xfd300088 CTR30_BLOCK_MONITER
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR30_BLOCK_MONITER[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"sd_int_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"trace8bit_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"cpu_mon_31_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"traceclk_en"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"trace_en4"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"trace_en3"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"trace_en2"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"trace_en1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"usb_mon_en2"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"usb_mon_en1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gfx_mon_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"aad_mon_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"aud_mon_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"cpu_mon_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"de_mon_en"                   },
};

/*--------------------------------------------
	0xfd30008c CTR31_GPIO_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR31_GPIO_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gp0_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"gp1_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"gp2_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"gp3_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"gp4_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"gp5_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"gp6_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"gp7_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"gp8_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"gp9_ren_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"gp10_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"gp11_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"gp12_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"gp13_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"gp14_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gp15_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"gp16_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"gp17_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"gp18_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp19_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"gp20_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"gp21_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"gp22_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp23_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"gp24_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"gp25_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"gp26_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp27_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"gp28_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"gp29_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"gp30_ren_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp31_ren_ctrl"               },
};

/*--------------------------------------------
	0xfd300090 CTR32_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR32_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"stpio_en_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"gp4_0_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"gp4_1_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"gp4_2_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp4_3_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"gp4_4_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"gp4_5_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"gp4_6_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp4_7_mux_en"                },
};

/*--------------------------------------------
	0xfd300098 CTR34_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR34_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"gp6_3_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"gp6_4_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gp6_5_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp6_6_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp6_7_mux_en"                },
};

/*--------------------------------------------
	0xfd30009c CTR35_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR35_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"gp7_5_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gp7_6_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp7_7_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp6_0_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp6_1_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp6_2_mux_en"                },
};

/*--------------------------------------------
	0xfd3000a0 CTR36_UART_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR36_UART_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"rx_sel_de"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"rx_sel_sp"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"uart2_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"uart1_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"uart0_sel"                   },
};

/*--------------------------------------------
	0xfd3000a4 CTR37_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR37_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"gp8_5_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"gp8_6_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"gp8_7_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gp7_0_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp7_1_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp7_2_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp7_3_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp7_4_mux_en"                },
};

/*--------------------------------------------
	0xfd3000a8 CTR38_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR38_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp8_1_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp8_2_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp8_3_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp8_4_mux_en"                },
};

/*--------------------------------------------
	0xfd3000ac CTR39_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR39_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"sc_clk_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"gp10_2_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"gp10_3_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp10_4_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"gp10_5_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"gp10_6_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"gp10_7_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp9_0_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"gp9_1_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"gp9_2_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"gp9_3_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp9_4_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"gp9_5_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"gp9_6_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"gp9_7_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp8_0_mux_en"                },
};

/*--------------------------------------------
	0xfd3000b0 CTR40_GPU_DFT_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR40_GPU_DFT_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gpu_pwrdnbypass"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gpu_testin0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gpu_testin1"                 },
};

/*--------------------------------------------
	0xfd3000b4 CTR41_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR41_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pull_up_ctrl7"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pull_up_ctrl6"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl5"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pull_up_ctrl4"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl3"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pull_up_ctrl2"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl1"               },
};

/*--------------------------------------------
	0xfd3000b8 CTR42_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR42_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pull_up_ctrl15"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pull_up_ctrl14"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pull_up_ctrl13"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl12"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pull_up_ctrl11"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl10"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pull_up_ctrl9"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl8"               },
};

/*--------------------------------------------
	0xfd3000bc CTR43_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR43_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl18"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl17"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl16"              },
};

/*--------------------------------------------
	0xfd3000c0 CTR44_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR44_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl21"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl20"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl19"              },
};

/*--------------------------------------------
	0xfd3000c4 CTR45_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR45_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pull_up_ctrl27"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl26"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pull_up_ctrl25"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl24"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pull_up_ctrl23"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl22"              },
};

/*--------------------------------------------
	0xfd3000c8 CTR46_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR46_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl30"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pull_up_ctrl29"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl28"              },
};

/*--------------------------------------------
	0xfd3000cc CTR47_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR47_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"pull_up_ctrl38"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pull_up_ctrl37"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pull_up_ctrl36"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl35"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pull_up_ctrl34"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl33"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pull_up_ctrl32"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl31"              },
};

/*--------------------------------------------
	0xfd3000d0 CTR48_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR48_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"pull_up_ctrl44"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl43"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pull_up_ctrl42"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl41"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pull_up_ctrl40"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl39"              },
};

/*--------------------------------------------
	0xfd3000d4 CTR49_PULLUP_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR49_PULLUP_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"pull_up_ctrl50"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pull_up_ctrl49"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"pull_up_ctrl48"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"pull_up_ctrl47"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"pull_up_ctrl46"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"pull_up_ctrl45"              },
};

/*--------------------------------------------
	0xfd3000d8 CTR50_TPIO_SEL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR50_TPIO_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"tpio_sel_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"tpo_sel_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"swrst"                       },
};

/*--------------------------------------------
	0xfd3000dc CTR51_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR51_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp11_6_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp11_7_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp10_0_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp10_1_mux_en"               },
};

/*--------------------------------------------
	0xfd3000e0 CTR52_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR52_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"en_aud_dacrlrch"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"gp11_0_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gp11_1_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp11_2_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp11_3_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp11_4_mux_en"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp11_5_mux_en"               },
};

/*--------------------------------------------
	0xfd3000e4 CTR53_GPIO_MUX_ENABLE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR53_GPIO_MUX_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"gp5_0_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"gp5_1_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"gp5_2_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"gp5_3_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"gp5_4_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"gp5_5_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"gp5_6_mux_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"gp5_7_mux_en"                },
};

/*--------------------------------------------
	0xfd3000e8 CTR54_BT_USB_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR54_BT_USB_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"dftclk_ctrl"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"pd"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"bt_testclk0_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,21 ,"bt_txpreemphasistune0_ctrl"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"bt_txrisetune0_ctrl"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"bt_commononn_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,25 ,"bt_refclksel_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,27 ,"bt_refclkdiv_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"bt_testen_en_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"bt_vatestenb_en_ctrl"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"bt_siddq_en_ctrl"            },
};

/*--------------------------------------------
	0xfd3000ec CTR55_RGG_SDEC_DCO_FCW_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR55_RGG_SDEC_DCO_FCW_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,0  ,"sd_dco_fcw_ctrl"             },
};

/*--------------------------------------------
	0xfd3000f0 CTR56_BT_USB_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR56_BT_USB_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"testaddr"                    },
};

/*--------------------------------------------
	0xfd3000f4 CTR57_BT_USB_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR57_BT_USB_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,3  ,"testdatain"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"testdataoutsel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"txvreftune"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"txfslstune"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"vregtune"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,21 ,"txhsxvtune"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"sqrxtune"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"compdistune"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"loopbackenb"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"otgdisable"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"portreset"                   },
};

/*--------------------------------------------
	0xfd3000f8 CTR58_MAIN_0_1_USB_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR58_MAIN_0_1_USB_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"testclk1_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,17 ,"txpreemphasistune1_ctrl"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"txrisetune1_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"testclk0_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,21 ,"txpreemphasistune0_ctrl"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"txrisetune0_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"commononn_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,25 ,"refclksel_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,27 ,"refclkdiv_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"testen_en_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"vatestenb_en_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"siddq_en_ctrl"               },
};

/*--------------------------------------------
	0xfd3000fc CTR59_BT_USB_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR59_BT_USB_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"testaddr1"                   },
};

/*--------------------------------------------
	0xfd300100 CTR60_MAIN_0_1_USB_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR60_MAIN_0_1_USB_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"testdatain1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"testdataoutsel1"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,9  ,"txvreftune1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,13 ,"txfslstune1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"vregtune1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"txhsxvtune1"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"sqrxtune1"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"compdistune1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"loopbackenb1"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"portreset1"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"testaddr0"                   },
};

/*--------------------------------------------
	0xfd300104 CTR61_MAIN_0_1_USB_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR61_MAIN_0_1_USB_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,3  ,"testdatain0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"testdataoutsel0"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"txvreftune0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"txfslstune0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"vregtune0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,21 ,"txhsxvtune0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"sqrxtune0"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"compdistune0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,29 ,"loopbackenb0"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"otgdisable0"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"portreset0"                  },
};

/*--------------------------------------------
	0xfd300108 CTR62_DISPLAY_PLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR62_DISPLAY_PLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"disp_pre_fd_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"disp_od_fout_ctrl"           },
};

/*--------------------------------------------
	0xfd30010c CTR63_DISPLAY_PLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR63_DISPLAY_PLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"disp_udex_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,5  ,"disp_msex_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,14 ,"disp_nsc_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,18 ,"disp_npc_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"disp_m_ctrl"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,27 ,"disp_cih_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"disp_lf_ctrl"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"disp_pdb_ctrl"               },
};

/*--------------------------------------------
	0xfd3001bc CTR64_DCO_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR64_DCO_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,18 ,"sd_dco_g_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,21 ,"sd_dco_lpf_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"sd_dco_resetb_ctrl"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"sd_dco_rom_test_ctrl"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"de_dco_g_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"de_dco_lpf_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"de_dco_resetb_ctrl"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"de_dco_rom_test_ctrl"        },
};

/*--------------------------------------------
	0xfd3001c4 CTR66_MAIN2_SYSPLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR66_MAIN2_SYSPLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"m2_dr3p_pre_fd_ctrl"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"m2_dr3p_od_fout_ctrl"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"m2_dr3p_dtr_sel_ctrl"        },
};

/*--------------------------------------------
	0xfd3001c8 CTR67_MAIN2_SYSPLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR67_MAIN2_SYSPLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"m2_dr3p_udex_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,5  ,"m2_dr3p_msex_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,14 ,"m2_dr3p_nsc_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,18 ,"m2_dr3p_npc_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"m2_dr3p_m_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,27 ,"m2_dr3p_cih_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"m2_dr3p_lf_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"m2_dr3p_pdb_ctrl"            },
};

/*--------------------------------------------
	0xfd3001cc CTR68_MAIN2_SYSPLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR68_MAIN2_SYSPLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"m1_dr3p_pre_fd_ctrl"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"m1_dr3p_od_fout_ctrl"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"m1_dr3p_dtr_sel_ctrl"        },
};

/*--------------------------------------------
	0xfd3001d0 CTR69_MAIN2_SYSPLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR69_MAIN2_SYSPLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"m1_dr3p_udex_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,5  ,"m1_dr3p_msex_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,14 ,"m1_dr3p_nsc_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,18 ,"m1_dr3p_npc_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"m1_dr3p_m_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,27 ,"m1_dr3p_cih_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"m1_dr3p_lf_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"m1_dr3p_pdb_ctrl"            },
};

/*--------------------------------------------
	0xfd3001d4 CTR70_CPUPLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR70_CPUPLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"c_dr3p_pre_fd_ctrl"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"c_dr3p_od_fout_ctrl"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"c_dr3p_dtr_sel_ctrl"         },
};

/*--------------------------------------------
	0xfd3001d8 CTR71_CPUPLL_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR71_CPUPLL_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"c_dr3p_udex_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,5  ,"c_dr3p_msex_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,14 ,"c_dr3p_nsc_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,18 ,"c_dr3p_npc_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"c_dr3p_m_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,27 ,"c_dr3p_cih_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"c_dr3p_lf_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"c_dr3p_pdb_ctrl"             },
};

/*--------------------------------------------
	0xfd3001dc CTR72_HSLVDS_TX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR72_HSLVDS_TX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"lv_flip_en_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,18 ,"lv_pemp_te2_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,20 ,"lv_pemp_td2_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,22 ,"lv_pemp_tclk2_ctrl"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"lv_pemp_tc2_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"lv_pemp_tb2_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"lv_pemp_ta2_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"lv_pemp_te1_ctrl"            },
};

/*--------------------------------------------
	0xfd3001e0 CTR73_HSLVDS_TX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR73_HSLVDS_TX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,1  ,"lv_pemp_td1_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,3  ,"lv_pemp_tclk1_ctrl"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,5  ,"lv_pemp_tc1_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,7  ,"lv_pemp_tb1_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,9  ,"lv_pemp_ta1_ctrl"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"lv_rf_ctrl"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"lv_rmlvds_en_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,14 ,"lv_swc_te2_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"lv_swc_td2_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"lv_swc_tclk2_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,23 ,"lv_swc_tc2_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,26 ,"lv_swc_tb2_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,29 ,"lv_swc_ta2_ctrl"             },
};

/*--------------------------------------------
	0xfd3001e4 CTR74_HSLVDS_TX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR74_HSLVDS_TX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"lv_swc_te1_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"lv_swc_td1_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,7  ,"lv_swc_tclk1_ctrl"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,10 ,"lv_swc_tc1_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"lv_swc_tb1_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"lv_swc_ta1_ctrl"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,19 ,"lv_pdb_ch_ctrl"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"lv_pdb_ctrl"                 },
};

/*--------------------------------------------
	0xfd3001e8 CTR75_HSLVDS_RX_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_CTR75_HSLVDS_RX_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,5  ,"link2_ch_swap"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,13 ,"link1_ch_swap"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"rx1_sel_speed_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"rx0_sel_speed_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"rx1_sel_8b10b_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"rx0_sel_8b10b_en"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,27 ,"rx1_rf_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"rx0_rf_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"rx1_pdb_en"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"rx0_pdb_en"                  },
};

DBG_REG_T gDbgRegCTOP_CTRL[] = {
	{ 0xfd300010 ,N_FLD(dbg_CTR00_CLK_DIV_SEL)               ,"CTR00_CLK_DIV_SEL"                 ,dbg_CTR00_CLK_DIV_SEL               },
	{ 0xfd300014 ,N_FLD(dbg_CTR01_CLK_DIV_SEL)               ,"CTR01_CLK_DIV_SEL"                 ,dbg_CTR01_CLK_DIV_SEL               },
	{ 0xfd300018 ,N_FLD(dbg_CTR02_CLK_DIV_SEL)               ,"CTR02_CLK_DIV_SEL"                 ,dbg_CTR02_CLK_DIV_SEL               },
	{ 0xfd30001c ,N_FLD(dbg_CTR03_CLK_DIV_SEL)               ,"CTR03_CLK_DIV_SEL"                 ,dbg_CTR03_CLK_DIV_SEL               },
	{ 0xfd300020 ,N_FLD(dbg_CTR04_CLK_DIV_SEL)               ,"CTR04_CLK_DIV_SEL"                 ,dbg_CTR04_CLK_DIV_SEL               },
	{ 0xfd300024 ,N_FLD(dbg_CTR05_SWRS_OF_DE)                ,"CTR05_SWRS_OF_DE"                  ,dbg_CTR05_SWRS_OF_DE                },
	{ 0xfd300028 ,N_FLD(dbg_CTR06_SWRST)                     ,"CTR06_SWRST"                       ,dbg_CTR06_SWRST                     },
	{ 0xfd30002c ,N_FLD(dbg_CTR07_SWRST)                     ,"CTR07_SWRST"                       ,dbg_CTR07_SWRST                     },
	{ 0xfd300030 ,N_FLD(dbg_CTR08_CLK_DIV_SEL)               ,"CTR08_CLK_DIV_SEL"                 ,dbg_CTR08_CLK_DIV_SEL               },
	{ 0xfd300034 ,N_FLD(dbg_CTR09_SWRST)                     ,"CTR09_SWRST"                       ,dbg_CTR09_SWRST                     },
	{ 0xfd300038 ,N_FLD(dbg_CTR10_AHBCLK_DIV_SEL)            ,"CTR10_AHBCLK_DIV_SEL"              ,dbg_CTR10_AHBCLK_DIV_SEL            },
	{ 0xfd30003c ,N_FLD(dbg_CTR11_AHBCLK_DIV_SEL)            ,"CTR11_AHBCLK_DIV_SEL"              ,dbg_CTR11_AHBCLK_DIV_SEL            },
	{ 0xfd300040 ,N_FLD(dbg_CTR12_RMIICLK_OFF)               ,"CTR12_RMIICLK_OFF"                 ,dbg_CTR12_RMIICLK_OFF               },
	{ 0xfd300044 ,N_FLD(dbg_CTR13_AHBCLK_DIV_SEL)            ,"CTR13_AHBCLK_DIV_SEL"              ,dbg_CTR13_AHBCLK_DIV_SEL            },
	{ 0xfd300048 ,N_FLD(dbg_CTR14_AHB_SWRST)                 ,"CTR14_AHB_SWRST"                   ,dbg_CTR14_AHB_SWRST                 },
	{ 0xfd30004c ,N_FLD(dbg_CTR15_AHB_SWRST)                 ,"CTR15_AHB_SWRST"                   ,dbg_CTR15_AHB_SWRST                 },
	{ 0xfd300050 ,N_FLD(dbg_CTR16_BUSCLK_DIV_SEL)            ,"CTR16_BUSCLK_DIV_SEL"              ,dbg_CTR16_BUSCLK_DIV_SEL            },
	{ 0xfd300054 ,N_FLD(dbg_CTR17_BUSCLK_DIV_SEL)            ,"CTR17_BUSCLK_DIV_SEL"              ,dbg_CTR17_BUSCLK_DIV_SEL            },
	{ 0xfd300058 ,N_FLD(dbg_CTR18_REB_CPUBUS_SWRST)          ,"CTR18_REB_CPUBUS_SWRST"            ,dbg_CTR18_REB_CPUBUS_SWRST          },
	{ 0xfd30005c ,N_FLD(dbg_CTR19_APBCLK_DIV_SEL)            ,"CTR19_APBCLK_DIV_SEL"              ,dbg_CTR19_APBCLK_DIV_SEL            },
	{ 0xfd300060 ,N_FLD(dbg_CTR20_APBCLK_DIV_SEL)            ,"CTR20_APBCLK_DIV_SEL"              ,dbg_CTR20_APBCLK_DIV_SEL            },
	{ 0xfd300064 ,N_FLD(dbg_CTR21_APBCLK_DIV_SEL)            ,"CTR21_APBCLK_DIV_SEL"              ,dbg_CTR21_APBCLK_DIV_SEL            },
	{ 0xfd300068 ,N_FLD(dbg_CTR22_APBCLK_DIV_SEL)            ,"CTR22_APBCLK_DIV_SEL"              ,dbg_CTR22_APBCLK_DIV_SEL            },
	{ 0xfd300070 ,N_FLD(dbg_CTR24_APB_SWRST)                 ,"CTR24_APB_SWRST"                   ,dbg_CTR24_APB_SWRST                 },
	{ 0xfd300074 ,N_FLD(dbg_CTR25_DE_SWRST)                  ,"CTR25_DE_SWRST"                    ,dbg_CTR25_DE_SWRST                  },
	{ 0xfd300078 ,N_FLD(dbg_CTR26_EXTCLK_DIV_SEL)            ,"CTR26_EXTCLK_DIV_SEL"              ,dbg_CTR26_EXTCLK_DIV_SEL            },
	{ 0xfd30007c ,N_FLD(dbg_CTR27_EXTCLK_SWRST)              ,"CTR27_EXTCLK_SWRST"                ,dbg_CTR27_EXTCLK_SWRST              },
	{ 0xfd300080 ,N_FLD(dbg_CTR28_CPU_SWRST)                 ,"CTR28_CPU_SWRST"                   ,dbg_CTR28_CPU_SWRST                 },
	{ 0xfd300084 ,N_FLD(dbg_CTR29_SWRST)                     ,"CTR29_SWRST"                       ,dbg_CTR29_SWRST                     },
	{ 0xfd300088 ,N_FLD(dbg_CTR30_BLOCK_MONITER)             ,"CTR30_BLOCK_MONITER"               ,dbg_CTR30_BLOCK_MONITER             },
	{ 0xfd30008c ,N_FLD(dbg_CTR31_GPIO_PULLUP_CTRL)          ,"CTR31_GPIO_PULLUP_CTRL"            ,dbg_CTR31_GPIO_PULLUP_CTRL          },
	{ 0xfd300090 ,N_FLD(dbg_CTR32_GPIO_MUX_ENABLE)           ,"CTR32_GPIO_MUX_ENABLE"             ,dbg_CTR32_GPIO_MUX_ENABLE           },
	{ 0xfd300098 ,N_FLD(dbg_CTR34_GPIO_MUX_ENABLE)           ,"CTR34_GPIO_MUX_ENABLE"             ,dbg_CTR34_GPIO_MUX_ENABLE           },
	{ 0xfd30009c ,N_FLD(dbg_CTR35_GPIO_MUX_ENABLE)           ,"CTR35_GPIO_MUX_ENABLE"             ,dbg_CTR35_GPIO_MUX_ENABLE           },
	{ 0xfd3000a0 ,N_FLD(dbg_CTR36_UART_SEL)                  ,"CTR36_UART_SEL"                    ,dbg_CTR36_UART_SEL                  },
	{ 0xfd3000a4 ,N_FLD(dbg_CTR37_GPIO_MUX_ENABLE)           ,"CTR37_GPIO_MUX_ENABLE"             ,dbg_CTR37_GPIO_MUX_ENABLE           },
	{ 0xfd3000a8 ,N_FLD(dbg_CTR38_GPIO_MUX_ENABLE)           ,"CTR38_GPIO_MUX_ENABLE"             ,dbg_CTR38_GPIO_MUX_ENABLE           },
	{ 0xfd3000ac ,N_FLD(dbg_CTR39_GPIO_MUX_ENABLE)           ,"CTR39_GPIO_MUX_ENABLE"             ,dbg_CTR39_GPIO_MUX_ENABLE           },
	{ 0xfd3000b0 ,N_FLD(dbg_CTR40_GPU_DFT_CTRL)              ,"CTR40_GPU_DFT_CTRL"                ,dbg_CTR40_GPU_DFT_CTRL              },
	{ 0xfd3000b4 ,N_FLD(dbg_CTR41_PULLUP_CTRL)               ,"CTR41_PULLUP_CTRL"                 ,dbg_CTR41_PULLUP_CTRL               },
	{ 0xfd3000b8 ,N_FLD(dbg_CTR42_PULLUP_CTRL)               ,"CTR42_PULLUP_CTRL"                 ,dbg_CTR42_PULLUP_CTRL               },
	{ 0xfd3000bc ,N_FLD(dbg_CTR43_PULLUP_CTRL)               ,"CTR43_PULLUP_CTRL"                 ,dbg_CTR43_PULLUP_CTRL               },
	{ 0xfd3000c0 ,N_FLD(dbg_CTR44_PULLUP_CTRL)               ,"CTR44_PULLUP_CTRL"                 ,dbg_CTR44_PULLUP_CTRL               },
	{ 0xfd3000c4 ,N_FLD(dbg_CTR45_PULLUP_CTRL)               ,"CTR45_PULLUP_CTRL"                 ,dbg_CTR45_PULLUP_CTRL               },
	{ 0xfd3000c8 ,N_FLD(dbg_CTR46_PULLUP_CTRL)               ,"CTR46_PULLUP_CTRL"                 ,dbg_CTR46_PULLUP_CTRL               },
	{ 0xfd3000cc ,N_FLD(dbg_CTR47_PULLUP_CTRL)               ,"CTR47_PULLUP_CTRL"                 ,dbg_CTR47_PULLUP_CTRL               },
	{ 0xfd3000d0 ,N_FLD(dbg_CTR48_PULLUP_CTRL)               ,"CTR48_PULLUP_CTRL"                 ,dbg_CTR48_PULLUP_CTRL               },
	{ 0xfd3000d4 ,N_FLD(dbg_CTR49_PULLUP_CTRL)               ,"CTR49_PULLUP_CTRL"                 ,dbg_CTR49_PULLUP_CTRL               },
	{ 0xfd3000d8 ,N_FLD(dbg_CTR50_TPIO_SEL)                  ,"CTR50_TPIO_SEL"                    ,dbg_CTR50_TPIO_SEL                  },
	{ 0xfd3000dc ,N_FLD(dbg_CTR51_GPIO_MUX_ENABLE)           ,"CTR51_GPIO_MUX_ENABLE"             ,dbg_CTR51_GPIO_MUX_ENABLE           },
	{ 0xfd3000e0 ,N_FLD(dbg_CTR52_GPIO_MUX_ENABLE)           ,"CTR52_GPIO_MUX_ENABLE"             ,dbg_CTR52_GPIO_MUX_ENABLE           },
	{ 0xfd3000e4 ,N_FLD(dbg_CTR53_GPIO_MUX_ENABLE)           ,"CTR53_GPIO_MUX_ENABLE"             ,dbg_CTR53_GPIO_MUX_ENABLE           },
	{ 0xfd3000e8 ,N_FLD(dbg_CTR54_BT_USB_CTRL)               ,"CTR54_BT_USB_CTRL"                 ,dbg_CTR54_BT_USB_CTRL               },
	{ 0xfd3000ec ,N_FLD(dbg_CTR55_RGG_SDEC_DCO_FCW_CTRL)     ,"CTR55_RGG_SDEC_DCO_FCW_CTRL"       ,dbg_CTR55_RGG_SDEC_DCO_FCW_CTRL     },
	{ 0xfd3000f0 ,N_FLD(dbg_CTR56_BT_USB_CTRL)               ,"CTR56_BT_USB_CTRL"                 ,dbg_CTR56_BT_USB_CTRL               },
	{ 0xfd3000f4 ,N_FLD(dbg_CTR57_BT_USB_CTRL)               ,"CTR57_BT_USB_CTRL"                 ,dbg_CTR57_BT_USB_CTRL               },
	{ 0xfd3000f8 ,N_FLD(dbg_CTR58_MAIN_0_1_USB_CTRL)         ,"CTR58_MAIN_0_1_USB_CTRL"           ,dbg_CTR58_MAIN_0_1_USB_CTRL         },
	{ 0xfd3000fc ,N_FLD(dbg_CTR59_BT_USB_CTRL)               ,"CTR59_BT_USB_CTRL"                 ,dbg_CTR59_BT_USB_CTRL               },
	{ 0xfd300100 ,N_FLD(dbg_CTR60_MAIN_0_1_USB_CTRL)         ,"CTR60_MAIN_0_1_USB_CTRL"           ,dbg_CTR60_MAIN_0_1_USB_CTRL         },
	{ 0xfd300104 ,N_FLD(dbg_CTR61_MAIN_0_1_USB_CTRL)         ,"CTR61_MAIN_0_1_USB_CTRL"           ,dbg_CTR61_MAIN_0_1_USB_CTRL         },
	{ 0xfd300108 ,N_FLD(dbg_CTR62_DISPLAY_PLL_CTRL)          ,"CTR62_DISPLAY_PLL_CTRL"            ,dbg_CTR62_DISPLAY_PLL_CTRL          },
	{ 0xfd30010c ,N_FLD(dbg_CTR63_DISPLAY_PLL_CTRL)          ,"CTR63_DISPLAY_PLL_CTRL"            ,dbg_CTR63_DISPLAY_PLL_CTRL          },
	{ 0xfd3001bc ,N_FLD(dbg_CTR64_DCO_CTRL)                  ,"CTR64_DCO_CTRL"                    ,dbg_CTR64_DCO_CTRL                  },
	{ 0xfd3001c4 ,N_FLD(dbg_CTR66_MAIN2_SYSPLL_CTRL)         ,"CTR66_MAIN2_SYSPLL_CTRL"           ,dbg_CTR66_MAIN2_SYSPLL_CTRL         },
	{ 0xfd3001c8 ,N_FLD(dbg_CTR67_MAIN2_SYSPLL_CTRL)         ,"CTR67_MAIN2_SYSPLL_CTRL"           ,dbg_CTR67_MAIN2_SYSPLL_CTRL         },
	{ 0xfd3001cc ,N_FLD(dbg_CTR68_MAIN2_SYSPLL_CTRL)         ,"CTR68_MAIN2_SYSPLL_CTRL"           ,dbg_CTR68_MAIN2_SYSPLL_CTRL         },
	{ 0xfd3001d0 ,N_FLD(dbg_CTR69_MAIN2_SYSPLL_CTRL)         ,"CTR69_MAIN2_SYSPLL_CTRL"           ,dbg_CTR69_MAIN2_SYSPLL_CTRL         },
	{ 0xfd3001d4 ,N_FLD(dbg_CTR70_CPUPLL_CTRL)               ,"CTR70_CPUPLL_CTRL"                 ,dbg_CTR70_CPUPLL_CTRL               },
	{ 0xfd3001d8 ,N_FLD(dbg_CTR71_CPUPLL_CTRL)               ,"CTR71_CPUPLL_CTRL"                 ,dbg_CTR71_CPUPLL_CTRL               },
	{ 0xfd3001dc ,N_FLD(dbg_CTR72_HSLVDS_TX_CTRL)            ,"CTR72_HSLVDS_TX_CTRL"              ,dbg_CTR72_HSLVDS_TX_CTRL            },
	{ 0xfd3001e0 ,N_FLD(dbg_CTR73_HSLVDS_TX_CTRL)            ,"CTR73_HSLVDS_TX_CTRL"              ,dbg_CTR73_HSLVDS_TX_CTRL            },
	{ 0xfd3001e4 ,N_FLD(dbg_CTR74_HSLVDS_TX_CTRL)            ,"CTR74_HSLVDS_TX_CTRL"              ,dbg_CTR74_HSLVDS_TX_CTRL            },
	{ 0xfd3001e8 ,N_FLD(dbg_CTR75_HSLVDS_RX_CTRL)            ,"CTR75_HSLVDS_RX_CTRL"              ,dbg_CTR75_HSLVDS_RX_CTRL            },
	{ 0 , } // end marker
};

#endif
