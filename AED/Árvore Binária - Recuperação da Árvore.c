#include <stdio.h>
#include <stdlib.h>
 
 
typedef struct {                                        ///Estrutura tipo Item
    int info;
}TItem;
 
typedef struct SNo *TArvbin;                            ///TArvbin eh um apontador do tipo TNo
 
typedef struct SNo {                                    ///Estrutura tipo TNo
    TItem item;
    TArvbin esq, dir;
} TNo;
 
 
/************************************************/
 
// Implemente aqui o arquivo TADArvBin.h
 
 
 
TArvbin TArvbin_Inicia();
TArvbin TArvbin_CriaNo(TItem x, TArvbin esq, TArvbin dir);
int TArvbin_EhExterno(TArvbin No);
TArvbin TArvbin_SubarvoreEsquerda(TArvbin No);
TArvbin TArvbin_SubarvoreDireita(TArvbin No);
void TArvbin_Libera(TArvbin No);
int TArvbin_Vazia(TArvbin No);
void TArvbin_PercorrePosOrdem(TArvbin raiz);
TArvbin TArvbin_Constroi(int Preord[], int Emord[], int esqueda, int direita, int *no);
 
 
 
/*************************==========TAD ARVORE BINARIA=========***********************/
 
// Implemente aqui o arquivo TADArvBin.c
 
 
TArvbin TArvbin_Inicia(){                                       ///cria um apontador tipo no para NULL
    return NULL;
}
 
TArvbin TArvbin_CriaNo(TItem x, TArvbin esq, TArvbin dir){      /// Cria no alocando memoria para um TNo e apontando para o filho da esqueda e o da direita
    TArvbin no = TArvbin_Inicia();
    no = (TArvbin)malloc(sizeof(TNo));
    no->item = x;
    no->dir = dir;
    no->esq = esq;
    return no;                                                  // retorna o no criado
}
 
int TArvbin_EhExterno(TArvbin No){                              ///verifica se eh uma folha
    return(No->dir == NULL && No->esq == NULL);
}
 
TArvbin TArvbin_SubarvoreEsquerda(TArvbin No){                  ///retorna um apontador para o filho da esquerda
    return(No->esq);
}
 
TArvbin TArvbin_SubarvoreDireita(TArvbin No){                   ///retorna um apontador para o filho da direita
    return(No->dir);
}
 
void TArvbin_Libera(TArvbin No){                                ///libera da memoria o no e seus filhos
    if(No == NULL)
        return;
    TArvbin_Libera(TArvbin_SubarvoreEsquerda(No));
    TArvbin_Libera(TArvbin_SubarvoreDireita(No));
    free(No);
    No = NULL;
}
 
 
int TArvbin_Vazia(TArvbin No){                                  ///Verifica se a arvor eh vazia
    return No == NULL;
}
 
 
void TArvbin_PercorrePosOrdem(TArvbin raiz){                    ///percorre a arvore em sentido posOrdem e imprime cada no
    if(!TArvbin_Vazia(raiz)){
        TArvbin_PercorrePosOrdem(TArvbin_SubarvoreEsquerda(raiz));
        TArvbin_PercorrePosOrdem(TArvbin_SubarvoreDireita(raiz));
        printf("%d\n", raiz->item.info);
    }
}
 
TArvbin TArvbin_Constroi(int Preord[], int Emord[], int esqueda, int direita, int *no){ ///Constroi a arvore recursivamente de baixo pra cima
 
    if(esqueda <= direita){
        TArvbin RaizMomento, NoEsq, NoDir;
        TItem item;
        int raiz, i;
        i = 0;
        while( Preord[*no] != Emord[i])
            i++;
        (*no)++;
        item.info = Emord[i];
        raiz = i;
        NoEsq = TArvbin_Constroi(Preord, Emord, esqueda, raiz-1, no);
        NoDir = TArvbin_Constroi(Preord, Emord, raiz+1, direita, no);
        RaizMomento = TArvbin_CriaNo(item, NoEsq, NoDir);
        return RaizMomento;
    }
    else
        return NULL;
}
 
 
/*************************===========Programa Principal=========***********************/
 
int main()
{
    int N, i, indice = 0;
    scanf("%d", &N);                        ///quantidade de nos
    while(N < 0 || N > 1000)
        scanf("%d", &N);
    TArvbin raiz = TArvbin_Inicia();
    int Preordem[N];
    int Emordem[N];
 
    for(i = 0; i < N; i++){
        scanf("%d", &Preordem[i]);          ///sequencia PreOrdem
    }
    for(i = 0; i < N; i++){
        scanf("%d", &Emordem[i]);           ///sequencia EmOrdem
    }
 
    raiz = TArvbin_Constroi(Preordem, Emordem, 0, N-1, &indice); ///construir a arvore
    TArvbin_PercorrePosOrdem(raiz);         ///Percorrer a arvore e imprimir os nos
 
    return 0;
}

/*caso teste
7
4 2 1 3 5 7 6
1 2 3 4 5 6 7
*/