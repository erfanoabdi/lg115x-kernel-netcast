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
#include "fbdev_hw_l9.h"
#include "fbdev_hal.h"
#include "fbdev_reg_l9a0.h"
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>
#include "l9/base_addr_sw_l9.h"

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
extern int FBDEV_L9_RunSuspend(void);
extern int FBDEV_L9_RunResume(void);

extern int FBDEV_L9_InitHW		        (void);
extern int FBDEV_L9_ShutdownHW			(void);
extern int FBDEV_L9_SetOSDEnable		(int layer , int enable);
extern int FBDEV_L9_GetOSDEnable		(int layer);
extern int FBDEV_L9_InitOSDLayer		(int layer);
//extern int FBDEV_L9_WriteOSDCfg		(LAYER_INFORM_T *inform);
extern int FBDEV_L9_WriteOSDHeader		(struct scanvas  *pstCanvas);

extern int FBDEV_L9_GetZList            (LX_FBDEV_ZLIST_T* zList );
extern int FBDEV_L9_SetZList            (LX_FBDEV_ZLIST_T* zList );
extern int FBDEV_L9_SetVideoMixerCtrl	(LX_FBDEV_VIDEO_MIXER_CTRL_T* ctrl);

extern int FBDEV_L9_WriteOSDEndian      (int layer , ENDIAN_INFORM_T *endian);
extern int FBDEV_L9_WriteOSDCSC         (int layer , CSC_INFORM_T *csc);
extern int FBDEV_L9_GetInterruptStatus  (INTERRUPT_INFORM_T intr);
extern int FBDEV_L9_SetInterruptClear   (INTERRUPT_INFORM_T intr);
extern int FBDEV_L9_SetInterruptEnable  (INTERRUPT_INFORM_T intr , int enable);

extern int FBDEV_L9_SetConnCtrl			(LX_FBDEV_CONN_CTRL_T* pConnCtrl);
extern int FBDEV_L9_SetTridCtrl			(int layer, LX_FBDEV_TRID_CTRL_T* ctrl);
extern int FBDEV_L9_SetOutPathCtrl		(int layer, LX_FBDEV_OUT_PATH_CTRL_T* ctrl);

