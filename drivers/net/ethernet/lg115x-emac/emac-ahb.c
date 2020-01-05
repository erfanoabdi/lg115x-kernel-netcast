#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/crc32.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/mii.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/timer.h>

#include <asm/dma-mapping.h>
#include <asm/io.h>
#include <asm-generic/sizes.h>

#include <mach/emac.h>

#include "emac-ahb.h"

#define EMAC_FRAME_LEN	(NET_IP_ALIGN + ETH_FRAME_LEN + ETH_FCS_LEN)
#define EMAC_INSTANCES	1

static unsigned char _addr[EMAC_INSTANCES][ETH_ALEN];
static size_t _addr_count;

static int __init _ethaddr_setup(char *str)
{
	unsigned char addr[ETH_ALEN];
	int i;

	if(_addr_count >= EMAC_INSTANCES)
		return -ENOMEM;

	for(i = 0; i < ETH_ALEN; ++i)
	{
		addr[i] = simple_strtoul(str, &str, 16);
		if(*str == ':' || *str == '-')
			++str;
	}

	memcpy(_addr[_addr_count++], addr, ETH_ALEN);

	return 0;
}
__setup("ethaddr=", _ethaddr_setup);

static size_t _instance;

/*
 * PHY support
 */

static void _phy_notifier(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	struct phy_device *phy_dev = priv->phy_dev;
	unsigned long ctrl = 0;
	unsigned long flags;

	BUG_ON(!phy_dev);

	spin_lock_irqsave(&priv->lock, flags);

	if(!phy_dev->link)
	{
		netdev_info(dev, "physical link lost\n");

		netif_carrier_off(dev);
		netif_stop_queue(dev);
	}
	else
	{
		if(phy_dev->speed == SPEED_100)
			ctrl |= 0x01;
		if(phy_dev->duplex == DUPLEX_FULL)
			ctrl |= 0x04;

		writel_relaxed(ctrl, priv->reg_base + MAC_GLOBAL_CTRL);

		if(!priv->link)
		{
			netdev_info(dev, "physical link established\n");

			netif_carrier_on(dev);
			netif_wake_queue(dev);
		}

		if(phy_dev->speed != priv->speed ||
		   phy_dev->duplex != priv->duplex)
		{
			netdev_info(dev, "link mode: %dMbps/%cDX\n",
			            phy_dev->speed == SPEED_100 ? 100 : 10,
			            phy_dev->duplex == DUPLEX_FULL ? 'F' : 'H');
		}
	}

	priv->link = phy_dev->link;
	priv->speed = phy_dev->speed;
	priv->duplex = phy_dev->duplex;

	spin_unlock_irqrestore(&priv->lock, flags);
}

/*
 * MDIO bus support
 */

static int _mii_bus_read(struct mii_bus *mii, int phy, int reg)
{
	struct net_device *dev = (struct net_device *)mii->priv;
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	unsigned long val;

	/* trigger MDIO reading */
	writel_relaxed((phy & 0x1f) | ((reg & 0x1f) << 5) | 0x8400,
	               priv->reg_base + MAC_MDIO_CTRL);
	/* busy-wait for completion */
	while(readl_relaxed(priv->reg_base + MAC_MDIO_CTRL) & 0x8000);
	/* return read value */
	val = readl_relaxed(priv->reg_base + MAC_MDIO_DATA);

	return (int)(val & 0xffff);
}

static int _mii_bus_write(struct mii_bus *mii, int phy, int reg, u16 val)
{
	struct net_device *dev = (struct net_device *)mii->priv;
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	/* store value written */
	writel_relaxed(val & 0xffff, priv->reg_base + MAC_MDIO_DATA);
	/* trigger MDIO writing */
	writel_relaxed((phy & 0x1f) | ((reg & 0x1f) << 5) | 0x8000,
	               priv->reg_base + MAC_MDIO_CTRL);
	/* busy-wait for completion */
	while(readl_relaxed(priv->reg_base + MAC_MDIO_CTRL) & 0x8000);

	return 0;
}

