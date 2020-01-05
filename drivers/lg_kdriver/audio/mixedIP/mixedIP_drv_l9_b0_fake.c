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

#include "mixedIP_drv_l9_b0.h"

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
 *  L9B0_MIXED_IP_I2C_Read
 *
 *  @parm UINT32 *
 *  @return int
*/
int L9B0_MIXED_IP_I2C_Read(UINT32* reg)
{
	return RET_OK;
}

/**
 *  L9B0_MIXED_IP_I2C_Write
 *
 *  @parm UINT32 *
 *  @return int
*/
int L9B0_MIXED_IP_I2C_Write(UINT32* reg)
{
	return RET_OK;
}

/**
 *  ANALOG_ReadRegister
 *
 *  @parm UINT32 *
 *  @return int
*/
int L9B0_ANALOG_ReadRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 *value)
{
	return RET_OK;
}

/**
 *  L9B0_ANALOG_WriteRegister
 *
 *  @parm UINT32 *
 *  @return int
*/
int L9B0_ANALOG_WriteRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 value)
{
	return RET_OK;
}

/**
 * Initializes the clock and reset module register value.
 * @see ADEC_Init
*/
int L9B0_MIXED_IP_ADEC_L9_InitClockRegisters( void )
{
	return RET_OK;
}

/**
 * Resets the clock register value.
 * @see ADEC_Init
*/
int L9B0_MIXED_IP_ADEC_L9_ResetClockRegisters( void )
{
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_SetClockSource( LX_AUD_SAMPLING_FREQ_T ui32SrcFreq, LX_AUD_CLOCK_SRC_T ui8AdecClockSrc )
{
	return RET_OK;
}

/**
 * Sets a PCM Clock frequency and Rate to sync with SPDIF clock for SPDIF output.
 * @see ADEC_L9_InitModule
 *  APLL_MODE_EN = 0, APLL_EN_EDGE = 0 인 경우
 *  Fout = APLL_N * Fin /( APLL_M * APLL_OD )   입니다.

 *  그러니까 Fin=27Mhz
 *  APLL_M[8:0]=0,1110,0001=225, APLL_N[12:0]=1,0000,0000,0000=4096,  APLL_OD[5:0]=10,1000=40
 *  Fout = 4096* 27M /(225 * 40) = 12.288MHz  이고

 *  APLL_N[12:0]=1,0000,0000,0011=4099 인 경우는 12.297MHz
 *  APLL_N[12:0]=1111,1111,1111=4095 인 경우는 12.285MHz
*/
int L9B0_MIXED_IP_ADEC_L9_SetPcmClockRate ( LX_AUD_SAMPLING_FREQ_T ui32SrcFreq, UINT32 ui32PcmClock )
{
	return RET_OK;
}

/**
 * Sets a SPDIF Clock frequency and Rate to sync with PCM clock for D-AMP output.
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq ( LX_AUD_SAMPLING_FREQ_T ui32SamplingFreq, LX_AUD_SPDIF_DTO_RATE_T stSpdifDtoRate )
{
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_InitCodecRegisters ( void )
{
	return RET_OK;
}

/**
 * Control the Mixed IP AAD, ADC, MIC ADC, DAC and HPDRV module to power on and mute off.
 * @see ADEC_L9_SetSource
*/
int L9B0_MIXED_IP_ADEC_L9_PowerControl ( LX_AUD_POWER_BLOCK_T block, LX_AUD_POWER_MODE_T mode )
{
	return RET_OK;
}

/**
 * Start the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_StartCodec ( void )
{
	return RET_OK;
}

/**
 * Stop the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_StopCodec ( void )
{
	return RET_OK;
}

/**
 * Sets a ADC port number for ADEC I2S input.
 * @see ADEC_L9_SetSource
*/
int L9B0_MIXED_IP_ADEC_L9_SetADCPortNumber ( UINT8 ui8PortNum )
{
	return RET_OK;
}

/**
 * Sets the volume of DAC output.
 * @see ADEC_L9_SetDACOutVolume
*/
int L9B0_MIXED_IP_ADEC_L9_SetDACOutVolume ( LX_AUD_DAC_VOL_T stDACOutVol )
{
	return RET_OK;
}

/**
 * Sets the mute of DAC output.
 * @see ADEC_L9_SetOutputPortMute
*/
int L9B0_MIXED_IP_ADEC_L9_SetDACOutMute ( LX_AUD_OUTPUT_PORT_MUTE_T stOutPortMute )
{
	return RET_OK;
}


/** @} */




