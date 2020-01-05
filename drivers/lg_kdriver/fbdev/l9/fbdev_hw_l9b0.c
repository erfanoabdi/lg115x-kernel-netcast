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

/* @file name : fbdev_hw.c
 * @description : fbdev hardware register control functions
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	FRC_1280x1080_SUPPORT
#undef	FRC_CURSOR_PARTIAL_UPDATE	/* improve performance .. not working well */
#undef  FRC_PIXEL_DUMP_BY_CURSOR
#define FRC_FAST_OSD_EMUL
#define PRINTK(fmt,args...)		//printk(##fmt,args)

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_drv.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_hw_l9.h"
#include "fbdev_util_l9.h"
#include "fbdev_reg_l9a0.h"

#include "../sys/ctop_regs.h"
#include "gfx_draw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define FRC_OSD_EMUL_DEVID			0			/* OSD0 */
#define FRC_OSD_EMUL_CALC_CRSR(v)	((v)*2/3)	/* get shrinken value for cursor simulation. v * 1280/1920, v * 720/1080 */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct	
{
	BOOLEAN             b_hdr_ready;        /* set to TRUE when FRC header is written */

	UINT32              hdr_phys_addr;		/* N/A */
	UINT32              hdr_virt_addr;      /* N/A */

	UINT32              frc_hdr[6];         /* FRC header data */
	UINT32              frc_hdr_remap[6];   /* FRC header data (after remap) */
}
FBDEV_FRC_HDR_EMUL_DATA_T;

typedef struct
{
	int                 osd_idx;
	UINT32				crsr_addr;				/* physical address for stretching cursor */
	UINT32				crsr_bkup_addr;			/* cursor image backup address */
	UINT32              merge_osd_addr[2];		/* two physical address for merging POSDs (1280*720) only */
	int                 fb_dev_id;				/* OSD Id used for OSD merger */

	int					merge_osd_hd_surface[2];/* surface ID for merge HD content */
	UINT32				merge_osd_hd_addr[2];	/* two physical address for merge POSDs (1920*1080) only */

	int					my_vsync;

#define	OSD_EMUL_VIEW_NONE			0x0
#define	OSD_EMUL_VIEW_POSD0			0x0001
#define	OSD_EMUL_VIEW_POSD1			0x0002
#define	OSD_EMUL_VIEW_CRSR			0x0004
#define OSD_EMUL_VIEW_BACK_IMG		0x0010
#define OSD_EMUL_VIEW_POSD1_RESIZE	0x0020
	UINT32				osd_view_flag;

	UINT32				osd_bm_ptr_sav[2];		/* previous image ptr. POSD0 & POSD1 */

	BOOLEAN             osd_view_status[LX_FBDEV_ID_MAX];
	FBDEV_L9_OSD_HDR_T		osd_hdr_sav[LX_FBDEV_ID_MAX];	

#ifdef	FRC_1280x1080_SUPPORT
	/* make 128x128 temp cursor */
	UINT32				crsr_1280x1080_addr;
	int					crsr_1280x1080_surface;
#endif
}
FBDEV_FRC_OSD_EMUL_DATA_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void	FBDEV_L9_InitOSDZOrder	( void );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
extern volatile OSD_L9A0_REG_T*		g_fbdev_l9_reg;
extern OSD_L9A0_REG_T*				g_fbdev_l9_reg_cached;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void FBDEV_L9B0_WriteFRCHeader	( void );
static void FBDEV_L9B0_InitHDOSDMerge	( void );
static void FBDEV_L9B0_ExitHDOSDMerge	( void );
static void	FBDEV_L9B0_MergePOSD 		( int layer, BOOLEAN b_flip );
static void	FBDEV_L9B0_MergePOSD_720p	( int layer, BOOLEAN b_flip );
static void	FBDEV_L9B0_MergePOSD_1080p	( int layer, BOOLEAN b_flip );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static const int 					pixel_depth_2_bpp[PIX_DEPTH_MAX] = { 1, 2, 4, 8, 16, 24, 32  };
static FBDEV_FRC_HDR_EMUL_DATA_T	g_frc_hdr_emul;
static FBDEV_FRC_OSD_EMUL_DATA_T	g_frc_osd_emul;
static OS_SEM_T  		     		g_frc_osd_emul_mtx;

/*========================================================================================
	Implementation Group
========================================================================================*/

/** initialize L9A0(A1) HW Ctx & Cfg 
 *
 * 
 */
void FBDEV_L9B0_InitHWCtx ( void )
{
	PRINTK("^g^[fb] L9B0 HW Ctx....\n");

	OS_InitMutex ( &g_frc_osd_emul_mtx, OS_SEM_ATTR_DEFAULT );	/* create simple mutex */

	g_fbdev_frc_ctrl.b_frc_sep_enable	= FALSE;	/* Blending Mode by default */
	g_fbdev_frc_ctrl.b_frc_UD_enable	= FALSE;	/* Standard Mode by default */
	g_fbdev_frc_ctrl.b_frc_hdr_emul		= FALSE;	/* Disable FRC HDR emulation */
	g_fbdev_frc_ctrl.b_frc_osd_emul		= TRUE;
	g_fbdev_frc_ctrl.frc_hdr_emul_dev	= -1;
#ifdef FRC_1280x1080_SUPPORT
	g_fbdev_frc_ctrl.b_frc_720p_disp_enable = FALSE;
#endif

	/* initialize OSD merge variable */
	g_frc_osd_emul.crsr_addr	  			= 0x0;
	g_frc_osd_emul.crsr_bkup_addr	 	 	= 0x0;
	g_frc_osd_emul.merge_osd_addr[0]		= 0x0;
	g_frc_osd_emul.merge_osd_addr[1]		= 0x0;
	g_frc_osd_emul.merge_osd_hd_addr[0] 	= 0x0;//gMemCfgFBDevFRCEmul.osd_emul_mem_1080p.base;
	g_frc_osd_emul.merge_osd_hd_addr[1] 	= 0x0;//gMemCfgFBDevFRCEmul.osd_emul_mem_1080p.base;
	g_frc_osd_emul.merge_osd_hd_surface[0]	= -1;
	g_frc_osd_emul.merge_osd_hd_surface[1]	= -1;

	g_frc_osd_emul.osd_idx	= 0;
	g_frc_osd_emul.my_vsync	= -1;

#ifdef FRC_1280x1080_SUPPORT
	g_frc_osd_emul.crsr_1280x1080_addr		= 0x0;
	g_frc_osd_emul.crsr_1280x1080_surface	= -1;
#endif
}

/** OSD HW Layer enable/disable
 *
 * @param	int layer : osd layer ,
 *		enable : 0 : display off , 1 : display on
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9B0_SetOSDEnable(int layer , int enable)
{
	int ret = RET_ERROR;

	FBDEV_TRACE_BEGIN();
	FBDEV_CHECK_CODE( layer<0 || layer>=LX_FBDEV_ID_MAX, goto func_exit, "invalid layer %d\n", layer );

	/* save POSD view status for FRC emulation */
	g_frc_osd_emul.osd_view_status[layer] = enable;

	/* if FRC emulation mode, ignore show/hide request for OSD2 */
    if ( g_fbdev_frc_ctrl.b_frc_sep_enable || g_fbdev_frc_ctrl.b_frc_UD_enable )
	{
		/* merge POSDs to the single POSD */
		FBDEV_L9B0_MergePOSD( layer, FALSE );
	}
	else
	{
		switch(layer)
		{
			case LX_FBDEV_ID_OSD0: 	g_fbdev_l9_reg->osd0_cfg.osd0_en = enable; break;
			case LX_FBDEV_ID_OSD1: 	g_fbdev_l9_reg->osd1_cfg.osd1_en = enable; break;
			case LX_FBDEV_ID_OSD2: 	g_fbdev_l9_reg->osd2_cfg.osd2_en = enable; break;
			case LX_FBDEV_ID_CSR0:	g_fbdev_l9_reg->crsr_cfg.crsr_en = enable; break;
			default: 				FBDEV_WARN("invalid OSD ID %d\n", layer ); ret = RET_ERROR; break;
		}
	}

	ret = RET_OK; /* all work done */
func_exit:
	FBDEV_TRACE_END();
	return ret;
}

/** OSD HW Layer status
 *
 * @param	void
 * @return	int 1 : ON , 0 : OFF
 *
 */
int FBDEV_L9B0_GetOSDEnable(int layer)
{
	int ret = 0;

	/* if FRC OSD enabled, just return the pseudo OSD status */
    if ( g_fbdev_frc_ctrl.b_frc_sep_enable || g_fbdev_frc_ctrl.b_frc_UD_enable )
	{
		return g_frc_osd_emul.osd_view_status[layer];
	}

	switch(layer)
	{
		case LX_FBDEV_ID_OSD0:	ret = g_fbdev_l9_reg->osd0_cfg.osd0_en; break;
		case LX_FBDEV_ID_OSD1:	ret = g_fbdev_l9_reg->osd1_cfg.osd1_en; break;
		case LX_FBDEV_ID_OSD2:	ret = g_fbdev_l9_reg->osd2_cfg.osd2_en; break;
		case LX_FBDEV_ID_CSR0:	ret = g_fbdev_l9_reg->crsr_cfg.crsr_en; break;
		default: 				FBDEV_WARN("invalid OSD ID %d\n", layer ); ret = -1; break;
	}

	return ret;
}

/** Set Header information
 *
 * @param	SCanvas : pointer to structure bearing osd header information
 * @return	void
 *
 * @ingroup osd_ddi_func
 */
