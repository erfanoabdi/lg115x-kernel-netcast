#ifndef __ARCH_EMAC_H
#define __ARCH_EMAC_H

#ifndef CONFIG_NET_LG115X_EMAC

static inline void lg115x_prep_emac(void)
{
}

static inline void lg115x_init_emac(void)
{
}

#else

#include <linux/init.h>

#define TX_QSIZE	CONFIG_EMAC_QSIZE_TX
#define RX_QSIZE	CONFIG_EMAC_QSIZE_RX

extern void __init lg115x_prep_emac(void);
extern void __init lg115x_init_emac(void);

#endif

#endif

