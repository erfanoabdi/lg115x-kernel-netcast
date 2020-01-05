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

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "fbdev_impl.h"
#include "fbdev_hw.h"
#include "fbdev_hw_h13.h"
#include "fbdev_reg_h13.h"
#include "mif_osd_reg_h13.h"
#include "fbdev_hal.h"
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "../sys/ctop_regs.h"

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
extern void FBDEV_H13_EventCallback		(FBDEV_HW_EVENT_T ev, FBDEV_HW_EVENT_DATA_T* data );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern FBDEV_H13_HW_CTX_T		g_fbdev_h13a0_hw_ctx;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_H13_InitOSDZOrder ( void );

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_H13_REG_T*			g_fbdev_h13_reg;
OSD_H13_REG_T*					g_fbdev_h13_reg_cached;
volatile MIF_OSD_H13_REG_T*		g_mif_osd_h13_reg;
MIF_OSD_H13_REG_T*				g_mif_osd_h13_reg_cached;

FBDEV_H13_HW_CTX_T				g_fbdev_h13_hw_ctx;			/* H13 OSD H/W ctrl */

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
LX_FBDEV_CFG_T*	FBDEV_H13_GetCfg(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static	FBDEV_HW_CTX_T		g_fbdev_hw_ctx_h13 =
{
	.GetCfg				= FBDEV_H13_GetCfg,
	.RunSuspend			= FBDEV_H13_RunSuspend,
	.RunResume			= FBDEV_H13_RunResume,

	.InitHW				= FBDEV_H13_InitHW,
	.ShutdownHW			= FBDEV_H13_ShutdownHW,

	.SetOSDEnable		= FBDEV_H13_SetOSDEnable,
	.GetOSDEnable		= FBDEV_H13_GetOSDEnable,

	.InitOSDLayer		= FBDEV_H13_InitOSDLayer,
	.WriteOSDHeader		= FBDEV_H13_WriteOSDHeader,

	.GetZList			= FBDEV_H13_GetZList,
	.SetZList			= FBDEV_H13_SetZList,
    .SetVideoMixerCtrl  = FBDEV_H13_SetVideoMixerCtrl,

	.WriteOSDEndian		= FBDEV_H13_WriteOSDEndian,
	.WriteOSDCSC		= FBDEV_H13_WriteOSDCSC,

	.GetInterruptStatus	= FBDEV_H13_GetInterruptStatus,
	.SetInterruptClear	= FBDEV_H13_SetInterruptClear,
	.SetInterruptEnable	= FBDEV_H13_SetInterruptEnable,

	.SetViewCtrl		= FBDEV_H13_SetViewCtrl,
	.SetTridCtrl		= FBDEV_H13_SetTridCtrl,
	.SetConnCtrl		= FBDEV_H13_SetConnCtrl,
	.SetOutPathCtrl		= FBDEV_H13_SetOutPathCtrl,

	.EventCallback		= FBDEV_H13_EventCallback,
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get H13 specific configuration
 *
 *  @return LX_FBDEV_CFG_T
 */
LX_FBDEV_CFG_T*   FBDEV_H13_GetCfg(void)
{
    return NULL;
}

/** initialize H13 specific HW Ctx.
 *
 *	@note this function is called before any H13 configuration
 */
void	FBDEV_H13_InitHWCtx( FBDEV_HW_CTX_T*	hal )
{
	int	i;

	/* select the active H13 HW function handler */
	switch( lx_chip_rev() )
	{
		case LX_CHIP_REV(H13,A0):
		default:
			memcpy( &g_fbdev_h13_hw_ctx, &g_fbdev_h13a0_hw_ctx, sizeof(FBDEV_H13_HW_CTX_T)); break;

	}

	/* initialize variable such as FRC ctrl, vosd ctrl etc */

	memset( &g_fbdev_h13_hw_ctx.frc_if_ctrl, 0x0, sizeof(FBDEV_H13_FRC_IF_CTRL_T));

    for( i=0; i<LX_FBDEV_ID_MAX; i++ )
    {
        g_fbdev_h13_hw_ctx.vosd_ctrl[i].opmask       = FBDEV_H13_VOSD_OPMASK_NONE;
        g_fbdev_h13_hw_ctx.vosd_ctrl[i].osd_idx      =  0;
        g_fbdev_h13_hw_ctx.vosd_ctrl[i].my_vsync     = -1;
        g_fbdev_h13_hw_ctx.vosd_ctrl[i].osd_surf[0]  = -1;
        g_fbdev_h13_hw_ctx.vosd_ctrl[i].osd_surf[1]  = -1;
        g_fbdev_h13_hw_ctx.vosd_ctrl[i].fb_mem_ptr[0]= 0x0;
        g_fbdev_h13_hw_ctx.vosd_ctrl[i].fb_mem_ptr[1]= 0x0;

        g_fbdev_h13_hw_ctx.clut_vosd_ctrl[i].osd_idx      =  0;
        g_fbdev_h13_hw_ctx.clut_vosd_ctrl[i].my_vsync     = -1;
        g_fbdev_h13_hw_ctx.clut_vosd_ctrl[i].osd_surf[0]  = -1;
        g_fbdev_h13_hw_ctx.clut_vosd_ctrl[i].osd_surf[1]  = -1;
        g_fbdev_h13_hw_ctx.clut_vosd_ctrl[i].fb_mem_ptr[0]= 0x0;
        g_fbdev_h13_hw_ctx.clut_vosd_ctrl[i].fb_mem_ptr[1]= 0x0;
	}
#if (CONFIG_LX_BOOT_LOGO==1)
	printk("[fb] disable video mix\n");
	g_fbdev_h13_hw_ctx.video_mixer_ctrl.b_video_mix = FALSE;
#else
	g_fbdev_h13_hw_ctx.video_mixer_ctrl.b_video_mix = TRUE;
#endif

	/* fill hal value */
	memcpy( hal, &g_fbdev_hw_ctx_h13, sizeof(FBDEV_HW_CTX_T));
	hal->chip_priv_ctx = &g_fbdev_h13_hw_ctx;
}

/*========================================================================================
	Implementation Group (INIT/EXIT)
========================================================================================*/
/** initialize OSD IP HW and register
 *
 * @param
 * @return	int 0 : OK , -1 : NOT OK
 *
 * [OK]
 */
int FBDEV_H13_InitHW		(void)
{
	int					ret = RET_ERROR;

	/* access to register */
	g_fbdev_h13_reg =(OSD_H13_REG_T *)ioremap( g_reg_io_ctx->reg_base_addr, g_reg_io_ctx->reg_size );
	FBDEV_CHECK_CODE( g_fbdev_h13_reg == NULL, goto func_exit, "out of memory\n");

	g_fbdev_h13_reg_cached = (OSD_H13_REG_T *)OS_Malloc( g_reg_io_ctx->reg_size );
	FBDEV_CHECK_CODE( g_fbdev_h13_reg_cached == NULL, return RET_ERROR, "out of memory\n");

	/* access to mif register */
	g_mif_osd_h13_reg =(MIF_OSD_H13_REG_T*)ioremap( 0xc0035900, sizeof(MIF_OSD_H13_REG_T));
	FBDEV_CHECK_CODE( g_mif_osd_h13_reg == NULL, goto func_exit, "out of memory\n");

	g_mif_osd_h13_reg_cached = (MIF_OSD_H13_REG_T*)OS_Malloc( sizeof(MIF_OSD_H13_REG_T));
	FBDEV_CHECK_CODE( g_mif_osd_h13_reg_cached == NULL, return RET_ERROR, "out of memory\n");

	/* DE_TOP::DED_CTRL::DED_PIC_INIT */
	OS_WrReg ( 0xc0035000, 0x08000000 );
//	FBDEV_WriteReg( 0xc0035000, 0x08000000 );


	/* OSD SCALER 2*LineMemory Enable.
	 * [TODO] rewrite the below bad code :(
	 */
	__raw_writel(0x80001000 , (ULONG)(g_fbdev_h13_reg) + 0x110);
	__raw_writel(0x80001000 , (ULONG)(g_fbdev_h13_reg) + 0x150);
	__raw_writel(0x80001000 , (ULONG)(g_fbdev_h13_reg) + 0x1D0);

	/* make POSD order to be default */
	FBDEV_H13_InitOSDZOrder( );

	/* call revision specific initialization */
	g_fbdev_h13_hw_ctx.H13_InitHW( );

	ret = RET_OK; /* all work done */
func_exit:
	return ret;
}

/** de-initial OSD IP HW and register
 *
 * @param
 * @return	int 0 : OK , -1 : NOT OK
 *
 * [OK]
 */
int FBDEV_H13_ShutdownHW	(void)
{
	int ret = RET_OK;

	iounmap((void*)g_fbdev_h13_reg);

	return ret;
}

/** make initial OSD zorder.
 *
 *	@return none
 *	@note this function controls osd_layer_mux register
 *	@note H13 doesn't support POSD2
 */
void FBDEV_H13_InitOSDZOrder ( void )
{
    LX_FBDEV_ZLIST_T    zlist;

    zlist.path      = LX_FBDEV_PATH_ALL;
    zlist.order[0]  = LX_FBDEV_ZLIST_OSD0;  /* top most . H/W default */
    zlist.order[1]  = LX_FBDEV_ZLIST_OSD1;  /* center   . H/W default */
    zlist.order[2]  = LX_FBDEV_ZLIST_VIDEO; /* bottom   . H/W default */

	FBDEV_H13_SetZList( &zlist );

	return;
}

/*========================================================================================
	Implementation Group
========================================================================================*/
static const int 		pixel_depth_2_bpp[PIX_DEPTH_MAX] = { 1, 2, 4, 8, 16, 24, 32  };

/*========================================================================================
	Implementation Group
========================================================================================*/
/** make OSD to be initial state
 *	make the basic configuration for each OSD layer.
 *
 *	@param layerId
 *
 *	[OK]
 */
int FBDEV_H13_InitOSDLayer ( int layer )
{
	int ret = RET_ERROR;

	/* please refer to OSD manual OSD?_CFG field */
	UINT32  hdr_src_sel;
	UINT32  osd_hdr_addr;

	if ( g_reg_io_ctx->hdr_op_method == FBDEV_HDR_OP_MMIO )
	{
		hdr_src_sel = 0;
	}
	else
	{
		hdr_src_sel = 1;
	}

	osd_hdr_addr = (gMemCfgFBHdr[layer].mem_header_base);

    switch( layer )
    {
        case LX_FBDEV_ID_OSD0:
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==0)
			/* keep OSD on/off status */
#else
            g_fbdev_h13_reg->osd0_ctrl_main.osd0_en 				= 0;
#endif
#ifdef FBDEV_USE_HDR_RDY_REG
			g_fbdev_h13_reg->osd0_ctrl_main.osd0_hdr_ready_flag_en	= 0x1;
#endif
            g_fbdev_h13_reg->osd0_ctrl_main.osd0_hdr_src_sel		= hdr_src_sel;
            g_fbdev_h13_reg->osd0_ctrl_base_addr.osd0_base_addr 	= osd_hdr_addr;	/* set header data address */

			g_fbdev_h13_reg->osd0_ctrl_scaler.osd0_sc_sampling_mode	= 0x1;			/* set scaler sample mode to normal (same as GFX) */
        break;

        case LX_FBDEV_ID_OSD1:
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==1)
			/* keep OSD on/off status */
#else
            g_fbdev_h13_reg->osd1_ctrl_main.osd1_en 				= 0;
#endif
#ifdef FBDEV_USE_HDR_RDY_REG
			g_fbdev_h13_reg->osd1_ctrl_main.osd1_hdr_ready_flag_en	= 0x1;
#endif
            g_fbdev_h13_reg->osd1_ctrl_main.osd1_hdr_src_sel		= hdr_src_sel;
            g_fbdev_h13_reg->osd1_ctrl_base_addr.osd1_base_addr 	= osd_hdr_addr; /* set header data address */

			g_fbdev_h13_reg->osd1_ctrl_scaler.osd1_sc_sampling_mode	= 0x1;			/* set scaler sample mode to normal (same as GFX) */
        break;

        case LX_FBDEV_ID_OSD2:
#if (CONFIG_LX_BOOT_LOGO==1 && CONFIG_LX_BOOT_LOGO_FBDEV==2)
			/* keep OSD on/off status */
#else
            g_fbdev_h13_reg->osd2_ctrl_main.osd2_en 				= 0;
#endif
#ifdef FBDEV_USE_HDR_RDY_REG
            g_fbdev_h13_reg->osd2_ctrl_main.osd2_hdr_ready_flag_en	= 0x1;
#endif
            g_fbdev_h13_reg->osd2_ctrl_main.osd2_hdr_src_sel 		= hdr_src_sel;
            g_fbdev_h13_reg->osd2_ctrl_base_addr.osd2_base_addr		= osd_hdr_addr;	/* set header data address */

			g_fbdev_h13_reg->osd1_ctrl_scaler.osd1_sc_sampling_mode	= 0x1;			/* set scaler sample mode to normal (same as GFX) */
        break;

        case LX_FBDEV_ID_CSR0:
            g_fbdev_h13_reg->osd3_ctrl_main.osd3_en 				= 0;
#ifdef FBDEV_USE_HDR_RDY_REG
            g_fbdev_h13_reg->osd3_ctrl_main.osd3_hdr_ready_flag_en	= 0x1;
#endif
            g_fbdev_h13_reg->osd3_ctrl_main.osd3_hdr_src_sel 		= hdr_src_sel;
            g_fbdev_h13_reg->osd3_ctrl_base_addr.osd3_base_addr 	= osd_hdr_addr; 	/* set header data address */

			g_fbdev_h13_reg->osd1_ctrl_scaler.osd1_sc_sampling_mode  = 0x1;			/* set scaler sample mode to normal (same as GFX) */
        break;

        default:
            FBDEV_ERROR("invalid osd %d\n", layer ); goto func_exit;
        break;
    }

    ret = RET_OK;   /* all work done */
func_exit:

    return ret;
}

