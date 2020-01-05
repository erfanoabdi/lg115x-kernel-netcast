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
 *  main driver implementation for venc device.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		Jaeseop So (jaeseop.so@lge.com)
 *  version		1.5
 *  date		2012.08.17
 *  note		Additional information.
 *
 *  @addtogroup lg1154_venc
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_VENC_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/version.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "venc_drv.h"
//#include "venc_isr.h"
#include "venc_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef VENC_USE_LOCK
#define VENC_LOCK_INIT()	OS_InitMutex(&venc_mutex, OS_SEM_ATTR_DEFAULT)
#define VENC_LOCK()			OS_LockMutex(&venc_mutex)
#define VENC_UNLOCK()		OS_UnlockMutex(&venc_mutex)
#else
#define VENC_LOCK_INIT()	do { } while(0)
#define VENC_LOCK()			do { } while(0)
#define VENC_UNLOCK()		do { } while(0)
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/**
 *	main control block for venc device.
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
	BOOLEAN					bCodecLoaded;

// END of device specific data
}
VENC_DEVICE_T;

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}VENC_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	VENC_PROC_Init(void);
extern	void	VENC_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		VENC_Init(void);
void	VENC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_venc_debug_fd;
int 	g_venc_major = VENC_MAJOR;
int 	g_venc_minor = VENC_MINOR;

#ifdef VENC_USE_LOCK
OS_SEM_T			venc_mutex;
#endif
UINT32	gVencMSGFlag;
UINT32	gVencCFGFlag;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      VENC_Open(struct inode *, struct file *);
static int      VENC_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int 		VENC_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long		VENC_Ioctl (struct file *, unsigned int, unsigned long );
#endif
#ifdef SUPPORT_VENC_DEVICE_READ_WRITE_FOPS
static ssize_t  VENC_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  VENC_Write(struct file *, const char *, size_t, loff_t *);
#endif
static int		VENC_Mmap (struct file *, struct vm_area_struct *);
static irqreturn_t VENC_Interrupt( int irq, void *dev_id, struct pt_regs *regs );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for venc device
*/
static VENC_DEVICE_T*		g_venc_device;

