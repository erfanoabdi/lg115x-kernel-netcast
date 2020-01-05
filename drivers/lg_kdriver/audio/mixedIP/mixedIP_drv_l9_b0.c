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

#include "debug_util.h"
#include "mixedIP_drv_l9_b0.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* SPDIF Sampling Clock frequency Number : 48, 44.1, 32Khz */
#define SPDIF_ES_OUT_FREQ_NUMBER	3
#define SPDIF_DTO_REG_NUMBER		9

/* SPDIF DTO Clock frequency and Rate Table */
const UINT32 g_ADEC_SpdifDtoTable[SPDIF_ES_OUT_FREQ_NUMBER][LX_AUD_SPDIF_DTO_RATE_NUMBER][SPDIF_DTO_REG_NUMBER] =
{
	{
		/*	Sample Frequency : 48Khz */
		/*	LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES */
		{
			0x02,	0x78,	0xCF,	0x13,	0x69,	0x01,	0x16,	0x00,	0x04,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_12_5SAMPLES */
		{
			0x00,	0xC5,	0xC0,	0x13,	0x69,	0xBB,	0x80,	0x00,	0x02,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_10_9SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x13,	0x69,	0xE4,	0xED,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_9_4SAMPLES */
		{
			0x01,	0x07,	0xAB,	0x13,	0x6A,	0x0E,	0x59,	0x00,	0x0B,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_7_8SAMPLES */
		{
			0x01,	0x3C,	0x67,	0x13,	0x6A,	0x37,	0xC6,	0x00,	0x09,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_6_3SAMPLES */
		{
			0x01,	0x8B,	0x81,	0x13,	0x6A,	0x61,	0x33,	0x00,	0x08,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_4_7SAMPLES */
		{
			0x00,	0xAF,	0xC7,	0x13,	0x6A,	0x8A,	0xA0,	0x00,	0x06,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_3_3SAMPLES */
		{
			0x03,	0x17,	0x03,	0x13,	0x6A,	0xB4,	0x0D,	0x00,	0x04,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_1_6SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x13,	0x6A,	0xDD,	0x7A,	0x00,	0x02,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_0_7SAMPLES */
		{
			0x0F,	0x73,	0x13,	0x13,	0x6A,	0xF6,	0x55,	0x00,	0x01,
		},
		/*	LX_AUD_SPDIF_DTO_NORMAL */
		{
			0x00,	0x0D,	0x2E,	0x13,	0x6B,	0x06,	0xE7,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_0_7SAMPLES */
		{
			0x0F,	0x73,	0x13,	0x13,	0x6B,	0x17,	0x78,	0x00,	0x0D,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_1_6SAMPLES */
		{
			0x02,	0x25,	0x50,	0x13,	0x6B,	0x2E,	0xAB,	0x00,	0x09,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_3_3SAMPLES */
		{
			0x03,	0x17,	0x03,	0x13,	0x6B,	0x59,	0xC0,	0x00,	0x0A,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_4_7SAMPLES */
		{
			0x02,	0x0F,	0x57,	0x13,	0x6B,	0x83,	0x2D,	0x00,	0x08,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_6_3SAMPLES */
		{
			0x01,	0x8B,	0x81,	0x13,	0x6B,	0xAC,	0x9A,	0x00,	0x06,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_7_8SAMPLES */
		{
			0x00,	0x3F,	0x47,	0x13,	0x6B,	0xD6,	0x07,	0x00,	0x04,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_9_4SAMPLES */
		{
			0x00,	0x1D,	0x4B,	0x13,	0x6B,	0xFF,	0x74,	0x00,	0x02,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_10_9SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x13,	0x6C,	0x28,	0xE1,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_12_5SAMPLES */
		{
			0x00,	0xC5,	0xC0,	0x13,	0x6C,	0x52,	0x4D,	0x00,	0x0B,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_19_5SAMPLES */
		{
			0x02,	0x78,	0xCF,	0x13,	0x6D,	0x0C,	0xB7,	0x00,	0x0A,
		},
	},
	{
		/*	Sample Frequency : 44.1Khz */
		/*	LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES */
		{
			0x0C,	0x5C,	0x0F,	0x11,	0xD5,	0x1B,	0xB9,	0x00,	0x0D,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_12_5SAMPLES */
		{
			0x0C,	0x5C,	0x0F,	0x11,	0xD5,	0xC1,	0x6D,	0x00,	0x05,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_10_9SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x11,	0xD5,	0xFF,	0x90,	0x00,	0x09,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_9_4SAMPLES */
		{
			0x01,	0x07,	0xAB,	0x11,	0xD6,	0x28,	0xFD,	0x00,	0x07,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_7_8SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x11,	0xD6,	0x52,	0x6A,	0x00,	0x05,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_6_3SAMPLES */
		{
			0x00,	0x4F,	0x19,	0x11,	0xD6,	0x7B,	0xD7,	0x00,	0x03,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_4_7SAMPLES */
		{
			0x02,	0x0F,	0x57,	0x11,	0xD6,	0xA5,	0x44,	0x00,	0x01,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_3_3SAMPLES */
		{
			0x03,	0x17,	0x03,	0x11,	0xD6,	0xCE,	0xB0,	0x00,	0x0D,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_1_6SAMPLES */
		{
			0x02,	0x49,	0xEF,	0x11,	0xD6,	0xFC,	0x42,	0x00,	0x04,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_0_7SAMPLES */
		{
			0x0F,	0x73,	0x13,	0x11,	0xD7,	0x10,	0xF8,	0x00,	0x0A,
		},
		/*	LX_AUD_SPDIF_DTO_NORMAL */
		{
			0x00,	0x15,	0xF8,	0x11,	0xD7,	0x21,	0x8A,	0x00,	0x09,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_0_7SAMPLES */
		{
			0x0F,	0x73,	0x13,	0x11,	0xD7,	0x32,	0x1C,	0x00,	0x08,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_1_6SAMPLES */
		{
			0x06,	0xDD,	0xCF,	0x11,	0xD7,	0x46,	0xD3,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_3_3SAMPLES */
		{
			0x03,	0x17,	0x03,	0x11,	0xD7,	0x74,	0x64,	0x00,	0x05,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_4_7SAMPLES */
		{
			0x02,	0x0F,	0x57,	0x11,	0xD7,	0x9D,	0xD1,	0x00,	0x03,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_6_3SAMPLES */
		{
			0x01,	0x8B,	0x81,	0x11,	0xD7,	0xC7,	0x3E,	0x00,	0x01,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_7_8SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x11,	0xD7,	0xF0,	0xAA,	0x00,	0x0D,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_9_4SAMPLES */
		{
			0x00,	0x34,	0xBB,	0x11,	0xD8,	0x1A,	0x17,	0x00,	0x0B,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_10_9SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x11,	0xD8,	0x43,	0x84,	0x00,	0x09,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_12_5SAMPLES */
		{
			0x00,	0xC5,	0xC0,	0x11,	0xD8,	0x6C,	0xF1,	0x00,	0x07,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_19_5SAMPLES */
		{
			0x0C,	0x5C,	0x0F,	0x11,	0xD9,	0x27,	0x5B,	0x00,	0x05,
		},
	},
	{
		/*	Sample Frequency : 32Khz */
		/*	LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES */
		{
			0x01,	0x8B,	0x81,	0x0C,	0xF0,	0x13,	0x7F,	0x00,	0x0E,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_12_5SAMPLES */
		{
			0x00,	0x41,	0xEA,	0x0C,	0xF0,	0xB9,	0x33,	0x00,	0x03,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_10_9SAMPLES */
		{
			0x06,	0x2E,	0x07,	0x0C,	0xF0,	0xE2,	0xA0,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_9_4SAMPLES */
		{
			0x03,	0x17,	0x03,	0x0C,	0xF1,	0x0C,	0x0C,	0x00,	0x11,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_7_8SAMPLES */
		{
			0x0C,	0x5C,	0x0F,	0x0C,	0xF1,	0x20,	0xC3,	0x00,	0x06,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_6_3SAMPLES */
		{
			0x0C,	0x5C,	0x0F,	0x0C,	0xF1,	0x4A,	0x30,	0x00,	0x03,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_4_7SAMPLES */
		{
			0x04,	0x1E,	0xAF,	0x0C,	0xF1,	0x73,	0x9D,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_3_3SAMPLES */
		{
			0x01,	0x07,	0xAB,	0x0C,	0xF1,	0xB1,	0xC0,	0x00,	0x06,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_1_6SAMPLES */
		{
			0x02,	0x93,	0x2D,	0x0C,	0xF1,	0xE3,	0x76,	0x00,	0x02,
		},
		/*	LX_AUD_SPDIF_DTO_MINUS_0_7SAMPLES */
		{
			0x00,	0x75,	0x2F,	0x0C,	0xF1,	0xEF,	0xE3,	0x00,	0x0B,
		},
		/*	LX_AUD_SPDIF_DTO_NORMAL */
		{
			0x00,	0x27,	0x8C,	0x0C,	0xF2,	0x04,	0x9A,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_0_7SAMPLES */
		{
			0x0C,	0x5C,	0x0F,	0x0C,	0xF2,	0x19,	0x50,	0x00,	0x09,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_1_6SAMPLES */
		{
			0x07,	0xB9,	0x89,	0x0C,	0xF2,	0x25,	0xBD,	0x00,	0x12,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_3_3SAMPLES */
		{
			0x03,	0x17,	0x03,	0x0C,	0xF2,	0x57,	0x73,	0x00,	0x0E,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_4_7SAMPLES */
		{
			0x0C,	0x5C,	0x0F,	0x0C,	0xF2,	0x95,	0x97,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_6_3SAMPLES */
		{
			0x00,	0x2B,	0xF1,	0x0C,	0xF2,	0xAA,	0x4D,	0x00,	0x09,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_7_8SAMPLES */
		{
			0x01,	0x3C,	0x67,	0x0C,	0xF2,	0xD3,	0xBA,	0x00,	0x06,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_9_4SAMPLES */
		{
			0x03,	0x17,	0x03,	0x0C,	0xF2,	0xFD,	0x27,	0x00,	0x03,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_10_9SAMPLES */
		{
			0x02,	0x0F,	0x57,	0x0C,	0xF3,	0x26,	0x94,	0x00,	0x00,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_12_5SAMPLES */
		{
			0x00,	0xC5,	0xC0,	0x0C,	0xF3,	0x50,	0x00,	0x00,	0x11,
		},
		/*	LX_AUD_SPDIF_DTO_PLUS_19_5SAMPLES */
		{
			0x01,	0x8B,	0x81,	0x0C,	0xF3,	0xF5,	0xB4,	0x00,	0x06,
		},
	},
};


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
//ADEC KDRV Structure
extern LX_AUD_KDRV_T g_adec_kdrv;


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#if 0
//Current Mixed IP Power Status
static LX_AUD_POWER_STATUS_T gADECPowerStatus_L9B0[LX_AUD_POWER_MAX] = {	\
							  {LX_AUD_POWER_AAD, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_ADC, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_HPDRV, LX_AUD_POWER_UP},
							  {LX_AUD_POWER_DAC, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_MIC, 	LX_AUD_POWER_UP} };
#endif

//Current SCART Boost Gain Setting
static UINT16 gScartBoostGain_L9B0 = 0;

//Current ADEC Clock Source Setting
static LX_AUD_CLOCK_SRC_T gAdecClockSource_L9B0 = LX_AUD_CLOCK_UNKNOWN;

//Current AAD Bypass Enabled
static BOOLEAN gAadBypassEnabled_L9B0 = FALSE;

//Current SRC Input Sampling Frequency Setting
static LX_AUD_SAMPLING_FREQ_T gAdecSrcFreq_L9B0 = LX_AUD_SAMPLING_FREQ_NONE;

//Current SPDIF Sampling Frequency Setting
static LX_AUD_SAMPLING_FREQ_T gAdecSpdifFreq_L9B0 = LX_AUD_SAMPLING_FREQ_NONE;

//Current PCM clock Rate Setting
static UINT32 	gAdecPcmClock_L9B0 = APLL_CLOCK_VALUE_12_288MHZ;	//4096

//Current SPDIF DTO Rate Setting
static LX_AUD_SPDIF_DTO_RATE_T gAdecSpdifDtoRate_L9B0 = LX_AUD_SPDIF_DTO_UNKNOWN;


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
	UINT8 tmpData = 0;

	VPORT_I2C_DATA_T *data = (VPORT_I2C_DATA_T*)reg;

	ACE_RegRead((data->slaveAddr)<<1, data->regAddr, &tmpData);
	data->data = tmpData;

//	AUD_KDRV_MIP_I2C("RD addr = 0x%2X reg = 0x%2X data = 0x%2X\n", data->slaveAddr, data->regAddr, data->data);

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
#if 0
	UINT8 tmpData = 0;
#endif

	VPORT_I2C_DATA_T *data = (VPORT_I2C_DATA_T*)reg;

	ACE_RegWrite((data->slaveAddr)<<1, data->regAddr, data->data);

	AUD_KDRV_MIP_I2C("WR addr = 0x%2X reg = 0x%2X data = 0x%2X\n",data->slaveAddr,data->regAddr, data->data);

#if 0
	I2C_DevRegRead((data->slaveAddr)<<1, data->regAddr, &tmpData, 3);
	data->data = tmpData;

	AUD_KDRV_MIP_I2C("RD addr = 0x%2X reg = 0x%2X data = 0x%2X\n", data->slaveAddr, data->regAddr, data->data);
#endif

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
	int 	ret = RET_OK;

	//Read I2C register
	*value = (UINT8)ACTRL_READ((UINT32)slaveAddr, (UINT32)regAddr);

//	AUD_KDRV_MIP_I2C("L9B0 Read  : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", slaveAddr, regAddr, *value);
//	AUD_KDRV_ERROR("L9B0 Read  : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", slaveAddr, regAddr, *value);

	return ret;
}

/**
 *  L9B0_ANALOG_WriteRegister
 *
 *  @parm UINT32 *
 *  @return int
*/
int L9B0_ANALOG_WriteRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 value)
{
	int 	ret = RET_OK;

	//Write I2C register
	(void)ACTRL_WRITE((UINT32)slaveAddr, (UINT32)regAddr, (UINT32)value);

	AUD_KDRV_MIP_I2C("L9B0 Write : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", slaveAddr, regAddr, value);

	return ret;
}

/**
 * Initializes the clock and reset module register value.
 * @see ADEC_Init
*/
int L9B0_MIXED_IP_ADEC_L9_InitClockRegisters( void )
{
	//Initialize clock registers.
	//clock setting for APLL block
	MIXIP_RdFL(gaudio_pll_0_bx);
	//MIXIP_Wr01(gaudio_pll_0_bx, apll_mode_en, 1);		//1 : APLL mode
	MIXIP_Wr01(gaudio_pll_0_bx, apll_mode_en, 0);	//0 : DPLL mode

	// 0 : 12.288MHz, 1 : 11.2896MHz, 2 : 8.192 MHz, 3 : 24.576MHz, 4 : 49.152 MHz,
	// 5 : 16.384 MHz, 6 : 32.768 MHz, 7 : 22.5792 MHz, 8 : 45.1584 MHz
	MIXIP_Wr01(gaudio_pll_0_bx, apll_mode, 0);
	MIXIP_WrFL(gaudio_pll_0_bx);

	MIXIP_RdFL(gaudio_pll_6_bx);
	MIXIP_Wr01(gaudio_pll_6_bx, apll_pdb, 1);		// 0 :power down, 1 : normal operation
	MIXIP_WrFL(gaudio_pll_6_bx);

	//clock setting for aad/btsc block
	MIXIP_RdFL(gafe_aad_0_bx);
	MIXIP_Wr01(gafe_aad_0_bx, aad_adc_selref, 3);
	MIXIP_Wr01(gafe_aad_0_bx, aad_adc_pdb, 1);
	MIXIP_Wr01(gafe_aad_0_bx, aad_dco_rtest, 1);
	MIXIP_Wr01(gafe_aad_0_bx, aad_dco_resetb, 1);
	MIXIP_WrFL(gafe_aad_0_bx);

	MIXIP_RdFL(gafe_aad_7_bx);
	MIXIP_Wr01(gafe_aad_7_bx, aad_spll_cvl, 2);
	MIXIP_Wr01(gafe_aad_7_bx, aad_spll_cvs, 3);
	MIXIP_Wr01(gafe_aad_7_bx, aad_spll_sel, 0);
	MIXIP_Wr01(gafe_aad_7_bx, aad_spll_pdb, 1);
	MIXIP_Wr01(gafe_aad_7_bx, aad_spllclk_test, 0);
	MIXIP_WrFL(gafe_aad_7_bx);

	MIXIP_RdFL(gafe_aad_8_bx);
	MIXIP_Wr01(gafe_aad_8_bx, aad_adcclk_test, 0);
	MIXIP_Wr01(gafe_aad_8_bx, aad_fs00clk_sel, 0);
	MIXIP_Wr01(gafe_aad_8_bx, aad_fs01clk_sel, 0);
	MIXIP_Wr01(gafe_aad_8_bx, aad_fs02clk_sel, 0);
	MIXIP_Wr01(gafe_aad_8_bx, aad_btscclk_sel, 0);
	MIXIP_WrFL(gafe_aad_8_bx);

	//delay before sw reset control
	udelay(MIXEDIP_RESET_DELAY_100US);

	//sw reset setting for mixed-IP block
	MIXIP_RdFL(gsoft_reset_4_bx);
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_mic, 0);
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auad, 0);
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 0);	//audio codec : dac1
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk0, 0);	//audio codec : dac0
	MIXIP_WrFL(gsoft_reset_4_bx);

	MIXIP_RdFL(gsoft_reset_5_bx);
	MIXIP_Wr01(gsoft_reset_5_bx, swrst_fs00, 0);
	MIXIP_WrFL(gsoft_reset_5_bx);

	MIXIP_RdFL(gsoft_reset_8_bx);
	MIXIP_Wr01(gsoft_reset_8_bx, swrst_adto, 0);
	MIXIP_Wr01(gsoft_reset_8_bx, swrst_aclk_mux2, 0);
	MIXIP_WrFL(gsoft_reset_8_bx);

	MIXIP_RdFL(gsoft_reset_9_bx);
//	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs25clk, 0);		//SRC output I2S clock
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs24clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs23clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs21clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs20clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_audclk_out,  0);		//D-AMP I2S clock
//	MIXIP_Wr01(gsoft_reset_9_bx, swrst_audclk_out_sub, 0);		//dac sub I2S clock
	MIXIP_WrFL(gsoft_reset_9_bx);

	MIXIP_RdFL(gsoft_reset_18_bx);
	MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk1, 0);
	MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk0, 0);
	MIXIP_WrFL(gsoft_reset_18_bx);

	//Fix AAD_AFE data output setup time error : change fs00_clk_out inversion : 2011.10.27
	MIXIP_RdFL(gaud_clock_inv_0_bx);
	MIXIP_Wr01(gaud_clock_inv_0_bx, fs00_clk_out, 1);
	MIXIP_WrFL(gaud_clock_inv_0_bx);

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_InitClockRegisters\n");
	return RET_OK;
}

/**
 * Resets the clock register value.
 * @see ADEC_Init
*/
int L9B0_MIXED_IP_ADEC_L9_ResetClockRegisters( void )
{
	//sw reset setting for mixed-IP block
	MIXIP_RdFL(gsoft_reset_4_bx);
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auad, 1);
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 1);	//audio codec : dac1
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk0, 1);	//audio codec : dac0
	MIXIP_WrFL(gsoft_reset_4_bx);

	MIXIP_RdFL(gsoft_reset_5_bx);
	MIXIP_Wr01(gsoft_reset_5_bx, swrst_fs00, 1);
	MIXIP_WrFL(gsoft_reset_5_bx);

	MIXIP_RdFL(gsoft_reset_8_bx);
	MIXIP_Wr01(gsoft_reset_8_bx, swrst_adto, 1);
	MIXIP_Wr01(gsoft_reset_8_bx, swrst_aclk_mux2, 1);
	MIXIP_WrFL(gsoft_reset_8_bx);

	MIXIP_RdFL(gsoft_reset_9_bx);
//	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs25clk, 0);		//SRC output I2S clock
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs24clk, 1);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs23clk, 1);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs21clk, 1);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs20clk, 1);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_audclk_out,  1);		//D-AMP I2S clock
//	MIXIP_Wr01(gsoft_reset_9_bx, swrst_audclk_out_sub, 0);		//dac sub I2S clock
	MIXIP_WrFL(gsoft_reset_9_bx);

	//add delay for clock setting
	udelay(MIXEDIP_RESET_DELAY_100US * 2);

	//sw reset setting for mixed-IP block
	MIXIP_RdFL(gsoft_reset_4_bx);
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auad, 0);
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 0);	//audio codec : dac1
	MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk0, 0);	//audio codec : dac0
	MIXIP_WrFL(gsoft_reset_4_bx);

	MIXIP_RdFL(gsoft_reset_5_bx);
	MIXIP_Wr01(gsoft_reset_5_bx, swrst_fs00, 0);
	MIXIP_WrFL(gsoft_reset_5_bx);

	MIXIP_RdFL(gsoft_reset_8_bx);
	MIXIP_Wr01(gsoft_reset_8_bx, swrst_adto, 0);
	MIXIP_Wr01(gsoft_reset_8_bx, swrst_aclk_mux2, 0);
	MIXIP_WrFL(gsoft_reset_8_bx);

	MIXIP_RdFL(gsoft_reset_9_bx);
//	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs25clk, 0);		//SRC output I2S clock
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs24clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs23clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs21clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs20clk, 0);
	MIXIP_Wr01(gsoft_reset_9_bx, swrst_audclk_out,  0);		//D-AMP I2S clock
//	MIXIP_Wr01(gsoft_reset_9_bx, swrst_audclk_out_sub, 0);		//dac sub I2S clock
	MIXIP_WrFL(gsoft_reset_9_bx);

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_ResetClockRegisters\n");
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_SetClockSource( LX_AUD_SAMPLING_FREQ_T ui32SrcFreq, LX_AUD_CLOCK_SRC_T ui8AdecClockSrc )
{
	BOOLEAN bAadBypassEnabled = FALSE;

#if 0
	ADEC_SET_PCM_INTERRUPT_T	pcmRate;
	ADEC_SET_SPDIF_DTO_T		spdifDTO;
#endif

	//Check previous clock source
	if(gAdecSrcFreq_L9B0 == ui32SrcFreq && gAdecClockSource_L9B0 == ui8AdecClockSrc)
	{
		AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetClockSource : same freq = %d, src = %d\n", ui32SrcFreq, ui8AdecClockSrc);
		return RET_OK;
	}

	//Check AAD Bypass Enabled Status
	if( (ui8AdecClockSrc == LX_AUD_CLOCK_ATV)
	  ||(ui8AdecClockSrc == LX_AUD_CLOCK_ADC)
	  ||(ui8AdecClockSrc == LX_AUD_CLOCK_HDMI) )
	{
		bAadBypassEnabled = TRUE;
	}
	else
	{
		bAadBypassEnabled = FALSE;
	}

	//Reset on for Mixed IP Module
	if(bAadBypassEnabled == FALSE || gAadBypassEnabled_L9B0 != bAadBypassEnabled)
	{
		MIXIP_RdFL(gacodec_9_bx);
		MIXIP_Wr01(gacodec_9_bx, dac0_mute_ena, 1);		// 1 bit : Line DAC CH0 Mute Control
		MIXIP_WrFL(gacodec_9_bx);

		MIXIP_RdFL(gacodec_18_bx);
		MIXIP_Wr01(gacodec_18_bx, dac1_mute_ena, 1);	// 1 bit : Line DAC CH1 Mute Control
		MIXIP_WrFL(gacodec_18_bx);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

		MIXIP_RdFL(gsoft_reset_18_bx);
		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk0, 1);	//audio codec : dac 0
		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk1, 1);	//audio codec : dac 1
		MIXIP_WrFL(gsoft_reset_18_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_4_bx);
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk0, 1);	//audio codec : dac 0
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 1);	//audio codec : dac 1
		MIXIP_WrFL(gsoft_reset_4_bx);

		MIXIP_RdFL(gsoft_reset_9_bx);
		MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs20clk, 1);	//hpdrv, clock change only
		MIXIP_WrFL(gsoft_reset_9_bx);
	}
	else	//SCART port is not reset.
	{
		MIXIP_RdFL(gacodec_18_bx);
		MIXIP_Wr01(gacodec_18_bx, dac1_mute_ena, 1);	// 1 bit : Line DAC CH1 Mute Control
		MIXIP_WrFL(gacodec_18_bx);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

		MIXIP_RdFL(gsoft_reset_18_bx);
		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk1, 1);	//audio codec : dac 1
		MIXIP_WrFL(gsoft_reset_18_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_4_bx);
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 1);	//audio codec : dac 1
		MIXIP_WrFL(gsoft_reset_4_bx);

		MIXIP_RdFL(gsoft_reset_9_bx);
		MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs20clk, 1);	//hpdrv
		MIXIP_WrFL(gsoft_reset_9_bx);
	}

	//add delay for clock setting
	udelay(MIXEDIP_RESET_DELAY_100US * 2);

	//Set default PCM frequency to 48Khz and notify input sampling frequency to DSP
	(void)L9B0_MIXED_IP_ADEC_L9_SetPcmClockRate(ui32SrcFreq, APLL_CLOCK_VALUE_12_288MHZ);

	//Set default SPDIF sampling frequency to 48Khz
	(void)L9B0_MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq(LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_SPDIF_DTO_NORMAL);

	//Setting Audio Clock Mux
	//Read clock mux reg.
	MIXIP_RdFL(gsoft_reset_10_bx);
	MIXIP_RdFL(gsoft_reset_11_bx);
	MIXIP_RdFL(gsoft_reset_12_bx);
	MIXIP_RdFL(gsoft_reset_13_bx);
	MIXIP_RdFL(gsoft_reset_14_bx);
	MIXIP_RdFL(gsoft_reset_15_bx);
	MIXIP_RdFL(gsoft_reset_16_bx);
	MIXIP_RdFL(gsoft_reset_17_bx);
	MIXIP_RdFL(gsoft_reset_18_bx);
	MIXIP_RdFL(gsoft_reset_19_bx);

	if( (ui8AdecClockSrc == LX_AUD_CLOCK_DTV)		//DTV to SPK(default)
      ||(ui8AdecClockSrc == LX_AUD_CLOCK_ADC) ) 	//ADC to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("LX_AUD_CLOCK_DTV/ADC\n");

		MIXIP_Wr01(gsoft_reset_10_bx, aclk_mux1_src,  1);
		MIXIP_Wr01(gsoft_reset_11_bx, aclk_mux1_div,  0);
		MIXIP_Wr01(gsoft_reset_11_bx, aclk_mux2_src,  1);
		MIXIP_Wr01(gsoft_reset_12_bx, aclk_mux2_div,  0);

		MIXIP_Wr01(gsoft_reset_12_bx, aclk_mux3_src,  1);	//Fs21 : APLL
		MIXIP_Wr01(gsoft_reset_13_bx, aclk_mux3_div,  1);
		MIXIP_Wr01(gsoft_reset_13_bx, aclk_mux4_src,  2);	//Fs22 : DTO
		MIXIP_Wr01(gsoft_reset_14_bx, aclk_mux4_div,  1);
		MIXIP_Wr01(gsoft_reset_14_bx, aclk_mux5_src,  1);	//Fs23 : APLL
		MIXIP_Wr01(gsoft_reset_15_bx, aclk_mux5_div,  1);
		MIXIP_Wr01(gsoft_reset_15_bx, aclk_mux6_src,  1);
		MIXIP_Wr01(gsoft_reset_16_bx, aclk_mux6_div,  1);
		MIXIP_Wr01(gsoft_reset_16_bx, aclk_mux7_src,  1);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux7_div,  1);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux8_src,  1);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux8_div,  1);

		if( ui8AdecClockSrc == LX_AUD_CLOCK_DTV )	//DTV to SPK(default)
		{
			MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_src,  1);
			MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_div,  0);
			MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_src, 1);
			MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_div, 0);
		}
   		else	//( ui8AdecClockSrc == LX_AUD_CLOCK_ADC ) //ADC to SPK, SCART AAD bypass
				//(ui8AdecClockSrc == LX_AUD_CLOCK_HDMI) ) //HDMI to SPK, SCART AAD bypass
		{
			MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_src,  0);
			MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_div,  1);
			MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_src, 1);
			MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_div, 0);
		}
	}
	else if(ui8AdecClockSrc == LX_AUD_CLOCK_HDMI) //HDMI to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("LX_AUD_CLOCK_HDMI\n");

		MIXIP_Wr01(gsoft_reset_10_bx, aclk_mux1_src,  1);
		MIXIP_Wr01(gsoft_reset_11_bx, aclk_mux1_div,  0);
		MIXIP_Wr01(gsoft_reset_11_bx, aclk_mux2_src,  1);
		MIXIP_Wr01(gsoft_reset_12_bx, aclk_mux2_div,  0);

		MIXIP_Wr01(gsoft_reset_12_bx, aclk_mux3_src,  1);	//Fs21 : APLL
		MIXIP_Wr01(gsoft_reset_13_bx, aclk_mux3_div,  1);
		MIXIP_Wr01(gsoft_reset_13_bx, aclk_mux4_src,  2);	//Fs22 : DTO
		MIXIP_Wr01(gsoft_reset_14_bx, aclk_mux4_div,  1);
		MIXIP_Wr01(gsoft_reset_14_bx, aclk_mux5_src,  3);	//Fs23 : HDMI Link0 ACR
		MIXIP_Wr01(gsoft_reset_15_bx, aclk_mux5_div,  0);
		MIXIP_Wr01(gsoft_reset_15_bx, aclk_mux6_src,  1);
		MIXIP_Wr01(gsoft_reset_16_bx, aclk_mux6_div,  0);
		MIXIP_Wr01(gsoft_reset_16_bx, aclk_mux7_src,  1);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux7_div,  1);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux8_src,  1);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux8_div,  1);

		MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_src,  0);
		MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_div,  1);
		MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_src, 1);
		MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_div, 0);
	}
	else if( ui8AdecClockSrc == LX_AUD_CLOCK_ATV ) //Analog TV to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("LX_AUD_CLOCK_ATV\n");

		MIXIP_Wr01(gsoft_reset_10_bx, aclk_mux1_src,  0);
		MIXIP_Wr01(gsoft_reset_11_bx, aclk_mux1_div,  1);
		MIXIP_Wr01(gsoft_reset_11_bx, aclk_mux2_src,  0);
		MIXIP_Wr01(gsoft_reset_12_bx, aclk_mux2_div,  1);

		MIXIP_Wr01(gsoft_reset_12_bx, aclk_mux3_src,  0);	//Fs21 : AAD-PLL
		MIXIP_Wr01(gsoft_reset_13_bx, aclk_mux3_div,  2);
		MIXIP_Wr01(gsoft_reset_13_bx, aclk_mux4_src,  0);	//Fs22 : AAD-PLL
		MIXIP_Wr01(gsoft_reset_14_bx, aclk_mux4_div,  2);
		MIXIP_Wr01(gsoft_reset_14_bx, aclk_mux5_src,  0);	//Fs23 : AAD-PLL
		MIXIP_Wr01(gsoft_reset_15_bx, aclk_mux5_div,  2);
		MIXIP_Wr01(gsoft_reset_15_bx, aclk_mux6_src,  0);
		MIXIP_Wr01(gsoft_reset_16_bx, aclk_mux6_div,  2);
		MIXIP_Wr01(gsoft_reset_16_bx, aclk_mux7_src,  0);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux7_div,  2);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux8_src,  0);
		MIXIP_Wr01(gsoft_reset_17_bx, aclk_mux8_div,  2);

		MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_src,  0);
		MIXIP_Wr01(gsoft_reset_18_bx, aclk_mux9_div,  1);
		MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_src, 0);
		MIXIP_Wr01(gsoft_reset_19_bx, aclk_mux10_div, 1);
	}
	else
	{
		AUD_KDRV_ERROR("L9B0_MIXED_IP_ADEC_L9_SetClockSource : freq = %d, src %d(Not Supported!!!)\n", ui32SrcFreq, ui8AdecClockSrc);
		return RET_ERROR;
	}

	//Write clock mux reg.
	MIXIP_WrFL(gsoft_reset_10_bx);
	MIXIP_WrFL(gsoft_reset_11_bx);
	MIXIP_WrFL(gsoft_reset_12_bx);
	MIXIP_WrFL(gsoft_reset_13_bx);
	MIXIP_WrFL(gsoft_reset_14_bx);
	MIXIP_WrFL(gsoft_reset_15_bx);
	MIXIP_WrFL(gsoft_reset_16_bx);
	MIXIP_WrFL(gsoft_reset_17_bx);
	MIXIP_WrFL(gsoft_reset_18_bx);
	MIXIP_WrFL(gsoft_reset_19_bx);

	//add delay for clock setting
	udelay(MIXEDIP_RESET_DELAY_100US * 2);

	//Reset off for Mixed IP Module
	if(bAadBypassEnabled == FALSE || gAadBypassEnabled_L9B0 != bAadBypassEnabled)
	{
		//Wait for SCART & HP reset
		MIXIP_RdFL(gsoft_reset_9_bx);
		MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs20clk, 0);	//hpdrv
		MIXIP_WrFL(gsoft_reset_9_bx);

		MIXIP_RdFL(gsoft_reset_4_bx);
