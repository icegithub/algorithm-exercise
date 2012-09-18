#include <stdio.h>

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


int main(int argc, char *argv[])
{
     int result = 0;
     result = recurisionFibonacci(15);
     printf ("%d\n", result);
     result = recurisionFibonacci( 15 );
     printf ("%d\n", result);
     result = iterationFibonacci( 15 );
     printf ("%d\n", result);

     return 0;
}
