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
#define	FRCIII_TEST_ON_URSA

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_l9.h"
#include "fbdev_util_l9.h"
#include "fbdev_reg_l9a0.h"

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
extern void	FBDEV_L9_InitOSDZOrder	( void );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
extern volatile OSD_L9A0_REG_T*		g_fbdev_l9_reg;
extern OSD_L9A0_REG_T*				g_fbdev_l9_reg_cached;

//DECLARE_MUTEX(fbdev_sem_l9);

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static const int 		pixel_depth_2_bpp[PIX_DEPTH_MAX] = { 1, 2, 4, 8, 16, 24, 32  };

/*========================================================================================
	Implementation Group
========================================================================================*/
/** make OSD to be initial state
 *	make the basic configuration for each OSD layer.
 *
 *	@param layerId
 */
int FBDEV_L9_InitOSDLayer ( int layer )
{
	int rc;
	int	ret = RET_ERROR;

	/* please refer to OSD manual OSD?_CFG field */
	UINT32	osd_cfg;
	UINT32	osd_hdr_addr;

#ifdef FBDEV_USE_MMIO_REG
    /* raxis.lim (note) - 0x1b000000 means that basic configuration on color selection (a,r,g,b)
     *
     *  {osd0_en = 0, osd0_round = 0, osd0_pure_ck = 0, osd0_hdr_ptr_bmp_sel = 0, osd0_hdr_ptr_plte_sel = 0,
     *  osd0_hdr_color_key_sel = 0, osd0_hdr_wpl_sel = 0, osd0_hdr_global_alpha_sel = 0, osd0_hdr_format_sel = 0,
     *  osd0_hdr_depth_sel = 0, osd0_hdr_h_out_sel = 0, osd0_hdr_w_out_sel = 0, osd0_hdr_global_alpha_en_sel = 0,
     *  osd0_hdr_pixel_order_sel = 0, osd0_hdr_h_mem_sel = 0, osd0_hdr_w_mem_sel = 0, osd0_hdr_ypos_sel = 0, osd0_hdr_xpos_sel = 0,
     *  osd0_hdr_color_key_en_sel = 0, osd0_ch_blue = 3, osd0_ch_green = 2, osd0_ch_red = 1, osd0_ch_alpha = 0
     *
     *  [note] OSD will be hidden osdx_en bit cleared
     */
	osd_cfg = 0x1b000000;
#else
	/* raxis.lim (note) - all header data is read from register not memory
	 * 
	 * {osd0_en = 0, osd0_double_h = 0, osd0_double_w = 0, osd0_manual_address = 0, osd0_round = 0, osd0_pure_ck = 0, ptr_bmp_sel = 1,
	 * ptr_plte_sel = 1, color_key_sel = 1, wpl_sel = 1, global_alpha_sel = 1, format_sel = 1, depth_sel = 1, h_out_sel = 1, w_out_sel = 1,
	 * global_alpha_en_sel = 1, pixel_order_sel = 1, h_mem_sel = 1, w_mem_sel = 1, ypos_sel = 1, xpos_sel = 1, color_key_en_sel = 1, 
	 * osd0_ch_blue = 3, osd0_ch_green = 2, osd0_ch_red = 1, osd0_ch_alpha = 0}
	 */
	osd_cfg = 0x1bffff00;
#endif

    /* raxis.lim (2011/04/20) -- L9A0 bug fix
	 * dongho7.park (2011/06/14) -- same error at L9A1 metal rev
	 * raxis.lim (2011/08/28) -- fixed at L9B0. L9B0 doesn't need to set register  
	 */
    if ( (lx_chip_rev() >= LX_CHIP_REV(L9,A0)) && (lx_chip_rev() < LX_CHIP_REV(L9,B0)) )
    {
        osd_cfg |= 0x8;
    }

	/* set DDR address which contains OSD header information */
    if ( g_reg_io_ctx->slkrd_prefix_mask )
    {
        osd_hdr_addr = (( ((gMemCfgFBHdr[layer].mem_header_base))&0x0FFFFFFF)| g_reg_io_ctx->slkrd_prefix_mask );
    }
    else
    {
        osd_hdr_addr = (gMemCfgFBHdr[layer].mem_header_base);
    }

//	FBDEV_ERROR("layer %d, osd_cfg = 0x%x, osd_hdr_addr = 0x%x\n", layer, osd_cfg, osd_hdr_addr );

	rc = 0; //down_interruptible(&fbdev_sem_l9);
	FBDEV_CHECK_CODE( rc, goto func_exit, "can't lock\n" );

	switch( layer )
	{
		case LX_FBDEV_ID_OSD0:
			memcpy( (void *)&g_fbdev_l9_reg->osd0_cfg, &osd_cfg, sizeof(unsigned int) );
			g_fbdev_l9_reg->osd0_base_addr.osd0_base_addr = osd_hdr_addr;	/* set header data address */
		break;

		case LX_FBDEV_ID_OSD1:
			memcpy( (void *)&g_fbdev_l9_reg->osd1_cfg, &osd_cfg, sizeof(unsigned int) );
			g_fbdev_l9_reg->osd1_base_addr.osd1_base_addr = osd_hdr_addr;	/* set header data address */
		break;

		case LX_FBDEV_ID_OSD2:
			memcpy( (void *)&g_fbdev_l9_reg->osd2_cfg, &osd_cfg, sizeof(unsigned int) );
			g_fbdev_l9_reg->osd2_base_addr.osd2_base_addr = osd_hdr_addr;	/* set header data address */
		break;

		case LX_FBDEV_ID_CSR0:
			memcpy( (void *)&g_fbdev_l9_reg->crsr_cfg, &osd_cfg, sizeof(unsigned int) );
			g_fbdev_l9_reg->crsr_base_addr.crsr_base_addr = osd_hdr_addr;	/* set header data address */
		break;

		default:
			FBDEV_ERROR("invalid osd %d\n", layer ); goto func_exit;
		break;
	}

	ret = RET_OK;	/* all work done */
func_exit:
//	up(&fbdev_sem_l9);

	return RET_OK;
}

