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
void darDeAlta(TLISTA *listaUsu);
void darDeBaja(TLISTA *listaUsu);
void imprimirTodosLosUsuarios(TLISTA listaUsu);

int main(int argc, char const *argv[])
{
    TLISTA listaUsu;
    crearLista(&listaUsu);
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

            imprimirTodosLosUsuarios(listaUsu);

            break;
        
        case 'b': 
            darDeBaja(&listaUsu);
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

void darDeAlta(TLISTA *listaUsu){

    TIPOELEMENTOLISTA nuevoUsu;
    unsigned short cifrado;
    char contrasenaTemp[MAX_PASS];
    clave clave1;
    TPOSICION pos;
    
    getchar();
    printf("Introduzca el nombre del usuario: ");
    scanf("%s", nuevoUsu.nombre); getchar();
    
    printf("Introduzca los apellidos del usuario: ");
    scanf("%[^\n]", nuevoUsu.apellidos); getchar(); 
    
    printf("Introduzca el email del usuario: ");
    scanf("%s", nuevoUsu.correo); getchar();
    
    printf("Introduzca la edad del usuario: ");
    scanf("%d", &nuevoUsu.edad);

    
    if (nuevoUsu.edad < 18){ //Comprobar que e maior de idade 
        printf("Error: El usuario debe ser mayor de edad.\n");
        return;
    }
    
    printf("Introduzca la clave: ");
    while (getchar() != '\n'); fgets(contrasenaTemp, sizeof(contrasenaTemp), stdin); //Almacena o escrito por teclado para a clave
    
    int len = strlen(contrasenaTemp); 
    if (len > 0 && contrasenaTemp[len-1] == '\n') { //Eliminar o \0 da cadea
        contrasenaTemp[len-1] = '\0';
    }
    
    printf("Inroduzca el número para cifrar la clave: ");
    scanf("%hu", &cifrado);
    
    cadena2clave(&clave1, contrasenaTemp, cifrado); //crea clave
    printf("Clave creada con éxito.\n");
    nuevoUsu.clave1 = clave1; //Pone clave en struct
    imprimir(nuevoUsu.clave1,0);
    
    pos = finLista(*listaUsu);
    insertarElementoLista(listaUsu, pos, nuevoUsu); //inserta elemento lista

}


void darDeBaja(TLISTA *listaUsu){
    
    


}


void imprimirTodosLosUsuarios(TLISTA listaUsu) {

    TPOSICION posi = primeroLista(listaUsu);
    TPOSICION fin = finLista(listaUsu);
    int position = 1;

    while (posi != fin) {
        DatUsuario *usuario;
        recuperarElementoLista(listaUsu, posi, usuario);
        printf("Usuario %d:\n", position);
        printf("Correo: %s\n", usuario->correo);
        printf("Nombre: %s\n", usuario->nombre);
        printf("Apellidos: %s\n", usuario->apellidos);
        printf("Edad: %d\n", usuario->edad);
        imprimir(usuario->clave1, 0); 
        // Puedes agregar más detalles si es necesario

        if (siguienteLista(listaUsu, posi) == fin) {
            break;
        }
        posi = siguienteLista(listaUsu, posi);
        position ++;
    }
}



/*TPOSICION final = finLista(*listaUsu);
    if (longitudLista(*listaUsu) > 1) //Porque si hay 0 da fallo de segmento
    {
        while (pos != final) {
            DatUsuario *usuariotemp;
            recuperarElementoLista(*listaUsu, pos, usuariotemp);
            printf("Comparando %s con %s\n", usuariotemp->edad, nuevoUsu.edad);
             // Puedes agregar más detalles si es necesario
            if (strcmp(nuevoUsu.correo, usuariotemp->correo) == 0) 
            {
                printf("Error: El usuario con ese correo ya existe.\n");
                break;
            }
            if (siguienteLista(*listaUsu, pos) == final) { 
            //Porque si no al llegar al final da fallo de segmento
                break;
            }
            pos = siguienteLista(*listaUsu, pos);
            }
        }
    */