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


/** @file	audio_kdrv_master.c
 *
 *  main driver implementation for  audio master device.
 *  audio master device will teach you how to make device driver with new platform.
 *
 *  author	wonchang.shin (wonchang.shin@lge.com)
 *  version	0.1
 *  date		2012.04.25
 *  note		Additional information.
 *
 *  @addtogroup lg1150_audio
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
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>    /**< For isr */
#include <linux/irq.h>			/**< For isr */
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <linux/rmap.h>
#include <linux/kthread.h>
#include <asm/io.h>			/**< For ioremap_nocache */
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/version.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>


#endif

#include "os_util.h"
#include "base_device.h"

#include "debug_util.h"
#include "audio_cfg.h"
#include "audio_drv.h"
#include "audio_reg.h"

#include "audio_buffer.h"
#include "imc/cmd/module_cmd_bypass.h"
#include "common/adec_config.h"

#include "audio_drv_master.h"
#include "audio_drv_decoder.h"
#include "audio_drv_manager.h"
#include "audio_imc_func.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define NOT_CLASSIFIED		0
#define LAST_MOD			1
#define MULTI_MOD			2
#define RM_MODULE_NUM		5

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

//need to sync with device num ,extra manager module

UINT8 *  allocMod_Str [ADEC_MODULE_MOD_MAX+1] =
{
		"MOD_NONE",

#ifdef ADEC_MODULE_DEF
#undef ADEC_MODULE_DEF
#endif
#ifdef __BUF_END
#undef __BUF_END
#endif

#define __BUF_END(...)	ADEC_BUF_NOT_DEF,ADEC_BUF_NOT_DEF,ADEC_BUF_NOT_DEF,ADEC_BUF_NOT_DEF
#define __GET_MOD_NAME(__MODULE, __MODULE_NAME, __MODULE_TYPE, __LOCATION, __NUM_IN, __NUM_OUT, __PORT_0_TYPE, __PORT_1_TYPE, __PORT_2_TYPE, __PORT_3_TYPE, ...) \
	__MODULE_NAME,
#define ADEC_MODULE_DEF(__MODULE, __MODULE_NAME, __MODULE_TYPE, __LOCATION, __NUM_IN, __NUM_OUT, ...)\
	__GET_MOD_NAME(__MODULE, __MODULE_NAME, __MODULE_TYPE, __LOCATION, __NUM_IN, __NUM_OUT, __VA_ARGS__)
#include "module/adec_module_def.h"
#undef ADEC_MODULE_DEF
#undef __GET_MOD_NAME
#undef __BUF_END
	"MPB_0",
	"MPB_1",
	"MPB_2",
	"MPB_3",
	"MPB_4",
	"MPB_5",
	"MPB_6",
	"MPB_7",
	"CPB_0",
	"CPB_1",
	"CPB_2",
	"CPB_3",
	"DPB_0",
	"DPB_1",
	"DPB_2",
	"DPB_3",
	"IEC_0",
	"IEC_1",
	"CAPB_0",
	"CAPB_1",
	"CAPB_2",

	"MOD_MAX",

};

//need to sync with device num ,extra manager module
UINT8 *  allocDev_Str [AUD_DEV_MAX+1] = // device node(D) and module(M)
{
    "DEV_NONE",		//56
    "DEV_DEC0",		//56
    "DEV_DEC1",
    "DEV_ENC0",
    "DEV_ENC1",
    "DEV_CAP0",
    "DEV_CAP1",
    "DEV_CAP2",
    "DEV_REN0",
    "DEV_REN1",
    "DEV_REN2",
    "DEV_REN3",
    "DEV_REN4",
    "DEV_REN5",
    "DEV_REN6",
    "DEV_REN7",
    "DEV_REN8",
    "DEV_REN9",
    "DEV_RE10",
    "DEV_RE11",
    "DEV_MAS0",
	"DEV_MAX",
};


CHAR* modTypeStr[LX_AUD_MOD_TYPE_MAX+1] ={NULL,};


//need to sync with device num ,extra manager module
UINT8 * devTypeStr[LX_AUD_DEV_TYPE_MAX+1] =  // device node(D) and module(M)
{
	"DEV_T_NONE",
	"DEV_DEC",//0
	"DEV_ENC",//1
	"DEV_CAP",//2
	"DEV_REN",//3
	"DEV_MAS",//4
	"DEV_T_MAX",
};

UINT8 *  conn_Str[CONN_TYPE_MAX] = // device node(D) and module(M)
{
	"    ",
	"  C ",
	"  A ",
	" CA>",// cpb alloc  assing for left module
	" <CA",// cpb alloc  assing for right module
	" DA>",// dpb alloc  assing for left module
	" <DA",// dpb alloc  assing for right module
	" MA>",// mpb alloc  assing for left module
	" <MA",// mpb alloc  assing for right module
	" IA>",// mpb alloc  assing for left module
	" <IA",// mpb alloc  assing for right module
	" PA>",// cap alloc  assing for left module
	" <PA",// cap alloc  assing for right module

	"xC  ",// disconnect
	"xCA>",// cpb dealloc  assing for left module
	"x<CA",// cpb dealloc  assing for right module
	"xDA>",// dpb dealloc  assing for left module
	"x<DA",// dpb dealloc  assing for right module
	"xMA>",// mpb dealloc  assing for left module
	"x<MA",// mpb dealloc  assing for right module
	"xIA>",// mpb dealloc  assing for left module
	"x<IA",// mpb dealloc  assing for right module
	"xPA>",// cap dealloc  assing for left module
	"x<PA",// cap dealloc  assing for right module
};



//need to sync with device num ,extra manager module
UINT32 devAvailableNum[LX_AUD_DEV_TYPE_MAX+1]=
{
	DUMMY_NUM,
	DEV_DEC_NUM,
	DEV_ENC_NUM,
	DEV_CAP_NUM,
	DEV_REN_NUM,
	DEV_MAS_NUM,
};


UINT8 lastModNum = 0;
UINT8 lastModName[20][20];

AUD_MOD_NUM_T stFwMod[ADEC_MODULE_MOD_MAX+1]=
{
	{
		DUMMY_NUM,
		"MOD_NONE",
	},
#ifdef ADEC_MODULE_DEF
#undef ADEC_MODULE_DEF
#endif
#ifdef __BUF_END
#undef __BUF_END
#endif

#define __BUF_END(...)	ADEC_BUF_NOT_DEF,ADEC_BUF_NOT_DEF,ADEC_BUF_NOT_DEF,ADEC_BUF_NOT_DEF
#define __GET_MOD_NUM_NAME(__MODULE, __MODULE_NAME, __MODULE_TYPE, __LOCATION, __NUM_IN, __NUM_OUT, __PORT_0_TYPE, __PORT_1_TYPE, __PORT_2_TYPE, __PORT_3_TYPE, ...) \
	{\
		__MODULE,\
		__MODULE_NAME,\
	},
#define ADEC_MODULE_DEF(__MODULE, __MODULE_NAME, __MODULE_TYPE, __LOCATION, __NUM_IN, __NUM_OUT, ...)\
	__GET_MOD_NUM_NAME(__MODULE, __MODULE_NAME, __MODULE_TYPE, __LOCATION, __NUM_IN, __NUM_OUT, __VA_ARGS__)
#include "module/adec_module_def.h"
#undef ADEC_MODULE_DEF
#undef __GET_MOD_NUM_NAME
#undef __BUF_END
};

UINT32 fwModTypeNum = 0;

//AUD_MOD_NUM_T stFwRmModType[ADEC_MODULE_MOD_MAX+1];
AUD_MOD_NUM_T stFwRmModType[LX_AUD_MOD_TYPE_MAX+1];

//need to sync with device num ,extra manager module
AUD_MOD_NUM_T stRmMod[RM_MODULE_NUM]=
{
	{MPB_NUM	,"MPB", },
	{CPB_NUM	,"CPB", },
	{DPB_NUM	,"DPB", },
	{IEC_NUM	,"IECB", },
	{CAPB_NUM	,"CAPB", },
};

LX_AUD_MOD_INFO_T ModInfo;
LX_AUD_DEV_INFO_T DevInfo;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * Alloc Device (Decorder,Render,Master)
 *
 * @param 	pOpenInfo 	[in] void * of device info
 * @return 	if succeeded -alloc device num , else - AUD_NO_DEV.
 * @see		.
 */

int  AUDIO_AllocDev ( void  * pOpenInfo)
{
	LX_AUD_DEV_TYPE_T devType;
	LX_AUD_ALLOC_FREE_INFO_T * allocDEV;

	UINT32	devToAlloc = AUD_NO_DEV;
	UINT32	searchStart,searchEnd;
	UINT32	availbleNum,allocBase,allocCnt;

	devType = (( LX_AUD_ALLOC_FREE_INFO_T *) pOpenInfo)->devType;

	allocCnt 		= DevInfo.allocCnt[devType];
	availbleNum 	= DevInfo.availableNum[devType];
	allocBase 		= DevInfo.allocBase[devType];

	AUD_KDRV_RMD("AUDIO_AllocDev devType[%s] [availbleNum:%d][allocCnt:%d][allocBase:%d]\n",devTypeStr[devType], availbleNum, allocCnt , allocBase);

	if( allocCnt < availbleNum )
	{
		searchStart 	= allocBase ;
		searchEnd 	= searchStart + availbleNum ;

		for( devToAlloc = searchStart ; devToAlloc < searchEnd ; devToAlloc++ )
		{
			//if dev is available
			if(DevInfo.list[devToAlloc].used == 0)
			{
				allocDEV = &DevInfo.list[devToAlloc];
				allocDEV->allocDev	= devToAlloc;
				allocDEV->used			= 1;
				allocDEV->devType 		= devType;
				allocDEV->allocStr 	= (UINT8 *)allocDev_Str[devToAlloc];
				allocDEV->hasIECBuff= 	0;
				allocDEV->hasIECLIP= 	0;
				allocDEV->hasEPB= 	0;
				DevInfo.allocCnt[devType] ++;
				break;
			}
		}
		AUD_KDRV_RMD(" searchStart[%d] searchEnd[%d] Alloc Dev:%s[%d] \n",searchStart,searchEnd,allocDev_Str[devToAlloc],devToAlloc);
		return devToAlloc;
	}
	// no dev case
	else
	{
		return AUD_NO_DEV;
	}
}


/**
 * Free Device (Decorder,Render,Master)
 *
 * @param 	pCloseInfo 	[in] void * of device info
 * @return 	if succeeded -alloc device num , else - AUD_NO_DEV.
 * @see		.
 */

int  AUDIO_FreeDev ( void  * pCloseInfo)
{
	LX_AUD_DEV_TYPE_T devType;
	LX_AUD_ALLOC_DEV_T devToFree = AUD_NO_DEV;
	LX_AUD_ALLOC_FREE_INFO_T * freeDEV;
	LX_AUD_MOD_T * pOwnMods;

	SINT32	retVal = RET_OK;
	UINT32 	allocModNum, i;

	devType = 	(( LX_AUD_ALLOC_FREE_INFO_T *) pCloseInfo)->devType;
	devToFree =   (( LX_AUD_ALLOC_FREE_INFO_T *) pCloseInfo)->allocDev;

	AUD_KDRV_RMD("AUDIO_FreeDev devType[%s] [devType %d devToFree%d]\n",devTypeStr[devType],devType ,devToFree);

	if( DevInfo.allocCnt[devType] > 0 )
	{
		//get alloc module info in given device node
		AUDIO_GetAllocInfo(devToFree, &allocModNum , &pOwnMods);

		for(i = 0; i < allocModNum; i++)
		{
			retVal = AUDIO_FreeModule ( pOwnMods[i].mod, devToFree);

			if( retVal != RET_OK)
			{
				AUD_KDRV_RM("%s:[%s] AUDIO_FreeModule ERROR!!!\n",__FUNCTION__,allocMod_Str[pOwnMods[i].mod] );
				break;
			}
			else
			{
				AUD_KDRV_RM("%s AUDIO_FreeModule OK[%s]!!!\n",__FUNCTION__,allocMod_Str[pOwnMods[i].mod]);
			}
		}

		freeDEV = &DevInfo.list[devToFree];
		freeDEV->used		 	= 0;
		freeDEV->devType  		= LX_AUD_DEV_TYPE_MAX;
		freeDEV->allocDev 	= AUD_NO_DEV;
		freeDEV->allocStr 	= NULL;
		freeDEV->in[0]			= NULL;
		freeDEV->out[0]			= NULL;
		freeDEV->connectStart = CONN_NONE;
		freeDEV->isFullyConnected = 0;
		//AUD_KDRV_RM("==== free \n");
		freeDEV->hasIECBuff= 	0;
		freeDEV->hasIECLIP= 	0;
		freeDEV->hasEPB= 	0;
		freeDEV->headOfDev			= NULL;
		freeDEV->tailOfDev		= NULL;
		freeDEV->connectLength	=	0;

		for( i = 0 ; i  < MAX_OWN_MOUDLE ; i++)
		{
			freeDEV->own[i].mod = ADEC_MODULE_NO_MOD;
			freeDEV->own[i].modType = LX_AUD_MOD_TYPE_NONE;
			freeDEV->own[i].modStr  = NULL;
		}
		freeDEV->ownNum		= 0;
		DevInfo.allocCnt[devType] --;

		return devToFree;
	}
	else
	{
		return AUD_NO_DEV;
	}
}


/**
 * Alloc Module ( Module in Firmware, refer to adec_module_def.h )
 *
 * @param 	allocDev 	[in] device num(return of AUDIO_AllocDev ) to alloc module
 * @param 	moduleType 	[in] module type to alloc
 * @param 	wantModule 	[in] explicit module num or 0:normal malloc
 * @return 	if succeeded -alloc device num , else - ADEC_MODULE_NO_MOD.
 * @see
 */

