
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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		raxis
 *  @version	1.0
 *  @date		2010-02-27
 *  @note		Additional information.
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
#include <linux/uaccess.h>
#include <linux/ctype.h>
#include <asm/io.h>
#include "os_util.h"
#include "misc_util.h"

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
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

int    OS_RegHexDumpEx ( UINT32 disp_addr, UINT32* reg_ptr, UINT32 reg_size, char* output_buf )
{
	int	output_len = 0;

    if (reg_size > 0)
    {
        int width = 4;	/* 4 dword = 16 data */
        int j, i = 0;

		UINT32* str 	= reg_ptr;
        char* 	buf_ptr = (char*)OS_Malloc(100);
        int		buf_len = 0;

		if ( output_buf )
		{
        	output_len += sprintf( output_buf + output_len, "--------------------------------------------------\n");
    	    output_len += sprintf( output_buf + output_len, "address     00010203  04050607  08090A0B  0C0D0E0F\n");
        	output_len += sprintf( output_buf + output_len, "--------------------------------------------------\n");
		}
		else
		{
        	printk("--------------------------------------------------\n");
    	    printk("address     00010203  04050607  08090A0B  0C0D0E0F\n");
			printk("--------------------------------------------------\n");
		}

		i = 0; j = 0;

        while (i < reg_size )
        {
            buf_len = 0;
            buf_len += sprintf( buf_ptr + buf_len,"0x%08x  ", i+disp_addr);

            if (1)
            {
                for ( j = 0; j < width; j++)
                {
                    if (i+j < reg_size )
                    {
                        buf_len += sprintf( buf_ptr + buf_len,"%08x  ", str[j]);
                    }
                }
            }

            str += width;
            i += j*4;

        	if ( output_buf )
        	{
            	output_len += sprintf( output_buf + output_len, "%s\n", buf_ptr );
        	}
        	else
        	{
            	printk("%s\n", buf_ptr );
        	}
        }
    	OS_Free(buf_ptr);
    }

    return output_len;
}

int    OS_HexDumpEx ( UINT32 disp_addr, void* data_ptr, UINT32 data_cnt, char* output_buf )
{
  	int	output_len = 0;

    if (data_cnt > 0)
    {
        int width = 16;
        int j, i = 0;

        char*	str = (char*)data_ptr;
        char* 	buf_ptr = (char*)OS_Malloc(100);
        int		buf_len = 0;

		if ( output_buf )
		{
        	output_len += sprintf( output_buf + output_len, "--------------------------------------------------------------------------------\n");
    	    output_len += sprintf( output_buf + output_len, "address     00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\n");
        	output_len += sprintf( output_buf + output_len, "--------------------------------------------------------------------------------\n");
		}
		else
		{
        	printk("--------------------------------------------------------------------------------\n");
    	    printk("address     00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  0123456789ABCDEF\n");
			printk("--------------------------------------------------------------------------------\n");
		}

        while (i < data_cnt )
        {
            buf_len = 0;
            buf_len += sprintf( buf_ptr + buf_len,"0x%08x  ", i+disp_addr);

            if (1)
            {
                for (j = 0; j < width; j++) {
                    if (i+j < data_cnt )
                    {
                        buf_len += sprintf( buf_ptr + buf_len,"%02x ", (UINT8)str[j]);
                    }
                    else
                    {
                        buf_len += sprintf( buf_ptr + buf_len,"%s", "   ");
                    }

                    if ((j+1) % (width/2) == 0)
                    buf_len += sprintf( buf_ptr + buf_len,"%s", " ");
                }
            }

            for (j = 0; j < width; j++)
            {
                // 출력할 수 없는 문자의 경우 '.' 으로 출력
                if (i+j < data_cnt )
                    buf_len += sprintf( buf_ptr + buf_len, "%c", isprint(str[j])? str[j]:'.');
                else
                    buf_len += sprintf( buf_ptr + buf_len, "%s", " ");
            }

            str += width;
            i += j;

        	if ( output_buf )
        	{
            	output_len += sprintf( output_buf + output_len, "%s\n", buf_ptr );
        	}
        	else
        	{
            	printk("%s\n", buf_ptr );
        	}
        }
    	OS_Free(buf_ptr);
    }

    return output_len;
}

char* OS_strtok(char *s, const char *delim, char **save_ptr)
{
    char *token = 0;

    if (s == 0) s = *save_ptr;

    if (s)
	{
		*save_ptr = 0;
		s += strspn(s, delim);
        if (*s != '\0')
		{
            token = s;
            *save_ptr = strpbrk(token, delim);
            if (*save_ptr != 0)
			{
                *(*save_ptr)++ = '\0';
            }
        }
    }
    return token;
}


STDC_ARGS_T*    OS_Str2Argv ( char* command )
{
    char*   sav;
    char*   token;
    int     len;
	static const char delim[] = " \t\n";

    STDC_ARGS_T* a = (STDC_ARGS_T*)OS_Malloc(sizeof(STDC_ARGS_T));
    memset( a, 0x0, sizeof(STDC_ARGS_T));

    len = 0;
    token = OS_strtok( command, delim, &sav );

    while( token )
    {
        a->argv[a->argc] = a->arglist + len;
        len += sprintf( a->arglist + len, "%s%c", token, '\0' );

        if ( (a->argc+1) < 32 ) a->argc++; else break;

        token = OS_strtok( NULL, delim, &sav );
    }

    return a;
}

int              OS_ScanCmdLine ( char* tok, char* str )
{
	OS_FILE_T	cmdln_file;
	int	len;
	int	ret 	= RET_ERROR;
	char* cmdline = OS_Malloc(2048);

	if ( !cmdline ) return RET_ERROR;

	if ( RET_OK != OS_OpenFile( &cmdln_file, "/proc/cmdline", O_RDONLY|O_LARGEFILE, 0666 ) )
	{
		// OS_FREE is added. (Mantis problem : memory leak) 2011.08.21. zaewon.lee.
		OS_Free(cmdline);
		return RET_ERROR;
	}
    len = OS_ReadFile( &cmdln_file, cmdline, 2048 );
	if ( len <= 0 ) goto func_exit;

	cmdline[len-1] = 0x0;

	{
		char* tok_str;
		char* p;

		tok_str = strstr( cmdline, tok );
		if ( !tok_str ) goto func_exit;

		tok_str += strlen(tok);	// skip tok string
		for ( p=tok_str; *p != ' '; p++ ); *p = 0x0; // append NULL string

		strcpy( str, tok_str );
	}

	ret = RET_OK;
func_exit:
	if ( cmdline ) OS_Free(cmdline);
	OS_CloseFile( &cmdln_file );
	return ret;
}

char*            OS_ParseFileName ( const char* filepath )
{
	return strrchr( filepath, '/')+1;
}

