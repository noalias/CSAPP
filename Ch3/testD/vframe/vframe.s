	.file	"vframe.c"
	.text
	.globl	vframe
	.type	vframe, @function
vframe:
.LFB0:
	.cfi_startproc
	pushq	%rbp                      # 保存被调用者寄存器
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp                # 储存栈指针
	.cfi_def_cfa_register 6
	subq	$16, %rsp                 # 分配16字节
	leaq	22(,%rdi,8), %rax         # 
	andq	$-16, %rax                # 准备数组字节
	subq	%rax, %rsp                # 分配数组
	leaq	7(%rsp), %rax             
	shrq	$3, %rax
	leaq	0(,%rax,8), %r8           # p
	movq	%r8, %rcx                 # p->%rcx
	leaq	-8(%rbp), %r9             # &i->%r9
	movq	%r9, 0(,%rax,8)           # &i->p[0]
	movq	$1, -8(%rbp)              # i = 1
	jmp	.L2
.L3:
	movq	%rdx, (%rcx,%rax,8)       # q->p[i]
	addq	$1, -8(%rbp)              # i = 1
.L2:
	movq	-8(%rbp), %rax            # i->%rax
	cmpq	%rax, %rdi                # compare n:i
	jg	.L3                           # if > , goto .loop
	movq	(%r8,%rsi,8), %rax        # p[idx]->%rax
	movq	(%rax), %rax              # store *p[idx]
	leave                             # restore %rsp & %rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	vframe, .-vframe
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
