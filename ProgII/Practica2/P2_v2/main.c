#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "clave.h"
#include "cola-1.h"
#include "lista-1.h"


#define MAX 255
#define MAX_NAME 25
#define MAX_APE 50
#define MAX_EMAIL 255
#define MAX_PASS 255

typedef struct{
    char correo[MAX_EMAIL];
    char nombre[MAX_NAME];
    char apellidos[MAX_APE];
    int edad;
    clave clave1;
}DatUsuario;

//Funciones definidas fuera del int main()
int darDeAlta(TLISTA *listaUsu);


int main(int argc, char const *argv[])
{
    TLISTA listaUsu;
    crearLista(&listaUsu);
    //lecturaArchivoUsuarios(&listaUsu, "listausuarios.txt");
    char opcion;

    do
    {
        printf("========= Seleccione una opcion =========");
        printf("\na) Dar de alta a un usuario.");
        printf("\nb) Dar de baja a un usuario.");
        printf("\nc) Recepción de solicitudes de entradas.");
        printf("\nd) Ver el numero de solicitudes para el evento.");
        printf("\ne) Venta de entradas.");
        printf("\ns) Salir del programa.");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);
        
        switch(opcion)
        {
        case 'a':
            darDeAlta(&listaUsu);
            int tam;
            tam = longitudLista(listaUsu);
            printf("Hay %d usuarios registrados. \n", tam);
            break;
        
        case 'b': 
            //darDeBaja(&listaUsu);
            break;

        case 's':
            //escribirArchivoUsuarios(&listaUsu, "listausuarios.txt");
            printf("Saliendo del programa...\n");
            break;
    
        default:
            printf("Opcion no valida.\n");
            break;
        }
    } while (opcion!='s');
    
    return 0;
}


int darDeAlta(TLISTA *listaUsu){

    DatUsuario *nuevoUsu = (DatUsuario *)malloc(sizeof(DatUsuario));

    if (nuevoUsu == NULL) { //Comprobar que el puntero se inicializa de forma correcta
        printf("Error: No se pudo asignar memoria para el nuevo usuario.\n");
        return 0;
    }
    

    printf("Ingrese su nombre: ");
    scanf(" %s", nuevoUsu->nombre);
    getc(stdin); //Elimina el caracter \n de salto de linea que queda en el buffer de entrada

    printf("Ingrese su apellido: ");
    fgets(nuevoUsu->apellidos, MAX_APE, stdin);
    nuevoUsu->apellidos[strlen(nuevoUsu->apellidos)-1]='\0'; 

    printf("Itroduzca su edad: ");
    scanf("%d", &nuevoUsu->edad);

    if (nuevoUsu->edad<18){ //Comprobar que el nuevo usuario es mayor de edad
        printf("Error: Para crear un usuario hay que ser mayor de esdad. \n");
        return 1; //return temprano si el usuario es menor de edad
    }else if(nuevoUsu->edad>150){ 
        printf("Error: Deberias estar muerto. \n");
        return 1;
    }

    printf("Introduzca el correo electrónico: ");
    scanf("%s", nuevoUsu->correo);
    getc(stdin); 

    TPOSICION posicion;
    DatUsuario usuario;

    posicion=primeroLista(*listaUsu);
    /*Para hacerlo se comprobará cada email con los emails que hayan en la lista
    y, si coincide, se detiene el programa dando un mensaje de error.*/
    while(posicion!=finLista(*listaUsu)){
        recuperarElementoLista(*listaUsu, posicion,(TIPOELEMENTOLISTA*)&usuario);
        /*Recupera el elemento almacenado en la lista en la posición dada, para ello 
        reconvierte la estructura definida al tipo de dato que usa la lista en su 
        definición (TIPOELEMENTOLISTA)*/
        if(strcmp(usuario.correo,nuevoUsu->correo)==0){ 
            //Se comparan ambas cadenas con strcmp para ver si son iguales
            printf("Error: El email ya está asociado a otro usuario. \n");
            free(nuevoUsu);
            return 0; //Devuelve 0 si hay error.
        }
        posicion=siguienteLista(*listaUsu,posicion);
    }

    char contrasena[MAX_PASS];
    int cifrado;
    printf("Introduzca la contraseña: ");
    scanf("%s", contrasena);
    getc(stdin);

    printf("Introduce el numero de cifrado para la contraseña: ");
    scanf("%d", &cifrado);

    cadena2clave(&(nuevoUsu->clave1), contrasena, cifrado);
    insertarElementoLista(listaUsu, finLista(*listaUsu), nuevoUsu);

    printf("\nUsuario dado de alta con éxito con los siguientes elementos: \n");
    printf("\n Correo electronico (email): %s", nuevoUsu->correo);
    printf("\n Nombre: %s", nuevoUsu->nombre);
    printf("\n Apellidos: %s", nuevoUsu->apellidos);
    printf("\n Contraseña:");
    imprimir(nuevoUsu->clave1, 1); //Se usa el modo 1 para imprimir *
    
    free(nuevoUsu);
    return 0;
}

int darDeBaja(TLISTA *listaUsu){
    
    return 0;
}