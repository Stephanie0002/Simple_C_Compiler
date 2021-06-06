	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	getint
	movl	%eax, a(%rip)
	callq	getint
	movl	%eax, a+4(%rip)
	callq	getint
	movl	%eax, a+8(%rip)
	callq	getint
	movl	%eax, a+12(%rip)
	callq	getint
	movl	%eax, a+16(%rip)
	xorl	%eax, %eax
	movl	$4, %ecx
	leaq	a(%rip), %rdx
	cmpl	$1, %ecx
	jle	.LBB0_3
	.p2align	4, 0x90
.LBB0_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	addl	(%rdx,%rcx,4), %eax
	decq	%rcx
	cmpl	$1, %ecx
	jg	.LBB0_1
.LBB0_3:                                # %afterloop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.bss
	.globl	a                               # @a
	.p2align	4
a:
	.zero	20

