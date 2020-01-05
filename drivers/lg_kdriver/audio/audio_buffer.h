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
 *  buffer interface header for audio device.
 *	buffer interface.
 *
 *  @author		jongsang.oh (jongsang.oh@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1152_adec
 *	@{
 */

#ifndef _AUDIO_BUFFER_H_
#define _AUDIO_BUFFER_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "buffer/adec_common_buf.h"

#include "buffer/adec_buf.h"
#include "buffer/adec_inter_buf_reader.h"
#include "buffer/adec_inter_buf_writer.h"
#include "buffer/adec_buf_helper.h"


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	PFN_ADEC_CACHE_CONTROL		pfnInvalidate;
	PFN_ADEC_CACHE_CONTROL		pfnWriteback;
	PFN_ADEC_ADDR_TRANSLATOR	pfnAddrTrans;
	unsigned char*				dummyAddr;
	int							memSize;
	unsigned char*				memBase;
}ARM_PROCESSOR_ADAP;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void ADEC_ARM_Create_Interbuf_Writer(void);
void ADEC_ARM_Create_Interbuf_Reader(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern ARM_PROCESSOR_ADAP gCPB_ArmWriterAdap[];
extern ARM_PROCESSOR_ADAP gDPB_ArmWriterAdap[];
extern ARM_PROCESSOR_ADAP gMIX_ArmWriterAdap[];
extern ARM_PROCESSOR_ADAP gAENC_ArmReaderAdap[];
extern ARM_PROCESSOR_ADAP gCAP_ArmReaderAdap[];
extern ARM_PROCESSOR_ADAP gIEC_ArmWriterAdap[];



#ifdef __cplusplus
}
#endif


#endif /* _AUDIO_BUFFER_H_ */
