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
#include <linux/vmalloc.h>
#include <linux/highmem.h>
#include <linux/crypto.h>
#include <linux/lzo.h>
#include <linux/lgsnap.h>
#include <asm/page.h>
#include "../power.h"

extern struct memory_bitmap *kernel_pages_map;

#define LGSNAP_GFP_FLAG  (GFP_NOWAIT | __GFP_DMA)
#define ABS(X) ((X) < 0 ? (-1 * (X)) : (X))

static lgsnap_status_t lgsnap_status = LGSNAP_STATUS_NONE;

static struct lgsnap_page_desc_ops *page_desc_ops = NULL;

static unsigned int get_address(union lgsnap_page_desc *page_desc)
{
    if(page_desc_ops)
        return page_desc_ops->get_address(page_desc); 
    
    return -1;
}

static unsigned int get_length(union lgsnap_page_desc *page_desc)
{
    if(page_desc_ops)
        return page_desc_ops->get_length(page_desc); 
    
    return -1;
}

static unsigned int get_attr(union lgsnap_page_desc *page_desc) __unused;
static unsigned int get_attr(union lgsnap_page_desc *page_desc)
{
    if(page_desc_ops && page_desc_ops->get_attr)
        return page_desc_ops->get_attr(page_desc); 
    
    return -1;
}

static int set_address(union lgsnap_page_desc *page_desc, unsigned int address)
{
    if(page_desc_ops)
        return page_desc_ops->set_address(page_desc, address); 
    
    return -1;
}

static int set_length(union lgsnap_page_desc *page_desc, unsigned int length)
{
    if(page_desc_ops)
        return page_desc_ops->set_length(page_desc, length); 
    
    return -1;
}

static int set_attr(union lgsnap_page_desc *page_desc, unsigned int attr)
{
    if(page_desc_ops && page_desc_ops->set_attr)
        return page_desc_ops->set_attr(page_desc, attr); 
    
    return -1;
}

static int lgsnap_generic_page_desc_get(union lgsnap_page_desc *page_desc, unsigned int *address, unsigned int *length, unsigned int *attr __unused)
{
    *address = page_desc->generic_desc.address;
    *length = page_desc->generic_desc.length;

    return 0;
}

static int lgsnap_generic_page_desc_set(union lgsnap_page_desc *page_desc, unsigned int address, unsigned int length, unsigned int attr __unused)
{
    page_desc->generic_desc.address = address;
    page_desc->generic_desc.length = length;

    return 0;
}

static unsigned int lgsnap_generic_page_desc_get_address(union lgsnap_page_desc *page_desc)
{
    return page_desc->generic_desc.address;
}

static int lgsnap_generic_page_desc_set_address(union lgsnap_page_desc *page_desc, unsigned int address)
{
    page_desc->generic_desc.address = address;

    return 0;
}

static unsigned int lgsnap_generic_page_desc_get_length(union lgsnap_page_desc *page_desc)
{
    return page_desc->generic_desc.length;
}

static int lgsnap_generic_page_desc_set_length(union lgsnap_page_desc *page_desc, unsigned int length)
{
    page_desc->generic_desc.length = length;

    return 0;
}

static struct lgsnap_page_desc_ops generic_ops = {
    .get = lgsnap_generic_page_desc_get,
    .set = lgsnap_generic_page_desc_set,
    .get_address = lgsnap_generic_page_desc_get_address,
    .set_address = lgsnap_generic_page_desc_set_address,
    .get_length = lgsnap_generic_page_desc_get_length,
    .set_length = lgsnap_generic_page_desc_set_length,
    .get_attr = NULL,
    .set_attr = NULL,
};

