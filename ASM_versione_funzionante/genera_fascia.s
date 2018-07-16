.section .data
.section .bss
.section .text
.global genera_fascia
.type genera_fascia, @function

genera_fascia:
    pushl %ebp  					#Salvo il frame pointer
    movl %esp, %ebp					#Il nuovo frame pointer lo faccio puntare alla cima della pila
   	movl $0, %ebx  					#Azzero ebx ad ogni nuova riga di input
   	            					#Nel registro esi si ha il puntatore al primo carattere di ogni riga
	LOAD1:
		cmpb $49, 4(%esi)			#Se LOAD1 è uguale a 1 (carattere ASCII 49) continuo il "blocco di istruzioni" altrimenti passo ad occuparmi del LOAD successivo
		jne LOAD2
		addl $2000, %ebx			#In ebx salvo la somma dei LOAD
     
    LOAD2:
		cmpb $49, 5(%esi)
		jne LOAD3
		addl $300, %ebx
    
    LOAD3:
		cmpb $49, 6(%esi)
		jne LOAD4
		addl $1200, %ebx    
    
    LOAD4:
		cmpb $49, 7(%esi)
		jne LOAD5
	 	addl $1000, %ebx

    LOAD5:							#Lavastoviglie (DW)
		cmpb $49, 8(%esi)
		jne LOAD6
		addl $2000, %ebx
	 	cmpb $48, 1(%edi)
		jne LOAD6
		subl $2000, %ebx
    
	LOAD6:							#Lavatrice (WM)
		cmpb $49, 9(%esi)
		jne LOAD7
		addl $1800, %ebx
		cmpb $48, 2(%edi)
		jne LOAD7
		subl $1800, %ebx
    LOAD7:
		cmpb $49, 10(%esi)
		jne LOAD8
		addl $240, %ebx
     
	LOAD8:
		
		cmpb $49, 11(%esi)
		jne LOAD9
		addl $400, %ebx

    LOAD9:
		cmpb $49, 12(%esi)
		jne LOAD10
		addl $200, %ebx
    
	LOAD10:
		cmpb $49, 13(%esi)
		jne FINE_SOMMA
		addl $300, %ebx
    
	FINE_SOMMA:					#A questo punto ho finito di sommare i LOAD	 
		cmpl $4500, %ebx
		jle TERZA_FASCIA
	
	CONTROLLO_OL:				#Se >4500 scrivo "OL\n" e termino
		movb $79, 4(%edi)		
		movb $76, 5(%edi)
		jmp FINE_GENERA_FASCIA
    
	TERZA_FASCIA:				#Se >3000 scrivo "F3\n" e termino
		cmpl $3000, %ebx
		jle SECONDA_FASCIA
		movb $70, 4(%edi)
		movb $51, 5(%edi)
		jmp FINE_GENERA_FASCIA

    SECONDA_FASCIA:				#Se >1500 scrivo "F2\n" e termino
		cmpl $1500, %ebx
		jle PRIMA_FASCIA
		movb $70, 4(%edi)
		movb $50, 5(%edi)
		jmp FINE_GENERA_FASCIA
    
    PRIMA_FASCIA:				#Altrimenti scrivo "F1\n" e termino
     	movb $70, 4(%edi)
     	movb $49, 5(%edi)

	FINE_GENERA_FASCIA:
		movb $10, 6(%edi)		#Aggiungo \n in fondo visto che e' comune a tutti
		popl %ebp				#Ripristino il frame pointer salvato sullo stack
	 	ret
