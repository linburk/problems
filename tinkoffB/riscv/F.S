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

func:
  addi sp, sp, -24 // 0 - ra, 8 - is_odd, 16 - number
  andi a0, a0, 0b01
  sd a0, 8(sp)
  scan_int
  beq a0, zero, end
  sd a0, 16(sp)
  ld a0, 8(sp)
  beqz a0, even
  j all
even:
  ld t0, 16(sp)
  ld t1, 40(sp)
  sd t0, 40(sp)
  sd t1, 16(sp)
all:
  ld a0, 8(sp)
  addi a0, a0, 1
  sd ra, 0(sp)
  call func
  ld ra, 0(sp)
  ld a0, 16(sp)
  print_int
end:
  addi sp, sp, 24
  ret

main:
  addi sp, sp, -8
  sd ra, 0(sp)
  addi a0, zero, 1
  call func
  ld ra, 0(sp)
  addi sp, sp, 8
  mv a0, zero
  ret
