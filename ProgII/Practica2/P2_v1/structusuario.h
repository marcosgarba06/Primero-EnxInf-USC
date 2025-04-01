#include "clave.h"

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