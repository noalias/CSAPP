/* Compute (int)f.
 * If conversion causes overflow or f is NaN, return 0x80000000
 */

/* 浮点数转化为整数，是基于数的实际值，浮点数frac位与整数具有关联
 * frac >> k（k为适当的位），可以得到整数
 */
#include <stdio.h>

typedef unsigned float_bits;

float_bits float_f2i(float_bits f);

int main(void)
{

    return 0;
}

int float_f2i(float_bits f)
{
    /* 浮点数的符号位、阶码和尾数的位级表示 */ 
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xff;
    unsigned frac = f & 0x7fffff;
    unsigned bias = 0x7f;

    int E = exp - bias; /* 对于unsigned bias,其逆元等同于bias相同位级补码的负值 */
    int num;

    if (E < 0) /* 指数小于0，表示f为小数，相应的整数向0舍入 */
        num = 0;
    else if (E > 31) /* 整数转化为浮点数，最多向左移位31，即一个整数能表示的最大浮点数的指数位最大为31 */
        num = 0x80000000;
    else
    {
        M = frac | 0x800000; /* 将浮点数的小数位还原为整数的有效位 */
        if (E > 23) /* 指数位大于23则说明，整数转化为浮点数时，将舍去最低的（E-23）位;反之，浮点数转化为整数时，需左移（E-23）位以补齐整数丢失的位 */
            num = M << E - 23;
        else /* 指数小于或等于23时，整数转化为浮点数时，需增加（23-E)位以补齐尾数；反之，浮点数转化为整数时，需右移以还原整数位级 */
            num = M >> (23 - E);
    }

    return sign ? -num : num;
}

