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
 *  hal api implementation for venc device.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		jaeseop.so (jaeseop.so@lge.com)
 *  version		1.0
 *  date		2012.07.23
 *  note		Additional information.
 *
 *  @addtogroup lg1154_venc
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <asm/io.h>
#include "os_util.h"
#include "venc_drv.h"
#include "venc_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define VENC_CHECK_CODE(__checker, __if_action, fmt, args...) \
			__CHECK_IF_ERROR(__checker, VENC_PRINT, __if_action, fmt, ##args)

#define E_INTER_EN						0x0C00		// IPC, VSYNC

#define RUN_API(__function, args...) ( pstHalApi != NULL && pstHalApi->__function != NULL) ? \
													pstHalApi->__function(args) : 0

//#warning "FIXME"
//#define lx_chip_rev()		LX_CHIP_REV(H13,B0)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef VENC_USE_H1ENCODE
VENC_HAL_API_T *VENC_HAL_InitializeH13Bx( void );
#endif

#ifdef VENC_USE_LGENC
VENC_HAL_API_T *VENC_HAL_InitializeLGEnc( void );
#endif

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
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
VENC_HAL_API_T * pstHalApi;

/*========================================================================================
	Implementation Group
========================================================================================*/
static int _HAL_APIInit( void )
{
#ifdef VENC_USE_H1ENCODE	
	if (lx_chip_rev() >= LX_CHIP_REV(H13,B0))
	{
		pstHalApi = VENC_HAL_InitializeH13Bx();
	} else
#endif	

#ifdef VENC_USE_LGENC
	if (lx_chip_rev() >= LX_CHIP_REV(L9,A0))
	{
		// L9, H13Ax(A0/A1)
		pstHalApi = VENC_HAL_InitializeLGEnc();
	} else
#endif	
	{
		pstHalApi = NULL;
	}

	if ( pstHalApi == NULL )
	{
		return RET_ERROR;
	}

	VENC_DEBUG("VENC API VER: 0x%08x\n", pstHalApi->version);
	
	return RET_OK;
}

int VENC_HAL_DeviceInitialize ( void )
{
	if ( _HAL_APIInit() != RET_OK )
	{
		return RET_ERROR;
	}

	return RUN_API( DeviceInitialize );

}

int VENC_HAL_DeviceFinalize ( void )
{

	return RUN_API( DeviceFinalize );
	
}

int VENC_HAL_Initialize( void )
{

	return RUN_API( Initialize );

}

int VENC_HAL_SetInputConfig ( LX_VENC_ENC_INPUT_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return RUN_API( SetInputConfig, pstParams );
}

int VENC_HAL_SetCommand ( LX_VENC_ENC_COMMAND_T eParam )
{

	return RUN_API( SetCommand, eParam);

}

int VENC_HAL_SetQuality ( LX_VENC_ENC_QUALITY_T eParam )
{
	return RUN_API( SetQuality, eParam );
}

int VENC_HAL_SetQPLevel ( UINT32 ui32Param )
{
	return RUN_API( SetQPLevel, ui32Param );
}

int VENC_HAL_SetGOP ( UINT32 ui32Param )
{
	return RUN_API( SetGOP, ui32Param );
}

int VENC_HAL_SetTargetBitrate( UINT32 ui32Param )
{
	return RUN_API( SetTargetBitrate, ui32Param );
}

int VENC_HAL_SetEncodeType( LX_VENC_ENCODE_TYPE_T eParam )
{
	return RUN_API( SetEncodeType, eParam );
}

int VENC_HAL_GetBufferInfo ( LX_VENC_BUFFER_T *pstParams )
{
	LX_MEMCFG_T *pMemCfg;

	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	pMemCfg = (LX_MEMCFG_T *)gpstVencMemConfig;
	//RUN_API( GetBufferInfo, pstParams );

	//pstParams->ui32PhysicalAddress 	= gpstVencMemConfig->uiScalerBase;
	//pstParams->ui32Size 			= gpstVencMemConfig->uiScalerSize;

	pstParams->ui32ESBufPhysBase = gpstVencMemConfig->uiESBufBase;
	pstParams->ui32ESBufSize = gpstVencMemConfig->uiESBufSize;
	pstParams->ui32ESBufOffset = gpstVencMemConfig->uiESBufBase - pMemCfg->base;

	pstParams->ui32AUIBufPhysBase = gpstVencMemConfig->uiAUIBufBase;
	pstParams->ui32AUIBufSize = gpstVencMemConfig->uiAUIBufSize;
	pstParams->ui32AUIBufOffset = gpstVencMemConfig->uiAUIBufBase - pMemCfg->base;

	pstParams->ui32InBufPhysBase= gpstVencMemConfig->uiInBufBase;
	pstParams->ui32InBufSize 	= gpstVencMemConfig->uiInBufSize;
	pstParams->ui32InBufOffset 	= gpstVencMemConfig->uiInBufBase - pMemCfg->base;

	return RET_OK;
}

int VENC_HAL_GetEncodeInfo( LX_VENC_ENC_INFO_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return RUN_API( GetEncodeInfo, pstParams );
}

int VENC_HAL_GetFrameImage( LX_VENC_ENC_FRAME_IMAGE_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return RUN_API( GetFrameImage, pstParams );
}

int VENC_HAL_GetOutputBuffer( LX_VENC_ENC_OUTPUT_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return RUN_API( GetOutputBuffer, pstParams );
}

int VENC_HAL_GetPerformance( LX_VENC_ENC_PERPERMANCE_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return RUN_API( GetPerformance, pstParams );
}

int VENC_HAL_PROC_ReadStatus( char * buffer )
{
	if ( buffer == NULL )
	{
		return 0;
	}

	return RUN_API( PROC_ReadStatus, buffer );
}

irqreturn_t VENC_HAL_ISRHandler( void )
{

	RUN_API( ISRHandler );

	return IRQ_HANDLED;
}


/*----------------------------------------------------------------------------------------
	Static Function Definition
----------------------------------------------------------------------------------------*/


/** @} */