//		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk0, 0);	//audio IP reset : dac 0,
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 0);	//audio IP reset : dac 1
		MIXIP_WrFL(gsoft_reset_4_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_18_bx);
//		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk0, 0);	//bclk reset : dac 0
		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk1, 0);	//bclk reset : dac 1
		MIXIP_WrFL(gsoft_reset_18_bx);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

//		MIXIP_RdFL(gacodec_9_bx);
//		MIXIP_Wr01(gacodec_9_bx, dac0_mute_ena, 0);		// 1 bit : Line DAC CH0 Mute Control
//		MIXIP_WrFL(gacodec_9_bx);

		MIXIP_RdFL(gacodec_18_bx);
		MIXIP_Wr01(gacodec_18_bx, dac1_mute_ena, 0);	// 1 bit : Line DAC CH1 Mute Control
		MIXIP_WrFL(gacodec_18_bx);
	}
	else	//SCART port is not reset.
	{
		//Wait for SCART & HP reset
		MIXIP_RdFL(gsoft_reset_9_bx);
		MIXIP_Wr01(gsoft_reset_9_bx, swrst_aud_fs20clk, 0);	//hpdrv, clock change only
		MIXIP_WrFL(gsoft_reset_9_bx);

		MIXIP_RdFL(gsoft_reset_4_bx);
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 0);	//audio codec : dac 1
		MIXIP_WrFL(gsoft_reset_4_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_18_bx);
		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk1, 0);	//audio codec : dac 1
		MIXIP_WrFL(gsoft_reset_18_bx);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

		MIXIP_RdFL(gacodec_18_bx);
		MIXIP_Wr01(gacodec_18_bx, dac1_mute_ena, 0);	// 1 bit : Line DAC CH1 Mute Control
		MIXIP_WrFL(gacodec_18_bx);
	}

