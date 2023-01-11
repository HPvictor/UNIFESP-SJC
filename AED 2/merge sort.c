//Victor Hugo 150976
#include <stdio.h>
#include <stdlib.h>
 
struct Node
{
    int data;
    struct Node* next;
};
 
struct Node* juncao(struct Node* a, struct Node* b);
void parteFrente(struct Node* fonte, struct Node** frente, struct Node** atras);
void MergeSort(struct Node** headRef)
{
    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;
    if ((head == NULL) ||
        (head->next == NULL))
    {
        return;
    }
    parteFrente(head, &a, &b);
    MergeSort(&a);
    MergeSort(&b);
    *headRef = juncao(a, b);
}

struct Node* juncao(struct Node* a,struct Node* b)
{
    struct Node* result = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (a->data <= b->data)
    {
        result = a;
        result->next =
                juncao(a->next, b);
    }
    else
    {
        result = b;
        result->next = juncao(a, b->next);
    }
    return (result);
}

void parteFrente(struct Node* fonte,struct Node** frente,struct Node** atras)
{
    struct Node* rapido;
    struct Node* devagar;
    devagar = fonte;
    rapido = fonte->next;
    while (rapido != NULL)
    {
        rapido = rapido->next;
        if (rapido != NULL)
        {
            devagar = devagar->next;
            rapido = rapido->next;
        }
    }
 
    *frente = fonte;
    *atras = devagar->next;
    devagar->next = NULL;
}
 
void printList(struct Node* node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}
 
void push(struct Node** prim,int new_data)
{
    struct Node* novo =(struct Node*)malloc(sizeof(struct Node));
    novo->data = new_data;
    novo->next = (*prim);
    (*prim) = novo;
}
 
int main()
{
int n,num,i;
  scanf("%d",&n);
    struct Node* res = NULL;
    struct Node* a = NULL;
  for(i=0;i<n;i++){
    scanf("%d",&num);
    push(&a, num);
  }
    MergeSort(&a);
    printList(a); 
    getchar();
    return 0;
}
//Victor Hugo 150976