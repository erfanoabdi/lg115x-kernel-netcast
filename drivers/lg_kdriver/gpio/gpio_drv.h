
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
 *  driver interface header for gpio device. ( used only within kdriver )
 *	gpio device will teach you how to make device driver with new platform.
 *
 *  @author		ingyu.yang (ingyu.yang@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_gpio
 *	@{
 */

#ifndef	_GPIO_DRV_H_
#define	_GPIO_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "gpio_cfg.h"
#include "gpio_kapi.h"

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
#define	GPIO_PRINT(format, args...)		DBG_PRINT(  g_gpio_debug_fd, 0, format, ##args)
#define	GPIO_TRACE(format, args...)		DBG_PRINTX( g_gpio_debug_fd, 1, format, ##args)
#define	GPIO_DEBUG(format, args...)		DBG_PRINT( g_gpio_debug_fd, 2, format, ##args)
#define	GPIO_ERROR(format, args...)		DBG_PRINT( g_gpio_debug_fd, 3, format, ##args)


#define GPIO_CHECK_CODE(__checker,__if_action,fmt,args...)   \
			 __CHECK_IF_ERROR(__checker, GPIO_ERROR, __if_action , fmt, ##args )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     GPIO_PreInit(void);
extern	int      GPIO_Init(void);
extern	void     GPIO_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_gpio_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _GPIO_DRV_H_ */

/** @} */
