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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.02.19
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

#ifndef _DE_IO_h
#define _DE_IO_h
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

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int DE_IO_Init(unsigned long arg);
int DE_IO_GetFirmwareInfo(unsigned long arg);
int DE_IO_GetInputWin(unsigned long arg);
int DE_IO_GetOutWin(unsigned long arg);
int DE_IO_SetInputWin(unsigned long arg);
int DE_IO_SetOutWin(unsigned long arg);
int DE_IO_SetInputSrc(unsigned long arg);
int DE_IO_SetDisOut(unsigned long arg);
int DE_IO_SetMultiWin(unsigned long arg);
int DE_IO_SetCviSrcType(unsigned long arg);
int DE_IO_GetCviCsc(unsigned long arg);
int DE_IO_SetCviCsc(unsigned long arg);
int DE_IO_GetPostCsc(unsigned long arg);
int DE_IO_SetPostCsc(unsigned long arg);
int DE_IO_GetMviColorimetry(unsigned long arg);
int DE_IO_SetZList(unsigned long arg);
int DE_IO_SetDisFmt(unsigned long arg);
int DE_IO_SetFrRate(unsigned long arg);
int DE_IO_SetBgColor(unsigned long arg);
int DE_IO_SetFreeze(unsigned long arg);
int DE_IO_GetMviTimingInfo(unsigned long arg);
int DE_IO_SetWinBlank(unsigned long arg);
int DE_IO_MultiWinEnable(unsigned long arg);
int DE_IO_RegRd(unsigned long arg);
int DE_IO_RegWr(unsigned long arg);
int DE_IO_GetCaptureWin(unsigned long arg);
int DE_IO_SetCaptureWin(unsigned long arg);
int DE_IO_GetOutFrRate(unsigned long arg);
int DE_IO_SetIrePattern(unsigned long arg);
int DE_IO_GrabPixel(unsigned long arg);
int DE_IO_SetSpread(unsigned long arg);
int DE_IO_SetDeinterlace(unsigned long arg);
//int DE_IO_Set3DSrcMux(unsigned long arg);
int DE_IO_SetPre3DInMode(unsigned long arg);
//int DE_IO_SetPre3DOutMode(unsigned long arg);
//int DE_IO_SetPre3DInCH(unsigned long arg);
//int DE_IO_SetPre3DEnable(unsigned long arg);
int DE_IO_SetPre3DOprMode(unsigned long arg);
int DE_IO_SetFull3DMode(unsigned long arg);
int DE_IO_SetUDMode(unsigned long arg);
int DE_IO_SetCve(unsigned long arg);
int DE_IO_SetVcs(unsigned long arg);
int DE_IO_SetUart4MCU(unsigned long arg);

int DE_IO_OIF_Init(unsigned long arg);
int DE_IO_OIF_SetLvdsOutput(unsigned long arg);
int DE_IO_OIF_SetLvdsPower(unsigned long arg);
int DE_IO_OIF_SetDarkScreen(unsigned long arg);
int DE_IO_OIF_SetVesaJeida(unsigned long arg);
int DE_IO_OIF_SetPanelIf(unsigned long arg);
int DE_IO_OIF_SetPixel(unsigned long arg);
int DE_IO_OIF_SetBitDepth(unsigned long arg);
int DE_IO_OIF_SelectOutPath(unsigned long arg);
int DE_IO_OIF_SelectOutCh(unsigned long arg);
int DE_IO_OIF_SelectLedPath(unsigned long arg);
int DE_IO_OIF_SelectPwmPath(unsigned long arg);
int DE_IO_OIF_SelectLrPath(unsigned long arg);
int DE_IO_OIF_GetInfo(unsigned long arg);
int DE_IO_OIF_SelectLvdsPath(unsigned long arg);
int DE_IO_OIF_SetLvdsOutCtrl(unsigned long arg);
int DE_IO_OIF_SetLvdsPortSwap(unsigned long arg);

int DE_IO_SetTable(unsigned long arg);

#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_IO_FW_Download(unsigned long arg);
#endif

int DE_IO_SetCviFir(unsigned long arg);
int DE_IO_SetCviTpg(unsigned long arg);
int DE_IO_SetCviCsampleMode(unsigned long arg);
int DE_IO_SetCviSyncReshape(unsigned long arg);
int DE_IO_SetPeTestPatternGen(unsigned long arg);
int DE_IO_SetPeBbdCtrl(unsigned long arg);
int DE_IO_GetPeBbdStatus(unsigned long arg);
int DE_IO_SetEdgeCrop(unsigned long arg);
#ifdef USE_DE_SUSPEND
int	DE_IO_probe(void);
int	DE_IO_remove(void);
int	DE_IO_resume(void);
#endif
int DE_IO_SetPwmControl(unsigned long arg);
int DE_IO_SetPwmDutyCycle(unsigned long arg);
int DE_IO_SetPwmFrequency(unsigned long arg);
int DE_IO_SetPwmPulseWidth(unsigned long arg);
int DE_IO_GetPwmDutyExternal(unsigned long arg);
int DE_IO_SetDvrFmtCtrl(unsigned long arg);
int DE_IO_FC_SetWinInfo(unsigned long arg);
int DE_IO_FC_GetFrameInfo(unsigned long arg);
int DE_IO_SetSubScFreeze(unsigned long arg);
int DE_IO_SetCviVideoFrameBuffer(unsigned long arg);
int DE_IO_SelectMultiWinSrc(unsigned long arg);
int DE_IO_SetScartRGBBypassMode(unsigned long arg);
int DE_IO_GetCviInfo(unsigned long arg);
int DE_IO_SetCviFreeze(unsigned long arg);
int DE_IO_GetDebug(unsigned long arg);
int DE_IO_SetDebug(unsigned long arg);
int DE_IO_SetCpuMviPort(unsigned long arg);
int DE_IO_GetCpuMviPort(unsigned long arg);
int DE_IO_Set3DInfoThroughMiddleware(unsigned long arg);
int DE_IO_Get3DInfoThroughMiddleware(unsigned long arg);
int DE_IO_SetLowDelay(unsigned long arg);
int DE_IO_GetLowDelay(unsigned long arg);
int DE_IO_GetParInfo(unsigned long arg);
int DE_IO_Set3DInOutCtrl(unsigned long arg);

int DE_IO_SetInSrc(unsigned long arg);
int DE_IO_SetVdecMemShare(unsigned long arg);
int DE_IO_SetInterfaceConfig(unsigned long arg);
int DE_IO_GetSystemStatus(unsigned long arg);
int DE_IO_GetSourceStatus(unsigned long arg);
int DE_IO_SetOperation(unsigned long arg);
int DE_IO_SetSubOperation(unsigned long arg);
int DE_IO_SetCaptureControl(unsigned long arg);
int DE_IO_SetMultiVision(unsigned long arg);
int DE_IO_SetFrameToOsd(unsigned long arg);
int DE_IO_GetFrameForOsd(unsigned long arg);
int DE_IO_GetScalerInfo(unsigned long arg);
/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif
/**  @} */
