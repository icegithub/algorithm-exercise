#include <stdio.h>

typedef struct {
     int a;
     int b;
     int c;
     int d;
}matrix_t;

static matrix_t matrix_multiply( matrix_t m1, matrix_t m2 )
{
     matrix_t m;
     /* m = ( matrix )colloc( sizeof( matirx_t ) ); */
     m.a = m1.a*m2.a + m1.b*m2.c;
     m.b = m1.a*m2.b + m1.b*m2.d;
     m.c = m1.c*m2.a + m1.d*m2.c;
     m.d = m1.c*m2.b + m1.d*m2.d;

     return m;
}

static matrix_t fibonacci( int n ) {
     matrix_t m, temp;
     int ret;
     m.a = 1;
     m.b = 1;
     m.c = 1;
     m.d = 0;

     if (1 == n)
     {
          return m;
     } else {
          temp = fibonacci( n / 2 );
          temp = matrix_multiply( temp, temp );
     }

     if( n & 1 ) {
          temp = matrix_multiply( temp, m );
     }

     return temp;
     /* ret = matrix_multiply( m, m ); */
     /* printf( "ret.a=%d", ret.a ); */
}

int main(int argc, char *argv[])
{
     int n = 45;
     matrix_t ret;
     ret = fibonacci( n );
     printf( "n=%d, ret.c=%d\n", n, ret.c );
     return 0;
}
