/*
 * linux/kernel/power/lgsnap_core.c based on kernel/power/suspend.c 
 *
 * This file provides system snapshot/restore functionality for lgsnap.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 * Copyright (c) 2009 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 * Copyright (C) 2011 Sangseok.Lee <sangseok.lee@lge.com>
 *
 * This file is released under the GPLv2.
 *
 */
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kernel.h>

#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/swap.h>
#include <linux/delay.h>

#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/lgsnap.h>

extern int sysctl_overcommit_memory;
extern int sysctl_overcommit_ratio;
extern struct percpu_counter vm_committed_as;


struct vmalloc_info {
	unsigned long	used;
	unsigned long	largest_chunk;
};

#define VMALLOC_TOTAL (VMALLOC_END - VMALLOC_START)
extern void get_vmalloc_info(struct vmalloc_info *vmi);
#ifdef CONFIG_HUGETLB_PAGE
    unsigned long hugetlb_total_pages(void);
#else /* !CONFIG_HUGETLB_PAGE */
    static inline unsigned long hugetlb_total_pages(void)
    {
    	return 0;
    }
#endif


#ifdef LGSNAP_DEBUG_TIME
/*
 * We test the system suspend code by setting an RTC wakealarm a short
 * time in the future, then suspending.  Suspending the devices won't
 * normally take long ... some systems only need a few milliseconds.
 *
 * The time it takes is system-specific though, so when we test this
 * during system bootup we allow a LOT of time.
 */
unsigned long lgsnap_test_start_time;

void lgsnap_test_start(void)
{
    extern unsigned long lgsnap_test_start_time;
	/* FIXME Use better timebase than "jiffies", ideally a clocksource.
	 * What we want is a hardware counter that will work correctly even
	 * during the irqs-are-off stages of the suspend/resume cycle...
	 */
	lgsnap_test_start_time = jiffies;
}

void lgsnap_test_finish(const char *label)
{
    extern unsigned long lgsnap_test_start_time;

	long nj = jiffies - lgsnap_test_start_time;
	unsigned msec;

	msec = jiffies_to_msecs(abs(nj));
	pr_info("PM: %s took %d.%03d seconds\n", label,
			msec / 1000, msec % 1000);

	/* Warning on suspend means the RTC alarm period needs to be
	 * larger -- the system was sooo slooowwww to suspend that the
	 * alarm (should have) fired before the system went to sleep!
	 *
	 * Warning on either suspend or resume also means the system
	 * has some performance issues.  The stack dump of a WARN_ON
	 * is more likely to get the right attention than a printk...
	 */
	//WARN(msec > (LGSNAP_SUSPEND_MAX_SECONDS * 1000),
	//     "Component: %s, time: %u\n", label, msec);
}
#endif

#ifdef LGSNAP_DEBUG_DUMP_HEADER
void lgsnap_dump_header(struct lgsnap_info * info)
{
	unsigned int i;
    unsigned int sum_length = 0, total_length;
    union lgsnap_page_desc *page_desc = info->page_desc;
    struct lgsnap_info_bl * info_bl = info->bl_info;
    struct lgsnap_page_desc_ops *ops = lgsnap_get_page_desc_ops();
    
    
	printk("\n\n\n=============================================================================================\n");
	printk("=============================================================================================\n");
    printk("lgsnap_dump_header\n");

    total_length = lgsnap_total_length(page_desc, info_bl->page_desc_count);

	for(i=0; i < info->bl_info->page_desc_count;i++) {
		printk("count_desc[%3u] => address : 0x%4x, length : %10u(%10u/%10u) %7lu pages\n", 
            i, ops->get_address(&page_desc[i]), ops->get_length(&page_desc[i]), 
            sum_length,total_length, PAGES(ops->get_length(&page_desc[i])));

        sum_length += ops->get_length(&page_desc[i]);
	}

	printk("info->kernel_count: %x\n", info->kernel_count);

	printk("info_bl->resume_address: %x\n", info_bl->resume_address);

	printk("info_bl->page_desc_count: %d(0x%x)\n", info_bl->page_desc_count, info_bl->page_desc_count);

    printk("total length : %dMbytes(%d)\n", total_length/(1024*1024), total_length);
    
	printk("=============================================================================================\n");
    printk("=============================================================================================\n");
}

void lgsnap_dump_pfn_list(struct memory_bitmap *bm) __unused;
void lgsnap_dump_pfn_list(struct memory_bitmap *bm)
{
    unsigned long pfn;
    unsigned int i;
    
    memory_bm_position_reset(bm);
    for(i = 0;;i++) {
        pfn = memory_bm_next_pfn(bm);
        if (unlikely(pfn == BM_END_OF_MAP))
            break;
        printk("%s %d : [%d] pfn : 0x%x\n", __func__, __LINE__, i, pfn);
    }
}
#endif

