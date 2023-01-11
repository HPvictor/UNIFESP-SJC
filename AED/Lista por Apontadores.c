#include <stdio.h>
#include <stdlib.h>
 
typedef struct SNo *TArvore;                        ///TArvore eh um apontador tipo Nó
 
typedef TArvore TItem;                              ///TItem tbm eh um apontador de Nó
 
typedef struct celula *TApontador;                  ///TApontador eh um apontador tipo celula
 
typedef struct {                                    ///estrutura para a informação do nó
    int info;
} TDados;
 
typedef struct celula {                             ///celula que guardara um nó e tera um apontador para a proxima celula e paa a anterior
    TItem item;
    TApontador ante, prox;
}TCelula;
 
typedef struct {                                    ///estrutura tipo lista
    TApontador ultimo;
    int tamanho;
}TLista;
 
typedef struct SNo {                                ///estrutura tipo Nó tera a informacao e e uma lista de filhos nos
    TDados dados;
    TLista filhos;
} TNo;
 
 
/************************************************/
 
 
// Implemente aqui o arquivo TADArvore.h
 
 
///=====================TAD ARVORE=======================
 
 
void TArvore_Inicia(TArvore arvore, TDados x);
int TArvore_EhExterno(TArvore arvore);
int TArvore_NDescendentes(TArvore arvore);
int TArvore_Insere(TArvore arvore, TArvore subArv);
int Imprime(TArvore arvore, TArvore raiz);
 
///=====================TAD LISTA========================
 
 
void TLista_Inicia(TLista *lista);
int TLista_EhVazia(TLista *lista);
int TLista_Insere(TLista *lista, TApontador p, TItem x);
int TLista_Retira(TLista *lista, TApontador p, TItem *px);
TCelula* Retorna(TLista *lista, int p);
 
 
/************************************************/
 
 
// Implemente aqui o arquivo TADArvore.c
 
 
 
void TLista_Inicia(TLista *lista){                              ///Inicia a lista
    TCelula *cabeca = (TCelula*)malloc(sizeof(TCelula));
    cabeca->prox = cabeca;
    cabeca->ante = cabeca;
    lista->ultimo = cabeca;
    lista->tamanho = 0;
}
 
int TLista_EhVazia(TLista *lista){                              /// verifica se a lista eh vazia
    return(lista->ultimo->prox == lista->ultimo);
}
 
int TLista_Insere(TLista *lista, TApontador p, TItem x){
    TCelula *novo = (TCelula*)malloc(sizeof(TCelula));
    novo->item = x;
    if(TLista_EhVazia(lista)){                                  ///Inserir com lista vazia
        novo->prox = lista->ultimo->prox;
        novo->ante = lista->ultimo->ante;
        lista->ultimo->prox = novo;
        lista->ultimo->ante = novo;
        lista->ultimo = novo;
        lista->tamanho++;
        return 1;
    }
    if(p == lista->ultimo->prox){                              ///Inserir na primeira posicao
        novo->prox = p->prox;
        novo->ante = lista->ultimo->prox;
        lista->ultimo->prox->prox = novo;
        novo->prox->ante = novo;
        lista->tamanho++;
        return 1;
    }
    if(p == lista->ultimo){                                         ///Inserir na ultima posicao
        novo->prox = lista->ultimo->prox;
        novo->ante = lista->ultimo;
        lista->ultimo->prox = novo;
        novo->prox->ante = novo;
        lista->ultimo = novo;
        lista->tamanho++;
        return 1;
    }                                                               ///Inserir no meio da lista
    novo->prox = p->prox;
    novo->ante = p;
    p->prox = novo;
    novo->prox->ante = novo;
    lista->tamanho++;
    return 1;
}
 
