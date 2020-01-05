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
 *  BE reg header file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.06
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _BE_REG_H_
#define _BE_REG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define REG_WD( addr, value)	( *( volatile UINT32 * )( addr )) = ( UINT32 )( value)
#define REG_RD( addr )			( *( volatile UINT32 * )( addr ))
#define GET_BITS(val,nd,wd)		(((val)>>(nd))&(0xFFFFFFFF>>(32-(wd))))
#define GET_PVAL(val,nd,wd)		(GET_BITS(val,nd,wd)<<(nd))


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int BE_REG_Init(void);
int BE_REG_Free(void);
int BE_REG_SwReset(void);
int BE_REG_Uart0_Switch(BOOLEAN isForMcu);

int BE_REG_RegAccess(UINT32 arg);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _BE_REG_H_ */

/** @} */





