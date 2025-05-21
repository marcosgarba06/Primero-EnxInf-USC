#include <stdio.h>

typedef int TELEMENTO;
typedef struct nodo
{
TELEMENTO dato;
struct nodo * sig; 
} TNodo;

typedef struct {TNodo * principio, * final; } STCOLA;
typedef STCOLA * TCOLA;

void ColaVacia ( TCOLA * q )
{
    *q = (TCOLA) malloc (sizeof (STCOLA) ) ;
    (*q)->final = NULL; (*q)->principio = NULL;
}

int EsColaVacia ( TCOLA q )
{
    if ( (q->final == NULL) && (q->principio == NULL) ) return 1; //Es vacia si inicio y final son NULL
    else return 0;
}

void PrimeroCola ( TCOLA q, TELEMENTO * e)
{
    int respuesta;
    respuesta = EsColaVacia(q);
    if ( respuesta == 1) printf("ERROR, la cola no tiene elementos");
    else *e = (q->principio)->dato; //El inicio es al dato al que apunta el nodo inicio de la cola
}

void EliminarCola (TCOLA * q)
{
    int respuesta;
    TNodo * aux;
    respuesta = EsColaVacia(*q);
    if ( respuesta == 1 ) printf("ERROR, ");
    else
    {
        aux = (*q)->principio; //se almacena un puntero al nodo que se va a eliminar
        (*q)->principio = aux->sig; //se mueve el inicio al siguiente nodo (que sera el nuevo primer elemento)
        if ((*q)->principio == NULL) //comprueba si la cola se ha quedado vacia
        (*q)->final = NULL;
        free (aux); //libera el nodo viejo que se ha eliminado
    }
}

void AnadirCola (TCOLA * q , TELEMENTO e)
{
    int respuesta;
    TNodo * aux; //se crea un nuevo nodo auxiliar y se reserva su memoria
    aux = (TNodo *) malloc (sizeof (TNodo) );
    aux->dato = e; //se pone el dato en este nodo
    aux->sig = NULL; //como es el ultimo nodo apunta a null
    respuesta = EsColaVacia (*q); //se comprueba si esta vacia la cola  
    if (respuesta == 1) //si lo está se asigna el nuevo nodo como inicio
        (*q)->principio = aux;
    else (*q)->final->sig = aux; //si no esta vacia se añade tras el final anterior
    (*q)->final = aux; //actualiza el puntero final de la cola
}