int TLista_Retira(TLista *lista, TApontador p, TItem *px){
    if(lista->tamanho == 0)                                       ///retorna zero se a lista está vazia
        return 0;
    TApontador aux;
    p = p->prox;
    aux = p;
    if(lista->tamanho == 1){                                         ///Retira quando só tem uma celula
        lista->ultimo->prox->prox = lista->ultimo->prox;
        lista->ultimo->prox->ante = p->ante;
        *px = aux->item;
        lista->tamanho--;
        free(aux);
        return 1;
    }
    if(p == lista->ultimo->prox->prox){                                  ///Retira a primeira celula
        lista->ultimo->prox->prox = lista->ultimo->prox->prox->prox;
        p->prox->ante = p->ante;
        *px = aux->item;
        lista->tamanho--;
        free(aux);
        return 1;
    }
    if(p == lista->ultimo){                                          ///Retira a ultima celula
        p->ante->prox = p->prox;
        p->prox->ante = p->ante;
        lista->ultimo = p->ante;
        *px = aux->item;
        lista->tamanho--;
        free(aux);
        return 1;
    }                                                                ///Retira do meio da lista
    p->ante->prox = p->prox;
    p->prox->ante = p->ante;
    *px = aux->item;
    lista->tamanho--;
    free(aux);
    return 0;
}
 
TCelula* Retorna(TLista *lista, int p){                             ///retorna um apontador para a celula desejada
    TApontador posicao;
    posicao = lista->ultimo->prox;
    if(p > 0){
        int lugar = 0;
        while(lugar < p){
            posicao = posicao->prox;
            lugar++;
        }
    }
return posicao;
}
 
 
///==============================TAD ARVORE==================================
 
 
void TArvore_Inicia(TArvore arvore, TDados x){                          ///Inicia um nó recebendo as informacoes e iniciando a lista de filhos dele
    arvore->dados = x;
    TLista_Inicia(&arvore->filhos);
}
 
int TArvore_EhExterno(TArvore arvore){                                  ///verifica se o nó eh uma folha
    return (arvore->filhos.tamanho == 0);
}
 
int TArvore_NDescendentes(TArvore arvore){                              ///verifica o numero de descendentes do nó
    return (arvore->filhos.tamanho);
}
 
int TArvore_Insere(TArvore arvore, TArvore subArv){                     ///insere o nó 'subarv' como filho do no avore
    TApontador p = Retorna(&arvore->filhos, arvore->filhos.tamanho);
    TLista_Insere(&arvore->filhos, p, subArv);
    return 1;
}
 
 
int Imprime(TArvore arvore, TArvore raiz){                              ///imprime a arvore como parenteses alinhados
    TArvore aux;
    aux = arvore;
    if(arvore == raiz)
        printf("(%d", arvore->dados.info);
    if(arvore->filhos.tamanho == 0)
        return 0;
    while( aux->filhos.ultimo->prox->prox != aux->filhos.ultimo->prox){
        printf("(%d", aux->filhos.ultimo->prox->prox->item->dados.info);
        if(!arvore->filhos.ultimo->prox->prox->item->filhos.tamanho == 0)
            Imprime(aux->filhos.ultimo->prox->prox->item, arvore);
        aux->filhos.ultimo->prox->prox = aux->filhos.ultimo->prox->prox->prox;
        printf(")");
    }
 
return 1;
}
 
///********************************************************************************
 
int main()
{
    int i, N, M, Pi, Fi;
    TDados x;
    scanf("%d %d", &N, &M);
    while( N < 1 || N > 1000)
        scanf("%d", &N);
    TNo arvore[N];
 
    while( M < 0 || M > N)
        scanf("%d", &M);
 
    for(i = 0; i < N; i++){
        x.info = i+1;
        TArvore_Inicia(&arvore[i], x);
    }
 
    for(i = 0; i < M; i++){
        scanf("%d %d", &Pi, &Fi);
        TArvore_Insere(&arvore[Pi-1], &arvore[Fi-1]);
    }
 
    Imprime(&arvore[0], &arvore[0]);
    printf(")\n");
    return 0;
}

/*
4 3
1 2
1 3
2 4
*/