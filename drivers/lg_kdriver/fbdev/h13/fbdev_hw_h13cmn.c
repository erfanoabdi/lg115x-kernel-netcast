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
 *  @date		2011-04-03
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define	UPDATE_VOSD_IDX_INSIDE_ISR	/* update virtual osd index inside isr handler.
									 * sometimes, it's better to update osd index for every frame update 
									 * so, more test & analysis needed.
									 * the best method is to use tripple buffer
									 */

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_drv.h"
#include "fbdev_hw.h"
#include "fbdev_hal.h"
#include "fbdev_hw_h13.h"
#include "fbdev_reg_h13.h"
#include "mif_osd_reg_h13.h"

#include "gfx_draw.h"

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
extern  volatile OSD_H13_REG_T*     g_fbdev_h13_reg;
extern  OSD_H13_REG_T*              g_fbdev_h13_reg_cached;
extern  volatile MIF_OSD_H13_REG_T* g_mif_osd_h13_reg;
extern  MIF_OSD_H13_REG_T*          g_mif_osd_h13_reg_cached;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void		FBDEV_H13CMN_InitVOSD		( int fb_dev_id, UINT32 opmask );
static void		FBDEV_H13CMN_ExitVOSD		( int fb_dev_id );

static UINT32	FBDEV_H13CMN_RemapFRCHeader ( UINT32 in );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_osd_hdr_spinlock);

static int 	_g_fbdev_h13_v_phase_offset		= 0x27;	/* determined by test. used when reverse mode enabled */
module_param_named( fbdev_h13_v_phase_offset, _g_fbdev_h13_v_phase_offset, int, 0644 );

static int 	_g_fbdev_h13_mrb_bank_mode		= 0x0;	/* H13 H/W default. TODO: read the default value from H/W */
static int 	_g_fbdev_h13_mrb_bank_mode_req	= 0x0;
module_param_named( fbdev_h13_mrb_bank_mode, _g_fbdev_h13_mrb_bank_mode_req, int, 0644 );

/*========================================================================================
    Implementation Group (OSD Hdr Processing)
========================================================================================*/
/** write real header data to register
 *
 *
 *
 */
void	FBDEV_H13CMN_WriteHdrRegs	( int fb_dev_id, FBDEV_H13_OSD_HDR_T* osd_hdr )
{
	struct scanvas* hCanvas = FBDEV_GetWinCanvas( fb_dev_id );

	FBDEV_CHECK_CODE(NULL==hCanvas, return, "[fb] invalid layer %d\n", fb_dev_id );

	if ( g_reg_io_ctx->hdr_op_method == FBDEV_HDR_OP_MMIO )
	{
		ULONG   flags;

		spin_lock_irqsave(&g_osd_hdr_spinlock, flags);
		memcpy( (void*)hCanvas->uiOSDHeaderPTR, (void*)osd_hdr, sizeof(FBDEV_H13_OSD_HDR_T) );
		spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);
	}
	else
	{
		UINT32 * p_osd_hdr_data = (UINT32 *)osd_hdr;

		switch( fb_dev_id )
		{
			case 0:
				FBDEV_REG_MEMCPY( &g_fbdev_h13_reg->osd0_ctrl_hdr0, p_osd_hdr_data, 7);
#ifdef FBDEV_USE_HDR_RDY_REG
				g_fbdev_h13_reg->osd0_ctrl_main.osd0_hdr_ready_flag = 0x1;
#endif
			break;
			case 1:
				FBDEV_REG_MEMCPY( &g_fbdev_h13_reg->osd1_ctrl_hdr0, p_osd_hdr_data, 7);
#ifdef FBDEV_USE_HDR_RDY_REG
				g_fbdev_h13_reg->osd1_ctrl_main.osd1_hdr_ready_flag = 0x1;
#endif
			break;
			case 2:
				FBDEV_REG_MEMCPY( &g_fbdev_h13_reg->osd2_ctrl_hdr0, p_osd_hdr_data, 7);
#ifdef FBDEV_USE_HDR_RDY_REG
				g_fbdev_h13_reg->osd2_ctrl_main.osd2_hdr_ready_flag = 0x1;
#endif
			break;
			case 3:
				FBDEV_REG_MEMCPY( &g_fbdev_h13_reg->osd3_ctrl_hdr0, p_osd_hdr_data, 7);
#ifdef FBDEV_USE_HDR_RDY_REG
				g_fbdev_h13_reg->osd3_ctrl_main.osd3_hdr_ready_flag = 0x1;
#endif
			break;
		}
	}
}

