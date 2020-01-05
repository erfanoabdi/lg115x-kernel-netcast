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
 *	main driver implementation for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *	author		dongho7.park (dongho7.park@lge.com)
 *	version		1.0
 *	date		2009.12.30
 *	note		Additional information.
 *
 *	@addtogroup lg1150_de
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_DE_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "de_qkb.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/kthread.h>
#ifdef KDRV_CONFIG_PM // added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "de_drv.h"

#include "de_model.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "de_ipc_def.h"
#include "de_ipc.h"
#include "de_int.h"
#include "de_io.h"
#include "de_hal.h"

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
 *	main control block for de device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
// BEGIN of common device
	int						dev_open_count; ///< check if device is opened or not
	dev_t					devno;			///< device number
	struct cdev				cdev;			///< char device structure
// END of command device

// BEGIN of device specific data
	int						dev_de_initialized;   ///< check if device is initialized or not
	int						dev_de_fw_downloaded; ///< check if de firmware is initialized or not

// END of device specific data
}
DE_DEVICE_T;

#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool is_suspended;
}DE_DRVDATA_T;

#endif
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	DE_PROC_Init(void);
extern	void	DE_PROC_Cleanup(void);
extern	void	DE_FW_Download(int fromFile);
#ifdef USE_KDRV_CODES_FOR_H13
extern  int     VIDEO_H13_InitRegister(void);
#endif
extern  int     VIDEO_InitRegister(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		DE_Init(void);
void	DE_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_de_debug_fd;
int		g_de_major = DE_MAJOR;
int		g_de_minor = DE_MINOR;
int		g_de_suspended = FALSE;
int		g_de_device_opened = 0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int		DE_Open(struct inode *, struct file *);
static int		DE_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int		DE_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long     DE_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg);
#endif
#ifdef SUPPORT_DE_DEVICE_READ_WRITE_FOPS
static ssize_t	DE_Read(struct file *, char *, size_t, loff_t *);
static ssize_t	DE_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for de device
*/
static DE_DEVICE_T*		g_de_device;

/**
 * file I/O description for de device
 *
*/
static struct file_operations g_de_fops =
{
	.open	= DE_Open,
	.release= DE_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= DE_Ioctl,
#else
	.unlocked_ioctl = DE_Ioctl,
#endif
#ifdef SUPPORT_DE_DEVICE_READ_WRITE_FOPS
	.read	= DE_Read,
	.write	= DE_Write,
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
static int DE_suspend(struct platform_device *pdev, pm_message_t state)
{
	DE_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code
	DE_HAL_ResetDE(TRUE);


	drv_data->is_suspended = 1;
	g_de_suspended = 1;
	DE_PRINT("[%s] done suspend\n", DE_MODULE);

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
static int DE_resume(struct platform_device *pdev)
{
	DE_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;


	// add here the resume code
	DE_HAL_ResetDE(FALSE);
	DE_FW_Download(FALSE);
#ifdef USE_DE_SUSPEND
	DE_IO_resume();
#endif
	DE_HAL_GPIO_Init();
	DE_HAL_LVDS_Init();

	drv_data->is_suspended = 0;
	g_de_suspended = 0;
	DE_PRINT("[%s] done resume\n", DE_MODULE);

	return RET_OK;
}
/**
 *
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int DE_probe(struct platform_device *pdev)
{
	DE_DRVDATA_T *drv_data;

	drv_data = (DE_DRVDATA_T *)kmalloc(sizeof(DE_DRVDATA_T) , GFP_KERNEL);


	// add here driver registering code & allocating resource code
#ifdef USE_DE_SUSPEND
	DE_IO_probe();
#endif


	DE_PRINT("[%s] done probe\n", DE_MODULE);
	drv_data->is_suspended = 0;
	g_de_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return RET_OK;
}


/**
 *
 * module remove function. this function will be called in rmmod de module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int	DE_remove(struct platform_device *pdev)
{
	DE_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

#ifdef USE_DE_SUSPEND
	DE_IO_remove();
#endif

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	DE_PRINT("removed\n");

	return 0;
}

/**
 *
 * module release function. this function will be called in rmmod de module.
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void DE_release(struct device *dev)
{
	DE_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static struct platform_driver de_driver =
#else
static struct platform_driver de_driver __refdata =
#endif
{
	.probe			= DE_probe,
	.suspend		= DE_suspend,
	.remove			= DE_remove,
	.resume			= DE_resume,
	.driver			=
	{
		.name	= DE_MODULE,
	},
};

static struct platform_device de_device = {
	.name = DE_MODULE,
	.id = 0,
	.dev =
	{
		.release = DE_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void DE_PreInit(void)
{
    /* TODO: do something */
}

int DE_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for de device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_de_debug_fd = DBG_OPEN( DE_MODULE );
	if (g_de_debug_fd < 0) {
		DBG_PRINT_ERROR("can't open de module\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_de_debug_fd );

	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, 0, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, 1, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, 2, DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_de_debug_fd, 3, DBG_COLOR_NONE );

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&de_driver) < 0)
	{
		DE_PRINT("[%s] platform driver register failed\n",DE_MODULE);

	}
	else
	{
		if(platform_device_register(&de_device))
		{
			platform_driver_unregister(&de_driver);
			DE_PRINT("[%s] platform device register failed\n",DE_MODULE);
		}
		else
		{
			DE_PRINT("[%s] platform register done\n", DE_MODULE);
		}


	}
