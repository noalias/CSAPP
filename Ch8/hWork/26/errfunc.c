#include "myhead.h"

void oops(char *funcname)                 /* 打印函数出错信息 */
{
    fprintf(stderr, "%s ", funcname);
    perror("error");
    exit(1);
}
