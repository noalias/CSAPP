#### 3.8
目的|值
---|---
0x100|0x100
0x108|0xA8
0x118|0x110
0x110|0x14
%rcx|0x0
%rax|0xFD
#### 3.9
*long shift_left4_rightn(long x, long n)*  
*x in %rdi, n in %rsi*  
```
shift_left4_rightn:  
  movq %rdi,%rax  
  salq $4,%rax
  movl %esi,%ecx
  sarq %cl,%rax
```
#### 3.10
```
long arith2(long x, long y, long z)
{
    long t1 = x | y;
    long t2 = t1 << 3;
    long t3 = ~t1;
    long t4 = z - t3;
    return t4;
}
```
#### 3.11
1. 将%rdx置为〇
2. movq $0,%rdx
3. 经过测试，3<7
#### 3.12
_void uremdiv(unsigned long x, unsigned long y, unsigned long *qp, unsigned long *rp)_   
*x in %rdi, y in %rsi, qp in %rdx, rp in %rcx*
```
uremdiv:  
  movq %rdx,%r8
  movq %rdi,%rax
  xorl %edx
  divq %rsi
  movq %rax,(%r8)
  movq %rdx,(%rcx)
```
#### 3.13
1. int <
2. short >=
3. unsigned char <=
4. unsigned long , long ==
#### 3.14
1. long >=
2. unsigned short , short ==
3. unsigned char >
4. int , unsigned <=
#### 3.15
1. 4003fe
2. 400525 #0xf4是补码，所以正确地址是400425
3. 400543 400545
4. 400560
#### 3.16
1. C语言goto版本
```
void cond(long a, long *p)
{
    if (p == 0) 
        goto done;
    if (*p >= a)
        goto done;
    *p = a;
done:
}
```
2. `p && a > *p`中&&操作符具有短路特性，左表达式为零，则不再测试右表达式.
#### 3.17
1. goto的另一种形式
```
long gotodiff_se(long x, long y)
{
    long result;
    if (x < y)
        goto x_l_y;
    ge_cnt++;
    result = x - y;
    return result;
x_l_y:
    lt_cn++;
    result = y - x;
    return result;
}
```
2. 两种表达式都可行，对于无else分支的if语句：
```
t = test_expr;
if (t)
    goto ture;
goto done;
ture:
    then_statement;
done:
t = test_expr;
if (!t)
    goto done;
then_statement;
done:
```
显然上述后者表达式更简洁
#### 3.18
```
long test(long x, long y, long z)
{
    long val = x + y + z;
    if (x < -3) {
        if (y < z)
            val = x * y;
        else
            val = y * z;
    } else if (x > 2)
        val = x * z;
    return val;
}
```
#### 3.19
1. 31 = 16 + 0.5Tmp -> Tmp = 30
2. 16 + 31 = 47
#### 3.20
1. `#define OP ((< 0 ? (x) + 7 : (x)) / )`
2. 注释  
_long arith(long x)_  
_x in %rdi_
```
arith:
  leaq 7(%rdi),%rax   // store x + 7
  testq %rdi,%rdi     // test x
  cmovns %rdi,%rax    // if >= 0, store x
  sarq $3,%rax        // x >>= 3
  ret                 // retrun x
```
#### 3.21
```
long test(long x, long y)
{
    long val = 8 * x;
    if (y > 0) {
        if (x < y) 
            val = y - x;
        else
            val = x & y;
    } else if (y <= -2)
        val = y + x;
    return val;
}
```
#### 3.23
1. x -> %rdi, y -> %rcx, n -> %rdx
2. \*p就是x本身，(\*p)++就是x++；
3. 注释
*long dw_loop(long x)*  
*x initially in %rdi*
```
dw_loop:
  movq %rdi,%rax               // store x
  movq %rdi,%rcx               
  imulq %rdi,%rcx              // y = x*x
  leaq (%rdi,%rdi),%rdx        // n = 2*x
.L2:                           // loop:
  leaq 1(%rcx,%rax),%rax       // x = x + y + 1
  subq $1,%rdx                 // n--
  testq %rdx,%rdx              // test n
  jg .L2                       // if > 0, goto loop
  rep;ret                      // return x
```
#### 3.25
```
long long_while2(long a, long b)
{
    long result = b;
    while (b > 0) {
        result = b * a;
        b = b - a;
    }
    return result;
}
```
#### 3.26
1. 跳转中间
2. c代码
```
long fun_a(unsigned long x)
{
    long val = 0;
    while (x != 0) {
        val ^= x;
        x >>= 1;
    }
    return val & 1;
}
```
3. 返回x位级表示，有多少个1，函数返回值是val & 1，掩码1使val最低位有效，这样在循环中x中的每一位都与val最低位进行异或操作，最终的值反应了x位级表示中有奇数还是偶数个1
#### 3.27
```
long fact_for(long n)
{
    long i = 2;
    long result = 1;
    if (i > n)
        goto done;
loop:
    result *= i;
    i++;
    if (i <= n)
        goto loop;
done:
    return result;
}
```
#### 3.28
1. c代码
```
long fun_b(unsigned long x)
{
    long val = 0;
    long i;
    for (i = 64; i; i--) {
         val = x & 1 | 2 * val;              // val = val << 1 | x & 0x1;
         x >>= 1;
    }
    return val;
}
```
2. i初始为64，再测试i是否等于0，是没有必要的
3. 将x的位级表示颠倒过来
#### 3.29
1. for -> while 循环代码
```
long sum = 0;
long i = 0;
while (i < 10) {
    if (i & 1)
        continue;
    sum += i;
    i++;
}
```
显然表达式`i&1`等于0式，`i++`将被跳过；
2. goto 代码
```
long sum = 0;
long i = 0;
while (i < 10) {
    if (i & 1)
        goto L1;
    sum += i;
L1:
    i++;
}
```
#### 3.30
1. 跳转表
```
.L4:
  .quad   .L9          0 -> -1
  .quad   .L5          1 -> 0
  .quad   .L6          2 -> 1
  .quad   .L7          3 -> 2
  .quad   .L2          4 -> default
  .quad   .L7          5 -> 4 
  .quad   .L8          6 -> 5
  .quad   .L2          7 -> default
  .quad   .L5          8 -> 7
```
C语言标号有：-1,0,1,2,4,5,7,default

