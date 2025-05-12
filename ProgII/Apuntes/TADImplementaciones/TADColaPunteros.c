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
    if ( (q->final == NULL) && (q->principio == NULL) ) return 1;
    else return 0;
}

void PrimeroCola ( TCOLA q, TELEMENTO * e)
{
    int respuesta;
    respuesta = EsColaVacia(q);
    if ( respuesta == 1) printf("ERROR, la cola no tiene elementos");
    else *e = (q->principio)->dato;
}

void EliminarCola (TCOLA * q)
{
    int respuesta;
    TNodo * aux;
    respuesta = EsColaVacia(*q);
    if ( respuesta == 1 ) printf("ERROR, ");
    else
    {
        aux = (*q)->principio;
        (*q)->principio = aux->sig;
        if ((*q)->principio == NULL)
        (*q)->final = NULL;
        free (aux);
    }
}

void AnadirCola (TCOLA * q , TELEMENTO e)
{
    int respuesta;
    TNodo * aux;
    aux = (TNodo *) malloc (sizeof (TNodo) );
    aux->dato = e;
    aux->sig = NULL;
    respuesta = EsColaVacia (*q);
    if (respuesta == 1)
        (*q)->principio = aux;
    else (*q)->final->sig = aux;
    (*q)->final = aux;
}