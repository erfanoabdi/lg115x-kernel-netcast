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
 *  drv file for BE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.02.07
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <asm/uaccess.h>
#ifdef	KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "be_dbg.h"

#include "be_kapi.h"
#include "be_cfg.h"
#include "be_def.h"
#include "be_drv.h"
#include "be_reg.h"

#include "fwl_drv.h"
#include "int_drv.h"
#include "ipc_def.h"
#include "ipc_drv.h"
#include "h3d_drv.h"
#include "frc_drv.h"
#include "sre_drv.h"
#include "led_drv.h"
#include "pwm_pe_drv.h"

// Temp for OIF(Vx1) : 2012.05.09 dj911.kim
#include "../sys/sys_regs.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
//#define USE_BE_IOCTL_MACROS

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *  main control block for BE device.
 *  each minor device has unique control block
 *
 */
typedef struct
{
	int				dev_open_count;		///< check if device is opened or not
	dev_t			devno;				///< device number
	struct cdev		cdev;				///< char device structure
}
BE_DEVICE_T;

typedef struct
{
	bool			is_suspended;
}
BE_DRVDATA_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int BE_FRC_Ioctl(unsigned int cmd, unsigned long arg);
extern int BE_H3D_Ioctl(unsigned int cmd, unsigned long arg);
extern int BE_LED_Ioctl(unsigned int cmd, unsigned long arg);
extern int BE_SRE_Ioctl(unsigned int cmd, unsigned long arg);
extern int BE_PWM_PE_Ioctl(unsigned int cmd, unsigned long arg);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int				g_be_major = BE_MAJOR;
int				g_be_minor = BE_MINOR;
int				g_be_debug_fd;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int		BE_Open	(struct inode *, struct file *);
static int		BE_Close	(struct inode *, struct file *);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int		BE_Ioctl	(struct inode *, struct file *, UINT32, ULONG );
#else
static long		BE_Ioctl	(struct file *, unsigned int, unsigned long );
#endif
//static int		BE_mmap	(struct file *, struct vm_area_struct *);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
//static OS_SEM_T	be_dev_mtx;

/**
 * main control block for gfx device
 */
static BE_DEVICE_T*		g_be_device;

/**
 * file I/O description for gfx device
 */
