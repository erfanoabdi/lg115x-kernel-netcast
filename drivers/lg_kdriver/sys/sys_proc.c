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
 *  Linux proc interface for sys device.
 *	sys device will teach you how to make device driver with new platform.
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2010.12.13
 *  note		Additional information.
 *
 *  @addtogroup lg1150_sys
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include "sys_drv.h"
#include "proc_util.h"
#include "debug_util.h"
#include "base_drv.h"
#include "gfx_drv.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_COMMAND,
	PROC_ID_MEM_STAT,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
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
static OS_PROC_DESC_TABLE_T	_g_sys_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "command",	PROC_ID_COMMAND , OS_PROC_FLAG_WRITE },
	{ "mem_stat",	PROC_ID_MEM_STAT, OS_PROC_FLAG_READ },
	{ NULL, 		PROC_ID_MAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/

/*
 * read_proc implementation of sys device
 *
*/
static int	_SYS_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = sprintf( buffer, "%s\n", "ks.hyun (ks.hyun@lge.com)" );
		}
		break;

		case PROC_ID_MEM_STAT:
		{
#if 0	/* not ready */
			LX_MEMCFG_STAT_T cfg_stat;
			LX_GFX_MEM_STAT_T gfx_stat;
			UINT32 total, alloc;

			BASE_MEMCFG_GetStat(&cfg_stat);
			GFX_GetSurfaceMemoryStat(&gfx_stat);
			total = cfg_stat.size;
			alloc = cfg_stat.alloc;
			alloc -= gfx_stat.surface_mem_free_size;
#else
			UINT32 total, alloc;
			total = 0;
			alloc = 0;	
#endif
			ret = sprintf( buffer, "total    used\n");
			ret += sprintf( buffer + ret, "%08x %08x\n", total, alloc);
		}
		break;

		default:
		{
			ret = sprintf( buffer, "%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

/*
 * write_proc implementation of sys device
 *
*/
static int _SYS_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			printk("command string : %s\n", command );
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return strlen(command);
}

/**
 * initialize proc utility for sys device
 *
 * @see SYS_Init
*/
void	SYS_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( SYS_MODULE, _g_sys_device_proc_table,
											_SYS_ReadProcFunction,
											_SYS_WriteProcFunction );
}

/**
 * cleanup proc utility for sys device
 *
 * @see SYS_Cleanup
*/
void	SYS_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( SYS_MODULE );
}

/** @} */


