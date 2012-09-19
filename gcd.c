/*
 *@author:icecream
 *@contect:creamidea@gmail.com
 *@time:Sun Sep  9 09:07:28 2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void changePosition(int *m, int *n);
void euclidAlgorithm(int , int );
void continuousDivisible(int , int );
void mutualMultiplicate( int [] );
void findSameNumber( int [], int [], int [] );
void factorizate(int , int []);
void factorizateAlgorithm( int, int );
int  prime[100];

int step[3] = {0};

//Change Position and make sure m is biger than n
void
changePosition(int *m, int *n)
{
     int *temp = NULL;
     /* printf( "Start Change Position\n" ); */
     if(*m < *n) {
          *temp = *m;
          *m = *n;
          *n = *temp;
     }
     else ;
}


//Euclid Algorithm
/*gcd( m,n ) = gcd( n, m%n )*/
void
euclidAlgorithm(int m, int n)
{
     int r;
     if(n==0) {
          printf("0?");
          exit( 1 );
     }
     else {

          do{
               r = m % n;
               m = n;
               n = r;
               step[0]++;
          }while( n != 0 );
          printf("gcd=%d\n", m);
 
     }
}


//Continus Divisible
/*
 *find the min number between m and n,
 *then find the number that m and n can 
 *division it together
 */ 
void
continuousDivisible(int m, int n)
{
     int min;
     min = n;
     for(; min>0; min--) {
          if( (m%min == 0) && (n%min == 0) ) {
               printf("gcd=%d\n", min);
               break;
          }
          else {
               step[1]++;
               continue;
          }
     }
}


/* This program is to factorizate.
 * My think is : 
 * create a vector to put the factorization number,
 * and the m( factorizated number) continue division .
 * I will write some method to get the factorizatision 
 * number in factorizate.c
*/
void
factorizate(int m, int vector[])
{
     int i;
     int j = 0;
     for (i=2; i<=m; i++) {
          step[3]++;
          if(m%i == 0) {
               vector[j] = i;
               m /= i;
               i = 1;    //Make Sure the i = 2 when the loop begin
               j++;
          }
     }
}

/*
 *find the same number between two array
*/
void 
findSameNumber( int m_vector[], int n_vector[], int common[] )
{
     int i=0, j=0;
     while( m_vector[i] != '\0' )
     {
          while (n_vector[j] != '\0')
          {
               step[3]++;
               if (m_vector[i] == n_vector[j])
               {
                    common[i] = m_vector[i];
               }
               j++;
          } 
          j=0;
          i++;
     }
}

/*
 *let the number in array multiplicate one by one
 *( mutual )
*/
void 
mutualMultiplicate( int common[] )
{
     int j=0;
     int gcd=1;
     if (common[j] == 0)
     {
          printf ("This is no prime\n");
     } else {
          do {
               gcd *= common[j];
               j++;
          }while(common[j]!='\0');
     }
     printf ("gcd=%d\n", gcd);
}

void
factorizateAlgorithm(int m, int n)
{
     int m_vector[100] = {0};
     int n_vector[100] = {0};
     int common[100]   = {0};
     if (m<=0 || n<=0)
     {
          exit( 1 );
     }
     factorizate( m, m_vector );
     factorizate( n, n_vector );
     findSameNumber( m_vector, n_vector, common );
     mutualMultiplicate( common );
}

//The Main( enterance ) of the program
int main()
{
     int m, n;
     /* printf ("Please input two number( blank ):"); */
     /* scanf("%d", &m); */
     /* scanf("%d", &n); */
     /* changePosition(&m, &n); */


     /* printf ("\nEuclid Algorithm:\n"); */
     /* euclidAlgorithm(457382, 89832); */
     /* printf ("The Euclid ALgorithm Step:%d\n", step[0]); */


     /* printf ("\nContinuous Divisible Algorithm:\n"); */
     /* continuousDivisible(54930, 42021); */
     /* printf ("The Continuous ALgorithm Step:%d\n", step[1]); */


     printf ("\nFactorizate Algorithm:\n");
     factorizateAlgorithm(54930, 42021);
     printf ("The Factorizate ALgorithm Step:%d\n", step[3]);
     return 0;
}
