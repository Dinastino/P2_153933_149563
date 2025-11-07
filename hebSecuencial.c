#include <stdio.h>
#include <pthread.h>
#include "structFilaMatriz.h"

/** Se supone que este codigo proviene de structFilaMatriz.h pero en caso de no ser asi
 * se incluye aqui por si acaso.
int total = 0;
#define DIMFILA 300000
#define NUMFILAS 20

typedef struct fila{
    int vector[DIMFILA];
    long suma;
} fila_t;

typedef fila_t * pfila_t;
fila_t matriz[NUMFILAS];
**/

void* trebajoHebra(void* arg){
    // Inicializacion de la matriz
    for(int i = 0; i < NUMFILAS; i++){
        for(int j = 0; j < DIMFILA; j++){
            matriz[i].vector[j] = 10;
            matriz[i].suma = 0;
        }
    }

    // Calculo de sumas
    for(int i = 0; i < NUMFILAS; i++){
        for(int j = 0; j < DIMFILA; j++){
            matriz[i].suma += matriz[i].vector[j];
        }
        total += matriz[i].suma;
        printf("Suma fila %d: %ld\n", i, matriz[i].suma);
    }

    printf("Suma total: %d\n", total);

    return NULL;
}


int main(){
    pthread_t hebra;
    if(pthread_create(&hebra, NULL, trebajoHebra, NULL) != 0){
        perror("Error en la creacion de la hebra");
        return 1;
    }
    pthread_join(hebra, NULL);

    return 0;
}