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
 *  @date		2012.05.01
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
#include "audio_imc_func.h"

#include "debug_util.h"
#include "mixedIP_drv_h13_a0.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* SPDIF Sampling Clock frequency Number : 48, 44.1, 32Khz */
#define SPDIF_DTO_REG_NUMBER		9

/* SPDIF DTO Clock frequency and Rate Table */
static const UINT32 g_AUD_SpdifDtoTable[SPDIF_ES_OUT_FREQ_NUMBER][LX_AUD_SPDIF_DTO_RATE_NUMBER][SPDIF_DTO_REG_NUMBER] =
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
extern LX_AUD_KDRV_T g_AudKdrv;


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
static LX_AUD_POWER_STATUS_T gADECPowerStatus_H13A0[LX_AUD_POWER_MAX] = {	\
							  {LX_AUD_POWER_AAD, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_ADC, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_HPDRV, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_DAC, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_MIC, 	LX_AUD_POWER_UP} };
#endif

//Current SCART Boost Gain Setting
static UINT16 gScartBoostGain_H13A0 = 0;

//Current ADEC Clock Source Setting
static LX_AUD_CLOCK_SRC_T gAdecClockSource_H13A0 = LX_AUD_CLOCK_UNKNOWN;

//Current AAD Bypass Enabled
static BOOLEAN gAadBypassEnabled_H13A0 = FALSE;

//Current SRC Input Sampling Frequency Setting
static LX_AUD_SAMPLING_FREQ_T gAdecSrcFreq_H13A0 = LX_AUD_SAMPLING_FREQ_NONE;

//Current SPDIF Sampling Frequency Setting
static LX_AUD_SAMPLING_FREQ_T gAdecSpdifFreq_H13A0 = LX_AUD_SAMPLING_FREQ_NONE;

//Current PCM clock Rate Setting
static UINT32 	gAdecPcmClock_H13A0 = APLL_DSP_VALUE_12_288MHZ;	//18,000

//Current SPDIF DTO Rate Setting
static LX_AUD_SPDIF_DTO_RATE_T gAdecSpdifDtoRate_H13A0 = LX_AUD_SPDIF_DTO_UNKNOWN;


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 *  H13A0_ANALOG_ReadRegister
 *
 *  @parm UINT32 *
 *  @return int
*/
int H13A0_ANALOG_ReadRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 *value)
{
	int 	ret = RET_OK;

	//Read I2C register
	ret = (UINT8)ACE_RegRead(slaveAddr << 1, regAddr, value);

//	AUD_KDRV_MIP_I2C("H13 A0 Read  : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", slaveAddr, regAddr, *value);
//	AUD_KDRV_ERROR("H13 A0 Read  : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", slaveAddr, regAddr, *value);

	return ret;
}

/**
 *  H13A0_ANALOG_WriteRegister
 *
 *  @parm UINT32 *
 *  @return int
*/
int H13A0_ANALOG_WriteRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 value)
{
	int 	ret = RET_OK;

	//Write I2C register
	(void)ACE_RegWrite(slaveAddr << 1, regAddr, value);

	AUD_KDRV_MIP_I2C("H13 A0 Write : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", slaveAddr, regAddr, value);

	return ret;
}


/**
 * Initializes the clock and reset module register value.
 * @see ADEC_Init
*/
int H13A0_MIXED_IP_ADEC_InitClockRegisters( void )
{
	//Initialize clock registers.
	//clock setting for APLL block
	ACE_REG_H13A0_RdFL(audio_pll_0);
	ACE_REG_H13A0_Wr01(audio_pll_0, apll_lpfon, 3);		// LPF cutoff freq. control pin (Default : 01) (00: Fcutoff = 24 Mhz, 01 : Fcutoff = 15.2Mhz, 11:Fcutoff = 8.8Mhz
	ACE_REG_H13A0_Wr01(audio_pll_0, apll_m, 	2);		// Value of forward divider(low for Audio PLL application)
	ACE_REG_H13A0_Wr01(audio_pll_0, apll_od, 	3);		// Value of output divider(low for Audio PLL application)
	ACE_REG_H13A0_Wr01(audio_pll_0, apll_sel, 	0);		// VCO & LPF reset pin (default : L)
	ACE_REG_H13A0_Wr01(audio_pll_0, apll_pdb, 	1);		// 0 :power down, 1 : normal operation,  Analog & digital block power down pin
	ACE_REG_H13A0_WrFL(audio_pll_0);

	ACE_REG_H13A0_RdFL(audio_pll_1);
	ACE_REG_H13A0_Wr01(audio_pll_1, apll_fcw_2,	0x04);	// Frequency control word (Fin: 162MHz, Fout: 18.432MHz)
	ACE_REG_H13A0_WrFL(audio_pll_1);

	ACE_REG_H13A0_RdFL(audio_pll_2);
	ACE_REG_H13A0_Wr01(audio_pll_2, apll_fcw_1,	0x65);
	ACE_REG_H13A0_WrFL(audio_pll_2);

	ACE_REG_H13A0_RdFL(audio_pll_3);
	ACE_REG_H13A0_Wr01(audio_pll_3, apll_fcw_0,	0x00);
	ACE_REG_H13A0_WrFL(audio_pll_3);

	ACE_REG_H13A0_RdFL(audio_pll_4);
	ACE_REG_H13A0_Wr01(audio_pll_4, apll_ci,	0x01);	//Icp Control for CP
	ACE_REG_H13A0_Wr01(audio_pll_4, apll_cvl,	0x00);	//VCO Lower Limit Control
	ACE_REG_H13A0_Wr01(audio_pll_4, apll_cvs,	0x00);	//VCO Upper Limit Control
	ACE_REG_H13A0_WrFL(audio_pll_4);

	//clock setting for aad/btsc block
	ACE_REG_H13A0_RdFL(afe_aad_7);
	ACE_REG_H13A0_Wr01(afe_aad_7, aad_adc_selref, 3);
	ACE_REG_H13A0_Wr01(afe_aad_7, aad_adc_pdb, 	  1);	// 0 :power down, 1 : normal operation
	ACE_REG_H13A0_Wr01(afe_aad_7, aad_dco_rtest,  1);
	ACE_REG_H13A0_Wr01(afe_aad_7, aad_dco_resetb, 1);	// 0 :power down, 1 : normal operation
	ACE_REG_H13A0_WrFL(afe_aad_7);

	//clock DCO value setting for aad/btsc block
	ACE_REG_H13A0_RdFL(afe_aad_8);
	ACE_REG_H13A0_Wr01(afe_aad_8,  aad_dco_fcw_2, 0x0E);
	ACE_REG_H13A0_WrFL(afe_aad_8);

	ACE_REG_H13A0_RdFL(afe_aad_9);
	ACE_REG_H13A0_Wr01(afe_aad_9,  aad_dco_fcw_1, 0x90);
	ACE_REG_H13A0_WrFL(afe_aad_9);

	ACE_REG_H13A0_RdFL(afe_aad_10);
	ACE_REG_H13A0_Wr01(afe_aad_10, aad_dco_fcw_0, 0x45);
	ACE_REG_H13A0_WrFL(afe_aad_10);

	//clock SPLL value setting for aad/btsc block
	ACE_REG_H13A0_RdFL(afe_aad_14);
	ACE_REG_H13A0_Wr01(afe_aad_14, aad_spll_cvl, 	 2);
	ACE_REG_H13A0_Wr01(afe_aad_14, aad_spll_cvs, 	 2);
	ACE_REG_H13A0_Wr01(afe_aad_14, aad_spll_sel, 	 0);
	ACE_REG_H13A0_Wr01(afe_aad_14, aad_spll_pdb, 	 1);	// 0 :power down, 1 : normal operation
	ACE_REG_H13A0_Wr01(afe_aad_14, aad_spllclk_test, 0);
	ACE_REG_H13A0_WrFL(afe_aad_14);

	//clock divide value setting for aad/btsc block
	ACE_REG_H13A0_RdFL(afe_aad_15);
	ACE_REG_H13A0_Wr01(afe_aad_15, aad_adcclk_test, 0);
	ACE_REG_H13A0_Wr01(afe_aad_15, aad_fs00clk_sel, 0);
	ACE_REG_H13A0_Wr01(afe_aad_15, aad_fs01clk_sel, 0);
	ACE_REG_H13A0_Wr01(afe_aad_15, aad_fs02clk_sel, 0);
	ACE_REG_H13A0_WrFL(afe_aad_15);

	//delay before sw reset control
	udelay(MIXEDIP_RESET_DELAY_100US);

	//sw reset setting for mixed-IP block
	ACE_REG_H13A0_RdFL(soft_reset_1);
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk0, 0);	//audio codec : dac0
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 0);	//audio codec : dac1
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auad, 0);
	ACE_REG_H13A0_WrFL(soft_reset_1);

	ACE_REG_H13A0_RdFL(soft_reset_2);
	ACE_REG_H13A0_Wr01(soft_reset_2, swrst_fs00, 0);
	ACE_REG_H13A0_WrFL(soft_reset_2);

	ACE_REG_H13A0_RdFL(soft_reset_4);
	ACE_REG_H13A0_Wr01(soft_reset_4, swrst_adto, 0);
	ACE_REG_H13A0_Wr01(soft_reset_4, swrst_aclk_mux2, 0);
	ACE_REG_H13A0_WrFL(soft_reset_4);

	ACE_REG_H13A0_RdFL(soft_reset_5);
