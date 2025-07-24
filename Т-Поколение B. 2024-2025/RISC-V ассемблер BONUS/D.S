.global main

.section .data
fmts: .ascii "%lld\0"
fmtp: .ascii "%lld\n\0"

.macro scan_int // to a0
  addi sp, sp, -16
  sd ra, 0(sp)
  la a0, fmts
  addi a1, sp, 8
  call scanf
  ld a0, 8(sp)
  ld ra, 0(sp)
  addi sp, sp, 16
.endm

.macro print_int // from a0
  addi sp, sp, -8
  sd ra, 0(sp)
  mv a1, a0
  la a0, fmtp
  call printf
  ld ra, 0(sp)
  addi sp, sp,  8
.endm

.section .text

main:
  scan_int
  mv s0, a0
  scan_int
  mv s1, a0
L1:
  beqz s1, EL1
  div t0, s0, s1
  mul t0, t0, s1
  sub s0, s0, t0
  mv t0, s0
  mv s0, s1
  mv s1, t0
  j L1
EL1:
  mv a0, s0
  print_int
  mv a0, zero
  ret
