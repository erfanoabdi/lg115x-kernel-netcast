/*
 * linux/arch/arm/mach-lg115x/lgsnap.c
 *
 * This file provides system snapshot/restore functionality for lgsnap.
 *
 * Copyright (C) 2011 Sangseok.Lee <sinchul.jung@lge.com> 
 * Copyright (C) 2011 Sangseok.Lee <sangseok.lee@lge.com>
 *
 * This file is released under the GPLv2.
 *
 */
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/suspend.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/mtd/partitions.h>
#include <linux/lgsnap.h>

#include <mtd/mtd-abi.h>
#include <asm/memory.h>
#include <asm/system.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/cacheflush.h>
#include <asm/hardware/gic.h>
#include <asm/mach/time.h>

#include <mach/resource.h>


#define HIB_PART_NAME            "hib"
#define LGSNAP_PART_MAX_NAE_LEN	(30)

extern struct mtd_partition lg_flash_parts[];

struct lgsnap_save_list L9_save_list[] = {
        { 0, 0, LGSNAP_SAVE_END_SHIFT }
};

struct lgsnap_nosave_list *L9_nosave_list;

extern void init_l2cc_pre(void);

// low level hibernation enter function
extern void dsm_entry(void);
// system resume function called from mmu disabled status.
extern void dsm_exit(void);
// secondary cpu resume function is called from mmu disabled status.
extern void secondary_cpu(void);

// appxip_start ~ appxip_start + appxip_size  : we can skip this region from hiberrnation image.
extern unsigned long appxip_start;
extern unsigned long appxip_size;

static int snapshot_fd;


extern char *lgemmc_get_partition(const char *part_name);
extern u32 lgemmc_get_partition_size(const char *part_name);

static int dtvsoc_lgsnap_begin(lgsnap_state_t state)
{
    mm_segment_t snapshot_old_fs;
	char *lgsnap_part_name;
    
	lgsnap_dprintk(">>>>>>>> go into pm c\n");

    lgsnap_part_name = lgemmc_get_partition(HIB_PART_NAME);

	snapshot_old_fs = get_fs();
	set_fs(KERNEL_DS);

	snapshot_fd = sys_open(lgsnap_part_name, O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);

	if(snapshot_fd < 0) {
		printk("fail to open %s\n", lgsnap_part_name);
		goto open_fail;
	}
    kfree(lgsnap_part_name);
    set_fs(snapshot_old_fs);
	lgsnap_dprintk(">>>>>>>> exit from pm begin\n");

	return 0;
    
open_fail:  
    kfree(lgsnap_part_name);
    set_fs(snapshot_old_fs);
    return -1;    
}

static int dtvsoc_lgsnap_prepare(void)
{
  	lgsnap_dprintk(">>>>>>>> go into pm prepare\n");

	return 0;
}

#define SYS_FLAGSSET (MMIO_P2V(CPU_CTRL_BASE) + 0x02dc)

static int dtvsoc_lgsnap_enter(lgsnap_state_t state)
{
    unsigned long secondary_cpu_resume_address;
    
	lgsnap_dprintk(">>>>>>>> go into pm enter\n");
    
    secondary_cpu_resume_address = virt_to_phys(&secondary_cpu);
    
	switch (state)
	{
		case LGSNAP_STATE_HIB:
            // real hibernation
            dsm_entry();

            // after resume we will start from here in C language level.
            __raw_writel(secondary_cpu_resume_address,(SYS_FLAGSSET));
            smp_mb();
            gic_raise_softirq(cpumask_of(1), 1);

            if(lgsnap_get_status() == LGSNAP_STATUS_RESUMING)
                init_l2cc_pre();

			break;

		case LGSNAP_STATE_ON:
            /* Fall through */
		default:
			return -EINVAL;
	}

	return 0;
}

static void dtvsoc_lgsnap_finish(void)
{
	lgsnap_dprintk(">>>>>>>> go into pm finish\n");
}

static void dtvsoc_lgsnap_end(void)
{
    mm_segment_t snapshot_old_fs;
    
	lgsnap_dprintk(">>>>>>>> go into pm end\n");

	snapshot_old_fs = get_fs();
	set_fs(KERNEL_DS);
	sys_close(snapshot_fd);
    set_fs(snapshot_old_fs);

	kfree(L9_nosave_list);
	lgsnap_dprintk(">>>>>>>> exit from pm end\n");
}

int dtvsoc_write_snapshot(const char *buf, size_t count)
{
    int ret;
    mm_segment_t snapshot_old_fs;

	snapshot_old_fs = get_fs();
	set_fs(KERNEL_DS);
	ret = sys_write(snapshot_fd, buf, count);
    set_fs(snapshot_old_fs);

    return ret;
}

int dtvsoc_get_snap_part_size(void)
{
    return lgemmc_get_partition_size(HIB_PART_NAME);
}


static struct platform_lgsnap_ops dtvsoc_lgsnap_ops = {
	.valid		    = lgsnap_valid_only_hib,
    .begin          = dtvsoc_lgsnap_begin,
	.prepare	    = dtvsoc_lgsnap_prepare,
	.enter		    = dtvsoc_lgsnap_enter,
	.finish		    = dtvsoc_lgsnap_finish,
	.end            = dtvsoc_lgsnap_end,
	.write_snapshot = dtvsoc_write_snapshot,
 	.get_snap_part_size = dtvsoc_get_snap_part_size,
};

// name, resume address, adma_enabled
// if bootloader argument is passed, then default value is ignored.
LGSNAP_INFO_START("L9", &dsm_exit, 0, LGSNAP_COMP_LZO, PAGE_SIZE * 32)
    .save = L9_save_list,
    .use_swap = 0,
    .bl_addr = 0x01800000,   
    .bl_size = 0x1000000,   
LGSNAP_INFO_END

static int __init dtvsoc_lgsnap_init(void)
{
	//free at dtvsoc_lgsnap_end
    L9_nosave_list = kmalloc(sizeof(struct lgsnap_nosave_list) * 2, GFP_KERNEL);
    L9_nosave_list[0].address = appxip_start;
    L9_nosave_list[0].size = appxip_size;
    L9_nosave_list[0].type = LGSNAP_SAVE_PHYSICAL;
    L9_nosave_list[1].address = 0;
    L9_nosave_list[1].size = 0;
    L9_nosave_list[1].type = LGSNAP_SAVE_END_SHIFT;

	register_nosave_region_late(PFN_DOWN(L9_nosave_list[0].address), 
			PFN_UP(L9_nosave_list[0].address + L9_nosave_list[0].size ));
	
    __lgsnap_info.nosave = L9_nosave_list;
    
    lgsnap_init_value(&dtvsoc_lgsnap_ops);
  
	return 0;
}
late_initcall(dtvsoc_lgsnap_init);

#ifdef CONFIG_HIBERNATION
void save_processor_state(void)
{
}

void restore_processor_state(void)
{
}

int pfn_is_nosave(unsigned long pfn)
{
	return 0;
}

int swsusp_arch_suspend(void)
{
	return 0;
}

int swsusp_arch_resume(void)
{
	return 0;
}
#endif
