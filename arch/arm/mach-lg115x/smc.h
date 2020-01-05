#ifndef __ARCH_SMC_H
#define __ARCH_SMC_H

struct smc_param {
	unsigned long param[8];
};

#ifndef CONFIG_TRUSTZONE

static inline void lg115x_smc(struct smc_param const *param)
{
}

#else

extern void lg115x_smc(struct smc_param const *param);

#endif

#endif
