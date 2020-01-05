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
 *  Linux proc interface for audio device.
 *  audio device will teach you how to make device driver with new platform.
 *
 *  author	wonchang.shin (wonchang.shin@lge.com)
 *  version	0.1
 *  date		2012.05.03
 *  note		Additional information.
 *
 *  @addtogroup lg1150_audio
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
#include <linux/cdev.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <linux/rmap.h>
#include <linux/file.h>		/** < For Audio Memory debug */
#include <linux/syscalls.h>
#include <linux/fcntl.h>

#include <asm/io.h>			/**< For ioremap_nocache */
#include <asm/uaccess.h>
#include "proc_util.h"
#include "debug_util.h"

#include "base_types.h"
#include "base_device.h"

#ifdef INCLUDE_L9_CHIP_KDRV
#include "../base/l9/base_addr_sw_l9.h"
#endif

#include "../base/h13/linux_platform.h"
#include "../base/h13/linux_irqs.h"

#include "os_util.h"
#include "base_drv.h"	//av lipsync semaphore

#include "audio_cfg.h"
#include "audio_drv.h"
#include "audio_reg.h"

//audio codec for DSP 0 and DSP1
#ifndef IC_CERTIFICATION
#include "firmware/multi_codec_h13.h"		// audio codec & decoder for DSP0
#else
#include "firmware/multi_codec_h13_certi.h"		// audio codec & decoder for DSP0
#endif
#include "firmware/multi_se_codec_h13.h" 	// audio post processing & se(sound engine) codec for DSP1

#include "audio_buffer.h"
#include "audio_drv_hal.h"
#include "audio_imc_func.h"
#include "common/adec_common_version.h"

#include "audio_drv_decoder.h"
#include "audio_drv_renderer.h"
#include "audio_drv_master.h"
#include "audio_drv_encoder.h"
#include "audio_drv_capturer.h"
#include "audio_kapi_master.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define AUDIO_IPC_BUF_SIZE			0x18400			// 97Kbytes


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
//define reset module
#define AUD_OPTION_DSP0				0x0		//DSP0 only
#define AUD_OPTION_DSP1				0x1		//DSP1 only
#define AUD_OPTION_AAD				0x2		//AAD Module only
#define AUD_OPTION_OTHERS			0x3		//Except DSP and Power-down
#define AUD_OPTION_ALL				0x4		//All reset

//define DSP Memory Flush Iteration
#define AUD_DSP_FLUSH_ITERATION		10		//loop per 10 us

//define reset delay
#define AUD_RESET_DELAY				 5		//5us
#define AAD_RESET_DELAY				 5		//5us

//define DSP Ready timeout value
#define WAIT_DSP0_READY_TIMEOUT		300		// Wait 300 ms for DSP0 to Ready
#define WAIT_DSP1_READY_TIMEOUT		300		// Wait 300 ms for DSP1 to Ready
#define WAIT_MONOTOR_TASK_TIMEOUT	200		// Wait 200 ms for Monitor Task
#define MONOTOR_TASK_PRINT_TIME		((1000/WAIT_MONOTOR_TASK_TIMEOUT)+1)	// 1.xx seconds
#define DSP_AUTO_RECOVERY_COUNT		  3		// 3 : 200 * 3 = 600 ms for ESD recovery, 2011.11.02 after reset, audio outputs 200ms.
												//QE Spec. is 1 seconds.
#define DSP_MAX_RESET_COUNT			  5

//define for constant value
#define AUD_CODEC_NAME_SIZE			 30

//VDEC H/W Reg. Address for A/V lipsync basetime
#define L9_VDEC_LIPSYNC_REG_MEMBASE		(0xC00038F0)
#define H13_VDEC_LIPSYNC_REG_MEMBASE	(0xC00048F0)
#define VDEC_LIPSYNC_REG_MEMSIZE		(0x10)
VDEC_LIPSYNC_REG_T	*g_pVDEC_LipsyncReg = NULL;	//VDEC H/W Reg. for Lip Sync Control with ADEC H/W Reg.


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
/* define AUDIO register */
volatile LX_AUD_REG_T	*g_pRealRegAud = NULL;
LX_AUD_REG_T			*g_pTempRegAud = NULL;

/* define a audio reset semaphore */
OS_SEM_T	_gAudResetSemaphore;
UINT32 g_DuringReset	=	0;

/* Related to AUDIO event processing */
LX_AUD_EVENT_TYPE_T gAudSetEvent[AUD_DEV_MAX];
LX_AUD_EVENT_TYPE_T gAudGetEvent[AUD_DEV_MAX];
DECLARE_WAIT_QUEUE_HEAD(gAudPollWaitQueue);
DEFINE_SPINLOCK(gAudEventSpinLock);

DECLARE_WAIT_QUEUE_HEAD(AudWaitDsp0Ready);
DECLARE_WAIT_QUEUE_HEAD(AudWaitDsp1Ready);
DECLARE_WAIT_QUEUE_HEAD(Monitor_WaitQ);

LX_AUD_TASK_MSG_T		g_suiWaitQForMonitor;

UINT32	*g_pui32GuardStartVirAddr = NULL;
UINT32	*g_pui32GuardEndVirAddr	  = NULL;
UINT32	*g_pui32DSP0CodecVirAddr  = NULL;
UINT32	*g_pui32DSP1CodecVirAddr  = NULL;

//IPC virtual address (ioremap)
UINT32	*g_pui32IPC_VirAddr 	= NULL;
UINT32	*g_pui32DebugVirAddr	= NULL;
UINT32	*g_pui32SEParamVirAddr  = NULL;

//Audio Monitor Task status for checking DSP latch-up
BOOLEAN	g_bEnableDspMonitor = TRUE;

//adec_module_def.h
/* transration LX_AUD_MOD_TYPE_T => LX_AUD_BUB_IF_IDX */
//if LX_AUD_MOD_TYPE_T is chaned , bufIF_TableLUT should be changed
UINT8	bufIF_TableLUT[LX_AUD_MOD_TYPE_MAX] ;

UINT8 	conTypeL[LX_AUD_BUB_IF_IDX_MAX] = {CONN_TYPE_CPB_ALLOC_L,CONN_TYPE_DPB_ALLOC_L,CONN_TYPE_MPB_ALLOC_L,CONN_TYPE_IECB_ALLOC_L,CONN_TYPE_CAPB_ALLOC_L,CONN_TYPE_NONE};
UINT8 	conTypeR[LX_AUD_BUB_IF_IDX_MAX] = {CONN_TYPE_CPB_ALLOC_R,CONN_TYPE_DPB_ALLOC_R,CONN_TYPE_MPB_ALLOC_R,CONN_TYPE_IECB_ALLOC_R,CONN_TYPE_CAPB_ALLOC_R,CONN_TYPE_NONE};

LX_AUD_BUF_MEM_CFG_S_T * bufIF[] =
{
	(LX_AUD_BUF_MEM_CFG_S_T *)&stCPB,
	(LX_AUD_BUF_MEM_CFG_S_T *)&stDPB,
	(LX_AUD_BUF_MEM_CFG_S_T *)&stMIX,
	(LX_AUD_BUF_MEM_CFG_S_T *)&stIEC,
	(LX_AUD_BUF_MEM_CFG_S_T *)&stCAP,
	(LX_AUD_BUF_MEM_CFG_S_T *)&stENC,
	NULL,
};

LX_AUD_BUF_MEM_CFG_S_T stCPB[] =
{
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_CPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_CPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
};

LX_AUD_BUF_MEM_CFG_S_T stDPB[] =
{
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_DPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_DPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_DPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_DPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
};

LX_AUD_BUF_MEM_CFG_S_T stENC[] =
{
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_ENC_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
};

LX_AUD_BUF_MEM_CFG_S_T stCAP[] =
{
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_CAPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_CAPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct = NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_CAPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
};

LX_AUD_BUF_MEM_CFG_S_T stIEC[] =
{
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_IEC_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_IEC_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},

};



LX_AUD_BUF_MEM_CFG_S_T stMIX[] =
{
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},
	{
		.pWriterReaderStruct 		= NULL,
		.pMemVirBase		= NULL,
		.MemPhyBase			= 0,
		.MemSize			= 0,
		.bufIndexBase		= ADEC_MODULE_MPB_0,
		.pConTypeL		= &conTypeL[0],
		.pConTypeR		= &conTypeR[0],
	},

};

//ADEC KDRV Structure
LX_AUD_KDRV_T	g_AudKdrv =
{
	.bInitDone			= FALSE,
	.soundEngineMask	= 0,

	.LoadCodec   		= TRUE,
	.CopyDSP0   		= TRUE,
	.CopyDSP1 			= TRUE,
	.EnableIMCDBG	  	= FALSE,

	.IsDSP0Reseted 		= 0,
	.IsDSP1Reseted 		= 0,
	.IsDSP0Ready		= 0,
	.IsDSP1Ready		= 0,
};


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
SINT32 AUDIO_SetReset ( UINT8 ui8ResetFlag );
SINT32 AUDIO_ClearReset ( UINT8 ui8ResetFlag );
SINT32 AUDIO_InitReg ( void );
SINT32 AUDIO_InitRegForCheckbit ( void );
SINT32 AUDIO_StallDspToReset ( void );

static SINT32  AUDIO_Create_Interbuf_Writer_N_Reader(
		void **ppWriterStruct, ARM_PROCESSOR_ADAP * bufAdapIf, UINT32 *pMemVirBase,
		UINT32 MemPhyBase, UINT32 MemSize, void *pRegBase, LX_AUD_BUF_IF_TYPE_T type );
SINT32  AUDIO_Create_CPB_Interbuf_WriterForExternel(void);
SINT32  AUDIO_Create_MIX_Interbuf_WriterForExternel(void);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * Initializes the audio module.
 * Audio module shall be initialized itself with pre-defined configuration value.
 * Audio module includes audio codec, post-processing, SPDIF parts
 * @see AUDIO_Init
*/
SINT32 AUDIO_InitModule ( void )
{
	SINT32 ret = RET_OK;

	UINT8	i;
	UINT32	dsp1bresetout;

	DtoCtrlCmdSetDtorate		setDtoRate;
#ifdef USE_DTO_AAD
 	DtoCtrlCmdSetClockType		setClockType;
#endif
	//Initialize a audio event variables.
	for(i = 0; i < AUD_DEV_MAX; i++)
	{
		gAudSetEvent[i].allocDev = AUD_NO_DEV;
		gAudSetEvent[i].eventMsg = LX_AUD_EVENT_MASK_NONE;

		gAudGetEvent[i].allocDev = AUD_NO_DEV;
		gAudGetEvent[i].eventMsg = LX_AUD_EVENT_MASK_NONE;
	}

	//ioremap audio memorys
	AUDIO_IOREMAP();

	//Resets the Clock Source and Mixed IP Registers.
	(void)MIXED_IP_AUDIO_SetClockSource( LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_CLOCK_DTV, LX_AUD_MASTER_SPDIF_ES );

	//Check a DSP1 reset value for in boot code
	AUD_RdFL(aud_swreset);
	AUD_Rd01(aud_swreset, dsp1bresetout, dsp1bresetout);	//13 dsp1bresetout : reset for DSP1

	//Reset Low : ADEC DSP1 : In boot code, DSP1 is running, so DSP1 memory data must be flushed.
	if(dsp1bresetout == 0x1)
	{
		AUD_KDRV_DEBUG("Flush a DSP1 Firmware Image!!!\n");

		g_AudKdrv.IsDSP1Reseted = 1;
		AUDIO_ClearReset(AUD_OPTION_DSP1);
	}

	//Clear DSP 0 /1 State
	g_AudKdrv.IsDSP0Reseted = 0;
	g_AudKdrv.IsDSP1Reseted = 0;

	//Reset Low : APB, SRC, ADEC DSP and AAD etc...
	AUDIO_ClearReset(AUD_OPTION_ALL);

	//Initializes the Mixed IP Registers.
	(void)MIXED_IP_AUDIO_InitCodecRegisters();

	//Reset High : APB, SRC and Mixed IP etc...
	(void)AUDIO_SetReset(AUD_OPTION_OTHERS);

	// Initialize register
	(void)AUDIO_InitReg();

	// Initialize register for check bit because DSP does not read reg. when CPU access reg.
	(void)AUDIO_InitRegForCheckbit();

	// Initialize IMC & IPC DBUG Module.
	AUDIO_IMC_Init();
	AUDIO_IPC_DBG_Init();

	//Load DSP1 codec for audio processing
	ret = AUDIO_LoadDSP1Codec();
	if (ret != RET_OK)
	{
		AUD_KDRV_ERROR("error in ADEC_L9_LoadDSP1Codec call\n");
		return RET_ERROR;
	}

	// Load DSP0 image
	ret = AUDIO_LoadDSP0Codec();
	if (ret != RET_OK)
	{
		AUD_KDRV_ERROR("error in AUDIO_LoadDSP0Codec call\n");
		return RET_ERROR;
	}
	AUD_KDRV_ERROR("KDRV  CMN Ver. - %02x.%02x.%02x.%c.%02x\n", ADEC_COMMON_VER_MAJOR, ADEC_COMMON_VER_MINOR, ADEC_COMMON_VER_FIX, ADEC_COMMON_VER_FLAG, ADEC_COMMON_VER_EXT);

  	//create buffer interface for DSP module.
	AUDIO_CreateBuffer();

	//Start-up the CODEC IP for mute on.
	(void)MIXED_IP_AUDIO_StartCodec();

  	//Set a DTO Interrupt Source
	MIXED_IP_AUDIO_SetDTOIntSrc(LX_AUD_CLOCK_DTV, LX_AUD_MASTER_SPDIF_ES);

	// Set DTO Clock Type
#ifdef USE_DTO_AAD
	setClockType.clock = AUD_CLOCK_TYPE_AAD;
	AUDIO_IMC_SendCmdParam(DTOCTRL_CMD_SET_CLOCKTYPE, ADEC_MODULE_DTO_A, sizeof(DtoCtrlCmdSetClockType), &setClockType);
#endif

	//Send a IMC command for DTO setting to be changed clock source.
#ifdef USE_DTO_AAD
	setDtoRate.dtorate			= (UINT32)AUD_AAD_RATE_48KHZ_NORMAL;
#else
	setDtoRate.dtorate			= (UINT32)LX_AUD_SPDIF_DTO_NORMAL;
#endif
	setDtoRate.force_cnt_clear	= (UINT32)1;
	AUDIO_IMC_SendCmdParam(DTOCTRL_CMD_SET_DTORATE, ADEC_MODULE_DTO_A, sizeof(DtoCtrlCmdSetDtorate), &setDtoRate);

  	//Start a DTO  DSP Module.
	MIXED_IP_AUDIO_StartDTO(LX_AUD_CLOCK_DTV, LX_AUD_MASTER_SPDIF_ES);

	//Initialize AUDIO RESET semaphore
	OS_InitMutex(&_gAudResetSemaphore, OS_SEM_ATTR_DEFAULT);

	/* Update Internal Status Value */
	g_AudKdrv.bInitDone = TRUE;

#ifdef ENABLE_ADEC_JTAG
	//Enable Wiggler JTAG for Audio DSP connection
	//Check a H13, L9 chip revision
	if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
	{
#ifdef INCLUDE_H13_CHIP_KDRV
#ifdef ENABLE_ADEC_JTAG_FOR_CPU
		CTOP_CTRL_H13B0_RdFL(ctr32);
		CTOP_CTRL_H13B0_Wr01(ctr32, jtag1_sel,	 0x0);	//VDEC, default
		CTOP_CTRL_H13B0_Wr01(ctr32, jtag0_sel,	 0x2);	//0 : CPU,   2 : ADEC
		CTOP_CTRL_H13B0_Wr01(ctr32, aud_jtag_no, 0x1);	//0 : JTAG1, 1 : JTAG0
		CTOP_CTRL_H13B0_WrFL(ctr32);
		AUD_KDRV_PRINT("ENABLE_ADEC_JTAG_FOR_CPU : 0x%X\n", CTOP_CTRL_H13B0_Rd(ctr32));
#else
		CTOP_CTRL_H13B0_RdFL(ctr32);
		CTOP_CTRL_H13B0_Wr01(ctr32, jtag1_sel, 0x2);	//ADEC
		CTOP_CTRL_H13B0_WrFL(ctr32);
		AUD_KDRV_PRINT("ENABLE_ADEC_JTAG_FOR_PERI : 0x%X\n", CTOP_CTRL_H13B0_Rd(ctr32));
#endif
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
	}
	else if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
#ifdef INCLUDE_H13_CHIP_KDRV
#ifdef ENABLE_ADEC_JTAG_FOR_CPU
		CTOP_CTRL_H13A0_RdFL(ctr32);
		CTOP_CTRL_H13A0_Wr01(ctr32, jtag1_sel,	 0x0);	//VDEC, default
		CTOP_CTRL_H13A0_Wr01(ctr32, jtag0_sel,	 0x1);	//0 : CPU,   1 : ADEC
		CTOP_CTRL_H13A0_Wr01(ctr32, aud_jtag_no, 0x1);	//0 : JTAG1, 1 : JTAG0
		CTOP_CTRL_H13A0_WrFL(ctr32);
		AUD_KDRV_PRINT("ENABLE_ADEC_JTAG_FOR_CPU : 0x%X\n", CTOP_CTRL_H13A0_Rd(ctr32));
#else
		CTOP_CTRL_H13A0_RdFL(ctr32);
		CTOP_CTRL_H13A0_Wr01(ctr32, jtag1_sel, 0x2);	//ADEC
		CTOP_CTRL_H13A0_WrFL(ctr32);
		AUD_KDRV_PRINT("ENABLE_ADEC_JTAG_FOR_PERI : 0x%X\n", CTOP_CTRL_H13A0_Rd(ctr32));
#endif
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
#ifdef INCLUDE_L9_CHIP_KDRV
#ifdef ENABLE_ADEC_JTAG_FOR_CPU
		CTOP_CTRL_L9B_RdFL(ctr29_reg_swrst);
		CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst, jtag1_sel,	 0x0);	//VDEC, default
		CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst, jtag0_sel,	 0x1);	//0 : CPU,   1 : ADEC
		CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst, aud_jtag_no, 0x1);	//0 : JTAG1, 1 : JTAG0
		CTOP_CTRL_L9B_WrFL(ctr29_reg_swrst);
		AUD_KDRV_PRINT("ENABLE_ADEC_JTAG_FOR_CPU : 0x%X\n", CTOP_CTRL_L9B_Rd(ctr29_reg_swrst));
