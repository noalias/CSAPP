#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 8192            /* 命令行最大输入字符 */
void oops(char *, char *);      /* 错误处理 */
void eval(char *);              /* 执行命令 */


#endif
