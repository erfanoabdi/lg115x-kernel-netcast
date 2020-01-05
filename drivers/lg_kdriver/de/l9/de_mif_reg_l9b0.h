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

#ifndef _REG_MIF_L9B0_h
#define _REG_MIF_L9B0_h

/*-----------------------------------------------------------------------------
	0x0800 mifa_rd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
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
	UINT32                             : 2;   // 10:11 reserved
	UINT32 disable_rd_mif              : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20 reserved
	UINT32 mrb_bank_mode               : 3;   // 21:23
} L9B0_MIFA_RD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0804 mifa_wd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 block_req_w_tnr_y           : 1;   //     0
	UINT32 block_req_w_tnr_c           : 1;   //     1
	UINT32 block_req_w_prew_y          : 1;   //     2
	UINT32 block_req_w_prew_c          : 1;   //     3
	UINT32                             : 8;   //  4:11 reserved
	UINT32 disable_wd_mif              : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20 reserved
	UINT32 mwb_bank_mode               : 3;   // 21:23
} L9B0_MIFA_WD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x0808 mif_rd_set_10b ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 set_10b_req_rd_prew_y       : 1;   //     0
	UINT32 set_10b_req_rd_prew_c       : 1;   //     1
	UINT32 set_10b_req_rd_ipc0_y       : 1;   //     2
	UINT32 set_10b_req_rd_ipc_c        : 1;   //     3
	UINT32 set_10b_req_rd_ipc1_y       : 1;   //     4
	UINT32 set_10b_req_rd_tnr0_y       : 1;   //     5
	UINT32 set_10b_req_rd_tnr_c        : 1;   //     6
	UINT32 set_10b_req_rd_tnr1_y       : 1;   //     7
} L9B0_MIF_RD_SET_10B_T;

/*-----------------------------------------------------------------------------
	0x080c mif_wd_set_10b ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 set_10b_req_wd_tnr_y        : 1;   //     0
	UINT32 set_10b_req_wd_tnr_c        : 1;   //     1
	UINT32 set_10b_req_wd_prew_y       : 1;   //     2
	UINT32 set_10b_req_wd_prew_c       : 1;   //     3
} L9B0_MIF_WD_SET_10B_T;

/*-----------------------------------------------------------------------------
	0x0810 mifa_rd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_v_mvi_y          : 4;   //  0: 3
	UINT32 cmd_rd_pri_v_mvi_c          : 4;   //  4: 7
	UINT32 cmd_rd_pri_v_prew_y         : 4;   //  8:11
	UINT32 cmd_rd_pri_v_prew_c         : 4;   // 12:15
	UINT32 cmd_rd_pri_v_ipc0_y         : 4;   // 16:19
	UINT32 cmd_rd_pri_v_ipc_c          : 4;   // 20:23
	UINT32 cmd_rd_pri_v_ipc1_y         : 4;   // 24:27
	UINT32 cmd_rd_pri_v_tnr0_y         : 4;   // 28:31
} L9B0_MIFA_RD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x0814 mifa_rd_cmd_pri1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_v_tnr_c          : 4;   //  0: 3
	UINT32 cmd_rd_pri_v_tnr1_y         : 4;   //  4: 7
} L9B0_MIFA_RD_CMD_PRI1_T;

/*-----------------------------------------------------------------------------
	0x0818 mifa_wd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_v_tnr_y          : 4;   //  0: 3
	UINT32 cmd_wd_pri_v_tnr_c          : 4;   //  4: 7
	UINT32 cmd_wd_pri_v_prew_y         : 4;   //  8:11
	UINT32 cmd_wd_pri_v_prew_c         : 4;   // 12:15
} L9B0_MIFA_WD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x081c mifa_rd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_mvi_y          : 4;   //  0: 3
	UINT32 req_rd_pri_v_mvi_c          : 4;   //  4: 7
	UINT32 req_rd_pri_v_prew_y         : 4;   //  8:11
	UINT32 req_rd_pri_v_prew_c         : 4;   // 12:15
	UINT32 req_rd_pri_v_ipc0_y         : 4;   // 16:19
	UINT32 req_rd_pri_v_ipc_c          : 4;   // 20:23
	UINT32 req_rd_pri_v_ipc1_y         : 4;   // 24:27
	UINT32 req_rd_pri_v_tnr0_y         : 4;   // 28:31
} L9B0_MIFA_RD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x0820 mifa_rd_req_pri1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_tnr_c          : 4;   //  0: 3
	UINT32 req_rd_pri_v_tnr1_y         : 4;   //  4: 7
} L9B0_MIFA_RD_REQ_PRI1_T;

/*-----------------------------------------------------------------------------
	0x0824 mifa_wd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pri_v_tnr_y          : 4;   //  0: 3
	UINT32 req_wd_pri_v_tnr_c          : 4;   //  4: 7
	UINT32 req_wd_pri_v_prew_y         : 4;   //  8:11
	UINT32 req_wd_pri_v_prew_c         : 4;   // 12:15
} L9B0_MIFA_WD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x0828 mifa_rd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_stv_v_mvi_y          : 4;   //  0: 3
	UINT32 req_rd_stv_v_mvi_c          : 4;   //  4: 7
	UINT32 req_rd_stv_v_prew_y         : 4;   //  8:11
	UINT32 req_rd_stv_v_prew_c         : 4;   // 12:15
	UINT32 req_rd_stv_v_ipc0_y         : 4;   // 16:19
	UINT32 req_rd_stv_v_ipc_c          : 4;   // 20:23
	UINT32 req_rd_stv_v_ipc1_y         : 4;   // 24:27
	UINT32 req_rd_stv_v_tnr0_y         : 4;   // 28:31
} L9B0_MIFA_RD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x082c mifa_rd_req_stv1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_stv_v_tnr_c          : 4;   //  0: 3
	UINT32 req_rd_stv_v_tnr1_y         : 4;   //  4: 7
} L9B0_MIFA_RD_REQ_STV1_T;

/*-----------------------------------------------------------------------------
	0x0830 mifa_wd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_stv_v_tnr_y          : 4;   //  0: 3
	UINT32 req_wd_stv_v_tnr_c          : 4;   //  4: 7
	UINT32 req_wd_stv_v_prew_y         : 4;   //  8:11
	UINT32 req_wd_stv_v_prew_c         : 4;   // 12:15
} L9B0_MIFA_WD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x0834 mifa_rd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pend_v_mvi_y         : 4;   //  0: 3
	UINT32 cmd_rd_pend_v_mvi_c         : 4;   //  4: 7
	UINT32 cmd_rd_pend_v_prew_y        : 4;   //  8:11
	UINT32 cmd_rd_pend_v_prew_c        : 4;   // 12:15
	UINT32 cmd_rd_pend_v_ipc0_y        : 4;   // 16:19
	UINT32 cmd_rd_pend_v_ipc_c         : 4;   // 20:23
	UINT32 cmd_rd_pend_v_ipc1_y        : 4;   // 24:27
	UINT32 cmd_rd_pend_v_tnr0_y        : 4;   // 28:31
} L9B0_MIFA_RD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x0838 mifa_rd_cmd_pend1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pend_v_tnr_c         : 4;   //  0: 3
	UINT32 cmd_rd_pend_v_tnr1_y        : 4;   //  4: 7
} L9B0_MIFA_RD_CMD_PEND1_T;

/*-----------------------------------------------------------------------------
	0x083c mifa_wd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pend_v_tnr_y         : 4;   //  0: 3
	UINT32 cmd_wd_pend_v_tnr_c         : 4;   //  4: 7
	UINT32 cmd_wd_pend_v_prew_y        : 4;   //  8:11
	UINT32 cmd_wd_pend_v_prew_c        : 4;   // 12:15
} L9B0_MIFA_WD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x0840 mifa_rd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_mvi_y       : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_mvi_c       : 4;   //  4: 7
	UINT32 cmd_rd_stride_v_2_prew_y    : 4;   //  8:11
	UINT32 cmd_rd_stride_v_8_prew_y    : 4;   // 12:15
	UINT32 cmd_rd_stride_v_2_prew_c    : 4;   // 16:19
	UINT32 cmd_rd_stride_v_8_prew_c    : 4;   // 20:23
	UINT32 cmd_rd_stride_v_2_ipc0_y    : 4;   // 24:27
	UINT32 cmd_rd_stride_v_8_ipc0_y    : 4;   // 28:31
} L9B0_MIFA_RD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x0844 mifa_rd_cmd_stride1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_2_ipc_c     : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_8_ipc_c     : 4;   //  4: 7
	UINT32 cmd_rd_stride_v_2_ipc1_y    : 4;   //  8:11
	UINT32 cmd_rd_stride_v_8_ipc1_y    : 4;   // 12:15
	UINT32 cmd_rd_stride_v_2_tnr0_y    : 4;   // 16:19
	UINT32 cmd_rd_stride_v_8_tnr0_y    : 4;   // 20:23
	UINT32 cmd_rd_stride_v_2_tnr_c     : 4;   // 24:27
	UINT32 cmd_rd_stride_v_8_tnr_c     : 4;   // 28:31
} L9B0_MIFA_RD_CMD_STRIDE1_T;

/*-----------------------------------------------------------------------------
	0x0848 mifa_rd_cmd_stride2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_2_tnr1_y    : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_8_tnr1_y    : 4;   //  4: 7
} L9B0_MIFA_RD_CMD_STRIDE2_T;

/*-----------------------------------------------------------------------------
	0x084c mifa_rd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
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
} L9B0_MIFA_RD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x0850 mifa_wd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_stride_v_2_tnr_y     : 4;   //  0: 3
	UINT32 cmd_wd_stride_v_8_tnr_y     : 4;   //  4: 7
	UINT32 cmd_wd_stride_v_2_tnr_c     : 4;   //  8:11
	UINT32 cmd_wd_stride_v_8_tnr_c     : 4;   // 12:15
	UINT32 cmd_wd_stride_v_2_prew_y    : 4;   // 16:19
	UINT32 cmd_wd_stride_v_8_prew_y    : 4;   // 20:23
	UINT32 cmd_wd_stride_v_2_prew_c    : 4;   // 24:27
	UINT32 cmd_wd_stride_v_8_prew_c    : 4;   // 28:31
} L9B0_MIFA_WD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x0854 mifa_wd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 man_cmd_wd_stride_v_tnr_y   : 1;   //     0
	UINT32 man_cmd_wd_stride_v_tnr_c   : 1;   //     1
	UINT32 man_cmd_wd_stride_v_prew_y  : 1;   //     2
	UINT32 man_cmd_wd_stride_v_prew_c  : 1;   //     3
} L9B0_MIFA_WD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x0858 mifa_saddr_rd_mvi_y_mvi_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_mvi_y          : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_mvi_c          : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_MVI_Y_MVI_C_T;

/*-----------------------------------------------------------------------------
	0x085c mifa_saddr_rd_prew_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_prew_y       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_prew_y       : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_PREW_Y_T;

/*-----------------------------------------------------------------------------
	0x0860 mifa_saddr_rd_prew_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_prew_c       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_prew_c       : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_PREW_C_T;

/*-----------------------------------------------------------------------------
	0x0864 mifa_saddr_rd_ipc0_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_ipc0_y       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_ipc0_y       : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_IPC0_Y_T;

/*-----------------------------------------------------------------------------
	0x0868 mifa_saddr_rd_ipc_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_ipc_c        : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_ipc_c        : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_IPC_C_T;

/*-----------------------------------------------------------------------------
	0x086c mifa_saddr_rd_ipc1_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_ipc1_y       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_ipc1_y       : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_IPC1_Y_T;

/*-----------------------------------------------------------------------------
	0x0870 mifa_saddr_rd_tnr0_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_tnr0_y       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_tnr0_y       : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_TNR0_Y_T;

/*-----------------------------------------------------------------------------
	0x0874 mifa_saddr_rd_tnr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_tnr_c        : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_tnr_c        : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_TNR_C_T;

/*-----------------------------------------------------------------------------
	0x0878 mifa_saddr_rd_tnr1_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_tnr1_y       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_tnr1_y       : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_TNR1_Y_T;

/*-----------------------------------------------------------------------------
	0x087c mifa_saddr_wd_tnr_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_tnr_y        : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_tnr_y        : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_TNR_Y_T;

/*-----------------------------------------------------------------------------
	0x0880 mifa_saddr_wd_tnr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_tnr_c        : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_tnr_c        : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_TNR_C_T;

/*-----------------------------------------------------------------------------
	0x0884 mifa_saddr_wd_prew_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_prew_y       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_prew_y       : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_PREW_Y_T;

/*-----------------------------------------------------------------------------
	0x0888 mifa_saddr_wd_prew_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_prew_c       : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_prew_c       : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_PREW_C_T;

/*-----------------------------------------------------------------------------
	0x088c mifa_saddr_rd_dl_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_dl_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_dl_y         : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_DL_Y_T;

/*-----------------------------------------------------------------------------
	0x0890 mifa_saddr_rd_dl_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_dl_c         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_dl_c         : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_DL_C_T;

/*-----------------------------------------------------------------------------
	0x0894 mifa_saddr_rd_dr_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_dr_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_dr_y         : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_DR_Y_T;

/*-----------------------------------------------------------------------------
	0x0898 mifa_saddr_rd_dr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_dr_c         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_dr_c         : 15;  // 16:30
} L9B0_MIFA_SADDR_RD_DR_C_T;

/*-----------------------------------------------------------------------------
	0x089c mifa_saddr_wd_dl_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_dl_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_dl_y         : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_DL_Y_T;

/*-----------------------------------------------------------------------------
	0x08a0 mifa_saddr_wd_dl_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_dl_c         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_dl_c         : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_DL_C_T;

/*-----------------------------------------------------------------------------
	0x08a4 mifa_saddr_wd_dr_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_dr_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_dr_y         : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_DR_Y_T;

/*-----------------------------------------------------------------------------
	0x08a8 mifa_saddr_wd_dr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_dr_c         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_dr_c         : 15;  // 16:30
} L9B0_MIFA_SADDR_WD_DR_C_T;

/*-----------------------------------------------------------------------------
	0x08ac mifa_saddr_rd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_mvi_y_msb4b    : 4;   //  0: 3
	UINT32 req_rd_saddr_mvi_c_msb4b    : 4;   //  4: 7
	UINT32 req_rd_saddr_2_prew_y_msb4b : 4;   //  8:11
	UINT32 req_rd_saddr_8_prew_y_msb4b : 4;   // 12:15
	UINT32 req_rd_saddr_2_prew_c_msb4b : 4;   // 16:19
	UINT32 req_rd_saddr_8_prew_c_msb4b : 4;   // 20:23
	UINT32 req_rd_saddr_2_ipc0_y_msb4b : 4;   // 24:27
	UINT32 req_rd_saddr_8_ipc0_y_msb4b : 4;   // 28:31
} L9B0_MIFA_SADDR_RD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x08b0 mifa_saddr_rd_ext1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_ipc_c_msb4b  : 4;   //  0: 3
	UINT32 req_rd_saddr_8_ipc_c_msb4b  : 4;   //  4: 7
	UINT32 req_rd_saddr_2_ipc1_y_msb4b : 4;   //  8:11
	UINT32 req_rd_saddr_8_ipc1_y_msb4b : 4;   // 12:15
	UINT32 req_rd_saddr_2_tnr0_y_msb4b : 4;   // 16:19
	UINT32 req_rd_saddr_8_tnr0_y_msb4b : 4;   // 20:23
	UINT32 req_rd_saddr_2_tnr_c_msb4b  : 4;   // 24:27
	UINT32 req_rd_saddr_8_tnr_c_msb4b  : 4;   // 28:31
} L9B0_MIFA_SADDR_RD_EXT1_T;

/*-----------------------------------------------------------------------------
	0x08b4 mifa_saddr_rd_ext2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_tnr1_y_msb4b : 4;   //  0: 3
	UINT32 req_rd_saddr_8_tnr1_y_msb4b : 4;   //  4: 7
} L9B0_MIFA_SADDR_RD_EXT2_T;

/*-----------------------------------------------------------------------------
	0x08b8 mifa_saddr_wd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_tnr_y_msb4b  : 4;   //  0: 3
	UINT32 req_wd_saddr_8_tnr_y_msb4b  : 4;   //  4: 7
	UINT32 req_wd_saddr_2_tnr_c_msb4b  : 4;   //  8:11
	UINT32 req_wd_saddr_8_tnr_c_msb4b  : 4;   // 12:15
	UINT32 req_wd_saddr_2_prew_y_msb4b : 4;   // 16:19
	UINT32 req_wd_saddr_8_prew_y_msb4b : 4;   // 20:23
	UINT32 req_wd_saddr_2_prew_c_msb4b : 4;   // 24:27
	UINT32 req_wd_saddr_8_prew_c_msb4b : 4;   // 28:31
} L9B0_MIFA_SADDR_WD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x08bc mifa_rd_dr_dl_ext ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_dl_y_msb4b   : 4;   //  0: 3
	UINT32 req_rd_saddr_8_dl_y_msb4b   : 4;   //  4: 7
	UINT32 req_rd_saddr_2_dl_c_msb4b   : 4;   //  8:11
	UINT32 req_rd_saddr_8_dl_c_msb4b   : 4;   // 12:15
	UINT32 req_rd_saddr_2_dr_y_msb4b   : 4;   // 16:19
	UINT32 req_rd_saddr_8_dr_y_msb4b   : 4;   // 20:23
	UINT32 req_rd_saddr_2_dr_c_msb4b   : 4;   // 24:27
	UINT32 req_rd_saddr_8_dr_c_msb4b   : 4;   // 28:31
} L9B0_MIFA_RD_DR_DL_EXT_T;

/*-----------------------------------------------------------------------------
	0x08c0 mifa_wd_dr_dl_ext ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_dl_y_msb4b   : 4;   //  0: 3
	UINT32 req_wd_saddr_8_dl_y_msb4b   : 4;   //  4: 7
	UINT32 req_wd_saddr_2_dl_c_msb4b   : 4;   //  8:11
	UINT32 req_wd_saddr_8_dl_c_msb4b   : 4;   // 12:15
	UINT32 req_wd_saddr_2_dr_y_msb4b   : 4;   // 16:19
	UINT32 req_wd_saddr_8_dr_y_msb4b   : 4;   // 20:23
	UINT32 req_wd_saddr_2_dr_c_msb4b   : 4;   // 24:27
	UINT32 req_wd_saddr_8_dr_c_msb4b   : 4;   // 28:31
} L9B0_MIFA_WD_DR_DL_EXT_T;

/*-----------------------------------------------------------------------------
	0x08c4 mifa_status ''
------------------------------------------------------------------------------*/
typedef struct {
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
} L9B0_MIFA_STATUS_T;

