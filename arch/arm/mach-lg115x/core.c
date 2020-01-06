#include <linux/kernel.h>

#include <linux/compiler.h>
#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/memblock.h>
#include <linux/lgsnap.h>

#include <asm/hardware/gic.h>
#include <asm/io.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/memory.h>
#include <asm-generic/sizes.h>

#include <generated/mach-types.h>

#include <mach/resource.h>

#include "core.h"

#include "clock.h"
#include "dmac.h"
#include "emac.h"
#include "emmc.h"
#include "gpio.h"
#include "l2cc.h"
#include "pmu.h"
#include "spi.h"
#include "timer.h"
#include "uart.h"
#include "usb.h"
#include "xip.h"
#include "ramoops.h"

static void __init _fixup(struct tag *tag, char **from, struct meminfo *meminfo)
{
	/* currently, nothing */
}

static void __init _reserve(void)
{
	lg115x_prep_emac();
	lg115x_prep_xip();

#ifdef CONFIG_LGSNAP
	lgsnap_reserve_bl_region();
#endif
}

static struct map_desc _io_desc[] __initdata = {
	{
		.virtual        = __MMIO_P2V(MPCORE_PERIPH_BASE),
		.pfn            = __phys_to_pfn(MPCORE_PERIPH_BASE),
		.length         = SZ_8K,
		.type           = MT_DEVICE,
	},
	{
		.virtual        = __MMIO_P2V(L2CC_BASE),
		.pfn            = __phys_to_pfn(L2CC_BASE),
		.length         = SZ_4K,
		.type           = MT_DEVICE,
	},
#ifdef CONFIG_LGSNAP
	{
		.virtual	= __MMIO_P2V(TIMER_BASE),
		.pfn		= __phys_to_pfn(TIMER_BASE),
		.length 	= SZ_4K,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= __MMIO_P2V(UART0_BASE),
		.pfn		= __phys_to_pfn(UART0_BASE),
		.length 	= SZ_4K,
		.type		= MT_DEVICE,
	},
#endif
#ifdef CONFIG_CLOCK_DETECTION
	{
		.virtual	= __MMIO_P2V(TOP_CTRL_BASE),
		.pfn		= __phys_to_pfn(TOP_CTRL_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
#endif
	{
		.virtual	= __MMIO_P2V(CPU_CTRL_BASE),
		.pfn		= __phys_to_pfn(CPU_CTRL_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

static void __init _map_io(void)
{
	init_consistent_dma_size(14 << 20);
	iotable_init(_io_desc, ARRAY_SIZE(_io_desc));
}

static void __init _init_early(void)
{
	lg115x_init_clock();

	/*
	 * We should enable PL310 in early stage. PL310 activation is done
	 * by a support code in the secure monitor, and the secure monitor
	 * runs only on the core #0.
	 */
	lg115x_init_l2cc();
}

static void __init _init_irq(void)
{
	gic_init(0, 29, MMIO_P2V(MPCORE_GIC_DIST_BASE),
			MMIO_P2V(MPCORE_GIC_CTRL_BASE));
}

static void __init _init_machine(void)
{
	lg115x_init_dmac();
	lg115x_init_emac();
	lg115x_init_emmc();
	lg115x_init_gpio();
	lg115x_init_pmu();
	lg115x_init_spi();
	lg115x_init_timer();
	lg115x_init_uart();
	lg115x_init_usb();
    lg115x_init_ramoops();
}

static void _restart(char mode, char const *cmd)
{
	void __iomem *wdt_base;

	/*
	 * try to reset by MPcore watchdog timer
	 */
	wdt_base = MMIO_P2V(MPCORE_WDOG_BASE);
	writel_relaxed(0x0000, wdt_base + 0x08);
	writel_relaxed(0x0000, wdt_base + 0x00);
	writel_relaxed(0x0009, wdt_base + 0x08);

	/*
	 * try to reset by sp805 watchdog timer
	 */
	wdt_base = ioremap(WDOG_BASE, SZ_4K);
	writel_relaxed(0x0000, wdt_base + 0x08);
	writel_relaxed(0x0000, wdt_base + 0x00);
	writel_relaxed(0x0003, wdt_base + 0x08);
}
#ifdef CONFIG_MACH_LG1154
MACHINE_START(LG1154, "LG Electronics Ltd LG1154-based board")
#elif defined ( CONFIG_MACH_LG1152 )
MACHINE_START(LG1152, "LG Electronics Ltd LG1152-based board")
#else
#error "Machine type is not specified"
#endif
	.atag_offset	= 0x00000100,
	.fixup		= _fixup,
	.reserve	= _reserve,
	.map_io		= _map_io,
	.init_early	= _init_early,
	.init_irq	= _init_irq,
	.timer		= &lg115x_timer,
	.init_machine	= _init_machine,
	.handle_irq	= gic_handle_irq,
	.restart	= _restart,
MACHINE_END

