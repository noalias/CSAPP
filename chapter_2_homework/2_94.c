#include <stdio.h>

typedef unsigned float_bits;

/* Compute 2.0*f, If f is NaN, then return NaN. */
/* V = 2 ^ E * M --> 2 * V = 2 ^ E * M * 2; 
 * 此时，当保持E不变，2 * V = 2 ^ E * (M << 1)
 * 当保持M不变，2 * V = 2 ^ (E + 1) * M
 * 第一种情况适用于，非规格化的数，但f左移overflow时，M = 1 + f，2 * V转化为规格化数;
 * 第二种情况适用于，规格化数，但e + 1 = 0xff时，2 * V转化为无穷，frac须置为0 */
float_bits float_twice(float_bits f);

int main(void)
{
    float_bits x = 0xbf800000;
    float *m = &x;

    printf("*m-->%f\nfloat_twice(f)-->%x\n2 * *m == float_twice(*m) is %d\n", *m, float_twice(x), 2 * *m == float_twice(*m));

    return 0;
}

float_bits float_twice(float_bits f)
{
    /* 浮点数的符号位、阶码和尾数的位级表示 */ 
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;

    if (exp == 0) /* 非规格化的数 */
    {
        frac <<= 1;
        if (frac & 0x800000) /* 检测overflow */
        {
            frac ^= 0x800000;
            exp++;
        }
    }
    else if (exp ^ 0xff) /* 规格化的数 */
    { 
        if (exp == 0xfe) /* 对于0xfe的阶码，运算后将浮点数处理为无穷 */
            frac = 0;
        exp++;
    }
    return sign << 31 | exp << 23 | frac;  
}
