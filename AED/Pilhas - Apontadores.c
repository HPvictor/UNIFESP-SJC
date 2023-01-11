#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct scelula *Tapontador;
 
typedef struct scelula {
    float conteudo;
    Tapontador prox;
}TCelula;
 
 
typedef struct pilha {
    Tapontador topo;
    int tamanho;
}TPilha;
 
 
/************************************************/
 
// Implemente aqui o arquivo TADPilha.h
 
void Inicia_Pilha(TPilha* pilha);
int TPilha_EhVazia (TPilha* pilha);
void TPilha_Empilha(TPilha* pilha, float x);
float TPilha_Desempilha(TPilha* pilha);
int TPilha_Tamanho(TPilha pilha);
 
 
/************************************************/
 
// Implemente aqui o arquivo TADPilha.c
 
 
 
void Inicia_Pilha(TPilha* pilha) {                          // Função para Iniciar a pilha
    pilha->topo = NULL;                                     // Ponteiro tipo celula topo aponta para NULL
    pilha->tamanho = 0;                                     // tamanho recebe zero
 
}
 
 
int TPilha_EhVazia (TPilha* pilha) {                        // Verifica se a pilha est vazia
 
    if(pilha->topo == NULL)                                 // retorna zero se o topo aponta para NULL
        return 0;
    else
        return 1;
}
 
void TPilha_Empilha(TPilha* pilha, float x) {               // Função Empilha
 
    TCelula* novo = (TCelula*) malloc(sizeof(TCelula));     // Cria uma variavel tipo celula e Aloca espaço na memoria tamanho celula
    if(TPilha_EhVazia(pilha) == 0){                         // Se a pilha está vazia
 
        novo->conteudo = x;                                 // a variavel tipo celula recebe em seu contudo o x passado por referencia
        novo->prox = NULL;                                  // e o prox dessa variavel aponta para NULL
        pilha->topo = novo;                                 // o topo aponta para essa nova struct
        pilha->tamanho++;                                   // e incrementa o tamanho
    }
    else{
 
        novo->conteudo = x;                                 // se não está vazia, a variavel tipo celula recebe em seu contudo o x passado por referencia
        novo->prox = pilha->topo;                           // o prox da variavel aponta para a struct celula do topo
        pilha->topo = novo;                                 // e o topo aponta para a nova struct
        pilha->tamanho++;                                   // e incrementa o tamanho
    }
}
 
 
float TPilha_Desempilha(TPilha* pilha){                     // funçao Desempilha
 float x;
    if(TPilha_EhVazia(pilha) == 0){                         // primeiro verifica se a pilha está vazia
        printf("Pilha Vazia\n");
    }
    else{                                                   // se nao
 
        TCelula* aux;                                       // cria um apontador tipo celula aux
        aux = pilha->topo;                                  // aux recebe o que esta no topo
        pilha->topo = pilha->topo->prox;                    // o topo aponta para o topo que aponta para o prox
        x = aux->conteudo;                                  // x recebe o conteudo do aux
        pilha->tamanho--;                                   // decrementa o tamanho
        free(aux);                                          // libera o aux
    }
return x;
}
 
 
int TPilha_Tamanho(TPilha pilha){                           // Retorna o tamanho da pilha
    int tam;
    tam = pilha.tamanho;                                    // tam recebe a quantidade do tamanho da pilha
    return tam;                                             // que eh retornada
}
 
 
/************************************************/
 
 
 
int main(void) {
 
    TPilha p;
    Inicia_Pilha(&p);     //Inicia a pilha, passando o endereço de p como referencia
    int i, num;
    float x1, x2, x3, R;
    char expressao[51];                //expressao a ser digitada, por exemplo abc+*
 
    scanf("%s", &expressao);         //lê a expressão
 
    num = strlen(expressao);        //num recebe a quantidade de elementos digitado na expressão
 
    for(i = 0; i<num; i++){            //laço para identificar cada elemento digitado
        switch(expressao[i]){
 
            case '+': x1 = p.topo->conteudo; TPilha_Desempilha(&p); x2 = p.topo->conteudo; TPilha_Desempilha(&p); R = x2+x1; TPilha_Empilha(&p, R); break; // se for '+' desempilha os ultimos dois e somando-os empilha o resultado
            case '-': x1 = p.topo->conteudo; TPilha_Desempilha(&p); x2 = p.topo->conteudo; TPilha_Desempilha(&p); R = x2-x1; TPilha_Empilha(&p, R); break; // se for '-' desempilha os ultimos dois e subtraindo-os empilha o resultado
            case '*': x1 = p.topo->conteudo; TPilha_Desempilha(&p); x2 = p.topo->conteudo; TPilha_Desempilha(&p); R = x2*x1; TPilha_Empilha(&p, R); break; // se for '*' desempilha os ultimos dois e multiplicando-os empilha o resultado
            case '/': x1 = p.topo->conteudo; TPilha_Desempilha(&p); x2 = p.topo->conteudo; TPilha_Desempilha(&p); R = x2/x1; TPilha_Empilha(&p, R); break; // se for '/' desempilha os ultimos dois e dividindo-os empilha o resultado
            default :
                scanf("%f", &x3);    // se não for nenhum dos casos acima lê um numero tipo float e empilha no topo
                TPilha_Empilha(&p, x3);
 
        }
 
 
    }
    x3 = TPilha_Desempilha(&p);    // desempilha o resultado final que está no topo
    printf("%f\n", x3);                // imprime o resultado na tela
 
return 0;
}

/*caso teste
ABC+*
2.000000
3.000000
4.000000
*/