static int lgsnap_adma_page_desc_get(union lgsnap_page_desc *page_desc, unsigned int *address, unsigned int *length, unsigned int *attr)
{
    *address = page_desc->adma_desc.desc[7]  << 24;
    *address |= page_desc->adma_desc.desc[6] << 16;
    *address |= page_desc->adma_desc.desc[5] << 8;
    *address |= page_desc->adma_desc.desc[4] << 0;

    *length = page_desc->adma_desc.desc[3] << 8;
    *length |= page_desc->adma_desc.desc[2] << 0;

    *attr = page_desc->adma_desc.desc[1] << 8;
    *attr |= page_desc->adma_desc.desc[0] << 0;

    return 0;
}

static int lgsnap_adma_page_desc_set(union lgsnap_page_desc *page_desc, unsigned int address, unsigned int length, unsigned int attr)
{
	BUG_ON(address & 0x3);

    page_desc->adma_desc.desc[7] = (address >> 24) & 0xff;
    page_desc->adma_desc.desc[6] = (address  >> 16) & 0xff;
    page_desc->adma_desc.desc[5] = (address  >> 8) & 0xff;
    page_desc->adma_desc.desc[4] = (address  >> 0) & 0xff;
    
    BUG_ON(length > 65536);
    
    page_desc->adma_desc.desc[3] = (length >> 8) & 0xff;
    page_desc->adma_desc.desc[2] = (length >> 0) & 0xff;
    
    page_desc->adma_desc.desc[1] = 0x00;
    page_desc->adma_desc.desc[0] = attr; 

    return 0;
}

static unsigned int lgsnap_adma_page_desc_get_address(union lgsnap_page_desc *page_desc)
{
    unsigned int address;

    address = page_desc->adma_desc.desc[7]  << 24;
    address |= page_desc->adma_desc.desc[6] << 16;
    address |= page_desc->adma_desc.desc[5] << 8;
    address |= page_desc->adma_desc.desc[4] << 0;

    return address;
}

static int lgsnap_adma_page_desc_set_address(union lgsnap_page_desc *page_desc, unsigned int address)
{
	BUG_ON(address & 0x3);

    page_desc->adma_desc.desc[7] = (address >> 24) & 0xff;
    page_desc->adma_desc.desc[6] = (address  >> 16) & 0xff;
    page_desc->adma_desc.desc[5] = (address  >> 8) & 0xff;
    page_desc->adma_desc.desc[4] = (address  >> 0) & 0xff;

    return 0;
}

static unsigned int lgsnap_adma_page_desc_get_length(union lgsnap_page_desc *page_desc)
{
    unsigned int length;
    
    length = page_desc->adma_desc.desc[3] << 8;
    length |= page_desc->adma_desc.desc[2] << 0;

    return length;
}

static int lgsnap_adma_page_desc_set_length(union lgsnap_page_desc *page_desc, unsigned int length)
{
    BUG_ON(length > 65536);
    
    page_desc->adma_desc.desc[3] = (length >> 8) & 0xff;
    page_desc->adma_desc.desc[2] = (length >> 0) & 0xff;

    return 0;
}

static unsigned int lgsnap_adma_page_desc_get_attr(union lgsnap_page_desc *page_desc)
{
    unsigned int attr;
    
    attr = page_desc->adma_desc.desc[1] << 8;
    attr |= page_desc->adma_desc.desc[0] << 0;

    return attr;
}

static int lgsnap_adma_page_desc_set_attr(union lgsnap_page_desc *page_desc, unsigned int attr)
{
    page_desc->adma_desc.desc[1] = 0x00;
    page_desc->adma_desc.desc[0] = attr; 

    return 0;
}

static struct lgsnap_page_desc_ops adma_ops = {
    .get = lgsnap_adma_page_desc_get,
    .set = lgsnap_adma_page_desc_set,
    .get_address = lgsnap_adma_page_desc_get_address,
    .set_address = lgsnap_adma_page_desc_set_address,
    .get_length = lgsnap_adma_page_desc_get_length,
    .set_length = lgsnap_adma_page_desc_set_length,
    .get_attr = lgsnap_adma_page_desc_get_attr,
    .set_attr = lgsnap_adma_page_desc_set_attr,
};

