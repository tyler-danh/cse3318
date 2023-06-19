/* Coding Assignment 1 */
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
	NODE *newNode = malloc(sizeof(NODE));
	newNode->number = Number;
	newNode->next_ptr = NULL;
	NODE *temp = *LinkedListHead;

	if(temp == NULL)
		*LinkedListHead = newNode;
	else
	{
		while(temp->next_ptr != NULL)
		{
			temp = temp->next_ptr;
		}
		temp->next_ptr = newNode;
	}
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
	FILE* io = fopen(argv[1], "r");
	if(io == NULL)
	{
		printf("File Failed to Open Exiting...");
		exit(1);
	}
	char num[10];
	int Num = 0;
	int counter = 0;
	int sum = 0;

	while(fgets(num, sizeof(num), io) != NULL)
	{
		Num = atoi(num);
		AddNodeToLL(Num, LLH);
		counter++;
		sum += Num;
	}
	fclose(io);
	printf("%d records were read for a total sum of %d", counter, sum);
}

void PrintLL(NODE *LLH) 
{
	NODE *temp = LLH;
	while(temp != NULL)
	{
		printf("%p, %d, %p\n", temp, temp->number, temp->next_ptr);
		temp = temp->next_ptr;
	}
}

void FreeLL(NODE **LLH) 
{ 
	NODE *temp = *LLH;
	NODE *nextNode;
	int counter = 0;
	int num = 0;

	while(temp != NULL)
	{
		num += temp->number;
		nextNode = temp->next_ptr;
		#ifdef PRINT
			printf("Freeing %p %d %p\n", temp, temp->number, temp->next_ptr);
		#endif
		free(temp);
		temp = nextNode;
		
		counter++;
	}
	printf("%d nodes were deleted for a total sum of %d", counter, num);
}

int main(int argc, char *argv[]) 
{ 
	

	NODE *LLH = NULL;
	long int start = 0;
	long int end = 0;
	
	/* capture the clock in a start time */
	start = clock();

	ReadFileIntoLL(argc, argv, &LLH);

	/* capture the clock in an end time */
	end = clock();
	printf("\n%ld tics to write the file into the linked list\n", end-start);

	#ifdef PRINT
		/* capture the clock in a start time */
		start = clock();

		PrintLL(LLH);

		/* capture the clock in an end time */
		end = clock();
	
		printf("\n%ld tics to print the linked list\n", end-start);
	#endif

	/* capture the clock in a start time */
	start = clock();

	FreeLL(&LLH);

	/* capture the clock in an end time */
	end = clock();
	printf("\n%ld tics to free the linked list\n", end-start);
	
	return 0; 
} 
