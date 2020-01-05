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
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */


#ifndef _SDEC_HAL_H
#define _SDEC_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sdec_kapi.h"
#include "sdec_io.h"

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define LX_SDEC_HAL_CHECK_CH(pSdecConf, ch) { \
__CHECK_IF_ERROR(ch >= pSdecConf->nChannel, SDEC_DEBUG_Print, goto exit , "Over channel range[ch:%d]", ch);\
	}

#define LX_SDEC_HAL_CHECK_PARAM(x) { \
__CHECK_IF_ERROR(x == NULL, SDEC_DEBUG_Print, goto exit , "parameter is NULL!\n");\
	}

#define LX_SDEC_HAL_CHECK_RET(x) { \
__CHECK_IF_ERROR(x != 0, SDEC_DEBUG_Print, goto exit, "Error! [E = %d]\n", x);\
	}


#define KADP_APVR_CHECK_RESULT(x) { \
	SDEC_DEBUG_Print("%s", (x == RET_OK) ? "OK" : " FAIL"); \
	}

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

enum
{
	SDEC_HAL_DISABLE = 0,
	SDEC_HAL_ENABLE = 1,
};

typedef enum{
	 SDEC_HAL_CDIOP_SERIAL_0		= 0x0,
	 SDEC_HAL_CDIOP_SERIAL_1		= 0x1
 }SDEC_HAL_CDIOP_PCONF_T;

typedef enum{
	 SDEC_HAL_CDIP_SERIAL_0		= 0x0,
	 SDEC_HAL_CDIP_SERIAL_1		= 0x1,
	 SDEC_HAL_CDIP_PARALLEL_0	= 0x2,
	 SDEC_HAL_CDIP_PARALLEL_1	= 0x3
 }SDEC_HAL_CDIP_PCONF_T;

typedef enum{
	 SDEC_HAL_CDIP_47DETECTION	= 0x0,
	 SDEC_HAL_CDIP_NEG_SOP		= 0x1,
	 SDEC_HAL_CDIP_POS_SOP		= 0x2,
	 SDEC_HAL_CDIP_BOTH_SOP		= 0x3
 }SDEC_HAL_CDIP_SYNC_TYPE_T;

typedef enum{
	SDEC_HAL_CDIP_MPEG2TS		= 0x0,
	SDEC_HAL_CDIP_VIDEOSTREAM	= 0xA,
	SDEC_HAL_CDIP_MUXEDSTREAM	= 0xB
 }SDEC_HAL_CDIP_DTYPE_T;

enum {
	SDEC_HAL_CDIP_SERIAL = 0,
	SDEC_HAL_CDIP_PARALLEL = 1,
};

enum {
	SDEC_HAL_CDIP_CLK_ACT_HIGH 	= 0,
	SDEC_HAL_CDIP_CLK_ACT_LOW 	= 1,
};

enum {
	SDEC_HAL_CDIP_VAL_DISABLE 	= 0,
	SDEC_HAL_CDIP_VAL_ENABLE		= 1,
};

enum {
	SDEC_HAL_CDIOP_IN = 0,
	SDEC_HAL_CDIOP_OUT = 1,
};

enum {
	SDEC_HAL_CDIP_FIRST = 0,
	SDEC_HAL_CDIP_FOLLOWER = 1,
};

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *  structre
 *----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *  API
 *----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