/** set endianess on each layer
 *
 * @param	ENDIAN_INFORM_T
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_WriteOSDEndian(int layer , ENDIAN_INFORM_T *endian)
{
	int ret = RET_OK;

	unsigned int temp;

	temp = (unsigned int)((endian->header << 8) | (endian->palette << 4) | (endian->image << 0) );

	switch(layer){
		case LX_FBDEV_ID_OSD0:
			memcpy( (void *)&g_fbdev_l9_reg->osd0_end_conv , (void *)&temp , sizeof(int) );
		break;

		case LX_FBDEV_ID_OSD1:
			memcpy( (void *)&g_fbdev_l9_reg->osd1_end_conv ,(void *) &temp , sizeof(int) );
		break;

		case LX_FBDEV_ID_OSD2:
			memcpy( (void *)&g_fbdev_l9_reg->osd2_end_conv , (void *)&temp , sizeof(int) );
		break;

		case LX_FBDEV_ID_CSR0:
			memcpy( (void *)&g_fbdev_l9_reg->crsr_end_conv , (void *) &temp , sizeof(int) );
		break;
		default:
			FBDEV_PRINT("WARNING : invalid int type %s %d\n" , __func__ , __LINE__);
			ret = RET_ERROR;
		break;
	}

	return ret;
}

/**
 *
 * set color space conversion on each layer
 *
 * @param	int layer , CSC_INFORM_T *csc
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_WriteOSDCSC(int layer , CSC_INFORM_T *csc)
{
	int ret = 0;

	switch(layer){
		case LX_FBDEV_ID_OSD0:
			g_fbdev_l9_reg->osd0_csc_ctrl.osd0_csc_data 	= csc->data;
			g_fbdev_l9_reg->osd0_csc_ctrl.osd0_csc_rw_n 	= csc->rw_n;
			g_fbdev_l9_reg->osd0_csc_ctrl.osd0_csc_bypass 	= csc->bypass;
			g_fbdev_l9_reg->osd0_csc_ctrl.osd0_csc_sel 		= csc->sel;
			g_fbdev_l9_reg->osd0_csc_ctrl.osd0_csc_out_ctrl = csc->out_ctrl;
			g_fbdev_l9_reg->osd0_csc_ctrl.osd0_csc_in_ctrl	= csc->in_ctrl;
		break;

		case LX_FBDEV_ID_OSD1:
			g_fbdev_l9_reg->osd1_csc_ctrl.osd1_csc_data		= csc->data;
			g_fbdev_l9_reg->osd1_csc_ctrl.osd1_csc_rw_n		= csc->rw_n;
			g_fbdev_l9_reg->osd1_csc_ctrl.osd1_csc_bypass	= csc->bypass;
			g_fbdev_l9_reg->osd1_csc_ctrl.osd1_csc_sel		= csc->sel;
			g_fbdev_l9_reg->osd1_csc_ctrl.osd1_csc_out_ctrl	= csc->out_ctrl;
			g_fbdev_l9_reg->osd1_csc_ctrl.osd1_csc_in_ctrl	= csc->in_ctrl;
		break;

		case LX_FBDEV_ID_OSD2:
			g_fbdev_l9_reg->osd2_csc_ctrl.osd2_csc_data		= csc->data;
			g_fbdev_l9_reg->osd2_csc_ctrl.osd2_csc_rw_n		= csc->rw_n;
			g_fbdev_l9_reg->osd2_csc_ctrl.osd2_csc_bypass	= csc->bypass;
			g_fbdev_l9_reg->osd2_csc_ctrl.osd2_csc_sel		= csc->sel;
			g_fbdev_l9_reg->osd2_csc_ctrl.osd2_csc_out_ctrl	= csc->out_ctrl;
			g_fbdev_l9_reg->osd2_csc_ctrl.osd2_csc_in_ctrl	= csc->in_ctrl;
		break;

		case LX_FBDEV_ID_CSR0:

		break;

		default:
			FBDEV_PRINT("WARNING : invalid int type %s %d\n" , __func__ , __LINE__);
			return -1;
		break;
	}

	return ret;
}

/** Get interrupt status
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
	UINT32	status = 0x0;

	OSD_L9A0_RdFL(osd_irq);

	switch(intr)
	{
    	case CRSR_INTR:		OSD_L9A0_Rd01( osd_irq, crsr_irq,	status ); break;
    	case OSD_0_INTR: 	OSD_L9A0_Rd01( osd_irq, osd0_irq,	status ); break;
    	case OSD_1_INTR: 	OSD_L9A0_Rd01( osd_irq, osd1_irq,	status ); break;
		case OSD_2_INTR:	OSD_L9A0_Rd01( osd_irq, osd2_irq,	status ); break;
		case MIXER_INTR:	OSD_L9A0_Rd01( osd_irq, mixer_irq,	status ); break;
		case ALL_INTR:
		default:			status = OSD_L9A0_Rd(osd_irq) & 0x1f;	break;
	}

	FBDEV_PRINT("intr(%d) status %x\n", intr, status );

	return status;
}

/** Clear interrupt status
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
	FBDEV_PRINT("clear interrupt %d\n", intr );

	OSD_L9A0_RdFL(osd_irq);

	/* set zero value not to clear other interrupt status */
	OSD_L9A0_Wr01( osd_irq, crsr_irq,	0 );
	OSD_L9A0_Wr01( osd_irq, osd0_irq,	0 );
	OSD_L9A0_Wr01( osd_irq, osd1_irq,	0 );
	OSD_L9A0_Wr01( osd_irq, osd2_irq,	0 );
	OSD_L9A0_Wr01( osd_irq, mixer_irq,	0 );

	switch(intr)
	{
    	case CRSR_INTR:		OSD_L9A0_Wr01( osd_irq, crsr_irq,	1 ); break;
    	case OSD_0_INTR: 	OSD_L9A0_Wr01( osd_irq, osd0_irq,	1 ); break;
    	case OSD_1_INTR: 	OSD_L9A0_Wr01( osd_irq, osd1_irq,	1 ); break;
		case OSD_2_INTR:	OSD_L9A0_Wr01( osd_irq, osd2_irq,	1 ); break;
		case MIXER_INTR:	OSD_L9A0_Wr01( osd_irq, mixer_irq,	1 ); break;
		case ALL_INTR:
		default:			OSD_L9A0_Wr01( osd_irq, crsr_irq,	1 );
    						OSD_L9A0_Wr01( osd_irq, osd0_irq,	1 );
    						OSD_L9A0_Wr01( osd_irq, osd1_irq,	1 );
							OSD_L9A0_Wr01( osd_irq, osd2_irq,	1 );
							OSD_L9A0_Wr01( osd_irq, mixer_irq,	1 ); break;
	}

	OSD_L9A0_WrFL( osd_irq );

	return RET_OK;
}

