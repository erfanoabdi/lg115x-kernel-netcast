
/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/

/** @file
 *
 *  driver interface header for aad device. ( used only within kdriver )
 *	aad device will teach you how to make device driver with new platform.
 *
 *  @author		Sudhaher (kanthiraj.s@lge.com)
 *  @version	1.0
 *  @date		2010.02.24
 *
 *  @addtogroup lg1150_aad
 *	@{
 */

#ifndef	_AAD_COREDRV_H_
#define	_AAD_COREDRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/delay.h>
#include <linux/version.h>

#include "debug_util.h"

#include "aad_cfg.h"
#include "aad_kapi.h"
#include "aad_reg.h"

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)
#include <asm/hardware.h> // For Register base address
#else
#include <mach/hardware.h> // For Register base address
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

#define AAD_SIGNAL_QUALITY_DEBUG	//define for signal quality debug enabled
//#define AAD_BAND_DETECT_DEBUG		//define for band detect debug enabled
//#define AAD_ATSC_A2_TASK_DEBUG		//define for band detect debug enabled

//define for constant value
#define DEBUG_MSG_BUFFER_SIZE			50

/* In DVB mode, calls 30ms and in ATSC mode, calls 20ms */
#define DEBUG_MSG_PRINT_TIME_1S			35		/* DVB mode */
#define DEBUG_MSG_PRINT_TIME_2S			70
#define DEBUG_MSG_PRINT_TIME_3S			105
#define DEBUG_MSG_PRINT_TIME_4S			140
#define DEBUG_MSG_PRINT_TIME_5S			175
#define DEBUG_MSG_PRINT_TIME_10S		350
#define DEBUG_MSG_PRINT_TIME			DEBUG_MSG_PRINT_TIME_10S
#define DEBUG_MSG_PRINT_TIME_HALF		(DEBUG_MSG_PRINT_TIME * 2)

//define delay function and time delay
#define	AAD_SIF_TIME_DELAY_MS(a)		msleep_interruptible(a)
#define AAD_SIF_TIME_DELAY_10MS			10

#define M_N_I_ASD_TIMEOUT_DELAY			(100+100)	//M/N, I sound system, +100 means to need more time than THAT spec.
#define B_G_L_ASD_TIMEOUT_DELAY			(300+100)	//B/G, L sound system, +100 means to need more time than THAT spec.
#define D_K_ASD_TIMEOUT_DELAY			(400+100)	//D/K sound system, +100 means to need more time than THAT spec.

#define SIGNAL_QUALITY_DELAY			300			//Signal Quality Delay
#define ERROR_PRINT_DELAY			   1000			//Error Print Delay
#define AAD_REG_READ_DELAY				500			//AAD_SIF_TIME_DELAY_MS

//define for default value
#define CARRIER2_MAGNITUDE_THRESHOLD	0x0AF4		//-24dbFS
#define CARRIER2_QUALITY_THRESHOLD_HI	0x01C0		// 18.xx-dB, equivalent to the value  0x34 for MN2Th-h/l
#define CARRIER2_QUALITY_THRESHOLD_LO	0x80		// 6.03-dB, equivalent to the value  0x10 for MN2Th-h/l
#define ID_MAGNITUDE_THRESHOLD			0x32		// ID Magnitude for A2
#define NICAM_ERROR_AAOS_THD_HI			0x50		// 0x50
#define NICAM_ERROR_AAOS_THD_LO			0x30		// 0x30