#endif
	g_de_device = (DE_DEVICE_T*)OS_KMalloc( sizeof(DE_DEVICE_T)*DE_MAX_DEVICE );

	if ( NULL == g_de_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(DE_DEVICE_T)* DE_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_de_device, 0x0, sizeof(DE_DEVICE_T)* DE_MAX_DEVICE );

	if (g_de_major)
	{
		dev = MKDEV( g_de_major, g_de_minor );
		err = register_chrdev_region(dev, DE_MAX_DEVICE, DE_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_de_minor, DE_MAX_DEVICE, DE_MODULE );
		g_de_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register de device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */
	DE_IPC_Init();
	DE_HAL_InitPHY2VIRT();
	VIDEO_WorkQueue_Init();
	DE_HAL_GPIO_Init();
	DE_HAL_HDMI_Init();
	DE_HAL_LVDS_Init();
	DE_HAL_MISC_Init();
	DE_HAL_OSD_Init();

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		VIDEO_H13_InitRegister();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		VIDEO_InitRegister();
	} else
#endif
	{
	}

	/* END */

	for ( i=0; i<DE_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_de_major, g_de_minor+i );
		cdev_init( &(g_de_device[i].cdev), &g_de_fops );
		g_de_device[i].devno		= dev;
		g_de_device[i].cdev.owner = THIS_MODULE;
		g_de_device[i].cdev.ops   = &g_de_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_de_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding de device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
#ifndef USE_VIDEO_FOR_FPGA
		OS_CreateDeviceClass ( g_de_device[i].devno, "%s%d", DE_MODULE, i );
#endif
	}

	/* initialize proc system */
	DE_PROC_Init ( );

	DE_PRINT("de device initialized\n");

	return 0;
}

void DE_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_de_major, g_de_minor );

#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&de_driver);
	platform_device_unregister(&de_device);
#endif
	/* cleanup proc system */
	DE_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<DE_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_de_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */
	DE_IPC_Free();
	DE_HAL_FreePHY2VIRT();
	VIDEO_WorkQueue_Destory();

	unregister_chrdev_region(dev, DE_MAX_DEVICE );

	OS_Free( g_de_device );

	DE_PRINT("de device cleanup\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for de device
 *
 */
static int
DE_Open(struct inode *inode, struct file *filp)
{
	int					major,minor;
	struct cdev*		cdev;
	DE_DEVICE_T*	my_dev;

	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, DE_DEVICE_T, cdev);

	/*	TODO : add your device specific code */
	/*	support multi-process system */
	if (g_de_device_opened == 0 )
	{
		my_dev->dev_de_initialized = 0;
		my_dev->dev_de_fw_downloaded = 0;
	}

	/* END */

	g_de_device_opened++;
	filp->private_data = my_dev;

	/* some debug */
	major = imajor(inode);
	minor = iminor(inode);
	DE_PRINT("device opened (%d:%d)\n", major, minor );

	return 0;
}

/**
 * release handler for de device
 *
 */
static int
DE_Close(struct inode *inode, struct file *file)
{
	int					major,minor;
	DE_DEVICE_T*	my_dev;
	struct cdev*		cdev;

	int num_de_irq = 0, num_de_ipc_irq = 0;

	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, DE_DEVICE_T, cdev);

	if ( my_dev->dev_open_count > 0 )
	{
		--my_dev->dev_open_count;
	}

	/* TODO : add your device specific code */
	/*	support multi-process system */
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		num_de_ipc_irq = H13_IRQ_IPC_BCPU;
		num_de_irq = H13_IRQ_DE_BCPU;
	}
	else if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		num_de_ipc_irq = L9_IRQ_IPC_BCPU;
		num_de_irq = L9_IRQ_DE_BCPU;
	}
	else
	{
		num_de_ipc_irq = L8_IRQ_DE_IPC;
		num_de_irq = L8_IRQ_DE;
	}

	if ( my_dev->dev_open_count < 0 )
	{
		free_irq(num_de_ipc_irq, NULL);
		free_irq(num_de_irq, NULL);
	}
	/* END */

	/* some debug */
	major = imajor(inode);
	minor = iminor(inode);
	DE_PRINT("device closed (%d:%d)\n", major, minor );
	return 0;
}

