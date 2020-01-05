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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#undef	SUPPORT_SDEC_DEVICE_READ_WRITE_FOPS
#define	SUPPORT_SDEC_DEVICE_READ_WRITE_FOPS

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>    /**< For isr */
#include <linux/irqreturn.h>
#include <asm/uaccess.h>
#include <asm/irq.h>                    /**< For isr */
#include <mach/irqs.h>
#include <linux/mm.h>
#include <linux/rmap.h>
#include <asm/io.h>			/**< For ioremap_nocache */
#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include <linux/version.h>

#include "os_util.h"
#include "base_device.h"
#include "sdec_drv.h"
#include "sdec_io.h"
#include "sdec_reg.h"
#include "sdec_isr.h"
#include "sdec_mm.h"
#include "sdec_pes.h"
#include "sdec_hal.h"
#include "sdec_swparser.h"

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
 *	main control block for sdec device.
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

	S_SDEC_PARAM_T		stSdecParam;
// END of device specific data
}
SDEC_DEVICE_T;

#ifdef KDRV_CONFIG_PM
typedef struct
{
	// add here extra parameter
	bool	is_suspended;
}SDEC_DRVDATA_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern	void	SDEC_PROC_Init(void);
extern	void	SDEC_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/
int		SDEC_Init(void);
void	SDEC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int		g_sdec_debug_fd = -1;
int 	g_sdec_major = SDEC_MAJOR;
int 	g_sdec_minor = SDEC_MINOR;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void 	SDEC_Timer(ULONG param);
static int      SDEC_Open(struct inode *, struct file *);
static int      SDEC_Close(struct inode *, struct file *);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int SDEC_Ioctl (struct inode *, struct file *, unsigned int, unsigned long );
#else
static long SDEC_Ioctl (struct file *filp, unsigned int cmd, unsigned long arg );
#endif
static int 	SDEC_Mmap (struct file *filep, struct vm_area_struct *vma );
#ifdef SUPPORT_SDEC_DEVICE_READ_WRITE_FOPS
static ssize_t  SDEC_Read (
			struct file *i_pstrFilp, 				/* file pointer representing driver instance */
			SINT8        *o_pcBufferToLoad,     	/* buffer from user space */
			size_t      i_uiSizeToRead,    		/* size of buffer in bytes*/
			loff_t 		*i_FileOffset  );   		/* offset in the file */
//static ssize_t  SDEC_Write(struct file *, const char *, size_t, loff_t *);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/**
 * main control block for sdec device
*/
static SDEC_DEVICE_T*		g_sdec_device;

/**
 * file I/O description for sdec device
 *
*/
static struct file_operations g_sdec_fops =
{
	.open 	= SDEC_Open,
	.release= SDEC_Close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl	= SDEC_Ioctl,
#else
	.unlocked_ioctl	= SDEC_Ioctl,
#endif
#ifdef SUPPORT_SDEC_DEVICE_READ_WRITE_FOPS
	.read 	= (void *)SDEC_Read,
	.mmap	=SDEC_Mmap,
//	.write 	= SDEC_Write,
#else
//	.read	= NULL,
//	.write	= NULL,
#endif
};

OS_TIMER_T		sdec_timer;

static irqreturn_t SDEC_irq_handler(int irq, void *dev_id)
{
	S_SDEC_PARAM_T *stpSdecParam;

	stpSdecParam = (S_SDEC_PARAM_T *)dev_id;

	SDEC_ISR_Handler(stpSdecParam);//call VDEC ISR routien

	return IRQ_HANDLED;
}

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

UINT32 ui32SDECBaseAddr;
UINT32 ui32SDECBaseAddr1;

