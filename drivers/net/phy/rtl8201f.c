#include <linux/phy.h>
#include <linux/module.h>

/* page 0 register 30 - interrupt indicators and SNR display register */
#define RTL8201F_ISR	0x1e
/* page 0 register 31 - page select register */
#define RTL8201F_PSR	0x1f
/* page 7 register 19 - interrupt, WOL enable, and LEDs function register */
#define RTL8201F_IER	0x13

static int rtl8201f_ack_interrupt(struct phy_device *phydev)
{
	/*
	 * once the status registers have been read by the MAC
	 * through the MDC/MDIO, the interrupt is de-asserted.
	 */
	phy_read(phydev, RTL8201F_ISR);

	return 0;
}

static int rtl8201f_config_intr(struct phy_device *phydev)
{
	phy_write(phydev, RTL8201F_PSR, 0x0007);	/* select page 7 */

	if(phydev->interrupts == PHY_INTERRUPT_ENABLED)
	{
		/* enable all interrupts */
		phy_write(phydev, RTL8201F_IER, 0x3800 |
		          phy_read(phydev, RTL8201F_IER));
	}
	else
	{
		/* disable all interrupts */
		phy_write(phydev, RTL8201F_IER, ~0x3800 &
		          phy_read(phydev, RTL8201F_IER));
	}

	phy_write(phydev, RTL8201F_PSR, 0x0000);	/* back to page 0 */

	return 0;
}

static struct phy_driver rtl8201f_driver = {
	.phy_id		= 0x001cc816,
	.name		= "RTL8201F Fast Ethernet",
	.phy_id_mask	= 0x001fffff,
	.features	= PHY_BASIC_FEATURES,
	.flags		= PHY_HAS_INTERRUPT,
	.config_aneg	= &genphy_config_aneg,
	.read_status	= &genphy_read_status,
	.ack_interrupt	= &rtl8201f_ack_interrupt,
	.config_intr	= &rtl8201f_config_intr,
	.driver		= {
		.owner	= THIS_MODULE,
	},
};

static int __init rtl8201f_init(void)
{
	printk("Realtek RTL8201F Fast Ethernet PHY driver\n");

	return phy_driver_register(&rtl8201f_driver);
}

static void __exit rtl8201f_exit(void)
{
	phy_driver_unregister(&rtl8201f_driver);
}

module_init(rtl8201f_init);
module_exit(rtl8201f_exit);

static struct mdio_device_id __maybe_unused rtl8201f_tbl[] = {
	{ 0x001cc816, 0x001fffff },
	{ }
};

MODULE_DEVICE_TABLE(mdio, rtl8201f_tbl);

MODULE_DESCRIPTION("Realtek RTL8201F PHY driver");
MODULE_AUTHOR("Kim, Jong-Sung <neidhard.kim@lge.com>");
MODULE_LICENSE("GPL");

