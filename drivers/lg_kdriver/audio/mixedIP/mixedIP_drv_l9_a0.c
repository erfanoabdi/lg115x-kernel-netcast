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
//Current Mixed IP Power Status
static LX_AUD_POWER_STATUS_T gADECPowerStatus_L9A0[LX_AUD_POWER_MAX] = {	\
							  {LX_AUD_POWER_AAD, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_ADC, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_HPDRV, LX_AUD_POWER_UP},
							  {LX_AUD_POWER_DAC, 	LX_AUD_POWER_UP},
							  {LX_AUD_POWER_MIC, 	LX_AUD_POWER_UP} };

//Current SCART Boost Gain Setting
static UINT16 gScartBoostGain_L9A0 = 0;

//Current ADEC Clock Source Setting
static LX_AUD_CLOCK_SRC_T gAdecClockSource_L9A0 = LX_AUD_CLOCK_UNKNOWN;

//Current SPDIF Sampling Frequency Setting
static LX_AUD_SAMPLING_FREQ_T gAdecSpdifFreq_L9A0 = LX_AUD_SAMPLING_FREQ_NONE;


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
	int 	ret = 0;
	UINT32	addr = 0;

	VPORT_I2C_DATA_T *i2cData = (VPORT_I2C_DATA_T*)&addr;

	i2cData->slaveAddr = slaveAddr;
	i2cData->regAddr   = regAddr;

	VPORT_I2C_Read((UINT32 *)i2cData);

	*value = i2cData->data;

	AUD_KDRV_MIP_DEBUG("Read  : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", i2cData->slaveAddr, i2cData->regAddr, i2cData->data);
//	AUD_KDRV_ERROR("Read  : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", i2cData->slaveAddr, i2cData->regAddr, i2cData->data);

	return ret;
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
	int 	ret = 0;
	UINT32	addr = 0;

	VPORT_I2C_DATA_T *i2cData = (VPORT_I2C_DATA_T*)&addr;

	i2cData->slaveAddr = slaveAddr;
	i2cData->regAddr   = regAddr;
	i2cData->data      = value;

	VPORT_I2C_Write((UINT32*)i2cData);

	AUD_KDRV_MIP_DEBUG("Write : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", i2cData->slaveAddr, i2cData->regAddr, i2cData->data);
//	AUD_KDRV_ERROR("Write : Slave 0x%2x, reg 0x%2x  Data = 0x%2x\n", i2cData->slaveAddr, i2cData->regAddr, i2cData->data);

	return ret;
}

