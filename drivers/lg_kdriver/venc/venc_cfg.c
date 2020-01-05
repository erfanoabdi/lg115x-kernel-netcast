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
 *  main configuration file for venc device
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.05.19
 *  note		Additional information.
 *
 *  @addtogroup lg1152_venc
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "venc_cfg.h"
#include "venc_drv.h"

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
LX_VENC_MEM_CFG_S_T	*gpstVencMemConfig;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
LX_VENC_MEM_CFG_T	gMemCfgVenc[] =
{
	// For L9 Platform
	[0] = { 
		.pcMEMName = "VENC MEM",
		.uiMEMBase = 0x0,
		.uiMEMSize = 0x02300000,
	},

	// For H13 Platform ( LGEncoder or H1Encoder )
	[1] = {
		.pcMEMName = "VENC MEM",
		.uiMEMBase = 0x0,
		.uiMEMSize = 0x02900000,	// 41Mb
	},
};

LX_VENC_MEM_CFG_S_T gMemCfgVencInternal[VENC_MAX_MEM_CONFIG] =
{
	// For L9 Platform
	{
		.pcSRAMName 	= "VencSRAM",
		.uiSRAMBase 	= 0x0, //0x7C000000,//0x76C84000,
		.uiSRAMSize 	= 0x00080000,

		.pcSROMName 	= "VencSROM",
		.uiSROMBase 	= 0x0,//0x76D04000,
		.uiSROMSize 	= 0x00080000,

		.pcFrameBufName	= "VencFrameBuf",
		.uiFrameBufBase	= 0x0,//0x76D84000,
		.uiFrameBufSize	= 0x002D0000,

		.pcDPBName		= "VencDPB",
		.uiDPBBase		= 0x0,//0x77054000,
		.uiDPBSize		= 0x003F0000,

		.pcESBufName	= "VencESBuf",
		.uiESBufBase	= 0x0,//0x77444000,
		.uiESBufSize	= 0x0017F000,

		.pcAUIBufName	= "VencAUIBuf",
		.uiAUIBufBase	= 0x0,//0x775C3000,
		.uiAUIBufSize	= 0x00001000,

		.pcInBufName	= "VencBuf",
		.uiInBufBase	= 0x0,//0x775C4000,
		.uiInBufSize	= 0x00546000,

		.pcScalerName	= "VencScaler",
		.uiScalerBase	= 0x0,//0x77B0A000,
		.uiScalerSize	= 0x00261000,

		.pcAESBufName	= "AudioESBuf",
		.uiAESBufBase	= 0x0,//0x77720000,
		.uiAESBufSize	= 0x00060000,

		.pcAAUIBufName	= "AudioAUIBuf",
		.uiAAUIBufBase	= 0x0,//0x77800000,
		.uiAAUIBufSize	= 0x00001000,

		.pcTSBufName 	= "TSOutBuf",
		.uiTSBufBase 	= 0x0,//0x77B0A000,
		.uiTSBufSize 	= 0x260FB0,
	},

#if 1
	// For H13 A0/A1	( Total = 0x02504000, 37.02Mb )
	{
		.pcSRAMName 	= "VencSRAM",
		.uiSRAMBase 	= 0, //0x7C000000,
		.uiSRAMSize 	= 0x00080000,

		.pcSROMName 	= "VencSROM",
		.uiSROMBase 	= 0, //0x7C080000,
		.uiSROMSize 	= 0x00080000,

		.pcFrameBufName	= "VencFrameBuf",	// 2 frames (1D->2D converted data)
		.uiFrameBufBase	= 0, //0x7C100000,
		.uiFrameBufSize	= 0x00690000,

		.pcDPBName		= "VencDPB",		// 2 frames
		.uiDPBBase		= 0, //0x7C790000,
		.uiDPBSize		= 0x00830000,

		.pcESBufName	= "VencESBuf",
		.uiESBufBase	= 0, //0x7CF20000,
		.uiESBufSize	= 0x0017F000,

		.pcAUIBufName	= "VencAUIBuf",
		.uiAUIBufBase	= 0, //0x7CF9F000,
		.uiAUIBufSize	= 0x00001000,

		.pcInBufName	= "VencBuf",		// for DE Frame buffer (2 Frames)
		.uiInBufBase	= 0, //0x7CFA0000,
		.uiInBufSize	= 0x00CC0000,

   		// Not use in H13
   		// 2012/06/14 TEST for Thumbnail.
		.pcScalerName	= "VencScaler",
		.uiScalerBase	= 0x0,
		.uiScalerSize	= 0x00440000,		// 2048x1088x2 (4:2:2)

		.pcAESBufName	= "AudioESBuf",
		.uiAESBufBase	= 0, //0x7D820000,
		.uiAESBufSize	= 0x00060000,

		.pcAAUIBufName	= "AudioAUIBuf",
		.uiAAUIBufBase	= 0, //0x7D880000,
		.uiAAUIBufSize	= 0x00001000,

		.pcTSBufName 	= "TSOutBuf",
		.uiTSBufBase 	= 0, //0x77B0A000,
		.uiTSBufSize 	= 0x263000, //0x263000 (13,312*188)
	},

	// For H13B0 (H1Encode) (Total = 0x0292E000, 41Mb)
	{
		.pcDPBName		= "VencDPB",		// Output buffer for h1encoder
		.uiDPBBase		= 0,
		.uiDPBSize		= 0x00800000,

		.pcESBufName	= "VencESBuf",		// Output buffer for User (4MB) 
		.uiESBufBase	= 0,
		.uiESBufSize	= 0x003FE000,		

		.pcAUIBufName	= "VencAUIBuf",
		.uiAUIBufBase	= 0,
		.uiAUIBufSize	= 0x00002000,		// 16bytes AUI * 512

		.pcInBufName	= "VencBuf",		// for DE Frame buffer (FHD 3 Frames)
		.uiInBufBase	= 0,
		.uiInBufSize	= 0x00CC0000,

		// Not use in H13
		// 2012/06/14 TEST for Thumbnail.
		.pcScalerName	= "VencScaler",
		.uiScalerBase	= 0x0,
		.uiScalerSize	= 0x00440000,		// 2048x1088x2 (4:2:2)

		.pcH1EncBufName = "H1Encoder",		// for H1Encoder SW/HW Shared Memory
		.uiH1EncBufBase = 0,
		.uiH1EncBufSize = 0x00C00000,		// 12MB
	},

#else
	// FOR H13A1 and H13B0 (LGENC+H1ENCODER)
	{
#ifdef VENC_USE_LGENC
		.pcSRAMName 	= "VencSRAM",
		.uiSRAMBase 	= 0, //0x7C000000,
		.uiSRAMSize 	= 0x00080000,
	
		.pcSROMName 	= "VencSROM",
		.uiSROMBase 	= 0, //0x7C080000,
		.uiSROMSize 	= 0x00080000,
	
		.pcFrameBufName = "VencFrameBuf",	// 2 frames (1D->2D converted data)
		.uiFrameBufBase = 0,
		.uiFrameBufSize = 0x00690000,
#endif
		.pcDPBName		= "VencDPB",		// Output buffer for encoder hw
		.uiDPBBase		= 0, //0x7C790000,
		.uiDPBSize		= 0x00830000,
	
		.pcESBufName	= "VencESBuf",		// Output buffer for User
		.uiESBufBase	= 0,
		.uiESBufSize	= 0x003FD000,
	
		.pcAUIBufName	= "VencAUIBuf",
		.uiAUIBufBase	= 0,
		.uiAUIBufSize	= 0x00001000,
	
		.pcInBufName	= "VencBuf",		// for DE Frame buffer (3 Frames)
		.uiInBufBase	= 0, //0x7CFA0000,
		.uiInBufSize	= 0x00CC0000,
	
		.pcScalerName	= "VencScaler",
		.uiScalerBase	= 0x0,
		.uiScalerSize	= 0x00440000,		// 2048x1088x2 (4:2:2)

#ifdef 	VENC_USE_LGENC
		.pcAESBufName	= "AudioESBuf",
		.uiAESBufBase	= 0,
		.uiAESBufSize	= 0x0, //0x00060000,
	
		.pcAAUIBufName	= "AudioAUIBuf",
		.uiAAUIBufBase	= 0, 
		.uiAAUIBufSize	= 0x0, //0x00001000,
	
		.pcTSBufName	= "TSOutBuf",
		.uiTSBufBase	= 0,
		.uiTSBufSize	= 0x00263000, // (13,312*188)
#endif

#ifdef VENC_USE_H1ENCODE		
		.pcH1EncBufName = "H1Encoder",		// for H1Encoder SW/HW Shared Memory
		.uiH1EncBufBase = 0,
		.uiH1EncBufSize = 0x00C00000,		// 12MB
#endif

	},
#endif

};

