/*Graph Diffusion with Adsorption: Input: A graph (first line is [r,c] followed by adjacency matrix*/
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
	return (a >= b)?a:b; 
}

void priorProbOfGraph(int **graph, int N, float *P_graph){
	int i;
	for(i=0;i<N;i++){
		P_graph[i] = 0.5f; //uniform prior
	}	
}

void adsorbGraph(int **graph, int N, int v, float *P_graph) {
	//Before BFS, all the nodes are unvisited
	int *visited = (int *)calloc(N,sizeof(int));
	if(!visited){
		printf("\nError: Memory leak for 'visited'.");
		exit(EXIT_FAILURE);
	}
	
	// queue implementation
	int front = 0;
	int rear = 0;
	int *Q = (int *)calloc(N,sizeof(int)); //this is the queue
	if(!Q){
		printf("\nError: Memory leak for 'visited'.");
		exit(EXIT_FAILURE);
	}
	
	// make vertex v visited
	visited[v] = 1;
	// enqueue vertex v
	Q[rear] = v; // insert at rear
	rear += 1; // increment rear

	while(rear != front){
		// dequeue
		int u = Q[front];
		//printf("\n%d %f", u, P_graph[u]);
		front += 1;

		// check adjacent nodes from u
		int i = 0, k = 0;
		//P_graph[u] = 0; //set its Prior to be updated
		//printf("\n%d(%f) --> [ ",u,P_graph[u]);
		for (i = 0; i < N; i++) {
			// update the graph prob --> posterior
			if(graph[u][i]){
				P_graph[u] = P_graph[u] + P_graph[i];
				k += 1;
				//printf("%d(%f) ",i,P_graph[i]);
			}
			
			// if there is adjacent vertex enqueue it
			if (!visited[i] && graph[u][i]) {
				Q[rear] = i;
				rear += 1;
				visited[i] = 1;
			}
		}
		//printf("] [k = %d]",k);
		if(!k){
			P_graph[u] = P_graph[u];
		}
		else{
			if(P_graph[u]/k > 1.0f){
				P_graph[u] = 1;
			}
			else{
				P_graph[u] = P_graph[u]/k;
			}
		}
		printf("\n%d %f", u, P_graph[u]);
	}
	printf("\n");
	free(Q);
}

int main(int *argc, char **argv) {

	//open the adjacency matrix file
	FILE *finp = fopen(argv[1],"r");
	if(!finp){
		printf("\nError finp: File read error.");
		exit(EXIT_FAILURE);
	}
	
	int N,row,col,i,j;
	fscanf(finp,"\n%d%d",&row,&col);
	N = row; //consider row and col as dummy variable

	//create the graph from the file
	int **graph;
	graph = (int **)calloc(N,sizeof(int *));
	if(!graph){
		printf("\nError: Memory leak for 'graph'.");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<N;i++){
		graph[i] = (int *)calloc(N,sizeof(int));
		if(!graph[i]){
			printf("\nError: Memory leak for 'graph[i]'.");
			exit(EXIT_FAILURE);
		}
		for(j=0;j<N;j++){
			fscanf(finp,"%d",&graph[i][j]);
		}
	}
	
	//make the graph undirected
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			graph[i][j]  = max(graph[i][j],graph[j][i]);
		}
	}
	
	//Prior probability of graph
	float *P_graph = (float *)calloc(N,sizeof(float));
	if(!P_graph){
		printf("\nError: Memory leak for 'P_graph'.");
		exit(EXIT_FAILURE);
	}
	
	// run bfs from 0th vertex (most general clause)
	priorProbOfGraph(graph, N, P_graph); //initialize Prior
	adsorbGraph(graph, N, 0, P_graph); //run adsorption
	
	fclose(finp);
	free(P_graph);
	for(i=0;i<N;i++){
		free(graph[i]);
	}
	free(graph);
		
	return 0;
}
