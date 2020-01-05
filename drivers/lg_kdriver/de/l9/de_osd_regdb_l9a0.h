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
	0x3a00 OSD0_CFG
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
	0x3a04 OSD1_CFG
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
	0x3a08 OSD2_CFG
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
	0x3a0c OSD_VERSION_DATE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_VERSION_DATE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"version_date"                    },
};

/*------------------------------------
	0x3a10 OSD_DISP_SIZE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_DISP_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"disp_h"                          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"disp_w"                          },
};

/*------------------------------------
	0x3a14 OSD_IRQ
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
	0x3a18 OSD0_BASE_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_BASE_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_base_addr"                  },
};

/*------------------------------------
	0x3a1c OSD0_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_hdr_color_key_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd0_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd0_hdr_ypos"                   },
};

/*------------------------------------
	0x3a20 OSD0_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd0_hdr_w_mem"                  },
};

/*------------------------------------
	0x3a24 OSD0_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_hdr_h_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd0_hdr_w_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd0_hdr_pixel_order"            },
};

/*------------------------------------
	0x3a28 OSD0_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"osd0_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd0_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"osd0_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd0_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd0_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x3a2c OSD0_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_hdr_color_key"              },
};

/*------------------------------------
	0x3a30 OSD0_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_hdr_ptr_plte"               },
};

/*------------------------------------
	0x3a34 OSD0_HDR6
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_HDR6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x3a38 OSD0_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"osd0_lfsr_seed"                  },
};

/*------------------------------------
	0x3a3c OSD1_BASE_ADDR
------------------------------------*/
/* no field */

/*------------------------------------
	0x3a40 OSD1_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_hdr_color_key_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd1_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd1_hdr_ypos"                   },
};

/*------------------------------------
	0x3a44 OSD1_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd1_hdr_w_mem"                  },
};

/*------------------------------------
	0x3a48 OSD1_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_hdr_h_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd1_hdr_w_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd1_hdr_pixel_order"            },
};

/*------------------------------------
	0x3a4c OSD1_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"osd1_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"osd1_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd1_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd1_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x3a50 OSD1_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_hdr_color_key"              },
};

/*------------------------------------
	0x3a54 OSD1_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_hdr_ptr_plte"               },
};

/*------------------------------------
	0x3a58 OSD1_HDR6
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_HDR6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x3a5c OSD1_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"osd1_lfsr_seed"                  },
};

/*------------------------------------
	0x3a60 OSD2_BASE_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_BASE_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_base_addr"                  },
};

/*------------------------------------
	0x3a64 OSD2_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_hdr_color_key_en"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd2_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd2_hdr_ypos"                   },
};

/*------------------------------------
	0x3a68 OSD2_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd2_hdr_w_mem"                  },
};

/*------------------------------------
	0x3a6c OSD2_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_hdr_h_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"osd2_hdr_w_out"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd2_hdr_pixel_order"            },
};

/*------------------------------------
	0x3a70 OSD2_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"osd2_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd2_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"osd2_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd2_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd2_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x3a74 OSD2_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_hdr_color_key"              },
};

/*------------------------------------
	0x3a78 OSD2_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_hdr_ptr_plte"               },
};

/*------------------------------------
	0x3a7c OSD2_HDR6
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_HDR6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x3a80 OSD2_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"osd2_lfsr_seed"                  },
};

/*------------------------------------
	0x3a84 OSD0_SC_CFG
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
	0x3a88 OSD1_SC_CFG
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
	0x3a8c OSD2_SC_CFG
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
	0x3a90 OSD_SC_V_PHASE_OFF
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_SC_V_PHASE_OFF[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"osd_sc_v_phase_off"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"osd_sc_v_phase_off_index"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"osd_sc_v_phase_off_rw"           },
};

/*------------------------------------
	0x3a94 OSD0_CSC_CTRL
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_CSC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"osd0_csc_data"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"osd0_csc_rw_n"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd0_csc_bypass"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd0_csc_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"osd0_csc_out_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd0_csc_in_ctrl"                },
};

/*------------------------------------
	0x3a98 OSD1_CSC_CTRL
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_CSC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"osd1_csc_data"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"osd1_csc_rw_n"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd1_csc_bypass"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd1_csc_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"osd1_csc_out_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd1_csc_in_ctrl"                },
};

/*------------------------------------
	0x3a9c OSD2_CSC_CTRL
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_CSC_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,0  ,"osd2_csc_data"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"osd2_csc_rw_n"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd2_csc_bypass"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd2_csc_sel"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"osd2_csc_out_ctrl"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"osd2_csc_in_ctrl"                },
};

/*------------------------------------
	0x3aa4 OSD0_END_CONV
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
	0x3aa8 OSD1_END_CONV
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
	0x3aac OSD2_END_CONV
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
	0x3ab4 CRSR_CFG
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
	0x3ab8 CRSR_BASE_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_BASE_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_base_addr"                  },
};

/*------------------------------------
	0x3abc CRSR_HDR0
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"crsr_hdr_ypos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"crsr_hdr_xpos"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"crsr_hdr_pos_load"               },
};

/*------------------------------------
	0x3ac0 CRSR_HDR1
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"crsr_hdr_h_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"crsr_hdr_pixel_order"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,16 ,"crsr_hdr_w_mem"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"crsr_hdr_color_key_en"           },
};

/*------------------------------------
	0x3ac4 CRSR_HDR2
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"crsr_hdr_wpl"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"crsr_hdr_global_alpha"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"crsr_hdr_format"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"crsr_hdr_depth"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"crsr_hdr_global_alpha_en"        },
};

/*------------------------------------
	0x3ac8 CRSR_HDR3
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_hdr_color_key"              },
};

/*------------------------------------
	0x3acc CRSR_HDR4
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_hdr_ptr_plte"               },
};

/*------------------------------------
	0x3ad0 CRSR_HDR5
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_HDR5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"crsr_hdr_ptr_bmp"                },
};

/*------------------------------------
	0x3ad4 CRSR_END_CONV
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
	0x3ad8 CRSR_LFSR_SEED
------------------------------------*/
const DBG_REG_FIELD_T dbg_CRSR_LFSR_SEED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,0  ,"crsr_lfsr_seed"                  },
};

