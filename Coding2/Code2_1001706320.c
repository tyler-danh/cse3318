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

int ReadFileIntoArray(int argc, char *argv[], int **Array)
{
    FILE* io = fopen(argv[1], "r");
	if(io == NULL)
	{
		printf("File must be provided on command line... exiting");
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
    //int TestArray[10] = {16, 1, 10, 4, 8, 9, 3, 12, 11, 0};
    int elements = ReadFileIntoArray(argc, argv, &BigArray);
    clock_t start, end;

    //PrintArray(TestArray, 10);
    //InsertionSort(TestArray, 10);
    //PrintArray(TestArray, 10);

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