#else
		CTOP_CTRL_L9B_RdFL(ctr29_reg_swrst);
		CTOP_CTRL_L9B_Wr01(ctr29_reg_swrst, jtag1_sel, 0x2);	//ADEC
		CTOP_CTRL_L9B_WrFL(ctr29_reg_swrst);
		AUD_KDRV_PRINT("ENABLE_ADEC_JTAG_FOR_PERI : 0x%X\n", CTOP_CTRL_L9B_Rd(ctr29_reg_swrst));
#endif
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
	}
	else
	{
#ifdef INCLUDE_L9_CHIP_KDRV
		CTOP_CTRL_L9_RdFL(ctr29);
		CTOP_CTRL_L9_Wr01(ctr29, jtag_sel, 0x2);
		CTOP_CTRL_L9_WrFL(ctr29);
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
	}
	AUD_KDRV_PRINT("ADEC DSP Wiggler JTAG Selected Now!!!\n");
#endif	//#ifdef ENABLE_ADEC_JTAG

	AUD_KDRV_PRINT("%s : Done!\n", __F__);

	return RET_OK;
}

/**
 * ioremap audio memory
 * @see
*/
SINT32 AUDIO_IOREMAP( void )
{
	SINT32 ret = RET_OK;
	SINT32 i;

	g_pRealRegAud = (volatile LX_AUD_REG_T *)ioremap(pstAudRegCfg->reg_base_addr, pstAudRegCfg->reg_size);
	g_pTempRegAud = (LX_AUD_REG_T *)kmalloc(sizeof(LX_AUD_REG_T), GFP_KERNEL);

	AUD_KDRV_PRINT("pstAudRegCfg->reg_base_addr[%x] pstAudRegCfg->reg_size[%x]\n",pstAudRegCfg->reg_base_addr,pstAudRegCfg->reg_size);

	if(g_pRealRegAud == NULL || g_pTempRegAud == NULL)
	{
		AUD_KDRV_ERROR("ERROR : can't allocate for register\n");
		return -EIO;
	}


	stCPB[0].MemPhyBase 	= pstMemCfgAud->cpb0_memory_base;
	stCPB[1].MemPhyBase 	= pstMemCfgAud->cpb1_memory_base;
	stCPB[0].MemSize 	= pstMemCfgAud->cpb0_memory_size;
	stCPB[1].MemSize 	= pstMemCfgAud->cpb1_memory_size;
	stCPB[0].pRegBase= (void *)&g_pRealRegAud->aud_buf_cpb0_wo;
	stCPB[1].pRegBase= (void *)&g_pRealRegAud->aud_buf_cpb1_wo;

	stDPB[0].MemPhyBase 	= pstMemCfgAud->dpb0_memory_base;
	stDPB[1].MemPhyBase 	= pstMemCfgAud->dpb1_memory_base;
	stDPB[0].MemSize 	= pstMemCfgAud->dpb0_memory_size;
	stDPB[1].MemSize 	= pstMemCfgAud->dpb1_memory_size;
	stDPB[0].pRegBase= (void *)&g_pRealRegAud->aud_buf_dpb0_wo;
	stDPB[1].pRegBase= (void *)&g_pRealRegAud->aud_buf_dpb1_wo;

	stMIX[0].MemPhyBase 	= pstMemCfgAud->mpb0_memory_base;
	stMIX[1].MemPhyBase 	= pstMemCfgAud->mpb1_memory_base;
	stMIX[2].MemPhyBase 	= pstMemCfgAud->mpb2_memory_base;
	stMIX[3].MemPhyBase 	= pstMemCfgAud->mpb3_memory_base;
	stMIX[4].MemPhyBase 	= pstMemCfgAud->mpb4_memory_base;
	stMIX[5].MemPhyBase 	= pstMemCfgAud->mpb5_memory_base;
	stMIX[6].MemPhyBase 	= pstMemCfgAud->mpb6_memory_base;
	stMIX[7].MemPhyBase 	= pstMemCfgAud->mpb7_memory_base;

	stMIX[0].MemSize 	= pstMemCfgAud->mpb0_memory_size;
	stMIX[1].MemSize 	= pstMemCfgAud->mpb1_memory_size;
	stMIX[2].MemSize 	= pstMemCfgAud->mpb2_memory_size;
	stMIX[3].MemSize 	= pstMemCfgAud->mpb3_memory_size;
	stMIX[4].MemSize 	= pstMemCfgAud->mpb4_memory_size;
	stMIX[5].MemSize 	= pstMemCfgAud->mpb5_memory_size;
	stMIX[6].MemSize 	= pstMemCfgAud->mpb6_memory_size;
	stMIX[7].MemSize 	= pstMemCfgAud->mpb7_memory_size;

	stMIX[0].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb0_wo;
	stMIX[1].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb1_wo;
	stMIX[2].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb2_wo;
	stMIX[3].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb3_wo;
	stMIX[4].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb4_wo;
	stMIX[5].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb5_wo;
	stMIX[6].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb6_wo;
	stMIX[7].pRegBase= (void *)&g_pRealRegAud->aud_buf_mpb7_wo;

	stIEC[0].MemPhyBase 	= pstMemCfgAud->iec0_memory_base;
	stIEC[0].MemSize 		= pstMemCfgAud->iec0_memory_size;
	stIEC[0].pRegBase		= (void *)&g_pRealRegAud->aud_buf_iec_wo;

	stIEC[1].MemPhyBase 	= pstMemCfgAud->iec1_memory_base;
	stIEC[1].MemSize 		= pstMemCfgAud->iec1_memory_size;
	stIEC[1].pRegBase		= (void *)&g_pRealRegAud->aud_buf_iec1_wo;

	stCAP[0].MemPhyBase 	= pstMemCfgAud->cap0_memory_base;
	stCAP[1].MemPhyBase 	= pstMemCfgAud->cap1_memory_base;
	stCAP[2].MemPhyBase 	= pstMemCfgAud->cap2_memory_base;

	stCAP[0].MemSize 		= pstMemCfgAud->cap0_memory_size;
	stCAP[1].MemSize 		= pstMemCfgAud->cap1_memory_size;
	stCAP[2].MemSize 		= pstMemCfgAud->cap2_memory_size;

	stCAP[0].pRegBase	= (void *)&g_pRealRegAud->aud_buf_sys_sink0_wo; //
	stCAP[1].pRegBase	= (void *)&g_pRealRegAud->aud_buf_sys_sink1_wo; //
	stCAP[2].pRegBase	= (void *)&g_pRealRegAud->aud_buf_dec_sink1_wo; //

	stENC[0].MemPhyBase 	= pstMemCfgAud->enc_memory_base;
	stENC[0].MemSize 		= pstMemCfgAud->enc_memory_size;
	stENC[0].pRegBase	= (void *)&g_pRealRegAud->aud_buf_dec_sink0_wo;

	// Mapping virtual memory address for guard memory - start/end
	g_pui32GuardStartVirAddr	= (UINT32*) ioremap(pstMemCfgAud->start_memory_base,
												pstMemCfgAud->start_memory_size);
	if (NULL == g_pui32GuardStartVirAddr)
	{
		AUD_KDRV_ERROR ("AUDIO_IOREMAP : Guard(Start) Virtual address ERR!");
		return RET_ERROR;
	}
	AUD_KDRV_PRINT("Guard(Start) memory address-phy [0x%08X]\n", (UINT32) pstMemCfgAud->start_memory_base);
	AUD_KDRV_PRINT("Guard(Start) memory address-virt[0x%08X]\n", (UINT32) g_pui32GuardStartVirAddr);

	g_pui32GuardEndVirAddr		= (UINT32*) ioremap(pstMemCfgAud->end_memory_base,
												pstMemCfgAud->end_memory_size);;
	if (NULL == g_pui32GuardEndVirAddr)
	{
		AUD_KDRV_ERROR("AUDIO_IOREMAP : Guard(End) Virtual address ERR!");
		return RET_ERROR;
	}
	AUD_KDRV_PRINT("Guard(End) memory address-phy [0x%08X]\n", (UINT32) pstMemCfgAud->end_memory_base);
	AUD_KDRV_PRINT("Guard(End) memory address-virt[0x%08X]\n", (UINT32) g_pui32GuardEndVirAddr);
#if 0
	// TODO: Set initial value on guard memory
	// init start guard buffer
	for (i = 0; i < (pstMemCfgAud->start_memory_size >> 2); i++)
		g_pui32GuardStartVirAddr[i] = 0x12345678;
	// init end guard buffer
	for (i = 0; i < (pstMemCfgAud->end_memory_size >> 2); i++)
		g_pui32GuardEndVirAddr[i] = 0x12345678;
#endif

	//Mapping virtual memory address for dsp0 fw download memory
	g_pui32DSP0CodecVirAddr = (UINT32*) ioremap(pstMemCfgAud->fw0_memory_base,
												pstMemCfgAud->fw0_memory_size);
	if (NULL == g_pui32DSP0CodecVirAddr)
	{
		AUD_KDRV_ERROR("AUDIO_LoadCodec : DSP0 Virtual address ERR!");
		return RET_ERROR;
	}
	AUD_KDRV_PRINT("DSP0 CODEC Download address-phy [0x%08X]\n", (UINT32) pstMemCfgAud->fw0_memory_base);
	AUD_KDRV_PRINT("DSP0 CODEC Download address-virt[0x%08X]\n", (UINT32) g_pui32DSP0CodecVirAddr);

	//Mapping virtual memory address for dsp1 fw download memory
	g_pui32DSP1CodecVirAddr = (UINT32*) ioremap(pstMemCfgAud->fw1_memory_base,
												pstMemCfgAud->fw1_memory_size);
	if (NULL == g_pui32DSP1CodecVirAddr)
	{
		AUD_KDRV_ERROR("AUDIO_LoadCodec : DSP1 Virtual address ERR!");
		return RET_ERROR;
	}
	AUD_KDRV_PRINT("DSP1 CODEC Download address-phy [0x%08X]\n", (UINT32) pstMemCfgAud->fw1_memory_base);
	AUD_KDRV_PRINT("DSP1 CODEC Download address-virt[0x%08X]\n", (UINT32) g_pui32DSP1CodecVirAddr);

	// Mapping virtual memory address for CPB buffer
	for(i = 0; i < AUDIO_CPB_MAX; i++)
	{
		//Mapping virtual memory address for CPB0
		stCPB[i].pMemVirBase = (UINT32*) ioremap( stCPB[i].MemPhyBase,stCPB[i].MemSize);
		if (NULL == stCPB[i].pMemVirBase )
		{
			AUD_KDRV_ERROR("%s : CPB[%d] Virtual address ERR!", __F__,i);
			return RET_ERROR;
		}

		AUD_KDRV_PRINT("AUD CPB[%d] address-phy [0x%08X]\n", i,(UINT32) stCPB[i].MemPhyBase);
		AUD_KDRV_PRINT("AUD CPB[%d] address-virt [0x%08X]\n", i,(UINT32) stCPB[i].pMemVirBase);
	}

	// Mapping virtual memory address for DPB buffer
	for(i = 0; i < AUDIO_DPB_MAX; i++)
	{
		//Mapping virtual memory address for DPB0
		stDPB[i].pMemVirBase = (UINT32*) ioremap( stDPB[i].MemPhyBase,stDPB[i].MemSize);
		if (NULL == stDPB[i].pMemVirBase )
		{
			AUD_KDRV_ERROR("%s : DPB[%d] Virtual address ERR!", __F__,i);
			return RET_ERROR;
		}

		AUD_KDRV_PRINT("AUD DPB[%d] address-phy [0x%08X]\n", i,(UINT32) stDPB[i].MemPhyBase);
		AUD_KDRV_PRINT("AUD DPB[%d] address-virt [0x%08X]\n", i,(UINT32) stDPB[i].pMemVirBase);
	}

	// Mapping virtual memory address for DPB buffer
	for(i = 0; i < AUDIO_CAP_MAX; i++)
	{
		//Mapping virtual memory address for DPB0
		stCAP[i].pMemVirBase = (UINT32*) ioremap( stCAP[i].MemPhyBase,stCAP[i].MemSize);
		if (NULL == stCAP[i].pMemVirBase )
		{
			AUD_KDRV_ERROR("%s : CAP[%d] Virtual address ERR!", __F__,i);
			return RET_ERROR;
		}

		AUD_KDRV_PRINT("AUD stCAP[%d] address-phy [0x%08X]\n", i,(UINT32) stCAP[i].MemPhyBase);
		AUD_KDRV_PRINT("AUD stCAP[%d] address-virt [0x%08X]\n", i,(UINT32) stCAP[i].pMemVirBase);
	}

	//Mapping virtual memory address for IEC
	for(i = 0; i < AUDIO_IEC_MAX; i++)
	{
		stIEC[i].pMemVirBase = (UINT32*) ioremap( stIEC[i].MemPhyBase,stIEC[i].MemSize);
		if (NULL == stIEC[i].pMemVirBase )
		{
			AUD_KDRV_ERROR("%s : IEC[%d] Virtual address ERR!", __F__,i);
			return RET_ERROR;
		}
		AUD_KDRV_PRINT("AUD stIEC[%d] address-phy [0x%08X]\n", i,(UINT32) stIEC[i].MemPhyBase);
		AUD_KDRV_PRINT("AUD stIEC[%d] address-virt [0x%08X]\n", i,(UINT32) stIEC[i].pMemVirBase);
	}

	i = 0;
	//Mapping virtual memory address for DPB0
	stENC[i].pMemVirBase = (UINT32*) ioremap( stENC[i].MemPhyBase,stENC[i].MemSize);
	if (NULL == stENC[i].pMemVirBase )
	{
		AUD_KDRV_ERROR ("%s : stENC[%d] Virtual address ERR!", __F__,i);
		return RET_ERROR;
	}

	AUD_KDRV_PRINT("AUD stENC[%d] address-phy [0x%08X]\n", i,(UINT32) stENC[i].MemPhyBase);
	AUD_KDRV_PRINT("AUD stENC[%d] address-virt [0x%08X]\n", i,(UINT32) stENC[i].pMemVirBase);

	// Mapping virtual memory address for MPB buffer
	for(i = 0; i < AUDIO_MIX_MAX; i++)
	{
		//Mapping virtual memory address for MIX0
		stMIX[i].pMemVirBase = (UINT32*) ioremap( stMIX[i].MemPhyBase,stMIX[i].MemSize);
		if (NULL == stMIX[i].pMemVirBase )
		{
			AUD_KDRV_ERROR("%s : MIX[%d] Virtual address ERR!", __F__,i);
			return RET_ERROR;
		}

		AUD_KDRV_PRINT("AUD MIX[%d] address-phy [0x%08X]\n", i,(UINT32) stMIX[i].MemPhyBase);
		AUD_KDRV_PRINT("AUD MIX[%d] address-virt [0x%08X]\n", i,(UINT32) stMIX[i].pMemVirBase);
	}

	//Mapping virtual memory address for sound engine(SE) parameter memory
	g_pui32SEParamVirAddr = (UINT32 *) ioremap(pstMemCfgAud->se_memory_base,
											   pstMemCfgAud->se_memory_size);
	if (NULL == g_pui32SEParamVirAddr)
	{
		AUD_KDRV_ERROR ("AUDIO_LoadCodec : LGSE Param Virtual address ERR!");
		return RET_ERROR;
	}
	AUD_KDRV_PRINT("AUD SE address-phy [0x%08X]\n", (UINT32)pstMemCfgAud->se_memory_base);
	AUD_KDRV_PRINT("AUD SE address-virt[0x%08X]\n", (UINT32)g_pui32SEParamVirAddr);

	// Mapping virtual memory address for IPC
	g_pui32IPC_VirAddr = (UINT32*) ioremap(pstMemCfgAud->ipc_memory_base, pstMemCfgAud->ipc_memory_size);
	if (NULL == g_pui32IPC_VirAddr)
	{
		AUD_KDRV_ERROR("%s : IPC Base address ERR!", __F__);
		return RET_ERROR;
	}
	AUD_KDRV_PRINT("IPC address-phy [0x%08X]\n", (UINT32) pstMemCfgAud->ipc_memory_base);
	AUD_KDRV_PRINT("IPC address-virt[0x%08X]\n", (UINT32) g_pui32IPC_VirAddr);

	// Mapping virtual memory address for debug(reserved) memory
	g_pui32DebugVirAddr	= (UINT32*) ioremap(pstMemCfgAud->debug_memory_base,
												pstMemCfgAud->debug_memory_size);
	if (NULL == g_pui32DebugVirAddr)
	{
		AUD_KDRV_ERROR ("AUDIO_IOREMAP : Debug(Reserved) Virtual address ERR!");
		return RET_ERROR;
	}
	AUD_KDRV_PRINT("Debug(Reserved) memory address-phy [0x%08X]\n", (UINT32) pstMemCfgAud->debug_memory_base);
	AUD_KDRV_PRINT("Debug(Reserved) memory address-virt[0x%08X]\n", (UINT32) g_pui32DebugVirAddr);

	// VDEC's lipsync basetime register
	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		//Mapping virtual memory address for vdec lipsync reg
		g_pVDEC_LipsyncReg = (VDEC_LIPSYNC_REG_T*) ioremap(H13_VDEC_LIPSYNC_REG_MEMBASE,
														   VDEC_LIPSYNC_REG_MEMSIZE);
		if (NULL == g_pVDEC_LipsyncReg)
		{
			AUD_KDRV_ERROR("%s.%d: VDEC Lipsync Reg address ERR!", __FUNCTION__, __LINE__);
			return RET_ERROR;
		}
		AUD_KDRV_PRINT("VDEC Lipsync Reg address-phy [0x%08X]\n", (UINT32) H13_VDEC_LIPSYNC_REG_MEMBASE);
		AUD_KDRV_PRINT("VDEC Lipsync Reg address-virt[0x%08X]\n", (UINT32) g_pVDEC_LipsyncReg);
	}
	else
	{
		//Mapping virtual memory address for vdec lipsync reg
		g_pVDEC_LipsyncReg = (VDEC_LIPSYNC_REG_T*) ioremap(L9_VDEC_LIPSYNC_REG_MEMBASE,
														   VDEC_LIPSYNC_REG_MEMSIZE);
		if (NULL == g_pVDEC_LipsyncReg)
		{
			AUD_KDRV_ERROR("%s.%d: VDEC Lipsync Reg address ERR!", __FUNCTION__, __LINE__);
			return RET_ERROR;
		}
		AUD_KDRV_PRINT("VDEC Lipsync Reg address-phy [0x%08X]\n", (UINT32) L9_VDEC_LIPSYNC_REG_MEMBASE);
		AUD_KDRV_PRINT("VDEC Lipsync Reg address-virt[0x%08X]\n", (UINT32) g_pVDEC_LipsyncReg);
	}

	return ret;
}