/**
 * ioctl handler for de device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int
DE_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long
DE_Ioctl (struct file * filp, unsigned int cmd, unsigned long arg)
#endif
{
	int err = 0, ret = 0;

	DE_DEVICE_T*	my_dev;
	struct cdev*		cdev;

	int num_de_irq = 0, num_de_ipc_irq = 0;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#else
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current de device object
	 */
	cdev	= inode->i_cdev;
	my_dev	= container_of ( cdev, DE_DEVICE_T, cdev);

	/*
	 * check if IOCTL command is valid or not.
	 * - if magic value doesn't match, return error (-ENOTTY)
	 * - if command is out of range, return error (-ENOTTY)
	 *
	 * note) -ENOTTY means "Inappropriate ioctl for device.
	 */
	if (_IOC_TYPE(cmd) != DE_IOC_MAGIC)
	{
		DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > DE_IOC_MAXNR)
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

#ifndef USE_QEMU_SYSTEM
	//DE_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );
#else
	switch(cmd)
	{
		case DE_IOW_REG_WR:
		case DE_IOR_REG_RD:
			break;
		default :
			DE_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );
	}
#endif

	switch(cmd)
	{

		case DE_IOW_DE_INIT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_PANEL_TYPE_T param;
			DE_PRINT("DE_IOW_DE_INIT IOCTL\n");

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_PANEL_TYPE_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] panel_type = %s \n", param?"LX_PANEL_TYPE_1336":"LX_PANEL_TYPE_1920"  );

			ret = 0;
#else
			/*	support multi-process system */
			if (my_dev->dev_de_initialized == 0)
			{
				if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
				{
					num_de_ipc_irq = H13_IRQ_IPC_BCPU;
					num_de_irq = H13_IRQ_DE_BCPU;
				}
				else if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
				{
					num_de_ipc_irq = L9_IRQ_IPC_BCPU;
					num_de_irq = L9_IRQ_DE_BCPU;
				}
				else
				{
					num_de_ipc_irq = L8_IRQ_DE_IPC;
					num_de_irq = L8_IRQ_DE;
				}

				if (request_irq(num_de_ipc_irq,(irq_handler_t)DE_IPC_interrupt,0,"DE2IPC", NULL)) {
					ffprintk("request_irq in %s is failed\n", __FUNCTION__);
					return -1;
				}

				if (request_irq(num_de_irq,(irq_handler_t)DE_VSYNC_interrupt,0,"DE2VSYNC", NULL)) {
					ffprintk("request_irq in %s is failed\n", __FUNCTION__);
					return -1;
				}

				ret = DE_IO_Init(arg); // TODO

				my_dev->dev_de_initialized++;
			}
			else
			{
				ret = 0;
			}
#endif
		}
		break;

		case DE_IOR_GET_FIRMWARE_INFO:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_FIRMWARE_INFO_T param;

			param.version = 0x100;
			param.date.year = 10;	/* 2010/1/27 */
			param.date.month = 1;
			param.date.day = 27;

			DE_PRINT("DE_IOR_GET_FIRMWARE_INFO IOCTL\n");
			DE_PRINT("[de_drv] firmware info (%0X, %d:%d:%d)\n", param.version,
											param.date.year, param.date.month, param.date.day );

			if ( copy_to_user((void __user *)arg, &param, sizeof(LX_DE_FIRMWARE_INFO_T)) )
				return -EFAULT;

			ret = 0;
#else
			ret = DE_IO_GetFirmwareInfo(arg);
#endif
		}
		break;

		case DE_IOW_SET_BG_COLOR:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_COLOR_T param;

			DE_PRINT("DE_IOW_SET_BG_COLOR IOCTL\n");

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_COLOR_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] bg_color = (%d,%d,%d)\n", param.r, param.g, param.b);

			ret = 0;
#else
			ret = DE_IO_SetBgColor(arg);
#endif
		}
		break;

		case DE_IOR_GET_OUT_FR_RATE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_FR_RATE_T param;

			param.isForceFreeRun = TRUE;
			param.fr_rate = 50;

			DE_PRINT("DE_IOR_GET_OUT_FR_RATE IOCTL\n");
			DE_PRINT("[de_drv] fr rate info is free run %d	freq %d Hz\n", param.isForceFreeRun,param.fr_rate);

			if ( copy_to_user((void __user *)arg, &param, sizeof(LX_DE_FR_RATE_T)) )
				return -EFAULT;

			ret = 0;
#else
			ret = DE_IO_GetOutFrRate(arg);
#endif
		}
		break;

		case DE_IOW_SET_WIN_BLANK:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_SET_WIN_BLANK_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_SET_WIN_BLANK_T)) )
				return -EFAULT;

			DE_PRINT("DE_IOW_SET_WIN_BLANK IOCTL\n");
			DE_PRINT("[de_drv] blank window id = %d, isEnable = %s.\n", param.win_id,param.bEnable ? "ON":"OFF" );
			DE_PRINT("[de_drv] blank window color = (%d,%d,%d)\n",
										param.win_color.r, param.win_color.g, param.win_color.b);

			ret = 0;