/*========================================================================================
	Implementation Group
========================================================================================*/
static int _VENC_CFG_InternalMmoryMap( LX_VENC_MEM_CFG_T *pstMemCFG, LX_VENC_MEM_CFG_S_T	*pstVencInternalMemCFG )
{

	if ( pstMemCFG == NULL )
	{
		return RET_ERROR;
	}
	else
	{
		UINT32	StartAddr = 0;
		UINT32	EndAddr = 0;
		UINT32	TotalSize = 0, AllocatedSize = 0;
		
		LX_MEMCFG_T*	pM = (LX_MEMCFG_T*)pstVencInternalMemCFG;
		int 			nM = sizeof(*pstVencInternalMemCFG)/sizeof(LX_MEMCFG_T);

		StartAddr =  pstMemCFG->uiMEMBase;
		EndAddr = pstMemCFG->uiMEMBase;
		AllocatedSize = pstMemCFG->uiMEMSize;

		for ( ; nM > 0; nM--, pM++)
		{
#if 0
			/* if base is NULL, try to set address automatically and forward EndAddr */
			if ( 0x0 == pM->base )
	{
				//pM->base = LX_CALC_ALIGNED_VALUE(EndAddr,  DEVMEM_ALIGN_VALUE);
				//EndAddr += LX_CALC_ALIGNED_VALUE(pM->size, DEVMEM_ALIGN_VALUE);

				pM->base = EndAddr;
				EndAddr += pM->size;
			}
			/* if base valid, keep the address and just forward EndAddr. not that EndAddr may jump to the long distance */
			else
			{
				//EndAddr = pM->base + pM->size;
				//EndAddr = LX_CALC_ALIGNED_VALUE(EndAddr, DEVMEM_ALIGN_VALUE );
				EndAddr = pM->base + pM->size;
				EndAddr = EndAddr;
			}
#else
			pM->base = EndAddr;
			EndAddr += pM->size;
#endif

			VENC_DEBUG("[MEM_CFG] %12s: 0x%08x ~ 0x%08x [0x%08x]\n",
				pM->name, pM->base, pM->base + pM->size, pM->size);
		}

		TotalSize = EndAddr - StartAddr;

		VENC_DEBUG("[MEM_CFG] -----------------------------------------------------------\n");
		VENC_DEBUG("[MEM_CFG] %12s: 0x%08x ~ 0x%08x [0x%08x]\n",
			"Total", StartAddr, EndAddr, TotalSize);

		if ( TotalSize > AllocatedSize )
		{
			VENC_ERROR("Not enough allocated memory. (Allocated: 0x%08x, Required: 0x%08x)\n",
				AllocatedSize, TotalSize);

			return RET_ERROR;
		}
	}

	return RET_OK;
}

void VENC_CFG_MemoryMap ( void )
{
#if 0
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0) )
	{
		// H13
		gpstVencMemConfig = &gMemCfgVenc[1];
	}
	else //if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		// L9
		gpstVencMemConfig = &gMemCfgVenc[0];
	}
#else
	LX_VENC_MEM_CFG_T *pstMemCFG;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, B0) )
	{
		// H13B0
		pstMemCFG = &gMemCfgVenc[1];
		gpstVencMemConfig = &gMemCfgVencInternal[2];
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(H13, A0) )
	{
		// H13
		pstMemCFG = &gMemCfgVenc[1];
		gpstVencMemConfig = &gMemCfgVencInternal[1];
	}
	else //if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		// L9
		pstMemCFG = &gMemCfgVenc[0];
		gpstVencMemConfig = &gMemCfgVencInternal[0];		
	}

	_VENC_CFG_InternalMmoryMap( pstMemCFG, gpstVencMemConfig );
#endif
}


/** @} */

