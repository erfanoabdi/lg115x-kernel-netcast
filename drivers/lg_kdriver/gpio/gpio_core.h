
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
 *
 *  @author		ks.hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2012.05.03
 *
 *  @addtogroup lg115x_gpio
 *	@{
 */

#ifndef	__GPIO_CORE_H__
#define	__GPIO_CORE_H__

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct GPIO_DEV *LX_GPIO_HANDLE;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	int	GPIO_DevInit(void);

extern	int GPIO_DevSetPinMux(UINT32 port, BOOLEAN enable);
extern	int GPIO_DevGetPinMux(UINT32 port, BOOLEAN *enable);
extern	int GPIO_DevSetMode(UINT32 port, LX_GPIO_MODE_T mode);
extern	int GPIO_DevGetMode(UINT32 port, LX_GPIO_MODE_T *mode);
extern	int GPIO_DevSetValue(UINT32 port, LX_GPIO_VALUE_T value);
extern	int GPIO_DevGetValue(UINT32 port, LX_GPIO_VALUE_T *value);

extern	int GPIO_DevExSetPinMux(UINT32 port, BOOLEAN enable);
extern	int GPIO_DevExGetPinMux(UINT32 port, BOOLEAN *enable);
extern	int GPIO_DevExSetMode(UINT32 port, LX_GPIO_MODE_T mode);
extern	int GPIO_DevExGetMode(UINT32 port, LX_GPIO_MODE_T *mode);
extern	int GPIO_DevExSetValue(UINT32 port, LX_GPIO_VALUE_T value);
extern	int GPIO_DevExGetValue(UINT32 port, LX_GPIO_VALUE_T *value);


#ifdef KDRV_CONFIG_PM
extern	int GPIO_DevResume(void);
extern	int GPIO_DevSuspend(void);
#endif
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* __GPIO_CORE_H__ */

/** @} */