//define Mono/stereo check value for KOREA A2 signal
//#define CAR2_MAG_THRES_ATSC_A2			0x0CD0		//-22.5(?)dbFS for Korea(West Door field stream issue)
#define CAR2_MAG_THRES_ATSC_A2			0x0800		//-22.5(?)dbFS for Korea(Ra Sung field stream issue)
#define CAR2_QUAL_THRES_HI_A2			0x01C0		// 18.xx-dB, equivalent to the value  0x34 for MN2Th-h/l
#define CAR2_QUAL_THRES_HI_QC_TEST	    0x0600		// 30.xx(?)-dB
#define CAR2_QUAL_THRES_HI_ILSAN_MAX    0x05FF		// 30.xx(?)-dB for Korea(Ulsan Ilsan-Dong field stream issue)
#define CAR2_QUAL_THRES_HI_ILSAN_MIN    0x0400		// 24.xx(?)-dB for Korea(Ulsan Ilsan-Dong field stream issue)
#define ID_MAG_THRES_ATSC_A2_BIG		0xF8		// ID Magnitude for KOREA A2 Chungnam Asan Field Signal
#define ID_MAG_THRES_HI_ATSC_A2			0x70		// ID Magnitude for KOREA A2 Signal
#define ID_MAG_THRES_LO_ATSC_A2			0x12		// ID Magnitude for KOREA A2 Signal
#define ID_MAG_THRES_HI_ATSC_A2_ILSAN	0x28		// ID Magnitude for KOREA A2 Signal(Ulsan Ilsan-Dong field stream issue)
#define ID_MAG_THRES_LO_ATSC_A2_ILSAN	0x12		// ID Magnitude for KOREA A2 Signal(Ulsan Ilsan-Dong field stream issue)

#define ID_ST_MAG_ZERO_COUNT_ATSC_A2	0x03		// Stereo ID Zero Magnitude count to detect stereo signal for KOREA A2 Signal
#define ID_BI_MAG_ZERO_COUNT_ATSC_A2	0x03		// Bilingual ID Zero Magnitude count to detect stereo signal for KOREA A2 Signal
#define ID_ST_MAG_NONZERO_COUNT_ATSC_A2	0x0A		// Stereo ID Non-Zero Magnitude count to detect normal signal for KOREA A2 Signal,(0x0A:10, 10 * 50 = 500ms), AAD_MONOTOR_TASK_TIMEOUT
#define STATUS_BI_NZ_EXIT_COUNT_ATSC_A2	0x02		// Bilingual Status Non-Zero exit count to detect normal signal for KOREA A2 Signal,(0x02: 2, 2 * 50 = 100ms), AAD_MONOTOR_TASK_TIMEOUT
#define ID_BI_MAG_NONZERO_COUNT_ATSC_A2	0x0A		// Bilingual ID Non-Zero Magnitude count to detect normal signal for KOREA A2 Signal,(0x0A:10, 10 * 50 = 500ms), AAD_MONOTOR_TASK_TIMEOUT


//define Mono/stereo check value for DVB signal
#define CARRIER1_QUAL_AAOS_THD_HI_DVB	0x13		// 0x22
#define CARRIER1_QUAL_AAOS_THD_LO_DVB	0x11		// 0x16
#define NICAM_ERROR_AAOS_THD_HI_DVB		0x30		// 0x50
#define NICAM_ERROR_AAOS_THD_LO_DVB		0x20		// 0x30
#define CARRIER_AVG_FREQ_THD_DVB_BG		0x30		// 0x18
#define ID_MAG_THRES_DVB_A2_BIG			0xF8		// ID Magnitude for Turkey A2 Field Signal
#define ID_MO_CONTINUOUS_COUNT_DK		0x03		// Mono ID continuous count to detect mono signal for PAL D/K Signal
#define ID_ST_CONTINUOUS_COUNT_DK		0x03		// Stereo ID continuous count to detect stereo signal for PAL D/K Signal
#define ID_BI_CONTINUOUS_COUNT_DK		0x03		// Bilingual ID continuous count to detect bilingual signal for PAL D/K Signal


//define Mono/stereo check value for DVB ID(Indonesia)signal
#define CARRIER1_QUAL_AAOS_THD_HI_ID	0x10		// 0x22
#define CARRIER1_QUAL_AAOS_THD_LO_ID	0x0C		// 0x16

//define  Mono/stereo check value for DVB IN(India) signal
#define ID_MAG_THRES_INDIA_0xF8			0xF8		// 0x34

//define  Mono/stereo check value for BTSC signal
#define FM_SUBCARRIER_NOISE_THD_HI_BTSC	0x38		// 0x14
#define FM_SUBCARRIER_NOISE_THD_LO_BTSC	0x20		// 0x0A
#define PILOT_MAG_AAOS_THD_HI_BTSC		0x50		// 0xB0
#define PILOT_MAG_AAOS_THD_LO_BTSC		0x48		// 0x64


