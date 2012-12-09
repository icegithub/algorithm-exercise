#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define N 4 					/* the size of the matrix */
#define INFINITY 65536
#define MAX_VERTEX_NUM 20

typedef char vertex_t;
typedef int  edge_t;

/* 以下结构体暂时没有用到 */
typedef enum {DG, DN, UDG, UDN} graph_kind_t; /* {有向图, 有向网, 无向图, 无向图} */
typedef struct {
	vertex_t *v;
	edge_t *e;
	graph_kind_t gkt;			/* 图的中类别 */
}graph_t;
/* 结束 */

typedef struct {
	int vexnum;
	int arcnum;
	int edgenum;
	vertex_t *v;				/* 顶点 */
	edge_t **arcs;				/* 因为邻接矩阵存储的是边的信 */
	vertex_t ***short_path;		/* 用于存放最短路径 */
}adjacency_matrix_t;

/**
 *初始化结构体
 */
int init_adjacency_matrix(adjacency_matrix_t *g, 
                          int vexnum)
{
	if(!g || vexnum <= 0)
		return -1;

	g->vexnum = vexnum;
	g->arcnum = vexnum;
	g->edgenum = 0;
	
	g->v = (vertex_t*)calloc(g->vexnum, sizeof(vertex_t));

	g->arcs = (edge_t**)calloc(g->arcnum, sizeof(edge_t*));
	g->short_path = (vertex_t***)calloc(g->vexnum, sizeof(vertex_t**));
	int i = 0, j= 0;
	for (i = 0; i < g->arcnum; i++) {
		g->arcs[i] = (edge_t*)calloc(g->arcnum, sizeof(edge_t));
		g->short_path[i] = (vertex_t**)calloc(g->vexnum, sizeof(vertex_t*));
		for (j = 0; j < g->vexnum; j++) {
			g->short_path[i][j] = (vertex_t*)calloc(g->vexnum, sizeof(vertex_t));
		}
	}
	return 0;
}

/**
 *通过外面传入一个顶点数组一个矩阵来进行设置
 */
int 
set_adjacency_matrix(adjacency_matrix_t *g, 
                     vertex_t *v, edge_t e[][N])
{
	if(!g)
		return -1;
	int i = 0, j = 0;
	/* 顶点的复制 */
	for (i = 0; i < g->vexnum; i++) {
		g->v[i] = v[i];
	}
	/* 边的复制 */
	for (i = 0; i < g->arcnum; i++) {
		for (j = 0; j < g->arcnum; j++) {
			g->arcs[i][j] = e[i][j];
		}
	}
	return 0;
}

/**
 *打印邻接矩阵和最短路径
 */
int 
display_adjacency_matrix(adjacency_matrix_t *g, int flag)
{
	if (!g) {
		printf("g is null\n");
		return -1;
	}
	int i, j;
	/* 打印邻接矩阵 */
	for(i = 0; i < g->arcnum; i++) {
		printf("%c| ", g->v[i]);
		for(j = 0; j < g->arcnum; j++) {
			printf("%5d  ", g->arcs[i][j]);
		}
		printf("\n");
	}

	if(flag) {
		/* 打印最短路径 */
		for (i = 0; i < g->arcnum; i++) {
			printf("From %c to any node:\n", g->v[i]);
			for (j = 0; j < g->arcnum; j++) {
				if (i != j && g->short_path[i][j] != '\0') {
					printf("%c%s%c\n", g->v[i], g->short_path[i][j], g->v[j]);
				}
			}
			printf("\n");
		}
	}
	return 0;
}

/**
 *销毁邻接矩阵
 */
int 
destory_adjacency_matrix(adjacency_matrix_t *g)
{
	if(!g)
		return -1;
	int i = 0, j = 0;
	/* 从里到外释放，像int类型的话不必写free，free接受的参数是指针类型 */
	free(g->v);
	for(i = 0; i < g->arcnum; i++) {
		free(g->arcs[i]);
		for(j = 0; j < g->vexnum; j++) {
			free(g->short_path[i][j]);
		}
		free(g->short_path[i]);
	}
	free(g->arcs);
	/* free(g);					/\* This can't be free *\/ */
	return 0;
}

/**
 *Warshall Algorithm
 */
