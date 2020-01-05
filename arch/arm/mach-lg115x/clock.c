#include <linux/kernel.h>

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/errno.h>
#include <linux/export.h>
#include <linux/list.h>

#include <mach/resource.h>
#include <mach/timex.h>

#include "core.h"
#include "clock.h"

struct clk {
	struct list_head node;

	unsigned long rate;	/* clock frequency in Hz */
};

#define CFF_CORE	0x01
#define CFF_PERI	0x02
#define CFF_DDR0	0x04
#define CFF_DDR1	0x08
#define CFF_AMBA	0x10

struct clock_freq {
	unsigned long flags;	/* availability */

	struct clk core;	/* CPU core */
	struct clk peri;	/* MPcore peripheral */
	struct clk ddr0;	/* DDR0 */
	struct clk ddr1;	/* DDR1 */
	struct clk amba;	/* AMBA bus */
};

static struct clock_freq _clock_freq;

static struct clk_lookup _clk_table[] = {
	CLKDEV_INIT("sdhci-lg115x", NULL, &_clock_freq.amba),
#ifdef CONFIG_LOCAL_TIMERS
	CLKDEV_INIT("smp_twd",      NULL, &_clock_freq.peri),
#endif
	CLKDEV_INIT("sp804",        NULL, &_clock_freq.amba),
	CLKDEV_INIT("spi0",         NULL, &_clock_freq.amba),
	CLKDEV_INIT("spi1",         NULL, &_clock_freq.amba),
	CLKDEV_INIT("uart0",        NULL, &_clock_freq.amba),
	CLKDEV_INIT("uart1",        NULL, &_clock_freq.amba),
	CLKDEV_INIT("uart2",        NULL, &_clock_freq.amba),
	CLKDEV_INIT("wdog",         NULL, &_clock_freq.amba),
};

#ifndef CONFIG_CLOCK_DETECTION

static inline void _init_clock(void)
{
#ifdef CONFIG_LOCAL_TIMERS
	_clock_freq.peri.rate = PERI_CLOCK;
	_clock_freq.flags |= CFF_PERI;
#endif
	_clock_freq.amba.rate = AMBA_CLOCK;
	_clock_freq.flags |= CFF_AMBA;
}

#else

#define PLL_FREQ	24000000

#define CTR_32		( 32 << 2)
#define CTR_74		( 74 << 2)
#define CTR_76		( 76 << 2)
#define CTR_78		( 78 << 2)
#define CTR111		(111 << 2)

struct pll_ctrl {
	unsigned long /* reserved */    : 19;
	unsigned long m                 :  5;
	unsigned long pre_fd            :  2;
	unsigned long od_fout           :  2;
	unsigned long /* reserved */    :  4;

	unsigned long udex              :  5;
	unsigned long msex              :  9;
	unsigned long nsc               :  4;
	unsigned long npc               :  6;
	unsigned long /* reserved */    :  3;
	unsigned long cih               :  3;
	unsigned long lf                :  1;
	unsigned long pdb               :  1;
};

static void __init _init_clock(void)
{
	unsigned long core_pll_out;
	unsigned long ddr0_pll_out;
	unsigned long ddr1_pll_out;
	unsigned long ctr_32;
	unsigned long ctr111;
	struct pll_ctrl const *ctrl;
	unsigned long npc;
	unsigned long nsc;

	ctr_32 = *(unsigned long *)MMIO_P2V(TOP_CTRL_BASE + CTR_32);
	ctr111 = *(unsigned long *)MMIO_P2V(TOP_CTRL_BASE + CTR111);

	/* CTR74-75: CPU PLL configuration */
	ctrl = (struct pll_ctrl *)MMIO_P2V(TOP_CTRL_BASE + CTR_74);
	switch(ctr111 >> 12)
	{
	case 0x13da0:
	case 0x13da1:
		/* H13A0 or H13A1 */
		npc = ctrl->npc ^ 0x0c;
		nsc = ctrl->nsc ^ 0x03;
		break;

	case 0x13db0:
	default:
		/* H13B0 or later */
		npc = ctrl->npc ^ 0x02;
		nsc = ctrl->nsc ^ 0x02;
		break;
	}
	core_pll_out = (PLL_FREQ * (((npc << 2) + nsc) << ctrl->pre_fd) /
	                ((ctrl->m + 1) << ctrl->od_fout));

	/* CTR76-77: main PLL 1 configuration */
	ctrl = (struct pll_ctrl *)MMIO_P2V(TOP_CTRL_BASE + CTR_76);
	npc = ctrl->npc;
	nsc = ctrl->nsc;
	ddr0_pll_out = (PLL_FREQ * (((npc << 2) + nsc) << ctrl->pre_fd) /
	                ((ctrl->m + 1) << ctrl->od_fout));

	/* CTR78-79: main PLL 2 configuration */
	ctrl = (struct pll_ctrl *)MMIO_P2V(TOP_CTRL_BASE + CTR_78);
	npc = ctrl->npc;
	nsc = ctrl->nsc;
	ddr1_pll_out = (PLL_FREQ * (((npc << 2) + nsc) << ctrl->pre_fd) /
	                ((ctrl->m + 1) << ctrl->od_fout));

	/* CPU core clock frequency */
	_clock_freq.core.rate = core_pll_out >> 1;

	/* MPcore peripheral clock frequency */
	_clock_freq.peri.rate = core_pll_out >> 2;

	/* DDR clock frequency */
	if(!(ctr_32 & 0x00000080))
	{
		_clock_freq.ddr0.rate = ddr0_pll_out >> 1;
		_clock_freq.ddr1.rate = ddr1_pll_out >> 1;
	}
	else
	{
		_clock_freq.ddr0.rate = ddr1_pll_out >> 1;
		_clock_freq.ddr1.rate = ddr0_pll_out >> 1;
	}

	/* AMBA bus clock frequency */
	if(!(ctr_32 & 0x00200000))
		_clock_freq.amba.rate = ddr0_pll_out >> 3;
	else
		_clock_freq.amba.rate = ddr1_pll_out >> 3;

	_clock_freq.flags = CFF_CORE | CFF_PERI | CFF_DDR0 | CFF_DDR1 |
	                    CFF_AMBA;
}

#endif

void __init lg115x_init_clock(void)
{
	_init_clock();

	clkdev_add_table(_clk_table, ARRAY_SIZE(_clk_table));
}

int clk_enable(struct clk *clk)
{
	/* do nothing -- bus clock is always enabled */
	return 0;
}
EXPORT_SYMBOL(clk_enable);

void clk_disable(struct clk *clk)
{
	/* do nothing -- bus clock is always enabled */
}
EXPORT_SYMBOL(clk_disable);

unsigned long clk_get_rate(struct clk *clk)
{
	return clk ? clk->rate : 0;
}
EXPORT_SYMBOL(clk_get_rate);

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	/* not supported -- constant rate */
	return -EIO;
}
EXPORT_SYMBOL(clk_set_rate);

long clk_round_rate(struct clk *clk, unsigned long rate)
{
	/* not supported -- constant rate */
	return rate;
}
EXPORT_SYMBOL(clk_round_rate);

