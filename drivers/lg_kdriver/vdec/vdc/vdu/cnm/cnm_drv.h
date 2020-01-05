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
 * CnM video decoding unit driver header for vdec device.
 * VDEC device will teach you how to make device driver with lg1154 platform.
 *
 * author     Youngwoo Jin(youngwoo.jin@lge.com)
 * version    1.0
 * date       2012.06.13
 * note       Additional information.
 *
 */

#ifndef _CNM_DRV_H_
#define _CNM_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "../../vdu_drv.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define CNM_MAX_NUM_OF_INSTANCE		(4)
#define CNM_NUM_OF_MAX_DPB			(16 + 4)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/
VDU_RET_T		CNM_Init(VDU_CALLBACK_FN_T pfnNotiCallback, const UINT16* pui16Data, UINT32 ui32Size);
VDU_HANDLE_T	CNM_Open(VDU_OPEN_PARAM_T *pstOpenParam);
VDU_RET_T		CNM_Close(VDU_HANDLE_T hInstance);
VDU_RET_T		CNM_Flush(VDU_HANDLE_T hInstance);
VDU_RET_T		CNM_Reset(VDU_HANDLE_T hInstance);
VDU_RET_T		CNM_StartDecoding(VDU_HANDLE_T hInstance);
VDU_RET_T		CNM_GetFrameInfo(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, VDU_FRM_INFO_T *pstFrameInfo);
VDU_RET_T		CNM_GetLinearFrame(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, void* pFrameBuf);
VDU_RET_T		CNM_FeedAu(VDU_HANDLE_T hInstance, VDU_AU_T* pstAu, void* pData);
VDU_RET_T		CNM_SetOption(VDU_HANDLE_T hInstance, VDU_OPTION_T* pstOption);
VDU_RET_T		CNM_ClearFrame(VDU_HANDLE_T hInstance, SINT8 si8FrameIdx);
void			CNM_Isr(UINT8 ui8CoreNum);

#ifdef __cplusplus
}
#endif

#endif /* _CNM_DRV_H_ */

