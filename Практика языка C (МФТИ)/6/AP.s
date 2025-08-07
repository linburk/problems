  .text
    .globl start

start:
    movq    $0, %rax           # rax = 0 (default: composite)
    cmpq    $1, %rdi
    jbe     composite
    cmpq    $3, %rdi
    jbe     prime
    testb   $1, %dil           # test if x is even
    je      composite

    movq    $2, %rcx           # rcx = divisor

loop:
	xor  	%rdx, %rdx
    mov     %rdi, %rax
	div	    %rcx
	test	%rdx, %rdx
	je	    composite
	addq	$1, %rcx
	mov 	%rcx, %rax
	imul	%rax, %rax
	cmp 	%rdi, %rax
    jbe     loop

prime:
    movq    $1, %rax
    ret

composite:
    movq    $0, %rax
    ret

.section .note.GNU-stack,"",@progbits