/*========================================================================================
    Implementation Group (FRC)
========================================================================================*/
void FBDEV_H13CMN_WriteFRCHeader( void )
{
	/* raxis.lim (2012/06/06) -- Not Ready. check if FRC header should be generated or not !!! */
	return;

//	if ( g_fbdev_frc_ctrl.b_frc_sep_enable )

	/* make the initial FRC header. this is processed only once at the first call */
	if ( g_fbdev_h13_hw_ctx.frc_if_ctrl.b_hdr_ready == FALSE )
	{
		UINT32				val;
	    FBDEV_H13_FRC_HDR_0  osd_frc_hdr_0;   // 0x1ba4 : ''
		FBDEV_H13_FRC_HDR_1  osd_frc_hdr_1;   // 0x1ba8 : ''
		FBDEV_H13_FRC_HDR_2  osd_frc_hdr_2;   // 0x1bac : ''
		FBDEV_H13_FRC_HDR_3  osd_frc_hdr_3;   // 0x1bb0 : ''
		FBDEV_H13_FRC_HDR_4  osd_frc_hdr_4;   // 0x1bb4 : ''
		FBDEV_H13_FRC_HDR_5  osd_frc_hdr_5;   // 0x1bb8 : ''

		/* enable the 2nd routine if you want to use the cleared memory before setting frc header */
		OSD_H13_RdFL(osd_common_sep_osd_hdr0); val = OSD_H13_Rd(osd_common_sep_osd_hdr0); memcpy( &osd_frc_hdr_0,	&val, sizeof(UINT32));
		OSD_H13_RdFL(osd_common_sep_osd_hdr1); val = OSD_H13_Rd(osd_common_sep_osd_hdr0); memcpy( &osd_frc_hdr_1,	&val, sizeof(UINT32));
		OSD_H13_RdFL(osd_common_sep_osd_hdr2); val = OSD_H13_Rd(osd_common_sep_osd_hdr0); memcpy( &osd_frc_hdr_2,	&val, sizeof(UINT32));
		OSD_H13_RdFL(osd_common_sep_osd_hdr3); val = OSD_H13_Rd(osd_common_sep_osd_hdr0); memcpy( &osd_frc_hdr_3,	&val, sizeof(UINT32));
		OSD_H13_RdFL(osd_common_sep_osd_hdr4); val = OSD_H13_Rd(osd_common_sep_osd_hdr0); memcpy( &osd_frc_hdr_4,	&val, sizeof(UINT32));
		OSD_H13_RdFL(osd_common_sep_osd_hdr5); val = OSD_H13_Rd(osd_common_sep_osd_hdr0); memcpy( &osd_frc_hdr_5,	&val, sizeof(UINT32));

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

#if 0//def	FBDEV_L9B1_VCOM_TEST_SUPPORT
		{
			struct scanvas* hCanvas = &g_dm_ctx->winfo[LX_FBDEV_ID_OSD1]->pixel;
			if ( hCanvas->bBackImageEnable )
			{
               	osd_frc_hdr_1.osd_frc_hdr_bmp_width = 1920;
			}
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
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data[0] = *((UINT32*)&osd_frc_hdr_0);
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data[1] = *((UINT32*)&osd_frc_hdr_1);
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data[2] = *((UINT32*)&osd_frc_hdr_2);
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data[3] = *((UINT32*)&osd_frc_hdr_3);
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data[4] = *((UINT32*)&osd_frc_hdr_4);
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data[5] = *((UINT32*)&osd_frc_hdr_5);

		/* save remapped header */
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[0] = FBDEV_H13CMN_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_0) );
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[1] = FBDEV_H13CMN_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_1) );
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[2] = FBDEV_H13CMN_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_2) );
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[3] = FBDEV_H13CMN_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_3) );
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[4] = FBDEV_H13CMN_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_4) );
		g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[5] = FBDEV_H13CMN_RemapFRCHeader( *((UINT32*)&osd_frc_hdr_5) );

		/* TODO: dump header if you need */

		/* remap(swap bit order) should be done before writing register */
		OSD_H13_Wr( osd_common_sep_osd_hdr0, g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[0] );
		OSD_H13_Wr( osd_common_sep_osd_hdr1, g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[1] );
		OSD_H13_Wr( osd_common_sep_osd_hdr2, g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[2] );
		OSD_H13_Wr( osd_common_sep_osd_hdr3, g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[3] );
		OSD_H13_Wr( osd_common_sep_osd_hdr4, g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[4] );
		OSD_H13_Wr( osd_common_sep_osd_hdr5, g_fbdev_h13_hw_ctx.frc_if_ctrl.hdr_data_remap[5] );

		OSD_H13_WrFL( osd_common_sep_osd_hdr0 );
		OSD_H13_WrFL( osd_common_sep_osd_hdr1 );
		OSD_H13_WrFL( osd_common_sep_osd_hdr2 );
		OSD_H13_WrFL( osd_common_sep_osd_hdr3 );
		OSD_H13_WrFL( osd_common_sep_osd_hdr4 );
		OSD_H13_WrFL( osd_common_sep_osd_hdr5 );

		g_fbdev_h13_hw_ctx.frc_if_ctrl.b_hdr_ready = TRUE;
	}
}

/** remapp FRC header data format
 *
 */
static UINT32	FBDEV_H13CMN_RemapFRCHeader ( UINT32 in )
{
	typedef struct
	{
		UINT32		blk00:8,
					__r00:2,
					blk10:6,
					blk11:2,
					__r01:2,
					blk20:4,
					blk21:4,
					__r02:2,
					__r03:2;
	}
	REMAP_BEFORE_T;

	typedef struct
	{
		UINT32		blk00:8,
					blk10:6,
					blk11:2,
					blk20:4,
					blk21:4,

					__r03:2,
					__r00:2,
					__r01:2,
					__r02:2;
	}
	REMAP_AFTER_T;

	UINT32	out;
	REMAP_BEFORE_T	remap0;
	REMAP_AFTER_T	remap1;

	memcpy(&remap0, &in, 4 );

	remap1.blk00 = remap0.blk00;
	remap1.blk10 = remap0.blk10;
	remap1.blk11 = remap0.blk11;
	remap1.blk20 = remap0.blk20;
	remap1.blk21 = remap0.blk21;
	remap1.__r00 = remap0.__r00;
	remap1.__r01 = remap0.__r01;
	remap1.__r02 = remap0.__r02;
	remap1.__r03 = remap0.__r03;

	memcpy(&out, &remap1, 4 );

	return out;
}

