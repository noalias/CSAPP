#### 3.8
目的|值
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
*void uremdiv(unsigned long x, unsigned long y, unsigned long *qp, unsigned long *rp)*
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
