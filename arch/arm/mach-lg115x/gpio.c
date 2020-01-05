#include <linux/kernel.h>

#include <linux/amba/bus.h>
#include <linux/amba/pl061.h>
#include <linux/init.h>

#include <asm-generic/sizes.h>

#include <mach/resource.h>

#include "core.h"

#include "gpio.h"

struct pl061_platform_data _gpio_data[] = {
	[ 0] = { .gpio_base =   0, },
	[ 1] = { .gpio_base =   8, },
	[ 2] = { .gpio_base =  16, },
	[ 3] = { .gpio_base =  24, },
	[ 4] = { .gpio_base =  32, },
	[ 5] = { .gpio_base =  40, },
	[ 6] = { .gpio_base =  48, },
	[ 7] = { .gpio_base =  56, },
	[ 8] = { .gpio_base =  64, },
	[ 9] = { .gpio_base =  72, },
	[10] = { .gpio_base =  80, },
	[11] = { .gpio_base =  88, },
	[12] = { .gpio_base =  96, },
	[13] = { .gpio_base = 104, },
	[14] = { .gpio_base = 112, },
	[15] = { .gpio_base = 120, },
	[16] = { .gpio_base = 128, },
	[17] = { .gpio_base = 136, },
};

static AMBA_DEVICE(_gpio_0, "gpio_0", GPIO_0, &_gpio_data[ 0]);
static AMBA_DEVICE(_gpio_1, "gpio_1", GPIO_1, &_gpio_data[ 1]);
static AMBA_DEVICE(_gpio_2, "gpio_2", GPIO_2, &_gpio_data[ 2]);
static AMBA_DEVICE(_gpio_3, "gpio_3", GPIO_3, &_gpio_data[ 3]);
static AMBA_DEVICE(_gpio_4, "gpio_4", GPIO_4, &_gpio_data[ 4]);
static AMBA_DEVICE(_gpio_5, "gpio_5", GPIO_5, &_gpio_data[ 5]);
static AMBA_DEVICE(_gpio_6, "gpio_6", GPIO_6, &_gpio_data[ 6]);
static AMBA_DEVICE(_gpio_7, "gpio_7", GPIO_7, &_gpio_data[ 7]);
static AMBA_DEVICE(_gpio_8, "gpio_8", GPIO_8, &_gpio_data[ 8]);
static AMBA_DEVICE(_gpio_9, "gpio_9", GPIO_9, &_gpio_data[ 9]);
static AMBA_DEVICE(_gpio10, "gpio10", GPIO10, &_gpio_data[10]);
static AMBA_DEVICE(_gpio11, "gpio11", GPIO11, &_gpio_data[11]);
static AMBA_DEVICE(_gpio12, "gpio12", GPIO12, &_gpio_data[12]);
static AMBA_DEVICE(_gpio13, "gpio13", GPIO13, &_gpio_data[13]);
static AMBA_DEVICE(_gpio14, "gpio14", GPIO14, &_gpio_data[14]);
static AMBA_DEVICE(_gpio15, "gpio15", GPIO15, &_gpio_data[15]);
static AMBA_DEVICE(_gpio16, "gpio16", GPIO16, &_gpio_data[16]);
static AMBA_DEVICE(_gpio17, "gpio17", GPIO17, &_gpio_data[17]);

static struct amba_device *_dev_table[] __initdata = {
	&_gpio_0_device,
	&_gpio_1_device,
	&_gpio_2_device,
	&_gpio_3_device,
	&_gpio_4_device,
	&_gpio_5_device,
	&_gpio_6_device,
	&_gpio_7_device,
	&_gpio_8_device,
	&_gpio_9_device,
	&_gpio10_device,
	&_gpio11_device,
	&_gpio12_device,
	&_gpio13_device,
	&_gpio14_device,
	&_gpio15_device,
	&_gpio16_device,
	&_gpio17_device,
	NULL,
};

void __init lg115x_init_gpio(void)
{
	struct amba_device **dev;

	for(dev = _dev_table; *dev; ++dev)
		amba_device_register(*dev, &iomem_resource);
}

