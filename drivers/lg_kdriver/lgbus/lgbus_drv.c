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

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_LGBUS_DEVICE_READ_WRITE_FOPS
#define SUPPORT_LGBUS_UNLOCKED_IOCTL

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/version.h>

#include "lgbus_drv.h"
#include "lgbus_proc.h"
#include "lgbus_kapi.h"

#include "os_util.h"
#include "base_device.h"

#include "../sys/sys_regs.h"	//for CTOP CTRL Reg. map
//#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/


/**
 *	main control block for lgbus device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
// END of command device

}
LGBUS_DEVICE_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void lgbus_wrap_control_open(void);
extern void lgbus_wrap_control_close(void);
extern int lgbus_wrap_control_init(LX_LGBUS_REQ_INFO_T arg);
extern int lgbus_wrap_control_stop(void);
extern int lgbus_wrap_control_read(LX_LGBUS_REPLY_T * result);


extern irqreturn_t lgbus_isr(int irq, void *dev_id, struct pt_regs *regs);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		LGBUS_Init(void);
void	LGBUS_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_lgbus_debug_fd;
int 	g_lgbus_major = LGBUS_MAJOR;
int 	g_lgbus_minor = LGBUS_MINOR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      LGBUS_Open(struct inode *, struct file *);
static int      LGBUS_Close(struct inode *, struct file *);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_LGBUS_UNLOCKED_IOCTL)
static int 		LGBUS_Ioctl 	(struct inode*, struct file *, UINT32, ULONG );
#else
static long		LGBUS_Ioctl 	(struct file *, UINT32, ULONG );
#endif
#ifdef SUPPORT_LGBUS_DEVICE_READ_WRITE_FOPS
static ssize_t  LGBUS_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  LGBUS_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for lgbus device
*/
static LGBUS_DEVICE_T*		g_lgbus_device;

/**
 * file I/O description for lgbus device
 *
*/
static struct file_operations g_lgbus_fops =
{
	.open 	= LGBUS_Open,
	.release= LGBUS_Close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_LGBUS_UNLOCKED_IOCTL)
			.ioctl	= LGBUS_Ioctl,
#else
	.unlocked_ioctl	= LGBUS_Ioctl,
#endif	
#ifdef SUPPORT_LGBUS_DEVICE_READ_WRITE_FOPS
	.read 	= LGBUS_Read,
	.write 	= LGBUS_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

/*========================================================================================
	Implementation Group
========================================================================================*/
void LGBUS_PreInit(void)
{
	/* TODO: */
}


int LGBUS_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for lgbus device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_lgbus_debug_fd = DBG_OPEN( LGBUS_MODULE );

    if ( g_lgbus_debug_fd < 0 )
    {
        printk("[mon] can't get debug handle\n");
		g_lgbus_debug_fd = g_global_debug_fd;
    }
    else
	{
		OS_DEBUG_EnableModule ( g_lgbus_debug_fd );
		
		//OS_DEBUG_EnableModuleByIndex ( g_lgbus_debug_fd, 0, DBG_COLOR_NONE );
		//OS_DEBUG_EnableModuleByIndex ( g_lgbus_debug_fd, 1, DBG_COLOR_NONE );
		//OS_DEBUG_EnableModuleByIndex ( g_lgbus_debug_fd, 2, DBG_COLOR_NONE );
		OS_DEBUG_EnableModuleByIndex ( g_lgbus_debug_fd, 3, DBG_COLOR_RED );
	}
	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
	g_lgbus_device = (LGBUS_DEVICE_T*)OS_KMalloc( sizeof(LGBUS_DEVICE_T)*LGBUS_MAX_DEVICE );

	if ( NULL == g_lgbus_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(LGBUS_DEVICE_T)* LGBUS_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_lgbus_device, 0x0, sizeof(LGBUS_DEVICE_T)* LGBUS_MAX_DEVICE );

	if (g_lgbus_major)
	{
		dev = MKDEV( g_lgbus_major, g_lgbus_minor );
		err = register_chrdev_region(dev, LGBUS_MAX_DEVICE, LGBUS_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_lgbus_minor, LGBUS_MAX_DEVICE, LGBUS_MODULE );
		g_lgbus_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register lgbus device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for (i = 0; i < LGBUS_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_lgbus_major, g_lgbus_minor+i );
		cdev_init( &(g_lgbus_device[i].cdev), &g_lgbus_fops );
		g_lgbus_device[i].devno		= dev;
		g_lgbus_device[i].cdev.owner = THIS_MODULE;
		g_lgbus_device[i].cdev.ops   = &g_lgbus_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_lgbus_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding lgbus device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_lgbus_device[i].devno, "%s%d", LGBUS_MODULE, i );
	}


    lgbus_wrap_control_open();

	/*
	; install interrupt handler. 
	*/
	if (request_irq(H13_IRQ_LBUS, (irq_handler_t)lgbus_isr,IRQF_SHARED,"LGBUS_L", g_lgbus_device)) 
	{
    	LGBUS_PRINT("request_irq in %s is failed\n", __FUNCTION__);
    }

	/*
	; install interrupt handler. 
	*/
	if (request_irq(H13_IRQ_GBUS, (irq_handler_t)lgbus_isr,IRQF_SHARED,"LGBUS_G", g_lgbus_device)) 
	{
    	LGBUS_PRINT("request_irq in %s is failed\n", __FUNCTION__);
    }
    
    LGBUS_proc_init();

	LGBUS_PRINT("lgbus device initialized\n");

	return 0;
}

