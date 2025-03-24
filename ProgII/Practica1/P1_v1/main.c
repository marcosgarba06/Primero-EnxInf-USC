#include <stdio.h>
#include <stdlib.h>
#include "clave.h"
int main() {
    clave clave1;
    unsigned short longitud, cifrado, posicion;
    TELEMENTO valor;
    char opcion;
    do{
        printf("\n--------------------\n");
        printf("\na) Crea clave");
        printf("\ns) Salir");
        printf("\n--------------------\n");
        printf("\nOpcion: ");
        scanf("%c",&opcion);
        switch(opcion){
            
            case 'a':
                printf("Introduce el tamanho de la clave: ");
                scanf("%hu",&longitud);
                printf("Introduce el número para cifrar la clave: ");
                scanf("%hu",&cifrado);
                crear(&clave1,longitud,cifrado);
                /*Asigno valores a la clave a partir de lo que teclea el
                usuario*/
                for (posicion=0;posicion<longitud;posicion++)
                {
                    printf("Elemento %d de la clave: ",posicion);
                    scanf(" %c",&valor);
                    asignar(&clave1,posicion,valor);
                }
                break;

            case 's':
                printf("Salimos del programa\n");
                break;
            
            default:
                printf("Opcion incorrecta\n");
            }
    }while (opcion!='s');
    return (EXIT_SUCCESS);
}