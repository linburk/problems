.global main

.section .data
fmts: .asciz "%lld"
fmtp: .asciz "%lld\n"

.macro scan_int // scan to a0
  addi sp, sp, -16
  sd ra, 0(sp)
  la a0, fmts
  addi a1, sp, 8
  call scanf
  ld a0, 8(sp)
  ld ra, 0(sp)
  addi sp, sp, 16
.endm

.macro print_int // print from a1
  addi sp, sp, -8
  sd ra, 0(sp)
  la a0, fmtp
  call printf
  ld ra, 0(sp)
  addi sp, sp, 8
.endm

.section .text

main:
  mv s0, zero
L1:
  scan_int
  beqz a0, L_end
  add s0, s0, a0
  j L1
L_end:
  mv a1, s0
  print_int
  mv a0, zero
  ret
