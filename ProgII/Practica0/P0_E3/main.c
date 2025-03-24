/*
 * PROGRAMA PARA CALCULAR LA RAÍZ CUADRADA Y EL MÁXIMO COMÚN DIVISOR DE DOS NÚMEROS ENTEROS
 * PEDIDOS AL USUARIO/A POR TECLADO.
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE VS CODE. 
 * EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES. DOCUMENTAR LAS CORRECCIONES 
 * INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 * 
 * PRUEBAS: USAR LOS SIGUIENTES CASOS PASANDOLOS TANTO COMO ARGUMENTOS COMO DEJANDO QUE EL PROGRAMA PIDA LOS VALORES
 * 10 2 (sqrt=3.162278, gcd=2)
 * 2 10 (sqrt=1.414214, gcd=2)
 * 49 7 (sqrt=7., gcd=7)
 * -5 1 (sqrt no existe por ser negativo, gcd=1)
 * -5 -3 (sqrt no existe por ser negativo, gcd=1)
 * 3 0  (sqrt=1.732051, gcd=3)
 * 0 10 (sqrt=0.000977, gcd=10) // La raíz cuadrada de 0 es 0, pero el método de Newton es un método estimado. Podéis comprobarlo jugando con el parámetro margen
 * 0 0 (sqrt=0.000977, gcd=0)
 */

/* a) Corregir los errores comentando la línea incorrecta y poniendo la incorrecta a continuación
 * b) Fija un breakpoint e inicia la ejecución en modo depuración ¿Qué sucede al ejecutar paso a paso
 *    (botón “Step into” [F11]) la sentencia donde se invoca la función sqrt()?
 *    RESPUESTA:
 *      Lo que ocurre es que ejecuta el programa hasta donde esta el brakpoint, pidiendo los valores por teclado. En el momento en el que llega 
 *      a donde esta el breakpoint la ejecución se detiene. Al continuar la ejecución con Step Into [F11]  y llegar a la linea de la llamada a sqrt() abre 
 *      el archivo sqrt.c y, al ir dándole sucesivamente a F11, muestra la ejecucion de sqrt paso a paso, mostrando los valores de todas las variables,
 *      incluidas las de la función absoluto. Cuando termina la ejecución de sqrt vuelve al main y continua mostrando la ejecución del main paso a paso
 *      y mostrando el valor de cada variable hasta llegar a la invocación de gcd donde vuelve a ocurrir lo mismo que con la invocación de sqrt(), la muestra
 *      paso a paso.
 * 
 * c) Al llegar a la función sqrt(), utiliza el botón “STEP OVER” [F10]  en  lugar  del  botón  “Step into” [F11]
 *   ¿Qué  diferencias observas frente a la ejecución del apartado b?
 *   RESPUESTA: 
 *      La diferencia es que utilizando STEP OVER con la tecla F10 no muestra la ejecución de la función paso a paso, sino que ya la realiza, cambia los parámetros 
 *      y las variables a las que retorna la funcion sqrt() y sigue la ejecución con la siguiente linea del main.
 * 
 * d) Repite la ejecución en modo depuración visualizando todas las variables. 
 *    Indica qué sucede con la ventana de variables cuando el flujo del programa continúa DENTRO de la función
 *    Justifica la información que aparece en la solapa "Call Stack"
 *    RESPUESTA: 
 *      La ventana de variables cuando se ejecuta una función muestra los valores que toman las variables locales dentro de esa función, por ejemplo cuando 
 *      ejecuta la funcion sqrt muestra las variables margen, estimación y numero, además cuando la función sqrt llama a la función aboluto también muestra sus 
 *      variables locales.
 *      La información que Call Stack está mostrando es un historial de las funciones que se están ejecutando, es decir, si una función se está ejecutando y llama a otra
 *      Call Stack muestra la función que se está ejecutando además del estado de ejecución de las que se han detenido al invocar a otra función, por ejemplo cuando desde el
 *      main se invoca a la función sqrt Call Stack muestra que se ha guardado el estado de ejecución del main y que se está ejecutando la función sqrt, asimismo, cuando sqrt
 *      llama a la función absoluto esta pestaña muestra que se ha guardado el estado de ejcución de main y sqrt y que se está ejecutando absoluto, pero cuando termina la 
 *      ejecución de la funcion absoluto y se retoma la ejecución de la función sqrt desaparece la pestaña de absoluto ya que el valor de retotno de esta función se ha guardado
 *      en las variables de sqrt, ocurre lo mismo cuando termina la ejecución de la función sqrt.
 *     
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

int main(int argc, char** argv) {

    int a, b;
    float s;
    float g;
    
    //if (argc == 0){
    if(argc==1){
        printf("Introduce dos números enteros: ");
       //scanf("%f%d", a, &b); 
       scanf("%d%d", &a, &b);
    } else {
        //a = argv[0];
        a = atoi(argv[1]);
        //b = argv[1];
        b = atoi(argv[2]);
    }
    
    //if (a > 0){
    if (a>=0){
        s = sqrt(a);
        printf("Raíz cuadrada(%d) = %f\n", a, s);
    }else{
        printf("Error raíz: el parámetro (%d) no es un entero positivo\n", a);
    }
        
    g = gcd(a, b);
    //printf("Máximo común divisor(%f,%d) = %f\n", a, b, g);
    printf("Máximo común divisor(%d,%d) = %f\n", a, b, g);
    return (EXIT_SUCCESS);
}

/*
ERRORES CORREGIDOS:
    1. double en sqrt.c
       double en la libreria operaciones.h
    2. scanf en main.c
    3. atoi en main.c
    4. print en main.c
    5. if argc en main.c
    6. return en sqrt porque si es negativo devuelve 
    -n es decir -3 devuelve 3
    7. if en gcd.c

*/