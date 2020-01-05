#ifndef __MACH_EMAC_H
#define __MACH_EMAC_H

#include <linux/types.h>

struct emac_platform_data {
	phys_addr_t desc_phys;	/* physical address for Tx/Rx desc. rings */
	size_t txd_count;	/* size of Tx descriptor ring */
	size_t rxd_count;	/* size of Rx descriptor ring */
};

#endif

