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


/** @file audio_drv_manager.h
 *
 *  driver interface header for audio device. ( used only within kdriver )
 *	audio device will teach you how to make device driver with new platform.
 *
 *  @author	wonchang.shin (wonchang.shin@lge.com)
 *  @version	0.1
 *  @date		2012.04.25
 *
 *  @addtogroup lg1150_audio
 *	@{
 */

#ifndef	_AUDIO_DRV_MANAGER_MGR_H_
#define	_AUDIO_DRV_MANAGER_MGR_H_

#include "audio_kapi_master.h"
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

#define DISCONNECT_ALL_IN_DEV_ENABLE
#define ADD_BYPASS_MODULE_ENABLE

//#define MASTER_MODULE_ENABLE

#define MULTI_CON_LEN 	10	// connection length
#define CON_LEN 		10	// connection length
#define TCON_NUM		10  // total connection num

#define DUMMY_NUM		1

//need to sync with device num ,extra manager module
// EXTRA MODULE
#define MPB_NUM			8
#define CPB_NUM			4
#define DPB_NUM			4
#define IEC_NUM			2
#define CAPB_NUM		3
#define	EXTRA_RM_MODULE_NUM		(MPB_NUM + CPB_NUM + DPB_NUM + IEC_NUM + CAPB_NUM )
#define IN_PORT			0

//need to sync with device num ,extra manager module
//device type: 5 unit
#define DEV_DEC_NUM		2
#define DEV_ENC_NUM		2
#define DEV_CAP_NUM		3
#define DEV_REN_NUM		12//8
#define DEV_MAS_NUM		1

#define CHECK_IN_PORT	0
#define CHECK_OUT_PORT	1




#define MAX_OWN_MOUDLE	16

#define MAX_PORT_IN_BYTE	2
#define MAX_PORT		32
#define MULTISINKBASE	16
#define INPORT_SHRINK_FOR_DISPLAY	8
#define OUT__0__7_PORT_FOR_DISPLAY_IGNORE	8
#define OUT_16_23_PORT_FOR_DISPLAY_IGNORE	24

#define PORT_FULL		32
#define PORT_NONE		32
#define MULTISINK_PORT_MASK 0xffff0000
#define MULTISINK_PORT_IGNORE__8_15_MASK 0x00ff0000

#define INTRA_PORT_MASK 0xffff
#define INTRA_PORT__IGNORE_24_31_MASK 0xff




#define IN_PORT 	0
#define OUT_PORT 	1

#define NONE		0
#define INIT		1
#define START		2
#define STOP		3
#define FLUSH		4
#define MULTI		5
#define ALLOC		6

#define LAST_MOD_OF_SAME_MODS	1
#define SAME_MOD				2

#define NO_FORCE	8

//only for device no for mod
#define CONN_HEAD	1
#define CONN_MIDDLE	2
#define CONN_NONE	0

//related bypass module
#define BYTE_BASED_MODE		0
#define AU_BASED_MODE		1

#define HAS_NOT_MULTISINK_PORT	100

#define NO_OVERFLOW_PROTECTION		0
#define ENABLE_OVERFLOW_PROTECTION		1

#define GET_DEC_INDEX(ALLOCDEC_DEV_ID)	((ALLOCDEC_DEV_ID) - AUD_DEV_DEC0)
#define GET_REN_INDEX(ALLOCDEC_DEV_ID)	((ALLOCDEC_DEV_ID) - AUD_DEV_REN0)
#define GET_ENC_INDEX(ALLOCDEC_DEV_ID)	((ALLOCDEC_DEV_ID) - AUD_DEV_ENC0)
#define GET_CAP_INDEX(ALLOCDEC_DEV_ID)	((ALLOCDEC_DEV_ID) - AUD_DEV_CAP0)

#define USED_PORT		0x100

/**
 * AUDIO MASTER Output Port.
 */