void lgsnap_set_page_desc_ops(unsigned int adma_enabled)
{
    if(adma_enabled)
        page_desc_ops = &adma_ops;
    else
        page_desc_ops = &generic_ops;
}

struct lgsnap_page_desc_ops *lgsnap_get_page_desc_ops(void)
{
    return page_desc_ops;
}

int _lgsnap_write_snapshot(void *write_func)
{
	int ret;
    int pfn;
	unsigned int image_size = 0;
	unsigned int comp_image_size;
    const char *buffer;
	struct page *s_page;
	void *src;
    size_t block_align_size;
    int (*write_snapshot)(const char *buf, size_t count);
	
    struct memory_bitmap *bm;
    struct lgsnap_info *info = lgsnap_get_info();
	comp_image_size = info->bl_info->image_size;

    bm = info->copy_bm;

    write_snapshot = write_func;
    
	ret = write_snapshot((const char *)info->bl_info, ALIGN(sizeof(struct lgsnap_info_bl), 4));
    if(ret <= 0)
		return ret;
    
    if(info->save && info->bl_info->save_list_count != 0) {
		ret = write_snapshot((const char *)info->save, ALIGN(sizeof(struct lgsnap_save_list) * info->bl_info->save_list_count, 4));
		if(ret <= 0)
			return ret;
	}
    
    ret = write_snapshot((const char *)info->page_desc, ALIGN(sizeof(union lgsnap_page_desc) * info->bl_info->page_desc_count, 4));
    if(ret <= 0)
		return ret;

    block_align_size = ALIGN(sizeof(struct lgsnap_info_bl), 4) + ALIGN(sizeof(struct lgsnap_save_list) * info->bl_info->save_list_count, 4)
        + ALIGN(sizeof(union lgsnap_page_desc) * info->bl_info->page_desc_count, 4);

    block_align_size %= PAGE_SIZE;
    block_align_size = PAGE_SIZE - block_align_size;

    buffer = kzalloc(block_align_size, GFP_KERNEL);

    ret = write_snapshot(buffer, block_align_size);     
    if(ret <= 0)
		return ret;
	
	kfree(buffer);
        
    memory_bm_position_reset(bm);
	for(;;) {
		pfn = memory_bm_next_pfn(bm);
     
		if (unlikely(pfn == BM_END_OF_MAP))
			break;
		if (image_size >= comp_image_size)
			break;
        
        s_page = pfn_to_page(pfn);
        if (PageHighMem(s_page)) {
            src = kmap_atomic(s_page);
            ret = write_snapshot(src, PAGE_SIZE);
            kunmap_atomic(src);
			if(ret <= 0)
				return ret;
			image_size += ret;

        } else {
            src = pfn_to_virt(pfn);
	
            ret = write_snapshot(src, PAGE_SIZE);
			if(ret <= 0)
				return ret;
			image_size += ret;
        }
	}

    return 0;
}

lgsnap_status_t lgsnap_get_status(void)
{
	return lgsnap_status;
}

void lgsnap_set_status(lgsnap_status_t status)
{
	lgsnap_status = status;
}

unsigned int lgsnap_get_worst_comp_result_size(lgsnap_comp_t comp_type, unsigned int size)
{
    unsigned int worst_size;
    
    switch(comp_type) {
    case LGSNAP_COMP_LZO:
        worst_size = lzo1x_worst_compress(size);
        break;

    // TODO : implement another compression type        
    
    default:
        worst_size = size;
        break;
    }

    return worst_size;
}

unsigned long lgsnap_get_comp_desc_worst_size(union lgsnap_page_desc *page_desc,
                unsigned int max_count, lgsnap_comp_t compt_type, unsigned int comp_block_size)
{
    int i;
    int comp_page_desc_count = 0;
    unsigned int length, addend;
    
    for(i = 0; i <= max_count; i++) {
        length = get_length(&page_desc[i]);
        length = lgsnap_get_worst_comp_result_size(compt_type, length);
        
        if(length <= comp_block_size)
            comp_page_desc_count++;
        else {
            addend = length / comp_block_size;
            comp_page_desc_count += addend;
            
            if((length % comp_block_size) != 0)
                comp_page_desc_count++;    
        }
    }
	comp_page_desc_count *= 2;

	printk("lgsnap_worst page desc count : %d(0x%x)\n", comp_page_desc_count, comp_page_desc_count);

    return comp_page_desc_count * sizeof(union lgsnap_page_desc);
}

