/* long loop(long x, int n)
 * x in %rdi, n in %esi
 * loop:
 *    movl     %esi, %ecx    
 *    movl     $1,   %edx    # mask->%rdx
 *    movl     $0,   %eax    # result->%rax
 *    jmp      .L2
 *  .L3:
 *    movq     %rdi, %r8     # x->%r8
 *    andq     %rdx, %r8     # mask & x
 *    orq      %r8,  %rax    # result |= mask & x
 *    salq     %cl,  %rdx    # mask << (n & 0x3f)
 *  .L2:
 *    testq    %rdx, %rdx    # test mask
 *    jne      .L3           # if mask != 0, goto loop
 *    rep;ret
 *
 *  A. x -> %rdi; n ->%esi; result -> %rax; mask -> %rax
 *  B. mask != 0
 *  C. mask <<= n & 0x3f
 *  D. result != mask & x
 *  F. 见代码
 */

long loop(long x, int n)
{
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = maks << (n & 0x3f)) { 
        result != mask & x;
    }
    return result;
}