/**
 * create audio buffer
 * @see
*/
SINT32 AUDIO_CreateBuffer( void )
{
	SINT32 ret = RET_OK;
	SINT32 i;


	for(i = 0; i < AUDIO_CPB_MAX; i++)
	{
		//Create Mix buffer to protect abnormal operation
		if(stCPB[i].pWriterReaderStruct == NULL)
		{
			/* Create CPB0 for EMP */
			ret = AUDIO_Create_Interbuf_Writer_N_Reader(	\
				  (void *)&stCPB[i].pWriterReaderStruct, (void *)&gCPB_ArmWriterAdap[i], (UINT32 *)stCPB[i].pMemVirBase,	\
				   stCPB[i].MemPhyBase, stCPB[i].MemSize, (void *)stCPB[i].pRegBase, LX_AUD_BUF_IF_TYPE_CPB );
			if(ret == WRITER_RET_OPEN_OK)
			{

				AUD_KDRV_PRINT("ADEC AUD_Create_CPB[%d]_Interbuf_Writer Success!!!\n",i);
			}
			else
			{
				AUD_KDRV_ERROR("ADEC AUD_Create_CPB[%d]_Interbuf_Writer Fail!!!\n",i);
			}
		}
	}

	for(i = 0; i < AUDIO_DPB_MAX; i++)
	{
		//Create Mix buffer to protect abnormal operation
		if(stDPB[i].pWriterReaderStruct == NULL)
		{
			/* Create DPB0 for EMP */
			ret = AUDIO_Create_Interbuf_Writer_N_Reader(	\
				  (void *)&stDPB[i].pWriterReaderStruct, (void *)&gDPB_ArmWriterAdap[i], (UINT32 *)stDPB[i].pMemVirBase,	\
				   stDPB[i].MemPhyBase, stDPB[i].MemSize, (void *)stDPB[i].pRegBase, LX_AUD_BUF_IF_TYPE_DPB );
			if(ret == WRITER_RET_OPEN_OK)
			{

				AUD_KDRV_PRINT("ADEC AUD_Create_DPB[%d]_Interbuf_Writer Success!!!\n",i);
			}
			else
			{
				AUD_KDRV_ERROR("ADEC AUD_Create_DPB[%d]_Interbuf_Writer Fail!!!\n",i);
			}
		}
	}

	for(i = 0; i < AUDIO_MIX_MAX; i++)
	{
		//Create Mix buffer to protect abnormal operation
		if(stMIX[i].pWriterReaderStruct == NULL)
		{
			/* Create MIX0 for EMP */
			ret = AUDIO_Create_Interbuf_Writer_N_Reader(	\
				  (void *)&stMIX[i].pWriterReaderStruct, (void *)&gMIX_ArmWriterAdap[i], (UINT32 *)stMIX[i].pMemVirBase,	\
				   stMIX[i].MemPhyBase, stMIX[i].MemSize, (void *)stMIX[i].pRegBase, LX_AUD_BUF_IF_TYPE_MPB );
			if(ret == WRITER_RET_OPEN_OK)
			{

				AUD_KDRV_PRINT("ADEC AUD_Create_MIX[%d]_Interbuf_Writer Success!!!\n",i);
			}
			else
			{
				AUD_KDRV_ERROR("ADEC AUD_Create_MIX[%d]_Interbuf_Writer Fail!!!\n",i);
			}
		}
	}

	for(i = 0; i < AUDIO_IEC_MAX; i++)
	{
		if(stIEC[i].pWriterReaderStruct == NULL)
		{
			/* Create IEC0 for EMP */
			ret = AUDIO_Create_Interbuf_Writer_N_Reader(	\
				  (void *)&stIEC[i].pWriterReaderStruct, (void *)&gIEC_ArmWriterAdap[i], (UINT32 *)stIEC[i].pMemVirBase,	\
				   stIEC[i].MemPhyBase, stIEC[i].MemSize, (void *)stIEC[i].pRegBase, LX_AUD_BUF_IF_TYPE_IEC );
			if(ret == WRITER_RET_OPEN_OK)
			{

				AUD_KDRV_PRINT("ADEC AUD_Create_IEC[%d]_Interbuf_Writer Success!!!\n",i);
			}
			else
			{
				AUD_KDRV_ERROR("ADEC AUD_Create_IEC[%d]_Interbuf_Writer Fail!!!\n",i);
			}
		}
	}

	for(i = 0; i < AUDIO_CAP_MAX; i++)
	{
		if(stCAP[i].pWriterReaderStruct == NULL)
		{
			/* Create CAP0 for EMP */
			ret = AUDIO_Create_Interbuf_Writer_N_Reader(	\
				  (void *)&stCAP[i].pWriterReaderStruct, (void *)&gCAP_ArmReaderAdap[i], (UINT32 *)stCAP[i].pMemVirBase,	\
				   stCAP[i].MemPhyBase, stCAP[i].MemSize, (void *)stCAP[i].pRegBase, LX_AUD_BUF_IF_TYPE_CAPB );
			if(ret == WRITER_RET_OPEN_OK)
			{

				AUD_KDRV_PRINT("ADEC AUD_Create_CAP[%d]_Interbuf_Writer Success!!!\n",i);
			}
			else
			{
				AUD_KDRV_ERROR("ADEC AUD_Create_CAP[%d]_Interbuf_Writer Fail!!!\n",i);
			}
		}
	}

	return RET_OK;
}
/**
 * Set a reset for ADEC block.
 * @see
*/
SINT32 AUDIO_SetReset ( UINT8 ui8ResetFlag )
{
	AUD_RdFL(aud_swreset);

	if (ui8ResetFlag == AUD_OPTION_DSP0)
	{
		/* Reset g_AudKdrv.IsDSP0Ready value */
		g_AudKdrv.IsDSP0Ready  = 0;

		/* Set DSP0 state after first call */
		g_AudKdrv.IsDSP0Reseted	= 1;

		AUD_Wr01(aud_swreset, dsp0ocdresetout, 1);		//10	dsp0ocdresetout    	reset for On chip debugger of DSP0
		AUD_Wr01(aud_swreset, dsp0bresetout, 1);		 //12	dsp0bresetout      	reset for DSP0
	}
	else if (ui8ResetFlag == AUD_OPTION_DSP1)
	{
		/* Reset g_AudKdrv.IsDSP0Ready value */
		g_AudKdrv.IsDSP1Ready	= 0;

		/* Set DSP1 state after first call */
		g_AudKdrv.IsDSP1Reseted = 1;

		AUD_Wr01(aud_swreset, dsp1ocdresetout, 1);		//11	dsp1ocdresetout    	reset for On chip debugger of DSP1
		AUD_Wr01(aud_swreset, dsp1bresetout, 1);		//13	dsp1bresetout      	reset for DSP1
	}
	else if (ui8ResetFlag == AUD_OPTION_AAD)
	{
		AUD_Wr01(aud_swreset, aadresetout, 1);		//14 	aadresetout        	reset for operation of Analog audio decoder
		AUD_Wr01(aud_swreset, aadapbresetout, 1);	//15 	aadapbresetout     	reset for AAD register interface
	}
	else if (ui8ResetFlag == AUD_OPTION_OTHERS)
	{
		AUD_Wr01(aud_swreset, aresetout, 1);		//0	 	aresetout          	reset for operation of peripherals
		AUD_Wr01(aud_swreset, apbresetout, 1);
	//1	 	apbresetout        	reset for register interface if this set, all registers are cleared
		AUD_Wr01(aud_swreset, aversetout, 1);		//2  	aversetout         	reset for TE data input interface,
		AUD_Wr01(aud_swreset, veresetout, 0);		 //3  	veresetout         	reset for TE data output interface (encoder)
		AUD_Wr01(aud_swreset, fs20resetout, 1);		//4	 	fs20resetout       	reset for audio PCM output interface
		AUD_Wr01(aud_swreset, fs21resetout, 1);		//5		fs21resetout       	reset for audio SPDIF output interface

		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
			AUD_Wr01(aud_swreset, h13_fs23resetout, 1);			//6 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 1);	//7 	fs24resetout		reset for audio HWSRC datat output
			AUD_Wr01(aud_swreset, h13_uartresetout, 1);			//16	 uartresetout			reset for audio UART
		}
		else
		{
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 1);		//7 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs25_l9_fs24resetout, 1);		//8 	fs24resetout		reset for audio HWSRC datat output
		}
		AUD_Wr01(aud_swreset, asrcrstout, 1);		//9	 	asrcrstout         	reset for audio HWSRC operation

		AUD_Wr01(aud_swreset, aadresetout, 1);		//14 	aadresetout        	reest for operation of Analog audio decoder
		AUD_Wr01(aud_swreset, aadapbresetout, 1);	//15 	aadapbresetout     	reset for AAD register interface
	}
	else if (ui8ResetFlag == AUD_OPTION_ALL)
	{
		AUD_Wr01(aud_swreset, aresetout, 1);		//0 	aresetout			reset for operation of peripherals
		AUD_Wr01(aud_swreset, apbresetout, 1);		//1 	apbresetout 		reset for register interface if this set, all registers are cleared
		AUD_Wr01(aud_swreset, aversetout, 1);		//2 	aversetout			reset for TE data input interface,
		AUD_Wr01(aud_swreset, veresetout, 1);		//3 	veresetout			reset for TE data output interface (encoder)
		AUD_Wr01(aud_swreset, fs20resetout, 1);		//4 	fs20resetout		reset for audio PCM output interface
		AUD_Wr01(aud_swreset, fs21resetout, 1);		//5 	fs21resetout		reset for audio SPDIF output interface

		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
			AUD_Wr01(aud_swreset, h13_fs23resetout, 1);			//6 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 1);	//7 	fs24resetout		reset for audio HWSRC datat output
			AUD_Wr01(aud_swreset, h13_uartresetout, 1);			//16	 uartresetout			reset for audio UART
		}
		else
		{
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 1);		//7 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs25_l9_fs24resetout, 1);		//8 	fs24resetout		reset for audio HWSRC datat output
		}

		AUD_Wr01(aud_swreset, asrcrstout, 1);			//9 	asrcrstout			reset for audio HWSRC operation
		AUD_Wr01(aud_swreset, dsp0ocdresetout, 1);		//10	dsp0ocdresetout    	reset for On chip debugger of DSP0
		AUD_Wr01(aud_swreset, dsp1ocdresetout, 1);		//11	dsp1ocdresetout    	reset for On chip debugger of DSP1
		AUD_Wr01(aud_swreset, dsp0bresetout, 1);		//12	dsp0bresetout      	reset for DSP0
		AUD_Wr01(aud_swreset, dsp1bresetout, 1);		//13	dsp1bresetout      	reset for DSP1
		AUD_Wr01(aud_swreset, aadresetout, 1);			//14	aadresetout 		reest for operation of Analog audio decoder
		AUD_Wr01(aud_swreset, aadapbresetout, 1);		//15	aadapbresetout		reset for AAD register interface
	}

	AUD_WrFL(aud_swreset);
	AUD_KDRV_PRINT("Reset reg val [0x%x]\n", AUD_Rd(aud_swreset) );

	//Set delay for reset high duration for stable operation
	if (ui8ResetFlag == AUD_OPTION_DSP0)
	{
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("ADEC_SetReset : AUD_OPTION_DSP0!!!\n");

		//Enable audio interrupt 0
		AUD_Wr(aud_int0_en, 0x1);
		AUD_WrFL(aud_int0_en);
	}
	else if (ui8ResetFlag == AUD_OPTION_DSP1)
	{
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("ADEC_SetReset : AUD_OPTION_DSP1!!!\n");

		//Enable audio interrupt 1
		AUD_Wr(aud_int1_en, 0x1);
		AUD_WrFL(aud_int1_en);
	}
	else if (ui8ResetFlag == AUD_OPTION_AAD)
	{
		udelay(AAD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("ADEC_SetReset : AUD_OPTION_AAD!!!\n");
	}
	else if (ui8ResetFlag == AUD_OPTION_OTHERS)
	{
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("ADEC_SetReset : AUD_OPTION_OTHERS!!!\n");
	}
	else if (ui8ResetFlag == AUD_OPTION_ALL)
	{
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("ADEC_SetReset : AUD_OPTION_ALL!!!\n");
	}

	return RET_OK;
}

