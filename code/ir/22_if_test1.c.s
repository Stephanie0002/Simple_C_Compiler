	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 ifElse;
	.scl	2;
	.type	32;
	.endef
	.globl	ifElse                          # -- Begin function ifElse
	.p2align	4, 0x90
ifElse:                                 # @ifElse
# %bb.0:                                # %entry
	movl	$25, %eax
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
	callq	ifElse
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