//	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs25clk, 0);		//SRC output I2S clock
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs24clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs23clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs21clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs20clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_audclk_out,  0);		//D-AMP I2S clock
//	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_audclk_out_sub, 0);		//dac sub I2S clock
	ACE_REG_H13A0_WrFL(soft_reset_5);

	ACE_REG_H13A0_RdFL(soft_reset_14);
	ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk0, 0);
	ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 0);
	ACE_REG_H13A0_WrFL(soft_reset_14);

	//Fix AAD_AFE data output setup time error : change fs00_clk_out inversion : 2011.10.27
	ACE_REG_H13A0_RdFL(clock_control_2);
	ACE_REG_H13A0_Wr01(clock_control_2, fs00_clk, 1);
	ACE_REG_H13A0_WrFL(clock_control_2);

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_InitClockRegisters\n");
	return RET_OK;
}

/**
 * Resets the clock register value.
 * @see ADEC_Init
*/
int H13A0_MIXED_IP_ADEC_ResetClockRegisters( void )
{
	//sw reset setting for mixed-IP block
	ACE_REG_H13A0_RdFL(soft_reset_1);
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk0, 1);	//audio codec : dac0
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 1);	//audio codec : dac1
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auad, 1);
	ACE_REG_H13A0_WrFL(soft_reset_1);

	ACE_REG_H13A0_RdFL(soft_reset_2);
	ACE_REG_H13A0_Wr01(soft_reset_2, swrst_fs00, 1);
	ACE_REG_H13A0_WrFL(soft_reset_2);

	ACE_REG_H13A0_RdFL(soft_reset_4);
	ACE_REG_H13A0_Wr01(soft_reset_4, swrst_adto, 1);
	ACE_REG_H13A0_Wr01(soft_reset_4, swrst_aclk_mux2, 1);
	ACE_REG_H13A0_WrFL(soft_reset_4);

	ACE_REG_H13A0_RdFL(soft_reset_5);
//	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs25clk, 1); 	//SRC output I2S clock
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs24clk, 1);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs23clk, 1);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs21clk, 1);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs20clk, 1);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_audclk_out,	1); 	//D-AMP I2S clock
//	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_audclk_out_sub, 1);		//dac sub I2S clock
	ACE_REG_H13A0_WrFL(soft_reset_5);

	ACE_REG_H13A0_RdFL(soft_reset_14);
	ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk0, 1);
	ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 1);
	ACE_REG_H13A0_WrFL(soft_reset_14);

	//add delay for clock setting
	udelay(MIXEDIP_RESET_DELAY_100US * 2);

	//sw reset setting for mixed-IP block
	ACE_REG_H13A0_RdFL(soft_reset_1);
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk0, 0);	//audio codec : dac0
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 0);	//audio codec : dac1
	ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auad, 0);
	ACE_REG_H13A0_WrFL(soft_reset_1);

	ACE_REG_H13A0_RdFL(soft_reset_2);
	ACE_REG_H13A0_Wr01(soft_reset_2, swrst_fs00, 0);
	ACE_REG_H13A0_WrFL(soft_reset_2);

	ACE_REG_H13A0_RdFL(soft_reset_4);
	ACE_REG_H13A0_Wr01(soft_reset_4, swrst_adto, 0);
	ACE_REG_H13A0_Wr01(soft_reset_4, swrst_aclk_mux2, 0);
	ACE_REG_H13A0_WrFL(soft_reset_4);

	ACE_REG_H13A0_RdFL(soft_reset_5);
//	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs25clk, 0); 	//SRC output I2S clock
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs24clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs23clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs21clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs20clk, 0);
	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_audclk_out,	0); 	//D-AMP I2S clock
