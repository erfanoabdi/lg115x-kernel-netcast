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

#ifndef _DBG_MIF_h
#define _DBG_MIF_h

/*--------------------------------------------
	0x0800 MIFA_RD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_r_mvi_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_r_mvi_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"block_req_r_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"block_req_r_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"block_req_r_ipc0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"block_req_r_ipc_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"block_req_r_ipc1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"block_req_r_tnr0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"block_req_r_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"block_req_r_tnr1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_rd_mif"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_rd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_rd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_rd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_rd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_rd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_rd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_rd_stv_cnt"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"mrb_bank_mode"               },
};

/*--------------------------------------------
	0x0804 MIFA_WD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_w_tnr_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_w_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"block_req_w_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"block_req_w_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_wd_mif"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_wd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_wd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_wd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_wd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_wd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_wd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_wd_stv_cnt"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"mwb_bank_mode"               },
};

/*--------------------------------------------
	0x0808 MIF_RD_SET_10B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIF_RD_SET_10B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"set_10b_req_rd_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"set_10b_req_rd_prew_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"set_10b_req_rd_ipc0_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"set_10b_req_rd_ipc_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"set_10b_req_rd_ipc1_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"set_10b_req_rd_tnr0_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"set_10b_req_rd_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"set_10b_req_rd_tnr1_y"       },
};

/*--------------------------------------------
	0x080c MIF_WD_SET_10B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIF_WD_SET_10B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"set_10b_req_wd_tnr_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"set_10b_req_wd_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"set_10b_req_wd_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"set_10b_req_wd_prew_c"       },
};

/*--------------------------------------------
	0x0810 MIFA_RD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_v_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_v_mvi_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_v_prew_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pri_v_ipc0_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pri_v_ipc_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_pri_v_ipc1_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_pri_v_tnr0_y"         },
};

/*--------------------------------------------
	0x0814 MIFA_RD_CMD_PRI1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_PRI1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_v_tnr1_y"         },
};

/*--------------------------------------------
	0x0818 MIFA_WD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_v_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_pri_v_prew_c"         },
};

/*--------------------------------------------
	0x081c MIFA_RD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_mvi_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_pri_v_prew_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_pri_v_ipc0_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_pri_v_ipc_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_pri_v_ipc1_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_pri_v_tnr0_y"         },
};

/*--------------------------------------------
	0x0820 MIFA_RD_REQ_PRI1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_REQ_PRI1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_tnr1_y"         },
};

/*--------------------------------------------
	0x0824 MIFA_WD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_pri_v_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_pri_v_prew_c"         },
};

/*--------------------------------------------
	0x0828 MIFA_RD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_stv_v_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_stv_v_mvi_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_stv_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_stv_v_prew_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_stv_v_ipc0_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_stv_v_ipc_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_stv_v_ipc1_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_stv_v_tnr0_y"         },
};

/*--------------------------------------------
	0x082c MIFA_RD_REQ_STV1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_REQ_STV1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_stv_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_stv_v_tnr1_y"         },
};

/*--------------------------------------------
	0x0830 MIFA_WD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_stv_v_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_stv_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_stv_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_stv_v_prew_c"         },
};

/*--------------------------------------------
	0x0834 MIFA_RD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pend_v_mvi_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pend_v_mvi_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pend_v_prew_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pend_v_ipc0_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pend_v_ipc_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_pend_v_ipc1_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_pend_v_tnr0_y"        },
};

/*--------------------------------------------
	0x0838 MIFA_RD_CMD_PEND1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_PEND1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pend_v_tnr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pend_v_tnr1_y"        },
};

/*--------------------------------------------
	0x083c MIFA_WD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pend_v_tnr_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pend_v_tnr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_pend_v_prew_c"        },
};

/*--------------------------------------------
	0x0840 MIFA_RD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_mvi_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_mvi_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_stride_v_2_prew_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_stride_v_8_prew_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_stride_v_2_prew_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_stride_v_8_prew_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_stride_v_2_ipc0_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_stride_v_8_ipc0_y"    },
};

/*--------------------------------------------
	0x0844 MIFA_RD_CMD_STRIDE1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_STRIDE1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_2_ipc_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_8_ipc_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_stride_v_2_ipc1_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_stride_v_8_ipc1_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_stride_v_2_tnr0_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_stride_v_8_tnr0_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_stride_v_2_tnr_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_stride_v_8_tnr_c"     },
};

/*--------------------------------------------
	0x0848 MIFA_RD_CMD_STRIDE2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_STRIDE2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_2_tnr1_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_8_tnr1_y"    },
};

/*--------------------------------------------
	0x084c MIFA_RD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_rd_stride_v_mvi_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_rd_stride_v_mvi_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"man_cmd_rd_stride_v_prew_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"man_cmd_rd_stride_v_prew_c"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"man_cmd_rd_stride_v_ipc0_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"man_cmd_rd_stride_v_ipc_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"man_cmd_rd_stride_v_ipc1_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"man_cmd_rd_stride_v_tnr0_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"man_cmd_rd_stride_v_tnr_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"man_cmd_rd_stride_v_tnr1_y"  },
};

/*--------------------------------------------
	0x0850 MIFA_WD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_stride_v_2_tnr_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_stride_v_8_tnr_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_stride_v_2_tnr_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_stride_v_8_tnr_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_wd_stride_v_2_prew_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_wd_stride_v_8_prew_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_wd_stride_v_2_prew_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_wd_stride_v_8_prew_c"    },
};

/*--------------------------------------------
	0x0854 MIFA_WD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_wd_stride_v_tnr_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_wd_stride_v_tnr_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"man_cmd_wd_stride_v_prew_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"man_cmd_wd_stride_v_prew_c"  },
};

/*--------------------------------------------
	0x0858 MIFA_SADDR_RD_MVI_Y_MVI_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_MVI_Y_MVI_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_mvi_c"          },
};

/*--------------------------------------------
	0x085c MIFA_SADDR_RD_PREW_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_PREW_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_prew_y"       },
};

/*--------------------------------------------
	0x0860 MIFA_SADDR_RD_PREW_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_PREW_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_prew_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_prew_c"       },
};

/*--------------------------------------------
	0x0864 MIFA_SADDR_RD_IPC0_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_IPC0_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_ipc0_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_ipc0_y"       },
};

/*--------------------------------------------
	0x0868 MIFA_SADDR_RD_IPC_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_IPC_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_ipc_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_ipc_c"        },
};

/*--------------------------------------------
	0x086c MIFA_SADDR_RD_IPC1_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_IPC1_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_ipc1_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_ipc1_y"       },
};

/*--------------------------------------------
	0x0870 MIFA_SADDR_RD_TNR0_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_TNR0_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_tnr0_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_tnr0_y"       },
};

/*--------------------------------------------
	0x0874 MIFA_SADDR_RD_TNR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_TNR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_tnr_c"        },
};

/*--------------------------------------------
	0x0878 MIFA_SADDR_RD_TNR1_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_TNR1_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_tnr1_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_tnr1_y"       },
};

/*--------------------------------------------
	0x087c MIFA_SADDR_WD_TNR_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_TNR_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_tnr_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_tnr_y"        },
};

/*--------------------------------------------
	0x0880 MIFA_SADDR_WD_TNR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_TNR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_tnr_c"        },
};

/*--------------------------------------------
	0x0884 MIFA_SADDR_WD_PREW_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_PREW_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_prew_y"       },
};

/*--------------------------------------------
	0x0888 MIFA_SADDR_WD_PREW_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_PREW_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_prew_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_prew_c"       },
};

/*--------------------------------------------
	0x088c MIFA_SADDR_RD_DL_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_DL_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_dl_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_dl_y"         },
};

/*--------------------------------------------
	0x0890 MIFA_SADDR_RD_DL_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_DL_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_dl_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_dl_c"         },
};

/*--------------------------------------------
	0x0894 MIFA_SADDR_RD_DR_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_DR_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_dr_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_dr_y"         },
};

/*--------------------------------------------
	0x0898 MIFA_SADDR_RD_DR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_DR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_dr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_dr_c"         },
};

/*--------------------------------------------
	0x089c MIFA_SADDR_WD_DL_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_DL_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_dl_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_dl_y"         },
};

/*--------------------------------------------
	0x08a0 MIFA_SADDR_WD_DL_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_DL_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_dl_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_dl_c"         },
};

/*--------------------------------------------
	0x08a4 MIFA_SADDR_WD_DR_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_DR_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_dr_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_dr_y"         },
};

/*--------------------------------------------
	0x08a8 MIFA_SADDR_WD_DR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_DR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_dr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_dr_c"         },
};

/*--------------------------------------------
	0x08ac MIFA_SADDR_RD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_mvi_y_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_mvi_c_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_2_prew_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_saddr_8_prew_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_saddr_2_prew_c_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_saddr_8_prew_c_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_saddr_2_ipc0_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_saddr_8_ipc0_y_msb4b" },
};

/*--------------------------------------------
	0x08b0 MIFA_SADDR_RD_EXT1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_EXT1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_2_ipc_c_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_8_ipc_c_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_2_ipc1_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_saddr_8_ipc1_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_saddr_2_tnr0_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_saddr_8_tnr0_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_saddr_2_tnr_c_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_saddr_8_tnr_c_msb4b"  },
};

/*--------------------------------------------
	0x08b4 MIFA_SADDR_RD_EXT2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_RD_EXT2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_2_tnr1_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_8_tnr1_y_msb4b" },
};

/*--------------------------------------------
	0x08b8 MIFA_SADDR_WD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_WD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_saddr_2_tnr_y_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_saddr_8_tnr_y_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_saddr_2_tnr_c_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_saddr_8_tnr_c_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_wd_saddr_2_prew_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_wd_saddr_8_prew_y_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_wd_saddr_2_prew_c_msb4b" },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_wd_saddr_8_prew_c_msb4b" },
};

/*--------------------------------------------
	0x08bc MIFA_RD_DR_DL_EXT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_DR_DL_EXT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_2_dl_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_8_dl_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_2_dl_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_saddr_8_dl_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_saddr_2_dr_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_saddr_8_dr_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_saddr_2_dr_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_saddr_8_dr_c_msb4b"   },
};

/*--------------------------------------------
	0x08c0 MIFA_WD_DR_DL_EXT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_DR_DL_EXT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_saddr_2_dl_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_saddr_8_dl_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_saddr_2_dl_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_saddr_8_dl_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_wd_saddr_2_dr_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_wd_saddr_8_dr_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_wd_saddr_2_dr_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_wd_saddr_8_dr_c_msb4b"   },
};

/*--------------------------------------------
	0x08c4 MIFA_STATUS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fr_rd_valid_mvi_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fr_rd_valid_mvi_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"fr_rd_valid_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"fr_rd_valid_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fr_rd_valid_ipc0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"fr_rd_valid_ipc_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"fr_rd_valid_ipc1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"fr_rd_valid_tnr0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"fr_rd_valid_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"fr_rd_valid_tnr1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"fr_wd_q_full_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"fr_wd_q_full_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"fr_wd_q_full_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"fr_wd_q_full_prew_c"         },
};

/*--------------------------------------------
	0x08c8 MIFA_SADDR_PARAM_UPDATE0_M
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_PARAM_UPDATE0_M[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,11 ,"register_update_address0_m"  },
};

/*--------------------------------------------
	0x08cc MIFA_SADDR_PARAM_UPDATE0_M1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_SADDR_PARAM_UPDATE0_M1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,11 ,"register_update_address0_m1" },
};

/*--------------------------------------------
	0x08d0 MIFA_RD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_8_mvi_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_8_mvi_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_rd_bank_addr_8_prew_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_rd_bank_addr_8_prew_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"req_rd_bank_addr_8_ipc0_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"req_rd_bank_addr_8_ipc_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"req_rd_bank_addr_8_ipc1_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"req_rd_bank_addr_8_tnr0_y"   },
};

/*--------------------------------------------
	0x08d4 MIFA_RD_BANK_8_ADDR1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_BANK_8_ADDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_8_tnr_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_8_tnr1_y"   },
};

/*--------------------------------------------
	0x08d8 MIFA_RD_BANK_2_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_BANK_2_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_rd_bank_addr_2_prew_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_rd_bank_addr_2_prew_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"req_rd_bank_addr_2_ipc0_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"req_rd_bank_addr_2_ipc_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"req_rd_bank_addr_2_ipc1_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"req_rd_bank_addr_2_tnr0_y"   },
};

/*--------------------------------------------
	0x08dc MIFA_RD_BANK_2_ADDR1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_BANK_2_ADDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_2_tnr_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_2_tnr1_y"   },
};

/*--------------------------------------------
	0x08e0 MIFA_WD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_wd_bank_addr_8_tnr_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_wd_bank_addr_8_tnr_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_wd_bank_addr_8_prew_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_wd_bank_addr_8_prew_c"   },
};

/*--------------------------------------------
	0x08e4 MIFA_WD_BANK_8_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x08e8 MIFA_WD_BANK_2_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_BANK_2_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_wd_bank_addr_2_tnr_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_wd_bank_addr_2_tnr_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_wd_bank_addr_2_prew_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_wd_bank_addr_2_prew_c"   },
};

/*--------------------------------------------
	0x08ec MIFA_WD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x08f0 MIFA_LSB_SWITCH
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_LSB_SWITCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"req_rd_lsb_prew_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"req_rd_lsb_prew_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"req_rd_lsb_ipc0_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"req_rd_lsb_ipc_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,8  ,"req_rd_lsb_ipc1_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,10 ,"req_rd_lsb_tnr0_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"req_rd_lsb_tnr_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,14 ,"req_rd_lsb_tnr1_y"           },
};

/*--------------------------------------------
	0x08f4 MIFA_RD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_mvi_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_mvi_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_rd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"req_rd_pend_v_prew_c"        },
};

/*--------------------------------------------
	0x08f8 MIFA_RD_REQ_PEND1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_REQ_PEND1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_ipc0_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_ipc_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_rd_pend_v_ipc1_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"req_rd_pend_v_tnr0_y"        },
};

/*--------------------------------------------
	0x08fc MIFA_RD_REQ_PEND2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_REQ_PEND2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_tnr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_tnr1_y"        },
};

/*--------------------------------------------
	0x0900 MIFA_WD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_wd_pend_v_tnr_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_wd_pend_v_tnr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_wd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"req_wd_pend_v_prew_c"        },
};

/*--------------------------------------------
	0x0904 MIFA_RD_CMD_PRI0_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_PRI0_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_s_v_mvi_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_s_v_mvi_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_s_v_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_s_v_prew_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pri_s_v_ipc0_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pri_s_v_ipc_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_pri_s_v_ipc1_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_pri_s_v_tnr0_y"       },
};

/*--------------------------------------------
	0x0908 MIFA_RD_CMD_PRI1_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RD_CMD_PRI1_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_s_v_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_s_v_tnr1_y"       },
};

/*--------------------------------------------
	0x090c MIFA_WD_CMD_PRI0_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_WD_CMD_PRI0_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_s_v_tnr_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_s_v_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_pri_s_v_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_pri_s_v_prew_c"       },
};

/*--------------------------------------------
	0x0910 MIFA_RESET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFA_RESET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"reset_mif_r_mvi_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"reset_mif_r_mvi_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"reset_mif_r_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"reset_mif_r_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"reset_mif_r_ipc0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"reset_mif_r_ipc_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"reset_mif_r_ipc1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"reset_mif_r_tnr0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"reset_mif_r_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"reset_mif_r_tnr1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"reset_mif_w_tnr_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"reset_mif_w_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"reset_mif_w_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"reset_mif_w_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"reset_time_out_cnt"          },
};

/*--------------------------------------------
	0x1b00 MIFB_RD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_r_ovm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_r_ovm_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"block_req_r_ovs_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"block_req_r_ovs_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_rd_mif"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_rd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_rd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_rd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_rd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_rd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_rd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_rd_stv_cnt"           },
};

/*--------------------------------------------
	0x1b04 MIFB_WD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_w_scm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_w_scm_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_wd_mif"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_wd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_wd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_wd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_wd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_wd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_wd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_wd_stv_cnt"           },
};

/*--------------------------------------------
	0x1b08 MIFB_RD_SET_10B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_SET_10B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"set_10b_req_rd_ovm_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"set_10b_req_rd_ovm_c"        },
};

/*--------------------------------------------
	0x1b0c MIFB_WD_SET_10B
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_SET_10B[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"set_10b_req_wd_scm_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"set_10b_req_wd_scm_c"        },
};

/*--------------------------------------------
	0x1b10 MIFB_RD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_v_ovm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_v_ovm_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_v_ovs_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_v_ovs_c"          },
};

/*--------------------------------------------
	0x1b14 MIFB_WD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_v_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_v_sm_c"           },
};

/*--------------------------------------------
	0x1b18 MIFB_RD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_ovm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_ovm_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_pri_v_ovs_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_pri_v_ovs_c"          },
};

/*--------------------------------------------
	0x1b1c MIFB_WD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_pri_v_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_pri_v_sm_c"           },
};

/*--------------------------------------------
	0x1b20 MIFB_RD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_stv_v_ovm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_stv_v_ovm_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_stv_v_ovs_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_stv_v_ovs_c"          },
};

/*--------------------------------------------
	0x1b24 MIFB_WD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_stv_v_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_stv_v_sm_c"           },
};

/*--------------------------------------------
	0x1b28 MIFB_RD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pend_v_ovm_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pend_v_ovm_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pend_v_ovs_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pend_v_ovs_c"         },
};

/*--------------------------------------------
	0x1b2c MIFB_WD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pend_v_sm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pend_v_sm_c"          },
};

/*--------------------------------------------
	0x1b30 MIFB_RD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_2_ovm_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_8_ovm_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_stride_v_2_ovm_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_stride_v_8_ovm_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_stride_v_ovs_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_stride_v_ovs_c"       },
};

/*--------------------------------------------
	0x1b34 MIFB_RD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_rd_stride_v_ovm_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_rd_stride_v_ovm_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"man_cmd_rd_stride_v_ovs_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"man_cmd_rd_stride_v_ovs_c"   },
};

/*--------------------------------------------
	0x1b38 MIFB_WD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_stride_v_2_sm_y"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_stride_v_8_sm_y"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_stride_v_2_sm_c"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_stride_v_8_sm_c"      },
};

/*--------------------------------------------
	0x1b3c MIFB_WD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_wd_stride_v_sm_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_wd_stride_v_sm_c"    },
};

/*--------------------------------------------
	0x1b40 MIFB_SADDR_RD_OVM_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_RD_OVM_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_ovm_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_ovm_y"        },
};

/*--------------------------------------------
	0x1b44 MIFB_SADDR_RD_OVM_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_RD_OVM_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_2_ovm_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_8_ovm_c"        },
};

/*--------------------------------------------
	0x1b48 MIFB_SADDR_RD_OVS_Y_OVS_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_RD_OVS_Y_OVS_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_ovs_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_ovs_c"          },
};

/*--------------------------------------------
	0x1b4c MIFB_SADDR_WD_SM_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_WD_SM_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_sm_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_sm_y"         },
};

/*--------------------------------------------
	0x1b50 MIFB_SADDR_WD_SM_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_WD_SM_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_2_sm_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_8_sm_c"         },
};

/*--------------------------------------------
	0x1b54 MIFB_SADDR_RD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_RD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_2_ovm_y_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_8_ovm_y_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_2_ovm_c_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_saddr_8_ovm_c_msb4b"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_saddr_ovs_y_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_saddr_ovs_c_msb4b"    },
};

/*--------------------------------------------
	0x1b58 MIFB_SADDR_WD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_WD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_saddr_2_sm_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_saddr_8_sm_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_saddr_2_sm_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_saddr_8_sm_c_msb4b"   },
};

/*--------------------------------------------
	0x1b5c MIFB_STATUS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fr_rd_valid_ovm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fr_rd_valid_ovm_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"fr_rd_valid_ovs_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"fr_rd_valid_ovs_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fr_wd_q_full_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"fr_wd_q_full_sm_c"           },
};

/*--------------------------------------------
	0x1b60 MIFB_SADDR_PARAM_UPDATE0_M
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_SADDR_PARAM_UPDATE0_M[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,11 ,"register_update_address0_m"  },
};

/*--------------------------------------------
	0x1b64 MIFB_RD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_8_ovm_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_8_ovm_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_rd_bank_addr_ovs_y"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_rd_bank_addr_ovs_c"      },
};

/*--------------------------------------------
	0x1b68 MIFB_RD_BANK_8_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1b6c MIFB_RD_BANK_2_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_BANK_2_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_2_ovs_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_2_ovs_c"    },
};

/*--------------------------------------------
	0x1b70 MIFB_RD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1b74 MIFB_WD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_wd_bank_addr_8_sm_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_wd_bank_addr_8_sm_c"     },
};

/*--------------------------------------------
	0x1b78 MIFB_WD_BANK_8_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1b7c MIFB_WD_BANK_2_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_BANK_2_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_wd_bank_addr_8_sm_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_wd_bank_addr_8_sm_c"     },
};

/*--------------------------------------------
	0x1b80 MIFB_WD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1b84 MIFB_LSB_SWITCH
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_LSB_SWITCH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"req_rd_lsb_ovm_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,2  ,"req_rd_lsb_ovm_c"            },
};

/*--------------------------------------------
	0x1b88 MIFB_RD_REQ_PEND0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x1b8c MIFB_WD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_wd_pend_v_sm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_wd_pend_v_sm_c"          },
};

/*--------------------------------------------
	0x1b90 MIFB_RD_CMD_PRI00_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RD_CMD_PRI00_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_s_v_ovm_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_s_v_ovm_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_s_v_ovs_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_s_v_ovs_c"        },
};

/*--------------------------------------------
	0x1b94 MIFB_WD_CMD_PRI00_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_WD_CMD_PRI00_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_s_v_sm_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_s_v_sm_c"         },
};

/*--------------------------------------------
	0x1b98 MIFB_RESET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFB_RESET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"reset_mif_r_ovm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"reset_mif_r_ovm_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"reset_mif_r_ovs_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"reset_mif_r_ovs_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"reset_mif_w_scm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"reset_mif_w_scm_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"reset_time_out_cnt"          },
};

/*--------------------------------------------
	0x2800 MIFC_RD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_r_mvi_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_r_mvi_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"block_req_r_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"block_req_r_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"block_req_r_ipc0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"block_req_r_ipc_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"block_req_r_ipc1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"block_req_r_tnr0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"block_req_r_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"block_req_r_ss_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"block_req_r_ss_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_rd_mifc"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_rd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_rd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_rd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_rd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_rd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_rd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_rd_stv_cnt"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"mrb_bank_mode"               },
};

/*--------------------------------------------
	0x2804 MIFC_WD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_w_ss_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_w_ss_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"block_req_w_tnr_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"block_req_w_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"block_req_w_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"block_req_w_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_wd_mifc"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_wd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_wd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_wd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_wd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_wd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_wd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_wd_stv_cnt"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,20 ,20 ,"set_ecanvas"                 },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"mwb_bank_mode"               },
};

/*--------------------------------------------
	0x2808 MIFC_RD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_v_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_v_mvi_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_v_prew_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pri_v_ipc0_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pri_v_ipc_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_pri_v_ipc1_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_pri_v_tnr0_y"         },
};

/*--------------------------------------------
	0x280c MIFC_RD_CMD_PRI1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_PRI1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_v_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_v_ss_c"           },
};

/*--------------------------------------------
	0x2810 MIFC_WD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_v_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_v_ss_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_pri_v_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_wd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_wd_pri_v_prew_c"         },
};

/*--------------------------------------------
	0x2814 MIFC_RD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_mvi_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_pri_v_prew_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_pri_v_ipc0_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_pri_v_ipc1_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_pri_v_ipc_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_pri_v_tnr0_y"         },
};

/*--------------------------------------------
	0x2818 MIFC_RD_REQ_PRI1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_REQ_PRI1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_pri_v_ss_c"           },
};

/*--------------------------------------------
	0x281c MIFC_WD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_pri_v_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_pri_v_ss_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_pri_v_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_wd_pri_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_wd_pri_v_prew_c"         },
};

/*--------------------------------------------
	0x2820 MIFC_RD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_stv_v_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_stv_v_mvi_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_stv_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_stv_v_prew_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_stv_v_ipc0_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_stv_v_ipc_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_stv_v_ipc1_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_stv_v_tnr0_y"         },
};

/*--------------------------------------------
	0x2824 MIFC_RD_REQ_STV1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_REQ_STV1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_pri_v_ss_c"           },
};

/*--------------------------------------------
	0x2828 MIFC_WD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_stv_v_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_stv_v_ss_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_stv_v_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_stv_v_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_wd_stv_v_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_wd_stv_v_prew_c"         },
};

/*--------------------------------------------
	0x282c MIFC_RD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pend_v_mvi_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pend_v_mvi_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pend_v_prew_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pend_v_ipc0_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pend_v_ipc_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_pend_v_ipc1_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_pend_v_tnr0_y"        },
};

/*--------------------------------------------
	0x2830 MIFC_RD_CMD_PEND1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_PEND1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pend_v_tnr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pend_v_ss_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pend_v_ss_c"          },
};

/*--------------------------------------------
	0x2834 MIFC_WD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pend_v_ss_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pend_v_ss_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_pend_v_tnr_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_pend_v_tnr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_wd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_wd_pend_v_prew_c"        },
};

/*--------------------------------------------
	0x2838 MIFC_RD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_mvi_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_mvi_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_stride_v_prew_y"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_stride_v_prew_c"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_stride_v_ipc0_y"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_stride_v_ipc_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_stride_v_ipc1_y"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_stride_v_tnr0_y"      },
};

/*--------------------------------------------
	0x283c MIFC_RD_CMD_STRIDE1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_STRIDE1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_tnr_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_ss_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_stride_v_ss_c"        },
};

/*--------------------------------------------
	0x2840 MIFC_RD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_rd_stride_v_mvi_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_rd_stride_v_mvi_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"man_cmd_rd_stride_v_prew_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"man_cmd_rd_stride_v_prew_c"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"man_cmd_rd_stride_v_ipc0_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"man_cmd_rd_stride_v_ipc_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"man_cmd_rd_stride_v_ipc1_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"man_cmd_rd_stride_v_tnr0_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"man_cmd_rd_stride_v_tnr_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"man_cmd_rd_stride_v_ss_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"man_cmd_rd_stride_v_ss_c"    },
};

/*--------------------------------------------
	0x2844 MIFC_WD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_stride_v_ss_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_stride_v_ss_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_stride_v_tnr_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_stride_v_tnr_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_wd_stride_v_prew_y"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_wd_stride_v_prew_c"      },
};

/*--------------------------------------------
	0x2848 MIFC_WD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_wd_stride_v_ss_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_wd_stride_v_ss_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"man_cmd_wd_stride_v_tnr_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"man_cmd_wd_stride_v_tnr_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"man_cmd_wd_stride_v_prew_y"  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"man_cmd_wd_stride_v_prew_c"  },
};

/*--------------------------------------------
	0x284c MIFC_SADDR_RD_MVI_Y_MVI_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_MVI_Y_MVI_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_mvi_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_mvi_c"          },
};

/*--------------------------------------------
	0x2850 MIFC_SADDR_RD_PREW_Y_PREW_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_PREW_Y_PREW_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_prew_c"         },
};

/*--------------------------------------------
	0x2854 MIFC_SADDR_RD_IPC0_Y_IPC_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_IPC0_Y_IPC_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_ipc0_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_ipc_c"          },
};

/*--------------------------------------------
	0x2858 MIFC_SADDR_RD_IPC1_Y_TNR0_Y
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_IPC1_Y_TNR0_Y[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_ipc1_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_tnr0_y"         },
};

/*--------------------------------------------
	0x285c MIFC_SADDR_RD_SS_Y_SS_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_SS_Y_SS_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_ss_c"           },
};

/*--------------------------------------------
	0x2860 MIFC_SADDR_RD_TNR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_TNR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_tnr_c"          },
};

/*--------------------------------------------
	0x2864 MIFC_SADDR_WD_SS_Y_SS_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_WD_SS_Y_SS_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_ss_c"           },
};

/*--------------------------------------------
	0x2868 MIFC_SADDR_WD_TNR_Y_TNR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_WD_TNR_Y_TNR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_tnr_c"          },
};

/*--------------------------------------------
	0x286c MIFC_SADDR_WD_PREW_Y_PREW_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_WD_PREW_Y_PREW_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_prew_c"         },
};

/*--------------------------------------------
	0x2870 MIFC_SADDR_RD_DL_Y_DL_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_DL_Y_DL_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_dl_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_dl_c"           },
};

/*--------------------------------------------
	0x2874 MIFC_SADDR_RD_DR_Y_DR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_DR_Y_DR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_dr_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_dr_c"           },
};

/*--------------------------------------------
	0x2878 MIFC_SADDR_WD_DL_Y_DL_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_WD_DL_Y_DL_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_dl_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_dl_c"           },
};

/*--------------------------------------------
	0x287c MIFC_SADDR_WD_DR_Y_DR_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_WD_DR_Y_DR_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_dr_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_dr_c"           },
};

/*--------------------------------------------
	0x2880 MIFC_SADDR_RD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_mvi_y_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_mvi_c_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_prew_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_saddr_prew_c_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_saddr_ipc0_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_saddr_ipc_c_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"req_rd_saddr_ipc1_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"req_rd_saddr_tnr0_y_msb4b"   },
};

/*--------------------------------------------
	0x2884 MIFC_SADDR_RD_EXT1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_RD_EXT1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_tnr_c_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_ss_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_ss_c_msb4b"     },
};

/*--------------------------------------------
	0x2888 MIFC_SADDR_WD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_WD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_saddr_ss_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_saddr_ss_c_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_saddr_tnr_y_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_saddr_tnr_c_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_wd_saddr_prew_y_msb4b"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_wd_saddr_prew_c_msb4b"   },
};

/*--------------------------------------------
	0x288c MIFC_RD_DR_DL_EXT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_DR_DL_EXT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_dl_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_dl_c_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_dr_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_saddr_dr_c_msb4b"     },
};

/*--------------------------------------------
	0x2890 MIFC_WD_DR_DL_EXT
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_DR_DL_EXT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_saddr_dl_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_saddr_dl_c_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_wd_saddr_dr_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_wd_saddr_dr_c_msb4b"     },
};

/*--------------------------------------------
	0x2894 MIFC_STATUS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fr_rd_valid_mvi_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fr_rd_valid_mvi_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"fr_rd_valid_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"fr_rd_valid_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fr_rd_valid_ipc0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"fr_rd_valid_ipc_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"fr_rd_valid_ipc1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"fr_rd_valid_tnr0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"fr_rd_valid_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"fr_rd_valid_ss_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"fr_rd_valid_ss_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"fr_wd_q_full_ss_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"fr_wd_q_full_ss_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"fr_wd_q_full_tnr_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"fr_wd_q_full_tnr_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"fr_wd_q_full_prew_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"fr_wd_q_full_prew_c"         },
};

/*--------------------------------------------
	0x2898 MIFC_SADDR_PARAM_UPDATE0_M
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_SADDR_PARAM_UPDATE0_M[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,11 ,"register_update_address0_m"  },
};

/*--------------------------------------------
	0x289c MIFC_RD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_8_mvi_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_8_mvi_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_rd_bank_addr_8_prew_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_rd_bank_addr_8_prew_c"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"req_rd_bank_addr_8_ipc0_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"req_rd_bank_addr_8_ipc_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,26 ,24 ,"req_rd_bank_addr_8_ipc1_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,28 ,"req_rd_bank_addr_8_tnr0_y"   },
};

/*--------------------------------------------
	0x28a0 MIFC_RD_BANK_8_ADDR1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_BANK_8_ADDR1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_8_tnr_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_8_ss_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_rd_bank_addr_8_ss_c"     },
};

/*--------------------------------------------
	0x28a4 MIFC_RD_BANK_2_ADDR0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x28a8 MIFC_RD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x28ac MIFC_WD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_wd_bank_addr_8_ss_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_wd_bank_addr_8_ss_c"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_wd_bank_addr_8_tnr_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_wd_bank_addr_8_tnr_c"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"req_wd_bank_addr_8_prew_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"req_wd_bank_addr_8_prew_c"   },
};

/*--------------------------------------------
	0x28b0 MIFC_WD_BANK_8_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x28b4 MIFC_WD_BANK_2_ADDR0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x28b8 MIFC_WD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x28bc MIFC_RD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_mvi_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_mvi_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_rd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"req_rd_pend_v_prew_c"        },
};

/*--------------------------------------------
	0x28c0 MIFC_RD_REQ_PEND1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_REQ_PEND1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_ipc0_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_ipc_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_rd_pend_v_ipc1_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"req_rd_pend_v_tnr0_y"        },
};

/*--------------------------------------------
	0x28c4 MIFC_RD_REQ_PEND2
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_REQ_PEND2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_tnr_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_ss_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_rd_pend_v_ss_c"          },
};

/*--------------------------------------------
	0x28c8 MIFC_WD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_wd_pend_v_ss_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_wd_pend_v_ss_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_wd_pend_v_tnr_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"req_wd_pend_v_tnr_c"         },
};

/*--------------------------------------------
	0x28cc MIFC_WD_REQ_PEND1
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_REQ_PEND1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_wd_pend_v_prew_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_wd_pend_v_prew_c"        },
};

/*--------------------------------------------
	0x28d0 MIFC_RD_CMD_PRI0_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_PRI0_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_s_v_mvi_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_s_v_mvi_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_s_v_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_s_v_prew_c"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pri_s_v_ipc0_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pri_s_v_ipc_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,24 ,"cmd_rd_pri_s_v_ipc1_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"cmd_rd_pri_s_v_tnr0_y"       },
};

/*--------------------------------------------
	0x28d4 MIFC_RD_CMD_PRI1_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RD_CMD_PRI1_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_s_v_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_s_v_ss_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_s_v_ss_c"         },
};

/*--------------------------------------------
	0x28d8 MIFC_WD_CMD_PRI0_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_WD_CMD_PRI0_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_s_v_ss_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_s_v_ss_c"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_wd_pri_s_v_tnr_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_wd_pri_s_v_tnr_c"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_wd_pri_s_v_prew_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_wd_pri_s_v_prew_c"       },
};

/*--------------------------------------------
	0x28dc MIFC_RESET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFC_RESET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"reset_mif_r_mvi_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"reset_mif_r_mvi_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"reset_mif_r_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"reset_mif_r_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"reset_mif_r_ipc0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"reset_mif_r_ipc_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,6  ,"reset_mif_r_ipc1_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,7  ,"reset_mif_r_tnr0_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"reset_mif_r_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"reset_mif_r_ss_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"reset_mif_r_ss_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,11 ,"reset_mif_w_ss_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"reset_mif_w_ss_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"reset_mif_w_tnr_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"reset_mif_w_tnr_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"reset_mif_w_prew_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"reset_mif_w_prew_c"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"reset_time_out_cnt"          },
};

/*--------------------------------------------
	0x3900 MIFD_RD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_r_ov_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_r_ov_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_rd_mif"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_rd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_rd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_rd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_rd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_rd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_rd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_rd_stv_cnt"           },
};

/*--------------------------------------------
	0x3904 MIFD_WD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_w_sm_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_w_sm_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_wd_mif"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_wd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_wd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_wd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_wd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_wd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_wd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_wd_stv_cnt"           },
};

/*--------------------------------------------
	0x3908 MIFD_RD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_v_ov_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_v_ov_c"           },
};

/*--------------------------------------------
	0x390c MIFD_WD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_v_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_v_sm_c"           },
};

/*--------------------------------------------
	0x3910 MIFD_RD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_ov_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_ov_c"           },
};

/*--------------------------------------------
	0x3914 MIFD_WD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_pri_v_scm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_pri_v_scm_c"          },
};

/*--------------------------------------------
	0x3918 MIFD_RD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_stv_v_ov_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_stv_v_ov_c"           },
};

/*--------------------------------------------
	0x391c MIFD_WD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_stv_v_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_stv_v_sm_c"           },
};

/*--------------------------------------------
	0x3920 MIFD_RD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pend_v_ov_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pend_v_ov_c"          },
};

/*--------------------------------------------
	0x3924 MIFD_WD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pend_v_sm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pend_v_sm_c"          },
};

/*--------------------------------------------
	0x3928 MIFD_RD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_ov_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_ov_c"        },
};

/*--------------------------------------------
	0x392c MIFD_RD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_rd_stride_v_ov_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_rd_stride_v_ov_c"    },
};

/*--------------------------------------------
	0x3930 MIFD_WD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_stride_v_sm_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_stride_v_sm_c"        },
};

/*--------------------------------------------
	0x3934 MIFD_WD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_wd_stride_v_sm_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_wd_stride_v_sm_c"    },
};

/*--------------------------------------------
	0x3938 MIFD_SADDR_RD_OV_Y_OV_C
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_SADDR_RD_OV_Y_OV_C[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_ov_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_ov_c"           },
};

/*--------------------------------------------
	0x393c MIFD_SADDR_WD_SM_YC
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_SADDR_WD_SM_YC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_wd_saddr_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_wd_saddr_sm_c"           },
};

/*--------------------------------------------
	0x3940 MIFD_SADDR_RD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_SADDR_RD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_ov_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_ov_c_msb4b"     },
};

/*--------------------------------------------
	0x3944 MIFD_SADDR_WD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_SADDR_WD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_wd_saddr_sm_y_msb4b"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_wd_saddr_sm_c_msb4b"     },
};

/*--------------------------------------------
	0x3948 MIFD_STATUS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fr_rd_valid_ov_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fr_rd_valid_ov_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"fr_wd_q_full_sm_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"fr_wd_q_full_sm_c"           },
};

/*--------------------------------------------
	0x394c MIFD_SADDR_PARAM_UPDATE0_M
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_SADDR_PARAM_UPDATE0_M[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,11 ,"register_update_address0_m"  },
};

/*--------------------------------------------
	0x3950 MIFD_RD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_8_ov_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_8_ov_c"     },
};

/*--------------------------------------------
	0x3954 MIFD_RD_BANK_8_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3958 MIFD_RD_BANK_2_ADDR0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x395c MIFD_RD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3960 MIFD_WD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_wd_bank_addr_8_sm_y"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_wd_bank_addr_8_sm_c"     },
};

/*--------------------------------------------
	0x3964 MIFD_WD_BANK_8_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3968 MIFD_WD_BANK_2_ADDR0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x396c MIFD_WD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x3970 MIFD_RD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_ov_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_ov_c"          },
};

/*--------------------------------------------
	0x3974 MIFD_WD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_wd_pend_v_sm_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_wd_pend_v_sm_c"          },
};

/*--------------------------------------------
	0x3978 MIFD_RD_CMD_PRI0_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RD_CMD_PRI0_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_s_v_ov_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_s_v_ov_c"         },
};

/*--------------------------------------------
	0x397c MIFD_WD_CMD_PRI0_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_WD_CMD_PRI0_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_wd_pri_s_v_sm_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_wd_pri_s_v_sm_c"         },
};

/*--------------------------------------------
	0x3980 MIFD_RESET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFD_RESET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"reset_mif_r_ov_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"reset_mif_r_ov_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"reset_mif_w_sm_y"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"reset_mif_w_sm_c"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"reset_time_out_cnt"          },
};

/*--------------------------------------------
	0x5f00 MIFF_RD_CTRL
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"block_req_r_osd_0"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"block_req_r_osd_1"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"block_req_r_osd_2"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"block_req_r_osd_3"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"block_req_r_cve_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"block_req_r_cve_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"disable_rd_mif"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,13 ,"load_rd_req_stv_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,14 ,"load_rd_req_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,15 ,"load_rd_cmd_saddr_v"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"load_rd_cmd_pend_v"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,17 ,"load_rd_cmd_pri_v"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,18 ,"load_rd_cmd_stride_v"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,19 ,"enable_rd_stv_cnt"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,21 ,"mrb_bank_mode"               },
};

/*--------------------------------------------
	0x5f04 MIFF_RD_CMD_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_CMD_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_v_osd_0"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_v_osd_1"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_v_osd_2"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_v_osd_3"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pri_v_cve_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pri_v_cve_c"          },
};

/*--------------------------------------------
	0x5f08 MIFF_RD_REQ_PRI0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_REQ_PRI0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_pri_v_osd_0"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_pri_v_osd_1"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_pri_v_osd_2"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_pri_v_osd_3"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_pri_v_cve_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_pri_v_cve_c"          },
};

/*--------------------------------------------
	0x5f0c MIFF_RD_REQ_STV0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_REQ_STV0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_stv_v_osd_0"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_stv_v_osd_1"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_stv_v_osd_2"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_stv_v_osd_3"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_stv_v_cve_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_stv_v_cve_c"          },
};

/*--------------------------------------------
	0x5f10 MIFF_RD_CMD_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_CMD_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pend_v_osd_0"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pend_v_osd_1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pend_v_osd_2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pend_v_osd_3"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pend_v_cve_y"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pend_v_cve_c"         },
};

/*--------------------------------------------
	0x5f14 MIFF_RD_CMD_STRIDE0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_CMD_STRIDE0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_stride_v_osd_0"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_stride_v_osd_1"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_stride_v_osd_2"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_stride_v_osd_3"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_stride_v_cve_y"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_stride_v_cve_c"       },
};

/*--------------------------------------------
	0x5f18 MIFF_RD_CMD_STRIDE_SET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_CMD_STRIDE_SET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"man_cmd_rd_stride_v_osd_0"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"man_cmd_rd_stride_v_osd_1"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"man_cmd_rd_stride_v_osd_2"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"man_cmd_rd_stride_v_osd_3"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"man_cmd_rd_stride_v_cve_y"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"man_cmd_rd_stride_v_cve_c"   },
};

/*--------------------------------------------
	0x5f1c MIFF_SADDR_RD_OSD_01
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_SADDR_RD_OSD_01[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_osd_0"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_osd_1"          },
};

/*--------------------------------------------
	0x5f20 MIFF_SADDR_RD_OSD_23
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_SADDR_RD_OSD_23[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_osd_2"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_osd_3"          },
};

/*--------------------------------------------
	0x5f24 MIFF_SADDR_RD_CVE_YC
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_SADDR_RD_CVE_YC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,0  ,"req_rd_saddr_cve_y"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,16 ,"req_rd_saddr_cve_c"          },
};

/*--------------------------------------------
	0x5f28 MIFF_SADDR_RD_EXT0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_SADDR_RD_EXT0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"req_rd_saddr_osd_0_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"req_rd_saddr_osd_1_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"req_rd_saddr_osd_2_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"req_rd_saddr_osd_3_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"req_rd_saddr_cve_y_msb4b"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"req_rd_saddr_cve_c_msb4b"    },
};

/*--------------------------------------------
	0x5f2c MIFF_STATUS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"fr_rd_valid_osd_0"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"fr_rd_valid_osd_1"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"fr_rd_valid_osd_2"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"fr_rd_valid_osd_3"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"fr_rd_valid_cve_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"fr_rd_valid_cve_c"           },
};

/*--------------------------------------------
	0x5f30 MIFF_RD_BANK_8_ADDR0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_BANK_8_ADDR0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"req_rd_bank_addr_8_osd_0"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"req_rd_bank_addr_8_osd_1"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"req_rd_bank_addr_8_osd_2"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"req_rd_bank_addr_8_osd_3"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,18 ,16 ,"req_rd_bank_addr_8_cve_y"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,22 ,20 ,"req_rd_bank_addr_8_cve_c"    },
};

/*--------------------------------------------
	0x5f34 MIFF_RD_BANK_8_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x5f38 MIFF_RD_BANK_2_ADDR0
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x5f3c MIFF_RD_BANK_2_ADDR1
--------------------------------------------*/
/* no field */

