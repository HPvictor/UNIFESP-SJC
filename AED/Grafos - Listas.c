#include <stdio.h>
#include <stdlib.h>
 
#define MAXVERTICES 100
 
typedef int TVertice;
typedef struct celula *TApontador;
typedef int TAresta;
 
typedef struct {
    TVertice Vertice;
    TAresta Aresta;
}TItem;
 
typedef struct celula {
    TItem item;
    TApontador ante, prox;
}TCelula;
 
typedef struct {
    TApontador ultimo;
    int tamanho;
}TLista;
 
typedef struct {
    TLista Adj[MAXVERTICES];
    int NVertices;
    int NArestas;
}TGrafo;
 
 
/************************************************/
 
// Implemente aqui o arquivo TADLista.h
///TAD GRAFO
int TGrafo_Inicia(TGrafo *grafo, int numVertice);
int TGrafo_ExisteAresta(TGrafo *grafo, TVertice u, TVertice v);
int TGrafo_InsereAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta e);
int TGrafo_RetiraAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta *pE);
int TGrafo_NVertice(TGrafo *grafo);
int TGrafo_NArestas(TGrafo *grafo);
///TAD LISTA
void TLista_Inicia(TLista *lista);
int TLista_EhVazia(TLista *lista);
int TLista_Insere(TLista *lista, TApontador p, TItem x);
int TLista_Retira(TLista *lista, TApontador p, TItem *px);
TCelula* Retorna(TLista *lista, int p);
int operacao(TLista *lista);
 
 
 
/************************************************/
 
// Implemente aqui o arquivo TADLista.c
 
 
void TLista_Inicia(TLista *lista){
    TCelula *cabeca = (TCelula*)malloc(sizeof(TCelula));
    cabeca->prox = cabeca;
    cabeca->ante = cabeca;
    lista->ultimo = cabeca;
    lista->tamanho = 0;
}
 
int TLista_EhVazia(TLista *lista){
    return(lista->ultimo->prox == lista->ultimo);
}
 
int TLista_Tamanho(TLista *lista){
    return lista->tamanho;
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
    if(p == lista->ultimo){                                         ///Inserir na ultima posicao
        novo->prox = lista->ultimo->prox;
        novo->ante = lista->ultimo;
        lista->ultimo->prox = novo;
        novo->prox->ante = novo;
        lista->ultimo = novo;
        lista->tamanho++;
        return 1;
    }
    return 0;
}
 
int TLista_Retira(TLista *lista, TApontador p, TItem *px){
    if(lista->tamanho == 0)                                       ///retorna zero se a lista está vazia
        return 0;
    TApontador aux;
    aux = p;
    if(p == lista->ultimo){                                          ///Retira a ultima celula
        p->ante->prox = p->prox;
        p->prox->ante = p->ante;
        lista->ultimo = p->ante;
        *px = aux->item;
        lista->tamanho--;
        free(aux);
        return 1;
    }
    return 0;
}
 
TApontador Retorna(TLista *lista, int p){                     ///funçao retorna para inserir
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
 
/************************************************/
 
// Implemente aqui o arquivo TADGrafo.c
 
int TGrafo_Inicia(TGrafo *grafo, int numVertice){               ///Inicia o Grafo
    int i;
    grafo->NArestas = 0;
    grafo->NVertices = numVertice;
    for(i = 0; i < numVertice; i++)
        TLista_Inicia(&grafo->Adj[i]);
    return 1;
}
 
int TGrafo_ExisteAresta(TGrafo *grafo, TVertice u, TVertice v){       ///Retorna se existe uma aresta na posição desejada
    TItem adj;
    TLista ListaAdj;
    TLista_Inicia(&ListaAdj);
    int Existe = 0;
    while(TLista_Tamanho(&grafo->Adj[u]) > 0){
        TLista_Retira(&grafo->Adj[u], grafo->Adj[u].ultimo, &adj);
        TLista_Insere(&ListaAdj, ListaAdj.ultimo, adj);
        Existe = (adj.Vertice == v);
        if(Existe){
            break;
        }
    }
    while(TLista_Tamanho(&ListaAdj) > 0){
        TLista_Retira(&ListaAdj, ListaAdj.ultimo, &adj);
        TLista_Insere(&grafo->Adj[u], grafo->Adj[u].ultimo, adj);
    }
return (Existe);
}
 
int TGrafo_InsereAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta e){  ///Insere uma Aresta
    TItem adj;
    adj.Aresta = e;
    adj.Vertice = v;
    if(TLista_Insere(&grafo->Adj[u], grafo->Adj[u].ultimo, adj)){
        grafo->NArestas++;
    return 1;
    }
    else
        return 0;
}
 
