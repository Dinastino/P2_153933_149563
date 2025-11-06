

#ifndef P2_153933_149563_STRUCTFILAMATRIZ_H
#define P2_153933_149563_STRUCTFILAMATRIZ_H
#define DIMFILA 300000
#define NUMFILAS 20
int total = 0;


typedef struct fila{
    int vector[DIMFILA];
    long suma;
} fila_t;

typedef fila_t * pfila_t;
fila_t matriz[NUMFILAS];

#endif //P2_153933_149563_STRUCTFILAMATRIZ_H