int 
WarshallAlgorithm(adjacency_matrix_t *g)
{
	if(!g)
		return -1;	
	int i = 0, j = 0, k = 0;
	int n = g->arcnum;
	edge_t x, y;
	for(k = 0; k < n; k++) { /* 这里的k就是从一点到另一点中间需要经过的节点中最短路径需要经过的节点个数 */
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				g->arcs[i][j] = 
					(x = g->arcs[i][j]) || /* 这行为真，则表示可以“直达”（意思是在这个k值时可以从a直接到达b） */
					(y = ( g->arcs[i][k] && g->arcs[k][j] )); /* 通过k值可以从a到达b */
				if ( !x && y ) {	/* strlen(short_path[i][j])这个是告诉偏移的位置，用来存放经过的中间节点 */
					/* 因为寻找的是中间节点，a通过k到达b，所以要将a到k的最短路径和k到b的最短路径加入到最短路径中去 */
					/* g->short_path[i][j]记录的是从a到达b需要经过的节点 */
					sprintf( g->short_path[i][j], "%s%c%s", g->short_path[i][k], g->v[k], g->short_path[k][j]); 
				} 
			}
		}
	}
	return 0;
}

/**
 *Floyd Algorithm
 */
int 
FloydAlgorithm(adjacency_matrix_t *g)
{
	if(!g)
		return -1;
	int i, j, k;
	int n = g->arcnum;
	edge_t x, y;
	for(k = 0; k < n; ++k){		/* 这里的k就是从一点到另一点中间需要经过的节点中最短路径需要经过的节点个数 */
		for(i = 0; i < n; ++i){	/* i控制行 */
			for(j = 0; j < n; ++j){ /* j控制列 */
				g->arcs[i][j] =
					(x = g->arcs[i][j]) < (y = g->arcs[i][k]+g->arcs[k][j]) ? x : y;
				/* 如果x<y说明这个是直达的，那么就不做任何处理，意思就是：short_path[i][j][0...k]没有内容 */
				if ( x > y) {	/* strlen(short_path[i][j])这个是告诉偏移的位置，用来存放经过的中间节点 */
					/* 因为寻找的是中间节点，a通过k到达b，所以要将a到k的最短路径和k到b的最短路径加入到最短路径中去 */
					/* g->short_path[i][j]记录的是从a到达b需要经过的节点 */
					sprintf( g->short_path[i][j], "%s%c%s", g->short_path[i][k], g->v[k], g->short_path[k][j]); 
				}
			}
		}
	}
	return 0;
}

int 
main(int argc, char *argv[])
{
	adjacency_matrix_t g;
#undef N 
#define N 4
	int vexnum = N;
	vertex_t v[N] = {'a', 'b', 'c', 'd'};
	edge_t e[N][N] = {
		{0, 1, 0, 1}, 
		{0, 0, 1, 0},
		{0, 0, 0, 1},
		{0, 0, 0, 0}
	};
	printf("\n============Warshell==================\n");
	init_adjacency_matrix(&g, vexnum);
	set_adjacency_matrix(&g, (vertex_t*)v, e);
	display_adjacency_matrix(&g, 0);
	WarshallAlgorithm(&g);
	printf("\n==============================\n");
	display_adjacency_matrix(&g, 1);
	destory_adjacency_matrix(&g);

	printf("\n=============Floyd=================\n");
	vertex_t v2[N] = {'a', 'b', 'c', 'd'};
	edge_t e2[N][N] = {
		{0, INFINITY, 3, INFINITY},
		{2, 0, INFINITY, INFINITY},
		{INFINITY, 7, 0, 1},
		{6, INFINITY, INFINITY, 0}
	};
	init_adjacency_matrix(&g, vexnum);
	set_adjacency_matrix(&g, (vertex_t*)v2, e2);
	display_adjacency_matrix(&g, 0);
	FloydAlgorithm(&g);
	printf("\n==============================\n");
	display_adjacency_matrix(&g, 1);
	destory_adjacency_matrix(&g);


	/* 	printf("\n=============Floyd=================\n"); */
	/* #undef N  */
	/* #define N 4 */
	/* 	vertex_t v3[N] = {'a', 'b', 'c'}; */
	/* 	edge_t e3[N][N] = { */
	/* 		{0, 4, 11}, */
	/* 		{6, 0, 2}, */
	/* 		{3, INFINITY, 0} */
	/* 	}; */
	/* 	init_adjacency_matrix(&g, vexnum); */
	/* 	set_adjacency_matrix(&g, (vertex_t*)v3, e3); */
	/* 	display_adjacency_matrix(&g); */
	/* 	FloydAlgorithm(&g); */
	/* 	printf("\n==============================\n"); */
	/* 	display_adjacency_matrix(&g); */
	/* 	destory_adjacency_matrix(&g); */

	printf("Hello, world\n");
	return 0;
}
