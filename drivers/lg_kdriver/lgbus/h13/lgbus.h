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


#ifndef _LGBUS_H_
#define _LGBUS_H_

#include "lgbus_kapi.h"

/*=========================================================================================*
| Symbolic Definitions																	
*==========================================================================================*/

#define MHz 1000000

/*
| Error Code Definitions
*/
#define	RET_OK					0			///< success
#define RET_ERROR				-EIO		///< general error
#define RET_INVALID_PARAMS		-EINVAL		///< invalid paramter
#define RET_INVALID_IOCTL		-ENOTTY		///< invalid ioctl request
#define	RET_OUT_OF_MEMORY		-ENOMEM		///< out ot memory
#define RET_TIMEOUT				-ETIME		///< timeout
#define RET_TRY_AGAIN			-EAGAIN		///< try again
#define RET_INTR_CALL			-EINTR		///< interrupted system call

/*
; Axi Frequency
*/
#define H13_FPGA_CPU_AXI_FREQ		10000000  /*10MHz*/
#define H13_A0_CPU_AXI_FREQ			400000000 /*400MHz*/
#define H13_B0_CPU_AXI_FREQ			400000000 /*400MHz*/


#define BLK_MON_NOT_REQED			0
#define BLK_MON_REQED				1

/*
; Register Base Address
*/
#define LG1154_LBUS_REG_BASE 		(0xC000E000)
#define LG1154_GBUS_REG_BASE		(0xC0010000)
#define LG1154_LGBUS_REG_RGN_SIZE	(0x2000)


/*
; REGISTER_MAP
*/

/*
; Monitor lbus register blk offset
*/
#define MNT_AUD_OFFSET        		(0x0100)
#define MNT_GPU0_OFFSET       		(0x0200)
#define MNT_GPU1_OFFSET       		(0x0300)
#define MNT_GFX_OFFSET        		(0x0400)
#define MNT_ICOD_OFFSET       		(0x0500)
#define MNT_TE_OFFSET         		(0x0600)
#define MNT_VDEC_OFFSET     		(0x0700)
#define MNT_VDO_OFFSET     			(0x0800)
#define MNT_VENC_OFFSET     		(0x0900)
#define MNT_DE_E_CVD_OFFSET   		(0x0E00)
#define MNT_DE_E_MCU_OFFSET   		(0x0F00)
#define MNT_CPU_MAIN_OFFSET   		(0x1C00)


/*
; Monitor gbus register blk offset
*/
#define MNT_DE_A_OFFSET       		(0x0A00)    
#define MNT_DE_B_OFFSET       		(0x0B00)
#define MNT_DE_C_OFFSET       		(0x0C00)
#define MNT_DE_D_OFFSET       		(0x0D00)
#define MNT_DPPA_OFFSET   			(0x1000)
#define MNT_DVI_OFFSET        		(0x1100)
#define MNT_DVO_OFFSET        		(0x1200)
#define MNT_SRE_OFFSET				(0x1300)
#define MNT_MEPA_OFFSET       		(0x1400)
#define MNT_MEPB_OFFSET       		(0x1500)
#define MNT_BVE_MCU_OFFSET   		(0x1600)
#define MNT_MC_OFFSET         		(0x1700)
#define MNT_TCON_OFFSET      		(0x1A00)
#define MNT_CPU_SUB_OFFSET       	(0x1C00) /*cpu_sub use gbus*/

/*
; Monitor register offset
*/
#define MNT_INTR_TOP_STATUS    		0x00 

#define MNT_DEFAULT_PORT            0x06

#define MNT_INTR_CTRL       		0x10 
#define MNT_TIMER_SETTING      		0x14 
#define MNT_TIMER_VALUE        		0x18

#define MNT_WR_BW_VALUE        		0x20 
#define MNT_WR_BW_BUDGET       		0x24 
#define MNT_WR_REQ_VALUE       		0x28 
#define MNT_WR_LATENCY_MAX     		0x2C 
#define MNT_WR_LATENCY_SUM     		0x30 
#define MNT_WR_LATENCY_BUDGET  		0x34 

#define MNT_RD_BW_VALUE        		0x38 
#define MNT_RD_BW_BUDGET       		0x3C 
#define MNT_RD_REQ_VALUE       		0x40 
#define MNT_RD_LATENCY_MAX     		0x44
#define MNT_RD_LATENCY_SUM     		0x48
#define MNT_RD_LATENCY_BUDGET  		0x4C

#define MNT_WR_OTHER_BUS_BW         0x50
#define MNT_RD_OTHER_BUS_BW         0x60

#define MNT_WR_BW_0_VALUE      		0x50
#define MNT_WR_BW_1_VALUE      		0x54
#define MNT_WR_BW_2_VALUE      		0x58
#define MNT_WR_BW_3_VALUE      		0x5C

#define MNT_RD_BW_0_VALUE      		0x60
#define MNT_RD_BW_1_VALUE      		0x64
#define MNT_RD_BW_2_VALUE      		0x68
#define MNT_RD_BW_3_VALUE     		0x6C

#define MNT_ADDR_SWITCH0			0x80
#define MNT_ADDR_SWITCH1			0x84


#define DEFAULT_PORT_FIELD          (0x01 << 2)

/*
; MNT_INTR_CTRL Register field value
*/
#define TMR_DONE_INTR_EN			(0x1<<4)

