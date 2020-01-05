
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
 *
 *  author     	sinchul.jung (sinchul.jung@lge.com)
 *  @version	1.0
 *  @date		2011.10.21
 *
 *  @addtogroup lg1150_base
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef SUPPORT_CACHE_MAP

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>
#include <linux/version.h>

#include "base_types.h"
#include "base_addr_sw_l9.h"
#include "os_util.h"
#include "debug_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*
 *	CASE1, CPU 768M/GPU 128M/SAV 128M
 */
const static LX_ADDR_SW_CFG_T g_address_switch_table_case1_l9[]=
{
	//{de_sav,		cpu_gpu,	cpu_shadow,},
	{0x30000118,	0x10030018,	0x00018110},	// CPU
	{0x30030158,	0x14030018,	0x00018150},	// GPU
	{0x30030158,	0x140300D8,	0x0C018150},	// GFX
	{0x34030158,	0x140300D8,	0x0C018150},	// TE_sdec
	{0x34030158,	0x140300D8,	0x0C018150},	// TE_dvr
	{0x34000198,	0x180300D8,	0x0C018190},	// VENC
	{0x34030218,	0x200300D8,	0x0C018210},	// ICOD
	{0x34000118,	0x100300D8,	0x0C018110},	// AUD0
	{0x34000118,	0x100300D8,	0x0C018110},	// AUD1
	{0x340301D8,	0x1C0300D8,	0x0C0181D0},	// VDEC0
	{0x340301D8,	0x1C0300D8,	0x0C0181D0},	// VDEC1
	{0x34000118,	0x100300D8,	0x0C018110},	// VDEC_mcu
	{0x24030218,	0x20030058,	0x04018210},	// DEa
	{0x28030218,	0x20030058,	0x04018210},	// DEb
	{0x2C030218,	0x20030058,	0x04018210},	// DEc
	{0x30030218,	0x20030058,	0x04018210},	// DEd
	{0x34030218,	0x20030058,	0x04018210},	// DEe
	{0x24000218,	0x20030058,	0x04018210},	// DE_mcu
};


/*
 *	CASE2, CPU 640M/GPU 128M/SAV 256M
 */
const static LX_ADDR_SW_CFG_T g_address_switch_table_case2_l9[]=
{
	//{de_sav,		cpu_gpu,	cpu_shadow,},
	{0x30000110,	0x10028018,	0x00018108},	// CPU
	{0x30030150,	0x14028018,	0x00018148},	// GPU
	{0x30030150,	0x140280D8,	0x0C018148},	// GFX
	{0x34030150,	0x140280D8,	0x0C018148},	// TE_sdec
	{0x34030150,	0x140280D8,	0x0C018148},	// TE_dvr
	{0x34000190,	0x180280D8,	0x0C018188},	// VENC
	{0x34030210,	0x200280D8,	0x0C018208},	// ICOD
	{0x34000110,	0x100280D8,	0x0C018108},	// AUD0
	{0x34000110,	0x100280D8,	0x0C018108},	// AUD1
	{0x340301D0,	0x1C0280D8,	0x0C0181C8},	// VDEC0
	{0x340301D0,	0x1C0280D8,	0x0C0181C8},	// VDEC1
	{0x34000110,	0x100280D8,	0x0C018108},	// VDEC_mcu
	{0x24030210,	0x20028058,	0x04018208},	// DEa
	{0x28030210,	0x20028058,	0x04018208},	// DEb
	{0x2C030210,	0x20028058,	0x04018208},	// DEc
	{0x30030210,	0x20028058,	0x04018208},	// DEd
	{0x34030210,	0x20028058,	0x04018208},	// DEe
	{0x24000210,	0x20028058,	0x04018208},	// DE_mcu
};


/*
 *	CASE3, CPU 640M/GPU 256M/SAV 128M
 */
const static LX_ADDR_SW_CFG_T g_address_switch_table_case3_l9[]=
{

	//{de_sav,		cpu_gpu,	cpu_shadow,},
	{0x30000118,	0x11028010,	0x00010100},	// CPU
	{0x30030158,	0x15028010,	0x00010140},	// GPU
	{0x30030158,	0x150280D0,	0x0C010140},	// GFX
	{0x34030158,	0x150280D0,	0x0C010140},	// TE_sdec
	{0x34030158,	0x150280D0,	0x0C010140},	// TE_dvr
	{0x34000198,	0x190280D0,	0x0C010180},	// VENC
	{0x34030218,	0x210280D0,	0x0C010200},	// ICOD
	{0x34000118,	0x110280D0,	0x0C010100},	// AUD0
	{0x34000118,	0x110280D0,	0x0C010100},	// AUD1
	{0x340301D8,	0x1D0280D0,	0x0C0101C0},	// VDEC0
	{0x340301D8,	0x1D0280D0,	0x0C0101C0},	// VDEC1
	{0x34000118,	0x110280D0,	0x0C010100},	// VDEC_mcu
	{0x24030218,	0x21028050,	0x04010200},	// DEa
	{0x28030218,	0x21028050,	0x04010200},	// DEb
	{0x2C030218,	0x21028050,	0x04010200},	// DEc
	{0x30030218,	0x21028050,	0x04010200},	// DEd
	{0x34030218,	0x21028050,	0x04010200},	// DEe
	{0x24000218,	0x21028050,	0x04010200},	// DE_mcu
};

