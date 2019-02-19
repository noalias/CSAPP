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
2. `p && a > \*p`中**&&**操作符具有短路特性，左表达式为零，则不再测试右表达式.
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
