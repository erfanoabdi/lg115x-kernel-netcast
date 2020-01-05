
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
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>			/**< printk() */
#include <linux/slab.h>			 	/**< kmalloc() */
#include <linux/fs.h> 				/**< everything\ldots{} */
#include <linux/types.h>		 	/**< size_t */
#include <linux/fcntl.h>			/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>			/**< For request_region, check_region etc */
#include <asm/io.h>					/**< For ioremap_nocache */
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>
#include <linux/irq.h>

#include "gfx_impl.h"
#include "gfx_reg_l9a0.h"
#include "l9/base_addr_sw_l9.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	GFX_REG_BASE_ADDR 		0xc0027000
#define	GFX_REG_SIZE 			0x1DF

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void		GFX_L9_stop(void);
extern int 		GFX_L9_RunFlushCommand(void);
extern int 		GFX_L9_RunStartCommand(void);
extern int 		GFX_L9_PauseCommand(void);
extern int		GFX_L9_ResumeCommand(void);
extern int		GFX_L9_StopCommand(void);
extern int		GFX_L9_SwResetCommand(void);
extern void		GFX_L9_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue);
extern BOOLEAN	GFX_L9_IsGfxIdle(void);
extern void		GFX_L9_GetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_L9_SetOperationStatus(GFX_CMD_OP_T *operate);
extern void		GFX_L9_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port);
extern void		GFX_L9_SetInputConfigure(GFX_PORT_CONFIGURE_T *port);
extern void		GFX_L9_SetBlendingOut(GFX_ENUM_OUT_T type);
extern void		GFX_L9_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_L9_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend);
extern void		GFX_L9_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_L9_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port);
extern void		GFX_L9_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler);
extern void		GFX_L9_SetInterruptMode(UINT32 uiMode);
extern void		GFX_L9_SetAckMode(UINT32 *mode);
extern void		GFX_L9_GetAckMode(UINT32 *mode);
extern int		GFX_L9_SetCLUT(int port, int size , UINT32 *data);
extern void		GFX_L9_SetCommandDelayReg(UINT16 delay);
extern UINT16 	GFX_L9_GetCommandDelayReg(void);
extern void 	GFX_L9_SetRegister(UINT32 addr, UINT32 val);
extern UINT32 	GFX_L9_GetRegister(UINT32 addr);
extern void		GFX_L9_DumpRegister(void);
extern int 		GFX_L9_RunSuspend(void);
extern int 		GFX_L9_RunResume(void);