void lgsnap_make_input_buffer(char *input, int ilen, 
                                    struct memory_bitmap *bm)
{
    char *buffer;
    unsigned long pfn;
    
    while(ilen > 0) {
        pfn = memory_bm_next_pfn(bm);
        buffer = pfn_to_virt(pfn);

        if(ilen < PAGE_SIZE)
            memcpy(input, buffer, ilen);
        else
            memcpy(input, buffer, PAGE_SIZE);
        
        input += PAGE_SIZE;
        ilen -= PAGE_SIZE;
    }
}

//TODO : we must check : output > input case, HIGHMEM support
// offset must be aligned to 4 bytes
void lgsnap_copy_comp_result(char *output, int dlen, struct memory_bitmap *obm, int offset)
{
    char *buffer;
    unsigned long pfn;
      
    pfn = memory_bm_current_pfn(obm);

    buffer = pfn_to_virt(pfn) + offset;
    if(dlen + offset > PAGE_SIZE ){
        memcpy(buffer, output, PAGE_SIZE - offset);
        dlen -= (PAGE_SIZE - offset);
        output += (PAGE_SIZE - offset); 
    } else if(dlen + offset == PAGE_SIZE){
        memcpy(buffer, output, dlen);
        memory_bm_next_pfn(obm);
        return;
    } else {
        memcpy(buffer, output, dlen);
        return;
    }
    
    while(dlen > 0) {
        pfn = memory_bm_next_pfn(obm);
        buffer = pfn_to_virt(pfn);

        if(dlen > PAGE_SIZE) {
            memcpy(buffer, output, PAGE_SIZE);
        } else {
            memcpy(buffer, output, dlen);
        }
        
        dlen -= PAGE_SIZE;
        output += PAGE_SIZE;
    }

    if(dlen == 0)
        memory_bm_next_pfn(obm);

}

int lgsnap_get_esti_size(int target_length, int input_length, int out_length)
{
	int diff;
	int ratio, ret;
	
	if(target_length > out_length)
		diff = target_length - out_length;
	else
		diff = out_length - target_length;

	ratio = ((input_length << 5) / (out_length <<5)) >> 5;

	if(ratio <=2)
		ret = (ALIGN((diff) + ((diff) >> 1), PAGE_SIZE));
	else 
		ret = (ALIGN((diff * ratio), PAGE_SIZE));

	return ret;
}

int lgsnap_make_comp_block(struct crypto_comp *tfm, int *ilen, int *dlen, 
                                    struct memory_bitmap *ibm, struct memory_bitmap *obm, 
                                    int offset, lgsnap_comp_t comp_type, int block_length, int *not_compressed)
{
	int ret;
	int best_comp_size, esti_comp_size;
    unsigned int temp_len;
	char *input = NULL, *output = NULL;

    esti_comp_size = lgsnap_get_esti_size(block_length, 2, 1);
	if(*ilen > esti_comp_size)
		best_comp_size = esti_comp_size;
	else 
		best_comp_size = *ilen;
   
	input = vmalloc(best_comp_size);
	temp_len = lgsnap_get_worst_comp_result_size(comp_type, best_comp_size);
	output = vmalloc(temp_len);

	lgsnap_make_input_buffer(input, best_comp_size, ibm);

	ret = crypto_comp_compress(tfm, input,
		   best_comp_size, output, dlen);
	if (ret) {
		printk(KERN_ERR "alg: comp: compression failed \n");
		goto fail;
	}

	if(temp_len < *dlen) {
		printk(KERN_ERR "decomp result length is strange. Please check!!!\n");
		ret = -1;
		goto fail;
	}
	
    *ilen = best_comp_size;
        
	if(*dlen >= *ilen) {
		*not_compressed = 1;
		*dlen = *ilen;
		lgsnap_copy_comp_result(input, *dlen, obm, offset);
	} else {
		*not_compressed = 0;
		lgsnap_copy_comp_result(output, *dlen, obm, offset);
    }
            
    ret = 0;
    
fail:
    vfree(input);
    vfree(output);

    return ret;
}

