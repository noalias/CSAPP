/* Return 1 when x can be represented as an n-bit, 2's-complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 */
#include <stdio.h>

int fits_bits(int x, int n);

int main(void)
{
    int x = 0xFF;
    int n = 8;

    printf("%x\n", fits_bits(x, n));

    return 0;
}

int fits_bits(int x, int n)
{
    int w = sizeof(int) << 3;
    int y = x << w - n - 1 >> w - n - 1; /* 能用n位表示，说明n+1位为0 */
    printf("%x\n%x\n", x, y);
    return y == x;
}
