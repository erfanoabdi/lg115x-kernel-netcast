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

#include <xtensa/config/core.h>
#include <xtensa/config/system.h>
#include <xtensa/xtruntime.h>
#include "mcu_timer.h"
#include "../vdec_type_defs.h"
#include "../vdec_print.h"

#define VDEC_TIMER_INTNUM		XCHAL_TIMER0_INTERRUPT
#define VDEC_TIMER_INTMASK		(1<<XCHAL_TIMER0_INTERRUPT)

#define TICK_PER_MSEC	(198U*1000U)
#define TICK_PER_SEC	(198U*1000U*1000U)

static struct
{
	UINT32	ui32_jiffies;
	UINT32	ui32_msec;

	UINT32	ui32Expires_ms;
	VDEC_MCU_TIMER_CALLBACK_T		fpTimerFunc;
}  gsVdeMcuTimer;


_xtos_handler _VDEC_MCU_TimerHandler(void)
{
	_xtos_clear_ints( VDEC_TIMER_INTMASK );
	_xtos_timer_0_delta( gsVdeMcuTimer.ui32Expires_ms * TICK_PER_MSEC );

	gsVdeMcuTimer.ui32_jiffies++;
	gsVdeMcuTimer.ui32_msec += gsVdeMcuTimer.ui32Expires_ms;

	if( gsVdeMcuTimer.fpTimerFunc == NULL )
	{
		VDEC_KDRV_Message( ERROR, "[Timer] Not Registered Timer Callback Function" );
	}
	else
	{
		gsVdeMcuTimer.fpTimerFunc();
	}
}

void VDEC_MCU_SetTimer(UINT32 ui32Expires_ms, VDEC_MCU_TIMER_CALLBACK_T fpTimerFunc)
{
	gsVdeMcuTimer.ui32_jiffies = 0;
	gsVdeMcuTimer.ui32Expires_ms = ui32Expires_ms;
	gsVdeMcuTimer.fpTimerFunc = fpTimerFunc;

	_xtos_set_interrupt_handler( VDEC_TIMER_INTNUM, (_xtos_handler)_VDEC_MCU_TimerHandler );
	_xtos_timer_0_delta( ui32Expires_ms * TICK_PER_MSEC );

	xthal_set_intclear(VDEC_TIMER_INTMASK);
	_xtos_ints_on( VDEC_TIMER_INTMASK );
}

void VDEC_MCU_KillTimer(void)
{
	_xtos_ints_off(VDEC_TIMER_INTMASK);

	gsVdeMcuTimer.ui32Expires_ms = 0;
	gsVdeMcuTimer.fpTimerFunc = NULL;
}