int FBDEV_L9B0_WriteOSDHeader( struct scanvas *hCanvas )
{
	int				ret;
	int				fb_dev_id;
	UINT32			bitmap_ptr;
	FBDEV_L9_OSD_HDR_T osd_hdr;

	/* clear osd_hdr before writing */
	memset( (void*)&osd_hdr, 0x0, sizeof(FBDEV_L9_OSD_HDR_T) );

	ret = 0; //down_interruptible(&fbdev_sem_l9);

	fb_dev_id	= hCanvas->fb_dev_id;
	bitmap_ptr	= hCanvas->uiBitmapDataYPTR;

	/* raxis.lim (2010/12/03)
	 * -- OSD ¿Í CRSR ÀÇ register Å©±â°¡ Æ²·Á¼­ Æ²·Á¼­ µ¿ÀÏ ÄÚµå°¡ Áßº¹µÇ¾î ÀÖ´Ù. Â÷ÈÄ Á¤¸® ¿ä¸Á.
	 */
	switch( fb_dev_id )
	{
		case LX_FBDEV_ID_CSR0:
		{
			/* if cursor csr_hotspot is active then adjust (x,y) position of cursor layer.
			 * if cursor position is negative, I should move the bitmap address ( H/W doesn't accept negative position )
		 	 *
			 * if cursor size is feeded, use that values as the viewing cursor area
			 *
			 * IMPORTATNT !! if you change the base address, its alignment should be multiplt of 16 byte ( not 8 byte )
			 * woonghyeon just said that it may be H/W bug.
			 * since we are using ARGB8888 pixel format for cursor OSD. cursor offset should be multiple of 4 !!
		 	 * If we are using ARGB4444 pixel format, cursor offset should be mulitiple of 8 !!!
			 */
			int	csr_x_off = 0;
			int	csr_y_off = 0;
			int	csr_x_pos = hCanvas->output_win.x - hCanvas->csr_hotspot.x;
			int	csr_y_pos = hCanvas->output_win.y - hCanvas->csr_hotspot.y;
#ifdef FBDEV_GP_USE_16BIT_CURSOR
			int	csr_x_size= (hCanvas->csr_size.w)? LX_CALC_ALIGNED_VALUE(hCanvas->csr_size.w,3) : hCanvas->input_win.w;
#else
			int	csr_x_size= (hCanvas->csr_size.w)? LX_CALC_ALIGNED_VALUE(hCanvas->csr_size.w,2) : hCanvas->input_win.w;
#endif
			/* there is no limit in height, so it is good to use the whole y size */
//			int	csr_y_size= (hCanvas->csr_size.h)? hCanvas->csr_size.h : hCanvas->input_win.h;
			int	csr_y_size = hCanvas->input_win.h;

			/* too small cursor with may lead to OSD corruption. According to system test, width should be greater than a half of OSD width */
			if ( csr_x_size < (hCanvas->input_win.w>>1) ) csr_x_size = (hCanvas->input_win.w>>1);

#ifdef FBDEV_GP_USE_16BIT_CURSOR
			if ( csr_x_pos < 0 ) { csr_x_off = -csr_x_pos; csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,3); csr_x_pos = 0; }
#else
			if ( csr_x_pos < 0 ) { csr_x_off = -csr_x_pos; csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2); csr_x_pos = 0; }
#endif
			if ( csr_y_pos < 0 ) { csr_y_off = -csr_y_pos; csr_y_pos = 0; }

			/* raxis.lim@lge.com (2011/09/23) 
			 * L9 donesn't support odd numbered x position when cursor is located to the far right side of the screen 
			 */
			if ( csr_x_pos + csr_x_size > 1920 ) csr_x_pos = LX_CALC_ALIGNED_VALUE(csr_x_pos,1);

//			PRINTK("[cursor] sz %d,%d, pos %d,%d hot %d,%d\n", csr_x_size, csr_y_size, csr_x_pos, csr_y_pos, hCanvas->csr_hotspot.x, hCanvas->csr_hotspot.y );

			osd_hdr.type.crsr.osd_hdr_xpos		 	= csr_x_pos;	/* output x (csr x pos) */
			osd_hdr.type.crsr.osd_hdr_ypos 			= csr_y_pos;	/* output y (csr y pos) */
			osd_hdr.type.crsr.osd_hdr_w_mem 		= csr_x_size;	/* viewing cursor width */
			osd_hdr.type.crsr.osd_hdr_h_mem 		= csr_y_size;	/* viewing cursor height */

			/* when 3Dmode enabled, input window should be shrinked so OSD h/w make double-sized screen */
            if( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode == LX_FBDEV_TRID_MODE_SS )
			{
				osd_hdr.type.crsr.osd_hdr_w_mem >>= 1;
//				PRINTK("^g^TRID MODE = SS (%d,%d)\n", osd_hdr.type.osd.osd_hdr_w_mem, osd_hdr.type.osd.osd_hdr_h_mem );
			}
			else if ( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode == LX_FBDEV_TRID_MODE_TB )
			{
				osd_hdr.type.crsr.osd_hdr_h_mem >>= 1;
//				PRINTK("^g^TRID MODE = TB (%d,%d)\n", osd_hdr.type.osd.osd_hdr_w_mem, osd_hdr.type.osd.osd_hdr_h_mem );
			}
			else
			{
				/* do nothing */
			}

			osd_hdr.type.crsr.osd_hdr_pixel_order	= hCanvas->bPixelOrderEnable;
			osd_hdr.osd_hdr_wpl 					= hCanvas->stride>>3;

#ifdef	FRC_1280x1080_SUPPORT
			if( g_fbdev_frc_ctrl.b_frc_720p_disp_enable )
			{
				/* make temp surface with cursor bitmap and shrink it. 
				 * surface should be cleared and copy region should be as small as possible to void the garbage.
			 	 */
				int	crsr_surf = GFX_AllocARGBSurface( 128, 128, bitmap_ptr );
#if 0
				GFX_ClearSurface  ( g_frc_osd_emul.crsr_1280x1080_surface, 128, 128 );
				GFX_StretchSurface( crsr_surf, g_frc_osd_emul.crsr_1280x1080_surface, 0, 0, 128, 128, 0, 0, 88, 128 );
#else
				GFX_ClearSurface  ( g_frc_osd_emul.crsr_1280x1080_surface, 128, 128 );
				GFX_StretchSurface( crsr_surf, g_frc_osd_emul.crsr_1280x1080_surface, 0, 0, csr_x_size, csr_y_size, 0, 0, csr_x_size*2/3, csr_y_size );
#endif
				GFX_FreeSurface( crsr_surf );

				/* replace bitmap pointer !! since it is the same size as the original cursor, I can use all the canvas data */
				bitmap_ptr	= g_frc_osd_emul.crsr_1280x1080_addr;

				csr_x_off						= (csr_x_off*2)/3;	/* crsr_x_off * 1280/1920 */
				osd_hdr.type.crsr.osd_hdr_xpos	= (osd_hdr.type.crsr.osd_hdr_xpos *2)/3;
				osd_hdr.type.crsr.osd_hdr_w_mem	= (osd_hdr.type.crsr.osd_hdr_w_mem*2)/3;

				csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2);
				osd_hdr.type.crsr.osd_hdr_xpos	= LX_CALC_ALIGNED_VALUE(osd_hdr.type.crsr.osd_hdr_xpos,2);
				osd_hdr.type.crsr.osd_hdr_w_mem	= LX_CALC_ALIGNED_VALUE(osd_hdr.type.crsr.osd_hdr_w_mem,2);
					
				printk("[fb] cursor x_off : %d,  xpos : %d, w_mem : %d\n", csr_x_off, osd_hdr.type.crsr.osd_hdr_xpos, osd_hdr.type.crsr.osd_hdr_w_mem );
			}
#endif
			/* if offset value is valid, move bitmap address */
			bitmap_ptr += ( csr_y_off * hCanvas->stride ) + ( csr_x_off * (hCanvas->bits_per_pixel>>3) );

			PRINTK("[fb] cursor off : %d %d, pos ; %d %d, sz %d %d, bm 0x%08x\n", 
							csr_x_off, csr_y_off, osd_hdr.type.crsr.osd_hdr_xpos, osd_hdr.type.crsr.osd_hdr_ypos,
							osd_hdr.type.crsr.osd_hdr_w_mem, osd_hdr.type.crsr.osd_hdr_h_mem, bitmap_ptr );
		}
		break;

		case LX_FBDEV_ID_OSD0:
		case LX_FBDEV_ID_OSD1:
		case LX_FBDEV_ID_OSD2:
		{
			osd_hdr.type.osd.osd_hdr_color_key_en 	= hCanvas->bColorKeyEnable;

			osd_hdr.type.osd.osd_hdr_w_out		= hCanvas->output_win.w;	/* output w */
			osd_hdr.type.osd.osd_hdr_h_out		= hCanvas->output_win.h;	/* output h */
			osd_hdr.type.osd.osd_hdr_xpos	 	= hCanvas->output_win.x;	/* output x */
			osd_hdr.type.osd.osd_hdr_ypos 		= hCanvas->output_win.y;	/* output y */
			osd_hdr.type.osd.osd_hdr_w_mem 		= hCanvas->input_win.w;		/* input w  */
			osd_hdr.type.osd.osd_hdr_h_mem 		= hCanvas->input_win.h;		/* input h  */

			/* when 3Dmode enabled, input window should be shrinked so OSD h/w make double-sized screen */
            if( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode == LX_FBDEV_TRID_MODE_SS )
			{
				osd_hdr.type.osd.osd_hdr_w_mem >>= 1;
//				PRINTK("^g^TRID MODE = SS (%d,%d)\n", osd_hdr.type.osd.osd_hdr_w_mem, osd_hdr.type.osd.osd_hdr_h_mem );
			}
			else if ( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode == LX_FBDEV_TRID_MODE_TB )
			{
				osd_hdr.type.osd.osd_hdr_h_mem >>= 1;
//				PRINTK("^g^TRID MODE = TB (%d,%d)\n", osd_hdr.type.osd.osd_hdr_w_mem, osd_hdr.type.osd.osd_hdr_h_mem );
			}
			else
			{
				/* do nothing */
			}
#ifdef FRC_1280x1080_SUPPORT
			if ( g_fbdev_frc_ctrl.b_frc_720p_disp_enable )
			{
//				osd_hdr.type.osd.osd_hdr_w_mem = (osd_hdr.type.osd.osd_hdr_w_mem * 1920 )/1280;
				osd_hdr.type.osd.osd_hdr_w_out = 1280;
			}
#endif
			osd_hdr.type.osd.osd_hdr_pixel_order= hCanvas->bPixelOrderEnable;
			osd_hdr.osd_hdr_wpl 				= hCanvas->stride>>3;
		}
		break;
	}

    osd_hdr.osd_hdr_format          = FBDEV_GetOSDPxlFmt( hCanvas->bits_per_pixel );
    osd_hdr.osd_hdr_depth           = FBDEV_GetOSDPxlDepth( hCanvas->bits_per_pixel );

	osd_hdr.osd_hdr_global_alpha_en	= hCanvas->bGlobalAlphaEnable;
	osd_hdr.osd_hdr_global_alpha	= hCanvas->usGlobalAlpha;
	osd_hdr.osd_hdr_color_key		= hCanvas->uiOSDColorKey;

	if ( g_reg_io_ctx->slkrd_prefix_mask )
	{
		osd_hdr.osd_hdr_ptr_bmp		= ((bitmap_ptr & 0x0FFFFFFF)| g_reg_io_ctx->slkrd_prefix_mask );
		osd_hdr.osd_hdr_ptr_plte	= ((hCanvas->uiPalettePTR&0x0FFFFFFF)| g_reg_io_ctx->slkrd_prefix_mask );
	}
	else
	{
		osd_hdr.osd_hdr_ptr_bmp		= bitmap_ptr;
		osd_hdr.osd_hdr_ptr_plte	= hCanvas->uiPalettePTR;
	}

#ifdef FBDEV_USE_MMIO_REG
	/* if FRC OSD emulation enabled and current layer is not for FRC header emulation, then merge POSD !!! */
	if ( g_fbdev_frc_ctrl.b_frc_sep_enable || g_fbdev_frc_ctrl.b_frc_UD_enable )
	{
		/* save header for merging */
		memcpy( (void*)&g_frc_osd_emul.osd_hdr_sav[fb_dev_id], (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );

		FBDEV_L9B0_MergePOSD( fb_dev_id, TRUE );
	}
	else
	{
		/* write hdr data */
		memcpy ( (void*)hCanvas->uiOSDHeaderPTR, (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );
		/* read data back for prevent data coherency problem */
		//memcpy ( (void*)&osd_hdr, (void*)hCanvas->uiOSDHeaderPTR, sizeof(FBDEV_L9_OSD_HDR_T) );
	}
#else
	/* TODO: write register. test more !! */
	switch( fb_dev_id )
	{
		case 0:	FBDEV_REG_MEMCPY( &g_fbdev_l9_reg->osd0_hdr0, &osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T)/4);
				break;
		case 1:	FBDEV_REG_MEMCPY( &g_fbdev_l9_reg->osd1_hdr0, &osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T)/4);
				break;
		case 2:	FBDEV_REG_MEMCPY( &g_fbdev_l9_reg->osd2_hdr0, &osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T)/4);
				break;
		case 3:	FBDEV_REG_MEMCPY( &g_fbdev_l9_reg->crsr_hdr0, &osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T)/4);
				break;
	}
#endif
	FBDEV_L9B0_WriteFRCHeader( );

//	up(&fbdev_sem_l9);

	return RET_OK;
}

/*========================================================================================
	Implementation Group (ISR)
========================================================================================*/
void FBDEV_L9B0_ISRTickHandler ( void )
{
	/* if new vsync arrived, swap osd idx */
	if ( ( g_fbdev_frc_ctrl.b_frc_sep_enable || g_fbdev_frc_ctrl.b_frc_UD_enable )
		&& g_frc_osd_emul.my_vsync >= 0 && g_frc_osd_emul.my_vsync != g_fbdev_vsync_cnt )
	{
//		PRINTK("OSD Vsync...[%d]\n", g_frc_osd_emul.osd_idx );
		g_frc_osd_emul.osd_idx ^= 1;
		g_frc_osd_emul.my_vsync = -1;
	}
}

