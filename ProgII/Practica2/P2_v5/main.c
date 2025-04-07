#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista-1.h"
#include "cola-1.h"
#include "clave.h"

#define MAX_EMAIL 255
#define MAX_PASS 255

//Funciones del menú de opciones
void darDeAlta(TLISTA *lista);
void darDeBaja(TLISTA *lista);
void solicitudesVenta(TLISTA lista, TCOLA *cola);
void numeroSoli(TCOLA cola);
void ventaEntradas(TCOLA *cola);
void salir(TLISTA *lista, TCOLA *cola);

//Funciones auxiliares para el funcionamiento del programa

int emailExiste(TLISTA lista, char *email);
void crearContrasena(char *contrasena, clave *clave1, unsigned short cifrado);
int verificarContrasena(clave clave1, char *contrasena);
void _strip_line(char *linea);
void cargarUsuarios(TLISTA *lista, const char *nombreFichero);
void guardarUsuarios(TLISTA lista, const char *nombreFichero);

int main(int argc, char *argv[]) {
    /*if (argc != 3 || strcmp(argv[1], "-f") != 0) {
        fprintf(stderr, "Uso: %s -f NOMBRE_DEL_FICHERO\n", argv[0]);
        return 1;
    }*/

    TLISTA listaUsuarios;
    TCOLA colaVenta;
    crearLista(&listaUsuarios);
    crearCola(&colaVenta);
    
    cargarUsuarios(&listaUsuarios, argv[2]);
    //El argv[2] es el nombre del archivo al ejecutar el programa

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
                solicitudesVenta(listaUsuarios, &colaVenta);
                break;

            case 4:
                //Devuelve el numero de solicitudes en la cola
                numeroSoli(colaVenta);
                break;

            case 5:
                //Vende entradas a los primeros usuarios almacenados en la cola y quita a estos usuarios dde la cola
                ventaEntradas(&colaVenta);
                break;

            case 6:
            /*Finaliza el programa almacenando los usuarios de la lista en el archivo y borrando la lista y la cola 
            creadas durante la ejecucion del programa*/
            guardarUsuarios(listaUsuarios, argv[2]); //El argv[2] es el nombre del archivo al ejecutar el programa
            destruirCola(&colaVenta);
            destruirLista(&listaUsuarios);
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
    scanf("%hu", &usuarioNuevo.cifrado); getchar();

    crearContrasena(contrasenaTemp, &usuarioNuevo.clave1, usuarioNuevo.cifrado); //Crea la contraseña usando la funcion cadena2clave

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

void solicitudesVenta(TLISTA lista, TCOLA *cola) {
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

void numeroSoli(TCOLA cola) {
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

void ventaEntradas(TCOLA *cola) {
    
    int numEntradas;
    printf("Introduzca el numero de entradas a vender: ");
    scanf("%d", &numEntradas); getchar();

    if (numEntradas <= 0 || esColaVacia(*cola)) 
    {
        printf("No hay suficientes solicitudes en la cola.\n");
        return;
    }

    for (int i = 0; i < numEntradas; i++) 
    {
        if (esColaVacia(*cola) == 1) //Si la cola es vacia sale del for
        {
            break;
        }
        
        TIPOELEMENTOCOLA elementoCola;
        consultarPrimerElementoCola(*cola, &elementoCola);

        printf("Entrada vendida a: %s\n", elementoCola.email);
        suprimirElementoCola(cola);
    }
}

// Función para eliminar el retorno de carro de una línea
void _strip_line(char *linea) {
    linea[strcspn(linea, "\r\n")] = 0;
}

// Función para cargar usuarios desde un fichero
void cargarUsuarios(TLISTA *lista, const char *nombreFichero) {
    FILE *archivo = fopen(nombreFichero, "r");
    if (!archivo) {
        printf("Error al abrir el fichero de usuarios.\n");
        return;
    }

    char linea[512];
    while (fgets(linea, sizeof(linea), archivo)) {
        _strip_line(linea);

        TIPOELEMENTOLISTA usuario;
        char contrasena[MAX_EMAIL];

        char *token = strtok(linea, ",");
        if (token != NULL) strcpy(usuario.correo, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(usuario.apellidos, token);
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(usuario.nombre, token);
        token = strtok(NULL, ",");
        if (token != NULL) usuario.edad = atoi(token); //atoi para pasar el ascii leido a un entero
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(contrasena, token);
        token = strtok(NULL, ",");
        if (token != NULL) usuario.cifrado = (unsigned short)atoi(token); //Unsigned short para que sean tipos compatibles 

        crear(&usuario.clave1, strlen(contrasena), usuario.cifrado);
        cadena2clave(&usuario.clave1, contrasena, usuario.cifrado);

        insertarElementoLista(lista, finLista(*lista), usuario);
    }

    fclose(archivo);
}

// Función para guardar usuarios en un fichero
void guardarUsuarios(TLISTA lista, const char *nombreFichero) {
    FILE *archivo = fopen(nombreFichero, "w");
    if (!archivo) {
        printf("Error al abrir el fichero de usuarios.\n");
        return;
    }

    TIPOELEMENTOLISTA usuario;
    TPOSICION pos = primeroLista(lista);
    char contrasena[MAX_EMAIL];

    while (pos != finLista(lista)) {
        recuperarElementoLista(lista, pos, &usuario);
        obtenerContrasena(usuario.clave1, contrasena);
        fprintf(archivo, "%s,%s,%s,%d,%s,%hu\n", usuario.correo, usuario.apellidos, usuario.nombre, usuario.edad, contrasena, usuario.cifrado);
        pos = siguienteLista(lista, pos);
    }

    fclose(archivo);
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

void crearContrasena(char *contrasena, clave *clave1, unsigned short cifrado) {
    cadena2clave(clave1, contrasena, cifrado);
}

int verificarContrasena(clave clave1, char *contrasena) {
    int correcto;
    correcto = compruebaclave(clave1, 0);
    return correcto; // Modo 0: Pide la clave completa
}





