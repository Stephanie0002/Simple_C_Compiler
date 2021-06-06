	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 EightWhile;
	.scl	2;
	.type	32;
	.endef
	.globl	EightWhile                      # -- Begin function EightWhile
	.p2align	4, 0x90
EightWhile:                             # @EightWhile
# %bb.0:                                # %entry
	movl	$5, %eax
	movl	$6, %r8d
	movl	$7, %edx
	movl	$10, %ecx
	jmp	.LBB0_23
	.p2align	4, 0x90
.LBB0_22:                               # %afterloop67
                                        #   in Loop: Header=BB0_23 Depth=1
	addl	$-2, %r8d
.LBB0_23:                               # %loopend70
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_21 Depth 2
                                        #       Child Loop BB0_19 Depth 3
                                        #         Child Loop BB0_17 Depth 4
                                        #           Child Loop BB0_15 Depth 5
                                        #             Child Loop BB0_13 Depth 6
                                        #               Child Loop BB0_11 Depth 7
                                        #                 Child Loop BB0_8 Depth 8
	cmpl	$20, %eax
	jge	.LBB0_24
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_23 Depth=1
	addl	$3, %eax
	jmp	.LBB0_21
	.p2align	4, 0x90
.LBB0_20:                               # %afterloop59
                                        #   in Loop: Header=BB0_21 Depth=2
	incl	%edx
.LBB0_21:                               # %loopend62
                                        #   Parent Loop BB0_23 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_19 Depth 3
                                        #         Child Loop BB0_17 Depth 4
                                        #           Child Loop BB0_15 Depth 5
                                        #             Child Loop BB0_13 Depth 6
                                        #               Child Loop BB0_11 Depth 7
                                        #                 Child Loop BB0_8 Depth 8
	cmpl	$10, %r8d
	jge	.LBB0_22
# %bb.2:                                # %loop2
                                        #   in Loop: Header=BB0_21 Depth=2
	incl	%r8d
	jmp	.LBB0_19
	.p2align	4, 0x90
.LBB0_18:                               # %afterloop51
                                        #   in Loop: Header=BB0_19 Depth=3
	decl	%ecx
.LBB0_19:                               # %loopend54
                                        #   Parent Loop BB0_23 Depth=1
                                        #     Parent Loop BB0_21 Depth=2
                                        # =>    This Loop Header: Depth=3
                                        #         Child Loop BB0_17 Depth 4
                                        #           Child Loop BB0_15 Depth 5
                                        #             Child Loop BB0_13 Depth 6
                                        #               Child Loop BB0_11 Depth 7
                                        #                 Child Loop BB0_8 Depth 8
	cmpl	$7, %edx
	jne	.LBB0_20
# %bb.3:                                # %loop5
                                        #   in Loop: Header=BB0_19 Depth=3
	decl	%edx
	jmp	.LBB0_17
	.p2align	4, 0x90
.LBB0_16:                               # %afterloop43
                                        #   in Loop: Header=BB0_17 Depth=4
	incl	e(%rip)
.LBB0_17:                               # %loopend46
                                        #   Parent Loop BB0_23 Depth=1
                                        #     Parent Loop BB0_21 Depth=2
                                        #       Parent Loop BB0_19 Depth=3
                                        # =>      This Loop Header: Depth=4
                                        #           Child Loop BB0_15 Depth 5
                                        #             Child Loop BB0_13 Depth 6
                                        #               Child Loop BB0_11 Depth 7
                                        #                 Child Loop BB0_8 Depth 8
	cmpl	$20, %ecx
	jge	.LBB0_18
# %bb.4:                                # %loop8
                                        #   in Loop: Header=BB0_17 Depth=4
	addl	$3, %ecx
	jmp	.LBB0_15
	.p2align	4, 0x90
.LBB0_14:                               # %afterloop35
                                        #   in Loop: Header=BB0_15 Depth=5
	incl	f(%rip)