/*========================================================================================
    Implementation Group (CAPS)
========================================================================================*/
BOOLEAN FBDEV_L9B0_CheckCaps ( FBDEV_L9_HW_CAPS_T caps, UINT32 args )
{
    BOOLEAN ret = FALSE;

    switch(caps)
    {
        case FBDEV_L9_HW_CAPS_TRID_CTRL:
        {
			if ( !g_fbdev_frc_ctrl.b_frc_sep_enable ) ret = TRUE;
        }
        break;

        default:
        {
            FBDEV_ERROR("unknown or not supported caps %d\n", caps );
        }
        break;
    }

    return ret;
}

/*========================================================================================
	Implementation Group (GPU SUPPORT)
========================================================================================*/
/** set CLK
 *
 *
 */
void FBDEV_L9B0_SetGPUClk ( FBDEV_L9_HW_GPU_CLK_T clk )
{
    CTOP_CTRL_L9B_RdFL(ctr01_reg_clk_div_sel);
    CTOP_CTRL_L9B_RdFL(ctr29_reg_swrst);


    printk("[fb] GPU CLOCK [old ] 0014: 0x%08x 0084: 0x%08x\n", CTOP_CTRL_L9B_Rd(ctr01_reg_clk_div_sel), CTOP_CTRL_L9B_Rd(ctr29_reg_swrst) );

    switch( clk )
    {
        case FBDEV_L9_HW_GPU_CLK_528MHZ:
            CTOP_CTRL_L9B_Wr01(ctr01_reg_clk_div_sel,   gpuclk_sel,		0x4 /* default value */ );
            CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst,         gpu_high_speed, 0x1 );
            printk("[fb] GPU CLOCK [528M] 0014:0x%08x 0084:0x%08x\n", CTOP_CTRL_L9B_Rd(ctr01_reg_clk_div_sel), CTOP_CTRL_L9B_Rd(ctr29_reg_swrst) );
        break;

        case FBDEV_L9_HW_GPU_CLK_400MHZ:
            CTOP_CTRL_L9B_Wr01(ctr01_reg_clk_div_sel,   gpuclk_sel,     0x3 /* 400 MHz */ );
            CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst,         gpu_high_speed, 0x0 );
            printk("[fb] GPU CLOCK [400M] 0014:0x%08x 0084:0x%08x\n", CTOP_CTRL_L9B_Rd(ctr01_reg_clk_div_sel), CTOP_CTRL_L9B_Rd(ctr29_reg_swrst) );
        break;

        default: /* 320M */
            CTOP_CTRL_L9B_Wr01(ctr01_reg_clk_div_sel,   gpuclk_sel,     0x4 /* default value */ );
            CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst,         gpu_high_speed, 0x0 );
            printk("[fb] GPU CLOCK [320M] 0014:0x%08x 0084:0x%08x\n", CTOP_CTRL_L9B_Rd(ctr01_reg_clk_div_sel), CTOP_CTRL_L9B_Rd(ctr29_reg_swrst) );
        return;
    }

    CTOP_CTRL_L9B_WrFL(ctr01_reg_clk_div_sel);
    CTOP_CTRL_L9B_WrFL(ctr29_reg_swrst);
}

/*========================================================================================
	Implementation Group (FRC)
========================================================================================*/
/** set OSD output ctrl
 *
 *	@param pConnCtrl [IN] connection control data
 *	@return RET_OK if success, RET_ERROR otherwise
 *
 */
int     FBDEV_L9B0_SetConnCtrl           (LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
	int ret = RET_OK;

	/* standard connection with LDVS */
	if ( pConnCtrl->conn_type == LX_FBDEV_CONN_STD_LVDS )
	{
        g_fbdev_frc_ctrl.b_frc_UD_enable	= FALSE;	/* clear UD flag */
		g_fbdev_frc_ctrl.b_frc_sep_enable	= FALSE;	/* clear SEP flag */
#ifdef FRC_1280x1080_SUPPORT
		g_fbdev_frc_ctrl.b_frc_720p_disp_enable = FALSE;
#endif
		FBDEV_L9B0_ExitHDOSDMerge( );					/* shutdown OSD merge */

		g_fbdev_l9_reg->osd0_cfg.osd0_double_w = 0x0;	/* disable OSD horizontal double */
		g_fbdev_l9_reg->osd0_cfg.osd0_double_h = 0x0;	/* disable OSD vertical   double */

        /* reinialize the OSD order. this function will make OSD_MUX L/R to be default
         * TODO: FRC control function should be H/W dependent part.
         */
        FBDEV_L9_InitOSDZOrder ( );

        /* make path mode to be default ( OSD out to both R/L path ) */
        OSD_L9A0_RdFL( osd0_3d_path_mode );
        OSD_L9A0_RdFL( osd1_3d_path_mode );
        OSD_L9A0_RdFL( osd2_3d_path_mode );
        OSD_L9A0_RdFL( crsr_3d_path_mode );

        OSD_L9A0_Wr02(osd0_3d_path_mode, osd0_path_sel,     0x0,    /* LR */
                                         osd0_path_buf_half,0x0 );  /* disable path buf half (checked by ±è¿õÇö) */
        OSD_L9A0_Wr01(osd1_3d_path_mode, osd1_path_sel,     0x0 );  /* LR */
        OSD_L9A0_Wr01(osd2_3d_path_mode, osd2_path_sel,     0x0 );  /* LR */
        OSD_L9A0_Wr01(crsr_3d_path_mode, crsr_path_sel,     0x0 );  /* LR */

        OSD_L9A0_WrFL( osd0_3d_path_mode );
        OSD_L9A0_WrFL( osd1_3d_path_mode );
        OSD_L9A0_WrFL( osd2_3d_path_mode );
        OSD_L9A0_WrFL( crsr_3d_path_mode );

		/* make OSD to be FHD size */
		OSD_L9A0_RdFL( osd_disp_size );
		OSD_L9A0_Wr02( osd_disp_size, 	disp_w,		1920,	/* 1920 */
										disp_h,		1080 );	/* 1080 */
		OSD_L9A0_WrFL( osd_disp_size );

        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[3]->pixel );

        /* TODO: add more code */
    }
    /* UD connection with FRCIII */
    else if ( pConnCtrl->conn_type == LX_FBDEV_CONN_UD_FRCIII_BLEND )
	{
		printk("^g^[fb] FRC UD BLEND mode..\n");

        if ( g_fbdev_frc_ctrl.b_frc_sep_enable ) { /* ignore multiple requetst */ goto func_exit; }

		/* disable FRC path */
        g_fbdev_frc_ctrl.b_frc_UD_enable	= TRUE;			/* set   UD flag */
        g_fbdev_frc_ctrl.b_frc_sep_enable	= FALSE;		/* clear SEP flag */
#ifdef FRC_1280x1080_SUPPORT
		g_fbdev_frc_ctrl.b_frc_720p_disp_enable = TRUE;
#endif
		FBDEV_L9B0_InitHDOSDMerge( );						/* init OSD merge */

		g_fbdev_l9_reg->osd_frc_if_cfg.osd_frc_if_en = 0x0; /* disable FRC sep */
#if 0
		/* rewrite OSD header to update current change */
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[3]->pixel );
#endif
		g_fbdev_l9_reg->osd0_cfg.osd0_en = 0x1;			/* on  PoSD0 for merging */
		g_fbdev_l9_reg->osd1_cfg.osd1_en = 0x0;			/* off POSD1 for merging */
		g_fbdev_l9_reg->osd2_cfg.osd2_en = 0x0;			/* off POSD2 for merging */
		g_fbdev_l9_reg->crsr_cfg.crsr_en = 0x0;			/* off POSD3 for merging */

		g_fbdev_l9_reg->osd0_cfg.osd0_double_w = 0x1;	/* enable OSD horizontal double (checked by ±è¿õÇö) */
		g_fbdev_l9_reg->osd0_cfg.osd0_double_h = 0x1;	/* enable OSD vertical   double (checked by ±è¿õÇö) */

        /* reinialize the OSD order. this function will make OSD_MUX L/R to be default
         * TODO: FRC control function should be H/W dependent part.
         */
		FBDEV_L9_InitOSDZOrder ( );

		/* make path mode to be default ( OSD out to both R/L path ) */
		OSD_L9A0_RdFL( osd0_3d_path_mode );
		OSD_L9A0_RdFL( osd1_3d_path_mode );
		OSD_L9A0_RdFL( osd2_3d_path_mode );
		OSD_L9A0_RdFL( crsr_3d_path_mode );

		OSD_L9A0_Wr02(osd0_3d_path_mode, osd0_path_sel,		0x0,	/* LR */
										 osd0_path_buf_half,0x1 );	/* enable path buf half (checked by ±è¿õÇö) */
		OSD_L9A0_Wr01(osd1_3d_path_mode, osd1_path_sel,		0x0	);	/* LR */
		OSD_L9A0_Wr01(osd2_3d_path_mode, osd2_path_sel,		0x0	); 	/* LR */
		OSD_L9A0_Wr01(crsr_3d_path_mode, crsr_path_sel,		0x0	); 	/* LR */

		OSD_L9A0_WrFL( osd0_3d_path_mode );
		OSD_L9A0_WrFL( osd1_3d_path_mode );
		OSD_L9A0_WrFL( osd2_3d_path_mode );
		OSD_L9A0_WrFL( crsr_3d_path_mode );

		/* make OSD to be UI size */
		OSD_L9A0_RdFL( osd_disp_size );
		OSD_L9A0_Wr02( osd_disp_size, 	disp_w,		1920,	/* not 1920<<1. confirmed by ±è¿õÇö  */
										disp_h,		2160 );	/* 1080<<1 . confirmed by ±è¿õÇö */
		OSD_L9A0_WrFL( osd_disp_size );

		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[3]->pixel );

        /* TODO: add more code */
	}
    /* standard connection with FRCIII */
    else if ( pConnCtrl->conn_type == LX_FBDEV_CONN_STD_FRCIII_BLEND )
    {
		printk("^g^[fb] FRC STD BLEND mode..\n");

        g_fbdev_frc_ctrl.b_frc_sep_enable	= FALSE;		/* clear SEP flag */
        g_fbdev_frc_ctrl.b_frc_UD_enable	= FALSE;		/* clear UD flag */
#ifdef FRC_1280x1080_SUPPORT
		g_fbdev_frc_ctrl.b_frc_720p_disp_enable = TRUE;		/* set 720p only flag */
#endif
		FBDEV_L9B0_ExitHDOSDMerge( );						/* shutdown OSD merge */

		g_fbdev_l9_reg->osd0_cfg.osd0_double_w = 0x0;		/* disable OSD horizontal double */
		g_fbdev_l9_reg->osd0_cfg.osd0_double_h = 0x0;		/* disable OSD vertical   double */
		g_fbdev_l9_reg->osd_frc_if_cfg.osd_frc_if_en = 0x0; /* disable FRC sep */

		/* rewrite OSD header to update current change */
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[3]->pixel );

        /* reinialize the OSD order. this function will make OSD_MUX L/R to be default
         * TODO: FRC control function should be H/W dependent part.
         */
		FBDEV_L9_InitOSDZOrder ( );

		/* make path mode to be default ( OSD out to both R/L path ) */
		OSD_L9A0_RdFL( osd0_3d_path_mode );
		OSD_L9A0_RdFL( osd1_3d_path_mode );
		OSD_L9A0_RdFL( osd2_3d_path_mode );
		OSD_L9A0_RdFL( crsr_3d_path_mode );

		OSD_L9A0_Wr02(osd0_3d_path_mode, osd0_path_sel,		0x0,	/* LR */
										 osd0_path_buf_half,0x0 );	/* disable path buf half (checked by ±è¿õÇö) */
		OSD_L9A0_Wr01(osd1_3d_path_mode, osd1_path_sel,	0x0	); /* LR */
		OSD_L9A0_Wr01(osd2_3d_path_mode, osd2_path_sel,	0x0	); /* LR */
		OSD_L9A0_Wr01(crsr_3d_path_mode, crsr_path_sel,	0x0	); /* LR */

		OSD_L9A0_WrFL( osd0_3d_path_mode );
		OSD_L9A0_WrFL( osd1_3d_path_mode );
		OSD_L9A0_WrFL( osd2_3d_path_mode );
		OSD_L9A0_WrFL( crsr_3d_path_mode );

		/* make OSD to be FHD size */
		OSD_L9A0_RdFL( osd_disp_size );
		OSD_L9A0_Wr02( osd_disp_size, 	disp_w,		1920,	/* 1920 */
										disp_h,		1080 );	/* 1080 */
		OSD_L9A0_WrFL( osd_disp_size );

        /* TODO: add more code */
    }
    /* standard connection with FRCIII (OSD/VIDEO separated mode) */
    else if ( pConnCtrl->conn_type == LX_FBDEV_CONN_STD_FRCIII_SEPARATE )
    {
		printk("^g^[fb] FRC STD SEP mode..\n");

#ifdef  FRC_1280x1080_SUPPORT
		/* raxis.lim (2011/11/14) -- create temp cursor surface to support 1280x1080 display.
		 * surface height should be greater than 128 to avoid screen garbage !! 
		 * without this, screen garbage will be shown at the top of the screen !!
		 */
		if ( g_frc_osd_emul.crsr_1280x1080_surface < 0 )
		{
			LX_GFX_SURFACE_SETTING_T surface_info;
			g_frc_osd_emul.crsr_1280x1080_surface   = GFX_AllocARGBSurface(128,192/*256*/, 0x0 );

			GFX_ClearSurface( g_frc_osd_emul.crsr_1280x1080_surface, 128, 192/*256*/ );

			GFX_GetSurfaceInfo(g_frc_osd_emul.crsr_1280x1080_surface, &surface_info );
			g_frc_osd_emul.crsr_1280x1080_addr = (UINT32)surface_info.phys_addr;
		}
#endif

        if ( g_fbdev_frc_ctrl.b_frc_sep_enable ) { /* ignore multiple requetst */ goto func_exit; }

        g_fbdev_frc_ctrl.b_frc_UD_enable	= FALSE;	/* clear UD flag */
        g_fbdev_frc_ctrl.b_frc_sep_enable	= TRUE;		/* set FRC sep flag */
		g_frc_hdr_emul.b_hdr_ready			= FALSE;	/* I want to make header again */
#ifdef FRC_1280x1080_SUPPORT
		g_fbdev_frc_ctrl.b_frc_720p_disp_enable = FALSE;/* clear 720p only flag */
#endif
		FBDEV_L9B0_ExitHDOSDMerge( );					/* Exit OSD merge */	/* TEST */

		g_fbdev_l9_reg->osd0_cfg.osd0_en = 0x1;			/* on  PoSD0 for merging */
		g_fbdev_l9_reg->osd1_cfg.osd1_en = 0x0;			/* off POSD1 for merging */
		g_fbdev_l9_reg->osd2_cfg.osd2_en = 0x0;			/* off POSD2 for merging */
		g_fbdev_l9_reg->crsr_cfg.crsr_en = 0x0;			/* off POSD3 for merging */

		g_fbdev_l9_reg->osd0_cfg.osd0_double_w = 0x0;	/* disable OSD horizontal double */
		g_fbdev_l9_reg->osd0_cfg.osd0_double_h = 0x0;	/* disable OSD vertical   double */

        {
			/* TODO: below codes are made for test purpose. make the release version */
			UINT32 val;

#if 0 /* FRC SEP works well even without the below code */
			/* raxis.lim (2011/09/10) -- workaround for DE firmware for FRC SEP */
			FBDEV_WriteReg( 0xc0021018, 0x000A019F );
#endif
			/* make path mode to be default ( OSD out to both R/L path ) */
			OSD_L9A0_RdFL( osd0_3d_path_mode );
			OSD_L9A0_RdFL( osd1_3d_path_mode );
			OSD_L9A0_RdFL( osd2_3d_path_mode );
			OSD_L9A0_RdFL( crsr_3d_path_mode );

			OSD_L9A0_Wr02(osd0_3d_path_mode, osd0_path_sel,		0x2,	/* LR */
											 osd0_path_buf_half,0x0 );	/* disable path buf half (checked by ±è¿õÇö) */
			OSD_L9A0_Wr01(osd1_3d_path_mode, osd1_path_sel,	0x2	); /* R only */
			OSD_L9A0_Wr01(osd2_3d_path_mode, osd2_path_sel,	0x2	); /* R only */
			OSD_L9A0_Wr01(crsr_3d_path_mode, crsr_path_sel,	0x2	); /* R only */

			OSD_L9A0_WrFL( osd0_3d_path_mode );
			OSD_L9A0_WrFL( osd1_3d_path_mode );
			OSD_L9A0_WrFL( osd2_3d_path_mode );
			OSD_L9A0_WrFL( crsr_3d_path_mode );

			/* make OSD to be FHD size */
			OSD_L9A0_RdFL( osd_disp_size );
			OSD_L9A0_Wr02( osd_disp_size, 	disp_w,		1920,	/* 1920 (0x780) */
											disp_h,		1080 );	/* 1080 (0x438) */
			OSD_L9A0_WrFL( osd_disp_size );

			// 3. OSD scaler buffer mode enable
			val = 0x80001163;
			memcpy((void *)&g_fbdev_l9_reg->osd0_sc_cfg , (void *)&val , 4);
			memcpy((void *)&g_fbdev_l9_reg->osd1_sc_cfg , (void *)&val , 4);
			memcpy((void *)&g_fbdev_l9_reg->osd2_sc_cfg , (void *)&val , 4);

			val = 0x2210;
			memcpy((void *)&g_fbdev_l9_reg->osd_layer_mux_right , (void *)&val , 4);

            /* 0x21 for B0, 0x01 for B1 ( checked by ±è¿õÇö )
             * L9B1 has the different concept for osd_frc_if_cfg.
             * for more information, please contact to ±è¿õÇö and read the latest OSD manual.
			 *
			 * support L9B0/B1 simulation !!!
             */
			if ( lx_chip_rev() >= LX_CHIP_REV(L9,B1) )  val = 0x01;
			else                                        val = 0x21;
			memcpy((void *)&g_fbdev_l9_reg->osd_frc_if_cfg , (void *)&val , 4);
		}

		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[3]->pixel );
    }
    else
    {
		g_fbdev_frc_ctrl.b_frc_sep_enable = 0;
		g_fbdev_frc_ctrl.b_frc_UD_enable = 0;
        FBDEV_WARN("conn(0x%x) not supported\n", pConnCtrl->conn_type );
        ret = RET_ERROR;
    }

