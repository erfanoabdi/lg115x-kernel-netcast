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
 *  main driver implementation for lgbus device.
 *	lgbus device will teach you how to make device driver with new platform.
 *
 *  author		hwanwook.lee (hwanwook.lee@lge.com)
 *              bongrae.cho (bongrae.cho@lge.com)
 *  version		1.0
 *  date		2012.11.10
 *  note		Additional information.
 *
 *  @addtogroup lg115x_lgbus
 *	@{
 */

/*=========================================================================================*
| Header files																			   
*==========================================================================================*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */

#include <linux/interrupt.h>	/** irqreturn_t */
#include <linux/irq.h>		/** platform interrupt */

#include "lgbus.h"
#include "lgbus_kapi.h"


/*=========================================================================================*
| Symbolic Constant																			   
*==========================================================================================*/


/*=========================================================================================*
| Type definitions																			   
*==========================================================================================*/


/*=========================================================================================*
| Function Prototype
*==========================================================================================*/


/*=========================================================================================*
| Global variables																			   
*==========================================================================================*/
extern	lgbus_ctrl_t			lgbus_ctrl;
extern	mon_req_info_t			req_info;

extern int lgbus_open(void);
extern int lgbus_close(void);

/*=========================================================================================*
| Function Definitions																			   
*==========================================================================================*/
static void copy_from_mon_result(LX_LGBUS_REPLY_T * dst, bus_mon_reply_t * src)
{
	//fixme: check struct-members between LX_LGBUS_REPLY_T and bus_mon_reply_t

	if (sizeof(LX_LGBUS_REPLY_T) != sizeof(bus_mon_reply_t))
	{
		printk("Opppsss LGBUS: error copy-result\n");

		return;
	}

	memcpy(dst, src, sizeof(LX_LGBUS_REPLY_T));
}

void lgbus_wrap_control_open(void)
{
	lgbus_open();
}
EXPORT_SYMBOL(lgbus_wrap_control_open);

void lgbus_wrap_control_close(void)
{
	lgbus_close();
}
EXPORT_SYMBOL(lgbus_wrap_control_close);


int lgbus_wrap_control_init(LX_LGBUS_REQ_INFO_T arg)
{
	int ret = 0;

	/*
	; get monitoring request information from application.
	*/
	req_info.chip_rev = arg.chip_rev;
	req_info.bus_chk_id = arg.bus_chk_id;
	req_info.mnt_chk_blks = arg.mnt_chk_blks;
	req_info.mon_freq_per_second= arg.mon_freq_per_second;

	/*
	; initialize regiater base address for each block, 
	; and kernel syncronization(semaphore).
	*/
	lgbus_ctrl.func.init(req_info);
	
	/*
	; timer setting in cpu_main bw monitor.
	; we just use timer in cpu_main monitoring block.
	*/		
    lgbus_ctrl.func.settmr(req_info.mon_freq_per_second);

	return ret;
}
EXPORT_SYMBOL(lgbus_wrap_control_init);

int lgbus_wrap_control_stop(void)
{
	lgbus_ctrl.func.stop();

	return 0;
}
EXPORT_SYMBOL(lgbus_wrap_control_stop);

int lgbus_wrap_control_read(LX_LGBUS_REPLY_T * result)
{
	lgbus_ctrl.func.start();

	down(&(lgbus_ctrl.sem));

	lgbus_ctrl.func.read();

	copy_from_mon_result(result, &(lgbus_ctrl.mon_info));

	return 0;
}
EXPORT_SYMBOL(lgbus_wrap_control_read);


