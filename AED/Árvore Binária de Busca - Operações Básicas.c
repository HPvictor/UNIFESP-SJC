#include <stdio.h>
#include <stdlib.h>
 
 
typedef struct SNo *TArvbin;                    ///TArvbin eh um apontador de TNo
 
typedef struct {                                ///Estrutura tipo Item
    int info;
}TItem;
 
typedef struct SNo {                            ///Estrutura tipo TNo
    TItem item;
    TArvbin esq, dir;
}TNo;
 
/***********************===============TAD ARVORE BINARIA DE BUSCA=============*************************/
 
// Implemente aqui o arquivo TADABB.h
 
 
void TArvbin_Inicia(TArvbin *arvore);
int TArvbin_Insere(TItem x, TArvbin *arvore);
void TArvbin_Pesquisa(int *num, TItem *x, TArvbin *arvore);
void sucessor(TArvbin arvore, TArvbin *NO);
void TArvbin_Retira(TItem x, TArvbin *arvore);
void PreOrdem(TArvbin arvore);
 
 
/***********************===============TAD ARVORE BINARIA DE BUSCA=============*************************/
 
// Implemente aqui o arquivo TADABB.c
 
 
 
void TArvbin_Inicia(TArvbin *arvore){                   ///Inicia um apontador de TArbin com NULL
    *arvore = NULL;
}
 
int TArvbin_Insere(TItem x, TArvbin *arvore){           ///Insere um no com o item na arvore alocando memoria para um TNo
    if(*arvore == NULL){
        *arvore = (TArvbin)malloc(sizeof(TNo));
        (*arvore)->item = x;
        (*arvore)->esq = NULL;
        (*arvore)->dir = NULL;
        return 1;
    }
    if(x.info < (*arvore)->item.info){
        TArvbin_Insere(x, &(*arvore)->esq);
        return 1;
    }
    if(x.info > (*arvore)->item.info){
        TArvbin_Insere(x, &(*arvore)->dir);
        return 1;
    }
    else
        return 0;
}
 
void TArvbin_Pesquisa(int *num, TItem *x, TArvbin *arvore){     ///Pesquisa na arvore se o TItem existe se sim, num recebe 1
    if(*arvore == NULL){
        return;
    }
    if(x->info < (*arvore)->item.info){
        TArvbin_Pesquisa(num, x, &(*arvore)->esq);
        return;
    }
    if(x->info > (*arvore)->item.info){
        TArvbin_Pesquisa(num, x, &(*arvore)->dir);
        return;
    }
    else{
        *x = (*arvore)->item;
        *num = 1;
    }
}
 
void sucessor(TArvbin arvore, TArvbin *NO){                     ///Se o no retirado tem dois filhos o sucessor vai para o lugar dele(substituido pelo no mais a esquerda da subarvore direita)
    TArvbin aux;
    if((*NO)->esq != NULL){
        sucessor(arvore, &(*NO)->esq);
        return;
    }
    arvore->item = (*NO)->item;
    aux = *NO;
    *NO = (*NO)->dir;
    free(aux);
}
 
void TArvbin_Retira(TItem x, TArvbin *arvore){                  ///Retira o item desejado da arvore
    if(*arvore == NULL){
        return;
    }
    if(x.info < (*arvore)->item.info){
        TArvbin_Retira(x, &(*arvore)->esq);
        return;
    }
    if(x.info > (*arvore)->item.info){
        TArvbin_Retira(x, &(*arvore)->dir);
        return;
    }
    if((*arvore)->dir == NULL){
        *arvore = (*arvore)->esq;
        return;
    }
    if((*arvore)->esq == NULL){
        *arvore = (*arvore)->dir;
        return;
    }
    sucessor(*arvore, &(*arvore)->dir);
}
 
void PreOrdem(TArvbin arvore){                      ///Percorre a arvore em PreOrdem e imprime cada no como parenteses alinhados
    if(arvore != NULL){
        printf("(C%d", arvore->item.info);
        PreOrdem(arvore->esq);
        PreOrdem(arvore->dir);
        printf(")");
    }
    else
        printf("()");
 
}
 
 
/***********************=============PROGRAMA PRINCIPAL============*************************/
 
int main()
{
    TArvbin arvore;
    TItem x;
    int i, N, num=0;
    TArvbin_Inicia(&arvore);
    scanf("%d", &N);                                ///quantidade de nos a inserir
    for(i = 0; i < N; i++){
        scanf("%d", &x.info);                       ///sequencia de nos para inserir
        TArvbin_Insere(x, &arvore);
    }
    scanf("%d", &x.info);                           ///no a ser pesquisado
    TArvbin_Pesquisa(&num, &x, &arvore);
    if(num == 1)
        TArvbin_Retira(x, &arvore);                 ///Se estiver na arvore, sera retirado
    else
        TArvbin_Insere(x, &arvore);                 ///Se não, sera inserido
    PreOrdem(arvore);                               ///Imprime com parenteses alinhados
    printf("\n");
    return 0;
}

/*caso teste
7
3 4 9 2 5 1 8
5
*/