//	ACE_REG_H13A0_Wr01(soft_reset_5, swrst_audclk_out_sub, 0);		//dac sub I2S clock
	ACE_REG_H13A0_WrFL(soft_reset_5);

	ACE_REG_H13A0_RdFL(soft_reset_14);
	ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk0, 0);
	ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 0);
	ACE_REG_H13A0_WrFL(soft_reset_14);

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_ResetClockRegisters\n");
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_DRV_InitModule
*/
int H13A0_MIXED_IP_ADEC_SetClockSource( LX_AUD_SAMPLING_FREQ_T ui32SrcFreq, LX_AUD_CLOCK_SRC_T ui8AdecClockSrc )
{
	BOOLEAN bAadBypassEnabled = FALSE;

#if 0
	ADEC_SET_PCM_INTERRUPT_T	pcmRate;
#endif
	DtoCtrlCmdSetDtorate		setDtoRate;

	//Check previous clock source
	if(gAdecSrcFreq_H13A0 == ui32SrcFreq && gAdecClockSource_H13A0 == ui8AdecClockSrc)
	{
		AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetClockSource : same freq = %d, src = %d\n", ui32SrcFreq, ui8AdecClockSrc);
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
	if(bAadBypassEnabled == FALSE || gAadBypassEnabled_H13A0 != bAadBypassEnabled)
	{
		ACE_REG_H13A0_RdFL(acodec_20);
		ACE_REG_H13A0_Wr01(acodec_20, dac0_mute_ena, 1);		// 1 bit : Line DAC CH0 Mute Control
		ACE_REG_H13A0_WrFL(acodec_20);

		ACE_REG_H13A0_RdFL(acodec_29);
		ACE_REG_H13A0_Wr01(acodec_29, dac1_mute_ena, 1);	// 1 bit : Line DAC CH1 Mute Control
		ACE_REG_H13A0_WrFL(acodec_29);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

		ACE_REG_H13A0_RdFL(soft_reset_14);
		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk0, 1);	//audio codec : dac 0
		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 1);	//audio codec : dac 1
		ACE_REG_H13A0_WrFL(soft_reset_14);

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_1);
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk0, 1);	//audio codec : dac0
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 1);	//audio codec : dac1
		ACE_REG_H13A0_WrFL(soft_reset_1);

		ACE_REG_H13A0_RdFL(soft_reset_5);
		ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs20clk, 1);	//hpdrv, clock change only
		ACE_REG_H13A0_WrFL(soft_reset_5);
	}
	else	//SCART port is not reset.
	{
		ACE_REG_H13A0_RdFL(acodec_29);
		ACE_REG_H13A0_Wr01(acodec_29, dac1_mute_ena, 1);	// 1 bit : Line DAC CH1 Mute Control
		ACE_REG_H13A0_WrFL(acodec_29);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

		ACE_REG_H13A0_RdFL(soft_reset_14);
		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 1);	//audio codec : dac 1
		ACE_REG_H13A0_WrFL(soft_reset_14);

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_1);
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 1);	//audio codec : dac1
		ACE_REG_H13A0_WrFL(soft_reset_1);

		ACE_REG_H13A0_RdFL(soft_reset_5);
		ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs20clk, 1);	//hpdrv, clock change only
		ACE_REG_H13A0_WrFL(soft_reset_5);
	}

	//add delay for clock setting
	udelay(MIXEDIP_RESET_DELAY_100US * 2);

	//Set default PCM frequency to 48Khz and notify input sampling frequency to DSP
	(void)H13A0_MIXED_IP_ADEC_SetPcmClockRate(ui32SrcFreq, APLL_DSP_VALUE_12_288MHZ);

	//Set default SPDIF sampling frequency to 48Khz
	(void)H13A0_MIXED_IP_ADEC_SetSPDIFSamplingFreq(LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_SPDIF_DTO_NORMAL);

	//Setting Audio Clock Mux
	//Read clock mux reg.
	ACE_REG_H13A0_RdFL(soft_reset_6);
	ACE_REG_H13A0_RdFL(soft_reset_7);
	ACE_REG_H13A0_RdFL(soft_reset_8);
	ACE_REG_H13A0_RdFL(soft_reset_9);
	ACE_REG_H13A0_RdFL(soft_reset_10);
	ACE_REG_H13A0_RdFL(soft_reset_11);
	ACE_REG_H13A0_RdFL(soft_reset_12);
	ACE_REG_H13A0_RdFL(soft_reset_13);
	ACE_REG_H13A0_RdFL(soft_reset_14);
	ACE_REG_H13A0_RdFL(soft_reset_15);

	if( (ui8AdecClockSrc == LX_AUD_CLOCK_DTV)		//DTV to SPK(default)
      ||(ui8AdecClockSrc == LX_AUD_CLOCK_ADC) ) 	//ADC to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("LX_AUD_CLOCK_DTV\n");

		ACE_REG_H13A0_Wr01(soft_reset_6,  aclk_mux1_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_7,  aclk_mux1_div,  0);
		ACE_REG_H13A0_Wr01(soft_reset_7,  aclk_mux2_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_8,  aclk_mux2_div,  0);

		ACE_REG_H13A0_Wr01(soft_reset_8,  aclk_mux3_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_9,  aclk_mux3_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_9,  aclk_mux4_src,  2);
		ACE_REG_H13A0_Wr01(soft_reset_10, aclk_mux4_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_10, aclk_mux5_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_11, aclk_mux5_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_11, aclk_mux6_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_12, aclk_mux6_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_12, aclk_mux7_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux7_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux8_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux8_div,  1);

		if( ui8AdecClockSrc == LX_AUD_CLOCK_DTV )	//DTV to SPK(default)
		{
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_src,  1);
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_div,  0);
			ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_src, 1);
			ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_div, 0);
		}
   		else	//( ui8AdecClockSrc == LX_AUD_CLOCK_ADC ) //ADC to SPK, SCART AAD bypass
		{
			//Check a H13 chip revision by chip bug
			if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
			{
				//Enable SCART bypass function
				ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_src,  0);
				ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_div,  1);
			}
			else
			{
				//Disable SCART bypass function
				ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_src,  1);
				ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_div,  0);
			}
			ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_src, 1);
			ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_div, 0);
		}
	}
	else if(ui8AdecClockSrc == LX_AUD_CLOCK_HDMI) //HDMI to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("LX_AUD_CLOCK_HDMI\n");

		ACE_REG_H13A0_Wr01(soft_reset_6,  aclk_mux1_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_7,  aclk_mux1_div,  0);
		ACE_REG_H13A0_Wr01(soft_reset_7,  aclk_mux2_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_8,  aclk_mux2_div,  0);

		ACE_REG_H13A0_Wr01(soft_reset_8,  aclk_mux3_src,  1);	//Fs21 : APLL
		ACE_REG_H13A0_Wr01(soft_reset_9,  aclk_mux3_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_9,  aclk_mux4_src,  2);	//Fs22 : DTO
		ACE_REG_H13A0_Wr01(soft_reset_10, aclk_mux4_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_10, aclk_mux5_src,  3);	//Fs23 : HDMI Link0 ACR
		ACE_REG_H13A0_Wr01(soft_reset_11, aclk_mux5_div,  0);
		ACE_REG_H13A0_Wr01(soft_reset_11, aclk_mux6_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_12, aclk_mux6_div,  0);
		ACE_REG_H13A0_Wr01(soft_reset_12, aclk_mux7_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux7_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux8_src,  1);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux8_div,  1);

		//Check a H13 chip revision by chip bug
		if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
		{
			//Enable SCART bypass function
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_src,  0);
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_div,  1);
		}
		else
		{
			//Disable SCART bypass function
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_src,  1);
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_div,  0);
		}

		ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_src, 1);
		ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_div, 0);
	}
	else if( ui8AdecClockSrc == LX_AUD_CLOCK_ATV ) //Analog TV to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("LX_AUD_CLOCK_ATV\n");

		ACE_REG_H13A0_Wr01(soft_reset_6,  aclk_mux1_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_7,  aclk_mux1_div,  1);
		ACE_REG_H13A0_Wr01(soft_reset_7,  aclk_mux2_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_8,  aclk_mux2_div,  1);

		ACE_REG_H13A0_Wr01(soft_reset_8,  aclk_mux3_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_9,  aclk_mux3_div,  2);
		ACE_REG_H13A0_Wr01(soft_reset_9,  aclk_mux4_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_10, aclk_mux4_div,  2);
		ACE_REG_H13A0_Wr01(soft_reset_10, aclk_mux5_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_11, aclk_mux5_div,  2);
		ACE_REG_H13A0_Wr01(soft_reset_11, aclk_mux6_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_12, aclk_mux6_div,  2);
		ACE_REG_H13A0_Wr01(soft_reset_12, aclk_mux7_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux7_div,  2);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux8_src,  0);
		ACE_REG_H13A0_Wr01(soft_reset_13, aclk_mux8_div,  2);

		//Check a H13 chip revision by chip bug
		if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
		{
			//Enable SCART bypass function
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_src,  0);
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_div,  1);
		}
		else
		{
			//Disable SCART bypass function
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_src,  1);
			ACE_REG_H13A0_Wr01(soft_reset_14, aclk_mux9_div,  0);
		}

		ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_src, 0);
		ACE_REG_H13A0_Wr01(soft_reset_15, aclk_mux10_div, 1);
	}
	else
	{
		AUD_KDRV_ERROR("H13A0_MIXED_IP_ADEC_SetClockSource : 0x%X(Not Supported!!!)\n", ui8AdecClockSrc);
		return RET_ERROR;
	}

	//Write clock mux reg.
	ACE_REG_H13A0_WrFL(soft_reset_6);
	ACE_REG_H13A0_WrFL(soft_reset_7);
	ACE_REG_H13A0_WrFL(soft_reset_8);
	ACE_REG_H13A0_WrFL(soft_reset_9);
	ACE_REG_H13A0_WrFL(soft_reset_10);
	ACE_REG_H13A0_WrFL(soft_reset_11);
	ACE_REG_H13A0_WrFL(soft_reset_12);
	ACE_REG_H13A0_WrFL(soft_reset_13);
	ACE_REG_H13A0_WrFL(soft_reset_14);
	ACE_REG_H13A0_WrFL(soft_reset_15);

	//add delay for clock setting
	udelay(MIXEDIP_RESET_DELAY_100US * 2);

	//Reset off for Mixed IP Module
	if(bAadBypassEnabled == FALSE || gAadBypassEnabled_H13A0 != bAadBypassEnabled)
	{
		//Wait for SCART & HP reset
		ACE_REG_H13A0_RdFL(soft_reset_5);
		ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs20clk, 0);	//hpdrv
		ACE_REG_H13A0_WrFL(soft_reset_5);

		ACE_REG_H13A0_RdFL(soft_reset_1);
//		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk0, 0);	//audio IP reset : dac 0,
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 0);	//audio IP reset : dac 1
		ACE_REG_H13A0_WrFL(soft_reset_1);

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_14);
//		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk0, 0);	//bclk reset : dac 0
		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 0);	//bclk reset : dac 1
		ACE_REG_H13A0_WrFL(soft_reset_14);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

