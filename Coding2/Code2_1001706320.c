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

    char num[10] = NULL;
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
        (*Array)[i] = num;
        i++;
    }
	fclose(io);
}

void PrintArray(int ArrayToPrint[], int sizeAP)
{
    int i = 0;

    for(i = 0; i < sizeAP; i++)
    {
        printf("%d", ArrayToPrint[i]);
    }
}

int main(int argc, char *argv[])
{
    int *BigArray = NULL;
    int elements = ReadFileIntoArray(argc, argv, BigArray);
    clock_t start, end;

    #ifdef PRINTARRAY
        PrintArray(BigArray, elements);
    #endif
}