/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/


/** @file
 *
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/platform.h>

#include "os_util.h"

#include "sdec_kapi.h"
#include "sdec_cfg.h"
#include "sdec_drv.h"
#include "sdec_io.h"

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
static OS_RGN_T g_SdecRgn;

static LX_SDEC_MEM_CFG_T _gstSdecMemMap;

/**
********************************************************************************
* @brief
*   initialize memory pool manager.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
int SDEC_MM_Init(UINT32 ui32Arg)
{
	int 				ret		= 0;
	LX_SDEC_GPB_INFO_T	*stpLXSdecGPBInfo;
	LX_SDEC_CFG_T		*pSdecConf = NULL;
	UINT8				memCfg = 0;

	/* get config */
	pSdecConf 	= SDEC_CFG_GetConfig();
	memCfg 		= pSdecConf->memCfg;

	/* 20110412 gaius.lee  : modify scheme used with config file. if memory address will be changed someday, we can modified memCfg value */
	_gstSdecMemMap.memory_name		= gMemCfgSDECGPB[memCfg].memory_name;
	_gstSdecMemMap.gpb_memory_base	= gMemCfgSDECGPB[memCfg].gpb_memory_base;
	_gstSdecMemMap.gpb_memory_size	= gMemCfgSDECGPB[memCfg].gpb_memory_size;

	stpLXSdecGPBInfo = (LX_SDEC_GPB_INFO_T *)ui32Arg;

	ret = OS_InitRegion( &g_SdecRgn , (void *)_gstSdecMemMap.gpb_memory_base , _gstSdecMemMap.gpb_memory_size);

	stpLXSdecGPBInfo->uiGpbBase = _gstSdecMemMap.gpb_memory_base;
	stpLXSdecGPBInfo->uiGpbSize = _gstSdecMemMap.gpb_memory_size;

	return ret;
}

/**
********************************************************************************
* @brief
*   Finalize memory pool manager.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
int SDEC_MM_Final(void)
{
	int 				ret		= 0;

	ret = OS_CleanupRegion( &g_SdecRgn);

	return ret;
}


/**
********************************************************************************
* @brief
*   allocate memory
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_MM_Alloc(UINT32 ui32Arg)
{
	DTV_STATUS_T	eRet	= NOT_OK;
	UINT32			size;
	void 			*ptr ;
	LX_SDEC_MM_Alloc	*stpLXSdecMMAlloc;

	if(ui32Arg == 0) goto EXIT;

	stpLXSdecMMAlloc = (LX_SDEC_MM_Alloc *)ui32Arg;

	/* get size */
	size = stpLXSdecMMAlloc->uiGpbSize;

	ptr = OS_MallocRegion ( &g_SdecRgn, size );

	if( ((UINT32)ptr >= _gstSdecMemMap.gpb_memory_base) && ((UINT32)ptr <= (_gstSdecMemMap.gpb_memory_base + _gstSdecMemMap.gpb_memory_size)))
	{
		stpLXSdecMMAlloc->uiGpbAddr = (UINT32) ptr;
		eRet = OK;
	}
	else
	{
		SDEC_DEBUG_Print("ERROR : dynamic allocation failed %08x\n" , (UINT32)ptr);
	}

EXIT:
	return eRet;
}


/**
********************************************************************************
* @brief
*   Free allocated memory
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_MM_Free(UINT32 ui32Arg)
{
	DTV_STATUS_T	eRet	= NOT_OK;
	int 			ret		= 0;
	UINT32			gpb_memory_base, gpb_memory__end;


	gpb_memory_base = _gstSdecMemMap.gpb_memory_base;
	gpb_memory__end = _gstSdecMemMap.gpb_memory_base + _gstSdecMemMap.gpb_memory_size;

	if(ui32Arg == 0) goto EXIT;

	/* check if memory address is valid */
	if(gpb_memory_base <= ui32Arg && ui32Arg <= gpb_memory__end)
	{
	}
	else
	{
		SDEC_DEBUG_Print("ERROR : memory address is incorrect 0x%08x\n" , gpb_memory_base);
		goto EXIT;
	}

	ret = OS_FreeRegion ( &g_SdecRgn, (void*)ui32Arg);

	if(ret == 0)		eRet = OK;

EXIT:
	return eRet;
}

/**
********************************************************************************
* @brief
* 	get memory statistics for sdec memory
*	application can use this information to monitor memroy usage.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
* @return
*  DTV_STATUS_T
********************************************************************************
*/

DTV_STATUS_T SDEC_MM_GetMemoryStat (UINT32 ui32Arg)
{
	OS_RGN_INFO_T   mem_info;
	LX_SDEC_MM_GetStat* pMemStat;

	pMemStat = (LX_SDEC_MM_GetStat*) ui32Arg;
	(void)OS_GetRegionInfo ( &g_SdecRgn, &mem_info );

	pMemStat->mem_base			= mem_info.phys_mem_addr;
	pMemStat->mem_length 		= mem_info.length;
	pMemStat->mem_alloc_size 	= mem_info.mem_alloc_size;
	pMemStat->mem_free_size 	= mem_info.mem_free_size;

	return OK;
}

