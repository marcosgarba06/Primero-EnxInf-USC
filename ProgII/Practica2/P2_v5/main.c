#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista-1.h"
#include "cola-1.h"
#include "clave.h"

#define FILENAME "usuarios.txt"
#define MAX_EMAIL 255
#define MAX_PASS 255

//Funciones del menú de opciones
void darDeAlta(TLISTA *lista);
void darDeBaja(TLISTA *lista);
void recibirSolicitudes(TLISTA lista, TCOLA *cola);
void consultarSolicitudes(TCOLA cola);
void venderEntradas(TCOLA *cola);
void finalizarPrograma(TLISTA *lista, TCOLA *cola);

//Funciones auxiliares para el funcionamiento del programa
void cargarUsuarios(TLISTA *lista);
void guardarUsuarios(TLISTA lista);
int emailExiste(TLISTA lista, char *email);
void codificarContrasena(char *contrasena, clave *clave1, unsigned short cifrado);
int verificarContrasena(clave clave1, char *contrasena);

int main(int argc, char *argv[]) {
    /*if (argc != 3 || strcmp(argv[1], "-f") != 0) {
        fprintf(stderr, "Uso: %s -f NOMBRE_DEL_FICHERO\n", argv[0]);
        return 1;
    }*/

    TLISTA listaUsuarios;
    TCOLA colaSolicitudes;
    crearLista(&listaUsuarios);
    crearCola(&colaSolicitudes);
    
    cargarUsuarios(&listaUsuarios);
    int tam;

    int opcion;
    do {
        printf("\nMenu Principal:\n");
        printf("1. Dar de alta a un usuario\n");
        printf("2. Dar de baja a un usuario\n");
        printf("3. Iniciar recepcion de solicitudes de entradas\n");
        printf("4. Consultar numero de solicitudes en cola\n");
        printf("5. Vender entradas\n");
        printf("6. Finalizar programa\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion); getchar(); //Limpiar con getchar() lo que quede guardado en el buffer de entrada

        switch (opcion) {
            case 1: //Dar de alta un usuario
                darDeAlta(&listaUsuarios);

                tam = longitudLista(listaUsuarios);
                printf("Hay %d usuarios registrados en la lista.\n", tam);
                break;

            case 2: //Dar de baja un usuario
                darDeBaja(&listaUsuarios);

                tam = longitudLista(listaUsuarios);
                printf("Hay %d usuarios registrados en la lista.\n", tam);
                break;

            case 3: 
            /*Recibe las solicitudes y las almacena en una cola virtual. Las solicitudes se hacen por el correo del 
            usuario, ya que este es unico para cada uno de los usuarios, hace fatla tambien que se compruebe la clave
            del usuario para poder hacer la solicitud*/
                recibirSolicitudes(listaUsuarios, &colaSolicitudes);
                break;

            case 4:
                //Devuelve el numero de solicitudes en la cola
                consultarSolicitudes(colaSolicitudes);
                break;

            case 5:
                //Vende entradas a los primeros usuarios almacenados en la cola y quita a estos usuarios dde la cola
                venderEntradas(&colaSolicitudes);
                break;

            case 6:
            /*Finaliza el programa almacenando los usuarios de la lista en el archivo y borrando la lista y la cola 
            creadas durante la ejecucion del programa*/
                finalizarPrograma(&listaUsuarios, &colaSolicitudes);
                break;

            default:
                printf("Opcion no valida.\n");

        }
    } while (opcion != 6);

    return 0;
}

void darDeAlta(TLISTA *lista) {

    TIPOELEMENTOLISTA usuarioNuevo;
    char contrasenaTemp[MAX_PASS];
    unsigned short cifrado;

    printf("Introduzca el email: ");
    scanf("%s", usuarioNuevo.correo); getchar();

    if (emailExiste(*lista, usuarioNuevo.correo) == 1)
    { 
        /*Comprobar si el email ya esta asociado a un usuario, si esta asociado ya a otro usuario da error y no permite 
        crear el usuario*/
        printf("Error: El email ya está asociado a un usuario.\n");
        return;
    }


    printf("Nombre: ");
    scanf("%s", usuarioNuevo.nombre); getchar();

    printf("Apellidos: ");
    scanf("%[^\n]", usuarioNuevo.apellidos); getchar();

    printf("Edad: ");
    scanf("%d", &usuarioNuevo.edad); getchar();

    if (usuarioNuevo.edad < 18) { 
        //Comprobacion mayoria de edad
        printf("Error: Hay que ser mayor de edad para poder registrarse.\n");
        return;
    }

    printf("Contraseña: ");
    scanf("%s", contrasenaTemp); getchar();  

    printf("Numero de cifrado para la contraseña: ");
    scanf("%hu", &cifrado); getchar();

    codificarContrasena(contrasenaTemp, &usuarioNuevo.clave1, cifrado); //Crea la contraseña usando la funcion cadena2clave

    insertarElementoLista(lista, finLista(*lista), usuarioNuevo); //Inserta el usuario en la lista al final de la misma
    printf("Usuario dado de alta.\n");
}

void darDeBaja(TLISTA *listausuarios) {

    char email[MAX_EMAIL];
    char contrasena[MAX_PASS]; 

    printf("Introduzca el email: ");
    scanf("%s", email); getchar();

    TPOSICION posicion;
    posicion = primeroLista(*listausuarios);
    TIPOELEMENTOLISTA usuario;

    while (posicion != finLista(*listausuarios)) 
    { 
        //Bucle que recorre la lista completa para comprobar si hay un usuario con ese email

        recuperarElementoLista(*listausuarios, posicion, &usuario);

        if (strcmp(usuario.correo, email) == 0) 
        {
            if (verificarContrasena(usuario.clave1, contrasena)) 
            {
                suprimirElementoLista(listausuarios, posicion);
                printf("Usuario dado de baja.\n");
                liberar(&usuario.clave1);
                return;
            } else 
            {
                printf("Error: Contraseña incorrecta.\n");
                return;
            }
        }
        posicion = siguienteLista(*listausuarios, posicion);
    }
    printf("Error: Usuario no encontrado.\n");
}

void recibirSolicitudes(TLISTA lista, TCOLA *cola) {
    char email[MAX_EMAIL];
    char contrasena[MAX_EMAIL]; // Usamos el mismo tamaño que el correo para la contraseña

    while (1) //Porque se debe repetir hasta que se introduzca el 0 por tanto haya un break
    {
        printf("Introduzca el email para hacer la solicitud: ");
        scanf("%s", email);

        if (strcmp(email, "0") == 0) //Si recibe 0 entonces se sale del bucle
        { 
            break;
        }

        if (emailExiste(lista, email)==0) 
        { 
            //Comprueba que el email existe, si no existe se imprime un error y vuelve al bucle
            printf("Error: Usuario no encontrado.\n");
        }

        TPOSICION pos = primeroLista(lista);
        TIPOELEMENTOLISTA usuario;

        while (pos != finLista(lista)) 
        {
            recuperarElementoLista(lista, pos, &usuario);
            if (strcmp(usuario.correo, email) == 0) 
            {
                if (verificarContrasena(usuario.clave1, contrasena)) 
                {
                    TIPOELEMENTOCOLA elementoCola;
                    strcpy(elementoCola.email, email);
                    anadirElementoCola(cola, elementoCola);
                    printf("Solicitud añadida a la cola.\n");
                    
                } else {
                    printf("Error: Contraseña incorrecta.\n");
                }
                break;
            }
            pos = siguienteLista(lista, pos);
        }
    }
}

void consultarSolicitudes(TCOLA cola) {
    /*Funcion que devuelve la cantidad de solicitudes en la cola*/
    int contador = 0;
    TIPOELEMENTOCOLA contadorcola;
    TCOLA colaTemp; //Se crea una cola temporal para no modificar la cola original
    
    crearCola(&colaTemp);

    while (esColaVacia(cola) == 0) 
    {
        consultarPrimerElementoCola(cola, &contadorcola);
        suprimirElementoCola(&cola);
        anadirElementoCola(&colaTemp, contadorcola);
        contador++;
    }

    while (esColaVacia(colaTemp) == 0) 
    {
        consultarPrimerElementoCola(colaTemp, &contadorcola);
        suprimirElementoCola(&colaTemp);
        anadirElementoCola(&cola, contadorcola);
    }

    destruirCola(&colaTemp);

    printf("Actualmente hay %d solicitudes en la cola.\n", contador);
}

void venderEntradas(TCOLA *cola) {
    int numEntradas;
    printf("Introduzca el numero de entradas a vender: ");
    scanf("%d", &numEntradas);

    if (numEntradas <= 0 || esColaVacia(*cola)) 
    {
        printf("No hay suficientes solicitudes en la cola.\n");
        return;
    }

    for (int i = 0; i < numEntradas && !esColaVacia(*cola); i++) 
    {
        TIPOELEMENTOCOLA elementoCola;
        consultarPrimerElementoCola(*cola, &elementoCola);
        printf("Entrada vendida a: %s\n", elementoCola.email);
        suprimirElementoCola(cola);
    }
}

void finalizarPrograma(TLISTA *lista, TCOLA *cola) { 
    /*Para finalizar el programa guarda la lista en el archivo y destruye tanto la lista
    como la cola creadas durante la ejecución del programa.*/
    guardarUsuarios(*lista);
    destruirLista(lista);
    destruirCola(cola);
}

void cargarUsuarios(TLISTA *lista) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) 
    {
        perror("Error al abrir el fichero");
        return;
    }

    TIPOELEMENTOLISTA usuario;
    unsigned short cifrado;
    while (fscanf(file, "%s %s %s %d %hu", usuario.correo, usuario.nombre, usuario.apellidos, &usuario.edad, &cifrado) == 5) 
    {
        cadena2clave(&usuario.clave1, usuario.correo, cifrado); // Suponemos que la clave es el correo cifrado
        insertarElementoLista(lista, finLista(*lista), usuario);
    }

    fclose(file);
}

