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
 *  driver interface header for mjpeg device. ( used only within kdriver )
 *	MJPEG device will teach you how to make device driver with new platform.
 *
 *  @author		youngwoo.jin (youngwoo.jin@lge.com)
 *  @version	1.0
 *  @date		2011.04.09
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

#ifndef	_MJPEG_DRV_H_
#define	_MJPEG_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "mjpeg_cfg.h"
#include "mjpeg_kapi.h"
#include "mjpeg_reg_l9.h"

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
#define	MJPEG_PRINT(format, args...)		DBG_PRINT(  g_MJPEG_debug_fd, 0, format, ##args)
#define	MJPEG_TRACE(format, args...)		DBG_PRINTX( g_MJPEG_debug_fd, 0, format, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern 	void 	 MJPEG_PreInit(void);
extern	int      MJPEG_Init(void);
extern	void     MJPEG_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int						g_MJPEG_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _MJPEG_DRV_H_ */

/** @} */