static int SDEC_suspend(struct platform_device *pdev, pm_message_t state)
{
	SDEC_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	// add here the suspend code

	drv_data->is_suspended = 1;

	printk(GREEN_COLOR"[%s] done suspend\n"NORMAL_COLOR, SDEC_MODULE);

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
static int SDEC_resume(struct platform_device *pdev)
{
	SDEC_DRVDATA_T *drv_data;
	CDIC	stCDIC[2];
	CDOC	stCDOC[2];

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;

	//g_sdec_device->stSdecParam.stSDEC_IO_Reg->

#if 0
	SDEC_HAL_CIDCReset(0);
	SDEC_HAL_CIDCReset(1);
	SDEC_HAL_CIDCReset(2);

	SDEC_HAL_STCCReset(0);
	SDEC_HAL_STCCReset(1);

	SDEC_HAL_GSTCReset();
#else
	stCDIC[0] = g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdic[0];
	stCDIC[1] = g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdic[1];
	stCDOC[0] = g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdoc[0];
	stCDOC[1] = g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdoc[1];

	// add here the resume code

	//iput path reset
	stCDIC[0].rst = 0x1;
	stCDIC[1].rst = 0x1;
	stCDOC[0].rst = 0x1;
	stCDOC[1].rst = 0x1;

	g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdic[0] = stCDIC[0];
	g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdic[1] = stCDIC[1];
	g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdoc[0] = stCDOC[0];
	g_sdec_device->stSdecParam.stSDEC_IO_Reg->cdoc[1] = stCDOC[1];

#endif
	drv_data->is_suspended = 0;

	printk(GREEN_COLOR"[%s] done resume\n"NORMAL_COLOR, SDEC_MODULE);
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
 int  SDEC_probe(struct platform_device *pdev)
{

	SDEC_DRVDATA_T *drv_data;

	drv_data = (SDEC_DRVDATA_T *)kmalloc(sizeof(SDEC_DRVDATA_T) , GFP_KERNEL);


	// add here driver registering code & allocating resource code



	SDEC_DTV_SOC_Message( SDEC_TRACE, "[%s] done probe\n", SDEC_MODULE);
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
static int  SDEC_remove(struct platform_device *pdev)
{
	SDEC_DRVDATA_T *drv_data;

	// add here driver unregistering code & deallocating resource code



	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "released\n");

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
static void  SDEC_release(struct device *dev)
{


	SDEC_DTV_SOC_Message( SDEC_TRACE, "device released\n");
}

/*
 *	module platform driver structure
 */
static struct platform_driver sdec_driver =
{
	.probe          = SDEC_probe,
	.suspend        = SDEC_suspend,
	.remove         = SDEC_remove,
	.resume         = SDEC_resume,
	.driver         =
	{
		.name   = SDEC_MODULE,
	},
};

static struct platform_device sdec_device = {
	.name = SDEC_MODULE,
	.id = 0,
	.id = -1,
	.dev = {
		.release = SDEC_release,
	},
};
#endif

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void SDEC_PreInit(void)
{
    /* TODO: do something */
}

int SDEC_Init(void)
{
	DTV_STATUS_T eRet = OK;

	int			i;
	int			err;
	dev_t		dev;
//	S_SDEC_PARAM_T *stpSdecParam = NULL;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	/* Get the handle of debug output for sdec device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_sdec_debug_fd = DBG_OPEN( SDEC_MODULE );
	OS_DEBUG_EnableModule ( g_sdec_debug_fd );

	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_DRV,			DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_TRACE,		DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_NORMAL,		DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_READ,		DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_ISR,			DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_IO,			DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_PIDSEC,		DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_RESET,		DBG_COLOR_NONE );
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_PCR,			DBG_COLOR_NONE );
	OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_ERROR,	DBG_COLOR_RED );	/* ERROR */
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_CIA,		DBG_COLOR_RED );	/* Special Force */
	//OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, SDEC_PES,		DBG_COLOR_NONE );

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&sdec_driver) < 0)
	{
		SDEC_DTV_SOC_Message( SDEC_TRACE, "[%s] platform driver register failed\n",SDEC_MODULE);

	}
	else
	{
		if(platform_device_register(&sdec_device))
		{
			platform_driver_unregister(&sdec_driver);
			SDEC_DTV_SOC_Message( SDEC_TRACE, "[%s] platform device register failed\n",SDEC_MODULE);
		}
		else
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "[%s] platform register done\n", SDEC_MODULE);
		}
	}
