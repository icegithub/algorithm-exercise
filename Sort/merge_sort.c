#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLENGTH 100		/* String Length */
#define TLEN 128

int 
copy(int d[], int dStart, int dEnd, int s[], int sStart, int sEnd)
{
  int dSize = dEnd - dStart + 1;
  int sSize = sEnd - sStart + 1;
  int i, j;//Control the add number
  if(dSize >= sSize) {
    for(i = 0, j = 0; i < dSize && j < sSize; i++, j++) {
      d[dStart++] = s[sStart++];
    }
    return 0;
  } 
  return -1;
}

void 
Mergesort(int A[], int aLength)
{
  if(aLength > 1) {
    int i = 0;
    int bLength = aLength / 2;
    int cLength = aLength - bLength;
    int *B = NULL, *C=NULL;
    B = (int*)calloc(bLength, sizeof(int));
    C = (int*)calloc(cLength, sizeof(int));
    copy(B, 0, bLength-1, A, 0, aLength / 2 - 1);
    copy(C, 0, cLength-1, A, aLength / 2, aLength - 1);
    
    printf("B: ");
    for(i = 0; i < bLength; i++)
      printf("%2d", B[i]);
    printf("\n");

    printf("C: ");
    for(i = 0; i < cLength; i++)
      printf("%2d", C[i]);
    printf("\n");
    
    Mergesort(B, bLength);
    Mergesort(C, cLength);
    Merge(B, bLength, C, cLength, A, aLength);
  }
}

int
Merge(int B[], int b_length, int C[], int c_length, int A[], int a_length)
{
  printf("\n+++++++Merge...++++++++\n");

  int i = 0, j = 0, k = 0;
  int p = b_length;
  int q = c_length;

  printf("B: ");
  for(i = 0; i < b_length; i++)
    printf("%2d", B[i]);
  printf("\n");

  printf("C: ");
  for(i = 0; i < c_length; i++)
    printf("%2d", C[i]);
  printf("\n");

  i = 0, j = 0, k = 0;
  while( i <  p && j < q ) {
    if(B[i] <= C[j]) {
      A[k] = B[i];
      i++;
    } else {
      A[k] = C[j];
      j++;
    }
    k++;
  }
  
  printf("K = %d\n", k);
  if (p == i) { //If i = p(the length of B) then copy the last of C into A
    printf("Copy C to A\n");
    copy(A, k, p+q-1, C, j, q-1);
  } else {
    printf("Copy B to A\n");
    copy(A, k, p+q-1, B, i, p-1);
  }
  free(B);
  free(C);
  printf("A: ");
  for(i = 0; i < a_length; i++)
    printf("%2d", A[i]);
  printf("\n=======End======= \n\n");
}

int main(){
  
  //String Merge Sort
  /* string_t A = createString(); */
  /* printf("The A String  is %s\n", A.string); */
  /* printf("The Length is %d\n", A.length); */
  /* Mergesort(A.string, A.length); */
  /* Mergesort(A); */
  
  //Number Merge Sort
  int A[] = {23, 24, 29, 8, 3, 2, 9, 7, 1, 5, 4};
  int aLength = 11;
  int i;

  Mergesort(A, aLength);

  printf("After Mergsort: ");
  for(i = 0; i < aLength; i++)
    printf("%2d ", A[i]);
  printf("\n");

  return 0;
}

