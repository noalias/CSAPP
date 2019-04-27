#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void handler(int sig)
{
    printf("Caught SIGINT!\n");
    return;
}

int main(void)
{
    int i;
    for (i = 0; i < 10; i++) {
        printf("请发送信号！\n");
        sleep(1);
    }

    if (signal(SIGINT, handler) == SIG_ERR) {
        fprintf(stderr, "%s", "signal error");
        exit(0);
    }

    exit(2);
}
