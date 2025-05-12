#define MAX 100 /* pero solo podemos guardar 99 */

typedef int TELEMENTO;

typedef struct { TELEMENTO arrayelementos[MAX];
    int principio, final;
} STCOLA;

typedef STCOLA * TCOLA;

int Siguiente ( int pos )
{
    if (pos < MAX - 1) return (pos+1);
    else return 0;
}

int EsColaLlena ( TCOLA q )
{
    int pos_sig = Siguiente(q->final) ;
    if (pos_sig == q->principio) return 1 ;
    else return 0;
}
void ColaVacia (TCOLA * q)
{
    *q = (TCOLA) malloc (sizeof (STCOLA) );
    (*q)->final = MAX - 1; (*q)->principio = MAX - 1;
}

int EsColaVacia ( TCOLA q )
{
    if (q->final == q->principio) return 1;
    else return 0;
}

void PrimeroCola (TCOLA q , TELEMENTO *e)
{
    int respuesta, sig;
    respuesta = EsColaVacia(q);
    if (respuesta == 1) printf("ERROR, la cola no tiene elementos");
    else {
        sig = Siguiente (q->principio);  //En esta implementación de cola circular, principio (el índice del "frente" de la cola) 
        //no almacena el primer elemento directamente, sino que apunta a la posición anterior.
        *e = q->arrayelementos[sig];
    }
}
void EliminarCola (TCOLA * q)
{
    int respuesta, sig;
    respuesta = EsColaVacia(*q);
    if ( respuesta == 1) printf("ERROR, ....");
    else {
        sig = Siguiente ((*q)->principio);
        (*q)->principio = sig; //El principio ahora a donde estaba antes el primer elemento
    }
}

void AnadirCola ( TCOLA * q , TELEMENTO e)
{
    int resp, pos_sig ;
    resp = EsColaLlena (*q) ;
    if (resp == 1) printf("ERROR, la cola esta llena");
    else
    {
        pos_sig = Siguiente ((*q)->final);
        (*q)->final = pos_sig;
        (*q)->arrayelementos [(*q)->final] = e;
    }
}