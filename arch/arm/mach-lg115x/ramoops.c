#include <linux/kernel.h>

#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>

#include <linux/ramoops.h>

#include <mach/resource.h>

#include "ramoops.h"

static struct ramoops_platform_data ramoops_data = {
    .mem_size               = 0x80000,
    .mem_address            = 0xaf000000,
    .record_size            = 0x3F800,
    .dump_oops              = 0x1,
};

static struct platform_device ramoops_dev = {
    .name = "ramoops",
    .dev = {
        .platform_data = &ramoops_data,
    },
};

void __init lg115x_init_ramoops(void)
{
    int ret;

    ret = platform_device_register(&ramoops_dev);
    if (ret) {
        printk(KERN_ERR "unable to register ramoops platform device\n");
        return ret;
    }
}

