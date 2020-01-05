#ifndef __ARCH_SPI_H
#define __ARCH_SPI_H

#ifndef CONFIG_SPI_PL022

static inline void lg115x_init_spi(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_init_spi(void);

#endif

#endif