/**
 * Clear a reset for AUDIO block.
 * @see
*/
SINT32 AUDIO_ClearReset ( UINT8 ui8ResetFlag )
{
	UINT32		aresetout, apbresetout;
	UINT32		flushDoneStatus = 1, timeout = 0;

	AUD_RdFL(aud_swreset);

	//Check a reset value for in boot code
	//Not reset a adec apb if boot code is reset before to protect a address switch malfunction
	AUD_Rd01(aud_swreset, aresetout, aresetout);		//0 	aresetout			reset for operation of peripherals
	AUD_Rd01(aud_swreset, apbresetout, apbresetout);	//1	apbresetout 		reset for register interface if this set, all registers are cleared

	if (ui8ResetFlag == AUD_OPTION_DSP0)
	{
		//Disable audio interrupt DSP0
		AUD_Wr(aud_int0_en, 0x0);
		AUD_WrFL(aud_int0_en);

		AUD_Wr01(aud_swreset, dsp0ocdresetout, 0);		 //10 dsp0ocdresetout    	reset for On chip debugger of DSP0
		AUD_Wr01(aud_swreset, dsp0bresetout, 0);		//12 dsp0bresetout      	reset for DSP0

	}
	else if (ui8ResetFlag == AUD_OPTION_DSP1)
	{
		//Disable audio interrupt DSP1
		AUD_Wr(aud_int1_en, 0x0);
		AUD_WrFL(aud_int1_en);

		AUD_Wr01(aud_swreset, dsp1ocdresetout, 0);		//11 dsp1ocdresetout    	reset for On chip debugger of DSP1
		AUD_Wr01(aud_swreset, dsp1bresetout, 0);		//13 dsp1bresetout      	reset for DSP1

	}
	else if (ui8ResetFlag == AUD_OPTION_AAD)
	{
		AUD_Wr01(aud_swreset, aadresetout, 0);			//14 aadresetout        	reest for operation of Analog audio decoder
		AUD_Wr01(aud_swreset, aadapbresetout, 0);		//15 aadapbresetout     	reset for AAD register interface
	}
	else if (ui8ResetFlag == AUD_OPTION_OTHERS)
	{
		//This reset is cleared oncely after booting
		if(apbresetout == 0)
			AUD_Wr01(aud_swreset, aresetout, 0);		//0	 aresetout          	reset for operation of peripherals

		//This reset is cleared oncely after booting
		if(apbresetout == 0)
			AUD_Wr01(aud_swreset, apbresetout, 0);		//1	 apbresetout        	reset for register interface if this set, all registers are cleared

		AUD_Wr01(aud_swreset, aversetout, 0);		//2  aversetout         	reset for TE data input interface,
		AUD_Wr01(aud_swreset, veresetout, 0);		//3	 veresetout         	reset for TE data output interface (encoder)

		AUD_Wr01(aud_swreset, fs20resetout, 0);		//4	 fs20resetout       	reset for audio PCM output interface
		AUD_Wr01(aud_swreset, fs21resetout, 0);		//5	 fs21resetout      		reset for audio SPDIF output interface

		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
			AUD_Wr01(aud_swreset, h13_fs23resetout, 0);			//6 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 0);	//7 	fs24resetout		reset for audio HWSRC datat output
			AUD_Wr01(aud_swreset, h13_uartresetout, 0);			//16	 uartresetout			reset for audio UART
		}
		else
		{
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 0);		//7 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs25_l9_fs24resetout, 0);		//8 	fs24resetout		reset for audio HWSRC datat output
		}
		AUD_Wr01(aud_swreset, asrcrstout, 0);		//9	 asrcrstout         	reset for audio HWSRC operation

		AUD_Wr01(aud_swreset, aadresetout, 0);		//14 aadresetout        	reest for operation of Analog audio decoder
		AUD_Wr01(aud_swreset, aadapbresetout, 0);	//15 aadapbresetout     	reset for AAD register interface
	}
	else if (ui8ResetFlag == AUD_OPTION_ALL)
	{
		//This reset is cleared oncely after booting
		if(apbresetout == 0)
			AUD_Wr01(aud_swreset, aresetout, 0);		//0	 aresetout          	reset for operation of peripherals

		//This reset is cleared oncely after booting
		if(apbresetout == 0)
			AUD_Wr01(aud_swreset, apbresetout, 0);		//1	 apbresetout        	reset for register interface if this set, all registers are cleared

		AUD_Wr01(aud_swreset, aversetout, 0);		//2 	aversetout			reset for TE data input interface,
		AUD_Wr01(aud_swreset, veresetout, 0);		//3 	veresetout			reset for TE data output interface (encoder)
		AUD_Wr01(aud_swreset, fs20resetout, 0);		//4 	fs20resetout		reset for audio PCM output interface
		AUD_Wr01(aud_swreset, fs21resetout, 0);		//5 	fs21resetout		reset for audio SPDIF output interface

		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
			AUD_Wr01(aud_swreset, h13_fs23resetout, 0);			//6 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 0);	//7 	fs24resetout		reset for audio HWSRC datat output
			AUD_Wr01(aud_swreset, h13_uartresetout, 0);			//16	 uartresetout			reset for audio UART
		}
		else
		{
			AUD_Wr01(aud_swreset, h13_fs24_l9_fs23resetout, 0);		//7 	fs23resetout		reset for audio HWSRC data input
			AUD_Wr01(aud_swreset, h13_fs25_l9_fs24resetout, 0);		//8 	fs24resetout		reset for audio HWSRC datat output
		}

		AUD_Wr01(aud_swreset, asrcrstout, 0);			//9 	asrcrstout			reset for audio HWSRC operation
		AUD_Wr01(aud_swreset, dsp0ocdresetout, 0);		 //10	dsp0ocdresetout    	reset for On chip debugger of DSP0
		AUD_Wr01(aud_swreset, dsp1ocdresetout, 0);		//11	dsp1ocdresetout    	reset for On chip debugger of DSP1
		AUD_Wr01(aud_swreset, dsp0bresetout, 0);		 //12	dsp0bresetout      	reset for DSP0
		AUD_Wr01(aud_swreset, dsp1bresetout, 0);		 //13	dsp1bresetout      	reset for DSP1
		AUD_Wr01(aud_swreset, aadresetout, 0);			//14	aadresetout 		reest for operation of Analog audio decoder
		AUD_Wr01(aud_swreset, aadapbresetout, 0);		//15	aadapbresetout		reset for AAD register interface
	}

	//Flush AUD DSP memory access
	if (g_AudKdrv.IsDSP0Reseted == 1 && ui8ResetFlag == AUD_OPTION_DSP0)
	{
		g_AudKdrv.IsDSP0Reseted = 0;

		//Stop AUD DSP 0
		AUD_Wr(aud_runstall0, 0x1);
		AUD_WrFL(aud_runstall0);

		//Set flush request register for ADEC DSP0
		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
#ifdef INCLUDE_H13_CHIP_KDRV
			CPU_TOP_H13A0_RdFL(flush_req);
			CPU_TOP_H13A0_Wr01(flush_req, aud_dsp0_flush_en, 0x1);
			CPU_TOP_H13A0_WrFL(flush_req);
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
		}
		else
		{
#ifdef INCLUDE_L9_CHIP_KDRV
			CTOP_CTRL_L9_RdFL(flush_req);
			CTOP_CTRL_L9_Wr01(flush_req, aud_dsp0_flush_en, 0x1);
			CTOP_CTRL_L9_WrFL(flush_req);
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
		}

		AUD_KDRV_DEBUG("Wait for AUD DSP0 Memory Flush!!!\n");

		//Check flush done for DSP0
		for(timeout = 0; timeout < AUD_DSP_FLUSH_ITERATION; timeout++)
		{
			udelay(1);

			//Check a H13, L9 chip revision
			if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
			{
#ifdef INCLUDE_H13_CHIP_KDRV
				CPU_TOP_H13A0_RdFL(flush_done_status);
				CPU_TOP_H13A0_Rd01(flush_done_status, aud_dsp0_flush_done, flushDoneStatus);
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
			}
			else
			{
#ifdef INCLUDE_L9_CHIP_KDRV
				CTOP_CTRL_L9_RdFL(flush_done_status);
				CTOP_CTRL_L9_Rd01(flush_done_status, aud_dsp0_flush_done, flushDoneStatus);
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
			}

			if(flushDoneStatus)
				break;
			else
				AUD_KDRV_DEBUG("Wait for AUD DSP0 Memory Flush!!!\n");
		}

		//Check if timeout is reached
		if(timeout == AUD_DSP_FLUSH_ITERATION)
		{
			AUD_KDRV_DEBUG("CPU_TOP_MAU_FLUSH_DONE_REG : DSP0 ERROR!!!\n");
		}
	}
	else if (g_AudKdrv.IsDSP1Reseted == 1 && ui8ResetFlag == AUD_OPTION_DSP1)
	{
		g_AudKdrv.IsDSP1Reseted	= 0;

		//Stop AUD DSP 1
		AUD_Wr(aud_runstall1, 0x1);
		AUD_WrFL(aud_runstall1);

		//Set flush request register for ADEC DSP1
		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
#ifdef INCLUDE_H13_CHIP_KDRV
			CPU_TOP_H13A0_RdFL(flush_req);
			CPU_TOP_H13A0_Wr01(flush_req, aud_dsp1_flush_en, 0x1);
			CPU_TOP_H13A0_WrFL(flush_req);
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
		}
		else
		{
#ifdef INCLUDE_L9_CHIP_KDRV
			CTOP_CTRL_L9_RdFL(flush_req);
			CTOP_CTRL_L9_Wr01(flush_req, aud_dsp1_flush_en, 0x1);
			CTOP_CTRL_L9_WrFL(flush_req);
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
		}

		AUD_KDRV_DEBUG("Wait for AUD DSP1 Memory Flush!!!\n");

		//Check flush done for DSP1
		for(timeout = 0; timeout < AUD_DSP_FLUSH_ITERATION; timeout++)
		{
			udelay(1);

			//Check a H13, L9 chip revision
			if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
			{
#ifdef INCLUDE_H13_CHIP_KDRV
				CPU_TOP_H13A0_RdFL(flush_done_status);
				CPU_TOP_H13A0_Rd01(flush_done_status, aud_dsp1_flush_done, flushDoneStatus);
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
			}
			else
			{
#ifdef INCLUDE_L9_CHIP_KDRV
				CTOP_CTRL_L9_RdFL(flush_done_status);
				CTOP_CTRL_L9_Rd01(flush_done_status, aud_dsp1_flush_done, flushDoneStatus);
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
			}

			if(flushDoneStatus)
				break;
			else
				AUD_KDRV_DEBUG("Wait for AUD DSP1 Memory Flush!!!\n");

		}

		//Check if timeout is reached
		if(timeout == AUD_DSP_FLUSH_ITERATION)
		{
			AUD_KDRV_DEBUG("CPU_TOP_MAU_FLUSH_DONE_REG : DSP1 ERROR!!!\n");
		}
	}

	AUD_WrFL(aud_swreset);
	AUD_KDRV_PRINT("Reset reg val [0x%x]\n", AUD_Rd(aud_swreset) );

	//Set delay for reset low duration
	if (ui8ResetFlag == AUD_OPTION_DSP0)
	{
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("AUDIO_ClearReset : AUD_OPTION_DSP0!!!\n");
	}
	else if (ui8ResetFlag == AUD_OPTION_DSP1)
	{
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("AUDIO_ClearReset : AUD_OPTION_DSP1!!!\n");
	}
	else if (ui8ResetFlag == AUD_OPTION_AAD)
	{
		udelay(AAD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("AUDIO_ClearReset : AUD_OPTION_AAD!!!\n");
	}
	else if (ui8ResetFlag == AUD_OPTION_OTHERS)
	{
		//msleep_interruptible(6);	//Mixed IP Spec. says 6ms in L8 B0.
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("AUDIO_ClearReset : AUD_OPTION_OTHERS!!!\n");
	}
	else if (ui8ResetFlag == AUD_OPTION_ALL)
	{
		//msleep_interruptible(6);	//Mixed IP Spec. says 2ms in L8 B0.
		udelay(AUD_RESET_DELAY);	//IC => 50 clk : 125ns
		AUD_KDRV_PRINT("AUDIO_ClearReset : AUD_OPTION_ALL!!!\n");
	}

	//Reset Flush Bit for ADEC DSP memory access
	if (g_AudKdrv.IsDSP0Reseted == 0 && ui8ResetFlag == AUD_OPTION_DSP0)
	{
		//Clear flush request register for ADEC DSP0
		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
#ifdef INCLUDE_H13_CHIP_KDRV
			CPU_TOP_H13A0_RdFL(flush_req);
			CPU_TOP_H13A0_Wr01(flush_req, aud_dsp0_flush_en, 0x0);
			CPU_TOP_H13A0_WrFL(flush_req);
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
		}
		else
		{
#ifdef INCLUDE_L9_CHIP_KDRV
			CTOP_CTRL_L9_RdFL(flush_req);
			CTOP_CTRL_L9_Wr01(flush_req, aud_dsp0_flush_en, 0x0);
			CTOP_CTRL_L9_WrFL(flush_req);
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
		}

		AUD_KDRV_PRINT("Reset ADEC DSP0 Memory Flush!!!\n");

		//Start ADEC DSP 0
		g_pRealRegAud->aud_runstall0.aud_runstall0 = 0x0;
	}
	else if (g_AudKdrv.IsDSP1Reseted == 0 && ui8ResetFlag == AUD_OPTION_DSP1)
	{
		//Clear flush request register for ADEC DSP1
		//Check a H13, L9 chip revision
		if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
#ifdef INCLUDE_H13_CHIP_KDRV
			CPU_TOP_H13A0_RdFL(flush_req);
			CPU_TOP_H13A0_Wr01(flush_req, aud_dsp1_flush_en, 0x0);
			CPU_TOP_H13A0_WrFL(flush_req);
#endif	//#ifdef INCLUDE_H13_CHIP_KDRV
		}
		else
		{
#ifdef INCLUDE_L9_CHIP_KDRV
			CTOP_CTRL_L9_RdFL(flush_req);
			CTOP_CTRL_L9_Wr01(flush_req, aud_dsp1_flush_en, 0x0);
			CTOP_CTRL_L9_WrFL(flush_req);
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV
		}

		AUD_KDRV_PRINT("Reset ADEC DSP1 Memory Flush!!!\n");

		//Start ADEC DSP 1
		g_pRealRegAud->aud_runstall1.aud_runstall1 = 0x0;
	}

	return RET_OK;
}