#if 0
	//Send a IPC command for PCM clock setting
	if(g_adec_kdrv.bInitDone == TRUE)
	{
		//Clears a PCM Clock interrupt count
		pcmRate.ui32InFs		  = (UINT32)ui32SrcFreq;
		pcmRate.ui32PCMclkRate	  = (UINT32)APLL_CLOCK_VALUE_12_288MHZ;
		pcmRate.ui32ForceCntClear = (UINT32)1;

		ADEC_IPC_SetPCMRate(pcmRate);
	}

	//Send a IPC command for DTO setting
	if(g_adec_kdrv.bInitDone == TRUE)
	{
		//Clears a SPDIF Clock interrupt count
		spdifDTO.ui32SampleFreq    = (UINT32)LX_AUD_SAMPLING_FREQ_48_KHZ;
		spdifDTO.ui32DtoRate	   = (UINT32)LX_AUD_SPDIF_DTO_NORMAL;
		spdifDTO.ui32ForceCntClear = (UINT32)1;

		ADEC_IPC_SetSPDIFDTO(spdifDTO);
	}
#endif

	//Save current SRC frequency
	gAdecSrcFreq_L9B0 = ui32SrcFreq;

	//Save current clock source
	gAdecClockSource_L9B0 = ui8AdecClockSrc;

	//Save current SCART bypass status
	gAadBypassEnabled_L9B0 = bAadBypassEnabled;

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetClockSource : freq = %d, src = %d\n", ui32SrcFreq, ui8AdecClockSrc);
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
	//ADEC_SET_PCM_INTERRUPT_T	 pcmRate;

	//Check a previous status.
	if( gAdecSrcFreq_L9B0 == ui32SrcFreq && gAdecPcmClock_L9B0 == ui32PcmClock)
	{
		AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetPcmClockRate : same freq = %d, rate = %d\n", ui32SrcFreq, ui32PcmClock);
		return RET_OK;
	}

	//Check a PCM clock rate for min and max value.
	if(ui32PcmClock < APLL_CLOCK_VALUE_10_752MHZ)
	{
		AUD_KDRV_ERROR("SetPcmClockRate : freq = %dKHz, MIN rate = %d\n", ui32SrcFreq, ui32PcmClock);

		ui32PcmClock = APLL_CLOCK_VALUE_10_752MHZ;
	}
	else if(ui32PcmClock > APLL_CLOCK_VALUE_13_824MHZ)
	{
		AUD_KDRV_ERROR("SetPcmClockRate : freq = %dKHz, MAX rate = %d\n", ui32SrcFreq, ui32PcmClock);

		ui32PcmClock = APLL_CLOCK_VALUE_13_824MHZ;
	}

	//Read a PCM Clock registers for audio PLL. Change appl_n_0 first(우 영신.2012.05.11)
	MIXIP_RdFL(gaudio_pll_4_bx);
	MIXIP_RdFL(gaudio_pll_3_bx);

	//Set a APLL PCM Clock Value
	MIXIP_Wr01(gaudio_pll_4_bx, apll_n_0, (ui32PcmClock >> 0) & 0xFF);
	MIXIP_Wr01(gaudio_pll_3_bx, apll_n_1, (ui32PcmClock >> 8) & 0x1F);

	//Update APLL clock register.
	MIXIP_WrFL(gaudio_pll_4_bx);
	MIXIP_WrFL(gaudio_pll_3_bx);