unsigned int lgsnap_total_length(union lgsnap_page_desc *page_desc, unsigned int count)
{
	unsigned int i;
    unsigned int total_length = 0;

    struct lgsnap_page_desc_ops *ops = lgsnap_get_page_desc_ops();

	for(i=0; i < count; i++)
        total_length += ALIGN(ops->get_length(&page_desc[i]), 4);

    return total_length;
}

int lgsnap_compress_snapshot(void)
{
	unsigned int i, index = 0;
    unsigned long comp_page_desc_size;
    unsigned int not_compressed;
	int ilen, dlen, length, saved_length, block_length, offset = 0;
 	struct crypto_comp *tfm;
    struct lgsnap_info *info;
	struct memory_bitmap *bm;
	union lgsnap_page_desc *comp_page_desc; 
	union lgsnap_page_desc *ori_page_desc;
    struct lgsnap_info_bl *info_bl;
    struct memory_bitmap *comp_bm;

    info = lgsnap_get_info();
    info_bl = info->bl_info;
    if(info_bl->comp_type == LGSNAP_COMP_OFF)
        return 0;

    lgsnap_test_start();

    ori_page_desc = info->page_desc; 
    bm = info->copy_bm;

    comp_bm = memory_bm_copy(bm);

    memory_bm_position_reset(comp_bm);
    memory_bm_position_reset(bm);
    comp_page_desc_size = 
        lgsnap_get_comp_desc_worst_size(ori_page_desc, info_bl->page_desc_count, 
                                        info_bl->comp_type, info_bl->comp_block_size);
    
	printk("comp_page_desc_size : %lu\n", comp_page_desc_size);
	
	comp_page_desc = kmalloc(comp_page_desc_size, GFP_ATOMIC);
    block_length = info->bl_info->comp_block_size;
    
	tfm = crypto_alloc_comp(lgsnap_get_comp_string(info->bl_info->comp_type), 0, 0);
	
	for(i = 0; i < info_bl->page_desc_count; i++) {
		saved_length = length = get_length(&ori_page_desc[i]);
        
		while(length > 0) {
			// available max length setting
			ilen = length;
			if(lgsnap_make_comp_block(tfm, &ilen, &dlen, bm, comp_bm, offset, info_bl->comp_type, block_length, &not_compressed))
                goto free_obj;

			set_address(&comp_page_desc[index], (get_address(&ori_page_desc[i]) + ((saved_length - length) >> PAGE_SHIFT)) | (not_compressed << 31));
			set_length(&comp_page_desc[index], dlen);	
    		length -= ilen;
			index ++;

            // offset must be aligned to 4 bytes
            offset = ALIGN((offset + dlen) % PAGE_SIZE, 4);
            
  //        lgsnap_dprintk("[%d] ilen : %d( %lu pages), dlen : %d( %lu pages), offset : %d, remain : %d(%lu pages)\n\n\n",
  //             i, ilen, ilen / PAGE_SIZE, dlen, PAGES(dlen), offset, length, PAGES(length));
            
		}
	}

	info_bl->page_desc_count = index;
    info_bl->image_size = lgsnap_total_length(comp_page_desc, index);
    
	printk("comp_info length : %d\n", index);
	printk("comp image size : %d(0x%x) %dMBytes\n", info_bl->image_size, info_bl->image_size, info_bl->image_size >> 20);

    info->page_desc = comp_page_desc;
    info_bl->page_desc_count = index;
    
	lgsnap_dump_header(info);

    crypto_free_comp(tfm);

    lgsnap_test_finish("compression done");
   
	return 0;
	
free_obj:
	kfree(comp_bm);

	return -1;
}

