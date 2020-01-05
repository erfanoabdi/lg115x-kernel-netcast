
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
 *  main driver implementation for gpio device.
 *	gpio device will teach you how to make device driver with new platform.
 *
 *  author		ingyu.yang (ingyu.yang@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_gpio
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_GPIO_DEVICE_READ_WRITE_FOPS
#undef	GPIO_DRV_PRINT_ENABLE
//#define GPIO_DRV_PRINT_ENABLE
//static void Debug_GPIO_Print(void);

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include "mach/platform.h"
#include <asm/uaccess.h>
#include "os_util.h"
#include "base_device.h"
#include "gpio_drv.h"
#include "gpio_reg.h"
#include "gpio_core.h"



/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define GPIO_COPY_FROM_USER(d,s,l) 							\
		do {												\
			if (copy_from_user((void*)d, (void *)s, l)) {	\
				GPIO_ERROR("ioctl: copy_from_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)

#define GPIO_COPY_TO_USER(d,s,l) 							\
		do {												\
			if (copy_to_user((void*)d, (void *)s, l)) { 	\
				GPIO_ERROR("ioctl: copy_to_user\n");		\
				return -EFAULT; 							\
			}												\
		} while(0)



/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	main control block for gpio device.
 *	each minor device has unique control block
 *
 */
typedef struct GPIO_DEVICE_t
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
// END of command device

// BEGIN of device specific data
	OS_SEM_T				mutex;
// END of device specific data
}
GPIO_DEVICE_T;


#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool			is_suspended;
}GPIO_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	GPIO_PROC_Init(void);
extern	void	GPIO_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		GPIO_Init(void);
void	GPIO_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_gpio_debug_fd;
int 	g_gpio_major = GPIO_MAJOR;
int 	g_gpio_minor = GPIO_MINOR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      GPIO_Open(struct inode *, struct file *);
static int      GPIO_Close(struct inode *, struct file *);
static long		GPIO_Ioctl (struct file *file, unsigned int cmd, unsigned long arg);

#ifdef SUPPORT_GPIO_DEVICE_READ_WRITE_FOPS
static ssize_t  GPIO_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  GPIO_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for gpio device
*/
static GPIO_DEVICE_T*		g_gpio_device;

/**
 * file I/O description for gpio device
 *
*/
static struct file_operations g_gpio_fops =
{
	.open 	= GPIO_Open,
	.release= GPIO_Close,
	.unlocked_ioctl	= GPIO_Ioctl,
#ifdef SUPPORT_GPIO_DEVICE_READ_WRITE_FOPS
	.read 	= GPIO_Read,
	.write 	= GPIO_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
static int GPIO_suspend(struct platform_device *pdev, pm_message_t state)
{
	GPIO_DRVDATA_T	*drv_data;
	drv_data = platform_get_drvdata(pdev);

	GPIO_DevSuspend();

	drv_data->is_suspended = 1;
	GPIO_PRINT("[%s] done suspend\n", GPIO_MODULE);

	return 0;
}


/**
 *
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int GPIO_resume(struct platform_device *pdev)
{
	GPIO_DRVDATA_T	*drv_data;

	drv_data = platform_get_drvdata(pdev);
	if(drv_data->is_suspended == 0) return -1;

	GPIO_DevResume(0;

	drv_data->is_suspended = 0;
	GPIO_PRINT("[%s] done resume\n", GPIO_MODULE);

	return 0;
}
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK, -1 : NOT OK
 *
 */
 int  GPIO_probe(struct platform_device *pdev)
{

	GPIO_DRVDATA_T *drv_data;

	drv_data = (GPIO_DRVDATA_T *)kmalloc(sizeof(GPIO_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	GPIO_PRINT("[%s] done probe\n", GPIO_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function, this function will be called in rmmod gpio module
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int  GPIO_remove(struct platform_device *pdev)
{
	GPIO_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	GPIO_PRINT("released\n");

	return 0;
}

/**
 *
 * module release function. this function will be called in rmmod module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void  GPIO_release(struct device *dev)
{
	GPIO_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver gpio_driver =
{
	.probe		= GPIO_probe,
	.suspend	= GPIO_suspend,
	.remove		= GPIO_remove,
	.resume		= GPIO_resume,
	.driver		=
	{
		.name	= GPIO_MODULE,
	},
};

static struct platform_device gpio_device = {
	.name = GPIO_MODULE,
	.id = 0,
	.id = -1,
	.dev = {
		.release = GPIO_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void GPIO_PreInit(void)
{
    /* TODO: do something */
}

int GPIO_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for gpio device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_gpio_debug_fd = DBG_OPEN( GPIO_MODULE );
	if(g_gpio_debug_fd < 0) return -1;


	OS_DEBUG_EnableModule ( g_gpio_debug_fd );

#if 0
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, 0, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, 1, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, 2, DBG_COLOR_NONE );
#endif
	OS_DEBUG_EnableModuleByIndex ( g_gpio_debug_fd, 3, DBG_COLOR_RED );


	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&gpio_driver) < 0)
	{
		GPIO_PRINT("[%s] platform driver register failed\n",GPIO_MODULE);
	}
	else
	{
		if(platform_device_register(&gpio_device))
		{
			platform_driver_unregister(&gpio_driver);
			GPIO_PRINT("[%s] platform device register failed\n",GPIO_MODULE);
		}
		else
		{
			GPIO_PRINT("[%s] platform register done\n", GPIO_MODULE);
		}
	}
#endif

	GPIO_DevInit();

	g_gpio_device = (GPIO_DEVICE_T*)OS_KMalloc( sizeof(GPIO_DEVICE_T)*GPIO_MAX_DEVICE );

	if ( NULL == g_gpio_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(GPIO_DEVICE_T)* GPIO_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_gpio_device, 0x0, sizeof(GPIO_DEVICE_T)* GPIO_MAX_DEVICE );

	if (g_gpio_major)
	{
		dev = MKDEV( g_gpio_major, g_gpio_minor );
		err = register_chrdev_region(dev, GPIO_MAX_DEVICE, GPIO_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_gpio_minor, GPIO_MAX_DEVICE, GPIO_MODULE );
		g_gpio_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register gpio device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<GPIO_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_gpio_major, g_gpio_minor+i );
		cdev_init( &(g_gpio_device[i].cdev), &g_gpio_fops );
		g_gpio_device[i].devno		= dev;
		g_gpio_device[i].cdev.owner = THIS_MODULE;
		g_gpio_device[i].cdev.ops   = &g_gpio_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_gpio_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding gpio device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_gpio_device[i].devno, "%s%d", GPIO_MODULE, i );
	}

	/* initialize proc system */
	GPIO_PROC_Init ( );

	GPIO_PRINT("gpio device initialized\n");

	return 0;
}

