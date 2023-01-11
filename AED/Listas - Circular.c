#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct celula *TApontador;
 
typedef struct {
    char nome;
}TItem;
 
typedef struct celula {
    TItem item;
    TApontador prox;
}TCelula;
 
typedef struct {
    TApontador ultimo;
    int tamanho;
}TLista;
 
 
/************************************************/
 
// Implemente aqui o arquivo TADLista.h
 
 
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
    lista->ultimo = cabeca;
    lista->tamanho = 0;
}
 
int TLista_EhVazia(TLista *lista){
    return(lista->ultimo->prox == lista->ultimo);
}
 
int TLista_Insere(TLista *lista, TApontador p, TItem x){
    TCelula *novo = (TCelula*)malloc(sizeof(TCelula));
    novo->item = x;
    lista->tamanho++;
    if(TLista_EhVazia(lista)){                      ///Inserir com lista vazia
        novo->prox = lista->ultimo->prox;
        lista->ultimo->prox->prox = novo;
        lista->ultimo = novo;
        return 1;
    }
    if(p == lista->ultimo->prox){                              ///Inserir na primeira posicao
        novo->prox = lista->ultimo->prox->prox;
        lista->ultimo->prox->prox = novo;
        return 1;
    }
    if(p == lista->ultimo){                              ///Inserir na ultima posicao
        novo->prox = lista->ultimo->prox;
        lista->ultimo->prox = novo;
        lista->ultimo = novo;
        return 1;
    }                                                   ///Inserir no meio da lista
    novo->prox = p->prox;
    p->prox = novo;
    return 1;
}
 
int TLista_Retira(TLista *lista, TApontador p, TItem *px){
    if(lista->tamanho == 0){                           ///retorna zero se a lista está vazia
        return 0;}
    p = p->prox;
    TApontador anterior, aux;
    anterior = lista->ultimo->prox->prox;
    aux = p;
    if(lista->tamanho == 1){                            ///Retira quando só tem uma celula
        lista->ultimo->prox->prox = lista->ultimo->prox;
        *px = aux->item;
        lista->tamanho--;
        free(aux);
        return 1;
    }
    if(p == anterior){                                  ///Retira a primeira celula
        lista->ultimo->prox->prox = lista->ultimo->prox->prox->prox;
        *px = aux->item;
        lista->tamanho--;
        free(aux);
        return 1;
    }
    if(p == lista->ultimo){                             ///Retira a ultima celula
        while(anterior->prox != p)
            anterior = anterior->prox;
        anterior->prox = anterior->prox->prox;
        lista->ultimo = anterior;
        *px = aux->item;
        lista->tamanho--;
        free(aux);
        return 1;
    }
    while(anterior->prox != p)                          ///Retira do meio da lista
        anterior = anterior->prox;
    anterior->prox = anterior->prox->prox;
    *px = aux->item;
    lista->tamanho--;
    free(aux);
    return 0;
}
 
TCelula* Retorna(TLista *lista, int p){                     ///funçao retorna para inserir
    TApontador posicao;                                     //cria uma variavel posicao tipo apontador de celula
    posicao = lista->ultimo->prox;                          //posição aponta para a primeira celula
    if(p > 0){                                              //Se p é maior que zero
        int lugar = 0;                                      //cria uma variavel lugar tipo inteiro igual a zero
        while(lugar < p){                                   //Enquanto lugar é menor que p
            posicao = posicao->prox;                        //posição aponta para a proxima celula da lista
            lugar++;
        }
    }
return posicao;                                             //Vai retornar um apontador para o local que a celula vai ser inserida
}                                                           //Se for inserir na ultima vai retornar NULL
int operacao(TLista *lista){
    TItem inserido, retirado;
    TApontador p, anterior;
    p = Retorna(lista, 0);
    int i, num;
    char frase[49999];
 
    scanf("%[^\n]s", frase);
 
    num = strlen(frase);
 
    for(i = 0; i < num; i++){
        if(frase[i] == '[')
            p = Retorna(lista, 0);
 
        else
        {   if(frase[i] == ']')
                p = Retorna(lista, lista->tamanho);
 
            else
            {   if(frase[i] == '>'){
                    if(p != lista->ultimo)
                        p = p->prox;
                }
                else
                {
                    if(frase[i] == '<'){
                        if(p != lista->ultimo->prox){
                            anterior = lista->ultimo->prox;
                            while(anterior->prox != p)
                                anterior = anterior->prox;
                            p = anterior;
                        }
                    }
                    else
                    {
                        if(frase[i] == '-'){
                            if(p != lista->ultimo->prox){
                                anterior = lista->ultimo->prox;
                                while(anterior->prox != p)
                                    anterior = anterior->prox;
                                p = anterior;
                                TLista_Retira(lista, p, &retirado);
                            }
                        }
                        else
                        {
                            inserido.nome = frase[i];
                            TLista_Insere(lista, p, inserido);
                            p = p->prox;
                        }
                    }
                }
            }
        }
    }
 
    p = Retorna(lista, 1);
    while(p != lista->ultimo->prox){
        printf("%c", p->item.nome);
        p = p->prox;
    }
    printf("\n");
return 1;
}
 
 
/************************************************/
 
 
int main()
{
    TLista lista;
    TLista_Inicia(&lista);
    operacao(&lista);
    return 0;
}

/*caso teste
Le<-mbra-te do futuro e o fut--uro se[ -lembr-][a-ra de] -ti.
*/