#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void good_echo(void);

int main(void)
{
    good_echo();
    return 0;
}

void good_echo(void)
{
    char buf[8];
    char *check;

    do { 
        if ((check = fgets(buf, sizeof(buf), stdin)) == NULL) 
            exit(EXIT_FAILURE);
        fputs(buf, stdout);
    } while (strlen(buf) == 7 && buf[6] != '\n');
}
