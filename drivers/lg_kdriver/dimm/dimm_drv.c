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
 *  main driver implementation for dimm device.
 *	dimm device will teach you how to make device driver with new platform.
 *
 *  author		sh.myoung (sh.myoung@lge.com)
 *  version		1.0
 *  date		2010.01.06
 *  note		Additional information.
 *
 *  @addtogroup lg1150_dimm
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_DIMM_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "dimm_qkb.h"
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

#include "../de/de_def.h"

#include "dimm_drv.h"
#include "dimm_io.h"
#ifdef USE_KDRV_CODES_FOR_L8
#include "l8/dimm_regp_l8.h"
#endif

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
 *	main control block for dimm device.
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
	int 					dev_initialized;  ///< check if device is initialized or not
// END of device specific data
}
DIMM_DEVICE_T;


#ifdef	KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}DIMM_DRVDATA_T;

#endif
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	DIMM_PROC_Init(void);
extern	void	DIMM_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		DIMM_Init(void);
void	DIMM_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_dimm_debug_fd;
int 	g_dimm_major = DIMM_MAJOR;
int 	g_dimm_minor = DIMM_MINOR;
int     g_dimm_suspended = FALSE;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      DIMM_Open(struct inode *, struct file *);
static int      DIMM_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int 		DIMM_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long     DIMM_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg);
#endif
#ifdef SUPPORT_DIMM_DEVICE_READ_WRITE_FOPS
static ssize_t  DIMM_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  DIMM_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for dimm device
*/
static DIMM_DEVICE_T*		g_dimm_device;

