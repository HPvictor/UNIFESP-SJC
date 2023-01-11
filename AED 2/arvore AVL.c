#include<stdio.h>
#include<stdlib.h>
//Struct para a arvore AVL
struct Node {
	int chave;
	struct Node *esquerda;
	struct Node *direita;
	int altura;
};
//Inicio do TAD
//Função para encontrar o maximo entre dois inteiros
int max(int a, int b);
//Função encontra altura da arvore
int altura(struct Node *N) {
	if (N == NULL)
		return 0;
	return N->altura;
}
int max(int a, int b) {
	return (a > b)? a : b;
}
//Funcao auxiliar que aloca um novo nó com o elemento dado e NULL para os ponteiros esquerdo e direito
struct Node* newNode(int chave) {
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->chave = chave;
	node->esquerda = NULL;
	node->direita = NULL;
	node->altura = 1;
	return(node);
}
//Função rotaciona para direita
struct Node *direitaRotate(struct Node *y) {
	struct Node *x = y->esquerda;
	struct Node *T2 = x->direita;
	x->direita = y;
	y->esquerda = T2;
	//Atualiza altura
	y->altura = max(altura(y->esquerda), altura(y->direita))+1;
	x->altura = max(altura(x->esquerda), altura(x->direita))+1;
	return x;
}

//Função rotaciona para esquerda
struct Node *esquerdaRotate(struct Node *x) {
	struct Node *y = x->direita;
	struct Node *T2 = y->esquerda;
	y->esquerda = x;
	x->direita = T2;
	//Atualiza altura
	x->altura = max(altura(x->esquerda), altura(x->direita))+1;
	y->altura = max(altura(y->esquerda), altura(y->direita))+1;
	return y;
}
//Encontra o balanco do nó N
int getBalance(struct Node *N) {
	if (N == NULL)
		return 0;
	return altura(N->esquerda) - altura(N->direita);
}
struct Node* insert(struct Node* node, int chave) {
	if (node == NULL)
		return(newNode(chave));
	if (chave < node->chave)
		node->esquerda = insert(node->esquerda, chave);
	else if (chave > node->chave)
		node->direita = insert(node->direita, chave);
	else 
		return node;
	node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
	int balance = getBalance(node);
	//Se o nó nao estiver balanceado pode ser 4 casos
	//Esquerdo Esquerdo
	if (balance > 1 && chave < node->esquerda->chave)
		return direitaRotate(node);
	//Direita Direita
	if (balance < -1 && chave > node->direita->chave)
		return esquerdaRotate(node);
	//Esquerda Direita
	if (balance > 1 && chave > node->esquerda->chave) {
		node->esquerda = esquerdaRotate(node->esquerda);
		return direitaRotate(node);
	}
	//Direita Esquerda
	if (balance < -1 && chave < node->direita->chave) {
		node->direita = direitaRotate(node->direita);
		return esquerdaRotate(node);
	}
	return node;
}

struct Node * minValueNode(struct Node* node) {
	struct Node* current = node;
	while (current->esquerda != NULL)
		current = current->esquerda;

	return current;
}

//Funcao recursiva para deletar um nó
struct Node* deleteNode(struct Node* root, int chave) {
	if (root == NULL)
		return root;
	if ( chave < root->chave )
		root->esquerda = deleteNode(root->esquerda, chave);
	else if( chave > root->chave )
		root->direita = deleteNode(root->direita, chave);
	else {
		//nó com um filho
		if( (root->esquerda == NULL) || (root->direita == NULL) ) {
			struct Node *temp = root->esquerda ? root->esquerda : root     ->direita;

			//sem filhos
			if (temp == NULL) {
				temp = root;
				root = NULL;
        //caso 1 filho
			} else 
				*root = *temp;
			free(temp);
		} else {
			//nó com 2 filhos
			struct Node* temp = minValueNode(root->direita);
			root->chave = temp->chave;
			root->direita = deleteNode(root->direita, temp->chave);
		}
	}
	if (root == NULL)
		return root;
	//Encontra altura
	root->altura = 1 + max(altura(root->esquerda), altura(root->direita));
	//Encontra o fator de balanceamento e ve se esta balanceada
	int balance = getBalance(root);
	//Caso não esteja balanceada, existem 4 casos
	//Esquerdo Esquerdo
	if (balance > 1 && getBalance(root->esquerda) >= 0)
		return direitaRotate(root);

	//Esquerdo Direita
	if (balance > 1 && getBalance(root->esquerda) < 0) {
		root->esquerda = esquerdaRotate(root->esquerda);
		return direitaRotate(root);
	}

	//Direita Direita
	if (balance < -1 && getBalance(root->direita) <= 0)
		return esquerdaRotate(root);

	//Direita Esquerda
	if (balance < -1 && getBalance(root->direita) > 0) {
		root->direita = direitaRotate(root->direita);
		return esquerdaRotate(root);
	}
	return root;
}
struct Node* locateChave(struct Node* root, int chave) {
	if (root == NULL)
		return NULL;
	if (root->chave > chave)
		return locateChave(root->esquerda, chave);
	if (root->chave < chave)
		return locateChave(root->direita, chave);
	return root;
}
//Fim do TAD
//Função main do programa
int main() {
	struct Node *root = NULL, *Loc = newNode(0);
	int i = 0;
	while (i >= 0) {
		scanf("%d", &i);
		if (i < 0)
			break;
		root = insert(root, i);
	}
	int l = 0, d = 0;
	if (root->esquerda != NULL)
		l = root -> esquerda -> altura;
	if (root -> direita != NULL)
		d = root -> direita -> altura;
	printf("%i, %i, %i\n", max(d, l), l, d);
	i = 0;
	int loc;
	while (i >= 0) {
		scanf("%d", &i);
		if (i < 0)
			break;
		if (locateChave(root, i))
			root = deleteNode(root, i);
		else
			root = insert(root, i);
	}
	scanf("%d", &i);
	Loc = locateChave(root, i);
	if (Loc != NULL) {
		int l2 = 0, d2 = 0;
		if (Loc -> esquerda)
			l2 = Loc -> esquerda -> altura;
		if (Loc->direita)
			d2 = Loc->direita->altura;
		printf("%i, %i, %i\n", max(d2, l2), l2, d2);
	} else
		printf("Valor nao encontrado\n");
	return 0;
}