static int _mii_bus_reset(struct mii_bus *mii)
{
	/* not implemented yet */

	return 0;
}

static int _mdio_probe(struct mii_bus *mii)
{
	struct net_device *dev = (struct net_device *)mii->priv;
	struct emac_priv *priv = netdev_priv(dev);
	int phy_addr;

	priv->phy_dev = NULL;

	/* skip 0-address because it's possibly the broadcast address */
	for(phy_addr = 1; phy_addr < PHY_MAX_ADDR; ++phy_addr)
	{
		if(mii->phy_map[phy_addr])
		{
			/* use the first-found PHY only */
			priv->phy_dev = mii->phy_map[phy_addr];
			break;
		}
	}

	if(!priv->phy_dev)
	{
		netdev_err(dev, "failed to find a PHY chip\n");
		return -ENODEV;
	}

	BUG_ON(priv->phy_dev->attached_dev);

	priv->phy_dev = phy_connect(dev, dev_name(&priv->phy_dev->dev),
	                            _phy_notifier, 0, PHY_INTERFACE_MODE_RMII);
	if(IS_ERR(priv->phy_dev))
	{
		netdev_err(dev, "failed to phy_connect\n");
		return PTR_ERR(priv->phy_dev);
	}

	priv->phy_dev->supported &= SUPPORTED_10baseT_Half |
	                            SUPPORTED_10baseT_Full |
	                            SUPPORTED_100baseT_Half |
	                            SUPPORTED_100baseT_Full |
	                            SUPPORTED_Autoneg |
	                            SUPPORTED_MII |
	                            SUPPORTED_TP;

	priv->phy_dev->advertising = priv->phy_dev->supported;

	priv->link = 0;
	priv->speed = SPEED_UNKNOWN;
	priv->duplex = DUPLEX_UNKNOWN;

	netdev_info(dev, "PHY attached: %s @ address %d using irq %d\n",
	            priv->phy_dev->drv->name, phy_addr, priv->phy_dev->irq);

	return 0;
}

static void _mdio_remove(struct mii_bus *mii)
{
	struct net_device *dev = (struct net_device *)mii->priv;
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	phy_disconnect(priv->phy_dev);

	priv->phy_dev = NULL;
}

/*
 * MAC support
 */

static unsigned long _mac_get_rx_stats(struct net_device *dev, int counter)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	/* trigger counter reading */
	writel_relaxed(counter | 0x8000, priv->reg_base + MAC_RX_STATS_CTRL);
	/* busy-wait for completion */
	while(readl_relaxed(priv->reg_base + MAC_RX_STATS_CTRL) & 0x8000);
	/* return read value */

	return readl_relaxed(priv->reg_base + MAC_RX_STATS_DATA_HI) << 16 |
	       readl_relaxed(priv->reg_base + MAC_RX_STATS_DATA_LO);
}

static unsigned long _mac_get_tx_stats(struct net_device *dev, int counter)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	/* trigger counter reading */
	writel_relaxed(counter | 0x8000, priv->reg_base + MAC_TX_STATS_CTRL);
	/* busy-wait for completion */
	while(readl_relaxed(priv->reg_base + MAC_TX_STATS_CTRL) & 0x8000);
	/* return read value */

	return readl_relaxed(priv->reg_base + MAC_TX_STATS_DATA_HI) << 16 |
	       readl_relaxed(priv->reg_base + MAC_TX_STATS_DATA_LO);
}

static void _mac_set_rx_promisc(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	writel_relaxed(0x0100, priv->reg_base + MAC_ADDR_CTRL);
}

static void _mac_set_rx_allmulti(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	writel_relaxed(~0x00, priv->reg_base + MAC_MULTICAST_HASH1);
	writel_relaxed(~0x00, priv->reg_base + MAC_MULTICAST_HASH2);
	writel_relaxed(~0x00, priv->reg_base + MAC_MULTICAST_HASH3);
	writel_relaxed(~0x00, priv->reg_base + MAC_MULTICAST_HASH4);
}

