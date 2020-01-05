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

#ifndef	_VENC_CFG_H_
#define	_VENC_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define VENC_USE_LOCK
//#define VENC_ENABLE_DEBUG
#define VENC_BIT_RATE_BUFFER	10

// 2ndTV 및 Wifi play를 위해 TS생성 문제에 대한 workaround로
// DVR 블럭을 통하지 않고 직접 down하기 위한 코드 추가
#define VENC_ENABLE_TS_OUT

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	VENC_MODULE			"venc"
#define VENC_MAX_DEVICE		1
#define VENC_MAX_MEM_CONFIG	3

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	char*	pcMEMName;
	UINT32	uiMEMBase;
	UINT32	uiMEMSize;
} LX_VENC_MEM_CFG_T;

typedef struct
{
	char*	pcSRAMName;
	UINT32	uiSRAMBase;
	UINT32	uiSRAMSize;

	char*	pcSROMName;
	UINT32	uiSROMBase;
	UINT32	uiSROMSize;

	char*	pcFrameBufName;
	UINT32	uiFrameBufBase;
	UINT32	uiFrameBufSize;

	char*	pcDPBName;
	UINT32	uiDPBBase;
	UINT32	uiDPBSize;

	char*	pcESBufName;
	UINT32	uiESBufBase;
	UINT32	uiESBufSize;

	char*	pcAUIBufName;
	UINT32	uiAUIBufBase;
	UINT32	uiAUIBufSize;

	char*	pcInBufName;
	UINT32	uiInBufBase;
	UINT32	uiInBufSize;

	char*	pcScalerName;
	UINT32	uiScalerBase;
	UINT32	uiScalerSize;

	char*	pcAESBufName;
	UINT32	uiAESBufBase;
	UINT32	uiAESBufSize;

	char*	pcAAUIBufName;
	UINT32	uiAAUIBufBase;
	UINT32	uiAAUIBufSize;

#if 0
	// For L8 platform
	char*	pcScalarOutName;
	UINT32	uiScalarOutBase;
	UINT32	uiScalerOutSize;

	char*	pcPNGBufName;
	UINT32	uiPNGBufBase;
	UINT32	uiPNGBufSize;
#endif

#ifdef VENC_ENABLE_TS_OUT
	char*	pcTSBufName;
	UINT32	uiTSBufBase;
	UINT32	uiTSBufSize;
#endif /* VENC_ENABLE_TS_OUT */

#ifdef VENC_USE_H1ENCODE
	char*	pcH1EncBufName;
	UINT32	uiH1EncBufBase;
	UINT32	uiH1EncBufSize;
#endif

} LX_VENC_MEM_CFG_S_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void VENC_CFG_MemoryMap ( void );

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern LX_VENC_MEM_CFG_S_T *gpstVencMemConfig;
extern LX_VENC_MEM_CFG_T gMemCfgVenc[VENC_MAX_MEM_CONFIG];


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VENC_CFG_H_ */

/** @} */