int SDEC_HAL_TOPInit(void);
int SDEC_HAL_IOInit(void);
int SDEC_HAL_MPGInit(void);
/* HAL for TOP register */
int SDEC_HAL_SetVideoOut(UINT8 idx, UINT8 sel);
int SDEC_HAL_SetPVRSrc(UINT8 idx, UINT8 sel);
/* HAL for IO register */
int SDEC_HAL_SetGPBBaseAddr(UINT8 gpb_base);
UINT32 SDEC_HAL_GetSTCCErrorCtrl(UINT8 idx);
int SDEC_HAL_SetSTCCErrorCtrl(UINT8 idx, UINT32 err_max, UINT8 en);
int SDEC_HAL_SDMWCLastBValidMode(UINT8 en);
int SDEC_HAL_EnableVideoReady(UINT8 idx, UINT8 en);
int SDEC_HAL_EnableAudioReady(UINT8 idx, UINT8 en);
int SDEC_HAL_EnableAutoIncr(UINT8 en);
int SDEC_HAL_SetTs2PesPid(UINT16 pid);
UINT16 SDEC_HAL_GetTs2PesPid(void);
UINT32 SDEC_HAL_IntrStatReadAndClear(void);
UINT32 SDEC_HAL_GetErrorInterruptStat(void);
int SDEC_HAL_EnableInterrupt(E_SDEC_INTR_T eSdecIntrSrc, UINT8 en);
int SDEC_HAL_EnableErrorInterrupt(E_SDEC_ERRINTR_T eSdecErrIntr, UINT8 val);
int SDEC_HAL_SDMWCReset(UINT32 val);
UINT32 SDEC_HAL_SDMWCGet(void);
UINT32 SDEC_HAL_SDMWCGetStatus(void);
UINT32 SDEC_HAL_STCCGetASG(void);
UINT8 SDEC_HAL_STCCGetMain(void);
int SDEC_HAL_STCCSetMain(UINT8 ch);
int SDEC_HAL_STCCSetVideoAssign(UINT8 idx, UINT8 ch);
int SDEC_HAL_STCCSetAudioAssign(UINT8 idx, UINT8 ch);
UINT32 SDEC_HAL_STCCGetReg(UINT8 ch);
int SDEC_HAL_STCCSetReg(UINT8 ch, UINT32 val);
int SDEC_HAL_STCCSetSTC(UINT8 ch, UINT32 val);
UINT32 SDEC_HAL_STCCGetSTC(UINT8 ch, UINT8 isHigh);
UINT32 SDEC_HAL_STCCGetPCR(UINT8 ch, UINT8 isHigh);
int SDEC_HAL_STCCEnable(UINT8 ch, UINT8 en);
int SDEC_HAL_STCCReset(UINT8 ch);
int SDEC_HAL_STCCSetCh(UINT8 ch, UINT8 chan);
int SDEC_HAL_STCCEnableCopy(UINT8 ch, UINT8 en);
int SDEC_HAL_STCCEnableLatch(UINT8 ch, UINT8 en);
int SDEC_HAL_AVSTCReset(UINT8 ch);
int SDEC_HAL_STCCSetPCRPid(UINT8 ch, UINT16 pid);
int SDEC_HAL_STCCSetSubStccRate(UINT32 val);
UINT32 SDEC_HAL_STCCGetSubStccRate(void);
int SDEC_HAL_GSTC(UINT32 *pStcc_41_10, UINT32 *pStcc_9_0);
int SDEC_HAL_GSTCReset(void);
int SDEC_HAL_DSCSetCasType(UINT8 ch, UINT8 val);
int SDEC_HAL_DSCSetBlkMode(UINT8 ch, UINT8 val);
int SDEC_HAL_DSCSetResMode(UINT8 ch, UINT8 val);
int SDEC_HAL_DSCSetKeySize(UINT8 ch, UINT8 val);
int SDEC_HAL_DSCEnablePESCramblingCtrl(UINT8 ch, UINT8 en);
int SDEC_HAL_DSCSetEvenMode(UINT8 ch, UINT8 val);
int SDEC_HAL_DSCSetOddMode(UINT8 ch, UINT8 val);
int SDEC_HAL_SetParallelInput(UINT8 isExternal);
int SDEC_HAL_CDIPEnable(UINT8 ch, UINT8 en);
int SDEC_HAL_CIDCReset(UINT8 ch);
int SDEC_HAL_CIDCMinSyncByteDetection(UINT8 ch, UINT8 val);
int SDEC_HAL_CIDCMaxSyncByteDrop(UINT8 ch, UINT8 val);
int SDEC_HAL_CIDCSetSrc(UINT8 ch, UINT8 val);
int SDEC_HAL_CIDCRead(UINT8 ch, UINT32 *pVal);
int SDEC_HAL_CIDCGetStatus(UINT8 ch, CDIC *pCdic);
UINT8 SDEC_HAL_CIDCGetCdif_OverFlow(UINT8 ch);
UINT8 SDEC_HAL_CIDCGetCdif_Full(UINT8 ch);
UINT32 SDEC_HAL_CIDCGet(UINT8 ch);
int SDEC_HAL_CIDC3DlConf(UINT8 ch, UINT8 val);
//int SDEC_HAL_CDIP(UINT8 idx,	UINT8 isParallel, UINT8 isFirst, UINT8 isClockActLow, UINT8 isValEnable);
//int SDEC_HAL_CDIOP(UINT8 idx, UINT8 inout, UINT8 isClockActLow, UINT8 isValEnable);
int SDEC_HAL_CDIP(UINT8 idx,	LX_SDEC_CFG_INPUT_T *pCfg);
int SDEC_HAL_CDIOP(UINT8 idx,	LX_SDEC_CFG_INPUT_T *pCfg);
int SDEC_HAL_CDIOPEnable(UINT8 ch, UINT8 en);
int SDEC_HAL_CDIPAEnable(UINT8 ch, UINT8 en);
int SDEC_HAL_CDIPA(UINT8 idx,	LX_SDEC_CFG_INPUT_T *pCfg);

