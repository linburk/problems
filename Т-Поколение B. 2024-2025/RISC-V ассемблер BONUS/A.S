.global main

.section .data
__fin: .asciz "%lld"
__fout: .asciz "%lld\n"

.macro read_int
addi sp, sp, -16
sd ra, 0(sp)
la a0, __fin
addi a1, sp, 8
call scanf
ld a0, 8(sp)
ld ra, 0(sp)
addi sp, sp, 16
.endm

.macro write_int
addi sp, sp, -8
sd ra, 0(sp)
add a1, zero, a0
la a0, __fout
call printf
ld ra, 0(sp)
addi sp, sp, 8
.endm

.section .text

main:
  read_int
  mv s0, a0
  read_int
  mv s1, a0

  add a0, s0, s1
  write_int
  
  sub a0, s0, s1
  write_int
  
  mul a0, s0, s1
  write_int
  
  div a0, s0, s1
  write_int
  
  div a0, s0, s1
  mul t0, s1, a0
  sub a0, s0, t0
  write_int
  
  xor a0, s0, s1
  write_int
  
  and a0, s0, s1
  write_int
  
  or a0, s0, s1
  write_int

  addi a0, zero, 0
  ret
