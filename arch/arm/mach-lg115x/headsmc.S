	.global __smc
__smc:
	push	{ r4-r7 }
	ldm	r0, { r0-r7 }
	isb
	dsb
	smc	#0
	pop	{ r4-r7 }
	mov	pc, lr

