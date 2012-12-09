#include <stdio.h>
#include <stdlib.h>

#define LEN 100
//程序开关
#define HORNER
#define LRBE

typedef struct {
     int length;                /* 存放数组的长度 */
     int *contents;             /* 存放数组的内容 */
}Array;

/**
 *                 n-1
 *  M(n) = A(n) =  --
 *                 \  1=n 
 *                 / 
 *                 --
 *                 i=0
 * quotient 商数
 * */
int Horner(int P[], int length, int x)
{
  /* printf("Length = %d\n", length); */
  int i = 0, n = length - 1;
  int p = P[n];
  int q_length = 0, quotient[LEN];
  /* printf("Array of P: "); */
  /* for(i=n-1; i>=0; i--) { */
  /*   printf("%2d ", P[i]); */
  /* } */
  /* printf("\n"); */
  for(i=0; i<n; i++) {
    p = x*p+P[i];
    quotient[q_length++] = p;//记录每个中间过程的值，也就是后来要求的商
  }
  printf("Quotient:");
  for(i = 0; i < q_length; i++) {
       printf("(%d)x^%d", quotient[i], (q_length-1));
       if(i < q_length-1) printf("+");
  }
  printf("\nRemainder:");
  printf("%2d\n", p);
  return p;//其实这个p除了是要求的表达式的最终结果，这也是除以（x-x0）的余数
}

/**
 * 从左到右
 * 将指数转化为二进制传入函数，利用horner法则进行表达式的快速求解
 * */
int LeftRightBinaryExponentiation(int a, int *b, int b_length)
{
     /* int j; */
     /* for (j = b_length - 1; j >= 0; j--) { */
     /*      printf("%2d ", b[j]); */
     /* } */
     /* printf("\n"); */
     int product;
     int I, i;
     product = a;
     I = b_length - 1;
     for(i = I - 1; i >= 0; i--) {
          product *= product;
          if (b[i] == 1) {
               product *= a;
          }
     }
     return product;
}

/**
 * 将十进制转化为二进制
 * 数组的顺序与实际的顺序相反
 * */
Array *dec_to_bin(int n) {
     printf("n = %d\n", n);
     int i = 0, j = 0;
     Array *b = (Array*)calloc(sizeof(Array), 1);
     b->contents = (int *)calloc(sizeof(int), 20);
     /* do{ */
     while(n > 0) {
          b->contents[i++] = n % 2;
          n /= 2;
     }
     b->length = i;             /* 给b赋值长度 */
     return b;
}

int main(int argc, char *argv[]) 
{
#ifdef HORNER
  int P[LEN] = {0};
  int length = 0;
  int x = 0;
  int result = 0;
  // input
  printf("Please input the number(input any letter to end).\n");
  while(scanf("%d", &P[length++])!=0){}
  /* getchar(); */
  printf("Please input x:");
  scanf("%d", &x);

  result = Horner(P, length, x);
  printf("The result is %d\n", result);
#undef HORNER
#endif

#ifdef LRBE
  /* Array *b = NULL;              /\*  *\/ */
  
  int product;
  int a = 2, n = 10;

  Array *b = (Array*)calloc(sizeof(Array), 1);
  b->contents = (int *)calloc(sizeof(int), 20);
  b = dec_to_bin(n);
  /* b = dec_to_bin(atoi(argv[1])); */

  product = LeftRightBinaryExponentiation(a, b->contents, b->length);
  printf("product=%d\n", product);
#undef LRBE
#endif

  return 0;
}
