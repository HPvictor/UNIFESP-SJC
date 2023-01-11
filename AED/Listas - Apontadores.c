#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct celula *TApontador;                          ///Ponteiro de celula
 
typedef struct Item{                                        ///Estrutura tipo item guarda os nomes
    char nome[19];
}TItem;
 
typedef struct celula{                                      ///Estrutura tipo celula guarda os itens
    TItem item;
    TApontador prox;                                        //E cada celula tem um ponteiro para a proxima celula
}TCelula;
 
typedef struct lista{                                       ///Estrutura tipo lista guarda as celulas
    TApontador primeiro, ultimo;                            //Tem um ponteiro para a primeira celula e um outro para a ultima
    int tamanho;                                            //guarda o tamanho da lista
}TLista;
 
 
/************************************************/
 
 
// Implemente aqui o arquivo TADLista.h
 
 
void TLista_Inicia (TLista *lista);
int TLista_EhVazia(TLista *lista);
int TLista_Insere(TLista *lista, TApontador p, TItem x);
int TLista_Retira(TLista *lista, TApontador p, TItem *px);
TCelula* retornaRetira(TLista *lista, int p);
TCelula* retorna(TLista *lista, int p);
 
 
/************************************************/
 
 
// Implemente aqui o arquivo TADLista.c
 
void TLista_Inicia (TLista *lista){                         ///Funcao para iniciar a lista
    lista->tamanho = 0;                                     //Tamanho recebe zero
    lista->primeiro = NULL;                                 //ponteiro primeiro aponta para NULL
    lista->ultimo = lista->primeiro;                        //E ultimo também aponta para NULL
}
 
int TLista_EhVazia(TLista *lista){                          ///Verifica se a lista está vazia
    return(lista->primeiro == NULL && lista->ultimo == NULL);//Se os ponteiros primeiro e ultimo apontarem para NULL
}
 
 
TCelula* retornaRetira(TLista *lista, int p){               ///funçao retorna para retirar
    TApontador posicao;                                     //cria uma variavel posicao tipo apontador de celula
    posicao = lista->primeiro;                              //posição aponta para a primeira celula
    if(p == 0)                                              //Se p é igual a zero
        return lista->primeiro;                             //vai retornar um apontador para a primeira posição da celula
    if(p == lista->tamanho)                                 //Se p é igual ao tamanho da lista
        return lista->ultimo;                               //Vai retornar um apontador da ultima celula da lista
    int lugar=0;                                            //Se não for as condições anteriores cria uma variavel lugar tipo inteiro igual a zero
    if(p > lugar)                                           //Se p é maior que lugar
    while(lugar < p){                                       //Enquanto lugar é menor que p
        posicao = posicao->prox;                            //posição aponta para a proxima celula da lista
        lugar++;
    }
return posicao;                                             //Vai retornar um apontador da celula que vai ser retirada
}
 
 
TCelula* retorna(TLista *lista, int p){                     ///funçao retorna para inserir
    //printf("entrou no retorna\n");
    TApontador posicao;                                     //cria uma variavel posicao tipo apontador de celula
    posicao = lista->primeiro;                              //posição aponta para a primeira celula
    if(p > 0){                                              //Se p é maior que zero
        int lugar = 0;                                      //cria uma variavel lugar tipo inteiro igual a zero
        while(lugar < p){                                   //Enquanto lugar é menor que p
            posicao = posicao->prox;                        //posição aponta para a proxima celula da lista
            lugar++;
        }
    }
return posicao;                                             //Vai retornar um apontador para o local que a celula vai ser inserida
}                                                           //Se for inserir na ultima vai retornar NULL
 
 
int Insere_Comeco(TLista *lista, TItem x){                  ///Função para inserir no começo
    TCelula *novo = (TCelula*)malloc(sizeof(TCelula));      //Cria uma nova celula alocando espaço de memoria para ela
    novo->item = x;                                         //Nova celula recebe o item x
    if(TLista_EhVazia(lista)){                              //Se lista é vazia, vai inserir a primeira celula
        novo->prox = NULL;                                  //ponteiro da nova celula aponta para NULL
        lista->ultimo = novo;                               //apontador ultimo aponta para nova celula
    }
    else                                                    //Se não, vai inserir no começo da lista já com itens
        novo->prox = lista->primeiro;                       //ponteiro da nova celula aponta para a primeira celula que estava na lista
    lista->primeiro = novo;                                 //e o apontador primeiro vai apontar para a nova celula para ambas as condições
    return 1;                                               //Sai da função
}
 
