#include <stdio.h>
#include <stdlib.h>

int n, dist[10][10];
void printDist();

void floyd_washell()
{
	int i, j, k;
	for(k = 0; k < n; ++k){
		printDist();
		for(i = 0; i < n; ++i){
			for(j = 0; j < i; ++j){
				if(((i != j) && (dist[i][k] * dist[j][k] != 0)) &&\
					 ((dist[i][k] + dist[j][k] < dist[i][j]) || (dist[i][j] == 0))){
					dist[i][j] = dist[i][k] + dist[k][j];
					dist[j][i] = dist[i][j];
				}
			}
		}
	}
	printDist();
}

void printDist()
{
	int i, j;
	printf("   +");
	for(i = 0; i < n; ++i)
		printf("%4c", 65 + i);
	printf("\n");
	for(i = 0; i < n; ++i){
		printf("%4c", 65 + i);
		for(j = 0; j < n; ++j){
			printf("%4d", dist[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	FILE *fin = fopen("input.dat", "r");
	fscanf(fin, "%d", &n);
	int i, j;
	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			fscanf(fin, "%d", &dist[i][j]);
		}
	}
	floyd_washell();
	fclose(fin);
	exit(0);
}