/**
 * file I/O description for venc device
 *
*/
static struct file_operations g_venc_fops =
{
	.open 	= VENC_Open,
	.release= VENC_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= VENC_Ioctl,
#else
	.unlocked_ioctl	= VENC_Ioctl,
#endif
#ifdef SUPPORT_VENC_DEVICE_READ_WRITE_FOPS
	.read 	= VENC_Read,
	.write 	= VENC_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
	.mmap	= VENC_Mmap,
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
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int
VENC_suspend(struct platform_device *pdev, pm_message_t state)
{
	VENC_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code

	if ( drv_data->is_suspended == 1 )
	{
		return -1;	//If already in suspend state, so ignore
	}

	VENC_RunSuspend();

	drv_data->is_suspended = 1;
	VENC_PRINT("[%s] done suspend\n", VENC_MODULE);

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
static int
VENC_resume(struct platform_device *pdev)
{
	VENC_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;

	VENC_RunResume();

	drv_data->is_suspended = 0;
	VENC_PRINT("[%s] done resume\n", VENC_MODULE);
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
 int
VENC_probe(struct platform_device *pdev)
{
	VENC_DRVDATA_T *drv_data;

	drv_data = (VENC_DRVDATA_T *)kmalloc(sizeof(VENC_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	VENC_PRINT("[%s] done probe\n", VENC_MODULE);
	drv_data->is_suspended = 0;
	platform_set_drvdata(pdev, drv_data);

	return 0;
}

/**
 *
 * module remove function. this function will be called in rmmod fbdev module.
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int
VENC_remove(struct platform_device *pdev)
{
	VENC_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	VENC_PRINT("released\n");

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
static void
VENC_release(struct device *dev)
{
	VENC_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver venc_driver =
{
	.probe			= VENC_probe,
	.suspend		= VENC_suspend,
	.remove 		= VENC_remove,
	.resume 		= VENC_resume,
	.driver 		=
	{
		.name	= VENC_MODULE,
	},
};

static struct platform_device venc_device = {
	.name	= VENC_MODULE,
	.id		= -1,
	.dev	= {
		.release = VENC_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void VENC_PreInit(void)
{
    /* TODO: do something */
}

int VENC_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;
	int			venc_irq_num;

	/* Get the handle of debug output for venc device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_venc_debug_fd = DBG_OPEN( VENC_MODULE );

	if ( g_venc_debug_fd < 0 )
	{
		DBG_PRINT_ERROR("[VENC] Can't get debug handle.\n" );
	}
	else
	{
		OS_DEBUG_EnableModule ( g_venc_debug_fd );
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_NORMAL, DBG_COLOR_NONE );	// PRINT
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_ERROR, DBG_COLOR_RED  );	// ERROR
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_DEBUG, DBG_COLOR_NONE );	// DEBUG
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_TRACE, DBG_COLOR_NONE );	// TRACE
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_VSYNC, DBG_COLOR_NONE );	// ENCODER/VSYNC
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_TIMER, DBG_COLOR_NONE );	// ENCODER/TIMER
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_INTER, DBG_COLOR_NONE );	// ENCODER/INTERRUPT
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_INFO, DBG_COLOR_NONE );	// ENCODER/INFOMATION
		OS_DEBUG_EnableModuleByIndex ( g_venc_debug_fd, VENC_MSG_WARN, DBG_COLOR_NONE );	// WARNING
	}

	SET_VENC_MSG_INDEX( VENC_MSG_NORMAL );
	SET_VENC_MSG_INDEX( VENC_MSG_ERROR );
	//SET_VENC_MSG_INDEX( VENC_MSG_VSYNC );
	//SET_VENC_MSG_INDEX( VENC_MSG_TIMER );
	//SET_VENC_MSG_INDEX( VENC_MSG_INTER );
	//SET_VENC_MSG_INDEX( VENC_MSG_INFO );
	//SET_VENC_MSG_INDEX( VENC_MSG_WARN );

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&venc_driver) < 0)
	{
		VENC_PRINT("[%s] platform driver register failed\n",VENC_MODULE);

	}
	else
	{
		if(platform_device_register(&venc_device))
		{
			platform_driver_unregister(&venc_driver);
			VENC_PRINT("[%s] platform device register failed\n",VENC_MODULE);
		}
		else
		{
			VENC_PRINT("[%s] platform register done\n", VENC_MODULE);
		}
	}
#endif

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
	g_venc_device = (VENC_DEVICE_T*)OS_KMalloc( sizeof(VENC_DEVICE_T)*VENC_MAX_DEVICE );

	if ( NULL == g_venc_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(VENC_DEVICE_T)* VENC_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_venc_device, 0x0, sizeof(VENC_DEVICE_T)* VENC_MAX_DEVICE );

	if (g_venc_major)
	{
		dev = MKDEV( g_venc_major, g_venc_minor );
		err = register_chrdev_region(dev, VENC_MAX_DEVICE, VENC_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_venc_minor, VENC_MAX_DEVICE, VENC_MODULE );
		g_venc_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register venc device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */
	VENC_CFG_MemoryMap();
	VENC_HAL_DeviceInitialize();
	g_venc_device->bCodecLoaded = FALSE;

	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		venc_irq_num = H13_IRQ_VENC0;
	}
	else
	{
		venc_irq_num = L9_IRQ_VENC0;
	}

    if ( request_irq(venc_irq_num, (irq_handler_t)VENC_Interrupt, 0, "DTVSoC2VENC ", NULL)) {
        VENC_DEBUG("request_irq in %s is failed\n", __FUNCTION__);
        return -EIO;
    }

#if 1
	irq_set_affinity( venc_irq_num, cpumask_of(0) );
#endif

	VENC_DEBUG("venc irq registered :%d:\n", venc_irq_num);

	/* END */

	for ( i=0; i<VENC_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_venc_major, g_venc_minor+i );
		cdev_init( &(g_venc_device[i].cdev), &g_venc_fops );
		g_venc_device[i].devno		= dev;
		g_venc_device[i].cdev.owner = THIS_MODULE;
		g_venc_device[i].cdev.ops   = &g_venc_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_venc_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding venc device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}

        	OS_CreateDeviceClass ( g_venc_device[i].devno, "%s%d", VENC_MODULE, i );
	}

	VENC_LOCK_INIT();

	/* initialize proc system */
	VENC_PROC_Init ( );

	VENC_PRINT("venc device initialized\n");

	return 0;
}

void VENC_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_venc_major, g_venc_minor );
	int venc_irq_num;

	/* cleanup proc system */
	VENC_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<VENC_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_venc_device[i].cdev) );
	}

	VENC_HAL_DeviceFinalize();

	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		venc_irq_num = H13_IRQ_VENC0;
	}
	else
	{
		venc_irq_num = L9_IRQ_VENC0;
	}

	/* TODO : cleanup your module not specific minor device */
	free_irq( venc_irq_num, NULL);

	unregister_chrdev_region(dev, VENC_MAX_DEVICE );

	OS_Free( g_venc_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for venc device
 *
 */
static int
VENC_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    VENC_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, VENC_DEVICE_T, cdev);

    /* TODO : add your device specific code */


	/* END */

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    VENC_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for venc device
 *
 */
