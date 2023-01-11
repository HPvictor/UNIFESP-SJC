#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTAM 1000
#define INICIO 0
 
 
typedef struct Item{                                           //Estrutura tipo Item
    char nome[19];                                             //Guardará os nomes
}TItem;
 
typedef struct lista{                                          //Estrutura tipo Lista
    int primeiro, ultimo;                                       //apontadores indices que guardão o primeiro e ultimo item da lista
    TItem item[MAXTAM];                                         //vetor que guardará os itens na fila
}TLista;
 
 
/************************************************/
 
 
// Implemente aqui o arquivo TADLista.h
 
 
void TLista_Inicia (TLista *lista);
int TLista_EhVazia(TLista *lista);
int TLista_EhCheia(TLista *lista);
int TLista_Insere(TLista *lista, int p, TItem x);
int TLista_Retira(TLista *lista, int p, TItem *px);
int TLista_Tamanho(TLista* lista);
int TLista_Retorna(TLista *lista, int p);
 
 
/************************************************/
 
 
// Implemente aqui o arquivo TADLista.c
 
 
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
 
/************************************************/
 
int main(void) {
 
    // Implemente aqui o programa principal
 
     TLista lista;                                               //Inicia a lista
    TLista_Inicia(&lista);
    TItem item, retirado;
    int p;
    int n, k, i, cont=0;
    scanf("%d %d", &n, &k);                                     //lê as variaveis n numero de crianças e k numeros que a batata vai percorrer para eliminar uma criança
    if(n > 1000 || n < 1)                                       //n tem que ser menor que 1000 e maior que 0
        return 0;
    if(k > n || k < 1)                                          //k tem que ser menor que n e maior que 0
         return 0;
    for(i = 1; i <= n; i++){                                    //enquanto i for menor ou igual a n
        scanf("%s", item.nome);                                 //lê o nome da criança e insere no final da lista
        TLista_Insere(&lista, i, item);
    }
    while(TLista_Tamanho(&lista) > 0){                          //enquanto a lista não for tamanho 0
        cont = (cont + k)  % TLista_Tamanho(&lista);            //cont recebe o resto da divisão de cont mais k pelo tamanho da lista
        p = TLista_Retorna(&lista, cont);                       //p recebe o indice que tera o item a ser retirado
        TLista_Retira(&lista, p, &retirado);                    //chama a função retirar e o retirado recebe o item desejado
        printf("%s \n", retirado.nome);                         //imprime na tela o nome da criança que saiu da brincadeira
    }
    return 0;                                                   //encerra a brincadeira
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