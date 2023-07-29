//Tyler Danh 1001706320
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
	int end,weight = 0;
	FILE *IO = fopen(argv[1], "r+");
	if(IO == NULL)
	{
		printf("File did not open.\n");
		exit(0);
	}
	while(fgets(Buffer, sizeof(Buffer), IO) != NULL)
	{
		//int i = 0;
		Token = strtok(Buffer, ",");
		addVertex(Token, VertexArray, VertexCount);
		while ((Token = strtok(NULL, ",")) != NULL)
        {
            end = atoi(Token);
            Token = strtok(NULL, ",");
            weight = atoi(Token);

            addEdge((*VertexCount)-1, end, weight, AdjMatrix);
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

void Dijkstra(int StartVertex, Vertex *VertexArray[], int AdjMatrix[][MAX], int VertexCount)
{
	int CurrentVertex = StartVertex;
	VertexArray[StartVertex]->distance = 0;
	VertexArray[StartVertex]->previous = -1;
	VertexArray[StartVertex]->visited = 1;
	int x,i,SmallestVertexIndex = 0;

	for (x = 0; x < VertexCount-1; x++)
	{
		for(i = 0; i < VertexCount; i++)
		{
			if (AdjMatrix[CurrentVertex][i] != -1 && !VertexArray[i]->visited)
			{
				if (VertexArray[CurrentVertex]->distance + AdjMatrix[CurrentVertex][i] < VertexArray[i]->distance)
				{
					VertexArray[i]->distance = VertexArray[CurrentVertex]->distance + AdjMatrix[CurrentVertex][i];
					VertexArray[i]->previous = CurrentVertex;
				}
			}
		}
		SmallestVertexIndex = -1;
		int SmallestVertex = INT_MAX;
		for(i = 0; i < VertexCount; i++)
		{
			if (!VertexArray[i]->visited)
			{
				if (VertexArray[i]->distance < SmallestVertex)
				{
					SmallestVertex = VertexArray[i]->distance;
					SmallestVertexIndex = i;
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int AdjMatrix[MAX][MAX];
	int VertexCount,startIndex,endIndex = 0;
	Vertex *VertexArray[MAX];
	char startVertex[6];
	char endVertex[6];
	char path[6];

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

	printf("What is the starting vertex?");
	scanf("%s", startVertex);
	while(startIndex < VertexCount && startVertex != VertexArray[startIndex]->label)
	{
		startIndex++;
	}

	Dijkstra(startIndex, VertexArray, AdjMatrix, VertexCount);

	printf("What is the destination vertex?");
	scanf("%s", endVertex);
	while(endIndex < VertexCount && endVertex != VertexArray[endIndex]->label)
	{
		endIndex++;
	}
	if(endIndex == VertexCount || startIndex == VertexCount)
		printf("Path does not exist");
	else
	{
		int pathindex = VertexArray[endIndex]->distance;
		int previndex = VertexArray[endIndex]->previous;
		path[pathindex] = VertexArray[endIndex]->label;
		while (pathindex > 0)
		{
			pathindex--;
			path[pathindex] = VertexArray[previndex]->label;
			previndex = VertexArray[previndex]->previous;
		}
	printf("%s\n", path);
	}
}