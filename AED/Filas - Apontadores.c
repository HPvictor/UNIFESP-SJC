#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct celula *Apontadorcelula;
 
typedef struct conteudo{                        //estrutura para guardar as informações
    int indice;            
    int forca;
    int Pi;
}TItem;
 
typedef struct celula{                            //célula com informações e um apontador para próxima célula se existir
    TItem info;
    Apontadorcelula prox;
}Tcelula;
 
typedef struct {                                //estrutura fila com um apontador para o primeiro item e um para o último
    Apontadorcelula frente, tras;
    int tamanho;
}TFila;
 
 
/************************************************/
 
// Implemente aqui o arquivo TADFila.h
 
void TFila_Inicia(TFila *fila);
int TFila_EhVazia(TFila *fila);
int TFila_Tamanho(TFila *fila);
int TFila_Enfileira(TFila *fila, TItem x);
int TFila_Desenfileira(TFila *fila, TItem *px);
 
void vencedor(TFila *fila, int k, int n, int x); 
 
/************************************************/
 
// Implemente aqui o arquivo TADFila.c 
 
 
void TFila_Inicia(TFila *fila){                    //iniciar a fila com os apontadores apontando para NULL e tamanho 0
    fila->frente = NULL;
    fila->tras = NULL;
    fila->tamanho = 0;
}
 
int TFila_EhVazia(TFila *fila){                    //retorna se a fila está vazia
    return(fila->frente == NULL);
}
 
int TFila_Tamanho(TFila *fila){                    //retorna o tamanho da fila
     return(fila->tamanho); 
}
 
int TFila_Enfileira(TFila *fila, TItem x){                        //função para enfileirar
    Tcelula* novo = (Apontadorcelula) malloc(sizeof(Tcelula));    //aloca um espaço de memória do tamanho de uma celula
    novo->info = x;                                                //as informações dessa nova celula recebe x passado por referencia
    novo->prox = NULL;                                            //o apontador da nova celula aponta para NULL
    if(TFila_EhVazia(fila)){                                    //se a fila é vazia
        fila->frente = novo;                                    //os apontadores frente e tras da fila aponta para a nova celula
        fila->tras = novo;                                        
        fila->tamanho++;                                        //incrementa o tamanho da fila
        }
    else{                                                        //se não for vazia
        fila->tras->prox = novo;                                //o apontador da última celula da fila vai apontar para a nova celula
        fila->tras = novo;                                        //e o apontador de tras da fila também vai apontar para a nova célula
        fila->tamanho++;                                        //incrementa o tamanho
    }
return 1;
}
 
int TFila_Desenfileira(TFila *fila, TItem *px){                    //função para desenfileirar
    Apontadorcelula aux;                                        //cria-se um aux tipo apontador  de célula
    
    if(TFila_EhVazia(fila))                                        //se a fila for vazia retorna 0
    return 0;
    
    aux = fila->frente;                                            //se não, aux vai apontar para o mesmo lugar que o apontador da frente da fila
    fila->frente = fila->frente->prox;                            //o apontador da frente vai apontar para o proximo elemento da fila
    *px = aux->info;                                            //px que é o endereço da variavel passada por referencia vai receber a informação de onde o aux está apontando no seu conteúdo
    free(aux);                                                    //libera o aux
    fila->tamanho--;                                            //decrementa o tamanho
return 1;
} 
 
void exibe(TFila *fila){                                           //função para imprimir todos os itens da fila
  Apontadorcelula celula;       
  int i;       
   celula = fila->frente;       
 
  for(i=0;i<fila->tamanho;++i){       
    printf("%d %d %d\n", celula->info.indice, celula->info.forca, celula->info.Pi);       
    celula = celula->prox;       
  }       
}
 
void vencedor(TFila *fila, int k, int n, int x){                //função para saber quem será o vencedor
    TItem c1, c2, c3;                                            //cria-se 3 variaveis tipo item(onde está as informações                            
    while( TFila_Tamanho(fila) != 1){                            //enquanto o tamanho da fila for diferente de 1 vai fazer: 
    //exibe(fila);
    //printf("\n");
        TFila_Desenfileira(fila, &c1);                            //c1 recebe o item que está na primeira posição da fila
        TFila_Desenfileira(fila, &c2);                            //c2 recebe o item que está na segunda posição da fila
        
        if(c1.forca >= c2.forca){                                //se a força de c1 for maior ou igual a força de c2
                c3 = c1;                                        //c3 recebe as informações de c1
                c3.forca = c1.forca - c2.forca;                    //a força de c3 recebe a força de c1 menos a de c2
        }
        else{
                c3 = c2;                                        //se não, c3 recebe as informações de c2
                c3.forca = c2.forca - c1.forca;                    //a força de c3 recebe a força de c2 menos a de c1
        }
        if(c3.forca + k > c3.Pi)                                //se a força de c3 + a força recuperada for maior que a força inicial
            c3.forca = c3.Pi;                                    //a força de c3 recebe a força inicial
        else        
            c3.forca = c3.forca + k;                            //se não, a força de c3 recebe + a força de recuperação        
    TFila_Enfileira(fila, c3);                                    //enfileira c3 no final da fila que corresponde ao ganhador da chave disputada
    }
        
TFila_Desenfileira(fila, &c1);                                    //concluida todadas as rodadas, tendo o tamanho igual a 1, desenfileira o único item restante 
printf("%d\n", c1.indice);                                        //e imprime o numero correspondente ao competidor
}
 
 
/************************************************/
 
 
 
int main()
{
     TFila fila;                                                    //cria-se uma variavel tipo fila
     TFila_Inicia(&fila);                                        //inicia-se essa fila
     TItem item;                                                    //cria-se uma variavel tipo item(informações)
     int n, x, k, i, f;                                            
     scanf("%d %d", &n, &k);                                        //lê-se n e k
     if(n > 15 || n < 1)                                            //se 0 < n < 16 ok, se não retorna 0
         return 0;
     x = pow(2,n);                                                // x recebe 2^n 
     if(k > 1000 || k < 0)                                        //se -1 < k < 1001 ok, se não retorna 0
         return 0;
     
     for(i=1; i<=x; i++){                                        //laço"for" para ler a força inicial de cada competidor
         item.indice = i;                                        //cada lutador recebe seu numero correspondente
         scanf("%d", &f);                                        //lê-se a força do respectivo competidor
         if(f > 1000 || f < 1)                                    //se 0 < f < 1001 ok, se não retorna 0
             return 0;
         item.forca = f;                                            //força do momento e força inicial recebe f
         item.Pi = f;
         TFila_Enfileira(&fila, item);                            //enfileira o item correspondente ao competidor com suas informações
     }
 
vencedor(&fila, k, n, x);                                        //calcula quem será o vencedor
 
    return 0;
}

/*caso teste
2 10
50
50
60
60
*/