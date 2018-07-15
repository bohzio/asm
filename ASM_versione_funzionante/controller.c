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
		
	/*CORDINATE DEI VARI INPUT OUTPUT E FUNZIONE REGISTRI:
	eax = contatore
	ebx = tiene la somma dei load per ogni riga
	cl = lo uso per gli spostamenti tra due indirizzi di memoria diversi (dimensione di un byte)
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
		__asm__(
		
		"subl %%eax, %%eax;"			//Svuoto eax per pulirlo da possibile memoria sporca.
		"jmp FINCHE_SPENTA;"
		"MACCHINA_SPENTA:"					//questo blocco di codice stampa 000-00\n se res_gen non è stato attivato / si è arrivati al sesto ciclo in OL
			"subl %%eax, %%eax;"
			"movb $48, (%%edi);"
			"movb $48, 1(%%edi);"
			"movb $48, 2(%%edi);"
			"movb $45, 3(%%edi);"   	//Questo è il carattere '-'
			"movb $48, 4(%%edi);"
			"movb $48, 5(%%edi);"
			"movb $10, 6(%%edi);"		//Questo è il carattere '-'
			"addl $15, %%esi;"
			"addl $7, %%edi;"
	
		"FINCHE_SPENTA:"
			"cmpb $0, (%%esi);"			//Se trovo '\0'(ASCII) allora ho finito di leggere le righe del file di input e termino
			"je FINE_INPUT;"
			"cmpb $48, (%%esi);"
			"je MACCHINA_SPENTA;"		//Se res_gen è ancora zero allora l'output sarà 000-00
			"movb $49, (%%edi);"		//Altrimenti la macchina deve accendersi. Quindi 111-__
			"movb $49, 1(%%edi);"		//int_dw
			"movb $49, 2(%%edi);"		//int_wm
			"movb $45, 3(%%edi);"   	//Questo è il carattere '-'
			"call genera_fascia;"
			"addl $15, %%esi;"
			"addl $7, %%edi;"
			"cmpb $76, 5(%%edi);"		//Controllo se il secondo carattere di TH e' L allora sono in OL
			"jne CICLO_MACCHINA_ACCESA;"
			"addl $1, %%eax;"
										//IMPORTANTE: Fino a questo punto è stato generato solo il primo ciclo da quando la macchina è stata accesa!
		"CICLO_MACCHINA_ACCESA:"
			"cmpb $0, (%%esi);"			//Se trovo '\0'(ASCII) allora ho finito di leggere le righe del file di input e termino
			"je FINE_INPUT;"
			"movb $49, (%%edi);"
			"movb -6(%%edi), %%cl;" 	//Questa riga e la prossima servono per spostare il valore dell'int precedente di dw nella nuova stringa di output
			"movb %%cl, 1(%%edi);"		//int_dw
			"movb -5(%%edi), %%cl;"
			"movb %%cl, 2(%%edi);"		//int_wm
			"movb $45, 3(%%edi);"   	//Questo è il carattere '-'
		"CONTROLLO_RES_DW:"
			"cmpb $49, 1(%%esi);"		//Se il res di dw è uguale a 1 allora metto a uno int_dw
			"jne CONTROLLO_RES_WM;"		
			"movb $49, 1(%%edi);"
		"CONTROLLO_RES_WM:"
			"cmpb $49, 2(%%esi);"		//Se il res di wm è uguale a 1 allora metto a uno int_wm
			"jne FINE_CONTROLLO_RES_WM;"
			"movb $49, 2(%%esi);"
		"FINE_CONTROLLO_RES_WM:"
			"call genera_fascia;"		//Calcolo la fascia in base agli int precedenti combinati con i res attuali
			"cmpb $76, 5(%%edi);"		//Se sono in OL allora inizio una serie di check per sapere a che punto si trova il contatore
			"jne FINE_CICLO_NON_OL;"	//Altrimenti vado a fine ciclo not OL dove azzero il contatore e passo alla riga successiva
			"cmp $3, %%eax;"			//Controlle se contatore = 3
			"jl INCREMENTA_CONTATORE;"	//Se <3 allora salta alla prossima riga con contatore incrementato
			"jne CICLO_5_OL;"			//Se non uguale (quindi >3) controllo se = 4
			"movb $48, 1(%%edi);"		//Altrimenti metto a 0 int_dw e ricalcolo la fascia
			"call genera_fascia;"
			"cmpb $76, 5(%%edi);"		//Se la fascia ricalcolata è ancora OL allora passo a INCREMENTA_CONTATORE
			"jne FINE_CICLO_NON_OL;"	//Altrimenti vado a FINE_CICLO_NON_OL
			"jmp INCREMENTA_CONTATORE;"
		"CICLO_5_OL:"
			"cmp $4, %%eax;"		
			"jne CICLO_6_OL;"			//Se non uguale a 5 controllo se = 6
			"movb $48, 2(%%edi);"		//Altrimenti metto a 0 int_wm e ricalcolo la fascia
			"call genera_fascia;"
			"cmpb $76, 5(%%edi);"		//Se la fascia ricalcolata è ancora OL allora passo a INCREMENTA_CONTATORE
			"jne FINE_CICLO_NON_OL;"	//Altrimenti vado a FINE_CICLO_NON_OL
			"jmp INCREMENTA_CONTATORE;"
		"CICLO_6_OL:"
			"cmp $5, %%eax;"
			"je MACCHINA_SPENTA;"
		"FINE_CICLO_NON_OL:"
			"subl %%eax, %%eax;"		//azzero il contatore
			"jmp NUOVA_RIGA_FILE;"
		"INCREMENTA_CONTATORE:"
			"addl $1, %%eax;"
		"NUOVA_RIGA_FILE:"	
			"addl $15, %%esi;"			//passo alla riga successiva
			"addl $7, %%edi;"
			"jmp CICLO_MACCHINA_ACCESA;"
		"FINE_INPUT:"					//Una volta terminata la stringa si esce dal programma
			"movb $0, (%%edi);"			//Metto il carattere per terminare la stringa
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