static struct file_operations g_be_fops =
{
	.open		=	BE_Open,
	.release	=	BE_Close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
	.ioctl		=	BE_Ioctl,
#else
	.unlocked_ioctl =	BE_Ioctl,
#endif
	.read		=	NULL,
	.write		=	NULL,
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef	KDRV_CONFIG_PM
/**
 * suspending module/
 *
 * @param	struct platform_device *pdev pm_message_t state
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int BE_suspend(struct platform_device *pdev, pm_message_t state)
{
	BE_DRVDATA_T	*drv_data;

	drv_data = platform_get_drvdata(pdev);

	drv_data->is_suspended = 1;

	BE_PRINT("[%s] done suspend\n", BE_MODULE);

	return 0;
}

/**
 * resuming module.
 *
 * @param	struct platform_device *
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int BE_resume(struct platform_device *pdev)
{
	BE_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);

	if(drv_data->is_suspended == 0) return -1;

	drv_data->is_suspenced = 0;

	BE_PRINT("[%s] done resume\n", BE_MODULE);
}

/**
 * probing module.
 *
 * @param	struct platform_device *pdev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
int BE_probe(struct platform_device *pdev)
{
	BE_DRVDATA_T *drv_data;

	drv_data = (BE_DRVDATA_T *)kmalloc(sizeof(BE_DRVDATA_T) , GFP_KERNEL);

	BE_PRINT("[%s] done probe\n", BE_MODULE);

	drv_data->is_suspended = 0;

	platform_set_drvdata(pdev, drv_data);

	return 0;
}

/**
 * module remove function. this function will be called in rmmod BE module
 *
 * @param	struct platform_device
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static int BE_remove(struct platform_device *pdev)
{
	BE_DRVDATA_T *drv_data;

	drv_data = platform_get_drvdata(pdev);
	kfree(drv_data);

	BE_PRINT("[%s] removed\n", BE_MODULE);
}

/**
 * module release function. this function will be called in rmmod BE module
 *
 * @param	struct device *dev
 * @return	int 0 : OK , -1 : NOT OK
 *
 */
static void BE_release(struct device *dev)
{
	BE_PRINT("[%s] device released\n", BE_MODULE);
}

/*
 * module platform driver structure
 */
static struct platform_driver be_driver =
{
	.probe		= BE_probe,
	.suspend	= BE_suspend,
	.remove		= BE_remove,
	.resume		= BE_resume,
	.driver		=
	{
		.name	= BE_MODULE,
	},
};

static struct platform_device be_device =
{
	.name		= BE_MODULE,
	.id			= 0,
	.dev		=
	{
		.release = BE_MODULE,
	},
};
#endif

/**
 * open handler for BE device
 *
 * @param	*inode [in] inode
 * @param	*filp [in] file
 * @return	OK if success, ERROR otherwisw,
 * @see
 * @author
 */
static int BE_Open(struct inode *inode, struct file *filp)
{
	int				major, minor;
	struct cdev*	cdev;
	BE_DEVICE_T*	my_dev;
	
	BE_PRINT("Attempting to open BE device...\n");

	cdev	= inode->i_cdev;
	my_dev	= container_of (cdev, BE_DEVICE_T, cdev);

	my_dev->dev_open_count++;
	filp->private_data = my_dev;

	major = imajor(inode);
	minor = iminor(inode);

	BE_PRINT("device opened (%d:%d)\n", major, minor);

	return 0;
}

/**
 * BE close
 *
 * @param	*inode [in] inode
 * @param	*file [in] file
 * @return	OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int BE_Close(struct inode *inode, struct file *file)
{
	int				major, minor;
	BE_DEVICE_T*	my_dev;
	struct cdev*	cdev;

	cdev	= inode->i_cdev;
	my_dev	= container_of( cdev, BE_DEVICE_T, cdev);

	if( my_dev->dev_open_count > 0 )
	{
		--my_dev->dev_open_count;
	}

	major = imajor(inode);
	minor = iminor(inode);

	BE_PRINT("device closed (%d:%d)\n", major, minor);
	return 0;
}

/**
 * ioctl handler for BE device.
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 * @note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
static int
BE_Ioctl ( struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg )
#else
static long
BE_Ioctl ( struct file *filp, unsigned int cmd, unsigned long arg )
#endif
{
    int err = 0, ret = 0;

    BE_DEVICE_T*	my_dev;
    struct cdev*		cdev;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#else
		struct inode *inode = filp->f_path.dentry->d_inode;
#endif

	/*
	 * get current BE device object
	 */
    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, BE_DEVICE_T, cdev);

    /*
     * check if IOCTL command is valid or not.
     * - if magic value doesn't match, return error (-ENOTTY)
     * - if command is out of range, return error (-ENOTTY)
     *
     * note) -ENOTTY means "Inappropriate ioctl for device.
     */
    if (_IOC_TYPE(cmd) != BE_IOC_MAGIC)
    {
    	DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
    	return -ENOTTY;
    }
    if ((_IOC_NR(cmd)) > BE_IOC_MAXNR)
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

	BE_DEBUG("cmd = %08X (cmd_idx=%d)\n",cmd, _IOC_NR(cmd) );

	if ((_IOC_NR(cmd)) < BE_IOC_TOP_MAX)		{BE_TOP_Ioctl(cmd,arg);}
	else if((_IOC_NR(cmd)) < BE_IOC_H3D_MAX)	{BE_H3D_Ioctl(cmd,arg);}
	else if((_IOC_NR(cmd)) < BE_IOC_FRC_MAX)	{BE_FRC_Ioctl(cmd,arg);}
	else if((_IOC_NR(cmd)) < BE_IOC_SRE_MAX)	{BE_SRE_Ioctl(cmd,arg);}
    	else if((_IOC_NR(cmd)) < BE_IOC_PE_MAX)	{BE_PWM_PE_Ioctl(cmd,arg);}
	else if((_IOC_NR(cmd)) < BE_IOC_LED_MAX)	{BE_LED_Ioctl(cmd,arg);}
	else if((_IOC_NR(cmd)) < BE_IOC_PWM_MAX){BE_PWM_PE_Ioctl(cmd,arg);}
	else BE_ERROR("Warning! Wrong IOCTL call from kadpator!\n");

    return ret;
}

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void BE_PreInit(void)
{
    /* TODO: do something */
}

