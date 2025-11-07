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

void* trabajoHebra(void* arg) {
    int idx = *(int*)arg;
    long suma_local = 0;

    for (int j = 0; j < DIMFILA; j++) {
        matriz[idx].vector[j] = 10;
    }

    for (int j = 0; j < DIMFILA; j++) {
        suma_local += matriz[idx].vector[j];
    }

    matriz[idx].suma = suma_local;

    printf("Hebra %d -> Suma fila: %ld\n", idx, suma_local);

    pthread_exit(NULL);
}

int main() {
    pthread_t hebras[NUMFILAS];
    int indices[NUMFILAS];

    for (int i = 0; i < NUMFILAS; i++) {
        indices[i] = i;
        if (pthread_create(&hebras[i], NULL, trabajoHebra, &indices[i]) != 0) {
            perror("Error al crear la hebra");
            return 1;
        }
    }

    for (int i = 0; i < NUMFILAS; i++) {
        pthread_join(hebras[i], NULL);
    }

    for (int i = 0; i < NUMFILAS; i++) {
        total += matriz[i].suma;
    }

    printf("Suma total de todas las filas: %d\n", total);

    return 0;
}
