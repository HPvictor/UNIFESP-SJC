#include <stdio.h>
#include <stdlib.h>
#define MAXTAM 1001
#define INICIO 0
 
 
typedef struct SNo *TArvore;                        ///TArvore eh um apontador tipo Nó
 
typedef TArvore TItem;                              ///TItem tbm eh um apontador de Nó
 
typedef struct {                                    ///estrutura para a informação do nó
    int info;
} TDados;
 
typedef struct lista{                                          //Estrutura tipo Lista
    int primeiro, ultimo;                                       //apontadores indices que guardão o primeiro e ultimo item da lista
    TItem item[MAXTAM];                                         //vetor que guardará os itens na fila
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
 
 
void TLista_Inicia (TLista *lista);
int TLista_EhVazia(TLista *lista);
int TLista_EhCheia(TLista *lista);
int TLista_Insere(TLista *lista, int p, TItem x);
int TLista_Retira(TLista *lista, int p, TItem *px);
int TLista_Tamanho(TLista* lista);
int TLista_Retorna(TLista *lista, int p);
 
 
/************************************************/
 
 
// Implemente aqui o arquivo TADArvore.c
 
 
 
void TLista_Inicia (TLista *lista){                             ///Função inicia lista
    lista->primeiro = INICIO;                                   //Apontador primeiro aponta para zero
    lista->ultimo = lista->primeiro;                            //Apontador ultimo aponta para o primeiro, ambos são zero
}
 
int TLista_EhVazia(TLista *lista){                              ///Retorna se a lista está vazia
    return(TLista_Tamanho(lista) == 0);                         //se o tamanho é igual a zero
}
 
int TLista_EhCheia(TLista *lista){                              ///Retorna se a lista está cheia
    return (lista->ultimo == MAXTAM);                           //Se o apontador ultimo é igual ao tamanho maximo
}
 
int TLista_Insere(TLista *lista, int p, TItem x){               ///Função para Inserir
    if(TLista_EhCheia(lista))                                   //Verifica se a lista está cheia
        return 0;                                               //Se sim retorna zero e sai da função
    if((TLista_Tamanho(lista) == 0) && p == 1){                 //Se o tamanho é igual a zero e o indice p for igual a 1
        lista->primeiro++;                                      //primeiro recebe 1
        lista->ultimo++;                                        //ultimo recebe 1
        lista->item[lista->primeiro] = x;                       //adiciona x ao primeiro item
        return 1;                                               // Sai da função
    }
    if(p == 1){                                                 //Se o indice p é igual a 1 somente
        int l = lista->ultimo;                                  // l recebe o indice ultimo
        while(l >= 0){                                          //enquanto l for maior ou igual a zero
            lista->item[l+1] = lista->item[l];                  //item na posição l mais um recebe o item que está na posição l
            l--;                                                //decrementa o l
        }
        lista->item[lista->primeiro] = x;                       //o primeiro item da lista na posição 1 recebe o item x
        lista->ultimo++;                                        //ultimo recebe o proximo indice
        return 1;                                               //Sai da função
    }
    if(p == TLista_Tamanho(lista) + 1){                         //Se p é maior que o tamanho da lista, vai inserir no proximo depois do ultimo
        lista->item[lista->ultimo + 1] = x;                     //O proximo indice depois do ultimo recebe o item x
        lista->ultimo++;                                        //ultimo aponta para esse proximo indice
        return 1;                                               //Sai da função
    }
    int posicao;                                                //Se não for nenhuma das alternativas anteriores, vai inserir no meio
    posicao = lista->ultimo;                                    //Cria um variavel posição que recebe o indice da ultima posição
    while(posicao >= p){                                        //Enquanto posição é maior ou igual a p
        lista->item[posicao + 1] = lista->item[posicao];        //O item da proxima posição recebe o item da posição apontada
        posicao--;                                              //decrementa a posição para passar o proximo item para frente até chegar na posição desejada a inserir
    }
    lista->item[p] = x;                                         //posição que eu quero inserir recebe o item x
    lista->ultimo++;                                            //ultimo aponta para o proximo item
    return 1;                                                   //sai da função
}
 
int TLista_Retira(TLista *lista, int p, TItem *px){             ///Função para retirar
    if(TLista_EhVazia(lista))                                   //verifica se a lista esta vazia
        return 0;                                               //se sim sai da função
    if(p == lista->primeiro && p == lista->ultimo){             //Se o apontador primeiro for igual ao ultimo, retira quando só tem um item na lista
        *px = lista->item[p];                                   //px passado como apontador do endereço do px da main recebe como conteudo o item na posição p(igual a 1)
        lista->primeiro--;                                      //ultimo e primeiro apontam para 0, fazendo a lista ser vazia
        lista->ultimo--;
        return 1;                                               //Sai da função
    }
    if(p == lista->primeiro){                                   //Se a lista não tem só um item e quero retirar da primeira posição
        *px = lista->item[p];                                   //px recebe o item da primeira posição
        int posicao;                                            //cria um variavel posição
        posicao = lista->primeiro;                              //posição recebe o indice da primeira posição
        while(posicao < lista->ultimo){                         //enquanto a posição for menor que o ultimo
            lista->item[posicao] = lista->item[posicao + 1];    //item da posição recebe o proximo item
            posicao++;                                          //incrementa a posição até todas as posições se deslocarem para esquerda
        }
        lista->ultimo--;                                        //ultimo aponta para o penultimo elemento
        return 1;                                               //Sai da função
    }
    if(p == lista->ultimo){                                     //se quero remover o ultimo elemento
        *px = lista->item[p];                                   //px recebe o ultimo item
        lista->ultimo--;                                        //ultimo aponta para o penultimo
        return 1;                                               //sai da função
    }
    *px = lista->item[p];                                       //se não for nenhuma das condições anteriores, vai retirar do meio
    int posicao;                                                //px vai receber o item da posição desejada
    posicao = p;                                                //cria uma variavel posição para guardar o indice do locar que retirei o item
    while(posicao < lista->ultimo){                             //enquanto a posição é menor que o ultimo elemento
        lista->item[posicao] = lista->item[posicao + 1];        //item da posição recebe o proximo elemento da lista
        posicao++;                                              //incrementa a posição até todos os itens da direita doitem retirado se deslocarem para esquerda
    }
    lista->ultimo--;                                            //ultimo aponta para o penultimo
    return 1;                                                   //sai da função
}
 
int TLista_Tamanho(TLista* lista){                              ///função para retornar o tamanho
    int tam;
    tam = lista->ultimo;                                        //tam recebe o indice do ultimo elemento da lista
return tam;                                                     //retorna assim o tamanho
}
 
int TLista_Retorna(TLista *lista, int p){                       ///retorna o indice para retirar
    int maisUm = 1;
    while(p+1 != maisUm){                                       //retorna sempre o p + 1
        maisUm++;
    }
return maisUm;
}
 
 
///==============================TAD ARVORE==================================
 
 
void TArvore_Inicia(TArvore arvore, TDados x){                          ///Inicia um nó recebendo as informacoes e iniciando a lista de filhos dele
    arvore->dados = x;
    TLista_Inicia(&arvore->filhos);
}
 
int TArvore_EhExterno(TArvore arvore){                                  ///verifica se o nó eh uma folha
    return (TLista_Tamanho(&arvore->filhos) == 0);
}
 
int TArvore_NDescendentes(TArvore arvore){                              ///verifica o numero de descendentes do nó
    return (TLista_Tamanho(&arvore->filhos));
}
 
int TArvore_Insere(TArvore arvore, TArvore subArv){                     ///insere o nó 'subarv' como filho do no avore
    int p = TLista_Retorna(&arvore->filhos, TLista_Tamanho(&arvore->filhos));
    TLista_Insere(&arvore->filhos, p, subArv);
    return 1;
}
 
 
int Imprime(TArvore arvore, TArvore raiz){                              ///imprime a arvore como parenteses alinhados
    TArvore aux;
    aux = arvore;
    int i = 0;
    if(arvore == raiz)
        printf("(%d", arvore->dados.info);
    if(TLista_Tamanho(&arvore->filhos) == 0)
        return 0;
    while(aux->filhos.primeiro + i != aux->filhos.ultimo + 1){
        printf("(%d", aux->filhos.item[aux->filhos.primeiro + i]->dados.info);
        if(! TLista_Tamanho(&arvore->filhos.item[aux->filhos.primeiro + i]->filhos) == 0)
            Imprime(aux->filhos.item[aux->filhos.primeiro + i], arvore);
        i++;
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

/*caso teste
4 3
1 2
1 3
2 4
*/