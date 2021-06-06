	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 deepWhileBr;
	.scl	2;
	.type	32;
	.endef
	.globl	deepWhileBr                     # -- Begin function deepWhileBr
	.p2align	4, 0x90
deepWhileBr:                            # @deepWhileBr
.seh_proc deepWhileBr
# %bb.0:                                # %entry
	pushq	%rbp
	.seh_pushreg %rbp
	movq	%rsp, %rbp
	.seh_setframe %rbp, 0
	.seh_endprologue
                                        # kill: def $ecx killed $ecx def $rcx
	addl	%edx, %ecx
	.p2align	4, 0x90
.LBB0_3:                                # %loopend
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$75, %ecx
	jge	.LBB0_4
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_3 Depth=1
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rdx
	movl	$42, (%rdx)
	addl	$42, %ecx
	cmpl	$100, %ecx
	jl	.LBB0_3
# %bb.2:                                # %then13
                                        #   in Loop: Header=BB0_3 Depth=1
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rax
	movl	(%rdx), %ecx
	leal	(%rcx,%rcx), %edx
	movl	%edx, (%rax)
	shll	$2, %ecx
	jmp	.LBB0_3
.LBB0_4:                                # %afterloop
	movl	%ecx, %eax
	movq	%rbp, %rsp
	popq	%rbp
	retq
	.seh_endproc
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
	movl	$2, %ecx
	movl	$2, %edx
	callq	deepWhileBr
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
