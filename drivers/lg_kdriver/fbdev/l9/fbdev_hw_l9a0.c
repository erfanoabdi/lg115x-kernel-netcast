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
#undef	FRCIII_TEST_ON_URSA
#define PRINTK(fmt,args...)		//printk(##fmt,args)

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_hw_l9.h"
#include "fbdev_util_l9.h"
#include "fbdev_reg_l9a0.h"

#include "gfx_draw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	FRC_HDR_EMUL_XRES			1920
#define	FRC_HDR_EMUL_YRES			1081
#define	FRC_HDR_EMUL_XOFF			0
#define	FRC_HDR_EMUL_YOFF			1

#define	FRC_HDR_EMUL_DEVID			2			/* OSD2 */
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

	UINT32              hdr_phys_addr;
	UINT32              hdr_virt_addr;      /* virtual address of FRC header for the direct access */

	UINT32              frc_hdr[6];         /* FRC header data */
	UINT32              frc_hdr_remap[6];   /* FRC header data (after remap) */
}
FBDEV_FRC_HDR_EMUL_DATA_T;

typedef struct
{
	int                 osd_idx;
	UINT32				crsr_addr;			/* physical address for stretching cursor */
	UINT32              osd_addr[2];        /* two physical address for merging POSDs */
	int                 fb_dev_id;          /* OSD Id used for OSD merger */

	int					my_vsync;

	BOOLEAN             osd_view_status[LX_FBDEV_ID_MAX];
	FBDEV_L9_OSD_HDR_T		osd_hdr_sav[LX_FBDEV_ID_MAX];	
}
FBDEV_FRC_OSD_EMUL_DATAT_T;

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
static void FBDEV_L9A0_WriteFRCHeader	( void );
static void	FBDEV_L9A0_MergePOSD 		( int layer, BOOLEAN b_flip );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static const int 					pixel_depth_2_bpp[PIX_DEPTH_MAX] = { 1, 2, 4, 8, 16, 24, 32  };
static FBDEV_FRC_HDR_EMUL_DATA_T	g_frc_hdr_emul;
static FBDEV_FRC_OSD_EMUL_DATAT_T	g_frc_osd_emul;
static OS_SEM_T  		     		g_frc_osd_emul_mtx;

/*========================================================================================
	Implementation Group
========================================================================================*/

/** initialize L9A0(A1) HW Ctx & Cfg 
 *
 * 
 */
void FBDEV_L9A0_InitHWCtx ( void )
{
	PRINTK("^g^[fb] L9A0(A1) HW Ctx....\n");

	OS_InitMutex ( &g_frc_osd_emul_mtx, OS_SEM_ATTR_DEFAULT );	/* create simple mutex */

	g_fbdev_frc_ctrl.b_frc_sep_enable	= FALSE;	/* Blending Mode by default */
	g_fbdev_frc_ctrl.b_frc_hdr_emul		= TRUE;
	g_fbdev_frc_ctrl.b_frc_osd_emul		= TRUE;
	g_fbdev_frc_ctrl.frc_hdr_emul_dev	= FRC_HDR_EMUL_DEVID;

    {
	    g_frc_osd_emul.crsr_addr    = 0x0;
	    g_frc_osd_emul.osd_addr[0]  = 0x0;
		g_frc_osd_emul.osd_addr[1]  = 0x0;
		g_frc_osd_emul.osd_idx		= 0;
		g_frc_osd_emul.my_vsync		= -1;
    }
}

/** OSD HW Layer enable/disable
 *
 * @param	int layer : osd layer ,
 *		enable : 0 : display off , 1 : display on
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9A0_SetOSDEnable(int layer , int enable)
{
	int ret = RET_OK;

	FBDEV_TRACE_BEGIN();

	/* if FRC SEP enabled, POSD0 should always enabled !!! (POSD0 is merge destination) */
    if ( g_fbdev_frc_ctrl.b_frc_sep_enable && layer == LX_FBDEV_ID_OSD0 ) 
	{
		enable = TRUE;
		g_fbdev_l9_reg->osd0_cfg.osd0_en = TRUE;
	}

	/* save POSD view status for FRC emulation */
	g_frc_osd_emul.osd_view_status[layer] = enable;

	/* if FRC emulation mode, ignore show/hide request for OSD2 */
    if ( g_fbdev_frc_ctrl.b_frc_sep_enable && layer != FRC_HDR_EMUL_DEVID )
	{
		/* merge POSDs to the single POSD */
		FBDEV_L9A0_MergePOSD( layer, FALSE );
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

	FBDEV_TRACE_END();
	return ret;
}

