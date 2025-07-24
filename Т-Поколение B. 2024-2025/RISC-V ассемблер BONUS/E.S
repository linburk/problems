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

is_prime:
  addi t0, zero, 2    // t0 = 2
  addi a1, zero, 1
  beq a1, a0, NP
L1:
  mul t1, t0, t0     // t1 = t0 * t0
  bgt t1, a0, LE1    // if t1 > a0
  div t1, a0, t0     // t1 = a0 / t0
  mul t1, t1, t0     // t1 = t1 * t0
  beq t1, a0, NP     // if t1 == a0
  addi t0, t0, 1     // t0 += 1
  j L1
NP:
  mv a1, zero
  j LE1
LE1:
  mv a0, a1
  jr ra

main:
  scan_int
  addi sp, sp, -8
  sd ra, 0(sp)
  call is_prime
  ld ra, 0(sp)
  addi sp, sp, 8
  print_int
  mv a0, zero
  ret
