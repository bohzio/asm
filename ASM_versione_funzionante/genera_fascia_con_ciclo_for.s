.section .data
loads:
	.long 2000
	.long 300
	.long 1200
	.long 1000
	.long 2000
	.long 1800
	.long 240
	.long 400
	.long 200
	.long 400

.section .bss
.section .text
.global genera_fascia
.type genera_fascia, @function

genera_fascia:
    pushl %ebp  						#Salvo il frame pointer
    movl %esp, %ebp						#Il nuovo frame pointer lo faccio puntare alla cima della pila
	pushl %edx
	pushl %ecx
	
	movl $0, %ebx  						#Azzero ebx ad ogni nuova riga di input
	addl $4, %esi 						#Mi sposto sui bit dei carichi
	movl $0, %edx						#Indice del ciclo FOR

	FOR:
		cmpb $49, (%esi,%edx,1)			#Controllo se il carattere e' '1'
		je TRUE
		jmp CONTINUE
	TRUE:
		movl loads(,%edx,4), %ecx		#Porto il valore contenuto in loads + edx*4 in ecx
		addl %ecx, %ebx					#somma a ebx ecx
	
	LOAD5:								#Lavastoviglie (DW)
		cmpl $5, %edx					#Se sono al 5' ciclo controllo int_dw || res_dw
		jne LOAD6
		cmpb $48, 1(%edi)				#Se int_dw || res_dw == 0 sottraggo il carico
		jne CONTINUE
		subl loads(,%edx,4), %ebx
	LOAD6:								#Lavatrice (WM)
		cmpl $6, %edx					#Se sono al 6' ciclo controllo int_dw || res_dw
		jne CONTINUE
		cmpb $48, 2(%edi)				#Se int_wm || res_wm == 0 sottraggo il carico
		jne CONTINUE
		subl loads(,%edx,4), %ebx
	CONTINUE:
		addl $1, %edx					#Indice edx += 1
		cmpl $10, %edx					#Se edx <= 10 sto dentro il ciclo altrimenti esco
		jne FOR
	# FINE CICLO FOR SOMMA
    
	FINE_SOMMA:							#A questo punto ho finito di sommare i LOAD	 
		cmpl $4500, %ebx
		jle TERZA_FASCIA
	
	CONTROLLO_OL:						#Se >4500 scrivo "OL\n" e termino
		movb $79, 4(%edi)		
		movb $76, 5(%edi)
		movb $10, 6(%edi)
		jmp FINE_GENERA_FASCIA
    
	TERZA_FASCIA:						#Se >3000 scrivo "F3\n" e termino
		cmpl $3000, %ebx
		jle SECONDA_FASCIA
		movb $70, 4(%edi)
		movb $51, 5(%edi)
		jmp FINE_GENERA_FASCIA

    SECONDA_FASCIA:						#Se >1500 scrivo "F2\n" e termino
		cmpl $1500, %ebx
		jle PRIMA_FASCIA
		movb $70, 4(%edi)
		movb $50, 5(%edi)
		jmp FINE_GENERA_FASCIA
    
    PRIMA_FASCIA:						#Altrimenti scrivo "F1\n" e termino
     	movb $70, 4(%edi)
     	movb $49, 5(%edi)

	FINE_GENERA_FASCIA:
		movb $10, 6(%edi)				#Aggiungo \n in fondo visto che e' comune a tutti
		subl $4, %esi 					#Mi risposto nel byte corretto
		popl %ecx
		popl %edx
		popl %ebp						#Ripristino il frame pointer salvato sullo stack
	 	ret	
