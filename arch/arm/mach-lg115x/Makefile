#
# Makefile for the linux kernel.
#

asflags-$(CONFIG_TRUSTZONE)	+= -mcpu=cortex-a9

obj-y				+= core.o
obj-y				+= clock.o
obj-$(CONFIG_AMBA_PL08X)	+= dmac.o
obj-$(CONFIG_NET_LG115X_EMAC)	+= emac.o
obj-$(CONFIG_MMC_SDHCI_LG115X)	+= emmc.o
obj-$(CONFIG_GPIO_PL061)	+= gpio.o
obj-$(CONFIG_CACHE_L2X0)	+= l2cc.o
obj-$(CONFIG_CPU_HAS_PMU)	+= pmu.o
obj-$(CONFIG_SPI_PL022)		+= spi.o
obj-y				+= timer.o
obj-$(CONFIG_SERIAL_AMBA_PL011)	+= uart.o
obj-$(CONFIG_USB)		+= usb.o
obj-$(CONFIG_LG_XIP)		+= xip.o
obj-$(CONFIG_HOTPLUG_CPU)	+= hotplug.o
obj-$(CONFIG_LGSNAP)		+= lgsnap_ca9.o
obj-$(CONFIG_LGSNAP)		+= lgsnap.o
obj-$(CONFIG_SMP)		+= headsmp.o
obj-$(CONFIG_SMP)		+= platsmp.o
obj-$(CONFIG_SMP)		+= smp.o
obj-$(CONFIG_TRUSTZONE)		+= headsmc.o
obj-$(CONFIG_TRUSTZONE)		+= smc.o
obj-y				+= ramoops.o