#else
			ret = DE_IO_SetWinBlank(arg);
#endif
		}
		break;

		case DE_IOR_GET_INPUT_WIN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_WIN_DIMENSION_T wi_info;

			if ( copy_from_user(&wi_info ,(void __user *)arg, sizeof(LX_DE_WIN_DIMENSION_T)) )
				return -EFAULT;

			if( wi_info.win_id == LX_DE_WIN_MAIN )
			{
				wi_info.rect.w = 1920;
				wi_info.rect.h = 1080;
				wi_info.rect.x = 0;
				wi_info.rect.y = 0;
			}
			else
			{
				wi_info.rect.w = 720;
				wi_info.rect.h = 480;
				wi_info.rect.x = 0;
				wi_info.rect.y = 0;
			}

			if ( copy_to_user((void __user *)arg, &wi_info, sizeof(LX_DE_WIN_DIMENSION_T)) )
				return -EFAULT;

			DE_PRINT("DE_IOR_GET_INPUT_WIN IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_GetInputWin(arg);
#endif
		}
		break;

		case DE_IOR_GET_OUT_WIN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_WIN_DIMENSION_T wo_info;

			if ( copy_from_user(&wo_info ,(void __user *)arg, sizeof(LX_DE_WIN_DIMENSION_T)) )
				return -EFAULT;

			if( wo_info.win_id == LX_DE_WIN_MAIN )
			{
				wo_info.rect.w = 1336;
				wo_info.rect.h = 768;
				wo_info.rect.x = 0;
				wo_info.rect.y = 0;
			}
			else
			{
				wo_info.rect.w = 720;
				wo_info.rect.h = 576;
				wo_info.rect.x = 0;
				wo_info.rect.y = 0;
			}

			if ( copy_to_user((void __user *)arg, &wo_info, sizeof(LX_DE_WIN_DIMENSION_T)) )
				return -EFAULT;

			DE_PRINT("DE_IOR_GET_OUT_WIN IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_GetOutWin(arg);
#endif
		}
		break;

		case DE_IOW_SET_INPUT_WIN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_WIN_DIMENSION_T wi_info;

			if ( copy_from_user(&wi_info ,(void __user *)arg, sizeof(LX_DE_WIN_DIMENSION_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] set input window wid = %d whxy(%d,%d,%d,%d)\n", wi_info.win_id,
													wi_info.rect.w, wi_info.rect.h, wi_info.rect.x, wi_info.rect.y);

			DE_PRINT("DE_IOW_SET_INPUT_WIN IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetInputWin(arg);
#endif
		}
		break;

		case DE_IOW_SET_OUT_WIN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_WIN_DIMENSION_T wo_info;

			if ( copy_from_user(&wo_info ,(void __user *)arg, sizeof(LX_DE_WIN_DIMENSION_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] set output window wid = %d whxy(%d,%d,%d,%d)\n", wo_info.win_id,
													wo_info.rect.w, wo_info.rect.h, wo_info.rect.x, wo_info.rect.y);
			DE_PRINT("DE_IOW_SET_OUT_WIN IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetOutWin(arg);
#endif
		}
		break;

		case DE_IOW_SET_FREEZE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_SET_FREEZE_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_SET_FREEZE_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] set freze w_id = %d	isOn = %s.\n", param.win_id, param.bEnable?"ON":"OFF");
			DE_PRINT("DE_IOW_SET_FREEZE IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetFreeze(arg);
#endif
		}
		break;

		case DE_IOW_SET_INPUT_SRC:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_SET_INPUT_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_SET_INPUT_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] set iput src w_id = %d  src = %d.\n", param.win_id, param.inputSrc );
			DE_PRINT("DE_IOW_SET_INPUT_SRC IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetInputSrc(arg);
#endif
		}
		break;

		case DE_IOW_SET_DIS_OUT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			BOOLEAN isOn;

			if ( copy_from_user(&isOn ,(void __user *)arg, sizeof(UINT32)) )
			return -EFAULT;

			DE_PRINT("[de_drv] set dis out	isOn = %s.\n", isOn?"ON":"OFF");
			DE_PRINT("[de_drv] set dis out	isOn = %d.\n", isOn);
			DE_PRINT("DE_IOW_SET_DIS_OUT IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetDisOut(arg);
#endif
		}
		break;

		case DE_IOW_SET_DIS_FMT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_DIS_FMT_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_DIS_FMT_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] SET_DIS_FMT panel_type = %d	fr_rate = %d.\n", param.panel_type, param.fr_rate );
			DE_PRINT("DE_IOW_SET_DIS_FMT IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetDisFmt(arg);
#endif
		}
		break;

		case DE_IOW_SET_FR_RATE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_FR_RATE_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_FR_RATE_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] SET_FR_RATE isForceFreeRun = %d	fr_rate = %d.\n", param.isForceFreeRun, param.fr_rate);
			DE_PRINT("DE_IOW_SET_FR_RATE IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetFrRate(arg);
#endif
		}
		break;

		case DE_IOW_SET_IRE_PATTERN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_SET_IRE_PATTERN_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_SET_IRE_PATTERN_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] SET_IRE_PATTERN ire_pattern %d, level =%d.\n", param.ire_pattern, param.level);
			DE_PRINT("DE_IOW_SET_IRE_PATTERN IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_SetIrePattern(arg); //TODO
#endif
		}
		break;

		case DE_IOW_SET_MULTI_WIN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_MULTI_WIN IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetMultiWin(arg);
