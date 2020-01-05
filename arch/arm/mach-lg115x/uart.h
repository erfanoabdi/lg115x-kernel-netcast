#ifndef __ARCH_UART_H
#define __ARCH_UART_H

#ifndef CONFIG_SERIAL_AMBA_PL011

static inline void lg115x_init_uart(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_init_uart(void);

#endif

#endif

