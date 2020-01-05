#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/smp.h>
#include <linux/io.h>
#include <asm/cacheflush.h>
#include <asm/smp_plat.h>
#include <asm/cp15.h>
#include <mach/resource.h>


static DECLARE_COMPLETION(cpu_killed);

extern volatile int pen_release;

static inline void cpu_enter_lowpower(void)
{
	unsigned int v;

	flush_cache_all();
	asm volatile(
	"	mcr	p15, 0, %1, c7, c5, 0\n"
	"	mcr	p15, 0, %1, c7, c10, 4\n"
	/*
	 * Turn off coherency
	 */
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, %3\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	  : "=&r" (v)
	  : "r" (0), "Ir" (CR_C), "Ir" (0x40)
	  : "cc");
}

static inline void cpu_leave_lowpower(void)
{
	unsigned int v;

	asm volatile(
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	orr	%0, %0, %1\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	orr	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	  : "=&r" (v)
	  : "Ir" (CR_C), "Ir" (0x40)
	  : "cc");
}

static inline void platform_do_lowpower(unsigned int cpu, int *spurious)
{
#ifdef CONFIG_LGSNAP
	extern	void save_context_secondary(void);
	save_context_secondary();
#endif
	/*
	 * there is no power-control hardware on this platform, so all
	 * can do is put the core into WFI; this is safe as the calling
	 * code will have already disabled interrupts
	 */
	for (;;) {
		wfi();

		if (pen_release == cpu_logical_map(cpu)) {
			/*
		 	* OK, proper wakeup, we're done
		 	*/
			break;
		}
			
		/*
		 * Getting here, means that we have come out of WFI
		 * without having been woken up - this shouldn't happen
		 *
		 * Just note it happening - when we're woken, we can
		 * report its occurrence.
		 */
		(*spurious)++;
	}
}

int platform_cpu_kill(unsigned int cpu)
{
	return 1;
}

/*
 * platform-specific code to shutdown a CPU
 *
 * Called with IRQs disabled
 */
#define hard_smp_processor_id()			\
	({						\
		unsigned int cpunum;			\
		__asm__("mrc p15, 0, %0, c0, c0, 5"	\
			: "=r" (cpunum));		\
		cpunum &= 0x0F;				\
	})

void platform_cpu_die(unsigned int cpu)
{
	int spurious = 0;

	unsigned int this_cpu = hard_smp_processor_id();

	if (cpu != this_cpu) {
		printk(KERN_CRIT "Eek! platform_cpu_die running on %u, should be %u\n",
			   this_cpu, cpu);
		BUG();
	}

	printk(KERN_NOTICE "CPU%u: shutdown\n", cpu);
	//complete(&cpu_killed);
	flush_cache_all();
	wmb();

	/*
	 * we're ready for shutdown now, so do it
	 */
    platform_do_lowpower(cpu, &spurious);

	if (spurious)
		pr_warn("CPU%u: %u spurious wakeup calls\n", cpu, spurious);
}


int platform_cpu_disable(unsigned int cpu)
{
	/*
	 * we don't allow CPU 0 to be shutdown (it is still too special
	 * e.g. clock tick interrupts)
	 */
	return cpu == 0 ? -EPERM : 0;
}

