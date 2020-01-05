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
#undef	FBDEV_USE_OSD_STATUS_MON

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_drv.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_hw_h13.h"
#include "fbdev_reg_h13.h"

#include "../sys/ctop_regs.h"
#include "gfx_draw.h"
#include <linux/version.h>


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PRINTK(fmt,args...)						//printk(##fmt,args)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#if 0
typedef struct
{
	int                 osd_idx;
	int                 fb_dev_id;				/* OSD Id used for OSD merger */

	int					posd0_hd_surface;
	int					posd1_hd_surface;

	BOOLEAN				b_crsr_draw_req;		/* indicate asynchrnous cursor render requested or not */

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
	BOOLEAN             osd_view_status[LX_FBDEV_ID_MAX];

	FBDEV_H13_OSD_HDR_T		osd_hdr_sav[LX_FBDEV_ID_MAX];	
}
FBDEV_FRC_OSD_EMUL_DATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
extern	volatile OSD_H13_REG_T*		g_fbdev_h13_reg;
extern	OSD_H13_REG_T*				g_fbdev_h13_reg_cached;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static const int 					pixel_depth_2_bpp[PIX_DEPTH_MAX] = { 1, 2, 4, 8, 16, 24, 32  };
#if 0
static FBDEV_FRC_OSD_EMUL_DATA_T	g_frc_osd_emul;
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/

/** initialize H13(A1) HW Ctx, Cfg and all chip dependent variables.
 * 
 */
void	FBDEV_H13A0_InitHW ( void )
{
	g_fbdev_frc_ctrl.b_frc_sep_enable	= FALSE;				/* Blending Mode by default */
	g_fbdev_frc_ctrl.b_frc_UD_enable	= FALSE;				/* Standard Mode by default */
	g_fbdev_frc_ctrl.b_frc_hdr_emul		= FALSE;				/* Disable FRC HDR emulation */
	g_fbdev_frc_ctrl.b_frc_osd_emul		= TRUE;
	g_fbdev_frc_ctrl.frc_hdr_emul_dev	= -1;
}

/** OSD HW Layer enable/disable
 *
 * @param	int layer : osd layer ,
 *		enable : 0 : display off , 1 : display on
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_H13A0_SetOSDEnable(int layer , int enable)
{
	int ret = RET_ERROR;

	FBDEV_TRACE_BEGIN();
	FBDEV_CHECK_CODE( layer<0 || layer>=LX_FBDEV_ID_MAX, goto func_exit, "invalid layer %d\n", layer );

#if 0
	/* save POSD view status for FRC emulation */
	g_frc_osd_emul.osd_view_status[layer] = enable;
#endif

#if 0
	/* if FRC emulation mode, ignore show/hide request for OSD2 */
    if ( g_fbdev_frc_ctrl.b_frc_UD_enable )
	{
		/* merge POSDs to the single POSD */
		//FBDEV_H13A0_MergePOSD( layer, FALSE );
	}
	else
