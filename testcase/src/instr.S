#include "trap.h"

// about 325 instrs per round

.globl start
start:
  mov $0x1000000, %esp
  mov $1, %eax
  cmp $1, %eax
  jne bad
  mov $30769, %eax // test for 10000000 instrs
  jmp loop_test
loop_main:
  call arith_test
  call ctrl_trans_test
  call data_trans_test
  call logic_test
  call string_test
  mov 0x10000, %eax
  sub $1, %eax
loop_test:
  mov %eax, 0x10000
  test %eax, %eax
  jnz loop_main
  HIT_GOOD_TRAP

string_test:
  // movs
  movb $1, 0x123456
  movb $2, 0x123457
  movb $3, 0x123458
  movb $4, 0x123459
  movb $5, 0x12345a
  movb $6, 0x12345b
  mov $0x123456, %esi
  mov $0x223456, %edi
  mov $3, %ecx
  rep movsw
  cmpl $0x04030201, 0x223456
  jne bad
  cmpw $0x0605, 0x22345a
  jne bad
  // stos
  mov $0x04, %ax
  mov $0x223456, %edi
  mov $5, %ecx
  stosb
  rep stosb
  cmp $0x22345c, %edi
  jne bad
  cmpl $0x04040404, 0x223456
  jne bad
  cmpw $0x0404, 0x22345a
  jne bad
  // cmps
  mov $5, %ecx
  mov $0x123456, %esi
  mov $0x223456, %edi
  cmpsb
  je bad
  repne cmpsb
  cmp $2, %ecx
  jne bad
  ret

logic_test:
  // and
  mov $0x12345678, %ecx
  mov $0xfedcba90, %edx
  mov %ecx, %eax
  and %edx, %eax
  cmp $0x12141210, %eax
  jne bad
  // or
  mov %ecx, %eax
  or %edx, %eax
  cmp $0xfefcfef8, %eax
  jne bad
  // not
  mov %ecx, %eax
  not %eax
  cmp $0xedcba987, %eax
  jne bad
  // xor
  mov %ecx, %eax
  xor %edx, %eax
  cmp $0xece8ece8, %eax
  jne bad
  // shrd
  mov %ecx, %eax
  shrd %cl, %edx, %eax
  cmp $0xdcba9012, %eax
  jne bad
  // sar
  sar $4, %eax
  cmp $0xfdcba901, %eax
  jne bad
  // shr
  shr $4, %eax
  cmp $0x0fdcba90, %eax
  jne bad
  // shld
  shld $4, %edx, %eax
  cmp $0xfdcba90f, %eax
  jne bad
  // shl
  shl $8, %eax
  cmp $0xcba90f00, %eax
  jne bad
  // test
  test $0x80000000, %eax
  jns bad
  // setcc
  sets %al
  cmp $1, %al
  jne bad
  ret

data_trans_test:
  // cwtl
  mov $0xfff001, %eax
  cwtl
  cmp $0xfffff001, %eax
  jne bad
  // cltd
  mov $0xff, %edx
  mov $1, %eax
  cltd
  cmp $0, %edx
  jne bad
  // leave
  call test_leave
  // mov
  mov $12345, %eax
  mov %eax, %ecx
  mov %ecx, %edx
  mov %edx, -5(%esp, %eax, 4)
  mov $4, %edx
  mul %edx
  mov %esp, %edx
  add %eax, %edx
  sub $5, %edx
  mov (%edx), %ebx
  cmp %ebx, %ecx
  jne bad
  // movsx
  mov $0xf0, %eax
  movsbl %al, %ecx
  cmp $0xfffffff0, %ecx
  jne bad
  // movzx
  movzbl %al, %ecx
  cmp $0xf0, %ecx
  jne bad
  // pop
  sub $4, %esp
  movl $0x12345678, (%esp)
  pop %ecx
  cmp $0x12345678, %ecx
  jne bad
  // push
  pushw $0x1234
  pop %dx
  cmp $0x1234, %dx
  jne bad
  // xchg
  mov $0x7788, %ebx
  mov %ebx, %ecx
  mov %edx, %eax
  xchg %ecx, %eax
  cmp %eax, %ebx
  jne bad
  cmp %edx, %ecx
  jne bad
  ret