/*--------------------------------------------
	0x5f40 MIFF_RD_REQ_PEND0
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_REQ_PEND0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"req_rd_pend_v_osd_0"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"req_rd_pend_v_osd_1"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,16 ,"req_rd_pend_v_osd_2"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,24 ,"req_rd_pend_v_osd_3"         },
};

/*--------------------------------------------
	0x5f44 MIFF_RD_CMD_PRI0_S
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RD_CMD_PRI0_S[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"cmd_rd_pri_s_v_osd_0"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,4  ,"cmd_rd_pri_s_v_osd_1"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,8  ,"cmd_rd_pri_s_v_osd_2"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,12 ,"cmd_rd_pri_s_v_osd_3"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,16 ,"cmd_rd_pri_s_v_cve_y"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,23 ,20 ,"cmd_rd_pri_s_v_cve_c"        },
};

/*--------------------------------------------
	0x5f48 MIFF_RESET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_RESET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"reset_mif_r_osd_0"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"reset_mif_r_osd_1"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"reset_mif_r_osd_2"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,3  ,"reset_mif_r_osd_3"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"reset_mif_r_cve_y"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"reset_mif_r_cve_c"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"reset_time_out_cnt"          },
};

/*--------------------------------------------
	0x5f4c MIFF_SADDR_PARAM_UPDATE0_M
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_MIFF_SADDR_PARAM_UPDATE0_M[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"load"                        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,11 ,"register_update_address0_m"  },
};

DBG_REG_T gDbgRegMIF[] = {
	{ 0x0800 ,N_FLD(dbg_MIFA_RD_CTRL)                    ,"MIFA_RD_CTRL"                      ,dbg_MIFA_RD_CTRL                    },
	{ 0x0804 ,N_FLD(dbg_MIFA_WD_CTRL)                    ,"MIFA_WD_CTRL"                      ,dbg_MIFA_WD_CTRL                    },
	{ 0x0808 ,N_FLD(dbg_MIF_RD_SET_10B)                  ,"MIF_RD_SET_10B"                    ,dbg_MIF_RD_SET_10B                  },
	{ 0x080c ,N_FLD(dbg_MIF_WD_SET_10B)                  ,"MIF_WD_SET_10B"                    ,dbg_MIF_WD_SET_10B                  },
	{ 0x0810 ,N_FLD(dbg_MIFA_RD_CMD_PRI0)                ,"MIFA_RD_CMD_PRI0"                  ,dbg_MIFA_RD_CMD_PRI0                },
	{ 0x0814 ,N_FLD(dbg_MIFA_RD_CMD_PRI1)                ,"MIFA_RD_CMD_PRI1"                  ,dbg_MIFA_RD_CMD_PRI1                },
	{ 0x0818 ,N_FLD(dbg_MIFA_WD_CMD_PRI0)                ,"MIFA_WD_CMD_PRI0"                  ,dbg_MIFA_WD_CMD_PRI0                },
	{ 0x081c ,N_FLD(dbg_MIFA_RD_REQ_PRI0)                ,"MIFA_RD_REQ_PRI0"                  ,dbg_MIFA_RD_REQ_PRI0                },
	{ 0x0820 ,N_FLD(dbg_MIFA_RD_REQ_PRI1)                ,"MIFA_RD_REQ_PRI1"                  ,dbg_MIFA_RD_REQ_PRI1                },
	{ 0x0824 ,N_FLD(dbg_MIFA_WD_REQ_PRI0)                ,"MIFA_WD_REQ_PRI0"                  ,dbg_MIFA_WD_REQ_PRI0                },
	{ 0x0828 ,N_FLD(dbg_MIFA_RD_REQ_STV0)                ,"MIFA_RD_REQ_STV0"                  ,dbg_MIFA_RD_REQ_STV0                },
	{ 0x082c ,N_FLD(dbg_MIFA_RD_REQ_STV1)                ,"MIFA_RD_REQ_STV1"                  ,dbg_MIFA_RD_REQ_STV1                },
	{ 0x0830 ,N_FLD(dbg_MIFA_WD_REQ_STV0)                ,"MIFA_WD_REQ_STV0"                  ,dbg_MIFA_WD_REQ_STV0                },
	{ 0x0834 ,N_FLD(dbg_MIFA_RD_CMD_PEND0)               ,"MIFA_RD_CMD_PEND0"                 ,dbg_MIFA_RD_CMD_PEND0               },
	{ 0x0838 ,N_FLD(dbg_MIFA_RD_CMD_PEND1)               ,"MIFA_RD_CMD_PEND1"                 ,dbg_MIFA_RD_CMD_PEND1               },
	{ 0x083c ,N_FLD(dbg_MIFA_WD_CMD_PEND0)               ,"MIFA_WD_CMD_PEND0"                 ,dbg_MIFA_WD_CMD_PEND0               },
	{ 0x0840 ,N_FLD(dbg_MIFA_RD_CMD_STRIDE0)             ,"MIFA_RD_CMD_STRIDE0"               ,dbg_MIFA_RD_CMD_STRIDE0             },
	{ 0x0844 ,N_FLD(dbg_MIFA_RD_CMD_STRIDE1)             ,"MIFA_RD_CMD_STRIDE1"               ,dbg_MIFA_RD_CMD_STRIDE1             },
	{ 0x0848 ,N_FLD(dbg_MIFA_RD_CMD_STRIDE2)             ,"MIFA_RD_CMD_STRIDE2"               ,dbg_MIFA_RD_CMD_STRIDE2             },
	{ 0x084c ,N_FLD(dbg_MIFA_RD_CMD_STRIDE_SET)          ,"MIFA_RD_CMD_STRIDE_SET"            ,dbg_MIFA_RD_CMD_STRIDE_SET          },
	{ 0x0850 ,N_FLD(dbg_MIFA_WD_CMD_STRIDE0)             ,"MIFA_WD_CMD_STRIDE0"               ,dbg_MIFA_WD_CMD_STRIDE0             },
	{ 0x0854 ,N_FLD(dbg_MIFA_WD_CMD_STRIDE_SET)          ,"MIFA_WD_CMD_STRIDE_SET"            ,dbg_MIFA_WD_CMD_STRIDE_SET          },
	{ 0x0858 ,N_FLD(dbg_MIFA_SADDR_RD_MVI_Y_MVI_C)       ,"MIFA_SADDR_RD_MVI_Y_MVI_C"         ,dbg_MIFA_SADDR_RD_MVI_Y_MVI_C       },
	{ 0x085c ,N_FLD(dbg_MIFA_SADDR_RD_PREW_Y)            ,"MIFA_SADDR_RD_PREW_Y"              ,dbg_MIFA_SADDR_RD_PREW_Y            },
	{ 0x0860 ,N_FLD(dbg_MIFA_SADDR_RD_PREW_C)            ,"MIFA_SADDR_RD_PREW_C"              ,dbg_MIFA_SADDR_RD_PREW_C            },
	{ 0x0864 ,N_FLD(dbg_MIFA_SADDR_RD_IPC0_Y)            ,"MIFA_SADDR_RD_IPC0_Y"              ,dbg_MIFA_SADDR_RD_IPC0_Y            },
	{ 0x0868 ,N_FLD(dbg_MIFA_SADDR_RD_IPC_C)             ,"MIFA_SADDR_RD_IPC_C"               ,dbg_MIFA_SADDR_RD_IPC_C             },
	{ 0x086c ,N_FLD(dbg_MIFA_SADDR_RD_IPC1_Y)            ,"MIFA_SADDR_RD_IPC1_Y"              ,dbg_MIFA_SADDR_RD_IPC1_Y            },
	{ 0x0870 ,N_FLD(dbg_MIFA_SADDR_RD_TNR0_Y)            ,"MIFA_SADDR_RD_TNR0_Y"              ,dbg_MIFA_SADDR_RD_TNR0_Y            },
	{ 0x0874 ,N_FLD(dbg_MIFA_SADDR_RD_TNR_C)             ,"MIFA_SADDR_RD_TNR_C"               ,dbg_MIFA_SADDR_RD_TNR_C             },
	{ 0x0878 ,N_FLD(dbg_MIFA_SADDR_RD_TNR1_Y)            ,"MIFA_SADDR_RD_TNR1_Y"              ,dbg_MIFA_SADDR_RD_TNR1_Y            },
	{ 0x087c ,N_FLD(dbg_MIFA_SADDR_WD_TNR_Y)             ,"MIFA_SADDR_WD_TNR_Y"               ,dbg_MIFA_SADDR_WD_TNR_Y             },
	{ 0x0880 ,N_FLD(dbg_MIFA_SADDR_WD_TNR_C)             ,"MIFA_SADDR_WD_TNR_C"               ,dbg_MIFA_SADDR_WD_TNR_C             },
	{ 0x0884 ,N_FLD(dbg_MIFA_SADDR_WD_PREW_Y)            ,"MIFA_SADDR_WD_PREW_Y"              ,dbg_MIFA_SADDR_WD_PREW_Y            },
	{ 0x0888 ,N_FLD(dbg_MIFA_SADDR_WD_PREW_C)            ,"MIFA_SADDR_WD_PREW_C"              ,dbg_MIFA_SADDR_WD_PREW_C            },
	{ 0x088c ,N_FLD(dbg_MIFA_SADDR_RD_DL_Y)              ,"MIFA_SADDR_RD_DL_Y"                ,dbg_MIFA_SADDR_RD_DL_Y              },
	{ 0x0890 ,N_FLD(dbg_MIFA_SADDR_RD_DL_C)              ,"MIFA_SADDR_RD_DL_C"                ,dbg_MIFA_SADDR_RD_DL_C              },
	{ 0x0894 ,N_FLD(dbg_MIFA_SADDR_RD_DR_Y)              ,"MIFA_SADDR_RD_DR_Y"                ,dbg_MIFA_SADDR_RD_DR_Y              },
	{ 0x0898 ,N_FLD(dbg_MIFA_SADDR_RD_DR_C)              ,"MIFA_SADDR_RD_DR_C"                ,dbg_MIFA_SADDR_RD_DR_C              },
	{ 0x089c ,N_FLD(dbg_MIFA_SADDR_WD_DL_Y)              ,"MIFA_SADDR_WD_DL_Y"                ,dbg_MIFA_SADDR_WD_DL_Y              },
	{ 0x08a0 ,N_FLD(dbg_MIFA_SADDR_WD_DL_C)              ,"MIFA_SADDR_WD_DL_C"                ,dbg_MIFA_SADDR_WD_DL_C              },
	{ 0x08a4 ,N_FLD(dbg_MIFA_SADDR_WD_DR_Y)              ,"MIFA_SADDR_WD_DR_Y"                ,dbg_MIFA_SADDR_WD_DR_Y              },
	{ 0x08a8 ,N_FLD(dbg_MIFA_SADDR_WD_DR_C)              ,"MIFA_SADDR_WD_DR_C"                ,dbg_MIFA_SADDR_WD_DR_C              },
	{ 0x08ac ,N_FLD(dbg_MIFA_SADDR_RD_EXT0)              ,"MIFA_SADDR_RD_EXT0"                ,dbg_MIFA_SADDR_RD_EXT0              },
	{ 0x08b0 ,N_FLD(dbg_MIFA_SADDR_RD_EXT1)              ,"MIFA_SADDR_RD_EXT1"                ,dbg_MIFA_SADDR_RD_EXT1              },
	{ 0x08b4 ,N_FLD(dbg_MIFA_SADDR_RD_EXT2)              ,"MIFA_SADDR_RD_EXT2"                ,dbg_MIFA_SADDR_RD_EXT2              },
	{ 0x08b8 ,N_FLD(dbg_MIFA_SADDR_WD_EXT0)              ,"MIFA_SADDR_WD_EXT0"                ,dbg_MIFA_SADDR_WD_EXT0              },
	{ 0x08bc ,N_FLD(dbg_MIFA_RD_DR_DL_EXT)               ,"MIFA_RD_DR_DL_EXT"                 ,dbg_MIFA_RD_DR_DL_EXT               },
	{ 0x08c0 ,N_FLD(dbg_MIFA_WD_DR_DL_EXT)               ,"MIFA_WD_DR_DL_EXT"                 ,dbg_MIFA_WD_DR_DL_EXT               },
	{ 0x08c4 ,N_FLD(dbg_MIFA_STATUS)                     ,"MIFA_STATUS"                       ,dbg_MIFA_STATUS                     },
	{ 0x08c8 ,N_FLD(dbg_MIFA_SADDR_PARAM_UPDATE0_M)      ,"MIFA_SADDR_PARAM_UPDATE0_M"        ,dbg_MIFA_SADDR_PARAM_UPDATE0_M      },
	{ 0x08cc ,N_FLD(dbg_MIFA_SADDR_PARAM_UPDATE0_M1)     ,"MIFA_SADDR_PARAM_UPDATE0_M1"       ,dbg_MIFA_SADDR_PARAM_UPDATE0_M1     },
	{ 0x08d0 ,N_FLD(dbg_MIFA_RD_BANK_8_ADDR0)            ,"MIFA_RD_BANK_8_ADDR0"              ,dbg_MIFA_RD_BANK_8_ADDR0            },
	{ 0x08d4 ,N_FLD(dbg_MIFA_RD_BANK_8_ADDR1)            ,"MIFA_RD_BANK_8_ADDR1"              ,dbg_MIFA_RD_BANK_8_ADDR1            },
	{ 0x08d8 ,N_FLD(dbg_MIFA_RD_BANK_2_ADDR0)            ,"MIFA_RD_BANK_2_ADDR0"              ,dbg_MIFA_RD_BANK_2_ADDR0            },
	{ 0x08dc ,N_FLD(dbg_MIFA_RD_BANK_2_ADDR1)            ,"MIFA_RD_BANK_2_ADDR1"              ,dbg_MIFA_RD_BANK_2_ADDR1            },
	{ 0x08e0 ,N_FLD(dbg_MIFA_WD_BANK_8_ADDR0)            ,"MIFA_WD_BANK_8_ADDR0"              ,dbg_MIFA_WD_BANK_8_ADDR0            },
	{ 0x08e4 ,0                                          ,"MIFA_WD_BANK_8_ADDR1"              ,NULL                                },
	{ 0x08e8 ,N_FLD(dbg_MIFA_WD_BANK_2_ADDR0)            ,"MIFA_WD_BANK_2_ADDR0"              ,dbg_MIFA_WD_BANK_2_ADDR0            },
	{ 0x08ec ,0                                          ,"MIFA_WD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x08f0 ,N_FLD(dbg_MIFA_LSB_SWITCH)                 ,"MIFA_LSB_SWITCH"                   ,dbg_MIFA_LSB_SWITCH                 },
	{ 0x08f4 ,N_FLD(dbg_MIFA_RD_REQ_PEND0)               ,"MIFA_RD_REQ_PEND0"                 ,dbg_MIFA_RD_REQ_PEND0               },
	{ 0x08f8 ,N_FLD(dbg_MIFA_RD_REQ_PEND1)               ,"MIFA_RD_REQ_PEND1"                 ,dbg_MIFA_RD_REQ_PEND1               },
	{ 0x08fc ,N_FLD(dbg_MIFA_RD_REQ_PEND2)               ,"MIFA_RD_REQ_PEND2"                 ,dbg_MIFA_RD_REQ_PEND2               },
	{ 0x0900 ,N_FLD(dbg_MIFA_WD_REQ_PEND0)               ,"MIFA_WD_REQ_PEND0"                 ,dbg_MIFA_WD_REQ_PEND0               },
	{ 0x0904 ,N_FLD(dbg_MIFA_RD_CMD_PRI0_S)              ,"MIFA_RD_CMD_PRI0_S"                ,dbg_MIFA_RD_CMD_PRI0_S              },
	{ 0x0908 ,N_FLD(dbg_MIFA_RD_CMD_PRI1_S)              ,"MIFA_RD_CMD_PRI1_S"                ,dbg_MIFA_RD_CMD_PRI1_S              },
	{ 0x090c ,N_FLD(dbg_MIFA_WD_CMD_PRI0_S)              ,"MIFA_WD_CMD_PRI0_S"                ,dbg_MIFA_WD_CMD_PRI0_S              },
	{ 0x0910 ,N_FLD(dbg_MIFA_RESET)                      ,"MIFA_RESET"                        ,dbg_MIFA_RESET                      },
	{ 0x1b00 ,N_FLD(dbg_MIFB_RD_CTRL)                    ,"MIFB_RD_CTRL"                      ,dbg_MIFB_RD_CTRL                    },
	{ 0x1b04 ,N_FLD(dbg_MIFB_WD_CTRL)                    ,"MIFB_WD_CTRL"                      ,dbg_MIFB_WD_CTRL                    },
	{ 0x1b08 ,N_FLD(dbg_MIFB_RD_SET_10B)                 ,"MIFB_RD_SET_10B"                   ,dbg_MIFB_RD_SET_10B                 },
	{ 0x1b0c ,N_FLD(dbg_MIFB_WD_SET_10B)                 ,"MIFB_WD_SET_10B"                   ,dbg_MIFB_WD_SET_10B                 },
	{ 0x1b10 ,N_FLD(dbg_MIFB_RD_CMD_PRI0)                ,"MIFB_RD_CMD_PRI0"                  ,dbg_MIFB_RD_CMD_PRI0                },
	{ 0x1b14 ,N_FLD(dbg_MIFB_WD_CMD_PRI0)                ,"MIFB_WD_CMD_PRI0"                  ,dbg_MIFB_WD_CMD_PRI0                },
	{ 0x1b18 ,N_FLD(dbg_MIFB_RD_REQ_PRI0)                ,"MIFB_RD_REQ_PRI0"                  ,dbg_MIFB_RD_REQ_PRI0                },
	{ 0x1b1c ,N_FLD(dbg_MIFB_WD_REQ_PRI0)                ,"MIFB_WD_REQ_PRI0"                  ,dbg_MIFB_WD_REQ_PRI0                },
	{ 0x1b20 ,N_FLD(dbg_MIFB_RD_REQ_STV0)                ,"MIFB_RD_REQ_STV0"                  ,dbg_MIFB_RD_REQ_STV0                },
	{ 0x1b24 ,N_FLD(dbg_MIFB_WD_REQ_STV0)                ,"MIFB_WD_REQ_STV0"                  ,dbg_MIFB_WD_REQ_STV0                },
	{ 0x1b28 ,N_FLD(dbg_MIFB_RD_CMD_PEND0)               ,"MIFB_RD_CMD_PEND0"                 ,dbg_MIFB_RD_CMD_PEND0               },
	{ 0x1b2c ,N_FLD(dbg_MIFB_WD_CMD_PEND0)               ,"MIFB_WD_CMD_PEND0"                 ,dbg_MIFB_WD_CMD_PEND0               },
	{ 0x1b30 ,N_FLD(dbg_MIFB_RD_CMD_STRIDE0)             ,"MIFB_RD_CMD_STRIDE0"               ,dbg_MIFB_RD_CMD_STRIDE0             },
	{ 0x1b34 ,N_FLD(dbg_MIFB_RD_CMD_STRIDE_SET)          ,"MIFB_RD_CMD_STRIDE_SET"            ,dbg_MIFB_RD_CMD_STRIDE_SET          },
	{ 0x1b38 ,N_FLD(dbg_MIFB_WD_CMD_STRIDE0)             ,"MIFB_WD_CMD_STRIDE0"               ,dbg_MIFB_WD_CMD_STRIDE0             },
	{ 0x1b3c ,N_FLD(dbg_MIFB_WD_CMD_STRIDE_SET)          ,"MIFB_WD_CMD_STRIDE_SET"            ,dbg_MIFB_WD_CMD_STRIDE_SET          },
	{ 0x1b40 ,N_FLD(dbg_MIFB_SADDR_RD_OVM_Y)             ,"MIFB_SADDR_RD_OVM_Y"               ,dbg_MIFB_SADDR_RD_OVM_Y             },
	{ 0x1b44 ,N_FLD(dbg_MIFB_SADDR_RD_OVM_C)             ,"MIFB_SADDR_RD_OVM_C"               ,dbg_MIFB_SADDR_RD_OVM_C             },
	{ 0x1b48 ,N_FLD(dbg_MIFB_SADDR_RD_OVS_Y_OVS_C)       ,"MIFB_SADDR_RD_OVS_Y_OVS_C"         ,dbg_MIFB_SADDR_RD_OVS_Y_OVS_C       },
	{ 0x1b4c ,N_FLD(dbg_MIFB_SADDR_WD_SM_Y)              ,"MIFB_SADDR_WD_SM_Y"                ,dbg_MIFB_SADDR_WD_SM_Y              },
	{ 0x1b50 ,N_FLD(dbg_MIFB_SADDR_WD_SM_C)              ,"MIFB_SADDR_WD_SM_C"                ,dbg_MIFB_SADDR_WD_SM_C              },
	{ 0x1b54 ,N_FLD(dbg_MIFB_SADDR_RD_EXT0)              ,"MIFB_SADDR_RD_EXT0"                ,dbg_MIFB_SADDR_RD_EXT0              },
	{ 0x1b58 ,N_FLD(dbg_MIFB_SADDR_WD_EXT0)              ,"MIFB_SADDR_WD_EXT0"                ,dbg_MIFB_SADDR_WD_EXT0              },
	{ 0x1b5c ,N_FLD(dbg_MIFB_STATUS)                     ,"MIFB_STATUS"                       ,dbg_MIFB_STATUS                     },
	{ 0x1b60 ,N_FLD(dbg_MIFB_SADDR_PARAM_UPDATE0_M)      ,"MIFB_SADDR_PARAM_UPDATE0_M"        ,dbg_MIFB_SADDR_PARAM_UPDATE0_M      },
	{ 0x1b64 ,N_FLD(dbg_MIFB_RD_BANK_8_ADDR0)            ,"MIFB_RD_BANK_8_ADDR0"              ,dbg_MIFB_RD_BANK_8_ADDR0            },
	{ 0x1b68 ,0                                          ,"MIFB_RD_BANK_8_ADDR1"              ,NULL                                },
	{ 0x1b6c ,N_FLD(dbg_MIFB_RD_BANK_2_ADDR0)            ,"MIFB_RD_BANK_2_ADDR0"              ,dbg_MIFB_RD_BANK_2_ADDR0            },
	{ 0x1b70 ,0                                          ,"MIFB_RD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x1b74 ,N_FLD(dbg_MIFB_WD_BANK_8_ADDR0)            ,"MIFB_WD_BANK_8_ADDR0"              ,dbg_MIFB_WD_BANK_8_ADDR0            },
	{ 0x1b78 ,0                                          ,"MIFB_WD_BANK_8_ADDR1"              ,NULL                                },
	{ 0x1b7c ,N_FLD(dbg_MIFB_WD_BANK_2_ADDR0)            ,"MIFB_WD_BANK_2_ADDR0"              ,dbg_MIFB_WD_BANK_2_ADDR0            },
	{ 0x1b80 ,0                                          ,"MIFB_WD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x1b84 ,N_FLD(dbg_MIFB_LSB_SWITCH)                 ,"MIFB_LSB_SWITCH"                   ,dbg_MIFB_LSB_SWITCH                 },
	{ 0x1b88 ,0                                          ,"MIFB_RD_REQ_PEND0"                 ,NULL                                },
	{ 0x1b8c ,N_FLD(dbg_MIFB_WD_REQ_PEND0)               ,"MIFB_WD_REQ_PEND0"                 ,dbg_MIFB_WD_REQ_PEND0               },
	{ 0x1b90 ,N_FLD(dbg_MIFB_RD_CMD_PRI00_S)             ,"MIFB_RD_CMD_PRI00_S"               ,dbg_MIFB_RD_CMD_PRI00_S             },
	{ 0x1b94 ,N_FLD(dbg_MIFB_WD_CMD_PRI00_S)             ,"MIFB_WD_CMD_PRI00_S"               ,dbg_MIFB_WD_CMD_PRI00_S             },
	{ 0x1b98 ,N_FLD(dbg_MIFB_RESET)                      ,"MIFB_RESET"                        ,dbg_MIFB_RESET                      },
	{ 0x2800 ,N_FLD(dbg_MIFC_RD_CTRL)                    ,"MIFC_RD_CTRL"                      ,dbg_MIFC_RD_CTRL                    },
	{ 0x2804 ,N_FLD(dbg_MIFC_WD_CTRL)                    ,"MIFC_WD_CTRL"                      ,dbg_MIFC_WD_CTRL                    },
	{ 0x2808 ,N_FLD(dbg_MIFC_RD_CMD_PRI0)                ,"MIFC_RD_CMD_PRI0"                  ,dbg_MIFC_RD_CMD_PRI0                },
	{ 0x280c ,N_FLD(dbg_MIFC_RD_CMD_PRI1)                ,"MIFC_RD_CMD_PRI1"                  ,dbg_MIFC_RD_CMD_PRI1                },
	{ 0x2810 ,N_FLD(dbg_MIFC_WD_CMD_PRI0)                ,"MIFC_WD_CMD_PRI0"                  ,dbg_MIFC_WD_CMD_PRI0                },
	{ 0x2814 ,N_FLD(dbg_MIFC_RD_REQ_PRI0)                ,"MIFC_RD_REQ_PRI0"                  ,dbg_MIFC_RD_REQ_PRI0                },
	{ 0x2818 ,N_FLD(dbg_MIFC_RD_REQ_PRI1)                ,"MIFC_RD_REQ_PRI1"                  ,dbg_MIFC_RD_REQ_PRI1                },
	{ 0x281c ,N_FLD(dbg_MIFC_WD_REQ_PRI0)                ,"MIFC_WD_REQ_PRI0"                  ,dbg_MIFC_WD_REQ_PRI0                },
	{ 0x2820 ,N_FLD(dbg_MIFC_RD_REQ_STV0)                ,"MIFC_RD_REQ_STV0"                  ,dbg_MIFC_RD_REQ_STV0                },
	{ 0x2824 ,N_FLD(dbg_MIFC_RD_REQ_STV1)                ,"MIFC_RD_REQ_STV1"                  ,dbg_MIFC_RD_REQ_STV1                },
	{ 0x2828 ,N_FLD(dbg_MIFC_WD_REQ_STV0)                ,"MIFC_WD_REQ_STV0"                  ,dbg_MIFC_WD_REQ_STV0                },
	{ 0x282c ,N_FLD(dbg_MIFC_RD_CMD_PEND0)               ,"MIFC_RD_CMD_PEND0"                 ,dbg_MIFC_RD_CMD_PEND0               },
	{ 0x2830 ,N_FLD(dbg_MIFC_RD_CMD_PEND1)               ,"MIFC_RD_CMD_PEND1"                 ,dbg_MIFC_RD_CMD_PEND1               },
	{ 0x2834 ,N_FLD(dbg_MIFC_WD_CMD_PEND0)               ,"MIFC_WD_CMD_PEND0"                 ,dbg_MIFC_WD_CMD_PEND0               },
	{ 0x2838 ,N_FLD(dbg_MIFC_RD_CMD_STRIDE0)             ,"MIFC_RD_CMD_STRIDE0"               ,dbg_MIFC_RD_CMD_STRIDE0             },
	{ 0x283c ,N_FLD(dbg_MIFC_RD_CMD_STRIDE1)             ,"MIFC_RD_CMD_STRIDE1"               ,dbg_MIFC_RD_CMD_STRIDE1             },
	{ 0x2840 ,N_FLD(dbg_MIFC_RD_CMD_STRIDE_SET)          ,"MIFC_RD_CMD_STRIDE_SET"            ,dbg_MIFC_RD_CMD_STRIDE_SET          },
	{ 0x2844 ,N_FLD(dbg_MIFC_WD_CMD_STRIDE0)             ,"MIFC_WD_CMD_STRIDE0"               ,dbg_MIFC_WD_CMD_STRIDE0             },
	{ 0x2848 ,N_FLD(dbg_MIFC_WD_CMD_STRIDE_SET)          ,"MIFC_WD_CMD_STRIDE_SET"            ,dbg_MIFC_WD_CMD_STRIDE_SET          },
	{ 0x284c ,N_FLD(dbg_MIFC_SADDR_RD_MVI_Y_MVI_C)       ,"MIFC_SADDR_RD_MVI_Y_MVI_C"         ,dbg_MIFC_SADDR_RD_MVI_Y_MVI_C       },
	{ 0x2850 ,N_FLD(dbg_MIFC_SADDR_RD_PREW_Y_PREW_C)     ,"MIFC_SADDR_RD_PREW_Y_PREW_C"       ,dbg_MIFC_SADDR_RD_PREW_Y_PREW_C     },
	{ 0x2854 ,N_FLD(dbg_MIFC_SADDR_RD_IPC0_Y_IPC_C)      ,"MIFC_SADDR_RD_IPC0_Y_IPC_C"        ,dbg_MIFC_SADDR_RD_IPC0_Y_IPC_C      },
	{ 0x2858 ,N_FLD(dbg_MIFC_SADDR_RD_IPC1_Y_TNR0_Y)     ,"MIFC_SADDR_RD_IPC1_Y_TNR0_Y"       ,dbg_MIFC_SADDR_RD_IPC1_Y_TNR0_Y     },
	{ 0x285c ,N_FLD(dbg_MIFC_SADDR_RD_SS_Y_SS_C)         ,"MIFC_SADDR_RD_SS_Y_SS_C"           ,dbg_MIFC_SADDR_RD_SS_Y_SS_C         },
	{ 0x2860 ,N_FLD(dbg_MIFC_SADDR_RD_TNR_C)             ,"MIFC_SADDR_RD_TNR_C"               ,dbg_MIFC_SADDR_RD_TNR_C             },
	{ 0x2864 ,N_FLD(dbg_MIFC_SADDR_WD_SS_Y_SS_C)         ,"MIFC_SADDR_WD_SS_Y_SS_C"           ,dbg_MIFC_SADDR_WD_SS_Y_SS_C         },
	{ 0x2868 ,N_FLD(dbg_MIFC_SADDR_WD_TNR_Y_TNR_C)       ,"MIFC_SADDR_WD_TNR_Y_TNR_C"         ,dbg_MIFC_SADDR_WD_TNR_Y_TNR_C       },
	{ 0x286c ,N_FLD(dbg_MIFC_SADDR_WD_PREW_Y_PREW_C)     ,"MIFC_SADDR_WD_PREW_Y_PREW_C"       ,dbg_MIFC_SADDR_WD_PREW_Y_PREW_C     },
	{ 0x2870 ,N_FLD(dbg_MIFC_SADDR_RD_DL_Y_DL_C)         ,"MIFC_SADDR_RD_DL_Y_DL_C"           ,dbg_MIFC_SADDR_RD_DL_Y_DL_C         },
	{ 0x2874 ,N_FLD(dbg_MIFC_SADDR_RD_DR_Y_DR_C)         ,"MIFC_SADDR_RD_DR_Y_DR_C"           ,dbg_MIFC_SADDR_RD_DR_Y_DR_C         },
	{ 0x2878 ,N_FLD(dbg_MIFC_SADDR_WD_DL_Y_DL_C)         ,"MIFC_SADDR_WD_DL_Y_DL_C"           ,dbg_MIFC_SADDR_WD_DL_Y_DL_C         },
	{ 0x287c ,N_FLD(dbg_MIFC_SADDR_WD_DR_Y_DR_C)         ,"MIFC_SADDR_WD_DR_Y_DR_C"           ,dbg_MIFC_SADDR_WD_DR_Y_DR_C         },
	{ 0x2880 ,N_FLD(dbg_MIFC_SADDR_RD_EXT0)              ,"MIFC_SADDR_RD_EXT0"                ,dbg_MIFC_SADDR_RD_EXT0              },
	{ 0x2884 ,N_FLD(dbg_MIFC_SADDR_RD_EXT1)              ,"MIFC_SADDR_RD_EXT1"                ,dbg_MIFC_SADDR_RD_EXT1              },
	{ 0x2888 ,N_FLD(dbg_MIFC_SADDR_WD_EXT0)              ,"MIFC_SADDR_WD_EXT0"                ,dbg_MIFC_SADDR_WD_EXT0              },
	{ 0x288c ,N_FLD(dbg_MIFC_RD_DR_DL_EXT)               ,"MIFC_RD_DR_DL_EXT"                 ,dbg_MIFC_RD_DR_DL_EXT               },
	{ 0x2890 ,N_FLD(dbg_MIFC_WD_DR_DL_EXT)               ,"MIFC_WD_DR_DL_EXT"                 ,dbg_MIFC_WD_DR_DL_EXT               },
	{ 0x2894 ,N_FLD(dbg_MIFC_STATUS)                     ,"MIFC_STATUS"                       ,dbg_MIFC_STATUS                     },
	{ 0x2898 ,N_FLD(dbg_MIFC_SADDR_PARAM_UPDATE0_M)      ,"MIFC_SADDR_PARAM_UPDATE0_M"        ,dbg_MIFC_SADDR_PARAM_UPDATE0_M      },
	{ 0x289c ,N_FLD(dbg_MIFC_RD_BANK_8_ADDR0)            ,"MIFC_RD_BANK_8_ADDR0"              ,dbg_MIFC_RD_BANK_8_ADDR0            },
	{ 0x28a0 ,N_FLD(dbg_MIFC_RD_BANK_8_ADDR1)            ,"MIFC_RD_BANK_8_ADDR1"              ,dbg_MIFC_RD_BANK_8_ADDR1            },
	{ 0x28a4 ,0                                          ,"MIFC_RD_BANK_2_ADDR0"              ,NULL                                },
	{ 0x28a8 ,0                                          ,"MIFC_RD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x28ac ,N_FLD(dbg_MIFC_WD_BANK_8_ADDR0)            ,"MIFC_WD_BANK_8_ADDR0"              ,dbg_MIFC_WD_BANK_8_ADDR0            },
	{ 0x28b0 ,0                                          ,"MIFC_WD_BANK_8_ADDR1"              ,NULL                                },
	{ 0x28b4 ,0                                          ,"MIFC_WD_BANK_2_ADDR0"              ,NULL                                },
	{ 0x28b8 ,0                                          ,"MIFC_WD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x28bc ,N_FLD(dbg_MIFC_RD_REQ_PEND0)               ,"MIFC_RD_REQ_PEND0"                 ,dbg_MIFC_RD_REQ_PEND0               },
	{ 0x28c0 ,N_FLD(dbg_MIFC_RD_REQ_PEND1)               ,"MIFC_RD_REQ_PEND1"                 ,dbg_MIFC_RD_REQ_PEND1               },
	{ 0x28c4 ,N_FLD(dbg_MIFC_RD_REQ_PEND2)               ,"MIFC_RD_REQ_PEND2"                 ,dbg_MIFC_RD_REQ_PEND2               },
	{ 0x28c8 ,N_FLD(dbg_MIFC_WD_REQ_PEND0)               ,"MIFC_WD_REQ_PEND0"                 ,dbg_MIFC_WD_REQ_PEND0               },
	{ 0x28cc ,N_FLD(dbg_MIFC_WD_REQ_PEND1)               ,"MIFC_WD_REQ_PEND1"                 ,dbg_MIFC_WD_REQ_PEND1               },
	{ 0x28d0 ,N_FLD(dbg_MIFC_RD_CMD_PRI0_S)              ,"MIFC_RD_CMD_PRI0_S"                ,dbg_MIFC_RD_CMD_PRI0_S              },
	{ 0x28d4 ,N_FLD(dbg_MIFC_RD_CMD_PRI1_S)              ,"MIFC_RD_CMD_PRI1_S"                ,dbg_MIFC_RD_CMD_PRI1_S              },
	{ 0x28d8 ,N_FLD(dbg_MIFC_WD_CMD_PRI0_S)              ,"MIFC_WD_CMD_PRI0_S"                ,dbg_MIFC_WD_CMD_PRI0_S              },
	{ 0x28dc ,N_FLD(dbg_MIFC_RESET)                      ,"MIFC_RESET"                        ,dbg_MIFC_RESET                      },
	{ 0x3900 ,N_FLD(dbg_MIFD_RD_CTRL)                    ,"MIFD_RD_CTRL"                      ,dbg_MIFD_RD_CTRL                    },
	{ 0x3904 ,N_FLD(dbg_MIFD_WD_CTRL)                    ,"MIFD_WD_CTRL"                      ,dbg_MIFD_WD_CTRL                    },
	{ 0x3908 ,N_FLD(dbg_MIFD_RD_CMD_PRI0)                ,"MIFD_RD_CMD_PRI0"                  ,dbg_MIFD_RD_CMD_PRI0                },
	{ 0x390c ,N_FLD(dbg_MIFD_WD_CMD_PRI0)                ,"MIFD_WD_CMD_PRI0"                  ,dbg_MIFD_WD_CMD_PRI0                },
	{ 0x3910 ,N_FLD(dbg_MIFD_RD_REQ_PRI0)                ,"MIFD_RD_REQ_PRI0"                  ,dbg_MIFD_RD_REQ_PRI0                },
	{ 0x3914 ,N_FLD(dbg_MIFD_WD_REQ_PRI0)                ,"MIFD_WD_REQ_PRI0"                  ,dbg_MIFD_WD_REQ_PRI0                },
	{ 0x3918 ,N_FLD(dbg_MIFD_RD_REQ_STV0)                ,"MIFD_RD_REQ_STV0"                  ,dbg_MIFD_RD_REQ_STV0                },
	{ 0x391c ,N_FLD(dbg_MIFD_WD_REQ_STV0)                ,"MIFD_WD_REQ_STV0"                  ,dbg_MIFD_WD_REQ_STV0                },
	{ 0x3920 ,N_FLD(dbg_MIFD_RD_CMD_PEND0)               ,"MIFD_RD_CMD_PEND0"                 ,dbg_MIFD_RD_CMD_PEND0               },
	{ 0x3924 ,N_FLD(dbg_MIFD_WD_CMD_PEND0)               ,"MIFD_WD_CMD_PEND0"                 ,dbg_MIFD_WD_CMD_PEND0               },
	{ 0x3928 ,N_FLD(dbg_MIFD_RD_CMD_STRIDE0)             ,"MIFD_RD_CMD_STRIDE0"               ,dbg_MIFD_RD_CMD_STRIDE0             },
	{ 0x392c ,N_FLD(dbg_MIFD_RD_CMD_STRIDE_SET)          ,"MIFD_RD_CMD_STRIDE_SET"            ,dbg_MIFD_RD_CMD_STRIDE_SET          },
	{ 0x3930 ,N_FLD(dbg_MIFD_WD_CMD_STRIDE0)             ,"MIFD_WD_CMD_STRIDE0"               ,dbg_MIFD_WD_CMD_STRIDE0             },
	{ 0x3934 ,N_FLD(dbg_MIFD_WD_CMD_STRIDE_SET)          ,"MIFD_WD_CMD_STRIDE_SET"            ,dbg_MIFD_WD_CMD_STRIDE_SET          },
	{ 0x3938 ,N_FLD(dbg_MIFD_SADDR_RD_OV_Y_OV_C)         ,"MIFD_SADDR_RD_OV_Y_OV_C"           ,dbg_MIFD_SADDR_RD_OV_Y_OV_C         },
	{ 0x393c ,N_FLD(dbg_MIFD_SADDR_WD_SM_YC)             ,"MIFD_SADDR_WD_SM_YC"               ,dbg_MIFD_SADDR_WD_SM_YC             },
	{ 0x3940 ,N_FLD(dbg_MIFD_SADDR_RD_EXT0)              ,"MIFD_SADDR_RD_EXT0"                ,dbg_MIFD_SADDR_RD_EXT0              },
	{ 0x3944 ,N_FLD(dbg_MIFD_SADDR_WD_EXT0)              ,"MIFD_SADDR_WD_EXT0"                ,dbg_MIFD_SADDR_WD_EXT0              },
	{ 0x3948 ,N_FLD(dbg_MIFD_STATUS)                     ,"MIFD_STATUS"                       ,dbg_MIFD_STATUS                     },
	{ 0x394c ,N_FLD(dbg_MIFD_SADDR_PARAM_UPDATE0_M)      ,"MIFD_SADDR_PARAM_UPDATE0_M"        ,dbg_MIFD_SADDR_PARAM_UPDATE0_M      },
	{ 0x3950 ,N_FLD(dbg_MIFD_RD_BANK_8_ADDR0)            ,"MIFD_RD_BANK_8_ADDR0"              ,dbg_MIFD_RD_BANK_8_ADDR0            },
	{ 0x3954 ,0                                          ,"MIFD_RD_BANK_8_ADDR1"              ,NULL                                },
	{ 0x3958 ,0                                          ,"MIFD_RD_BANK_2_ADDR0"              ,NULL                                },
	{ 0x395c ,0                                          ,"MIFD_RD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x3960 ,N_FLD(dbg_MIFD_WD_BANK_8_ADDR0)            ,"MIFD_WD_BANK_8_ADDR0"              ,dbg_MIFD_WD_BANK_8_ADDR0            },
	{ 0x3964 ,0                                          ,"MIFD_WD_BANK_8_ADDR1"              ,NULL                                },
	{ 0x3968 ,0                                          ,"MIFD_WD_BANK_2_ADDR0"              ,NULL                                },
	{ 0x396c ,0                                          ,"MIFD_WD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x3970 ,N_FLD(dbg_MIFD_RD_REQ_PEND0)               ,"MIFD_RD_REQ_PEND0"                 ,dbg_MIFD_RD_REQ_PEND0               },
	{ 0x3974 ,N_FLD(dbg_MIFD_WD_REQ_PEND0)               ,"MIFD_WD_REQ_PEND0"                 ,dbg_MIFD_WD_REQ_PEND0               },
	{ 0x3978 ,N_FLD(dbg_MIFD_RD_CMD_PRI0_S)              ,"MIFD_RD_CMD_PRI0_S"                ,dbg_MIFD_RD_CMD_PRI0_S              },
	{ 0x397c ,N_FLD(dbg_MIFD_WD_CMD_PRI0_S)              ,"MIFD_WD_CMD_PRI0_S"                ,dbg_MIFD_WD_CMD_PRI0_S              },
	{ 0x3980 ,N_FLD(dbg_MIFD_RESET)                      ,"MIFD_RESET"                        ,dbg_MIFD_RESET                      },
	{ 0x5f00 ,N_FLD(dbg_MIFF_RD_CTRL)                    ,"MIFF_RD_CTRL"                      ,dbg_MIFF_RD_CTRL                    },
	{ 0x5f04 ,N_FLD(dbg_MIFF_RD_CMD_PRI0)                ,"MIFF_RD_CMD_PRI0"                  ,dbg_MIFF_RD_CMD_PRI0                },
	{ 0x5f08 ,N_FLD(dbg_MIFF_RD_REQ_PRI0)                ,"MIFF_RD_REQ_PRI0"                  ,dbg_MIFF_RD_REQ_PRI0                },
	{ 0x5f0c ,N_FLD(dbg_MIFF_RD_REQ_STV0)                ,"MIFF_RD_REQ_STV0"                  ,dbg_MIFF_RD_REQ_STV0                },
	{ 0x5f10 ,N_FLD(dbg_MIFF_RD_CMD_PEND0)               ,"MIFF_RD_CMD_PEND0"                 ,dbg_MIFF_RD_CMD_PEND0               },
	{ 0x5f14 ,N_FLD(dbg_MIFF_RD_CMD_STRIDE0)             ,"MIFF_RD_CMD_STRIDE0"               ,dbg_MIFF_RD_CMD_STRIDE0             },
	{ 0x5f18 ,N_FLD(dbg_MIFF_RD_CMD_STRIDE_SET)          ,"MIFF_RD_CMD_STRIDE_SET"            ,dbg_MIFF_RD_CMD_STRIDE_SET          },
	{ 0x5f1c ,N_FLD(dbg_MIFF_SADDR_RD_OSD_01)            ,"MIFF_SADDR_RD_OSD_01"              ,dbg_MIFF_SADDR_RD_OSD_01            },
	{ 0x5f20 ,N_FLD(dbg_MIFF_SADDR_RD_OSD_23)            ,"MIFF_SADDR_RD_OSD_23"              ,dbg_MIFF_SADDR_RD_OSD_23            },
	{ 0x5f24 ,N_FLD(dbg_MIFF_SADDR_RD_CVE_YC)            ,"MIFF_SADDR_RD_CVE_YC"              ,dbg_MIFF_SADDR_RD_CVE_YC            },
	{ 0x5f28 ,N_FLD(dbg_MIFF_SADDR_RD_EXT0)              ,"MIFF_SADDR_RD_EXT0"                ,dbg_MIFF_SADDR_RD_EXT0              },
	{ 0x5f2c ,N_FLD(dbg_MIFF_STATUS)                     ,"MIFF_STATUS"                       ,dbg_MIFF_STATUS                     },
	{ 0x5f30 ,N_FLD(dbg_MIFF_RD_BANK_8_ADDR0)            ,"MIFF_RD_BANK_8_ADDR0"              ,dbg_MIFF_RD_BANK_8_ADDR0            },
	{ 0x5f34 ,0                                          ,"MIFF_RD_BANK_8_ADDR1"              ,NULL                                },
	{ 0x5f38 ,0                                          ,"MIFF_RD_BANK_2_ADDR0"              ,NULL                                },
	{ 0x5f3c ,0                                          ,"MIFF_RD_BANK_2_ADDR1"              ,NULL                                },
	{ 0x5f40 ,N_FLD(dbg_MIFF_RD_REQ_PEND0)               ,"MIFF_RD_REQ_PEND0"                 ,dbg_MIFF_RD_REQ_PEND0               },
	{ 0x5f44 ,N_FLD(dbg_MIFF_RD_CMD_PRI0_S)              ,"MIFF_RD_CMD_PRI0_S"                ,dbg_MIFF_RD_CMD_PRI0_S              },
	{ 0x5f48 ,N_FLD(dbg_MIFF_RESET)                      ,"MIFF_RESET"                        ,dbg_MIFF_RESET                      },
	{ 0x5f4c ,N_FLD(dbg_MIFF_SADDR_PARAM_UPDATE0_M)      ,"MIFF_SADDR_PARAM_UPDATE0_M"        ,dbg_MIFF_SADDR_PARAM_UPDATE0_M      },
	{ 0 , } // end marker
};

#endif
