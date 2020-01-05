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


/** @file
 *
 *  main driver implementation for png device.
 *	png device will teach you how to make device driver with new platform.
 *
 *  author		juhee.park
 *  version		1.0
 *  date		2011.12.02
 *  note		Additional information.
 *
 *  @addtogroup lg_png
 *	@{
 */
/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/spinlock.h>

#include "base_types.h"
#include "png_l9_reg.h"
#include "icod_l9_reg.h"
#include "png_impl.h"

#include "l9/linux_platform.h"
#include "l9/linux_irqs.h"
//#include "l9/base_addr_sw_l9.h"

static volatile PNG_REG_T *gpRealRegPNG = NULL;	//real register of PNG
static volatile PNG_REG_T *gpRegPNG = NULL;		//shadow register

static volatile ICOD_REG_T *gpRealRegICOD = NULL;
static volatile ICOD_REG_T *gpRegICOD = NULL;


static int _enableISR(struct PNG_T* pPNG)
{
//	unsigned long irq_flag	= 0;

	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);

	PNG_RdFL(intr_enable);
	PNG_Wr01(intr_enable, filter_done_en, 1);	
	PNG_Wr01(intr_enable, tcopt_err_en, 1);	
	PNG_Wr01(intr_enable, tlen_err_en, 1);	
	PNG_Wr01(intr_enable, tgen_err_en, 1);	
	PNG_Wr01(intr_enable, win_err_en, 1);	
	PNG_Wr01(intr_enable, code_err_en, 1);	
	PNG_Wr01(intr_enable, btype_err_en, 1);	
	PNG_Wr01(intr_enable, len_err_en, 1);	
	PNG_Wr01(intr_enable, row_err_en, 1);	
	PNG_Wr01(intr_enable, ftype_err_en, 1);	
	PNG_WrFL(intr_enable);
	
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);

	return RET_OK;
}

static int _disableISR(struct PNG_T* pPNG)
{
//	unsigned long irq_flag	= 0;

	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);

	PNG_RdFL(intr_enable);
	PNG_Wr01(intr_enable, filter_done_en, 0);	
	PNG_Wr01(intr_enable, tcopt_err_en, 0);	
	PNG_Wr01(intr_enable, tlen_err_en, 0);	
	PNG_Wr01(intr_enable, tgen_err_en, 0);	
	PNG_Wr01(intr_enable, win_err_en, 0);	
	PNG_Wr01(intr_enable, code_err_en, 0);	
	PNG_Wr01(intr_enable, btype_err_en, 0);	
	PNG_Wr01(intr_enable, len_err_en, 0);	
	PNG_Wr01(intr_enable, row_err_en, 0);	
	PNG_Wr01(intr_enable, ftype_err_en, 0);	
	PNG_WrFL(intr_enable);
	
	// // spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);
	return RET_OK;
}

static int _waitISR(struct PNG_T* pPNG)
{
	int ret = 0;

	pPNG->handled = 0;
	ret = wait_event_interruptible_timeout(pPNG->wq_irq, pPNG->handled==1, pPNG->max_decode_timeout);
	if (ret == 0)
	{
		PNG_ERROR("[png] : Timeout[%d]\n", ret);
		return RET_ERROR;
	}
	else
	{
		return RET_OK;
	}
}

static void _doneISR(struct PNG_T* pPNG)
{
	pPNG->handled = 1;
	wake_up_interruptible(&pPNG->wq_irq);
	
	pPNG->changeState(pPNG, LX_PNG_STATE_IDLE);
}

static int _ISRHandler(struct PNG_T* pPNG)
{
	BOOLEAN	decode_done = FALSE;
	UINT32 intr_status = 0;
//	unsigned long irq_flag	= 0;

	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);
	/* read PNG interrupt status */
	PNG_RdFL(intr_status);
	intr_status = PNG_Rd(intr_status);
	PNG_Rd01(intr_status, filter_done, decode_done);	

	/* clear PNG interrupt */
	PNG_Wr(intr_clear, intr_status);	
	PNG_WrFL(intr_clear);
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);
	
	_doneISR(pPNG);	
	
	return RET_OK;
}

