#include <stdio.h>
#include <string.h>

#define N 7

// visited array
int visited[N];

// graph as adjacency matrix
//0 1 2 3 4 5 6
int graph[N][N] = { { 0, 1, 1, 0, 0, 0, 0 }, //0
		{ 0, 0, 0, 0, 0, 0, 1 }, //1
		{ 0, 0, 0, 1, 0, 0, 1 }, //2
		{ 0, 0, 0, 0, 1, 0, 0 }, //3
		{ 0, 0, 0, 0, 0, 0, 1 }, //4
		{ 6, 0, 0, 1, 0, 0, 0 }, //5
		{ 0, 0, 0, 0, 0, 0, 0 }, //6
		};

// queue implementation
int front = 0;
int rear = 0;
int q[N] = { 0 };

void bfs(int v);

int main() {
	// make all vertex unvisited
	memset(visited, 0, sizeof(visited));

	// run bfs from 0th vertex
	bfs(0);
	return 0;
}

void bfs(int v) {

	// make vertex v visited
	visited[v] = 1;
	// enqueue vertex v
	q[rear] = v; // insert at rear
	rear++; // increment rear

	while (rear != front) // condition for empty queue
	{
		// dequeue
		int u = q[front];
		printf("%d ", u);
		front++;

		// check adjacent nodes from u
		int i = 0;
		for (i = 0; i < N; i++) {
			// if there is adjacent vertex enqueue it
			if (!visited[i] && graph[u][i]) {
				q[rear] = i;
				rear++;
				visited[i] = 1;
			}
		}
	}
	printf("\n");
}
