/* Determine whether arguments can be subtracted without overflow */
#include <stdio.h>
#include <limits.h>

int tsub_ok(int x, int y);

int main(void)
{
    int x = INT_MAX;
    int y = 1;
    printf("%d", tsub_ok(x, y));

    return 0;
}

int tsub_ok(int x, int y)
{
    int sum = x - y;
    int mask = 0x1 << 31;
    int pos_over = !(x & mask) && !(-y & mask) && (sum & mask);
    int neg_over = (x & mask) && (-y & mask) && !(sum & mask);

    return !(pos_over || neg_over);
}

