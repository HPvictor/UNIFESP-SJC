#include <stdio.h>
#include <stdlib.h>

//Funcao imprime
void printTable(int v[], int n) {
  int i;
  for (i = 0; i<n; i++)
    printf("%i ", v[i]);
  printf("\n");
}

//funcao encontra o numero
int EncontraNum(int arr[], int inicio, int fim, int n) {
  while (inicio <= fim) {
    int meio = inicio + (fim - inicio) / 2;
    if (n < arr[meio]) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
  } 
  return inicio;
}
//funcao para o insertion sort
void insertionSort(int arr[], int n, int i) {
  if (n <= 1)
    return;  
  n--;
  insertionSort( arr, n, ++i ); 
  int ultimo = arr[n], j; 
  int loc = EncontraNum(arr, 0, n-1, ultimo); 
  printf("%d %d %d\n", i, ultimo, loc);
  for (j = n-1;j >= 0 && arr[j] > ultimo; j--) {
    arr[j+1] = arr[j];
  }
  arr[j+1] = ultimo;
}

//funcao main
int main(void) {
  int n, *v, i;
  scanf("%i", &n);
  v = malloc(n * sizeof(int));
  for (i=0; i<n; i++)
    scanf("%i", &v[i]); 
  insertionSort(v, n, 0); 
  printTable(v, n);
  return 0;
}