.LBB0_15:                               # %loopend38
                                        #   Parent Loop BB0_23 Depth=1
                                        #     Parent Loop BB0_21 Depth=2
                                        #       Parent Loop BB0_19 Depth=3
                                        #         Parent Loop BB0_17 Depth=4
                                        # =>        This Loop Header: Depth=5
                                        #             Child Loop BB0_13 Depth 6
                                        #               Child Loop BB0_11 Depth 7
                                        #                 Child Loop BB0_8 Depth 8
	cmpl	$1, e(%rip)
	jle	.LBB0_16
# %bb.5:                                # %loop11
                                        #   in Loop: Header=BB0_15 Depth=5
	decl	e(%rip)
	jmp	.LBB0_13
	.p2align	4, 0x90
.LBB0_12:                               # %afterloop27
                                        #   in Loop: Header=BB0_13 Depth=6
	addl	$-8, g(%rip)
.LBB0_13:                               # %loopend30
                                        #   Parent Loop BB0_23 Depth=1
                                        #     Parent Loop BB0_21 Depth=2
                                        #       Parent Loop BB0_19 Depth=3
                                        #         Parent Loop BB0_17 Depth=4
                                        #           Parent Loop BB0_15 Depth=5
                                        # =>          This Loop Header: Depth=6
                                        #               Child Loop BB0_11 Depth 7
                                        #                 Child Loop BB0_8 Depth 8
	cmpl	$2, f(%rip)
	jle	.LBB0_14
# %bb.6:                                # %loop13
                                        #   in Loop: Header=BB0_13 Depth=6
	addl	$-2, f(%rip)
	jmp	.LBB0_11
	.p2align	4, 0x90
.LBB0_10:                               # %afterloop
                                        #   in Loop: Header=BB0_11 Depth=7
	decl	h(%rip)
.LBB0_11:                               # %loopend22
                                        #   Parent Loop BB0_23 Depth=1
                                        #     Parent Loop BB0_21 Depth=2
                                        #       Parent Loop BB0_19 Depth=3
                                        #         Parent Loop BB0_17 Depth=4
                                        #           Parent Loop BB0_15 Depth=5
                                        #             Parent Loop BB0_13 Depth=6
                                        # =>            This Loop Header: Depth=7
                                        #                 Child Loop BB0_8 Depth 8
	cmpl	$3, g(%rip)
	jge	.LBB0_12
# %bb.7:                                # %loop15
                                        #   in Loop: Header=BB0_11 Depth=7
	addl	$10, g(%rip)
	cmpl	$10, h(%rip)
	jge	.LBB0_10
	.p2align	4, 0x90
.LBB0_8:                                # %loop17
                                        #   Parent Loop BB0_23 Depth=1
                                        #     Parent Loop BB0_21 Depth=2
                                        #       Parent Loop BB0_19 Depth=3
                                        #         Parent Loop BB0_17 Depth=4
                                        #           Parent Loop BB0_15 Depth=5
                                        #             Parent Loop BB0_13 Depth=6
                                        #               Parent Loop BB0_11 Depth=7
                                        # =>              This Inner Loop Header: Depth=8
	addl	$8, h(%rip)
	cmpl	$10, h(%rip)
	jl	.LBB0_8
	jmp	.LBB0_10
.LBB0_24:                               # %afterloop75
	addl	%ecx, %r8d
	addl	%r8d, %eax
	addl	%edx, %eax
	addl	e(%rip), %ecx
	subl	g(%rip), %ecx
	addl	h(%rip), %ecx
	subl	%ecx, %eax
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
	movl	$1, g(%rip)
	movl	$2, h(%rip)
	movl	$4, e(%rip)
	movl	$6, f(%rip)
	callq	EightWhile
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.bss
	.globl	g                               # @g
	.p2align	2
g:
	.long	0                               # 0x0

	.globl	h                               # @h
	.p2align	2
h:
	.long	0                               # 0x0

	.globl	f                               # @f
	.p2align	2
f:
	.long	0                               # 0x0

	.globl	e                               # @e
	.p2align	2
e:
	.long	0                               # 0x0

