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
# %bb.0:                                # %entry
	movl	$10, %eax
	cmpl	$6, %eax
	jl	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # %then
                                        # =>This Inner Loop Header: Depth=1
	decl	%eax
	cmpl	$6, %eax
	jge	.LBB0_2
.LBB0_3:                                # %ifcont
	retq
                                        # -- End function
