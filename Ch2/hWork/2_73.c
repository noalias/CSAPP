/* Addition that saturates to TMin or TMax */
#include <stdio.h>
#include <limits.h>

int saturating_add(int x, int y);

int main(void)
{
    int x = 0x4FFFFFFF;
    int y = 0x60000000;
    printf("%x-->%d", saturating_add(x, y), saturating_add(x, y));

    return 0;
}

int saturating_add(int x, int y)
{
    int sum = x + y;
    int pos_over = !(x & INT_MIN) && !(y & INT_MIN) && (sum & INT_MIN);
    int neg_over = (x & INT_MIN) && (y & INT_MIN) && !(sum & INT_MIN);
    (pos_over && (sum = INT_MAX)) || (neg_over && (sum = INT_MIN));

    return sum;
}