/**
 * Initializes the clock and reset module register value.
 * @see ADEC_Init
*/
int L9A0_MIXED_IP_ADEC_L9_InitClockRegisters( void )
{
	//Initialize clock registers.

	//clock setting for APLL block
	VPORT_I2C_Read((UINT32 *)&gaudio_pll_0);
	gaudio_pll_0.apll_mode_en	= 1;
	// 0 : 12.288MHz, 1 : 11.2896MHz, 2 : 8.192 MHz, 3 : 24.576MHz, 4 : 49.152 MHz,
	// 5 : 16.384 MHz, 6 : 32.768 MHz, 7 : 22.5792 MHz, 8 : 45.1584 MHz
	gaudio_pll_0.apll_mode		= 0;
	VPORT_I2C_Write((UINT32*)&gaudio_pll_0);

	VPORT_I2C_Read((UINT32 *)&gaudio_pll_6);
	gaudio_pll_6.apll_pdb		= 1;			// 0 :power down, 1 : normal operation
	VPORT_I2C_Write((UINT32*)&gaudio_pll_6);


	//clock setting for aad/btsc block
	VPORT_I2C_Read((UINT32*)&gafe_aad_0);
	gafe_aad_0.aad_adc_selref	= 3;
	gafe_aad_0.aad_adc_pdb		= 1;
	gafe_aad_0.aad_dco_rtest	= 1;
	gafe_aad_0.aad_dco_resetb	= 1;
	VPORT_I2C_Write((UINT32*)&gafe_aad_0);

	VPORT_I2C_Read((UINT32*)&gafe_aad_7);
	gafe_aad_7.aad_spll_cvl 	= 2;
	gafe_aad_7.aad_spll_cvs 	= 3;
	gafe_aad_7.aad_spll_sel 	= 0;
	gafe_aad_7.aad_spll_pdb 	= 1;
	gafe_aad_7.aad_spllclk_test = 0;
	VPORT_I2C_Write((UINT32*)&gafe_aad_7);

	VPORT_I2C_Read((UINT32*)&gafe_aad_8);
	gafe_aad_8.aad_adcclk_test	= 0;
	gafe_aad_8.aad_fs00clk_sel	= 0;
	gafe_aad_8.aad_fs01clk_sel	= 0;
	gafe_aad_8.aad_fs02clk_sel	= 0;
	gafe_aad_8.aad_btscclk_sel	= 0;
	VPORT_I2C_Write((UINT32*)&gafe_aad_8);

	//delay before sw reset control
	udelay(200);

	//sw reset setting for mixed-IP block
	VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
	gsoft_reset_4.swrst_hp_drv_ctrl	= 0;
	gsoft_reset_4.swrst_hp_drv 		= 0;
	gsoft_reset_4.swrst_mic 		= 0;
	gsoft_reset_4.swrst_auad 		= 0;
	gsoft_reset_4.swrst_mclk1 		= 0;	//audio codec
	gsoft_reset_4.swrst_mclk0 		= 0;	//audio codec
	VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_5);
	gsoft_reset_5.swrst_fs00 = 0;	//aad
	VPORT_I2C_Write((UINT32*)&gsoft_reset_5);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
	gsoft_reset_8.swrst_aclk_mux2 	= 0;	//audio codec -> clk reset xxx
	gsoft_reset_8.swrst_hp_drv_32x	= 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_9);
	gsoft_reset_9.swrst_aud_fs26clk	= 0;
	gsoft_reset_9.swrst_aud_fs25clk = 0;
	gsoft_reset_9.swrst_aud_fs24clk = 0;
	gsoft_reset_9.swrst_aud_fs23clk = 0;
	gsoft_reset_9.swrst_aud_fs21clk = 0;
	gsoft_reset_9.swrst_aud_fs20clk = 0;
	gsoft_reset_9.swrst_audclk_out	= 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_9);

	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_SetClockSource( LX_AUD_CLOCK_SRC_T ui8AdecClockSrc )
{
	UINT8	dac0_mute_ena = 0;
	UINT8	dac1_mute_ena = 0;

#ifdef ENABLE_HPDRV_PORT
	UINT8	hp_mute_ena   = 0;
#endif	//#ifdef ENABLE_HPDRV_PORT

	//Check previous clock source
	if(ui8AdecClockSrc == gAdecClockSource_L9A0)
	{
		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetClockSource : %d\n", ui8AdecClockSrc);
		return RET_OK;
	}

	//Setting Audio Clock Mux
	//Reset on for Mixed IP Module
	VPORT_I2C_Read((UINT32*)&gacodec_9);
	dac0_mute_ena = gacodec_9.dac0_mute_ena;
	gacodec_9.dac0_mute_ena = 1;	// 1 bit : Line DAC CH0 Mute Control
	VPORT_I2C_Write((UINT32*)&gacodec_9);

	VPORT_I2C_Read((UINT32*)&gacodec_18);
	dac1_mute_ena = gacodec_18.dac1_mute_ena;
	gacodec_18.dac1_mute_ena = 1;	// 1 bit : Line DAC CH1 Mute Control
	VPORT_I2C_Write((UINT32*)&gacodec_18);

	VPORT_I2C_Read((UINT32 *)&gacodec_39);
	gacodec_39.ladc_mute_ena = 1;
	VPORT_I2C_Write((UINT32*)&gacodec_39);

#ifdef ENABLE_HPDRV_PORT
	VPORT_I2C_Read((UINT32 *)&gacodec_28);
	hp_mute_ena = gacodec_28.hp_mute_ena;
	gacodec_28.hp_mute_ena = 1;		// 1 bit : HP Driver Mute Control
	VPORT_I2C_Write((UINT32*)&gacodec_28);
#endif	//#ifdef ENABLE_HPDRV_PORT

	msleep_interruptible(MIXEDIP_RESET_DELAY);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
	gsoft_reset_8.swrst_aclk_mux2 = 1;	//audio codec
	VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
	gsoft_reset_4.swrst_mclk1  = 1;	//audio codec
	gsoft_reset_4.swrst_mclk0  = 1;	//audio codec
	gsoft_reset_4.swrst_auad   = 1;
#ifdef ENABLE_HPDRV_PORT
	gsoft_reset_4.swrst_hp_drv = 1;
#endif	//#ifdef ENABLE_HPDRV_PORT
	VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

	//Read clock mux reg.
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_10);
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_11);
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_12);
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_13);
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_14);
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_15);
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_16);
	VPORT_I2C_Read((UINT32 *)&gsoft_reset_17);

	if( ui8AdecClockSrc == LX_AUD_CLOCK_DTV )	//DTV to SPK(default)
	{
		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetClockSource : LX_AUD_CLOCK_DTV\n");

		gsoft_reset_10.aclk_mux1_src = 1;
		gsoft_reset_11.aclk_mux1_div = 0;
		gsoft_reset_11.aclk_mux2_src = 1;
		gsoft_reset_12.aclk_mux2_div = 0;

		gsoft_reset_12.aclk_mux3_src = 1;
		gsoft_reset_13.aclk_mux3_div = 1;
		gsoft_reset_13.aclk_mux4_src = 1;
		gsoft_reset_14.aclk_mux4_div = 1;
		gsoft_reset_14.aclk_mux5_src = 1;
		gsoft_reset_15.aclk_mux5_div = 1;
		gsoft_reset_15.aclk_mux6_src = 1;
		gsoft_reset_16.aclk_mux6_div = 1;
		gsoft_reset_16.aclk_mux7_src = 1;
		gsoft_reset_17.aclk_mux7_div = 1;
		gsoft_reset_17.aclk_mux8_src = 1;
		gsoft_reset_17.aclk_mux8_div = 1;
	}
	else if( ui8AdecClockSrc == LX_AUD_CLOCK_ATV ) //Analog TV to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetClockSource : LX_AUD_CLOCK_ATV\n");

		gsoft_reset_10.aclk_mux1_src = 0;
		gsoft_reset_11.aclk_mux1_div = 1;
		gsoft_reset_11.aclk_mux2_src = 0;
		gsoft_reset_12.aclk_mux2_div = 1;

		gsoft_reset_12.aclk_mux3_src = 0;
		gsoft_reset_13.aclk_mux3_div = 2;
		gsoft_reset_13.aclk_mux4_src = 0;
		gsoft_reset_14.aclk_mux4_div = 2;
		gsoft_reset_14.aclk_mux5_src = 0;
		gsoft_reset_15.aclk_mux5_div = 2;
		gsoft_reset_15.aclk_mux6_src = 0;
		gsoft_reset_16.aclk_mux6_div = 2;
		gsoft_reset_16.aclk_mux7_src = 0;
		gsoft_reset_17.aclk_mux7_div = 2;
		gsoft_reset_17.aclk_mux8_src = 0;
		gsoft_reset_17.aclk_mux8_div = 2;
	}
	else if( ui8AdecClockSrc == LX_AUD_CLOCK_ADC ) //ADC to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetClockSource : LX_AUD_CLOCK_ADC\n");

		gsoft_reset_10.aclk_mux1_src = 0;
		gsoft_reset_11.aclk_mux1_div = 1;
#ifndef ENABLE_SCART_BYPASS_TEST	//Use APLL clock
		gsoft_reset_11.aclk_mux2_src = 1;
		gsoft_reset_12.aclk_mux2_div = 0;
#else	//Use AAD AFE clock
		gsoft_reset_11.aclk_mux2_src = 0;
		gsoft_reset_12.aclk_mux2_div = 1;
