/* 
 * Generate mask indicating leftmost 1 in x. Assume w=32.
 * For example, 0xFF00 -> 0x8000, and 0x66xx --> 0x4000.
 * If x = 0, then return 0.
 */
#include <stdio.h>

int leftmost_one(unsigned x);

int main(void)
{
    unsigned x = 0x6600;

    printf("%x", leftmost_one(x));

    return 0;
}

int leftmost_one(unsigned x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1 >> 1;
}
