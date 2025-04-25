#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Funciones para la implementaccion del quick sort de la web
void swap(int *a, int *b);
int partition(int array[], int low, int high);
void quickSort(int array[], int low, int high);
void printArray(int array[], int size);

//Funciones para la implementacion del insertion sort de la web
void printArray2(int array[], int size);
void insertionSort(int array[], int size);

//Funcion inicializar vector
void inicializaVectorRand(int *v1, int tam);

//Funciones encontrar suma pares
void encontrarSumaPares(int *v1, int resultado, int tam);

int main(int argc, char const *argv[])
{
  if(argc < 5)
  {
    printf("Error: Se deben introducir los siguientes argumentos: ");
    printf("\nargv[1]: Tamaño inicial");
    printf("\nargv[2]: Tamaño final");
    printf("\nargv[3]: Paso");
    printf("\nargv[4]: Modo(1 busqueda de pares, 2 quicksort  y 3 insertion sort)");
    return -1;
  }
    int tamInicial =  atoi(argv[1]);
    int tamFinal = atoi(argv[2]);
    int paso = atoi(argv[3]);
    int modo = atoi(argv[4]);

    if (tamInicial < 0 || tamFinal <0 || paso < 0)
    {
      printf("Error: Todos los parametros deben ser numeros enteros positivos");
      return -1;
    }

    if (modo < 1 || modo > 3)
    {
      printf("El modo debe ser 1 (busqueda de pares), 2 (quicksort) o 3 (insertion sort)");
    }

    for(int i = tamInicial; i <= tamFinal; i+=paso)
    {
      int *v = (int *)malloc(i * sizeof(int));

      if (v == NULL)
      {
        printf("Error: No se pudo asignar memoria para el vector");
        return -1;
      }

      inicializaVectorRand(v, i); //Funcion que inicializa el vector randomizado del tamaño i
      printf("\nEJECUCION CON TAMAÑO %d\n", i);
      printf("\n");
      switch(modo)
      {
        case 1:
          encontrarSumaPares(v,100,i);
          break;
        case 2:
          printf("Vector desoredenado: \n"); //Imprime el vector desordenado
          printArray(v, i);

          quickSort(v, 0, i-1); //Ordena el vector en orden ascendente con quick sort

          printf("Vector ordenado en orden ascendente: \n"); //Imprime el vector ordenado
          printArray(v, i);

          break;
        case 3:
          printf("Vector desordenado:\n"); //Imprime el vector desordenado
          printArray2(v, i); 

          insertionSort(v, i); //Ordena el vector con insertion sort

          
          printf("Vector ordenado en orden ascendente:\n"); //Imprime el vector ordenado de forma ascendente
          printArray2(v, i);

          break;
        default:
          printf("Error: Modo incorrecto\n");
      }

      free(v);
    }
    return 0;
}


void inicializaVectorRand(int *v1, int tam)
{
  srand(time(NULL));
  for (int i = 0; i < tam; i++)
  {
    v1[i] = rand() % 101; //Porque el rango de los numeros en el vector es de 0 a 100
  }
}

void encontrarSumaPares(int *v1, int resultado, int tam) //Encuentra 2 numeros pares que sumen un resultado en concreto
//Complejidad O(n^2) en el peor caso y 
{
  if (resultado % 2 != 0)
  {
    printf("Error: 2 numeros pares tienen que sumar un numero par\n");
    return;
  }

  clock_t inicio = clock(); //Inicia el contador del tiempo de ejecucion

  for (int i = 0; i < tam; i++) //Recorre el vecrtor
  {
    if (v1[i] % 2 != 0) //Continua si el numero es impar ya que deben ser pares
    {
      continue;
    }
    for (int j = i + 1; j < tam; j++) //Recorre el vector desde la posicion siguiente al primero
    {
      if (v1[j] % 2 == 0 && v1[i] + v1[j] == resultado) //Solo se hace si es par y la suma es el resultado
      {
        printf("Resultados en las posiciones %d y %d del vector\n", i,j); 
        printf("%d  + %d  = %d \n", v1[i], v1[j], resultado);
      } 
    }
  }
  double tiempo = (double)(clock() - inicio) / CLOCKS_PER_SEC; //Calcula el tiempo de ejecucion de la funcion
}


//Implementacion de Quick Sort en C obtenida de la web
//function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

//function to find the partition position
int partition(int array[], int low, int high) {
  
  //select the rightmost element as pivot
  int pivot = array[high];
  
  //pointer for greater element
  int i = (low - 1);

  //traverse each element of the array
  //compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      //if element smaller than pivot is found
      //swap it with the greater element pointed by i
      i++;
      
      //swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  //swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  //return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    //find the pivot element such that
    //elements smaller than pivot are on left of pivot
    //elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    //recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    //recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

//function to print array elements
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

/*
// main function
int main() {
    int data[] = {8, 7, 2, 1, 0, 9, 6};
    
    int n = sizeof(data) / sizeof(data[0]);
    
    printf("Unsorted Array\n");
    printArray(data, n);
    
    // perform quicksort on data
    quickSort(data, 0, n - 1);
    
    printf("Sorted array in ascending order: \n");
    printArray(data, n);
  }
*/

//IMPLEMENTACION DE INSERTION SORT DE LA WEB

// Function to print an array
void printArray2(int array[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void insertionSort(int array[], int size) {
  for (int step = 1; step < size; step++) {
    int key = array[step];
    int j = step - 1;

    // Compare key with each element on the left of it until an element smaller than
    // it is found.
    // For descending order, change key<array[j] to key>array[j].
    while (j >=0 && key < array[j]) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

/*
// Driver code
int main() {
  int data[] = {9, 5, 1, 4, 3};
  int size = sizeof(data) / sizeof(data[0]);
  insertionSort(data, size);
  printf("Sorted array in ascending order:\n");
  printArray(data, size);
}
*/