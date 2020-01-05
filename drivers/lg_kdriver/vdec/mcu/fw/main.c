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
#include "..\vdec_type_defs.h"
#include "..\mcu_config.h"

#include "..\lg1152_hal\mcu_hal_api.h"
#include "..\lg1152_hal\top_hal_api.h"

#include "..\ipc_req.h"
#include "..\ram_log.h"

#if (defined(USE_MCU_FOR_VDEC_PDEC) || defined(USE_MCU_FOR_VDEC_DECODER))
#include "..\pdec_auib.h"
#include "..\pdec_cpb.h"
#endif

#if defined(USE_MCU_FOR_VDEC_DECODER) || defined(USE_MCU_FOR_VDEC_SYNC)
#include "..\disp_q.h"
#include "..\disp_clear_q.h"
#endif

#if defined(USE_MCU_FOR_VDEC_SYNC)
#include "..\lg1152_hal\av_lipsync_hal_api.h"
#include "..\lg1152_hal\de_ipc_hal_api.h"
#include "..\lg1152_hal\vsync_hal_api.h"
#include "..\vdisp_drv.h"
#endif

#include "mcu_timer.h"

#include "..\vdec_print.h"


#define	VDEC_MCU_WATCHDOG_UPDATE_DURATION	60U	// msec


extern void ExtInt_Init(void);

void VDEC_MCU_UpdateWatchdogCnt( void )
{
	IPC_REG_Set_WatchdogCnt(IPC_REG_Get_WatchdogCnt() + VDEC_MCU_WATCHDOG_UPDATE_DURATION);
}

int main()
{
	MCU_HAL_Init();
	TOP_HAL_Init();
	LQ_HAL_Init();

	IPC_REG_Init();

	IPC_DBG_Init();
	IPC_CMD_Init();
	IPC_REQ_Init();
	IPC_CALLBACK_Init();
	RAM_LOG_Init();

	PDEC_HAL_Init();
#if defined(USE_MCU_FOR_VDEC_PDEC)
	PDEC_Init();
#endif

#if (defined(USE_MCU_FOR_VDEC_PDEC) || defined(USE_MCU_FOR_VDEC_DECODER))
	PDEC_AUIB_Init();
	PDEC_CPB_Init();
#endif

#if defined(USE_MCU_FOR_VDEC_DECODER) || defined(USE_MCU_FOR_VDEC_DECODER)
	VDC_Init();
	VDEC_DPB_Init();
#endif

#if (defined(USE_MCU_FOR_VDEC_DECODER) || defined(USE_MCU_FOR_VDEC_SYNC))
	DISP_Q_Init(); DISP_CLEAR_Q_Init();
#endif

	VSync_HAL_Init();
	DE_IPC_HAL_Init();
	AV_LipSync_HAL_Init();
#if defined(USE_MCU_FOR_VDEC_SYNC)
	VDISP_Init();
#endif

	ExtInt_Init();

	IPC_REG_Set_WatchdogCnt(0);
	VDEC_MCU_SetTimer(VDEC_MCU_WATCHDOG_UPDATE_DURATION, VDEC_MCU_UpdateWatchdogCnt);

	IPC_REQ_Send(IPC_REQ_ID_MCU_READY, 0, NULL);

	VDEC_KDRV_Message(ERROR, "[DBG] main() - MCU initialisation complete");

	while (1) {
	}

	return 0;
}

