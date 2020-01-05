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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.10.01
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

#ifndef  DIMM_LST_INC
#define  DIMM_LST_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct _DIMM_KLIST
{
	struct _DIMM_KLIST *pNext;
	void 		 *pData;
} DIMM_KLIST_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DIMM_SUSPEND
DIMM_KLIST_T *DIMM_InitKList( void );
int DIMM_AddTableToKList(DIMM_KLIST_T *pList, LX_DIMM_LUT_CTRL_T *pTable);
DIMM_KLIST_T *DIMM_NextItmeFromKlist(DIMM_KLIST_T *pList, DIMM_KLIST_T *pItem);
DIMM_KLIST_T *DIMM_FindItemFromKList4Table(DIMM_KLIST_T *pList, LX_DIMM_LUT_CTRL_T *pTable);
#endif

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DIMM_LST_INC  ----- */

/**  @} */
