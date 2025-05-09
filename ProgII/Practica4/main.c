#include <stdio.h>
#include <stdlib.h>

typedef struct{ 
    char id[10];
    int tiempo;
}Procesos;

void leerProcesosArchivo(FILE *archivo, Procesos *proceso, int n);
int contarNumeroProcesos(FILE *file);
int calcularTiempoEspera(Procesos procesos[], int n);
int calcularTiempoEsperaDecreciente(Procesos procesos[], int n);

//Funciones quicksort modificadas para que tengan tipoelemento Procesos
void swap(Procesos *a, Procesos *b);
int partition(Procesos array[], int low, int high);
void quickSort(Procesos array[], int low, int high);
void printArray(Procesos array[], int size);
void printArrayDecreciente(Procesos array[], int size);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Hay que pasarle al programa el nombre del arvchivo");
    }

    FILE *archivo = fopen(argv[1], "r");

    if (!archivo) {
        perror("Error al abrir el archivo");
        return 1;
    }

    int numeroProcesos;
    numeroProcesos = contarNumeroProcesos(archivo); //Cuenta el numero de procesos

    Procesos *vectorprocesos;
    vectorprocesos = (Procesos*)malloc(numeroProcesos * sizeof(Procesos)); 
    //Asignacion de memoria para el vector de procesos
    if (vectorprocesos == NULL) {
        perror("Error al asignar memoria");
        fclose(archivo);
        return 1;
    }
    
    leerProcesosArchivo(archivo, vectorprocesos, numeroProcesos); //Lee el archivo y lo guarda en el vector de procesos
    quickSort(vectorprocesos, 0, numeroProcesos - 1); //Ordena el vector en orden creciente
    int opcion;
    do {
        printf("\n========== Menú de opciones ==========\n");
        printf("1. Estrategia voraz seleccionando tareas en orden creciente de tiempo de proceso\n");
        printf("2. Estrategia voraz seleccionando tareas en orden decreciente de tiempo de proceso\n");
        printf("3. Salir\n");
        printf("====================================\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("\nEstrategia voraz en orden creciente:\n");
                printf("Resultado:\n");
                printArray(vectorprocesos, numeroProcesos);
                int tiempoesperatotal=calcularTiempoEspera(vectorprocesos, numeroProcesos);
                printf("Tiempo total de espera: %d", tiempoesperatotal);
                break;
            
            case 2:
                printf("\nEstrategia voraz en orden decreciente:\n");
                printf("Resultado:\n");
                printArrayDecreciente(vectorprocesos, numeroProcesos);
                int tiempoesperadec= calcularTiempoEsperaDecreciente(vectorprocesos, numeroProcesos);
                printf("Tiempo total de espera: %d", tiempoesperadec);
                break;
            
            case 3:
                printf("Saliendo...\n");
                free(vectorprocesos);
                break;

            default:
                printf("Opción no válida.\n");
                break;
        }        
    } while (opcion != 3);

    fclose(archivo);
    return 0;
}




void leerProcesosArchivo(FILE *archivo, Procesos *proceso, int n) { 
    //Funcion que lee los datos de los procesos del archivo y los guarda en un vector de estructuras del tipo Procesos
    for (int i = 0; i < n; i++) {
        fscanf(archivo, "%s %d", proceso[i].id, &proceso[i].tiempo);
    }
}

int contarNumeroProcesos(FILE *file) 
{
    char buffer[1024]; //Se guarda lo que se lee en fgets en cada interaccion
    int contador = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    { //Cuando fgets devuelva NULL significa que ya ha llegado al EOF (final del archivo)
        contador++; 
    }
    rewind(file); //regresa el archivo a la posicion inicial
    return contador;
}

//Funcion para calcular el tiempo de espera
int calcularTiempoEspera(Procesos procesos[], int n) 
{
  int tiempoEspera = 0;
  int tiempoProcesosAnteriores = 0;  // Lleva la suma de los tiempos de los procesos anteriores

  // El primer proceso no espera, así que empezamos desde el segundo
  for (int i = 1; i < n; i++) 
  {
      tiempoProcesosAnteriores += procesos[i - 1].tiempo;  //Suma el tiempo del proceso anterior
      tiempoEspera += tiempoProcesosAnteriores;       //Acumulamos el tiempo de espera
  }

  return tiempoEspera;
}

int calcularTiempoEsperaDecreciente(Procesos procesos[], int n) //Calcula el tiempo de espera de los procesos ordenados en orden decreciente
{
  int tiempoEspera = 0;
  int tiempoProcesosAnteriores = 0;  // Lleva la suma de los tiempos de los procesos anteriores

  // El primer proceso no espera, así que empezamos desde el segundo
  for (int i = n-2; i >= 0; i--) 
  {
      tiempoProcesosAnteriores += procesos[i + 1].tiempo;  //Suma el tiempo del proceso anterior
      tiempoEspera += tiempoProcesosAnteriores;       //Acumulamos el tiempo de espera
  }
  return tiempoEspera;
}

//Implementacion de Quick Sort en C obtenida de la web
//function to swap elements 
void swap(Procesos *a, Procesos *b) { //Se cambia el tipo elemento de int a struct
    Procesos t = *a;
    *a = *b;
    *b = t;
  }
  
  //function to find the partition position
  int partition(Procesos array[], int low, int high) {
    
    //select the rightmost element as pivot
    int pivot = array[high].tiempo; //Se ordenan por el tiempo que lleva el proceso
    
    //pointer for greater element
    int i = (low - 1);
  
    //traverse each element of the array
    //compare them with the pivot
    for (int j = low; j < high; j++) {
      if (array[j].tiempo <= pivot) { //Tambien cambia porque se ordenan por tiempo
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
  
  void quickSort(Procesos array[], int low, int high) { //Cambia el int a Procesos
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
  void printArray(Procesos array[], int size) { //Cambia de int a Procesos
    for (int i = 0; i < size; ++i) {
      printf("Proceso: %s  Tiempo: %d  \n", array[i].id, array[i].tiempo); //Se imprimen los 2 elementos del struct
    }
    printf("\n");
  }

  void printArrayDecreciente(Procesos array[], int size) { //Imprime array en orden inverso, es decir de forma decreciente
    for (int i = size-1; i >=0; i--)
    {
      printf("Proceso: %s  Tiempo: %d  \n", array[i].id, array[i].tiempo); //Se imprimen los 2 elementos del struct
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