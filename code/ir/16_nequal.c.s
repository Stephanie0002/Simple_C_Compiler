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
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	getint
	movl	%eax, a(%rip)
	callq	getint
	movl	%eax, b(%rip)
	xorl	%ecx, %ecx
	cmpl	%eax, a(%rip)
	setne	%cl
	movl	%ecx, %eax
	addq	$40, %rsp
	retq
	.seh_endproc
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

