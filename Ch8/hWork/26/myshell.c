#include "myhead.h"

#define ARGUS 128

int main(void)
{
    char cmdline[ARGUS];

    initjobs();

    while (1) {
        printf("> ");
        if (fgets(cmdline, MAXLINE, stdin) == NULL)
            oops("fgets");

        eval(cmdline);
    }

    return 0;
}
