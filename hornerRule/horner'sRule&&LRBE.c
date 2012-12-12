#include <stdio.h>
#include <stdlib.h>

#define LEN 100

//使用宏定义控制执行那部分的逻辑
#define HORNER
#define LRBE

//定义一个数组结构体，方便求LRBE
typedef struct {
     int length;
     int *contents;
}Array;

/**
 * 霍纳法则：求解多项式（polynomial）
 * 输入：一个数组及其长度，以及x的值
 * 输出：the value of the polynomial at x
 * */
int 
Horner(int P[], int length, int x)
{
  /* printf("Length = %d\n", length); */
  int i = 0, n = length - 1;
  int p = P[n];
  
  int quoient[LEN], q_length = 0;
  /* printf("Array of P: "); */
  /* for(i=n-1; i>=0; i--) { */
  /*   printf("%2d ", P[i]); */
  /* } */
  /* printf("\n"); */
  //求解p（就是最终需要的答案）
  for(i=0; i<n; i++) {
    p = x*p+P[i];
    quoient[q_length++] = p; //记录过程中产生的数（商的组成）
  }
  printf("\nQuieint:");
  //输出商的形式
  for(i = 0; i < q_length; i++) {
    printf("(%d)x^%d", quoient[i], (q_length-i-1));
    if(i < q_length - 1) printf("+");
  }
  //打印余数（其实此时的余数就是最终的结果啦）
  printf("\nRemienal:", p);
  return p;
}

/**
 * 从左到右求解二进制表达
 * 输入：a为底，b为指数的二进制数组及其长度
 * 输出：the value of a^n 
 * 公式：
   if bi = 0   (a^p)^2
   if bi = 1   (a^p)^2 * a
 * */
int LeftRightBinaryExponentiation(int a, int *b, int b_length)
{
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

Array *dec_to_bin(int n) {
     printf("n = %d\n", n);
     int i = 0, j = 0;
     Array *b = (Array*)calloc(sizeof(Array), 1);
     b->contents = (int *)calloc(sizeof(int), 20);
     while(n > 0) {
          b->contents[i++] = n % 2;
          n /= 2;
     }
     b->length = i;             /* 给b赋值长度 */
     return b;
}

/**
 * 先进的二进制求法。有空看
 * */
/* main()  */
/* {  */
/*      int  ival, n = 0;  */
/*      char bin[32];  */

/*      scanf("%d", &ival);  */
/*      while(ival >; 0) {  */
/*           bin[n++] = ival & 0x01;  */
/*           ival >;>;= 1;  */
/*      }  */
/*      for(n--; n >;= 0; n--)  */
/*           printf("%d", bin[n]);  */
/*      printf("\n");  */
/* }  */

int main(int argc, char *argv[]) 
{
#ifdef HORNER
  printf("++++++++++++++++++HORNER RULE++++++++++++++++++++++");
  int P[LEN] = {0};
  int length = 0;
  int x = 0;
  int result = 0;
  // input
  /* printf("Please input the number(input any letter to end).\n"); */
  while(scanf("%d", &P[length++])!=0){}

  getchar();

  /* printf("Please input x:"); */
  scanf("%d", &x);

  result = Horner(P, length, x);
  printf("The result is %d\n", result);
#undef HORNER
#endif

#ifdef LRBE
  /* Array *b = NULL;              /\*  *\/ */
  printf("++++++++++++++++++LRBE++++++++++++++++++++++\n");
  int product;
  int a = 2, n = 10;
  Array *b = (Array*)calloc(sizeof(Array), 1);
  b->contents = (int *)calloc(sizeof(int), 20);
  b = dec_to_bin(n);
  /* b = dec_to_bin(atoi(argv[1])); */
  
  product = LeftRightBinaryExponentiation(a, b->contents, b->length);
  printf("product(%d^%d)=%d\n", a, n, product);
#undef LRBE
#endif

  return 0;
}