/*========================================================================================
    Implementation Group (3D)
========================================================================================*/
int FBDEV_H13CMN_SetTridCtrl( int fb_dev_id, LX_FBDEV_TRID_CTRL_T* ctrl )
{
	UINT32	disp_val_left	= 0x100;
	UINT32	disp_val_right	= 0x100;

	BOOLEAN	b_2d3d_en		= FALSE;
	BOOLEAN b_s3d_en		= FALSE;

	UINT32	def_s3d_fb_addr	= 0x0;

	/* check OSD context */
	FBDEV_WIN_CTX_T* winfo = FBDEV_GetWinCtx( fb_dev_id );
	FBDEV_CHECK_CODE( winfo == NULL, goto func_exit, "can't get winfo\n") ;

	/* raxis.lim (2012/07/12) -- setup disparity 
	 * maximum available disparity is between -0x40 and +0x40 in H13. 
	 * this is not H/W restriction, just optimal max value for all type of panel.
	 */
	if ( ctrl->mode != LX_FBDEV_TRID_MODE_2D )
	{
		if ( ctrl->disparity > 0x40 )	ctrl->disparity = 0x40;

		if ( ctrl->mode & LX_FBDEV_TRID_MODE_EXT_DOWN )
		{
			disp_val_left	= 0x100 + ctrl->disparity;	/* move L to right direction */
			disp_val_right	= 0x100 - ctrl->disparity;	/* move R to left  direction */
		}
		else
		{
			disp_val_left	= 0x100 - ctrl->disparity;	/* move L to left  direction */
			disp_val_right	= 0x100 + ctrl->disparity;	/* move R to right direction */
		}
	}

	b_2d3d_en = (ctrl->mode & LX_FBDEV_TRID_MODE_2D_3D) ? TRUE: FALSE;
	b_s3d_en  = ((ctrl->mode & LX_FBDEV_TRID_MODE_SS ) || ( ctrl->mode & LX_FBDEV_TRID_MODE_TB ))? TRUE: FALSE;
	def_s3d_fb_addr = (b_s3d_en)? winfo->pixel.uiBitmapDataYPTR : 0x0;

	FBDEV_PRINT("[fb] %s: 3D OPT %d-%d-0x%x\n", __F__, b_2d3d_en, b_s3d_en, def_s3d_fb_addr );

	switch( fb_dev_id )
	{
		case 0:
			OSD_H13_RdFL( osd0_ctrl_3d_disparity );
			OSD_H13_Wr02( osd0_ctrl_3d_disparity,   osd0_l_3d_disparity_value,  disp_val_left,
													osd0_r_3d_disparity_value,  disp_val_right );
			OSD_H13_WrFL( osd0_ctrl_3d_disparity );

			OSD_H13_RdFL( osd0_ctrl_scaler );
			OSD_H13_Wr01( osd0_ctrl_scaler, osd0_sc_vdouble, b_2d3d_en );
			OSD_H13_WrFL( osd0_ctrl_scaler );

			OSD_H13_RdFL( osd0_ctrl_main );
			OSD_H13_Wr01( osd0_ctrl_main, osd0_s3d_en, b_s3d_en );
			OSD_H13_WrFL( osd0_ctrl_main );

			MIF_OSD_H13_Wr01( mifo_saddr_osd_0_l, cmd_rd_saddr_osd_0_l, def_s3d_fb_addr );
			MIF_OSD_H13_Wr01( mifo_saddr_osd_0_r, cmd_rd_saddr_osd_0_r, def_s3d_fb_addr );
			MIF_OSD_H13_WrFL( mifo_saddr_osd_0_l );
			MIF_OSD_H13_WrFL( mifo_saddr_osd_0_r );
		break;

		case 1:
			OSD_H13_RdFL( osd1_ctrl_3d_disparity );
			OSD_H13_Wr02( osd1_ctrl_3d_disparity,	osd1_l_3d_disparity_value,  disp_val_left,
													osd1_r_3d_disparity_value,	disp_val_right );
			OSD_H13_WrFL( osd1_ctrl_3d_disparity );

			OSD_H13_RdFL( osd1_ctrl_scaler );
			OSD_H13_Wr01( osd1_ctrl_scaler, osd1_sc_vdouble, b_2d3d_en );
			OSD_H13_WrFL( osd1_ctrl_scaler );

			OSD_H13_RdFL( osd1_ctrl_main );
			OSD_H13_Wr01( osd1_ctrl_main, osd1_s3d_en, b_s3d_en );
			OSD_H13_WrFL( osd1_ctrl_main );

			MIF_OSD_H13_Wr01( mifo_saddr_osd_1_l, cmd_rd_saddr_osd_1_l, def_s3d_fb_addr );
			MIF_OSD_H13_Wr01( mifo_saddr_osd_1_r, cmd_rd_saddr_osd_1_r, def_s3d_fb_addr );
			MIF_OSD_H13_WrFL( mifo_saddr_osd_1_l );
			MIF_OSD_H13_WrFL( mifo_saddr_osd_1_r );
		break;

		case 2:
		case 3:
			OSD_H13_RdFL( osd3_ctrl_3d_disparity );
			OSD_H13_Wr02( osd3_ctrl_3d_disparity,	osd3_l_3d_disparity_value,  disp_val_left,
													osd3_r_3d_disparity_value,	disp_val_right );
			OSD_H13_WrFL( osd3_ctrl_3d_disparity );

			OSD_H13_RdFL( osd3_ctrl_scaler );
			OSD_H13_Wr01( osd3_ctrl_scaler, osd3_sc_vdouble, b_2d3d_en );
			OSD_H13_WrFL( osd3_ctrl_scaler );

			OSD_H13_RdFL( osd3_ctrl_main );
			OSD_H13_Wr01( osd3_ctrl_main, osd3_s3d_en, b_s3d_en );
			OSD_H13_WrFL( osd3_ctrl_main );

			MIF_OSD_H13_Wr01( mifo_saddr_osd_3_l, cmd_rd_saddr_osd_3_l, def_s3d_fb_addr );
			MIF_OSD_H13_Wr01( mifo_saddr_osd_3_r, cmd_rd_saddr_osd_3_r, def_s3d_fb_addr );
			MIF_OSD_H13_WrFL( mifo_saddr_osd_3_l );
			MIF_OSD_H13_WrFL( mifo_saddr_osd_3_r );
		break;
	}

	FBDEV_WriteOSDHeader( &winfo->pixel );

func_exit:
	return RET_OK;
}

