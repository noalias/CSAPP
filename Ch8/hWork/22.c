/* 程序mysystem */
#include "../../csapp.h"

int mysystem(char *command);

int main(int argc, char *argv[])
{
    mysystem(argv[1]);

    return 0;
}

    
int mysystem(char *command)
{
    int status;
    char *argv[] = {"/ban/sh", "-c", command, NULL}; 
    if (fork() == 0)
        execve(argv[0], argv, NULL);

    if (waitpid(-1, &status, 0) > 0) {
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        if (WIFSIGNALED(status))
            return WTERMSIG(status);
    }
}
