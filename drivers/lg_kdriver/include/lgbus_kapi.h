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
 *  application interface header for lgbus device
 *
 *  author		hwanwook.lee (hwanwook.lee@lge.com)
 *              bongrae.cho (bongrae.cho@lge.com)
 *  version		1.0
 *  date		2012.07.14
 *
 *  @addtogroup lg115x_lgbus
 */

#ifndef	_LGBUS_KAPI_H_
#define	_LGBUS_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	LGBUS_IOC_MAGIC		'L'

#define LGBUS_MNT_TOTAL_HW_BLKS  26


#define LX_LGBUS_H13_SOC_DDR_TOTAL_BW		6400000000 /*6.4 GB/sec*/
#define LX_LGBUS_H13_FPGA_DDR_TOTAL_BW		160000000  /*6.4/40=160MB/sec*/	


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
    
/*
; LG BUS monitoring structure.
*/

typedef enum {
    MNT_CPU_MAIN_IDX    = 0,
    MNT_CPU_SUB_IDX     = 1,
    MNT_GPU0_IDX        = 2,
    MNT_GPU1_IDX        = 3,
    MNT_GFX_IDX         = 4,
    MNT_VDEC_IDX        = 5,
    MNT_VDO_IDX         = 6,
    MNT_AUD_IDX         = 7,
    MNT_ICOD_IDX        = 8,
    MNT_TE_IDX          = 9,
    MNT_VENC_IDX        = 10,
    MNT_TCON_IDX        = 11,
    MNT_DPPA_IDX        = 12,
    MNT_DE_A_IDX        = 13,
    MNT_DE_B_IDX        = 14,
    MNT_DE_C_IDX        = 15,
    MNT_DE_D_IDX        = 16,
    MNT_DE_E_CVD_IDX    = 17,
    MNT_DE_E_MCU_IDX    = 18,
    MNT_DVI_IDX         = 19,
    MNT_DVO_IDX         = 20,
    MNT_SRE_IDX         = 21,
    MNT_MEP_A_IDX       = 22,
    MNT_MEP_B_IDX       = 23,
    MNT_BVE_MCU_IDX     = 24,
    MNT_MC_IDX          = 25,

} bus_mon_blk_idx_e;


typedef enum {
	LX_LGBUS_H13_FPGA = 0,
	LX_LGBUS_H13_A0 = 1,
	LX_LGBUS_H13_B0 = 2
} LX_LGBUS_REV_E;


typedef enum {
	LX_LBUS_IDX 	= 0,
	LX_GBUS_IDX 	= 1,
	LX_LGBUS_MAX	= 2
} LX_LGBUS_IDX_E;

typedef enum {
	LX_LGBUS_REQ_LBUS	= (1<<0),
	LX_LGBUS_REQ_GBUS	= (1<<1),
	LX_LGBUS_REQ_LGBUS	= (LX_LGBUS_REQ_LBUS | LX_LGBUS_REQ_GBUS)
} LX_LGBUS_REQ_BUS_E;



typedef struct {
    LX_LGBUS_IDX_E  bus_idx;
	UINT32 	requestd;
	UINT32 	wr_bw;
	UINT32 	wr_bw_bud;
	UINT32 	wr_req_val;
	UINT32	wr_max_ltn;
	UINT32 	wr_sum_ltn;
	UINT32 	wr_ltn_bud;
	UINT32 	rd_port0_3_bw[4];
	UINT32 	rd_bw;
	UINT32 	rd_bw_bud;
	UINT32 	rd_req_val;
	UINT32	rd_max_ltn;
	UINT32 	rd_sum_ltn;
	UINT32	rd_ltn_bud;
	UINT32 	wr_port0_3_bw[4];
} LX_LGBUS_RAW_T;



typedef struct {
	UINT32 	wr_avg_ltn;
	UINT32 	wr_port0_3_sum;
	UINT32 	rd_avg_ltn;
	UINT32 	rd_port0_3_sum;
} LX_LGBUS_REFINED_T;


typedef struct {
    UINT32      total_blks;
    UINT32      requested_blks;
	UINT32		rd_score; 						//	B0 added
	UINT32		rd_total_bw;
	UINT32		wr_total_bw;
	UINT32		wr_ddrc_other_bw;
	UINT32		wr_ddrc_port0_3bw[4];
	UINT32		rd_ddrc_other_bw;				// B0 added	
	UINT32		rd_ddrc_port0_3bw[4];		
} LX_LGBUS_RESULT_T;


typedef struct {
	LX_LGBUS_RAW_T		raw[LGBUS_MNT_TOTAL_HW_BLKS];
	LX_LGBUS_REFINED_T	refined[LGBUS_MNT_TOTAL_HW_BLKS];
	LX_LGBUS_RESULT_T		result[LX_LGBUS_MAX];
} LX_LGBUS_REPLY_T;

typedef struct {
	UINT32 	chip_rev;
	LX_LGBUS_REQ_BUS_E 	bus_chk_id;
	UINT32 	mnt_chk_blks;
	UINT32 	mon_freq_per_second;
} LX_LGBUS_REQ_INFO_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

#define LGBUS_IOW_INIT		    _IOW(LGBUS_IOC_MAGIC, 0, LX_LGBUS_REQ_INFO_T)
#define LGBUS_IO_STOP		    _IO(LGBUS_IOC_MAGIC, 1)
#define LGBUS_IOR_MON_READ		_IOR(LGBUS_IOC_MAGIC, 2, LX_LGBUS_REPLY_T)

#define LGBUS_IOC_MAXNR			5

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _LGBUS_KAPI_H_ */

