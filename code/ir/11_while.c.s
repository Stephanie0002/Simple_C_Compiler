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
	movl	$0, b(%rip)
	movl	$3, %eax
	.p2align	4, 0x90
.LBB0_2:                                # %loopend
                                        # =>This Inner Loop Header: Depth=1
	movl	%eax, a(%rip)
	testl	%eax, %eax
	jle	.LBB0_3
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_2 Depth=1
	movl	a(%rip), %eax
	addl	%eax, b(%rip)
	decl	%eax
	jmp	.LBB0_2
.LBB0_3:                                # %afterloop
	movl	b(%rip), %eax
	retq
                                        # -- End function
	.bss
	.globl	a                               # @a
	.p2align	2
a:
	.long	0                               # 0x0

	.globl	b                               # @b
	.p2align	2
b:
	.long	0                               # 0x0

