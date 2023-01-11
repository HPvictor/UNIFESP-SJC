#include <stdio.h>
#include <stdlib.h>

#define MIN 2
#define MAX 4 

struct No{
    int num[MAX+1];
    int cont;
    struct No *p[MAX+1];
};
struct No *raiz;
//incia arvore
struct No *iniciaArvB(int valor, struct No *filho){
    struct No *novo;
    novo = (struct No *)malloc(sizeof(struct No));       
    novo->num[1] = valor;
    novo->cont = 1;
    novo->p[0] = raiz;
    novo->p[1] = filho;
    return novo;
}
//funcao insere folha
void insereFolha(int valor, int pos, struct No *no, struct No *filho){
    int i;
    i = no->cont;
    while (i > pos){
        no->num[i + 1] = no->num[i];
        no->p[i + 1] = no->p[i];
        i--;
    }
    no->num[i + 1] = valor;
    no->p[i + 1] = filho;
    no->cont++;
}
//funcao para dividir um no e alocalo em uma nova posicao
void divideNo(int num, int *pValor, int pos, struct No *no, struct No *filho, struct No **novo){
    int med, i;
    if (pos > MIN){
        med = MIN + 1;
    } else{
        med = MIN;
    }
    *novo = (struct No *)malloc(sizeof(struct No));      
    i = med + 1;
    while (i <= MAX){
        (*novo)->num[i - med] = no->num[i];
        (*novo)->p[i - med] = no->p[i];
        i++;
    }
    no->cont = med;
    (*novo)->cont = MAX - med;
    if (pos <= MIN){
        insereFolha(num, pos, no, filho);
    } else{
        insereFolha(num, (pos - med), *novo, filho);
    }
    *pValor = no->num[no->cont];
    (*novo)->p[0] = no->p[no->cont];
    no->cont--;
}
//funcao valor do no
int valorNo(int num, int *pValor, struct No *no, struct No **filho){
    int pos;
    if (!no){
        *pValor = num;
        *filho = NULL;
        return 1;
    }
    if (num < no->num[1]){
        pos = 0;
    } else{
        for (pos = no->cont; ((num < no->num[pos]) && (pos > 1)); pos--){
            if (num == no->num[pos]){
                return 0;      
            }
        }
    }
    if (valorNo(num, pValor, no->p[pos], filho)){
        if (no->cont < MAX){
            insereFolha(*pValor, pos, no, *filho);
        } else{
            divideNo(*pValor, pValor, pos, no, *filho, filho);
            return 1;
        }
    }
    return 0;
}
//funcao insere numero
void inserirNum(int valor){
    int aux, i;
    struct No *filho;
    aux = valorNo(valor, &i, raiz, &filho);      
    if (aux){
        raiz = iniciaArvB(i, filho);      
    }
}
//funcao pesquisar
int pesquisar(int valor, int *pos, struct No *no) {
    if (!no){
        return -1;
    }
    if (valor < no->num[1]) {
        *pos = 0;
    } else{
        for (*pos = no->cont; (valor < no->num[*pos] && *pos > 1); (*pos)--); 
        if (valor == no->num[*pos]) {
        return no->cont;     
        }
    }
    pesquisar(valor, pos, no->p[*pos]);
    return;      
}
//inicio funcao main
int main(){
    int num, aux=0, pesquisa, numpesquisar;
    while (aux == 0){
        scanf("%d", &num);      
        if (num > 0){
            inserirNum(num);
        } else{
            aux = 1;
        }
    }
    scanf("%d", &numpesquisar);
    pesquisa = pesquisar(numpesquisar, &aux, raiz);
    printf("%d\n", raiz->cont);
    if (pesquisa != -1){
        printf("%d\n", pesquisa);
    } else{
        printf("Valor nao encontrado");
    }        
    return 0;
}