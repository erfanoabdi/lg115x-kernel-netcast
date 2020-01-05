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
 *  driver interface header for fmt3d device. ( used only within kdriver )
 *	fmt3d device will teach you how to make device driver with new platform.
 *
 *  @author		dongho7.park (dongho7.park@lge.com)
 *  @version	1.0 
 *  @date		2010.01.06
 *
 *  @addtogroup lg1150_fmt3d
 *	@{
 */

#ifndef	_FMT3D_DRV_H_
#define	_FMT3D_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "fmt3d_cfg.h"
#include "fmt3d_kapi.h"

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
#define	FMT3D_PRINT(format, args...)		DBG_PRINT(  g_fmt3d_debug_fd, 0, format, ##args)
#define	FMT3D_TRACE(format, args...)		DBG_PRINTX( g_fmt3d_debug_fd, 0, format, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     FMT3D_PreInit(void);
extern	int      FMT3D_Init(void);
extern	void     FMT3D_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_fmt3d_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _FMT3D_DRV_H_ */

/** @} */