/** OSD HW Layer status
 *
 * @param	void
 * @return	int 1 : ON , 0 : OFF
 *
 */
int FBDEV_L9A0_GetOSDEnable(int layer)
{
	int ret = 0;

	/* if FRC OSD enabled, just return the pseudo OSD status */
    if ( g_fbdev_frc_ctrl.b_frc_sep_enable )
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
int FBDEV_L9A0_WriteOSDHeader( struct scanvas *hCanvas )
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
	 * -- OSD 와 CRSR 의 register 크기가 틀려서 틀려서 동일 코드가 중복되어 있다. 차후 정리 요망.
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
#if 0
			int	csr_y_size= (hCanvas->csr_size.h)? hCanvas->csr_size.h : hCanvas->input_win.h;
#else
			int	csr_y_size = hCanvas->input_win.h;
#endif
			/* too small cursor with may lead to OSD corruption. According to system test, width should be greater than a half of OSD width */
			if ( csr_x_size < (hCanvas->input_win.w>>1) ) csr_x_size = (hCanvas->input_win.w>>1);

#ifdef FBDEV_GP_USE_16BIT_CURSOR
			if ( csr_x_pos < 0 ) { csr_x_off = -csr_x_pos; csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,3); csr_x_pos = 0; }
#else
			if ( csr_x_pos < 0 ) { csr_x_off = -csr_x_pos; csr_x_off = LX_CALC_ALIGNED_VALUE(csr_x_off,2); csr_x_pos = 0; }
#endif
			if ( csr_y_pos < 0 ) { csr_y_off = -csr_y_pos; csr_y_pos = 0; }

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

			/* workaround to support FRC HDR emulation */
			if ( g_fbdev_frc_ctrl.b_frc_sep_enable )
			{
				osd_hdr.type.crsr.osd_hdr_ypos 		= csr_y_pos+1;			/* output y (csr y pos) */
			}

			/* if offset value is valid, move bitmap address */
			bitmap_ptr += ( csr_y_off * hCanvas->stride ) + ( csr_x_off * (hCanvas->bits_per_pixel>>3) );
#if 0
			PRINTK("csr off : %d %d, pos ; %d %d, sz %d %d, bm 0x%08x\n", 
							csr_x_off, csr_y_off, osd_hdr.type.crsr.osd_hdr_xpos, osd_hdr.type.crsr.osd_hdr_ypos,
							osd_hdr.type.crsr.osd_hdr_w_mem, osd_hdr.type.crsr.osd_hdr_h_mem, bitmap_ptr );
