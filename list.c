#include <stdio.h>
#include <stdlib.h>
#include "list.h"

status initList( linkList *l )
{
     l->head = l->tail = ( listPtr )malloc( sizeof(listNode) );
     if( l->head == NULL || l->tail == NULL )
         return ERROR;
     l->head->next=l->tail->next=NULL;
     return OK;
}

/*
 * destory the list
 */
status destoryList( linkList *l )
{
     if( l == NULL )
          return ERROR;
     listPtr lp = NULL;
     while( l->head->next != NULL ) {
          lp = l->head; //the head node
          lp = lp->next;
          l->head->next = lp->next; 
          free( lp );
     }
     free( l->head );
     free( l->tail );
     return OK;
}

/*
 * clear the list
 */
status clearList( linkList *l )
{
     if ( NULL == l )
          return ERROR;
     if ( listEmpty(l) == isEmpty ) {
          printf( "**The list is empty**\n" );
          return ERROR;
     }
     listPtr lp = NULL;
     lp = l->head;//The head node
     while( lp->next != NULL ) {
          lp->next->data = 0;
          lp = lp->next;
     }
     return OK;
}

/*
 * print the list
 */
void printList( linkList *l )
{
     /* printf( "print List\n" ); */
     if ( l == NULL )
          exit( 1 );
     listPtr lp = l->head->next;

     printf( "The number in the list:\n" );
     if (listEmpty(l) == isEmpty)
     {
          printf( "**The list is null**\n" );
     }
     while( lp != NULL ) {
          printf( DATAFORMAT, lp->data );
          lp = lp -> next;
     }
     /* do { */
     /*      /\* lp = lp -> next; *\/ */
     /*      printf( DATAFORMAT, lp->data ); */
     /*      lp = lp -> next; */
     /* }while( lp ); */
     printf ("\n");
}

/*
 * enqueue the list
 * put data into the list
 */
status enList( linkList *l, listElemType e )
{
     listPtr lp = ( listPtr )malloc( sizeof(listNode) );
     if ( lp != NULL ) {
          lp -> data = e;
          lp -> next = NULL;
          l->tail->next = lp;
          l->tail = lp;
     } else {
          return ERROR;
     }
     return OK;
}

/*
 * search the node by the element and 
 * return the point before then element if find 
 * or reuturn NULL
 */
listPtr queryByElement( linkList *l, listElemType e )
{
     listPtr lp = l->head;//the head node that dont has data
     /* printf( "Head: %d \n", lp->data ); */
     do {
          if ( lp->next == NULL )
               return NULL; //The head node
          else if ( lp->next->data == e ) {
               /* printf( "The front data=%d \n", lp->data ); */
               return lp; //return the front node point
          }
          else
               lp = lp -> next;
     }while( lp->next );
     
     return NULL;
}

/*
 * dequeue the list
 * delete the data from the list
 */
status deListByElement( linkList *l, listElemType e )
{
     listPtr lp_front = queryByElement( l, e );
     listPtr lp_deleted = lp_front -> next;
     //Delete the node is the last
     if ( lp_front == NULL )
          return ERROR; //this mean lp_front is point to the head node or something that not node has data
     
     //The last node
     else if ( lp_deleted->next == NULL ) {
          /* printf( "This number:%d out of the queue\n", lp_deleted->data ); */
          lp_front -> next = NULL;
          l->tail = lp_front;
          free( lp_deleted );
     } else {
          /* printf( "This number:%d out of the queue\n", lp_deleted->data ); */
          lp_front->next = lp_deleted->next;
          free( lp_deleted );
     }
     return OK;
}

/*
 * return the length of the list
 */
int listLength( linkList *l )
{
     int length = 0;
     if ( l == NULL )
          return ERROR;
     listPtr lp = l->head;//The head node
     while( NULL != lp->next ) {
          length++;
          lp = lp->next;
     }
     return length;
}

/*
 * judge the list is empty{}
 * if empty return 1{}
 * else return 0{}
 */
int listEmpty( linkList *l )
{
     if( l == NULL )
          return ERROR;
     else if ( l->head->next == NULL )
          return isEmpty;
     return isNotEmpty;
}


//********************************************//
//test 
/* int main(int argc, char *argv[]) */
/* { */
/*      linkList *l = ( linkList* )malloc( sizeof( linkList ) ); */
/*      /\* createList(l); *\/ */
/*      /\* linkList *l; *\/ */
/*      /\* linkList l; *\/ */
/*      initList( l ); */
/*      enList( l, 100 ); */
/*      enList( l, 200 ); */
/*      enList( l, 300 ); */
/*      enList( l, 400 ); */
/*      enList( l, 500 ); */
/*      enList( l, 600 ); */
/*      enList( l, 700 ); */
/*      enList( l, 800 ); */
/*      enList( l, 900 ); */
/*      enList( l, 1000 ); */
/*      enList( l, 1200 ); */
/*      enList( l, 1300 ); */
/*      printList( l ); */
/*      int length = 0; */
/*      length = listLength( l ); */
/*      printf( "The length of the list:%d\n", length); */
/*      deListByElement( l, 1300 ); */
/*      deListByElement( l, 1200 ); */
/*      deListByElement( l, 500 ); */
/*      deListByElement( l, 100 ); */

/*      printList( l ); */
/*      clearList( l ); */
/*      printList( l ); */
/*      destoryList( l ); */
/*      printList( l ); */
/*      /\* int a = 100; *\/ */
/*      /\* printf ("%d \n", a); *\/ */
/*      /\* printf (DATAFORMAT, test() ); *\/ */
/*      return 0; */
/* } */

/*
 * create a list by the init length
 */
/* status createList( linkList *l ) */
/* { */
/*      int i = 1; */
/*      listPtr lp = NULL; */
/*      l->head = l->tail = lp = ( listPtr )malloc( sizeof(listNode) ); */
/*      if ( lp != NULL ) { */
/*           lp -> data = 0; */
/*           lp -> next = NULL; */
/*           for ( ; i < INITLENGTH; i++ ) { */
/*                lp = ( listPtr )malloc( sizeof(listNode) ); */
/*                if ( lp != NULL ) { */
/*                     lp -> data = 0; */
/*                     lp -> next = NULL; */
/*                     l->tail->next = lp; */
/*                     l->tail = lp; */
/*                } else { */
/*                     return ERROR; */
/*                } */
/*           } */
/*      } */
/*      return OK; */
/* } */