/*------------------------------------
	0x3af0 OSD_LAYER_MUX_LEFT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_LAYER_MUX_LEFT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"layer_mux_3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"layer_mux_2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"layer_mux_1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"layer_mux_0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"video_layer_alpha"               },
};

/*------------------------------------
	0x3af4 OSD_LAYER_MUX_RIGHT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_LAYER_MUX_RIGHT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"layer_mux_3"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"layer_mux_2"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"layer_mux_1"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"layer_mux_0"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"video_layer_alpha"               },
};

/*------------------------------------
	0x3af8 OSD_MIXER_OUT_LEFT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_MIXER_OUT_LEFT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"mixer_out_blue"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"mixer_out_green"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"mixer_out_red"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"mixer_mask_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mixer_out_en"                    },
};

/*------------------------------------
	0x3afc OSD_MIXER_OUT_RIGHT
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_MIXER_OUT_RIGHT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,0  ,"mixer_out_blue"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,10 ,"mixer_out_green"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,20 ,"mixer_out_red"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"mixer_mask_en"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"mixer_out_en"                    },
};

/*------------------------------------
	0x3b00 OSD0_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd0_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd0_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd0_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd0_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd0_3d_mode_sel"                },
};

/*------------------------------------
	0x3b04 OSD0_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd0_right_disparity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd0_right_disparity_sign"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd0_left_disparity"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd0_left_disparity_sign"        },
};

/*------------------------------------
	0x3b08 OSD0_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_left_3d_blank"              },
};

/*------------------------------------
	0x3b0c OSD0_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd0_right_3d_blank"             },
};

/*------------------------------------
	0x3b10 OSD0_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD0_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_tb_line_space"              },
};

/*------------------------------------
	0x3b20 OSD1_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd1_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd1_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd1_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd1_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd1_3d_mode_sel"                },
};

/*------------------------------------
	0x3b24 OSD1_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd1_right_disparity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd1_right_disparity_sign"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_left_disparity"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd1_left_disparity_sign"        },
};

/*------------------------------------
	0x3b28 OSD1_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_left_3d_blank"              },
};

/*------------------------------------
	0x3b2c OSD1_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd1_right_3d_blank"             },
};

/*------------------------------------
	0x3b30 OSD1_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD1_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_tb_line_space"              },
};

/*------------------------------------
	0x3b40 OSD2_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd2_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd2_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd2_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd2_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd2_3d_mode_sel"                },
};

/*------------------------------------
	0x3b44 OSD2_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd2_right_disparity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd2_right_disparity_sign"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd2_left_disparity"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd2_left_disparity_sign"        },
};

/*------------------------------------
	0x3b48 OSD2_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_left_3d_blank"              },
};

/*------------------------------------
	0x3b4c OSD2_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd2_right_3d_blank"             },
};

/*------------------------------------
	0x3b50 OSD2_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD2_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_tb_line_space"              },
};

/*------------------------------------
	0x3b60 OSD3_3D_PATH_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_3D_PATH_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd3_path_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"osd3_path_buf_half"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"osd3_path_buf_repeat"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"osd3_3d_en"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"osd3_3d_mode_sel"                },
};

/*------------------------------------
	0x3b64 OSD3_3D_DISPARITY
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_3D_DISPARITY[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd3_right_disparity"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"osd3_right_disparity_sign"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd3_left_disparity"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"osd3_left_disparity_sign"        },
};

/*------------------------------------
	0x3b68 OSD3_LEFT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_LEFT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd3_left_3d_blank"              },
};

/*------------------------------------
	0x3b6c OSD3_RIGHT_3D_BLANK
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_RIGHT_3D_BLANK[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"osd3_right_3d_blank"             },
};

/*------------------------------------
	0x3b70 OSD3_TB_SPACE
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD3_TB_SPACE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd3_tb_line_space"              },
};

/*------------------------------------
	0x3ba0 OSD_FRC_IF_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_IF_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"osd_frc_layer_sel"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"osd_frc_lr_sel"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"osd_frc_dither_en"               },
};

/*------------------------------------
	0x3ba4 OSD_FRC_HDR_0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"osd_frc_hdr_format"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"osd_frc_hdr_po"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"osd_frc_lr"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"osd_frc_3d"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd_frc_hdr_code"                },
};

/*------------------------------------
	0x3ba8 OSD_FRC_HDR_1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"osd_frc_hdr_bmp_height"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"osd_frc_hdr_bmp_width"           },
};

/*------------------------------------
	0x3bac OSD_FRC_HDR_2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd_frc_hdr_global_alpha"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"osd_frc_hdr_pe"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"osd_frc_hdr_ge"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"osd_frc_hdr_ce"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"osd_frc_hdr_ou"                  },
};

/*------------------------------------
	0x3bb0 OSD_FRC_HDR_3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd_frc_hdr_ck_b"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"osd_frc_hdr_ck_g"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd_frc_hdr_ck_r"                },
};

/*------------------------------------
	0x3bb4 OSD_FRC_HDR_4
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"osd_frc_hdr_yoffset"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"osd_frc_hdr_xoffset"             },
};

/*------------------------------------
	0x3bb8 OSD_FRC_HDR_5
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_HDR_5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"osd_frc_hdr_disp_height"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"osd_frc_hdr_disp_width"          },
};

/*------------------------------------
	0x3bc0 OSD_FRC_ABLEND_TH_L
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_ABLEND_TH_L[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd3_external_blend_th_l"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"osd2_external_blend_th_l"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_external_blend_th_l"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"osd0_external_blend_th_l"        },
};

/*------------------------------------
	0x3bc4 OSD_FRC_ABLEND_TH_R
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_FRC_ABLEND_TH_R[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"osd3_external_blend_th_r"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"osd2_external_blend_th_r"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"osd1_external_blend_th_r"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"osd0_external_blend_th_r"        },
};

/*------------------------------------
	0x3bd0 OSD_DDR_ADDRESSING
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_DDR_ADDRESSING[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"osd_layer_sel"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"op_mode"                         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,9  ,"osd_ddr_sel_bmp"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,17 ,"osd_ddr_sel_plt"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,25 ,"osd_ddr_sel_hdr"                 },
};

/*------------------------------------
	0x3bd8 OSD_LEFT_AWB
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
	0x3bdc OSD_RIGHT_AWB
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
	0x3be4 OSD_L_MIXER_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_L_MIXER_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mixer_process_line_l"            },
};

/*------------------------------------
	0x3be8 OSD_R_MIXER_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_R_MIXER_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"mixer_process_line_r"            },
};

/*------------------------------------
	0x3bec OSD_STATUS_CFG
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_CFG[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"osd_status_cfg"                  },
};

/*------------------------------------
	0x3bf0 OSD_STATUS_0
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd0_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd0_process_state"              },
};

/*------------------------------------
	0x3bf4 OSD_STATUS_1
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd1_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd1_process_state"              },
};

/*------------------------------------
	0x3bf8 OSD_STATUS_2
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd2_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd2_process_state"              },
};

/*------------------------------------
	0x3bfc OSD_STATUS_3
------------------------------------*/
const DBG_REG_FIELD_T dbg_OSD_STATUS_3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"osd3_process_line"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"osd3_process_state"              },
};

