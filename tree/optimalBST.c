#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int rNum; //行(row)数
  int cNum;//列(column)数
  /* ElemType **p;  */
}table_t;

int createTable(int m, int n, double **C, int **R);
int destoryTable(int m, double **C, int **R);

int
createTable(int m, int n, double **C, int **R)
{
  int i;
  C = (double**)calloc(m, sizeof(double*));
  R = (int**)calloc(m, sizeof(int*));
  for(i = 0; i < m; i++) {
    C[i] = (double*)calloc(n, sizeof(double));
    R[i] = (int*)calloc(n, sizeof(int));
  }
  return 0;
}

int 
destoryTable(int m, double **C, int **R)
{
  /* 销毁两张表 */
  int i;
  for(i = 0; i < m; i++) {
    free(C[i]);
    free(R[i]);
  }
     
  return 0;
}

int
optimalBST(double *p, int len, double **C, int **R, int m, int n)
{
  int i, j;
  for(i = 0; i < m; i++) {
    for(j = 0; j < n; j++) {
      R[i][j] = 0;
    }
  }
  return 0;
} 

int main(int argc, char* argv[])
{
  double p[] = {0, 0.1, 0.2, 0.4, 0.3};
  int len = 5;

  double **C = NULL;
  int    **R = NULL;
     
  int m = 6, n = 5;
  int i, j;

  //创建C表和R表
  /* createTable(m, n, C, R); */
  C = (double**)calloc(m, sizeof(double*));
  R = (int**)calloc(m, sizeof(int*));
  for(i = 0; i < m; i++) {
    C[i] = (double*)calloc(n, sizeof(double));
    R[i] = (int*)calloc(n, sizeof(int));
  }

  /* ===========最优二叉查找树算法=========== */
  /* optimalBST(p, len, C, R, m, n); */
  //R表和C表的第一行用于填充字母A, B, C....
  //现在先空着
  //这里m与n(书本上的n P297（影印本）)的关系是n = m -1(这个我还不确定)
  //其实这里更加准确的是使用p的长度len,len = n
  //初始化C表和R表
  n = len - 1;
  for(i = 1; i <= n; i++) {   /* 难道这里控制的是行 */
    C[i][i-1] = 0;
    C[i][i] = p[i]; //i-1是为了从p数组的开始赋值
    R[i][i] = i;
    C[n+1][n] = 0;
  }
  int d;
  for(d = 1; d <= n-1; d++ ) {	/* 其实这里的d没有什么其他意思，就是一个控制循环次数的变量,这里是循环3次，因为从图（书P297上 影印本）中可知，是从第3列开始的，即2，到最后的第5列，循环了3次 */
    /* 下面的计算是从对角线开始的，意思是计算顺序: 
       C[1, 2] -> 
       C[2, 3] -> C[1, 3] -> 
       C[3, 4] -> C[2, 4] -> C[1, 4] */
    for(i = 1; i <= n-d; i++) {	/* i控制的是行，从书P296（影印本）图8.10可以看出，随着i增多，需要计算的空格减少 */
      int j = i + d;		/* j最终的值是n，这个C[i,j]下面还有多少空间，书P296（影印本）图8.10中的C[i, j]下面的空格 */
      double min = 65536.0;
      double temp = 0.0;
      int k, kmin = 0;
      for(k = i; k <= j; k++) {	/* k开始的值是i的值，因为是从这里开始的 */
	if ( (C[i][k-1] + C[k+1][j]) < min ) {
	  min = C[i][k-1] + C[k+1][j];
	  kmin = k;
	}
      }
      R[i][j] = kmin;
      /* 这里求解的是从i到j这些数的和 即sigma(P(s)) */
      double sum = p[i];
      int s;
      for (s = i + 1; s <= j; s++) {
	sum += p[s];
      }
      /* 将求得的最小值给C[i, j] */
      C[i][j] = min + sum;
    }
  }

  for(i = 1; i < m; i++) {
    for(j = 0; j < 5; j++) {
      printf("%2.1lf ", C[i][j]);
    }
    printf("\n");
  }
  for(i = 1; i < m; i++) {
    for(j = 0; j < 5; j++) {
      printf("%d ", R[i][j]);
    }
    printf("\n");
  }
     

  /* destoryTable(m, C, R); */
  for(i = 0; i < m; i++) {
    free(C[i]);
    free(R[i]);
  }

  return 0;
}


/* //这是创建3维指针的！！！！ */
/* for(i = 0; i < m; i++) { */
/*      C = (double**)calloc(m, sizeof(double*)); */
/*      R = (int**)calloc(m, sizeof(int*)); */
/*      for(j = 0; j < n; j++) { */
/*           C[i] = (double*)calloc(n, sizeof(double)); */
/*           R[i] = (int*)calloc(n, sizeof(int)); */
/*      } */
/* } */