int TGrafo_RetiraAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta *pE){    ///Retira uma aresta
    printf("retAresta\n");
    TLista ListaAdj;
    TItem adj;
    int IncideAresta = 0;
    TLista_Inicia(&ListaAdj);
    while(! IncideAresta && TLista_Retira(&grafo->Adj[u], grafo->Adj[u].ultimo, &adj))
    if(adj.Vertice == v){
        *pE = adj.Aresta;
        grafo->NArestas--;
        IncideAresta = 1;
    }
    else
        TLista_Insere(&ListaAdj, grafo->Adj[u].ultimo, adj);
    while(TLista_Retira(&ListaAdj, ListaAdj.ultimo, &adj))
        TLista_Insere(&grafo->Adj[u], grafo->Adj[u].ultimo, adj);
return IncideAresta;
}
/*
TLista *TGrafo_ListaAdj(TGrafo *grafo, TVertice u){
    TLista *lista, ListaAdj;
    TItem adj;
    lista = (TLista*)malloc(sizeof(TLista));
    TLista_Inicia(lista);
    TLista_Inicia(&ListaAdj);
    while(TLista_Tamanho(&grafo->Adj[u]) > 0){
        TLista_Retira(&grafo->Adj[u], grafo->Adj[u].ultimo, &adj);
        TLista_Insere(&ListaAdj, ListaAdj.ultimo, adj);
    }
    while(TLista_Tamanho(&ListaAdj) > 0){
        TLista_Retira(&ListaAdj, ListaAdj.ultimo, &adj);
        TLista_Insere(&grafo->Adj[u], grafo->Adj[u].ultimo, adj);
        TLista_Insere(lista, lista->ultimo, adj);
    }
return lista;
}
*/
int TGrafo_NVertice(TGrafo *grafo){                             ///Retorna a quantidade de Vertices do grafo
return grafo->NVertices;
}
 
int TGrafo_NArestas(TGrafo *grafo){                             ///Retorna a quantidade de Arestas do grafo
return grafo->NArestas;
}
 
int dependentes(TGrafo *grafo, TVertice u, int num){            ///Imprime a quantidade de vertices que sao dependentes do vertive na posicao u
    printf("%d ", grafo->Adj[u].tamanho);
return 1;
}
 
int dependencia(TGrafo *grafo, TVertice u, int num){            ///Imprime quantos vertices depende do vertice na posicao u
    int i, cont = 0;
    TApontador p;
    TLista *lista = (TLista*)malloc(sizeof(TLista));
    TLista_Inicia(lista);
    for(i = 0; i < num; i++){
        lista = &grafo->Adj[i];
        p = lista->ultimo->prox->prox;
        if(lista->tamanho != 0) {
           while (p != lista->ultimo->prox) {
                if(p->item.Vertice == u) {
                    cont++;
                }
                p = p->prox;
            }
        }
    }
    printf("%d ", cont);
return 1;
}
 
int imprimeLista(TLista *lista){                                ///Imprime todos os vertices do qual o vertice na posicao u depende
    TApontador imprimi;
    imprimi = lista->ultimo->prox->prox;
    while(imprimi != lista->ultimo->prox){
        printf("%d ", imprimi->item.Vertice);
        imprimi = imprimi->prox;
    }
    printf("\n");
return 1;
}
 
/************************************************/
 
int main(){
    TGrafo grafo;
    int numVertice, numAresta, u, v;
    scanf("%d %d", &numVertice, &numAresta);                            ///Lê o numero de vertices e arestas a inserir
    if(numVertice < 1 || numVertice > 100)
        return 0;
    if(numAresta < 0 || numAresta > 10000)
        return 0;
    TGrafo_Inicia(&grafo, numVertice);
    int i;
    for(i = 1; i <= numAresta; i++){
        scanf("%d %d", &u, &v);                                         ///Lê o vertice e a aresta que irá criar
            if(! TGrafo_ExisteAresta(&grafo, v-1, u)){                  ///se jah existir aresta não ira inserir
                if(u != v)                                              ///O vertice não podera depender dele mesmo
                    TGrafo_InsereAresta(&grafo, u-1, v, 9);             ///Insere aresta
            }
    }
    for(i = 0; i < numVertice; i++){
        printf("%d ", i+1);
        dependencia(&grafo, i+1, numVertice);
        dependentes(&grafo, i, numVertice);
        imprimeLista(&grafo.Adj[i]);
    }
    return 0;
}

/*caso teste
4 3
1 2
1 3
4 2
*/