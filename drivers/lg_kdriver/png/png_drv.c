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
 *  main driver implementation for png device.
 *	png device will teach you how to make device driver with new platform.
 *
 *  author		juhee.park
 *  version		1.0
 *  date		2011.12.02
 *  note		Additional information.
 *
 *  @addtogroup lg_png
 *	@{
 */

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <asm/irq.h>                    /**< For isr */
#include <asm/io.h>                    /**< For isr */


#include "os_util.h"
#include "base_device.h"
#include "misc_util.h"

#include "png_drv.h"
#include "png_impl.h"

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
#define PNG_USE_UNLOCKED_IOCTL

int	g_png_debug_fd	= -1;
int	g_png_trace_depth = 0;

/* Module param for Debug print */
#define PNG_DEBUG_OFF		0x00
#define PNG_DEBUG_PRINT		0x01
#define PNG_DEBUG_TRACE		0x02
#define PNG_DEBUG_WARN		0x04
#define PNG_DEBUG_ERROR		0x08
#define PNG_DEBUG_PROC		0x10
#define PNG_DEBUG_ASSERT	0x20
#define PNG_DEBUG_SYSFS		0x40
#define PNG_DEBUG_DEVFS		0x80

static int gPNG_DbgLvl = PNG_DEBUG_DEVFS|PNG_DEBUG_WARN|PNG_DEBUG_ERROR;
module_param(gPNG_DbgLvl, int, S_IWUSR);
MODULE_PARM_DESC(gPNG_DbgLvl, "PNG Debugging Level");
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

static int _PNG_requestISR(struct PNG_T *pPNG);

#include "png_io.c"

static struct PNG_T* _gpPNG = NULL;

static long _PNG_UNLOCKED_IOCTL(struct file *file, unsigned int cmd, unsigned long arg)
{
	long res = 0;

	PNG_TRACE_BEGIN();

	cmd = _IOC_NR(cmd);
	cmd -= _IOC_NR(PNG_IOR_GET_CAPS);
   		
	//juhee FIXME if == NULL nosys
	if (cmd < sizeof(_gpIOCTLfns)/sizeof(int*) && _gpIOCTLfns[cmd] != NULL )
	{
#if 0
		juhee
		if (CMD == DECODE)
		{
			if (curState == IDLE)
			{
				pass
			}
			else if (curState == DECODING || curState == DONE)
			{
				wait Queue
			}
			else if (curState == ERROR)
			{
		  	return PNG_HW_ERROR;
			}
#endif

		res = _gpIOCTLfns[cmd](_gpPNG, arg);
	}
	else
	{
		/* redundant check but it seems more readable */
   		PNG_ERROR("[PNG] IOCTL: unknown IOCTL command %08X\n", cmd);

		res = -ENOTTY;
	}

	PNG_TRACE_END();

	return res;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(PNG_USE_UNLOCKED_IOCTL)
static int _PNG_IOCTL(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	return (int)_PNG_UNLOCKED_IOCTL(file, cmd, arg);
}
#endif

/**
 * memory mapping to virtual region
 *
 */
static int _PNG_MMAP(struct file *file, struct vm_area_struct *vma)
{
    int ret;
    UINT32 pfn;
    UINT32 len;
    UINT32 off = ((vma->vm_pgoff) << PAGE_SHIFT);

	if (_gpPNG == NULL)
	{
		PNG_ERROR("ASSERT\n");
		return -EIO;
	}

    pfn = ((UINT32)_gpPNG->src_buf_addr) & PAGE_MASK;
    len = PAGE_ALIGN((pfn & ~PAGE_MASK) + _gpPNG->src_buf_size);

    if ((vma->vm_end - vma->vm_start + off) > len)
    {
   		PNG_ERROR("Not enough memory\n");
        return -ENOMEM;
    }

    off += pfn;

    vma->vm_pgoff = off >> PAGE_SHIFT;
    vma->vm_flags |= VM_IO;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

    ret = io_remap_pfn_range(vma, 
							vma->vm_start, 
							vma->vm_pgoff, 
							vma->vm_end - vma->vm_start,
							vma->vm_page_prot);

    return ret;
}

/**
 * open handler for png device
 *
 */
static int _PNG_Open(struct inode *inode, struct file *filp)
{
#if 0 
	int					major,minor;
    struct cdev*    	cdev;
    PNG_DEVICE_T*		my_dev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, PNG_DEVICE_T, cdev);

    /* TODO : add your device specific code */
	if ( my_dev->dev_open_count == 0 )
	{
		OS_InitEvent( &my_dev->png_event );
		PNG_InitReg( my_dev );
		/* PNG_InitHW may not be execulted until host initialized. but don't worry */
		PNG_InitHW( my_dev );

	}

	/* END */
    my_dev->dev_open_count++;
    filp->private_data = my_dev;

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);

    PNG_PRINT("device opened (%d:%d)\n", major, minor );
#endif
    _gpPNG->changeState(_gpPNG, LX_PNG_STATE_IDLE);
	return 0;
}

/**
 * release handler for png device
 *
 */
static int _PNG_Close(struct inode *inode, struct file *file)
{
#if 0 
    int				major,minor;
    PNG_DEVICE_T*	my_dev;
    struct cdev*	cdev;

    cdev	= inode->i_cdev;
    my_dev	= container_of ( cdev, PNG_DEVICE_T, cdev);

    if ( my_dev->dev_open_count > 0 )
    {
        --my_dev->dev_open_count;
    }

    /* TODO : add your device specific code */
	if ( my_dev->dev_open_count <= 0 )
	{
		PNG_ShutdownHW	( my_dev );
	}

	/* END */

	/* some debug */
    major = imajor(inode);
    minor = iminor(inode);

    PNG_PRINT("device closed (%d:%d)\n", major, minor );
#endif
    return 0;
}


/**
 * file I/O description for png device
 *
*/
static struct file_operations _g_fops =
{
	.open 	= _PNG_Open,
	.release= _PNG_Close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)) || !defined(PNG_USE_UNLOCKED_IOCTL)
	.ioctl	= _PNG_IOCTL,
