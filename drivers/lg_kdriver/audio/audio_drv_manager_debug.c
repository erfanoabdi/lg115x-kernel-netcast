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



#include "os_util.h"
#include "base_device.h"

#include "debug_util.h"
#include "audio_cfg.h"
#include "audio_drv.h"
#include "audio_reg.h"

#include "common/adec_config.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

#define NORMAL_FINDING		1		// single connection case
#define ADDITIONAL_FINDING	2		// multiple connection case


#define NO_MODULE_LEFT		0

#define NOT_CLASSIFIED		0

#define RM_MODULE_NUM		5
#define MOD_STATE_MAX		7
#define FINDMOD_STATE_MAX   4
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
extern UINT8 * devTypeStr[LX_AUD_DEV_TYPE_MAX+1];
extern UINT8 *  allocMod_Str [ADEC_MODULE_MOD_MAX+1];
extern LX_AUD_MOD_INFO_T ModInfo;
extern LX_AUD_DEV_INFO_T DevInfo;
extern UINT8 *  allocDev_Str [AUD_DEV_MAX+1] ;
extern UINT8 *  conn_Str[CONN_TYPE_MAX];


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

UINT8 * findStatusS[FINDMOD_STATE_MAX]=
{
	"NO_MOD",
	"NORMAL",
	"ADDIT_",
	"MULTI_",
};

UINT8 *  modStatusStr [MOD_STATE_MAX] = // device node(D) and module(M)
{
    "NONE",
    "INIT ",		//56
    "START",		//56
    "STOP",
    "FLUSH",
    "MULTI",
    "ALLOC",
};
//need to sync with device num ,extra manager module


LX_AUD_CON_T GCon[TCON_NUM];// connection


/**
 * Show Connection Information Between module
 *
 * @param 	: None
 * @return 	if  succed-RET_OK , else - .
 * @see
 */

UINT32 AUDIO_FindConnectedModule(UINT32 *pNextMod, UINT32 outPortSearchBase, UINT32 *pConNum,UINT32 *pSubConNum, UINT32 multiConPrintPosition, UINT32 findType  )
{

	UINT32 nextMod ;

	UINT32 nextModConnection = 0 ;
	UINT32	isExistNextMod = 0;
	LX_AUD_ALLOC_FREE_INFO_T * nextMOD;

	AUD_KDRV_RM("=====\n");
	AUD_KDRV_RM("A MOD[%9s:%2d]port[%d]y[%d]x[%d]\n",allocMod_Str[*pNextMod],*pNextMod,outPortSearchBase,*pConNum ,*pSubConNum );
	// get info of nextMod
	nextMOD 	= (LX_AUD_ALLOC_FREE_INFO_T * )ModInfo.list[*pNextMod].out[outPortSearchBase];
	nextMod 	= nextMOD->allocMod;

	AUD_KDRV_RM("=>[%s]x[%d]y[%d]ct[%d]\n", allocMod_Str[nextMOD->allocMod],*pConNum ,*pSubConNum,nextMOD->connType );

	GCon[*pConNum].subCon[*pSubConNum] 		= nextMOD->allocMod ;
	GCon[*pConNum].subConStr[*pSubConNum] 	= nextMOD->allocStr;
	GCon[*pConNum].subConType[*pSubConNum]	= nextMOD->connType;
	nextModConnection	= AUDIO_GetMultiOutConnIdx(nextMOD);

	if( nextModConnection >= 1)
		isExistNextMod = 1;
	else
		isExistNextMod = 0;

	*pNextMod = nextMOD->allocMod;

	//inclease y index in GCon matrix for GCon Matrix display
	(*pSubConNum)++;

	AUD_KDRV_RM("=>B MOD[%9s:%9s]y[%d]x[%d]f[%d]isN[%d]CON[%d]\n", allocMod_Str[nextMOD->allocMod],allocMod_Str[*pNextMod],*pConNum ,*pSubConNum,findType ,isExistNextMod,nextModConnection);

	return isExistNextMod;

}

