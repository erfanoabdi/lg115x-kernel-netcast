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
 *  main configuration file for de device
 *	de device will teach you how to make device driver with new platform.
 *
 *  author		dongho7.park (dongho7.park@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_de
 *	@{
 */

#ifndef	_DE_CFG_H_
#define	_DE_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "de_cfg_def.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	DE_MODULE			"de"
#define DE_MAX_DEVICE		1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	char*	fw_name;	///< name of firmware
	UINT32	fw_base;	///< base address of firmware
	UINT32	fw_size;	///< size of firmware
} LX_DE_CH_MEM_T;

typedef struct
{
	LX_DE_CH_MEM_T	fw[3];
	char*	frame_name;  ///< name of frame memory
	UINT32	frame_base;  ///< base of frame memory
	UINT32	frame_size;  ///< size of frame memory
} LX_DE_MEM_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern LX_DE_MEM_CFG_T *gpDeMem, gMemCfgDe[];
extern LX_DE_CH_MEM_T gMemCfgDePreW[];
extern LX_DE_CH_MEM_T gMemCfgDeGrap[];
extern LX_DE_CH_MEM_T gMemCfgDeFW[];

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_CFG_H_ */

/** @} */