#else
	.unlocked_ioctl = _PNG_UNLOCKED_IOCTL,
#endif
	.mmap	= _PNG_MMAP,
	.read	= NULL,
	.write	= NULL,
};

static int _PNG_InitDEVFS(void)
{
	int err;

	PNG_Config(&_gpPNG);

	err = register_chrdev_region(_gpPNG->devno, 1, PNG_MODULE );

	cdev_init(&_gpPNG->cdev, &_g_fops);

	_gpPNG->cdev.owner= THIS_MODULE;
	_gpPNG->cdev.ops  = &_g_fops;

	err = cdev_add (&_gpPNG->cdev, _gpPNG->devno, 1 );
	if (err)
	{
		PNG_ERROR("error (%d) while adding PNG device (%d.%d)\n", err, MAJOR(_gpPNG->devno), MINOR(_gpPNG->devno) );
		return -EIO;
	}

	if (gPNG_DbgLvl & PNG_DEBUG_PROC)
	{
		//PNG_PROC_Init();
	}

	return 0;
}

static void _PNG_CleanupDEVFS(void)
{
	PNG_Unconfig(_gpPNG);

	if (gPNG_DbgLvl & PNG_DEBUG_PROC)
	{
		//SE_PROC_Cleanup();
	}
}

#include "png_isr.c"

/*========================================================================================
    Implementation Group : PNG Module
========================================================================================*/
static int _change_state(struct PNG_T* pPNG, LX_PNG_STATE_T state)
{
//	unsigned long flags;
	
//	write_lock_irqsave(&pPNG->state_lock, flags);
	pPNG->cur_state = state;
//	write_unlock_irqrestore(&pPNG->state_lock, flags);

	return RET_OK;
}

/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void PNG_PreInit(void)
{
    /* TODO: do something */
}

int PNG_Init(void)
{
	int res  = 0;

	/* Get the handle of debug output for png device.
	 *
	 * Most module should open debug handle before the real initialization of module.
	 * As you know, debug_util offers 4 independent debug outputs for your device driver.
	 * So if you want to use all the debug outputs, you should initialize each debug output
	 * using OS_DEBUG_EnableModuleByIndex() function.
	 */
	g_png_debug_fd = DBG_OPEN(PNG_MODULE);

	if ( g_png_debug_fd < 0 )
	{
		DBG_PRINT_ERROR("can't register se device\n" );
		return -1;
	}
	OS_DEBUG_EnableModule (g_png_debug_fd);

	if (gPNG_DbgLvl & PNG_DEBUG_PRINT)
	{
		/* Print */
		OS_DEBUG_EnableModuleByIndex(g_png_debug_fd, 0, DBG_COLOR_NONE);
	}
	if (gPNG_DbgLvl & PNG_DEBUG_TRACE)
	{
		/* Trace */
		OS_DEBUG_EnableModuleByIndex(g_png_debug_fd, 1, DBG_COLOR_CYAN);
	}
	if (gPNG_DbgLvl & PNG_DEBUG_WARN)
	{
		/* Warn */
		OS_DEBUG_EnableModuleByIndex(g_png_debug_fd, 2, DBG_COLOR_YELLOW);
	}
	if (gPNG_DbgLvl & PNG_DEBUG_ERROR)
	{
		/* Error */
		OS_DEBUG_EnableModuleByIndex(g_png_debug_fd, 3, DBG_COLOR_RED);
	}

	//FIXME Implement the following
	//if (gPNG_DbgLvl & PNG_DEBUG_ASSERT)

	if (gPNG_DbgLvl & PNG_DEBUG_SYSFS)
	{
	//	res = _PNG_InitSYSFS();
	}
	else // default if (gPNG_DbgLvl & PNG_DEBUG_DEVFS)
	{
		res = _PNG_InitDEVFS();
	}
	rwlock_init(&_gpPNG->state_lock);
	init_waitqueue_head(&_gpPNG->wq_requesters);
	_PNG_requestISR(_gpPNG);
	_gpPNG->changeState = _change_state;
	printk("png device initialized\n");

	return res;
}

void PNG_Cleanup(void)
{
	_PNG_freeISR(_gpPNG);
	if (gPNG_DbgLvl & PNG_DEBUG_SYSFS)
	{
//		_PNG_CleanupSYSFS();
	}
	else // default if (gPNG_DbgLvl & PNG_DEBUG_DEVFS)
	{
		_PNG_CleanupDEVFS();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
module_init(PNG_Init);
module_exit(PNG_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("PNG driver");
MODULE_LICENSE("GPL");
#endif

/** @} */

