#ifndef __ARCH_SMP_H
#define __ARCH_SMP_H

#include <linux/init.h>

extern void __init lg115x_flags_set(unsigned long data);
extern void __init lg115x_secondary_startup(void);

#endif

