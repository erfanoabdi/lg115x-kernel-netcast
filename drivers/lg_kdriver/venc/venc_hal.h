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
 *  hal api for venc device.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  @author		jaeseop.so (jaeseop.so@lge.com)
 *  version		1.0
 *  date		2012.07.23
 *  note		Additional information.
 *
 *  @addtogroup lg1154_venc
 *	@{
 */

#ifndef	_VENC_HAL_H_
#define	_VENC_HAL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <asm/irq.h>

#include "os_util.h"
#include "venc_kapi.h"

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

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	int version;

// BEGIN of public APIs
	int (*DeviceInitialize) ( void );
	int (*DeviceFinalize) 	( void );
	int (*Initialize)		( void );

	// Setter functions
	int (*SetEncodeType)	( LX_VENC_ENCODE_TYPE_T eParam );
	int (*SetInputConfig)	( LX_VENC_ENC_INPUT_T *pstParams );
	int (*SetCommand)		( LX_VENC_ENC_COMMAND_T eParam );
	int (*SetQuality)		( LX_VENC_ENC_QUALITY_T eParam );
	int (*SetQPLevel)		( UINT32 ui32Param );
	int (*SetGOP)			( UINT32 ui32Param );
	int (*SetTargetBitrate)	( UINT32 ui32Param );

	// Getter functions
//	int (*GetBufferInfo)	( LX_VENC_BUFFER_T *pstParams );
	int (*GetEncodeInfo)	( LX_VENC_ENC_INFO_T *pstParams );
	int (*GetFrameImage)	( LX_VENC_ENC_FRAME_IMAGE_T *pstParams );
	int (*GetOutputBuffer)	( LX_VENC_ENC_OUTPUT_T *pstParams );
	int (*GetPerformance)	( LX_VENC_ENC_PERPERMANCE_T *pstParams );
// END of public APIs

	int (*PROC_ReadStatus)	( char *buffer );

// BEGIN of ISRs
	irqreturn_t (*ISRHandler)( void );
// END of ISRs
} VENC_HAL_API_T;

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/

int VENC_HAL_DeviceInitialize ( void );
int VENC_HAL_DeviceFinalize ( void );
int VENC_HAL_Initialize( void );

int VENC_HAL_SetEncodeType( LX_VENC_ENCODE_TYPE_T eParam );
int VENC_HAL_SetInputConfig ( LX_VENC_ENC_INPUT_T *pstParams );
int VENC_HAL_SetCommand ( LX_VENC_ENC_COMMAND_T eParam );
int VENC_HAL_SetQuality ( LX_VENC_ENC_QUALITY_T eParam );
int VENC_HAL_SetQPLevel ( UINT32 ui32Param );
int VENC_HAL_SetGOP ( UINT32 ui32Param );
int VENC_HAL_SetTargetBitrate( UINT32 ui32Param );

int VENC_HAL_GetBufferInfo ( LX_VENC_BUFFER_T *pstParams );
int VENC_HAL_GetEncodeInfo( LX_VENC_ENC_INFO_T *pstParams );
int VENC_HAL_GetFrameImage( LX_VENC_ENC_FRAME_IMAGE_T *pstParams );
int VENC_HAL_GetOutputBuffer( LX_VENC_ENC_OUTPUT_T *pstParams );
int VENC_HAL_GetPerformance( LX_VENC_ENC_PERPERMANCE_T *pstParams );

irqreturn_t VENC_HAL_ISRHandler( void );

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VENC_HAL_H_ */

/** @} */

