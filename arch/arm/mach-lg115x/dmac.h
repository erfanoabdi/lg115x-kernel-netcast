#ifndef __ARCH_DMAC_H
#define __ARCH_DMAC_H

#ifndef CONFIG_AMBA_PL08X

static inline void lg115x_init_dmac(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_init_dmac(void);

#endif

#endif

