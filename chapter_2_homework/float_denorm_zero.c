#include <stdio.h>
typedef unsigned float_bits;
/* IA32机器的float和double都是用80位的扩展精度表示. 
 * If f is denorm, return 0. Otherwise, return f. */
float_bits float_denorm_zero(float_bits f);

int main(void)
{
    float_bits x = 0x80001111; /* NaN */
    float *y = &x;

    printf("*y-->%f\n", *y);
    printf("float_denorm_zero(f): %x-->%x\n", x, float_denorm_zero(*y));

    return 0;
}

float_bits float_denorm_zero(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    exp == 0 && (frac = 0);

    return (sign << 31) | (exp << 23) | frac;
}