/** set endianess on each layer
 *
 * @param	ENDIAN_INFORM_T
 * @return	int 0 : OK , -1 : NOT OK
 *
 *	[OK]
 */
int FBDEV_H13_WriteOSDEndian(int layer , ENDIAN_INFORM_T *endian)
{
    int ret = RET_OK;

    unsigned int temp;

    temp = (unsigned int)((endian->header << 8) | (endian->palette << 4) | (endian->image << 0) );

    switch(layer){
        case LX_FBDEV_ID_OSD0:
            memcpy( (void *)&g_fbdev_h13_reg->osd0_ctrl_swap, (void *)&temp , sizeof(int) );
        break;

        case LX_FBDEV_ID_OSD1:
            memcpy( (void *)&g_fbdev_h13_reg->osd1_ctrl_swap ,(void *) &temp , sizeof(int) );
        break;

        case LX_FBDEV_ID_OSD2:
            memcpy( (void *)&g_fbdev_h13_reg->osd2_ctrl_swap, (void *)&temp , sizeof(int) );
        break;

        case LX_FBDEV_ID_CSR0:
            memcpy( (void *)&g_fbdev_h13_reg->osd3_ctrl_swap, (void *) &temp , sizeof(int) );
        break;
        default:
            FBDEV_PRINT("WARNING : invalid int type %s %d\n" , __func__ , __LINE__);
            ret = RET_ERROR;
        break;
    }

    return ret;
}

