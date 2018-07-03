#include <stdio.h>

int res_gen = 0, res_wm = 0, res_dw = 0, int_gen = 0, int_wm= 0, int_dw = 0;
int count = 0; // <-- contatore ciclo
int TH = 0;    // <-- fascia
int stato = 0; // A = 0, B = 1, C = 2, ..., M = 10

/*
# INDICAZIONE DEGLI STATI
# A = 'La macchina e' spenta'
# B = 'La macchina e' accesa e non si trova in OL con int-dw=1 e int-wm=1'
# C = 'La macchina si trova in OL fino al 3 controllo'
# D = 'La macchina si trova in OL ed e' al 4 controllo; spengo la DW'
# E = 'La macchina si trova in OL ed e' al 5 controllo; spengo la WM'
# F = 'La macchina si trova con int-dw=0'
# G = 'La macchina si trova con int-wm=0'
# H = 'La macchina si trova con int-dw=0 e int-wm=0'
# I = 'La macchina si trova in OL con int-dw=0'
# L = 'La macchina si trova in OL con int-wm=0'
# M = 'La macchina si trova in OL con int-dw=0 e int-wm=0'
*/

int main(void){
    // stato A macchina spenta
    if (stato == 0){
        stato = 1;
        int_gen = 1;
        int_wm = 1;
        int_dw = 1;
        // in assembly devo ritornare lo stato, int_gen, int_wm, int_dw
    } 
    // B e C nell' else if
    if (stato == 1){
        if (count <= 3)
            stato = 1; // i valori li setto solo se cambiano anche in assembly.
        else if (count == 4){
            stato = 2;
            // i valori li setto solo se cambiano anche in assembly.
            int_dw = 0;
        }
    }
    // D
    if (stato == 2 && count == 5){
        stato = 3;
        // i valori li setto solo se cambiano anche in assembly. qui dw e' gia' 0 mentre gen = 1
        int_wm = 0;
    }
    // E
    if (stato == 3 && count == 6){
        stato = 0;
        int_gen = 0;
        // i valori li setto solo se cambiano anche in assembly. qui wm e dw sono gia' 0
    }


    return 0;
}