#include "csapp.h"

int main()
{
    pid_t pid;
    int i, status;

    for (i = 0; i < 2; i++)
        if ((pid = Fork()) == 0) {
            int *i = NULL;
            *i = 1;                   /* 访问非法地址 */
        }

    while ((pid = waitpid(-1, &status, 0)) > 0)
        if (WIFSIGNALED(status)) {
            fprintf(stderr, "child %d terminated by signal %d: ", pid, WTERMSIG(status));
            psignal(WTERMSIG(status), NULL);
        } else 
            printf("child %d terminated abnormally\n", pid);


    if (errno != ECHILD)
        unix_error("waitpid error");

    return 0;
}
