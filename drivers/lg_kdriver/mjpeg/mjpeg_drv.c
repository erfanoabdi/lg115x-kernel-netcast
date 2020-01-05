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
 *  main driver implementation for mjpeg device.
 *	MJPEG device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.04.09
 *  note		Additional information.
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_MJPEG_DEVICE_READ_WRITE_FOPS

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
#include <asm/io.h>				// for ioremap
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/version.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "mjpeg_drv.h"
#include "mjpeg_core.h"
#include "mjpeg_header.h"
#include "icod_reg_l9.h"
#include "l9/base_addr_sw_l9.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
enum
{
	MJPEG_EVENT_DONE	= 0x0001,
	MJPEG_EVENT_BBC		= 0x0002,
	MJPEG_EVENT_ERROR	= 0x0004,
};

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#ifdef MJPEG_USE_LOCK
#define MJPEG_LOCK_INIT()		OS_InitMutex(&mjpeg_mutex, OS_SEM_ATTR_DEFAULT)
#define MJPEG_LOCK()			OS_LockMutex(&mjpeg_mutex)
#define MJPEG_UNLOCK()			OS_UnlockMutex(&mjpeg_mutex)
#else
#define MJPEG_LOCK_INIT()
#define MJPEG_LOCK()
#define MJPEG_UNLOCK()
#endif


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/**
 *	main control block for MJPEG device.
 *	each minor device has unique control block
 *
 */
typedef struct
{
// BEGIN of common device
	int						dev_open_count;		///< check if device is opened or not
	dev_t					devno;				///< device number
	struct cdev				cdev;				///< char device structure
// END of command device

// BEGIN of device specific data
	OS_EVENT_T				stEvent;			///< evnet to catch decode_done

	LX_MJPEG_HEADER_T		stHeader;			///< header information of current image
	LX_MJPEG_IMAGE_INFO_T	stImageInfo;		///< image informatino of current image
	LX_MJPEG_OPTION_T			stOption;

	LX_MEM_BUF_T			stDataBuffer;		///< encoded data buffer
	LX_MJPEG_IMAGE_BUF_T	stImageBuffer;		///< image buffer

	UINT32					ui32InputSize;
	UINT32					ui32OutputSize;

	BOOLEAN					bFirstBlock;
// END of device specific data
}
MJPEG_DEVICE_T;

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
} MJPEG_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	MJPEG_PROC_Init(void);
extern	void	MJPEG_PROC_Cleanup(void);

