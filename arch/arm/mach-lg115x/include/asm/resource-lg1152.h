#ifndef __ASM_RESOURCE_LG1152_H
#define __ASM_RESOURCE_LG1152_H

/*
 * physical to virtual address mapping for static mapping table
 */
#ifndef CONFIG_LGSNAP
#define __MMIO_P2V(x)	((((x) & 0x3ff00000) >> 6) | ((x) & 0x00001fff) | \
			0xfe000000)
#else
#define __MMIO_P2V(x)	(x)
#endif

/*
 * Cortex-A9 MPcore devices
 */

#define MPCORE_PERIPH_BASE	0xf0000000
#define MPCORE_SCU_BASE		0xf0000000
#define MPCORE_GIC_CTRL_BASE	0xf0000100
#define MPCORE_GTIMER_BASE	0xf0000200
#define MPCORE_PTIMER_BASE	0xf0000600
#define MPCORE_WDOG_BASE	0xf0000620
#define MPCORE_GIC_DIST_BASE	0xf0001000

#define MPCORE_GTIMER_IRQ	27
#define MPCORE_PTIMER_IRQ	29
#define MPCORE_WDOG_IRQ		30

/*
 * AMBA bus devices
 */

#define L2CC_BASE	0xf1000000
#define EHCI0_BASE	0xfb000000
#define OHCI0_BASE	0xfb004000
#define EHCI1_BASE	0xfc000000
#define OHCI1_BASE	0xfc004000
#define EHCI2_BASE	0xf8000000
#define OHCI2_BASE	0xf8004000
#define EMAC_BASE	0xfa000000
#define TIMER_BASE	0xfd100000
#define WDOG_BASE	0xfd200000
#define GPIO_0_BASE	0xfd400000
#define GPIO_1_BASE	0xfd500000
#define GPIO_2_BASE	0xfd600000
#define GPIO_3_BASE	0xfd700000
#define GPIO_4_BASE	0xfd800000
#define GPIO_5_BASE	0xfd900000
#define GPIO_6_BASE	0xfda00000
#define GPIO_7_BASE	0xfdb00000
#define GPIO_8_BASE	0xfdc00000
#define GPIO_9_BASE	0xfdd00000
#define GPIO10_BASE	0xfde00000
#define GPIO11_BASE	0xfdf00000
#define UART0_BASE	0xfe000000
#define UART1_BASE	0xfe100000
#define UART2_BASE	0xfe200000
#define SPI0_BASE	0xfe800000
#define SPI1_BASE	0xfe900000
#define SDHCI_BASE	0xff000000
#define DMAC_BASE	0xff200000

#define UART0_IRQS	32
#define UART1_IRQS	33
#define UART2_IRQS	34
#define SPI0_IRQS	35
#define SPI1_IRQS	36
#define TIMER_IRQ	38
#define WDOG_IRQS	39
#define GPIO_0_IRQS	30
#define GPIO_1_IRQS	30
#define GPIO_2_IRQS	30
#define GPIO_3_IRQS	31
#define GPIO_4_IRQS	31
#define GPIO_5_IRQS	31
#define GPIO_6_IRQS	32
#define GPIO_7_IRQS	32
#define GPIO_8_IRQS	32
#define GPIO_9_IRQS	33
#define GPIO10_IRQS	33
#define GPIO11_IRQS	33
#define DMAC_IRQS	48
#define SDHCI_IRQS	50
#define OHCI0_IRQ	51
#define EHCI0_IRQ	52
#define OHCI1_IRQ	53
#define EHCI1_IRQ	54
#define OHCI2_IRQ	55
#define EHCI2_IRQ	56
#define EMAC_IRQ	58
#define PMU0_IRQ	118
#define PMU1_IRQ	119

/*
 * something else
 */

#define CPU_CTRL_BASE	0xfd300000
#define SRAM_BASE	0xfff00000

#endif
