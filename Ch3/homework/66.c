/* long sum_col(long n, long A[NR(n)][NC(n)], long j)
 * n in %rdi, A in %rsi, j in %rdx
 *
 * sum_col:
 *     leaq    1(,%rdi,4),%r8         4n+1
 *     leaq    (%rdi,%rdi,2),%rax     3n
 *     movq    %rax,%rdi              3n
 *     testq   %rax,%rax              test 3n:0
 *     jle     .L4                    if 3n <= 0, goto done
 *     salq    $3,%r8                 4n+1 << 3
 *     leaq    (%rsi,%rdi,8),%rcx     A+24n
 *     movl    $0,%eax                result = 0
 *     movl    $0,%edx                i = 0
 * .L3:                               loop:
 *     addq    (%rcx),%rax            *(A+8*3n) 第i=0行
 *     addq    $1,%rdx                i++
 *     addq    %r8,%rcx               A+8*3n+4n+1 每增加一行,地址偏移量为4n+1
 *     cmpq    %rdi,%rdx              comp i:3n
 *     jne     .L3                    if i != 3n, goto loop
 *     rep;ret
 * .L4:
 *     movl    $0,%eax                result = 0
 *     ret
 * A[i][j]的地址偏移：A + T(i * N + j) 
 * 每增加一行，N = 4n + 1 = NC(n)
 * i < 3n, 所以NR(n)=3n
 */
#define NR(n) (3 * (n))
#define NC(n) (4 * (n) + 1)
