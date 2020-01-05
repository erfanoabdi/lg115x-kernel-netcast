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


/** @file pe_dnt_hw_l9.h
 *
 *  driver header for picture enhance deinterlacer. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_DNT_HW_L9_H_
#define	_PE_DNT_HW_L9_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

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
/**
 *	pe dnt ipc fmt
 */
typedef enum
{
	PE_DNT_L9_IPC_ATV_NTSC = 0,		///< atv ntsc
	PE_DNT_L9_IPC_ATV_PAL,			///< atv pal
	PE_DNT_L9_IPC_AV_NTSC,			///< av ntsc
	PE_DNT_L9_IPC_AV_PAL,			///< av pal
	PE_DNT_L9_IPC_DTV_SD_60,		///< dtv sd 60
	PE_DNT_L9_IPC_DTV_SD_50,		///< dtv sd 50
	PE_DNT_L9_IPC_HDMI_SD_60,		///< hdmi sd 60
	PE_DNT_L9_IPC_HDMI_SD_50,		///< hdmi sd 50
	PE_DNT_L9_IPC_HD,				///< hd
	PE_DNT_L9_IPC_NUM,				///< max num
}
PE_DNT_HW_L9_IPC_FMT;
/**
 *	pe dnt fmd fmt
 */
typedef enum
{
	PE_DNT_L9_FMD_ATV_60 = 0,		///< atv 60
	PE_DNT_L9_FMD_ATV_50,			///< atv 50
	PE_DNT_L9_FMD_AV_60,			///< cvbs 60
	PE_DNT_L9_FMD_AV_50,			///< cvbs 50
	PE_DNT_L9_FMD_DTV_SD_60,		///< dtv sd 60
	PE_DNT_L9_FMD_DTV_SD_50,		///< dtv sd 50
	PE_DNT_L9_FMD_DTV_HD,			///< dtv hd
	PE_DNT_L9_FMD_HDMI_SD_60,		///< hdmi sd 60
	PE_DNT_L9_FMD_HDMI_SD_50,		///< hdmi sd 50
	PE_DNT_L9_FMD_HD,				///< hd
	PE_DNT_L9_FMD_NUM,				///< max num
}
PE_DNT_HW_L9_FMD_FMT;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_DNT_HW_L9_SetDbgPrint(UINT32 on_off);
int PE_DNT_HW_L9_Init(void);
int PE_DNT_HW_L9_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNT_HW_L9_H_ */
