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
    #if QSM
        int middle = (high+low)/2;
        swap(&A[middle], &A[high]);
    #elif QSRND
        int random = (rand() % (high-low+1)) + low;
        swap(&A[random], &A[high]);
    #endif
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
    clock_t start, end;
    int elements, counter, i = 0;
    long sum = 0;

    if(argv[2] != NULL)
    {
        counter = atoi(argv[2]);
    }
    else
    {
        printf("Number of runs not specified on command line... defaulting to 10\n");
        counter = 10;
    }    
    elements = ReadFileIntoArray(argc, argv, &BigArray);
    for(i = 0; i < counter; i++)
    {
        elements = ReadFileIntoArray(argc, argv, &BigArray);
        #ifdef PRINTARRAY
            PrintArray(BigArray, elements);
        #endif
        start = clock();
        QuickSort(BigArray, 0, elements-1);
        end = clock();
        #ifdef PRINTARRAY
            PrintArray(BigArray, elements);
        #endif
        
        printf("Run %d complete: %ld tics\n", i+1, end-start);
        sum += (end-start);
        free(BigArray);
    }
    
    printf("Average run time for %d runs: %ld\n", counter, (long)(sum/counter));
    elements = ReadFileIntoArray(argc, argv, &BigArray);
    printf("%d records processed\n", elements);
    
}