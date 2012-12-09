#include <stdio.h>
#define N 12
long combi(int n, int r) 
{
  int i;
  long p = 1;
  for(i = 1; i <= r; i++) {
    p = p * (n - i + 1) / i;
  }
  return p;
}

int main(int argc, char* argv[])
{
  int n, r, t;
  for(n=0; n<=N; n++) {
    for(r=0; r<=n; r++) {
      int i; 			/* set up the sort starting */
      if(i==0) {
	for(i=0; i<=(N-n); i++) {
	  printf("  ");
	}
      } else {
	printf("  ");
      } /* set up the end of the sorting */
      printf("%3ld", combi(n,r));
    } 
    printf("\n");
  }
  printf("Hello, icecream\n");
  return 0;
}