static void _mac_set_rx_mc_list(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	struct netdev_hw_addr *ha;
	unsigned long hash[4] = { 0, };
	u32 crc;

	netdev_for_each_mc_addr(ha, dev)
	{
		crc = ether_crc(ETH_ALEN, ha->addr);
		crc = (crc >> 26) & 0x3f;
		hash[crc >> 4] |= 1 << (crc & 0x0f);
	}

	writel_relaxed(hash[0], priv->reg_base + MAC_MULTICAST_HASH1);
	writel_relaxed(hash[1], priv->reg_base + MAC_MULTICAST_HASH2);
	writel_relaxed(hash[2], priv->reg_base + MAC_MULTICAST_HASH3);
	writel_relaxed(hash[3], priv->reg_base + MAC_MULTICAST_HASH4);
}

static void _mac_set_rx_uc_list(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	struct netdev_hw_addr *ha;
	int i = 0;

	writel_relaxed((unsigned long)*(unsigned short *)&dev->dev_addr[0],
	               priv->reg_base + MAC_ADDR1_HI);
	writel_relaxed((unsigned long)*(unsigned short *)&dev->dev_addr[2],
	               priv->reg_base + MAC_ADDR1_ME);
	writel_relaxed((unsigned long)*(unsigned short *)&dev->dev_addr[4],
	               priv->reg_base + MAC_ADDR1_LO);

	netdev_for_each_uc_addr(ha, dev)
	{
		writel_relaxed((unsigned long)*(unsigned short *)&ha->addr[0],
		               priv->reg_base + MAC_ADDR2_HI + i * 0x0c);
		writel_relaxed((unsigned long)*(unsigned short *)&ha->addr[2],
		               priv->reg_base + MAC_ADDR2_ME + i * 0x0c);
		writel_relaxed((unsigned long)*(unsigned short *)&ha->addr[4],
		               priv->reg_base + MAC_ADDR2_LO + i * 0x0c);
		++i;
	}

	writel_relaxed((1 << (netdev_uc_count(dev) + 1)) - 1,
	               priv->reg_base + MAC_ADDR_CTRL);
}

static int _mac_init(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	/* stop both Rx/Tx MAC */
	writel_relaxed(0x00, priv->reg_base + MAC_RX_CTRL);
	writel_relaxed(0x00, priv->reg_base + MAC_TX_CTRL);
	
	/* reset MAC counters */
	writel_relaxed(0x18, priv->reg_base + MAC_GLOBAL_CTRL);

	msleep(1);

	/* clear reset and initially setup 10Mbps/HDX */
	writel_relaxed(0x00, priv->reg_base + MAC_GLOBAL_CTRL);

	/* ?MAGIC VALUE? -- Tx FIFO almost-full threshold */
	writel_relaxed(0x01f8, priv->reg_base + MAC_TX_FIFO_ALMOST_FULL);

	/* setup MAC Rx/Tx start threshold */
	writel_relaxed(ETH_ALEN * 2, priv->reg_base + MAC_RX_START_THRESHOLD);
	writel_relaxed(ETH_FRAME_LEN + ETH_FCS_LEN,
	               priv->reg_base + MAC_TX_START_THRESHOLD);

	/* start both Rx/Tx MAC in proper mode */
	writel_relaxed(0x09, priv->reg_base + MAC_RX_CTRL);
	writel_relaxed(0x09, priv->reg_base + MAC_TX_CTRL);

	/* stop both Rx/Tx DMA */
	writel_relaxed(0x00, priv->reg_base + DMA_CTRL);

	/* soft-reset DMA controller */
	writel_relaxed(0x00000001, priv->reg_base + DMA_CONF);

	msleep(1);

	/* clear reset and setup DMA burst mode */
	writel_relaxed(0x00020020, priv->reg_base + DMA_CONF);

	msleep(1);

	/* clear ring pointers to force update */
	writel_relaxed(0x00, priv->reg_base + DMA_RX_BASE_ADDR);
	writel_relaxed(0x00, priv->reg_base + DMA_TX_BASE_ADDR);

	/* setup DMA Rx/Tx descriptor ring pointers */
	writel_relaxed(priv->rxd_phys, priv->reg_base + DMA_RX_BASE_ADDR);
	writel_relaxed(priv->txd_phys, priv->reg_base + DMA_TX_BASE_ADDR);

	/* do not use auto-poll feature */
	writel_relaxed(0x00, priv->reg_base + DMA_TX_AUTO_POLL_CNTR);

	/* start both Rx/Tx DMA */
	writel_relaxed(0x03, priv->reg_base + DMA_CTRL);

	return 0;
}

