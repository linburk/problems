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

comp:
  ld t0, 0(a0)
  ld t1, 8(a0)
  ld t2, 0(a1)
  ld t3, 8(a1)
  beq t0, t2, 1f
  blt t0, t2, 2f
  j 3f
1:
  beq t1, t3, 11f
  blt t1, t3, 22f
  j 33f
11:
  li a0, 0
  j end
22:
  li a0, -1
  j end
33:
  li a0, 1
  j end
2:
  li a0, -1
  j end
3:
  li a0, 1
  j end
end:
  ret

main:
// s0 - heap address
// s1 - address of last el
// s2 - size

  addi sp, sp, -8
  sd ra, 0(sp)

  li a0, 804
  li t0, 2000
  mul a0, a0, t0
  call malloc
  mv s0, a0
  mv s1, a0

L1:
  scan_int
  beqz a0, EL1
  sd a0, 0(s1)
  addi s1, s1, 8
  addi s2, s2, 1
  j L1
EL1:

  mv a0, s0
  mv a1, s2
  srli a1, a1, 1
  li a2, 16
  la a3, comp
  call qsort

  mv s3, zero
  mv s1, s0
L2:
  beq s3, s2, EL2
  ld a0, 0(s1)
  print_int
  addi s3, s3, 1
  addi s1, s1, 8
  j L2
EL2:

  mv a0, s0
  call free

  ld ra, 0(sp)
  addi sp, sp, 8
  mv a0, zero
  ret
