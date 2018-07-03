.section .data
.section .bss

.section .text
    .global contatore
    .type contatore , @function	# <-- questa riga dichara che e' una funzione

# argomento (2 int 4 byte ciascuno) valore contatore mantenuto dal programma chiamante e fascia (0, 1, 2, 3)
contatore:
    # quando chiamo una funzione uso lo stack
    pushl %ebp  # li salvo per il ripristino
    movl %esp, %ebp
    # salvo i registri che uso
    pushl %eax
    pushl %ebx
    pushl %ecx

    movl %eax, 4(%ebp)   # 4 per il valore contatore mantenuto
    movl %ebx, 8(%ebp)   # 8 per la fascia
    movl $0, %ecx        # per azzerare il contatore
    cmpl $3, %ebx
    je SET
    jmp RESET

SET:
    inc %eax;
    movl 4(%ebp), %eax
    jmp END
RESET:
    movl 4(%ebp), %ecx
END:
    popl %ecx
    popl %ebx
    popl %eax
    popl %ebp
    ret

