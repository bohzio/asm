#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

unsigned int const loads[] = {2000, 300, 1200, 1000, 2000, 1800, 240, 400, 200, 400};

_Bool res_gen = 0, res_wm = 0, res_dw = 0, int_gen = 0, int_wm= 0, int_dw = 0;
unsigned int count = 0; // <-- contatore ciclo (incrementando indica anche che sono ancora in OL)
unsigned int th;

enum { MAXLINES = 400 };
enum { LIN_LEN = 15 };
enum { LOUT_LEN = 8 };

unsigned int generaFascia(_Bool bitStato[],unsigned int const length, _Bool wm, _Bool dw){


    unsigned int sum = 0;
    unsigned int i = 0;

    _Bool oldDw = bitStato[4];
    _Bool oldWm = bitStato[5];

    //array
    bitStato[4] = bitStato[4] && dw;
    bitStato[5] = bitStato[5] && wm;

    for (; i < length; i++){
        if(bitStato[i])
            sum += loads[i];
    }

    bitStato[4] = oldDw;
    bitStato[5] = oldWm;

    if (sum <= 1500)
        return 0;
    else if(sum <= 3000)
        return 1;
    else if(sum <= 4500)
        return 2;
    return 3;
}

unsigned int contatore(unsigned int count, unsigned int fascia){
    return (fascia == 3) ? count+=1 : 0;
}


char * readFile(int argc, char *argv[]){

    int i = 0;
    char *bufferin =  malloc(sizeof(char) * MAXLINES*LIN_LEN+1); ;
    char line[1024];

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

    return bufferin;
}


int main(int argc, char *argv[]){


    char *bufferin = readFile(argc,argv);

    //Ho bisogno di 2 array perchè uno viene modificato con genera fascia
    _Bool bitStato[10];

    const unsigned int n_input = 15;

    _Bool wm_old = 0;
    _Bool dw_old = 0;

    while (*bufferin != '\0'){

        wm_old = int_wm;
        dw_old = int_dw;

        res_gen = bufferin[0] - '0';
        res_dw = bufferin[1] - '0';
        res_wm = bufferin[2] - '0';

        //salto bufferin[3] che sarebbe il trattino (-)

        for(int i=0; i<10;i++){
            bitStato[i] = bufferin[i+4] - '0';
        }


        _Bool wm = res_wm || int_wm;
        _Bool dw = res_dw || int_dw;

        th = generaFascia(bitStato,10,wm,dw);

        count = contatore(count, th);
        /*
        Con questi if sistemo gli eventuali 
        */
        if (int_gen == 0 && res_gen){
            int_gen = 1;
            int_wm = 1;
            int_dw = 1;
        }
        if (int_wm == 0){
            int_wm = res_wm;
        }
        if (int_dw == 0){
            int_dw = res_dw;
        }
        if (count == 4){
            int_dw = 0;
        } else if (count == 5){
            int_wm = 0;
        } else if (count == 6){
            int_gen = 0;
            int_wm = 0;
            int_dw = 0;
        }


        if(wm_old != int_wm || dw_old != int_dw){
            th = generaFascia(bitStato,10,int_wm,int_dw);
        }

        if(int_gen != 0){
            printf("%i%i%i-",int_gen,int_dw,int_wm);

            if(th == 0) printf("F1");
            if(th == 1) printf("F2");
            if(th == 2) printf("F3");
            if(th == 3) printf("OL");
        }else{
            printf("000-00");
        }

        printf("\n");


        bufferin+=n_input;
    }

    return 0;
}