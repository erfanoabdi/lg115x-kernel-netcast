/*
 *
 *  fs/partitions/lgemmc.c
 *
 *  this partition system using for EMMC
 *
 *  maked by hankyung.yu in SIC Center SPT Group
 *
 */

#include <linux/msdos_fs.h>
#include <linux/proc_fs.h>

#include "check.h"
#include "lgemmc.h"

/*
 * Many architectures don't like unaligned accesses, while
 * the nr_sects and start_sect partition table entries are
 * at a 2 (mod 4) address.
 */
#include <asm/unaligned.h>

#undef DEBUG
//#define DEBUG

/* magic number */
#ifdef CONFIG_LGEMMC_PARTITION_LA
#define PARTMAP_MAGIC					(0x20120716)
#else
#define PARTMAP_MAGIC					(0x20110609)
#endif

#define EMMC_PARTINFO_ADDR 			(0x100000)		// 1Mbyte = 800 sector (1sector = 512byte)

#define SECT_IDX(pos)					(unsigned long)(pos>>9)
#define SECT_POS(idx)					(unsigned long)(idx<<9)

/*-----------------------------------------------------------------------------
 * partition info
 */
#define STR_LEN_MAX					32
#define PARTITION_MAX					64

struct device_info
{
	char			name[STR_LEN_MAX];
#ifdef CONFIG_LGEMMC_PARTITION_LA
	unsigned long long	size;
	unsigned long long	phys;
#else
	unsigned int	size;
	unsigned int	phys;
#endif
	void			*virt;
	void			*cached;
	int				bankwidth;
	unsigned int	used;
};

struct partition_info
{
	char			name[STR_LEN_MAX];			/* identifier string                               */
#ifdef CONFIG_LGEMMC_PARTITION_LA
	unsigned long long	offset;					/* offset within the master MTD space              */
	unsigned long long	size;					/* partition size                                  */
#else
	unsigned int	offset;						/* offset within the master MTD space              */
	unsigned int	size;						/* partition size                                  */
#endif
	char			filename[STR_LEN_MAX];		/* file name                                       */
	unsigned int	filesize;					/* file size                                       */
	unsigned int	sw_ver;						/* software version                                */
	unsigned char	used;						/* Is this partition is used?                      */
	unsigned char	valid;						/* Is this partition is valid?                     */
	unsigned int	mask_flags;					/* master MTD flags to mask out for this partition */
};

struct partmap_info
{
	unsigned int					magic;
	unsigned int					cur_epk_ver;
	unsigned int					old_epk_ver;
	unsigned char 					npartition;
	struct device_info				dev;
	struct partition_info			partition[PARTITION_MAX];
};

struct partmap_info partinfo;

static int nb_parts = 0;

#ifdef CONFIG_PROC_FS

/*====================================================================*/
/* Support for /proc/mtd */

static struct proc_dir_entry *proc_partinfo;

static inline int part_proc_info (char *buf, int slot)
{
	struct partition_info* this = &(partinfo.partition[slot-1]);

	if (!this)
		return 0;

	return sprintf(buf, "part%d: %8.8llx %8.8llx \"%s\"\n", slot,
				(unsigned long long)this->offset,
				(unsigned long long)this->size,
				this->name);
}

static int partinfo_read_proc (char *page, char **start, off_t off, int count,
			  int *eof, void *data_unused)
{
	int len, l, slot;
    off_t   begin = 0;

	len = sprintf(page, "dev:    offset   size  name\n");

	for (slot=1; slot<nb_parts; slot++) {
	    l = part_proc_info(page + len, slot);
	    len += l;
	    if (len+begin > off+count)
	            goto done;
	    if (len+begin < off) {
	            begin += len;
	            len = 0;
	    }
	}

	*eof = 1;

	done:
	if (off >= len+begin)
	    return 0;
	*start = page + (off-begin);
	return ((count < begin+len-off) ? count : begin+len-off);
}

#endif /* CONFIG_PROC_FS */

