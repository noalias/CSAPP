#include <stdio.h>
#include <limits.h>

int mul3div4(int );

int main(void)
{
    int x = INT_MIN;
    printf("%d", mul3div4(x));

    return 0;
}

int mul3div4(int x)
{
    int bais = x >> ((sizeof(int) << 3) -1);
    x = (x << 1) + x;
    return (bais & ((x + (1 << 2) - 1) >> 2)) + (!bais & (x >> 2));
}

