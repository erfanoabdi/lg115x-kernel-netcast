
/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *  
 *  This program is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU General Public License 
 *  version 2 as published by the Free Software Foundation.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 *   GNU General Public License for more details.
*/ 

/** @file
 *
 *  register interface header for png device. ( used only within kdriver )
 *	png device will teach you how to make device driver with new platform.
 *
 *  @author		Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version	1.0
 *  @date		2011.10.21
 *
 *  @addtogroup h13
 *	@{
 */

#ifndef	_VENCIPC_HAL_API_H_
#define	_VENCIPC_HAL_API_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "../../mcu/vdec_type_defs.h"
#include "de_ipc_hal_api.h"

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

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/
void VENC_IPC_HAL_Init(void);
BOOLEAN VENC_IPC_HAL_UpdateDisplayBuffer(UINT8 ui8DeIpcCh, S_DIS_BUF_T *pDisBuf);
void VENC_IPC_HAL_InitFrameBuffer(UINT8 ui8DeIpcCh, S_FRAME_BUF_T *pFrameBuf);

#endif /* _VENCIPC_HAL_API_H_ */