/** set color space conversion on each layer
 *
 * @param	int layer , CSC_INFORM_T *csc
 * @return	int 0 : OK , -1 : NOT OK
 *
 *	@note H13 doesn't support CSC for each layer
 *
 *	[OK]
 */
int FBDEV_H13_WriteOSDCSC(int layer , CSC_INFORM_T *csc)
{
    int ret = 0;

    switch(layer){
        case LX_FBDEV_ID_OSD0:
        case LX_FBDEV_ID_OSD1:
        case LX_FBDEV_ID_OSD2:
        case LX_FBDEV_ID_CSR0:
            g_fbdev_h13_reg->osd_common_csc_coef0.reg_common_csc0_datai 	= csc->data;
            g_fbdev_h13_reg->osd_common_csc_coef0.reg_common_csc0_rw_n 		= csc->rw_n;
            g_fbdev_h13_reg->osd_common_csc_coef0.reg_common_csc0_bypass	= csc->bypass;
            g_fbdev_h13_reg->osd_common_csc_coef0.reg_common_csc0_sel 		= csc->sel;
            g_fbdev_h13_reg->osd_common_csc_coef0.reg_common_csc0_out_ctrl	= csc->out_ctrl;
            g_fbdev_h13_reg->osd_common_csc_coef0.reg_common_csc0_in_ctrl	= csc->in_ctrl;
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
 * [OK?]
 */
int FBDEV_H13_GetInterruptStatus(INTERRUPT_INFORM_T intr)
{
	UINT32  status = 0x0;

	OSD_H13_RdFL(osd_common_ctrl_irq);

	switch(intr)
	{
		case CRSR_INTR:
			OSD_H13_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd3, status);
		break;
		case OSD_0_INTR:
			OSD_H13_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd0, status);
		break;
		case OSD_1_INTR:
			OSD_H13_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd1, status);
		break;
		case OSD_2_INTR:
			OSD_H13_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd2, status);
		break;
		case MIXER_INTR:
			OSD_H13_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_mixer, status);
		break;
		case MIXER_INTR_EXT:
			OSD_H13_Rd01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_mixer_60hz, status);
		break;
			case ALL_INTR:
		default:            status = (OSD_H13_Rd(osd_common_ctrl_irq)) & 0x3f;    break;
	}

    //FBDEV_PRINT("intr(%d) status %x\n", intr, status );

    return status;

	return status;
}

