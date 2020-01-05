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
 *  PWM HAL file for BE device
 *	
 *  author		dj911.kim
 *  version		1.0
 *  date		2012.06.30
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/delay.h>


#include "os_util.h"
#include "be_dbg.h"

#include "be_kapi.h"
#include "pwm_hal.h"
#include "h13/pwm_reg_h13.h"

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

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int PWM_HAL_Init(void)
{
	int ret = RET_OK;

	ret = PWM_REG_H13_Init();

	return ret;
}

int PWM_HAL_SetPwmControl(BE_PWM_CTRL_T *pstParams)
{
	int ret = RET_OK;

	ret = PWM_REG_H13_SetPwmControl(pstParams);

	return ret;
}

int PWM_HAL_SetPwmAdaptFreqControl(BE_PWM_ADAPT_FREQ_CTRL_T *pstParams)
{
	int ret = RET_OK;

	ret = PWM_REG_H13_SetPwmAdaptFreqControl(pstParams);

	return ret;
}

int PWM_HAL_SetPwmFrequency(BE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;

	ret = PWM_REG_H13_SetPwmFrequency(pstParams);

	return ret;
}

int PWM_HAL_SetPwmDutyCycle(BE_PWM_DUTY_T *pstParams)
{
	int ret = RET_OK;

	ret = PWM_REG_H13_SetPwmDutyCycle(pstParams);

	return ret;
}

int PWM_HAL_GetPwmInfoExternal(BE_EXTERNAL_PWM_T *pstParams)
{
	int ret = RET_OK;

	ret = PWM_REG_H13_GetPwmInfo(pstParams);

	return ret;
}

int PWM_HAL_SetPwmSync(UINT32 u32Frequency)
{
	int ret = RET_OK;

	ret = PWM_REG_H13_SetPwmSync(u32Frequency);

	return ret;
}

