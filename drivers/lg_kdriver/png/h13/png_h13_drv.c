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
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	PNG_DEBUG_PRINTK								/* enable all PNG decoding log for dbeug */
#define PNG_USE_STATUS_DUMP_ON_FAILURE					/* dump PNG H/W status on failure */
#undef  PNG_USE_LINE_TIMEOUT							/* detect single line timeout. not implemented yet */

#define	PNG_DONE_ACK_WAIT_TICK	(15+5)					/* PNG default value is 0xf (15 clk) */
#define	PNG_RESET_WAIT_TICK		(32) 					/* 32 tick = 160 ns */

#define	PNG_DECODE_WAIT_MSEC	100						/* default image decoding wait time in msec . retry 5 times */
#define PNG_DECODE_WAIT_RETRY	1						/* retry count when event timeout */
	
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

#include "png_h13_reg.h"
#include "icod_h13_reg.h"
#include "png_impl.h"

#include "h13/linux_platform.h"
#include "h13/linux_irqs.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	PNG_CLK2NSEC(clk)	((clk)*5)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/** H13 platform dependent ctx */
typedef struct
{
	struct
	{
		UINT32		png_done_isr_emul:1,	/* PNG_DONE interrupt is not generated for some PNG image */
					:31;
	}
	hwfix;
}
PNG_H13_PLT_CTX_T;

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
static int PNG_H13_EnableISR	(struct PNG_T* pPNG);
static int PNG_H13_DisableISR	(struct PNG_T* pPNG);
static int PNG_H13_WaitISR		(struct PNG_T* pPNG);
static int PNG_H13_Reset		(struct PNG_T* pPNG);
static int PNG_H13_DecodeIDAT	(struct PNG_T *pPNG, LX_PNG_DECODE_PARAM_T *pRequest);

static int PNG_H13_CheckHW		(struct PNG_T* pPNG, int cnt );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static volatile PNG_REG_T *gpRealRegPNG = NULL;	//real register of PNG
static volatile PNG_REG_T *gpRegPNG = NULL;		//shadow register

static volatile ICOD_REG_T *gpRealRegICOD = NULL;
static volatile ICOD_REG_T *gpRegICOD = NULL;

/*========================================================================================
	Implementation Group
========================================================================================*/
static int PNG_H13_EnableISR(struct PNG_T* pPNG)
{
//	spin_lock_irqsave(&pPNG->IO_lock, irq_flag);

	PNG_H13_PLT_CTX_T* plt_ctx = (PNG_H13_PLT_CTX_T*)pPNG->plt_ctx;

	PNG_RdFL(intr_enable);
	PNG_Wr01(intr_enable, png_done_en, 1);	
//	PNG_Wr01(intr_enable, inflate_done_en, 1);	
	PNG_Wr01(intr_enable, tcopt_err_en, 1);	
	PNG_Wr01(intr_enable, tlen_err_en, 1);	
	PNG_Wr01(intr_enable, tgen_err_en, 1);	
	PNG_Wr01(intr_enable, win_err_en, 1);	
	PNG_Wr01(intr_enable, code_err_en, 1);	
	PNG_Wr01(intr_enable, btype_err_en, 1);	
	PNG_Wr01(intr_enable, len_err_en, 1);	
	PNG_Wr01(intr_enable, row_err_en, 1);	
	PNG_Wr01(intr_enable, ftype_err_en, 1);	
	
	/* raxis.lim (2012/06/15) -- enable read_done interrupt to emulate png_done status */
	if ( plt_ctx->hwfix.png_done_isr_emul ) PNG_Wr01(intr_enable, read_done_en, 1);	
#ifdef PNG_DEBUG_PRINTK
	printk("[png] %s : PNG_DONE emulation mode\n", __F__ );
#endif
//	PNG_Wr01(intr_enable, time_out_en, 1);	

	PNG_WrFL(intr_enable);

	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);

	return RET_OK;
}