/**
 * file I/O description for dimm device
 *
*/
static struct file_operations g_dimm_fops =
{
	.open 	= DIMM_Open,
	.release= DIMM_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= DIMM_Ioctl,
#else
	.unlocked_ioctl = DIMM_Ioctl,
#endif
#ifdef SUPPORT_DIMM_DEVICE_READ_WRITE_FOPS
	.read 	= DIMM_Read,
	.write 	= DIMM_Write,
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
static int DIMM_suspend(struct platform_device *pdev, pm_message_t state)
{
	DIMM_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code





	drv_data->is_suspended = 1;
    g_dimm_suspended = 1;
	DIMM_PRINT("[%s] done suspend\n", DIMM_MODULE);

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
static int DIMM_resume(struct platform_device *pdev)
{
	DIMM_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;


	// add here the resume code
#ifdef USE_DIMM_SUSPEND
	DIMM_IO_resume();
#endif




	drv_data->is_suspended = 0;
    g_dimm_suspended = 0;
	DIMM_PRINT("[%s] done resume\n", DIMM_MODULE);
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
 int  DIMM_probe(struct platform_device *pdev)
{

	DIMM_DRVDATA_T *drv_data;

	drv_data = (DIMM_DRVDATA_T *)kmalloc(sizeof(DIMM_DRVDATA_T) , GFP_KERNEL);


	// add here driver registering code & allocating resource code
#ifdef USE_DIMM_SUSPEND
	DIMM_IO_probe();
#endif



	DIMM_PRINT("[%s] done probe\n", DIMM_MODULE);
	drv_data->is_suspended = 0;
    g_dimm_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function. this function will be called in rmmod dimm module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int  DIMM_remove(struct platform_device *pdev)
{
	DIMM_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code
#ifdef USE_DIMM_SUSPEND
	DIMM_IO_remove();
#endif



	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	DIMM_PRINT("removed\n");

	return 0;
}

/**
 *
 * module release function. this function will be called in rmmod dimm module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void DIMM_release(struct device *dev)
{
	DIMM_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static struct platform_driver dimm_driver =
#else
static struct platform_driver dimm_driver __refdata =
#endif
{
	.probe          = DIMM_probe,
	.suspend        = DIMM_suspend,
	.remove         = DIMM_remove,
	.resume         = DIMM_resume,
	.driver         =
	{
		.name   = DIMM_MODULE,
	},
};

static struct platform_device dimm_device = {
	.name = DIMM_MODULE,
	.id = 0,
	.dev =
	{
		.release = DIMM_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void DIMM_PreInit(void)
{
    /* TODO: do something */
}

int DIMM_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for dimm device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_dimm_debug_fd = DBG_OPEN( DIMM_MODULE );
	if (g_dimm_debug_fd < 0) {
		DBG_PRINT_ERROR("can't open dimm module\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_dimm_debug_fd );
#if 1 //temp
	OS_DEBUG_DisableModuleByIndex ( g_dimm_debug_fd, 0 ); // DIMM_PRINT
	OS_DEBUG_DisableModuleByIndex ( g_dimm_debug_fd, 1 ); // DIMM_TRACE
	OS_DEBUG_EnableModuleByIndex ( g_dimm_debug_fd, 2, DBG_COLOR_RED );   // DIMM_ERROR
	OS_DEBUG_EnableModuleByIndex ( g_dimm_debug_fd, 3, DBG_COLOR_GREEN ); // DIMM_DEBUG
#else //all enable for debug
	OS_DEBUG_EnableModuleByIndex ( g_dimm_debug_fd, 0, DBG_COLOR_NONE );  // DIMM_PRINT
	OS_DEBUG_EnableModuleByIndex ( g_dimm_debug_fd, 1, DBG_COLOR_NONE );  // DIMM_TRACE
	OS_DEBUG_EnableModuleByIndex ( g_dimm_debug_fd, 2, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_dimm_debug_fd, 3, DBG_COLOR_NONE );
#endif //#if 1

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&dimm_driver) < 0)
	{
		DIMM_PRINT("[%s] platform driver register failed\n",DIMM_MODULE);

	}
	else
	{
		if(platform_device_register(&dimm_device))
		{
			platform_driver_unregister(&dimm_driver);
			DIMM_PRINT("[%s] platform device register failed\n",DIMM_MODULE);
		}
		else
		{
			DIMM_PRINT("[%s] platform register done\n", DIMM_MODULE);
		}


	}
#endif
	g_dimm_device = (DIMM_DEVICE_T*)OS_KMalloc( sizeof(DIMM_DEVICE_T)*DIMM_MAX_DEVICE );

	if ( NULL == g_dimm_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(DIMM_DEVICE_T)* DIMM_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_dimm_device, 0x0, sizeof(DIMM_DEVICE_T)* DIMM_MAX_DEVICE );

	if (g_dimm_major)
	{
		dev = MKDEV( g_dimm_major, g_dimm_minor );
		err = register_chrdev_region(dev, DIMM_MAX_DEVICE, DIMM_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_dimm_minor, DIMM_MAX_DEVICE, DIMM_MODULE );
		g_dimm_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register dimm device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<DIMM_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_dimm_major, g_dimm_minor+i );
		cdev_init( &(g_dimm_device[i].cdev), &g_dimm_fops );
		g_dimm_device[i].devno		= dev;
		g_dimm_device[i].cdev.owner = THIS_MODULE;
		g_dimm_device[i].cdev.ops   = &g_dimm_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_dimm_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding dimm device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_dimm_device[i].devno, "%s%d", DIMM_MODULE, i );
	}

	/* initialize proc system */
	DIMM_PROC_Init ( );

	DIMM_PRINT("dimm device initialized\n");

	return 0;
}

void DIMM_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_dimm_major, g_dimm_minor );

#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&dimm_driver);
	platform_device_unregister(&dimm_device);
#endif

	/* cleanup proc system */
	DIMM_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<DIMM_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_dimm_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, DIMM_MAX_DEVICE );

	OS_Free( g_dimm_device );

	DIMM_PRINT("dimm device cleanup\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for dimm device
 *
 */
static int
DIMM_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    DIMM_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, DIMM_DEVICE_T, cdev);

    /* TODO : add your device specific code */
    if ( my_dev->dev_open_count == 0 )
    {
#ifdef USE_KDRV_CODES_FOR_L8
		if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
			DIMM_REG_Create();
		}
