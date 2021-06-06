	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 ifWhile;
	.scl	2;
	.type	32;
	.endef
	.globl	ifWhile                         # -- Begin function ifWhile
	.p2align	4, 0x90
ifWhile:                                # @ifWhile
# %bb.0:                                # %entry
	xorl	%ecx, %ecx
	movl	$3, %eax
	cmpl	$5, %ecx
	jge	.LBB0_3
	.p2align	4, 0x90
.LBB0_1:                                # %loop8
                                        # =>This Inner Loop Header: Depth=1
	addl	%eax, %eax
	incl	%ecx
	cmpl	$5, %ecx
	jl	.LBB0_1
.LBB0_3:                                # %ifcont
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
	callq	ifWhile
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
