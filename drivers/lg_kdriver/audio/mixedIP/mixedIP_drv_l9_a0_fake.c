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
 *  driver interface header for Mixed IP device. ( used only within kdriver )
 *	Mixed IP device will teach you how to make device driver with new platform.
 *
 *  @author		Jong-Sang Oh(jongsang.oh@lge.com)
 *  @version	1.0
 *  @date		2011.04.09
 *  note		Additional information.
 *
 *  @addtogroup lg1152_adec
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include "os_util.h" //for alloc functions

#include "audio_cfg.h"
#include "audio_kapi.h"
#include "audio_drv.h"

#include "mixedIP_drv_l9_a0.h"


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
/**
 *  ANALOG_ReadRegister
 *
 *  @parm UINT32 *
 *  @return int
 	data:8,
	rsvd8:8,
	slaveAddr:8,
	regAddr:8;
*/
int L9A0_ANALOG_ReadRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 *value)
{
	return 0;
}

/**
 *  L9A0_ANALOG_WriteRegister
 *
 *  @parm UINT32 *
 *  @return int
 	data:8,
	rsvd8:8,
	slaveAddr:8,
	regAddr:8;
*/
int L9A0_ANALOG_WriteRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 value)
{
	return 0;
}

/**
 * Initializes the clock and reset module register value.
 * @see ADEC_Init
*/
int L9A0_MIXED_IP_ADEC_L9_InitClockRegisters( void )
{
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_SetClockSource( LX_AUD_CLOCK_SRC_T ui8AdecClockSrc )
{
	return RET_OK;
}

/**
 * Sets a PCM Clock frequency and Rate to sync with SPDIF clock for SPDIF output.
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_SetPcmClockRate ( LX_AUD_SAMPLING_FREQ_T ui32SrcFreq, UINT32 ui32PcmClock )
{
	return RET_OK;
}

int L9A0_MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq ( LX_AUD_SAMPLING_FREQ_T ui32SamplingFreq, LX_AUD_SPDIF_DTO_RATE_T stSpdifDtoRate )
{
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_InitCodecRegisters ( void )
{
	return RET_OK;
}

/**
 * Control the Mixed IP AAD, ADC, MIC ADC, DAC and HPDRV module to power on and mute off.
 * @see ADEC_L9_SetSource
*/
int L9A0_MIXED_IP_ADEC_L9_PowerControl ( LX_AUD_POWER_BLOCK_T block, LX_AUD_POWER_MODE_T mode )
{
	return RET_OK;
}

/**
 * Start the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_StartCodec ( void )
{
	return RET_OK;
}

/**
 * Stop the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_StopCodec ( void )
{
	return RET_OK;
}

/**
 * Sets a ADC port number for ADEC I2S input.
 * @see ADEC_L9_SetSource
*/
int L9A0_MIXED_IP_ADEC_L9_SetADCPortNumber ( UINT8 ui8PortNum )
{
	return RET_OK;
}

/**
 * Sets the volume of DAC output.
 * @see ADEC_L9_SetDACOutVolume
*/
int L9A0_MIXED_IP_ADEC_L9_SetDACOutVolume ( LX_AUD_DAC_VOL_T stDACOutVol )
{
	return RET_OK;
}

/**
 * Sets the mute of DAC output.
 * @see ADEC_L9_SetOutputPortMute
*/
int L9A0_MIXED_IP_ADEC_L9_SetDACOutMute ( LX_AUD_OUTPUT_PORT_MUTE_T stOutPortMute )
{
	return RET_OK;
}

/** @} */