#if 0
	//Send a IPC command for DTO setting
	if(g_adec_kdrv.bInitDone == TRUE)
	{
		pcmRate.ui32InFs		  = (UINT32)ui32SrcFreq;
		pcmRate.ui32PCMclkRate	  = (UINT32)ui32PcmClock;
		pcmRate.ui32ForceCntClear = (UINT32)0;

		ADEC_IPC_SetPCMRate(pcmRate);
	}
#endif

	//Save current SRC frequency
	gAdecSrcFreq_L9B0  = ui32SrcFreq;

	//Save current PCM Clock Rate
	gAdecPcmClock_L9B0 = ui32PcmClock;

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetPcmClockRate : src  freq = %dKHz, rate = %d(0x%4X)\n", ui32SrcFreq, ui32PcmClock, ui32PcmClock);
	return RET_OK;

}



/**
 * Sets a SPDIF Clock frequency and Rate to sync with PCM clock for D-AMP output.
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq ( LX_AUD_SAMPLING_FREQ_T ui32SamplingFreq, LX_AUD_SPDIF_DTO_RATE_T stSpdifDtoRate )
{
	UINT8	freqTableNum = 0;
	UINT8	rateTableNum = 0;

//	ADEC_SET_SPDIF_DTO_T 	 spdifDTO;

	//Check a previous status.
	if(	gAdecSpdifFreq_L9B0 == ui32SamplingFreq && gAdecSpdifDtoRate_L9B0 == stSpdifDtoRate)
	{
		AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : same freq = %d_KHZ, rate = %d\n",  ui32SamplingFreq, stSpdifDtoRate);
		return RET_OK;
	}

	//Read a SPDIF DTO registers.
	MIXIP_RdFL(gaudio_dto_0_bx);
	MIXIP_RdFL(gaudio_dto_1_bx);
	MIXIP_RdFL(gaudio_dto_2_bx);
	MIXIP_RdFL(gaudio_dto_3_bx);
	MIXIP_RdFL(gaudio_dto_4_bx);
	MIXIP_RdFL(gaudio_dto_5_bx);
	MIXIP_RdFL(gaudio_dto_6_bx);
	MIXIP_RdFL(gaudio_dto_7_bx);
	MIXIP_RdFL(gaudio_dto_8_bx);

	if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_48_KHZ )
	{
		AUD_KDRV_PRINT("SetSPDIFSamplingFreq : 48_KHZ\n" );

		//Set a SPDIF DTO frequency table.
		freqTableNum = 0;

		//Set a SPDIF DTO Frequency for IPC
//		spdifDTO.ui32SampleFreq = LX_AUD_SAMPLING_FREQ_48_KHZ;
	}
	else if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_44_1KHZ )
	{
		AUD_KDRV_PRINT("SetSPDIFSamplingFreq : 44_1KHZ\n" );

		//Set a SPDIF DTO frequency table.
		freqTableNum = 1;

		//Set a SPDIF DTO Frequency for IPC
//		spdifDTO.ui32SampleFreq = LX_AUD_SAMPLING_FREQ_44_1KHZ;
	}
	else if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_32_KHZ )
	{
		AUD_KDRV_PRINT("SetSPDIFSamplingFreq : 32_KHZ\n" );

		//Set a SPDIF DTO frequency table.
		freqTableNum = 2;

		//Set a SPDIF DTO Frequency for IPC
//		spdifDTO.ui32SampleFreq = LX_AUD_SAMPLING_FREQ_32_KHZ;
	}
	else
	{
		AUD_KDRV_ERROR("SetSPDIFSamplingFreq : freq = %d\n", ui32SamplingFreq);

		//Set a SPDIF DTO frequency table.
		freqTableNum = 0;

		//Set a SPDIF DTO Frequency for IPC
//		spdifDTO.ui32SampleFreq = LX_AUD_SAMPLING_FREQ_48_KHZ;
	}

	//Set a SPDIF DTO rate table and Rate for IPC.
	if(stSpdifDtoRate <= LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES)
	{
		AUD_KDRV_ERROR("SetSPDIFSamplingFreq : freq = %dKHz, MIN rate = %d\n", ui32SamplingFreq, stSpdifDtoRate);

		rateTableNum = LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES - 1;	//LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES
	}
	else if( stSpdifDtoRate >= LX_AUD_SPDIF_DTO_PLUS_19_5SAMPLES)
	{
		AUD_KDRV_ERROR("SetSPDIFSamplingFreq : freq = %dKHz, MAX rate = %d\n", ui32SamplingFreq, stSpdifDtoRate);

		rateTableNum = LX_AUD_SPDIF_DTO_PLUS_19_5SAMPLES - 1;	//LX_AUD_SPDIF_DTO_PLUS_19_5SAMPLES
	}
	else
	{
		rateTableNum = (UINT8)stSpdifDtoRate - 1;	//Rate table starts 0 value.
	}

	//Set a SPDIF DTO Rate
	if( (freqTableNum < SPDIF_ES_OUT_FREQ_NUMBER)
	  &&(rateTableNum < LX_AUD_SPDIF_DTO_RATE_NUMBER) )
	{
		MIXIP_Wr01(gaudio_dto_0_bx, reg_adto_loop_value_2, g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][0]);
		MIXIP_Wr01(gaudio_dto_1_bx, reg_adto_loop_value_1, g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][1]);
		MIXIP_Wr01(gaudio_dto_2_bx, reg_adto_loop_value_0, g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][2]);
		MIXIP_Wr01(gaudio_dto_3_bx, reg_adto_add_value_3,  g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][3]);
		MIXIP_Wr01(gaudio_dto_4_bx, reg_adto_add_value_2,  g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][4]);
		MIXIP_Wr01(gaudio_dto_5_bx, reg_adto_add_value_1,  g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][5]);
		MIXIP_Wr01(gaudio_dto_6_bx, reg_adto_add_value_0,  g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][6]);
		MIXIP_Wr01(gaudio_dto_7_bx, reg_adto_err_value_1,  g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][7]);
		MIXIP_Wr01(gaudio_dto_8_bx, reg_adto_err_value_0,  g_ADEC_SpdifDtoTable[freqTableNum][rateTableNum][8]);
	}

	//Update DTO clock register.
	//Update add / error value register : 2012.01.11 by joonil.lee request
	MIXIP_WrFL(gaudio_dto_3_bx);
	MIXIP_WrFL(gaudio_dto_4_bx);
	MIXIP_WrFL(gaudio_dto_5_bx);
	MIXIP_WrFL(gaudio_dto_6_bx);
	MIXIP_WrFL(gaudio_dto_7_bx);
	MIXIP_WrFL(gaudio_dto_8_bx);

	//Update loop value register in last : 2012.01.11 by joonil.lee request
	MIXIP_WrFL(gaudio_dto_0_bx);
	MIXIP_WrFL(gaudio_dto_1_bx);
	MIXIP_WrFL(gaudio_dto_2_bx);

#if 0
	//Send a IPC command for DTO setting
	if(g_adec_kdrv.bInitDone == TRUE)
	{
		spdifDTO.ui32DtoRate	   = (UINT32)stSpdifDtoRate;
		spdifDTO.ui32ForceCntClear = (UINT32)0;

		ADEC_IPC_SetSPDIFDTO(spdifDTO);
	}
#endif

	//Save current SPDIF sampling frequency
	gAdecSpdifFreq_L9B0    = ui32SamplingFreq;

	//Save current SPDIF DTO Rate
	gAdecSpdifDtoRate_L9B0 = stSpdifDtoRate;

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : freq = %dKHz, rate = %d\n", ui32SamplingFreq, stSpdifDtoRate);
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_InitCodecRegisters ( void )
{
	//Setting Mixed IP
	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_InitCodecRegisters : Start\n");

	L9B0_ANALOG_WriteRegister(0x1D, 0x00, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x01, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x03, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x04, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x05, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x0B, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x0E, 0x00);		//DAC0 Volume -125dB
//	L9B0_ANALOG_WriteRegister(0x1D, 0x0F, 0xFF);		//0x0FF => -31dB
//	L9B0_ANALOG_WriteRegister(0x1D, 0x0F, 0x6E);		//0x6E(SCART DTV) => default value workaround
//	L9B0_ANALOG_WriteRegister(0x1D, 0x0F, 0x16);		//0x16(SCART DTV) => default value workaround
	L9B0_ANALOG_WriteRegister(0x1D, 0x0F, 0x13);		//0x13(SCART DTV) => default value workaround, 2012.05.02
	L9B0_ANALOG_WriteRegister(0x1D, 0x11, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x13, 0x20);		//DAC0 mute rate control, 2011.11.117(0x20 : 64ms) <= 2011. 09.23(0x0F : 30ms)
	L9B0_ANALOG_WriteRegister(0x1D, 0x14, 0x01);		//Enable DAC0 by-pass, 2011.06.13
	L9B0_ANALOG_WriteRegister(0x1D, 0x16, 0x00);
//	L9B0_ANALOG_WriteRegister(0x1D, 0x17, 0x00);		//DAC1 Volume -125dB
//	L9B0_ANALOG_WriteRegister(0x1D, 0x18, 0xFF);		//0x0FF => -31dB
//	L9B0_ANALOG_WriteRegister(0x1D, 0x17, 0x01);		//0x01(HP Volume 10) => default value workaround,
//	L9B0_ANALOG_WriteRegister(0x1D, 0x18, 0x17);		//0x17(HP Volume 10) => default value workaround
	L9B0_ANALOG_WriteRegister(0x1D, 0x17, 0x00);		//0x00
	L9B0_ANALOG_WriteRegister(0x1D, 0x18, 0x00);		//0x00
	L9B0_ANALOG_WriteRegister(0x1D, 0x1A, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x1C, 0x0F);		//DAC1 mute rate control, 2011. 09.23(0x0F : 30 ms)
	L9B0_ANALOG_WriteRegister(0x1D, 0x1D, 0x01);		//Enable DAC1 by-pass, 2011.06.13
	L9B0_ANALOG_WriteRegister(0x1D, 0x1F, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x20, 0x40);		//DAC0/1 I2S settimg : Normal(0x40) -> L/R change(0x50)

	if(lx_ace_rev() >= LX_CHIP_REV(L9, B1))
	{
		L9B0_ANALOG_WriteRegister(0x1D, 0x2A, 0x03);	//L9 ACE, B1, ADC L/R change, falling(0x02) for I2S output ->  B1, L/R(0x03) rising
	}
	else
	{
		L9B0_ANALOG_WriteRegister(0x1D, 0x2A, 0x02);	//L9 ACE, B0, ADC L/R change, falling(0x02) for I2S output ->  B1, L/R(0x03) rising
	}

	L9B0_ANALOG_WriteRegister(0x1D, 0x2B, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x2C, 0x08);		//Amplify ADC digital gain : 1.00 dB, 2011.11.08
	L9B0_ANALOG_WriteRegister(0x1D, 0x2D, 0x01);		//Amplify ADC digital gain : 1.00 dB, 2011.11.08
	L9B0_ANALOG_WriteRegister(0x1D, 0x2F, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x31, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x33, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x37, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x39, 0x00);
	L9B0_ANALOG_WriteRegister(0x1D, 0x3A, 0x00);

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_InitCodecRegisters : Done!!!\n");
	return RET_OK;
}

/**
 * Control the Mixed IP AAD, ADC, MIC ADC, DAC and HPDRV module to power on and mute off.
 * @see ADEC_L9_SetSource
*/
int L9B0_MIXED_IP_ADEC_L9_PowerControl ( LX_AUD_POWER_BLOCK_T block, LX_AUD_POWER_MODE_T mode )
{
	return RET_OK;

//L9 A0 ADC uses AAD clock for operation, so AAD block must always enabled now.
#if 0

	//Set Power Control for ATSC model
	if ( g_eAdecInitType & LX_AUD_INIT_TYPE_SYS_ATSC )
	{
		if(stSetSource.adecSource == LX_AUD_IN_PORT_SIF)
		{
			/* AAD Power-up */
			MIXED_IP_ADEC_L9_PowerControl(LX_AUD_POWER_AAD, LX_AUD_POWER_UP);
		}
		else
		{
			/* AAD Power-down */
			MIXED_IP_ADEC_L9_PowerControl(LX_AUD_POWER_AAD, LX_AUD_POWER_DOWN);
		}
	}
	//Set Power Control for DVB model
	/* AAD is enabled automatically. */
	/* When ADC is power-down, SCART output is also disabled. */
	else if( g_eAdecInitType & LX_AUD_INIT_TYPE_SYS_DVB )
	{
		if(stSetSource.adecSource == LX_AUD_IN_PORT_TP)
		{
			/* AAD Power-down  */
			MIXED_IP_ADEC_L9_PowerControl(LX_AUD_POWER_AAD, LX_AUD_POWER_DOWN);
		}
		else
		{
			/* AAD Power-up */
			MIXED_IP_ADEC_L9_PowerControl(LX_AUD_POWER_AAD, LX_AUD_POWER_UP);
		}
	}
	else
	{
		/* AAD Power-up */
		MIXED_IP_ADEC_L9_PowerControl(LX_AUD_POWER_AAD, LX_AUD_POWER_UP);

		/* ADC Power-up */
		MIXED_IP_ADEC_L9_PowerControl(LX_AUD_POWER_ADC, LX_AUD_POWER_UP);
	}


	//LX_AUD_POWER_AAD
	if(block == LX_AUD_POWER_AAD)
	{
		if( (gADECPowerStatus_L9B0[LX_AUD_POWER_AAD].block == block)
		  &&(gADECPowerStatus_L9B0[LX_AUD_POWER_AAD].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9B0[LX_AUD_POWER_AAD].block = block;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(AAD) : Same mode(%d)\n", mode);
		}
		else
		{
			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(AAD) : block = %d, mode = %d\n", block, mode);

			//update power block mode
			gADECPowerStatus_L9B0[LX_AUD_POWER_AAD].mode = mode;

			if (mode == LX_AUD_POWER_UP)
			{
				VPORT_I2C_Read((UINT32 *)&gafe_aad_0);
				gafe_aad_0.aad_dco_resetb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_aad_0);
				udelay(AAD_DCO_RESETB_DELAY);	//Spec. => 5 us

				VPORT_I2C_Read((UINT32 *)&gafe_aad_7);
				gafe_aad_7.aad_spll_pdb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_aad_7);
				udelay(AAD_SPLL_PDB_DELAY);		//Spec. => 200 us

				VPORT_I2C_Read((UINT32 *)&gafe_aad_0);
				gafe_aad_0.aad_adc_pdb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_aad_0);
				udelay(AAD_ADC_PDB_DELAY); 		//Spec. => 3 cycles

				udelay(AAD_SW_RESET_DELAY);		//Spec.(?) => 200 us

				VPORT_I2C_Read((UINT32*)&gsoft_reset_5);
				gsoft_reset_5.swrst_fs00 = 0;	//aad
				VPORT_I2C_Write((UINT32*)&gsoft_reset_5);
			}
			else
			{
				//To eliminate D-AMP noise
				udelay(AAD_POWER_OFF_DELAY);	//Spec.(?) => 200 us

				VPORT_I2C_Read((UINT32*)&gsoft_reset_5);
				gsoft_reset_5.swrst_fs00 = 1;	//aad
				VPORT_I2C_Write((UINT32*)&gsoft_reset_5);

				VPORT_I2C_Read((UINT32 *)&gafe_aad_0);
				gafe_aad_0.aad_adc_pdb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_aad_0);
				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us

				VPORT_I2C_Read((UINT32 *)&gafe_aad_7);
				gafe_aad_7.aad_spll_pdb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_aad_7);
				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us

				VPORT_I2C_Read((UINT32 *)&gafe_aad_0);
				gafe_aad_0.aad_dco_resetb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_aad_0);

				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us
			}

			/* When AAD is power-up, SCART output is also enabled. */
			if( g_eAdecInitType & LX_AUD_INIT_TYPE_SYS_DVB )
			{
				//sw reset setting for SCART block
				VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
				gsoft_reset_8.swrst_aclk_mux2 = 1;	//audio codec
				VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

				VPORT_I2C_Read((UINT32*)&gsoft_reset_4_bx);
				gsoft_reset_4_bx.swrst_auda_mclk1 = 1;
				gsoft_reset_4_bx.swrst_auda_mclk0 = 1;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4_bx);

				udelay(20);

				//sw reset setting for SCART block
				VPORT_I2C_Read((UINT32*)&gsoft_reset_4_bx);
				gsoft_reset_4_bx.swrst_auda_mclk1 = 0;
				gsoft_reset_4_bx.swrst_auda_mclk0 = 0;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4_bx);

				VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
				gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
				VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

				AUD_KDRV_MIP_DEBUG("MIXED_IP_SCART_RESET\n");
				AUD_KDRV_ERROR("MIXED_IP_SCART_RESET\n");
			}

		}
	}

	//LX_AUD_POWER_ADC
	if(block == LX_AUD_POWER_ADC)
	{
		if( (gADECPowerStatus_L9B0[LX_AUD_POWER_ADC].block == block)
		  &&(gADECPowerStatus_L9B0[LX_AUD_POWER_ADC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9B0[LX_AUD_POWER_ADC].block = block;

			AUD_KDRV_MIP_DEBUG("ADC : Same mode(%d)\n", mode);
		}
		else
		{
			AUD_KDRV_MIP_DEBUG("ADC : block = %d, mode = %d\n", block, mode);

			//update power block mode
			gADECPowerStatus_L9B0[LX_AUD_POWER_ADC].mode = mode;

			if (mode == LX_AUD_POWER_UP)
			{
				VPORT_I2C_Read((UINT32 *)&gafe_acodec_3);
				gafe_acodec_3.auad_pdb_in 		= 1;
				gafe_acodec_3.auad_rec_ch_muteb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_3);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&gacodec_39);
				gacodec_39.ladc_mute_ena = 1;
				VPORT_I2C_Write((UINT32*)&gacodec_39);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&gsoft_reset_4_bx);
				gsoft_reset_4_bx.swrst_auad = 1;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4_bx);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us
			}
			else
			{
				VPORT_I2C_Read((UINT32 *)&gafe_acodec_3);
				gafe_acodec_3.auad_pdb_in 		= 0;
				gafe_acodec_3.auad_rec_ch_muteb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_3);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&gacodec_39);
				gacodec_39.ladc_mute_ena = 0;
				VPORT_I2C_Write((UINT32*)&gacodec_39);

				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&gsoft_reset_4_bx);
				gsoft_reset_4_bx.swrst_auad = 0;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4_bx);

				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us
			}
		}
	}

	//LX_AUD_POWER_DAC
	if(block == LX_AUD_POWER_DAC)
	{
		if( (gADECPowerStatus_L9B0[LX_AUD_POWER_DAC].block == block)
		  &&(gADECPowerStatus_L9B0[LX_AUD_POWER_DAC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9B0[LX_AUD_POWER_DAC].block = block;

			AUD_KDRV_MIP_DEBUG("DAC : Same mode(%d)\n", mode);
		}
		else
		{
			//update power block mode
			gADECPowerStatus_L9B0[LX_AUD_POWER_DAC].mode = mode;

			AUD_KDRV_MIP_DEBUG("DAC : block = %d, mode = %d\n", block, mode);

			if (mode == LX_AUD_POWER_UP)
			{
				VPORT_I2C_Read((UINT32 *)&gafe_acodec_0);
				gafe_acodec_0.auda_pdb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_0);
				msleep_interruptible(AUDA_PDB_DELAY);		//Spec. => 40ms

				VPORT_I2C_Read((UINT32 *)&gafe_acodec_0);
				gafe_acodec_0.auda_pdb_dse = 1;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_0);
				msleep_interruptible(AUDA_PDB_DSE_DELAY);	//Spec. => 40ms

				udelay(AUDA_PDB_DSE_DELAY);		//Spec. => 40 us
			}
			else
			{
				udelay(AUDA_PDB_DSE_DELAY);		//Spec. => 40 us

				VPORT_I2C_Read((UINT32 *)&gafe_acodec_0);
				gafe_acodec_0.auda_pdb_dse = 0;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_0);
				msleep_interruptible(AUDA_PDB_DSE_DELAY);	//Spec. => 40ms

				VPORT_I2C_Read((UINT32 *)&gafe_acodec_0);
				gafe_acodec_0.auda_pdb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_0);
				msleep_interruptible(AUDA_PDB_DELAY);		//Spec. => 40ms
			}
		}
	}


	//LX_AUD_POWER_MIC
	if(block == LX_AUD_POWER_MIC)
	{
		if( (gADECPowerStatus_L9B0[LX_AUD_POWER_MIC].block == block)
		  &&(gADECPowerStatus_L9B0[LX_AUD_POWER_MIC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9B0[LX_AUD_POWER_MIC].block = block;

			AUD_KDRV_MIP_DEBUG("MIC : Same mode(%d)\n", mode);
		}
		else
		{
			//update power block mode
			gADECPowerStatus_L9B0[LX_AUD_POWER_MIC].mode = mode;

			AUD_KDRV_MIP_DEBUG("MIC : block = %d, mode = %d\n", block, mode);

			if (mode == LX_AUD_POWER_UP)
			{
				VPORT_I2C_Read((UINT32 *)&gafe_acodec_5);
				gafe_acodec_5.aumi_pdb_in = 1;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_5);
				msleep_interruptible(AUMI_PDB_IN_DELAY);	//Spec. => 200 ms
			}
			else
			{
				VPORT_I2C_Read((UINT32 *)&gafe_acodec_5);
				gafe_acodec_5.aumi_pdb_in = 0;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_5);
				msleep_interruptible(AUMI_PDB_IN_DELAY);	//Spec. => 200 ms
			}
		}
	}

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_PowerControl : block = %d, mode = %d\n", block, mode);
	return RET_OK;
