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
 *  driver interface header for audio device. ( used only within kdriver )
 *	audio device will teach you how to make device driver with new platform.
 *
 *  @author	wonchang.shin (wonchang.shin@lge.com)
 *  @version	0.1
 *  @date		2012.04.23
 *
 *  @addtogroup lg1150_audio
 *	@{
 */

#ifndef	_AUDIO_DRV_H_
#define	_AUDIO_DRV_H_

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
#include <linux/interrupt.h>    /**< For isr */
#include <linux/irq.h>			/**< For isr */
#include <linux/ioport.h>		/**< For request_region, check_region etc */
#include <linux/rmap.h>
#include <linux/kthread.h>
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <linux/poll.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "debug_util.h"

#include "audio_kapi.h"
#include "audio_cfg.h"
#include "audio_drv_hal_mixedIP.h"

#include "module/adec_module_list.h"
#include "audio_drv_manager.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

extern	int		g_AudDebugFd;

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define NORMAL		0
#define _TRACE		1
#define NORMAL1		2
#define NORMAL2		3
#define ERROR		4
#define WARNING		5
#define NORMAL3		6
#define NORMAL4		7
#define NORMAL5		8
#define NORMAL6		9

//Define Debug Print
#define ADEC_OPT_USE_DEBUG			1
#define ADEC_OPT_USE_ASSERT			1

//Define a overflow protection
#define NOT_USE_OVERFLOW_PROTECTION	0
#define USE_OVERFLOW_PROTECTION		1

#define	AUDIO_CPB_MAX		2
#define	AUDIO_DPB_MAX		2
#define	AUDIO_MIX_MAX		8
#define	AUDIO_CAP_MAX		3
#define	AUDIO_IEC_MAX		2

#define AUD_EVENT_NUM	   20

//#define ENABLE_SOLA


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	AUD_KDRV_PRINT(format, args...)				DBG_PRINT( g_AudDebugFd, 0, format, ##args)
#define	AUD_KDRV_TRACE(format, args...)				DBG_PRINT( g_AudDebugFd, 1, format, ##args)
#define	AUD_KDRV_ISR_DEBUG(format, args...)			DBG_PRINT( g_AudDebugFd, 2, format, ##args)
#define	AUD_KDRV_MIP_DEBUG(format, args...)			DBG_PRINT( g_AudDebugFd, 3, format, ##args)
#define	AUD_KDRV_ERROR(format, args...)				DBG_PRINT( g_AudDebugFd, 4, format, ##args)
#define	AUD_KDRV_DEBUG(format, args...)				DBG_PRINT( g_AudDebugFd, 5, format, ##args)
#define	AUD_KDRV_DEBUG_TMP(format, args...)			DBG_PRINT( g_AudDebugFd, 6, format, ##args)
#define	AUD_KDRV_IPC_DEBUG(format, args...)			DBG_PRINT( g_AudDebugFd, 7, format, ##args)
#define	AUD_KDRV_IPC_MSG0(format, args...)			DBG_PRINT( g_AudDebugFd, 8, format, ##args)
#define	AUD_KDRV_MIP_I2C(format, args...)			DBG_PRINT( g_AudDebugFd, 9, format, ##args)
#define	AUD_KDRV_RM(format, args...)				DBG_PRINT( g_AudDebugFd, 10, format, ##args)
#define	AUD_KDRV_RMD(format, args...)				DBG_PRINT( g_AudDebugFd, 11, format, ##args)
#define AUD_KDRV_IPC_MSG1(format, args...)			DBG_PRINT( g_AudDebugFd, 12, format, ##args)
#define AUD_KDRV_IPC_DBG_ERR(format, args...)		DBG_PRINT( g_AudDebugFd, 13, format, ##args)

#define	AUD_KDRV_TRACE_BEGIN()						AUD_KDRV_TRACE("[AUDIO] BEGIN -- %s:%d\n", __FUNCTION__, __LINE__ )
#define	AUD_KDRV_TRACE_END()						AUD_KDRV_TRACE("[AUDIO] END   -- %s:%d\n", __FUNCTION__, __LINE__ )
#define	AUD_KDRV_TRACE_MARK()						AUD_KDRV_TRACE("[AUDIO] %s:%d\n -- TRACING...", __FUNCTION__, __LINE__ )

#define	AUD_KDRV_Message(level, format, args...)	DBG_PRINT( g_AudDebugFd, level, format "\n", ##args)

#if (ADEC_OPT_USE_DEBUG == 1)
#define AUD_DEBUG_PRINT						AUD_KDRV_PRINT
#define AUD_DEBUG_LOW						AUD_KDRV_DEBUG
#define AUD_DEBUG_ERR						AUD_KDRV_ERROR
#else
#define AUD_DEBUG_PRINT(...)
#define AUD_DEBUG_LOW(...)
#define AUD_DEBUG_ERR(...)
#endif

#if (ADEC_OPT_USE_ASSERT == 1)
#define AUD_ASSERT(_COND, _RETVAL, ...)		if((_COND) == 0){AUD_DEBUG_ERR(__VA_ARGS__);return _RETVAL; }
#else
#define AUD_ASSERT(...)
#endif

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * AUDIO Device Information.
 */
typedef struct
{
	LX_AUD_DEVICE_T		devType;	/* device type */
	LX_AUD_ALLOC_DEV_T	allocDev;	/* alloc device*/
	dev_t				devNo;		/* device number */
	struct cdev			cdev;		/* charactor device struct */
	bool				isInit;		///< check if device is initialized
	void*				devInfo;	///< device info
	UINT32				openCount;	///< device open count (reference count)
} AUD_DEVICE_T;

/**
 * AUDIO Event Information.
 */
typedef struct
{
	UINT32 event;
	UINT32 actionID;

	ADEC_MODULE_ID moduleID;
} AUD_EVENT_T;

/**
 * AUDIO Connect Information.
 */
typedef struct
{
	LX_AUD_DEV_TYPE_T 	devType;
	LX_AUD_ALLOC_DEV_T 	connectDev;
} AUD_CONNECT_T;

/**
 * Interrupt Index.
 * Audio DTO Interrupt Index is defined.
 *
 */
typedef enum
{
    AUD_INT_NOTDEF,
    AUD_INT_PCM,
    AUD_INT_PCMSUB,
    AUD_INT_SPDIF,
    AUD_INT_HWSRCI,
    AUD_INT_HWSRCO,
    AUD_INT_HDMIIN,
    AUD_INT_ADCIN,
    AUD_INT_AADIN,
    AUD_INT_MAX,
} AUD_INT_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     AUDIO_PreInit(void);
extern	int      AUDIO_Init(void);
extern	void     AUDIO_Cleanup(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _AUDIO_DRV_H_ */

/** @} */
