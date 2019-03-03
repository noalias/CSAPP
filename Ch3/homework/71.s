	.file	"71.c"
	.text
	.globl	good_echo
	.type	good_echo, @function
good_echo:
.LFB53:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
.L4:
	movq	%rsp, %rdi
	movq	stdin(%rip), %rdx
	movl	$8, %esi
	call	fgets@PLT
	testq	%rax, %rax
	je	.L7
	movq	%rsp, %rbx
	movq	stdout(%rip), %rsi
	movq	%rbx, %rdi
	call	fputs@PLT
	movq	$-1, %rcx
	movl	$0, %eax
	movq	%rbx, %rdi
	repnz scasb
	cmpq	$-9, %rcx
	jne	.L1
	cmpb	$10, 6(%rsp)
	jne	.L4
.L1:
	movq	8(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L8
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	movl	$1, %edi
	call	exit@PLT
.L8:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE53:
	.size	good_echo, .-good_echo
	.globl	main
	.type	main, @function
main:
.LFB52:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	good_echo
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE52:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
