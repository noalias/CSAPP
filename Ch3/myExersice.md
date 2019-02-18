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
shift_left4_rightn:  
  movq %rdi,%rax  
  salq $4,%rax
  movl %esi,%ecx
  sarq %cl,%rax