//define monitor task
#define AAD_MONOTOR_TASK_NO_TIMEOUT		0xFFFFFFFFFFFFFFFFULL	// Wait infinite time for AAD Monitor Task
#define AAD_MONOTOR_TASK_TIMEOUT		50						// Wait 50 ms for AAD Monitor Task
#define AAD_MONOTOR_TASK_PRINT_TIME		(500/AAD_MONOTOR_TASK_TIMEOUT)	// 0.5 seconds

/**
 * AAD Mono and Stereo State for A2 Signal.
 * This enumeration describes the Mono and Stereo State for A2 Signal.
 *
 */
typedef  enum
{
	LX_AAD_A2_DEFAULT0_STATE	= 0,		///< Default State
	LX_AAD_A2_WAIT1_STATE		= 1,		///< Wait State
	LX_AAD_A2_SEQ2_MONO_STATE	= 2,		///< Mono State(1)
	LX_AAD_A2_SEQ3_ST_STATE		= 3,		///< Stereo State(1)
	LX_AAD_A2_SEQ4_MONO_STATE	= 4,		///< Mono State(2)
} LX_AAD_A2_MONO_ST_STATE_T;


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/**
 * AAD 4.5MHz and 6.5MHz carrier interpretation mode.
 * This enumeration interpretates the 4.5MHz and 6.5MHz carrier.
 *
 */
typedef enum
{
	AAD_ASD_4_5_MHZ		=	0x00,	///< 6.5 MHz Carrier Interpretation
	AAD_ASD_6_5_MHZ		=	0x01,	///< 4.5 MHz Carrier Interpretation
} AAD_ASD_CARRIER_T;

/**
 * AAD MonitorTask Message Status
 * This enumeration describes the AAD monitor task status.
 *
 */
typedef  enum
{
	LX_AAD_TASK_NONE_MSG		= 0,	///< None
	LX_AAD_TASK_START			= 1,	///< Start AAD Monitor Task
	LX_AAD_TASK_STOP			= 2,	///< Stop AAD Monitor Task
} LX_AAD_TASK_MSG_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
/* Audio Register definitions */
extern LX_AAD_REG_CFG_T 		gstAadRegCfg[];
extern LX_AAD_REG_CFG_T 		*pstAadRegCfg;
extern volatile AAD_REG_T		*gpRealRegAAD;
extern AAD_REG_T				*gpRegAAD;


/*----------------------------------------------------------------------------------------
	Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int AAD_SIF_InitModule ( LX_AAD_INIT_TYPE_T eInitType, BOOLEAN bInitialized );
int AAD_SIF_SetHighDeviationMode ( LX_AAD_HIGH_DEV_SET_T eHighDevMode );
int AAD_SIF_SetBandSetup ( LX_AAD_SIF_SOUNDSYSTEM_T eSoundSystem );
int AAD_SIF_SetModeSetup ( LX_AAD_SIF_STANDARD_T eStandard );
int AAD_SIF_SetUserAnalogMode ( LX_ATV_AUDIO_MODE_SET_T eAudioModeSet );
int AAD_SIF_SetThresholdLevel ( LX_AAD_SIF_THRESHOLD_T level );
int AAD_SIF_GetBandDetect ( LX_AAD_SIF_SYSTEM_INFO_T	*pstSystemInfo );
int AAD_SIF_CheckSoundMode ( LX_AAD_SIF_STANDARD_INFO_T *pstStandardInfo );
int AAD_SIF_GetThresholdLevel ( LX_AAD_SIF_THRESHOLD_T	*pLevel );
int AAD_SIF_GetCurAnalogMode ( LX_ATV_AUDIO_MODE_GET_T *pAudioMode );
int AAD_SIF_GetSIFSatus ( BOOLEAN *pSIFStatus );
int AAD_SIF_SetTaskSatus ( BOOLEAN bTaskStatus );
int AAD_SIF_ReadAndWriteReg ( LX_AAD_REG_INFO_T	*pstRegInfo );

int AAD_ASD_WaitEvent_Intrruptible ( UINT32	ui32Timeout );
void AAD_ASD_WakeUp_Interruptible ( void );

int AAD_Monitor_Task( void *i_pvParam );

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _AAD_COREDRV_H_ */

/** @} */


