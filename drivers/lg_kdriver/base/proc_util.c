
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
 *	Linux proc file system utility
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version		1.0
 *  date		2009.11.14
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
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "proc_util.h"
#include "debug_util.h"
#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	BASE_PROC_NAME		"lg"

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* proc_util makes proc data using module_id and proc_id */
#define	MK_PROC_DATA(idx,id)		(((idx)<<16)|(id))
#define GET_MODULE_ID(data)			(((UINT32)(data))>>16)
#define GET_PROC_ID(data)			(((UINT32)(data))&0xffff)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	char					module_name[LX_MAX_DEVICE_NAME];
	OS_PROC_DESC_TABLE_T*	module_proc_table;
	struct proc_dir_entry*	module_proc_dir;

	int						max_proc_num;
	OS_PROC_READ_FUNC_T		ext_read_proc;
	OS_PROC_WRITE_FUNC_T	ext_write_proc;
}
PROC_MANAGE_TABLE_T;

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
static int	_OS_PROC_CreateEntry( char*	module_name,OS_PROC_DESC_TABLE_T* pTable, void* read_function, void* write_function, BOOLEAN fExtMode );
static int	_OS_PROC_Reader 	( char* buffer, char** buffer_location, off_t offset, int buffer_length, int* eof, void* data );
static int	_OS_PROC_Writer		( struct file* file, const char* buffer, unsigned long count, void* data );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static OS_SEM_T						 	_g_proc_sem;
static struct proc_dir_entry*			_g_proc_base_dir;
static PROC_MANAGE_TABLE_T				_g_base_manage_table[LX_MAX_DEVICE_NUM];

/*========================================================================================
	Implementation Group
========================================================================================*/
/** @name Function Definition for Proc Utility
 * function list for proc utility
 *
 * @{
*/

/**
 * Initialize proc utility system.
 * This function should be called at main device initialization
 *
 * @see base_device_init
*/
void		OS_PROC_Init	  	( void )
{
	OS_InitMutex(&_g_proc_sem, OS_SEM_ATTR_DEFAULT);

	memset( _g_base_manage_table, 0x0, sizeof(PROC_MANAGE_TABLE_T) * LX_MAX_DEVICE_NUM );
	_g_proc_base_dir = proc_mkdir ( BASE_PROC_NAME, NULL );

	OS_LockMutex(&_g_proc_sem);


	OS_UnlockMutex(&_g_proc_sem);
}

/**
 * Cleanup proc utility system
 * This function should be called at main deivce cleanup
 *
 * @see base_device_shutdown
*/
void		OS_PROC_Cleanup	( void )
{
	int	ret;

	OS_PROC_FlushEntry( );

	ret = OS_LockMutex(&_g_proc_sem);
	remove_proc_entry ( BASE_PROC_NAME, NULL );
	OS_UnlockMutex(&_g_proc_sem);

	/* remove mutex ? */
}


/**
 * create proc entry for each module
 *
 * @param base_name [IN] module name
 * @param pTable [IN] pointer to proc description table
 * @param read_function [IN] read proc callback for read operation ( application reads something from driver )
 * @param write_function [IN] write proc callback for write operation ( application writes something to driver )
 * @returns RET_OK(0) if success, none zero for otherwise
 *
 * @see OS_PROC_CreateEntryEx
 * @see OS_PROC_RemoveEntry
 * @see OS_PROC_fush_entry
 *
*/
int			OS_PROC_CreateEntry (	char*					module_name,
									OS_PROC_DESC_TABLE_T*	pTable,
									read_proc_t*			read_function,
									write_proc_t*			write_function )
{
	return _OS_PROC_CreateEntry( module_name, pTable, read_function, write_function, FALSE );
}

/**
 * create proc entry for each module
 *
 * @param base_name [IN] module name
 * @param pTable [IN] pointer to proc description table
 * @param read_function [IN] read proc callback for read operation ( application reads something from driver )
 * @param write_function [IN] write proc callback for write operation ( application writes something to driver )
 * @returns RET_OK(0) if success, none zero for otherwise
 *
 * @see OS_PROC_CreateEntry
 * @see OS_PROC_RemoveEntry
 * @see OS_PROC_fush_entry
 *
*/
int			OS_PROC_CreateEntryEx ( char*					module_name,
									OS_PROC_DESC_TABLE_T*	pTable,
									OS_PROC_READ_FUNC_T		read_function,
									OS_PROC_WRITE_FUNC_T	write_function )
{
	return _OS_PROC_CreateEntry( module_name, pTable, read_function, write_function, TRUE );
}

