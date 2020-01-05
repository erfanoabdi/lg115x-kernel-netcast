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
/@file name : fbdev_module.c
/@description : fbdev ioctl's function
**/

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#define	FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT	20000	/* 20,000 us = 20 ms = 50 fps */

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>		 /**< FBDEV_WARN() */
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/slab.h>			 /**< kmalloc() */
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <asm/io.h>
#include <linux/fs.h>			 /**< everything\ldots{} */
#include <linux/console.h>		 /** acquire_console_sem */
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)
#include <asm/hardware.h>
#else
#include <mach/hardware.h>
#endif

#include <asm/uaccess.h>
#include <asm/system.h>

#include <linux/device.h>

#include <linux/interrupt.h>	 /** irqreturn_t */
#include <linux/irq.h>
#include <asm/irq.h>

#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "gfx_draw.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#ifndef	KDRV_CONFIG_PM
#define FBDEV_suspend		NULL
#define FBDEV_resume		NULL
#else
static int FBDEV_suspend	(struct platform_device *pdev, pm_message_t state);
static int FBDEV_resume		(struct platform_device *pdev);
#endif

#define LCD_PANEL_CLOCK 	180000	 // not be used

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define	PRINTK(fmt,args...)				// printk

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool			is_suspended;
	unsigned int	uiPmFbdevLayerStatus;
}FBDEV_DRVDATA_T;

#endif
/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void		FBDEV_PROC_Init		(void);
extern void		FBDEV_PROC_Cleanup	(void);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/
UINT32				g_fbdev_vsync_cnt		= 0;
int					g_fbdev_vsync_timeout	= FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT;
int    			 	g_fbdev_debug_fd		= -1;
int					g_fbdev_trace_depth		= 0;
int					g_fbdev_vsync_debug		= 1;
int					g_fbdev_osd_freeze		= 0;
FBDEV_FRC_CTRL_T	g_fbdev_frc_ctrl;

FBDEV_HW_CTX_T		g_fbdev_hw_ctx;

#ifdef KDRV_CONFIG_PM
//static unsigned int gPmFbdevLayerStatus = 0;
#endif

static int			g_fbdev_vsync_cnt_on_flip = 1;
module_param_named( fbdev_vsync_cnt_on_flip, g_fbdev_vsync_cnt_on_flip, int, 0644 );

static int			g_fbdev_use_flip_check	= 1;
module_param_named( fbdev_use_flip_check, g_fbdev_use_flip_check, int, 0644 );

static int			g_fbdev_irq_run_flag  = 0;				// isr handler is active ?
static DEFINE_SPINLOCK(g_fbdev_vsync_check_spinlock);		// spinlock for check vsync state
static DECLARE_WAIT_QUEUE_HEAD(g_fbdev_vsync_wq);			// for sync
/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static irqreturn_t 			FBDEV_ISRHandler	(int irq, void *dev_id, struct pt_regs *regs);

static int FBDEV_open(struct fb_info *info , int user);
static int FBDEV_close(struct fb_info *info , int user);
static int FBDEV_ioctl(struct fb_info *info,  unsigned int cmd , unsigned long arg);

static FBDEV_WIN_CTX_T*		FBDEV_InitLayer	 	( char* name, int fb_dev_id );
static void 				FBDEV_InitLinuxFB	( FBDEV_WIN_CTX_T *w, struct fb_var_screeninfo *var, char *id );
static int 					FBDEV_GetConfig 	( FBDEV_WIN_CTX_T *w, LX_FBDEV_CONFIG_T *config);
static int 					FBDEV_SetConfig 	( FBDEV_WIN_CTX_T *w, LX_FBDEV_CONFIG_T *config);
static int					FBDEV_WaitVSync		( int fb_dev_id, int vsync_cnt_on_flip );

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
FBDEV_CTX_T		g_dm_ctx_static;
FBDEV_CTX_T*	g_dm_ctx = &g_dm_ctx_static;

/*========================================================================================
    Implementation Group
========================================================================================*/
/**	update screen !!
 *
 *	@param fb_dev_id [IN] OSD id
 *	@param fb_screen [IN] new screen description
 *	@param b_free_run [IN] if TRUE, OSD doesn't wait for vsync, if FALSE, OSD waits for vsync (default)
 *	@param RET_OK if success, RET_ERROR otherwise
 *
 */
static int	FBDEV_FlipScreen( int fb_dev_id, LX_FBDEV_FB_SCREEN_T* fb_screen, BOOLEAN b_free_run )
{
	// TODO: check

	BOOLEAN b_hdr_update = TRUE;
	BOOLEAN	b_vsync_wait = TRUE;
	FBDEV_WIN_CTX_T* winfo = FBDEV_GetWinCtx( fb_dev_id );

	FBDEV_CHECK_CODE( NULL==winfo, return RET_ERROR, "invalid layer %d\n", fb_dev_id );

	FBDEV_WARN("[fb] %s <begin> osd %d\n", __F__, fb_dev_id );

	if ( g_fbdev_use_flip_check	)
	{
		/* raxis.lim (2011/11/19)
		 * if requst address is the same as current view pointer, DO NOT update header nor wait vsync.
		 * But since we should support the various OSD mode such as UD mode, FRC SEP with L9B0, it is necessary to write OSD header !!
		 * As you know, FBDEV_WriteOSDHeader function have many chip workaround code !!! it is good to enter that function to cope with any situation.
		 *
		 * more code review is needed to check the below code works well with the old L9 chips.
		 */
		if ( winfo->pixel.uiBitmapDataYPTR == fb_screen->phys_addr )
		{
			switch( fb_dev_id )
			{
				case LX_FBDEV_ID_OSD3:	/* cursor */
				{
					if (lx_chip_rev() >= LX_CHIP_REV(L9,B1) ) { b_hdr_update = TRUE; b_vsync_wait = FALSE; }
				}
				break;

				case LX_FBDEV_ID_OSD0:
				case LX_FBDEV_ID_OSD1:
				case LX_FBDEV_ID_OSD2:	/* graphic */
				default:
				{
					if (lx_chip_rev() >= LX_CHIP_REV(L9,B1) ) { b_hdr_update = TRUE; b_vsync_wait = FALSE; }
				}
				break;
			}
		}
	}

	/* update OSD header info every screen update
	 *
	 * @note width & height info is not used !!!
	 */
	if ( b_hdr_update )
	{
		UINT8	curr_bpp = winfo->pixel.bits_per_pixel;

		winfo->pixel.uiBitmapDataYPTR	= fb_screen->phys_addr;
		winfo->pixel.stride				= fb_screen->stride;
		winfo->pixel.bits_per_pixel		= fb_screen->bits_per_pixel;
//		winfo->pixel.eOSDPixDepth		= FBDEV_GetOSDPxlDepth( fb_screen->bits_per_pixel );
//		winfo->pixel.eOSDPixFmt			= FBDEV_GetOSDPxlFmt( fb_screen-bits_per_pixel );

//		winfo->fb_base_phys		 		= fb_screen->phys_addr;
//		winfo->screen_dma				= fb_screen->phys_addr;

//		printk("[fb] osd %d <begin> - bm 0x%08x pitch %d, bpp %d\n", fb_dev_id, winfo->pixel.uiBitmapDataYPTR, winfo->pixel.stride, winfo->pixel.bits_per_pixel );

		if ( curr_bpp != fb_screen->bits_per_pixel )
		{
			//printk("[fb] POSD %d - change endian from %d bpp to %d bpp\n", fb_dev_id,  curr_bpp, fb_screen->bits_per_pixel );
			FBDEV_SetOSDImageEndian( fb_dev_id, fb_screen->bits_per_pixel );
		}

		FBDEV_WriteOSDHeader(&winfo->pixel);
	}

	/* raxis.lim (2012/06/14) -- fbdev supports freerun mode ( non-vsync )  */
	if ( b_vsync_wait == TRUE && b_free_run == FALSE )
	{
		FBDEV_WaitVSync( fb_dev_id, winfo->vsync_cnt_on_flip );
	}

//	printk("[fb] %s osd %d <end> \n", __F__, fb_dev_id );

	return RET_OK;
}

/*========================================================================================
    Implementation Group ( FB interface )
========================================================================================*/
/**
 *      Pans the display.
 *      @var: frame buffer variable screen structure
 *      @info: frame buffer structure that represents a single frame buffer
 *
 *      Pan (or wrap, depending on the `vmode' field) the display using the
 *      `xoffset' and `yoffset' fields of the `var' structure.
 *      If the values don't fit, return -EINVAL.
 *
 *      Returns negative errno on error, or zero on success.
 */