/** Clear interrupt status
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T
 * @return	int 0 : OK , -1 : NOT OK
 *
 * [OK]
 */
int FBDEV_H13_SetInterruptClear(INTERRUPT_INFORM_T intr)
{
	OSD_H13_RdFL(osd_common_ctrl_irq);

	switch(intr)
	{
    	case OSD_0_INTR:	OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd0, 1);		break;
    	case OSD_1_INTR:	OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd1, 1);		break;
		case OSD_2_INTR:	OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd2, 1);		break;
    	case CRSR_INTR:		OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd3, 1);		break;
		case MIXER_INTR:	OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_mixer,1);		break;
		case MIXER_INTR_EXT:OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_mixer_60hz,1);	break;
		case ALL_INTR:
		default:			OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd0, 1);
							OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd1, 1);
							OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd2, 1);
							OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_osd3, 1);
							OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_mixer,1);		break;
							OSD_H13_Wr01(osd_common_ctrl_irq, reg_common_ctrl_irq_clear_mixer_60hz,1);	break;
	}

	OSD_H13_WrFL(osd_common_ctrl_irq);

	return RET_OK;
}

/** Set interrupt enable/disable
 * [note] If you don't need any interrupt service of FB device, DO NOT call this function
 *
 * @param	INTERRUPT_INFORM_T , int : enable/disable
 * @return	int 0 : OK , -1 : NOT OK
 *
 * [OK]
 */
