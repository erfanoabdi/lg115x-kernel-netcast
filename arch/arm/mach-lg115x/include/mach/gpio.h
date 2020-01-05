#ifndef MACH_GPIO_H
#define MACH_GPIO_H

#define ARCH_NR_GPIOS	144

#include <asm-generic/gpio.h>

#define __ARM_GPIOLIB_COMPLEX

static inline int gpio_trans(unsigned gpio)
{
	return (gpio & ~0x07) | ~(gpio & 0x07);
}

static inline int gpio_get_value(unsigned gpio)
{
	if(gpio < ARCH_NR_GPIOS)
		return __gpio_get_value(gpio_trans(gpio));
	else
		return __gpio_get_value(gpio);
}

static inline void gpio_set_value(unsigned gpio, int value)
{
	if(gpio < ARCH_NR_GPIOS)
		__gpio_set_value(gpio_trans(gpio), value);
	else
		__gpio_set_value(gpio, value);
}

static inline int gpio_cansleep(unsigned gpio)
{
	if(gpio < ARCH_NR_GPIOS)
		return __gpio_cansleep(gpio_trans(gpio));
	else
		return __gpio_cansleep(gpio);
}

#endif

