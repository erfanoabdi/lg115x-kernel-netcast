#ifndef __ARCH_PMU_H
#define __ARCH_PMU_H

#ifndef CONFIG_CPU_HAS_PMU

static inline void lg115x_init_pmu(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_init_pmu(void);

#endif

#endif