static int FBDEV_pan_display ( struct fb_var_screeninfo* var, struct fb_info* fbinfo )
{
	int rc = 0;
	FBDEV_WIN_CTX_T* winfo = (FBDEV_WIN_CTX_T *)fbinfo->par;
	int		fb_dev_id = winfo->fb_dev_id;
	UINT32	start = 0, offset = 0;

	/* support pan_display only when OSD contains internal FB memory */
	FBDEV_CHECK_CODE( FALSE == g_fbdev_cfg->fb[fb_dev_id].b_use_builtin_fbmem, return RET_OK, "FB(%d) has no FB mem\n", fb_dev_id );

	PRINTK("FB(%d) pan_display \n", fb_dev_id );

	/* ignore OSD update if current OSD is for FRC header emulation */
	if ( fb_dev_id == g_fbdev_frc_ctrl.frc_hdr_emul_dev && g_fbdev_frc_ctrl.b_frc_sep_enable && g_fbdev_frc_ctrl.b_frc_hdr_emul )
	{
		FBDEV_WARN("<warning> ignore OSD(%d) for FRC simul\n", fb_dev_id );
		return RET_OK; /* do nothing */
	}

	/* ignore OSD update if current OSD is freezed !!! */
	if ( winfo->freeze_ctrl_mask & LX_FBDEV_FREEZE_CTRL_MASK_PAN_DISPLAY )
	{
		FBDEV_WARN("<warning> OSD(%d) is freezed. mask=0x%x\n", fb_dev_id, winfo->freeze_ctrl_mask );
		return RET_OK; /* do nothing */
	}

#ifdef FBDEV_FLIP_LOCK
	OS_LockMutex( &winfo->fb_dev_mtx );
#endif

	/* raxis.lim (2012/10/25)
	 * code block to handle input window offset is moved to each header handler function.
	 * ( h13/fbdev_hw_h13a0.c in case of H13 )
	 * but DON'T FORGET var->xoffset, var->yoffset should be processed here becuase this value is
	 * changed in application to handle double buffering
	 */
#if 0
	offset	+= ( var->yoffset + winfo->pixel.input_win.y ) * fbinfo->fix.line_length;
	offset	+= ( var->xoffset + winfo->pixel.input_win.x ) * var->bits_per_pixel / 8;
	start	= (UINT32)fbinfo->fix.smem_start + offset;
#else
	offset	+= var->yoffset * fbinfo->fix.line_length;
	offset	+= var->xoffset * var->bits_per_pixel / 8;
	start	= (UINT32)fbinfo->fix.smem_start + offset;
	start	= LX_CALC_ALIGNED_VALUE(start,4);	/* gMAU requests 16byte aligned address */
#endif

//	printk("[fbkdrv] %s: fb %d, yoffset %d, start addr 0x%x\n", __F__, fb_dev_id, var->yoffset, start );
	{
		BOOLEAN					b_free_run = FALSE;
		LX_FBDEV_FB_SCREEN_T 	fb_screen;
		memset( &fb_screen, 0x0, sizeof(LX_FBDEV_FB_SCREEN_T));

		fb_screen.phys_addr 	= start;
		fb_screen.stride		= fbinfo->fix.line_length; //winfo->pixel.stride;
		fb_screen.bits_per_pixel= fbinfo->var.bits_per_pixel;
//		fb_screen.width			= fbinfo->var.xres;
//		fb_screen.height		= fbinfo->var.yres;
//		fb_screen.pixel_format	= LX_FBDEV_PIXEL_FORMAT_RGB_8888;

		/* raxis.lim (2012/06/14) -- support non-vsync application :(  */
		b_free_run = ( var->sync == (UINT32)-1 )? TRUE: FALSE;
		//printk("[fb] %s : fb[%d] sync %d, free_run %d\n", __F__, fb_dev_id, var->sync, b_free_run );
		rc = FBDEV_FlipScreen( fb_dev_id, &fb_screen, b_free_run );
	}

	FBDEV_CHECK_CODE( RET_OK != rc, /* go */, "[fb%d] error during update_screen\n", fb_dev_id );

#ifdef FBDEV_FLIP_LOCK
	OS_UnlockMutex( &winfo->fb_dev_mtx );
#endif

	return rc;
}

/** check that current setting parameter are correctly or not.
 *
 * @param	struct fb_var_screeninfo *var  , struct fb_info *info
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_check_var(struct fb_var_screeninfo *var, struct fb_info* fbinfo)
{
	const FBDEV_WIN_CTX_T *winfo = (const FBDEV_WIN_CTX_T *)fbinfo->par;
	int	fb_dev_id = winfo->fb_dev_id;

	UINT32	xres, yres, xres_virt, yres_virt;

	switch ( var->bits_per_pixel )
	{
		case 8: case 16: case 32: /* pass */ break;
		default:				  /* not supported */ return -EINVAL;
	}

	/* just check for input size not to be greater than physical max size.
	 * for the safe operation, x coordinate should be aligned by 8 byte ( OSD WORD unit )
	 */
	xres 		= LX_CALC_ALIGNED_VALUE( var->xres, 3 );
	yres 		= var->yres;
	xres_virt 	= LX_CALC_ALIGNED_VALUE( var->xres_virtual, 3 );
	yres_virt 	= var->yres_virtual;

	if ( xres > g_fbdev_cfg->fb[fb_dev_id].max_xres )		xres = g_fbdev_cfg->fb[fb_dev_id].max_xres;
	if ( yres > g_fbdev_cfg->fb[fb_dev_id].max_yres )		yres = g_fbdev_cfg->fb[fb_dev_id].max_yres;
	if ( xres_virt > g_fbdev_cfg->fb[fb_dev_id].max_xres )	xres_virt = g_fbdev_cfg->fb[fb_dev_id].max_xres;
//	if ( yres_virt > g_fbdev_cfg->fb[fb_dev_id].max_yres )	yres_virt = g_fbdev_cfg->fb[fb_dev_id].max_yres;

	/* input size should not be greater than virtual screen size */
	if ( xres > xres_virt)	xres_virt = xres;
	if ( yres > yres_virt)	yres_virt = yres;

	var->xres 			= xres;
	var->yres 			= yres;
	var->xres_virtual 	= xres_virt;
	var->yres_virtual 	= yres_virt;

	return RET_OK;
}

/** parameter setting function.
 *
 * @param	struct fb_info *info
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int	FBDEV_set_par(struct fb_info* fbinfo)
{
	UINT32 pxl_fmt, pxl_depth;
	FBDEV_WIN_CTX_T*	winfo 		= (FBDEV_WIN_CTX_T *)fbinfo->par;
	int					fb_dev_id 	= winfo->fb_dev_id;

#ifdef FBDEV_FLIP_LOCK
	OS_LockMutex( &winfo->fb_dev_mtx );
#endif
	FBDEV_TRACE_BEGIN();

	/* raxis.lim (2010/12/10)
	 * By default, initialize input & output window based on var.xres & var.yres.
	 * [note] FBDEV_SetConfig() fills the real input & output window after calling this function.
	 */
	winfo->pixel.input_win.x = 0;
	winfo->pixel.input_win.y = 0;
	winfo->pixel.input_win.w = fbinfo->var.xres;
	winfo->pixel.input_win.h = fbinfo->var.yres;
	winfo->pixel.output_win.x = 0;
	winfo->pixel.output_win.y = 0;
	winfo->pixel.output_win.w = g_fbdev_cfg->display_width;
	winfo->pixel.output_win.h = g_fbdev_cfg->display_height;

	/* updaet fix info */
	fbinfo->fix.line_length		= (fbinfo->var.xres_virtual * fbinfo->var.bits_per_pixel) / 8;
	fbinfo->fix.smem_len		= PAGE_ALIGN( fbinfo->fix.line_length * fbinfo->var.yres_virtual );

	/* update stride & bits_per_pixel */
	winfo->pixel.stride			= fbinfo->fix.line_length;
	winfo->pixel.bits_per_pixel = fbinfo->var.bits_per_pixel;

#define CHECK_FB_PXLFMT(a,r,g,b)	fbinfo->var.transp.length == (a) && fbinfo->var.red.length == (r) && fbinfo->var.green.length == (g) && fbinfo->var.blue.length == (b)

	/* something.... */
	switch(fbinfo->var.bits_per_pixel)
	{
		case 8:
		{
			pxl_fmt		= LX_FBDEV_PIXEL_FORMAT_RGB_8888;
			pxl_depth	= PIX_DEPTH_8_BPP;
			FBDEV_SetOSDImageEndian( fb_dev_id, 8);
		}
		break;

		case 16:
		{
			if 		( CHECK_FB_PXLFMT(0,5,6,5) ) pxl_fmt = LX_FBDEV_PIXEL_FORMAT_RGB_565;
			if 		( CHECK_FB_PXLFMT(1,5,5,5) ) pxl_fmt = LX_FBDEV_PIXEL_FORMAT_RGB_1555;
			if 		( CHECK_FB_PXLFMT(6,3,4,3) ) pxl_fmt = LX_FBDEV_PIXEL_FORMAT_RGB_6343;
			else 	/* default ARGB4444 */		 pxl_fmt = LX_FBDEV_PIXEL_FORMAT_RGB_4444;

			pxl_depth 	= PIX_DEPTH_16_BPP;
			FBDEV_SetOSDImageEndian( fb_dev_id, 16);
		}
		break;

		case 32:
		default:
			pxl_fmt 	= LX_FBDEV_PIXEL_FORMAT_RGB_8888;
			pxl_depth	= PIX_DEPTH_32_BPP;
			FBDEV_SetOSDImageEndian( fb_dev_id, 32);
		break;
	}

//	winfo->pixel.eOSDPixFmt 	= pxl_fmt;
//	winfo->pixel.eOSDPixDepth	= pxl_depth;

	/* sync data */
	FBDEV_WriteOSDHeader(&winfo->pixel);

	FBDEV_TRACE_END();
#ifdef FBDEV_FLIP_LOCK
	OS_UnlockMutex( &winfo->fb_dev_mtx );
#endif
	return RET_OK;
}

