#include <stdio.h>
#include <inttypes.h>

int signed_high_prod(int x, int y);
unsigned unsigned_high_prod(unsigned x, unsigned y);

unsigned w = sizeof(unsigned) << 3;

int main(void)
{
    unsigned x = 0x82345678;
    unsigned y = 0xFFFFFFFF;
    uint64_t mul = (uint64_t) x * y;
    unsigned mul_high = mul >> w;
    printf("%d", mul_high == unsigned_high_prod(x, y));

    return 0;
}

int signed_high_prod(int x, int y)
{
    int64_t mul = (int64_t) x * y;
    return mul >> w;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    int unsigned_high_prod_A = signed_high_prod(x, y);
    unsigned x_h = x >> 31; /* x最高有效位的值*/
    unsigned y_h = y >> 31; /* y最高有效位的值*/
    int unsigned_high_prod_B = x * y_h + y * x_h;/* 按照2.18式进行展开,其中,x_h*y_h*(2<<w)项式超过w位被舍去*/
    return unsigned_high_prod_A + unsigned_high_prod_B;
}