int  lgsnap_make_header(struct lgsnap_info *info, unsigned int kernel_count, unsigned int page_desc_count)
{
    struct lgsnap_info_bl *bl_info= info->bl_info;

    info->kernel_count = kernel_count;
    
	strncpy(bl_info->magic, LGSNAP_MAGIC, LGSNAP_MAGIC_LENGTH);
    bl_info->comp_type = lgsnap_get_comp_type();
    bl_info->comp_block_size = lgsnap_get_comp_block_size();
    bl_info->page_desc_count = page_desc_count;
    bl_info->offset_save_list = ALIGN(sizeof(struct lgsnap_info), 4);
    bl_info->offset_lgsnap_page_desc = bl_info->offset_save_list 
        + ALIGN(sizeof(struct lgsnap_save_list) * bl_info->save_list_count, 4);

    return 0;
}

int  lgsnap_make_page_desc(union lgsnap_page_desc *page_desc, unsigned int estimate_count)
{
	unsigned int pfn_count = -1; // -1 == 0xffffffff
	unsigned int kernel_count = 0;
    struct memory_bitmap *bm;
    unsigned long pfn;
    struct lgsnap_info *info;
    info = lgsnap_get_info();

	if(unlikely(!page_desc)) 
		return -1;

    bm = info->orig_bm;
    
    memory_bm_position_reset(bm);
	for(;;) {
		pfn = memory_bm_next_pfn(bm);
     
		if (unlikely(pfn == BM_END_OF_MAP))
			break;
            
		if(pfn_count != -1 && (get_address(&page_desc[pfn_count]) + get_length(&page_desc[pfn_count]) == pfn)) {
			set_length(&page_desc[pfn_count], get_length(&page_desc[pfn_count]) + 1);
		} else {
		    if(unlikely((pfn_count >= estimate_count) && pfn_count != -1)) {
				printk("%s %d : savable page count estimation fail\n", __func__, __LINE__);
                return -1;
	    	}

            if(likely(pfn_count != -1)) {
                set_length(&page_desc[pfn_count], get_length(&page_desc[pfn_count]) * PAGE_SIZE);
                set_attr(&page_desc[pfn_count],  LGSNAP_ADMA_ATTR_VALID |  LGSNAP_ADMA_ATTR_TRAN | LGSNAP_ADMA_ATTR_INT);
            }
            
            pfn_count++; // 0xffffffff + 1 = 0x0

			set_address(&page_desc[pfn_count], pfn);
			set_length(&page_desc[pfn_count], 1);
		}
        kernel_count++;
	}
    
    set_length(&page_desc[pfn_count], get_length(&page_desc[pfn_count]) * PAGE_SIZE);
    set_attr(&page_desc[pfn_count],  LGSNAP_ADMA_ATTR_VALID |  LGSNAP_ADMA_ATTR_END);
    
	return kernel_count;
}

unsigned int lgsnap_get_page_desc_size(void)
{
	unsigned int pfn_count = -1; // -1 == 0xffffffff
    union lgsnap_page_desc page_desc;
    struct memory_bitmap *bm;
    unsigned long pfn;
    struct lgsnap_info *info;

    info = lgsnap_get_info();
    bm = info->orig_bm;

    memory_bm_position_reset(bm);
	for(;;) {
		pfn = memory_bm_next_pfn(bm);
     
		if (unlikely(pfn == BM_END_OF_MAP))
			break;

		if(pfn_count != -1 && (get_address(&page_desc) + get_length(&page_desc) == pfn)) {
			set_length(&page_desc, get_length(&page_desc) + 1);
		} else {
            pfn_count++; // 0xffffffff + 1 = 0x0
            
			set_address(&page_desc, pfn);
			set_length(&page_desc, 1);
        }
	}
	return pfn_count+1;
}
