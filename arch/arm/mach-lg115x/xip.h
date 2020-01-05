#ifndef __ARCH_XIP_H
#define __ARCH_XIP_H

#ifndef CONFIG_LG_XIP

static inline void lg115x_prep_xip(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_prep_xip(void);

#endif

#endif

