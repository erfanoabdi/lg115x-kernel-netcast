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
 * audio buffer functions.
 * Manage audio buffer.
 *
 * author     wonchang.shin (wonchang.shinu@lge.com)
 * version    1.0
 * date       2011.05.01
 *
 * @addtogroup lg1152_adec
 * @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "audio_drv.h"
#include "audio_buffer.h"

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
	Function Prototype Declaration
----------------------------------------------------------------------------------------*/
static void ARM_DCache_Invalidate(void* _addr, unsigned int _length, void* _adap);
static void ARM_DCache_Writeback(void* _addr, unsigned int _length, void* _adap);
static unsigned char* ARM_Mem_Translator(unsigned char* _addr, void* _adap);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/


ARM_PROCESSOR_ADAP gCPB_ArmWriterAdap[] =
{
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
};
ARM_PROCESSOR_ADAP gDPB_ArmWriterAdap[] =
{
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
		{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
};

ARM_PROCESSOR_ADAP gMIX_ArmWriterAdap[] =
{
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
		{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
};

ARM_PROCESSOR_ADAP gAENC_ArmReaderAdap[] =
{
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
};

ARM_PROCESSOR_ADAP gCAP_ArmReaderAdap[] =
{
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
};

ARM_PROCESSOR_ADAP gIEC_ArmWriterAdap[] =
{
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
	{
		ARM_DCache_Invalidate,
		ARM_DCache_Writeback,
		ARM_Mem_Translator
	},
};


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static void ARM_DCache_Invalidate(void* _addr, unsigned int _length, void* _adap)
{
	return;
}

static void ARM_DCache_Writeback(void* _addr, unsigned int _length, void* _adap)
{
	return;
}

static unsigned char* ARM_Mem_Translator(unsigned char* _addr, void* _adap)
{
	ARM_PROCESSOR_ADAP* adap;
	int offset;

	adap = (ARM_PROCESSOR_ADAP*) _adap;

	if( adap->memBase > _addr || adap->memBase + adap->memSize < _addr )
	{
	    AUD_ASSERT(0,
       	 (unsigned char*)NULL,
        	"exceed size(addr = 0x%X).\n", (unsigned int)_addr);
		return _addr;
	}

	offset = (unsigned char*)_addr - adap->memBase;

	return adap->dummyAddr + offset;/**/
}