int  AUDIO_AllocModule ( UINT32 allocDev , UINT32 moduleType , UINT32 wantModule)
{
	LX_AUD_MOD_TYPE_T modType;
	LX_AUD_ALLOC_FREE_INFO_T * allocMOD, *allocDEV;
	LX_AUD_MOD_T	*pOwnMods;

	UINT32	allocModNum;
	UINT32	ModToAlloc = ADEC_MODULE_NO_MOD;
	UINT32	searchStart,searchEnd;
	UINT32	availbleNum,allocBase,allocCnt;
	UINT32 	i, isExist= 0;


	if ( DevInfo.list[allocDev].ownNum >= MAX_OWN_MOUDLE )
	{
		AUD_KDRV_RM(" NO Module resource to alloc [%d] \n",__LINE__);
		return ADEC_MODULE_NO_MOD;
	}

	//check whether allocDev has a given moduleType
	isExist = 0;
	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for( i = 0 ; i  < allocModNum  ; i++)
	{
		//AUD_KDRV_RMD("[%d]modType[%s] modTypeToAlloc[%s] modTypeToAlloc[%d]\n",i,modTypeStr[pOwnMods[i].modType],modTypeStr[moduleType],moduleType);
		if (pOwnMods[i].modType == moduleType)
		{
			isExist=1;
			ModToAlloc = pOwnMods[i].mod;
			break;
		}
	}

	// if yes, return previous alloc module
	if(isExist == 1 && ( moduleType != LX_AUD_OUT_CTRL ) )
	{
		AUD_KDRV_RMD("Use Previous Alloc Module[%s]",allocMod_Str[ModToAlloc]);
		return ModToAlloc;
	}

	modType = moduleType;

	allocCnt 		= ModInfo.allocCnt[modType];
	availbleNum 	= ModInfo.availableNum[modType];
	allocBase 		= ModInfo.allocBase[modType];


	if (wantModule != 0)
	{
		ModToAlloc = wantModule;
		allocDEV =&DevInfo.list[allocDev];
		allocMOD =&ModInfo.list[ModToAlloc];

		if( allocCnt < availbleNum && allocDEV->ownNum < MAX_OWN_MOUDLE )
		{
			//if module is available
			if(ModInfo.list[ModToAlloc].used == 0)
			{
				for(	i = 0 ; i < MAX_OWN_MOUDLE; i++)
				{
				 	if (DevInfo.list[allocDev].own[i].mod == ADEC_MODULE_NO_MOD)
					{
						allocDEV =&DevInfo.list[allocDev];
						allocMOD =&ModInfo.list[ModToAlloc];

						allocDEV->own[i].mod = ModToAlloc ;
						allocDEV->own[i].modType= modType ;
						#if 0
						if (ModToAlloc != ADEC_MODULE_OUT_CTRL_1  &&  ModToAlloc != ADEC_MODULE_OUT_CTRL_2 &&
							ModToAlloc != ADEC_MODULE_OUT_CTRL_3  && ModToAlloc != ADEC_MODULE_OUT_SPDIF &&
							ModToAlloc != ADEC_MODULE_IEC_0

						)
						#endif
							allocDEV->ownNum++;

						if (allocDEV->ownNum == 1)		// check as FullyConnected  when dev has one module
						{
							allocDEV->headOfDev = allocMOD;
							allocDEV->tailOfDev = allocMOD;
							allocDEV->isFullyConnected = 1;
							//AUD_KDRV_RM("==== 7 \n");
						}
						else
						{
							#if 0
							if (ModToAlloc != ADEC_MODULE_OUT_CTRL_1  &&  ModToAlloc != ADEC_MODULE_OUT_CTRL_2 &&
								ModToAlloc != ADEC_MODULE_OUT_CTRL_3  && ModToAlloc != ADEC_MODULE_OUT_SPDIF &&
								ModToAlloc != ADEC_MODULE_IEC_0

							)
							#endif
							{
								if(allocDEV->isFullyConnected == 1 &&  moduleType != LX_AUD_IEC &&  moduleType != LX_AUD_RTS)
								{
									allocDEV->isFullyConnected	= 0;

									//AUD_KDRV_RM("====\n");
								}
							}
						}
						allocMOD->allocMod	= ModToAlloc;
						allocMOD->allocDev	= allocDev;
						allocMOD->used			= 1;
						allocMOD->status		= ALLOC;
						allocMOD->modType 		= modType;
						allocMOD->allocStr = (UINT8 *)allocMod_Str[ModToAlloc];

						ModInfo.allocCnt[modType] ++;
						//AUD_KDRV_RMD(" check loop ModToAlloc[%d] [%d] \n",ModToAlloc,__LINE__);
						break;
				 	}
				}
				return ModToAlloc;
			}
			else
			{
				return ADEC_MODULE_NO_MOD;
			}
		}
		else
		{
			return ADEC_MODULE_NO_MOD;
		}
	}

	AUD_KDRV_RMD("AUDIO_AllocModule modType[%9s] [availbleNum:%d][allocCnt:%d][allocBase:%d]\n",modTypeStr[modType], availbleNum, allocCnt , allocBase);

	searchStart 	= allocBase ;
	searchEnd 	= searchStart + availbleNum ;
	ModToAlloc = searchStart ;

	if( allocCnt < availbleNum )
	{
		for( ModToAlloc = searchStart ; ModToAlloc < searchEnd ; ModToAlloc++ )
		{
			//AUD_KDRV_RM("for 1[%d] \n",__LINE__);
			//if module is available
			if(ModInfo.list[ModToAlloc].used == 0)
			{
				for(	i = 0 ; i < MAX_OWN_MOUDLE; i++)
				{
					//AUD_KDRV_RM("for 2[%d] \n",__LINE__);
				 	if (DevInfo.list[allocDev].own[i].mod == ADEC_MODULE_NO_MOD)
					{
						//AUD_KDRV_RM("ModToAlloc[%d] [%d] \n",ModToAlloc,__LINE__);
						allocDEV =&DevInfo.list[allocDev];
						allocMOD =&ModInfo.list[ModToAlloc];

						allocDEV->own[i].mod = ModToAlloc ;
						allocDEV->own[i].modType= modType ;
						#if 0
						if (ModToAlloc != ADEC_MODULE_OUT_CTRL_1  &&  ModToAlloc != ADEC_MODULE_OUT_CTRL_2 &&
							ModToAlloc != ADEC_MODULE_OUT_CTRL_3  && ModToAlloc != ADEC_MODULE_OUT_SPDIF &&
							ModToAlloc != ADEC_MODULE_IEC_0
						)
						#endif
							allocDEV->ownNum++;

						if (allocDEV->ownNum == 1)		// check as FullyConnected  when dev has one module
						{
							allocDEV->headOfDev = allocMOD;
							allocDEV->tailOfDev = allocMOD;
							allocDEV->isFullyConnected = 1;
							//AUD_KDRV_RM("==== 1\n");
							//AUD_KDRV_RM("ModTo Alloc[%d] [%d] \n",ModToAlloc,__LINE__);
						}
						else
						{
							#if 0
							if (ModToAlloc != ADEC_MODULE_OUT_CTRL_1  &&  ModToAlloc != ADEC_MODULE_OUT_CTRL_2 &&
								ModToAlloc != ADEC_MODULE_OUT_CTRL_3  && ModToAlloc != ADEC_MODULE_OUT_SPDIF &&
								ModToAlloc != ADEC_MODULE_IEC_0
							)
							#endif
							{
								//AUD_KDRV_RM("ModToAlloc[%d] [%d] \n",ModToAlloc,__LINE__);
								if(allocDEV->isFullyConnected == 1 &&  moduleType != LX_AUD_IEC &&  moduleType != LX_AUD_RTS)
								{
									//AUD_KDRV_RM("==== 2\n");
									allocDEV->isFullyConnected	= 0;
								}
							}

						}
						allocMOD->allocMod	= ModToAlloc;
						allocMOD->allocDev	= allocDev;
						allocMOD->used			= 1;
						allocMOD->status		= ALLOC;
						allocMOD->modType 		= modType;
						allocMOD->allocStr = (UINT8 *)allocMod_Str[ModToAlloc];
						ModInfo.allocCnt[modType] ++;
						//AUD_KDRV_RM(" check loop ModToAlloc[%d] [%d] \n",ModToAlloc,__LINE__);
						break;
				 	}
				}
				break;
			}
			else
			{
				//AUD_KDRV_RM("else [%d] \n",__LINE__);
				//return ADEC_MODULE_NO_MOD;
			}
		}

		AUD_KDRV_RMD(" searchStart[%d] searchEnd[%d] Alloc Dev:%s[%d] \n",searchStart,searchEnd,allocMod_Str[ModToAlloc],ModToAlloc);
		return ModToAlloc;
	}
	else if (ModInfo.list[ModToAlloc].hasFakeMod== 1 && ModInfo.list[ModToAlloc].subUsed == 0)
	{
		for(	i = 0 ; i < MAX_OWN_MOUDLE; i++)
		{
		 	if (DevInfo.list[allocDev].own[i].mod == ADEC_MODULE_NO_MOD)
			{
				allocDEV =&DevInfo.list[allocDev];
				allocMOD =&ModInfo.list[ModToAlloc];

				allocDEV->own[i].mod = ModToAlloc ;
				allocDEV->own[i].modType= modType ;

				allocDEV->ownNum++;

				if (allocDEV->ownNum == 1)		// check as FullyConnected  when dev has one module
				{
					//allocDEV->headOfDev = allocMOD;
					//allocDEV->tailOfDev = allocMOD;
					allocDEV->isFullyConnected = 1;
				}
				else
				{
					{
						if(allocDEV->isFullyConnected == 1)
						{
							allocDEV->isFullyConnected	= 0;
						}
					}

				}
				allocMOD->allocSubDev	= allocDev;
				allocMOD->subUsed			= 1;

				break;
		 	}
		}

		AUD_KDRV_RMD(" searchStart[%d] searchEnd[%d] Alloc Dev:%s[%d] \n",searchStart,searchEnd,allocMod_Str[ModToAlloc],ModToAlloc);
		return ModToAlloc;
	}
	else
	{
		return ADEC_MODULE_NO_MOD;
	}
}


/**
 * Free Module ( Module in Firmware, refer to adec_module_def.h )
 *
 * @param 	allocMod	[in] free module num(return of AUDIO_AllocMod ) to free
 * @return 	if succeeded -freed device num , else - ADEC_MODULE_NO_MOD.
 * @see
 */

int  AUDIO_FreeModule ( UINT32 allocMod, UINT32 allocDev )
{

	LX_AUD_MOD_TYPE_T modType;
	LX_AUD_ALLOC_MOD_T modToFree 	= ADEC_MODULE_NO_MOD; //module to free
	LX_AUD_ALLOC_DEV_T belongto 	= ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_FREE_INFO_T * freeMOD;
	UINT32	i, k;

	modToFree 	=  allocMod;
	modType 	= ModInfo.list[modToFree].modType ;
	belongto	   	= (LX_AUD_ALLOC_DEV_T)allocDev;

	AUD_KDRV_RM("[%s] allocDev[%s]  allocsubDev[%s] own[%d]  \n",allocMod_Str[modToFree],allocDev_Str[ModInfo.list[modToFree].allocDev],allocDev_Str[ModInfo.list[modToFree].allocSubDev],DevInfo.list[belongto].ownNum  );
	AUD_KDRV_RM(" AUDIO_FreeModule[%s:%d]  modType[%s] allocCnt [%d] \n",allocMod_Str[modToFree],modToFree,modTypeStr[modType] ,ModInfo.allocCnt[modType] );
	if (DevInfo.list[belongto].ownNum == 0)
	{
		AUD_KDRV_RMD(" NO Module resource to free [%d]\n",__LINE__);
		return ADEC_MODULE_NO_MOD;
	}

	if( ModInfo.allocCnt[modType] > 0 )
	{
		// device node's module free;
		for(	i = 0 ; i < MAX_OWN_MOUDLE; i++)
		{
			AUD_KDRV_RMD(" own[%s] alloc[%s]  [%s] allocCnt [%d]\n",allocMod_Str[DevInfo.list[belongto].own[i].mod ],allocMod_Str[modToFree],modTypeStr[modType],ModInfo.allocCnt[modType] );
		 	if (DevInfo.list[belongto].own[i].mod == modToFree)
			{
				DevInfo.list[belongto].own[i].mod = ADEC_MODULE_NO_MOD ;
				#if 0
				if (modToFree != ADEC_MODULE_OUT_CTRL_1  &&  modToFree != ADEC_MODULE_OUT_CTRL_2 && modToFree != ADEC_MODULE_OUT_CTRL_3  && modToFree != ADEC_MODULE_OUT_SPDIF &&
					modToFree != ADEC_MODULE_IEC_0
				)
				#endif
				DevInfo.list[belongto].ownNum--;

				freeMOD =&ModInfo.list[modToFree];

				if( freeMOD->hasFakeMod == 0 || (freeMOD->hasFakeMod == 1 && freeMOD->subUsed == 0) )
				{
					freeMOD->connectStart		= 0;
					freeMOD->used		 		= 0;
					freeMOD->modType  			= LX_AUD_MOD_TYPE_NONE;
					freeMOD->allocMod 		= ADEC_MODULE_NO_MOD;
					freeMOD->allocDev 		= AUD_NO_DEV;
					freeMOD->allocStr 		= NULL;
					//freeMOD->multiSinkPortNum = HAS_NOT_MULTISINK_PORT;

					for(k=0; k< MAX_PORT; k++)
					{
						freeMOD->out[k] = NULL;
						freeMOD->in[k] 	= NULL;
						freeMOD->inOutMap[k].map.in= 	ADEC_MODULE_NO_MOD;
						freeMOD->inOutMap[k].map.out= 	ADEC_MODULE_NO_MOD;
						freeMOD->inPool		=	0xffffffff;
						freeMOD->outPool	=	0xffffffff;
					}

					freeMOD->connType = CONN_TYPE_NONE;
					ModInfo.allocCnt[modType] --;
					AUD_KDRV_RM("free 1\n");
				}
				else if(freeMOD->hasFakeMod == 1 && freeMOD->subUsed == 1)
				{

					if( freeMOD->allocDev == belongto)
					{
						freeMOD->allocDev		= freeMOD->allocSubDev;
						freeMOD->allocSubDev		= AUD_NO_DEV;
						AUD_KDRV_RM("allocDev1[%s]\n",allocDev_Str[freeMOD->allocDev	]);

					}
					else if ( freeMOD->allocSubDev == belongto)
					{
						freeMOD->allocSubDev		= AUD_NO_DEV;
						AUD_KDRV_RM("allocDev2[%s]\n",allocDev_Str[freeMOD->allocDev	]);
					}

					freeMOD->subUsed			= 0;
					AUD_KDRV_RM("free 2\n");

				}
				break;
		 	}

					// no dev case
			if ( i == MAX_OWN_MOUDLE -1 )
			{
				AUD_KDRV_RMD(" NO Module resource to free [%d] \n",__LINE__);
				return ADEC_MODULE_NO_MOD;
			}
		}

		return RET_OK;
	}
#ifdef ENABLE_MULTI_INPUT
	else if (ModInfo.list[modToFree].hasFakeMod == 1 &&  ModInfo.list[modToFree].subUsed == 1 )
	{
		// device node's module free;
		for(	i = 0 ; i < MAX_OWN_MOUDLE; i++)
		{
			AUD_KDRV_RMD(" own[%s] alloc[%s]  [%s] allocCnt [%d]\n",allocMod_Str[DevInfo.list[belongto].own[i].mod ],allocMod_Str[modToFree],modTypeStr[modType],ModInfo.allocCnt[modType] );
		 	if (DevInfo.list[belongto].own[i].mod == modToFree)
			{
				DevInfo.list[belongto].own[i].mod = ADEC_MODULE_NO_MOD ;

				DevInfo.list[belongto].ownNum--;

				freeMOD =&ModInfo.list[modToFree];
				freeMOD->connectStart		= 0;
				freeMOD->used		 		= 0;
				freeMOD->modType  			= LX_AUD_MOD_TYPE_NONE;
				freeMOD->allocMod 		= ADEC_MODULE_NO_MOD;
				freeMOD->allocDev 		= AUD_NO_DEV;
				freeMOD->allocStr 		= NULL;
				//freeMOD->multiSinkPortNum 	= HAS_NOT_MULTISINK_PORT;

				for(k=0; k< MAX_PORT; k++)
				{
					freeMOD->out[k] = NULL;
					freeMOD->in[k] 	= NULL;
					freeMOD->inOutMap[k].map.in= 	ADEC_MODULE_NO_MOD;
					freeMOD->inOutMap[k].map.out= 	ADEC_MODULE_NO_MOD;
					freeMOD->inPool		=	0xffff;
					freeMOD->outPool	=	0xffff;

				}

				freeMOD->connType = CONN_TYPE_NONE;

				freeMOD->allocSubDev	= AUD_NO_DEV;
				freeMOD->subUsed			= 0;
				AUD_KDRV_RM("free 3\n");
				break;
		 	}

					// no dev case
			if ( i == MAX_OWN_MOUDLE -1 )
			{
				AUD_KDRV_RMD(" NO Module resource to free [%d] \n",__LINE__);
				return ADEC_MODULE_NO_MOD;
			}
		}

		return RET_OK;
	}
#endif //ENABLE_MULTI_INPUT
	else
	{
		return ADEC_MODULE_NO_MOD;
	}
}

/**
 * Get Alloc Module info in allocDev
 *
 * @param 	allocDev		[in]  alloc device  to ack whether it has module?(in value)
 * @param 	allocModNum	[out]  pointer of alloc module number( out value )
 * @param 	ppOwnMods:   	[out] duble pointer of alloc module belong to given allocDev  (out value)
 * @return 	if succeeded -RET_OK , else - RET_OK.
 * @see
 */

int  AUDIO_GetAllocInfo ( UINT32 allocDev , UINT32 * allocModNum,  LX_AUD_MOD_T  ** ppOwnMods )
{
	if ( allocDev < AUD_DEV_DEC0 || allocDev >= AUD_DEV_MAX)
	{
		AUD_KDRV_RM("[%s][%d] Check Arg \n",__FUNCTION__,__LINE__);
		return ADEC_MODULE_NO_MOD;
	}

	* allocModNum	=DevInfo.list[allocDev].ownNum;
	* ppOwnMods 		= &DevInfo.list[allocDev].own[0];

	//AUD_KDRV_RM("[%s][%d] [%s:%d]allocNum:%d\n",__FUNCTION__,__LINE__,allocMod_Str[DevInfo.list[allocDev].own[0].mod],DevInfo.list[allocDev].own[0].mod, * allocModNum);
	return RET_OK;
}


/**
 * Ask for Device to have given module type
 *
 * @param 	allocDev		[in]  alloc device  to ack whether it has module type ?(in value)
 * @param 	modTypeToFind	[in]   module type to find( out value )
 * @return 	if succeeded -LX_AUD_ALLOC_MOD_T , else - ADEC_MODULE_NO_MOD.
 * @see
 */