static int PNG_H13_DisableISR(struct PNG_T* pPNG)
{
	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);
	PNG_RdFL(intr_enable);
	PNG_Wr01(intr_enable, png_done_en, 0);	
	PNG_Wr01(intr_enable, inflate_done_en, 0);	
	PNG_Wr01(intr_enable, tcopt_err_en, 0);	
	PNG_Wr01(intr_enable, tlen_err_en, 0);	
	PNG_Wr01(intr_enable, tgen_err_en, 0);	
	PNG_Wr01(intr_enable, win_err_en, 0);	
	PNG_Wr01(intr_enable, code_err_en, 0);	
	PNG_Wr01(intr_enable, btype_err_en, 0);	
	PNG_Wr01(intr_enable, len_err_en, 0);	
	PNG_Wr01(intr_enable, row_err_en, 0);	
	PNG_Wr01(intr_enable, ftype_err_en, 0);	
	PNG_Wr01(intr_enable, read_done_en, 0);	
	PNG_Wr01(intr_enable, time_out_en, 0);	
	PNG_WrFL(intr_enable);
	
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);

	return RET_OK;
}

/** wait PNG done or error event 
 *
 */
static int PNG_H13_WaitISR(struct PNG_T* pPNG)
{
	int		retry;
	int 	ret = RET_ERROR;
	UINT32	event	 	= 0x0;
	UINT32	recv_event	= 0x0;
	PNG_H13_PLT_CTX_T* plt_ctx = (PNG_H13_PLT_CTX_T*)pPNG->plt_ctx;

	event = PNG_EV_DECODE_DONE|PNG_EV_DECODE_ERROR|PNG_EV_DECODE_TIMEOUT;

	if ( plt_ctx->hwfix.png_done_isr_emul ) event |= PNG_EV_DECODE_READ_DONE;

	for (retry=0; retry<PNG_DECODE_WAIT_RETRY; retry++ )
	{
		ret = OS_RecvEvent( &(pPNG->ev), event, &recv_event, OS_EVENT_RECEIVE_ANY, PNG_DECODE_WAIT_MSEC );
		if ( ret == RET_OK ) break;
#ifdef PNG_DEBUG_PRINTK
		printk("[png] %s : event timeout !! ev 0x%x - try cnt = %d/%d\n", __F__, recv_event, retry+1, PNG_DECODE_WAIT_RETRY );
#endif
	}

	PNG_CHECK_CODE( ret != RET_OK, goto png_wait_done, "png decoder error (0x%x) detected. timeout.\n", recv_event );

	/* raxis.lim (2012/06/15)
	 * 
	 * H13A0 doesn't generate png_done event for some PNG images. so I should detect png_done by polling 
 	 */
	if ( plt_ctx->hwfix.png_done_isr_emul && (recv_event & PNG_EV_DECODE_READ_DONE ) && !(recv_event & PNG_EV_DECODE_DONE ) )
	{
		int	i;
#ifdef PNG_DEBUG_PRINTK
		printk("[png] %s : png_done emulation start.\n", __F__ );
#endif
		for ( i=0; i< 10; i++ )	/* 10 msec ? */
		{
			PNG_RdFL(ftr_status);
			if ( PNG_Rd00( ftr_status, filter_done ) == 0x1 ) break;
			OS_MsecSleep(1);
		}
		
		PNG_CHECK_CODE( i>=10, ret = RET_ERROR; goto png_wait_done, "png_done not detected.\n");
#ifdef PNG_DEBUG_PRINTK
		printk("[png] %s : png_done emulation completed (ok) cnt = %d \n", __F__, i );
#endif
		ret = RET_OK; /* png decode done */
	}

	/* check HW when decode error */
png_wait_done:
	if ( ret != RET_OK )
	{
		PNG_H13_CheckHW	(pPNG, 1 );
	}

	/* wait some perioid to complete memory I/O */
	OS_NsecDelay(PNG_CLK2NSEC(PNG_DONE_ACK_WAIT_TICK));

	/* wait PNG aftering decoding */
	pPNG->reset(pPNG);
	pPNG->changeState(pPNG, LX_PNG_STATE_IDLE);

	return ret;
}

/** H13 PNG interrupt handler
 *
 */
