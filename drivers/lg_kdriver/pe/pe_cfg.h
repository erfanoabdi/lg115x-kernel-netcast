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


/** @file pe_cfg.h
 *
 *  configuration header for pe device. ( used only within kdriver )
 *	
 *	@author		
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_CFG_H_
#define	_PE_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_H14_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_H14
#endif
#ifdef INCLUDE_H13_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_H13
#endif
#ifdef INCLUDE_L9_CHIP_KDRV
#define USE_PE_KDRV_CODES_FOR_L9
#endif

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	PE_MODULE			"pe"
#define PE_MAX_DEVICE		1

/* kdrv version bit */
#define PE_KDRV_VER_BIT_NONE		0x00000000
#define PE_KDRV_VER_BIT_L9AX		0x00000001
#define PE_KDRV_VER_BIT_L9BX		0x00000002
#define PE_KDRV_VER_BIT_H13AX		0x00000004
#define PE_KDRV_VER_BIT_H13BX		0x00000008
#define PE_KDRV_VER_BIT_H14AX		0x00000010
#define PE_KDRV_VER_BIT_H14BX		0x00000020
#define PE_KDRV_VER_BIT_L9			(PE_KDRV_VER_BIT_L9AX|PE_KDRV_VER_BIT_L9BX)
#define PE_KDRV_VER_BIT_H13			(PE_KDRV_VER_BIT_H13AX|PE_KDRV_VER_BIT_H13BX)
#define PE_KDRV_VER_BIT_H14			(PE_KDRV_VER_BIT_H14AX|PE_KDRV_VER_BIT_H14BX)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* kdrv version define */
#define PE_KDRV_VER_NONE		PE_KDRV_VER_BIT_NONE
#define PE_KDRV_VER_L9AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_L9AX)
#define PE_KDRV_VER_L9BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_L9BX)
#define PE_KDRV_VER_L9			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_L9)
#define PE_KDRV_VER_H13AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_H13AX)
#define PE_KDRV_VER_H13BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_H13BX)
#define PE_KDRV_VER_H13			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_H13)
#define PE_KDRV_VER_H14AX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_H14AX)
#define PE_KDRV_VER_H14BX		(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_H14BX)
#define PE_KDRV_VER_H14			(g_pe_kdrv_ver_mask&PE_KDRV_VER_BIT_H14)

#define PE_CHIP_VER				lx_chip_rev( )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern unsigned int g_pe_kdrv_ver_mask;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CFG_H_ */
