#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


unsigned int snooze(unsigned int secs)
{
    unsigned int n = sleep(secs);
    printf("Slept for %d of %d secs.\n", secs - n, secs);

    return n;
}

void handler(int sig)
{
    return;
}

int main(int argc, char *argv[])
{
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s secs.\n", argv[0]);
        exit(1);
    }
    if ((n = atoi(argv[1])) == 0) {
        fprintf(stderr, "Usage: %s is illegal option.\n", argv[1]);
        exit(1);
    }

    if (signal(SIGINT, handler) == SIG_ERR) {
        fprintf(stderr, "Signal error\n");
        exit(1);
    }
    (void)snooze(n);
    exit(0);
}