//		ACE_REG_H13A0_RdFL(acodec_20);
//		ACE_REG_H13A0_Wr01(acodec_20, dac0_mute_ena, 0);		// 1 bit : Line DAC CH0 Mute Control
//		ACE_REG_H13A0_WrFL(acodec_20);

		ACE_REG_H13A0_RdFL(acodec_29);
		ACE_REG_H13A0_Wr01(acodec_29, dac1_mute_ena, 0);	// 1 bit : Line DAC CH1 Mute Control
		ACE_REG_H13A0_WrFL(acodec_29);
	}
	else	//SCART port is not reset.
	{
		//Wait for SCART & HP reset
		ACE_REG_H13A0_RdFL(soft_reset_5);
		ACE_REG_H13A0_Wr01(soft_reset_5, swrst_aud_fs20clk, 0);	//hpdrv, clock change only
		ACE_REG_H13A0_WrFL(soft_reset_5);

		ACE_REG_H13A0_RdFL(soft_reset_1);
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 0);	//audio codec : dac 1
		ACE_REG_H13A0_WrFL(soft_reset_1);

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_14);
		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 0);	//audio codec : dac 1
		ACE_REG_H13A0_WrFL(soft_reset_14);

		msleep_interruptible(MIXEDIP_RESET_DELAY_10MS);

		ACE_REG_H13A0_RdFL(acodec_29);
		ACE_REG_H13A0_Wr01(acodec_29, dac1_mute_ena, 0);	// 1 bit : Line DAC CH1 Mute Control
		ACE_REG_H13A0_WrFL(acodec_29);
	}

#if 0
	//Send a IPC command for PCM clock setting
	if(g_adec_kdrv.bInitDone == TRUE)
	{
		//Clears a PCM Clock interrupt count
		pcmRate.ui32InFs		  = (UINT32)ui32SrcFreq;
		pcmRate.ui32PCMclkRate	  = (UINT32)APLL_DSP_VALUE_12_288MHZ;
		pcmRate.ui32ForceCntClear = (UINT32)1;

		ADEC_IPC_SetPCMRate(pcmRate);
	}
#endif

	//Send a IMC command for DTO setting to be changed clock source.
	if(g_AudKdrv.bInitDone == TRUE)
	{
		setDtoRate.dtorate			= (UINT32)LX_AUD_SPDIF_DTO_NORMAL;
		setDtoRate.force_cnt_clear	= (UINT32)1;
		AUDIO_IMC_SendCmdParam(DTOCTRL_CMD_SET_DTORATE, ADEC_MODULE_DTO_D, sizeof(DtoCtrlCmdSetDtorate), &setDtoRate);
	}

	//Save current SRC frequency
	gAdecSrcFreq_H13A0 = ui32SrcFreq;

	//Save current clock source
	gAdecClockSource_H13A0 = ui8AdecClockSrc;

	//Save current SCART bypass status
	gAadBypassEnabled_H13A0 = bAadBypassEnabled;

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetClockSource : %d\n", ui8AdecClockSrc);
	return RET_OK;
}

/**
 * Sets a PCM Clock frequency and Rate to sync with SPDIF clock for SPDIF output.
 * @see ADEC_L9_InitModule
 * APLL FCW default value for 12.288MHZ : low 4 bit and high 2 bit is ignored,
 * use 16 bit value and value and freq. is reversed.
 *  Fout = ((2^23 / FCW[21:0]) / (2^M[1:0] * 2^OD[1:0])) * Fin
 *
 *  Fin=27Mhz
 *  FCW[21:0]=288000, M[1:0]=2,  OD[1:0]=4
 *  Fout = ((2^23 / 288000) / (2^2 * 2^4)) * 27,000,000 = 12.288MHz  이고

 *  FCW[21:0]=329088 인 경우는 10.754MHz
 *  FCW[21:0]=256000 인 경우는 13.824MHz
*/
int H13A0_MIXED_IP_ADEC_SetPcmClockRate ( LX_AUD_SAMPLING_FREQ_T ui32SrcFreq, UINT32 ui32PcmClock )
{
	UINT32	ui32FCWValue = 0;

	//ADEC_SET_PCM_INTERRUPT_T 	 pcmRate;

	//Check a previous status.
	if(	gAdecSrcFreq_H13A0 == ui32SrcFreq && gAdecPcmClock_H13A0 == ui32PcmClock)
	{
		AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetPcmClockRate : same freq = %d, rate = %d\n", ui32SrcFreq, ui32PcmClock);
		return RET_OK;
	}

	//Change PCM clock to Audio PLL FCW value
	if(ui32PcmClock >= APLL_DSP_VALUE_12_288MHZ)
	{
		ui32FCWValue = APLL_CLK_FCW_VALUE_12_288MHZ - ((ui32PcmClock - APLL_DSP_VALUE_12_288MHZ) << 6);		//0x40(64)
	}
	else
	{
		ui32FCWValue = APLL_CLK_FCW_VALUE_12_288MHZ + ((APLL_DSP_VALUE_12_288MHZ - ui32PcmClock) << 6);		//0x40(64)
	}

	//Check a PCM clock rate for min and max value.
	if(ui32FCWValue > APLL_CLK_FCW_VALUE_10_754MHZ)
	{
		AUD_KDRV_ERROR("SetPcmClockRate : freq = %dHz, MIN rate = %d, fcw = %d\n", ui32SrcFreq, ui32PcmClock, ui32FCWValue);

		ui32FCWValue = APLL_CLK_FCW_VALUE_10_754MHZ;
	}
	else if(ui32FCWValue < APLL_CLK_FCW_VALUE_13_824MHZ)
	{
		AUD_KDRV_ERROR("SetPcmClockRate : freq = %dHz, MAX rate = %d, fcw = %d\n", ui32SrcFreq, ui32PcmClock, ui32FCWValue);

		ui32FCWValue = APLL_CLK_FCW_VALUE_13_824MHZ;
	}

	//Read a PCM Clock registers for audio PLL. Change apll_fcw_0 first(우 영신.2012.05.11)
	ACE_REG_H13A0_RdFL(audio_pll_3);
	ACE_REG_H13A0_RdFL(audio_pll_2);
	ACE_REG_H13A0_RdFL(audio_pll_1);

	//Set a FCW value.
	ACE_REG_H13A0_Wr01(audio_pll_3, apll_fcw_0, (ui32FCWValue >>  0) & 0xFF);
	ACE_REG_H13A0_Wr01(audio_pll_2, apll_fcw_1, (ui32FCWValue >>  8) & 0xFF);
	ACE_REG_H13A0_Wr01(audio_pll_1, apll_fcw_2, (ui32FCWValue >> 16) & 0x07);	//upper 3 bit is zero padding.

	//Write a APLL PCM Clock Value.
	ACE_REG_H13A0_WrFL(audio_pll_3);
	ACE_REG_H13A0_WrFL(audio_pll_2);
	ACE_REG_H13A0_WrFL(audio_pll_1);

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
	gAdecSrcFreq_H13A0  = ui32SrcFreq;

	//Save current PCM Clock Rate
	gAdecPcmClock_H13A0 = ui32PcmClock;

	//AUD_KDRV_ERROR("H13A0_MIXED_IP_ADEC_SetPcmClockRate      : freq = %dHz, rate = %d, fcw = %d(0x%X)\n", ui32SrcFreq, ui32PcmClock, ui32FCWValue, ui32FCWValue);

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetPcmClockRate      : freq = %dHz, rate = %d, fcw = %d\n", ui32SrcFreq, ui32PcmClock, ui32FCWValue);
	return RET_OK;

}


