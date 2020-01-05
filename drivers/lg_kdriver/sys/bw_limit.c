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


#include <linux/kernel.h>		 /**< FBDEV_WARN() */
#include <linux/timer.h>
#include <linux/string.h>
#include <linux/version.h>
#include <asm/io.h>

#define	BW_LIMIT_REG	0xFD300164
#define	BW_LIMIT_DURATION	60

struct timer_list timerTrigger;
static unsigned long timerOfTimeout;
static unsigned int doingCheckLimitBW;
static unsigned int ctop_cpu_ddr1BW;

/*
 * gVdecEmmcSleepTime variable is defined in kernel/drivers/mmc/card/block.c .
 * If you have compile error at here, please build again the kernel after you update it.
 */
#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,39)
extern unsigned int gVdecEmmcSleepTime;
#else
unsigned int gVdecEmmcSleepTime;
#endif

/*
// following register will be set at lxboot
D.S ASD:0xfd300240 %LONG 0x30000150
D.S ASD:0xfd300248 %LONG 0x00010140
D.S ASD:0xfd30024C %LONG 0x30000150
D.S ASD:0xfd300254 %LONG 0x00010140
*/

static void timer_func(unsigned long arg)
{
	memset((void *)ctop_cpu_ddr1BW, 0x0 , 0x4);
	gVdecEmmcSleepTime = 0;
//	printk("\n\n%s : %x\n\n", __FUNCTION__, *(unsigned int *)ctop_cpu_ddr1BW);
}

void BW_LimitCtrl_Init(void)
{
	/////////////////////////////
	// add this code initial part
	timerOfTimeout = jiffies + BW_LIMIT_DURATION*HZ;
	doingCheckLimitBW = 1;

	ctop_cpu_ddr1BW = (unsigned long)ioremap(BW_LIMIT_REG , 0x10);
//	printk("\n\n%s : %lu\n\n", __FUNCTION__, timerOfTimeout);
}

void BW_LimitCtrl(int bSet)
{
	/////////////////////////////
	// add this code triggering part
	if((timerOfTimeout > jiffies ) && ( doingCheckLimitBW == 1 ) && bSet)
	{
		if(timerOfTimeout - jiffies < BW_LIMIT_DURATION*HZ)
		{
			*(unsigned int *)ctop_cpu_ddr1BW = 0x120;
	//		printk("\n\n%s : %x\n\n", __FUNCTION__, *(unsigned int *) ctop_cpu_ddr1BW);

			init_timer(&timerTrigger);
			timerTrigger.expires = timerOfTimeout;
			timerTrigger.function = timer_func;
			timerTrigger.data = 0;
			add_timer(&timerTrigger);
			doingCheckLimitBW = 0;
			gVdecEmmcSleepTime = 20;	// 15ms
		}
		else
			doingCheckLimitBW = 0;
	}
	else if(timerOfTimeout < jiffies )
		doingCheckLimitBW = 0;
}