/**
 *  Resets a AAD Module using H/W reset signal.
 *  This function resets a AAD module to clear previous setting.
 * @see
*/
SINT32 AUDIO_ResetAADModule(void)
{
	//Reset Low : AAD Module
	AUDIO_ClearReset(AUD_OPTION_AAD);

	//Reset High : AAD Module
	AUDIO_SetReset(AUD_OPTION_AAD);

	AUD_KDRV_DEBUG("AUDIO_ResetAADModule\n");
	return RET_OK;
}

/**
 * Initialize register
 * @see AUDIO_InitModule
*/
SINT32 AUDIO_InitReg ( void )
{
 	UINT64		start = 0, elapsed = 0;

	LX_ADDR_SW_CFG_T	addrSwCfg;

	//Get a current mili-second time
	start = jiffies;

	//Set download address to ADEC DSP memory
	//set address for DSP0
	AUD_Wr(aud_dsp0offset5, pstMemCfgAud->fw0_memory_base);
	AUD_WrFL(aud_dsp0offset5);

	AUD_Wr(aud_dsp0offset6, pstMemCfgAud->dsp0_memory_base);
	AUD_WrFL(aud_dsp0offset6);

	//Share area for DSP0
	AUD_Wr(aud_dsp0offset61, pstMemCfgAud->dpb0_memory_base);
	AUD_WrFL(aud_dsp0offset61);

	//set address for DSP1
	AUD_Wr(aud_dsp1offset5, pstMemCfgAud->fw1_memory_base);
	AUD_WrFL(aud_dsp1offset5);

	AUD_Wr(aud_dsp1offset6, pstMemCfgAud->dsp1_memory_base);
	AUD_WrFL(aud_dsp1offset6);

	//Share area for DSP1
	AUD_Wr(aud_dsp1offset61, pstMemCfgAud->dpb0_memory_base);
	AUD_WrFL(aud_dsp1offset61);

	AUD_KDRV_DEBUG_TMP("ADEC_RegInit - aud_dsp0offset5[0x%08X]\n", AUD_Rd(aud_dsp0offset5));
	AUD_KDRV_DEBUG_TMP("ADEC_RegInit - aud_dsp0offset6[0x%08X]\n", AUD_Rd(aud_dsp0offset6));
	AUD_KDRV_DEBUG_TMP("ADEC_RegInit - aud_dsp0offset6[0x%08X]\n", AUD_Rd(aud_dsp0offset61));
	AUD_KDRV_DEBUG_TMP("ADEC_RegInit - aud_dsp1offset5[0x%08X]\n", AUD_Rd(aud_dsp1offset5));
	AUD_KDRV_DEBUG_TMP("ADEC_RegInit - aud_dsp1offset6[0x%08X]\n", AUD_Rd(aud_dsp1offset6));
	AUD_KDRV_DEBUG_TMP("ADEC_RegInit - aud_dsp1offset6[0x%08X]\n", AUD_Rd(aud_dsp1offset61));

	//Set ADEC memory table setting(0x02c0 ~ 0x02d4)
	/* Check LX Chip Revision Number */
	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		AUD_KDRV_DEBUG_TMP("H13 Chip is set in CTOP registers.\n");
	}
	else
	{
#ifdef INCLUDE_L9_CHIP_KDRV
		/* initialize L9 memory address switch */
		//address switch setting ADEC0
		(void)BASE_L9_GetAddrSwCfg( ADDR_SW_CFG_AUD0, &addrSwCfg );
#endif	//#ifdef INCLUDE_L9_CHIP_KDRV

		AUD_Wr(memtab0, addrSwCfg.de_sav);
		AUD_WrFL(memtab0);

		AUD_Wr(memtab1, addrSwCfg.cpu_gpu);
		AUD_WrFL(memtab1);

		AUD_Wr(memtab2, addrSwCfg.cpu_shadow);
		AUD_WrFL(memtab2);

		//address switch setting ADEC1
		(void)BASE_L9_GetAddrSwCfg( ADDR_SW_CFG_AUD1, &addrSwCfg );

		AUD_Wr(memtab3, addrSwCfg.de_sav);
		AUD_WrFL(memtab3);

		AUD_Wr(memtab4, addrSwCfg.cpu_gpu);
		AUD_WrFL(memtab4);

		AUD_Wr(memtab5, addrSwCfg.cpu_shadow);
		AUD_WrFL(memtab5);

		AUD_KDRV_DEBUG_TMP ( "ADEC_RegInit - memtab0[0x%08X]\n", AUD_Rd(memtab0));
		AUD_KDRV_DEBUG_TMP ( "ADEC_RegInit - memtab1[0x%08X]\n", AUD_Rd(memtab1));
		AUD_KDRV_DEBUG_TMP ( "ADEC_RegInit - memtab2[0x%08X]\n", AUD_Rd(memtab2));
		AUD_KDRV_DEBUG_TMP ( "ADEC_RegInit - memtab3[0x%08X]\n", AUD_Rd(memtab3));
		AUD_KDRV_DEBUG_TMP ( "ADEC_RegInit - memtab4[0x%08X]\n", AUD_Rd(memtab4));
		AUD_KDRV_DEBUG_TMP ( "ADEC_RegInit - memtab5[0x%08X]\n", AUD_Rd(memtab5));
	}

	//Set base address and size
	AUD_Wr(aud_mem_share_base, pstMemCfgAud->dpb0_memory_base);
	AUD_WrFL(aud_mem_share_base);

	AUD_Wr(aud_mem_dsp0_base, pstMemCfgAud->dsp0_memory_base);
	AUD_WrFL(aud_mem_dsp0_base);

	AUD_Wr(aud_mem_dsp1_base, pstMemCfgAud->dsp1_memory_base);
	AUD_WrFL(aud_mem_dsp1_base);

	//Sound Engine parameters
	AUD_Wr(aud_mem_se_param_base, pstMemCfgAud->se_memory_base);
	AUD_WrFL(aud_mem_se_param_base);
	AUD_Wr(aud_mem_se_param_size, pstMemCfgAud->se_memory_size);
	AUD_WrFL(aud_mem_se_param_size);

	//IPC
	// from ARM to DSP0 (DSP0 - Write: IPC_WRITE_TO_DSP0)
	AUD_Wr(aud_mem_ipc_a2d_base, pstMemCfgAud->ipc_memory_base);
	AUD_WrFL(aud_mem_ipc_a2d_base);
	AUD_Wr(aud_mem_ipc_a2d_size, AUDIO_IPC_BUF_SIZE);
	AUD_WrFL(aud_mem_ipc_a2d_size);

	// from DSP0 to ARM (DSP0 - Read:  IPC_READ_FROM_DSP0)
	AUD_Wr(aud_mem_ipc_d2a_base, pstMemCfgAud->ipc_memory_base + (AUDIO_IPC_BUF_SIZE * 1));
	AUD_WrFL(aud_mem_ipc_d2a_base);
	AUD_Wr(aud_mem_ipc_d2a_size, AUDIO_IPC_BUF_SIZE);
	AUD_WrFL(aud_mem_ipc_d2a_size);

	// from ARM to DSP1 (DSP1 - Write: IPC_WRITE_TO_DSP1)
	AUD_Wr(aud_mem_ipc_a2p_base, pstMemCfgAud->ipc_memory_base + (AUDIO_IPC_BUF_SIZE * 2));
	AUD_WrFL(aud_mem_ipc_a2p_base);
	AUD_Wr(aud_mem_ipc_a2p_size, AUDIO_IPC_BUF_SIZE);
	AUD_WrFL(aud_mem_ipc_a2p_size);

	// from DSP1 to ARM (DSP1 - Read: IPC_READ_FROM_DSP1)
	AUD_Wr(aud_mem_ipc_p2a_base, pstMemCfgAud->ipc_memory_base + (AUDIO_IPC_BUF_SIZE * 3));
	AUD_WrFL(aud_mem_ipc_p2a_base);
	AUD_Wr(aud_mem_ipc_p2a_size, AUDIO_IPC_BUF_SIZE);
	AUD_WrFL(aud_mem_ipc_p2a_size);

	// from DSP0 to DSP1
	AUD_Wr(aud_mem_ipc_d2p_base, pstMemCfgAud->ipc_memory_base + (AUDIO_IPC_BUF_SIZE * 4));
	AUD_WrFL(aud_mem_ipc_d2p_base);
	AUD_Wr(aud_mem_ipc_d2p_size, AUDIO_IPC_BUF_SIZE);
	AUD_WrFL(aud_mem_ipc_d2p_size);

	// from DSP1 to DSP0
	AUD_Wr(aud_mem_ipc_p2d_base, pstMemCfgAud->ipc_memory_base + (AUDIO_IPC_BUF_SIZE * 5));
	AUD_WrFL(aud_mem_ipc_p2d_base);
	AUD_Wr(aud_mem_ipc_p2d_size, AUDIO_IPC_BUF_SIZE);
	AUD_WrFL(aud_mem_ipc_p2d_size);

	// DEBUG - DSP0
	AUD_Wr(aud_mem_ipc_dbgd_base, pstMemCfgAud->ipc_memory_base + (AUDIO_IPC_BUF_SIZE * 6));
	AUD_WrFL(aud_mem_ipc_dbgd_base);
	AUD_Wr(aud_mem_ipc_dbgd_size, (AUDIO_IPC_BUF_SIZE << 1));
	AUD_WrFL(aud_mem_ipc_dbgd_size);

	// DEBUG - DSP1
	AUD_Wr(aud_mem_ipc_dbgp_base, pstMemCfgAud->ipc_memory_base + (AUDIO_IPC_BUF_SIZE * 8));
	AUD_WrFL(aud_mem_ipc_dbgp_base);
	AUD_Wr(aud_mem_ipc_dbgp_size, (AUDIO_IPC_BUF_SIZE << 1));
	AUD_WrFL(aud_mem_ipc_dbgp_size);

	// Basetime of Lipsync
	AUD_Wr(aud_dec0_cbt, 0xFFFFFFFF);	// Init DEC0 Clock Basetime
	AUD_WrFL(aud_dec0_cbt);
	AUD_Wr(aud_dec0_sbt, 0xFFFFFFFF);	// Init DEC0 Stream Basetime
	AUD_WrFL(aud_dec0_sbt);
	AUD_Wr(aud_dec1_cbt, 0xFFFFFFFF);	// Init DEC1 Clock Basetime
	AUD_WrFL(aud_dec1_cbt);
	AUD_Wr(aud_dec1_sbt, 0xFFFFFFFF);	// Init DEC1 Stream Basetime
	AUD_WrFL(aud_dec1_sbt);
	AUD_Wr(aud_basepts, 0xFFFFFFFF);	// Init MHEG Stream Basetime
	AUD_WrFL(aud_basepts);
	AUD_Wr(aud_basestc, 0xFFFFFFFF);	// Init MHEG Clock Basetime
	AUD_WrFL(aud_basestc);

	// Presented PTS at DEC0
	AUD_Wr(aud_presented_pts, 0xFFFFFFFF);	// Init Presented PTS at DEC0
	AUD_WrFL(aud_presented_pts);

	//Get a elapsed nono-second time
	elapsed = jiffies - start;
	AUD_KDRV_DEBUG_TMP("ADEC_RegInit in %d ms.\n", (UINT32)elapsed);

 	return RET_OK;
}

