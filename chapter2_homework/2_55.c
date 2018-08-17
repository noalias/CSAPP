#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer , size_t );
void show_short(short );
void show_int(int );
void show_long(long );
void show_float(float );
void show_double(double );
void show_pointer(void * );
void test_show_bytes(int );

int main(void)
{
    int val = 12345;
    test_show_bytes(val);
}

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_short(short x)
{
    printf("size of 'short' :");
    show_bytes((byte_pointer) &x, sizeof(short));
}

void show_int(int x)
{
    printf("size of 'int' :");
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_long(long x)
{
    printf("size of 'long' :");
    show_bytes((byte_pointer) &x, sizeof(long));
}

void show_float(float x)
{
    printf("size of 'float' :");
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_double(double x)
{
    printf("size of 'double' :");
    show_bytes((byte_pointer) &x, sizeof(double));
}

void show_pointer(void *x)
{
    printf("size of 'void *' :");
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val)
{
    int ival = val;
    short sval = ival;
    long lval = ival;
    float fval = (float) ival;
    double dval = (double) ival;
    int *pval = &ival;

    show_short(sval);
    show_int(ival);
    show_long(lval);
    show_float(fval);
    show_double(dval);
    show_pointer(pval);
}

