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
	movl	$4, %eax
	retq
                                        # -- End function
	.section	.rdata,"dr"
	.globl	x                               # @x
	.p2align	2
x:
	.long	4                               # 0x4

