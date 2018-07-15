.section .text
.global genera_fascia
.type genera_fascia, @function

genera_fascia:

	 pushl %ebp 
	 movl %esp, %ebp

	 pushl %eax
					
     subl %ebx, %ebx  				#azzero ebx ad ogni nuova riga di input
	 subl %eax, %eax


	 save_old_dw_wm:
	 	movb 8(%esi), %al			#salvo DW
		movb 9(%esi), %ah   		#salvo WM

	 replace_dw_wm_loads:
	 	andb %cl, 8(%esi)           #metto nel load DW l'and tra il load e int_dw 
		andb %dl, 9(%esi)		   	#metto nel load WM l'and tra il load e int_wm

   	            					#nel registro esi si ha il puntatore al primo carattere di ogni riga
     load1:
		 cmpb $49, 4(%esi)			#se load1 è uguale a 1 (carattere ASCII 49) continuo il "blocco di istruzioni" altrimenti passo ad occuparmi del load successivo
		 jne load2
		 addl $2000, %ebx			#in ebx salvo la somma dei load
     
     load2:
		 cmpb $49, 5(%esi)
		 jne load3
		 addl $300, %ebx
    
     load3:
		 cmpb $49, 6(%esi)
		 jne load4
		 addl $1200, %ebx    
     
     load4:
		 cmpb $49, 7(%esi)
		 jne load5
		 addl $1000, %ebx
     
     load5:							#Lavastoviglie (DW)
		 cmpb $49, 8(%esi)
		 jne load6
		 addl $2000, %ebx
     
     load6:							#Lavatrice (WM)
		 cmpb $49, 9(%esi)
		 jne load7
		 addl $1800, %ebx
     
     load7:
		 cmpb $49, 10(%esi)
		 jne load8
		 addl $240, %ebx
     
     load8:
		 cmpb $49, 11(%esi)
		 jne load9
		 addl $400, %ebx
    
     load9:
		 cmpb $49, 12(%esi)
		 jne load10
		 addl $200, %ebx
    
     load10:
		 cmpb $49, 13(%esi)
		 jne fine_somma
		 addl $300, %ebx

	restore_old_dw_wm:
	 	movb %al, 8(%esi) 			#ripristino il load DW iniziale
		movb %ah, 9(%esi)   		#ripristino il load WM iniziale
    
     fine_somma:					#A questo punto ho finito di sommare i load
		 
		 cmpl $4500, %ebx
		 jle terza_fascia
		 							#Se >4500 scrivo "OL\n" e termino
		 movb $79, 4(%edi)
		 movb $76, 5(%edi)
		 movb $10, 6(%edi)
		 jmp fine_genera_fascia
     
     terza_fascia:
		 
		 cmpl $3000, %ebx
		 jle seconda_fascia
		 							#Se >3000 scrivo "F3\n" e termino
		 movb $70, 4(%edi)
		 movb $51, 5(%edi)
		 movb $10, 6(%edi)
		 jmp fine_genera_fascia
     
     seconda_fascia:
		 
		 cmpl $1500, %ebx
		 jle prima_fascia
		 							#Se >1500 scrivo "F2\n" e termino
		 movb $70, 4(%edi)
		 movb $50, 5(%edi)
		 movb $10, 6(%edi)
		 jmp fine_genera_fascia
     
     prima_fascia:
     								#Altrimenti scrivo "F1\n" e termino
     	 	movb $70, 4(%edi)
     	 	movb $49, 5(%edi)
     	 	movb $10, 6(%edi)

     fine_genera_fascia:

	 	popl %eax
	
		popl %ebp

	 	ret
