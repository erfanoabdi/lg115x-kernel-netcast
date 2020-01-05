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

#ifndef _DBG_IPC_h
#define _DBG_IPC_h

/*------------------------------------
	0x4e00 SET_CTRL0
------------------------------------*/
const DBG_REG_FIELD_T dbg_SET_CTRL0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"run_stall"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,1  ,"start_vector_sel"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,2  ,"p_debug_enable"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,24 ,24 ,"sw_reset_fdone"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"sw_reset"                    },
};

/*------------------------------------
	0x4e04 SET_CTRL1
------------------------------------*/
const DBG_REG_FIELD_T dbg_SET_CTRL1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"prid"                        },
};

/*------------------------------------
	0x4e08 EXT_INTR_EVENT
------------------------------------*/
const DBG_REG_FIELD_T dbg_EXT_INTR_EVENT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_event_arm"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_event_arm"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"wdg_interrupt_event"         },
};

/*------------------------------------
	0x4e0c EXT_INTR_ENABLE
------------------------------------*/
const DBG_REG_FIELD_T dbg_EXT_INTR_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_enable_arm"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_enable_arm"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"wdg_interrupt_enable"        },
};

/*------------------------------------
	0x4e10 EXT_INTR_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_EXT_INTR_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_status_arm"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_status_arm"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"wdg_interrupt_status"        },
};

/*------------------------------------
	0x4e14 EXT_INTR_CLEAR
------------------------------------*/
const DBG_REG_FIELD_T dbg_EXT_INTR_CLEAR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_clear_arm"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_clear_arm"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,31 ,"wdg_interrupt_clear"         },
};

/*------------------------------------
	0x4e18 INT_INTR_EVENT
------------------------------------*/
const DBG_REG_FIELD_T dbg_INT_INTR_EVENT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_event_mcu"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_event_mcu"    },
};

/*------------------------------------
	0x4e1c INT_INTR_ENABLE
------------------------------------*/
const DBG_REG_FIELD_T dbg_INT_INTR_ENABLE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_enable_mcu"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_enable_mcu"   },
};

/*------------------------------------
	0x4e20 INT_INTR_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_INT_INTR_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_status_mcu"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_status_mcu"   },
};

/*------------------------------------
	0x4e24 INT_INTR_CLEAR
------------------------------------*/
const DBG_REG_FIELD_T dbg_INT_INTR_CLEAR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,29 ,0  ,"ipc_interrupt_clear_mcu"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,30 ,30 ,"edma_interrupt_clear_mcu"    },
};

/*------------------------------------
	0x4e28 SROM_BOOT_OFFSET
------------------------------------*/
const DBG_REG_FIELD_T dbg_SROM_BOOT_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"boot_img_offset"             },
};

/*------------------------------------
	0x4e2c ATLAS_PORT_SEL
------------------------------------*/
const DBG_REG_FIELD_T dbg_ATLAS_PORT_SEL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"sram2_atlas_port_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,6  ,4  ,"sram1_atlas_port_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,8  ,"sram0_atlas_port_sel"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,14 ,12 ,"edma_atlas_port_sel"         },
};

/*------------------------------------
	0x4e30 PDEBUG_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_PDEBUG_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"pdebug_status"               },
};

/*------------------------------------
	0x4e34 PDEBUG_DATA
------------------------------------*/
const DBG_REG_FIELD_T dbg_PDEBUG_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pdebug_data"                 },
};

/*------------------------------------
	0x4e38 PDEBUG_PC
------------------------------------*/
const DBG_REG_FIELD_T dbg_PDEBUG_PC[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pdebug_pc"                   },
};

/*------------------------------------
	0x4e3c AXI_USER_ID
------------------------------------*/
const DBG_REG_FIELD_T dbg_AXI_USER_ID[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"axi_user_id"                 },
};

/*------------------------------------
	0x4e40 SRAM0_ATLAS_OFFSET
------------------------------------*/
const DBG_REG_FIELD_T dbg_SRAM0_ATLAS_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"sram0_atlas_offset"          },
};

/*------------------------------------
	0x4e44 SRAM1_ATLAS_OFFSET
------------------------------------*/
const DBG_REG_FIELD_T dbg_SRAM1_ATLAS_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"sram1_atlas_offset"          },
};

/*------------------------------------
	0x4e48 SRAM2_ATLAS_OFFSET
------------------------------------*/
const DBG_REG_FIELD_T dbg_SRAM2_ATLAS_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"sram2_atlas_offset"          },
};

/*------------------------------------
	0x4e5c SPP_MCU_VERSION
------------------------------------*/
const DBG_REG_FIELD_T dbg_SPP_MCU_VERSION[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"mcu_version_number"          },
};

/*------------------------------------
	0x4f00 TX_LOCKED_ID
------------------------------------*/
const DBG_REG_FIELD_T dbg_TX_LOCKED_ID[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"tx_locked_id"                },
};

/*------------------------------------
	0x4f04 TX_SRC_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_TX_SRC_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"tx_src_addr"                 },
};

/*------------------------------------
	0x4f08 TX_DST_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_TX_DST_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"tx_dst_addr"                 },
};

/*------------------------------------
	0x4f0c TX_NXT_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_TX_NXT_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"tx_nxt_addr"                 },
};

/*------------------------------------
	0x4f10 TX_LENGTH
------------------------------------*/
const DBG_REG_FIELD_T dbg_TX_LENGTH[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"tx_length"                   },
};

/*------------------------------------
	0x4f14 EDMA_CTRL
------------------------------------*/
const DBG_REG_FIELD_T dbg_EDMA_CTRL[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"tx_start"                    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,1  ,"tx_dir"                      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"tx_nxt_dir"                  },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"tx_done"                     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,9  ,9  ,"tx_locked"                   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,10 ,10 ,"tx_switch_en"                },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,13 ,12 ,"tx_atomic_size"              },
};