#endif
		}
		break;

		case DE_IOW_MULTI_WIN_ENABLE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_MULTI_WIN_ENABLE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_MultiWinEnable(arg);
#endif
		}
		break;

		case DE_IOWR_GRAB_PIXEL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_GRAB_PIXEL_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_GRAB_PIXEL_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] GRAB_PIXEL win %d, (x,y,w,h)=(%d,%d,%d,%d).\n",
																				param.region.win_id,
																				param.region.pixelGrabX,
																				param.region.pixelGrabY,
																				param.region.pixelGrabW,
																				param.region.pixelGrabH);


			param.region.realPixelGrabW = param.region.pixelGrabW;
			param.region.realPixelGrabH = param.region.pixelGrabH;
			param.region.colorSpace = 0;	// 0: YUV 1:RGB
			param.region.colorDepth = 1; // 0: 8bit 1: 10bit

			param.color.pixelGrabCb = 512;	// Cb or B
			param.color.pixelGrabY = 64;	// Y or G
			param.color.pixelGrabCr = 512;	// CR or R

			if ( copy_to_user((void __user *)arg, &param, sizeof(LX_DE_GRAB_PIXEL_T)) )
				return -EFAULT;

			DE_PRINT("DE_IOWR_GRAB_PIXEL IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_GrabPixel(arg);
#endif
		}
		break;

		case DE_IOR_GET_MVI_TIMING_INFO:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_MVI_TIMING_INFO IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetMviTimingInfo(arg);
#endif
		}
		break;

		case DE_IOW_SET_SPREAD:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_SPREAD IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetSpread(arg);
#endif
		}
		break;

		case DE_IOW_SET_CVI_SRC_TYPE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CVI_SRC_TYPE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCviSrcType(arg);
#endif
		}
		break;

		case DE_IOR_GET_CVI_CSC:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_CVI_CSC IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetCviCsc(arg);
#endif
		}
		break;

		case DE_IOW_SET_CVI_CSC:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_CVI_CSC_T param;
			int i;
			DE_PRINT("DE_IOW_SET_CVI_CSC IOCTL\n");
			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_CVI_CSC_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv]CVI_CSC cvi ch = %d  is_enable = %d\n", param.cvi_channel,param.isEnable);

			for(i=0; i< 9; i++)
					DE_PRINT("[de_drv]CVI_CSC matrix %d = %x\n", i,param.CSC_matrix[i]);
			for(i=0; i< 6; i++)
					DE_PRINT("[de_drv]CVI_CSC offset %d = %x\n", i,param.CSC_offset[i]);

			ret = 0;
#else
			ret = DE_IO_SetCviCsc(arg);
#endif
		}
		break;

		case DE_IOR_GET_POST_CSC:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_POST_CSC IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetPostCsc(arg);
#endif
		}
		break;

		case DE_IOW_SET_POST_CSC:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_POST_CSC_T param;
			int i;

			DE_PRINT("DE_IOW_SET_POST_CSC IOCTL\n");
			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_POST_CSC_T)) )
				return -EFAULT;

			for(i=0; i< 9; i++)
					DE_PRINT("[de_drv]POST_CSC matrix %d = %x\n", i,param.CSC_matrix[i]);
			for(i=0; i< 6; i++)
					DE_PRINT("[de_drv]POST_CSC offset %d = %x\n", i,param.CSC_offset[i]);

			ret = 0;
#else
			ret = DE_IO_SetPostCsc(arg);
#endif
		}
		break;

		case DE_IOR_GET_MVI_COLORIMETRY:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_MVI_COLORIMETRY_T param;

			DE_PRINT("DE_IOR_GET_MVI_COLORIMETRY IOCTL\n");

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_MVI_COLORIMETRY_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv]GET_MVI_COLORIMETRY win %d.\n", param.win_id);

			param.colorimetry = LX_DE_COLOR_601;

			if ( copy_to_user((void __user *)arg, &param, sizeof(LX_DE_MVI_COLORIMETRY_T)) )
				return -EFAULT;

			ret = 0;
#else
			ret = DE_IO_GetMviColorimetry(arg);
#endif
		}
		break;

		case DE_IOW_SET_ZLIST:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_ZLIST IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetZList(arg);
