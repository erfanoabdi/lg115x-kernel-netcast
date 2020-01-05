@ Author: Yaewon Kim (yw.kim@lge.com)
@ Modifier: Sinchul Jung (sinchul.jung@lge.com)
#include <asm/memory.h>
#include "lgsnap_ca9.h"
#include <mach/resource.h>

	.text

/* ---------------------------------------------------------------------------------
 * Configuration and constants
 * ---------------------------------------------------------------------------------
 */
	.equ 	MODE_USR,   	0x10
	.equ 	MODE_FIQ,   	0x11
	.equ 	MODE_IRQ,   	0x12
	.equ 	MODE_SVC,   	0x13
	.equ 	MODE_ABT,   	0x17
	.equ 	MODE_UND,   	0x1B
	.equ 	MODE_SYS,   	0x1F
/* ---------------------------------------------------------------------------------
 * Deep Sleep Mode Entry
 * ---------------------------------------------------------------------------------
 */

/*
 * This code assumes that the operating system will make the decision to enter deep 
 * sleep mode. The operating system must call this deep sleep mode entry code in 
 * SVC mode using an instruction of the form:
 *      BL dsm_entry
 * as the shutdown mode exit code returns using a mov pc,r14 instruction.  The entry 
 * code assumes that it is in System mode and does not check for this.
 *
 * The deep sleep mode entry code saves all required state in the correct order.
 * Information about the deep sleep mode exit code is given at the start of that code.
*/
	/*
	*
	* for storing primary CPU context and peripherals status @@
	*/
	.global  dsm_entry
