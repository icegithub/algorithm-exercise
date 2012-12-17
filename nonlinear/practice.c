#include <stdio.h>
#include <stdlib.h>

/* 定义一个有一个int参数的函数，返回值为int的函数指针 */
typedef int (*f)(int);

/* 声明一个函数实现 */
int fun(int);
int fun2(int);
/* 定义一个需要调用函数指针的函数 */
int test(f fp, int x);

/* 实现一个函数 */
int fun(int x) 
{
  /* 这里曾经导致一个致命的错误，原因是没有分配指针指向内存的地址 */
  /* int *ret = (int*)calloc(1, sizeof(int)); */
  int *ret;
  int temp = x * x;
  /* (*ret) = x * x; */
  ret = &temp;
  return (*ret);
  /* return (x * x); */
}

int fun2(int x) 
{
  return x + x;
}

int test(f fp, int x)
{
  int result;
  result = fp(x);
  printf("Result=%d\n", result);
  return 0;
}

/* 我发现这里如果写出这个样子:
int *test2(int *x)
{
  return (*x)*(*x);
}
也是可以的，但是会有警告，不过一切运行正常
*/
/* 写成一下这种情况是完全正确的 */
/* int test2(int *x) */
/* { */
/*   return (*x)*(*x); */
/* } */
/* int main(int argc, char *argv[]) */
/* { */
/*   test(fun2, 10); */
/*   int x = 13; */
/*   x = test2(&x); */
/*   printf("x=%d\n", x); */
/*   return 0; */
/* } */

/* 写成这样也是可以的，这样就不必申请地址，或者定义一个临时变量了 */
int *test2(int *x) 
{
  return (*x)*(*x);		/* 我明白了，这里返回需要有一个空间，单单返回指针，是会报错的！但是返回整型就不一样了 */
  /* 还有就是，其实test2 和 *test2 是一样的，他们都是表示函数指针（常量），test2是设计者们设计的*test2的简写吧 */
  /* 所以写成(int*)(*x)*(*x)就是错的，因为返回的明明是一个整型 */
} 
int main()
{
  int *x;
  int x2 = 13;
  x = test2(&x2);
  /* printf("x=%d\n", (*x));	/\* 这样写就是错的 *\/ */
  printf("x=%d\n", x);
  printf("x=%d\n", test2(&x2));
}

/* /\* 我曾经还这样写过 *\/ */
/* int *test2(int x) */
/* { */
/*   int *ret = NULL; */
/*   int temp = x * x; */
/*   ret = &temp;			/\* 不要忘记这里有一个去地址符 *\/ */
/*   return ret; */
/* } */
/* /\* 相应的主函数中写成这个样子 *\/ */
/* int main() */
/* { */
/*   int *x = NULL; */
/*   x = test2(13); */
/*   printf("x=%d\n", (*x)); */
/* } */