/*========================================================================================
    Implementation Group (OSD ctrl)
========================================================================================*/
int		FBDEV_H13CMN_SetViewCtrl ( LX_FBDEV_VIEW_CTRL_T* ctrl )
{
    int i;
    ULONG flags;

	//printk("%s: 0x%x 0x%x 0x%x 0x%x\n", __F__, ctrl->view_status[0], ctrl->view_status[1],ctrl->view_status[2],ctrl->view_status[3] );

	spin_lock_irqsave(&g_osd_hdr_spinlock, flags);

    for (i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
        if ( ctrl->view_status[i] == FALSE || ctrl->view_status[i] == TRUE )
        {
            FBDEV_H13_SetOSDEnable( i, ctrl->view_status[i] );
        }
    }

	spin_unlock_irqrestore(&g_osd_hdr_spinlock, flags);

    return RET_OK;
}

/*========================================================================================
    Implementation Group (VOSD emulation)
========================================================================================*/
void	FBDEV_H13CMN_HandleCLUT ( int fb_dev_id, struct scanvas* hCanvas, FBDEV_H13_OSD_HDR_T* osd_hdr )
{
#ifdef FBDEV_SUPPORT_8BPP_EMUL
	FBDEV_H13_CLUT_VOSD_CTRL_T* vosd_ctrl = &g_fbdev_h13_hw_ctx.clut_vosd_ctrl[fb_dev_id];

	if ( hCanvas->bits_per_pixel == 8 )
	{
		LX_GFX_SURFACE_SETTING_T surf_info;

		GFX_LockDevice();

		/* create 8bpp clut surface if needed */
		if ( vosd_ctrl->osd_surf[0] < 0 )
		{
			vosd_ctrl->osd_surf[0] = GFX_AllocARGBSurface( FBDEV_H13_CLUT_VOSD_WIDTH, FBDEV_H13_CLUT_VOSD_HEIGHT, 0x0 );
			FBDEV_CHECK_CODE( vosd_ctrl->osd_surf[0] < 0, goto clut_proc_exit, "can't clut vosd\n");

			GFX_GetSurfaceInfo ( vosd_ctrl->osd_surf[0], &surf_info );
			vosd_ctrl->fb_mem_ptr[0] = (UINT32)surf_info.phys_addr;
		}
		if ( vosd_ctrl->osd_surf[1] < 0 )
		{
			vosd_ctrl->osd_surf[1] = GFX_AllocARGBSurface( FBDEV_H13_CLUT_VOSD_WIDTH, FBDEV_H13_CLUT_VOSD_HEIGHT, 0x0 );
			FBDEV_CHECK_CODE( vosd_ctrl->osd_surf[1] < 0, goto clut_proc_exit, "can't alloc VOSD surf\n");

			GFX_GetSurfaceInfo ( vosd_ctrl->osd_surf[1], &surf_info );
			vosd_ctrl->fb_mem_ptr[1] = (UINT32)surf_info.phys_addr;
		}

		/* convert clut to 32bpp surface */
		{
			int 	fb_width	= (hCanvas->stride << 3)/ hCanvas->bits_per_pixel;
			int		fb_height	= (hCanvas->input_win.h);
			int		vosd_idx	= vosd_ctrl->osd_idx;
			int		vosd_surf	= vosd_ctrl->osd_surf[ vosd_idx ];
			int		vosd_mem_ptr= vosd_ctrl->fb_mem_ptr[ vosd_idx ];
			int		posd_surf	= -1;

			/* raxis.lim (2012/12/11) -- OSD input window can't be larger than physical OSD width (?) */
			if ( hCanvas->input_win.w > fb_width  ) hCanvas->input_win.w = fb_width;
			if ( hCanvas->input_win.h > fb_height ) hCanvas->input_win.h = fb_height;

			posd_surf = GFX_Alloc8BppSurfaceEx( fb_width, fb_height, hCanvas->uiBitmapDataYPTR, hCanvas->stride );
			FBDEV_CHECK_CODE( posd_surf<0, goto clut_proc_exit, "can't create temp FB surf for CLUT\n");

			GFX_SetSurfacePalette( posd_surf, 256, hCanvas->palette );

			/* if real POSD is less than clut vosd region, just blit */
			if ( hCanvas->input_win.w <= FBDEV_H13_CLUT_VOSD_WIDTH && hCanvas->input_win.h <= FBDEV_H13_CLUT_VOSD_HEIGHT )
			{
				GFX_BlitSurface( posd_surf, -1, vosd_surf, 0, 0, hCanvas->input_win.w, hCanvas->input_win.h, 0, 0, FALSE );
			}
			/* if real POSD is larger than clut vosd region, scale down it */
			else
			{
				GFX_StretchSurface( posd_surf, vosd_surf, 0, 0, hCanvas->input_win.w, hCanvas->input_win.h, 0, 0, FBDEV_H13_CLUT_VOSD_WIDTH, FBDEV_H13_CLUT_VOSD_HEIGHT );

				/* scale input dimension */
				if ( hCanvas->input_win.w > FBDEV_H13_CLUT_VOSD_WIDTH )
				{
					hCanvas->input_win.x = (hCanvas->input_win.x*FBDEV_H13_CLUT_VOSD_WIDTH)/fb_width;
					hCanvas->input_win.w = (hCanvas->input_win.w*FBDEV_H13_CLUT_VOSD_WIDTH)/fb_width;
				}
				if ( hCanvas->input_win.h > FBDEV_H13_CLUT_VOSD_HEIGHT )
				{
					hCanvas->input_win.y = (hCanvas->input_win.y*FBDEV_H13_CLUT_VOSD_HEIGHT)/fb_height;
					hCanvas->input_win.h = (hCanvas->input_win.h*FBDEV_H13_CLUT_VOSD_HEIGHT)/fb_height;
				}
			}

			/* change canvas data to hold 32bpp clut vosd */
			hCanvas->stride				= FBDEV_H13_CLUT_VOSD_WIDTH * 4;
			hCanvas->uiBitmapDataYPTR 	= vosd_mem_ptr;
			hCanvas->bits_per_pixel		= 32;

			if ( posd_surf>=0 ) GFX_FreeSurface( posd_surf );

			/* request vsync monitor & swap osd index */
			vosd_ctrl->my_vsync = g_fbdev_vsync_cnt;
#ifndef UPDATE_VOSD_IDX_INSIDE_ISR
			vosd_ctrl->osd_idx ^= 1;
#endif
		}

clut_proc_exit:
		GFX_UnlockDevice();
	}
	else
	{
		if ( vosd_ctrl->osd_surf[0] >= 0 || vosd_ctrl->osd_surf[1] >= 0 )
		{
			GFX_LockDevice();
			if ( vosd_ctrl->osd_surf[0] >= 0 ) { GFX_FreeSurface( vosd_ctrl->osd_surf[0] ); vosd_ctrl->osd_surf[0] = -1; }
			if ( vosd_ctrl->osd_surf[1] >= 0 ) { GFX_FreeSurface( vosd_ctrl->osd_surf[1] ); vosd_ctrl->osd_surf[1] = -1; }
			GFX_UnlockDevice();

			vosd_ctrl->osd_idx  = 0;
			vosd_ctrl->my_vsync = -1;
		}
	}

#endif
}