/** module mmap function.
 *
 * @param	int blank ,struct fb_info *info
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_mmap(struct fb_info *fbinfo,  struct vm_area_struct *vma)
{
	FBDEV_WIN_CTX_T *winfo = (FBDEV_WIN_CTX_T *)fbinfo->par;
	int		 fb_dev_id = winfo->fb_dev_id;
	unsigned long start;
	unsigned long len;
	unsigned long off = (vma->vm_pgoff << PAGE_SHIFT);
	int     ret = -1;

	FBDEV_TRACE_BEGIN();

	/* support mmap only when OSD contains internal FB memory */
	FBDEV_CHECK_CODE( FALSE == g_fbdev_cfg->fb[fb_dev_id].b_use_builtin_fbmem, /* pass */, "FB(%d) has no FBMem. Check you config...\n", fb_dev_id );

	if ( g_reg_io_ctx->slkrd_mmap_mask )
	{
		start = ( (fbinfo->fix.smem_start&0x0FFFFFFF)| g_reg_io_ctx->slkrd_mmap_mask );
	}
	else
	{
		start = fbinfo->fix.smem_start;
	}

	len = PAGE_ALIGN((start & ~PAGE_MASK) + g_fbdev_cfg->fb[fb_dev_id].max_size );	/* same result as gMemCfgFbdev.... */

	if ((vma->vm_end - vma->vm_start + off) > len)
	{
		FBDEV_TRACE_END();
		return -EINVAL;
	}

	off += start & PAGE_MASK;
	vma->vm_pgoff = off >> PAGE_SHIFT;
	vma->vm_flags |= VM_IO;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	ret = io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
		vma->vm_end - vma->vm_start,
		vma->vm_page_prot);

	FBDEV_TRACE_END();
	return ret;
}

/**	set color map (palette)
 *
 */
static int FBDEV_setcmap( struct fb_cmap *cmap, struct fb_info *info )
{
	UINT32* palette;
	int i;
	FBDEV_WIN_CTX_T *winfo = (FBDEV_WIN_CTX_T *)info->par;

	FBDEV_PRINT("[FBDV] FBDEV_setcmap\n");

	if( cmap->start + cmap->len > 256 ) return RET_ERROR;

	palette = (UINT32*)OS_Malloc(sizeof(UINT32)*cmap->len);
	FBDEV_CHECK_CODE( NULL == palette, return RET_ERROR, "out of memory\n");


	for( i=0; i<cmap->len; i++)
	{
		palette[i] =((cmap->transp[i]>>8)<<24)| ((cmap->red[i] >>8)<<16)|
					((cmap->green[i] >>8)<< 8)| ((cmap->blue[i]>>8)<< 0);
	}

	/* update palette */
#if 1
	memcpy( (void*)((UINT32*)winfo->osd_pal_base + cmap->start), palette, sizeof(UINT32)*cmap->len );
#else
//	FBDEV_SetPalette( winfo, palette + cmap->start, cmap->len - cmap->start  );
#endif

	OS_Free( palette );

	return 0;
}

/** module blank function.
 *
 * @param	int blank ,struct fb_info *info
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_blank( int blank ,struct fb_info *info)
{
	return 0;
}

static struct fb_ops stL8fb_ops =
{
	.owner 			= THIS_MODULE,
	.fb_open 		= FBDEV_open,
	.fb_release		= FBDEV_close,
	.fb_check_var	= FBDEV_check_var,
	.fb_set_par		= FBDEV_set_par,
//	.fb_setcolreg	= FBDEV_setcolreg,
	.fb_pan_display	= FBDEV_pan_display,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_rotate		= NULL,
	.fb_sync		= NULL,
	.fb_mmap		= FBDEV_mmap,
	.fb_blank		= FBDEV_blank,
	.fb_ioctl		= FBDEV_ioctl,
	.fb_setcmap		= FBDEV_setcmap,
};

/*========================================================================================
    Implementation Group ( FB(OSD) native interface )
========================================================================================*/

/** Get the image configration ( ioctl interface )
 *
 * @param win [IN] osd plane information
 * @param config [OUT] image configuration
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_GetConfig(FBDEV_WIN_CTX_T* winfo, LX_FBDEV_CONFIG_T* config)
{
	int ret = 0;

	memcpy( &config->input_win,  &winfo->pixel.input_win,  sizeof(LX_RECT_T));
	memcpy( &config->output_win, &winfo->pixel.output_win, sizeof(LX_RECT_T));

	config->fbinfo.xres				= winfo->fbinfo.var.xres;
	config->fbinfo.yres				= winfo->fbinfo.var.yres;
	config->fbinfo.xres_virtual		= winfo->fbinfo.var.xres_virtual;
	config->fbinfo.yres_virtual		= winfo->fbinfo.var.yres_virtual;
	config->fbinfo.bits_per_pixel 	= winfo->fbinfo.var.bits_per_pixel;

	config->global_alpha			= winfo->pixel.usGlobalAlpha;
	config->color_key				= winfo->pixel.uiOSDColorKey;
	config->vsync_enable			= winfo->status.b_use_vsync;

	config->color_key_enable		= winfo->pixel.bColorKeyEnable;
	config->global_alpha_enable		= winfo->pixel.bGlobalAlphaEnable;
	config->reverse_screen_enable	= winfo->pixel.bReverseScreenEnable;

	return ret;
}

/** Set the image configration ( ioctl interface )
 *
 * @param	win [IN] osd plane information
 * @param	config [IN image configuration
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_SetConfig(FBDEV_WIN_CTX_T *winfo, LX_FBDEV_CONFIG_T *config)
{
	int ret = 0;

	FBDEV_TRACE_BEGIN();

#ifdef FBDEV_FLIP_LOCK
	OS_LockMutex( &winfo->fb_dev_mtx );
#endif
	FBDEV_WARN("[fb] %s <begin> osd %d\n", __F__, winfo->fb_dev_id );

	/* raxis.lim (2011/11/22) -- DO NOT change the FB information. !!! */
#if 0
	winfo->fbinfo.var.xres			= config->fbinfo.xres;
	winfo->fbinfo.var.yres			= config->fbinfo.yres;
	winfo->fbinfo.var.xres_virtual	= config->fbinfo.xres_virtual;
	winfo->fbinfo.var.yres_virtual	= config->fbinfo.yres_virtual;
	winfo->fbinfo.var.bits_per_pixel= config->fbinfo.bits_per_pixel;

	winfo->pixel.usGlobalAlpha		= config->global_alpha;
	winfo->pixel.uiOSDColorKey		= config->color_key;
	winfo->pixel.bColorKeyEnable	= config->color_key_enable;
	winfo->pixel.bGlobalAlphaEnable	= config->global_alpha_enable;

	/*	update FB value and OSD header */
	FBDEV_set_par ( &winfo->fbinfo );
#endif

	winfo->status.b_use_vsync 		= config->vsync_enable;

    /* raxis.lim (2012/06/20) -- process reverse mode change */
	if ( winfo->pixel.bReverseScreenEnable != config->reverse_screen_enable )
	{
        FBDEV_HW_EVENT_DATA_T evdata;

        memset( &evdata, 0x0, sizeof(FBDEV_HW_EVENT_DATA_T));
        evdata.reverse_screen_change.fb_dev_id = winfo->fb_dev_id;
        evdata.reverse_screen_change.enable = config->reverse_screen_enable;

        FBDEV_ExecFBHWHandler ( FBDEV_HW_EVENT_REVERSE_SCREEN_CHANGE, &evdata );

		winfo->pixel.bReverseScreenEnable = config->reverse_screen_enable;
	}

	/* raxis.lim (2012/01/27) -- update OSD header only value is changed.
	 * without this protection, OSD may flicker when multiple application tries to call FBDEV_WriteOSDHeader
	 */
	if ( winfo->pixel.usGlobalAlpha != config->global_alpha 						||
		 winfo->pixel.bColorKeyEnable != config->color_key_enable					||
		 winfo->pixel.uiOSDColorKey	  != config->color_key							||
		 memcmp( &winfo->pixel.input_win,  &config->input_win,  sizeof(LX_RECT_T)) 	||
         memcmp( &winfo->pixel.output_win, &config->output_win, sizeof(LX_RECT_T)) )
	{
		/* raxis.lim (2012/01/10) -- some platform should support pseudo global alpha level for POSD */
		winfo->pixel.usGlobalAlpha	= config->global_alpha;
		winfo->pixel.bReverseScreenEnable = config->reverse_screen_enable;

		/* raxis.lim (2013/02/05) -- support color key */
		winfo->pixel.uiOSDColorKey		= config->color_key;
		winfo->pixel.bColorKeyEnable	= config->color_key_enable;

		/* if input & output window changed, update osd header again.
		 * [note] winfo->pixel.uiBitmapDataYPTR should be updated after changing input_win.
		 *		  the simplest way to update this value is to call pan_display again.
		 */
		memcpy ( &winfo->pixel.input_win,  &config->input_win,  sizeof(LX_RECT_T));
		memcpy ( &winfo->pixel.output_win, &config->output_win, sizeof(LX_RECT_T));

		FBDEV_WriteOSDHeader(&winfo->pixel);
#if 0
		FBDEV_WaitVSync( winfo->fb_dev_id, winfo->vsync_cnt_on_flip );
#endif
	}

	FBDEV_WARN("[fb] %s <end> osd %d\n", __F__, winfo->fb_dev_id );

#ifdef FBDEV_FLIP_LOCK
	OS_UnlockMutex( &winfo->fb_dev_mtx );
#endif
	FBDEV_TRACE_END();

	return ret;
}

/** wait for vsync
 *
 *
 *
 */
