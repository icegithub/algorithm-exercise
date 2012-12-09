/**
 * remember complier it with
 * gcc fibonacci.c -lm
 * */


#include <stdio.h>
#include <math.h>
/**
 * Method 1
 * */
int recurisionFibonacci(int n)
{
     if( n <= 2 )
          return 1;
     else
          return  recurisionFibonacci( n-1 ) + recurisionFibonacci( n-2 );
}

/**
 * Method 2
 * */
int recurisionFibonacci2( int n, int a, int b, int count )
{
     if( count == n )
          return b;
     else
          return recurisionFibonacci2( n, a, a+b, count++ );
}

int fiboncacci( int n )
{
     return recurisionFibonacci2( n, 0, 1, 1 );
}
/**
 * Method 3
 * */
int iterationFibonacci( int n )
{
     int i = 0;
     int x = 0, y = 1; //The initial
     for (i = 1; i < n; ++i)
     {
          y = x + y;
          x = y - x;
     }
     return y;
}


/**
 * Method 4
 * */
int threoyFibonacci(int n)
{
     int i = 0;
     double result = 0.0;
     double argument1 = 0.0, argument2 = 0.0;
     argument1 = 1 / (sqrt(5));
     argument2 = ( 1 + sqrt(5) ) / 2;
     argument2 = pow(argument2, n);
     result = argument1 * argument2;
     if(result >= (int)result+0.5)
          result++;
     return result;
}


/**
 * Method 5
 * */
int maxtriFibonacci(int n)
{
     n -= 2;
     int a[4]={0, 1, 1, 1}, b[4]={0, 1, 1, 1};
     int result, i, left, right;
     for(i = 0; i < n; i++) {
          left = a[2]*b[0] + a[3]*b[2];
          right = a[2]*b[1] + a[3]*b[3];
          a[2] = left;
          a[3] = right;
          result = right;
     }

     return result;
}


int main(int argc, char *argv[])
{
     int n = 43;
     int result = 0;

     /* result = recurisionFibonacci(n); */
     /* printf ("%d\n", result); */

     /* result = recurisionFibonacci( n ); */
     /* printf ("%d\n", result); */

     /* result = iterationFibonacci( n ); */
     /* printf ("%d\n", result); */

     /* result = threoyFibonacci( n ); */
     /* printf ("%d\n", result); */

     result = maxtriFibonacci( n );
     printf ("%d\n", result);


     return 0;
}