#endif
	{
		switch(layer)
		{
			case LX_FBDEV_ID_OSD0:	g_fbdev_h13_reg->osd0_ctrl_main.osd0_en = enable; break;
			case LX_FBDEV_ID_OSD1:	g_fbdev_h13_reg->osd1_ctrl_main.osd1_en = enable; break;
			case LX_FBDEV_ID_OSD2:	g_fbdev_h13_reg->osd2_ctrl_main.osd2_en = enable; break;
			case LX_FBDEV_ID_CSR0:	g_fbdev_h13_reg->osd3_ctrl_main.osd3_en = enable; break;
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
int FBDEV_H13A0_GetOSDEnable(int layer)
{
	int ret = 0;

#if 0
	/* if FRC OSD enabled, just return the pseudo OSD status */
    if ( g_fbdev_frc_ctrl.b_frc_UD_enable )
	{
		return g_frc_osd_emul.osd_view_status[layer];
	}
#endif

	switch(layer)
	{
		case LX_FBDEV_ID_OSD0:	ret = g_fbdev_h13_reg->osd0_ctrl_main.osd0_en;	break;
		case LX_FBDEV_ID_OSD1:	ret = g_fbdev_h13_reg->osd1_ctrl_main.osd1_en; break;
		case LX_FBDEV_ID_OSD2:	ret = g_fbdev_h13_reg->osd2_ctrl_main.osd2_en; break;
		case LX_FBDEV_ID_CSR0:	ret = g_fbdev_h13_reg->osd3_ctrl_main.osd3_en; break;
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
int FBDEV_H13A0_WriteOSDHeader( struct scanvas *pCanvas )
{
	int				ret;
	int				fb_dev_id;
	UINT32			bitmap_ptr;
	FBDEV_H13_OSD_HDR_T osd_hdr;
	struct scanvas	canvas;

	/* clear osd_hdr before writing */
	memset( &osd_hdr, 0x0, sizeof(FBDEV_H13_OSD_HDR_T) );
	memcpy( &canvas, pCanvas, sizeof(struct scanvas) );

	ret = 0; //down_interruptible(&fbdev_sem_h13);

	fb_dev_id	= canvas.fb_dev_id;

	switch( fb_dev_id )
	{
		case LX_FBDEV_ID_CSR0:
		{
            /* if cursor csr_hotspot is active then adjust (x,y) position of cursor layer.
             * if cursor position is negative, I should move the bitmap address ( H/W doesn't accept negative position )
             *
             * IMPORTATNT !! if you change the base address, its alignment should be multiplt of 16 byte ( not 8 byte )
             * woonghyeon just said that it may be H/W bug.
             * since we are using ARGB8888 pixel format for cursor OSD. cursor offset should be multiple of 4 !!
			 */
			int csr_x_max = canvas.stride / (canvas.bits_per_pixel>>3);

			int csr_x_off = 0;
			int csr_y_off = 0;
			int csr_x_pos = canvas.output_win.x - canvas.csr_hotspot.x;
			int csr_y_pos = canvas.output_win.y - canvas.csr_hotspot.y;
			int csr_x_size= (canvas.csr_size.w)? LX_CALC_ALIGNED_VALUE(canvas.csr_size.w,2) : canvas.input_win.w;
			int csr_y_size= (canvas.csr_size.h)? canvas.csr_size.h : canvas.input_win.h;

			PRINTK("[fb#0] pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) max_x %d\n", csr_x_pos, csr_y_pos, csr_x_size, csr_y_size, 
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y, csr_x_max ); 

			/* too small cursor with may lead to OSD corruption. According to system test, width should be greater than a half of OSD width */
            if ( csr_x_pos < 0 ) { csr_x_off = -csr_x_pos; csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2); csr_x_pos = 0; csr_x_size -= csr_x_off; }
            if ( csr_y_pos < 0 ) { csr_y_off = -csr_y_pos; csr_y_pos = 0; csr_y_size -= csr_y_off; }
            if ( csr_x_size < 32 ) 			csr_x_size = 32;		/* for preventing OSD H/W crash */
			if ( csr_x_size > csr_x_max )	csr_x_size = csr_x_max;	/* for preventing OSD garbage */

            /* raxis.lim@lge.com (2011/09/23)
             * L9 donesn't support odd numbered x position when cursor is located to the far right side of the screen
             */
            if ( csr_x_pos + csr_x_size > 1920 ) csr_x_pos = LX_CALC_ALIGNED_VALUE(csr_x_pos,1);

			osd_hdr.type.crsr.osd_hdr_xpos			= csr_x_pos;	/* output x (csr x pos) */
			osd_hdr.type.crsr.osd_hdr_ypos			= csr_y_pos;	/* output y (csr y pos) */
			osd_hdr.type.crsr.osd_hdr_w_mem			= csr_x_size;	/* viewing cursor width */
			osd_hdr.type.crsr.osd_hdr_h_mem			= csr_y_size;
			osd_hdr.type.crsr.osd_hdr_w_out			= csr_x_size;	/* output w */
			osd_hdr.type.crsr.osd_hdr_h_out			= csr_y_size;	/* output h */

			/* gMAU requests 16byte aligned address */
			bitmap_ptr	= canvas.uiBitmapDataYPTR;
            bitmap_ptr += ( csr_y_off * canvas.stride ) + LX_CALC_ALIGNED_VALUE((csr_x_off * (canvas.bits_per_pixel>>3)),4);

			osd_hdr.type.osd.osd_hdr_pixel_order	= canvas.bPixelOrderEnable;
			osd_hdr.osd_hdr_wpl 					= canvas.stride>>3;

			PRINTK("[fb#1] pos %dx%d csr_sz %d,%d info( %dx%d h %d,%d ) \n\n", csr_x_pos, csr_y_pos, csr_x_size, csr_y_size, 
						canvas.output_win.x, canvas.output_win.y, canvas.csr_hotspot.x, canvas.csr_hotspot.y ); 
		}
		break;

		case LX_FBDEV_ID_OSD0:
		case LX_FBDEV_ID_OSD1:
		default:
		{
			/* raxis.lim (2012/11/16) -- handle CLUT
			 * if POSD is configured to 8bpp, this function will convert it to 32bpp image.
			 * DO NOT forget that this function will replace some canvas variable.
			 */
			FBDEV_H13CMN_HandleCLUT( fb_dev_id, &canvas, &osd_hdr );

			osd_hdr.type.osd.osd_hdr_color_key_en= canvas.bColorKeyEnable;

			osd_hdr.type.osd.osd_hdr_w_out		= canvas.output_win.w;	/* output w */
			osd_hdr.type.osd.osd_hdr_h_out		= canvas.output_win.h;	/* output h */
			osd_hdr.type.osd.osd_hdr_xpos	 	= canvas.output_win.x;	/* output x */
			osd_hdr.type.osd.osd_hdr_ypos 		= canvas.output_win.y;	/* output y */
			osd_hdr.type.osd.osd_hdr_w_mem 		= canvas.input_win.w;	/* input w  */
			osd_hdr.type.osd.osd_hdr_h_mem 		= canvas.input_win.h;	/* input h  */

			bitmap_ptr	= canvas.uiBitmapDataYPTR;

			/* modify bitmap ptr for input position is provided */
			if ( canvas.input_win.x > 0 || canvas.input_win.y > 0 )
			{
				/* gMAU requests 16byte aligned address */
				bitmap_ptr += ( canvas.input_win.y ) * canvas.stride;
				bitmap_ptr += LX_CALC_ALIGNED_VALUE( ((canvas.input_win.x*canvas.bits_per_pixel)>>3), 4);
			}
			PRINTK("[fb] %s: fb %d, bitmap param (%d,%d,%d,%d) stride %d ptr 0x%08x\n", __F__, fb_dev_id, 
					canvas.input_win.x, canvas.input_win.y, 
					canvas.input_win.w, canvas.input_win.h, 
					canvas.stride, bitmap_ptr );

			if ( g_fbdev_frc_ctrl.b_frc_sep_enable ) 
			{
				/* when 3Dmode enabled, input window should be shrinked so OSD h/w make double-sized screen */
				if( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode == LX_FBDEV_TRID_MODE_SS )
				{
					osd_hdr.type.osd.osd_hdr_w_mem >>= 1;
//					PRINTK("^g^TRID MODE = SS (%d,%d)\n", osd_hdr.type.osd.osd_hdr_w_mem, osd_hdr.type.osd.osd_hdr_h_mem );
				}
				else if ( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode == LX_FBDEV_TRID_MODE_TB )
				{
					osd_hdr.type.osd.osd_hdr_h_mem >>= 1;
//					PRINTK("^g^TRID MODE = TB (%d,%d)\n", osd_hdr.type.osd.osd_hdr_w_mem, osd_hdr.type.osd.osd_hdr_h_mem );
				}
				else
				{
					/* do nothing */
				}
			}

			osd_hdr.type.osd.osd_hdr_pixel_order= canvas.bPixelOrderEnable;
			osd_hdr.osd_hdr_wpl 				= canvas.stride>>3;

		}
		break;
	}

	/* copy common attribute */
    osd_hdr.osd_hdr_format          = FBDEV_GetOSDPxlFmt( canvas.bits_per_pixel );
    osd_hdr.osd_hdr_depth           = FBDEV_GetOSDPxlDepth( canvas.bits_per_pixel );

	osd_hdr.osd_hdr_global_alpha_en	= canvas.bGlobalAlphaEnable;
	osd_hdr.osd_hdr_global_alpha	= (canvas.bGlobalAlphaEnable)? canvas.usGlobalAlpha : 0xff;
	osd_hdr.osd_hdr_color_key		= canvas.uiOSDColorKey;

	if ( g_reg_io_ctx->slkrd_prefix_mask )
	{
		osd_hdr.osd_hdr_ptr_bmp		= ((bitmap_ptr & 0x0FFFFFFF)| g_reg_io_ctx->slkrd_prefix_mask );
		osd_hdr.osd_hdr_ptr_plte	= ((canvas.uiPalettePTR&0x0FFFFFFF)| g_reg_io_ctx->slkrd_prefix_mask );
	}
	else
	{
		osd_hdr.osd_hdr_ptr_bmp		= bitmap_ptr;
		osd_hdr.osd_hdr_ptr_plte	= canvas.uiPalettePTR;
	}

	/* handle virtual OSD if requested */
	FBDEV_H13CMN_HandleVOSD( fb_dev_id, &canvas, &osd_hdr );

	/* handle S3D if requestd */
	FBDEV_H13CMN_Handle3DOSD( fb_dev_id, &canvas, &osd_hdr );

	/* handle reverse OSD if requested */
	FBDEV_H13CMN_HandleReverseOSD( fb_dev_id, &canvas, &osd_hdr );

	PRINTK("[fb] %s: fb %d, bitmap param (%d,%d,%d,%d) stride %d ptr 0x%08x (final)\n", __F__, fb_dev_id, 
			canvas.input_win.x, canvas.input_win.y, 
			canvas.input_win.w, canvas.input_win.h, 
			canvas.stride, bitmap_ptr );

	FBDEV_H13CMN_WriteHdrRegs	( fb_dev_id, &osd_hdr );

	/* update FRC header if FRC SEP path enabled */
	FBDEV_H13CMN_WriteFRCHeader( );
//	up(&fbdev_sem_h13);
	return RET_OK;
}

/*========================================================================================
	Implementation Group (ISR)
========================================================================================*/
void FBDEV_H13A0_ISRTickHandler ( void )
{
#if 0
	/* if new vsync arrived, swap osd idx */
	if ( g_fbdev_frc_ctrl.b_frc_UD_enable
		&& g_frc_osd_emul.my_vsync >= 0 && g_frc_osd_emul.my_vsync != g_fbdev_vsync_cnt )
	{
		PRINTK("OSD Vsync...[%d]\n", g_frc_osd_emul.osd_idx );
		g_frc_osd_emul.osd_idx ^= 1;
		g_frc_osd_emul.my_vsync = -1;
	}
#endif

#ifdef FBDEV_USE_OSD_STATUS_MON	/* debug only */
	UINT32* a0 = (UINT32*) &g_fbdev_h13_reg->osd0_ctrl_main;
	UINT32* a1 = (UINT32*) &g_fbdev_h13_reg->osd0_ctrl_base_addr;
	UINT32* a2 = (UINT32*) &g_fbdev_h13_reg->osd0_ctrl_hdr6;
	UINT32* b0 = (UINT32*) &g_fbdev_h13_reg->osd1_ctrl_main;
	UINT32* b1 = (UINT32*) &g_fbdev_h13_reg->osd1_ctrl_base_addr;
	UINT32* b2 = (UINT32*) &g_fbdev_h13_reg->osd1_ctrl_hdr6;

	printk("POSD0 0x%08x, 0x%08x, 0x%08x  POSD1 0x%08x, 0x%08x, 0x%08x\n", *a0, *a1, *a2, *b0, *b1, *b2 );
#endif

	FBDEV_H13CMN_HandleISR ( );
}

/*========================================================================================
	Implementation Group (PATH)
========================================================================================*/
/** set OSD output ctrl
 *
 *	@param pConnCtrl [IN] connection control data
 *	@return RET_OK if success, RET_ERROR otherwise
 *
 */
int     FBDEV_H13A0_SetConnCtrl           (LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
	//TODO:
	return RET_OK;
}

static int FBDEV_H13A0_SetOutPathCtrl(int layer, LX_FBDEV_OUT_PATH_CTRL_T * ctrl)
{
	//TODO:
	return RET_OK;
}

/*========================================================================================
    chip revision handler
=======================================================================================*/
FBDEV_H13_HW_CTX_T  g_fbdev_h13a0_hw_ctx =
{
	/* variable is initialize at fbdev_drv_h13.c */

    .H13_InitHW			 = FBDEV_H13A0_InitHW,

	.H13_SetViewCtrl	 = FBDEV_H13CMN_SetViewCtrl,
	.H13_SetOutPathCtrl	 = FBDEV_H13A0_SetOutPathCtrl,
    .H13_SetConnCtrl     = FBDEV_H13A0_SetConnCtrl,
    .H13_SetTridCtrl     = FBDEV_H13CMN_SetTridCtrl,

    .H13_WriteOSDHeader  = FBDEV_H13A0_WriteOSDHeader,
    .H13_SetOSDEnable    = FBDEV_H13A0_SetOSDEnable,
    .H13_GetOSDEnable    = FBDEV_H13A0_GetOSDEnable,
    .H13_ISRTickHandler  = FBDEV_H13A0_ISRTickHandler,
};

