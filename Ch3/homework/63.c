/* (gdb) x/6gx 0x4006f8 跳转表是包含代码代码地址的数组
 * 按照给出的地址依次排列：
 * 0x 00 00 00 00 00 00 4005a1          0 -> L0
 * 0x 00 00 00 00 00 00 4005c3          1 -> L1
 * 0x 00 00 00 00 00 00 4005a1          2 -> L0
 * 0x 00 00 00 00 00 00 4005aa          3 -> L3
 * 0x 00 00 00 00 00 00 4005b2          4 -> L4
 * 0x 00 00 00 00 00 00 4005bf          5 -> L5
 *
 * long switch_prob(long x, long n)
 * x in %rdi, n in %rsi
 *
 *   sub  $0x3c,%rsi              n -= 60
 *   cmp  $0x5,%rsi               cmp n:5
 *   ja   4005c3                  if > , goto .L1
 *   jmpq *0x4006f8(,%rsi,8)      goto n
 * .L0:                           n = 0, 2
 *   lea  0x0(,%rdi,8),%rax       result = 8x
 *   retq                         break
 * .L3:                           n = 3
 *   mov  %rdi,%rax               
 *   sar  $0x3,%rax               result = x >> 3
 *   retq                         break
 * .L4:                           n = 4
 *   mov  %rdi,%rax               
 *   shl  $0x4,%rax               
 *   sub  %rdi,%rax               result = 15 * x
 *   mov  %rax,%rdi               x *= 15
 * .L5:                           n = 5
 *   imul %rdi,%rdi               x *= x
 * .L1:                           default
 *   lea  0x4b(%rdi),%rax         result = x + 75
 *   retq
 */
 
long switch_prob(long x, long n)
{
    long result = x;
    switch (n) {
        case 60:
        case 62: result <<= 3;
                 break;
        case 63:
                 result >>= 3;
                 break;
        case 64:
                 x *= 15;
        case 65:
                 x *= x;
        default:
                 result = x + 75;
                 break;
    }
    return result;
}

