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
    TIPOELEMENTOLISTA nuevoUsu;
    unsigned short cifrado;
    char contrasenaTemp[MAX_PASS];
    clave clave1;

    getchar();
    printf("Introduzca el nombre del usuario: ");
    scanf("%s", nuevoUsu.nombre);
    getchar();

    printf("Introduzca los apellidos del usuario: ");
    scanf("%[^\n]", nuevoUsu.apellidos);
    getchar();

    printf("Introduzca el email del usuario: ");
    scanf("%s", nuevoUsu.correo);
    getchar();

    printf("Introduzca la edad del usuario: ");
    scanf("%d", &nuevoUsu.edad);

    if (nuevoUsu.edad < 18){
        printf("Error: El usuario debe ser mayor de edad.\n");
        return -1;
    }

    printf("Introduzca la clave: ");
    while (getchar() != '\n');
    fgets(contrasenaTemp, sizeof(contrasenaTemp), stdin);

    int len = strlen(contrasenaTemp);
    if (len > 0 && contrasenaTemp[len-1] == '\n') {
        contrasenaTemp[len-1] = '\0';
    }

    printf("Inroduzca el número para cifrar la clave: ");
    scanf("%hu", &cifrado);

    cadena2clave(&clave1, contrasenaTemp, cifrado);
    printf("Clave creada con éxito.\n");
    nuevoUsu.clave1 = clave1;
    imprimir(nuevoUsu.clave1,0);

    insertarElementoLista(listaUsu, primeroLista(listaUsu), nuevoUsu);
    
    TIPOELEMENTOLISTA aux;
    TPOSICION pos=finLista(listaUsu);

    recuperarElementoLista(&listaUsu, pos, &aux);
    getchar();
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