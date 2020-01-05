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
 *  main driver implementation for frc device.
 *	frc device will teach you how to make device driver with new platform.
 *
 *  author		sh.myoung (sh.myoung@lge.com)
 *  version		1.0
 *  date		2010.01.06
 *  note		Additional information.
 *
 *  @addtogroup lg1150_frc
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_FRC_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#ifdef	KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include "os_util.h"
#include "base_device.h"
#include "frc_drv.h"
#include "frc_io.h"

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
 *	main control block for frc device.
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
	bool					is_called_scan_direction;
	BOOLEAN					b_scan_direction;
	bool					is_called_fhd_mode;
	LX_FRC_FHD_MODE_T		fhd_mode;
	bool					is_called_rgbyuv_mode;
	LX_FRC_RGBYUV_MODE_T 	rgbyuv_mode;
	bool					is_called_memc;
	BOOLEAN					b_memc_enable;
	bool					is_called_memc_type;
	LX_FRC_MC_TYPE_T		mc_type;
	bool					is_called_pwm_duty_cycle;
	LX_FRC_PWM_PARAM_T		pwm_param;
	bool					is_called_pwm_control;
	LX_FRC_PWM_CTRL_T		pwm_ctrl;

	int						dev_initialized;	///< check if device is initialized or not
// for test
	BOOLEAN					bFreezeEnable;

// END of device specific data
}
FRC_DEVICE_T;

#ifdef	KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}FRC_DRVDATA_T;

#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	FRC_PROC_Init(void);
extern	void	FRC_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		FRC_Init(void);
void	FRC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_frc_debug_fd;
int 	g_frc_major = FRC_MAJOR;
int 	g_frc_minor = FRC_MINOR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      FRC_Open(struct inode *, struct file *);
static int      FRC_Close(struct inode *, struct file *);
static int 		FRC_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#ifdef SUPPORT_FRC_DEVICE_READ_WRITE_FOPS
static ssize_t  FRC_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  FRC_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for frc device
*/
static FRC_DEVICE_T*		g_frc_device;