static int PNG_H13_ISRHandler(struct PNG_T* pPNG)
{
	UINT32 ev = 0x0;
	UINT32 intr_status = 0;
    PNG_H13_PLT_CTX_T* plt_ctx = (PNG_H13_PLT_CTX_T*)pPNG->plt_ctx;

	/* read PNG interrupt status */
	PNG_RdFL(intr_status);
	intr_status = PNG_Rd(intr_status);

#ifdef PNG_DEBUG_PRINTK
	printk("[png] intr status(%d-%d-%d) err(%d-%d-%d-%d %d-%d-%d-%d %d-%d)\n",
			PNG_Rd00(intr_status,png_done), PNG_Rd00(intr_status,inflate_done), PNG_Rd00(intr_status,read_done),
			PNG_Rd00(intr_status,tcopy_err), PNG_Rd00(intr_status,tlen_err), PNG_Rd00(intr_status,tgen_err), PNG_Rd00(intr_status,win_err), 
			PNG_Rd00(intr_status,code_err), PNG_Rd00(intr_status,btype_err), PNG_Rd00(intr_status,len_err), PNG_Rd00(intr_status,row_err),
			PNG_Rd00(intr_status,ftype_err), PNG_Rd00(intr_status,time_out) );
#endif
	/* report DECODE READ DONE */
    ev |= ( plt_ctx->hwfix.png_done_isr_emul && PNG_Rd00(intr_status,read_done) )?  PNG_EV_DECODE_READ_DONE : 0x0;

	/* report DECODE DONE */
	ev |= ( PNG_Rd00(intr_status,png_done))?  PNG_EV_DECODE_DONE : 0x0;

	/* report DECODE ERROR */
	ev |= ( PNG_Rd00(intr_status,tcopy_err) || PNG_Rd00(intr_status,tlen_err) || PNG_Rd00(intr_status,tgen_err)  || 
			PNG_Rd00(intr_status,win_err)   || PNG_Rd00(intr_status,code_err) || PNG_Rd00(intr_status,btype_err) || 
			PNG_Rd00(intr_status,len_err)	|| PNG_Rd00(intr_status,row_err)  || PNG_Rd00(intr_status,ftype_err) )? PNG_EV_DECODE_ERROR : 0x0;
	/* report DECODE TIMEOUT */
	ev |= ( PNG_Rd00(intr_status,time_out) )? PNG_EV_DECODE_TIMEOUT : 0x0;

	/* clear PNG interrupt */
	PNG_Wr(intr_clear, intr_status);	
	PNG_WrFL(intr_clear);

#ifdef PNG_DEBUG_PRINTK
	printk("[png] intr - ev = 0x%x\n", ev );
#endif
	/* report event if event is available */
	if (ev)	OS_SendEvent( &(pPNG->ev), ev);
		
	return RET_OK;
}

/** check current PNG H/W status for debug 
 *
 */
static int PNG_H13_CheckHW		(struct PNG_T* pPNG, int cnt )
{
#ifdef PNG_USE_STATUS_DUMP_ON_FAILURE
	int	i;

	for (i=0; i<cnt; i++ )
	{
		PNG_RdFL(read_base_addr);
		PNG_RdFL(write_base_addr);

		PNG_RdFL(debug_valid_chk);
		PNG_RdFL(debug_rd_addr);
		PNG_RdFL(debug_rd_len);
		PNG_RdFL(debug_wr_addr);
		PNG_RdFL(debug_wr_len);

		PNG_RdFL(fifo_status);
		PNG_RdFL(inflate_status);

		printk("[png] %s - status : 0x%08x, 0x%08x, 0x%08x, 0x%08x, 0x%08x (rd_base 0x%08x, wr_base 0x%08x) fifo: 0x%08x (0x%x 0x%x) inflate: 0x%08x (0x%x 0x%x 0x%x)\n", 
			__F__, 
			PNG_Rd(debug_valid_chk),
			PNG_Rd(debug_rd_addr),
			PNG_Rd(debug_rd_len),
			PNG_Rd(debug_wr_addr),
			PNG_Rd(debug_wr_len),
			PNG_Rd(read_base_addr),
			PNG_Rd(write_base_addr),
			PNG_Rd(fifo_status),
			PNG_Rd00(fifo_status,in_fifo_valid_bits), PNG_Rd00(fifo_status,r_fifo_space),
			PNG_Rd(inflate_status),
			PNG_Rd00(inflate_status,main_state), PNG_Rd00(inflate_status,table_state), PNG_Rd00(inflate_status,inflate_state) );
//		OS_UsecDelay(1);
	}
#endif

	return RET_OK;
}

