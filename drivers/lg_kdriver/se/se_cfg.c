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





/** @file
 *
 *  se memcfg data. this code is included by base_mem_cfg.c.
 *
 *	NOTE :	TZFW uses fixed address, and SE also uses fixed address.
 *			size of TZFW is 1MBytes, and other 7MBytes are marked by TZ-ASC for Secure Memory for SE.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include "base_types.h"

LX_MEMCFG_T gMemCfgSE =
{
	.name = "se_mem",
	.base = 0x7F600000,
	.size = 0x00200000,
};
EXPORT_SYMBOL(gMemCfgSE);

LX_MEMCFG_T gMemCfgSE_TZFW =
{
	.name = "se_tzfw",
	.base = 0x7F800000,
	.size = 0x00800000,
};
EXPORT_SYMBOL(gMemCfgSE_TZFW);

#if 0
/*
 * The memory header is for COSMO only.
 */
LX_SE_MEM_CFG_T gMemCfgSE = {
	.name = "se_mem",
	.base = 0x2fd00000, /*TARGET_PRODUCT_COSMO*/
	.size = 0x00200000,
};
EXPORT_SYMBOL(gMemCfgSE);

LX_SE_MEM_CFG_T gMemCfgSE_TZFW = {
	.name = "se_tzfw",
	.base = 0x2ff00000, /*TARGET_PRODUCT_COSMO*/
	.size = 0x00100000,
};
EXPORT_SYMBOL(gMemCfgSE_TZFW);
#endif

