	.file	"74.s"
	.text
	.globl	find_range
	.type	find_range, @function
find_range:
     xorl      %eax,%eax
     vcvtsi2ss %eax,%xmm1,%xmm1
     movl      %eax,%edi
     movl      $1,%esi
     movl      $2,%ecx
     movl      $3,%eax
     vucomiss  %xmm0,%xmm1              # compare 0:x
     cmova     %edi,%eax
     cmovb     %ecx,%eax
     cmove     %esi,%eax
     ret