func_exit:
	return ret;
}

/** write FRC releated heaer
 *
 *
 */
static void FBDEV_L9B0_WriteFRCHeader( void )
{
	/* write OSD header only when FRC header emulation enabled */
	if ( g_fbdev_frc_ctrl.b_frc_sep_enable )
	{
		UINT32				val;
	    OSD_L9A0_FRC_HDR_0  osd_frc_hdr_0;   // 0x1ba4 : ''
		OSD_L9A0_FRC_HDR_1  osd_frc_hdr_1;   // 0x1ba8 : ''
		OSD_L9A0_FRC_HDR_2  osd_frc_hdr_2;   // 0x1bac : ''
		OSD_L9A0_FRC_HDR_3  osd_frc_hdr_3;   // 0x1bb0 : ''
		OSD_L9A0_FRC_HDR_4  osd_frc_hdr_4;   // 0x1bb4 : ''
		OSD_L9A0_FRC_HDR_5  osd_frc_hdr_5;   // 0x1bb8 : ''

		/* make the initial FRC header. this is processed only once at the first call */
		if ( g_frc_hdr_emul.b_hdr_ready == FALSE )
		{
			/* enable the 2nd routine if you want to use the cleared memory before setting frc header */
#if 1
			OSD_L9A0_RdFL(osd_frc_hdr_0); val = OSD_L9A0_Rd(osd_frc_hdr_0);	memcpy( &osd_frc_hdr_0,	&val, sizeof(UINT32));
			OSD_L9A0_RdFL(osd_frc_hdr_1); val = OSD_L9A0_Rd(osd_frc_hdr_1); memcpy( &osd_frc_hdr_1,	&val, sizeof(UINT32));
			OSD_L9A0_RdFL(osd_frc_hdr_2); val = OSD_L9A0_Rd(osd_frc_hdr_2); memcpy( &osd_frc_hdr_2,	&val, sizeof(UINT32));
			OSD_L9A0_RdFL(osd_frc_hdr_3); val = OSD_L9A0_Rd(osd_frc_hdr_3);	memcpy( &osd_frc_hdr_3,	&val, sizeof(UINT32));
			OSD_L9A0_RdFL(osd_frc_hdr_4); val = OSD_L9A0_Rd(osd_frc_hdr_4);	memcpy( &osd_frc_hdr_4,	&val, sizeof(UINT32));
			OSD_L9A0_RdFL(osd_frc_hdr_5); val = OSD_L9A0_Rd(osd_frc_hdr_5);	memcpy( &osd_frc_hdr_5,	&val, sizeof(UINT32));
#else
			memset( &osd_frc_hdr_0, 0x0, sizeof(UINT32) );
			memset( &osd_frc_hdr_1, 0x0, sizeof(UINT32) );
			memset( &osd_frc_hdr_2, 0x0, sizeof(UINT32) );
			memset( &osd_frc_hdr_3, 0x0, sizeof(UINT32) );
			memset( &osd_frc_hdr_4, 0x0, sizeof(UINT32) );
			memset( &osd_frc_hdr_5, 0x0, sizeof(UINT32) );
#endif
			/* osd_frc_hdr_0.osdf_frc_hdr_frame_number should be increased at vsync interrupt
		 	 *
			 * hdr0.format
			 *  0001 (AYUV6888), 0010 (ARGB6888), 0101 (AYUV8888), 0100 (ARGB8888)
			 *
			 * hdr0.po (pixel order)
			 *	0001 (AGBR/YUV), 0010 (BGRA/VUYA), 0001 (ABGR/AVUY, 0000: (ARGB/AYUV)
			 *
			 * hdr0.lr (Left/Right)
			 *  1 (R), 0 (L)
			 *
			 * hdr0.3d (3D bitmap indicator) - this value should be set for 2D mode or 3D mode with the same L/R image
			 *  1 (3D), 0 (2d)
			 *
			 * hdr0.header_prefix
			 *  1010 (valid OSD), 0000
			 */
			osd_frc_hdr_0.osd_frc_hdr_format		= 0x4; /* ARGB8888 */
			osd_frc_hdr_0.osd_frc_hdr_po			= 0x0; /* ARGB/AYUV */
			osd_frc_hdr_0.osd_frc_lr				= 0x0;
			osd_frc_hdr_0.osd_frc_hdr_prefix		= 0xA;
			osd_frc_hdr_0.osd_frc_3d				= 0x0; //( g_fbdev_frc_info.trid_ctrl[layer].mode )? 1:0;
			osd_frc_hdr_0.osd_frc_hdr_frame_number	= 0x0; /* fixed */

			osd_frc_hdr_1.osd_frc_hdr_bmp_width		= 1920;
			osd_frc_hdr_1.osd_frc_hdr_bmp_height	= 1080;
#ifdef FRC_1280x1080_SUPPORT
            /* raxis.lim (2011/11/14) -- set OSD bitmap size to be 1280. this will FRC expand OSD horizontally */
            if( g_fbdev_frc_ctrl.b_frc_720p_disp_enable )
            {
                osd_frc_hdr_1.osd_frc_hdr_bmp_width = 1280;
            }
#endif
			osd_frc_hdr_2.osd_frc_hdr_global_alpha	= 0xff;
			osd_frc_hdr_2.osd_frc_hdr_pe			= 0x1;
			osd_frc_hdr_2.osd_frc_hdr_ge			= 0x0;
			osd_frc_hdr_2.osd_frc_hdr_ce			= 0x0;
			osd_frc_hdr_2.osd_frc_hdr_ou			= 0x1;

			osd_frc_hdr_3.osd_frc_hdr_ck_r			= 0x0;
			osd_frc_hdr_3.osd_frc_hdr_ck_g			= 0x0;
			osd_frc_hdr_3.osd_frc_hdr_ck_b			= 0x0;

			osd_frc_hdr_4.osd_frc_hdr_xoffset		= 0x0;
			osd_frc_hdr_4.osd_frc_hdr_yoffset		= 0x0;

			osd_frc_hdr_5.osd_frc_hdr_disp_width	= 1920;
			osd_frc_hdr_5.osd_frc_hdr_disp_height	= 1080;

			/* save FRC header */
			g_frc_hdr_emul.frc_hdr[0] = *((UINT32*)&osd_frc_hdr_0);
			g_frc_hdr_emul.frc_hdr[1] = *((UINT32*)&osd_frc_hdr_1);
			g_frc_hdr_emul.frc_hdr[2] = *((UINT32*)&osd_frc_hdr_2);
			g_frc_hdr_emul.frc_hdr[3] = *((UINT32*)&osd_frc_hdr_3);
			g_frc_hdr_emul.frc_hdr[4] = *((UINT32*)&osd_frc_hdr_4);
			g_frc_hdr_emul.frc_hdr[5] = *((UINT32*)&osd_frc_hdr_5);

			/* save remapped header */
			g_frc_hdr_emul.frc_hdr_remap[0] = FBDEV_L9_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_0) );
			g_frc_hdr_emul.frc_hdr_remap[1] = FBDEV_L9_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_1) );
			g_frc_hdr_emul.frc_hdr_remap[2] = FBDEV_L9_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_2) );
			g_frc_hdr_emul.frc_hdr_remap[3] = FBDEV_L9_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_3) );
			g_frc_hdr_emul.frc_hdr_remap[4] = FBDEV_L9_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_4) );
			g_frc_hdr_emul.frc_hdr_remap[5] = FBDEV_L9_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_5) );

			PRINTK("^c^[fb] FRC HDR[0 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[0] );	// should be 0x00a00004
			PRINTK("^c^[fb] FRC HDR[1 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[1] );	// should be 0x00780138
			PRINTK("^c^[fb] FRC HDR[2 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[2] );	// should be 0x000024ff
			PRINTK("^c^[fb] FRC HDR[3 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[3] );	// should be 0x0
			PRINTK("^c^[fb] FRC HDR[4 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[4] );	// should be 0x0
			PRINTK("^c^[fb] FRC HDR[5 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[5] );	// should be 0x00780138

			/* remap(swap bit order) should be done before writing register */
			OSD_L9A0_Wr( osd_frc_hdr_0, g_frc_hdr_emul.frc_hdr_remap[0] );
			OSD_L9A0_Wr( osd_frc_hdr_1, g_frc_hdr_emul.frc_hdr_remap[1] );
			OSD_L9A0_Wr( osd_frc_hdr_2, g_frc_hdr_emul.frc_hdr_remap[2] );
			OSD_L9A0_Wr( osd_frc_hdr_3, g_frc_hdr_emul.frc_hdr_remap[3] );
			OSD_L9A0_Wr( osd_frc_hdr_4, g_frc_hdr_emul.frc_hdr_remap[4] );
			OSD_L9A0_Wr( osd_frc_hdr_5, g_frc_hdr_emul.frc_hdr_remap[5] );

			OSD_L9A0_WrFL( osd_frc_hdr_0 );
			OSD_L9A0_WrFL( osd_frc_hdr_1 );
			OSD_L9A0_WrFL( osd_frc_hdr_2 );
			OSD_L9A0_WrFL( osd_frc_hdr_3 );
			OSD_L9A0_WrFL( osd_frc_hdr_4 );
			OSD_L9A0_WrFL( osd_frc_hdr_5 );

			g_frc_hdr_emul.b_hdr_ready = TRUE;
		}
	}
}

/** initialize/exit OSD merge environment 
 *
 *
 */
static void FBDEV_L9B0_InitHDOSDMerge		( void )
{
	LX_GFX_SURFACE_SETTING_T surface_info;

	if( g_frc_osd_emul.merge_osd_hd_surface[0] < 0 )
	{
		g_frc_osd_emul.merge_osd_hd_surface[0] = GFX_AllocARGBSurface( 1920, 1080, 0x0 /*NULL*/ );
		FBDEV_CHECK_CODE( g_frc_osd_emul.merge_osd_hd_surface[0]<0, return, "can't alloc HD[0] surface. crtical error!!\n");

		GFX_GetSurfaceInfo ( g_frc_osd_emul.merge_osd_hd_surface[0], &surface_info );
		g_frc_osd_emul.merge_osd_hd_addr[0]	= (UINT32)surface_info.phys_addr;
	}
	if( g_frc_osd_emul.merge_osd_hd_surface[1] < 0 )
	{
		g_frc_osd_emul.merge_osd_hd_surface[1] = GFX_AllocARGBSurface( 1920, 1080, 0x0 /*NULL*/ );
		FBDEV_CHECK_CODE( g_frc_osd_emul.merge_osd_hd_surface[1]<0, return, "can't alloc HD[1] surface. crtical error!!\n");

		GFX_GetSurfaceInfo ( g_frc_osd_emul.merge_osd_hd_surface[1], &surface_info );
		g_frc_osd_emul.merge_osd_hd_addr[1]	= (UINT32)surface_info.phys_addr;
	}
}

static void FBDEV_L9B0_ExitHDOSDMerge		( void )
{
	if ( g_frc_osd_emul.merge_osd_hd_surface[0] >= 0 )
	{
		g_frc_osd_emul.merge_osd_hd_surface[0]	= -1;
		g_frc_osd_emul.merge_osd_hd_addr[0] 	= 0x0;
		GFX_FreeSurface( g_frc_osd_emul.merge_osd_hd_surface[0] );
	}

	if ( g_frc_osd_emul.merge_osd_hd_surface[1] >= 0 )
	{
		g_frc_osd_emul.merge_osd_hd_surface[1]	= -1;
		g_frc_osd_emul.merge_osd_hd_addr[1] 	= 0x0;
		GFX_FreeSurface( g_frc_osd_emul.merge_osd_hd_surface[1] );
	}
}

/** merge POSDs into the one single POSD since L9B0 chip has bugs in FRC separated OSD mode and OSD H/W
 *	can show only one POSD.
 *
 *	@param layer [IN] layer(POSD) to be updated
 *	@param b_actie [IN] if TRUE, OSD should be merged. if FALSE, separated mode will be shutdown and OSD should be cleared
 *	@param b_flip [IN] emulated POSD should be fliped for TRUE input.
 *
 *	@note 128x128 cursor is resized to 88x88 to simulate the cursor size in 1920x1080 dimension
 *	@note cursor hot spot is reimplemented
 *
 *	@note To obtain system performnace, this function is NOT general !!!
 */
static void FBDEV_L9B0_MergePOSD ( int layer, BOOLEAN b_flip )
{
	if ( g_fbdev_frc_ctrl.b_frc_sep_enable ) 		{ FBDEV_L9B0_MergePOSD_720p ( layer, b_flip ); }	/* TEST */
	else if ( g_fbdev_frc_ctrl.b_frc_UD_enable )	{ FBDEV_L9B0_MergePOSD_1080p( layer, b_flip ); }
	else											{ /* do nothing */; }
} 

static void FBDEV_L9B0_MergePOSD_720p( int layer, BOOLEAN b_flip )
{
	struct scanvas *posd0_canvas = NULL;
	struct scanvas *posd1_canvas = NULL;
	struct scanvas *posd3_canvas = NULL;

	FBDEV_L9_OSD_HDR_T	osd_hdr;
	UINT32			merge_osd_addr		= 0x0;
	UINT32			merge_osd_hd_addr	= 0x0;

	int				posd0_surf = -1;
	int				posd1_surf = -1; 
	int				posd3_surf = -1;
	int				merge_surf = -1;

	static int		crsr_surf 			= -1;
	static int		crsr_bkup_surf		= -1;
 	static int		merge_surf_list[2]	= {-1,-1};
	static int		full_hd_merge_surf	= -1;

#ifdef FRC_CURSOR_PARTIAL_UPDATE
	static LX_RECT_T	crsr_bkup_rect		= {0,0,88,88};
	static BOOLEAN		b_crsr_bkup_avail	= FALSE;
	BOOLEAN				b_crsr_partial_draw	= FALSE;
#endif
	int					cx, cy, cw, ch, dx, dy;			/* cursor related value */

	cx = cy = dx = dy = 0;								/* ?? */
	cw = ch = 88;										/* ?? */

	/* POSD merge is only valid for FRC3 SEP mode. */
	if( g_fbdev_frc_ctrl.b_frc_sep_enable == 0 ) return;

	PRINTK("^g^%s : %d,%d\n", __func__, layer, b_flip );

	/* disable multiple enterance !! */
	OS_LockMutex( &g_frc_osd_emul_mtx );

	posd0_canvas = &g_dm_ctx->winfo[0]->pixel;	/* POSD0 */
	posd1_canvas = &g_dm_ctx->winfo[1]->pixel;	/* POSD1 */
	posd3_canvas = &g_dm_ctx->winfo[3]->pixel;	/* POSD3 (CRSR) */

    /* create external surface for POSD merge */
    {
        LX_GFX_SURFACE_SETTING_T surface_info;

        if ( !g_frc_osd_emul.crsr_addr )
        {
            int surf = GFX_AllocARGBSurface( 128, 128, 0x0 );
            FBDEV_CHECK_CODE( surf<0, goto func_exit, "can't create merge surface\n");

            GFX_GetSurfaceInfo ( surf, &surface_info );
            g_frc_osd_emul.crsr_addr = (UINT32)surface_info.phys_addr;
        }

        if ( !g_frc_osd_emul.crsr_bkup_addr )
        {
            int surf = GFX_AllocARGBSurface( 128, 128, 0x0 );
            FBDEV_CHECK_CODE( surf<0, goto func_exit, "can't create merge surface\n");

            GFX_GetSurfaceInfo ( surf, &surface_info );
            g_frc_osd_emul.crsr_bkup_addr = (UINT32)surface_info.phys_addr;
		}

        if ( !g_frc_osd_emul.merge_osd_addr[0] )
        {
            int surf = GFX_AllocARGBSurface( 1280, 720, 0x0 );
            FBDEV_CHECK_CODE( surf<0, goto func_exit, "can't create merge surface\n");

            GFX_GetSurfaceInfo ( surf, &surface_info );
            g_frc_osd_emul.merge_osd_addr[0] = (UINT32)surface_info.phys_addr;
        }

        if ( !g_frc_osd_emul.merge_osd_addr[1] )
        {
            int surf = GFX_AllocARGBSurface( 1280, 720, 0x0 );
            FBDEV_CHECK_CODE( surf<0, goto func_exit, "can't create merge surface\n");

            GFX_GetSurfaceInfo ( surf, &surface_info );
            g_frc_osd_emul.merge_osd_addr[1] = (UINT32)surface_info.phys_addr;
        }
    }

	/* collect OSD view status */
	g_frc_osd_emul.osd_view_flag	= 0x0;
	g_frc_osd_emul.osd_view_flag	|= (g_frc_osd_emul.osd_view_status[0])? OSD_EMUL_VIEW_POSD0: 0x0;
	g_frc_osd_emul.osd_view_flag	|= (g_frc_osd_emul.osd_view_status[1])? OSD_EMUL_VIEW_POSD1: 0x0;
	g_frc_osd_emul.osd_view_flag	|= (g_frc_osd_emul.osd_view_status[3])? OSD_EMUL_VIEW_CRSR:  0x0;
	g_frc_osd_emul.osd_view_flag	|= (posd0_canvas->bBackImageEnable)?	OSD_EMUL_VIEW_BACK_IMG: 0x0;
	g_frc_osd_emul.osd_view_flag	|= ( g_frc_osd_emul.osd_view_status[1] && ( posd1_canvas->input_win.w != 1280 || posd1_canvas->input_win.h != 720 ) )? OSD_EMUL_VIEW_POSD1_RESIZE: 0x0;

	PRINTK("[fb] osd flag = %08x\n", g_frc_osd_emul.osd_view_flag );

	/* raxis.lim (2011/09/03)
	 * Accoring to the cursor test, I found that the invalid cursor is requested. 
	 * In that cases, cursor size is set to zero. I don't know what is wrong exactly.
	 * But some workaround shoule be added..
	 */
	if ( layer == 3 && posd3_canvas->csr_size.w == 0 && posd3_canvas->csr_size.h == 0 )
	{
		PRINTK("[fb] ignore invalid cursor request...\n"); goto func_exit;
	}

	/* initialize my_vsync control value to be '-1' to avoid incorrect swap of OSD INDEX */
	if ( layer == 0 || layer == 1 ) g_frc_osd_emul.my_vsync = -1;

	/* get the saved OSD0 header */
	memcpy( (void*)&osd_hdr, (void*)&g_frc_osd_emul.osd_hdr_sav[0], sizeof(FBDEV_L9_OSD_HDR_T) ); 

	if ( crsr_surf < 0 )			crsr_surf			= GFX_AllocARGBSurface(  88,   88, g_frc_osd_emul.crsr_addr );		 /* 88x88 */
	if ( crsr_bkup_surf < 0 )		crsr_bkup_surf		= GFX_AllocARGBSurface(  88,   88, g_frc_osd_emul.crsr_bkup_addr );	 /* 88x88 */
	if ( merge_surf_list[0] < 0 )	merge_surf_list[0]	= GFX_AllocARGBSurface( 1280, 720, g_frc_osd_emul.merge_osd_addr[0] ); /* 720p  */
	if ( merge_surf_list[1] < 0 )	merge_surf_list[1]	= GFX_AllocARGBSurface( 1280, 720, g_frc_osd_emul.merge_osd_addr[1] ); /* 720p  */

	/* create HD surface image when needed.
	 * remember that HD surface is destroyed when it is not necessary.
	 */
	if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_BACK_IMG )
	{
		LX_GFX_SURFACE_SETTING_T surface_info;

		if ( full_hd_merge_surf < 0 ) 
		{
			full_hd_merge_surf = GFX_AllocARGBSurface( 1920,1080, 0x0 /*NULL*/);
			FBDEV_CHECK_CODE( full_hd_merge_surf < 0, goto func_exit, "can't alloc HD surface. critical error !!\n");
		}
		GFX_GetSurfaceInfo ( full_hd_merge_surf, &surface_info );
		merge_osd_hd_addr = (UINT32)surface_info.phys_addr;
	}
	else
	{
		if ( full_hd_merge_surf >= 0 )
		{
			GFX_FreeSurface( full_hd_merge_surf );
			full_hd_merge_surf	= -1;
			merge_osd_hd_addr	= 0x0 /*NULL*/;
		}
	}

	/* create temporary surface to merge the POSD source */
	posd0_surf	= GFX_AllocARGBSurfaceEx( 1280, 720, posd0_canvas->uiBitmapDataYPTR, posd0_canvas->stride );
	posd1_surf	= GFX_AllocARGBSurfaceEx( 1280, 720, posd1_canvas->uiBitmapDataYPTR, posd1_canvas->stride );
	posd3_surf	= GFX_AllocARGBSurfaceEx(  128, 128, posd3_canvas->uiBitmapDataYPTR, posd3_canvas->stride );

	GFX_LockDevice();

	/* get active OSD frame buffer and destination OSD surface */
	merge_osd_addr		= g_frc_osd_emul.merge_osd_addr[g_frc_osd_emul.osd_idx];
	merge_surf			= merge_surf_list[g_frc_osd_emul.osd_idx];
	
	PRINTK("[fb] %d-%d-%d %08x:%08x:%08x Idx %d flip %d layer %d\n", 
												g_frc_osd_emul.osd_view_status[0], g_frc_osd_emul.osd_view_status[1], g_frc_osd_emul.osd_view_status[3], 
												posd0_canvas->uiBitmapDataYPTR,
												posd1_canvas->uiBitmapDataYPTR,
												posd3_canvas->uiBitmapDataYPTR,
												g_frc_osd_emul.osd_idx, b_flip, layer );

	/* if POSD1 is shown and its size is less than 1280x720, POSD1 should be resized !!! */
#ifdef FRC_FAST_OSD_EMUL
	/* do nothing */
#else
	if ( g_frc_osd_emul.osd_view_status[1] && ( posd1_canvas->input_win.w != 1280 || posd1_canvas->input_win.h != 720 ) )
	{
		PRINTK("^g^[fb] POSD1 resized (%d,%d)->(%d,%d)\n",  posd1_canvas->input_win.w, posd1_canvas->input_win.h, 1280, 720 );
	}
#endif

	/* if only single POSD is updated, go to the header_update without any action !! */
	if ( g_frc_osd_emul.osd_view_flag == OSD_EMUL_VIEW_POSD0 || g_frc_osd_emul.osd_view_flag == OSD_EMUL_VIEW_POSD1 )
	{
		PRINTK("[fb] CASE(-1)\n");
		b_flip = FALSE;	/* disable merge_osd flip since the real POSD will be used ~ */
		goto header_update;
	}

	/* if cursor layer is shown, process(scale down) the cursor to fit the virtual POSD.
	 * cursor image may be drawn to the merge surface or POSD surface directly. 
	 */  
	if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_CRSR )
	{
		int	csr_x_pos, csr_y_pos;	

		csr_y_pos  = posd3_canvas->output_win.y - posd3_canvas->csr_hotspot.y;	/* cursor y */
		csr_x_pos  = posd3_canvas->output_win.x - posd3_canvas->csr_hotspot.x;	/* cursor x */

		csr_y_pos = FRC_OSD_EMUL_CALC_CRSR(csr_y_pos);					/* 1280x720 dimension */
		csr_x_pos = FRC_OSD_EMUL_CALC_CRSR(csr_x_pos);					/* 1280x720 dimension */
		csr_x_pos = LX_CALC_ALIGNED_VALUE(csr_x_pos,1); 				/* make even number to meed alignment reguirement of GFX H/W */

		if ( csr_x_pos < 1280 && csr_y_pos < 720 )
		{
			if 		( csr_x_pos < 0	)   { cx = -csr_x_pos; cw = 88 - cx; dx = 0 ;}
			else if ( csr_x_pos >= 1192){ cx = 0; cw = 88-(csr_x_pos-1192); dx=csr_x_pos; }
			else                        { cx = 0; cw = 88; dx = csr_x_pos ; }

			if 		( csr_y_pos < 0 )   { cy = -csr_y_pos; ch = 88 - cy; dy = 0 ;}
			else if ( csr_y_pos >= 632 ){ cy = 0; ch = 88-(csr_y_pos-632); dy=csr_y_pos; }
			else                        { cy = 0; ch = 88; dy = csr_y_pos ; }

			PRINTK("^c^[csr] %4d,%4d (%3d,%3d %3d,%3d) :: %d.%d.%d.%d -> %d.%d.%d.%d\n", 
								csr_x_pos, csr_y_pos, 
								posd3_canvas->csr_hotspot.x, posd3_canvas->csr_hotspot.y, posd3_canvas->csr_size.w, posd3_canvas->csr_size.h,
								cx, cy, cw, ch, dx, dy, cw, ch );

			/* shrink cursor to simulate 1920x1080 cursor size */
			GFX_StretchSurface( posd3_surf, crsr_surf, 0, 0, 128, 128, 0, 0, 88, 88 );	
#ifdef FRC_PIXEL_DUMP_BY_CURSOR
			if ( layer == 3 )
			{
				UINT32	crsr_pos_paddr	= merge_osd_addr + (( dy * 1280 + dx )<<2);		
				UINT32* crsr_pos_vaddr 	= (UINT32*)ioremap( crsr_pos_paddr, 4 );	
				UINT32	pixel			= *crsr_pos_vaddr;		
			
				iounmap( crsr_pos_vaddr );
				printk("[fb] cursor pixel (%4d,%3d) %08x (%02x)\n", dx, dy, pixel, (pixel>>24)&0xff );
			}
#endif
		}
	}

#ifdef FRC_CURSOR_PARTIAL_UPDATE
	/* if current updater is "cursor" and partial blit condition is satified, DO IT.
	 * cursor partial update is very limited and should be treated very carefully.
	 * cursor partial update will be performed only when POSD0 or POSD1 is not changed and only cursor is moving.
	 * we should go to the normal path when the condition is not met.
	 * partial update is compose of the three process. e.g: restore region + backup region + copy image.
	 * restore process will be omitted when there is no backuped region
	 */
	if ( g_frc_osd_emul.osd_view_flag == (OSD_EMUL_VIEW_POSD0|OSD_EMUL_VIEW_CRSR) ||
		 g_frc_osd_emul.osd_view_flag == (OSD_EMUL_VIEW_POSD1|OSD_EMUL_VIEW_CRSR) )
	{
		int	dst_surf = -1;

		if ( layer == 0 )
		{
			dst_surf 			= posd0_surf;	/* merge destination if POSD0 */
			b_crsr_partial_draw = FALSE;		/* not cursor paritial draw */
			b_crsr_bkup_avail	= FALSE;		/* reset cursor backup */
		}
		else if ( layer == 1)
		{
			dst_surf 			= posd1_surf;	/* merge destination if POSD1 */
			b_crsr_partial_draw = FALSE;		/* not cursor paritial draw */
			b_crsr_bkup_avail	= FALSE;		/* reset cursor backup */
		}
		else /* cursor it self */
		{
			/* check if POSD0 not changed and only cursor changed */
			if ( g_frc_osd_emul.osd_view_flag == (OSD_EMUL_VIEW_POSD0|OSD_EMUL_VIEW_CRSR) &&
				 g_frc_osd_emul.osd_bm_ptr_sav[0] == posd0_canvas->uiBitmapDataYPTR )
			{
				dst_surf 			= posd0_surf;	/* merge destination if POSD0 */
				b_crsr_partial_draw = TRUE;			/* DO partial update */
				b_flip 				= FALSE;		/* disable merge_osd flip */
			}
			/* check if POSD1 not changed and only cursor changed */
			else if (g_frc_osd_emul.osd_view_flag == (OSD_EMUL_VIEW_POSD1|OSD_EMUL_VIEW_CRSR) &&
       	          g_frc_osd_emul.osd_bm_ptr_sav[1] == posd1_canvas->uiBitmapDataYPTR )
			{
				dst_surf 			= posd1_surf;	/* merge destination if POSD0 */
				b_crsr_partial_draw = TRUE;			/* DO partial update */
				b_flip 				= FALSE;		/* disable merge_osd flip */
			}
		}

		if ( dst_surf >= 0 )
		{
			/* restore the previous backup if availble */
			if ( b_crsr_bkup_avail )
			{
				GFX_BlitSurface( crsr_bkup_surf, -1, dst_surf, 0, 0, crsr_bkup_rect.w, crsr_bkup_rect.h, crsr_bkup_rect.x, crsr_bkup_rect.y, FALSE );
				PRINTK("[fb] restore img (%d,%d,%d,%d) to dst (%d,%d)\n", 0, 0, crsr_bkup_rect.w, crsr_bkup_rect.h, crsr_bkup_rect.x, crsr_bkup_rect.y );
			}

			/* backup the new region */
			PRINTK("[fb] backing up dst (%d,%d,%d,%d) to img (%d,%d,%d,%d)\n", dx, dy, cw, ch, 0, 0, cw, ch );
			GFX_BlitSurface( dst_surf, -1, crsr_bkup_surf, dx, dy, cw, ch, 0, 0, FALSE );

			PRINTK("[fb] layer %d, dst_surf %s, partial %d, b_crsr_bkup_avail %d (%d,%d,%d,%d->%d,%d,%d,%d)\n", 
				layer, (dst_surf==posd1_surf)? "P1" : (dst_surf==posd0_surf)? "P0" : "??", b_crsr_partial_draw, b_crsr_bkup_avail,
								cx, cy, cw, ch, dx, dy, cw, ch );
			/* draw cursor */
			crsr_bkup_rect.x = dx;
			crsr_bkup_rect.y = dy;	
			crsr_bkup_rect.w = cw;	
			crsr_bkup_rect.h = ch;	
			b_crsr_bkup_avail = TRUE; /* mark cursor backup flag */

			GFX_BlitSurface( crsr_surf, dst_surf, dst_surf, cx, cy, cw, ch, dx, dy, TRUE );

			goto header_update;	
		}
	}

	b_crsr_bkup_avail = FALSE; /* reset cursor backup flag */
#endif

	/* BEGIN of the (slow) normal update process
	 *
	 * POSD merge is very tricky and special code for L9A0,B0 revision.
	 * the below code is not optimizaed but well working routine.
	 */

	/* CASE1: both POSD0 and POSD1 is shown */
	switch( g_frc_osd_emul.osd_view_flag & (OSD_EMUL_VIEW_POSD0|OSD_EMUL_VIEW_POSD1) )
	{	
	case (OSD_EMUL_VIEW_POSD0|OSD_EMUL_VIEW_POSD1):
	{
		PRINTK("[fb] CASE1 (POSD0|POSD1)\n");
		if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_POSD1_RESIZE )
		{
			GFX_StretchSurface( posd1_surf, merge_surf, 0, 0, posd1_canvas->input_win.w, posd1_canvas->input_win.h, 0, 0, 1280, 720 );
			GFX_BlitSurface( posd0_surf, merge_surf, merge_surf, 0, 0, 1280, 720, 0, 0, TRUE );
		}
		else
		{
			GFX_BlitSurface( posd0_surf, posd1_surf, merge_surf, 0, 0, 1280, 720, 0, 0, TRUE );
		}
	}
	break;

	/* CASE2: only POSD0 is shown */
	case OSD_EMUL_VIEW_POSD0:
	{
		PRINTK("[fb] CASE2 (POSD0)\n");
		GFX_BlitSurface( posd0_surf, -1, merge_surf, 0, 0, 1280, 720, 0, 0, FALSE );
	}
	break;

	/* CASE3: only POSD1 is shown */
	case OSD_EMUL_VIEW_POSD1:
	{
		PRINTK("[fb] CASE3 (POSD1)\n");
		if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_POSD1_RESIZE )
		{
			GFX_StretchSurface( posd1_surf, merge_surf, 0, 0, posd1_canvas->input_win.w, posd1_canvas->input_win.h, 0, 0, 1280, 720 );
		}
		else
		{
			GFX_BlitSurface( posd1_surf, -1, merge_surf, 0, 0, 1280, 720, 0, 0, FALSE );
		}
	}
	break;

		/* CASE4: any POSD is not shown */
		default:
		{
			PRINTK("[fb] CASE4 (empty)\n");
			GFX_ClearSurface( merge_surf, 1280, 720 );
		}
		break;
	}

	/* mrege cursor after merging POSD0 and POSD1 */
	if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_CRSR )
	{
		PRINTK("[fb] draw cursor\n");
		GFX_BlitSurface( crsr_surf, merge_surf, merge_surf, cx, cy, cw, ch, dx, dy, TRUE );
	}

	/* speical code when back image is shown */
	if( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_BACK_IMG )
	{
		int temp_surf = GFX_AllocARGBSurface( 1920, 1080, 0x0 );
		int img_surf  = GFX_AllocARGBSurface( 1920, 1080, posd0_canvas->back_image_mem.addr );
		PRINTK("^g^[fb] temp_surf %d, img_surf %d\n", temp_surf, img_surf );

		/* resize the merged POSD to be full HD size */ 
		GFX_StretchSurface( merge_surf, temp_surf, 0, 0, 1280, 720, 0, 0, 1920, 1080 );	
//		GFX_BlitSurface( merge_surf, -1, temp_surf, 0, 0, 1280, 720, 0, 0, FALSE );
		/* merge the resized POSD and image and generates one single full HD screen */
		GFX_BlitSurface( temp_surf, img_surf, full_hd_merge_surf, 0, 0, 1920, 1080, 0, 0, TRUE );

		GFX_FreeSurface ( img_surf );
		GFX_FreeSurface ( temp_surf );
	}

