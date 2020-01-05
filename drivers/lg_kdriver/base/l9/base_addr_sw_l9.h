
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
 *  @author     sinchul.jung ( sinchul.jung@lge.com )
 *  @version    1.0
 *  @date       2011-10-21
 *  @note       Additional information.
 */

#ifndef	_BASE_ADDRESS_SWITCH_CFG_H_
#define	_BASE_ADDRESS_SWITCH_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Some default values
----------------------------------------------------------------------------------------*/

/*
 * Address switch module base number
 */
#define	ADDR_SW_CFG_CPU			0
#define	ADDR_SW_CFG_GPU			1
#define	ADDR_SW_CFG_GFX			2
#define	ADDR_SW_CFG_TE_SDEC		3
#define	ADDR_SW_CFG_TE_DVR		4
#define	ADDR_SW_CFG_VENC		5
#define	ADDR_SW_CFG_ICOD		6
#define	ADDR_SW_CFG_AUD0		7
#define	ADDR_SW_CFG_AUD1		8
#define	ADDR_SW_CFG_VDEC0		9
#define	ADDR_SW_CFG_VDEC1		10
#define	ADDR_SW_CFG_VDEC_MCU	11
#define	ADDR_SW_CFG_DE_A		12
#define	ADDR_SW_CFG_DE_B		13
#define	ADDR_SW_CFG_DE_C		14
#define	ADDR_SW_CFG_DE_D		15
#define	ADDR_SW_CFG_DE_E		16
#define	ADDR_SW_CFG_DE			17

#define	ADDR_SW_CFG_MAX			17
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *  Memory address swicth header for L9
 */

typedef struct
{
	UINT32	de_sav;
	UINT32	cpu_gpu;
	UINT32	cpu_shadow;
} LX_ADDR_SW_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern void BASE_L9_GetAddrSwCfg(int devId, LX_ADDR_SW_CFG_T *addr_sw);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

