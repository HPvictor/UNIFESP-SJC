#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxTam 51
 
typedef struct item{
    float valor;
}tipoItem;
 
 
typedef struct pilha {
    tipoItem item[MaxTam];
    int topo;
}TPilha;
 
 
/************************************************/
 
// Implemente aqui o arquivo TADPilha.h
 
 
TPilha* Inicia_Pilha();
int Pilha_Vazia(TPilha* p);
int Pilha_Cheia(TPilha* p);
void TPilha_Empilha(TPilha* p, float x);
int TPilha_Desempilha(TPilha* p, float *x);
int TPilha_Tamanho(TPilha* p);
 
 
 
/************************************************/
 
// Implemente aqui o arquivo TADPilha.c
 
 
 
TPilha* Inicia_Pilha(){                                // Inicia a pilha
    TPilha* p = (TPilha*) malloc(sizeof(TPilha));    // aloca um espaço de memoria do tamanho da struct TPilha
    p->topo = 0;                                    // topo igual a zero
return p;                                            // retorna um apontador de pilha
}
 
 
int Pilha_Vazia(TPilha* p){                            // verifica se a pilha está vazia
    if(p->topo == 0)                                
            return 0;                                // retorna zero se a pilha estiver vazia
    else
            return 1;                                
}
 
 
int Pilha_Cheia(TPilha* p){                            // verifica se a pilha está cheia
if(p->topo == MaxTam)
            return 0;
    else
            return 1;
 
}
 
 
void TPilha_Empilha(TPilha* p, float x){            // função para empilhar
 
        if(Pilha_Cheia(p) != 0){                    // verifica se a pilha está cheia, se não estiver
        p->topo++;                                    // incrementa-se o topo
        p->item[p->topo].valor = x;                    // e o topo recebe o elemento passado por referência
    }
    else
        printf("Pilha esta Cheia\n");                
}
 
 
int TPilha_Desempilha(TPilha* p, float *x){            // função para Desempilhar
    
    if(Pilha_Vazia(p) == 0 ){                        // verifica se a pilha está vazia
        printf("Pilha esta Vazia\n");    
    }
    else{                                            // se não estiver vazia
        tipoItem* aux;                                // declara um aux tipoItem
        aux->valor = p->item[p->topo].valor;        // valor do aux recebe o valor que está no topo
        p->topo--;                                    // topo é decrementado
        *x = aux->valor;                            // o apontador x recebe o valor do aux alterando diretamente na main
    }
return 1;
}
 
int TPilha_Tamanho(TPilha* p){                        // função para verificar o tamanho da pilha
    int tam;
    tam = p->topo;
return tam;
}
 
 
/************************************************/ 
 
 
 
int main(void) {
 
    TPilha* p = Inicia_Pilha();     //Inicia a pilha, com um ponteiro tipo pilha
    int i, num;
    float x1, x2, x3, R;
    char expressao[51];                //expressao a ser digitada, por exemplo abc+*
    
    scanf("%s", &expressao);         //lê a expressão
    
    num = strlen(expressao);        //num recebe a quantidade de elementos digitado na expressão
    
    for(i = 0; i<num; i++){            //laço para identificar cada elemento digitado
        switch(expressao[i]){
            
            case '+': TPilha_Desempilha(p, &x1); TPilha_Desempilha(p, &x2); R = x2+x1; TPilha_Empilha(p, R); break; // se for '+' desempilha os ultimos dois e somando-os empilha o resultado
            case '-': TPilha_Desempilha(p, &x1); TPilha_Desempilha(p, &x2); R = x2-x1; TPilha_Empilha(p, R); break; // se for '-' desempilha os ultimos dois e subtraindo-os empilha o resultado
            case '*': TPilha_Desempilha(p, &x1); TPilha_Desempilha(p, &x2); R = x2*x1; TPilha_Empilha(p, R); break; // se for '*' desempilha os ultimos dois e multiplicando-os empilha o resultado
            case '/': TPilha_Desempilha(p, &x1); TPilha_Desempilha(p, &x2); R = x2/x1; TPilha_Empilha(p, R); break; // se for '/' desempilha os ultimos dois e dividindo-os empilha o resultado
            default : 
                scanf("%f", &x3);    // se não for nenhum dos casos assima lê um numero tipo float e empilha no topo
                TPilha_Empilha(p, x3); 
            
        }
        
        
    }
    TPilha_Desempilha(p, &x3);        // desempilha o resultado final que está no topo
    printf("%f\n", x3);                // imprime o resultado na tela
    
return 0;
}

/* caso teste
ABC+*
2.000000
3.000000
4.000000
*/