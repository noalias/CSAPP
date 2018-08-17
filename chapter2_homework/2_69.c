/* Do rotating left shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32;
 *  n = 4 -> 0x23456781, n = 20 -> 0x67812345
 */
#include <stdio.h>

unsigned rotate_left(unsigned x, int n);

int main(void)
{
    unsigned x = 0x12345678;    
    int n = 0, n_1 = 4, n_2 = 20;

    printf("%x\n", rotate_left(x, n));
    printf("%x\n", rotate_left(x, n_1));
    printf("%x\n", rotate_left(x, n_2));

    return 0;
}
    
unsigned rotate_left(unsigned x, int n)
{
    return (x << n) | (x >> (sizeof(int) << 3) - n -1 >> 1);
}
                