int FBDEV_H13_SetInterruptEnable(INTERRUPT_INFORM_T intr , int enable)
{
    switch(intr)
    {
        case OSD_0_INTR:    g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd0 = enable; break;
        case OSD_1_INTR:    g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd1 = enable; break;
        case OSD_2_INTR:    g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd2 = enable; break;
        case CRSR_INTR:     g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd3 = enable; break;
        case MIXER_INTR:    g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_mixer= enable; break;
	    case MIXER_INTR_EXT:g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_mixer_60hz = enable; break;
        case ALL_INTR:
		default: 			g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd0 = enable;
							g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd1 = enable;
							g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd2 = enable;
							g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_osd3 = enable;
							g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_mixer= enable;
							g_fbdev_h13_reg->osd_common_ctrl_irq.reg_common_ctrl_irq_en_mixer_60hz = enable; break;
    }

    return RET_OK;
}

/** Update OSD ZList
 *
 * @param zList [IN] pointer to POSD List config.
 * @return RET_OK
 *
 * @note layer id definition is 03: video, 00: OSD0, 01: OSD1, 02: OSD2 ( refer to OSD register manual )
 * @note I will not use osd_mixer_ctrl_mux0.layer_mux_3 ( it's default value is POSD2 )
 *
 * [OK]
 */
int FBDEV_H13_SetZList ( LX_FBDEV_ZLIST_T* zList )
{
	UINT32	video_layer_off;

	/* raxis.lim (2012/12/10) -- I should control video mix flag to prevent screen garbage during bootlogo */
	video_layer_off = ( g_fbdev_h13_hw_ctx.video_mixer_ctrl.b_video_mix )? FALSE: TRUE;

	OSD_H13_RdFL(osd_mixer_ctrl_mux0);

	OSD_H13_Wr06(osd_mixer_ctrl_mux0, 	layer_mux_3,        0x2,
                                        layer_mux_2,        zList->order[0],
                                        layer_mux_1,        zList->order[1],
                                        layer_mux_0,        zList->order[2],
										video_layer_off,	video_layer_off,
                                        video_layer_alpha,  0xff );
    OSD_H13_WrFL(osd_mixer_ctrl_mux0);

	return RET_OK;
}

