#include <stdio.h>

unsigned srl(unsigned , int );
int sra(int , int );

int main(void)
{
    int x = 0x11000000;
    int k = 16;

    printf("%x-->%u\n", srl(x, k), srl(x, k));
    printf("%x-->%d\n", sra(x, k), sra(x, k));

    return 0;
}

unsigned srl(unsigned x, int k)
{
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    return xsra &= ~(-1 << (sizeof(int) << 3) - k);
}

int sra(int x, int k)
{
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    return xsrl |= -1 << (sizeof(int) << 3) - k;
}