/**
 * file I/O description for frc device
 *
*/
static struct file_operations g_frc_fops =
{
	.open 	= FRC_Open,
	.release= FRC_Close,
	.ioctl	= FRC_Ioctl,
#ifdef SUPPORT_FRC_DEVICE_READ_WRITE_FOPS
	.read 	= FRC_Read,
	.write 	= FRC_Write,
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
static int FRC_suspend(struct platform_device *pdev, pm_message_t state)
{
	FRC_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code


	// for test
//	FRC_IO_Init();




	drv_data->is_suspended = 1;
	FRC_PRINT("[%s] done suspend\n", FRC_MODULE);

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
static int FRC_resume(struct platform_device *pdev)
{
	FRC_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;

	// add here the resume code

	// for test
	mdelay(50);

#if 1
//	g_frc_device[0].b_scan_direction= 0;

	if(g_frc_device[0].is_called_scan_direction)
	{
		FRC_IOW_SetScanDirection((unsigned long)(&(g_frc_device[0].b_scan_direction)), 0);
	}

	if(g_frc_device[0].is_called_fhd_mode)
	{
		FRC_IOW_SetFHDMode((unsigned long)(&(g_frc_device[0].fhd_mode)), 0);
	}

	if(g_frc_device[0].is_called_rgbyuv_mode)
	{
		FRC_IOW_SetRgbYuvMode((unsigned long)(&(g_frc_device[0].rgbyuv_mode)), 0);
	}

	if(g_frc_device[0].is_called_memc)
	{
		FRC_IOW_SetMEMC((unsigned long)(&(g_frc_device[0].b_memc_enable)), 0);
	}

	if(g_frc_device[0].is_called_memc_type)
	{
		FRC_IOW_SetMEMCType((unsigned long)(&(g_frc_device[0].mc_type)), 0);
	}

	if(g_frc_device[0].is_called_pwm_duty_cycle)
	{
		FRC_IOW_SetPWMDutyCycle((unsigned long)(&(g_frc_device[0].pwm_param)), 0);
	}

	if(g_frc_device[0].is_called_pwm_control)
	{
		FRC_IOW_SetPWMControl((unsigned long)(&(g_frc_device[0].pwm_ctrl)), 0);
	}

// for test
	g_frc_device[0].bFreezeEnable = 0;
	FRC_IOW_SetFreeze((unsigned long)(&(g_frc_device[0].bFreezeEnable)), 0);

#endif

	drv_data->is_suspended = 0;
	FRC_PRINT("[%s] done resume\n", FRC_MODULE);
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
 int  FRC_probe(struct platform_device *pdev)
{

	FRC_DRVDATA_T *drv_data;

	drv_data = (FRC_DRVDATA_T *)kmalloc(sizeof(FRC_DRVDATA_T) , GFP_KERNEL);


	// add here driver registering code & allocating resource code



	FRC_PRINT("[%s] done probe\n", FRC_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}


/**
 *
 * module remove function. this function will be called in rmmod frc module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int  FRC_remove(struct platform_device *pdev)
{
	FRC_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code



	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	FRC_PRINT("removed\n");

	return 0;
}

/**
 *
 * module release function. this function will be called in rmmod frc module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void  FRC_release(struct device *dev)
{
	FRC_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver frc_driver =
{
	.probe          = FRC_probe,
	.suspend        = FRC_suspend,
	.remove         = FRC_remove,
	.resume         = FRC_resume,
	.driver         =
	{
		.name   = FRC_MODULE,
	},
};

static struct platform_device frc_device = {
	.name = FRC_MODULE,
	.id = 0,
	.dev =
	{
		.release = FRC_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void FRC_PreInit(void)
{
    /* TODO: do something */
}

int FRC_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for frc device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_frc_debug_fd = DBG_OPEN( FRC_MODULE );
	if(g_frc_debug_fd < 0) return -1;

	OS_DEBUG_EnableModule ( g_frc_debug_fd );
#if 1 // temp
	OS_DEBUG_DisableModuleByIndex ( g_frc_debug_fd, 0 );                        // FRC_PRINT
	OS_DEBUG_DisableModuleByIndex ( g_frc_debug_fd, 1 );                        // FRC_TRACE
	OS_DEBUG_EnableModuleByIndex ( g_frc_debug_fd, 2, DBG_COLOR_RED );          // FRC_ERROR
	OS_DEBUG_EnableModuleByIndex ( g_frc_debug_fd, 3, DBG_COLOR_GREEN );        // FRC_DEBUG
#else
	OS_DEBUG_EnableModuleByIndex ( g_frc_debug_fd, 0, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_frc_debug_fd, 1, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_frc_debug_fd, 2, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_frc_debug_fd, 3, DBG_COLOR_NONE );
#endif //if 1

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&frc_driver) < 0)
	{
		FRC_PRINT("[%s] platform driver register failed\n",FRC_MODULE);

	}
	else
	{
		if(platform_device_register(&frc_device))
		{
			platform_driver_unregister(&frc_driver);
			FRC_PRINT("[%s] platform device register failed\n",FRC_MODULE);
		}
		else
		{
			FRC_PRINT("[%s] platform register done\n", FRC_MODULE);
		}


	}
#endif

	g_frc_device = (FRC_DEVICE_T*)OS_KMalloc( sizeof(FRC_DEVICE_T)*FRC_MAX_DEVICE );

	if ( NULL == g_frc_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(FRC_DEVICE_T)* FRC_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_frc_device, 0x0, sizeof(FRC_DEVICE_T)* FRC_MAX_DEVICE );

#ifdef	KDRV_CONFIG_PM
	g_frc_device[0].is_called_scan_direction = 0;
	g_frc_device[0].is_called_fhd_mode = 0;
	g_frc_device[0].is_called_rgbyuv_mode = 0;
	g_frc_device[0].is_called_memc = 0;
	g_frc_device[0].is_called_memc_type = 0;
	g_frc_device[0].is_called_pwm_duty_cycle = 0;
	g_frc_device[0].is_called_pwm_control = 0;
#endif

