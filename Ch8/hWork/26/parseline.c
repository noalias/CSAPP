#include "myhead.h"

int parseline(char *buf, char **argv, int argv)
{
    char *delim;
    int argc;
    int bg;

    buf[strlen(buf)-1] = ' ';
    while (*buf && (*buf == ' '))
        buf++;

    argc = 0;

    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' '))
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0)
        return 1;

    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}