static int _mac_start(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	/* clear all interrupts */
	writel_relaxed(0xff, priv->reg_base + DMA_STAT_INTR);

	/* enable MAC interrupt(s) -- currently nothing */
	writel_relaxed(0x00, priv->reg_base + MAC_INTR_ENABLE);
	/* enable DMA interrupt(s) -- only Rx/Tx done INTRs */
	writel_relaxed(0x11, priv->reg_base + DMA_INTR_ENABLE);

	return 0;
}

static int _mac_stop(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	/* disable DMA interrupts */
	writel_relaxed(0x00, priv->reg_base + DMA_INTR_ENABLE);
	/* disable MAC interrupts */
	writel_relaxed(0x00, priv->reg_base + MAC_INTR_ENABLE);

	return 0;
}

/*
 * network driver support
 */

void _drv_handle_tx(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	while(priv->txd_used)
	{
		if(priv->txd[priv->txd_tail].own)
			break;

		dma_unmap_single(&dev->dev,
		                 priv->txd[priv->txd_tail].addr1,
		                 priv->txd[priv->txd_tail].size1,
		                 DMA_TO_DEVICE);

		dev_kfree_skb_any(priv->txd[priv->txd_tail].addr2);

		priv->txd_tail = (priv->txd_tail + 1) % priv->txd_count;
		priv->txd_used--;
	}
}

void _drv_handle_rx(struct net_device *dev)
{
	struct emac_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	dma_addr_t dma;

	while(!priv->rxd[priv->rxd_next].own)
	{
		dma_unmap_single(&dev->dev,
		                 priv->rxd[priv->rxd_next].addr1,
		                 priv->rxd[priv->rxd_next].size1,
		                 DMA_FROM_DEVICE);

		skb = priv->rxd[priv->rxd_next].addr2;
		skb_put(skb, priv->rxd[priv->rxd_next].length);
		skb->protocol = eth_type_trans(skb, dev);

		netif_rx(skb);

		skb = dev_alloc_skb(EMAC_FRAME_LEN + NET_IP_ALIGN);
		skb->dev = dev;
		skb_reserve(skb, NET_IP_ALIGN);

		dma = dma_map_single(&dev->dev, skb->data, EMAC_FRAME_LEN,
		                     DMA_FROM_DEVICE);

		priv->rxd[priv->rxd_next].size1 = EMAC_FRAME_LEN;
		priv->rxd[priv->rxd_next].size2 = 0;
		priv->rxd[priv->rxd_next].addr1 = dma;
		priv->rxd[priv->rxd_next].addr2 = skb;

		priv->rxd[priv->rxd_next].own = 1;
		
		priv->rxd_next = (priv->rxd_next + 1) % priv->rxd_count;
	}
}

static irqreturn_t _drv_isr(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	unsigned long status;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	status = readl_relaxed(priv->reg_base + DMA_STAT_INTR);

	/* handle any Tx frame(s) */
	if(status & 0x01)
		_drv_handle_tx(dev);
	/* handle any Rx frame(s) */
	if(status & 0x10)
		_drv_handle_rx(dev);

	writel_relaxed(status & 0xff, priv->reg_base + DMA_STAT_INTR);

	spin_unlock_irqrestore(&priv->lock, flags);

	return IRQ_HANDLED;
}

static int _drv_alloc_tx(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	int i;

	memset(priv->txd, 0, sizeof(struct emac_txd) * priv->txd_count);

	for(i = 0; i < priv->txd_count; ++i)
	{
		/* currently nothing */
	}

	priv->txd[priv->txd_count - 1].end = 1;

	priv->txd_tail = priv->txd_head;
	priv->txd_used = 0;

	return 0;
}