DBG_REG_T gDbgRegOSD[] = {
	{ 0x3a00 ,N_FLD(dbg_OSD0_CFG)                ,"OSD0_CFG"                  ,dbg_OSD0_CFG                },
	{ 0x3a04 ,N_FLD(dbg_OSD1_CFG)                ,"OSD1_CFG"                  ,dbg_OSD1_CFG                },
	{ 0x3a08 ,N_FLD(dbg_OSD2_CFG)                ,"OSD2_CFG"                  ,dbg_OSD2_CFG                },
	{ 0x3a0c ,N_FLD(dbg_OSD_VERSION_DATE)        ,"OSD_VERSION_DATE"          ,dbg_OSD_VERSION_DATE        },
	{ 0x3a10 ,N_FLD(dbg_OSD_DISP_SIZE)           ,"OSD_DISP_SIZE"             ,dbg_OSD_DISP_SIZE           },
	{ 0x3a14 ,N_FLD(dbg_OSD_IRQ)                 ,"OSD_IRQ"                   ,dbg_OSD_IRQ                 },
	{ 0x3a18 ,N_FLD(dbg_OSD0_BASE_ADDR)          ,"OSD0_BASE_ADDR"            ,dbg_OSD0_BASE_ADDR          },
	{ 0x3a1c ,N_FLD(dbg_OSD0_HDR0)               ,"OSD0_HDR0"                 ,dbg_OSD0_HDR0               },
	{ 0x3a20 ,N_FLD(dbg_OSD0_HDR1)               ,"OSD0_HDR1"                 ,dbg_OSD0_HDR1               },
	{ 0x3a24 ,N_FLD(dbg_OSD0_HDR2)               ,"OSD0_HDR2"                 ,dbg_OSD0_HDR2               },
	{ 0x3a28 ,N_FLD(dbg_OSD0_HDR3)               ,"OSD0_HDR3"                 ,dbg_OSD0_HDR3               },
	{ 0x3a2c ,N_FLD(dbg_OSD0_HDR4)               ,"OSD0_HDR4"                 ,dbg_OSD0_HDR4               },
	{ 0x3a30 ,N_FLD(dbg_OSD0_HDR5)               ,"OSD0_HDR5"                 ,dbg_OSD0_HDR5               },
	{ 0x3a34 ,N_FLD(dbg_OSD0_HDR6)               ,"OSD0_HDR6"                 ,dbg_OSD0_HDR6               },
	{ 0x3a38 ,N_FLD(dbg_OSD0_LFSR_SEED)          ,"OSD0_LFSR_SEED"            ,dbg_OSD0_LFSR_SEED          },
	{ 0x3a3c ,0                                  ,"OSD1_BASE_ADDR"            ,NULL                        },
	{ 0x3a40 ,N_FLD(dbg_OSD1_HDR0)               ,"OSD1_HDR0"                 ,dbg_OSD1_HDR0               },
	{ 0x3a44 ,N_FLD(dbg_OSD1_HDR1)               ,"OSD1_HDR1"                 ,dbg_OSD1_HDR1               },
	{ 0x3a48 ,N_FLD(dbg_OSD1_HDR2)               ,"OSD1_HDR2"                 ,dbg_OSD1_HDR2               },
	{ 0x3a4c ,N_FLD(dbg_OSD1_HDR3)               ,"OSD1_HDR3"                 ,dbg_OSD1_HDR3               },
	{ 0x3a50 ,N_FLD(dbg_OSD1_HDR4)               ,"OSD1_HDR4"                 ,dbg_OSD1_HDR4               },
	{ 0x3a54 ,N_FLD(dbg_OSD1_HDR5)               ,"OSD1_HDR5"                 ,dbg_OSD1_HDR5               },
	{ 0x3a58 ,N_FLD(dbg_OSD1_HDR6)               ,"OSD1_HDR6"                 ,dbg_OSD1_HDR6               },
	{ 0x3a5c ,N_FLD(dbg_OSD1_LFSR_SEED)          ,"OSD1_LFSR_SEED"            ,dbg_OSD1_LFSR_SEED          },
	{ 0x3a60 ,N_FLD(dbg_OSD2_BASE_ADDR)          ,"OSD2_BASE_ADDR"            ,dbg_OSD2_BASE_ADDR          },
	{ 0x3a64 ,N_FLD(dbg_OSD2_HDR0)               ,"OSD2_HDR0"                 ,dbg_OSD2_HDR0               },
	{ 0x3a68 ,N_FLD(dbg_OSD2_HDR1)               ,"OSD2_HDR1"                 ,dbg_OSD2_HDR1               },
	{ 0x3a6c ,N_FLD(dbg_OSD2_HDR2)               ,"OSD2_HDR2"                 ,dbg_OSD2_HDR2               },
	{ 0x3a70 ,N_FLD(dbg_OSD2_HDR3)               ,"OSD2_HDR3"                 ,dbg_OSD2_HDR3               },
	{ 0x3a74 ,N_FLD(dbg_OSD2_HDR4)               ,"OSD2_HDR4"                 ,dbg_OSD2_HDR4               },
	{ 0x3a78 ,N_FLD(dbg_OSD2_HDR5)               ,"OSD2_HDR5"                 ,dbg_OSD2_HDR5               },
	{ 0x3a7c ,N_FLD(dbg_OSD2_HDR6)               ,"OSD2_HDR6"                 ,dbg_OSD2_HDR6               },
	{ 0x3a80 ,N_FLD(dbg_OSD2_LFSR_SEED)          ,"OSD2_LFSR_SEED"            ,dbg_OSD2_LFSR_SEED          },
	{ 0x3a84 ,N_FLD(dbg_OSD0_SC_CFG)             ,"OSD0_SC_CFG"               ,dbg_OSD0_SC_CFG             },
	{ 0x3a88 ,N_FLD(dbg_OSD1_SC_CFG)             ,"OSD1_SC_CFG"               ,dbg_OSD1_SC_CFG             },
	{ 0x3a8c ,N_FLD(dbg_OSD2_SC_CFG)             ,"OSD2_SC_CFG"               ,dbg_OSD2_SC_CFG             },
	{ 0x3a90 ,N_FLD(dbg_OSD_SC_V_PHASE_OFF)      ,"OSD_SC_V_PHASE_OFF"        ,dbg_OSD_SC_V_PHASE_OFF      },
	{ 0x3a94 ,N_FLD(dbg_OSD0_CSC_CTRL)           ,"OSD0_CSC_CTRL"             ,dbg_OSD0_CSC_CTRL           },
	{ 0x3a98 ,N_FLD(dbg_OSD1_CSC_CTRL)           ,"OSD1_CSC_CTRL"             ,dbg_OSD1_CSC_CTRL           },
	{ 0x3a9c ,N_FLD(dbg_OSD2_CSC_CTRL)           ,"OSD2_CSC_CTRL"             ,dbg_OSD2_CSC_CTRL           },
	{ 0x3aa4 ,N_FLD(dbg_OSD0_END_CONV)           ,"OSD0_END_CONV"             ,dbg_OSD0_END_CONV           },
	{ 0x3aa8 ,N_FLD(dbg_OSD1_END_CONV)           ,"OSD1_END_CONV"             ,dbg_OSD1_END_CONV           },
	{ 0x3aac ,N_FLD(dbg_OSD2_END_CONV)           ,"OSD2_END_CONV"             ,dbg_OSD2_END_CONV           },
	{ 0x3ab4 ,N_FLD(dbg_CRSR_CFG)                ,"CRSR_CFG"                  ,dbg_CRSR_CFG                },
	{ 0x3ab8 ,N_FLD(dbg_CRSR_BASE_ADDR)          ,"CRSR_BASE_ADDR"            ,dbg_CRSR_BASE_ADDR          },
	{ 0x3abc ,N_FLD(dbg_CRSR_HDR0)               ,"CRSR_HDR0"                 ,dbg_CRSR_HDR0               },
	{ 0x3ac0 ,N_FLD(dbg_CRSR_HDR1)               ,"CRSR_HDR1"                 ,dbg_CRSR_HDR1               },
	{ 0x3ac4 ,N_FLD(dbg_CRSR_HDR2)               ,"CRSR_HDR2"                 ,dbg_CRSR_HDR2               },
	{ 0x3ac8 ,N_FLD(dbg_CRSR_HDR3)               ,"CRSR_HDR3"                 ,dbg_CRSR_HDR3               },
	{ 0x3acc ,N_FLD(dbg_CRSR_HDR4)               ,"CRSR_HDR4"                 ,dbg_CRSR_HDR4               },
	{ 0x3ad0 ,N_FLD(dbg_CRSR_HDR5)               ,"CRSR_HDR5"                 ,dbg_CRSR_HDR5               },
	{ 0x3ad4 ,N_FLD(dbg_CRSR_END_CONV)           ,"CRSR_END_CONV"             ,dbg_CRSR_END_CONV           },
	{ 0x3ad8 ,N_FLD(dbg_CRSR_LFSR_SEED)          ,"CRSR_LFSR_SEED"            ,dbg_CRSR_LFSR_SEED          },
	{ 0x3af0 ,N_FLD(dbg_OSD_LAYER_MUX_LEFT)      ,"OSD_LAYER_MUX_LEFT"        ,dbg_OSD_LAYER_MUX_LEFT      },
	{ 0x3af4 ,N_FLD(dbg_OSD_LAYER_MUX_RIGHT)     ,"OSD_LAYER_MUX_RIGHT"       ,dbg_OSD_LAYER_MUX_RIGHT     },
	{ 0x3af8 ,N_FLD(dbg_OSD_MIXER_OUT_LEFT)      ,"OSD_MIXER_OUT_LEFT"        ,dbg_OSD_MIXER_OUT_LEFT      },
	{ 0x3afc ,N_FLD(dbg_OSD_MIXER_OUT_RIGHT)     ,"OSD_MIXER_OUT_RIGHT"       ,dbg_OSD_MIXER_OUT_RIGHT     },
	{ 0x3b00 ,N_FLD(dbg_OSD0_3D_PATH_MODE)       ,"OSD0_3D_PATH_MODE"         ,dbg_OSD0_3D_PATH_MODE       },
	{ 0x3b04 ,N_FLD(dbg_OSD0_3D_DISPARITY)       ,"OSD0_3D_DISPARITY"         ,dbg_OSD0_3D_DISPARITY       },
	{ 0x3b08 ,N_FLD(dbg_OSD0_LEFT_3D_BLANK)      ,"OSD0_LEFT_3D_BLANK"        ,dbg_OSD0_LEFT_3D_BLANK      },
	{ 0x3b0c ,N_FLD(dbg_OSD0_RIGHT_3D_BLANK)     ,"OSD0_RIGHT_3D_BLANK"       ,dbg_OSD0_RIGHT_3D_BLANK     },
	{ 0x3b10 ,N_FLD(dbg_OSD0_TB_SPACE)           ,"OSD0_TB_SPACE"             ,dbg_OSD0_TB_SPACE           },
	{ 0x3b20 ,N_FLD(dbg_OSD1_3D_PATH_MODE)       ,"OSD1_3D_PATH_MODE"         ,dbg_OSD1_3D_PATH_MODE       },
	{ 0x3b24 ,N_FLD(dbg_OSD1_3D_DISPARITY)       ,"OSD1_3D_DISPARITY"         ,dbg_OSD1_3D_DISPARITY       },
	{ 0x3b28 ,N_FLD(dbg_OSD1_LEFT_3D_BLANK)      ,"OSD1_LEFT_3D_BLANK"        ,dbg_OSD1_LEFT_3D_BLANK      },
	{ 0x3b2c ,N_FLD(dbg_OSD1_RIGHT_3D_BLANK)     ,"OSD1_RIGHT_3D_BLANK"       ,dbg_OSD1_RIGHT_3D_BLANK     },
	{ 0x3b30 ,N_FLD(dbg_OSD1_TB_SPACE)           ,"OSD1_TB_SPACE"             ,dbg_OSD1_TB_SPACE           },
	{ 0x3b40 ,N_FLD(dbg_OSD2_3D_PATH_MODE)       ,"OSD2_3D_PATH_MODE"         ,dbg_OSD2_3D_PATH_MODE       },
	{ 0x3b44 ,N_FLD(dbg_OSD2_3D_DISPARITY)       ,"OSD2_3D_DISPARITY"         ,dbg_OSD2_3D_DISPARITY       },
	{ 0x3b48 ,N_FLD(dbg_OSD2_LEFT_3D_BLANK)      ,"OSD2_LEFT_3D_BLANK"        ,dbg_OSD2_LEFT_3D_BLANK      },
	{ 0x3b4c ,N_FLD(dbg_OSD2_RIGHT_3D_BLANK)     ,"OSD2_RIGHT_3D_BLANK"       ,dbg_OSD2_RIGHT_3D_BLANK     },
	{ 0x3b50 ,N_FLD(dbg_OSD2_TB_SPACE)           ,"OSD2_TB_SPACE"             ,dbg_OSD2_TB_SPACE           },
	{ 0x3b60 ,N_FLD(dbg_OSD3_3D_PATH_MODE)       ,"OSD3_3D_PATH_MODE"         ,dbg_OSD3_3D_PATH_MODE       },
	{ 0x3b64 ,N_FLD(dbg_OSD3_3D_DISPARITY)       ,"OSD3_3D_DISPARITY"         ,dbg_OSD3_3D_DISPARITY       },
	{ 0x3b68 ,N_FLD(dbg_OSD3_LEFT_3D_BLANK)      ,"OSD3_LEFT_3D_BLANK"        ,dbg_OSD3_LEFT_3D_BLANK      },
	{ 0x3b6c ,N_FLD(dbg_OSD3_RIGHT_3D_BLANK)     ,"OSD3_RIGHT_3D_BLANK"       ,dbg_OSD3_RIGHT_3D_BLANK     },
	{ 0x3b70 ,N_FLD(dbg_OSD3_TB_SPACE)           ,"OSD3_TB_SPACE"             ,dbg_OSD3_TB_SPACE           },
	{ 0x3ba0 ,N_FLD(dbg_OSD_FRC_IF_CFG)          ,"OSD_FRC_IF_CFG"            ,dbg_OSD_FRC_IF_CFG          },
	{ 0x3ba4 ,N_FLD(dbg_OSD_FRC_HDR_0)           ,"OSD_FRC_HDR_0"             ,dbg_OSD_FRC_HDR_0           },
	{ 0x3ba8 ,N_FLD(dbg_OSD_FRC_HDR_1)           ,"OSD_FRC_HDR_1"             ,dbg_OSD_FRC_HDR_1           },
	{ 0x3bac ,N_FLD(dbg_OSD_FRC_HDR_2)           ,"OSD_FRC_HDR_2"             ,dbg_OSD_FRC_HDR_2           },
	{ 0x3bb0 ,N_FLD(dbg_OSD_FRC_HDR_3)           ,"OSD_FRC_HDR_3"             ,dbg_OSD_FRC_HDR_3           },
	{ 0x3bb4 ,N_FLD(dbg_OSD_FRC_HDR_4)           ,"OSD_FRC_HDR_4"             ,dbg_OSD_FRC_HDR_4           },
	{ 0x3bb8 ,N_FLD(dbg_OSD_FRC_HDR_5)           ,"OSD_FRC_HDR_5"             ,dbg_OSD_FRC_HDR_5           },
	{ 0x3bc0 ,N_FLD(dbg_OSD_FRC_ABLEND_TH_L)     ,"OSD_FRC_ABLEND_TH_L"       ,dbg_OSD_FRC_ABLEND_TH_L     },
	{ 0x3bc4 ,N_FLD(dbg_OSD_FRC_ABLEND_TH_R)     ,"OSD_FRC_ABLEND_TH_R"       ,dbg_OSD_FRC_ABLEND_TH_R     },
	{ 0x3bd0 ,N_FLD(dbg_OSD_DDR_ADDRESSING)      ,"OSD_DDR_ADDRESSING"        ,dbg_OSD_DDR_ADDRESSING      },
	{ 0x3bd8 ,N_FLD(dbg_OSD_LEFT_AWB)            ,"OSD_LEFT_AWB"              ,dbg_OSD_LEFT_AWB            },
	{ 0x3bdc ,N_FLD(dbg_OSD_RIGHT_AWB)           ,"OSD_RIGHT_AWB"             ,dbg_OSD_RIGHT_AWB           },
	{ 0x3be4 ,N_FLD(dbg_OSD_L_MIXER_STATUS)      ,"OSD_L_MIXER_STATUS"        ,dbg_OSD_L_MIXER_STATUS      },
	{ 0x3be8 ,N_FLD(dbg_OSD_R_MIXER_STATUS)      ,"OSD_R_MIXER_STATUS"        ,dbg_OSD_R_MIXER_STATUS      },
	{ 0x3bec ,N_FLD(dbg_OSD_STATUS_CFG)          ,"OSD_STATUS_CFG"            ,dbg_OSD_STATUS_CFG          },
	{ 0x3bf0 ,N_FLD(dbg_OSD_STATUS_0)            ,"OSD_STATUS_0"              ,dbg_OSD_STATUS_0            },
	{ 0x3bf4 ,N_FLD(dbg_OSD_STATUS_1)            ,"OSD_STATUS_1"              ,dbg_OSD_STATUS_1            },
	{ 0x3bf8 ,N_FLD(dbg_OSD_STATUS_2)            ,"OSD_STATUS_2"              ,dbg_OSD_STATUS_2            },
	{ 0x3bfc ,N_FLD(dbg_OSD_STATUS_3)            ,"OSD_STATUS_3"              ,dbg_OSD_STATUS_3            },
	{ 0 , } // end marker
};

#endif