/* ~ H13A0 CDIC2 PID Filter Related */
int SDEC_HAL_EnableCDIC2PIDFWrite(UINT8 en);
int SDEC_HAL_CDIC2PIDFSetPidfData(UINT8 idx, UINT32 val);
UINT32 SDEC_HAL_CDIC2PIDFGetPidfData(UINT8 idx);
int SDEC_HAL_CDIC2PIDFEnablePidFilter(UINT8 idx, UINT8 en);
UINT8 SDEC_HAL_CDIC2GetPIDFEnable(UINT8 idx);
int SDEC_HAL_CDIC2DlExtConf(UINT8 ch, UINT8 val);

/* HAL for MPEG register */

TPI_ISTAT SDEC_HAL_TPIGetIntrStat(UINT8 ch);
SE_ISTAT SDEC_HAL_SEGetIntrStat(UINT8 ch);
int SDEC_HAL_ConfSetPESReadyCheck(UINT8 ch, UINT8 chk_ch, UINT8 val);
CHAN_STAT SDEC_HAL_GetChannelStatus(UINT8 ch);
UINT32 SDEC_HAL_GetChannelStatus2(UINT8 ch);
UINT8 SDEC_HAL_ChanStatGetMWFOverFlow(UINT8 ch);
UINT32 SDEC_HAL_CCCheckEnableGet(UINT8 ch, UINT8 idx);
int SDEC_HAL_CCCheckEnableSet(UINT8 ch, UINT8 idx, UINT32 val);
int SDEC_HAL_ExtConfSECIDcont(UINT8 ch, UINT8 val);
int SDEC_HAL_ExtConfSECICCError(UINT8 ch, UINT8 val);
int SDEC_HAL_ExtConfVideoDupPacket(UINT8 ch, UINT8 val);
int SDEC_HAL_ExtConfDcontDupPacket(UINT8 ch, UINT8 val);
int SDEC_HAL_ExtConfGPBOverWrite(UINT8 ch, UINT8 en);
int SDEC_HAL_ExtConfGPBFullLevel(UINT8 ch, UINT32 val);
int SDEC_HAL_TPISetIntrPayloadUnitStartIndicator(UINT8 ch, UINT8 val);
int SDEC_HAL_TPISetIntrAutoScCheck(UINT8 ch, UINT8 val);
int SDEC_HAL_GPBSetFullIntr(UINT8 ch, UINT8 loc);
int SDEC_HAL_GPBClearFullIntr(UINT8 ch, UINT8 loc);
UINT32 SDEC_HAL_GPBGetDataIntrStat(UINT8 ch, UINT8 isHigh);
UINT32 SDEC_HAL_GPBGetFullIntrStat(UINT8 ch, UINT8 idx);
UINT32 SDEC_HAL_GPBGetWritePtr(UINT8 ch, UINT8 idx);
UINT32 SDEC_HAL_GPBGetReadPtr(UINT8 ch, UINT8 idx);
int SDEC_HAL_GPBSetReadPtr(UINT8 ch, UINT8 idx, UINT32 val);
int SDEC_HAL_GPBSetWritePtr(UINT8 ch, UINT8 idx, UINT32 val);
UINT32 SDEC_HAL_GPBGetLowerBnd(UINT8 ch, UINT8 idx);
UINT32 SDEC_HAL_GPBGetUpperBnd(UINT8 ch, UINT8 idx);
int SDEC_HAL_GPBSetBnd(UINT8 ch, UINT8 idx, UINT32 l_bnd, UINT32 u_bnd);

