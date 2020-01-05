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
 *  driver interface header for demod device. ( used only within kdriver )
 *	demod device will teach you how to make device driver with new platform.
 *
 *  @author		jeongpil.yun (jeongpil.yun@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#ifndef	_DEMOD_HAL_H_
#define	_DEMOD_HAL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "demod_kapi.h"
#include "demod_module.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef	struct
{
	const LX_DEMOD_CFG_T*	(*GetCfg)		(void);


/***********************************************************************************
* DVBT/ DVBC/ VSB/ QAM/ ISDBT  common  function
************************************************************************************/


	int (*ResetHW)							(void);	//jeongpil.yun
	int (*SetI2C)							(void);	//jeongpil.yun
	int (*SetInclk)							(LX_DEMOD_INCLK_SEL_T *inclk);	//jeongpil.yun

	int (*Get_Id)							(UINT16 *pId);	//jeongpil.yun
	int (*RepeaterEnable)					(BOOLEAN bEnable);
	int (*SoftwareReset)					(void);
	int (*Serial_Control)					(BOOLEAN bEnable);
	int (*Power_Save)						(BOOLEAN bEnable);
	int (*StdOperModeContrl)				(LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr);
	int (*NeverlockScan)					(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock);
	int (*TPOutCLKEnable)					(BOOLEAN bEnable);
	int (*Set_IF_Frq)						(UINT32 ifFrq);
	int (*Set_AGCPolarity)					(LX_DEMOD_AGC_POLAR_T agcPola);
	int (*Set_SpectrumCtrl)					(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable);
	int (*Get_SpectrumStatus)				(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv);
	int (*Get_IFAGC)						(UINT16 *pIfAgc);
	int (*Get_OperMode)						(LX_DEMOD_OPER_MODE_T *pOperMode);
	int (*Get_NeverLockStatus)				(LX_DEMOD_OPER_MODE_T scanMode, LX_DEMOD_LOCK_STATE_T *pNeverLockStatus);
	int (*Get_CarrierFreqOffset)			(SINT32 *pFreqOff);
	int (*Get_TPIFStatus)					(BOOLEAN *pbEnable);
	int (*Get_VABER)						(UINT32 *pVber);
	int (*Get_Packet_Error)					(UINT32 *pError);
	int (*Get_BandWidthMode)				(LX_DEMOD_BWMODE_T *ChannelBW );
	int (*Get_QAMMode)						(LX_DEMOD_RF_MODE_T *pQamMode );
	int (*Get_MseInfo)						(LX_DEMOD_MSE_T *pSigMse);
	int (*Get_Lock)							(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState);


/***********************************************************************************
* DVBT/ DVBC common  function
************************************************************************************/


/***********************************************************************************
* DVBC function
************************************************************************************/

	int (*DVBC_AutoSymbolRateDet)			(LX_DEMOD_SYMRDET_MODE_T symrateMode, UINT16 SymbolRate);
	int (*DVBC_IsSymbolRateAuto)			(BOOLEAN *bAuto);
	int (*DVBC_IsQammodeAutoDet)			(BOOLEAN *bAutoQam);
	int (*DVBC_Set_DefaultRegisterValue)	(void);
	int (*DVBC_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBC_Set_QamMode) 				(UINT8 constel);
	int (*DVBC_Set_NeverLockWaitTime)		(UINT32 waitMs);
	int (*DVBC_Get_SymbolRateDetect)		(UINT16 *pSymbolRate);
	int (*DVBC_Get_SymbolRateStatus)		(LX_DEMOD_SYMBOLRATE_STATE_T *pSymbolRateDet);
	int (*DVBC_Get_QamModeDetectStatus)		(LX_DEMOD_QAMMODE_STATE_T *pQamModeDet);
	int (*DVBC_Get_DvbInfo)					(void);

	int (*DVBC_Obtaining_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);
	int (*DVBC_Monitoring_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);





/***********************************************************************************
* DVBT function
************************************************************************************/

	int (*DVBT_Set_DefaultRegisterValue)	(LX_DEMOD_BWMODE_T band);
	int (*DVBT_Set_Config_auto)				(BOOLEAN bAutoDetect);
	int (*DVBT_Set_PartialConfig)			(LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam);
	int (*DVBT_Set_FullConfig)				(LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam);
	int (*DVBT_Set_NeverLockWaitTime)		(UINT32 waitMs);
	int (*DVBT_Get_DelaySpreadStatus)		(UINT16 *pDelaySpread);
	int (*DVBT_Get_Hierach_HPSel)			(BOOLEAN *pBSetHp );
	int (*DVBT_Get_FFTMode)					(LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
	int (*DVBT_Get_GuradIntervalMode)		(LX_DEMOD_GIMODE_T *pGIMode );
	int (*DVBT_Get_HierachyMode)			(LX_DEMOD_DVB_TPS_HIERACHY_T *pHierachMode );
	int (*DVBT_Get_LpCoderRate)				(LX_DEMOD_CODERATE_T *pLpCodeRate );
	int (*DVBT_Get_HpCoderRate)				(LX_DEMOD_CODERATE_T *pHpCodeRate );
	int (*DVBT_Get_CellId)					(UINT8 *pCellIDLength, UINT16 *cell_id);
	int (*DVBT_Get_TpsInfo)					(LX_DEMOD_DVBT_CONFIG_T *pTpsParams);
	int (*DVBT_Get_TotalInfo)				(void);
	int (*DVBT_Get_IFO_LOCK)				(BOOLEAN *pIfoLock);
	int (*DVBT_Get_CochanDetIndicator)		(BOOLEAN *pDetStatus);
	int (*DVBT_EqualizereReset)				(void);

	int (*DVBT_Obtaining_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);
	int (*DVBT_Monitoring_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);



/***********************************************************************************
* VSB/ QAM/ ISDBT common  function
************************************************************************************/



/***********************************************************************************
* VSB function
************************************************************************************/

	int (*VSB_Set_DefaultRegisterValue)		(void);	//jeongpil.yun
	int (*VSB_Set_NeverLockWaitTime)		(UINT32 waitMs);
	int (*VSB_CochannelExist)				(BOOLEAN *pCochannel);  //jeongpil.yun
	int (*VSB_PreMonitor)					(void);
	int (*VSB_Monitor)						(DEMOD_CTX_T *pDemodInfo);
	int (*VSB_Get_MSEdynStatus)				(BOOLEAN *pbEnable);
	int (*VSB_Get_TotalInfo)				(void);

	int (*VSB_Obtaining_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);
	int (*VSB_Monitoring_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);


/***********************************************************************************
* QAM function
************************************************************************************/

	int (*QAM_SoftwareResetFEC)				(void); //jeongpil.yun
	int (*QAM_Monitor)						(void);
	int (*QAM_ModeAutoDetection)			(BOOLEAN bEnable);
	int (*QAM_64Mode)						(void);  //jeongpil.yun
	int (*QAM_256Mode)						(void);  //jeongpil.yun
	int (*QAM_Set_DefaultRegisterValue)		(void);	//jeongpil.yun
	int (*QAM_Set_NeverLockWaitTime)		(UINT32 waitMs);

	int (*QAM_Get_TotalInfo)				(void);

	int (*QAM_Obtaining_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);
	int (*QAM_Monitoring_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);
	int (*QAM_EQ_Signal_Detector)			(BOOLEAN OnOff);
	




/***********************************************************************************
* ISDBT function
************************************************************************************/

	int (*ISDBT_Set_DefaultRegisterValue)	(void);
	int (*ISDBT_Set_Config_auto)			(BOOLEAN bAutoDetect);
	int (*ISDBT_Set_PartialConfig)			(LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
	int (*ISDBT_Set_FullConfig)				(LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam);
	int (*ISDBT_Set_NeverLockWaitTime)		(UINT32 waitMs);
	int (*ISDBT_Get_DelaySpreadStatus)		(UINT16 *pDelaySpread);
	int (*ISDBT_Get_FFTMode)				(LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode );
	int (*ISDBT_Get_GuradIntervalMode)		(LX_DEMOD_GIMODE_T *pGIMode );
	int (*ISDBT_Get_TMCCInfo)				(LX_DEMOD_ISDBT_TMCC_CONFIG_T *pTmccParams);
	int (*ISDBT_Get_TotalInfo)				(void);
	int (*ISDBT_Get_IFO_LOCK)				(BOOLEAN *pIfoLock);
	int (*ISDBT_Get_CochanDetIndicator)		(BOOLEAN *pDetStatus);
	int (*ISDBT_EqualizereReset)			(void);

	int (*ISDBT_Obtaining_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);
	int (*ISDBT_Monitoring_Signal_Lock)		(DEMOD_CTX_T *pDemodInfo);


}
DEMOD_HAL_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	DEMOD_HAL_T	g_demod_hal;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _GFX_HAL_H_ */