int AUDIO_GetMultiOutConnIdx( LX_AUD_ALLOC_FREE_INFO_T * pMod)
{
	UINT32 connIdx=0, i;

	for( i = 0; i < MAX_PORT ; i++)
	{
		if(  pMod->out[i] != NULL)
		{
			connIdx ++;
		}
	}
	return connIdx;
}
/**
 * Show alloc information of Device and Module
 *
 * @param 	: none
 * @return 	if succeeded -RET_OK , else - .
 * @see
 */

void  AUDIO_UpdateAllocInfo (void )
{
	int i,j;

	LX_AUD_MOD_TYPE_T modType = LX_AUD_MAN_ARM;
	LX_AUD_DEV_TYPE_T devType = LX_AUD_DEV_DEC;
	LX_AUD_ALLOC_FREE_INFO_T * MOD, * DEV;

	UINT32	searchStart;
	UINT32	availbleNum, allocBase;


	char		strsum[25];
	char		tstrsum[250];
	char		instr[3];
	char		i_instr[6];
	char		tinstr[60];
	char		outstr[3];
	char		i_outstr[6];
	char		toutstr[60];

	char		used[25];
	used[0]='-';
	used[1]='-';
	used[2]='\0';



	strsum[0]='\0';
	tstrsum[0]='\0';

	#if 0
	AUD_KDRV_ERROR("\n");
	AUD_KDRV_ERROR("========================================================= ALLOC MOD INFO =======================================================\n");
	for( i = 0; i < (LX_AUD_MOD_TYPE_MAX -1); i++)
	{
		allocBase 	= ModInfo.allocBase[modType];
		availbleNum 	= ModInfo.availableNum[modType];

		for(  searchStart = allocBase; searchStart < allocBase +availbleNum  ; searchStart++)
		{
			MOD =&ModInfo.list[searchStart];

			//sprintf(strsum,"[%11s] ",(ModInfo.devList[searchStart].allocMod_Str==(void *)0)? 'not assign':ModInfo.devList[searchStart].allocMod_Str);
			sprintf(strsum,"[%11s] ",MOD->allocStr);
			strcat(tstrsum,strsum);
		}

		if(i ==  LX_AUD_OUT_PCM_0 )
		AUD_KDRV_ERROR("========================================================= EXTRA MOD INFO =======================================================\n");

		AUD_KDRV_ERROR("[%9s]  :  %s\n",modTypeStr[modType] ,tstrsum);

		strsum[0]='\0';
		tstrsum[0]='\0';

		modType++;
	}
	AUD_KDRV_ERROR("================================================================================================================================\n");
	#endif

	strsum[0]='\0';
	tstrsum[0]='\0';
	AUD_KDRV_ERROR("\n");
	AUD_KDRV_ERROR("========================================================= ALLOC DEV INFO =======================================================\n");
	for( i = 0; i < (LX_AUD_DEV_TYPE_MAX -1); i++)
	{
		allocBase 	= DevInfo.allocBase[devType];
		availbleNum 	= DevInfo.availableNum[devType];

		for(  searchStart = allocBase; searchStart < allocBase +availbleNum  ; searchStart++)
		{
			DEV =&DevInfo.list[searchStart];
			//sprintf(strsum,"[%11s] ",(DevInfo.devList[searchStart].allocMod_Str==(void *)0)? 'not assign':DevInfo.devList[searchStart].allocMod_Str);
			sprintf(strsum,"[%9s] ",DEV->allocStr);
			strcat(tstrsum,strsum);
		}

		AUD_KDRV_ERROR("[%9s] : %s\n",devTypeStr[devType] ,tstrsum);

		strsum[0]='\0';
		tstrsum[0]='\0';

		devType++;
	}
	msleep_interruptible(10);
	AUD_KDRV_ERROR("============================================================ DEV INFO ==========================================================\n");

	strsum[0]='\0';
	tstrsum[0]='\0';
	devType = LX_AUD_DEV_DEC;
	for( i = 0; i < (LX_AUD_DEV_TYPE_MAX -1); i++)
	{
		allocBase 	= DevInfo.allocBase[devType];
		availbleNum 	= DevInfo.availableNum[devType];

		for(  searchStart = allocBase; searchStart < allocBase +availbleNum  ; searchStart++)
		{
			DEV =&DevInfo.list[searchStart];

			//AUD_KDRV_ERROR("dev[%s] allocBase[%d] availbleNum[%d] searchStart[%d],ownNum[%d]\n ",allocDev_Str[searchStart],allocBase,availbleNum,searchStart,DevInfo.list[searchStart].ownNum	);

			if (DEV->ownNum >0 )
			{
				for(	j = 0 ; j < MAX_OWN_MOUDLE; j++)
				{
				 	if (DEV->own[j].mod != ADEC_MODULE_NO_MOD)
					{
						sprintf(strsum,"[%9s] ",allocMod_Str[DEV->own[j].mod]);
						strcat(tstrsum,strsum);
				 	}
				}

				AUD_KDRV_ERROR("[%9s] : %s\n",allocDev_Str[searchStart] ,tstrsum);
				strsum[0]='\0';
				tstrsum[0]='\0';
			}

		}

		devType++;
	}
	AUD_KDRV_ERROR("================================================================================================================================\n");

	devType = LX_AUD_DEV_DEC;
	for( i = 0; i < (LX_AUD_DEV_TYPE_MAX -1); i++)
	{
		allocBase 	= DevInfo.allocBase[devType];
		availbleNum 	= DevInfo.availableNum[devType];

		for(  searchStart = allocBase; searchStart < allocBase +availbleNum  ; searchStart++)
		{
			DEV =&DevInfo.list[searchStart];

			instr[0]='\0';			i_instr[0]='\0';
			tinstr[0]='\0';
			strsum[0]='\0';

			for(	j = 0 ; j < MAX_OWN_MOUDLE; j++)
			{
				sprintf(instr,"%2d",DEV->own[j].mod);

				if(j !=(MAX_OWN_MOUDLE-1))
					sprintf(i_instr,"%2s:",(DEV->own[j].mod !=ADEC_MODULE_NO_MOD)?instr : strsum);
				else
					sprintf(i_instr,"%2s",(DEV->own[j].mod !=ADEC_MODULE_NO_MOD)?instr : strsum);

				strcat(tinstr,i_instr);
			}

			if(DEV->allocDev !=AUD_NO_DEV)
			{
				//AUD_KDRV_ERROR("[%9s]  :  %11s:%2d  own:%2d full:%d start:%d head[%11s] tail[%11s] own[%2d,%2d,%2d,%2d,%2d,%2d,%2d,%2d]\n"
				AUD_KDRV_ERROR("[%9s:%2d] : own:%2d full:%d start:%d head[%9s] tail[%9s] own[%s]\n"
					,allocDev_Str[searchStart], DEV->allocDev
					,DEV->ownNum,DEV->isFullyConnected
					,DEV->connectStart
					,(DEV->headOfDev!= NULL)?allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T * )DEV->headOfDev)->allocMod]:NULL
					,(DEV->tailOfDev!= NULL)?allocMod_Str[((LX_AUD_ALLOC_FREE_INFO_T * )DEV->tailOfDev)->allocMod]:NULL
				//	,DEV->own[0].mod, DEV->own[1].mod, DEV->own[2].mod, DEV->own[3].mod, DEV->own[4].mod, DEV->own[5].mod, DEV->own[6].mod, DEV->own[7].mod
					,tinstr
				);
			}
		}

		devType++;
	}
	msleep_interruptible(10);
	AUD_KDRV_ERROR("============================================================ MOD INFO ==========================================================\n");
	AUD_KDRV_ERROR("                                         |                                      |           INTRA|     MULTISINK| \n");
	//AUD_KDRV_ERROR("                                             |                 |                           INTRA|                           MULTISINK| \n");

	modType = LX_AUD_MAN_ARM;
	for( i = 0; i < (LX_AUD_MOD_TYPE_MAX -1); i++)
	{
		allocBase 	= ModInfo.allocBase[modType];
		availbleNum 	= ModInfo.availableNum[modType];

		for(  searchStart = allocBase; searchStart < allocBase +availbleNum  ; searchStart++)
		{
			instr[0]='\0';			i_instr[0]='\0';
			tinstr[0]='\0';
			outstr[0]='\0';			i_outstr[0]='\0';
			toutstr[0]='\0';
			strsum[0]='\0';
			tstrsum[0]='\0';

			MOD =&ModInfo.list[searchStart];
			for( j = 0 ; j < MAX_PORT; j++)
			{

				if(j < MULTISINKBASE)
				//if(j < MULTISINKBASE - INPORT_SHRINK_FOR_DISPLAY)

				{
					sprintf(instr,"%2d",MOD->inOutMap[j].map.in);
					sprintf(i_instr,"%2s",(MOD->inOutMap[j].map.in !=ADEC_MODULE_NO_MOD)?instr : strsum);
					strcat(tinstr,i_instr);
				}

				if(j < OUT__0__7_PORT_FOR_DISPLAY_IGNORE || ( j >= MULTISINKBASE && j < OUT_16_23_PORT_FOR_DISPLAY_IGNORE )  )
				{
				//if(j < MULTISINKBASE - INPORT_SHRINK_FOR_DISPLAY)
					sprintf(outstr,"%2d",MOD->inOutMap[j].map.out);
					sprintf(i_outstr,"%2s",


					(MOD->inOutMap[j].map.out !=ADEC_MODULE_NO_MOD)? 	((MOD->inOutMap[j].map.out!=USED_PORT)?outstr : used):((MOD->inOutMap[j].map.out!=USED_PORT)?strsum : used) );
					strcat(toutstr,i_outstr);
				}
			}
			instr[0]='\0';
			i_instr[0]='\0';

			sprintf(instr,"%2d",MOD->allocMod);
			sprintf(i_instr,"%2s",(MOD->allocMod !=ADEC_MODULE_NO_MOD)?instr : strsum);

			if(MOD->allocMod !=ADEC_MODULE_NO_MOD)
			{

	//			AUD_KDRV_ERROR("[%10s:%2d:%2x%5s]M%2dS%2dSU%dHF%dm%ds%d I[%s%4llx]O[%s%8llx]\n"
	//			AUD_KDRV_ERROR("[%10s:%2d:%2x%5s]M%2dS%2dSU%dHF%dm%ds%d I[%s%4llx]O[%s%4llx|%4llx]\n"
				AUD_KDRV_ERROR("[%10s:%2d:%2x%5s]M%2dS%2d SU%dHF%d m%ds%d I[%s%4llx]O[%sXX%2llx|XX%2llx]\n"
								,allocMod_Str[searchStart], searchStart,searchStart,modStatusStr[MOD->status],
								MOD->allocDev,
								MOD->allocSubDev,
								MOD->subUsed,MOD->hasFakeMod,
								MOD->multiConnIdx,MOD->connectStart,
								tinstr,
								MOD->inPool&INTRA_PORT_MASK,
								toutstr,
								//MOD->outPool&INTRA_PORT_MASK,(MOD->outPool& MULTISINK_PORT_MASK)>> MULTISINKBASE
								MOD->outPool&INTRA_PORT__IGNORE_24_31_MASK,(MOD->outPool& MULTISINK_PORT_IGNORE__8_15_MASK)>> MULTISINKBASE
								//MOD->outPool
								);

			}
		}
		if( i % 20 == 0)
			msleep_interruptible(10);
		modType++;

	}
	AUD_KDRV_ERROR("================================================================================================================================\n");


}

