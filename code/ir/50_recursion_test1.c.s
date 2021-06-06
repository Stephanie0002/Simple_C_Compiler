	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 fact;
	.scl	2;
	.type	32;
	.endef
	.globl	fact                            # -- Begin function fact
	.p2align	4, 0x90
fact:                                   # @fact
.seh_proc fact
# %bb.0:                                # %entry
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	testl	%ecx, %ecx
	je	.LBB0_1
# %bb.3:                                # %ifcont
	movl	%ecx, %esi
	leal	-1(%rsi), %ecx
	callq	fact
	imull	%esi, %eax
	jmp	.LBB0_2
.LBB0_1:                                # %then
	movl	$1, %eax
.LBB0_2:                                # %then
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
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
	movl	$4, %ecx
	callq	fact
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
