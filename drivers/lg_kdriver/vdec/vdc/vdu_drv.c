/* ****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * *****************************************************************************************/

/** @file
 *
 * video decoding unit driver implementation for VDEC device.
 * VDEC device will teach you how to make device driver with lg1154 platform.
 *
 * @author     Youngwoo Jin(youngwoo.jin@lge.com)
 * @version    1.0
 * @date       2013.01.06
 * @note       Additional information.
 *
 * @addtogroup lg1154_vdec
 * @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/string.h>

#include "vdu_drv.h"
#include "../log.h"
#ifdef INCLUDE_MODULE
#include "vdu/cnm/cnm_drv.h"
#endif

#include "vdu/cnm/blackbird.h"

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
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
logm_define(vdec_vdu, log_level_warning);
logm_define(vdec_perf, log_level_warning);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static spinlock_t			_gstOperationLock;
static VDU_OPERATIONS_T		_gstOperations;
static VDU_CALLBACK_FN_T	_gpfnCallback = NULL;

/*========================================================================================
    Implementation Group
========================================================================================*/
/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T 		VDU_Init(VDU_CALLBACK_FN_T pfnCallback)
{
	VDU_RET_T		eRetVal = VDU_RET_ERROR;
	ULONG			ulFlags;

	spin_lock_init(&_gstOperationLock);

	spin_lock_irqsave(&_gstOperationLock, ulFlags);

	memset(&_gstOperations, 0, sizeof(VDU_OPERATIONS_T));
	_gpfnCallback = pfnCallback;

	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

#ifdef INCLUDE_MODULE
	{
		VDU_OPERATIONS_T stOperations;

		stOperations.pfnInit			= CNM_Init;
		stOperations.pfnOpen			= CNM_Open;
		stOperations.pfnClose			= CNM_Close;
		stOperations.pfnFlush			= CNM_Flush;
		stOperations.pfnReset			= CNM_Reset;
		stOperations.pfnStartDecoding	= CNM_StartDecoding;
		stOperations.pfnGetFrameInfo	= CNM_GetFrameInfo;
		stOperations.pfnGetLinearFrame	= CNM_GetLinearFrame;
		stOperations.pfnFeedAu			= CNM_FeedAu;
		stOperations.pfnSetOption		= CNM_SetOption;
		stOperations.pfnClearFrame		= CNM_ClearFrame;
		stOperations.pfnIsr				= CNM_Isr;

		VDU_RegisterOperations(&stOperations);
	}
#endif

	eRetVal = VDU_RET_OK;

	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_HANDLE_T	VDU_Open(VDU_OPEN_PARAM_T *pstOpenParam)
{
	VDU_HANDLE_T	hRetHandle = VDU_INVALID_HANDLE;
	ULONG			ulFlags;
	VDU_OPEN_FN_T	pfnOpen;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnOpen = _gstOperations.pfnOpen;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnOpen == NULL )
	{
		logm_error(vdec_vdu, "VDU_Open failed : No function registered\n");
		goto GOTO_END;
	}

	hRetHandle = pfnOpen(pstOpenParam);

GOTO_END:
	return hRetHandle;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_Close(VDU_HANDLE_T hInstance)
{
	VDU_RET_T		eRetVal = VDU_RET_ERROR;
	ULONG			ulFlags;
	VDU_CLOSE_FN_T	pfnClose;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnClose = _gstOperations.pfnClose;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnClose == NULL )
	{
		logm_error(vdec_vdu, "VDU_Close failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnClose(hInstance);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_Flush(VDU_HANDLE_T hInstance)
{
	VDU_RET_T		eRetVal = VDU_RET_ERROR;
	ULONG			ulFlags;
	VDU_FLUSH_FN_T	pfnFlush;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnFlush = _gstOperations.pfnFlush;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnFlush == NULL )
	{
		logm_error(vdec_vdu, "VDU_Flush failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnFlush(hInstance);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_Reset(VDU_HANDLE_T hInstance)
{
	VDU_RET_T		eRetVal = VDU_RET_ERROR;
	ULONG			ulFlags;
	VDU_RESET_FN_T	pfnReset;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnReset = _gstOperations.pfnReset;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnReset == NULL )
	{
		logm_error(vdec_vdu, "VDU_Reset failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnReset(hInstance);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_StartDecoding(VDU_HANDLE_T hInstance)
{
	VDU_RET_T				eRetVal = VDU_RET_ERROR;
	ULONG					ulFlags;
	VDU_START_DECODING_FN_T	pfnStartDecoding;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnStartDecoding = _gstOperations.pfnStartDecoding;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnStartDecoding == NULL )
	{
		logm_error(vdec_vdu, "VDU_StartDecoding failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnStartDecoding(hInstance);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_GetFrameInfo(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, VDU_FRM_INFO_T *pstFrameInfo)
{
	VDU_RET_T				eRetVal = VDU_RET_ERROR;
	ULONG					ulFlags;
	VDU_GET_FRAME_INFO_FN_T	pfnGetFrameInfo;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnGetFrameInfo = _gstOperations.pfnGetFrameInfo;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnGetFrameInfo == NULL )
	{
		logm_error(vdec_vdu, "VDU_GetFrameInfo failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnGetFrameInfo(hInstance, si8FrameNum, pstFrameInfo);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_GetLinearFrame(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, void* pFrameBuf)
{
	VDU_RET_T					eRetVal = VDU_RET_ERROR;
	ULONG						ulFlags;
	VDU_GET_LINEAR_FRAME_FN_T	pfnGetLinearFrame;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnGetLinearFrame = _gstOperations.pfnGetLinearFrame;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnGetLinearFrame == NULL )
	{
		logm_error(vdec_vdu, "VDU_GetLinearFrame failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnGetLinearFrame(hInstance, si8FrameNum, pFrameBuf);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_FeedAu(VDU_HANDLE_T hInstance, VDU_AU_T* pstAu, void* pData)
{
	VDU_RET_T			eRetVal = VDU_RET_ERROR;
	ULONG				ulFlags;
	VDU_FEED_AU_FN_T	pfnFeedAu;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnFeedAu = _gstOperations.pfnFeedAu;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnFeedAu == NULL )
	{
		logm_error(vdec_vdu, "VDU_FeedAu failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnFeedAu(hInstance, pstAu, pData);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_SetOption(VDU_HANDLE_T hInstance, VDU_OPTION_T* pstOption)
{
	VDU_RET_T			eRetVal = VDU_RET_ERROR;
	ULONG				ulFlags;
	VDU_SET_OPTION_FN_T	pfnSetOption;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnSetOption = _gstOperations.pfnSetOption;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnSetOption == NULL )
	{
		logm_error(vdec_vdu, "VDU_SetOption failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnSetOption(hInstance, pstOption);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_ClearFrame(VDU_HANDLE_T hInstance, SINT8 si8FrameIdx)
{
	VDU_RET_T				eRetVal = VDU_RET_ERROR;
	ULONG					ulFlags;
	VDU_CLEAR_FRAME_FN_T	pfnClearFrame;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnClearFrame = _gstOperations.pfnClearFrame;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnClearFrame == NULL )
	{
		logm_error(vdec_vdu, "VDU_ClearFrame failed : No function registered\n");
		goto GOTO_END;
	}

	eRetVal = pfnClearFrame(hInstance, si8FrameIdx);

GOTO_END:
	return eRetVal;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void			VDU_Isr(UINT8 ui8CoreNum)
{
	ULONG			ulFlags;
	VDU_ISR_FN_T	pfnIsr;

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
	pfnIsr = _gstOperations.pfnIsr;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( pfnIsr == NULL )
	{
		logm_error(vdec_vdu, "VDU_Isr failed : No function registered\n");
		goto GOTO_END;
	}

	pfnIsr(ui8CoreNum);

GOTO_END:
	return;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
VDU_RET_T		VDU_RegisterOperations(VDU_OPERATIONS_T* pstOperations)
{
	VDU_RET_T			eRetVal = VDU_RET_ERROR;
	ULONG				ulFlags;
	VDU_INIT_FN_T		pfnInit;
	VDU_CALLBACK_FN_T	_pfnCallback;

	if( pstOperations == NULL )
	{
		logm_error(vdec_vdu, "VDU_RegisterOperations failed : Null parameter\n");
		goto GOTO_END;
	}

	spin_lock_irqsave(&_gstOperationLock, ulFlags);
#ifdef INCLUDE_MODULE
	if( _gstOperations.pfnInit != NULL )
	{
		spin_unlock_irqrestore(&_gstOperationLock, ulFlags);
		logm_error(vdec_vdu, "VDU_RegisterOperations failed : An included module already registered\n");
		goto GOTO_END;
	}
#endif
	_gstOperations = *pstOperations;
	pfnInit = _gstOperations.pfnInit;
	_pfnCallback = _gpfnCallback;
	spin_unlock_irqrestore(&_gstOperationLock, ulFlags);

	if( (pfnInit == NULL) || (_pfnCallback == NULL) )
	{
		goto GOTO_END;
	}

	eRetVal = pfnInit(_pfnCallback, (const UINT16*)bit_code, sizeof(bit_code) / sizeof(bit_code[0]));

GOTO_END:
	return eRetVal;
}
EXPORT_SYMBOL(VDU_RegisterOperations);

/** @} */