static int _drv_free_tx(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	int i;

	for(i = 0; i < priv->txd_count; ++i)
	{
		if(!priv->txd[i].own)
			continue;

		priv->txd[i].own = 0;

		dma_unmap_single(&dev->dev, priv->txd[i].addr1,
		                 priv->txd[i].size1, DMA_TO_DEVICE);
		kfree_skb(priv->txd[i].addr2);
	}

	return 0;
}

static int _drv_alloc_rx(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	struct sk_buff *skb;
	dma_addr_t dma;
	int i;

	memset(priv->rxd, 0, sizeof(struct emac_rxd) * priv->rxd_count);

	for(i = 0; i < priv->rxd_count; ++i)
	{
		skb = alloc_skb(EMAC_FRAME_LEN + NET_IP_ALIGN, GFP_KERNEL);
		skb->dev = dev;
		skb_reserve(skb, NET_IP_ALIGN);

		dma = dma_map_single(&dev->dev, skb->data, EMAC_FRAME_LEN,
		                     DMA_FROM_DEVICE);

		priv->rxd[i].size1 = EMAC_FRAME_LEN;
		priv->rxd[i].size2 = 0;
		priv->rxd[i].addr1 = dma;
		priv->rxd[i].addr2 = skb;

		priv->rxd[i].own = 1;
	}

	priv->rxd[priv->rxd_count - 1].end = 1;

	return 0;
}

static int _drv_free_rx(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	int i;

	for(i = 0; i < priv->rxd_count; ++i)
	{
		priv->rxd[i].own = 0;

		dma_unmap_single(&dev->dev, priv->rxd[i].addr1,
		                 priv->rxd[i].size1, DMA_FROM_DEVICE);
		kfree_skb(priv->rxd[i].addr2);
	}

	return 0;
}

static int _drv_init(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	int err;

	/*
	 * remap registers
	 */

	priv->reg_base = (void __iomem *)ioremap(dev->base_addr, SZ_1K);
	if(!priv->reg_base)
	{
		netdev_err(dev, "failed to ioremap\n");
		err = -ENXIO;
		goto _quit_0;
	}

	priv->desc_virt = (void __iomem *)ioremap(priv->desc_phys,
	                                          priv->desc_size);
	if(!priv->desc_virt)
	{
		netdev_err(dev, "failed to ioremap\n");
		err = -ENXIO;
		goto _quit_1;
	}

	priv->txd = priv->desc_virt;
	priv->rxd = priv->desc_virt + sizeof(struct emac_txd) * priv->txd_count;

	/*
	 * Tx/Rx descriptors(at least, the own bits of the first descriptors)
	 * should be cleared before calling _mac_init, because the DMA starts
	 * descriptor-lookup immediately on enabling DMA even when the auto-
	 * polling is disabled -- possible HW bug?
	 */
	memset(priv->desc_virt, 0, priv->desc_size);

	/*
	 * init driver data
	 */

	if(!is_valid_ether_addr(_addr[_instance]))
	{
		netdev_info(dev, "no valid MAC address -- random-generated\n");
		random_ether_addr(dev->dev_addr);
	}
	else
		memcpy(dev->dev_addr, _addr[_instance], ETH_ALEN);

	/*
	 * init internal data
	 */

	spin_lock_init(&priv->lock);

	priv->txd_head = 0;
	priv->txd_tail = 0;
	priv->txd_used = 0;
	priv->rxd_next = 0;

	if(!(priv->mii_bus = mdiobus_alloc()))
	{
		netdev_err(dev, "failed to mdiobus_alloc\n");
		err = -ENOMEM;
		goto _quit_2;
	}

	priv->mii_bus->priv = dev;
	priv->mii_bus->read = _mii_bus_read;
	priv->mii_bus->write = _mii_bus_write;
	priv->mii_bus->reset = _mii_bus_reset;
	priv->mii_bus->name = "LG115x EMAC-AHB mdc/mdio bus";
	snprintf(priv->mii_bus->id, MII_BUS_ID_SIZE, "%x", priv->id);
	priv->mii_bus->irq = priv->phy_irq;
	
	if((err = mdiobus_register(priv->mii_bus)) < 0)
	{
		netdev_err(dev, "failed to mdiobus_register\n");
		goto _quit_3;
	}

	if((err = _mdio_probe(priv->mii_bus)) < 0)
		goto _quit_4;

	if((err = _mac_init(dev)) < 0)
		goto _quit_5;

	return 0;

_quit_5:
	_mdio_remove(priv->mii_bus);
_quit_4:
	mdiobus_unregister(priv->mii_bus);
_quit_3:
	mdiobus_free(priv->mii_bus);
_quit_2:
	iounmap(priv->desc_virt);
_quit_1:
	iounmap(priv->reg_base);
_quit_0:
	return err;
}

