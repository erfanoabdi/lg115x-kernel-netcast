#include <linux/kernel.h>

#include <linux/amba/bus.h>
#include <linux/amba/pl08x.h>
#include <linux/amba/serial.h>
#include <linux/init.h>
#include <linux/delay.h>

#include <mach/resource.h>

#include "core.h"

#include "uart.h"


static void _uart1_mux_disable(void)
{
	unsigned long val;
	unsigned long __iomem *ctr58 = MMIO_P2V(TOP_CTRL_BASE) + 0x0E8;

	/* change uart1 tx to tz */
	val = readl(ctr58) & ~(0x7 << 25);
	writel(val, ctr58);
}

static void _uart1_mux_enable(void)
{
	unsigned long val;
	unsigned long __iomem *ctr58 = MMIO_P2V(TOP_CTRL_BASE) + 0x0E8;

	/* enable cpu uart1 tx */
	val = readl(ctr58) | (0x7 << 25);
	mdelay(1);
	writel(val, ctr58);
}

static struct amba_pl011_data _uart_data[] = {
	[0] = {
		.dma_filter	= pl08x_filter_id,
		.dma_rx_param	= "uart0rx",
		.dma_tx_param	= "uart0tx",
	},
	[1] = {
		.init = _uart1_mux_enable,
		.exit = _uart1_mux_disable,
	/*	.dma_filter	= pl08x_filter_id,
		.dma_rx_param	= "uart1rx",
		.dma_tx_param	= "uart1tx", */
	},
	[2] = {
		.dma_filter	= pl08x_filter_id,
		.dma_rx_param	= "uart2rx",
		.dma_tx_param	= "uart2tx",
	},
};

static AMBA_DEVICE(_uart0, "uart0", UART0, NULL);
static AMBA_DEVICE(_uart1, "uart1", UART1, &_uart_data[1]);
static AMBA_DEVICE(_uart2, "uart2", UART2, NULL);

static struct amba_device *_dev_table[] __initdata = {
	&_uart0_device,
	&_uart1_device,
	&_uart2_device,
	NULL,
};

void __init lg115x_init_uart(void)
{
	struct amba_device **dev;

	/* In order to defend against spurious tx */
	_uart1_mux_disable();

	for(dev = _dev_table; *dev; ++dev)
		amba_device_register(*dev, &iomem_resource);
}