UINT32 SDEC_HAL_SECFGetLinkedMap(UINT8 ch, UINT8 idx);
UINT32 SDEC_HAL_SECFGetMap(UINT8 ch, UINT8 idx);
int SDEC_HAL_SECFSetMap(UINT8 ch, UINT8 idx, UINT32 val);
int SDEC_HAL_SECFSetMapBit(UINT8 ch, UINT8 idx, UINT8 loc);
int SDEC_HAL_SECFClearMapBit(UINT8 ch, UINT8 idx, UINT8 loc);
UINT32 SDEC_HAL_SECFGetEnable(UINT8 ch, UINT8 idx);
UINT8 SDEC_HAL_SECFGetEnableBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_SECFSetEnable(UINT8 ch, UINT8 idx, UINT32 val);
int SDEC_HAL_SECFSetEnableBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_SECFClearEnableBit(UINT8 ch, UINT8 loc);
UINT32 SDEC_HAL_SECFGetBufValid(UINT8 ch, UINT8 idx);
int SDEC_HAL_SECFSetBufValid(UINT8 ch, UINT8 idx, UINT32 val);
int SDEC_HAL_SECFSetBufValidBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_SECFClearBufValidBit(UINT8 ch, UINT8 loc);
UINT32 SDEC_HAL_SECFGetMapType(UINT8 ch, UINT8 loc);
UINT8 SDEC_HAL_SECFGetMapTypeBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_SECFSetMapType(UINT8 ch, UINT8 idx, UINT32 val);
int SDEC_HAL_SECFSetMapTypeBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_SECFClearMapTypeBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_SECFSetCRCBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_SECFClearCRCBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_PIDFSetCRCBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_PIDFClearCRCBit(UINT8 ch, UINT8 loc);
int SDEC_HAL_PIDFSetPidfData(UINT8 ch, UINT8 idx, UINT32 val);
UINT32 SDEC_HAL_PIDFGetPidfData(UINT8 ch, UINT8 idx);
int SDEC_HAL_PIDFEnable(UINT8 ch, UINT8 idx, UINT8 en);
int SDEC_HAL_PIDFScrambleCheck(UINT8 ch, UINT8 idx, UINT8 en);
int SDEC_HAL_PIDFDescEnable(UINT8 ch, UINT8 idx, UINT8 en);
int SDEC_HAL_PIDFDownloadEnable(UINT8 ch, UINT8 idx, UINT8 en);
int SDEC_HAL_SECFSetSecfData(UINT8 ch, UINT8 secf_idx, UINT8 word_idx, UINT32 val);
UINT32 SDEC_HAL_SECFGetSecfData(UINT8 ch, UINT8 secf_idx, UINT8 word_idx);
int SDEC_HAL_KMEMSet(UINT8 ch, UINT8 key_type, UINT8 pid_idx, UINT8 odd_key, UINT8 word_idx, UINT32 val);
UINT32 SDEC_HAL_KMEMGet(UINT8 ch, UINT8 key_type, UINT8 pid_idx, UINT8 odd_key, UINT8 word_idx);

void SDEC_VDECHAL_PDECInit(void);
void SDEC_VDECHAL_TOPSetPdecInputSelection(UINT8 ui8TeCh);
UINT8 SDEC_VDECHAL_TOPGetPdecInputSelection(void);
void SDEC_VDECHAL_TOPEnablePdecInput(BOOLEAN bEnable);
void SDEC_VDECHAL_TOPEnableExtIntr(UINT32 ui32IntrSrc);
void SDEC_VDECHAL_TOPDisableExtIntr(UINT32 ui32IntrSrc);
void SDEC_VDECHAL_TOPClearExtIntr(UINT32 ui32IntrSrc);
void SDEC_VDECHAL_TOPClearExtIntrMsk(UINT32 ui32IntrMsk);
void SDEC_VDECHAL_TOPDisableExtIntrAll(void);
void SDEC_VDECHAL_PDECReset(void);
void SDEC_VDECHAL_PDECEnable(void);
void SDEC_VDECHAL_PDECDisable(void);
void SDEC_VDECHAL_PDECSetVideoStandard(UINT8 ui8Vcodec);
void SDEC_VDECHAL_PDECCPB_Init(UINT32 ui32CpbBase, UINT32 ui32CpbSize);
UINT32 SDEC_VDECHAL_PDECGetCPBBase(void);
UINT32 SDEC_VDECHAL_PDECGetCPBSize(void);
UINT32 SDEC_VDECHAL_PDECCPB_GetWrPtr(void);
void SDEC_VDECHAL_PDECCPB_SetWrPtr(UINT32 ui32CpbRdPtr);
UINT32 SDEC_VDECHAL_PDECCPB_GetRdPtr(void);
void SDEC_VDECHAL_PDECCPB_SetRdPtr(UINT32 ui32CpbRdPtr);
void SDEC_VDECHAL_PDECCPB_Reset(void);
void SDEC_VDECHAL_PDECSetBypass(void);
void SDEC_VDECHAL_PDECEnableUserDefinedSCD(UINT8 ui8ScdIdx);
void SDEC_VDECHAL_PDECSetUserDefinedSCD(UINT32 ui32Val);
void SDEC_VDECHAL_PDECBDRC_Enable(BOOLEAN bEnable);
void SDEC_VDECHAL_PDECBDRC_Init(UINT32 bufBase, UINT32 bufSize);
void SDEC_VDECHAL_PDECBDRC_Update(void);
void SDEC_VDECHAL_PDECBDRC_SetWPtr(UINT32 wptr);

#ifdef __cplusplus
}
#endif

#endif /* _SDEC_HAL_H */

