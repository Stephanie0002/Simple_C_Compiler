	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 doubleWhile;
	.scl	2;
	.type	32;
	.endef
	.globl	doubleWhile                     # -- Begin function doubleWhile
	.p2align	4, 0x90
doubleWhile:                            # @doubleWhile
# %bb.0:                                # %entry
	movl	$5, %ecx
	movl	$7, %eax
	jmp	.LBB0_5
	.p2align	4, 0x90
.LBB0_4:                                # %afterloop
                                        #   in Loop: Header=BB0_5 Depth=1
	addl	$-100, %eax
.LBB0_5:                                # %loopend8
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_2 Depth 2
	cmpl	$100, %ecx
	jge	.LBB0_6
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_5 Depth=1
	addl	$30, %ecx
	cmpl	$100, %eax
	jge	.LBB0_4
	.p2align	4, 0x90
.LBB0_2:                                # %loop2
                                        #   Parent Loop BB0_5 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	addl	$6, %eax
	cmpl	$100, %eax
	jl	.LBB0_2
	jmp	.LBB0_4
.LBB0_6:                                # %afterloop13
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
	callq	doubleWhile
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
