	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"SysY--"
	.def	 whileIf;
	.scl	2;
	.type	32;
	.endef
	.globl	whileIf                         # -- Begin function whileIf
	.p2align	4, 0x90
whileIf:                                # @whileIf
# %bb.0:                                # %entry
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.LBB0_6
	.p2align	4, 0x90
.LBB0_2:                                #   in Loop: Header=BB0_6 Depth=1
	movl	$25, %eax
.LBB0_5:                                # %ifcont9
                                        #   in Loop: Header=BB0_6 Depth=1
	incl	%edx
	addl	$2, %ecx
.LBB0_6:                                # %loopend
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$100, %edx
	jge	.LBB0_7
# %bb.1:                                # %loop
                                        #   in Loop: Header=BB0_6 Depth=1
	cmpl	$5, %edx
	je	.LBB0_2
# %bb.3:                                # %loop
                                        #   in Loop: Header=BB0_6 Depth=1
	movl	$42, %eax
	cmpl	$10, %edx
	je	.LBB0_5
# %bb.4:                                # %else7
                                        #   in Loop: Header=BB0_6 Depth=1
	movl	%ecx, %eax
	jmp	.LBB0_5
.LBB0_7:                                # %afterloop
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
	callq	whileIf
	nop
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
