#include <stdio.h>
#include <stdlib.h>

///////////firse method///////////
/*
 * please see the function:
 * factorizate in gcd.c
*/


//////////second method//////////
/*
 * first we find the prime smaller 
 * than the m( which is factorizated )
*/
void 
getPrime( int m, int prime[] )
{
     int i = 0;
     for( ; i<m; i++ ) {
          prime[i] = i+2; //Make sure the begin number is 2
     }
}


int main(int argc, char *argv[])
{
     
     return 0;
}