#endif
		}
		break;

		case DE_IOW_SET_DEINTERLACE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_DEINTERLACE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetDeinterlace(arg);
#endif
		}
		break;

		case DE_IOW_SET_UART_FOR_MCU:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_UART_FOR_MCU IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetUart4MCU(arg);
#endif
		}
		break;

// add 2010. 4. 1
		case DE_IOW_SET_PRE3D_IN_MODE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_PRE3D_IN_MODE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetPre3DInMode(arg);
#endif
		}
		break;

		case DE_IOW_SET_3D_OPR_MODE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_3D_OPR_MODE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetPre3DOprMode(arg);
#endif
		}
		break;

		case DE_IOW_SET_3D_FULL_MODE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_3D_FULL_MODE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetFull3DMode(arg);
#endif
		}
		break;

		case DE_IOW_SET_UD_MODE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_UD_MODE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetUDMode(arg);
#endif
		}
		break;

		case DE_IOW_SET_PWM_CONTROL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_PWM_CONTROL IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetPwmControl(arg);
#endif
		}
		break;

		case DE_IOW_SET_PWM_DUTY_CYCLE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_PWM_DUTY_CYCLE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetPwmDutyCycle(arg);
#endif
		}
		break;

		case DE_IOW_SET_PWM_FREQUENCY:
		{
			ret = DE_IO_SetPwmFrequency(arg);
		}
		break;

		case DE_IOW_SET_PWM_PULSE_WIDTH:
		{
			ret = DE_IO_SetPwmPulseWidth(arg);
		}
		break;

		case DE_IOR_GET_EXTERNAL_PWM:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_EXTERNAL_PWM IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetPwmDutyExternal(arg);
#endif
		}
		break;

		case DE_IOW_SET_CVE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CVE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCve(arg);
#endif
		}
		break;

		case DE_IOW_SET_VCS:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_VCS IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetVcs(arg);
#endif
		}
		break;

		case DE_IOR_REG_RD:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			UINT32 io_data;

			if ( copy_from_user(&io_data ,(void __user *)arg, sizeof(UINT32)) )
				return -EFAULT;

			DE_PRINT("[de_drv] address 0x%x.\n", io_data);
			io_data = 0xFAFAFAFA;	// read form L8 register
			DE_PRINT("[de_drv] rd data 0x%x.\n", io_data);

			if ( copy_to_user((void __user *)arg, &io_data, sizeof(UINT32)) )
				return -EFAULT;

			DE_PRINT("DE_IOR_REG_RD IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_RegRd(arg);
#endif
		}
		break;

		case DE_IOW_REG_WR:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_REG_WR_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_REG_WR_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv] address 0x%x.\n", param.wr_addr);
			DE_PRINT("[de_drv] wr data 0x%x.\n", param.wr_data);

			// write to  L8 register

			DE_PRINT("DE_IOW_REG_WR IOCTL\n");

			ret = 0;
#else
			ret = DE_IO_RegWr(arg);
#endif
		}
		break;

		case DE_IOR_GET_CAPTURE_WIN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_CVI_CAPTURE_WIN_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_CVI_CAPTURE_WIN_T)) )
				return -EFAULT;

			ret = 0;
#else
			ret = DE_IO_GetCaptureWin(arg);
#endif
		}
		break;

		case DE_IOW_SET_CAPTURE_WIN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_CVI_CAPTURE_WIN_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_CVI_CAPTURE_WIN_T)) )
				return -EFAULT;

			ret = 0;
#else
			ret = DE_IO_SetCaptureWin(arg);
#endif
		}
		break;

		case DE_IOW_SET_ECANVAS:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_ECANVAS_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_ECANVAS_T)) )
				return -EFAULT;

			ret = 0;
