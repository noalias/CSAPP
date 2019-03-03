#define M 15
void transpose(long A[M][M])
{
    long i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++) {
            long t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
}

/* 内循环代码
 * .L6:
 *   movq  (%rdx),%rcx        store *p1
 *   movq  (%rax),%rsi        store *p2
 *   movq  %rsi,(%rdx)        
 *   movq  %rcx,(%rax)        exchange the value of *p2 & *p1
 *   addq  $8,%rdx            p1+8
 *   addq  $120,%rax          p2+15*8
 *   cmpq  %rdi,%rax          %rdi -> A
 *   jne   .L6
 *
 * A. %rdx -> &A[i][j]
 * B. %rax -> &A[j][i]
 * C. M = 15
 */