extern void FBDEV_L9_EventCallback		(FBDEV_HW_EVENT_T ev, FBDEV_HW_EVENT_DATA_T* data );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern	FBDEV_L9_HW_FUNC_T	g_fbdev_l9a0_hw_func;
extern	FBDEV_L9_HW_FUNC_T	g_fbdev_l9b0_hw_func;
extern	FBDEV_L9_HW_FUNC_T	g_fbdev_l9b1_hw_func;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
void FBDEV_L9_InitOSDZOrder ( void );

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile OSD_L9A0_REG_T*	g_fbdev_l9_reg;
OSD_L9A0_REG_T*				g_fbdev_l9_reg_cached;
FBDEV_L9_HW_FUNC_T			g_fbdev_l9_hw_func;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
LX_FBDEV_CFG_T*	FBDEV_L9_GetCfg		(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static	FBDEV_HW_CTX_T		g_fbdev_hw_ctx_l9 =
{
	.GetCfg			= FBDEV_L9_GetCfg,
	.RunSuspend		= FBDEV_L9_RunSuspend,
	.RunResume		= FBDEV_L9_RunResume,

	.InitHW			= FBDEV_L9_InitHW,
	.ShutdownHW		= FBDEV_L9_ShutdownHW,

	.SetOSDEnable	= FBDEV_L9_SetOSDEnable,
	.GetOSDEnable	= FBDEV_L9_GetOSDEnable,

	.InitOSDLayer	= FBDEV_L9_InitOSDLayer,
	.WriteOSDHeader	= FBDEV_L9_WriteOSDHeader,

	.GetZList			= FBDEV_L9_GetZList,
	.SetZList			= FBDEV_L9_SetZList,
    .SetVideoMixerCtrl  = FBDEV_L9_SetVideoMixerCtrl,

	.WriteOSDEndian		= FBDEV_L9_WriteOSDEndian,
	.WriteOSDCSC		= FBDEV_L9_WriteOSDCSC,

	.GetInterruptStatus	= FBDEV_L9_GetInterruptStatus,
	.SetInterruptClear	= FBDEV_L9_SetInterruptClear,
	.SetInterruptEnable	= FBDEV_L9_SetInterruptEnable,

	.SetConnCtrl		= FBDEV_L9_SetConnCtrl,
	.SetTridCtrl		= FBDEV_L9_SetTridCtrl,
	.SetOutPathCtrl		= FBDEV_L9_SetOutPathCtrl,

	.EventCallback		= FBDEV_L9_EventCallback,	
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** get L9 specific configuration
 *
 *  @return LX_FBDEV_CFG_T
 */
LX_FBDEV_CFG_T*   FBDEV_L9_GetCfg(void)
{
    return NULL;
}

/** initialize L9 specific HW Ctx.
 *
 *	@note this function is called before any L9 configuration
 */
void	FBDEV_L9_InitHWCtx( FBDEV_HW_CTX_T*	hal )
{
	memcpy( hal, &g_fbdev_hw_ctx_l9, sizeof(FBDEV_HW_CTX_T));

	/* select the active L9 HW function handler */
	switch( lx_chip_rev() )
	{
		case LX_CHIP_REV(L9,A0):
		case LX_CHIP_REV(L9,A1): memcpy( &g_fbdev_l9_hw_func, &g_fbdev_l9a0_hw_func, sizeof(FBDEV_L9_HW_FUNC_T)); break;
		case LX_CHIP_REV(L9,B0): memcpy( &g_fbdev_l9_hw_func, &g_fbdev_l9b0_hw_func, sizeof(FBDEV_L9_HW_FUNC_T)); break;
		case LX_CHIP_REV(L9,B1): 
		default:				 memcpy( &g_fbdev_l9_hw_func, &g_fbdev_l9b1_hw_func, sizeof(FBDEV_L9_HW_FUNC_T)); break;
	}
}

/*========================================================================================
	Implementation Group (INIT/EXIT)
========================================================================================*/
/** initialize OSD IP HW and register
 *
 * @param
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_InitHW		(void)
{
	ULONG				addr;
	LX_ADDR_SW_CFG_T	addr_sw_cfg_osd;
	LX_ADDR_SW_CFG_T	addr_sw_cfg_gpu;
	int					ret = RET_ERROR;

	/* access to register */
	g_fbdev_l9_reg =(OSD_L9A0_REG_T *)ioremap( g_reg_io_ctx->reg_base_addr, g_reg_io_ctx->reg_size );
	FBDEV_CHECK_CODE( g_fbdev_l9_reg == NULL, goto func_exit, "out of memory\n");

	g_fbdev_l9_reg_cached = (OSD_L9A0_REG_T *)OS_Malloc( g_reg_io_ctx->reg_size );
	FBDEV_CHECK_CODE( g_fbdev_l9_reg_cached == NULL, return RET_ERROR, "out of memory\n");

	/* raxis.lim (2011/04/20) -- write L9 memory map value */
//	if (!request_mem_region(0xc0023000, 0x830, MODULE_NAME)) 
//	{
//		FBDEV_ERROR( "cannot reserve MMIO region\n"); goto func_exit;
//	}

	/* DE_TOP::DED_CTRL::DED_PIC_INIT */
	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) )
	{
 		addr = (unsigned long)ioremap(0xc0025000, 0xC00);
	}
	else /* L9A0, L9A1 */
	{
		addr = (unsigned long)ioremap(0xc0023000, 0xC00);
	}
	FBDEV_CHECK_CODE( addr == 0, goto func_exit, "out of memory\n");

	/* auto PIC signal */
    __raw_writel(0x08000000, addr + 0x0);
	/* raxis.lim (20110/08/28) -- adjust PIC singal */
	__raw_writel(0x00000010, addr + 0x28);
	__raw_writel(0x0000ffff, addr + 0x34);

	/* make DDR addressing for OSD
	 * raxis.lim (20110/08/28) -- L9B0 doesn't need to set the below register
	 */
	if ( lx_chip_rev() >= LX_CHIP_REV(L9,A0) && lx_chip_rev() < LX_CHIP_REV(L9,B0) )
	{
#if 1
		OSD_L9A0_Wr( osd_ddr_addressing, 0x00000010 );
		OSD_L9A0_WrFL( osd_ddr_addressing );
		OSD_L9A0_Wr( osd_ddr_addressing, 0x00000011 );
		OSD_L9A0_WrFL( osd_ddr_addressing );
		OSD_L9A0_Wr( osd_ddr_addressing, 0x00000012 );
		OSD_L9A0_WrFL( osd_ddr_addressing );
		OSD_L9A0_Wr( osd_ddr_addressing, 0x00000013 );
		OSD_L9A0_WrFL( osd_ddr_addressing );
		OSD_L9A0_Wr( osd_ddr_addressing, 0x00000002 );
		OSD_L9A0_WrFL( osd_ddr_addressing );
#else
		__raw_writel(0x00000010, addr + 0xbd0);
		__raw_writel(0x00000011, addr + 0xbd0);
		__raw_writel(0x00000012, addr + 0xbd0);
		__raw_writel(0x00000013, addr + 0xbd0);
		__raw_writel(0x00000002, addr + 0xbd0);
#endif
	}

	BASE_L9_GetAddrSwCfg ( ADDR_SW_CFG_DE_D /*OSD*/, &addr_sw_cfg_osd );
    __raw_writel( addr_sw_cfg_osd.de_sav, 		addr + 0x050);
    __raw_writel( addr_sw_cfg_osd.cpu_gpu, 		addr + 0x054);
    __raw_writel( addr_sw_cfg_osd.cpu_shadow, 	addr + 0x058);

    iounmap((void*)addr);

	/* make DDR addressing for GPU -- refer to LG1152-CO-MAN-02 V1.0 (GPU_Top_control).xls */
    addr = (unsigned long)ioremap(0xc000f800, 14);
    FBDEV_CHECK_CODE( addr == 0, goto func_exit, "out of memory\n");

	BASE_L9_GetAddrSwCfg ( ADDR_SW_CFG_GPU  /*GPU*/, &addr_sw_cfg_gpu );
    __raw_writel( addr_sw_cfg_gpu.de_sav, 		addr + 0x4);
    __raw_writel( addr_sw_cfg_gpu.cpu_gpu, 		addr + 0x8);
    __raw_writel( addr_sw_cfg_gpu.cpu_shadow, 	addr + 0xc);

    iounmap((void*)addr);

	FBDEV_L9_InitOSDZOrder( );

	/* why clear mixer ? */
