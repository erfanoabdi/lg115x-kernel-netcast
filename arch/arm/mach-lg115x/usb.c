#include <linux/kernel.h>

#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/usb/ehci_pdriver.h>
#include <linux/usb/ohci_pdriver.h>

#include <mach/resource.h>
#include <linux/delay.h>

#include "usb.h"


#ifdef CONFIG_USB_XHCI_LG115X

static u64 _xhci_dma_mask = DMA_BIT_MASK(32);

static struct resource _xhci0_res[] = {
	DEFINE_RES_MEM_NAMED(XHCI0_BASE, SZ_4K, "xhci0-reg"),
	DEFINE_RES_IRQ_NAMED(XHCI0_IRQ,         "xhci0-irq"),
};

static struct platform_device _xhci0_dev = {
	.name		= "xhci",
	.id		= 0,
	.dev = {
		.dma_mask			= &_xhci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= 0,
	},
	.num_resources	= ARRAY_SIZE(_xhci0_res),
	.resource	= _xhci0_res,
};

#define USB3_CR_CAP_ADDR (1<<19)
#define USB3_CR_ACK      (1<<16)

static u32 xhci_access_check(void)
{
	u32 reg0;
	u16 address = 0x1018;

	u32 status = 0;

	volatile u32 * ptr_reg0;
	volatile u32 * ptr_reg1;

	ptr_reg0 = ( volatile u32 *)(MMIO_P2V(TOP_CTRL_BASE) + 0x1E0);
	ptr_reg1 = ( volatile u32 *)(MMIO_P2V(TOP_CTRL_BASE) + 0x1E4) ;

	/* capture address */
	reg0  = 0;
	reg0 |= address;
	*ptr_reg0 = reg0;
	reg0 |= USB3_CR_CAP_ADDR;
	*ptr_reg0 = reg0;

	mdelay(1);

	/* check whether or not access for usb30 xhci register is possible. */
	if((*ptr_reg1 & USB3_CR_ACK))
		status = 1;

	*ptr_reg0 = 0;

	return status;
}

#endif

#ifdef CONFIG_USB_EHCI_LG115X

static struct usb_ehci_pdata _ehci_pdata = {
	.caps_offset		= 0,
	.has_tt			= 0,
	.has_synopsys_hc_bug	= 1,
	.big_endian_desc	= 0,
	.big_endian_mmio	= 0,
	.port_power_on		= 1,
	.port_power_off		= 0,
};

static u64 _ehci_dma_mask = DMA_BIT_MASK(32);

static struct resource _ehci0_res[] = {
	DEFINE_RES_MEM_NAMED(EHCI0_BASE, SZ_4K, "ehci0-reg"),
	DEFINE_RES_IRQ_NAMED(EHCI0_IRQ,         "ehci0-irq"),
};

static struct resource _ehci1_res[] = {
	DEFINE_RES_MEM_NAMED(EHCI1_BASE, SZ_4K, "ehci1-reg"),
	DEFINE_RES_IRQ_NAMED(EHCI1_IRQ,         "ehci1-irq"),
};

static struct resource _ehci2_res[] = {
	DEFINE_RES_MEM_NAMED(EHCI2_BASE, SZ_4K, "ehci2-reg"),
	DEFINE_RES_IRQ_NAMED(EHCI2_IRQ,         "ehci2-irq"),
};

static struct platform_device _ehci0_dev = {
	.name		= "ehci",
	.id		= 0,
	.dev		= {
		.dma_mask		= &_ehci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &_ehci_pdata,
	},
	.num_resources	= ARRAY_SIZE(_ehci0_res),
	.resource	= _ehci0_res,
};

static struct platform_device _ehci1_dev = {
	.name		= "ehci",
	.id		= 1,
	.dev		= {
		.dma_mask		= &_ehci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &_ehci_pdata,
	},
	.num_resources	= ARRAY_SIZE(_ehci1_res),
	.resource	= _ehci1_res,
};

static struct platform_device _ehci2_dev = {
	.name		= "ehci",
	.id		= 2,
	.dev		= {
		.dma_mask		= &_ehci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &_ehci_pdata,
	},
	.num_resources	= ARRAY_SIZE(_ehci2_res),
	.resource	= _ehci2_res,
};

#endif

#ifdef CONFIG_USB_OHCI_LG115X

static struct usb_ohci_pdata _ohci_pdata = {
	.big_endian_desc	= 0,
	.big_endian_mmio	= 0,
	.no_big_frame_no	= 0,
};

static u64 _ohci_dma_mask = DMA_BIT_MASK(32);

static struct resource _ohci0_res[] = {
	DEFINE_RES_MEM_NAMED(OHCI0_BASE, SZ_4K, "ohci0-reg"),
	DEFINE_RES_IRQ_NAMED(OHCI0_IRQ,         "ohci0-irq"),
};

static struct resource _ohci1_res[] = {
	DEFINE_RES_MEM_NAMED(OHCI1_BASE, SZ_4K, "ohci1-reg"),
	DEFINE_RES_IRQ_NAMED(OHCI1_IRQ,         "ohci1-irq"),
};

static struct resource _ohci2_res[] = {
	DEFINE_RES_MEM_NAMED(OHCI2_BASE, SZ_4K, "ohci2-reg"),
	DEFINE_RES_IRQ_NAMED(OHCI2_IRQ,         "ohci2-irq"),
};

static struct platform_device _ohci0_dev = {
	.name		= "ohci",
	.id		= 0,
	.dev		= {
		.dma_mask		= &_ohci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &_ohci_pdata,
	},
	.num_resources	= ARRAY_SIZE(_ohci0_res),
	.resource	= _ohci0_res,
};

static struct platform_device _ohci1_dev = {
	.name		= "ohci",
	.id		= 1,
	.dev		= {
		.dma_mask		= &_ohci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &_ohci_pdata,
	},
	.num_resources	= ARRAY_SIZE(_ohci1_res),
	.resource	= _ohci1_res,
};

static struct platform_device _ohci2_dev = {
	.name		= "ohci",
	.id		= 2,
	.dev		= {
		.dma_mask		= &_ohci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platform_data		= &_ohci_pdata,
	},
	.num_resources	= ARRAY_SIZE(_ohci2_res),
	.resource	= _ohci2_res,
};

#endif

void __init lg115x_init_usb(void)
{
#ifdef CONFIG_USB_XHCI_LG115X
	if(xhci_access_check())
		platform_device_register(&_xhci0_dev);
#endif
#ifdef CONFIG_USB_EHCI_LG115X
	platform_device_register(&_ehci0_dev);
	platform_device_register(&_ehci1_dev);
	platform_device_register(&_ehci2_dev);
#endif
#ifdef CONFIG_USB_OHCI_LG115X
	platform_device_register(&_ohci0_dev);
	platform_device_register(&_ohci1_dev);
	platform_device_register(&_ohci2_dev);
#endif
}

