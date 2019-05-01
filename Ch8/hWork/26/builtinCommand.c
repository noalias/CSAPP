#include "myhead.h"

static void jobs(int argc, char **argv);
static void cont(int argc, char **argv);

#define COMNUM 5

int builtinCommand(int argc, char **argv,)
{
    char *command[COMNUM] = {"quit", "&", "jobs", "bg", "fg"};
    int i;

    for (i = 0; i < COMNUM; i++) 
        if (!strcmp(argv[0], command[i])) break;

    if (i == 0) exit(0);
    else if (i < COMNUM) {
        if (i == 2) jobs(argc, argv);
        if (i == 3) {
            cont(argc, argv);
            bg = 0;
        }
        if (i == 4) cont(argc, argv);
        return 1;
    }

    return 0;
}

static void jobs(int argc, char **argv)
{
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return;
    }

//    printf("jobs\n");

    return 0;
}
    

static void cont(int argc, char **argv)
{
    pid_t pid; 
    char *str_to_num = argv[1];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s JID or PID\n", argv[0]);
        return;
    }

    if (str_to_num[0] == '%')
        str_to_num++;
    pid = (pid_t)strtol(str_to_num, NULL, 10); /* 将PID和JID转化为pid_t型 */

    if (kill(pid, SIGCONT) < 0)
        oops("kill");
}
