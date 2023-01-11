#include <stdio.h>
#include <stdlib.h>
//código remocao de arvore rubro negra
//crio as structs q seram utilizadas
typedef int ArvKey;
typedef struct {
    ArvKey valor;
} TItem;
typedef struct SNo *TArvBin;
typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
    int cor;
} TNo;
//funcao para identificar a cor(vermelho ou preto)
int EhPreto(TArvBin No) {
    return (No == NULL) || (No->cor == 0);
}
int EhVermelho(TArvBin No) {
    return (No != NULL) && (No->cor == 1);
}
//funcao para encontrar altura, tanto para Esquerda quanto pra Direita, rubro e negra
int Height(TArvBin No) {
    int l, r;
    if (No == NULL)
        return 0;
    l = Height(No->Esq);
    r = Height(No->Dir);
    if (l > r)
        return l + 1;
    else
        return r + 1;
}
int HeightLeft(TArvBin No) {
  return Height(No->Esq);
}
int HeightRight(TArvBin No) {
  return Height(No->Dir);
}
int HeightNegra(TArvBin No) {
    int hEsq, hDir;
    if (No == NULL)
        return 0;
    hEsq = HeightNegra(No->Esq);
    hDir = HeightNegra(No->Dir);
    if (hEsq > hDir)
        return hEsq + EhPreto(No);
    else
        return hDir + EhPreto(No);
}
int HeightRubro(TArvBin No) {
    int hEsq, hDir;
    if (No == NULL)
        return 0;
    hEsq = HeightRubro(No->Esq);
    hDir = HeightRubro(No->Dir);
    if (hEsq > hDir)
        return hEsq + EhVermelho(No);
    else
        return hDir + EhVermelho(No);
}
//funcao da arvore rubro negra
int ArvoreARN(TArvBin No) {
    if (No == NULL)
        return 1;
    if (!ArvoreARN(No->Esq))
        return 0;
    if (!ArvoreARN(No->Dir))
        return 0;
    if (EhVermelho(No) && (!EhPreto(No->Esq) || !EhPreto(No->Dir)))
        return 0;
    if (HeightNegra(No->Esq) != HeightNegra(No->Dir))
        return 0;
    return 1;
}
//funcoes de balanceamento(mudar cor,rotacionar)
void ChangeColor(TArvBin No) {
    if (No != NULL) No->cor = !No->cor;
}
void SwitchColor(TArvBin No) {
    ChangeColor(No);
    ChangeColor(No->Esq);
    ChangeColor(No->Dir);
}
void RoteateRight(TArvBin *pA) {
    TArvBin pB;
    pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;
    *pA = pB;
}
void RotateLeft(TArvBin *pA) {
    TArvBin pB;
    pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;
    *pA = pB;
}
void BalanceLeft(TArvBin *pA, TArvBin *pB, TArvBin *pC) {
    if (EhVermelho((*pC)->Dir))
        SwitchColor(*pC);
    else {
        if (*pB == (*pA)->Dir)
            RotateLeft(pA);
        ChangeColor(*pA);
        ChangeColor(*pC);
        RoteateRight(pC);
    }
}
int BalanceLeftRemove(TArvBin *pC) {
    TArvBin pD = (*pC)->Esq;
    if (EhVermelho(pD)) {
        RoteateRight(pC);
        pC = &(*pC)->Dir;
        pD = (*pC)->Esq;
    }
    if (pD != NULL) {
        if (EhPreto(pD->Esq) && EhPreto(pD->Dir)) {
            ChangeColor(pD);
            if (EhVermelho(*pC)) {
                ChangeColor(*pC);
                return 0;
            }
        } else {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;
            if (EhPreto(pD->Esq))
                RotateLeft(&(*pC)->Esq);
            else
                ChangeColor(pD->Esq);
            RoteateRight(pC);
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}
void BalanceRight(TArvBin *pA, TArvBin *pB, TArvBin *pC) {
    if (EhVermelho((*pC)->Esq))
        SwitchColor(*pC);
    else {
        if (*pB == (*pA)->Esq)
            RoteateRight(pA);
        ChangeColor(*pA);
        ChangeColor(*pC);
        RotateLeft(pC);
    }
}
int BalanceRightRemove(TArvBin *pC) {
    TArvBin pD = (*pC)->Dir;
    if (EhVermelho(pD)) {
        RotateLeft(pC);
        pC = &(*pC)->Esq;
        pD = (*pC)->Dir;
    }
    if (pD != NULL) {
        if (EhPreto(pD->Esq) && EhPreto(pD->Dir)) {
            ChangeColor(pD);
            if (EhVermelho(*pC)) {
                ChangeColor(*pC);
                return 0;
            }
        } else {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;
            if (EhPreto(pD->Dir))
                RoteateRight(&(*pC)->Dir);
            else
                ChangeColor(pD->Dir);
            RotateLeft(pC);
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}
void BalanceNode(TArvBin *pA, TArvBin *pB, TArvBin *pC) {
    if ((pC != NULL) && EhVermelho(*pA) && EhVermelho(*pB)) {
        if (*pA == (*pC)->Esq)
            BalanceLeft(pA, pB, pC);
        else
            BalanceRight(pA, pB, pC);
    }
}
//funcao insercao recursiva
void RecursiveInsert(TArvBin *pA, TArvBin *pC, TItem x) {
    if (*pA == NULL) {
        *pA = (TArvBin) malloc(sizeof(TNo));
        (*pA)->Item = x;
        (*pA)->Esq = NULL;
        (*pA)->Dir = NULL;
        (*pA)->cor = 1;
    } else if (x.valor < (*pA)->Item.valor) {
        RecursiveInsert(&(*pA)->Esq, pA, x);
        BalanceNode(pA, &(*pA)->Esq, pC);
    } else if (x.valor > (*pA)->Item.valor) {
        RecursiveInsert(&(*pA)->Dir, pA, x);
        BalanceNode(pA, &(*pA)->Dir, pC);
    }
}
int Parent(TArvBin *q, TArvBin *r) {
    int bh;
    if ((*r)->Dir != NULL) {
        if (Parent(q, &(*r)->Dir))
            return BalanceLeftRemove(r);
        return 0;
    } else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Esq;
        bh = EhPreto(*q) && EhPreto(*r);
        if (!bh && EhPreto(*q))
            (*r)->cor = 0;
        return bh;
    }
}
int Sucessor(TArvBin *q, TArvBin *r) {
    int bh; 
    if ((*r)->Esq != NULL) {
        if (Sucessor(q, &(*r)->Esq))
            return BalanceRightRemove(r);
        return 0;
    } else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
        bh = EhPreto(*q) && EhPreto(*r);
        if (!bh && EhPreto(*q))
            (*r)->cor = 0;
        return bh;
    }
}
//funcao Remocao recursiva
int RecursiveRemove(TArvBin *p, ArvKey x) {
    TArvBin q;
    int bh;
    if (*p == NULL)
        return 0;
    else if (x < (*p)->Item.valor) {
        if (RecursiveRemove(&(*p)->Esq, x))
            return BalanceRightRemove(p);
        return 0;
    } else if (x > (*p)->Item.valor) {
        if (RecursiveRemove(&(*p)->Dir, x))
            return BalanceLeftRemove(p);
        return 0;
    } else {
        q = *p;
        if (q->Esq == NULL) {
            *p = q->Dir;
            bh = EhPreto(*p) && EhPreto(q);
            if (!bh && EhPreto(q))
                (*p)->cor = 0;
        } else if (q->Dir == NULL) {
            *p = q->Esq;
            bh = EhPreto(*p) && EhPreto(q);
            if (!bh && EhPreto(q))
                (*p)->cor = 0;
        } else {
            if (Sucessor(&q, &q->Dir))
                bh = BalanceLeftRemove(p);
            else bh = 0;
        }
        free(q);
        return bh;
    }
}
void Remove(TArvBin *pRaiz, ArvKey x) {
    RecursiveRemove(pRaiz, x);
    if (*pRaiz != NULL)
        (*pRaiz)->cor = 0;
}
//funcoes base da arvore
TArvBin SetupTree() {
    return NULL;
}
TArvBin Search(TArvBin No, ArvKey x) {
    if (No == NULL)
        return NULL;
    else if (x < No->Item.valor)
        return Search(No->Esq, x);
    else if (x > No->Item.valor)
        return Search(No->Dir, x);
    return No;
}
void Insert(TArvBin *pRaiz, TItem x) {
    RecursiveInsert(pRaiz, NULL, x);
    (*pRaiz)->cor = 0;
} 
void DoInserts(TArvBin *pNo, TItem *nopraremover) {
    int i, n, removeno;
    TItem x; 
    scanf("%d", &x.valor);
    while (x.valor >= 0) {
        Insert(pNo, x);
        scanf("%d", &x.valor);
    }
 
}
void FreeNode(TArvBin *pNo) {
    TArvBin No;
    No = *pNo;
    if (No != NULL) {
        FreeNode(&No->Esq);
        FreeNode(&No->Dir);
        free(No);
        (*pNo) = NULL;
    }
}
void PrintTree(TArvBin No) {
    if (No != NULL) {
        if (EhPreto(No))
            printf("(N%d", No->Item.valor);
        else
            printf("(R%d", No->Item.valor);
        PrintTree(No->Esq);
        PrintTree(No->Dir);
        printf(")");
    }
    else
        printf("()");
}
//fim da TAD
//Funcao MAIN
int main() {
    TArvBin Raiz;
    TItem x;
    Raiz = SetupTree();
    DoInserts(&Raiz, &x);
    if (ArvoreARN(Raiz)) {
      printf("%d, %d, %d\n", Height(Raiz)-1, HeightLeft(Raiz), HeightRight(Raiz));
    }
    scanf("%d", &x.valor);
    while(x.valor >= 0) {
        TArvBin no = Search(Raiz, x.valor);
        if (no == NULL){
            Insert(&Raiz, x);
        } else {
            printf("%d, %d, %d\n", Height(no)-1, HeightLeft(no), HeightRight(no));
            Remove(&Raiz, x.valor);
        }
        scanf("%d", &x.valor);
    }
    scanf("%d", &x.valor);
    TArvBin no = Search(Raiz, x.valor);
    if( no == NULL) {
        printf("Valor nao encontrado\n");
    } else {
        printf("%d\n", HeightRubro(no));
    }
    FreeNode(&Raiz);
    return 0;
}