int H13A0_MIXED_IP_ADEC_SetSPDIFSamplingFreq ( LX_AUD_SAMPLING_FREQ_T ui32SamplingFreq, LX_AUD_SPDIF_DTO_RATE_T stSpdifDtoRate )
{
	UINT8	freqTableNum = 0;
	UINT8	rateTableNum = 0;

	DtoCtrlCmdSetDtorate		setDtoRate;

	//Check a previous status.
	if(	gAdecSpdifFreq_H13A0 == ui32SamplingFreq && gAdecSpdifDtoRate_H13A0 == stSpdifDtoRate)
	{
		AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetSPDIFSamplingFreq : same freq = %d_HZ, rate = %d\n",  ui32SamplingFreq, stSpdifDtoRate);
		return RET_OK;
	}

	//Read a SPDIF DTO registers.
	ACE_REG_H13A0_RdFL(audio_dto_0);
	ACE_REG_H13A0_RdFL(audio_dto_1);
	ACE_REG_H13A0_RdFL(audio_dto_2);
	ACE_REG_H13A0_RdFL(audio_dto_3);
	ACE_REG_H13A0_RdFL(audio_dto_4);
	ACE_REG_H13A0_RdFL(audio_dto_5);
	ACE_REG_H13A0_RdFL(audio_dto_6);
	ACE_REG_H13A0_RdFL(audio_dto_7);
	ACE_REG_H13A0_RdFL(audio_dto_8);

	if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_48_KHZ )
	{
		AUD_KDRV_PRINT("48_KHZ\n" );

		//Set a SPDIF DTO frequency table.
		freqTableNum = 0;

		//Set a SPDIF DTO Frequency for IPC
//		spdifDTO.ui32SampleFreq = LX_AUD_SAMPLING_FREQ_48_KHZ;
	}
	else if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_44_1KHZ )
	{
		AUD_KDRV_PRINT("44_1KHZ\n" );

		//Set a SPDIF DTO frequency table.
		freqTableNum = 1;

		//Set a SPDIF DTO Frequency for IPC
//		spdifDTO.ui32SampleFreq = LX_AUD_SAMPLING_FREQ_44_1KHZ;
	}
	else if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_32_KHZ )
	{
		AUD_KDRV_PRINT("32_KHZ\n" );

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
		AUD_KDRV_ERROR("SetSPDIFSamplingFreq : freq = %dHz, MIN rate = %d\n", ui32SamplingFreq, stSpdifDtoRate);

		rateTableNum = LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES - 1;	//LX_AUD_SPDIF_DTO_MINUS_19_5SAMPLES
	}
	else if( stSpdifDtoRate >= LX_AUD_SPDIF_DTO_PLUS_19_5SAMPLES)
	{
		AUD_KDRV_ERROR("SetSPDIFSamplingFreq : freq = %dHz, MAX rate = %d\n", ui32SamplingFreq, stSpdifDtoRate);

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
		ACE_REG_H13A0_Wr01(audio_dto_0, reg_adto_loop_value_2, g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][0]);
		ACE_REG_H13A0_Wr01(audio_dto_1, reg_adto_loop_value_1, g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][1]);
		ACE_REG_H13A0_Wr01(audio_dto_2, reg_adto_loop_value_0, g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][2]);
		ACE_REG_H13A0_Wr01(audio_dto_3, reg_adto_add_value_3,  g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][3]);
		ACE_REG_H13A0_Wr01(audio_dto_4, reg_adto_add_value_2,  g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][4]);
		ACE_REG_H13A0_Wr01(audio_dto_5, reg_adto_add_value_1,  g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][5]);
		ACE_REG_H13A0_Wr01(audio_dto_6, reg_adto_add_value_0,  g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][6]);
		ACE_REG_H13A0_Wr01(audio_dto_7, reg_adto_err_value_1,  g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][7]);
		ACE_REG_H13A0_Wr01(audio_dto_8, reg_adto_err_value_0,  g_AUD_SpdifDtoTable[freqTableNum][rateTableNum][8]);
	}

	//Update DTO clock register.
	//Update add / error value register : 2012.01.11 by joonil.lee request
	ACE_REG_H13A0_WrFL(audio_dto_3);
	ACE_REG_H13A0_WrFL(audio_dto_4);
	ACE_REG_H13A0_WrFL(audio_dto_5);
	ACE_REG_H13A0_WrFL(audio_dto_6);
	ACE_REG_H13A0_WrFL(audio_dto_7);
	ACE_REG_H13A0_WrFL(audio_dto_8);

	//Update loop value register in last : 2012.01.11 by joonil.lee request
	ACE_REG_H13A0_WrFL(audio_dto_0);
	ACE_REG_H13A0_WrFL(audio_dto_1);
	ACE_REG_H13A0_WrFL(audio_dto_2);

	//Send a IMC command for DTO setting
	if(g_AudKdrv.bInitDone == TRUE)
	{
		setDtoRate.dtorate 		   = (UINT32)(rateTableNum + 1);
		setDtoRate.force_cnt_clear = (UINT32)0;
		AUDIO_IMC_SendCmdParam(DTOCTRL_CMD_SET_DTORATE, ADEC_MODULE_DTO_D, sizeof(DtoCtrlCmdSetDtorate), &setDtoRate);
	}

	//Save current SPDIF sampling frequency
	gAdecSpdifFreq_H13A0    = ui32SamplingFreq;

	//Save current SPDIF DTO Rate
	gAdecSpdifDtoRate_H13A0 = stSpdifDtoRate;

	//AUD_KDRV_ERROR("H13A0_MIXED_IP_ADEC_SetSPDIFSamplingFreq : freq = %dHz, rate = %d\n", ui32SamplingFreq, stSpdifDtoRate);

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetSPDIFSamplingFreq : freq = %dHz, rate = %d\n", ui32SamplingFreq, stSpdifDtoRate);
	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_DRV_InitModule
*/
int H13A0_MIXED_IP_ADEC_InitCodecRegisters ( void )
{
	//Setting Mixed IP
	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_InitCodecRegisters : Start\n");

	H13A0_ANALOG_WriteRegister(0x1D, 0x00, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x01, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x03, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x04, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x05, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x0B, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x0E, 0x00);		//DAC0 Volume -125dB
	H13A0_ANALOG_WriteRegister(0x1D, 0x0F, 0x13);		//0x13(SCART DTV) => default value workaround, 2012.05.02
	H13A0_ANALOG_WriteRegister(0x1D, 0x11, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x13, 0x20);		//DAC0 mute rate control, 2011.11.117(0x20 : 64ms) <= 2011. 09.23(0x0F : 30ms)

	//////////////////////////
	//H13A0_ANALOG_WriteRegister(0x1D, 0x14, 0x01);		//Enable DAC0 by-pass, 2011.06.13
	H13A0_ANALOG_WriteRegister(0x1D, 0x14, 0x09);		//Enable DAC0 DC Set-up, 2012.09.17(H13 only)

	H13A0_ANALOG_WriteRegister(0x1D, 0x16, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x17, 0x00);		//0x00, HP(DAC1 Volume) 0dB
	H13A0_ANALOG_WriteRegister(0x1D, 0x18, 0x00);		//0x00, HP(DAC1 Volume) 0dB
	H13A0_ANALOG_WriteRegister(0x1D, 0x1A, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x1C, 0x0F);		//DAC1 mute rate control, 2011. 09.23(0x0F : 30 ms)

	//////////////////////////
	//H13A0_ANALOG_WriteRegister(0x1D, 0x1D, 0x01);		//Enable DAC1 by-pass, 2011.06.13
	H13A0_ANALOG_WriteRegister(0x1D, 0x1D, 0x09);		//Enable DAC1 DC Set-up, 2012.09.17(H13 only)

	H13A0_ANALOG_WriteRegister(0x1D, 0x1F, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x20, 0x40);		//DAC0/1 I2S settimg : Normal(0x40)
	H13A0_ANALOG_WriteRegister(0x1D, 0x2A, 0x02); 		//bug fixed, change with dsp setting, H13 ACE, ADC I2S falling(0x02) for I2S output, 2012.06.08

	H13A0_ANALOG_WriteRegister(0x1D, 0x2B, 0x00);

	//Workaround for 0x2D register not to update issue : 2012.10.25
//	H13A0_ANALOG_WriteRegister(0x1D, 0x2C, 0x0C);		//Amplify ADC digital gain : +3.00 dB, 2012.06.08
	H13A0_ANALOG_WriteRegister(0x1D, 0x2D, 0x07);		//Amplify ADC digital gain : -0.50 dB, 2012.06.14 => total : +2.00 dB
	H13A0_ANALOG_WriteRegister(0x1D, 0x2C, 0x0D);		//Amplify ADC digital gain :-29.00 dB, 2012.10.25 => Workaround for 0x2D register update issue
	H13A0_ANALOG_WriteRegister(0x1D, 0x2C, 0x0C);		//Amplify ADC digital gain : +3.00 dB, 2012.10.25 => Workaround for 0x2D register update issue

	H13A0_ANALOG_WriteRegister(0x1D, 0x2F, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x31, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x33, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x37, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x39, 0x00);
	H13A0_ANALOG_WriteRegister(0x1D, 0x3A, 0x00);

	//This register is added in H13 A0 chip for power down control
	H13A0_ANALOG_WriteRegister(0x1D, 0x48, 0x03);		//ADC power-down : Normal
	H13A0_ANALOG_WriteRegister(0x1D, 0x49, 0xFF);		//DAC power-down : Normal

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_InitCodecRegisters : Done!!!\n");
	return RET_OK;
}