//	OSD_L9A0_RdFL(osd_mixer_out_left);
//	OSD_L9A0_RdFL(osd_mixer_out_right);
	OSD_L9A0_Wr(osd_mixer_out_left,	0x00000000 );
	OSD_L9A0_Wr(osd_mixer_out_right,0x00000000 );
	OSD_L9A0_WrFL(osd_mixer_out_left);
	OSD_L9A0_WrFL(osd_mixer_out_right);

	/* raxis.lim (2011/11/24) -- configure MEMC off region for OSD blend path.
	 *
	 * we may configure only the left path since L9 uses the left path for blending mode.
	 * ( the right path is for the seprated mode )
	 *
	 * Threshold value 0xa doesn't have any speial meaning. 
	 * ideally threshold value should be 0x1 which means that any pixel having any alpha value should be non-EMC region.
	 * I selected 0xa since 0x1 is too tough :-)
	 * checked by ±è¿õÇö
	 */
	OSD_L9A0_RdFL(osd_frc_ablend_th_l);
	OSD_L9A0_Wr04(osd_frc_ablend_th_l,	osd0_external_blend_th_l, 0xa,
										osd1_external_blend_th_l, 0xa,
										osd2_external_blend_th_l, 0xa,
										crsr_external_blend_th_l, 0xa );
	OSD_L9A0_WrFL(osd_frc_ablend_th_l);

	/* raxis.lim (2010/06/05) -- set OSD scale factor */
	g_fbdev_l9_reg->osd0_sc_cfg.osd0_sc_bc_sa = 6;
	g_fbdev_l9_reg->osd1_sc_cfg.osd1_sc_bc_sa = 6;
	g_fbdev_l9_reg->osd2_sc_cfg.osd2_sc_bc_sa = 6;

	/* raxis.lim (2011/07/06) -- initialize OSD to be 2D mode */
	{
		LX_FBDEV_TRID_CTRL_T trid_ctrl = { LX_FBDEV_TRID_MODE_NONE, 0x0 };
		FBDEV_L9_SetTridCtrl( 0, &trid_ctrl );
		FBDEV_L9_SetTridCtrl( 1, &trid_ctrl );
		FBDEV_L9_SetTridCtrl( 2, &trid_ctrl );
		FBDEV_L9_SetTridCtrl( 3, &trid_ctrl );
	}

	/* raxis.lim (2011/07/11) -- enable FRC separated mode. 0000_0030(A0) or 0000_0031(A0,B0)
	 * refer to email from woong-hyeon.kim 2011/07/11 4:24p  
	 * raxis.lim (2011/10/25) -- change osd_scaler_mux selection to POSD0.
	 */
	if ( lx_chip_rev() >= LX_CHIP_REV(L9,B0) )
	{	
		g_fbdev_l9_reg->osd_scaler_mux.reg_osd_scaler_mux = 0x0;

		OSD_L9A0_Wr(osd_frc_if_cfg, 0x00000031 );
		OSD_L9A0_WrFL(osd_frc_if_cfg );
	}
	else
	{
		OSD_L9A0_Wr(osd_frc_if_cfg, 0x00000031 );
		OSD_L9A0_WrFL(osd_frc_if_cfg );
	}

	/* DO chip revision specific initialization */
	g_fbdev_l9_hw_func.L9_InitHWCtx( );

	/* raxis.lim (2011/12/14) 
	 * ajudst GPU clock after initializaint L9 HW Ctx 
	 * default clock of GPU is fixed to 320MHZ. it should be increased to run some heavy application.
	 */
