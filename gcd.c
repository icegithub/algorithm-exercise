#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VLength 100

void changePosition(int *m, int *n);
void euclidAlgorithm(int m, int n);
void continuousDivisible(int m, int n);
void factorizate(int m, int []);
void factorizateAlgorithm( int, int );
int  prime[100];



//The Main( enterance ) of the program
int main()
{
  int m, n;
  scanf("%d", &m);
  scanf("%d", &n);
  changePosition(&m, &n);
  printf ("Euclid Algorithm:\n");
  euclidAlgorithm(m, n);
  printf ("Continuous Divisible Algorithm:\n");
  continuousDivisible(m,n);
  printf ("Factorizate Algorithm:\n");
  factorizateAlgorithm(m, n);
  return 0;
}


//Euclid Algorithm
void
euclidAlgorithm(int m, int n)
{
  int r;
  if(n==0)
    printf("0?");
  else {
      r = m % n;
        while(r != 0) {
            n = r;
            m = n;
            r = m % n;
            if(r == 0)
                printf("%d\n", m);
        }
  }
}


//Continus Divisible 
void
continuousDivisible(int m, int n)
{
   int min;
   min = n;
   //printf("%f", m*1.0/min);
   for(; min>0; min--) {
       if( (m%min == 0) && (n%min == 0) ) {
           printf("%d\n", min);
           break;
        }
        else
            continue;
   }
}


//Change Position and make sure m is biger than n
void
changePosition(int *m, int *n)
{
  int *temp = NULL;
  printf( "Start Change Position\n" );
  if(*m < *n) {
    *temp = *m;
    *m = *n;
    *n = *temp;
  }
  else ;
}

void
factorizate(int m, int vector[])
{
     int i;
     int j = 0;
     /* int vector[100]; //To Storage the factorizational number */
     for (i=2; i<=m; i++) {
          if(m%i == 0) {
               vector[j] = i;
               m /= i;
               i = 1;
               j++;
          }
     }
     /* for(i=0; i<j; i++) */
     /*      printf("%d ", vector[i]); */
     /* printf ("\n"); */
}

/* int */
/* seekPrime( int m ) */
/* { */
/*      if( m <= 0 | m = 1) */
/*           return 0; */
/*      if( m == 2 ){ */
/*           prime[ 0 ] = 2; */
/*           return 1; */
/*      } */
     
/*      //make sure the m is > 3 */
/*      int i; */
/*      for ( i = 3; i < Math.sqrt( m ); i+=2 ) */
/*      { */
/*           if (m%i != 0) */
/*           { */
               
/*           } */
/*      } */
/* } */

void
seekPrime( int m )
{
     
}

void
factorizateAlgorithm(int m, int n)
{
     int i=0, j=0, gcd=1;
     int m_vector[100] = {0};
     int n_vector[100] = {0};
     int common[100]   = {0};
     if (m<=0 || n<=0)
     {
          exit( 1 );
     }
     factorizate( m, m_vector );
     factorizate( n, n_vector );
     while( m_vector[j] != '\0' ) {
          printf( "%d ", m_vector[j] );
          j++;
     }
     printf ("\n");
     j=0;
     while( n_vector[j] != '\0' ) {
          printf( "%d ", n_vector[j] );
          j++;
     }
     i=0, j=0;
     while( m_vector[i] != '\0' )
     {
          while (n_vector[j] != '\0')
          {
               if (m_vector[i] == n_vector[j])
               {
                    common[i] = m_vector[i];
               }
               j++;
          } 
          j=0;
          i++;
     }
     j=0;
     if (common[j] == 0)
     {
          printf ("This is no prime\n");
     } else {
          do {
               gcd *= common[j];
               j++;
          }while(common[j]!='\0');
     }
     printf ("\ngcd=%d\n", gcd);
}
