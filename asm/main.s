.section .data

stato:
	.value 1
	.value 1
	.value 1
	.value 1
	.value 1
	.value 1
	.value 1
	.value 1
	.value 1
	.value 1

.section .bss

.section .text
    .global _start

_start:
    movl stato, %edx
    pushl %edx
    call generaFascia
	popl %ebx

	# movl $4, %eax # memoria contatore
	# movl $3, %ebx # ol in questo caso
	
	# per call contatore (OL, memoriaContatore)
	# pushl %ebx
	# pushl %eax
	# call contatore
	# popl %eax # memoria
END:
    movl $1, %eax
    movl $0, %ebx

    int $0x80  
