#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX 6

typedef struct
{
	char label[6];
	int distance;
	int previous;
	int visited;
}
Vertex;

void addVertex(char *argv[], Vertex *VertexArray[], int *VertexCount)
{
	char label;
	char *Token = NULL;
	char Buffer[100] = {};
	FILE *IO = fopen(argv[1], "r+");
	Vertex *NewVertex = malloc(sizeof(Vertex));
	if(IO == NULL)
		exit(0);
	for(int i = 0; i < MAX; i++)
	{
		fgets(Buffer, sizeof(Buffer), IO);
		Token = strtok(Buffer, ",");
		strcpy(NewVertex->label, Token);
		NewVertex->visited = 0;
		VertexArray[(*VertexCount)++] = NewVertex;
	}
	fclose(IO);
}


void CreateAdjacencyMatrix(char *argv[], int AdjMatrix[][MAX])
{
	int start = 0, end = 0;
	int i = 0, j = 0;
	char buffer[100] = {};
	FILE *FH = fopen(argv[1], "r+");
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
		//this is a dumpster fire, figure out how to make adjacency matrix
	}
	fclose(FH);
}

void Dijkstra(int StartVertex, Vertex *VertexArray)
{

}

int main(int argc, char *argv[])
{
	int AdjMatrix[MAX][MAX];
	int VertexCount = 0;
	Vertex *VertexArray[MAX];

	addVertex(argv, VertexArray, &VertexCount);
}