/* Divide by power of 3. assume 0 <= k < w-1 */
#include <stdio.h>

int divide_power2(int x, int k);

int main(void)
{
    int x = 15, y = -15;
    int k = 3;
    printf("%d %d-->%d", divide_power2(x, k), divide_power2(y, k), y >> k);

    return 0;
}

int divide_power2(int x, int k)
{
    int w = sizeof(int) << 3;
    int sign = x >> (w - 1);
    int result;
    (sign && (result = (x + (1 << k) - 1) >> k)) || (result = x >> k);
    return result;
}

