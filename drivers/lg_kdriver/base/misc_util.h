
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
 *  @author     raxis
 *  @version    1.0
 *  @date       2010-02-27
 *  @note       Additional information.
 *  @addtogroup lg1150_base
 *  @{
 */

#ifndef	_MISC_UTIL_H_
#define	_MISC_UTIL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include <linux/string.h>

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

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
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/** dump memory buffer with beautiful format
 *
 * @param disp_addr [IN] start address of display address
 * @param memptr [IN] memory buffer
 * @param cnt [IN] byte count of dump data
 * @param out_buf [OUT] if not NULL, all dump data is stored to out_buf. 
 *						so size of out_buf shoule be enough to hold dump data.
 * @return write count if out_buf is not NULL. otherwise return 0.
 */
#define	OS_HexDump(disp_addr,data_ptr,data_cnt)	(void)OS_HexDumpEx(disp_addr,data_ptr,data_cnt,NULL)
extern	int		OS_HexDumpEx ( UINT32 disp_addr, void* data_ptr, UINT32 data_cnt, char* output_buf );

#define	OS_RegHexDump(disp_addr,reg_ptr,reg_size)	(void)OS_RegHexDumpEx(disp_addr,reg_ptr,reg_size,NULL)
extern	int		OS_RegHexDumpEx ( UINT32 disp_addr, UINT32* reg_ptr, UINT32 reg_size, char* output_buf );

/**	simple strtok to support multi thread safety
 *
 */
extern	char* 	OS_strtok ( char *s, const char *delim, char **save_ptr );

/** convert simple string to standard argc, argv 
 *	this function allocates new string so caller function should free argv memory	
 *
 *	@return RET_OK when success, RET_ERROR otherwise
 */
typedef struct
{
    char	arglist[128];
    char*   argv[32];
  	int     argc;
}
STDC_ARGS_T;

extern	STDC_ARGS_T* 	OS_Str2Argv ( char* s );

/** simple scan utilty for /proc/cmdline 
 *
 *	@code
 *
 *	char mem_str[32];
 *	int rc = OS_ScanCmdLine( "mem", mem_str );
 *
 *  if ( rc == RET_OK ) printk( "mem=%s\n", mem_str );
 *
 *	@endcode
 *
 *	@param tok [IN]  token string to find
 *	@param str [OUT] string array
 */
extern int				OS_ScanCmdLine ( char* tok, char* str );

extern char*			OS_ParseFileName ( const char* filepath );

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

/** @} */

