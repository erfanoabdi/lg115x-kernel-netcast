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

#ifndef _REG_VENC_L9_IPC_h
 #define _REG_VENC_L9_IPC_h

/* VENC IPC Registers from 0x800 ~ 0x8f4 */
/*-----------------------------------------------------------------------------
	0x0800 SW_VERSION ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		yymmddhh                        ;   	// 31: 0
	}be;
	struct {
		UINT32		yymmddhh                        ;   	// 31: 0
	}le;
} SW_VERSION;

/*-----------------------------------------------------------------------------
	0x080C VENC_CONFIG0 ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		spe_modesel						: 3;	// 31:29
		UINT32		dbg_me_level0_enable			: 1;	//    28
		UINT32		_rsvd_01                        : 3;	// 27:25
		UINT32		qp_level						: 5;	// 24:20
		UINT32		_rsvd_00                        :11;	// 19: 9
		UINT32		deblock_off						: 1;	//     8
		UINT32		hlambda							: 4;	//  7: 4
		UINT32		me_level1_enable				: 1;	//     3
		UINT32		en_pskip_off					: 1;	//     2
		UINT32		en_mvnum_rst					: 1;	//     1
		UINT32		me_level2_enable				: 1;	//     0
	}be;
	struct {
		UINT32		me_level2_enable				: 1;	//     0
		UINT32		en_mvnum_rst					: 1;	//     1
		UINT32		en_pskip_off					: 1;	//     2
		UINT32		me_level1_enable				: 1;	//     3
		UINT32		hlambda							: 4;	//  7: 4
		UINT32		deblock_off						: 1;	//     8
		UINT32		_rsvd_00                        :11;	// 19: 9
		UINT32		qp_level						: 5;	// 24:20
		UINT32		_rsvd_01                        : 3;	// 27:25
		UINT32		dbg_me_level0_enable			: 1;	//    28
		UINT32		spe_modesel						: 3;	// 31:29
	}le;
} VENC_CONFIG0;

/*-----------------------------------------------------------------------------
	0x0810 VENC_MODE_IN ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :28;	// 31: 4
		UINT32		input_mode                      : 4;	//  3: 0
	}be;
	struct {
		UINT32		input_mode                      : 4;	//  3: 0
		UINT32		_rsvd_00                        :28;	// 31: 4
	}le;
} VENC_MODE_IN;

/*-----------------------------------------------------------------------------
	0x0814 VENC_MODE2_IN ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		dbg_force_bp					: 1;	// 31
		UINT32		_rsvd_00                        : 4;	// 30:27
		UINT32		gop_idr                         : 1;	//    26
		UINT32		gop_m                           : 2;	// 25:24
		UINT32		gop_n                           : 8;	// 23:16
		UINT32		_rsvd_01                        : 6;	// 15:10
		UINT32		yuyv                            : 2;	//  9: 8
		UINT32		color_format                    : 4;	//  7: 4
		UINT32		_rsvd_02                        : 2;	//  3: 2
		UINT32		source                          : 2;	//  1: 0
	}be;
	struct {
		UINT32		source                          : 2;	//  1: 0
		UINT32		_rsvd_02                        : 2;	//  3: 2
		UINT32		color_format                    : 4;	//  7: 4
		UINT32		yuyv                            : 2;	//  9: 8
		UINT32		_rsvd_01                        : 6;	// 15:10
		UINT32		gop_n                           : 8;	// 23:16
		UINT32		gop_m                           : 2;	// 25:24
		UINT32		gop_idr                         : 1;	//    26
		UINT32		_rsvd_00                        : 4;	// 30:27
		UINT32		dbg_force_bp					: 1;	// 31
	}le;
} VENC_MODE2_IN;

/*-----------------------------------------------------------------------------
	0x0818 VENC_FRAME_BA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ba                              ;   	// 31: 0
	}be;
	struct {
		UINT32		ba                              ;   	// 31: 0
	}le;
} VENC_FRAME_BA;

/*-----------------------------------------------------------------------------
	0x081c VENC_DPB_BA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ba                              ;   	// 31: 0
	}be;
	struct {
		UINT32		ba                              ;   	// 31: 0
	}le;
} VENC_DPB_BA;

/*-----------------------------------------------------------------------------
	0x0820 THUMBNAIL_BA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ba                              ;   	// 31: 0
	}be;
	struct {
		UINT32		ba                              ;   	// 31: 0
	}le;
} THUMBNAIL_BA;

/*-----------------------------------------------------------------------------
	0x0824 RD_CTRL ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		rd_ctrl_enable					: 1;		//    31
		UINT32		reserved0                       : 3;		// 30:28		
		UINT32		threshold						: 12;	// 27:16
		UINT32		target_bitrate					: 16;	// 15: 0
	}be;
	struct {
		UINT32		target_bitrate					: 16;	// 15: 0
		UINT32		threshold						: 12;	// 27:16		
		UINT32		reserved0                       : 3;		// 30:28
		UINT32		rd_ctrl_enable					: 1;		//    31
	}le;
} RD_CTRL;

/*-----------------------------------------------------------------------------
	0x0828 EXT_IPC_STATE ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		vdec_cmd                        : 1;	//    31
		UINT32		reserved0                       : 3;	// 30:28
		UINT32		ves_eda                         : 1;	//    27
		UINT32		ves_bsa                         : 1;	//    26
		UINT32		venc_ctrl                       : 1;	//    25
		UINT32		venc_ext_esrptr                 : 1;	//    24
		UINT32		venc_ext_eswptr                 : 1;	//    23
		UINT32		reserved1                       : 1;	//    22
		UINT32		reserved2                       : 5;	// 21:17
		UINT32		thumb_bsa_out                   : 1;	//    16
		UINT32		thumb_bsa_in                    : 1;	//    15
		UINT32		thumb_sz_out                    : 1;	//    14
		UINT32		thumb_sz_in                     : 1;	//    13
		UINT32		thumb_ctrl                      : 1;	//    12
		UINT32		reserved3                       : 3;	// 11: 9
		UINT32		venc_widx_ibf                   : 1;	//     8
		UINT32		reserved4                       : 8;	//  7: 0
	}be;
	struct {
		UINT32		reserved4                       : 8;	//  7: 0
		UINT32		venc_widx_ibf                   : 1;	//     8
		UINT32		reserved3                       : 3;	// 11: 9
		UINT32		thumb_ctrl                      : 1;	//    12
		UINT32		thumb_sz_in                     : 1;	//    13
		UINT32		thumb_sz_out                    : 1;	//    14
		UINT32		thumb_bsa_in                    : 1;	//    15
		UINT32		thumb_bsa_out                   : 1;	//    16
		UINT32		reserved2                       : 5;	// 21:17
		UINT32		reserved1                       : 1;	//    22
		UINT32		venc_ext_eswptr                 : 1;	//    23
		UINT32		venc_ext_esrptr                 : 1;	//    24
		UINT32		venc_ctrl                       : 1;	//    25
		UINT32		ves_bsa                         : 1;	//    26
		UINT32		ves_eda                         : 1;	//    27
		UINT32		reserved0                       : 3;	// 30:28
		UINT32		vdec_cmd                        : 1;	//    31
	}le;
} EXT_IPC_STATE;

/*-----------------------------------------------------------------------------
	0x082c INT_IPC_STATE ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		reserved0                       : 4;	// 31:28
		UINT32		ves_eda                         : 1;	//    27
		UINT32		ves_bsa                         : 1;	//    26
		UINT32		venc_ctrl                       : 1;	//    25
		UINT32		venc_ext_esrptr                 : 1;	//    24
		UINT32		venc_ext_eswptr                 : 1;	//    23
		UINT32		venc_gauge                      : 1;	//    22
		UINT32		reserved1                       : 5;	// 21:17
		UINT32		thumb_bsa_out                   : 1;	//    16
		UINT32		thumb_bsa_in                    : 1;	//    15
		UINT32		thumb_sz_out                    : 1;	//    14
		UINT32		thumb_sz_in                     : 1;	//    13
		UINT32		thumb_ctrl                      : 1;	//    12
		UINT32		reserved2                       : 2;	// 11:10
		UINT32		venc_ridx_ibf                   : 1;	//     9
		UINT32		reserved3                       : 8;	//  8: 1
		UINT32		senc_ctrl                       : 1;	//     0
	}be;
	struct {
		UINT32		senc_ctrl                       : 1;	//     0
		UINT32		reserved3                       : 8;	//  8: 1
		UINT32		venc_ridx_ibf                   : 1;	//     9
		UINT32		reserved2                       : 2;	// 11:10
		UINT32		thumb_ctrl                      : 1;	//    12
		UINT32		thumb_sz_in                     : 1;	//    13
		UINT32		thumb_sz_out                    : 1;	//    14
		UINT32		thumb_bsa_in                    : 1;	//    15
		UINT32		thumb_bsa_out                   : 1;	//    16
		UINT32		reserved1                       : 5;	// 21:17
		UINT32		venc_gauge                      : 1;	//    22
		UINT32		venc_ext_eswptr                 : 1;	//    23
		UINT32		venc_ext_esrptr                 : 1;	//    24
		UINT32		venc_ctrl                       : 1;	//    25
		UINT32		ves_bsa                         : 1;	//    26
		UINT32		ves_eda                         : 1;	//    27
		UINT32		reserved0                       : 4;	// 31:28
	}le;
} INT_IPC_STATE;

/*-----------------------------------------------------------------------------
	0x0830 SENC_CTRL ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :11;	// 31:21
		UINT32		vdec_au_empty                   : 1;	//    20
		UINT32		adec_au_empty                   : 1;	//    19
		UINT32		vdec_au_full                    : 1;	//    18
		UINT32		adec_au_full                    : 1;	//    17
		UINT32		aes_wptr_err                    : 1;	//    16
		UINT32		_rsvd_01                        :15;	// 15: 1
		UINT32		senc_disable                    : 1;	//     0
	}be;
	struct {
		UINT32		senc_disable                    : 1;	//     0
		UINT32		_rsvd_01                        :15;	// 15: 1
		UINT32		aes_wptr_err                    : 1;	//    16
		UINT32		adec_au_full                    : 1;	//    17
		UINT32		vdec_au_full                    : 1;	//    18
		UINT32		adec_au_empty                   : 1;	//    19
		UINT32		vdec_au_empty                   : 1;	//    20
		UINT32		_rsvd_00                        :11;	// 31:21
	}le;
} SENC_CTRL;

/*-----------------------------------------------------------------------------
	0x0834 TS_CNT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ts_cnt                          ;   	// 31: 0
	}be;
	struct {
		UINT32		ts_cnt                          ;   	// 31: 0
	}le;
} TS_CNT;

/*-----------------------------------------------------------------------------
	0x0838 V_TS_CNT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		v_ts_cnt                        ;   	// 31: 0
	}be;
	struct {
		UINT32		v_ts_cnt                        ;   	// 31: 0
	}le;
} V_TS_CNT;

/*-----------------------------------------------------------------------------
	0x083c A_TS_CNT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		a_ts_cnt                        ;   	// 31: 0
	}be;
	struct {
		UINT32		a_ts_cnt                        ;   	// 31: 0
	}le;
} A_TS_CNT;

/*-----------------------------------------------------------------------------
	0x0840 VES_AUI_WPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ves_aui_wptr                    ;   	// 31: 0
	}be;
	struct {
		UINT32		ves_aui_wptr                    ;   	// 31: 0
	}le;
} VES_AUI_WPTR;

/*-----------------------------------------------------------------------------
	0x0844 VES_AUI_RPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ves_aui_rptr                    ;   	// 31: 0
	}be;
	struct {
		UINT32		ves_aui_rptr                    ;   	// 31: 0
	}le;
} VES_AUI_RPTR;

/*-----------------------------------------------------------------------------
	0x0848 VES_AU_WPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ves_au_wptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		ves_au_wptr                     ;   	// 31: 0
	}le;
} VES_AU_WPTR;

/*-----------------------------------------------------------------------------
	0x084c VES_AU_RPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ves_au_rptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		ves_au_rptr                     ;   	// 31: 0
	}le;
} VES_AU_RPTR;

/*-----------------------------------------------------------------------------
	0x0850 AES_BASE_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_base_addr                   ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_base_addr                   ;   	// 31: 0
	}le;
} AES_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x0854 AES_END_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_end_addr                    ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_end_addr                    ;   	// 31: 0
	}le;
} AES_END_ADDR;

/*-----------------------------------------------------------------------------
	0x0858 AAUI_BASE_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aaui_base_addr                  ;   	// 31: 0
	}be;
	struct {
		UINT32		aaui_base_addr                  ;   	// 31: 0
	}le;
} AAUI_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x085c AAUI_END_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aaui_end_addr                   ;   	// 31: 0
	}be;
	struct {
		UINT32		aaui_end_addr                   ;   	// 31: 0
	}le;
} AAUI_END_ADDR;

/*-----------------------------------------------------------------------------
	0x0860 VES_BUF_STAT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ves_buf_stat                    ;   	// 31: 0
	}be;
	struct {
		UINT32		ves_buf_stat                    ;   	// 31: 0
	}le;
} VES_BUF_STAT;

/*-----------------------------------------------------------------------------
	0x0864 AES_DTS_OFFSET ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_dts_offset                  ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_dts_offset                  ;   	// 31: 0
	}le;
} AES_DTS_OFFSET;

/*-----------------------------------------------------------------------------
	0x0868 AES_AUI_WPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_aui_wptr                    ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_aui_wptr                    ;   	// 31: 0
	}le;
} AES_AUI_WPTR;

/*-----------------------------------------------------------------------------
	0x086c AES_AUI_RPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_aui_rptr                    ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_aui_rptr                    ;   	// 31: 0
	}le;
} AES_AUI_RPTR;

/*-----------------------------------------------------------------------------
	0x0870 AES_AU_WPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_au_wptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_au_wptr                     ;   	// 31: 0
	}le;
} AES_AU_WPTR;

/*-----------------------------------------------------------------------------
	0x0874 AES_AU_RPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_au_rptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_au_rptr                     ;   	// 31: 0
	}le;
} AES_AU_RPTR;

/*-----------------------------------------------------------------------------
	0x0878 AES_PTS32 ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :31;	// 31: 1
		UINT32		aes_pts32                       : 1;	//     0
	}be;
	struct {
		UINT32		aes_pts32                       : 1;	//     0
		UINT32		_rsvd_00                        :31;	// 31: 1
	}le;
} AES_PTS32;

/*-----------------------------------------------------------------------------
	0x087c AES_PTS31_0 ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_pts31_0                     ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_pts31_0                     ;   	// 31: 0
	}le;
} AES_PTS31_0;

/*-----------------------------------------------------------------------------
	0x0880 AES_SAMP_FREQ ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_samp_freq                   ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_samp_freq                   ;   	// 31: 0
	}le;
} AES_SAMP_FREQ;

/*-----------------------------------------------------------------------------
	0x0884 AES_FRAME_DURATION ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_frame_duration              ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_frame_duration              ;   	// 31: 0
	}le;
} AES_FRAME_DURATION;

/*-----------------------------------------------------------------------------
	0x0888 AES_CODEC_TYPE ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_codec_type                  ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_codec_type                  ;   	// 31: 0
	}le;
} AES_CODEC_TYPE;

/*-----------------------------------------------------------------------------
	0x088c AES_BIT_RATE ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_bit_rate                    ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_bit_rate                    ;   	// 31: 0
	}le;
} AES_BIT_RATE;

/*-----------------------------------------------------------------------------
	0x0890 AES_FRAME_SIZE ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		aes_frame_size                  ;   	// 31: 0
	}be;
	struct {
		UINT32		aes_frame_size                  ;   	// 31: 0
	}le;
} AES_FRAME_SIZE;

/*-----------------------------------------------------------------------------
	0x0894 VENC_RES_PIC ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        : 5;	// 31:27
		UINT32		width                           :11;	// 26:16
		UINT32		_rsvd_01                        : 5;	// 15:11
		UINT32		height                          :11;	// 10: 0
	}be;
	struct {
		UINT32		height                          :11;	// 10: 0
		UINT32		_rsvd_01                        : 5;	// 15:11
		UINT32		width                           :11;	// 26:16
		UINT32		_rsvd_00                        : 5;	// 31:27
	}le;
} VENC_RES_PIC;

/*-----------------------------------------------------------------------------
	0x0898 VENC_BSA_IBF ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		rd_base_input                   ;   	// 31: 0
	}be;
	struct {
		UINT32		rd_base_input                   ;   	// 31: 0
	}le;
} VENC_BSA_IBF;

/*-----------------------------------------------------------------------------
	0x089c VENC_EDA_IBF ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		rd_end_input                    ;   	// 31: 0
	}be;
	struct {
		UINT32		rd_end_input                    ;   	// 31: 0
	}le;
} VENC_EDA_IBF;

/*-----------------------------------------------------------------------------
	0x08a0 VENC_WIDX_IBF ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		wr_idx_input                    ;   	// 31: 0
	}be;
	struct {
		UINT32		wr_idx_input                    ;   	// 31: 0
	}le;
} VENC_WIDX_IBF;

/*-----------------------------------------------------------------------------
	0x08a4 VENC_RIDX_IBF ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		rd_idx_input                    ;   	// 31: 0
	}be;
	struct {
		UINT32		rd_idx_input                    ;   	// 31: 0
	}le;
} VENC_RIDX_IBF;

/*-----------------------------------------------------------------------------
	0x08a8 VENC_OFFSET_IBF ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		offset_picsz_input              ;   	// 31: 0
	}be;
	struct {
		UINT32		offset_picsz_input              ;   	// 31: 0
	}le;
} VENC_OFFSET_IBF;

/*-----------------------------------------------------------------------------
	0x08ac VENC_OFFSET2_IBF ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		hdr_sz_pic                      :16;	// 31:16
		UINT32		_rsvd_00                        : 5;	// 15:11
		UINT32		stride_pic                      :11;	// 10: 0
	}be;
	struct {
		UINT32		stride_pic                      :11;	// 10: 0
		UINT32		_rsvd_00                        : 5;	// 15:11
		UINT32		hdr_sz_pic                      :16;	// 31:16
	}le;
} VENC_OFFSET2_IBF;

/*-----------------------------------------------------------------------------
	0x08b0 THUMB_CTRL ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        : 4;	// 31:28
		UINT32		stride_in_thumbnail             :12;	// 27:16
		UINT32		_rsvd_01                        : 7;	// 15: 9
		UINT32		start                           : 1;	//     8
		UINT32		_rsvd_02                        : 3;	//  7: 5
		UINT32		sw_rst                          : 1;	//     4
		UINT32		lock_inactive                   : 1;	//     3
		UINT32		seperated_chrom_in              : 1;	//     2
		UINT32		progressive                     : 1;	//     1
		UINT32		path                            : 1;	//     0
	}be;
	struct {
		UINT32		path                            : 1;	//     0
		UINT32		progressive                     : 1;	//     1
		UINT32		seperated_chrom_in              : 1;	//     2
		UINT32		lock_inactive                   : 1;	//     3
		UINT32		sw_rst                          : 1;	//     4
		UINT32		_rsvd_02                        : 3;	//  7: 5
		UINT32		start                           : 1;	//     8
		UINT32		_rsvd_01                        : 7;	// 15: 9
		UINT32		stride_in_thumbnail             :12;	// 27:16
		UINT32		_rsvd_00                        : 4;	// 31:28
	}le;
} THUMB_CTRL;

/*-----------------------------------------------------------------------------
	0x08b4 THUMB_SZ_IN ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        : 5;	// 31:27
		UINT32		height                          :11;	// 26:16
		UINT32		_rsvd_01                        : 5;	// 15:11
		UINT32		width                           :11;	// 10: 0
	}be;
	struct {
		UINT32		width                           :11;	// 10: 0
		UINT32		_rsvd_01                        : 5;	// 15:11
		UINT32		height                          :11;	// 26:16
		UINT32		_rsvd_00                        : 5;	// 31:27
	}le;
} THUMB_SZ_IN;

/*-----------------------------------------------------------------------------
	0x08b8 THUMB_SZ_OUT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        : 5;	// 31:27
		UINT32		height                          :11;	// 26:16
		UINT32		_rsvd_01                        : 5;	// 15:11
		UINT32		width                           :11;	// 10: 0
	}be;
	struct {
		UINT32		width                           :11;	// 10: 0
		UINT32		_rsvd_01                        : 5;	// 15:11
		UINT32		height                          :11;	// 26:16
		UINT32		_rsvd_00                        : 5;	// 31:27
	}le;
} THUMB_SZ_OUT;

/*-----------------------------------------------------------------------------
	0x08bc THUMB_BSA_IN ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		in_base_addr                    ;   	// 31: 0
	}be;
	struct {
		UINT32		in_base_addr                    ;   	// 31: 0
	}le;
} THUMB_BSA_IN;

/*-----------------------------------------------------------------------------
	0x08c0 THUMB_BSA_OUT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		out_base_addr                   ;   	// 31: 0
	}be;
	struct {
		UINT32		out_base_addr                   ;   	// 31: 0
	}le;
} THUMB_BSA_OUT;

/*-----------------------------------------------------------------------------
	0x08c4 THUMB_BSA_IN_CH ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		in_base_addr_c                  ;   	// 31: 0
	}be;
	struct {
		UINT32		in_base_addr_c                  ;   	// 31: 0
	}le;
} THUMB_BSA_IN_CH;

/*-----------------------------------------------------------------------------
	0x08c8 TSDUMP_BASE_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		tsdump_base_addr                ;   	// 31: 0
	}be;
	struct {
		UINT32		tsdump_base_addr                ;   	// 31: 0
	}le;
} TSDUMP_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x08cc TSDUMP_END_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		tsdump_end_addr                 ;   	// 31: 0
	}be;
	struct {
		UINT32		tsdump_end_addr                 ;   	// 31: 0
	}le;
} TSDUMP_END_ADDR;

/*-----------------------------------------------------------------------------
	0x08d0 VAUI_BSA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		vaui_base_addr                  ;   	// 31: 0
	}be;
	struct {
		UINT32		vaui_base_addr                  ;   	// 31: 0
	}le;
} VAUI_BSA;

/*-----------------------------------------------------------------------------
	0x08d4 VAUI_EDA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		vaui_end_addr                   ;   	// 31: 0
	}be;
	struct {
		UINT32		vaui_end_addr                   ;   	// 31: 0
	}le;
} VAUI_EDA;

/*-----------------------------------------------------------------------------
	0x08d8 VENC_GAUGE ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		slice_counter                   :16;	// 31:16
		UINT32		slice_encoding_msec             :16;	// 15: 0
	}be;
	struct {
		UINT32		slice_encoding_msec             :16;	// 15: 0
		UINT32		slice_counter                   :16;	// 31:16
	}le;
} VENC_GAUGE;

/*-----------------------------------------------------------------------------
	0x08dc VENC_EXT_ESWPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ext_esw_ptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		ext_esw_ptr                     ;   	// 31: 0
	}le;
} VENC_EXT_ESWPTR;

/*-----------------------------------------------------------------------------
	0x08e0 VENC_EXT_ESRPTR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		ext_esr_ptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		ext_esr_ptr                     ;   	// 31: 0
	}le;
} VENC_EXT_ESRPTR;

/*-----------------------------------------------------------------------------
	0x08e4 VENC_CTRL ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :28;	// 31: 4
		UINT32		enc_ctrl                        : 4;	//  3: 0
	}be;
	struct {
		UINT32		enc_ctrl                        : 4;	//  3: 0
		UINT32		_rsvd_00                        :28;	// 31: 4
	}le;
} VENC_CTRL;

/*-----------------------------------------------------------------------------
	0x08e8 VES_BSA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		es_base_addr                    ;   	// 31: 0
	}be;
	struct {
		UINT32		es_base_addr                    ;   	// 31: 0
	}le;
} VES_BSA;

/*-----------------------------------------------------------------------------
	0x08ec VES_EDA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		es_end_addr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		es_end_addr                     ;   	// 31: 0
	}le;
} VES_EDA;

/*-----------------------------------------------------------------------------
	0x08f0 VENC_INT_ESWPRT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		int_esw_ptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		int_esw_ptr                     ;   	// 31: 0
	}le;
} VENC_INT_ESWPRT;

/*-----------------------------------------------------------------------------
	0x08f4 VENC_INT_ESRPRT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		int_esr_ptr                     ;   	// 31: 0
	}be;
	struct {
		UINT32		int_esr_ptr                     ;   	// 31: 0
	}le;
} VENC_INT_ESRPRT;

/*-----------------------------------------------------------------------------
	0x08f8 TSDUMP_WR_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		tsdump_wr_addr                  ;   	// 31: 0
	}be;
	struct {
		UINT32		tsdump_wr_addr                  ;   	// 31: 0
	}le;
} TSDUMP_WR_ADDR;

/*-----------------------------------------------------------------------------
	0x08fc TSDUMP_RD_ADDR ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		tsdump_rd_addr                  ;   	// 31: 0
	}be;
	struct {
		UINT32		tsdump_rd_addr                  ;   	// 31: 0
	}le;
} TSDUMP_RD_ADDR;


typedef struct {
	SW_VERSION                      	sw_version                      ;	// 0x0800 : ''
	UINT32                          	             _rsvd_addr_06[   2];	// 0x0804 ~ 0x0808
	VENC_CONFIG0						venc_config0					;	// 0x080c : ''
	VENC_MODE_IN                    	venc_mode_in                    ;	// 0x0810 : ''
	VENC_MODE2_IN                   	venc_mode2_in                   ;	// 0x0814 : ''
	VENC_FRAME_BA                   	venc_frame_ba                   ;	// 0x0818 : ''
	VENC_DPB_BA                     	venc_dpb_ba                     ;	// 0x081c : ''
	THUMBNAIL_BA                    	thumbnail_ba                    ;	// 0x0820 : ''
	RD_CTRL								rd_ctrl							;	// 0x0824 ; ''

	/*{{{ Interrupt control registers */
	EXT_IPC_STATE                   	ext_ipc_state                   ;	// 0x0828 : ''
	INT_IPC_STATE                   	int_ipc_state                   ;	// 0x082c : ''
	/*}}}*/

	/*{{{ SENC control registers - 0x830 ~ 0x890 */
	SENC_CTRL                       	senc_ctrl                       ;	// 0x0830 : ''
	TS_CNT                          	ts_cnt                          ;	// 0x0834 : ''
	V_TS_CNT                        	v_ts_cnt                        ;	// 0x0838 : ''
	A_TS_CNT                        	a_ts_cnt                        ;	// 0x083c : ''
	VES_AUI_WPTR                    	ves_aui_wptr                    ;	// 0x0840 : ''
	VES_AUI_RPTR                    	ves_aui_rptr                    ;	// 0x0844 : ''
	VES_AU_WPTR                     	ves_au_wptr                     ;	// 0x0848 : ''
	VES_AU_RPTR                     	ves_au_rptr                     ;	// 0x084c : ''
	AES_BASE_ADDR                   	aes_base_addr                   ;	// 0x0850 : ''
	AES_END_ADDR                    	aes_end_addr                    ;	// 0x0854 : ''
	AAUI_BASE_ADDR                  	aaui_base_addr                  ;	// 0x0858 : ''
	AAUI_END_ADDR                   	aaui_end_addr                   ;	// 0x085c : ''
	VES_BUF_STAT                    	ves_buf_stat                    ;	// 0x0860 : ''
	AES_DTS_OFFSET                  	aes_dts_offset                  ;	// 0x0864 : ''
	AES_AUI_WPTR                    	aes_aui_wptr                    ;	// 0x0868 : ''
	AES_AUI_RPTR                    	aes_aui_rptr                    ;	// 0x086c : ''
	AES_AU_WPTR                     	aes_au_wptr                     ;	// 0x0870 : ''
	AES_AU_RPTR                     	aes_au_rptr                     ;	// 0x0874 : ''
	AES_PTS32                       	aes_pts32                       ;	// 0x0878 : ''
	AES_PTS31_0                     	aes_pts31_0                     ;	// 0x087c : ''
	AES_SAMP_FREQ                   	aes_samp_freq                   ;	// 0x0880 : ''
	AES_FRAME_DURATION              	aes_frame_duration              ;	// 0x0884 : ''
	AES_CODEC_TYPE                  	aes_codec_type                  ;	// 0x0888 : ''
	AES_BIT_RATE                    	aes_bit_rate                    ;	// 0x088c : ''
	AES_FRAME_SIZE                  	aes_frame_size                  ;	// 0x0890 : ''
	/*}}}*/

	VENC_RES_PIC                    	venc_res_pic                    ;	// 0x0894 : ''
	VENC_BSA_IBF                    	venc_bsa_ibf                    ;	// 0x0898 : ''
	VENC_EDA_IBF                    	venc_eda_ibf                    ;	// 0x089c : ''
	VENC_WIDX_IBF                   	venc_widx_ibf                   ;	// 0x08a0 : ''
	VENC_RIDX_IBF                   	venc_ridx_ibf                   ;	// 0x08a4 : ''
	VENC_OFFSET_IBF                 	venc_offset_ibf                 ;	// 0x08a8 : ''
	VENC_OFFSET2_IBF                	venc_offset2_ibf                ;	// 0x08ac : ''
	THUMB_CTRL                      	thumb_ctrl                      ;	// 0x08b0 : ''
	THUMB_SZ_IN                     	thumb_sz_in                     ;	// 0x08b4 : ''
	THUMB_SZ_OUT                    	thumb_sz_out                    ;	// 0x08b8 : ''
	THUMB_BSA_IN                    	thumb_bsa_in                    ;	// 0x08bc : ''
	THUMB_BSA_OUT                   	thumb_bsa_out                   ;	// 0x08c0 : ''
	THUMB_BSA_IN_CH                 	thumb_bsa_in_ch                 ;	// 0x08c4 : ''
	TSDUMP_BASE_ADDR                  	tsdump_base_addr                ;	// 0x08c8 : ''
	TSDUMP_END_ADDR                    	tsdump_end_addr                 ;	// 0x08cc : ''
	VAUI_BSA                        	vaui_bsa                        ;	// 0x08d0 : ''
	VAUI_EDA                        	vaui_eda                        ;	// 0x08d4 : ''
	VENC_GAUGE                      	venc_gauge                      ;	// 0x08d8 : ''
	VENC_EXT_ESWPTR                 	venc_ext_eswptr                 ;	// 0x08dc : ''
	VENC_EXT_ESRPTR                 	venc_ext_esrptr                 ;	// 0x08e0 : ''
	VENC_CTRL                       	venc_ctrl                       ;	// 0x08e4 : ''
	VES_BSA                         	ves_bsa                         ;	// 0x08e8 : ''
	VES_EDA                         	ves_eda                         ;	// 0x08ec : ''
	VENC_INT_ESWPRT                 	venc_int_eswprt                 ;	// 0x08f0 : ''
	VENC_INT_ESRPRT                 	venc_int_esrprt                 ;	// 0x08f4 : ''
	TSDUMP_WR_ADDR                      tsdump_wr_addr					;	// 0x08f8 ; ''
	TSDUMP_RD_ADDR                      tsdump_rd_addr					;	// 0x08fc ; ''
//	UINT32                          	             _rsvd_addr_08[   2];	// 0x08f8 ~ 0x08fc
} VENC_L9_REG_IPC_T;

/******************************************************************************
 * Exported variables
 ******************************************************************************/
extern volatile VENC_L9_REG_IPC_T *gpVencL9IpcReg;


#endif	/* !_REG_VENC_L9_IPC_h */

