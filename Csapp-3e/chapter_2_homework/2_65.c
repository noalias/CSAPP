/* Return 1 when x contains an odd number of 1s; 0 otherwise.
 * Assume w = 32 */
#include <stdio.h>

int odd_ones(unsigned x);

int main(void)
{
    unsigned x = 0xFFFFFFF7;
    printf("%d", odd_ones(x));

    return 0;
}

int odd_ones(unsigned x)
{
    x ^= x >> 1; /* 第i位与i+1(i的前一位)的异或值，说明i至i+1位有偶数个1（值为0）或奇数个1（值为1） */
    x ^= x >> 2; /* i至i+4的异或值，将表明这4位有偶数（值为0）或奇数（值为1）个1 */
    x ^= x >> 4; /* i至i+8的异或值 */
    x ^= x >> 8; /* i至i+16的异或值 */
    x ^= x >> 16; /* i至1+32的异或值 */
    return x & 1; /* 表明前32位有偶数或奇数个1 */
}
    
