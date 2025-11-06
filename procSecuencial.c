#include <stdio.h>
#include "structFilaMatriz.h"


int main(){

    for(int i = 0; i < NUMFILAS; i++){
        for(int j = 0; j < DIMFILA; j++){
            matriz[i].vector[j] = 10;
            matriz[i].suma = 0;
        }
    }

    for(int i = 0; i < NUMFILAS; i++){
        for(int j = 0; j < DIMFILA; j++){
            matriz[i].suma += matriz[i].vector[j];
        }
        total += matriz[i].suma;
        printf("Suma fila %d: %ld\n", i, matriz[i].suma);
    }

    printf("Suma total: %d\n", total);
    return 0;
}