LX_AUD_ALLOC_MOD_T  AUDIO_HasThisModuleType ( UINT32 allocDev , LX_AUD_MOD_TYPE_T modTypeToFind )
{


	LX_AUD_MOD_T	*pOwnMods;
	UINT32			allocModNum, i , isExist= 0;
	UINT32 allocMod = ADEC_MODULE_NO_MOD;

	if ( allocDev < AUD_DEV_DEC0 || allocDev >= AUD_DEV_MAX)
	{
		AUD_KDRV_RM("[%s][%d] Check Arg\n",__FUNCTION__,__LINE__);
		return ADEC_MODULE_NO_MOD;
	}

	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	isExist = 0;
	for( i = 0 ; i  < allocModNum  ; i++)
	{
		if (pOwnMods[i].modType == modTypeToFind)
		{
			allocMod = pOwnMods[i].mod;
			isExist=1;
			break;
		}
	}

	if(isExist == 1   && allocMod !=ADEC_MODULE_NO_MOD )
	{
		return allocMod;
	}
	else
		return ADEC_MODULE_NO_MOD;

}

/**
 * Ask for port which is connected with connectedWithMod
 *
 * @param 	portOwnerMod		[in]  module to ask port connected with connectedWithMod(module) (in value)
 * @param 	connectedWithMod	[in]  ( in value )
 * @return 	if succeeded -port num , else - PORT_NONE.
 * @see
 */

UINT32  AUDIO_GetConnectedPort ( UINT32 portOwnerMod , UINT32 connectedWithMod )
{
	UINT32		i, connectedPort = PORT_NONE;

	LX_AUD_ALLOC_FREE_INFO_T *portOwnerMOD=NULL, *connectedWithMOD =NULL;


	portOwnerMOD 	= AUDIO_GetAllocModInfo( portOwnerMod );
	connectedWithMOD = AUDIO_GetAllocModInfo( connectedWithMod );


	for(i =0; i < MAX_PORT; i++)
	{
		if(portOwnerMOD->inOutMap[i].map.out == connectedWithMOD->allocMod)
		{
			connectedPort = i;
			break;
		}
	}

	if(connectedPort != PORT_NONE)
		return connectedPort;
	else
		return PORT_NONE;
}
/**
 * Get Module.
 *
 * @param 	allocDev		[in] a allocated decoder device.
 * @param 	modType			[in] module type.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		.
 */
UINT32 AUDIO_GetModule(UINT32 allocDev, LX_AUD_MOD_TYPE_T modType)
{
	UINT32			module = ADEC_MODULE_NO_MOD;
	UINT32			allocModNum = 0;
	UINT32			i = 0;
	LX_AUD_MOD_T	*pOwnMods;

	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);

	for( i = 0 ; i  < allocModNum  ; i++)
	{
		if (pOwnMods[i].modType == modType)
		{
			module = pOwnMods[i].mod;
			break;
		}
	}

	AUD_KDRV_PRINT("%s : mod %x.\n", __F__, module);
	return module;
}

/**
 * Initailization of  Device  and Module info
 *
 * @param 	: none
 * @return 	if succeeded -RET_OK , else - RET_OK.
 * @see
 */


int  AUDIO_DevInfoInit ( void  )
{
	int i,j,k,fwModNum = 0,fwModIndex = 1,cur = NOT_CLASSIFIED;
	int curLen = 0 , nextLen = 0, cmpLen = 0, lastModLen = 0;
	LX_AUD_ALLOC_FREE_INFO_T * MOD, * DEV;

	UINT8 curModName[20], nextModName[20];

	ModuleInfo moduleInfo;

	curModName[0]='\0';
	nextModName[0]='\0';

	for(i=0; i < LX_AUD_MOD_TYPE_MAX; i++ )
	{
		if( i == LX_AUD_MPB )
			bufIF_TableLUT[i] = LX_AUD_BUB_IF_IDX_MPB;
		else if( i == LX_AUD_CPB )
			bufIF_TableLUT[i] = LX_AUD_BUB_IF_IDX_CPB;
		else if( i == LX_AUD_DPB )
			bufIF_TableLUT[i] = LX_AUD_BUB_IF_IDX_DPB;
		else if( i == LX_AUD_IEC )
			bufIF_TableLUT[i] = LX_AUD_BUB_IF_IDX_IEC;
		else if( i == LX_AUD_CAPB )
			bufIF_TableLUT[i] = LX_AUD_BUB_IF_IDX_CAPB;
		else
			bufIF_TableLUT[i]=0;
	}


	memset(&ModInfo,0x0,sizeof(LX_AUD_MOD_INFO_T));
	memset(&DevInfo,0x0,sizeof(LX_AUD_DEV_INFO_T));

	// initialize module info
	for( i =0 ; i < ADEC_MODULE_MAX ; i++)
	{
		AUD_KDRV_RM("Mod[%11s] num[%2d] [%p]\n",stFwMod[i].ModNumName,stFwMod[i].ModNum, stFwMod[i].ModNumName );
	}
	AUD_KDRV_RM("===================================================================================================================\n");

 		stFwRmModType[0].ModNumName 	= stFwMod[0].ModNumName;
 		stFwRmModType[0].ModNum 		= stFwMod[0].ModNum;


	// find module type
	for( i =1 ; i < ADEC_MODULE_MAX ; i++)
	{
		if ( i < ADEC_MODULE_MAX -1)
		{
			curLen 	= strlen(stFwMod[i].ModNumName) - 1;
			nextLen = strlen(stFwMod[i+1].ModNumName)- 1;

			strncpy( curModName, stFwMod[i].ModNumName, curLen);
			strncpy( nextModName, stFwMod[i+1].ModNumName, nextLen);
			curModName[curLen] = '\0';
			nextModName[nextLen] = '\0';

			if( curLen > nextLen  )
				cmpLen = curLen;
			else
				cmpLen = nextLen;

			AUD_KDRV_RM("[%11s][%4d]c[%11s]n[%11s]$[%d][%11s][%2d]\n",allocMod_Str[i],__LINE__,curModName , nextModName,!strncmp(curModName,nextModName,cmpLen),stFwMod[i].ModNumName,stFwMod[i].ModNum);
		}


		if( (! (stFwMod[i].ModNum == ADEC_MODULE_MAN_DSP0 ) && ! (stFwMod[i].ModNum == ADEC_MODULE_DBG_DSP0 ) && ! (stFwMod[i].ModNum == ADEC_MODULE_TP_IN_0 ) &&
			! (stFwMod[i].ModNum == ADEC_MODULE_DUMP_DSP0 ) && ! (stFwMod[i].ModNum == ADEC_MODULE_DTO_D ) &&! (stFwMod[i].ModNum == ADEC_MODULE_SRC_D3)  && ! (stFwMod[i].ModNum == ADEC_MODULE_SRC_9 ) &&
			! (stFwMod[i].ModNum == ADEC_MODULE_LIP_9 ) && ! (stFwMod[i].ModNum == ADEC_MODULE_DTO_A) && ! (stFwMod[i].ModNum == ADEC_MODULE_IMC_DSP0)&&
			! (stFwMod[i].ModNum == ADEC_MODULE_HWSRC_DSP0 ) && ! (stFwMod[i].ModNum == ADEC_MODULE_CTRLSRC_2 ) &&
			!strncmp(curModName,nextModName, curLen)) ||
			stFwMod[i].ModNum == ADEC_MODULE_OUT_CTRL_0 ||
			stFwMod[i].ModNum == ADEC_MODULE_OUT_CTRL_1 ||
			stFwMod[i].ModNum == ADEC_MODULE_OUT_CTRL_2
			)
		{
			cur = SAME_MOD;
			AUD_KDRV_RM("[%11s][%4d] same module is left\n",allocMod_Str[i],__LINE__);
			fwModNum++;
		}
		else
		{
			cur = LAST_MOD_OF_SAME_MODS ;

			if (
				( fwModNum > 0)
				//(strncmp(curModName,nextModName, cmpLen) && fwModNum > 0)
				//(strncmp(curModName,nextModName, cmpLen) && cur == LAST_MOD_OF_SAME_MODS && fwModNum > 0)
			)
			{
				AUD_KDRV_RM("###[%11s]%d]\n",allocMod_Str[i],__LINE__);

				lastModLen 	= strlen(stFwMod[i].ModNumName) - 1;
				strncpy( lastModName[lastModNum]  , stFwMod[i].ModNumName, lastModLen);
				stFwRmModType[fwModIndex].ModNumName =(char*)lastModName[lastModNum++];

				AUD_KDRV_RM("###[%11s]last[%11s]%d]\n",allocMod_Str[i],lastModName[i] ,__LINE__);
				stFwRmModType[fwModIndex].ModNum = fwModNum+1;

				fwModIndex++;
				fwModNum = 0;
			}
			else
			{
				AUD_KDRV_RM("##[%11s][%2d] $[%2d] c[%11s] n[%11s]\n",allocMod_Str[i],__LINE__,strncmp(curModName,nextModName, cmpLen), curModName,nextModName  );
				stFwRmModType[fwModIndex].ModNumName = stFwMod[i].ModNumName;
				stFwRmModType[fwModIndex].ModNum = 1;
				fwModIndex++;
			}
		}
	}

	fwModTypeNum=fwModIndex;

	// initialize RM module info
	for( i =0 ; i < RM_MODULE_NUM ; i++)
	{
		stFwRmModType[fwModIndex + i].ModNumName = stRmMod[i].ModNumName;
		stFwRmModType[fwModIndex + i].ModNum = stRmMod[i].ModNum;
	}


	AUD_KDRV_RM("===================================================================================================================\n");
	// display module info
	for( i =0 ; i < fwModTypeNum + RM_MODULE_NUM ; i++)
	{
		modTypeStr[i] = stFwRmModType[i].ModNumName;
		AUD_KDRV_RM("BUFIF[%2d] Mod[%2d][%11s] num[%d] LX_AUD_MOD_TYPE_MAX[%d]\n",bufIF_TableLUT[i],i,stFwRmModType[i].ModNumName,stFwRmModType[i].ModNum,LX_AUD_MOD_TYPE_MAX);
	}

//	stFwRmModType[0].ModNumName 	= stFwMod[0].ModNumName;
//	stFwRmModType[0].ModNum 		= stFwMod[0].ModNum;

	AUD_KDRV_RM("size of LX_AUD_DEV_INFO_T :[%x]\n",sizeof(LX_AUD_DEV_INFO_T));
	AUD_KDRV_RM("size of LX_AUD_MOD_INFO_T :[%x]\n",sizeof(LX_AUD_MOD_INFO_T));
	AUD_KDRV_RM("===================================================================================================================\n");
	// initialize module info
	for( i =0 ; i < ADEC_MODULE_MOD_MAX ; i++)
	{

		ModuleList_GetModuleInfo(i, &moduleInfo);

		MOD =&ModInfo.list[i];

		for(k=0; k< MAX_PORT; k++)
		{
			MOD->out[k] = NULL;
			MOD->in[k] 	= NULL;
			MOD->inOutMap[k].total[0]= 0;
			MOD->inOutMap[k].total[1]= 0;

			MOD->inOutMap[k].map.in= 	ADEC_MODULE_NO_MOD;
			MOD->inOutMap[k].map.out= 	ADEC_MODULE_NO_MOD;
		}

		MOD->status= NONE;
		MOD->allocStr = NULL;
		MOD->allocDev 		= AUD_NO_DEV;
		MOD->allocMod 		= ADEC_MODULE_NO_MOD;
		MOD->inNum		=	moduleInfo.num_in;
		MOD->outNum	=	moduleInfo.num_out;

		MOD->multiSinkPortNum = HAS_NOT_MULTISINK_PORT;
		for(j = 0; j < ADEC_CNST_MODULE_MAX_OUT_PORT	; j ++)
		{
			if( moduleInfo.out_buffer_type[j] == ADEC_BUF_MULTI_SINK)
				MOD->multiSinkPortNum	= j;
		}

		MOD->connectStart = 0;
		MOD->connType = CONN_TYPE_NONE;

		if( i == ADEC_MODULE_IEC_0 || i == ADEC_MODULE_IEC_1)
			MOD->needToConnectToIntra = 1;
		else
			MOD->needToConnectToIntra = 0;

		if(i < ADEC_MODULE_MAX)
		{
			MOD->hasMultiSink = (moduleInfo.out_buffer_type[0] == ADEC_BUF_MULTI_SINK ) ? 1: 0;
			MOD->hasIntra = (moduleInfo.out_buffer_type[1] == ADEC_BUF_INTRA ) ? 1: 0;

			if(MOD->hasMultiSink)
			{
				MOD->outPortSearchBase = MULTISINKBASE;
			}
			else
			{
				MOD->outPortSearchBase = 0;
			}
		}
		else
		{
			MOD->outPortSearchBase = 0;
			MOD->hasMultiSink = 0;
		}

		if(moduleInfo.module >= ADEC_MODULE_TP_IN_0 && moduleInfo.module <= ADEC_MODULE_ADC_IN)
		{
			MOD->hasFakeMod = 1;
		}
		else
		{
			MOD->hasFakeMod = 0;
		}

		MOD->allocSubDev 		= AUD_NO_DEV;

		if(moduleInfo.module == ADEC_MODULE_MIX_0)
		{
			MOD->inPool		=		0xffffffff;
			MOD->outPool	=		0xffffffff   &	(~(( LX_AUD_OUTPUT_HP|LX_AUD_OUTPUT_SCART|LX_AUD_OUTPUT_SPDIF )<< MULTISINKBASE));

			MOD->out[MULTISINKBASE + LX_AUD_OUTPUT_HP_B		] =	AUDIO_GetAllocModInfo(ADEC_MODULE_OUT_CTRL_1) ;
			MOD->out[MULTISINKBASE + LX_AUD_OUTPUT_SCART_B	] =	AUDIO_GetAllocModInfo(ADEC_MODULE_OUT_CTRL_2) ;
			MOD->out[MULTISINKBASE + LX_AUD_OUTPUT_SPDIF_B		] =	AUDIO_GetAllocModInfo(ADEC_MODULE_OUT_CTRL_3) ;

			MOD->inOutMap[MULTISINKBASE + LX_AUD_OUTPUT_HP_B		].map.out =	USED_PORT;
			MOD->inOutMap[MULTISINKBASE + LX_AUD_OUTPUT_SCART_B		].map.out =	USED_PORT;
			MOD->inOutMap[MULTISINKBASE + LX_AUD_OUTPUT_SPDIF_B		].map.out =	USED_PORT;

		}
		else
		{
			if(MOD->hasMultiSink == 1 && MOD->hasIntra == 1)
			{
				MOD->inPool		=	0xffffffff;
				MOD->outPool	=	0xffffffff;
			}
			else
			{
				MOD->inPool		=	0xffffffff;
				MOD->outPool	=	0xffffffff;
			}
		}

		//ModInfo.OpenCnt
		AUD_KDRV_RM("[%2d] dev/mod address[%p] [%11s] hasM[%d] info[%d] MP[%d] \n",i,&ModInfo.list[i ],allocMod_Str[i],MOD->hasMultiSink,moduleInfo.out_buffer_type[0] ,MOD->multiSinkPortNum);
	}
	AUD_KDRV_RM("===================================================================================================================\n");
	ModInfo.allocBase[0] = 0;

	for( i =0 ; i < LX_AUD_MOD_TYPE_MAX ; i++)
	{
		ModInfo.allocCnt[i] = 0;
		//ModInfo.availableNum[i] = modAvailableNum[i];
		ModInfo.availableNum[i] = stFwRmModType[i].ModNum;

		if( i+1 < LX_AUD_MOD_TYPE_MAX )
			//ModInfo.allocBase[i+1] =   ModInfo.allocBase[i] + modAvailableNum[i];
			ModInfo.allocBase[i+1] =   ModInfo.allocBase[i] + stFwRmModType[i].ModNum;
		AUD_KDRV_RM("[%12s][%d]allocCnt[%d] availableNum[%d] allocBase[%d]\n",modTypeStr[i] ,i,ModInfo.allocCnt[i],ModInfo.availableNum[i],ModInfo.allocBase[i]   );
	}

	// initailize dev info
	for( i =0 ; i < AUD_DEV_MAX ; i++)
	{

		DEV =&DevInfo.list[i];

		DEV->out[0] 		= NULL;
		DEV->in[0] 			= NULL;
		DEV->allocStr 		= NULL;
		DEV->allocDev 		= AUD_NO_DEV;
		DEV->allocSubDev 	= AUD_NO_DEV;

		DEV->headOfDev		= NULL;
		DEV->tailOfDev		= NULL;

		for( j =0 ; j < MAX_OWN_MOUDLE ; j++)
			DEV->own[j].mod = ADEC_MODULE_NO_MOD;

		AUD_KDRV_RM("[%d] dev/mod address[%p]\n",i,&DevInfo.list[i ]);
	}

	DevInfo.allocBase[0] = 0;

	for( i =0 ; i < LX_AUD_DEV_TYPE_MAX ; i++)
	{
		DevInfo.allocCnt[i] = 0;
		DevInfo.availableNum[i] = devAvailableNum[i];

		if( i+1 < LX_AUD_DEV_TYPE_MAX )
			DevInfo.allocBase[i+1] =   DevInfo.allocBase[i] + devAvailableNum[i];
		AUD_KDRV_RM("[%12s][%d]allocCnt[%d] availableNum[%d] allocBase[%d]\n",devTypeStr[i] ,i,DevInfo.allocCnt[i],DevInfo.availableNum[i],DevInfo.allocBase[i]   );
	}
	return RET_OK;
}