static int _reset(struct PNG_T* pPNG)
{
//	unsigned long irq_flag	= 0;
	UINT32	rst_clk_cnt = 0;
	UINT32	status_rst = 0;
	
	pPNG->disableISR(pPNG);

	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);	

	/* reset PNG H/W and wait for completion */
	ICOD_RdFL(sw_rst);
	ICOD_Wr01(sw_rst, sw_rst_png, 1);	
	ICOD_WrFL(sw_rst);
	
	while(1)
	{
		if ( rst_clk_cnt < 600 )	/* I think 600 clk ( 3 usec ) in 5ns/1clk is enough to wait. average wait time is 500 clk ( 2.5 usec ) */
		{
			OS_NsecDelay(5);
		}
		else
		{
			DBG_PRINT_ERROR("[png] too many clk %d for PNG reset. critical error\n", rst_clk_cnt);
			OS_MsecSleep(1);	/* 1 msec means that 200,000 clk !!!!! it's very critical case !! */
		}

		rst_clk_cnt++;

		ICOD_RdFL(intr_status_sw_rst_done);
		ICOD_Rd01(intr_status_sw_rst_done, intr_status_sw_rst_done_png, status_rst);	

		if ( status_rst == 0x1 )
		{
			ICOD_RdFL(intr_clear_sw_rst_done);
			ICOD_Wr01(intr_clear_sw_rst_done, intr_clear_sw_rst_done_png, 1);	
			ICOD_WrFL(intr_clear_sw_rst_done);

//			printk("[png] png reset time = %d clk\n", rst_clk_cnt );
			break;
		}
	}
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);	
	pPNG->enableISR(pPNG);

	return RET_OK;
}

static int _decodeIDAT(struct PNG_T *pPNG, LX_PNG_DECODE_PARAM_T *pRequest)
{
	UINT32 read_base_addr	= 0; 
	UINT32 write_base_addr	= 0; 
	UINT32 read_byte_size	= 0; 
//	unsigned long irq_flag	= 0;

	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);	
	
	/* write header information to png decoder */
	PNG_RdFL(image_info1);
	PNG_Wr01(image_info1, image_height, pRequest->img_hdr.height);	
	PNG_Wr01(image_info1, image_width, pRequest->img_hdr.width);	
	PNG_WrFL(image_info1);
	PNG_RdFL(image_info2);
	PNG_Wr01(image_info2, bitdepth, pRequest->img_hdr.bit_depth);	
	PNG_Wr01(image_info2, color_type, pRequest->img_hdr.color_type);	
	PNG_WrFL(image_info2);

	/* set read memory */
	read_base_addr = pPNG->src_buf_addr + pRequest->offset;
	read_byte_size = pRequest->length;
	PNG_Wr(read_base_addr, read_base_addr);	
	PNG_WrFL(read_base_addr);
	PNG_Wr(read_byte_size, read_byte_size);	
	PNG_WrFL(read_byte_size);
	PNG_RdFL(dma_read_value);
	PNG_Wr01(dma_read_value, read_pri2, 0);	
	PNG_Wr01(dma_read_value, read_pri1, 0);
	PNG_Wr01(dma_read_value, read_delay, 0);
	PNG_Wr01(dma_read_value, read_txid, 0);
	PNG_WrFL(dma_read_value);
	
	/* set write memory */
	write_base_addr= pRequest->out_buf.addr;
	PNG_Wr(write_base_addr, write_base_addr);	
	PNG_WrFL(write_base_addr);
	PNG_RdFL(dma_write_value);
	PNG_Wr01(dma_write_value, write_pri2, 0);	
	PNG_Wr01(dma_write_value, write_pri1, 0);
	PNG_Wr01(dma_write_value, write_delay, 0);
	PNG_Wr01(dma_write_value, write_txid, 0);
	PNG_WrFL(dma_write_value);

	/* set window memory */
	PNG_Wr(read_base_addr_win, pPNG->window_buf_addr);	
	PNG_WrFL(read_base_addr_win);
	PNG_Wr(write_base_addr_win, pPNG->window_buf_addr);	
	PNG_WrFL(write_base_addr_win);
	PNG_RdFL(dma_read_value_win);
	PNG_Wr01(dma_read_value_win, read_pri2, 0);	
	PNG_Wr01(dma_read_value_win, read_pri1, 0);
	PNG_Wr01(dma_read_value_win, read_delay, 0);
	PNG_Wr01(dma_read_value_win, read_txid, 1);
	PNG_WrFL(dma_read_value_win);
	PNG_RdFL(dma_write_value_win);
	PNG_Wr01(dma_write_value_win, write_pri2, 0);	
	PNG_Wr01(dma_write_value_win, write_pri1, 0);
	PNG_Wr01(dma_write_value_win, write_delay, 0);
	PNG_Wr01(dma_write_value_win, write_txid, 1);
	PNG_WrFL(dma_write_value_win);

	/* set filter memory */
	PNG_Wr(read_base_addr_filter, pPNG->filter_buf_addr);	
	PNG_WrFL(read_base_addr_filter);
	PNG_Wr(write_base_addr_filter, pPNG->filter_buf_addr);	
	PNG_WrFL(write_base_addr_filter);
	PNG_RdFL(dma_read_value_filter);
	PNG_Wr01(dma_read_value_filter, read_pri2, 0);	
	PNG_Wr01(dma_read_value_filter, read_pri1, 0);
	PNG_Wr01(dma_read_value_filter, read_delay, 0);
	PNG_Wr01(dma_read_value_filter, read_txid, 2);
	PNG_WrFL(dma_read_value_filter);
	PNG_RdFL(dma_write_value_filter);
	PNG_Wr01(dma_write_value_filter, write_pri2, 0);	
	PNG_Wr01(dma_write_value_filter, write_pri1, 0);
	PNG_Wr01(dma_write_value_filter, write_delay, 0);
	PNG_Wr01(dma_write_value_filter, write_txid, 2);
	PNG_WrFL(dma_write_value_filter);

	/* set drop memory */
	PNG_RdFL(read_byte_drop);
	PNG_Wr01(read_byte_drop, start_read_byte_drop, 0);	
	PNG_Wr01(read_byte_drop, end_read_byte_drop, 0);
	PNG_WrFL(read_byte_drop);
	
	/* begin decoding */
	PNG_RdFL(cmd);
	PNG_Wr01(cmd, start, 1);	
	PNG_WrFL(cmd);
	
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);	
	_waitISR(pPNG);	

	return RET_OK;
}