void guardarUsuarios(TLISTA lista) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) 
    {
        perror("Error al abrir el fichero");
        return;
    }

    TPOSICION pos = primeroLista(lista);
    TIPOELEMENTOLISTA usuario;
    while (pos != finLista(lista)) 
    {
        recuperarElementoLista(lista, pos, &usuario);
        unsigned short cifrado = longitud(usuario.clave1); // Asumimos que el cifrado es la longitud de la clave
        fprintf(file, "%s %s %s %d %hu\n", usuario.correo, usuario.nombre, usuario.apellidos, usuario.edad, cifrado);
        pos = siguienteLista(lista, pos);
    }

    fclose(file);
}

int emailExiste(TLISTA lista, char *email) {
    TPOSICION pos = primeroLista(lista);
    TIPOELEMENTOLISTA usuario;
    while (pos != finLista(lista)) 
    {
        recuperarElementoLista(lista, pos, &usuario);
        if (strcmp(usuario.correo, email) == 0) {
            return 1;
        }
        pos = siguienteLista(lista, pos);
    }
    return 0;
}

void codificarContrasena(char *contrasena, clave *clave1, unsigned short cifrado) {
    cadena2clave(clave1, contrasena, cifrado);
}

int verificarContrasena(clave clave1, char *contrasena) {
    int correcto;
    correcto = compruebaclave(clave1, 0);
    return correcto; // Modo 0: Pide la clave completa
}





