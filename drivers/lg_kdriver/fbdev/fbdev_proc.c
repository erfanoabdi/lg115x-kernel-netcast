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
 *  Linux proc interface for fbdev device.
 *	fbdev device will teach you how to make device driver with new platform.
 *
 *  author		raxis
 *  version		1.0 
 *  date		2010.02.01
 *  note		Additional information. 
 *
 *  @addtogroup lg1150_fbdev 
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_drv.h"
#include "gfx_draw.h"
#include "proc_util.h"
#include <linux/seq_file.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define LG1150_OSD_BASE 0xc0017A00

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_COMMAND,
	PROC_ID_OSD_INFO,
	PROC_ID_REG_DUMP,
	PROC_ID_SA,
	PROC_ID_MUX,
	PROC_ID_VIEW_CTRL,
	PROC_ID_SYNC_CTRL,
	PROC_ID_REG_RD,
	PROC_ID_REG_WR,
	PROC_ID_DATA_RD,
	PROC_ID_OSD_FREEZE,
	PROC_ID_OSD_CLEAR,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int FBDEV_SetZList ( LX_FBDEV_ZLIST_T* zList );
extern int FBDEV_GetZList ( LX_FBDEV_ZLIST_T* zList );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void	_FBDEV_PROC_PrintOSDInfo ( struct seq_file *m );
static void	_FBDEV_PROC_DumpRegs ( struct seq_file *m );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int osdinfo_proc_print(struct seq_file *m, void *v)
{
	_FBDEV_PROC_PrintOSDInfo ( m );
	return 0;
}

static int osdinfo_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, osdinfo_proc_print, NULL);
}

const struct file_operations osdinfo_proc_fops = {
    .open       = osdinfo_proc_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static int regdump_proc_print(struct seq_file *m, void *v)
{
	_FBDEV_PROC_DumpRegs( m );
	return 0;
}

static int regdump_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, regdump_proc_print, NULL);
}

const struct file_operations regdump_proc_fops = {
    .open       = regdump_proc_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};