/**
 * Initialize register for check bit
 * @see AUDIO_InitModule
*/
SINT32 AUDIO_InitRegForCheckbit ( void )
{
	UINT32  i, j;

	for(i = 0; i < AUD_BUF_IF_REG_NUM; i++) // i means  wo, ro, wi, ri
	{
		//CPB
		for(j = 0; j < AUDIO_CPB_MAX; j++)
		{
			AUD_WrREG(((UINT32 *) stCPB[j].pRegBase +i), 0xA0000000);
			AUD_KDRV_PRINT("0x%p = [%x]\n",((UINT32 *) stCPB[j].pRegBase + i), AUD_RdREG(((UINT32 *) stCPB[j].pRegBase + i)));
		}
		//DPB
		for(j = 0; j < AUDIO_DPB_MAX; j++)
		{
			AUD_WrREG(((UINT32 *) stDPB[j].pRegBase +i), 0xA0000000);
			AUD_KDRV_PRINT("0x%p = [%x]\n",((UINT32 *) stDPB[j].pRegBase + i), AUD_RdREG(((UINT32 *) stDPB[j].pRegBase + i)));
		}
		//MIX
		for(j = 0; j < AUDIO_MIX_MAX; j++)
		{
			AUD_WrREG(((UINT32 *) stMIX[j].pRegBase +i), 0xA0000000);
			AUD_KDRV_PRINT ("0x%p = [%x]\n",((UINT32 *) stMIX[j].pRegBase + i), AUD_RdREG(((UINT32 *) stMIX[j].pRegBase + i)));
		}

		j = 0;
		AUD_WrREG(((UINT32 *) stIEC[j].pRegBase +i), 0xA0000000);
		AUD_KDRV_PRINT("0x%p = [%x]\n",((UINT32 *) stIEC[j].pRegBase + i), AUD_RdREG(((UINT32 *) stIEC[j].pRegBase + i)));

		AUD_WrREG(((UINT32 *) stENC[j].pRegBase +i), 0xA0000000);
		AUD_KDRV_PRINT("0x%p = [%x]\n",((UINT32 *) stENC[j].pRegBase + i), AUD_RdREG(((UINT32 *) stENC[j].pRegBase + i)));
	}

	//DDCO(SPDIF)
	AUD_Wr(aud_buf_reverse_wo, 0xA0000000);
	AUD_WrFL(aud_buf_reverse_wo);

	AUD_Wr(aud_buf_reverse_ro, 0xA0000000);
	AUD_WrFL(aud_buf_reverse_ro);

	AUD_Wr(aud_buf_reverse_wi, 0xA0000000);
	AUD_WrFL(aud_buf_reverse_wi);

	AUD_Wr(aud_buf_reverse_ri, 0xA0000000);
	AUD_WrFL(aud_buf_reverse_ri);

	//ETC
#if 0 // INCLUDE_H13 20120604_mhhwang BEGIN
	AUD_Wr(aud_sai_gain, 0xA0800000);	//0 dB SAI Input volume gain
	AUD_WrFL(aud_sai_gain);
#endif // INCLUDE_H13 20120604_mhhwang END

	AUD_Wr(aud_ver_dsp0, 0xA0000000);
	AUD_WrFL(aud_ver_dsp0);

	AUD_Wr(aud_ver_dsp1, 0xA0000000);
	AUD_WrFL(aud_ver_dsp1);

	AUD_KDRV_PRINT("ADEC_InitRegForCheckbit\n");
	return RET_OK;
}

/**
 * Stall a audio DSP module to reset.
 * @see
*/
SINT32 AUDIO_StallDspToReset ( void )
{
	//Stop AUD DSP 1
	AUD_Wr(aud_runstall1, 0x1);
	AUD_WrFL(aud_runstall1);

	//Stop AUD DSP 0
	AUD_Wr(aud_runstall0, 0x1);
	AUD_WrFL(aud_runstall0);

	return RET_OK;
}

/**
 * Wait for DSP1 Ready!.
 * @see
*/
void AUDIO_WaitForDSP1Ready ( UINT64 startTick )
{
	UINT8	ext, flag, fix, minor, major;
	UINT32	elapsed;

	UINT32	actionID;
	ImcActionParameter actionParam;

	AUD_KDRV_PRINT("Wait %d ms for DSP1 to Ready!!!\n", WAIT_DSP1_READY_TIMEOUT);
	actionParam.actionType = IMC_ACTION_GET_CALLBACK;
	actionParam.repeatType = IMC_ACTION_ONCE;
	actionParam.target = ADEC_MODULE_MAN_ARM;
	actionParam.actionParam.notiParam.noti = (PFN_ImcNoti)AUDIO_SignalDSP1Ready;
	actionParam.actionParam.notiParam.param = NULL;
	actionParam.actionParam.notiParam.level = 1;
	IMC_RegisterEvent(IMC_GetLocalImc(0), ADEC_EVT_DSP_DN_DONE, ADEC_MODULE_MAN_DSP1, &actionID, &actionParam);

	//Wait if DSP1 is ready
	wait_event_interruptible_timeout(AudWaitDsp1Ready, g_AudKdrv.IsDSP1Ready != 0, msecs_to_jiffies(WAIT_DSP1_READY_TIMEOUT));

	//Get codec version
	AUD_RdFL(aud_ver_dsp1);
	AUD_Rd01(aud_ver_dsp1, ext, ext);
	AUD_Rd01(aud_ver_dsp1, flag, flag);
	AUD_Rd01(aud_ver_dsp1, fix, fix);
	AUD_Rd01(aud_ver_dsp1, minor, minor);
	AUD_Rd01(aud_ver_dsp1, major, major);

	//Get a elapsed tick
	elapsed = (UINT32)(jiffies - startTick);

	if(g_AudKdrv.IsDSP1Ready)
		AUD_KDRV_ERROR("DSP1 MAIN Ver. - %02x.%02x.%02x.%c.%02x - ready time = %d\n", major, minor, fix, flag, ext, elapsed);
	else
		AUD_KDRV_ERROR("DSP1 to Not Ready : DSP1 Ver. Info - %02x.%02x.%02x.%c.%02x - ready time = %d\n", major, minor, fix, flag, ext, elapsed);

	// Get common layer version
	AUD_RdFL(aud_ver_dsp1_common);
	AUD_Rd01(aud_ver_dsp1_common, ext, ext);
	AUD_Rd01(aud_ver_dsp1_common, flag, flag);
	AUD_Rd01(aud_ver_dsp1_common, fix, fix);
	AUD_Rd01(aud_ver_dsp1_common, minor, minor);
	AUD_Rd01(aud_ver_dsp1_common, major, major);
	AUD_KDRV_ERROR("DSP1  CMN Ver. - %02x.%02x.%02x.%c.%02x\n", major, minor, fix, flag, ext);

	return;
}

/**
 * Signal as DSP1 is ready.
 * @see
*/
void AUDIO_SignalDSP1Ready(void* _param, int _paramLen, void* _cbParam)
{
	g_AudKdrv.IsDSP1Ready = 1;
	wake_up_interruptible(&AudWaitDsp1Ready);

	AUD_KDRV_PRINT("AUDIO_SignalDSP1Ready\n");
	return;
}

/**
 * Load a DSP1 codec firmware.
 * @see
*/
SINT32 AUDIO_LoadDSP1Codec ( void )
{
	UINT8		codecName[AUD_CODEC_NAME_SIZE];	//30

	UINT32		ui32CodecSize = 0;
	UINT32		*pui32Codec = NULL;

	UINT64		startTick = 0;

	//Get a current tick time
	startTick = jiffies;

	if(NULL == g_pui32DSP1CodecVirAddr)
	{
		AUD_KDRV_ERROR("ADEC_LoadCodec : Err - g_pui32DSP1CodecVirAddr NULL!\n");
		return RET_ERROR;
	}

	//Reset Low : ADEC DSP1
	AUDIO_ClearReset(AUD_OPTION_DSP1);

	//Clear aud_dsp1_state reg. for codec ver and DSP1 running location
	AUD_RdFL(aud_ver_dsp1);
	AUD_Wr01(aud_ver_dsp1, ext, 0x0);
	AUD_Wr01(aud_ver_dsp1, flag, 0x0);
	AUD_Wr01(aud_ver_dsp1, fix, 0x0);
	AUD_Wr01(aud_ver_dsp1, minor, 0x0);
	AUD_Wr01(aud_ver_dsp1, major, 0x0);
	AUD_WrFL(aud_ver_dsp1);

	//Clear aud_dsp1_state reg. for codec ver and DSP1 running location
	AUD_RdFL(aud_ver_dsp1_common);
	AUD_Wr01(aud_ver_dsp1_common, ext, 0x0);
	AUD_Wr01(aud_ver_dsp1_common, flag, 0x0);
	AUD_Wr01(aud_ver_dsp1_common, fix, 0x0);
	AUD_Wr01(aud_ver_dsp1_common, minor, 0x0);
	AUD_Wr01(aud_ver_dsp1_common, major, 0x0);
	AUD_WrFL(aud_ver_dsp1_common);

	//Load LGSE codec for DSP1
	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		ui32CodecSize = sizeof(se_codec_h13);
		pui32Codec	  = (UINT32 *)se_codec_h13;
		strcpy(codecName, "se_codec_h13");
	}
#if 0
	else
	{
		ui32CodecSize = sizeof(se_codec_l9);
		pui32Codec	  = (UINT32 *)se_codec_l9;
		strcpy(codecName, "se_codec_l9");
	}
#else
	else
	{
		AUD_KDRV_ERROR("[%s] Not Supported Chip Revision\n", __F__);
		return RET_ERROR;
	}
