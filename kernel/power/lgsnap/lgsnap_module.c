/*
 * linux/kernel/power/lgsnap_module.c based on kernel/power/suspend.c 
 *
 * This file provides system snapshot/restore functionality for lgsnap.
 *
 * Copyright (C) 1998-2005 Pavel Machek <pavel@suse.cz>
 * Copyright (C) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 * Copyright (C) 2011 Sangseok.Lee <sangseok.lee@lge.com>
 *
 * all most of source code is copied from suspend.c 
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
#include <linux/bootmem.h>
#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/lgsnap.h>
#include <linux/memblock.h>
#include <asm/setup.h>
#include <asm/uaccess.h>

#define LGSNAP_ARG_INIT     (0xffffffff)

// lgsnap_ops, lgsnap_main, lgsnap_test_level 
DEFINE_MUTEX(lgsnap_mutex);

struct kobject *lgsnap_kobj;

const char *const lgsnap_states[LGSNAP_STATE_MAX] = {
	[LGSNAP_STATE_ON]	    = "on",
	[LGSNAP_STATE_HIB]	    = "hib",
};

const char *const lgsnap_compressions[LGSNAP_COMP_MAX] = {
	[LGSNAP_COMP_OFF]	    = "off",
	[LGSNAP_COMP_LZO]	    = "lzo",
    [LGSNAP_COMP_LZO_999]   = "lzo_999",
    [LGSNAP_COMP_ZLIB]      = "zlib",
};

const char *const lgsnap_swap_states[LGSNAP_SWAP_MAX] = {
	[LGSNAP_SWAP_OFF]	    = "off",
	[LGSNAP_SWAP_ON]	    = "on",
};

const char *const lgsnap_kdl_states[LGSNAP_KDL_MAX] = {
	[LGSNAP_KDL_OFF]	= "off",
	[LGSNAP_KDL_ON]	    = "on",
};

static lgsnap_comp_t lgsnap_comp_type   = (lgsnap_comp_t)CONFIG_LGSNAP_COMP_TYPE;
static lgsnap_swap_t lgsnap_swap_state  = LGSNAP_SWAP_OFF;
static lgsnap_kdl_t lgsnap_kdl_state    = LGSNAP_KDL_OFF;

static unsigned long lgsnap_bl_addr = LGSNAP_ARG_INIT;
static unsigned long lgsnap_bl_size = LGSNAP_ARG_INIT;
static unsigned long lgsnap_bl_buf_addr = LGSNAP_ARG_INIT;
static unsigned long lgsnap_bl_buf_size = LGSNAP_ARG_INIT;
static unsigned int lgsnap_comp_block_size;

static unsigned int lgsnap_is_enabled = 0;

void lgsnap_reserve_bl_region(void)
{
	struct lgsnap_info *info;

	if(!lgsnap_is_enabled)
		return;

    if(lgsnap_bl_addr == LGSNAP_ARG_INIT || lgsnap_bl_size == LGSNAP_ARG_INIT) {
		info = lgsnap_get_info(); 

		if(info->bl_addr != 0x0 && info->bl_size != 0x0) {
			lgsnap_bl_addr = info->bl_addr;
			lgsnap_bl_size = info->bl_size;

			printk("Use default info->bl_addr : 0x%x, info->bl_size : 0x%x\n", info->bl_addr , info->bl_size);

		} else {
			return;
		}
	}
	
#ifdef CONFIG_HAVE_MEMBLOCK
	memblock_reserve(lgsnap_bl_addr, lgsnap_bl_size);
#else
    reserve_bootmem(lgsnap_bl_addr, lgsnap_bl_size, BOOTMEM_EXCLUSIVE);
#endif
}

void lgsnap_free_bl_region(void)
{
    if(lgsnap_bl_addr != LGSNAP_ARG_INIT && lgsnap_bl_size != LGSNAP_ARG_INIT) {
#ifdef CONFIG_HAVE_MEMBLOCK
		memblock_free(lgsnap_bl_addr, lgsnap_bl_size);
#else
		#error "bootmem feature is deprecated. It may occur panic"
		/*
         * free_bootmem_late(lgsnap_bl_addr, lgsnap_bl_size);
         */
#endif
	}
}

void __init lgsnap_register_nosave_bl_region(void)
{
    unsigned long start_pfn, end_pfn;

    if(lgsnap_bl_addr == LGSNAP_ARG_INIT || lgsnap_bl_size == LGSNAP_ARG_INIT)
        return;

    start_pfn = PFN_DOWN(lgsnap_bl_addr);
    end_pfn = PFN_UP(lgsnap_bl_addr + lgsnap_bl_size);
    register_nosave_region_late(start_pfn, end_pfn);	
}


unsigned int lgsnap_get_bl_addr(void)
{
    return lgsnap_bl_addr;
}