/** initialize virtual OSD 
 *
 */
static void	FBDEV_H13CMN_InitVOSD	( int fb_dev_id, UINT32 opmask )
{
	FBDEV_H13_VOSD_CTRL_T* vosd_ctrl = &g_fbdev_h13_hw_ctx.vosd_ctrl[fb_dev_id];

	if ( opmask == FBDEV_H13_VOSD_OPMASK_NONE ) return;

	if ( vosd_ctrl->opmask == FBDEV_H13_VOSD_OPMASK_NONE ) 
	{
		LX_GFX_SURFACE_SETTING_T surf_info;
		int width  = g_fbdev_cfg->display_width;	/* maximum width	*/
		int height = g_fbdev_cfg->display_height;	/* maximum height	*/

		vosd_ctrl->osd_surf[0] = GFX_AllocARGBSurface( width, height, 0x0 );
		FBDEV_CHECK_CODE( vosd_ctrl->osd_surf[0] < 0, return, "can't alloc VOSD surf\n");
		vosd_ctrl->osd_surf[1] = GFX_AllocARGBSurface( width, height, 0x0 );
		FBDEV_CHECK_CODE( vosd_ctrl->osd_surf[1] < 0, return, "can't alloc VOSD surf\n");

		GFX_GetSurfaceInfo ( vosd_ctrl->osd_surf[0], &surf_info );
		vosd_ctrl->fb_mem_ptr[0] = (UINT32)surf_info.phys_addr;
		GFX_GetSurfaceInfo ( vosd_ctrl->osd_surf[1], &surf_info );
		vosd_ctrl->fb_mem_ptr[1] = (UINT32)surf_info.phys_addr;

		vosd_ctrl->osd_idx = 0x0;
		memset( &vosd_ctrl->src_rect, 0x0, sizeof(LX_RECT_T));
		memset( &vosd_ctrl->dst_rect, 0x0, sizeof(LX_RECT_T));
	}

	vosd_ctrl->opmask |= opmask;
}

/** shutdown virtual OSD
 *
 */
static void	FBDEV_H13CMN_ExitVOSD	( int fb_dev_id )
{
	FBDEV_H13_VOSD_CTRL_T* vosd_ctrl = &g_fbdev_h13_hw_ctx.vosd_ctrl[fb_dev_id];

	if ( vosd_ctrl->opmask == FBDEV_H13_VOSD_OPMASK_NONE ) return; /* ignore multiple shutdown */

	vosd_ctrl->opmask = FBDEV_H13_VOSD_OPMASK_NONE;

	if ( vosd_ctrl->osd_surf[0] >= 0 ) GFX_FreeSurface( vosd_ctrl->osd_surf[0] );
	if ( vosd_ctrl->osd_surf[1] >= 0 ) GFX_FreeSurface( vosd_ctrl->osd_surf[1] );
}

/** make virtual OSD screen
 *
 *	@param fb_dev_id [IN] OSD id
 *	@param hCanvas [IN] canvas handle
 *	@param osd_hdr [IN/OUT] OSD header 
 */
