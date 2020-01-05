/*
 * linux/kernel/power/lgsnap.h based on kernel/power/lgsnap.h 
 *
 * This file provides system snapshot/restore functionality for lgsnap.
 *
 * Copyright (C) 2011 Sangseok.Lee <sangseok.lee@lge.com>
 *
 * This file is released under the GPLv2.
 *
 */
#ifndef _LINUX_LGSNAP_IF_H
#define _LINUX_LGSNAP_IF_H

#ifdef CONFIG_LGSNAP

#define pfn_to_virt(pfn)	    __va((pfn) << PAGE_SHIFT)
#define lgsnap_init_value(x)   _lgsnap_init_value(&__lgsnap_info, x)

#define LGSNAP_MAGIC_LENGTH	20
#define LGSNAP_MAGIC_INIT		"lgsnap_making_image"
#define LGSNAP_MAGIC            "lgsnap_hibernation"

// Additional save list and nosave list attributes
#define LGSNAP_SAVE_END_SHIFT      (0)
#define LGSNAP_SAVE_DMABLE_SHIFT        (1)
#define LGSNAP_SAVE_NON_DMABLE_SHIFT    (2)
#define LGSNAP_SAVE_VIRTUAL_SHIFT       (3)
#define LGSNAP_SAVE_PHYSICAL_SHIFT      (4)

#define LGSNAP_SAVE_END         (1 << (LGSNAP_SAVE_END_SHIFT))
#define LGSNAP_SAVE_DMABLE      (1 << (LGSNAP_SAVE_DMABLE_SHIFT))
#define LGSNAP_SAVE_NON_DMABLE  (1 << (LGSNAP_SAVE_NON_DMABLE_SHIFT))
#define LGSNAP_SAVE_VIRTUAL     (1 << (LGSNAP_SAVE_VIRTUAL_SHIFT))
#define LGSNAP_SAVE_PHYSICAL    (1 << (LGSNAP_SAVE_PHYSICAL_SHIFT))

// ADMA Descriptor Table Attributes
#define LGSNAP_ADMA_ATTR_VALID_SHIFT    (0)
#define LGSNAP_ADMA_ATTR_VALID          (1 << LGSNAP_ADMA_ATTR_INT_SHIFT)

#define LGSNAP_ADMA_ATTR_END_SHIFT      (1)
#define LGSNAP_ADMA_ATTR_END            (1 << LGSNAP_ADMA_ATTR_INT_SHIFT)

#define LGSNAP_ADMA_ATTR_INT_SHIFT      (2)
#define LGSNAP_ADMA_ATTR_INT            (1 << LGSNAP_ADMA_ATTR_INT_SHIFT)

#define LGSNAP_ADMA_ATTR_ACT_SHIFT      (4)
#define LGSNAP_ADMA_ATTR_NOP            (00 << (LGSNAP_ADMA_ATTR_ACT_SHIFT))
#define LGSNAP_ADMA_ATTR_RSV            (01 << (LGSNAP_ADMA_ATTR_ACT_SHIFT))
#define LGSNAP_ADMA_ATTR_TRAN           (10 << (LGSNAP_ADMA_ATTR_ACT_SHIFT))
#define LGSNAP_ADMA_ATTR_LINK_MAKS      (11 << (LGSNAP_ADMA_ATTR_ACT_SHIFT))

#define LGSNAP_PFN_LIST_END	    (0xffffffff)

typedef enum {
    LGSNAP_STATE_ON,
    LGSNAP_STATE_HIB,
    LGSNAP_STATE_MAX
} lgsnap_state_t;

typedef enum {
	LGSNAP_STATUS_NONE,
	LGSNAP_STATUS_MAKING_IMAGE,
	LGSNAP_STATUS_RESUMING,
	LGSNAP_STATUS_MAX,
} lgsnap_status_t;

typedef enum {
    LGSNAP_COMP_OFF,
    LGSNAP_COMP_LZO,
    LGSNAP_COMP_LZO_999,
    LGSNAP_COMP_ZLIB,
    LGSNAP_COMP_MAX
} lgsnap_comp_t;

typedef enum {
    LGSNAP_SWAP_OFF,
    LGSNAP_SWAP_ON,
    LGSNAP_SWAP_MAX
} lgsnap_swap_t;

typedef enum {
    LGSNAP_KDL_OFF,
    LGSNAP_KDL_ON,
    LGSNAP_KDL_MAX
} lgsnap_kdl_t;

