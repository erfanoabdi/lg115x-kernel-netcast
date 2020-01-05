#ifndef __ARCH_TIMER_H
#define __ARCH_TIMER_H

#include <linux/init.h>

#include <asm/mach/time.h>

extern struct sys_timer lg115x_timer;

extern void __init lg115x_init_timer(void);

#endif

