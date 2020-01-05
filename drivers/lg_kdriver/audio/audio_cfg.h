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

#ifndef	_AUDIO_CFG_H_
#define	_AUDIO_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#include "audio_kapi.h"
#include "audio_reg.h"
#include "audio_drv_hal.h"
#include "audio_drv_hal_mixedIP.h"


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	AUDIO_MODULE			"audio"
#define	AUDIO_DEVICE_MAX		5

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
AUDIO Register configuration.
*/
typedef struct
{
	char*		chip_name;			// 	Chip Name
	UINT32		reg_base_addr;		//	AUD Register Base Address for Real Chip.
	UINT32		reg_size;			//	AUD Register Size for Real Chip.
	UINT32		irq0_num;			//	AUD IRQ 0 Number for Real Chip.
	UINT32		irq1_num;			//	AUD IRQ 0 Number for Real Chip.
} LX_AUD_REG_CFG_T;

/**
AUDIO Memory Map configuration.
*/
typedef struct
{
	char*	start_memory_name;
	UINT32	start_memory_base;
	UINT32	start_memory_size;

	char* 	fw0_memory_name;
	UINT32	fw0_memory_base;
	UINT32 	fw0_memory_size;

	char* 	dsp0_memory_name;
	UINT32 	dsp0_memory_base;
	UINT32 	dsp0_memory_size;

	char* 	fw1_memory_name;
	UINT32	fw1_memory_base;
	UINT32 	fw1_memory_size;

	char* 	dsp1_memory_name;
	UINT32 	dsp1_memory_base;
	UINT32 	dsp1_memory_size;

	char* 	dpb0_memory_name;
	UINT32 	dpb0_memory_base;
	UINT32 	dpb0_memory_size;

	char* 	dpb1_memory_name;
	UINT32 	dpb1_memory_base;
	UINT32 	dpb1_memory_size;

	char* 	cpb0_memory_name;
	UINT32	cpb0_memory_base;
	UINT32 	cpb0_memory_size;

	char* 	cpb1_memory_name;
	UINT32	cpb1_memory_base;
	UINT32 	cpb1_memory_size;

	char* 	mpb0_memory_name;
	UINT32 	mpb0_memory_base;
	UINT32 	mpb0_memory_size;

	char* 	mpb1_memory_name;
	UINT32 	mpb1_memory_base;
	UINT32 	mpb1_memory_size;

	char* 	mpb2_memory_name;
	UINT32 	mpb2_memory_base;
	UINT32 	mpb2_memory_size;

	char* 	mpb3_memory_name;
	UINT32 	mpb3_memory_base;
	UINT32 	mpb3_memory_size;

	char* 	mpb4_memory_name;
	UINT32 	mpb4_memory_base;
	UINT32 	mpb4_memory_size;

	char* 	mpb5_memory_name;
	UINT32 	mpb5_memory_base;
	UINT32 	mpb5_memory_size;

	char* 	mpb6_memory_name;
	UINT32 	mpb6_memory_base;
	UINT32 	mpb6_memory_size;

	char* 	mpb7_memory_name;
	UINT32 	mpb7_memory_base;
	UINT32 	mpb7_memory_size;

	char* 	iec0_memory_name;
	UINT32 	iec0_memory_base;
	UINT32 	iec0_memory_size;

	char* 	iec1_memory_name;
	UINT32 	iec1_memory_base;
	UINT32 	iec1_memory_size;

	char* 	cap0_memory_name;
	UINT32 	cap0_memory_base;
	UINT32 	cap0_memory_size;

	char* 	cap1_memory_name;
	UINT32 	cap1_memory_base;
	UINT32 	cap1_memory_size;

	char* 	cap2_memory_name;
	UINT32 	cap2_memory_base;
	UINT32 	cap2_memory_size;

	char* 	enc_memory_name;
	UINT32 	enc_memory_base;
	UINT32 	enc_memory_size;

	char* 	se_memory_name;
	UINT32 	se_memory_base;
	UINT32 	se_memory_size;

	char* 	ipc_memory_name;
	UINT32 	ipc_memory_base;
	UINT32 	ipc_memory_size;

	char* 	debug_memory_name;
	UINT32 	debug_memory_base;
	UINT32 	debug_memory_size;

	char*	end_memory_name;
	UINT32	end_memory_base;
	UINT32	end_memory_size;
} LX_AUD_MEM_CFG_S_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern volatile LX_AUD_REG_T		*g_pRealRegAud;
extern LX_AUD_REG_T					*g_pTempRegAud ;

//define memory map
extern LX_AUD_REG_CFG_T 			g_stAudRegCfg[];
extern LX_AUD_REG_CFG_T 			*pstAudRegCfg;	// for Real. Chip
extern LX_AUD_MEM_CFG_S_T 			g_stMemCfgAud[];
extern LX_AUD_MEM_CFG_S_T 			*pstMemCfgAud;	// for Real. Chip

extern LX_AUD_EVENT_TYPE_T gAudSetEvent[AUD_DEV_MAX];
extern LX_AUD_EVENT_TYPE_T gAudGetEvent[AUD_DEV_MAX];
extern wait_queue_head_t   gAudPollWaitQueue;
extern spinlock_t 		   gAudEventSpinLock;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _AUD_CFG_H_ */

/** @} */