/**
 * init BE drv
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int BE_Init(void)
{
	int			i;
	int			err;
	dev_t		dev;

	/* Get the handle of debug output for BE device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	if (lx_chip_rev() < LX_CHIP_REV(H13, A0))
		return 0;
	
	g_be_debug_fd = DBG_OPEN( BE_MODULE );
	if (g_be_debug_fd < 0) {
		DBG_PRINT_ERROR("can't open BE module\n" );
		return -EIO;
	}
	OS_DEBUG_EnableModule ( g_be_debug_fd );

	OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_PRINT, DBG_COLOR_NONE ); 	// BE_PRINT
	OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_ERROR, DBG_COLOR_UL_RED );	// BE_ERROR
	OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_DEBUG ); 					// BE_DEBUG
	OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_TRACE );					// BE_TRACE

	/* allocate main device handler, register current device.
	 *
	 * If devie major is predefined then register device using that number.
	 * otherwise, major number of device is automatically assigned by Linux kernel.
	 *
	 */
#ifdef	KDRV_CONFIG_PM
	// added by SC Jung for quick booting
	if(platform_driver_register(&be_driver) < 0)
	{
		BE_ERROR("[%s] platform driver register failed\n",BE_MODULE);

	}
	else
	{
		if(platform_device_register(&be_device))
		{
			platform_driver_unregister(&be_driver);
			BE_ERROR("[%s] platform device register failed\n",BE_MODULE);
		}
		else
		{
			BE_PRINT("[%s] platform register done\n", BE_MODULE);
		}


	}
#endif

	g_be_device = (BE_DEVICE_T*)OS_KMalloc( sizeof(BE_DEVICE_T)*BE_MAX_DEVICE );

	if ( NULL == g_be_device )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(BE_DEVICE_T)* BE_MAX_DEVICE );
		return -ENOMEM;
	}

	memset( g_be_device, 0x0, sizeof(BE_DEVICE_T)* BE_MAX_DEVICE );

	if (g_be_major)
	{
		dev = MKDEV( g_be_major, g_be_minor );
		err = register_chrdev_region(dev, BE_MAX_DEVICE, BE_MODULE );
	}
	else
	{
		err = alloc_chrdev_region(&dev, g_be_minor, BE_MAX_DEVICE, BE_MODULE );
		g_be_major = MAJOR(dev);
	}

	if ( err < 0 )
	{
		DBG_PRINT_ERROR("can't register BE device\n" );
		return -EIO;
	}



	/* END */

	for ( i=0; i<BE_MAX_DEVICE; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_be_major, g_be_minor+i );
		cdev_init( &(g_be_device[i].cdev), &g_be_fops );
		g_be_device[i].devno		= dev;
		g_be_device[i].cdev.owner = THIS_MODULE;
		g_be_device[i].cdev.ops   = &g_be_fops;

		/* TODO: initialize minor device */


		/* END */

		err = cdev_add (&(g_be_device[i].cdev), dev, 1 );

		if (err)
		{
			DBG_PRINT_ERROR("error (%d) while adding BE device (%d.%d)\n", err, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}
        OS_CreateDeviceClass ( g_be_device[i].devno, "%s%d", BE_MODULE, i );
	}

	/* TODO : initialize your module not specific minor device */
	BE_InitCfg();
	BE_REG_Init();
	BE_IPC_Init();
	BE_INT_Init();
	BE_PWM_PE_Init();

	// Temp for OIF(Vx1) : 2012.05.09 dj911.kim
