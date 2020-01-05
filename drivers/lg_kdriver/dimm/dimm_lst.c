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

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "dimm_qkb.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "os_util.h"

#include "../de/de_def.h"

#include "dimm_kapi.h"
#include "dimm_lst.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
#ifdef USE_DIMM_SUSPEND
/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
/**
 * initailize list
 * make dummy header
 *
 * @see DIMM_KLIST_T
 */
DIMM_KLIST_T *DIMM_InitKList( void )
{
	DIMM_KLIST_T	*pList;

	pList = (DIMM_KLIST_T *)OS_Malloc(sizeof(DIMM_KLIST_T));
	if ( pList ) pList->pNext = pList;

	return pList;
}


/* add item to list
 * add an item to the end of the list
 *
 * @param in: pList target list
 * @param in: pItem item to be added
 */
int DIMM_AddItemToKList(DIMM_KLIST_T *pList, DIMM_KLIST_T *pItem)
{
	int ret = RET_OK;
	DIMM_KLIST_T		 *pLast;

	if ( pList && pItem )
	{
		pLast = pList;
		while ( pLast->pNext != pList ) pLast = pLast->pNext;

		pLast->pNext = pItem;
		pItem->pNext = pList;
	}
	else
	{
		ret = RET_ERROR;
	}

	return ret;
}

/**
 * delete element from list
 * remove an item from the list and free its memory
 *
 * @param in: pList previous item of the seleted item
 * @param in: pItem item to be deleted
 */
int DIMM_DeleteItemFromKList(DIMM_KLIST_T *pList, DIMM_KLIST_T *pItem)
{
	int ret = RET_OK;
	LX_DIMM_LUT_CTRL_T *pParam;

	if ( pList && pItem )
	{
		pList->pNext = pItem->pNext;

		pParam = pItem->pData;
		OS_Free((void *)(pParam->pLut));
		OS_Free((void *)(pParam));
		OS_Free((void *)(pItem));
	}
	else
	{
		ret = RET_ERROR;
	}

	return ret;
}

DIMM_KLIST_T *DIMM_FindItemFromKList4Table(DIMM_KLIST_T *pList, LX_DIMM_LUT_CTRL_T *pTable)
{
	DIMM_KLIST_T			   *pLast;
	LX_DIMM_LUT_CTRL_T *pParam;

	if ( pList && pTable )
	{
		pLast = pList;
		while ( pLast->pNext != pList ) {
			pLast  = pLast->pNext;
			pParam = pLast->pData;
			if (!pParam) break;
			if (pParam->u32Num != pTable->u32Num) continue;
			if (!pParam->pLut) continue;
			if (!pTable->pLut) continue;

			return pLast;
		}
	}

	return NULL;
}

DIMM_KLIST_T *DIMM_NextItmeFromKlist(DIMM_KLIST_T *pList, DIMM_KLIST_T *pItem)
{
	DIMM_KLIST_T			   *pCurr;
	DIMM_KLIST_T			   *pLast;

	if ( pList && pItem )
	{
		pLast = pList;
		while ( pLast->pNext != pList ) {
			pCurr  = pLast;
			pLast  = pLast->pNext;
			if (pCurr != pItem) continue;
			return pLast;
		}
	}

	return NULL;
}

int DIMM_AddTableToKList(DIMM_KLIST_T *pList, LX_DIMM_LUT_CTRL_T *pTable)
{
	int ret = RET_OK;
	DIMM_KLIST_T		*pItem = NULL;
	LX_DIMM_LUT_CTRL_T	*pParam;
	UINT32 dataSize;

	do {
		CHECK_KNULL(pList);
		CHECK_KNULL(pTable);
		pItem = DIMM_FindItemFromKList4Table(pList, pTable);
		do {
			if (!pItem) break;
			ret = DIMM_DeleteItemFromKList(pList, pItem);
		} while (0);
		if (ret) break;

		pItem = (DIMM_KLIST_T *)OS_Malloc(sizeof(DIMM_KLIST_T));
		CHECK_KNULL(pItem);
		pParam = (LX_DIMM_LUT_CTRL_T *)OS_Malloc(sizeof(LX_DIMM_LUT_CTRL_T));
		CHECK_KNULL(pParam);
		memcpy(pParam, pTable, sizeof(LX_DIMM_LUT_CTRL_T));
		dataSize = pParam->u32Num * sizeof(UINT32);
		pParam->pLut = (UINT32 *)OS_Malloc(dataSize);
		CHECK_KNULL(pParam->pLut);
		memcpy((UINT32 *)pParam->pLut, pTable->pLut, dataSize);
		pItem->pData = pParam;

		ret = DIMM_AddItemToKList(pList, pItem);
	} while (0);

	return ret;
}

int DIMM_DeleteAllFromKList(DIMM_KLIST_T *pList)
{
	int ret = RET_OK;
	DIMM_KLIST_T	*pLast;
	DIMM_KLIST_T	*pCurr;
	LX_DIMM_LUT_CTRL_T	*pParam;

	do {
		CHECK_KNULL(pList);
		pLast = pList;
		while ( pLast->pNext != pList ) {
			pCurr = pLast;
			pLast = pLast->pNext;

			pParam = pCurr->pData;
			OS_Free((void *)(pParam->pLut));
			OS_Free((void *)(pParam));
			OS_Free((void *)(pCurr));
		}
	} while (0);

	return ret;
}
#endif

/**  @} */
