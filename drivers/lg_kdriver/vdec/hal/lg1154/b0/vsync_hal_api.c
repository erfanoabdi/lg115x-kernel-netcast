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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     youngki.lyu@lge.com
 * version    0.1
 * date       2010.03.11
 * note       Additional information.
 *
 * @addtogroup h13_vdec
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "../../../mcu/vdec_type_defs.h"
#include "../lg1154_vdec_base.h"
#include "../../../mcu/os_adap.h"
#include "vsync_reg.h"
#include "../vsync_hal_api.h"
#include "asm/div64.h"

#define LOG_NAME vdec_hal_vsync
#include "log.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define VDEC_SYNC_BASE					(H13_VDEC_BASE + 0x1700)

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static volatile Sync_REG_T			*stpSync_Reg = NULL;
static UINT32 u32PhaseShift[VDISP_NUM_OF_CHANNEL] = {0, };
static BOOLEAN bCurInterlaced[VDISP_NUM_OF_CHANNEL];


/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_Init(void)
{
	stpSync_Reg		= (volatile Sync_REG_T *)VDEC_TranselateVirualAddr(VDEC_SYNC_BASE, 0x20);
	VSync_HAL_Reset();
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VSync_HAL_GetVersion(void)
{
	return stpSync_Reg->version;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_Reset(void)
{
	VDISP_CONF		sync_conf;
	UINT32			i;

	for(i=0; i<VDISP_NUM_OF_CHANNEL; i++)
	{
		u32PhaseShift[i] = 0;
		bCurInterlaced[i] = TRUE;
	}

	sync_conf = stpSync_Reg->sync_conf;

	sync_conf.reg_int_vsync0_field_sel = 1;
	sync_conf.reg_int_vsync1_field_sel = 1;
	sync_conf.reg_int_vsync2_field_sel = 1;
	sync_conf.reg_int_vsync3_field_sel = 1;
	sync_conf.reg_vsync0_first_pul_en = 1;
	sync_conf.reg_vsync1_first_pul_en = 1;
	sync_conf.reg_vsync2_first_pul_en = 1;
	sync_conf.reg_vsync3_first_pul_en = 1;
	sync_conf.reg_vsync0_srst = 1;
	sync_conf.reg_vsync1_srst = 1;
	sync_conf.reg_vsync2_srst = 1;
	sync_conf.reg_vsync3_srst = 1;
	sync_conf.reg_vsync0_en = 1;
	sync_conf.reg_vsync1_en = 1;
	sync_conf.reg_vsync2_en = 1;
	sync_conf.reg_vsync3_en = 1;
	sync_conf.reg_ext_vsync0_field_sel = 1;
	sync_conf.reg_ext_vsync1_field_sel = 1;
	sync_conf.reg_ext_vsync2_field_sel = 1;
	sync_conf.reg_ext_vsync3_field_sel = 1;

	stpSync_Reg->sync_conf = sync_conf;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VSync_HAL_UTIL_GCD(UINT32 a, UINT32 b)
{
	if(a%b == 0)
	{
		return b;
	}

	return VSync_HAL_UTIL_GCD(b,a%b);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
/*
BOOLEAN VSync_HAL_SetVsyncFrameInterval(UINT8 ui8SyncCh, UINT32 ui32Interval, BOOLEAN bInterlaced)
{
	if( ui8SyncCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error ("[VSync%d][Err] Channel Number, %s", ui8SyncCh, __FUNCTION__ );
		return FALSE;
	}

	if( (ui32FrameRateRes == 0) || (ui32FrameRateDiv == 0) )
	{
		log_error ("[VSync%d][ERR] Frame Rate Residual(%d)/Divider(%d)", ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv );
		return FALSE;
	}

}
*/

void VSync_HAL_SetVsyncShift(UINT8 ui8SyncCh, UINT32 u32Delta)
{
	log_noti("ch %d phase shift %d\n", ui8SyncCh, u32Delta);
	u32PhaseShift[ui8SyncCh] = u32Delta;
}

BOOLEAN VSync_HAL_SetVsyncField(UINT8 ui8SyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv, BOOLEAN bInterlaced)
{
	UINT32	ui32FieldNum;

	VDISP_UPDATE		sync_update;
	UINT64  u64Temp;

	if( ui8SyncCh >= VDISP_NUM_OF_CHANNEL )
	{
		log_error ("[VSync%d][Err] Channel Number, %s", ui8SyncCh, __FUNCTION__ );
		return FALSE;
	}

	if( (ui32FrameRateRes == 0) || (ui32FrameRateDiv == 0) )
	{
		log_error ("[VSync%d][ERR] Frame Rate Residual(%d)/Divider(%d)", ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv );
		return FALSE;
	}

	u64Temp = (UINT64)27000000 * (UINT64)ui32FrameRateDiv;
	do_div(u64Temp, ui32FrameRateRes);
	ui32FieldNum = (UINT32)u64Temp;
	ui32FieldNum += u32PhaseShift[ui8SyncCh];
	ui32FieldNum >>= 1;

	if( bInterlaced != bCurInterlaced[ui8SyncCh])
	{
		if( bInterlaced )
		{
			(*(UINT32*)&stpSync_Reg->sync_conf)	|= (1<<ui8SyncCh);
			(*(UINT32*)&stpSync_Reg->sync_conf)	|= (1<<(12+ui8SyncCh));
		}
		else
		{
			(*(UINT32*)&stpSync_Reg->sync_conf)	&= ~(1<<ui8SyncCh);
			(*(UINT32*)&stpSync_Reg->sync_conf)	&= ~(1<<(12+ui8SyncCh));
		}
		log_noti("[VSync%d] ScanType %d->%d  %X\n", ui8SyncCh, bCurInterlaced[ui8SyncCh],
				bInterlaced, (*(UINT32*)&stpSync_Reg->sync_conf) );
		bCurInterlaced[ui8SyncCh] = bInterlaced;
	}

	log_debug ("[VSync%d][DBG] Vsync Rate Res(%d)/Div(%d) Intlc %d, FieldNum:%d Phase %d",
			ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv, bInterlaced, ui32FieldNum,
			u32PhaseShift[ui8SyncCh]);

	stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field0_num = ui32FieldNum;
	stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field1_num = ui32FieldNum;

	sync_update = stpSync_Reg->sync_update;
	switch( ui8SyncCh )
	{
		case 0:
			sync_update.reg_vsync0_update = 1;
			break;
		case 1:
			sync_update.reg_vsync1_update = 1;
			break;
		default:
			log_error ("[VSYNC%d][ERR] Frame Rate", ui8SyncCh );
			break;
	}
	stpSync_Reg->sync_update = sync_update;

	return TRUE;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_RestartAllVsync(void)
{
	UINT8		ui8SyncCh;
	UINT32		ui32FieldNum[4];

	log_debug ("[SYNC][DBG] %s", __FUNCTION__ );

	for( ui8SyncCh = 0; ui8SyncCh < VDISP_NUM_OF_CHANNEL; ui8SyncCh++ )
	{
		ui32FieldNum[0] = stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field0_num;
		ui32FieldNum[1] = stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field1_num;
		ui32FieldNum[2] = stpSync_Reg->vsync_field_num[ui8SyncCh+2].reg_field0_num;
		ui32FieldNum[3] = stpSync_Reg->vsync_field_num[ui8SyncCh+2].reg_field1_num;

		stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field0_num = 0x0006DF92;
		stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field1_num = 0x0006DF92;
		stpSync_Reg->vsync_field_num[ui8SyncCh+2].reg_field0_num = 0x0006DF92;
		stpSync_Reg->vsync_field_num[ui8SyncCh+2].reg_field1_num = 0x0006DF92;
	}
	VSync_HAL_Reset();
	for( ui8SyncCh = 0; ui8SyncCh < VDISP_NUM_OF_CHANNEL; ui8SyncCh++ )
	{
		stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field0_num = ui32FieldNum[0];
		stpSync_Reg->vsync_field_num[ui8SyncCh].reg_field1_num = ui32FieldNum[1];
		stpSync_Reg->vsync_field_num[ui8SyncCh+2].reg_field0_num = ui32FieldNum[2];
		stpSync_Reg->vsync_field_num[ui8SyncCh+2].reg_field1_num = ui32FieldNum[3];

		switch( ui8SyncCh )
		{
		case 0:
			stpSync_Reg->sync_update.reg_vsync0_update = 1;
			stpSync_Reg->sync_update.reg_vsync2_update = 1;
			break;

		case 1:
			stpSync_Reg->sync_update.reg_vsync1_update = 1;
			stpSync_Reg->sync_update.reg_vsync3_update = 1;
			break;
		}

	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32  VSync_HAL_IntField(UINT8 ui8SyncCh)
{
	return stpSync_Reg->vsync_int_field[ui8SyncCh].reg_int_vsync_field & 0x1;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32  VSync_HAL_ExtField(UINT8 ui8SyncCh)
{
	return stpSync_Reg->vsync_ext_field[ui8SyncCh].reg_ext_vsync_field & 0x1;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_SetUpdateMode(UINT8 ui8TimerCh, UINT8 ui8Mode)
{
	switch( ui8TimerCh )
	{
	case 0:
		stpSync_Reg->timer_conf.reg_timer0_update_mode = ui8Mode; break;
	case 1:
		stpSync_Reg->timer_conf.reg_timer1_update_mode = ui8Mode; break;
	case 2:
		stpSync_Reg->timer_conf.reg_timer2_update_mode = ui8Mode; break;
	case 3:
		stpSync_Reg->timer_conf.reg_timer3_update_mode = ui8Mode; break;
	default:
		break;
	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_ResetTimer(UINT8 ui8TimerCh)
{
	switch( ui8TimerCh )
	{
	case 0:
		stpSync_Reg->timer_conf.reg_timer0_srst = 1; break;
	case 1:
		stpSync_Reg->timer_conf.reg_timer1_srst = 1; break;
	case 2:
		stpSync_Reg->timer_conf.reg_timer2_srst = 1; break;
	case 3:
		stpSync_Reg->timer_conf.reg_timer3_srst = 1; break;
	default:
		break;
	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_EnableTimer(UINT8 ui8TimerCh)
{
	switch( ui8TimerCh )
	{
	case 0:
		stpSync_Reg->timer_conf.reg_timer0_en = 1; break;
	case 1:
		stpSync_Reg->timer_conf.reg_timer1_en = 1; break;
	case 2:
		stpSync_Reg->timer_conf.reg_timer2_en = 1; break;
	case 3:
		stpSync_Reg->timer_conf.reg_timer3_en = 1; break;
	default:
		break;
	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_DisableTimer(UINT8 ui8TimerCh)
{
	switch( ui8TimerCh )
	{
	case 0:
		stpSync_Reg->timer_conf.reg_timer0_en = 0; break;
	case 1:
		stpSync_Reg->timer_conf.reg_timer1_en = 0; break;
	case 2:
		stpSync_Reg->timer_conf.reg_timer2_en = 0; break;
	case 3:
		stpSync_Reg->timer_conf.reg_timer3_en = 0; break;
	default:
		break;
	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VSync_HAL_SetTimer(UINT8 ui8TimerCh, UINT32 ui32Value)
{
	switch( ui8TimerCh )
	{
	case 0:
		stpSync_Reg->timer0_num.reg_timer0_num = ui32Value; break;
	case 1:
		stpSync_Reg->timer1_num.reg_timer1_num = ui32Value; break;
	case 2:
		stpSync_Reg->timer2_num.reg_timer2_num = ui32Value; break;
	case 3:
		stpSync_Reg->timer3_num.reg_timer3_num = ui32Value; break;
	default:
		break;
	}
}

/** @} */

