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
 *  driver interface header for dimm device. ( used only within kdriver )
 *	dimm device will teach you how to make device driver with new platform.
 *
 *  @author		sh.myoung (sh.myoung@lge.com)
 *  @version	1.0 
 *  @date		2010.01.06
 *
 *  @addtogroup lg1150_dimm
 *	@{
 */

#ifndef	_DIMM_DRV_H_
#define	_DIMM_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "dimm_cfg.h"
#include "dimm_kapi.h"

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
#if	1	//temp
#define	DIMM_PRINT(format, args...)		DBG_PRINT(  g_dimm_debug_fd, 0, format, ##args)
#define	DIMM_TRACE(format, args...)		DBG_PRINTX( g_dimm_debug_fd, 1, format, ##args)
#define	DIMM_ERROR(format, args...)		DBG_PRINT( g_dimm_debug_fd, 2, format, ##args)
#define	DIMM_DEBUG(format, args...)		DBG_PRINT( g_dimm_debug_fd, 3, format, ##args)
#else
#define	DIMM_PRINT(format, args...)		DBG_PRINT(  g_dimm_debug_fd, 0, format, ##args)
#define	DIMM_TRACE(format, args...)		DBG_PRINTX( g_dimm_debug_fd, 0, format, ##args)
#endif
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     DIMM_PreInit(void);
extern	int      DIMM_Init(void);
extern	void     DIMM_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_dimm_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DIMM_DRV_H_ */

/** @} */

