## 异常控制流
程序内部状态的变化，引起的控制转移，叫做__处理器的控制流__。

计算机系统对控制流的突变产生的反应，叫做**异常控制流**；有三个层次：_硬件层_，硬件检测到的事件触发控制转移到异常处理程序，_操作系统层_，内核通过上下文切换将控制从一个用户进程转移到另一个用户进程，_应用层_，一个进程发送信号到另一个进程，接收者会将控制转移到它的一个信号处理程序。

应用层异常控制流的一个实例，**非本地跳转**：一个程序违反通常的调用/返回栈规则的跳转来响应错误。
### 异常
处理器执行指令时，当出发事件后，通过异常表调用异常处理程序，来处理事件；异常处理程序完成后，将控制返回给1）当前指令，2）下一条指令，3）终止被中断的程序。

异常的种类：
1. **中断**：为处理由I/O设备发出的信号而引发的异常，中断不会对控制流造成影响，这样就好像中断是异步发生的，所以中断又叫异步异常。
2. **陷阱或系统调用**：陷阱是控制流调用系统调用过程主动触发的异常，系统调用处理后，返回下一条指令。
3. **故障**：由错误引起，故障程序处理后，将返回至当前指令或和终止程序。
4. **终止**：由致命错误引起，处理程序将终止程序。
### 进程
**进程**是程序运行的一个实例，在系统中任何一个程序都运行在一个进程的上下文中；上下文是指程序正常运行所需的状态，包括：程序在内存存放的数据、代码、栈、通用目的寄存器的内容、程序计数器、环境变量及打开的文件描述符。

进程的两个抽象：1）独立的逻辑控制流，2）私有的地址空间。

#### 进程逻辑流
每个进程的PC序列值叫做逻辑控制流；一个逻辑流与另一个逻辑流在时间上重叠，称为并发流；
> 流X和流Y相互并发，当且仅当X在Y开始之后和Y结束之前开始，或者Y在X开始之后或者结束之前开始。

如果两个流并发的运行在不同的处理器核或计算机上，称为**并行流**。
#### 进程地址空间
进程拥有自己的私有地址空间，地址空间中某个地址对应的内存字节是不能被其他进程读写的。但所有进程地址空间都有相同的通用结构；代码段总是从0x400000开始，之后是从可执行文件加载的只读代码段、读写代码段，然后是由malloc创建的堆，以及共享库内存映射区，用户栈；用户栈从地址2^48-1向下增长，2^48网上为内核数据段，无法被用户访问。

#### 进程上下文切换
处理器通过某个控制寄存器的模式位控制进程的访问权限，设置位模式时，进程运行在内核模式中，此时进程可以执行指令集中所有指令、访问系统中所有内存位置；没有设置位模式时，进程运行在用户模式，此时进程权限受到限制，进程只能通过系统调用访问内核代码和数据。

初始时，进程在用户模式中运行，进程可以通过异常从用户模式变为内核模式。操作系统内核使用上下文切换的异常控制流来实现多任务（上下文切换是建立在低层次异常机制上），内核为每个进程维护一个上下文（内核重新启动一个被抢占的进程所需的状态），内核**调度**进程（抢占当前运行的进程，启动之前被抢占的进程）是使用上下文切换实现的。 
>上下文切换：1）保存当前进程上下文，2）恢复先前被抢占进程的上下文，3）将控制传递给新恢复的进程。

上下文切换过程中，内核将代替被抢占的进程及新启动的进程运行，直至恢复为新启动进程上下文。

### 进程控制
操作进程主要有以下系统调用。
```c
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t getpid(void);       /* 返回调用者进程ID */
pid_t getppid(void);      /* 返回调用者父进程ID */

void exit(int status);    /* 以status退出状态来终止进程 */

pid_t fork(void);         /* 调用者创建一个子进程，父进程中返回子进程PID，子进程中返回0，出错则为-1 */
pid_t waitpid(pid_t pid, int *statusp, int options); /* 等待进程终止，返回进程PID */

unsigned sleep(unsigned secs); /* 将进程挂起指定的时间，返回还要休眠的秒数 */
int pause(void);           /* 让进程休眠，直到收到一个信号 */

int execve(const char *filename, const char *argv[], const char *envp[]);                 /* 加载并运行一个新程序 */
```

以上，fork系统调用将创建一个子进程，子进程拥有父进程的上下文副本，父子进程并发运行，由于有相同的文件描述符，父子进程在运行时，共享同一文件。

execve系统调用加载新程序，新程序将覆盖前程序的地址空间，但PID不变。execve函数运行后，进程将以新程序终止。
```c
// 加载程序pro1
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
    // 加载pro2后此后的指令将不会运行
    printf("PID is %d.\n", (int)getpid());        
    exit(100);
}

// 被加载程序pro2
#include <stdlib.h>

int main(void)
{
    return 200;           // pro2被加载后程序退出状态为200
}

----------------------------------------------------------
命令行下运行：
> ./pro1 pro2
> echo $?
> 200

```
### 信号
内核和进程通过**信号**中断其它进程。

#### 发送信号
内核通过更新目的进程上下文的某个状态，发送一个进程给目的进程。发送信号的原因：1）内核监测到一个系统事件，2）进程调用了kill函数，显示要求内核发送一个信号给目的进程。