extern	LX_MJPEG_CFG_T* MJPEG_GetCfg(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		MJPEG_Init(void);
void	MJPEG_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_MJPEG_debug_fd;
int 	g_MJPEG_major = MJPEG_MAJOR;
int 	g_MJPEG_minor = MJPEG_MINOR;

volatile ICOD_REG_T*	gpRealRegICOD	= NULL;		/** ICOD register */
ICOD_REG_T*				gpRegICOD		= NULL;		/** ICOD shadow register */
volatile MJPEG_REG_T*	gpRealRegMJPEG	= NULL;		/** MJPEG register */
MJPEG_REG_T*			gpRegMJPEG		= NULL;		/** MJPEG shadow register */

#ifdef MJPEG_USE_LOCK
OS_SEM_T			mjpeg_mutex;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      MJPEG_Open(struct inode *, struct file *);
static int      MJPEG_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int 		MJPEG_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long		MJPEG_Ioctl (struct file *, unsigned int, unsigned long );
#endif
static int      MJPEG_mmap(struct file *, struct vm_area_struct *);
#ifdef SUPPORT_MJPEG_DEVICE_READ_WRITE_FOPS
static ssize_t  MJPEG_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  MJPEG_Write(struct file *, const char *, size_t, loff_t *);
#endif
irqreturn_t		MJPEG_Interrrupt(int, void *, struct pt_regs *);

static void		_SW_Reset(void);
static SINT32	_Initialize(void);
static void		_DisableBBC(void);
static void		_EnableBBC(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for MJPEG device
*/
static MJPEG_DEVICE_T*		g_MJPEG_device;

/**
 * file I/O description for MJPEG device
 *
*/
static struct file_operations g_MJPEG_fops =
{
	.open 	= MJPEG_Open,
	.release= MJPEG_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= MJPEG_Ioctl,
#else
	.unlocked_ioctl	= MJPEG_Ioctl,
#endif
	.mmap	= MJPEG_mmap,
#ifdef SUPPORT_MJPEG_DEVICE_READ_WRITE_FOPS
	.read 	= MJPEG_Read,
	.write 	= MJPEG_Write,
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
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int
MJPEG_suspend(struct platform_device *pdev, pm_message_t state)
{
	MJPEG_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code

	if ( drv_data->is_suspended == 1 )
	{
		return -1;	//If already in suspend state, so ignore
	}

	drv_data->is_suspended = 1;
	MJPEG_PRINT("[%s] done suspend\n", MJPEG_MODULE);

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
MJPEG_resume(struct platform_device *pdev)
{
	MJPEG_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;

	// add here the resume code

	drv_data->is_suspended = 0;
	MJPEG_PRINT("[%s] done resume\n", MJPEG_MODULE);
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
MJPEG_probe(struct platform_device *pdev)
{
	MJPEG_DRVDATA_T *drv_data;

	drv_data = (MJPEG_DRVDATA_T *)kmalloc(sizeof(MJPEG_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	MJPEG_PRINT("[%s] done probe\n", MJPEG_MODULE);
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
MJPEG_remove(struct platform_device *pdev)
{
	MJPEG_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	MJPEG_PRINT("released\n");

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
MJPEG_release(struct device *dev)
{
	MJPEG_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver mjpeg_driver =
{
	.probe			= MJPEG_probe,
	.suspend		= MJPEG_suspend,
	.remove 		= MJPEG_remove,
	.resume 		= MJPEG_resume,
	.driver 		=
	{
		.name	= MJPEG_MODULE,
	},
};

static struct platform_device mjpeg_device = {
	.name	= MJPEG_MODULE,
	.id 	= -1,
	.dev	= {
		.release = MJPEG_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void MJPEG_PreInit(void)
{
    /* TODO: do something */
}

int MJPEG_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;
	int			irq_num;

	/* Get the handle of debug output for MJPEG device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_MJPEG_debug_fd = DBG_OPEN( MJPEG_MODULE );
	if ( g_MJPEG_debug_fd < 0 )
	{
		printk("[MJPEG] can't get debug handle\n");	
	}
	else
	{
		OS_DEBUG_EnableModule ( g_MJPEG_debug_fd );
		//OS_DEBUG_EnableModuleByIndex ( g_MJPEG_debug_fd, 0, DBG_COLOR_NONE );
		//OS_DEBUG_EnableModuleByIndex ( g_MJPEG_debug_fd, 1, DBG_COLOR_GREEN );
		OS_DEBUG_EnableModuleByIndex ( g_MJPEG_debug_fd, 2, DBG_COLOR_NONE );
		OS_DEBUG_EnableModuleByIndex ( g_MJPEG_debug_fd, 3, DBG_COLOR_NONE );
	}

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&mjpeg_driver) < 0)
	{
		MJPEG_PRINT("[%s] platform driver register failed\n",MJPEG_MODULE);
	}
	else
	{
		if(platform_device_register(&mjpeg_device))
		{
			platform_driver_unregister(&mjpeg_driver);
			MJPEG_PRINT("[%s] platform device register failed\n",MJPEG_MODULE);
		}
		else
		{
			MJPEG_PRINT("[%s] platform register done\n", MJPEG_MODULE);
		}
	}
#endif

	g_MJPEG_device = (MJPEG_DEVICE_T*)OS_KMalloc( sizeof(MJPEG_DEVICE_T)*MJPEG_MAX_DEVICE );

	if ( NULL == g_MJPEG_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(MJPEG_DEVICE_T)* MJPEG_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_MJPEG_device, 0x0, sizeof(MJPEG_DEVICE_T)* MJPEG_MAX_DEVICE );

	if (g_MJPEG_major)
	{
		dev = MKDEV( g_MJPEG_major, g_MJPEG_minor );
		err = register_chrdev_region(dev, MJPEG_MAX_DEVICE, MJPEG_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_MJPEG_minor, MJPEG_MAX_DEVICE, MJPEG_MODULE );
		g_MJPEG_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register MJPEG device\n" );
		return -EIO;
	}

	/* TODO : initialize your module not specific minor device */

	if ( lx_chip_rev( ) >= LX_CHIP_REV(H13, A0) )
	{
		irq_num = H13_IRQ_ICOD1;
	}
	else
	{
		irq_num = L9_IRQ_ICOD1;
	}
	
	err = request_irq( irq_num, (irq_handler_t)MJPEG_Interrrupt, 0, "DTVSoc2MJPEG", NULL );
	
	if (err)
	{
		MJPEG_TRACE("request_irq IRQ_ICOD1 in %s is failed %d\n", __FUNCTION__, err);
		unregister_chrdev_region(dev, MJPEG_MAX_DEVICE );
		return -EIO;
	}

	MJPEG_PRINT("ICOD1 IRQ registered :%d:\n", irq_num);

	/* END */

	for ( i=0; i<MJPEG_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_MJPEG_major, g_MJPEG_minor+i );
		cdev_init( &(g_MJPEG_device[i].cdev), &g_MJPEG_fops );
		g_MJPEG_device[i].devno		= dev;
		g_MJPEG_device[i].cdev.owner = THIS_MODULE;
		g_MJPEG_device[i].cdev.ops   = &g_MJPEG_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_MJPEG_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding MJPEG device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}

        OS_CreateDeviceClass ( g_MJPEG_device[i].devno, "%s%d", MJPEG_MODULE, i );
	}

	MJPEG_LOCK_INIT();

	/* initialize proc system */
	MJPEG_PROC_Init ( );

	MJPEG_PRINT("MJPEG device initialized\n");

	return 0;
}

void MJPEG_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_MJPEG_major, g_MJPEG_minor );
	int irq_num;

	/* cleanup proc system */
	MJPEG_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<MJPEG_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_MJPEG_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */
	if ( lx_chip_rev( ) >= LX_CHIP_REV(H13, A0) )
	{
		irq_num = H13_IRQ_ICOD1;
	}
	else
	{
		irq_num = L9_IRQ_ICOD1;
	}
	
	free_irq( irq_num, NULL);
	
	OS_Free(gpRegICOD);
	OS_Free(gpRegMJPEG);

	unregister_chrdev_region(dev, MJPEG_MAX_DEVICE );

	OS_Free( g_MJPEG_device );

	MJPEG_PRINT("MJPEG device cleanup\n");

}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for MJPEG device
 *
 */
static int
MJPEG_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    MJPEG_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, MJPEG_DEVICE_T, cdev);

    /* TODO : add your device specific code */
	if ( my_dev->dev_open_count == 0 )
	{
		/* Support only L9 platform */
		if ( lx_chip_rev() >= LX_CHIP_REV(L9,A0) ) { }
		else { return -EIO; }

		if ( _Initialize() != RET_OK ) { return -ENOMEM; }

		OS_InitEvent( &my_dev->stEvent);
	}

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    MJPEG_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for MJPEG device
 *
 */
static int
MJPEG_Close(struct inode *inode, struct file *file)
{
    int				major,minor;
    MJPEG_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, MJPEG_DEVICE_T, cdev);

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
    MJPEG_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for MJPEG device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int
MJPEG_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
{
#else
static long
MJPEG_Ioctl ( struct file *filp, unsigned int cmd, unsigned long arg )
{
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif
    int err = 0, ret = 0;

    MJPEG_DEVICE_T*	my_dev;
    struct cdev*		cdev;

	/*
	 * get current MJPEG device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, MJPEG_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != MJPEG_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > MJPEG_IOC_MAXNR)
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

	//MJPEG_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case LX_MJPEG_IO_SW_RESET:
		{
			MJPEG_LOCK();

			_SW_Reset();
			memset( &my_dev->stHeader, 0, sizeof(LX_MJPEG_HEADER_T) );

			MJPEG_UNLOCK();

			break;
		}

		case LX_MJPEG_IOR_GET_CFG:
		{
			LX_MJPEG_CFG_T*	mjpeg_cfg = MJPEG_GetCfg();

			if ( NULL == mjpeg_cfg ) { ret = RET_ERROR; break; }
			ret = copy_to_user((void __user*)arg, (void *)mjpeg_cfg, sizeof(LX_MJPEG_CFG_T));
			break;
		}

		case LX_MJPEG_IOR_GET_BUFFER_INFO:
		{
			LX_MEM_BUF_T stParam;

			stParam.addr = gMemCfgMjpeg.ui32Memory_base;
			stParam.length = gMemCfgMjpeg.ui32Memory_size;

			ret = copy_to_user((void __user*)arg, (void *)&stParam, sizeof(LX_MEM_BUF_T));
			break;
		}

		case LX_MJPEG_IOW_ENCODE_INIT:
		{
			LX_MJPEG_ENC_INIT_PARAM_T *stInitParam = (LX_MJPEG_ENC_INIT_PARAM_T*)OS_KMalloc(sizeof(LX_MJPEG_ENC_INIT_PARAM_T));
			
			if( stInitParam == NULL ) { ret = -ENOMEM; break; }
			if ( copy_from_user((void *)stInitParam, (void __user *)arg, sizeof(LX_MJPEG_ENC_INIT_PARAM_T)) )
			{
				OS_KFree(stInitParam);
				ret = RET_ERROR;
				break;
			}

			MJPEG_LOCK();

			_SW_Reset();

			memcpy((void *)&my_dev->stImageInfo, (void *)&stInitParam->stImageInfo, sizeof(LX_MJPEG_IMAGE_INFO_T));
			memcpy((void *)&my_dev->stImageBuffer, (void *)&stInitParam->stImageBuf, sizeof(LX_MJPEG_IMAGE_BUF_T));
			my_dev->stOption.eMirroring = stInitParam->stOption.eMirroring;
			my_dev->stOption.eRotation = stInitParam->stOption.eRotation;
			OS_KFree(stInitParam);

			my_dev->ui32InputSize = MJPEG_ENC_Init( &my_dev->stImageInfo, &my_dev->stImageBuffer, &my_dev->stOption,
													 &my_dev->stHeader );
			if ( my_dev->ui32InputSize == 0 )
			{
				ret = -EIO;
			}
			else
			{
				my_dev->ui32OutputSize = 0;
				my_dev->bFirstBlock = TRUE;
			}

			if (ret != RET_OK)
			{
				MJPEG_UNLOCK();
			}

			break;
		}

		case LX_MJPEG_IOW_ENCODE_START:
		{
			UINT32 ui32ReceivedEvent;
			LX_MJPEG_ENC_START_PARAM_T *stEncParam = (LX_MJPEG_ENC_START_PARAM_T*)OS_KMalloc(sizeof(LX_MJPEG_ENC_START_PARAM_T));
			if( stEncParam == NULL )
			{
				ret = -ENOMEM;
				MJPEG_UNLOCK();
				break;
			}

			if ( copy_from_user((void *)stEncParam, (void __user *)arg, sizeof(LX_MJPEG_ENC_START_PARAM_T)) )
			{
				OS_KFree(stEncParam);
				
				ret = RET_ERROR;
				MJPEG_UNLOCK(); 
				break; 
			}

			memcpy((void *)&my_dev->stDataBuffer, (void *)&stEncParam->stDataBuffer, sizeof(LX_MEM_BUF_T) );

			if ( my_dev->bFirstBlock )
			{
				my_dev->bFirstBlock = FALSE;

				OS_ClearEvent(&my_dev->stEvent);
				
				MJPEG_ENC_Start( &my_dev->stDataBuffer );
			}
			else
			{
				ret = OS_RecvEvent( &my_dev->stEvent, MJPEG_EVENT_BBC|MJPEG_EVENT_DONE, &ui32ReceivedEvent, OS_EVENT_RECEIVE_ANY, MJPEG_TIMEOUT );
				if ( ret == RET_OK )
				{
					if ( ui32ReceivedEvent&MJPEG_EVENT_BBC )
					{
						my_dev->ui32OutputSize += MJPEG_ENC_Continue( &my_dev->stDataBuffer );
						_EnableBBC();
					}

					if ( ui32ReceivedEvent&MJPEG_EVENT_DONE )
					{
						my_dev->ui32OutputSize += MJPEG_ENC_End();
						ret = -EIO;
					}
				}
			}

			OS_KFree(stEncParam);

			if (ret != RET_OK)
			{
				MJPEG_UNLOCK();
			}

			break;
		}

		case LX_MJPEG_IOR_ENCODE_STOP:
		{
			LX_MJPEG_ENC_STOP_PARAM_T *stStopParam;

			if ( my_dev->ui32OutputSize == 0 )
			{
				ret = -EIO;
				MJPEG_UNLOCK();
				break;
			}

			stStopParam = (LX_MJPEG_ENC_STOP_PARAM_T*)OS_KMalloc(sizeof(LX_MJPEG_ENC_STOP_PARAM_T));
			if( stStopParam == NULL )
			{
				ret = -ENOMEM;
				MJPEG_UNLOCK();
				break;
			};

			memcpy( (void *)&stStopParam->stHeader, (void *)&my_dev->stHeader, sizeof(LX_MJPEG_HEADER_T) );
			stStopParam->ui32Length = my_dev->ui32OutputSize;

			ret = copy_to_user((void __user*)arg, (void *)stStopParam, sizeof(LX_MJPEG_ENC_STOP_PARAM_T));
			OS_KFree(stStopParam);

			MJPEG_UNLOCK();

			break;
		}

		case LX_MJPEG_IOW_DECODE_INIT:
		{
			LX_MJPEG_DEC_INIT_PARAM_T *stInitParam = (LX_MJPEG_DEC_INIT_PARAM_T*)OS_KMalloc(sizeof(LX_MJPEG_DEC_INIT_PARAM_T));
			if( stInitParam == NULL ) { ret = -ENOMEM; break; };
			ret = copy_from_user((void *)stInitParam, (void __user *)arg, sizeof(LX_MJPEG_DEC_INIT_PARAM_T));
			if( ret != RET_OK )
			{
				OS_KFree(stInitParam);
				break;
			}

			MJPEG_LOCK();

			_SW_Reset();

			memcpy((void *)&my_dev->stHeader, (void *)&stInitParam->stHeader, sizeof(LX_MJPEG_HEADER_T));
			memcpy((void *)&my_dev->stImageBuffer, (void *)&stInitParam->stImageBuf, sizeof(LX_MJPEG_IMAGE_BUF_T));
			memcpy((void *)&my_dev->stOption, &stInitParam->stOption, sizeof(LX_MJPEG_OPTION_T));
			OS_KFree(stInitParam);

			my_dev->ui32OutputSize = MJPEG_DEC_Init( &my_dev->stHeader, &my_dev->stImageBuffer, &my_dev->stOption,
													&my_dev->stImageInfo );

			if ( my_dev->ui32OutputSize == 0  )
			{
				MJPEG_PRINT("Can't calculate output image size\n");
				ret = -EIO;
				MJPEG_UNLOCK();
				break;
			}
/*			else if ( my_dev->ui32OutputSize > my_dev->stOuterStream.mem_buf.length )
			{
				MJPEG_PRINT("Frame buffer overflow : need %d bytes\n", my_dev->ui32OutputSize );
				ret = -ENOMEM;
				break;
			}
*/
			my_dev->ui32InputSize = 0;
			my_dev->bFirstBlock = TRUE;
			break;
		}

		case LX_MJPEG_IOW_DECODE_START:
		{
			UINT32 ui32ReceivedEvent;
			LX_MJPEG_DEC_START_PARAM_T *stDecParam = (LX_MJPEG_DEC_START_PARAM_T*)OS_KMalloc(sizeof(LX_MJPEG_DEC_START_PARAM_T));
			if( stDecParam == NULL )
			{
				ret = -ENOMEM;
				MJPEG_UNLOCK();
				break;
			}

			ret  = copy_from_user((void *)stDecParam, (void __user *)arg, sizeof(LX_MJPEG_DEC_START_PARAM_T));
			if( ret != RET_OK ) 
			{ 
				OS_KFree(stDecParam);
				MJPEG_UNLOCK(); 
				break; 
			}

			memcpy((void *)&my_dev->stDataBuffer, (void *)&stDecParam->stDataBuffer, sizeof(LX_MEM_BUF_T));
			my_dev->ui32InputSize += stDecParam->ui32DataLength;


			if ( my_dev->bFirstBlock )
			{
				my_dev->bFirstBlock = FALSE;

				OS_ClearEvent(&my_dev->stEvent);
				
				MJPEG_DEC_Start( &my_dev->stDataBuffer, stDecParam->ui32DataLength, stDecParam->bEndOfStream  );
			}
			else
			{
				ret = OS_RecvEvent( &my_dev->stEvent, MJPEG_EVENT_BBC|MJPEG_EVENT_DONE, &ui32ReceivedEvent, OS_EVENT_RECEIVE_ANY, MJPEG_TIMEOUT );
				if ( ret == RET_OK )
				{
					if ( ui32ReceivedEvent&MJPEG_EVENT_BBC )
					{
						MJPEG_DEC_Continue( &my_dev->stDataBuffer, stDecParam->ui32DataLength, stDecParam->bEndOfStream );
						_EnableBBC();
					}

					if ( ui32ReceivedEvent&MJPEG_EVENT_DONE )
					{
#if 0
						MJPEG_RdFL(gbu_tt_cnt_low);
						ret = MJPEG_Rd(gbu_tt_cnt_low);
#else
						ret = 1;	// success
#endif
					}
				}
				else
				{
					MJPEG_UNLOCK();
				}
			}

			OS_KFree(stDecParam);
			
			break;
		}

		case LX_MJPEG_IOR_DECODE_STOP:
		{
			UINT32 ui32ReceivedEvent;
			LX_MJPEG_DEC_STOP_PARAM_T *stStopParam;

			stStopParam = (LX_MJPEG_DEC_STOP_PARAM_T*)OS_KMalloc(sizeof(LX_MJPEG_DEC_STOP_PARAM_T));
			if( stStopParam == NULL ) { ret = -ENOMEM; MJPEG_UNLOCK(); break; }

			ret = OS_RecvEvent( &my_dev->stEvent, MJPEG_EVENT_DONE, &ui32ReceivedEvent, OS_EVENT_RECEIVE_ANY, MJPEG_TIMEOUT );
			if ( ret == RET_OK )
			{
				memcpy( (void *)&stStopParam->stImageInfo, (void *)&my_dev->stImageInfo, sizeof(LX_MJPEG_IMAGE_INFO_T) );
			}

			ret = copy_to_user((void __user*)arg, (void *)stStopParam, sizeof(LX_MJPEG_DEC_STOP_PARAM_T));
			OS_KFree(stStopParam);

			MJPEG_UNLOCK();

			break;
		}

		case LX_MJPEG_IOR_DECODE_SEQUENCE_INIT:
		{
			LX_MEM_BUF_T stRemapBuf;
			UINT8 ui8CheckList = 0;
			LX_MJPEG_DEC_SEQ_PARAM_T *stSeqParam = (LX_MJPEG_DEC_SEQ_PARAM_T *)OS_KMalloc(sizeof(LX_MJPEG_DEC_SEQ_PARAM_T));
			
			if( stSeqParam == NULL ) { ret = -ENOMEM; break; };

			if ( copy_from_user((void *)stSeqParam, (void __user *)arg, sizeof(LX_MJPEG_DEC_SEQ_PARAM_T)) )
			{
				OS_KFree(stSeqParam);
				break;
			}

			memcpy((void *)&my_dev->stDataBuffer, (void *)&stSeqParam->stDataBuffer, sizeof(LX_MEM_BUF_T));
			memset( stSeqParam, 0, sizeof(LX_MJPEG_DEC_SEQ_PARAM_T) );

			stRemapBuf.addr = (UINT32)ioremap(my_dev->stDataBuffer.addr, my_dev->stDataBuffer.length);
			stRemapBuf.length = my_dev->stDataBuffer.length;

			if ( stRemapBuf.addr == 0 )
			{
				OS_KFree(stSeqParam);
				MJPEG_PRINT("Remap Error\n");
				break;
			}

			stSeqParam->ui32Length = MJPEG_HDR_Decode(&stRemapBuf, &stSeqParam->stHeader, &ui8CheckList);
			ret = copy_to_user((void __user*)arg, (void *)stSeqParam, sizeof(LX_MJPEG_DEC_SEQ_PARAM_T));

			if( stSeqParam->ui32Length > 0 )
			{
				if ( (ui8CheckList & 0x1B) != 0x1B ) // DRI
				{
						MJPEG_PRINT("Header size error 0x%X\n", ui8CheckList);
						ret = -EAGAIN;
				}
			}
			else { ret = -EIO; }

			iounmap((void*)stRemapBuf.addr);
			OS_KFree(stSeqParam);
			break;
		}

	    default:
	    {
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
    }

    return ret;
}

/**
 * memory mapping to virtual region
 *
 */
static int
MJPEG_mmap(struct file *file, struct vm_area_struct *vma)
{
    int ret;
    UINT32 start;
    UINT32 len;
    UINT32 off = ((vma->vm_pgoff) << PAGE_SHIFT);

	start = gMemCfgMjpeg.ui32Memory_base & PAGE_MASK;
	len = PAGE_ALIGN((start & ~PAGE_MASK) + gMemCfgMjpeg.ui32Memory_size);

	MJPEG_PRINT("MMAP : start - %08x , len - %08x , off - %08x\n" , start , len , off);

    if ((vma->vm_end - vma->vm_start + off) > len)
    {
        MJPEG_TRACE("ERROR : MJPEG_mmap leng is over\n");
        MJPEG_PRINT("start : %x end : %x offset : %x len : %x\n" , (UINT32)vma->vm_start , (UINT32)vma->vm_end , off , len);
        return RET_INVALID_PARAMS;
    }

    off += start;
    MJPEG_PRINT("%s:%d -- mmap : start - %08x , len - %08x , off - %08x\n", __F__, __L__, start , len , (UINT32)vma->vm_pgoff);

    vma->vm_pgoff = off >> PAGE_SHIFT;
    vma->vm_flags |= VM_IO;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

    ret = io_remap_pfn_range(vma,   vma->vm_start, off >> PAGE_SHIFT,
                                    vma->vm_end - vma->vm_start,
                                    vma->vm_page_prot );

    return ret;
}


/**
 * interrupt handler for MJPEG device.
 *
 */
irqreturn_t MJPEG_Interrrupt(int i_iIrq, void *pDevId, struct pt_regs *pstRegs)
{
	BOOLEAN eStatus;

	MJPEG_RdFL( pic_status );

	MJPEG_Rd01( pic_status, jpeg_done, eStatus );
	if ( eStatus )
	{
		OS_SendEvent( &g_MJPEG_device->stEvent, MJPEG_EVENT_DONE );
		MJPEG_Wr01( pic_status, jpeg_done, 1 );
		MJPEG_PRINT("Interrupt : [Done]\n");
	}

	MJPEG_Rd01( pic_status, jpeg_error, eStatus );
	if ( eStatus )
	{
		OS_SendEvent( &g_MJPEG_device->stEvent, MJPEG_EVENT_ERROR );
		MJPEG_Wr01( pic_status, jpeg_error, 1 );
		MJPEG_PRINT("Interrupt : [ERROR]\n");
	}

	MJPEG_Rd01( pic_status, bbc_interrupt, eStatus );
	if ( eStatus )
	{
		OS_SendEvent( &g_MJPEG_device->stEvent, MJPEG_EVENT_BBC );
		_DisableBBC();
		MJPEG_Wr01( pic_status, bbc_interrupt, 0 );
		MJPEG_PRINT("Interrupt : [BBC WAIT]\n");
	}

	MJPEG_Rd01( pic_status, jpeg_overflow, eStatus );
	if ( eStatus )
	{
		MJPEG_Wr01( pic_status, jpeg_overflow, 1 );
		MJPEG_PRINT("Interrupt : [OVERFLOW]\n");
	}


	MJPEG_WrFL( pic_status );

	return IRQ_HANDLED;
}

/**
 * Software reset for MJPEG device.
 *
 */
static void
_SW_Reset(void)
{
	BOOLEAN bResetStatus;
//	memset((void *)&g_MJPEG_device->stImageInfo, 0, sizeof(LX_MEM_STREAM_T));

	ICOD_RdFL ( sw_rst );
	ICOD_Wr01 ( sw_rst, sw_rst_mjpeg, 1 );
	ICOD_WrFL ( sw_rst );
	do
	{
		ICOD_RdFL ( sw_rst );
		ICOD_Rd01 ( sw_rst, sw_rst_status_mjpeg, bResetStatus );
	} while( bResetStatus != 0 );
}

/**
 * Shadow register Initialize for MJPEG device.
 *
 */
static SINT32
_Initialize(void)
{
	LX_ADDR_SW_CFG_T	addr_sw_cfg_icod;
	UINT32 MJPEG_REG_BASE, ICODTOP_REG_BASE;
	UINT32 ICOD_REG_BASE, ICOD_REG_SIZE;
	UINT32 ICOD_REG_VIRT;
	
	if ( lx_chip_rev( ) >= LX_CHIP_REV(H13, A0) )
	{
		MJPEG_REG_BASE = ( H13_IOCD_BASE + 0x0000 );
		ICODTOP_REG_BASE = ( H13_IOCD_BASE + 0x0C00 );
		ICOD_REG_BASE = H13_IOCD_BASE;
		ICOD_REG_SIZE = 0x1000;
	}
	else
	{
		MJPEG_REG_BASE = ( L9_IOCD_BASE + 0x0000 );
		ICODTOP_REG_BASE = ( L9_IOCD_BASE + 0x0C00 );
		ICOD_REG_BASE = L9_IOCD_BASE;
		ICOD_REG_SIZE = 0x1000;
	}

	ICOD_REG_VIRT = (volatile void *)ioremap( ICOD_REG_BASE, ICOD_REG_SIZE );

#if 0
	gpRealRegICOD = (volatile ICOD_REG_T*) ioremap(ICODTOP_REG_BASE, sizeof(ICOD_REG_T));
	gpRegICOD = (ICOD_REG_T*)OS_KMalloc(sizeof(ICOD_REG_T));
	gpRealRegMJPEG = (volatile MJPEG_REG_T*) ioremap(MJPEG_REG_BASE, sizeof(MJPEG_REG_T));
	gpRegMJPEG = (MJPEG_REG_T*)OS_KMalloc(sizeof(MJPEG_REG_T));
#else
	gpRealRegICOD = (volatile ICOD_REG_T*) (ICOD_REG_VIRT + 0x0C00);
	gpRegICOD = (ICOD_REG_T*)OS_KMalloc(sizeof(ICOD_REG_T));

	gpRealRegMJPEG = (volatile MJPEG_REG_T*) (ICOD_REG_VIRT + 0x0 );
	gpRegMJPEG = (MJPEG_REG_T*)OS_KMalloc(sizeof(MJPEG_REG_T));
#endif

	if ( gpRegICOD == NULL )
	{
		MJPEG_PRINT("Shadow register memory allocation error\n");
		return RET_ERROR;
	}

	if ( gpRegMJPEG == NULL )
	{
		MJPEG_PRINT("Shadow register memory allocation error\n");
		OS_Free(gpRegICOD);
		return RET_ERROR;
	}

	memset( gpRegICOD, 0x0, sizeof(ICOD_REG_T));
	memset( gpRegMJPEG, 0x0, sizeof(MJPEG_REG_T));

	// Address switching
	if ( lx_chip_rev( ) >= LX_CHIP_REV(H13, A0) )
	{
		// H13 관련 코드
		
	}
	else
	{
		// L9 관련 코드
		BASE_L9_GetAddrSwCfg ( ADDR_SW_CFG_ICOD, &addr_sw_cfg_icod);
		
		ICOD_Wr  ( addr_sw_de_sav, addr_sw_cfg_icod.de_sav );
		ICOD_Wr  ( addr_sw_cpu_gpu, addr_sw_cfg_icod.cpu_gpu );
		ICOD_Wr  ( addr_sw_cpu_shadow, addr_sw_cfg_icod.cpu_shadow );
		
		ICOD_WrFL( addr_sw_de_sav );
		ICOD_WrFL( addr_sw_cpu_gpu );
		ICOD_WrFL( addr_sw_cpu_shadow );
	}

//	g_MJPEG_device->stInnerStream.mem_buf.addr	 = gMemCfgMjpeg.ui32Memory_base;
//	g_MJPEG_device->stInnerStream.mem_buf.length = gMemCfgMjpeg.ui32Memory_size;
//	g_MJPEG_device->stInnerStream.curr_offset = 0;

	MJPEG_PRINT("mjpeg device initialized");

	return RET_OK;
}

/**
 * Disable BBC interrupt.
 *
 */
static void
_DisableBBC(void)
{
	MJPEG_RdFL( intr_mask );
	MJPEG_Wr01( intr_mask, bbc_interrupt, 1 );
	MJPEG_WrFL( intr_mask );
}

/**
 * Enable BBC interrupt.
 *
 */
static void
_EnableBBC(void)
{
	MJPEG_RdFL( pic_status );
	MJPEG_Wr01( pic_status, bbc_interrupt, 1 );
	MJPEG_WrFL( pic_status );

	MJPEG_RdFL( intr_mask );
	MJPEG_Wr01( intr_mask, bbc_interrupt, 0 );
	MJPEG_WrFL( intr_mask );
}


///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",MJPEG_Init);
#else
module_init(MJPEG_Init);
#endif
module_exit(MJPEG_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("mjpeg driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