/*-----------------------------------------------------------------------------
	0x08c8 mifa_saddr_param_update0_m ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  //  1:10 reserved
	UINT32 register_update_address0_m  : 21;  // 11:31
} L9B0_MIFA_SADDR_PARAM_UPDATE0_M_T;

/*-----------------------------------------------------------------------------
	0x08cc mifa_saddr_param_update0_m1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  //  1:10 reserved
	UINT32 register_update_address0_m1 : 21;  // 11:31
} L9B0_MIFA_SADDR_PARAM_UPDATE0_M1_T;

/*-----------------------------------------------------------------------------
	0x08d0 mifa_rd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_8_mvi_y    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_8_mvi_c    : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_rd_bank_addr_8_prew_y   : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_rd_bank_addr_8_prew_c   : 3;   // 12:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_bank_addr_8_ipc0_y   : 3;   // 16:18
	UINT32                             : 1;   //    19 reserved
	UINT32 req_rd_bank_addr_8_ipc_c    : 3;   // 20:22
	UINT32                             : 1;   //    23 reserved
	UINT32 req_rd_bank_addr_8_ipc1_y   : 3;   // 24:26
	UINT32                             : 1;   //    27 reserved
	UINT32 req_rd_bank_addr_8_tnr0_y   : 3;   // 28:30
} L9B0_MIFA_RD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x08d4 mifa_rd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_8_tnr_c    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_8_tnr1_y   : 3;   //  4: 6
} L9B0_MIFA_RD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x08d8 mifa_rd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32                             : 8;   //  0: 7 reserved
	UINT32 req_rd_bank_addr_2_prew_y   : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_rd_bank_addr_2_prew_c   : 3;   // 12:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_bank_addr_2_ipc0_y   : 3;   // 16:18
	UINT32                             : 1;   //    19 reserved
	UINT32 req_rd_bank_addr_2_ipc_c    : 3;   // 20:22
	UINT32                             : 1;   //    23 reserved
	UINT32 req_rd_bank_addr_2_ipc1_y   : 3;   // 24:26
	UINT32                             : 1;   //    27 reserved
	UINT32 req_rd_bank_addr_2_tnr0_y   : 3;   // 28:30
} L9B0_MIFA_RD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x08dc mifa_rd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_2_tnr_c    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_2_tnr1_y   : 3;   //  4: 6
} L9B0_MIFA_RD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x08e0 mifa_wd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_bank_addr_8_tnr_y    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_wd_bank_addr_8_tnr_c    : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_wd_bank_addr_8_prew_y   : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_wd_bank_addr_8_prew_c   : 3;   // 12:14
} L9B0_MIFA_WD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x08e4 mifa_wd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifa_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9B0_MIFA_WD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x08e8 mifa_wd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_bank_addr_2_tnr_y    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_wd_bank_addr_2_tnr_c    : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_wd_bank_addr_2_prew_y   : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_wd_bank_addr_2_prew_c   : 3;   // 12:14
} L9B0_MIFA_WD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x08ec mifa_wd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifa_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFA_WD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x08f0 mifa_lsb_switch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_lsb_prew_y           : 2;   //  0: 1
	UINT32 req_rd_lsb_prew_c           : 2;   //  2: 3
	UINT32 req_rd_lsb_ipc0_y           : 2;   //  4: 5
	UINT32 req_rd_lsb_ipc_c            : 2;   //  6: 7
	UINT32 req_rd_lsb_ipc1_y           : 2;   //  8: 9
	UINT32 req_rd_lsb_tnr0_y           : 2;   // 10:11
	UINT32 req_rd_lsb_tnr_c            : 2;   // 12:13
	UINT32 req_rd_lsb_tnr1_y           : 2;   // 14:15
} L9B0_MIFA_LSB_SWITCH_T;

/*-----------------------------------------------------------------------------
	0x08f4 mifa_rd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_mvi_y         : 8;   //  0: 7
	UINT32 req_rd_pend_v_mvi_c         : 8;   //  8:15
	UINT32 req_rd_pend_v_prew_y        : 8;   // 16:23
	UINT32 req_rd_pend_v_prew_c        : 8;   // 24:31
} L9B0_MIFA_RD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x08f8 mifa_rd_req_pend1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_ipc0_y        : 8;   //  0: 7
	UINT32 req_rd_pend_v_ipc_c         : 8;   //  8:15
	UINT32 req_rd_pend_v_ipc1_y        : 8;   // 16:23
	UINT32 req_rd_pend_v_tnr0_y        : 8;   // 24:31
} L9B0_MIFA_RD_REQ_PEND1_T;

/*-----------------------------------------------------------------------------
	0x08fc mifa_rd_req_pend2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_tnr_c         : 8;   //  0: 7
	UINT32 req_rd_pend_v_tnr1_y        : 8;   //  8:15
} L9B0_MIFA_RD_REQ_PEND2_T;

/*-----------------------------------------------------------------------------
	0x0900 mifa_wd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pend_v_tnr_y         : 8;   //  0: 7
	UINT32 req_wd_pend_v_tnr_c         : 8;   //  8:15
	UINT32 req_wd_pend_v_prew_y        : 8;   // 16:23
	UINT32 req_wd_pend_v_prew_c        : 8;   // 24:31
} L9B0_MIFA_WD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x0904 mifa_rd_cmd_pri0_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_s_v_mvi_y        : 4;   //  0: 3
	UINT32 cmd_rd_pri_s_v_mvi_c        : 4;   //  4: 7
	UINT32 cmd_rd_pri_s_v_prew_y       : 4;   //  8:11
	UINT32 cmd_rd_pri_s_v_prew_c       : 4;   // 12:15
	UINT32 cmd_rd_pri_s_v_ipc0_y       : 4;   // 16:19
	UINT32 cmd_rd_pri_s_v_ipc_c        : 4;   // 20:23
	UINT32 cmd_rd_pri_s_v_ipc1_y       : 4;   // 24:27
	UINT32 cmd_rd_pri_s_v_tnr0_y       : 4;   // 28:31
} L9B0_MIFA_RD_CMD_PRI0_S_T;

/*-----------------------------------------------------------------------------
	0x0908 mifa_rd_cmd_pri1_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_s_v_tnr_c        : 4;   //  0: 3
	UINT32 cmd_rd_pri_s_v_tnr1_y       : 4;   //  4: 7
} L9B0_MIFA_RD_CMD_PRI1_S_T;

/*-----------------------------------------------------------------------------
	0x090c mifa_wd_cmd_pri0_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_s_v_tnr_y        : 4;   //  0: 3
	UINT32 cmd_wd_pri_s_v_tnr_c        : 4;   //  4: 7
	UINT32 cmd_wd_pri_s_v_prew_y       : 4;   //  8:11
	UINT32 cmd_wd_pri_s_v_prew_c       : 4;   // 12:15
} L9B0_MIFA_WD_CMD_PRI0_S_T;

/*-----------------------------------------------------------------------------
	0x0910 mifa_reset ''
------------------------------------------------------------------------------*/
typedef struct {
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
	UINT32                             : 6;   // 14:19 reserved
	UINT32 reset_time_out_cnt          : 12;  // 20:31
} L9B0_MIFA_RESET_T;

