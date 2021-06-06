	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 func1;
	.scl	2;
	.type	32;
	.endef
	.globl	func1                           # -- Begin function func1
	.p2align	4, 0x90
func1:                                  # @func1
# %bb.0:                                # %entry
	movl	$1, %eax
	retq
                                        # -- End function
	.def	 func2;
	.scl	2;
	.type	32;
	.endef
	.globl	func2                           # -- Begin function func2
	.p2align	4, 0x90
func2:                                  # @func2
# %bb.0:                                # %entry
	movl	$2, %eax
	retq
                                        # -- End function
	.def	 func3;
	.scl	2;
	.type	32;
	.endef
	.globl	func3                           # -- Begin function func3
	.p2align	4, 0x90
func3:                                  # @func3
# %bb.0:                                # %entry
	movl	$4, %eax
	retq
                                        # -- End function
	.def	 func4;
	.scl	2;
	.type	32;
	.endef
	.globl	func4                           # -- Begin function func4
	.p2align	4, 0x90
func4:                                  # @func4
# %bb.0:                                # %entry
	movl	$24, %eax
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
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	func1
	movl	%eax, %esi
	callq	func2
	movl	%eax, %edi
	addl	%esi, %edi
	callq	func3
	movl	%eax, %esi
	addl	%edi, %esi
	callq	func4
                                        # kill: def $eax killed $eax def $rax
	leal	96(%rax,%rsi), %eax
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