static int
VENC_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    VENC_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, VENC_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */
	if ( my_dev->dev_open_count <= 0 )
	{

	}

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    VENC_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for venc device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int
VENC_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
{
#else
static long
VENC_Ioctl ( struct file *filp, unsigned int cmd, unsigned long arg )
{
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif
    int err = 0, ret = 0;

    VENC_DEVICE_T*	my_dev;
    struct cdev*		cdev;

	/*
	 * get current venc device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, VENC_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != VENC_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > VENC_IOC_MAXNR)
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

	//VENC_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case LX_VENC_IO_INIT:
		{
			VENC_HAL_Initialize();
			ret = 0;
		}
		break;

		case LX_VENC_IOR_GET_BUFFER_INFO:
		{
			LX_VENC_BUFFER_T stParam;

			VENC_HAL_GetBufferInfo( &stParam );

			if ( copy_to_user( (void *)arg, (void *)&stParam, sizeof(LX_VENC_BUFFER_T) ) )
            {
				VENC_PRINT("ioctl: copy_to_user error !!! \n");
 	            ret = -EFAULT;
            }
		}
		break;

		case LX_VENC_IOW_ENC_SET_INPUT:
		{
			LX_VENC_ENC_INPUT_T stParam;

			if ( copy_from_user( (void *)&stParam, (void *)arg, sizeof(LX_VENC_ENC_INPUT_T) ) )
            {
				VENC_PRINT("ioctl: copy_from_user error !!! \n");
 	            ret = -EFAULT;
				break;
            }

			if ( VENC_HAL_SetInputConfig( &stParam ) != RET_OK )
			{
				VENC_PRINT("Invalid parametes !!! \n");
 	            ret = -EFAULT;
				break;
			}

			ret = 0;
		}
		break;

		case LX_VENC_IOW_ENC_SET_COMMAND:
		{
			LX_VENC_ENC_COMMAND_T eCommand;

			if ( copy_from_user( (void *)&eCommand, (void *)arg, sizeof(LX_VENC_ENC_COMMAND_T) ) )
            {
				VENC_PRINT("ioctl: copy_from_user error !!! \n");
 	            ret = -EFAULT;
				break;
            }

			ret = VENC_HAL_SetCommand( eCommand );
		}
		break;

		case LX_VENC_IOW_ENC_SET_QUALITY:
		{
			LX_VENC_ENC_QUALITY_T eQuality;

			if ( copy_from_user( (void *)&eQuality, (void *)arg, sizeof(LX_VENC_ENC_QUALITY_T) ) )
            {
				VENC_PRINT("ioctl: copy_from_user error !!! \n");
 	            ret = -EFAULT;
				break;
            }

			if ( VENC_HAL_SetQuality( eQuality ) )
			{
				ret = -EFAULT;
				break;
			}

			ret = 0;
		}
		break;

		case LX_VENC_IOW_ENC_SET_QUALITY_DEBUG:
		{
			UINT32 ui32Param;
			
			if ( copy_from_user( (void *)&ui32Param, (void *)arg, sizeof(ui32Param) ) )
            {
				VENC_PRINT("ioctl: copy_from_user error !!! \n");
 	            ret = -EFAULT;
				break;
            }

			if ( VENC_HAL_SetQPLevel( ui32Param ) )
			{
				ret = -EFAULT;
				break;
			}

			ret = 0;
		}
		break;

		case LX_VENC_IOW_ENC_SET_TARGETBITRATE:
		{
			UINT32 ui32Param;

			if ( copy_from_user( (void *)&ui32Param, (void *)arg, sizeof(ui32Param) ) )
            {
				VENC_PRINT("ioctl: copy_from_user error !!! \n");
 	            ret = -EFAULT;
				break;
            }

			if ( VENC_HAL_SetTargetBitrate( ui32Param ) )
			{
				ret = -EFAULT;
				break;
			}


		}
		break;

		case LX_VENC_IOW_ENC_SET_GOP_DEBUG:
		{
			UINT32 ui32_GopNValue;

			if ( copy_from_user( (void *)&ui32_GopNValue, (void *)arg, sizeof(ui32_GopNValue) ) )
            {
				VENC_PRINT("ioctl: copy_from_user error !!! \n");
 	            ret = -EFAULT;
				break;
            }

			if ( VENC_HAL_SetGOP( ui32_GopNValue ) )
			{
				ret = -EFAULT;
				break;
			}

		}
		break;

		case LX_VENC_IOW_ENC_GET_INFO:
		{
			LX_VENC_ENC_INFO_T stParam;

			if( VENC_HAL_GetEncodeInfo( &stParam ) != RET_OK )
			{
				ret = -EFAULT;
				break;
			}

			if ( copy_to_user( (void *)arg, (void *)&stParam, sizeof(LX_VENC_ENC_INFO_T) ) )
            {
				VENC_PRINT("ioctl: copy_to_user error !!! \n");
 	            ret = -EFAULT;
            }
			ret = 0;
		}
		break;

		case LX_VENC_IOR_ENC_GET_FRAME_IMAGE:
		{
			LX_VENC_ENC_FRAME_IMAGE_T stParam;

			VENC_LOCK();

			ret = VENC_HAL_GetFrameImage( &stParam );

			VENC_UNLOCK();

			if ( ret != RET_OK )
			{
				ret = -EFAULT;
				break;
			}

			if ( copy_to_user( (void *)arg, (void *)&stParam, sizeof(LX_VENC_ENC_FRAME_IMAGE_T) ) )
			{
				VENC_PRINT("ioctl: copy_to_user error !!! \n");
				ret = -EFAULT;
			}
			ret = 0;
		}
		break;

		case LX_VENC_IOR_ENC_GET_OUTPUT:
		{
			LX_VENC_ENC_OUTPUT_T stParam;

			//Get the current input buffer status
			if ( VENC_HAL_GetOutputBuffer( &stParam ) != RET_OK )
			{
 	            ret = -EFAULT;
				break;
			}

			/* After updating all the parameters in local structure, copy it back to user memory */
			if ( copy_to_user( (void *)arg, (void *)&stParam, sizeof(LX_VENC_ENC_OUTPUT_T) ) )
            {
				VENC_PRINT("ioctl: copy_to_user error !!! \n");
 	            ret = -EFAULT;
            }
		}
		break;

		case LX_VENC_IOR_ENC_GET_PERFORMANCE:
		{
			LX_VENC_ENC_PERPERMANCE_T stParam;

			VENC_HAL_GetPerformance( &stParam );

			/* After updating all the parameters in local structure, copy it back to user memory */
			if ( copy_to_user( (void *)arg, (void *)&stParam, sizeof(LX_VENC_ENC_PERPERMANCE_T) ) )
            {
				VENC_PRINT("ioctl: copy_to_user error !!! \n");
 	            ret = -EFAULT;
            }
		}
		break;

		case LX_VENC_IOW_ENC_SET_ENCODETYPE :
		{
			LX_VENC_ENCODE_TYPE_T stParam;

			if ( copy_from_user( (void *)&stParam, (void *)arg, sizeof(stParam) ) )
            {
				VENC_PRINT("ioctl: copy_from_user error !!! \n");
 	            ret = -EFAULT;
				break;
            }

			ret = VENC_HAL_SetEncodeType( stParam );
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

#ifdef SUPPORT_VENC_DEVICE_READ_WRITE_FOPS
static ssize_t
VENC_Read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	copy_to_user( (void *)buf, (void *)(0xC0000000+count), 0x0200 );
	return 0x0200;
}

static ssize_t
VENC_Write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	return 0;
}
#endif


