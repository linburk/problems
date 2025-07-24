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
  addi sp, sp, -8
  
  sd ra, 0(sp)
  addi a0, a0, 1000
  li t0, 804
  mul a0, a0, t0
  call malloc
  ld ra, 0(sp)
  mv s0, a0    // s0 - address of heap
  mv s2, zero // s2 - size

L1:
  scan_int
  beqz a0, EL1
  sd a0, 0(s0)
  addi s0, s0, 8
  addi s2, s2, 1
  j L1
EL1:

L2:
  beq s2, zero, EL2
  ld a0, -16(s0)
  print_int
  ld a0, -8(s0)
  print_int
  addi s0, s0, -16
  addi s2, s2, -2
  j L2
EL2:
  sd ra, 0(sp)
  mv a0, s0
  call free
  ld ra, 0(sp)
  addi sp, sp, 8
  mv a0, zero
  ret