static OS_PROC_DESC_TABLE_T	_g_fbdev_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "command",	PROC_ID_COMMAND , OS_PROC_FLAG_WRITE },
	{ "osdinfo",	PROC_ID_OSD_INFO, OS_PROC_FLAG_READ | OS_PROC_FLAG_FOP, (void*)&osdinfo_proc_fops },
	{ "regdump",	PROC_ID_REG_DUMP, OS_PROC_FLAG_READ | OS_PROC_FLAG_FOP, (void*)&regdump_proc_fops },
	{ "sa",			PROC_ID_SA		, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },	
	{ "mux",		PROC_ID_MUX		, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ "viewctrl",	PROC_ID_VIEW_CTRL,OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ "syncctrl",	PROC_ID_SYNC_CTRL,OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ "reg_rd",		PROC_ID_REG_RD	, OS_PROC_FLAG_WRITE },
	{ "reg_wr",		PROC_ID_REG_WR	, OS_PROC_FLAG_WRITE },
	{ "data_rd",	PROC_ID_DATA_RD	, OS_PROC_FLAG_WRITE },
	{ "freeze",		PROC_ID_OSD_FREEZE, OS_PROC_FLAG_WRITE },
	{ "clear",		PROC_ID_OSD_CLEAR,  OS_PROC_FLAG_WRITE },
	{ NULL, 		PROC_ID_MAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/

/*
 * read_proc implementation of fbdev device 
 *
*/
static int	_FBDEV_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = sprintf( buffer, "%s\n", "raxis.lim@lge.com" );
		}
		break;	

		case PROC_ID_MUX:
		{
			LX_FBDEV_ZLIST_T	zlist;
			int len = 0;

			char* posd_name[4] = {"OSD0", "OSD1", "OSD2 (Not Used)", "VIDEO" };

			zlist.path = LX_FBDEV_PATH_LEFT;
			FBDEV_GetZList( &zlist );
			len += sprintf( buffer + len, "LEFT\n");
			len += sprintf( buffer + len, "[0] %d (%s)\n", zlist.order[0], posd_name[zlist.order[0]] );
			len += sprintf( buffer + len, "[1] %d (%s)\n", zlist.order[1], posd_name[zlist.order[1]] );
			len += sprintf( buffer + len, "[2] %d (%s)\n", zlist.order[2], posd_name[zlist.order[2]] );

			zlist.path = LX_FBDEV_PATH_RIGHT;
			FBDEV_GetZList( &zlist );
			len += sprintf( buffer + len, "RIGHT\n");
			len += sprintf( buffer + len, "[0] %d (%s)\n", zlist.order[0], posd_name[zlist.order[0]] );
			len += sprintf( buffer + len, "[1] %d (%s)\n", zlist.order[1], posd_name[zlist.order[1]] );
			len += sprintf( buffer + len, "[2] %d (%s)\n", zlist.order[2], posd_name[zlist.order[2]] );
			len += sprintf( buffer + len, "\n");
			len += sprintf( buffer + len, "[usage] echo path order0, order1, order2 > /proc/lg/fbdev/mux\n" );
			len += sprintf( buffer + len, "        path      : 'l' for LEFT, 'r' for RIGHT\n");
			len += sprintf( buffer + len, "        order0,1,2: order0 is topmost, order1 is center, order2 is bottom\n");

			ret = len;
		}
		break;

		case PROC_ID_SA:
		{
			int len = 0;
//			len += sprintf( buffer + len, "[0] sa = %x\n", g_fbdev_reg_l8->osd0_sc_cfg.osd0_sc_bc_sa );
//			len += sprintf( buffer + len, "[1] sa = %x\n", g_fbdev_reg_l8->osd1_sc_cfg.osd1_sc_bc_sa );
//			len += sprintf( buffer + len, "[2] sa = %x\n", g_fbdev_reg_l8->osd2_sc_cfg.osd2_sc_bc_sa );

			ret = len;
		}
		break;

		case PROC_ID_VIEW_CTRL:
		{
			int	len = 0;
			len += sprintf( buffer + len, "OSD VIEW CTRL status\n");
			len += sprintf( buffer + len, "OSD 0 : %d\n", FBDEV_GetOSDEnable(0) );
			len += sprintf( buffer + len, "OSD 1 : %d\n", FBDEV_GetOSDEnable(1) );
			len += sprintf( buffer + len, "OSD 2 : %d\n", FBDEV_GetOSDEnable(2) );
			len += sprintf( buffer + len, "OSD 3 : %d\n", FBDEV_GetOSDEnable(3) );
			len += sprintf( buffer + len, "\n");
			len += sprintf( buffer + len, "[usage] echo osd_id on_off_val > /proc/lg/fbdev/viewctrl\n" );
			len += sprintf( buffer + len, "        osd_id     : 0 ~ 3\n" );
			len += sprintf( buffer + len, "        on_off_val : 0 (off), 1(on)\n" );
			ret = len;
		}
		break;

		case PROC_ID_SYNC_CTRL:
		{
			int	len = 0;
			FBDEV_WIN_CTX_T* w;

			len += sprintf( buffer + len, "OSD SYNC CTRL status\n");
			w = FBDEV_GetWinCtx(0);
			len += sprintf( buffer + len, "OSD 0 : %d\n", w->status.b_use_vsync );
			w = FBDEV_GetWinCtx(1);
			len += sprintf( buffer + len, "OSD 1 : %d\n", w->status.b_use_vsync );
			w = FBDEV_GetWinCtx(2);
			len += sprintf( buffer + len, "OSD 2 : %d\n", w->status.b_use_vsync );
			w = FBDEV_GetWinCtx(3);
			len += sprintf( buffer + len, "OSD 3 : %d\n", w->status.b_use_vsync );
			len += sprintf( buffer + len, "\n");

			len += sprintf( buffer + len, "[usage] echo osd_id on_off_val > /proc/lg/fbdev/syncctrl\n" );
			len += sprintf( buffer + len, "        osd_id     : 0 ~ 3\n" );
			len += sprintf( buffer + len, "        on_off_val : 0 (off), 1(on)\n" );
			ret = len;
		}
		break;

		default:
		{
			ret = sprintf( buffer, "%s(%d)\n", "unimplemented read proc", procId );
		}
	}
		
	return ret;
}

