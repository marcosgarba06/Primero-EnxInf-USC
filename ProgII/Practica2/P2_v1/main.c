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

//Funciones definidas fuera de main
int darDeAlta(TLISTA *listaUsu);
int darDeBaja(TLISTA *listaUsu);
void lecturaArchivoUsuarios(TLISTA *listaUsu, const char *archivo);

int main(int argc, char const *argv[])
{
    TLISTA listaUsu;
    crearLista(&listaUsu);
    lecturaArchivoUsuarios(&listaUsu, "listausuarios.txt");
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
        scanf(" %c", &opcion);
        
        switch(opcion)
        {
        case 'a':
            darDeAlta(&listaUsu);
            break;
        
        case 'b': 
            darDeBaja(&listaUsu);
            break;

        case 's':
            printf("Saliendo del programa...\n");
            break;
    
        default:
            printf("Opcion no valida.\n");
            break;
        }
    } while (opcion!='s');
    
    return 0;
}

void lecturaArchivoUsuarios(TLISTA *listaUsu, const char *archivo){
    
    DatUsuario usuario;
    FILE *archivoLista = fopen(archivo, "r");
    //Abrir el archivo
    if(archivoLista == NULL){ //Comprobar que se haya abierto con exito
        printf("Error al abrir el archivo. \n");
        return; //return temprano si hay error
    }
    
    char contrasena[MAX_PASS];
    while(fscanf(archivoLista, "%s %s %d %s %s", usuario.nombre, usuario.apellidos, 
        &usuario.edad, usuario.correo, contrasena)==5){ //Lee los datos del archivo
            cadena2clave(&usuario.clave1, contrasena, 7);
            //Crea clave para guardarla cifrada
            insertarElementoLista(listaUsu, finLista(listaUsu), &usuario);
            //Inserta cada elemento al final de la lista.
        }
    /*Leer del archivo los usuarios, en el archivos los usuarios estan en 
    diferes columnas con una fila para cada usuario. En las columnas se
    representa en este orden: NOMBRE APELLIDOS EDAD EMAIL CONTRASEÑA*/
    
    fclose(archivoLista);  //Cierra el archivo de la lista.
}


int darDeAlta(TLISTA *listaUsu) {

    DatUsuario nuevoUsu;
    char contrasena[MAX];

    printf("Introduzca el correo electrónico: ");
    scanf("%s", nuevoUsu.correo);
    getchar(); 
    //Con el getchar limpiamos la cadena de entrada para evitar fallos
    
    //Comprobar existencia del email
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
        if(strcmp(usuario.correo,nuevoUsu.correo)==0){ 
            //Se comparan ambas cadenas con strcmp para ver si son iguales
            printf("Error: El email ya está asociado a otro usuario. \n");
            return 0; //Devuelve 0 si hay error.
        }
        posicion=siguienteLista(*listaUsu,posicion);
    }  
    
    printf("Introduzca su nombre:");
    scanf("%s", nuevoUsu.nombre);
    getchar();

    printf("Introduzca sus apellidos: ");
    fgets(nuevoUsu.apellidos, MAX_APE, stdin);
    nuevoUsu.apellidos[strlen(nuevoUsu.apellidos)-1]='\0'; 
    //Elimina el caracter de salto \n que guarda fgets

    printf("Itroduzca su edad: ");
    scanf("%d", &nuevoUsu.edad);

    if (nuevoUsu.edad<18){
        printf("Error: Para crear un usuario hay que ser mayor de esdad. \n");
        return 0;
    }
    
    printf("Introduzca la contraseña: ");
    scanf("%s", contrasena);
    getchar();
    
    int cifrado = 7;

    //Cifrar contraseña;
    cadena2clave(nuevoUsu.clave1, contrasena, cifrado);

    insertarElementoLista(listaUsu, finLista(*listaUsu), &nuevoUsu);

    printf("\nUsuario dado de alta con éxito con los siguientes elementos: \n");
    printf("CORREO ELECTRONICO: %s:", nuevoUsu.correo);
    printf("\n Nombre: %s", nuevoUsu.nombre);
    printf("\n Apellidos: %s", nuevoUsu.apellidos);
    printf("\nContraseña: ");
    imprimir(nuevoUsu.clave1, 1); //Se usa el modo 1 para imprimir *
    
    return 1;
}

/*
SOLUVON A WARNING???    
void insertarUsuario(TLISTA *listaUsu, TPOSICION pos, DatUsuario *usuario) {
    TIPOELEMENTOLISTA elemento = convertirDatUsuarioATIPOELEMENTOLISTA(usuario);
    insertarElementoLista(listaUsu, pos, elemento);
}

TIPOELEMENTOLISTA convertirDatUsuarioATIPOELEMENTOLISTA(DatUsuario *usuario) {
    return (TIPOELEMENTOLISTA)usuario;
}*/

int darDeBaja(TLISTA *listaUsu){
    DatUsuario usuario;
    char email[MAX_EMAIL];

    printf("Introduzca el correo electonico del usuario a eliminar: ");
    scanf("%s", email);
    getchar();

    TPOSICION pos;
    pos = primeroLista(*listaUsu);
    int elementoEncontrado;

    while (finLista(*listaUsu) != pos){
        recuperarElementoLista(*listaUsu, pos, (TIPOELEMENTOLISTA*)&usuario);
        if(strcmp(usuario.correo, email)==0){
        elementoEncontrado = 1;
        break; 
        /*se detiene si lo encuentra y queda guardado en la variable usuario el 
        usuario que tiene ese correo*/
        }
    }

    if(elementoEncontrado==0){ //Si no lo encuentra da error
        printf("Error: El correo electronico no se encuentra entre los usuarios.");
        return 0;
    }

    char contrasenha[MAX_PASS];
    int cifrado = 7; //Se usa el mismo cifrado que en la fincion de introducir usuarios
    
    printf("Introdizca la contraseña para poder eliminar el Usuario con email %s: \n", email);
    scanf("%s", contrasenha);
    getchar();

     /*Comprobar si las contraseñas son iguales, para esto se crea una clave a partir de la string
    del usuario y se compara caracter a caracter con la existente para ese usuario*/
    
    clave clave;
    cadena2clave(&clave, contrasenha, cifrado);

    if(longitud(clave) != longitud(usuario.clave1)){
        printf("Eror : Contraseña incorrecta.\n");
        liberar(&clave); //se libera clave porque es incorrecta y no se va a usar otra vez
        return 0;
    }else{

        int compararClaves;
        compararClaves = 1;

        for(int i=0;i<longitud(usuario.clave1);i++){ //Bucle for para comprobar las claves
            if (recuperar(usuario.clave1, i) != recuperar(clave, i)){
                /*Se itera caracter a caracter, si son diferentes entonces el proceso se detiene
                si son iguales continua hasta el final*/
                compararClaves = 0;
                break;
            }
        }

        if(compararClaves==0){
            printf("Error: Clave incorrecta. \n");
            liberar(&clave);
            return 0;
        }else{ //Si contraseñas son iguales entonces se elimina de la lista
            suprimirElementoLista(listaUsu, pos); 
            //suprime el elemento de esa posicion (la posicion guardada de antes)
            printf("Usuario eliminado de la lista de usuarios. \n");    
            liberar(&clave);
            return 1;
        }
    }
}

