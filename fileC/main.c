#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

short int const loads[] = {2000, 300, 1200, 1000, 2000, 1800, 240, 400, 200, 400};

int res_gen = 0, res_wm = 0, res_dw = 0, int_gen = 0, int_wm= 0, int_dw = 0;
int count = 0; // <-- contatore ciclo (incrementando indica anche che sono ancora in OL)
int stato = 0; // A = 0, B = 1, C = 2, ..., M = 10
int th;

enum { MAXLINES = 400 };
enum { LIN_LEN = 15 };
enum { LOUT_LEN = 8 };

int generaFascia(int bitStato[], int length, int wm, int dw){


    int sum = 0;
    int i = 0;

    int oldDw = bitStato[4];
    int oldWm = bitStato[5];

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

int contatore(int count, int fascia){
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
    int bitStato[10];

    const int n_input = 15;

    int wm_old = 0;
    int dw_old = 0;

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


        int wm = res_wm || int_wm;
        int dw = res_dw || int_dw;

        th = generaFascia(bitStato,10,wm,dw);

        count = contatore(count, th);

        // stato A macchina spenta
        if (stato == 0) {
            if(res_gen) {
                stato = 1;
                int_gen = 1;
                int_wm = 1;
                int_dw = 1;
            }

            // in assembly devo ritornare lo stato, int_gen, int_wm, int_dw
        }
            // C e' un particolare B si comporta simile a parte
            // B e C nell' if
        else if (stato == 1) {
            // B NON CAMBIA NIENTE
            // if (count <= 3) i valori li setto solo se cambiano anche in assembly.
            if (count == 4) {
                stato = 2;
                // i valori li setto solo se cambiano anche in assembly.
                int_dw = 0;
            }
        }
            // D
        else if (stato == 2) {
            if (count) {
                // i valori li setto solo se cambiano anche in assembly. qui dw e' gia' 0 mentre gen = 1
                int_wm = 0;
                // passo ad L
                if (res_dw) {
                    stato = 8;
                    int_dw = 1;
                } // passo ad E
                else {
                    stato = 3;
                }
            } else {
                if (res_dw) {
                    stato = 1;
                    int_dw = 1;
                } // passo ad F
                else if (!res_dw) {
                    stato = 4;
                }
            }
        }
            // E
        else if (stato == 3) {
            if (count) {
                stato = 0;
                int_gen = 0;
                // i valori li setto solo se cambiano anche in assembly. qui wm e dw sono gia' 0
            } else {
                // G
                if (res_dw && !res_wm) {
                    stato = 5;
                    int_dw = 1;
                }
                    // F
                else if (res_wm && !res_dw) {
                    stato = 4;
                    int_wm = 1;
                }
                    // B
                else if (res_wm && res_dw) {
                    stato = 1;
                    int_wm = 1;
                    int_dw = 1;
                }
                    // H
                else {
                    stato = 6;
                }
            }

        }
            // stato F
        else if (stato == 4) {
            // passo in I
            if (count) {
                stato = 7;
                // C
                if (res_dw) {
                    stato = 1;
                    int_dw = 1;
                }
            } else {
                // B
                if (res_dw) {
                    stato = 1;
                    int_dw = 1;
                }
            }
        }

            // stato G
        else if (stato == 5) {
            if (count) {
                // L
                stato = 8;
                // C
                if (res_wm) {
                    stato = 1;
                    int_wm = 1;
                }
            } else {
                // B
                if (res_wm) {
                    stato = 1;
                    int_wm = 1;
                }
            }
        }

            // stato H
        else if (stato == 6) {
            if (count) {
                // I
                if (res_dw) {
                    stato = 7;
                    int_dw = 1;
                } // L
                else if (res_wm) {
                    stato = 8;
                    int_wm = 1;
                }
                    // C
                else if (res_dw && res_wm) {
                    stato = 1;
                    int_wm = 1;
                    int_dw = 1;
                } else {
                    stato = 9;
                }
            } else {
                // B
                if (res_dw && res_wm) {
                    stato = 1;
                    int_wm = 1;
                    int_dw = 1;
                }
                    // F
                else if (res_wm) {
                    stato = 4;
                    int_wm = 1;
                }
                    // G
                else if (res_dw) {
                    stato = 5;
                    int_dw = 1;
                }
            }
        }
            // stato I
        else if (stato == 7) {
            if (count) {
                // C
                if (res_dw && count <= 3) {
                    stato = 1;
                    int_dw = 1;
                }
                    // D
                else if (res_dw && count == 4) {
                    stato = 2;
                }
                    // E
                else if (res_dw && count == 5) {
                    stato = 2;
                }
                    // M
                else if (count == 5) {
                    stato = 9;
                    int_wm = 0;
                }
            } else {
                // B
                if (res_dw) {
                    stato = 1;
                    int_dw = 1;
                }
                    // F
                else {
                    stato = 4;
                }
            }
        }

        else if (stato == 8) {
            if (count) {
                // count == 4 stato L
                if (count == 5) {
                    stato = 3;
                }
                    // A
                else if (count == 6) {
                    stato = 0;
                    int_gen = 0;
                    int_dw = 0;
                }
                    // C
                else if (res_wm && count <= 3) {
                    stato = 1;
                    int_wm = 1;
                }
                    // D
                else if (res_wm && count == 4) {
                    stato = 2;
                    int_wm = 1;
                    int_dw = 0;
                }
            } else {
                // B
                if (res_wm) {
                    stato = 1;
                    int_wm = 1;
                } else {
                    stato = 5;
                }
            }
        }
            // stato M
        else if (stato == 9) {
            if (count) {
                // A
                if (count == 6) {
                    stato = 0;
                    int_gen = 0;
                    int_dw = 0;
                }
                    // I
                else if (res_wm && count <= 5) {
                    stato = 7;
                    int_wm = 1;
                }
                    // L
                else if (res_dw) {
                    stato = 8;
                    int_dw = 1;
                }
            } else {
                // B
                if (res_wm && res_dw) {
                    stato = 1;
                    int_wm = 1;
                    int_dw = 1;
                }
                    // F
                else if (res_wm) {
                    stato = 4;
                    int_wm = 1;
                }
                    // G
                else if (res_dw) {
                    stato = 5;
                    int_dw = 1;
                } else {
                    stato = 6;
                }
            }
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