/*
 * write_proc implementation of fbdev device 
 *
*/
static int _FBDEV_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */	
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			printk("command string : %s\n", command );
		}
		break;

#if 1

		case PROC_ID_MUX:
		{
			LX_FBDEV_ZLIST_T	zlist;
			char path;
			int	 a, b, c;
			sscanf( command, " %c %d %d %d", &path, &a, &b, &c );

			zlist.path		= (path=='r')? LX_FBDEV_PATH_RIGHT: LX_FBDEV_PATH_LEFT;
			zlist.order[0]	= a;
			zlist.order[1]	= b;
			zlist.order[2]	= c;

			FBDEV_SetZList( &zlist );
		}
		break;

		case PROC_ID_SA:
		{
            char*   endp;
            UINT32  value;
            value = simple_strtoul( command, &endp, 16 );

//			g_fbdev_reg_l8->osd0_sc_cfg.osd0_sc_bc_sa = value;
//			g_fbdev_reg_l8->osd1_sc_cfg.osd1_sc_bc_sa = value;
//			g_fbdev_reg_l8->osd2_sc_cfg.osd2_sc_bc_sa = value;
		}
		break;
#endif

		case PROC_ID_VIEW_CTRL:
		{
			int	osd_id;
			int on_off_val;

			sscanf( command, " %d %d", &osd_id, &on_off_val );

			if ( osd_id >= 0 && osd_id < LX_FBDEV_ID_MAX )
			{
            	FBDEV_SetOSDEnable( osd_id, on_off_val );
			}
		}
		break;

		case PROC_ID_SYNC_CTRL:
		{
			int	osd_id;
			int on_off_val;

			sscanf( command, " %d %d", &osd_id, &on_off_val );

			if ( osd_id >= 0 && osd_id < LX_FBDEV_ID_MAX )
			{
				FBDEV_WIN_CTX_T* w = g_dm_ctx->winfo[osd_id];
				w->status.b_use_vsync = on_off_val;
			}
		}
		break;

		case PROC_ID_REG_RD:
		{
			UINT32 addr, val;
			sscanf( command, " %x", &addr );
			OS_RdReg( addr, &val );
			printk("0x%x = 0x%08x\n", addr, val );
		}
		break;

		case PROC_ID_REG_WR:
		{
			UINT32 addr, val;

			sscanf( command, " %x %x", &addr, &val );
			OS_WrReg( addr, val );
		}
		break;

		case PROC_ID_DATA_RD:
		{
			UINT32 	addr, num;
			UINT8*	data;
			sscanf( command, " %x %d", &addr, &num );

			data = (UINT8*)OS_Malloc( sizeof(UINT32)*num );

			OS_RdData( addr, (UINT32*)data, num );
			OS_HexDump( addr, data, sizeof(UINT32)* num );			
		}
		break;

		case PROC_ID_OSD_FREEZE:
		{
			UINT32 val;
			sscanf( command, " %d", &val );

			g_fbdev_osd_freeze = val;
		}
		break;

		/* clear OSD front screen for debug */
		case PROC_ID_OSD_CLEAR:
		{
#if 0
			FBDEV_WIN_CTX_T* winfo;
			int	posd_fd;
			UINT32 fb_dev_id;
			sscanf( command, " %d", &fb_dev_id );

			/* get WIN ctx */
			winfo = FBDEV_GetWinCtx( fb_dev_id );
			if ( winfo == NULL ) { printk("invalid win info\n"); break; }
			
				/* create temporary surface to clear the front screen */
			posd_fd = GFX_AllocARGBSurfaceEx( winfo->pixel.input_win.w, winfo->pixel.input_win.h,
										 		 winfo->pixel.uiBitmapDataYPTR, winfo->pixel.stride );

			/* clear it !! */
			if ( posd_fd >= 0 )
			{
				GFX_LockDevice();
				GFX_FillSurface( posd_fd, 0, 0, winfo->pixel.input_win.w, winfo->pixel.input_win.h, 0xffff0000 );
				GFX_FreeSurface( posd_fd );
				GFX_UnlockDevice();
			}

			/* this will make the registered surface to be front. there is a some mismatch in front screen during system startup */
			FBDEV_WriteOSDHeader( &(winfo->pixel) );
#endif
		}
		break;
				
		default:
		{
			/* do nothing */
		}
		break;	
	}
	
	return strlen(command);
}

