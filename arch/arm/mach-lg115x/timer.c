#include <linux/kernel.h>

#include <linux/amba/bus.h>
#include <linux/clocksource.h>
#include <linux/init.h>
#include <linux/io.h>

#include <asm/hardware/arm_timer.h>
#include <asm/hardware/timer-sp.h>
#include <asm/sched_clock.h>
#include <asm/smp_twd.h>

#include <mach/resource.h>
#include <mach/timex.h>

#include "core.h"

#include "clock.h"
#include "timer.h"

static void __init _init_mpcore_glob_timer(void)
{
	/* not implemented yet */
}

static DEFINE_TWD_LOCAL_TIMER(_twd, MPCORE_PTIMER_BASE, MPCORE_PTIMER_IRQ);

static void __init _init_mpcore_priv_timer(void)
{
	twd_local_timer_register(&_twd);
}

static void __init _init_sp804_timer0(void __iomem *base, char const *name)
{
	sp804_clockevents_init(base, TIMER_IRQ, name);
}

#ifndef CONFIG_SP804_CLOCKSOURCE_PRESET

static void __init _init_sp804_timer1(void __iomem *base, char const *name)
{
	sp804_clocksource_and_sched_clock_init(base, name);
}

#else	/* CONFIG_SP804_CLOCKSOURCE_PRESET */

#define SP804_CLOCKSOURCE_PRESET_MULT	CONFIG_SP804_CLOCKSOURCE_PRESET_MULT
#define SP804_CLOCKSOURCE_PRESET_SHIFT	CONFIG_SP804_CLOCKSOURCE_PRESET_SHIFT

static void __iomem *_sched_clock_base;

static u32 _sp804_read(void)
{
	return ~readl_relaxed(_sched_clock_base + TIMER_VALUE);
}

static void __init _init_sp804_timer1(void __iomem *base, char const *name)
{
	/* setup timer 1 as free-running clocksource */
	writel_relaxed(0, base + TIMER_CTRL);
	writel_relaxed(0xffffffff, base + TIMER_LOAD);
	writel_relaxed(0xffffffff, base + TIMER_VALUE);
	writel_relaxed(TIMER_CTRL_32BIT | TIMER_CTRL_ENABLE |
	               TIMER_CTRL_PERIODIC, base + TIMER_CTRL);

	clocksource_mmio_init_preset(base + TIMER_VALUE, name,
	                             SP804_CLOCKSOURCE_PRESET_MULT,
	                             SP804_CLOCKSOURCE_PRESET_SHIFT,
	                             200, 32, clocksource_mmio_readl_down);

	_sched_clock_base = base;
	setup_sched_clock(_sp804_read, 32, AMBA_CLOCK);
}

#endif	/* CONFIG_SP804_CLOCKSOURCE_PRESET */

static void __init _init_sp804_timer(void)
{
	void __iomem *base;

	request_mem_region(TIMER_BASE, SZ_4K, "timers");
	base = ioremap(TIMER_BASE, SZ_4K);

	_init_sp804_timer0(base + TIMER_1_BASE, "timer0");
	_init_sp804_timer1(base + TIMER_2_BASE, "timer1");
}

static AMBA_DEVICE(_wdog, "wdog", WDOG, NULL);

static void __init _init_sp805_watchdog(void)
{
	amba_device_register(&_wdog_device, &iomem_resource);
}

static void __init _init_timer(void)
{
	_init_mpcore_glob_timer();
	_init_mpcore_priv_timer();

	_init_sp804_timer();
}

struct sys_timer lg115x_timer = {
	.init = _init_timer,
};

void __init lg115x_init_timer(void)
{
	_init_sp805_watchdog();
}

