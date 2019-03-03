	.file	"dui.c"
	.text
	.globl	sum
	.type	sum, @function
sum:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	addl	a(%rip), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	sum, .-sum
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	movl	$1, a(%rip)
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.comm	a,4,4
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
