/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2010 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 


/** @file
 *
 *  interrupt driver file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.08
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_kapi.h"
#include "be_def.h"
#include "be_cfg.h"
#include "ipc_def.h"
#include "int_drv.h"
#include "int_hal.h"
#include "ipc_drv.h"

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
extern void FWI_CPU_ISR_FROM_MCU(unsigned long temp);
extern void FWI_CPU_ACK_FROM_MCU(unsigned long temp);
extern void FWI_CPU_WDG_FROM_MCU(unsigned long temp);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static irqreturn_t DMA_Interrupt(int irq, void *dev_id, struct pt_regs *regs);
static irqreturn_t IPC_Interrupt(int irq, void *dev_id, struct pt_regs *regs);
static void        INT_DMA_Handler(void);
static void        INT_IPC_Handler(void);

static DECLARE_TASKLET(Video_WDG_tasklet,	FWI_CPU_WDG_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_IPC_tasklet,	FWI_CPU_ISR_FROM_MCU,  0UL);
static DECLARE_TASKLET(VIdeo_ACK_tasklet,	FWI_CPU_ACK_FROM_MCU,  0UL);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize Interrupt
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_INT_Init(void)
{
	int ret = RET_OK;
	int num_be_irq_0 = 0;
	int num_be_irq_1 = 0;

	num_be_irq_0 = H13_IRQ_BVE0;
	num_be_irq_1 = H13_IRQ_BVE1;

	if (request_irq(num_be_irq_0,(irq_handler_t)IPC_Interrupt,0,"BE2IPC", NULL)) {
		BE_ERROR("request_irq 0 is failed\n");
		ret = RET_ERROR;
	}
#if 0 // check BVE1 interrupt (purpose, usage)
	if (request_irq(num_be_irq_1,(irq_handler_t)DMA_Interrupt,0,"BE2DMA", NULL)) {
		BE_ERROR("request_irq 1 is failed\n");
		ret = RET_ERROR;
	}
#endif

	INT_HAL_Init();

	return ret;
}
    
static irqreturn_t DMA_Interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	INT_DMA_Handler();

	return IRQ_HANDLED;
}

static irqreturn_t IPC_Interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	INT_IPC_Handler();

	return IRQ_HANDLED;
}

static void INT_DMA_Handler(void)
{
	BE_DEBUG("%s\n", __F__);
}

static void INT_IPC_Handler(void)
{
	int ret;
	UINT32 intrStatus;

	ret = INT_HAL_GetStatus(INT_SWI, &intrStatus);
	if(intrStatus & SWI_TYPE_IPC)
	{
		tasklet_schedule(&Video_IPC_tasklet);
	}
	if(intrStatus & SWI_TYPE_ACK)
	{
		tasklet_schedule(&VIdeo_ACK_tasklet);
	}
	BE_DEBUG("SWI : status 0x%x\n", intrStatus);

	// clear interrupt
	if(intrStatus) INT_HAL_ClearStatus(INT_SWI, &intrStatus);

	ret = INT_HAL_GetStatus(INT_HWI, &intrStatus);

	if(intrStatus & (1 << CPU_INT_WDG))
	{
		tasklet_schedule(&Video_WDG_tasklet);
	}
	if(intrStatus & (1 << CPU_INT_DMA))
	{
	}
#if 0	
	if(intrStatus & (1 << CPU_INT_LED))
	{
	}
	if(intrStatus & (1 << CPU_INT_DPPA))
	{
	}
	if(intrStatus & (1 << CPU_INT_SRE))
	{
	}
	if(intrStatus & (1 << CPU_INT_LRX))
	{
	}
	if(intrStatus & (1 << CPU_INT_DVO))
	{
	}
	if(intrStatus & (1 << CPU_INT_DVI))
	{
	}
	if(intrStatus & (1 << CPU_INT_H3D0))
	{
	}
	if(intrStatus & (1 << CPU_INT_H3D1))
	{
	}
#endif

	BE_DEBUG("HWI : status 0x%x\n", intrStatus);
	// clear interrupt
	if(intrStatus) INT_HAL_ClearStatus(INT_HWI, &intrStatus);
}

