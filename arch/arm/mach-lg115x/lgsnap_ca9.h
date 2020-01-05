
/* ----------------------------------------------------------------------
 * 
 * Deep sleep mode and Instant boot verification. made by yw.kim@lge.com
 *
 * ----------------------------------------------------------------------
 */

#ifndef LG115X_CPU_SLEEP_H
#define LG115X_CPU_SLEEP_H

/*
Test for BOOTLOADER or KERNEL.
Select boot loader or linux kernel.
*/
#define LG115X_DEEP_SLEEP_IN_KERNEL		1
//#define LG115X_DEEP_SLEEP_IN_BLOADER	1

#ifdef LG115X_DEEP_SLEEP_IN_KERNEL
#include <mach/resource.h>
#include <asm/hardware/gic.h>
#elif defined(LG115X_DEEP_SLEEP_IN_BLOADER)
#include <config.h>
#include "gic.h"
#endif


#define	io_address(a)	__io(a)
/* ----------------------------------------------------------------------------
 * reset vector position
 * ----------------------------------------------------------------------------
 */
#define RST_VECTOR_ON_SRAM	0	/* 0: on DRAM, 1: on SRAM*/



/* ----------------------------------------------------------------------------
 * SYMBOLIC CONSTANTS FOR RESET VECTOR REPLACE
 * ----------------------------------------------------------------------------
 */
#define RST_VECTOR_PHYS_ADDR	(0x00000000)
#define RST_HNDLR_OFFSET		(0x000000C0)
#define RST_HNDLR_PHYS_ADDR		(RST_VECTOR_PHYS_ADDR+RST_HNDLR_OFFSET)



/* ----------------------------------------------------------------------------
 * SYMBOLIC CONSTANTS FOR ATLAS SETTING IN SRAM
 * ----------------------------------------------------------------------------
 */
/*code execution address in sram*/
#define DRAM_VECT_VIRT_ADDR		0xffff0000 //kernel change
#define SRAM_VECT_VIRT_ADDR		0xffff0000 //kernel change
#define SRAM_VECT_PHYS_ADDR		0xfff00000
#define SRAM_CODE_PHYS_ADDR		0xFFF01000 /*in sram*/
#define SRAM_CODE_VIRT_ADDR		0xFFFF1000


#define NUM_FIRST_ENTRIES		10
#define NUM_SECOND_ENTRIES		3
#define NUM_THIRD_ENTRIES		2
#define NUM_FOURTH_ENTRIES  	10
#define NUM_FIFTH_ENTRIES		0


/*the number of atlas parameter*/
#define NUM_DDR_SELF_REFRESH_PARAMS	( NUM_FIRST_ENTRIES \
										+ NUM_SECOND_ENTRIES \
										+ NUM_THIRD_ENTRIES	\
										+ NUM_FOURTH_ENTRIES \
										+ NUM_FIFTH_ENTRIES )

#define	SECONDARY_OFFSET	0x400
/* ----------------------------------------------------------------------------
 * CONDITIONAL COMPILATION FOR VERIFICATION
 * ----------------------------------------------------------------------------
 */


#ifndef CONFIG_LG115X_DEEP_SLEEP_MODE
/* Enter and restoration codes for deep sleep mode and restoration.*/
#define CONFIG_LG115X_DEEP_SLEEP_MODE	1

#endif

/*
symbolic defination for gnu as assembly.*/
#define CONFIG_LG115X_GNU_ARM_ASM		1

/*
symbolic defination for armasm assembly.*/
//#define CONFIG_LG115X_ARMASM			1

/*
debug code for cou core information.*/
//#define CONFIG_CPU_CORE_INFO			1

/*
reset vector replace in case of restoration for cpu state.*/
#define CONFIG_LG115X_IBOOT_RST_REPLACE	1

/*
lg115x hw schedule is very delayed, so we make only software test option for instant boot*/
//#define CONFIG_LG115X_IBOOT_ONLY_SW_TEST
/*-------------------------------------------------------------------*/

/*
We need to test in case of mmu off and on. 
*/
//#define CONFIG_LG115X_SRAM_EXEC_SREFRESH_WITH_MMU
#ifndef CONFIG_LG115X_SRAM_EXEC_SREFRESH_WITH_MMU
#define CONFIG_LG115X_SRAM_EXEC_SREFRESH_WITHOUT_MMU
#endif

/*
Only software test, in case of not ready hardware in instant boot verification. 
*/
//#define CONFIG_LG115X_REG_RW_TEST_IN_SRAM_CODES
//#define LG115X_IBOOT_CONSOLE_DEBUG		1

#ifdef CONFIG_TRUSTZONE

/*
; GIC Register field value.
*/
#define ICDISR_SGI_PPI_NONSECURE	(0xFFFFFFFF)
#define ICDISER_SGI_SET_ENABLE		(0xFFFF)
#define ICCICR_EnableNS				(0x1<<1)

/*
; NSACR field value.
*/
#define NSACR_NS_SMP				(0x1<<18)
#define NSACR_TL					(0x1<<17)
#define NSACR_CP_10					(0x1<<10)
#define NSACR_CP_11					(0x1<<11)

/*
* ACTLR field value.
**/
#define ACTLR_FW					(0x1<<0)
#define ACTLR_SMP					(0x1<<6)

/*
; SCR field value.
*/
#define SCR_NS						(0x1<<0)
#define SCR_IRQ						(0x1<<1)
#define SCR_FIQ						(0x1<<2)
#define SCR_EA						(0x1<<3)
#define SCR_FW						(0x1<<4)
#define SCR_AW						(0x1<<5)

#endif /* CONFIG_TRUSTZONE */


#endif /*LG115X_CPU_SLEEP_H*/
