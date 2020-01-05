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

#ifndef _REG_VDI_L9A0_h
#define _REG_VDI_L9A0_h

typedef struct { // 0x4d00
	UINT32 frame_index         : 8;   //  7: 0
} L9A0_VDI_FRAME_INX_T;

typedef struct { // 0x4d04
	UINT32 display_type        : 2;   //  1: 0
} L9A0_VDI_PIC_INFO_T;

typedef struct { // 0x4d08
	UINT32 framerateresidual   : 16;  // 15: 0
	UINT32 frameratedivminus1  : 16;  // 31:16
} L9A0_VDI_FRAME_RATE_T;

typedef struct { // 0x4d0c
	UINT32 aspect_ratio        : 4;   //  3: 0
} L9A0_VDI_ASPECT_RATIO_T;

typedef struct { // 0x4d10
	UINT32 height              : 16;  // 15: 0
	UINT32 width               : 16;  // 31:16
} L9A0_VDI_PICTURE_SIZE_T;

typedef struct { // 0x4d14
	UINT32 right_offset        : 16;  // 15: 0
	UINT32 left_offset         : 16;  // 31:16
} L9A0_VDI_H_OFFSET_T;

typedef struct { // 0x4d18
	UINT32 bottom_offset       : 16;  // 15: 0
	UINT32 top_offset          : 16;  // 31:16
} L9A0_VDI_V_OFFSET_T;

typedef struct { // 0x4d1c
	UINT32 updated             : 1;   //     0
} L9A0_VDI_FRAMEUPDATED_T;

typedef struct { // 0x4d20
	UINT32 start_addr          : 12;  // 11: 0
	UINT32 base_addr           : 20;  // 31:12
} L9A0_VDI_Y_FRAME_BASE_ADDRESS_T;

typedef struct { // 0x4d24
	UINT32 start_addr          : 12;  // 11: 0
	UINT32 base_addr           : 20;  // 31:12
} L9A0_VDI_C_FRAME_BASE_ADDRESS_T;

typedef struct { // 0x4d28
	UINT32 frame_offset        : 32;  // 31: 0
} L9A0_VDI_Y_FRAME_OFFSET_T;

typedef struct { // 0x4d2c
	UINT32 frame_offset        : 32;  // 31: 0
} L9A0_VDI_C_FRAME_OFFSET_T;

typedef struct { // 0x4d30
	UINT32 stride              : 16;  // 15: 0
} L9A0_VDI_STRIDE_T;

typedef struct { // 0x4d34
	UINT32 userdatabaseaddr    : 32;  // 31: 0
} L9A0_VDI_USERDATABASEADDR_T;

typedef struct {
	L9A0_VDI_FRAME_INX_T                vdi_frame_inx;                       // 0x4d00
	L9A0_VDI_PIC_INFO_T                 vdi_pic_info;                        // 0x4d04
	L9A0_VDI_FRAME_RATE_T               vdi_frame_rate;                      // 0x4d08
	L9A0_VDI_ASPECT_RATIO_T             vdi_aspect_ratio;                    // 0x4d0c
	L9A0_VDI_PICTURE_SIZE_T             vdi_picture_size;                    // 0x4d10
	L9A0_VDI_H_OFFSET_T                 vdi_h_offset;                        // 0x4d14
	L9A0_VDI_V_OFFSET_T                 vdi_v_offset;                        // 0x4d18
	L9A0_VDI_FRAMEUPDATED_T             vdi_frameupdated;                    // 0x4d1c
	L9A0_VDI_Y_FRAME_BASE_ADDRESS_T     vdi_y_frame_base_address;            // 0x4d20
	L9A0_VDI_C_FRAME_BASE_ADDRESS_T     vdi_c_frame_base_address;            // 0x4d24
	L9A0_VDI_Y_FRAME_OFFSET_T           vdi_y_frame_offset;                  // 0x4d28
	L9A0_VDI_C_FRAME_OFFSET_T           vdi_c_frame_offset;                  // 0x4d2c
	L9A0_VDI_STRIDE_T                   vdi_stride;                          // 0x4d30
	L9A0_VDI_USERDATABASEADDR_T         vdi_userdatabaseaddr;                // 0x4d34
} DE_VDI_REG_L9A0_T;

#endif