typedef enum {
	LX_AUD_OUTPUT_SPEAKER_B		=	0, 		// 0
	LX_AUD_OUTPUT_HP_B			=	1, 		// 1
	LX_AUD_OUTPUT_SCART_B		=	2,		// 2
	LX_AUD_OUTPUT_SPDIF_B		=	3,		// 3
	LX_AUD_OUTPUT_MAX_B			=	4
} LX_AUD_OUTPUT_BIT_T;

typedef enum {
	LX_AUD_OUTPUT_SPEAKER	=	0, 		// 0
	LX_AUD_OUTPUT_HP		=	1 << LX_AUD_OUTPUT_HP_B, 		// 1
	LX_AUD_OUTPUT_SCART		=	1 << LX_AUD_OUTPUT_SCART_B,	// 2
	LX_AUD_OUTPUT_SPDIF		=	1 << LX_AUD_OUTPUT_SPDIF_B,	// 3
	LX_AUD_OUTPUT_MAX		=	1 << LX_AUD_OUTPUT_MAX_B
} LX_AUD_OUTPUT_T;

typedef enum {
	CONN_TYPE_NONE	= 0,
	CONN_TYPE_CONNECT,
	CONN_TYPE_ALLOC	,
	CONN_TYPE_CPB_ALLOC_L  ,
	CONN_TYPE_CPB_ALLOC_R  ,
	CONN_TYPE_DPB_ALLOC_L  ,
	CONN_TYPE_DPB_ALLOC_R  ,
	CONN_TYPE_MPB_ALLOC_L	,
	CONN_TYPE_MPB_ALLOC_R	,
	CONN_TYPE_IECB_ALLOC_L	,
	CONN_TYPE_IECB_ALLOC_R	,
	CONN_TYPE_CAPB_ALLOC_L	,
	CONN_TYPE_CAPB_ALLOC_R	,

	CONN_TYPE_DISCONNECT,
	CONN_TYPE_CPB_DALLOC_L ,
	CONN_TYPE_CPB_DALLOC_R ,
	CONN_TYPE_DPB_DALLOC_L  ,
	CONN_TYPE_DPB_DALLOC_R  ,
	CONN_TYPE_MPB_DALLOC_L	,
	CONN_TYPE_MPB_DALLOC_R	,
	CONN_TYPE_IECB_DALLOC_L	,
	CONN_TYPE_IECB_DALLOC_R	,
	CONN_TYPE_CAPB_DALLOC_L	,
	CONN_TYPE_CAPB_DALLOC_R	,

	CONN_TYPE_MAX,
}LX_AUD_CONN_TYPE_T;

typedef enum {

	IEC_BUFF = 0,
	IEC_LIP,
}LX_AUD_SUB_MOD_T;

//need to sync with device num ,extra manager module
/**
 * AUDIO Allocated Device Temp
 */
typedef enum {

	ADEC_MODULE_MPB_0	= ADEC_MODULE_MAX,
	ADEC_MODULE_MPB_1,
	ADEC_MODULE_MPB_2,
	ADEC_MODULE_MPB_3,
	ADEC_MODULE_MPB_4,
	ADEC_MODULE_MPB_5,
	ADEC_MODULE_MPB_6,
	ADEC_MODULE_MPB_7,
	ADEC_MODULE_CPB_0,
	ADEC_MODULE_CPB_1,
	ADEC_MODULE_CPB_2,
	ADEC_MODULE_CPB_3,
	ADEC_MODULE_DPB_0,
	ADEC_MODULE_DPB_1,
	ADEC_MODULE_DPB_2,
	ADEC_MODULE_DPB_3,
	ADEC_MODULE_IEC_0,
	ADEC_MODULE_IEC_1,
	ADEC_MODULE_CAPB_0,	// capture buffer
	ADEC_MODULE_CAPB_1,	// capture buffer
	ADEC_MODULE_CAPB_2,	// capture buffer

	//refer ""module/adec_module_def.h"'s module

	ADEC_MODULE_NO_MOD	= (ADEC_MODULE_MAX + EXTRA_RM_MODULE_NUM + 1),
	ADEC_MODULE_MOD_MAX,

	//To Do: need to cover all device(resource) in adec_module_def.h
} LX_AUD_ALLOC_MOD_T;

