#include <stdio.h>
typedef unsigned float_bits;

/* Compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f);

int main(void)
{
    printf("float_negate(f)-->%u\n", float_negate(32.0));
    printf("is_equal = %d\n", -32.0 == float_negate(32.0)); /* 无法测试，因为IA32机器的float和double都是用80位的扩展精度表示。 */

    return 0;
}

float_bits float_negate(float_bits f)
{
    unsigned _sign = f >> 31 ^ 0x1;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    _sign ^= !(exp ^ 0xff) && frac;

    return (_sign << 31) | (exp << 23) | frac;
}
