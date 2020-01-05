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


/** @file pe_drv.h
 *
 *  driver interface header for pe device. ( used only within kdriver )
 *	
 *	@author		
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_DRV_H_
#define	_PE_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

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
//#define PE_PRINT	printk
#define PE_DRV_ERROR	printk

#ifdef PE_USE_DBG_PRINT
#define PE_DRV_DBG_PRINT(fmt,args...)	printk("[%s,%d] "fmt,__F__,__L__, ##args)
#else
#define PE_DRV_DBG_PRINT(fmt,args...)
#endif

#define PE_DRV_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_DRV_ERROR(fmt,##args);_action;}}
// to_do_list : #define PE_PRINT(format, args...)		DBG_PRINT(g_pe_debug_fd, 0, format, ##args)
// to_do_list : #define PE_TRACE(format, args...)		DBG_PRINTX(g_pe_debug_fd, 0, format, ##args)

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     PE_PreInit(void);
extern	int      PE_Init(void);
extern	void     PE_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
//extern int g_pe_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DRV_H_ */
