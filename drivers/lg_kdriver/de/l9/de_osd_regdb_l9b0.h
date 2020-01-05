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

#ifndef _DBG_OSD_h
#define _DBG_OSD_h

/*------------------------------------
	0x5100 OSD0_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd0_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd0_double_h"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd0_double_w"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"osd0_manual_address"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"osd0_round"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"osd0_pure_ck"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd0_hdr_ptr_bmp_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd0_hdr_ptr_plte_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd0_hdr_color_key_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"osd0_hdr_wpl_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"osd0_hdr_global_alpha_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"osd0_hdr_format_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"osd0_hdr_depth_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"osd0_hdr_h_out_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd0_hdr_w_out_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"osd0_hdr_global_alpha_en_sel"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"osd0_hdr_pixel_order_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"osd0_hdr_h_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd0_hdr_w_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"osd0_hdr_ypos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"osd0_hdr_xpos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"osd0_hdr_color_key_en_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"osd0_ch_blue"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"osd0_ch_green"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"osd0_ch_red"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"osd0_ch_alpha"                   },
};

/*------------------------------------
	0x5104 OSD1_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd1_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd0_double_h"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd0_double_w"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"osd0_manual_address"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"osd1_round"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"osd1_pure_ck"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd1_hdr_ptr_bmp_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd1_hdr_ptr_plte_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd1_hdr_color_key_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"osd1_hdr_wpl_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"osd1_hdr_global_alpha_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"osd1_hdr_format_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"osd1_hdr_depth_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"osd1_hdr_h_out_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd1_hdr_w_out_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"osd1_hdr_global_alpha_en_sel"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"osd1_hdr_pixel_order_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"osd1_hdr_h_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd1_hdr_w_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"osd1_hdr_ypos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"osd1_hdr_xpos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"osd1_hdr_color_key_en_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"osd1_ch_blue"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"osd1_ch_green"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"osd1_ch_red"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"osd1_ch_alpha"                   },
};

/*------------------------------------
	0x5108 OSD2_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd2_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd0_double_h"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd0_double_w"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"osd0_manual_address"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"osd2_round"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"osd2_pure_ck"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd2_hdr_ptr_bmp_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd2_hdr_ptr_plte_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd2_hdr_color_key_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"osd2_hdr_wpl_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"osd2_hdr_global_alpha_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"osd2_hdr_format_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"osd2_hdr_depth_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"osd2_hdr_h_out_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd2_hdr_w_out_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"osd2_hdr_global_alpha_en_sel"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"osd2_hdr_pixel_order_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"osd2_hdr_h_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd2_hdr_w_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"osd2_hdr_ypos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"osd2_hdr_xpos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"osd2_hdr_color_key_en_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"osd2_ch_blue"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"osd2_ch_green"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"osd2_ch_red"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"osd2_ch_alpha"                   },
};

/*------------------------------------
	0x510c OSD_VERSION_DATE
------------------------------------*/
/* no field */

/*------------------------------------
	0x5110 OSD_DISP_SIZE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_DISP_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"disp_h"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"disp_w"                          },
};

/*------------------------------------
	0x5114 OSD_IRQ
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_IRQ[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"crsr_irq"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd2_irq"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd1_irq"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"osd0_irq"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"mixer_irq"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"crsr_irq_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"osd2_irq_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"osd1_irq_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"osd0_irq_en"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"mixer_irq_en"                    },
};

/*------------------------------------
	0x5118 OSD0_BASE_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_BASE_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_base_addr"                  },
};

/*------------------------------------
	0x511c OSD0_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_hdr_color_key_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd0_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd0_hdr_ypos"                   },
};

/*------------------------------------
	0x5120 OSD0_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd0_hdr_w_mem"                  },
};

/*------------------------------------
	0x5124 OSD0_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_hdr_h_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd0_hdr_w_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd0_hdr_pixel_order"            },
};

/*------------------------------------
	0x5128 OSD0_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"osd0_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd0_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"osd0_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd0_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd0_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x512c OSD0_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_hdr_color_key"              },
};

/*------------------------------------
	0x5130 OSD0_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_hdr_ptr_plte"               },
};

/*------------------------------------
	0x5134 OSD0_HDR6
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x5138 OSD0_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"osd0_lfsr_seed"                  },
};

/*------------------------------------
	0x513c OSD1_BASE_ADDR
------------------------------------*/
/* no field */

