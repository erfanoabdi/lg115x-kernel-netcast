#ifndef __ARCH_CORE_H
#define __ARCH_CORE_H

#include <linux/amba/bus.h>

#define AMBA_DEVICE(name, busid, prefix, data)	\
	AMBA_AHB_DEVICE(name, busid, 0, prefix##_BASE, {prefix##_IRQS}, data)

#endif