/**
 * Control the Mixed IP AAD, ADC, MIC ADC, DAC and HPDRV module to power on and mute off.
 * @see ADEC_DRV_SetSource
*/
int H13A0_MIXED_IP_ADEC_PowerControl ( LX_AUD_POWER_BLOCK_T block, LX_AUD_POWER_MODE_T mode )
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
		if( (gADECPowerStatus_H13A0[LX_AUD_POWER_AAD].block == block)
		  &&(gADECPowerStatus_H13A0[LX_AUD_POWER_AAD].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_H13A0[LX_AUD_POWER_AAD].block = block;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(AAD) : Same mode(%d)\n", mode);
		}
		else
		{
			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(AAD) : block = %d, mode = %d\n", block, mode);

			//update power block mode
			gADECPowerStatus_H13A0[LX_AUD_POWER_AAD].mode = mode;

			if (mode == LX_AUD_POWER_UP)
			{
				VPORT_I2C_Read((UINT32 *)&afe_aad_7);
				afe_aad_7.aad_dco_resetb = 1;
				VPORT_I2C_Write((UINT32*)&afe_aad_7);
				udelay(AAD_DCO_RESETB_DELAY);	//Spec. => 5 us

				VPORT_I2C_Read((UINT32 *)&afe_aad_14);
				afe_aad_14.aad_spll_pdb = 1;
				VPORT_I2C_Write((UINT32*)&afe_aad_14);
				udelay(AAD_SPLL_PDB_DELAY);		//Spec. => 200 us

				VPORT_I2C_Read((UINT32 *)&afe_aad_7);
				afe_aad_7.aad_adc_pdb = 1;
				VPORT_I2C_Write((UINT32*)&afe_aad_7);
				udelay(AAD_ADC_PDB_DELAY); 		//Spec. => 3 cycles

				udelay(AAD_SW_RESET_DELAY);		//Spec.(?) => 200 us

				VPORT_I2C_Read((UINT32*)&soft_reset_5);
				soft_reset_5.swrst_fs00 = 0;	//aad
				VPORT_I2C_Write((UINT32*)&soft_reset_5);
			}
			else
			{
				//To eliminate D-AMP noise
				udelay(AAD_POWER_OFF_DELAY);	//Spec.(?) => 200 us

				VPORT_I2C_Read((UINT32*)&soft_reset_5);
				soft_reset_5.swrst_fs00 = 1;	//aad
				VPORT_I2C_Write((UINT32*)&soft_reset_5);

				VPORT_I2C_Read((UINT32 *)&afe_aad_7);
				afe_aad_7.aad_adc_pdb = 0;
				VPORT_I2C_Write((UINT32*)&afe_aad_7);
				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us

				VPORT_I2C_Read((UINT32 *)&afe_aad_14);
				afe_aad_14.aad_spll_pdb = 0;
				VPORT_I2C_Write((UINT32*)&afe_aad_14);
				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us

				VPORT_I2C_Read((UINT32 *)&afe_aad_7);
				afe_aad_7.aad_dco_resetb = 0;
				VPORT_I2C_Write((UINT32*)&afe_aad_7);

				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us
			}

			/* When AAD is power-up, SCART output is also enabled. */
			if( g_eAdecInitType & LX_AUD_INIT_TYPE_SYS_DVB )
			{
				//sw reset setting for SCART block
				VPORT_I2C_Read((UINT32*)&soft_reset_8);
				soft_reset_8.swrst_aclk_mux2 = 1;	//audio codec
				VPORT_I2C_Write((UINT32*)&soft_reset_8);

				VPORT_I2C_Read((UINT32*)&soft_reset_4);
				soft_reset_4.swrst_auda_mclk1 = 1;
				soft_reset_4.swrst_auda_mclk0 = 1;
				VPORT_I2C_Write((UINT32*)&soft_reset_4);

				udelay(20);

				//sw reset setting for SCART block
				VPORT_I2C_Read((UINT32*)&soft_reset_4);
				soft_reset_4.swrst_auda_mclk1 = 0;
				soft_reset_4.swrst_auda_mclk0 = 0;
				VPORT_I2C_Write((UINT32*)&soft_reset_4);

				VPORT_I2C_Read((UINT32*)&soft_reset_8);
				soft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
				VPORT_I2C_Write((UINT32*)&soft_reset_8);

				AUD_KDRV_MIP_DEBUG("MIXED_IP_SCART_RESET\n");
				AUD_KDRV_ERROR("MIXED_IP_SCART_RESET\n");
			}

		}
	}

	//LX_AUD_POWER_ADC
	if(block == LX_AUD_POWER_ADC)
	{
		if( (gADECPowerStatus_H13A0[LX_AUD_POWER_ADC].block == block)
		  &&(gADECPowerStatus_H13A0[LX_AUD_POWER_ADC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_H13A0[LX_AUD_POWER_ADC].block = block;

			AUD_KDRV_MIP_DEBUG("ADC : Same mode(%d)\n", mode);
		}
		else
		{
			AUD_KDRV_MIP_DEBUG("ADC : block = %d, mode = %d\n", block, mode);

			//update power block mode
			gADECPowerStatus_H13A0[LX_AUD_POWER_ADC].mode = mode;

			if (mode == LX_AUD_POWER_UP)
			{
				VPORT_I2C_Read((UINT32 *)&gafe_acodec_14);
				gafe_acodec_14.auad_pdb_in 		= 1;
				gafe_acodec_14.auad_rec_ch_muteb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_14);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&gacodec_149);
				gacodec_149.ladc_mute_ena = 1;
				VPORT_I2C_Write((UINT32*)&gacodec_149);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&soft_reset_4);
				soft_reset_4.swrst_auad = 1;
				VPORT_I2C_Write((UINT32*)&soft_reset_4);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us
			}
			else
			{
				VPORT_I2C_Read((UINT32 *)&gafe_acodec_14);
				gafe_acodec_14.auad_pdb_in 		= 0;
				gafe_acodec_14.auad_rec_ch_muteb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_acodec_14);
				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&gacodec_149);
				gacodec_149.ladc_mute_ena = 0;
				VPORT_I2C_Write((UINT32*)&gacodec_149);

				udelay(AUAD_PDB_IN_DELAY);	//Spec. => > 200 us

				VPORT_I2C_Read((UINT32 *)&soft_reset_4);
				soft_reset_4.swrst_auad = 0;
				VPORT_I2C_Write((UINT32*)&soft_reset_4);

				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us
			}
		}
	}

	//LX_AUD_POWER_DAC
	if(block == LX_AUD_POWER_DAC)
	{
		if( (gADECPowerStatus_H13A0[LX_AUD_POWER_DAC].block == block)
		  &&(gADECPowerStatus_H13A0[LX_AUD_POWER_DAC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_H13A0[LX_AUD_POWER_DAC].block = block;

			AUD_KDRV_MIP_DEBUG("DAC : Same mode(%d)\n", mode);
		}
		else
		{
			//update power block mode
			gADECPowerStatus_H13A0[LX_AUD_POWER_DAC].mode = mode;

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
		if( (gADECPowerStatus_H13A0[LX_AUD_POWER_MIC].block == block)
		  &&(gADECPowerStatus_H13A0[LX_AUD_POWER_MIC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_H13A0[LX_AUD_POWER_MIC].block = block;

			AUD_KDRV_MIP_DEBUG("MIC : Same mode(%d)\n", mode);
		}
		else
		{
			//update power block mode
			gADECPowerStatus_H13A0[LX_AUD_POWER_MIC].mode = mode;

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

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_L9_PowerControl : block = %d, mode = %d\n", block, mode);
	return RET_OK;
#endif

}

/**
 * Start the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_DRV_InitModule
*/
int H13A0_MIXED_IP_ADEC_StartCodec ( void )
{
	//Setting Mixed IP
	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_StartCodec : Start\n");

	H13A0_ANALOG_WriteRegister(0x1D, 0x00, 0x7C);
	H13A0_ANALOG_WriteRegister(0x1D, 0x01, 0x19);

	//Hum noise issue after DV-2nd Board
//	H13A0_ANALOG_WriteRegister(0x1D, 0x02, 0x1B);

	//Hum noise issue to DV-2nd Board(2011.10.24)
//	H13A0_ANALOG_WriteRegister(0x1D, 0x02, 0x40);
	H13A0_ANALOG_WriteRegister(0x1D, 0x02, 0x00);	//Amplify ADC digital gain : 1.00 dB, 2011.11.08

	H13A0_ANALOG_WriteRegister(0x1D, 0x03, 0x7B);
	H13A0_ANALOG_WriteRegister(0x1D, 0x10, 0x02);
	H13A0_ANALOG_WriteRegister(0x1D, 0x16, 0x02);
	H13A0_ANALOG_WriteRegister(0x1D, 0x2B, 0x40);
	H13A0_ANALOG_WriteRegister(0x1D, 0x2F, 0x0F);	//to supress pop-noise. ADC volume rate control, 2011.12.29
	H13A0_ANALOG_WriteRegister(0x1D, 0x31, 0x0F);	//to supress pop-noise. ADC mute rate control, 2011.12.29

	H13A0_ANALOG_WriteRegister(0x1D, 0x14, 0x05);	//DAC0 Mute on, SCART
//	H13A0_ANALOG_WriteRegister(0x1D, 0x1D, 0x05);	//DAC1 Mute on, HPDRV
	H13A0_ANALOG_WriteRegister(0x1D, 0x32, 0x04);	//ADC Mute on

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_StartCodec : Done\n");

	return RET_OK;
}

/**
 * Stop the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_DRV_InitModule
*/
int H13A0_MIXED_IP_ADEC_StopCodec ( void )
{

	AUD_KDRV_DEBUG_TMP("H13A0_MIXED_IP_ADEC_StopCodec : Not Implemented!!!\n");
	return RET_OK;
}

/**
 * Sets a ADC port number for ADEC I2S input.
 * @see ADEC_DRV_SetSource
*/
int H13A0_MIXED_IP_ADEC_SetADCPortNumber ( UINT8 ui8PortNum )
{
	if(ui8PortNum < 4)
	{
		ACE_REG_H13A0_RdFL(acodec_50);
		ACE_REG_H13A0_Wr01(acodec_50, ladc_mute_ena, 1);
		ACE_REG_H13A0_WrFL(acodec_50);

		/* Wait for pop-noise supression */
		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_1);
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auad, 1);
		ACE_REG_H13A0_WrFL(soft_reset_1);

		udelay(MIXEDIP_RESET_DELAY_100US);

		/* Set a ADC port number */
		ACE_REG_H13A0_RdFL(afe_acodec_1);
		//3A_01_18:ADC ch1='floating' 19:ADC ch2=AV2  1A:ADC ch3=AV1  1B:ADC ch4=COMP2 1C:ADC ch5=PCIN
		ACE_REG_H13A0_Wr01(afe_acodec_1, auad_gcon, 0x4);	//boost ADC gain : 2.4dB
		ACE_REG_H13A0_Wr01(afe_acodec_1, auad_ch_sel, ui8PortNum);
		ACE_REG_H13A0_WrFL(afe_acodec_1);

		//workaround for not to uodate 0x2D register after IP reset : 2012.10.25
		//H13A0_ANALOG_WriteRegister(0x1D, 0x2D, 0x00);
		H13A0_ANALOG_WriteRegister(0x1D, 0x2D, 0x07); //Amplify ADC digital gain : -0.50 dB, 2012.06.14 => total : +2.00 dB

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_1);
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auad, 0);
		ACE_REG_H13A0_WrFL(soft_reset_1);

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(acodec_50);
		ACE_REG_H13A0_Wr01(acodec_50, ladc_mute_ena, 0);
		ACE_REG_H13A0_WrFL(acodec_50);

		udelay(MIXEDIP_RESET_DELAY_100US);

		//workaround for not working IP reset, add volume control to re-trigger : 2012.10.25
		//H13A0_ANALOG_WriteRegister(0x1D, 0x2D, 0x07); //Amplify ADC digital gain : -0.50 dB, 2012.06.14 => total : +2.00 dB
	}
	else
	{
		AUD_KDRV_ERROR("H13A0_MIXED_IP_ADEC_SetADCPortNumber : ADC Port = %d(Not Supported.)\n", ui8PortNum);
		return RET_ERROR;
	}

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetADCPortNumber : ADC Port = %d\n", ui8PortNum);
	AUD_KDRV_ERROR("SetADCPortNumber : ADC Port = %d\n", ui8PortNum);
	return RET_OK;
}

/**
 * Sets the volume of DAC output.
 * @see ADEC_DRV_SetDACOutVolume
*/
int H13A0_MIXED_IP_ADEC_SetDACOutVolume ( LX_AUD_DAC_VOL_T stDACOutVol )
{
	UINT8	dac0MuteEnable = 0;
	UINT16	dac0_vol_con_1 = 0, dac1_vol_con_1 = 0;

	//L9 B0 Support Function : DAC0 -> SCART, DAC1 -> HPDRV
	//Set a SCART DAC volume for NICAM : Boost
	if ( stDACOutVol.mode & LX_AUD_DAC_SCART )
	{
		//Save gScartBoostSetted
		gScartBoostGain_H13A0 = stDACOutVol.scartGain;

		//Check a current mute status
		ACE_REG_H13A0_RdFL(acodec_20);
		ACE_REG_H13A0_Rd01(acodec_20, dac0_mute_ena, dac0MuteEnable);
		if(dac0MuteEnable == 0)
		{
			ACE_REG_H13A0_Wr01(acodec_20, dac0_mute_ena, 1);		// 1 bit : Line DAC CH0 Mute Control
			ACE_REG_H13A0_WrFL(acodec_20);

			/* To protect pop-noise */
			msleep_interruptible(MIXEDIP_MUTE_DELAY_30MS);	//30ms
		}

		ACE_REG_H13A0_RdFL(acodec_14);
		ACE_REG_H13A0_Rd01(acodec_14, dac0_vol_con_1, dac0_vol_con_1);
		dac0_vol_con_1 &= 0x03;							// 2 bit : Line DAC CH0 Volume Control
		dac0_vol_con_1 |= (UINT8)(stDACOutVol.scartGain << 2);	// 4 bit : Line DAC CH0 Volume Control
		ACE_REG_H13A0_Wr01(acodec_14, dac0_vol_con_1, dac0_vol_con_1);
		ACE_REG_H13A0_WrFL(acodec_14);

		if(dac0MuteEnable == 0)
		{
			ACE_REG_H13A0_RdFL(acodec_20);
			ACE_REG_H13A0_Wr01(acodec_20, dac0_mute_ena, 0);	// 1 bit : Line DAC CH0 Mute Control
			ACE_REG_H13A0_WrFL(acodec_20);
		}

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : SCART Gain = %d(dac0 = 0x%X)\n", stDACOutVol.scartGain, stDACOutVol.scartGain);

#ifdef ENABLE_MUTE_DEBUG
		AUD_KDRV_ERROR("SCART Gain = %d\n", gScartBoostGain_H13A0);
#endif

		return RET_OK;
	}

	//Set a SCART DAC volume : Attunuation
	if ( stDACOutVol.portNum & LX_AUD_OUTPUT_DAC0 )
	{
		//Check Mute case if volume is 0x3FF
		if(stDACOutVol.hwVolume == 0x3FF)
		{
			ACE_REG_H13A0_RdFL(acodec_15);
			ACE_REG_H13A0_Wr01(acodec_15, dac0_vol_con_0, (UINT8)(stDACOutVol.hwVolume & 0xFF));	// 8 bit : Line DAC CH0 Volume Control
			ACE_REG_H13A0_WrFL(acodec_15);

			ACE_REG_H13A0_RdFL(acodec_14);
			dac0_vol_con_1  = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH0 Volume Control
			dac0_vol_con_1 |= (gScartBoostGain_H13A0 << 2);	// 4 bit : Line DAC CH0 Volume Control
			ACE_REG_H13A0_Wr01(acodec_14, dac0_vol_con_1, dac0_vol_con_1);
			ACE_REG_H13A0_WrFL(acodec_14);
		}
		else
		{
			ACE_REG_H13A0_RdFL(acodec_15);
			ACE_REG_H13A0_Wr01(acodec_15, dac0_vol_con_0, (UINT8)(stDACOutVol.hwVolume & 0xFF));	// 8 bit : Line DAC CH0 Volume Control
			ACE_REG_H13A0_WrFL(acodec_15);

			//Check gScartBoostGain_H13A0 value
			if(gScartBoostGain_H13A0)
			{
				ACE_REG_H13A0_RdFL(acodec_14);
				dac0_vol_con_1  = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH0 Volume Control
				dac0_vol_con_1 |= (gScartBoostGain_H13A0 << 2);	// 4 bit : Line DAC CH0 Volume Control
				ACE_REG_H13A0_Wr01(acodec_14, dac0_vol_con_1, dac0_vol_con_1);
				ACE_REG_H13A0_WrFL(acodec_14);
			}
			else
			{
				ACE_REG_H13A0_RdFL(acodec_14);
				dac0_vol_con_1  = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH0 Volume Control
				ACE_REG_H13A0_Wr01(acodec_14, dac0_vol_con_1, dac0_vol_con_1);
				ACE_REG_H13A0_WrFL(acodec_14);
			}
		}

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : SCART(dac0_0 = 0x%X, dac0_1 = 0x%X)\n", stDACOutVol.hwVolume, stDACOutVol.hwVolume >> 8);
	}

	//Set a HeadPhone DAC volume
	if ( stDACOutVol.portNum & LX_AUD_OUTPUT_DAC2 )
	{
		ACE_REG_H13A0_RdFL(acodec_24);
		ACE_REG_H13A0_Wr01(acodec_24, dac1_vol_con_0, (UINT8)(stDACOutVol.hwVolume & 0xFF));	// 8 bit : Line DAC CH1 Volume Control
		ACE_REG_H13A0_WrFL(acodec_24);

		ACE_REG_H13A0_RdFL(acodec_23);
		dac1_vol_con_1 = (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH1 Volume Control
		ACE_REG_H13A0_Wr01(acodec_23, dac1_vol_con_1, dac1_vol_con_1);
		ACE_REG_H13A0_WrFL(acodec_23);

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : HPDRV(dac1_0 = 0x%X, dac1_1 = 0x%X)\n", stDACOutVol.hwVolume, stDACOutVol.hwVolume >> 8);
	}

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetDACOutVolume : Port = %d, Volume = 0x%X\n", stDACOutVol.portNum, stDACOutVol.hwVolume);
	return RET_OK;
}

/**
 * Sets the mute of DAC output.
 * @see ADEC_DRV_SetOutputPortMute
*/
int H13A0_MIXED_IP_ADEC_SetDACOutMute ( LX_AUD_OUTPUT_PORT_MUTE_T stOutPortMute )
{
	//H13 Support Function : DAC0 -> SCART, DAC1 -> HPDRV

	//Set a SCART DAC Reset
	if ( stOutPortMute.mode & LX_AUD_DAC_SCART_RESET )
	{
		ACE_REG_H13A0_RdFL(soft_reset_14);
		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk0, 1);	//audio codec : dac 0
		ACE_REG_H13A0_WrFL(soft_reset_14);

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_1);
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk0, 1);	//audio codec : dac 0
		ACE_REG_H13A0_WrFL(soft_reset_1);

		//add delay for clock setting
		udelay(MIXEDIP_RESET_DELAY_100US * 2);

		ACE_REG_H13A0_RdFL(soft_reset_1);
		ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk0, 0);	//audio codec : dac 0,
		ACE_REG_H13A0_WrFL(soft_reset_1);

		udelay(MIXEDIP_RESET_DELAY_100US);

		ACE_REG_H13A0_RdFL(soft_reset_14);
		ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk0, 0);	//audio codec : dac 0
		ACE_REG_H13A0_WrFL(soft_reset_14);

		AUD_KDRV_MIP_DEBUG("SCART : Reset\n");

		return RET_OK;
	}

	//Set a SCART DAC mute
	if ( stOutPortMute.portNum & LX_AUD_OUTPUT_DAC0 )
	{
		if( stOutPortMute.bHwOnOff == TRUE )
		{
			ACE_REG_H13A0_RdFL(acodec_20);
			ACE_REG_H13A0_Wr01(acodec_20, dac0_mute_ena, 1);		// 1 bit : Line DAC CH0 Mute Control
			ACE_REG_H13A0_WrFL(acodec_20);

			AUD_KDRV_MIP_DEBUG("SCART : Mute On\n");

#ifdef ENABLE_MUTE_DEBUG
			AUD_KDRV_ERROR("SCART : Mute On\n");
#endif
		}
		else	//un-mute
		{
			ACE_REG_H13A0_RdFL(acodec_20);
			ACE_REG_H13A0_Wr01(acodec_20, dac0_mute_ena, 0);		// 1 bit : Line DAC CH0 Mute Control
			ACE_REG_H13A0_WrFL(acodec_20);

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
			ACE_REG_H13A0_RdFL(acodec_29);
			ACE_REG_H13A0_Wr01(acodec_29, dac1_mute_ena, 1);	// 1 bit : Line DAC CH1 Mute Control
			ACE_REG_H13A0_WrFL(acodec_29);

			msleep_interruptible(MIXEDIP_MUTE_DELAY_30MS);

			ACE_REG_H13A0_RdFL(soft_reset_14);
			ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 1);	//audio codec : dac 1
			ACE_REG_H13A0_WrFL(soft_reset_14);

			ACE_REG_H13A0_RdFL(soft_reset_1);
			ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 1);	//audio codec : dac 1
			ACE_REG_H13A0_WrFL(soft_reset_1);

			//add delay for clock setting
			udelay(MIXEDIP_RESET_DELAY_100US * 2);

			AUD_KDRV_MIP_DEBUG("HPDRV : Mute On\n");