/*------------------------------------
	0x5140 OSD1_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_hdr_color_key_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd1_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd1_hdr_ypos"                   },
};

/*------------------------------------
	0x5144 OSD1_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd1_hdr_w_mem"                  },
};

/*------------------------------------
	0x5148 OSD1_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_hdr_h_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd1_hdr_w_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd1_hdr_pixel_order"            },
};

/*------------------------------------
	0x514c OSD1_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"osd1_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"osd1_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd1_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd1_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x5150 OSD1_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_hdr_color_key"              },
};

/*------------------------------------
	0x5154 OSD1_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_hdr_ptr_plte"               },
};

/*------------------------------------
	0x5158 OSD1_HDR6
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x515c OSD1_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"osd1_lfsr_seed"                  },
};

/*------------------------------------
	0x5160 OSD2_BASE_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_BASE_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_base_addr"                  },
};

/*------------------------------------
	0x5164 OSD2_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_hdr_color_key_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd2_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd2_hdr_ypos"                   },
};

/*------------------------------------
	0x5168 OSD2_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd2_hdr_w_mem"                  },
};

/*------------------------------------
	0x516c OSD2_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_hdr_h_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd2_hdr_w_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd2_hdr_pixel_order"            },
};

/*------------------------------------
	0x5170 OSD2_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"osd2_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd2_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"osd2_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd2_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd2_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x5174 OSD2_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_hdr_color_key"              },
};

/*------------------------------------
	0x5178 OSD2_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_hdr_ptr_plte"               },
};

/*------------------------------------
	0x517c OSD2_HDR6
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x5180 OSD2_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"osd2_lfsr_seed"                  },
};

/*------------------------------------
	0x5184 OSD0_SC_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_SC_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd0_sc_vs_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd0_sc_hs_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"osd0_sc_bc_sa"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd0_sc_bnd_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"osd0_sc_h2v_path"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"osd0_sc_h_phase_off"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd0_sc_buf_mode_en"             },
};

/*------------------------------------
	0x5188 OSD1_SC_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_SC_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd1_sc_vs_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd1_sc_hs_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"osd1_sc_bc_sa"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd1_sc_bnd_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"osd1_sc_h2v_path"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"osd1_sc_h_phase_off"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd1_sc_buf_mode_en"             },
};

/*------------------------------------
	0x518c OSD2_SC_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_SC_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd2_sc_vs_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd2_sc_hs_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"osd2_sc_bc_sa"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd2_sc_bnd_mode"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"osd2_sc_h2v_path"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"osd2_sc_h_phase_off"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd2_sc_buf_mode_en"             },
};

/*------------------------------------
	0x5190 OSD_SC_V_PHASE_OFF
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_SC_V_PHASE_OFF[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"osd_sc_v_phase_off"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"osd_sc_v_phase_off_index"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd_sc_v_phase_off_rw"           },
};

/*------------------------------------
	0x51a4 OSD0_END_CONV
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_END_CONV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd0_bbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd0_bqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd0_bhws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd0_pbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd0_pqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"osd0_phws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd0_hbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd0_hqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd0_hhws"                       },
};

/*------------------------------------
	0x51a8 OSD1_END_CONV
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_END_CONV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd1_bbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd1_bqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd1_bhws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd1_pbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd1_pqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"osd1_phws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd1_hbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd1_hqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd1_hhws"                       },
};

/*------------------------------------
	0x51ac OSD2_END_CONV
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_END_CONV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd2_bbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd2_bqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd2_bhws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd2_pbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd2_pqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"osd2_phws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd2_hbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd2_hqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd2_hhws"                       },
};

/*------------------------------------
	0x51b4 CRSR_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"crsr_en"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"osd0_double_h"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"osd0_double_w"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"crsr_manual_address"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"crsr_round"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"crsr_pure_color_key"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"crsr_hdr_ptr_bmp_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"crsr_hdr_ptr_plte_sel"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"crsr_hdr_color_key_sel"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"crsr_hdr_wpl_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"crsr_hdr_global_alpha_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"crsr_hdr_format_sel"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"crsr_hdr_depth_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"crsr_hdr_global_alpha_en_sel"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"crsr_hdr_pixel_order_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"crsr_hdr_h_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"crsr_hdr_w_mem_sel"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,21 ,21 ,"crsr_hdr_ypos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,22 ,"crsr_hdr_xpos_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,23 ,"crsr_hdr_color_key_en_sel"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,24 ,"crsr_ch_blue"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,26 ,"crsr_ch_green"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,28 ,"crsr_ch_red"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,30 ,"crsr_ch_alpha"                   },
};

/*------------------------------------
	0x51b8 CRSR_BASE_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_BASE_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_base_addr"                  },
};

/*------------------------------------
	0x51bc CRSR_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"crsr_hdr_ypos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"crsr_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"crsr_hdr_pos_load"               },
};

/*------------------------------------
	0x51c0 CRSR_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"crsr_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"crsr_hdr_pixel_order"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"crsr_hdr_w_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"crsr_hdr_color_key_en"           },
};

/*------------------------------------
	0x51c4 CRSR_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"crsr_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"crsr_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"crsr_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"crsr_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"crsr_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x51c8 CRSR_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_hdr_color_key"              },
};

/*------------------------------------
	0x51cc CRSR_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_hdr_ptr_plte"               },
};

/*------------------------------------
	0x51d0 CRSR_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x51d4 CRSR_END_CONV
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_END_CONV[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"crsr_bbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"crsr_bqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"crsr_bhws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"crsr_pbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"crsr_pqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"crsr_phws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"crsr_hbs"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"crsr_hqws"                       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"crsr_hhws"                       },
};

/*------------------------------------
	0x51d8 CRSR_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"crsr_lfsr_seed"                  },
};

/*------------------------------------
	0x51f0 OSD_LAYER_MUX_LEFT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_LAYER_MUX_LEFT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"layer_mux_3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"layer_mux_2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"layer_mux_1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"layer_mux_0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"video_layer_alpha"               },
};

/*------------------------------------
	0x51f4 OSD_LAYER_MUX_RIGHT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_LAYER_MUX_RIGHT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"layer_mux_3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"layer_mux_2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"layer_mux_1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"layer_mux_0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"video_layer_alpha"               },
};

/*------------------------------------
	0x51f8 OSD_MIXER_OUT_LEFT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_MIXER_OUT_LEFT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"mixer_out_blue"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"mixer_out_green"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"mixer_out_red"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"mixer_mask_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mixer_out_en"                    },
};

/*------------------------------------
	0x51fc OSD_MIXER_OUT_RIGHT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_MIXER_OUT_RIGHT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"mixer_out_blue"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"mixer_out_green"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"mixer_out_red"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"mixer_mask_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mixer_out_en"                    },
};

/*------------------------------------
	0x5200 OSD0_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd0_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd0_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd0_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd0_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd0_3d_mode_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd0_3d_mode_dual"               },
};

/*------------------------------------
	0x5204 OSD0_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd0_rb_disparity_value"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd0_rb_disparity_sign_b08"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd0_lt_disparity_value"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd0_rb_disparity_sign_b24"      },
};

/*------------------------------------
	0x5208 OSD0_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_left_3d_blank"              },
};

/*------------------------------------
	0x520c OSD0_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_right_3d_blank"             },
};

/*------------------------------------
	0x5210 OSD0_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_tb_line_space"              },
};

/*------------------------------------
	0x5220 OSD1_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd1_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd1_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd1_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd1_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd1_3d_mode_sel"                },
};

/*------------------------------------
	0x5224 OSD1_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd1_right_disparity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd1_right_disparity_sign"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_left_disparity"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd1_left_disparity_sign"        },
};

/*------------------------------------
	0x5228 OSD1_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_left_3d_blank"              },
};

/*------------------------------------
	0x522c OSD1_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_right_3d_blank"             },
};

/*------------------------------------
	0x5230 OSD1_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_tb_line_space"              },
};

/*------------------------------------
	0x5240 OSD2_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd2_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd2_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd2_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd2_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd2_3d_mode_sel"                },
};

/*------------------------------------
	0x5244 OSD2_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd2_right_disparity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd2_right_disparity_sign"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd2_left_disparity"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd2_left_disparity_sign"        },
};

/*------------------------------------
	0x5248 OSD2_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_left_3d_blank"              },
};

/*------------------------------------
	0x524c OSD2_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_right_3d_blank"             },
};

/*------------------------------------
	0x5250 OSD2_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_tb_line_space"              },
};

/*------------------------------------
	0x5260 OSD3_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd3_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd3_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd3_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd3_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd3_3d_mode_sel"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd3_3d_mode_dual"               },
};

/*------------------------------------
	0x5264 OSD3_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd3_right_disparity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd3_right_disparity_sign"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd3_left_disparity"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd3_left_disparity_sign"        },
};

/*------------------------------------
	0x5268 OSD3_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd3_left_3d_blank"              },
};

/*------------------------------------
	0x526c OSD3_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd3_right_3d_blank"             },
};

/*------------------------------------
	0x5270 OSD3_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd3_tb_line_space"              },
};

/*------------------------------------
	0x52a0 OSD_FRC_IF_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_IF_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"osd_frc_if_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"osd_frc_layer_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"osd_frc_lr_sel"                  },
};

/*------------------------------------
	0x52a4 OSD_FRC_HDR_0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"osd_frc_hdr_0"                   },
};

/*------------------------------------
	0x52a8 OSD_FRC_HDR_1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"osd_frc_hdr_1"                   },
};

/*------------------------------------
	0x52ac OSD_FRC_HDR_2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"osd_frc_hdr_2"                   },
};

/*------------------------------------
	0x52b0 OSD_FRC_HDR_3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd_frc_hdr_3"                   },
};

/*------------------------------------
	0x52b4 OSD_FRC_HDR_4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"osd_frc_hdr_4"                   },
};

/*------------------------------------
	0x52b8 OSD_FRC_HDR_5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"osd_frc_hdr_5"                   },
};

/*------------------------------------
	0x52c0 OSD_FRC_ABLEND_TH_L
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_ABLEND_TH_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd3_external_blend_th_l"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"osd2_external_blend_th_l"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_external_blend_th_l"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"osd0_external_blend_th_l"        },
};

/*------------------------------------
	0x52c4 OSD_FRC_ABLEND_TH_R
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_ABLEND_TH_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd3_external_blend_th_r"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"osd2_external_blend_th_r"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_external_blend_th_r"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"osd0_external_blend_th_r"        },
};

/*------------------------------------
	0x52d4 OSD_PALETTE_SEL
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_PALETTE_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd_palette_sel"                 },
};

/*------------------------------------
	0x52d8 OSD_LEFT_AWB
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_LEFT_AWB[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"crsr_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"crsr_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"crsr_awb_red"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd2_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd2_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd2_awb_red"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd1_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"osd1_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"osd1_awb_red"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd0_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"osd0_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"osd0_awb_red"                    },
};

/*------------------------------------
	0x52dc OSD_RIGHT_AWB
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_RIGHT_AWB[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"crsr_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"crsr_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"crsr_awb_red"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd2_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"osd2_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd2_awb_red"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd1_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"osd1_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"osd1_awb_red"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd0_awb_blue"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,25 ,25 ,"osd0_awb_green"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,26 ,"osd0_awb_red"                    },
};

/*------------------------------------
	0x52e4 OSD_L_MIXER_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_L_MIXER_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mixer_process_line_l"            },
};

/*------------------------------------
	0x52e8 OSD_R_MIXER_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_R_MIXER_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mixer_process_line_r"            },
};

/*------------------------------------
	0x52ec OSD_STATUS_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"osd_status_cfg"                  },
};

/*------------------------------------
	0x52f0 OSD_STATUS_0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd0_process_state"              },
};

/*------------------------------------
	0x52f4 OSD_STATUS_1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd1_process_state"              },
};

/*------------------------------------
	0x52f8 OSD_STATUS_2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd2_process_state"              },
};

/*------------------------------------
	0x52fc OSD_STATUS_3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd3_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd3_process_state"              },
};

DBG_REG_T gDbgRegOSD[] = {
	{ 0x5100 ,N_FLD(dbg_OSD0_CFG)                ,"OSD0_CFG"                  ,dbg_OSD0_CFG                },
	{ 0x5104 ,N_FLD(dbg_OSD1_CFG)                ,"OSD1_CFG"                  ,dbg_OSD1_CFG                },
	{ 0x5108 ,N_FLD(dbg_OSD2_CFG)                ,"OSD2_CFG"                  ,dbg_OSD2_CFG                },
	{ 0x510c ,0                                  ,"OSD_VERSION_DATE"          ,NULL                        },
	{ 0x5110 ,N_FLD(dbg_OSD_DISP_SIZE)           ,"OSD_DISP_SIZE"             ,dbg_OSD_DISP_SIZE           },
	{ 0x5114 ,N_FLD(dbg_OSD_IRQ)                 ,"OSD_IRQ"                   ,dbg_OSD_IRQ                 },
	{ 0x5118 ,N_FLD(dbg_OSD0_BASE_ADDR)          ,"OSD0_BASE_ADDR"            ,dbg_OSD0_BASE_ADDR          },
	{ 0x511c ,N_FLD(dbg_OSD0_HDR0)               ,"OSD0_HDR0"                 ,dbg_OSD0_HDR0               },
	{ 0x5120 ,N_FLD(dbg_OSD0_HDR1)               ,"OSD0_HDR1"                 ,dbg_OSD0_HDR1               },
	{ 0x5124 ,N_FLD(dbg_OSD0_HDR2)               ,"OSD0_HDR2"                 ,dbg_OSD0_HDR2               },
	{ 0x5128 ,N_FLD(dbg_OSD0_HDR3)               ,"OSD0_HDR3"                 ,dbg_OSD0_HDR3               },
	{ 0x512c ,N_FLD(dbg_OSD0_HDR4)               ,"OSD0_HDR4"                 ,dbg_OSD0_HDR4               },
	{ 0x5130 ,N_FLD(dbg_OSD0_HDR5)               ,"OSD0_HDR5"                 ,dbg_OSD0_HDR5               },
	{ 0x5134 ,N_FLD(dbg_OSD0_HDR6)               ,"OSD0_HDR6"                 ,dbg_OSD0_HDR6               },
	{ 0x5138 ,N_FLD(dbg_OSD0_LFSR_SEED)          ,"OSD0_LFSR_SEED"            ,dbg_OSD0_LFSR_SEED          },
	{ 0x513c ,0                                  ,"OSD1_BASE_ADDR"            ,NULL                        },
	{ 0x5140 ,N_FLD(dbg_OSD1_HDR0)               ,"OSD1_HDR0"                 ,dbg_OSD1_HDR0               },
	{ 0x5144 ,N_FLD(dbg_OSD1_HDR1)               ,"OSD1_HDR1"                 ,dbg_OSD1_HDR1               },
	{ 0x5148 ,N_FLD(dbg_OSD1_HDR2)               ,"OSD1_HDR2"                 ,dbg_OSD1_HDR2               },
	{ 0x514c ,N_FLD(dbg_OSD1_HDR3)               ,"OSD1_HDR3"                 ,dbg_OSD1_HDR3               },
	{ 0x5150 ,N_FLD(dbg_OSD1_HDR4)               ,"OSD1_HDR4"                 ,dbg_OSD1_HDR4               },
	{ 0x5154 ,N_FLD(dbg_OSD1_HDR5)               ,"OSD1_HDR5"                 ,dbg_OSD1_HDR5               },
	{ 0x5158 ,N_FLD(dbg_OSD1_HDR6)               ,"OSD1_HDR6"                 ,dbg_OSD1_HDR6               },
	{ 0x515c ,N_FLD(dbg_OSD1_LFSR_SEED)          ,"OSD1_LFSR_SEED"            ,dbg_OSD1_LFSR_SEED          },
	{ 0x5160 ,N_FLD(dbg_OSD2_BASE_ADDR)          ,"OSD2_BASE_ADDR"            ,dbg_OSD2_BASE_ADDR          },
	{ 0x5164 ,N_FLD(dbg_OSD2_HDR0)               ,"OSD2_HDR0"                 ,dbg_OSD2_HDR0               },
	{ 0x5168 ,N_FLD(dbg_OSD2_HDR1)               ,"OSD2_HDR1"                 ,dbg_OSD2_HDR1               },
	{ 0x516c ,N_FLD(dbg_OSD2_HDR2)               ,"OSD2_HDR2"                 ,dbg_OSD2_HDR2               },
	{ 0x5170 ,N_FLD(dbg_OSD2_HDR3)               ,"OSD2_HDR3"                 ,dbg_OSD2_HDR3               },
	{ 0x5174 ,N_FLD(dbg_OSD2_HDR4)               ,"OSD2_HDR4"                 ,dbg_OSD2_HDR4               },
	{ 0x5178 ,N_FLD(dbg_OSD2_HDR5)               ,"OSD2_HDR5"                 ,dbg_OSD2_HDR5               },
	{ 0x517c ,N_FLD(dbg_OSD2_HDR6)               ,"OSD2_HDR6"                 ,dbg_OSD2_HDR6               },
	{ 0x5180 ,N_FLD(dbg_OSD2_LFSR_SEED)          ,"OSD2_LFSR_SEED"            ,dbg_OSD2_LFSR_SEED          },
	{ 0x5184 ,N_FLD(dbg_OSD0_SC_CFG)             ,"OSD0_SC_CFG"               ,dbg_OSD0_SC_CFG             },
	{ 0x5188 ,N_FLD(dbg_OSD1_SC_CFG)             ,"OSD1_SC_CFG"               ,dbg_OSD1_SC_CFG             },
	{ 0x518c ,N_FLD(dbg_OSD2_SC_CFG)             ,"OSD2_SC_CFG"               ,dbg_OSD2_SC_CFG             },
	{ 0x5190 ,N_FLD(dbg_OSD_SC_V_PHASE_OFF)      ,"OSD_SC_V_PHASE_OFF"        ,dbg_OSD_SC_V_PHASE_OFF      },
	{ 0x51a4 ,N_FLD(dbg_OSD0_END_CONV)           ,"OSD0_END_CONV"             ,dbg_OSD0_END_CONV           },
	{ 0x51a8 ,N_FLD(dbg_OSD1_END_CONV)           ,"OSD1_END_CONV"             ,dbg_OSD1_END_CONV           },
	{ 0x51ac ,N_FLD(dbg_OSD2_END_CONV)           ,"OSD2_END_CONV"             ,dbg_OSD2_END_CONV           },
	{ 0x51b4 ,N_FLD(dbg_CRSR_CFG)                ,"CRSR_CFG"                  ,dbg_CRSR_CFG                },
	{ 0x51b8 ,N_FLD(dbg_CRSR_BASE_ADDR)          ,"CRSR_BASE_ADDR"            ,dbg_CRSR_BASE_ADDR          },
	{ 0x51bc ,N_FLD(dbg_CRSR_HDR0)               ,"CRSR_HDR0"                 ,dbg_CRSR_HDR0               },
	{ 0x51c0 ,N_FLD(dbg_CRSR_HDR1)               ,"CRSR_HDR1"                 ,dbg_CRSR_HDR1               },
	{ 0x51c4 ,N_FLD(dbg_CRSR_HDR2)               ,"CRSR_HDR2"                 ,dbg_CRSR_HDR2               },
	{ 0x51c8 ,N_FLD(dbg_CRSR_HDR3)               ,"CRSR_HDR3"                 ,dbg_CRSR_HDR3               },
	{ 0x51cc ,N_FLD(dbg_CRSR_HDR4)               ,"CRSR_HDR4"                 ,dbg_CRSR_HDR4               },
	{ 0x51d0 ,N_FLD(dbg_CRSR_HDR5)               ,"CRSR_HDR5"                 ,dbg_CRSR_HDR5               },
	{ 0x51d4 ,N_FLD(dbg_CRSR_END_CONV)           ,"CRSR_END_CONV"             ,dbg_CRSR_END_CONV           },
	{ 0x51d8 ,N_FLD(dbg_CRSR_LFSR_SEED)          ,"CRSR_LFSR_SEED"            ,dbg_CRSR_LFSR_SEED          },
	{ 0x51f0 ,N_FLD(dbg_OSD_LAYER_MUX_LEFT)      ,"OSD_LAYER_MUX_LEFT"        ,dbg_OSD_LAYER_MUX_LEFT      },
	{ 0x51f4 ,N_FLD(dbg_OSD_LAYER_MUX_RIGHT)     ,"OSD_LAYER_MUX_RIGHT"       ,dbg_OSD_LAYER_MUX_RIGHT     },
	{ 0x51f8 ,N_FLD(dbg_OSD_MIXER_OUT_LEFT)      ,"OSD_MIXER_OUT_LEFT"        ,dbg_OSD_MIXER_OUT_LEFT      },
	{ 0x51fc ,N_FLD(dbg_OSD_MIXER_OUT_RIGHT)     ,"OSD_MIXER_OUT_RIGHT"       ,dbg_OSD_MIXER_OUT_RIGHT     },
	{ 0x5200 ,N_FLD(dbg_OSD0_3D_PATH_MODE)       ,"OSD0_3D_PATH_MODE"         ,dbg_OSD0_3D_PATH_MODE       },
	{ 0x5204 ,N_FLD(dbg_OSD0_3D_DISPARITY)       ,"OSD0_3D_DISPARITY"         ,dbg_OSD0_3D_DISPARITY       },
	{ 0x5208 ,N_FLD(dbg_OSD0_LEFT_3D_BLANK)      ,"OSD0_LEFT_3D_BLANK"        ,dbg_OSD0_LEFT_3D_BLANK      },
	{ 0x520c ,N_FLD(dbg_OSD0_RIGHT_3D_BLANK)     ,"OSD0_RIGHT_3D_BLANK"       ,dbg_OSD0_RIGHT_3D_BLANK     },
	{ 0x5210 ,N_FLD(dbg_OSD0_TB_SPACE)           ,"OSD0_TB_SPACE"             ,dbg_OSD0_TB_SPACE           },
	{ 0x5220 ,N_FLD(dbg_OSD1_3D_PATH_MODE)       ,"OSD1_3D_PATH_MODE"         ,dbg_OSD1_3D_PATH_MODE       },
	{ 0x5224 ,N_FLD(dbg_OSD1_3D_DISPARITY)       ,"OSD1_3D_DISPARITY"         ,dbg_OSD1_3D_DISPARITY       },
	{ 0x5228 ,N_FLD(dbg_OSD1_LEFT_3D_BLANK)      ,"OSD1_LEFT_3D_BLANK"        ,dbg_OSD1_LEFT_3D_BLANK      },
	{ 0x522c ,N_FLD(dbg_OSD1_RIGHT_3D_BLANK)     ,"OSD1_RIGHT_3D_BLANK"       ,dbg_OSD1_RIGHT_3D_BLANK     },
	{ 0x5230 ,N_FLD(dbg_OSD1_TB_SPACE)           ,"OSD1_TB_SPACE"             ,dbg_OSD1_TB_SPACE           },
	{ 0x5240 ,N_FLD(dbg_OSD2_3D_PATH_MODE)       ,"OSD2_3D_PATH_MODE"         ,dbg_OSD2_3D_PATH_MODE       },
	{ 0x5244 ,N_FLD(dbg_OSD2_3D_DISPARITY)       ,"OSD2_3D_DISPARITY"         ,dbg_OSD2_3D_DISPARITY       },
	{ 0x5248 ,N_FLD(dbg_OSD2_LEFT_3D_BLANK)      ,"OSD2_LEFT_3D_BLANK"        ,dbg_OSD2_LEFT_3D_BLANK      },
	{ 0x524c ,N_FLD(dbg_OSD2_RIGHT_3D_BLANK)     ,"OSD2_RIGHT_3D_BLANK"       ,dbg_OSD2_RIGHT_3D_BLANK     },
	{ 0x5250 ,N_FLD(dbg_OSD2_TB_SPACE)           ,"OSD2_TB_SPACE"             ,dbg_OSD2_TB_SPACE           },
	{ 0x5260 ,N_FLD(dbg_OSD3_3D_PATH_MODE)       ,"OSD3_3D_PATH_MODE"         ,dbg_OSD3_3D_PATH_MODE       },
	{ 0x5264 ,N_FLD(dbg_OSD3_3D_DISPARITY)       ,"OSD3_3D_DISPARITY"         ,dbg_OSD3_3D_DISPARITY       },
	{ 0x5268 ,N_FLD(dbg_OSD3_LEFT_3D_BLANK)      ,"OSD3_LEFT_3D_BLANK"        ,dbg_OSD3_LEFT_3D_BLANK      },
	{ 0x526c ,N_FLD(dbg_OSD3_RIGHT_3D_BLANK)     ,"OSD3_RIGHT_3D_BLANK"       ,dbg_OSD3_RIGHT_3D_BLANK     },
	{ 0x5270 ,N_FLD(dbg_OSD3_TB_SPACE)           ,"OSD3_TB_SPACE"             ,dbg_OSD3_TB_SPACE           },
	{ 0x52a0 ,N_FLD(dbg_OSD_FRC_IF_CFG)          ,"OSD_FRC_IF_CFG"            ,dbg_OSD_FRC_IF_CFG          },
	{ 0x52a4 ,N_FLD(dbg_OSD_FRC_HDR_0)           ,"OSD_FRC_HDR_0"             ,dbg_OSD_FRC_HDR_0           },
	{ 0x52a8 ,N_FLD(dbg_OSD_FRC_HDR_1)           ,"OSD_FRC_HDR_1"             ,dbg_OSD_FRC_HDR_1           },
	{ 0x52ac ,N_FLD(dbg_OSD_FRC_HDR_2)           ,"OSD_FRC_HDR_2"             ,dbg_OSD_FRC_HDR_2           },
	{ 0x52b0 ,N_FLD(dbg_OSD_FRC_HDR_3)           ,"OSD_FRC_HDR_3"             ,dbg_OSD_FRC_HDR_3           },
	{ 0x52b4 ,N_FLD(dbg_OSD_FRC_HDR_4)           ,"OSD_FRC_HDR_4"             ,dbg_OSD_FRC_HDR_4           },
	{ 0x52b8 ,N_FLD(dbg_OSD_FRC_HDR_5)           ,"OSD_FRC_HDR_5"             ,dbg_OSD_FRC_HDR_5           },
	{ 0x52c0 ,N_FLD(dbg_OSD_FRC_ABLEND_TH_L)     ,"OSD_FRC_ABLEND_TH_L"       ,dbg_OSD_FRC_ABLEND_TH_L     },
	{ 0x52c4 ,N_FLD(dbg_OSD_FRC_ABLEND_TH_R)     ,"OSD_FRC_ABLEND_TH_R"       ,dbg_OSD_FRC_ABLEND_TH_R     },
	{ 0x52d4 ,N_FLD(dbg_OSD_PALETTE_SEL)         ,"OSD_PALETTE_SEL"           ,dbg_OSD_PALETTE_SEL         },
	{ 0x52d8 ,N_FLD(dbg_OSD_LEFT_AWB)            ,"OSD_LEFT_AWB"              ,dbg_OSD_LEFT_AWB            },
	{ 0x52dc ,N_FLD(dbg_OSD_RIGHT_AWB)           ,"OSD_RIGHT_AWB"             ,dbg_OSD_RIGHT_AWB           },
	{ 0x52e4 ,N_FLD(dbg_OSD_L_MIXER_STATUS)      ,"OSD_L_MIXER_STATUS"        ,dbg_OSD_L_MIXER_STATUS      },
	{ 0x52e8 ,N_FLD(dbg_OSD_R_MIXER_STATUS)      ,"OSD_R_MIXER_STATUS"        ,dbg_OSD_R_MIXER_STATUS      },
	{ 0x52ec ,N_FLD(dbg_OSD_STATUS_CFG)          ,"OSD_STATUS_CFG"            ,dbg_OSD_STATUS_CFG          },
	{ 0x52f0 ,N_FLD(dbg_OSD_STATUS_0)            ,"OSD_STATUS_0"              ,dbg_OSD_STATUS_0            },
	{ 0x52f4 ,N_FLD(dbg_OSD_STATUS_1)            ,"OSD_STATUS_1"              ,dbg_OSD_STATUS_1            },
	{ 0x52f8 ,N_FLD(dbg_OSD_STATUS_2)            ,"OSD_STATUS_2"              ,dbg_OSD_STATUS_2            },
	{ 0x52fc ,N_FLD(dbg_OSD_STATUS_3)            ,"OSD_STATUS_3"              ,dbg_OSD_STATUS_3            },
	{ 0 , } // end marker
};

#endif
