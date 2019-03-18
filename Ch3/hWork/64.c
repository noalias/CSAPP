long A[R][S][T];

long store_ele(long i, long j, long k, long *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}

/* long store_ele(long i, long j, long k, long *dest)
 * i in %rdi, j in %rsi, k in %rdx, dest in %rcx
 *
 * store_ele:
 *    leaq  (%rsi,%rsi,2),%rax        
 *    leaq  (%rsi,%rax,4),%rax        stroe 13j
 *    movq  %rdi,%rsi                 store i
 *    salq  $6,%rsi                   i*128
 *    addq  %rsi,%rdi                 i*129
 *    addq  %rax,%rdi                 13j+129i
 *    addq  %rdi,%rdx                 13j+129i+k
 *    movq  A(,%rdx,8),%rax           
 *    movq  %rax,(%rcx)               store A[i][j][k]
 *    movl  $3640,%eax                R * S * T = 3640
 *    ret
 *
 * A. &A[i][j][k] = A + (S * T * i + T * j + k) * 8
 * B. 根据上式：
 *    T = 13; S = 129 / 13 = 9; R = 3640 / 129 = 28
 */