/*------------------------------------
	0x4f18 PATTERN_ADDR
------------------------------------*/
const DBG_REG_FIELD_T dbg_PATTERN_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pattern_addr"                },
};

/*------------------------------------
	0x4f1c PATTERN_DATA
------------------------------------*/
const DBG_REG_FIELD_T dbg_PATTERN_DATA[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"pattern_addr"                },
};

DBG_REG_T gDbgRegIPC[] = {
	{ 0x4e00 ,N_FLD(dbg_SET_CTRL0)               ,"SET_CTRL0"                 ,dbg_SET_CTRL0               },
	{ 0x4e04 ,N_FLD(dbg_SET_CTRL1)               ,"SET_CTRL1"                 ,dbg_SET_CTRL1               },
	{ 0x4e08 ,N_FLD(dbg_EXT_INTR_EVENT)          ,"EXT_INTR_EVENT"            ,dbg_EXT_INTR_EVENT          },
	{ 0x4e0c ,N_FLD(dbg_EXT_INTR_ENABLE)         ,"EXT_INTR_ENABLE"           ,dbg_EXT_INTR_ENABLE         },
	{ 0x4e10 ,N_FLD(dbg_EXT_INTR_STATUS)         ,"EXT_INTR_STATUS"           ,dbg_EXT_INTR_STATUS         },
	{ 0x4e14 ,N_FLD(dbg_EXT_INTR_CLEAR)          ,"EXT_INTR_CLEAR"            ,dbg_EXT_INTR_CLEAR          },
	{ 0x4e18 ,N_FLD(dbg_INT_INTR_EVENT)          ,"INT_INTR_EVENT"            ,dbg_INT_INTR_EVENT          },
	{ 0x4e1c ,N_FLD(dbg_INT_INTR_ENABLE)         ,"INT_INTR_ENABLE"           ,dbg_INT_INTR_ENABLE         },
	{ 0x4e20 ,N_FLD(dbg_INT_INTR_STATUS)         ,"INT_INTR_STATUS"           ,dbg_INT_INTR_STATUS         },
	{ 0x4e24 ,N_FLD(dbg_INT_INTR_CLEAR)          ,"INT_INTR_CLEAR"            ,dbg_INT_INTR_CLEAR          },
	{ 0x4e28 ,N_FLD(dbg_SROM_BOOT_OFFSET)        ,"SROM_BOOT_OFFSET"          ,dbg_SROM_BOOT_OFFSET        },
	{ 0x4e2c ,N_FLD(dbg_ATLAS_PORT_SEL)          ,"ATLAS_PORT_SEL"            ,dbg_ATLAS_PORT_SEL          },
	{ 0x4e30 ,N_FLD(dbg_PDEBUG_STATUS)           ,"PDEBUG_STATUS"             ,dbg_PDEBUG_STATUS           },
	{ 0x4e34 ,N_FLD(dbg_PDEBUG_DATA)             ,"PDEBUG_DATA"               ,dbg_PDEBUG_DATA             },
	{ 0x4e38 ,N_FLD(dbg_PDEBUG_PC)               ,"PDEBUG_PC"                 ,dbg_PDEBUG_PC               },
	{ 0x4e3c ,N_FLD(dbg_AXI_USER_ID)             ,"AXI_USER_ID"               ,dbg_AXI_USER_ID             },
	{ 0x4e40 ,N_FLD(dbg_SRAM0_ATLAS_OFFSET)      ,"SRAM0_ATLAS_OFFSET"        ,dbg_SRAM0_ATLAS_OFFSET      },
	{ 0x4e44 ,N_FLD(dbg_SRAM1_ATLAS_OFFSET)      ,"SRAM1_ATLAS_OFFSET"        ,dbg_SRAM1_ATLAS_OFFSET      },
	{ 0x4e48 ,N_FLD(dbg_SRAM2_ATLAS_OFFSET)      ,"SRAM2_ATLAS_OFFSET"        ,dbg_SRAM2_ATLAS_OFFSET      },
	{ 0x4e5c ,N_FLD(dbg_SPP_MCU_VERSION)         ,"SPP_MCU_VERSION"           ,dbg_SPP_MCU_VERSION         },
	{ 0x4f00 ,N_FLD(dbg_TX_LOCKED_ID)            ,"TX_LOCKED_ID"              ,dbg_TX_LOCKED_ID            },
	{ 0x4f04 ,N_FLD(dbg_TX_SRC_ADDR)             ,"TX_SRC_ADDR"               ,dbg_TX_SRC_ADDR             },
	{ 0x4f08 ,N_FLD(dbg_TX_DST_ADDR)             ,"TX_DST_ADDR"               ,dbg_TX_DST_ADDR             },
	{ 0x4f0c ,N_FLD(dbg_TX_NXT_ADDR)             ,"TX_NXT_ADDR"               ,dbg_TX_NXT_ADDR             },
	{ 0x4f10 ,N_FLD(dbg_TX_LENGTH)               ,"TX_LENGTH"                 ,dbg_TX_LENGTH               },
	{ 0x4f14 ,N_FLD(dbg_EDMA_CTRL)               ,"EDMA_CTRL"                 ,dbg_EDMA_CTRL               },
	{ 0x4f18 ,N_FLD(dbg_PATTERN_ADDR)            ,"PATTERN_ADDR"              ,dbg_PATTERN_ADDR            },
	{ 0x4f1c ,N_FLD(dbg_PATTERN_DATA)            ,"PATTERN_DATA"              ,dbg_PATTERN_DATA            },
	{ 0 , } // end marker
};

#endif