#endif
		//reset initialized value
		my_dev->dev_initialized = 0;
    }
	/* END */

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    DIMM_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for dimm device
 *
 */
static int
DIMM_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    DIMM_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, DIMM_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
		--my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */
    if ( my_dev->dev_open_count <= 0 )
    {
#ifdef USE_KDRV_CODES_FOR_L8
		if (lx_chip_rev( ) >= LX_CHIP_REV(L8,A0) ) {
			DIMM_REG_Destroy();
		}
#endif
    }
	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    DIMM_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for dimm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int
DIMM_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long
DIMM_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg)
#endif
{
    int err = 0, ret = 0;

    DIMM_DEVICE_T*	my_dev;
    struct cdev*		cdev;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#else
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current dimm device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, DIMM_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != DIMM_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > DIMM_IOC_MAXNR)
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

	DIMM_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case DIMM_IOW_INIT:
		{
			DIMM_PRINT("DIMM_IOW_INIT IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			if ( my_dev->dev_initialized == 0)
			{
				ret = DIMM_IO_Init(arg);

				//set my_dev->dev_initialized value
				if (ret == 0)
					my_dev->dev_initialized = 1;
			}
			else
				ret = 0;
#endif
		}
		break;

		case DIMM_IOW_LOCALDIMMING_CONTROL:
		{
    	    DIMM_PRINT("DIMM_IOW_LOCALDIMMING_CONTROL IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_LocaldimmingControl(arg);
#endif
		}
		break;

		case DIMM_IOW_STORE_DEMO:
		{
			DIMM_PRINT("DIMM_IOW_STORE_DEMO IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_StoreDemo(arg);
#endif
		}
		break;

		case DIMM_IOW_LINE_DEMO:
		{
			DIMM_PRINT("DIMM_IOW_LINE_DEMO IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_LineDemo(arg);
#endif
		}
		break;


		case DIMM_IOW_PIXELCOMPENSATION_CONTROL:
		{
			DIMM_PRINT("DIMM_IOW_PIXELCOMPENSATION_CONTROL IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_ControlCompensation(arg);
#endif
		}
		break;

		case DIMM_IOW_LUT_CONTROL:
		{
			DIMM_PRINT("DIMM_IOW_LUT_CONTROL IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_LutControl(arg);
#endif
		}
		break;

		case DIMM_IOW_STORE_CONTROL:
		{
			DIMM_PRINT("DIMM_IOW_STORE_CONTROL IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_StoreControl(arg);
#endif
		}
		break;

		case DIMM_IOW_WBCOLOR_CONTROL:
		{
			DIMM_PRINT("DIMM_IOW_WBCOLOR_CONTROL IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_WbColorControl(arg);
#endif
		}
		break;

		case DIMM_IOR_REG_RD:
		{
			DIMM_PRINT("DIMM_IOW_REG_WR IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_RegRd(arg);
#endif
		}
		break;

		case DIMM_IOW_REG_WR:
		{
			DIMM_PRINT("DIMM_IOW_REG_WR IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_RegWr(arg);
#endif
		}
		break;

#ifdef USE_DIMM_TEMPORAL_DEFINITION
		case DIMM_IOR_GET_VERSION:
		{
			DIMM_PRINT("DIMM_IOR_GET_VERSION IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_GetVersion(arg);
#endif
		}
		break;

		case DIMM_IOW_DBG_CONTROL:
		{
			DIMM_PRINT("DIMM_IOW_DBG_CONTROL IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_DbgControl(arg);
#endif
		}
		break;

		case DIMM_IOW_BLU_CONTROL:
		{
			DIMM_PRINT("DIMM_IOW_BLU_CONTROL IOCTL\n");
#ifndef USE_VIDEO_IOCTL_CALLING
			ret = 0;
#else
			ret = DIMM_IO_BluControl(arg);
#endif
		}
		break;
#endif
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
user_initcall_grp("kdrv",DIMM_Init);
#else
module_init(DIMM_Init);
#endif

module_exit(DIMM_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