/*-----------------------------------------------------------------------------
	0x1b00 mifb_rd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 block_req_r_ovm_y           : 1;   //     0
	UINT32 block_req_r_ovm_c           : 1;   //     1
	UINT32 block_req_r_ovs_y           : 1;   //     2
	UINT32 block_req_r_ovs_c           : 1;   //     3
	UINT32                             : 8;   //  4:11 reserved
	UINT32 disable_rd_mif              : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
} L9B0_MIFB_RD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1b04 mifb_wd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 block_req_w_scm_y           : 1;   //     0
	UINT32 block_req_w_scm_c           : 1;   //     1
	UINT32                             : 10;  //  2:11 reserved
	UINT32 disable_wd_mif              : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
} L9B0_MIFB_WD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x1b08 mifb_rd_set_10b ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 set_10b_req_rd_ovm_y        : 1;   //     0
	UINT32 set_10b_req_rd_ovm_c        : 1;   //     1
} L9B0_MIFB_RD_SET_10B_T;

/*-----------------------------------------------------------------------------
	0x1b0c mifb_wd_set_10b ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 set_10b_req_wd_scm_y        : 1;   //     0
	UINT32 set_10b_req_wd_scm_c        : 1;   //     1
} L9B0_MIFB_WD_SET_10B_T;

/*-----------------------------------------------------------------------------
	0x1b10 mifb_rd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_v_ovm_y          : 4;   //  0: 3
	UINT32 cmd_rd_pri_v_ovm_c          : 4;   //  4: 7
	UINT32 cmd_rd_pri_v_ovs_y          : 4;   //  8:11
	UINT32 cmd_rd_pri_v_ovs_c          : 4;   // 12:15
} L9B0_MIFB_RD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x1b14 mifb_wd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_v_sm_y           : 4;   //  0: 3
	UINT32 cmd_wd_pri_v_sm_c           : 4;   //  4: 7
} L9B0_MIFB_WD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x1b18 mifb_rd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_ovm_y          : 4;   //  0: 3
	UINT32 req_rd_pri_v_ovm_c          : 4;   //  4: 7
	UINT32 req_rd_pri_v_ovs_y          : 4;   //  8:11
	UINT32 req_rd_pri_v_ovs_c          : 4;   // 12:15
} L9B0_MIFB_RD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x1b1c mifb_wd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pri_v_sm_y           : 4;   //  0: 3
	UINT32 req_wd_pri_v_sm_c           : 4;   //  4: 7
} L9B0_MIFB_WD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x1b20 mifb_rd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_stv_v_ovm_y          : 4;   //  0: 3
	UINT32 req_rd_stv_v_ovm_c          : 4;   //  4: 7
	UINT32 req_rd_stv_v_ovs_y          : 4;   //  8:11
	UINT32 req_rd_stv_v_ovs_c          : 4;   // 12:15
} L9B0_MIFB_RD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x1b24 mifb_wd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_stv_v_sm_y           : 4;   //  0: 3
	UINT32 req_wd_stv_v_sm_c           : 4;   //  4: 7
} L9B0_MIFB_WD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x1b28 mifb_rd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pend_v_ovm_y         : 4;   //  0: 3
	UINT32 cmd_rd_pend_v_ovm_c         : 4;   //  4: 7
	UINT32 cmd_rd_pend_v_ovs_y         : 4;   //  8:11
	UINT32 cmd_rd_pend_v_ovs_c         : 4;   // 12:15
} L9B0_MIFB_RD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x1b2c mifb_wd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pend_v_sm_y          : 4;   //  0: 3
	UINT32 cmd_wd_pend_v_sm_c          : 4;   //  4: 7
} L9B0_MIFB_WD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x1b30 mifb_rd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_2_ovm_y     : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_8_ovm_y     : 4;   //  4: 7
	UINT32 cmd_rd_stride_v_2_ovm_c     : 4;   //  8:11
	UINT32 cmd_rd_stride_v_8_ovm_c     : 4;   // 12:15
	UINT32 cmd_rd_stride_v_ovs_y       : 4;   // 16:19
	UINT32 cmd_rd_stride_v_ovs_c       : 4;   // 20:23
} L9B0_MIFB_RD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x1b34 mifb_rd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 man_cmd_rd_stride_v_ovm_y   : 1;   //     0
	UINT32 man_cmd_rd_stride_v_ovm_c   : 1;   //     1
	UINT32 man_cmd_rd_stride_v_ovs_y   : 1;   //     2
	UINT32 man_cmd_rd_stride_v_ovs_c   : 1;   //     3
} L9B0_MIFB_RD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x1b38 mifb_wd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_stride_v_2_sm_y      : 4;   //  0: 3
	UINT32 cmd_wd_stride_v_8_sm_y      : 4;   //  4: 7
	UINT32 cmd_wd_stride_v_2_sm_c      : 4;   //  8:11
	UINT32 cmd_wd_stride_v_8_sm_c      : 4;   // 12:15
} L9B0_MIFB_WD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x1b3c mifb_wd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 man_cmd_wd_stride_v_sm_y    : 1;   //     0
	UINT32 man_cmd_wd_stride_v_sm_c    : 1;   //     1
} L9B0_MIFB_WD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x1b40 mifb_saddr_rd_ovm_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_ovm_y        : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_ovm_y        : 15;  // 16:30
} L9B0_MIFB_SADDR_RD_OVM_Y_T;

/*-----------------------------------------------------------------------------
	0x1b44 mifb_saddr_rd_ovm_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_ovm_c        : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_8_ovm_c        : 15;  // 16:30
} L9B0_MIFB_SADDR_RD_OVM_C_T;

/*-----------------------------------------------------------------------------
	0x1b48 mifb_saddr_rd_ovs_y_ovs_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_ovs_y          : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_ovs_c          : 15;  // 16:30
} L9B0_MIFB_SADDR_RD_OVS_Y_OVS_C_T;

/*-----------------------------------------------------------------------------
	0x1b4c mifb_saddr_wd_sm_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_sm_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_sm_y         : 15;  // 16:30
} L9B0_MIFB_SADDR_WD_SM_Y_T;

/*-----------------------------------------------------------------------------
	0x1b50 mifb_saddr_wd_sm_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_sm_c         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_8_sm_c         : 15;  // 16:30
} L9B0_MIFB_SADDR_WD_SM_C_T;

/*-----------------------------------------------------------------------------
	0x1b54 mifb_saddr_rd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_2_ovm_y_msb4b  : 4;   //  0: 3
	UINT32 req_rd_saddr_8_ovm_y_msb4b  : 4;   //  4: 7
	UINT32 req_rd_saddr_2_ovm_c_msb4b  : 4;   //  8:11
	UINT32 req_rd_saddr_8_ovm_c_msb4b  : 4;   // 12:15
	UINT32 req_rd_saddr_ovs_y_msb4b    : 4;   // 16:19
	UINT32 req_rd_saddr_ovs_c_msb4b    : 4;   // 20:23
} L9B0_MIFB_SADDR_RD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x1b58 mifb_saddr_wd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_2_sm_y_msb4b   : 4;   //  0: 3
	UINT32 req_wd_saddr_8_sm_y_msb4b   : 4;   //  4: 7
	UINT32 req_wd_saddr_2_sm_c_msb4b   : 4;   //  8:11
	UINT32 req_wd_saddr_8_sm_c_msb4b   : 4;   // 12:15
} L9B0_MIFB_SADDR_WD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x1b5c mifb_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fr_rd_valid_ovm_y           : 1;   //     0
	UINT32 fr_rd_valid_ovm_c           : 1;   //     1
	UINT32 fr_rd_valid_ovs_y           : 1;   //     2
	UINT32 fr_rd_valid_ovs_c           : 1;   //     3
	UINT32 fr_wd_q_full_sm_y           : 1;   //     4
	UINT32 fr_wd_q_full_sm_c           : 1;   //     5
} L9B0_MIFB_STATUS_T;

/*-----------------------------------------------------------------------------
	0x1b60 mifb_saddr_param_update0_m ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  //  1:10 reserved
	UINT32 register_update_address0_m  : 21;  // 11:31
} L9B0_MIFB_SADDR_PARAM_UPDATE0_M_T;

/*-----------------------------------------------------------------------------
	0x1b64 mifb_rd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_8_ovm_y    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_8_ovm_c    : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_rd_bank_addr_ovs_y      : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_rd_bank_addr_ovs_c      : 3;   // 12:14
} L9B0_MIFB_RD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x1b68 mifb_rd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifb_rd_bank_8_addr1_f      : 32;   // 31: 0
} L9B0_MIFB_RD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x1b6c mifb_rd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_2_ovs_y    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_2_ovs_c    : 3;   //  4: 6
} L9B0_MIFB_RD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x1b70 mifb_rd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifb_rd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFB_RD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x1b74 mifb_wd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_bank_addr_8_sm_y     : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_wd_bank_addr_8_sm_c     : 3;   //  4: 6
} L9B0_MIFB_WD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x1b78 mifb_wd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifb_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9B0_MIFB_WD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x1b7c mifb_wd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_bank_addr_8_sm_y     : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_wd_bank_addr_8_sm_c     : 3;   //  4: 6
} L9B0_MIFB_WD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x1b80 mifb_wd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifb_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFB_WD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x1b84 mifb_lsb_switch ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_lsb_ovm_y            : 2;   //  0: 1
	UINT32 req_rd_lsb_ovm_c            : 2;   //  2: 3
} L9B0_MIFB_LSB_SWITCH_T;

/*-----------------------------------------------------------------------------
	0x1b88 mifb_rd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifb_rd_req_pend0_f         : 32;   // 31: 0
} L9B0_MIFB_RD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x1b8c mifb_wd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pend_v_sm_y          : 8;   //  0: 7
	UINT32 req_wd_pend_v_sm_c          : 8;   //  8:15
} L9B0_MIFB_WD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x1b90 mifb_rd_cmd_pri00_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_s_v_ovm_y        : 4;   //  0: 3
	UINT32 cmd_rd_pri_s_v_ovm_c        : 4;   //  4: 7
	UINT32 cmd_rd_pri_s_v_ovs_y        : 4;   //  8:11
	UINT32 cmd_rd_pri_s_v_ovs_c        : 4;   // 12:15
} L9B0_MIFB_RD_CMD_PRI00_S_T;

/*-----------------------------------------------------------------------------
	0x1b94 mifb_wd_cmd_pri00_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_s_v_sm_y         : 4;   //  0: 3
	UINT32 cmd_wd_pri_s_v_sm_c         : 4;   //  4: 7
} L9B0_MIFB_WD_CMD_PRI00_S_T;

/*-----------------------------------------------------------------------------
	0x1b98 mifb_reset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reset_mif_r_ovm_y           : 1;   //     0
	UINT32 reset_mif_r_ovm_c           : 1;   //     1
	UINT32 reset_mif_r_ovs_y           : 1;   //     2
	UINT32 reset_mif_r_ovs_c           : 1;   //     3
	UINT32 reset_mif_w_scm_y           : 1;   //     4
	UINT32 reset_mif_w_scm_c           : 1;   //     5
	UINT32                             : 14;  //  6:19 reserved
	UINT32 reset_time_out_cnt          : 12;  // 20:31
} L9B0_MIFB_RESET_T;

/*-----------------------------------------------------------------------------
	0x2800 mifc_rd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
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
	UINT32                             : 1;   //    11 reserved
	UINT32 disable_rd_mifc             : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20 reserved
	UINT32 mrb_bank_mode               : 3;   // 21:23
} L9B0_MIFC_RD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2804 mifc_wd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 block_req_w_ss_y            : 1;   //     0
	UINT32 block_req_w_ss_c            : 1;   //     1
	UINT32 block_req_w_tnr_y           : 1;   //     2
	UINT32 block_req_w_tnr_c           : 1;   //     3
	UINT32 block_req_w_prew_y          : 1;   //     4
	UINT32 block_req_w_prew_c          : 1;   //     5
	UINT32                             : 6;   //  6:11 reserved
	UINT32 disable_wd_mifc             : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
	UINT32 set_ecanvas                 : 1;   //    20
	UINT32 mwb_bank_mode               : 3;   // 21:23
} L9B0_MIFC_WD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x2808 mifc_rd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_v_mvi_y          : 4;   //  0: 3
	UINT32 cmd_rd_pri_v_mvi_c          : 4;   //  4: 7
	UINT32 cmd_rd_pri_v_prew_y         : 4;   //  8:11
	UINT32 cmd_rd_pri_v_prew_c         : 4;   // 12:15
	UINT32 cmd_rd_pri_v_ipc0_y         : 4;   // 16:19
	UINT32 cmd_rd_pri_v_ipc_c          : 4;   // 20:23
	UINT32 cmd_rd_pri_v_ipc1_y         : 4;   // 24:27
	UINT32 cmd_rd_pri_v_tnr0_y         : 4;   // 28:31
} L9B0_MIFC_RD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x280c mifc_rd_cmd_pri1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_v_tnr_c          : 4;   //  0: 3
	UINT32 cmd_rd_pri_v_ss_y           : 4;   //  4: 7
	UINT32 cmd_rd_pri_v_ss_c           : 4;   //  8:11
} L9B0_MIFC_RD_CMD_PRI1_T;

/*-----------------------------------------------------------------------------
	0x2810 mifc_wd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_v_ss_y           : 4;   //  0: 3
	UINT32 cmd_wd_pri_v_ss_c           : 4;   //  4: 7
	UINT32 cmd_wd_pri_v_tnr_y          : 4;   //  8:11
	UINT32 cmd_wd_pri_v_tnr_c          : 4;   // 12:15
	UINT32 cmd_wd_pri_v_prew_y         : 4;   // 16:19
	UINT32 cmd_wd_pri_v_prew_c         : 4;   // 20:23
} L9B0_MIFC_WD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x2814 mifc_rd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_mvi_y          : 4;   //  0: 3
	UINT32 req_rd_pri_v_mvi_c          : 4;   //  4: 7
	UINT32 req_rd_pri_v_prew_y         : 4;   //  8:11
	UINT32 req_rd_pri_v_prew_c         : 4;   // 12:15
	UINT32 req_rd_pri_v_ipc0_y         : 4;   // 16:19
	UINT32 req_rd_pri_v_ipc1_y         : 4;   // 20:23
	UINT32 req_rd_pri_v_ipc_c          : 4;   // 24:27
	UINT32 req_rd_pri_v_tnr0_y         : 4;   // 28:31
} L9B0_MIFC_RD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x2818 mifc_rd_req_pri1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_tnr_c          : 4;   //  0: 3
	UINT32 req_rd_pri_v_ss_y           : 4;   //  4: 7
	UINT32 req_rd_pri_v_ss_c           : 4;   //  8:11
} L9B0_MIFC_RD_REQ_PRI1_T;

/*-----------------------------------------------------------------------------
	0x281c mifc_wd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pri_v_ss_y           : 4;   //  0: 3
	UINT32 req_wd_pri_v_ss_c           : 4;   //  4: 7
	UINT32 req_wd_pri_v_tnr_y          : 4;   //  8:11
	UINT32 req_wd_pri_v_tnr_c          : 4;   // 12:15
	UINT32 req_wd_pri_v_prew_y         : 4;   // 16:19
	UINT32 req_wd_pri_v_prew_c         : 4;   // 20:23
} L9B0_MIFC_WD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x2820 mifc_rd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_stv_v_mvi_y          : 4;   //  0: 3
	UINT32 req_rd_stv_v_mvi_c          : 4;   //  4: 7
	UINT32 req_rd_stv_v_prew_y         : 4;   //  8:11
	UINT32 req_rd_stv_v_prew_c         : 4;   // 12:15
	UINT32 req_rd_stv_v_ipc0_y         : 4;   // 16:19
	UINT32 req_rd_stv_v_ipc_c          : 4;   // 20:23
	UINT32 req_rd_stv_v_ipc1_y         : 4;   // 24:27
	UINT32 req_rd_stv_v_tnr0_y         : 4;   // 28:31
} L9B0_MIFC_RD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x2824 mifc_rd_req_stv1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_tnr_c          : 4;   //  0: 3
	UINT32 req_rd_pri_v_ss_y           : 4;   //  4: 7
	UINT32 req_rd_pri_v_ss_c           : 4;   //  8:11
} L9B0_MIFC_RD_REQ_STV1_T;

/*-----------------------------------------------------------------------------
	0x2828 mifc_wd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_stv_v_ss_y           : 4;   //  0: 3
	UINT32 req_wd_stv_v_ss_c           : 4;   //  4: 7
	UINT32 req_wd_stv_v_tnr_y          : 4;   //  8:11
	UINT32 req_wd_stv_v_tnr_c          : 4;   // 12:15
	UINT32 req_wd_stv_v_prew_y         : 4;   // 16:19
	UINT32 req_wd_stv_v_prew_c         : 4;   // 20:23
} L9B0_MIFC_WD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x282c mifc_rd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pend_v_mvi_y         : 4;   //  0: 3
	UINT32 cmd_rd_pend_v_mvi_c         : 4;   //  4: 7
	UINT32 cmd_rd_pend_v_prew_y        : 4;   //  8:11
	UINT32 cmd_rd_pend_v_prew_c        : 4;   // 12:15
	UINT32 cmd_rd_pend_v_ipc0_y        : 4;   // 16:19
	UINT32 cmd_rd_pend_v_ipc_c         : 4;   // 20:23
	UINT32 cmd_rd_pend_v_ipc1_y        : 4;   // 24:27
	UINT32 cmd_rd_pend_v_tnr0_y        : 4;   // 28:31
} L9B0_MIFC_RD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x2830 mifc_rd_cmd_pend1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pend_v_tnr_c         : 4;   //  0: 3
	UINT32 cmd_rd_pend_v_ss_y          : 4;   //  4: 7
	UINT32 cmd_rd_pend_v_ss_c          : 4;   //  8:11
} L9B0_MIFC_RD_CMD_PEND1_T;

/*-----------------------------------------------------------------------------
	0x2834 mifc_wd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pend_v_ss_y          : 4;   //  0: 3
	UINT32 cmd_wd_pend_v_ss_c          : 4;   //  4: 7
	UINT32 cmd_wd_pend_v_tnr_y         : 4;   //  8:11
	UINT32 cmd_wd_pend_v_tnr_c         : 4;   // 12:15
	UINT32 cmd_wd_pend_v_prew_y        : 4;   // 16:19
	UINT32 cmd_wd_pend_v_prew_c        : 4;   // 20:23
} L9B0_MIFC_WD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x2838 mifc_rd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_mvi_y       : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_mvi_c       : 4;   //  4: 7
	UINT32 cmd_rd_stride_v_prew_y      : 4;   //  8:11
	UINT32 cmd_rd_stride_v_prew_c      : 4;   // 12:15
	UINT32 cmd_rd_stride_v_ipc0_y      : 4;   // 16:19
	UINT32 cmd_rd_stride_v_ipc_c       : 4;   // 20:23
	UINT32 cmd_rd_stride_v_ipc1_y      : 4;   // 24:27
	UINT32 cmd_rd_stride_v_tnr0_y      : 4;   // 28:31
} L9B0_MIFC_RD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x283c mifc_rd_cmd_stride1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_tnr_c       : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_ss_y        : 4;   //  4: 7
	UINT32 cmd_rd_stride_v_ss_c        : 4;   //  8:11
} L9B0_MIFC_RD_CMD_STRIDE1_T;

/*-----------------------------------------------------------------------------
	0x2840 mifc_rd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
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
} L9B0_MIFC_RD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x2844 mifc_wd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_stride_v_ss_y        : 4;   //  0: 3
	UINT32 cmd_wd_stride_v_ss_c        : 4;   //  4: 7
	UINT32 cmd_wd_stride_v_tnr_y       : 4;   //  8:11
	UINT32 cmd_wd_stride_v_tnr_c       : 4;   // 12:15
	UINT32 cmd_wd_stride_v_prew_y      : 4;   // 16:19
	UINT32 cmd_wd_stride_v_prew_c      : 4;   // 20:23
} L9B0_MIFC_WD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x2848 mifc_wd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 man_cmd_wd_stride_v_ss_y    : 1;   //     0
	UINT32 man_cmd_wd_stride_v_ss_c    : 1;   //     1
	UINT32 man_cmd_wd_stride_v_tnr_y   : 1;   //     2
	UINT32 man_cmd_wd_stride_v_tnr_c   : 1;   //     3
	UINT32 man_cmd_wd_stride_v_prew_y  : 1;   //     4
	UINT32 man_cmd_wd_stride_v_prew_c  : 1;   //     5
} L9B0_MIFC_WD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x284c mifc_saddr_rd_mvi_y_mvi_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_mvi_y          : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_mvi_c          : 15;  // 16:30
} L9B0_MIFC_SADDR_RD_MVI_Y_MVI_C_T;

/*-----------------------------------------------------------------------------
	0x2850 mifc_saddr_rd_prew_y_prew_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_prew_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_prew_c         : 15;  // 16:30
} L9B0_MIFC_SADDR_RD_PREW_Y_PREW_C_T;

/*-----------------------------------------------------------------------------
	0x2854 mifc_saddr_rd_ipc0_y_ipc_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_ipc0_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_ipc_c          : 15;  // 16:30
} L9B0_MIFC_SADDR_RD_IPC0_Y_IPC_C_T;

/*-----------------------------------------------------------------------------
	0x2858 mifc_saddr_rd_ipc1_y_tnr0_y ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_ipc1_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_tnr0_y         : 15;  // 16:30
} L9B0_MIFC_SADDR_RD_IPC1_Y_TNR0_Y_T;

/*-----------------------------------------------------------------------------
	0x285c mifc_saddr_rd_ss_y_ss_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_ss_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_ss_c           : 15;  // 16:30
} L9B0_MIFC_SADDR_RD_SS_Y_SS_C_T;

/*-----------------------------------------------------------------------------
	0x2860 mifc_saddr_rd_tnr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_tnr_c          : 15;  //  0:14
} L9B0_MIFC_SADDR_RD_TNR_C_T;

/*-----------------------------------------------------------------------------
	0x2864 mifc_saddr_wd_ss_y_ss_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_ss_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_ss_c           : 15;  // 16:30
} L9B0_MIFC_SADDR_WD_SS_Y_SS_C_T;

/*-----------------------------------------------------------------------------
	0x2868 mifc_saddr_wd_tnr_y_tnr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_tnr_y          : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_tnr_c          : 15;  // 16:30
} L9B0_MIFC_SADDR_WD_TNR_Y_TNR_C_T;

/*-----------------------------------------------------------------------------
	0x286c mifc_saddr_wd_prew_y_prew_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_prew_y         : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_prew_c         : 15;  // 16:30
} L9B0_MIFC_SADDR_WD_PREW_Y_PREW_C_T;

/*-----------------------------------------------------------------------------
	0x2870 mifc_saddr_rd_dl_y_dl_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_dl_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_dl_c           : 15;  // 16:30
} L9B0_MIFC_SADDR_RD_DL_Y_DL_C_T;

/*-----------------------------------------------------------------------------
	0x2874 mifc_saddr_rd_dr_y_dr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_dr_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_dr_c           : 15;  // 16:30
} L9B0_MIFC_SADDR_RD_DR_Y_DR_C_T;

/*-----------------------------------------------------------------------------
	0x2878 mifc_saddr_wd_dl_y_dl_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_dl_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_dl_c           : 15;  // 16:30
} L9B0_MIFC_SADDR_WD_DL_Y_DL_C_T;

/*-----------------------------------------------------------------------------
	0x287c mifc_saddr_wd_dr_y_dr_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_dr_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_dr_c           : 15;  // 16:30
} L9B0_MIFC_SADDR_WD_DR_Y_DR_C_T;

/*-----------------------------------------------------------------------------
	0x2880 mifc_saddr_rd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_mvi_y_msb4b    : 4;   //  0: 3
	UINT32 req_rd_saddr_mvi_c_msb4b    : 4;   //  4: 7
	UINT32 req_rd_saddr_prew_y_msb4b   : 4;   //  8:11
	UINT32 req_rd_saddr_prew_c_msb4b   : 4;   // 12:15
	UINT32 req_rd_saddr_ipc0_y_msb4b   : 4;   // 16:19
	UINT32 req_rd_saddr_ipc_c_msb4b    : 4;   // 20:23
	UINT32 req_rd_saddr_ipc1_y_msb4b   : 4;   // 24:27
	UINT32 req_rd_saddr_tnr0_y_msb4b   : 4;   // 28:31
} L9B0_MIFC_SADDR_RD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x2884 mifc_saddr_rd_ext1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_tnr_c_msb4b    : 4;   //  0: 3
	UINT32 req_rd_saddr_ss_y_msb4b     : 4;   //  4: 7
	UINT32 req_rd_saddr_ss_c_msb4b     : 4;   //  8:11
} L9B0_MIFC_SADDR_RD_EXT1_T;

/*-----------------------------------------------------------------------------
	0x2888 mifc_saddr_wd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_ss_y_msb4b     : 4;   //  0: 3
	UINT32 req_wd_saddr_ss_c_msb4b     : 4;   //  4: 7
	UINT32 req_wd_saddr_tnr_y_msb4b    : 4;   //  8:11
	UINT32 req_wd_saddr_tnr_c_msb4b    : 4;   // 12:15
	UINT32 req_wd_saddr_prew_y_msb4b   : 4;   // 16:19
	UINT32 req_wd_saddr_prew_c_msb4b   : 4;   // 20:23
} L9B0_MIFC_SADDR_WD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x288c mifc_rd_dr_dl_ext ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_dl_y_msb4b     : 4;   //  0: 3
	UINT32 req_rd_saddr_dl_c_msb4b     : 4;   //  4: 7
	UINT32 req_rd_saddr_dr_y_msb4b     : 4;   //  8:11
	UINT32 req_rd_saddr_dr_c_msb4b     : 4;   // 12:15
} L9B0_MIFC_RD_DR_DL_EXT_T;

/*-----------------------------------------------------------------------------
	0x2890 mifc_wd_dr_dl_ext ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_dl_y_msb4b     : 4;   //  0: 3
	UINT32 req_wd_saddr_dl_c_msb4b     : 4;   //  4: 7
	UINT32 req_wd_saddr_dr_y_msb4b     : 4;   //  8:11
	UINT32 req_wd_saddr_dr_c_msb4b     : 4;   // 12:15
} L9B0_MIFC_WD_DR_DL_EXT_T;

/*-----------------------------------------------------------------------------
	0x2894 mifc_status ''
------------------------------------------------------------------------------*/
typedef struct {
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
} L9B0_MIFC_STATUS_T;

