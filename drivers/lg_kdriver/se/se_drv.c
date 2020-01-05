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
 *  main driver implementation for se device.
 *	se device will teach you how to make device driver with new platform.
 *
 *  author		stan.kim@lge.com
 *  version		1.0
 *  date		2012.05
 *  note		Additional information.
 *
 *  @addtogroup lg_se
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
#include <linux/version.h>
#include <linux/rmap.h>
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/kthread.h>

#include <asm/io.h>
#include <asm/memory.h>
#include <asm/uaccess.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "se_cfg.h"
#include "se_drv.h"
#include "se_kapi.h"

#include "hma_alloc.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define SE_MODULE	"se"

#define SE_TZ_THREAD_PRIORITY	92

#define SE_TZ_SCHED_WAIT		100		// 100usec
#define SE_USE_YIELD_AS_WAIT	1

#define SE_WAIT					100		// 100usec
#define SE_WAIT_RETRY			50000	// Max : SE_DMA_WAIT_RETRY * SE_DMA_WAIT = 5sec
#define SE_WAIT_LOOP			0x1000000	// > DMA 10MBytes

#define SE_DEBUG_OFF	0x00
#define SE_DEBUG_PRINT	0x01
#define SE_DEBUG_TRACE	0x02
#define SE_DEBUG_WARN	0x04
#define SE_DEBUG_ERROR	0x08

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define SE_PRINT(fmt, args...)   DBG_PRINT(_gSeInfo.debugFd, 0, fmt, ##args)
#define SE_TRACE(fmt, args...)   DBG_PRINT(_gSeInfo.debugFd, 1, fmt, ##args)
#define SE_WARN(fmt, args...)    DBG_PRINT(_gSeInfo.debugFd, 2, "[SE-WRN] %s(%d):" fmt, __F__, __L__, ##args)
#define SE_ERROR(fmt, args...)   DBG_PRINT(_gSeInfo.debugFd, 3, "[SE-ERR] %s(%d):" fmt, __F__, __L__, ##args)

#define SE_CHECK_RESULT(arg, result)	if (arg) {\
											SE_ERROR(#arg"\n");\
											return (result);\
										}

#define _INIT_LOCK(pLock)	sema_init(pLock,1)
#define _LOCK(pLock)		while (down_interruptible(pLock)!=0) \
								SE_ERROR("down_interruptible\n");
#define _UNLOCK(pLock)		up(pLock)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	TZ_SUCCESS					= 8000,
	TZ_TIMER_SCHED				= TZ_SUCCESS + 4,

	TZ_FAIL 					= -8000,
	TZ_FAIL_VERSION_MISMATCH	= TZ_FAIL - 1,
	TZ_FAIL_NOT_SUPPORTED_CHIP	= TZ_FAIL - 2,
	TZ_FAIL_WRONG_CMD			= TZ_FAIL - 3,
	TZ_FAIL_NOT_IMPLEMENTED 	= TZ_FAIL - 4,
	TZ_FAIL_ILLEGAL_ARGUMENT	= TZ_FAIL - 5,
	TZ_FAIL_BUSY				= TZ_FAIL - 6,
} TZ_RETURN_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _SE_Open(struct inode *inode, struct file *filp);
static int _SE_Close(struct inode *inode, struct file *filp);
static int _SE_MMAP(struct file *file, struct vm_area_struct *vma);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int _SE_IOCTL(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
#endif
static long _SE_UNLOCKED_IOCTL(struct file *file, unsigned int cmd, unsigned long arg);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

// SE Device Info
static struct _SeInfo_tag {
	UINT32 chip;
	UINT32 platform;

	int debugFd;

	// For TZ Operation
	struct task_struct *pTzOperationThread;
	struct semaphore semaTzOperationStart;
	struct semaphore semaTzOperationEnd;

	UINT32 tzArgs[8];
	int tzResult;

	UINT8 *pWaitMap;
	UINT32 *pWait;
#if (SE_USE_YIELD_AS_WAIT==0)
	wait_queue_head_t waitQueue;
#endif

	// For HMA Allocation
	unsigned long hmaAddress;
	int hmaSize;

	// For Device
	dev_t devNum;
	struct cdev cDev;
	struct file_operations fileOperations;
} _gSeInfo = {
	.debugFd			= -1,
	.pTzOperationThread = NULL,

	.pWaitMap			= NULL,
	.pWait				= NULL,

	.hmaAddress			= 0,
	.hmaSize			= 0,

	.fileOperations 	= {
		.open			= _SE_Open,
		.release		= _SE_Close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
		.ioctl			= _SE_IOCTL,
#else
		.unlocked_ioctl = _SE_UNLOCKED_IOCTL,
#endif
		.mmap			= _SE_MMAP,
		.read			= NULL,
		.write			= NULL,
	},
};

static int _gDebugLvl = SE_DEBUG_ERROR;
module_param(_gDebugLvl, int, S_IWUSR);
MODULE_PARM_DESC(_gDebugLvl, "Debugging Level");

/*========================================================================================
    Implementation Group : SE CDEV
========================================================================================*/

static void _TzCmd(void)
{
	isb();
	dsb();
	dmb();

	asm volatile (
        "LDM    %1, {r0-r7}\n"
        ".word  0xe1600070 @SMC 0\n"
        "MOV    %0, r0\n"
        : "=r" (_gSeInfo.tzArgs[0])
        : "r"  (_gSeInfo.tzArgs)
        : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r12"
    );
}

static int _RunTzCmd(void)
{
	do {
		_TzCmd();
		if ((TZ_RETURN_T)_gSeInfo.tzArgs[0]==TZ_TIMER_SCHED) {
#if (SE_USE_YIELD_AS_WAIT==0)
			/*
			; Set current process state to interruptible sleep.
			*/
			set_current_state(TASK_INTERRUPTIBLE);

			/*
			; Take a nap and wake up after specified time.
			*/
			if (schedule_timeout(usecs_to_jiffies(SE_TZ_SCHED_WAIT))<0)	// Just Check
				SE_ERROR("Negative return in schedule_timeout()\n");
#else	// for performance
			yield();
#endif
		}
	} while ((TZ_RETURN_T)_gSeInfo.tzArgs[0]==TZ_TIMER_SCHED);

	switch ((TZ_RETURN_T)_gSeInfo.tzArgs[0]) {
		case TZ_SUCCESS :
			return 0;

		case TZ_FAIL :
			SE_ERROR("TZ_FAIL\n");
			break;

		case TZ_FAIL_VERSION_MISMATCH :
			SE_ERROR("TZ_FAIL_VERSION_MISMATCH - Update sedrv and tzfw.\n");
			break;

		case TZ_FAIL_NOT_SUPPORTED_CHIP :
			SE_ERROR("TZ_FAIL_NOT_SUPPORTED_CHIP\n");
			break;

		case TZ_FAIL_WRONG_CMD :
			SE_ERROR("TZ_FAIL_WRONG_CMD\n");
			break;

		case TZ_FAIL_NOT_IMPLEMENTED :
			SE_ERROR("TZ_FAIL_NOT_IMPLEMENTED\n");
			break;

		case TZ_FAIL_ILLEGAL_ARGUMENT :
			SE_ERROR("TZ_FAIL_ILLEGAL_ARGUMENT\n");
			break;

		case TZ_FAIL_BUSY :
			SE_ERROR("TZ_FAIL_BUSY\n");
			break;

		default :
			SE_ERROR("Unknown(0x%x)\n", _gSeInfo.tzArgs[0]);
			break;
	}

	return -1;
}

static int _tzOperationThread(void *pArg)
{
	while (!kthread_should_stop()) {
		_LOCK(&_gSeInfo.semaTzOperationStart);

		_gSeInfo.tzResult = _RunTzCmd();

		_UNLOCK(&_gSeInfo.semaTzOperationEnd);
	}
	_UNLOCK(&_gSeInfo.semaTzOperationStart);
	SE_PRINT("Stop thread\n");

	return 0;
}

static int _runTzOperation(unsigned long arg)
{
	SE_CHECK_RESULT(copy_from_user((void *)_gSeInfo.tzArgs, (void __user *)arg, sizeof(_gSeInfo.tzArgs)), -EIO);

	_UNLOCK(&_gSeInfo.semaTzOperationStart);
	_LOCK(&_gSeInfo.semaTzOperationEnd);

	SE_CHECK_RESULT(_gSeInfo.tzResult < 0, -EIO);
	SE_CHECK_RESULT(copy_to_user((void __user *)arg, (void *)_gSeInfo.tzArgs, sizeof(_gSeInfo.tzArgs)), -EIO);

	return 0;
}

static int _wait(unsigned long arg)
{
	UINT32 pageAddr;
	int i;

	if (_gSeInfo.pWaitMap==NULL) {
		SE_CHECK_RESULT(arg==0, -EIO);

		pageAddr = arg & (~(PAGE_SIZE-1));
		_gSeInfo.pWaitMap = ioremap(pageAddr, PAGE_SIZE);
		SE_CHECK_RESULT(_gSeInfo.pWaitMap==NULL, -EIO);

		_gSeInfo.pWait = (UINT32 *)(_gSeInfo.pWaitMap + (arg - pageAddr));
#if (SE_USE_YIELD_AS_WAIT==0)
		init_waitqueue_head(&_gSeInfo.waitQueue);
#endif
	}

#if (SE_USE_YIELD_AS_WAIT==0)
	for (i=0; i<SE_WAIT_RETRY; i++) {
		if (*_gSeInfo.pWait==0) {
			return 0;
		}
		wait_event_timeout_interruptible(_gSeInfo.waitQueue, (*_gSeInfo.pWait==0), usecs_to_jiffies(SE_WAIT));
	}
#else	// for performance
	for (i=0; i<SE_WAIT_LOOP; i++) {
		if (*_gSeInfo.pWait==0) {
			return 0;
		}
		yield();
	}
#endif

	SE_ERROR("Time out!\n");
	return -EIO;
}

static int _getMemInfo(unsigned long arg)
{
	SE_CHECK_RESULT(copy_to_user((void __user *)arg,
		(void *)&gMemCfgSE, sizeof(LX_MEMCFG_T)), -EIO);
	SE_CHECK_RESULT(copy_to_user((void __user *)arg + sizeof(LX_MEMCFG_T),
		(void *)&gMemCfgSE_TZFW, sizeof(LX_MEMCFG_T)), -EIO);

	return 0;
}

static long _SE_UNLOCKED_IOCTL(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
		case SE_IORW_RUN_TZ_OP :
			return _runTzOperation(arg);

		case SE_IOR_WAIT :
			return _wait(arg);

		case SE_IOW_GET_MEM_INFO :
			return _getMemInfo(arg);

		default :
			break;
	}

	SE_ERROR("Not defined(%d)\n", cmd);
	return -ENOTTY;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
static int _SE_IOCTL(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	return (int)_SE_UNLOCKED_IOCTL(file, cmd, arg);
}
#endif

static int _SE_MMAP(struct file *file, struct vm_area_struct *vma)
{
	vma->vm_flags |= VM_IO;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
		vma->vm_end - vma->vm_start, vma->vm_page_prot);
}

