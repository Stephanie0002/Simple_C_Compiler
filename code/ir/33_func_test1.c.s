	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 myFunc;
	.scl	2;
	.type	32;
	.endef
	.globl	myFunc                          # -- Begin function myFunc
	.p2align	4, 0x90
myFunc:                                 # @myFunc
# %bb.0:                                # %entry
	movl	%edx, %eax
	testl	%eax, %eax
	jle	.LBB0_3
	.p2align	4, 0x90
.LBB0_1:                                # %loop
                                        # =>This Inner Loop Header: Depth=1
	decl	%eax
	testl	%eax, %eax
	jg	.LBB0_1
.LBB0_3:                                # %afterloop
	addl	$2, %eax
	retq
                                        # -- End function
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
	movl	$3, a(%rip)
	movl	$1, %ecx
	movl	$2, %edx
	movl	$1, %r8d
	callq	myFunc
	addl	a(%rip), %eax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.bss
	.globl	a                               # @a
	.p2align	2
a:
	.long	0                               # 0x0