#ifdef ALPHA_6BIT_PREVIEW_TEST
	{
		int		i;
		UINT32* ptr;
		static UINT32* vaddr[2] = { 0x0, 0x0 };

		if ( !vaddr[0] ) vaddr[0] = (UINT32*)ioremap( g_frc_osd_emul.merge_osd_addr[0], 1280*720*4 );
		if ( !vaddr[1] ) vaddr[1] = (UINT32*)ioremap( g_frc_osd_emul.merge_osd_addr[1], 1280*720*4 );

		printk("^g^[fb] converting alpha (0x%08x:%d)\n", vaddr[g_frc_osd_emul.osd_idx], g_frc_osd_emul.osd_idx );

		ptr = vaddr[g_frc_osd_emul.osd_idx];
		for ( i=1280*720; i>0; i-- )
		{
			*ptr = ((*ptr) & 0xfcffffff); ptr++; 
		}
		wmb();
	}
#endif

header_update:
	GFX_UnlockDevice();

	/* write the merge result (FHD image) to OSD0 header. */
	if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_BACK_IMG )
	{
        struct scanvas* merge_canvas = &g_dm_ctx->winfo[0]->pixel;

		osd_hdr.osd_hdr_ptr_bmp 		= (UINT32)merge_osd_hd_addr;
		osd_hdr.type.osd.osd_hdr_w_out	= 1920;
		osd_hdr.type.osd.osd_hdr_h_out	= 1080;
		osd_hdr.type.osd.osd_hdr_w_mem	= 1920;
		osd_hdr.type.osd.osd_hdr_h_mem	= 1080;
		osd_hdr.osd_hdr_wpl 			= (1920*4)>>3;
		memcpy ( (void*)merge_canvas->uiOSDHeaderPTR, (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );
	}
	/* write the merge result (HD image) to OSD0 header. */
	else
	{
        struct scanvas* merge_canvas = &g_dm_ctx->winfo[0]->pixel;

		switch( g_frc_osd_emul.osd_view_flag )
		{
#ifdef FRC_CURSOR_PARTIAL_UPDATE
			case OSD_EMUL_VIEW_POSD1|OSD_EMUL_VIEW_CRSR:
#endif
			case OSD_EMUL_VIEW_POSD1: 					osd_hdr.osd_hdr_ptr_bmp = (UINT32)posd1_canvas->uiBitmapDataYPTR; break;

#ifdef FRC_CURSOR_PARTIAL_UPDATE
			case OSD_EMUL_VIEW_POSD0|OSD_EMUL_VIEW_CRSR:
#endif
			case OSD_EMUL_VIEW_POSD0: 					osd_hdr.osd_hdr_ptr_bmp = (UINT32)posd0_canvas->uiBitmapDataYPTR; break;

			default:									osd_hdr.osd_hdr_ptr_bmp = (UINT32)merge_osd_addr; break; 
		}

		memcpy ( (void*)merge_canvas->uiOSDHeaderPTR, (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );
	}

//	smp_mb();

	/* swap osd_idx */
	if ( b_flip ) g_frc_osd_emul.my_vsync = g_fbdev_vsync_cnt; 
	
func_exit:
	if (posd3_surf>=0) GFX_FreeSurface ( posd3_surf );
	if (posd1_surf>=0) GFX_FreeSurface ( posd1_surf );
	if (posd0_surf>=0) GFX_FreeSurface ( posd0_surf );

	/* save the current state */
	g_frc_osd_emul.osd_bm_ptr_sav[0] = posd0_canvas->uiBitmapDataYPTR;
	g_frc_osd_emul.osd_bm_ptr_sav[1] = posd1_canvas->uiBitmapDataYPTR;

	OS_UnlockMutex( &g_frc_osd_emul_mtx );
}

static void FBDEV_L9B0_MergePOSD_1080p( int layer, BOOLEAN b_flip )
{
#if 1
	struct scanvas *posd0_canvas, *posd1_canvas, *posd3_canvas;

	FBDEV_L9_OSD_HDR_T	osd_hdr;
	UINT32			merge_osd_hd_addr= 0x0;
	UINT32			posd_view_flag = 0x0;

	int				posd0_surf		= -1;
	int				posd1_surf		= -1; 
	int				posd3_surf		= -1;
	int				crsr_surf 		= -1;
	int				merge_surf 		= -1;	/* merge surface for the normal OSD */
	int				merge_hd_surf 	= -1;	/* merge surface for the HD OSD */

	static int		crsr_bkup_surf			= -1;
 	static int		merge_surf_list[2]		= {-1,-1};
 	static int		merge_hd_surf_list[2]	= {-1,-1};

	int				cx, cy, cw, ch, dx, dy;	/* cursor related value */

	cx = cy = dx = dy = 0;								/* ?? */
	cw = ch = 88;										/* ?? */

	/* POSD merge is only valid for UD mode. */
	if( g_fbdev_frc_ctrl.b_frc_UD_enable == FALSE ) return;

	PRINTK("^g^%s : %d,%d\n", __func__, layer, b_flip );

	/* disable multiple enterance !! */
	OS_LockMutex( &g_frc_osd_emul_mtx );

	posd0_canvas = &g_dm_ctx->winfo[0]->pixel;	/* POSD0 */
	posd1_canvas = &g_dm_ctx->winfo[1]->pixel;	/* POSD1 */
	posd3_canvas = &g_dm_ctx->winfo[3]->pixel;	/* POSD3 (CRSR) */

	/* collect OSD view status */
	g_frc_osd_emul.osd_view_flag	= 0x0;
	g_frc_osd_emul.osd_view_flag	|= (g_frc_osd_emul.osd_view_status[0])? OSD_EMUL_VIEW_POSD0: 0x0;
	g_frc_osd_emul.osd_view_flag	|= (g_frc_osd_emul.osd_view_status[1])? OSD_EMUL_VIEW_POSD1: 0x0;
	g_frc_osd_emul.osd_view_flag	|= (g_frc_osd_emul.osd_view_status[3])? OSD_EMUL_VIEW_CRSR:  0x0;
	g_frc_osd_emul.osd_view_flag	|= (posd0_canvas->bBackImageEnable)?	OSD_EMUL_VIEW_BACK_IMG: 0x0;
	g_frc_osd_emul.osd_view_flag	|= ( g_frc_osd_emul.osd_view_status[1] && ( posd1_canvas->input_win.w != 1280 || posd1_canvas->input_win.h != 720 ) )? OSD_EMUL_VIEW_POSD1_RESIZE: 0x0;

	/* make the real POSD flag. this flag is used to determine whether we can skip the POSD merge or not.
	 * ( OSD_EMUL_VIEW_BACK_IMG and OSD_EMUL_VIEW_CRSR flag is checked after merging POSD, so we don't need them during merge process
	 */
	posd_view_flag = g_frc_osd_emul.osd_view_flag & ~(OSD_EMUL_VIEW_CRSR|OSD_EMUL_VIEW_BACK_IMG);
	
	PRINTK("[fb] osd_view_flag = %08x (%08x)\n", g_frc_osd_emul.osd_view_flag, posd_view_flag );

	/* raxis.lim (2011/09/03)
	 * Accoring to the cursor test, I found that the invalid cursor is requested. 
	 * In that cases, cursor size is set to zero. I don't know what is wrong exactly.
	 * But some workaround shoule be added..
	 */
	if ( layer == 3 && posd3_canvas->csr_size.w == 0 && posd3_canvas->csr_size.h == 0 )
	{
		PRINTK("[fb] ignore invalid cursor request...\n"); goto func_exit;
	}

	/* initialize my_vsync control value to be '-1' to avoid incorrect swap of OSD INDEX */
	if ( layer == 0 || layer == 1 ) g_frc_osd_emul.my_vsync = -1;

	/* get the saved OSD0 header */
	memcpy( (void*)&osd_hdr, (void*)&g_frc_osd_emul.osd_hdr_sav[0], sizeof(FBDEV_L9_OSD_HDR_T) ); 

	if ( crsr_bkup_surf < 0 )			crsr_bkup_surf		= GFX_AllocARGBSurface( 128,  128, g_frc_osd_emul.crsr_bkup_addr );	 /* 128x128  */
	if ( merge_surf_list[0] < 0 )		merge_surf_list[0]	= GFX_AllocARGBSurface( 1280, 720, g_frc_osd_emul.merge_osd_addr[0] ); /* 1280x720 */
	if ( merge_surf_list[1] < 0 )		merge_surf_list[1]	= GFX_AllocARGBSurface( 1280, 720, g_frc_osd_emul.merge_osd_addr[1] ); /* 1280x720 */
	if ( merge_hd_surf_list[0] < 0 )	merge_hd_surf_list[0]= g_frc_osd_emul.merge_osd_hd_surface[0];
	if ( merge_hd_surf_list[1] < 0 )	merge_hd_surf_list[1]= g_frc_osd_emul.merge_osd_hd_surface[1];

	/* create temporary surface to merge the POSD source */
	posd0_surf	= GFX_AllocARGBSurface( 1280, 720, posd0_canvas->uiBitmapDataYPTR );
	posd1_surf	= GFX_AllocARGBSurface( 1280, 720, posd1_canvas->uiBitmapDataYPTR );
	posd3_surf	= GFX_AllocARGBSurface(  128, 128, posd3_canvas->uiBitmapDataYPTR );
	crsr_surf	= posd3_surf;

	/* get active OSD frame buffer and destination OSD surface */
	merge_osd_hd_addr	= g_frc_osd_emul.merge_osd_hd_addr[g_frc_osd_emul.osd_idx];
	merge_surf			= merge_surf_list[0]; //g_frc_osd_emul.osd_idx];
	merge_hd_surf		= merge_hd_surf_list[g_frc_osd_emul.osd_idx];
	
	PRINTK("[fb] UD %d-%d-%d %08x:%08x:%08x (%08x %08x (0x%x->0x%x 0x%x) Idx %d flip %d layer %d\n", 
												g_frc_osd_emul.osd_view_status[0], g_frc_osd_emul.osd_view_status[1], g_frc_osd_emul.osd_view_status[3], 
												posd0_canvas->uiBitmapDataYPTR,
												posd1_canvas->uiBitmapDataYPTR,
												posd3_canvas->uiBitmapDataYPTR,
												g_frc_osd_emul.merge_osd_hd_addr[0],	
												g_frc_osd_emul.merge_osd_hd_addr[1],
												merge_surf,
												merge_hd_surf,
												merge_osd_hd_addr,
												g_frc_osd_emul.osd_idx, b_flip, layer );

	GFX_LockDevice();

	/* if only single POSD is updated, go to the header_update without any action !! */
	if ( posd_view_flag == OSD_EMUL_VIEW_POSD0 || posd_view_flag == OSD_EMUL_VIEW_POSD1 )
	{
		PRINTK("[fb] CASE(-1)\n");
//		b_flip = FALSE;		/* disable merge_osd flip */
		goto posd_merge_done;
	}

	/* if cursor layer is shown, process(scale down) the cursor to fit the virtual POSD.
	 * cursor image may be drawn to the merge surface or POSD surface directly. 
	 */  
	if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_CRSR )
	{
		int	csr_x_pos, csr_y_pos;	

		csr_y_pos  = posd3_canvas->output_win.y - posd3_canvas->csr_hotspot.y;	/* cursor y */
		csr_x_pos  = posd3_canvas->output_win.x - posd3_canvas->csr_hotspot.x;	/* cursor x */

//		csr_y_pos = FRC_OSD_EMUL_CALC_CRSR(csr_y_pos);					/* 1280x720 dimension */
//		csr_x_pos = FRC_OSD_EMUL_CALC_CRSR(csr_x_pos);					/* 1280x720 dimension */
		csr_x_pos = LX_CALC_ALIGNED_VALUE(csr_x_pos,1); 				/* make even number to meed alignment reguirement of GFX H/W */

		if ( csr_x_pos < 1920 && csr_y_pos < 1080 )
		{
			if 		( csr_x_pos < 0	)   { cx = -csr_x_pos; cw = 128 - cx; dx = 0 ;}
			else if ( csr_x_pos >= 1792){ cx = 0; cw = 128-(csr_x_pos-1792); dx=csr_x_pos; }
			else                        { cx = 0; cw = 128; dx = csr_x_pos ; }

			if 		( csr_y_pos < 0 )   { cy = -csr_y_pos; ch = 128 - cy; dy = 0 ;}
			else if ( csr_y_pos >= 952 ){ cy = 0; ch = 128-(csr_y_pos-952); dy=csr_y_pos; }
			else                        { cy = 0; ch = 128; dy = csr_y_pos ; }

			printk("^c^[csr] %4d,%4d (%3d,%3d %3d,%3d) :: %d.%d.%d.%d -> %d.%d.%d.%d\n", 
								csr_x_pos, csr_y_pos, 
								posd3_canvas->csr_hotspot.x, posd3_canvas->csr_hotspot.y, posd3_canvas->csr_size.w, posd3_canvas->csr_size.h,
								cx, cy, cw, ch, dx, dy, cw, ch );

			/* confirm crsr_surf is the same as posd3_surf. ok ! */
		}
	}

	/* BEGIN of the (slow) normal update process
	 *
	 * POSD merge is very tricky and special code for L9A0,B0 revision.
	 * the below code is not optimizaed but well working routine.
	 */

	/* CASE1: both POSD0 and POSD1 is shown */
	switch( g_frc_osd_emul.osd_view_flag & (OSD_EMUL_VIEW_POSD0|OSD_EMUL_VIEW_POSD1) )
	{	
		case (OSD_EMUL_VIEW_POSD0|OSD_EMUL_VIEW_POSD1):
		{
			PRINTK("[fb] CASE1 (POSD0|POSD1)\n");
			if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_POSD1_RESIZE )
			{
				GFX_StretchSurface( posd1_surf, merge_surf, 0, 0, posd1_canvas->input_win.w, posd1_canvas->input_win.h, 0, 0, 1280, 720 );
				GFX_BlitSurface( posd0_surf, merge_surf, merge_surf, 0, 0, 1280, 720, 0, 0, TRUE );
			}
			else
			{
				GFX_BlitSurface( posd0_surf, posd1_surf, merge_surf, 0, 0, 1280, 720, 0, 0, TRUE );
			}
		}
		break;

		/* CASE2: only POSD0 is shown */
		case OSD_EMUL_VIEW_POSD0:
		{
			PRINTK("[fb] CASE2 (POSD0)\n");
			GFX_BlitSurface( posd0_surf, -1, merge_surf, 0, 0, 1280, 720, 0, 0, FALSE );
		}
		break;

		/* CASE3: only POSD1 is shown */
		case OSD_EMUL_VIEW_POSD1:
		{
			PRINTK("[fb] CASE3 (POSD1)\n");
			if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_POSD1_RESIZE )
			{
				GFX_StretchSurface( posd1_surf, merge_surf, 0, 0, posd1_canvas->input_win.w, posd1_canvas->input_win.h, 0, 0, 1280, 720 );
			}
			else
			{
				GFX_BlitSurface( posd1_surf, -1, merge_surf, 0, 0, 1280, 720, 0, 0, FALSE );
			}
		}
		break;

		/* CASE4: any POSD is not shown. 
	 	 * In this case, clear HD surface directly and skip POSD stretch !!. this can speed up the POSD merge
		 */
		default:
		{
			PRINTK("[fb] CASE4 (empty)\n");
			GFX_ClearSurface( merge_hd_surf, 1920, 1080 );
			goto posd_stretch_done;
		}
		break;
	}

	/* POSD0, POSD1 is merged. stretch to HD surface and copy cursor image onto it !!! */
