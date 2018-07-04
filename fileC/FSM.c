int res_gen = 0, res_wm = 0, res_dw = 0, int_gen = 0, int_wm= 0, int_dw = 0;
int count = 0; // <-- contatore ciclo (incrementando indica anche che sono ancora in OL)
int stato = 0; // A = 0, B = 1, C = 2, ..., M = 10
/*
A       0
B - C   1
D       2
E       3
F       4
G       5
H       6
I       7
L       8
M       9
*/
int main(void){
    // stato A macchina spenta
    if (stato == 0 && res_gen){
        stato = 1;
        int_gen = 1;
        int_wm = 1;
        int_dw = 1;
        
        // in assembly devo ritornare lo stato, int_gen, int_wm, int_dw
    }
    // C e' un particolare B si comporta simile a parte
    // B e C nell' if
    if (stato == 1){
        // B NON CAMBIA NIENTE
        // if (count <= 3) i valori li setto solo se cambiano anche in assembly.
        if (count == 4){
            stato = 2;
            // i valori li setto solo se cambiano anche in assembly.
            int_dw = 0;
        }
    }
    // D
    if (stato == 2){
        if (count){
            // i valori li setto solo se cambiano anche in assembly. qui dw e' gia' 0 mentre gen = 1
            int_wm = 0;
            // passo ad L
            if (res_dw){
                stato = 8;
                int_dw = 1;
            } // passo ad E
            else{
                stato = 3;
            }
        } else{
            if (res_dw){
                stato = 1;
                int_dw = 1;
            } // passo ad F
            else if (!res_dw){
                stato = 4;
            }
        }
    }
    // E
    if (stato == 3){
        if (count){
            stato = 0;
            int_gen = 0;
            // i valori li setto solo se cambiano anche in assembly. qui wm e dw sono gia' 0
        } else{
            // G
            if (res_dw && !res_wm){
                stato = 5;
                int_dw = 1;
            }
            // F
            else if(res_wm && !res_dw){
                stato = 4;
                int_wm = 1;
            }
            // B
            else if(res_wm && res_dw){
                stato = 1;
                int_wm = 1;
                int_dw = 1;
            } 
            // H
            else{
                stato = 6;
            }
        }

    }
    // stato F
    if (stato == 4){
        // passo in I
        if (count){
            stato = 7;
            // C
            if (res_dw){
                stato = 1;
                int_dw = 1;
            }
        } else{
            // B
            if (res_dw){
                stato = 1;
                int_dw = 1;
            }
        }
    }

    // stato G
    if (stato == 5){
        if (count){
            // L
            stato = 8;
            // C
            if (res_wm){
                stato = 1;
                int_wm = 1;
            }
        } else{
            // B
            if (res_wm){
                stato = 1;
                int_wm = 1;
            }
        }
    }

    // stato H
    if (stato == 6){
        if (count){
            // I
            if (res_dw){
                stato = 7;
                int_dw = 1;
            } // L
            else if (res_wm){
                stato = 8;
                int_wm = 1;
            }
            // C
            else if (res_dw & res_wm){
                stato = 1;
                int_wm = 1;
                int_dw = 1;
            } else{
                stato = 9;
            }
        } else{
            // B
            if (res_dw & res_wm){
                stato = 1;
                int_wm = 1;
                int_dw = 1;
            }
            // F
            else if (res_wm){
                stato = 4;
                int_wm = 1;
            }
            // G
            else if (res_dw){
                stato = 5;
                int_dw = 1;
            }
        }
    }
    // stato I
    if (stato == 7){
        if (count){
            // C
            if (res_dw && count <= 3){
                stato = 1;
                int_dw = 1;
            } 
            // D
            else if (res_dw && count == 4){
                stato = 2;
            }
            // E
            else if (res_dw && count == 5){
                stato = 2;
            } 
            // M
            else if (count == 5){
                stato = 9;
                int_wm = 0;
            }
        } else{
            // B
            if (res_dw){
                stato = 1;
                int_dw = 1;
            } 
            // F
            else{
                stato = 4;
            }
        }
    }

    if (stato == 8){
        if (count){
            // count == 4 stato L
            if (count == 5){
                stato = 3;
            }
            // A
            else if (count == 6){
                stato = 0;
                int_gen = 0;
                int_dw = 0;
            }
            // C
            else if (res_wm && count <= 3){
                stato = 1;
                int_wm = 1;
            } 
            // D
            else if (res_wm && count == 4){
                stato = 2;
                int_wm = 1;
                int_dw = 0;
            }
        } else{
            // B
            if (res_wm){
                stato = 1;
                int_wm = 1;
            } else{
                stato = 5;
            }
        }
    }
    // stato M
    if (stato == 9){
        if (count){
            // A
            if (count == 6){
                stato = 0;
                int_gen = 0;
                int_dw = 0;
            } 
            // I
            else if (res_wm && count <= 5){
                stato = 7;
                int_wm = 1;
            }
            // L
            else if (res_dw){
                stato = 8;
                int_dw = 1;
            }
        } else{
            // B
            if (res_wm && res_dw){
                stato = 1;
                int_wm = 1;
                int_dw = 1;
            } 
            // F
            else if (res_wm){
                stato = 4;
                int_wm = 1;
            } 
            // G
            else if (res_dw){
                stato = 5;
                int_dw = 1;
            } else{
                stato = 6;
            }
        }
    }


    return 0;
}