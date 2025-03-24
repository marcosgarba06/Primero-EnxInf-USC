/*
 * PROGRAMA PARA REALIZAR OPERACIONES BÁSICAS CON UNA MATRIZ DINÁMICA
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES
 * LADO DE LA SENTENCIA CORREGIDA
 *
 * PRUEBAS:
 * - número de filas o columnas: 0 
 *      Con filas o columnas 0 da error al crear la matriz, por tanto la suma, el producto, obtener elemento e imprimir matrices da error ya que no se ha podido crear la matriz.
 * 
 * - acceder a un dato con índices negativos
 *      Al acceder a un dato con indices negativos da un mensaje de error.
 * 
 * - verificar todas las operaciones, para matrices pequeñas (2,3 filas/cols)
 *      - número de filas y columnas distintos en las dos matrices 
 *      - número de filas igual y de columnas distinto
 *      - número de columnas igual y de filas distinto
 *         Tanto la suma como la multiplicación dan error por su tamaño a menos que el numero de filas y columas de A y B sean iguales que se
 *         que se pueden hacer ambas operaciones o que el numero de filas de A sea igual al numero de columnas de B que se puede hacer la 
 *         multiplicación.   
 * 
 * ¿Se está liberando correctamente la memoria en todos los casos?
 *      No, hay casos en los que la memoria se elimina de forma incorrecta, ya que aunque se elimine la matriz y su memoria reservada de forma 
 *      correcta al destruir la matriz (eliminando primero los datos y luego la matriz) los punteros que apuntan a estas matrices no regresan a
 *      apuntar a NULL, esto es que se quedan apuntando a la direccion donde estaba la matriz eliminada y para evitar errores cada vez que se
 *      elimine una matriz hay que enviar su respectivo puntero a NULL.
 *  
 *  Una vez modificada la liberación de memoria, prueba a crear las matrices, destruirlas y salir del programa (opción '0'). ¿Está finalizando la
 *  ejecución de forma correcta?
 *      No, porque antes de salir del programa se deben eliminar todas las matrices creadas durante la ejecución, ademas de que hay que enviar sus 
 *      respectivos punteros al valor NULL. De esta forma se evitan todos los posibles errores.
 */

#include "matriz.h"

int main(int argc, char** argv) {
    int f, c;//int i, k, f, c;
    float valor;
    //matriz *a = 0, *b = 0, *aux = 0;
    matriz *a = NULL, *b = NULL, *aux = NULL;
    char opcion, resp;


    do {
        printf("---------------------Libreria matrices---------------------\n\n");
        printf("1-Crear matrices\n");
        printf("2-Asignar elementos\n");
        printf("3-Obtener elemento\n");
        printf("4-Imprimir matrices\n");
        printf("5-Sumar matrices\n");
        printf("6-Producto de matrices\n");
        printf("7-Eliminar matrices\n");
        printf("0-Salir\n");
        printf("Opcion: ");
        //scanf(" %c", opcion);
        scanf(" %c", &opcion);

        switch (opcion) {
            case '0':
                destruirMatriz(a);//Hay que destruir todas las matrices si se quiere salir para que no queden en la memoria
                destruirMatriz(b);
                destruirMatriz(aux);
                a = NULL;
                b = NULL;
                aux = NULL;
                printf("Saliendo del programa\n");
                break;

            case '1':
                destruirMatriz(a); //Hay que destruir todas las matrices antes de crear otras para que no ocurran errores
                destruirMatriz(b);
                destruirMatriz(aux);
                a = NULL; 
                b = NULL;
                aux = NULL;

                printf("Introduzca el numero de filas de la matriz 'a': ");
                scanf("%d", &f); //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'a': ");
                scanf("%d", &c); 
                a = crearMatriz(f, c);

                printf("Introduzca el numero de filas de la matriz 'b': ");
                scanf("%d", &f); //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'b': ");
                scanf("%d", &c);
                b = crearMatriz(f, c);

                break;

            case '2':

                if (a!=NULL){ //Pongo este if para evitar errores
                printf("Matriz A\n");
                for (f = 0; f < a->filas; f++)
                    for (c = 0; c < a->columnas; c++) {
                        printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                        scanf("%f", &valor);
                        asignarElemento(f, c, valor, a);
                    }
                }
                else{
                    printf("Hay que definir primero el numero de filas y columnas de A\n");
                }

                if(b!=NULL){
                printf("Matriz B\n");
                for (f = 0; f < b->filas; f++)
                    for (c = 0; c < b->columnas; c++) {
                        printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                        scanf("%f", &valor);
                        asignarElemento(f, c, valor, b); //asignarElemento(f, c, valor, a);
                    }
                }
                else{
                    printf("Hay que definir primero el numero de filas y columnas de B");
                }

                break;

            case '3':
                do {
                    printf("De que matriz quieres ver un elemento? (a/b): ");
                    scanf(" %c", &resp);
                } while (resp != 'a' && resp != 'b');

                printf("Introduce fila y columna (fila columna): ");
                scanf("%d %d", &f, &c);
                
                if ((resp == 'a') && (a != NULL)) { //if (resp == 'a') {
                    //valor = obtenerElemento(f, c, b);
                    valor = obtenerElemento(f-1, c-1, a);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                } else if ((resp == 'b') && (b != NULL)) { //} else if (resp == 'b') {
                    //valor = obtenerElemento(f, c, a);
                    valor = obtenerElemento(f-1, c-1, b);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                }

                if ((resp == 'a') && (a == NULL)) { //Creo estos ifs para evitar errores
                    printf("Hay que definir la matriz A\n");
                }
                if ((resp == 'b') && (b == NULL)) { 
                    printf("Hay que definir la matriz B\n");
                }
                break;
            
            case '4':
                printf("Matriz A\n");
                imprimirMatriz(a);
                printf("Matriz B\n");
                imprimirMatriz(b);
                break;

            case '5':
                aux = suma(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                aux = NULL;
                break;

            case '6':
                aux = producto(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                aux = NULL; 
                //destruirMatriz(aux);
                break;

            case '7':
                destruirMatriz(a);  
                destruirMatriz(b);
                destruirMatriz(aux); //Añado tambien aux por si acaso
                a = NULL; //Así a y b apuntan a NULL y no a donde estaba la matriz antes de destruirla
                b = NULL;
                printf("Matrices eliminadas...\n");
                break;

            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion != '0');

    return (EXIT_SUCCESS);
}
