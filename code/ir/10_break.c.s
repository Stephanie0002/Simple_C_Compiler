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
	.p2align	4, 0x90
.LBB0_2:                                # %loopend
                                        # =>This Inner Loop Header: Depth=1
	testl	%eax, %eax
	jle	.LBB0_3
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_2 Depth=1
	decl	%eax
	cmpl	$5, %eax
	jne	.LBB0_2
.LBB0_3:                                # %afterloop
	retq
                                        # -- End function
