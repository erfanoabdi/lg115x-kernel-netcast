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

#ifndef _REG_MIF_L9A0_h
#define _REG_MIF_L9A0_h

typedef struct { // 0x0800
	UINT32 block_req_r_mvi_y           : 1;   //     0
	UINT32 block_req_r_mvi_c           : 1;   //     1
	UINT32 block_req_r_prew_y          : 1;   //     2
	UINT32 block_req_r_prew_c          : 1;   //     3
	UINT32 block_req_r_ipc0_y          : 1;   //     4
	UINT32 block_req_r_ipc_c           : 1;   //     5
	UINT32 block_req_r_ipc1_y          : 1;   //     6
	UINT32 block_req_r_tnr0_y          : 1;   //     7
	UINT32 block_req_r_tnr_c           : 1;   //     8
	UINT32 block_req_r_tnr1_y          : 1;   //     9
	UINT32                             : 2;   // 11:10
	UINT32 disable_rd_mif              : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20
	UINT32 mrb_bank_mode               : 3;   // 23:21
} L9A0_MIFA_RD_CTRL_T;

typedef struct { // 0x0804
	UINT32 block_req_w_tnr_y           : 1;   //     0
	UINT32 block_req_w_tnr_c           : 1;   //     1
	UINT32 block_req_w_prew_y          : 1;   //     2
	UINT32 block_req_w_prew_c          : 1;   //     3
	UINT32                             : 8;   // 11: 4
	UINT32 disable_wd_mif              : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20
	UINT32 mwb_bank_mode               : 3;   // 23:21
} L9A0_MIFA_WD_CTRL_T;

typedef struct { // 0x0808
	UINT32 set_10b_req_rd_prew_y       : 1;   //     0
	UINT32 set_10b_req_rd_prew_c       : 1;   //     1
	UINT32 set_10b_req_rd_ipc0_y       : 1;   //     2
	UINT32 set_10b_req_rd_ipc_c        : 1;   //     3
	UINT32 set_10b_req_rd_ipc1_y       : 1;   //     4
	UINT32 set_10b_req_rd_tnr0_y       : 1;   //     5
	UINT32 set_10b_req_rd_tnr_c        : 1;   //     6
	UINT32 set_10b_req_rd_tnr1_y       : 1;   //     7
} L9A0_MIF_RD_SET_10B_T;

typedef struct { // 0x080c
	UINT32 set_10b_req_wd_tnr_y        : 1;   //     0
	UINT32 set_10b_req_wd_tnr_c        : 1;   //     1
	UINT32 set_10b_req_wd_prew_y       : 1;   //     2
	UINT32 set_10b_req_wd_prew_c       : 1;   //     3
} L9A0_MIF_WD_SET_10B_T;

typedef struct { // 0x0810
	UINT32 cmd_rd_pri_v_mvi_y          : 4;   //  3: 0
	UINT32 cmd_rd_pri_v_mvi_c          : 4;   //  7: 4
	UINT32 cmd_rd_pri_v_prew_y         : 4;   // 11: 8
	UINT32 cmd_rd_pri_v_prew_c         : 4;   // 15:12
	UINT32 cmd_rd_pri_v_ipc0_y         : 4;   // 19:16
	UINT32 cmd_rd_pri_v_ipc_c          : 4;   // 23:20
	UINT32 cmd_rd_pri_v_ipc1_y         : 4;   // 27:24
	UINT32 cmd_rd_pri_v_tnr0_y         : 4;   // 31:28
} L9A0_MIFA_RD_CMD_PRI0_T;

typedef struct { // 0x0814
	UINT32 cmd_rd_pri_v_tnr_c          : 4;   //  3: 0
	UINT32 cmd_rd_pri_v_tnr1_y         : 4;   //  7: 4
} L9A0_MIFA_RD_CMD_PRI1_T;

typedef struct { // 0x0818
	UINT32 cmd_wd_pri_v_tnr_y          : 4;   //  3: 0
	UINT32 cmd_wd_pri_v_tnr_c          : 4;   //  7: 4
	UINT32 cmd_wd_pri_v_prew_y         : 4;   // 11: 8
	UINT32 cmd_wd_pri_v_prew_c         : 4;   // 15:12
} L9A0_MIFA_WD_CMD_PRI0_T;

typedef struct { // 0x081c
	UINT32 req_rd_pri_v_mvi_y          : 4;   //  3: 0
	UINT32 req_rd_pri_v_mvi_c          : 4;   //  7: 4
	UINT32 req_rd_pri_v_prew_y         : 4;   // 11: 8
	UINT32 req_rd_pri_v_prew_c         : 4;   // 15:12
	UINT32 req_rd_pri_v_ipc0_y         : 4;   // 19:16
	UINT32 req_rd_pri_v_ipc_c          : 4;   // 23:20
	UINT32 req_rd_pri_v_ipc1_y         : 4;   // 27:24
	UINT32 req_rd_pri_v_tnr0_y         : 4;   // 31:28
} L9A0_MIFA_RD_REQ_PRI0_T;

typedef struct { // 0x0820
	UINT32 req_rd_pri_v_tnr_c          : 4;   //  3: 0
	UINT32 req_rd_pri_v_tnr1_y         : 4;   //  7: 4
} L9A0_MIFA_RD_REQ_PRI1_T;

typedef struct { // 0x0824
	UINT32 req_wd_pri_v_tnr_y          : 4;   //  3: 0
	UINT32 req_wd_pri_v_tnr_c          : 4;   //  7: 4
	UINT32 req_wd_pri_v_prew_y         : 4;   // 11: 8
	UINT32 req_wd_pri_v_prew_c         : 4;   // 15:12
} L9A0_MIFA_WD_REQ_PRI0_T;

typedef struct { // 0x0828
	UINT32 req_rd_stv_v_mvi_y          : 4;   //  3: 0
	UINT32 req_rd_stv_v_mvi_c          : 4;   //  7: 4
	UINT32 req_rd_stv_v_prew_y         : 4;   // 11: 8
	UINT32 req_rd_stv_v_prew_c         : 4;   // 15:12
	UINT32 req_rd_stv_v_ipc0_y         : 4;   // 19:16
	UINT32 req_rd_stv_v_ipc_c          : 4;   // 23:20
	UINT32 req_rd_stv_v_ipc1_y         : 4;   // 27:24
	UINT32 req_rd_stv_v_tnr0_y         : 4;   // 31:28
} L9A0_MIFA_RD_REQ_STV0_T;

typedef struct { // 0x082c
	UINT32 req_rd_stv_v_tnr_c          : 4;   //  3: 0
	UINT32 req_rd_stv_v_tnr1_y         : 4;   //  7: 4
} L9A0_MIFA_RD_REQ_STV1_T;

typedef struct { // 0x0830
	UINT32 req_wd_stv_v_tnr_y          : 4;   //  3: 0
	UINT32 req_wd_stv_v_tnr_c          : 4;   //  7: 4
	UINT32 req_wd_stv_v_prew_y         : 4;   // 11: 8
	UINT32 req_wd_stv_v_prew_c         : 4;   // 15:12
} L9A0_MIFA_WD_REQ_STV0_T;

typedef struct { // 0x0834
	UINT32 cmd_rd_pend_v_mvi_y         : 4;   //  3: 0
	UINT32 cmd_rd_pend_v_mvi_c         : 4;   //  7: 4
	UINT32 cmd_rd_pend_v_prew_y        : 4;   // 11: 8
	UINT32 cmd_rd_pend_v_prew_c        : 4;   // 15:12
	UINT32 cmd_rd_pend_v_ipc0_y        : 4;   // 19:16
	UINT32 cmd_rd_pend_v_ipc_c         : 4;   // 23:20
	UINT32 cmd_rd_pend_v_ipc1_y        : 4;   // 27:24
	UINT32 cmd_rd_pend_v_tnr0_y        : 4;   // 31:28
} L9A0_MIFA_RD_CMD_PEND0_T;

typedef struct { // 0x0838
	UINT32 cmd_rd_pend_v_tnr_c         : 4;   //  3: 0
	UINT32 cmd_rd_pend_v_tnr1_y        : 4;   //  7: 4
} L9A0_MIFA_RD_CMD_PEND1_T;

typedef struct { // 0x083c
	UINT32 cmd_wd_pend_v_tnr_y         : 4;   //  3: 0
	UINT32 cmd_wd_pend_v_tnr_c         : 4;   //  7: 4
	UINT32 cmd_wd_pend_v_prew_y        : 4;   // 11: 8
	UINT32 cmd_wd_pend_v_prew_c        : 4;   // 15:12
} L9A0_MIFA_WD_CMD_PEND0_T;

typedef struct { // 0x0840
	UINT32 cmd_rd_stride_v_mvi_y       : 4;   //  3: 0
	UINT32 cmd_rd_stride_v_mvi_c       : 4;   //  7: 4
	UINT32 cmd_rd_stride_v_2_prew_y    : 4;   // 11: 8
	UINT32 cmd_rd_stride_v_8_prew_y    : 4;   // 15:12
	UINT32 cmd_rd_stride_v_2_prew_c    : 4;   // 19:16
	UINT32 cmd_rd_stride_v_8_prew_c    : 4;   // 23:20
	UINT32 cmd_rd_stride_v_2_ipc0_y    : 4;   // 27:24
	UINT32 cmd_rd_stride_v_8_ipc0_y    : 4;   // 31:28
} L9A0_MIFA_RD_CMD_STRIDE0_T;

typedef struct { // 0x0844
	UINT32 cmd_rd_stride_v_2_ipc_c     : 4;   //  3: 0
	UINT32 cmd_rd_stride_v_8_ipc_c     : 4;   //  7: 4
	UINT32 cmd_rd_stride_v_2_ipc1_y    : 4;   // 11: 8
	UINT32 cmd_rd_stride_v_8_ipc1_y    : 4;   // 15:12
	UINT32 cmd_rd_stride_v_2_tnr0_y    : 4;   // 19:16
	UINT32 cmd_rd_stride_v_8_tnr0_y    : 4;   // 23:20
	UINT32 cmd_rd_stride_v_2_tnr_c     : 4;   // 27:24
	UINT32 cmd_rd_stride_v_8_tnr_c     : 4;   // 31:28
} L9A0_MIFA_RD_CMD_STRIDE1_T;

typedef struct { // 0x0848
	UINT32 cmd_rd_stride_v_2_tnr1_y    : 4;   //  3: 0
	UINT32 cmd_rd_stride_v_8_tnr1_y    : 4;   //  7: 4
} L9A0_MIFA_RD_CMD_STRIDE2_T;

typedef struct { // 0x084c
	UINT32 man_cmd_rd_stride_v_mvi_y   : 1;   //     0
	UINT32 man_cmd_rd_stride_v_mvi_c   : 1;   //     1
	UINT32 man_cmd_rd_stride_v_prew_y  : 1;   //     2
	UINT32 man_cmd_rd_stride_v_prew_c  : 1;   //     3
	UINT32 man_cmd_rd_stride_v_ipc0_y  : 1;   //     4
	UINT32 man_cmd_rd_stride_v_ipc_c   : 1;   //     5
	UINT32 man_cmd_rd_stride_v_ipc1_y  : 1;   //     6
	UINT32 man_cmd_rd_stride_v_tnr0_y  : 1;   //     7
	UINT32 man_cmd_rd_stride_v_tnr_c   : 1;   //     8
	UINT32 man_cmd_rd_stride_v_tnr1_y  : 1;   //     9
} L9A0_MIFA_RD_CMD_STRIDE_SET_T;

typedef struct { // 0x0850
	UINT32 cmd_wd_stride_v_2_tnr_y     : 4;   //  3: 0
	UINT32 cmd_wd_stride_v_8_tnr_y     : 4;   //  7: 4
	UINT32 cmd_wd_stride_v_2_tnr_c     : 4;   // 11: 8
	UINT32 cmd_wd_stride_v_8_tnr_c     : 4;   // 15:12
	UINT32 cmd_wd_stride_v_2_prew_y    : 4;   // 19:16
	UINT32 cmd_wd_stride_v_8_prew_y    : 4;   // 23:20
	UINT32 cmd_wd_stride_v_2_prew_c    : 4;   // 27:24
	UINT32 cmd_wd_stride_v_8_prew_c    : 4;   // 31:28
} L9A0_MIFA_WD_CMD_STRIDE0_T;

typedef struct { // 0x0854
	UINT32 man_cmd_wd_stride_v_tnr_y   : 1;   //     0
	UINT32 man_cmd_wd_stride_v_tnr_c   : 1;   //     1
	UINT32 man_cmd_wd_stride_v_prew_y  : 1;   //     2
	UINT32 man_cmd_wd_stride_v_prew_c  : 1;   //     3
} L9A0_MIFA_WD_CMD_STRIDE_SET_T;

