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
 * date       2010.03.17
 * note       Additional information.
 *
 * @addtogroup lg1150_dimm
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "dimm_qkb.h"
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/platform.h>

#include "base_types.h"
#include "os_util.h"

#include "../de/de_model.h"

#include "../de/de_def.h"
#include "../de/de_ipc_def.h"
#include "../de/de_ipc.h"

#include "dimm_kapi.h"
#include "dimm_io.h"
#include "dimm_hal.h"
#include "dimm_lst.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DIMM_SUSPEND
#define DIMM_COPY_FROM_USER(indx, to, from, n) (RET_OK != (ret = dimm_copy_from_user(indx, to, from, n)))
#define DIMM_IPC_SETDATA(cmd, msg, n)          DE_KIPC_SetData(cmd, &msg, n);
#else
#define DIMM_COPY_FROM_USER(indx, to, from, n) copy_from_user(to, from, n)
#define DIMM_IPC_SETDATA(cmd, msg, n)          DE_IPC_SetData(cmd, p##msg, n);
#endif

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DIMM_SUSPEND
typedef enum {
	DIMM_SUSPEND_INIT				 ,
	DIMM_SUSPEND_LOCALDIMMINGCONTROL ,
	DIMM_SUSPEND_STOREDEMO			 ,
	DIMM_SUSPEND_LINEDEMO			 ,
	DIMM_SUSPEND_CONTROLCOMPENSATION ,
	DIMM_SUSPEND_LUTCONTROL			 ,
	DIMM_SUSPEND_STORECONTROL		 ,
	DIMM_SUSPEND_WBCOLOR		 	 ,
} DIMM_SUSPEND_INDX_T;

