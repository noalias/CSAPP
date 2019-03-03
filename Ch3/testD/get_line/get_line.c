#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *gets(char *s)
{
    int c;
    char *dest = s;
    while ((c = getchar()) != '\n' && c != EOF)
        *dest++ = c;
    if (c == EOF && dest == s)
        return NULL;
    *dest++ = '\0';
    return s;
}

char *get_line()
{
    char buf[4];
    char *result;
    gets(buf);
    if ((result = malloc(strlen(buf) + 1)) == NULL)
        exit(1);
    strcpy(result, buf);
    return result;
}

int main(void)
{
    get_line();

    return 0;
}