#ifdef LGSNAP_DEBUG_MEMINFO
void lgsnap_meminfo_show(void)
{
	struct sysinfo i;
	unsigned long committed;
	unsigned long allowed;
	struct vmalloc_info vmi;
	long cached;
	unsigned long pages[NR_LRU_LISTS];
	int lru;

/*
 * display in kilobytes.
 */
#define K(x) ((x) << (PAGE_SHIFT - 10))
	si_meminfo(&i);
	si_swapinfo(&i);
	committed = percpu_counter_read_positive(&vm_committed_as);
	allowed = ((totalram_pages - hugetlb_total_pages())
		* sysctl_overcommit_ratio / 100) + total_swap_pages;

	cached = global_page_state(NR_FILE_PAGES) -
			total_swapcache_pages - i.bufferram;
	if (cached < 0)
		cached = 0;

	get_vmalloc_info(&vmi);

	for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
		pages[lru] = global_page_state(NR_LRU_BASE + lru);

	/*
	 * Tagged format, for easy grepping and expansion.
	 */
	printk(
	    "===================================\n"
		"MemTotal:	 %8lu kB\n"
		"MemFree:	 %8lu kB\n"
		"Buffers:	 %8lu kB\n"
		"Cached:	 %8lu kB\n"
		"SwapCached:	 %8lu kB\n"
		"Active:	 %8lu kB\n"
		"Inactive:	 %8lu kB\n"
		"Active(anon):	 %8lu kB\n"
		"Inactive(anon): %8lu kB\n"
		"Active(file):	 %8lu kB\n"
		"Inactive(file): %8lu kB\n"
		"Unevictable:	 %8lu kB\n"
		"Mlocked:	 %8lu kB\n"
#ifdef CONFIG_HIGHMEM
		"HighTotal:	 %8lu kB\n"
		"HighFree:	 %8lu kB\n"
		"LowTotal:	 %8lu kB\n"
		"LowFree:	 %8lu kB\n"
#endif
#ifndef CONFIG_MMU
		"MmapCopy:	 %8lu kB\n"
#endif
		"SwapTotal:	 %8lu kB\n"
		"SwapFree:	 %8lu kB\n"
		"Dirty: 	 %8lu kB\n"
		"Writeback:	 %8lu kB\n"
		"AnonPages:	 %8lu kB\n"
		"Mapped:	 %8lu kB\n"
		"Shmem: 	 %8lu kB\n"
		"Slab:		 %8lu kB\n"
		"SReclaimable:	 %8lu kB\n"
		"SUnreclaim:	 %8lu kB\n"
		"KernelStack:	 %8lu kB\n"
		"PageTables:	 %8lu kB\n"
#ifdef CONFIG_QUICKLIST
		"Quicklists:	 %8lu kB\n"
#endif
		"NFS_Unstable:	 %8lu kB\n"
		"Bounce:	 %8lu kB\n"
		"WritebackTmp:	 %8lu kB\n"
		"CommitLimit:	 %8lu kB\n"
		"Committed_AS:	 %8lu kB\n"
		"VmallocTotal:	 %8lu kB\n"
		"VmallocUsed:	 %8lu kB\n"
		"VmallocChunk:	 %8lu kB\n"
#ifdef CONFIG_MEMORY_FAILURE
		"HardwareCorrupted: %5lu kB\n"
#endif
        "===================================\n\n\n"
		,
		K(i.totalram),
		K(i.freeram),
		K(i.bufferram),
		K(cached),
		K(total_swapcache_pages),
		K(pages[LRU_ACTIVE_ANON]   + pages[LRU_ACTIVE_FILE]),
		K(pages[LRU_INACTIVE_ANON] + pages[LRU_INACTIVE_FILE]),
		K(pages[LRU_ACTIVE_ANON]),
		K(pages[LRU_INACTIVE_ANON]),
		K(pages[LRU_ACTIVE_FILE]),
		K(pages[LRU_INACTIVE_FILE]),
		K(pages[LRU_UNEVICTABLE]),
		K(global_page_state(NR_MLOCK)),
#ifdef CONFIG_HIGHMEM
		K(i.totalhigh),
		K(i.freehigh),
		K(i.totalram-i.totalhigh),
		K(i.freeram-i.freehigh),
#endif
#ifndef CONFIG_MMU
		K((unsigned long) atomic_long_read(&mmap_pages_allocated)),
#endif
		K(i.totalswap),
		K(i.freeswap),
		K(global_page_state(NR_FILE_DIRTY)),
		K(global_page_state(NR_WRITEBACK)),
		K(global_page_state(NR_ANON_PAGES)),
		K(global_page_state(NR_FILE_MAPPED)),
		K(global_page_state(NR_SHMEM)),
		K(global_page_state(NR_SLAB_RECLAIMABLE) +
				global_page_state(NR_SLAB_UNRECLAIMABLE)),
		K(global_page_state(NR_SLAB_RECLAIMABLE)),
		K(global_page_state(NR_SLAB_UNRECLAIMABLE)),
		global_page_state(NR_KERNEL_STACK) * THREAD_SIZE / 1024,
		K(global_page_state(NR_PAGETABLE)),
#ifdef CONFIG_QUICKLIST
		K(quicklist_total_size()),
#endif
		K(global_page_state(NR_UNSTABLE_NFS)),
		K(global_page_state(NR_BOUNCE)),
		K(global_page_state(NR_WRITEBACK_TEMP)),
		K(allowed),
		K(committed),
		(unsigned long)VMALLOC_TOTAL >> 10,
		vmi.used >> 10,
		vmi.largest_chunk >> 10
#ifdef CONFIG_MEMORY_FAILURE
		,atomic_long_read(&mce_bad_pages) << (PAGE_SHIFT - 10)
#endif
		);
#undef K
}
#endif


#ifdef LGSNAP_DEBUG_HEXDUMP
void lgsnap_hexdump(char *note, unsigned char *buf, unsigned int len)
{
	printk(KERN_CRIT "%s", note);
	print_hex_dump(KERN_CONT, "", DUMP_PREFIX_OFFSET,
			16, 1,
			buf, len, false);

}
#endif

