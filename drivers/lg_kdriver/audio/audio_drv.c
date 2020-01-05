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


/** @file	audio_kdrv.c
 *
 *  main driver implementation for  audio device.
 *  audio device will teach you how to make device driver with new platform.
 *
 *  author	wonchang.shin (wonchang.shin@lge.com)
 *  version	0.1
 *  date		2012.04.24
 *  note		Additional information.
 *
 *  @addtogroup lg1150_audio
 *	@{
 */


/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>    /**< For isr */
#include <linux/irq.h>			/**< For isr */
#include <linux/ioport.h>		/**< For request_region, check_region etc */
#include <linux/rmap.h>
#include <linux/kthread.h>
#include <asm/io.h>				/**< For ioremap_nocache */
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/version.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"

#include "debug_util.h"
#include "audio_cfg.h"
#include "audio_reg.h"
#include "audio_drv.h"

#include "audio_drv_decoder.h"
#include "audio_drv_encoder.h"
#include "audio_drv_capturer.h"
#include "audio_drv_renderer.h"
#include "audio_drv_master.h"


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
const char* gcAudDevMod[AUDIO_DEVICE_MAX] =
{
	"adec0",		// audio decoder 	00
	"aenc0",		// audio encoder 	01
	"acap0",		// audio capturer 	02
	"aren0",		// audio renderer 	03
	"amst0"			// audio master 	04
};


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void	AUDIO_PROC_Init (char* procName);
extern void	AUDIO_PROC_Cleanup (char* procName);
extern irqreturn_t AUDIO_interrupt0 (int irq, void *dev_id, struct pt_regs *regs);
extern irqreturn_t AUDIO_interrupt1 (int irq, void *dev_id, struct pt_regs *regs);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern LX_AUD_REG_CFG_T	*pstAudRegCfg;


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int	g_AudDebugFd = 0;
int g_AudMajor 	 = AUDIO_MAJOR;
int g_AudMinor 	 = AUDIO_MINOR;

AUD_DEVICE_T 	*g_AudDev;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static unsigned int KDRV_AUDIO_PollMaster(struct file *filp, poll_table *wait);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct file_operations g_audio_fops[LX_MAX_DEVICE_NAME] =
{
	// audio decoder
	{
	.open 		= KDRV_AUDIO_OpenDecoder,
	.release	= KDRV_AUDIO_CloseDecoder,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl		= KDRV_AUDIO_IoctlDecoder,
#else
	.unlocked_ioctl	= KDRV_AUDIO_IoctlDecoder,
#endif
	},
	// audio encoder
	{
	.open 		= KDRV_AUDIO_OpenEncoder,
	.release	= KDRV_AUDIO_CloseEncoder,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl		= KDRV_AUDIO_IoctlEncoder,
#else
	.unlocked_ioctl	= KDRV_AUDIO_IoctlEncoder,
#endif
	},
	// audio capturer
	{
	.open 	= KDRV_AUDIO_OpenCapture,
	.release	= KDRV_AUDIO_CloseCapture,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl		= KDRV_AUDIO_IoctlCapture,
#else
	.unlocked_ioctl	= KDRV_AUDIO_IoctlCapture,
#endif
	},
	// audio renderer
	{
	.open 	= KDRV_AUDIO_OpenRenderer,
	.release	= KDRV_AUDIO_CloseRenderer,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl		= KDRV_AUDIO_IoctlRenderer,
#else
	.unlocked_ioctl	= KDRV_AUDIO_IoctlRenderer,
#endif
	},
	// audio master
	{
	.open 		= KDRV_AUDIO_OpenMaster,
	.release	= KDRV_AUDIO_CloseMaster,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
	.ioctl		= KDRV_AUDIO_IoctlMaster,
#else
	.unlocked_ioctl	= KDRV_AUDIO_IoctlMaster,
#endif
	.poll 		= KDRV_AUDIO_PollMaster,
	},
};

/*========================================================================================
	Implementation Group
========================================================================================*/
/** Initialize the device environment before the real H/W initialization
 *
 *  @note main usage of this function is to initialize the HAL layer and memory size adjustment
 *  @note it's natural to keep this function blank :)
 */
void AUDIO_PreInit(void)
{
    /* TODO: do something */
}