#endif

}

/**
 * Start the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_StartCodec ( void )
{
	//Setting Mixed IP
	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_StartCodec : Start\n");

	L9B0_ANALOG_WriteRegister(0x1D, 0x00, 0x7C);
	L9B0_ANALOG_WriteRegister(0x1D, 0x01, 0x19);

	//Hum noise issue after DV-2nd Board
//	L9B0_ANALOG_WriteRegister(0x1D, 0x02, 0x1B);

	//Hum noise issue to DV-2nd Board(2011.10.24)
//	L9B0_ANALOG_WriteRegister(0x1D, 0x02, 0x40);
	L9B0_ANALOG_WriteRegister(0x1D, 0x02, 0x00);	//Amplify ADC digital gain : 1.00 dB, 2011.11.08

	L9B0_ANALOG_WriteRegister(0x1D, 0x03, 0x7B);
	L9B0_ANALOG_WriteRegister(0x1D, 0x10, 0x02);
	L9B0_ANALOG_WriteRegister(0x1D, 0x16, 0x02);
	L9B0_ANALOG_WriteRegister(0x1D, 0x2B, 0x40);
	L9B0_ANALOG_WriteRegister(0x1D, 0x2F, 0x0F);	//to supress pop-noise. ADC volume rate control, 2011.12.29
	L9B0_ANALOG_WriteRegister(0x1D, 0x31, 0x0F);	//to supress pop-noise. ADC mute rate control, 2011.12.29

	L9B0_ANALOG_WriteRegister(0x1D, 0x14, 0x05);	//DAC0 Mute on, SCART
//	L9B0_ANALOG_WriteRegister(0x1D, 0x1D, 0x05);	//DAC1 Mute on, HPDRV
	L9B0_ANALOG_WriteRegister(0x1D, 0x32, 0x04);	//ADC Mute on

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_StartCodec : Done\n");

	return RET_OK;
}

/**
 * Stop the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9B0_MIXED_IP_ADEC_L9_StopCodec ( void )
{

	AUD_KDRV_DEBUG_TMP("L9B0_MIXED_IP_ADEC_L9_StopCodec : Not Implemented!!!\n");
	return RET_OK;
}

/**
 * Sets a ADC port number for ADEC I2S input.
 * @see ADEC_L9_SetSource
*/
int L9B0_MIXED_IP_ADEC_L9_SetADCPortNumber ( UINT8 ui8PortNum )
{
	if(ui8PortNum <= 5) //ui8PortNum 7 is defined for MIC input test
	{
		MIXIP_RdFL(gacodec_39_bx);
		MIXIP_Wr01(gacodec_39_bx, ladc_mute_ena, 1);
		MIXIP_WrFL(gacodec_39_bx);

		/* Wait for pop-noise supression */
		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_4_bx);
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auad, 1);
		MIXIP_WrFL(gsoft_reset_4_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		/* Set a ADC port number */
		MIXIP_RdFL(gafe_acodec_1_bx);
		//3A_01_18:ADC ch1='floating' 19:ADC ch2=AV2  1A:ADC ch3=AV1  1B:ADC ch4=COMP2 1C:ADC ch5=PCIN
		MIXIP_Wr01(gafe_acodec_1_bx, auad_gcon, 0x4);	//boost ADC gain : 2.4dB
		MIXIP_Wr01(gafe_acodec_1_bx, auad_ch_sel, ui8PortNum);
		MIXIP_WrFL(gafe_acodec_1_bx);

		//workaround for not working IP reset
		L9B0_ANALOG_WriteRegister(0x1D, 0x2D, 0x00);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_4_bx);
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auad, 0);
		MIXIP_WrFL(gsoft_reset_4_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gacodec_39_bx);
		MIXIP_Wr01(gacodec_39_bx, ladc_mute_ena, 0);
		MIXIP_WrFL(gacodec_39_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		//workaround for not working IP reset, add volume control to re-trigger
		L9B0_ANALOG_WriteRegister(0x1D, 0x2D, 0x01);	//Amplify ADC digital gain : 1.00 dB, 2011.11.08
	}
	else if(ui8PortNum == 6) //ui8PortNum 6 is defined for mute for HDMI /DVI is not connectted.
	{
		MIXIP_RdFL(gacodec_39_bx);
		MIXIP_Wr01(gacodec_39_bx, ladc_mute_ena, 1);
		MIXIP_WrFL(gacodec_39_bx);
	}
