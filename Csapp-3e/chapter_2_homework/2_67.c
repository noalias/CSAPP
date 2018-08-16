/* Answer for A: page 41 of csapp ,移位量k大于被移位数的宽度w时，移位量k=k mod w；*/
#include <stdio.h>

/* The following code does not run properly on some machines */
int int_size_is_32(void);
int int_size_is_32_for_16bits(void);

int main(void)
{
    int lval = 0xFEDCBA98;
    printf("%x\n", lval << 32); /* 佐证了A,但是立即数似乎并不受此影响 */
    printf("%d\n", int_size_is_32());
    printf("%d", int_size_is_32_for_16bits());

    return 0;
}

/* Answer for B */
int int_size_is_32(void)
{
    int set_msb = 1 << 31;
    int beyond_msb = set_msb;
    beyond_msb <<= 1;

    return set_msb && !beyond_msb;
}


/* Answer for C */
int int_size_is_32_for_16bits(void)
{
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb;
    beyond_msb <<= 1;

    return set_msb && !beyond_msb;
}
