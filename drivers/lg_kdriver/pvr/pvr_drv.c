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
 *  main driver implementation for pvr device.
 *	pvr device will teach you how to make device driver with new platform.
 *
 *  author		murugan.d (murugan.d@lge.com)
 *  version		1.0
 *  date		2010.02.05
 *  note		Additional information.
 *
 *  @addtogroup lg1150_pvr
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_PVR_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include <linux/version.h>

#include "os_util.h"
#include "base_device.h"
#include "pvr_drv.h"
#include "pvr_dev.h"
#include "pvr_reg.h"
#include "pvr_core_api.h"

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
 *	main control block for pvr device.
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
PVR_DEVICE_T;

#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}PVR_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	PVR_PROC_Init(void);
extern	void	PVR_PROC_Cleanup(void);
irqreturn_t DVR_interrupt(int irq, void *dev_id, struct pt_regs *regs);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern DVR_STATE_T	astDvrState[];
extern DVR_BUFFER_STATE_T	astDvrBufferState[];
extern DVR_MOD_T astDvrControl[];
extern DVR_PIE_DATA_T astDvrPieData[];
extern DVR_ErrorStatus_T astDvrErrStat[];



/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		PVR_Init(void);
void	PVR_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_pvr_debug_fd = -1;
int 	g_pvr_major = PVR_MAJOR;
int 	g_pvr_minor = PVR_MINOR;

extern LX_PVR_STREAMINFO_T gStreamInfo;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int      PVR_Open(struct inode *, struct file *);
static int      PVR_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int PVR_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long PVR_Ioctl (struct file *filp, unsigned int cmd, unsigned long arg );
#endif
#ifdef SUPPORT_PVR_DEVICE_READ_WRITE_FOPS
static ssize_t  PVR_Read(struct file *, char *, size_t, loff_t *);
static ssize_t  PVR_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for pvr device
*/
static PVR_DEVICE_T*		g_pvr_device;

/**
 * file I/O description for pvr device
 *
*/
static struct file_operations g_pvr_fops =
{
	.open 	= PVR_Open,
	.release= PVR_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= PVR_Ioctl,
#else
	.unlocked_ioctl	= PVR_Ioctl,
#endif
#ifdef SUPPORT_PVR_DEVICE_READ_WRITE_FOPS
	.read 	= PVR_Read,
	.write 	= PVR_Write,
#else
	.read	= NULL,
	.write	= NULL,
#endif
};

static UINT32 ui32PvrDefaultPktCount = 0x80;

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
static int PVR_suspend(struct platform_device *pdev, pm_message_t state)
{
	PVR_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	PVR_PRINT("[%s] Memorizing reg content\n", PVR_MODULE);

	if ( drv_data->is_suspended == 1 )
	{
		return -1;	//If already in suspend state, so ignore
	}

	// add here the suspend code

	drv_data->is_suspended = 1;
	printk("[%s] done suspend\n", PVR_MODULE);
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
static int PVR_resume(struct platform_device *pdev)
{
	PVR_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	PVR_PRINT("[%s] Restoring reg content\n", PVR_MODULE);

	if(drv_data->is_suspended == 0) return -1;

	// add here the resume code

	drv_data->is_suspended = 0;
	printk("[%s] done resume\n", PVR_MODULE);
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
 int  PVR_probe(struct platform_device *pdev)
{

	PVR_DRVDATA_T *drv_data;

	drv_data = (PVR_DRVDATA_T *)kmalloc(sizeof(PVR_DRVDATA_T) , GFP_KERNEL);

	// add here driver registering code & allocating resource code

	PVR_PRINT("[%s] done probe\n", PVR_MODULE);
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
static int  PVR_remove(struct platform_device *pdev)
{
	PVR_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	PVR_PRINT("released\n");

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
static void  PVR_release(struct device *dev)
{


	PVR_PRINT("device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver pvr_driver =
{
	.probe          = PVR_probe,
	.suspend        = PVR_suspend,
	.remove         = PVR_remove,
	.resume         = PVR_resume,
	.driver         =
	{
		.name   = PVR_MODULE,
	},
};

static struct platform_device pvr_device = {
	.name = PVR_MODULE,
	.id = 0,
	.id = -1,
	.dev = {
		.release = PVR_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void PVR_PreInit(void)
{
    /* TODO: do something */
}

int PVR_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for pvr device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_pvr_debug_fd = DBG_OPEN( PVR_MODULE );

	if ( g_pvr_debug_fd >= 0 )
	{
		OS_DEBUG_EnableModule ( g_pvr_debug_fd );
	//	OS_DEBUG_EnableModuleByIndex ( g_pvr_debug_fd, 0, DBG_COLOR_UL_YELLOW );
	//	OS_DEBUG_EnableModuleByIndex ( g_pvr_debug_fd, 1, DBG_COLOR_NONE );
	//	OS_DEBUG_EnableModuleByIndex ( g_pvr_debug_fd, 2, DBG_COLOR_NONE );
	//	OS_DEBUG_EnableModuleByIndex ( g_pvr_debug_fd, 3, DBG_COLOR_NONE );
	}

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&pvr_driver) < 0)
	{
		PVR_PRINT("[%s] platform driver register failed\n",PVR_MODULE);

	}
	else
	{
		if(platform_device_register(&pvr_device))
		{
			platform_driver_unregister(&pvr_driver);
			PVR_PRINT("[%s] platform device register failed\n",PVR_MODULE);
		}
		else
		{
			PVR_PRINT("[%s] platform register done\n", PVR_MODULE);
		}


	}
#endif

	g_pvr_device = (PVR_DEVICE_T*)OS_KMalloc( sizeof(PVR_DEVICE_T)*PVR_MAX_DEVICE );

	if ( NULL == g_pvr_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(PVR_DEVICE_T)* PVR_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_pvr_device, 0x0, sizeof(PVR_DEVICE_T)* PVR_MAX_DEVICE );

	if (g_pvr_major)
	{
		dev = MKDEV( g_pvr_major, g_pvr_minor );
		err = register_chrdev_region(dev, PVR_MAX_DEVICE, PVR_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_pvr_minor, PVR_MAX_DEVICE, PVR_MODULE );
		g_pvr_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register pvr device\n" );
		return -EIO;
	}

	DVR_RegInit();

	/* TODO : initialize your module not specific minor device */
    if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if (request_irq(H13_IRQ_DVR,(irq_handler_t)DVR_interrupt,0,"DTVSoC2DVR", NULL)) {
			PVR_PRINT("request_irq in %s is failed\n", __FUNCTION__);
			return -1;
		}
		PVR_PRINT ( "Inserting DVR IRQ[%d] Success\n", H13_IRQ_DVR );		
	} 
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
	{
		if (request_irq(L9_IRQ_DVR,(irq_handler_t)DVR_interrupt,0,"DTVSoC2DVR", NULL)) {
			PVR_PRINT("request_irq in %s is failed\n", __FUNCTION__);
			return -1;
		}
	}
	else
	{
		if (request_irq(L8_IRQ_DVR,(irq_handler_t)DVR_interrupt,0,"DTVSoC2DVR", NULL)) {
			PVR_PRINT("request_irq in %s is failed\n", __FUNCTION__);
			return -1;
		}
	}


	/* END */

	for ( i=0; i<PVR_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_pvr_major, g_pvr_minor+i );
		cdev_init( &(g_pvr_device[i].cdev), &g_pvr_fops );
		g_pvr_device[i].devno		= dev;
		g_pvr_device[i].cdev.owner = THIS_MODULE;
		g_pvr_device[i].cdev.ops   = &g_pvr_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_pvr_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding pvr device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_pvr_device[i].devno, "%s%d", PVR_MODULE, i );
	}

	/* initialize proc system */
	PVR_PROC_Init ( );

	PVR_PRINT("pvr device initialized\n");

	return 0;
}

void PVR_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_pvr_major, g_pvr_minor );

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&pvr_driver);
	platform_device_unregister(&pvr_device);
