/**
 * Author : sinchul.jung
 * Date : 2011.7.13
 */
#include <linux/init.h>
#include <linux/suspend.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/delay.h>

#include <mach/hardware.h>
#include <asm/memory.h>
#include <asm/system.h>
#include <asm/mach/time.h>

#include "lgsleep_ca9.h"

static int lg1154_pm_prepare(void)
{

	printk(">>>>>>>> go into pm prepare\n");
	return 0;
}


#if 1//ndef CONFIG_LG115X_IBOOT_ONLY_SW_TEST
extern void lg115x_pm_install_sram_code_params(void);
extern void lg115x_pm_install_rst_vect_hdlr(void);
extern void lg115x_pm_entr(void);
extern void lg115x_board_init(void);
#endif

static int lg1154_pm_enter(suspend_state_t state)
{

	printk(">>>>>>>> go into pm enter\n");
	/* go zzz */
	switch (state)
	{
		case PM_SUSPEND_STANDBY:
		case PM_SUSPEND_MEM:
#if 1//ndef CONFIG_LG115X_IBOOT_ONLY_SW_TEST
			lg115x_pm_install_sram_code_params();
			lg115x_pm_install_rst_vect_hdlr();
			lg115x_pm_entr();


#if defined(CONFIG_CACHE_L2X0)
			outer_cache.resume();
#endif
			/*
			 * after system rebooting, set the ddr2 param again and initialize system
			 */
			lg115x_board_init();
			mdelay(50);
#else

#endif						
			break;
		default:
			return -EINVAL;
	}

	return 0;
}

static int lg1154_pm_finish(void)
{
	printk(">>>>>>>> go into pm finish\n");

	return 0;
}


static struct platform_suspend_ops lg1154_pm_ops = {
	.prepare	= lg1154_pm_prepare,
	.enter		= lg1154_pm_enter,
	.finish		= lg1154_pm_finish,
	.valid		= suspend_valid_only_mem,
};

static int __init lg1154_pm_init(void)
{
	suspend_set_ops(&lg1154_pm_ops);
	return 0;
}

late_initcall(lg1154_pm_init);
