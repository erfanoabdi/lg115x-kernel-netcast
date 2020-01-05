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
 *  application interface header for sys device
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2010.12.13
 *
 *  @addtogroup lg1150_sys
 *	@{
 */

#ifndef	_SYS_KAPI_H_
#define	_SYS_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	SYS_IOC_MAGIC		'a'
/**
@name SYS IOCTL List
ioctl list for sys device.

@{
@def SYS_IO_RESET
Reset sys module.
When sys device receives above IOCTL, then reset itself.

@def SYS_IOR_CHIP_REV_INFO
Reads chip revision information.
Just get chiop revision information. To support automatic changing behavior of device driver or middleware by this ioctl.

@def SYS_IOW_WRITE_UINT32
write 32bit value to sys module.
detailed...[minimum two lines of comment required. one line of comment does not generated automatically]

@def SYS_IOW_WRITE_STRUCT
control complex parameter to sys module.
control codec_type, speed, and additional parameter.
no need to use "see also", exact struct name shall be linked automatically.

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define	SYS_IO_RESET				_IO(SYS_IOC_MAGIC,  0 )
#define SYS_IOR_CHIP_REV_INFO		_IOR(SYS_IOC_MAGIC, 1, CHIP_REV_INFO_T )

#define SYS_IOW_WRITE_MEM			_IOW(SYS_IOC_MAGIC, 2, LX_SYS_MEM_T )
#define SYS_IORW_READ_MEM			_IOWR(SYS_IOC_MAGIC, 3, LX_SYS_MEM_T )

#define SYS_IOW_WRITE_MEM_ARRAY		_IOW(SYS_IOC_MAGIC, 4, LX_SYS_MEM_ARRAY_T )
#define SYS_IORW_READ_MEM_ARRAY		_IOWR(SYS_IOC_MAGIC, 5, LX_SYS_MEM_ARRAY_T )




#define SYS_IOC_MAXNR				10
/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * sys ioctl parameter.
 * useful when complex parameter should be passed to sys kernel driver.
 * @see SYS_IOW_WRITE_STRUCT
 */
typedef struct
{
	UINT32	addr;
	UINT32	value;
}	LX_SYS_MEM_T;

typedef struct
{
	UINT32	addr;
	UINT32	size;
	void	*data;
}	LX_SYS_MEM_ARRAY_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _SYS_DRV_H_ */

/** @} */
