	.file	"65.c"
	.text
	.globl	transpose
	.type	transpose, @function
transpose:
.LFB0:
	.cfi_startproc
	leaq	120(%rdi), %r10
	movq	%rdi, %r9
.L2:
	leaq	1800(%r9), %r8
	movq	%r9, %rax
	movq	%rdi, %rdx
.L3:
	movq	(%rdx), %rcx
	movq	(%rax), %rsi
	movq	%rsi, (%rdx)
	movq	%rcx, (%rax)
	addq	$8, %rdx
	addq	$120, %rax
	cmpq	%r8, %rax
	jne	.L3
	addq	$120, %rdi
	addq	$8, %r9
	cmpq	%r10, %r9
	jne	.L2
	rep ret
	.cfi_endproc
.LFE0:
	.size	transpose, .-transpose
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
