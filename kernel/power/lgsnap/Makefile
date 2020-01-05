
ifeq ($(CONFIG_LGSNAP_DEBUG),y)
EXTRA_CFLAGS	+=	-DDEBUG
endif

obj-$(CONFIG_LGSNAP)		+= lgsnap_module.o lgsnap_main.o lgsnap_core.o
obj-$(CONFIG_LGSNAP_DEBUG)	+= lgsnap_debug.o
