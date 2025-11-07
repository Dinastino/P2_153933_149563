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

// Función que ejecutará cada hebra
void* trabajoHebra(void* arg) {
    int idx = *(int*)arg;  // Índice de la fila a procesar
    long suma_local = 0;

    // Inicializa el vector de la fila (por ejemplo, todo con 10)
    for (int j = 0; j < DIMFILA; j++) {
        matriz[idx].vector[j] = 10;
    }

    // Calcula la suma de los valores del vector
    for (int j = 0; j < DIMFILA; j++) {
        suma_local += matriz[idx].vector[j];
    }

    // Guarda la suma en la estructura correspondiente
    matriz[idx].suma = suma_local;

    printf("Hebra %d -> Suma fila: %ld\n", idx, suma_local);

    pthread_exit(NULL);
}

int main() {
    pthread_t hebras[NUMFILAS];
    int indices[NUMFILAS];

    // Crear una hebra por cada fila de la matriz
    for (int i = 0; i < NUMFILAS; i++) {
        indices[i] = i;
        if (pthread_create(&hebras[i], NULL, trabajoHebra, &indices[i]) != 0) {
            perror("Error al crear la hebra");
            return 1;
        }
    }

    // Esperar a que todas las hebras terminen
    for (int i = 0; i < NUMFILAS; i++) {
        pthread_join(hebras[i], NULL);
    }

    // Calcular la suma total de todas las filas
    for (int i = 0; i < NUMFILAS; i++) {
        total += matriz[i].suma;
    }

    printf("Suma total de todas las filas: %d\n", total);

    return 0;
}
