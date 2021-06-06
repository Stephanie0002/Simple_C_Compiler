	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 ififElse;
	.scl	2;
	.type	32;
	.endef
	.globl	ififElse                        # -- Begin function ififElse
	.p2align	4, 0x90
ififElse:                               # @ififElse
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
	callq	ififElse
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