static int	_OS_PROC_CreateEntry(	char*					module_name,
									OS_PROC_DESC_TABLE_T*	pTable,
									void*					read_function,
									void*					write_function,
									BOOLEAN					fExtMode )
{
	int		i, j;
	int		ret;
	mode_t	entry_mode;
	struct	proc_dir_entry*	proc_entry;

	read_proc_t*		read_proc  = NULL;
	write_proc_t*		write_proc = NULL;

	if ( NULL == module_name || NULL == pTable || NULL == read_function )
	{
		DBG_PRINT_WARNING("null argument (%c,%c,%c)\n", (module_name)? 'O':'-', (pTable)? 'O':'-', (read_function)? 'O':'-' );
		return RET_INVALID_PARAMS;
	}

	ret = OS_LockMutex(&_g_proc_sem);

	for (i=0; i< LX_MAX_DEVICE_NUM; i++ )
	{
		if ( NULL == _g_base_manage_table[i].module_proc_table ) { /* found empty */ break; }
	}

	if ( i >= LX_MAX_DEVICE_NUM )
	{
		DBG_PRINT_WARNING("proc register failed. no empty slot.\n" );
		ret = RET_INVALID_PARAMS; goto function_exit;
	}

	/* if ext mode, internal proc function will be used */
	if ( fExtMode )
	{
		_g_base_manage_table[i].ext_read_proc = read_function;
		_g_base_manage_table[i].ext_write_proc= write_function;
	}
	else
	{
		_g_base_manage_table[i].ext_read_proc = NULL;
		_g_base_manage_table[i].ext_write_proc= NULL;
	}

	read_proc = ( fExtMode )? _OS_PROC_Reader : (read_proc_t*)read_function;
	write_proc= ( fExtMode )? _OS_PROC_Writer: (write_proc_t*)write_function;

	/* make proc structure */
	_g_base_manage_table[i].module_proc_table = pTable;
	snprintf( _g_base_manage_table[i].module_name, LX_MAX_DEVICE_NAME-1, "%s", module_name );

	_g_base_manage_table[i].module_proc_dir = proc_mkdir ( module_name, _g_proc_base_dir );

	for ( j=0; pTable[j].name ; j++ )
	{
		entry_mode = ( pTable[j].flag & OS_PROC_FLAG_WRITE )? 0644: 0444;

		if ( pTable[j].flag & OS_PROC_FLAG_FOP )
		{
			proc_entry = create_proc_entry( pTable[j].name, entry_mode, _g_base_manage_table[i].module_proc_dir );

			/* override operation pointer and private data of proc_entry */
			if ( proc_entry )
			{
				proc_entry->proc_fops	= (struct file_operations *) pTable[j].fop;
				proc_entry->data		= (void*)pTable[j].data;
			}
		}
		else
		{
			proc_entry = create_proc_entry( pTable[j].name, entry_mode, _g_base_manage_table[i].module_proc_dir );

			proc_entry->read_proc	= ( pTable[j].flag & OS_PROC_FLAG_READ )? read_proc : NULL;
			proc_entry->write_proc	= ( pTable[j].flag & OS_PROC_FLAG_WRITE)? write_proc: NULL;
//			proc_entry->owner		= THIS_MODULE;
//			proc_entry->mode		= S_IFREG | S_IRUGO;
//			proc_entry->uid			= 0;
//			proc_entry->gid			= 0;
//			proc_entry->size		= 80;
			proc_entry->data		= (void*)( (fExtMode)? MK_PROC_DATA( i, pTable[j].id ) : pTable[j].id );
		}
	}

	_g_base_manage_table[i].max_proc_num = j;

function_exit:
	OS_UnlockMutex(&_g_proc_sem);

	return RET_OK;
}

