#include <stdio.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x);

int main(void)
{
    char *sen[] = {"NEG", "ZERO", "POS", "OTHER"};

    printf("%s\n", sen[find_range(0.0)]);
    printf("%s\n", sen[find_range(0.0/0.0)]);
    printf("%s\n", sen[find_range(-2.3)]);
    printf("%s\n", sen[find_range(3.30)]);

    return 0;
}

