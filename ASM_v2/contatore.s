.section .text
.global contatore
.type contatore, @function

contatore:

	pushl %ebp 
	movl %esp, %ebp

    #EAX contatore
    #4(%edi) contiene prima lettera fascia
    if_ol:
        cmpl $79, 4(%edi)  #se prima lettera è O significa che sono in OL
        je incrementa
        movl $0, %eax
        jmp fine

    incrementa:
        addl $1, %eax
        jmp fine

	fine:
        popl %ebp
        ret
