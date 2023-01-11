#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char palavra[50];
} Strs;

int IsValid(Strs t) {
	char c = t.palavra[0];
	int i = 0;
	while (c != 0) {
		if (c < 97 || c > 122) {
			return 1;
		}
		c = t.palavra[++i];
	}
	return 0;
}

void swap (Strs *a, int i1, int i2) {
  Strs hold = a[i1];
  a[i1] = a[i2];
  a[i2] = hold;
}

int checkSub(Strs a, Strs b, int i) {
	if (a.palavra[i] == b.palavra[i])
		return checkSub(a, b, i+1);
	return a.palavra[i] > b.palavra[i] && 1 || 0;
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(Strs *arr, int n, int i) {
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n) {
		if (checkSub(arr[l], arr[largest], 0) == 1)
			largest = l;
	}

	// If right child is larger than largest so far
	if (r < n) {
		if (checkSub(arr[r], arr[largest], 0) == 1)
			largest = r;
	}

	// If largest is not root
	if (largest != i) {
		swap(arr, i, largest);

		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}

// main function to do heap sort
void heapSort(Strs *arr, int n) {
  int i;
	// Build heap (rearrange array)
	for (i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap
	for (i = n - 1; i > 0; i--) {
		// Move current root to end
		swap(arr, 0, i);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

/* A utility function to print array of size n */
void printArray(Strs *arr, int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("%s ", arr[i].palavra);
	  //printf("\n");
}

int main() {
	int n, i, m, ss;

	//printf("Insira o número n: ");
	scanf("%i", &n);

	//printf("Insira as %i palavras: ", n);
	Strs *sstr, *selected;
	sstr = malloc( n * sizeof(Strs) );
	for (i = 0; i < n; i++)
		scanf("%s", sstr[i].palavra);

	//printf("Insira o número de palavras selecionadas: ");
	scanf("%i", &m);

	selected = malloc( m * sizeof(Strs) );

	//printf("Insira o ID das %i palavras a serem selecionadas: ", m);
	for (i = 0; i < m; i++) {
		scanf("%i", &ss);
		selected[i] = sstr[ ss ];
	}
	for (i = 0; i < n; i++) {
		if (IsValid(sstr[i])) {
			printf("a palavra %s eh invalida", sstr[i].palavra);
			return 0;
		}
	}
	printf("build_heap: ");
	printArray(selected, m);
  printf("\n");

	heapSort(selected, m);
	printf("palavras: ");
	printArray(selected, m);
  //printf("4");
  free(sstr);
	return 0;
}