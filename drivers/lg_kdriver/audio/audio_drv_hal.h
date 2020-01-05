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
 *  date		2012.04.24
 *  note		Additional information.
 *
 *  @addtogroup lg1150_audio
 *	@{
 */

#ifndef	_AUDIO_DRV_HAL_H_
#define	_AUDIO_DRV_HAL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include "os_util.h" //for alloc functions

#include "base_types.h"
#include "audio_kapi.h"
#include "audio_reg.h"
#include "audio_drv.h"

#ifdef INCLUDE_H13_CHIP_KDRV
#include "sys_regs.h"	//for ACE TOP CTRL Reg. map
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)
#include <asm/hardware.h> // For Register base address
#else
#include <mach/hardware.h> // For Register base address
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

#define ENABLE_ADEC_JTAG			//Enable ADEC DSP JTAG
//#define ENABLE_ADEC_JTAG_FOR_CPU	//Enable ADEC DSP JTAG for CPU PORT

// define audio buffer number
#define AUD_BUF_IF_REG_NUM				4

// TODO: BASE_DIFF를 모두 하나로 통합해라!!!!
// define CPB / MPB / ENC / CAP buffer enumeration
#define CPB_CPU_TO_DSP_BASE_DIFF		(pstMemCfgAud->dpb0_memory_base - 0x68000000)
#define DPB_CPU_TO_DSP_BASE_DIFF		(pstMemCfgAud->dpb0_memory_base - 0x68000000)
#define MPB_CPU_TO_DSP_BASE_DIFF		(pstMemCfgAud->dpb0_memory_base - 0x68000000)
#define ENC_CPU_TO_DSP_BASE_DIFF		(pstMemCfgAud->dpb0_memory_base - 0x68000000)
#define IEC_CPU_TO_DSP_BASE_DIFF		(pstMemCfgAud->dpb0_memory_base - 0x68000000)
#define CAPB_CPU_TO_DSP_BASE_DIFF		(pstMemCfgAud->dpb0_memory_base - 0x68000000)

#define CPB_MAX_ACCESS_SIZE         	(20*1024)
#define DPB_MAX_ACCESS_SIZE         	(20*1024)
#define MPB_MAX_ACCESS_SIZE         	(10*1024)
#define IEC_MAX_ACCESS_SIZE         	(10*1024)
#define CAPB_MAX_ACCESS_SIZE         	(20*1024)

#define CPB_AUI_INDEX_COUNT       		(0x1000)	// 4096
#define DPB_AUI_INDEX_COUNT       		(0x0400)	// 1024
#define MPB_AUI_INDEX_COUNT       		(0x1000)
#define IEC_AUI_INDEX_COUNT       		(0x1000)
#define CAPB_AUI_INDEX_COUNT      		(0x1000)

// Sound Engine Update Mask
#define MASK_SE_FN_MODE_SHIFT   		(8)
#define MASK_SE_FN_MODE_FN000   		(0x0001)
#define MASK_SE_FN_MODE_FN001   		(0x0002)
#define MASK_SE_FN_MODE_FN002   		(0x0004)
#define MASK_SE_FN_MODE_FN003   		(0x0008)
#define MASK_SE_FN_MODE_FN004_MODE1		(0x0010)
#define MASK_SE_FN_MODE_FN004_MODE2		(0x0020)
#define MASK_SE_FN_MODE_FN004_MODE3		(0x0040)
#define MASK_SE_FN_MODE_FN005   		(0x0080)
#define MASK_SE_FN_MODE_FN006   		(0x0100)
#define MASK_SE_FN_MODE_FN007   		(0x0200)
#define MASK_SE_FN_MODE_FN008   		(0x0400)
#define MASK_SE_FN_MODE_FN009   		(0x0800)
#define MASK_SE_FN_MODE_FN010   		(0x1000)
#define MASK_SE_FN_MODE_FN011   		(0x2000)
#define MASK_SE_FN_MODE_FN012   		(0x4000)
#define MASK_SE_FN_MODE_FN013   		(0x8000)

//define for constant value
#define ADEC_CODEC_NAME_SIZE			30

/**
 * AUD MonitorTask Message Status
 * This enumeration describes the ADEC monitor task status.
 *
 */
typedef  enum
{
	LX_AUD_TASK_NONE_MSG		= 0x000,	///< None
	LX_AUD_TASK_RESET_DSP0		= 0x001,	///< Reset DSP0 with exception handler interrupt
	LX_AUD_TASK_RESET_DSP1		= 0x002,	///< Reset DSP1 with exception handler interrupt
	LX_AUD_TASK_SET_SPDIF		= 0x004,	///< Set SPDIF clock for DEC0
	LX_AUD_TASK_USE_GSTC		= 0x008,	///< Use GSTC for MHEG TP stream lipsync
	LX_AUD_TASK_SET_DTO_RATE	= 0x010,	///< Set SPDIF DTO Clock Rate
	LX_AUD_TASK_SET_SPDIF_DEC1	= 0x020,	///< Set SPDIF clock for DEC1
	LX_AUD_TASK_RESET_CLOCK		= 0x040,	///< Reset a I2S and SPDIF clock registers
	LX_AUD_TASK_RESTART_DEC0	= 0x080,	///< Restart DEC0 DTS codec when undeflow occurrs dts codec in HDMI input
	LX_AUD_TASK_RESTART_DEC1	= 0x100		///< Restart DEC1 DTS codec when undeflow occurrs dts codec in HDMI input
} LX_AUD_TASK_MSG_T;


