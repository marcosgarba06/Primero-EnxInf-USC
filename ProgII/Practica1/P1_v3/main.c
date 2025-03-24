#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clave.h"
#define MAX 200
int main(int argc, char** argv) {

    clave clave1;
    unsigned short longi, cifrado, posicion; //Cambio el nombre de la variable longi porque se puede confundir con la función longi
    TELEMENTO valor;
    char opcion;
    int existeClave; existeClave=0;

    do{
        printf("\n--------------------\n");
        printf("\na) Crea clave");
        printf("\nb) Liberar clave");
        printf("\nc) Crear clave introducida por consola");
        printf("\nd) Recuperar un caracter");
        printf("\ne) Calcular la longi de la clave");
        printf("\nf) Imprimir la clave");
        printf("\ng) Crear clave a partir de cadena de caracteres");
        printf("\nh) Comprobar si una clave es correcta");
        printf("\ns) Salir");
        printf("\n--------------------\n");
        printf("\nOpcion: ");
        scanf(" %c",&opcion);
       
        switch(opcion){
            
            case 'a':
                
                if(existeClave==1){ //Libera memoria si existe la clave
                    liberar(&clave1);
                }

                printf("Introduce el tamanho de la clave: ");
                scanf("%hu",&longi);
                printf("Introduce el número para cifrar la clave: ");
                scanf("%hu",&cifrado);
                crear(&clave1,longi,cifrado);
                /*Asigno valores a la clave a partir de lo que teclea el
                usuario*/

                for (posicion=0;posicion<longi;posicion++)
                {
                    printf("Elemento %d de la clave: ",posicion);
                    scanf(" %c",&valor);
                    asignar(&clave1,posicion,valor);
                }
                existeClave=1;
                break;

            case 'b': //caso para liberar memoria
                
                if(existeClave==1){  //Libera memoria si existe la clave
                    liberar(&clave1);
                }

                printf("\nClave liberada con éxito.");
                break;

            case 'c': //Caso para elegir si se mete la clave por comandos
                
                if (argc <= 2){ 
                    printf("Se deben introdicir al menos 3 argumentos, el código, un caracter y un número para el cifrado");
                    return(EXIT_FAILURE);
                }

                if(existeClave==1){ //Libera memoria si existe la clave
                    liberar(&clave1);
                }

                longi = argc -2; //La logitud es asi porque un arg es el codigo y otro el numero
                cifrado = atoi(argv[argc - 1]); //Convierte a int el num del final
                crear(&clave1, longi, cifrado);
               
                for (posicion=0;posicion<longi;posicion++)
                {
                    valor = *argv[posicion+1]; //Valor de cada posición
                    asignar(&clave1,posicion,valor);
                }
                
                printf("Clave cifrada con éxito\n");
                existeClave = 1;
                break;
            
            case 'd':
                
                if(existeClave==0){
                    printf("No hay ninguna clave creada. Para recuperar un elemento primero hay que recuperar una clave\n");
                }else{
                    int pos;
                    printf("Posición para recuperar: ");
                    scanf("%d", &pos);
                    TELEMENTO caracterRec;         

                    caracterRec = recuperar(clave1, pos-1);
                    if (caracterRec != -1) { //Comprueba que no hay ningun error de tamaño.
                        printf("Carácter de la clave en la posición %d: %c\n", pos, caracterRec);
                    }
                }
                break;

            case 'e': //Caso para la longitud de la clave

                if(existeClave==0){
                    printf("Error: Primero se debe crear una clave\n");
                }
                else{
                    int tamanho = longitud(clave1);
                    printf("La longitud de la clave es %d",tamanho);
                }
                break;
            
            case 'f':
                if(existeClave==0){
                    printf("Error: Primero se debe crear una clave");
                }else{
                    char opcion2;
                    printf("Modos para imprimir la clave:");
                    printf("\nModo 0: Imprime la clave descifrada");
                    printf("\nModo 1: Imprime la clave oculta con *");
                    printf("\nModo 2: Imprime la clave con algunos caracteres visibles");
                    printf("\nOpcion: ");
                    scanf(" %c",&opcion2);
                    switch (opcion2)
                    {
                    case '0':
                        imprimir(clave1, 0);
                        break;
                    
                    case '1':
                        imprimir(clave1, 1);
                        break;

                    case '2':
                        imprimir(clave1, 2);
                        break;

                    default:
                    printf("Opción inválida");
                        break;
                    }
                }

                break;
                
            case 'g':
                char cad[100];
                if (existeClave==1){
                    liberar(&clave1);
                    existeClave = 0;
                }
                
                printf("Introduzca la clave: ");
                while (getchar() != '\n'); 
                fgets(cad, sizeof(cad), stdin);         
                
                int len = strlen(cad);
                if (len > 0 && cad[len-1] == '\n') {
                    cad[len-1] = '\0';
                }

                printf("\nInroduzca el número para cifrar la clave: ");
                scanf("%hu", &cifrado);

                cadena2clave(&clave1, cad, cifrado);
                printf("Clave creada con éxito.\n");
                existeClave = 1;
                
                break;

            case 'h':
                if(existeClave==0){
                    printf("Error: Se debe crear una clave primero");
                }else{
                    printf("Elija el modo de comprobación (Modo 1: Parcial, Modo 0: Completa): ");
                    int modo;
                    scanf("%d", &modo);
                    int resultado;
                    resultado = compruebaclave(clave1, modo);
                    if(resultado==1){
                        printf("Clave correcta.\n");
                    }else{
                        printf("Clave incorrecta");
                    }
                }
                break;

            case 's':
                
                if(existeClave==1){ //libera memoria si existe la clave
                    liberar(&clave1);
                }

                printf("Salimos del programa\n");
                break;
            
            default:
                printf("Opcion incorrecta\n");
            }

    }while (opcion!='s');
    
    return (EXIT_SUCCESS);
}