/**
 * Check Whether Left(module) is connneted with Right(module)
 *
 * @param 	left	[in] alloc module
 * @param 	right	[in] alloc module
 * @return 	if not yet connected  -1 , else -0 .
 * @see
 */

int  AUDIO_IsNotConnectedYet ( UINT32 left, UINT32 right)
{
	LX_AUD_ALLOC_FREE_INFO_T *leftMOD, *rightMOD;
	UINT32 i, leftFind=0, rightFind = 0;

	leftMOD = AUDIO_GetAllocModInfo(left);
	rightMOD = AUDIO_GetAllocModInfo(right);

	if( ( leftMOD == NULL)||( rightMOD == NULL) )
	{
		AUD_KDRV_ERROR("========= Not Conn ============ \n");
		AUD_KDRV_ERROR("leftMOD[%p] rightMOD[%p]  \n",leftMOD, rightMOD);
		return 0;
	}


	for(i = 0 ; i < MAX_PORT;i++)
	{
		if(leftMOD->inOutMap[i].map.out == right )
		{
			leftFind = 1;
			break;
		}

	}

	for(i = 0 ; i < MAX_PORT;i++)
	{
		if( rightMOD->inOutMap[i].map.in == left)
		{
			rightFind = 1;
			break;
		}

	}
	if( leftFind == 1 && rightFind == 1	)
		return 0;
	else
		return 1;
}

/**
 * Check Whether Left(module) is connneted with Right(module)
 *
 * @param 	left	[in] alloc module
 * @param 	right	[in] alloc module
 * @return 	if already connected  -1 , else -0 .
 * @see
 */

int  AUDIO_IsAlreadyConnected ( UINT32 left, UINT32 right)
{
	LX_AUD_ALLOC_FREE_INFO_T *leftMOD, *rightMOD;
	UINT32 i, leftFind=0, rightFind = 0;

	leftMOD = AUDIO_GetAllocModInfo(left);
	rightMOD = AUDIO_GetAllocModInfo(right);

	if( ( leftMOD == NULL)||( rightMOD == NULL) )
	{
		AUD_KDRV_ERROR("========= Aly Conn ============ \n");
		AUD_KDRV_ERROR("leftMOD[%p] rightMOD[%p]  \n",leftMOD, rightMOD);
		return 0;
	}


	for(i = 0 ; i < MAX_PORT;i++)
	{
		AUD_KDRV_RMD("l%d",leftMOD->inOutMap[i].map.out);
		if(leftMOD->inOutMap[i].map.out == right )
		{
			leftFind = 1;
			break;
		}


	}
	AUD_KDRV_RMD("\n");

	for(i = 0 ; i < MAX_PORT;i++)
	{
		AUD_KDRV_RMD("r%d",rightMOD->inOutMap[i].map.in);
		if( rightMOD->inOutMap[i].map.in == left)
		{

			rightFind = 1;
			break;
		}

	}
	AUD_KDRV_RMD("\n");
	AUD_KDRV_RMD("leftFind %d righfind %d\n", leftFind,leftFind );

	if( leftFind == 1 && rightFind == 1	)
		return 1;
	else
		return 0;
}


/**
 * Do Connection between modules trhu IMC command Considering relation between modules
 *
 * @param 	 left				[in] return of AUDIO_AllocModule, should be a module
 * @param 	 right			[in] return of AUDIO_AllocModule, should be a module
 * @param 	 forceLeftOutPort	[in] port num to connect  in forcing manager
 * @param 	 foreceRightInPort	[in] port num to connect  in forcing manager
 * @return 	return leftOut_15_8_RightIn_7_0 [out] leftOutPort 15:8 bitfield rightInPort:7:0 bitfield
 *  connection sequence  become : A - B
 * @see
 */


