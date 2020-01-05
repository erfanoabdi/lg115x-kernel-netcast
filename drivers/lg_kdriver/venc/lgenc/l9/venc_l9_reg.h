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

#ifndef _VENC_L9_REG_h
 #define _VENC_L9_REG_h

#include "venc_l9_regipc.h"

#if 0
 #define VENC_REG_V1
 #undef  VENC_REG_V2
#else
 #define VENC_REG_V2
 #undef  VENC_REG_V1
#endif /* #if 0 */
/*********************************************************************************
 *  FILE NAME      : Reg_venc.h
 *  DESCRIPTION    : Register definition header file for VENC
 *  AUTHOR(s)      : D. Murugan     [murugan.d@lge.com]
 *  DEPENDENCIES   :
 *  REFERENCES     : DTVSoC_VENC_MCU_MAN_v1.0a(090826)
 *  HISTORY        :
 *  Date           Inititals            Modifications
 *  ===============================================================================
 *  17.Sep.09       Murugan             New development
 *  ===============================================================================
 *********************************************************************************/


/******************************************************************************
 * Preprocessor Defines
 ******************************************************************************/



/******************************************************************************
 * Register definitions
 ******************************************************************************/
/*-----------------------------------------------------------------------------
	0x0700 PROC_CTRL ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :29;	// 31: 3
		UINT32		pdbg_en                         : 1;	//     2
		UINT32		vec_sel                         : 1;	//     1
		UINT32		run_stall                       : 1;	//     0
	}be;
	struct {
		UINT32		run_stall                       : 1;	//     0
		UINT32		vec_sel                         : 1;	//     1
		UINT32		pdbg_en                         : 1;	//     2
		UINT32		_rsvd_00                        :29;	// 31: 3
	}le;
} PROC_CTRL;

/*-----------------------------------------------------------------------------
	0x0704 PROC_ID ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        : 8;	// 31:24
		UINT32		pdbg_st                         : 8;	// 23:16
		UINT32		proc_id                         :16;	// 15: 0
	}be;
	struct {
		UINT32		proc_id                         :16;	// 15: 0
		UINT32		pdbg_st                         : 8;	// 23:16
		UINT32		_rsvd_00                        : 8;	// 31:24
	}le;
} PROC_ID;

/*-----------------------------------------------------------------------------
	0x0708 PDBG_DATA ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		pdbg_data                       ;   	// 31: 0
	}be;
	struct {
		UINT32		pdbg_data                       ;   	// 31: 0
	}le;
} PDBG_DATA;

/*-----------------------------------------------------------------------------
	0x070c PDBG_PC ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		pdbg_pc                         ;   	// 31: 0
	}be;
	struct {
		UINT32		pdbg_pc                         ;   	// 31: 0
	}le;
} PDBG_PC;

/*-----------------------------------------------------------------------------
	0x0710 SROM_OFFSET ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		srom_start                      :20;	// 31:12
		UINT32		_rsvd_00                        :12;	// 11: 0
	}be;
	struct {
		UINT32		_rsvd_00                        :12;	// 11: 0
		UINT32		srom_start                      :20;	// 31:12
	}le;
} SROM_START;

/*-----------------------------------------------------------------------------
	0x0714 SRAM_OFFSET_0 ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		sram_start                      :20;	// 31:12
		UINT32		_rsvd_00                        :12;	// 11: 0
	}be;
	struct {
		UINT32		_rsvd_00                        :12;	// 11: 0
		UINT32		sram_start                      :20;	// 31:12
	}le;
} SRAM_START;

/*-----------------------------------------------------------------------------
	0x0720 AXI_PRI ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        : 5;	// 31:27
		UINT32		pngd_rd                         : 3;	// 26:24
		UINT32		_rsvd_01                        : 1;	//    23
		UINT32		dma_rd                          : 3;	// 22:20
		UINT32		_rsvd_02                        : 1;	//    19
		UINT32		core_rd                         : 3;	// 18:16
		UINT32		_rsvd_03                        : 5;	// 15:11
		UINT32		pngd_wr                         : 3;	// 10: 8
		UINT32		_rsvd_04                        : 1;	//     7
		UINT32		dma_wr                          : 3;	//  6: 4
		UINT32		_rsvd_05                        : 1;	//     3
		UINT32		core_wr                         : 3;	//  2: 0
	}be;
	struct {
		UINT32		core_wr                         : 3;	//  2: 0
		UINT32		_rsvd_05                        : 1;	//     3
		UINT32		dma_wr                          : 3;	//  6: 4
		UINT32		_rsvd_04                        : 1;	//     7
		UINT32		pngd_wr                         : 3;	// 10: 8
		UINT32		_rsvd_03                        : 5;	// 15:11
		UINT32		core_rd                         : 3;	// 18:16
		UINT32		_rsvd_02                        : 1;	//    19
		UINT32		dma_rd                          : 3;	// 22:20
		UINT32		_rsvd_01                        : 1;	//    23
		UINT32		pngd_rd                         : 3;	// 26:24
		UINT32		_rsvd_00                        : 5;	// 31:27
	}le;
} AXI_PRI;

/*-----------------------------------------------------------------------------
	0x0730 E_INTR_T ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :19;	// 31:13
		UINT32		pngd                        	: 1;	//    12
		UINT32		vsync                        	: 1;	//    11
		UINT32		ipc                             : 1;	//    10
		UINT32		dma                             : 1;	//     9
		UINT32		tso                             : 1;	//     8
		UINT32		token                           : 1;	//     7
		UINT32		deblock                         : 1;	//     6
		UINT32		vlc                             : 1;	//     5
		UINT32		venc                            : 1;	//     4
		UINT32		fme_qpel                        : 1;	//     3
		UINT32		fme_hpel                        : 1;	//     2
		UINT32		ime                             : 1;	//     1
		UINT32		cfc                             : 1;	//     0
	}be;
	struct {
		UINT32		cfc                             : 1;	//     0
		UINT32		ime                             : 1;	//     1
		UINT32		fme_hpel                        : 1;	//     2
		UINT32		fme_qpel                        : 1;	//     3
		UINT32		venc                            : 1;	//     4
		UINT32		vlc                             : 1;	//     5
		UINT32		deblock                         : 1;	//     6
		UINT32		token                           : 1;	//     7
		UINT32		tso                             : 1;	//     8
		UINT32		dma                             : 1;	//     9
		UINT32		ipc                             : 1;	//    10
		UINT32		vsync                        	: 1;	//    11
		UINT32		pngd                        	: 1;	//    12
		UINT32		_rsvd_00                        :19;	// 31:13
	}le;
} E_INTR_T;

/*-----------------------------------------------------------------------------
	0x073c E_INTR_EV ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :31;	// 31: 1
		UINT32		ipc                             : 1;	//     0
	}be;
	struct {
		UINT32		ipc                             : 1;	//     0
		UINT32		_rsvd_00                        :31;	// 31: 1
	}le;
} E_INTR_EV;

/*-----------------------------------------------------------------------------
	0x0740 I_INTR_T ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :21;	// 31:11
		UINT32		ipc                             : 1;	//    10
		UINT32		dma                             : 1;	//     9
		UINT32		tso                             : 1;	//     8
		UINT32		token                           : 1;	//     7
		UINT32		deblock                         : 1;	//     6
		UINT32		vlc                             : 1;	//     5
		UINT32		venc                            : 1;	//     4
		UINT32		fme_qpel                        : 1;	//     3
		UINT32		fme_hpel                        : 1;	//     2
		UINT32		ime                             : 1;	//     1
		UINT32		cfc                             : 1;	//     0
	}be;
	struct {
		UINT32		cfc                             : 1;	//     0
		UINT32		ime                             : 1;	//     1
		UINT32		fme_hpel                        : 1;	//     2
		UINT32		fme_qpel                        : 1;	//     3
		UINT32		venc                            : 1;	//     4
		UINT32		vlc                             : 1;	//     5
		UINT32		deblock                         : 1;	//     6
		UINT32		token                           : 1;	//     7
		UINT32		tso                             : 1;	//     8
		UINT32		dma                             : 1;	//     9
		UINT32		ipc                             : 1;	//    10
		UINT32		_rsvd_00                        :21;	// 31:11
	}le;
} I_INTR_T;

/*-----------------------------------------------------------------------------
	0x074c I_INTR_EV ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :31;	// 31: 1
		UINT32		ipc                             : 1;	//     0
	}be;
	struct {
		UINT32		ipc                             : 1;	//     0
		UINT32		_rsvd_00                        :31;	// 31: 1
	}le;
} I_INTR_EV;

/*-----------------------------------------------------------------------------
	0x0750 TSO_CMD ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :30;	// 31: 2
		UINT32		page                            : 1;	//     1
		UINT32		out_req                         : 1;	//     0
	}be;
	struct {
		UINT32		out_req                         : 1;	//     0
		UINT32		page                            : 1;	//     1
		UINT32		_rsvd_00                        :30;	// 31: 2
	}le;
} TSO_CMD;

/*-----------------------------------------------------------------------------
	0x0754 TSO_CONF ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :22;	// 31:10
		UINT32		ts_au                           : 1;	//     9
		UINT32		ts_type                         : 1;	//     8
		UINT32		ts_size                         : 8;	//  7: 0
	}be;
	struct {
		UINT32		ts_size                         : 8;	//  7: 0
		UINT32		ts_type                         : 1;	//     8
		UINT32		ts_au                           : 1;	//     9
		UINT32		_rsvd_00                        :22;	// 31:10
	}le;
} TSO_CONF;

/*-----------------------------------------------------------------------------
	0x0758 TSO_TSTAMP ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		tstamp                          ;   	// 31: 0
	}be;
	struct {
		UINT32		tstamp                          ;   	// 31: 0
	}le;
} TSO_TSTAMP;

/*-----------------------------------------------------------------------------
	0x0760 GSTCC_EN ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :30;	// 31: 2
		UINT32		aud_en                          : 1;	//     1
		UINT32		vid_en                          : 1;	//     0
	}be;
	struct {
		UINT32		vid_en                          : 1;	//     0
		UINT32		aud_en                          : 1;	//     1
		UINT32		_rsvd_00                        :30;	// 31: 2
	}le;
} GSTCC_EN;

/*-----------------------------------------------------------------------------
	0x0770 ENC_MCU_VER ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		yyyymmdd                        ;   	// 31: 0
	}be;
	struct {
		UINT32		yyyymmdd                        ;   	// 31: 0
	}le;
} ENC_MCU_VER;

/*-----------------------------------------------------------------------------
	0x0900 STC_CTRL ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		en                              : 1;	//    31
		UINT32		rst                             : 1;	//    30
		UINT32		_rsvd_01                        :30;	// 29: 0
	}be;
	struct {
		UINT32		_rsvd_01                        :30;	// 29: 0
		UINT32		rst                             : 1;	//    30
		UINT32		en                              : 1;	//    31
	}le;
} STC_CTRL;

/*-----------------------------------------------------------------------------
	0x0904 STC_BASE ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		stcc_41_10                      ;   	// 31: 0
	}be;
	struct {
		UINT32		stcc_41_10                      ;   	// 31: 0
	}le;
} STC_BASE;

/*-----------------------------------------------------------------------------
	0x0908 STC_EXT ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		_rsvd_00                        :22;	// 31:10
		UINT32		stcc_9_0                        :10;	//  9: 0
	}be;
	struct {
		UINT32		stcc_9_0                        :10;	//  9: 0
		UINT32		_rsvd_00                        :22;	// 31:10
	}le;
} STC_EXT;

/*-----------------------------------------------------------------------------
	0x0a00 TOKEN_INFO ''
------------------------------------------------------------------------------*/
typedef union  {
	UINT32	ui32Val;
	struct {
		UINT32		tok_info                        ;   	// 31: 0
	}be;
	struct {
		UINT32		tok_info                        ;   	// 31: 0
	}le;
} TOKEN_INFO;

