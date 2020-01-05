#ifndef __ARCH_USB_H
#define __ARCH_USB_H

#ifndef CONFIG_USB

static inline void lg115x_init_usb(void)
{
}

#else

#include <linux/init.h>

extern void __init lg115x_init_usb(void);

#endif

#endif