typedef struct { // 0x0858
	UINT32 req_rd_saddr_mvi_y          : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_mvi_c          : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_MVI_Y_MVI_C_T;

typedef struct { // 0x085c
	UINT32 req_rd_saddr_2_prew_y       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_prew_y       : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_PREW_Y_T;

typedef struct { // 0x0860
	UINT32 req_rd_saddr_2_prew_c       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_prew_c       : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_PREW_C_T;

typedef struct { // 0x0864
	UINT32 req_rd_saddr_2_ipc0_y       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_ipc0_y       : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_IPC0_Y_T;

typedef struct { // 0x0868
	UINT32 req_rd_saddr_2_ipc_c        : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_ipc_c        : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_IPC_C_T;

typedef struct { // 0x086c
	UINT32 req_rd_saddr_2_ipc1_y       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_ipc1_y       : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_IPC1_Y_T;

typedef struct { // 0x0870
	UINT32 req_rd_saddr_2_tnr0_y       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_tnr0_y       : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_TNR0_Y_T;

typedef struct { // 0x0874
	UINT32 req_rd_saddr_2_tnr_c        : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_tnr_c        : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_TNR_C_T;

typedef struct { // 0x0878
	UINT32 req_rd_saddr_2_tnr1_y       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_tnr1_y       : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_TNR1_Y_T;

typedef struct { // 0x087c
	UINT32 req_wd_saddr_2_tnr_y        : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_tnr_y        : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_TNR_Y_T;

typedef struct { // 0x0880
	UINT32 req_wd_saddr_2_tnr_c        : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_tnr_c        : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_TNR_C_T;

typedef struct { // 0x0884
	UINT32 req_rd_saddr_2_prew_y       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_prew_y       : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_PREW_Y_T;

typedef struct { // 0x0888
	UINT32 req_rd_saddr_2_prew_c       : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_prew_c       : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_PREW_C_T;

typedef struct { // 0x088c
	UINT32 req_rd_saddr_2_dl_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_dl_y         : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_DL_Y_T;

typedef struct { // 0x0890
	UINT32 req_rd_saddr_2_dl_c         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_dl_c         : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_DL_C_T;

typedef struct { // 0x0894
	UINT32 req_rd_saddr_2_dr_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_dr_y         : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_DR_Y_T;

typedef struct { // 0x0898
	UINT32 req_rd_saddr_2_dr_c         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_dr_c         : 15;  // 30:16
} L9A0_MIFA_SADDR_RD_DR_C_T;

typedef struct { // 0x089c
	UINT32 req_wd_saddr_2_dl_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_dl_y         : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_DL_Y_T;

typedef struct { // 0x08a0
	UINT32 req_wd_saddr_2_dl_c         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_dl_c         : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_DL_C_T;

typedef struct { // 0x08a4
	UINT32 req_wd_saddr_2_dr_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_dr_y         : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_DR_Y_T;

typedef struct { // 0x08a8
	UINT32 req_wd_saddr_2_dr_c         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_dr_c         : 15;  // 30:16
} L9A0_MIFA_SADDR_WD_DR_C_T;

typedef struct { // 0x08ac
	UINT32 req_rd_saddr_mvi_y_msb4b    : 4;   //  3: 0
	UINT32 req_rd_saddr_mvi_c_msb4b    : 4;   //  7: 4
	UINT32 req_rd_saddr_2_prew_y_msb4b : 4;   // 11: 8
	UINT32 req_rd_saddr_8_prew_y_msb4b : 4;   // 15:12
	UINT32 req_rd_saddr_2_prew_c_msb4b : 4;   // 19:16
	UINT32 req_rd_saddr_8_prew_c_msb4b : 4;   // 23:20
	UINT32 req_rd_saddr_2_ipc0_y_msb4b : 4;   // 27:24
	UINT32 req_rd_saddr_8_ipc0_y_msb4b : 4;   // 31:28
} L9A0_MIFA_SADDR_RD_EXT0_T;

typedef struct { // 0x08b0
	UINT32 req_rd_saddr_2_ipc_c_msb4b  : 4;   //  3: 0
	UINT32 req_rd_saddr_8_ipc_c_msb4b  : 4;   //  7: 4
	UINT32 req_rd_saddr_2_ipc1_y_msb4b : 4;   // 11: 8
	UINT32 req_rd_saddr_8_ipc1_y_msb4b : 4;   // 15:12
	UINT32 req_rd_saddr_2_tnr0_y_msb4b : 4;   // 19:16
	UINT32 req_rd_saddr_8_tnr0_y_msb4b : 4;   // 23:20
	UINT32 req_rd_saddr_2_tnr_c_msb4b  : 4;   // 27:24
	UINT32 req_rd_saddr_8_tnr_c_msb4b  : 4;   // 31:28
} L9A0_MIFA_SADDR_RD_EXT1_T;

typedef struct { // 0x08b4
	UINT32 req_rd_saddr_2_tnr1_y_msb4b : 4;   //  3: 0
	UINT32 req_rd_saddr_8_tnr1_y_msb4b : 4;   //  7: 4
} L9A0_MIFA_SADDR_RD_EXT2_T;

typedef struct { // 0x08b8
	UINT32 req_wd_saddr_2_tnr_y_msb4b  : 4;   //  3: 0
	UINT32 req_wd_saddr_8_tnr_y_msb4b  : 4;   //  7: 4
	UINT32 req_wd_saddr_2_tnr_c_msb4b  : 4;   // 11: 8
	UINT32 req_wd_saddr_8_tnr_c_msb4b  : 4;   // 15:12
	UINT32 req_wd_saddr_2_prew_y_msb4b : 4;   // 19:16
	UINT32 req_wd_saddr_8_prew_y_msb4b : 4;   // 23:20
	UINT32 req_wd_saddr_2_prew_c_msb4b : 4;   // 27:24
	UINT32 req_wd_saddr_8_prew_c_msb4b : 4;   // 31:28
} L9A0_MIFA_SADDR_WD_EXT0_T;

typedef struct { // 0x08bc
	UINT32 req_rd_saddr_2_dl_y_msb4b   : 4;   //  3: 0
	UINT32 req_rd_saddr_8_dl_y_msb4b   : 4;   //  7: 4
	UINT32 req_rd_saddr_2_dl_c_msb4b   : 4;   // 11: 8
	UINT32 req_rd_saddr_8_dl_c_msb4b   : 4;   // 15:12
	UINT32 req_rd_saddr_2_dr_y_msb4b   : 4;   // 19:16
	UINT32 req_rd_saddr_8_dr_y_msb4b   : 4;   // 23:20
	UINT32 req_rd_saddr_2_dr_c_msb4b   : 4;   // 27:24
	UINT32 req_rd_saddr_8_dr_c_msb4b   : 4;   // 31:28
} L9A0_MIFA_RD_DR_DL_EXT_T;

typedef struct { // 0x08c0
	UINT32 req_wd_saddr_2_dl_y_msb4b   : 4;   //  3: 0
	UINT32 req_wd_saddr_8_dl_y_msb4b   : 4;   //  7: 4
	UINT32 req_wd_saddr_2_dl_c_msb4b   : 4;   // 11: 8
	UINT32 req_wd_saddr_8_dl_c_msb4b   : 4;   // 15:12
	UINT32 req_wd_saddr_2_dr_y_msb4b   : 4;   // 19:16
	UINT32 req_wd_saddr_8_dr_y_msb4b   : 4;   // 23:20
	UINT32 req_wd_saddr_2_dr_c_msb4b   : 4;   // 27:24
	UINT32 req_wd_saddr_8_dr_c_msb4b   : 4;   // 31:28
} L9A0_MIFA_WD_DR_DL_EXT_T;

typedef struct { // 0x08c4
	UINT32 fr_rd_valid_mvi_y           : 1;   //     0
	UINT32 fr_rd_valid_mvi_c           : 1;   //     1
	UINT32 fr_rd_valid_prew_y          : 1;   //     2
	UINT32 fr_rd_valid_prew_c          : 1;   //     3
	UINT32 fr_rd_valid_ipc0_y          : 1;   //     4
	UINT32 fr_rd_valid_ipc_c           : 1;   //     5
	UINT32 fr_rd_valid_ipc1_y          : 1;   //     6
	UINT32 fr_rd_valid_tnr0_y          : 1;   //     7
	UINT32 fr_rd_valid_tnr_c           : 1;   //     8
	UINT32 fr_rd_valid_tnr1_y          : 1;   //     9
	UINT32 fr_wd_q_full_tnr_y          : 1;   //    10
	UINT32 fr_wd_q_full_tnr_c          : 1;   //    11
	UINT32 fr_wd_q_full_prew_y         : 1;   //    12
	UINT32 fr_wd_q_full_prew_c         : 1;   //    13
} L9A0_MIFA_STATUS_T;

typedef struct { // 0x08c8
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  // 10: 1
	UINT32 register_update_address0_m  : 21;  // 31:11
} L9A0_MIFA_SADDR_PARAM_UPDATE0_M_T;

typedef struct { // 0x08cc
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  // 10: 1
	UINT32 register_update_address0_m1 : 21;  // 31:11
} L9A0_MIFA_SADDR_PARAM_UPDATE0_M1_T;

typedef struct { // 0x08d0
	UINT32 req_rd_bank_addr_8_mvi_y    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_8_mvi_c    : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_rd_bank_addr_8_prew_y   : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_rd_bank_addr_8_prew_c   : 3;   // 14:12
	UINT32                             : 1;   //    15
	UINT32 req_rd_bank_addr_8_ipc0_y   : 3;   // 18:16
	UINT32                             : 1;   //    19
	UINT32 req_rd_bank_addr_8_ipc_c    : 3;   // 22:20
	UINT32                             : 1;   //    23
	UINT32 req_rd_bank_addr_8_ipc1_y   : 3;   // 26:24
	UINT32                             : 1;   //    27
	UINT32 req_rd_bank_addr_8_tnr0_y   : 3;   // 30:28
} L9A0_MIFA_RD_BANK_8_ADDR0_T;

typedef struct { // 0x08d4
	UINT32 req_rd_bank_addr_8_tnr_c    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_8_tnr1_y   : 3;   //  6: 4
} L9A0_MIFA_RD_BANK_8_ADDR1_T;

typedef struct { // 0x08d8
	UINT32                             : 8;   //  7: 0
	UINT32 req_rd_bank_addr_2_prew_y   : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_rd_bank_addr_2_prew_c   : 3;   // 14:12
	UINT32                             : 1;   //    15
	UINT32 req_rd_bank_addr_2_ipc0_y   : 3;   // 18:16
	UINT32                             : 1;   //    19
	UINT32 req_rd_bank_addr_2_ipc_c    : 3;   // 22:20
	UINT32                             : 1;   //    23
	UINT32 req_rd_bank_addr_2_ipc1_y   : 3;   // 26:24
	UINT32                             : 1;   //    27
	UINT32 req_rd_bank_addr_2_tnr0_y   : 3;   // 30:28
} L9A0_MIFA_RD_BANK_2_ADDR0_T;

typedef struct { // 0x08dc
	UINT32 req_rd_bank_addr_2_tnr_c    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_2_tnr1_y   : 3;   //  6: 4
} L9A0_MIFA_RD_BANK_2_ADDR1_T;

typedef struct { // 0x08e0
	UINT32 req_wd_bank_addr_8_tnr_y    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_wd_bank_addr_8_tnr_c    : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_wd_bank_addr_8_prew_y   : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_wd_bank_addr_8_prew_c   : 3;   // 14:12
} L9A0_MIFA_WD_BANK_8_ADDR0_T;

typedef struct { // 0x08e4
	UINT32 mifa_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9A0_MIFA_WD_BANK_8_ADDR1_T;

typedef struct { // 0x08e8
	UINT32 req_wd_bank_addr_2_tnr_y    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_wd_bank_addr_2_tnr_c    : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_wd_bank_addr_2_prew_y   : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_wd_bank_addr_2_prew_c   : 3;   // 14:12
} L9A0_MIFA_WD_BANK_2_ADDR0_T;

typedef struct { // 0x08ec
	UINT32 mifa_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9A0_MIFA_WD_BANK_2_ADDR1_T;

typedef struct { // 0x08f0
	UINT32 req_rd_lsb_prew_y           : 2;   //  1: 0
	UINT32 req_rd_lsb_prew_c           : 2;   //  3: 2
	UINT32 req_rd_lsb_ipc0_y           : 2;   //  5: 4
	UINT32 req_rd_lsb_ipc_c            : 2;   //  7: 6
	UINT32 req_rd_lsb_ipc1_y           : 2;   //  9: 8
	UINT32 req_rd_lsb_tnr0_y           : 2;   // 11:10
	UINT32 req_rd_lsb_tnr_c            : 2;   // 13:12
	UINT32 req_rd_lsb_tnr1_y           : 2;   // 15:14
} L9A0_MIFA_LSB_SWITCH_T;

typedef struct { // 0x08f4
	UINT32 req_rd_pend_v_mvi_y         : 8;   //  7: 0
	UINT32 req_rd_pend_v_mvi_c         : 8;   // 15: 8
	UINT32 req_rd_pend_v_prew_y        : 8;   // 23:16
	UINT32 req_rd_pend_v_prew_c        : 8;   // 31:24
} L9A0_MIFA_RD_REQ_PEND0_T;

typedef struct { // 0x08f8
	UINT32 req_rd_pend_v_ipc0_y        : 8;   //  7: 0
	UINT32 req_rd_pend_v_ipc_c         : 8;   // 15: 8
	UINT32 req_rd_pend_v_ipc1_y        : 8;   // 23:16
	UINT32 req_rd_pend_v_tnr0_y        : 8;   // 31:24
} L9A0_MIFA_RD_REQ_PEND1_T;

typedef struct { // 0x08fc
	UINT32 req_rd_pend_v_tnr_c         : 8;   //  7: 0
	UINT32 req_rd_pend_v_tnr1_y        : 8;   // 15: 8
} L9A0_MIFA_RD_REQ_PEND2_T;

typedef struct { // 0x0900
	UINT32 req_wd_pend_v_tnr_y         : 8;   //  7: 0
	UINT32 req_wd_pend_v_tnr_c         : 8;   // 15: 8
	UINT32 req_wd_pend_v_prew_y        : 8;   // 23:16
	UINT32 req_wd_pend_v_prew_c        : 8;   // 31:24
} L9A0_MIFA_WD_REQ_PEND0_T;

typedef struct { // 0x0904
	UINT32 cmd_rd_pri_s_v_mvi_y        : 4;   //  3: 0
	UINT32 cmd_rd_pri_s_v_mvi_c        : 4;   //  7: 4
	UINT32 cmd_rd_pri_s_v_prew_y       : 4;   // 11: 8
	UINT32 cmd_rd_pri_s_v_prew_c       : 4;   // 15:12
	UINT32 cmd_rd_pri_s_v_ipc0_y       : 4;   // 19:16
	UINT32 cmd_rd_pri_s_v_ipc_c        : 4;   // 23:20
	UINT32 cmd_rd_pri_s_v_ipc1_y       : 4;   // 27:24
	UINT32 cmd_rd_pri_s_v_tnr0_y       : 4;   // 31:28
} L9A0_MIFA_RD_CMD_PRI0_S_T;

typedef struct { // 0x0908
	UINT32 cmd_rd_pri_s_v_tnr_c        : 4;   //  3: 0
	UINT32 cmd_rd_pri_s_v_tnr1_y       : 4;   //  7: 4
} L9A0_MIFA_RD_CMD_PRI1_S_T;

typedef struct { // 0x090c
	UINT32 cmd_wd_pri_s_v_tnr_y        : 4;   //  3: 0
	UINT32 cmd_wd_pri_s_v_tnr_c        : 4;   //  7: 4
	UINT32 cmd_wd_pri_s_v_prew_y       : 4;   // 11: 8
	UINT32 cmd_wd_pri_s_v_prew_c       : 4;   // 15:12
} L9A0_MIFA_WD_CMD_PRI0_S_T;

typedef struct { // 0x0910
	UINT32 reset_mif_r_mvi_y           : 1;   //     0
	UINT32 reset_mif_r_mvi_c           : 1;   //     1
	UINT32 reset_mif_r_prew_y          : 1;   //     2
	UINT32 reset_mif_r_prew_c          : 1;   //     3
	UINT32 reset_mif_r_ipc0_y          : 1;   //     4
	UINT32 reset_mif_r_ipc_c           : 1;   //     5
	UINT32 reset_mif_r_ipc1_y          : 1;   //     6
	UINT32 reset_mif_r_tnr0_y          : 1;   //     7
	UINT32 reset_mif_r_tnr_c           : 1;   //     8
	UINT32 reset_mif_r_tnr1_y          : 1;   //     9
	UINT32 reset_mif_w_tnr_y           : 1;   //    10
	UINT32 reset_mif_w_tnr_c           : 1;   //    11
	UINT32 reset_mif_w_prew_y          : 1;   //    12
	UINT32 reset_mif_w_prew_c          : 1;   //    13
	UINT32                             : 6;   // 19:14
	UINT32 reset_time_out_cnt          : 12;  // 31:20
} L9A0_MIFA_RESET_T;

typedef struct { // 0x1b00
	UINT32 block_req_r_ovm_y           : 1;   //     0
	UINT32 block_req_r_ovm_c           : 1;   //     1
	UINT32 block_req_r_ovs_y           : 1;   //     2
	UINT32 block_req_r_ovs_c           : 1;   //     3
	UINT32                             : 8;   // 11: 4
	UINT32 disable_rd_mif              : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
} L9A0_MIFB_RD_CTRL_T;

typedef struct { // 0x1b04
	UINT32 block_req_w_scm_y           : 1;   //     0
	UINT32 block_req_w_scm_c           : 1;   //     1
	UINT32                             : 10;  // 11: 2
	UINT32 disable_wd_mif              : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
} L9A0_MIFB_WD_CTRL_T;

typedef struct { // 0x1b08
	UINT32 set_10b_req_rd_ovm_y        : 1;   //     0
	UINT32 set_10b_req_rd_ovm_c        : 1;   //     1
} L9A0_MIFB_RD_SET_10B_T;

typedef struct { // 0x1b0c
	UINT32 set_10b_req_wd_scm_y        : 1;   //     0
	UINT32 set_10b_req_wd_scm_c        : 1;   //     1
} L9A0_MIFB_WD_SET_10B_T;

typedef struct { // 0x1b10
	UINT32 cmd_rd_pri_v_ovm_y          : 4;   //  3: 0
	UINT32 cmd_rd_pri_v_ovm_c          : 4;   //  7: 4
	UINT32 cmd_rd_pri_v_ovs_y          : 4;   // 11: 8
	UINT32 cmd_rd_pri_v_ovs_c          : 4;   // 15:12
} L9A0_MIFB_RD_CMD_PRI0_T;

typedef struct { // 0x1b14
	UINT32 cmd_wd_pri_v_sm_y           : 4;   //  3: 0
	UINT32 cmd_wd_pri_v_sm_c           : 4;   //  7: 4
} L9A0_MIFB_WD_CMD_PRI0_T;

typedef struct { // 0x1b18
	UINT32 req_rd_pri_v_ovm_y          : 4;   //  3: 0
	UINT32 req_rd_pri_v_ovm_c          : 4;   //  7: 4
	UINT32 req_rd_pri_v_ovs_y          : 4;   // 11: 8
	UINT32 req_rd_pri_v_ovs_c          : 4;   // 15:12
} L9A0_MIFB_RD_REQ_PRI0_T;

typedef struct { // 0x1b1c
	UINT32 req_wd_pri_v_sm_y           : 4;   //  3: 0
	UINT32 req_wd_pri_v_sm_c           : 4;   //  7: 4
} L9A0_MIFB_WD_REQ_PRI0_T;

typedef struct { // 0x1b20
	UINT32 req_rd_stv_v_ovm_y          : 4;   //  3: 0
	UINT32 req_rd_stv_v_ovm_c          : 4;   //  7: 4
	UINT32 req_rd_stv_v_ovs_y          : 4;   // 11: 8
	UINT32 req_rd_stv_v_ovs_c          : 4;   // 15:12
} L9A0_MIFB_RD_REQ_STV0_T;

typedef struct { // 0x1b24
	UINT32 req_wd_stv_v_sm_y           : 4;   //  3: 0
	UINT32 req_wd_stv_v_sm_c           : 4;   //  7: 4
} L9A0_MIFB_WD_REQ_STV0_T;

typedef struct { // 0x1b28
	UINT32 cmd_rd_pend_v_ovm_y         : 4;   //  3: 0
	UINT32 cmd_rd_pend_v_ovm_c         : 4;   //  7: 4
	UINT32 cmd_rd_pend_v_ovs_y         : 4;   // 11: 8
	UINT32 cmd_rd_pend_v_ovs_c         : 4;   // 15:12
} L9A0_MIFB_RD_CMD_PEND0_T;

typedef struct { // 0x1b2c
	UINT32 cmd_wd_pend_v_sm_y          : 4;   //  3: 0
	UINT32 cmd_wd_pend_v_sm_c          : 4;   //  7: 4
} L9A0_MIFB_WD_CMD_PEND0_T;

typedef struct { // 0x1b30
	UINT32 cmd_rd_stride_v_2_ovm_y     : 4;   //  3: 0
	UINT32 cmd_rd_stride_v_8_ovm_y     : 4;   //  7: 4
	UINT32 cmd_rd_stride_v_2_ovm_c     : 4;   // 11: 8
	UINT32 cmd_rd_stride_v_8_ovm_c     : 4;   // 15:12
	UINT32 cmd_rd_stride_v_ovs_y       : 4;   // 19:16
	UINT32 cmd_rd_stride_v_ovs_c       : 4;   // 23:20
} L9A0_MIFB_RD_CMD_STRIDE0_T;

typedef struct { // 0x1b34
	UINT32 man_cmd_rd_stride_v_ovm_y   : 1;   //     0
	UINT32 man_cmd_rd_stride_v_ovm_c   : 1;   //     1
	UINT32 man_cmd_rd_stride_v_ovs_y   : 1;   //     2
	UINT32 man_cmd_rd_stride_v_ovs_c   : 1;   //     3
} L9A0_MIFB_RD_CMD_STRIDE_SET_T;

typedef struct { // 0x1b38
	UINT32 cmd_wd_stride_v_2_sm_y      : 4;   //  3: 0
	UINT32 cmd_wd_stride_v_8_sm_y      : 4;   //  7: 4
	UINT32 cmd_wd_stride_v_2_sm_c      : 4;   // 11: 8
	UINT32 cmd_wd_stride_v_8_sm_c      : 4;   // 15:12
} L9A0_MIFB_WD_CMD_STRIDE0_T;

typedef struct { // 0x1b3c
	UINT32 man_cmd_wd_stride_v_sm_y    : 1;   //     0
	UINT32 man_cmd_wd_stride_v_sm_c    : 1;   //     1
} L9A0_MIFB_WD_CMD_STRIDE_SET_T;

typedef struct { // 0x1b40
	UINT32 req_rd_saddr_2_ovm_y        : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_ovm_y        : 15;  // 30:16
} L9A0_MIFB_SADDR_RD_OVM_Y_T;

typedef struct { // 0x1b44
	UINT32 req_rd_saddr_2_ovm_c        : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_8_ovm_c        : 15;  // 30:16
} L9A0_MIFB_SADDR_RD_OVM_C_T;

typedef struct { // 0x1b48
	UINT32 req_rd_saddr_ovs_y          : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_ovs_c          : 15;  // 30:16
} L9A0_MIFB_SADDR_RD_OVS_Y_OVS_C_T;

typedef struct { // 0x1b4c
	UINT32 req_wd_saddr_2_sm_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_sm_y         : 15;  // 30:16
} L9A0_MIFB_SADDR_WD_SM_Y_T;

typedef struct { // 0x1b50
	UINT32 req_wd_saddr_2_sm_c         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_8_sm_c         : 15;  // 30:16
} L9A0_MIFB_SADDR_WD_SM_C_T;

typedef struct { // 0x1b54
	UINT32 req_rd_saddr_2_ovm_y_msb4b  : 4;   //  3: 0
	UINT32 req_rd_saddr_8_ovm_y_msb4b  : 4;   //  7: 4
	UINT32 req_rd_saddr_2_ovm_c_msb4b  : 4;   // 11: 8
	UINT32 req_rd_saddr_8_ovm_c_msb4b  : 4;   // 15:12
	UINT32 req_rd_saddr_ovs_y_msb4b    : 4;   // 19:16
	UINT32 req_rd_saddr_ovs_c_msb4b    : 4;   // 23:20
} L9A0_MIFB_SADDR_RD_EXT0_T;

typedef struct { // 0x1b58
	UINT32 req_wd_saddr_2_sm_y_msb4b   : 4;   //  3: 0
	UINT32 req_wd_saddr_8_sm_y_msb4b   : 4;   //  7: 4
	UINT32 req_wd_saddr_2_sm_c_msb4b   : 4;   // 11: 8
	UINT32 req_wd_saddr_8_sm_c_msb4b   : 4;   // 15:12
} L9A0_MIFB_SADDR_WD_EXT0_T;

typedef struct { // 0x1b5c
	UINT32 fr_rd_valid_ovm_y           : 1;   //     0
	UINT32 fr_rd_valid_ovm_c           : 1;   //     1
	UINT32 fr_rd_valid_ovs_y           : 1;   //     2
	UINT32 fr_rd_valid_ovs_c           : 1;   //     3
	UINT32 fr_wd_q_full_sm_y           : 1;   //     4
	UINT32 fr_wd_q_full_sm_c           : 1;   //     5
} L9A0_MIFB_STATUS_T;

typedef struct { // 0x1b60
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  // 10: 1
	UINT32 register_update_address0_m  : 21;  // 31:11
} L9A0_MIFB_SADDR_PARAM_UPDATE0_M_T;

typedef struct { // 0x1b64
	UINT32 req_rd_bank_addr_8_ovm_y    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_8_ovm_c    : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_rd_bank_addr_ovs_y      : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_rd_bank_addr_ovs_c      : 3;   // 14:12
} L9A0_MIFB_RD_BANK_8_ADDR0_T;

typedef struct { // 0x1b68
	UINT32 mifb_rd_bank_8_addr1_f      : 32;   // 31: 0
} L9A0_MIFB_RD_BANK_8_ADDR1_T;

typedef struct { // 0x1b6c
	UINT32 req_rd_bank_addr_2_ovs_y    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_2_ovs_c    : 3;   //  6: 4
} L9A0_MIFB_RD_BANK_2_ADDR0_T;

typedef struct { // 0x1b70
	UINT32 mifb_rd_bank_2_addr1_f      : 32;   // 31: 0
} L9A0_MIFB_RD_BANK_2_ADDR1_T;

typedef struct { // 0x1b74
	UINT32 req_wd_bank_addr_8_sm_y     : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_wd_bank_addr_8_sm_c     : 3;   //  6: 4
} L9A0_MIFB_WD_BANK_8_ADDR0_T;

typedef struct { // 0x1b78
	UINT32 mifb_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9A0_MIFB_WD_BANK_8_ADDR1_T;

typedef struct { // 0x1b7c
	UINT32 req_wd_bank_addr_8_sm_y     : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_wd_bank_addr_8_sm_c     : 3;   //  6: 4
} L9A0_MIFB_WD_BANK_2_ADDR0_T;

typedef struct { // 0x1b80
	UINT32 mifb_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9A0_MIFB_WD_BANK_2_ADDR1_T;

typedef struct { // 0x1b84
	UINT32 req_rd_lsb_ovm_y            : 2;   //  1: 0
	UINT32 req_rd_lsb_ovm_c            : 2;   //  3: 2
} L9A0_MIFB_LSB_SWITCH_T;

typedef struct { // 0x1b88
	UINT32 mifb_rd_req_pend0_f         : 32;   // 31: 0
} L9A0_MIFB_RD_REQ_PEND0_T;

typedef struct { // 0x1b8c
	UINT32 req_wd_pend_v_sm_y          : 8;   //  7: 0
	UINT32 req_wd_pend_v_sm_c          : 8;   // 15: 8
} L9A0_MIFB_WD_REQ_PEND0_T;

typedef struct { // 0x1b90
	UINT32 cmd_rd_pri_s_v_ovm_y        : 4;   //  3: 0
	UINT32 cmd_rd_pri_s_v_ovm_c        : 4;   //  7: 4
	UINT32 cmd_rd_pri_s_v_ovs_y        : 4;   // 11: 8
	UINT32 cmd_rd_pri_s_v_ovs_c        : 4;   // 15:12
} L9A0_MIFB_RD_CMD_PRI00_S_T;

typedef struct { // 0x1b94
	UINT32 cmd_wd_pri_s_v_sm_y         : 4;   //  3: 0
	UINT32 cmd_wd_pri_s_v_sm_c         : 4;   //  7: 4
} L9A0_MIFB_WD_CMD_PRI00_S_T;

typedef struct { // 0x1b98
	UINT32 reset_mif_r_ovm_y           : 1;   //     0
	UINT32 reset_mif_r_ovm_c           : 1;   //     1
	UINT32 reset_mif_r_ovs_y           : 1;   //     2
	UINT32 reset_mif_r_ovs_c           : 1;   //     3
	UINT32 reset_mif_w_scm_y           : 1;   //     4
	UINT32 reset_mif_w_scm_c           : 1;   //     5
	UINT32                             : 14;  // 19: 6
	UINT32 reset_time_out_cnt          : 12;  // 31:20
} L9A0_MIFB_RESET_T;

typedef struct { // 0x2800
	UINT32 block_req_r_mvi_y           : 1;   //     0
	UINT32 block_req_r_mvi_c           : 1;   //     1
	UINT32 block_req_r_prew_y          : 1;   //     2
	UINT32 block_req_r_prew_c          : 1;   //     3
	UINT32 block_req_r_ipc0_y          : 1;   //     4
	UINT32 block_req_r_ipc_c           : 1;   //     5
	UINT32 block_req_r_ipc1_y          : 1;   //     6
	UINT32 block_req_r_tnr0_y          : 1;   //     7
	UINT32 block_req_r_tnr_c           : 1;   //     8
	UINT32 block_req_r_ss_y            : 1;   //     9
	UINT32 block_req_r_ss_c            : 1;   //    10
	UINT32                             : 1;   //    11
	UINT32 disable_rd_mifc             : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20
	UINT32 mrb_bank_mode               : 3;   // 23:21
} L9A0_MIFC_RD_CTRL_T;

typedef struct { // 0x2804
	UINT32 block_req_w_ss_y            : 1;   //     0
	UINT32 block_req_w_ss_c            : 1;   //     1
	UINT32 block_req_w_tnr_y           : 1;   //     2
	UINT32 block_req_w_tnr_c           : 1;   //     3
	UINT32 block_req_w_prew_y          : 1;   //     4
	UINT32 block_req_w_prew_c          : 1;   //     5
	UINT32                             : 6;   // 11: 6
	UINT32 disable_wd_mifc             : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
	UINT32 set_ecanvas                 : 1;   //    20
	UINT32 mwb_bank_mode               : 3;   // 23:21
} L9A0_MIFC_WD_CTRL_T;

typedef struct { // 0x2808
	UINT32 cmd_rd_pri_v_mvi_y          : 4;   //  3: 0
	UINT32 cmd_rd_pri_v_mvi_c          : 4;   //  7: 4
	UINT32 cmd_rd_pri_v_prew_y         : 4;   // 11: 8
	UINT32 cmd_rd_pri_v_prew_c         : 4;   // 15:12
	UINT32 cmd_rd_pri_v_ipc0_y         : 4;   // 19:16
	UINT32 cmd_rd_pri_v_ipc_c          : 4;   // 23:20
	UINT32 cmd_rd_pri_v_ipc1_y         : 4;   // 27:24
	UINT32 cmd_rd_pri_v_tnr0_y         : 4;   // 31:28
} L9A0_MIFC_RD_CMD_PRI0_T;

typedef struct { // 0x280c
	UINT32 cmd_rd_pri_v_tnr_c          : 4;   //  3: 0
	UINT32 cmd_rd_pri_v_ss_y           : 4;   //  7: 4
	UINT32 cmd_rd_pri_v_ss_c           : 4;   // 11: 8
} L9A0_MIFC_RD_CMD_PRI1_T;

typedef struct { // 0x2810
	UINT32 cmd_wd_pri_v_ss_y           : 4;   //  3: 0
	UINT32 cmd_wd_pri_v_ss_c           : 4;   //  7: 4
	UINT32 cmd_wd_pri_v_tnr_y          : 4;   // 11: 8
	UINT32 cmd_wd_pri_v_tnr_c          : 4;   // 15:12
	UINT32 cmd_wd_pri_v_prew_y         : 4;   // 19:16
	UINT32 cmd_wd_pri_v_prew_c         : 4;   // 23:20
} L9A0_MIFC_WD_CMD_PRI0_T;

typedef struct { // 0x2814
	UINT32 req_rd_pri_v_mvi_y          : 4;   //  3: 0
	UINT32 req_rd_pri_v_mvi_c          : 4;   //  7: 4
	UINT32 req_rd_pri_v_prew_y         : 4;   // 11: 8
	UINT32 req_rd_pri_v_prew_c         : 4;   // 15:12
	UINT32 req_rd_pri_v_ipc0_y         : 4;   // 19:16
	UINT32 req_rd_pri_v_ipc1_y         : 4;   // 23:20
	UINT32 req_rd_pri_v_ipc_c          : 4;   // 27:24
	UINT32 req_rd_pri_v_tnr0_y         : 4;   // 31:28
} L9A0_MIFC_RD_REQ_PRI0_T;

typedef struct { // 0x2818
	UINT32 req_rd_pri_v_tnr_c          : 4;   //  3: 0
	UINT32 req_rd_pri_v_ss_y           : 4;   //  7: 4
	UINT32 req_rd_pri_v_ss_c           : 4;   // 11: 8
} L9A0_MIFC_RD_REQ_PRI1_T;

typedef struct { // 0x281c
	UINT32 req_wd_pri_v_ss_y           : 4;   //  3: 0
	UINT32 req_wd_pri_v_ss_c           : 4;   //  7: 4
	UINT32 req_wd_pri_v_tnr_y          : 4;   // 11: 8
	UINT32 req_wd_pri_v_tnr_c          : 4;   // 15:12
	UINT32 req_wd_pri_v_prew_y         : 4;   // 19:16
	UINT32 req_wd_pri_v_prew_c         : 4;   // 23:20
} L9A0_MIFC_WD_REQ_PRI0_T;

typedef struct { // 0x2820
	UINT32 req_rd_stv_v_mvi_y          : 4;   //  3: 0
	UINT32 req_rd_stv_v_mvi_c          : 4;   //  7: 4
	UINT32 req_rd_stv_v_prew_y         : 4;   // 11: 8
	UINT32 req_rd_stv_v_prew_c         : 4;   // 15:12
	UINT32 req_rd_stv_v_ipc0_y         : 4;   // 19:16
	UINT32 req_rd_stv_v_ipc_c          : 4;   // 23:20
	UINT32 req_rd_stv_v_ipc1_y         : 4;   // 27:24
	UINT32 req_rd_stv_v_tnr0_y         : 4;   // 31:28
} L9A0_MIFC_RD_REQ_STV0_T;

typedef struct { // 0x2824
	UINT32 req_rd_pri_v_tnr_c          : 4;   //  3: 0
	UINT32 req_rd_pri_v_ss_y           : 4;   //  7: 4
	UINT32 req_rd_pri_v_ss_c           : 4;   // 11: 8
} L9A0_MIFC_RD_REQ_STV1_T;

typedef struct { // 0x2828
	UINT32 req_wd_stv_v_ss_y           : 4;   //  3: 0
	UINT32 req_wd_stv_v_ss_c           : 4;   //  7: 4
	UINT32 req_wd_stv_v_tnr_y          : 4;   // 11: 8
	UINT32 req_wd_stv_v_tnr_c          : 4;   // 15:12
	UINT32 req_wd_stv_v_prew_y         : 4;   // 19:16
	UINT32 req_wd_stv_v_prew_c         : 4;   // 23:20
} L9A0_MIFC_WD_REQ_STV0_T;

typedef struct { // 0x282c
	UINT32 cmd_rd_pend_v_mvi_y         : 4;   //  3: 0
	UINT32 cmd_rd_pend_v_mvi_c         : 4;   //  7: 4
	UINT32 cmd_rd_pend_v_prew_y        : 4;   // 11: 8
	UINT32 cmd_rd_pend_v_prew_c        : 4;   // 15:12
	UINT32 cmd_rd_pend_v_ipc0_y        : 4;   // 19:16
	UINT32 cmd_rd_pend_v_ipc_c         : 4;   // 23:20
	UINT32 cmd_rd_pend_v_ipc1_y        : 4;   // 27:24
	UINT32 cmd_rd_pend_v_tnr0_y        : 4;   // 31:28
} L9A0_MIFC_RD_CMD_PEND0_T;

typedef struct { // 0x2830
	UINT32 cmd_rd_pend_v_tnr_c         : 4;   //  3: 0
	UINT32 cmd_rd_pend_v_ss_y          : 4;   //  7: 4
	UINT32 cmd_rd_pend_v_ss_c          : 4;   // 11: 8
} L9A0_MIFC_RD_CMD_PEND1_T;

typedef struct { // 0x2834
	UINT32 cmd_wd_pend_v_ss_y          : 4;   //  3: 0
	UINT32 cmd_wd_pend_v_ss_c          : 4;   //  7: 4
	UINT32 cmd_wd_pend_v_tnr_y         : 4;   // 11: 8
	UINT32 cmd_wd_pend_v_tnr_c         : 4;   // 15:12
	UINT32 cmd_wd_pend_v_prew_y        : 4;   // 19:16
	UINT32 cmd_wd_pend_v_prew_c        : 4;   // 23:20
} L9A0_MIFC_WD_CMD_PEND0_T;

typedef struct { // 0x2838
	UINT32 cmd_rd_stride_v_mvi_y       : 4;   //  3: 0
	UINT32 cmd_rd_stride_v_mvi_c       : 4;   //  7: 4
	UINT32 cmd_rd_stride_v_prew_y      : 4;   // 11: 8
	UINT32 cmd_rd_stride_v_prew_c      : 4;   // 15:12
	UINT32 cmd_rd_stride_v_ipc0_y      : 4;   // 19:16
	UINT32 cmd_rd_stride_v_ipc_c       : 4;   // 23:20
	UINT32 cmd_rd_stride_v_ipc1_y      : 4;   // 27:24
	UINT32 cmd_rd_stride_v_tnr0_y      : 4;   // 31:28
} L9A0_MIFC_RD_CMD_STRIDE0_T;

typedef struct { // 0x283c
	UINT32 cmd_rd_stride_v_tnr_c       : 4;   //  3: 0
	UINT32 cmd_rd_stride_v_ss_y        : 4;   //  7: 4
	UINT32 cmd_rd_stride_v_ss_c        : 4;   // 11: 8
} L9A0_MIFC_RD_CMD_STRIDE1_T;

typedef struct { // 0x2840
	UINT32 man_cmd_rd_stride_v_mvi_y   : 1;   //     0
	UINT32 man_cmd_rd_stride_v_mvi_c   : 1;   //     1
	UINT32 man_cmd_rd_stride_v_prew_y  : 1;   //     2
	UINT32 man_cmd_rd_stride_v_prew_c  : 1;   //     3
	UINT32 man_cmd_rd_stride_v_ipc0_y  : 1;   //     4
	UINT32 man_cmd_rd_stride_v_ipc_c   : 1;   //     5
	UINT32 man_cmd_rd_stride_v_ipc1_y  : 1;   //     6
	UINT32 man_cmd_rd_stride_v_tnr0_y  : 1;   //     7
	UINT32 man_cmd_rd_stride_v_tnr_c   : 1;   //     8
	UINT32 man_cmd_rd_stride_v_ss_y    : 1;   //     9
	UINT32 man_cmd_rd_stride_v_ss_c    : 1;   //    10
} L9A0_MIFC_RD_CMD_STRIDE_SET_T;

typedef struct { // 0x2844
	UINT32 cmd_wd_stride_v_ss_y        : 4;   //  3: 0
	UINT32 cmd_wd_stride_v_ss_c        : 4;   //  7: 4
	UINT32 cmd_wd_stride_v_tnr_y       : 4;   // 11: 8
	UINT32 cmd_wd_stride_v_tnr_c       : 4;   // 15:12
	UINT32 cmd_wd_stride_v_prew_y      : 4;   // 19:16
	UINT32 cmd_wd_stride_v_prew_c      : 4;   // 23:20
} L9A0_MIFC_WD_CMD_STRIDE0_T;

typedef struct { // 0x2848
	UINT32 man_cmd_wd_stride_v_ss_y    : 1;   //     0
	UINT32 man_cmd_wd_stride_v_ss_c    : 1;   //     1
	UINT32 man_cmd_wd_stride_v_tnr_y   : 1;   //     2
	UINT32 man_cmd_wd_stride_v_tnr_c   : 1;   //     3
	UINT32 man_cmd_wd_stride_v_prew_y  : 1;   //     4
	UINT32 man_cmd_wd_stride_v_prew_c  : 1;   //     5
} L9A0_MIFC_WD_CMD_STRIDE_SET_T;

typedef struct { // 0x284c
	UINT32 req_rd_saddr_mvi_y          : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_mvi_c          : 15;  // 30:16
} L9A0_MIFC_SADDR_RD_MVI_Y_MVI_C_T;

typedef struct { // 0x2850
	UINT32 req_rd_saddr_prew_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_prew_c         : 15;  // 30:16
} L9A0_MIFC_SADDR_RD_PREW_Y_PREW_C_T;

typedef struct { // 0x2854
	UINT32 req_rd_saddr_ipc0_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_ipc_c          : 15;  // 30:16
} L9A0_MIFC_SADDR_RD_IPC0_Y_IPC_C_T;

typedef struct { // 0x2858
	UINT32 req_rd_saddr_ipc1_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_tnr0_y         : 15;  // 30:16
} L9A0_MIFC_SADDR_RD_IPC1_Y_TNR0_Y_T;

typedef struct { // 0x285c
	UINT32 req_rd_saddr_ss_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_ss_c           : 15;  // 30:16
} L9A0_MIFC_SADDR_RD_SS_Y_SS_C_T;

typedef struct { // 0x2860
	UINT32 req_rd_saddr_tnr_c          : 15;  // 14: 0
} L9A0_MIFC_SADDR_RD_TNR_C_T;

typedef struct { // 0x2864
	UINT32 req_wd_saddr_ss_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_ss_c           : 15;  // 30:16
} L9A0_MIFC_SADDR_WD_SS_Y_SS_C_T;

typedef struct { // 0x2868
	UINT32 req_wd_saddr_tnr_y          : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_tnr_c          : 15;  // 30:16
} L9A0_MIFC_SADDR_WD_TNR_Y_TNR_C_T;

typedef struct { // 0x286c
	UINT32 req_wd_saddr_prew_y         : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_prew_c         : 15;  // 30:16
} L9A0_MIFC_SADDR_WD_PREW_Y_PREW_C_T;

typedef struct { // 0x2870
	UINT32 req_rd_saddr_dl_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_dl_c           : 15;  // 30:16
} L9A0_MIFC_SADDR_RD_DL_Y_DL_C_T;

typedef struct { // 0x2874
	UINT32 req_rd_saddr_dr_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_dr_c           : 15;  // 30:16
} L9A0_MIFC_SADDR_RD_DR_Y_DR_C_T;

typedef struct { // 0x2878
	UINT32 req_wd_saddr_dl_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_dl_c           : 15;  // 30:16
} L9A0_MIFC_SADDR_WD_DL_Y_DL_C_T;

typedef struct { // 0x287c
	UINT32 req_wd_saddr_dr_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_dr_c           : 15;  // 30:16
} L9A0_MIFC_SADDR_WD_DR_Y_DR_C_T;

typedef struct { // 0x2880
	UINT32 req_rd_saddr_mvi_y_msb4b    : 4;   //  3: 0
	UINT32 req_rd_saddr_mvi_c_msb4b    : 4;   //  7: 4
	UINT32 req_rd_saddr_prew_y_msb4b   : 4;   // 11: 8
	UINT32 req_rd_saddr_prew_c_msb4b   : 4;   // 15:12
	UINT32 req_rd_saddr_ipc0_y_msb4b   : 4;   // 19:16
	UINT32 req_rd_saddr_ipc_c_msb4b    : 4;   // 23:20
	UINT32 req_rd_saddr_ipc1_y_msb4b   : 4;   // 27:24
	UINT32 req_rd_saddr_tnr0_y_msb4b   : 4;   // 31:28
} L9A0_MIFC_SADDR_RD_EXT0_T;

typedef struct { // 0x2884
	UINT32 req_rd_saddr_tnr_c_msb4b    : 4;   //  3: 0
	UINT32 req_rd_saddr_ss_y_msb4b     : 4;   //  7: 4
	UINT32 req_rd_saddr_ss_c_msb4b     : 4;   // 11: 8
} L9A0_MIFC_SADDR_RD_EXT1_T;

typedef struct { // 0x2888
	UINT32 req_wd_saddr_ss_y_msb4b     : 4;   //  3: 0
	UINT32 req_wd_saddr_ss_c_msb4b     : 4;   //  7: 4
	UINT32 req_wd_saddr_tnr_y_msb4b    : 4;   // 11: 8
	UINT32 req_wd_saddr_tnr_c_msb4b    : 4;   // 15:12
	UINT32 req_wd_saddr_prew_y_msb4b   : 4;   // 19:16
	UINT32 req_wd_saddr_prew_c_msb4b   : 4;   // 23:20
} L9A0_MIFC_SADDR_WD_EXT0_T;

typedef struct { // 0x288c
	UINT32 req_rd_saddr_dl_y_msb4b     : 4;   //  3: 0
	UINT32 req_rd_saddr_dl_c_msb4b     : 4;   //  7: 4
	UINT32 req_rd_saddr_dr_y_msb4b     : 4;   // 11: 8
	UINT32 req_rd_saddr_dr_c_msb4b     : 4;   // 15:12
} L9A0_MIFC_RD_DR_DL_EXT_T;

typedef struct { // 0x2890
	UINT32 req_wd_saddr_dl_y_msb4b     : 4;   //  3: 0
	UINT32 req_wd_saddr_dl_c_msb4b     : 4;   //  7: 4
	UINT32 req_wd_saddr_dr_y_msb4b     : 4;   // 11: 8
	UINT32 req_wd_saddr_dr_c_msb4b     : 4;   // 15:12
} L9A0_MIFC_WD_DR_DL_EXT_T;

typedef struct { // 0x2894
	UINT32 fr_rd_valid_mvi_y           : 1;   //     0
	UINT32 fr_rd_valid_mvi_c           : 1;   //     1
	UINT32 fr_rd_valid_prew_y          : 1;   //     2
	UINT32 fr_rd_valid_prew_c          : 1;   //     3
	UINT32 fr_rd_valid_ipc0_y          : 1;   //     4
	UINT32 fr_rd_valid_ipc_c           : 1;   //     5
	UINT32 fr_rd_valid_ipc1_y          : 1;   //     6
	UINT32 fr_rd_valid_tnr0_y          : 1;   //     7
	UINT32 fr_rd_valid_tnr_c           : 1;   //     8
	UINT32 fr_rd_valid_ss_y            : 1;   //     9
	UINT32 fr_rd_valid_ss_c            : 1;   //    10
	UINT32 fr_wd_q_full_ss_y           : 1;   //    11
	UINT32 fr_wd_q_full_ss_c           : 1;   //    12
	UINT32 fr_wd_q_full_tnr_y          : 1;   //    13
	UINT32 fr_wd_q_full_tnr_c          : 1;   //    14
	UINT32 fr_wd_q_full_prew_y         : 1;   //    15
	UINT32 fr_wd_q_full_prew_c         : 1;   //    16
} L9A0_MIFC_STATUS_T;

typedef struct { // 0x2898
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  // 10: 1
	UINT32 register_update_address0_m  : 21;  // 31:11
} L9A0_MIFC_SADDR_PARAM_UPDATE0_M_T;

typedef struct { // 0x289c
	UINT32 req_rd_bank_addr_8_mvi_y    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_8_mvi_c    : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_rd_bank_addr_8_prew_y   : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_rd_bank_addr_8_prew_c   : 3;   // 14:12
	UINT32                             : 1;   //    15
	UINT32 req_rd_bank_addr_8_ipc0_y   : 3;   // 18:16
	UINT32                             : 1;   //    19
	UINT32 req_rd_bank_addr_8_ipc_c    : 3;   // 22:20
	UINT32                             : 1;   //    23
	UINT32 req_rd_bank_addr_8_ipc1_y   : 3;   // 26:24
	UINT32                             : 1;   //    27
	UINT32 req_rd_bank_addr_8_tnr0_y   : 3;   // 30:28
} L9A0_MIFC_RD_BANK_8_ADDR0_T;

typedef struct { // 0x28a0
	UINT32 req_rd_bank_addr_8_tnr_c    : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_8_ss_y     : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_rd_bank_addr_8_ss_c     : 3;   // 10: 8
} L9A0_MIFC_RD_BANK_8_ADDR1_T;

typedef struct { // 0x28a4
	UINT32 mifc_rd_bank_2_addr0_f      : 32;   // 31: 0
} L9A0_MIFC_RD_BANK_2_ADDR0_T;

typedef struct { // 0x28a8
	UINT32 mifc_rd_bank_2_addr1_f      : 32;   // 31: 0
} L9A0_MIFC_RD_BANK_2_ADDR1_T;

typedef struct { // 0x28ac
	UINT32 req_wd_bank_addr_8_ss_y     : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_wd_bank_addr_8_ss_c     : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_wd_bank_addr_8_tnr_y    : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_wd_bank_addr_8_tnr_c    : 3;   // 14:12
	UINT32                             : 1;   //    15
	UINT32 req_wd_bank_addr_8_prew_y   : 3;   // 18:16
	UINT32                             : 1;   //    19
	UINT32 req_wd_bank_addr_8_prew_c   : 3;   // 22:20
} L9A0_MIFC_WD_BANK_8_ADDR0_T;

typedef struct { // 0x28b0
	UINT32 mifc_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9A0_MIFC_WD_BANK_8_ADDR1_T;

typedef struct { // 0x28b4
	UINT32 mifc_wd_bank_2_addr0_f      : 32;   // 31: 0
} L9A0_MIFC_WD_BANK_2_ADDR0_T;

typedef struct { // 0x28b8
	UINT32 mifc_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9A0_MIFC_WD_BANK_2_ADDR1_T;

typedef struct { // 0x28bc
	UINT32 req_rd_pend_v_mvi_y         : 8;   //  7: 0
	UINT32 req_rd_pend_v_mvi_c         : 8;   // 15: 8
	UINT32 req_rd_pend_v_prew_y        : 8;   // 23:16
	UINT32 req_rd_pend_v_prew_c        : 8;   // 31:24
} L9A0_MIFC_RD_REQ_PEND0_T;

typedef struct { // 0x28c0
	UINT32 req_rd_pend_v_ipc0_y        : 8;   //  7: 0
	UINT32 req_rd_pend_v_ipc_c         : 8;   // 15: 8
	UINT32 req_rd_pend_v_ipc1_y        : 8;   // 23:16
	UINT32 req_rd_pend_v_tnr0_y        : 8;   // 31:24
} L9A0_MIFC_RD_REQ_PEND1_T;

typedef struct { // 0x28c4
	UINT32 req_rd_pend_v_tnr_c         : 8;   //  7: 0
	UINT32 req_rd_pend_v_ss_y          : 8;   // 15: 8
	UINT32 req_rd_pend_v_ss_c          : 8;   // 23:16
} L9A0_MIFC_RD_REQ_PEND2_T;

typedef struct { // 0x28c8
	UINT32 req_wd_pend_v_ss_y          : 8;   //  7: 0
	UINT32 req_wd_pend_v_ss_c          : 8;   // 15: 8
	UINT32 req_wd_pend_v_tnr_y         : 8;   // 23:16
	UINT32 req_wd_pend_v_tnr_c         : 8;   // 31:24
} L9A0_MIFC_WD_REQ_PEND0_T;

typedef struct { // 0x28cc
	UINT32 req_wd_pend_v_prew_y        : 8;   //  7: 0
	UINT32 req_wd_pend_v_prew_c        : 8;   // 15: 8
} L9A0_MIFC_WD_REQ_PEND1_T;

typedef struct { // 0x28d0
	UINT32 cmd_rd_pri_s_v_mvi_y        : 4;   //  3: 0
	UINT32 cmd_rd_pri_s_v_mvi_c        : 4;   //  7: 4
	UINT32 cmd_rd_pri_s_v_prew_y       : 4;   // 11: 8
	UINT32 cmd_rd_pri_s_v_prew_c       : 4;   // 15:12
	UINT32 cmd_rd_pri_s_v_ipc0_y       : 4;   // 19:16
	UINT32 cmd_rd_pri_s_v_ipc_c        : 4;   // 23:20
	UINT32 cmd_rd_pri_s_v_ipc1_y       : 4;   // 27:24
	UINT32 cmd_rd_pri_s_v_tnr0_y       : 4;   // 31:28
} L9A0_MIFC_RD_CMD_PRI0_S_T;

typedef struct { // 0x28d4
	UINT32 cmd_rd_pri_s_v_tnr_c        : 4;   //  3: 0
	UINT32 cmd_rd_pri_s_v_ss_y         : 4;   //  7: 4
	UINT32 cmd_rd_pri_s_v_ss_c         : 4;   // 11: 8
} L9A0_MIFC_RD_CMD_PRI1_S_T;

typedef struct { // 0x28d8
	UINT32 cmd_wd_pri_s_v_ss_y         : 4;   //  3: 0
	UINT32 cmd_wd_pri_s_v_ss_c         : 4;   //  7: 4
	UINT32 cmd_wd_pri_s_v_tnr_y        : 4;   // 11: 8
	UINT32 cmd_wd_pri_s_v_tnr_c        : 4;   // 15:12
	UINT32 cmd_wd_pri_s_v_prew_y       : 4;   // 19:16
	UINT32 cmd_wd_pri_s_v_prew_c       : 4;   // 23:20
} L9A0_MIFC_WD_CMD_PRI0_S_T;

typedef struct { // 0x28dc
	UINT32 reset_mif_r_mvi_y           : 1;   //     0
	UINT32 reset_mif_r_mvi_c           : 1;   //     1
	UINT32 reset_mif_r_prew_y          : 1;   //     2
	UINT32 reset_mif_r_prew_c          : 1;   //     3
	UINT32 reset_mif_r_ipc0_y          : 1;   //     4
	UINT32 reset_mif_r_ipc_c           : 1;   //     5
	UINT32 reset_mif_r_ipc1_y          : 1;   //     6
	UINT32 reset_mif_r_tnr0_y          : 1;   //     7
	UINT32 reset_mif_r_tnr_c           : 1;   //     8
	UINT32 reset_mif_r_ss_y            : 1;   //     9
	UINT32 reset_mif_r_ss_c            : 1;   //    10
	UINT32 reset_mif_w_ss_y            : 1;   //    11
	UINT32 reset_mif_w_ss_c            : 1;   //    12
	UINT32 reset_mif_w_tnr_y           : 1;   //    13
	UINT32 reset_mif_w_tnr_c           : 1;   //    14
	UINT32 reset_mif_w_prew_y          : 1;   //    15
	UINT32 reset_mif_w_prew_c          : 1;   //    16
	UINT32                             : 3;   // 19:17
	UINT32 reset_time_out_cnt          : 12;  // 31:20
} L9A0_MIFC_RESET_T;

typedef struct { // 0x3e00
	UINT32 block_req_r_ov_y            : 1;   //     0
	UINT32 block_req_r_ov_c            : 1;   //     1
	UINT32 block_req_r_osd_0           : 1;   //     2
	UINT32 block_req_r_osd_1           : 1;   //     3
	UINT32 block_req_r_osd_2           : 1;   //     4
	UINT32 block_req_r_osd_3           : 1;   //     5
	UINT32 block_req_r_cve_y           : 1;   //     6
	UINT32 block_req_r_cve_c           : 1;   //     7
	UINT32                             : 4;   // 11: 8
	UINT32 disable_rd_mif              : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20
	UINT32 mrb_bank_mode               : 3;   // 23:21
} L9A0_MIFD_RD_CTRL_T;

typedef struct { // 0x3e04
	UINT32 block_req_w_sm_y            : 1;   //     0
	UINT32 block_req_w_sm_c            : 1;   //     1
	UINT32                             : 10;  // 11: 2
	UINT32 disable_wd_mif              : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
} L9A0_MIFD_WD_CTRL_T;

typedef struct { // 0x3e08
	UINT32 cmd_rd_pri_v_ov_y           : 4;   //  3: 0
	UINT32 cmd_rd_pri_v_ov_c           : 4;   //  7: 4
	UINT32 cmd_rd_pri_v_osd_0          : 4;   // 11: 8
	UINT32 cmd_rd_pri_v_osd_1          : 4;   // 15:12
	UINT32 cmd_rd_pri_v_osd_2          : 4;   // 19:16
	UINT32 cmd_rd_pri_v_osd_3          : 4;   // 23:20
	UINT32 cmd_rd_pri_v_cve_y          : 4;   // 27:24
	UINT32 cmd_rd_pri_v_cve_c          : 4;   // 31:28
} L9A0_MIFD_RD_CMD_PRI0_T;

typedef struct { // 0x3e0c
	UINT32 cmd_wd_pri_v_sm_y           : 4;   //  3: 0
	UINT32 cmd_wd_pri_v_sm_c           : 4;   //  7: 4
} L9A0_MIFD_WD_CMD_PRI0_T;

typedef struct { // 0x3e10
	UINT32 req_rd_pri_v_ov_y           : 4;   //  3: 0
	UINT32 req_rd_pri_v_ov_c           : 4;   //  7: 4
	UINT32 req_rd_pri_v_osd_0          : 4;   // 11: 8
	UINT32 req_rd_pri_v_osd_1          : 4;   // 15:12
	UINT32 req_rd_pri_v_osd_2          : 4;   // 19:16
	UINT32 req_rd_pri_v_osd_3          : 4;   // 23:20
	UINT32 req_rd_pri_v_cve_y          : 4;   // 27:24
	UINT32 req_rd_pri_v_cve_c          : 4;   // 31:28
} L9A0_MIFD_RD_REQ_PRI0_T;

typedef struct { // 0x3e14
	UINT32 req_wd_pri_v_scm_y          : 4;   //  3: 0
	UINT32 req_wd_pri_v_scm_c          : 4;   //  7: 4
} L9A0_MIFD_WD_REQ_PRI0_T;

typedef struct { // 0x3e18
	UINT32 req_rd_stv_v_ov_y           : 4;   //  3: 0
	UINT32 req_rd_stv_v_ov_c           : 4;   //  7: 4
	UINT32 req_rd_stv_v_osd_0          : 4;   // 11: 8
	UINT32 req_rd_stv_v_osd_1          : 4;   // 15:12
	UINT32 req_rd_stv_v_osd_2          : 4;   // 19:16
	UINT32 req_rd_stv_v_osd_3          : 4;   // 23:20
	UINT32 req_rd_stv_v_cve_y          : 4;   // 27:24
	UINT32 req_rd_stv_v_cve_c          : 4;   // 31:28
} L9A0_MIFD_RD_REQ_STV0_T;

typedef struct { // 0x3e1c
	UINT32 req_wd_stv_v_sm_y           : 4;   //  3: 0
	UINT32 req_wd_stv_v_sm_c           : 4;   //  7: 4
} L9A0_MIFD_WD_REQ_STV0_T;

typedef struct { // 0x3e20
	UINT32 cmd_rd_pend_v_ov_y          : 4;   //  3: 0
	UINT32 cmd_rd_pend_v_ov_c          : 4;   //  7: 4
	UINT32 cmd_rd_pend_v_osd_0         : 4;   // 11: 8
	UINT32 cmd_rd_pend_v_osd_1         : 4;   // 15:12
	UINT32 cmd_rd_pend_v_osd_2         : 4;   // 19:16
	UINT32 cmd_rd_pend_v_osd_3         : 4;   // 23:20
	UINT32 cmd_rd_pend_v_cve_y         : 4;   // 27:24
	UINT32 cmd_rd_pend_v_cve_c         : 4;   // 31:28
} L9A0_MIFD_RD_CMD_PEND0_T;

typedef struct { // 0x3e24
	UINT32 cmd_wd_pend_v_sm_y          : 4;   //  3: 0
	UINT32 cmd_wd_pend_v_sm_c          : 4;   //  7: 4
} L9A0_MIFD_WD_CMD_PEND1_T;

typedef struct { // 0x3e28
	UINT32 cmd_rd_stride_v_ov_y        : 4;   //  3: 0
	UINT32 cmd_rd_stride_v_ov_c        : 4;   //  7: 4
	UINT32 cmd_rd_stride_v_osd_0       : 4;   // 11: 8
	UINT32 cmd_rd_stride_v_osd_1       : 4;   // 15:12
	UINT32 cmd_rd_stride_v_osd_2       : 4;   // 19:16
	UINT32 cmd_rd_stride_v_osd_3       : 4;   // 23:20
	UINT32 cmd_rd_stride_v_cve_y       : 4;   // 27:24
	UINT32 cmd_rd_stride_v_cve_c       : 4;   // 31:28
} L9A0_MIFD_RD_CMD_STRIDE0_T;

typedef struct { // 0x3e2c
	UINT32 man_cmd_rd_stride_v_ov_y    : 1;   //     0
	UINT32 man_cmd_rd_stride_v_ov_c    : 1;   //     1
	UINT32 man_cmd_rd_stride_v_osd_0   : 1;   //     2
	UINT32 man_cmd_rd_stride_v_osd_1   : 1;   //     3
	UINT32 man_cmd_rd_stride_v_osd_2   : 1;   //     4
	UINT32 man_cmd_rd_stride_v_osd_3   : 1;   //     5
	UINT32 man_cmd_rd_stride_v_cve_y   : 1;   //     6
	UINT32 man_cmd_rd_stride_v_cve_c   : 1;   //     7
} L9A0_MIFD_RD_CMD_STRIDE_SET_T;

typedef struct { // 0x3e30
	UINT32 cmd_wd_stride_v_sm_y        : 4;   //  3: 0
	UINT32 cmd_wd_stride_v_sm_c        : 4;   //  7: 4
} L9A0_MIFD_WD_CMD_STRIDE0_T;

typedef struct { // 0x3e34
	UINT32 man_cmd_wd_stride_v_sm_y    : 1;   //     0
	UINT32 man_cmd_wd_stride_v_sm_c    : 1;   //     1
} L9A0_MIFD_WD_CMD_STRIDE_SET_T;

typedef struct { // 0x3e38
	UINT32 req_rd_saddr_ov_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_ov_c           : 15;  // 30:16
} L9A0_MIFD_SADDR_RD_OV_Y_OV_C_T;

typedef struct { // 0x3e3c
	UINT32 req_rd_saddr_osd_0          : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_osd_1          : 15;  // 30:16
} L9A0_MIFD_SADDR_RD_OSD_01_T;

typedef struct { // 0x3e40
	UINT32 req_rd_saddr_osd_2          : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_osd_3          : 15;  // 30:16
} L9A0_MIFD_SADDR_RD_OSD_23_T;

typedef struct { // 0x3e44
	UINT32 req_rd_saddr_cve_y          : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_rd_saddr_cve_c          : 15;  // 30:16
} L9A0_MIFD_SADDR_RD_CVE_YC_T;

typedef struct { // 0x3e48
	UINT32 req_wd_saddr_sm_y           : 15;  // 14: 0
	UINT32                             : 1;   //    15
	UINT32 req_wd_saddr_sm_c           : 15;  // 30:16
} L9A0_MIFD_SADDR_WD_SM_YC_T;

typedef struct { // 0x3e4c
	UINT32 req_rd_saddr_ov_y_msb4b     : 4;   //  3: 0
	UINT32 req_rd_saddr_ov_c_msb4b     : 4;   //  7: 4
	UINT32 req_rd_saddr_osd_0_msb4b    : 4;   // 11: 8
	UINT32 req_rd_saddr_osd_1_msb4b    : 4;   // 15:12
	UINT32 req_rd_saddr_osd_2_msb4b    : 4;   // 19:16
	UINT32 req_rd_saddr_osd_3_msb4b    : 4;   // 23:20
	UINT32 req_rd_saddr_cve_y_msb4b    : 4;   // 27:24
	UINT32 req_rd_saddr_cve_c_msb4b    : 4;   // 31:28
} L9A0_MIFD_SADDR_RD_EXT0_T;

typedef struct { // 0x3e50
	UINT32 req_wd_saddr_sm_y_msb4b     : 4;   //  3: 0
	UINT32 req_wd_saddr_sm_c_msb4b     : 4;   //  7: 4
} L9A0_MIFD_SADDR_WD_EXT0_T;

typedef struct { // 0x3e54
	UINT32 fr_rd_valid_ov_y            : 1;   //     0
	UINT32 fr_rd_valid_ov_c            : 1;   //     1
	UINT32 fr_rd_valid_osd_0           : 1;   //     2
	UINT32 fr_rd_valid_osd_1           : 1;   //     3
	UINT32 fr_rd_valid_osd_2           : 1;   //     4
	UINT32 fr_rd_valid_osd_3           : 1;   //     5
	UINT32 fr_rd_valid_cve_y           : 1;   //     6
	UINT32 fr_rd_valid_cve_c           : 1;   //     7
	UINT32 fr_wd_q_full_sm_y           : 1;   //     8
	UINT32 fr_wd_q_full_sm_c           : 1;   //     9
} L9A0_MIFD_STATUS_T;

typedef struct { // 0x3e58
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  // 10: 1
	UINT32 register_update_address0_m  : 21;  // 31:11
} L9A0_MIFD_SADDR_PARAM_UPDATE0_M_T;

typedef struct { // 0x3e5c
	UINT32 req_rd_bank_addr_8_ov_y     : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_rd_bank_addr_8_ov_c     : 3;   //  6: 4
	UINT32                             : 1;   //     7
	UINT32 req_rd_bank_addr_8_osd_0    : 3;   // 10: 8
	UINT32                             : 1;   //    11
	UINT32 req_rd_bank_addr_8_osd_1    : 3;   // 14:12
	UINT32                             : 1;   //    15
	UINT32 req_rd_bank_addr_8_osd_2    : 3;   // 18:16
	UINT32                             : 1;   //    19
	UINT32 req_rd_bank_addr_8_osd_3    : 3;   // 22:20
	UINT32                             : 1;   //    23
	UINT32 req_rd_bank_addr_8_cve_y    : 3;   // 26:24
	UINT32                             : 1;   //    27
	UINT32 req_rd_bank_addr_8_cve_c    : 3;   // 30:28
} L9A0_MIFD_RD_BANK_8_ADDR0_T;

typedef struct { // 0x3e60
	UINT32 mifd_rd_bank_8_addr1_f      : 32;   // 31: 0
} L9A0_MIFD_RD_BANK_8_ADDR1_T;

typedef struct { // 0x3e64
	UINT32 mifd_rd_bank_2_addr0_f      : 32;   // 31: 0
} L9A0_MIFD_RD_BANK_2_ADDR0_T;

typedef struct { // 0x3e68
	UINT32 mifd_rd_bank_2_addr1_f      : 32;   // 31: 0
} L9A0_MIFD_RD_BANK_2_ADDR1_T;

typedef struct { // 0x3e6c
	UINT32 req_wd_bank_addr_8_sm_y     : 3;   //  2: 0
	UINT32                             : 1;   //     3
	UINT32 req_wd_bank_addr_8_sm_c     : 3;   //  6: 4
} L9A0_MIFD_WD_BANK_8_ADDR0_T;

typedef struct { // 0x3e70
	UINT32 mifd_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9A0_MIFD_WD_BANK_8_ADDR1_T;

typedef struct { // 0x3e74
	UINT32 mifd_wd_bank_2_addr0_f      : 32;   // 31: 0
} L9A0_MIFD_WD_BANK_2_ADDR0_T;

typedef struct { // 0x3e78
	UINT32 mifd_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9A0_MIFD_WD_BANK_2_ADDR1_T;

typedef struct { // 0x3e7c
	UINT32 req_rd_pend_v_osd_0         : 8;   //  7: 0
	UINT32 req_rd_pend_v_osd_1         : 8;   // 15: 8
	UINT32 req_rd_pend_v_osd_2         : 8;   // 23:16
	UINT32 req_rd_pend_v_osd_3         : 8;   // 31:24
} L9A0_MIFD_RD_REQ_PEND0_T;

typedef struct { // 0x3e80
	UINT32 req_wd_pend_v_sm_y          : 8;   //  7: 0
	UINT32 req_wd_pend_v_sm_c          : 8;   // 15: 8
	UINT32 req_rd_pend_v_ov_y          : 8;   // 23:16
	UINT32 req_rd_pend_v_ov_c          : 8;   // 31:24
} L9A0_MIFD_WD_REQ_PEND0_T;

typedef struct { // 0x3e84
	UINT32 cmd_rd_pri_s_v_ov_y         : 4;   //  3: 0
	UINT32 cmd_rd_pri_s_v_ov_c         : 4;   //  7: 4
	UINT32 cmd_rd_pri_s_v_osd_0        : 4;   // 11: 8
	UINT32 cmd_rd_pri_s_v_osd_1        : 4;   // 15:12
	UINT32 cmd_rd_pri_s_v_osd_2        : 4;   // 19:16
	UINT32 cmd_rd_pri_s_v_osd_3        : 4;   // 23:20
	UINT32 cmd_rd_pri_s_v_cve_y        : 4;   // 27:24
	UINT32 cmd_rd_pri_s_v_cve_c        : 4;   // 31:28
} L9A0_MIFD_RD_CMD_PRI0_S_T;

typedef struct { // 0x3e88
	UINT32 cmd_wd_pri_s_v_sm_y         : 4;   //  3: 0
	UINT32 cmd_wd_pri_s_v_sm_c         : 4;   //  7: 4
} L9A0_MIFD_WD_CMD_PRI0_S_T;

typedef struct { // 0x3e8c
	UINT32 reset_mif_r_ov_y            : 1;   //     0
	UINT32 reset_mif_r_ov_c            : 1;   //     1
	UINT32 reset_mif_r_osd_0           : 1;   //     2
	UINT32 reset_mif_r_osd_1           : 1;   //     3
	UINT32 reset_mif_r_osd_2           : 1;   //     4
	UINT32 reset_mif_r_osd_3           : 1;   //     5
	UINT32 reset_mif_r_cve_y           : 1;   //     6
	UINT32 reset_mif_r_cve_c           : 1;   //     7
	UINT32 reset_mif_w_sm_y            : 1;   //     8
	UINT32 reset_mif_w_sm_c            : 1;   //     9
	UINT32                             : 10;  // 19:10
	UINT32 reset_time_out_cnt          : 12;  // 31:20
} L9A0_MIFD_RESET_T;

typedef struct {
	L9A0_MIFA_RD_CTRL_T                 mifa_rd_ctrl;                        // 0x0800
	L9A0_MIFA_WD_CTRL_T                 mifa_wd_ctrl;                        // 0x0804
	L9A0_MIF_RD_SET_10B_T               mif_rd_set_10b;                      // 0x0808
	L9A0_MIF_WD_SET_10B_T               mif_wd_set_10b;                      // 0x080c
	L9A0_MIFA_RD_CMD_PRI0_T             mifa_rd_cmd_pri0;                    // 0x0810
	L9A0_MIFA_RD_CMD_PRI1_T             mifa_rd_cmd_pri1;                    // 0x0814
	L9A0_MIFA_WD_CMD_PRI0_T             mifa_wd_cmd_pri0;                    // 0x0818
	L9A0_MIFA_RD_REQ_PRI0_T             mifa_rd_req_pri0;                    // 0x081c
	L9A0_MIFA_RD_REQ_PRI1_T             mifa_rd_req_pri1;                    // 0x0820
	L9A0_MIFA_WD_REQ_PRI0_T             mifa_wd_req_pri0;                    // 0x0824
	L9A0_MIFA_RD_REQ_STV0_T             mifa_rd_req_stv0;                    // 0x0828
	L9A0_MIFA_RD_REQ_STV1_T             mifa_rd_req_stv1;                    // 0x082c
	L9A0_MIFA_WD_REQ_STV0_T             mifa_wd_req_stv0;                    // 0x0830
	L9A0_MIFA_RD_CMD_PEND0_T            mifa_rd_cmd_pend0;                   // 0x0834
	L9A0_MIFA_RD_CMD_PEND1_T            mifa_rd_cmd_pend1;                   // 0x0838
	L9A0_MIFA_WD_CMD_PEND0_T            mifa_wd_cmd_pend0;                   // 0x083c
	L9A0_MIFA_RD_CMD_STRIDE0_T          mifa_rd_cmd_stride0;                 // 0x0840
	L9A0_MIFA_RD_CMD_STRIDE1_T          mifa_rd_cmd_stride1;                 // 0x0844
	L9A0_MIFA_RD_CMD_STRIDE2_T          mifa_rd_cmd_stride2;                 // 0x0848
	L9A0_MIFA_RD_CMD_STRIDE_SET_T       mifa_rd_cmd_stride_set;              // 0x084c
	L9A0_MIFA_WD_CMD_STRIDE0_T          mifa_wd_cmd_stride0;                 // 0x0850
	L9A0_MIFA_WD_CMD_STRIDE_SET_T       mifa_wd_cmd_stride_set;              // 0x0854
	L9A0_MIFA_SADDR_RD_MVI_Y_MVI_C_T    mifa_saddr_rd_mvi_y_mvi_c;           // 0x0858
	L9A0_MIFA_SADDR_RD_PREW_Y_T         mifa_saddr_rd_prew_y;                // 0x085c
	L9A0_MIFA_SADDR_RD_PREW_C_T         mifa_saddr_rd_prew_c;                // 0x0860
	L9A0_MIFA_SADDR_RD_IPC0_Y_T         mifa_saddr_rd_ipc0_y;                // 0x0864
	L9A0_MIFA_SADDR_RD_IPC_C_T          mifa_saddr_rd_ipc_c;                 // 0x0868
	L9A0_MIFA_SADDR_RD_IPC1_Y_T         mifa_saddr_rd_ipc1_y;                // 0x086c
	L9A0_MIFA_SADDR_RD_TNR0_Y_T         mifa_saddr_rd_tnr0_y;                // 0x0870
	L9A0_MIFA_SADDR_RD_TNR_C_T          mifa_saddr_rd_tnr_c;                 // 0x0874
	L9A0_MIFA_SADDR_RD_TNR1_Y_T         mifa_saddr_rd_tnr1_y;                // 0x0878
	L9A0_MIFA_SADDR_WD_TNR_Y_T          mifa_saddr_wd_tnr_y;                 // 0x087c
	L9A0_MIFA_SADDR_WD_TNR_C_T          mifa_saddr_wd_tnr_c;                 // 0x0880
	L9A0_MIFA_SADDR_WD_PREW_Y_T         mifa_saddr_wd_prew_y;                // 0x0884
	L9A0_MIFA_SADDR_WD_PREW_C_T         mifa_saddr_wd_prew_c;                // 0x0888
	L9A0_MIFA_SADDR_RD_DL_Y_T           mifa_saddr_rd_dl_y;                  // 0x088c
	L9A0_MIFA_SADDR_RD_DL_C_T           mifa_saddr_rd_dl_c;                  // 0x0890
	L9A0_MIFA_SADDR_RD_DR_Y_T           mifa_saddr_rd_dr_y;                  // 0x0894
	L9A0_MIFA_SADDR_RD_DR_C_T           mifa_saddr_rd_dr_c;                  // 0x0898
	L9A0_MIFA_SADDR_WD_DL_Y_T           mifa_saddr_wd_dl_y;                  // 0x089c
	L9A0_MIFA_SADDR_WD_DL_C_T           mifa_saddr_wd_dl_c;                  // 0x08a0
	L9A0_MIFA_SADDR_WD_DR_Y_T           mifa_saddr_wd_dr_y;                  // 0x08a4
	L9A0_MIFA_SADDR_WD_DR_C_T           mifa_saddr_wd_dr_c;                  // 0x08a8
	L9A0_MIFA_SADDR_RD_EXT0_T           mifa_saddr_rd_ext0;                  // 0x08ac
	L9A0_MIFA_SADDR_RD_EXT1_T           mifa_saddr_rd_ext1;                  // 0x08b0
	L9A0_MIFA_SADDR_RD_EXT2_T           mifa_saddr_rd_ext2;                  // 0x08b4
	L9A0_MIFA_SADDR_WD_EXT0_T           mifa_saddr_wd_ext0;                  // 0x08b8
	L9A0_MIFA_RD_DR_DL_EXT_T            mifa_rd_dr_dl_ext;                   // 0x08bc
	L9A0_MIFA_WD_DR_DL_EXT_T            mifa_wd_dr_dl_ext;                   // 0x08c0
	L9A0_MIFA_STATUS_T                  mifa_status;                         // 0x08c4
	L9A0_MIFA_SADDR_PARAM_UPDATE0_M_T   mifa_saddr_param_update0_m;          // 0x08c8
	L9A0_MIFA_SADDR_PARAM_UPDATE0_M1_T  mifa_saddr_param_update0_m1;         // 0x08cc
	L9A0_MIFA_RD_BANK_8_ADDR0_T         mifa_rd_bank_8_addr0;                // 0x08d0
	L9A0_MIFA_RD_BANK_8_ADDR1_T         mifa_rd_bank_8_addr1;                // 0x08d4
	L9A0_MIFA_RD_BANK_2_ADDR0_T         mifa_rd_bank_2_addr0;                // 0x08d8
	L9A0_MIFA_RD_BANK_2_ADDR1_T         mifa_rd_bank_2_addr1;                // 0x08dc
	L9A0_MIFA_WD_BANK_8_ADDR0_T         mifa_wd_bank_8_addr0;                // 0x08e0
	L9A0_MIFA_WD_BANK_8_ADDR1_T         mifa_wd_bank_8_addr1;                // 0x08e4
	L9A0_MIFA_WD_BANK_2_ADDR0_T         mifa_wd_bank_2_addr0;                // 0x08e8
	L9A0_MIFA_WD_BANK_2_ADDR1_T         mifa_wd_bank_2_addr1;                // 0x08ec
	L9A0_MIFA_LSB_SWITCH_T              mifa_lsb_switch;                     // 0x08f0
	L9A0_MIFA_RD_REQ_PEND0_T            mifa_rd_req_pend0;                   // 0x08f4
	L9A0_MIFA_RD_REQ_PEND1_T            mifa_rd_req_pend1;                   // 0x08f8
	L9A0_MIFA_RD_REQ_PEND2_T            mifa_rd_req_pend2;                   // 0x08fc
	L9A0_MIFA_WD_REQ_PEND0_T            mifa_wd_req_pend0;                   // 0x0900
	L9A0_MIFA_RD_CMD_PRI0_S_T           mifa_rd_cmd_pri0_s;                  // 0x0904
	L9A0_MIFA_RD_CMD_PRI1_S_T           mifa_rd_cmd_pri1_s;                  // 0x0908
	L9A0_MIFA_WD_CMD_PRI0_S_T           mifa_wd_cmd_pri0_s;                  // 0x090c
	L9A0_MIFA_RESET_T                   mifa_reset;                          // 0x0910
} DE_MIA_REG_L9A0_T;

typedef struct {
	L9A0_MIFB_RD_CTRL_T                 mifb_rd_ctrl;                        // 0x1b00
	L9A0_MIFB_WD_CTRL_T                 mifb_wd_ctrl;                        // 0x1b04
	L9A0_MIFB_RD_SET_10B_T              mifb_rd_set_10b;                     // 0x1b08
	L9A0_MIFB_WD_SET_10B_T              mifb_wd_set_10b;                     // 0x1b0c
	L9A0_MIFB_RD_CMD_PRI0_T             mifb_rd_cmd_pri0;                    // 0x1b10
	L9A0_MIFB_WD_CMD_PRI0_T             mifb_wd_cmd_pri0;                    // 0x1b14
	L9A0_MIFB_RD_REQ_PRI0_T             mifb_rd_req_pri0;                    // 0x1b18
	L9A0_MIFB_WD_REQ_PRI0_T             mifb_wd_req_pri0;                    // 0x1b1c
	L9A0_MIFB_RD_REQ_STV0_T             mifb_rd_req_stv0;                    // 0x1b20
	L9A0_MIFB_WD_REQ_STV0_T             mifb_wd_req_stv0;                    // 0x1b24
	L9A0_MIFB_RD_CMD_PEND0_T            mifb_rd_cmd_pend0;                   // 0x1b28
	L9A0_MIFB_WD_CMD_PEND0_T            mifb_wd_cmd_pend0;                   // 0x1b2c
	L9A0_MIFB_RD_CMD_STRIDE0_T          mifb_rd_cmd_stride0;                 // 0x1b30
	L9A0_MIFB_RD_CMD_STRIDE_SET_T       mifb_rd_cmd_stride_set;              // 0x1b34
	L9A0_MIFB_WD_CMD_STRIDE0_T          mifb_wd_cmd_stride0;                 // 0x1b38
	L9A0_MIFB_WD_CMD_STRIDE_SET_T       mifb_wd_cmd_stride_set;              // 0x1b3c
	L9A0_MIFB_SADDR_RD_OVM_Y_T          mifb_saddr_rd_ovm_y;                 // 0x1b40
	L9A0_MIFB_SADDR_RD_OVM_C_T          mifb_saddr_rd_ovm_c;                 // 0x1b44
	L9A0_MIFB_SADDR_RD_OVS_Y_OVS_C_T    mifb_saddr_rd_ovs_y_ovs_c;           // 0x1b48
	L9A0_MIFB_SADDR_WD_SM_Y_T           mifb_saddr_wd_sm_y;                  // 0x1b4c
	L9A0_MIFB_SADDR_WD_SM_C_T           mifb_saddr_wd_sm_c;                  // 0x1b50
	L9A0_MIFB_SADDR_RD_EXT0_T           mifb_saddr_rd_ext0;                  // 0x1b54
	L9A0_MIFB_SADDR_WD_EXT0_T           mifb_saddr_wd_ext0;                  // 0x1b58
	L9A0_MIFB_STATUS_T                  mifb_status;                         // 0x1b5c
	L9A0_MIFB_SADDR_PARAM_UPDATE0_M_T   mifb_saddr_param_update0_m;          // 0x1b60
	L9A0_MIFB_RD_BANK_8_ADDR0_T         mifb_rd_bank_8_addr0;                // 0x1b64
	L9A0_MIFB_RD_BANK_8_ADDR1_T         mifb_rd_bank_8_addr1;                // 0x1b68
	L9A0_MIFB_RD_BANK_2_ADDR0_T         mifb_rd_bank_2_addr0;                // 0x1b6c
	L9A0_MIFB_RD_BANK_2_ADDR1_T         mifb_rd_bank_2_addr1;                // 0x1b70
	L9A0_MIFB_WD_BANK_8_ADDR0_T         mifb_wd_bank_8_addr0;                // 0x1b74
	L9A0_MIFB_WD_BANK_8_ADDR1_T         mifb_wd_bank_8_addr1;                // 0x1b78
	L9A0_MIFB_WD_BANK_2_ADDR0_T         mifb_wd_bank_2_addr0;                // 0x1b7c
	L9A0_MIFB_WD_BANK_2_ADDR1_T         mifb_wd_bank_2_addr1;                // 0x1b80
	L9A0_MIFB_LSB_SWITCH_T              mifb_lsb_switch;                     // 0x1b84
	L9A0_MIFB_RD_REQ_PEND0_T            mifb_rd_req_pend0;                   // 0x1b88
	L9A0_MIFB_WD_REQ_PEND0_T            mifb_wd_req_pend0;                   // 0x1b8c
	L9A0_MIFB_RD_CMD_PRI00_S_T          mifb_rd_cmd_pri00_s;                 // 0x1b90
	L9A0_MIFB_WD_CMD_PRI00_S_T          mifb_wd_cmd_pri00_s;                 // 0x1b94
	L9A0_MIFB_RESET_T                   mifb_reset;                          // 0x1b98
} DE_MIB_REG_L9A0_T;

typedef struct {
	L9A0_MIFC_RD_CTRL_T                 mifc_rd_ctrl;                        // 0x2800
	L9A0_MIFC_WD_CTRL_T                 mifc_wd_ctrl;                        // 0x2804
	L9A0_MIFC_RD_CMD_PRI0_T             mifc_rd_cmd_pri0;                    // 0x2808
	L9A0_MIFC_RD_CMD_PRI1_T             mifc_rd_cmd_pri1;                    // 0x280c
	L9A0_MIFC_WD_CMD_PRI0_T             mifc_wd_cmd_pri0;                    // 0x2810
	L9A0_MIFC_RD_REQ_PRI0_T             mifc_rd_req_pri0;                    // 0x2814
	L9A0_MIFC_RD_REQ_PRI1_T             mifc_rd_req_pri1;                    // 0x2818
	L9A0_MIFC_WD_REQ_PRI0_T             mifc_wd_req_pri0;                    // 0x281c
	L9A0_MIFC_RD_REQ_STV0_T             mifc_rd_req_stv0;                    // 0x2820
	L9A0_MIFC_RD_REQ_STV1_T             mifc_rd_req_stv1;                    // 0x2824
	L9A0_MIFC_WD_REQ_STV0_T             mifc_wd_req_stv0;                    // 0x2828
	L9A0_MIFC_RD_CMD_PEND0_T            mifc_rd_cmd_pend0;                   // 0x282c
	L9A0_MIFC_RD_CMD_PEND1_T            mifc_rd_cmd_pend1;                   // 0x2830
	L9A0_MIFC_WD_CMD_PEND0_T            mifc_wd_cmd_pend0;                   // 0x2834
	L9A0_MIFC_RD_CMD_STRIDE0_T          mifc_rd_cmd_stride0;                 // 0x2838
	L9A0_MIFC_RD_CMD_STRIDE1_T          mifc_rd_cmd_stride1;                 // 0x283c
	L9A0_MIFC_RD_CMD_STRIDE_SET_T       mifc_rd_cmd_stride_set;              // 0x2840
	L9A0_MIFC_WD_CMD_STRIDE0_T          mifc_wd_cmd_stride0;                 // 0x2844
	L9A0_MIFC_WD_CMD_STRIDE_SET_T       mifc_wd_cmd_stride_set;              // 0x2848
	L9A0_MIFC_SADDR_RD_MVI_Y_MVI_C_T    mifc_saddr_rd_mvi_y_mvi_c;           // 0x284c
	L9A0_MIFC_SADDR_RD_PREW_Y_PREW_C_T  mifc_saddr_rd_prew_y_prew_c;         // 0x2850
	L9A0_MIFC_SADDR_RD_IPC0_Y_IPC_C_T   mifc_saddr_rd_ipc0_y_ipc_c;          // 0x2854
	L9A0_MIFC_SADDR_RD_IPC1_Y_TNR0_Y_T  mifc_saddr_rd_ipc1_y_tnr0_y;         // 0x2858
	L9A0_MIFC_SADDR_RD_SS_Y_SS_C_T      mifc_saddr_rd_ss_y_ss_c;             // 0x285c
	L9A0_MIFC_SADDR_RD_TNR_C_T          mifc_saddr_rd_tnr_c;                 // 0x2860
	L9A0_MIFC_SADDR_WD_SS_Y_SS_C_T      mifc_saddr_wd_ss_y_ss_c;             // 0x2864
	L9A0_MIFC_SADDR_WD_TNR_Y_TNR_C_T    mifc_saddr_wd_tnr_y_tnr_c;           // 0x2868
	L9A0_MIFC_SADDR_WD_PREW_Y_PREW_C_T  mifc_saddr_wd_prew_y_prew_c;         // 0x286c
	L9A0_MIFC_SADDR_RD_DL_Y_DL_C_T      mifc_saddr_rd_dl_y_dl_c;             // 0x2870
	L9A0_MIFC_SADDR_RD_DR_Y_DR_C_T      mifc_saddr_rd_dr_y_dr_c;             // 0x2874
	L9A0_MIFC_SADDR_WD_DL_Y_DL_C_T      mifc_saddr_wd_dl_y_dl_c;             // 0x2878
	L9A0_MIFC_SADDR_WD_DR_Y_DR_C_T      mifc_saddr_wd_dr_y_dr_c;             // 0x287c
	L9A0_MIFC_SADDR_RD_EXT0_T           mifc_saddr_rd_ext0;                  // 0x2880
	L9A0_MIFC_SADDR_RD_EXT1_T           mifc_saddr_rd_ext1;                  // 0x2884
	L9A0_MIFC_SADDR_WD_EXT0_T           mifc_saddr_wd_ext0;                  // 0x2888
	L9A0_MIFC_RD_DR_DL_EXT_T            mifc_rd_dr_dl_ext;                   // 0x288c
	L9A0_MIFC_WD_DR_DL_EXT_T            mifc_wd_dr_dl_ext;                   // 0x2890
	L9A0_MIFC_STATUS_T                  mifc_status;                         // 0x2894
	L9A0_MIFC_SADDR_PARAM_UPDATE0_M_T   mifc_saddr_param_update0_m;          // 0x2898
	L9A0_MIFC_RD_BANK_8_ADDR0_T         mifc_rd_bank_8_addr0;                // 0x289c
	L9A0_MIFC_RD_BANK_8_ADDR1_T         mifc_rd_bank_8_addr1;                // 0x28a0
	L9A0_MIFC_RD_BANK_2_ADDR0_T         mifc_rd_bank_2_addr0;                // 0x28a4
	L9A0_MIFC_RD_BANK_2_ADDR1_T         mifc_rd_bank_2_addr1;                // 0x28a8
	L9A0_MIFC_WD_BANK_8_ADDR0_T         mifc_wd_bank_8_addr0;                // 0x28ac
	L9A0_MIFC_WD_BANK_8_ADDR1_T         mifc_wd_bank_8_addr1;                // 0x28b0
	L9A0_MIFC_WD_BANK_2_ADDR0_T         mifc_wd_bank_2_addr0;                // 0x28b4
	L9A0_MIFC_WD_BANK_2_ADDR1_T         mifc_wd_bank_2_addr1;                // 0x28b8
	L9A0_MIFC_RD_REQ_PEND0_T            mifc_rd_req_pend0;                   // 0x28bc
	L9A0_MIFC_RD_REQ_PEND1_T            mifc_rd_req_pend1;                   // 0x28c0
	L9A0_MIFC_RD_REQ_PEND2_T            mifc_rd_req_pend2;                   // 0x28c4
	L9A0_MIFC_WD_REQ_PEND0_T            mifc_wd_req_pend0;                   // 0x28c8
	L9A0_MIFC_WD_REQ_PEND1_T            mifc_wd_req_pend1;                   // 0x28cc
	L9A0_MIFC_RD_CMD_PRI0_S_T           mifc_rd_cmd_pri0_s;                  // 0x28d0
	L9A0_MIFC_RD_CMD_PRI1_S_T           mifc_rd_cmd_pri1_s;                  // 0x28d4
	L9A0_MIFC_WD_CMD_PRI0_S_T           mifc_wd_cmd_pri0_s;                  // 0x28d8
	L9A0_MIFC_RESET_T                   mifc_reset;                          // 0x28dc
} DE_MIC_REG_L9A0_T;

typedef struct {
	L9A0_MIFD_RD_CTRL_T                 mifd_rd_ctrl;                        // 0x3e00
	L9A0_MIFD_WD_CTRL_T                 mifd_wd_ctrl;                        // 0x3e04
	L9A0_MIFD_RD_CMD_PRI0_T             mifd_rd_cmd_pri0;                    // 0x3e08
	L9A0_MIFD_WD_CMD_PRI0_T             mifd_wd_cmd_pri0;                    // 0x3e0c
	L9A0_MIFD_RD_REQ_PRI0_T             mifd_rd_req_pri0;                    // 0x3e10
	L9A0_MIFD_WD_REQ_PRI0_T             mifd_wd_req_pri0;                    // 0x3e14
	L9A0_MIFD_RD_REQ_STV0_T             mifd_rd_req_stv0;                    // 0x3e18
	L9A0_MIFD_WD_REQ_STV0_T             mifd_wd_req_stv0;                    // 0x3e1c
	L9A0_MIFD_RD_CMD_PEND0_T            mifd_rd_cmd_pend0;                   // 0x3e20
	L9A0_MIFD_WD_CMD_PEND1_T            mifd_wd_cmd_pend1;                   // 0x3e24
	L9A0_MIFD_RD_CMD_STRIDE0_T          mifd_rd_cmd_stride0;                 // 0x3e28
	L9A0_MIFD_RD_CMD_STRIDE_SET_T       mifd_rd_cmd_stride_set;              // 0x3e2c
	L9A0_MIFD_WD_CMD_STRIDE0_T          mifd_wd_cmd_stride0;                 // 0x3e30
	L9A0_MIFD_WD_CMD_STRIDE_SET_T       mifd_wd_cmd_stride_set;              // 0x3e34
	L9A0_MIFD_SADDR_RD_OV_Y_OV_C_T      mifd_saddr_rd_ov_y_ov_c;             // 0x3e38
	L9A0_MIFD_SADDR_RD_OSD_01_T         mifd_saddr_rd_osd_01;                // 0x3e3c
	L9A0_MIFD_SADDR_RD_OSD_23_T         mifd_saddr_rd_osd_23;                // 0x3e40
	L9A0_MIFD_SADDR_RD_CVE_YC_T         mifd_saddr_rd_cve_yc;                // 0x3e44
	L9A0_MIFD_SADDR_WD_SM_YC_T          mifd_saddr_wd_sm_yc;                 // 0x3e48
	L9A0_MIFD_SADDR_RD_EXT0_T           mifd_saddr_rd_ext0;                  // 0x3e4c
	L9A0_MIFD_SADDR_WD_EXT0_T           mifd_saddr_wd_ext0;                  // 0x3e50
	L9A0_MIFD_STATUS_T                  mifd_status;                         // 0x3e54
	L9A0_MIFD_SADDR_PARAM_UPDATE0_M_T   mifd_saddr_param_update0_m;          // 0x3e58
	L9A0_MIFD_RD_BANK_8_ADDR0_T         mifd_rd_bank_8_addr0;                // 0x3e5c
	L9A0_MIFD_RD_BANK_8_ADDR1_T         mifd_rd_bank_8_addr1;                // 0x3e60
	L9A0_MIFD_RD_BANK_2_ADDR0_T         mifd_rd_bank_2_addr0;                // 0x3e64
	L9A0_MIFD_RD_BANK_2_ADDR1_T         mifd_rd_bank_2_addr1;                // 0x3e68
	L9A0_MIFD_WD_BANK_8_ADDR0_T         mifd_wd_bank_8_addr0;                // 0x3e6c
	L9A0_MIFD_WD_BANK_8_ADDR1_T         mifd_wd_bank_8_addr1;                // 0x3e70
	L9A0_MIFD_WD_BANK_2_ADDR0_T         mifd_wd_bank_2_addr0;                // 0x3e74
	L9A0_MIFD_WD_BANK_2_ADDR1_T         mifd_wd_bank_2_addr1;                // 0x3e78
	L9A0_MIFD_RD_REQ_PEND0_T            mifd_rd_req_pend0;                   // 0x3e7c
	L9A0_MIFD_WD_REQ_PEND0_T            mifd_wd_req_pend0;                   // 0x3e80
	L9A0_MIFD_RD_CMD_PRI0_S_T           mifd_rd_cmd_pri0_s;                  // 0x3e84
	L9A0_MIFD_WD_CMD_PRI0_S_T           mifd_wd_cmd_pri0_s;                  // 0x3e88
	L9A0_MIFD_RESET_T                   mifd_reset;                          // 0x3e8c
} DE_MID_REG_L9A0_T;

#endif
