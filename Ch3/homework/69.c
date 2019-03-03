/* void test(long i, b_struct *bp)
 * i in %rdi, bp in %rsi
 *
 * mov    0x120(%rsi),%ecx           &bp->last = bp+0x120
 * add    (%rsi),%ecx                stroe (bp->first + bp->last) in n
 * lea    (%rdi,%rdi,4),%rax         store 5i
 * lea    (%rsi,%rax,8),%rax         bp + 40i
 * mov    0x8(%rax),%rdx             store ap->idx in %rdx; *(bp + 0x8 + 40i),这里bp+0x8也就是bp->a,(bp->a + 40i)也就是ap
 * movslq %ecx,%rcx                  对n做符号扩展
 * mov    %rcx,0x10(%rax,%rdx,8)     (bp + 0x10 + 40i + ap->idx * 8) = ap + 0x8 + ap->idx * 8;这里ap+0x8就是ap->x
 * retq
 *
 * 考虑结构的元素对齐，对汇编代码进行分析可得：
 * bp结构元素分布图:
 * &bp->first--------&bp->a---...----&bp->last----
 * &bp->last - &bp->first = 0x120
 * &bp->a - &bp->first = 0x8
 *
 * 数组a_struct a[CNT]的伸缩量为40
 * 字段idx的位数为8
 * 字段x必须为8的倍数,其元素伸缩量为8，
 * 所以idx类型为long,x的类型为long x[4]
 * 
 * A. CNT = (0x120 - 0x8) / 40 = 7
 * B. long idx; long x[5]
 */

typedef struct {
    long idx;
    long x[4];
} a_struct;