static int _drv_open(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	int err;

	memset(&priv->stats, 0, sizeof(struct net_device_stats));

	if((err = _drv_alloc_tx(dev)) < 0)
		goto _quit_0;

	if((err = _drv_alloc_rx(dev)) < 0)
		goto _quit_1;

	if((err = _mac_start(dev)) < 0)
		goto _quit_2;

	phy_start(priv->phy_dev);

	if((err = request_irq(dev->irq, _drv_isr, 0, "EMAC-AHB", dev)) < 0)
	{
		netdev_err(dev, "failed to request_irq\n");
		goto _quit_3;
	}

	netif_start_queue(dev);

	return 0;

_quit_3:
	_mac_stop(dev);
_quit_2:
	_drv_free_rx(dev);
_quit_1:
	_drv_free_tx(dev);
_quit_0:
	return err;
}

static int _drv_stop(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);

	netif_stop_queue(dev);

	free_irq(dev->irq, dev);

	phy_stop(priv->phy_dev);

	_mac_stop(dev);

	_drv_free_rx(dev);
	_drv_free_tx(dev);

	return 0;
}

static netdev_tx_t _drv_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	dma_addr_t dma;
	unsigned long flags;

	if(priv->txd_used == priv->txd_count)
		return NETDEV_TX_BUSY;

	spin_lock_irqsave(&priv->lock, flags);

	dma = dma_map_single(&dev->dev, skb->data, skb->len, DMA_TO_DEVICE);

	priv->txd[priv->txd_head].first = 1;
	priv->txd[priv->txd_head].last  = 1;
	priv->txd[priv->txd_head].intr  = 1;
	priv->txd[priv->txd_head].size1 = skb->len;
	priv->txd[priv->txd_head].size2 = 0;
	priv->txd[priv->txd_head].addr1 = dma;
	priv->txd[priv->txd_head].addr2 = skb;

	wmb();

	priv->txd[priv->txd_head].own = 1;

	writel_relaxed(0x01, priv->reg_base + DMA_TX_POLL_DEMAND);

	priv->txd_head = (priv->txd_head + 1) % priv->txd_count;
	priv->txd_used++;

	spin_unlock_irqrestore(&priv->lock, flags);

	return NETDEV_TX_OK;
}

static void _drv_set_rx_mode(struct net_device *dev)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	
	if(dev->flags & IFF_PROMISC || netdev_uc_count(dev) > 3)
		_mac_set_rx_promisc(dev);
	else
	{
		_mac_set_rx_uc_list(dev);

		if(dev->flags & IFF_ALLMULTI)
			_mac_set_rx_allmulti(dev);
		else
			_mac_set_rx_mc_list(dev);
	}

	spin_unlock_irqrestore(&priv->lock, flags);
}

static int _drv_set_mac_address(struct net_device *dev, void *addr)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	unsigned long flags;

	if(!is_valid_ether_addr(addr))
		return -EINVAL;

	spin_lock_irqsave(&priv->lock, flags);

	/* update device data */
	memcpy(dev->dev_addr, addr, ETH_ALEN);

	/* update unicast address filter */
	writel_relaxed((unsigned long)((unsigned short *)addr)[0],
	               priv->reg_base + MAC_ADDR1_HI);
	writel_relaxed((unsigned long)((unsigned short *)addr)[1],
	               priv->reg_base + MAC_ADDR1_ME);
	writel_relaxed((unsigned long)((unsigned short *)addr)[2],
	               priv->reg_base + MAC_ADDR1_LO);

	/* enable MAC address #1 */
	writel_relaxed(readl_relaxed(priv->reg_base + MAC_ADDR_CTRL) | 0x01,
	               priv->reg_base + MAC_ADDR_CTRL);

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}