#endif

		gsoft_reset_12.aclk_mux3_src = 0;
		gsoft_reset_13.aclk_mux3_div = 2;
		gsoft_reset_13.aclk_mux4_src = 0;
		gsoft_reset_14.aclk_mux4_div = 2;
		gsoft_reset_14.aclk_mux5_src = 0;
		gsoft_reset_15.aclk_mux5_div = 2;
		gsoft_reset_15.aclk_mux6_src = 0;
		gsoft_reset_16.aclk_mux6_div = 2;
		gsoft_reset_16.aclk_mux7_src = 0;
		gsoft_reset_17.aclk_mux7_div = 2;
		gsoft_reset_17.aclk_mux8_src = 0;
		gsoft_reset_17.aclk_mux8_div = 2;
	}
	else if( ui8AdecClockSrc == LX_AUD_CLOCK_HDMI )	//HDMI to SPK, SCART AAD bypass
	{
		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetClockSource : LX_AUD_CLOCK_HDMI\n");

	//L9 A0 workaround for 128 Fs to 256 Fs for AAD clock
#ifndef ENABLE_SCART_BYPASS_TEST	//Use HDMI Clock
		gsoft_reset_10.aclk_mux1_src = 4;
		gsoft_reset_11.aclk_mux1_div = 0;
		gsoft_reset_11.aclk_mux2_src = 4;
		gsoft_reset_12.aclk_mux2_div = 0;

		gsoft_reset_12.aclk_mux3_src = 4;
		gsoft_reset_13.aclk_mux3_div = 1;
		gsoft_reset_13.aclk_mux4_src = 4;
		gsoft_reset_14.aclk_mux4_div = 1;
		gsoft_reset_14.aclk_mux5_src = 4;
		gsoft_reset_15.aclk_mux5_div = 1;
		gsoft_reset_15.aclk_mux6_src = 4;
		gsoft_reset_16.aclk_mux6_div = 1;
		gsoft_reset_16.aclk_mux7_src = 4;
		gsoft_reset_17.aclk_mux7_div = 1;
		gsoft_reset_17.aclk_mux8_src = 4;
		gsoft_reset_17.aclk_mux8_div = 1;
#else	//Use AAD AFE clock
		gsoft_reset_10.aclk_mux1_src = 0;
		gsoft_reset_11.aclk_mux1_div = 1;
		gsoft_reset_11.aclk_mux2_src = 0;
		gsoft_reset_12.aclk_mux2_div = 1;

		gsoft_reset_12.aclk_mux3_src = 0;
		gsoft_reset_13.aclk_mux3_div = 2;
		gsoft_reset_13.aclk_mux4_src = 0;
		gsoft_reset_14.aclk_mux4_div = 2;
		gsoft_reset_14.aclk_mux5_src = 0;
		gsoft_reset_15.aclk_mux5_div = 2;
		gsoft_reset_15.aclk_mux6_src = 0;
		gsoft_reset_16.aclk_mux6_div = 2;
		gsoft_reset_16.aclk_mux7_src = 0;
		gsoft_reset_17.aclk_mux7_div = 2;
		gsoft_reset_17.aclk_mux8_src = 0;
		gsoft_reset_17.aclk_mux8_div = 2;
#endif
	}
	else
	{
		AUD_KDRV_ERROR("MIXED_IP_ADEC_DRV_SetClockSource : 0x%X(Not Supported!!!)\n", ui8AdecClockSrc);
		return RET_ERROR;
	}

	//Write clock mux reg.
	VPORT_I2C_Write((UINT32*)&gsoft_reset_10);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_11);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_12);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_13);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_14);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_15);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_16);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_17);

	//Wait for SCART & HP reset
	//msleep_interruptible(MIXEDIP_RESET_DELAY);
	udelay(100);

#if 1
	VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
	gsoft_reset_4.swrst_mclk1 = 0;
	gsoft_reset_4.swrst_mclk0 = 0;
	gsoft_reset_4.swrst_auad  = 0;
	VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

	VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
	gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
	VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

	msleep_interruptible(MIXEDIP_RESET_DELAY);

	VPORT_I2C_Read((UINT32*)&gacodec_9);
	gacodec_9.dac0_mute_ena = 0;	// 1 bit : Line DAC CH0 Mute Control
	VPORT_I2C_Write((UINT32*)&gacodec_9);

	VPORT_I2C_Read((UINT32*)&gacodec_18);
	gacodec_18.dac1_mute_ena = 0;	// 1 bit : Line DAC CH1 Mute Control
	VPORT_I2C_Write((UINT32*)&gacodec_18);

	VPORT_I2C_Read((UINT32 *)&gacodec_39);
	gacodec_39.ladc_mute_ena = 0;
	VPORT_I2C_Write((UINT32*)&gacodec_39);
#else
	//Reset off for Mixed IP Module for un-mute
	if(dac0_mute_ena == 0 || dac1_mute_ena == 0)
	{
		VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
		gsoft_reset_4.swrst_mclk1 = 0;
		gsoft_reset_4.swrst_mclk0 = 0;
		gsoft_reset_4.swrst_auad  = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

		VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
		gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
		VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

		msleep_interruptible(MIXEDIP_RESET_DELAY);

		if(dac0_mute_ena == 0)
		{
			VPORT_I2C_Read((UINT32*)&gacodec_9);
			gacodec_9.dac0_mute_ena = 0;	// 1 bit : Line DAC CH0 Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_9);
		}

		if(dac1_mute_ena == 0)
		{
			VPORT_I2C_Read((UINT32*)&gacodec_18);
			gacodec_18.dac1_mute_ena = 0;	// 1 bit : Line DAC CH1 Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_18);
		}
	}
	else
	{
		msleep_interruptible(MIXEDIP_RESET_DELAY);

		VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
		gsoft_reset_4.swrst_mclk1 = 0;
		gsoft_reset_4.swrst_mclk0 = 0;
		gsoft_reset_4.swrst_auad  = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

		VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
		gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
		VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

		msleep_interruptible(MIXEDIP_RESET_DELAY);
	}

	VPORT_I2C_Read((UINT32 *)&gacodec_39);
	gacodec_39.ladc_mute_ena = 0;
	VPORT_I2C_Write((UINT32*)&gacodec_39);
#endif

#ifdef ENABLE_HPDRV_PORT
	if(hp_mute_ena == 0)
	{
		VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
		gsoft_reset_4.swrst_hp_drv = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

		VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
		gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
		VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

		msleep_interruptible(MIXEDIP_RESET_DELAY);

		VPORT_I2C_Read((UINT32 *)&gacodec_28);
		gacodec_28.hp_mute_ena = 0;		// 1 bit : HP Driver Mute Control
		VPORT_I2C_Write((UINT32*)&gacodec_28);
	}
	else
	{
		msleep_interruptible(MIXEDIP_RESET_DELAY);

		VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
		gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
		VPORT_I2C_Write((UINT32*)&gsoft_reset_8);
	}
