// procConcurrente.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

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

int main(void){

    const char *fname = "archivo";
    size_t bytes = sizeof(fila_t) * (size_t)NUMFILAS;

    int fd = open(fname, O_RDWR | O_CREAT, 0600);
    if (fd == -1){
        perror("open(archivo)");
        return 1;
    }

    if (bytes == 0){
        fprintf(stderr, "Tamano a mapear es 0\n");
        close(fd);
        return 1;
    }

    if (write(fd, "", 1) != 1){
        perror("write(size byte)");
        close(fd);
        return 1;
    }
    if (ftruncate(fd, (off_t)bytes) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    // --- Mapear el archivo en memoria compartida ---
    fila_t *matriz_map = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (matriz_map == MAP_FAILED){
        perror("mmap");
        close(fd);
        return 1;
    }

    // --- Inicialización en el padre ---
    for (int f = 0; f < NUMFILAS; ++f){
        for (int j = 0; j < DIMFILA; ++j) matriz_map[f].vector[j] = 10;
        matriz_map[f].suma = 0;
    }

    // --- Un hijo por fila ---
    for (int f = 0; f < NUMFILAS; ++f){
        pid_t pid = fork();
        if (pid < 0){
            perror("fork");
            for (int k = 0; k < f; ++k) wait(NULL);
            munmap(matriz_map, bytes);
            close(fd);
            return 1;
        }
        if (pid == 0){
            long acc = 0;
            for (int j = 0; j < DIMFILA; ++j) acc += matriz_map[f].vector[j];
            matriz_map[f].suma = acc;
            _exit(0); // evita duplicar buffers stdio
        }
        // padre sigue creando hijos
    }

    // --- Esperar a todos los hijos ---
    for (int i = 0; i < NUMFILAS; ++i)
        if (wait(NULL) == -1) perror("wait");

    // --- Mostrar resultados ---
    for (int f = 0; f < NUMFILAS; ++f)
        printf("fila %2d -> suma = %ld\n", f, matriz_map[f].suma);

    // --- Limpieza ---
    if (munmap(matriz_map, bytes) == -1) perror("munmap");
    close(fd);


    return 0;
}