posd_merge_done:
	{
		int		src_surf;

		/* select src_surf based on the active POSD condition */
		switch( posd_view_flag )
		{
			case OSD_EMUL_VIEW_POSD1:	src_surf = posd1_surf; break;
			case OSD_EMUL_VIEW_POSD0:	src_surf = posd0_surf; break;
			default:					src_surf = merge_surf; break;
		}

		GFX_StretchSurface( src_surf, merge_hd_surf, 0, 0, 1280, 720, 0, 0, 1920, 1080 );	

posd_stretch_done:
		/* post step #1: if BACK image is available, blend back image + scaled POSD merge ! */
		if( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_BACK_IMG )
		{
			int img_surf = GFX_AllocARGBSurface( 1920, 1080, posd0_canvas->back_image_mem.addr );
			GFX_BlitSurface( merge_hd_surf, img_surf, merge_hd_surf, 0, 0, 1920, 1080, 0, 0, TRUE );
			GFX_FreeSurface ( img_surf );
		}

		/* post step #2: mrege cursor after merging POSD0 and POSD1 */
		if ( g_frc_osd_emul.osd_view_flag & OSD_EMUL_VIEW_CRSR )
		{
			PRINTK("[fb] draw cursor\n");
			GFX_BlitSurface( crsr_surf, merge_hd_surf, merge_hd_surf, cx, cy, cw, ch, dx, dy, TRUE );
		}

		GFX_UnlockDevice();

		/* FHD OSD is ready, write PSD0 header */
		{
			struct scanvas* merge_canvas = &g_dm_ctx->winfo[0]->pixel;
	
			osd_hdr.osd_hdr_ptr_bmp 		= (UINT32)merge_osd_hd_addr;
			osd_hdr.type.osd.osd_hdr_w_out	= 3840;	/* confirmed by ±è¿õÇö */
			osd_hdr.type.osd.osd_hdr_h_out	= 2160;	/* confirmed by ±è¿õÇö */
			osd_hdr.type.osd.osd_hdr_w_mem	= 1920;	/* confirmed by ±è¿õÇö */
			osd_hdr.type.osd.osd_hdr_h_mem	= 1080;	/* confirmed by ±è¿õÇö */
			osd_hdr.osd_hdr_wpl 			= (1920*4)>>3;

			PRINTK("[fb] UD wr_reg : in %dx%d out %dx%d stride %d wpl %d \n", 
													osd_hdr.type.osd.osd_hdr_w_mem, osd_hdr.type.osd.osd_hdr_h_mem,
													osd_hdr.type.osd.osd_hdr_w_out, osd_hdr.type.osd.osd_hdr_h_out,
													1920*4,
													osd_hdr.osd_hdr_wpl );
			memcpy ( (void*)merge_canvas->uiOSDHeaderPTR, (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );
		}
	}

//	smp_mb();

	/* swap osd_idx */
	if ( b_flip ) g_frc_osd_emul.my_vsync = g_fbdev_vsync_cnt; 
	
func_exit:
	if (posd3_surf>=0) GFX_FreeSurface ( posd3_surf );
	if (posd1_surf>=0) GFX_FreeSurface ( posd1_surf );
	if (posd0_surf>=0) GFX_FreeSurface ( posd0_surf );

	/* save the current state */
	g_frc_osd_emul.osd_bm_ptr_sav[0] = posd0_canvas->uiBitmapDataYPTR;
	g_frc_osd_emul.osd_bm_ptr_sav[1] = posd1_canvas->uiBitmapDataYPTR;

	OS_UnlockMutex( &g_frc_osd_emul_mtx );
#endif
}

/*========================================================================================
	chip revision handler
========================================================================================*/
FBDEV_L9_HW_FUNC_T  g_fbdev_l9b0_hw_func =
{
    .L9_InitHWCtx         = FBDEV_L9B0_InitHWCtx,
    .L9_SetConnCtrl     = FBDEV_L9B0_SetConnCtrl,
    .L9_WriteOSDHeader  = FBDEV_L9B0_WriteOSDHeader,
    .L9_SetOSDEnable    = FBDEV_L9B0_SetOSDEnable,
    .L9_GetOSDEnable    = FBDEV_L9B0_GetOSDEnable,
    .L9_ISRTickHandler  = FBDEV_L9B0_ISRTickHandler,
    .L9_SetTridCtrl     = NULL,
    .L9_CheckCaps       = FBDEV_L9B0_CheckCaps,
    .L9_SetGPUClk       = FBDEV_L9B0_SetGPUClk,
};

