#include <stdio.h>

int main () {
    char bufferin[400] = "000-0001011000\n100-0001011000\n001-0001111000\n011-0001111000\n000-1001011000\n000-1001111000\n100-1011011100\n100-0011011000\n000-1011001000\n100-1011001100\n000-1011001100\n000-1011001100\n000-1011001100\n000-1011001100\n000-1011001100\n000-0001011000\n001-0001011000\n101-0000101000\0";
    char* s = bufferin;
    while(*s!='\0') 
    {
        if(*s == '\n')
            s++; 
        //48 è la posizione del carattere '0' nella tabella ASCII
        int reset_gen = *s++ - 48;
        int reset_dw = *s++ - 48;
        int reset_wm = *s++ - 48;
        s = s+1; //devo saltare il simbolo - 
        int load[10];
        printf("%i %i %i - ", reset_gen, reset_dw, reset_wm);
        for( int i = 0 ; i < 10 ; i++ ) {
            load[i] = *s++ - 48;
            printf("%i ", load[i]);
        }
        printf("\n");
    }
    return 0;
}

/* i print sono solo per provare il funzionamento. Nel file controller.c bisogna inserire solamente il ciclo per avere ad ogni iterazione
i corretti valori dei res e l'array di load*/
