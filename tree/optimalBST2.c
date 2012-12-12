#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int rNum; //��(row)��
  int cNum;//��(column)��
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
  /* �������ű� */
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

  //����C���R��
  /* createTable(m, n, C, R); */
  C = (double**)calloc(m, sizeof(double*));
  R = (int**)calloc(m, sizeof(int*));
  for(i = 0; i < m; i++) {
    C[i] = (double*)calloc(n, sizeof(double));
    R[i] = (int*)calloc(n, sizeof(int));
  }

  /* ===========���Ŷ���������㷨=========== */
  /* optimalBST(p, len, C, R, m, n); */
  //R���C��ĵ�һ�����������ĸA, B, C....
  //�����ȿ���
  //����m��n(�鱾�ϵ�n P297��Ӱӡ����)�Ĺ�ϵ��n = m -1
  //��ʵ�������׼ȷ����ʹ��p�ĳ���len,len = n
  //��ʼ��C���R��
  n = len - 1;
  for(i = 1; i <= n; i++) {   /* �ѵ�������Ƶ����� */
    C[i][i-1] = 0;
    C[i][i] = p[i]; //i-1��Ϊ�˴�p����Ŀ�ʼ��ֵ
    R[i][i] = i;
    C[n+1][n] = 0;
  }
  int d;
  for (d = 1; d <= n-1; d++ ) {	/* �Խ��߼���, ��ʵʹ���ܹ������ϱ�����Ϊʲô���ǵ���n���Ҹо���ͨ������ļ��㣬C���n�лᱻ��� */
    for (i = 1; i <= n-d; i++) {
      int j = i + d;		/* �����j���ջᵽn�������Ϊ�������d��С�ڵ���n-1 */
      double min = 65536.0;
      double temp = 0.0;	/* ���ڴ��C[i][k-1] + C[k+1][j]�����ټ��㲽�� */
      int k, kmin = 0;
      for(k = i; k <= j; k++) {	/* k���ƴ�a��b��ÿһ�ֿ����� */
	if ( (temp = C[i][k-1] + C[k+1][j]) < min ) {
	  min = temp;
	  kmin = k;
	}
      }
      R[i][j] = kmin;
      double sum = p[i];
      int s;
      for (s = i + 1; s <= j; s++) {
	sum += p[s];
      }
      C[i][j] = min + sum;
    }
  }

  for(i = 1; i < m; i++) {
    for(j = 0; j < 5; j++) {
      /* if(C[i][j] == 0.0) */
      /* 	printf("   "); */
      /* else */
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


/* //���Ǵ���3άָ��ģ������� */
/* for(i = 0; i < m; i++) { */
/*      C = (double**)calloc(m, sizeof(double*)); */
/*      R = (int**)calloc(m, sizeof(int*)); */
/*      for(j = 0; j < n; j++) { */
/*           C[i] = (double*)calloc(n, sizeof(double)); */
/*           R[i] = (int*)calloc(n, sizeof(int)); */
/*      } */
/* } */