#define TMR_DONE_INTR_STATUS		(0x1<<12)

#define TMR_DONE_INTR_CLR			(0x1<<20)

#define TMR_ENABLE					(0x1<<24)
#define TMR_AUTO_ENABLE				(0x1<<25)


/*
; Interrupt information for lgbus
*/
#ifndef IRQ_LBUS
#define LBUS_INTR_NUM				66
#define IRQ_LBUS					(LBUS_INTR_NUM + 32)
#endif

#ifndef IRQ_GBUS
#define GBUS_INTR_NUM				67
#define IRQ_GBUS					(GBUS_INTR_NUM + 32)
#endif


/*=========================================================================================*
| Type Definitions																
*==========================================================================================*/

typedef enum {
	H13_FPGA = 0,
	H13_A0 = 1,
	H13_B0 = 2
} chip_rev_e;

typedef enum {
	LBUS_IDX 	= 0,
	GBUS_IDX 	= 1,
	LGBUS_MAX	= 2
} bus_idx_e;

typedef enum {
	REQ_LBUS	= (1<<0),
	REQ_GBUS	= (1<<1),
	REQ_LGBUS	= (REQ_LBUS | REQ_GBUS)
} req_bus_e;

typedef enum {

	BUS_WR_BW_INTR,
	BUS_WR_LATENCY_INTR,
	BUS_RD_BW_INTR,
	BUS_RD_LATENCY_INTR,
	BUS_TMR_DONE_INTR
	
} bus_intr_type_e;



typedef struct {
    unsigned int idx;
    unsigned int reg_base;
    unsigned int reg_offset;
    bus_idx_e bus_idx;
    unsigned int blk_clk;
    unsigned char blk_name[20];
}lgbus_mnt_blk_inform_t;

typedef struct {
	unsigned int 	chip_rev;
	req_bus_e 		bus_chk_id;
	unsigned int 	mnt_chk_blks;
	unsigned int 	mon_freq_per_second;
} mon_req_info_t;



typedef struct {
    bus_idx_e       bus_idx;
	unsigned int 	requestd;
	unsigned int 	wr_bw;
	unsigned int 	wr_bw_bud;
	unsigned int 	wr_req_val;
	unsigned int	wr_max_ltn;
	unsigned int 	wr_sum_ltn;
	unsigned int 	wr_ltn_bud;
	unsigned int 	rd_port0_3_bw[4]; // B0 : rd_port0_3_bw[0] -> rd_bw_to_other;
	unsigned int 	rd_bw;
	unsigned int 	rd_bw_bud;
	unsigned int 	rd_req_val;
	unsigned int	rd_max_ltn;
	unsigned int 	rd_sum_ltn;
	unsigned int	rd_ltn_bud;
	unsigned int 	wr_port0_3_bw[4]; // B0 : wr_port0_3_bw[0] -> wr_bw_to_other;
} bus_mon_raw_t;


typedef struct {
	unsigned int 	wr_avg_ltn; /* wr_sum_ltn/wr_req_val [cycles] */
	unsigned int 	wr_port0_3_sum;
	unsigned int 	rd_avg_ltn; /* rd_sum_ltn/rd_req_val [cycles] */
	unsigned int 	rd_port0_3_sum;
} bus_mon_refined_t;


typedef struct {
    unsigned int        total_blks;
    unsigned int        requested_blks;
	unsigned int		rd_score; 						//	B0 added
	unsigned int		rd_total_bw;
	unsigned int		wr_total_bw;
	unsigned int		wr_ddrc_other_bw;				// B0 added
	unsigned int		wr_ddrc_port0_3bw[4];
	unsigned int		rd_ddrc_other_bw;				// B0 added
	unsigned int		rd_ddrc_port0_3bw[4];
} bus_mon_result_t;


typedef struct {
	bus_mon_raw_t		    raw[LGBUS_MNT_TOTAL_HW_BLKS];
	bus_mon_refined_t	    refined[LGBUS_MNT_TOTAL_HW_BLKS];
	bus_mon_result_t		result[LGBUS_MAX];
} bus_mon_reply_t;


typedef struct {
	int (*init)(mon_req_info_t);
	void (*settmr)(unsigned int );
	void (*start)(void);
	void (*read)(void);
	void (*stop)(void);
	int (*isr[LGBUS_MAX])(void);
} lgbus_ops_t;


typedef struct	{
	volatile unsigned int* 	bus_reg_base[LGBUS_MAX];
    unsigned int            total_blks;
	int 					irq[LGBUS_MAX];
    lgbus_mnt_blk_inform_t  mnt_blk[LGBUS_MNT_TOTAL_HW_BLKS];
//  unsigned int            requested_mnt_blk[LGBUS_MNT_TOTAL_HW_BLKS];
//	volatile unsigned int	qos_reg_base[LGBUS_MAX][LGBUS_MAX_HW_BLKS];
//	unsigned int 	        num_lbus_blks;
//	unsigned int 	        num_gbus_blks;
	bus_mon_reply_t			mon_info;
	int 					mon_frequency;
	lgbus_ops_t				func;
	unsigned long 			ddrc_total_bw;
	struct semaphore		sem;
} lgbus_ctrl_t;



/*=========================================================================================*
| Global Variables																
*==========================================================================================*/


#endif /*_LGBUS_H_*/