#endif

	AUD_KDRV_DEBUG("ADEC_LoadDSP1 : Started... Codec(%s), Size(%d)\n", codecName, ui32CodecSize);

	if(ui32CodecSize > pstMemCfgAud->fw1_memory_size)
	{
		AUD_KDRV_ERROR("ADEC_LoadCodec : %s size is bigger than memory.(%d > %d)\n",	\
					codecName, ui32CodecSize, pstMemCfgAud->fw1_memory_size);
		return RET_ERROR;
	}

	//Copy codec fw from memory to dsp1 memory
	if(g_AudKdrv.CopyDSP1 == TRUE)
	{
		memcpy(g_pui32DSP1CodecVirAddr, pui32Codec, ui32CodecSize);
		AUD_KDRV_PRINT("ADEC_LoadCodec : Done(%s)!!!\n", codecName );
	}

	//Set DSP1 swreset register
	AUDIO_SetReset(AUD_OPTION_DSP1);

	//Wait for DSP1 fw download completion to DSP1 memory and DSP1 ready
	AUDIO_WaitForDSP1Ready(startTick);

	//Set a current Lip sync , sound engine, SPDIF SCMS and output control mode after dsp auto reset.
	if(g_AudKdrv.bInitDone == TRUE)
	{
		//Set a default sampling frequency and DTO rate after dsp reset
#ifdef USE_DTO_AAD
		(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(LX_AUD_SAMPLING_FREQ_48_KHZ, AUD_AAD_RATE_48KHZ_NORMAL, AUD_DTO_AAD);
#else
		(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(LX_AUD_SAMPLING_FREQ_48_KHZ, LX_AUD_SPDIF_DTO_NORMAL, AUD_DTO_A);
#endif
	}

	AUD_KDRV_PRINT("AUDIO_LoadDSP1Codec\n");
	return RET_OK;
}

/**
 * Wait for DSP0 Ready!.
 * @see
*/

void AUDIO_WaitForDSP0Ready ( UINT64 startTick )
{
	UINT8	ext, flag, fix, minor, major;
	UINT32	elapsed;

	UINT32 actionID;
	ImcActionParameter actionParam;

	AUD_KDRV_PRINT("Wait %d ms for DSP0 to Ready!!!\n", WAIT_DSP0_READY_TIMEOUT);
	actionParam.actionType = IMC_ACTION_GET_CALLBACK;
	actionParam.repeatType = IMC_ACTION_ONCE;
	actionParam.target = ADEC_MODULE_MAN_ARM;
	actionParam.actionParam.notiParam.noti = (PFN_ImcNoti)AUDIO_SignalDSP0Ready;
	actionParam.actionParam.notiParam.param = NULL;
	actionParam.actionParam.notiParam.level = 1;
	IMC_RegisterEvent(IMC_GetLocalImc(0), ADEC_EVT_DSP_DN_DONE, ADEC_MODULE_MAN_DSP0, &actionID, &actionParam);

	//Wait if DSP0 is ready
	wait_event_interruptible_timeout(AudWaitDsp0Ready, g_AudKdrv.IsDSP0Ready != 0, msecs_to_jiffies(WAIT_DSP0_READY_TIMEOUT));

	//Get codec type and version
	AUD_RdFL(aud_ver_dsp0);
	AUD_Rd01(aud_ver_dsp0, ext, ext);
	AUD_Rd01(aud_ver_dsp0, flag, flag);
	AUD_Rd01(aud_ver_dsp0, fix, fix);
	AUD_Rd01(aud_ver_dsp0, minor, minor);
	AUD_Rd01(aud_ver_dsp0, major, major);

	//Get a elapsed tick
	elapsed = (UINT32)(jiffies - startTick);

	if(g_AudKdrv.IsDSP0Ready)
		AUD_KDRV_ERROR("DSP0 MAIN Ver. - %02x.%02x.%02x.%c.%02x - ready time = %d\n", major, minor, fix, flag, ext, elapsed);
	else
		AUD_KDRV_ERROR("DSP0 to Not Ready : DSP0 Ver. Info - %02x.%02x.%02x.%c.%02x - ready time = %d\n", major, minor, fix, flag, ext, elapsed);

	// Get Decoder's Common Layer Version
	AUD_RdFL(aud_ver_dsp0_common);
	AUD_Rd01(aud_ver_dsp0_common, ext, ext);
	AUD_Rd01(aud_ver_dsp0_common, flag, flag);
	AUD_Rd01(aud_ver_dsp0_common, fix, fix);
	AUD_Rd01(aud_ver_dsp0_common, minor, minor);
	AUD_Rd01(aud_ver_dsp0_common, major, major);
	AUD_KDRV_ERROR("DSP0  CMN Ver. - %02x.%02x.%02x.%c.%02x\n", major, minor, fix, flag, ext);

	return;
}


/**
 * Signal as DSP1 is ready.
 * @see
*/
void AUDIO_SignalDSP0Ready(void* _param, int _paramLen, void* _cbParam)
{
	g_AudKdrv.IsDSP0Ready = 1;
	wake_up_interruptible(&AudWaitDsp0Ready);

	AUD_KDRV_PRINT("AUDIO_SignalDSP0Ready\n");
	return;
}

/**
 * Load a DSP0 codec firmware.
 * @see
*/
SINT32 AUDIO_LoadDSP0Codec ( void )
{
	UINT8		codecName[ADEC_CODEC_NAME_SIZE];	//30

	UINT32		ui32CodecSize = 0;
	UINT32		*pui32Codec = NULL;

	UINT64		startTick = 0;

	//Get a current tick time
	startTick = jiffies;

	//Check a fw memory
	if(NULL == g_pui32DSP0CodecVirAddr)
	{
		AUD_KDRV_ERROR("ADEC_LoadCodec : Err - g_pui32DSP0CodecVirAddr NULL!\n");
		return RET_ERROR;
	}

	//Check a current loaded codec.
	if(g_AudKdrv.LoadCodec == FALSE)
	{
		AUD_KDRV_PRINT("ADEC_LoadCodec : Codec already loaded\n");
		return RET_OK;
	}

	//Reset Low : ADEC DSP0
	AUDIO_ClearReset(AUD_OPTION_DSP0);

	//Clear aud_dsp0_state reg.
	AUD_RdFL(aud_ver_dsp0);
	AUD_Wr01(aud_ver_dsp0, ext, 0x0);
	AUD_Wr01(aud_ver_dsp0, flag, 0x0);
	AUD_Wr01(aud_ver_dsp0, fix, 0x0);
	AUD_Wr01(aud_ver_dsp0, minor, 0x0);
	AUD_Wr01(aud_ver_dsp0, major, 0x0);
	AUD_WrFL(aud_ver_dsp0);

	// Clear DSP0's Common Layer Version
	AUD_RdFL(aud_ver_dsp0_common);
	AUD_Wr01(aud_ver_dsp0_common, ext, 0x0);
	AUD_Wr01(aud_ver_dsp0_common, flag, 0x0);
	AUD_Wr01(aud_ver_dsp0_common, fix, 0x0);
	AUD_Wr01(aud_ver_dsp0_common, minor, 0x0);
	AUD_Wr01(aud_ver_dsp0_common, major, 0x0);
	AUD_WrFL(aud_ver_dsp0_common);

	//Set audio codec firmware image
	if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		ui32CodecSize = sizeof(multi_codec_h13);
		pui32Codec	  = (UINT32 *)multi_codec_h13;
		strcpy(codecName, "multi_codec_h13");
	}
#if 0	//temp
	else
	{
		ui32CodecSize = sizeof(multi_codec_l9);
		pui32Codec	  = (UINT32 *)multi_codec_l9;
		strcpy(codecName, "multi_codec_l9");
	}
#else
	else
	{
		AUD_KDRV_ERROR("[%s] Not Supported Chip Revision\n", __F__);
		return RET_ERROR;
	}
#endif

	AUD_KDRV_DEBUG("ADEC_LoadCodec : Started... Codec(%s), Size(%d)\n", codecName, ui32CodecSize);

	if(ui32CodecSize > pstMemCfgAud->fw0_memory_size)
	{
		AUD_KDRV_ERROR("ADEC_LoadCodec : %s size is bigger than memory.(%d > %d)\n",	\
						codecName, ui32CodecSize, pstMemCfgAud->fw0_memory_size);
		return RET_ERROR;
	}

	//Copy codec fw from memory to dsp0 memory
	if(g_AudKdrv.CopyDSP0 == TRUE)
	{
		memcpy(g_pui32DSP0CodecVirAddr, pui32Codec, ui32CodecSize);
		AUD_KDRV_PRINT("ADEC_LoadCodec : Done(%s)!!!\n", codecName );
	}

	AUD_KDRV_DEBUG_TMP("ADEC_LoadCodec : Done(%s)!!!\n", codecName);

	//Set DSP swreset register
	AUDIO_SetReset(AUD_OPTION_DSP0);

	//Wait for DSP fw download completion to DSP memory and DSP ready
	AUDIO_WaitForDSP0Ready(startTick);

	AUD_KDRV_PRINT("KDRV_AUDIO_LoadDSP0Codec is called!!!\n");

	return RET_OK;
}


/**
AUDIO create interbuf writer and reader
*/

static SINT32  AUDIO_Create_Interbuf_Writer_N_Reader(
		void **ppWriterReaderStruct, ARM_PROCESSOR_ADAP * bufAdapIf, UINT32 *pMemVirBase,
		UINT32 MemPhyBase, UINT32 MemSize, void *pRegBase, LX_AUD_BUF_IF_TYPE_T  type)
{
	SINT32 ret = WRITER_RET_OPEN_OK;
	UINT32 cpuToDspBasDiff = 0,auiIndexCount = 0, MaxAccessSize = 0 ;
	UINT32 structSize;

	cpuToDspBasDiff 	= CAPB_CPU_TO_DSP_BASE_DIFF;
	switch( type	)
	{
		case LX_AUD_BUF_IF_TYPE_CPB:
			auiIndexCount 	= CPB_AUI_INDEX_COUNT;
			MaxAccessSize	= CPB_MAX_ACCESS_SIZE;
			break;
		case LX_AUD_BUF_IF_TYPE_DPB:
			auiIndexCount 	= DPB_AUI_INDEX_COUNT;
			MaxAccessSize	= DPB_MAX_ACCESS_SIZE;
			break;
		case LX_AUD_BUF_IF_TYPE_MPB:
			auiIndexCount 	= MPB_AUI_INDEX_COUNT;
			MaxAccessSize	= MPB_MAX_ACCESS_SIZE;
			break;
		case LX_AUD_BUF_IF_TYPE_IEC:
			auiIndexCount 	= IEC_AUI_INDEX_COUNT;
			MaxAccessSize	= IEC_MAX_ACCESS_SIZE;
			break;
		case LX_AUD_BUF_IF_TYPE_CAPB:
			auiIndexCount 	= CAPB_AUI_INDEX_COUNT;
			MaxAccessSize	= CAPB_MAX_ACCESS_SIZE;
			break;
		case LX_AUD_BUF_IF_TYPE_ENC:
			break;
		default:
			break;
	}

	//writer
	if(type != LX_AUD_BUF_IF_TYPE_ENC && type != LX_AUD_BUF_IF_TYPE_CAPB)
	{
		if(*ppWriterReaderStruct == NULL)
		{
			*ppWriterReaderStruct = OS_KMalloc(InterBufWriter_GetStructSize());
		}
	}
	//reader
	else
	{
		if(*ppWriterReaderStruct == NULL)
		{
			*ppWriterReaderStruct = OS_KMalloc(InterBufReader_GetStructSize());
		}
	}

	if(type  != LX_AUD_BUF_IF_TYPE_ENC)
	{
		structSize = CommonBuffer_GetStructSize(auiIndexCount);

		//Set a memory address for CPU and DSP
		bufAdapIf->dummyAddr = (unsigned char *)pMemVirBase;
		bufAdapIf->memBase   = (unsigned char *)(MemPhyBase - cpuToDspBasDiff);
		bufAdapIf->memSize   = MemSize;

		//Create buffer for mixer
		ret = CommonBuffer_Create(
		(unsigned char *)((MemPhyBase - cpuToDspBasDiff) + structSize),
		MemSize - structSize,
		MaxAccessSize,
		auiIndexCount,
		(ADEC_PROCESSOR_ADAP_IF_T *)bufAdapIf,
		pMemVirBase,
		NULL);
	}


	switch(type)
	{
		//writer
		case LX_AUD_BUF_IF_TYPE_CPB:
		case LX_AUD_BUF_IF_TYPE_DPB:
		case LX_AUD_BUF_IF_TYPE_MPB:
		case LX_AUD_BUF_IF_TYPE_IEC:
			if(ret != WRITER_RET_OPEN_OK)
			{
				AUD_KDRV_ERROR("ADEC Mix0 CommonBuffer_Create Error(ret = %d)!!!\n", ret);
			}
			else
			{
				ret = InterBufWriter_CreateFromCommonBuffer(
							(ADEC_PROCESSOR_ADAP_IF_T *)(bufAdapIf),
							(void *)pRegBase,
							pMemVirBase,
							*ppWriterReaderStruct);
			}
			break;
		//reader
		case LX_AUD_BUF_IF_TYPE_CAPB:
			if(ret != WRITER_RET_OPEN_OK)
			{
				AUD_KDRV_ERROR("ADEC CommonBuffer_Create Error(ret = %d)!!!\n", ret);
			}

			ret = InterBufReader_CreateFromCommonBuffer(
						(ADEC_PROCESSOR_ADAP_IF_T *)(bufAdapIf),
						(void *)pRegBase,
						pMemVirBase,
						*ppWriterReaderStruct);
			break;
		//reader
		case LX_AUD_BUF_IF_TYPE_ENC:
			ret = InterBufReader_CreateFromCommonBuffer(
						(ADEC_PROCESSOR_ADAP_IF_T *)(bufAdapIf),
						(void *)pRegBase,
						pMemVirBase,
						*ppWriterReaderStruct);
			break;
		default:
			break;
	}

    return ret;
}


/**
AUDIO CPB Memory Map configuration.
*/
SINT32  AUDIO_Create_CPB_Interbuf_WriterForExternel(void)
{
	SINT32 retVal = RET_OK,i = 0;

	for(i = 0; i < AUDIO_CPB_MAX; i++)
	{
		//Create Mix buffer to protect abnormal operation
		if(stCPB[i].pWriterReaderStruct == NULL)
		{
			/* Create CPB0 for EMP */
			retVal = AUDIO_Create_Interbuf_Writer_N_Reader(	\
				  (void *)&stCPB[i].pWriterReaderStruct, (void *)&gCPB_ArmWriterAdap[i], (UINT32 *)stCPB[i].pMemVirBase,	\
				   stCPB[i].MemPhyBase, stCPB[i].MemSize, (void *)stCPB[i].pRegBase, LX_AUD_BUF_IF_TYPE_CPB );
			if(retVal == WRITER_RET_OPEN_OK)
			{

				AUD_KDRV_PRINT("ADEC AUD_Create_CPB[%d]_Interbuf_Writer Success!!!\n",i);
			}
			else
			{

				AUD_KDRV_ERROR("ADEC AUD_Create_CPB[%d]_Interbuf_Writer Fail!!!\n",i);
				return RET_ERROR;
			}
		}
	}

    return retVal;
}