static int _drv_do_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	unsigned long flags;
	int err;

	spin_lock_irqsave(&priv->lock, flags);

	err = phy_mii_ioctl(priv->phy_dev, ifr, cmd);

	spin_unlock_irqrestore(&priv->lock, flags);

	return err;
}

static void _drv_tx_timeout(struct net_device *dev)
{
	/* currently nothing */
}

static struct net_device_stats *_drv_get_stats(struct net_device *dev)
{
	struct emac_priv *priv = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	priv->stats.rx_packets = _mac_get_rx_stats(dev, RX_FRAMES_OK);
	priv->stats.tx_packets = _mac_get_tx_stats(dev, TX_FRAMES_OK);
	priv->stats.rx_bytes   = _mac_get_rx_stats(dev, RX_OCTETS_OK);
	priv->stats.tx_bytes   = _mac_get_tx_stats(dev, TX_OCTETS_OK);
	priv->stats.tx_errors  = _mac_get_tx_stats(dev, TX_FRAMES_ERR);
	priv->stats.rx_errors  = _mac_get_rx_stats(dev, RX_FRAMES_ERR);
	priv->stats.tx_dropped = _mac_get_tx_stats(dev, TX_FRAMES_TOTAL) -
	                         priv->stats.tx_packets - priv->stats.tx_errors;
	priv->stats.rx_dropped = _mac_get_rx_stats(dev, RX_FRAMES_TOTAL) -
	                         priv->stats.rx_packets - priv->stats.rx_errors;

	spin_unlock_irqrestore(&priv->lock, flags);

	return &priv->stats;
}

static struct net_device_ops const _ndo = {
	.ndo_init		= _drv_init,
	.ndo_open		= _drv_open,
	.ndo_stop		= _drv_stop,
	.ndo_start_xmit		= _drv_start_xmit,
	.ndo_set_rx_mode	= _drv_set_rx_mode,
	.ndo_set_mac_address	= _drv_set_mac_address,
	.ndo_do_ioctl		= _drv_do_ioctl,
	.ndo_tx_timeout		= _drv_tx_timeout,
	.ndo_get_stats		= _drv_get_stats,
};

static int _drv_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	return phy_ethtool_gset(priv->phy_dev, cmd);
}

static int _drv_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct emac_priv *priv = (struct emac_priv *)netdev_priv(dev);
	return phy_ethtool_sset(priv->phy_dev, cmd);
}

static void _drv_get_drvinfo(struct net_device *dev,
                             struct ethtool_drvinfo *info)
{
	strcpy(info->driver, "EMAC-AHB");
	strcpy(info->version, "2.0");
	strcpy(info->bus_info, "AMBA");
}

static struct ethtool_ops const _eto = {
	.get_settings	= _drv_get_settings,
	.set_settings	= _drv_set_settings,
	.get_drvinfo	= _drv_get_drvinfo,
};

/*
 * platform driver support
 */

