#include <linux/kernel.h>

#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>

#include <asm/pmu.h>

#include <mach/resource.h>

#include "pmu.h"

static struct resource _pmu_res[] = {
	DEFINE_RES_IRQ_NAMED(PMU0_IRQ, "pmu@cpu0-irq"),
	DEFINE_RES_IRQ_NAMED(PMU1_IRQ, "pmu@cpu1-irq"),
};

static struct platform_device _pmu_dev = {
	.name		= "arm-pmu",
	.id		= ARM_PMU_DEVICE_CPU,
	.num_resources	= ARRAY_SIZE(_pmu_res),
	.resource	= _pmu_res,
};

void __init lg115x_init_pmu(void)
{
	platform_device_register(&_pmu_dev);
}

