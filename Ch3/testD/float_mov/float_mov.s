	.file	"float_mov.c"
	.text
	.globl	float_mov
	.type	float_mov, @function
float_mov:
.LFB0:
	.cfi_startproc
	vmovss	(%rdi), %xmm1
	vmovss	%xmm0, (%rsi)
	vmovaps	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	float_mov, .-float_mov
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
