#include <linux/kernel.h>

#include <linux/amba/bus.h>
#include <linux/amba/pl022.h>

#include <asm-generic/sizes.h>

#include <mach/resource.h>

#include "core.h"

#include "spi.h"

static struct pl022_ssp_controller _spi_data[] = {
	[0] = {
		.bus_id		= 0,
		.num_chipselect	= 1,
		.enable_dma	= 0,
	},
	[1] = {
		.bus_id		= 1,
		.num_chipselect	= 1,
		.enable_dma	= 0,
	},
};

static AMBA_DEVICE(_spi0, "spi0", SPI0, &_spi_data[0]);
static AMBA_DEVICE(_spi1, "spi1", SPI1, &_spi_data[1]);

static struct amba_device *_dev_table[] __initdata = {
	&_spi0_device,
	&_spi1_device,
	NULL,
};

void __init lg115x_init_spi(void)
{
	struct amba_device **dev;

	for(dev = _dev_table; *dev; ++dev)
		amba_device_register(*dev, &iomem_resource);
}

