# Y86-64 Code
# long absSum(long *start, long count)
# start in %rdi, count in %rsi
sum:
  irmovq     $8,%r8
  irmovq     $1,%r9
  xorq       %rax,%rax
  andq       %rsi,%rsi
  jmp        test
loop:
  mrmovq     (%rdi),%r10
  andq       %r10,%r10
  jl         neg
  addq       %r10,%rax
  addq       %r10,%rax
neg:
  subq       %r10,%rax
  addq       %r8,%rdi
  subq       %r9,%rsi
test:
  jne        loop
  ret