#endif

	g_sdec_device = (SDEC_DEVICE_T*)OS_KMalloc( sizeof(SDEC_DEVICE_T)*SDEC_MAX_DEVICE );

	if ( NULL == g_sdec_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(SDEC_DEVICE_T)* SDEC_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_sdec_device, 0x0, sizeof(SDEC_DEVICE_T)* SDEC_MAX_DEVICE );

	if (g_sdec_major)//already know device major number
	{
		dev = MKDEV( g_sdec_major, g_sdec_minor );
		err = register_chrdev_region(dev, SDEC_MAX_DEVICE, SDEC_MODULE );
	}
	else//want to allocate device major number
	{
		err = alloc_chrdev_region(&dev, g_sdec_minor, SDEC_MAX_DEVICE, SDEC_MODULE );
		g_sdec_major = MAJOR(dev);
	}

	/* TODO : initialize your module not specific minor device */


	/* END */

	for ( i=0; i<SDEC_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_sdec_major, g_sdec_minor+i );
		cdev_init( &(g_sdec_device[i].cdev), &g_sdec_fops );
		g_sdec_device[i].devno		= dev;
		g_sdec_device[i].cdev.owner = THIS_MODULE;
		g_sdec_device[i].cdev.ops   = &g_sdec_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_sdec_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding sdec device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_sdec_device[i].devno, "%s%d", SDEC_MODULE, i );
	}

	/* initialize proc system */

	SDEC_PROC_Init ( );

	//g_sdec_device->stSdecParam.ui32MsgMask = 0x11111111;//for debug

	eRet = SDEC_Intialize(&g_sdec_device->stSdecParam);

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("SDEC_Intialize failed\n" );
		return -EIO;
	}

	eRet = SDEC_ParamInit(&g_sdec_device->stSdecParam);
	if(LX_IS_ERR(eRet))
	{
		SDEC_DEBUG_Print("Param_Init failed:[%d]", eRet);

		return -EFAULT;
	}


	//init_MUTEX(&_sdec_gpb_lock);

/* For PES H/W bug workaound. See @LX_SDEC_USE_KTHREAD_PES */
#if	( LX_SDEC_USE_KTHREAD_PES == 1)
	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();
	if(pSdecConf->noPesBug == 0)
	{
		/* if there is pes h/w buf, do it */
		SDEC_PES_Init(&g_sdec_device->stSdecParam);
	}
#endif

	//kernel_thread((void *)&SDEC_PollThread, (void*)&g_sdec_device->stSdecParam, 0);

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if (request_irq(H13_IRQ_SDEC,SDEC_irq_handler,0,"DTVSoC2SDEC ", &g_sdec_device->stSdecParam)) {
			SDEC_DEBUG_Print("request_irq in SDEC is failed:[%d]", H13_IRQ_SDEC);
			return -EIO;
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
	{
		if (request_irq(L9_IRQ_SDEC,SDEC_irq_handler,0,"DTVSoC2SDEC ", &g_sdec_device->stSdecParam)) {
			SDEC_DEBUG_Print("request_irq in SDEC is failed:[%d]", L9_IRQ_SDEC);
			return -EIO;
		}
	}
	else
	{
		if (request_irq(L8_IRQ_SDEC,SDEC_irq_handler,0,"DTVSoC2SDEC ", &g_sdec_device->stSdecParam)) {
			SDEC_DEBUG_Print("request_irq in SDEC is failed:[%d]", L8_IRQ_SDEC);
			return -EIO;
		}
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "sdec device initialized\n");

	return 0;
}

