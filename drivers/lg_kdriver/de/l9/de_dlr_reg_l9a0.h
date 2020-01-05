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

#ifndef _REG_DLR_L9A0_h
#define _REG_DLR_L9A0_h

typedef struct { // 0x0300
	UINT32 in_image_format     : 3;   //  2: 0
	UINT32                     : 1;   //     3
	UINT32 color_format        : 2;   //  5: 4
	UINT32                     : 2;   //  7: 6
	UINT32 lr_in_order         : 1;   //     8
	UINT32                     : 3;   // 11: 9
	UINT32 progressive         : 1;   //    12
	UINT32                     : 3;   // 15:13
	UINT32 sample_comb         : 2;   // 17:16
} L9A0_DLR_IN_IMG_FORMAT_T;

typedef struct { // 0x0304
	UINT32 one_frame_height    : 12;  // 11: 0
	UINT32                     : 4;   // 15:12
	UINT32 active_blank        : 12;  // 27:16
	UINT32 fp_interlace        : 1;   //    28
} L9A0_DLR_FRAME_PACK_INFO_T;

typedef struct { // 0x0308
	UINT32 quincunx_coeff0     : 32;  // 31: 0
} L9A0_DLR_QUINCUNX_COEFF0_T;

typedef struct { // 0x030c
	UINT32 quincunx_coeff1     : 32;  // 31: 0
} L9A0_DLR_QUINCUNX_COEFF1_T;

typedef struct { // 0x0310
	UINT32 quincunx_coeff2     : 32;  // 31: 0
} L9A0_DLR_QUINCUNX_COEFF2_T;

typedef struct { // 0x0314
	UINT32 quincunx_coeff3     : 32;  // 31: 0
} L9A0_DLR_QUINCUNX_COEFF3_T;

typedef struct { // 0x0318
	UINT32 quincunx_coeff4     : 32;  // 31: 0
} L9A0_DLR_QUINCUNX_COEFF4_T;

typedef struct { // 0x031c
	UINT32 quincunx_coeff5     : 32;  // 31: 0
} L9A0_DLR_QUINCUNX_COEFF5_T;

typedef struct { // 0x0320
	UINT32 quincunx_coeff6     : 32;  // 31: 0
} L9A0_DLR_QUINCUNX_COEFF6_T;

typedef struct { // 0x0324
	UINT32 status              : 4;   //  3: 0
	UINT32                     : 4;   //  7: 4
	UINT32 luma_line_counts    : 12;  // 19: 8
	UINT32 chroma_line_counts  : 12;  // 31:20
} L9A0_DLR_STATUS_T;

typedef struct { // 0x0328
	UINT32 debugmode_en        : 1;   //     0
	UINT32                     : 3;   //  3: 1
	UINT32 qx_repetition       : 1;   //     4
} L9A0_DLR_DEBUG_MODE_T;

typedef struct {
	L9A0_DLR_IN_IMG_FORMAT_T    dlr_in_img_format;           // 0x0300
	L9A0_DLR_FRAME_PACK_INFO_T  dlr_frame_pack_info;         // 0x0304
	L9A0_DLR_QUINCUNX_COEFF0_T  dlr_quincunx_coeff0;         // 0x0308
	L9A0_DLR_QUINCUNX_COEFF1_T  dlr_quincunx_coeff1;         // 0x030c
	L9A0_DLR_QUINCUNX_COEFF2_T  dlr_quincunx_coeff2;         // 0x0310
	L9A0_DLR_QUINCUNX_COEFF3_T  dlr_quincunx_coeff3;         // 0x0314
	L9A0_DLR_QUINCUNX_COEFF4_T  dlr_quincunx_coeff4;         // 0x0318
	L9A0_DLR_QUINCUNX_COEFF5_T  dlr_quincunx_coeff5;         // 0x031c
	L9A0_DLR_QUINCUNX_COEFF6_T  dlr_quincunx_coeff6;         // 0x0320
	L9A0_DLR_STATUS_T           dlr_status;                  // 0x0324
	L9A0_DLR_DEBUG_MODE_T       dlr_debug_mode;              // 0x0328
} DE_DLR_REG_L9A0_T;

#endif