/*
 *	CASE4, CPU 512M/GPU 256M/SAV 256M
 */
const static LX_ADDR_SW_CFG_T g_address_switch_table_case4_l9[]=
{

	//{de_sav,		cpu_gpu,	cpu_shadow,},
	{0x30000110,	0x00020010,	0x00010100},	// CPU
	{0x30030150,	0x00020010,	0x01010140},	// GPU
	{0x30030150,	0x000200D0,	0x0C010140},	// GFX
	{0x34030150,	0x000200D0,	0x0C010140},	// TE_sdec
	{0x34030150,	0x000200D0,	0x0C010140},	// TE_dvr
	{0x34000190,	0x000200D0,	0x0C010180},	// VENC
	{0x34030210,	0x000200D0,	0x0C010200},	// ICOD
	{0x34000110,	0x000200D0,	0x0C010100},	// AUD0
	{0x34000110,	0x000200D0,	0x0C010100},	// AUD1
	{0x340301D0,	0x000200D0,	0x0C0101C0},	// VDEC0
	{0x340301D0,	0x000200D0,	0x0C0101C0},	// VDEC1
	{0x34000110,	0x000200D0,	0x0C010100},	// VDEC_mcu
	{0x24030210,	0x00020050,	0x04010200},	// DEa
	{0x28030210,	0x00020050,	0x04010200},	// DEb
	{0x2C030210,	0x00020050,	0x04010200},	// DEc
	{0x30030210,	0x00020050,	0x04010200},	// DEd
	{0x34030210,	0x00020050,	0x04010200},	// DEe
	{0x24000210,	0x00020050,	0x04010200},	// DE_mcu
};

/*
 *	CASE5, CPU 1664M/GPU 128M/SAV 256M	(CASE21 in SIC document)
 */
const static LX_ADDR_SW_CFG_T g_address_switch_table_case5_l9[]=
{

	{0x30000130,	0x10068038,	0x00038128},	// CPU
	{0x30030170,	0x14068038,	0x00038168},	// GPU
	{0x30030170,	0x140680F8,	0x0C038168},	// GFX
	{0x34030170,	0x140680F8,	0x0C038168},	// TE_sdec
	{0x34030170,	0x140680F8,	0x0C038168},	// TE_dvr
	{0x340001B0,	0x180680F8,	0x0C0381A8},	// VENC
	{0x34030230,	0x200680F8,	0x0C038228},	// ICOD
	{0x34000130,	0x100680F8,	0x0C038128},	// AUD0
	{0x34000130,	0x100680F8,	0x0C038128},	// AUD1
	{0x340301F0,	0x1C0680F8,	0x0C0381E8},	// VDEC0
	{0x340301F0,	0x1C0680F8,	0x0C0381E8},	// VDEC1
	{0x34000130,	0x100680F8,	0x0C038128},	// VDEC_mcu
	{0x24030230,	0x20068078,	0x04038228},	// DEa
	{0x28030230,	0x20068078,	0x04038228},	// DEb
	{0x2C030230,	0x20068078,	0x04038228},	// DEc
	{0x30030230,	0x20068078,	0x04038228},	// DEd
	{0x34030230,	0x20068078,	0x04038228},	// DEe
	{0x24000230,	0x20068078,	0x04038228},	// DE_mcu
};
/*========================================================================================
	Implementation Group
========================================================================================*/
void BASE_L9_GetAddrSwCfg(int devId, LX_ADDR_SW_CFG_T* addr_sw)
{
	if (devId > ADDR_SW_CFG_MAX)
	{
		DBG_PRINT_ERROR("out of index (%d)\n", devId ); return;
	}

	if (lx_chip_plt() == LX_CHIP_PLATFORM_GP)
	{
		memcpy((void *)addr_sw , (void *)&g_address_switch_table_case4_l9[devId] , sizeof(LX_ADDR_SW_CFG_T) );
	}
	else if (lx_chip_plt() == LX_CHIP_PLATFORM_COSMO)
	{
		memcpy((void *)addr_sw , (void *)&g_address_switch_table_case2_l9[devId] , sizeof(LX_ADDR_SW_CFG_T));
	}
	else
	{
		DBG_PRINT_ERROR("unknown platform !!! 0x%x\n", lx_chip_plt() );
	}
}

/** @} */

