#include <linux/kernel.h>

#include <linux/init.h>

#include <asm/hardware/cache-l2x0.h>
#include <asm/io.h>

#include <mach/resource.h>

#include "core.h"

#include "l2cc.h"
#include "smc.h"

#ifndef CONFIG_TRUSTZONE

void init_l2cc_pre(void)
{
	/*
	 * 1st-half for secure kernel: write desired control values
	 */

	/* use reset value for the AUX_CTRL register */
	writel_relaxed(L2TLCTRL, MMIO_P2V(L2CC_BASE) + L2X0_TAG_LATENCY_CTRL);
	writel_relaxed(L2DLCTRL, MMIO_P2V(L2CC_BASE) + L2X0_DATA_LATENCY_CTRL);
	writel_relaxed(L2DBCTRL, MMIO_P2V(L2CC_BASE) + L2X0_DEBUG_CTRL);
	writel_relaxed(L2PFCTRL, MMIO_P2V(L2CC_BASE) + L2X0_PREFETCH_CTRL);
}

#else

void init_l2cc_pre(void)
{
	struct smc_param param;

	/*
	 * 1st-half for non-secure kernel: enable L2CC with desired control
	 * values via secure monitor call
	 */

	param.param[0] = 0x0100;
	param.param[1] = readl_relaxed(MMIO_P2V(L2CC_BASE + L2X0_AUX_CTRL));
	param.param[2] = L2TLCTRL;
	param.param[3] = L2DLCTRL;
	param.param[4] = L2DBCTRL;
	param.param[5] = L2PFCTRL;

	lg115x_smc(&param);
}

#endif

static void __init init_l2cc_post(void)
{
	/*
	 * 2nd-half for secure kernel: enable L2CC and register outer-cache
	 * 2nd-half for non-secure kernel: register outer-cache
	 */

	l2x0_init(MMIO_P2V(L2CC_BASE), 0x00, ~0x00);
}

void __init lg115x_init_l2cc(void)
{
	init_l2cc_pre();
	init_l2cc_post();
}

