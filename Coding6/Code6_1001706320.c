// Coding Assignment 6 - Tyler Danh - 1001706320

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 10
 
/* Node for storing information */
typedef struct cursedenergyuser
{
    char *name;
    float height;
    char gender;
    int age;
    char *grade;
    char *jujutsu;
    char *domain;
    struct cursedenergyuser *next_ptr;
}
CursedEnergyUser;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
	
	for (int i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(CursedEnergyUser *NewNode, CursedEnergyUser *SorcererIndex[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (SorcererIndex[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		SorcererIndex[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		CursedEnergyUser *TempPtr = SorcererIndex[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(CursedEnergyUser *SorcererIndex[])
{
	CursedEnergyUser *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = SorcererIndex[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				free(TempPtr->grade);
				free(TempPtr->jujutsu);
				free(TempPtr->domain);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(CursedEnergyUser *SorcererIndex[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the sorcerer to delete from the Sorcerer Index ");
	fgets(LookupName, sizeof(LookupName), stdin);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	CursedEnergyUser *TempPtr = SorcererIndex[HashIndex];
	CursedEnergyUser *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nSorcerer %s does not exist in the Sorcerer Index\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == SorcererIndex[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					SorcererIndex[HashIndex] = TempPtr->next_ptr;
					printf("\nSorcerer %s has been deleted from the Sorcerer Index\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nSorcerer %s has been deleted from the Sorcerer Index\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nSorcerer %s does not exist in the Sorcerer Index\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(CursedEnergyUser *SorcererIndex[])
{
	int i;
	CursedEnergyUser *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = SorcererIndex[i];

		printf("\nSorcererIndex[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(CursedEnergyUser *SorcererIndex[])
{
	int i;
	CursedEnergyUser *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = SorcererIndex[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(CursedEnergyUser *SorcererIndex[])
{
	CursedEnergyUser *TempPtr = NULL;
	char height[10] = {};
	char meters[10] = {};
	char centimeters[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter sorcerer's name ");
	fgets(LookupName, sizeof(LookupName), stdin);
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = SorcererIndex[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
					
					printf("Height\t\t");
					sprintf(height, "%.2f", TempPtr->height);
					for (int i = 0; i < strlen(height); i++)
					{
						if (height[i] == '.')
						{
							printf("\' ");
						}
						else
						{
							printf("%c", height[i]);
						}
					}
					printf("\"\n");
					if (TempPtr->gender == 'M')
						printf("Gender\t\tMale\n");
					else if(TempPtr->gender == 'F')
						printf("Gender\t\tFemale\n");
					printf("Age\t%d\n", TempPtr->age);
					printf("Grade\t%s\n", TempPtr->grade);
					printf("Techniques\t%s\n", TempPtr->jujutsu);
					printf("Domain Name\t%s\n", TempPtr->domain);

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nSorcerer %s not found in Sorcerer Index\n\n", LookupName);
}

void AddNewSorcerer(CursedEnergyUser *SorcererIndex[])
{
	int HashIndex = 0;
	CursedEnergyUser *NewNode;
	char TempBuffer[150] = {};

	NewNode = malloc(sizeof(CursedEnergyUser));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new sorcerer's name ");
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's height as meters.centimeters ", NewNode->name);
	scanf("%f", &(NewNode->height));
	
	printf("\n\nEnter %s's possible gender (M/F/B/U) ", NewNode->name);
	scanf(" %c", &(NewNode->gender));
	NewNode->gender = toupper(NewNode->gender);
	
	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);

	printf("\n\nEnter %s's age ", NewNode->name);
	scanf("%d", &(NewNode->age));
	
	printf("\n\nEnter %s's grade ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin); 
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->grade = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->grade, TempBuffer);

	printf("\n\nEnter %s's techniques ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	TempBuffer[strlen(TempBuffer)-1] = '\0';	
	NewNode->jujutsu = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->jujutsu, TempBuffer);

	printf("\n\nEnter %s's domain name (enter none if they do not have one) ", NewNode->name);
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
	TempBuffer[strlen(TempBuffer)-1] = '\0';
	NewNode->domain = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->domain, TempBuffer);

	AddNode(NewNode, SorcererIndex);
}

int ReadFileIntoHashTable(int argc, char *argv[], CursedEnergyUser *SorcererIndex[])
{
	FILE *FH = NULL;
	char FileLine[150] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	CursedEnergyUser *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");
			FileLine[strcspn(FileLine, "\n")] = '\0';

			
			NewNode = malloc(sizeof(CursedEnergyUser));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->height = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->gender = *token;

			token = strtok(NULL, "|");
			NewNode->age = atoi(token);

			token = strtok(NULL, "|");
			NewNode->grade = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->grade, token);
			
			token = strtok(NULL, "|");
			NewNode->jujutsu = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->jujutsu, token);

			token = strtok(NULL, "|");
			NewNode->domain = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->domain, token);

			AddNode(NewNode, SorcererIndex);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	CursedEnergyUser *SorcererIndex[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, SorcererIndex);
 
	do
	{
		printf("\n\nSorcerer Index Menu\n\n"
			   "1. Show all sorcerers in Sorcerer Index for a given letter\n"
			   "2. Look up sorcerer by name\n"
			   "3. How many sorcerers are in the Sorcerer Index?\n"
			   "4. Display the Sorcerer Index\n"
			   "5. Add a new sorcerer\n"
			   "6. Delete a sorcerer from the Sorcerer Index\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(SorcererIndex);
				break;
			case SHOWBYNAME:
				ShowByName(SorcererIndex);
				break;
			case COUNT:
				printf("Your Sorcerer Index contains %d sorcerers\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(SorcererIndex);
				break;
			case ADD:
				AddNewSorcerer(SorcererIndex);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(SorcererIndex))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(SorcererIndex);

	return 0;
}			  