	if (g_frc_major)
	{
		dev = MKDEV( g_frc_major, g_frc_minor );
		err = register_chrdev_region(dev, FRC_MAX_DEVICE, FRC_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_frc_minor, FRC_MAX_DEVICE, FRC_MODULE );
		g_frc_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register frc device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<FRC_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_frc_major, g_frc_minor+i );
		cdev_init( &(g_frc_device[i].cdev), &g_frc_fops );
		g_frc_device[i].devno		= dev;
		g_frc_device[i].cdev.owner = THIS_MODULE;
		g_frc_device[i].cdev.ops   = &g_frc_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_frc_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding frc device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_frc_device[i].devno, "%s%d", FRC_MODULE, i );
	}

	/* initialize proc system */
	FRC_PROC_Init ( );

	FRC_PRINT("frc device initialized\n");

	return 0;
}

void FRC_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_frc_major, g_frc_minor );

#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&frc_driver);
	platform_device_unregister(&frc_device);
#endif

	/* cleanup proc system */
	FRC_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<FRC_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_frc_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, FRC_MAX_DEVICE );

	OS_Free( g_frc_device );

	FRC_PRINT("frc device cleanup\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for frc device
 *
 */
static int
FRC_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    FRC_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, FRC_DEVICE_T, cdev);

    /* TODO : add your device specific code */
   	if( my_dev->dev_open_count == 0 )
    {
		//reset initialized value
		my_dev->dev_initialized = 0;
    }
	/* END */

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    FRC_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for frc device
 *
 */