union lgsnap_page_desc {
    struct adma_desc {
		// The SDHCI specification states that ADMA addresses must be 32-bit aligned. 
        // drivers/mmc/host/sdhci.c -> sdhci_adma_table_pre function
        // 63 ~ 32 : 32bit address, 31 ~ 16 : 16bit Length, 15 ~ 06 : Reserved, 05 ~ 00 : Attributes
        // Attributes -> 05 ~ 04  : Act, 03 : Reseved, 02 : Int, 01 : End, 00 : Valid
        // Act -> 00 : nop, 01 : Rsv, 10 : Tran, 11 : Link
        u8 desc[8];        
    } adma_desc;

    struct generic_desc {
        unsigned int address;   // physical address. at least 4bytes aligned
                                // if address is odd, compression not used.
        unsigned int length;    // length in bytes
    } generic_desc;
};

struct lgsnap_page_desc_ops {
    int (*get)(union lgsnap_page_desc *page_desc, unsigned int *address, unsigned int *length, unsigned int *attr);
    int (*set)(union lgsnap_page_desc *page_desc, unsigned int address, unsigned int length, unsigned int attr);
    unsigned int (*get_address)(union lgsnap_page_desc *page_desc);
    int (*set_address)(union lgsnap_page_desc *page_desc, unsigned int address);
    unsigned int (*get_length)(union lgsnap_page_desc *page_desc);
    int (*set_length)(union lgsnap_page_desc *page_desc, unsigned int length);
    unsigned int (*get_attr)(union lgsnap_page_desc *page_desc);
    int (*set_attr)(union lgsnap_page_desc *page_desc, unsigned int attr);
};

struct lgsnap_image_page {
	unsigned int pfn;
} ;

//additional save list like as video memory which doesn't managed by kernel
struct lgsnap_save_list {
	unsigned int address;
	unsigned int size;
    
    //LGSNAP_SAVE_DMABLE or LGSNAP_SAVE_NON_DMABLE && LGSNAP_SAVE_VIRTUAL or LGSNAP_SAVE_PHYSICAL
	unsigned int type;  
};

struct lgsnap_nosave_list {
	unsigned int address;
	int size;
    
    //LGSNAP_SAVE_VIRTUAL or LGSNAP_SAVE_PHYSICAL
	unsigned int type;  
};

struct lgsnap_info_bl {
    unsigned char magic[LGSNAP_MAGIC_LENGTH];
    unsigned int adma_enabled;
    lgsnap_comp_t comp_type;
    unsigned int comp_block_size;
    
    unsigned int save_list_count;
    unsigned int page_desc_count;
    unsigned int image_size;

    unsigned int resume_address;

    // if lgsnap_info's bl_buf_addr and boot param's  bl_buf_addr does not define, kernel malloc for boot loader compress buffer.
    unsigned int comp_buf_addr;
    unsigned int comp_buf_size;

    unsigned int offset_save_list;
    unsigned int offset_lgsnap_page_desc;
};

struct  lgsnap_info {
    struct lgsnap_info_bl *bl_info; // this info is for bootloader
    union lgsnap_page_desc *page_desc;
    struct memory_bitmap *copy_bm;
    struct memory_bitmap *orig_bm;

    char *name;
    struct lgsnap_save_list *save;
    struct lgsnap_nosave_list *nosave;

    unsigned int kernel_count;
    
    int use_swap;
    int use_kdl;
    unsigned int bl_addr;
    unsigned int bl_size;
    unsigned int bl_buf_addr;
    unsigned int bl_buf_size;
};

