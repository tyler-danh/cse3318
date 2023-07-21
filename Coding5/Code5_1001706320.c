#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

void CreateAdjacencyMatrix(int AdjMatrix[][MAX])
{
	int start = 0, end = 0;
	int i = 0, j = 0;
	char buffer[100] = {};
	FILE *FH = fopen("EdgeList.txt", "r+");
	if (FH == NULL)
		exit(0);
	/* initialize adjacency matrix to -1 */
	for(i = 0; i < MAX; i++)
		for(j = 0; j < MAX; j++)
			AdjMatrix[i][j] = -1;
	while (fgets(buffer, sizeof(buffer)-1, FH))
	{
		sscanf(buffer, "%d %d", &start, &end); //this will need fixing when slides come out
		AdjMatrix[start][end] = 1;
		//figure out how to read the entire line, these are for ints, we will be using strtok()
	}
	fclose(FH);
}

int main(int argc, char *argv[])
{
	int AdjMatrix[MAX][MAX]; //maybe this wont be an array of int?
}