void	FBDEV_H13CMN_HandleVOSD ( int fb_dev_id, struct scanvas* hCanvas, FBDEV_H13_OSD_HDR_T* osd_hdr )
{
	UINT32	opmask = FBDEV_H13_VOSD_OPMASK_NONE;

	/* check if application want to scale down POSD or fade in/out */
	if ( hCanvas->output_win.w < hCanvas->input_win.w || hCanvas->output_win.h < hCanvas->input_win.h )
		opmask |= FBDEV_H13_VOSD_OPMASK_DOWN_SCALE;
	if ( hCanvas->usGlobalAlpha < 0xff )
		opmask |= FBDEV_H13_VOSD_OPMASK_GLOBAL_ALPHA;

	if ( opmask == FBDEV_H13_VOSD_OPMASK_NONE) 
	{
		FBDEV_H13CMN_ExitVOSD( fb_dev_id );
		return;
	}

	GFX_LockDevice();

	/* initialize VOSD struct based on opmask */
	FBDEV_H13CMN_InitVOSD( fb_dev_id, opmask );

	/* make virtual OSD screen */
	{
		UINT32	vosd_idx;
		UINT32	vosd_mem_ptr;
		int		vosd_surf = -1;
		int		posd_surf = -1;

		FBDEV_H13_VOSD_CTRL_T* vosd_ctrl = &g_fbdev_h13_hw_ctx.vosd_ctrl[fb_dev_id];

		int 		fb_width	= (hCanvas->stride << 3)/ hCanvas->bits_per_pixel;
		int			fb_height	= (hCanvas->input_win.h);
		LX_RECT_T	src_rect	= { 0, 0, hCanvas->input_win.w, hCanvas->input_win.h };
		LX_RECT_T	dst_rect	= { hCanvas->output_win.x, hCanvas->output_win.y, hCanvas->output_win.w, hCanvas->output_win.h };

		vosd_idx	= vosd_ctrl->osd_idx;
		vosd_surf	= vosd_ctrl->osd_surf[ vosd_idx ];
		vosd_mem_ptr= vosd_ctrl->fb_mem_ptr[ vosd_idx ];

		/* create current (input) POSD surface */
		posd_surf= GFX_AllocARGBSurface( fb_width, fb_height, osd_hdr->osd_hdr_ptr_bmp );
		FBDEV_CHECK_CODE( posd_surf<0, goto vosd_exit, "can't create temp FB surf\n");

		osd_hdr->osd_hdr_wpl = ( g_fbdev_cfg->display_width << 2 /* stride */ ) >> 3;

		switch( vosd_ctrl->opmask )
		{
			case FBDEV_H13_VOSD_OPMASK_GLOBAL_ALPHA:
			{
				GFX_FadeSurface( posd_surf, vosd_surf, dst_rect.w, dst_rect.h, hCanvas->usGlobalAlpha );

				osd_hdr->type.osd.osd_hdr_w_mem	= dst_rect.w;
				osd_hdr->type.osd.osd_hdr_h_mem	= dst_rect.h;
			}
			break;

			case FBDEV_H13_VOSD_OPMASK_DOWN_SCALE:
			{
#if 0
				/* accoding to down-scale test, ther seems 2 line screen garbage at the right side in vertical lines.
				 * below codes will be remove these garbage [TODO] check H13
				 */
				osd_hdr->type.osd.osd_hdr_w_mem  -= 2;   /* hidde right 2 lines in vertical */
				osd_hdr->type.osd.osd_hdr_w_out  -= 2;   /* hidde right 2 lines in vertical */
#endif
				GFX_StretchSurface( posd_surf, vosd_surf, 0, 0, src_rect.w, src_rect.h, 0, 0, dst_rect.w, dst_rect.h );

				osd_hdr->type.osd.osd_hdr_w_mem	= dst_rect.w;
				osd_hdr->type.osd.osd_hdr_h_mem	= dst_rect.h;
			}
			break;

			case FBDEV_H13_VOSD_OPMASK_DOWN_SCALE|FBDEV_H13_VOSD_OPMASK_GLOBAL_ALPHA:
			default:
			{
#if 0
				/* accoding to down-scale test, ther seems 2 line screen garbage at the right side in vertical lines.
				 * below codes will be remove these garbage [TODO] check H13
				 */
				osd_hdr->type.osd.osd_hdr_w_mem  -= 2;   /* hidde right 2 lines in vertical */
				osd_hdr->type.osd.osd_hdr_w_out  -= 2;   /* hidde right 2 lines in vertical */
#endif
				GFX_StretchSurface( posd_surf, vosd_surf, 0, 0, src_rect.w, src_rect.h, 0, 0, dst_rect.w, dst_rect.h );
				GFX_FadeSurface   ( vosd_surf, vosd_surf, dst_rect.w, dst_rect.h, hCanvas->usGlobalAlpha );

				osd_hdr->type.osd.osd_hdr_w_mem	= dst_rect.w;
				osd_hdr->type.osd.osd_hdr_h_mem	= dst_rect.h;
			}
			break;
		}

		if ( posd_surf>=0 ) GFX_FreeSurface( posd_surf );

		/* replace old bm to new bm */
		osd_hdr->osd_hdr_ptr_bmp = vosd_mem_ptr;

		/* request vsync monitor & swap osd index */
		vosd_ctrl->my_vsync = g_fbdev_vsync_cnt;
#ifndef UPDATE_VOSD_IDX_INSIDE_ISR
		vosd_ctrl->osd_idx ^= 1;
#endif

#if 0
printk("[fb] %s : POSD info = (0,0,%d,%d) @ %dx%d\n", __F__, src_rect.w, src_rect.h, fb_width, fb_height );
printk("[fb] %s : VOSD info = (%d,%d,%d,%d) \n", __F__, dst_rect.x, dst_rect.y, dst_rect.w, dst_rect.h );
printk("[fb] %s : HDR  info = %d,%d,%d,%d -> %d,%d,%d,%d\n", __F__, 0, 0, osd_hdr->type.osd.osd_hdr_w_mem, osd_hdr->type.osd.osd_hdr_h_mem,
		            osd_hdr->type.osd.osd_hdr_xpos, osd_hdr->type.osd.osd_hdr_ypos ,
           		 	osd_hdr->type.osd.osd_hdr_w_out, osd_hdr->type.osd.osd_hdr_h_out );
#endif
	}
vosd_exit:
	GFX_UnlockDevice();
}

