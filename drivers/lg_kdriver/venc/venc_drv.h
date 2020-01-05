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
 *  driver interface header for venc device. ( used only within kdriver )
 *	venc device will teach you how to make device driver with new platform.
 *
 *  @author		youngwoo.jin (youngwoo.jin@lge.com)
 *  @version	1.0
 *  @date		2011.05.19
 *
 *  @addtogroup lg1152_venc
 *	@{
 */

#ifndef	_VENC_DRV_H_
#define	_VENC_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "venc_cfg.h"
#include "venc_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define VENC_KDRV_MSG(index, format, args...)	do { \
		if ( gVencMSGFlag & (0x1 << index)  ) { \
			DBG_PRINT(  g_venc_debug_fd, index, format, ##args); \
		}	\
	} while(0)
#define SET_VENC_MSG_INDEX( index )		(gVencMSGFlag = gVencMSGFlag | (1<<(index)))
#define UNSET_VENC_MSG_INDEX( index )	(gVencMSGFlag = gVencMSGFlag & ~(1<<(index)))
#define GET_VENC_MSG_INDEX( index )		(gVencMSGFlag & (1<<(index)))

#if 1
#define	VENC_PRINT(format, args...)		VENC_KDRV_MSG( VENC_MSG_NORMAL, format, ##args)
#define	VENC_ERROR(format, args...)		VENC_KDRV_MSG( VENC_MSG_ERROR, format, ##args)
#define	VENC_DEBUG(format, args...)		VENC_KDRV_MSG( VENC_MSG_DEBUG, format, ##args)
#define	VENC_TRACE(format, args...)		VENC_KDRV_MSG( VENC_MSG_TRACE, format, ##args)
#define	VENC_VSYNC(format, args...)		VENC_KDRV_MSG( VENC_MSG_VSYNC, format, ##args)
#define	VENC_TIMER(format, args...)		VENC_KDRV_MSG( VENC_MSG_TIMER, format, ##args)
#define	VENC_INTER(format, args...)		VENC_KDRV_MSG( VENC_MSG_INTER, format, ##args)
#define	VENC_INFO(format, args...)		VENC_KDRV_MSG( VENC_MSG_INFO, format, ##args)
#define	VENC_WARN(format, args...)		VENC_KDRV_MSG( VENC_MSG_WARN, format, ##args)
#else
#define	VENC_PRINT(format, args...)		
#define	VENC_ERROR(format, args...)		
#define	VENC_DEBUG(format, args...)		
#define	VENC_TRACE(format, args...)		
#endif

#define SET_VENC_CFG_CTRL_INDEX( index )	(gVencCFGFlag = gVencCFGFlag | (1<<(index)))
#define UNSET_VENC_CFG_CTRL_INDEX( index ) 	(gVencCFGFlag = gVencCFGFlag & ~(1<<(index)))
#define GET_VENC_CFG_CTRL_INDEX( index )	(gVencCFGFlag & (1<<(index)))

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	VENC_MSG_NORMAL = 0,
	VENC_MSG_ERROR,
	VENC_MSG_DEBUG,
	VENC_MSG_TRACE,
	VENC_MSG_VSYNC,		// vsync
	VENC_MSG_TIMER,		// timer
	VENC_MSG_INTER,		// interrupt
	VENC_MSG_INFO,		// info (config, reg)
	VENC_MSG_WARN,		// warning

	VENC_MSG_INDEX_COUNT
} VENC_MSG_TYPE_T;

typedef enum {
	VENC_CFG_CTRL_FLIP_TB = 0,
	VENC_CFG_CTRL_SCD,
	VENC_CFG_CTRL_SAR,

	VENC_CFG_CTRL_COUNT
} VENC_CFG_CTRL_TYPE_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     VENC_PreInit(void);
extern	int      VENC_Init(void);
extern	void     VENC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_venc_debug_fd;
extern 	UINT32	gVencMSGFlag;
extern 	UINT32 	gVencCFGFlag;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VENC_DRV_H_ */

/** @} */