#ifdef ENABLE_SCART1_MIC_PORT
	else if(ui8PortNum == 7)
	{
		MIXIP_RdFL(gacodec_47_bx);
		MIXIP_Wr01(gacodec_47_bx, mute_ena_mic, 0);
		MIXIP_WrFL(gacodec_47_bx);
	}
#endif	//#ifdef ENABLE_SCART1_MIC_PORT
	else
	{
		AUD_KDRV_ERROR("L9B0_MIXED_IP_ADEC_L9_SetADCPortNumber : ADC Port = %d(Not Supported.)\n", ui8PortNum);
	}

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetADCPortNumber : ADC Port = %d\n", ui8PortNum);
	AUD_KDRV_ERROR("SetADCPortNumber : ADC Port = %d\n", ui8PortNum);
	return RET_OK;
}

/**
 * Sets the volume of DAC output.
 * @see ADEC_L9_SetDACOutVolume
*/
int L9B0_MIXED_IP_ADEC_L9_SetDACOutVolume ( LX_AUD_DAC_VOL_T stDACOutVol )
{
	UINT8	dac0MuteEnable = 0;
	UINT16	dac0_vol_con_1 = 0, dac1_vol_con_1 = 0;

	//L9 B0 Support Function : DAC0 -> SCART, DAC1 -> HPDRV
	//Set a SCART DAC volume for NICAM : Boost
	if ( stDACOutVol.mode & LX_AUD_DAC_SCART )
	{
		//Save gScartBoostSetted
		gScartBoostGain_L9B0 = stDACOutVol.scartGain;

		//Check a current mute status
		MIXIP_RdFL(gacodec_9_bx);
		MIXIP_Rd01(gacodec_9_bx, dac0_mute_ena, dac0MuteEnable);
		if(dac0MuteEnable == 0)
		{
			MIXIP_Wr01(gacodec_9_bx, dac0_mute_ena, 1);		// 1 bit : Line DAC CH0 Mute Control
			MIXIP_WrFL(gacodec_9_bx);

			/* To protect pop-noise */
			msleep_interruptible(MIXEDIP_MUTE_DELAY_30MS);	//30ms
		}

		MIXIP_RdFL(gacodec_3_bx);
		MIXIP_Rd01(gacodec_3_bx, dac0_vol_con_1, dac0_vol_con_1);
		dac0_vol_con_1 &= 0x03;							// 2 bit : Line DAC CH0 Volume Control
		dac0_vol_con_1 |= (UINT8)(stDACOutVol.scartGain << 2);	// 4 bit : Line DAC CH0 Volume Control
		MIXIP_Wr01(gacodec_3_bx, dac0_vol_con_1, dac0_vol_con_1);
		MIXIP_WrFL(gacodec_3_bx);

		if(dac0MuteEnable == 0)
		{
			MIXIP_RdFL(gacodec_9_bx);
			MIXIP_Wr01(gacodec_9_bx, dac0_mute_ena, 0);	// 1 bit : Line DAC CH0 Mute Control
			MIXIP_WrFL(gacodec_9_bx);
		}

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : SCART Gain = %d(dac0 = 0x%X)\n", stDACOutVol.scartGain, stDACOutVol.scartGain);

#ifdef ENABLE_MUTE_DEBUG
		AUD_KDRV_ERROR("SCART Gain = %d\n", gScartBoostGain_L9B0);
#endif

		return RET_OK;
	}

	//Set a SCART DAC volume : Attunuation
	if ( stDACOutVol.portNum & LX_AUD_OUTPUT_DAC0 )
	{
		//Check Mute case if volume is 0x3FF
		if(stDACOutVol.hwVolume == 0x3FF)
		{
			MIXIP_RdFL(gacodec_4_bx);
			MIXIP_Wr01(gacodec_4_bx, dac0_vol_con_0, (UINT8)(stDACOutVol.hwVolume & 0xFF));	// 8 bit : Line DAC CH0 Volume Control
			MIXIP_WrFL(gacodec_4_bx);

			MIXIP_RdFL(gacodec_3_bx);
			dac0_vol_con_1  = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH0 Volume Control
			dac0_vol_con_1 |= (gScartBoostGain_L9B0 << 2);	// 4 bit : Line DAC CH0 Volume Control
			MIXIP_Wr01(gacodec_3_bx, dac0_vol_con_1, dac0_vol_con_1);
			MIXIP_WrFL(gacodec_3_bx);
		}
		else
		{
			MIXIP_RdFL(gacodec_4_bx);
			MIXIP_Wr01(gacodec_4_bx, dac0_vol_con_0, (UINT8)(stDACOutVol.hwVolume & 0xFF));	// 8 bit : Line DAC CH0 Volume Control
			MIXIP_WrFL(gacodec_4_bx);

			//Check gScartBoostGain_L9B0 value
			if(gScartBoostGain_L9B0)
			{
				MIXIP_RdFL(gacodec_3_bx);
				dac0_vol_con_1  = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH0 Volume Control
				dac0_vol_con_1 |= (gScartBoostGain_L9B0 << 2);	// 4 bit : Line DAC CH0 Volume Control
				MIXIP_Wr01(gacodec_3_bx, dac0_vol_con_1, dac0_vol_con_1);
				MIXIP_WrFL(gacodec_3_bx);
			}
			else
			{
				MIXIP_RdFL(gacodec_3_bx);
				dac0_vol_con_1  = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH0 Volume Control
				MIXIP_Wr01(gacodec_3_bx, dac0_vol_con_1, dac0_vol_con_1);
				MIXIP_WrFL(gacodec_3_bx);
			}
		}

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : SCART(dac0_0 = 0x%X, dac0_1 = 0x%X)\n", stDACOutVol.hwVolume, stDACOutVol.hwVolume >> 8);
	}

	//Set a HeadPhone DAC volume
	if ( stDACOutVol.portNum & LX_AUD_OUTPUT_DAC2 )
	{
		MIXIP_RdFL(gacodec_13_bx);
		MIXIP_Wr01(gacodec_13_bx, dac1_vol_con_0, (UINT8)(stDACOutVol.hwVolume & 0xFF));	// 8 bit : Line DAC CH1 Volume Control
		MIXIP_WrFL(gacodec_13_bx);

		MIXIP_RdFL(gacodec_12_bx);
		dac1_vol_con_1 = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH1 Volume Control
		MIXIP_Wr01(gacodec_12_bx, dac1_vol_con_1, dac1_vol_con_1);
		MIXIP_WrFL(gacodec_12_bx);

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : HPDRV(dac1_0 = 0x%X, dac1_1 = 0x%X)\n", stDACOutVol.hwVolume, stDACOutVol.hwVolume >> 8);
	}

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetDACOutVolume : Port = %d, Volume = 0x%X\n", stDACOutVol.portNum, stDACOutVol.hwVolume);
	return RET_OK;
}