/** Set interrupt enable/disable
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T , int : enable/disable
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_SetInterruptEnable(INTERRUPT_INFORM_T intr , int enable)
{
//	FBDEV_ERROR("control interrupt %d - %d\n", intr, enable );

#if 0
    OSD_L9A0_RdFL(osd_irq);

    switch(intr)
    {
        case CRSR_INTR:     OSD_L9A0_Wr01( osd_irq, crsr_irq_en,   enable ); break;
        case OSD_0_INTR:    OSD_L9A0_Wr01( osd_irq, osd0_irq_en,   enable ); break;
        case OSD_1_INTR:    OSD_L9A0_Wr01( osd_irq, osd1_irq_en,   enable ); break;
        case OSD_2_INTR:    OSD_L9A0_Wr01( osd_irq, osd2_irq_en,   enable ); break;
        case MIXER_INTR: 	OSD_L9A0_Wr01( osd_irq, mixer_irq_en,  enable ); break;
        case ALL_INTR:
		default:			OSD_L9A0_Wr01( osd_irq, crsr_irq_en,   enable );
                            OSD_L9A0_Wr01( osd_irq, osd0_irq_en,   enable );
                            OSD_L9A0_Wr01( osd_irq, osd1_irq_en,   enable );
                            OSD_L9A0_Wr01( osd_irq, osd2_irq_en,   enable );
                            OSD_L9A0_Wr01( osd_irq, mixer_irq_en,  enable ); break;
    }

    OSD_L9A0_WrFL( osd_irq );
#else

    switch(intr)
    {
        case CRSR_INTR:     g_fbdev_l9_reg->osd_irq.crsr_irq_en = enable; break;
        case OSD_0_INTR:    g_fbdev_l9_reg->osd_irq.osd0_irq_en = enable; break;
        case OSD_1_INTR:    g_fbdev_l9_reg->osd_irq.osd1_irq_en = enable; break;
        case OSD_2_INTR:    g_fbdev_l9_reg->osd_irq.osd2_irq_en = enable; break;
        case MIXER_INTR:    g_fbdev_l9_reg->osd_irq.mixer_irq_en= enable; break;
        case ALL_INTR:
		default:			g_fbdev_l9_reg->osd_irq.crsr_irq_en = enable;
							g_fbdev_l9_reg->osd_irq.osd0_irq_en = enable;
							g_fbdev_l9_reg->osd_irq.osd1_irq_en = enable;
							g_fbdev_l9_reg->osd_irq.osd2_irq_en = enable;
							g_fbdev_l9_reg->osd_irq.mixer_irq_en= enable; break;
    }
#endif

    return RET_OK;
}

/** Update OSD ZList
 *
 * @param zList [IN] pointer to POSD List config.
 * @return RET_OK if success, RET_ERROR otherwise
 *
 * @note layer id definition is 03: video, 00: OSD0, 01: OSD1, 02: OSD2 ( refer to OSD register manual )
 *
 * [NOTE] raxis.lim (2011/02/23)
 * POSD2 block is not supported any more since its circult is used to fix OSD H/W bug in SEP mode.
 * Furthermore, layer_mux should not replace POSD2 ( layer_mux.layer_mux3 ). it may be sideeffect by POSD2 metal revision.
 * PR Description ) if other POSD is set to use layer_mux_3, that POSD will not be shown on the screen !!!
 *
 * So we should use only layer_mux_0, layer_mux_1, and layer_mux_2.
 * it's very critical to OSD H/W and DO NOT forget this H/W restriction.
 *
 * there is another note for video_layer_alpha.
 * I will set zero value to video_layer_alpha even though that register field is active.
 * remember that video_layer_alpha affects the non-active area outside of VIDEO.
 * According to the analsysis of TV runtime scenarioes, I reach the conclustion that video_layer_alpha can be always zero.
 *
 * scene #1 ) video layer is located at the bottom and all OSD layer is located over the video.
 * analsys  ) video_layer_alpha cannot run since there is no OSD layer below video. any value doesn't affect the screen.				
 *
 * scene #2 ) video layer is located at the middle or topmost and OSD layer is located below the video.
 * analysis ) normal application will use this scenario to implement PIP ( small video region is showen over OSD )
 *			  in this scenario, video_layer_alpha should be zero to show OSD area outside the video.
 *
 *
 */