void GPIO_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_gpio_major, g_gpio_minor );

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&gpio_driver);
	platform_device_unregister(&gpio_device);
#endif

	/* cleanup proc system */
	GPIO_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<GPIO_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_gpio_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, GPIO_MAX_DEVICE );

	OS_Free( g_gpio_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for gpio device
 *
 */
static int GPIO_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    GPIO_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, GPIO_DEVICE_T, cdev);

    /* TODO : add your device specific code */


	/* END */

	if(my_dev->dev_open_count == 0)
	{

	}

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    GPIO_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for gpio device
 *
 */
static int GPIO_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    GPIO_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, GPIO_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    GPIO_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}



/**
 * ioctl handler for gpio device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
static long GPIO_Ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	GPIO_DEVICE_T*	gpio_dev;
	LX_GPIO_PARAM_T param;
	int err = 0, ret = 0;

	/*
	 * get current gpio device object
	 */
	gpio_dev = (GPIO_DEVICE_T*)file->private_data;

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != GPIO_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > GPIO_IOC_MAXNR)
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

	GPIO_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case GPIO_IOW_COMMAND_SET:
		{
			GPIO_TRACE("GPIO_IOW_COMMAND_SET\n");
			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevSetPinMux(param.pin_number, (BOOLEAN)param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevSetMode(param.pin_number, (LX_GPIO_MODE_T)param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevSetValue(param.pin_number, (LX_GPIO_VALUE_T)param.data);
					break;
				default: GPIO_ERROR("GPIO_IOW_COMMAND_SET: unknown\n"); return -EFAULT;
			}
			break;
		}

		case GPIO_IORW_COMMAND_GET:
		{
			GPIO_TRACE("GPIO_IORW_COMMAND_GET\n");
			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevGetPinMux(param.pin_number, (BOOLEAN*)&param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevGetMode(param.pin_number, (LX_GPIO_MODE_T*)&param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevGetValue(param.pin_number, (LX_GPIO_VALUE_T*)&param.data);
					break;
				default: GPIO_ERROR("GPIO_IORW_COMMAND_GET: unknown\n"); return -EFAULT;
			}
			GPIO_COPY_TO_USER(arg, &param, sizeof(LX_GPIO_PARAM_T));
			break;
		}

		case GPIO_IOW_EX_COMMAND_SET:
		{
			GPIO_TRACE("GPIO_IOW_EX_COMMAND_SET\n");
			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevExSetPinMux(param.pin_number, (BOOLEAN)param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevExSetMode(param.pin_number, (LX_GPIO_MODE_T)param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevExSetValue(param.pin_number, (LX_GPIO_VALUE_T)param.data);
					break;
				default: GPIO_ERROR("GPIO_IOW_EX_COMMAND_SET: unknown\n"); return -EFAULT;
			}
			break;
		}

		case GPIO_IORW_EX_COMMAND_GET:
		{
			GPIO_TRACE("GPIO_IORW_EX_COMMAND_GET\n");
			GPIO_COPY_FROM_USER(&param, arg, sizeof(LX_GPIO_PARAM_T));
			switch(param.command)
			{
				case LX_GPIO_COMMAND_PIN_MUX:
					ret = GPIO_DevExGetPinMux(param.pin_number, (BOOLEAN*)&param.data);
					break;
				case LX_GPIO_COMMAND_MODE:
					ret = GPIO_DevExGetMode(param.pin_number, (LX_GPIO_MODE_T*)&param.data);
					break;
				case LX_GPIO_COMMAND_VALUE:
					ret = GPIO_DevExGetValue(param.pin_number, (LX_GPIO_VALUE_T*)&param.data);
					break;
				default: GPIO_ERROR("GPIO_IORW_EX_COMMAND_GET: unknown\n"); return -EFAULT;
			}
			GPIO_COPY_TO_USER(arg, &param, sizeof(LX_GPIO_PARAM_T));
			break;
		}

	    default:
	    {
	    	GPIO_ERROR("ioctl: default\n");
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
    }

    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",GPIO_Init);
#else
module_init(GPIO_Init);
#endif
module_exit(GPIO_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