void LGBUS_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_lgbus_major, g_lgbus_minor );
    
    LGBUS_proc_cleanup();

	free_irq (H13_IRQ_LBUS, g_lgbus_device);
	free_irq (H13_IRQ_GBUS, g_lgbus_device);

    lgbus_wrap_control_close();

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<LGBUS_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_lgbus_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, LGBUS_MAX_DEVICE );

	OS_Free( g_lgbus_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for lgbus device
 *
 */
static int
LGBUS_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    LGBUS_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, LGBUS_DEVICE_T, cdev);

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    LGBUS_PRINT("device opened (%d:%d)\n", major, minor );

	lgbus_wrap_control_open();

    return 0;
}

/**
 * release handler for lgbus device
 *
 */
static int
LGBUS_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    LGBUS_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, LGBUS_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    LGBUS_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for lgbus device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_LGBUS_UNLOCKED_IOCTL)
static int LGBUS_Ioctl  ( struct inode* inode, struct file *filp, UINT32 cmd, ULONG arg )
#else
static long LGBUS_Ioctl  ( struct file* filp, UINT32 cmd, ULONG arg )
#endif
{
    int err = 0, ret = 0;

    LGBUS_DEVICE_T*	my_dev;
    struct cdev*		cdev;

	/*
	 * get current lgbus device object
	 */

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(SUPPORT_LGBUS_UNLOCKED_IOCTL)
		cdev	= inode->i_cdev;
		my_dev	= container_of ( cdev, LGBUS_DEVICE_T, cdev);
#else
		my_dev	= (LGBUS_DEVICE_T*)filp->private_data;
		cdev	= &my_dev->cdev;
#endif

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != LGBUS_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > LGBUS_IOC_MAXNR)
    {
    	DBG_PRINT_WARNING("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
    	return -ENOTTY;
    }

	/* TODO : add some check routine for your device */

    /*
     * check if user memory is valid or not.
     * if memory can't be accessed from kernel, return error (-EFAULT)
     */
    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
    if (err)
    {
    	DBG_PRINT_WARNING("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
    													_IOC_NR(cmd),
    													(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
    													(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
    													(void*)arg );
        return -EFAULT;
	}

	LGBUS_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

    // set APB clk select to 50MHz(1), 25MHz(2), doesn't work at 100MHz(0) async arbitration H/W bug
	if (lx_chip_rev() == LX_CHIP_REV(H13, B0))
	{
        CTOP_CTRL_H13B0_RdFL(ctr01);    
        CTOP_CTRL_H13B0_Wr01(ctr01, apb_clk_sel, 1);
        CTOP_CTRL_H13B0_WrFL(ctr01);
	}
	switch(cmd)
	{
		case LGBUS_IOW_INIT:
		{
			LX_LGBUS_REQ_INFO_T req_info;

			err = copy_from_user((void *)&req_info, (void __user *)arg, sizeof(LX_LGBUS_REQ_INFO_T));
			LGBUS_CHECK_CODE(err > 0, break, "copy from error\n");
			
			err = lgbus_wrap_control_init(req_info);
			LGBUS_CHECK_CODE(err < 0, break, "lgbus init error\n");
		}
		break;

		case LGBUS_IO_STOP:
		{
			err = lgbus_wrap_control_stop();
			LGBUS_CHECK_CODE(err < 0, break, "lgbus stop error\n");
		}
		break;

		case LGBUS_IOR_MON_READ:
		{
			LX_LGBUS_REPLY_T * result;

			result = (LX_LGBUS_REPLY_T *)kmalloc(sizeof(LX_LGBUS_REPLY_T), GFP_KERNEL);
			LGBUS_CHECK_CODE(result == NULL, break, "error - lgbus kmalloc\n"); 			

			
			err = lgbus_wrap_control_read(result);
			LGBUS_CHECK_CODE(err < 0, do {kfree(result); break;} while(0), "lgbus read error\n");

			err = copy_to_user((void __user *)arg, (void *)result, sizeof(LX_LGBUS_REPLY_T));
			LGBUS_CHECK_CODE(err > 0, do {kfree(result); break;} while(0), "copy to error\n");

			kfree(result);
		}
		break;

	    default:
	    {
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
    }

    // set APB clk select to 100MHz(0) for normal operation, It's workaround of async arbitration H/W bug
	if (lx_chip_rev() == LX_CHIP_REV(H13, B0))
	{
        CTOP_CTRL_H13B0_RdFL(ctr01);    
        CTOP_CTRL_H13B0_Wr01(ctr01, apb_clk_sel, 0);
        CTOP_CTRL_H13B0_WrFL(ctr01);
	}

    return ret;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",LGBUS_Init);
#else
module_init(LGBUS_Init);
#endif
module_exit(LGBUS_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

