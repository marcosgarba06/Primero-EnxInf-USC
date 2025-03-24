#include <stdlib.h>
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