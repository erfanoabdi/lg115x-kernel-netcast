#ifndef __ARCH_EMMC_H
#define __ARCH_EMMC_H

#ifndef CONFIG_MMC_SDHCI_LG115X

static inline void lg115x_init_emmc(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_init_emmc(void);

#endif

#endif

