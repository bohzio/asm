#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

/* Inserite eventuali extern modules qui */

/* ************************************* */

enum { MAXLINES = 400 };
enum { LIN_LEN = 15 };
enum { LOUT_LEN = 8 };

long long current_timestamp() {
    struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	/* te.tv_nsec nanoseconds divide by 1000 to get microseconds*/
	long long nanoseconds = tp.tv_sec*1000LL + tp.tv_nsec; // caculate nanoseconds
    return nanoseconds;
}


int main(int argc, char *argv[]) {
    int i = 0;
    char bufferin[MAXLINES*LIN_LEN+1] ;
    char line[1024];
    long long tic_c, toc_c, tic_asm, toc_asm;

    char bufferout_c[MAXLINES*LOUT_LEN+1] = "" ;
    char bufferout_asm[MAXLINES*LOUT_LEN+1] = "" ;

    FILE *inputFile = fopen(argv[1], "r");

    if(argc != 3)
    {
        fprintf(stderr, "Syntax ./test <input_file> <output_file>\n");
        exit(1);
    }

    if (inputFile == 0)
    {
        fprintf(stderr, "failed to open the input file. Syntax ./test <input_file> <output_file>\n");
        exit(1);
    }

    while (i < MAXLINES && fgets(line, sizeof(line), inputFile))
    {
        i = i + 1;
        strcat( bufferin, line) ;
    }

    bufferin[MAXLINES*LIN_LEN] = '\0' ;

    fclose(inputFile);


    /* ELABORAZIONE in C */
    tic_c = current_timestamp();

    /* è possibile inserire qui il codice per l'elaborazione in C (non richiesto per l'elaborato) */
    /* questo pezzo di codice è solo una base di partenza per fare dei check sui dati */
    /*
    int c = 0;
    char tmpout[LOUT_LEN];
    strcpy( tmpout, "000-00\n");
    while ( bufferin[c] != '\0') {
      printf( "%d\n", bufferin[c]);
      strcat( bufferout_asm, tmpout);
      c = c + LIN_LEN ;
    }
    */

    toc_c = current_timestamp();

  	long long c_time_in_nanos = toc_c - tic_c;

    /* FINE ELABORAZIONE C */


    /* INIZIO ELABORAZIONE ASM */

    tic_asm = current_timestamp();

    /* Assembly inline:
    Inserite qui il vostro blocco di codice assembly inline o richiamo a funzioni assembly.
    Il blocco di codice prende come input 'bufferin' e deve restituire una variabile stringa 'bufferout_asm' che verrà poi salvata su file. */
		
	/*
	
	CORDINATE DEI VARI INPUT OUTPUT E FUNZIONE REGISTRI:
	
	eax = contatore
	ebx = tiene la somma dei load per ogni riga
    cl = dw
    dl = wm
	esi = puntatore per la stringa bufferin.
	edi = puntatore per la stringa bufferout_asm. Per scrivere basta vare movb $(codice ascii), spiaz(%edi)
	
	(esi) = res_gen
	1(esi) = res_dw
	2(esi) = res_wm
	3(esi) = "-"
	4(esi) = load1
	5(esi) = load2
	6(esi) = load3
	7(esi) = load4
	8(esi) = load5 ->lavastoviglie/DW
	9(esi) = load6 ->lavatrice/WM
	10(esi) = load7
	11(esi) = load8
	12(esi) = load9
	13(esi) = load10
	14(esi) = "\n"
	Esi va incrementato di 15 per ogni riga successiva
	
	0(edi) = int_gen
	1(edi) = int_dw
	2(edi) = int_wm
	3(edi) = "-"
	4(edi) = caratterefascia(1)
	5(edi) = caratterefascia(2)
	6(edi) = "\n"
	Edi va incrementato di 7 per ogni riga successiva
	
	*/
    /*
    48 = '0'
    49 = '1'
    */
		__asm__(
        
        "movb $0, %%dh;"
		"Start:"
            "movb $48, (%%edi);"
            "movb $48, 1(%%edi);"
            "movb $48, 2(%%edi);"
			"cmpb $0, (%%esi);"		//Se trovo '\0'(ASCII) allora ho finito di leggere le righe del file di input e termino
			"je FineInput;"
            "cmpb $0, %%dh;"
            "je SETTO_INT_INIZIALI_0;"
            "subl $7, %%edi;"
            "movb 1(%%edi), %%cl;"  // recupero il vecchio int_dw
            "movb 2(%%edi), %%dl;"  // recupero il vecchio int_wm
            "addl $7, %%edi;"
            "jmp END_SETTO_INT_INIZIALI_0;"
        "SETTO_INT_INIZIALI_0:"
            "movb $48, (%%edi);"
            "movb $48, 1(%%edi);"
            "movb $48, 2(%%edi);"
            "movb 1(%%edi), %%cl;"  // setto cl a 0 --> int_dw_old = 0
            "movb 2(%%edi), %%dl;"  // setto dl a 0 --> int_wm_old = 0
        "END_SETTO_INT_INIZIALI_0:"
            "or 1(%%esi), %%cl;"    //res_dw || int_dw
            "or 2(%%esi), %%dl;"    //res_wm || int_wm
            "call contatore;"
    		"call genera_fascia;"
        "ControlloGEN:"             // doppio controllo if (int_gen == 0 && res_gen)
            "cmpb $48, (%%edi);"
            "jne ControlloDW;"
            "cmpb $49, (%%esi);"
            "jne ControlloDW;"
            "movb $49, (%%edi);"
            "movb $49, 1(%%edi);"
            "movb $49, 2(%%edi);"
        "ControlloDW:"
            "cmpb $48, 1(%%edi);"
            "jne ControlloWM;"
            "movb 1(%%esi), %%ch;"
            "movb %%ch, 1(%%edi);"
        "ControlloWM:"
            "cmpb $48, 2(%%edi);"
            "jne ControlloCiclo4;"
            "movb 2(%%esi), %%dh;"
            "movb %%dh, 2(%%edi);"
        "ControlloCiclo4:"
            "cmpl $4, %%eax;"
            "jne ControlloCiclo5;"
            "movb $48, 1(%%edi);"
            "jmp ControlloRicalcolaTH;"
        "ControlloCiclo5:"
            "cmpl $5, %%eax;"
            "jne ControlloCiclo6;"
            "movb $48, 2(%%edi);"
            "jmp ControlloRicalcolaTH;"
        "ControlloCiclo6:"
            "cmpl $6, %%eax;"
            "jne ControlloRicalcolaTH;"
            "movb $48, (%%edi);"
            "movb $48, 1(%%edi);"
            "movb $48, 2(%%edi);"
        "ControlloRicalcolaTH:"
            "cmpb 1(%%edi), %%cl;"      //dw_old != int_dw
            "jne RicalcolaTH;"
            "cmpb 2(%%edi), %%dl;"      //wm_old != int_wm
            "jne RicalcolaTH;"
            "jmp ControlloIntGen;"
        "RicalcolaTH:"
            "movb 1(%%edi), %%cl;"      // piazzo in cl il nuovo int_dw
            "movb 2(%%edi), %%dl;"      // piazzo in dl il nuovo int_wm
            "call genera_fascia;"
        "ControlloIntGen:"
            "cmpb $48, (%%edi);"
            "jne FineControllo;"        //int_gen == 0 allora TH = 00
            "movb $48, 4(%%edi);"
            "movb $48, 5(%%edi);"
        "FineControllo:"                //Fine controllo
            "movb $45, 3(%%edi);"   	//Questo è il carattere '-'
    		"addl $15, %%esi;"
    		"addl $7, %%edi;"
            "movb $1, %%dh;"
    		"jmp Start;"
		"FineInput:"				    //Una volta terminata la stringa si esce dal programma
			"movb $0, (%%edi);"		    //Metto il carattere per terminare la stringa
			:
			:"D" (bufferout_asm), "S" (bufferin)
			:
			
		);
		

    toc_asm = current_timestamp();

  	long long asm_time_in_nanos = toc_asm - tic_asm;

    /* FINE ELABORAZIONE ASM */


    printf("C time elapsed: %lld ns\n", c_time_in_nanos);
    printf("ASM time elapsed: %lld ns\n", asm_time_in_nanos);

    /* Salvataggio dei risultati ASM */
  	FILE *outputFile;
    outputFile = fopen (argv[2], "w");
    fprintf (outputFile, "%s", bufferout_asm);
    fclose (outputFile);

    return 0;
}