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
 *  main driver implementation for fmt3d device.
 *	fmt3d device will teach you how to make device driver with new platform.
 *
 *  author		dongho7.park (dongho7.park@lge.com)
 *  version		0.6a
 *  date		2010.01.06
 *  note		Additional information.
 *
 *  @addtogroup lg1150_fmt3d
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_FMT3D_DEVICE_READ_WRITE_FOPS

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
#ifdef	KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include "os_util.h"
#include "base_device.h"

#include "../de/de_model.h"
#include "../de/de_def.h"
#include "fmt3d_drv.h"
#include "fmt3d_io.h"

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
 *	main control block for fmt3d device.
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

// BEGIN of device specific data


// END of device specific data
}
FMT3D_DEVICE_T;

#ifdef	KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}FMT3D_DRVDATA_T;

#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	FMT3D_PROC_Init(void);
extern	void	FMT3D_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		FMT3D_Init(void);
void	FMT3D_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_fmt3d_debug_fd;
int 	g_fmt3d_major = FMT3D_MAJOR;
int 	g_fmt3d_minor = FMT3D_MINOR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      FMT3D_Open(struct inode *, struct file *);
static int      FMT3D_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int 		FMT3D_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long     FMT3D_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg);
#endif
#ifdef SUPPORT_FMT3D_DEVICE_READ_WRITE_FOPS
static ssize_t  FMT3D_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  FMT3D_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for fmt3d device
*/
static FMT3D_DEVICE_T*		g_fmt3d_device;

/**
 * file I/O description for fmt3d device
 *
*/
static struct file_operations g_fmt3d_fops =
{
	.open 	= FMT3D_Open,
	.release= FMT3D_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= FMT3D_Ioctl,
#else
	.unlocked_ioctl = FMT3D_Ioctl,
#endif
#ifdef SUPPORT_FMT3D_DEVICE_READ_WRITE_FOPS
	.read 	= FMT3D_Read,
	.write 	= FMT3D_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef	KDRV_CONFIG_PM	// added by SC Jung for quick booting
/**
 *
 * suspending module.
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int FMT3D_suspend(struct platform_device *pdev, pm_message_t state)
{
	FMT3D_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code





	drv_data->is_suspended = 1;
	FMT3D_PRINT("[%s] done suspend\n", FMT3D_MODULE);

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
static int FMT3D_resume(struct platform_device *pdev)
{
	FMT3D_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;


	// add here the resume code




	drv_data->is_suspended = 0;
	FMT3D_PRINT("[%s] done resume\n", FMT3D_MODULE);
	return 0;
}
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
 int  FMT3D_probe(struct platform_device *pdev)
{

	FMT3D_DRVDATA_T *drv_data;

	drv_data = (FMT3D_DRVDATA_T *)kmalloc(sizeof(FMT3D_DRVDATA_T) , GFP_KERNEL);


	// add here driver registering code & allocating resource code



	FMT3D_PRINT("[%s] done probe\n", FMT3D_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function. this function will be called in rmmod fmt3d module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int  FMT3D_remove(struct platform_device *pdev)
{
	FMT3D_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code



	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	FMT3D_PRINT("removed\n");

	return 0;
}

/**
 *
 * module release function. this function will be called in rmmod fmt3d module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void FMT3D_release(struct device *dev)
{
	FMT3D_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static struct platform_driver fmt3d_driver =
#else
static struct platform_driver fmt3d_driver __refdata =
#endif
{
	.probe          = FMT3D_probe,
	.suspend        = FMT3D_suspend,
	.remove         = FMT3D_remove,
	.resume         = FMT3D_resume,
	.driver         =
	{
		.name   = FMT3D_MODULE,
	},
};

static struct platform_device fmt3d_device = {
	.name = FMT3D_MODULE,
	.id = 0,
	.dev =
	{
		.release = FMT3D_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void FMT3D_PreInit(void)
{
    /* TODO: do something */
}

int FMT3D_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for fmt3d device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_fmt3d_debug_fd = DBG_OPEN( FMT3D_MODULE );
	if (g_fmt3d_debug_fd < 0) {
		DBG_PRINT_ERROR("can't open fmt3d module\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_fmt3d_debug_fd );

	OS_DEBUG_EnableModuleByIndex ( g_fmt3d_debug_fd, 0, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_fmt3d_debug_fd, 1, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_fmt3d_debug_fd, 2, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_fmt3d_debug_fd, 3, DBG_COLOR_NONE );

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&fmt3d_driver) < 0)
	{
		FMT3D_PRINT("[%s] platform driver register failed\n",FMT3D_MODULE);

	}
	else
	{
		if(platform_device_register(&fmt3d_device))
		{
			platform_driver_unregister(&fmt3d_driver);
			FMT3D_PRINT("[%s] platform device register failed\n",FMT3D_MODULE);
		}
		else
		{
			FMT3D_PRINT("[%s] platform register done\n", FMT3D_MODULE);
		}


	}
