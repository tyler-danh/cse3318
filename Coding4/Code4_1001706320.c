//Tyler Danh 1001706320
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int ReadFileIntoArray();
void PrintArray();
void QuickSort();
int Partition();
void swap();

void QuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int ndx = Partition(A, low, high);
        QuickSort(A, low, ndx - 1);
        QuickSort(A, ndx + 1, high);
    }
}

int Partition(int A[], int low, int high)
{
    int i, j = 0;
    int pivot = A[high];
    i = (low - 1);
    for (j = low; j < high; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return (i + 1);
}

void swap(int *SwapA, int *SwapB)
{
    int temp = *SwapA;
    *SwapA = *SwapB;
    *SwapB = temp;
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
    int counter = 0;
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
    QuickSort(BigArray, 0, elements-1);
    end = clock();
    #ifdef PRINTARRAY
        PrintArray(BigArray, elements);
    #endif
    printf("%d records read\n", elements);
    printf("Quick Sort = %ld tics\n\n", end-start);

    free(BigArray);
}