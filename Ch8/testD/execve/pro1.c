#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[])
{
    if (execve(argv[1], &argv[1], environ) < 0) {
        printf("%s: Command not found.\n",argv[1]);
        exit(-1);
    }

    printf("PID is %d.\n", (int)getpid());
    exit(100);
}