/**
 * struct platform_lgsnap_ops - Callbacks for managing platform dependent
 *	system sleep states.
 *
 * @valid: Callback to determine if given system sleep state is supported by
 *	the platform.
 *	Valid (ie. supported) states are advertised in /sys/power/state.  Note
 *	that it still may be impossible to enter given system sleep state if the
 *	conditions aren't right.
 *	There is the %suspend_valid_only_mem function available that can be
 *	assigned to this if the platform only supports mem sleep.
 *
 * @begin: Initialise a transition to given system sleep state.
 *	@begin() is executed right prior to suspending devices.  The information
 *	conveyed to the platform code by @begin() should be disregarded by it as
 *	soon as @end() is executed.  If @begin() fails (ie. returns nonzero),
 *	@prepare(), @enter() and @finish() will not be called by the PM core.
 *	This callback is optional.  However, if it is implemented, the argument
 *	passed to @enter() is redundant and should be ignored.
 *
 * @prepare: Prepare the platform for entering the system sleep state indicated
 *	by @begin().
 *	@prepare() is called right after devices have been suspended (ie. the
 *	appropriate .suspend() method has been executed for each device) and
 *	before device drivers' late suspend callbacks are executed.  It returns
 *	0 on success or a negative error code otherwise, in which case the
 *	system cannot enter the desired sleep state (@prepare_late(), @enter(),
 *	@wake(), and @finish() will not be called in that case).
 *
 * @prepare_late: Finish preparing the platform for entering the system sleep
 *	state indicated by @begin().
 *	@prepare_late is called before disabling nonboot CPUs and after
 *	device drivers' late suspend callbacks have been executed.  It returns
 *	0 on success or a negative error code otherwise, in which case the
 *	system cannot enter the desired sleep state (@enter() and @wake()).
 *
 * @enter: Enter the system sleep state indicated by @begin() or represented by
 *	the argument if @begin() is not implemented.
 *	This callback is mandatory.  It returns 0 on success or a negative
 *	error code otherwise, in which case the system cannot enter the desired
 *	sleep state.
 *
 * @wake: Called when the system has just left a sleep state, right after
 *	the nonboot CPUs have been enabled and before device drivers' early
 *	resume callbacks are executed.
 *	This callback is optional, but should be implemented by the platforms
 *	that implement @prepare_late().  If implemented, it is always called
 *	after @enter(), even if @enter() fails.
 *
 * @finish: Finish wake-up of the platform.
 *	@finish is called right prior to calling device drivers' regular suspend
 *	callbacks.
 *	This callback is optional, but should be implemented by the platforms
 *	that implement @prepare().  If implemented, it is always called after
 *	@enter() and @wake(), if implemented, even if any of them fails.
 *
 * @end: Called by the PM core right after resuming devices, to indicate to
 *	the platform that the system has returned to the working state or
 *	the transition to the sleep state has been aborted.
 *	This callback is optional, but should be implemented by the platforms
 *	that implement @begin().  Accordingly, platforms implementing @begin()
 *	should also provide a @end() which cleans up transitions aborted before
 *	@enter().
 *
 * @recover: Recover the platform from a suspend failure.
 *	Called by the PM core if the suspending of devices fails.
 *	This callback is optional and should only be implemented by platforms
 *	which require special recovery actions in that situation.
 * @write_snapshot: write hibernation image to hibernation partition.
 *	write buf to hibernation partition.
 */
struct platform_lgsnap_ops {
	int (*valid)(lgsnap_state_t state);
	int (*begin)(lgsnap_state_t state);
	int (*prepare)(void);
	int (*prepare_late)(void);
	int (*enter)(lgsnap_state_t state);
	void (*wake)(void);
	void (*finish)(void);
	void (*end)(void);
	void (*recover)(void);
	int (*write_snapshot)(const char *buf, size_t count);
	int (*get_snap_part_size)(void);
};

struct lgsnap_ioctl_arg {
	lgsnap_status_t lgsnap_mode;
	unsigned int lgsnap_image_size;
};

#define LGSNAP_IOC_MAGIC            'l'
#define LGSNAP_IOC_MAKE_SNAPSHOT    _IOW(LGSNAP_IOC_MAGIC, 0, struct lgsnap_ioctl_arg)
#define LGSNAP_IOC_MAXNR            0
#define LGSNAP_PARTITION_NAME       "hib"

#define LGSNAP_INFO_START(_name, _resume_address, _adma_enabled, _comp_type, _comp_block_size)	\
static struct lgsnap_info_bl __lgsnap_info_bl = {                   \
    .magic = LGSNAP_MAGIC_INIT,                                     \
    .resume_address = (unsigned int)_resume_address,                              \
    .adma_enabled = _adma_enabled,                                  \
    .comp_type = _comp_type,                                  \
    .comp_block_size = _comp_block_size,                                  \
};                                                                  \
struct lgsnap_info __lgsnap_info	= {                         \
	.name		= _name,                                            \
	.bl_info    = &__lgsnap_info_bl,
	
#define LGSNAP_INFO_END				                                \
};

#define __unused __attribute__ ((unused))
#define BM_END_OF_MAP	(~0UL)

#define lgsnap_attr(_name) \
static struct kobj_attribute lgsnap_##_name##_attr = {	\
	.attr	= {				\
		.name = __stringify(_name),	\
		.mode = 0644,			\
	},					\
	.show	= lgsnap_##_name##_show,			\
	.store	= lgsnap_##_name##_store,		\
}