static void _Init_IOAddrSW(struct PNG_T* pPNG)
{
//	unsigned long irq_flag	= 0;

	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);	
#if 0
	LX_ADDR_SW_CFG_T addr_sw_cfg;

	BASE_L9_GetAddrSwCfg( ADDR_SW_CFG_ICOD, &addr_sw_cfg );

	// Address switching
	ICOD_RdFL(addr_sw_de_sav);
	PNG_Wr(addr_sw_de_sav, addr_sw_cfg.de_sav);	
	ICOD_WrFL(addr_sw_de_sav);
	ICOD_RdFL(addr_sw_cpu_gpu);
	PNG_Wr01(addr_sw_cpu_gpu, addr_sw_cfg.cpu_gpu);	
	ICOD_WrFL(addr_sw_cpu_gpu);
	ICOD_RdFL(addr_sw_cpu_shadow);
	PNG_Wr01(addr_sw_cpu_shadow, addr_sw_cfg.cpu_shadow);	
	ICOD_WrFL(addr_sw_cpu_shadow);
#else
	// Address switching
	ICOD_RdFL(addr_sw_de_sav);
	ICOD_Wr(addr_sw_de_sav, 0x34030210);	
	ICOD_WrFL(addr_sw_de_sav);
	ICOD_RdFL(addr_sw_cpu_gpu);
	ICOD_Wr(addr_sw_cpu_gpu, 0x000200D0);	
	ICOD_WrFL(addr_sw_cpu_gpu);
	ICOD_RdFL(addr_sw_cpu_shadow);
	ICOD_Wr(addr_sw_cpu_shadow, 0x0C010200);	
	ICOD_WrFL(addr_sw_cpu_shadow);

#endif
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);	
}

static int _initISR(struct PNG_T* pPNG)
{
	pPNG->irq_nr = L9_IRQ_ICOD0;
	pPNG->max_decode_timeout = usecs_to_jiffies(5000);

	init_waitqueue_head(&pPNG->wq_irq);

	return RET_OK;
}