/**
 * AUDIO alloc device type : main device having a device node, sub device type
 */
//need to sync with device num ,extra manager module
typedef enum {
	LX_AUD_MOD_TYPE_NONE	= 	0,
	LX_AUD_MAN_ARM	     	,
	LX_AUD_MAN_DSP0	     	,
	LX_AUD_MAN_DSP1	     	,
	LX_AUD_DBG_DSP0	     	,
	LX_AUD_DBG_DSP1	     	,
	LX_AUD_TP_IN0         	,
	LX_AUD_TP_IN1         	,
	LX_AUD_SIF_IN	     	,
	LX_AUD_HDMI_IN	     	,
	LX_AUD_ADC_IN	     	,
	LX_AUD_DEC           	,
	LX_AUD_ENC           	,
	LX_AUD_SRCD	     		,
	LX_AUD_SRC_DEC	     	,
	LX_AUD_SRC1     		,
	LX_AUD_LIP           	,
	LX_AUD_LIP_ES           ,
	LX_AUD_MIX	     		,
	LX_AUD_SE	     		,
	LX_AUD_OUT_CTRL      	,
	LX_AUD_OUT_ES			,
	LX_AUD_OUT_PCM	     	,
	LX_AUD_OUT_SPDIF     	,
	LX_AUD_OUT_PCM_0   		,
	LX_AUD_OUT_SPDIF_0		,
	LX_AUD_DUMP_DSP0		,
	LX_AUD_DUMP_DSP1		,
	LX_AUD_BYPASS_DSP0		,
	LX_AUD_BYPASS_ES_DSP0		,
	LX_AUD_BYPASS_DSP1		,
	LX_AUD_IMC_DSP0			,
	LX_AUD_IMC_DSP1			,
	LX_AUD_IMC_ARM			,
	LX_AUD_IMC_OUT_PCMSUB	,
	LX_AUD_IMC_DTO_A		,
	LX_AUD_IMC_DTO_D		,
	LX_AUD_RTS				,
	LX_AUD_HWSRC_DSP0		,
	LX_AUD_HWSRC_DSP1		,
	LX_AUD_SOLA				,
	LX_AUD_CTRLSRC			,

	LX_AUD_MPB        		,
	LX_AUD_CPB      		,
	LX_AUD_DPB        		,
	LX_AUD_IEC        		,
	LX_AUD_CAPB        		,
	LX_AUD_MOD_TYPE_MAX  	,
} LX_AUD_MOD_TYPE_T;

typedef enum {
	LX_AUD_DEV_NONE	 = 0,
	LX_AUD_DEV_DEC	     	,
	LX_AUD_DEV_ENC	     	,
	LX_AUD_DEV_CAP	     	,
	LX_AUD_DEV_REN			,
	LX_AUD_DEV_MAS			,
	LX_AUD_DEV_TYPE_MAX  	,
} LX_AUD_DEV_TYPE_T;


typedef union _LX_AUD_INOUT_MAP_T
{
	struct
	{
		unsigned int	in;
		unsigned int	out;
	}				map;
	int				total[MAX_PORT_IN_BYTE];
}LX_AUD_INOUT_MAP_T;

typedef union _LX_AUD_INOUT_PORTMAP_T
{
	struct
	{
		unsigned int	to :16;
		unsigned int	num:16;
	}				map;
	int				total;
}LX_AUD_INOUT_PORTMAP_T;



#define DEV_TYPE_BASE	1

