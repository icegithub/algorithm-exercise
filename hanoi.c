#include <stdio.h>

int hanoi(int n, char a, char b, char c) 
{
  if(1==n) {
    printf("Move sheet %d from %c to %c\n", n, a, c);
  } else {
    hanoi(n-1, a, b, c);
    printf("Move sheet %d from %c to %c\n", n, a, c);
    hanoi(n-1, b, a, c);
  }
}

int main(int argc, char* argv[])
{
  int n = atoi(argv[1]);
  printf("Pleas input the sheet number:");
  /* scanf("%d", &n); */
  hanoi(n, 'a', 'b', 'c');
  return 0;
}