int
AUDIO_ConnectTo ( UINT32 left, UINT32 right, UINT32 forceLeftOutPort, UINT32 foreceRightInPort)
{
	CmCmdAllocBuf		allocBuf;
	CmCmdConnect		connectModule;
	LX_AUD_ALLOC_FREE_INFO_T * leftMOD, * rightMOD,* leftDEV, *rightDEV,*leftHead, *rightTail;


	int		leftOut_15_8_RightIn_7_0 =0;
	UINT32 	rightInPort = 0,leftOutPort = 0;
	UINT32	leftBelongTo,rightBelongTo;
	UINT32	leftAvailablePortNum = 0 ,rightAvailablePortNum = 0;
	UINT32	leftSubBelongTo;
	UINT32 	IsForcePort = 0;
	UINT32	moduleToAllocBuf,managerModule;
	UINT32 	leftManagerModule,rightManagerModule;
	UINT32 	isRM_ModUsed = 0; // is included module defined only in resource mgr like EPB,CPB,DPB
	UINT32	outPortSearchBase	=	0;
	UINT32	buffIndex = 0;

	LX_AUD_BUF_MEM_CFG_S_T * pstBufIF;

	AUD_KDRV_RM("##### [%s] [%d]  left[%s:%d] right[%s:%d] \n",__FUNCTION__,__LINE__,allocMod_Str[left],left,allocMod_Str[right],right);

	if(right >= ADEC_MODULE_NO_MOD ||left >= ADEC_MODULE_NO_MOD )
	{
		AUD_KDRV_RM("Check Arg [%s] [%d] ADEC_MODULE_MOD_MAX[%d] \n",__FUNCTION__,__LINE__,ADEC_MODULE_NO_MOD);
		return RET_ERROR;
	}

	if( forceLeftOutPort != NO_FORCE || foreceRightInPort != NO_FORCE )
	{
		IsForcePort = 1;
	}

	leftMOD	= &ModInfo.list[left];
	rightMOD	= &ModInfo.list[right];

	leftBelongTo	= leftMOD->allocDev;
	rightBelongTo	= rightMOD->allocDev;
	leftSubBelongTo	= leftMOD->allocSubDev;
	leftDEV	=  &DevInfo.list[leftBelongTo];
	rightDEV	=  &DevInfo.list[rightBelongTo];


	if ( left >= ADEC_MODULE_MAX || right >= ADEC_MODULE_MAX)
	{
		isRM_ModUsed = 1;
	}

	leftManagerModule = _AUDIO_GetManagerModule(left);
	rightManagerModule = _AUDIO_GetManagerModule(right);

	AUD_KDRV_RMD(" leftMOD:%p rightMOD:%p leftBelongTo:%d rightBelongTo:%d leftDEV:%p rightDEV:%p \n",leftMOD,rightMOD,leftBelongTo,rightBelongTo, leftDEV,rightDEV);

	if (IsForcePort)
	{
		leftOutPort	=	forceLeftOutPort;
		rightInPort	=	foreceRightInPort;
	}
	else
	{
		if(leftMOD->hasMultiSink && leftMOD->hasIntra)
		{
			AUD_KDRV_RMD("[%s] hasMultiSink\n",allocMod_Str[left] );

			if( rightMOD->needToConnectToIntra)//LX_AUD_IEC
			{
				AUD_KDRV_RMD("[%s] needToConnectToIntra\n",allocMod_Str[right] );
				leftOutPort	=	AUDIO_GetPort(leftMOD, OUT_PORT, 0 );
				rightInPort	=	AUDIO_GetPort(rightMOD, IN_PORT, 0);
			}
			else
			{
				AUD_KDRV_RMD("[%s] NO needToConnectToIntra\n",allocMod_Str[right] );
				leftOutPort	=	AUDIO_GetPort(leftMOD, OUT_PORT, 1 );
				rightInPort	=	AUDIO_GetPort(rightMOD, IN_PORT, 0);
			}
		}
		else if (leftMOD->hasMultiSink )
		{
			if( rightMOD->needToConnectToIntra)//LX_AUD_IEC //-> error case
			{
				AUD_KDRV_RMD("LEFT [%s] NOT hasIntra\n",allocMod_Str[left] );
			}
			else
			{
				AUD_KDRV_RMD("[%s] NO needToConnectToIntra\n",allocMod_Str[right] );
				leftOutPort	=	AUDIO_GetPort(leftMOD, OUT_PORT, 1 );
				rightInPort	=	AUDIO_GetPort(rightMOD, IN_PORT, 0);
			}
		}
		else
		{
			AUD_KDRV_RMD("[%s] NOT hasMultiSink\n",allocMod_Str[left] );
			leftOutPort	=	AUDIO_GetPort(leftMOD	, OUT_PORT, 0);
			rightInPort	=	AUDIO_GetPort(rightMOD,  IN_PORT, 0);
		}
	}

	if(leftOutPort == PORT_FULL || rightInPort == PORT_FULL)
	{
		AUD_KDRV_RM("PORT FULL\n");
		return RET_ERROR;
	}
	else
	{
		AUD_KDRV_RMD("leftOutPort[%s:%d] rightInPort[%s:%d] leftinpool[%llx] leftoutpool[%llx rightinpool[%llx] rightoutpool[%llx]\n",allocMod_Str[left],leftOutPort,allocMod_Str[right],rightInPort,leftMOD->inPool,leftMOD->outPool,rightMOD->inPool,rightMOD->outPool);

		leftMOD->inOutMap[leftOutPort].map.out	=	right;
		rightMOD->inOutMap[rightInPort].map.in	=	left;

		leftMOD->out[leftOutPort] 	=  rightMOD;
		rightMOD->in[rightInPort]		= leftMOD;
	}

	leftAvailablePortNum  = AUDIO_GeAvailabletPortNum(leftMOD,OUT_PORT);
	rightAvailablePortNum  = AUDIO_GeAvailabletPortNum(rightMOD,IN_PORT);

	//AUD_KDRV_ERROR("leftAvailablePortNum[%d] rightAvailablePortNum[%d]\n",leftAvailablePortNum,rightAvailablePortNum);

	if(leftMOD->hasMultiSink &&  leftMOD->hasIntra  )
		leftAvailablePortNum  = leftAvailablePortNum +1;
	if(rightMOD->hasMultiSink &&  rightMOD->hasIntra  )
		rightAvailablePortNum  = rightAvailablePortNum +1;

	//AUD_KDRV_ERROR("leftAvailablePortNum[%d %d %d] rightAvailablePortNum[%d %d %d]\n",leftMOD->multiConnIdx,leftMOD->hasMultiSink,leftMOD->hasIntra,rightMOD->multiConnIdx,rightMOD->hasMultiSink,rightMOD->hasIntra);

	leftMOD->multiConnIdx = AUDIO_GeMultiConnectiionOutPortNum(leftMOD);

		//rightMOD->multiConnIdx = MAX_PORT - rightAvailablePortNum;
	AUD_KDRV_RMD("LM[%d] RM[%d]\n",leftMOD->multiConnIdx,rightMOD->multiConnIdx);
	AUD_KDRV_RMD("LO[%d] RI[%d]\n",leftOutPort,rightInPort);

	leftHead 	= leftMOD;
	rightTail	= rightMOD;

	//same device node
	// assume that input device is left
	if( leftBelongTo == rightBelongTo || leftSubBelongTo == rightBelongTo)
	{
		//AUD_KDRV_ERROR("leftAvailablePortNum[%d %d %d] rightAvailablePortNum[%d %d %d]\n",leftMOD->multiConnIdx,leftMOD->hasMultiSink,leftMOD->hasIntra,rightMOD->multiConnIdx,rightMOD->hasMultiSink,rightMOD->hasIntra);
		//AUD_KDRV_ERROR("LM[%d] RM[%d]\n",leftMOD->multiConnIdx,rightMOD->multiConnIdx);

		if( isRM_ModUsed  ==1 )
		{
			if( leftMOD->modType == LX_AUD_CPB  ||leftMOD->modType == LX_AUD_DPB  || leftMOD->modType ==LX_AUD_MPB || leftMOD->modType ==LX_AUD_IEC|| leftMOD->modType ==LX_AUD_CAPB)
			{
				switch(leftMOD->modType)
				{
					case LX_AUD_CPB:
					case LX_AUD_DPB:
					case LX_AUD_MPB:
					case LX_AUD_IEC:
					case LX_AUD_CAPB:


						pstBufIF = bufIF[  bufIF_TableLUT[ leftMOD->modType] ];
						buffIndex = leftMOD->allocMod - pstBufIF->bufIndexBase;
						pstBufIF = pstBufIF + buffIndex;
						leftMOD->connType  = ((UINT8 *)pstBufIF->pConTypeL)[ bufIF_TableLUT[ leftMOD->modType]];
						allocBuf.physical_addr =  pstBufIF->MemPhyBase;
						allocBuf.register_addr_offset	= pstBufIF->pRegBase - (void *)&g_pRealRegAud->aud_mem_share_base;
						//AUD_KDRV_RM("[%s] [%d] [%d] [%d [%x] [%x] [%x] b[%d]\n",__FUNCTION__,__LINE__, leftMOD->modType,bufIF_TableLUT[leftMOD->modType], pstBufIF->MemPhyBase, pstBufIF->pRegBase ,allocBuf.register_addr_offset ,buffIndex);
						break;
					default:
						break;
				}


				moduleToAllocBuf	=	right;
				allocBuf.module		= moduleToAllocBuf;
				allocBuf.port		= MOD_IN_PORT(rightInPort);
				allocBuf.is_reader	= TRUE;

				if( allocBuf.physical_addr  < pstMemCfgAud->start_memory_base  ||  allocBuf.physical_addr  > pstMemCfgAud->end_memory_base)
				{
					AUD_KDRV_ERROR("start[%8x] end[%8x] buf[%8x] idx[%d]\n",pstMemCfgAud->start_memory_base, pstMemCfgAud->end_memory_base, allocBuf.physical_addr, leftMOD->modType  );
					AUD_KDRV_ERROR("1[%11s]       ----%s----      [%11s] ALLOC moduleToAllocBuf:%d port:%d read:%d leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	,allocBuf.is_reader, leftOutPort , outPortSearchBase);
					return RET_ERROR;
				}


				leftOut_15_8_RightIn_7_0 = allocBuf.port;

				managerModule = _AUDIO_GetManagerModule(moduleToAllocBuf);
				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF, managerModule, sizeof(CmCmdAllocBuf), &allocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}
				AUD_KDRV_RM("[%11s]       ----%s----      [%11s] ALLOC moduleToAllocBuf:%d port:%d read:%d leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	,allocBuf.is_reader, leftOutPort , outPortSearchBase);
			}
			else if( rightMOD->modType == LX_AUD_CPB  ||rightMOD->modType == LX_AUD_DPB  || rightMOD->modType ==LX_AUD_MPB ||rightMOD->modType ==LX_AUD_IEC||rightMOD->modType ==LX_AUD_CAPB)
			{
				switch(rightMOD->modType)
				{
					case LX_AUD_CPB:
					case LX_AUD_DPB:
					case LX_AUD_MPB:
					case LX_AUD_IEC:
					case LX_AUD_CAPB:

						pstBufIF = bufIF[  bufIF_TableLUT[ rightMOD->modType] ];
						buffIndex = rightMOD->allocMod - pstBufIF->bufIndexBase;
						pstBufIF = pstBufIF + buffIndex;
						leftMOD->connType  = ((UINT8 *)pstBufIF->pConTypeR)[ bufIF_TableLUT[ rightMOD->modType]];

						allocBuf.physical_addr =  pstBufIF->MemPhyBase;
						allocBuf.register_addr_offset	= pstBufIF->pRegBase - (void *)&g_pRealRegAud->aud_mem_share_base;
						//AUD_KDRV_RM("[%s] [%d] [%d] [%d [%x] [%x] [%x] b[%d]\n",__FUNCTION__,__LINE__, rightMOD->modType,bufIF_TableLUT[rightMOD->modType], pstBufIF->MemPhyBase, pstBufIF->pRegBase ,allocBuf.register_addr_offset ,buffIndex);
						break;
					default:
						break;
				}


				moduleToAllocBuf	=	left;
				allocBuf.module		= moduleToAllocBuf;

				outPortSearchBase   = leftMOD->outPortSearchBase;

				if(leftMOD->hasMultiSink && leftMOD->hasIntra && rightMOD->needToConnectToIntra)
				{
					outPortSearchBase	 = 0;
					allocBuf.port		= MOD_OUT_PORT( (leftOutPort - outPortSearchBase));
				}
				//AUD_KDRV_RM("left hasMultiSink[%d] left hasIntra[%d] right needToConnectToIntra [%d] \n", leftMOD->hasMultiSink , leftMOD->hasIntra , rightMOD->needToConnectToIntra );
				else if(leftMOD->hasMultiSink)
				{

					allocBuf.port		= MOD_OUT_PORT(0)+ (leftOutPort - outPortSearchBase);
				}
				else
				{
					allocBuf.port		= MOD_OUT_PORT( (leftOutPort - outPortSearchBase) );
				}

				if( allocBuf.physical_addr  < pstMemCfgAud->start_memory_base  ||  allocBuf.physical_addr  > pstMemCfgAud->end_memory_base)
				{
					AUD_KDRV_ERROR("start[%8x] end[%8x] buf[%8x] idx[%d]\n",pstMemCfgAud->start_memory_base, pstMemCfgAud->end_memory_base, allocBuf.physical_addr, rightMOD->modType  );
					AUD_KDRV_ERROR(" 2[%11s]       ----%s----      [%11s] ALLOC moduleToAllocBuf:%d port:%d leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	, leftOutPort , outPortSearchBase);
					return RET_ERROR;
				}

				leftOut_15_8_RightIn_7_0 = allocBuf.port;

				allocBuf.is_reader	= FALSE;

				managerModule = _AUDIO_GetManagerModule(moduleToAllocBuf);
				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF, managerModule, sizeof(CmCmdAllocBuf), &allocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}
				AUD_KDRV_RM("[%11s]       ----%s----      [%11s] ALLOC moduleToAllocBuf:%d port:%d read:%d leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	,allocBuf.is_reader, leftOutPort , outPortSearchBase);

			}
			else
			{
				AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
			}


		}
		else if (isRM_ModUsed  ==0 )
		{
			if( leftManagerModule == rightManagerModule  && leftManagerModule != ADEC_MODULE_NOT_DEF )
			{
				leftMOD->connType  = CONN_TYPE_CONNECT;
				managerModule = _AUDIO_GetManagerModule(left);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					connectModule.input_module	= right;
					connectModule.input_port	= MOD_IN_PORT(rightInPort);
					connectModule.output_module	= left;
					outPortSearchBase   = leftMOD->outPortSearchBase;

				if(leftMOD->hasMultiSink && leftMOD->hasIntra && rightMOD->needToConnectToIntra)
				{
					outPortSearchBase	 = 0;
					connectModule.output_port	= MOD_OUT_PORT((leftOutPort - outPortSearchBase));
				}
				//AUD_KDRV_RM("left hasMultiSink[%d] left hasIntra[%d] right needToConnectToIntra [%d] \n", leftMOD->hasMultiSink , leftMOD->hasIntra , rightMOD->needToConnectToIntra );
				else if(leftMOD->hasMultiSink)
				{
					connectModule.output_port	= MOD_OUT_PORT(0)+ (leftOutPort - outPortSearchBase);
				}
				else
				{
					connectModule.output_port	= MOD_OUT_PORT( (leftOutPort - outPortSearchBase) );
				}

					leftOut_15_8_RightIn_7_0 = connectModule.output_port << 8;


					if (AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, managerModule, sizeof(CmCmdConnect), &connectModule) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT) Error\n", __FUNCTION__, __LINE__);
					}
				}

				AUD_KDRV_RM("[%11s]       ----%s----      [%11s] CONNECT inM[%d] inP[%d] outM[%d] outP[%d] leftoutport:%d base:%d \n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],connectModule.input_module, connectModule.input_port ,connectModule.output_module , connectModule.output_port    , leftOutPort , outPortSearchBase);

			}
			else
			{

			}

		}
		else
		{
			AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
		}

		rightDEV->isFullyConnected = 1;
		AUD_KDRV_RMD("left head [%p] tail [%p]       ----------     right head [%p] tail[%p]\n",leftDEV->headOfDev,leftDEV->tailOfDev,rightDEV->headOfDev,rightDEV->tailOfDev);

		if( rightDEV->headOfDev == NULL && 	rightDEV->tailOfDev	== NULL )
		{
			rightDEV->headOfDev = (LX_AUD_ALLOC_FREE_INFO_T * )leftMOD;
			rightDEV->tailOfDev = (LX_AUD_ALLOC_FREE_INFO_T * )rightMOD;
			rightDEV->connectLength	=	2;
		}
		else if (rightDEV->headOfDev == (LX_AUD_ALLOC_FREE_INFO_T * )rightMOD )
		{
			rightDEV->headOfDev = (LX_AUD_ALLOC_FREE_INFO_T * )leftMOD;
			rightDEV->connectLength++;
		}
		else if (rightDEV->tailOfDev == (LX_AUD_ALLOC_FREE_INFO_T * )leftMOD )
		{
			rightDEV->tailOfDev = (LX_AUD_ALLOC_FREE_INFO_T * )rightMOD;
			rightDEV->connectLength++;
		}
		else
		{
			rightDEV->isFullyConnected = 0;
		}

		if ( rightDEV->headOfDev != NULL && rightDEV->tailOfDev	!= NULL )
			AUD_KDRV_RM("left head [%11s] tail [%11s]       ----------     right head [%11s] tail[%11s]\n",allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *) (leftDEV->headOfDev))->allocMod] ,allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *) (leftDEV->tailOfDev))->allocMod],allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *) (rightDEV->headOfDev))->allocMod],allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *) (rightDEV->tailOfDev))->allocMod]);
		else
			AUD_KDRV_RM("right head [%p] tail [%p]\n", rightDEV->headOfDev,rightDEV->tailOfDev);

	}
	else//no same device node : ex) connection betw decoder and renderer
	{
		AUD_KDRV_RM("#### CONNECTION BETWEEN DEVICES ####\n");

		if( leftDEV->isFullyConnected != 1  || rightDEV->isFullyConnected != 1 )
		{
			AUD_KDRV_RM("Need to Check Connection [%s] [%d] l%dr%d leftDEV head[%s] tail[%s] rightDEV head[%s] tail[%s] \n",__FUNCTION__,__LINE__,leftDEV->isFullyConnected, rightDEV->isFullyConnected ,
			allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *)(leftDEV->headOfDev))->allocMod],
			allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *)(leftDEV->tailOfDev))->allocMod],
			allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *)(rightDEV->headOfDev))->allocMod],
			allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T *)(rightDEV->tailOfDev))->allocMod]);


			return RET_ERROR;
		}

		if (  (leftDEV->connectStart == CONN_NONE  && rightDEV->connectStart == CONN_NONE) ||
			(leftDEV->connectStart == CONN_NONE  && rightDEV->connectStart == CONN_HEAD) ||
			(leftDEV->connectStart == CONN_NONE  && rightDEV->connectStart == CONN_MIDDLE && (((LX_AUD_ALLOC_FREE_INFO_T *)(leftDEV->headOfDev))->modType == LX_AUD_MPB )) ||
			(leftDEV->connectStart == CONN_HEAD  && rightDEV->connectStart == CONN_NONE) ||
			(leftDEV->connectStart == CONN_HEAD  && rightDEV->connectStart == CONN_HEAD)
		)
		{
			leftDEV->connectStart	= CONN_HEAD;
			((LX_AUD_ALLOC_FREE_INFO_T *  )(leftDEV->headOfDev))->connectStart = 1;
			((LX_AUD_ALLOC_FREE_INFO_T *  )(rightDEV->headOfDev))->connectStart = 0;
			rightDEV->connectStart	= CONN_MIDDLE;
		}
		else if (leftDEV->connectStart == CONN_MIDDLE  && rightDEV->connectStart == CONN_NONE)
		{
			((LX_AUD_ALLOC_FREE_INFO_T *  )(rightDEV->headOfDev))->connectStart = 0;
			rightDEV->connectStart	= CONN_MIDDLE;
		}
		else if (leftDEV->connectStart == CONN_MIDDLE  && rightDEV->connectStart == CONN_HEAD)
		{
			((LX_AUD_ALLOC_FREE_INFO_T *  )(rightDEV->headOfDev))->connectStart = 0;
			rightDEV->connectStart	= CONN_MIDDLE;
		}

		if( isRM_ModUsed  ==1 )
		{
			if( leftMOD->modType == LX_AUD_CPB  ||leftMOD->modType == LX_AUD_DPB  || leftMOD->modType ==LX_AUD_MPB  || leftMOD->modType == LX_AUD_IEC || leftMOD->modType == LX_AUD_CAPB)
			{
				switch(leftMOD->modType)
				{
					case LX_AUD_CPB:
					case LX_AUD_DPB:
					case LX_AUD_MPB:
					case LX_AUD_IEC:
					case LX_AUD_CAPB:

						pstBufIF = bufIF[  bufIF_TableLUT[ leftMOD->modType] ];
						buffIndex = leftMOD->allocMod - pstBufIF->bufIndexBase;
						pstBufIF = pstBufIF + buffIndex;
						leftMOD->connType  = ((UINT8 *)pstBufIF->pConTypeL)[ bufIF_TableLUT[ leftMOD->modType]];

						allocBuf.physical_addr =  pstBufIF->MemPhyBase;
						allocBuf.register_addr_offset	= pstBufIF->pRegBase - (void *)&g_pRealRegAud->aud_mem_share_base;
						//AUD_KDRV_RM("[%s] [%d] [%d] [%d [%x] [%x] [%x] b[%d]\n",__FUNCTION__,__LINE__, leftMOD->modType,bufIF_TableLUT[leftMOD->modType], pstBufIF->MemPhyBase, pstBufIF->pRegBase ,allocBuf.register_addr_offset ,buffIndex);
						break;
					default:
						break;

				}


				moduleToAllocBuf	=	right;
				allocBuf.module		= moduleToAllocBuf;
				allocBuf.port		= MOD_IN_PORT(rightInPort);
				allocBuf.is_reader	= TRUE;

				if( allocBuf.physical_addr  < pstMemCfgAud->start_memory_base  ||  allocBuf.physical_addr  > pstMemCfgAud->end_memory_base)
				{
					AUD_KDRV_ERROR("start[%8x] end[%8x] buf[%8x] idx[%d]\n",pstMemCfgAud->start_memory_base, pstMemCfgAud->end_memory_base, allocBuf.physical_addr, leftMOD->modType  );
					AUD_KDRV_ERROR("3[%11s]       ----%s----      [%11s] ALLOC moduleToAllocBuf:%d port:%d read:%d leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	,allocBuf.is_reader, leftOutPort , outPortSearchBase);
					return RET_ERROR;
				}

				leftOut_15_8_RightIn_7_0 = allocBuf.port;

				managerModule = _AUDIO_GetManagerModule(moduleToAllocBuf);
				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF, managerModule, sizeof(CmCmdAllocBuf), &allocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}
				AUD_KDRV_RM("[%11s]       ====%s====      [%11s] ALLOC moduleToAllocBuf:%d port:%d read:%d leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	,allocBuf.is_reader, leftOutPort , outPortSearchBase);
			}
			else if( rightMOD->modType == LX_AUD_CPB  ||rightMOD->modType == LX_AUD_DPB  || rightMOD->modType ==LX_AUD_MPB ||rightMOD->modType ==LX_AUD_IEC  ||rightMOD->modType ==LX_AUD_CAPB)
			{
				switch(rightMOD->modType)
				{
					case LX_AUD_CPB:
					case LX_AUD_DPB:
					case LX_AUD_MPB:
					case LX_AUD_IEC:
					case LX_AUD_CAPB:

						pstBufIF = bufIF[  bufIF_TableLUT[ rightMOD->modType] ];
						buffIndex = rightMOD->allocMod - pstBufIF->bufIndexBase;
						pstBufIF = pstBufIF + buffIndex;
						leftMOD->connType  = ((UINT8 *)pstBufIF->pConTypeR)[ bufIF_TableLUT[ rightMOD->modType]];

						allocBuf.physical_addr =  pstBufIF->MemPhyBase;
						allocBuf.register_addr_offset	= pstBufIF->pRegBase - (void *)&g_pRealRegAud->aud_mem_share_base;
						//AUD_KDRV_RM("[%s] [%d] [%d] [%d [%x] [%x] [%x] b[%d]\n",__FUNCTION__,__LINE__, rightMOD->modType,bufIF_TableLUT[rightMOD->modType], pstBufIF->MemPhyBase, pstBufIF->pRegBase ,allocBuf.register_addr_offset ,buffIndex);
						break;
					default:
						break;

				}

				moduleToAllocBuf	=	left;
				allocBuf.module		= moduleToAllocBuf;

				outPortSearchBase   = leftMOD->outPortSearchBase;

				if(leftMOD->hasMultiSink && leftMOD->hasIntra && rightMOD->needToConnectToIntra)
				{
					outPortSearchBase	 = 0;
					allocBuf.port		= MOD_OUT_PORT( (leftOutPort - outPortSearchBase));
				}
				//AUD_KDRV_RM("left hasMultiSink[%d] left hasIntra[%d] right needToConnectToIntra [%d] \n", leftMOD->hasMultiSink , leftMOD->hasIntra , rightMOD->needToConnectToIntra );
				else if(leftMOD->hasMultiSink)
				{
					allocBuf.port		= MOD_OUT_PORT( 0)+ (leftOutPort - outPortSearchBase);
				}
				else
				{
					allocBuf.port		= MOD_OUT_PORT( (leftOutPort - outPortSearchBase) );
				}


				leftOut_15_8_RightIn_7_0 = allocBuf.port;
				allocBuf.is_reader	= FALSE;

				if( allocBuf.physical_addr  < pstMemCfgAud->start_memory_base  ||  allocBuf.physical_addr  > pstMemCfgAud->end_memory_base)
				{
					AUD_KDRV_ERROR("start[%8x] end[%8x] buf[%8x] idx[%d]\n",pstMemCfgAud->start_memory_base, pstMemCfgAud->end_memory_base, allocBuf.physical_addr, rightMOD->modType  );
					AUD_KDRV_ERROR("4[%11s]       ----%s----      [%11s] ALLOC moduleToAllocBuf:%d port:%d read:%d leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	,allocBuf.is_reader, leftOutPort , outPortSearchBase);
					return RET_ERROR;
				}

				managerModule = _AUDIO_GetManagerModule(moduleToAllocBuf);
				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF, managerModule, sizeof(CmCmdAllocBuf), &allocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_ALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}
				AUD_KDRV_RM("[%11s]       ====%s====      [%11s] ALLOC moduleToAllocBuf:%d port:%d read:%d  leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],moduleToAllocBuf,allocBuf.port	,allocBuf.is_reader, leftOutPort , outPortSearchBase);

			}
			else
			{
				AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
			}

		}
		else if ( isRM_ModUsed  ==0)
		{
			//if(( leftManagerModule == rightManagerModule  && leftManagerModule != ADEC_MODULE_NOT_DEF ) && (leftMOD->modType  != LX_AUD_SRC1 ) && (rightMOD->modType  != LX_AUD_MIX ) )
			if(( leftManagerModule == rightManagerModule  && leftManagerModule != ADEC_MODULE_NOT_DEF )  )
			{

				leftMOD->connType  = CONN_TYPE_CONNECT;
				managerModule = _AUDIO_GetManagerModule(left);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					connectModule.input_module	= right;
					connectModule.input_port	= MOD_IN_PORT(rightInPort);
					connectModule.output_module	= left;

					outPortSearchBase   = leftMOD->outPortSearchBase;

					if(leftMOD->hasMultiSink && leftMOD->hasIntra && rightMOD->needToConnectToIntra)
					{
						outPortSearchBase	 = 0;
						connectModule.output_port	= MOD_OUT_PORT( (leftOutPort - outPortSearchBase));
					}
					//AUD_KDRV_RM("left hasMultiSink[%d] left hasIntra[%d] right needToConnectToIntra [%d] \n", leftMOD->hasMultiSink , leftMOD->hasIntra , rightMOD->needToConnectToIntra );
					else if(leftMOD->hasMultiSink)
					{

						connectModule.output_port	= MOD_OUT_PORT( 0)+ (leftOutPort - outPortSearchBase);
					}
					else
					{
						connectModule.output_port		= MOD_OUT_PORT( (leftOutPort - outPortSearchBase) );
					}
					leftOut_15_8_RightIn_7_0 =  ( connectModule.output_port << 8) |connectModule.input_port;


					if (AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, managerModule, sizeof(CmCmdConnect), &connectModule) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT) Error\n", __FUNCTION__, __LINE__);
					}

					// if right module is MASTER & input port is not 0, then send command (MIX_PORT_ENABLE) to MIX module
					// if ((right == ADEC_MODULE_MIX_0) && (rightInPort != 0))
					// if right module is MASTER (MIX_0), then send command (MIX_PORT_ENABLE) to MIX module
					if (right == ADEC_MODULE_MIX_0)
					{
						MixCmdEnablePort mixParam;

						mixParam.port = MOD_IN_PORT(rightInPort);
						mixParam.enable = 1;

						if (AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT, right, sizeof(MixCmdEnablePort), &mixParam) < 0)
						{
							AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT) Error\n", __FUNCTION__, __LINE__);
						}
					}
				}
				AUD_KDRV_RM(" [%11s]       ====%s====      [%11s] CONNECT inM[%d] inP[%d] outM[%d] outP[%d] leftoutport:%d base:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] , allocMod_Str[rightMOD->allocMod],connectModule.input_module, connectModule.input_port ,connectModule.output_module , connectModule.output_port , leftOutPort , outPortSearchBase);
			}
			else
			{

			}
		}
		else
		{
			AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
		}
	}

	AUD_KDRV_RMD( "leftout:%x  rightin%x\n",(leftOut_15_8_RightIn_7_0&0xff00)>>8,leftOut_15_8_RightIn_7_0&0xff);
	return leftOut_15_8_RightIn_7_0;
}

