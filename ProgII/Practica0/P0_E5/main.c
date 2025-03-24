/*
a) Los valores de las que se pueden ver en el Panel Watch al ejecutar el programa paso a paso son las direcciones de memoria de los
4 elementos del array en notación hexadecimal. En este caso son:
    &a[0]= 0x7fffffffe0e0
    &a[1]= 0x7fffffffe0e4
    &a[2]= 0x7fffffffe0e8
    &a[3]= 0x7fffffffe0ec

El valor mayor es el de la posición de a[3] (&a[3]) y el menor es el de la posición de a[0] (&a[0]). Esto indica que los valores de los
elementos del array van guardados en memoria de manera consecutiva. LA diferencia entre 2 posiciones consecutivas es de 4 bytes debido a
que en la memoria los elementos de un array se guardan de forma consecutiva y cada int necesita 4 bytes para guardar su valor. Además 
como un float también es de tamaño 4 bytes para guardarlo en memoria en el array raiz[4] (un array de floats) sus elementos también van 
consecutivos y separados por 4 bytes.
*/
#include <stdio.h>

double absoluto(double n) {
    //return (n < 0) ? n : n;
    return(n<0) ? -n : n;
}

//double sqrt(int numero) { Método de Newton (aproximación)
double sqrt(double numero){
    double margen = 0.000001;
    double estimacion = 1.0;
    // Mientras haya una diferencia notable.
    // Es decir, que el cuadrado de nuestra estimación difiera mucho del número
    while (absoluto((estimacion * estimacion) - numero) >= margen)
    {
        double cociente = numero / estimacion;
        double promedio = (cociente + estimacion) / 2.0;
        estimacion = promedio;
    }
    return estimacion;
}


int main(int argc, char const *argv[])
{
    int a[4];
    float raiz[4]; 

    for (int i = 0; i < 4; i++){ 
        //Bucle for para pedir por consola los elementos del array
        printf("\nValor de la posición %d ", i);
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < 4; i++){ 
        //Bucle for para hacer la raiz de cada elemento del array
        if (a[i] >= 0){
        raiz[i]=sqrt(a[i]);
        }
        else{
            printf("No se puede hacer la raiz cuadrada de un numero negativo.\n");
        }
    }

    for (int i = 0; i < 4; i++){
        //Bucle for para imprimir el resultado de la raiz
        if (a[i] >= 0){
            printf(" Raiz de a[%d] = %.10f\n", i, raiz[i]);
        }
        else{
            printf("No existe la raiz de a[%d] al ser un número negativo.\n", i);
        }
    }

    return 0;
}
