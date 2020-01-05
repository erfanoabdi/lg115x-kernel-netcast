#ifndef __ARCH_GPIO_H
#define __ARCH_GPIO_H

#ifndef CONFIG_GPIO_PL061

static inline void lg115x_init_gpio(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_init_gpio(void);

#endif

#endif

