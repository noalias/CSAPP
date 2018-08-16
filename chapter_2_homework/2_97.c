/* Compute (float)i.
 */

#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

float_bits float_i2f(int i);

int main(void)
{
    int i = 0;
    printf("float_i2f(i)-->%x\n", float_i2f(i));

    return 0;
}

float_bits float_i2f(int i)
{
    unsigned sign = 0;
    unsigned exp;
    unsigned frac;

    int count = 1; /* 将整数最高位标记为1 */
    int sign_32 = INT_MIN; 
    int E; /* 浮点数的指数 */

    /* 计算符号位 */
    if (i & INT_MIN) /* 整型数转化为浮点数，先检查符号位 */
    {
        sign = 1;
        i = - i; /* 这里i=INT_MIN时，负数是其本身 */
    }

    /* 计算指数E */
    while (!(i & sign_32)) /* 从最高位开始检查当前位是否为0,如果不为0,则得到值为1最高位的标记count */
    {
        if (count == 32) /* 当整数为1时，count=32并退出循环；而整数为0时，count=32后继续进入循环，这样触发条件，并退出循环 */
            return 0; /* 直接返回将1和0区分开 */
        count++;
        sign_32 >>= 1;
    }

    E = (sizeof(int) << 3) - count;
    printf("E-->%d\n", E);

    exp = E ? E + 0x7f : 0x7f;

    /* 计算小数位 */
    if (E > 23) 
        frac = i >> E - 23; /* 向0舍入 */
    else
        frac = i << 23 - E;
    
    return sign << 31 | exp << 23 | frac & 0x7fffff;
}
