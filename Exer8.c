/*
	Exercise: Vertex Coloring
	1. Complete the basic greedy coloring program below.
	2. Analyze the running time of the program.
*/

// TIME COMPLEXITY ANALYSIS:
// It can be observed that the time complexity of the algorithm is O(n^2) in the worst case.
// This is because for each vertex, we need to check all its adjacent vertices to determine the available colors.
// In the worst case, this can lead to a nested loop where we check each vertex against all its neighbors.
// Additionally, the insertion of edges into the adjacency list takes O(n) time already.
// When we do this for all vertices, the overall complexity becomes O(n^2).

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int x;
	struct node *next;
}graph;

graph **createAdjList(int *, int *);
void viewList(graph **, int);
int * graphColoring(graph **, int);
int getAvailableColor(graph **, int *, int, int);
void viewColor(int *, int);
void deleteGraph(graph **, int);

// create a new node
graph* createNode(int x){
	graph *newNode = (graph *)malloc(sizeof(graph));
	newNode->x = x;
	newNode->next = NULL;
	return newNode;
}

int main(){
	graph **g;
	int v, e;
	int *color;
	
	g = createAdjList(&v, &e);
	color = graphColoring(g, v);
	viewList(g, v);
	viewColor(color, v);
	
	free(color);
	deleteGraph(g, v);
}

graph **createAdjList(int *v, int *e){
	/*insert code here for creating an adjacency list*/

	// read from file
	FILE *fp = fopen("Exer8.in", "r");
	// ensure file is read
	if(fp == NULL){
		printf("Error opening file\n");
		exit(1);
	}

	// read number of vertices and edges
	fscanf(fp, "%d %d", v, e);

	// create an array of adjacency lists
	graph **g = (graph **)malloc(sizeof(graph *) * (*v));
	for(int i = 0; i < *v; i++){
		// initialize each list to NULL
		g[i] = NULL;
	}

	// read edges and create adjacency list
	for (int i=0; i<*e; i++){
		// read each edge
		int u, v;
		fscanf(fp, "%d %d", &u, &v);

		// create a new node for each vertex
		// for u->v
		// first time inserting a node
		if (g[u] == NULL) {
			g[u] = createNode(v);
		}
		// insert at the end of the list
		else {
			graph *temp = g[u];
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = createNode(v);
		}
		// for v->u
		// first time inserting a node
		if (g[v] == NULL) {
			g[v] = createNode(u);
		}
		// insert at the end of the list
		else {
			graph *temp = g[v];
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = createNode(u);
		}
	}
	// return the adjacency list
	fclose(fp);
	return g;
}

void viewList(graph **g, int v){
	int i;
	graph *p;
	
	for(i = 0; i < v; i++){
		p = g[i];
		printf("%d: ", i);
		//traverse the list connected to vertex i
		while(p != NULL){
			printf("%3d", p->x);
			p = p->next;
		}
		printf("\n");
	}
}

int * graphColoring(graph **g, int v){
	int *color, availCol, i;
	
	//colors are represented as integers starting from 0
	color = (int *)malloc(sizeof(int)*v);
	for(i = 0; i < v; i++)
		color[i] = -1;
	
	color[0] = 0;	//assign first vertex with the first color
	for(i = 1; i < v; i++){
		availCol = getAvailableColor(g, color, v, i);
		color[i] = availCol;
	}
	return color;
}

int getAvailableColor(graph **g, int *color, int v, int curr){
	graph *p;
	int *available, i, availCol;
	
	//keeps track of the colors used on any previously colored vertices adjacent to it
	available = (int *)malloc(sizeof(int)*(v));
	for(i = 0; i < v; i++)
		available[i] = 1;
	
	/*Insert code here for marking the colors that have been used 
	on any previously colored vertices adjacent to it.*/

	// traverse the adjacency list of the current vertex
	graph *temp = g[curr];
	while (temp != NULL) {
		// if the vertex is colored, mark its color as unavailable
		if (color[temp->x] != -1) {
			available[color[temp->x]] = 0;
		}
		temp = temp->next;
	}

	
	for(i = 0; i < v; i++){				//get the smallest color that is available
		if(available[i] == 1){
			availCol = i;
			break;
		}
	}
	
	free(available);
	return availCol;
}

void viewColor(int *color, int v){
	int i;
	
	for(i = 0; i < v; i++){
		printf("Vertex %d -> Color %d\n", i, color[i]);
	}
}

void deleteGraph(graph **g, int v){
	int i;
	graph *p;
	for(i = 0; i < v; i++){
		while(g[i] != NULL){
			p = g[i];
			g[i] = g[i]->next;
			free(p);
		}
	}
	free(g);
}