#if 1
	g_fbdev_l9_hw_func.L9_SetGPUClk( FBDEV_L9_HW_GPU_CLK_400MHZ );
#else
	/* configure GPU clock to 400 MHZ */
	UINT32 clkval;
	CTOP_CTRL_L9B_RdFL(ctr01_reg_clk_div_sel);
	CTOP_CTRL_L9B_Rd01(ctr01_reg_clk_div_sel, gpuclk_sel, clkval );
	CTOP_CTRL_L9B_Wr01(ctr01_reg_clk_div_sel, gpuclk_sel, 0x3 /* 400 MHz */ );
	CTOP_CTRL_L9B_WrFL(ctr01_reg_clk_div_sel);
printk("[fb] clk val = 0x%x -> 0x%x\n", clkval, 0x3 );

	CTOP_CTRL_L9B_RdFL(ctr29_reg_swrst);
	CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst, gpu_high_speed, 0x0 /* default */ );
	CTOP_CTRL_L9B_WrFL(ctr29_reg_swrst);
#endif

	/* make initial zorder */

	ret = RET_OK; /* all work done */
func_exit:
	return ret;
}

/** de-initial OSD IP HW and register
 *
 * @param
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int FBDEV_L9_ShutdownHW	(void)
{
	int ret = RET_OK;

	iounmap((void *)g_fbdev_l9_reg);

	return ret;
}

/** make initial OSD zorder. 
 *
 *	@return none
 *	@note this function controls osd_layer_mux register
 */
void FBDEV_L9_InitOSDZOrder ( void )
{
	LX_FBDEV_ZLIST_T	zlist;

	/* raxis.lim (2011/11/15) -- change the default zorder based on L9B1 
	 * L9 dones't support OSD2 any more since its core circuit is used as L9B1 metal revision.
	 * we should be careful of handling the default layer order.
	 * the first topmost layer should be OSD2 (disabled OSD layer).
	 * for more information, please contact to ±è¿õÇö
	 */
	zlist.path		= LX_FBDEV_PATH_ALL;
	zlist.order[0]	= LX_FBDEV_ZLIST_OSD0;	/* top most . H/W default */
	zlist.order[1]	= LX_FBDEV_ZLIST_OSD1;	/* center   . H/W default */
	zlist.order[2]	= LX_FBDEV_ZLIST_VIDEO;	/* bottom 	. H/W default */

	FBDEV_L9_SetZList( &zlist );
}


/** @} */

