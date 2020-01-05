/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/

/*
 *
 *  CPU TOP Control register details. ( used only within kdriver )
 *
 *  author     ks.hyun (ks.hyun@lge.com)
 *  version    1.0
 *  date       2012.05.02
 *
 */

#ifndef __CPU_TOP_REG_H13A0_H__
#define __CPU_TOP_REG_H13A0_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	0x0000 gp_reg0 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0004 gp_reg1 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0008 gp_reg2 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x000c gp_reg3 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0010 cpu0_addr_sw_reg_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	cpu0_paddr_app_nor_boot         : 6,	// 10:15
	                                :12,	// 16:27 reserved
	cpu0_laddr_app_nor_boot         : 4;	// 28:31
} CPU0_ADDR_SW_REG_0_H13A0;

/*-----------------------------------------------------------------------------
	0x0014 cpu0_addr_sw_reg_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cpu0_paddr_app_rom_boot         :16,	//  0:15
	                                : 2,	// 16:17 reserved
	cpu0_laddr_app_rom_boot         :14;	// 18:31
} CPU0_ADDR_SW_REG_1_H13A0;

/*-----------------------------------------------------------------------------
	0x0018 cpu0_addr_sw_reg_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cpu0_paddr_app_gpu_host         : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	cpu0_laddr_app_gpu_host         : 4,	// 12:15
	                                : 2,	// 16:17 reserved
	cpu0_paddr_app_shadow           : 6,	// 18:23
	                                : 4,	// 24:27 reserved
	cpu0_laddr_app_shadow           : 4;	// 28:31
} CPU0_ADDR_SW_REG_2_H13A0;

/*-----------------------------------------------------------------------------
	0x001c cpu0_addr_sw_reg_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset0                    : 8,	//  8:15
	cpu0_leaddr0                    : 8,	// 16:23
	cpu0_lsaddr0                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_3_H13A0;

/*-----------------------------------------------------------------------------
	0x0020 cpu0_addr_sw_reg_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset1                    : 8,	//  8:15
	cpu0_leaddr1                    : 8,	// 16:23
	cpu0_lsaddr1                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_4_H13A0;

/*-----------------------------------------------------------------------------
	0x0024 cpu0_addr_sw_reg_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset2                    : 8,	//  8:15
	cpu0_leaddr2                    : 8,	// 16:23
	cpu0_lsaddr2                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_5_H13A0;

/*-----------------------------------------------------------------------------
	0x0028 cpu0_addr_sw_reg_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset3                    : 8,	//  8:15
	cpu0_leaddr3                    : 8,	// 16:23
	cpu0_lsaddr3                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_6_H13A0;

/*-----------------------------------------------------------------------------
	0x002c cpu0_addr_sw_reg_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset4                    : 8,	//  8:15
	cpu0_leaddr4                    : 8,	// 16:23
	cpu0_lsaddr4                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_7_H13A0;

/*-----------------------------------------------------------------------------
	0x0030 cpu0_addr_sw_reg_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset5                    : 8,	//  8:15
	cpu0_leaddr5                    : 8,	// 16:23
	cpu0_lsaddr5                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_8_H13A0;

/*-----------------------------------------------------------------------------
	0x0034 cpu0_addr_sw_reg_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset6                    : 8,	//  8:15
	cpu0_leaddr6                    : 8,	// 16:23
	cpu0_lsaddr6                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_9_H13A0;

/*-----------------------------------------------------------------------------
	0x0038 cpu0_addr_sw_reg_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu0_offset7                    : 8,	//  8:15
	cpu0_leaddr7                    : 8,	// 16:23
	cpu0_lsaddr7                    : 8;	// 24:31
} CPU0_ADDR_SW_REG_10_H13A0;

/*-----------------------------------------------------------------------------
	0x003c cpu1_addr_sw_reg_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	cpu1_paddr_app_nor_boot         : 6,	// 10:15
	                                :12,	// 16:27 reserved
	cpu1_laddr_app_nor_boot         : 4;	// 28:31
} CPU1_ADDR_SW_REG_0_H13A0;

/*-----------------------------------------------------------------------------
	0x0040 cpu1_addr_sw_reg_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cpu1_paddr_app_rom_boot         :16,	//  0:15
	                                : 2,	// 16:17 reserved
	cpu1_laddr_app_rom_boot         :14;	// 18:31
} CPU1_ADDR_SW_REG_1_H13A0;

/*-----------------------------------------------------------------------------
	0x0044 cpu1_addr_sw_reg_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cpu1_paddr_app_gpu_host         : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	cpu1_laddr_app_gpu_host         : 4,	// 12:15
	                                : 2,	// 16:17 reserved
	cpu1_paddr_app_shadow           : 6,	// 18:23
	                                : 4,	// 24:27 reserved
	cpu1_laddr_app_shadow           : 4;	// 28:31
} CPU1_ADDR_SW_REG_2_H13A0;

/*-----------------------------------------------------------------------------
	0x0048 cpu1_addr_sw_reg_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset0                    : 8,	//  8:15
	cpu1_leaddr0                    : 8,	// 16:23
	cpu1_lsaddr0                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_3_H13A0;

/*-----------------------------------------------------------------------------
	0x004c cpu1_addr_sw_reg_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset1                    : 8,	//  8:15
	cpu1_leaddr1                    : 8,	// 16:23
	cpu1_lsaddr1                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_4_H13A0;

/*-----------------------------------------------------------------------------
	0x0050 cpu1_addr_sw_reg_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset2                    : 8,	//  8:15
	cpu1_leaddr2                    : 8,	// 16:23
	cpu1_lsaddr2                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_5_H13A0;

/*-----------------------------------------------------------------------------
	0x0054 cpu1_addr_sw_reg_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset3                    : 8,	//  8:15
	cpu1_leaddr3                    : 8,	// 16:23
	cpu1_lsaddr3                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_6_H13A0;

/*-----------------------------------------------------------------------------
	0x0058 cpu1_addr_sw_reg_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset4                    : 8,	//  8:15
	cpu1_leaddr4                    : 8,	// 16:23
	cpu1_lsaddr4                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_7_H13A0;

/*-----------------------------------------------------------------------------
	0x005c cpu1_addr_sw_reg_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset5                    : 8,	//  8:15
	cpu1_leaddr5                    : 8,	// 16:23
	cpu1_lsaddr5                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_8_H13A0;

/*-----------------------------------------------------------------------------
	0x0060 cpu1_addr_sw_reg_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset6                    : 8,	//  8:15
	cpu1_leaddr6                    : 8,	// 16:23
	cpu1_lsaddr6                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_9_H13A0;

/*-----------------------------------------------------------------------------
	0x0064 cpu1_addr_sw_reg_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	cpu1_offset7                    : 8,	//  8:15
	cpu1_leaddr7                    : 8,	// 16:23
	cpu1_lsaddr7                    : 8;	// 24:31
} CPU1_ADDR_SW_REG_10_H13A0;

/*-----------------------------------------------------------------------------
	0x0068 peri0_addr_sw_reg_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	peri0_paddr_app_nor_boot        : 6,	// 10:15
	                                :12,	// 16:27 reserved
	peri0_laddr_app_nor_boot        : 4;	// 28:31
} PERI0_ADDR_SW_REG_0_H13A0;

/*-----------------------------------------------------------------------------
	0x006c peri0_addr_sw_reg_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	peri0_paddr_app_rom_boot        :16,	//  0:15
	                                : 2,	// 16:17 reserved
	peri0_laddr_app_rom_boot        :14;	// 18:31
} PERI0_ADDR_SW_REG_1_H13A0;

/*-----------------------------------------------------------------------------
	0x0070 peri0_addr_sw_reg_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	peri0_paddr_app_gpu_host        : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	peri0_laddr_app_gpu_host        : 4,	// 12:15
	                                : 2,	// 16:17 reserved
	peri0_paddr_app_shadow          : 6,	// 18:23
	                                : 4,	// 24:27 reserved
	peri0_laddr_app_shadow          : 4;	// 28:31
} PERI0_ADDR_SW_REG_2_H13A0;

/*-----------------------------------------------------------------------------
	0x0074 peri0_addr_sw_reg_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset0                   : 8,	//  8:15
	peri0_leaddr0                   : 8,	// 16:23
	peri0_lsaddr0                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_3_H13A0;

/*-----------------------------------------------------------------------------
	0x0078 peri0_addr_sw_reg_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset1                   : 8,	//  8:15
	peri0_leaddr1                   : 8,	// 16:23
	peri0_lsaddr1                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_4_H13A0;

/*-----------------------------------------------------------------------------
	0x007c peri0_addr_sw_reg_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset2                   : 8,	//  8:15
	peri0_leaddr2                   : 8,	// 16:23
	peri0_lsaddr2                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_5_H13A0;

/*-----------------------------------------------------------------------------
	0x0080 peri0_addr_sw_reg_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset3                   : 8,	//  8:15
	peri0_leaddr3                   : 8,	// 16:23
	peri0_lsaddr3                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_6_H13A0;

/*-----------------------------------------------------------------------------
	0x0084 peri0_addr_sw_reg_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset4                   : 8,	//  8:15
	peri0_leaddr4                   : 8,	// 16:23
	peri0_lsaddr4                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_7_H13A0;

/*-----------------------------------------------------------------------------
	0x0088 peri0_addr_sw_reg_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset5                   : 8,	//  8:15
	peri0_leaddr5                   : 8,	// 16:23
	peri0_lsaddr5                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_8_H13A0;

/*-----------------------------------------------------------------------------
	0x008c peri0_addr_sw_reg_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset6                   : 8,	//  8:15
	peri0_leaddr6                   : 8,	// 16:23
	peri0_lsaddr6                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_9_H13A0;

/*-----------------------------------------------------------------------------
	0x0090 peri0_addr_sw_reg_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri0_offset7                   : 8,	//  8:15
	peri0_leaddr7                   : 8,	// 16:23
	peri0_lsaddr7                   : 8;	// 24:31
} PERI0_ADDR_SW_REG_10_H13A0;

/*-----------------------------------------------------------------------------
	0x0094 peri1_addr_sw_reg_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	peri1_paddr_app_nor_boot        : 6,	// 10:15
	                                :12,	// 16:27 reserved
	peri1_laddr_app_nor_boot        : 4;	// 28:31
} PERI1_ADDR_SW_REG_0_H13A0;

/*-----------------------------------------------------------------------------
	0x0098 peri1_addr_sw_reg_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	peri1_paddr_app_rom_boot        :16,	//  0:15
	                                : 2,	// 16:17 reserved
	peri1_laddr_app_rom_boot        :14;	// 18:31
} PERI1_ADDR_SW_REG_1_H13A0;

/*-----------------------------------------------------------------------------
	0x009c peri1_addr_sw_reg_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	peri1_paddr_app_gpu_host        : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	peri1_laddr_app_gpu_host        : 4,	// 12:15
	                                : 2,	// 16:17 reserved
	peri1_paddr_app_shadow          : 6,	// 18:23
	                                : 4,	// 24:27 reserved
	peri1_laddr_app_shadow          : 4;	// 28:31
} PERI1_ADDR_SW_REG_2_H13A0;

/*-----------------------------------------------------------------------------
	0x00a0 peri1_addr_sw_reg_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset0                   : 8,	//  8:15
	peri1_leaddr0                   : 8,	// 16:23
	peri1_lsaddr0                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_3_H13A0;

/*-----------------------------------------------------------------------------
	0x00a4 peri1_addr_sw_reg_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset1                   : 8,	//  8:15
	peri1_leaddr1                   : 8,	// 16:23
	peri1_lsaddr1                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_4_H13A0;

/*-----------------------------------------------------------------------------
	0x00a8 peri1_addr_sw_reg_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset2                   : 8,	//  8:15
	peri1_leaddr2                   : 8,	// 16:23
	peri1_lsaddr2                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_5_H13A0;

/*-----------------------------------------------------------------------------
	0x00ac peri1_addr_sw_reg_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset3                   : 8,	//  8:15
	peri1_leaddr3                   : 8,	// 16:23
	peri1_lsaddr3                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_6_H13A0;

/*-----------------------------------------------------------------------------
	0x00b0 peri1_addr_sw_reg_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset4                   : 8,	//  8:15
	peri1_leaddr4                   : 8,	// 16:23
	peri1_lsaddr4                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_7_H13A0;

/*-----------------------------------------------------------------------------
	0x00b4 peri1_addr_sw_reg_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset5                   : 8,	//  8:15
	peri1_leaddr5                   : 8,	// 16:23
	peri1_lsaddr5                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_8_H13A0;

/*-----------------------------------------------------------------------------
	0x00b8 peri1_addr_sw_reg_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset6                   : 8,	//  8:15
	peri1_leaddr6                   : 8,	// 16:23
	peri1_lsaddr6                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_9_H13A0;

/*-----------------------------------------------------------------------------
	0x00bc peri1_addr_sw_reg_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	peri1_offset7                   : 8,	//  8:15
	peri1_leaddr7                   : 8,	// 16:23
	peri1_lsaddr7                   : 8;	// 24:31
} PERI1_ADDR_SW_REG_10_H13A0;

/*-----------------------------------------------------------------------------
	0x00c0 isol_addr_sw_reg_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	isol_paddr_app_nor_boot         : 6,	// 10:15
	                                :12,	// 16:27 reserved
	isol_laddr_app_nor_boot         : 4;	// 28:31
} ISOL_ADDR_SW_REG_0_H13A0;

/*-----------------------------------------------------------------------------
	0x00c4 isol_addr_sw_reg_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	isol_paddr_app_rom_boot         :16,	//  0:15
	                                : 2,	// 16:17 reserved
	isol_laddr_app_rom_boot         :14;	// 18:31
} ISOL_ADDR_SW_REG_1_H13A0;

/*-----------------------------------------------------------------------------
	0x00c8 isol_addr_sw_reg_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	isol_paddr_app_gpu_host         : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	isol_laddr_app_gpu_host         : 4,	// 12:15
	                                : 2,	// 16:17 reserved
	isol_paddr_app_shadow           : 6,	// 18:23
	                                : 4,	// 24:27 reserved
	isol_laddr_app_shadow           : 4;	// 28:31
} ISOL_ADDR_SW_REG_2_H13A0;

/*-----------------------------------------------------------------------------
	0x00cc isol_addr_sw_reg_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset0                    : 8,	//  8:15
	isol_leaddr0                    : 8,	// 16:23
	isol_lsaddr0                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_3_H13A0;

/*-----------------------------------------------------------------------------
	0x00d0 isol_addr_sw_reg_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset1                    : 8,	//  8:15
	isol_leaddr1                    : 8,	// 16:23
	isol_lsaddr1                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_4_H13A0;

/*-----------------------------------------------------------------------------
	0x00d4 isol_addr_sw_reg_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset2                    : 8,	//  8:15
	isol_leaddr2                    : 8,	// 16:23
	isol_lsaddr2                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_5_H13A0;

/*-----------------------------------------------------------------------------
	0x00d8 isol_addr_sw_reg_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset3                    : 8,	//  8:15
	isol_leaddr3                    : 8,	// 16:23
	isol_lsaddr3                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_6_H13A0;

/*-----------------------------------------------------------------------------
	0x00dc isol_addr_sw_reg_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset4                    : 8,	//  8:15
	isol_leaddr4                    : 8,	// 16:23
	isol_lsaddr4                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_7_H13A0;

/*-----------------------------------------------------------------------------
	0x00e0 isol_addr_sw_reg_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset5                    : 8,	//  8:15
	isol_leaddr5                    : 8,	// 16:23
	isol_lsaddr5                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_8_H13A0;

/*-----------------------------------------------------------------------------
	0x00e4 isol_addr_sw_reg_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset6                    : 8,	//  8:15
	isol_leaddr6                    : 8,	// 16:23
	isol_lsaddr6                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_9_H13A0;

/*-----------------------------------------------------------------------------
	0x00e8 isol_addr_sw_reg_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	isol_offset7                    : 8,	//  8:15
	isol_leaddr7                    : 8,	// 16:23
	isol_lsaddr7                    : 8;	// 24:31
} ISOL_ADDR_SW_REG_10_H13A0;

/*-----------------------------------------------------------------------------
	0x0110 usb0_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	usb0_endian_ahbms_ehci_bufacc   : 1,	//     1
	usb0_endian_ahbms_ohci_bufacc   : 1,	//     2
	usb0_app_start_clk_i            : 1,	//     3
	usb0_ohci_susp_lgcy_i           : 1,	//     4
	usb0_ss_simulation_mode_i       : 1,	//     5
	usb0_ss_word_if_i               : 1,	//     6
	usb0_ss_utmi_backward_enb_i     : 1,	//     7
	usb0_ss_fladj_val_host_i        : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	usb0_ss_fladj_val_i             : 6,	// 16:21
	usb0_ss_resume_utmi_pls_dis_i   : 1,	//    22
	usb0_ss_autoppd_on_overcur_en_i : 1,	//    23
	usb0_ss_ena_incr16_i            : 1,	//    24
	usb0_ss_ena_incr8_i             : 1,	//    25
	usb0_ss_ena_incr4_i             : 1,	//    26
	usb0_ss_ena_incrx_align_i       : 1,	//    27
	usb0_app_prt_ovrcur_i           : 1,	//    28
	usb0_endian_ahbsl               : 1,	//    29
	usb0_endian_ahbms_ehci          : 1,	//    30
	usb0_endian_ahbms_ohci          : 1;	//    31
} USB0_CTRL0_H13A0;

/*-----------------------------------------------------------------------------
	0x0114 usb0_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb0_ohci_0_globalsuspend_o     : 1,	//     0
	usb0_ohci_0_drwe_o              : 1,	//     1
	usb0_ohci_0_rwe_o               : 1,	//     2
	usb0_ohci_0_rmtwkp_o            : 1,	//     3
	usb0_ohci_0_smi_o_n             : 1,	//     4
	usb0_ohci_0_sof_o_n             : 1,	//     5
	usb0_ohci_0_bufacc_o            : 1,	//     6
	usb0_ehci_prt_pwr_o             : 1,	//     7
	usb0_ehci_xfer_cnt_o            :11,	//  8:18
	                                : 1,	//    19 reserved
	usb0_ehci_xfer_prdc_o           : 1,	//    20
	usb0_ehci_bufacc_o              : 1,	//    21
	usb0_ehci_pme_status_o          : 1,	//    22
	usb0_ehci_power_state_ack_o     : 1,	//    23
	usb0_ohci_0_ccs_o               : 1;	//    24
} USB0_STATUS0_H13A0;

/*-----------------------------------------------------------------------------
	0x0118 usb0_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :30,	//  0:29 reserved
	usb0_ehci_usbsts_o              : 1,	//    30
	usb0_ehci_lpsmc_state_o         : 1;	//    31
} USB0_STATUS1_H13A0;

/*-----------------------------------------------------------------------------
	0x0128 io_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ci_en                           : 1,	//     0
	                                : 3,	//  1: 3 reserved
	monitor_sig_sel                 : 4,	//  4: 7
	                                : 8,	//  8:15 reserved
	ahb_port_sel                    :14;	// 16:29
} IO_CTRL_H13A0;

/*-----------------------------------------------------------------------------
	0x0138 apb_time_out_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	tout_en                         : 1,	//     0
	tout_intr_clr                   : 1,	//     1
	                                :14,	//  2:15 reserved
	tout_cnt                        :16;	// 16:31
} APB_TIME_OUT_CTRL_H13A0;

/*-----------------------------------------------------------------------------
	0x013c apb_time_out_src_31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	psel0_tout                      : 1,	//     0
	psel1_tout                      : 1,	//     1
	psel2_tout                      : 1,	//     2
	psel3_tout                      : 1,	//     3
	psel4_tout                      : 1,	//     4
	psel5_tout                      : 1,	//     5
	                                : 2,	//  6: 7 reserved
	psel8_tout                      : 1,	//     8
	psel9_tout                      : 1,	//     9
	psel10_tout                     : 1,	//    10
	psel11_tout                     : 1,	//    11
	psel12_tout                     : 1,	//    12
	psel13_tout                     : 1,	//    13
	psel14_tout                     : 1,	//    14
	psel15_tout                     : 1,	//    15
	psel16_tout                     : 1,	//    16
	psel17_tout                     : 1,	//    17
	psel18_tout                     : 1,	//    18
	psel19_tout                     : 1,	//    19
	psel20_tout                     : 1,	//    20
	psel21_tout                     : 1,	//    21
	psel22_tout                     : 1,	//    22
	psel23_tout                     : 1,	//    23
	psel24_tout                     : 1,	//    24
	psel25_tout                     : 1,	//    25
	psel26_tout                     : 1,	//    26
	psel27_tout                     : 1,	//    27
	psel28_tout                     : 1,	//    28
	psel29_tout                     : 1,	//    29
	psel30_tout                     : 1;	//    30
} APB_TIME_OUT_SRC_31_0_H13A0;

/*-----------------------------------------------------------------------------
	0x0140 apb_time_out_src_41_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	psel32_tout                     : 1,	//     0
	psel33_tout                     : 1,	//     1
	psel34_tout                     : 1,	//     2
	psel35_tout                     : 1,	//     3
	psel36_tout                     : 1,	//     4
	psel37_tout                     : 1;	//     5
} APB_TIME_OUT_SRC_41_32_H13A0;

/*-----------------------------------------------------------------------------
	0x0144 version ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0148 stcc_ref_time_stamp_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_ref_time_stamp_high        : 1;	//     0
} STCC_REF_TIME_STAMP_32_H13A0;

/*-----------------------------------------------------------------------------
	0x014c stcc_ref_time_stamp_31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_ref_time_stamp_low         ;   	// 31: 0
} STCC_REF_TIME_STAMP_31_0_H13A0;

/*-----------------------------------------------------------------------------
	0x0150 stcc_real_time_stamp_32 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_real_time_stamp_high       : 1;	//     0
} STCC_REAL_TIME_STAMP_32_H13A0;

/*-----------------------------------------------------------------------------
	0x0154 stcc_real_time_stamp_31_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	stcc_real_time_stamp_low        ;   	// 31: 0
} STCC_REAL_TIME_STAMP_31_0_H13A0;

/*-----------------------------------------------------------------------------
	0x0158 flush_done_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sc_flush_done                   : 1,	//     0
	                                : 1,	//     1 reserved
	vdec_flush_done                 : 1,	//     2
	icod_flush_done                 : 1,	//     3
	venc_flush_done                 : 1,	//     4
	te_flush_done                   : 1,	//     5
	gpu_flush_done                  : 1,	//     6
	gfx_flush_done                  : 1,	//     7
	de_gmau_flush_done_dp           : 1,	//     8
	de_gmau_flush_done              : 1,	//     9
	aud_dsp1_flush_done             : 1,	//    10
	aud_dsp0_flush_done             : 1,	//    11
	dvi_flush_done                  : 1,	//    12
	dvo_flush_done                  : 1,	//    13
	mc_flush_done                   : 1,	//    14
	ma_flush_done                   : 1,	//    15
	mb_flhsu_done                   : 1,	//    16
	sre_flush_done                  : 1,	//    17
	dppa_flush_done                 : 1,	//    18
	dppb_flush_done                 : 1;	//    19
} FLUSH_DONE_STATUS_H13A0;

/*-----------------------------------------------------------------------------
	0x015c flush_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sc_flush_en                     : 1,	//     0
	                                : 1,	//     1 reserved
	vdec_flush_en                   : 1,	//     2
	icod_flush_en                   : 1,	//     3
	venc_flush_en                   : 1,	//     4
	te_flush_en                     : 1,	//     5
	gpu_flush_en                    : 1,	//     6
	gfx_flush_en                    : 1,	//     7
	de_gmau_flush_en_dp             : 1,	//     8
	de_gmau_flush_en                : 1,	//     9
	aud_dsp1_flush_en               : 1,	//    10
	aud_dsp0_flush_en               : 1,	//    11
	dvi_flush_en                    : 1,	//    12
	dvo_flush_en                    : 1,	//    13
	mc_flush_en                     : 1,	//    14
	ma_flush_en                     : 1,	//    15
	mb_flhsu_en                     : 1,	//    16
	sre_flush_en                    : 1,	//    17
	dppa_flush_en                   : 1,	//    18
	dppb_flush_en                   : 1;	//    19
} FLUSH_REQ_H13A0;

/*-----------------------------------------------------------------------------
	0x016c bandwidth_limiter_cpu_axi0_dly_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bw_cpu_raxi0_dly_cnt            :16,	//  0:15
	bw_cpu_waxi0_dly_cnt            :16;	// 16:31
} BANDWIDTH_LIMITER_CPU_AXI0_DLY_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0170 bandwidth_limiter_cpu_axi1_dly_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bw_cpu_raxi1_dly_cnt            :16,	//  0:15
	bw_cpu_waxi1_dly_cnt            :16;	// 16:31
} BANDWIDTH_LIMITER_CPU_AXI1_DLY_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0174 gpio_interrupt_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	gpio0_intr                      : 1,	//     0
	gpio1_intr                      : 1,	//     1
	gpio2_intr                      : 1,	//     2
	gpio3_intr                      : 1,	//     3
	gpio4_intr                      : 1,	//     4
	gpio5_intr                      : 1,	//     5
	gpio6_intr                      : 1,	//     6
	gpio7_intr                      : 1,	//     7
	gpio8_intr                      : 1,	//     8
	gpio9_intr                      : 1,	//     9
	gpio10_intr                     : 1,	//    10
	gpio11_intr                     : 1;	//    11
} GPIO_INTERRUPT_STATUS_H13A0;

/*-----------------------------------------------------------------------------
	0x0178 urgency ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	peri1_aw_urgency                : 2,	//  0: 1
	peri1_ar_urgency                : 2,	//  2: 3
	                                : 4,	//  4: 7 reserved
	peri0_aw_urgency                : 2,	//  8: 9
	peri0_ar_urgency                : 2,	// 10:11
	                                : 4,	// 12:15 reserved
	cpu1_aw_urgency                 : 2,	// 16:17
	cpu1_ar_urgency                 : 2,	// 18:19
	                                : 4,	// 20:23 reserved
	cpu0_aw_urgency                 : 2,	// 24:25
	cpu0_ar_urgency                 : 2,	// 26:27
	sc_aw_urgency                   : 2,	// 28:29
	sc_ar_urgency                   : 2;	// 30:31
} URGENCY_H13A0;

/*-----------------------------------------------------------------------------
	0x017c l2_cache_drreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_drreq_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DRREQ_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0180 l2_cache_drhit_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_drhit_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DRHIT_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0184 l2_cache_dwreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_dwreq_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DWREQ_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0188 l2_cache_dwtreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_dwtreq_evnt_cnt              ;   	// 31: 0
} L2_CACHE_DWTREQ_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x018c l2_cache_dwhit_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_dwhit_evnt_cnt               ;   	// 31: 0
} L2_CACHE_DWHIT_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0190 l2_cache_irreq_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_irreq_evnt_cnt               ;   	// 31: 0
} L2_CACHE_IRREQ_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0194 l2_cache_irhit_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_irhit_evnt_cnt               ;   	// 31: 0
} L2_CACHE_IRHIT_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0198 l2_cache_wa_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_wa_evnt_cnt                  ;   	// 31: 0
} L2_CACHE_WA_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x019c l2_cache_co_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_co_evnt_cnt                  ;   	// 31: 0
} L2_CACHE_CO_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x01a4 l2_cache_event_monitor_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	evnt_en                         : 1,	//     0
	evnt_cnt_reset                  : 1;	//     1
} L2_CACHE_EVENT_MONITOR_CTRL_H13A0;

/*-----------------------------------------------------------------------------
	0x01a8 usb1_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	usb1_endian_ahbms_ehci_bufacc   : 1,	//     1
	usb1_endian_ahbms_ohci_bufacc   : 1,	//     2
	usb1_app_start_clk_i            : 1,	//     3
	usb1_ohci_susp_lgcy_i           : 1,	//     4
	usb1_ss_simulation_mode_i       : 1,	//     5
	usb1_ss_word_if_i               : 1,	//     6
	usb1_ss_utmi_backward_enb_i     : 1,	//     7
	usb1_ss_fladj_val_host_i        : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	usb1_ss_fladj_val_i             : 6,	// 16:21
	usb1_ss_resume_utmi_pls_dis_i   : 1,	//    22
	usb1_ss_autoppd_on_overcur_en_i : 1,	//    23
	usb1_ss_ena_incr16_i            : 1,	//    24
	usb1_ss_ena_incr8_i             : 1,	//    25
	usb1_ss_ena_incr4_i             : 1,	//    26
	usb1_ss_ena_incrx_align_i       : 1,	//    27
	usb1_app_prt_ovrcur_i           : 1,	//    28
	usb1_endian_ahbsl               : 1,	//    29
	usb1_endian_ahbms_ehci          : 1,	//    30
	usb1_endian_ahbms_ohci          : 1;	//    31
} USB1_CTRL0_H13A0;

/*-----------------------------------------------------------------------------
	0x01ac usb1_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb1_ohci_0_globalsuspend_o     : 1,	//     0
	usb1_ohci_0_drwe_o              : 1,	//     1
	usb1_ohci_0_rwe_o               : 1,	//     2
	usb1_ohci_0_rmtwkp_o            : 1,	//     3
	usb1_ohci_0_smi_o_n             : 1,	//     4
	usb1_ohci_0_sof_o_n             : 1,	//     5
	usb1_ohci_0_bufacc_o            : 1,	//     6
	usb1_ehci_prt_pwr_o             : 1,	//     7
	usb1_ehci_xfer_cnt_o            :11,	//  8:18
	                                : 1,	//    19 reserved
	usb1_ehci_xfer_prdc_o           : 1,	//    20
	usb1_ehci_bufacc_o              : 1,	//    21
	usb1_ehci_pme_status_o          : 1,	//    22
	usb1_ehci_power_state_ack_o     : 1,	//    23
	usb1_ohci_0_ccs_o               : 1;	//    24
} USB1_STATUS0_H13A0;

/*-----------------------------------------------------------------------------
	0x01b0 usb1_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :30,	//  0:29 reserved
	usb1_ehci_usbsts_o              : 1,	//    30
	usb1_ehci_lpsmc_state_o         : 1;	//    31
} USB1_STATUS1_H13A0;

/*-----------------------------------------------------------------------------
	0x01ec l2_cache_epfalloc_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_epfalloc_event_cnt           ;   	// 31: 0
} L2_CACHE_EPFALLOC_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x01f0 l2_cache_epfhit_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_epfhit_event_cnt             ;   	// 31: 0
} L2_CACHE_EPFHIT_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x01f4 l2_cache_epfrcvds0_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_epfrcvds0_event_cnt          ;   	// 31: 0
} L2_CACHE_EPFRCVDS0_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x01f8 l2_cache_epfrcvds1_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_epfrcvds1_event_cnt          ;   	// 31: 0
} L2_CACHE_EPFRCVDS1_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x01fc l2_cache_srconfs0_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_srconfs0_event_cnt           ;   	// 31: 0
} L2_CACHE_SRCONFS0_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0200 l2_cache_srconfs1_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_srconfs1_event_cnt           ;   	// 31: 0
} L2_CACHE_SRCONFS1_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0204 l2_cache_srrcvds0_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_srrcvds0_event_cnt           ;   	// 31: 0
} L2_CACHE_SRRCVDS0_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0208 l2_cache_srrcvds1_event_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_srrcvds1_event_cnt           ;   	// 31: 0
} L2_CACHE_SRRCVDS1_EVENT_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x020c l2_cache_ipfalloc_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l2_ipfalloc_cnt                 ;   	// 31: 0
} L2_CACHE_IPFALLOC_CNT_H13A0;

/*-----------------------------------------------------------------------------
	0x0210 l2_cache_clock_stoped ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	l2_clock_stoped                 : 1;	//    31
} L2_CACHE_CLOCK_STOPED_H13A0;

/*-----------------------------------------------------------------------------
	0x0214 ctr76 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	syncreq0                        : 1,	//     0
	syncreq1                        : 1;	//     1
} SYNC_REQ_H13A0;

/*-----------------------------------------------------------------------------
	0x0218 sc_addr_sw_reg_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	sc_paddr_app_nor_boot           : 6,	// 10:15
	                                :12,	// 16:27 reserved
	sc_laddr_app_nor_boot           : 4;	// 28:31
} SC_ADDR_SW_REG_0_H13A0;

/*-----------------------------------------------------------------------------
	0x021c sc_addr_sw_reg_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sc_paddr_app_rom_boot           :16,	//  0:15
	                                : 2,	// 16:17 reserved
	sc_laddr_app_rom_boot           :14;	// 18:31
} SC_ADDR_SW_REG_1_H13A0;

/*-----------------------------------------------------------------------------
	0x0220 sc_addr_sw_reg_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sc_paddr_app_gpu_host           : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	sc_laddr_app_gpu_host           : 4,	// 12:15
	                                : 2,	// 16:17 reserved
	sc_paddr_app_shadow             : 6,	// 18:23
	                                : 4,	// 24:27 reserved
	sc_laddr_app_shadow             : 4;	// 28:31
} SC_ADDR_SW_REG_2_H13A0;

/*-----------------------------------------------------------------------------
	0x0224 sc_addr_sw_reg_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset0                      : 8,	//  8:15
	sc_leaddr0                      : 8,	// 16:23
	sc_lsaddr0                      : 8;	// 24:31
} SC_ADDR_SW_REG_3_H13A0;

/*-----------------------------------------------------------------------------
	0x0228 sc_addr_sw_reg_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset1                      : 8,	//  8:15
	sc_leaddr1                      : 8,	// 16:23
	sc_lsaddr1                      : 8;	// 24:31
} SC_ADDR_SW_REG_4_H13A0;

/*-----------------------------------------------------------------------------
	0x022c sc_addr_sw_reg_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset2                      : 8,	//  8:15
	sc_leaddr2                      : 8,	// 16:23
	sc_lsaddr2                      : 8;	// 24:31
} SC_ADDR_SW_REG_5_H13A0;

/*-----------------------------------------------------------------------------
	0x0230 sc_addr_sw_reg_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset3                      : 8,	//  8:15
	sc_leaddr3                      : 8,	// 16:23
	sc_lsaddr3                      : 8;	// 24:31
} SC_ADDR_SW_REG_6_H13A0;

/*-----------------------------------------------------------------------------
	0x0234 sc_addr_sw_reg_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset4                      : 8,	//  8:15
	sc_leaddr4                      : 8,	// 16:23
	sc_lsaddr4                      : 8;	// 24:31
} SC_ADDR_SW_REG_7_H13A0;

/*-----------------------------------------------------------------------------
	0x0238 sc_addr_sw_reg_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset5                      : 8,	//  8:15
	sc_leaddr5                      : 8,	// 16:23
	sc_lsaddr5                      : 8;	// 24:31
} SC_ADDR_SW_REG_8_H13A0;

/*-----------------------------------------------------------------------------
	0x023c sc_addr_sw_reg_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset6                      : 8,	//  8:15
	sc_leaddr6                      : 8,	// 16:23
	sc_lsaddr6                      : 8;	// 24:31
} SC_ADDR_SW_REG_9_H13A0;

/*-----------------------------------------------------------------------------
	0x0240 sc_addr_sw_reg_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	sc_offset7                      : 8,	//  8:15
	sc_leaddr7                      : 8,	// 16:23
	sc_lsaddr7                      : 8;	// 24:31
} SC_ADDR_SW_REG_10_H13A0;

/*-----------------------------------------------------------------------------
	0x0244 ssusb_addr_sw_reg_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	ssusb_paddr_app_nor_boot        : 6,	// 10:15
	                                :12,	// 16:27 reserved
	ssusb_laddr_app_nor_boot        : 4;	// 28:31
} SSUSB_ADDR_SW_REG_0_H13A0;

/*-----------------------------------------------------------------------------
	0x0248 ssusb_addr_sw_reg_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_paddr_app_rom_boot        :16,	//  0:15
	                                : 2,	// 16:17 reserved
	ssusb_laddr_app_rom_boot        :14;	// 18:31
} SSUSB_ADDR_SW_REG_1_H13A0;

/*-----------------------------------------------------------------------------
	0x024c ssusb_addr_sw_reg_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_paddr_app_gpu_host        : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	ssusb_laddr_app_gpu_host        : 4,	// 12:15
	                                : 2,	// 16:17 reserved
	ssusb_paddr_app_shadow          : 6,	// 18:23
	                                : 4,	// 24:27 reserved
	ssusb_laddr_app_shadow          : 4;	// 28:31
} SSUSB_ADDR_SW_REG_2_H13A0;

/*-----------------------------------------------------------------------------
	0x0250 ssusb_addr_sw_reg_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset0                   : 8,	//  8:15
	ssusb_leaddr0                   : 8,	// 16:23
	ssusb_lsaddr0                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_3_H13A0;

/*-----------------------------------------------------------------------------
	0x0254 ssusb_addr_sw_reg_4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset1                   : 8,	//  8:15
	ssusb_leaddr1                   : 8,	// 16:23
	ssusb_lsaddr1                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_4_H13A0;

/*-----------------------------------------------------------------------------
	0x0258 ssusb_addr_sw_reg_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset2                   : 8,	//  8:15
	ssusb_leaddr2                   : 8,	// 16:23
	ssusb_lsaddr2                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_5_H13A0;

/*-----------------------------------------------------------------------------
	0x025c ssusb_addr_sw_reg_6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset3                   : 8,	//  8:15
	ssusb_leaddr3                   : 8,	// 16:23
	ssusb_lsaddr3                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_6_H13A0;

/*-----------------------------------------------------------------------------
	0x0260 ssusb_addr_sw_reg_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset4                   : 8,	//  8:15
	ssusb_leaddr4                   : 8,	// 16:23
	ssusb_lsaddr4                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_7_H13A0;

/*-----------------------------------------------------------------------------
	0x0264 ssusb_addr_sw_reg_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset5                   : 8,	//  8:15
	ssusb_leaddr5                   : 8,	// 16:23
	ssusb_lsaddr5                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_8_H13A0;

/*-----------------------------------------------------------------------------
	0x0268 ssusb_addr_sw_reg_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset6                   : 8,	//  8:15
	ssusb_leaddr6                   : 8,	// 16:23
	ssusb_lsaddr6                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_9_H13A0;

/*-----------------------------------------------------------------------------
	0x026c ssusb_addr_sw_reg_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	ssusb_offset7                   : 8,	//  8:15
	ssusb_leaddr7                   : 8,	// 16:23
	ssusb_lsaddr7                   : 8;	// 24:31
} SSUSB_ADDR_SW_REG_10_H13A0;

/*-----------------------------------------------------------------------------
	0x0270 cpu_addr_sw_on_3_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 2,	//  0: 1 reserved
	cpu_addr_sw_on_7_3              : 2;	//  2: 3
} CPU_ADDR_SW_ON_3_2_H13A0;

/*-----------------------------------------------------------------------------
	0x0288 emmc_host_control0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	fb_clk_en                       : 4,	//  0: 3
	ip_tap_ctrl                     : 2,	//  4: 5
	                                : 2,	//  6: 7 reserved
	ip_tap_delay                    : 6,	//  8:13
	                                : 1,	//    14 reserved
	ip_tap_en                       : 1,	//    15
	op_tap_ctrl                     : 2,	// 16:17
	                                : 2,	// 18:19 reserved
	op_tap_delay                    : 4,	// 20:23
	op_tap_en                       : 1,	//    24
	                                : 3,	// 25:27 reserved
	retuning_require                : 1,	//    28
	                                : 2,	// 29:30 reserved
	cmd_conflict_dis                : 1;	//    31
} EMMC_HOST_CONTROL0_H13A0;

/*-----------------------------------------------------------------------------
	0x028c emmc_host_control1 & cap_reg_in_s1_h ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cap_reg_in_s1_h                 :13,	//  0:12
	                                :11,	// 13:23 reserved
	tuning_cmd_success_cnt_s2       : 4,	// 24:27
	tuning_cmd_success_cnt_s1       : 4;	// 28:31
} EMMC_HOST_CONTROL1_CAP_REG_IN_S1_H_H13A0;

/*-----------------------------------------------------------------------------
	0x0290 cap_reg_in_s1_l ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cap_reg_in_s1_l                 ;   	// 31: 0
} CAP_REG_IN_S1_L_H13A0;

/*-----------------------------------------------------------------------------
	0x0294 init_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	init_preset_in_s1               :13;	//  0:12
} INIT_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x0298 default_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	default_preset_in_s1            :13;	//  0:12
} DEFAULT_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x029c high_speed_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	high_speed_preset_in_s1         :13;	//  0:12
} HIGH_SPEED_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x02a0 sdr12_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr12_preset_in_s1              :13;	//  0:12
} SDR12_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x02a4 sdr25_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr25_preset_in_s1              :13;	//  0:12
} SDR25_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x02a8 sdr50_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr50_preset_in_s1              :13;	//  0:12
} SDR50_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x02ac sdr104_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr104_preset_in_s1             :13;	//  0:12
} SDR104_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x02b0 ddr50_preset_in_s1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ddr50_preset_in_s1              :13;	//  0:12
} DDR50_PRESET_IN_S1_H13A0;

/*-----------------------------------------------------------------------------
	0x02b4 cap_reg_in_s2_h ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cap_reg_in_s2_h                 :13;	//  0:12
} CAP_REG_IN_S2_H_H13A0;

/*-----------------------------------------------------------------------------
	0x02b8 cap_reg_in_s2_l ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cap_reg_in_s2_l                 ;   	// 31: 0
} CAP_REG_IN_S2_L_H13A0;

/*-----------------------------------------------------------------------------
	0x02bc init_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	init_preset_in_s2               :13;	//  0:12
} INIT_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02c0 default_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	default_preset_in_s2            :13;	//  0:12
} DEFAULT_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02c4 high_speed_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	high_speed_preset_in_s2         :13;	//  0:12
} HIGH_SPEED_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02c8 sdr12_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr12_preset_in_s2              :13;	//  0:12
} SDR12_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02cc sdr25_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr25_preset_in_s2              :13;	//  0:12
} SDR25_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02d0 sdr50_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr50_preset_in_s2              :13;	//  0:12
} SDR50_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02d4 sdr104_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sdr104_preset_in_s2             :13;	//  0:12
} SDR104_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02d8 ddr50_preset_in_s2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ddr50_preset_in_s2              :13;	//  0:12
} DDR50_PRESET_IN_S2_H13A0;

/*-----------------------------------------------------------------------------
	0x02dc sync_reg0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sync_reg0                       ;   	// 31: 0
} SYNC_REG0_H13A0;

/*-----------------------------------------------------------------------------
	0x02e0 sync_reg1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sync_reg1                       ;   	// 31: 0
} SYNC_REG1_H13A0;

/*-----------------------------------------------------------------------------
	0x02e4 gp_reg4 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02e8 gp_reg5 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02ec gp_reg6 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02f0 gp_reg7 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02f4 gp_reg8 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02f8 gp_reg9 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02fc gp_reg10 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0300 osprey_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :29,	//  0:28 reserved
	npwrupdbgmd1                    : 1,	//    29
	npwrupdbgmd0                    : 1,	//    30
	nisolatesdbgm                   : 1;	//    31
} OSPREY_CTRL7_H13A0;

/*-----------------------------------------------------------------------------
	0x0304 osprey_ctrl8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cfgfiltend                      :12,	//  0:11
	cfgfiltstart                    :12,	// 12:23
	                                : 7,	// 24:30 reserved
	cfgaddrfilten                   : 1;	//    31
} OSPREY_CTRL8_H13A0;

/*-----------------------------------------------------------------------------
	0x0308 osprey_ctrl9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	csysreqm1vsoc                   : 1,	//     0
	                                :30,	//  1:30 reserved
	csysreqm0vsoc                   : 1;	//    31
} OSPREY_CTRL9_H13A0;

/*-----------------------------------------------------------------------------
	0x030c osprey_ctrl10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	tpmaxdatasize                   : 5;	//  0: 4
} OSPREY_CTRL10_H13A0;

/*-----------------------------------------------------------------------------
	0x0310 osprey_ctrl11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cihsbypass                      : 4,	//  0: 3
	                                :27,	//  4:30 reserved
	cisbypass                       : 1;	//    31
} OSPREY_CTRL11_H13A0;

/*-----------------------------------------------------------------------------
	0x0314 osprey_ctrl12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	cdbgrstack                      : 1;	//    31
} OSPREY_CTRL12_H13A0;

/*-----------------------------------------------------------------------------
	0x0318 gp_reg11 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x031c gp_reg12 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0320 gp_reg13 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0324 gp_reg14 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0328 gp_reg15 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x032c gp_reg16 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0330 gp_reg17 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0334 osprey_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	smpnamp                         : 2,	//  0: 1
	pl310idle                       : 1,	//     2
	                                : 6,	//  3: 8 reserved
	deflags0                        : 7,	//  9:15
	deflags1                        : 7,	// 16:22
	pmusecure                       : 2,	// 23:24
	pmupriv                         : 2,	// 25:26
	ptmpwrup1                       : 1,	//    27
	ptmidleack1                     : 1,	//    28
	ptmpwrup0                       : 1,	//    29
	ptmidleack0                     : 1,	//    30
	scuevabort                      : 1;	//    31
} OSPREY_STATUS0_H13A0;

/*-----------------------------------------------------------------------------
	0x0338 osprey_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	datawritelat                    : 3,	//  0: 2
	datareadlat                     : 3,	//  3: 5
	datasetuplat                    : 3,	//  6: 8
	tagwritelat                     : 3,	//  9:11
	tagreadlat                      : 3,	// 12:14
	tagsetuplat                     : 3,	// 15:17
	pwrctlo0                        : 2,	// 18:19
	                                : 2,	// 20:21 reserved
	pwrctlo1                        : 2,	// 22:23
	                                : 2,	// 24:25 reserved
	standbywfi                      : 2,	// 26:27
	                                : 2,	// 28:29 reserved
	standbywfe                      : 2;	// 30:31
} OSPREY_STATUS1_H13A0;

/*-----------------------------------------------------------------------------
	0x033c osprey_status2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	csysackm1vsoc                   : 1,	//     0
	cdbgrstreq                      : 1,	//     1
	                                :18,	//  2:19 reserved
	nfiqout                         : 2,	// 20:21
	nirqout                         : 2,	// 22:23
	                                : 2,	// 24:25 reserved
	dbgnoppwrdn                     : 2,	// 26:27
	                                : 1,	//    28 reserved
	dbgcpudone                      : 2,	// 29:30
	csysackm0vsoc                   : 1;	//    31
} OSPREY_STATUS2_H13A0;

/*-----------------------------------------------------------------------------
	0x0340 osprey_status3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cpuready                        : 2,	//  0: 1
	neonready                       : 2,	//  2: 3
	                                :27,	//  4:30 reserved
	scuready                        : 1;	//    31
} OSPREY_STATUS3_H13A0;

/*-----------------------------------------------------------------------------
	0x0348 usb2_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 1,	//     0 reserved
	usb2_endian_ahbms_ehci_bufacc   : 1,	//     1
	usb2_endian_ahbms_ohci_bufacc   : 1,	//     2
	usb2_app_start_clk_i            : 1,	//     3
	usb2_ohci_susp_lgcy_i           : 1,	//     4
	usb2_ss_simulation_mode_i       : 1,	//     5
	usb2_ss_word_if_i               : 1,	//     6
	usb2_ss_utmi_backward_enb_i     : 1,	//     7
	usb2_ss_fladj_val_host_i        : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	usb2_ss_fladj_val_i             : 6,	// 16:21
	usb2_ss_resume_utmi_pls_dis_i   : 1,	//    22
	usb2_ss_autoppd_on_overcur_en_i : 1,	//    23
	usb2_ss_ena_incr16_i            : 1,	//    24
	usb2_ss_ena_incr8_i             : 1,	//    25
	usb2_ss_ena_incr4_i             : 1,	//    26
	usb2_ss_ena_incrx_align_i       : 1,	//    27
	usb2_app_prt_ovrcur_i           : 1,	//    28
	usb2_endian_ahbsl               : 1,	//    29
	usb2_endian_ahbms_ehci          : 1,	//    30
	usb2_endian_ahbms_ohci          : 1;	//    31
} USB2_CTRL0_H13A0;

/*-----------------------------------------------------------------------------
	0x034c usb2_status0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	usb2_ohci_0_globalsuspend_o     : 1,	//     0
	usb2_ohci_0_drwe_o              : 1,	//     1
	usb2_ohci_0_rwe_o               : 1,	//     2
	usb2_ohci_0_rmtwkp_o            : 1,	//     3
	usb2_ohci_0_smi_o_n             : 1,	//     4
	usb2_ohci_0_sof_o_n             : 1,	//     5
	usb2_ohci_0_bufacc_o            : 1,	//     6
	usb2_ehci_prt_pwr_o             : 1,	//     7
	usb2_ehci_xfer_cnt_o            :11,	//  8:18
	                                : 1,	//    19 reserved
	usb2_ehci_xfer_prdc_o           : 1,	//    20
	usb2_ehci_bufacc_o              : 1,	//    21
	usb2_ehci_pme_status_o          : 1,	//    22
	usb2_ehci_power_state_ack_o     : 1,	//    23
	usb2_ohci_0_ccs_o               : 1;	//    24
} USB2_STATUS0_H13A0;

/*-----------------------------------------------------------------------------
	0x0350 usb2_status1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :30,	//  0:29 reserved
	usb2_ehci_usbsts_o              : 1,	//    30
	usb2_ehci_lpsmc_state_o         : 1;	//    31
} USB2_STATUS1_H13A0;

/*-----------------------------------------------------------------------------
	0x03a8 ssusb_logic_analyzer_trace_upper ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_logic_analyzer_trace_63_32;   	// 31: 0
} SSUSB_LOGIC_ANALYZER_TRACE_UPPER_H13A0;

/*-----------------------------------------------------------------------------
	0x03ac ssusb_logic_analyzer_trace_lower ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_logic_analyzer_trace_31_0 ;   	// 31: 0
} SSUSB_LOGIC_ANALYZER_TRACE_LOWER_H13A0;

/*-----------------------------------------------------------------------------
	0x03b0 ssusb_control_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_fladj_30mhz_req           : 6,	//  0: 5
	                                : 6,	//  6:11 reserved
	ssusb_host_msi_enable           : 1,	//    12
	                                : 3,	// 13:15 reserved
	ssusb_host_port_power_control_pr: 1,	//    16
	                                : 3,	// 17:19 reserved
	ssusb_host_u3_port_disable      : 1,	//    20
	                                : 3,	// 21:23 reserved
	ssusb_host_u2_port_disable      : 1,	//    24
	                                : 3,	// 25:27 reserved
	ssusb_bigendian_gs              : 1;	//    28
} SSUSB_CONTROL_0_H13A0;

/*-----------------------------------------------------------------------------
	0x03b4 ssusb_control_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_xhc_bme                   : 1,	//     0
	                                : 3,	//  1: 3 reserved
	ssusb_xhci_revision             : 1;	//     4
} SSUSB_CONTROL_1_H13A0;

/*-----------------------------------------------------------------------------
	0x03b8 ssusb_host_current_belt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_host_current_belt         :12;	//  0:11
} SSUSB_HOST_CURRENT_BELT_H13A0;

/*-----------------------------------------------------------------------------
	0x03bc ssusb_debug_info_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_debug_info_57_32          :26;	//  0:25
} SSUSB_DEBUG_INFO_0_H13A0;

/*-----------------------------------------------------------------------------
	0x03c0 ssusb_debug_info_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ssusb_debug_info_31_0           ;   	// 31: 0
} SSUSB_DEBUG_INFO_1_H13A0;

typedef struct {
	UINT32                          	    gp_reg0                         ;	// 0x0000 : ''
	UINT32                              	gp_reg1                         ;	// 0x0004 : ''
	UINT32                              	gp_reg2                         ;	// 0x0008 : ''
	UINT32                              	gp_reg3                         ;	// 0x000c : ''
	CPU0_ADDR_SW_REG_0_H13A0              	cpu0_addr_sw_reg_0              ;	// 0x0010 : ''
	CPU0_ADDR_SW_REG_1_H13A0              	cpu0_addr_sw_reg_1              ;	// 0x0014 : ''
	CPU0_ADDR_SW_REG_2_H13A0              	cpu0_addr_sw_reg_2              ;	// 0x0018 : ''
	CPU0_ADDR_SW_REG_3_H13A0              	cpu0_addr_sw_reg_3              ;	// 0x001c : ''
	CPU0_ADDR_SW_REG_4_H13A0              	cpu0_addr_sw_reg_4              ;	// 0x0020 : ''
	CPU0_ADDR_SW_REG_5_H13A0              	cpu0_addr_sw_reg_5              ;	// 0x0024 : ''
	CPU0_ADDR_SW_REG_6_H13A0              	cpu0_addr_sw_reg_6              ;	// 0x0028 : ''
	CPU0_ADDR_SW_REG_7_H13A0              	cpu0_addr_sw_reg_7              ;	// 0x002c : ''
	CPU0_ADDR_SW_REG_8_H13A0              	cpu0_addr_sw_reg_8              ;	// 0x0030 : ''
	CPU0_ADDR_SW_REG_9_H13A0              	cpu0_addr_sw_reg_9              ;	// 0x0034 : ''
	CPU0_ADDR_SW_REG_10_H13A0             	cpu0_addr_sw_reg_10             ;	// 0x0038 : ''
	CPU1_ADDR_SW_REG_0_H13A0              	cpu1_addr_sw_reg_0              ;	// 0x003c : ''
	CPU1_ADDR_SW_REG_1_H13A0              	cpu1_addr_sw_reg_1              ;	// 0x0040 : ''
	CPU1_ADDR_SW_REG_2_H13A0              	cpu1_addr_sw_reg_2              ;	// 0x0044 : ''
	CPU1_ADDR_SW_REG_3_H13A0              	cpu1_addr_sw_reg_3              ;	// 0x0048 : ''
	CPU1_ADDR_SW_REG_4_H13A0              	cpu1_addr_sw_reg_4              ;	// 0x004c : ''
	CPU1_ADDR_SW_REG_5_H13A0              	cpu1_addr_sw_reg_5              ;	// 0x0050 : ''
	CPU1_ADDR_SW_REG_6_H13A0              	cpu1_addr_sw_reg_6              ;	// 0x0054 : ''
	CPU1_ADDR_SW_REG_7_H13A0              	cpu1_addr_sw_reg_7              ;	// 0x0058 : ''
	CPU1_ADDR_SW_REG_8_H13A0              	cpu1_addr_sw_reg_8              ;	// 0x005c : ''
	CPU1_ADDR_SW_REG_9_H13A0              	cpu1_addr_sw_reg_9              ;	// 0x0060 : ''
	CPU1_ADDR_SW_REG_10_H13A0             	cpu1_addr_sw_reg_10             ;	// 0x0064 : ''
	PERI0_ADDR_SW_REG_0_H13A0             	peri0_addr_sw_reg_0             ;	// 0x0068 : ''
	PERI0_ADDR_SW_REG_1_H13A0             	peri0_addr_sw_reg_1             ;	// 0x006c : ''
	PERI0_ADDR_SW_REG_2_H13A0             	peri0_addr_sw_reg_2             ;	// 0x0070 : ''
	PERI0_ADDR_SW_REG_3_H13A0             	peri0_addr_sw_reg_3             ;	// 0x0074 : ''
	PERI0_ADDR_SW_REG_4_H13A0             	peri0_addr_sw_reg_4             ;	// 0x0078 : ''
	PERI0_ADDR_SW_REG_5_H13A0             	peri0_addr_sw_reg_5             ;	// 0x007c : ''
	PERI0_ADDR_SW_REG_6_H13A0             	peri0_addr_sw_reg_6             ;	// 0x0080 : ''
	PERI0_ADDR_SW_REG_7_H13A0             	peri0_addr_sw_reg_7             ;	// 0x0084 : ''
	PERI0_ADDR_SW_REG_8_H13A0             	peri0_addr_sw_reg_8             ;	// 0x0088 : ''
	PERI0_ADDR_SW_REG_9_H13A0             	peri0_addr_sw_reg_9             ;	// 0x008c : ''
	PERI0_ADDR_SW_REG_10_H13A0            	peri0_addr_sw_reg_10            ;	// 0x0090 : ''
	PERI1_ADDR_SW_REG_0_H13A0             	peri1_addr_sw_reg_0             ;	// 0x0094 : ''
	PERI1_ADDR_SW_REG_1_H13A0             	peri1_addr_sw_reg_1             ;	// 0x0098 : ''
	PERI1_ADDR_SW_REG_2_H13A0             	peri1_addr_sw_reg_2             ;	// 0x009c : ''
	PERI1_ADDR_SW_REG_3_H13A0             	peri1_addr_sw_reg_3             ;	// 0x00a0 : ''
	PERI1_ADDR_SW_REG_4_H13A0             	peri1_addr_sw_reg_4             ;	// 0x00a4 : ''
	PERI1_ADDR_SW_REG_5_H13A0             	peri1_addr_sw_reg_5             ;	// 0x00a8 : ''
	PERI1_ADDR_SW_REG_6_H13A0             	peri1_addr_sw_reg_6             ;	// 0x00ac : ''
	PERI1_ADDR_SW_REG_7_H13A0             	peri1_addr_sw_reg_7             ;	// 0x00b0 : ''
	PERI1_ADDR_SW_REG_8_H13A0             	peri1_addr_sw_reg_8             ;	// 0x00b4 : ''
	PERI1_ADDR_SW_REG_9_H13A0             	peri1_addr_sw_reg_9             ;	// 0x00b8 : ''
	PERI1_ADDR_SW_REG_10_H13A0            	peri1_addr_sw_reg_10            ;	// 0x00bc : ''
	ISOL_ADDR_SW_REG_0_H13A0              	isol_addr_sw_reg_0              ;	// 0x00c0 : ''
	ISOL_ADDR_SW_REG_1_H13A0              	isol_addr_sw_reg_1              ;	// 0x00c4 : ''
	ISOL_ADDR_SW_REG_2_H13A0              	isol_addr_sw_reg_2              ;	// 0x00c8 : ''
	ISOL_ADDR_SW_REG_3_H13A0              	isol_addr_sw_reg_3              ;	// 0x00cc : ''
	ISOL_ADDR_SW_REG_4_H13A0              	isol_addr_sw_reg_4              ;	// 0x00d0 : ''
	ISOL_ADDR_SW_REG_5_H13A0              	isol_addr_sw_reg_5              ;	// 0x00d4 : ''
	ISOL_ADDR_SW_REG_6_H13A0              	isol_addr_sw_reg_6              ;	// 0x00d8 : ''
	ISOL_ADDR_SW_REG_7_H13A0              	isol_addr_sw_reg_7              ;	// 0x00dc : ''
	ISOL_ADDR_SW_REG_8_H13A0              	isol_addr_sw_reg_8              ;	// 0x00e0 : ''
	ISOL_ADDR_SW_REG_9_H13A0              	isol_addr_sw_reg_9              ;	// 0x00e4 : ''
	ISOL_ADDR_SW_REG_10_H13A0             	isol_addr_sw_reg_10             ;	// 0x00e8 : ''
	UINT32                              	                 __rsvd_00[   9];	// 0x00ec ~ 0x010c
	USB0_CTRL0_H13A0                      	usb0_ctrl0                      ;	// 0x0110 : ''
	USB0_STATUS0_H13A0                    	usb0_status0                    ;	// 0x0114 : ''
	USB0_STATUS1_H13A0                    	usb0_status1                    ;	// 0x0118 : ''
	UINT32                              	                 __rsvd_01[   3];	// 0x011c ~ 0x0124
	IO_CTRL_H13A0                         	io_ctrl                         ;	// 0x0128 : ''
	UINT32                              	                 __rsvd_02[   3];	// 0x012c ~ 0x0134
	APB_TIME_OUT_CTRL_H13A0               	apb_time_out_ctrl               ;	// 0x0138 : ''
	APB_TIME_OUT_SRC_31_0_H13A0           	apb_time_out_src_31_0           ;	// 0x013c : ''
	APB_TIME_OUT_SRC_41_32_H13A0          	apb_time_out_src_41_32          ;	// 0x0140 : ''
	UINT32                              	version                         ;	// 0x0144 : ''
	STCC_REF_TIME_STAMP_32_H13A0          	stcc_ref_time_stamp_32          ;	// 0x0148 : ''
	STCC_REF_TIME_STAMP_31_0_H13A0        	stcc_ref_time_stamp_31_0        ;	// 0x014c : ''
	STCC_REAL_TIME_STAMP_32_H13A0         	stcc_real_time_stamp_32         ;	// 0x0150 : ''
	STCC_REAL_TIME_STAMP_31_0_H13A0       	stcc_real_time_stamp_31_0       ;	// 0x0154 : ''
	FLUSH_DONE_STATUS_H13A0               	flush_done_status               ;	// 0x0158 : ''
	FLUSH_REQ_H13A0                       	flush_req                       ;	// 0x015c : ''
	UINT32                              	                 __rsvd_03[   3];	// 0x0160 ~ 0x0168
	BANDWIDTH_LIMITER_CPU_AXI0_DLY_CNT_H13A0	bandwidth_limiter_cpu_axi0_dly_cnt;	// 0x016c : ''
	BANDWIDTH_LIMITER_CPU_AXI1_DLY_CNT_H13A0	bandwidth_limiter_cpu_axi1_dly_cnt;	// 0x0170 : ''
	GPIO_INTERRUPT_STATUS_H13A0           	gpio_interrupt_status           ;	// 0x0174 : ''
	URGENCY_H13A0                         	urgency                         ;	// 0x0178 : ''
	L2_CACHE_DRREQ_EVENT_CNT_H13A0        	l2_cache_drreq_event_cnt        ;	// 0x017c : ''
	L2_CACHE_DRHIT_EVENT_CNT_H13A0        	l2_cache_drhit_event_cnt        ;	// 0x0180 : ''
	L2_CACHE_DWREQ_EVENT_CNT_H13A0        	l2_cache_dwreq_event_cnt        ;	// 0x0184 : ''
	L2_CACHE_DWTREQ_EVENT_CNT_H13A0       	l2_cache_dwtreq_event_cnt       ;	// 0x0188 : ''
	L2_CACHE_DWHIT_EVENT_CNT_H13A0        	l2_cache_dwhit_event_cnt        ;	// 0x018c : ''
	L2_CACHE_IRREQ_EVENT_CNT_H13A0        	l2_cache_irreq_event_cnt        ;	// 0x0190 : ''
	L2_CACHE_IRHIT_EVENT_CNT_H13A0        	l2_cache_irhit_event_cnt        ;	// 0x0194 : ''
	L2_CACHE_WA_EVENT_CNT_H13A0           	l2_cache_wa_event_cnt           ;	// 0x0198 : ''
	L2_CACHE_CO_EVENT_CNT_H13A0           	l2_cache_co_event_cnt           ;	// 0x019c : ''
	UINT32                              	                 __rsvd_04[   1];	// 0x01a0
	L2_CACHE_EVENT_MONITOR_CTRL_H13A0     	l2_cache_event_monitor_ctrl     ;	// 0x01a4 : ''
	USB1_CTRL0_H13A0                      	usb1_ctrl0                      ;	// 0x01a8 : ''
	USB1_STATUS0_H13A0                    	usb1_status0                    ;	// 0x01ac : ''
	USB1_STATUS1_H13A0                    	usb1_status1                    ;	// 0x01b0 : ''
	UINT32                          	                 __rsvd_05[  14];	// 0x01b4 ~ 0x01e8
	L2_CACHE_EPFALLOC_EVENT_CNT_H13A0     	l2_cache_epfalloc_event_cnt     ;	// 0x01ec : ''
	L2_CACHE_EPFHIT_EVENT_CNT_H13A0       	l2_cache_epfhit_event_cnt       ;	// 0x01f0 : ''
	L2_CACHE_EPFRCVDS0_EVENT_CNT_H13A0    	l2_cache_epfrcvds0_event_cnt    ;	// 0x01f4 : ''
	L2_CACHE_EPFRCVDS1_EVENT_CNT_H13A0    	l2_cache_epfrcvds1_event_cnt    ;	// 0x01f8 : ''
	L2_CACHE_SRCONFS0_EVENT_CNT_H13A0     	l2_cache_srconfs0_event_cnt     ;	// 0x01fc : ''
	L2_CACHE_SRCONFS1_EVENT_CNT_H13A0     	l2_cache_srconfs1_event_cnt     ;	// 0x0200 : ''
	L2_CACHE_SRRCVDS0_EVENT_CNT_H13A0     	l2_cache_srrcvds0_event_cnt     ;	// 0x0204 : ''
	L2_CACHE_SRRCVDS1_EVENT_CNT_H13A0     	l2_cache_srrcvds1_event_cnt     ;	// 0x0208 : ''
	L2_CACHE_IPFALLOC_CNT_H13A0           	l2_cache_ipfalloc_cnt           ;	// 0x020c : ''
	L2_CACHE_CLOCK_STOPED_H13A0           	l2_cache_clock_stoped           ;	// 0x0210 : ''
	SYNC_REQ_H13A0                          sync_req                        ;	// 0x0214 : ''
	SC_ADDR_SW_REG_0_H13A0                	sc_addr_sw_reg_0                ;	// 0x0218 : ''
	SC_ADDR_SW_REG_1_H13A0                	sc_addr_sw_reg_1                ;	// 0x021c : ''
	SC_ADDR_SW_REG_2_H13A0                	sc_addr_sw_reg_2                ;	// 0x0220 : ''
	SC_ADDR_SW_REG_3_H13A0                	sc_addr_sw_reg_3                ;	// 0x0224 : ''
	SC_ADDR_SW_REG_4_H13A0                	sc_addr_sw_reg_4                ;	// 0x0228 : ''
	SC_ADDR_SW_REG_5_H13A0                	sc_addr_sw_reg_5                ;	// 0x022c : ''
	SC_ADDR_SW_REG_6_H13A0                	sc_addr_sw_reg_6                ;	// 0x0230 : ''
	SC_ADDR_SW_REG_7_H13A0                	sc_addr_sw_reg_7                ;	// 0x0234 : ''
	SC_ADDR_SW_REG_8_H13A0                	sc_addr_sw_reg_8                ;	// 0x0238 : ''
	SC_ADDR_SW_REG_9_H13A0                	sc_addr_sw_reg_9                ;	// 0x023c : ''
	SC_ADDR_SW_REG_10_H13A0               	sc_addr_sw_reg_10               ;	// 0x0240 : ''
	SSUSB_ADDR_SW_REG_0_H13A0             	ssusb_addr_sw_reg_0             ;	// 0x0244 : ''
	SSUSB_ADDR_SW_REG_1_H13A0             	ssusb_addr_sw_reg_1             ;	// 0x0248 : ''
	SSUSB_ADDR_SW_REG_2_H13A0             	ssusb_addr_sw_reg_2             ;	// 0x024c : ''
	SSUSB_ADDR_SW_REG_3_H13A0             	ssusb_addr_sw_reg_3             ;	// 0x0250 : ''
	SSUSB_ADDR_SW_REG_4_H13A0             	ssusb_addr_sw_reg_4             ;	// 0x0254 : ''
	SSUSB_ADDR_SW_REG_5_H13A0             	ssusb_addr_sw_reg_5             ;	// 0x0258 : ''
	SSUSB_ADDR_SW_REG_6_H13A0             	ssusb_addr_sw_reg_6             ;	// 0x025c : ''
	SSUSB_ADDR_SW_REG_7_H13A0             	ssusb_addr_sw_reg_7             ;	// 0x0260 : ''
	SSUSB_ADDR_SW_REG_8_H13A0             	ssusb_addr_sw_reg_8             ;	// 0x0264 : ''
	SSUSB_ADDR_SW_REG_9_H13A0             	ssusb_addr_sw_reg_9             ;	// 0x0268 : ''
	SSUSB_ADDR_SW_REG_10_H13A0            	ssusb_addr_sw_reg_10            ;	// 0x026c : ''
	CPU_ADDR_SW_ON_3_2_H13A0              	cpu_addr_sw_on_3_2              ;	// 0x0270 : ''
	UINT32                              	                 __rsvd_06[   5];	// 0x0274 ~ 0x0284
	EMMC_HOST_CONTROL0_H13A0              	emmc_host_control0              ;	// 0x0288 : ''
	EMMC_HOST_CONTROL1_CAP_REG_IN_S1_H_H13A0	emmc_host_control1_cap_reg_in_s1_h;	// 0x028c : ''
	CAP_REG_IN_S1_L_H13A0                 	cap_reg_in_s1_l                 ;	// 0x0290 : ''
	INIT_PRESET_IN_S1_H13A0               	init_preset_in_s1               ;	// 0x0294 : ''
	DEFAULT_PRESET_IN_S1_H13A0            	default_preset_in_s1            ;	// 0x0298 : ''
	HIGH_SPEED_PRESET_IN_S1_H13A0         	high_speed_preset_in_s1         ;	// 0x029c : ''
	SDR12_PRESET_IN_S1_H13A0              	sdr12_preset_in_s1              ;	// 0x02a0 : ''
	SDR25_PRESET_IN_S1_H13A0              	sdr25_preset_in_s1              ;	// 0x02a4 : ''
	SDR50_PRESET_IN_S1_H13A0              	sdr50_preset_in_s1              ;	// 0x02a8 : ''
	SDR104_PRESET_IN_S1_H13A0             	sdr104_preset_in_s1             ;	// 0x02ac : ''
	DDR50_PRESET_IN_S1_H13A0              	ddr50_preset_in_s1              ;	// 0x02b0 : ''
	CAP_REG_IN_S2_H_H13A0                 	cap_reg_in_s2_h                 ;	// 0x02b4 : ''
	CAP_REG_IN_S2_L_H13A0                 	cap_reg_in_s2_l                 ;	// 0x02b8 : ''
	INIT_PRESET_IN_S2_H13A0               	init_preset_in_s2               ;	// 0x02bc : ''
	DEFAULT_PRESET_IN_S2_H13A0            	default_preset_in_s2            ;	// 0x02c0 : ''
	HIGH_SPEED_PRESET_IN_S2_H13A0         	high_speed_preset_in_s2         ;	// 0x02c4 : ''
	SDR12_PRESET_IN_S2_H13A0              	sdr12_preset_in_s2              ;	// 0x02c8 : ''
	SDR25_PRESET_IN_S2_H13A0              	sdr25_preset_in_s2              ;	// 0x02cc : ''
	SDR50_PRESET_IN_S2_H13A0              	sdr50_preset_in_s2              ;	// 0x02d0 : ''
	SDR104_PRESET_IN_S2_H13A0             	sdr104_preset_in_s2             ;	// 0x02d4 : ''
	DDR50_PRESET_IN_S2_H13A0              	ddr50_preset_in_s2              ;	// 0x02d8 : ''
	SYNC_REG0_H13A0                       	sync_reg0                       ;	// 0x02dc : ''
	SYNC_REG1_H13A0                       	sync_reg1                       ;	// 0x02e0 : ''
	UINT32                              	gp_reg4                         ;	// 0x02e4 : ''
	UINT32                              	gp_reg5                         ;	// 0x02e8 : ''
	UINT32                              	gp_reg6                         ;	// 0x02ec : ''
	UINT32                              	gp_reg7                         ;	// 0x02f0 : ''
	UINT32                              	gp_reg8                         ;	// 0x02f4 : ''
	UINT32                              	gp_reg9                         ;	// 0x02f8 : ''
	UINT32                              	gp_reg10                        ;	// 0x02fc : ''
	OSPREY_CTRL7_H13A0                    	osprey_ctrl7                    ;	// 0x0300 : ''
	OSPREY_CTRL8_H13A0                    	osprey_ctrl8                    ;	// 0x0304 : ''
	OSPREY_CTRL9_H13A0                    	osprey_ctrl9                    ;	// 0x0308 : ''
	OSPREY_CTRL10_H13A0                   	osprey_ctrl10                   ;	// 0x030c : ''
	OSPREY_CTRL11_H13A0                   	osprey_ctrl11                   ;	// 0x0310 : ''
	OSPREY_CTRL12_H13A0                   	osprey_ctrl12                   ;	// 0x0314 : ''
	UINT32                              	gp_reg11                        ;	// 0x0318 : ''
	UINT32                              	gp_reg12                        ;	// 0x031c : ''
	UINT32                              	gp_reg13                        ;	// 0x0320 : ''
	UINT32                              	gp_reg14                        ;	// 0x0324 : ''
	UINT32                                 	gp_reg15                        ;	// 0x0328 : ''
	UINT32                              	gp_reg16                        ;	// 0x032c : ''
	UINT32                              	gp_reg17                        ;	// 0x0330 : ''
	OSPREY_STATUS0_H13A0                  	osprey_status0                  ;	// 0x0334 : ''
	OSPREY_STATUS1_H13A0                  	osprey_status1                  ;	// 0x0338 : ''
	OSPREY_STATUS2_H13A0                  	osprey_status2                  ;	// 0x033c : ''
	OSPREY_STATUS3_H13A0                  	osprey_status3                  ;	// 0x0340 : ''
	UINT32                              	                 __rsvd_07[   1];	// 0x0344
	USB2_CTRL0_H13A0                      	usb2_ctrl0                      ;	// 0x0348 : ''
	USB2_STATUS0_H13A0                    	usb2_status0                    ;	// 0x034c : ''
	USB2_STATUS1_H13A0                    	usb2_status1                    ;	// 0x0350 : ''
	UINT32                              	                 __rsvd_08[  21];	// 0x0354 ~ 0x03a4
	SSUSB_LOGIC_ANALYZER_TRACE_UPPER_H13A0	ssusb_logic_analyzer_trace_upper;	// 0x03a8 : ''
	SSUSB_LOGIC_ANALYZER_TRACE_LOWER_H13A0	ssusb_logic_analyzer_trace_lower;	// 0x03ac : ''
	SSUSB_CONTROL_0_H13A0                 	ssusb_control_0                 ;	// 0x03b0 : ''
	SSUSB_CONTROL_1_H13A0                 	ssusb_control_1                 ;	// 0x03b4 : ''
	SSUSB_HOST_CURRENT_BELT_H13A0         	ssusb_host_current_belt         ;	// 0x03b8 : ''
	SSUSB_DEBUG_INFO_0_H13A0              	ssusb_debug_info_0              ;	// 0x03bc : ''
	SSUSB_DEBUG_INFO_1_H13A0              	ssusb_debug_info_1              ;	// 0x03c0 : ''
}CPU_TOP_REG_H13A0_T;


/* For symbol preview */
#ifdef NEVER_DEFINE_THIS
UINT32									gp_reg0 						;	// 0x0000 : ''
UINT32									gp_reg1 						;	// 0x0004 : ''
UINT32									gp_reg2 						;	// 0x0008 : ''
UINT32									gp_reg3 						;	// 0x000c : ''
CPU0_ADDR_SW_REG_0_H13A0				cpu0_addr_sw_reg_0				;	// 0x0010 : ''
CPU0_ADDR_SW_REG_1_H13A0				cpu0_addr_sw_reg_1				;	// 0x0014 : ''
CPU0_ADDR_SW_REG_2_H13A0				cpu0_addr_sw_reg_2				;	// 0x0018 : ''
CPU0_ADDR_SW_REG_3_H13A0				cpu0_addr_sw_reg_3				;	// 0x001c : ''
CPU0_ADDR_SW_REG_4_H13A0				cpu0_addr_sw_reg_4				;	// 0x0020 : ''
CPU0_ADDR_SW_REG_5_H13A0				cpu0_addr_sw_reg_5				;	// 0x0024 : ''
CPU0_ADDR_SW_REG_6_H13A0				cpu0_addr_sw_reg_6				;	// 0x0028 : ''
CPU0_ADDR_SW_REG_7_H13A0				cpu0_addr_sw_reg_7				;	// 0x002c : ''
CPU0_ADDR_SW_REG_8_H13A0				cpu0_addr_sw_reg_8				;	// 0x0030 : ''
CPU0_ADDR_SW_REG_9_H13A0				cpu0_addr_sw_reg_9				;	// 0x0034 : ''
CPU0_ADDR_SW_REG_10_H13A0				cpu0_addr_sw_reg_10 			;	// 0x0038 : ''
CPU1_ADDR_SW_REG_0_H13A0				cpu1_addr_sw_reg_0				;	// 0x003c : ''
CPU1_ADDR_SW_REG_1_H13A0				cpu1_addr_sw_reg_1				;	// 0x0040 : ''
CPU1_ADDR_SW_REG_2_H13A0				cpu1_addr_sw_reg_2				;	// 0x0044 : ''
CPU1_ADDR_SW_REG_3_H13A0				cpu1_addr_sw_reg_3				;	// 0x0048 : ''
CPU1_ADDR_SW_REG_4_H13A0				cpu1_addr_sw_reg_4				;	// 0x004c : ''
CPU1_ADDR_SW_REG_5_H13A0				cpu1_addr_sw_reg_5				;	// 0x0050 : ''
CPU1_ADDR_SW_REG_6_H13A0				cpu1_addr_sw_reg_6				;	// 0x0054 : ''
CPU1_ADDR_SW_REG_7_H13A0				cpu1_addr_sw_reg_7				;	// 0x0058 : ''
CPU1_ADDR_SW_REG_8_H13A0				cpu1_addr_sw_reg_8				;	// 0x005c : ''
CPU1_ADDR_SW_REG_9_H13A0				cpu1_addr_sw_reg_9				;	// 0x0060 : ''
CPU1_ADDR_SW_REG_10_H13A0				cpu1_addr_sw_reg_10 			;	// 0x0064 : ''
PERI0_ADDR_SW_REG_0_H13A0				peri0_addr_sw_reg_0 			;	// 0x0068 : ''
PERI0_ADDR_SW_REG_1_H13A0				peri0_addr_sw_reg_1 			;	// 0x006c : ''
PERI0_ADDR_SW_REG_2_H13A0				peri0_addr_sw_reg_2 			;	// 0x0070 : ''
PERI0_ADDR_SW_REG_3_H13A0				peri0_addr_sw_reg_3 			;	// 0x0074 : ''
PERI0_ADDR_SW_REG_4_H13A0				peri0_addr_sw_reg_4 			;	// 0x0078 : ''
PERI0_ADDR_SW_REG_5_H13A0				peri0_addr_sw_reg_5 			;	// 0x007c : ''
PERI0_ADDR_SW_REG_6_H13A0				peri0_addr_sw_reg_6 			;	// 0x0080 : ''
PERI0_ADDR_SW_REG_7_H13A0				peri0_addr_sw_reg_7 			;	// 0x0084 : ''
PERI0_ADDR_SW_REG_8_H13A0				peri0_addr_sw_reg_8 			;	// 0x0088 : ''
PERI0_ADDR_SW_REG_9_H13A0				peri0_addr_sw_reg_9 			;	// 0x008c : ''
PERI0_ADDR_SW_REG_10_H13A0				peri0_addr_sw_reg_10			;	// 0x0090 : ''
PERI1_ADDR_SW_REG_0_H13A0				peri1_addr_sw_reg_0 			;	// 0x0094 : ''
PERI1_ADDR_SW_REG_1_H13A0				peri1_addr_sw_reg_1 			;	// 0x0098 : ''
PERI1_ADDR_SW_REG_2_H13A0				peri1_addr_sw_reg_2 			;	// 0x009c : ''
PERI1_ADDR_SW_REG_3_H13A0				peri1_addr_sw_reg_3 			;	// 0x00a0 : ''
PERI1_ADDR_SW_REG_4_H13A0				peri1_addr_sw_reg_4 			;	// 0x00a4 : ''
PERI1_ADDR_SW_REG_5_H13A0				peri1_addr_sw_reg_5 			;	// 0x00a8 : ''
PERI1_ADDR_SW_REG_6_H13A0				peri1_addr_sw_reg_6 			;	// 0x00ac : ''
PERI1_ADDR_SW_REG_7_H13A0				peri1_addr_sw_reg_7 			;	// 0x00b0 : ''
PERI1_ADDR_SW_REG_8_H13A0				peri1_addr_sw_reg_8 			;	// 0x00b4 : ''
PERI1_ADDR_SW_REG_9_H13A0				peri1_addr_sw_reg_9 			;	// 0x00b8 : ''
PERI1_ADDR_SW_REG_10_H13A0				peri1_addr_sw_reg_10			;	// 0x00bc : ''
ISOL_ADDR_SW_REG_0_H13A0				isol_addr_sw_reg_0				;	// 0x00c0 : ''
ISOL_ADDR_SW_REG_1_H13A0				isol_addr_sw_reg_1				;	// 0x00c4 : ''
ISOL_ADDR_SW_REG_2_H13A0				isol_addr_sw_reg_2				;	// 0x00c8 : ''
ISOL_ADDR_SW_REG_3_H13A0				isol_addr_sw_reg_3				;	// 0x00cc : ''
ISOL_ADDR_SW_REG_4_H13A0				isol_addr_sw_reg_4				;	// 0x00d0 : ''
ISOL_ADDR_SW_REG_5_H13A0				isol_addr_sw_reg_5				;	// 0x00d4 : ''
ISOL_ADDR_SW_REG_6_H13A0				isol_addr_sw_reg_6				;	// 0x00d8 : ''
ISOL_ADDR_SW_REG_7_H13A0				isol_addr_sw_reg_7				;	// 0x00dc : ''
ISOL_ADDR_SW_REG_8_H13A0				isol_addr_sw_reg_8				;	// 0x00e0 : ''
ISOL_ADDR_SW_REG_9_H13A0				isol_addr_sw_reg_9				;	// 0x00e4 : ''
ISOL_ADDR_SW_REG_10_H13A0				isol_addr_sw_reg_10 			;	// 0x00e8 : ''
UINT32													 __rsvd_00[   9];	// 0x00ec ~ 0x010c
USB0_CTRL0_H13A0						usb0_ctrl0						;	// 0x0110 : ''
USB0_STATUS0_H13A0						usb0_status0					;	// 0x0114 : ''
USB0_STATUS1_H13A0						usb0_status1					;	// 0x0118 : ''
UINT32													 __rsvd_01[   3];	// 0x011c ~ 0x0124
IO_CTRL_H13A0							io_ctrl 						;	// 0x0128 : ''
UINT32													 __rsvd_02[   3];	// 0x012c ~ 0x0134
APB_TIME_OUT_CTRL_H13A0 				apb_time_out_ctrl				;	// 0x0138 : ''
APB_TIME_OUT_SRC_31_0_H13A0 			apb_time_out_src_31_0			;	// 0x013c : ''
APB_TIME_OUT_SRC_41_32_H13A0			apb_time_out_src_41_32			;	// 0x0140 : ''
UINT32									version 						;	// 0x0144 : ''
STCC_REF_TIME_STAMP_32_H13A0			stcc_ref_time_stamp_32			;	// 0x0148 : ''
STCC_REF_TIME_STAMP_31_0_H13A0			stcc_ref_time_stamp_31_0		;	// 0x014c : ''
STCC_REAL_TIME_STAMP_32_H13A0			stcc_real_time_stamp_32 		;	// 0x0150 : ''
STCC_REAL_TIME_STAMP_31_0_H13A0 		stcc_real_time_stamp_31_0		;	// 0x0154 : ''
FLUSH_DONE_STATUS_H13A0 				flush_done_status				;	// 0x0158 : ''
FLUSH_REQ_H13A0 						flush_req						;	// 0x015c : ''
UINT32													 __rsvd_03[   3];	// 0x0160 ~ 0x0168
BANDWIDTH_LIMITER_CPU_AXI0_DLY_CNT_H13A0	bandwidth_limiter_cpu_axi0_dly_cnt; // 0x016c : ''
BANDWIDTH_LIMITER_CPU_AXI1_DLY_CNT_H13A0	bandwidth_limiter_cpu_axi1_dly_cnt; // 0x0170 : ''
GPIO_INTERRUPT_STATUS_H13A0 			gpio_interrupt_status			;	// 0x0174 : ''
URGENCY_H13A0							urgency 						;	// 0x0178 : ''
L2_CACHE_DRREQ_EVENT_CNT_H13A0			l2_cache_drreq_event_cnt		;	// 0x017c : ''
L2_CACHE_DRHIT_EVENT_CNT_H13A0			l2_cache_drhit_event_cnt		;	// 0x0180 : ''
L2_CACHE_DWREQ_EVENT_CNT_H13A0			l2_cache_dwreq_event_cnt		;	// 0x0184 : ''
L2_CACHE_DWTREQ_EVENT_CNT_H13A0 		l2_cache_dwtreq_event_cnt		;	// 0x0188 : ''
L2_CACHE_DWHIT_EVENT_CNT_H13A0			l2_cache_dwhit_event_cnt		;	// 0x018c : ''
L2_CACHE_IRREQ_EVENT_CNT_H13A0			l2_cache_irreq_event_cnt		;	// 0x0190 : ''
L2_CACHE_IRHIT_EVENT_CNT_H13A0			l2_cache_irhit_event_cnt		;	// 0x0194 : ''
L2_CACHE_WA_EVENT_CNT_H13A0 			l2_cache_wa_event_cnt			;	// 0x0198 : ''
L2_CACHE_CO_EVENT_CNT_H13A0 			l2_cache_co_event_cnt			;	// 0x019c : ''
UINT32													 __rsvd_04[   1];	// 0x01a0
L2_CACHE_EVENT_MONITOR_CTRL_H13A0		l2_cache_event_monitor_ctrl 	;	// 0x01a4 : ''
USB1_CTRL0_H13A0						usb1_ctrl0						;	// 0x01a8 : ''
USB1_STATUS0_H13A0						usb1_status0					;	// 0x01ac : ''
USB1_STATUS1_H13A0						usb1_status1					;	// 0x01b0 : ''
UINT32												 __rsvd_05[  14];	// 0x01b4 ~ 0x01e8
L2_CACHE_EPFALLOC_EVENT_CNT_H13A0		l2_cache_epfalloc_event_cnt 	;	// 0x01ec : ''
L2_CACHE_EPFHIT_EVENT_CNT_H13A0 		l2_cache_epfhit_event_cnt		;	// 0x01f0 : ''
L2_CACHE_EPFRCVDS0_EVENT_CNT_H13A0		l2_cache_epfrcvds0_event_cnt	;	// 0x01f4 : ''
L2_CACHE_EPFRCVDS1_EVENT_CNT_H13A0		l2_cache_epfrcvds1_event_cnt	;	// 0x01f8 : ''
L2_CACHE_SRCONFS0_EVENT_CNT_H13A0		l2_cache_srconfs0_event_cnt 	;	// 0x01fc : ''
L2_CACHE_SRCONFS1_EVENT_CNT_H13A0		l2_cache_srconfs1_event_cnt 	;	// 0x0200 : ''
L2_CACHE_SRRCVDS0_EVENT_CNT_H13A0		l2_cache_srrcvds0_event_cnt 	;	// 0x0204 : ''
L2_CACHE_SRRCVDS1_EVENT_CNT_H13A0		l2_cache_srrcvds1_event_cnt 	;	// 0x0208 : ''
L2_CACHE_IPFALLOC_CNT_H13A0 			l2_cache_ipfalloc_cnt			;	// 0x020c : ''
L2_CACHE_CLOCK_STOPED_H13A0 			l2_cache_clock_stoped			;	// 0x0210 : ''
CTR76_H13A0 							ctr76							;	// 0x0214 : ''
SC_ADDR_SW_REG_0_H13A0					sc_addr_sw_reg_0				;	// 0x0218 : ''
SC_ADDR_SW_REG_1_H13A0					sc_addr_sw_reg_1				;	// 0x021c : ''
SC_ADDR_SW_REG_2_H13A0					sc_addr_sw_reg_2				;	// 0x0220 : ''
SC_ADDR_SW_REG_3_H13A0					sc_addr_sw_reg_3				;	// 0x0224 : ''
SC_ADDR_SW_REG_4_H13A0					sc_addr_sw_reg_4				;	// 0x0228 : ''
SC_ADDR_SW_REG_5_H13A0					sc_addr_sw_reg_5				;	// 0x022c : ''
SC_ADDR_SW_REG_6_H13A0					sc_addr_sw_reg_6				;	// 0x0230 : ''
SC_ADDR_SW_REG_7_H13A0					sc_addr_sw_reg_7				;	// 0x0234 : ''
SC_ADDR_SW_REG_8_H13A0					sc_addr_sw_reg_8				;	// 0x0238 : ''
SC_ADDR_SW_REG_9_H13A0					sc_addr_sw_reg_9				;	// 0x023c : ''
SC_ADDR_SW_REG_10_H13A0 				sc_addr_sw_reg_10				;	// 0x0240 : ''
SSUSB_ADDR_SW_REG_0_H13A0				ssusb_addr_sw_reg_0 			;	// 0x0244 : ''
SSUSB_ADDR_SW_REG_1_H13A0				ssusb_addr_sw_reg_1 			;	// 0x0248 : ''
SSUSB_ADDR_SW_REG_2_H13A0				ssusb_addr_sw_reg_2 			;	// 0x024c : ''
SSUSB_ADDR_SW_REG_3_H13A0				ssusb_addr_sw_reg_3 			;	// 0x0250 : ''
SSUSB_ADDR_SW_REG_4_H13A0				ssusb_addr_sw_reg_4 			;	// 0x0254 : ''
SSUSB_ADDR_SW_REG_5_H13A0				ssusb_addr_sw_reg_5 			;	// 0x0258 : ''
SSUSB_ADDR_SW_REG_6_H13A0				ssusb_addr_sw_reg_6 			;	// 0x025c : ''
SSUSB_ADDR_SW_REG_7_H13A0				ssusb_addr_sw_reg_7 			;	// 0x0260 : ''
SSUSB_ADDR_SW_REG_8_H13A0				ssusb_addr_sw_reg_8 			;	// 0x0264 : ''
SSUSB_ADDR_SW_REG_9_H13A0				ssusb_addr_sw_reg_9 			;	// 0x0268 : ''
SSUSB_ADDR_SW_REG_10_H13A0				ssusb_addr_sw_reg_10			;	// 0x026c : ''
CPU_ADDR_SW_ON_3_2_H13A0				cpu_addr_sw_on_3_2				;	// 0x0270 : ''
UINT32													 __rsvd_06[   5];	// 0x0274 ~ 0x0284
EMMC_HOST_CONTROL0_H13A0				emmc_host_control0				;	// 0x0288 : ''
EMMC_HOST_CONTROL1_CAP_REG_IN_S1_H_H13A0	emmc_host_control1_cap_reg_in_s1_h; // 0x028c : ''
CAP_REG_IN_S1_L_H13A0					cap_reg_in_s1_l 				;	// 0x0290 : ''
INIT_PRESET_IN_S1_H13A0 				init_preset_in_s1				;	// 0x0294 : ''
DEFAULT_PRESET_IN_S1_H13A0				default_preset_in_s1			;	// 0x0298 : ''
HIGH_SPEED_PRESET_IN_S1_H13A0			high_speed_preset_in_s1 		;	// 0x029c : ''
SDR12_PRESET_IN_S1_H13A0				sdr12_preset_in_s1				;	// 0x02a0 : ''
SDR25_PRESET_IN_S1_H13A0				sdr25_preset_in_s1				;	// 0x02a4 : ''
SDR50_PRESET_IN_S1_H13A0				sdr50_preset_in_s1				;	// 0x02a8 : ''
SDR104_PRESET_IN_S1_H13A0				sdr104_preset_in_s1 			;	// 0x02ac : ''
DDR50_PRESET_IN_S1_H13A0				ddr50_preset_in_s1				;	// 0x02b0 : ''
CAP_REG_IN_S2_H_H13A0					cap_reg_in_s2_h 				;	// 0x02b4 : ''
CAP_REG_IN_S2_L_H13A0					cap_reg_in_s2_l 				;	// 0x02b8 : ''
INIT_PRESET_IN_S2_H13A0 				init_preset_in_s2				;	// 0x02bc : ''
DEFAULT_PRESET_IN_S2_H13A0				default_preset_in_s2			;	// 0x02c0 : ''
HIGH_SPEED_PRESET_IN_S2_H13A0			high_speed_preset_in_s2 		;	// 0x02c4 : ''
SDR12_PRESET_IN_S2_H13A0				sdr12_preset_in_s2				;	// 0x02c8 : ''
SDR25_PRESET_IN_S2_H13A0				sdr25_preset_in_s2				;	// 0x02cc : ''
SDR50_PRESET_IN_S2_H13A0				sdr50_preset_in_s2				;	// 0x02d0 : ''
SDR104_PRESET_IN_S2_H13A0				sdr104_preset_in_s2 			;	// 0x02d4 : ''
DDR50_PRESET_IN_S2_H13A0				ddr50_preset_in_s2				;	// 0x02d8 : ''
SYNC_REG0_H13A0 						sync_reg0						;	// 0x02dc : ''
SYNC_REG1_H13A0 						sync_reg1						;	// 0x02e0 : ''
UINT32									gp_reg4 						;	// 0x02e4 : ''
UINT32									gp_reg5 						;	// 0x02e8 : ''
UINT32									gp_reg6 						;	// 0x02ec : ''
UINT32									gp_reg7 						;	// 0x02f0 : ''
UINT32									gp_reg8 						;	// 0x02f4 : ''
UINT32									gp_reg9 						;	// 0x02f8 : ''
UINT32									gp_reg10						;	// 0x02fc : ''
OSPREY_CTRL7_H13A0						osprey_ctrl7					;	// 0x0300 : ''
OSPREY_CTRL8_H13A0						osprey_ctrl8					;	// 0x0304 : ''
OSPREY_CTRL9_H13A0						osprey_ctrl9					;	// 0x0308 : ''
OSPREY_CTRL10_H13A0 					osprey_ctrl10					;	// 0x030c : ''
OSPREY_CTRL11_H13A0 					osprey_ctrl11					;	// 0x0310 : ''
OSPREY_CTRL12_H13A0 					osprey_ctrl12					;	// 0x0314 : ''
UINT32									gp_reg11						;	// 0x0318 : ''
UINT32									gp_reg12						;	// 0x031c : ''
UINT32									gp_reg13						;	// 0x0320 : ''
UINT32									gp_reg14						;	// 0x0324 : ''
UINT32									gp_reg15						;	// 0x0328 : ''
UINT32									gp_reg16						;	// 0x032c : ''
UINT32									gp_reg17						;	// 0x0330 : ''
OSPREY_STATUS0_H13A0					osprey_status0					;	// 0x0334 : ''
OSPREY_STATUS1_H13A0					osprey_status1					;	// 0x0338 : ''
OSPREY_STATUS2_H13A0					osprey_status2					;	// 0x033c : ''
OSPREY_STATUS3_H13A0					osprey_status3					;	// 0x0340 : ''
UINT32													 __rsvd_07[   1];	// 0x0344
USB2_CTRL0_H13A0						usb2_ctrl0						;	// 0x0348 : ''
USB2_STATUS0_H13A0						usb2_status0					;	// 0x034c : ''
USB2_STATUS1_H13A0						usb2_status1					;	// 0x0350 : ''
UINT32													 __rsvd_08[  21];	// 0x0354 ~ 0x03a4
SSUSB_LOGIC_ANALYZER_TRACE_UPPER_H13A0	ssusb_logic_analyzer_trace_upper;	// 0x03a8 : ''
SSUSB_LOGIC_ANALYZER_TRACE_LOWER_H13A0	ssusb_logic_analyzer_trace_lower;	// 0x03ac : ''
SSUSB_CONTROL_0_H13A0					ssusb_control_0 				;	// 0x03b0 : ''
SSUSB_CONTROL_1_H13A0					ssusb_control_1 				;	// 0x03b4 : ''
SSUSB_HOST_CURRENT_BELT_H13A0			ssusb_host_current_belt 		;	// 0x03b8 : ''
SSUSB_DEBUG_INFO_0_H13A0				ssusb_debug_info_0				;	// 0x03bc : ''
SSUSB_DEBUG_INFO_1_H13A0				ssusb_debug_info_1				;	// 0x03c0 : ''
#endif	/* #ifdef NEVER_DEFINE_THIS */

#ifdef __cplusplus
}
#endif

#endif	/* __CPU_TOP_REG_H13A0_H__ */

/* from 'H13_RegMap_CPU_subsystem_v1.0.csv'  대한민국 표준시 by getregs v2.8 */
