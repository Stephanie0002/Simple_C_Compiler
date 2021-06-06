	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 func;
	.scl	2;
	.type	32;
	.endef
	.globl	func                            # -- Begin function func
	.p2align	4, 0x90
func:                                   # @func
# %bb.0:                                # %entry
                                        # kill: def $ecx killed $ecx def $rcx
	leal	-1(%rcx), %eax
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
	movl	$10, a(%rip)
	movl	$10, %ecx
	callq	func
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.bss
	.globl	a                               # @a
	.p2align	2
a:
	.long	0                               # 0x0

