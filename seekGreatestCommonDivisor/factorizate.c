#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "list.h"
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
getPrime( int m, linkList *l )
{
     int i = 0, j = 0;
     int length;
     int e;
     for( ; i<=m-2; i++ ) {
          e=i+2;
          enList(l, e); //Make sure the begin number is 2
     }
     printf( "get Prime" );
     length = listLength( l );
     printf ("The length is:%d\n", length);
     printList( l );
     for ( j=1; j<=5; j++ ) {
          e = 2*(j+1);
          deListByElement( l, 2*j );
     }
     printList( l );
}

int main(int argc, char *argv[])
{
     linkList *l = ( linkList* )malloc( sizeof( linkList ) );
     initList( l );
     getPrime( 2, l );
     return 0;
}