/**
 * remove proc entry for each module
 *
 * @param	base_name [IN] base module name
 * @returns RET_OK(0) if success, none zero for otherwise
 *
*/
int			OS_PROC_RemoveEntry ( char*		module_name )
{
	int		i, j;
	int		ret;
	PROC_MANAGE_TABLE_T	manage_table;

	if ( NULL == module_name )
	{
		DBG_PRINT_WARNING("null argument\n");
		return RET_INVALID_PARAMS;
	}

	ret = OS_LockMutex(&_g_proc_sem);

	for ( i=0 ; i<LX_MAX_DEVICE_NUM ; i++ )
	{
		if ( !_g_base_manage_table[i].module_name ) continue;

		if ( !strcmp ( _g_base_manage_table[i].module_name, module_name ) )
		{
			manage_table = _g_base_manage_table[i];
			memset( &_g_base_manage_table[i], 0x0, sizeof(PROC_MANAGE_TABLE_T) );
			break;
		}
	}

	if ( i >= LX_MAX_DEVICE_NUM )
	{
		ret = RET_INVALID_PARAMS; goto function_exit;
	}

	for ( j=0; manage_table.module_proc_table[j].name ; j++ )
	{
		remove_proc_entry( manage_table.module_proc_table[j].name, manage_table.module_proc_dir );
	}

	remove_proc_entry ( manage_table.module_name, _g_proc_base_dir );

	ret = 0;

function_exit:
	OS_UnlockMutex(&_g_proc_sem);

	return ret;
}

/**
 * flush all proc entries
 *
*/
void		OS_PROC_FlushEntry	( void )
{
	int	i,j;
	int	ret;
	PROC_MANAGE_TABLE_T	manage_table;

    ret = OS_LockMutex(&_g_proc_sem);

	for ( i=0; i<LX_MAX_DEVICE_NUM ; i++ )
	{
		manage_table = _g_base_manage_table[i];

		if ( !manage_table.module_proc_table ) continue;

		manage_table = _g_base_manage_table[i];

		for ( j=0; manage_table.module_proc_table[j].name ; j++ )
		{
			remove_proc_entry( manage_table.module_proc_table[j].name, manage_table.module_proc_dir );
		}

		remove_proc_entry ( manage_table.module_name, _g_proc_base_dir );

		memset( &_g_base_manage_table[i], 0x0, sizeof(PROC_MANAGE_TABLE_T) );
	}

    OS_UnlockMutex(&_g_proc_sem);
}

/* internal read proc function
 * checks basic error condition and calls simple user-defined read proc
 *
 */
static int	_OS_PROC_Reader ( char* buffer, char** buffer_location, off_t offset, int buffer_length, int* eof, void* data )
{
	UINT32	moduleId= GET_MODULE_ID(data);
	UINT32	procId  = GET_PROC_ID(data);

	OS_PROC_READ_FUNC_T	ext_read_proc;

	if ( offset > 0 )
	{
    	/* we've finished to read, return 0 */ goto read_proc_exit;
	}

	if ( moduleId >= LX_MAX_DEVICE_NUM )
	{
    	DBG_PRINT_WARNING("unknown module (%d)\n", moduleId );
    	/* we've finished to read, return 0 */ goto read_proc_exit;
	}

    if ( procId >= _g_base_manage_table[moduleId].max_proc_num )
    {
    	DBG_PRINT_WARNING("unknown proc (%d)\n", procId );
    	/* we've finished to read, return 0 */ goto read_proc_exit;
    }

	ext_read_proc = _g_base_manage_table[moduleId].ext_read_proc;

	if ( ext_read_proc ) return ext_read_proc ( procId, buffer );

read_proc_exit:
	return 0;
}

/* internal read proc function
 * checks basic error condition and calls simple user-defined write proc
 *
 */
static int	_OS_PROC_Writer( struct file* file, const char* buffer, unsigned long count, void* data )
{
    int		i;
    char	msg[LX_MAX_WRITE_PROC_BUFSZ];
	UINT32	moduleId= GET_MODULE_ID(data);
	UINT32	procId  = GET_PROC_ID(data);

   	OS_PROC_WRITE_FUNC_T	ext_write_proc;

	if ( moduleId >= LX_MAX_DEVICE_NUM )
	{
    	DBG_PRINT_WARNING("unknown module (%d)\n", moduleId );
    	/* we've finished to write, return 0 */ goto write_proc_exit;
	}

    if ( procId >= _g_base_manage_table[moduleId].max_proc_num )
    {
    	DBG_PRINT_WARNING("unknown proc (%d)\n", procId );
    	/* we've finished to write, return 0 */ goto write_proc_exit;
    }

    /* copy buffer to internal msg */
    if ( count > (LX_MAX_WRITE_PROC_BUFSZ - 1))
         count = LX_MAX_WRITE_PROC_BUFSZ - 1;

    for( i = 0; i <count; i++)
    {
    	get_user(msg[i], buffer+i);
    }
    msg[i] = '\0';

	ext_write_proc = _g_base_manage_table[moduleId].ext_write_proc;

	if (ext_write_proc) return ext_write_proc ( procId, msg );

write_proc_exit:
	return 0;
}

/** @} */
/** @} */

