#include <stdio.h>
typedef unsigned float_bits;
/* IA32机器的float和double都是用80位的扩展精度表示. */
/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f);

int main(void)
{
    float_bits x = 0xff800001; /* NaN */

    printf("float_negate(f): %x-->%x\n", x, float_absval(x));
    printf("is_equal is %d", float_absval(x) == x);

    return 0;
}

float_bits float_absval(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    (!(exp ^ 0xff) && frac) || (sign &= 0x0);

    return (sign << 31) | (exp << 23) | frac;
}

