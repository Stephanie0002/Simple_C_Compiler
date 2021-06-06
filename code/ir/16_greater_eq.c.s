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
	xorl	%eax, %eax
	leaq	s(%rip), %rcx
	.p2align	4, 0x90
.LBB0_2:                                # %loopend
                                        # =>This Inner Loop Header: Depth=1
	movslq	%eax, %rdx
	movl	(%rcx,%rdx,4), %edx
	cmpl	a(%rip), %edx
	jl	.LBB0_3
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_2 Depth=1
	incl	%eax
	jmp	.LBB0_2
.LBB0_3:                                # %afterloop
	retq
                                        # -- End function
	.data
	.globl	a                               # @a
	.p2align	2
a:
	.long	5                               # 0x5

	.globl	s                               # @s
	.p2align	4
s:
	.long	9                               # 0x9
	.long	8                               # 0x8
	.long	7                               # 0x7
	.long	6                               # 0x6
	.long	5                               # 0x5
	.long	4                               # 0x4
	.long	3                               # 0x3
	.long	2                               # 0x2
	.long	1                               # 0x1
	.long	0                               # 0x0

