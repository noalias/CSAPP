/* long decode2(long x, long y, long z);
 * decode2:
 *   subq     %rdx,%rsi
 *   imulq    %rsi,%rdi
 *   movq     %rsi,%rax
 *   salq     $63, %rax
 *   sarq     $63, %rax
 *   xorq     %rdi,%rax
 *   ret
 */

long decode2(long x, lnog y, long z)
{
    long result;

    y -= z;
    x *= y;
    result = y << 63 >> 63;
    result ^= x;

    return result;
}