int lgemmc_partition(struct parsed_partitions *state)
{
	Sector sect;
	unsigned char *data, *pbuf;
	unsigned int i, nsect;
	unsigned int magic;
	int slot = 0;
	u32 start = 0;
	u32 size = 0;
	u32 last_size = 0;
	unsigned long long emmc_size;

	/* fisrt of all, check magic without using static memory */
	data = read_part_sector(state, SECT_IDX(EMMC_PARTINFO_ADDR), &sect);
	if (!data)
		return -1;
	magic = (data[3] << 24) + (data[2] << 16) + (data[1] << 8) + data[0];
	put_dev_sector(sect);	
	if (magic == PARTMAP_MAGIC)
	{
		printk("LG EMMC PARTITION MAP! \n");
	}
	else
	{
		return 0;
	}

	pbuf = (unsigned char *)&(partinfo);
	nsect  = (sizeof(struct partmap_info) / 512) + 1;
	last_size = 512 - (( 512 * nsect) - sizeof(struct partmap_info));

	for(i=0; i<nsect; i++) {
		data = read_part_sector(state, SECT_IDX(EMMC_PARTINFO_ADDR) + i, &sect);
		if (!data)
			return -1;
		if (i == (nsect-1))
		{
			memcpy((unsigned char*)&pbuf[SECT_POS(i)], data, last_size);
		}
		else
		{
			memcpy((unsigned char*)&pbuf[SECT_POS(i)], data, 512);
		}
		put_dev_sector(sect);
	}


	nb_parts = partinfo.npartition;
#ifdef DEBUG
	printk("part info : # of partition = %d\n", nb_parts);
#endif
	state->next = PARTITION_MAX + 1;
	emmc_size = (unsigned long long)(state->bdev->bd_disk->part0.nr_sects)<<9;

	for(slot=1; slot<nb_parts; slot++) {
		struct partition_info* ptt_info = (struct partition_info*)&(partinfo.partition[slot-1]);
		//larger than 4GB or smaller than 3696MB
		if (emmc_size > 0x100000000 || emmc_size < 0xe7000000)
		{
			if(!strncmp("apps",ptt_info->name,4))
			{
				printk("ENTER APPS \n");
				ptt_info->size = emmc_size - ptt_info->offset;
			}
		}

		start	= (u32)SECT_IDX(ptt_info->offset);
		size 	= (u32)SECT_IDX(ptt_info->size);
		put_partition(state, slot, start, size);

		printk(" %s%d 0x%012llx-0x%012llx : \"%s\"\n", state->name, slot,
				(unsigned long long)ptt_info->offset,
				(unsigned long long)(ptt_info->offset + ptt_info->size),
				ptt_info->name);

#ifdef DEBUG
		printk("{\n");
		printk("  .name =      \"%s\"\n", 	ptt_info->name);
		printk("  .offset =    0x%x\n", 	ptt_info->offset);
		printk("  .size =      0x%x\n", 	ptt_info->size);
		printk("}\n");
#endif
	}
#ifdef DEBUG
	printk("\n");
#endif

#ifdef CONFIG_PROC_FS
	if ((proc_partinfo = create_proc_entry( "partinfo", 0, NULL )))
		proc_partinfo->read_proc = partinfo_read_proc;
#endif /* CONFIG_PROC_FS */

	return 1;
}

char *lgemmc_get_partition(const char *part_name)
{
    int slot = 0;
    u32 start = 0;
    unsigned char *dev_name;

    nb_parts = partinfo.npartition;

    for(slot = 1; slot < nb_parts; slot++) {
        struct partition_info *ptt_info = (struct partition_info *)&(partinfo.partition[slot-1]);
        start = (u32)SECT_IDX(ptt_info->offset);

        if(!strncmp(part_name, ptt_info->name, strlen(part_name)))
            break;
    }

    dev_name = kmalloc(30, GFP_KERNEL);

    sprintf(dev_name, "/dev/mmcblk0p%d", slot);
    
    printk("Lgsnap hib partition : %s\n", dev_name);
    
    return dev_name;
}

u32 lgemmc_get_partition_size(const char *part_name)
{
    int slot = 0;
    u32 size = 0;

    nb_parts = partinfo.npartition;

    for(slot = 1; slot < nb_parts; slot++) {
        struct partition_info *ptt_info = (struct partition_info *)&(partinfo.partition[slot-1]);

        size  = (u32)SECT_IDX(ptt_info->size);

        if(!strncmp(part_name, ptt_info->name, strlen(part_name)))
            break;
    }

    printk("Lgsnap hib partition size : %d(0x%x)\n", size, size);
    
    return size;
}

