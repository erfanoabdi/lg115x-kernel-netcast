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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.02.17
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>

#include "base_types.h"
#include "os_util.h"

#include "de_ver_def.h"

#include "de_kapi.h"
#include "de_def.h"

#include "de_int_def.h"
#include "de_hal_def.h"
#include "de_ipc_def.h"
#include "de_ipc.h"
#include "de_int.h"
#include "de_hal.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	int (*cb_func)(void);
} DE_VSYNC_CB;
DE_VSYNC_CB vsync_cb;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static DECLARE_TASKLET(Video_WDG_tasklet,	VIDEO_CPU_WDG_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_IPC_tasklet,	VIDEO_CPU_ISR_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_DMA_tasklet,	VIDEO_CPU_DMA_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_JPG_tasklet,	VIDEO_CPU_JPG_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_USB_tasklet,	VIDEO_CPU_USB_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_WEL_tasklet,	VIDEO_CPU_WEL_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_WER_tasklet,	VIDEO_CPU_WER_FROM_MCU,  0UL);
static DECLARE_TASKLET(Video_VSYNC_tasklet, VIDEO_CPU_VSYNC_Tasklet, 0UL);

static DECLARE_WAIT_QUEUE_HEAD(wqVsync);
static int de_vsync_event_wakeup;

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt handler which is comming from MCU
 */
void DE_IPC_Handler(void)
{
	UINT32 ipcStatus;

	DE_HAL_GetIPCIntrStatus(VIDEO_IPC_CPU, &ipcStatus);
	if (GET_CM(ipcStatus, VIDEO_WDG_INTERRUPT_ARM_MASK)) {
		DE_HAL_ClearWDGStatus();
		tasklet_schedule(&Video_WDG_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_IPC_INTERRUPT_ARM_MASK)) {
		DE_HAL_ClearIPCStatus();
		tasklet_schedule(&Video_IPC_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_DMA_INTERRUPT_ARM_MASK)) {
		DE_HAL_ClearDMAStatus();
		tasklet_schedule(&Video_DMA_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_JPG_INTERRUPT_ARM_MASK)) {
		DE_HAL_ClearJPGStatus();
		tasklet_schedule(&Video_JPG_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_USB_INTERRUPT_ARM_MASK)) {
		DE_HAL_ClearUSBStatus();
		tasklet_schedule(&Video_USB_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_WEL_INTERRUPT_ARM_MASK)) {
		DE_HAL_ClearWELStatus();
		tasklet_schedule(&Video_WEL_tasklet);
	}
	if (GET_CM(ipcStatus, VIDEO_WER_INTERRUPT_ARM_MASK)) {
		DE_HAL_ClearWERStatus();
		tasklet_schedule(&Video_WER_tasklet);
	}
}

irqreturn_t DE_IPC_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
    DE_IPC_Handler();

	return IRQ_HANDLED;
}

irqreturn_t DE_VSYNC_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
    DE_VSYNC_Handler();

	return IRQ_HANDLED;
}

void DE_VSYNC_Handler(void)
{
	do {
		if (!DE_HAL_CheckIrq4Vsync()) break;
		tasklet_schedule(&Video_VSYNC_tasklet);
	} while (0);
}

void DE_VSYNC_Register(int (*func)(void))
{
	vsync_cb.cb_func = func;
}
EXPORT_SYMBOL(DE_VSYNC_Register);

void DE_VSYNC_Callback(void)
{
	vsync_cb.cb_func();
}

void VIDEO_CPU_VSYNC_Tasklet(unsigned long temp)
{
	DE_VSYNC_WakeUp();
	DE_VSYNC_Callback();
}

void DE_VSYNC_WakeUp(void)
{
	if (de_vsync_event_wakeup < 0) de_vsync_event_wakeup++;
	wake_up_interruptible(&wqVsync);
}

int DE_VSYNC_WaitTimeOut(int timeout)
{
	if (timeout < 0) {
		de_vsync_event_wakeup = timeout;
		wait_event_interruptible(wqVsync, !de_vsync_event_wakeup);
	} else {
		de_vsync_event_wakeup = -1;
		wait_event_interruptible_timeout(wqVsync, !de_vsync_event_wakeup, (long)timeout);
	}
	return RET_OK;
}
/** @} */
