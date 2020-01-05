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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		raxis.lim
 *  @version	1.0
 *  @date		2012-06-13
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>           /**< printk() */
#include <linux/slab.h>             /**< kmalloc() */
#include <linux/fs.h>               /**< everything\ldots{} */
#include <linux/types.h>            /**< size_t */
#include <linux/fcntl.h>            /**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>           /**< For request_region, check_region etc */
#include <asm/io.h>                 /**< For ioremap_nocache */
#include <linux/workqueue.h>        /**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>
#include "gpu_drv.h"
#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	int		clk;
	UINT32	regval;
	char*	txt;
}
GPU_CLK_REGVAL_T;

typedef struct
{
	int		ratio;
	UINT32	regval;
	char*	txt;
}
GPU_BW_REGVAL_T;

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
static	int	GPU_H13_InitHW	(void);

static	int GPU_H13_SetClock( UINT32 clk );
static	int GPU_H13_SetMemBW ( UINT32 ratio );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static GPU_HW_CTX_T		g_gpu_hw_ctx_h13 =
{
	.default_clk		= 266,	// 266Mhz
	.default_bw_ratio	= 60,	// 60%. make GPU run in slow mode for other devices to run
	.InitHW				= GPU_H13_InitHW,
};

static const GPU_CLK_REGVAL_T gpu_clk_reg_tbl[] =
{
	{ 50, 	0x20000110, " 50Mhz"},
	{ 100,	0x20000120,	"100Mhz (H13A0 default)" },
	{ 200,	0x20000140, "200Mhz"},
	{ 266,	0x10000000, "266Mhz (H13A1 default)" },
};

static const GPU_BW_REGVAL_T gpu_bw_reg_tbl[] =
{
	{ 100,	0x7ff },
	{  90,	0x733 },
	{  80,	0x667 },
	{  70,	0x59b },
	{  60,	0x4cf },
	{  50,	0x403 },
	{  40,	0x337 },
	{  30,	0x26b },
	{  20,	0x19f },
	{  10,	0x0d3 },
	{   0,	0x000 },
};

/*========================================================================================
	Implementation Group
========================================================================================*/
void	GPU_H13_InitCtx	( GPU_HW_CTX_T* ctx )
{
	g_gpu_hw_ctx_h13.priv = 0x0;

	/* copy context */
	memcpy( ctx, &g_gpu_hw_ctx_h13, sizeof(GPU_HW_CTX_T));
}

/** callback : initialize GPU H/W */
static	int	GPU_H13_InitHW	(void)
{
	int	default_clk = g_gpu_hw_ctx.default_clk;
	int	default_bw	= g_gpu_hw_ctx.default_bw_ratio;

#if 1
	if ( lx_chip_rev() < LX_CHIP_REV(H13,A1) )
	{
		default_clk = 100;
	}
#endif

#if 1
	if( lx_chip_rev( ) >= LX_CHIP_REV(H13,B0) )
	{
		default_clk = 297;
	}
#endif

	if( RET_OK != GPU_H13_SetClock(default_clk) )
	{
		printk("GPU CLK Failed..\n");
	}

	if( RET_OK != GPU_H13_SetMemBW( default_bw ) )
	{
		printk("GPU BW Failed..\n");
	}

	return RET_OK;
}

/** setup memory clock */
static	int GPU_H13_SetClock( UINT32 clk )
{
	int		i;
	int		tbl_num = NELEMENTS(gpu_clk_reg_tbl);

	if( lx_chip_rev( ) >= LX_CHIP_REV(H13,B0) )
	{
		if (320 == clk)
		{
			OS_WrReg( 0xc001b00c, 0x0 );
			OS_WrReg( 0xc001b178, 0x0 );
printk("GPU CLK = %d Mhz\n", clk );
			return RET_OK;
		}
		else if (297 == clk)
		{
			OS_WrReg( 0xc001b00c, 0x0 );
			OS_WrReg( 0xc001b178, 0x00080000 );
printk("GPU CLK = %d Mhz\n", clk );
			return RET_OK;
		}
	}

	for ( i=0; i<tbl_num; i++ )
	{
		if ( gpu_clk_reg_tbl[i].clk == clk )
		{
			OS_WrReg( 0xc001b000+0xc, gpu_clk_reg_tbl[i].regval );
printk("GPU CLK = %d Mhz\n", clk );
			return RET_OK;
		}
	}

	return RET_ERROR;
}

/** setup memory bandwidth */
static int GPU_H13_SetMemBW ( UINT32 ratio )
{
	int		i;
	int		tbl_num = NELEMENTS(gpu_bw_reg_tbl);

	for ( i=0; i<tbl_num; i++ )
	{
		if ( gpu_bw_reg_tbl[i].ratio == ratio )
		{
			if( lx_chip_rev( ) >= LX_CHIP_REV(H13,B0) )
			{
				OS_WrReg(0xc000e2f8, gpu_bw_reg_tbl[i].regval );
				OS_WrReg(0xc000e2fc, 0x0);
		
				OS_WrReg(0xc000e3f8, gpu_bw_reg_tbl[i].regval );
				OS_WrReg(0xc000e3fc, 0x0);
			}
			else
			{
				OS_WrReg( 0xc000f110,		gpu_bw_reg_tbl[i].regval );
				OS_WrReg( 0xc000f110+0x80,	gpu_bw_reg_tbl[i].regval );
			}

printk("GPU BW  = %d %% (0x%x)\n", ratio, gpu_bw_reg_tbl[i].regval );

			return RET_OK;
		}
	}

	return RET_ERROR;
}

