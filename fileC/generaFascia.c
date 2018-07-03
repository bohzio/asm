short int loads[] = {2000, 300, 1200, 1000, 2000, 1800, 240, 400, 200, 400};

int generaFascia(_Bool *bitStato, int length){
    int sum = 0;
    int i = 0;
    for (; i < length; i++){
        if(bitStato[i])
            sum += loads[i];
    }
    if (sum <= 1500)
        return 0;
    else if(sum <= 3000)
        return 1;
    else if(sum <= 4500)
        return 2;
    return 3;
}

int main(void){
    return 0;
}