int Insere_Fim(TLista *lista, TItem x){                     ///Função para inserir no fim
    //printf("entrou no inserir no fim\n");
    TCelula *novo = (TCelula*)malloc(sizeof(TCelula));      //Cria uma nova celula alocando espaço de memoria para ela
    novo->item = x;                                         //Nova celula recebe o item x
    novo->prox = NULL;                                      //ponteiro da nova celula aponta para NULL
    lista->ultimo->prox = novo;                             //Ponteiro da ultima posição vai apontar para a nova celula
    lista->ultimo = novo;                                   //ponteiro ultimo aponta para a nova celula
    return 1;                                               //Sai da função
}
 
 
int TLista_Insere(TLista *lista, TApontador p, TItem x){    ///Função geral de inserir
    lista->tamanho++;                                       //incrementa o tamanho
        if(p == lista->primeiro){                           //Se o apontador p estiver apontando para o mesmo local de primeiro
            //printf("entrou inserir no primeiro\n");
            Insere_Comeco(lista, x);                        //Chama a função inserir começo
            return 1;                                       //Sai da função
        }
        if(p == NULL){                                      //Se o apontador p estiver apontando para o mesmo local de ultimo
            //printf("entrou inserir no ultimo\n");
            Insere_Fim(lista, x);                           //Chama a função inserir ultimo
            return 1;                                       //Sai da função
        }
//    }
//printf("entrou no inserir qualquer\n");                   //se não for inserir no começo ou no fim, vai inserir no meio
    TApontador anterior;                                    //cria uma variavel anterior tipo apontador de celula
    anterior = lista->primeiro;                             //anterior aponta para o primeiro item
    while(anterior->prox != p)                              //enquanto a proxima celula do anterior não for igual a p
        anterior = anterior->prox;                          //anterior aponta para a proxima celula
    TCelula *novo = (TCelula*)malloc(sizeof(TCelula));      //Cria uma nova celula alocando espaço de memoria para ela
    novo->item = x;                                         //Nova celula recebe o item x
    novo->prox = p;                                         //apontador da nova celula aponta para onde o p aponta
    anterior->prox = novo;                                  //a celula que o anterior está apontando aponta agora para a nova celula
    return 1;                                               //sai da função
}
 
int Retira_Comeco(TLista *lista, TItem *px){                ///Função para retirar no começo
    //printf("entrou no retirar comeco\n");
    TApontador aux;                                         //cria uma variavel aux tipo apontador de celula
    aux = lista->primeiro;                                  //aux aponta para a primeira celula
    if(lista->tamanho > 1)                                  //Se a lista tem mais de uma celuala
        lista->primeiro = lista->primeiro->prox;            //o apontador primeiro aponta para a segunda celula
    else{                                                   //Se a lista tiver só uma celula
        lista->primeiro = NULL;                             //o apontador primeiro aponta para NULL e ultimo também
        lista->ultimo =NULL;
        }
    *px = aux->item;                                        //em ambas as condições, px recebe o item que está na celula que o aux esta apontando
    lista->tamanho--;                                       //Decrementa o tamanho
    free(aux);                                              //Libera o aux
    return 1;                                               //Sai da função
}
 
int Retira_Fim(TLista *lista, TItem *px){                   ///Função para retirar no fim
    //printf("entrou no retirar fim\n");
    TApontador aux, anterior;                               //cria uma variavel aux e uma anterior tipo apontador de celula
    anterior = lista->primeiro;                             //anterior aponta para a primeira celula
    if(lista->primeiro->prox != lista->ultimo){             //Se a proxima celula depois da primeira nao for a ultima
        while(anterior->prox != lista->ultimo)              //enquanto a proxima celula que o anterior aponta não for a ultima
            anterior = anterior->prox;                      //anterior aponta para a proxima celula
        }
    aux = lista->ultimo;                                    //aux vai apontar para a ultima
    anterior->prox = NULL;                                  //a anterior que é a penultima, sua celula aponta para NULL
    lista->ultimo = anterior;                               //apontador ultimo aponta para a anterior
    *px = aux->item;                                        //px recebe o item da celula que o aux aponta, antiga ultima
    lista->tamanho--;                                       //decrementa o tamanho da lista
    free(aux);                                              //Libera o aux
    return 1;                                               //Sai da função
}
 