/**
 * Do Disconnection between modules thru IMC command Considering relation between modules
 *
 * @param 	left				[in] return of AUDIO_AllocModule, should be a module
 * @param 	right				[in] return of AUDIO_AllocModule, should be a module
 * @param 	forceLeftOutPort	[in] port num to disconnect  in forcing manager
 * @param 	foreceRightInPort	[in] port num to disconnect  in forcing manager
 * @return 	return leftOut_15_8_RightIn_7_0 [out] leftOutPort 15:8 bitfield rightInPort:7:0 bitfield
 * disconnection sequence  become : A - B
 * @see
 */

int  AUDIO_DisconnectTo ( UINT32 left, UINT32 right, UINT32 forceLeftOutPort, UINT32 foreceRightInPort)
{
	CmCmdDisconnect				disconnectParam;
	CmCmdDeallocBuf				deallocBuf;
	LX_AUD_ALLOC_FREE_INFO_T * leftMOD, * rightMOD, *leftDEV, *rightDEV, *leftHead, *rightTail;

	UINT32 	rightInPortToFree = PORT_NONE,leftOutPortToFree =PORT_NONE;
	UINT32	leftBelongTo,rightBelongTo,leftAvailablePortNum= 0,rightAvailablePortNum = 0;
	UINT32	leftSubBelongTo; // input module is always in left side
	UINT32 	i,IsForcePort = 0;
	UINT32	moduleToDeallocBuf;
	UINT32	managerModule;
	UINT32 	leftManagerModule,rightManagerModule;
	UINT32 	isRM_ModUsed = 0; // is included module defined only in resource mgr like EPB,CPB,DPB
	UINT32	outPortSearchBase	=	0;

	AUD_KDRV_RM("left[%s:%d] right[%s:%d] \n",allocMod_Str[left],left,allocMod_Str[right],right);

	if(right >= ADEC_MODULE_NO_MOD ||left >= ADEC_MODULE_NO_MOD )
	{
		AUD_KDRV_RM("Check Arg [%s] [%d] ADEC_MODULE_MOD_MAX[%d] \n",__FUNCTION__,__LINE__,ADEC_MODULE_MOD_MAX);
		return RET_ERROR;
	}

	if( forceLeftOutPort != NO_FORCE || foreceRightInPort != NO_FORCE )
	{
		IsForcePort = 1;
	}

	//leftMOD	= (LX_AUD_ALLOC_FREE_INFO_T *)&(ModInfo.devList[left]);
	leftMOD		= &ModInfo.list[left];
	rightMOD	= &ModInfo.list[right];

	leftBelongTo	= leftMOD->allocDev;
	rightBelongTo	= rightMOD->allocDev;
	leftSubBelongTo	= leftMOD->allocSubDev;
	leftDEV			=  &DevInfo.list[leftBelongTo];
	rightDEV		=  &DevInfo.list[rightBelongTo];


	//AUD_KDRV_RM(" leftMOD:%p rightMOD:%p leftBelongTo:%d rightBelongTo:%d leftDEV:%p rightDEV:%p \n",leftMOD,rightMOD,leftBelongTo,rightBelongTo, leftDEV,rightDEV);
	if ( left >= ADEC_MODULE_MAX || right >= ADEC_MODULE_MAX)
	{
		isRM_ModUsed = 1;
	}

	leftManagerModule = _AUDIO_GetManagerModule(left);
	rightManagerModule = _AUDIO_GetManagerModule(right);

	if(IsForcePort)
	{
		leftOutPortToFree 	=	forceLeftOutPort;
		rightInPortToFree	=	foreceRightInPort;
	}
	else
	{
		//find port to dealloc
		for ( i = 0 ; i < MAX_PORT; i++)
		{
			if( leftMOD->inOutMap[i].map.out  == right )
			{
				leftOutPortToFree = i;
				break;
			}
		}
		for ( i = 0 ; i < MAX_PORT; i++)
		{
			if( rightMOD->inOutMap[i].map.in  == left )
			{
				rightInPortToFree = i;
				break;
			}
		}
	}

	if(leftOutPortToFree == PORT_NONE || rightInPortToFree == PORT_NONE)
	{
		AUD_KDRV_RM("@@@@@ INVALID DISCONNECT TRIAL\n");

		//AUDIO_UpdateConnectionInfo();

		return RET_ERROR;
	}
	else
	{
		AUDIO_FreePort(leftMOD, OUT_PORT,leftOutPortToFree );
		AUDIO_FreePort(rightMOD, IN_PORT,rightInPortToFree );

		AUD_KDRV_RMD("leftOutPort[%s:%d] rightInPort[%s:%d] leftinpool[%llx] leftoutpool[%llx] rightinpool[%llx] rightoutpool[%llx]\n",allocMod_Str[left],leftOutPortToFree,allocMod_Str[right],rightInPortToFree,leftMOD->inPool,leftMOD->outPool,rightMOD->inPool,rightMOD->outPool);

		leftMOD->inOutMap[leftOutPortToFree].map.out	=	ADEC_MODULE_NO_MOD;
		rightMOD->inOutMap[rightInPortToFree].map.in	=	ADEC_MODULE_NO_MOD;

		leftMOD->out[leftOutPortToFree] 	=  NULL;
		rightMOD->in[rightInPortToFree]	= NULL;
	}

	leftAvailablePortNum  = AUDIO_GeAvailabletPortNum(leftMOD,OUT_PORT);
	rightAvailablePortNum  = AUDIO_GeAvailabletPortNum(rightMOD,IN_PORT);

	if(leftMOD->hasMultiSink &&  leftMOD->hasIntra  )
		leftAvailablePortNum  = leftAvailablePortNum +1;
	if(rightMOD->hasMultiSink &&  rightMOD->hasIntra  )
		rightAvailablePortNum  = rightAvailablePortNum +1;

	leftMOD->multiConnIdx = AUDIO_GeMultiConnectiionOutPortNum(leftMOD);

	AUD_KDRV_RMD("LM[%d] RM[%d]\n",leftMOD->multiConnIdx,rightMOD->multiConnIdx);
	//same device node
	// assume that input device is left
	if( leftBelongTo == rightBelongTo || leftSubBelongTo == rightBelongTo)
	{
		leftHead = leftMOD;
		rightTail	= rightMOD;

		if( isRM_ModUsed  ==1 )
		{
			if(leftMOD->modType == LX_AUD_CPB  ||leftMOD->modType == LX_AUD_DPB  || leftMOD->modType ==LX_AUD_MPB ||leftMOD->modType ==LX_AUD_IEC ||leftMOD->modType ==LX_AUD_CAPB)
			{

				if(leftMOD->modType == LX_AUD_CPB)
					leftMOD->connType  = CONN_TYPE_CPB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_DPB)
					leftMOD->connType  = CONN_TYPE_DPB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_MPB)
					leftMOD->connType  = CONN_TYPE_MPB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_IEC)
					leftMOD->connType  = CONN_TYPE_IECB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_CAPB)
					leftMOD->connType  = CONN_TYPE_CAPB_DALLOC_R;

				moduleToDeallocBuf	=	right;
				deallocBuf.module	= moduleToDeallocBuf;
				deallocBuf.port		= MOD_IN_PORT(rightInPortToFree);

				managerModule = _AUDIO_GetManagerModule(moduleToDeallocBuf);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF, managerModule, sizeof(CmCmdDeallocBuf), &deallocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}

				AUD_KDRV_RM(" [%11s]      ----%s----      [%11s] DEALLOC moduleToDeallocBuf:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] ,allocMod_Str[rightMOD->allocMod],moduleToDeallocBuf);
				leftMOD->connType  = CONN_TYPE_NONE;

			}

			else if( rightMOD->modType == LX_AUD_CPB  ||rightMOD->modType == LX_AUD_DPB  || rightMOD->modType ==LX_AUD_MPB ||rightMOD->modType ==LX_AUD_IEC ||rightMOD->modType ==LX_AUD_CAPB)
			{

				if(rightMOD->modType == LX_AUD_CPB)
					leftMOD->connType  = CONN_TYPE_CPB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_DPB)
					leftMOD->connType  = CONN_TYPE_DPB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_MPB)
					leftMOD->connType  = CONN_TYPE_MPB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_IEC)
					leftMOD->connType  = CONN_TYPE_IECB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_CAPB)
					leftMOD->connType  = CONN_TYPE_CAPB_DALLOC_L;



				moduleToDeallocBuf	=	left;
				deallocBuf.module	= moduleToDeallocBuf;

				outPortSearchBase   = leftMOD->outPortSearchBase;

				if(leftMOD->hasMultiSink && leftMOD->hasIntra && rightMOD->needToConnectToIntra)
				{
					outPortSearchBase	 = 0;
					deallocBuf.port		= MOD_OUT_PORT( (leftOutPortToFree - outPortSearchBase));
				}
				//AUD_KDRV_RM("left hasMultiSink[%d] left hasIntra[%d] right needToConnectToIntra [%d] \n", leftMOD->hasMultiSink , leftMOD->hasIntra , rightMOD->needToConnectToIntra );
				else if(leftMOD->hasMultiSink)
				{
					deallocBuf.port		= MOD_OUT_PORT(0)+ (leftOutPortToFree - outPortSearchBase);
				}
				else
				{
					deallocBuf.port		= MOD_OUT_PORT( (leftOutPortToFree - outPortSearchBase) );
				}

				managerModule = _AUDIO_GetManagerModule(moduleToDeallocBuf);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF, managerModule, sizeof(CmCmdDeallocBuf), &deallocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}

				AUD_KDRV_RM(" [%11s]      ----%s----      [%11s] DEALLOC moduleToDeallocBuf:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] ,allocMod_Str[rightMOD->allocMod],moduleToDeallocBuf);

				leftMOD->connType  = CONN_TYPE_NONE;
			}
			else
			{
				AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
			}

		}
		else if ( isRM_ModUsed  == 0 )
		{
			//if( leftManagerModule == rightManagerModule  && leftManagerModule != ADEC_MODULE_NOT_DEF  && (leftMOD->modType != LX_AUD_SRC1 && rightMOD->modType != LX_AUD_LIP))
			if (leftManagerModule == rightManagerModule && leftManagerModule != ADEC_MODULE_NOT_DEF)
			{
				leftMOD->connType  = CONN_TYPE_DISCONNECT;
				AUD_KDRV_RM(" [%11s]      ----%s----      [%11s]  DISCONNECT \n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] ,allocMod_Str[rightMOD->allocMod]) ;
				managerModule = _AUDIO_GetManagerModule(right);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					disconnectParam.module	= right;
					disconnectParam.port	= MOD_IN_PORT(rightInPortToFree);		// TODO: get port number from resource manager ???

					if (AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, TP_IN) Error\n", __FUNCTION__, __LINE__);
					}
				}
				leftMOD->connType  = CONN_TYPE_NONE;
			}
			else
			{

			}
		}
		else
		{
			AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
		}

		// it could be leftDEV or rightDEV becasue rightDEV is same as leftDEV
		if( rightDEV->isFullyConnected == 1 && rightDEV->ownNum > 2)
		{
			// it could be rightDEV or rightDEV becasue rightDEV is same as rightDEV
			if( ((LX_AUD_ALLOC_FREE_INFO_T *) rightDEV->headOfDev)->allocMod == left )
			{
				AUD_KDRV_RMD("[%s]'s HEAD is CHANGED [%s]-> [%s] \n",allocDev_Str[rightBelongTo], allocMod_Str[left],allocMod_Str[right]);
				rightDEV->headOfDev = rightMOD;
			}

			// it could be rightDEV or rightDEV becasue rightDEV is same as rightDEV
			if( ((LX_AUD_ALLOC_FREE_INFO_T *) rightDEV->tailOfDev)->allocMod == right )
			{
				AUD_KDRV_RMD("[%s]'s TAIL is CHANGED [%s]-> [%s] \n",allocDev_Str[rightBelongTo], allocMod_Str[right],allocMod_Str[left]);
				rightDEV->headOfDev = leftMOD;
			}

			AUD_KDRV_RMD(" 3 full %d own %d  head[%p] tail[%p] \n",rightDEV->isFullyConnected, rightDEV->ownNum , rightDEV->headOfDev,rightDEV->tailOfDev);
			//rightDEV->isFullyConnected = 0;
		}
		else if (rightDEV->isFullyConnected == 1 &&  rightDEV->ownNum == 2)
		{
			AUD_KDRV_RMD(" 4 full %d own %d  head[%p] tail[%p] \n",rightDEV->isFullyConnected, rightDEV->ownNum , rightDEV->headOfDev,rightDEV->tailOfDev);
			rightDEV->isFullyConnected = 0;
			rightDEV->headOfDev =NULL;
			rightDEV->tailOfDev =NULL;
		}
		else
		{
			AUD_KDRV_RMD(" 5 full %d own %d  head[%p] tail[%p] \n",rightDEV->isFullyConnected, rightDEV->ownNum , rightDEV->headOfDev,rightDEV->tailOfDev);
		}


	}
	else//no same device node : ex) connection betw decoder and renderer
	{
		AUD_KDRV_RM("#### DISCONNECTION BETWEEN DEVICES ####\n");

		if (
			(leftDEV->connectStart == CONN_HEAD  && rightDEV->connectStart == CONN_MIDDLE) &&(leftMOD->modType != LX_AUD_DEC && rightMOD->modType == LX_AUD_IEC  )
		)
		{
			leftDEV->connectStart	= CONN_NONE;

			((LX_AUD_ALLOC_FREE_INFO_T *  )(leftDEV->headOfDev))->connectStart = 0;
			((LX_AUD_ALLOC_FREE_INFO_T *  )(rightDEV->headOfDev))->connectStart = 1;

			rightDEV->connectStart	= CONN_HEAD;

		}


		if( isRM_ModUsed  ==1 )
		{
			if( leftMOD->modType == LX_AUD_CPB  ||leftMOD->modType == LX_AUD_DPB  || leftMOD->modType ==LX_AUD_MPB || leftMOD->modType ==LX_AUD_IEC || leftMOD->modType ==LX_AUD_CAPB)
			{

				if(leftMOD->modType == LX_AUD_CPB)
					leftMOD->connType  = CONN_TYPE_CPB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_DPB)
					leftMOD->connType  = CONN_TYPE_DPB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_MPB)
					leftMOD->connType  = CONN_TYPE_MPB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_IEC)
					leftMOD->connType  = CONN_TYPE_IECB_DALLOC_R;
				else if (leftMOD->modType == LX_AUD_CAPB)
					leftMOD->connType  = CONN_TYPE_CAPB_DALLOC_R;

				moduleToDeallocBuf	=	right;
				deallocBuf.module	= moduleToDeallocBuf;
				deallocBuf.port		= MOD_IN_PORT(rightInPortToFree);

				managerModule = _AUDIO_GetManagerModule(moduleToDeallocBuf);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF, managerModule, sizeof(CmCmdDeallocBuf), &deallocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}

				AUD_KDRV_RM(" [%11s]      ====%s====      [%11s] DEALLOC moduleToDeallocBuf:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] ,allocMod_Str[rightMOD->allocMod],moduleToDeallocBuf);

				leftMOD->connType  = CONN_TYPE_NONE;

			}
			else if ( rightMOD->modType == LX_AUD_CPB  ||rightMOD->modType == LX_AUD_DPB  || rightMOD->modType ==LX_AUD_MPB ||rightMOD->modType ==LX_AUD_IEC||rightMOD->modType ==LX_AUD_CAPB)
			{
				if(rightMOD->modType == LX_AUD_CPB)
					leftMOD->connType  = CONN_TYPE_CPB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_DPB)
					leftMOD->connType  = CONN_TYPE_DPB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_MPB)
					leftMOD->connType  = CONN_TYPE_MPB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_IEC)
					leftMOD->connType  = CONN_TYPE_IECB_DALLOC_L;
				else if (rightMOD->modType == LX_AUD_CAPB)
					leftMOD->connType  = CONN_TYPE_CAPB_DALLOC_L;


				moduleToDeallocBuf	=	left;
				deallocBuf.module	= moduleToDeallocBuf;

				outPortSearchBase   = leftMOD->outPortSearchBase;

				if(leftMOD->hasMultiSink && leftMOD->hasIntra && rightMOD->needToConnectToIntra)
				{
					outPortSearchBase	 = 0;
					deallocBuf.port		= MOD_OUT_PORT( (leftOutPortToFree - outPortSearchBase));
				}
				//AUD_KDRV_RM("left hasMultiSink[%d] left hasIntra[%d] right needToConnectToIntra [%d] \n", leftMOD->hasMultiSink , leftMOD->hasIntra , rightMOD->needToConnectToIntra );
				else if(leftMOD->hasMultiSink)
				{

					deallocBuf.port		= MOD_OUT_PORT (0) + (leftOutPortToFree - outPortSearchBase) ;
				}
				else
				{
					deallocBuf.port		= MOD_OUT_PORT( (leftOutPortToFree - outPortSearchBase) );
				}
				managerModule = _AUDIO_GetManagerModule(moduleToDeallocBuf);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{
					if (AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF, managerModule, sizeof(CmCmdDeallocBuf), &deallocBuf) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DEALLOC_BUF) Error\n", __FUNCTION__, __LINE__);
					}
				}

				AUD_KDRV_RM(" [%11s]      ====%s====      [%11s] DEALLOC moduleToDeallocBuf:%d\n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] ,allocMod_Str[rightMOD->allocMod],moduleToDeallocBuf);
				leftMOD->connType  = CONN_TYPE_NONE;

			}
			else
			{
				AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
			}

		}
		else if ( isRM_ModUsed  == 0 )
		{

			if( leftManagerModule == rightManagerModule  && leftManagerModule != ADEC_MODULE_NOT_DEF )
			{

				leftMOD->connType  = CONN_TYPE_DISCONNECT;
				AUD_KDRV_RM(" [%11s]      ====%s====      [%11s]  DISCONNECT \n",allocMod_Str[leftMOD->allocMod],conn_Str[leftMOD->connType] ,allocMod_Str[rightMOD->allocMod]) ;
				managerModule = _AUDIO_GetManagerModule(right);

				if (managerModule != ADEC_MODULE_NOT_DEF)
				{

					disconnectParam.module	= right;
					disconnectParam.port	= MOD_IN_PORT(rightInPortToFree);		// TODO: get port number from resource manager ???

					if (AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam) < 0)
					{
						AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, TP_IN) Error\n", __FUNCTION__, __LINE__);
					}
					leftMOD->connType  = CONN_TYPE_NONE;

					// if right module is MASTER & input port is not 0, then send command (MIX_PORT_ENABLE) to MIX module
					// if ((right == ADEC_MODULE_MIX_0) && (rightInPortToFree != 0))
					// if right module is MASTER (MIX_0), then send command (MIX_PORT_ENABLE) to MIX module
					if (right == ADEC_MODULE_MIX_0)
					{
						MixCmdEnablePort mixParam;

						mixParam.port = MOD_IN_PORT(rightInPortToFree);
						mixParam.enable = 0;

						if (AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT, right, sizeof(MixCmdEnablePort), &mixParam) < 0)
						{
							AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT) Error\n", __FUNCTION__, __LINE__);
						}
					}
				}
			}
			else
			{

			}

		}
		else
		{
			AUD_KDRV_RM("%s %d leftMOD[%s] rightMOD[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[leftMOD->allocMod],allocMod_Str[rightMOD->allocMod]) ;
		}

	}


	return RET_OK;
}