#endif

	/* cleanup proc system */
	PVR_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<PVR_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_pvr_device[i].cdev) );
	}

	/* TODO : cleanup your module not specific minor device */

	unregister_chrdev_region(dev, PVR_MAX_DEVICE );

	OS_Free( g_pvr_device );
}


UINT32 DVR_DEV_Install ( void )
{
	PVR_PRINT("device install success\n" );
	return 0;
}

UINT32 DVR_DEV_UnInstall ( void )
{
	PVR_PRINT("device un-install success\n" );
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for pvr device
 *
 */
static int
PVR_Open(struct inode *inode, struct file *filp)
{
    int					major,minor;
    struct cdev*    	cdev;
    PVR_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, PVR_DEVICE_T, cdev);

    /* TODO : add your device specific code */

    if ( my_dev->dev_open_count == 0 )
    {
		/* Device initializations only for the first time */
		DVR_DEV_Install ( );
    }
	/* END */

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    PVR_PRINT("device opened (%d:%d)\n", major, minor );

    return 0;
}

/**
 * release handler for pvr device
 *
 */
static int
PVR_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    PVR_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, PVR_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */

	if (my_dev->dev_open_count == 0)
	{
		/* Last device handle, so close the device */
		DVR_DEV_UnInstall();
	}

	/* END */


	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    PVR_PRINT("device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for pvr device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int PVR_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long PVR_Ioctl (struct file *filp, unsigned int cmd, unsigned long arg )
#endif
{
	int err = 0, ret = 0;

	PVR_DEVICE_T*	my_dev;
	struct cdev*		cdev;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current pvr device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, PVR_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != PVR_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > PVR_IOC_MAXNR)
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

//	PVR_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case PVR_IOW_PANIC:
			{
				LX_PVR_PANIC_T stPanic;

				if (copy_from_user(&stPanic, (void __user *)arg, sizeof(LX_PVR_PANIC_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}
				
				panic("[MARINE] PVR PANIC!! Addr(0x%x) BitPos(0x%x) DataSize(%d) bitSize(0x%x)", stPanic.dataaddress, stPanic.startBitPos, stPanic.dataSize, stPanic.bitSize);
				break;
			}
			
		case PVR_IOW_INIT:
			{
				LX_PVR_CH_T eCh;

				if (copy_from_user(&eCh, (void __user *)arg, sizeof(LX_PVR_CH_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				PVR_DD_Init ( eCh );
				PVR_TRACE("PVR_IOW_INIT ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_TERMINATE:
			{
				PVR_DD_Terminate ( );
				PVR_TRACE("PVR_IOW_TERMINATE ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_DN_START:
			{
				LX_PVR_START_T	stDnStart;
				if (copy_from_user(&stDnStart, (void __user *)arg, sizeof(LX_PVR_START_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if ( stDnStart.ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}

				if ( stDnStart.bStart )
				{
					ret = PVR_DD_StartDownload ( stDnStart.ePVRCh );
					PVR_TRACE("PVR_IOW_DN_START ok\n");
				}
				else
				{
					ret = PVR_DD_StopDownload ( stDnStart.ePVRCh );
					PVR_TRACE("PVR_IOW_DN_STOP ok\n");
				}
			}
			break;

		case PVR_IOW_DN_SET_BUF:
			{
				LX_PVR_SET_BUFFER_T	stSetBuf;
				if (copy_from_user(&stSetBuf, (void __user *)arg, sizeof(LX_PVR_SET_BUFFER_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}
				//Sanity check
				if ( stSetBuf.ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}
				PVR_DD_SetDownloadbuffer ( stSetBuf.ePVRCh, stSetBuf.uiBufAddr, stSetBuf.uiBufSize);

				PVR_TRACE("PVR_IOW_DN_SET_BUF ok\n");
				ret = 0;
			}
			break;

		case PVR_IOR_DN_GET_WRITE_ADD:
			{
				LX_PVR_DN_GET_WRITE_ADD_T	stGetWriteBuf;
				UINT32	ch = 0, ui32CurBufOffset = 0, ui32ClipBufSize = 0;

				if (copy_from_user(&stGetWriteBuf, (void __user *)arg, sizeof(LX_PVR_DN_GET_WRITE_ADD_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if ( stGetWriteBuf.ePVRCh > LX_PVR_CH_MAX )
				{
					PVR_PRINT("ioctl: Sanity check Error !!! \n");
					return -EFAULT;
				}

				ch = stGetWriteBuf.ePVRCh;
				PVR_DD_GetDownloadWriteAddr (
					ch,
					&stGetWriteBuf.streamBuffer.uiWriteAddr );

				ui32CurBufOffset = stGetWriteBuf.streamBuffer.uiWriteAddr - astDvrMemMap[ch].stDvrDnBuff.ui32BufferBase;
				ui32ClipBufSize = ui32CurBufOffset %(ui32PvrDefaultPktCount * 192);

				stGetWriteBuf.streamBuffer.uiWriteAddr = stGetWriteBuf.streamBuffer.uiWriteAddr - ui32ClipBufSize;
				stGetWriteBuf.streamBuffer.eStatus = astDvrBufferState[ch].eDnBufState;
				/* Update the DVR overflow status */
				if ( astDvrBufferState[ch].eDnBufState == LX_PVR_BUF_STAT_Full)
				{
					PVR_PRINT ( "PVR_DRV %d> Overflow detected !!Unit_Buf[%d] Overflow[%d]\n",
						__LINE__,
						astDvrErrStat[ch].ui32DnUnitBuf,
						astDvrErrStat[ch].ui32DnOverFlowErr );
					/* Reset the buffer state to normal */
					astDvrBufferState[ch].eDnBufState = LX_PVR_BUF_STAT_Ready;
				}

				if (copy_to_user( (LX_PVR_DN_GET_WRITE_ADD_T *)arg,	&stGetWriteBuf,	sizeof(LX_PVR_DN_GET_WRITE_ADD_T)))
				{
					PVR_PRINT("ioctl: copy_to_user error !!! \n");
					return -EFAULT;
				}

				//PVR_TRACE("PVR_IOR_DN_GET_WRITE_ADD ok\n");
				ret = 0;
			}
			break;

		case PVR_IOR_GET_STREAM_INFO:
			{
				LX_PVR_STREAMINFO_T		stGetStreamInfo;

				if (copy_from_user(&stGetStreamInfo, (void __user *)arg, sizeof(LX_PVR_STREAMINFO_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				stGetStreamInfo.bFoundSeqSPS	= gStreamInfo.bFoundSeqSPS;
				stGetStreamInfo.bitRate			= gStreamInfo.bitRate;
				stGetStreamInfo.frRate			= gStreamInfo.frRate;

				if (copy_to_user( (LX_PVR_STREAMINFO_T *)arg, &stGetStreamInfo,	sizeof(LX_PVR_STREAMINFO_T)))
				{
					PVR_PRINT("ioctl: copy_to_user error !!! \n");
					return -EFAULT;
				}
				ret = 0;
			}
			break;

			/*
			 * To set the user read pointer for Download stream and index buffers
			 */
		case PVR_IOW_DN_SET_CONFIG:
			{
				LX_PVR_DN_SET_READ_ADD_T	stSetReadAddr;
				UINT32	ch;

				if (copy_from_user(&stSetReadAddr, (void __user *)arg, sizeof(LX_PVR_DN_SET_READ_ADD_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if ( (stSetReadAddr.ePVRCh > LX_PVR_CH_MAX ) || (stSetReadAddr.streamBuffer.uiReadAddr == 0) )
				{
					return -EFAULT;
				}
				ch = stSetReadAddr.ePVRCh;
				PVR_DD_SetDownloadReadAddr (
					ch,
					stSetReadAddr.streamBuffer.uiReadAddr );

				PVR_DD_SetPieReadAddr(ch,
					stSetReadAddr.indexBuffer.uiReadAddr );
				
				/* 2012. 12. 22 jinhwan.bae Change from mmaped virtual to physical. Pie Buffer Setting in Kdriver should be ioremapped address, deleted mmaped address operation */
#if 0
				astDvrMemMap[ch].stPieUserVirtBuff.ui32WritePtr = stSetReadAddr.indexBuffer.uiWriteAddr;
#else
				astDvrMemMap[ch].stPiePhyBuff.ui32WritePtr = stSetReadAddr.indexBuffer.uiWriteAddr;
				astDvrMemMap[ch].stPieMappedBuff.ui32WritePtr = stSetReadAddr.indexBuffer.uiWriteAddr + astDvrMemMap[ch].si32PieVirtOffset;
#endif

				PVR_TRACE("PVR_IOW_DN_SET_CONFIG ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_PIE_START:
			{
				PVR_TRACE("PVR_IOW_PIE_START ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_PIE_SET_BUF:
			{
				LX_PVR_SET_BUFFER_T	stSetBuf;
				if (copy_from_user(&stSetBuf, (void __user *)arg, sizeof(LX_PVR_SET_BUFFER_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if ( (stSetBuf.ePVRCh > LX_PVR_CH_MAX ) || (stSetBuf.uiBufAddr == 0) )
				{
					return -EFAULT;
				}
				ret = PVR_DD_SetPiebuffer ( stSetBuf.ePVRCh, stSetBuf.uiBufAddr, stSetBuf.uiBufSize);

				/* 2012. 12. 22 jinhwan.bae Change from mmaped virtual to physical. Pie Buffer Setting in Kdriver should be ioremapped address, deleted mmaped address operation */
#if 0
				PVR_PRINT ( "PIE (%c)> Buffer B[0x%08X] Size[0x%04X] E[0x%08X]\n",
					stSetBuf.ePVRCh ? 'B' : 'A',
					astDvrMemMap[stSetBuf.ePVRCh].stPieUserVirtBuff.ui32BufferBase,
					stSetBuf.uiBufSize,
					astDvrMemMap[stSetBuf.ePVRCh].stPieUserVirtBuff.ui32BufferEnd );
#else
				PVR_PRINT ( "PIE (%c)> Buffer B[0x%08X] Size[0x%04X] E[0x%08X]\n",
					stSetBuf.ePVRCh ? 'B' : 'A',
					astDvrMemMap[stSetBuf.ePVRCh].stPiePhyBuff.ui32BufferBase,
					stSetBuf.uiBufSize,
					astDvrMemMap[stSetBuf.ePVRCh].stPiePhyBuff.ui32BufferEnd );
#endif

				PVR_TRACE("PVR_IOW_PIE_SET_BUF ok\n");
			}
			break;

		case PVR_IOW_PIE_SET_PID:
			{
				LX_PVR_PIE_SET_PID_T	stSetPid;

				if (copy_from_user(&stSetPid, (void __user *)arg, sizeof(LX_PVR_PIE_SET_PID_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				astDvrControl[stSetPid.ePVRCh].ui32PieIndex = 0;	//Write index
				astDvrControl[stSetPid.ePVRCh].ui32PieRdIndex = 0;	//Read index
				astDvrControl[stSetPid.ePVRCh].ui32TotalBufCounter = 0;
				astDvrControl[stSetPid.ePVRCh].ui32PrevBufNum = 0;
				astDvrControl[stSetPid.ePVRCh].ui32CurrBufNum = 0;	//Total number of indices-for debugging

				astDvrPieData[stSetPid.ePVRCh].ui32PieWrIndex = 0;

				if ((stSetPid.uiDownChunkPktCount < LX_PVR_DN_MIN_PKT_COUNT) ||
					(stSetPid.uiDownChunkPktCount > LX_PVR_DN_MAX_PKT_COUNT))
				{
					/* If invalid Packet count is passed, then assume the default packet count of 384KB */
					stSetPid.uiDownChunkPktCount = LX_PVR_DN_PKT_COUNT_DEFAULT;
				}

				PVR_PRINT ( "PIE (%c)> Down Chunk packet count[%d] Chunk Size[0x%08X]\n",
					stSetPid.ePVRCh ? 'B' : 'A',
					stSetPid.uiDownChunkPktCount,
					stSetPid.uiDownChunkPktCount * 192 );
				/*
				 * Murugan-18.01.2011 - Configure the chunk size for download and PIE numbering
				 * This value will affect the macro DVR_DN_MIN_BUF_CNT. This macro is used to configure
				 * the PKT_LIM register which control the UNIT_BUFF Interrupt.
				 */
				ui32DvrDnMinPktCount = stSetPid.uiDownChunkPktCount;
//				ui32PvrDefaultPktCount = 0x200;		// Download Chunksize 96KByte(512 * 192)
//				ui32PvrDefaultPktCount = 0x100;		// Download Chunksize 48KByte(256 * 192)
				ui32PvrDefaultPktCount = 0x80;		// Download Chunksize 24KByte(128 * 192)
				ui32DvrDnMinPktCount = ui32PvrDefaultPktCount;

				astDvrControl[stSetPid.ePVRCh].ui32TotalBufCounter =
					(astDvrMemMap[stSetPid.ePVRCh].stDvrDnBuff.ui32BufferEnd -
					astDvrMemMap[stSetPid.ePVRCh].stDvrDnBuff.ui32BufferBase)/(ui32PvrDefaultPktCount * 192);

				PVR_PRINT("ui32LocalBufCounter %d\n", astDvrControl[stSetPid.ePVRCh].ui32TotalBufCounter);

				//Sanity check
				if (stSetPid.ePVRCh > LX_PVR_CH_MAX )
				{
	 	            return -EFAULT;
				}

				DVR_SetDownloadPID(stSetPid.ePVRCh, stSetPid.uiPid, stSetPid.ePidType);
				PVR_PRINT("ePidType %d\n", stSetPid.ePidType);

				if(stSetPid.ePidType == LX_PVR_PIE_TYPE_MPEG2TS)
					astDvrState[stSetPid.ePVRCh].ePieState = LX_PVR_PIE_STATE_MP2;
				else
					astDvrState[stSetPid.ePVRCh].ePieState = LX_PVR_PIE_STATE_GSCD;

				PVR_PRINT("astDvrState[stSetPid.ePVRCh].ePieState %d\n", astDvrState[stSetPid.ePVRCh].ePieState);

				PVR_TRACE("PVR_IOW_PIE_SET_PID ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_PIE_SET_CONFIG:
			{
				PVR_TRACE("PVR_IOW_PIE_SET_CONFIG ok\n");
				ret = 0;
			}
			break;

		case PVR_IOR_PIE_GET_TABLE:
			{
				LX_PVR_PIE_GET_TABLE_T	stGetPieTable;
				UINT32	ui32IndexCnt, ui32Count;
				UINT32	ch;

				UINT32 ui32RawTsRdAddr = 0, ui32RawTsWrAddr = 0, ui32RawTsSize = 0;
				UINT32 ui32DnBufBase = 0, ui32DnBufEnd = 0;
				UINT32 ui32TsOffset = 0, ui32TotalBufCnt = 0;
				UINT32 ui32BaseBufNum = 0, ui32MaxBufCnt = 0, ui32WrapBufCnt = 0;

				if (copy_from_user(&stGetPieTable, (void __user *)arg, sizeof(LX_PVR_PIE_GET_TABLE_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if (stGetPieTable.ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}

				ch = stGetPieTable.ePVRCh;
				stGetPieTable.indexBuffer.eStatus = LX_PVR_BUF_STAT_Empty;

				// get information about TS mermoy addr,size and make virtual memory offset, addr
				ui32RawTsRdAddr = stGetPieTable.tsBuffer.uiReadAddr;
				ui32RawTsWrAddr = stGetPieTable.tsBuffer.uiWriteAddr;
				ui32DnBufBase = astDvrMemMap[ch].stDvrDnBuff.ui32BufferBase;
				ui32DnBufEnd = astDvrMemMap[ch].stDvrDnBuff.ui32BufferEnd;
				ui32TotalBufCnt = astDvrControl[ch].ui32TotalBufCounter;

				if(ui32RawTsRdAddr > ui32RawTsWrAddr) //wrap arround
					ui32RawTsSize = (ui32DnBufEnd - ui32RawTsRdAddr) + (ui32RawTsWrAddr - ui32DnBufBase);
				else
					ui32RawTsSize = ui32RawTsWrAddr - ui32RawTsRdAddr;

				ui32TsOffset = ui32RawTsRdAddr - ui32DnBufBase;

				PVR_PRINT("^G^RdAddr [0x%x][0x%x] Size [0x%x] \n", ui32RawTsRdAddr, ui32RawTsWrAddr, ui32RawTsSize);

				if (astDvrControl[ch].ui32PieIndex == astDvrControl[ch].ui32PieRdIndex)
				{
					//Index buffer empty
					ui32IndexCnt = 0;
				}
				else if (astDvrControl[ch].ui32PieIndex > astDvrControl[ch].ui32PieRdIndex)
				{
					/* Normal condition write ahead of read */
					ui32IndexCnt = astDvrControl[ch].ui32PieIndex - astDvrControl[ch].ui32PieRdIndex;
				}
				else
				{
					/* Wrap around condition */
					ui32IndexCnt = ((PIE_MAX_ENTRIES_LOCAL-1) - astDvrControl[ch].ui32PieRdIndex) + astDvrControl[ch].ui32PieIndex;
				}

				PVR_PRINT("^G^Index[%d]\n", ui32IndexCnt);

				// 다운로드 버퍼사이즈를 기반으로 인덱스를 요청한 메모리 사이즈와 비교하여 매칭한다.
				ui32BaseBufNum = ui32TsOffset/(ui32DvrDnMinPktCount*192);
				ui32MaxBufCnt = ui32BaseBufNum + (ui32RawTsSize/(ui32DvrDnMinPktCount*192));

				if(ui32RawTsSize%(ui32DvrDnMinPktCount*192))  // Added by Soontae Kim
						ui32MaxBufCnt++;

				if(ui32MaxBufCnt > ui32TotalBufCnt)
					ui32WrapBufCnt = ui32MaxBufCnt - ui32TotalBufCnt;

				if ( ui32IndexCnt && ui32RawTsSize )
				{
					PIE_IND_T			*pstPieSrcData;
					PVR_KDRV_INDEX_T	*pstIdx, *pstEnd, *pstBase;
					UINT32				*pstBufNum = NULL;
					UINT32				ui32ByteOffset = 0;
					SINT32 				si32AccCount = 0;
					static	UINT32		preByteOffset = -1;

					/* Destination buffer */
					/* 2012. 12. 22 jinhwan.bae Change from mmaped virtual to physical. Pie Buffer Setting in Kdriver should be ioremapped address, deleted mmaped address operation */
#if 0
					pstIdx = ( PVR_KDRV_INDEX_T *)astDvrMemMap[ch].stPieUserVirtBuff.ui32BufferBase;
					pstEnd = ( PVR_KDRV_INDEX_T *)astDvrMemMap[ch].stPieUserVirtBuff.ui32BufferEnd;
					pstBase = ( PVR_KDRV_INDEX_T *)astDvrMemMap[ch].stPieUserVirtBuff.ui32BufferBase;
#else
					pstIdx = ( PVR_KDRV_INDEX_T *)astDvrMemMap[ch].stPieMappedBuff.ui32BufferBase;
					pstEnd = ( PVR_KDRV_INDEX_T *)astDvrMemMap[ch].stPieMappedBuff.ui32BufferEnd;
					pstBase = ( PVR_KDRV_INDEX_T *)astDvrMemMap[ch].stPieMappedBuff.ui32BufferBase;
#endif

					// Source data
					pstPieSrcData = &astDvrControl[ch].astPieTable[astDvrControl[ch].ui32PieRdIndex];
					pstBufNum = &astDvrControl[ch].astBufTable[astDvrControl[ch].ui32PieRdIndex];

					if( ui32WrapBufCnt && ( *pstBufNum <= ui32WrapBufCnt))
						*pstBufNum = *pstBufNum + ui32TotalBufCnt;

					PVR_PRINT ( "^B^BaseBufNum [%d] MaxBufCnt [%d] pstBufNum [%d]\n", ui32BaseBufNum, ui32MaxBufCnt, *pstBufNum);

					// 인덱스가 가진 버퍼와 받은 버퍼가 다를경우 받은 버퍼와 매칭되는 인덱스를 찾도록 한다
					if((*pstBufNum < ui32BaseBufNum) || (*pstBufNum > ui32MaxBufCnt))
					{
						for ( ui32Count = 0; ui32Count < ui32IndexCnt; ui32Count++)
						{
							if(ui32Count)
							{
								++pstPieSrcData;
								++pstBufNum;
							}

							if( ui32WrapBufCnt && ( *pstBufNum <= ui32WrapBufCnt))
								*pstBufNum = *pstBufNum + ui32TotalBufCnt;

							PVR_PRINT ( "^C^pstBufNum [%d]\n", *pstBufNum);

							if( (*pstBufNum >= ui32BaseBufNum) && (*pstBufNum < ui32MaxBufCnt))
								break;

							--ui32IndexCnt;
							++astDvrControl[ch].ui32PieRdIndex;
							if (astDvrControl[ch].ui32PieRdIndex == PIE_MAX_ENTRIES_LOCAL)
							{
								/* Wrap around */
								astDvrControl[ch].ui32PieRdIndex = 0;
								pstPieSrcData = &astDvrControl[ch].astPieTable[0];
								pstBufNum = &astDvrControl[ch].astBufTable[0];
								PVR_PRINT ( "PVR_DRV %d> Pie Source buffer wrap around\n", __LINE__ );
							}
						}
					}

					for ( ui32Count = 0; ui32Count < ui32IndexCnt; ui32Count++)
					{
						if(ui32Count)
						{
							++pstPieSrcData;
							++pstBufNum;
						}

						if( ui32WrapBufCnt && ( *pstBufNum <= ui32WrapBufCnt))
							*pstBufNum = *pstBufNum + ui32TotalBufCnt;

						if((*pstBufNum >= ui32MaxBufCnt) || (*pstBufNum < ui32BaseBufNum))
						{
							if( *pstBufNum > ui32TotalBufCnt )
								*pstBufNum = *pstBufNum - ui32TotalBufCnt;
							PVR_PRINT("^Y^overflow BufNum %d index %d \n", *pstBufNum, astDvrControl[ch].ui32PieRdIndex);
							break;
						}

						if ( pstPieSrcData->ui32Val & 0x00F00000 )
						{
							si32AccCount = *pstBufNum - ui32BaseBufNum;
							//ui32ByteOffset = ((pstPieSrcData->le.pack_cnt - 1) + (ui32DvrDnMinPktCount * si32AccCount))*192;  // Removed by Soontae Kim
							ui32ByteOffset = ((pstPieSrcData->le.pack_cnt - 1) + (ui32DvrDnMinPktCount * si32AccCount))*192 - ui32TsOffset%(ui32DvrDnMinPktCount*192);  // Modified by Soontae Kim

							if( ui32ByteOffset >= ui32RawTsSize )
							{
								if( *pstBufNum > ui32TotalBufCnt )
									*pstBufNum = *pstBufNum - ui32TotalBufCnt;
								PVR_PRINT("^R^overflow byteoffset 0x%x bufnum %d AccCount %d index %d \n", ui32ByteOffset, *pstBufNum, si32AccCount, astDvrControl[ch].ui32PieRdIndex);
								break;
							}
							else
							{
								// byte offset 을 먼저 체크해보고 Read index를 증가시킨다.
								++astDvrControl[ch].ui32PieRdIndex;
								if (astDvrControl[ch].ui32PieRdIndex == PIE_MAX_ENTRIES_LOCAL)
								{
									/* Wrap around */
									astDvrControl[ch].ui32PieRdIndex = 0;
									pstPieSrcData = &astDvrControl[ch].astPieTable[0];
									pstBufNum = &astDvrControl[ch].astBufTable[0];
									PVR_PRINT ( "PVR_DRV %d> Pie Source buffer wrap around\n", __LINE__ );
								}
							}

							//Total buffer count from beggining
							pstIdx->indexType  = PVR_IDX_NONE;
							pstIdx->byteOffset = ui32ByteOffset;

							if(preByteOffset == ui32ByteOffset)
								continue;
							else
								preByteOffset = ui32ByteOffset;

							if(astDvrState[ch].ePieState == LX_PVR_PIE_STATE_MP2)
							{
								//Assign the Picture index type
								if (pstPieSrcData->le.sdet == 1)
								{
									pstIdx->indexType = PVR_IDX_SEQ;	//SEQ
								}
								if (pstPieSrcData->le.idet == 1)
								{
									/*
									 * The bitwise OR is used when both Sequence header
									 * and I-Pic are present in same packet
									 */
									pstIdx->indexType |= PVR_IDX_I_PIC; //I Picture
								}
								if (pstPieSrcData->le.bdet == 1)
								{
									pstIdx->indexType = PVR_IDX_B_PIC;	//B Picture
								}

								if (pstPieSrcData->le.pdet == 1)
								{
									pstIdx->indexType = PVR_IDX_P_PIC;	//P Picture
								}
							}
							else	//LX_PVR_PIE_STATE_GSCD
							{
								if (pstPieSrcData->le.bdet == 1)
								{
									pstIdx->indexType = PVR_IDX_SEQ;
								}

								if (pstPieSrcData->le.idet == 1)
								{
									switch(pstPieSrcData->le.byte_info)
									{
										case 0x10:
											pstIdx->indexType = PVR_IDX_I_PIC;
											break;
										case 0x30:
											pstIdx->indexType = PVR_IDX_P_PIC;
											break;
										case 0x50:
										default:
											pstIdx->indexType = PVR_IDX_B_PIC;
											break;
									}
								}
							}

							++pstIdx;
							if ( pstIdx == pstEnd)
								pstIdx = pstBase;	//Wrap around handling
						}
						else
						{
							++astDvrControl[ch].ui32PieRdIndex;
							if (astDvrControl[ch].ui32PieRdIndex == PIE_MAX_ENTRIES_LOCAL)
							{
								/* Wrap around */
								astDvrControl[ch].ui32PieRdIndex = 0;
								pstPieSrcData = &astDvrControl[ch].astPieTable[0];
								pstBufNum = &astDvrControl[ch].astBufTable[0];
								PVR_PRINT ( "PVR_DRV %d> Pie Source buffer wrap around\n", __LINE__ );
							}
						}
					}

					//Assign the current write pointer address to the write pointer
					/* 2012. 12. 22 jinhwan.bae Change from mmaped virtual to physical. Pie Buffer Setting in Kdriver should be ioremapped address, deleted mmaped address operation */
#if 0
					astDvrMemMap[ch].stPieUserVirtBuff.ui32WritePtr = (UINT32)pstIdx;
#else
					astDvrMemMap[ch].stPieMappedBuff.ui32WritePtr = (UINT32)pstIdx;
					astDvrMemMap[ch].stPiePhyBuff.ui32WritePtr = astDvrMemMap[ch].stPieMappedBuff.ui32WritePtr - astDvrMemMap[ch].si32PieVirtOffset;
#endif
					stGetPieTable.indexBuffer.eStatus = LX_PVR_BUF_STAT_Ready;
				}

				/* Send the write pointer back to user */
				/* 2012. 12. 22 jinhwan.bae Change from mmaped virtual to physical. Pie Buffer Setting in Kdriver should be ioremapped address, deleted mmaped address operation */
#if 0
				stGetPieTable.indexBuffer.uiWriteAddr = astDvrMemMap[ch].stPieUserVirtBuff.ui32WritePtr;
#else
				stGetPieTable.indexBuffer.uiWriteAddr = astDvrMemMap[ch].stPiePhyBuff.ui32WritePtr;
#endif
				/* Reset index write pointer to the base after copying to user for linear mode operation */
				//astDvrMemMap[ch].stPieUserVirtBuff.ui32WritePtr = astDvrMemMap[ch].stPieUserVirtBuff.ui32BufferBase;

				if (copy_to_user( (LX_PVR_PIE_GET_TABLE_T *)arg, &stGetPieTable, sizeof(LX_PVR_PIE_GET_TABLE_T)))
				{
					PVR_PRINT("ioctl: copy_to_user error !!! \n");
					return -EFAULT;
				}
				//PVR_TRACE("PVR_IOR_DN_GET_WRITE_ADD ok\n");
				ret = 0;
			}
			break;

		case PVR_IOR_PIE_GET_DATA:
			{
				UINT32	ui32Index, ui32Count, ech;
				LX_PVR_PIE_GET_DATA_T	stGetPieData;

				if (copy_from_user(&stGetPieData, (void __user *)arg, sizeof(LX_PVR_PIE_GET_DATA_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				ech = stGetPieData.ePVRCh;

				ui32Index = astDvrPieData[ech].ui32PieWrIndex;

				for ( ui32Count = 0; ui32Count < ui32Index; ui32Count++)
				{
					stGetPieData.ui32PieData[ui32Count].ui32Val	= astDvrPieData[ech].astPieData[ui32Count].ui32Val;
				}

				stGetPieData.ui32PieDataCnt = ui32Index;
				astDvrPieData[ech].ui32PieWrIndex = 0;

				if (copy_to_user( (LX_PVR_PIE_GET_DATA_T *)arg,	&stGetPieData, sizeof(LX_PVR_PIE_GET_DATA_T)))
				{
					PVR_PRINT("ioctl: copy_to_user error !!! \n");
					return -EFAULT;
				}
			}
			break;

		case PVR_IOW_UP_INIT:
			{
				LX_PVR_SET_BUFFER_T	stSetBuf;
				if (copy_from_user(&stSetBuf, (void __user *)arg, sizeof(LX_PVR_SET_BUFFER_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}
				//Sanity check
				if ( stSetBuf.ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}
				PVR_DD_SetUploadbuffer ( stSetBuf.ePVRCh, stSetBuf.uiBufAddr, stSetBuf.uiBufSize);

				PVR_TRACE("PVR_IOW_UP_INIT ok\n");
				ret = 0;
			}
			break;

			//23.05.2010 - Based on discussion for trick mode/jump case to restart upload hw
		case PVR_IOW_UP_RESTART:
			{
				LX_PVR_SET_BUFFER_T	stSetBuf;

				if (copy_from_user(&stSetBuf, (void __user *)arg, sizeof(LX_PVR_SET_BUFFER_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if (stSetBuf.ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}

				PVR_DD_RestartUpload(stSetBuf.ePVRCh, stSetBuf.uiBufAddr, stSetBuf.uiBufSize);

				PVR_TRACE("PVR_IOW_UP_RESTART ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_UP_RESET:	//Restart purpose???
			{
				LX_PVR_CH_T	ePVRCh;
				if (copy_from_user(&ePVRCh, (void __user *)arg, sizeof(LX_PVR_CH_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if (ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}

				PVR_DD_ReSetUpload(ePVRCh);

				PVR_TRACE("PVR_IOW_UP_RESET ok\n");
				ret = 0;
			}
		break;

		case PVR_IOW_UP_UPLOAD_BUFFER:
			{
				LX_PVR_SET_BUFFER_T	stUpSetBuf;

				if (copy_from_user(&stUpSetBuf, (void __user *)arg, sizeof(LX_PVR_SET_BUFFER_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if (stUpSetBuf.ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}
				//Set the upload write pointer with the new value
				PVR_DD_UpUploadbuffer (stUpSetBuf.ePVRCh, stUpSetBuf.uiBufAddr );

				PVR_PRINT("^Y^WrAddr [0x%x]\n", stUpSetBuf.uiBufAddr);

				//PVR_TRACE("PVR_IOW_UP_UPLOAD_BUFFER ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_UP_START:
			{
				LX_PVR_START_T	stUpStart;
				UINT8			ui8PacketLen = 192;

				if (copy_from_user(&stUpStart, (void __user *)arg, sizeof(LX_PVR_START_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				//Sanity check
				if (stUpStart.ePVRCh > LX_PVR_CH_MAX )
				{
					return -EFAULT;
				}

				//Murugan-8/12/2010 - Enable the below line, to select between 192 byte or 188byte packet streams
				//ePacketLen argument has to be valid in the START command
				ui8PacketLen = (stUpStart.ePacketLen == LX_PVR_STREAM_TYPE_192)? 192 : 188;
				if ( stUpStart.bStart )
				{
					PVR_DD_StartUpload ( stUpStart.ePVRCh, ui8PacketLen );
				}
				else
				{
					PVR_DD_StopUpload( stUpStart.ePVRCh );
				}
				PVR_TRACE("PVR_IOW_UP_START ok\n");
				ret = 0;
			}
			break;

		case PVR_IOW_UP_PAUSE:
		{
			LX_PVR_UP_PAUSE_T	stGetUpPause;

			if (copy_from_user(&stGetUpPause, (void __user *)arg, sizeof(LX_PVR_UP_PAUSE_T)))
			{
				PVR_PRINT("ioctl: copy_from_user error !!! \n");
				return -EFAULT;
			}
			ret = -1;

			//Sanity check
			if (stGetUpPause.ePVRCh > LX_PVR_CH_MAX )
			{
				return -EFAULT;
			}
			if (stGetUpPause.ePlay == LX_PVR_UP_PAUSE)
			{
				ret = PVR_DD_PauseUpload (stGetUpPause.ePVRCh);
			}
			else if (stGetUpPause.ePlay == LX_PVR_UP_RESUME)
			{
				ret = PVR_DD_ResumeUpload (stGetUpPause.ePVRCh);
			}
			PVR_TRACE("PVR_IOW_UP_PAUSE ok\n");

		}
		break;

		case PVR_IOR_UP_GET_STATE:
		{
			LX_PVR_UP_GET_STATE_T	stGetUpState;

			if (copy_from_user(&stGetUpState, (void __user *)arg, sizeof(LX_PVR_UP_GET_STATE_T)))
			{
				PVR_PRINT("ioctl: copy_from_user error !!! \n");
				return -EFAULT;
			}

			//Sanity check
			if (stGetUpState.ePVRCh > LX_PVR_CH_MAX )
			{
				return -EFAULT;
			}
			/* Get the upload buffer read pointer */
			PVR_DD_GetUploadReadAddr (
				stGetUpState.ePVRCh,
				&stGetUpState.upBuffer.uiWriteAddr,
				&stGetUpState.upBuffer.uiReadAddr );

			//Give the current buffer status
			stGetUpState.upBuffer.eStatus = astDvrBufferState[stGetUpState.ePVRCh].eUpBufState;


			/* Copy the current upload driver state */
			stGetUpState.eUpState = astDvrState[stGetUpState.ePVRCh].eUpState;

			/* Copy the local updates back to user buffer and return */
			if (copy_to_user( (LX_PVR_UP_GET_STATE_T *)arg,	&stGetUpState, sizeof(LX_PVR_UP_GET_STATE_T)))
			{
				PVR_PRINT("ioctl: copy_to_user error !!! \n");
				return -EFAULT;
			}

			//PVR_TRACE("PVR_IOR_UP_GET_STATE ok\n");
			ret = 0;
		}
		break;

		case PVR_IOW_PRINT_CONTROL:
			{
				LX_PVR_PRINT_CONTROL_T	stPrntCtrl;
				UINT32	msk, ui32Count;

				if (copy_from_user(&stPrntCtrl, (void __user *)arg, sizeof(LX_PVR_PRINT_CONTROL_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				msk = stPrntCtrl.ui32PrintMask & 0xF;

				for ( ui32Count = 0; ui32Count < 4; ui32Count++ )
				{
					if ( msk & (1 << ui32Count) )
					{
						OS_DEBUG_EnableModuleByIndex ( g_pvr_debug_fd, ui32Count, DBG_COLOR_NONE );
					}
					else
					{
						OS_DEBUG_DisableModuleByIndex ( g_pvr_debug_fd, ui32Count);
					}
				}
			}
			break;

		case PVR_IOW_UP_MODE:
			{
				LX_PVR_TRICK_MODE_T	stTrickMode;

				if (copy_from_user(&stTrickMode, (void __user *)arg, sizeof(LX_PVR_TRICK_MODE_T)))
				{
					PVR_PRINT("ioctl: copy_from_user error !!! \n");
					return -EFAULT;
				}

				ret = PVR_DD_UpMode(stTrickMode.ePVRCh, stTrickMode.eMode);

// move to PVR_DD_UpMode()
#if 0
				if (stTrickMode.ePVRCh > LX_PVR_CH_MAX)
				{
					PVR_PRINT("ioctl: Bad parameter for trickmode!!\n");
					return -EFAULT;
				}

				if ( 1 )	// TSC Disable method
				{
					switch (stTrickMode.eMode)
					{
						case LX_PVR_UPMODE_NORMAL :
							/* Clear the TSC Disable register for normal play */
							DVR_UP_TimeStampCheckDisable (stTrickMode.ePVRCh, FALSE);
							break;
						case LX_PVR_UPMODE_TRICK_MODE:
							/* Enable the TSC Disable register for trick mode play */
							DVR_UP_TimeStampCheckDisable (stTrickMode.ePVRCh, TRUE);
							break;
					}
				}
				else if ( 0 )		//PLAY_MOD = 100 Trickmode method
				{
					switch (stTrickMode.eMode)
					{
						case LX_PVR_UPMODE_NORMAL :
							/* Upload playmode is set to normal playmode value 000 */
							DVR_UP_ChangePlaymode(stTrickMode.ePVRCh, LX_PVR_UPMODE_NORMAL);
							break;
						case LX_PVR_UPMODE_TRICK_MODE:
							/* Change playmode to trick playmode 100 (4) */
							//Need to check if default AL_JITTER value has to be changed or not !!!
							DVR_UP_ChangePlaymode(stTrickMode.ePVRCh, 4);
							break;
					}
				}
				else if ( 0 )		//PLAY_MOD variable according to different speed
				{
					switch (stTrickMode.eMode)
					{
						case LX_PVR_UPMODE_NORMAL :
						case LX_PVR_UPMODE_TRICK_MODE:
							/*
							 * Change playmode to the trick mode value passed, the enum value is matching the
							  * register field definition
							  */
							DVR_UP_ChangePlaymode(stTrickMode.ePVRCh, (UINT8) stTrickMode.eMode);
							break;
					}
				}
#endif
			}
			break;

		case PVR_IOW_MM_Init:
		{
			LX_PVR_GPB_INFO_T	stLXPvrGPBInfo;
			PVR_PRINT("PVR_IOW_MM_Init ok\n");

			if (copy_from_user(&stLXPvrGPBInfo, (void __user *)arg, sizeof(LX_PVR_GPB_INFO_T)))
			{
				PVR_PRINT("ioctl: copy_from_user error !!! \n");
				return -EFAULT;
			}
#if 0
			//Sanity check
			if (stLXPvrGPBInfo.uiDnBase == 0)
			{
				return -EFAULT;
			}
#endif
			ret = PVR_DD_MemoryInit(&stLXPvrGPBInfo);

			/* Copy the local updates back to user buffer and return */
			if (copy_to_user( (LX_PVR_GPB_INFO_T *)arg,	&stLXPvrGPBInfo, sizeof(LX_PVR_GPB_INFO_T)))
			{
				PVR_PRINT("ioctl: copy_to_user error !!! \n");
				return -EFAULT;
			}

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
user_initcall_grp("kdrv",PVR_Init);
#else
module_init(PVR_Init);
#endif
module_exit(PVR_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

