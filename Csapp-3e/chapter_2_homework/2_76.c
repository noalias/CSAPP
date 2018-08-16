#include <stdio.h>

int main(void)
{
    int x = 2;
    printf("k=17,x*k-->%d\n", (x << 4) + x);
    printf("k=-7,x*k-->%d\n", (x << 3) - x);
    printf("k=60,x*k-->%d\n", (x << 6) - (x << 2));
    printf("k=112,x*k-->%d\n", (x << 4) - (x << 7));

    return 0;
}

