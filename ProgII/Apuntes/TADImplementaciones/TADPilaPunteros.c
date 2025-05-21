#include <stdio.h>
typedef int TELEMENTO ;
/* tipo de datos correspondiente a los elementos de la pila */

typedef struct nodo
{
    TELEMENTO dato;
    struct nodo * sig; 
} TNodo;

typedef TNodo *TPILA;

void PilaVacia (TPILA *p)
{
    *p = NULL; /*Valor NULO en un puntero, para indicar que
    la pila está vacía. */
}
int EsVacia (TPILA p )
{
    if (p == NULL)
    return 1;
    else return 0;
}

void Push(TPILA *p , TELEMENTO e)
{
    TPILA q; //se declara el nuevo nodo
    q= (TPILA) malloc (sizeof(TNodo)); //se reserva espacio para un nuevo nodo
    q->dato = e ; //se asigna al nuevo nodo el elemento
    q->sig = *p ; //el nuevo nodo apunta al nodo que estaba en la cima
    *p = q; //ahora el puntero pila apunta al nuevo nodo
}

void Cima (TPILA p, TELEMENTO * pe)
{
    int respuesta = EsVacia(p);
    if (respuesta == 1)
    printf ("ERROR, la pila no tiene elementos\n");
    else *pe = p->dato; //el dato al que apunta p se almacena en pe
}

void Pop(TPILA * p)
{
    TPILA q; //puntero a un TNODO auxiliar 
    int respuesta;
    respuesta = EsVacia(*p);
    if (respuesta==1)
    printf("ERROR, ....\n");
    else
    {
        q = *p; //se almaceena una copia del puntero p en q
        *p = (*p)->sig; //hacemos que p apunte al siguiente nodo
        free(q); //liberamos q
    }
}

void destruye(TPILA *p) {
    TPILA q;
    while (*p != NULL) {
        q = *p;
        *p = (*p)->sig;
        free(q);
    }
}