/* update S3D register if trid control changed */
void	FBDEV_H13CMN_Handle3DOSD ( int fb_dev_id, struct scanvas* hCanvas, FBDEV_H13_OSD_HDR_T* osd_hdr )
{
	BOOLEAN	b_mif_addr_ready = FALSE;
	UINT32	l_bmp_addr		 = osd_hdr->osd_hdr_ptr_bmp;
	UINT32	r_bmp_addr		 = osd_hdr->osd_hdr_ptr_bmp;
	UINT32	bmp_len			 = 0x0;

	if ( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode & LX_FBDEV_TRID_MODE_SS )
	{
		b_mif_addr_ready 	= TRUE;

		/* raxis.lim (2012/12/07)
		 * H13 requires osd input height should be less than half of output height.
		 * for example, if output height is 1080, input height should be less than 540 ( half of 1080 ) !!!
		 * H/W makes full OSD screen using two half-height left & right screen. 
		 *
		 * So Application should knows this H/W restrtion.
		 */
		if ( osd_hdr->type.osd.osd_hdr_h_mem > osd_hdr->type.osd.osd_hdr_h_out/2 )	
		{
			osd_hdr->type.osd.osd_hdr_h_mem = osd_hdr->type.osd.osd_hdr_h_out/2;
		}

		/* raxis.lim (2012/12/18)
		 * calculate bmp_len to be used in mirror mode.
		 * bmp_len should indicate the real bye length of OSD screen. ( but the height should be less than 1/2 of output display height ) 
		 */
		bmp_len = hCanvas->stride * osd_hdr->type.osd.osd_hdr_h_mem;

		/* raxis.lim (2012/12/07)
		 * OSD H/W mixes left picture & right picture. 
	 	 * H13 OSD H/W requires half of width & double of height.
		 * for example, if you want to enable S3D with 1280x540 POSD, you should make OSD header with input_w 640, input_w 1080.
		 */
		osd_hdr->type.osd.osd_hdr_w_mem >>= 1;	/* h/2 */
		osd_hdr->type.osd.osd_hdr_h_mem <<= 1;	/* V*2 */ 	 

		r_bmp_addr			= (UINT32)osd_hdr->osd_hdr_ptr_bmp + ((osd_hdr->type.osd.osd_hdr_w_mem * hCanvas->bits_per_pixel)>>3);

		FBDEV_PRINT("S/S ON : mem_w %d, mem_h %d, fb(L) 0x%x, fb(R) 0x%x\n", osd_hdr->type.osd.osd_hdr_w_mem, osd_hdr->type.osd.osd_hdr_h_mem, l_bmp_addr, r_bmp_addr );
	}
	else if ( g_fbdev_hw_ctx.fb[fb_dev_id].trid_ctrl.mode & LX_FBDEV_TRID_MODE_TB )
	{
		b_mif_addr_ready 	= TRUE;
		r_bmp_addr			= (UINT32)osd_hdr->osd_hdr_ptr_bmp + (hCanvas->stride * (osd_hdr->type.osd.osd_hdr_h_mem>>1) );

		FBDEV_WARN("not tested\n");
	}
	else
	{
		/* do nothing */
		b_mif_addr_ready 	= FALSE;
	}

	if ( b_mif_addr_ready )
	{
		switch( fb_dev_id )
		{
			case 0:
				/* raxis.lim (2012/12/18) H13 workaround. 
			 	 * because MIF reads the invalid base address in reverse mode, we should adjust address for MIF to read the right data
				 * see internal docs for more information */
				if ( g_fbdev_h13_reg->osd0_ctrl_main.osd0_v_reverse_en )
				{
					l_bmp_addr -= bmp_len; r_bmp_addr -= bmp_len;				
				}	

				MIF_OSD_H13_Wr01( mifo_saddr_osd_0_l, cmd_rd_saddr_osd_0_l, l_bmp_addr );
				MIF_OSD_H13_Wr01( mifo_saddr_osd_0_r, cmd_rd_saddr_osd_0_r, r_bmp_addr );
				MIF_OSD_H13_WrFL( mifo_saddr_osd_0_l );
				MIF_OSD_H13_WrFL( mifo_saddr_osd_0_r );

				MIF_OSD_H13_RdFL( mifo_rd_ctrl );
				MIF_OSD_H13_Wr01( mifo_rd_ctrl, load_rd_cmd_saddr_v, 0x1 );
				MIF_OSD_H13_WrFL( mifo_rd_ctrl );
			break;

			case 1:
				/* raxis.lim (2012/12/18) H13 workaround. 
			 	 * because MIF reads the invalid base address in reverse mode, we should adjust address for MIF to read the right data
				 * see internal docs for more information */
				if ( g_fbdev_h13_reg->osd1_ctrl_main.osd1_v_reverse_en )
				{
					l_bmp_addr -= bmp_len; r_bmp_addr -= bmp_len;				
				}

				MIF_OSD_H13_Wr01( mifo_saddr_osd_1_l, cmd_rd_saddr_osd_1_l, l_bmp_addr );
				MIF_OSD_H13_Wr01( mifo_saddr_osd_1_r, cmd_rd_saddr_osd_1_r, r_bmp_addr );
				MIF_OSD_H13_WrFL( mifo_saddr_osd_1_l );
				MIF_OSD_H13_WrFL( mifo_saddr_osd_1_r );

				MIF_OSD_H13_RdFL( mifo_rd_ctrl );
				MIF_OSD_H13_Wr01( mifo_rd_ctrl, load_rd_cmd_saddr_v, 0x1 );
				MIF_OSD_H13_WrFL( mifo_rd_ctrl );
			break;


			case 3:
#if 1
				FBDEV_WARN("fb[%d] S3D feature not tested\n", fb_dev_id );
#else
				/* raxis.lim (2012/12/18) H13 workaround. 
			 	 * because MIF reads the invalid base address in reverse mode, we should adjust address for MIF to read the right data */
				if ( g_fbdev_h13_reg->osd3_ctrl_main.osd3_v_reverse_en )
				{
					l_bmp_addr -= bmp_len; r_bmp_addr -= bmp_len;				
				}

				MIF_OSD_H13_Wr01( mifo_saddr_osd_3_l, cmd_rd_saddr_osd_3_l, l_bmp_addr );
				MIF_OSD_H13_Wr01( mifo_saddr_osd_3_r, cmd_rd_saddr_osd_3_r, r_bmp_addr );
				MIF_OSD_H13_WrFL( mifo_saddr_osd_3_l );
				MIF_OSD_H13_WrFL( mifo_saddr_osd_3_r );

				MIF_OSD_H13_RdFL( mifo_rd_ctrl );
				MIF_OSD_H13_Wr01( mifo_rd_ctrl, load_rd_cmd_saddr_v, 0x1 );
				MIF_OSD_H13_WrFL( mifo_rd_ctrl );
#endif
			break;

			case 2:
			default:
				FBDEV_WARN("fb[%d] S3D feature not tested nor supported\n", fb_dev_id );
			break;
		}
	}
}

