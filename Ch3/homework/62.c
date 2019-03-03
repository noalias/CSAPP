/* p1 in %rdi, p2 in %rsi, action in %edx
 * .L8:                       MODE_E
 *   movl  $27,%eax         result = 27
 *   ret                    break
 * .L3:                       MODE_A
 *   movq  (%rsi),%rax      result = *p2
 *   movq  (%rdi),%rdx      
 *   movq  %rdx,(%rsi)      *p2 = *p1
 *   ret                    break
 * .L5:                       MODE_B
 *   movq  (%rdi),%rax      
 *   addq  (%rsi),%rax      result = *p1 + *p2
 *   movq  %rax,(%rdi)      *p1 = *p1 + *p2
 *   ret                    break
 * .L6:                       MODE_C
 *   movq  $59,(%rdi)       *p1 = 59
 *   movq  (%rsi),%rax      result = *p2
 *   ret                    break
 * .L7:                       MODE_D
 *   movq  (%rsi),%rax      
 *   movq  %rax,(%rdi)      *p1 = *p2
 *   movl  $27,%eax         result = 27
 *   ret
 * .L9:                       default
 *   movl  $12,%eax         result = 12
 *   ret
 */
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action)
{
    long result = 0;
    switch (action) {
        case MODE_A: result = *p2;
                     *p2 = *p1;
                     break;
        case MODE_B: result = *p1 + *p2;
                     *p1 += *p2 ;
                     break;
        case MODE_C: *P1 = 59;
                     result = *p2;
                     break;
        case MODE_D: *p1 = *p2;           /*这里可以将部分代码合并*/
        case MODE_E: result = 27;
                     break;
        default:
                     result = 12;
    }
    return result;
}

