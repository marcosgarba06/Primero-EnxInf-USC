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