/**
 * Destroy Module
 *
 * @param 	left	[in] module to destory
 * @return 	if  succed-RET_OK , else -RET_ERROR .
 *  connection sequence  become : A - B
 * @see
 */

int  AUDIO_Destory ( UINT32 left )
{
	CmCmdDestroyModule			destroyModule;
	ADEC_MODULE_ID	moduleToDistory;
	ADEC_MODULE_ID	managerModule;
	LX_AUD_ALLOC_FREE_INFO_T * leftModList,* leftDevList,*leftHead;

	UINT32	leftBelongTo;

	AUD_KDRV_RM("left[%s:%d] \n",allocMod_Str[left],left);


	if(left >= ADEC_MODULE_MOD_MAX )
	{
		AUD_KDRV_RM("Check Arg [%s] [%d] ADEC_MODULE_MOD_MAX[%d] \n",__FUNCTION__,__LINE__,ADEC_MODULE_MOD_MAX);
		return RET_ERROR;
	}

	leftModList	= &ModInfo.list[left];
	leftBelongTo	= leftModList->allocDev;
	leftDevList	=  &DevInfo.list[leftBelongTo];

	AUD_KDRV_RM(" DESTORY TRIAL [%s]       XXXXX     LINE [%d] \n",allocMod_Str[leftModList->allocMod],__LINE__);

	//same device node
	leftHead = leftModList;

	if( (leftModList->modType == LX_AUD_DEC ) || (leftModList->modType == LX_AUD_ENC ) ||
		(leftModList->modType == LX_AUD_ADC_IN  ) ||(leftModList->modType == LX_AUD_HDMI_IN ) ||	(leftModList->modType == LX_AUD_SIF_IN  ) )
	{
		moduleToDistory= left;
		//AUD_KDRV_RM(" [%s]      - ---X----      [%s] moduleToDistory:%d\n",allocMod_Str[leftModList->allocMod],allocMod_Str[rightModList->allocMod],moduleToDistory);

		// Destory Decoder module
		managerModule = _AUDIO_GetManagerModule(moduleToDistory);
		if (managerModule != ADEC_MODULE_NOT_DEF)
		{
			destroyModule.module_id = moduleToDistory;
			if (AUDIO_IMC_SendCmdParam(CM_CMD_DESTROY_MODULE, managerModule, sizeof(CmCmdDestroyModule), &destroyModule) < 0)
			{
				AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(CM_CMD_DESTROY_MODULE, DEC) Error\n", __FUNCTION__, __LINE__);
			}
		}
	}
	else
	{
		AUD_KDRV_RM(" @@@@@ INVALID DISTORY TRIAL [%s]       XXXXXXXX     LINE [%d] \n",allocMod_Str[leftModList->allocMod],__LINE__);
	}






	return RET_OK;
}




/**
 * Get Available Port of given module
 *
 * @param 	pMod		[in] pointer of module info struction
 * @param 	inOut		[in] port type to alloce
 * @param 	useMultiSink 	[out] whether need to use multiSink port or not
 * outpool:  0~7 intra port, multisink port used   bit  8~15 : multi sink port used  bit
 * useMultiSink: 1  mean      left out port using MultiSink pool
 * useMultiSink: 0  mean      left out port not using MultiSink pool  or  right in port

 * @return 	if  succed-RET_OK , else - .
 * @see
 */
int AUDIO_GetPort( LX_AUD_ALLOC_FREE_INFO_T * pMod , UINT32 inOut, UINT8 useMultiSink)
{
	UINT32 availablePort =0, i;
	UINT64 tempPool;

	if(inOut == OUT_PORT)
	{
		if(useMultiSink)
		{
			tempPool = pMod->outPool>>MULTISINKBASE;
			//for(i =0, availablePort = 0 ; i< pMod-> 	; i++)
			for(i =MULTISINKBASE, availablePort = 0 ; i< MAX_PORT	; i++)
			{
				if( (tempPool) & 0x1)
				{

					AUD_KDRV_RMD("out1 B %llx %d MP[%d]\n",pMod->outPool , availablePort,pMod->multiSinkPortNum);
					availablePort = i;
	 				pMod->outPool = (pMod->outPool &( ~(0x1<<i)))&0xffffffff; //check alloced port mak as a 0

					if( pMod->multiSinkPortNum != HAS_NOT_MULTISINK_PORT && pMod->hasIntra &&( ( pMod->outPool & ( 1<< (pMod->multiSinkPortNum)) ) == 1)) // mark used bit 0~7 range bit as a multisink used port  if multisink used is not marked in range of 0~7 bit
					{
						AUD_KDRV_RMD("true[%11s] here outPool[%llx] [%d] \n",allocMod_Str[pMod->allocMod], pMod->outPool, pMod->multiSinkPortNum);
						pMod->outPool = (pMod->outPool &( ~(0x1<<(pMod->multiSinkPortNum))))&0xffffffff;
						pMod->inOutMap[pMod->multiSinkPortNum].map.out = USED_PORT;
						AUD_KDRV_RMD("here outPool[%llx] [%d] \n", pMod->outPool, pMod->multiSinkPortNum);
					}
					else
					{
						AUD_KDRV_RMD("false[%11s] here outPool[%llx] [%d] \n",allocMod_Str[pMod->allocMod] ,pMod->outPool, pMod->multiSinkPortNum);
					}

					AUD_KDRV_RMD("out1 A %llx %d MP[%d]\n",pMod->outPool,availablePort ,pMod->multiSinkPortNum);
					break;
				}
				else
				{
					tempPool = tempPool>> 1;
					tempPool = tempPool&( ~0xffffffff00000000); // assume that max port is less than 8

					AUD_KDRV_RMD("out2 %llx %d\n",tempPool,availablePort );

					if( i == MAX_PORT -1 )
					{
						availablePort= PORT_FULL;
						AUD_KDRV_RMD("PORT FULL");
					}
				}
			}
		}
		else
		{
			tempPool = pMod->outPool;
			//for(i =0, availablePort = 0 ; i< pMod->outNum	; i++)
			for(i =0, availablePort = 0 ; i< MAX_PORT	; i++)
			{
				if( (tempPool) & 0x1)
				{
					AUD_KDRV_RMD("out1 B %llx %d\n",pMod->outPool , availablePort);
					availablePort = i;
	 				pMod->outPool = (pMod->outPool &( ~(1<<i)))&0xffffffff; //check alloced port mak as a 0

					AUD_KDRV_RMD("out1 A %llx %d\n",pMod->outPool,availablePort );
					break;
				}
				else
				{
					tempPool = tempPool>> 1;
					tempPool = tempPool&( ~0xffffffff00000000); // assume that max port is less than 8

					AUD_KDRV_RMD("out2 %llx %d\n",tempPool,availablePort );

					if( i == MAX_PORT -1 )
					{
						availablePort= PORT_FULL;
						AUD_KDRV_RMD("PORT FULL");
					}
				}
			}
		}
	}
	else if (inOut == IN_PORT)
	{
		tempPool = pMod->inPool;
		//for(i =0, availablePort = 0 ; i< pMod->inNum	; i++)
		for(i =0, availablePort = 0 ; i< MAX_PORT	; i++)
		{
			if( (tempPool) & 0x1)
			{
				AUD_KDRV_RMD("in 1 B %llx %d\n",pMod->inPool,availablePort );
				availablePort = i;
				pMod->inPool = (pMod->inPool &( ~(1<<i)))&0xffffffff;
				AUD_KDRV_RMD("in 1 A %llx %d\n",pMod->inPool,availablePort );
				break;
			}
			else
			{
				tempPool = tempPool>> 1;
				tempPool = tempPool&( ~0xffffffff00000000); // assume that max port is less than 8
				AUD_KDRV_RMD("in 2  %llx %d\n",pMod->inPool, availablePort );
				if( i == MAX_PORT -1 )
				{
					availablePort= PORT_FULL;
					AUD_KDRV_RMD("PORT FULL");
				}
			}
		}
	}
	return availablePort;
}

/**
 * Get Available Port Num of given module
 *
 * @param 	pMod [in] pointer of module info struction
 * @param 	inOut [in] port type
 * @return 	if  succed-RET_OK , else - .
 * @see
 */
int AUDIO_GeAvailabletPortNum( LX_AUD_ALLOC_FREE_INFO_T * pMod , UINT32 inOut)
{
	UINT32 availablePort =0, i;
	UINT64 tempPool;

	if(inOut == OUT_PORT)
	{
		tempPool = pMod->outPool;
		for(i =0, availablePort = 0 ; i< MAX_PORT	; i++)
		{
			if( (tempPool) & 0x1)
			{
				availablePort ++;
			}
			tempPool = tempPool>> 1;
			tempPool = tempPool&( ~0xffffffff00000000);
		}
	}
	else if (inOut == IN_PORT)
	{
		tempPool = pMod->inPool;
		for(i =0, availablePort = 0 ; i< MAX_PORT	; i++)
		{
			if( (tempPool) & 0x1)
			{
				availablePort ++;
			}
			tempPool = tempPool>> 1;
			tempPool = tempPool&( ~0xffffffff00000000);

		}
	}
	return availablePort;
}


/**
 * Get MultiConnnection out Port Num of given module
 *
 * @param 	pMod [in] pointer of module info struction
 * @param 	inOut [in] port type
 * @return 	if  succed-RET_OK , else - .
 * @see
 */
int AUDIO_GeMultiConnectiionOutPortNum( LX_AUD_ALLOC_FREE_INFO_T * pMod)
{
	UINT32 multiConOutPort =0, i, tempPool = 0;

	tempPool = pMod->outPool;
	for(i =0; i< MULTISINKBASE	; i++)
	{
		if( (tempPool) & 0x1)
		{

		}
		else
		{
			if( ( pMod->inOutMap[i].map.out != USED_PORT ) && ( pMod->inOutMap[i].map.out != ADEC_MODULE_NO_MOD ) )
			{
				multiConOutPort ++;
				AUD_KDRV_RM("@ [%d]\n",pMod->inOutMap[i].map.out );
			}
		}
		tempPool = tempPool>> 1;
		tempPool = tempPool&( ~0xffff0000);
	}

	for(i =MULTISINKBASE; i< MAX_PORT	; i++)
	{
		if(( pMod->inOutMap[i].map.out != ADEC_MODULE_NO_MOD ))
		{
			multiConOutPort ++;
			AUD_KDRV_RM("^^ [%d] \n",pMod->inOutMap[i].map.out);
		}
	}

	return multiConOutPort;
}


/**
 * Free Port of given Module
 *
 * @param 	pMod 			[in] pointer of module info struction
 * @param 	inOut 			[in] port type
 * @param 	portNumToFree 	[in] port num to free
 * @return 	if  succed-RET_OK , else - .
 * @see
 */
int AUDIO_FreePort( LX_AUD_ALLOC_FREE_INFO_T * pMod , UINT32 inOut, UINT32 portNumToFree)
{
	if(inOut == OUT_PORT && portNumToFree < MULTISINKBASE)
	{

		pMod->outPool = pMod->outPool | 1<< portNumToFree;
		AUD_KDRV_RMD("intra [%11s] [%llxx] portnum[%d]\n",allocMod_Str[pMod->allocMod],pMod->outPool, portNumToFree );
	}
	else if(inOut == OUT_PORT &&  portNumToFree >= MULTISINKBASE && pMod->multiSinkPortNum != HAS_NOT_MULTISINK_PORT)
	{

		pMod->outPool = pMod->outPool | 1<< portNumToFree;
		pMod->outPool = pMod->outPool | 1<< pMod->multiSinkPortNum;
		AUD_KDRV_RMD("multisink [%11s] [%llxx] portnum[%d]\n",allocMod_Str[pMod->allocMod],pMod->outPool, portNumToFree );
	}
	else if (inOut == IN_PORT)
	{
		pMod->inPool = pMod->inPool | 1<< portNumToFree;
	}

	return RET_OK;
}