/**
 * Connection infomation
 * @see
*/
typedef struct
{
	UINT8 *				modStr;		/*module string*/
	LX_AUD_ALLOC_MOD_T  mod;		/* module */
	LX_AUD_MOD_TYPE_T	modType;	/* module type */
}LX_AUD_MOD_T;

/**
 * Audio alloc free information for Main dev(having a device node) , Sub dev
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ENCODING_INFO
*/
typedef struct LX_AUD_ALLOC_FREE_INFO{
	UINT8				connType;
	UINT8				used;
	UINT8				subUsed;
	UINT8				hasFakeMod;
	UINT8				status;
	UINT8				inNum;
	UINT8				outNum;
	UINT8				multiConnIdx;
	UINT64				inPool;
	UINT64				outPool;
	LX_AUD_INOUT_MAP_T	inOutMap[MAX_PORT];
	void	*			out[MAX_PORT];
	void	*			in[MAX_PORT];
	UINT8				multiSinkPortNum;
	UINT8				hasMultiSink;
	UINT8				hasIntra;
	UINT8				outPortSearchBase;
	UINT8				needToConnectToIntra;
	UINT8 *				allocStr;
	LX_AUD_MOD_TYPE_T	modType;
	LX_AUD_ALLOC_MOD_T	allocMod;   //device node, module
	LX_AUD_DEV_TYPE_T	devType;
	LX_AUD_ALLOC_DEV_T	allocDev; //devicenode
	LX_AUD_ALLOC_DEV_T	allocSubDev; //devicenode

	//only has a meaning in device node
	UINT8				hasIECBuff;
	UINT8				hasIECLIP;
	UINT8				hasEPB;
	UINT8				connectStart;
	UINT8				connectEnd;
	UINT8				connectLength;
	UINT8				isFullyConnected;
	void	*			headOfDev;
	void	*			tailOfDev;
	LX_AUD_MOD_T		own[MAX_OWN_MOUDLE];
	UINT32				ownNum;
} LX_AUD_ALLOC_FREE_INFO_T;

/**
 * Audio alloc free information for Main dev(having a device node) , Sub dev
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ENCODING_INFO
*/
typedef struct
{
	UINT32	conNum;
	UINT32 	allocCnt[LX_AUD_DEV_TYPE_MAX+1];
	UINT32 	availableNum[LX_AUD_DEV_TYPE_MAX+1];
	UINT32 	allocBase[LX_AUD_DEV_TYPE_MAX+1];

	LX_AUD_ALLOC_FREE_INFO_T list[AUD_DEV_MAX]; // for main device having a device node   , sub device( ex SRC,LIP)
}LX_AUD_DEV_INFO_T;

/**
 * Audio alloc free information for Main dev(having a device node) , Sub dev
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ENCODING_INFO
*/

typedef struct
{
	UINT32	conNum;
	UINT32 	allocCnt[LX_AUD_MOD_TYPE_MAX+1];
	UINT32 	availableNum[LX_AUD_MOD_TYPE_MAX+1];
	UINT32 	allocBase[LX_AUD_MOD_TYPE_MAX+1];

	LX_AUD_ALLOC_FREE_INFO_T list[ADEC_MODULE_MOD_MAX]; // for main device having a device node   , sub device( ex SRC,LIP)
}LX_AUD_MOD_INFO_T;

typedef struct
{
	UINT8	*str;
	UINT32					depth;
	UINT32					subConNum;
	UINT32					direction;
	LX_AUD_ALLOC_MOD_T		start;

}LX_AUD_MULTI_T;

/**
 * Connection infomation
 * @see
*/
typedef struct
{
	UINT8 *				subConStr[CON_LEN];
	LX_AUD_ALLOC_MOD_T	subCon[CON_LEN];
	UINT32 				subConType[CON_LEN];
	UINT32				subConMultiConnNum;
	LX_AUD_MULTI_T		mulCon[MULTI_CON_LEN];

	LX_AUD_DEVICE_T	subConDevType[CON_LEN];/* device type */
}LX_AUD_CON_T;

