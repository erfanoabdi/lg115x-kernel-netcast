
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
 *	kdriver main
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version		1.0
 *  date		2009.11.04
 *
 *  @addtogroup lg1150_base
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_drv.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	AUTHOR_LIST				"raxis.lim@lge.com"
#define	PRINT_MASK_CONFIG_FILE	"/mnt/flash/data/kdrv-printmask.txt"

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
extern const struct file_operations memcfg_proc_fops;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static char*	print_mask_help_text =
	"<Usage> echo load cmd_file   > /proc/lg/base/print_mask\n"
	"        echo save cmd_file   > /proc/lg/base/print_mask\n"
	"        echo cmd  cmd_string > /proc/lg/base/print_mask\n";

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Debug proc system
========================================================================================*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_DCHIP,
	PROC_ID_ACHIP,
	PROC_ID_PLATFORM,
	PROC_ID_PRINT_MASK,
	PROC_ID_MEMCFG,
	PROC_ID_REG_RD,
	PROC_ID_REG_WR,
	PROC_ID_MAX,
};

static OS_PROC_DESC_TABLE_T	_g_base_proc_table[] =
{
	{ "author",			PROC_ID_AUTHOR, 	OS_PROC_FLAG_READ },
	{ "chip_rev",		PROC_ID_DCHIP, 		OS_PROC_FLAG_READ },
	{ "ace_rev",		PROC_ID_ACHIP, 		OS_PROC_FLAG_READ },
	{ "platform",		PROC_ID_PLATFORM, 	OS_PROC_FLAG_READ },
	{ "reg_rd",			PROC_ID_REG_RD,		OS_PROC_FLAG_WRITE },
	{ "reg_wr",			PROC_ID_REG_WR,		OS_PROC_FLAG_WRITE },
	{ "print_mask",		PROC_ID_PRINT_MASK,	OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "memcfg",			PROC_ID_MEMCFG,		OS_PROC_FLAG_READ|OS_PROC_FLAG_FOP, (void*)&memcfg_proc_fops },
	{ NULL, 			PROC_ID_MAX, 		0 }
};

static int	BASE_PROC_ReadProcFunction( UINT32 procId, char* buffer )
{
	int		len = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
            len += sprintf( buffer, "%s\n", AUTHOR_LIST );
		}
		break;

		case PROC_ID_DCHIP:
		{
			len += sprintf( buffer, "0x%x\n", lx_chip_rev() );
		}
		break;

		case PROC_ID_ACHIP:
		{
			len += sprintf( buffer, "0x%x\n", lx_ace_rev() );
		}
		break;

		case PROC_ID_PLATFORM:
		{
			len += sprintf( buffer, "0x%x\n", lx_chip_plt() );
		}
		break;

		case PROC_ID_PRINT_MASK:
		{
			len = _OS_DEBUG_DumpPrintMask ( buffer );

			len += sprintf( buffer+len, print_mask_help_text );
		}
		break;

		case PROC_ID_MEMCFG:
		{
			len += sprintf( buffer, "How can you call me?\n");
		}
		break;

		default:
		{
			len = sprintf( buffer, "%s(%d)\n", "unimplemented read proc",procId );
		}
	}

	return len;
}

/*
 * write_proc implementation of ttx device
 *
*/
static int BASE_PROC_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		/* command syntax :
		 *
		 *
		 *
		 */
		case PROC_ID_PRINT_MASK:
		{
			char	opt[8];
			char	ext[64];

			/* TODO: 테스트 코드이므로 예외 처리 없음 */

			sscanf( command, "%s %s", opt, ext );

			if ( !strcmp(opt, "cmd") )
			{
				if( RET_OK != _OS_DEBUG_SetPrintMask( ext ) )
				{
					printk("<error> invalid format for print_mask.\n"); break;
				}

				_OS_DEBUG_SavePrintMask(PRINT_MASK_CONFIG_FILE);
			}
			else if ( !strcmp(opt,"save") )
			{
				/* check if default config file will be used */
				if ( !strcmp(ext, "default") )
				{
					strcpy( ext, PRINT_MASK_CONFIG_FILE );
				}

				_OS_DEBUG_SavePrintMask( ext );
			}
			else if ( !strcmp(opt,"load") )
			{
				/* check if default config file will be used */
				if ( !strcmp(ext, "default") )
				{
					strcpy( ext, PRINT_MASK_CONFIG_FILE );
				}

				_OS_DEBUG_LoadPrintMask( ext );
			}
			else
			{
				printk("<error> unknown option \n%s\n", print_mask_help_text );
			}
		}
		break;

        case PROC_ID_REG_RD:
        {
            UINT32 addr, val;
            sscanf( command, " %x", &addr );
            OS_RdReg( addr, &val );
            printk("\nAddr 0x%x = 0x%08x\n", addr, val );
        }
        break;

        case PROC_ID_REG_WR:
        {
            UINT32 addr, val;

            sscanf( command, " %x %x", &addr, &val );
            OS_WrReg( addr, val );
            OS_RdReg( addr, &val );
            printk("\nAddr 0x%x = 0x%08x\n", addr, val );
        }
        break;
	}

	return strlen(command);
}

/**
 * Initialize proc system for debug utility
 *
 */
void	BASE_PROC_Init ( void )
{
	OS_PROC_CreateEntryEx ( "base" ,	_g_base_proc_table,
										BASE_PROC_ReadProcFunction,
										BASE_PROC_WriteProcFunction );
}

