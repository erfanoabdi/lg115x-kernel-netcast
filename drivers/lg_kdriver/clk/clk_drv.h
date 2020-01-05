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
 *  main configuration file for clock device
 *
 *  author		gaius.lee
 *  version		1.0 
 *  date		2010.03.07
 *  note		Additional information. 
 *
 *  @addtogroup lg1150_clock 
 *	@{
 */

#ifndef	_CLK_DRV_H_
#define	_CLK_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "clk_cfg.h"
#include "clk_kapi.h"

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

#define	CLK_PRINT(format, args...)		DBG_PRINT(  g_clk_debug_fd, 0, format, ##args)
/* Trace are used for tracking IOCTL calls */
#define	CLK_TRACE(format, args...)		DBG_PRINTX( g_clk_debug_fd, 1, format, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     CLK_PreInit(void);
extern	int      CLK_Init(void);
extern	void     CLK_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_clk_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _CLK_DRV_H_ */

/** @} */
