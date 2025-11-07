#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "structFilaMatriz.h"

/** Se supone que este codigo proviene de structFilaMatriz.h pero en caso de no ser asi
 * se incluye aqui por si acaso.
int tot al = 0;
#define DIMFILA 300000
#define NUMFILAS 20

typedef struct fila{
    int vector[DIMFILA];
    long suma;
} fila_t;

typedef fila_t * pfila_t;
fila_t matriz[NUMFILAS];
**/



int main(){
    int fd, zero = 0;
    size_t bytes = sizeof(fila_t) * (size_t)NUMFILAS;

    fd = open("archivo", O_RDWR | O_CREAT, 0600);
    if(fd == -1){
        perror("Error al abrir o al crear el archivo");
        return 1;
    }
    if(write(fd, &zero, sizeof(int)) == -1){
        perror("Error al escribir en el archivo");
        close(fd);
        return 1;
    }
    fila_t *matriz_map = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (matriz_map == MAP_FAILED){
        perror("mmap");
        close(fd);
        return 1;
    }


    for (int f = 0; f < NUMFILAS; ++f){
        for (int j = 0; j < DIMFILA; ++j) matriz_map[f].vector[j] = 10;
        matriz_map[f].suma = 0;
    }


    for (int f = 0; f < NUMFILAS; ++f){
        pid_t pid = fork();
        if (pid < 0){
            perror("fork");
            // Evitar zombis si falló a mitad
            for (int k = 0; k < f; ++k) wait(NULL);
            munmap(matriz_map, bytes);
            close(fd);
            return 1;
        }
        if (pid == 0){
            long acc = 0;
            for (int j = 0; j < DIMFILA; ++j) acc += matriz_map[f].vector[j];
            matriz_map[f].suma = acc;
            _exit(0); // no duplicar buffers stdio
        }
        // El padre sigue creando hijos
    }


    for (int i = 0; i < NUMFILAS; ++i)
        if (wait(NULL) == -1) perror("wait");


    for (int f = 0; f < NUMFILAS; ++f)
        printf("fila %2d -> suma = %ld\n", f, matriz_map[f].suma);


    if (munmap(matriz_map, bytes) == -1) perror("munmap");
    close(fd);


    return 0;


}