/** Get OSD ZList
 *
 * @param zList [OUT] pointer to POSD List config.
 * @return RET_OK
 *
 * @note layer id definition is 00: video, 01: OSD0, 02: OSD1, 03: OSD2
 * @note H13 doesn't support L&R zlist.
 * @note I will not use osd_mixer_ctrl_mux0.layer_mux_3 ( it's default value is POSD2 )
 *
 * [OK]
 */
int FBDEV_H13_GetZList( LX_FBDEV_ZLIST_T* zList )
{
    OSD_H13_RdFL(osd_mixer_ctrl_mux0);

	zList->order[0] = g_fbdev_h13_reg_cached->osd_mixer_ctrl_mux0.layer_mux_2;	/* top most */
	zList->order[1] = g_fbdev_h13_reg_cached->osd_mixer_ctrl_mux0.layer_mux_1;	/* midle */
	zList->order[2] = g_fbdev_h13_reg_cached->osd_mixer_ctrl_mux0.layer_mux_0;	/* bottom */

	return RET_OK;
}

/** control video mixer region
 *
 *	@note window_ctrl.window_alpha value is initialized as 0xff in OSD H/W.
 *		  actually, we don't need to set window_ctrl.window_alpha since it is always set to 0xff.
 *		  but I think that it is set to the right value explictely
 *
 *	[OK?]
 */
int FBDEV_H13_SetVideoMixerCtrl   (LX_FBDEV_VIDEO_MIXER_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;
	int b_enable = (ctrl->b_enable)? 0x1: 0x0;

	printk("[debug] path = 0x%x\n", ctrl->path   );
	printk("[debug] mixid= 0x%x\n", ctrl->mix_id );

	switch( ctrl->mix_id )
	{
		case 0:
		{
			OSD_H13_RdFL( osd_mixer_ctrl_mux1 );
			OSD_H13_RdFL( osd_mixer_ctrl_mux2 );
			OSD_H13_RdFL( osd_mixer_ctrl_mux3 );

			OSD_H13_Wr02( osd_mixer_ctrl_mux1, reg_mixer_window0_en, 		b_enable,
												reg_mixer_window0_alpha,	0xff );
			OSD_H13_Wr02( osd_mixer_ctrl_mux2, reg_mixer_window0_xpos, 		ctrl->mix_win.x,
												reg_mixer_window0_ypos, 	ctrl->mix_win.y );
			OSD_H13_Wr02( osd_mixer_ctrl_mux3, reg_mixer_window0_w, 		ctrl->mix_win.w,
												reg_mixer_window0_h, 		ctrl->mix_win.h );
			OSD_H13_WrFL( osd_mixer_ctrl_mux1 );
			OSD_H13_WrFL( osd_mixer_ctrl_mux2 );
			OSD_H13_WrFL( osd_mixer_ctrl_mux3 );
		}
		break;

		case 1:
		{
			OSD_H13_RdFL( osd_mixer_ctrl_mux4 );
			OSD_H13_RdFL( osd_mixer_ctrl_mux5 );
			OSD_H13_RdFL( osd_mixer_ctrl_mux6 );

			OSD_H13_Wr02( osd_mixer_ctrl_mux4, reg_mixer_window1_en, 		b_enable,
												reg_mixer_window1_alpha,	0xff );
			OSD_H13_Wr02( osd_mixer_ctrl_mux5, reg_mixer_window1_xpos, 		ctrl->mix_win.x,
												reg_mixer_window1_ypos, 	ctrl->mix_win.y );
			OSD_H13_Wr02( osd_mixer_ctrl_mux6, reg_mixer_window1_w, 		ctrl->mix_win.w,
												reg_mixer_window1_h, 		ctrl->mix_win.h );
			OSD_H13_WrFL( osd_mixer_ctrl_mux4 );
			OSD_H13_WrFL( osd_mixer_ctrl_mux5 );
			OSD_H13_WrFL( osd_mixer_ctrl_mux6 );
		}
		break;

		case 2:
		{
			OSD_H13_RdFL( osd_mixer_ctrl_mux7 );
			OSD_H13_RdFL( osd_mixer_ctrl_mux8 );
			OSD_H13_RdFL( osd_mixer_ctrl_mux9 );

			OSD_H13_Wr02( osd_mixer_ctrl_mux7, reg_mixer_window2_en, 		b_enable,
												reg_mixer_window2_alpha,	0xff );
			OSD_H13_Wr02( osd_mixer_ctrl_mux8, reg_mixer_window2_xpos, 		ctrl->mix_win.x,
												reg_mixer_window2_ypos, 	ctrl->mix_win.y );
			OSD_H13_Wr02( osd_mixer_ctrl_mux9, reg_mixer_window2_w, 		ctrl->mix_win.w,
												reg_mixer_window2_h, 		ctrl->mix_win.h );
			OSD_H13_WrFL( osd_mixer_ctrl_mux7 );
			OSD_H13_WrFL( osd_mixer_ctrl_mux8 );
			OSD_H13_WrFL( osd_mixer_ctrl_mux9 );
		}
		break;

		default: FBDEV_ERROR("invalid mix id %d\n", ctrl->mix_id ); goto func_exit;
	}

	ret = RET_OK; /* all work done */
func_exit:
	return ret;
}