/**
 * Get Pointer of Device information
 *
 * @param 	alloc 	[in] alloc device
 * @return 	if  succed-pointer of device information  sturct , else - .
 * @see
 */
LX_AUD_ALLOC_FREE_INFO_T * AUDIO_GetAllocDevInfo( LX_AUD_ALLOC_DEV_T alloc)
{
	LX_AUD_ALLOC_FREE_INFO_T * allocDEV;

	if ( alloc < AUD_DEV_DEC0 || alloc >= AUD_DEV_MAX)
	{
		//AUD_KDRV_ERROR("[%s][%d] Check Arg\n",__FUNCTION__,__LINE__);
		return NULL;
	}

	allocDEV = &DevInfo.list[alloc];
	return allocDEV;
}
/**
 * Get Pointer of Moudle information
 *
 * @param 	alloc 	[in] alloc module
 * @return 	if  succed-pointer of module information  sturct , else - .

 * @see
 */
LX_AUD_ALLOC_FREE_INFO_T * AUDIO_GetAllocModInfo( LX_AUD_ALLOC_MOD_T alloc)
{
	LX_AUD_ALLOC_FREE_INFO_T * allocMOD;
	if ( alloc < 0 || alloc >= ADEC_MODULE_MOD_MAX)
	{
		AUD_KDRV_ERROR("[%s][%d] Check Arg\n",__FUNCTION__,__LINE__);
		return NULL;
	}
	allocMOD = &ModInfo.list[alloc];
	return allocMOD;
}


LX_AUD_ALLOC_FREE_INFO_T * AUDIO_GetDev(	LX_AUD_DEV_TYPE_T devType,  LX_AUD_SUB_MOD_T wantedSubModule)
{

	UINT32	devToFind = AUD_NO_DEV;
	UINT32	searchStart,searchEnd;
	UINT32	availbleNum,allocBase,allocCnt;

	LX_AUD_ALLOC_FREE_INFO_T * allocDEV;

	devType = devType;

	allocCnt 		= DevInfo.allocCnt[devType];
	availbleNum 	= DevInfo.availableNum[devType];
	allocBase 	= DevInfo.allocBase[devType];

	AUD_KDRV_RM("AUDIO_GetDev devType[%s] [availbleNum:%d][allocCnt:%d][allocBase:%d]\n",devTypeStr[devType], availbleNum, allocCnt , allocBase);

	searchStart 	= allocBase ;
	searchEnd 	= searchStart + availbleNum ;

	for( devToFind = searchStart ; devToFind < searchEnd ; devToFind++ )
	{
		switch (wantedSubModule)
		{
			case IEC_BUFF:
				if(DevInfo.list[devToFind].hasIECBuff == 1)
				{
					goto finddev;
				}
				break;
			case IEC_LIP:
				if(DevInfo.list[devToFind].hasIECLIP == 1)
				{
					goto finddev;
				}
				break;
			default:
				AUD_KDRV_RM(" No wanded Sub Module  \n");
				return ((void *)0);
				break;
		}

	}

finddev:
	AUD_KDRV_RMD(" searchStart[%d] searchEnd[%d] finded Dev:%s[%d] \n",searchStart,searchEnd,allocDev_Str[devToFind],devToFind);
	allocDEV = &DevInfo.list[devToFind];
	return allocDEV;
}

/**
 * Get Core of Given Module
 *
 * @param 	audioModule 	[in] alloc module
  * @return 	if  succed- Core(manager)   , else - .
 * @see
 */
ADEC_MODULE_ID _AUDIO_GetManagerModule(ADEC_MODULE_ID audioModule)
{
	ADEC_MODULE_ID		managerModule;
	ADEC_CORE_TYPE		coreOfModule = ModuleList_FindModule(audioModule);

	switch (coreOfModule)
	{
		case ADEC_CORE_ARM:
			managerModule = ADEC_MODULE_MAN_ARM;
			break;
		case ADEC_CORE_DSP0:
			managerModule = ADEC_MODULE_MAN_DSP0;
			break;
		case ADEC_CORE_DSP1:
			managerModule = ADEC_MODULE_MAN_DSP1;
			break;
		default:
			managerModule = ADEC_MODULE_NOT_DEF;
			break;
	}
	AUD_KDRV_PRINT("audio manger module is %d\n", managerModule);

	return managerModule;
}


/**
 * Set Bypass Module Configuration
 *
 * @param 	allocMod_Bypass	[in] alloc bypass module
 * @param 	mode 			[in] 0 - Byte Based Mode , 1 - AU Based Mode
 * @param 	over_protect 		[in] 0 - No Overflow Protection, 1 - Enable Overflow Protection
 * @return 	if  succed- RET_OK  , else - .
 * @see
 */
int AUDIO_SetBypassMode( UINT32 allocMod_Bypass, UINT32 mode , UINT32 over_protect )
{
	BypassCmdSetMode	bypassMode;

	if(allocMod_Bypass >= ADEC_MODULE_MOD_MAX)
	{
		AUD_KDRV_RM("Check Arg [%s] [%d] MOD[%d: MAX:%d] \n",__FUNCTION__,__LINE__,allocMod_Bypass,ADEC_MODULE_MOD_MAX);
		return RET_ERROR;
	}

	bypassMode.mode				= mode ;
	bypassMode.over_protect		= over_protect;

	if (AUDIO_IMC_SendCmdParam(BYPASS_CMD_SET_MODE, allocMod_Bypass, sizeof(BypassCmdSetMode), &bypassMode) < 0)
	{
		AUD_KDRV_ERROR("%s.%d: AUDIO_IMC_SendCmdParam(BYPASS_CMD_SET_MODE mod[%s]) Error\n",__FUNCTION__, __LINE__, allocMod_Str[allocMod_Bypass]);
		return RET_ERROR;
	}

	AUD_KDRV_RM("%s.%d: AUDIO_IMC_SendCmdParam(BYPASS_CMD_SET_MODE mod[%s] [%d:%d] ) \n",__FUNCTION__, __LINE__, allocMod_Str[allocMod_Bypass],mode,over_protect);
	return RET_OK;
}


/**
 * Disconnect All Connecitoin Between Modules Possed By Given Module
 *
 * @param 	allocDev 	[in] alloc device
 * @return 	if  succed- RET_OK  , else - .
 * @see
 */
int  AUDIO_DisconnectAllInDev ( UINT32 allocDev)
{
	LX_AUD_ALLOC_FREE_INFO_T *allocDEV,*leftMOD;
	LX_AUD_MOD_T	*pOwnMods = NULL;
	SINT32				retVal = RET_ERROR;
	UINT32			allocModNum = 0;
	UINT32 i, left=ADEC_MODULE_NO_MOD, right=ADEC_MODULE_NO_MOD;
	UINT32 decMod	=ADEC_MODULE_NO_MOD, inputMod	=ADEC_MODULE_NO_MOD;
	UINT32	outPortSearchBase	=	0;

	if(allocDev >= AUD_DEV_MAX )
	{
		AUD_KDRV_ERROR("Check Arg [%s] [%d] \n",__FUNCTION__,__LINE__);
		return RET_ERROR;
	}

	AUDIO_GetAllocInfo( allocDev, &allocModNum , &pOwnMods);
	allocDEV = AUDIO_GetAllocDevInfo(allocDev);

	if( allocDEV == NULL )
	{
		AUD_KDRV_DEBUG(" Check allocDEV[%p] \n",allocDEV);
		return RET_ERROR	;
	}

	if( allocDEV->headOfDev == NULL )
	{
		AUD_KDRV_ERROR("Device[%s] own[%d] full[%d]  [%s] [%d] \n",allocDev_Str[allocDev],allocDEV->ownNum,allocDEV->isFullyConnected,__FUNCTION__,__LINE__);
		return RET_ERROR;
	}

	left =	((LX_AUD_ALLOC_FREE_INFO_T *) (allocDEV->headOfDev))->allocMod;
	leftMOD = AUDIO_GetAllocModInfo(left);

	if( leftMOD == NULL )
	{
		AUD_KDRV_ERROR(" Check leftMOD[%p] \n",leftMOD);
		return RET_ERROR	;
	}

	if (leftMOD->hasMultiSink)
		outPortSearchBase = MULTISINKBASE;
	else
		outPortSearchBase = 0;

		inputMod = left;

		if(inputMod  >= (UINT32)ADEC_MODULE_TP_IN_0 && inputMod  <= (UINT32)ADEC_MODULE_ADC_IN)
		{
			decMod = AUDIO_HasThisModuleType (  allocDev ,  LX_AUD_DEC );

			if(decMod != ADEC_MODULE_NO_MOD)
			{
				outPortSearchBase = AUDIO_GetConnectedPort(inputMod,decMod);

				if (outPortSearchBase == PORT_NONE)
				{
					AUD_KDRV_ERROR("  inoutMod[%s]'s Wrong PortNum[%d] decMod[%s]  \n",allocMod_Str[inputMod],outPortSearchBase,allocMod_Str[decMod]);
					return RET_ERROR;
				}
			}
		}
	//AUDIO_ForceDisconnectRemainedBetweenDEVs(left,CHECK_IN_PORT);

	if (allocModNum > 2 && allocDEV->isFullyConnected == 1 )
	{

		for(i = 0; i < allocModNum; i++)
		{

			if(  leftMOD->inOutMap[outPortSearchBase].map.out != ADEC_MODULE_NO_MOD)
			{
				right= leftMOD->inOutMap[outPortSearchBase].map.out;
				AUD_KDRV_RMD("[%s] [%d] right[%s] \n",__FUNCTION__,__LINE__,allocMod_Str[right]);

				AUDIO_DisconnectTo(left,right , NO_FORCE, NO_FORCE );
			}
			else
			{
				AUD_KDRV_RMD("No more Connection[%s] [%d] right[%s]\n",__FUNCTION__,__LINE__,allocMod_Str[right]);
			}

			//find next Disconnection
			left = right;
			leftMOD = AUDIO_GetAllocModInfo(left);

			if ( leftMOD == NULL)
			{
				AUD_KDRV_ERROR("Check ARG leftMOD[%p] \n", leftMOD);
				return RET_ERROR;
			}

			if (leftMOD->hasMultiSink)
				outPortSearchBase = MULTISINKBASE;
			else
				outPortSearchBase = 0;

			retVal = RET_OK;

		}

		//AUDIO_ForceDisconnectRemainedBetweenDEVs(right,CHECK_OUT_PORT);
	}
	else if (allocModNum == 2 && allocDEV->isFullyConnected == 1 )
	{

		right =	((LX_AUD_ALLOC_FREE_INFO_T *) (allocDEV->tailOfDev))->allocMod;
		AUDIO_DisconnectTo(left,right, NO_FORCE, NO_FORCE );
		//AUDIO_ForceDisconnectRemainedBetweenDEVs(right,CHECK_OUT_PORT);
		retVal = RET_OK;

	}
	else
	{
			//AUDIO_UpdateConnectionInfo();
			AUD_KDRV_RM("@@@@@ INVALID DISTCONNECT TRIAL[%s] [%d] allocModNum[%d]isFullyConnected[%d] allocDev[%s]  \n",__FUNCTION__,__LINE__,allocModNum,allocDEV->isFullyConnected ,allocDev_Str[allocDev]);
	}
	return retVal;
}


/**
 * Disconnect All Connecitoin Remained Even After Closing device
 *
 * @param 	checkModule			[in] module to be checked
  * @param 	inOutExtraConnection	[in] 0: inport check 1: outport check
 * checkModule	: module to be checked
 *  not used
 * @return 	if  succed- RET_OK  , else - .
 * @see
 */


int  AUDIO_ForceDisconnectRemainedBetweenDEVs( LX_AUD_ALLOC_MOD_T checkMod, UINT32 inOutExtraConnection)
{
	UINT32 i, left=ADEC_MODULE_NO_MOD, right=ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_FREE_INFO_T * checkMOD;
	checkMOD = &ModInfo.list[checkMod];

	if ( inOutExtraConnection == CHECK_IN_PORT)
	{
		for(i = 0; i < MAX_PORT; i++)
		{
			// if there is connection info exist in in port
			if(  checkMOD->inOutMap[i].map.in != ADEC_MODULE_NO_MOD)
			{
				left= checkMOD->inOutMap[i].map.in;
				right = (UINT32)checkMod;

				AUD_KDRV_RM("force disconnection: in port  [%s] [%d] left[%s] right[%s] \n",__FUNCTION__,__LINE__,allocMod_Str[left],allocMod_Str[right]);

				AUDIO_DisconnectTo(left,right , NO_FORCE, NO_FORCE );
			}
		}
	}
	else if ( inOutExtraConnection == CHECK_OUT_PORT)
	{
		for(i = 0; i < MAX_PORT; i++)
		{
			// if there is connection info exist in in port
			if(  checkMOD->inOutMap[i].map.out != ADEC_MODULE_NO_MOD)
			{
				left =  (UINT32)checkMod;
				right = checkMOD->inOutMap[i].map.out;

				AUD_KDRV_RM("force disconnection: out port  [%s] [%d] left[%s] right[%s] \n",__FUNCTION__,__LINE__,allocMod_Str[left],allocMod_Str[right]);

				AUDIO_DisconnectTo(left,right , NO_FORCE, NO_FORCE );
			}
		}
	}

	return RET_OK;
}


/**
 * Find Module Existing in Pre or Post Possion of Given Module
 *
 * @param 	checkMod 			[in] alloc module

 * @param 	inOutExtraConnection 	[in] search direction
 * @return 	if  succed- RET_OK  , else - .
 * @see
 */

LX_AUD_ALLOC_MOD_T  AUDIO_GetInOutModOfThisModule( LX_AUD_ALLOC_MOD_T checkMod, UINT32 inOutExtraConnection)
{
	UINT32 i,ValidConnection = 0 ,InOutMod=ADEC_MODULE_NO_MOD;

	LX_AUD_ALLOC_FREE_INFO_T * checkMOD;
	checkMOD = &ModInfo.list[checkMod];

	if ( inOutExtraConnection == CHECK_IN_PORT)
	{
		for(i = 0; i < MAX_PORT; i++)
		{
			// if there is connection info exist in in port
			if(  checkMOD->inOutMap[i].map.in != ADEC_MODULE_NO_MOD)
			{
				InOutMod= checkMOD->inOutMap[i].map.in;
				ValidConnection ++;
			}
		}
	}

	else if ( inOutExtraConnection == CHECK_OUT_PORT)
	{
		for(i = 0; i < MAX_PORT; i++)
		{
			// if there is connection info exist in in port
			if(  checkMOD->inOutMap[i].map.out != ADEC_MODULE_NO_MOD)
			{
				InOutMod= checkMOD->inOutMap[i].map.out;
				ValidConnection ++;
			}
		}
	}

	if (ValidConnection == 1)
		return InOutMod;
	else
	{
		InOutMod=ADEC_MODULE_NO_MOD;
		return InOutMod;
	}
}


int	KDRV_AUDIO_ResetManagerParam( void)
{
	LX_AUD_ALLOC_FREE_INFO_T * MOD;

	MOD	= AUDIO_GetAllocModInfo(ADEC_MODULE_MIX_0) ;

	AUD_KDRV_RM("MOD->outPool[%llx] \n", MOD->outPool);
	/* make this port as used port */
	MOD->outPool	=		MOD->outPool   &	(~(( LX_AUD_OUTPUT_HP|LX_AUD_OUTPUT_SCART|LX_AUD_OUTPUT_SPDIF )<< MULTISINKBASE));
	AUD_KDRV_RM("MOD->outPool[%llx] \n", MOD->outPool);
	MOD->out[MULTISINKBASE + LX_AUD_OUTPUT_HP_B		] =	AUDIO_GetAllocModInfo(ADEC_MODULE_OUT_CTRL_1) ;
	MOD->out[MULTISINKBASE + LX_AUD_OUTPUT_SCART_B	] =	AUDIO_GetAllocModInfo(ADEC_MODULE_OUT_CTRL_2) ;
	MOD->out[MULTISINKBASE + LX_AUD_OUTPUT_SPDIF_B	] =	AUDIO_GetAllocModInfo(ADEC_MODULE_OUT_CTRL_3) ;


	MOD->inOutMap[MULTISINKBASE + LX_AUD_OUTPUT_HP_B		].map.out =	USED_PORT;
	MOD->inOutMap[MULTISINKBASE + LX_AUD_OUTPUT_SCART_B		].map.out =	USED_PORT;
	MOD->inOutMap[MULTISINKBASE + LX_AUD_OUTPUT_SPDIF_B		].map.out =	USED_PORT;

	return RET_OK;
}



