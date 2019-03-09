## HCL语言
### 组合逻辑
基本构成：
- 布尔表达式：ADN->`&&`,OR->`||`,NOT->`!`
  > 表达式`bool eq = (a && b) || (!a && !b);`表示位相等的组合逻辑，这里**类型**bool表示一位，即其修饰下的信号为0或1；eq表示组合逻辑的**输出**，a和b是组合逻辑的**输入**；其功能是，ab相等时，eq为1，否则为0。
- 判等表达式:`==`
  > **位**级信号用bool修饰，而**字**级信号用int修饰；表达式`bool eq = (A == B);`表示字A和字B是否相等，其输出是位级信号eq。
- 情况表达式：`[ select1 : expr1; select2 : expr2; ... selectk : selectk; ]`
  > 下式表达了，在控制信号s下，输出为字A，默认输出字B。情况表达式并不显示输入字。
```
word Out = [
    s : A;
    1 : B;
];
```
- 集合：`in {..}`
  > 表达式`bool s1 = code == 2 || code == 3`，表示code为2或3时，s1为1，可简化为`bool s1 = code in {2， 3}；`，集合表达式得到的是一个位级信号。
## 硬件及HCL描述
### Y86-64的指令执行框架及硬件组成
#### 取指阶段  
取指阶段包括指令内存(只读存储器)硬件单元和PC增加器。  
1. **指令内存**接受时钟信号控制，输入为PC，输出包括：icode、ifun、rA、rB及valC,错误信号imem_error。根据need_regids信号输出rA、rB及valC。
```
int icode = [
    imem_error : INOP;
    1 : icode;
];
bool need_regids = 
    icode in { IRRMOVQ, IIRMOVQ, IRMMOVQ, IMRMOVQ, IOPQ, IPUSHQ, IPOPQ };
#need_regids 为1时，rA：rB被设置成0xFF，同时valC输出字节1-8(从0算起)；否则，rA：rB输出字节1，valC输出字节3-9
```
2. **PC增加器**，输入为PC，信号need_valc、need_regids，输出valP。
```
#PC的值为p, 指令字段长度1，寄存器字段长度1*r(r为need_regids),valc字段长度8*i(need_valc)
word valp = p + 1 + r + 8*i
```
#### 译码和写回阶段  
此阶段包括寄存件文件。  
1. **寄存件文件**受时钟信号控制，输入valE(ALU计算输出)、valM(数据内存读出)，输出寄存器rA的值valA、寄存器rB的值valB，接受信号写端口dstE、dstM，读端口srcA及srcB控制。
```
#译码阶段,根据srcA、srcB端口输入的寄存器id,取出rA、rB或%rsp寄存器中的值
word srcA = [                # 此端口输入rA id
    icode in { IOPQ, IRRMOVQ, IRMMOVQ, IPUSHQ } : rA;
    icode in { IPOPQ, IRET } : RRSP;
    1 : RONE;
];
word srcB = [
    icode in { IOPQ, IRMMOVQ, IMRMOVQ } : rB;
    icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
    1 : RONE;
];
#写回阶段，根据dstE、dstM端口输入寄存器id，在相应寄存器上写入值
word dstE = [                    # 在rB对应的寄存器上写ALU入计算的值valE
    icode in { IRRMOVQ } && cnd : rB; # 当条件传送时，根据条件cnd选择传送
    icode in { IOPQ, IIRMOVQ } : rB;
    icode in { IPUSHQ, IPOPQ, ICALL, IRET } : RRSP;
    1 : RONE;
];
word dstM = [                    # 在rA对应的寄存器上写入从数据内存读出的值valM
    icode in { IMRMOVQ, IPOPQ } : rA;
    1 : RONE;
];
```
#### 执行阶段
此阶段包含算术/逻辑单元(ALU)。
1. ALU的输入是aluA及aluB,输出是valE，受alufun控制进行不同计算。
```
word aluA = [
    icode in { IOPQ, IRRMOVQ } : valA;
    icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ } : valC;
    icode in { IPUSHQ, ICALL } : 8;
    icode in { IPOPQ, IRET } ： -8；
];
word aluB = [
    icode in { IOPQ, IRMMOVQ, IMRMOVQ, IPUSHQ, IPOPQ, ICALL, IRET } : valB;
    icode in { IRRMOVQ, IIRMOVQ } : 0;
];
word alufun = [
    icode in { IOPQ } : ifun; # 执行opq指令时，根据ifun执行相关的运算
    i : ALUADD; # 其他情况执行加法
];
bool set_cc = icode in { IOPQ }; # 在执行哦opq命令时，设置条件码
# 信号cnd根据条件码set_cc与功能码ifun进行设置
```
#### 访存
