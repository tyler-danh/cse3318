#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void InsertionSort(int A[], int n)
{
    int i, key, j = 0;

    for(j = 1; j < n; j++)
    {
        key = A[j];
        i=j-1;
        printf("j = %d, key = %d\n", j, key);

        while(i >= 0 && A[i] > key)
        {
            A[i+1] = A[i];
            i=i-1;
        }
        A[i + 1] = key;
        printf("i = %d\n", i);
    }
}

void PrintArray(int ArrayToPrint[], int sizeAP)
{
    int i = 0;

    for(i = 0; i < sizeAP; i++)
    {
        printf("%d,", ArrayToPrint[i]);
    }
    printf("\n");
}

int main(void)
{
    int Array[8] = {32,9,13,11,56,1,2,0};
    int n = 8;

    PrintArray(Array, n);
    InsertionSort(Array, n);
    PrintArray(Array, n);
}