2. default, 2和4, 0和7
#### 3.31
``` 
void switcher(long a, long b, long c, long \*dest)
{
    long val;
    switch(a) {
        case 5:
            c = b ^ 15;
            /* Fall through */
        case 0:
            val = c + 112;
            break;
        case 2:
        case 7:
            val = (b + c) << 2;
            break;
        default:
            val = b;
    }
    *dest = val;
}
```
#### 3.32
标号|PC|指令|%rdi|%rsi|%rax|%rsp|\*%rsp|描述
---|---|---|---|---|---|---|---|---
M1|0x400560|callq|10|-|-|0x7fffffffe820|-|调用first(10)
F1|0x400548|lea|10|-|-|0x7fffffffe818|0x400565|计算x+1
F2|0x40054c|sub|10|11|-|0x7fffffffe818|0x400565|计算x-1
F3|0x400550|callq|9|11|-|0x7fffffffe818|0x400565|调用last(9,11)
L1|0x400540|mov|9|11|-|0x7fffffffe810|0x400555|存储9
L2|0x400543|imul|9|11|9|0x7fffffffe810|0x400555|9X11
L3|0x400547|retq|9|11|99|0x7fffffffe810|0x400555|返回
F4|0x400555|retq|9|11|99|0x7fffffffe818|0x400565|返回
M2|0x400565|mov|9|11|99|0x7fffffffe820|-|保存
#### 3.33
`procprob(int a, short b, long *u, char *v)`或`procprob(int b, short a, long *v, char *u)`
#### 3.34
1. a0~a5
2. a6~a7
3. 被调用者寄存器数量有限
#### 3.35
1. %rbx中存储过程rfun的形参
2. c代码
```
long rfun(unsigned long x)
{
    if (x) 
        return 0;
    unsigned long nx = x / 2;
    long rv = rfun(nx);
    return x + rv;
}
```
#### 3.36
数组|元素大小|整个数组的大小|起始地址|元素i
---|---|---|---|---
S|2|14|xS|xS+2i
T|8|24|xT|xT+8i
U|8|48|xU|xU+8i
V|4|32|xV|xV+4i
W|8|32|xW|xW+8i
#### 3.37
表达式|类型|值|汇编代码
---|---|---|---
S+1|short \*|xs+2|leaq 3(%rdx), %rax
S[3]|short|M[xs+6]|movb 6(%rdx), %ax
&S[i]|short \*|xs+2i|leaq (%rdx,%rcx,2), %rax
S[4\*i+1]|short|M[xs+8i+2]|movb 2(%rdx,%rcx,8), %ax
S+i-5|short \*|xs+2i-10|leaq -10(%rdx,%rcx,2), %rax
#### 3.38
*long sum_element(long i, long j)*  
*i in %rdi, j in %rsi*  
```
sum_element
  leaq 0(,%rdi,8), %rdx          //8i
  subq %rdi,%rdx                 //7i
  addq %rsi,%rdx                 //%rdx->7i+j
  leaq (%rsi,%rsi,4), %rax       //5j
  addq %rax,%rdi                 //%rdi->5j+i
  movq Q(,%rdi,8), %rax          //Q[N][M]->8(j*M+i)=8(5j+i)->M=5
  addq P(,%rdx,8), %rax          //P[M][N]->8(i*N+j)=8(7i+j)->N=7
  ret
```
M=5,N=7
#### 3.39
*&D[i][j]=xd+L(Cxi+j)*  
*N=16*  
&A[i][0]=A+4x(ixN+0)=A+4Ni=A+64i  
&B[0][k]=B+4k  
&B[N][k]=B+4(16N+k)=B+4k+1024
#### 3.40
```
void fix_set_diag_opt(fix_matrix A, int val)
{
    int *Aptr = &A[0][0];
    int *Aend = &A[N][N];

    do {
        *Aptr = val;
        Aptr += N + 1;
    } while(Aptr != Aend); 
}
```
#### 3.41
1. p:0; s.x:8; s.y:12; next:16
2. 24
3. C代码
```
void sp_init(struct prob \*sp)
{
    sp->s.x = sp->s.y;
    sp->p = &sp->s.x;
    sp->next = sp;
}
```
#### 3.42
1. C代码
```
long fun(struct ELE \*ptr)
{
    long result = 0;

    while(ptr) {
        result += ptr->v;
        ptr = ptr->p;
    }

    return result;
}
```
2. 实现了数据结构链表，将链表中的数据叠加
#### 3.43
expr|type|代码
---|---|---
up->t1.u|long|movq (%rdi),%rax; movq %rax,(%rsi)
up->t1.v|short|movw 8(%rdi),%ax; movw %ax,(%rsi)
&up->t1.w|char \*|leaq 10(%rdi),%rax; movq %rax,(%rsi)
up->t2.a|int \*|movq %rdi,(%rsi)
up->t2.a[up->t1.u]|int|movq (%rdi),%rax; movl (%rdi,%rax,4),%edx; movl %edx,(%rsi)
\*up->t2.p|char|movq 8(%rdi),%rax; movb (%rax),%al; movb %al,(%rsi)
#### 3.44
标识符|元素1|元素2|元素3|元素4|数据总量
---|---|---|---|---|---
P1|0|4|8|12|16字节
P2|0|4|5|8|16字节
P3|0|6|-|-|10字节
P4|0|16|-|-|40字节
P5|0|24|-|-|40字节
P5中结构的对齐应该参照结构的字节数
#### 3.45
1. 字节偏移量
标识符|a|b|c|d|e|f|g|h
---|---|---|---|---|---|---|---|---
偏移|0|8|16|24|32|40|48|56|
2. 64个字节
3. 重排d->f->b->h->a->c->e->g