#endif

	g_fmt3d_device = (FMT3D_DEVICE_T*)OS_KMalloc( sizeof(FMT3D_DEVICE_T)*FMT3D_MAX_DEVICE );

	if ( NULL == g_fmt3d_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(FMT3D_DEVICE_T)* FMT3D_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_fmt3d_device, 0x0, sizeof(FMT3D_DEVICE_T)* FMT3D_MAX_DEVICE );

	if (g_fmt3d_major)
	{
		dev = MKDEV( g_fmt3d_major, g_fmt3d_minor );
		err = register_chrdev_region(dev, FMT3D_MAX_DEVICE, FMT3D_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_fmt3d_minor, FMT3D_MAX_DEVICE, FMT3D_MODULE );
		g_fmt3d_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register fmt3d device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<FMT3D_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_fmt3d_major, g_fmt3d_minor+i );
		cdev_init( &(g_fmt3d_device[i].cdev), &g_fmt3d_fops );
		g_fmt3d_device[i].devno		= dev;
		g_fmt3d_device[i].cdev.owner = THIS_MODULE;
		g_fmt3d_device[i].cdev.ops   = &g_fmt3d_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_fmt3d_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding fmt3d device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_fmt3d_device[i].devno, "%s%d", FMT3D_MODULE, i );
	}

	/* initialize proc system */
	FMT3D_PROC_Init ( );

	FMT3D_PRINT("fmt3d device initialized\n");

	return 0;
}

void FMT3D_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_fmt3d_major, g_fmt3d_minor );

#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&fmt3d_driver);
	platform_device_unregister(&fmt3d_device);
#endif

	/* cleanup proc system */
	FMT3D_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<FMT3D_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_fmt3d_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, FMT3D_MAX_DEVICE );

	OS_Free( g_fmt3d_device );

	FMT3D_PRINT("fmt3d device cleanup\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for fmt3d device
 *
 */
static int
FMT3D_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    FMT3D_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, FMT3D_DEVICE_T, cdev);

    /* TODO : add your device specific code */
	/*  support multi-process system */
    if ( my_dev->dev_open_count == 0 )
    {
		// nothing to do!
    }

	/* END */

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    FMT3D_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for fmt3d device
 *
 */
static int
FMT3D_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    FMT3D_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, FMT3D_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
		--my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */
	/*  support multi-process system */
    if ( my_dev->dev_open_count <= 0 )
    {
        // nothing to do!
    }

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    FMT3D_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for fmt3d device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int
FMT3D_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long
FMT3D_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg)
#endif
{
    int err = 0, ret = 0;

    FMT3D_DEVICE_T*	my_dev;
    struct cdev*		cdev;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#else
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current fmt3d device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, FMT3D_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != FMT3D_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > FMT3D_IOC_MAXNR)
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

//	FMT3D_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{

		case FMT3D_IO_INIT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FMT3D_PRINT("FMT3D_IO_INIT IOCTL\n");
			ret = 0;
#else
			ret = FMT3D_IO_Init(arg);
#endif
		}
		break;

		case FMT3D_IOW_SET_CONVERGENCE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FMT3D_PRINT("FMT3D_IOW_SET_CONVERGENCE IOCTL\n");
			ret = 0;
#else
			ret = FMT3D_IO_SetConvergence(arg);
#endif
		}
		break;

		case FMT3D_IOW_SET_DEPTH_CTRL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FMT3D_PRINT("FMT3D_IOW_SET_DEPTH_CTRL IOCTL\n");
			ret = 0;
#else
			ret = FMT3D_T3_IO_SetDepthCtrl(arg);
#endif
		}
		break;

		case FMT3D_IOW_SET_FPR_FHD:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FMT3D_PRINT("FMT3D_IOW_SET_FPR_FHD IOCTL\n");
			ret = 0;
#else
			ret = FMT3D_IO_SetFprFhd(arg);
#endif
		}
		break;

		case FMT3D_IOW_SET_INOUT_CTRL :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FMT3D_PRINT("FMT3D_IOW_SET_INOUT_CTRL IOCTL\n");
			ret = 0;
#else
			ret = FMT3D_IO_SetInOutCtrl(arg);
#endif
		}
		break;

	    default:
	    {
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
    }

    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",FMT3D_Init);
#else
module_init(FMT3D_Init);
#endif
module_exit(FMT3D_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