#else
//			ret = DE_IO_SetEcanvas(arg);
#endif
		}
		break;

		case DE_IOW_OIF_INIT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_INIT IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_Init(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_LVDS_OUTPUT:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_LVDS_OUTPUT IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetLvdsOutput(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_LVDS_POWER:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_LVDS_POWER IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetLvdsPower(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_DARK_SCREEN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_DARK_SCREEN IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetDarkScreen(arg);
#endif
		}
		break;

// add OIF ioctl 2010. 3. 10
		case DE_IOW_OIF_SET_VESA_JEIDA:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_VESA_JEIDA IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetVesaJeida(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_PANEL_IF:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_PANEL_IF IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetPanelIf(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_PIXEL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_PIXEL IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetPixel(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_BIT_DEPTH:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_BIT_DEPTH IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetBitDepth(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SELECT_OUT_PATH:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SELECT_OUT_PATH IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SelectOutPath(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_LVDS_OUT_CTRL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_LVDS_OUT_CTRL IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetLvdsOutCtrl(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SELECT_LVDS_PATH:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SELECT_LVDS_PATH IOCTL\n");
			ret = 0;
#else
			 ret = DE_IO_OIF_SelectLvdsPath(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SELECT_OUT_CH:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SELECT_OUT_CH IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SelectOutCh(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SELECT_LED_PATH:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SELECT_LED_PATH IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SelectLedPath(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SELECT_PWM_PATH:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SELECT_PWM_PATH IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SelectPwmPath(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SELECT_LR_PATH:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SELECT_LR_PATH IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SelectLrPath(arg);
#endif
		}
		break;

		case DE_IOR_OIF_GET_INFO:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_OIF_GET_INFO IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_GetInfo(arg);
#endif
		}
		break;

		case DE_IOW_OIF_SET_LVDS_PORT_SWAP:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_OIF_SET_LVDS_PORT_SWAP IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_OIF_SetLvdsPortSwap(arg);
#endif
		}
		break;

		case DE_IOW_IPC_CLI:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_IPC_CLI IOCTL\n");
			ret = 0;
#else
			LX_DE_IPC_CLI_T *pstParams = (LX_DE_IPC_CLI_T*)arg;
			UINT32 msgCnt;

			do {
				ret = -EFAULT;
				if ( pstParams->cnt > 1024*1024 ) break;
				if ( copy_from_user(&msgCnt, (void __user *)&pstParams->cnt, sizeof(int)) ) break;
				ret = DE_IPC_SetStr(pstParams->pStr, msgCnt);
			} while (0);
#endif
		}
		break;

		case DE_IOW_FW_DOWNLOAD:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_FW_DWLD_T param;

			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_FW_DWLD_T)) )
				return -EFAULT;

			ret = 0;
#else
			/*	support multi-process system */
			if ( my_dev->dev_de_fw_downloaded == 0)
			{
				ret = DE_IO_FW_Download(arg);
				my_dev->dev_de_fw_downloaded++;
			}
			else
			{
				ret = 0;
			}
#endif
		}
		break;

		case DE_IOW_SET_CVI_FIR:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			LX_DE_CVI_FIR_T param;
			int i;
			DE_PRINT("DE_IOW_SET_CVI_FIR IOCTL\n");
			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_CVI_FIR_T)) )
				return -EFAULT;

			DE_PRINT("[de_drv]CVI_FIR cvi ch = %d  is_enable = %d\n", param.cvi_channel,param.isEnable);

			for(i=0; i< 8; i++)
					DE_PRINT("[de_drv]CVI_FIR coef %d = %x\n", i,param.fir_coef[i]);

			ret = 0;
#else
			ret = DE_IO_SetCviFir(arg);
#endif
		}
		break;

		case DE_IOW_SET_CVI_TPG:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CVI_TPG IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCviTpg(arg);
#endif
		}
		break;

		case DE_IOW_SET_CVI_CSAMPLE_MODE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CVI_CSAMPLE_MODE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCviCsampleMode(arg);
#endif
		}
		break;

		case DE_IOW_SET_CVI_SYNC_RESHAPE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CVI_SYNC_RESHAPE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCviSyncReshape(arg);
#endif
		}
		break;

		case DE_IOR_GET_CVI_INFO:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_CVI_INFO IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetCviInfo(arg);
#endif
		}
		break;

		case DE_IOW_SET_PE_TEST_PATTERN_GEN:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_PE_TEST_PATTERN_GEN IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetPeTestPatternGen(arg);
#endif
		}
		break;

		case DE_IOW_SET_PE_BBD_CTRL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_PE_BBD_CTRL IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetPeBbdCtrl(arg);
#endif
		}
		break;

		case DE_IOW_GET_PE_BBD_STATUS:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_GET_PE_BBD_STATUS IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetPeBbdStatus(arg);
#endif
		}
		break;

		case DE_IOW_SET_EDGECROP:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_EDGECROP IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetEdgeCrop(arg);
#endif
		}
		break;

		case DE_IOW_SET_TABLE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_TABLE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetTable(arg);
#endif
		}
		break;

		case DE_IOW_SET_DVR_FMT_CTRL:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_DVR_FMT_CTRL IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetDvrFmtCtrl(arg);
#endif
		}
		break;

		case DE_IOW_FC_SET_WIN_INFO:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_FC_SET_WIN_INFO IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_FC_SetWinInfo(arg);
#endif
		}
		break;

		case DE_IOR_FC_GET_FRAME_INFO:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_FC_GET_FRAME_INFO IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_FC_GetFrameInfo(arg);
#endif
		}
		break;


		case DE_IOW_SET_SUB_SC_FREEZE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_SUB_SC_FREEZE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetSubScFreeze(arg);
#endif
		}
		break;

		case DE_IOW_SET_CVI_FREEZE:
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CVI_FREEZE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCviFreeze(arg);
#endif
		}
		break;

		case DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCviVideoFrameBuffer(arg);
#endif

		}
		break;

		case  DE_IOWR_SELECT_MULTI_WIN_SRC :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOWR_SELECT_MULTI_WIN_SRC IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SelectMultiWinSrc(arg);
