#typedef __int 128 int128_t;
#void store_prod(int128_t *dest, int64_t x, int64_t y)
#{
#    *dest = x * (int128_t) y;
#}

store_prod:
  movq     %rdx, %rax       # y -> %rax
  cqto                      # 扩展y符号位到%rdx
  movq     %rsi, %rcx       # 准备x符号位
  sarq     $63,  %rcx       # 扩展x符号位到%rcx
  imulq    %rax, %rcx       # x_l * y_h (高64位)
  imulq    %rsi, %rdx       # y_l * x_h (高64位)
  addq     %rdx, %rcx       # 上述两式相加
  mulq     %rsi             # x * y -> 高64位存储在%rdx中，低64位在%rax中
  addq     %rcx, %rdx       # %rdx存储x*y中的高64位
  movq     %rax, (%rdi)
  movq     %rdx, 8(%rdi)
  ret

# 128位的xy相乘，可扩展为(2^64 * x_h + x_l) * (2^64 * y_h + y_l) = 2^128 * x_h * y_h + 2^64 * x_h * y_l + 2^64 * y_h * x_l + x_l * y_l 
# 上式中2^128 * x_h * y_h = (x_h * y_h) << 128超出了128位，该值为零，故只要求出后三式即可
