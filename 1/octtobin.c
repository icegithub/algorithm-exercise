#include <stdio.h>

#define LEN 50

/**
 *reutnr i is the number of the binary
 * */
int
octtobin( int n, int vector[] )
{
     if( n < 0 ) {
          printf( "N can't be 10\n" );
          return 0;
     }
     int i = 0;
     do {
          vector[i] = n % 2;
          n /= 2;
          i++;
     } while( n != 1 );
     vector[i] = n;
     return i+1;
}

int main(int argc, char *argv[])
{
     int n, count, i;
     int vector[LEN] = {0};
     printf ("please input the n:\n");
     scanf( "%d", &n );
     count = octtobin( n, vector );
     for (i = count-1; i >=0 ; --i)
     {
          printf( "%d", vector[i] );
     }
     printf( "\n" );
     return 0;
}