dsm_entry:
	push {r0-r12, r14}
	
	/* we are in SVC Mode really!!.
	 * Save general purpose registers (SVC) and cpsR
	 */
	str     r0,r0_tmp_str 					/*Temporary store */
	ldr     r0,dsm_sav_rgn_addr				/*Get state save addr*/
	str     r1,[r0,#4]    					/*Save r1*/
	mov     r1,r0         					/*Get state save addr*/
	ldr     r0,r0_tmp_str 					/*Restore r0*/
	str     r0,[r1],#8    					/*Save r0*/

	/* By Lee sangseok for resume*/
	add		r13, r13, #56
	stmia   r1!,{r2-r14}  					/*Save r2-r14 (SVC)*/
	/* By Lee sangseok for resume */
	sub		r13, r13, #56
	
	mrs     r0,cpsR       					/*Get cpsR*/
	str     r0,[r1],#4    					/*Save cpsR*/
	
	/*
	 * Disable interrupts until mode regs & SPSRs are saved
	 * Also change to FIQ mode for next section
	 * FOR CPU0
	 */
	cpsid   if,#MODE_FIQ
	
	@ Save FIQ mode registers and SPSR
	stmia   r1!,{r8-r14}                    /*Save r8-r14 (FIQ)*/
	mrs     r0,SPSR                         /*Get SPSR*/
	str     r0,[r1],#4                      /*Save SPSR*/
	
	@ Save IRQ mode registers and SPSR
	cps     #MODE_IRQ
	stmia   r1!,{r13-r14}                   /*Save r13-r14 (IRQ)*/
	mrs     r0,SPSR                         /*Get SPSR*/
	str     r0,[r1],#4                      /*Save SPSR*/
	
	@ Save Abort mode registers and SPSR
	cps     #MODE_ABT
	stmia   r1!,{r13-r14}                   /*Save r13-r14 (Abort)*/
	mrs     r0,SPSR                         /*Get SPSR*/
	str     r0,[r1],#4                      /*Save SPSR*/
	
	@ Save Supervisor mode registers and SPSR
	cps     #MODE_SYS
	stmia   r1!,{r13-r14}                   /*Save r13-r14 (SYS/USR)*/
	mrs     r0,SPSR                         /*Get SPSR*/
	str     r0,[r1],#4                      /*Save SPSR*/
	
	@ Save Undefined mode registers and SPSR
	cps     #MODE_UND
	stmia   r1!,{r13-r14}                   /*Save r13-r14 (Undef)*/
	mrs     r0,SPSR                         /*Get SPSR*/
	str     r0,[r1],#4                      /*Save SPSR*/
	
	@ Return to System mode and enable interrupts
	cpsIE	aif,#MODE_SVC

	/*
	* store SCU configuration 
	*/
	ldr	r0,=__MMIO_P2V(MPCORE_SCU_BASE)
	ldr	r2,[r0]
	ldr	r3,[r0,#0x4]
	stmia	r1!,{r2,r3}

	/*
	 * Save TLB lockdown register, then force page table walks to
	 * write into the associative region of the TLB, to avoid
	 * changing the lockdown region 
	 */
	mrc     p15,0,r2,c10,c0,0               /*TLB Lockdown*/
	str     r2,[r1],#4                      /*Save*/
	bic     r2,r2,#1                        /*Clear P bit*/
	mcr     p15,0,r2,c10,c0,0               /*Write TLB Lockdown*/

	@ Save CP15 control & fault registers
	mrc     p15,0,r2,c5,c0,0                /*DFSR */
	mrc     p15,0,r3,c5,c0,1                /*IFSR */
	mrc     p15,0,r4,c6,c0,0                /*FAR */
	mrc     p15,0,r5,c6,c0,1                /*IFAR */
	mrc     p15,0,r6,c1,c0,1                /*Auxiliary Control */
	mrc     p15,0,r7,c1,c0,2                /*Coproc Access Control */
	stmia   r1!,{r2-r7}                     /*Save */


	@ Save CP15 thread/processID registers
	mrc     p15,0,r2,c13,c0,2               /*User R/W Thread/PID */
	mrc     p15,0,r3,c13,c0,3               /*User RO Thread/PID */
	mrc     p15,0,r4,c13,c0,4               /*Priv Only Thread/PID */
	stmia   r1!,{r2-r4}                     /*Save */

#ifndef CONFIG_TRUSTZONE	
	@ Save lockdown region of TLB
	mcr     p15,5,r0,c15,c4,2               /* Read lockdown entry 0 */
	mrc     p15,5,r2,c15,c5,2               /* Read Main TLB VA */
	mrc     p15,5,r3,c15,c6,2               /* Read Main TLB PA */
	mrc     p15,5,r4,c15,c7,2               /* Read Main TLB Attr */
	stmia   r1!,{r2-r4}
#endif

	/*
	 * Save the state of any memory-mapped peripherals that are
	 * powered down in deep sleep mode.
	 * Currently, For LG115X verification, Console(Uart) and Timer
	 */
	.equ	CONSOLE_BASE,	__MMIO_P2V(UART0_BASE)
	
	ldr     r0,=CONSOLE_BASE
	ldr     r2,[r0,#0x24]                   
	ldr     r3,[r0,#0x28]                   
	ldr     r4,[r0,#0x2c] 
	ldr     r5,[r0,#0x30]
	stmia   r1!,{r2-r5}                     /*Save */
	
	/*
	Save memory system control registers */
	mrc     p15,0,r2,c1,c0,0                /*CR*/
	mrc     p15,0,r3,c2,c0,0                /*TTBR0*/
	mrc     p15,0,r4,c2,c0,1                /*TTBR1*/
	mrc     p15,0,r5,c2,c0,2                /*TTBCR*/
	mrc     p15,0,r6,c3,c0,0                /*daC*/
	mrc     p15,0,r7,c13,c0,0               /*FCSE PID*/
	mrc     p15,0,r8,c13,c0,1               /*Context ID*/
	stmia   r1!,{r2-r8}                     /*Save*/

	mrc	p15,0,r2,c10,c2,0		/*PRRR*/
	mrc	p15,0,r3,c10,c2,1		/*NMRR*/
	mrc	p15,0,r4,c13,c0,2		/*USER R/W thread and process ID*/
	mrc	p15,0,r5,c13,c0,3		/*USER RO thread and process ID*/
	mrc	p15,0,r6,c13,c0,4		/*Privilege only thread and process ID*/

	/*
	 * Normal world don't use VBAR.
	 * primary cpu(save), yw.kim@lge.com
	 */
#ifdef CONFIG_TRUSTZONE
	stmia	r1!,{r2-r6}
#else
	mrc	p15,0,r7,c12,c0,0		/*Secure or NS vector base address*/
	stmia	r1!,{r2-r7}
#endif

	/*
	 * Disable interrupts, caches and mmu, moved from below
	 */
	cpsid ifa					@ Disable interrupts	

	/*
	Save Generic Inaterrupt Controller registers.
	GIC include distribute interrupt controller and cpu interface.*/
	/*1*/
	ldr 	r0,=__MMIO_P2V(MPCORE_GIC_DIST_BASE+GIC_DIST_ENABLE_SET)
	ldr 	r2,[r0,#0x0]
	ldr 	r3,[r0,#0x4]
	ldr 	r4,[r0,#0x8]
	ldr 	r5,[r0,#0xc]
	stmia   r1!,{r3-r4}

	/*2*/
	ldr 	r0,=__MMIO_P2V(MPCORE_GIC_CTRL_BASE+GIC_CPU_CTRL)
	ldr	r2,[r0]
	ldr	r3,[r0,#8]
	str     r2,[r1],#0x4
	str	r3,[r1],#0x4

	/*3*/
	ldr	r0,=__MMIO_P2V(MPCORE_GIC_DIST_BASE+GIC_DIST_CTRL)
	ldr 	r2,[r0]
	str	r2,[r1],#0x4

	/*5*/
	ldr	r0,=__MMIO_P2V(MPCORE_GIC_DIST_BASE+GIC_DIST_TARGET)
	add	r3,r0,#0xb0
gic_store_target:
	ldr	r2, [r0],#4
	str	r2, [r1],#4
	cmp	r3, r0
	bne	gic_store_target

	/*6*/
	ldr 	r0,=__MMIO_P2V(MPCORE_GIC_DIST_BASE+GIC_DIST_PRI)
	@add		r0,r0,#0x20	
	add	r3,r0,#0xb0
gic_store_pri:
	ldr	r2, [r0],#4
	str	r2, [r1],#4
	cmp	r3, r0
	bne		gic_store_pri
	
	/*	
	 * Save Dual input timer registers.	
	 * Timer0 and Timer1 register, offset is 0x20.
	 */
	/* global timer */
	ldr 	r0,=__MMIO_P2V(TIMER_BASE)
	ldr 	r2,[r0]    /*timer 0 load reg*/
	ldr 	r3,[r0,#8] /*timer 0 control reg*/

	add 	r0,r0,#0x20
	ldr 	r4,[r0]		/*timer 1 load reg*/
	ldr 	r5,[r0,#8]  /*timer 1 control reg*/
	stmia   r1!,{r2-r5}
	/* local timer */
	ldr	r0,=__MMIO_P2V(MPCORE_PTIMER_BASE)
	ldr	r2,[r0]		/* local timer for CPU0 load reg */
	ldr	r3,[r0,#8]		/* local timer for CPU0 control reg */
	stmia	r1!,{r2,r3}
	
	/*	
	 * Note: we do not save Cache Lockdown registers, as we lose the	
	 * data or instructions in the locked ways.
	 *
	 * Save the address at the end of the state saving.	
	 * Save this at a known fixed address so we can restore from it.
	 */

	ldr		r0, =dsm_sav_rgn
	sub		r1, r1, r0
	str     r1, dsm_sav_rgn_size


	/* Added by Lee sangseok*/
	ldr r1, lgsnap_create
	mov lr, pc
	bx r1

	pop {r0-r12, r15}
	/* skip below this line because we don't want to enter real deep sleep state by Lee sangseok */

	@ r0_tmp_str is temporary store address.
r0_tmp_str:    .word   0

lgsnap_create: .word lgsnap_create_snapshot
	.ltorg 

	
	/*
	*
	*  for secondary CPU context save ##
	*/
	.global	save_context_secondary
save_context_secondary:
	str     r0,r0_tmp                                   /*Temporary store */
	ldr     r0,dsm_sav_rgn_addr                         /*Get state save addr*/
	add	r0,r0,#(SECONDARY_OFFSET)
	str     r1,[r0,#4]                                  /*Save r1*/
	mov     r1,r0                                       /*Get state save addr*/
	ldr     r0,r0_tmp                                   /*Restore r0*/
	str     r0,[r1],#8                                  /*Save r0*/
	stmia   r1!,{r2-r14}                                /*Save r2-r14 (SYS/USR)*/
	mrs     r0,cpsR                                     /*Get cpsR*/
	str     r0,[r1],#4                                  /*Save cpsR*/

	str	r1, r0_tmp				/* save svc status for return */

    @ Save FIQ mode registers and SPSR
    stmia   r1!,{r8-r14}                    /*Save r8-r14 (FIQ)*/
    mrs     r0,SPSR                         /*Get SPSR*/
    str     r0,[r1],#4                      /*Save SPSR*/

    @ Save IRQ mode registers and SPSR
    cps     #MODE_IRQ
    stmia   r1!,{r13-r14}                   /*Save r13-r14 (IRQ)*/
    mrs     r0,SPSR                         /*Get SPSR*/
    str     r0,[r1],#4                      /*Save SPSR*/

    @ Save Abort mode registers and SPSR
    cps     #MODE_ABT
    stmia   r1!,{r13-r14}                   /*Save r13-r14 (Abort)*/
    mrs     r0,SPSR                         /*Get SPSR*/
    str     r0,[r1],#4                      /*Save SPSR*/

    @ Save Supervisor mode registers and SPSR
    cps     #MODE_SVC
    stmia   r1!,{r13-r14}                   /*Save r13-r14 (SVC)*/
    mrs     r0,SPSR                         /*Get SPSR*/
    str     r0,[r1],#4                      /*Save SPSR*/

    @ Save Undefined mode registers and SPSR
    cps     #MODE_UND
    stmia   r1!,{r13-r14}                   /*Save r13-r14 (Undef)*/
    mrs     r0,SPSR                         /*Get SPSR*/
    str     r0,[r1],#4                      /*Save SPSR*/

    @ Return to System mode and enable interrupts
    cpsIE   aif,#MODE_SVC


	@ Disable interrupts, caches and mmu
	cpsid ifa					@ Disable interrupts

    @ Save TLB lockdown register
    mrc     p15,0,r2,c10,c0,0               /*TLB Lockdown*/
    str     r2,[r1],#4                      /*Save*/
    bic     r2,r2,#1                        /*Clear P bit*/
    mcr     p15,0,r2,c10,c0,0               /*Write TLB Lockdown*/

    @ Save CP15 control & fault registers
    mrc     p15,0,r2,c5,c0,0                /*DFSR */
    mrc     p15,0,r3,c5,c0,1                /*IFSR */
    mrc     p15,0,r4,c6,c0,0                /*FAR */
    mrc     p15,0,r5,c6,c0,1                /*IFAR */
    mrc     p15,0,r6,c1,c0,1                /*Auxiliary Control */
    mrc     p15,0,r7,c1,c0,2                /*Coproc Access Control */
    stmia   r1!,{r2-r7}                     /*Save */

	@ Save CP15 thread/processID registers
    mrc     p15,0,r2,c13,c0,2               /*User R/W Thread/PID */
    mrc     p15,0,r3,c13,c0,3               /*User RO Thread/PID */
    mrc     p15,0,r4,c13,c0,4               /*Priv Only Thread/PID */
    stmia   r1!,{r2-r4}                     /*Save */

    @ Save memory system control registers 
    mrc     p15,0,r2,c1,c0,0                /*CR*/
    mrc     p15,0,r3,c2,c0,0                /*TTBR0*/
    mrc     p15,0,r4,c2,c0,1                /*TTBR1*/
    mrc     p15,0,r5,c2,c0,2                /*TTBCR*/
    mrc     p15,0,r6,c3,c0,0                /*daC*/
    mrc     p15,0,r7,c13,c0,0               /*FCSE PID*/
    mrc     p15,0,r8,c13,c0,1               /*Context ID*/
    stmia   r1!,{r2-r8}                     /*Save*/

    mrc     p15,0,r2,c10,c2,0               /*PRRR*/
    mrc     p15,0,r3,c10,c2,1               /*NMRR*/
    mrc     p15,0,r4,c13,c0,2               /*USER R/W thread and process ID*/
    mrc     p15,0,r5,c13,c0,3               /*USER RO thread and process ID*/
    mrc     p15,0,r6,c13,c0,4               /*Privilege only thread and process ID*/

	/*
	 * Normal world don't use VBAR, yw.kim@lge.com
	 * secondary cpu(save)
	 */
#ifdef CONFIG_TRUSTZONE
	stmia   r1!,{r2-r6}
#else
    mrc     p15,0,r7,c12,c0,0               /*Secure or NS vector base address*/
    stmia   r1!,{r2-r7}
#endif

	ldr	r0, =dsm_sav_rgn		
	add	r0,r0,#(SECONDARY_OFFSET)	@ load memory address for saving the CPU1
	sub	r1, r1, r0
	str	r1, dsm_sav_rgn_size_sc

	@ L1 cache flush
	bl	v7_flush_dcache_all
#ifdef CONFIG_TRUSTZONE
	dmb
#endif

	nop
	dsb
	dmb
	isb
	nop
	nop

	ldr	r1, r0_tmp
    ldr     r0,[r1,#-4]!                    /*Load cpsR */
    msr     cpsR_cxsf,r0                    /*Restore cpsR */

    @ Now in svc mode, with enabling of interrupts restored.
    ldmdb   r1,{r0-r14}                     /*Restore r0-r14 (SVC)*/

    @ Return from deep sleep mode entry/exit
    mov     pc,r14

	@ r0_tmp is temporary store address.
r0_tmp:    .word   0
	.ltorg

/* ---------------------------------------------------------------------------------
 * Deep Sleep Mode Exit
 * ---------------------------------------------------------------------------------
 */

	/*
	 * This code assumes that the reset exception handler determines that the reset is 
	 * due to exiting deep sleep mode, and the reset handler then branches to this deep 
	 * sleep mode exit code.
	 *
	 * The deep sleep mode exit code restores all required state in the correct order
	 * (generally the opposite order from that in which it was saved). 
	 *
	 * You must make some modifications to this code as explained by the comments within it.
	 * When all state is restored, the deep sleep mode exit code restores the original cpsR,
	 * thus entering System mode (as shutdown mode entry was called in System mode), and 
	 * returns to the instruction after the the original call to the deep sleep mode entry 
	 * code, using the following instruction:
	 * mov pc,r14
	 * This assumes that the deep sleep mode entry code was called in System mode
	 * using an instruction of the form:
	 * BL dsm_entry

	 * Information about the shutdown mode entry code is given at the start of that
	 * code. 
	*/
	.global  dsm_exit
dsm_exit:
	/*
	 * Assume we are in a privileged mode.
	 * Enter system mode and ensure interrupts are disabled.
	 */
	@ Load the address at the end of the state save memory region
	b get_dsm_addr			@ to get address

return_get_addr:
	ldr     r1, dsm_sav_rgn_size
	add		r1, r1, r0						/* r1 = end address of sdm_sav_rgn */

	/*
	 * Restore Dual input timer registers.
	 * Timer0 and Timer1 register, offset is 0x20.
	 */
	/* local timer */
	ldmdb   r1!,{r2-r3}                     /*Load */
	ldr	r0,=(MPCORE_PTIMER_BASE)
	str	r2,[r0]		/* local timer for CPU0 load reg */
	mov	r3,#0x7		/* should be setting for scheduling */
	str	r3,[r0,#0x8]		/* local timer for CPU0 control reg */
	/* global timer */
	ldmdb   r1!,{r2-r5}                     /*Load */
	ldr 	r0,=(TIMER_BASE)
	str	r2,[r0]							/*timer 0 load reg*/
	str	r3,[r0,#0x8]					/*timer 0 control reg*/
	add	r0,r0,#0x20						/*timer 1 reg base addr*/
	str	r4,[r0]							/*timer 1 load reg*/
	str	r5,[r0,#0x8]					/*timer 1 control reg*/

	/*
	 * Restore Generic Inaterrupt Controller registers.
	 * GIC include distribute interrupt controller and cpu interface.
	 */
	sub	r1,r1,#4

	ldr 	r0,=(MPCORE_GIC_DIST_BASE+GIC_DIST_PRI)
	mov	r3,r0
	add	r0,r0,#0xb0
gic_restore_pri:
	sub	r0,r0,#4
	sub	r1,r1,#4
	ldr	r2,[r1]
	str	r2,[r0]
	cmp	r3, r0
	bne		gic_restore_pri

	ldr	r0,=(MPCORE_GIC_DIST_BASE+GIC_DIST_TARGET)
	mov	r3,r0
	add	r0,r0,#0xb0
gic_restore_target:
	sub	r0,r0,#4
	sub	r1,r1,#4
	ldr	r2,[r1]
	str	r2,[r0]
	cmp	r3, r0
	bne	gic_restore_target

	ldr	r0,=(MPCORE_GIC_DIST_BASE+GIC_DIST_ENABLE_SET)
	ldr	r2,=0x2000ffff
	str	r2,[r0]
	ldr	r2,=0x05fa0041
	str	r2,[r0,#4]

	ldr	r0,=(MPCORE_GIC_DIST_BASE+GIC_DIST_CTRL)
	ldr     r2,[r1]
	str     r2,[r0]

	sub 	r1,r1,#4
	ldr 	r0,=(MPCORE_GIC_CTRL_BASE+GIC_CPU_CTRL)
	ldr     r3,[r1]
	sub	r1,r1,#4
	ldr	r2,[r1]
	str	r3,[r0,#8]
	str     r2,[r0]

	ldr 	r0,=(MPCORE_GIC_DIST_BASE+GIC_DIST_ENABLE_SET)
	add	r0,r0,#4
	ldmdb	r1!,{r2-r3}
	stmia	r0!,{r2-r3}	

	/*
	 * Note: we do not save and restore the Cache Lockdown registers.
	 * Powering down the cache RAMs in shutdown mode loses the
	 * contents of any locked cache ways, so there is no point
	 * locking ways that are now empty.
	 * If you use the cache lockdown features, there are two methods
	 * to restore locked cache ways:
	 * 1) If the locked ways and their contents are static, you can
	 * simply repeat the code that you used to fill and lock the
	 * cache ways.
	 * 2) If cache way locking or the addresses that are locked into
	 * cache ways vary, it is possible to identify the addresses
	 * of lines locked in a cache way, save these addresses, then
	 * refill the cache lines and relock them on exiting shutdown
	 * mode.  The procedure is described in the shutdown mode
	 * documentation. 
	 */

	/*
	 * Restore memory system control registers.
	 * ARM1136 rev1 has two extra memory system registers.
	 */
	ldr		r0,virt_mmu_enabled

	mrc     p15,0,r10,c1,c0,0		@ read ctrl reg
	bic		r10, r10, #(1<<12)		@ disable instruction cache
	mrc		p15,0,r10,c1,c0,0

	mov    	r10, #0
	mcr    	p15,0,r10,c7,c5,0		@ invalidate cache

	/* L1 dcache invalidate */
	mov r13,pc
	add r13,r13,#4
	b L1_dcache_invalidate

	/*
	 * Normal world don't use VBAR, yw.kim@lge.com
	 * primary cpu(restore)
	 */
#ifdef CONFIG_TRUSTZONE
	ldmdb	r1!,{r2-r6}			/*LOAD*/
#else
	ldmdb	r1!,{r2-r7}			/*LOAD*/	
	mcr	p15,0,r7,c12,c0,0		/*Secure or NS vector base address*/
#endif
	mcr	p15,0,r2,c10,c2,0		/*PRRR*/
	mcr	p15,0,r3,c10,c2,1		/*NMRR*/
	mcr	p15,0,r4,c13,c0,2		/*USER R/W thread and process ID*/
	mcr	p15,0,r5,c13,c0,3		/*USER RO thread and process ID*/
	mcr	p15,0,r6,c13,c0,4		/*Privilege only thread and process ID*/

	ldmdb   r1!,{r2-r8}			/* Load*/
	mcr     p15,0,r8,c13,c0,1		/* Context ID*/
	mcr     p15,0,r7,c13,c0,0		/* FCSE PID*/
	mcr     p15,0,r6,c3,c0,0 		/* Domain Access Control */
	mcr     p15,0,r5,c2,c0,2 		/* TTBCR*/
	mcr     p15,0,r4,c2,c0,1 		/* TTBR1*/
	mcr     p15,0,r3,c2,c0,0 		/* TTBR0*/

	mov	r4,#0
	mcr 	p15, 0, r4, c8, c7, 0   	@ flush I,D TLBs
	mcr	p15, 0, r4, c7, c5, 4		@ Flush prefetch buffer
	mcr	p15, 0, r4, c7, c5, 6		@ Invalidate branch predictor array
	mcr	p15, 0, r4, c8, c5, 0		@ Invalidate instruction TLB
	mcr	p15, 0, r4, c8, c6, 0		@ Invalidate data TLB

	b	dsm_exit_turn_on_mmu
	
	.align 5
dsm_exit_turn_on_mmu:	
	mcr		p15,0,r2,c1,c0,0		/* Control */
	mov	pc,r0

	.globl mmu_enabled
mmu_enabled:
	add r1, r1, #PAGE_OFFSET

	@ Restore console(uart0) registers
	ldmdb   r1!,{r2-r5}                     /*Load */
	ldr     r0,=CONSOLE_BASE		/*UART0 base address*/
	str     r2,[r0,#0x24]                   /*IBRD*/
	str     r3,[r0,#0x28]                   /*FBRD*/
	str     r4,[r0,#0x2C]                   /*LCRH*/
	str     r5,[r0,#0x30]                   /*CR*/
	
#ifndef CONFIG_TRUSTZONE
	@ Restore lockdown region of TLB
	ldmdb   r1!,{r2-r4}
	sub     r0,r0,#1 
	mcr     p15,5,r0,c15,c4,4               /*Write lockdown entry 0*/
	mcr     p15,5,r2,c15,c7,2              /*Write Main TLB Attr*/
	mcr     p15,5,r3,c15,c6,2              /*Write Main TLB PA*/
	mcr     p15,5,r4,c15,c5,2              /*Write Main TLB VA*/
#endif

	/*
	 * Restore CP15 control & fault registers
	 * ARM1136 rev1 has three extra thread/process ID registers
	 */
	ldmdb   r1!,{r2-r4}                     /*Load*/
	mcr     p15,0,r4,c13,c0,4               /*Priv Only Thread/PID*/
	mcr     p15,0,r3,c13,c0,3               /*User RO Thread/PID*/
	mcr     p15,0,r2,c13,c0,2               /*User R/W Thread/PID*/


	ldmdb   r1!,{r2-r7}                     /*Load*/
	mcr     p15,0,r7,c1,c0,2                /*Coproc Access Control*/
	mcr     p15,0,r6,c1,c0,1                /*Auxiliary Control*/
	mcr     p15,0,r5,c6,c0,1                /*IFAR*/
	mcr     p15,0,r4,c6,c0,0                /*FAR*/
	mcr     p15,0,r3,c5,c0,1                /*IFSR*/
	mcr     p15,0,r2,c5,c0,0                /*DFSR*/

	@ Restore TLB lockdown register
	ldr     r2,[r1,#-4]!                    /*Load*/
	mcr     p15,0,r2,c10,c0,0               /*TLB Lockdown*/


	@ Restore SCU configuration 
	ldmdb	r1!,{r2,r3}
	ldr	r0,=__MMIO_P2V(MPCORE_SCU_BASE)
	str	r2,[r0]			@ no meaning now 'FIXME'
	@str	r3,[r0,#0x4]

	/*
	 * Disable interrupts while we restore mode SPSRs and regs
	 * Also change to Undefined mode for next section 
	 */
	cpsid   if,#MODE_UND

	@ Restore Undefined mode SPSR and registers
	ldr     r0,[r1,#-4]!                    /*Load SPSR*/
	msr     SPSR_cxsf,r0                    /*Restore SPSR*/
	ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (UND)*/

	@ Restore Supervisor mode SPSR and registers
	cps     #MODE_SYS
	ldr     r0,[r1,#-4]!                    /*Load SPSR*/
	msr     SPSR_cxsf,r0                    /*Restore SPSR*/
	ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (SYS/USR)*/

	@ Restore Abort mode SPSR and registers
	cps     #MODE_ABT
	ldr     r0,[r1,#-4]!                    /*Load SPSR*/
	msr     SPSR_cxsf,r0                    /*Restore SPSR*/
	ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (Abt)*/

	@ Restore IRQ mode SPSR and registers
	cps     #MODE_IRQ
	ldr     r0,[r1,#-4]!                    /*Load SPSR*/
	msr     SPSR_cxsf,r0                    /*Restore SPSR*/
	ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (IRQ)*/

	@ Restore FIQ mode SPSR and registers
	cps     #MODE_FIQ
	ldr     r0,[r1,#-4]!                    /*Load SPSR*/
	msr     SPSR_cxsf,r0                    /*Restore SPSR*/
	ldmdb   r1!,{r8-r14}                    /*Restore r8-r14 (FIQ)*/
	
	cps     #MODE_SVC
	/*
	 * Restore cpsR (puts us into System mode) and restore
	 * general purpose registers (SVC) 
	 */
	ldr     r0,[r1,#-4]!                    /*Load cpsR */
	msr     cpsR_cxsf,r0                    /*Restore cpsR */


	@ Now in svc mode, with enabling of interrupts restored.
	ldmdb   r1,{r0-r14}                     /*Restore r0-r14 (SVC)*/

	@ Return from deep sleep mode entry/exit
	mov     pc,r14



	/*
	* restore secondary CPU context $$
	*/
	.global  secondary_cpu
secondary_cpu:
    adr     r0, dsm_sav_rgn
	add	r0 ,r0, #(SECONDARY_OFFSET)
    ldr     r1, dsm_sav_rgn_size_sc
    add     r1, r1, r0                      /* r1 = end address of sdm_sav_rgn */
	

	ldr	r0, secondary_cpu_virt_mmu_enabled

	mrc     p15,0,r10,c1,c0,0               @ read ctrl reg
    bic     r10, r10, #(1<<12)              @ disable instruction cache
    mrc     p15,0,r10,c1,c0,0

    mov     r10, #0
    mcr     p15,0,r10,c7,c5,0               @ invalidate cache

	/* L1 dcache invalidate */
	mov r13,pc
	add r13,r13,#4
	b L1_dcache_invalidate

	/*
     * Restore Generic Inaterrupt Controller registers.
     * GIC include distribute interrupt controller and cpu interface.
     */

	/*
	 * Normal world don't use VBAR, yw.kim@lge.com
	 * secondary cpu(restore)
	 */
#ifdef CONFIG_TRUSTZONE
	ldmdb   r1!,{r2-r6}                     /*LOAD*/
#else
	ldmdb   r1!,{r2-r7}                     /*LOAD*/
	mcr     p15,0,r7,c12,c0,0               /*Secure or NS vector base address*/
#endif
	mcr     p15,0,r2,c10,c2,0               /*PRRR*/
    mcr     p15,0,r3,c10,c2,1               /*NMRR*/
    mcr     p15,0,r4,c13,c0,2               /*USER R/W thread and process ID*/
    mcr     p15,0,r5,c13,c0,3               /*USER RO thread and process ID*/
    mcr     p15,0,r6,c13,c0,4               /*Privilege only thread and process ID*/
    
    ldmdb   r1!,{r2-r8}                     /* Load*/
    mcr     p15,0,r8,c13,c0,1               /* Context ID*/
    mcr     p15,0,r7,c13,c0,0               /* FCSE PID*/
    mcr     p15,0,r6,c3,c0,0                /* Domain Access Control */
    mcr     p15,0,r5,c2,c0,2                /* TTBCR*/
    mcr     p15,0,r4,c2,c0,1                /* TTBR1*/
    mcr     p15,0,r3,c2,c0,0                /* TTBR0*/

    mov     r4,#0
    mcr     p15, 0, r4, c8, c7, 0           @ flush I,D TLBs
    mcr     p15, 0, r4, c7, c5, 4           @ Flush prefetch buffer
    mcr     p15, 0, r4, c7, c5, 6           @ Invalidate branch predictor array
    mcr     p15, 0, r4, c8, c5, 0           @ Invalidate instruction TLB
    mcr     p15, 0, r4, c8, c6, 0           @ Invalidate data TLB

	b	secondary_cpu_turn_on_mmu

	.align 5
secondary_cpu_turn_on_mmu:
	/* from here, CPU will run DRAM not SRAM*/
	mcr	p15,0,r2,c1,c0,0		/* MMU ON */
	mov	pc,r0


	.globl	secondary_cpu_mmu_enabled
secondary_cpu_mmu_enabled:
	add r1, r1, #PAGE_OFFSET

    /*
     * Restore CP15 control & fault registers
     * ARM1136 rev1 has three extra thread/process ID registers
     */
    ldmdb   r1!,{r2-r4}                     /*Load*/
    mcr     p15,0,r4,c13,c0,4               /*Priv Only Thread/PID*/
    mcr     p15,0,r3,c13,c0,3               /*User RO Thread/PID*/
    mcr     p15,0,r2,c13,c0,2               /*User R/W Thread/PID*/

    ldmdb   r1!,{r2-r7}                     /*Load*/
    mcr     p15,0,r7,c1,c0,2                /*Coproc Access Control*/
    mcr     p15,0,r6,c1,c0,1                /*Auxiliary Control*/
    mcr     p15,0,r5,c6,c0,1                /*IFAR*/
    mcr     p15,0,r4,c6,c0,0                /*FAR*/
    mcr     p15,0,r3,c5,c0,1                /*IFSR*/
    mcr     p15,0,r2,c5,c0,0                /*DFSR*/

    @ Restore TLB lockdown register
    ldr     r2,[r1,#-4]!                    /*Load*/
    mcr     p15,0,r2,c10,c0,0               /*TLB Lockdown*/

	/*
     * Disable interrupts while we restore mode SPSRs and regs
     * Also change to Undefined mode for next section
     */
    cpsid   if,#MODE_UND

    @ Restore Undefined mode SPSR and registers
    ldr     r0,[r1,#-4]!                    /*Load SPSR*/
    msr     SPSR_cxsf,r0                    /*Restore SPSR*/
    ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (UND)*/

    @ Restore Supervisor mode SPSR and registers
    cps     #MODE_SVC
    ldr     r0,[r1,#-4]!                    /*Load SPSR*/
    msr     SPSR_cxsf,r0                    /*Restore SPSR*/
    ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (SVC)*/

    @ Restore Abort mode SPSR and registers
    cps     #MODE_ABT
    ldr     r0,[r1,#-4]!                    /*Load SPSR*/
    msr     SPSR_cxsf,r0                    /*Restore SPSR*/
    ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (Abt)*/

    @ Restore IRQ mode SPSR and registers
    cps     #MODE_IRQ
    ldr     r0,[r1,#-4]!                    /*Load SPSR*/
    msr     SPSR_cxsf,r0                    /*Restore SPSR*/
    ldmdb   r1!,{r13-r14}                   /*Restore r13-r14 (IRQ)*/

    @ Restore FIQ mode SPSR and registers
    cps     #MODE_FIQ
    ldr     r0,[r1,#-4]!                    /*Load SPSR*/
    msr     SPSR_cxsf,r0                    /*Restore SPSR*/
    ldmdb   r1!,{r8-r14}                    /*Restore r8-r14 (FIQ)*/

    cps     #MODE_SVC
    /*
     * Restore cpsR (puts us into System mode) and restore
     * general purpose registers (SVC)
     */
    ldr     r0,[r1,#-4]!                    /*Load cpsR */
    msr     cpsR_cxsf,r0                    /*Restore cpsR */

    @ Now in svc mode, with enabling of interrupts restored.
    ldmdb   r1,{r0-r14}                     /*Restore r0-r14 (SVC)*/

    @ Return from deep sleep mode entry/exit
    mov     pc,r14


L1_dcache_invalidate:
	mrc             p15, 1, r4, c0, c0, 1           @ read clidr
    ands    r3, r4, #0x7000000                      @ extract loc from clidr
    mov             r3, r3, lsr #23                 @ left align loc bit field
    beq     finished_inv                          @ if loc is 0, then no need to clean
    mov             r10, #0                         @ start clean at cache level 0 (in r10)
loop1_inv:
    add             r9, r10, r10, lsr #1            @ work out 3x current cache level
    mov             r12, r4, lsr r9                 @ extract cache type bits from clidr
    and             r12, r12, #7                    @ mask of the bits for current cache only
    cmp             r12, #2                         @ see what cache we have at this level
    blt             skip_inv                      @ skip if no cache, or just i-cache
    mcr             p15, 2, r10, c0, c0, 0          @ select current cache level in cssr
    isb
    mrc             p15, 1, r12, c0, c0, 0          @ read the new csidr
    and     r9, r12, #7                             @ extract the length of the cache lines
    add     r9, r9, #4                              @ add 4 (line length offset)
    ldr             r6, =0x3ff
    ands    r6, r6, r12, lsr #3                     @ find maximum number on the way size
    clz             r5, r6                          @ find bit position of way size increment
    ldr             r7, =0x7fff
    ands    r7, r7, r12, lsr #13            	@ extract max number of the index size
loop2_inv:
    mov             r8, r6                          @ create working copy of max way size
loop3_inv:
    orr             r11, r10, r8, lsl r5            @ factor way and cache number into r11
    orr             r11, r11, r7, lsl r9            @ factor index number into r11
    mcr             p15, 0, r11, c7, c6, 2         @ invalidate/clean/both by set/way
    subs    r8, r8, #1                              @ decrement the way
    bge             loop3_inv
    subs    r7, r7, #1                              @ decrement the index
    bge             loop2_inv
skip_inv:
    add     r10, r10, #2                            @ increment cache number
    cmp             r3, r10
    bgt             loop1_inv
finished_inv:
    mov             r10, #0
    mcr             p15, 0, r10, c7, c10, 4         @ drain write buffer

    mcr             p15, 0, r10, c8, c7, 0          @ invalidate I + D TLBs
    mcr             p15, 0, r10, c2, c0, 2          @ TTB control register
	mov	pc,r13


get_dsm_addr:
	adr	r0, dsm_sav_rgn
	b return_get_addr


	/*
	 * dsm_sav_rgn_size label have end address of state store area.
	 */
	.globl page_offset
page_offset:		.long	0
	.globl virt_mmu_enabled
virt_mmu_enabled:	.long	mmu_enabled
	.globl secondary_cpu_virt_mmu_enabled
secondary_cpu_virt_mmu_enabled:	.long	secondary_cpu_mmu_enabled
dsm_sav_rgn_addr:	.long	dsm_sav_rgn
dsm_sav_rgn_size:	.word   0
dsm_sav_rgn_size_sc:	.word	0
	.ltorg

/* ---------------------------------------------------------------------------------
 * Space for state saving
 * ---------------------------------------------------------------------------------
 */

	/*
	 * Reserve 1KB Space for saving deep sleep mode state
	 * You will probably want to change this to a fixed address in your memory map. 
	 * Deep Sleep Mode SToRe ReGioN
	 */
	.align 4
	.globl dsm_sav_rgn
dsm_sav_rgn:	.space		0x800	/*0x000 ~ 0x3ff : CPU0 , 0x400 ~ 0x7ff : CPU1*/
	.globl dsm_exit_end
dsm_exit_end:

/* -------------------------------------------------------------------------------------
 * End of code
 * -------------------------------------------------------------------------------------
 */
.end