向进程发送信号是基于进程组，每个进程只属于一个进程组。
```c
#include <unistd.h>
pid_t getpgrp(void);             /* 返回进程的进程组ID */
int setpgid(pid_t pid, pid_t pgid); /* 更改当前进程的进程组ID */
```
1. 使用`/bin/kill`程序向进程发送信号
```sh
> /bin/kill -9 15213            # 发送信号9给进程15213
> /bin/kill -9 -15213           # 发送信号9给进程组15213中的每个进程
```
2. 使用键盘发送信号，shell中`Ctrl+c`终止前台作业，`Ctrl+z`挂起前台作业。
3. 使用函数发送信号
```c
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int kill(pid_t pid, int sig);        /* 向进程pid发送信号sig */
unsigned alarm(unsigned secs);       /* secs秒后向调用进程发送信号SIGALRM */
```
#### 接收信号
目的进程被内核强迫对信号作出反应，被称为接收信号。进程可以忽略、终止或通过执行信号处理程序捕获信号。
> 信号处理程序是如何捕获到信号的？

发出而未被接收的信号，为_待处理信号_。一种信号最多有一个待处理信号。当一个类型为K信号发出时，内核会设置目的进程中的`pending`位向量K位，当K信号被目的进程接受，`pending`位向量K位被内核清除；当目的进程有一个K类型待处理信号，接下来的发送的K类型信号将被丢弃；目的进程可以**阻塞**待处理信号，使待处理信号不被接受，此时内核会设置`blocked`位向量。

内核把进程从内核模式切换到用户模式时(如系统调用返回，或完成一次上下文切换），内核检查进程的未被阻塞的带处理信号(pending & ~blocked)，如果集合非空，内核将控制传递给下一个指令，否则，内核强制进程接收信号（通常是值最小的信号，这表明进程每次接收一次信号？）；收到信号后，进程会触发进程采取某种行为，完成行为后，进程将进入逻辑流下一条指令。

每种信号都能触发进程默认行为，可以通过函数更改进程对信号的默认行为
```c
#include <signal.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
/* 如果handler是SIG_IGN，那么忽略signum
 * 如果handler是SIG_DFL, 那么恢复signum信号的默认行为
 * 如果handler是用户定义的函数地址，就会调用此函数
 */
```
`handler`为信号处理程序，`signal`设置信号处理程序，调用信号处理程序称为_捕获信号_，执行信号处理程序被称为_处理信号_。

> 对`signal`函数的理解:  
> signal函数改变了内核强制目的进程对信号反应的行为，使`handler`函数替代了默认的处理程序，当进程的上下文切换后，内核检测到待处理信号，并强制进程调用`handler`函数。

```c
/* pro1 在发送信号前安装处理程序，这样处理程序总是可用 */
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
    if (signal(SIGINT, handler) == SIG_ERR) {   /* 安装处理程序 */
        fprintf(stderr, "%s", "signal error");
        exit(0);
    }

    for (i = 0; i < 10; i++) {                   /* 在某一刻，发送Ctrl+C信号 */
        printf("请发送信号！\n");
        sleep(1);
    }

    exit(2);
}

-----------------------------------------------------
命令行： ./pro1
> 请发送信号！
> 请发送信号！
> 请发送信号！
> Ctrl+C
> Caught SIGINT!
> 请发送信号！
> 请发送信号！
> 请发送信号！
> Ctrl+C
> Caught SIGINT!
此时程序继续运行
-----------------------------------------------------
/* pro2 在发送信号后安装处理程序，这样信号不能及时传递到处理程序 */
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
    for (i = 0; i < 10; i++) {                   /* 在某一刻，发送Ctrl+C信号 */
        printf("请发送信号！\n");
        sleep(1);
    }

    if (signal(SIGINT, handler) == SIG_ERR) {   /* 安装处理程序 */
        fprintf(stderr, "%s", "signal error");
        exit(0);
    }
    exit(2);
}

-----------------------------------------------------
命令行： ./pro2
> 请发送信号！
> 请发送信号！
> 请发送信号！
> Ctrl+C
此时程序退出
```
#### 阻塞和解除阻塞信号
隐式阻塞，内核默认阻塞当前处理程序正在处理的信号类型的待处理信号。

显式阻塞，程序调用`sigprocmask`函数和它的辅助函数，明确的阻塞和解除阻塞选定的信号。
```c
#include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);   /* 根据how设置blocked位，并将旧blocked保存在oldset中 */
int sigemptyset(sigset_t *set); /* 将集合设置为0x0 */
int sigfillset(sigset_t *set);  /* 将集合设置为~0x0 */
int sigaddset(sigset_t *set, int signum); /* 将信号signum添加到集合中 */
int sigdelset(sigset_t *set, int signum); /* 将信号signum从集合中删除 */
int sigismember(const sigset_t *set, int signum); /* 测试信号signum是否在集合中 */
```

#### 信号处理程序

#### 非本地跳转
非本地跳转，将控制直接从一个函数转移到另一个当前正在执行的函数。
```c
#include <setjmp.h>
int setjmp(jmp_buf env);         /* 将当前调用环境保存在env中，并返回0 */
int sigsetjmp(sigjmp_buf env. int savesigs);  

#include <setjmp.h>
void longjmp(jmp_buf env, int retval);  /* 调用longjmp函数后，释放env中的调用环境，即当前环境切换为最近一次调用setjmp的环境，并使setjmp返回retval */
void siglongjmp(sigjmp_buf env, int retval);
```