int FBDEV_L9_SetZList ( LX_FBDEV_ZLIST_T* zList )
{

	if ( zList->path & LX_FBDEV_PATH_LEFT )
	{
    	OSD_L9A0_RdFL(osd_layer_mux_left);
		OSD_L9A0_Wr05(osd_layer_mux_left,   layer_mux_3,        0x2,				/* POSD2 should be fixed to layer_mux_3 */
   	                                     	layer_mux_2,        zList->order[0],
   	                                     	layer_mux_1,        zList->order[1],
   	                                     	layer_mux_0,   		zList->order[2],
                                        	video_layer_alpha,  0x0 );				/* video alpha shoule always be 0x0 to change layer zorder */
    	OSD_L9A0_WrFL(osd_layer_mux_left);
	}

	if ( zList->path & LX_FBDEV_PATH_RIGHT )
	{
    	OSD_L9A0_RdFL(osd_layer_mux_right);
		OSD_L9A0_Wr05(osd_layer_mux_right,	layer_mux_3,		0x2,				/* POSD2 should be fixed to layer_mux_3 */
											layer_mux_2,        zList->order[0],
											layer_mux_1,        zList->order[1],
											layer_mux_0,        zList->order[2],
											video_layer_alpha,  0x0 );				/* video alpha shoule always be 0x0 to change layer zorder */
    	OSD_L9A0_WrFL(osd_layer_mux_right);
	}

	return RET_OK;
}

/** Get OSD ZList
 *
 * @note layer id definition is 00: video, 01: OSD0, 02: OSD1, 03: OSD2
 *
 *
 */
int FBDEV_L9_GetZList( LX_FBDEV_ZLIST_T* zList )
{
	if ( zList->path & LX_FBDEV_PATH_LEFT )	/* left path or all path */
	{ 
	    OSD_L9A0_RdFL(osd_layer_mux_left);

		zList->order[0] = g_fbdev_l9_reg_cached->osd_layer_mux_left.layer_mux_2;
		zList->order[1] = g_fbdev_l9_reg_cached->osd_layer_mux_left.layer_mux_1;
		zList->order[2] = g_fbdev_l9_reg_cached->osd_layer_mux_left.layer_mux_0;
	}
	else	/* right path */
	{ 
		OSD_L9A0_RdFL(osd_layer_mux_right);

		zList->order[0] = g_fbdev_l9_reg_cached->osd_layer_mux_right.layer_mux_2;
		zList->order[1] = g_fbdev_l9_reg_cached->osd_layer_mux_right.layer_mux_1;
		zList->order[2] = g_fbdev_l9_reg_cached->osd_layer_mux_right.layer_mux_0;
	}

	return RET_OK;
}

/** control video mixer region 
 *
 *	@note window_ctrl.window_alpha value is initialized as 0xff in OSD H/W.
 *		  actually, we don't need to set window_ctrl.window_alpha since it is always set to 0xff.
 *		  but I think that it is set to the right value explictely 
 */
