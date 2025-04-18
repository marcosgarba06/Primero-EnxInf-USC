#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Funciones para la implementaccion del quick sort de la web
void swap(int *a, int *b);
int partition(int array[], int low, int high);
void quickSort(int array[], int low, int high);
void printArray(int array[], int size);

//Funciones para la implementacion del insertion sort de la web
void printArray(int array[], int size);
void insertionSort(int array[], int size);

int main(int argc, char const *argv[])
{

    return 0;
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
void printArray(int array[], int size) {
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