static int
VENC_Mmap ( struct file *pstFilePtr, struct vm_area_struct *pstVmArea )
{
	UINT32 offset, size;
	LX_MEMCFG_T *pMemCfg;

	pMemCfg = (LX_MEMCFG_T *)gpstVencMemConfig;

	size = pstVmArea->vm_end - pstVmArea->vm_start;
	offset = pstVmArea->vm_pgoff << PAGE_SHIFT;
		offset += pMemCfg->base;		// add venc base address

	/* Set default mmap variable */
    pstVmArea->vm_flags |= VM_RESERVED;
    pstVmArea->vm_flags |= VM_IO;

	/* For non-cached access !! */
	pstVmArea->vm_page_prot = pgprot_noncached(pstVmArea->vm_page_prot);

    if(remap_pfn_range(
		pstVmArea,
		pstVmArea->vm_start,
		offset >> PAGE_SHIFT,	/* Physical address */
      	pstVmArea->vm_end - pstVmArea->vm_start,
      	pstVmArea->vm_page_prot))
    {
       return -EAGAIN;
    }

	//VENC_PRINT ( "Venc Phys[0x%08X] Virt[0x%08X]\n", offset, (UINT32) pstVmArea->vm_start );

    return 0;
}

static irqreturn_t
VENC_Interrupt( int irq, void *dev_id, struct pt_regs *regs )
{
	return VENC_HAL_ISRHandler();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",VENC_Init);
#else
module_init(VENC_Init);
#endif
module_exit(VENC_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