typedef enum
{
	WRITER_RET_OPEN_OK = 0,
	WRITER_RET_CLOSE_OK,
	WRITER_RET_INIT_OK,
	WRITER_RET_WRITE_OK,
	WRITER_RET_FLUSH_OK,
	WRITER_RET_UNDERFLOW,
	WRITER_RET_OVERFLOW,
	WRITER_RET_ERROR,
	WRITER_RET_UNKNOWN
} WRITER_RET_TYPE;

/**
 * Audio buffer type
 * Audio decoder number is defined for dual decoding.
 */
typedef  enum
{
	LX_AUD_BUF_IF_TYPE_NONE		= 0,		///< Audio Decoder 0
	LX_AUD_BUF_IF_TYPE_CPB,		//writer	comm buff o
	LX_AUD_BUF_IF_TYPE_DPB, 		//writer	comm buff o
	LX_AUD_BUF_IF_TYPE_MPB,    	//writer	comm buff o
	LX_AUD_BUF_IF_TYPE_IEC,    	//writer	comm buff o
	LX_AUD_BUF_IF_TYPE_CAPB, 	//reader	comm buff o
	LX_AUD_BUF_IF_TYPE_ENC,   	//reader	comm buff x
} LX_AUD_BUF_IF_TYPE_T;

typedef struct
{
	BOOLEAN			bInitDone;				/* Current Audio Init Done Status */
	UINT32 			soundEngineMask;		/* Current ADEC Sound Engine Mask */

	//DSP load and copy flag after H/W reset
	BOOLEAN 		LoadCodec ;
	BOOLEAN 		CopyDSP0;
	BOOLEAN 		CopyDSP1;
	BOOLEAN 		EnableIMCDBG;

	/* Set for DSP 0/1 state for memory flush */
	UINT32			IsDSP0Reseted;
	UINT32			IsDSP1Reseted;
	int				IsDSP0Ready;
	int 			IsDSP1Ready;
}LX_AUD_KDRV_T;

typedef enum
{
	LX_AUD_BUB_IF_IDX_CPB = 0,
	LX_AUD_BUB_IF_IDX_DPB,
	LX_AUD_BUB_IF_IDX_MPB,
	LX_AUD_BUB_IF_IDX_IEC,
	LX_AUD_BUB_IF_IDX_CAPB,
	LX_AUD_BUB_IF_IDX_ENC,
	LX_AUD_BUB_IF_IDX_MAX,
} LX_AUD_BUB_IF_IDX;

/**
AUDIO MIX Memory Map configuration.
*/
typedef struct
{
	void	*pWriterReaderStruct;
	UINT32	*pMemVirBase;
	void	*pRegBase;
	char* 	MemName;
	UINT32 	MemPhyBase;
	UINT32 	MemSize;
	UINT32 	bufIndexBase;
	UINT8	*pConTypeL;//UINT32 	conTypeL[LX_AUD_BUB_IF_IDX_MAX];
	UINT8	*pConTypeR;//UINT32 	conTypeR[LX_AUD_BUB_IF_IDX_MAX];

} LX_AUD_BUF_MEM_CFG_S_T;

/**
Lipsync basetime of VDEC
*/
typedef struct
{
	UINT32			vdec_dec0_cbt;	// 0x08F0
	UINT32			vdec_dec0_sbt;	// 0x08F4
	UINT32			vdec_dec1_cbt;	// 0x08F8
	UINT32			vdec_dec1_sbt;	// 0x08FC
} VDEC_LIPSYNC_REG_T;


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern UINT8	bufIF_TableLUT[];
extern LX_AUD_BUF_MEM_CFG_S_T * bufIF[] ;
extern UINT32		*g_pui32IPC_VirAddr;
extern LX_AUD_BUF_MEM_CFG_S_T stMIX[];
extern LX_AUD_BUF_MEM_CFG_S_T stCPB[];
extern LX_AUD_BUF_MEM_CFG_S_T stDPB[];
extern LX_AUD_BUF_MEM_CFG_S_T stIEC[];
extern LX_AUD_BUF_MEM_CFG_S_T stENC[];
extern LX_AUD_BUF_MEM_CFG_S_T stCAP[];

SINT32 AUDIO_InitModule ( void );
SINT32 AUDIO_LoadDSP1Codec ( void );
SINT32 AUDIO_LoadDSP0Codec ( void );
void AUDIO_SignalDSP0Ready ( void* _param, int _paramLen,	void* _cbParam);
void AUDIO_SignalDSP1Ready ( void* _param, int _paramLen, void* _cbParam);

SINT32 AUDIO_IOREMAP( void );
SINT32 AUDIO_CreateBuffer( void );

void AUDIO_ShowIoremap( void );
void AUDIO_ShowMemoryDump( LX_AUD_DEBUG_MEM_DUMP_T *pMemDump );

SINT32 AUDIO_MonitorTask(void *pParam);

UINT32 AUDIO_ReadDebugMask (void);
void AUDIO_WriteDebugMask (unsigned int mask);

void AUDIO_Restart(void);
SINT32 AUDIO_ResetAADModule(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _AUDIO_DRV_HAL_H_ */

/** @} */