#if 1 
	if(lx_chip_rev() < LX_CHIP_REV( H13, B0))
	{
		CTOP_CTRL_H13A0_RdFL(ctr82);
		if(CTOP_CTRL_H13A0_Rd(ctr82) == 0x05000000) // if not : set by bootloader
		{
			CTOP_CTRL_H13A0_RdFL(ctr83);
			CTOP_CTRL_H13A0_Wr(ctr83, 0xC8148000);
			CTOP_CTRL_H13A0_WrFL(ctr83);

			CTOP_CTRL_H13A0_RdFL(ctr89);
			CTOP_CTRL_H13A0_Wr(ctr89, 0x620000D8);
			CTOP_CTRL_H13A0_WrFL(ctr89);

			CTOP_CTRL_H13A0_RdFL(ctr90);
			CTOP_CTRL_H13A0_Wr(ctr90, 0x88CFC200);
			CTOP_CTRL_H13A0_WrFL(ctr90);

			CTOP_CTRL_H13A0_RdFL(ctr90);
			CTOP_CTRL_H13A0_Wr(ctr90, 0x88DFC200);
			CTOP_CTRL_H13A0_WrFL(ctr90);

			CTOP_CTRL_H13A0_RdFL(ctr91);
			CTOP_CTRL_H13A0_Wr(ctr91, 0x00155080);
			CTOP_CTRL_H13A0_WrFL(ctr91);

			CTOP_CTRL_H13A0_RdFL(ctr91);
			CTOP_CTRL_H13A0_Wr(ctr91, 0x00155000);
			CTOP_CTRL_H13A0_WrFL(ctr91);

			CTOP_CTRL_H13A0_RdFL(ctr92);
			CTOP_CTRL_H13A0_Wr(ctr92, 0xF8200020);
			CTOP_CTRL_H13A0_WrFL(ctr92);
		
			BE_PRINT("be : Vx1 parameter has been initialized\n");
		
		}
	}
#endif

#ifndef	KDRV_CONFIG_PM
	//PE_SPD_probe();
#endif

	BE_PRINT("BE device initialized\n");

	return 0;
}

