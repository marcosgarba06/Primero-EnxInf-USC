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

typedef struct{
    char correo[MAX_EMAIL];
    char nombre[MAX_NAME];
    char apelldos[MAX_APE];
    int edad;
    clave clave1;
}DatUsuario;


int main(int argc, char const *argv[])
{
    TLISTA listaUsuarios;
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
        
        switch(opcion)
        {
        case 'a':
            darAlta(&listaUsuarios);
            break;

        case 's':
            printf("Saliendo del programa...\n");
            break;
    
        default:
            break;
        }
    } while (opcion!='s');
    
    return 0;
}

int darAlta(TLISTA *listaUsu) {
    DatUsuario nuevoUsuario;
    char password[MAX];
    int valido = 1;
    
   
    printf("Introduzca el correo electrónico: ");
    scanf("%s", nuevoUsuario.correo);
    getchar(); 
    //Con el getchar limpiamos la cadena de entrada para evitar fallos
    
    //FALTA COMPROBAR SI HAY OTRO CORREO IGUAL 
    
    printf("Introduazca el nombre: ");
    scanf("%s", nuevoUsuario.nombre);
    getchar();
    
    printf("Introduzca los Apellidos: ");
    scanf(" %[^\n]", nuevoUsuario.apelldos);
    getchar(); 
    
    printf("Edad: ");
    scanf("%d", &nuevoUsuario.edad);
    getchar(); 
    
    if (nuevoUsuario.edad < 18) {
        printf("Error: Para crear una cuenta de usuario hay que ser mayor de edad.\n");
        return 0;
    }
    
    printf("Introduzca la contraseña: ");
    scanf("%s", password);
    getchar();
    
    CLAVE_CREAR(&nuevoUsuario.clave1);
    CLAVE_ASIGNAR(&nuevoUsuario.clave1, password);
    
   //Falta insertar el elemento en la lista
}