static int PNG_H13_Reset(struct PNG_T* pPNG)
{
	UINT32	rst_clk_cnt = 0;
	UINT32	rst_err_cnt = 0;

	pPNG->disableISR(pPNG);
	
	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);

	/* reset PNG H/W and wait for completion */
	ICOD_RdFL(sw_rst);
	ICOD_Wr01(sw_rst, sw_rst_png, 1);
	ICOD_WrFL(sw_rst);

	while(1)
	{
		if ( rst_clk_cnt < PNG_CLK2NSEC(PNG_RESET_WAIT_TICK) )
		{
			OS_NsecDelay(1); rst_clk_cnt++;
		}
		else
		{
			if ( !(rst_err_cnt%2000) )
			{
				DBG_PRINT_ERROR("[png] too many clk %d for PNG reset. reset failed. critical error\n", rst_clk_cnt);
			}
			OS_MsecSleep(1);
			rst_clk_cnt += 200000; /* 200,000 clk @ 200 Mhz */
			rst_err_cnt++;
		}

		ICOD_RdFL(intr_status_sw_rst_done);
		if ( ICOD_Rd00( intr_status_sw_rst_done, intr_status_sw_rst_done_png) )
		{
			ICOD_RdFL(intr_clear_sw_rst_done);
			ICOD_Wr01(intr_clear_sw_rst_done, intr_clear_sw_rst_done_png, 1);	
			ICOD_WrFL(intr_clear_sw_rst_done);

			break;
		}
	}
	
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);
	pPNG->enableISR(pPNG);
#ifdef PNG_DEBUG_PRINTK
	printk("[png] png reset time = %d clk\n", rst_clk_cnt );
#endif

	return RET_OK;
}

static int PNG_H13_DecodeIDAT(struct PNG_T *pPNG, LX_PNG_DECODE_PARAM_T *pRequest)
{
	UINT32 read_base_addr	= 0; 
	UINT32 write_base_addr	= 0; 
	UINT32 read_byte_size	= 0; 

	/* clear PNG event before decoding */
//	OS_ClearEvent( &(pPNG->ev) );

#ifdef PNG_DEBUG_PRINTK
	printk("[png] %s: decoding %dx%d, %d:%d len %d \n", __F__, pRequest->img_hdr.width, pRequest->img_hdr.height, pRequest->img_hdr.bit_depth, pRequest->img_hdr.color_type, pRequest->length );
#endif
	
	// spin_lock_irqsave(&pPNG->IO_lock, irq_flag);

#if 0	/* test code. do not use it */
	/* some config */
	PNG_RdFL(inflate_config);
	PNG_Wr01(inflate_config, window_size, 7 );
	PNG_WrFL(inflate_config);

	ICOD_RdFL(flush_wait_cycle);
	ICOD_RdFL(sw_rst_wait_cycle);
	printk("[PNG] %s : info cycle %d %d\n", __F__, ICOD_Rd00(flush_wait_cycle,flush_wait_cycle_png), ICOD_Rd00(sw_rst_wait_cycle,sw_rst_wait_cycle_png) );

	ICOD_Wr01(flush_wait_cycle,flush_wait_cycle_png, 0xf);
	ICOD_Wr01(sw_rst_wait_cycle,sw_rst_wait_cycle_png, 0xf); 
	ICOD_WrFL(flush_wait_cycle);
	ICOD_WrFL(sw_rst_wait_cycle);
#endif

	/* write header information to png decoder */
	PNG_RdFL(image_info1);
	PNG_Wr01(image_info1, image_height, pRequest->img_hdr.height);	
	PNG_Wr01(image_info1, image_width, pRequest->img_hdr.width);	
	PNG_WrFL(image_info1);
	PNG_RdFL(image_info2);
	PNG_Wr01(image_info2, bitdepth, pRequest->img_hdr.bit_depth);	
	PNG_Wr01(image_info2, color_type, pRequest->img_hdr.color_type);	

	/* raxis.lim (2012/06/16) -- set the default output format to little endian ARGB */
	PNG_Wr01(image_info2, out_format, 0x1 );	
	PNG_WrFL(image_info2);

	/* set read memory */
	read_base_addr = pRequest->in_buf.addr + pRequest->offset;
	read_byte_size = pRequest->length;
	PNG_Wr(read_base_addr, read_base_addr);	
	PNG_WrFL(read_base_addr);
	PNG_Wr(read_byte_size, read_byte_size);	
	PNG_WrFL(read_byte_size);
	
	/* set write memory */
	write_base_addr= pRequest->out_buf.addr;
	PNG_Wr(write_base_addr, write_base_addr);	
	PNG_WrFL(write_base_addr);

#ifdef PNG_DEBUG_PRINTK
	printk("read buf 0x%08x len %d -> write buf 0x%8x\n", read_base_addr, read_byte_size, write_base_addr );
#endif

	/* clar event before starting decode */
	OS_ClearEvent( &(pPNG->ev) );
	
	/* begin decoding */
	PNG_RdFL(cmd);
	PNG_Wr01(cmd, start, 1);	
	PNG_WrFL(cmd);
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);

	return PNG_H13_WaitISR(pPNG);
}

