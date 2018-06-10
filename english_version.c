/*
DIJKSTRA 
Social network presented like weighted graph. Nodes are users (name, surname and year).
0 is when two users are not connected, and numbers above 0 are distance between users.
The program loads the graph from the graph.txt file. (n is for number of users, a and b are for
serial nubers(users) and c is for distance.
The path function searches for the shortest path between two users using the DIJKSTRA algorithm.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20

typedef struct social_network
{
	char name[MAX];
	char surname[MAX];
	int year;
}NETWORK;

void load(NETWORK network[], FILE* in, int n, int matrix[n][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		fscanf(in,"%s %s %d", network[i].name, network[i].surname, &network[i].year);
	}
	for( i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			matrix[i][j] = 0;
int a;
int b;
int c;

	while( (fscanf(in,"%d %d %d", &a, &b, &c)) != EOF)
	{
		matrix[a-1][b-1] = c;
		//matrix[b-1][a-1] = c;	
	}
}

int findMin(int n, int dist[], int visited[])
{
	int min = 100000; //infinity
	int min_index = -1;
	int i;
	for (i = 0; i < n; i++)
		if (visited[i] == 0 && dist[i] <= min)
		{
			min = dist[i];
			min_index = i;
		}

	return min_index;
}
void relax(int n, int AdjMatrix[n][n], int dist[], int visited[], int min)
{
	for (int i = 0; i < n; i++)

			if (!visited[i] && AdjMatrix[min][i] != 0 && dist[min] != 100000)
				if( dist[min] + AdjMatrix[min][i] < dist[i] )
					dist[i] = dist[min] + AdjMatrix[min][i];
}

void path(int n, int AdjMatrix[n][n], int source, NETWORK network[], int d)
{
	int dist[n];     
	int i, j;
	int visited[n];

	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(AdjMatrix[i][j] > d) 	//uslov zadatka
				AdjMatrix[i][j] = 0;


	for (int i = 0; i < n; i++)
	{
		dist[i] = 100000;	
		visited[i] = 0;	
	}

	dist[source] = 0;	

	for (i = 0; i < n - 1; i++)
	{
		int min = findMin(n, dist, visited);	

		visited[min] = 1;

		relax(n, AdjMatrix, dist, visited, min);
	
	}

	printf("Paths: \n");
	for(i = 0; i < n;i++)
	{
		if(dist[i] == 100000)
			dist[i] = 0;
		printf("distance of user %d from user %d = %d\n",source+1, i+1, dist[i]);
	}
}


int main(int arg_num, char *args[])
{
	if(arg_num != 2)
	{
		printf("Bad arguments!");
		exit(1);
	}
	FILE *fp = fopen("graph.txt", "r");
	int n;
	fscanf(fp, "%d", &n);

	NETWORK network[n];
	int AdjMatrix[n][n];
	load(network, fp, n, AdjMatrix);
	
	path(n, AdjMatrix, 0, network, atoi(args[1]));

	return 0;
}