int FBDEV_L9_SetVideoMixerCtrl   (LX_FBDEV_VIDEO_MIXER_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;
	int b_enable = (ctrl->b_enable)? 0x1: 0x0;

	printk("[debug] path = 0x%x\n", ctrl->path   );
	printk("[debug] mixid= 0x%x\n", ctrl->mix_id );

	if ( ctrl->path & LX_FBDEV_PATH_LEFT )
	{
		switch( ctrl->mix_id )
		{
			case 0:
			{
				OSD_L9A0_RdFL( osd_l_window0_ctrl0 );
				OSD_L9A0_RdFL( osd_l_window0_ctrl1 );
				OSD_L9A0_RdFL( osd_l_window0_ctrl2 );

				printk("[debug] ctrl->b_enable = %d\n", ctrl->b_enable );

				OSD_L9A0_Wr02( osd_l_window0_ctrl0, window0_en, b_enable,
													window0_alpha, 0xff );
				OSD_L9A0_Wr02( osd_l_window0_ctrl1, window0_x , ctrl->mix_win.x,
													window0_y , ctrl->mix_win.y );
				OSD_L9A0_Wr02( osd_l_window0_ctrl2, window0_w , ctrl->mix_win.w,
													window0_h , ctrl->mix_win.h );
				OSD_L9A0_WrFL( osd_l_window0_ctrl0 );
				OSD_L9A0_WrFL( osd_l_window0_ctrl1 );
				OSD_L9A0_WrFL( osd_l_window0_ctrl2 );
			}
			break;

			case 1:
			{
				OSD_L9A0_RdFL( osd_l_window1_ctrl0 );
				OSD_L9A0_RdFL( osd_l_window1_ctrl1 );
				OSD_L9A0_RdFL( osd_l_window1_ctrl2 );

				OSD_L9A0_Wr02( osd_l_window1_ctrl0, window1_en, b_enable,
													window1_alpha, 0xff );
				OSD_L9A0_Wr02( osd_l_window1_ctrl1, window1_x , ctrl->mix_win.x,
													window1_y , ctrl->mix_win.y );
				OSD_L9A0_Wr02( osd_l_window1_ctrl2, window1_w , ctrl->mix_win.w,
													window1_h , ctrl->mix_win.h );
				OSD_L9A0_WrFL( osd_l_window1_ctrl0 );
				OSD_L9A0_WrFL( osd_l_window1_ctrl1 );
				OSD_L9A0_WrFL( osd_l_window1_ctrl2 );

			}
			break;

			case 2:
			{
				OSD_L9A0_RdFL( osd_l_window2_ctrl0 );
				OSD_L9A0_RdFL( osd_l_window2_ctrl1 );
				OSD_L9A0_RdFL( osd_l_window2_ctrl2 );

				OSD_L9A0_Wr02( osd_l_window2_ctrl0, window2_en, b_enable,
													window2_alpha, 0xff );
				OSD_L9A0_Wr02( osd_l_window2_ctrl1, window2_x , ctrl->mix_win.x,
													window2_y , ctrl->mix_win.y );
				OSD_L9A0_Wr02( osd_l_window2_ctrl2, window2_w , ctrl->mix_win.w,
													window2_h , ctrl->mix_win.h );
				OSD_L9A0_WrFL( osd_l_window2_ctrl0 );
				OSD_L9A0_WrFL( osd_l_window2_ctrl1 );
				OSD_L9A0_WrFL( osd_l_window2_ctrl2 );
			}
			break;

			default: FBDEV_ERROR("invalid mix id %d\n", ctrl->mix_id ); goto func_exit;
		}
	}

	if ( ctrl->path & LX_FBDEV_PATH_RIGHT )
	{
		switch( ctrl->mix_id )
		{
			case 0:
			{
				OSD_L9A0_RdFL( osd_r_window0_ctrl0 );
				OSD_L9A0_RdFL( osd_r_window0_ctrl1 );
				OSD_L9A0_RdFL( osd_r_window0_ctrl2 );

				OSD_L9A0_Wr02( osd_r_window0_ctrl0, window0_en, 	b_enable,
													window0_alpha,	0xff );
				OSD_L9A0_Wr02( osd_r_window0_ctrl1, window0_x , ctrl->mix_win.x,
													window0_y , ctrl->mix_win.y );
				OSD_L9A0_Wr02( osd_r_window0_ctrl2, window0_w , ctrl->mix_win.w,
													window0_h , ctrl->mix_win.h );
				OSD_L9A0_WrFL( osd_r_window0_ctrl0 );
				OSD_L9A0_WrFL( osd_r_window0_ctrl1 );
				OSD_L9A0_WrFL( osd_r_window0_ctrl2 );
			}
			break;

			case 1:
			{
				OSD_L9A0_RdFL( osd_r_window1_ctrl0 );
				OSD_L9A0_RdFL( osd_r_window1_ctrl1 );
				OSD_L9A0_RdFL( osd_r_window1_ctrl2 );

				OSD_L9A0_Wr02( osd_r_window1_ctrl0, window1_en, 	b_enable,
													window1_alpha,	0xff );
				OSD_L9A0_Wr02( osd_r_window1_ctrl1, window1_x , ctrl->mix_win.x,
													window1_y , ctrl->mix_win.y );
				OSD_L9A0_Wr02( osd_r_window1_ctrl2, window1_w , ctrl->mix_win.w,
													window1_h , ctrl->mix_win.h );
				OSD_L9A0_WrFL( osd_r_window1_ctrl0 );
				OSD_L9A0_WrFL( osd_r_window1_ctrl1 );
				OSD_L9A0_WrFL( osd_r_window1_ctrl2 );

			}
			break;

			case 2:
			{
				OSD_L9A0_RdFL( osd_r_window2_ctrl0 );
				OSD_L9A0_RdFL( osd_r_window2_ctrl1 );
				OSD_L9A0_RdFL( osd_r_window2_ctrl2 );

				OSD_L9A0_Wr02( osd_r_window2_ctrl0, window2_en, 	b_enable,
													window2_alpha,	0xff );
				OSD_L9A0_Wr02( osd_r_window2_ctrl1, window2_x , ctrl->mix_win.x,
													window2_y , ctrl->mix_win.y );
				OSD_L9A0_Wr02( osd_r_window2_ctrl2, window2_w , ctrl->mix_win.w,
													window2_h , ctrl->mix_win.h );
				OSD_L9A0_WrFL( osd_r_window2_ctrl0 );
				OSD_L9A0_WrFL( osd_r_window2_ctrl1 );
				OSD_L9A0_WrFL( osd_r_window2_ctrl2 );
			}
			break;

			default: FBDEV_ERROR("invalid mix id %d\n", ctrl->mix_id ); goto func_exit;
		}
	}

	ret = RET_OK; /* all work done */
func_exit:
	return ret;
}

/** update 3D OSD mode
 *
 *	@param layer [IN] layerId
 *	@param ctrl [IN] new 3D config
 *	@return RET_OK if success, RET_ERROR otherwise
 */
