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
 *  main driver implementation for sys device.
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2010.12.13
 *  note		Additional information.
 *
 *  @addtogroup lg1150_sys
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
#include <asm/io.h>

#include "os_util.h"
#include "sys_io.h"
#include "sys_drv.h"


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
	global Functions
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


int SYS_IO_ReadMemArray(UINT32 addr, UINT32 size, void *data)
{
	UINT32 *io_addr;
	io_addr = (UINT32*)ioremap_nocache(addr, size);
	if(io_addr != NULL)
	{
		memcpy((void*)addr, io_addr, size);
		iounmap(io_addr);
		return 0;
	}
	return -1;
}

int SYS_IO_WriteMemArray(UINT32 addr, UINT32 size, const void *data)
{
	UINT32 *io_addr;
	io_addr = (UINT32*)ioremap_nocache(addr, size);
	if(io_addr != NULL)
	{
		memcpy(io_addr, (void*)addr, size);
		iounmap(io_addr);
		return 0;
	}
	return -1;
}


int SYS_IO_ReadRegArray(UINT32 addr, UINT32 size, void *data)
{
	UINT32 *io_addr, *aio_addr;
	int rc = 0;

	io_addr = (UINT32*)ioremap_nocache(addr, size);
	if(io_addr != NULL)
	{
		int i;
		UINT32 temp;
		UINT32 remainder;
		UINT8 *v = (UINT8*)data;

		do {
			aio_addr = (UINT32*)((UINT32)io_addr & ~0x03);
			if(aio_addr != io_addr)	/* Address is not aligned to 4 bytes */
			{
				int ulen;
				UINT8 *s = (UINT8*)&temp;
				
				remainder = (UINT32)io_addr & 0x03;				
				temp = SYS_READ32(aio_addr);
				s += remainder;				
				ulen = min(size, 4-remainder);
				for(i=0; i<ulen; i++)
					*v++ = s[i];

				aio_addr++;
				size -= ulen;
				if(size == 0) break;
			}

			remainder = size%4;
			if((UINT32)v&0x03)	/* Data is not aligned to 4 bytes */
			{
				UINT8 *s = (UINT8*)&temp;
				for(i=0; i<size/4; i++)
				{
					temp = SYS_READ32(aio_addr);
					*v++ = s[0];
					*v++ = s[1];
					*v++ = s[2];
					*v++ = s[3];
					aio_addr++;
				}
			}
			else
			{
				for(i=0; i<size/4; i++)
				{
					*((volatile UINT32*)v) = SYS_READ32(aio_addr);
					v += 4;
					aio_addr++;
				}
			}

			if(remainder)
			{
				UINT8 *s = (UINT8*)&temp;
				temp = SYS_READ32(aio_addr);
				for(i=0; i<remainder; i++)
					*v++ = s[i];
			}
		} while(0);

		iounmap(io_addr);
	}
	else
	{
		SYS_ERROR("Can't ioremap !!!\n");
		rc = -1;
	}

	return rc;
}

int SYS_IO_WriteRegArray(UINT32 addr, UINT32 size, const void *data)
{
	UINT32 *io_addr, *aio_addr;

	io_addr = (UINT32*)ioremap_nocache(addr, size);
	if(io_addr != NULL)
	{
		int i;
		UINT32 temp;
		UINT32 remainder;
		UINT8 *v = (UINT8*)data;

		do {
			aio_addr = (UINT32*)((UINT32)io_addr & ~0x03);
			if(aio_addr != io_addr)	/* Address is not aligned to 4 bytes */
			{
				int ulen;
				UINT8 *s = (UINT8*)&temp;
				
				remainder = (UINT32)io_addr & 0x03;				
				temp = SYS_READ32(aio_addr);				
				s += remainder;
				ulen = min(size, 4-remainder);
				for(i=0; i<ulen; i++)
					s[i] = *v++;
				SYS_WRITE32(aio_addr, temp);

				aio_addr++;
				size -= ulen;
				if(size == 0) break;
			}

			remainder = size%4;
			if((UINT32)v&0x03)	/* Data is not aligned to 4 bytes */
			{
				//UINT32 pv, nv;	// will modify next time. read one time
				UINT8 *s = (UINT8*)&temp;
				for(i=0; i<size/4; i++)
				{
					s[0] = *v++;
					s[1] = *v++;
					s[2] = *v++;
					s[3] = *v++;					
					SYS_WRITE32(aio_addr, temp);
					aio_addr++;
				}
			}
			else
			{
				for(i=0; i<size/4; i++)
				{
					SYS_WRITE32(aio_addr, *((volatile UINT32*)v));
					v += 4;
					aio_addr++;
				}
			}

			if(remainder)
			{
				UINT8 *s = (UINT8*)&temp;
				temp = SYS_READ32(aio_addr);
				for(i=0; i<remainder; i++)
					s[i] = *v++;
				SYS_WRITE32(aio_addr, temp);
			}
		} while(0);

		iounmap(io_addr);
	}

	return 0;

}



/** @} */

