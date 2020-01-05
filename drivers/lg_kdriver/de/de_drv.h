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
 *  driver interface header for de device. ( used only within kdriver )
 *	de device will teach you how to make device driver with new platform.
 *
 *  @author		dongho7.park (dongho7.park@lge.com)
 *  @version	1.0 
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_de
 *	@{
 */

#ifndef	_DE_DRV_H_
#define	_DE_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "de_cfg.h"
#include "de_kapi.h"

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
#define	DE_PRINT(format, args...)		DBG_PRINT(  g_de_debug_fd, 0, format, ##args)
#define	DE_TRACE(format, args...)		DBG_PRINTX( g_de_debug_fd, 0, format, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     DE_PreInit(void);
extern	int      DE_Init(void);
extern	void     DE_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_de_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_DRV_H_ */

/** @} */