/** initialize proc utility for fbdev device
 *
 * @see FBDEV_Init
*/
void	FBDEV_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( FBDEV_MODULE, _g_fbdev_device_proc_table, 
											_FBDEV_ReadProcFunction,
											_FBDEV_WriteProcFunction );
}

/** cleanup proc utility for fbdev device
 *
 * @see FBDEV_Cleanup
*/
void	FBDEV_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( FBDEV_MODULE );	
}

/** print OSD info 
 *
 */
static void	_FBDEV_PROC_PrintOSDInfo ( struct seq_file *m )
{
	int	i;
	extern FBDEV_CTX_T* g_dm_ctx;

	seq_printf( m, "mmio_base_phys = 0x%x\n", 	(UINT32)g_dm_ctx->mmio_base_phys );
	seq_printf( m, "mmio_size      = %d\n", 	(UINT32)g_dm_ctx->mmio_size );

	for ( i=0; i<4 ; i++ )
	{
		FBDEV_WIN_CTX_T* w = g_dm_ctx->winfo[i];
		seq_printf( m, "[ OSD %d ]\n", w->fb_dev_id );
		seq_printf( m, " - users                = %d\n", w->users );
		seq_printf( m, " - fb_base_phys         = 0x%x\n", (UINT32)w->fb_base_phys );
		seq_printf( m, " - fb_base              = 0x%x\n", (UINT32)w->fb_base );
		seq_printf( m, " - fb_size              = %d\n",   (int)w->fb_size );

		seq_printf( m, " - osd_header_base_phys = 0x%x\n", (UINT32)w->osd_header_base_phys );
		seq_printf( m, " - osd_header_base      = 0x%x\n", (UINT32)w->osd_header_base );
		seq_printf( m, " - osd_header_size      = 0x%x\n", (UINT32)w->osd_header_size );

		seq_printf( m, " - osd_pal_base_phys    = 0x%x\n", (UINT32)w->osd_pal_base_phys );
		seq_printf( m, " - osd_pal_base         = 0x%x\n", (UINT32)w->osd_pal_base );
		seq_printf( m, " - osd_pal_size         = %d\n", 	(int)w->osd_pal_size );

		seq_printf( m, " - map_dma              = 0x%x\n", (UINT32)w->map_dma );
		seq_printf( m, " - map_cpu              = %s\n",   (w->map_cpu)? (char*)w->map_cpu : "??" );
		seq_printf( m, " - map_size             = %d\n",   (int)w->map_size );

		seq_printf( m, " - screen_dma           = 0x%x\n", (UINT32)w->screen_dma );
		seq_printf( m, " - screen_cpu           = %s\n", (w->screen_cpu)? (char*)w->screen_cpu : "??" );

		seq_printf( m, " - alloc_fb_mem         = 0x%x\n", (UINT32)w->alloc_fb_mem );
		seq_printf( m, " - sdram_address        = 0x%x\n", (UINT32)w->sdram_address );

		seq_printf( m, "\n");
		seq_printf( m, " - pixel.fb_dev_id          = %d\n", w->pixel.fb_dev_id );
		seq_printf( m, " - pixel.uiOSDHeaderPTR  = 0x%x\n", (UINT32)w->pixel.uiOSDHeaderPTR );
		seq_printf( m, " - pixel.BitmapDataYPTR  = 0x%x\n", (UINT32)w->pixel.uiBitmapDataYPTR );
		seq_printf( m, " - pixel.PalettePTR      = 0x%x\n", (UINT32)w->pixel.uiPalettePTR );


//		seq_printf( m, " - pixel.usWordsPerLine  = %d\n", w->pixel.usWordsPerLine );
		seq_printf( m, " - pixel.stride          = %d\n", w->pixel.stride );
		seq_printf( m, " - pixel.bits_per_pixel  = %d (pxlfmt 0x%x, pxldepth 0x%x)\n", w->pixel.bits_per_pixel, 
																				FBDEV_GetOSDPxlFmt( w->pixel.bits_per_pixel ),
																				FBDEV_GetOSDPxlDepth( w->pixel.bits_per_pixel ) );
		seq_printf( m, " - pixel.input_win.x     = %d\n", w->pixel.input_win.x );
		seq_printf( m, " - pixel.input_win.y     = %d\n", w->pixel.input_win.y );
		seq_printf( m, " - pixel.input_win.w     = %d\n", w->pixel.input_win.w );
		seq_printf( m, " - pixel.input_win.h     = %d\n", w->pixel.input_win.h );
		seq_printf( m, " - pixel.output_win.x    = %d\n", w->pixel.output_win.x );
		seq_printf( m, " - pixel.output_win.y    = %d\n", w->pixel.output_win.y );
		seq_printf( m, " - pixel.output_win.w    = %d\n", w->pixel.output_win.w );
		seq_printf( m, " - pixel.output_win.h    = %d\n", w->pixel.output_win.h );
		seq_printf( m, " - pixel.bColorKeyEn     = 0x%x\n", (UINT32)w->pixel.bColorKeyEnable );
		seq_printf( m, " - pixel.bPixelOrderEn   = 0x%x\n", (UINT32)w->pixel.bPixelOrderEnable );
		seq_printf( m, " - pixel.bGlobalAlphaEn  = 0x%x\n", (UINT32)w->pixel.bGlobalAlphaEnable );
		seq_printf( m, " - pixel.uiOSDColorKey   = 0x%x\n", (UINT32)w->pixel.uiOSDColorKey );
		seq_printf( m, " - pixel.usGlobalAlpha   = 0x%x\n", (UINT32)w->pixel.usGlobalAlpha );
		seq_printf( m, " - pixel.uiLfsrSeed      = 0x%x\n", (UINT32)w->pixel.uiLfsrSeed );
		seq_printf( m, "\n");
		
		seq_printf( m, " - info.state            = 0x%x\n", (UINT32)w->fbinfo.state );
		seq_printf( m, " - info.flags            = 0x%x\n", (UINT32)w->fbinfo.flags );
		seq_printf( m, " - info.screen_base      = 0x%x\n", (UINT32)w->fbinfo.screen_base );
		seq_printf( m, " - info.screen_size      = %d\n",   (UINT32)w->fbinfo.screen_size );
		seq_printf( m, " - info.fbcon_par        = 0x%x\n", (UINT32)w->fbinfo.fbcon_par );
		seq_printf( m, " - info.par              = 0x%x\n", (UINT32)w->fbinfo.par );
		seq_printf( m, " - info.fix.id           = %s\n",   (char*)w->fbinfo.fix.id );
		seq_printf( m, " - info.fix.smem_start   = 0x%x\n", (UINT32)w->fbinfo.fix.smem_start );
		seq_printf( m, " - info.fix.smem_len     = %d\n",   (int)w->fbinfo.fix.smem_len );
		seq_printf( m, " - info.fix.type         = 0x%x\n", (UINT32)w->fbinfo.fix.type );
		seq_printf( m, " - info.fix.type_aux     = 0x%x\n", (UINT32)w->fbinfo.fix.type_aux );
		seq_printf( m, " - info.fix.visual       = 0x%x\n", (UINT32)w->fbinfo.fix.visual );
		seq_printf( m, " - info.fix.xpanstep     = %d\n",   (int)w->fbinfo.fix.xpanstep );
		seq_printf( m, " - info.fix.ypanstep     = %d\n",   (int)w->fbinfo.fix.ypanstep );
		seq_printf( m, " - info.fix.ywrapstep    = %d\n",   (int)w->fbinfo.fix.ywrapstep );
		seq_printf( m, " - info.fix.line_length  = %d\n",	(int)w->fbinfo.fix.line_length );
		seq_printf( m, " - info.fix.mmio_start   = 0x%x\n",	(UINT32)w->fbinfo.fix.mmio_start );
		seq_printf( m, " - info.fix.mmio_len     = %d\n",   (int)w->fbinfo.fix.mmio_len );
		seq_printf( m, " - info.fix.accel        = %x\n",	(UINT32)w->fbinfo.fix.accel );
		seq_printf( m, " - info.fix.reserved[3] 2B\n\n");

		seq_printf( m, " - info.var.xres         = %d\n",	(int)w->fbinfo.var.xres );
		seq_printf( m, " - info.var.yres         = %d\n",	(int)w->fbinfo.var.yres );
		seq_printf( m, " - info.var.xres_virtual = %d\n",	(int)w->fbinfo.var.xres_virtual );
		seq_printf( m, " - info.var.yres_virtual = %d\n",	(int)w->fbinfo.var.yres_virtual );
		seq_printf( m, " - info.var.xoffset      = %d\n",	(int)w->fbinfo.var.xoffset );
		seq_printf( m, " - info.var.yoffset      = %d\n",	(int)w->fbinfo.var.yoffset );
		seq_printf( m, " - info.var.bits_per_pixel= %d\n",	(int)w->fbinfo.var.bits_per_pixel );
		seq_printf( m, " - info.var.grayscale    = %d\n",	(int)w->fbinfo.var.grayscale );
		seq_printf( m, " - info.var.transp       = (%2d,%2d,%2d)\n",	(int)w->fbinfo.var.transp.offset, (int)w->fbinfo.var.transp.length, (int)w->fbinfo.var.transp.msb_right );
		seq_printf( m, " - info.var.red          = (%2d,%2d,%2d)\n", (int)w->fbinfo.var.red.offset, (int)w->fbinfo.var.red.length, (int)w->fbinfo.var.red.msb_right );
		seq_printf( m, " - info.var.green        = (%2d,%2d,%2d)\n", (int)w->fbinfo.var.green.offset, (int)w->fbinfo.var.green.length, (int)w->fbinfo.var.green.msb_right );
		seq_printf( m, " - info.var.blue         = (%2d,%2d,%2d)\n", (int)w->fbinfo.var.blue.offset, (int)w->fbinfo.var.blue.length, (int)w->fbinfo.var.blue.msb_right );
		seq_printf( m, " - info.var.nonstd       = %d\n",	(int)w->fbinfo.var.nonstd );
		seq_printf( m, " - info.var.activate     = 0x%x\n",	(UINT32)w->fbinfo.var.activate );
		seq_printf( m, " - info.var.width(mm)    = %d\n",	(int)w->fbinfo.var.width );
		seq_printf( m, " - info.var.height(mm)   = %d\n",	(int)w->fbinfo.var.height );
		seq_printf( m, " - info.var.pixclock     = %d\n",	(int)w->fbinfo.var.pixclock );
		seq_printf( m, " - info.var.left_margin  = %d\n",	(int)w->fbinfo.var.left_margin );
		seq_printf( m, " - info.var.right_margin = %d\n",	(int)w->fbinfo.var.right_margin );
		seq_printf( m, " - info.var.upper_margin = %d\n",	(int)w->fbinfo.var.upper_margin );
		seq_printf( m, " - info.var.lower_margin = %d\n",	(int)w->fbinfo.var.lower_margin );
		seq_printf( m, " - info.var.hsync_len(l8)= 0x%x\n",	(UINT32)w->fbinfo.var.hsync_len );
		seq_printf( m, " - info.var.vsync_len(l8)= 0x%x\n",	(UINT32)w->fbinfo.var.vsync_len );
		seq_printf( m, " - info.var.sync         = 0x%x\n",	(UINT32)w->fbinfo.var.sync );
		seq_printf( m, " - info.var.vmode        = 0x%x\n",	(UINT32)w->fbinfo.var.vmode );
		seq_printf( m, " - info.var.rotate       = %d\n",	(int)w->fbinfo.var.rotate );
		seq_printf( m, " - info.var.reserved[5] 4B\n\n");
	}	
}

static void	_FBDEV_PROC_DumpRegs ( struct seq_file *m )
{
	int		i;
	UINT32	val;
	UINT32	reg_base = g_reg_io_ctx->reg_base_addr;
	int		reg_num  = g_reg_io_ctx->reg_size>>2;

	seq_printf( m, "FBDEV Base Reg : 0x%08x\n", reg_base );

	for ( i=0; i<reg_num; i++ )
	{
		OS_RdReg( reg_base + (i<<2), &val );

		seq_printf( m, " 0x%08x (+0x%04x) = %08x\n", reg_base + (i<<2), (i<<2), val );
	}
}

/** @} */


