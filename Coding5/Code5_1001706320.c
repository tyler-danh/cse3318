#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX 50

typedef struct
{
	char label[6];
	int distance;
	int previous;
	int visited;
}
Vertex;

void addVertex(char *label, Vertex *VertexArray[], int *VertexCount)
{
	Vertex *NewVertex = malloc(sizeof(Vertex));
	strcpy(NewVertex->label, label);
	NewVertex->visited = 0;
	VertexArray[(*VertexCount)++] = NewVertex;
}

void addEdge(int start, int end, int weight, int AdjMatrix[][MAX])
{
	AdjMatrix[start][end] = weight;
}


void readFile(char *argv[], Vertex *VertexArray[], int *VertexCount, int AdjMatrix[][MAX])
{
	char *Token = NULL;
	char Buffer[100] = {};
	int node,weight = 0;
	FILE *IO = fopen(argv[1], "r+");
	if(IO == NULL)
		exit(0);
	while(fgets(Buffer, sizeof(Buffer), IO) != NULL)
	{
		//int i = 0;
		Token = strtok(Buffer, ",");
		addVertex(Token, VertexArray, VertexCount);
		while(Token != NULL)
		{
			Token = (NULL, ",");
			node = atoi(Token);
			Token = (NULL, ",");
			weight = atoi(Token);

			addEdge((*VertexCount)-1, node, weight, AdjMatrix);
		}
		
		//printf("%s\n", VertexArray[i++]->label);
	}
	fclose(IO);
}

void CreateAdjacencyMatrix(int AdjMatrix[][MAX])
{
	int start = 0, end = 0;
	int i = 0, j = 0;
	char buffer[100] = {};
	/* initialize adjacency matrix to -1 */
	for(i = 0; i < MAX; i++)
		for(j = 0; j < MAX; j++)
			AdjMatrix[i][j] = -1;
}

void Dijkstra(int StartVertex, Vertex *VertexArray, int AdjMatrix[][MAX])
{

}

int main(int argc, char *argv[])
{
	int AdjMatrix[MAX][MAX];
	int VertexCount = 0;
	Vertex *VertexArray[MAX];

	CreateAdjacencyMatrix(AdjMatrix);
	readFile(argv, VertexArray, &VertexCount, AdjMatrix);

	#ifdef PRINTIT
	for(int i = 0; i < VertexCount; i++)
	{
		for(int j = 0; j < VertexCount; j++)
			printf("%5d\t", AdjMatrix[i][j]);
		printf("\n");
	}
	#endif
}