/*========================================================================================
	Implementation Group (Event)
========================================================================================*/
static void FBDEV_H13_EnableVideoMix( ULONG data )
{
	g_fbdev_h13_hw_ctx.video_mixer_ctrl.b_video_mix = TRUE;
	FBDEV_H13_InitOSDZOrder( );

//	FBDEV_H13_SetOSDEnable( LX_FBDEV_ID_OSD0, FALSE );
}

void FBDEV_H13_EventCallback		(FBDEV_HW_EVENT_T ev, FBDEV_HW_EVENT_DATA_T* data )
{
	switch(ev)
	{
		/* H13 support only 1 8bpp OSD layer (it's selectable)
	 	 * before writing OSD header (before updating 8bpp OSD plane), selection register should be set !!
		 *
		 */
		case FBDEV_HW_EVENT_PXL_FMT_CHANGE:
		{
//			UINT32	fb_dev_id = data->pxl_fmt_change.fb_dev_id;
//			UINT32	bpp		  = data->pxl_fmt_change.bits_per_pixel;

#ifdef FBDEV_SUPPORT_8BPP_EMUL
			/* do nothing */
#else
			if ( bpp == 8 )
			{
				OSD_H13_RdFL(osd_common_plte_sel);
				OSD_H13_Wr01(osd_common_plte_sel, reg_common_plte_sel, fb_dev_id );
				OSD_H13_WrFL(osd_common_plte_sel);
				FBDEV_WARN("layer %d, 8bpp OSD selected\n", fb_dev_id );
			}
#endif
		}
		break;

		case FBDEV_HW_EVENT_REVERSE_SCREEN_CHANGE:
		{
			UINT32	fb_dev_id = data->reverse_screen_change.fb_dev_id;
			UINT32	enable	= data->reverse_screen_change.enable;

	        switch(fb_dev_id)
			{
				case LX_FBDEV_ID_OSD0:  g_fbdev_h13_reg->osd0_ctrl_main.osd0_v_reverse_en = enable; break;
				case LX_FBDEV_ID_OSD1:  g_fbdev_h13_reg->osd1_ctrl_main.osd1_v_reverse_en = enable; break;
				case LX_FBDEV_ID_OSD2:  g_fbdev_h13_reg->osd2_ctrl_main.osd2_v_reverse_en = enable; break;
				case LX_FBDEV_ID_CSR0:  g_fbdev_h13_reg->osd3_ctrl_main.osd3_v_reverse_en = enable; break;
				default:                FBDEV_WARN("invalid OSD ID %d\n", fb_dev_id ); break;
	        }
		}
		break;

		case FBDEV_HW_EVENT_VSYNC:
		{
			if ( g_fbdev_h13_hw_ctx.H13_ISRTickHandler )
			{
				g_fbdev_h13_hw_ctx.H13_ISRTickHandler( );
			}
		}
		break;

		case FBDEV_HW_EVENT_POSD_OPEN:
		{
#if (CONFIG_LX_BOOT_LOGO==1)
			/* raxis.lim (2012/12/10) -- enable video mix when application opens OSD at the initialization 
			 * this mechanism is very heuristic and should be fixed someday to the right place.
			 */
			static BOOLEAN		b_first_posd_open = TRUE;
			static OS_TIMER_T	video_mix_en_timer;
			if ( b_first_posd_open )
			{
				b_first_posd_open = FALSE;
				OS_InitTimer ( &video_mix_en_timer );
				OS_StartTimer( &video_mix_en_timer, FBDEV_H13_EnableVideoMix, OS_TIMER_TIMEOUT, 200 /*ms*/, 0x0 );
			}
#endif
		}
		break;

		default:
		{

		}
		break;
	}
}

