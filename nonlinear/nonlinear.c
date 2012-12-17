#include <stdio.h>
#include <stdlib.h>

#define N 100

///////////////////////////////////////////////////////
// 平分法
//////////////////////////////////////////////////////
/* 声明一个函数指针 */
typedef double (*f)(double x);
typedef struct {
  // Bisection and method of position
  double a[N];			/* 用于记录中间产生的a */
  double b[N];			/* 用于记录中间产生的b */
  double x[N];			/* 用于记录中间产生的x */
  double f[N];                  /* 用于记录中间产生的f(x) */
  double xBefore[N];		/* newton method用于记录中间产生的Xn */
  double xAfter[N];             /* newton method用于记录中间产生的X(n+1) */
  int cngNum;		        /* Convergence number收敛次数 */
  int length;			/* 用于后期打印的长度控制 */
}msg_t;

int msgInit(msg_t *msg)
{
  int i = 0;
  /* 其实这里也可以使用calloc和指针（将变量定义为指针，而不是数组）
     ，不过我感觉大同小异，所以没有这么写 */
  for(i = 0; i < N; i++) {
    msg->a[i] = 0;
    msg->b[i] = 0;
    msg->x[i] = 0;
    msg->f[i] = 0;
    msg->xBefore[i] = 0;
    msg->xAfter[i] = 0;
  }
  msg->cngNum = 0;
  msg->length = 0;
  return 0;
}

double fun(double x) 
{
  return x*x*x - x - 1;
}

double dfun(double x)
{
  return 3*x*x - 1;
}

double bisection(f fun, double a, double b, double eps, msg_t *msg)
{
  int n = 1;
  double x = 0.0;
  while(n <= N) {
    x = ( a + b ) / 2;
    msg->x[msg->length] = x;
    /* “防止“程序返回，a，b, f没有赋值 */
    msg->b[msg->length] = b;
    msg->a[msg->length] = a;
    msg->f[msg->length] = fun(x);
    if( (x - a) < eps ) {
      return x;
    }
    double fval = fun(x);
    /* 矫正f */
    msg->f[msg->length] = fun(x);
    if(fval == 0) {
      msg->x[msg->length] = x;
      return x;
    }
    if( (fval * fun(a)) < 0 ) {
      b = x;
    } else {
      a = x;
    }
    /* 矫正a和b的值 */
    msg->b[msg->length] = b;
    msg->a[msg->length] = a;
    msg->length++;
    n++;
  }
  /* 返回括住根的区间,在上面的过程中已经存储了 */
  return -1.0;			/* 没有找到准确的，返回一个区间 */
}

double position(f fun, double a, double b, double eps, msg_t *msg)
{
  /* 本来这里应该交给相应的处理函数初始化，但是这里省略 */
  msg->length = 0;

  int n = 1;
  double x = 0.0;
  while(n <= N) {
    /* 区别在这个公式 */
    double fa = fun(a);
    double fb = fun(b);
    x = ( a * fb - b * fa ) / ( fb - fa );
    
    msg->x[msg->length] = x;
    /* “防止“程序返回，a，b, f没有赋值 */
    msg->b[msg->length] = b;
    msg->a[msg->length] = a;
    msg->f[msg->length] = fun(x);
    if( (x - a) < eps ) {
      return x;
    }
    double fval = fun(x);
    /* 矫正f */
    msg->f[msg->length] = fun(x);
    if(fval == 0) {
      msg->x[msg->length] = x;
      return x;
    }
    if( (fval * fun(a)) < 0 ) {
      b = x;
    } else {
      a = x;
    }
    /* 矫正a和b的值 */
    msg->b[msg->length] = b;
    msg->a[msg->length] = a;
    msg->length++;
    n++;
  }
  /* 返回括住根的区间,在上面的过程中已经存储了 */
  return -1.0;			/* 没有找到准确的，返回一个区间 */
}

double newtonMethod(f fun, f dfun, double x0, msg_t *msg)
{
  int i;
  int count;
  /* 记住第一个 */
  msg->xBefore[0] = x0;
  double x = x0 - fun(x0)/dfun(x0);
  msg->f[0] = fun(x);
  msg->xAfter[0] = x;
  if(msg->cngNum != 0)
    count = msg->cngNum;
  else
    count = N;
  /* 根据公式迭代 */
  for( i = 1; i < count; i++) {
    msg->xBefore[i] = x;
    x = x - fun(x)/dfun(x);
    msg->f[i] = fun(x);
    msg->xAfter[i] = x;
  }
  msg->length = i;
  return x;
}


int main(int argc, char* argv[])
{
  double x;
  msg_t msg;
  int i = 0;
  double a = 0.0, b = 2.0, esp = 0.000001;

  // biseciton 平分法
  printf("====平分法====\n");
  msgInit(&msg);
  x = bisection(fun, a, b, esp, &msg);
  for(i = 0; i < msg.length; i++) {
    printf("a=%8lf ", msg.a[i]);
    printf("b=%8lf ", msg.b[i]);
    printf("x=%8lf ", msg.x[i]);
    printf("f(x)=%8lf ", msg.f[i]);
    printf("\n");
  }
  printf("x = %lf\n", x);

  /* method of position 试位法 */
  /* 试位法与平分法的唯一区别就在于求Xn */
  printf("====试位法====\n");
  msgInit(&msg);
  x = position(fun, a, b, esp, &msg);
  for(i = 0; i < msg.length; i++) {
    printf("a=%8lf ", msg.a[i]);
    printf("b=%8lf ", msg.b[i]);
    printf("x=%8lf ", msg.x[i]);
    printf("f(x)=%8lf ", msg.f[i]);
    printf("\n");
  }
  printf("x = %lf\n", x);
  
  /* Newton's Method */
  printf("====牛顿法====\n");
  msgInit(&msg);
  /* 限制收敛次数 */
  msg.cngNum = 5;
  int x0 = 2.0;
  x = newtonMethod(fun, dfun, x0, &msg);
  printf("    Xn\t   X(n+1) f(X(n+1))\n");
  for(i = 0; i < msg.length; i++) {
    printf("%8lf ", msg.xBefore[i]);
    printf("%8lf ", msg.xAfter[i]);
    printf("%8lf ", msg.f[i]);
    printf("\n");
  }
  printf("x = %lf\n", x);

  return 0;
}
