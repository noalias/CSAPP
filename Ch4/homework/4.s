# Y86-64 code
# long rsum(long *start, long count)
# start in %rdi, count in %rsi
rsum:
   xorq    %rax,%rax
   andq    %rsi,%rsi
   jle     done
   irmovq  $1,%r8
   irmovq  $8,%r9
   pushq   %r10
   mrmovq  (%rdi),%r10
   addq    %r9,%rdi
   subq    %r8,%rsi
   call    rsum
   addq    %r10,%rax
   popq    %r10
done:
   ret
