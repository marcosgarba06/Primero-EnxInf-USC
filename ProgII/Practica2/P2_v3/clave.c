#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
typedef char TELEMENTO;
/* tipo de datos de los elementos de la contraseña */
/* implementación, ahora ya no es opaca pues estamos en el .c de
la librería, del tipo clave */
typedef struct {
    TELEMENTO *datos; /*caracteres de la contraseña*/
    unsigned short tam; /*tamaño de la clave*/
    unsigned short cifrado; /*numero para el cifrado*/
}STCLAVE; /*definición del tipo de datos estructura*/
typedef STCLAVE *clave; /*puntero a estructura*/

/* para crear una clave se proporciona un puntero a la dirección de
memoria donde el TAD almacenará la clave, la función crear del TAD
asignará memoria, y guardará encapsuladamente la longitud y número
de cifrado de la clave */

void crear(clave *c, unsigned short longitud, unsigned short cifrado)
{
    unsigned short i;
/* crea espacio para el struct */
    *c = (clave) malloc(sizeof(STCLAVE));
/* dentro del struct creamos el bloque dinámico para almacenar los
caracteres de la clave */
    (*c)->datos = (TELEMENTO *) malloc(longitud*sizeof(TELEMENTO));
/* guardamos el tamaño y número de cifrado como datos encapsulados en el
struct del TAD */
    (*c)->tam = longitud;
    (*c)->cifrado = cifrado;
/* inicializamos la contraseña a letras a */
    for (i=0; i<longitud; i++)
        *((*c)->datos + i) = 'a';
}
/* para introducir individualmente cada posición de la clave */
void asignar(clave *c, unsigned short posicion, TELEMENTO valor)
{
/* en lugar de asignar el valor que nos dan representamos el carácter
ASCII correspondiente a ese carácter ASCII desplazado el offset que
corresponda según su posición en la clave y el número de cifrado*/
    *((*c)->datos + posicion) = valor + posicion*(*c)->cifrado;
}

/*esta función libera la memoria que hay almacenada en clave, borrando
tanto los caracteres de la clave, como el tamaño de la clave y el cifrado
de la misma*/
void liberar(clave *c){
    if(*c!=NULL){
        free((*c)->datos); //Libera los caracteres de la clave
        /*No se liberan ni tam ni cifrado porque estas variables no 
        trabajan con la memoria dinámica*/ 
        free(*c); //Libera la estructura STCLAVE
        *c=NULL; 
        //Destruye el acceso a la memoria liberada enviando el puntero a NULL para evitar errores
    }
}

TELEMENTO recuperar(clave c, int posicion) {
    /*función que devuelve el caracter correspondiente a la 
    posición dada, pero descifrada*/
    if (c==NULL) {  
        printf("Error: No se ha creado una clave.\n");
        return -1;  
    }
    if(posicion >= c->tam||posicion<0){ 
        printf("Error: Esa posicion no es válida.\n");
        return -1;
    }

    return *(c->datos + posicion) - posicion*c->cifrado; // Descifrar el carácter
}

unsigned short longitud(clave c){
    /*función que devuelve la longitud de la clave creada*/
    return c->tam;
}

