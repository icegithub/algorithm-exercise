#include <stdio.h>
#include <stdlib.h>

int *test(int x)
{
  return (x*x);
}

int main(int argc, char* argv[])
{
  int rlt;
  int *r = NULL;
  int x = 12;
  r = test(x);			/* 这里感觉就是将r指针当成变量来使用了。还有就是这里test返回时是直接返回的，感觉没有分配真正的空间，导致返回后给r指针后没有指向有效的空间，在打印是如果使用(*r)则会出现明显的段错误，吸取教训啊，指针一定要指向有效的内存空间 */
  rlt = test(x);
  printf("result = %d\n", rlt);
  printf("r = %d\n", r);	/*  */

  int *r2 = (int*)calloc(1, sizeof(int));
  *r2 = x;
  /* (*r2) = x; /\* 这里是将指针中的指向的内存单元间给赋值为x的值 *\/  */
  printf("r2 = %d\n", (*r2));

  int *r3 = NULL;
  /* r3 = x; /\* 这里是将指针中的变量之间给赋值为x的值，而不是指向x *\/ */
  /* printf("r3 = %d\n", r3); */
  r3 = &x;			/* 这里是将x变量的地址赋值给r指针，这里估计就是使r指针指向x了吧 */
  printf("r3 = %d\n", (*r3));

  int *r4 = x;			/* 这里是将指针中的变量之间给赋值为x的值，而不是指向x */
  printf("r4 = %d\n", r4);	/*  */
  /* printf("r4 = %d\n", (*r4));	/\* 写成这样是错误的，这里的*是取该指针所指向的变量的内容，但是该指针没有指向任何变量 *\/ */
  
  return 0;
}