unsigned int lgsnap_get_bl_size(void)
{
    return lgsnap_bl_size;
}

void lgsnap_set_bl_addr(unsigned int addr)
{
    lgsnap_bl_addr = addr;
}

void lgsnap_set_bl_size(unsigned int size)
{
    lgsnap_bl_size = size;
}

static int __init lgsnap_bl_addr_setup(char *p)
{
    unsigned long start, size;
	char *endp;

    start = memparse(p, &endp);

    if(*endp == ',') {
        size = memparse(endp + 1, NULL);

        lgsnap_bl_addr = start;
        lgsnap_bl_size = size;
    }

	printk("Use bootparam bl_addr : 0x%lx, bl_size : 0x%lx\n", lgsnap_bl_addr , lgsnap_bl_size);
	
	return 0;
}
early_param("bl_addr", lgsnap_bl_addr_setup);

unsigned int lgsnap_get_bl_buf_addr(void)
{
    return lgsnap_bl_buf_addr;
}

void lgsnap_set_bl_buf_addr(unsigned int addr)
{
    lgsnap_bl_buf_addr = addr;
}

unsigned int lgsnap_get_bl_buf_size(void)
{
    return lgsnap_bl_buf_size;
}

void lgsnap_set_bl_buf_size(unsigned int size)
{
    lgsnap_bl_buf_size = size;
}

static int __init lgsnap_bl_buf_addr_setup(char *p)
{
    unsigned long start, size;
	char *endp;

    start = memparse(p, &endp);
    if(*endp == ',') {
        size = memparse(endp + 1, NULL);

        lgsnap_bl_buf_addr = start;
        lgsnap_bl_buf_size = size;
    }

    printk("bl_buf_address : 0x%lx\n", lgsnap_bl_buf_addr);
    printk("bl_buf_size : 0x%lx\n", lgsnap_bl_buf_size);   

	return 0;
}
__setup("bl_buf_addr=", lgsnap_bl_buf_addr_setup);

static int __init lgsnap_enable_setup(char *p)
{
	lgsnap_zero_alloc = 1;
	lgsnap_is_enabled = 1;

	return 0;
}
early_param("lgsnap", lgsnap_enable_setup);

lgsnap_comp_t lgsnap_get_comp_type(void)
{
    return lgsnap_comp_type;
}

void lgsnap_set_comp_type(lgsnap_comp_t type)
{
    lgsnap_comp_type = type;
}

lgsnap_swap_t lgsnap_get_swap_state(void)
{
    return lgsnap_swap_state;
}

void lgsnap_set_swap_state(lgsnap_swap_t state)
{
    lgsnap_swap_state = state;
}

lgsnap_kdl_t lgsnap_get_kdl_state(void)
{
    return lgsnap_kdl_state;
}

void lgsnap_set_kdl_state(lgsnap_kdl_t state)
{
    lgsnap_kdl_state = state;
}

unsigned int lgsnap_get_comp_block_size(void)
{
    return lgsnap_comp_block_size;
}

void lgsnap_set_comp_block_size(unsigned int size)
{
    lgsnap_comp_block_size = size;
}

static ssize_t lgsnap_state_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	char *s = buf;
	int i;
    
	for (i = 0; i < LGSNAP_STATE_MAX; i++) {
        s += sprintf(s,"%s ", lgsnap_states[i]);
	}
    
	if (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';

	return (s - buf);
}

static ssize_t lgsnap_state_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
{
	suspend_state_t state = PM_SUSPEND_STANDBY;
	const char * const *s;

	char *p;
	int len;
	int error = -EINVAL;

	if(!lgsnap_is_enabled)
		return error;
	else 
		lgsnap_is_enabled = 0;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

	for (s = &lgsnap_states[state]; state < LGSNAP_STATE_MAX; s++, state++) {
            if (*s && len == strlen(*s) && !strncmp(buf, *s, len))
                break;
    }

    if (state < LGSNAP_STATE_MAX && *s)
        error = lgsnap_main(state);

	return error ? error : n;
}

lgsnap_attr(state);

const char * const lgsnap_get_comp_string(lgsnap_comp_t type)
{
    return lgsnap_compressions[type];
}

#ifdef CONFIG_LGSNAP_COMPRESS
static ssize_t lgsnap_comp_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	char *s = buf;
	int i;
    
	for (i = 0; i < LGSNAP_COMP_MAX; i++) {
            
        if (lgsnap_comp_type == i)
        	s += sprintf(s,"[%s] ", lgsnap_compressions[i]);
        else
        	s += sprintf(s,"%s ", lgsnap_compressions[i]);
	}

	if (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';

	return (s - buf);
}

lgsnap_attr_ro(comp);

