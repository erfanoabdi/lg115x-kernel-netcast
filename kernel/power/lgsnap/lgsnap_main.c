/*
 * linux/kernel/power/lgsnap_main.c based on kernel/power/suspend.c 
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
#include <linux/mm.h>
#include <linux/suspend.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/cpu.h>
#include <linux/syscalls.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/lgsnap.h>
#include <linux/syscore_ops.h>
#include "../power.h"

unsigned int lgsnap_zero_alloc = 0;
EXPORT_SYMBOL(lgsnap_zero_alloc);
static struct platform_lgsnap_ops *lgsnap_ops;
static int lgsnap_test_level = TEST_NONE;
extern struct lgsnap_info __lgsnap_info;


struct lgsnap_info *lgsnap_get_info(void)
{
    return &__lgsnap_info;
}

void __init _lgsnap_init_value(struct lgsnap_info *info, struct platform_lgsnap_ops *ops)
{
	mutex_lock(&lgsnap_mutex);
	lgsnap_ops = ops;

    info->bl_info->resume_address = virt_to_phys((void *)info->bl_info->resume_address);
    lgsnap_set_page_desc_ops(info->bl_info->adma_enabled);
    lgsnap_set_comp_type(info->bl_info->comp_type);
    lgsnap_set_comp_block_size(info->bl_info->comp_block_size);
    lgsnap_set_swap_state(info->use_swap);
    lgsnap_set_kdl_state(info->use_kdl);

	lgsnap_register_nosave_bl_region();
    mutex_unlock(&lgsnap_mutex);
}

/**
 * lgsnap_valid_only_hib - generic hib-only valid callback
 *
 * lgsnap drivers that implement hibernation only and only need
 * to check for that in their .valid callback can use this instead
 * of rolling their own .valid callback.
 */
int lgsnap_valid_only_hib(lgsnap_state_t state)
{
	return state == LGSNAP_STATE_HIB;
}

bool lgsnap_valid_state(lgsnap_state_t state)
{
	/*
	 * All states need lowlevel support and need to be valid to the lowlevel
	 * implementation, no valid callback implies that none are valid.
	 */
	return lgsnap_ops && lgsnap_ops->valid && lgsnap_ops->valid(state);
}

static int lgsnap_test(int level)
{
	if (lgsnap_test_level == level) {
		printk(KERN_INFO "suspend debug: Waiting for 5 seconds.\n");
		mdelay(5000);
		return 1;
	}

    return 0;
}

/**
 *	lgsnap_prepare - Do prep work before entering hibernation.
 *
 *	This is common code that is called for each state that we're entering.
 *	Run suspend notifiers, allocate a console and stop all processes.
 */
static int lgsnap_prepare(void)
{
	int error;

	if (!lgsnap_ops || !lgsnap_ops->enter)
		return -EPERM;

	pm_prepare_console();

	error = pm_notifier_call_chain(PM_SUSPEND_PREPARE);
	if (error)
		goto Finish;

	error = usermodehelper_disable();
	if (error)
		goto Finish;

	error = suspend_freeze_processes();
	if (!error)
		return 0;

	suspend_thaw_processes();
	usermodehelper_enable();
 Finish:
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
	return error;
}


/**
 *	lgsnap_enter - enter the desired system sleep state.
 *	@state:		state to enter
 *
 *	This function should be called after devices have been suspended.
 */
static int lgsnap_enter(suspend_state_t state)
{
	int error;

	if (lgsnap_ops->prepare) {
		error = lgsnap_ops->prepare();
		if (error)
			return error;
	}

	error = dpm_suspend_end(PMSG_SUSPEND);
	if (error) {
		printk(KERN_ERR "PM: Some devices failed to power down\n");
		goto Platfrom_finish;
	}

	if (lgsnap_ops->prepare_late) {
		error = lgsnap_ops->prepare_late();
		if (error)
			goto Power_up_devices;
	}

	if (lgsnap_test(TEST_PLATFORM))
		goto Platform_wake;

	error = disable_nonboot_cpus();
	if (error || lgsnap_test(TEST_CPUS))
		goto Enable_cpus;

	arch_suspend_disable_irqs();
	BUG_ON(!irqs_disabled());

	syscore_suspend();

	if (!error) {
		if (!lgsnap_test(TEST_CORE))
			error = lgsnap_ops->enter(state);
	}
	lgsnap_zero_alloc = 0;

	syscore_resume();

	arch_suspend_enable_irqs();
	BUG_ON(irqs_disabled());

 Enable_cpus:
	enable_nonboot_cpus();

 Platform_wake:
	if (lgsnap_ops->wake)
		lgsnap_ops->wake();

 Power_up_devices:
	dpm_resume_start(PMSG_RESUME);

 Platfrom_finish:
	if (lgsnap_ops->finish)
		lgsnap_ops->finish();

    return error;
}

extern int _lgsnap_write_snapshot(void *func);
int lgsnap_write_snapshot(void)
{
	if (!lgsnap_ops->write_snapshot)
        return -1;
	return _lgsnap_write_snapshot(lgsnap_ops->write_snapshot);
}

