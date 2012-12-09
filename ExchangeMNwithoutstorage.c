#include <stdio.h>

int exchangeTwoNumber(int *u, int *v) 
{
     *u = *u + *v; //这相当于保存了两者的共性
     *v = *u - *v; //通过减法将两者逐个分开
     *u = *u - *v;
     /* *u = *u | *v; */
     /* *v = *u | *v; */
     /* *u = *u | *v; */
}

/* int  */
/* exchange2(int *x, int &y) */
/* { */
/*      int temp = x; */
/*      x = y; */
/*      y = temp; */
/*      printf("x=%d, y=%d\n", x, y); */
/* } */

int main(int argc, char *argv[])
{
     int temp1 = 2;
     int temp2 = 4;
     int *m = &temp1;
     int *n = &temp2;
     printf("Before: m = %d, n = %d\n", *m, *n);
     /* exchangeTwoNumber(m, n); */
     exchange2(temp1, temp2);
     printf("After: m = %d, n = %d\n", *m, *n);
}