int      AUDIO_Init(void)
{
	int						retVal = 0;
	int						i;
	dev_t					dev;
	char 					dev_name[LX_MAX_DEVICE_NAME];

	g_AudDebugFd = DBG_OPEN( AUDIO_MODULE );

	if ( g_AudDebugFd < 0 )
	{
		DBG_PRINT_ERROR("debug system shutdowned.\n" );
		return -EIO;
	}

	OS_DEBUG_EnableModule ( g_AudDebugFd );

	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 0);						//AUD_KDRV_PRINT
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 1);						//AUD_KDRV_TRACE
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 2);						//AUD_KDRV_ISR_DEBUG
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 3);						//AUD_KDRV_MIP_DEBUG
	OS_DEBUG_EnableModuleByIndex (g_AudDebugFd, 4, DBG_COLOR_NONE);	//AUD_KDRV_ERROR
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 5);						//AUD_KDRV_DEBUG
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 6);						//AUD_KDRV_DEBUG_TMP
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 7);						//AUD_KDRV_IPC_DEBUG
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 8);						//AUD_KDRV_IPC_MSG
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 9);						//AUD_KDRV_MIP_I2C
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 10 );						//AUD_KDRV_RM
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 11 );						//AUD_KDRV_RMD
	//OS_DEBUG_EnableModuleByIndex(g_AudDebugFd, 10,DBG_COLOR_CYAN );						//AUD_KDRV_RM
	//OS_DEBUG_EnableModuleByIndex(g_AudDebugFd, 11,DBG_COLOR_RED );						//AUD_KDRV_RM
	OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, 12 );					//AUD_KRDV_IPC_DBG_ERR

	g_AudDev = (AUD_DEVICE_T*)OS_KMalloc( sizeof(AUD_DEVICE_T)*AUDIO_DEVICE_MAX );

	if ( g_AudDev == NULL )
	{
		DBG_PRINT_ERROR("out of memory. can't allocate %d bytes\n", sizeof(AUD_DEVICE_T)* AUDIO_DEVICE_MAX );
		return -ENOMEM;
	}

	memset( g_AudDev, 0x0, sizeof(AUD_DEVICE_T)* AUDIO_DEVICE_MAX );

	if (g_AudMajor)
	{
		dev = MKDEV( g_AudMajor, g_AudMinor );
		retVal = register_chrdev_region(dev, AUDIO_DEVICE_MAX, AUDIO_MODULE );
	}
	else
	{
		retVal = alloc_chrdev_region(&dev, g_AudMinor, AUDIO_DEVICE_MAX, AUDIO_MODULE );
		g_AudMajor = MAJOR(dev);
	}

	if ( retVal < 0 )
	{
		AUD_KDRV_ERROR("can't register audio device\n" );
		return -EIO;
	}

	for ( i=0; i<AUDIO_DEVICE_MAX; i++ )
	{
		/* initialize cdev structure with predefined variable */
		dev = MKDEV( g_AudMajor, g_AudMinor+i );
		cdev_init(&(g_AudDev[i].cdev), &g_audio_fops[i]);

		g_AudDev[i].devNo			= dev;
		g_AudDev[i].cdev.owner		= THIS_MODULE;
		g_AudDev[i].cdev.ops		= &g_audio_fops[i];
		g_AudDev[i].allocDev		= AUD_NO_DEV;
		g_AudDev[i].isInit			= FALSE;
		g_AudDev[i].openCount		= 0;

 		retVal = cdev_add (&g_AudDev[i].cdev, dev, 1 );
		if (retVal)
		{
			AUD_KDRV_ERROR("error (%d) while adding audio capture device (%d.%d)\n", retVal, MAJOR(dev), MINOR(dev) );
			return -EIO;
		}

		OS_CreateDeviceClass(dev, "%s", gcAudDevMod[i]);
		sprintf(dev_name, "%s",  gcAudDevMod[i]);

		/* initialize proc system */
		AUDIO_PROC_Init(dev_name);
	}

	//Initialize Audio Decoder(DSP) register base
	/* Check LX Chip Revision Number */
	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		AUD_KDRV_DEBUG_TMP ("LX_CHIP_REV(H13, XX)(0x%X)\n", lx_chip_rev());

		pstAudRegCfg = &g_stAudRegCfg[1];
		pstMemCfgAud = &g_stMemCfgAud[0];

		AUD_KDRV_DEBUG("reg_base_addr = 0x%X, size = 0x%X\n", pstAudRegCfg->reg_base_addr, pstAudRegCfg->reg_size);
	}
	else if(lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		AUD_KDRV_DEBUG_TMP ("LX_CHIP_REV(L9, BX)(0x%X)\n", lx_chip_rev());

		pstAudRegCfg = &g_stAudRegCfg[0];
		pstMemCfgAud = &g_stMemCfgAud[0];

		AUD_KDRV_DEBUG("reg_base_addr = 0x%X, size = 0x%X\n", pstAudRegCfg->reg_base_addr, pstAudRegCfg->reg_size);
	}
	else
	{
		DBG_PRINT_ERROR("ADEC : LX_CHIP_REV => Unknown(0x%X) : ERROR\n", lx_chip_rev());
		return -EIO;
	}

	//Initializes the clock and reset module register value.
	MIXED_IP_AUDIO_InitClockRegisters();

	//Initialize IRQ0 of ADEC DSP0
	retVal = request_irq(pstAudRegCfg->irq0_num, (irq_handler_t)AUDIO_interrupt0, 0, "AUDIO0", NULL);
	if (retVal)
	{
		AUD_KDRV_ERROR("request_irq IRQ_AUD0 in %s is failed %d\n", "ADEC0 ", retVal);
		return -1;
	}
	AUD_KDRV_PRINT("adec irq0 registered :%d:\n", pstAudRegCfg->irq0_num );

	//Initialize IRQ1 of ADEC DSP1
	retVal = request_irq(pstAudRegCfg->irq1_num, (irq_handler_t)AUDIO_interrupt1, 0, "AUDIO1", NULL);
	if (retVal)
	{
		AUD_KDRV_ERROR("request_irq IRQ_AUD1 in %s is failed %d\n", "ADEC1 ", retVal);
		free_irq(pstAudRegCfg->irq0_num, NULL);
		return -1;
	}
	AUD_KDRV_PRINT("adec irq1 registered :%d:\n", pstAudRegCfg->irq1_num);

	return retVal;
}