/** handle workaround about reverse screen 
 *
 *
 */
void	FBDEV_H13CMN_HandleReverseOSD ( int fb_dev_id, struct scanvas* hCanvas, FBDEV_H13_OSD_HDR_T* osd_hdr )
{
	UINT32	b_reverse_en;

	OSD_H13_RdFL( osd_mixer_ctrl_sync );
	OSD_H13_Rd01( osd_mixer_ctrl_sync, reg_sync_v_reverse, b_reverse_en );

	if ( b_reverse_en == FALSE ) { /* No reverse mode. return */ return; }
//	if ( osd_hdr->type.osd.osd_hdr_h_mem < osd_hdr->type.osd.osd_hdr_h_out ) { /* vertical upscale. return */ return; }
	if ( osd_hdr->type.osd.osd_hdr_h_mem >= osd_hdr->type.osd.osd_hdr_h_out ) { /* no vertical upscale. return */ return; }

	FBDEV_PRINT("[fb %d] tune vphase offset 0x%x for reverse mode\n", fb_dev_id, _g_fbdev_h13_v_phase_offset );

	switch ( fb_dev_id )
	{
		case 0:
			OSD_H13_RdFL( osd0_ctrl_scaler );
			OSD_H13_Wr01( osd0_ctrl_scaler, osd0_sc_v_phase_off, _g_fbdev_h13_v_phase_offset );	
			OSD_H13_WrFL( osd0_ctrl_scaler );
			break;
		case 1:
			OSD_H13_RdFL( osd1_ctrl_scaler );
			OSD_H13_Wr01( osd1_ctrl_scaler, osd1_sc_v_phase_off, _g_fbdev_h13_v_phase_offset );	
			OSD_H13_WrFL( osd1_ctrl_scaler );
			break;

		case 2:	/* not supported */ break;
		case 3: /* don't do workaround */ break;
	}
}

/** VOSD ISR handler 
 *
 *
 */
void     FBDEV_H13CMN_HandleISR ( void )
{
	int		i;
	UINT32	mif_mrb_bank_mode;

	/* wirte MIF::mrb_bank_mode */
	if ( _g_fbdev_h13_mrb_bank_mode != _g_fbdev_h13_mrb_bank_mode_req )
	{
		printk("[fb] mrb_bank_mode changed from 0x%x to 0x%x\n", _g_fbdev_h13_mrb_bank_mode, _g_fbdev_h13_mrb_bank_mode_req );
		_g_fbdev_h13_mrb_bank_mode = _g_fbdev_h13_mrb_bank_mode_req;

		MIF_OSD_H13_RdFL( mifo_rd_ctrl );
		MIF_OSD_H13_Wr01( mifo_rd_ctrl, mrb_bank_mode, _g_fbdev_h13_mrb_bank_mode );
		MIF_OSD_H13_WrFL( mifo_rd_ctrl );
	}

	for ( i=0; i<LX_FBDEV_ID_MAX; i++ )
	{
		FBDEV_H13_VOSD_CTRL_T* vosd_ctrl = &g_fbdev_h13_hw_ctx.vosd_ctrl[i];
		FBDEV_H13_CLUT_VOSD_CTRL_T* clut_vosd_ctrl = &g_fbdev_h13_hw_ctx.clut_vosd_ctrl[i];

		if ( vosd_ctrl->opmask && vosd_ctrl->my_vsync >= 0 && vosd_ctrl->my_vsync != g_fbdev_vsync_cnt )
		{
#ifdef UPDATE_VOSD_IDX_INSIDE_ISR
			vosd_ctrl->osd_idx ^= 1;	/* swap osd_idx */
#endif
			vosd_ctrl->my_vsync = -1;	/* disable vsync monitoring */
		}
		if ( clut_vosd_ctrl->my_vsync >= 0 && clut_vosd_ctrl->my_vsync != g_fbdev_vsync_cnt )
		{
#ifdef UPDATE_VOSD_IDX_INSIDE_ISR
			clut_vosd_ctrl->osd_idx ^= 1;	/* swap osd_idx */
#endif
			clut_vosd_ctrl->my_vsync = -1;	/* disable vsync monitoring */
		}
	}
}

