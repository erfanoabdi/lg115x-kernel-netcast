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


/** @file pe_reg.c
 *
 *  driver for picture enhance register read, write functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "pe_cfg.h"
#include "pe_reg.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_REG_ERROR	printk

#ifdef PE_USE_DBG_PRINT
#define PE_REG_DBG_PRINT(fmt,args...)	printk("[%x][%s,%d] "fmt,PE_CHIP_VER,__F__,__L__,##args)
#else
#define PE_REG_DBG_PRINT(fmt,args...)
#endif

#define PE_REG_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_REG_ERROR(fmt,##args);_action;}}

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
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_REG_WD(UINT32 addr, UINT32 value);
static UINT32 PE_REG_RD(UINT32 addr);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * write address data set
 *
 * @param   *table [in] PE_REG_PARAM_T
 * @param   offset [in] UINT32
 * @param   size [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_SetTable(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size)
{
	int ret = RET_ERROR;
	UINT32 table_size;
	int i;
	do {
		PE_REG_CHECK_CODE(!table,break,"[%s,%d] table is null.\n",__F__,__L__);
		PE_REG_CHECK_CODE(!size,break,"[%s,%d] size is zero.\n",__F__,__L__);
		table_size = size/sizeof(PE_REG_PARAM_T);
		for (i=0;i<table_size;i++) PE_REG_WD((table[i].addr+offset), table[i].data);
		ret = RET_OK;
	}while(0);
	return ret;
}
/**
 * read address data set
 *
 * @param   *table [in/out] PE_REG_PARAM_T
 * @param   offset [in] UINT32
 * @param   size [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_GetTable(PE_REG_PARAM_T *table, UINT32 offset, UINT32 size)
{
	int ret = RET_ERROR;
	UINT32 table_size;
	int i;
	do {
		PE_REG_CHECK_CODE(!table,break,"[%s,%d] table is null.\n",__F__,__L__);
		PE_REG_CHECK_CODE(!size,break,"[%s,%d] size is zero.\n",__F__,__L__);
		table_size = size/sizeof(PE_REG_PARAM_T);
		for (i=0;i<table_size;i++) table[i].data=PE_REG_RD(table[i].addr+offset);
		ret = RET_OK;
	}while(0);
	return ret;
}

/**
 * init phy to virtual addr
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_InitPhyToVirt(void)
{
	int ret = RET_OK;
	do {
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_REG_H13_InitPhyToVirt();
			PE_REG_CHECK_CODE(ret,break,"[%s,%d] PE_REG_H13_InitPhyToVirt() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_REG_L9_InitPhyToVirt();
			PE_REG_CHECK_CODE(ret,break,"[%s,%d] PE_REG_L9_InitPhyToVirt() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_REG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * free phy to virtual addr
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_FreePhyToVirt(void)
{
	int ret = RET_OK;
	do {
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_REG_H13_FreePhyToVirt();
			PE_REG_CHECK_CODE(ret,break,"[%s,%d] PE_REG_H13_FreePhyToVirt() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_REG_L9_FreePhyToVirt();
			PE_REG_CHECK_CODE(ret,break,"[%s,%d] PE_REG_L9_FreePhyToVirt() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_REG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * write address data
 *
 * @param   addr [in] UINT32
 * @param   value [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_REG_WD(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_REG_H13_WD(addr,value);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_REG_L9_WD(addr,value);
		}
		else
		#endif
		{
			PE_REG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * read address data
 *
 * @param   addr [in] UINT32, accessing for register
 * @return  value of register
 * @see
 * @author
 */
static UINT32 PE_REG_RD(UINT32 addr)
{
	UINT32 value = 0x0;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			value = PE_REG_H13_RD(addr);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			value = PE_REG_L9_RD(addr);
		}
		else
		#endif
		{
			PE_REG_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return value;
}

