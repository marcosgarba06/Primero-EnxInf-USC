typedef char TELEMENTO;
/* tipo de datos de los elementos de la contraseña */
typedef void *clave;
/* tipo clave opaco, el usuario del TAD sólo ve el .h, no tiene que
saber como está implementada la clave por dentro */
void crear(clave *c, unsigned short longitud, unsigned short cifrado);
/* para crear una clave se proporciona un puntero a la dirección de
memoria donde el TAD almacenará la clave, la función crear del TAD
asignará memoria, y guardará encapsuladamente la longitud y número
de cifrado de la clave */
void asignar(clave *c, unsigned short posicion, TELEMENTO valor);
/* para introducir individualmente cada posición de la clave */
void liberar(clave *c);
/*para vaciar la memoria de la clave almacenada*/
TELEMENTO recuperar(clave c, int posicion);
/*para imprimir un caracter de (descifrado) de la clave de una posicion 
concreta dada por el usuario*/
unsigned short longitud(clave c);
/*para calcular la longitud de una clave creada*/
void imprimir(clave c, int modo);
/*para imprimir la clave con 3 posibles modos 
    MODO 0: Escribe los caracteres normalmente.
    MODO 1: El programa escribe la clave pero sustituyendo cada carácter original por un asterisco
    MODO 2: El programa ocultará sólo parte de la clave aleatoriamente
*/
void cadena2clave(clave *c, char *string, int cifrado);
/*para crear una clave a partir de una cadena de caracteres introducida 
por consola*/
int compruebaclave(clave c, int modo2);
    /*para comprobar si una clave escrita por el usuario es correcta con
    2 modos diferentes:
        MODO 0: Pide la clave completa
        MODO 1: Oculta varios caracteres con * y pide al usuario el resto*/