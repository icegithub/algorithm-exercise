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
 * 制作一张移动表。
 * 表里面的内容是128个ASCII码（在这里已经变成在数组中的位置即数组的下标）
 * 表里面的值为模式串P中的每个字母距离最后一个位置的距离
 * 其余用模式串P的长度初始化
 *
 * shiftTable是一个函数，它返回一个指针，该指针指向一个包含20个int元素的数组
 * */
int (*shiftTable(string p))[TLEN]
{
  int i = 0, j = 0;
  int m = p.length;
  int (*table)[TLEN];//用以存储数据的临时数组，最后会返回这个数组
  table = ( int (*)[TLEN] )malloc( TLEN * sizeof(int) );

  //初始化数组，用模式串P的长度初始化
  //initialize all the elements of table with m
  for(i=0; i<TLEN; i++)
    (*table)[i] = m;

  //打印表
  /* for(j=0; j<TLEN; j++) { */
  /*      printf("\n%c: %3d ", j, (*table)[j]); */
  /* } */
  /* printf("\n"); */

  /* printf("m: %d, p: %s\n", m, p.a); */
     
  //开始制作表，这里有点类似于Hash散列，就是填写移动距离
  for(j=0; j<m-1; j++) {
    int letter = p.a[j];
    printf("  letter=%3d", letter);
    (*table)[letter] = m-1-j;
  }
  printf( "\n" );

  //打印制作好的移动表
  /* for(j=0; j<TLEN; j++) { */
  /*      printf("\n%c: %4d ", j, (*table)[j]); */
  /* } */
  /* printf("\nShift Table End Here. And now return!\n"); */

  return table;
}

/**
 * Horspool字符匹配算法
 * 思路：
 * 首先制作一张移动表，索引index是每个ASCII字符的位置，
 * 内容是：如果该字符在模式串P中出现，就填入该字符距离模式串P末端（最右段）
 * 的距离，如果没有出现的字符都填写模式串P的长度。
 *
 * 匹配：
 * 主串T和模式串P左端对齐，然后从模式串P右端开始向左匹配。如果T与P相同，则继续往左匹配；
 * 如果匹配失败，则对应于主串T此时的字符查移动表，找出模式串P向右移动的距离。
 * 直至匹配成功，或者到达主串T的“尽头”
 *
 * 举例：
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
      i = i + (*table)[temp];//移动的距离查移动表(Shift Table)
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