int TLista_Retira(TLista *lista, TApontador p, TItem *px){  ///Função geral de retirar
    if(TLista_EhVazia(lista))                               //Se a lista esta vazia
        return 0;                                           //Sai da função
    if(p == lista->primeiro){                               //Se a celula que p aponta for igual a celula que primeiro aponta
            //printf("entrou no retirar comeco\n");
        Retira_Comeco(lista, px);                           //Vai retirar do começo
        return 1;                                           //Sai da função
    }
    if(p == lista->ultimo){                                 //Se a celula que p aponta for igual a celula que ultimo aponta
             //printf("entrou no retirar fim\n");
        Retira_Fim(lista, px);                              //Vai retirar do fim da lista
        return 1;                                           //Sai da função
    }
    //}
    //printf("entrou no retirar qualquer\n");               //Se não for nenhuma das condiçoes anteriores, vai retirar do meio
     TApontador aux, anterior;                              //cria uma variavel aux e uma anterior tipo apontador de celula
    anterior = lista->primeiro;                             //anterior aponta para a primeira celula
    while(anterior->prox != p){                             //enquanto a proxima celula que o anterior aponta não for a celula que p aponta
        anterior = anterior->prox;                          //anterior aponta para a proxima celula
 
        }                                                   //quando anterior prox for igual a p anterior vai apontar para a celula anterior da celula que vai ser retirada
    aux = p;                                                //aux vai apontar para a mesma celula que o p aponta
    anterior->prox = aux->prox;                             //a celula que o anterior aponta vai apontar para a proxima celula que o aux aponta
    *px = aux->item;                                        //px recebe o item que esta na celula que o aux aponta
    lista->tamanho--;                                       //decrementa o tamanho da lista
    free(aux);                                              //libera o aux
    return 1;                                               //Sai da função
}
 
/************************************************/
 
int main(void) {
 
    // Implemente aqui o programa principal
 
    TLista lista;                                          //Inicia a lista
    TLista_Inicia(&lista);
    TItem item, retirado;
    TApontador p;
    int n, k, i, cont=0;
    scanf("%d %d", &n, &k);                                 //lê as variaveis n numero de crianças e k numeros que a batata vai percorrer para eliminar uma criança
    if(n > 1000 || n < 1)                                   //n tem que ser menor que 1000 e maior que 0
        return 0;
    if(k > n || k < 1)                                      //k tem que ser menor que n e maior que 0
         return 0;
    for(i = 0; i < n; i++){                                //enquanto i for menor ou igual a n
        scanf("%s", item.nome);                             //lê o nome da criança e insere no final da lista
        p = retorna(&lista, i);                             //p recebe o apontador de celula que a função retornaInsere vai retornar
        TLista_Insere(&lista, p, item);                     //lê o nome da criança e insere na posisao na qual p está apontando na lista
    }
    while(lista.tamanho > 0){                               //enquanto a lista não for tamanho 0
        cont = (cont + k)  % lista.tamanho;                 //cont recebe o resto da divisão de cont mais k pelo tamanho da lista
        p = retornaRetira(&lista, cont);                    //p recebe o apontador da celula que tera o item a ser retirado
        TLista_Retira(&lista, p, &retirado);                //chama a função retirar e o retirado recebe o item desejado
        printf("%s \n", retirado.nome);                     //imprime na tela o nome da criança que saiu da brincadeira
    }
    return 0;                                               //encerra a brincadeira
}

/*caso teste
10 5
Sophia
Miguel
Julia
Arthur
Isabella
Davi
Alice
Gabriel
Manuela
Lucas
*/