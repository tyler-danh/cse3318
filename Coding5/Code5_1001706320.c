#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReadFileIntoArray(int argc, char *argv[], int **Array)
{
    FILE* io = fopen(argv[1], "r");
	if(io == NULL)
	{
		printf("File must be provided on command line... exiting\n");
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	
}