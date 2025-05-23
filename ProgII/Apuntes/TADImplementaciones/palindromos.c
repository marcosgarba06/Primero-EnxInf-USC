#include <stdio.h>
#include <string.h>

int es_palindromo(char cadena[], int izq, int der) {
    if (izq >= der) {
        return 1; // Caso base: la cadena vacía o de un solo carácter es palíndroma
    }
    if (cadena[izq] != cadena[der]) {
        return 0; // Si hay un par que no coincide, no es palíndromo
    }
    // Llamada recursiva con los índices acercándose hacia el centro
    return es_palindromo(cadena, izq + 1, der - 1);
}

int main() {
    char p[] = "anilina";
    if (es_palindromo(p, 0, strlen(p) - 1)) {
        printf("La cadena \"%s\" es un palíndromo.\n", p);
    } else {
        printf("La cadena \"%s\" no es un palíndromo.\n", p);
    }
    return 0;
}
