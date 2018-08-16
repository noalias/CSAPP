#include <stdio.h>

int replace_byte(unsigned , int , unsigned char );

int main(void)
{
    unsigned x = 0x12345678;
    int i = 2;
    unsigned char b = 0xAB;
    printf("The change is %x", replace_byte(x, i, b));

    return 0;
}

int replace_byte(unsigned x, int i, unsigned char b)
{
    int byte_i = i * 8;
    return x & (0xff << byte_i) ^ ((unsigned) b << byte_i) ^ x;
}