/*-----------------------------------------------------------------------------
	0x2898 mifc_saddr_param_update0_m ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  //  1:10 reserved
	UINT32 register_update_address0_m  : 21;  // 11:31
} L9B0_MIFC_SADDR_PARAM_UPDATE0_M_T;

/*-----------------------------------------------------------------------------
	0x289c mifc_rd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_8_mvi_y    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_8_mvi_c    : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_rd_bank_addr_8_prew_y   : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_rd_bank_addr_8_prew_c   : 3;   // 12:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_bank_addr_8_ipc0_y   : 3;   // 16:18
	UINT32                             : 1;   //    19 reserved
	UINT32 req_rd_bank_addr_8_ipc_c    : 3;   // 20:22
	UINT32                             : 1;   //    23 reserved
	UINT32 req_rd_bank_addr_8_ipc1_y   : 3;   // 24:26
	UINT32                             : 1;   //    27 reserved
	UINT32 req_rd_bank_addr_8_tnr0_y   : 3;   // 28:30
} L9B0_MIFC_RD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x28a0 mifc_rd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_8_tnr_c    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_8_ss_y     : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_rd_bank_addr_8_ss_c     : 3;   //  8:10
} L9B0_MIFC_RD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x28a4 mifc_rd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifc_rd_bank_2_addr0_f      : 32;   // 31: 0
} L9B0_MIFC_RD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x28a8 mifc_rd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifc_rd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFC_RD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x28ac mifc_wd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_bank_addr_8_ss_y     : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_wd_bank_addr_8_ss_c     : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_wd_bank_addr_8_tnr_y    : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_wd_bank_addr_8_tnr_c    : 3;   // 12:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_bank_addr_8_prew_y   : 3;   // 16:18
	UINT32                             : 1;   //    19 reserved
	UINT32 req_wd_bank_addr_8_prew_c   : 3;   // 20:22
} L9B0_MIFC_WD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x28b0 mifc_wd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifc_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9B0_MIFC_WD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x28b4 mifc_wd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifc_wd_bank_2_addr0_f      : 32;   // 31: 0
} L9B0_MIFC_WD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x28b8 mifc_wd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifc_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFC_WD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x28bc mifc_rd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_mvi_y         : 8;   //  0: 7
	UINT32 req_rd_pend_v_mvi_c         : 8;   //  8:15
	UINT32 req_rd_pend_v_prew_y        : 8;   // 16:23
	UINT32 req_rd_pend_v_prew_c        : 8;   // 24:31
} L9B0_MIFC_RD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x28c0 mifc_rd_req_pend1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_ipc0_y        : 8;   //  0: 7
	UINT32 req_rd_pend_v_ipc_c         : 8;   //  8:15
	UINT32 req_rd_pend_v_ipc1_y        : 8;   // 16:23
	UINT32 req_rd_pend_v_tnr0_y        : 8;   // 24:31
} L9B0_MIFC_RD_REQ_PEND1_T;

/*-----------------------------------------------------------------------------
	0x28c4 mifc_rd_req_pend2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_tnr_c         : 8;   //  0: 7
	UINT32 req_rd_pend_v_ss_y          : 8;   //  8:15
	UINT32 req_rd_pend_v_ss_c          : 8;   // 16:23
} L9B0_MIFC_RD_REQ_PEND2_T;

/*-----------------------------------------------------------------------------
	0x28c8 mifc_wd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pend_v_ss_y          : 8;   //  0: 7
	UINT32 req_wd_pend_v_ss_c          : 8;   //  8:15
	UINT32 req_wd_pend_v_tnr_y         : 8;   // 16:23
	UINT32 req_wd_pend_v_tnr_c         : 8;   // 24:31
} L9B0_MIFC_WD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x28cc mifc_wd_req_pend1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pend_v_prew_y        : 8;   //  0: 7
	UINT32 req_wd_pend_v_prew_c        : 8;   //  8:15
} L9B0_MIFC_WD_REQ_PEND1_T;

/*-----------------------------------------------------------------------------
	0x28d0 mifc_rd_cmd_pri0_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_s_v_mvi_y        : 4;   //  0: 3
	UINT32 cmd_rd_pri_s_v_mvi_c        : 4;   //  4: 7
	UINT32 cmd_rd_pri_s_v_prew_y       : 4;   //  8:11
	UINT32 cmd_rd_pri_s_v_prew_c       : 4;   // 12:15
	UINT32 cmd_rd_pri_s_v_ipc0_y       : 4;   // 16:19
	UINT32 cmd_rd_pri_s_v_ipc_c        : 4;   // 20:23
	UINT32 cmd_rd_pri_s_v_ipc1_y       : 4;   // 24:27
	UINT32 cmd_rd_pri_s_v_tnr0_y       : 4;   // 28:31
} L9B0_MIFC_RD_CMD_PRI0_S_T;

/*-----------------------------------------------------------------------------
	0x28d4 mifc_rd_cmd_pri1_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_s_v_tnr_c        : 4;   //  0: 3
	UINT32 cmd_rd_pri_s_v_ss_y         : 4;   //  4: 7
	UINT32 cmd_rd_pri_s_v_ss_c         : 4;   //  8:11
} L9B0_MIFC_RD_CMD_PRI1_S_T;

/*-----------------------------------------------------------------------------
	0x28d8 mifc_wd_cmd_pri0_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_s_v_ss_y         : 4;   //  0: 3
	UINT32 cmd_wd_pri_s_v_ss_c         : 4;   //  4: 7
	UINT32 cmd_wd_pri_s_v_tnr_y        : 4;   //  8:11
	UINT32 cmd_wd_pri_s_v_tnr_c        : 4;   // 12:15
	UINT32 cmd_wd_pri_s_v_prew_y       : 4;   // 16:19
	UINT32 cmd_wd_pri_s_v_prew_c       : 4;   // 20:23
} L9B0_MIFC_WD_CMD_PRI0_S_T;

/*-----------------------------------------------------------------------------
	0x28dc mifc_reset ''
------------------------------------------------------------------------------*/
typedef struct {
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
	UINT32                             : 3;   // 17:19 reserved
	UINT32 reset_time_out_cnt          : 12;  // 20:31
} L9B0_MIFC_RESET_T;