/**
 * Sets the mute of DAC output.
 * @see ADEC_L9_SetOutputPortMute
*/
int L9B0_MIXED_IP_ADEC_L9_SetDACOutMute ( LX_AUD_OUTPUT_PORT_MUTE_T stOutPortMute )
{
	//L9 B0 Support Function : DAC0 -> SCART, DAC1 -> HPDRV

	//Set a SCART DAC Reset
	if ( stOutPortMute.mode & LX_AUD_DAC_SCART_RESET )
	{
		MIXIP_RdFL(gsoft_reset_18_bx);
		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk0, 1);	//audio codec : dac 0
		MIXIP_WrFL(gsoft_reset_18_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_4_bx);
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk0, 1);	//audio codec : dac 0
		MIXIP_WrFL(gsoft_reset_4_bx);

		//add delay for clock setting
		udelay(MIXEDIP_RESET_DELAY_100US * 2);

		MIXIP_RdFL(gsoft_reset_4_bx);
		MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk0, 0);	//audio codec : dac 0,
		MIXIP_WrFL(gsoft_reset_4_bx);

		udelay(MIXEDIP_RESET_DELAY_100US);

		MIXIP_RdFL(gsoft_reset_18_bx);
		MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk0, 0);	//audio codec : dac 0
		MIXIP_WrFL(gsoft_reset_18_bx);

		AUD_KDRV_MIP_DEBUG("SCART : Reset\n");

		return RET_OK;
	}

	//Set a SCART DAC mute
	if ( stOutPortMute.portNum & LX_AUD_OUTPUT_DAC0 )
	{
		if( stOutPortMute.bHwOnOff == TRUE )
		{
			MIXIP_RdFL(gacodec_9_bx);
			MIXIP_Wr01(gacodec_9_bx, dac0_mute_ena, 1);		// 1 bit : Line DAC CH0 Mute Control
			MIXIP_WrFL(gacodec_9_bx);

			AUD_KDRV_MIP_DEBUG("SCART : Mute On\n");

#ifdef ENABLE_MUTE_DEBUG
			AUD_KDRV_ERROR("SCART : Mute On\n");
#endif
		}
		else	//un-mute
		{
			MIXIP_RdFL(gacodec_9_bx);
			MIXIP_Wr01(gacodec_9_bx, dac0_mute_ena, 0);		// 1 bit : Line DAC CH0 Mute Control
			MIXIP_WrFL(gacodec_9_bx);

			AUD_KDRV_MIP_DEBUG("SCART : Mute Off\n");

#ifdef ENABLE_MUTE_DEBUG
			AUD_KDRV_ERROR("SCART : Mute Off\n");
#endif
		}
	}

	//Set a HeadPhone DAC mute : *** Not Used in L9 B0 ***
	if ( stOutPortMute.portNum & LX_AUD_OUTPUT_DAC2 )
	{
		//mute
		if( stOutPortMute.bHwOnOff == TRUE )
		{
			MIXIP_RdFL(gacodec_18_bx);
			MIXIP_Wr01(gacodec_18_bx, dac1_mute_ena, 1);	// 1 bit : Line DAC CH1 Mute Control
			MIXIP_WrFL(gacodec_18_bx);

			msleep_interruptible(MIXEDIP_MUTE_DELAY_30MS);

			MIXIP_RdFL(gsoft_reset_18_bx);
			MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk1, 1);	//audio codec : dac 1
			MIXIP_WrFL(gsoft_reset_18_bx);

			MIXIP_RdFL(gsoft_reset_4_bx);
			MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 1);	//audio codec : dac 1
			MIXIP_WrFL(gsoft_reset_4_bx);

			//add delay for clock setting
			udelay(MIXEDIP_RESET_DELAY_100US * 2);

			AUD_KDRV_MIP_DEBUG("HPDRV : Mute On\n");

