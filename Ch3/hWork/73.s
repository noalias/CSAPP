	.file	"73.s"
	.text
	.globl	find_range
	.type	find_range, @function
find_range:
     xorl      %eax,%eax
     vcvtsi2ss %eax,%xmm1,%xmm1
     vucomiss  %xmm0,%xmm1              # compare 0:x
     jp        .L0
     ja        .L1                      # if 0 > x, goto done
     je        .L2
     jb        .L3
 .L0:
     addl      $1,%eax
 .L3:
     addl      $1,%eax
 .L2:
     addl      $1,%eax
 .L1:
     ret