int FBDEV_L9_SetTridCtrl( int layer, LX_FBDEV_TRID_CTRL_T* ctrl )
{
	int	ret = RET_OK;

	/* check current chip & osd layer supports 3D OSD */
	if ( FALSE == g_fbdev_l9_hw_func.L9_CheckCaps(FBDEV_L9_HW_CAPS_TRID_CTRL, layer) )
	{
		return RET_OK;
	}

	switch( layer )
	{
		case LX_FBDEV_ID_OSD0:
		{
			OSD_L9A0_RdFL( osd0_3d_path_mode );
			OSD_L9A0_RdFL( osd0_3d_disparity );

			if ( g_fbdev_cfg->fb[0].b_use_trid_hw )
			{
				if ( ctrl->mode == LX_FBDEV_TRID_MODE_SS )
				{
					OSD_L9A0_Wr04(osd0_3d_path_mode,	osd0_path_buf_half,		0x1,
														osd0_path_buf_repeat,	0x1,
														osd0_3d_en,				0x1,
														osd0_3d_mode_sel,		0x0	);	/* S/S */

					OSD_L9A0_Wr04(osd0_3d_disparity,	osd0_right_disparity_value,	0,
														osd0_right_disparity_sign,	0,	/* 0: L->R, 1: R->L */
														osd0_left_disparity_value,	0,
														osd0_left_disparity_sign,	1 );/* 0: L->R, 1: R->L */
				}
				else if ( ctrl->mode == LX_FBDEV_TRID_MODE_TB )
				{
					OSD_L9A0_Wr04(osd0_3d_path_mode,	osd0_path_buf_half,		0x0,
														osd0_path_buf_repeat,	0x0,
														osd0_3d_en,				0x1,
														osd0_3d_mode_sel,		0x1	);	/* T/B */

					OSD_L9A0_Wr04(osd0_3d_disparity,	osd0_right_disparity_value,	0,
														osd0_right_disparity_sign,	0,	/* 0: L->R, 1: R->L */
														osd0_left_disparity_value,	0,
														osd0_left_disparity_sign,	1 );/* 0: L->R, 1: R->L */
				}
				else /* 2D or NONE */
				{
					OSD_L9A0_Wr( osd0_3d_path_mode,		0x00000000 );	/* all clear */
					OSD_L9A0_Wr( osd0_3d_disparity,		0x00000000 );	/* all clear */
				}
			}

			OSD_L9A0_Wr( osd0_left_3d_blank, 	0xff000000 );		/* black ? */
			OSD_L9A0_Wr( osd0_right_3d_blank, 	0xff000000 );		/* black ? */
			OSD_L9A0_Wr( osd0_tb_space,			0x00000000 );

			/* chip revision handler can ovrride the default 3DOSD config */
			if ( g_fbdev_l9_hw_func.L9_SetTridCtrl )
			{
				ret = g_fbdev_l9_hw_func.L9_SetTridCtrl( layer, ctrl );
			}

			OSD_L9A0_WrFL( osd0_3d_path_mode );
			OSD_L9A0_WrFL( osd0_3d_disparity );
			OSD_L9A0_WrFL( osd0_left_3d_blank );
			OSD_L9A0_WrFL( osd0_left_3d_blank );
			OSD_L9A0_WrFL( osd0_tb_space );
		}
		break;

		case LX_FBDEV_ID_OSD1:
		{
			OSD_L9A0_RdFL( osd1_3d_path_mode );
			OSD_L9A0_RdFL( osd1_3d_disparity );

			if ( g_fbdev_cfg->fb[1].b_use_trid_hw )
			{
				if ( ctrl->mode == LX_FBDEV_TRID_MODE_SS )
				{
					OSD_L9A0_Wr04(osd1_3d_path_mode, 	osd1_path_buf_half,		0x1,
														osd1_path_buf_repeat,	0x1,
														osd1_3d_en,				0x1,
														osd1_3d_mode_sel,		0x0	);	/* S/S */
	
					OSD_L9A0_Wr04(osd1_3d_disparity,	osd1_right_disparity_value,	0,
														osd1_right_disparity_sign,	0,	/* 0: L->R, 1: R->L */
														osd1_left_disparity_value,	0,
														osd1_left_disparity_sign,	1 );/* 0: L->R, 1: R->L */
				}
				else if ( ctrl->mode == LX_FBDEV_TRID_MODE_TB )
				{
					OSD_L9A0_Wr04(osd1_3d_path_mode,	osd1_path_buf_half,		0x0,
														osd1_path_buf_repeat,	0x0,
														osd1_3d_en,				0x1,
														osd1_3d_mode_sel,		0x1	);	/* T/B */

					OSD_L9A0_Wr04(osd1_3d_disparity,	osd1_right_disparity_value,	0,
														osd1_right_disparity_sign,	0,	/* 0: L->R, 1: R->L */
														osd1_left_disparity_value,	0,
														osd1_left_disparity_sign,	1 );/* 0: L->R, 1: R->L */
				}
				else /* NORMAL */
				{
					OSD_L9A0_Wr( osd1_3d_path_mode,	0x00000000 );	/* all clear and make to be default */
					OSD_L9A0_Wr( osd1_3d_disparity,	0x00000000 );	/* all clear and make to be default */
				}
			}

			OSD_L9A0_Wr( osd1_left_3d_blank, 	0xff000000 );	/* black color */
			OSD_L9A0_Wr( osd1_right_3d_blank, 	0xff000000 );	/* black color */
			OSD_L9A0_Wr( osd1_tb_space,			0x00000000 );

			if ( g_fbdev_l9_hw_func.L9_SetTridCtrl )
			{
				ret = g_fbdev_l9_hw_func.L9_SetTridCtrl( layer, ctrl );
			}

			/* chip revision handler can ovrride the default 3DOSD config */
			OSD_L9A0_WrFL( osd1_3d_path_mode );
			OSD_L9A0_WrFL( osd1_3d_disparity );
			OSD_L9A0_WrFL( osd1_left_3d_blank );
			OSD_L9A0_WrFL( osd1_left_3d_blank );
			OSD_L9A0_WrFL( osd1_tb_space );
		}
		break;

		case LX_FBDEV_ID_OSD2:
		{
			OSD_L9A0_RdFL( osd2_3d_path_mode );
			OSD_L9A0_RdFL( osd2_3d_disparity );

			if ( g_fbdev_cfg->fb[2].b_use_trid_hw )
			{
				if ( ctrl->mode == LX_FBDEV_TRID_MODE_SS )
				{
					OSD_L9A0_Wr04(osd2_3d_path_mode, 	osd2_path_buf_half,		0x1,
														osd2_path_buf_repeat,	0x1,
														osd2_3d_en,				0x1,
														osd2_3d_mode_sel,		0x0	);	/* S/S */
	
					OSD_L9A0_Wr04(osd2_3d_disparity,	osd2_right_disparity_value,	0,
														osd2_right_disparity_sign,	0, /* 0: L->R, 1: R->L */
														osd2_left_disparity_value,	0,
														osd2_left_disparity_sign,	1 ); /* 0: L->R, 1: R->L */
				}
				else if ( ctrl->mode == LX_FBDEV_TRID_MODE_TB )
				{
					OSD_L9A0_Wr04(osd2_3d_path_mode, 	osd2_path_buf_half,		0x0,
														osd2_path_buf_repeat,	0x0,
														osd2_3d_en,				0x1,
														osd2_3d_mode_sel,		0x1	);	/* T/B */
	
					OSD_L9A0_Wr04(osd2_3d_disparity,	osd2_right_disparity_value,	0,
														osd2_right_disparity_sign,	0,
														osd2_left_disparity_value,	0,
														osd2_left_disparity_sign,	1 );
				}
				else /* NORMAL */
				{
					OSD_L9A0_Wr( osd2_3d_path_mode,		0x00000000 );	/* all clear and make to be default */
					OSD_L9A0_Wr( osd2_3d_disparity,		0x00000000 );	/* all clear and make to be default */
				}
			}
	
			OSD_L9A0_Wr( osd2_left_3d_blank, 	0xff000000 );		/* black color */
			OSD_L9A0_Wr( osd2_right_3d_blank, 	0xff000000 );		/* black color*/
			OSD_L9A0_Wr( osd2_tb_space,			0x00000000 );

			/* chip revision handler can ovrride the default 3DOSD config */
			if ( g_fbdev_l9_hw_func.L9_SetTridCtrl )
			{
				ret = g_fbdev_l9_hw_func.L9_SetTridCtrl( layer, ctrl );
			}

			OSD_L9A0_WrFL( osd2_3d_path_mode );
			OSD_L9A0_WrFL( osd2_3d_disparity );
			OSD_L9A0_WrFL( osd2_left_3d_blank );
			OSD_L9A0_WrFL( osd2_left_3d_blank );
			OSD_L9A0_WrFL( osd2_tb_space );
		}
		break;

		case LX_FBDEV_ID_CSR0:
		{
			OSD_L9A0_RdFL( crsr_3d_path_mode );
			OSD_L9A0_RdFL( crsr_3d_disparity );

			if ( g_fbdev_cfg->fb[3].b_use_trid_hw )
			{
				if ( ctrl->mode == LX_FBDEV_TRID_MODE_SS )
				{
					OSD_L9A0_Wr04(crsr_3d_path_mode,	crsr_path_buf_half,		0x1,
														crsr_path_buf_repeat,	0x1,
														crsr_3d_en,				0x1,
														crsr_3d_mode_sel,		0x0	);	/* S/S */
	
					OSD_L9A0_Wr04(crsr_3d_disparity,	crsr_right_disparity_value,	0,
														crsr_right_disparity_sign,	0,	/* 0: L->R, 1: R->L */
														crsr_left_disparity_value,	0,
														crsr_left_disparity_sign,	1 ); /* 0: L->R, 1: R->L */
				}
				else if ( ctrl->mode == LX_FBDEV_TRID_MODE_TB )
				{
					OSD_L9A0_Wr04(crsr_3d_path_mode, 	crsr_path_buf_half,		0x0,
														crsr_path_buf_repeat,	0x0,
														crsr_3d_en,				0x1,
														crsr_3d_mode_sel,		0x1	);	/* T/B */

					OSD_L9A0_Wr04(crsr_3d_disparity,	crsr_right_disparity_value,	0,
														crsr_right_disparity_sign,	0,	/* 0: L->R, 1: R->L */
														crsr_left_disparity_value,	0,
														crsr_left_disparity_sign,	1 ); /* 0: L->R, 1: R->L */
				}
				else /* NORMAL */
				{
					OSD_L9A0_Wr( crsr_3d_path_mode,	0x00000000 );	/* all clear and make to be default */
					OSD_L9A0_Wr( crsr_3d_disparity,	0x00000000 );	/* all clear and make to be default */
				}
			}

			OSD_L9A0_Wr( crsr_left_3d_blank, 	0x00000000 );	/* empty color ? */
			OSD_L9A0_Wr( crsr_right_3d_blank, 	0x00000000 );	/* empty color ? */
			OSD_L9A0_Wr( crsr_tb_space,			0x00000000 );

			/* chip revision handler can ovrride the default 3DOSD config */
			if ( g_fbdev_l9_hw_func.L9_SetTridCtrl )
			{
				ret = g_fbdev_l9_hw_func.L9_SetTridCtrl( layer, ctrl );
			}

			OSD_L9A0_WrFL( crsr_3d_path_mode );
			OSD_L9A0_WrFL( crsr_3d_disparity );
			OSD_L9A0_WrFL( crsr_left_3d_blank );
			OSD_L9A0_WrFL( crsr_left_3d_blank );
			OSD_L9A0_WrFL( crsr_tb_space );
		}
		break;

		default:
		{
			/* do nothing */
		}
	}

	return ret;
}