typedef struct
{

	UINT8 ModNum;
	char * ModNumName;
} AUD_MOD_NUM_T;


int  AUDIO_AllocDev ( void  * pOpenInfo);
int  AUDIO_FreeDev ( void  * pCloseInfo);
int  AUDIO_AllocModule ( UINT32 allocDevN , UINT32 moduleType, UINT32 wantModule);
int  AUDIO_FreeModule ( UINT32 allocMod, UINT32 allocDev );
int  AUDIO_GetAllocInfo ( UINT32 allocDevN , UINT32 * allocModNum,  LX_AUD_MOD_T  ** ppOwnMods );

UINT32 AUDIO_GetModule(UINT32 allocDev, LX_AUD_MOD_TYPE_T modType);
LX_AUD_ALLOC_MOD_T  AUDIO_HasThisModuleType ( UINT32 allocDev , LX_AUD_MOD_TYPE_T modTypeToFind );

int  AUDIO_DevInfoInit ( void  );
int  AUDIO_IsAlreadyConnected ( UINT32 left, UINT32 right);
int  AUDIO_IsNotConnectedYet ( UINT32 left, UINT32 right);
int  AUDIO_ConnectTo ( UINT32 left, UINT32 right, UINT32 forceLeftOutPort, UINT32 foreceRightInPort);
int  AUDIO_DisconnectTo ( UINT32 left, UINT32 right, UINT32 forceLeftOutPort, UINT32 foreceRightInPort);
int  AUDIO_Destory ( UINT32 left );

int AUDIO_GeAvailabletPortNum( LX_AUD_ALLOC_FREE_INFO_T * pMod , UINT32 inOut);
int AUDIO_GetMultiOutConnIdx( LX_AUD_ALLOC_FREE_INFO_T * pMod);
int AUDIO_GeMultiConnectiionOutPortNum( LX_AUD_ALLOC_FREE_INFO_T * pMod);

 ADEC_MODULE_ID _AUDIO_GetManagerModule(ADEC_MODULE_ID audioModule);

void  AUDIO_UpdateConnectionInfo (void );
void  AUDIO_UpdateAllocInfo (void );

int AUDIO_GetPort( LX_AUD_ALLOC_FREE_INFO_T * pMod , UINT32 inOut, UINT8 HasMultiSink);
int AUDIO_FreePort( LX_AUD_ALLOC_FREE_INFO_T * pMod , UINT32 inOut, UINT32 portNumToFree);

LX_AUD_ALLOC_FREE_INFO_T * AUDIO_GetAllocDevInfo( LX_AUD_ALLOC_DEV_T alloc);
LX_AUD_ALLOC_FREE_INFO_T * AUDIO_GetAllocModInfo( LX_AUD_ALLOC_MOD_T alloc);
LX_AUD_ALLOC_FREE_INFO_T * AUDIO_GetDev(	LX_AUD_DEV_TYPE_T devType,  LX_AUD_SUB_MOD_T wantedSubModule);

int AUDIO_SetBypassMode( UINT32 allocMod_Bypass, UINT32 mode , UINT32 over_protect );
int AUDIO_DisconnectAllInDev ( UINT32 allocDev);
int AUDIO_ForceRemainedDisconnectBetweenDEVs( LX_AUD_ALLOC_MOD_T checkMod, UINT32 inOutExtraConnection);
LX_AUD_ALLOC_MOD_T  AUDIO_GetInOutModOfThisModule( LX_AUD_ALLOC_MOD_T checkMod, UINT32 inOutExtraConnection);

int	KDRV_AUDIO_ResetManagerParam(void);
extern LX_AUD_MOD_INFO_T ModInfo;
extern LX_AUD_DEV_INFO_T DevInfo;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _AUDIO_DRV_MANAGER_MGR_H_ */