SINT32  AUDIO_Create_MIX_Interbuf_WriterForExternel(void)
{
	SINT32 retVal = RET_OK,i = 0;
	for(i = 0; i < AUDIO_MIX_MAX; i++)
	{
		//Create Mix buffer to protect abnormal operation
		if(stMIX[i].pWriterReaderStruct == NULL)
		{
			/* Create MIX0 for EMP */
			retVal = AUDIO_Create_Interbuf_Writer_N_Reader(	\
				  (void *)&stMIX[i].pWriterReaderStruct, (void *)&gMIX_ArmWriterAdap[i], (UINT32 *)stMIX[i].pMemVirBase,	\
				   stMIX[i].MemPhyBase, stMIX[i].MemSize, (void *)stMIX[i].pRegBase, LX_AUD_BUF_IF_TYPE_MPB );
			if(retVal == WRITER_RET_OPEN_OK)
			{

				AUD_KDRV_PRINT("ADEC AUD_Create_MIX[%d]_Interbuf_Writer Success!!!\n",i);
			}
			else
			{
				AUD_KDRV_ERROR("ADEC AUD_Create_MIX[%d]_Interbuf_Writer Fail!!!\n",i);
				retVal = RET_ERROR;
			}
		}
	}

    return retVal;
}
/**
 * show ioremap audio memory for debug
 * @see
*/
void AUDIO_ShowIoremap( void )
{
	SINT32 i;

	AUD_KDRV_ERROR ( "\n");
	AUD_KDRV_ERROR ( "GUARD-START [0x%08X:0x%08X]\n", (UINT32) g_pui32GuardStartVirAddr, (UINT32)pstMemCfgAud->start_memory_base);
	AUD_KDRV_ERROR ( "DSP0        [0x%08X:0x%08X]\n", (UINT32) g_pui32DSP0CodecVirAddr, (UINT32)pstMemCfgAud->fw0_memory_base);
	AUD_KDRV_ERROR ( "DSP1        [0x%08X:0x%08X]\n", (UINT32) g_pui32DSP1CodecVirAddr,(UINT32)pstMemCfgAud->fw1_memory_base);

	for(i = 0; i < AUDIO_CPB_MAX; i++)
	{
		AUD_KDRV_ERROR("CPB%d        [0x%08X:0x%08X]\n", i,(UINT32) stCPB[i].pMemVirBase, (UINT32)stCPB[i].MemPhyBase);
	}
	for(i = 0; i < AUDIO_DPB_MAX; i++)
	{
		AUD_KDRV_ERROR("DPB%d        [0x%08X:0x%08X]\n", i,(UINT32) stDPB[i].pMemVirBase, (UINT32)stDPB[i].MemPhyBase);
	}
	for(i = 0; i < AUDIO_MIX_MAX; i++)
	{
		AUD_KDRV_ERROR("MIX%d        [0x%08X:0x%08X]\n", i,(UINT32) stMIX[i].pMemVirBase, (UINT32)stMIX[i].MemPhyBase);
	}
	for(i = 0; i < AUDIO_CAP_MAX; i++)
	{
		AUD_KDRV_ERROR("CAP%d        [0x%08X:0x%08X]\n", i,(UINT32) stCAP[i].pMemVirBase, (UINT32)stCAP[i].MemPhyBase);
	}
	i = 0;
	AUD_KDRV_ERROR("ENC%d        [0x%08X:0x%08X]\n", i,(UINT32) stENC[i].pMemVirBase, (UINT32)stENC[i].MemPhyBase);
	AUD_KDRV_ERROR("IEC%d         [0x%08X:0x%08X]\n", i,(UINT32) stIEC[i].pMemVirBase, (UINT32)stIEC[i].MemPhyBase);

	AUD_KDRV_ERROR("SE          [0x%08X:0x%08X]\n", (UINT32) g_pui32SEParamVirAddr, (UINT32)pstMemCfgAud->se_memory_base);
	AUD_KDRV_ERROR("IPC         [0x%08X:0x%08X]\n", (UINT32) g_pui32IPC_VirAddr, (UINT32)pstMemCfgAud->ipc_memory_base);
	AUD_KDRV_ERROR("RESERVED    [0x%08X:0x%08X]\n", (UINT32) g_pui32DebugVirAddr, (UINT32)pstMemCfgAud->debug_memory_base);
	AUD_KDRV_ERROR("GUARD-END   [0x%08X:0x%08X]\n", (UINT32) g_pui32GuardEndVirAddr, (UINT32)pstMemCfgAud->end_memory_base);
	AUD_KDRV_ERROR("\n");
}

/**
 * show audio memory for debug
 * @see
*/
void AUDIO_ShowMemoryDump( LX_AUD_DEBUG_MEM_DUMP_T *pMemDump )
{
	SINT32 i;
	UINT32 *memAddr = NULL;
	UINT32 address;
	UINT32 line;
	UINT32 type;
	char* fileName;

	address = pMemDump->address;
	line = pMemDump->line;
	type = pMemDump->type;

	if(address < 0x10000000)
	{
		AUD_KDRV_ERROR("address is not valid.\n");
		return;
	}

	memAddr = (UINT32 *)address;

	if(line == 0)
		line = 1;

	if(type == 0)
	{
		AUD_KDRV_ERROR ( "\n");
		AUD_KDRV_ERROR ( "         :    00       04       08       0C       10       14       18       1C\n");
		for(i = 0 ; i < line; i++)
		{
			AUD_KDRV_ERROR ( "%08X : %08X %08X %08X %08X %08X %08X %08X %08X\n", (UINT32)(memAddr + 0x8*i),
				*(memAddr + 0x8*i + 0), *(memAddr + 0x8*i + 1), *(memAddr + 0x8*i + 2), *(memAddr + 0x8*i + 3),
				*(memAddr + 0x8*i + 4), *(memAddr + 0x8*i + 5), *(memAddr + 0x8*i + 6), *(memAddr + 0x8*i + 7));
		}
		AUD_KDRV_ERROR("\n");
	}
	else
	{
		struct file *filp;
		mm_segment_t old_fs = get_fs();

		fileName = &(pMemDump->fileName[0]);

		if(fileName == NULL)
		{
			AUD_KDRV_ERROR("fileName is not valid.\n");
			return;
		}

		set_fs(KERNEL_DS);

		filp = filp_open(fileName, O_WRONLY|O_CREAT, 0644);
		if(IS_ERR(filp))
		{
			AUD_KDRV_ERROR("open error\n(%s)\n", fileName);
			return;
		}
		else
		{
			AUD_KDRV_ERROR("open success(%s)\n", fileName);
		}

		vfs_write(filp, (const char *)memAddr, line*0x20, &filp->f_pos);
		filp_close(filp, NULL);
		set_fs(old_fs);
	}
}

UINT32 AUDIO_ReadDebugMask (void)
{
	UINT32 mask;

	AUD_RdFL(aud_dbg_print_mask);
	mask = AUD_Rd(aud_dbg_print_mask);

	return mask;
}

void AUDIO_WriteDebugMask (unsigned int mask)
{
	AUD_Wr(aud_dbg_print_mask, mask);
	AUD_WrFL(aud_dbg_print_mask);
}

void AUDIO_Restart(void)
{
	UINT8	i;
	ULONG	flags;

	LX_AUD_ALLOC_DEV_T	allocDev = AUD_NO_DEV;

	g_DuringReset = 1;

	//Lock a AUDIO Reset Semaphore
	OS_LockMutex(&_gAudResetSemaphore);

	//Stall a DSP
	(void)AUDIO_StallDspToReset();

	//Unlock a AUDIO Reset Semaphore
	OS_UnlockMutex(&_gAudResetSemaphore);
	OS_LockMutex(&_gAudResetSemaphore);

	//IMC Finalize
	(void)AUDIO_IMC_Finalize();
	(void)AUDIO_IPC_DBG_Finalize();

	//IMC Re-Init
	(void)AUDIO_IMC_Init();
	(void)AUDIO_IPC_DBG_Init();

	//Unlock a AUDIO Reset Semaphore
	OS_UnlockMutex(&_gAudResetSemaphore);
	OS_LockMutex(&_gAudResetSemaphore);

	//Download dsp codec
	(void)AUDIO_LoadDSP1Codec();
	(void)AUDIO_LoadDSP0Codec();

	//Unlock a AUDIO Reset Semaphore
	OS_UnlockMutex(&_gAudResetSemaphore);
	OS_LockMutex(&_gAudResetSemaphore);

	KDRV_AUDIO_ResetCapturer();
	KDRV_AUDIO_ResetEncoder();
	KDRV_AUDIO_ResetDisconnectMaster();
	KDRV_AUDIO_ResetRenderer();
	KDRV_AUDIO_ResetDecoder();
	KDRV_AUDIO_ResetMaster();

	//Unlock a AUDIO Reset Semaphore
	OS_UnlockMutex(&_gAudResetSemaphore);
	OS_LockMutex(&_gAudResetSemaphore);

	KDRV_AUDIO_ResetManagerParam();
	KDRV_AUDIO_ResetMasterParam();
	KDRV_AUDIO_ResetDecoderParam();
	KDRV_AUDIO_ResetRendererParam();
	KDRV_AUDIO_ResetConnectMaster();
	KDRV_AUDIO_ResetEncoderParam();
	KDRV_AUDIO_ResetCapturerParam();

	//Unlock a AUDIO Reset Semaphore
	OS_UnlockMutex(&_gAudResetSemaphore);
	OS_LockMutex(&_gAudResetSemaphore);

	KDRV_AUDIO_RestartMaster();
	KDRV_AUDIO_RestartDecoder();
	KDRV_AUDIO_RestartRenderer();
	KDRV_AUDIO_RestartEncoder();
	KDRV_AUDIO_RestartCapturer();

	//Unlock a AUDIO Reset Semaphore
	OS_UnlockMutex(&_gAudResetSemaphore);

	g_DuringReset = 0;

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Set a audio GET event type for next event.
	for(i = 0; i < AUD_DEV_REN0; i++)
	{
		if(gAudSetEvent[i].allocDev != AUD_NO_DEV)
		{
			gAudGetEvent[i].allocDev  = gAudSetEvent[i].allocDev;
			gAudGetEvent[i].eventMsg |= LX_AUD_EVENT_DSP_RESET;

			allocDev = i;	//Save a last allocated device.
		}
	}

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	//Wake up poll event if allocated device and event message is set.
	if(allocDev != AUD_NO_DEV)
	{
		if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
		  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_DSP_RESET) )
		{
			wake_up_interruptible_all(&gAudPollWaitQueue);
		}
	}

	AUD_KDRV_DEBUG("AUDIO_Restart(allocDev = %d)\n", allocDev);
	return;
}


SINT32 AUDIO_MonitorTask(void *pParam)
{
	//DSP0, DSP1 running counter
	UINT32		ui32CheckDSP0RunningCnt = 0;
	UINT32		ui32CheckDSP1RunningCnt = 0;

	UINT32		ui32Dsp0Timer = 0;
	UINT32		ui32Dsp1Timer = 0;

	UINT32		ui32PreDsp0Timer = 0;
	UINT32		ui32PreDsp1Timer = 0;

	UINT32		ui32DspResetCount = 0;
	UINT32		ui32ResetCount = 0;

	AUD_KDRV_PRINT("Audio Monitor Task is created\n");

	do
	{
		/* Check stop condition when device is closed. */
		if( kthread_should_stop())
		{
			AUD_KDRV_PRINT("Audio Monitor Task - exit!\n");
			break;
		}

		/* Reset a wait queue monitor variable. */
		g_suiWaitQForMonitor = LX_AUD_TASK_NONE_MSG;

		wait_event_interruptible_timeout( Monitor_WaitQ,	\
										  g_suiWaitQForMonitor != LX_AUD_TASK_NONE_MSG,	\
										  msecs_to_jiffies(WAIT_MONOTOR_TASK_TIMEOUT) );	//200 ms

		AUD_KDRV_TRACE("%s(msg = %d)\n", __F__, g_suiWaitQForMonitor);

		////////////////////////////////////
		//Process and Check a DSP 0/1 latch-up status
		if(g_bEnableDspMonitor == TRUE && g_suiWaitQForMonitor == LX_AUD_TASK_NONE_MSG)
		{
			//Update a DSP running check count
			ui32CheckDSP0RunningCnt++;
			ui32CheckDSP1RunningCnt++;

			//Check a DSP0 running status
			AUD_RdFL(aud_dsp0_gstc);
			ui32Dsp0Timer = AUD_Rd(aud_dsp0_gstc);

			if(ui32PreDsp0Timer == ui32Dsp0Timer)
			{
				AUD_KDRV_ERROR("DSP0 Timer not changed : [%d:%d]\n", ui32Dsp0Timer, ui32PreDsp0Timer);
			}
			else
			{
				AUD_KDRV_DEBUG_TMP("DSP0 Timer changed : [%d:%d]\n", ui32Dsp0Timer, ui32PreDsp0Timer);
				ui32CheckDSP0RunningCnt = 0;
			}

			//Check a DSP1 running status
			AUD_RdFL(aud_dsp1_gstc);
			ui32Dsp1Timer = AUD_Rd(aud_dsp1_gstc);

			if(ui32PreDsp1Timer == ui32Dsp1Timer)
			{
				AUD_KDRV_ERROR("DSP1 Timer not changed : [%d:%d]\n", ui32Dsp1Timer, ui32PreDsp1Timer);
			}
			else
			{
				AUD_KDRV_DEBUG_TMP("DSP1 Timer changed : [%d:%d]\n", ui32Dsp1Timer, ui32PreDsp1Timer);
				ui32CheckDSP1RunningCnt = 0;
			}

			//Update a  DSP 0 /1 Timer
			ui32PreDsp0Timer = ui32Dsp0Timer;
			ui32PreDsp1Timer = ui32Dsp1Timer;

			if( (ui32CheckDSP0RunningCnt >= DSP_AUTO_RECOVERY_COUNT)	\
			  ||(ui32CheckDSP1RunningCnt >= DSP_AUTO_RECOVERY_COUNT) )
			{
				AUD_KDRV_ERROR("Reset Audio(count = %d)\n", ui32DspResetCount++);

				//Update DSP0 and DSP1 Reset Counter for debug
				if(ui32PreDsp0Timer == ui32Dsp0Timer && ui32CheckDSP0RunningCnt >= DSP_AUTO_RECOVERY_COUNT)
				{
					AUD_RdFL(aud_dbg_dsp0_reset);
					ui32ResetCount = AUD_Rd(aud_dbg_dsp0_reset);
					AUD_Wr(aud_dbg_dsp0_reset, ui32ResetCount + 1);
					AUD_WrFL(aud_dbg_dsp0_reset);
				}

				if(ui32PreDsp1Timer == ui32Dsp1Timer && ui32CheckDSP1RunningCnt >= DSP_AUTO_RECOVERY_COUNT)
				{
					AUD_RdFL(aud_dbg_dsp1_reset);
					AUD_Rd01(aud_dbg_dsp1_reset, dsp_reset_count, ui32ResetCount);
					AUD_Wr01(aud_dbg_dsp1_reset, dsp_reset_count, ui32ResetCount + 1);
					AUD_WrFL(aud_dbg_dsp1_reset);
				}

				//Restart audio decoder and renderer after DSP H/W Reset
				AUDIO_Restart();

				ui32CheckDSP0RunningCnt = 0;
				ui32CheckDSP1RunningCnt = 0;
			}
		}

		// if Render does not run, redemand decoded notification.
		if(g_bEnableDspMonitor == TRUE && g_suiWaitQForMonitor == LX_AUD_TASK_NONE_MSG)
		{
			KDRV_AUDIO_RedemandDecodedNofiRenderer();
			KDRV_AUDIO_RedemandDecodedNofiEncoder();
		}
	} while (TRUE);

	return 0;
}


