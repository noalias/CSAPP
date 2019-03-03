/* long aframe(long n, long idx, long *q)
 * n in %rdi, idx in %rsi, q in %rdx
 * aframe:
 *     pushq  %rsp
 *     movq   %rsp,%rbp               store %rsp
 *     subq   $16,%rsp                Allocate space for i (%rsp = s1) 
 *     leaq   30(,%rdi,8),%rax        30 + 8 * n
 *     andq   $-16,%rax               0x1E + 8 * n & ~0xF
 *     subq   %rax,%rsp               Allocate space for p (%rsp = s2)
 *     leaq   15(%rsp),%r8            
 *     andq   $-16,%r8                set %r8 to &p[0]
 *
 * A. 0x1E + 8 * n & ~0xF,当n为偶数时，上式等于0x10 + 8 * n(即表达式中低4位中0xE被掩码去掉),当n为奇数时，上式等于0x18 + 8 * n（即表达式中低四位中0x6被掩码去掉)。即，n为偶数时，s2=s1-(8n+16);n为奇数时，s2=s1-(8n+24)
 * B. p = s2+15 & ~0xF,使s2的低4位清零并增加0x10,即p为16的倍数z中大于s2的最低值
 * C. 
