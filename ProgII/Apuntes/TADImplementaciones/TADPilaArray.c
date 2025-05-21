//IMPLEMENTACION POR ARRAYS
#define MAX 100 /* núm. máx de elementos que podrá almacenar la pila */

typedef int TELEMENTO ; /* tipo de datos correspondiente a los elementosde la pila */

typedef struct {
    TELEMENTO arrayelementos[MAX];
    int cima;
} STPILA ;

typedef STPILA* TPILA; /* concretamos el tipo abstracto */

void PilaVacia (TPILA *p)
{
    *p = (TPILA) malloc(sizeof(STPILA));
    (*p)->cima = -1; /*Valor asignado por nosotrospara indicar que la pila está vacía. */
}

int EsLlena (TPILA p)
{
    if (p->cima == MAX-1)
    return 1;
    else return 0;
}

int EsVacia (TPILA p )
{
    if (p->cima == -1) return 1;
    else return 0;
}

void Push (TPILA *p, TELEMENTO e)
{
    int resp = EsLlena(*p);
    if (resp == 1) printf("ERROR, la pila está llena\n");
    else {
        (*p)->cima++; //se amplia el puntero que indica la cima
        (*p)->arrayelementos[(*p)->cima] = e ; 
        //se añade el nuevo elemento en la posicion que se deja libre al mover el puntero a cima
    }
}

void Cima (TPILA p, TELEMENTO * pe)
{
    int respuesta = EsVacia(p);
    if (respuesta==1)
    printf("ERROR, la pila no tiene elementos\n");
    else
    *pe = p->arrayelementos [p->cima];
}
void Pop (TPILA *p)
{
    int respuesta = EsVacia(*p);
    if (respuesta == 1)
    printf("ERROR, la pila no tiene elementos\n");
    else (*p)->cima = (*p)->cima - 1;
}