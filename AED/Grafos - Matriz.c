#include <stdio.h>
#include <stdlib.h>
 
#define MAXVERTICES 100
 
typedef int TVertice;
 
typedef int TAresta;
 
typedef struct {
    int IncideAresta;
    TAresta Aresta;
}TAdjacencia;
 
typedef struct {
    TAdjacencia Adj[MAXVERTICES][MAXVERTICES];
    int NVertices;
    int NArestas;
}TGrafo;
 
/************************************************/
 
// Implemente aqui o arquivo TADGrafo.h
 
int TGrafo_Inicia(TGrafo *grafo, int numVertice);
int TGrafo_ExisteAresta(TGrafo *grafo, TVertice u, TVertice v);
int TGrafo_InsereAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta e);
int TGrafo_RetiraAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta *pE);
int TGrafo_NVertice(TGrafo *grafo);
int TGrafo_NArestas(TGrafo *grafo);
 
 
/************************************************/
 
// Implemente aqui o arquivo TADGrafo.c
 
 
int TGrafo_Inicia(TGrafo *grafo, int numVertice){               ///Inicia o Grafo
    grafo->NVertices = numVertice;
    grafo->NArestas = 0;
    int i, j;
    for(i = 1;i <= numVertice; i++){
        for(j = 1; j <= numVertice; j++){
            grafo->Adj[i][j].IncideAresta = 0;
        }
    }
    return 1;
}
 
int TGrafo_ExisteAresta(TGrafo *grafo, TVertice u, TVertice v){ ///Retorna se existe uma aresta na posição desejada
return (grafo->Adj[u][v].IncideAresta == 1);
}
 
int TGrafo_InsereAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta e){  ///Insere uma Aresta
    if(TGrafo_ExisteAresta(grafo, v, u))
        return 0;
    grafo->Adj[u][v].IncideAresta = 1;
    grafo->Adj[u][v].Aresta = e;
    grafo->NArestas++;
return 1;
}
 
int TGrafo_RetiraAresta(TGrafo *grafo, TVertice u, TVertice v, TAresta *pE){    ///Retira uma aresta
    grafo->Adj[u][v].IncideAresta = 0;
    *pE = grafo->Adj[u][v].Aresta;
    grafo->Adj[u][v].Aresta = 0;
    grafo->NArestas--;
return 1;
}
 
int TGrafo_NVertice(TGrafo *grafo){                             ///Retorna a quantidade de Vertices do grafo
return grafo->NVertices;
}
 
int TGrafo_NArestas(TGrafo *grafo){                             ///Retorna a quantidade de Arestas do grafo
return grafo->NArestas;
}
 
 
int dependentes(TGrafo *grafo, TVertice u, int num){
    int i, cont = 0;
    for(i = 1; i <= num; i++){
        if(TGrafo_ExisteAresta(grafo, u, i))
                cont++;
    }
return cont;
}
 
int dependencia(TGrafo *grafo, TVertice u, int num){
    int i, cont = 0;
    for(i = 1; i <= num; i++){
        if(TGrafo_ExisteAresta(grafo, i, u))
                cont++;
    }
return cont;
}
 
int imprimeDependt(TGrafo *grafo, TVertice u, int num){
    int i;
    for(i = 1; i <= num; i++){
        if(TGrafo_ExisteAresta(grafo, u, i))
            printf(" %d", i);
    }
return 1;
}
 
/************************************************/
 
int main(){
    TGrafo grafo;
    int numVertice, numAresta, u, v, dt, dc;
    scanf("%d %d", &numVertice, &numAresta);
    if(numVertice < 1 || numVertice > 100)
        return 0;
    if(numAresta < 0 || numAresta > 10000)
        return 0;
    TGrafo_Inicia(&grafo, numVertice);
    int i;
    for(i = 1; i <= numAresta; i++){
        scanf("%d %d", &u, &v);
        if(! TGrafo_ExisteAresta(&grafo, u, v)){
                TGrafo_InsereAresta(&grafo, u, v, 9);
        }
    }
    for(i = 1; i <= numVertice; i++){
        dt = dependentes(&grafo, i, numVertice);
        dc = dependencia(&grafo, i, numVertice);
    printf("%d %d %d", i, dc, dt);
    imprimeDependt(&grafo, i, numVertice);
    printf("\n");
    }
    return 0;
}

/*caso teste
4 3
1 2
1 3
4 2
*/