typedef struct {
	PROC_CTRL                       	proc_ctrl                       ;	// 0x0700 : ''
	PROC_ID                         	proc_id                         ;	// 0x0704 : ''
	PDBG_DATA                       	pdbg_data                       ;	// 0x0708 : ''
	PDBG_PC                         	pdbg_pc                         ;	// 0x070c : ''
	SROM_START                      	srom_start                      ;	// 0x0710 : ''
	SRAM_START                      	sram_start0                      ;	// 0x0714 : ''
	SRAM_START                      	sram_start1                      ;	// 0x0718 : ''
	SRAM_START                      	sram_start2                      ;	// 0x071c : ''
	AXI_PRI                         	axi_pri                         ;	// 0x0720 : ''
	UINT32								axi_addr_sw_de_sav              ;	// 0x0724 : ''
	UINT32								axi_addr_sw_cpu_gpu             ;	// 0x0728 : ''
	UINT32								axi_addr_sw_cpu_shadow          ;	// 0x072c : ''
	E_INTR_T                       		e_intr_en                       ;	// 0x0730 : ''
	E_INTR_T                       		e_intr_st                       ;	// 0x0734 : ''
	E_INTR_T                       		e_intr_cl                       ;	// 0x0738 : ''
	E_INTR_EV                       	e_intr_ev                       ;	// 0x073c : ''
	I_INTR_T                       		i_intr_en                       ;	// 0x0740 : ''
	I_INTR_T                       		i_intr_st                       ;	// 0x0744 : ''
	I_INTR_T                       		i_intr_cl                       ;	// 0x0748 : ''
	I_INTR_EV                       	i_intr_ev                       ;	// 0x074c : ''
	TSO_CMD                         	tso_cmd                         ;	// 0x0750 : ''
	TSO_CONF                        	tso_conf                        ;	// 0x0754 : ''
	TSO_TSTAMP                          	tso_tstamp                          ;	// 0x0758 : ''
	UINT32                          	                   _rsvd_addr_03;	// 0x075c
	GSTCC_EN                        	gstcc_en                        ;	// 0x0760 : ''
	UINT32                          	             _rsvd_addr_01[   3];	// 0x0764 ~ 0x076c
	ENC_MCU_VER                     	enc_mcu_ver                     ;	// 0x0770 : ''
	UINT32                          	             _rsvd_addr_02[  35];	// 0x0774 ~ 0x07fc
#if 0
	UINT32                          	ipc_data[ 64]					;	// 0x0800 ~ 0x08fc
#else
	union
	{
		UINT32                          	ipc_data[ 64]					;	// 0x0800 ~ 0x08fc
		VENC_L9_REG_IPC_T						stIpcReg;
	}ipc;
#endif /* #if 0 */
	STC_CTRL                        	stc_ctrl                        ;	// 0x0900 : ''
	STC_BASE                        	stc_base                        ;	// 0x0904 : ''
	STC_EXT                         	stc_ext                         ;	// 0x0908 : ''
	UINT32                          	_rsvd_addr_04[  61]				;	// 0x090c ~ 0x09fc
	TOKEN_INFO                      	token_info                      ;	// 0x0a00 : ''
	UINT32                          	_rsvd_addr_05[  63]				;	// 0x0a04 ~ 0x0afc
	UINT32                          	tso0_data[ 48]					;	// 0x0b00 ~ 0x0bbc
	UINT32                          	_rsvd_addr_06[  16]				;	// 0x0bc0 ~ 0x0bfc
	UINT32                          	tso1_data[ 48]					;	// 0x0c00 ~ 0x0cbc
} VENC_L9_REG_MCU_T;

/******************************************************************************
 * Exported variables
 ******************************************************************************/
//extern volatile VENC_L9_REG_MCU_T *gpVencL9McuReg;
//extern VENC_L9_REG_MCU_T stVencStoredL9McuReg;



#endif	/* _VENC_L9_REG_h */