#endif
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

			osd_hdr.type.osd.osd_hdr_pixel_order= hCanvas->bPixelOrderEnable;
			osd_hdr.osd_hdr_wpl 				= hCanvas->stride>>3;

			if ( g_fbdev_frc_ctrl.b_frc_sep_enable && g_fbdev_frc_ctrl.b_frc_hdr_emul )
			{
				if ( FRC_HDR_EMUL_DEVID == fb_dev_id )	/* OSD 2 */
				{
					osd_hdr.type.osd.osd_hdr_w_out		= 1920;				/* output w */
					osd_hdr.type.osd.osd_hdr_h_out		= 1;				/* output h */
					osd_hdr.type.osd.osd_hdr_ypos 		= 0;				/* output x */
					osd_hdr.type.osd.osd_hdr_ypos 		= 0;				/* output y */
					osd_hdr.type.osd.osd_hdr_w_mem 		= 1920;				/* input w  */
					osd_hdr.type.osd.osd_hdr_h_mem 		= 1;				/* input h  */
					osd_hdr.osd_hdr_wpl 				= 1920*4;			/* stride   */
				}
				/* normal OSD is copied to the position (0,1) to avoid FRC header corruption */
				else
				{
					osd_hdr.type.osd.osd_hdr_w_out		= 1920;				/* output w */
					osd_hdr.type.osd.osd_hdr_h_out		= 1080+1;			/* output h */
					osd_hdr.type.osd.osd_hdr_ypos 		+=1;				/* output y */
				}
			}
		}
		break;
	}

	osd_hdr.osd_hdr_format 			= FBDEV_GetOSDPxlFmt( hCanvas->bits_per_pixel );
	osd_hdr.osd_hdr_depth 			= FBDEV_GetOSDPxlDepth( hCanvas->bits_per_pixel );

	/* if OSD2, turn on the global alpha mode */
	if ( g_fbdev_frc_ctrl.b_frc_sep_enable && g_fbdev_frc_ctrl.b_frc_hdr_emul && FRC_HDR_EMUL_DEVID == fb_dev_id )
	{
		osd_hdr.osd_hdr_global_alpha_en	= 0x1;
		osd_hdr.osd_hdr_global_alpha	= 0xff;
	}
	else
	{
		osd_hdr.osd_hdr_global_alpha_en	= hCanvas->bGlobalAlphaEnable;
		osd_hdr.osd_hdr_global_alpha	= hCanvas->usGlobalAlpha;
	}

	osd_hdr.osd_hdr_color_key		= hCanvas->uiOSDColorKey;

	/* hook bitmap address when current fb_dev_id is for HDR emulation */
	if ( g_fbdev_frc_ctrl.b_frc_sep_enable && g_fbdev_frc_ctrl.b_frc_hdr_emul && FRC_HDR_EMUL_DEVID == fb_dev_id )
	{
		bitmap_ptr					= g_frc_hdr_emul.hdr_phys_addr;
	}

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
	if ( g_fbdev_frc_ctrl.b_frc_sep_enable && FRC_HDR_EMUL_DEVID != fb_dev_id )
	{
		/* save header for merging */
		memcpy( (void*)&g_frc_osd_emul.osd_hdr_sav[fb_dev_id], (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );

		FBDEV_L9A0_MergePOSD( fb_dev_id, TRUE );
	}
	else
	{
		/* write hdr data */
		memcpy ( (void*)hCanvas->uiOSDHeaderPTR, (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );
		/* read data back for prevent data coherency problem */
		//memcpy ( (void*)&osd_hdr, (void*)hCanvas->uiOSDHeaderPTR, sizeof(FBDEV_L9_OSD_HDR_T) );
	}
#else
	/* TODO: write register */
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
	FBDEV_L9A0_WriteFRCHeader( );

//	up(&fbdev_sem_l9);

	return RET_OK;
}

/*========================================================================================
	Implementation Group (ISR)
========================================================================================*/
void FBDEV_L9A0_ISRTickHandler ( void )
{
	/* if new vsync arrived, swap osd idx */
	if ( g_fbdev_frc_ctrl.b_frc_sep_enable && g_frc_osd_emul.my_vsync >= 0 && g_frc_osd_emul.my_vsync != g_fbdev_vsync_cnt )
	{
//		PRINTK("OSD Vsync...[%d]\n", g_frc_osd_emul.osd_idx );
		g_frc_osd_emul.osd_idx ^= 1;
		g_frc_osd_emul.my_vsync = -1;
	}
}

/*========================================================================================
    Implementation Group (CAPS)
========================================================================================*/
BOOLEAN FBDEV_L9A0_CheckCaps ( FBDEV_L9_HW_CAPS_T caps, UINT32 args )
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
void FBDEV_L9A0_SetGPUClk ( FBDEV_L9_HW_GPU_CLK_T clk )
{
	printk("[fb] GPUCLK can't be changed\n");
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
int     FBDEV_L9A0_SetConnCtrl           (LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
	int ret = RET_OK;

	/* standard connection with LDVS */
	if ( pConnCtrl->conn_type == LX_FBDEV_CONN_STD_LVDS )
	{
		g_fbdev_frc_ctrl.b_frc_sep_enable 		= 0;

		/* disbale OSD2 since FRC header emulation is not necessary */
        if ( g_fbdev_frc_ctrl.b_frc_hdr_emul )
        {
            FBDEV_SetOSDEnable  ( FRC_HDR_EMUL_DEVID, FALSE );
        }

        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );     // <-- OSD2 is used as FRC3 emulation
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[3]->pixel );

        /* TODO: add more code */
    }
    /* standard connection with FRCIII */
    else if ( pConnCtrl->conn_type == LX_FBDEV_CONN_STD_FRCIII_BLEND )
    {
        g_fbdev_frc_ctrl.b_frc_sep_enable = 0;

		/* disbale OSD2 since FRC header emulation is not necessary */
        if ( g_fbdev_frc_ctrl.b_frc_hdr_emul )
        {
            FBDEV_SetOSDEnable  ( FRC_HDR_EMUL_DEVID, FALSE );
        }
		/* rewrite OSD header to update current change */
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
        FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );     // <-- OSD2 is used as FRC3 emulation
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

		OSD_L9A0_Wr01(osd0_3d_path_mode, osd0_path_sel,	0x0	); /* LR */
		OSD_L9A0_Wr01(osd1_3d_path_mode, osd1_path_sel,	0x0	); /* LR */
		OSD_L9A0_Wr01(osd2_3d_path_mode, osd2_path_sel,	0x0	); /* LR */
		OSD_L9A0_Wr01(crsr_3d_path_mode, crsr_path_sel,	0x0	); /* LR */

		OSD_L9A0_WrFL( osd0_3d_path_mode );
		OSD_L9A0_WrFL( osd1_3d_path_mode );
		OSD_L9A0_WrFL( osd2_3d_path_mode );
		OSD_L9A0_WrFL( crsr_3d_path_mode );

        /* TODO: add more code */
    }
    /* standard connection with FRCIII (OSD/VIDEO separated mode) */
    else if ( pConnCtrl->conn_type == LX_FBDEV_CONN_STD_FRCIII_SEPARATE )
    {
        if ( g_fbdev_frc_ctrl.b_frc_sep_enable )    { /* ignore multiple requetst */ goto func_exit; }

        g_fbdev_l9_reg->osd0_cfg.osd0_en = TRUE;    /* on  PoSD0 for merging */
        g_fbdev_l9_reg->osd1_cfg.osd1_en = FALSE;   /* off POSD1 for merging */
        g_fbdev_l9_reg->osd2_cfg.osd2_en = FALSE;   /* off POSD2 for merging */
        g_fbdev_l9_reg->crsr_cfg.crsr_en = FALSE;   /* off POSD3 for merging */

        g_fbdev_frc_ctrl.b_frc_sep_enable = 1;
        g_frc_hdr_emul.b_hdr_ready = FALSE;         /* I want to make header again */

        if ( g_fbdev_frc_ctrl.b_frc_hdr_emul )
        {
            /* if FRCIII emulation mode enabled, I should write 24byte FRC header
             * So, it is necessary to create pointer to access the start address of FRC header.
             */
            g_frc_hdr_emul.hdr_phys_addr = (UINT32)gMemCfgFBDev[FRC_HDR_EMUL_DEVID].mem_frame_base;
            g_frc_hdr_emul.hdr_virt_addr = (UINT32)ioremap(g_frc_hdr_emul.hdr_phys_addr,
                                                                FRC_HDR_EMUL_XRES * sizeof(UINT32) );

			/* TODO: below codes are made for test purpose. make the release version */
			{
				UINT32 val;
				// 1. OSD path
#ifdef	FRCIII_TEST_ON_URSA
				val = 0x00;
#else
				val = 0x02;
#endif
				memcpy((void *)&g_fbdev_l9_reg->osd0_3d_path_mode , (void *)&val , 4);
				memcpy((void *)&g_fbdev_l9_reg->osd1_3d_path_mode , (void *)&val , 4);
				memcpy((void *)&g_fbdev_l9_reg->osd2_3d_path_mode , (void *)&val , 4);
				memcpy((void *)&g_fbdev_l9_reg->crsr_3d_path_mode , (void *)&val , 4);

				// 2. OSD display size
				val = 0x07800439;
				memcpy((void *)&g_fbdev_l9_reg->osd_disp_size , (void *)&val , 4);

				// 3. OSD scaler buffer mode enable
				val = 0x80001163;
				memcpy((void *)&g_fbdev_l9_reg->osd0_sc_cfg , (void *)&val , 4);

				// 4. OSD Layer mux
				val = 0x2220; 	// 0x2210 raxis.lim (2011/09/02) -- ready for POSD0 merge 
				memcpy((void *)&g_fbdev_l9_reg->osd_layer_mux_right , (void *)&val , 4);

				// 5. OSD pixel alpha
				val = 0x21;
				memcpy((void *)&g_fbdev_l9_reg->osd_frc_if_cfg , (void *)&val , 4);
			}

            /* write test pattern to debug */
            {
                int     i;
                UINT32* hdr_ptr = (UINT32*)g_frc_hdr_emul.hdr_virt_addr;

                hdr_ptr += 6;                                       /* skip header */
                for ( i=0; i<32; i++ )   *hdr_ptr++ = 0xffff0000;    /* RED */
                for ( i=0; i<32; i++ )   *hdr_ptr++ = 0xff00ff00;    /* BLUE */
                for ( i=0; i<32; i++ )   *hdr_ptr++ = 0xff0000ff;    /* GREEN */
                for ( i=0; i<32; i++ )   *hdr_ptr++ = 0xff000000;    /* BLACK */
                for ( i=0; i<32; i++ )   *hdr_ptr++ = 0xffffffff;    /* WHITE */
            }

            /* enable OSD2 to emulate FRC header */
            FBDEV_SetOSDEnable  ( FRC_HDR_EMUL_DEVID, TRUE );
        }

		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[0]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[1]->pixel );
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[2]->pixel );     // <-- OSD2 is used as FRC3 emulation
		FBDEV_WriteOSDHeader( &g_dm_ctx->winfo[3]->pixel );
    }
    else
    {
		g_fbdev_frc_ctrl.b_frc_sep_enable = 0;
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
static void FBDEV_L9A0_WriteFRCHeader( void )
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

			printk("^c^[fb] FRC HDR[0 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[0] );	// should be 0x00a00004
			printk("^c^[fb] FRC HDR[1 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[1] );	// should be 0x00780138
			printk("^c^[fb] FRC HDR[2 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[2] );	// should be 0x000024ff
			printk("^c^[fb] FRC HDR[3 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[3] );	// should be 0x0
			printk("^c^[fb] FRC HDR[4 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[4] );	// should be 0x0
			printk("^c^[fb] FRC HDR[5 ] = %08x\n", g_frc_hdr_emul.frc_hdr_remap[5] );	// should be 0x00780138

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

			/* write header to emulation memory area */
			{
				UINT32 hdr_virt_addr = g_frc_hdr_emul.hdr_virt_addr;

				__raw_writel( g_frc_hdr_emul.frc_hdr_remap[0], hdr_virt_addr + 0x00 );
				__raw_writel( g_frc_hdr_emul.frc_hdr_remap[1], hdr_virt_addr + 0x04 );
				__raw_writel( g_frc_hdr_emul.frc_hdr_remap[2], hdr_virt_addr + 0x08 );
				__raw_writel( g_frc_hdr_emul.frc_hdr_remap[3], hdr_virt_addr + 0x0c );
				__raw_writel( g_frc_hdr_emul.frc_hdr_remap[4], hdr_virt_addr + 0x10 );
				__raw_writel( g_frc_hdr_emul.frc_hdr_remap[5], hdr_virt_addr + 0x14 );
			}
		}
	}
}

#include "gfx_draw.h"

/**
 *
 *
 *
 *
 *	@note 128x128 cursor is resized to 88x88 to simulate the cursor size in 1920x1080 dimension
 *	@note cursor hot spot is reimplemented
 */
static void FBDEV_L9A0_MergePOSD ( int layer, BOOLEAN b_flip )
{
	struct scanvas *posd0_canvas, *posd1_canvas, *posd3_canvas;

	FBDEV_L9_OSD_HDR_T	osd_hdr;
	UINT32			osd_addr;

	int				posd0_surf = -1;
	int				posd1_surf = -1; 
	int				posd3_surf = -1;
	int				merge_surf = -1;

	static int		crsr_surf = -1;
 	static int		merge_surf_list[2] = {-1,-1};

	/* POSD merge is only valid for FRC3 SEP mode. */
	if( g_fbdev_frc_ctrl.b_frc_sep_enable == 0 ) return;

	/* disable multiple enterance !! */
	OS_LockMutex( &g_frc_osd_emul_mtx );

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

		if ( !g_frc_osd_emul.osd_addr[0] )
		{
			int surf = GFX_AllocARGBSurface( 1280, 720, 0x0 );
			FBDEV_CHECK_CODE( surf<0, goto func_exit, "can't create merge surface\n");

			GFX_GetSurfaceInfo ( surf, &surface_info );
			g_frc_osd_emul.osd_addr[0] = (UINT32)surface_info.phys_addr;
		}
		
		if ( !g_frc_osd_emul.osd_addr[1] )
		{
			int surf = GFX_AllocARGBSurface( 1280, 720, 0x0 );
			FBDEV_CHECK_CODE( surf<0, goto func_exit, "can't create merge surface\n");

			GFX_GetSurfaceInfo ( surf, &surface_info );
			g_frc_osd_emul.osd_addr[1] = (UINT32)surface_info.phys_addr;
		}
	}

	posd0_canvas = &g_dm_ctx->winfo[0]->pixel;	/* POSD0 */
	posd1_canvas = &g_dm_ctx->winfo[1]->pixel;	/* POSD1 */
	posd3_canvas = &g_dm_ctx->winfo[3]->pixel;	/* POSD3 (CRSR) */

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
	if ( layer == 0 || layer == 1 )
	{
		g_frc_osd_emul.my_vsync = -1;
	}

	/* get the saved OSD0 header */
	memcpy( (void*)&osd_hdr, (void*)&g_frc_osd_emul.osd_hdr_sav[0], sizeof(FBDEV_L9_OSD_HDR_T) ); 

	if ( crsr_surf < 0 )			crsr_surf			= GFX_AllocARGBSurface(  88,   88, g_frc_osd_emul.crsr_addr );	 /* 88x88 */
	if ( merge_surf_list[0] < 0 )	merge_surf_list[0]	= GFX_AllocARGBSurface( 1280, 720, g_frc_osd_emul.osd_addr[0] );
	if ( merge_surf_list[1] < 0 )	merge_surf_list[1]	= GFX_AllocARGBSurface( 1280, 720, g_frc_osd_emul.osd_addr[1] );

	posd0_surf	= GFX_AllocARGBSurfaceEx( 1280, 720, posd0_canvas->uiBitmapDataYPTR, posd0_canvas->stride );
	posd1_surf	= GFX_AllocARGBSurfaceEx( 1280, 720, posd1_canvas->uiBitmapDataYPTR, posd1_canvas->stride  );
	posd3_surf	= GFX_AllocARGBSurfaceEx(  128, 128, posd3_canvas->uiBitmapDataYPTR, posd3_canvas->stride  );

	GFX_LockDevice();

	/* get active OSD frame buffer and destination OSD surface */
	osd_addr 	= g_frc_osd_emul.osd_addr[ g_frc_osd_emul.osd_idx ];
	merge_surf	= merge_surf_list[ g_frc_osd_emul.osd_idx ];
	
	PRINTK("[fb] %d-%d-%d %08x:%08x:%08x Idx %d flip %d layer %d\n", 
												g_frc_osd_emul.osd_view_status[0], g_frc_osd_emul.osd_view_status[1], g_frc_osd_emul.osd_view_status[3], 
												posd0_canvas->uiBitmapDataYPTR,
												posd1_canvas->uiBitmapDataYPTR,
												posd3_canvas->uiBitmapDataYPTR,
												g_frc_osd_emul.osd_idx, b_flip, layer );

	if ( g_frc_osd_emul.osd_view_status[0] && g_frc_osd_emul.osd_view_status[1] )
	{
		GFX_BlitSurface( posd0_surf, posd1_surf, merge_surf, 0, 0, 1280, 720, 0, 0, TRUE );
	}
	else if ( g_frc_osd_emul.osd_view_status[0] )
	{
		GFX_BlitSurface( posd0_surf, -1, merge_surf, 0, 0, 1280, 720, 0, 0, FALSE );
	}
	else if ( g_frc_osd_emul.osd_view_status[1] )
	{
		GFX_BlitSurface( posd1_surf, -1, merge_surf, 0, 0, 1280, 720, 0, 0, FALSE );
	}
	else
	{
		GFX_ClearSurface( merge_surf, 1280, 720 );
	}

	/* mrege cursor. test */
	if ( g_frc_osd_emul.osd_view_status[3] )
	{
		int	csr_x_pos, csr_y_pos;
		int	cx, cy, cw, ch, dx, dy;

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

			PRINTK("^c^[csr] %4d,%4d (%3d,%3d %3d,%3d):: %d.%d.%d.%d -> %d.%d.%d.%d\n", 
								csr_x_pos, csr_y_pos, 
								posd3_canvas->csr_hotspot.x, posd3_canvas->csr_hotspot.y, posd3_canvas->csr_size.w, posd3_canvas->csr_size.h,
								cx, cy, cw, ch, dx, dy, cw, ch );

			/* shrink cursor to simulate 1920x1080 cursor size */
			GFX_StretchSurface( posd3_surf, crsr_surf, 0, 0, 128, 128, 0, 0, 88, 88 );	
			/* merge cursor to the dstination buffer */
			GFX_BlitSurface( crsr_surf, merge_surf, merge_surf, cx, cy, cw, ch, dx, dy, TRUE );
		}
	}

	GFX_UnlockDevice();

	/* write the merge result to OSD header.
	 * cursor should be shrinked
	 */
	{
        struct scanvas* posd3_canvas = &g_dm_ctx->winfo[0]->pixel;

		osd_hdr.osd_hdr_ptr_bmp = (UINT32)osd_addr;
		memcpy ( (void*)posd3_canvas->uiOSDHeaderPTR, (void*)&osd_hdr, sizeof(FBDEV_L9_OSD_HDR_T) );
	}

	/* swap osd_idx */
	if ( b_flip ) //&& ( layer == 0 || layer == 1 ) )
	{
		g_frc_osd_emul.my_vsync = g_fbdev_vsync_cnt;
	}
	
func_exit:
	if (posd0_surf>=0) GFX_FreeSurface ( posd0_surf );
	if (posd1_surf>=0) GFX_FreeSurface ( posd1_surf );
	if (posd3_surf>=0) GFX_FreeSurface ( posd3_surf );

	OS_UnlockMutex( &g_frc_osd_emul_mtx );
}

/*========================================================================================
    chip revision handler
========================================================================================*/
FBDEV_L9_HW_FUNC_T	g_fbdev_l9a0_hw_func = 
{
	.L9_InitHWCtx			= FBDEV_L9A0_InitHWCtx,
    .L9_SetConnCtrl		= FBDEV_L9A0_SetConnCtrl,
	.L9_WriteOSDHeader	= FBDEV_L9A0_WriteOSDHeader,
	.L9_SetOSDEnable	= FBDEV_L9A0_SetOSDEnable,
	.L9_GetOSDEnable	= FBDEV_L9A0_GetOSDEnable,
	.L9_ISRTickHandler	= FBDEV_L9A0_ISRTickHandler,
	.L9_SetTridCtrl		= NULL,
	.L9_CheckCaps		= FBDEV_L9A0_CheckCaps,
    .L9_SetGPUClk       = FBDEV_L9A0_SetGPUClk,
};

