union ele {
    struct {
        long *p;
        long y;
    } e1;
    struct {
        long x;
        union ele *next;
    } e2;
};

/* A. 字段的偏移量:
 * e1.p: 0;
 * e1.y: 8;
 * e2.x: 0;
 * e2.next: 8;
 *
 * B. 共16个字节
 *
 * C. proc汇编代码：
 * void proc(union ele *up)
 * up in %rdi
 * proc:
 *    movq  8(%rdi),%rax      store up->e2.next in %rax
 *    movq  (%rax),%rdx       store up->e2.next->e1.p in %rdx
 *    movq  (%rdx),%rdx       store *(up->e2.next->e1.p) in %rdx
 *    subq  8(%rax),%rdx      *(up->e2.next->e1.p) - up->e2.next->e1.y
 *    movq  %rdx,(%rdi)       store %rdx in up->e2.x
 *    ret
 * C代码如下：
 */
void proc(union ele *up) 
{
    up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1.y;
}

