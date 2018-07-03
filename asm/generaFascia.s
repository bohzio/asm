.section .data
loads:
	.value 2000
	.value 300
	.value 1200
	.value 1000
	.value 2000
	.value 1800
	.value 240
	.value 400
	.value 200
	.value 400

.section .bss

.section .text
    .global generaFascia
    .type generaFascia , @function	# <-- questa riga dichara che e' una funzione

# argomento array _Bool (4 byte) di 10 elementi 40 byte
generaFascia:
    # quando chiamo una funzione uso lo stack
    pushl %ebp  #li salvo per il ripristino
    movl %esp, %ebp
    # salvo i registri che uso
    pushl %eax
    pushl %ebx
    pushl %ecx
    pushl %edx

    movl $0, %eax
    movl loads, %ebx
    movl 4(%ebp), %ecx   # 4 per i ind mem dell'array di bit di stato
    movl $0, %edx        # somma

FOR:
    cmpl $1, %ecx
    je TRUE
    jmp CONTINUE
TRUE:
    addl (%ebx), %edx
CONTINUE:
    addl $1, %eax
    subl $4, %ebx
    subl $4, %ecx
    cmpl $10, %eax
    jne FOR
    # FINE CICLO FOR INIZIO CONTROLLO VALORI + INSERIMENTO IN 18(%ebp)
    cmpl $1500, %edx
    jle COMPARE1500
    cmpl $3000, %edx
    jle COMPARE3000
    cmpl $4500, %edx
    jle COMPARE4500
    jmp COMPAREOL

COMPARE1500:
    movl $0, 4(%ebp)
    jmp END
COMPARE3000:
    movl $1, 4(%ebp)
    jmp END
COMPARE4500:
    movl $2, 4(%ebp)
    jmp END
COMPAREOL:
    movl $3, 4(%ebp)
    jmp END
END:
    popl %edx
    popl %ecx
    popl %ebx
    popl %eax
    popl %ebp
    ret