#ifdef ENABLE_MUTE_DEBUG
			AUD_KDRV_ERROR("HPDRV : Mute On\n");
#endif
		}
		else	//un-mute
		{
			MIXIP_RdFL(gsoft_reset_4_bx);
			MIXIP_Wr01(gsoft_reset_4_bx, swrst_auda_mclk1, 0);	//audio codec : dac 1
			MIXIP_WrFL(gsoft_reset_4_bx);

			MIXIP_RdFL(gsoft_reset_18_bx);
			MIXIP_Wr01(gsoft_reset_18_bx, swrst_auda_f256fs_clk1, 0);	//audio codec : dac 1
			MIXIP_WrFL(gsoft_reset_18_bx);

			msleep_interruptible(MIXEDIP_MUTE_DELAY_30MS);

			MIXIP_RdFL(gacodec_18_bx);
			MIXIP_Wr01(gacodec_18_bx, dac1_mute_ena, 0);	// 1 bit : Line DAC CH1 Mute Control
			MIXIP_WrFL(gacodec_18_bx);

			AUD_KDRV_MIP_DEBUG("HPDRV : Mute Off\n");

#ifdef ENABLE_MUTE_DEBUG
			AUD_KDRV_ERROR("HPDRV : Mute Off\n");
#endif
		}
	}

	AUD_KDRV_MIP_DEBUG("L9B0_MIXED_IP_ADEC_L9_SetDACOutMute : Port = %d, mute = 0x%X\n", stOutPortMute.portNum, stOutPortMute.bHwOnOff);
	return RET_OK;
}


/** @} */