static int _initISR(struct PNG_T* pPNG)
{
	pPNG->irq_nr = H13_IRQ_ICOD0;
	pPNG->max_decode_timeout = usecs_to_jiffies(50000000);

	init_waitqueue_head(&pPNG->wq_irq);

	return RET_OK;
}

int PNG_H13_Init(struct PNG_T* pPNG)
{
	const UINT32 WINDOW_BUFF_SIZE = 0;
	const UINT32 FILTER_BUFF_SIZE = 0;

	const UINT32 PNG_REG_BASE	= H13_IOCD_BASE + 0x0400;
	const UINT32 ICOD_REG_BASE	= H13_IOCD_BASE + 0x0C00;
	
//	spin_lock_irqsave(&pPNG->IO_lock, irq_flag);

	if ( !LX_COMP_CHIP(pPNG->chip, LX_CHIP_H13) )
	{
		pPNG->pPhyBuf = &gMemCfgPng[2];
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

	/* Config Capiblities */
	pPNG->caps.possible_op = LX_PNG_OP_FULL;// & LX_PNG_DECODE_PARTIAL;
	pPNG->caps.color_type = LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_GRAYSCALE) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_TRUECOLOR) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_INDEXED) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_GRAYSCALE_ALPHA) | \
							LX_PNG_CAPS_COLOR_TYPE(LX_PNG_COLOR_TRUECOLOR_ALPHA);
	pPNG->caps.interlacing 	= LX_PNG_INTERLACING_DISABLED;
	pPNG->caps.min_width 	= 1;
	pPNG->caps.min_height	= 1;
	pPNG->caps.max_width 	= 2048;
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
	gpRegPNG = (PNG_REG_T*)kmalloc(pPNG->IO_PNG_mem_size, GFP_KERNEL);
	pPNG->IO_PNG_shadow_mem = (UINT32*)gpRegPNG;

	gpRealRegICOD = (ICOD_REG_T*)ioremap(pPNG->IO_ICOD_mem_addr, pPNG->IO_ICOD_mem_size);
	pPNG->IO_ICOD_mem = (UINT32*)gpRealRegICOD;
	gpRegICOD = (ICOD_REG_T*)kmalloc(pPNG->IO_ICOD_mem_size, GFP_KERNEL);
	pPNG->IO_ICOD_shadow_mem = (UINT32*)gpRegICOD;

	/* Connect PNG fns */
	pPNG->reset				= PNG_H13_Reset;
	pPNG->decodeIDAT		= PNG_H13_DecodeIDAT;
	pPNG->ISRHandler		= PNG_H13_ISRHandler;
	pPNG->enableISR			= PNG_H13_EnableISR;
	pPNG->disableISR		= PNG_H13_DisableISR;

	/* create platform context */
	{
		PNG_H13_PLT_CTX_T*	plt_ctx = (PNG_H13_PLT_CTX_T*)OS_Malloc(sizeof(PNG_H13_PLT_CTX_T));

		switch( lx_chip_rev() )
		{
			case LX_CHIP_REV(H13,A0):
			{
				/* TODO */
			}
			break;

			case LX_CHIP_REV(H13,A1):
			{
				/* TODO */
			}
			break;
		
			default:
			{
				/* TODO */
			}
			break;
		}

		/* common attributes */
		plt_ctx->hwfix.png_done_isr_emul = TRUE;

		pPNG->plt_ctx = (void*)plt_ctx;
	}
	
	// spin_unlock_irqrestore(&pPNG->IO_lock, irq_flag);

	OS_InitEvent( &(pPNG->ev) );

    return RET_OK;
}

void PNG_H13_Exit(struct PNG_T* pPNG)
{
	/* do nothing */
}

