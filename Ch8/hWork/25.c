#include "csapp.h"

#define BUFFSIZE 100

sigjmp_buf buf;

void handler(int sig)
{
    siglongjmp(buf, 1);
}

char *tfgets(char *s, int size, FILE *stream) 
{
    if (!sigsetjmp(buf, 1)) {
        alarm(5);   /* 先调用alarm取消待处理的闹钟，避免非当前tfgets调用发出的信号干扰 */
        Signal(SIGALRM, handler);
        return fgets(s, size, stream);
    } else
        return NULL;
}

int main(void)
{
    char buf[BUFFSIZE], *ch;

    ch = tfgets(buf, BUFFSIZE, stdin);

    if (ch == NULL)
        printf("请在5秒内键入输入.\n");
    else
        printf("%s", ch);

    return 0;
}

