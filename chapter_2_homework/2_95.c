#include <stdio.h>

typedef unsigned float_bits;

/* Compute 0.5*f, If f is NaN, then return NaN. */
float_bits float_half(float_bits f);

int main(void)
{

    return 0;
}

float_bits float_half(float_bits f)
{
    /* 浮点数的符号位、阶码和尾数的位级表示 */ 
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;

    if (exp == 0) /* 非规格化的数 */
    {
        if (frac & 0x1) /* 检测frac右移是否需要舍入 */
            frac++;
        frac >>= 1;
    }
    else if (exp ^ 0xff) /* 规格化的数 */
    { 
        if (exp == 0x1) /* 对于0x1的阶码，运算后转化为非规格化的数 */
        {
            if (frac & 0x1) /* 检测frac右移是否需要舍入,同时需要在最高有效位补1 */
                frac++;
            frac >>= 1;
            frac |= 0x400000;
        }
        exp--;
    }
    return sign << 31 | exp << 23 | frac;  
}