/** configure POSD path control ( L only, R only or L/R both )
 *
 *
 * when transition from SEP to BLEND mode, screen blank may ocurr since FRC needs 6 frame delay to show OSD in blend mode.
 * To prevent screen blank, we should change state via intermediate "L/R" mode during 6 frame times.
 * (confirmed by ±è¿õÇö, ÁøÀ±Á¾)
 *
 * raxis.lim (2012/02/02)
 * I've found that screen blank may ocurr even when OSD path is changed from BLEND to SEP mode.
 * So add the intermediate state "L/R" when new configuration is feeded.
 *
 */
int FBDEV_L9_SetOutPathCtrl      (int layer, LX_FBDEV_OUT_PATH_CTRL_T* ctrl)
{
#define	WAIT_FOR_FRC_STABLE()	OS_MsecSleep(100)	/* wait FRC to be stablized. 8 ms * 6 frame = 48 ms or 16.7 ms * 6 frame = 96 ms ??? */
	UINT32 old_dir;
	UINT32 dir = (*ctrl==LX_FBDEV_OUT_PATH_CTRL_BLEND)? 0x1 /*L only*/: 0x2 /*R only*/;

	switch( layer )
	{
		case LX_FBDEV_ID_OSD0:
		{
			OSD_L9A0_RdFL( osd0_3d_path_mode );
			OSD_L9A0_Rd01( osd0_3d_path_mode, osd0_path_sel, old_dir );

//			if ( old_dir == 0x2 && dir == 0x1 )	/* SEP -> BLEND */
			if ( old_dir != dir )
			{
				OSD_L9A0_Wr01( osd0_3d_path_mode, osd0_path_sel, 0x0 /* L/R */);
				OSD_L9A0_WrFL( osd0_3d_path_mode );
				WAIT_FOR_FRC_STABLE();
			}
			OSD_L9A0_Wr01( osd0_3d_path_mode, osd0_path_sel, dir );
			OSD_L9A0_WrFL( osd0_3d_path_mode );
		}
		break;

		case LX_FBDEV_ID_OSD1:
		{
			OSD_L9A0_RdFL( osd1_3d_path_mode );
			OSD_L9A0_Rd01( osd1_3d_path_mode, osd1_path_sel, old_dir );

//			if ( old_dir == 0x2 && dir == 0x1 )	/* SEP -> BLEND */
			if ( old_dir != dir )
			{
				OSD_L9A0_Wr01( osd1_3d_path_mode, osd1_path_sel, 0x0 /* L/R */);
				OSD_L9A0_WrFL( osd1_3d_path_mode );
				WAIT_FOR_FRC_STABLE();
			}
			OSD_L9A0_Wr01( osd1_3d_path_mode, osd1_path_sel, dir );
			OSD_L9A0_WrFL( osd1_3d_path_mode );
		}
		break;

		case LX_FBDEV_ID_OSD2:
		{
			OSD_L9A0_RdFL( osd2_3d_path_mode );
			OSD_L9A0_Rd01( osd2_3d_path_mode, osd2_path_sel, old_dir );

//			if ( old_dir == 0x2 && dir == 0x1 )	/* SEP -> BLEND */
			if ( old_dir != dir )
			{
				OSD_L9A0_Wr01( osd2_3d_path_mode, osd2_path_sel, 0x0 /* L/R */);
				OSD_L9A0_WrFL( osd2_3d_path_mode );
				WAIT_FOR_FRC_STABLE();
			}
			OSD_L9A0_Wr01( osd2_3d_path_mode, osd2_path_sel, dir );
			OSD_L9A0_WrFL( osd2_3d_path_mode );
		}
		break;

		case LX_FBDEV_ID_CSR0:
		{
			OSD_L9A0_RdFL( crsr_3d_path_mode );
			OSD_L9A0_Rd01( crsr_3d_path_mode, crsr_path_sel, old_dir );

//			if ( old_dir == 0x2 && dir == 0x1 )	/* SEP -> BLEND */
			if ( old_dir != dir )
			{
				OSD_L9A0_Wr01( crsr_3d_path_mode, crsr_path_sel, 0x0 /* L/R */);
				OSD_L9A0_WrFL( crsr_3d_path_mode );
				WAIT_FOR_FRC_STABLE();
			}
			OSD_L9A0_Wr01( crsr_3d_path_mode, crsr_path_sel, dir );
			OSD_L9A0_WrFL( crsr_3d_path_mode );
		}
		break;

		default:
		{
			/* do nothing */
		}
	}

	return RET_OK;
}

