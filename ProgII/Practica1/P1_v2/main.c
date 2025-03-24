#include <stdio.h>
#include <stdlib.h>
#include "clave.h"
int main(int argc, char** argv) {

    clave clave1;
    unsigned short longitud, cifrado, posicion;
    TELEMENTO valor;
    char opcion;

    do{
        printf("\n--------------------\n");
        printf("\na) Crea clave");
        printf("\nb) Crear clave introducida por consola");
        printf("\ns) Salir");
        printf("\n--------------------\n");
        printf("\nOpcion: ");
        scanf(" %c",&opcion);
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

            case 'b': //Caso para elegir si se mete la clave por comandos
                if (argc <= 2){ 
                    printf("Se deben introdicir al menos 3 argumentos, el código, un caracter y un número para el cifrado");
                    return(EXIT_FAILURE);
                }
                longitud = argc -2; //La logitud es asi porque un arg es el codigo y otro el numero
                cifrado = atoi(argv[argc - 1]); //Convierte a int el num del final
                crear(&clave1, longitud, cifrado);
                for (posicion=0;posicion<longitud;posicion++)
                {
                    //printf("Elemento %d de la clave: ",posicion);
                    /*PREGUNTAR POR QUE HAY QUE PONER EL * */ 
                    valor = *argv[posicion+1]; //Valor de cada posición
                    asignar(&clave1,posicion,valor);
                }
                printf("Clave cifrada con éxito\n");
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