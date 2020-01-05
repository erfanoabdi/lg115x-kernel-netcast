#include <linux/kernel.h>

#include <linux/delay.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/platform_device.h>

#include <asm/memblock.h>
#include <asm-generic/sizes.h>

#include <mach/emac.h>
#include <mach/resource.h>

#include "emac.h"

static struct emac_platform_data _emac_data;

static struct resource _emac_res[] = {
	DEFINE_RES_MEM_NAMED(EMAC_BASE, SZ_1K, "emac-reg"),
	DEFINE_RES_IRQ_NAMED(EMAC_IRQ,         "emac-irq"),
};

static struct platform_device _emac_dev = {
	.name		= "emac-ahb",
	.id		= 0,
	.dev		= {
		.platform_data	= &_emac_data,
	},
	.num_resources	= ARRAY_SIZE(_emac_res),
	.resource	= _emac_res,
};

void __init lg115x_prep_emac(void)
{
	size_t size = ALIGN((TX_QSIZE + RX_QSIZE) << 4, PAGE_SIZE);
	_emac_data.desc_phys = arm_memblock_steal(size, PAGE_SIZE);
	_emac_data.txd_count = TX_QSIZE;
	_emac_data.rxd_count = RX_QSIZE;
}

#ifdef CONFIG_MACH_LG1154
static int _fixup_run(struct phy_device *phydev)
{
	struct net_device *netdev = (struct net_device *)phydev->bus->priv;
	void __iomem *base;

	/* skip possible broadcasting address */
	if(phydev->addr == 0)
		return 0;

	/*
	 * RTL8201F: cold-reset by GPIO27
	 */
	base = ioremap(GPIO_3_BASE, SZ_4K);
	writel_relaxed(readl_relaxed(base + 0x400) | 0x08, base + 0x400);
	writel_relaxed(0x00, base + 0x020);
	msleep(10);
	writel_relaxed(0x08, base + 0x020);
	msleep(150);
	writel_relaxed(readl_relaxed(base + 0x400) & 0xf7, base + 0x400);
	iounmap(base);

	/*
	 * RTL8201F: set MAC address
	 */
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0012);
	mdiobus_write(phydev->bus, phydev->addr, 0x10,
	              *(unsigned short *)&netdev->dev_addr[0]);
	mdiobus_write(phydev->bus, phydev->addr, 0x11,
	              *(unsigned short *)&netdev->dev_addr[2]);
	mdiobus_write(phydev->bus, phydev->addr, 0x12,
	              *(unsigned short *)&netdev->dev_addr[4]);

	/*
	 * RTL8201F: set max packet length
	 */
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0011);
	mdiobus_write(phydev->bus, phydev->addr, 0x11, 0x1fff);

	/*
	 * RTL8201F: wake up frame select and enable -- magic packet only
	 */
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0011);
	mdiobus_write(phydev->bus, phydev->addr, 0x10, 0x1000);

	/*
	 * RTL8201F: enable WOL
	 */
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0007);
	mdiobus_write(phydev->bus, phydev->addr, 0x13,
	              mdiobus_read(phydev->bus, phydev->addr, 0x13) | 0x0400);

#ifdef CONFIG_EPHY_NO_EEE
	/*
	 * RTL8201F: disable EEE for better compatibility
	 */
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0004);
	mdiobus_write(phydev->bus, phydev->addr, 0x10, 0x4077);
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0000);
	mdiobus_write(phydev->bus, phydev->addr, 0x0d, 0x0007);
	mdiobus_write(phydev->bus, phydev->addr, 0x0e, 0x003c);
	mdiobus_write(phydev->bus, phydev->addr, 0x0d, 0x4007);
	mdiobus_write(phydev->bus, phydev->addr, 0x0e, 0x0000);
#endif

	/*
	 * RTL8201F: adjust RMII mode setting
	 */
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0007);
	mdiobus_write(phydev->bus, phydev->addr, 0x10, 0x077a);

	/*
	 * RTL8201F: return to page 0
	 */
	mdiobus_write(phydev->bus, phydev->addr, 0x1f, 0x0000);

	return 0;
}
#endif

void __init lg115x_init_emac(void)
{
	#ifdef CONFIG_MACH_LG1154
	phy_register_fixup_for_uid(0x001cc816, 0xfffffff0, _fixup_run);
	#endif
	platform_device_register(&_emac_dev);
}