int BE_TOP_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case BE_IOW_UPDATE_FIRMWARE:
		{
			ret = BE_FW_Update(arg);
		}
		break;

		case BE_IOW_RESET_SW:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_Reset_SW();
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_BYPASS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Bypass(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_TOP_GET_BYPASS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Get_Bypass(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_TOP_GET_STATUS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Get_Status(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_TOGGLE_3D_LR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Toggle_3D_LR(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_3D_IN_FORMAT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_3D_In_Format(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_GET_3D_IN_FORMAT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Get_3D_In_Format(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_3D_OUT_FORMAT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_3D_Out_Format(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_3D_SYNC_DELAY:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_3D_Sync_Delay(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_3D_CONVERGENCE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_3D_Convergence(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_BLACK_BAR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Black_Bar(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_VIDEO_MUTE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Video_Mute(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_MUTE_COLOR:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Mute_Color(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_SET_DISPLAY_TYPE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Display_Type(arg);
			#else
			//Added macro code
			#endif
		}
		break;
		
		case BE_IOW_TOP_SET_DEBUG_DISPLAY:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Debug_Display(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_VID_OPERATION:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_VID_Operation(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_INPUT_SRC_TYPE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Input_Src_Type(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_ACTIVE_WINDOW_START:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Active_Window_Start(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_ACTIVE_WINDOW_SIZE:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Set_Active_Window_Size(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_TOP_FIRMWARE_DEBUG:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_TOP_Firmware_Debug(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SET_UART_FOR_MCU:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_Set_UartForMcu(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IORW_REG_ACCESS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_REG_RegAccess(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_ENABLE_DEBUG_PRINT:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_Set_DebugPrint(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		default :
		{
			BE_ERROR("WARNING! WRONG IOCTL CALL!!\n");
			ret = RET_ERROR;
		}
		break;
	}

	return ret;
}

int BE_Reset_SW(void)
{
	int ret = RET_OK;

	do{
		ret = BE_REG_SwReset();
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_Set_UartForMcu(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN stParams;

	do{
		ret = copy_from_user(&stParams, (BOOLEAN *)arg, sizeof(BOOLEAN));
		if(ret) BREAK_WRONG(ret);
		ret = BE_REG_Uart0_Switch(stParams);
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_Set_DebugPrint(unsigned long arg)
{
	int ret = RET_OK;
	BE_DEBUG_PRINT_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_DEBUG_PRINT_T *)arg, sizeof(BE_DEBUG_PRINT_T));
		if(ret) BREAK_WRONG(ret);

		if(stParams.dbgMask & BE_DBG_PRT_MSK_PRINT) // BE_PRINT
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_PRINT, DBG_COLOR_NONE ); 	
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_PRINT );
		}

		if(stParams.dbgMask & BE_DBG_PRT_MSK_ERROR) // BE_ERROR
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_ERROR, DBG_COLOR_UL_RED );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_ERROR );
		}

		if(stParams.dbgMask & BE_DBG_PRT_MSK_DEBUG) // BE_DEBUG
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_DEBUG, DBG_COLOR_NONE );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_DEBUG ); 
		}

		if(stParams.dbgMask & BE_DBG_PRT_MSK_TRACE) // BE_TRACE
		{
			OS_DEBUG_EnableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_TRACE, DBG_COLOR_NONE );
		}
		else
		{
			OS_DEBUG_DisableModuleByIndex ( g_be_debug_fd, BE_DBG_PRT_IDX_TRACE );
		}
	} while(0);
	return ret;
}

int BE_TOP_Set_Bypass(unsigned long arg)
{
	int ret = RET_OK;
	BE_BLOCK_BYPASS_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_BLOCK_BYPASS_T *)arg, sizeof(BE_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_BLOCK_BYPASS, &stParams, sizeof(BE_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Get_Bypass(unsigned long arg)
{
	int ret = RET_OK;
	//BE_BLOCK_BYPASS_T *stParams = (BE_BLOCK_BYPASS_T*)arg;

	do{

	} while(0);
	return ret;
}

int BE_TOP_Get_Status(unsigned long arg)
{
	int ret = RET_OK;
	BE_STATUS_T stParams;

	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_STATUS, &stParams, sizeof(BE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Toggle_3D_LR(unsigned long arg)
{
	int ret = RET_OK;
	BE_3D_LR_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_3D_LR_T *)arg, sizeof(BE_3D_LR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_TOGGLE_3D_LR, &stParams, sizeof(BE_3D_LR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_3D_In_Format(unsigned long arg)
{
	int ret = RET_OK;
	BE_TOP_3D_IN_FORMAT_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_TOP_3D_IN_FORMAT_T *)arg, sizeof(BE_TOP_3D_IN_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_3D_IN_FORMAT, &stParams, sizeof(BE_TOP_3D_IN_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Get_3D_In_Format(unsigned long arg)
{
	int ret = RET_OK;
	BE_TOP_3D_IN_FORMAT_T stParams;

	do{
		IPC_SET_GET_PARAM(BE_TOP_3D_IN_FORMAT_T, stParams);
		ret = BE_KIPC_SetData(BE_TOP_SET_3D_IN_FORMAT, &stParams, sizeof(BE_TOP_3D_IN_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_TOP_3D_IN_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_TOP_3D_IN_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_3D_Out_Format(unsigned long arg)
{
	int ret = RET_OK;
	BE_3D_OUT_FORMAT_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_3D_OUT_FORMAT_T *)arg, sizeof(BE_3D_OUT_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_3D_OUT_FORMAT, &stParams, sizeof(BE_3D_OUT_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_3D_Sync_Delay(unsigned long arg)
{
	int ret = RET_OK;
	BE_SYNC_DELAY_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SYNC_DELAY_T *)arg, sizeof(BE_SYNC_DELAY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_3D_SYNC_DELAY, &stParams, sizeof(BE_SYNC_DELAY_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_3D_Convergence(unsigned long arg)
{
	int ret = RET_OK;
	BE_3D_CONVERGENCE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_3D_CONVERGENCE_T *)arg, sizeof(BE_3D_CONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_3D_CONVERGENCE, &stParams, sizeof(BE_3D_CONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Black_Bar(unsigned long arg)
{
	int ret = RET_OK;
	BE_BLACK_BAR_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_BLACK_BAR_T *)arg, sizeof(BE_BLACK_BAR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_BLACK_BAR, &stParams, sizeof(BE_BLACK_BAR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Video_Mute(unsigned long arg)
{
	int ret = RET_OK;
	BE_VIDEO_MUTE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_VIDEO_MUTE_T *)arg, sizeof(BE_VIDEO_MUTE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_VIDEO_MUTE, &stParams, sizeof(BE_VIDEO_MUTE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Mute_Color(unsigned long arg)
{
	int ret = RET_OK;
	BE_VIDEO_MUTE_COLOR_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_VIDEO_MUTE_COLOR_T *)arg, sizeof(BE_VIDEO_MUTE_COLOR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_MUTE_COLOR, &stParams, sizeof(BE_VIDEO_MUTE_COLOR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Display_Type(unsigned long arg)
{
	int ret = RET_OK;
	BE_DISPLAY_TYPE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_DISPLAY_TYPE_T *)arg, sizeof(BE_DISPLAY_TYPE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_DISPLAY_TYPE, &stParams, sizeof(BE_DISPLAY_TYPE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Debug_Display(unsigned long arg)
{
	int ret = RET_OK;
	BE_DEBUG_DISPLAY_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_DEBUG_DISPLAY_T *)arg, sizeof(BE_DEBUG_DISPLAY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_DEBUG_DISPLAY, &stParams, sizeof(BE_DEBUG_DISPLAY_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_VID_Operation(unsigned long arg)
{
	int ret = RET_OK;
	BE_VID_OPERATION_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_VID_OPERATION_T *)arg, sizeof(BE_VID_OPERATION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_VID_OPERATION, &stParams, sizeof(BE_VID_OPERATION_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Input_Src_Type(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRC_TYPE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRC_TYPE_T *)arg, sizeof(BE_SRC_TYPE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_SRC_TYPE, &stParams, sizeof(BE_SRC_TYPE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Active_Window_Start(unsigned long arg)
{
	int ret = RET_OK;
	BE_ACTIVE_WINDOW_START_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_ACTIVE_WINDOW_START_T *)arg, sizeof(BE_ACTIVE_WINDOW_START_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_ACTIVE_WINDOW_START, &stParams, sizeof(BE_ACTIVE_WINDOW_START_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Set_Active_Window_Size(unsigned long arg)
{
	int ret = RET_OK;
	BE_ACTIVE_WINDOW_SIZE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_ACTIVE_WINDOW_SIZE_T *)arg, sizeof(BE_ACTIVE_WINDOW_SIZE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_TOP_SET_ACTIVE_WINDOW_SIZE, &stParams, sizeof(BE_ACTIVE_WINDOW_SIZE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_TOP_Firmware_Debug(unsigned long arg)
{
	int ret = RET_OK;
	BE_FIRMWARE_DEBUG_T stParams;

	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_FIRMWARE_DEBUG_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(stParams.u32Cmd, &stParams.u32Param, sizeof(stParams.u32Param));
		if(ret) BREAK_WRONG(ret);

		if(stParams.u8Read)
		{
			ret = BE_KIPC_GetData(&stParams.u32Param, sizeof(stParams.u32Param));
			if(ret) BREAK_WRONG(ret);
			ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_FIRMWARE_DEBUG_T));
			if(ret) BREAK_WRONG(ret);
		}
	} while(0);
	return ret;
}

/**
 * BE cleanup
 *
 * @param   void
 * @return  void
 * @see
 * @author
 */
void BE_Cleanup(void)
{
	BE_PRINT("BE device cleanup\n");
}

#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",BE_Init);
#else
module_init(BE_Init);
#endif
module_exit(BE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("be driver");
MODULE_LICENSE("GPL");
#endif

/** @} */