/**
 *	suspend_devices_and_enter - suspend devices and enter the desired system
 *				    sleep state.
 *	@state:		  state to enter
 */
int lgsnap_devices_and_enter(suspend_state_t state)
{
	int error;
	struct lgsnap_info *info;
    unsigned int page_desc_count;
	unsigned int kernel_count;

	if (!lgsnap_ops)
		return -ENOSYS;

	if (lgsnap_ops->begin) {
		error = lgsnap_ops->begin(state);
		if (error)
			goto Close;
	}
	suspend_console();
	lgsnap_test_start();
	error = dpm_suspend_start(PMSG_SUSPEND);
	if (error) {
		printk(KERN_ERR "PM: Some devices failed to suspend\n");
		goto Recover_platform;
	}
	lgsnap_test_finish("suspend devices");
	if (lgsnap_test(TEST_DEVICES))
		goto Recover_platform;

	lgsnap_enter(state);
    
 Resume_devices:
	lgsnap_test_start();
	dpm_resume_end(PMSG_RESUME);
    lgsnap_test_finish("resume devices");
    resume_console();

    if(lgsnap_get_status() == LGSNAP_STATUS_MAKING_IMAGE) {
		info = lgsnap_get_info();
		page_desc_count = lgsnap_get_page_desc_size();
		info->page_desc = kmalloc(sizeof(union lgsnap_page_desc) * page_desc_count, GFP_KERNEL);
		if(info->page_desc == NULL) {
			printk("%s %d kmalloc fail\n", __func__, __LINE__);
			goto  Close;
		}
		
		kernel_count = lgsnap_make_page_desc(info->page_desc, page_desc_count);
		
		lgsnap_make_header(info, kernel_count, page_desc_count);
		
		error = lgsnap_compress_snapshot();
		if(error)
			goto fail_alloc;

		error = lgsnap_write_snapshot();
		
		printk(KERN_INFO "LG Snap : Syncing filesystems ... ");
		sys_sync();
		printk(KERN_INFO "LG Snap : Syncing Done... ");

	fail_alloc:
		kfree(info->page_desc);	
    }

 Close:
	if (lgsnap_ops->end)
		lgsnap_ops->end();

	return error;

 Recover_platform:
	if (lgsnap_ops->recover)
		lgsnap_ops->recover();
	goto Resume_devices;
}

/**
 *	lgsnap_finish - Do final work before exiting suspend sequence.
 *
 *	Call platform code to clean up, restart processes, and free the
 *	console that we've allocated. This is not called for suspend-to-disk.
 */
static void lgsnap_finish(void)
{
	printk("lgsnap_finish \n");
	suspend_thaw_processes();
	usermodehelper_enable();
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
}


/**
 *	lgsnap_main - Do common work of entering lgsnap hibernation.
 *	@state:		pm_state structure for state we're entering.
 *
 *	Make sure we're the only ones trying to enter a sleep state. Fail
 *	if someone has beat us to it, since we don't want anything weird to
 *	happen when we wake up.
 *	Then, do the setup for suspend, enter the state, and cleaup (after
 *	we've woken up).
 */
int lgsnap_main(lgsnap_state_t state)
{
	int error = 0;
	unsigned long reclaim_page_num;
    struct lgsnap_info *info;
    
	if (!lgsnap_valid_state(state))
		return -ENODEV;

	if (!mutex_trylock(&lgsnap_mutex))
		return -EBUSY;

	printk(KERN_INFO "PM: Syncing filesystems ... ");
	sys_sync();
	printk("done.\n");

	lgsnap_dprintk("PM: Preparing system for lgsnap\n");
	error = lgsnap_prepare();
	if (error)
		goto Unlock;
	
	lgsnap_dprintk("PM: Allocate bitmap memory.\n");

	error |= lgsnap_create_basic_memory_bitmaps();
	error |= create_basic_memory_bitmaps();

	if (error)
		goto Unlock;

	reclaim_page_num = totalram_pages - global_page_state(NR_FREE_PAGES);

	shrink_all_memory(reclaim_page_num);

	lgsnap_dprintk("PM : nr_free_pages() :%ld\n", nr_free_pages());

	if (lgsnap_test(TEST_FREEZER))
		goto Free;

	lgsnap_dprintk("PM: Entering lgsnap hibernation\n");
	error = lgsnap_devices_and_enter(state);

	info = lgsnap_get_info();
	lgsnap_free_snap_image_buffer(info->copy_bm);
	lgsnap_free_bl_region();

Free:  
	lgsnap_dprintk("PM: Free bitmap memory.\n");

	lgsnap_free_basic_memory_bitmaps();
	free_basic_memory_bitmaps();

	lgsnap_finish();

		#ifdef LGSNAP_CHECK_MEMORY_FINAL_STATUS
        reclaim_page_num = totalram_pages - global_page_state(NR_FREE_PAGES);
		#endif

Unlock:
	mutex_unlock(&lgsnap_mutex);

	return error;
}