static ssize_t lgsnap_comp_block_size_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	return sprintf(buf, "%u\n", lgsnap_comp_block_size);
}

static ssize_t lgsnap_comp_block_size_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
{
	unsigned long comp_block_size;
	int err;

	err = strict_strtoul(buf, 10, &comp_block_size);
	if (err || comp_block_size > UINT_MAX)
		return -EINVAL;

	lgsnap_comp_block_size = comp_block_size;

	return n;
}

lgsnap_attr(comp_block_size);
#endif


#ifdef CONFIG_LGSNAP_SWAP
static ssize_t lgsnap_swap_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	char *s = buf;
	int i;
    
	for (i = 0; i < LGSNAP_SWAP_MAX; i++) {
            
        if (lgsnap_swap_state == i)
        	s += sprintf(s,"[%s] ", lgsnap_swap_states[i]);
        else
        	s += sprintf(s,"%s ", lgsnap_swap_states[i]);
	}

	if (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';

	return (s - buf);
}

static ssize_t lgsnap_swap_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
{
    lgsnap_swap_t state = LGSNAP_SWAP_OFF;
    const char * const *s;

    char *p;
    int len;
    int error = -EINVAL;

    p = memchr(buf, '\n', n);
    len = p ? p - buf : n;

    for (s = &lgsnap_swap_states[state]; state < LGSNAP_SWAP_MAX; s++, state++) {
            if (*s && len == strlen(*s) && !strncmp(buf, *s, len)) {
                error = 0;
                break;
            }
    }

    if (state < LGSNAP_SWAP_MAX && *s)
        lgsnap_swap_state = state;
    
    return error ? error : n;
}

lgsnap_attr(swap);
#endif


#ifdef CONFIG_LGSNAP_KERNEL_DEMAND_LOADING
static ssize_t lgsnap_kdl_show(struct kobject *kobj, struct kobj_attribute *attr,
			  char *buf)
{
	char *s = buf;
	int i, len;

	for (i = 0; i < LGSNAP_KDL_MAX; i++) {
        if (lgsnap_kdl_state == i)
        	s += sprintf(s,"[%s] ", lgsnap_kdl_states[i]);
        else
        	s += sprintf(s,"%s ", lgsnap_kdl_states[i]);
	}

	if (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';

	return (s - buf);
}

static ssize_t lgsnap_kdl_store(struct kobject *kobj, struct kobj_attribute *attr,
			   const char *buf, size_t n)
{
    lgsnap_swap_t state = LGSNAP_SWAP_OFF;
    const char * const *s;

    char *p;
    int len;
    int error = -EINVAL;

    p = memchr(buf, '\n', n);
    len = p ? p - buf : n;

    for (s = &lgsnap_kdl_states[state]; state < LGSNAP_KDL_MAX; s++, state++) {
            if (*s && len == strlen(*s) && !strncmp(buf, *s, len)) {
                error = 0;
                break;
            }
    }

    if (state < LGSNAP_KDL_MAX && *s)
        lgsnap_kdl_state = state;
    
    return error ? error : n;
}

lgsnap_attr(kdl);
#endif

#ifdef CONFIG_LGSNAP_TEST
int lgsnap_test_level = LGSNAP_TEST_NONE;

static const char * const lgsnap_tests[__LGSNAP_TEST_AFTER_LAST] = {
	[LGSNAP_TEST_NONE] = "none",
	[LGSNAP_TEST_CORE] = "core",
	[LGSNAP_TEST_CPUS] = "processors",
	[LGSNAP_TEST_PLATFORM] = "platform",
	[LGSNAP_TEST_DEVICES] = "devices",
	[LGSNAP_TEST_FREEZER] = "freezer",
};

static ssize_t lgsnap_test_show(struct kobject *kobj, struct kobj_attribute *attr,
				char *buf)
{
	char *s = buf;
	int level;

	for (level = LGSNAP_TEST_FIRST; level <= LGSNAP_TEST_MAX; level++)
		if (lgsnap_tests[level]) {
			if (level == lgsnap_test_level)
				s += sprintf(s, "[%s] ", lgsnap_tests[level]);
			else
				s += sprintf(s, "%s ", lgsnap_tests[level]);
		}

	if (s != buf)
		/* convert the last space to a newline */
		*(s-1) = '\n';

	return (s - buf);
}

static ssize_t lgsnap_test_store(struct kobject *kobj, struct kobj_attribute *attr,
				const char *buf, size_t n)
{
	const char * const *s;
	int level;
	char *p;
	int len;
	int error = -EINVAL;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

	mutex_lock(&lgsnap_mutex);

	level = LGSNAP_TEST_FIRST;
	for (s = &lgsnap_tests[level]; level <= LGSNAP_TEST_MAX; s++, level++)
		if (*s && len == strlen(*s) && !strncmp(buf, *s, len)) {
			lgsnap_test_level = level;
			error = 0;
			break;
		}

	mutex_unlock(&lgsnap_mutex);

	return error ? error : n;
}

lgsnap_attr(test);

#endif /* CONFIG_PM_DEBUG */

static struct attribute * g[] = {
	&lgsnap_state_attr.attr,

#ifdef CONFIG_LGSNAP_COMPRESS
    &lgsnap_comp_ro_attr.attr,
    &lgsnap_comp_block_size_attr.attr,
#endif

#ifdef CONFIG_LGSNAP_SWAP
    &lgsnap_swap_attr.attr,
#endif

#ifdef CONFIG_LGSNAP_KERNEL_DEMAND_LOADING
    &lgsnap_kdl_attr.attr,
#endif

#ifdef CONFIG_LGSNAP_TEST
    &lgsnap_test_attr.attr,
#endif

	NULL,
};

static struct attribute_group attr_group = {
	.attrs = g,
};

static int lgsnap_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int lgsnap_release(struct inode *inode, struct file *filp)
{
	return 0;
}

#define LGSNAP_HEADER_SIZE(info) ALIGN((ALIGN(sizeof(struct lgsnap_info_bl), 4) + ALIGN(sizeof(struct lgsnap_save_list) * info->bl_info->save_list_count, 4) \
									+ ALIGN(sizeof(union lgsnap_page_desc) * info->bl_info->page_desc_count, 4)), PAGE_SIZE)
	
