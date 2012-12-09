#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define N 4

int n, dist[10][10];
int n2, dist2[10][10];

void
printDist()
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

void
washall()
{
	int r[10][10];
	int i = 0, j = 0, k = 0;
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++){
			r[i][j] = dist[i][j];
		}
	}
	for(k = 0; k < n; k++) {
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				r[i][j] = r[i][j] || ( r[i][k] && r[k][j] );
			}
		}
	}
	//printDist(r);

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++){
			printf("%d ", r[i][j]);
		}
		printf("\n");
	}

}

int min(int a, int b)
{
	return a < b ? a : b;
}
void floyd()
{
	int i, j, k;
	int r[10][10];
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 10; j++){
			r[i][j] = dist2[i][j];
		}
	}
	for(k = 0; k < n2; ++k){
		for(i = 0; i < n2; ++i){
			for(j = 0; j < n2; ++j){
				r[i][j] = min(r[i][j], r[i][k]+r[k][j]);
			}
		}
	}
	for(i = 0; i < n2; i++) {
		for(j = 0; j < n2; j++){
			printf("%2d ", r[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	FILE *fin = fopen("warshell.dat", "r");
	fscanf(fin, "%d", &n);
	int i, j;
	for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j){
			fscanf(fin, "%d", &dist[i][j]);
		}
	}
	printf("washall\n");
	fclose(fin);
	washall();
	printf("=========================\n");
	FILE *fin2 = fopen("floyd.dat", "r");
	fscanf(fin2, "%d", &n2);
	for(i = 0; i < n2; ++i){
		for(j = 0; j < n2; ++j){
			fscanf(fin, "%d", &dist2[i][j]);
		}
	}
	fclose(fin2);
	printf("floyd\n");
	floyd();
	return 0;
	//exit(0);
}