extern void		GFX_L9_InitScaler(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile GFX_L9A0_REG_T*	g_gfx_reg_l9a0;
GFX_L9A0_REG_T*				g_gfx_reg_l9a0_cache;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
const LX_GFX_CFG_T*	GFX_L9_GetCfg		(void);
int 				GFX_L9_InitHW		(void);
int 				GFX_L9_ShutdownHW	(void);
irqreturn_t 		GFX_L9_ISRHandler	(int irq, void *dev_id, struct pt_regs *regs);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
const static	GFX_HAL_T		g_gfx_hal_l9 =
{
	.GetCfg					= GFX_L9_GetCfg,
	.InitHW					= GFX_L9_InitHW,
	.ShutdownHW				= GFX_L9_ShutdownHW,
	.RunSuspend				= GFX_L9_RunSuspend,
	.RunResume				= GFX_L9_RunResume,

	.RunFlushCommand		= GFX_L9_RunFlushCommand,
	.RunStartCommand		= GFX_L9_RunStartCommand,
	.RunPauseCommand		= GFX_L9_PauseCommand,
	.RunResumeCommand		= GFX_L9_ResumeCommand,
	.RunStopCommand			= GFX_L9_StopCommand,
	.RunSwResetCommand		= GFX_L9_SwResetCommand,

	.GetComQueueStatus		= GFX_L9_GetComQueueStatus,

	.GetOperationStatus		= GFX_L9_GetOperationStatus,
	.SetOperationStatus		= GFX_L9_SetOperationStatus,
	.GetInputConfigure		= GFX_L9_GetInputConfigure,
	.SetInputConfigure		= GFX_L9_SetInputConfigure,
	.GetBlendConfigure		= GFX_L9_GetBlendConfigure,
	.SetBlendConfigure		= GFX_L9_SetBlendConfigure,
	.SetBlendingOut			= GFX_L9_SetBlendingOut,
	.GetOutputConfigure		= GFX_L9_GetOutputConfigure,
	.SetOutputConfigure		= GFX_L9_SetOutputConfigure,
	.SetScalerConfigure		= GFX_L9_SetScalerConfigure,
	.SetCLUT				= GFX_L9_SetCLUT,
	.SetCommandDelayReg		= GFX_L9_SetCommandDelayReg,
	.GetCommandDelayReg		= GFX_L9_GetCommandDelayReg,

	.IsGfxIdle				= GFX_L9_IsGfxIdle,

	.SetRegister			= GFX_L9_SetRegister,
	.GetRegister			= GFX_L9_GetRegister,
	.DumpRegister			= GFX_L9_DumpRegister,
};

static	LX_GFX_CFG_T 		g_gfx_cfg_l9 =
{
    .b_hw_scaler 				= TRUE,
    .surface_blit_cmd_delay 	= 0x0,//0x40,
    .screen_blit_cmd_delay  	= 0x0,//0x20,
	.sync_wait_timeout			= 20, //16,   2011/11/10 -- increase wait time to reduce the possibilities for sync timeout.
	.sync_fail_retry_count		= 2,

	.hw_limit = {
		.max_surface_width		= 8191,		/* L9 has 13 bit width field  */
		.max_surface_stride		= 32767,	/* L9 has 15 bit stride field */
		.min_scaler_input_width = 12,		/* L9 doesn't strech below input width <= 12 */
	},
};

/*========================================================================================
    Implementation Group
========================================================================================*/

/** this function is called before any GFX H/W initialization
 *
 */
void	GFX_L9_InitHAL( GFX_HAL_T*	hal )
{
	memcpy( hal, &g_gfx_hal_l9, sizeof(GFX_HAL_T));

	/* set L9 workaround list */
	switch( lx_chip_rev() )
	{
		case LX_CHIP_REV(L9,A0):
		case LX_CHIP_REV(L9,A1):
		{
			g_gfx_cfg_l9.workaround.bad_dst_addr_stuck		= 1;
			g_gfx_cfg_l9.workaround.scaler_read_buf_stuck	= 1;
			g_gfx_cfg_l9.workaround.srcblt_op_stuck			= 0;
			g_gfx_cfg_l9.workaround.write_op_stuck			= 0;
		}
		break;

		case LX_CHIP_REV(L9,B0):
		case LX_CHIP_REV(L9,B1):
		case LX_CHIP_REV(L9,B2):
		default:
		{
			g_gfx_cfg_l9.workaround.bad_dst_addr_stuck		= 0;
			g_gfx_cfg_l9.workaround.scaler_read_buf_stuck	= 0;
			g_gfx_cfg_l9.workaround.srcblt_op_stuck			= 1;
			g_gfx_cfg_l9.workaround.write_op_stuck			= 1;
		}
		break;
	}
}

/** get L9 specific configuration
 *
 *  @return LX_GFX_CFG_T
 */
const LX_GFX_CFG_T*   GFX_L9_GetCfg(void)
{
    return &g_gfx_cfg_l9;
}


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/

/** GFX interrupt handler
 *
 */
irqreturn_t GFX_L9_ISRHandler(int irq, void *dev_id, struct pt_regs *regs)
{
//	if ( GFX_IsGfxIdle() )
	{
//		GFX_PRINT("#### GFX ISR - IDLE OK ####\n");
		GFX_WakeupWaitSync();
	}

	g_gfx_reg_l9a0->gfx_intr_clear.gfx_intr_clear = 0x1;
	GFX_PRINT("#### GFX ISR ####\n");

	return IRQ_HANDLED;
}

/** initialize L9 hardware
*
* @return RET_OK when success, RET_ERROR otherwise
*/

int GFX_L9_InitHW(void)
{
	LX_ADDR_SW_CFG_T	addr_sw_cfg;

	/* do ioremap */
	g_gfx_reg_l9a0 =(GFX_L9A0_REG_T *)ioremap( gpGfxRegCfg->reg_base_addr, GFX_REG_SIZE);
	GFX_CHECK_ERROR( g_gfx_reg_l9a0 == NULL, return RET_ERROR, "can't alloc memory for regs\n");

	g_gfx_reg_l9a0_cache = (GFX_L9A0_REG_T *)OS_Malloc( gpGfxRegCfg->reg_size );
	GFX_CHECK_ERROR( g_gfx_reg_l9a0_cache == NULL, return RET_ERROR, "out of memory\n");

	memset( g_gfx_reg_l9a0_cache, 0x0, gpGfxRegCfg->reg_size );

	/* initialize L9 memory address switch */
	BASE_L9_GetAddrSwCfg( ADDR_SW_CFG_GFX, &addr_sw_cfg );	

#if 1
	g_gfx_reg_l9a0->sw_de_sav		= addr_sw_cfg.de_sav;
	g_gfx_reg_l9a0->sw_cpu_gpu		= addr_sw_cfg.cpu_gpu;
	g_gfx_reg_l9a0->sw_cpu_shadow	= addr_sw_cfg.cpu_shadow;
#else
	GFX_Wr( sw_de_sav, 		addr_sw_cfg.de_sav );		
	GFX_Wr( sw_cpu_gpu, 	addr_sw_cfg.cpu_gpu );
	GFX_Wr( sw_cpu_shadow, 	addr_sw_cfg.cpu_shadow );

	GFX_WrFL( sw_de_sav );
	GFX_WrFL( sw_cpu_gpu );
	GFX_WrFL( sw_cpu_shadow );
#endif

	/* register GFX interrupt handler */
	GFX_CHECK_ERROR( request_irq( gpGfxRegCfg->irq_num, (irq_handler_t)GFX_L9_ISRHandler, 0, "gfx_irq", NULL), /* nop */, "request irq failed\n" );

	g_gfx_reg_l9a0->gfx_intr_ctrl.intr_gen_mode = 0;	// batch command finish
	g_gfx_reg_l9a0->gfx_intr_ctrl.intr_en		= 1;	// interrupt enable

	/* raxis.lim (2011/04/20)
	 * disable GFX scaler at the start time. GFX scaler control should be done for each GFX operation
	 */
//	g_gfx_reg_l9a0->scaler_bypass.scaler_bypass = 1;

//	GFX_L9_InitScaler( );

	return 0;
}

/** shutdown L9 hardware 
 *
 * @return RET_OK when success, RET_ERROR otherwise
 */
int 			GFX_L9_ShutdownHW	(void)
{
	g_gfx_reg_l9a0->gfx_intr_ctrl.intr_en = 0;	// interrupt disable

	/* [TODO] more cleanup !!! */

    iounmap((void *)g_gfx_reg_l9a0);

	return 0;
}

/** @} */