void AUDIO_Cleanup(void)
{
	int 	i;

	dev_t 	dev = MKDEV( g_AudMajor, g_AudMinor );
	char 	dev_name[LX_MAX_DEVICE_NAME];

	/* remove all minor devicies and unregister current device */
	for ( i=0; i<AUDIO_DEVICE_MAX;i++)
	{
		sprintf(dev_name, "%s",  gcAudDevMod[i]);

		AUDIO_PROC_Cleanup(dev_name);

		cdev_del( &(g_AudDev[i].cdev) );
	}

	/* TODO : add your device specific code */

	//Release IRQ0 of AUDIO
	free_irq(pstAudRegCfg->irq0_num, NULL);
	AUD_KDRV_PRINT("free_irq IRQ_AUD0 released :%d:\n", pstAudRegCfg->irq0_num);

	//Release IRQ1 of ADEC
	free_irq(pstAudRegCfg->irq1_num, NULL);
	AUD_KDRV_PRINT("free_irq IRQ_AUD1 released :%d:\n", pstAudRegCfg->irq1_num);

	/* END */

	unregister_chrdev_region(dev, AUDIO_DEVICE_MAX );
	OS_Free( g_AudDev );

	return;
}

static unsigned int KDRV_AUDIO_PollMaster(struct file *filp, poll_table *wait)
{
	UINT8	i;

	AUD_KDRV_PRINT("Audio Poll wait!!!\n");

	poll_wait(filp, &gAudPollWaitQueue, wait);

	//Set a audio GET event type for next event.
	for(i = 0; i < AUD_DEV_MAS0; i++)
	{
		if( (gAudGetEvent[i].allocDev != AUD_NO_DEV)		\
		  &&(gAudGetEvent[i].eventMsg & LX_AUD_EVENT_MASK_ALL) )
		{
		 	return POLLIN;
		}
	}

   	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef KDRV_GLOBAL_LINK
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",AUDIO_Init);
#else
module_init(AUDIO_Init);
#endif
module_exit(AUDIO_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("base driver");
MODULE_LICENSE("GPL");
#endif

/** @} */


