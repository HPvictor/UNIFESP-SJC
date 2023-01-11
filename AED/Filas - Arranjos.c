#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MaxTam 32769
 
 
 
typedef struct {
    int indice;
    int forca;
    int Pi;
}TItem;
 
typedef struct {
    int frente, tras;
    TItem item[MaxTam];
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
 
 
void TFila_Inicia(TFila *fila){                                        //inicia a fila
    fila->frente = 0;                                                //indice da frente recebe 0
    fila->tras = fila->frente;                                        //indice de tras recebe o mesmo indice da frente
}
 
int TFila_EhVazia(TFila *fila){                                        //retorna se a fila está vazia ( se frente e tras forem iguais
    return(fila->frente == fila->tras);
}
 
int TFila_Tamanho(TFila *fila){                                        //retorna o tamanho da fila
     return((fila->tras >= fila->frente) ?                            //se indice tras for maior ou igual a frente
            (fila->tras - fila->frente) :                            //retorna o indice de tras menos o da frente
            (MaxTam + fila->tras - fila->frente));                     //se não, retorna o (tamanho máximo mais tras) menos frente 
}
 
int TFila_Enfileira(TFila *fila, TItem x){                            //função para enfileirar
    if(fila->frente == (fila->tras + 1) % MaxTam)                    //se fila frente for igual ao resto da divisão de tras + 1 pelo tamanho máximo, a fila está cheia
        return 0;                                                    //retorna zero
    
    fila->item[fila->tras] = x;                                        //se a fila ainda tem espaço o item na posição do indice de tras recebe as informações de x
    fila->tras = (fila->tras +1) % MaxTam;                            //tras recebe o resto da divisão de tras +1 pelo tamanho máximo
    
return 1;
}
 
int TFila_Desenfileira(TFila *fila, TItem *px){                        //função para desinfileirar
    if(TFila_EhVazia(fila))                                            //se a fila está vazia retorna zero
    return 0;
    
    *px = fila->item[fila->frente];                                    //se não, o conteudo de px passado por referencia como ponteiro recebe as informações do item que esta na posição da frente
    fila->frente = (fila->frente + 1) % MaxTam;                        //frente recebe o resto da divisão da frente + 1 pelo tamanho máximo
    
return 1;
} 
 
void exibe(TFila *fila, int x){                                           //função para imprimir todos os itens da fila
  int l;
  for(l = 0; l < x; l++){
        printf("%d %d %d\n", fila->item[fila->frente + l].indice, fila->item[fila->frente + l].forca, fila->item[fila->frente + l].Pi);
    }
    printf("\n");     
  }       
 
 
void vencedor(TFila *fila, int k, int n, int x){                //função para saber quem será o vencedor
    TItem c1, c2, c3;                                            //cria-se 3 variaveis tipo item(onde está as informações                            
    while( TFila_Tamanho(fila) != 1){                            //enquanto o tamanho da fila for diferente de 1 vai fazer: 
    //exibe(fila, x);
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