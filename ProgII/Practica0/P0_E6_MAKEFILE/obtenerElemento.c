#include "matriz.h"

float obtenerElemento(int fila, int columna, matriz *M) {
    int x;

    if (M != 0) {
        if ((fila < 0 || fila > M->filas) || (columna < 0 || columna > M->columnas)) {
            printf("Ese elemento no existe\n");
            return 0;
        }
        x = *((M->datos) + fila * M->columnas + columna);
        return x;
    } else{
        printf("La matriz no existe\n");
        return 0;
    }
}