#endif	//#ifdef ENABLE_HPDRV_PORT

	//Save current clock source
	gAdecClockSource_L9A0 = ui8AdecClockSrc;

	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetClockSource : %d\n", ui8AdecClockSrc);

	return RET_OK;
}


/**
 * Sets a PCM Clock frequency and Rate to sync with SPDIF clock for SPDIF output.
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_SetPcmClockRate ( LX_AUD_SAMPLING_FREQ_T ui32SrcFreq, UINT32 ui32PcmClock )
{
	AUD_KDRV_MIP_DEBUG("L9A0_MIXED_IP_ADEC_L9_SetPcmClockRate : Not Implemented!!!\n");

	return RET_OK;
}

int L9A0_MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq ( LX_AUD_SAMPLING_FREQ_T ui32SamplingFreq, LX_AUD_SPDIF_DTO_RATE_T stSpdifDtoRate )
{
	VPORT_I2C_Read((UINT32*)&gsoft_reset_13);

	VPORT_I2C_Read((UINT32*)&gaudio_dto_1);
	VPORT_I2C_Read((UINT32*)&gaudio_dto_2);
	VPORT_I2C_Read((UINT32*)&gaudio_dto_3);
	VPORT_I2C_Read((UINT32*)&gaudio_dto_4);
	VPORT_I2C_Read((UINT32*)&gaudio_dto_5);
	VPORT_I2C_Read((UINT32*)&gaudio_dto_6);
	VPORT_I2C_Read((UINT32*)&gaudio_dto_8);

	if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_48_KHZ )
	{
		if(	gAdecSpdifFreq_L9A0 == ui32SamplingFreq)
		{
			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : same to 48_KHZ\n" );
			return RET_OK;
		}

		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : 48_KHZ\n" );

		gsoft_reset_13.aclk_mux4_src = 1;

		gaudio_dto_1.reg_adto_loop_value_1 = 0x0D;
		gaudio_dto_2.reg_adto_loop_value_0 = 0x2E;
		gaudio_dto_3.reg_adto_add_value_3 = 0x13;
		gaudio_dto_4.reg_adto_add_value_2 = 0x6B;
		gaudio_dto_5.reg_adto_add_value_1 = 0x06;
		gaudio_dto_6.reg_adto_add_value_0 = 0xE7;
		gaudio_dto_8.reg_adto_err_value_0 = 0x00;
	}
	else if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_44_1KHZ )
	{
		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : 44_1KHZ\n" );

		gsoft_reset_13.aclk_mux4_src = 2;

		gaudio_dto_0.reg_adto_loop_value_2 = 0x00;
		gaudio_dto_1.reg_adto_loop_value_1 = 0x15;
		gaudio_dto_2.reg_adto_loop_value_0 = 0xF8;
		gaudio_dto_3.reg_adto_add_value_3 = 0x11;
		gaudio_dto_4.reg_adto_add_value_2 = 0xD7;
		gaudio_dto_5.reg_adto_add_value_1 = 0x21;
		gaudio_dto_6.reg_adto_add_value_0 = 0x8A;
		gaudio_dto_8.reg_adto_err_value_0 = 0x09;
	}
	else if( ui32SamplingFreq == LX_AUD_SAMPLING_FREQ_32_KHZ )
	{
		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : 32_KHZ\n" );

		gsoft_reset_13.aclk_mux4_src = 2;

		gaudio_dto_0.reg_adto_loop_value_2 = 0x00;
		gaudio_dto_1.reg_adto_loop_value_1 = 0x27;
		gaudio_dto_2.reg_adto_loop_value_0 = 0x8C;
		gaudio_dto_3.reg_adto_add_value_3 = 0x0C;
		gaudio_dto_4.reg_adto_add_value_2 = 0xF2;
		gaudio_dto_5.reg_adto_add_value_1 = 0x04;
		gaudio_dto_6.reg_adto_add_value_0 = 0x9A;
		gaudio_dto_8.reg_adto_err_value_0 = 0x00;
	}
	else
	{
		if(	gAdecSpdifFreq_L9A0 == ui32SamplingFreq)
		{
			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : same to 48_KHZ\n" );
			return RET_OK;
		}

		AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : %d => 48KHz\n", ui32SamplingFreq);

		gsoft_reset_13.aclk_mux4_src = 1;

		gaudio_dto_1.reg_adto_loop_value_1 = 0x0D;
		gaudio_dto_2.reg_adto_loop_value_0 = 0x2E;
		gaudio_dto_3.reg_adto_add_value_3 = 0x13;
		gaudio_dto_4.reg_adto_add_value_2 = 0x6B;
		gaudio_dto_5.reg_adto_add_value_1 = 0x06;
		gaudio_dto_6.reg_adto_add_value_0 = 0xE7;
		gaudio_dto_8.reg_adto_err_value_0 = 0x00;
	}

	VPORT_I2C_Write((UINT32*)&gsoft_reset_13);

	VPORT_I2C_Write((UINT32*)&gaudio_dto_1);
	VPORT_I2C_Write((UINT32*)&gaudio_dto_2);
	VPORT_I2C_Write((UINT32*)&gaudio_dto_3);
	VPORT_I2C_Write((UINT32*)&gaudio_dto_4);
	VPORT_I2C_Write((UINT32*)&gaudio_dto_5);
	VPORT_I2C_Write((UINT32*)&gaudio_dto_6);
	VPORT_I2C_Write((UINT32*)&gaudio_dto_8);

	//Save current SPDIF sampling frequency
	gAdecSpdifFreq_L9A0 = ui32SamplingFreq;

	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_SetSPDIFSamplingFreq : %dKHz\n", ui32SamplingFreq);

	return RET_OK;
}

/**
 * Initializes the Mixed IP ADC, MIC ADC, DAC and HP module register value.
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_InitCodecRegisters ( void )
{
	//Setting Mixed IP
	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_InitCodecRegisters : Start\n");

	L9A0_ANALOG_WriteRegister(0x1D, 0x00, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x01, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x02, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x03, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x04, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x05, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x06, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x07, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x08, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x09, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x0A, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x0B, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x0C, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x0D, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x0E, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x0F, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x10, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x11, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x12, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x13, 0x08);
	L9A0_ANALOG_WriteRegister(0x1D, 0x14, 0x01);		//Enable DAC0 by-pass, 2011.06.13
	L9A0_ANALOG_WriteRegister(0x1D, 0x15, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x16, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x17, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x18, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x19, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x1A, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x1B, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x1C, 0x08);
	L9A0_ANALOG_WriteRegister(0x1D, 0x1D, 0x01);		//Enable DAC0 by-pass, 2011.06.13
	L9A0_ANALOG_WriteRegister(0x1D, 0x1E, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x1F, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x20, 0x40);		//DAC0/1 I2S settimg : Normal(0x40) -> L/R change(0x50)
	L9A0_ANALOG_WriteRegister(0x1D, 0x21, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x22, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x23, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x24, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x25, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x26, 0x14);
	L9A0_ANALOG_WriteRegister(0x1D, 0x27, 0x04);
	L9A0_ANALOG_WriteRegister(0x1D, 0x28, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x29, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x2A, 0x02);		//ADC L/R Normal(0x02) for I2S output -> L/R change(0x00)
	L9A0_ANALOG_WriteRegister(0x1D, 0x2B, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x2C, 0x04);		//Amplify ADC digital gain : 1.00 dB
	L9A0_ANALOG_WriteRegister(0x1D, 0x2D, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x2E, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x2F, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x30, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x31, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x32, 0x04);
	L9A0_ANALOG_WriteRegister(0x1D, 0x33, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x34, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x35, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x36, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x37, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x38, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x39, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x3A, 0x00);

	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_InitCodecRegisters : Done!!!\n");

	return RET_OK;
}

/**
 * Control the Mixed IP AAD, ADC, MIC ADC, DAC and HPDRV module to power on and mute off.
 * @see ADEC_L9_SetSource
*/
int L9A0_MIXED_IP_ADEC_L9_PowerControl ( LX_AUD_POWER_BLOCK_T block, LX_AUD_POWER_MODE_T mode )
{
//L9 A0 ADC uses AAD clock for operation, so AAD block must always enabled now.
#if 0
	//LX_AUD_POWER_AAD
	if(block == LX_AUD_POWER_AAD)
	{
		if( (gADECPowerStatus_L9A0[LX_AUD_POWER_AAD].block == block)
		  &&(gADECPowerStatus_L9A0[LX_AUD_POWER_AAD].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9A0[LX_AUD_POWER_AAD].block = block;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(AAD) : Same mode(%d)\n", mode);
		}
		else
		{
			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(AAD) : block = %d, mode = %d\n", block, mode);

			//update power block mode
			gADECPowerStatus_L9A0[LX_AUD_POWER_AAD].mode = mode;

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

				VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
				gsoft_reset_4.swrst_mclk1 = 1;
				gsoft_reset_4.swrst_mclk0 = 1;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

				udelay(20);

				//sw reset setting for SCART block
				VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
				gsoft_reset_4.swrst_mclk1 = 0;
				gsoft_reset_4.swrst_mclk0 = 0;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

				VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
				gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
				VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

				AUD_KDRV_MIP_DEBUG("MIXED_IP_SCART_RESET\n");
				AUD_KDRV_ERROR("MIXED_IP_SCART_RESET\n");
			}

		}
	}
#endif

	//LX_AUD_POWER_ADC
	if(block == LX_AUD_POWER_ADC)
	{
		if( (gADECPowerStatus_L9A0[LX_AUD_POWER_ADC].block == block)
		  &&(gADECPowerStatus_L9A0[LX_AUD_POWER_ADC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9A0[LX_AUD_POWER_ADC].block = block;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(ADC) : Same mode(%d)\n", mode);
		}
		else
		{
			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(ADC) : block = %d, mode = %d\n", block, mode);

			//update power block mode
			gADECPowerStatus_L9A0[LX_AUD_POWER_ADC].mode = mode;

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

				VPORT_I2C_Read((UINT32 *)&gsoft_reset_4);
				gsoft_reset_4.swrst_auad = 1;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4);
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

				VPORT_I2C_Read((UINT32 *)&gsoft_reset_4);
				gsoft_reset_4.swrst_auad = 0;
				VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

				udelay(MIXEDIP_POWER_OFF_DELAY); 	//Spec. => 1 us
			}
		}
	}


	//LX_AUD_POWER_HPDRV
	if(block == LX_AUD_POWER_HPDRV)
	{
		if( (gADECPowerStatus_L9A0[LX_AUD_POWER_HPDRV].block == block)
		  &&(gADECPowerStatus_L9A0[LX_AUD_POWER_HPDRV].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9A0[LX_AUD_POWER_HPDRV].block = block;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(HPD) : Same mode(%d)\n", mode);
		}
		else
		{
			//update power block mode
			gADECPowerStatus_L9A0[LX_AUD_POWER_HPDRV].mode = mode;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(HPD) : block = %d, mode = %d\n", block, mode);

			if (mode == LX_AUD_POWER_UP)
			{
				VPORT_I2C_Read((UINT32 *)&gafe_hp_drv_4);
				gafe_hp_drv_4.hp_pll_pdb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_hp_drv_4);
				msleep_interruptible(HP_PDB_DELAY);		//Spec. => 40ms

				VPORT_I2C_Read((UINT32 *)&gafe_hp_drv_4);
				gafe_hp_drv_4.hp_ana_pdb = 1;
				VPORT_I2C_Write((UINT32*)&gafe_hp_drv_4);
			}
			else
			{
				VPORT_I2C_Read((UINT32 *)&gafe_hp_drv_4);
				gafe_hp_drv_4.hp_ana_pdb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_hp_drv_4);
				msleep_interruptible(HP_PDB_DELAY);		//Spec. => 40ms

				VPORT_I2C_Read((UINT32 *)&gafe_hp_drv_4);
				gafe_hp_drv_4.hp_pll_pdb = 0;
				VPORT_I2C_Write((UINT32*)&gafe_hp_drv_4);
			}
		}
	}


	//LX_AUD_POWER_DAC
	if(block == LX_AUD_POWER_DAC)
	{
		if( (gADECPowerStatus_L9A0[LX_AUD_POWER_DAC].block == block)
		  &&(gADECPowerStatus_L9A0[LX_AUD_POWER_DAC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9A0[LX_AUD_POWER_DAC].block = block;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(DAC) : Same mode(%d)\n", mode);
		}
		else
		{
			//update power block mode
			gADECPowerStatus_L9A0[LX_AUD_POWER_DAC].mode = mode;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(DAC) : block = %d, mode = %d\n", block, mode);

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

#if 0
				/* CTR69 ==> Read  FLushing : Shadow <- Real. */
				CTOP_CTRL_B0_RdFL(ctr69);
				AUD_KDRV_MIP_DEBUG("RD : CTR69 : 0x%8X\n", CTOP_CTRL_B0_Rd(ctr69));

				CTOP_CTRL_B0_Wr01(ctr69, aud_pdb_ldrv_in,		 0b1);	// 1 bit : SCART0 output power down control : Power-Up

				/* Write FLushing : Shadow -> Real. */
				AUD_KDRV_MIP_DEBUG("	 CTR69 : 0x%8X\n", CTOP_CTRL_B0_Rd(ctr69));
				CTOP_CTRL_B0_WrFL(ctr69);

				udelay(AUDA_PDB_DSE_DELAY);		//Spec. => 40 us
#endif
			}
			else
			{
#if 0
				/* CTR69 ==> Read  FLushing : Shadow <- Real. */
				CTOP_CTRL_B0_RdFL(ctr69);
				AUD_KDRV_MIP_DEBUG("RD : CTR69 : 0x%8X\n", CTOP_CTRL_B0_Rd(ctr69));

				CTOP_CTRL_B0_Wr01(ctr69, aud_pdb_ldrv_in,		 0b1);	// 1 bit : SCART0 output power down control : Power-Up

				/* Write FLushing : Shadow -> Real. */
				AUD_KDRV_MIP_DEBUG("	 CTR69 : 0x%8X\n", CTOP_CTRL_B0_Rd(ctr69));
				CTOP_CTRL_B0_WrFL(ctr69);

				udelay(AUDA_PDB_DSE_DELAY);		//Spec. => 40 us
#endif

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
		if( (gADECPowerStatus_L9A0[LX_AUD_POWER_MIC].block == block)
		  &&(gADECPowerStatus_L9A0[LX_AUD_POWER_MIC].mode  == mode ) )
		{
			//update power block
			gADECPowerStatus_L9A0[LX_AUD_POWER_MIC].block = block;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(MIC) : Same mode(%d)\n", mode);
		}
		else
		{
			//update power block mode
			gADECPowerStatus_L9A0[LX_AUD_POWER_MIC].mode = mode;

			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_PowerControl(MIC) : block = %d, mode = %d\n", block, mode);

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

	return RET_OK;
}

/**
 * Start the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_StartCodec ( void )
{
	//Setting Mixed IP
	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_L9_StartCodec : Start\n");

	L9A0_ANALOG_WriteRegister(0x1D, 0x00, 0x7C);
	L9A0_ANALOG_WriteRegister(0x1D, 0x01, 0x18);		//0x18(JK1603),  0x19(JK3302)
	L9A0_ANALOG_WriteRegister(0x1D, 0x02, 0x1b);
	L9A0_ANALOG_WriteRegister(0x1D, 0x03, 0x7C);
	L9A0_ANALOG_WriteRegister(0x1D, 0x07, 0x30);
	L9A0_ANALOG_WriteRegister(0x1D, 0x09, 0x20);
	L9A0_ANALOG_WriteRegister(0x1D, 0x0A, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x10, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x13, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x14, 0x06);
	L9A0_ANALOG_WriteRegister(0x1D, 0x16, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x20, 0x40);
	L9A0_ANALOG_WriteRegister(0x1D, 0x25, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x26, 0x14);
	L9A0_ANALOG_WriteRegister(0x1D, 0x27, 0x06);
	L9A0_ANALOG_WriteRegister(0x1D, 0x28, 0x00);
	L9A0_ANALOG_WriteRegister(0x1D, 0x29, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x2B, 0x40);
	L9A0_ANALOG_WriteRegister(0x1D, 0x2F, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x31, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x32, 0x00);

	/* Wait for soft start */
	msleep_interruptible(50);	//40ms

	L9A0_ANALOG_WriteRegister(0x1D, 0x0A, 0x03);
	L9A0_ANALOG_WriteRegister(0x1D, 0x14, 0x02);
	L9A0_ANALOG_WriteRegister(0x1D, 0x27, 0x02);

	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_StartUpCodec : Done\n");

	return RET_OK;
}

/**
 * Stop the Mixed IP ADC, MIC ADC, DAC and HP module to mute off.(only upper L8 B0 Chip)
 * @see ADEC_L9_InitModule
*/
int L9A0_MIXED_IP_ADEC_L9_StopCodec ( void )
{
	AUD_KDRV_DEBUG_TMP("MIXED_IP_ADEC_DRV_StopCodec : Not Implemented!!!\n");

	return RET_OK;
}

/**
 * Sets a ADC port number for ADEC I2S input.
 * @see ADEC_L9_SetSource
*/
int L9A0_MIXED_IP_ADEC_L9_SetADCPortNumber ( UINT8 ui8PortNum )
{
	if(ui8PortNum <= 5) //ui8PortNum 7 is defined for MIC input test
	{
		VPORT_I2C_Read((UINT32 *)&gacodec_39);
		gacodec_39.ladc_mute_ena = 1;
		VPORT_I2C_Write((UINT32*)&gacodec_39);

		/* Wait for pop-noise supression */
		udelay(100);

		VPORT_I2C_Read((UINT32 *)&gsoft_reset_4);
		gsoft_reset_4.swrst_auad = 1;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

		VPORT_I2C_Read((UINT32 *)&gafe_acodec_1);
		gafe_acodec_1.auad_ch_sel = ui8PortNum;
		VPORT_I2C_Write((UINT32*)&gafe_acodec_1);

		udelay(100);

		VPORT_I2C_Read((UINT32 *)&gsoft_reset_4);
		gsoft_reset_4.swrst_auad = 0;
		VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

		udelay(1);

		VPORT_I2C_Read((UINT32 *)&gacodec_39);
		gacodec_39.ladc_mute_ena = 0;
		VPORT_I2C_Write((UINT32*)&gacodec_39);
	}
	else if(ui8PortNum == 6) //ui8PortNum 6 is defined for mute for HDMI /DVI is not connectted.
	{
		VPORT_I2C_Read((UINT32 *)&gacodec_39);
		gacodec_39.ladc_mute_ena = 1;
		VPORT_I2C_Write((UINT32*)&gacodec_39);
	}
#ifdef ENABLE_SCART1_MIC_PORT
	else if(ui8PortNum == 7)
	{
		VPORT_I2C_Read((UINT32 *)&gacodec_47);
		gacodec_47.mute_ena_mic = 0;
		VPORT_I2C_Write((UINT32*)&gacodec_47);
	}
#endif	//#ifdef ENABLE_SCART1_MIC_PORT
	else
	{
		AUD_KDRV_ERROR("MIXED_IP_ADEC_DRV_SetADCPortNumber : ADC Port = %d(Not Supported.)\n", ui8PortNum);
	}

	AUD_KDRV_ERROR("SetADCPortNumber : ADC Port = %d\n", ui8PortNum);
	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetADCPortNumber : ADC Port = %d\n", ui8PortNum);

	return RET_OK;
}

/**
 * Sets the volume of DAC output.
 * @see ADEC_L9_SetDACOutVolume
*/
int L9A0_MIXED_IP_ADEC_L9_SetDACOutVolume ( LX_AUD_DAC_VOL_T stDACOutVol )
{
	UINT8	dac1_mute_ena = 0;

	LX_AUD_OUTPUT_PORT_MUTE_T portMute = {0, FALSE, FALSE, LX_AUD_DAC_NONE};

	//L8 B0 Support Function : DAC0 -> HPDRV, DAC1 -> SCART
	//Set a SCART DAC volume for NICAM : Boost
	if ( stDACOutVol.mode & LX_AUD_DAC_SCART )
	{
		//Save gScartBoostSetted
		gScartBoostGain_L9A0 = stDACOutVol.scartGain;

		//Read SCART mute status for mute sequence
		VPORT_I2C_Read((UINT32*)&gacodec_18);
		dac1_mute_ena = gacodec_18.dac1_mute_ena;

		if(dac1_mute_ena == 0)
		{
			/* Sets a SCART mute On */
			portMute.portNum  = LX_AUD_OUTPUT_DAC0;
			portMute.mode	  = LX_AUD_DAC_MIXEDIP;
			portMute.bHwOnOff = TRUE;
			(void)L9A0_MIXED_IP_ADEC_L9_SetDACOutMute ( portMute );
		}

		VPORT_I2C_Read((UINT32 *)&gacodec_12);
		gacodec_12.dac1_vol_con_1 &= 0x03;		// 2 bit : Line DAC CH1 Volume Control
		gacodec_12.dac1_vol_con_1 |= (stDACOutVol.scartGain << 2);	// 4 bit : Line DAC CH1 Volume Control
		VPORT_I2C_Write((UINT32*)&gacodec_12);

		if(dac1_mute_ena == 0)
		{
			/* Sets a SCART mute Off */
			portMute.bHwOnOff = FALSE;
			(void)L9A0_MIXED_IP_ADEC_L9_SetDACOutMute ( portMute );
		}

		if ( stDACOutVol.mode == LX_AUD_DAC_SCART )
		{
			AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetDACOutVolume : SCART Gain = %d(dac0 = 0x%X, dac1 = 0x%X)\n", stDACOutVol.scartGain, gacodec_3.dac0_vol_con_1, gacodec_12.dac1_vol_con_1);

			return RET_OK;
		}
	}

	//Set a SCART DAC volume : Attunuation
	if ( stDACOutVol.portNum & LX_AUD_OUTPUT_DAC0 )
	{
		VPORT_I2C_Read((UINT32 *)&gacodec_13);
		gacodec_13.dac1_vol_con_0  = (UINT8)(stDACOutVol.hwVolume & 0xFF);	// 8 bit : Line DAC CH1 Volume Control
		VPORT_I2C_Write((UINT32*)&gacodec_13);

		//Check Mute case if gScartBoostGain_L9A0 is set
		if(stDACOutVol.hwVolume == 0x3FF)
		{
			VPORT_I2C_Read((UINT32 *)&gacodec_12);
			gacodec_12.dac1_vol_con_1 = 0x03;		// 2 bit : Line DAC CH1 Volume Control
			VPORT_I2C_Write((UINT32*)&gacodec_12);
		}
		else
		{
			//Check gScartBoostGain_L9A0 value
			if(gScartBoostGain_L9A0)
			{
				VPORT_I2C_Read((UINT32 *)&gacodec_12);
				gacodec_12.dac1_vol_con_1  = (gScartBoostGain_L9A0 << 2);	// 4 bit : Line DAC CH1 Volume Control
				gacodec_12.dac1_vol_con_1 |= (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH1 Volume Control
				VPORT_I2C_Write((UINT32*)&gacodec_12);
			}
			else
			{
				VPORT_I2C_Read((UINT32 *)&gacodec_12);
				gacodec_12.dac1_vol_con_1 &= 0x3C;		// 2 bit : Line DAC CH1 Volume Control
				gacodec_12.dac1_vol_con_1 |= (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH1 Volume Control
				VPORT_I2C_Write((UINT32*)&gacodec_12);
			}
		}

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : SCART(dac1_0 = 0x%X, dac1_1 = 0x%X)\n", gacodec_13.dac1_vol_con_0, gacodec_12.dac1_vol_con_1);
	}

	//Set a HeadPhone DAC volume
	if ( stDACOutVol.portNum & LX_AUD_OUTPUT_DAC2 )
	{
#ifdef ENABLE_HPDRV_PORT
		VPORT_I2C_Read((UINT32 *)&gacodec_23);
		gacodec_23.hp_vol_con_0 = (UINT8)(stDACOutVol.hwVolume & 0xFF);	// 8 bit : HP Driver Volume Control
		VPORT_I2C_Write((UINT32*)&gacodec_23);

		VPORT_I2C_Read((UINT32 *)&gacodec_22);
		gacodec_22.hp_vol_con_1 &= 0x3C;		// 2 bit : HP Driver Volume Control
		gacodec_22.hp_vol_con_1 |= (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : HP Driver  Volume Control
		VPORT_I2C_Write((UINT32*)&gacodec_22);
#endif	//#ifdef ENABLE_HPDRV_PORT

		VPORT_I2C_Read((UINT32 *)&gacodec_4);
		gacodec_4.dac0_vol_con_0 = (UINT8)(stDACOutVol.hwVolume & 0xFF);	// 8 bit : Line DAC CH1 Volume Control
		VPORT_I2C_Write((UINT32*)&gacodec_4);

		VPORT_I2C_Read((UINT32 *)&gacodec_3);
		gacodec_3.dac0_vol_con_1 &= 0x3C;		// 2 bit : Line DAC CH0 Volume Control
		gacodec_3.dac0_vol_con_1 |= (UINT8)((stDACOutVol.hwVolume >> 8) & 0x03);// 2 bit : Line DAC CH1 Volume Control
		VPORT_I2C_Write((UINT32*)&gacodec_3);

		AUD_KDRV_MIP_DEBUG("SetDACOutVolume : HPDRV(dac0_0 = 0x%X, dac0_1 = 0x%X)\n", gacodec_4.dac0_vol_con_0, gacodec_3.dac0_vol_con_1);
	}

	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetDACOutVolume : Port = %d, Volume = 0x%X\n", stDACOutVol.portNum, stDACOutVol.hwVolume);

	return RET_OK;
}

/**
 * Sets the mute of DAC output.
 * @see ADEC_L9_SetOutputPortMute
*/
int L9A0_MIXED_IP_ADEC_L9_SetDACOutMute ( LX_AUD_OUTPUT_PORT_MUTE_T stOutPortMute )
{
	//L9 A0/1 Support Function : DAC0 -> HPDRV, DAC1 -> SCART

	//Set a SCART DAC mute
	if ( stOutPortMute.portNum & LX_AUD_OUTPUT_DAC0 )
	{
		//mute
		if( stOutPortMute.bHwOnOff == TRUE )
		{
			VPORT_I2C_Read((UINT32*)&gacodec_18);
			gacodec_18.dac1_mute_ena = 1;	// 1 bit : Line DAC CH1 Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_18);

			msleep_interruptible(MIXEDIP_RESET_DELAY);

			VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
			gsoft_reset_8.swrst_aclk_mux2 = 1;	//audio codec
			VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

			VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
			gsoft_reset_4.swrst_mclk1 = 1;	//audio codec
			VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

			AUD_KDRV_MIP_DEBUG("SCART : Mute On\n");
		}
		else	//un-mute
		{
			VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
			gsoft_reset_4.swrst_mclk1 = 0;
			VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

			VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
			gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
			VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

			msleep_interruptible(MIXEDIP_RESET_DELAY);

			VPORT_I2C_Read((UINT32*)&gacodec_18);
			gacodec_18.dac1_mute_ena = 0;	// 1 bit : Line DAC CH1 Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_18);

			AUD_KDRV_MIP_DEBUG("SCART : Mute Off\n");
		}
	}

	//Set a HeadPhone DAC mute
	if ( stOutPortMute.portNum & LX_AUD_OUTPUT_DAC2 )
	{
		if( stOutPortMute.bHwOnOff == TRUE )
		{
#ifdef ENABLE_HPDRV_PORT
			VPORT_I2C_Read((UINT32 *)&gacodec_28);
			gacodec_28.hp_mute_ena = 1;		// 1 bit : HP Driver Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_28);

			msleep_interruptible(MIXEDIP_RESET_DELAY);

			VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
			gsoft_reset_4.swrst_hp_drv = 1;
			VPORT_I2C_Write((UINT32*)&gsoft_reset_4);
#endif	//#ifdef ENABLE_HPDRV_PORT

			VPORT_I2C_Read((UINT32*)&gacodec_9);
			gacodec_9.dac0_mute_ena = 1;	// 1 bit : Line DAC CH0 Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_9);

			msleep_interruptible(MIXEDIP_RESET_DELAY);

			VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
			gsoft_reset_8.swrst_aclk_mux2 = 1;	//audio codec
			VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

			VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
			gsoft_reset_4.swrst_mclk0 = 1;	//audio codec
			VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

			AUD_KDRV_MIP_DEBUG("HPDRV : Mute On\n");
		}
		else	//un-mute
		{
#ifdef ENABLE_HPDRV_PORT
			VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
			gsoft_reset_4.swrst_hp_drv = 0;
			VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

			msleep_interruptible(MIXEDIP_RESET_DELAY);

			VPORT_I2C_Read((UINT32 *)&gacodec_28);
			gacodec_28.hp_mute_ena = 0;		// 1 bit : HP Driver Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_28);
#endif	//#ifdef ENABLE_HPDRV_PORT

			VPORT_I2C_Read((UINT32*)&gsoft_reset_4);
			gsoft_reset_4.swrst_mclk0 = 0;
			VPORT_I2C_Write((UINT32*)&gsoft_reset_4);

			VPORT_I2C_Read((UINT32*)&gsoft_reset_8);
			gsoft_reset_8.swrst_aclk_mux2 = 0;	//audio codec
			VPORT_I2C_Write((UINT32*)&gsoft_reset_8);

			msleep_interruptible(MIXEDIP_RESET_DELAY);

			VPORT_I2C_Read((UINT32*)&gacodec_9);
			gacodec_9.dac0_mute_ena = 0;	// 1 bit : Line DAC CH0 Mute Control
			VPORT_I2C_Write((UINT32*)&gacodec_9);

			AUD_KDRV_MIP_DEBUG("HPDRV : Mute Off\n");
		}
	}

	AUD_KDRV_MIP_DEBUG("MIXED_IP_ADEC_DRV_SetDACOutMute : Port = %d, mute = 0x%X\n", stOutPortMute.portNum, stOutPortMute.bHwOnOff);

	return RET_OK;
}


/** @} */