static long
lgsnap_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret = -1;
	int err = 0;
	unsigned int header_size;
	struct lgsnap_info *info;
	struct lgsnap_ioctl_arg from;
	struct lgsnap_ioctl_arg *to;

	if(!lgsnap_is_enabled)
		return ret;

	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != LGSNAP_IOC_MAGIC) 
		return -ENOTTY;

	if (_IOC_NR(cmd) > LGSNAP_IOC_MAXNR) 
		return -ENOTTY;

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	
	if (err) 
		return -EFAULT;
	
	switch(cmd) {
		case LGSNAP_IOC_MAKE_SNAPSHOT:
			info = lgsnap_get_info(); 
			ret = lgsnap_main(LGSNAP_STATE_HIB);
			header_size = LGSNAP_HEADER_SIZE(info);
			from.lgsnap_image_size = info->bl_info->image_size + header_size;
			from.lgsnap_mode = lgsnap_get_status();
			
			//printk("lgsnap lgsnap_image_size : %d\n", from.lgsnap_image_size);
			//printk("lgsnap mode : %d\n", from.lgsnap_mode);
			
			to = (struct lgsnap_ioctl_arg *)arg;
			if (copy_to_user(to, &from, sizeof(struct lgsnap_ioctl_arg)))
				ret = -EFAULT;
			else
				ret = 0;
			break;

		default:
			break; 
	}

	return ret;
}

static const struct file_operations lgsnap_fops = {
	.open		= lgsnap_open,
	.release	= lgsnap_release,
	.unlocked_ioctl = lgsnap_ioctl,
	.owner		= THIS_MODULE,
};

static struct cdev lgsnap_cdev;

#define LGSNAP_MAJOR	181
#define MAX_LGSNAP_MINORS 1
static int __init lgsnap_init(void)
{
	dev_t dev;
	int ret;

	lgsnap_kobj = kobject_create_and_add("lgsnap", power_kobj);
	if (!lgsnap_kobj)
		return -ENOMEM;
    
    ret = sysfs_create_group(lgsnap_kobj, &attr_group);
	if (ret) {
		printk(KERN_ERR
		       "Unable to create lgsnap attributes\n");
		kobject_put(lgsnap_kobj);
		goto error;
}

	dev = MKDEV(LGSNAP_MAJOR, 0);

	ret = register_chrdev_region(dev, MAX_LGSNAP_MINORS, "lgsnap");
	if (ret)
		goto error;

	cdev_init(&lgsnap_cdev, &lgsnap_fops);
	ret = cdev_add(&lgsnap_cdev, dev, MAX_LGSNAP_MINORS);
	if (ret) {
		kobject_put(&lgsnap_cdev.kobj);
		goto error_region;
	}

	return 0;

error_region:
	unregister_chrdev_region(dev, MAX_LGSNAP_MINORS);
error:
	sysfs_remove_group(lgsnap_kobj, &attr_group);
	kobject_put(lgsnap_kobj);
	
	return ret;
}

static void __exit lgsnap_exit(void)
{
	cdev_del(&lgsnap_cdev);
	unregister_chrdev_region(MKDEV(LGSNAP_MAJOR, 0), MAX_LGSNAP_MINORS);
}

module_init(lgsnap_init);
module_exit(lgsnap_exit);
MODULE_LICENSE("GPL");