void  AUDIO_UpdateConnectionInfo (void )
{
	UINT32 	i= 0,j= 0,k= 0,m= 0;
	UINT32 	conNum = 0,nextMod = 0, subConNum = 0,inputMod = 0 ;
	UINT32 	*pConNum = NULL, *pSubConNum =NULL, *pNextMod =NULL;
	UINT32 	leftNextConn = 0;
	UINT32 	tempOutPool	= 0;
	UINT32	findStatus = NORMAL_FINDING,findType = NORMAL_FINDING;
	UINT32	retFind = 0;
	UINT32	outPortSearchBase =	0;
	UINT32  leftMod = ADEC_MODULE_NO_MOD, leftModPort[MAX_PORT], nextModConnection = 0, leftSubComNum = 0;

	UINT32 	connection = 0;
	UINT32 	multiINPUT = 0;
	UINT32 	multiINPUT_mod = ADEC_MODULE_NO_MOD;
	UINT32 	multiINPUT_mod2 = ADEC_MODULE_NO_MOD;
	LX_AUD_ALLOC_FREE_INFO_T * nextMOD,*inputMOD;

	pConNum		= &conNum;
	pSubConNum	= &subConNum;
	pNextMod	= &nextMod;

	AUDIO_UpdateAllocInfo();
	memset(&GCon,0, sizeof(LX_AUD_CON_T)*TCON_NUM );

	// find  start of connection
	for( i = 0; i < ADEC_MODULE_MOD_MAX ; i++)
	{

		nextMOD = &ModInfo.list[i];

		//backup module for multi input display
		inputMOD = nextMOD;

		if(nextMOD->connectStart == 1 )
		{
			inputMod = nextMOD->allocMod;
			nextMod	=	nextMOD->allocMod;
			GCon[conNum].subCon[subConNum] 			= nextMOD->allocMod;
			GCon[conNum].subConStr[subConNum] 		= nextMOD->allocStr;
			GCon[conNum].subConDevType[subConNum] 	= nextMOD->modType;
			GCon[conNum].subConType[subConNum]		= nextMOD->connType;

			// conNum(x), subConNum(y) is index in GCon matrix
			subConNum++;

			nextMod 		= i;

 			if (
				((UINT32)(nextMOD->allocMod)  >= (UINT32)ADEC_MODULE_TP_IN_0 && (UINT32)(nextMOD->allocMod)  <= (UINT32)ADEC_MODULE_ADC_IN) &&
				nextMOD->subUsed  == 1
			)
			{
				multiINPUT = 1;
				multiINPUT_mod  = nextMOD->allocMod;
				multiINPUT_mod2 = ADEC_MODULE_DEC_1;

			}

			repeatHere:

			switch(findStatus)
			{
				case NORMAL_FINDING:
				case ADDITIONAL_FINDING:
					nextMOD = &ModInfo.list[nextMod];
					AUD_KDRV_RM("[%s] Mod[%9s]\n",findStatusS[findStatus], allocMod_Str[nextMod]);
					j= outPortSearchBase;
					break;
				default:
					nextMOD = &ModInfo.list[nextMod];
					AUD_KDRV_RM("d findStatus[%d]Mod[%9s] \n", findStatus,allocMod_Str[nextMod] );
					break;
			}

			// check multiconnection of currentmodule
			connection	= AUDIO_GeMultiConnectiionOutPortNum(nextMOD);

			tempOutPool = nextMOD->outPool;

			//printk("conection%d tempOutPool[%x] findStatus[%s]\n",connection ,tempOutPool,findStatusS[findStatus]  );

			if(connection > 1 && findStatus == NORMAL_FINDING && nextMod != ADEC_MODULE_MIX_0 )
			//if(connection > 1 && findStatus == NORMAL_FINDING && ( nextMod == ADEC_MODULE_DEC_0 || nextMod == ADEC_MODULE_DEC_1) )
			{
				for( k= 0; k < MAX_PORT ; k++)
				{
					if( (tempOutPool &	0x1) == 0 && nextMOD->modType == LX_AUD_DEC && nextMOD->inOutMap[k].map.out != USED_PORT ) /*DECODER MODULE */
					{

						leftMod = nextMod;
						leftModPort[leftNextConn]= k;
						nextModConnection++;
						leftNextConn++;
						leftSubComNum = subConNum;
						//printk("####leftMod[%9s:%d] port[%d] connection[%d] m[%d]\n",allocMod_Str[leftMod],leftMod, leftModPort[m], leftNextConn ,m);

					}
					//AUD_KDRV_RMD("2*** nextMod[%s]tempOutPool[%4x] k[%d] \n",allocMod_Str[nextMod],tempOutPool,k );
					tempOutPool=tempOutPool >>1 ;
				}

				if( nextModConnection > 1)
				{
					leftMod = nextMod;
				}
			}

			tempOutPool = nextMOD->outPool;
			tempOutPool = tempOutPool << outPortSearchBase;

			for(j = outPortSearchBase;j < MAX_PORT; j++)
			{
					//AUD_KDRV_RMD("j[%d] tempOutPool[%4x] \n",j,tempOutPool);

				if( (tempOutPool &	0x1) == 0 && !(nextMOD->hasMultiSink == 1 && nextMOD->hasIntra == 1 && j==0) /*DECODER MODULE */ )
				{
					while(1)
					{
						AUD_KDRV_RM("j[%d]temp[%4x]nextMod[%9s:%d]f[%d][%s]\n",j,tempOutPool,allocMod_Str[nextMod],nextMod, findType,findStatusS[findStatus] );
						//seek the sequenctional module
						retFind = AUDIO_FindConnectedModule( &nextMod, j, pConNum, pSubConNum,0, findType);


						// if module has next module
						if( retFind > 0 )
						{
							#if 0
							if ( findStatus == ADDITIONAL_FINDING && nextMod == ADEC_MODULE_SE)
							{
 							}
							#endif
							outPortSearchBase = 0;
							goto	repeatHere;

						}
						// no next module left
						else if ( retFind == 0 )
						{

							if(findStatus == NORMAL_FINDING && leftMod != ADEC_MODULE_MIX_0 )
							//if(findStatus == NORMAL_FINDING &&  (leftMod == ADEC_MODULE_DEC_0 || leftMod == ADEC_MODULE_DEC_1) )
							{


								AUD_KDRV_RM("leftNextConn[%d] leftMod[%s]\n",leftNextConn, allocMod_Str[leftMod] );

								if( leftNextConn > 1 )
								{
									findStatus = ADDITIONAL_FINDING;
									nextMod= leftMod;
									outPortSearchBase = leftModPort[m+1];
									(*pConNum )++;
									*pSubConNum = leftSubComNum;
									leftNextConn--;
									m++;

									nextMOD = &ModInfo.list[nextMod];

									// multi input case
									if((UINT32)(nextMOD->allocMod)  >= (UINT32)ADEC_MODULE_TP_IN_0 && (UINT32)(nextMOD->allocMod)  <= (UINT32)ADEC_MODULE_ADC_IN)
									{
										AUD_KDRV_RMD("LM[%s] M[%s]y[%d]x[%d] ct[%d]",allocMod_Str[leftMod], allocMod_Str[nextMOD->allocMod],*pConNum,*pSubConNum,nextMOD->connType );
										nextMOD = &ModInfo.list[nextMod];
										GCon[*pConNum].subCon[0] 		= nextMOD->allocMod ;
										GCon[*pConNum].subConStr[0] 	= nextMOD->allocStr;
										GCon[*pConNum].subConType[0]	= nextMOD->connType;
									}

									leftMod = 0;
									memset(&leftModPort[0],0,MAX_PORT*sizeof(UINT32));
									nextModConnection=0;
									leftNextConn=0;

									m=0;
									goto	repeatHere;
								}
								else
								{

									if(multiINPUT == 1)
									{
										multiINPUT = 0;

										(*pConNum )++;
										*pSubConNum = 0;
										findStatus = NORMAL_FINDING;
										printk("@@@@\n");

										nextMod = multiINPUT_mod; //tp

										nextMOD = &ModInfo.list[nextMod];

										GCon[*pConNum].subCon[*pSubConNum] 		= nextMOD->allocMod ;
										GCon[*pConNum].subConStr[*pSubConNum] 	= nextMOD->allocStr;
										GCon[*pConNum].subConType[*pSubConNum]	= nextMOD->connType;

										(*pSubConNum)++;

										nextMod = multiINPUT_mod2;//dec1

										nextMOD = &ModInfo.list[nextMod];

										GCon[*pConNum].subCon[*pSubConNum] 		= nextMOD->allocMod ;
										GCon[*pConNum].subConStr[*pSubConNum] 	= nextMOD->allocStr;
										GCon[*pConNum].subConType[*pSubConNum]	= nextMOD->connType;

										(*pSubConNum)++;

										nextMod = multiINPUT_mod2;

									    goto repeatHere;
									}

									AUD_KDRV_RM("else1\n");
									(*pConNum )++;
									*pSubConNum = 0;
									goto	excapeAdditional;
								}
								AUD_KDRV_RMD("NEXT nextMod[%9s:%9s:%d]f[%d]port[%d]leftNextConn[%d]\n",allocMod_Str[nextMod],allocMod_Str[*pNextMod],nextMod, findType, outPortSearchBase,leftNextConn );

							}
							else if (findStatus == NORMAL_FINDING )
							{
								AUD_KDRV_RMD("leftmod [%s] [%s]\n",allocMod_Str[leftMod],findStatusS[findStatus]);
							}
							else if (findStatus == ADDITIONAL_FINDING)
							{
								AUD_KDRV_RMD("leftmod [%s] [%s]\n",allocMod_Str[leftMod],findStatusS[findStatus]);

								if(multiINPUT == 1)
								{
									multiINPUT = 0;

									(*pConNum )++;
									*pSubConNum = 0;
									findStatus = NORMAL_FINDING;
									printk("@@@@\n");

									nextMod = multiINPUT_mod; //tp

									nextMOD = &ModInfo.list[nextMod];

									GCon[*pConNum].subCon[*pSubConNum] 		= nextMOD->allocMod ;
									GCon[*pConNum].subConStr[*pSubConNum] 	= nextMOD->allocStr;
									GCon[*pConNum].subConType[*pSubConNum]	= nextMOD->connType;

									(*pSubConNum)++;

									nextMod = multiINPUT_mod2;//dec1

									nextMOD = &ModInfo.list[nextMod];

									GCon[*pConNum].subCon[*pSubConNum] 		= nextMOD->allocMod ;
									GCon[*pConNum].subConStr[*pSubConNum] 	= nextMOD->allocStr;
									GCon[*pConNum].subConType[*pSubConNum]	= nextMOD->connType;

									(*pSubConNum)++;

									nextMod = multiINPUT_mod2;

								    goto repeatHere;
								}
								else
								{
									//printk("escape1 %s\n", allocMod_Str[nextMod]);
									AUD_KDRV_RM("escape1 %s\n", allocMod_Str[nextMod]);
									findStatus = NORMAL_FINDING;
									(*pConNum )++;
									*pSubConNum = 0;
									outPortSearchBase = 0;
									goto	excapeAdditional;
								}
							}

						}

						else
						{
							AUD_KDRV_RM("else\n");
						}
					}
				}
				tempOutPool = tempOutPool >> 1;
			}




		}

		excapeAdditional:;

	}


	if(*pSubConNum ==0 && conNum > 0 )
		conNum--;

	ModInfo.conNum = conNum;
	AUD_KDRV_ERROR("\n");
	AUD_KDRV_ERROR("========================================================= CONNECTION INFO ======================================================\n");

	for( i = 0; i <= conNum; i++)
	{
		AUD_KDRV_ERROR("[%9s]%s[%9s]%s[%9s]%s[%9s]%s[%9s]%s[%9s]%s[%9s]%s[%9s]%s[%9s]%s[%9s]%s\n",
			GCon[i].subConStr[0],conn_Str[ GCon[i].subConType[0]] ,
			GCon[i].subConStr[1],conn_Str[ GCon[i].subConType[1]] ,
			GCon[i].subConStr[2],conn_Str[ GCon[i].subConType[2]] ,
			GCon[i].subConStr[3],conn_Str[ GCon[i].subConType[3]] ,
			GCon[i].subConStr[4],conn_Str[ GCon[i].subConType[4]] ,
			GCon[i].subConStr[5],conn_Str[ GCon[i].subConType[5]] ,
			GCon[i].subConStr[6],conn_Str[ GCon[i].subConType[6]] ,
			GCon[i].subConStr[7],conn_Str[ GCon[i].subConType[7]] ,
			GCon[i].subConStr[8],conn_Str[ GCon[i].subConType[8]] ,
			GCon[i].subConStr[9],conn_Str[ GCon[i].subConType[9]] );
		AUD_KDRV_ERROR("================================================================================================================================\n");
	}
	AUD_KDRV_ERROR("================================================================================================================================\n");


}





