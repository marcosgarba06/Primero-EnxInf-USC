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

//Funciones definidas fuera del int main()
int darDeAlta(TLISTA *listaUsu);
//int darDeBaja(TLISTA *listaUsu);
void imprimirLista(TLISTA listaUsu);

int main(int argc, char const *argv[])
{
    TLISTA listaUsu;
    crearLista(&listaUsu);
    //lecturaArchivoUsuarios(&listaUsu, "listausuarios.txt");
    char opcion;
    int tam = 0;
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
            tam = longitudLista(listaUsu);
            printf("Hay %d usuarios registrados. \n", tam);
            break;
        
        case 'b': 
            void imprimirLista(TLISTA listaUsu);
            //darDeBaja(&listaUsu);
            //tam = longitudLista(listaUsu);
            //printf("Hay %d usuarios registrados. \n", tam);
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

    TIPOELEMENTOLISTA *nuevoUsu;
    nuevoUsu = (TIPOELEMENTOLISTA*)malloc(sizeof(TIPOELEMENTOLISTA));
    if (nuevoUsu == NULL)
    {
        printf("Error: No se ha podido reservar memoria.\n");
        return -1;
    }
    
    printf("Introduzca el nombre del usuario: ");
    scanf("%s", nuevoUsu->nombre);
    getc(stdin);

    printf("Introduzca los apellidos del usuario: ");
    fgets(nuevoUsu->apellidos, MAX_APE, stdin);
    nuevoUsu->apellidos[strlen(nuevoUsu->apellidos)-1]='\0'; 

    printf("Introduzca la edad del usuario: ");
    scanf("%d", &nuevoUsu->edad);
    getc(stdin);

    if (nuevoUsu->edad < 18)
    {
        printf("Error: El usuario debe ser mayor de edad.\n");
    }else if(nuevoUsu->edad > 150){
        printf("Error: Con esa edad deberias estar muerto.\n");
    }

    printf("Introduzca el email del usuario: ");
    scanf("%s", nuevoUsu->correo);
    getc(stdin);

    TPOSICION posicion = primeroLista(*listaUsu);
    TIPOELEMENTOLISTA *aux;

    while(posicion!=finLista(*listaUsu)){
        recuperarElementoLista(*listaUsu,posicion,aux);
        printf("Email recuperado: '%s'\n", aux->correo);

        /*Recupera el elemento almacenado en la lista en la posición dada, para ello 
        reconvierte la estructura definida al tipo de dato que usa la lista en su 
        definición (TIPOELEMENTOLISTA)*/
        if(strcmp(aux->correo,nuevoUsu->correo)==0){ 
            //Se comparan ambas cadenas con strcmp para ver si son iguales
            printf("Error: El email ya está asociado a otro usuario. \n");
            free(nuevoUsu);
            return -1; //Devuelve -1 si hay error.
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
    getc(stdin);

    cadena2clave(&(nuevoUsu->clave1), contrasena, cifrado);
    insertarElementoLista(*listaUsu, finLista(*listaUsu), &nuevoUsu);
    imprimirLista(*listaUsu);

    printf("\nUsuario dado de alta con éxito con los siguientes elementos: \n");
    printf("\n Correo electronico (email): %s", nuevoUsu->correo);
    printf("\n Nombre: %s", nuevoUsu->nombre);
    printf("\n Apellidos: %s", nuevoUsu->apellidos);
    printf("\n Contraseña:");
    imprimir(nuevoUsu->clave1, 1); //Se usa el modo 1 para imprimir *
    
    free(nuevoUsu);
    return 0;
}


//int darDeBaja(TLISTA *listaUsu) 
/*Funcion para dar de baja a un usuario de la lista, para ello se le pide el correo electronico
del usuario que se quiere eliminar, si este se encuentra en la lista entonces se le pide la contraseña,
si la contraseña es correcta entonces se elimina el usuario de la lista*/
/*{
    DatUsuario usuario;
    char email[MAX_EMAIL];

    printf("Introduzca el correo electonico del usuario a eliminar: ");
    scanf("%s", email);
    getc(stdin);

    email[strcspn(email, "\n")] = 0; //elimina el salto de linea si hay

    TPOSICION pos;
    pos = primeroLista(*listaUsu);
    int elementoEncontrado;

    while (finLista(*listaUsu) != pos)
    {
        recuperarElementoLista(*listaUsu, pos, (TIPOELEMENTOLISTA *)&usuario);
        
        // Añadir impresión para depuración
        printf("Comparando: '%s' con '%s'\n", usuario.correo, email);

        if (strcmp(usuario.correo, email) == 0)
        {
            elementoEncontrado = 1;
            break;*/
            /*se detiene si lo encuentra y queda guardado en la variable usuario el
            usuario que tiene ese correo */
        /*}
        pos = siguienteLista(*listaUsu, pos);
    }

    if (elementoEncontrado == 0)
    { // Si no lo encuentra da error
        printf("Error: El correo electronico no se encuentra entre los usuarios.");
        return 1;
    }

    printf("Introduzca la contraseña del usuario a eliminar: ");
    scanf(" %s", email);
    getc(stdin);

    char contrasenaGuardada[MAX_PASS];
    obtenerContrasena(usuario.clave1, contrasenaGuardada); //recupera la contraseña del usuario con ese mail
    if (strcmp(contrasenaGuardada, email) != 0)
    {
        printf("Error: Contraseña incorrecta. \n");
        return 1;
    }else{
        suprimirElementoLista(listaUsu, pos); //elimina el usuario de la lista
        printf("Usuario eliminado con exito. \n");
        return 0;
    }
}
*/
void imprimirLista(TLISTA listaUsu) {
    TPOSICION pos = primeroLista(listaUsu);
    DatUsuario usuario;

    printf("Contenido de la lista de usuarios:\n");
    while (pos != finLista(listaUsu)) {
        recuperarElementoLista(listaUsu, pos, (TIPOELEMENTOLISTA *)&usuario);
        
        // Imprimir la información del usuario
        printf("\nCorreo electrónico: %s", usuario.correo);
        printf("\nNombre: %s", usuario.nombre);
        printf("\nApellidos: %s", usuario.apellidos);
        printf("\nEdad: %d", usuario.edad);
        printf("\nContraseña: ");
        imprimir(usuario.clave1, 1); // Imprimir con el modo de asteriscos
        printf("\n---------------------------");

        pos = siguienteLista(listaUsu, pos);
    }
    printf("\nFin de la lista de usuarios.\n");
}