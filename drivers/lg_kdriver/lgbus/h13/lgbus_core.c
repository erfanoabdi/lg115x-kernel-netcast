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


/*=========================================================================================*
| Header files																			   
*==========================================================================================*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */

#include <linux/interrupt.h>	/** irqreturn_t */
#include <linux/irq.h>		/** platform interrupt */

#include <linux/delay.h>

#include "os_util.h"
#include "lgbus_kapi.h"

#include "lgbus.h"
//#include "lgbus_budget.h"
//#include "lgbus_qos.h"


/*=========================================================================================*
| Symbolic Constant																			   
*==========================================================================================*/

#define	MODULE_NAME		"LGBUS"

#define LGBUS_DEBUG				0
#define DBG_LGBUS(fmt, args...) \
	do { if(LGBUS_DEBUG) printk(fmt,## args); } while(0)

/*=========================================================================================*
| Type definitions																			   
*==========================================================================================*/



/*=========================================================================================*
| Function Prototype
*==========================================================================================*/

int lgbus_open(void); 
int lgbus_close(void);

int lgbus_init(mon_req_info_t);
void lgbus_settmr(unsigned int );
void lgbus_start(void);
void lgbus_read(void);
void lgbus_stop(void);
void lgbus_enable_intr(bus_intr_type_e);
void lgbus_disable_intr(bus_intr_type_e);
int lbus_isr(void);
int gbus_isr(void);






/*=========================================================================================*
| Global variables																			   
*==========================================================================================*/
    
lgbus_mnt_blk_inform_t blk_inform_a0[LGBUS_MNT_TOTAL_HW_BLKS] =
{
    {   .idx = MNT_CPU_MAIN_IDX,.reg_offset = 0x0B00, .bus_idx = LBUS_IDX,    .blk_clk =  400000000,    .blk_name = "cpu_main"   }, 
    {   .idx = MNT_CPU_SUB_IDX, .reg_offset = 0x1800, .bus_idx = GBUS_IDX,    .blk_clk =  400000000,    .blk_name = "cpu_sub"   },
    {   .idx = MNT_GPU0_IDX,    .reg_offset = 0x0200, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "gpu0"   }, 
    {   .idx = MNT_GPU1_IDX,    .reg_offset = 0x0300, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "gpu1"   }, 
    {   .idx = MNT_GFX_IDX,     .reg_offset = 0x0400, .bus_idx = LBUS_IDX,    .blk_clk =  400000000,    .blk_name = "gfx"   }, 
    {   .idx = MNT_VDEC_IDX,    .reg_offset = 0x0700, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "vd_pri"   }, 
    {   .idx = MNT_VDO_IDX,     .reg_offset = 0x0800, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "vd_sec"   }, 
    {   .idx = MNT_AUD_IDX,     .reg_offset = 0x0100, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "aud"   }, 
    {   .idx = MNT_ICOD_IDX,    .reg_offset = 0x0500, .bus_idx = LBUS_IDX,    .blk_clk =  200000000,    .blk_name = "icod"   }, 
    {   .idx = MNT_TE_IDX,      .reg_offset = 0x0600, .bus_idx = LBUS_IDX,    .blk_clk =  200000000,    .blk_name = "te"   }, 
    {   .idx = MNT_VENC_IDX,    .reg_offset = 0x0900, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "ve_pri"   }, 
    {   .idx = MNT_TCON_IDX,    .reg_offset = 0x1A00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "tcon"   }, 
    {   .idx = MNT_DPPA_IDX,    .reg_offset = 0x1000, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "dpp_a"   }, 
    {   .idx = MNT_DE_A_IDX,    .reg_offset = 0x0A00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_a"   }, 
    {   .idx = MNT_DE_B_IDX,    .reg_offset = 0x0B00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_b"   }, 
    {   .idx = MNT_DE_C_IDX,    .reg_offset = 0x0C00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_c"   }, 
    {   .idx = MNT_DE_D_IDX,    .reg_offset = 0x0D00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_d"   }, 
    {   .idx = MNT_DE_E_CVD_IDX,.reg_offset = 0x0E00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_e_cvd"   }, 
    {   .idx = MNT_DE_E_MCU_IDX,.reg_offset = 0x0F00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_e_mcu"   }, 
    {   .idx = MNT_DVI_IDX,     .reg_offset = 0x1100, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "dvi"   }, 
    {   .idx = MNT_DVO_IDX,     .reg_offset = 0x1200, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "dvo"   }, 
    {   .idx = MNT_SRE_IDX,     .reg_offset = 0x1300, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "sre"   }, 
    {   .idx = MNT_MEP_A_IDX,   .reg_offset = 0x1400, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "mep_a"   }, 
    {   .idx = MNT_MEP_B_IDX,   .reg_offset = 0x1500, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "mep_b"   }, 
    {   .idx = MNT_BVE_MCU_IDX, .reg_offset = 0x1600, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "bve_mcu"   }, 
    {   .idx = MNT_MC_IDX,      .reg_offset = 0x1700, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "mc"   }, 
};


lgbus_mnt_blk_inform_t blk_inform_b0[LGBUS_MNT_TOTAL_HW_BLKS] =
{
    {   .idx = MNT_CPU_MAIN_IDX,.reg_offset = 0x1C00, .bus_idx = LBUS_IDX,    .blk_clk =  400000000,    .blk_name = "cpu_main"   }, 
    {   .idx = MNT_CPU_SUB_IDX, .reg_offset = 0x1C00, .bus_idx = GBUS_IDX,    .blk_clk =  400000000,    .blk_name = "cpu_sub"   },
    {   .idx = MNT_GPU0_IDX,    .reg_offset = 0x0200, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "gpu0"   }, 
    {   .idx = MNT_GPU1_IDX,    .reg_offset = 0x0300, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "gpu1"   }, 
    {   .idx = MNT_GFX_IDX,     .reg_offset = 0x0400, .bus_idx = LBUS_IDX,    .blk_clk =  400000000,    .blk_name = "gfx"   }, 
    {   .idx = MNT_VDEC_IDX,    .reg_offset = 0x0700, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "vd_pri"   }, 
    {   .idx = MNT_VDO_IDX,     .reg_offset = 0x0800, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "vd_sec"   }, 
    {   .idx = MNT_AUD_IDX,     .reg_offset = 0x0100, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "aud"   }, 
    {   .idx = MNT_ICOD_IDX,    .reg_offset = 0x0500, .bus_idx = LBUS_IDX,    .blk_clk =  200000000,    .blk_name = "icod"   }, 
    {   .idx = MNT_TE_IDX,      .reg_offset = 0x0600, .bus_idx = LBUS_IDX,    .blk_clk =  200000000,    .blk_name = "te"   }, 
    {   .idx = MNT_VENC_IDX,    .reg_offset = 0x0900, .bus_idx = LBUS_IDX,    .blk_clk =  320000000,    .blk_name = "ve_pri"   }, 
    {   .idx = MNT_TCON_IDX,    .reg_offset = 0x1A00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "tcon"   }, 
    {   .idx = MNT_DPPA_IDX,    .reg_offset = 0x1000, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "dpp_a"   }, 
    {   .idx = MNT_DE_A_IDX,    .reg_offset = 0x0A00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_a"   }, 
    {   .idx = MNT_DE_B_IDX,    .reg_offset = 0x0B00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_b"   }, 
    {   .idx = MNT_DE_C_IDX,    .reg_offset = 0x0C00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_c"   }, 
    {   .idx = MNT_DE_D_IDX,    .reg_offset = 0x0D00, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_d"   }, 
    {   .idx = MNT_DE_E_CVD_IDX,.reg_offset = 0x0E00, .bus_idx = LBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_e_cvd"   }, 
    {   .idx = MNT_DE_E_MCU_IDX,.reg_offset = 0x0F00, .bus_idx = LBUS_IDX,    .blk_clk =  200000000,    .blk_name = "de_e_mcu"   }, 
    {   .idx = MNT_DVI_IDX,     .reg_offset = 0x1100, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "dvi"   }, 
    {   .idx = MNT_DVO_IDX,     .reg_offset = 0x1200, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "dvo"   }, 
    {   .idx = MNT_SRE_IDX,     .reg_offset = 0x1300, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "sre"   }, 
    {   .idx = MNT_MEP_A_IDX,   .reg_offset = 0x1400, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "mep_a"   }, 
    {   .idx = MNT_MEP_B_IDX,   .reg_offset = 0x1500, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "mep_b"   }, 
    {   .idx = MNT_BVE_MCU_IDX, .reg_offset = 0x1600, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "bve_mcu"   }, 
    {   .idx = MNT_MC_IDX,      .reg_offset = 0x1700, .bus_idx = GBUS_IDX,    .blk_clk =  200000000,    .blk_name = "mc"   }, 
};

lgbus_ops_t lgbus_func = 
{
	.init = lgbus_init,
	.settmr = lgbus_settmr,
	.start = lgbus_start,
	.read = lgbus_read,
	//.setbudget = lgbus_set_budget,
	//.setqos = lgbus_set_qos,
	.stop = lgbus_stop,
	.isr[LBUS_IDX] = lbus_isr,
	.isr[GBUS_IDX] = gbus_isr,
};


lgbus_ctrl_t			lgbus_ctrl;
mon_req_info_t 			req_info;


/*=========================================================================================*
| Function Definitions																			   
*==========================================================================================*/

int lbus_isr(void)
{
	unsigned int i, reg_val, intr_status = 0;

    DBG_LGBUS("LBUS_ISR\n");

	reg_val = __raw_readl(lgbus_ctrl.mnt_blk[MNT_CPU_MAIN_IDX].reg_base + MNT_INTR_CTRL);

	if(reg_val & TMR_DONE_INTR_STATUS)
	{
		intr_status |= TMR_DONE_INTR_STATUS;
        
    	/*
    	; Signal to process
    	*/
    	if(down_trylock(&(lgbus_ctrl.sem))!=0)
    		up(&(lgbus_ctrl.sem));
        
    	/*
    	; clear interrupt, we have to search interrupt clear bit.
    	*/
    	reg_val |= (intr_status << 8); 
    	__raw_writel(reg_val, lgbus_ctrl.mnt_blk[MNT_CPU_MAIN_IDX].reg_base + MNT_INTR_CTRL);
	}
    else
    {
    	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
    	{
    		reg_val = __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);

    		if(reg_val & TMR_DONE_INTR_STATUS)
    		{
    			intr_status |= TMR_DONE_INTR_STATUS; 
    		}
            else
            {
                if(reg_val & (0x01 << 13))  // protected memory access
                {
                    printk("Check the Protected Memory Access of Blk[%s]!! reg:[0x%08X]\n", lgbus_ctrl.mnt_blk[i].blk_name, reg_val);
                    reg_val &= ~(0x01 << 5); // disable protected memory access intr
                }
                intr_status = reg_val & 0xFF00;
            }

    		/*
    		; clear interrupt
    		*/
    		reg_val |= (intr_status << 8); 
    		__raw_writel(reg_val, lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
    	}        
    }

	return 0;
}


int gbus_isr(void)
{
	unsigned int reg_val, i, intr_status = 0;

    DBG_LGBUS("GBUS_ISR\n");

	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	{
		reg_val = __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);


		if(reg_val & TMR_DONE_INTR_STATUS)
		{
			intr_status |= TMR_DONE_INTR_STATUS; 
		}
        else
        {
            if(reg_val & (0x01 << 13))  // protected memory access
            {
                printk("Check the Protected Memory Access of Blk[%s]!! reg:[0x%8X]\n", lgbus_ctrl.mnt_blk[i].blk_name, reg_val);
                reg_val &= ~(0x01 << 5); // disable protected memory access intr
            }
            intr_status = reg_val & 0xFF00;
        }

		/*
		; clear interrupt
		*/
		reg_val |= (intr_status << 8);
		__raw_writel(reg_val, lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
	}

	return 0;
}




irqreturn_t lgbus_isr(int irq, void *dev_id, struct pt_regs *regs)
{
	bus_idx_e id = LGBUS_MAX;

	DBG_LGBUS(KERN_ERR "lgbus_isr, isr number[%d]\n", irq);


	if(irq==IRQ_LBUS)
        id = LBUS_IDX;
	else if(irq==IRQ_GBUS)
        id = GBUS_IDX;
	else
		DBG_LGBUS("lgbus_isr, unknow isr number[%d]\n", irq);


	/*
	; call lbus or gbus isr function.
	*/
	if(lgbus_ctrl.func.isr[id])
    	lgbus_ctrl.func.isr[id]();
	else
		DBG_LGBUS("lgbus_isr don't inited, unknow interrupt. guess that protected memory access is happened![%d]\n", irq);
        
	return IRQ_HANDLED;
}


/*
; file operation function
*/
int lgbus_open(void) 
{
    unsigned int i;
    bus_idx_e bus_idx;
    
	DBG_LGBUS(KERN_INFO "lgbus_open()\n");

	lgbus_ctrl.bus_reg_base[LBUS_IDX]	= (unsigned long)ioremap_nocache((unsigned long)LG1154_LBUS_REG_BASE, 0x2000);
	lgbus_ctrl.bus_reg_base[GBUS_IDX]	= (unsigned long)ioremap_nocache((unsigned long)LG1154_GBUS_REG_BASE, 0x2000); 

	printk("lgbus_init, Lbus vaddr[0x%8x], Lbus vaddr[0x%8x]\n", lgbus_ctrl.bus_reg_base[LBUS_IDX], lgbus_ctrl.bus_reg_base[GBUS_IDX]);

    if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
    {
        //printk("H13B0!\n");
        memcpy(lgbus_ctrl.mnt_blk, blk_inform_b0, sizeof(blk_inform_b0));
    }
    else if(lx_chip_rev() >= LX_CHIP_REV(H13, A0))
    {
        //printk("H13A0!\n");
        memcpy(lgbus_ctrl.mnt_blk, blk_inform_a0, sizeof(blk_inform_a0));
    }
    else
    {
        printk("Not support chip\n");
    }
    
	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	{
        bus_idx = lgbus_ctrl.mnt_blk[i].bus_idx;
        lgbus_ctrl.mnt_blk[i].reg_base = (unsigned int)(lgbus_ctrl.bus_reg_base[bus_idx]) + lgbus_ctrl.mnt_blk[i].reg_offset;
        //printk("[%d] [%d]BUS base addr : 0x%X\n", i, bus_idx,lgbus_ctrl.mnt_blk[i].reg_base);
    }

	/*
	; register lgbus irq number
	*/
	lgbus_ctrl.irq[LBUS_IDX] = IRQ_LBUS;
	lgbus_ctrl.irq[GBUS_IDX] = IRQ_GBUS;

	/*
	; register lgbus driver functions
	*/
	lgbus_ctrl.func = lgbus_func;


	/* Success */
	return 0;
}

int lgbus_close()
{    
	iounmap(lgbus_ctrl.bus_reg_base[LBUS_IDX]);
	iounmap(lgbus_ctrl.bus_reg_base[GBUS_IDX]);

    return 0;
}


void lgbus_enable_intr(bus_intr_type_e i_type)
{
	unsigned int reg_val;

	reg_val = __raw_readl(lgbus_ctrl.mnt_blk[MNT_CPU_MAIN_IDX].reg_base + MNT_INTR_CTRL);
	__raw_writel((reg_val)|(1 << i_type), lgbus_ctrl.mnt_blk[MNT_CPU_MAIN_IDX].reg_base + MNT_INTR_CTRL);

	DBG_LGBUS("cpu timer intr is enabled!!\n");
}

void lgbus_disable_intr(bus_intr_type_e i_type)
{
	unsigned int reg_val;

	reg_val = __raw_readl(lgbus_ctrl.mnt_blk[MNT_CPU_MAIN_IDX].reg_base + MNT_INTR_CTRL);
	__raw_writel((reg_val)&(~(1 << i_type)), lgbus_ctrl.mnt_blk[MNT_CPU_MAIN_IDX].reg_base + MNT_INTR_CTRL);
}




void lgbus_settmr(unsigned int mon_frequncy)
{
	unsigned int i;
	unsigned int tmr_val;

	/*
	; check requested monitoring blks.
	*/
	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	{
		tmr_val = lgbus_ctrl.mnt_blk[i].blk_clk / mon_frequncy ;
        
		__raw_writel(tmr_val, lgbus_ctrl.mnt_blk[i].reg_base + MNT_TIMER_SETTING);
	}
}


void lgbus_start(void)
{
	unsigned int reg_val;
    int i;

	/*
	; timer start all monitoring blks.
	*/
	//for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	for(i = LGBUS_MNT_TOTAL_HW_BLKS - 1; i >= 0; i--)
	{
		reg_val = __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
        
		__raw_writel((reg_val | TMR_ENABLE), lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
	}
}

void lgbus_auto_start()
{
	unsigned int r_val, i;

	/*
	; check requested monitoring blks.
	*/
	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	{
    	r_val = __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
    	__raw_writel((r_val | TMR_AUTO_ENABLE), lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
	}
}

void lgbus_stop(void)
{
	unsigned int reg_val, i;

	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	{
        reg_val = __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
        __raw_writel((reg_val & ~TMR_ENABLE), lgbus_ctrl.mnt_blk[i].reg_base + MNT_INTR_CTRL);
    }
}

int lgbus_init(mon_req_info_t req)
{
	unsigned int i, bus_idx;

	/*
	; check requested monitoring blks.
	*/
    lgbus_ctrl.mon_info.result[LBUS_IDX].total_blks = 0;
    lgbus_ctrl.mon_info.result[GBUS_IDX].total_blks = 0;
    
    lgbus_ctrl.mon_info.result[LBUS_IDX].requested_blks = 0;
    lgbus_ctrl.mon_info.result[GBUS_IDX].requested_blks = 0;
    
	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	{   
        // printk("bus_IDX[%x]\n", __raw_readb(lgbus_ctrl.mnt_blk[i].reg_base + MNT_DEFAULT_PORT)); //doesn't work
		//lgbus_ctrl.mnt_blk[i].bus_idx = (__raw_readb(lgbus_ctrl.mnt_blk[i].reg_base + MNT_DEFAULT_PORT) & 0x01); // check bus index(L or G)
		
		//lgbus_ctrl.mnt_blk[i].bus_idx = ((__raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + 0x04) >> 16) & 0x01); // check bus index(L or G)
        
        bus_idx = lgbus_ctrl.mnt_blk[i].bus_idx;
        //printk("[%d] is BUS[%d]\n", i, bus_idx);
                
		if(req.mnt_chk_blks & (1 << i))
		{
            lgbus_ctrl.mon_info.raw[i].requestd = BLK_MON_REQED;
            lgbus_ctrl.mon_info.result[bus_idx].requested_blks++;
            
		}
		else
            lgbus_ctrl.mon_info.raw[i].requestd = BLK_MON_NOT_REQED;
        
        lgbus_ctrl.mon_info.result[bus_idx].total_blks++;
	}
    printk("Total_blks L[%d], G[%d], requested blks L[%d], G[%d]\n",
        lgbus_ctrl.mon_info.result[LBUS_IDX].total_blks,
        lgbus_ctrl.mon_info.result[GBUS_IDX].total_blks,
        lgbus_ctrl.mon_info.result[LBUS_IDX].requested_blks,
        lgbus_ctrl.mon_info.result[GBUS_IDX].requested_blks);
    
	/*
	; initialize semaphore.
	; this semaphore operate with lbus timer done interrupt handler.
	*/
	sema_init(&(lgbus_ctrl.sem), 1);
	down(&(lgbus_ctrl.sem));


	/*
	; enable cpu main monitoring timer done interrupt.  
	*/
	lgbus_enable_intr(BUS_TMR_DONE_INTR);
	

	return 0;
}

void lgbus_read()
{
	unsigned int i;
	unsigned int bus_idx, port = 0;


    // initialize LBUS result value
	lgbus_ctrl.mon_info.result[LBUS_IDX].rd_score	 = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].wr_total_bw = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].rd_total_bw = 0;

	lgbus_ctrl.mon_info.result[LBUS_IDX].wr_ddrc_other_bw = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].wr_ddrc_port0_3bw[0] = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].wr_ddrc_port0_3bw[1] = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].wr_ddrc_port0_3bw[2] = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].wr_ddrc_port0_3bw[3] = 0;

	lgbus_ctrl.mon_info.result[LBUS_IDX].rd_ddrc_other_bw = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].rd_ddrc_port0_3bw[0] = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].rd_ddrc_port0_3bw[1] = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].rd_ddrc_port0_3bw[2] = 0;
	lgbus_ctrl.mon_info.result[LBUS_IDX].rd_ddrc_port0_3bw[3] = 0;

    // initialize GBUS result value
	lgbus_ctrl.mon_info.result[GBUS_IDX].rd_score	 = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].wr_total_bw = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].rd_total_bw = 0;

	lgbus_ctrl.mon_info.result[GBUS_IDX].wr_ddrc_other_bw = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].wr_ddrc_port0_3bw[0] = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].wr_ddrc_port0_3bw[1] = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].wr_ddrc_port0_3bw[2] = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].wr_ddrc_port0_3bw[3] = 0;

	lgbus_ctrl.mon_info.result[GBUS_IDX].rd_ddrc_other_bw = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].rd_ddrc_port0_3bw[0] = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].rd_ddrc_port0_3bw[1] = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].rd_ddrc_port0_3bw[2] = 0;
	lgbus_ctrl.mon_info.result[GBUS_IDX].rd_ddrc_port0_3bw[3] = 0;

	for(i = 0; i < LGBUS_MNT_TOTAL_HW_BLKS; i++)
	{
        bus_idx = lgbus_ctrl.mnt_blk[i].bus_idx;
                
		port = (__raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_ADDR_SWITCH0) >> 24);// & 0x3;
        
        lgbus_ctrl.mon_info.raw[i].bus_idx = bus_idx;
        
		/*write bandwidth*/
		lgbus_ctrl.mon_info.raw[i].wr_bw			= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_WR_BW_VALUE);
		lgbus_ctrl.mon_info.raw[i].wr_bw_bud  		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_WR_BW_BUDGET);
		lgbus_ctrl.mon_info.raw[i].wr_req_val 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_WR_REQ_VALUE);
		lgbus_ctrl.mon_info.raw[i].wr_sum_ltn 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_WR_LATENCY_SUM);
		lgbus_ctrl.mon_info.raw[i].wr_max_ltn 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_WR_LATENCY_MAX);
		lgbus_ctrl.mon_info.raw[i].wr_ltn_bud 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_WR_LATENCY_BUDGET);

		lgbus_ctrl.mon_info.raw[i].wr_port0_3_bw[0] = __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_WR_OTHER_BUS_BW); 

		/*read bandwidth*/
		lgbus_ctrl.mon_info.raw[i].rd_bw 			= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_RD_BW_VALUE);
		lgbus_ctrl.mon_info.raw[i].rd_bw_bud 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_RD_BW_BUDGET);
		lgbus_ctrl.mon_info.raw[i].rd_req_val 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_RD_REQ_VALUE);
		lgbus_ctrl.mon_info.raw[i].rd_sum_ltn 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_RD_LATENCY_SUM);
		lgbus_ctrl.mon_info.raw[i].rd_max_ltn 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_RD_LATENCY_MAX);
		lgbus_ctrl.mon_info.raw[i].rd_ltn_bud 		= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_RD_LATENCY_BUDGET);

		lgbus_ctrl.mon_info.raw[i].rd_port0_3_bw[0]	= __raw_readl(lgbus_ctrl.mnt_blk[i].reg_base + MNT_RD_OTHER_BUS_BW);


		/*refine*/
		if(lgbus_ctrl.mon_info.raw[i].wr_req_val == 0)
			lgbus_ctrl.mon_info.refined[i].wr_avg_ltn	= 0;
		else
			lgbus_ctrl.mon_info.refined[i].wr_avg_ltn	= lgbus_ctrl.mon_info.raw[i].wr_sum_ltn / lgbus_ctrl.mon_info.raw[i].wr_req_val;
		
		if(lgbus_ctrl.mon_info.raw[i].rd_req_val == 0)
			lgbus_ctrl.mon_info.refined[i].rd_avg_ltn	= 0;
		else
			lgbus_ctrl.mon_info.refined[i].rd_avg_ltn	= lgbus_ctrl.mon_info.raw[i].rd_sum_ltn / lgbus_ctrl.mon_info.raw[i].rd_req_val;

        // work around of H/W problem
        if (lgbus_ctrl.mnt_blk[i].idx == MNT_CPU_MAIN_IDX || lgbus_ctrl.mnt_blk[i].idx == MNT_CPU_SUB_IDX || lgbus_ctrl.mnt_blk[i].idx == MNT_DE_E_CVD_IDX)
        {
            lgbus_ctrl.mon_info.raw[i].wr_port0_3_bw[0] = 0;
            lgbus_ctrl.mon_info.raw[i].rd_port0_3_bw[0] = 0;
        }     
        // work around of H/W problem
        else if(lgbus_ctrl.mnt_blk[i].idx == MNT_DPPA_IDX)
        {
            bus_idx = LBUS_IDX;            
            lgbus_ctrl.mon_info.raw[i].bus_idx = bus_idx;
        }
        // Move TCON to LBUS statically
        else if(lgbus_ctrl.mnt_blk[i].idx == MNT_TCON_IDX)   
        {
            bus_idx = LBUS_IDX;
            lgbus_ctrl.mon_info.raw[i].bus_idx = bus_idx;
            
            lgbus_ctrl.mon_info.raw[i].wr_port0_3_bw[0] = 0;
            lgbus_ctrl.mon_info.raw[i].rd_port0_3_bw[0] = 0;
        }

		lgbus_ctrl.mon_info.result[bus_idx].wr_ddrc_port0_3bw[port]	+= lgbus_ctrl.mon_info.raw[i].wr_bw - lgbus_ctrl.mon_info.raw[i].wr_port0_3_bw[0];
		lgbus_ctrl.mon_info.result[bus_idx].rd_ddrc_port0_3bw[port]	+= lgbus_ctrl.mon_info.raw[i].rd_bw - lgbus_ctrl.mon_info.raw[i].rd_port0_3_bw[0];


        // calcaulate another bus sum if blk use another bus
        if(lgbus_ctrl.mon_info.raw[i].wr_bw == lgbus_ctrl.mon_info.raw[i].wr_port0_3_bw[0])
            lgbus_ctrl.mon_info.result[!bus_idx].wr_ddrc_port0_3bw[port] += lgbus_ctrl.mon_info.raw[i].wr_port0_3_bw[0];
        
        if(lgbus_ctrl.mon_info.raw[i].rd_bw == lgbus_ctrl.mon_info.raw[i].rd_port0_3_bw[0])
            lgbus_ctrl.mon_info.result[!bus_idx].rd_ddrc_port0_3bw[port] += lgbus_ctrl.mon_info.raw[i].rd_port0_3_bw[0];
        


        
		lgbus_ctrl.mon_info.result[bus_idx].wr_ddrc_other_bw	+= lgbus_ctrl.mon_info.raw[i].wr_port0_3_bw[0];
		lgbus_ctrl.mon_info.result[bus_idx].rd_ddrc_other_bw	+= lgbus_ctrl.mon_info.raw[i].rd_port0_3_bw[0];

		lgbus_ctrl.mon_info.result[bus_idx].rd_score += lgbus_ctrl.mon_info.raw[i].rd_sum_ltn ;
	}
	
	return;		
}


