#include <stdio.h>

typedef unsigned char *byte_pointer;

int little_endian(int );

int main(void)
{
    int val = 12345;
    printf("little endian is : %d", little_endian(val));

    return 0;
}

int little_endian(int x)
{
    return !((unsigned short) x == *((byte_pointer) &x));
}

