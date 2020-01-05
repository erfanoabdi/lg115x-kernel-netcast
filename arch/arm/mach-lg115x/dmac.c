#include <linux/kernel.h>

#include <linux/amba/bus.h>
#include <linux/amba/pl08x.h>
#include <linux/init.h>

#include <asm/hardware/pl080.h>

#include <mach/resource.h>

#include "core.h"

#include "dmac.h"

static int pl081_get_signal(struct pl08x_dma_chan *ch)
{
	struct pl08x_channel_data const *cd = ch->cd;

	/* This one has statically assigned channels */

	return cd->min_signal;
}

static void pl081_put_signal(struct pl08x_dma_chan *ch)
{
	/* This one has statically assigned channels */
}

#define PRIMECELL_DEFAULT_CCTL	( \
	(PL080_BSIZE_8 << PL080_CONTROL_SB_SIZE_SHIFT) | \
	(PL080_BSIZE_8 << PL080_CONTROL_DB_SIZE_SHIFT) | \
	(PL080_WIDTH_32BIT << PL080_CONTROL_SWIDTH_SHIFT) | \
	(PL080_WIDTH_32BIT << PL080_CONTROL_DWIDTH_SHIFT) | \
	PL080_CONTROL_PROT_SYS \
	)

static struct pl08x_channel_data dmac_channel_data[] = {
	[0] = {
		.bus_id = "uart0rx",
		.min_signal = 0,
		.max_signal = 0,
		.cctl = PRIMECELL_DEFAULT_CCTL,
	},
	[1] = {
		.bus_id = "uart0tx",
		.min_signal = 1,
		.max_signal = 1,
		.cctl = PRIMECELL_DEFAULT_CCTL,
	},
	[2] = {
		.bus_id = "uart1rx",
		.min_signal = 2,
		.max_signal = 2,
		.cctl = PRIMECELL_DEFAULT_CCTL,
	},
	[3] = {
		.bus_id = "uart1tx",
		.min_signal = 3,
		.max_signal = 3,
		.cctl = PRIMECELL_DEFAULT_CCTL,
	},
	[4] = {
		.bus_id = "uart2rx",
		.min_signal = 4,
		.max_signal = 4,
		.cctl = PRIMECELL_DEFAULT_CCTL,
	},
	[5] = {
		.bus_id = "uart2tx",
		.min_signal = 5,
		.max_signal = 5,
		.cctl = PRIMECELL_DEFAULT_CCTL,
	},
};

static struct pl08x_platform_data dmac_data= {
	.slave_channels		= dmac_channel_data,
	.num_slave_channels	= ARRAY_SIZE(dmac_channel_data),
	.memcpy_channel		= {
		.bus_id		= "memcpy",
		/*
		 * We pass in some optimal memcpy config, the
		 * driver will augment it if need be. 256 byte
		 * bursts and 32bit bus width.
		 */
		.cctl		=
			PL080_BSIZE_256 << PL080_CONTROL_SB_SIZE_SHIFT | \
			PL080_BSIZE_256 << PL080_CONTROL_DB_SIZE_SHIFT | \
			PL080_WIDTH_32BIT << PL080_CONTROL_SWIDTH_SHIFT | \
			PL080_WIDTH_32BIT << PL080_CONTROL_DWIDTH_SHIFT | \
			PL080_CONTROL_PROT_BUFF | \
			PL080_CONTROL_PROT_CACHE | \
			PL080_CONTROL_PROT_SYS,
	},
	.get_signal		= pl081_get_signal,
	.put_signal		= pl081_put_signal,
};

static AMBA_DEVICE(_dmac, "dmac", DMAC, &dmac_data);

void __init lg115x_init_dmac(void)
{
	amba_device_register(&_dmac_device, &iomem_resource);
}

