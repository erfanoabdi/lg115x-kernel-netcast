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

/**
 * @file
 *
 *  main driver implementation for CnM vdec device.
 *	vdec device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2013.01.05
 *  note		Additional information.
 *
 *  @addtogroup lg1154_vdec
 * @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/module.h>

#include "cnm/cnm_drv.h"

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

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

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
int VDEC_CNM_Init(void)
{
	int					iRetVal = -1;
	VDU_OPERATIONS_T	stOperations;

	stOperations.pfnInit = CNM_Init;
	stOperations.pfnOpen = CNM_Open;
	stOperations.pfnClose = CNM_Close;
	stOperations.pfnFlush = CNM_Flush;
	stOperations.pfnReset = CNM_Reset;
	stOperations.pfnStartDecoding = CNM_StartDecoding;
	stOperations.pfnGetFrameInfo = CNM_GetFrameInfo;
	stOperations.pfnGetLinearFrame = CNM_GetLinearFrame;
	stOperations.pfnFeedAu = CNM_FeedAu;
	stOperations.pfnSetOption = CNM_SetOption;
	stOperations.pfnClearFrame = CNM_ClearFrame;
	stOperations.pfnIsr = CNM_Isr;

	if( VDU_RegisterOperations(&stOperations) != VDU_RET_OK )
	{
		goto GOTO_END;
	}

	iRetVal = 0;

GOTO_END:
	return iRetVal;
}

void VDEC_CNM_Cleanup(void)
{
	return;
}

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("LG video decoder driver");
MODULE_LICENSE("GPL");

module_init(VDEC_CNM_Init);
module_exit(VDEC_CNM_Cleanup);
