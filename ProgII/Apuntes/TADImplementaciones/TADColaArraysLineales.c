#define MAX 100 /* número máximo de elementos que podrá almacenar la cola */

typedef int TELEMENTO;

typedef struct { TELEMENTO arrayelementos[MAX];
    int principio, final;
} STCOLA;

typedef STCOLA * TCOLA;

void ColaVacia (TCOLA *q)
{
    *q = (TCOLA) malloc (sizeof(STCOLA)) ;
    (*q)->final = -1;
    (*q)->principio = -1;
}

int EsColaLlena (TCOLA q)
{
    if (q->final == MAX-1) return 1;
    else return 0;
}

void EliminarCola (TCOLA *q)
{
    int respuesta;
    respuesta = EsColaVacia(*q);
    if (respuesta == 1) printf("ERROR, la cola no tiene elementos");
    else (*q)->principio++;
}

void AnadirCola (TCOLA *q, TELEMENTO e)
{
    int respuesta;
    respuesta = EsColaLlena (*q);
    if (respuesta == 1) printf("ERROR, la cola esta llena");
    else { 
        (*q)->final++ ;
        (*q)->arrayelementos [(*q)->final] = e;
    }
}
int EsColaVacia (TCOLA q)
{
    int respuesta = (q->final == q->principio);
    return respuesta;
}

void PrimeroCola (TCOLA q , TELEMENTO *e)
{
    int respuesta;
    respuesta = EsColaVacia(q);
    if (respuesta == 1) printf("ERROR, la cola no tiene elementos");
    else *e = q->arrayelementos [q->principio + 1];
}