DIMM_SUSPEND_STORE_T dimm_suspend_store[] = {
	{TRUE  ,DIMM_SUSPEND_INIT				 ,sizeof(LX_DIMM_INFO_T)		 ,DIMM_IO_Init				   ,NULL},
	{TRUE  ,DIMM_SUSPEND_LOCALDIMMINGCONTROL ,sizeof(BOOLEAN)				 ,DIMM_IO_LocaldimmingControl  ,NULL},
	{TRUE  ,DIMM_SUSPEND_STOREDEMO			 ,sizeof(BOOLEAN)				 ,DIMM_IO_StoreDemo			   ,NULL},
	{TRUE  ,DIMM_SUSPEND_LINEDEMO			 ,sizeof(LX_DIMM_LINE_CTRL_T)	 ,DIMM_IO_LineDemo			   ,NULL},
	{TRUE  ,DIMM_SUSPEND_CONTROLCOMPENSATION ,sizeof(BOOLEAN)				 ,DIMM_IO_ControlCompensation  ,NULL},
	{TRUE  ,DIMM_SUSPEND_LUTCONTROL			 ,sizeof(LX_DIMM_LUT_CTRL_T)	 ,DIMM_IO_LutControl		   ,NULL},
	{TRUE  ,DIMM_SUSPEND_STORECONTROL		 ,sizeof(BOOLEAN)				 ,DIMM_IO_StoreControl		   ,NULL},
	{TRUE  ,DIMM_SUSPEND_WBCOLOR			 ,sizeof(LX_DIMM_WBCOLOR_CTRL_T) ,DIMM_IO_WbColorControl	   ,NULL},
};
#endif

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern int  g_dimm_suspended;

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DIMM_SUSPEND
static int g_dimm_resumed  = FALSE;
static DIMM_KLIST_T *spDimmList = NULL;
static int dimm_copy_from_user(unsigned short indx, void * to, const void __user * from, unsigned int n);
#endif

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize DIMM module.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_Init(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_INFO_T stParams;
	UINT32 *lpLut = NULL;
	UINT32 dataSize;
#ifdef USE_DIMM_SUSPEND
	LX_DIMM_LUT_CTRL_T stTable;
#endif
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	LX_DIMM_INFO_T *pstParams = (LX_DIMM_INFO_T *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_INIT;
#endif

	do {
		if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_INIT, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
#ifdef USE_DIMM_SUSPEND
		if (!g_dimm_suspended)
#endif
		{
			ret = RET_ERROR;
			dataSize = GET_BITS(stParams.u32length, 0, 16) * sizeof(*stParams.InitData);
			if (!dataSize) break;
			if (!stParams.InitData) break;
			lpLut = OS_KMalloc(dataSize);
			CHECK_KNULL(lpLut);
			if ( copy_from_user(lpLut, (void __user *)stParams.InitData, dataSize) ) break;
			stParams.InitData = lpLut;
			ret = DIMM_HAL_Init(&stParams);
#ifdef USE_DIMM_SUSPEND
			if (ret) break;
			stTable.pLut   = lpLut;
			stTable.u32Num = stParams.u32length;
			ret = DIMM_AddTableToKList(spDimmList, &stTable);
		} else {
			stParams.u32length = 0;
			stParams.InitData  = NULL;
			ret = DIMM_HAL_Init(&stParams);
#endif
		}
	} while (0);
	OS_Free(lpLut);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control local-dimming-on.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_LocaldimmingControl(unsigned long arg)
{
	int ret = RET_ERROR;
	BOOLEAN stParams;
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	BOOLEAN *pstParams = (BOOLEAN *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_LOCALDIMMING_CONTROL;
#endif

	do {
        if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_LOCALDIMMINGCONTROL, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_LocaldimmingControl(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Dimming Store Demo Mode.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_StoreDemo(unsigned long arg)
{
	int ret = RET_ERROR;
	BOOLEAN stParams;
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	BOOLEAN *pstParams = (BOOLEAN *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_STORE_DEMO;
#endif

	do {
        if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_STOREDEMO, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_StoreDemo(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Dimming Line Demo Mode.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_LineDemo(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_LINE_CTRL_T stParams;
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	LX_DIMM_LINE_CTRL_T *pstParams = (LX_DIMM_LINE_CTRL_T *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_LINE_DEMO;
#endif

	do {
        if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_LINEDEMO, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_LineDemo(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Pixel Compensation.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_ControlCompensation(unsigned long arg)
{
	int ret = RET_ERROR;
	BOOLEAN stParams;
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	BOOLEAN *pstParams = (BOOLEAN *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_CONTROL_COMPENSATION;
#endif

	do {
        if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_CONTROLCOMPENSATION, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_ControlCompensation(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Look up Table.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_LutControl(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_LUT_CTRL_T stParams;
	UINT32 *lpLut = NULL;
	UINT32 dataSize;
#ifdef USE_DIMM_SUSPEND
	LX_DIMM_LUT_CTRL_T *pParam;
	DIMM_KLIST_T	   *pItem;
#endif
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	LX_DIMM_LUT_CTRL_T *pstParams = (LX_DIMM_LUT_CTRL_T *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_LUT_CONTROL;
#endif

	do {
		if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_LUTCONTROL, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
		ret = RET_ERROR;
#ifdef USE_DIMM_SUSPEND
		if (!g_dimm_suspended)
#endif
		{
			dataSize = GET_BITS(stParams.u32Num, 0, 16) * sizeof(*stParams.pLut);
			if (!dataSize) break;
			if (!stParams.pLut) break;
			lpLut = OS_KMalloc(dataSize);
			CHECK_KNULL(lpLut);
			if ( copy_from_user(lpLut, (void __user *)stParams.pLut, dataSize) ) break;
			stParams.pLut = lpLut;
			ret = DIMM_HAL_LutControl(&stParams);
#ifdef USE_DIMM_SUSPEND
			if (ret) break;
			ret = DIMM_AddTableToKList(spDimmList, &stParams);
		} else {
			CHECK_KNULL(spDimmList);
			pItem = spDimmList;
			while (NULL != (pItem = DIMM_NextItmeFromKlist(spDimmList, pItem))) {
				pParam = pItem->pData;
				if (!pParam) continue;
				ret = DIMM_HAL_LutControl(pParam);
				if (ret) break;
			}
#endif
		}
	} while (0);
	OS_Free(lpLut);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Local Dimming Control for Store Mode.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_StoreControl(unsigned long arg)
{
	int ret = RET_ERROR;
	BOOLEAN stParams;
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	BOOLEAN *pstParams = (BOOLEAN *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_STORE_CONTROL;
#endif

	do {
        if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_STORECONTROL, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_StoreControl(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Local Dimming Control White Balance Color.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_WbColorControl(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_WBCOLOR_CTRL_T stParams;
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DIMM_SUSPEND
	LX_DIMM_WBCOLOR_CTRL_T *pstParams = (LX_DIMM_WBCOLOR_CTRL_T *)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_WBCOLOR_CTRL;
#endif

	do {
        if ( DIMM_COPY_FROM_USER(DIMM_SUSPEND_WBCOLOR, &stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DIMM_IPC_SETDATA(ipcCmd, stParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_WbColorControl(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Read Register
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_RegRd(unsigned long arg)
{
	int ret = RET_ERROR;
	UINT32 *pstParams = (UINT32 *)arg;
	UINT32 addr;
	UINT32 data;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_REG_RD;
#endif

	do {
        if ( copy_from_user(&addr, (void __user *)pstParams, sizeof(UINT32)) ) break;
		data = DIMM_HAL_RegRd(addr);
        if ( copy_to_user((void __user *)pstParams, &data, sizeof(UINT32)) ) break;
		ret = RET_OK;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_RegWr(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_REG_WRITE_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_REG_WR;
#endif

	do {
		if ( copy_from_user(&stParams, (void __user *)arg, sizeof(stParams)) ) break;
		ret = DIMM_HAL_RegWr(&stParams);
	} while (0);

	return ret;
}

#ifdef USE_DIMM_TEMPORAL_DEFINITION
/**
 * @callgraph
 * @callergraph
 *
 * @brief Get DIMM INFO.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_GetVersion(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_VERSION_T stParams;
	LX_DIMM_VERSION_T *pstParams = (LX_DIMM_VERSION_T *)arg;
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_GET_VERSION;

	do {
        if ( copy_from_user(&stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_GetVersion(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief For DIMM debugging.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_DbgControl(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_DBG_CTRL_T stParams;
	LX_DIMM_DBG_CTRL_T *pstParams = (LX_DIMM_DBG_CTRL_T *)arg;
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_DBG_CONTROL;

	do {
        if ( copy_from_user(&stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_DbgControl(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief BLU(Back Light Uint) Control of DIMM.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_IO_BluControl(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_DIMM_BLU_CTRL_T stParams;
	LX_DIMM_BLU_CTRL_T *pstParams = (LX_DIMM_BLU_CTRL_T *)arg;
	DE_IPC_CMD_T ipcCmd = DIMM_IPC_BLU_CONTROL;

	do {
        if ( copy_from_user(&stParams, (void __user *)arg, sizeof(stParams)) ) break;
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		if (ret) break;
#endif
		ret = DIMM_HAL_BluControl(&stParams);
	} while (0);

	return ret;
}
#endif

#ifdef USE_DIMM_SUSPEND
static int dimm_copy_from_user(unsigned short indx, void * to, const void __user * from, unsigned int n)
{
    int ret = RET_OK;
    DIMM_SUSPEND_STORE_T *pStore = NULL;

    do {
		if (!g_dimm_suspended) {
			if (copy_from_user(to, from, n)) BREAK_WRONG(n);
			if (g_dimm_resumed) break;
		}
		if (!n) break;
		if ( !(indx < ARRAY_SIZE(dimm_suspend_store)) ) BREAK_WRONG(indx);
		pStore = &dimm_suspend_store[indx];
		CHECK_KNULL(pStore);
		CHECK_KNULL(pStore->pData);
		if (pStore->indx != indx) BREAK_WRONG(indx);
		if (!g_dimm_suspended) {
			if (!memcpy(pStore->pData, to, n)) BREAK_WRONG(n);
			pStore->size = n;
		} else {
			if (!pStore->size) BREAK_SETV(ret, 1);
			if (pStore->size != n) BREAK_WRONG(n);
			if (!memcpy(to, pStore->pData, n)) BREAK_WRONG(n);
		}
    } while (0);

    return ret;
}

int DIMM_IO_probe(void)
{
    int ret = RET_OK;
    DIMM_SUSPEND_STORE_T *pStore = NULL;
    int indx;

    for (indx=0;indx<ARRAY_SIZE(dimm_suspend_store);indx++) {
        pStore = &dimm_suspend_store[indx];
        CHECK_KNULL(pStore);
        pStore->pData = OS_Malloc(pStore->size);
        CHECK_KNULL(pStore->pData);
		pStore->size = 0;
    }
	spDimmList = DIMM_InitKList();

    return ret;
}

int DIMM_IO_remove(void)
{
    int ret = RET_OK;
    DIMM_SUSPEND_STORE_T *pStore = NULL;
    int indx;

    for (indx=0;indx < ARRAY_SIZE(dimm_suspend_store);indx++) {
        pStore = &dimm_suspend_store[indx];
        CHECK_KNULL(pStore);
        OS_Free(pStore->pData);
    }
	OS_Free(spDimmList);

    return ret;
}

int DIMM_IO_resume(void)
{
    int ret = RET_OK;
    DIMM_SUSPEND_STORE_T *pStore = NULL;
    int indx;

    for (indx=0;indx<ARRAY_SIZE(dimm_suspend_store);indx++) {
        pStore = &dimm_suspend_store[indx];
        CHECK_KNULL(pStore);
        if (!pStore->bOn) break;
        ret = pStore->susF(0);
		if (ret > 0) continue;
        if (ret) break;
    }
	//g_dimm_resumed = TRUE;

    return ret;
}
#endif
/**  @} */
