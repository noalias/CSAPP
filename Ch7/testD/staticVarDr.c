#include <stdio.h>
#include <stdbool.h>

int *f(void);
int *g(void);

int main(void) 
{
    if (f() != g()) 
        printf("The address is different.\n");
    else 
        printf("The address is same.\n");

    return 0;
}

int *f(void)
{
    static int a;
    return &a;
}

int *g(void)
{
    static int a;
    return &a;
}
