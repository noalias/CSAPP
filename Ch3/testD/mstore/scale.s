	.file	"scale.c"
	.text
	.globl	scale
	.type	scale, @function
scale:
.LFB0:
	.cfi_startproc
	leaq	(%rdi,%rsi,4), %rax
	leaq	(%rdx,%rdx,2), %rcx
	leaq	0(,%rcx,4), %rdx
	addq	%rdx, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	scale, .-scale
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
