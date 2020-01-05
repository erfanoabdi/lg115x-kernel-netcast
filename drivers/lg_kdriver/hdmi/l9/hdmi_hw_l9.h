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
 * author     sh.myoung (sh.myoung@lge.com)
 * version    1.0
 * date       2012.05.01
 * note       Additional information.
 *
 * @addtogroup lg1154_hdmi
 * @{
 */
#ifndef  HDMI_HW_L9_INC
#define  HDMI_HW_L9_INC

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
int HDMI_L9_HWInitial(void);
int HDMI_L9_SetPort(UINT32 *port);
int HDMI_L9_GetMode(LX_HDMI_MODE_T *mode);
int HDMI_L9_GetAspectRatio(LX_HDMI_ASPECTRATIO_T *ratio);
int HDMI_L9_GetTimingInfo(LX_HDMI_TIMING_INFO_T *info);


int HDMI_L9_GetAudioInfo(LX_HDMI_AUDIO_INFO_T *audio_info);
int HDMI_L9_GetAviPacket(LX_HDMI_AVI_PACKET_T *packet);
int HDMI_L9_GetVsiPacket(LX_HDMI_VSI_PACKET_T *packet);
int HDMI_L9_GetSpdPacket(LX_HDMI_SPD_PACKET_T *packet);


int HDMI_L9_GetStatus(LX_HDMI_STATUS_T *status);

int HDMI_L9_SetHPD(LX_HDMI_HPD_T *hpd);
int HDMI_L9_SetMute(LX_HDMI_MUTE_CTRL_T *mute);
int HDMI_L9_SetArc(LX_HDMI_ARC_CTRL_T *arc);
int HDMI_L9_PowerConsumption(UINT32 power);
int HDMI_L9_SetUDn3DControl(LX_HDMI_UD_3D_MODE_T *udn3d);
int HDMI_L9_GetRegister(UINT32 addr , UINT32 *value);
int HDMI_L9_SetRegister(UINT32 addr , UINT32 value);



#ifdef	KDRV_CONFIG_PM
int HDMI_L9_RunSuspend(void);
int HDMI_L9_RunResume(void);
#endif

int HDMI_L9_SetPowerControl(UINT32 power);
int HDMI_L9_SetAudio(void);
void HDMI_L9_SetPixelRepetition(void);
void HDMI_L9_SetAutoSyncPolarity(void);
int HDMI_L9_RunReset(void);

irqreturn_t HDMI_L9_IRQHandler(int irq, void *dev);
void HDMI_L9_EnableInterrupt(void);
int HDMI_L9_GetPortConnection(void);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef DE_REG_L9_INC  ----- */
/**  @} */
