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

//Funciones auxiliares para el funcionamiento del programa

int emailExiste(TLISTA lista, char *email);
void crearContrasena(char *contrasena, clave *clave1, unsigned short cifrado);
int verificarContrasena(clave clave1, char *contrasena);
void _strip_line(char *linea);
void cargarUsuariosArchivo(TLISTA *lista, const char *nombreFichero);
void guardarUsuariosArchivo(TLISTA lista, const char *nombreFichero);

int main(int argc, char *argv[]) {

    TLISTA listaUsuarios;
    TCOLA colaVenta;
    crearLista(&listaUsuarios);
    crearCola(&colaVenta);
    
    if(argc<3){ //Si el num de argumentos pasados es menor a 3 entonces el programa da error
        printf("Para ejecutar el programa hay que pasar como argumentos -f y el nombre del archivo");
        destruirCola(&colaVenta);
        destruirLista(&listaUsuarios);
        return 1;
    }

    cargarUsuariosArchivo(&listaUsuarios, argv[2]);
    //El argv[2] es el nombre del archivo al ejecutar el programa

    int tam;

    int opcion;
    do {
        printf("\n======= Menú de opciones =======\n");
        printf("1. Dar de alta\n");
        printf("2. Dar de baja\n");
        printf("3. Recepcion de solicitudes de entradas\n");
        printf("4. Numero de solicitudes\n");
        printf("5. Venta de entradas\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion); getchar(); //Limpiar con getchar() lo que quede guardado en el buffer de entrada

        switch (opcion) {
            case 1: //Dar de alta un usuario
                darDeAlta(&listaUsuarios);

                tam = longitudLista(listaUsuarios);
                printf("Hay %d usuarios registrados.\n", tam);
                break;

            case 2: //Dar de baja un usuario
                darDeBaja(&listaUsuarios);

                tam = longitudLista(listaUsuarios);
                printf("Hay %d usuarios registrados.\n", tam);
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
            guardarUsuariosArchivo(listaUsuarios, argv[2]); //El argv[2] es el nombre del archivo al ejecutar el programa
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

    TIPOELEMENTOLISTA nuevoUsu;
    char contrasenaTemp[MAX_PASS];

    printf("Introduzca el email: ");
    scanf("%s", nuevoUsu.correo); getchar();

    if (emailExiste(*lista, nuevoUsu.correo) == 1)
    { 
        /*Comprobar si el email ya esta asociado a un usuario, si esta asociado ya a otro usuario da error y no permite 
        crear el usuario*/
        printf("Error: El email ya está asociado a un usuario.\n");
        return;
    }


    printf("Nombre: ");
    scanf("%s", nuevoUsu.nombre); getchar();

    printf("Apellidos: ");
    scanf("%[^\n]", nuevoUsu.apellidos); getchar();

    printf("Edad: ");
    scanf("%d", &nuevoUsu.edad); getchar();

    if (nuevoUsu.edad < 18) { 
        //Comprobacion mayoria de edad
        printf("Error: Hay que ser mayor de edad para poder registrarse.\n");
        return;
    }

    printf("Contraseña: ");
    scanf("%s", contrasenaTemp); getchar();  

    printf("Numero de cifrado para la contraseña: ");
    scanf("%hu", &nuevoUsu.cifrado); getchar();

    crearContrasena(contrasenaTemp, &nuevoUsu.clave1, nuevoUsu.cifrado); //Crea la contraseña usando la funcion cadena2clave

    insertarElementoLista(lista, finLista(*lista), nuevoUsu); //Inserta el usuario en la lista al final de la misma
    printf("Usuario registrado con exito.\n");
}

void darDeBaja(TLISTA *listausuarios) {

    char email[MAX_EMAIL];
    char password[MAX_PASS]; 
    TPOSICION posicion; posicion = primeroLista(*listausuarios);
    TIPOELEMENTOLISTA usuario;

    printf("Email: ");
    scanf("%s", email); getchar();

    while (posicion != finLista(*listausuarios)) 
    { 
        //Bucle que recorre la lista completa para comprobar si hay un usuario con ese email

        recuperarElementoLista(*listausuarios, posicion, &usuario);

        if (strcmp(usuario.correo, email) == 0) 
        {
            if (verificarContrasena(usuario.clave1, password)) 
            {
                suprimirElementoLista(listausuarios, posicion);
                liberar(&usuario.clave1); //Libera la clave
                printf("Usuario eliminado con exito.\n");
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
    //Si no encuentra en todo el bucle al usuarii para eliminar entonces da un mensaje de error
}

void solicitudesVenta(TLISTA lista, TCOLA *cola) {

    char email[MAX_EMAIL];
    char password[MAX_EMAIL]; 

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
            printf("Error: El email no esta registrado.\n");
        }

        TPOSICION pos = primeroLista(lista);
        TIPOELEMENTOLISTA usuario;

        while (pos != finLista(lista)) 
        {
            recuperarElementoLista(lista, pos, &usuario);
            if (strcmp(usuario.correo, email) == 0) 
            {
                if (verificarContrasena(usuario.clave1, password)) 
                {
                    TIPOELEMENTOCOLA elementoCola;
                    strcpy(elementoCola.email, email);
                    anadirElementoCola(cola, elementoCola);
                    printf("Solicitud añadida.\n");
                    
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
    int flag = 0;
    TIPOELEMENTOCOLA contadorcola;
    TCOLA colaTemp; //Se crea una cola temporal para no modificar la cola original
    
    crearCola(&colaTemp);

    while (esColaVacia(cola) == 0)  
    /*Mientras la cola no este vacia se consulta el primer elemto, se elimina este de la cola original y se añade a una 
    cola temporal, ademas con cada iteracion del while se aumenta 1 al contador de elementos de la cola*/
    {
        consultarPrimerElementoCola(cola, &contadorcola);
        suprimirElementoCola(&cola);
        anadirElementoCola(&colaTemp, contadorcola);
        flag++;
    }

    while (esColaVacia(colaTemp) == 0) 
    /*Se have lo mismo que antes pero al reves, en este caso mientras la cola temporal no sea vacia se consulta el primer 
    elemnto de la misma,se elimina de la cola temporal y se añade a la cola original para que asi la cola original no tenga
    ningun cambio con respecto a la que entra en la funcion*/
    {
        consultarPrimerElementoCola(colaTemp, &contadorcola);
        suprimirElementoCola(&colaTemp);
        anadirElementoCola(&cola, contadorcola);
    }

    destruirCola(&colaTemp); //Se elimina la cola temporal

    printf("Hay %d solicitudes.\n", flag);
}

void ventaEntradas(TCOLA *cola) {
    //
    int cantidadEntradas;
    printf("Numero de entradas a la venta: ");
    scanf("%d", &cantidadEntradas); getchar();

    if (cantidadEntradas <= 0) //Comprobar que el numero de solicitudes sea correcto
    {
        printf("Error: Numero de solicitudes no válido.\n");
        return;
    }
    if (esColaVacia(*cola)) //Comprobar que la cola de solicitudes no sea vacia
    {
        printf("Error: No hay elementos en la cola de solicitudes.\n");
        return;
    }

    for (int i = 0; i < cantidadEntradas; i++)  
    {
        if (esColaVacia(*cola) == 1) //Si la cola es vacia sale del bucle
        {
            break;
        }
        
        TIPOELEMENTOCOLA usuario;
        consultarPrimerElementoCola(*cola, &usuario);

        printf("Vendida a: %s\n", usuario.email);
        suprimirElementoCola(cola); //Al vender la entrada el usuario se elimina de la cola
    }
}

void _strip_line(char *linea) { 
    //Funcion que elimina el retorno y el salto de linea de una cadena
    linea[strcspn(linea, "\r\n")] = 0;
}

// Función para cargar usuarios desde un fichero
void cargarUsuariosArchivo(TLISTA *lista, const char *nombreFichero) {
    
    FILE *file = fopen(nombreFichero, "r");

    if (file == NULL) { //Para evitar errores de que el archivo no se abra de forma correcta
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[1024];

    while (fgets(linea, sizeof(linea), file))
    {
        _strip_line(linea); //Elimina el salto de linea y el retorno de la cadena

        TIPOELEMENTOLISTA usuario;
        char password[MAX_EMAIL];

        char *token = strtok(linea, ",");

        if (token != NULL){
            strcpy(usuario.correo, token);
        }
        token = strtok(NULL, ",");

        if (token != NULL){ 
            strcpy(usuario.apellidos, token);
        }
        token = strtok(NULL, ",");

        if (token != NULL) {
            strcpy(usuario.nombre, token);
        }
        token = strtok(NULL, ",");

        if (token != NULL) {
            usuario.edad = atoi(token); //atoi para pasar el ascii leido a un entero
        } 
        token = strtok(NULL, ",");

        if (token != NULL){ 
            strcpy(password, token);
        }
        token = strtok(NULL, ",");

        if (token != NULL) {
            usuario.cifrado = (unsigned short)atoi(token); //Unsigned short para que sean tipos compatibles 
        } 

        cadena2clave(&usuario.clave1, password, usuario.cifrado); //Crea clave a partir de cadena de caracteres
        insertarElementoLista(lista, finLista(*lista), usuario);
    }

    fclose(file);
}

void guardarUsuariosArchivo(TLISTA lista, const char *nombreFichero) {
    
    FILE *file = fopen(nombreFichero, "w");

    if (file == NULL) { //Para evitar errores de que el archivo no se abra de forma correcta
        printf("Error al abrir el archivo.\n");
        return;
    }

    TIPOELEMENTOLISTA usuario;
    TPOSICION pos = primeroLista(lista);
    char password[MAX_EMAIL];

    while (pos != finLista(lista)) //Bucle que recorre toda la lista de usuarios
    { 
        recuperarElementoLista(lista, pos, &usuario);
        obtenerContrasena(usuario.clave1, password); 
        //Recupera la contrasela cifrada y la guarda en el array de password
        fprintf(file, "%s,%s,%s,%d,%s,%hu\n", usuario.correo, usuario.apellidos, usuario.nombre, usuario.edad, password, usuario.cifrado); 
        //Escribe en el archivo los distintos elementos de la lista separados por comas 
        pos = siguienteLista(lista, pos);
    }
    fclose(file);
}

int emailExiste(TLISTA lista, char *email) {

    TPOSICION posicion = primeroLista(lista);
    TIPOELEMENTOLISTA usu;
    while (posicion != finLista(lista))  //Bucle que recorre la lista de usuarios
    {
        recuperarElementoLista(lista, posicion, &usu);
        if (strcmp(usu.correo, email) == 0) { 
        //Si los emails son iguales la funcion strcmp devuelve 0 entonces emailExiste devuelve 1
            return 1;
        }
        posicion = siguienteLista(lista, posicion);
    }
    return 0;
}

void crearContrasena(char *contrasena, clave *clave1, unsigned short cifrado) {
    //Utilizo esta funcion porque creando la clave con cadena2clave directamente daba fallo de segmento y de esta forma no (no se por que)
    cadena2clave(clave1, contrasena, cifrado);
}

int verificarContrasena(clave clave1, char *contrasena) {
    int correcto;
    correcto = compruebaclave(clave1, 0); //Comprueba ckave usando el modo 0 para que pida la clave completa
    return correcto;
}