#define lgsnap_attr_ro(_name) \
static struct kobj_attribute lgsnap_##_name##_ro_attr = {	\
	.attr	= {				\
		.name = __stringify(_name),	\
		.mode = 0644,			\
	},					\
	.show	= lgsnap_##_name##_show,			\
}

extern struct mutex lgsnap_mutex;
extern unsigned int lgsnap_zero_alloc;

extern lgsnap_comp_t lgsnap_get_comp_type(void);
extern void lgsnap_set_comp_type(lgsnap_comp_t type);
extern void lgsnap_set_swap_state(lgsnap_swap_t state);
extern void lgsnap_set_kdl_state(lgsnap_kdl_t state);
extern unsigned int lgsnap_get_comp_block_size(void);
extern void lgsnap_set_comp_block_size(unsigned int size);
extern const char * const lgsnap_get_comp_string(lgsnap_comp_t type);
extern int lgsnap_create_basic_memory_bitmaps(void);
extern void lgsnap_free_basic_memory_bitmaps(void);
extern void lgsnap_free_snap_image_buffer(struct memory_bitmap *bm);
extern void lgsnap_set_page_desc_ops(unsigned int adma_enabled);
extern struct lgsnap_page_desc_ops *lgsnap_get_page_desc_ops(void);
extern int lgsnap_compress_snapshot(void);
extern lgsnap_comp_t lgsnap_get_comp_type(void);
extern unsigned int lgsnap_total_length(union lgsnap_page_desc *page_desc, unsigned int count);
extern int  lgsnap_make_page_desc(union lgsnap_page_desc *page_desc, unsigned int estimate_count);
extern unsigned int lgsnap_get_page_desc_size(void);
extern int  lgsnap_make_header(struct lgsnap_info *info, unsigned int kernel_count, unsigned int page_desc_count);
extern void lgsnap_register_nosave_bl_region(void);
extern void lgsnap_free_bl_region(void);
extern int lgsnap_valid_only_hib(lgsnap_state_t state);
extern void _lgsnap_init_value(struct lgsnap_info *info, struct platform_lgsnap_ops *ops);
extern struct lgsnap_info *lgsnap_get_info(void);
extern int lgsnap_main(lgsnap_state_t state);
extern lgsnap_status_t lgsnap_get_status(void);
extern void lgsnap_reserve_bl_region(void);

extern unsigned long memory_bm_next_pfn(struct memory_bitmap *bm);
extern void memory_bm_position_reset(struct memory_bitmap *bm);
extern unsigned long memory_bm_current_pfn(struct memory_bitmap *bm);
extern struct memory_bitmap *memory_bm_copy(struct memory_bitmap *bm);

/*
 * LGSNAP debug features.
 */

#define LGSNAP_DEBUG_TIME
//#define LGSNAP_DEBUG_DUMP_HEADER
#define LGSNAP_DEBUG_MEMINFO
//#define LGSNAP_DEBUG_HEXDUMP
//#define LGSNAP_DEBUG_PRINTK

#define LGSNAP_SUSPEND_MAX_SECONDS	10

#if defined (CONFIG_LGSNAP_DEBUG) && defined (LGSNAP_DEBUG_TIME)
extern void lgsnap_test_start(void);
extern void lgsnap_test_finish(const char *label);
#else
static inline void lgsnap_test_start(void) {}
static inline void lgsnap_test_finish(const char *label) {}
#endif

#if defined (CONFIG_LGSNAP_DEBUG) && defined (LGSNAP_DEBUG_DUMP_HEADER)
extern void lgsnap_dump_header(struct lgsnap_info * info);
#else
#define lgsnap_dump_header(x)
#endif

#if defined (CONFIG_LGSNAP_DEBUG) && defined (LGSNAP_DEBUG_MEMINFO)
extern void lgsnap_meminfo_show(void);
#else
#define lgsnap_meminfo_show(x)
#endif

#if defined (CONFIG_LGSNAP_DEBUG) && defined (LGSNAP_DEBUG_HEXDUMP)
extern void lgsnap_hexdump(char *note, unsigned char *buf, unsigned int len);
#else
#define lgsnap_hexdump(x,y,z)
#endif

#if defined (CONFIG_LGSNAP_DEBUG) && defined (LGSNAP_DEBUG_PRINTK)
#define lgsnap_dprintk(fmt, args...) printk(KERN_ERR "%s: " fmt, __func__, ##args)
#else
#define lgsnap_dprintk(fmt, args...)
#endif

#endif /* CONFIG_LGSNAP */

#endif /* _LINUX_LGSNAP_IF_H */