static int __devinit _drv_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct emac_priv *priv;
	struct emac_platform_data *pdata;
	struct resource *reg;
	int irq;
	int i;
	int err;

	if(_instance >= EMAC_INSTANCES)
	{
		dev_err(&pdev->dev, "too many devices\n");
		err = -ENOMEM;
		goto _quit_0;
	}

	if(!(dev = alloc_etherdev(sizeof(struct emac_priv))))
	{
		dev_err(&pdev->dev, "failed to alloc_etherdev\n");
		err = -ENOMEM;
		goto _quit_0;
	}

	SET_NETDEV_DEV(dev, &pdev->dev);
	platform_set_drvdata(pdev, dev);
	priv = (struct emac_priv *)netdev_priv(dev);

	/*
	 * find and reserve all dedicated resources
	 */

	reg = platform_get_resource(pdev, IORESOURCE_MEM, _instance);
	if(!reg)
	{
		dev_err(&pdev->dev, "failed to platform_get_resource\n");
		err = -ENODEV;
		goto _quit_1;
	}

	if(!request_mem_region(reg->start, resource_size(reg), pdev->name))
	{
		dev_err(&pdev->dev, "failed to request_mem_region\n");
		err = -ENXIO;
		goto _quit_1;
	}

	dev->base_addr = reg->start;
	
	if((irq = platform_get_irq(pdev, _instance)) < 0)
	{
		dev_err(&pdev->dev, "failed to platform_get_irq\n");
		err = -ENODEV;
		goto _quit_2;
	}

	dev->irq = irq;

	pdata = (struct emac_platform_data *)pdev->dev.platform_data;
	if(!pdata)
	{
		dev_err(&pdev->dev, "failed to get platform data\n");
		err = -EINVAL;
		goto _quit_2;
	}

	priv->desc_phys = pdata->desc_phys;
	priv->desc_size = sizeof(struct emac_txd) * pdata->txd_count +
	                  sizeof(struct emac_rxd) * pdata->rxd_count;
	priv->txd_count = pdata->txd_count;
	priv->rxd_count = pdata->rxd_count;

	priv->txd_phys = priv->desc_phys;
	priv->rxd_phys = priv->desc_phys + sizeof(struct emac_txd) *
	                 priv->txd_count;

	for(i = 0; i < PHY_MAX_ADDR; ++i)
		priv->phy_irq[i] = PHY_POLL;

	priv->id = _instance;

	/* early device inits */

	dev->netdev_ops = &_ndo;
	dev->ethtool_ops = &_eto;

	if((err = register_netdev(dev)) < 0)
	{
		dev_err(&pdev->dev, "failed to register_netdev\n");
		goto _quit_2;
	}

	++_instance;

	return 0;

_quit_2:
	release_mem_region(dev->base_addr, SZ_1K);
_quit_1:
	free_netdev(dev);
_quit_0:
	return err;
}

static int __devexit _drv_remove(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	struct emac_priv *priv = netdev_priv(dev);

	unregister_netdev(dev);
	_mdio_remove(priv->mii_bus);
	mdiobus_unregister(priv->mii_bus);
	mdiobus_free(priv->mii_bus);
	iounmap(priv->desc_virt);
	iounmap(priv->reg_base);
	release_mem_region(dev->base_addr, SZ_1K);
	free_netdev(dev);

	return 0;
}

static int _drv_suspend(struct platform_device *pdev, pm_message_t state)
{
	/* not implemented yet */

	return 0;
}

static int _drv_resume(struct platform_device *pdev)
{
	/* not implemented yet */

	return 0;
}

static struct platform_device_id const _id_table[] = {
	{ "emac-ahb", 0 },
	{ }
};

static struct platform_driver _driver = {
	.probe		= _drv_probe,
	.remove		= __devexit_p(_drv_remove),
	.suspend	= _drv_suspend,
	.resume		= _drv_resume,
	.driver		= {
		.name	= "LG115x EMAC-AHB",
		.owner	= THIS_MODULE,
	},
	.id_table	= _id_table,
};

/*
 * kernel module support
 */

#ifdef CONFIG_USER_INITCALL_NET
int _mod_init(void)
#else
static int __init _mod_init(void)
#endif
{
	printk("LG115x EMAC-AHB Fast Ethernet MAC driver\n");

	return platform_driver_register(&_driver);
}

static void __exit _mod_exit(void)
{
	platform_driver_unregister(&_driver);
}

#ifdef CONFIG_USER_INITCALL_NET
user_initcall_grp("NETWORK", _mod_init);
#else
module_init(_mod_init);
#endif
module_exit(_mod_exit);

MODULE_AUTHOR("Kim, Jong-Sung <neidhard.kim@lge.com>");
MODULE_DESCRIPTION("LG115x-integrated EMAC-AHB device driver");
MODULE_LICENSE("GPL");

