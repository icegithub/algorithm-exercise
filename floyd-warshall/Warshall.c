#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* #define INF 0 */
#define N   10      // the size of the matrix

typedef char vertex_t;
typedef int  edge_t;
typedef int flag_t;

typedef struct {
	int vexnum;     //record the number of the vex
	int edgenum;    //record the number of the edge
	flag_t isDigraph;   //the graph is digraph or not
	flag_t hasWeighted; //the edge has weighted or not
	vertex_t vexs[N]; 
	edge_t edges[N][N];//record the power of the arc
}adjacency_matrix_t;

/**
 *init 
 */
int 
init_adjacency_matrix(adjacency_matrix_t *g, flag_t isDigraph, flag_t hasWeighted)
{
	if(!g)
		return -1;
	g->isDigraph = isDigraph;
	g->hasWeighted = hasWeighted;
	return 0;
}

/**
 * create adjacency matrix
 * input: adjacency_matrix_t and flag of graph ( 1 -> digraph; 0 -> undirected graph )
 * output: success or failed
 */
int 
create_adjacency_matrix(adjacency_matrix_t *g)
{
	if(!g) {
		printf("g is null\n");
		return -1;
	}
	int i = 0, j = 0;
	vertex_t v;

	//init
	g->vexnum = 0;
	g->edgenum = 0;

	//input vertex
	printf("Please input the veretx and end by #\n");
	while( scanf("%c", &v) && v != '#' ) {
		getchar();
		if(v != ' ') {
			g->vexs[i] = v;
			i++;
		}
	}
	g->vexnum = i;
	/* { */
	/* 	g->vexs[0] = 'a'; */
	/* 	g->vexs[1] = 'b'; */
	/* 	g->vexs[2] = 'c'; */
	/* 	g->vexs[3] = 'd'; */
	/* 	g->vexnum = 4; */
	/* } */
	
	int inf_flag = 0;
	if (g->hasWeighted){
		inf_flag = 65536;
	} else {
		inf_flag = 0;
	}
	//input edge
	for(i=0;i<g->vexnum;i++) {
		for(j=0;j<g->vexnum;j++) {
			g->edges[i][j]=inf_flag;
		}
	}

	//storage the edge
	g->edgenum = 0;
	if (g->isDigraph == 1) {
		for(i=0;i<g->vexnum;i++) {
			for(j=0;j<g->vexnum;j++) {
				if(i == j)
					continue;
				printf("%c->%c: ", g->vexs[i], g->vexs[j]);
				edge_t w = 0;
				scanf("%d", &w);
				printf("w = %d", w);
				g->edges[i][j] = w;
				g->edgenum++;
				printf("\n");
			}
		}
	} else {
		for(i=0;i<g->vexnum;i++) {
			for(j=0;j<g->vexnum;j++) {
				if(i <= j)
					continue;
				printf("%c->%c:", g->vexs[i], g->vexs[j]);
				edge_t w = 0;
				scanf("%d", &w);
				g->edges[i][j] = g->edges[j][i] = w;
				g->edgenum++;
				printf("\n");
			}
		}
	}

	return 0;
}

int 
display_adjacency_matrix(adjacency_matrix_t *g)
{
	if (!g) {
		printf("g is null\n");
		return -1;
	}
	int i, j;
	for(i = 0; i < g->vexnum; i++) {
		printf("%c ", g->vexs[i]);
		for(j = 0; j < g->vexnum; j++) {
			printf("%d ", g->edges[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int 
destory_adjacency_matrix(adjacency_matrix_t *g)
{
	if(!g)
		return -1;
	free(g);
	return 0;
}

int 
WarshallAlgorithm(adjacency_matrix_t *g)
{
	if(!g)
		return -1;	
	int i = 0, j = 0, k = 0;
	int n = g->vexnum;
	for(k = 0; k < n; k++) {
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				g->edges[i][j] = g->edges[i][j] || ( g->edges[i][k] && g->edges[k][j] );
			}
		}
	}
	return 0;
}

static int 
min(int a, int b)
{
	return ( a < b ? a : b );
}

int 
FloydAlgorithm(adjacency_matrix_t *g)
{
	if(!g)
		return -1;
	int i, j, k;
	int n = g->vexnum;
	for(k = 0; k < n; ++k){
		for(i = 0; i < n; ++i){
			for(j = 0; j < n; ++j){
				g->edges[i][j] = min(g->edges[i][j], g->edges[i][k]+g->edges[k][j]);
			}
		}
	}
	return 0;
}

int 
main(int argc, char *argv[])
{
	adjacency_matrix_t g;

	init_adjacency_matrix(&g, 1, 0);
	create_adjacency_matrix(&g);
	display_adjacency_matrix(&g);
	printf("++++++++++++++++++++\n");
	WarshallAlgorithm(&g);
	display_adjacency_matrix(&g);

	printf("++++++++++++++++++++\n");
	init_adjacency_matrix(&g, 1, 0);
	create_adjacency_matrix(&g);
	display_adjacency_matrix(&g);
	FloydAlgorithm(&g);
	display_adjacency_matrix(&g);

	destory_adjacency_matrix(&g);
	
	return 0;
}