/*========================================================================================
	Implementation Group (REV dependent)
========================================================================================*/

/** set OSD output ctrl
 *
 *	@param pConnCtrl [IN] connection control data
 *	@return RET_OK if success, RET_ERROR otherwise
 *
 */
int     FBDEV_L9_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* pConnCtrl)
{
	int	ret = RET_ERROR;

	if ( g_fbdev_l9_hw_func.L9_SetConnCtrl )
	{
		ret = g_fbdev_l9_hw_func.L9_SetConnCtrl( pConnCtrl );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
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
int FBDEV_L9_WriteOSDHeader( struct scanvas *hCanvas )
{
	int	ret = RET_ERROR;

	if ( g_fbdev_l9_hw_func.L9_WriteOSDHeader )
	{
		ret = g_fbdev_l9_hw_func.L9_WriteOSDHeader( hCanvas );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
	}

	return ret;
}

/** OSD HW Layer enable/disable
 *
 * @param	int layer : osd layer ,
 *		enable : 0 : display off , 1 : display on
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_SetOSDEnable(int layer , int enable)
{
	int	ret = RET_ERROR;

	if ( g_fbdev_l9_hw_func.L9_SetOSDEnable )
	{
		ret = g_fbdev_l9_hw_func.L9_SetOSDEnable( layer, enable );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
	}

	return ret;
}

/** OSD HW Layer status
 *
 * @param	void
 * @return	int 1 : ON , 0 : OFF
 *
 */
int FBDEV_L9_GetOSDEnable(int layer)
{
	int	ret = RET_ERROR;

	if ( g_fbdev_l9_hw_func.L9_GetOSDEnable )
	{
		ret = g_fbdev_l9_hw_func.L9_GetOSDEnable( layer );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
	}

	return ret;
}

/*========================================================================================
	Implementation Group (Event)
========================================================================================*/
void FBDEV_L9_EventCallback		(FBDEV_HW_EVENT_T ev, FBDEV_HW_EVENT_DATA_T* data )
{
	switch(ev)
	{
		case FBDEV_HW_EVENT_PXL_FMT_CHANGE:
		{
			/* do nothing */
		}
		break;

		case FBDEV_HW_EVENT_VSYNC:
		{
			if ( g_fbdev_l9_hw_func.L9_ISRTickHandler )
			{
				g_fbdev_l9_hw_func.L9_ISRTickHandler( );
			}
		}
		break;

		default:
		{

		}
		break;
	}
}

/*========================================================================================
	Implementation Group (PM)
========================================================================================*/
int	FBDEV_L9_RunResume	( void )
{
	/* do nothing. not ready */
	return RET_OK;
}

int	FBDEV_L9_RunSuspend	( void )
{
	/* do nothing. not ready */
	return RET_OK;
}