int PNG_L9_Init(struct PNG_T* pPNG)
{
	const UINT32 WINDOW_BUFF_SIZE = 0x8000;
	const UINT32 FILTER_BUFF_SIZE = 0x4000;

	const UINT32 PNG_REG_BASE	= L9_IOCD_BASE + 0x0400;
	const UINT32 ICOD_REG_BASE	= L9_IOCD_BASE + 0x0C00;

	if (pPNG->chip == LX_CHIP_REV(L9,A0) ||
		pPNG->chip == LX_CHIP_REV(L9,A1) ||
		pPNG->chip == LX_CHIP_REV(L9,B0) ||
		pPNG->chip == LX_CHIP_REV(L9,B1) )
	{
		pPNG->pPhyBuf = &gMemCfgPng[1];
		pPNG->IO_PNG_mem_addr = PNG_REG_BASE;
		pPNG->IO_PNG_mem_size = sizeof(PNG_REG_T);
		pPNG->IO_ICOD_mem_addr = ICOD_REG_BASE;
		pPNG->IO_ICOD_mem_size = sizeof(ICOD_REG_T);
	}
	else
	{
		PNG_ERROR("Unknown platform setting\n");
		return RET_ERROR;
	}
	
	_initISR(pPNG);

	/* Config Capiblities
	 * L9 PNG H/W bug
     * image width width 512 can't decoded 
     * scanline width = 512*4(RGBA)*8/8(bitdepth/8) = 2048 bytes (2KB)
	 */
	pPNG->caps.possible_op = LX_PNG_OP_FULL;
	pPNG->caps.color_type = LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_GRAYSCALE) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_TRUECOLOR) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_INDEXED) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_GRAYSCALE_ALPHA) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_TRUECOLOR_ALPHA);
	pPNG->caps.interlacing 	= LX_PNG_INTERLACING_DISABLED;
	pPNG->caps.min_width 	= 10;
	pPNG->caps.min_height	= 1;
	pPNG->caps.max_width 	= 512;
	pPNG->caps.max_height	= 2048;

	/* Config Buf memory */
	pPNG->window_buf_addr	= pPNG->pPhyBuf->memory_base;
	pPNG->filter_buf_addr	= pPNG->window_buf_addr + WINDOW_BUFF_SIZE;
	pPNG->src_buf_addr		= pPNG->filter_buf_addr + FILTER_BUFF_SIZE;
	
	pPNG->src_buf_size	= pPNG->pPhyBuf->memory_size - WINDOW_BUFF_SIZE - FILTER_BUFF_SIZE;
	pPNG->src_buf 		= (UINT32*)ioremap(pPNG->src_buf_addr, pPNG->src_buf_size);

	/* Config IO memory */
	gpRealRegPNG = (PNG_REG_T*)ioremap(pPNG->IO_PNG_mem_addr, pPNG->IO_PNG_mem_size);
	pPNG->IO_PNG_mem= (UINT32*)gpRealRegPNG;
	gpRegPNG = (PNG_REG_T*)kzalloc(pPNG->IO_PNG_mem_size, GFP_KERNEL);
	pPNG->IO_PNG_shadow_mem = (UINT32*)gpRegPNG;

	gpRealRegICOD = (ICOD_REG_T*)ioremap(pPNG->IO_ICOD_mem_addr, pPNG->IO_ICOD_mem_size);
	pPNG->IO_ICOD_mem = (UINT32*)gpRealRegICOD;
	gpRegICOD = (ICOD_REG_T*)kzalloc(pPNG->IO_ICOD_mem_size, GFP_KERNEL);
	pPNG->IO_ICOD_shadow_mem = (UINT32*)gpRegICOD;
	_Init_IOAddrSW(pPNG);

	/* Connect PNG fns */
	pPNG->reset				= _reset;
	pPNG->decodeIDAT		= _decodeIDAT;
	pPNG->ISRHandler		= _ISRHandler;
	pPNG->enableISR			= _enableISR;
	pPNG->disableISR		= _disableISR;

    return RET_OK;
}

void PNG_L9_Exit(struct PNG_T* pPNG)
{
#if 0
	/* disconnect PNG fns */
	pPNG->decodeIDAT		= NULL;
	pPNG->ISRHandler		= NULL;
	pPNG->reset				= NULL;

	/* Unconfig IO memory */
	iounmap(pPNG->IO_PNG_mem );
	pPNG->IO_PNG_mem = gpRealRegPNG = NULL;
	kfree(pPNG->shadow_IO_mem);
	pPNG->IO_PNG_shadow_mem = gpRegPNG = NULL;
	pPNG->IO_mem_addr = 0;
	pPNG->IO_mem_size = 0;

	/* Unconfig Buf memory */
	pPNG->window_buf_addr	= 0;
	pPNG->filter_buf_addr	= 0;
	pPNG->src_buf_addr		= 0;
	pPNG->src_buf_size		= 0;
	iounmap(pPNG->src_buf);
	pPNG->src_buf			= NULL;
	
	/* Unconfig Capiblities */
	pPNG->caps.possible_decode = LX_PNG_DECODE_NONE;
	pPNG->caps.max_width = 0;
	pPNG->caps.max_height = 0;
#endif
}