void imprimir(clave c, int modo){
/*funcion para imprimir la clave con 3 posibles modos 
MODO 0: Escribe los caracteres normalmente.
MODO 1: El programa escribe la clave pero sustituyendo cada carácter original por un asterisco
MODO 2: El programa ocultará sólo parte de la clave aleatoriamente
*/
    if (c == NULL) {
        printf("Error: Hay que crear la clave.\n");
        return; //asi la función termina si no hay clave creada
    }
    
    if (modo==0){
    /*modo que imprime la clave normalmente*/
        printf("La clave es:\n");

        for(int i=0;i<longitud(c);i++){
            printf("%c", recuperar(c,i));
        }
        printf("\n");
    }

    else if (modo==1){
    /*modo que imprime la clave con asteriscos*/
        printf("La clave es:\n");

        for (int i=0;i<longitud(c);i++){
            printf("*");
        }
        printf("\n");
    }

    else if(modo==2){
        srand(time(NULL)); 
        /*hace que la funcion rand devuelva un valor aleatorio segun la hora que es
        para poder usarla hay que añadir la librería time.h. 
        El metodo para decidir si el caracter se muestra o no será dividir el numero entre 2
        si el resto es 1 entonces el numero se muestra, por el contrario, si el resto es 0 
        se mostrará un * */
        printf("La clave es:\n");

        for(int i=0;i<longitud(c);i++){
            if(rand()%2==0){
                printf("*");
            }
            else{
                printf("%c", recuperar(c,i));
            }
        }
        printf("\n");
    }
}

void cadena2clave(clave *c, char *string, int cifrado){
    /*función que crea una clave a partir de una cadena de caracteres*/
    unsigned int tamanho;
    tamanho=strlen(string);
    crear(c,tamanho,cifrado);

    for(unsigned short i=0; i<longitud(*c); i++){
        asignar(c, i, string[i]);
    }
}

int compruebaclave(clave c, int modo2){
    /*funcion para comprobar si una clave escrita por el usuario es correcta con
    2 modos diferentes:
        MODO 0: Pide la clave completa
        MODO 1: Oculta varios caracteres con * y pide al usuario el resto*/
    char cad[200];
    if(modo2==0){
        printf("Introduzca la clave: ");
        scanf("%s", cad);
       
        if (strlen(cad) != longitud(c)){
            return 0;
        }

        for(int i=0; i<longitud(c);i++){
            if(cad[i]!=recuperar(c,i)){
                printf("\nLa contraseña es incorrecta.");
                return 0;
            }
        }
        return 1;
    }
    else if(modo2==1){
       /* Al igual que en imprimir se usan las funciones
       de aleatroización para decidir que caracteres mostrar */
        srand(time(NULL));
        char ocultos[longitud(c) + 1]; //guarda caracteres ocultos
        int numOcultos = 0; 
        /* Al igual que en imprimir se divide el numero entre 2 y si el resto es
        * 1 se muestra y si es 0 se oculta con un */
        for(int i = 0; i < longitud(c); i++) {
            if(rand() % 2 == 1) {
                ocultos[i] = 1;
                numOcultos++;
            } else {
                ocultos[i] = 0;
            }
        }

        if(numOcultos == 0) {
            ocultos[longitud(c)-1]=1;
            numOcultos++;
        }

        printf("La clave para que se complete es: ");
        for(int i = 0; i < longitud(c); i++) {
            if(ocultos[i] == 0) {
                printf("%c", recuperar(c, i));
            } else {
                printf("*");
            }
        }
        printf("\n");
        char respuesta[200];
        printf("Introduzca (sin espacios) los caracteres ocultos con un * en la clave anterior: ");
        scanf("%s", respuesta);
        if(strlen(respuesta) != numOcultos) {
            printf("Error: Longitud incorrecta\n");
            return 0;
        }
        int indiceResp = 0;
        for(int i = 0; i < longitud(c); i++) {
            
            if(ocultos[i] == 1) {
                if(respuesta[indiceResp] != recuperar(c, i)) {
                    return 0;
                }
                indiceResp++;
            }
        }
        return 1;
    }else{ //se utiliza este else para que no haya errores
        printf("Modo no valido\n");
        return 0;
    }
}


//ACTUALIZACION TAD CLAVE PARA OBTENER CONTRASEÑA DESCIRADA
void obtenerContrasena(clave c, char *cad){
    for(int i = 0;i<longitud(c);i++){
        cad[i] = recuperar(c,i); 
        /*Como recuperar obtiene cada caracter descifrado entonces
        se crea la clave descifrada descifrando elemento a elemento
        la clave existente*/ 
    }
} 