#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SLENGTH 100
#define TLEN 128

#define PRINT_ADDRESS(addr) printf( "0x%08X\n", (addr) )

int step1 = 0;
int step2 = 0;

typedef struct {
  char a[SLENGTH];
  int length;
}string;

string createString()
{
  string s;
  int i = 0;
  scanf("%s", &s.a);
  while(s.a[i] != '\0') i++;
  getchar();
  s.length = i;
  return s;
}

int bruteForceStringMatch(string t, string p)
{
  int i, j;
  int n = t.length;
  int m = p.length;
  for(i = 0; i<n; i++) {
    step1++;
    j = 0;
    while(j < m && p.a[j]==t.a[i+j]) {
      step1++;
      j += 1;
    }
    if(j == m)
      return i;
  }
  return -1;
}

/**
 * ����һ���ƶ���
 * �������������128��ASCII�루�������Ѿ�����������е�λ�ü�������±꣩
 * �������ֵΪģʽ��P�е�ÿ����ĸ�������һ��λ�õľ���
 * ������ģʽ��P�ĳ��ȳ�ʼ��
 *
 * shiftTable��һ��������������һ��ָ�룬��ָ��ָ��һ������20��intԪ�ص�����
 * */
int (*shiftTable(string p))[TLEN]
{
  int i = 0, j = 0;
  int m = p.length;
  int (*table)[TLEN];//���Դ洢���ݵ���ʱ���飬���᷵���������
  table = ( int (*)[TLEN] )malloc( TLEN * sizeof(int) );

  //��ʼ�����飬��ģʽ��P�ĳ��ȳ�ʼ��
  //initialize all the elements of table with m
  for(i=0; i<TLEN; i++)
    (*table)[i] = m;

  //��ӡ��
  /* for(j=0; j<TLEN; j++) { */
  /*      printf("\n%c: %3d ", j, (*table)[j]); */
  /* } */
  /* printf("\n"); */

  /* printf("m: %d, p: %s\n", m, p.a); */
     
  //��ʼ�����������е�������Hashɢ�У�������д�ƶ�����
  for(j=0; j<m-1; j++) {
    int letter = p.a[j];
    printf("  letter=%3d", letter);
    (*table)[letter] = m-1-j;
  }
  printf( "\n" );

  //��ӡ�����õ��ƶ���
  /* for(j=0; j<TLEN; j++) { */
  /*      printf("\n%c: %4d ", j, (*table)[j]); */
  /* } */
  /* printf("\nShift Table End Here. And now return!\n"); */

  return table;
}

/**
 * Horspool�ַ�ƥ���㷨
 * ˼·��
 * ��������һ���ƶ�������index��ÿ��ASCII�ַ���λ�ã�
 * �����ǣ�������ַ���ģʽ��P�г��֣���������ַ�����ģʽ��Pĩ�ˣ����ҶΣ�
 * �ľ��룬���û�г��ֵ��ַ�����дģʽ��P�ĳ��ȡ�
 *
 * ƥ�䣺
 * ����T��ģʽ��P��˶��룬Ȼ���ģʽ��P�Ҷ˿�ʼ����ƥ�䡣���T��P��ͬ�����������ƥ�䣻
 * ���ƥ��ʧ�ܣ����Ӧ������T��ʱ���ַ����ƶ����ҳ�ģʽ��P�����ƶ��ľ��롣
 * ֱ��ƥ��ɹ������ߵ�������T�ġ���ͷ��
 *
 * ������
 * J I M _ S A W _ M E _ I N _ A _ B A R B E R S H O P
 * B A R B E R           B A R B E R
 *         B A R B E R       B A R B E R 
 *           B A R B E R           B A R B E R
 * */
int horspoolMatching(string t, string p)
{
  int (*table)[TLEN] = NULL;
  int m = p.length, n = t.length;
  int i, k = 0;
  i = m - 1;
  printf("\nStart to get shift table\n");
  table = shiftTable(p);
  printf("\nGet shift table end\n");
  
  /* for(k=0; k<TLEN; k++) { */
  /*      printf("\n%c: %2d", k, (*table)[k]); */
  /* } */
  /* printf("\nPrint end!\n"); */
  
  printf("\nStarting Matching....!\n");
  while(i<=n-1) {
    step2++;
    k = 0;
    while(k<=m-1 && p.a[m-1-k]==t.a[i-k]) {
      step2++;
      k += 1;
    }
    if(k == m) {
      return i-m+1;
    }
    else {
      int temp = t.a[i];
      i = i + (*table)[temp];//�ƶ��ľ�����ƶ���(Shift Table)
      step2++;
    }
  }
  return -1;
}

int main()
{
  string t, p;
  int ret;
  printf("Please input t:\n");
  t = createString();
  /* printf("t=%s\n", t.a); */
  printf("t length=%d\n", t.length);

  printf("Please input p:\n");
  p = createString();
  /* printf("p=%s\n", p.a); */
  printf("p length=%d\n", p.length);


  printf( "\n==========Brite Force String Match=============\n" );
  ret = bruteForceStringMatch(t, p);
  if(-1 == ret) {
    printf("Don't match!\n");
  }
  else {
    printf("Match, the start position is %d\n", ret+1);
  }
  printf( "==========Brite Force String Match End=============\n" );

  printf( "\n==========Horspool String Match=============\n" );
  ret = horspoolMatching(t, p);
  if(-1 == ret) {
    printf("Don't match!\n");
  }
  else {
    printf("Match, the start position is %d\n", ret+1);
  }
  printf( "==========Horspool String Match End=============\n" );

  printf("Step1 is %d\n", step1);
  printf("Step2 is %d\n", step2);
  return 0;
}