static int _SE_Open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int _SE_Close(struct inode *inode, struct file *filp)
{
	return 0;
}

/*========================================================================================
    Implementation Group : SE Module
========================================================================================*/
/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void SE_PreInit(void)
{
    /* TODO: do something */
}

int SE_Init(void)
{
	/* Get the handle of debug output for se device.
	*
	* Most module should open debug handle before the real initialization of module.
	* As you know, debug_util offers 4 independent debug outputs for your device driver.
	* So if you want to use all the debug outputs, you should initialize each debug output
	* using OS_DEBUG_EnableModuleByIndex() function.
	*/
	_gSeInfo.debugFd = DBG_OPEN(SE_MODULE);

	SE_CHECK_RESULT(_gSeInfo.debugFd<0, -1);
	OS_DEBUG_EnableModule(_gSeInfo.debugFd);

	if (_gDebugLvl & SE_DEBUG_PRINT)
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, 0, DBG_COLOR_NONE);

	if (_gDebugLvl & SE_DEBUG_TRACE)
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, 1, DBG_COLOR_CYAN);

	if (_gDebugLvl & SE_DEBUG_WARN)
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, 2, DBG_COLOR_YELLOW);

	if (_gDebugLvl & SE_DEBUG_ERROR)
		OS_DEBUG_EnableModuleByIndex(_gSeInfo.debugFd, 3, DBG_COLOR_RED);

	_gSeInfo.chip = lx_chip_rev();
	_gSeInfo.platform = lx_chip_plt();

	switch (_gSeInfo.platform) {
		case LX_CHIP_PLATFORM_GP :
			break;

		case LX_CHIP_PLATFORM_COSMO :
			break;

		default :
			SE_ERROR("Unknown Platform Setting : Use default\n");
			break;
	}

	switch (_gSeInfo.chip) {
		case LX_CHIP_REV(L9,A0):
		case LX_CHIP_REV(L9,A1):
		case LX_CHIP_REV(L9,B0):
		case LX_CHIP_REV(L9,B1):
		case LX_CHIP_REV(H13,A0):
		case LX_CHIP_REV(H13,A1):
		case LX_CHIP_REV(H13,B0):
			break;

		default :
			SE_ERROR("Unknown Chip Setting : Use default\n");
			break;
	}

	// Sync Mutex for tz operation thread
	_INIT_LOCK(&_gSeInfo.semaTzOperationStart);
	_INIT_LOCK(&_gSeInfo.semaTzOperationEnd);
	_LOCK(&_gSeInfo.semaTzOperationStart);
	_LOCK(&_gSeInfo.semaTzOperationEnd);

	// Thread create
	_gSeInfo.pTzOperationThread = kthread_create(_tzOperationThread, NULL, "setzkthread");
	if (IS_ERR(_gSeInfo.pTzOperationThread)) {
		SE_ERROR("while kthread_create()\n");
		_gSeInfo.pTzOperationThread = NULL;
		return -EIO;
	}

	// Bind se_tz_kthread to CPU0
	kthread_bind(_gSeInfo.pTzOperationThread, 0);	// Bind setzkthread to CPU0

	// Set Real-Time Priority
	{
		struct sched_param param = { 0 };

		param.sched_priority = SE_TZ_THREAD_PRIORITY;
		if (sched_setscheduler(_gSeInfo.pTzOperationThread, SCHED_FIFO, &param)!=0) {
			SE_ERROR("Can't change priority\n");
		}
	}

	// Start thread
	wake_up_process(_gSeInfo.pTzOperationThread);

	// Register Device
	_gSeInfo.devNum = MKDEV(SE_MAJOR, SE_MINOR);
	SE_CHECK_RESULT(register_chrdev_region(_gSeInfo.devNum, 1, SE_MODULE), -EIO);
	cdev_init(&_gSeInfo.cDev, &_gSeInfo.fileOperations);
	SE_CHECK_RESULT(cdev_add(&_gSeInfo.cDev, _gSeInfo.devNum, 1), -EIO);
	OS_CreateDeviceClass(_gSeInfo.devNum, "%s%d", SE_MODULE, 0);

	return 0;
}

void SE_Cleanup(void)
{
	// Stop Thread
	if (_gSeInfo.pTzOperationThread!=NULL) {
		_UNLOCK(&_gSeInfo.semaTzOperationStart);
		kthread_stop(_gSeInfo.pTzOperationThread);
		_gSeInfo.pTzOperationThread = NULL;
	}

	// iounmap
	if (_gSeInfo.pWaitMap!=NULL)
		iounmap(_gSeInfo.pWaitMap);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(KDRV_GLOBAL_LINK) || defined(MAKE_SE_MODULE)
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP) && !defined(MAKE_SE_MODULE)
user_initcall_grp("kdrv",SE_Init);
#else
module_init(SE_Init);
#endif
module_exit(SE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("SE driver");
MODULE_LICENSE("GPL");
#endif
/** @} */

