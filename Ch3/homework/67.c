/* strB process(strA s)
 * process:
 *       movq  %rdi,%rax         store &r
 *       movq  24(%rsp),%rdx     store s.p
 *       movq  (%rdx),%rdx       store *s.p
 *       movq  16(%rsp),%rcx     
 *       movq  %rcx,(%rdi)       r.u[o] = s.a[1]
 *       movq  8(%rsp),%rcx
 *       movq  %rcx,8(%rdi)      r.u[1] = s.a[0]
 *       movq  %rdx,16(%rdi)     r.q = *s.p
 *       ret                     return &r
 *
 * long eval(long x, long y, long z)
 * x in %rdi, y in %rsi, z in %rdx
 * eval:
 *    subq  $104,%rsp            建立栈帧
 *    movq  %rdx,24(%rsp)        store z
 *    leaq  24(%rsp),%rax        store &z
 *    movq  %rdi,(%rsp)          s.a[0] = x
 *    movq  %rsi,8(%rsp)         s.a[1] = y
 *    movq  %rax,16(%rsp)        s.p = &z
 *    leaq  64(%rsp),%rdi        store &r
 *    call  process
 *    movq  72(%rsp),%rax        r.u[1]
 *    addq  64(%rsp),%rax        r.u[1] + r.u[0]
 *    addq  80(%rsp),%rax        r.u[1] + r.u[0] + r.q
 *    addq  $104,%rsp            释放栈帧
 *    ret
 *
 *
 *  A. 栈帧：
 *   --------(空)            %rsp+104
 *   --------(空)            %rsp+96
 *   --------(空)            %rsp+88
 *   --------(空)            %rsp+80
 *   --------(空)            %rsp+72
 *   --------(空)            %rsp+64
 *   --------(空)            %rsp+56
 *   --------(空)            %rsp+48
 *   --------(空)            %rsp+40
 *   --------(空)            %rsp+32
 *   --------(z )            %rsp+24
 *   --------(s.p = &z)      %rsp+16
 *   --------(s.a[1] = y)    %rsp+8
 *   --------(s.a[0] = x)    %rsp
 *  B. %rsp+64 表示strA s的地址
 *  C. 以%rsp+8为基址，访问s.a[0] = M[%rsp+8]，s.a[1] = M[%rsp+16]，s.p = M[%rsp+24]，在调用process时，%rsp指向返回地址
 *  D. 以%rdi为基址，访问r.u[0] = M[%rdi]，r.u[1] = M[%rdi+8]，r.q = M[%rdi+16]
 *  E. 栈帧:
 *   --------(空)            %rsp+104
 *   --------(空)            %rsp+96
 *   --------(空)            %rsp+88
 *   --------(r.q)           %rsp+80
 *   --------(r.u[1])        %rsp+72
 *   --------(r.u[0])        %rsp+64
 *   --------(空)            %rsp+56
 *   --------(空)            %rsp+48
 *   --------(空)            %rsp+40
 *   --------(空)            %rsp+32
 *   --------(z )            %rsp+24
 *   --------(s.p = &z)      %rsp+16
 *   --------(s.a[1] = y)    %rsp+8
 *   --------(s.a[0] = x)    %rsp
 *   以%rsp+64为基址，访问r.u[0] = M[%rsp+64]，r.u[1] = M[%rsp+72]，r.q = M[%rsp+80]
 *  F.传递入函数的结构参数和返回的结构值,都是建立在调用者函数的栈帧上
 */
