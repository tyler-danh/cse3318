//Tyler Danh 1001706320
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

        while(i >= 0 && A[i] > key)
        {
            A[i+1] = A[i];
            i=i-1;
        }
        A[i + 1] = key;
    }
}

void Merge(int arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int A[], int left, int right)
{
    if(left < right)
    {
        int middle = (left+right)/2;
        MergeSort(A, left, middle);
        MergeSort(A, middle+1, right);
        Merge(A, left, middle, right);
    }
}

int ReadFileIntoArray(int argc, char *argv[], int **Array)
{
    FILE* io = fopen(argv[1], "r");
	if(io == NULL)
	{
		printf("File must be provided on command line... exiting\n");
		exit(1);
	}

    char num[10];
    int counter;
    int i = 0;

    while(fgets(num, sizeof(num), io) != NULL)
	{
		counter++;
	}
    *Array = malloc(counter * sizeof(int));

    fseek(io, 0, SEEK_SET);
    
    while(fgets(num, sizeof(num), io) != NULL)
    {
        (*Array)[i] = atoi(num);
        i++;
    }
	fclose(io);
    return counter;
}

void PrintArray(int ArrayToPrint[], int sizeAP)
{
    int i = 0;

    for(i = 0; i < sizeAP; i++)
    {
        printf("%d\n", ArrayToPrint[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int *BigArray = NULL;
    int elements = ReadFileIntoArray(argc, argv, &BigArray);
    clock_t start, end;

    #ifdef PRINTARRAY
        PrintArray(BigArray, elements);
    #endif
    start = clock();
    InsertionSort(BigArray, elements);
    end = clock();
    #ifdef PRINTARRAY
        PrintArray(BigArray, elements);
    #endif
    printf("%d records read\n", elements);
    printf("Insertion Sort = %ld tics\n", end-start);
}