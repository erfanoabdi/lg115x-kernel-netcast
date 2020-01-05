
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
 *  Linux proc interface for gfx device.
 *	gfx device will teach you how to make device driver with new platform.
 *
 *  author		raxis.lim (raxis.lim@lge.com).lim (raxis.lim@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_gfx
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
#include "proc_util.h"
#include "gfx_impl.h"

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
	PROC_ID_CMD_DELAY,
	PROC_ID_MEM_STAT,
	PROC_ID_REG_DUMP,
	PROC_ID_SURFACE,
	PROC_ID_GFX_STATUS,
	PROC_ID_PERF_LOG,
	PROC_ID_RESET,
	PROC_ID_SYNC_TMOUT,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern GFX_SURFACE_OBJ_T 		*g_gfx_surf_list;
extern int						g_gfx_perf_log;

#if 0
extern volatile GFX_REG_MAP_T   *g_gfx_reg_l8;
extern GFX_REG_MAP_T            *g_gfx_reg_l8_cache;
#endif

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static OS_PROC_DESC_TABLE_T	_g_gfx_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , 	OS_PROC_FLAG_READ },
	{ "cmd_delay",	PROC_ID_CMD_DELAY,	OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "mem_stat",	PROC_ID_MEM_STAT , 	OS_PROC_FLAG_READ },
	{ "reg_dump",	PROC_ID_REG_DUMP , 	OS_PROC_FLAG_READ },
	{ "surface",	PROC_ID_SURFACE,	OS_PROC_FLAG_READ },
	{ "status",		PROC_ID_GFX_STATUS,	OS_PROC_FLAG_READ },
	{ "perflog",	PROC_ID_PERF_LOG,	OS_PROC_FLAG_WRITE },
	{ "reset",		PROC_ID_RESET, 		OS_PROC_FLAG_WRITE },
	{ "synctm",		PROC_ID_SYNC_TMOUT,	OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ NULL, 		PROC_ID_MAX		, 	0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/

/*
 * read_proc implementation of gfx device
 *
*/
static int	_GFX_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = sprintf( buffer, "%s\n", "raxis.lim (raxis.lim@lge.com)" );
		}
		break;

		case PROC_ID_CMD_DELAY:
		{
			UINT32	cmd_delay;

			(void)GFX_GetCommandDelay( &cmd_delay );
			ret = sprintf( buffer, "-- cmd delay : 0x%x (%d)\n", cmd_delay, cmd_delay );
		}
		break;

		/* dump GFX memory status */
		case PROC_ID_MEM_STAT:
		{
			int	len;
			LX_GFX_MEM_STAT_T	stat;
			(void)GFX_GetSurfaceMemoryStat( &stat );

			len =0;
			len += sprintf( buffer +len, "-- mem base  : %6dMB (%p - physical)\n", ((UINT32)stat.surface_mem_base)>>10, stat.surface_mem_base );
			len += sprintf( buffer +len, "-- mem len   : %6dKB (%9d)\n",stat.surface_mem_length>>10, stat.surface_mem_length );
			len += sprintf( buffer +len, "-- alloc size: %6dKB (%9d)\n",stat.surface_mem_alloc_size>>10, stat.surface_mem_alloc_size );
			len += sprintf( buffer +len, "-- free  size: %6dKB (%9d)\n",stat.surface_mem_free_size>>10, stat.surface_mem_free_size );
			len += sprintf( buffer +len, "-- alloc cnt : %6d\n", stat.surface_alloc_num );

			ret = len;
		}
		break;

		/* dump surface info */
		case PROC_ID_SURFACE:
		{
			int		i;
			int		len = 0;
			int		surface_cnt = 0;

			for ( i=0; i< GFX_MAX_SURFACE; i++ )
			{
				GFX_SURFACE_OBJ_T*	surface = &g_gfx_surf_list[i];

				
				if ( surface->bAlloc )
				{
					surface_cnt++;
#if 0
					len += sprintf( buffer+len, "[%4d] %d:%d:%3d:%8p - %d:%2x:%4dx%3d:%d:%d:%p - %8p:%8x:%7d\n",
						i,
						surface->bPalette, surface->bPalDownload, surface->PalSize, surface->pal,
						surface->surf.type, surface->surf.pixel_format, 
						surface->surf.width, surface->surf.height,
						surface->surf.alignment, surface->surf.stride, surface->surf.phys_addr, 
						surface->mem.phys_addr, surface->mem.offset, surface->mem.length );
#endif
					printk( "[%3x(%3d)] %d:%3d:%4d:%08x - %d:%2x:%4dx%4d - %d:%4d - %d - %8p:%8x:%7d %s\n",
						i, i,
						surface->bPalette, surface->PalSize, surface->cIdx, surface->cTick,
						surface->surf.type, surface->surf.pixel_format, surface->surf.width, surface->surf.height,
						surface->surf.alignment, surface->surf.stride, 
						(surface->pal)? 1:0,	
						surface->mem.phys_addr, surface->mem.offset, surface->mem.length, surface->psname );
				}
			}

			len += sprintf( buffer+len, "%d surfaces created\n", surface_cnt );

			ret = len;
		}
		break;

		case PROC_ID_GFX_STATUS:
		{
			int	len;
			GFX_CMD_QUEUE_CTRL_T status;	
			GFX_GetComQueueStatus( &status );

			len = 0;
			
			len += sprintf( buffer+len, " -- usLine  : 0x%x\n", status.usLine );
			len += sprintf( buffer+len, " -- bStatus : 0x%x\n", status.bStatus );
			len += sprintf( buffer+len, " -- usRemainSpace: 0x%x\n", status.usRemainSpace );
			len += sprintf( buffer+len, " -- bFull        : 0x%x\n", status.bFull );
			len += sprintf( buffer+len, " -- usRemainParam: 0x%x\n", status.usRemainParam  );
			len += sprintf( buffer+len, " -- bBatchStatus : 0x%x\n", status.bBatchStatus   );

			ret = len;
		}
		break;

		/* dump GFX register */
		case PROC_ID_REG_DUMP:
		{
			GFX_DumpRegister( );
			ret = sprintf( buffer, "ok\n");
		}
		break;

		case PROC_ID_SYNC_TMOUT:
		{
			int len = 0;
			len += sprintf( buffer+len, "sync wait timeout = %d ms\n", 	g_gfx_cfg.sync_wait_timeout );
			len += sprintf( buffer+len, "fail retry count  = %d \n", 	g_gfx_cfg.sync_fail_retry_count );
			ret = len;
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
 * write_proc implementation of gfx device
 *
*/
static int _GFX_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_CMD_DELAY:
		{
			char*	endp;
			UINT32	cmd_delay;

			cmd_delay = simple_strtoul( command, &endp, 16 );
//			sscanf( command, " %x", &cmd_delay );

			(void)GFX_SetCommandDelay( (cmd_delay>0x7ff)? 0x7ff: 0x0 );
			(void)GFX_GetCommandDelay( &cmd_delay );
			printk( "-- cmd delay : 0x%x (%d)\n", cmd_delay, cmd_delay );
		}
		break;

		case PROC_ID_PERF_LOG:
		{
			char*	endp;
			UINT32	val;
			val = simple_strtoul( command, &endp, 10 );
			g_gfx_perf_log = val;
		}
		break;
		
		case PROC_ID_RESET:
		{

		}
		break;

		case PROC_ID_SYNC_TMOUT:
		{
			int	timeout, retry;
			sscanf( command, " %d %d", &timeout, &retry );

			g_gfx_cfg.sync_wait_timeout = timeout;
			g_gfx_cfg.sync_fail_retry_count = retry;	
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

/*
 * initialize proc utility for gfx device
 *
 * @see GFX_Init
*/
void	GFX_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( GFX_MODULE, _g_gfx_device_proc_table,
											_GFX_ReadProcFunction,
											_GFX_WriteProcFunction );
}

/*
 * cleanup proc utility for gfx device
 *
 * @see GFX_Cleanup
*/
void	GFX_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( GFX_MODULE );
}

/** @} */

