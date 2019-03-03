	.file	"get.c"
	.text
	.globl	get
	.type	get, @function
get:
.LFB0:
	.cfi_startproc
	movq	8(%rdi), %rax
	movzbl	(%rax), %eax
	movb	%al, (%rsi)
	ret
	.cfi_endproc
.LFE0:
	.size	get, .-get
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
