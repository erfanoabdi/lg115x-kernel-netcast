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

#ifndef _REG_DVR_L9A0_h
#define _REG_DVR_L9A0_h

typedef struct { // 0x5400
	UINT32 de_status           : 3;   //  2: 0
	UINT32                     : 1;   //     3
	UINT32 ctrl_mode           : 1;   //     4
	UINT32                     : 11;  // 15: 5
	UINT32 rd_indx             : 2;   // 17:16
	UINT32 de_info             : 14;  // 31:18
} L9A0_DVR_STATUS_T;

typedef struct { // 0x5404
	UINT32 vsize               : 12;  // 11: 0
	UINT32                     : 4;   // 15:12
	UINT32 hsize               : 12;  // 27:16
} L9A0_DVR_DSIZE_T;

typedef struct { // 0x5408
	UINT32 vsize               : 12;  // 11: 0
	UINT32                     : 4;   // 15:12
	UINT32 hsize               : 12;  // 27:16
} L9A0_DVR_DECSIZE_T;

typedef struct { // 0x540c
	UINT32 roffset             : 12;  // 11: 0
	UINT32                     : 4;   // 15:12
	UINT32 loffset             : 12;  // 27:16
} L9A0_DVR_HOFFSET_T;

typedef struct { // 0x5410
	UINT32 boffset             : 12;  // 11: 0
	UINT32                     : 4;   // 15:12
	UINT32 toffset             : 12;  // 27:16
} L9A0_DVR_VOFFSET_T;

typedef struct { // 0x5414
	UINT32 aspect_ratio        : 5;   //  4: 0
	UINT32                     : 11;  // 15: 5
	UINT32 prog_seq            : 1;   //    16
	UINT32                     : 11;  // 27:17
	UINT32 frame_rate          : 4;   // 31:28
} L9A0_DVR_SEQINFO_T;

typedef struct { // 0x5418
	UINT32 prog_frame          : 1;   //     0
	UINT32                     : 3;   //  3: 1
	UINT32 topfield_first      : 1;   //     4
	UINT32 repeat_firstfield   : 1;   //     5
	UINT32 frame_struct        : 2;   //  7: 6
	UINT32 frame_ptr           : 8;   // 15: 8
	UINT32 clr_info            : 16;  // 31:16
} L9A0_DVR_PICINFO_T;

typedef struct { // 0x5420
	UINT32 y_addr              : 32;  // 31: 0
} L9A0_DVR_Y_ADDR_T;

typedef struct { // 0x5424
	UINT32 y_stride            : 12;  // 11: 0
} L9A0_DVR_Y_STRIDE_T;

typedef struct { // 0x5428
	UINT32 c_addr              : 32;  // 31: 0
} L9A0_DVR_C_ADDR_T;

typedef struct { // 0x542c
	UINT32 c_stride            : 12;  // 11: 0
} L9A0_DVR_C_STRIDE_T;

typedef struct {
	L9A0_DVR_STATUS_T       dvr_status;              // 0x5400
	L9A0_DVR_DSIZE_T        dvr_dsize;               // 0x5404
	L9A0_DVR_DECSIZE_T      dvr_decsize;             // 0x5408
	L9A0_DVR_HOFFSET_T      dvr_hoffset;             // 0x540c
	L9A0_DVR_VOFFSET_T      dvr_voffset;             // 0x5410
	L9A0_DVR_SEQINFO_T      dvr_seqinfo;             // 0x5414
	L9A0_DVR_PICINFO_T      dvr_picinfo;             // 0x5418
	UINT32                  reserved0;               // 0x541c
	L9A0_DVR_Y_ADDR_T       dvr_y_addr;              // 0x5420
	L9A0_DVR_Y_STRIDE_T     dvr_y_stride;            // 0x5424
	L9A0_DVR_C_ADDR_T       dvr_c_addr;              // 0x5428
	L9A0_DVR_C_STRIDE_T     dvr_c_stride;            // 0x542c
} DE_DVR_REG_L9A0_T;

#endif