static int	FBDEV_WaitVSync	( int fb_dev_id, int vsync_cnt_on_flip )
{
	UINT32	vsync_usec_tmout;
	int		rc = RET_OK;
	FBDEV_WIN_CTX_T* w = FBDEV_GetWinCtx( fb_dev_id );

	FBDEV_CHECK_CODE( NULL==w, return RET_ERROR, "invalid layer %d\n", fb_dev_id );

	/* if application don't want to wait for the vsync, return function !! */
	if ( vsync_cnt_on_flip ==0 ) return RET_OK;

	/* if the default vsync_cnt is requested, I will wait for one vsync.... */
	if ( vsync_cnt_on_flip < 0 ) vsync_cnt_on_flip = g_fbdev_vsync_cnt_on_flip;

	//printk("[fb %d] vsync cnt %d, usec %d :%d:%d\n", fb_dev_id, vsync_cnt_on_flip, g_fbdev_vsync_timeout * vsync_cnt_on_flip, g_fbdev_cfg->b_use_irq, g_fbdev_cfg->fb[fb_dev_id].b_use_vsync );

	/* calculate the current vsync timeout */
	vsync_usec_tmout = g_fbdev_vsync_timeout * vsync_cnt_on_flip;

	/* this function is valid only when vsync_wait is enabled */
	if ( g_fbdev_cfg->b_use_irq && w->status.b_use_vsync )
	{
		ULONG flags;

        spin_lock_irqsave(&g_fbdev_vsync_check_spinlock, flags);
		w->vsync_cnt = vsync_cnt_on_flip;
		spin_unlock_irqrestore(&g_fbdev_vsync_check_spinlock, flags);

		rc = wait_event_interruptible_timeout (g_fbdev_vsync_wq, w->vsync_cnt == 0, usecs_to_jiffies(vsync_usec_tmout) );

		if ( g_fbdev_vsync_debug )
		{
			FBDEV_CHECK_CODE( rc == 0, /* nop */, "FB[%d] vsync timeout !!!!\n", fb_dev_id );
			FBDEV_CHECK_CODE( rc <  0, /* nop */, "FB[%d] vsync abort by signal !!!!\n", fb_dev_id );
		}
	}

	return RET_OK;
}

