#include "myhead.h"

void eval(char *cmdline)
{
    char *argv[MAXARGV];  /* 存储参数 */
    int argc;             /* 存储参数数量 */
    bool bg;
    pid_t pid;

    bg = parseline(cmdline, argv, &argc);       /* 解析命令行，并填充argv参数,返回当前命令是否前台或后台运行 */

    if (argv[0] == NULL)            /* 无输入内容直接返回 */
        return;

    if (!builtinCommand(argc, argv)) {
        if ((pid = fork()) == 0) 
            if (execve(argv[0], argv, NULL) == -1)
                oops("execve");
        if (pid == -1)
            oops("fork");
        if (!bg) {
            int status;
            if (waitpid(pid, $status, 0) < 0)
                oops("waitpid");
        }

    }


}


