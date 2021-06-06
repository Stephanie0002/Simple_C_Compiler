	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 FourWhile;
	.scl	2;
	.type	32;
	.endef
	.globl	FourWhile                       # -- Begin function FourWhile
	.p2align	4, 0x90
FourWhile:                              # @FourWhile
# %bb.0:                                # %entry
	movl	$5, %eax
	movl	$6, %r8d
	movl	$7, %ecx
	movl	$10, %edx
	jmp	.LBB0_11
	.p2align	4, 0x90
.LBB0_10:                               # %afterloop27
                                        #   in Loop: Header=BB0_11 Depth=1
	addl	$-2, %r8d
.LBB0_11:                               # %loopend30
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_9 Depth 2
                                        #       Child Loop BB0_7 Depth 3
                                        #         Child Loop BB0_4 Depth 4
	cmpl	$20, %eax
	jge	.LBB0_12
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_11 Depth=1
	addl	$3, %eax
	jmp	.LBB0_9
	.p2align	4, 0x90
.LBB0_8:                                # %afterloop19
                                        #   in Loop: Header=BB0_9 Depth=2
	incl	%ecx
.LBB0_9:                                # %loopend22
                                        #   Parent Loop BB0_11 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_7 Depth 3
                                        #         Child Loop BB0_4 Depth 4
	cmpl	$10, %r8d
	jge	.LBB0_10
# %bb.2:                                # %loop2
                                        #   in Loop: Header=BB0_9 Depth=2
	incl	%r8d
	jmp	.LBB0_7
	.p2align	4, 0x90
.LBB0_6:                                # %afterloop
                                        #   in Loop: Header=BB0_7 Depth=3
	decl	%edx
.LBB0_7:                                # %loopend14
                                        #   Parent Loop BB0_11 Depth=1
                                        #     Parent Loop BB0_9 Depth=2
                                        # =>    This Loop Header: Depth=3
                                        #         Child Loop BB0_4 Depth 4
	cmpl	$7, %ecx
	jne	.LBB0_8
# %bb.3:                                # %loop5
                                        #   in Loop: Header=BB0_7 Depth=3
	decl	%ecx
	cmpl	$20, %edx
	jge	.LBB0_6
	.p2align	4, 0x90
.LBB0_4:                                # %loop8
                                        #   Parent Loop BB0_11 Depth=1
                                        #     Parent Loop BB0_9 Depth=2
                                        #       Parent Loop BB0_7 Depth=3
                                        # =>      This Inner Loop Header: Depth=4
	addl	$3, %edx
	cmpl	$20, %edx
	jl	.LBB0_4
	jmp	.LBB0_6
.LBB0_12:                               # %afterloop35
	addl	%edx, %r8d
	addl	%r8d, %eax
	addl	%ecx, %eax
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
	callq	FourWhile
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