void SDEC_Cleanup(void)
{
	int i;
	dev_t dev = MKDEV( g_sdec_major, g_sdec_minor );

#ifdef KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	platform_driver_unregister(&sdec_driver);
	platform_device_unregister(&sdec_device);
#endif

	/* cleanup proc system */
	SDEC_PROC_Cleanup( );

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<SDEC_MAX_DEVICE;i++)
	{
		/* TODO: cleanup each minor device */


		/* END */
		cdev_del( &(g_sdec_device[i].cdev) );
	}

	//disable intr
	SDEC_HAL_EnableInterrupt( PCR, 				SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHA_GPL, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHA_GPH, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHB_GPL, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHB_GPH, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_FULL_CHA_GPL, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_FULL_CHA_GPH, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_FULL_CHB_GPL, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( GPB_FULL_CHB_GPH, 	SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( TP_INFO_CHA, 		SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( TP_INFO_CHB, 		SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( ERR_RPT, 			SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( TB_DCOUNT, 		SDEC_HAL_DISABLE );

	SDEC_HAL_EnableErrorInterrupt(MPG_SD, 		0x0);
	SDEC_HAL_EnableErrorInterrupt(MPG_CC, 		0x0);
	SDEC_HAL_EnableErrorInterrupt(MPG_DUP, 		0x0);
	SDEC_HAL_EnableErrorInterrupt(MPG_TS, 		0x0);
	SDEC_HAL_EnableErrorInterrupt(MPG_PD, 		0x0);
	SDEC_HAL_EnableErrorInterrupt(STCC_DCONT, 	0x0);
	SDEC_HAL_EnableErrorInterrupt(CDIF_RPAGE, 	0x0);
	SDEC_HAL_EnableErrorInterrupt(CDIF_WPAGE, 	0x0);
	SDEC_HAL_EnableErrorInterrupt(CDIF_OVFLOW, 	0x0);
	SDEC_HAL_EnableErrorInterrupt(SB_DROPPED, 	0x0);
	SDEC_HAL_EnableErrorInterrupt(SYNC_LOST, 	0x0);
	SDEC_HAL_EnableErrorInterrupt(TEST_DCONT, 	0x0);

	OS_StopTimer( &sdec_timer);

	/* TODO : cleanup your module not specific minor device */

	free_irq(H13_IRQ_SDEC, NULL);

	unregister_chrdev_region(dev, SDEC_MAX_DEVICE );

	OS_Free( g_sdec_device );
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * open handler for sdec device
 *
 */
static int
SDEC_Open(struct inode *inode, struct file *filp)
{
	int					major,minor;
    struct cdev*    	cdev;
    SDEC_DEVICE_T*	my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, SDEC_DEVICE_T, cdev);

    /* TODO : add your device specific code */
	if ( my_dev->dev_open_count == 0 )
	{
		my_dev->stSdecParam.ui32MsgMask = 0x11111111;

		OS_InitTimer( &sdec_timer);
		OS_StartTimer( &sdec_timer, SDEC_Timer, OS_TIMER_TIMETICK, 10 /* 10 Mhz */, (ULONG)&my_dev->stSdecParam );
	}

	/* END */

    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	my_dev->stSdecParam.stSdecStatus.f.SDEC_OPEN = 0x1;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);

    SDEC_DTV_SOC_Message( SDEC_TRACE, "device opened (%d:%d)\n", major, minor );

	return 0;
}

/**
 * release handler for sdec device
 *
 */
static int
SDEC_Close(struct inode *inode, struct file *file)
{
    int					major,minor;
    SDEC_DEVICE_T*	my_dev;
    struct cdev*		cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, SDEC_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */
	if ( my_dev->dev_open_count == 0 )
	{
		my_dev->stSdecParam.stSdecStatus.f.SDEC_CLOSE = 0x1;
		my_dev->stSdecParam.stSdecStatus.f.SDEC_OPEN = 0x0;
	}
	/* END */


	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);
    SDEC_DTV_SOC_Message( SDEC_TRACE, "device closed (%d:%d)\n", major, minor );
    return 0;
}

/**
 * ioctl handler for sdec device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int SDEC_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long SDEC_Ioctl (struct file *filp, unsigned int cmd, unsigned long arg )
#endif
{
    int err = 0, ret = 0;

    SDEC_DEVICE_T*	my_dev;
    struct cdev*		cdev;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
	struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current sdec device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, SDEC_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != SDEC_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if (_IOC_NR(cmd) > SDEC_IOC_MAXNR)
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

	SDEC_DTV_SOC_Message( SDEC_TRACE, "cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case SDEC_IOR_INIT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IO_INIT ok\n");
#if 0
				ret = SDEC_ParamInit(&my_dev->stSdecParam);

	if(LX_IS_ERR(ret))
	{
		SDEC_DEBUG_Print("Param_Init failed:[%d]", ret);

		return -EFAULT;
	}
#endif /* #if 0 */
#if 1
			ret = SDEC_IO_InitialaizeModule(&my_dev->stSdecParam, arg);
			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_InitialaizeModule failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
#endif /* #if 0 */
				ret = 0;

		}
		break;

		case SDEC_IOR_GET_STC_PCR:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_GET_STC ok\n");
			ret = SDEC_IO_GetCurrentSTCPCR(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_GetCurrentSTCPCR failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SEL_INPUT_PORT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SEL_INPUT_PORT ok\n");
			ret = SDEC_IO_SelInputPort(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SelInputPort failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_CFG_INPUT_PORT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_CFG_INPUT_PORT ok\n");
			ret = SDEC_IO_CfgInputPort(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_CfgInputPort failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SEL_PAR_INPUT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SEL_PAR_INPUT ok\n");
			ret = SDEC_IO_SelParInput(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SelParInput failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SEL_CI_INPUT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SEL_CI_INPUT ok\n");
			ret = SDEC_IO_SelCiInput(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SelCiInput failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SET_CIPHER_ENABLE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_CIPHER_ENABLE ok\n");
			ret = SDEC_IO_SetCipherEnable(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetCipherEnable failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SET_CIPHER_MODE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_CIPHER_MODE ok\n");
			ret = SDEC_IO_SetCipherMode(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetCipherMode failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SET_CIPHER_KEY:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_CIPHER_KEY ok\n");
			ret = SDEC_IO_SetCipherKey(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetCipherKey failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SET_PCR_PID:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_PCR_PID ok\n");
			ret = SDEC_IO_SetPCRPID(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetPCRPID failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SET_PCR_RECOVERY:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_PCR_RECOVERY ok\n");
			ret = SDEC_IO_SetPcrRecovery(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetPcrRecovery failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_GET_INPUT_PORT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_GET_INPUT_PORT ok\n");
			ret = SDEC_IO_GetInputPort(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetPcrRecovery failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SET_VDEC_PORT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_VDEC_PORT ok\n");
			ret = SDEC_IO_SetVidOutport(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetVidOutport failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_PIDFLT_ALLOC:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_PIDFLT_ALLOC ok\n");
			ret = SDEC_IO_PIDFilterAlloc(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterAlloc failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_PIDFLT_FREE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_PIDFLT_FREE ok\n");
			ret = SDEC_IO_PIDFilterFree(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterFree failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_PIDFLT_SET_PID:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_PIDFLT_SET_PID ok\n");
			ret = SDEC_IO_PIDFilterSetPID(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterSetPID failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_PIDFLT_MAP_SECFLT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_PIDFLT_MAP_SECFLT ok\n");
			ret = SDEC_IO_PIDFilterMapSelect(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterMapSelect failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_PIDFLT_ENABLE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_PIDFLT_ENABLE ok\n");
			ret = SDEC_IO_PIDFilterEnable(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterEnable failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_PIDFLT_CRC_ENABLE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_PIDFLT_CRC_ENABLE ok\n");
			ret = SDEC_IO_PIDFilterCRCEnable(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterCRCEnable failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_PIDFLT_GET_STATE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_PIDFLT_GET_STATE ok\n");
			ret = SDEC_IO_PIDFilterGetState(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterGetState failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_PIDFLT_ENABLE_SCMBCHK:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_PIDFLT_ENABLE_SCMBCHK ok\n");
			ret = SDEC_IO_PIDFilterEnableSCMBCHK(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterEnableSCMBCHK failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_PIDFLT_ENABLE_DOWNLOAD:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_PIDFLT_ENABLE_DOWNLOAD ok\n");
			ret = SDEC_IO_PIDFilterEnableDownload(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PIDFilterEnableDownload failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_SECFLT_ALLOC:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_SECFLT_ALLOC ok\n");
			ret = SDEC_IO_SectionFilterAlloc(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterAlloc failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SECFLT_FREE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SECFLT_FREE ok\n");
			ret = SDEC_IO_SectionFilterFree(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterFree failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_PESFLT_FREE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_PESFLT_FREE ok\n");
			ret = SDEC_IO_PESFilterFree(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_PESFilterFree failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SECFLT_PATTERN:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SECFLT_PATTERN ok\n");
			ret = SDEC_IO_SectionFilterPattern(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterPattern failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SECFLT_BUFFER_RESET:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SECFLT_BUFFER_RESET ok\n");
			ret = SDEC_IO_SectionFilterBufferReset(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterBufferReset failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SECFLT_BUFFER_SET:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SECFLT_BUFFER_SET ok\n");
			ret = SDEC_IO_SectionFilterBufferSet(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterBufferSet failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SECFLT_BUFFER_GET_INFO:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SECFLT_BUFFER_GET_INFO ok\n");
			ret = SDEC_IO_SectionFilterGetInfo(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterGetInfo failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_SECFLT_SET_READPTR:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SECFLT_SET_READPTR ok\n");
			ret = SDEC_IO_SectionFilterSetReadPtr(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterSetReadPtr failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_SECFLT_GET_STATE:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_SECFLT_GET_STATE ok\n");
			ret = SDEC_IO_SectionFilterGetState(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterGetState failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		
		case SDEC_IOW_SECFLT_ENABLE_SWPARSER:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SECFLT_ENABLE_SWPARSER ok\n");
			ret = SDEC_SWP_EnableSWParser(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_SWP_EnableSWParser failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_SECFLT_GET_AVAIL_NUMBER:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_SECFLT_GET_AVAIL_NUMBER ok\n");
			ret = SDEC_IO_SectionFilterGetAvailableNumber(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SectionFilterGetAvailableNumber failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}				

		case SDEC_IOW_ENABLE_LOG:
		{
			// LJH added - setting log level
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_ENABLE_LOG ok\n");
			ret = SDEC_IO_EnableLog(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_EnableLog failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_SET_FCW:
		{
			UINT32 *pArg = (UINT32*) arg;
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_FCW ok\n");
			//ret = SDEC_IO_SetFCW(&my_dev->stSdecParam, *pArg);
			ret = SDEC_IO_SetSTCMultiply(&my_dev->stSdecParam, *pArg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_EnableLog failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;
		
		case SDEC_IOR_GET_STCCASG:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_GET_STCCASG ok\n");

			ret = SDEC_IO_GetSTCCASGStatus(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_GetSTCCASGStatus failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOR_SET_STCCASG:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_SET_STCCASG ok\n");

			ret = SDEC_IO_SetSTCCASGStatus(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetSTCCASGStatus failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOR_GET_STCC_STATUS:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IO_GetSTCCStatus ok\n");

			ret = SDEC_IO_GetSTCCStatus(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_GetSTCCStatus failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOR_GET_GSTC:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_GET_GSTC ok\n");

			ret = SDEC_IO_GetCurrentGSTC(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IOR_GET_GSTC failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOR_GET_REG:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_GET_REG ok\n");

			ret = SDEC_IO_GetRegister(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_GetRegister failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOR_SET_REG:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_SET_REG ok\n");

			ret = SDEC_IO_SetRegister(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetRegister failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_MM_Init:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_MM_Init ok\n");

			ret = SDEC_MM_Init(arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_MM_Init failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_MM_Final:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_MM_Final ok\n");

			ret = SDEC_MM_Final();

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IOW_MM_Final failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_MM_Free:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_MM_Free ok\n");
			ret = SDEC_MM_Free(arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_MM_Free failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_MM_Alloc:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_MM_Alloc ok\n");
			ret = SDEC_MM_Alloc(arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_MM_Alloc failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOR_MM_GetStat:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_MM_GetStat ok\n");
			ret = SDEC_MM_GetMemoryStat(arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_MM_GetMemoryStat failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_ENABLE_INPUT_PORT:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOR_PORT_EN_DIS ok\n");
			ret = SDEC_IO_InputPortEnable(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IOR_PORT_EN_DIS failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_GET_CIPHER_KEY:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_SET_CIPHER_KEY ok\n");
			ret = SDEC_IO_GetCipherKey(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SetCipherKey failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
				ret = 0;
		}
		break;

		case SDEC_IOW_DL_SEL:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_DL_SEL ok\n");
			ret = SDEC_IO_SelectPVRSource(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_SelectPVRSource failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_GET_CHIPCFG:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_GET_CHIPCFG ok\n");
			ret = SDEC_IO_GetChipCfg(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_GetChipCfg failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

		case SDEC_IOW_DBG_CMD:
		{
			SDEC_DTV_SOC_Message( SDEC_TRACE, "SDEC_IOW_DBG_CMD ok\n");
			ret = SDEC_IO_DebugCommand(&my_dev->stSdecParam, arg);

			if(LX_IS_ERR(ret))
			{
				SDEC_DEBUG_Print("SDEC_IO_DebugCommand failed:[%d]", ret);

				ret = -ENOTTY;
			}
			else
			ret = 0;
		}
		break;

	    default:
	    {
			/* redundant check but it seems more readable */
    	    ret = -ENOTTY;
		}
		break;
    }

    return ret;
}

#if 0 // SDEC_H13_TEMP

static int 	SDEC_Mmap (struct file *filep, struct vm_area_struct *vma )
{
	ULONG physical = vma->vm_pgoff << PAGE_SHIFT;
	ULONG size = vma->vm_end - vma->vm_start;

	//if(size > MAX_MAPPING_SIZE) return -EINVAL;

	vma->vm_flags |= VM_IO;
	vma->vm_flags |= VM_RESERVED;

	if(remap_pfn_range(vma, vma->vm_start, physical, size, vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}

#else

static int 	SDEC_Mmap (struct file *filep, struct vm_area_struct *vma )
{
	unsigned long start;
	unsigned long len;
	unsigned long off = ((vma->vm_pgoff) << PAGE_SHIFT);

	printk("%s entered \n" , __func__);

	start = 0x8E000000 & PAGE_MASK; // or 0
	len = PAGE_ALIGN((start & ~PAGE_MASK) + 0x1900000);

	printk("MMAP : start - %08lx , len - %08lx , off - %08lx \r\n" , start , len , off);

	if ((vma->vm_end - vma->vm_start + off) > len)
	{
	 	printk("ERROR : GFX_SurfaceMmap leng is over\n");
	 	printk("start : %lx end : %lx offset : %lx len : %lx\n" ,
	 		vma->vm_start , vma->vm_end , off , len);

        return -EINVAL;
	}

	off += start;


	vma->vm_pgoff = off >> PAGE_SHIFT;

	vma->vm_flags |= VM_IO;

	printk("MMAP : start - %08lx , len - %08lx , off - %08lx \r\n" , start , len , vma->vm_pgoff);

	//vma->vm_page_prot //= pgprot_writecombine(vma->vm_page_prot);
	vma->vm_page_prot = __pgprot_modify(vma->vm_page_prot, L_PTE_MT_MASK, L_PTE_MT_WRITEALLOC);

	return io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
	                           vma->vm_end - vma->vm_start,
	                           vma->vm_page_prot);

	return 0;
}

#endif


static ssize_t  SDEC_Read(
			struct file *i_pstrFilp, 				/* file pointer representing driver instance */
			SINT8        *o_pcBufferToLoad,     	/* buffer from user space */
			size_t      i_uiSizeToRead,    		/* size of buffer in bytes*/
			loff_t 		*i_FileOffset  )  		/* offset in the file */
{
	SDEC_DEVICE_T		*my_dev;
	S_SDEC_PARAM_T 	*stpSdecParam;

	UINT8 ui8GpbInfoWIdx = 0, ui8GpbInfoHeadCnt = 0, ui8GpbInfoRIdx = 0;
	UINT8 ui8DataCnt = 0;

	my_dev = (SDEC_DEVICE_T*)i_pstrFilp->private_data;
	stpSdecParam = &(my_dev->stSdecParam);
	//while(1)
	{
		//interruptible_sleep_on(&my_dev->stSdecParam.wait_command_queue[0]);
		/* if there is pending signal, return error code */
		//if(signal_pending(current))	return -EIO;

		wait_event_interruptible(stpSdecParam->wq, stpSdecParam->wq_condition);
		stpSdecParam->wq_condition = 0;

		ui8GpbInfoWIdx = stpSdecParam->ui8GpbInfoWIdx;
		ui8GpbInfoRIdx = stpSdecParam->ui8GpbInfoRIdx;

		/* there is no data. forbid false alarm */
		//if(ui8GpbInfoWIdx == ui8GpbInfoRIdx) continue;
		if(ui8GpbInfoWIdx == ui8GpbInfoRIdx) return -EAGAIN;

		/* wrap around happen */
		if(ui8GpbInfoWIdx < ui8GpbInfoRIdx)
		{
			SDEC_DTV_SOC_Message( SDEC_READ, "wrap around happen");

			/*
			 *                                ui8GpbInfoRIdx
			 *                                       V
			 * |---------------------------------------------------------|
			 * |                                     | ui8GpbInfoHeadCnt |
			 * |---------------------------------------------------------|
			 * |   ui8GpbInfoWIdx |                                      |
			 * |---------------------------------------------------------|
			 *                    ^
			 *              ui8GpbInfoWIdx
			 */
			ui8GpbInfoHeadCnt 	= LX_SDEC_MAX_GPB_DATA - ui8GpbInfoRIdx;
			ui8DataCnt 			= ui8GpbInfoHeadCnt + ui8GpbInfoWIdx;

			SDEC_DTV_SOC_Message( SDEC_READ, "Origianl #of data(#of head data)[%d] #of tail data [%d] ui8GpbInfoRIdx : [%d]",ui8GpbInfoWIdx, ui8GpbInfoHeadCnt,ui8GpbInfoRIdx);

			/* head copy */
			if(copy_to_user( o_pcBufferToLoad,
				&stpSdecParam->stGPBInfo[ui8GpbInfoRIdx],
				sizeof(LX_SDEC_NOTIFY_PARAM_T)*ui8GpbInfoHeadCnt))
	 			return -EFAULT;

			/* tail copy */
			if(copy_to_user( o_pcBufferToLoad + sizeof(LX_SDEC_NOTIFY_PARAM_T)*ui8GpbInfoHeadCnt,
				&stpSdecParam->stGPBInfo[0],
				sizeof(LX_SDEC_NOTIFY_PARAM_T)*ui8GpbInfoWIdx))
	 			return -EFAULT;

		}
		else
		{
			SDEC_DTV_SOC_Message( SDEC_READ, "no wrap around happen");

			ui8DataCnt = ui8GpbInfoWIdx - ui8GpbInfoRIdx;
			SDEC_DTV_SOC_Message( SDEC_READ, "ui8GpbInfoRIdx : [%d] ui8GpbInfoWIdx : [%d] #of data[%d]",ui8GpbInfoRIdx, ui8GpbInfoWIdx, ui8DataCnt);

			/* copy buffer to user */
			if(copy_to_user(o_pcBufferToLoad, &stpSdecParam->stGPBInfo[ui8GpbInfoRIdx],
				sizeof(LX_SDEC_NOTIFY_PARAM_T)*ui8DataCnt))
	 			return -EFAULT;
		}

		//break;
	}

	stpSdecParam->ui8GpbInfoRIdx = ui8GpbInfoWIdx;

	return sizeof(LX_SDEC_NOTIFY_PARAM_T)*ui8DataCnt;

}


static void SDEC_Timer(ULONG param)
{
	SDEC_PollThread((void*)param);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",SDEC_Init);
#else
module_init(SDEC_Init);
#endif
module_exit(SDEC_Cleanup);

//MODULE_AUTHOR("LGE");
//MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

