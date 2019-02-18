#include <stdio.h>

int x_to_y(int , int );

int main(void)
{
    int x = 0x89ABCDEF, y = 0x76543210;

    printf(" %x", x_to_y(x, y));

    return 0;
}

int x_to_y(int x, int y)
{
    return (x & 0xFF ^ y) ^ (y & 0xFF);
}
