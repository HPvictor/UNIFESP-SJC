#include <stdio.h>

void quicksort(int list[], int low, int high, int k)
{
    int temp;
    if (low < high)
    {
        if(low<high)
            temp=partition(list,low,high);            
            if(temp==k)
              return;
        if(k<temp)
              quicksort(list, low, temp-1,k);
            else
              quicksort(list, temp+1,high,k );
    }
}

int main()
{
    int list[50];
    int size, i, num;
    scanf("%d", &num);
    scanf("%d", &size);
    for (i = 0; i < size; i++)
    {
        scanf("%d", &list[i]);
    }
    quicksort(list, 0, size - 1, num);
    printf("%d",num);
    printf("o menor elemento eh o %d\n",list[num-1]);
    for (i = 0; i < size; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");
    return 0;
}
