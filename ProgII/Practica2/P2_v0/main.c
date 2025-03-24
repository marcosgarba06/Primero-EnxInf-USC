#include <stdio.h>
#include "clave.h"
#include "cola-1.h"
#include "lista-1.h"


int main(int argc, char const *argv[])
{
    char opcion;
    do
    {
        printf("========= Seleccione una opcion =========");
        printf("\na) Dar de alta a un usuario.");
        printf("\nb) Dar de baja a un usuario.");
        printf("\nc) Recepción de solicitudes de entradas.");
        printf("\nd) Ver el numero de solicitudes para el evento.");
        printf("\ne) Venta de entradas.");
        printf("\n s) Salir del programa.");
        
        switch (opcion)
        {



        case 's':
            printf("Saliendo del programa...\n");
            break;
        
        default:
            break;
        }
    } while (opcion!='s');
    
    return 0;
}