/*========================================================================================
	Implementation Group (REV dependent)
========================================================================================*/
int		FBDEV_H13_SetViewCtrl(LX_FBDEV_VIEW_CTRL_T* ctrl )
{
	int	ret = RET_ERROR;

	if ( g_fbdev_h13_hw_ctx.H13_SetViewCtrl )
	{
		g_fbdev_h13_hw_ctx.H13_SetViewCtrl( ctrl );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
	}

	return ret;
}

/** set OSD output ctrl
 *
 *	@param pConnCtrl [IN] connection control data
 *	@return RET_OK if success, RET_ERROR otherwise
 *
 */
int     FBDEV_H13_SetConnCtrl(LX_FBDEV_CONN_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;

	if ( g_fbdev_h13_hw_ctx.H13_SetConnCtrl )
	{
		ret = g_fbdev_h13_hw_ctx.H13_SetConnCtrl( ctrl );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
	}

	return ret;
}

/** configure POSD path control ( L only, R only or L/R both )
 *
 *
 */
int FBDEV_H13_SetOutPathCtrl      (int layer, LX_FBDEV_OUT_PATH_CTRL_T* ctrl)
{
	int	ret = RET_ERROR;

	if ( g_fbdev_h13_hw_ctx.H13_SetOutPathCtrl )
	{
		ret = g_fbdev_h13_hw_ctx.H13_SetOutPathCtrl( layer, ctrl );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
	}

	return ret;
}

/** update 3D OSD mode
 *
 *	@param layer [IN] layerId
 *	@param ctrl [IN] new 3D config
 *	@return RET_OK if success, RET_ERROR otherwise
 */
int FBDEV_H13_SetTridCtrl( int layer, LX_FBDEV_TRID_CTRL_T* ctrl )
{
	int	ret = RET_ERROR;

	if ( g_fbdev_h13_hw_ctx.H13_SetTridCtrl )
	{
		ret = g_fbdev_h13_hw_ctx.H13_SetTridCtrl( layer, ctrl );
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
int FBDEV_H13_WriteOSDHeader( struct scanvas *hCanvas )
{
	int	ret = RET_ERROR;

	if ( g_fbdev_h13_hw_ctx.H13_WriteOSDHeader )
	{
		if ( hCanvas->fb_dev_id == 0 && g_fbdev_h13_hw_ctx.video_mixer_ctrl.b_video_mix == FALSE ) return RET_OK;

		ret = g_fbdev_h13_hw_ctx.H13_WriteOSDHeader( hCanvas );
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
int FBDEV_H13_SetOSDEnable(int layer , int enable)
{
	int	ret = RET_ERROR;

	if ( g_fbdev_h13_hw_ctx.H13_SetOSDEnable )
	{
		ret = g_fbdev_h13_hw_ctx.H13_SetOSDEnable( layer, enable );
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
int FBDEV_H13_GetOSDEnable(int layer)
{
	int	ret = RET_ERROR;

	if ( g_fbdev_h13_hw_ctx.H13_GetOSDEnable )
	{
		ret = g_fbdev_h13_hw_ctx.H13_GetOSDEnable( layer );
	}
	else
	{
		FBDEV_ERROR("NULL handler\n");
	}

	return ret;
}


/*========================================================================================
	Implementation Group (PM)
========================================================================================*/
int	FBDEV_H13_RunResume	( void )
{
	/* do nothing. not ready */
	return RET_OK;
}

int	FBDEV_H13_RunSuspend	( void )
{
	/* do nothing. not ready */
	return RET_OK;
}

