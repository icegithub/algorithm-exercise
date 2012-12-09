#include <stdio.h>

double f( double x );
double f_prime( double x );
double myFabs( double, double );

int
commonMethod(int n) 
{
     if( n < 0 ) {
          printf( "N is 0??\n" );
          return 0;
     }
     
     int i;
     for (i = 0; i < n; ++i) {
          if (i*i > n) {
               return i-1;
          } else {
               continue;
          }
     }
}


/**
 *http://en.wikipedia.org/wiki/Newton's_method
 * */
double newtonMethod( double x_0, double tol, int max_iters, 
                     int* iters_p, int* converged_p)
{
     double x = x_0;
     double x_prev;
     int iter = 0;

     do
     {
          iter++;
          x_prev = x;
          x = x_prev - f( x_prev )/f_prime( x_prev );
     } while (myFabs( x, x_prev ) > tol && iter < max_iters);

     if (myFabs( x, x_prev ) <= tol){
          *converged_p = 1;
     } else {
          *converged_p = 0;
     }
     *iters_p = iter;
     
     return x;
     
}

double f( double x )
{
     return x*x-2;
}
double f_prime( double x )
{
     return 2*x;
}

double myFabs( double x, double x_prev )
{
     return x<x_prev ? x_prev - x: x - x_prev;
}

int main(int argc, char *argv[])
{
     int n;
     int reslut;
     printf ("First Method:\n");
     printf ("please input the n:\n");
     scanf( "%d", &n );
     reslut = commonMethod( n );
     printf( "Radical Sign N is %d\n", reslut );
     printf ("\n\nSecond Method:\n");
     
     double x_0;       /* Initial guess                */
     double x;         /* Approximate solution         */
     double tol;       /* Maximum error                */
     int    max_iters; /* Maximum number of iterations */
     int    iters;     /* Actual number of iterations  */
     int    converged; /* Whether iteration converged  */
     
     printf( "Enter x_0, tol, and max_iters\n");
     scanf( "%lf %lf %d", &x_0, &tol, &max_iters);

     x = newtonMethod( x_0, tol, max_iters, &iters, &converged);

     if ( converged) {
          printf( "Newton algorithm converged after %d steps.\n", iters);
          printf( "The approximate solution is %19.16e\n", x);
          printf( "f( %19.16e) = %19.16e\n", x, f(x));
     } else {
          printf( "Newton algorithm didn't converge after %d steps.\n", iters);
          printf( "The final estimate was %19.16e\n", x);
          printf( "f( %19.16e) = %19.16e\n", x, f( x));
     } 

     return 0;
}
