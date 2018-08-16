#include <stdio.h>

int int_shifts_are_arithmetic(int );

int main(void)
{
    int a = -1;
    printf("%d", int_shifts_are_arithmetic(a));

    return 0;
}

int int_shifts_are_arithmetic(int x)
{
    return (x >> 1) == -1;
}