/*-----------------------------------------------------------------------------
	0x3900 mifd_rd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 block_req_r_ov_y            : 1;   //     0
	UINT32 block_req_r_ov_c            : 1;   //     1
	UINT32                             : 10;  //  2:11 reserved
	UINT32 disable_rd_mif              : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
} L9B0_MIFD_RD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x3904 mifd_wd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 block_req_w_sm_y            : 1;   //     0
	UINT32 block_req_w_sm_c            : 1;   //     1
	UINT32                             : 10;  //  2:11 reserved
	UINT32 disable_wd_mif              : 1;   //    12
	UINT32 load_wd_req_stv_v           : 1;   //    13
	UINT32 load_wd_req_pri_v           : 1;   //    14
	UINT32 load_wd_cmd_saddr_v         : 1;   //    15
	UINT32 load_wd_cmd_pend_v          : 1;   //    16
	UINT32 load_wd_cmd_pri_v           : 1;   //    17
	UINT32 load_wd_cmd_stride_v        : 1;   //    18
	UINT32 enable_wd_stv_cnt           : 1;   //    19
} L9B0_MIFD_WD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x3908 mifd_rd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_v_ov_y           : 4;   //  0: 3
	UINT32 cmd_rd_pri_v_ov_c           : 4;   //  4: 7
} L9B0_MIFD_RD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x390c mifd_wd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_v_sm_y           : 4;   //  0: 3
	UINT32 cmd_wd_pri_v_sm_c           : 4;   //  4: 7
} L9B0_MIFD_WD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x3910 mifd_rd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_ov_y           : 4;   //  0: 3
	UINT32 req_rd_pri_v_ov_c           : 4;   //  4: 7
} L9B0_MIFD_RD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x3914 mifd_wd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pri_v_scm_y          : 4;   //  0: 3
	UINT32 req_wd_pri_v_scm_c          : 4;   //  4: 7
} L9B0_MIFD_WD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x3918 mifd_rd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_stv_v_ov_y           : 4;   //  0: 3
	UINT32 req_rd_stv_v_ov_c           : 4;   //  4: 7
} L9B0_MIFD_RD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x391c mifd_wd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_stv_v_sm_y           : 4;   //  0: 3
	UINT32 req_wd_stv_v_sm_c           : 4;   //  4: 7
} L9B0_MIFD_WD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x3920 mifd_rd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pend_v_ov_y          : 4;   //  0: 3
	UINT32 cmd_rd_pend_v_ov_c          : 4;   //  4: 7
} L9B0_MIFD_RD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x3924 mifd_wd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pend_v_sm_y          : 4;   //  0: 3
	UINT32 cmd_wd_pend_v_sm_c          : 4;   //  4: 7
} L9B0_MIFD_WD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x3928 mifd_rd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_ov_y        : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_ov_c        : 4;   //  4: 7
} L9B0_MIFD_RD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x392c mifd_rd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 man_cmd_rd_stride_v_ov_y    : 1;   //     0
	UINT32 man_cmd_rd_stride_v_ov_c    : 1;   //     1
} L9B0_MIFD_RD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x3930 mifd_wd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_stride_v_sm_y        : 4;   //  0: 3
	UINT32 cmd_wd_stride_v_sm_c        : 4;   //  4: 7
} L9B0_MIFD_WD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x3934 mifd_wd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 man_cmd_wd_stride_v_sm_y    : 1;   //     0
	UINT32 man_cmd_wd_stride_v_sm_c    : 1;   //     1
} L9B0_MIFD_WD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x3938 mifd_saddr_rd_ov_y_ov_c ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_ov_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_ov_c           : 15;  // 16:30
} L9B0_MIFD_SADDR_RD_OV_Y_OV_C_T;

/*-----------------------------------------------------------------------------
	0x393c mifd_saddr_wd_sm_yc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_sm_y           : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_wd_saddr_sm_c           : 15;  // 16:30
} L9B0_MIFD_SADDR_WD_SM_YC_T;

/*-----------------------------------------------------------------------------
	0x3940 mifd_saddr_rd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_ov_y_msb4b     : 4;   //  0: 3
	UINT32 req_rd_saddr_ov_c_msb4b     : 4;   //  4: 7
} L9B0_MIFD_SADDR_RD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x3944 mifd_saddr_wd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_saddr_sm_y_msb4b     : 4;   //  0: 3
	UINT32 req_wd_saddr_sm_c_msb4b     : 4;   //  4: 7
} L9B0_MIFD_SADDR_WD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x3948 mifd_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fr_rd_valid_ov_y            : 1;   //     0
	UINT32 fr_rd_valid_ov_c            : 1;   //     1
	UINT32 fr_wd_q_full_sm_y           : 1;   //     2
	UINT32 fr_wd_q_full_sm_c           : 1;   //     3
} L9B0_MIFD_STATUS_T;

/*-----------------------------------------------------------------------------
	0x394c mifd_saddr_param_update0_m ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  //  1:10 reserved
	UINT32 register_update_address0_m  : 21;  // 11:31
} L9B0_MIFD_SADDR_PARAM_UPDATE0_M_T;

/*-----------------------------------------------------------------------------
	0x3950 mifd_rd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_8_ov_y     : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_8_ov_c     : 3;   //  4: 6
} L9B0_MIFD_RD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x3954 mifd_rd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifd_rd_bank_8_addr1_f      : 32;   // 31: 0
} L9B0_MIFD_RD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x3958 mifd_rd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifd_rd_bank_2_addr0_f      : 32;   // 31: 0
} L9B0_MIFD_RD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x395c mifd_rd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifd_rd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFD_RD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x3960 mifd_wd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_bank_addr_8_sm_y     : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_wd_bank_addr_8_sm_c     : 3;   //  4: 6
} L9B0_MIFD_WD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x3964 mifd_wd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifd_wd_bank_8_addr1_f      : 32;   // 31: 0
} L9B0_MIFD_WD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x3968 mifd_wd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifd_wd_bank_2_addr0_f      : 32;   // 31: 0
} L9B0_MIFD_WD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x396c mifd_wd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifd_wd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFD_WD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x3970 mifd_rd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_ov_y          : 8;   //  0: 7
	UINT32 req_rd_pend_v_ov_c          : 8;   //  8:15
} L9B0_MIFD_RD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x3974 mifd_wd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_wd_pend_v_sm_y          : 8;   //  0: 7
	UINT32 req_wd_pend_v_sm_c          : 8;   //  8:15
} L9B0_MIFD_WD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x3978 mifd_rd_cmd_pri0_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_s_v_ov_y         : 4;   //  0: 3
	UINT32 cmd_rd_pri_s_v_ov_c         : 4;   //  4: 7
} L9B0_MIFD_RD_CMD_PRI0_S_T;

/*-----------------------------------------------------------------------------
	0x397c mifd_wd_cmd_pri0_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_wd_pri_s_v_sm_y         : 4;   //  0: 3
	UINT32 cmd_wd_pri_s_v_sm_c         : 4;   //  4: 7
} L9B0_MIFD_WD_CMD_PRI0_S_T;

/*-----------------------------------------------------------------------------
	0x3980 mifd_reset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reset_mif_r_ov_y            : 1;   //     0
	UINT32 reset_mif_r_ov_c            : 1;   //     1
	UINT32 reset_mif_w_sm_y            : 1;   //     2
	UINT32 reset_mif_w_sm_c            : 1;   //     3
	UINT32                             : 16;  //  4:19 reserved
	UINT32 reset_time_out_cnt          : 12;  // 20:31
} L9B0_MIFD_RESET_T;

/*-----------------------------------------------------------------------------
	0x5f00 miff_rd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 block_req_r_osd_0           : 1;   //     0
	UINT32 block_req_r_osd_1           : 1;   //     1
	UINT32 block_req_r_osd_2           : 1;   //     2
	UINT32 block_req_r_osd_3           : 1;   //     3
	UINT32 block_req_r_cve_y           : 1;   //     4
	UINT32 block_req_r_cve_c           : 1;   //     5
	UINT32                             : 6;   //  6:11 reserved
	UINT32 disable_rd_mif              : 1;   //    12
	UINT32 load_rd_req_stv_v           : 1;   //    13
	UINT32 load_rd_req_pri_v           : 1;   //    14
	UINT32 load_rd_cmd_saddr_v         : 1;   //    15
	UINT32 load_rd_cmd_pend_v          : 1;   //    16
	UINT32 load_rd_cmd_pri_v           : 1;   //    17
	UINT32 load_rd_cmd_stride_v        : 1;   //    18
	UINT32 enable_rd_stv_cnt           : 1;   //    19
	UINT32                             : 1;   //    20 reserved
	UINT32 mrb_bank_mode               : 3;   // 21:23
} L9B0_MIFF_RD_CTRL_T;

/*-----------------------------------------------------------------------------
	0x5f04 miff_rd_cmd_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_v_osd_0          : 4;   //  0: 3
	UINT32 cmd_rd_pri_v_osd_1          : 4;   //  4: 7
	UINT32 cmd_rd_pri_v_osd_2          : 4;   //  8:11
	UINT32 cmd_rd_pri_v_osd_3          : 4;   // 12:15
	UINT32 cmd_rd_pri_v_cve_y          : 4;   // 16:19
	UINT32 cmd_rd_pri_v_cve_c          : 4;   // 20:23
} L9B0_MIFF_RD_CMD_PRI0_T;

/*-----------------------------------------------------------------------------
	0x5f08 miff_rd_req_pri0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pri_v_osd_0          : 4;   //  0: 3
	UINT32 req_rd_pri_v_osd_1          : 4;   //  4: 7
	UINT32 req_rd_pri_v_osd_2          : 4;   //  8:11
	UINT32 req_rd_pri_v_osd_3          : 4;   // 12:15
	UINT32 req_rd_pri_v_cve_y          : 4;   // 16:19
	UINT32 req_rd_pri_v_cve_c          : 4;   // 20:23
} L9B0_MIFF_RD_REQ_PRI0_T;

/*-----------------------------------------------------------------------------
	0x5f0c miff_rd_req_stv0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_stv_v_osd_0          : 4;   //  0: 3
	UINT32 req_rd_stv_v_osd_1          : 4;   //  4: 7
	UINT32 req_rd_stv_v_osd_2          : 4;   //  8:11
	UINT32 req_rd_stv_v_osd_3          : 4;   // 12:15
	UINT32 req_rd_stv_v_cve_y          : 4;   // 16:19
	UINT32 req_rd_stv_v_cve_c          : 4;   // 20:23
} L9B0_MIFF_RD_REQ_STV0_T;

/*-----------------------------------------------------------------------------
	0x5f10 miff_rd_cmd_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pend_v_osd_0         : 4;   //  0: 3
	UINT32 cmd_rd_pend_v_osd_1         : 4;   //  4: 7
	UINT32 cmd_rd_pend_v_osd_2         : 4;   //  8:11
	UINT32 cmd_rd_pend_v_osd_3         : 4;   // 12:15
	UINT32 cmd_rd_pend_v_cve_y         : 4;   // 16:19
	UINT32 cmd_rd_pend_v_cve_c         : 4;   // 20:23
} L9B0_MIFF_RD_CMD_PEND0_T;

/*-----------------------------------------------------------------------------
	0x5f14 miff_rd_cmd_stride0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_stride_v_osd_0       : 4;   //  0: 3
	UINT32 cmd_rd_stride_v_osd_1       : 4;   //  4: 7
	UINT32 cmd_rd_stride_v_osd_2       : 4;   //  8:11
	UINT32 cmd_rd_stride_v_osd_3       : 4;   // 12:15
	UINT32 cmd_rd_stride_v_cve_y       : 4;   // 16:19
	UINT32 cmd_rd_stride_v_cve_c       : 4;   // 20:23
} L9B0_MIFF_RD_CMD_STRIDE0_T;

/*-----------------------------------------------------------------------------
	0x5f18 miff_rd_cmd_stride_set ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 man_cmd_rd_stride_v_osd_0   : 1;   //     0
	UINT32 man_cmd_rd_stride_v_osd_1   : 1;   //     1
	UINT32 man_cmd_rd_stride_v_osd_2   : 1;   //     2
	UINT32 man_cmd_rd_stride_v_osd_3   : 1;   //     3
	UINT32 man_cmd_rd_stride_v_cve_y   : 1;   //     4
	UINT32 man_cmd_rd_stride_v_cve_c   : 1;   //     5
} L9B0_MIFF_RD_CMD_STRIDE_SET_T;

/*-----------------------------------------------------------------------------
	0x5f1c miff_saddr_rd_osd_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_osd_0          : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_osd_1          : 15;  // 16:30
} L9B0_MIFF_SADDR_RD_OSD_01_T;

/*-----------------------------------------------------------------------------
	0x5f20 miff_saddr_rd_osd_23 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_osd_2          : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_osd_3          : 15;  // 16:30
} L9B0_MIFF_SADDR_RD_OSD_23_T;

/*-----------------------------------------------------------------------------
	0x5f24 miff_saddr_rd_cve_yc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_cve_y          : 15;  //  0:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_saddr_cve_c          : 15;  // 16:30
} L9B0_MIFF_SADDR_RD_CVE_YC_T;

/*-----------------------------------------------------------------------------
	0x5f28 miff_saddr_rd_ext0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_saddr_osd_0_msb4b    : 4;   //  0: 3
	UINT32 req_rd_saddr_osd_1_msb4b    : 4;   //  4: 7
	UINT32 req_rd_saddr_osd_2_msb4b    : 4;   //  8:11
	UINT32 req_rd_saddr_osd_3_msb4b    : 4;   // 12:15
	UINT32 req_rd_saddr_cve_y_msb4b    : 4;   // 16:19
	UINT32 req_rd_saddr_cve_c_msb4b    : 4;   // 20:23
} L9B0_MIFF_SADDR_RD_EXT0_T;

/*-----------------------------------------------------------------------------
	0x5f2c miff_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 fr_rd_valid_osd_0           : 1;   //     0
	UINT32 fr_rd_valid_osd_1           : 1;   //     1
	UINT32 fr_rd_valid_osd_2           : 1;   //     2
	UINT32 fr_rd_valid_osd_3           : 1;   //     3
	UINT32 fr_rd_valid_cve_y           : 1;   //     4
	UINT32 fr_rd_valid_cve_c           : 1;   //     5
} L9B0_MIFF_STATUS_T;

/*-----------------------------------------------------------------------------
	0x5f30 miff_rd_bank_8_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_bank_addr_8_osd_0    : 3;   //  0: 2
	UINT32                             : 1;   //     3 reserved
	UINT32 req_rd_bank_addr_8_osd_1    : 3;   //  4: 6
	UINT32                             : 1;   //     7 reserved
	UINT32 req_rd_bank_addr_8_osd_2    : 3;   //  8:10
	UINT32                             : 1;   //    11 reserved
	UINT32 req_rd_bank_addr_8_osd_3    : 3;   // 12:14
	UINT32                             : 1;   //    15 reserved
	UINT32 req_rd_bank_addr_8_cve_y    : 3;   // 16:18
	UINT32                             : 1;   //    19 reserved
	UINT32 req_rd_bank_addr_8_cve_c    : 3;   // 20:22
} L9B0_MIFF_RD_BANK_8_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x5f34 miff_rd_bank_8_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 miff_rd_bank_8_addr1_f      : 32;   // 31: 0
} L9B0_MIFF_RD_BANK_8_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x5f38 miff_rd_bank_2_addr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 miff_rd_bank_2_addr0_f      : 32;   // 31: 0
} L9B0_MIFF_RD_BANK_2_ADDR0_T;

/*-----------------------------------------------------------------------------
	0x5f3c miff_rd_bank_2_addr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 miff_rd_bank_2_addr1_f      : 32;   // 31: 0
} L9B0_MIFF_RD_BANK_2_ADDR1_T;

/*-----------------------------------------------------------------------------
	0x5f40 miff_rd_req_pend0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 req_rd_pend_v_osd_0         : 8;   //  0: 7
	UINT32 req_rd_pend_v_osd_1         : 8;   //  8:15
	UINT32 req_rd_pend_v_osd_2         : 8;   // 16:23
	UINT32 req_rd_pend_v_osd_3         : 8;   // 24:31
} L9B0_MIFF_RD_REQ_PEND0_T;

/*-----------------------------------------------------------------------------
	0x5f44 miff_rd_cmd_pri0_s ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 cmd_rd_pri_s_v_osd_0        : 4;   //  0: 3
	UINT32 cmd_rd_pri_s_v_osd_1        : 4;   //  4: 7
	UINT32 cmd_rd_pri_s_v_osd_2        : 4;   //  8:11
	UINT32 cmd_rd_pri_s_v_osd_3        : 4;   // 12:15
	UINT32 cmd_rd_pri_s_v_cve_y        : 4;   // 16:19
	UINT32 cmd_rd_pri_s_v_cve_c        : 4;   // 20:23
} L9B0_MIFF_RD_CMD_PRI0_S_T;

/*-----------------------------------------------------------------------------
	0x5f48 miff_reset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 reset_mif_r_osd_0           : 1;   //     0
	UINT32 reset_mif_r_osd_1           : 1;   //     1
	UINT32 reset_mif_r_osd_2           : 1;   //     2
	UINT32 reset_mif_r_osd_3           : 1;   //     3
	UINT32 reset_mif_r_cve_y           : 1;   //     4
	UINT32 reset_mif_r_cve_c           : 1;   //     5
	UINT32                             : 14;  //  6:19 reserved
	UINT32 reset_time_out_cnt          : 12;  // 20:31
} L9B0_MIFF_RESET_T;

/*-----------------------------------------------------------------------------
	0x5f4c miff_saddr_param_update0_m ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32 load                        : 1;   //     0
	UINT32                             : 10;  //  1:10 reserved
	UINT32 register_update_address0_m  : 21;  // 11:31
} L9B0_MIFF_SADDR_PARAM_UPDATE0_M_T;

typedef struct {
	L9B0_MIFA_RD_CTRL_T                 mifa_rd_ctrl;                        // 0x0800
	L9B0_MIFA_WD_CTRL_T                 mifa_wd_ctrl;                        // 0x0804
	L9B0_MIF_RD_SET_10B_T               mif_rd_set_10b;                      // 0x0808
	L9B0_MIF_WD_SET_10B_T               mif_wd_set_10b;                      // 0x080c
	L9B0_MIFA_RD_CMD_PRI0_T             mifa_rd_cmd_pri0;                    // 0x0810
	L9B0_MIFA_RD_CMD_PRI1_T             mifa_rd_cmd_pri1;                    // 0x0814
	L9B0_MIFA_WD_CMD_PRI0_T             mifa_wd_cmd_pri0;                    // 0x0818
	L9B0_MIFA_RD_REQ_PRI0_T             mifa_rd_req_pri0;                    // 0x081c
	L9B0_MIFA_RD_REQ_PRI1_T             mifa_rd_req_pri1;                    // 0x0820
	L9B0_MIFA_WD_REQ_PRI0_T             mifa_wd_req_pri0;                    // 0x0824
	L9B0_MIFA_RD_REQ_STV0_T             mifa_rd_req_stv0;                    // 0x0828
	L9B0_MIFA_RD_REQ_STV1_T             mifa_rd_req_stv1;                    // 0x082c
	L9B0_MIFA_WD_REQ_STV0_T             mifa_wd_req_stv0;                    // 0x0830
	L9B0_MIFA_RD_CMD_PEND0_T            mifa_rd_cmd_pend0;                   // 0x0834
	L9B0_MIFA_RD_CMD_PEND1_T            mifa_rd_cmd_pend1;                   // 0x0838
	L9B0_MIFA_WD_CMD_PEND0_T            mifa_wd_cmd_pend0;                   // 0x083c
	L9B0_MIFA_RD_CMD_STRIDE0_T          mifa_rd_cmd_stride0;                 // 0x0840
	L9B0_MIFA_RD_CMD_STRIDE1_T          mifa_rd_cmd_stride1;                 // 0x0844
	L9B0_MIFA_RD_CMD_STRIDE2_T          mifa_rd_cmd_stride2;                 // 0x0848
	L9B0_MIFA_RD_CMD_STRIDE_SET_T       mifa_rd_cmd_stride_set;              // 0x084c
	L9B0_MIFA_WD_CMD_STRIDE0_T          mifa_wd_cmd_stride0;                 // 0x0850
	L9B0_MIFA_WD_CMD_STRIDE_SET_T       mifa_wd_cmd_stride_set;              // 0x0854
	L9B0_MIFA_SADDR_RD_MVI_Y_MVI_C_T    mifa_saddr_rd_mvi_y_mvi_c;           // 0x0858
	L9B0_MIFA_SADDR_RD_PREW_Y_T         mifa_saddr_rd_prew_y;                // 0x085c
	L9B0_MIFA_SADDR_RD_PREW_C_T         mifa_saddr_rd_prew_c;                // 0x0860
	L9B0_MIFA_SADDR_RD_IPC0_Y_T         mifa_saddr_rd_ipc0_y;                // 0x0864
	L9B0_MIFA_SADDR_RD_IPC_C_T          mifa_saddr_rd_ipc_c;                 // 0x0868
	L9B0_MIFA_SADDR_RD_IPC1_Y_T         mifa_saddr_rd_ipc1_y;                // 0x086c
	L9B0_MIFA_SADDR_RD_TNR0_Y_T         mifa_saddr_rd_tnr0_y;                // 0x0870
	L9B0_MIFA_SADDR_RD_TNR_C_T          mifa_saddr_rd_tnr_c;                 // 0x0874
	L9B0_MIFA_SADDR_RD_TNR1_Y_T         mifa_saddr_rd_tnr1_y;                // 0x0878
	L9B0_MIFA_SADDR_WD_TNR_Y_T          mifa_saddr_wd_tnr_y;                 // 0x087c
	L9B0_MIFA_SADDR_WD_TNR_C_T          mifa_saddr_wd_tnr_c;                 // 0x0880
	L9B0_MIFA_SADDR_WD_PREW_Y_T         mifa_saddr_wd_prew_y;                // 0x0884
	L9B0_MIFA_SADDR_WD_PREW_C_T         mifa_saddr_wd_prew_c;                // 0x0888
	L9B0_MIFA_SADDR_RD_DL_Y_T           mifa_saddr_rd_dl_y;                  // 0x088c
	L9B0_MIFA_SADDR_RD_DL_C_T           mifa_saddr_rd_dl_c;                  // 0x0890
	L9B0_MIFA_SADDR_RD_DR_Y_T           mifa_saddr_rd_dr_y;                  // 0x0894
	L9B0_MIFA_SADDR_RD_DR_C_T           mifa_saddr_rd_dr_c;                  // 0x0898
	L9B0_MIFA_SADDR_WD_DL_Y_T           mifa_saddr_wd_dl_y;                  // 0x089c
	L9B0_MIFA_SADDR_WD_DL_C_T           mifa_saddr_wd_dl_c;                  // 0x08a0
	L9B0_MIFA_SADDR_WD_DR_Y_T           mifa_saddr_wd_dr_y;                  // 0x08a4
	L9B0_MIFA_SADDR_WD_DR_C_T           mifa_saddr_wd_dr_c;                  // 0x08a8
	L9B0_MIFA_SADDR_RD_EXT0_T           mifa_saddr_rd_ext0;                  // 0x08ac
	L9B0_MIFA_SADDR_RD_EXT1_T           mifa_saddr_rd_ext1;                  // 0x08b0
	L9B0_MIFA_SADDR_RD_EXT2_T           mifa_saddr_rd_ext2;                  // 0x08b4
	L9B0_MIFA_SADDR_WD_EXT0_T           mifa_saddr_wd_ext0;                  // 0x08b8
	L9B0_MIFA_RD_DR_DL_EXT_T            mifa_rd_dr_dl_ext;                   // 0x08bc
	L9B0_MIFA_WD_DR_DL_EXT_T            mifa_wd_dr_dl_ext;                   // 0x08c0
	L9B0_MIFA_STATUS_T                  mifa_status;                         // 0x08c4
	L9B0_MIFA_SADDR_PARAM_UPDATE0_M_T   mifa_saddr_param_update0_m;          // 0x08c8
	L9B0_MIFA_SADDR_PARAM_UPDATE0_M1_T  mifa_saddr_param_update0_m1;         // 0x08cc
	L9B0_MIFA_RD_BANK_8_ADDR0_T         mifa_rd_bank_8_addr0;                // 0x08d0
	L9B0_MIFA_RD_BANK_8_ADDR1_T         mifa_rd_bank_8_addr1;                // 0x08d4
	L9B0_MIFA_RD_BANK_2_ADDR0_T         mifa_rd_bank_2_addr0;                // 0x08d8
	L9B0_MIFA_RD_BANK_2_ADDR1_T         mifa_rd_bank_2_addr1;                // 0x08dc
	L9B0_MIFA_WD_BANK_8_ADDR0_T         mifa_wd_bank_8_addr0;                // 0x08e0
	L9B0_MIFA_WD_BANK_8_ADDR1_T         mifa_wd_bank_8_addr1;                // 0x08e4
	L9B0_MIFA_WD_BANK_2_ADDR0_T         mifa_wd_bank_2_addr0;                // 0x08e8
	L9B0_MIFA_WD_BANK_2_ADDR1_T         mifa_wd_bank_2_addr1;                // 0x08ec
	L9B0_MIFA_LSB_SWITCH_T              mifa_lsb_switch;                     // 0x08f0
	L9B0_MIFA_RD_REQ_PEND0_T            mifa_rd_req_pend0;                   // 0x08f4
	L9B0_MIFA_RD_REQ_PEND1_T            mifa_rd_req_pend1;                   // 0x08f8
	L9B0_MIFA_RD_REQ_PEND2_T            mifa_rd_req_pend2;                   // 0x08fc
	L9B0_MIFA_WD_REQ_PEND0_T            mifa_wd_req_pend0;                   // 0x0900
	L9B0_MIFA_RD_CMD_PRI0_S_T           mifa_rd_cmd_pri0_s;                  // 0x0904
	L9B0_MIFA_RD_CMD_PRI1_S_T           mifa_rd_cmd_pri1_s;                  // 0x0908
	L9B0_MIFA_WD_CMD_PRI0_S_T           mifa_wd_cmd_pri0_s;                  // 0x090c
	L9B0_MIFA_RESET_T                   mifa_reset;                          // 0x0910
} DE_MIA_REG_L9B0_T;

typedef struct {
	L9B0_MIFB_RD_CTRL_T                 mifb_rd_ctrl;                        // 0x1b00
	L9B0_MIFB_WD_CTRL_T                 mifb_wd_ctrl;                        // 0x1b04
	L9B0_MIFB_RD_SET_10B_T              mifb_rd_set_10b;                     // 0x1b08
	L9B0_MIFB_WD_SET_10B_T              mifb_wd_set_10b;                     // 0x1b0c
	L9B0_MIFB_RD_CMD_PRI0_T             mifb_rd_cmd_pri0;                    // 0x1b10
	L9B0_MIFB_WD_CMD_PRI0_T             mifb_wd_cmd_pri0;                    // 0x1b14
	L9B0_MIFB_RD_REQ_PRI0_T             mifb_rd_req_pri0;                    // 0x1b18
	L9B0_MIFB_WD_REQ_PRI0_T             mifb_wd_req_pri0;                    // 0x1b1c
	L9B0_MIFB_RD_REQ_STV0_T             mifb_rd_req_stv0;                    // 0x1b20
	L9B0_MIFB_WD_REQ_STV0_T             mifb_wd_req_stv0;                    // 0x1b24
	L9B0_MIFB_RD_CMD_PEND0_T            mifb_rd_cmd_pend0;                   // 0x1b28
	L9B0_MIFB_WD_CMD_PEND0_T            mifb_wd_cmd_pend0;                   // 0x1b2c
	L9B0_MIFB_RD_CMD_STRIDE0_T          mifb_rd_cmd_stride0;                 // 0x1b30
	L9B0_MIFB_RD_CMD_STRIDE_SET_T       mifb_rd_cmd_stride_set;              // 0x1b34
	L9B0_MIFB_WD_CMD_STRIDE0_T          mifb_wd_cmd_stride0;                 // 0x1b38
	L9B0_MIFB_WD_CMD_STRIDE_SET_T       mifb_wd_cmd_stride_set;              // 0x1b3c
	L9B0_MIFB_SADDR_RD_OVM_Y_T          mifb_saddr_rd_ovm_y;                 // 0x1b40
	L9B0_MIFB_SADDR_RD_OVM_C_T          mifb_saddr_rd_ovm_c;                 // 0x1b44
	L9B0_MIFB_SADDR_RD_OVS_Y_OVS_C_T    mifb_saddr_rd_ovs_y_ovs_c;           // 0x1b48
	L9B0_MIFB_SADDR_WD_SM_Y_T           mifb_saddr_wd_sm_y;                  // 0x1b4c
	L9B0_MIFB_SADDR_WD_SM_C_T           mifb_saddr_wd_sm_c;                  // 0x1b50
	L9B0_MIFB_SADDR_RD_EXT0_T           mifb_saddr_rd_ext0;                  // 0x1b54
	L9B0_MIFB_SADDR_WD_EXT0_T           mifb_saddr_wd_ext0;                  // 0x1b58
	L9B0_MIFB_STATUS_T                  mifb_status;                         // 0x1b5c
	L9B0_MIFB_SADDR_PARAM_UPDATE0_M_T   mifb_saddr_param_update0_m;          // 0x1b60
	L9B0_MIFB_RD_BANK_8_ADDR0_T         mifb_rd_bank_8_addr0;                // 0x1b64
	L9B0_MIFB_RD_BANK_8_ADDR1_T         mifb_rd_bank_8_addr1;                // 0x1b68
	L9B0_MIFB_RD_BANK_2_ADDR0_T         mifb_rd_bank_2_addr0;                // 0x1b6c
	L9B0_MIFB_RD_BANK_2_ADDR1_T         mifb_rd_bank_2_addr1;                // 0x1b70
	L9B0_MIFB_WD_BANK_8_ADDR0_T         mifb_wd_bank_8_addr0;                // 0x1b74
	L9B0_MIFB_WD_BANK_8_ADDR1_T         mifb_wd_bank_8_addr1;                // 0x1b78
	L9B0_MIFB_WD_BANK_2_ADDR0_T         mifb_wd_bank_2_addr0;                // 0x1b7c
	L9B0_MIFB_WD_BANK_2_ADDR1_T         mifb_wd_bank_2_addr1;                // 0x1b80
	L9B0_MIFB_LSB_SWITCH_T              mifb_lsb_switch;                     // 0x1b84
	L9B0_MIFB_RD_REQ_PEND0_T            mifb_rd_req_pend0;                   // 0x1b88
	L9B0_MIFB_WD_REQ_PEND0_T            mifb_wd_req_pend0;                   // 0x1b8c
	L9B0_MIFB_RD_CMD_PRI00_S_T          mifb_rd_cmd_pri00_s;                 // 0x1b90
	L9B0_MIFB_WD_CMD_PRI00_S_T          mifb_wd_cmd_pri00_s;                 // 0x1b94
	L9B0_MIFB_RESET_T                   mifb_reset;                          // 0x1b98
} DE_MIB_REG_L9B0_T;

typedef struct {
	L9B0_MIFC_RD_CTRL_T                 mifc_rd_ctrl;                        // 0x2800
	L9B0_MIFC_WD_CTRL_T                 mifc_wd_ctrl;                        // 0x2804
	L9B0_MIFC_RD_CMD_PRI0_T             mifc_rd_cmd_pri0;                    // 0x2808
	L9B0_MIFC_RD_CMD_PRI1_T             mifc_rd_cmd_pri1;                    // 0x280c
	L9B0_MIFC_WD_CMD_PRI0_T             mifc_wd_cmd_pri0;                    // 0x2810
	L9B0_MIFC_RD_REQ_PRI0_T             mifc_rd_req_pri0;                    // 0x2814
	L9B0_MIFC_RD_REQ_PRI1_T             mifc_rd_req_pri1;                    // 0x2818
	L9B0_MIFC_WD_REQ_PRI0_T             mifc_wd_req_pri0;                    // 0x281c
	L9B0_MIFC_RD_REQ_STV0_T             mifc_rd_req_stv0;                    // 0x2820
	L9B0_MIFC_RD_REQ_STV1_T             mifc_rd_req_stv1;                    // 0x2824
	L9B0_MIFC_WD_REQ_STV0_T             mifc_wd_req_stv0;                    // 0x2828
	L9B0_MIFC_RD_CMD_PEND0_T            mifc_rd_cmd_pend0;                   // 0x282c
	L9B0_MIFC_RD_CMD_PEND1_T            mifc_rd_cmd_pend1;                   // 0x2830
	L9B0_MIFC_WD_CMD_PEND0_T            mifc_wd_cmd_pend0;                   // 0x2834
	L9B0_MIFC_RD_CMD_STRIDE0_T          mifc_rd_cmd_stride0;                 // 0x2838
	L9B0_MIFC_RD_CMD_STRIDE1_T          mifc_rd_cmd_stride1;                 // 0x283c
	L9B0_MIFC_RD_CMD_STRIDE_SET_T       mifc_rd_cmd_stride_set;              // 0x2840
	L9B0_MIFC_WD_CMD_STRIDE0_T          mifc_wd_cmd_stride0;                 // 0x2844
	L9B0_MIFC_WD_CMD_STRIDE_SET_T       mifc_wd_cmd_stride_set;              // 0x2848
	L9B0_MIFC_SADDR_RD_MVI_Y_MVI_C_T    mifc_saddr_rd_mvi_y_mvi_c;           // 0x284c
	L9B0_MIFC_SADDR_RD_PREW_Y_PREW_C_T  mifc_saddr_rd_prew_y_prew_c;         // 0x2850
	L9B0_MIFC_SADDR_RD_IPC0_Y_IPC_C_T   mifc_saddr_rd_ipc0_y_ipc_c;          // 0x2854
	L9B0_MIFC_SADDR_RD_IPC1_Y_TNR0_Y_T  mifc_saddr_rd_ipc1_y_tnr0_y;         // 0x2858
	L9B0_MIFC_SADDR_RD_SS_Y_SS_C_T      mifc_saddr_rd_ss_y_ss_c;             // 0x285c
	L9B0_MIFC_SADDR_RD_TNR_C_T          mifc_saddr_rd_tnr_c;                 // 0x2860
	L9B0_MIFC_SADDR_WD_SS_Y_SS_C_T      mifc_saddr_wd_ss_y_ss_c;             // 0x2864
	L9B0_MIFC_SADDR_WD_TNR_Y_TNR_C_T    mifc_saddr_wd_tnr_y_tnr_c;           // 0x2868
	L9B0_MIFC_SADDR_WD_PREW_Y_PREW_C_T  mifc_saddr_wd_prew_y_prew_c;         // 0x286c
	L9B0_MIFC_SADDR_RD_DL_Y_DL_C_T      mifc_saddr_rd_dl_y_dl_c;             // 0x2870
	L9B0_MIFC_SADDR_RD_DR_Y_DR_C_T      mifc_saddr_rd_dr_y_dr_c;             // 0x2874
	L9B0_MIFC_SADDR_WD_DL_Y_DL_C_T      mifc_saddr_wd_dl_y_dl_c;             // 0x2878
	L9B0_MIFC_SADDR_WD_DR_Y_DR_C_T      mifc_saddr_wd_dr_y_dr_c;             // 0x287c
	L9B0_MIFC_SADDR_RD_EXT0_T           mifc_saddr_rd_ext0;                  // 0x2880
	L9B0_MIFC_SADDR_RD_EXT1_T           mifc_saddr_rd_ext1;                  // 0x2884
	L9B0_MIFC_SADDR_WD_EXT0_T           mifc_saddr_wd_ext0;                  // 0x2888
	L9B0_MIFC_RD_DR_DL_EXT_T            mifc_rd_dr_dl_ext;                   // 0x288c
	L9B0_MIFC_WD_DR_DL_EXT_T            mifc_wd_dr_dl_ext;                   // 0x2890
	L9B0_MIFC_STATUS_T                  mifc_status;                         // 0x2894
	L9B0_MIFC_SADDR_PARAM_UPDATE0_M_T   mifc_saddr_param_update0_m;          // 0x2898
	L9B0_MIFC_RD_BANK_8_ADDR0_T         mifc_rd_bank_8_addr0;                // 0x289c
	L9B0_MIFC_RD_BANK_8_ADDR1_T         mifc_rd_bank_8_addr1;                // 0x28a0
	L9B0_MIFC_RD_BANK_2_ADDR0_T         mifc_rd_bank_2_addr0;                // 0x28a4
	L9B0_MIFC_RD_BANK_2_ADDR1_T         mifc_rd_bank_2_addr1;                // 0x28a8
	L9B0_MIFC_WD_BANK_8_ADDR0_T         mifc_wd_bank_8_addr0;                // 0x28ac
	L9B0_MIFC_WD_BANK_8_ADDR1_T         mifc_wd_bank_8_addr1;                // 0x28b0
	L9B0_MIFC_WD_BANK_2_ADDR0_T         mifc_wd_bank_2_addr0;                // 0x28b4
	L9B0_MIFC_WD_BANK_2_ADDR1_T         mifc_wd_bank_2_addr1;                // 0x28b8
	L9B0_MIFC_RD_REQ_PEND0_T            mifc_rd_req_pend0;                   // 0x28bc
	L9B0_MIFC_RD_REQ_PEND1_T            mifc_rd_req_pend1;                   // 0x28c0
	L9B0_MIFC_RD_REQ_PEND2_T            mifc_rd_req_pend2;                   // 0x28c4
	L9B0_MIFC_WD_REQ_PEND0_T            mifc_wd_req_pend0;                   // 0x28c8
	L9B0_MIFC_WD_REQ_PEND1_T            mifc_wd_req_pend1;                   // 0x28cc
	L9B0_MIFC_RD_CMD_PRI0_S_T           mifc_rd_cmd_pri0_s;                  // 0x28d0
	L9B0_MIFC_RD_CMD_PRI1_S_T           mifc_rd_cmd_pri1_s;                  // 0x28d4
	L9B0_MIFC_WD_CMD_PRI0_S_T           mifc_wd_cmd_pri0_s;                  // 0x28d8
	L9B0_MIFC_RESET_T                   mifc_reset;                          // 0x28dc
} DE_MIC_REG_L9B0_T;

typedef struct {
	L9B0_MIFD_RD_CTRL_T                 mifd_rd_ctrl;                        // 0x3900
	L9B0_MIFD_WD_CTRL_T                 mifd_wd_ctrl;                        // 0x3904
	L9B0_MIFD_RD_CMD_PRI0_T             mifd_rd_cmd_pri0;                    // 0x3908
	L9B0_MIFD_WD_CMD_PRI0_T             mifd_wd_cmd_pri0;                    // 0x390c
	L9B0_MIFD_RD_REQ_PRI0_T             mifd_rd_req_pri0;                    // 0x3910
	L9B0_MIFD_WD_REQ_PRI0_T             mifd_wd_req_pri0;                    // 0x3914
	L9B0_MIFD_RD_REQ_STV0_T             mifd_rd_req_stv0;                    // 0x3918
	L9B0_MIFD_WD_REQ_STV0_T             mifd_wd_req_stv0;                    // 0x391c
	L9B0_MIFD_RD_CMD_PEND0_T            mifd_rd_cmd_pend0;                   // 0x3920
	L9B0_MIFD_WD_CMD_PEND0_T            mifd_wd_cmd_pend0;                   // 0x3924
	L9B0_MIFD_RD_CMD_STRIDE0_T          mifd_rd_cmd_stride0;                 // 0x3928
	L9B0_MIFD_RD_CMD_STRIDE_SET_T       mifd_rd_cmd_stride_set;              // 0x392c
	L9B0_MIFD_WD_CMD_STRIDE0_T          mifd_wd_cmd_stride0;                 // 0x3930
	L9B0_MIFD_WD_CMD_STRIDE_SET_T       mifd_wd_cmd_stride_set;              // 0x3934
	L9B0_MIFD_SADDR_RD_OV_Y_OV_C_T      mifd_saddr_rd_ov_y_ov_c;             // 0x3938
	L9B0_MIFD_SADDR_WD_SM_YC_T          mifd_saddr_wd_sm_yc;                 // 0x393c
	L9B0_MIFD_SADDR_RD_EXT0_T           mifd_saddr_rd_ext0;                  // 0x3940
	L9B0_MIFD_SADDR_WD_EXT0_T           mifd_saddr_wd_ext0;                  // 0x3944
	L9B0_MIFD_STATUS_T                  mifd_status;                         // 0x3948
	L9B0_MIFD_SADDR_PARAM_UPDATE0_M_T   mifd_saddr_param_update0_m;          // 0x394c
	L9B0_MIFD_RD_BANK_8_ADDR0_T         mifd_rd_bank_8_addr0;                // 0x3950
	L9B0_MIFD_RD_BANK_8_ADDR1_T         mifd_rd_bank_8_addr1;                // 0x3954
	L9B0_MIFD_RD_BANK_2_ADDR0_T         mifd_rd_bank_2_addr0;                // 0x3958
	L9B0_MIFD_RD_BANK_2_ADDR1_T         mifd_rd_bank_2_addr1;                // 0x395c
	L9B0_MIFD_WD_BANK_8_ADDR0_T         mifd_wd_bank_8_addr0;                // 0x3960
	L9B0_MIFD_WD_BANK_8_ADDR1_T         mifd_wd_bank_8_addr1;                // 0x3964
	L9B0_MIFD_WD_BANK_2_ADDR0_T         mifd_wd_bank_2_addr0;                // 0x3968
	L9B0_MIFD_WD_BANK_2_ADDR1_T         mifd_wd_bank_2_addr1;                // 0x396c
	L9B0_MIFD_RD_REQ_PEND0_T            mifd_rd_req_pend0;                   // 0x3970
	L9B0_MIFD_WD_REQ_PEND0_T            mifd_wd_req_pend0;                   // 0x3974
	L9B0_MIFD_RD_CMD_PRI0_S_T           mifd_rd_cmd_pri0_s;                  // 0x3978
	L9B0_MIFD_WD_CMD_PRI0_S_T           mifd_wd_cmd_pri0_s;                  // 0x397c
	L9B0_MIFD_RESET_T                   mifd_reset;                          // 0x3980
} DE_MID_REG_L9B0_T;

typedef struct {
	L9B0_MIFF_RD_CTRL_T                 miff_rd_ctrl;                        // 0x5f00
	L9B0_MIFF_RD_CMD_PRI0_T             miff_rd_cmd_pri0;                    // 0x5f04
	L9B0_MIFF_RD_REQ_PRI0_T             miff_rd_req_pri0;                    // 0x5f08
	L9B0_MIFF_RD_REQ_STV0_T             miff_rd_req_stv0;                    // 0x5f0c
	L9B0_MIFF_RD_CMD_PEND0_T            miff_rd_cmd_pend0;                   // 0x5f10
	L9B0_MIFF_RD_CMD_STRIDE0_T          miff_rd_cmd_stride0;                 // 0x5f14
	L9B0_MIFF_RD_CMD_STRIDE_SET_T       miff_rd_cmd_stride_set;              // 0x5f18
	L9B0_MIFF_SADDR_RD_OSD_01_T         miff_saddr_rd_osd_01;                // 0x5f1c
	L9B0_MIFF_SADDR_RD_OSD_23_T         miff_saddr_rd_osd_23;                // 0x5f20
	L9B0_MIFF_SADDR_RD_CVE_YC_T         miff_saddr_rd_cve_yc;                // 0x5f24
	L9B0_MIFF_SADDR_RD_EXT0_T           miff_saddr_rd_ext0;                  // 0x5f28
	L9B0_MIFF_STATUS_T                  miff_status;                         // 0x5f2c
	L9B0_MIFF_RD_BANK_8_ADDR0_T         miff_rd_bank_8_addr0;                // 0x5f30
	L9B0_MIFF_RD_BANK_8_ADDR1_T         miff_rd_bank_8_addr1;                // 0x5f34
	L9B0_MIFF_RD_BANK_2_ADDR0_T         miff_rd_bank_2_addr0;                // 0x5f38
	L9B0_MIFF_RD_BANK_2_ADDR1_T         miff_rd_bank_2_addr1;                // 0x5f3c
	L9B0_MIFF_RD_REQ_PEND0_T            miff_rd_req_pend0;                   // 0x5f40
	L9B0_MIFF_RD_CMD_PRI0_S_T           miff_rd_cmd_pri0_s;                  // 0x5f44
	L9B0_MIFF_RESET_T                   miff_reset;                          // 0x5f48
	L9B0_MIFF_SADDR_PARAM_UPDATE0_M_T   miff_saddr_param_update0_m;          // 0x5f4c
} DE_MIF_REG_L9B0_T;

#endif
