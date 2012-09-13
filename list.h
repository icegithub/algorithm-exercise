#ifndef _LIST_H
#define _LIST_H

#define OK 1
#define ERROR 0
#define INITLENGTH 10
#define DATAFORMAT "%d "

enum listEmpty{isEmpty, isNotEmpty};

typedef int listElemType;
typedef int status;

typedef struct list{
     listElemType data;
     struct list *next;
}listNode, *listPtr;

typedef struct {
     listPtr head;
     listPtr tail;
}linkList;

/*
 * create a list 
*/
/* status createList( linkList *l ); */

/*
 * init a list 
 */
status initList( linkList *l );

/*
 * destory the list
*/
status destoryList( linkList *l );

/*
 * clear the list
*/
status clearList( linkList *l );

/*
 * print the list
*/
void printList( linkList *l );

/*
 * enqueue the list
 * put data into the list
*/
status enList( linkList *l, listElemType e );

/*
 * dequeue the list
 * delete the data from the list
 */
status deListByElement( linkList *l, listElemType e );

/*
 * search the node by the element and 
 * return the point 
*/
listPtr queryByElement( linkList *l, listElemType e ); 

/*
 * return the length of the list
*/
int listLength( linkList *l );

/*
 * judge the list is empty;
 * if empty return 1;
 * else return 0;
*/
int listEmpty( linkList *l );

#endif