/*========================================================================================
    Implementation Group (Ioctl Handler)
========================================================================================*/
/** module ioctl.
 *
 * @param	struct fb_info *info,  unsigned int cmd , unsigned long arg
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_ioctl(struct fb_info *info,  unsigned int cmd , unsigned long arg)
{
	int	rc;
	int ret = RET_ERROR;

	FBDEV_WIN_CTX_T*	w = (FBDEV_WIN_CTX_T *)info->par;
	int					fb_dev_id = w->fb_dev_id;

	FBDEV_CHECK_CODE( !g_fbdev_cfg->fb[fb_dev_id].b_active, /* nop */, "inactive OSD %d\n", fb_dev_id );

	FBDEV_TRACE_BEGIN();

	switch(cmd)
	{
		case FBDEV_IOR_CHIP_REV_INFO:
		{
			ret = RET_OK;
		}
		break;

		case FBDEV_IOR_GET_CFG:
		{
            rc = copy_to_user((void __user *)arg, (void *)g_fbdev_cfg , sizeof(LX_FBDEV_CFG_T));
            FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

            ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOW_SET_PALETTE:
		{
            LX_FBDEV_PALETTE_T*	input_pal = (LX_FBDEV_PALETTE_T*)arg;
			LX_FBDEV_PALETTE_T	fbdev_pal;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			fbdev_pal.palette_data = (UINT32*)OS_Malloc(sizeof(UINT32)*256);
			FBDEV_CHECK_CODE( NULL == fbdev_pal.palette_data, goto func_exit, "out of memory\n");

			rc = __get_user( fbdev_pal.palette_num, &(input_pal->palette_num));
			FBDEV_CHECK_CODE( rc, goto func_exit, "copy error\n");

			rc = copy_from_user( (void*)fbdev_pal.palette_data, (void __user*)input_pal->palette_data, sizeof(UINT32)*input_pal->palette_num );
			FBDEV_CHECK_CODE( rc>0, goto func_exit, "copy error\n");

#if 0
			memcpy( (void*)w->osd_pal_base, fbdev_pal.palette_data, fbdev_pal.palette_num * sizeof(UINT32) );
#else
			FBDEV_SetPalette( w, fbdev_pal.palette_data, fbdev_pal.palette_num );
#endif
			OS_Free( fbdev_pal.palette_data );

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOR_GET_CONFIG:
		{
			LX_FBDEV_CONFIG_T	config;

//			/* support only POSD is enable(active)? */
//			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			FBDEV_GetConfig( w, &config );
			rc = copy_to_user( (void __user *)arg,(void *)&config,sizeof(LX_FBDEV_CONFIG_T));
			FBDEV_CHECK_CODE( rc > 0, , "copy error\n");

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOW_SET_CONFIG:
		{
			LX_FBDEV_CONFIG_T	config;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&config , (void __user *)arg , sizeof(LX_FBDEV_CONFIG_T));
			FBDEV_CHECK_CODE( rc > 0, break, "copy error\n");

			FBDEV_SetConfig( w, &config );

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOR_GET_POSITION:
		{
			LX_POSITION_T cur_pos;

			cur_pos.x 	= w->pixel.output_win.x;
			cur_pos.y 	= w->pixel.output_win.y;

			rc = copy_to_user((void __user *)arg , (void *)&cur_pos , sizeof(LX_POSITION_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOW_SET_POSITION:
		{
			LX_POSITION_T	new_pos;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&new_pos , (void __user *)arg , sizeof(LX_POSITION_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			w->pixel.csr_size.w		= 0;	/* use the full size */
			w->pixel.csr_size.h		= 0;	/* use the full size */
			w->pixel.csr_hotspot.x	= 0;	/* disable hotspot */
			w->pixel.csr_hotspot.y	= 0;	/* disable hotspot */

//			if ( new_pos.x < 0 ) new_pos.x = 0;
//			if ( new_pos.y < 0 ) new_pos.y = 0;

			w->pixel.output_win.x = new_pos.x;
			w->pixel.output_win.y = new_pos.y;

			FBDEV_WriteOSDHeader( &w->pixel );

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOW_SET_CURSOR_POSITION:
		{
			LX_FBDEV_CURSOR_POSITION_T	cursor;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&cursor , (void __user *)arg , sizeof(LX_FBDEV_CURSOR_POSITION_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

//			if ( cursor.pos.x < 0 ) cursor.pos.x = 0;
//			if ( cursor.pos.y < 0 ) cursor.pos.y = 0;

			w->pixel.csr_size.w		= cursor.size.w;
			w->pixel.csr_size.h		= cursor.size.h;
			w->pixel.csr_hotspot.x  = cursor.hotspot.x;
			w->pixel.csr_hotspot.y  = cursor.hotspot.y;
			w->pixel.output_win.x 	= cursor.pos.x;
			w->pixel.output_win.y 	= cursor.pos.y;

			FBDEV_WARN("sz %d,%d hotspot %d,%d pos %d,%d\n", cursor.size.w, cursor.size.h, cursor.hotspot.x, cursor.hotspot.y, cursor.pos.x, cursor.pos.y );
			FBDEV_WriteOSDHeader( &w->pixel );

			/* raxis.lim (2012/01/03) -- when UD mode, all POSD should be merge into the single POSD. so cursor movement should wait for vsync */
			if ( g_fbdev_frc_ctrl.b_frc_UD_enable )
			{
				FBDEV_WaitVSync( fb_dev_id, w->vsync_cnt_on_flip ); /* wait for vsync !! */
			}

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOR_GET_PHY_MEMORY:
		{
			LX_FBDEV_PHY_MEMORY_T phy_mem;
			UINT32	stride	= w->fbinfo.fix.line_length;
			UINT32	len 	= w->fbinfo.fix.smem_len;

			phy_mem.memptr = w->fb_base_phys;
			phy_mem.stride = stride;
			phy_mem.length = len;

			rc = copy_to_user((void __user *)arg , (void *)&phy_mem , sizeof(LX_FBDEV_PHY_MEMORY_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOW_SET_VISIBLE:
		{
			UINT32	enable;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&enable , (void __user *)arg , sizeof(UINT32));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			FBDEV_SetOSDEnable(w->pixel.fb_dev_id, enable);

			/* OSD layer actually will be turned off but after vsync of the time of disabling the lyaer not at that time of disabling it. In curosr, if thw app try to re-draw the new cursor image after disabling it without waiting of vsync, the display would be cracked */
			if ( lx_chip_plt() == LX_CHIP_PLATFORM_COSMO )
			{
				FBDEV_WaitVSync( fb_dev_id, w->vsync_cnt_on_flip ); /* wait for vsync !! */
			}

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOR_GET_VISIBLE:
		{
			UINT32	enable;

			enable = (unsigned int)(FBDEV_GetOSDEnable(w->pixel.fb_dev_id));

			rc = copy_to_user((void __user *)arg , (void *)&enable , sizeof(UINT32));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IOR_GET_FB_STATUS:
		{
			LX_FBDEV_FB_STATUS_T	fb_status;
			memset( &fb_status, 0x0, sizeof(LX_FBDEV_FB_STATUS_T));

			fb_status.b_visible = FBDEV_GetOSDEnable(w->pixel.fb_dev_id);
			fb_status.view_fb_phys_addr = w->pixel.uiBitmapDataYPTR;

			rc = copy_to_user((void __user *)arg , (void *)&fb_status , sizeof(LX_FBDEV_FB_STATUS_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			ret = RET_OK; /* all work done */
		}
		break;

		case FBDEV_IO_WAITFORVSYNC:
		{
			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

#ifdef FBDEV_FLIP_LOCK
			OS_LockMutex( &w->fb_dev_mtx );
#endif
			FBDEV_WaitVSync( fb_dev_id, w->vsync_cnt_on_flip ); /* wait for vsync !! */
#ifdef FBDEV_FLIP_LOCK
			OS_UnlockMutex( &w->fb_dev_mtx );
#endif
			ret = RET_OK; /* all work done. don't detect VSYNC timeout */
		}
		break;

		/*
		 * -1: donot care the vsync. use configuration setting
		 *  0: donot wait vsync.
		 * >0: wait vsyncs.
		 */
		case FBDEV_IOW_WAITFORVSYNC_ON_FLIP:
		{
			rc = get_user ( w->vsync_cnt_on_flip, (int*)arg );
		}
		break;

		case FBDEV_IORW_GET_ZLIST:
		{
			LX_FBDEV_ZLIST_T	zList;

			rc = FBDEV_GetZList( &zList );
			FBDEV_CHECK_CODE( rc != RET_OK, goto func_exit, "can't get zlist\n");

			rc = copy_to_user((void __user *)arg , (void *)&zList , sizeof(LX_FBDEV_ZLIST_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			ret = RET_OK;	/* all work done */
		}
		break;

		case FBDEV_IOW_SET_ZLIST:
		{
			LX_FBDEV_ZLIST_T	zList;

			rc = copy_from_user((void *)&zList , (void __user *)arg , sizeof(LX_FBDEV_ZLIST_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			rc = FBDEV_SetZList( &zList );
			FBDEV_CHECK_CODE( rc != RET_OK, goto func_exit, "can't set zlist\n");

			ret = RET_OK;	/* all work done */
		}
		break;

		case FBDEV_IOW_SET_VIDEO_MIXER_CTRL:
		{
			LX_FBDEV_VIDEO_MIXER_CTRL_T	mix_ctrl;

			rc = copy_from_user((void *)&mix_ctrl , (void __user *)arg , sizeof(LX_FBDEV_VIDEO_MIXER_CTRL_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			rc = FBDEV_SetVideoMixerCtrl(&mix_ctrl);
			FBDEV_CHECK_CODE( rc != RET_OK, goto func_exit, "can't set video mixer\n");

			ret = RET_OK;	/* all work done */
		}
		break;

		case FBDEV_IOW_SET_TRID_CTRL:
		{
			LX_FBDEV_TRID_CTRL_T	trid_ctrl;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&trid_ctrl , (void __user *)arg , sizeof(LX_FBDEV_TRID_CTRL_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			rc = FBDEV_SetTridCtrl( fb_dev_id, &trid_ctrl );
			FBDEV_CHECK_CODE( rc != RET_OK, goto func_exit, "can't init FRC\n");

			ret = RET_OK;	/* all work done */
		}
		break;

		case FBDEV_IOW_SET_CONN_CTRL:
		{
			LX_FBDEV_CONN_CTRL_T	conn_ctrl;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&conn_ctrl , (void __user *)arg , sizeof(LX_FBDEV_CONN_CTRL_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			rc = FBDEV_SetConnCtrl( &conn_ctrl );
			FBDEV_CHECK_CODE( rc != RET_OK, goto func_exit, "can't update the connection\n");

			/* when changing connection mode, reset vsync timoeut to be default */
			g_fbdev_vsync_timeout = FBDEV_DEFAULT_VSYNC_USEC_TIMEOUT;

			ret = RET_OK;	/* all work done */
		}
		break;

        case FBDEV_IOW_SET_OUT_PATH_CTRL:
        {
            LX_FBDEV_OUT_PATH_CTRL_T path_ctrl;

            /* support only POSD is enable(active)? */
            if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

            rc = copy_from_user((void *)&path_ctrl , (void __user *)arg , sizeof(LX_FBDEV_OUT_PATH_CTRL_T));
            FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

            rc = FBDEV_SetOutPathCtrl( fb_dev_id, &path_ctrl );
            FBDEV_CHECK_CODE( rc != RET_OK, goto func_exit, "can't update output path\n");

			ret = RET_OK;	/* all work done */
        }
        break;

		case FBDEV_IOW_SET_FREEZE_CTRL:
		{
            LX_FBDEV_FREEZE_CTRL_T freeze_ctrl;

            rc = copy_from_user((void *)&freeze_ctrl , (void __user *)arg , sizeof(LX_FBDEV_FREEZE_CTRL_T));
            FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

#ifdef FBDEV_FLIP_LOCK
			OS_LockMutex( &w->fb_dev_mtx );
#endif
			/* freeze control doesn't need to be controlled with locking mechaism.
			 * it just updates the current status and application will block or redenr from the next time
	 	 	 */
			if ( freeze_ctrl.b_enable )	w->freeze_ctrl_mask |= freeze_ctrl.ctrl_mask;
			else						w->freeze_ctrl_mask &= ~freeze_ctrl.ctrl_mask;
#ifdef FBDEV_FLIP_LOCK
			OS_UnlockMutex( &w->fb_dev_mtx );
#endif
			ret = RET_OK;	/* all work done */
		}
		break;

		case FBDEV_IOW_SET_VIEW_CTRL:
		{
			LX_FBDEV_VIEW_CTRL_T	view_ctrl;

			rc = copy_from_user((void *)&view_ctrl , (void __user *)arg , sizeof(LX_FBDEV_VIEW_CTRL_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			FBDEV_SetViewCtrl( &view_ctrl );

			ret = RET_OK; /* all work done */
		}
		break;


		case FBDEV_IOW_SET_BACK_IMAGE:
		{
			LX_FBDEV_BACK_IMAGE_T	image;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&image , (void __user *)arg , sizeof(LX_FBDEV_BACK_IMAGE_T));
			FBDEV_CHECK_CODE( rc > 0, goto func_exit, "copy error\n");

			w->pixel.bBackImageEnable 	= image.b_enable;
			w->pixel.back_image_mem		= image.img_phys_mem;

			FBDEV_WriteOSDHeader( &w->pixel );
			FBDEV_WaitVSync( fb_dev_id, 1 );

			ret = RET_OK;	/* all work done */
		}
		break;

		case FBDEV_IOW_FLIP_FB_SCREEN:
		{
			LX_FBDEV_FB_SCREEN_T	fb_screen;

			/* support only POSD is enable(active)? */
			if ( !g_fbdev_cfg->fb[fb_dev_id].b_active ) { ret = RET_OK; break; }

			rc = copy_from_user((void *)&fb_screen , (void __user *)arg , sizeof(LX_FBDEV_FB_SCREEN_T));
			FBDEV_CHECK_CODE( rc > 0, break, "copy error\n");

#ifdef FBDEV_FLIP_LOCK
			OS_LockMutex( &winfo->fb_dev_mtx );
#endif
			FBDEV_FlipScreen( fb_dev_id, &fb_screen, FALSE );
#ifdef FBDEV_FLIP_LOCK
			OS_UnlockMutex( &winfo->fb_dev_mtx );
#endif
			ret = RET_OK;	/* all work done */
		}
		break;

		default:
		{
			/* redundant check but it seems more readable */
			FBDEV_PRINT("[FBDV] IOCTL: unknown IOCTL command %08X\n", cmd );
			FBDEV_TRACE_END();

			ret = -ENOTTY;
		}
	}

func_exit:
	FBDEV_TRACE_END();
	return ret;
}

/*========================================================================================
    Implementation Group ( open & close )
========================================================================================*/
/** module open.
 *
 * @param	struct fb_info *info , int user
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_open(struct fb_info *info , int user)
{
    FBDEV_WIN_CTX_T* win;
	int	ret = RET_ERROR;
	int	fb_dev_id;

	FBDEV_TRACE_BEGIN();

	win = (FBDEV_WIN_CTX_T*)info->par;
	fb_dev_id = win->fb_dev_id;
	FBDEV_CHECK_CODE( !win, goto func_exit, "null parameter\n");

	/* by default, user dont care about vsync. use the configuration setting */
	win->vsync_cnt_on_flip	= -1;
	win->vsync_cnt 			= 0;

#if (CONFIG_LX_BOOT_LOGO==1)
	/* raixs.lim (2012/08/20)
	 * hide bootlogo osd layer to reduce screen garbage during system initialization.
	 * without this code, screen blanks :(
	 */
	if ( fb_dev_id == LX_FBDEV_ID_OSD0 )
	{
		static BOOLEAN b_clr_logo = TRUE;

		if ( b_clr_logo ) { FBDEV_SetOSDEnable( fb_dev_id, FALSE ); b_clr_logo = FALSE; }
	}
#endif

	/*	raxis.lim (2010/11/20) -- register interrupt handler when IRQ enabled */
	if( win->users++ == 0 )
	{
		if ( g_fbdev_cfg->b_use_irq && !(info->state & (1<<1)) )
		{
			if ( !g_fbdev_irq_run_flag )
			{
				int ret = request_irq( g_reg_io_ctx->irq_num, (irq_handler_t)FBDEV_ISRHandler,0,"osd_irq", NULL);
				FBDEV_CHECK_CODE( ret, /* nop */, "request_irq failed\n" );
#if defined(CONFIG_SMP) && defined(CONFIG_GENERIC_HARDIRQS)
//				irq_set_affinity( g_reg_io_ctx->irq_num, cpumask_of(1) );
#endif
				g_fbdev_irq_run_flag = 1;

#ifdef FBDEV_USE_MIXER_INTR
				/* register MIXER INTR !!!. instead, remove each OSD INTR !! */
				FBDEV_SetInterruptEnable(MIXER_INTR,1);
#endif
			}
			info->state |= (1<<1);
		}

		if(is_win(info->fix.id, OSD0))
		{
#ifndef FBDEV_USE_MIXER_INTR
			if ( g_fbdev_cfg->fb[0].b_use_vsync )		FBDEV_SetInterruptEnable(OSD_0_INTR,1);
#endif
#if 0
			{
				static BOOLEAN	b_clr_logo = TRUE;

				if ( b_clr_logo ) /* clear screen */
				{
					int	surf_fd = GFX_AllocARGBSurface( g_fbdev_cfg->fb[0].max_xres, g_fbdev_cfg->fb[0].max_yres * g_fbdev_cfg->fb[0].max_buf_num, win->fb_base_phys );

					if ( surf_fd >= 0 )
					{
						GFX_FillSurface( surf_fd, 0, 0, g_fbdev_cfg->fb[0].max_xres, g_fbdev_cfg->fb[0].max_yres * g_fbdev_cfg->fb[0].max_buf_num, 0xffff0000 );
						GFX_FreeSurface ( surf_fd );

printk("[fb] clear logo screen 0x%x %dx%d\n", win->fb_base_phys, g_fbdev_cfg->fb[0].max_xres, g_fbdev_cfg->fb[0].max_yres * g_fbdev_cfg->fb[0].max_buf_num );
						FBDEV_WriteOSDHeader(&win->pixel);
						b_clr_logo = FALSE;
					}
				}
			}
#endif
			if ( g_fbdev_cfg->fb[0].b_show_on_startup )	FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD0,TRUE);
		}
		else if(is_win(info->fix.id , OSD1))
		{
#ifndef FBDEV_USE_MIXER_INTR
			if ( g_fbdev_cfg->fb[1].b_use_vsync )		FBDEV_SetInterruptEnable(OSD_1_INTR,1);
#endif
			if ( g_fbdev_cfg->fb[1].b_show_on_startup )	FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD1,TRUE);
		}
		else if(is_win(info->fix.id , OSD2))
		{
#ifndef FBDEV_USE_MIXER_INTR
			if ( g_fbdev_cfg->fb[2].b_use_vsync )		FBDEV_SetInterruptEnable(OSD_2_INTR,1);
#endif
			if ( g_fbdev_cfg->fb[2].b_show_on_startup )	FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD2,TRUE);
		}
		else if(is_win(info->fix.id , OSD_CURSOR))
		{
#ifndef FBDEV_USE_MIXER_INTR
			if ( g_fbdev_cfg->fb[3].b_use_vsync )		FBDEV_SetInterruptEnable(CRSR_INTR,1);
#endif
			if ( g_fbdev_cfg->fb[3].b_show_on_startup )	FBDEV_SetOSDEnable(LX_FBDEV_ID_CSR0,TRUE);
		}
		else
		{
			/* do nothing */
		}
	}

	/* generate FB event */
	{
        FBDEV_HW_EVENT_DATA_T evdata;

        memset( &evdata, 0x0, sizeof(FBDEV_HW_EVENT_DATA_T));
        evdata.osd.fb_dev_id = fb_dev_id;

        FBDEV_ExecFBHWHandler ( FBDEV_HW_EVENT_POSD_OPEN, &evdata );
	}

	ret = RET_OK;	/* all work done */
func_exit:
	FBDEV_TRACE_END();
	return ret;
}

/**
 *
 * module close.
 *
 * @param	struct fb_info *info , int user
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_close(struct fb_info *info , int user)
{
	int	ret = RET_ERROR;
    FBDEV_WIN_CTX_T *win;

	/*[TODO] cosmo 에서 왜 _USE_VSYNC 에서 close 를 안하게 하지 ? */

	FBDEV_TRACE_BEGIN();

	win = (FBDEV_WIN_CTX_T*)info->par;
	FBDEV_CHECK_CODE( !win, goto func_exit, "null parameter\n");

	/* raxis.lim (2011/03/29)
	 * DO NOT clear interrupt when FB closed.
	 * the below code seems to stop all interrupts of FB when a single FB device is closed.
	 */
#if 0
	if( --win->users == 0 && (info->state & (1<<1)) )
	{
		/* raxis.lim (2010/11/26) -- OSD irq is never freed */
		// free_irq(IRQ_OSD,NULL);
		info->state &= ~(1<<1);	// info state : 0bit(running, suspend) 1bit(irq enable, disable)
	}

	if(is_win(info->fix.id, OSD0))
	{
		FBDEV_SetInterruptEnable(OSD_0_INTR,FALSE);
		FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD0,FALSE);
	}
	else if(is_win(info->fix.id, OSD1))
	{
		FBDEV_SetInterruptEnable(OSD_1_INTR,FALSE);
		FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD1,FALSE);
	}
	else if(is_win(info->fix.id, OSD2))
	{
		FBDEV_SetInterruptEnable(OSD_2_INTR,FALSE);
		FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD2,FALSE);
	}
	else if(is_win(info->fix.id, OSD_CURSOR))
	{
		FBDEV_SetInterruptEnable(CRSR_INTR,FALSE);
		FBDEV_SetOSDEnable(LX_FBDEV_ID_CSR0,FALSE);
	}
	else
	{

	}
#else
	--win->users;
#endif

	/* generate FB event */
	{
        FBDEV_HW_EVENT_DATA_T evdata;

        memset( &evdata, 0x0, sizeof(FBDEV_HW_EVENT_DATA_T));
        evdata.osd.fb_dev_id = win->fb_dev_id;

        FBDEV_ExecFBHWHandler ( FBDEV_HW_EVENT_POSD_CLOSE, &evdata );
	}

func_exit:
	FBDEV_TRACE_END();

	return ret;
}

#include<mach/platform.h>

/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
 int /*__init*/ FBDEV_probe(struct platform_device *pdev)
{
#ifdef	KDRV_CONFIG_PM
	FBDEV_DRVDATA_T *drv_data;
#endif
	// resource register
	g_dm_ctx->dev = &pdev->dev;

	FBDEV_TRACE_BEGIN();

#ifdef	KDRV_CONFIG_PM
	drv_data = (FBDEV_DRVDATA_T *)kmalloc(sizeof(FBDEV_DRVDATA_T) , GFP_KERNEL);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);
#endif

	/* allocate memory region for register */
	g_dm_ctx->mmio_base_phys	= g_reg_io_ctx->reg_base_addr;
	g_dm_ctx->mmio_size 		= g_reg_io_ctx->reg_size;

	if (FBDEV_InitHardware() < 0)
	{
		FBDEV_PRINT(": cannot map MMIO\n");
		goto func_exit;
	}

	/* initialize 4 OSD layers */
	g_dm_ctx->winfo[0] = FBDEV_InitLayer( OSD0_FBNAME, 0 );	FBDEV_WARN("%s[%d] %p\n", __func__, 0, g_dm_ctx->winfo[0] );
	g_dm_ctx->winfo[1] = FBDEV_InitLayer( OSD1_FBNAME, 1 );	FBDEV_WARN("%s[%d] %p\n", __func__, 1, g_dm_ctx->winfo[1] );
	g_dm_ctx->winfo[2] = FBDEV_InitLayer( OSD2_FBNAME, 2 );	FBDEV_WARN("%s[%d] %p\n", __func__, 2, g_dm_ctx->winfo[2] );
	g_dm_ctx->winfo[3] = FBDEV_InitLayer( OSD3_FBNAME, 3 );	FBDEV_WARN("%s[%d] %p\n", __func__, 3, g_dm_ctx->winfo[3] );
#ifdef FBDEV_USE_DEFAULT_PALETTE

#endif

func_exit:
	FBDEV_TRACE_END();
	return (0);
}

/**	initialize layer at system startup
 *
 *
 */
static FBDEV_WIN_CTX_T*	FBDEV_InitLayer( char* fbname, int fb_dev_id ) //, struct fb_var_screeninfo* default_vinfo )
{
	int	ret = RET_ERROR;
	FBDEV_WIN_CTX_T *winfo;

	/* allocate window context and initialize it */
	winfo = OS_Malloc(sizeof(FBDEV_WIN_CTX_T));
	FBDEV_CHECK_CODE( !winfo, return NULL, "out of memory. can't alloc %s\n", fbname );

	memset(winfo, 0x0, sizeof(FBDEV_WIN_CTX_T));

	winfo->dm					= g_dm_ctx;
	winfo->fb_dev_id			= fb_dev_id;
	winfo->freeze_ctrl_mask		= LX_FBDEV_FREEZE_CTRL_MASK_NONE;

	/* create mutex for single fbdev */
	OS_InitMutex( &winfo->fb_dev_mtx, OS_SEM_ATTR_DEFAULT);

	/* initialize the default vsync ctrl value based on some configuration */
	winfo->status.b_use_vsync	= g_fbdev_cfg->fb[fb_dev_id].b_use_vsync;

	winfo->osd_pal_base_phys 	= gMemCfgFBDev[fb_dev_id].mem_palette_base;
	winfo->osd_pal_size 		= gMemCfgFBDev[fb_dev_id].mem_palette_size ;
	winfo->fb_base_phys 		= gMemCfgFBDev[fb_dev_id].mem_frame_base;
	winfo->screen_dma	 		= gMemCfgFBDev[fb_dev_id].mem_frame_base;
//	winfo->fb_size				= ( g_fbdev_cfg->fb[fb_dev_id].b_use_builtin_fbmem )? g_fbdev_cfg->fb[fb_dev_id].max_size : 0x0 ;
	winfo->fb_size				= g_fbdev_cfg->fb[fb_dev_id].max_size; 
	winfo->osd_header_base_phys = gMemCfgFBHdr[fb_dev_id].mem_header_base;
	winfo->osd_header_size 		= gMemCfgFBHdr[fb_dev_id].mem_header_size;

#ifndef	_DEBUG_
	if (!request_mem_region(winfo->osd_header_base_phys, winfo->osd_header_size, fbname))
	{
		FBDEV_PRINT("%s: can't reserve osd header region\n", fbname);
		goto err_exit;
	}
#endif
	winfo->osd_header_base = (ULONG)ioremap(winfo->osd_header_base_phys, winfo->osd_header_size);
	FBDEV_CHECK_CODE( !winfo->osd_header_base, goto err_exit, "%s: can't ioremap osd hdr\n", fbname );

	winfo->osd_pal_base 	= (ULONG)ioremap(winfo->osd_pal_base_phys, winfo->osd_pal_size * sizeof(UINT32) );
	FBDEV_CHECK_CODE( !winfo->osd_header_base, goto err_exit, "%s: can't ioremap osd pal\n", fbname );

	/* initialize linux fb */
	FBDEV_InitLinuxFB( winfo, FBDEV_GetVarScreenObject(fb_dev_id), fbname );

	/* We reserve one page for the palette, plus the size of the framebuffer. */
	winfo->map_size				= PAGE_ALIGN(winfo->fbinfo.fix.smem_len);

	/* initialize osd header */
	FBDEV_InitCanvas(winfo);

	/* register OSD framebuffer */
	ret = register_framebuffer(&winfo->fbinfo);
	FBDEV_CHECK_CODE( ret < 0, goto err_exit, "%s: fail to reg fbdev\n", fbname );

#if 1
	/* FBDEV_set_par will set pixel_format, pixel_depth ... */
	FBDEV_set_par( &winfo->fbinfo );
#endif
	return winfo;
err_exit:
	if (winfo) FBDEV_CleanupLayer( winfo );

	return NULL;
}

/** initialize 'struct fb_info' of fb device based on the default param
 *	this function initializes 'struct var_screen_info' and 'struct fix_screen info'.
 *
 */
static void FBDEV_InitLinuxFB(FBDEV_WIN_CTX_T* winfo, struct fb_var_screeninfo* default_vinfo, char *id )
{
	int	fb_dev_id = winfo->fb_dev_id;
	struct fb_info *fbinfo = &(winfo->fbinfo);

	FBDEV_PRINT("fb(%d) init FB variable\n", fb_dev_id );

	/* initialize the fb_info structure */
	fbinfo->flags			= FBINFO_DEFAULT;
	fbinfo->fbops			= &stL8fb_ops;
	fbinfo->screen_base		= (char*)(winfo->fb_base);
	fbinfo->pseudo_palette	= winfo->pseudo_palette;
	fbinfo->par				= (void*)winfo;
//	fbinfo->screen_base		= (g_fbdev_cfg->fb[fb_dev_id].b_use_builtin_fbmem)? ioremap(winfo->fb_base_phys, winfo->fb_size) : 0x0;
	fbinfo->screen_base		= ioremap(winfo->fb_base_phys, winfo->fb_size);
	fbinfo->screen_size		= winfo->fb_size;

	/* copy default values */
	memcpy (&fbinfo->var, default_vinfo, sizeof(struct fb_var_screeninfo));

	/* Initialize fixed screeninfo.
	 * The fixed screeninfo cannot be directly specified by the user, but
	 * it may change to reflect changes to the var info.
	 */
	strncpy(fbinfo->fix.id, id, sizeof(fbinfo->fix.id)-1);

	fbinfo->fix.line_length		= (fbinfo->var.xres_virtual * fbinfo->var.bits_per_pixel) / 8;
	fbinfo->fix.smem_start		= winfo->fb_base_phys;
	fbinfo->fix.smem_len		= winfo->fb_size;
	fbinfo->fix.type			= FB_TYPE_PACKED_PIXELS;
	fbinfo->fix.visual			= (fbinfo->var.bits_per_pixel <= 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	fbinfo->fix.xpanstep		= 0;
	fbinfo->fix.ypanstep		= 1;		 // paning enable
	fbinfo->fix.ywrapstep		= 0;
	fbinfo->fix.type_aux		= 0;
	fbinfo->fix.mmio_start		= winfo->dm->mmio_base_phys;
	fbinfo->fix.mmio_len		= winfo->dm->mmio_size;
	fbinfo->fix.accel			= FB_ACCEL_NONE;

	winfo->sdram_address		= 0;

	FBDEV_TRACE_END();
}

/*========================================================================================
    Implementation Group (IRQ)
========================================================================================*/

/** fbdev sync function.
 *
 * @param	void
 * @return	int
 *
 */
int FBDEV_SyncWithVsync(void)
{
	if ( g_fbdev_cfg->b_use_irq )
	{
		int i;
		ULONG flags;

		spin_lock_irqsave(&g_fbdev_vsync_check_spinlock, flags );

		for (i=0; i<FBDEV_MAX_DEVICE; i++)
		{
			if ( g_dm_ctx->winfo[i] && g_dm_ctx->winfo[i]->vsync_cnt > 0)
			{
				g_dm_ctx->winfo[i]->vsync_cnt-- ;
			}
		}
		spin_unlock_irqrestore(&g_fbdev_vsync_check_spinlock, flags);

		wake_up_interruptible_all(&g_fbdev_vsync_wq);
	}

	return 0;
}

/** fbdev interrupt handler.
 *
 * @param	void
 * @return	int
 *
 */
static irqreturn_t FBDEV_ISRHandler(int irq, void *dev_id, struct pt_regs *regs)
{
	/* read current ISR status */
	UINT32	intr_status = FBDEV_GetInterruptStatus(ALL_INTR);
	PRINTK("^c^[fb] intr_status = 0x%x\n", intr_status );

#ifdef FBDEV_USE_AUTO_VSYNC
	{
		static	int		b_first_vsync 	= 1;
		static	UINT64	start_tick;

		if ( b_first_vsync )
		{
			b_first_vsync = 0; start_tick = OS_GetMsecTicks();
		}
		else
		{
			if ( ++g_fbdev_vsync_cnt & 0xff00 ) /* vsync count >= 256 */
			{
				UINT64	curr_tick = OS_GetMsecTicks();
				int		diff_tick = (int)(curr_tick-start_tick);

				/* if DVB mode (50Hz) , ideal diff_tick will be 20.000 ms * 256 = 5120
				 * if DVB mode (48Hz) , ideal diff_tick will be 20.833 ms * 256 = 5333
				 * If UD  mode (30Hz) , local diff_tick will be 33.333 ms * 256 = 8532 ?
				 * else 60Hz
				 */
				 g_fbdev_vsync_timeout = (diff_tick>=8000)? 33333 : (diff_tick>=5300)? 20832: (diff_tick>=5000)? 19999: (diff_tick>=2200)? 16666: 8333;

				if ( g_fbdev_vsync_debug )
				{
					FBDEV_WARN("[FB] vsync_tm %d us (diff %d ms/256). Linux HZ=%d\n", g_fbdev_vsync_timeout, diff_tick, HZ );
				}
				start_tick = curr_tick;
				g_fbdev_vsync_cnt = 0;
			}
		}
	}
#else
	{
		if ( ++g_fbdev_vsync_cnt & 0xff00 ) g_fbdev_vsync_cnt = 0; /* vsync count >= 256 */
	}
#endif

	/* ignore handler when there is not any OSD interrupt */
	if( intr_status == 0 ) goto func_exit;

	/* raxis.lim (2010/11/20) -- ignore interrupt service when FB doesn't use IRQ */
	if ( !g_fbdev_cfg->b_use_irq )
	{
		FBDEV_SetInterruptClear( ALL_INTR ); goto func_exit;
	}

#ifndef FBDEV_USE_MIXER_INTR
	if( intr_status & (1<<OSD_0_INTR) )
	{
		FBDEV_SetInterruptClear( OSD_0_INTR );
	}

	if( intr_status & (1<<OSD_1_INTR) )
	{
		FBDEV_SetInterruptClear(OSD_1_INTR );
	}

	if( intr_status & (1<<OSD_2_INTR) )
	{
		FBDEV_SetInterruptClear(OSD_2_INTR );
	}

	if( intr_status & (1<<OSD_3_INTR) )
	{
		FBDEV_SetInterruptClear( CRSR_INTR );
	}
	if( intr_status & (1<<MIXER_INTR_EXT) )		/* ??? */
	{
		FBDEV_SetInterruptClear( MIXER_INTR_EXT );
	}

#endif
	if( intr_status & (1<<MIXER_INTR) )
	{
//		printk("[fb] mixer irq ...\n");
		FBDEV_SetInterruptClear( MIXER_INTR );
		FBDEV_ISRTickHandler(g_fbdev_vsync_cnt);/* call chip dependent ISR */
		FBDEV_SyncWithVsync();					/* call ISR callback */
	}

func_exit:
	return IRQ_HANDLED;
}

/*========================================================================================
    Implementation Group
========================================================================================*/

/**
 *
 * module remove function. this function will be called in insmod fbdev module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int  FBDEV_remove(struct platform_device *pdev)
{
	FBDEV_PRINT("released\n");

	return 0;
}


/**
 *
 * module remove function. this function will be called in insmod fbdev module.
 *
 * @param	struct device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void  FBDEV_release(struct device *dev)
{
	FBDEV_PRINT("released\n");

}

/*
 *	L8 fbdev platform device structure
 */
static struct platform_device fbdev_plt_device =
{
	.name = MODULE_NAME,
	.id = 0,
	.id = -1,
	.dev =
	{
		.coherent_dma_mask	= 0xffffffff,
		.release 			= FBDEV_release,
	},
};

/*
 *	L8 fbdev platform driver structure
 */
static struct platform_driver fbdev_plt_driver =
{
	.probe		= FBDEV_probe,
	.suspend	= FBDEV_suspend,
	.remove     = FBDEV_remove,
	.resume		= FBDEV_resume,
	.driver		=
	{
		.name   = MODULE_NAME,
	},
};

/**
 *
 *
 *
 * @param
 * @return	int 0 : OK , -1 : NOT OK
 *
 */

#ifndef MODULE
/*
 * Only necessary if your driver takes special options,
 * otherwise we fall back on the generic fb_setup().
 */
int __init FBDEV_setup(char *options)
{
	/* Parse user speficied options (`video=l8fb:') */
	return RET_OK;
}
#endif

/*========================================================================================
    Implementation Group
========================================================================================*/
/* initialize all variable of FB device */
static void FBDEV_InitVar ( void )
{
	memset( &g_fbdev_frc_ctrl,  0x0, sizeof(FBDEV_FRC_CTRL_T));		/* clear FRC */
	memset( &g_fbdev_hw_ctx, 	0x0, sizeof(FBDEV_HW_CTX_T));		/* clear HW Ctx */
	memset( g_dm_ctx, 			0x0, sizeof(FBDEV_CTX_T));			/* celar dm_ctx */
}

/** initialize basic configuration for FB device.
 *	[note] this function is called before the real device intialization
 *
 */
void	FBDEV_PreInit	( void )
{
	FBDEV_InitVar	( );	/* initialize variable */
	FBDEV_InitHWCtx	( );	/* initialize HW context */
	FBDEV_InitCfg	( );	/* initialize configuration */
}

/** module initial function. this function will be called in insmod fbdev module.
 *
 * @param	void
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int  FBDEV_Init(void)
{
#if 1
	/* raxis.lim (2012/05/08)
	 * I decided to support the dynamic alloacation for FBDEV framebuffer memory.
	 * so gpFBdevRegCfg->frame_base_addr can't be determined before device memory allocation.
	 *
	 * [TODO] REWRITE !!
	 */
	if ( g_reg_io_ctx->frame_base_addr == 0x0 )
	{
		g_reg_io_ctx->frame_base_addr = gMemCfgFBDev[0].mem_frame_base;
	}

	/* application needs FB memory information
	 *
	 * [TODO] REWRITE !!
	 */
	g_fbdev_cfg->fb_mem_base = g_reg_io_ctx->frame_base_addr;
	g_fbdev_cfg->fb_mem_size = g_reg_io_ctx->frame_base_size;
#endif

	/* Get the handle of debug output for fbdev device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_fbdev_debug_fd = DBG_OPEN( FBDEV_MODULE );
	if(g_fbdev_debug_fd < 0) return RET_ERROR;

	OS_DEBUG_EnableModule ( g_fbdev_debug_fd );

//	OS_DEBUG_EnableModuleByIndex ( g_fbdev_debug_fd, 0, DBG_COLOR_NONE );	/* print */
//	OS_DEBUG_EnableModuleByIndex ( g_fbdev_debug_fd, 1, DBG_COLOR_CYAN );	/* trace */
//	OS_DEBUG_EnableModuleByIndex ( g_fbdev_debug_fd, 2, DBG_COLOR_YELLOW);	/* warn  */
	OS_DEBUG_EnableModuleByIndex ( g_fbdev_debug_fd, 3, DBG_COLOR_RED );	/* error */

#ifndef MODULE
	{
		char *option = NULL;

		/* name register */
		if(fb_get_options("lg115xfb", &option) )
		{
			FBDEV_PRINT("Error fb_get_options\n");
			return -ENODEV;
		}

		FBDEV_setup(option);
	}
#endif
	if(platform_driver_register(&fbdev_plt_driver) < 0)
	{
		FBDEV_PRINT("failed to register fbdev\n");
	}
	else
	{
		FBDEV_PRINT("register done\n");

		if(platform_device_register(&fbdev_plt_device))
		{
			platform_driver_unregister(&fbdev_plt_driver);
		}
		else
		{
			FBDEV_PRINT("device registerd\n");
		}
	}

	FBDEV_PROC_Init();

	return 0;
}

/**
 *
 * module remove function. this function will be called in rmmod fbdev module.
 *
 * @param	void
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
void  FBDEV_Cleanup(void)
{
	struct fb_info *info;

	FBDEV_PROC_Cleanup();

	// register memory release
	FBDEV_ExitHardware();

	info = &g_dm_ctx->winfo[0]->fbinfo;
	unregister_framebuffer(info);
	info = &g_dm_ctx->winfo[1]->fbinfo;
	unregister_framebuffer(info);
	info = &g_dm_ctx->winfo[2]->fbinfo;
	unregister_framebuffer(info);
	info = &g_dm_ctx->winfo[3]->fbinfo;
	unregister_framebuffer(info);

	// header&palette  memory release
	FBDEV_CleanupLayer(g_dm_ctx->winfo[0]);
	FBDEV_CleanupLayer(g_dm_ctx->winfo[1]);
	FBDEV_CleanupLayer(g_dm_ctx->winfo[2]);
	FBDEV_CleanupLayer(g_dm_ctx->winfo[3]);

	platform_driver_unregister(&fbdev_plt_driver);
	platform_device_unregister(&fbdev_plt_device);

	FBDEV_PRINT("INFO(FBDEV_Exit)-  removing module\n");
}

/*========================================================================================
    Implementation Group (suspend/resume)
========================================================================================*/

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_suspend(struct platform_device *pdev, pm_message_t state)
{
	FBDEV_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code
	FBDEV_RunSuspend( );

	drv_data->uiPmFbdevLayerStatus = 0;
#if 1
	if(FBDEV_GetOSDEnable(LX_FBDEV_ID_OSD0) == 1)
		drv_data->uiPmFbdevLayerStatus |= (1<<0);

	if(FBDEV_GetOSDEnable(LX_FBDEV_ID_OSD1) == 1)
		drv_data->uiPmFbdevLayerStatus |= (1<<1);

	if(FBDEV_GetOSDEnable(LX_FBDEV_ID_OSD2) == 1)
		drv_data->uiPmFbdevLayerStatus |= (1<<2);

	if(FBDEV_GetOSDEnable(LX_FBDEV_ID_CSR0) == 1)
		drv_data->uiPmFbdevLayerStatus |= (1<<3);

	// endianess
	drv_data->is_suspended = 1;
#endif
	FBDEV_PRINT("[%s] done suspend\n", FBDEV_MODULE);

	return 0;
}

/**
 *
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FBDEV_resume(struct platform_device *pdev)
{
	FBDEV_DRVDATA_T *drv_data;
	FBDEV_WIN_CTX_T *fake_window;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;
	// add here the resume code

	FBDEV_RunResume( );

	// for test
	FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD0 , 0);
	FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD1 , 0);
	FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD2 , 0);
	FBDEV_SetOSDEnable(LX_FBDEV_ID_CSR0 , 0);

	fake_window = (FBDEV_WIN_CTX_T *)kmalloc(sizeof(FBDEV_WIN_CTX_T) , GFP_KERNEL);

	// restore canvas
	memcpy((void *)fake_window , (void *)g_dm_ctx->winfo[0] , sizeof(FBDEV_WIN_CTX_T));
	FBDEV_InitCanvas(fake_window);
	memcpy((void *)fake_window , (void *)g_dm_ctx->winfo[1] , sizeof(FBDEV_WIN_CTX_T));
	FBDEV_InitCanvas(fake_window);
	memcpy((void *)fake_window , (void *)g_dm_ctx->winfo[2] , sizeof(FBDEV_WIN_CTX_T));
	FBDEV_InitCanvas(fake_window);
	memcpy((void *)fake_window , (void *)g_dm_ctx->winfo[3] , sizeof(FBDEV_WIN_CTX_T));
	FBDEV_InitCanvas(fake_window);

	FBDEV_set_par(&g_dm_ctx->winfo[0]->fbinfo);
	FBDEV_set_par(&g_dm_ctx->winfo[1]->fbinfo);
	FBDEV_set_par(&g_dm_ctx->winfo[2]->fbinfo);
	FBDEV_set_par(&g_dm_ctx->winfo[3]->fbinfo);

	// restore osd configuration
	FBDEV_WriteOSDHeader(&g_dm_ctx->winfo[0]->pixel);
	FBDEV_WriteOSDHeader(&g_dm_ctx->winfo[1]->pixel);
	FBDEV_WriteOSDHeader(&g_dm_ctx->winfo[2]->pixel);
	FBDEV_WriteOSDHeader(&g_dm_ctx->winfo[3]->pixel);

	// osd enable
	if(drv_data->uiPmFbdevLayerStatus & (1<<0))
		FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD0 , 1);
	if(drv_data->uiPmFbdevLayerStatus & (1<<1))
		FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD1 , 1);
	if(drv_data->uiPmFbdevLayerStatus & (1<<2))
		FBDEV_SetOSDEnable(LX_FBDEV_ID_OSD2 , 1);
	if(drv_data->uiPmFbdevLayerStatus & (1<<3))
		FBDEV_SetOSDEnable(LX_FBDEV_ID_CSR0 , 1);

	// endianess
	drv_data->is_suspended = 0;
	FBDEV_PRINT("[%s] done resume\n", FBDEV_MODULE);

	kfree(fake_window);
	return 0;
}
#endif

/**
 *	Declaration of the init and exit functions
 */

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",FBDEV_Init);
#else
module_init(FBDEV_Init);
#endif
module_exit(FBDEV_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("FBDEV driver");
MODULE_LICENSE("GPL");
#endif