#ifdef ENABLE_MUTE_DEBUG
			AUD_KDRV_ERROR("HPDRV : Mute On\n");
#endif
		}
		else	//un-mute
		{
			ACE_REG_H13A0_RdFL(soft_reset_1);
			ACE_REG_H13A0_Wr01(soft_reset_1, swrst_auda_mclk1, 0);	//audio codec : dac 1
			ACE_REG_H13A0_WrFL(soft_reset_1);

			ACE_REG_H13A0_RdFL(soft_reset_14);
			ACE_REG_H13A0_Wr01(soft_reset_14, swrst_auda_f256fs_clk1, 0);	//audio codec : dac 1
			ACE_REG_H13A0_WrFL(soft_reset_14);

			msleep_interruptible(MIXEDIP_MUTE_DELAY_30MS);

			ACE_REG_H13A0_RdFL(acodec_29);
			ACE_REG_H13A0_Wr01(acodec_29, dac1_mute_ena, 0);	// 1 bit : Line DAC CH1 Mute Control
			ACE_REG_H13A0_WrFL(acodec_29);

			AUD_KDRV_MIP_DEBUG("HPDRV : Mute Off\n");

#ifdef ENABLE_MUTE_DEBUG
			AUD_KDRV_ERROR("HPDRV : Mute Off\n");
#endif
		}
	}

	AUD_KDRV_MIP_DEBUG("H13A0_MIXED_IP_ADEC_SetDACOutMute : Port = %d, mute = 0x%X\n", stOutPortMute.portNum, stOutPortMute.bHwOnOff);
	return RET_OK;
}


/** @} */