static int
FRC_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    FRC_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, FRC_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

	/* TODO : add your device specific code */

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    FRC_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for frc device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
static int
FRC_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
{
    int err = 0, ret = 0;

    FRC_DEVICE_T*	my_dev;
    struct cdev*		cdev;

	/*
	 * get current frc device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, FRC_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != FRC_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > FRC_IOC_MAXNR)
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

	FRC_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case FRC_IOW_INIT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_INIT IOCTL\n");
			ret = 0;
#else
			if( my_dev->dev_initialized == 0 )
			{
				ret = FRC_IO_Init(arg);

				//set my_dev->dev_initialized value
				if(ret == 0)
					my_dev->dev_initialized = 1;
			}
			else
				ret = 0;
#endif
		}
		break;

		case FRC_IO_RESET_SW:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IO_RESET_SW IOCTL\n");
			ret = 0;
#else
			ret = FRC_IO_ResetSW();
#endif
		}
		break;

		case FRC_IOR_IS_STABLE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOR_IS_STABLE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOR_IsStable(arg);
#endif
		}
		break;

		case FRC_IOW_SET_MEMC:
		{
#ifdef	KDRV_CONFIG_PM
			if( copy_from_user(&(g_frc_device[0].b_memc_enable), (void *)arg, sizeof(BOOLEAN)) ) break;
			g_frc_device[0].is_called_memc = 1;
#endif

#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_MEMC - ENABLE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetMEMC(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_MEMC_TYPE:
		{
#ifdef	KDRV_CONFIG_PM
			if( copy_from_user(&(g_frc_device[0].mc_type), (void *)arg, sizeof(LX_FRC_MC_TYPE_T)) ) break;
			g_frc_device[0].is_called_memc_type = 1;
#endif

#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_MEMC_TYPE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetMEMCType(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_TRUEMOTION_DEMO:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_TRUEMOTION_DEMO IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetTrueMotionDemo(arg);
#endif
		}
		break;

		case FRC_IOW_SET_TRUEMOTION_DEMO_BAR:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_TRUEMOTION_DEMO_BAR IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetTrueMotionDemoBar(arg);
#endif
		}
		break;

		case FRC_IOW_SET_SCAN_DIRECTION:
		{
#ifdef	KDRV_CONFIG_PM
			if( copy_from_user(&(g_frc_device[0].b_scan_direction), (void *)arg, sizeof(BOOLEAN)) ) break;
			g_frc_device[0].is_called_scan_direction = 1;
#endif

#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_SCAN_DIRECTION IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetScanDirection(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_FREEZE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_FREEZE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetFreeze(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_OSD_CONTROL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_OSD_CONTORL IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetOSDControl(arg);
#endif
		}
		break;

		case FRC_IOW_SET_SPREAD_SPECTRUM:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_SPREAD_SPECTRUM IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetSpreadSpectrum(arg);
#endif
		}
		break;

		case FRC_IOW_SET_PWM_DUTY_CYCLE:
		{
#ifdef	KDRV_CONFIG_PM
			if( copy_from_user(&(g_frc_device[0].pwm_param), (void *)arg, sizeof(LX_FRC_PWM_PARAM_T)) ) break;
			g_frc_device[0].is_called_pwm_duty_cycle = 1;
#endif

#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_PWM_DUTY_CYCLE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetPWMDutyCycle(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_PWM_CONTROL:
		{
#ifdef	KDRV_CONFIG_PM
			if( copy_from_user(&(g_frc_device[0].pwm_ctrl), (void *)arg, sizeof(LX_FRC_PWM_CTRL_T)) ) break;
			g_frc_device[0].is_called_pwm_control = 1;
#endif

#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_PWM_CONTROL IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetPWMControl(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_LOW_DELAY_MODE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_LOW_DELAY_MODE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetLowDelayMode(arg);
#endif
		}
		break;

		case FRC_IOW_SET_DISPLAY_OUTPUT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_DISPLAY_OUTPUT IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetDisplayOutput(arg);
#endif
		}
		break;

		case FRC_IOW_SET_FHD_MODE:
		{
#ifdef	KDRV_CONFIG_PM
			if( copy_from_user(&(g_frc_device[0].fhd_mode), (void *)arg, sizeof(LX_FRC_FHD_MODE_T)) ) break;
			g_frc_device[0].is_called_fhd_mode = 1;
#endif

#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_FHD_MODE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetFHDMode(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_OUTPUT_FRAME_RATE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_OUTPUT_FRAME_RATE IOCTL\n");
			ret = 0;
#else
			ret = 0;
			//ret = FRC_IOW_SetOutputFrameRate(arg);
#endif
		}
		break;

		case FRC_IOW_SET_RGBYUV_MODE:
		{
#ifdef	KDRV_CONFIG_PM
			if( copy_from_user(&(g_frc_device[0].rgbyuv_mode), (void *)arg, sizeof(LX_FRC_RGBYUV_MODE_T)) ) break;
			g_frc_device[0].is_called_rgbyuv_mode = 1;
#endif

#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_RGBYUV_MODE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetRgbYuvMode(arg, 1);
#endif
		}
		break;

		case FRC_IOW_SET_DISPLAY_MUTE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_DISPLAY_MUTE IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetDisplayMute(arg);
#endif
		}
		break;

		case FRC_IOR_GET_FIRMWARE_VERSION:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOR_GET_FIRMWARE_VERSION IOCTL\n");
			ret = 0;
#else
			ret = 0;
			ret = FRC_IOR_GetFirmwareVersion(arg);
#endif
		}
		break;

		case FRC_IOW_SET_JUDDER_LEVEL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_JUDDER_LEVEL IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetJudderLevel(arg);
#endif
		}
		break;

		case FRC_IOW_SET_BLUR_LEVEL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_SET_BLUR_LEVEL IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_SetBlurLevel(arg);
#endif
		}
		break;

		case FRC_IOR_REG_RD:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOR_REG_RD IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOR_RegRd(arg);
#endif
		}
		break;

		case FRC_IOW_REG_WR:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			FRC_PRINT("FRC_IOW_REG_WR IOCTL\n");
			ret = 0;
#else
			ret = FRC_IOW_RegWr(arg);
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
user_initcall_grp("kdrv",FRC_Init);
#else
module_init(FRC_Init);
#endif
module_exit(FRC_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

