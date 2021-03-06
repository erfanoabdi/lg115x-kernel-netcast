
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
 *  driver interface header for aad device. ( used only within kdriver )
 *	aad device will teach you how to make device driver with new platform.
 *
 *  @author		jongsang.oh (jongsang.oh@lge.com)
 *  @version	1.0
 *  @date		2010.01.26
 *
 *  @addtogroup lg1150_aad
 *	@{
 */

#ifndef	_AAD_DRV_H_
#define	_AAD_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "aad_cfg.h"
#include "aad_kapi.h"

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
#if 0
#define	AAD_PRINT(format, args...)		DBG_PRINT(  g_aad_debug_fd, 0, format, ##args)
#define	AAD_TRACE(format, args...)		DBG_PRINTX( g_aad_debug_fd, 0, format, ##args)
#else
#define	AAD_PRINT(format, args...)		DBG_PRINT( g_aad_debug_fd, 0, format, ##args)
#define	AAD_TRACE(format, args...)		DBG_PRINT( g_aad_debug_fd, 1, format, ##args)
#define	AAD_ISR_DEBUG(format, args...)	DBG_PRINT( g_aad_debug_fd, 2, format, ##args)
#define	AAD_ERROR(format, args...)		DBG_PRINT( g_aad_debug_fd, 3, format, ##args)
#define	AAD_DEBUG(format, args...)		DBG_PRINT( g_aad_debug_fd, 4, format, ##args)
#define	AAD_DEBUG_TMP(format, args...)	DBG_PRINT( g_aad_debug_fd, 5, format, ##args)

#define	AAD_TRACE_BEGIN()				AAD_TRACE("[AAD] BEGIN -- %s:%d\n", __FUNCTION__, __LINE__ )
#define	AAD_TRACE_END()					AAD_TRACE("[AAD] END   -- %s:%d\n", __FUNCTION__, __LINE__ )
#define	AAD_TRACE_MARK()				AAD_TRACE("[AAD] %s:%d\n -- TRACING...", __FUNCTION__, __LINE__ )
#endif /* #if 0 ... */

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void	 AAD_PreInit(void);
extern	int      AAD_Init(void);
extern	void     AAD_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_aad_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _AAD_DRV_H_ */

/** @} */
