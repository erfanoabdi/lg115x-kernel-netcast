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

#include <stdio.h>
#include <xtensa/xtruntime.h>
#include "../vdec_type_defs.h"
#include "../lg1152_hal/mcu_reg.h"
//#include "../msvc_isr.h"
#include "../vdec_isr.h"
#include "../os_adap.h"
#include "../vdec_print.h"

_xtos_handler ExtInt0InterruptHandler(void);
_xtos_handler ExtInt1InterruptHandler(void);

BOOLEAN		bRunningExtInt0 = FALSE;
BOOLEAN		bRunningExtInt1 = FALSE;

void ExtInt_Init(void)
{
	// set interrupt handler
	_xtos_set_interrupt_handler(EXTINT0, (_xtos_handler) ExtInt0InterruptHandler);	// MCU Internal
	_xtos_set_interrupt_handler(EXTINT1, (_xtos_handler) ExtInt1InterruptHandler);	// VDEC

	// interrupt enable
	OS_INTS_ON(EXTINT0_MASK);
	OS_INTS_ON(EXTINT1_MASK);

	return;
}

_xtos_handler ExtInt0InterruptHandler(void)
{
	OS_INTS_OFF(EXTINT0_MASK);

	bRunningExtInt0 = TRUE;
	if( bRunningExtInt1 == TRUE )
		VDEC_KDRV_Message( ERROR, "[Preemption] Running ExtInt1" );

	MCU_ISR_Handler();
	bRunningExtInt0 = FALSE;

	OS_INTS_ON(EXTINT0_MASK);
	return 0;
}

_xtos_handler ExtInt1InterruptHandler(void)
{
	OS_INTS_OFF(EXTINT1_MASK);

	bRunningExtInt1 = TRUE;
//	if( bRunningExtInt0 == TRUE )
//		VDEC_KDRV_Message( ERROR, "[Preemption] Running ExtInt0" );

	VDEC_ISR_Handler();
	bRunningExtInt1 = FALSE;

	IPC_CMD_Receive();

	OS_INTS_ON(EXTINT1_MASK);
	return 0;
}

