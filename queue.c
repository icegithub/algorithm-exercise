#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* create a queue */
status initQueue( linkQueue *q )
{
     
}

/* destory a queue */
status destroyQueue( linkQueue *q ){}

/* clear a queue */
status clearQueue( linkQueue *q ){}

/* if queue is empty return true or return false */
status queueEmpty( linkQueue q ){}

/* return the length of the queue */
int    queueLength( linkQueue Q ){}

/*
 * if queue is not empty and 
 * return head by e and reuturn OK
 * else reutnr ERROR
 */
status getHead( linkQueue q, qElemType *e ){}

/*
 * put the e into the tail( rear ) of the queue
*/
status enQueue( linkQueue *q, qElemType e ){}

/*
 * if queue is not empty, delete the head element and
 * return the the head element by e, return OK
 * or return ERROR
 */
status deQueue( linkQueue *q, qElemType *e ){}


int main(int argc, char *argv[])
{
     
     return 0;
}
