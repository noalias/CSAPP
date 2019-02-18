#include <stdio.h>


/* Mask with least signficant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n);

int main(void)
{
    int n = 6;
    int n_1 = 17;
    int n_2 = sizeof(int) << 3;

    printf("%x\n", lower_one_mask(n));
    printf("%x\n", lower_one_mask(n_1));
    printf("%x\n", lower_one_mask(n_2));

    return 0;
}

int lower_one_mask(int n)
{
    return ~(-1 << n -1 << 1);
}
