#include <stdio.h>
#include <stdlib.h>

//Função de busca binaria
int binarySearch(int vet[], int esquerda, int direita, int valor, int contador)
{
	if (direita >= esquerda) {
		int mid = esquerda + (direita - esquerda) / 2;
		//Elemento é o meio
		if (vet[mid] == valor)
			return contador;
		//Elemento presente na esquerda
		if (vet[mid] > valor)
			return binarySearch(vet, esquerda, mid - 1, valor, contador +1);
		//Elemento presente na direita
		return binarySearch(vet, mid + 1, direita, valor, contador +1);
	}
	return -1;
}

int main(void)
{
  int *vet,n,i,valor;
  scanf("%d",&n);
  vet=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++){
    scanf("%d",&vet[i]);
  }
  scanf("%d", &valor);
	int result = binarySearch(vet, 0, n - 1, valor, 0);
	(result == -1)
		? printf("%d nao foi encontrado\n", valor)
		: printf("%d", result);
free(vet);
	return 0;
}