test_leave:
  push %ebp
  mov %esp, %ebp
  sub 0x10000, %esp
  leave
  ret

ctrl_trans_test:
  // jmp
  jmp jmp_test0
  jmp bad
jmp_test0:
  // jcc
  mov $3, %eax
  cmp $0, %eax
  jz bad
  js bad
  jc bad
  jo bad
  jnp bad
  cmp $5, %eax
  jo bad
  jz bad
  jnc bad
  jns bad
  jp bad
  cmp $0x80000000, %eax
  jno bad
  cmp %eax, %eax
  jnz bad
  // call
  call call_test0
call_ret_pos:
  jmp bad
  // ret
  lea ret_ret_pos, %ebx
  push %ebx
  jmp ret_test0
  jmp bad
  jmp bad
  jmp bad
ret_ret_pos:
  ret
call_test0:
  pop %eax
  lea call_ret_pos, %edx
  cmp %eax, %edx
  jne bad
  add $5, %eax
  jmp *%eax
ret_test0:
  ret

arith_test:
  // add
  mov $0x12, %al
  add $0xef, %al
  call test_cf
  mov $2147420000, %ecx
  add $100000, %ecx
  call test_of
  mov $0xffff0000, %ecx
  add $0x10000, %ecx
  call test_zf
  // sub
  mov $0, %eax
  sub $1, %eax
  call test_cf
  mov $0x7fffffff, %eax
  sub $0xffffffff, %eax
  call test_of
  mov $0xffffffff, %eax
  sub $0xffffffff, %eax
  call test_zf
  mov $0, %edx
  sub $0xffffffff, %edx
  call test_pf
  // adc
  call set_cf
  mov $0xffffffff, %eax
  adc $0, %eax
  call test_cf
  mov $0, %eax
  cmp $0, %eax
  mov $0xffffffff, %eax
  adc $1, %eax
  call test_zf
  // sbb
  mov $0, %eax
  call set_cf
  sbb $0, %eax
  call test_cf
  cmp $0xffffffff, %eax
  jne bad
  // inc
  mov $0x7fff, %ax
  inc %ax
  call test_of
  // dec
  dec %ax
  call test_of
  cmp $0x7fff, %ax
  jne bad
  // mul
  mov $1010101, %eax
  mov $808808808, %ecx
  mul %ecx
  cmp $0xa664d688, %eax
  jne bad
  cmp $0x2e709, %edx
  jne bad
  // imul
  imul $-50, %edx, %ecx
  cmp $-9510850, %ecx
  jne bad
  imul $-50, %ecx
  cmp $475542500, %ecx
  jne bad
  // div
  mov $0, %edx
  mov %ecx, %eax
  mov $65, %ecx
  div %ecx
  cmp $7316038, %eax
  jne bad
  // idiv
  mov $0xffffec00, %edx
  mov $0x353523a7, %eax
  mov $12345678, %ecx
  idiv %ecx
  cmp $-8350329, %edx
  jne bad
  cmp $-1781136, %eax
  jne bad
  // neg
  mov $12345678, %eax
  lea -1(%eax), %ecx
  not %ecx
  neg %eax
  cmp %eax, %ecx
  jne bad
  ret

test_cf:
  push %eax
  setc %al
  test %al, %al
  jz bad
  pop %eax
  ret

test_of:
  push %eax
  seto %al
  test %al, %al
  jz bad
  pop %eax
  ret

test_zf:
  push %eax
  setz %al
  test %al, %al
  jz bad
  pop %eax
  ret

test_pf:
  push %eax
  setp %al
  test %al, %al
  jnz bad
  pop %eax
  ret

set_cf:
  push %eax
  mov $0, %eax
  cmp $1, %eax
  pop %eax
  ret

set_of:
  push %eax
  mov $0x7fffffff, %eax
  cmp $0xffffffff, %eax
  pop %eax
  ret

bad:
  HIT_BAD_TRAP

