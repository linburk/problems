.global main

.section .data
fmts: .asciz "%lld"
fmtp: .asciz "%lld\n"

.macro scan_int // scan a0
  addi sp, sp, -16
  sd ra, 8(sp)
  la a0, fmts
  addi a1, sp, 0
  call scanf
  ld a0, 0(sp)
  ld ra, 8(sp)
  addi sp, sp, 16
.endm

.macro print_int // print a1
  addi sp, sp, -8
  sd ra, 0(sp)
  la a0, fmtp
  call printf
  ld ra, 0(sp)
  addi sp, sp, 8
.endm

.section .text

main:
  scan_int
  mv s0, a0
  scan_int
  mv s1, a0
  scan_int
  mv s2, a0
  bge s1, s0, 1f // s1 >= s0
  mv s0, s1
1:
  bge s2, s0, 2f // s2 >= s0
  mv s0, s2
2:
  mv a1, s0
  print_int
  mv a0, zero
  ret