#endif
		}
		break;

		case  DE_IOW_SET_SCART_RGB_BYPASS_MODE :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_SCART_RGB_BYPASS_MODE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetScartRGBBypassMode(arg);
#endif
		}
		break;


		case DE_IOR_GET_DBG :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_DBG IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetDebug(arg);
#endif
		}
		break;

		case DE_IOW_SET_DBG :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_DBG IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetDebug(arg);
#endif
		}
		break;

		case DE_IOR_GET_CPU_MVI_PORT :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_CPU_MVI_PORT IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetCpuMviPort(arg);
#endif
		}
		break;

		case DE_IOW_SET_CPU_MVI_PORT :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CPU_MVI_PORT IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCpuMviPort(arg);
#endif
		}
		break;

		case DE_IOW_SET_LOW_DELAY :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_LOW_DELAY IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetLowDelay(arg);
#endif
		}
		break;

		case DE_IOR_GET_LOW_DELAY :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_LOW_DELAY IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetLowDelay(arg);
#endif
		}
		break;

		case DE_IOW_SET_3D_INFO_THROUGH_MIDDLEWARE :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_3D_INFO_THROUGH_MIDDLEWARE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_Set3DInfoThroughMiddleware(arg);
#endif
		}
		break;

		case DE_IOW_GET_3D_INFO_THROUGH_MIDDLEWARE :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_GET_3D_INFO_THROUGH_MIDDLEWARE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_Get3DInfoThroughMiddleware(arg);
#endif
		}
		break;


		case DE_IOR_GET_PAR_INFO :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_PAR_INFO IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetParInfo(arg);
#endif
		}
		break;

		case DE_IOW_VDEC_MEM_SHARE :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_VDEC_MEM_SHARE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetVdecMemShare(arg);
#endif
		}
		break;

		case DE_IOW_SET_3D_INOUT_CTRL :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_3D_INOUT_CTRL IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_Set3DInOutCtrl(arg);
#endif
		}
		break;

		case DE_IOW_SET_IF_CONFIG :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_IF_CONFIG IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetInterfaceConfig(arg);
#endif
		}
		break;

		case DE_IOR_GET_SYS_STATUS :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_SYS_STATUS IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetSystemStatus(arg);
#endif
		}
		break;

		case DE_IOR_GET_SRC_STATUS :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_SRC_STATUS IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetSourceStatus(arg);
#endif
		}
		break;

		case DE_IOW_SET_IN_SRC :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_IN_SRC IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetInSrc(arg);
#endif
		}
		break;

		case DE_IOW_SET_TIMING_INFO :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_SRC_TIMING_INFO IOCTL\n");
			ret = 0;
#else
			//ret = DE_IO_SetTimingInfo(arg);
#endif
		}
		break;

		case DE_IOW_SET_OPERATION :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_OPERATION IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetOperation(arg);
#endif
		}
		break;

		case DE_IOW_SET_SUB_OPERATION :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_SUB_OPERATION IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetSubOperation(arg);
#endif
		}
		break;

		case DE_IOW_SET_CAPTURE :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_CAPTURE IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetCaptureControl(arg);
#endif
		}
		break;

		case DE_IOW_SET_MULTI_VISION :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_MULTI_VISION IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetMultiVision(arg);
#endif
		}
		break;

		case DE_IOW_SET_FRAME_TO_OSD :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_FRAME_TO_OSD IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_SetFrameToOsd(arg);
#endif
		}
		break;

		case DE_IOR_GET_FRAME_FOR_OSD :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_GET_FRAME_TO_OSD IOCTL\n");
			ret = 0;
#else
			ret =DE_IO_GetFrameForOsd(arg);
#endif
		}
		break;

		case DE_IOR_GET_SCALER_INFO :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOR_GET_SCALER_INFO IOCTL\n");
			ret = 0;
#else
			ret = DE_IO_GetScalerInfo(arg);
#endif
		}
		break;

#if 0//def USE_VIDEO_FOR_FPGA
		case DE_IOW_SET_EVAL_DBG :
		{
#ifndef USE_VIDEO_IOCTL_CALLING
			DE_PRINT("DE_IOW_SET_DBG IOCTL\n");
			ret = 0;
#else
			#include "de_dbi.h"
			LX_DE_SET_EVAL_DBG_T param;
			if ( copy_from_user(&param ,(void __user *)arg, sizeof(LX_DE_SET_EVAL_DBG_T)) )
				return -EFAULT;
			switch (param.cmd)
			{
				case LX_DE_EVAL_CMD_DBI :
				{
					ret = DBI_VIDEO_Execute(param.arg.argc, param.arg.argv);
				}
				break;

				default :
					break;
			}
#endif
		}
#endif
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
user_initcall_grp("kdrv", DE_Init);
#else
module_init(DE_Init);
#endif
module_exit(DE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

