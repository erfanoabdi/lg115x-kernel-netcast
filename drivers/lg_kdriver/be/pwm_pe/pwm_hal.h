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
 *  PWM HAL header file for BE device
 *	
 *  author		dj911.kim
 *  version		1.0
 *  date		2012.06.30
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _PWM_HAL_H_
#define _PWM_HAL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int PWM_HAL_Init(void);
int PWM_HAL_SetPwmControl(BE_PWM_CTRL_T *pstParams);
int PWM_HAL_SetPwmAdaptFreqControl(BE_PWM_ADAPT_FREQ_CTRL_T *pstParams);
int PWM_HAL_SetPwmFrequency(BE_PWM_FREQ_T *pstParams);
int PWM_HAL_SetPwmDutyCycle(BE_PWM_DUTY_T *pstParams);
int PWM_HAL_GetPwmInfoExternal(BE_EXTERNAL_PWM_T *pstParams);

int PWM_HAL_SetPwmSync(UINT32 u32Frequency);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _PWM_HAL_H_ */

/** @} */


