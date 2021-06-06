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
.seh_proc main
# %bb.0:                                # %entry
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	pushq	%rax
	.seh_stackalloc 8
	movq	%rsp, %rbp
	.seh_setframe %rbp, 0
	.seh_endprologue
	subq	$32, %rsp
	callq	getint
	addq	$32, %rsp
	movl	%eax, n(%rip)
	cmpl	$11, %eax
	jl	.LBB0_3
# %bb.1:                                # %then
	movl	$1, %eax
	jmp	.LBB0_2
.LBB0_3:                                # %ifcont
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rsi
	movl	$16, %eax
	callq	__chkstk
	subq	%rax, %rsp
	movq	%rsp, %rdi
	movl	$0, (%rdi)
	movl	$0, (%rsi)
	leaq	a(%rip), %rbx
	.p2align	4, 0x90
.LBB0_5:                                # %loopend
                                        # =>This Inner Loop Header: Depth=1
	movl	(%rdi), %eax
	cmpl	n(%rip), %eax
	jge	.LBB0_6
# %bb.4:                                # %loop
                                        #   in Loop: Header=BB0_5 Depth=1
	subq	$32, %rsp
	callq	getint
	addq	$32, %rsp
	movslq	(%rdi), %rcx
	movl	%eax, (%rbx,%rcx,4)
	addl	%eax, (%rsi)
	incl	(%rdi)
	jmp	.LBB0_5
.LBB0_6:                                # %afterloop
	movl	(%rsi), %esi
	subq	$32, %rsp
	movl	%esi, %ecx
	callq	putint
	movl	$10, %ecx
	callq	putch
	addq	$32, %rsp
	movl	%esi, %eax
.LBB0_2:                                # %then
	leaq	8(%rbp), %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.bss
	.globl	n                               # @n
	.p2align	2
n:
	.long	0                               # 0x0

	.globl	a                               # @a
	.p2align	4
a:
	.zero	40

